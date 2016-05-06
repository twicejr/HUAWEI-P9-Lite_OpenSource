

#include <linux/module.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/contexthub/motionhub.h>

#include "inputhub_route.h"
#include "inputhub_bridge.h"
/*
#ifndef MHB_LOG_ON
#define MHB_LOG_ON 0
#endif
*/

/*******************************************************************************************
Function:       mhb_read
Description:   read /dev/motionhub
Data Accessed:  no
Data Updated:   no
Input:          struct file *file, char __user *buf, size_t count, loff_t *pos
Output:         no
Return:         length of read data
*******************************************************************************************/
static ssize_t mhb_read(struct file *file, char __user *buf, size_t count, loff_t *pos)
{
    return inputhub_route_read(ROUTE_MOTION_PORT,buf, count);
}

/*******************************************************************************************
Function:       mhb_write
Description:   write to /dev/motionhub, do nothing now
Data Accessed:  no
Data Updated:   no
Input:          struct file *file, const char __user *data, size_t len, loff_t *ppos
Output:         no
Return:         length of write data
*******************************************************************************************/
static ssize_t mhb_write(struct file *file, const char __user *data, size_t len, loff_t *ppos)
{
    hwlog_info("%s need to do...\n", __func__);

    return len;
}

/*******************************************************************************************
Function:       mhb_ioctl
Description:   ioctrl function to /dev/motionhub, do open, close motion, or set interval and attribute to motion
Data Accessed:  no
Data Updated:   no
Input:          struct file *file, unsigned int cmd, unsigned long arg
                   cmd indicates command, arg indicates parameter
Output:         no
Return:         result of ioctrl command, 0 successed, -ENOTTY failed
*******************************************************************************************/
static long mhb_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch(cmd)
    {
        case MHB_IOCTL_MOTION_START:
            break;
        case MHB_IOCTL_MOTION_STOP:
            break;
        case MHB_IOCTL_MOTION_ATTR_START:
            break;
        case MHB_IOCTL_MOTION_ATTR_STOP:
            break;
        default:
            hwlog_err("%s unknown cmd : %d\n", __func__, cmd);
            return -ENOTTY;
    }
    inputhub_route_cmd(ROUTE_MOTION_PORT,cmd,arg);

    return 0;
}

/*******************************************************************************************
Function:       mhb_open
Description:   open to /dev/motionhub, do nothing now
Data Accessed:  no
Data Updated:   no
Input:          struct inode *inode, struct file *file
Output:         no
Return:         result of open
*******************************************************************************************/
static int mhb_open(struct inode *inode, struct file *file)
{
    hwlog_info("%s ok!\n", __func__);
    return 0;
}

/*******************************************************************************************
Function:       mhb_release
Description:   releaseto /dev/motionhub, do nothing now
Data Accessed:  no
Data Updated:   no
Input:          struct inode *inode, struct file *file
Output:         no
Return:         result of release
*******************************************************************************************/
static int mhb_release(struct inode *inode, struct file *file)
{
    hwlog_info("%s ok!\n", __func__);
    return 0;
}

/*******************************************************************************************
Description:   file_operations to motion
*******************************************************************************************/
static const struct file_operations mhb_fops =
{
    .owner      =   THIS_MODULE,
    .llseek     =   no_llseek,
    .read = mhb_read,
    .write      =   mhb_write,
    .unlocked_ioctl =   mhb_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl =   mhb_ioctl,
#endif
    .open       =   mhb_open,
    .release    =   mhb_release,
};

/*******************************************************************************************
Description:   miscdevice to motion
*******************************************************************************************/
static struct miscdevice motionhub_miscdev =
{
    .minor =    MISC_DYNAMIC_MINOR,
    .name =     "motionhub",
    .fops =     &mhb_fops,
};

/*******************************************************************************************
Function:       motionhub_init
Description:   apply kernel buffer, register motionhub_miscdev
Data Accessed:  no
Data Updated:   no
Input:          void
Output:        void
Return:        result of function, 0 successed, else false
*******************************************************************************************/
static int __init motionhub_init(void)
{
    int ret;

    if(is_sensorhub_disabled())
	return -1;    

    hwlog_info("%s start \n", __func__);

    ret = inputhub_route_open(ROUTE_MOTION_PORT);
    if(ret != 0)
    {
        hwlog_err("cannot open inputhub route err=%d\n", ret);
        return ret;
    }

    ret = misc_register(&motionhub_miscdev);
    if(ret != 0)
    {
        hwlog_err("cannot register miscdev err=%d\n", ret);
        inputhub_route_close(ROUTE_MOTION_PORT);
        return ret;
    }

    hwlog_info("%s ok\n", __func__);
    return ret;
}

/*******************************************************************************************
Function:       motionhub_exit
Description:   release kernel buffer, deregister motionhub_miscdev
Data Accessed:  no
Data Updated:   no
Input:          void
Output:        void
Return:        void
*******************************************************************************************/
static void __exit motionhub_exit(void)
{
    int ret;

    inputhub_route_close(ROUTE_MOTION_PORT);
    ret = misc_deregister(&motionhub_miscdev);

    hwlog_info("%s ret=%d\n", __func__, ret);
}

module_init(motionhub_init);
module_exit(motionhub_exit);

MODULE_AUTHOR("MotionHub <smartphone@huawei.com>");
MODULE_DESCRIPTION("MotionHub driver");
MODULE_LICENSE("GPL");
