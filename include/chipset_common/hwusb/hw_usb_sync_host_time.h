/*
 * <chipset_common/hwusb/hw_sync_host_time.h>
 * $Revision: #123 $
 * $Date: 2015/05 $
 * Through the PC side USB driver will be sent to the mobile phone side time,
 * ensure the PC side and mobile phone side time synchronization time;
 *
 * huawei header pc time synchronization to the system time of phone.
 */
#ifndef __DRIVERS_USB_HW_TIMESYNC_H__
#define __DRIVERS_USB_HW_TIMESYNC_H__

#include <linux/kobject.h>
#include <linux/device.h>
#include <linux/stat.h>
#include <linux/interrupt.h>    /* For in_interrupt() */
#include <linux/fs.h>


/*========================================================================
FUNCTION       hw_usb_handle_host_time

DESCRIPTION  : Get PC time, the system calls the kernel function, 
set the system time.

PARAM:    struct usb_ep *ep: usb endpoint Pointer;
          struct usb_request *req:usb request massage data;         
RETURN VALUE : void

DEPENDENCIES : void do_gettimeofday(struct timeval *tv);
=========================================================================*/
void hw_usb_handle_host_time(struct usb_ep *ep, struct usb_request *req);

/*========================================================================
FUNCTION       hw_usb_sync_host_time_init

DESCRIPTION  : Initialize the data structure and work queue. 

PARAM:    void
RETURN VALUE : void

DEPENDENCIES : NA
=========================================================================*/
void hw_usb_sync_host_time_init(void);

#endif /* __DRIVERS_USB_HW_TIMESYNC_H__ */
