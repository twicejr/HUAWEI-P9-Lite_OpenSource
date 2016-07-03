/*
 * viatel_cbp_power.c
 *
 * VIA CBP driver for Linux
 *
 * Copyright (C) 2009 VIA TELECOM Corporation, Inc.
 * Author: VIA TELECOM Corporation, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.  */
#include <linux/ctype.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/irq.h>
#include <linux/wakelock.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/completion.h>
#include <linux/workqueue.h>
#include <linux/io.h>
#include <linux/wait.h>
#include <linux/random.h>
#include <linux/time.h>
#include <linux/compiler.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/pinctrl/consumer.h>
#include <linux/skbuff.h>
#include "viatel.h"
#include "core.h"
#include <huawei_platform/log/log_exception.h>
#include <linux/rtc.h>
#include "power.h"
#include "ext_modem.h"

/*define viacbp82d power name, must be same with dts*/
#define VIACBP82D_POWER_DRIVER_NAME    "huawei,viacbp82d-power"


/* ioctl for vomodem, which must be same as viatelutils.h  */
#define VMDM_IOCTL_RESET    _IO( 'v', 0x01)
#define VMDM_IOCTL_POWER    _IOW('v', 0x02, int)
#define VMDM_IOCTL_CRL      _IOW('v', 0x03, int)
#define VMDM_IOCTL_DIE      _IO( 'v', 0x04)
#define VMDM_IOCTL_WAKE     _IO( 'v', 0x05)

typedef enum MODEM_CONTROL {
    POWER_SET_DEBUGOFF = 0,
    POWER_SET_DEBUGON,
    POWER_SET_OFF,
    POWER_SET_ON,
    MODEM_CTRL_RESET,
    MODEM_CTRL_DIE,     //5
    MODEM_CTRL_WAKE_LOCK,
    MODEM_CTRL_WAKE_LOCK_RELEASE,    //7
    MODEM_CONTROL_MAX,
}MODEM_CONTROL_T;

static const char* const via_state_str[] =
{
    "MODEM_STATE_OFF",
    "MODEM_STATE_POWER",
    "MODEM_STATE_READY",
    "MODEM_STATE_INVALID",
};

typedef enum ENUM_MODEM_STATE
{
    MODEM_STATE_OFF = 0,
    MODEM_STATE_POWER,
    MODEM_STATE_READY,
    MODEM_STATE_INVALID,
} ENUM_MODEM_STATE_T;

int cbp_rst_gpio = 0;
int cbp_pwr_en_gpio = 0;
int cbp_rst_ind_gpio = 0;
unsigned int cbp_reset_ind_connect_to_codec = 0;//1: connected to;  0: not connected to
int cbp_sim_switch_gpio = 0;
int cbp_backup_gpio = 0;
struct timer_list cbp_backup_timer;
static atomic_t cbp_backup_timer_started = ATOMIC_INIT(0);

static int via_curr_power_state;

static int via_modem_state = MODEM_STATE_OFF;

#define MODEM_VIACBP82D   "viacbp82d"
#define MODEM_DEVICE_BOOT(type)   type"_boot"

/* event for vmodem, which must be same as viatelutilis.h */
enum ASC_USERSPACE_NOTIFIER_CODE
{
    ASC_USER_USB_WAKE =  (__SI_POLL | 100),
    ASC_USER_USB_SLEEP,
    ASC_USER_UART_WAKE,
    ASC_USER_UART_SLEEP,
    ASC_USER_SDIO_WAKE,
    ASC_USER_SDIO_SLEEP,
    ASC_USER_MDM_POWER_ON = (__SI_POLL | 200),
    ASC_USER_MDM_POWER_OFF,
    ASC_USER_MDM_RESET_ON,
    ASC_USER_MDM_RESET_OFF,
    ASC_USER_MDM_ERR = (__SI_POLL | 300),
    ASC_USER_MDM_ERR_ENHANCE
};

#define MDM_RST_LOCK_TIME   (120)
#define MDM_RST_HOLD_DELAY  (100) //ms
#define MDM_PWR_HOLD_DELAY  (500) //ms
#define WAIT_CBP_BACKUP_RAMDUMP_RST_TIME  (10000) //ms
#define CBP_BACKUP_GPIO_SELECT_HOLD_TIME  (3000) //ms
#define CBP_BACKUP_GPIO_DELECT_DELAY  (150) //ms
#define QUEUE_NUM   8

#define VIA_RESETINFO_WR_APPEND  (1)
#define VIA_RESETINFO_WR_COVER   (0)
#define VIA_RESETINFO_WR_CLEAR   "0"

struct viatel_modem_data {
    struct platform_device *via_pdev;
    struct fasync_struct *fasync;
    struct raw_notifier_head ntf;
    struct notifier_block rst_ntf;
    struct wake_lock wlock;
    struct work_struct work;
    struct work_struct via_uevent_work;
    char* envp[QUEUE_NUM][2];
    unsigned char head;
    unsigned char tail;
    spinlock_t lock;
    atomic_t count;
    unsigned long ntf_flags;
};

static struct viatel_modem_data* vmdata;
extern void oem_reset_modem(void);
extern int modem_on_off_ctrl_chan(unsigned char on);
extern void gpio_irq_cbp_rst_ind(int level);
static void cbp_backup_check_ramdump_timer(unsigned long data);

static int cbp_need_apr = 0;
static char time_buf[16] ={0};
static char g_cbp_resetinfo[MDM_RESETINFO_SIZE] = {0};
static struct mutex g_cbp_resetinfo_lock;

static struct platform_device viacbp82d_3rd_modem_info =
{
    .name = MODEM_DEVICE_BOOT(MODEM_VIACBP82D),
    .id = -1,
};

static int via_resetinfo_read(void *buf, int size)
{
    int real_size = -1;
    if(!buf) {
        hwlog_err("%s %d: the pointer of buf is null\n", __func__, __LINE__);
        return -1;
    }

    mutex_lock(&g_cbp_resetinfo_lock);
    real_size = snprintf(buf, size, "%s", g_cbp_resetinfo);
    mutex_unlock(&g_cbp_resetinfo_lock);
    return real_size;
}

/*
if append_flag == 1, write data into g_cbp_resetinfo by append,
else if append_flag == 0 by cover
*/
static int via_resetinfo_write(void *buf, int append_flag)
{
    int real_size = -1;
    if(!buf) {
        hwlog_err("%s %d: the pointer of buf is null\n", __func__, __LINE__);
        return -1;
    }

    hwlog_info("%s %d: start write resetinfo to g_cbp_resetinfo\n",__func__, __LINE__);
    mutex_lock(&g_cbp_resetinfo_lock);
    if(VIA_RESETINFO_WR_COVER == append_flag) {
        memset(g_cbp_resetinfo, 0, sizeof(g_cbp_resetinfo));
        if(strcmp(buf, VIA_RESETINFO_WR_CLEAR)) {
            real_size = snprintf(g_cbp_resetinfo, MDM_RESETINFO_SIZE, "%s", (char *)buf);
        }
    }else if(VIA_RESETINFO_WR_APPEND == append_flag) {
        real_size = snprintf(g_cbp_resetinfo+strlen(g_cbp_resetinfo), MDM_RESETINFO_SIZE-strlen(g_cbp_resetinfo), "%s", (char *)buf);
    }else {
        hwlog_err("%s %d: unknow append_flag!\n", __func__, __LINE__);
        real_size = -1;
    }
    mutex_unlock(&g_cbp_resetinfo_lock);
    return real_size;
}


static void oem_cbp_reset_by_ap(struct cbp_reset_info_s resetinfo)
{
    char rst_buf[MDM_RESETINFO_SIZE] = {0};
    if(via_modem_state != MODEM_STATE_READY) {
        hwlog_err("%s %d: VIA is in reset!\n", __func__, __LINE__);
        return;
    }

    snprintf(rst_buf, MDM_RESETINFO_SIZE, 
        "cmpnt:%s\nreboot_task:%s\ntask_name:%s\nreboot_int:0xffffffff\nmodid:0x%x\n",
        resetinfo.stack, resetinfo.task_name, resetinfo.task_name, resetinfo.modid);
    hwlog_info("%s %d: resetinfo:%s", __func__, __LINE__, rst_buf);

    if(via_resetinfo_write(rst_buf, VIA_RESETINFO_WR_COVER)) {
        hwlog_err("%s %d:via_resetinfo_write write failed!\n", __func__,__LINE__);
    }

    if (0 == atomic_read(&cbp_backup_timer_started)) {
            mod_timer(&cbp_backup_timer, jiffies + msecs_to_jiffies(WAIT_CBP_BACKUP_RAMDUMP_RST_TIME));
            atomic_set(&cbp_backup_timer_started, 1);
    }

    oem_reset_modem_by_backup();
}

static int oem_gpio_get_cbp_rst_ind_value(void)
{
    if( cbp_reset_ind_connect_to_codec ) {
        //connected to hi6402, use task context gpio api
        return oem_gpio_get_value_cansleep(cbp_rst_ind_gpio);
    } else {
        //connected to soc, use interrupt context gpio api
        return oem_gpio_get_value(cbp_rst_ind_gpio);
    }
}

static void cbp_backup_check_ramdump_timer(unsigned long data)
{
    char rst_buf[CBP_EXCEPT_STACK_LEN]={0};

    atomic_set(&cbp_backup_timer_started, 0);
    snprintf(rst_buf, CBP_EXCEPT_STACK_LEN, "%s %d: VIA CBP can not produce ramdump by AP pull backup GPIO!\n", __func__,__LINE__);
    if(via_resetinfo_write(rst_buf, VIA_RESETINFO_WR_APPEND)) {
        hwlog_err("%s %d:via_resetinfo_write write failed!\n", __func__,__LINE__);
    }
    hwlog_info("%s", rst_buf);

    oem_reset_modem();
    hwlog_err("%s %d: finish hardware reset VIA CBP.\n", __func__, __LINE__);
}

static void set_time_stamp(void)
{
    struct timeval tv;
    struct rtc_time tm;
    memset(&tv, 0, sizeof(struct timeval));
    memset(&tm, 0, sizeof(struct rtc_time));
    do_gettimeofday(&tv);
    tv.tv_sec -= sys_tz.tz_minuteswest * 60;
    rtc_time_to_tm(tv.tv_sec, &tm);
    memset(time_buf, 0, sizeof(time_buf));
    hwlog_info("%s sizeof %d\n", __func__, (int)sizeof(time_buf));
    snprintf(time_buf, 16, "%04d%02d%02d%02d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

static void get_time_stamp(char* timestamp_buf,  unsigned int len)
{
    hwlog_info("%s sizeof %d\n", __func__, (int)sizeof(timestamp_buf));
    strncpy(timestamp_buf, time_buf, len);
}

static void apr_log_entry(struct work_struct* dummy)
{

    char cmd[256];
    char time_buf[16];
    int ret = 0;
    get_time_stamp(time_buf, 16);
    snprintf(cmd, 256, "%s%s%s%s%s",
             "archive -i /data/hwzd_logs/3rdcp-log",
             " -i /data/android_logs/kmsgcat-log -i /data/android_logs/kmsgcat-log.1",
             " -o ", time_buf, "_VIAMODEM -z zip");
    ret = log_to_exception("viamodem", cmd);
    if (ret < 0 )
    {
        hwlog_info("%s logexception sysfs err.\n", __func__);
    }
    hwlog_info("%s %d cmd %s ret %d\n", __func__, __LINE__, cmd, ret);

}
static DECLARE_DELAYED_WORK(apr_log_wk, apr_log_entry);

//schedule a work to send uevent
static void via_uevent_work_func(struct work_struct* data)
{
    struct viatel_modem_data* via_boot = vmdata;
    unsigned long flags;//linux native use for spin lock

    while (via_boot->head != via_boot->tail)
    {
        kobject_uevent_env(&viacbp82d_3rd_modem_info.dev.kobj, KOBJ_CHANGE, &vmdata->envp[via_boot->head][0] );
        hwlog_info("%s. notify event[%d,%d] %s to userspace!\n", __func__,
                   via_boot->tail, via_boot->head, vmdata->envp[via_boot->head][0]);

        spin_lock_irqsave(&vmdata->lock, flags);
        vmdata->envp[via_boot->head][0] = NULL;
        via_boot->head = (via_boot->head + 1) % QUEUE_NUM;
        spin_unlock_irqrestore(&vmdata->lock, flags);
    }

    hwlog_info("%s:%d notify uevent end\n", __func__, __LINE__);
}

/*
 Send the uevent notify message to userspace (rild)
*/
void via_monitor_uevent_notify(int event)
{
    struct viatel_modem_data* via_boot = vmdata;
    int temp = 0;
    unsigned long flags;
    hwlog_info("%s: event=%s\n", __func__, via_state_str[event]);

    if (vmdata == NULL )
    {
        hwlog_err("%s:%d vmdata is NULL\n", __func__, __LINE__);
        return;
    }

    //rild received "VPUP", then set modem ready, now via cbp is bringup, so we release wake lock.
    if ( MODEM_STATE_READY == event )
    {
        wake_unlock(&vmdata->wlock);
        hwlog_info("%s:%d wake_unlock(&vmdata->wlock) when received MODEM_STATE_READY event\n", __func__, __LINE__);
    }

    spin_lock_irqsave(&vmdata->lock, flags);
    temp = (via_boot->tail + 1) % QUEUE_NUM;
    if (temp != via_boot->head)
    {
        if (event >= MODEM_STATE_OFF && event < MODEM_STATE_INVALID)
        { vmdata->envp[via_boot->tail][0] = (char*)via_state_str[event]; }
        else
        { vmdata->envp[via_boot->tail][0] = (char*)via_state_str[MODEM_STATE_INVALID]; }

        vmdata->envp[via_boot->tail][1] = NULL;
        via_boot->tail = temp;
    }

    schedule_work(&vmdata->via_uevent_work);
    spin_unlock_irqrestore(&vmdata->lock, flags);
}



static void modem_signal_user(int event)
{
    if (vmdata && vmdata->fasync)
    {
        hwlog_info("%s: evnet %d.\n", __FUNCTION__,  event);
        kill_fasync(&vmdata->fasync, SIGIO, event);
    }
}

/* Protection for the above */
static DEFINE_RAW_SPINLOCK(rslock);

void oem_reset_modem(void)
{
    wake_lock_timeout(&vmdata->wlock, MDM_RST_LOCK_TIME * HZ);
    oem_gpio_direction_output(cbp_rst_gpio, 1);
    mdelay(MDM_RST_HOLD_DELAY);
    oem_gpio_direction_output(cbp_rst_gpio, 0);
    mdelay(MDM_RST_HOLD_DELAY);
    hwlog_info("Warnning: reset vmodem\n");
}
EXPORT_SYMBOL(oem_reset_modem);

void oem_reset_modem_by_backup(void)
{
    oem_gpio_direction_output(cbp_backup_gpio, 1);
    hwlog_info("cbp_backup_gpio =1,via will reset,then save the crash and ramdump to ap\n");
    msleep(CBP_BACKUP_GPIO_SELECT_HOLD_TIME);
    oem_gpio_direction_output(cbp_backup_gpio, 0);
    mdelay(CBP_BACKUP_GPIO_DELECT_DELAY);
}
void oem_power_on_modem(void)
{
    oem_gpio_direction_output(cbp_rst_gpio, 0);
    hwlog_info("%s cbp_rst_gpio:%d\n", __func__, cbp_rst_gpio);
    mdelay(MDM_RST_HOLD_DELAY);
    hwlog_info("%s cbp_pwr_en_gpio:%d\n", __func__, cbp_pwr_en_gpio);
    oem_gpio_direction_output(cbp_pwr_en_gpio, 1);
    mdelay(MDM_PWR_HOLD_DELAY);

    if (cbp_need_apr)
    {
        schedule_delayed_work(&apr_log_wk, msecs_to_jiffies(60 * 1000)); /*wait for 1 minute due to ramdump may later*/
        cbp_need_apr = 0;
    }
    hwlog_info("Warnning: power on vmodem\n");
}
EXPORT_SYMBOL(oem_power_on_modem);

void oem_power_off_modem(void)
{
    set_modem_bus_state(0);
    oem_gpio_direction_output(cbp_pwr_en_gpio, 0);
    oem_gpio_direction_output(cbp_rst_gpio, 1);
    /*just hold the reset pin if no power enable pin*/
    mdelay(MDM_RST_HOLD_DELAY);
    oem_gpio_direction_output(cbp_rst_gpio, 0);
    hwlog_info("Warnning: power off vmodem\n");
}
EXPORT_SYMBOL(oem_power_off_modem);

int modem_err_indication_usr(int revocery, struct cbp_reset_info_s resetinfo)
{
    hwlog_info("%s %d revocery=%d\n", __func__, __LINE__, revocery);
    if (revocery)
    {
        hwlog_info("%s %d MDM_EVT_NOTIFY_HD_ERR\n", __func__, __LINE__);
        /*1, check the rst_ind*/
        /*2, set GPIO_7_3 low*/
        hwlog_info("%s %d rst_ind %d\n", __func__, __LINE__, oem_gpio_get_cbp_rst_ind_value());

        if (0 == atomic_read(&cbp_backup_timer_started))
        {
            mod_timer(&cbp_backup_timer, jiffies + msecs_to_jiffies(WAIT_CBP_BACKUP_RAMDUMP_RST_TIME));
            atomic_set(&cbp_backup_timer_started, 1);
        }
        oem_cbp_reset_by_ap(resetinfo);

        //cbp_need_apr = 1;
        set_time_stamp();
        //schedule_delayed_work(&apr_log_wk, 0);
        modem_notify_event(MDM_EVT_NOTIFY_HD_ERR);
    }
    else
    {
        hwlog_info("%s %d MDM_EVT_NOTIFY_HD_ENHANCE\n", __func__, __LINE__);
        modem_notify_event(MDM_EVT_NOTIFY_HD_ENHANCE);
    }
    return 0;
}
EXPORT_SYMBOL(modem_err_indication_usr);

void modem_err_indication_usr_form_module(void *rst_buf, char *rst_mod_name, enum cbp_except_modid_e rst_modid)
{
    struct cbp_reset_info_s resetinfo;

    memset(&resetinfo, 0, sizeof(resetinfo));
    if(rst_mod_name) {
        memcpy(resetinfo.task_name, rst_mod_name, strlen(rst_mod_name)+1);
    }
    if(rst_buf) {
        memcpy(resetinfo.stack, rst_buf, strlen(rst_buf)+1);
	}
    resetinfo.modid = rst_modid;
    modem_err_indication_usr(1, resetinfo);
}
EXPORT_SYMBOL(modem_err_indication_usr_form_module);

void oem_let_cbp_die(void)
{
    if (GPIO_OEM_VALID(GPIO_VIATEL_CRASH_CBP))
    {
        oem_gpio_direction_output(GPIO_VIATEL_CRASH_CBP, 0);
        mdelay(MDM_RST_HOLD_DELAY);
        oem_gpio_direction_output(GPIO_VIATEL_CRASH_CBP, 1);
    }
    hwlog_info("let cbp die\n");
}
EXPORT_SYMBOL(oem_let_cbp_die);



static int modem_reset_notify_misc(struct notifier_block* nb, unsigned long event,
                                   void* ptr)
{
    switch (event)
    {
        case MDM_EVT_NOTIFY_RESET_ON:
            modem_signal_user(ASC_USER_MDM_RESET_ON);
            break;
        case MDM_EVT_NOTIFY_RESET_OFF:
            modem_signal_user(ASC_USER_MDM_RESET_OFF);
            break;
        default:
            ;
    }

    return NOTIFY_OK;
}


/*
 * Notify about a modem event change.
 *
 */
static void modem_notify_task(struct work_struct* work)
{
    int i = 0;

    for (i = 0; i < MDM_EVT_NOTIFY_NUM; i++)
    {
        if (test_and_clear_bit(i, &vmdata->ntf_flags))
        {
            raw_notifier_call_chain(&vmdata->ntf, i, NULL);
        }
    }
}

void modem_notify_event(int event)
{
    if (vmdata && event < MDM_EVT_NOTIFY_NUM)
    {
        set_bit(event, &vmdata->ntf_flags);
        schedule_work(&vmdata->work);
    }
}
EXPORT_SYMBOL(modem_notify_event);

/*
 *  register a modem events change listener
 */
int modem_register_notifier(struct notifier_block* nb)
{
    int ret = -ENODEV;
    unsigned long flags;

    if (vmdata)
    {
        raw_spin_lock_irqsave(&rslock, flags);
        ret = raw_notifier_chain_register(&vmdata->ntf, nb);
        raw_spin_unlock_irqrestore(&rslock, flags);
    }
    return ret;
}
EXPORT_SYMBOL(modem_register_notifier);

/*
 *  unregister a modem events change listener
 */
int modem_unregister_notifier(struct notifier_block* nb)
{
    int ret = -ENODEV;
    unsigned long flags;

    if (vmdata)
    {
        raw_spin_lock_irqsave(&rslock, flags);
        ret = raw_notifier_chain_unregister(&vmdata->ntf, nb);
        raw_spin_unlock_irqrestore(&rslock, flags);
    }
    return ret;
}
EXPORT_SYMBOL(modem_unregister_notifier);

static int first_irq_flag = 1;
static irqreturn_t modem_reset_indication_irq(int irq, void* data)
{
    int rst_level = 0;
    if (GPIO_OEM_VALID(cbp_rst_ind_gpio ))
    {
        hwlog_info("%s %d oem_gpio_get_value_cansleep(GPIO_VIATEL_MDM_RST_IND)=%d \n", __func__, __LINE__, oem_gpio_get_cbp_rst_ind_value());
        if (oem_gpio_get_cbp_rst_ind_value())
        {
            if (first_irq_flag == 1)
            {
                hwlog_info("%s %d first irq read rest_gpio is high,return. \n", __func__, __LINE__);
                return IRQ_HANDLED;
            }
            wake_lock_timeout(&vmdata->wlock, MDM_RST_LOCK_TIME * HZ);
            modem_notify_event(MDM_EVT_NOTIFY_RESET_ON);
            via_modem_state = MODEM_STATE_POWER;
            via_monitor_uevent_notify(MODEM_STATE_POWER);
            rst_level = 1;
        }
        else
        {
            if (first_irq_flag == 1)
            {
                hwlog_info("%s %d set first_irq_flag=0. \n", __func__, __LINE__);
                first_irq_flag = 0;
            }
            modem_notify_event(MDM_EVT_NOTIFY_RESET_OFF);
            rst_level = 0;
        }
        if (1 == atomic_read(&cbp_backup_timer_started))
        {
            del_timer(&cbp_backup_timer);
        }
    }
    irq_set_irq_type(irq, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING);
    gpio_irq_cbp_rst_ind(rst_level);
    oem_gpio_irq_unmask(cbp_rst_ind_gpio);
    return IRQ_HANDLED;
}



static int misc_modem_open(struct inode* inode, struct file* filp)
{
    int ret = -ENODEV;
    if (vmdata)
    {
        filp->private_data = vmdata;
        atomic_inc(&vmdata->count);
        ret = 0;
    }

    return ret;
}

static int misc_modem_release(struct inode *inode, struct file *filp)
{
    struct viatel_modem_data* d = (struct viatel_modem_data*)(filp->private_data);

    if (atomic_read(&vmdata->count) > 0)
    {
        atomic_dec(&vmdata->count);
    }
    return fasync_helper(-1, filp, 0, &d->fasync);
}

static int misc_modem_fasync(int fd, struct file* filp, int on)
{
    struct viatel_modem_data* d = (struct viatel_modem_data*)(filp->private_data);
    return fasync_helper(fd, filp, on, &d->fasync);
}



static int modem_data_init(struct viatel_modem_data* d)
{
    int ret = 0;

    d->ntf_flags = 0;
    RAW_INIT_NOTIFIER_HEAD(&d->ntf);
    wake_lock_init(&d->wlock, WAKE_LOCK_SUSPEND, "cbp_rst");
    spin_lock_init( &d->lock );
    INIT_WORK(&d->work, modem_notify_task);
    INIT_WORK(&d->via_uevent_work, via_uevent_work_func);
    d->rst_ntf.notifier_call = modem_reset_notify_misc;
    atomic_set(&d->count, 0);
    mutex_init(&g_cbp_resetinfo_lock);

    return ret;
}


static inline void modem_boot_change_state(int state)
{
    hwlog_info("modem_power: Power state change: %d -> %d\n", via_curr_power_state, state);
    via_curr_power_state = state;
}

#if 0
static ssize_t modem_boot_get(struct device* pdev, struct device_attribute* attr, char* buf)
{
    ssize_t ret = via_curr_power_state;
    return sprintf(buf, "%d\n", ret);
}
#endif


static ssize_t modem_boot_set(struct device* pdev, struct device_attribute* attr, const char* buf, size_t count)
{
    int state;

    hwlog_info("Power PHY set to %s\n", buf);

    if (kstrtoint(buf, 10, &state))
    {
        hwlog_err("%s:%d kstrtoint %s fail\n", __func__, __LINE__, buf);
        return -EINVAL;
    }

	switch(state){
		case POWER_SET_DEBUGOFF:
			modem_boot_change_state(state);
			oem_power_off_modem();
			break;
		case POWER_SET_DEBUGON:
			modem_boot_change_state(state);
			oem_power_on_modem();
			break;
		case POWER_SET_OFF:
			modem_boot_change_state(state);
			via_modem_state = MODEM_STATE_OFF;
			via_monitor_uevent_notify(MODEM_STATE_OFF);
			oem_power_off_modem();
			break;
		case POWER_SET_ON:
			modem_boot_change_state(state);
			oem_power_on_modem();
			break;
		case MODEM_CTRL_RESET:
			oem_reset_modem();
			break;
		case MODEM_CTRL_DIE:
			oem_let_cbp_die();
			break;
		case MODEM_CTRL_WAKE_LOCK:
			hwlog_info("hold on wakelock.\n");
			wake_lock(&vmdata->wlock);
			break;
		case MODEM_CTRL_WAKE_LOCK_RELEASE:
			hwlog_info("release wakelock.\n");
			wake_unlock(&vmdata->wlock);
			break;
		default:
			hwlog_info("default: do nothing!\n");
			break;
	}

    return count;
}



static ssize_t modem_state_show(struct device* pdev, struct device_attribute* attr, char* buf)
{
    return ( snprintf(buf, PAGE_SIZE, "%s\n", via_state_str[via_modem_state]) );
}

static ssize_t modem_state_store(struct device* pdev, struct device_attribute* attr, const char* buf, size_t count)
{
    int modem_state;

    hwlog_info("set modem_state to  %s\n", buf);

    if ( kstrtoint(buf, 10, &modem_state) )
    {
        hwlog_err("%s:%d kstrtoint %s fail\n", __func__, __LINE__, buf);
        return -EINVAL;
    }

    if (modem_state == MODEM_STATE_READY)
    {
        via_modem_state = MODEM_STATE_READY;
        via_monitor_uevent_notify(MODEM_STATE_READY);
    }
    else
    {
        hwlog_err("Power PHY error state. %s\n", buf);
    }

    return count;

}

int is_via_modem_state_ready(void)
{
    if (MODEM_STATE_READY == via_modem_state)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
EXPORT_SYMBOL(is_via_modem_state_ready);

ssize_t modem_sim_switch_show(struct device* dev, struct device_attribute* attr, char* buf)
{
    int reset = 0;
    int ret = 0;
    if (GPIO_OEM_VALID(cbp_sim_switch_gpio))
    {
        reset = !!oem_gpio_get_value(cbp_sim_switch_gpio);
    }

    if (reset)
    {
        ret += sprintf(buf + ret, "sim_to_VIA\n");
    }
    else
    {
        ret += sprintf(buf + ret, "sim_to_Balong\n");
    }
    return ret;
}

ssize_t modem_sim_switch_store(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    if ( !strncmp(buf, "1", strlen("1")))
    {
        oem_gpio_direction_output(cbp_sim_switch_gpio, 1);
        hwlog_info("Switch sim connection to VIA\n");
    }
    else if ( !strncmp(buf, "0", strlen("0")))
    {
        oem_gpio_direction_output(cbp_sim_switch_gpio, 0);
        hwlog_info("Switch sim connection to Balong\n");
    }
    else
    {
        hwlog_info("Unknow command.\n");
    }
    return count;
}


ssize_t modem_via_backup_show(struct device* dev, struct device_attribute* attr, char* buf)
{
    int reset = 0;
    if (GPIO_OEM_VALID(cbp_backup_gpio))
    {
        reset = !!oem_gpio_get_value(cbp_backup_gpio);
    }
    if (reset)
    {
        return snprintf(buf, PAGE_SIZE, "via_backup_on\n");
    }
    else
    {
        return snprintf(buf, PAGE_SIZE, "via_backup_off\n");
    }
}
ssize_t modem_via_backup_store(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    if ( !strncmp(buf, "1", strlen("1")))
    {
        oem_reset_modem_by_backup();
    }
    else if ( !strncmp(buf, "0", strlen("0")))
    {
        oem_gpio_direction_output(cbp_backup_gpio, 0);
    }else if( !strncmp(buf, CBP_EXCEPT_RILD_AT_TIMEOUT, strlen(CBP_EXCEPT_RILD_AT_TIMEOUT))) {
        struct cbp_reset_info_s resetinfo;

        memset(&resetinfo, 0, sizeof(resetinfo));
        memcpy(resetinfo.task_name, CBP_EXCEPT_REASON_RILD, (strlen(CBP_EXCEPT_REASON_RILD)+1));
        resetinfo.modid = CBP_EXCE_MID_RILD_AT_TIMEOUT;
        memcpy(resetinfo.stack, "at timeout", strlen("at timeout")+1);
        oem_cbp_reset_by_ap(resetinfo);
    }else{
        hwlog_info("Unknow command.\n");
    }
    return count;
}
ssize_t modem_via_rst_mdm_show(struct device* dev, struct device_attribute* attr, char* buf)
{
    int reset = 0;
    if (GPIO_OEM_VALID(cbp_rst_ind_gpio))
    {
        reset = !!oem_gpio_get_cbp_rst_ind_value();
    }
    if (reset)
    {
        return snprintf(buf, PAGE_SIZE, "via_reset_on\n");
    }
    else
    {
        return snprintf(buf, PAGE_SIZE, "via_reset_off\n");
    }
}
ssize_t modem_via_rst_mdm_store(struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    if ( !strncmp(buf, "1", strlen("1")))
    {
        oem_reset_modem();
    }else if( !strncmp(buf, "0", strlen("0"))){
        oem_gpio_direction_output(cbp_rst_gpio, 0);
    }else{
        hwlog_info("Unknow command.\n");
    }
        return count;
}

ssize_t modem_via_resetinfo_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    int count = -1;
    hwlog_info("%s %d: start to read resetinfo from g_cbp_resetinfo", __func__,__LINE__);
    count = via_resetinfo_read(buf, PAGE_SIZE);
    return count;
}

ssize_t modem_via_resetinfo_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    int ret = -1;

    hwlog_info("%s %d: start to call modem_via_resetinfo_store\n", __func__,__LINE__);
    if( !strncmp(buf, VIA_RESETINFO_WR_CLEAR, strlen(VIA_RESETINFO_WR_CLEAR)) ) {
        ret = via_resetinfo_write(VIA_RESETINFO_WR_CLEAR, VIA_RESETINFO_WR_COVER);
        if(ret != 0) {
            hwlog_err("%s %d: via_resetinfo_write write failed!\n", __func__,__LINE__);
            count = -1;
        }
        hwlog_info("%s %d: resetinfo has been clean.\n", __func__,__LINE__);
    }
    return count;
}
//static DEVICE_ATTR(state, S_IRUGO | S_IWUSR, modem_boot_get, modem_boot_set);
static DEVICE_ATTR(state, S_IRUGO | S_IWUSR, modem_state_show, modem_boot_set);
static DEVICE_ATTR(modem_state, S_IRUGO | S_IWUSR, modem_state_show, modem_state_store);
static DEVICE_ATTR(sim_switch, S_IRUGO | S_IWUSR, modem_sim_switch_show, modem_sim_switch_store);
static DEVICE_ATTR(via_backup, S_IRUGO | S_IWUSR, modem_via_backup_show, modem_via_backup_store);
static DEVICE_ATTR(via_rst_mdm, S_IRUGO | S_IWUSR, modem_via_rst_mdm_show, modem_via_rst_mdm_store);
static DEVICE_ATTR(via_resetinfo, S_IRUGO | S_IWUSR, modem_via_resetinfo_show, modem_via_resetinfo_store);

static struct attribute *viacbp82d_3rd_modem_attributes[] = {
    &dev_attr_modem_state.attr,
    &dev_attr_state.attr,
    &dev_attr_sim_switch.attr,
    &dev_attr_via_backup.attr,
    &dev_attr_via_rst_mdm.attr,
    &dev_attr_via_resetinfo.attr,
    NULL,
};

static const struct attribute_group viacbp82d_3rd_modem_node =
{
    .attrs = viacbp82d_3rd_modem_attributes,
};

static int modem_boot_probe(struct platform_device* pdev)
{
    int ret = 0;
    struct device* dev = &pdev->dev;
    struct device_node* np = dev->of_node;

    hwlog_info("%s %d: enter.\n", __func__, __LINE__);
    vmdata = kzalloc(sizeof(struct viatel_modem_data), GFP_KERNEL);
    if (!vmdata)
    {
        ret = -ENOMEM;
        hwlog_err("No memory to alloc vmdata");
        goto err_create_vmdata;
    }

    vmdata->via_pdev = pdev;
    vmdata->tail = 0;
    vmdata->head = 0;

    ret = modem_data_init(vmdata);
    if (ret < 0)
    {
        hwlog_err("Fail to init modem data\n");
        goto err_init_modem_data;
    }

    ret = platform_device_register(&viacbp82d_3rd_modem_info);
    if (ret)
    {
        hwlog_err( "%s: platform_device_register failed, ret:%d.\n",
                   __func__, ret);
        goto err_register_platform_device;
    }

    ret = sysfs_create_group(&viacbp82d_3rd_modem_info.dev.kobj, &viacbp82d_3rd_modem_node);
    if (ret)
    {
        hwlog_err( "sensor_input_info_init sysfs_create_group error ret =%d", ret);
        platform_device_unregister(&viacbp82d_3rd_modem_info);
        goto err_create_sysfs_group;
    }

    ret = of_property_read_u32(np, "via_reset_ind_connect_to_codec", &cbp_reset_ind_connect_to_codec);
    if (ret)
    {
        hwlog_err("can't get cbp_reset_ind_connect_to_codec property in viacbp82d_power device node\n");
        goto err_get_gpio;
    }

    hwlog_info("get cbp_reset_ind_connect_to_codec:%u\n", cbp_reset_ind_connect_to_codec);

    /* rst_ind is connect to hi6402 codec in fifa */
    cbp_rst_ind_gpio = of_get_named_gpio(np, "via_reset_ind", 0);//gpio is 254
    hwlog_info("%s get CBP_VIATEL_RST_IND_STR gpio %d\n", __func__, cbp_rst_ind_gpio);
    if (GPIO_OEM_VALID(cbp_rst_ind_gpio))
    {
        int irq = 0;
        ret = oem_gpio_request(cbp_rst_ind_gpio, "GPIO_VIATEL_MDM_RST_IND");
        if (ret < 0 )
        {
            hwlog_err("%s:%d gpio_request %d fail, return:%d\n", __func__, __LINE__, cbp_rst_ind_gpio, ret);
        }
        oem_gpio_irq_mask(cbp_rst_ind_gpio);
        ret = oem_gpio_direction_input_for_irq(cbp_rst_ind_gpio);
        if (ret < 0 )
        {
            hwlog_err("%s:%d gpio_direction_inout_for_irq %d fail, return:%d\n", __func__, __LINE__, cbp_rst_ind_gpio, ret);
        }

        irq = oem_gpio_to_irq(cbp_rst_ind_gpio);
        hwlog_info("%s:%d cbp_rst_ind_gpio:%d irq is:%d\n", __func__, __LINE__,  cbp_rst_ind_gpio, irq);

        oem_gpio_set_irq_type(cbp_rst_ind_gpio, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING);

        if ( cbp_reset_ind_connect_to_codec )
        {
            //connected to hi6402, then use task context api to register irq handler.
            ret = oem_gpio_request_threaded_irq(cbp_rst_ind_gpio, modem_reset_indication_irq, \
                                                IRQF_SHARED | IRQF_NO_SUSPEND | IRQF_TRIGGER_FALLING, \
                                                "mdm_reset_ind", vmdata);
        }
        else
        {
            ret = oem_gpio_request_irq(cbp_rst_ind_gpio, modem_reset_indication_irq, \
                                       IRQF_SHARED | IRQF_NO_SUSPEND | IRQF_TRIGGER_FALLING, \
                                       "mdm_reset_ind", vmdata);
        }

        oem_gpio_irq_unmask(cbp_rst_ind_gpio);

        if (ret < 0)
        {
            hwlog_err("%s:%d fail to request mdm_rst_ind %d irq, return:%d\n", __func__, __LINE__, cbp_rst_ind_gpio, ret);
        }
        hwlog_info("%s:%d gpio via_reset_ind %d init successfully\n", __func__, __LINE__, cbp_rst_ind_gpio);

        modem_register_notifier(&vmdata->rst_ntf);
    }
    else
    {
        hwlog_err("%s:%d via_reset_ind is invalid gpio\n", __func__, __LINE__);
        goto err_get_gpio;
    }

    cbp_pwr_en_gpio = of_get_named_gpio(np, "via_pwr_en", 0);
    hwlog_info("%s get CBP_VIATEL_PWR_EN_STR gpio %d\n", __func__, cbp_pwr_en_gpio);
    if (GPIO_OEM_VALID(cbp_pwr_en_gpio))
    {
        ret = oem_gpio_request(cbp_pwr_en_gpio, "GPIO_VIATEL_MDM_PWR_EN");
        if (0 > ret)
        {
            hwlog_err("%s: gpio request GPIO_VIATEL_MDM_PWR_EN failed", __FUNCTION__);
        }
        oem_gpio_direction_output(cbp_pwr_en_gpio, 0);
    }
    else
    {
        goto err_get_gpio;
    }

    cbp_rst_gpio = of_get_named_gpio(np, "via_rst_mdm", 0);
    hwlog_info("%s get CBP_VIATEL_CBP_RST_STR gpio %d\n", __func__, cbp_rst_gpio);
    if (GPIO_OEM_VALID(cbp_rst_gpio))
    {
        ret = oem_gpio_request(cbp_rst_gpio, "GPIO_VIATEL_MDM_RST");
        if (0 > ret)
        {
            hwlog_err("%s: gpio request GPIO_VIATEL_MDM_RST failed", __FUNCTION__);
        }
        oem_gpio_direction_output(cbp_rst_gpio, 0);
    }
    else
    {
        goto err_get_gpio;
    }

#if 0 //don't delete. there is no gpio for sim switch
    cbp_sim_switch_gpio = of_get_named_gpio(np, "via_sim_switch", 0);
    hwlog_info("%s get CBP_VIATEL_CBP_SIM_SWITCH gpio %d\n", __func__, cbp_sim_switch_gpio);
    if (GPIO_OEM_VALID(cbp_sim_switch_gpio))
    {
        ret = oem_gpio_request(cbp_sim_switch_gpio, "GPIO_VIATEL_MDM_SIM_SWITCH");
        if (0 > ret)
        {
            hwlog_err("%s: gpio request GPIO_VIATEL_MDM_SIM_SWITCH failed", __FUNCTION__);
        }
        oem_gpio_direction_output(cbp_sim_switch_gpio, 0);
    }
    else
    {
        goto err_get_gpio;
    }
#endif

    /*add gpio function to make cp ramdump*/
    cbp_backup_gpio = of_get_named_gpio(np, "via_backup", 0);
    hwlog_info("%s get CBP_VIATEL_CBP_BACKUP gpio %d\n", __func__, cbp_backup_gpio);
    if (GPIO_OEM_VALID(cbp_backup_gpio))
    {
        ret = oem_gpio_request(cbp_backup_gpio, "gpio_cbp_crash");
        if (0 > ret)
        {
            hwlog_err("%s: gpio request gpio_cbp_crash failed", __FUNCTION__);
        }
        oem_gpio_direction_output(cbp_backup_gpio, 0);
        setup_timer(&cbp_backup_timer, cbp_backup_check_ramdump_timer, (unsigned long)NULL);
    }
    else
    {
        goto err_get_gpio;
    }
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return 0;

err_get_gpio:
    sysfs_remove_group(&viacbp82d_3rd_modem_info.dev.kobj, &viacbp82d_3rd_modem_node);
err_create_sysfs_group:
    platform_device_unregister(&viacbp82d_3rd_modem_info);
err_register_platform_device:
err_init_modem_data:
    kfree(vmdata);
    vmdata = NULL;
err_create_vmdata:

    return ret;
}

static int modem_boot_remove(struct platform_device* pdev)
{
    hwlog_info("%s %d: enter.\n", __func__, __LINE__);
    if (GPIO_OEM_VALID(cbp_rst_ind_gpio))
    {
        free_irq(oem_gpio_to_irq(cbp_rst_ind_gpio), vmdata);
        oem_gpio_free(cbp_rst_ind_gpio);
        modem_unregister_notifier(&vmdata->rst_ntf);
    }

    if (vmdata)
    { wake_lock_destroy(&vmdata->wlock); }
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return 0;
}

static void modem_boot_shutdown(struct platform_device* pdev)
{
    hwlog_info("%s %d: enter.\n", __func__, __LINE__);
    oem_power_off_modem();
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}


static const struct of_device_id viacbp82d_power_match_table[] =
{
    {
        .compatible = VIACBP82D_POWER_DRIVER_NAME,
        .data = NULL,
    },
    {
    },
};
MODULE_DEVICE_TABLE(of, viacbp82d_power_match_table);


static struct platform_driver modem_boot_driver =
{
    .probe = modem_boot_probe,
    .remove = modem_boot_remove,
    .shutdown = modem_boot_shutdown,
    .driver = {
        .name = "huawei,viacbp82d-power",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(viacbp82d_power_match_table),
    },
};



static const struct file_operations misc_modem_fops = {
	.owner = THIS_MODULE,
	.open = misc_modem_open,
	.release = misc_modem_release,
	.fasync	= misc_modem_fasync,
};

static struct miscdevice misc_modem_device =
{
    .minor = MISC_DYNAMIC_MINOR,
    .name = "vmodem",
    .fops = &misc_modem_fops,
};

static int __init modem_boot_init(void)
{
    int ret = 0;

    hwlog_info("%s %d: enter.\n", __func__, __LINE__);
    ret = platform_driver_register(&modem_boot_driver);
    if (ret < 0)
    {
        hwlog_err("platform_driver_register failed\n");
        goto err_platform_driver_register;
    }

    ret = misc_register(&misc_modem_device);
    if (ret < 0)
    {
        hwlog_err("misc regiser via modem failed\n");
        goto err_misc_device_register;
    }
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
    return ret;

err_misc_device_register:
    platform_driver_unregister(&modem_boot_driver);
err_platform_driver_register:

    return ret;
}

static void __exit modem_boot_exit(void)
{
    hwlog_info("%s %d: enter.\n", __func__, __LINE__);
    platform_driver_unregister(&modem_boot_driver);
    hwlog_info("%s %d: Exit.\n", __func__, __LINE__);
}
late_initcall_sync(modem_boot_init);
module_exit(modem_boot_exit);
