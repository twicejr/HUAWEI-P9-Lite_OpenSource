/**
    @copyright: Huawei Technologies Co., Ltd. 2012-2013. All rights reserved.

    @file: srecorder_dev.c

    @brief:  Register a char device to dump log

    @version: 1.0 

    @author: QiDechun ID: 216641

    @date: 2013-01-30

    @history:
*/

/*----includes-----------------------------------------------------------------------*/

#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/vmalloc.h>
#include <linux/kthread.h>
#include <linux/version.h>

#include "../include/srecorder_common.h"
#include "../include/srecorder_dev.h"


/*----local macroes------------------------------------------------------------------*/

#define SRECORDER_LOG_OFFSET(a, b) (a)


/*----local prototypes----------------------------------------------------------------*/

typedef struct __srecorder_log_info
{
    char *buf; /* SRecorder's reserved mem start addr */
    char *log_buf; /* log temp buffer start addr */
    int log_len; /* length of the log */
    int buf_size; /* SRecorder's reserved buffer size */
    int read_pos; /* SRecorder read index */
} srecorder_log_info, *psrecorder_log_info;


/*----local function prototypes---------------------------------------------------------*/

static ssize_t srecorder_read(struct file *file, char __user *buf, size_t count, loff_t *pos);
static ssize_t srecorder_write(struct file *file, const char __user *data, size_t len, loff_t *ppos);
static long srecorder_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static loff_t srecorder_llseek(struct file *file, loff_t offset, int origin);
static int srecorder_open(struct inode *inode, struct file *file);
static int srecorder_release(struct inode *inode, struct file *file);
static inline void srecorder_log_read_clean(void);
static int srecorder_log_read_monitor(void *arg);


/*----local variables------------------------------------------------------------------*/

static DEFINE_MUTEX(s_srecorder_mutex);

/*
* Kernel Interfaces
*/
static const struct file_operations s_srecorder_fops = 
{
    .owner		= THIS_MODULE,
    .llseek		= srecorder_llseek,
    .read         = srecorder_read,
    .write		= srecorder_write,
    .unlocked_ioctl	= srecorder_ioctl,
    .open		= srecorder_open,
    .release	= srecorder_release,
};

static struct miscdevice s_srecorder_miscdev = 
{
    .minor		= MISC_DYNAMIC_MINOR,
    .name		= "srecorder",
    .fops		= &s_srecorder_fops,
};

static srecorder_log_info s_srecorder_log_info;
static volatile bool s_dev_online = true;
static DEFINE_SPINLOCK(s_read_log_lock);


/*----global variables-----------------------------------------------------------------*/


/*----function definitions--------------------------------------------------------------*/

/**
    @function: static loff_t srecorder_llseek(struct file *file, loff_t offset, int origin)
    @brief: Move read/write index in the SRecorder char device

    @param: file
    @param: offset
    @param: origin

    @return: 0 - success; others - failed

    @note: 
*/
static loff_t srecorder_llseek(struct file *file, loff_t offset, int origin)
{
    loff_t ret = -1;
    
    switch (origin)
    {
    case SEEK_SET:
        {
            if ((offset >= 0) && (offset <= s_srecorder_log_info.log_len))
            {
                s_srecorder_log_info.read_pos = SRECORDER_LOG_OFFSET(s_srecorder_log_info.read_pos + offset, s_srecorder_log_info.log_len);
                return 0;
            }
            
            break;
        }
    case SEEK_CUR:
        {
            if ((offset >= -s_srecorder_log_info.read_pos) && ((offset + s_srecorder_log_info.read_pos) <= s_srecorder_log_info.log_len))
            {
                s_srecorder_log_info.read_pos = SRECORDER_LOG_OFFSET(s_srecorder_log_info.read_pos + offset, s_srecorder_log_info.log_len);
                return 0;
            }
            
            break;
        }
    case SEEK_END:
        {
            if ((offset >= -s_srecorder_log_info.log_len) && (offset <= 0))
            {
                s_srecorder_log_info.read_pos = SRECORDER_LOG_OFFSET(s_srecorder_log_info.read_pos + offset, s_srecorder_log_info.log_len);
                return 0;
            }
            
            break;
        }
    default :
        {
            return -EINVAL;
        }
    }

    return ret;
}


/**
    @function: static ssize_t srecorder_write(struct file *file, const char __user *data, size_t len, loff_t *ppos)
    @brief: Write data to the SRecorder char device

    @param: file
    @param: data
    @param: len
    @param: ppos

    @return: 0 - success; others - failed

    @note: 
*/
static ssize_t srecorder_write(struct file *file, const char __user *data, size_t len, loff_t *ppos)
{
    char c = 0;
    
    if (unlikely(NULL == data))
    {
        return -EINVAL;
    }
    
    if (get_user(c, data))
    {
        return -1;
    }

    switch (c)
    {
    case 'c': /* clean reserved buffer */
    case 'C': /* clean reserved buffer */
        {
            srecorder_write_reserved_mem_header(false, false, INVALID_SRECORDER_MAGIC_NUM, 0);

            /* do clean */
            spin_lock(&s_read_log_lock);
            srecorder_log_read_clean();
            spin_unlock(&s_read_log_lock);

            return 0;
        }
        break;
    case 'e': /* enable SRecorder */
    case 'E': /* enable SRecorder */
        {
            srecorder_enable(); /* User enable SRecorder */
            SRECORDER_PRINTK("^_^_^ Enable SRecorder %s!\n", (srecorder_has_been_enabled()) ? ("successfully") : ("failed"));
            
            return 0;
        }
        break;
    default:
        {
            break;
        }
    }
    
    return -1;
}


/**
    @function: static long srecorder_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
    @brief: Ctrl the SRecorder char device

    @param: file
    @param: cmd
    @param: arg

    @return: 0 - success; others - failed

    @note: 
*/
static long srecorder_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int rc = 0;
    unsigned long __user *p = (unsigned long __user *)arg;
    srecorder_reserved_mem_info_t *pmem_info = srecorder_get_reserved_mem_info();
    srecorder_reserved_mem_header_t *pmem_header = (srecorder_reserved_mem_header_t *)srecorder_get_reserved_mem_addr();
    
    if ((SRIOC_SET_DUMP_ENABLE_BIT == cmd) || (SRIOC_CLR_DUMP_ENABLE_BIT == cmd))
    {
        if ((int)arg > LOG_TYPE_MAX)
        {
            return -EINVAL;
        }
    }
    
    switch (cmd)
    {
    case SRIOC_SET_DUMP_ENABLE_BIT:
        {
            srecorder_set_dump_enable_bit(arg);
            break;
        }
    case SRIOC_CLR_DUMP_ENABLE_BIT:
        {
            srecorder_clear_dump_enable_bit(arg);
            break;
        }
    case SRIOC_GET_DUMP_ENABLE_BITS:
        {
            spin_lock(&(pmem_info->lock));
            rc = copy_to_user(p, pmem_header->dump_ctrl_bits, sizeof(pmem_header->dump_ctrl_bits));
            spin_unlock(&(pmem_info->lock));
            break;
        }
    case SRIOC_SET_DUMP_ENABLE_BITS:
        {
            spin_lock(&(pmem_info->lock));
            rc = copy_from_user(pmem_header->dump_ctrl_bits, p, sizeof(pmem_header->dump_ctrl_bits));
            spin_unlock(&(pmem_info->lock));
            break;
        }
    case SRIOC_CLEAN:
        {
            srecorder_write_reserved_mem_header(false, false, INVALID_SRECORDER_MAGIC_NUM, 0);

            /* do clean */
            spin_lock(&s_read_log_lock);
            srecorder_log_read_clean();
            spin_unlock(&s_read_log_lock);
            break;
        }
    case SRIOC_ENABLE:
        {
            srecorder_enable(); /* User enable SRecorder */
            SRECORDER_PRINTK("^_^ Enable SRecorder %s!\n", (srecorder_has_been_enabled()) ? ("successfully") : ("failed"));
            break;
        }
    case SRIOC_DISABLE:
        {
            srecorder_disable(); /* User enable SRecorder */
            SRECORDER_PRINTK("^_^ Disable SRecorder %s!\n", (srecorder_has_been_enabled()) ? ("failed") : ("successfully"));
            break;
        }
    default:
        return -ENOTTY; 
    }
    
    return rc;
}


/**
    @function: static int srecorder_release(struct inode *inode, struct file *file)
    @brief: Close the SRecorder char device

    @param: inode
    @param: file

    @return: 0 - success; -1- failed

    @note: 
*/
static int srecorder_release(struct inode *inode, struct file *file)
{
    return 0;
}


/**
    @function: static ssize_t srecorder_read(struct file *file, char __user *buf, size_t count, loff_t *pos)
    @brief: Read data from the SRecorder char device

    @param: file
    @param: buf
    @param: count
    @param: pos

    @return: 0 - success; -1- failed

    @note: 
*/
static ssize_t srecorder_read(struct file *file, char __user *buf, size_t count, loff_t *pos)
{
    size_t len = 0;

    if (unlikely(NULL == buf))
    {
        SRECORDER_PRINTK("File: %s - Line: %d, Invalid parameter!\n", __FILE__, __LINE__);
        return -EINVAL;
    }
    
    /* This is very important, or memory overflow may occur */
    if (unlikely(s_srecorder_log_info.read_pos >= s_srecorder_log_info.log_len))
    {
        SRECORDER_PRINTK("File: %s - Line: %d, read_pos = %d log_len = %d No data left!\n", 
            __FILE__, __LINE__, s_srecorder_log_info.read_pos, s_srecorder_log_info.log_len);
        return -EFAULT; /* Bad address */
    }
    
    spin_lock(&s_read_log_lock);
    if (!s_dev_online) /* device is offline */
    {
        SRECORDER_PRINTK("File: %s - Line: %d, /dev/srecorder/ is off line!\n", __FILE__, __LINE__);
        spin_unlock(&s_read_log_lock);
        return -ENODEV; /* No such device or address */
    }
    
    len = MIN(count, s_srecorder_log_info.log_len - s_srecorder_log_info.read_pos);
    if (NULL == s_srecorder_log_info.log_buf) /* There is no log to be dumped */
    {
        SRECORDER_PRINTK("File: %s - Line: %d, SRecorder's temp buf is NULL!\n", __FILE__, __LINE__);
        spin_unlock(&s_read_log_lock);
        return -EFAULT; /* Bad address */
    }
    
    if (copy_to_user(buf, s_srecorder_log_info.log_buf + s_srecorder_log_info.read_pos, len))
    {
        SRECORDER_PRINTK("File: %s - Line: %d, copy data failed!\n", __FILE__, __LINE__);
        spin_unlock(&s_read_log_lock);
        return -EFAULT;
    }
    spin_unlock(&s_read_log_lock);
    s_srecorder_log_info.read_pos = SRECORDER_LOG_OFFSET(s_srecorder_log_info.read_pos + len, s_srecorder_log_info.log_len);
    
    return len;
}


/**
    @function: static int srecorder_open(struct inode *inode, struct file *file)
    @brief: open the SRecorder char device

    @param: inode
    @param: file

    @return: 0 - success; -1- failed

    @note: 
*/
static int srecorder_open(struct inode *inode, struct file *file)
{
    int ret = -1;

#if 0
    ret = nonseekable_open(inode, file);
#else
    ret = generic_file_open(inode, file);
#endif

    return ret;
}


/**
    @function: static inline void srecorder_log_read_clean(void)
    @brief: unrigister the SRecorder char dev and  release teh temp buffer

    @param: none

    @return: none

    @note: 
*/
static inline void srecorder_log_read_clean(void)
{
    if (NULL != s_srecorder_log_info.log_buf)
    {
        vfree(s_srecorder_log_info.log_buf);
        s_srecorder_log_info.log_buf = NULL;
    }
}


/**
    @function: static int srecorder_log_read_monitor(void *arg)
    @brief: log read monitor

    @param: arg kernel thread argument

    @return: 0 - success; others - failed

    @note: 
*/
static int srecorder_log_read_monitor(void *arg)
{
    current->flags |= PF_NOFREEZE;
    msleep((unsigned int)SRECORDER_TIMER_EXPIRE_PERIOD 
        * (unsigned int)60000); /* 5 minitues */
    spin_lock(&s_read_log_lock);
    srecorder_log_read_clean();
    spin_unlock(&s_read_log_lock);
    srecorder_exit_dev();
    s_dev_online = false;
    return 0;
}


/**
    @function: int srecorder_init_snprintf(srecorder_module_init_params_t *pinit_params)
    @brief: initialise this module

    @param: pinit_params initialize parameters

    @return: 0 - successfully; -1- failed

    @note: 
*/
int srecorder_init_dev(srecorder_module_init_params_t *pinit_params)
{
    int ret = -1;
    
    memset(&s_srecorder_log_info, 0, sizeof(srecorder_log_info));
    s_srecorder_log_info.buf = pinit_params->srecorder_reserved_mem_start_addr;
    s_srecorder_log_info.buf_size = pinit_params->srecorder_reserved_mem_size;
    s_srecorder_log_info.log_buf = pinit_params->srecorder_log_temp_buf;
    s_srecorder_log_info.log_len = pinit_params->srecorder_log_len;
    s_srecorder_log_info.read_pos = 0;

    ret = misc_register(&s_srecorder_miscdev);
    if (0 != ret)
    {
        SRECORDER_PRINTK("Cannot register miscdev on minor = %d (err = %d)\n", MISC_DYNAMIC_MINOR, ret);
    }
    else
    {
        SRECORDER_PRINTK("^_^_^ Create /dev/srecorder successfully!\n ");
    }
    
    /* this kernel thread will monitor if user will dump the log in time or not */
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 4, 0))
    kernel_thread(srecorder_log_read_monitor, NULL, CLONE_FS | CLONE_SIGHAND);
#else
    kthread_run(srecorder_log_read_monitor, NULL, "srecorder_log_read_monitor");
#endif
    
    return ret;
}


/**
    @function: void srecorder_exit_snprintf(void)
    @brief: exit this module

    @param: none

    @return: none

    @note: 
*/
void srecorder_exit_dev(void)
{
    int rc = misc_deregister(&s_srecorder_miscdev);

    SRECORDER_PRINTK("~_~_~ Unregister /dev/srecorder %s!\n", (0 == rc) ? ("successfully") : ("failed!"));
}

