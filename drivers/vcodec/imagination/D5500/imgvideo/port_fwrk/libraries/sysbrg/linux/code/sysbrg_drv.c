/*!
 *****************************************************************************
 *
 * @File       sysbrg_drv.c
 * @Title      The System Bridge user mode API.
 * @Description    This file contains the System Bridge Driver for Linux.
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#include <img_defs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/mm.h>
#include <linux/compat.h>
#include <asm/atomic.h>
#include <asm/io.h>
#include <sysbrg_api.h>
#include <sysbrg_api_km.h>
#include <sysbrg_utils.h>
#include <sysos_api_km.h>
#include <lst.h>
#include <sysbrg_drv.h>
#include <system.h>
#include <sysenv_api_km.h>
#include <sysos_api_km.h>
#include <report_api.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <linux/version.h>
#include <linux/uaccess.h>
#ifdef IMG_MEM_ERROR_INJECTION
#include "mem_error_injector.h"
#endif /* IMG_MEM_ERROR_INJECTION */

#ifdef PDUMP_INTERFACE
#include <sysbrg_pdump.h>
#endif

#define SYSBRG_VERSION     "1.0.0"
#define SYSBRG_MAX_MINORS  1

 #define PCTRL_PERI_STAT1 0xE8A09098
static const IMG_CHAR *  pszModuleName = IMGSYSBRG_MODULE_NAME;

static struct class *  sysbrg_class;
static int             sysbrg_major;
extern int gIsFpga;

struct sysbrg_device
{
    wait_queue_head_t  wait;
    struct cdev        cdev;
    struct mutex       open_lock;
};

struct listener
{
    IMG_HANDLE pid;
};
static struct sysbrg_device *  gpsUkcDev = NULL;
static unsigned char           sysbrg_devices[SYSBRG_MAX_MINORS];

#ifdef IMG_MEM_ERROR_INJECTION
/* Memory Error Injector parameters. */
/* The memory error injection configuration stream. */
char *  memerrinj_config = NULL;
module_param(memerrinj_config, charp, 0444);
MODULE_PARM_DESC(memerrinj_config, "The memory error injection configuration stream.");
/* The memory error injection report dir. */
/* NOTE: Reconfigurable at runtime by writing to /sys/module/vdecdd/parameters/memerrinj_dir. */
char *  memerrinj_dir = "/tmp";
module_param(memerrinj_dir, charp, 0664);
MODULE_PARM_DESC(memerrinj_dir, "The memory error injection report dir.");
#endif /* IMG_MEM_ERROR_INJECTION */

/*!
******************************************************************************

 @Function              sysbrg_ioctl

******************************************************************************/
static long sysbrg_ioctl(
    struct file *  file,
    unsigned int   cmd,
    unsigned long  arg
)
{
    if (_IOC_TYPE(cmd) != SYSBRG_IOCTL_MAGIC)
    {
        return -ENOTTY;
    }

    switch (cmd)
    {
        case SYSBRG_IOCTL_APICALL:
#ifdef CONFIG_COMPAT
        case COMPAT_SYSBRG_IOCTL_APICALL:
#endif
        {
            SYSBRG_POINTER_ARG(psPacket) psPacket = make_sysbrg_pointer_from_num(arg);
            SYSBRG_sPacket           psPacketL;
            IMG_BOOL                 bFoundAPI = IMG_FALSE;
            SYSBRGKM_sAPIInfo *      psKernelAPIInfo = IMG_NULL;

            if (SYSOSKM_CopyFromUser(&psPacketL, psPacket, sizeof(SYSBRG_sPacket))) {
                IMG_ASSERT(!"failed to copy from user");
                return -EFAULT;
            }

            bFoundAPI = SYSBRGU_GetAPI(psPacketL.ui32APIId, &psKernelAPIInfo);

            if (bFoundAPI && psKernelAPIInfo && psKernelAPIInfo->pfnDispatcher)
            {
                psKernelAPIInfo->pfnDispatcher(&psPacketL);
            }
            else
            {
                printk(KERN_ERR "ERROR: %s: ioctl - API ID: %d - not found\n", pszModuleName, psPacketL.ui32APIId);
                return -EINVAL;
            }
            break;
        }
        default:
        {
            printk(KERN_ERR "%s: Not ioctl command\n", pszModuleName);
            return -ENOTTY;
        }
    }

    return 0;
}

/*!
******************************************************************************

 @Function              sysbrg_mmap

******************************************************************************/
static int sysbrg_mmap(
    struct file *            filep,
    struct vm_area_struct *  vma
)
{   
    int                     iRes = 0;
    SYSBRGU_sMappableReg *  psMappableReg;

    if (vma->vm_end < vma->vm_start)
    {
        return -EINVAL;
    }

    /* Get infomation for this mappable region...*/
    psMappableReg = SYSBRGU_GetMappableRegion(vma->vm_pgoff<<PAGE_SHIFT);
    IMG_ASSERT(psMappableReg != IMG_NULL);
    if (psMappableReg == IMG_NULL)
    {
        return -EINVAL;
    }

    IMG_ASSERT((vma->vm_end - vma->vm_start) <= psMappableReg->ui32Size);
    if ((vma->vm_end - vma->vm_start) > psMappableReg->ui32Size)
    {
        return -EINVAL;
    }

    /* If cached...*/
    if ((psMappableReg->eMemAttrib & SYS_MEMATTRIB_CACHED) != 0)
    {
        /* Default - do nothing...*/
    }

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29)
    /* Write combined implies non-cached in Linux x86. If we additionally call
       pgprot_noncached, we will not have write combining, just non-cached. */
    if ((psMappableReg->eMemAttrib & SYS_MEMATTRIB_WRITECOMBINE) != 0)
    {
        vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
    } else
#endif
    /* If uncached...*/
    if ((psMappableReg->eMemAttrib & SYS_MEMATTRIB_UNCACHED) != 0)
    {
        vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
    }

    /* Physical address switch.  */
    vma->vm_pgoff = ((unsigned long)psMappableReg->paCpuPhysAddr >> PAGE_SHIFT);

    /* We can communicate any kind of private information via this element */
    vma->vm_private_data = filep->private_data;

    DEBUG_REPORT(REPORT_MODULE_SYSBRG, "%s size %u phys 0x%llx", __FUNCTION__,
                 psMappableReg->ui32Size, psMappableReg->paCpuPhysAddr);

    if (psMappableReg->pSysMem) {
    	// Normal sysmem memory.
    	iRes = SYSMEMU_MapToUser(psMappableReg->pSysMem, vma);

    } else {
    	// Device-related memory ( usually registers )
    	iRes =  remap_pfn_range(vma,
    								vma->vm_start,
    								vma->vm_pgoff,
    								vma->vm_end - vma->vm_start,
    								vma->vm_page_prot
    							   );
    }

    return iRes;
}


/*!
******************************************************************************

 @Function              sysbrg_open

******************************************************************************/
static int sysbrg_open(
    struct inode *  inode,
    struct file *   file
)
{
	if (gIsFpga) {
        int dev_exi = 0;
        unsigned long * viraddr_pctrl = NULL;
        viraddr_pctrl = (unsigned long *)ioremap(PCTRL_PERI_STAT1,4);
        if (viraddr_pctrl)
        {
            dev_exi = readl(viraddr_pctrl) & 0x2;
            iounmap(viraddr_pctrl);
            viraddr_pctrl = NULL;
            if (!dev_exi)
            {
                printk("Device enc or dec is not exist!\n");
                return -ERESTARTSYS;
            }
        }
        else
        {
            printk("PCTRL_PERI_STAT1 ioremap failed!\n");
        }
	}

    struct sysbrg_device *  dev = container_of(inode->i_cdev, struct sysbrg_device, cdev);
    struct listener *listener;

    listener = kzalloc(sizeof(*listener), GFP_KERNEL);
    if(listener == NULL)
    {
        return -ENOMEM;
    }
    nonseekable_open(inode, file);

    if (mutex_lock_interruptible(&dev->open_lock))
    {
        kfree(listener);
        return -ERESTARTSYS;
    }

    file->private_data = listener;

    listener->pid = SYSOSKM_GetProcessId();


    mutex_unlock(&dev->open_lock);

    return 0;
}


/*!
******************************************************************************

 @Function              sysbrg_release

******************************************************************************/
static int sysbrg_release(
    struct inode *  inode,
    struct file *   file
)
{
    struct sysbrg_device *dev = container_of(inode->i_cdev, struct sysbrg_device, cdev);
    struct listener *  listener = file->private_data;

    mutex_lock(&dev->open_lock);
    SYSBRGU_MakeProcessLostCb(listener->pid);
    mutex_unlock(&dev->open_lock);

        kfree(listener);

    return 0;
}


static struct file_operations sysbrg_file_ops =
{
    .open           = sysbrg_open,
    .release        = sysbrg_release,
    .unlocked_ioctl = sysbrg_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl = sysbrg_ioctl,
#endif
    .mmap           = sysbrg_mmap,
};


/*!
******************************************************************************

 @Function              sysbrg_get_free

******************************************************************************/
static unsigned int sysbrg_get_free(void)
{
    unsigned int  i;

    for (i = 0; i < SYSBRG_MAX_MINORS; i++)
    {
        if (sysbrg_devices[i] == 0)
        {
            break;
        }
    }

    return i;
}


/*!
******************************************************************************

 @Function              sysbrg_setup_cdev

******************************************************************************/
static int sysbrg_setup_cdev(void)
{
    struct device *         dev;
    struct sysbrg_device *  psUkcDev;
    unsigned int            minor;
    int                     retval;

    minor = sysbrg_get_free();
    if (minor == SYSBRG_MAX_MINORS)
    {
        printk(KERN_ERR "%s: too many devices found\n", pszModuleName);
        retval = -EIO;
        goto err_dis;
    }

    retval = -ENOMEM;
    psUkcDev = kzalloc(sizeof(*psUkcDev), GFP_KERNEL);

    if (psUkcDev == NULL)
    {
        printk(KERN_ERR "%s: Unable to allocate device\n", pszModuleName);
        goto err_reg;
    }

    mutex_init(&psUkcDev->open_lock);
    init_waitqueue_head(&psUkcDev->wait);

    cdev_init(&psUkcDev->cdev, &sysbrg_file_ops);
    psUkcDev->cdev.owner = THIS_MODULE;
    psUkcDev->cdev.ops = &sysbrg_file_ops;

    retval = cdev_add(&psUkcDev->cdev, MKDEV(sysbrg_major, minor), 1);
    if (retval)
    {
        printk(KERN_ERR "%s: chardev registration failed\n", pszModuleName);
        goto err_irq;
    }

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26)
    dev = device_create(sysbrg_class, 0, MKDEV(sysbrg_major, minor), IMGSYSBRG_MODULE_NAME"%u", minor);
#elif ((LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26)) && (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,27)))
    dev = device_create_drvdata(sysbrg_class, 0, MKDEV(sysbrg_major, minor), NULL, IMGSYSBRG_MODULE_NAME"%u", minor);
#else
    dev = device_create(sysbrg_class, NULL, MKDEV(sysbrg_major, minor), NULL, IMGSYSBRG_MODULE_NAME"%u", minor);
#endif
    if (IS_ERR(dev))
    {
        printk(KERN_ERR "%s: Can't create device\n", pszModuleName);
    }

    gpsUkcDev = psUkcDev;
    return 0;

err_irq:
    kfree(psUkcDev);
err_reg:
    sysbrg_devices[minor] = 0;
err_dis:
//err:
    return retval;
}


/*!
******************************************************************************

 @Function              sysbrg_remove

******************************************************************************/
static void  sysbrg_remove(void)
{
    struct sysbrg_device *  psUkcDev = gpsUkcDev;
    unsigned int            minor;

    /* Deinitialise SYSENVKM */
    SYSENVKM_Deinitialise();

    if (gpsUkcDev)
    {
        minor = MINOR(psUkcDev->cdev.dev);

        device_destroy(sysbrg_class, MKDEV(sysbrg_major, minor));

        cdev_del(&psUkcDev->cdev);

        kfree(psUkcDev);

        sysbrg_devices[minor] = 0;

        gpsUkcDev = NULL;
    }
}


/*!
******************************************************************************

 @Function              sysbrg_show_version

******************************************************************************/
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,33)
static ssize_t sysbrg_show_version(struct class *cls, struct class_attribute * attr, char *buf)
#else
static ssize_t sysbrg_show_version(struct class *cls, char *buf)
#endif
{
    return sprintf(buf, SYSBRG_VERSION "\n");
}

static CLASS_ATTR(version, 0444, sysbrg_show_version, NULL);


/*!
******************************************************************************

 @Function              sysbrg_init

******************************************************************************/
static int __init sysbrg_init(void)
{
    int    retval;
    dev_t  dev;

    printk(KERN_INFO "%s: Loadable Module, version " SYSBRG_VERSION "\n", pszModuleName);

    sysbrg_class = class_create(THIS_MODULE, IMGSYSBRG_MODULE_NAME);

    if (IS_ERR(sysbrg_class))
    {
        retval = PTR_ERR(sysbrg_class);
        printk(KERN_ERR "SYSBRG: can't register %s class\n", IMGSYSBRG_MODULE_NAME);
        goto err;
    }
    retval = class_create_file(sysbrg_class, &class_attr_version);

    if (retval)
    {
        printk(KERN_ERR "%s: Can't create sysfs versionfile\n", pszModuleName);
        goto err_class;
    }

    retval = alloc_chrdev_region(&dev, 0, SYSBRG_MAX_MINORS, IMGSYSBRG_MODULE_NAME);
    if (retval)
    {
        printk(KERN_ERR "%s: Can't register character device\n", pszModuleName);
        goto err_attr;
    }
    sysbrg_major = MAJOR(dev);

    /* Initialise SYSENVKM */
    retval = SYSENVKM_Initialise();
    IMG_ASSERT(retval == IMG_SUCCESS);
    if (retval != IMG_SUCCESS)
    {
        retval = -EIO;
        goto err_unchr;
    }

#ifdef PDUMP_INTERFACE
    /* Register Pdump Device.  */
    retval = imgpci_register_pdump();
    if(retval)
    {
        printk(KERN_ERR "%s: Can't register pdump interface\n", pszModuleName);
        goto err_unchr;
    }
#endif

    retval = sysbrg_setup_cdev( );
    if (retval)
    {
        printk(KERN_ERR "%s: Can't register char driver\n", pszModuleName);
        goto err_unchr;
    }

    printk(KERN_INFO "%s: Loaded\n", pszModuleName);

    return 0;
err_unchr:
    unregister_chrdev_region(dev, SYSBRG_MAX_MINORS);
err_attr:
    class_remove_file(sysbrg_class, &class_attr_version);
err_class:
    class_destroy(sysbrg_class);
err:
    return retval;
}


/*!
******************************************************************************

 @Function              sysbrg_exit

******************************************************************************/
static void __exit sysbrg_exit(void)
{
#ifdef PDUMP_INTERFACE
    /* Unregister Pdump device.  */
    imgpci_unregister_pdump();
#endif

    /* This will unregister the PCI device, so it must be called after
       unregistering pdump. */
    sysbrg_remove();

    unregister_chrdev_region(MKDEV(sysbrg_major, 0), SYSBRG_MAX_MINORS);

    class_remove_file(sysbrg_class, &class_attr_version);
    class_destroy(sysbrg_class);

#ifdef IMG_MEM_ERROR_INJECTION
    MEMERRINJ_Report(IMG_NULL);
#endif /* IMG_MEM_ERROR_INJECTION */
    printk (KERN_INFO "%s: Module successfully removed\n", pszModuleName);
}

module_init(sysbrg_init);
module_exit(sysbrg_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION(IMGSYSBRG_MODULE_NAME" - Imagination Technologies System Bridge Module");
MODULE_AUTHOR("Imagination Technologies Ltd");

