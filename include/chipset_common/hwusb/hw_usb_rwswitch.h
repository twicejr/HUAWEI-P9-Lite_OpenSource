/*
 * <chipset_common/hwusb/hw_rwswitch.h>
 * $Revision: #123 $
 * $Date: 2015/05 $
 * The following interface function and data structure, 
 * complete the bottom to upper HW Hw_ueventd service 
 * sends switching production port instruction function.
 *
 * huawei header rework switch usb to the manufacture port .
 */
#ifndef __DRIVERS_USB_HW_RWSWITCH_H__
#define __DRIVERS_USB_HW_RWSWITCH_H__

#include <linux/kobject.h>
#include <linux/device.h>
#include <linux/stat.h>
#include <linux/interrupt.h>    /* For in_interrupt() */
#include <linux/fs.h>


//USB vendor customized request to switch USB port mode;
#define  USB_REQ_VENDOR_SWITCH_MODE	0xA5


//USB_PortMode switch index define
#define INDEX_ENDUSER_SWITCH            0x11    //0x11 设置为USB端口模式17: "pcmodem2";
#define INDEX_FACTORY_REWORK            0x0E   //0x0E 设置为USB端口模式14: "manufacture,adb";
#define INDEX_USB_REWORK_SN            0x0D   //0x0D 设置为USB端口模式13;

/*========================================================================
FUNCTION       hw_usb_port_switch_request

DESCRIPTION  : submit usb switch request by sending uevent.

PARAM: int usb_switch_index:0x0E is factory port mode.

RETURN VALUE :return -1 is exception,other is normal.

DEPENDENCIES : NA
=========================================================================*/
int hw_usb_port_switch_request(int usb_switch_index);

/*========================================================================
FUNCTION       hw_usb_port_mode_get

DESCRIPTION  : get usb port mode.

PARAM: void

RETURN VALUE :usb port mode index.

DEPENDENCIES : NA
=========================================================================*/
int hw_usb_port_mode_get(void);

#ifdef CONFIG_HUAWEI_ANDROID
void hw_usb_get_device(struct device *dev);
#endif
#endif /* __DRIVERS_USB_HW_RWSWITCH_H__ */
