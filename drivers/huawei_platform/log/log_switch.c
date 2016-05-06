/*
 * drivers/huawei/logswitch/log_switch.c
 *
 * A Logger switch module
 *
 * Copyright (C) 2012 Huawei, Inc.
 *
 * June Yang <june.yang@huawei.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/sched.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/vmalloc.h>
#include <linux/aio.h>
#include <linux/poll.h>
#include <asm/ioctls.h>

#include <uapi/mtd/mtd-abi.h>
#include <linux/hisi/hw_cmdline_parse.h>
#include <huawei_platform/log/log_switch.h>
#include <huawei_platform/log/log_exception.h>
#include <huawei_platform/log/hw_log.h>
#define HWLOG_TAG	log_switch
HWLOG_REGIST();


extern int hisi_nve_direct_access(struct hisi_nve_info_user *info_user);

/* add log switch, control logmian ect logs can write in or not */
static int logctl_flag = 0;	//default 0, switch logger off
static bool logctl_changed = false;
static DECLARE_WAIT_QUEUE_HEAD(logctl_wait_queue);

int get_logctl_flag(void)
{
	return logctl_flag;
}
EXPORT_SYMBOL(get_logctl_flag);

//write logctl value to nv: 0 on success, <0 on fail;
static int write_logctl_to_nv(int val)
{
	struct hisi_nve_info_user user_info;
	int ret = 0;

	memset(&user_info, 0, sizeof(user_info));

	user_info.nv_operation = NV_READ;
	user_info.nv_number = LOGCTL_NV_NUM;
	user_info.valid_size = 1;
	strncpy(user_info.nv_name, LOGCTL_NV_NAME, sizeof(user_info.nv_name));

	ret = hisi_nve_direct_access(&user_info);
	if (ret) {
		hwlog_err("%s: NV '%s' read error %d\n", __func__, user_info.nv_name, ret);
		return LOGCTL_READ_ERR;
	}

	if (user_info.nv_data[0] == val) {
		hwlog_info("%s: NV '%s' no change %d", __func__, user_info.nv_name, user_info.nv_data[0]);
		return LOGCTL_SUCCESS;
	}

	user_info.nv_operation = NV_WRITE;
	user_info.nv_data[0] = val;

	ret = hisi_nve_direct_access(&user_info);
	if (ret) {
		hwlog_err("%s: NV '%s' write %d error %d\n", __func__, user_info.nv_name, val, ret);
		return LOGCTL_WRITE_ERR;
	}
	hwlog_info("%s: NV '%s' write %d ok\n", __func__, user_info.nv_name, val);

	//status changed
	logctl_changed = true;

	return LOGCTL_SUCCESS;
}

static DEFINE_MUTEX(logctl_lock);

static ssize_t log_switch_read(struct file *file, char __user *buf, size_t count, loff_t *pos)
{
	int ret = 0;
	mutex_lock(&logctl_lock);
	ret = snprintf(buf, PAGE_SIZE, "%d\n", logctl_flag);
	if (ret > 0) {
		if(*pos > 0)
			ret = 0;
		else
			*pos += ret;
	}
	mutex_unlock(&logctl_lock);
	return ret;
}

static ssize_t log_switch_write(struct file * file, const char __user * buf, size_t count, loff_t * pos)
{
	int val = 0;
	int ret = 0;
	char kbuff[3] = {0};

	if(copy_from_user( kbuff, buf, 2))
	{
		hwlog_err("copy buf from user error\n");
		return -EINVAL;
	}

	if (sscanf(kbuff, "%1d", &val) != 1) {
		hwlog_err("%s: invalid args %lu '%s'!", __func__, count, kbuff);
		return -EINVAL;
	}

	hwlog_debug("%s: args %lu '%s', val=%d\n", __func__, count, kbuff, val);

	mutex_lock(&logctl_lock);
	logctl_flag = val;
	ret = write_logctl_to_nv(val);
	mutex_unlock(&logctl_lock);

	if (ret < 0) {
		hwlog_err("%s: write nv %d error %d", __func__, val, ret);
		return -EIO;
	}

	if(logctl_changed){
		wake_up_interruptible(&logctl_wait_queue);
	}

	return count;
}

static unsigned int log_switch_poll(struct file *filp, poll_table *wait)
{
	unsigned int mask = 0;

	poll_wait(filp, &logctl_wait_queue, wait);
	if(logctl_changed){
		logctl_changed = false;
		mask |= POLLIN | POLLRDNORM;
	}

	return mask;
}


static long log_switch_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{

	long ret = -EINVAL;

	mutex_lock(&logctl_lock);
	switch (cmd) {
	case LOGCTL_GET_STATE:
		ret = logctl_flag;
		break;
	default:
		mutex_unlock(&logctl_lock);
		return -ENOTTY;
	}
	mutex_unlock(&logctl_lock);

	return ret;
}


static const struct file_operations log_switch_fops = {
	.owner = THIS_MODULE,
	.read = log_switch_read,
	.write = log_switch_write,
	.poll = log_switch_poll,
	.unlocked_ioctl = log_switch_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = log_switch_ioctl,
#endif
};

static struct miscdevice log_switch_misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "hwlog_switch",
	.fops = &log_switch_fops,
	.parent = NULL,
};

static int __init logswitch_init(void)
{
	int ret=0;

	//get logctl_flag from cmdline
	logctl_flag = get_logctl_value();

	//used for logd to get logctl init state
	logctl_changed = true;
	hwlog_info("%s: logctl_value=%d,logctl_changed = %d\n", \
		        __func__, logctl_flag,logctl_changed);

	ret = misc_register(&log_switch_misc_dev);
	if (unlikely(ret)) {
		hwlog_err("%s: register misc device for '%s' failed %d!\n",
				__func__, log_switch_misc_dev.name, ret);
		goto out;
	}

out:
	return ret;
}

static void __exit logswitch_exit(void)
{
	misc_deregister(&log_switch_misc_dev);
}


device_initcall(logswitch_init);
module_exit(logswitch_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("June Yang, <june.yang@huawei.com>");
MODULE_DESCRIPTION("Huawei Log switch");
