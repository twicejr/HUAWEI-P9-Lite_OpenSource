/*
 * huawei Gadget Driver for Android
 *
 * Copyright (C) 2015 Huawei, Company.
 * Author: NA
 *
 * PC through the USB drive, synchronized to the kernel of the system time, 
 * because when the phone is out of power, the kernel of the system time on 
 * initial 1970-1-1, that it is not good for problem analysis and positioning, 
 * so through the USB drive computer system time synchronization to 
 * the system time of the mobile phone, can facilitate the localization problem.
 * This function only when the port on the phone for the production of port 
 * and time system for 1970-1-1, will take effect so as not to 
 * affect the end user use.
 *
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/utsname.h>
#include <linux/platform_device.h>
#include <linux/rtc.h>
#include <linux/usb/ch9.h>
#include <linux/usb/composite.h>
#include <linux/usb/gadget.h>


#define HW_USB_TIME_SYNC_PC


#ifdef HW_USB_TIME_SYNC_PC
    #define AFTER_BOOT_TO_1970YEAR ((1971-1970)*365*24*60*60)
    #define BEIJING_TIME_ZONE 8
struct _time {
    int            time_bias;
    unsigned short year;
    unsigned short month;
    unsigned short day;
    unsigned short hour;
    unsigned short minute;
    unsigned short second;
    unsigned short millisecond;
    unsigned short weekday;
};
struct hw_flush_pc_time {
    struct timespec tv;
    struct delayed_work pc_data_work;
};

static struct hw_flush_pc_time flush_pc_data;

static void hw_usb_flush_pc_time_work(struct work_struct *work)
{
    struct hw_flush_pc_time *pc_data = container_of(work,
            struct hw_flush_pc_time, pc_data_work.work);
    struct rtc_device *rtc;
    struct rtc_time new_rtc_tm;
    int rv = 0;

    if(do_settimeofday(&pc_data->tv) < 0)
    {
        printk(KERN_INFO "[USB_DEBUG]set system time Fail!\n");
    }
    rtc = rtc_class_open(CONFIG_RTC_HCTOSYS_DEVICE);
    if (rtc == NULL) {
        printk(KERN_INFO "%s: unable to open rtc device (%s)\n",
                __FILE__, CONFIG_RTC_HCTOSYS_DEVICE);
        return;
    }

    rtc_time_to_tm(pc_data->tv.tv_sec, &new_rtc_tm);
    rv = rtc_set_time(rtc, &new_rtc_tm);
    if(rv!=0)
    {
        printk(KERN_INFO "[USB_DEBUG]set RTC time Fail!\n");
    }
    printk(KERN_INFO "[USB_DEBUG]set system time ok!\n");
    //	spin_lock_irqsave(&alarm_slock, flags);
    //	alarm_pending |= ANDROID_ALARM_TIME_CHANGE_MASK;
    //	wake_up(&alarm_wait_queue);
    //	spin_unlock_irqrestore(&alarm_slock, flags);
}

/*========================================================================
FUNCTION       hw_usb_handle_host_time

DESCRIPTION  : Get PC time, the system calls the kernel function, 
set the system time.

PARAM:    struct usb_ep *ep: usb endpoint Pointer;
          struct usb_request *req:usb request massage data;         
RETURN VALUE : void

DEPENDENCIES : void do_gettimeofday(struct timeval *tv);
=========================================================================*/
void hw_usb_handle_host_time(struct usb_ep *ep, struct usb_request *req)
{
    struct _time *host_time;
    struct timeval tvNow;

    host_time = (struct _time *)req->buf;

    printk(KERN_INFO "Time Bias:%d minutes\n", host_time->time_bias);

    printk(KERN_INFO "Host Time:[%d:%d:%d %d:%d:%d:%d Weekday:%d]\n", host_time->year,
            host_time->month, host_time->day, host_time->hour, host_time->minute,
            host_time->second, host_time->millisecond, host_time->weekday);
    do_gettimeofday(&tvNow);
    if(AFTER_BOOT_TO_1970YEAR < (tvNow.tv_sec))
        return;

    flush_pc_data.tv.tv_nsec = NSEC_PER_SEC >> 1;
    flush_pc_data.tv.tv_sec = (unsigned long) mktime (host_time->year,
                    host_time->month,
                    host_time->day,
                    (host_time->hour+BEIJING_TIME_ZONE),
                    host_time->minute,
                    host_time->second);
    schedule_delayed_work(&(flush_pc_data.pc_data_work), 0);

    return;
}
EXPORT_SYMBOL(hw_usb_handle_host_time);
/*========================================================================
FUNCTION       hw_usb_sync_host_time_init

DESCRIPTION  : Initialize the data structure and work queue. 

PARAM:    void
RETURN VALUE : void

DEPENDENCIES : NA
=========================================================================*/
void hw_usb_sync_host_time_init(void)
{
    pr_info("Enter fuction %s\n", __func__);
    memset(&flush_pc_data, 0, sizeof(struct hw_flush_pc_time) );
    INIT_DELAYED_WORK(&(flush_pc_data.pc_data_work), hw_usb_flush_pc_time_work);
}
EXPORT_SYMBOL(hw_usb_sync_host_time_init);
#endif
