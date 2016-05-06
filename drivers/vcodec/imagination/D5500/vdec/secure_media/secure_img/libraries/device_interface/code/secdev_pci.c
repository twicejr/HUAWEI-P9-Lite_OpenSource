/*!
 *****************************************************************************
 *
 * @File       secdev_pci.c
 * @Description    This file contains the kernel mode implementation of the
 *  PCI device interface.
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

#include "target.h"
#include "secure_device.h"

#include <linux/pci.h>
#include <linux/kobject.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <asm/page.h>
#include <linux/mm.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <linux/module.h>
#include <img_defs.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0)
#include <linux/export.h>
#endif


#if defined(TARGET_CEDARVIEW)

#define PCI_CDV_VENDOR_ID   0x8086
#define PCI_CDV_DEVICE_ID0  0x0be0
#define PCI_CDV_DEVICE_ID7  0x0be7
#define PCI_REG_BAR         (0)
#define PCI_REG_OFFSET      (0x00090000)
#define PCI_REG_SIZE        (0x00010000)
#define PCI_MEM_BAR         (0)
#define PCI_MEM_OFFSET      (0x00000000)
#define PCI_MEM_SIZE        (0x00100000)
#define PCI_MAX_REGIONS     (1)            //!< Maximum allowed memory regios mappable through the driver

#elif defined(TARGET_FPGA)

#define IMGPCI_VENDOR_ID    0x1010
#define IMGPCI_DEVICE_ID    PCI_ANY_ID
#define PCI_REG_BAR         (1)
#define PCI_REG_OFFSET      (0x00000000)
#define PCI_REG_SIZE        (0x00020000)
#define PCI_MEM_BAR         (2)
#define PCI_MEM_OFFSET      (0x00000000)
#define PCI_MEM_SIZE        (0x10000000)
#define MAX_IMGPCI_MAPS     (3)
#define PCI_MAX_REGIONS     (3)            //!< Maximum allowed memory regios mappable through the driver

#else
#error Not a supported PCI device
#endif

#define PCI_ATLAS_VENDOR_ID             (0x1010)
#define PCI_ATLAS_DEVICE_ID             (0x1CF1)    //!< Atlas V1 - FPGA device ID.
#define PCI_APOLLO_DEVICE_ID            (0x1CF2)    //!< Apollo - FPGA device ID.

// from TCF Support FPGA.Technical Reference Manual.1.0.92.Internal Atlas GEN.External.doc:
#define PCI_ATLAS_SYS_CTRL_REGS_BAR     (0)         //!< Altas - System control register bar
#define PCI_ATLAS_PDP_REGS_BAR          (0)         //!< Altas - PDP register bar
#define PCI_ATLAS_PDP_REGS_SIZE         (0x2000)    //!< Atlas - size of PDP register area
#define PCI_ATLAS_SYS_CTRL_REGS_OFFSET  (0x0000)    //!< Altas - System control register offset
#define PCI_ATLAS_PDP1_REGS_OFFSET      (0xC000)    //!< Atlas - PDP1 register offset into bar
#define PCI_ATLAS_PDP2_REGS_OFFSET      (0xE000)    //!< Atlas - PDP2 register offset into bar
#define PCI_ATLAS_INTERRUPT_STATUS      (0x00E0)    //!< Atlas - Offset of INTERRUPT_STATUS
#define PCI_ATLAS_INTERRUPT_ENABLE      (0x00F0)    //!< Atlas - Offset of INTERRUPT_ENABLE
#define PCI_ATLAS_INTERRUPT_CLEAR       (0x00F8)    //!< Atlas - Offset of INTERRUPT_CLEAR
#define PCI_ATLAS_MASTER_ENABLE         (1<<31)     //!< Atlas - Master interrupt enable
#define PCI_ATLAS_DEVICE_INT            (1<<13)     //!< Atlas - Device interrupt
#define PCI_ATLAS_PDP1_INT              (1<<14)     //!< Atlas - PDP1 interrupt
#define PCI_ATLAS_PDP2_INT              (1<<15)     //!< Atlas - PDP2 interrupt
#define PCI_ATLAS_SCB_RESET             (1<<4)      //!< Atlas - SCB Logic soft reset
#define PCI_ATLAS_PDP2_RESET            (1<<3)      //!< Atlas - PDP2 soft reset
#define PCI_ATLAS_PDP1_RESET            (1<<2)      //!< Atlas - PDP1 soft reset
#define PCI_ATLAS_DDR_RESET             (1<<1)      //!< Atlas - soft reset the DDR logic
#define PCI_ATLAS_DUT_RESET             (1<<0)      //!< Atlas - soft reset the device under test
#define PCI_ATLAS_RESET_REG_OFFSET      0x0080
#define PCI_ATLAS_RESET_BITS            (PCI_ATLAS_DDR_RESET | PCI_ATLAS_DUT_RESET |PCI_ATLAS_PDP1_RESET| PCI_ATLAS_PDP2_RESET | PCI_ATLAS_SCB_RESET )

#define IS_AVNET_DEVICE(devid)  ((devid)!=PCI_ATLAS_DEVICE_ID && (devid)!=PCI_APOLLO_DEVICE_ID)
#define IS_ATLAS_DEVICE(devid)  ((devid)==PCI_ATLAS_DEVICE_ID)
#define IS_APOLLO_DEVICE(devid) ((devid)==PCI_APOLLO_DEVICE_ID)

#define PCI_APOLLO_INTERRUPT_STATUS  (0x00C8)    //!< Atlas - Offset of INTERRUPT_STATUS
#define PCI_APOLLO_INTERRUPT_ENABLE  (0x00D8)    //!< Atlas - Offset of INTERRUPT_ENABLE
#define PCI_APOLLO_INTERRUPT_CLEAR   (0x00E0)    //!< Atlas - Offset of INTERRUPT_CLEAR


/*!
******************************************************************************
   Structure used to describe a PCI bar memory region
******************************************************************************/
struct pci_mem
{
    struct kobject  kobj;
    IMG_PHYSADDR    addr;
    unsigned long   size;
    void __iomem *  pvKmAddr;
};

/* PCI device detected? */
static IMG_BOOL gbDevMapped = IMG_FALSE;

/* Device information...*/
static SECURE_sDev *         gpsInfo = IMG_NULL;
static IMG_CHAR *            gpszDevName;

/* PCI bars array */
static struct pci_mem  gsPCIMem [PCI_MAX_REGIONS];


#ifdef TARGET_HEADER_NAME
#include TARGET_HEADER_NAME
#else
#error TARGET_HEADER_NAME has to be defined in order to use TAL light
#endif
/*!
******************************************************************************

 @Function                pciio_UnmapResources

******************************************************************************/
static IMG_VOID pciio_UnmapResources(IMG_UINT32 ui32Bar)
{
    /* Release the internal memory */
    if(!gsPCIMem[ui32Bar].pvKmAddr)
        return;

    iounmap(gsPCIMem[ui32Bar].pvKmAddr);

    //printk(KERN_DEBUG "%s bar %u address 0x%lx size 0x%lx km addr 0x%p\n", __FUNCTION__,
           //ui32Bar, gsPCIMem[ui32Bar].addr, gsPCIMem[ui32Bar].size, gsPCIMem[ui32Bar].pvKmAddr);

    gsPCIMem[ui32Bar].pvKmAddr = NULL;
}
/*!
******************************************************************************

 @Function                pciio_RemapResources

******************************************************************************/
static IMG_VOID * pciio_RemapResources(IMG_VOID *dev, IMG_UINT32 ui32Bar)
{
    static const unsigned long maxMapSize_s = 256*1024*1024;
    struct pci_dev *pci_dev = (struct pci_dev *)dev;

    /* Create a user space mapping for each of the i32Bars */
    if (gsPCIMem[ui32Bar].pvKmAddr)
    {
        goto out;
    }

    gsPCIMem[ui32Bar].addr = pci_resource_start(pci_dev, ui32Bar);
    gsPCIMem[ui32Bar].size = pci_resource_len(pci_dev, ui32Bar);
    if (gsPCIMem[ui32Bar].size > maxMapSize_s) {
        /* We avoid mapping too big regions: we do not need such a big amount of memory
           and some times we do not have enough contiguous 'vmallocable' memory. */
        printk(KERN_WARNING "%s Not mapping all available memory for bar %u\n",
               __FUNCTION__, ui32Bar);
        gsPCIMem[ui32Bar].size = maxMapSize_s;
    }
    gsPCIMem[ui32Bar].pvKmAddr = ioremap(gsPCIMem[ui32Bar].addr, gsPCIMem[ui32Bar].size);

    //printk(KERN_DEBUG "%s bar %u address 0x%lx size 0x%lx km addr 0x%p\n", __FUNCTION__,
           //ui32Bar, gsPCIMem[ui32Bar].addr, gsPCIMem[ui32Bar].size, gsPCIMem[ui32Bar].pvKmAddr);

out:
    return (void*)(unsigned long) gsPCIMem[ui32Bar].pvKmAddr;
}
/*!
******************************************************************************

 @Function                pciio_PciDetectDevice

******************************************************************************/
static IMG_RESULT pciio_PciDetectDevice(SECDEV_eMapArea eArea)
{
    IMG_UINT32           ui32Result = IMG_SUCCESS;
    struct pci_dev *     dev;

    if (1)//!gbDevMapped)
    {
        /* Register pci driver with the OS */
        IMG_ASSERT(gpszDevName != IMG_NULL);

#if defined (TARGET_CEDARVIEW)
        {
            IMG_UINT32 i;

            for(i = PCI_CDV_DEVICE_ID0; i <= PCI_CDV_DEVICE_ID7; i++)
            {
                dev = pci_get_device(PCI_CDV_VENDOR_ID, i, NULL);
                if(dev != IMG_NULL)
                {
                    break;
                }
            }
        }
#elif defined (TARGET_FPGA)
        // Check first for Apollo card otherwise try Atlas.
        dev = pci_get_device(IMGPCI_VENDOR_ID, PCI_APOLLO_DEVICE_ID, NULL);
        if (dev == IMG_NULL)
        {
            dev = pci_get_device(IMGPCI_VENDOR_ID, PCI_ATLAS_DEVICE_ID, NULL);
        }

#endif
        IMG_ASSERT(dev != IMG_NULL);

#if defined (TARGET_FPGA)
        /* Create a kernel space mapping for each of the bars */
        switch (eArea)
        {
        case SECDEV_MAPAREA_REGISTER:
            pciio_RemapResources(dev, 1);
            break;

        case SECDEV_MAPAREA_MEMORY:
            pciio_RemapResources(dev, 2);
            break;

        case SECDEV_MAPAREA_REG_MEM:
            pciio_RemapResources(dev, 1);
            pciio_RemapResources(dev, 2);
            break;

        default:
            IMG_ASSERT(IMG_FALSE);
            break;
        }

#elif defined (TARGET_CEDARVIEW)
        pciio_RemapResources(dev, 0);
#endif

#if defined (TARGET_FPGA)
        /* Check the device bar...*/
        if (!(PCI_REG_BAR >= PCI_MAX_REGIONS))
        {
            IMG_ASSERT(PCI_REG_OFFSET + PCI_REG_SIZE <= gsPCIMem[PCI_REG_BAR].size);
            if (PCI_REG_OFFSET + PCI_REG_SIZE > gsPCIMem[PCI_REG_BAR].size)
            {
                IMG_ASSERT("Error"==0);
                return IMG_ERROR_GENERIC_FAILURE;
            }
        }
        else
        {
            IMG_ASSERT("Error"==0);
            return IMG_ERROR_GENERIC_FAILURE;
        }
#endif
        gbDevMapped = IMG_TRUE;

    }


    return ui32Result;
}
/*!
******************************************************************************

 @Function                pciio_DeviceAttach

******************************************************************************/
static IMG_RESULT pciio_DeviceAttach(
    IMG_CHAR *      pszDevName,
    SECDEV_eMapArea  eArea
)
{
    IMG_UINT32  ui32Result;

    IMG_ASSERT(gpszDevName != IMG_NULL);
    if (gpszDevName != IMG_NULL)
    {
        IMG_ASSERT(IMG_STRCMP(pszDevName, gpszDevName) == 0);
    }
    else
    {
        return IMG_ERROR_GENERIC_FAILURE;
    }

    /* In this implementation we initialise the PCI component */
    ui32Result = pciio_PciDetectDevice(eArea);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                SECDEV_Initialise

******************************************************************************/
IMG_RESULT SECDEV_Initialise(IMG_VOID)
{
    IMG_UINT32 ui32Result;

    (void)gsTargetConfig; /* Avoid compiler warning. */

    if (gpszDevName == IMG_NULL)
    {
        gpszDevName = IMG_STRDUP(asDevice[0].pszDeviceName);
        IMG_ASSERT(gpszDevName);
        if (gpszDevName == IMG_NULL)
        {
            ui32Result = IMG_ERROR_OUT_OF_MEMORY;
            goto error;
        }
    }

    return IMG_SUCCESS;

error:
    return ui32Result;
}


/*!
******************************************************************************

 @Function                SECDEV_DeInitialise

******************************************************************************/
IMG_VOID SECDEV_DeInitialise(SECDEV_eMapArea eArea)
{
    if (gbDevMapped)
    {
#if defined (TARGET_FPGA)
        if(eArea == SECDEV_MAPAREA_REGISTER)
        {
            pciio_UnmapResources(1);
        }
#ifdef SECURE_MEDIA_SUPPORT
        if(eArea == SECDEV_MAPAREA_MEMORY)
        {
            printk(KERN_DEBUG "Umapping secure memory\n");
            pciio_UnmapResources(2);
        }
        if(gsPCIMem[1].pvKmAddr == IMG_NULL &&  gsPCIMem[2].pvKmAddr == IMG_NULL)
        {
            gbDevMapped = IMG_FALSE;
        }
#else
        gbDevMapped = IMG_FALSE;
#endif
#elif defined (TARGET_CEDARVIEW)
        pciio_UnmapResources(0);
        gbDevMapped = IMG_FALSE;
#endif

    }

    if (gpszDevName)
    {
        IMG_FREE(gpszDevName);
        gpszDevName = IMG_NULL;
    }
}
/*!
******************************************************************************

 @Function                SECDEV_LocateDevice

 @Description
 This implementation can be called twice:
 Once for the main device under test, and once for a PDP subdevice on an ATLAS card

******************************************************************************/
IMG_RESULT SECDEV_LocateDevice(
	SECURE_sDev *   psInfo,
	SECDEV_eMapArea  eArea
)
{
    IMG_UINT32 ui32Result;

    if (gpsInfo == NULL)
    {
        gpsInfo = psInfo;
    }

    /* Configure the device...*/
    ui32Result = pciio_DeviceAttach(psInfo->pszDeviceName, eArea);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    if(ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Save register pointer etc....*/
    psInfo->paPhysRegBase  = gsPCIMem[PCI_REG_BAR].addr + PCI_REG_OFFSET;
    psInfo->pvKmRegBase    = gsPCIMem[PCI_REG_BAR].pvKmAddr + PCI_REG_OFFSET;
    psInfo->ui32RegSize    = PCI_REG_SIZE;

    /* Return success...*/
    return IMG_SUCCESS;
}
/*!
******************************************************************************

 @Function                SECDEV_GetMemoryInfo

******************************************************************************/
IMG_VOID SECDEV_GetMemoryInfo(
    IMG_VOID **   ppvKmMemory,
    IMG_UINT64 *  pui64MemSize
)
{
#ifdef FPGA_BUS_MASTERING
	*ppvKmMemory  = 0;
	*pui64MemSize = 0;
#else
    *ppvKmMemory  = gsPCIMem[PCI_MEM_BAR].pvKmAddr + PCI_MEM_OFFSET;
    *pui64MemSize = PCI_MEM_SIZE;
#endif
}

/*!
******************************************************************************

 @Function                SECDEV_CpuVirtAddrToCpuPAddr

******************************************************************************/
IMG_PHYSADDR SECDEV_CpuVirtAddrToCpuPAddr(
	IMG_VOID *pvCpuKmAddr
)
{
#ifdef FPGA_BUS_MASTERING
    IMG_PHYSADDR ret = 0;

    if(virt_addr_valid(pvCpuKmAddr))
    {
        /* direct mapping of kernel addresses.
         * this works for kmalloc.
         */
        ret = virt_to_phys(pvCpuKmAddr);
    }
    else
    {
        /* walk the page table.
         * Works for ioremap, vmalloc, and kmalloc(GPF_DMA),
          but not, for some reason, kmalloc(GPF_KERNEL)
         */
        struct page * pg = vmalloc_to_page(pvCpuKmAddr);
        if(pg) {
            ret = page_to_phys(pg);
        }
        else {
            IMG_ASSERT(!"vmalloc_to_page failure");
        }
    }

    return ret;
#else
	int i;
	IMG_UINTPTR uipOffset = 0;

	for(i = 0; i < PCI_MAX_REGIONS; i++)
	{
		if (((IMG_UINTPTR)pvCpuKmAddr >= (IMG_UINTPTR)gsPCIMem[i].pvKmAddr) &&
				((IMG_UINTPTR)pvCpuKmAddr < (IMG_UINTPTR)gsPCIMem[i].pvKmAddr + gsPCIMem[i].size))
		{
			uipOffset = (IMG_UINTPTR)pvCpuKmAddr - (IMG_UINTPTR)gsPCIMem[i].pvKmAddr;
			return gsPCIMem[i].addr + (IMG_PHYSADDR)uipOffset;
		}
	}

	return 0;
#endif
}
