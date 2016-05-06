#include <linux/kthread.h>
#include <linux/sched/rt.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/freezer.h>
#include <linux/input.h>
#include <linux/i2c.h>
#include <linux/reboot.h>
#include <linux/suspend.h>
#include <linux/fb.h>
#include <linux/timer.h>
#include <linux/rtc.h>
#include <linux/wakelock.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/syscalls.h>
#include <linux/async.h>
#include "recovery_misc.h"

#define HWLOG_TAG    MISC_RECOVERY
HWLOG_REGIST();

#define WR 1
#define RE 0

int operate_node(const char *path,char* data,unsigned int len,unsigned int write_read)
{
    if(NULL == path || NULL == data )
    {
        MISC_LOG_ERR("NULL input\n");
        return -1;
    }
    struct file *fp;
    unsigned long old_fs;
    fp = filp_open(path, O_RDWR,0644);
    if (IS_ERR(fp))
    {
        MISC_LOG_INFO("open misc node fail\n");
        return -1;
    }
    old_fs = get_fs();
    set_fs(KERNEL_DS);
    if(WR == write_read)
    {
        vfs_write(fp, data, len, &(fp->f_pos));
        vfs_fsync(fp,0);
    }
    else
    {
        vfs_read(fp, data, len, &(fp->f_pos));
    }
    MISC_LOG_INFO("writing has been done\n");
    filp_close(fp, NULL);
    set_fs(old_fs);
    return 0;
}

static int reboot_recovery_misc_write()
{
    misc_message_type misc_message;
    memset(&misc_message, 0, sizeof(misc_message_type));
    strncpy(misc_message.command, MISC_BOOT_RECOVERY_STR, sizeof(misc_message.command));
    if(0 == operate_node(MISC_NODE_PATH,(char *)&misc_message,sizeof(misc_message_type),WR))
    {
        MISC_LOG_INFO("write boot-recovery into misc success\n");
        return 0;
    }
    else
    {
        MISC_LOG_ERR("write boot-recovery into misc fail\n");
        return -1;
    }
}

static int reboot_recovery_misc_write_check()
{
    misc_message_type misc_message;
    memset(&misc_message, 0, sizeof(misc_message_type));
    if (0 == operate_node(MISC_NODE_PATH,(char *)&misc_message,sizeof(misc_message_type),RE))
    {
        MISC_LOG_INFO("misc command info:%s \n",misc_message.command);
    }
    return 0;
}
static int recovery_notify(struct notifier_block *this, unsigned long code,
        void *buf)
{
    if(NULL == buf)
    {
        MISC_LOG_INFO("no need to handle \n");
        return 0;
    }
    if(0 == strncmp("recovery", buf, strlen("recovery")))
    {
        MISC_LOG_INFO("reboot recovery detected\n");
        if(0 == reboot_recovery_misc_write())
        {
            MISC_LOG_INFO("write to misc success\n");
        }
    }
    else
    {
        MISC_LOG_INFO("no need to write boot-recovery into misc\n");
    }
    return 0;
}

static struct notifier_block recovery_notifier = {
        .notifier_call = recovery_notify,
};
static int __init misc_recovery_init(void)
{
    int ret;
    ret = register_reboot_notifier(&recovery_notifier);
    if (ret) {
           MISC_LOG_ERR("cannot register reboot notifier (err=%d)\n", ret);
    }
    return 0;
}
module_init(misc_recovery_init);

