/*
 *  drivers/misc/inputhub/sensorhub_channel.c
 *  Sensor Hub Channel driver
 *
 *  Copyright (C) 2012 Huawei, Inc.
 *  Author: qindiwen <qindiwen@huawei.com>
 *
 */

#include <linux/module.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <huawei_platform/inputhub/sensorhub.h>

#include "inputhub_route.h"

int first_start_flag;
extern int read_gsensor_offset_from_nv(void);
extern int write_gsensor_offset_to_nv(int* temp);
/*******************************************************************************************
Function:       shb_read
Description:    定义/dev/sensorhub节点的读函数，从kernel的事件缓冲区中读数据
Data Accessed:  无
Data Updated:   无
Input:          struct file *file, char __user *buf, size_t count, loff_t *pos
Output:         无
Return:         实际读取数据的长度
*******************************************************************************************/
static ssize_t shb_read(struct file *file, char __user *buf, size_t count,
              loff_t *pos)
{
#ifdef LOG_SENSORHUB_CHANNEL
    hwlog_info( "shb_read \n");
#endif

    return inputhub_route_read(ROUTE_SHB_PORT,buf, count);
}

static ssize_t shb_write(struct file *file, const char __user *data,
                        size_t len, loff_t *ppos)
{
    char cmdbuf[DEV_SENSORHUB_MAX_WRITE_SIZE];

    if (len <= DEV_SENSORHUB_MAX_WRITE_SIZE) {
        if (copy_from_user(cmdbuf, data, len)) {
            hwlog_info( "!!!!!!!!!!!!!!!copy_from_user failed!!!!!!!!!!!!!!!!!\n");
            return -EFAULT;
        }
        parse_write_cmds_from_devsensorhub((const struct pkg_from_devsensorhub *)cmdbuf, len);
    } else {
        hwlog_info( "shb_write invalid len:%lu, the max length is %d bytes\n", len, DEV_SENSORHUB_MAX_WRITE_SIZE);
    }

    return len;
}
static void get_acc_calibrate_data(void)
{
    int ret = 0;
    if (0 == first_start_flag)
    {
        ret=read_gsensor_offset_from_nv();
        if(ret) hwlog_err( "get_acc_calibrate_data read from nv fail, ret=%d", ret);
        else
        {
            hwlog_info("read nv success\n");
        }
    }
}

extern int read_mag_calibrate_data_from_nv(void);
static void get_mag_calibrate_data(void)
{
    int ret = 0;
    static int mag_first_start_flag = 0;
    if (0 == mag_first_start_flag)
    {
        ret = read_mag_calibrate_data_from_nv();
        if (ret) {
            hwlog_err("%s read mag data from nv or send to iom3 failed, ret=%d\n", __func__, ret);
        } else {
            hwlog_info("%s read mag data from nv and send to iom3 success\n", __func__);
        }
        mag_first_start_flag = 1;
    }
}

extern int read_cap_prox_calibrate_data_from_nv(void);
static void get_cap_prox_calibrate_data(void)
{
    int ret = 0;
    static int cap_prox_first_start_flag = 0;
    if (0 == cap_prox_first_start_flag)
    {
        ret = read_cap_prox_calibrate_data_from_nv();
        if (ret) {
            hwlog_err("%s read cap_prox data from nv or send to iom3 failed, ret=%d\n", __func__, ret);
        } else {
            hwlog_info("%s read cap_prox data from nv and send to iom3 success\n", __func__);
        }
        cap_prox_first_start_flag = 1;
    }
}
/*******************************************************************************************
Function:       shb_ioctl
Description:    定义/dev/sensorhub节点的ioctl函数，主要用于设置传感器命令和获取MCU是否存在
Data Accessed:  无
Data Updated:   无
Input:          struct file *file, unsigned int cmd, unsigned long arg，cmd是命令码，arg是命令跟的参数
Output:         无
Return:         成功或者失败信息
*******************************************************************************************/
static long shb_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    void __user *argp = (void __user *)arg;
    /*begin huangwen 20120706*/
    int sensorMcuMode;
    /*end huangwen 20120706*/

    
    switch (cmd) {
    case SHB_IOCTL_APP_ENABLE_SENSOR:
        get_acc_calibrate_data();
        get_mag_calibrate_data();
        get_cap_prox_calibrate_data();
        break;
    case SHB_IOCTL_APP_DISABLE_SENSOR:
        break;
    /*begin huangwen 20120706*/
    case SHB_IOCTL_APP_GET_SENSOR_MCU_MODE:
        sensorMcuMode = getSensorMcuMode();
        hwlog_info( "isSensorMcuMode [%d]\n", sensorMcuMode );
        if (copy_to_user(argp, &sensorMcuMode, sizeof(sensorMcuMode)))
            return -EFAULT;
        return 0;
        break;
    /*end huangwen 20120706*/
    case SHB_IOCTL_APP_DELAY_ACCEL:
    case SHB_IOCTL_APP_DELAY_LIGHT:
    case SHB_IOCTL_APP_DELAY_PROXI:
    case SHB_IOCTL_APP_DELAY_GYRO:
    case SHB_IOCTL_APP_DELAY_GRAVITY:
    case SHB_IOCTL_APP_DELAY_MAGNETIC:
    case SHB_IOCTL_APP_DELAY_ROTATESCREEN:
    case SHB_IOCTL_APP_DELAY_LINEARACCELERATE:
    case SHB_IOCTL_APP_DELAY_ORIENTATION:
    case SHB_IOCTL_APP_DELAY_ROTATEVECTOR:
    case SHB_IOCTL_APP_DELAY_PRESSURE:
    case SHB_IOCTL_APP_DELAY_TEMPERATURE:
    case SHB_IOCTL_APP_DELAY_RELATIVE_HUMIDITY:
    case SHB_IOCTL_APP_DELAY_AMBIENT_TEMPERATURE:
    case SHB_IOCTL_APP_DELAY_MCU_LABC:
    case SHB_IOCTL_APP_DELAY_HALL:
    case SHB_IOCTL_APP_DELAY_MAGNETIC_FIELD_UNCALIBRATED:
    case SHB_IOCTL_APP_DELAY_GAME_ROTATION_VECTOR:
    case SHB_IOCTL_APP_DELAY_GYROSCOPE_UNCALIBRATED:
    case SHB_IOCTL_APP_DELAY_SIGNIFICANT_MOTION:
    case SHB_IOCTL_APP_DELAY_STEP_DETECTOR:
    case SHB_IOCTL_APP_DELAY_STEP_COUNTER:
    case SHB_IOCTL_APP_DELAY_GEOMAGNETIC_ROTATION_VECTOR:
    case SHB_IOCTL_APP_DELAY_AIRPRESS:
    case SHB_IOCTL_APP_DELAY_HANDPRESS:
    case SHB_IOCTL_APP_DELAY_CAP_PROX:
        break;
    default:
        hwlog_err("shb_ioctl unknown cmd : %d\n", cmd);
        return -ENOTTY;
    }
    return inputhub_route_cmd(ROUTE_SHB_PORT,cmd,arg);

}

/*******************************************************************************************
Function:       shb_open
Description:    定义/dev/sensorhub节点的open函数，暂未实现实质功能
Data Accessed:  无
Data Updated:   无
Input:          struct inode *inode, struct file *file
Output:         无
Return:         成功或者失败信息
*******************************************************************************************/
static int shb_open(struct inode *inode, struct file *file)
{
    /* /dev/sensorhub can only be opened once */
    //if (test_and_set_bit(0, &shb_is_open))
    //    return -EBUSY;
    hwlog_info( "shb_open \n");
    return 0;
}

/*******************************************************************************************
Function:       shb_release
Description:    定义/dev/sensorhub节点的release函数，暂未实现实质功能
Data Accessed:  无
Data Updated:   无
Input:          struct inode *inode, struct file *file
Output:         无
Return:         成功或者失败信息
*******************************************************************************************/
static int shb_release(struct inode *inode, struct file *file)
{
    hwlog_info( "shb_release \n");
    //clear_bit(0, &shb_is_open);
    return 0;
}

//--------------------------------------
static const struct file_operations shb_fops = {
    .owner      =   THIS_MODULE,
    .llseek     =   no_llseek,
    .read = shb_read,
    .write      =   shb_write,
    .unlocked_ioctl =   shb_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl =   shb_ioctl,
#endif
    .open       =   shb_open,
    .release    =   shb_release,
};

static struct miscdevice senorhub_miscdev = {
    .minor =    MISC_DYNAMIC_MINOR,
    .name =     "sensorhub",
    .fops =     &shb_fops,
};

/*******************************************************************************************
Function:       sensorhub_init
Description:    申请kernel缓冲区并初始化读写指针，注册msic设备
Data Accessed:  无
Data Updated:   无
Input:          无
Output:         无
Return:         成功或者失败信息
*******************************************************************************************/
int __init sensorhub_init(void)
{
    int ret;

    ret = inputhub_route_open(ROUTE_SHB_PORT);
    if (ret != 0) {
        hwlog_err( "cannot open inputhub route err=%d\n", ret);
        return ret;
    }

    ret = misc_register(&senorhub_miscdev);
    if (ret != 0) {
        inputhub_route_close(ROUTE_SHB_PORT);
        hwlog_err( "cannot register miscdev err=%d\n", ret);
        return ret;
    }

    hwlog_info( "sensorhub_init ok\n");

    return 0;
}

/*******************************************************************************************
Function:       sensorhub_exit
Description:    释放kernel缓冲区并初始化读写指针，注销msic设备
Data Accessed:  无
Data Updated:   无
Input:          无
Output:         无
Return:         成功或者失败信息
*******************************************************************************************/
void __exit sensorhub_exit(void)
{
    int ret;

    inputhub_route_close(ROUTE_SHB_PORT);
    ret = misc_deregister(&senorhub_miscdev);

    hwlog_info( "sensorhub_exit ret=%d\n", ret);
}

module_init(sensorhub_init);
module_exit(sensorhub_exit);

MODULE_AUTHOR("SensorHub <smartphone@huawei.com>");
MODULE_DESCRIPTION("SensorHub driver");
MODULE_LICENSE("GPL");
