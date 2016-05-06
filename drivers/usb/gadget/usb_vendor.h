/*************************************************************************
*   版权所有(C) 1987-2011, 深圳华为技术有限公司.
*
*   文 件 名 :  usb_vendor.h
*
*   作    者 :  wangzhongshun
*
*   描    述 :  gadget usb驱动内接口头文件
*
*   修改记录 :  2013年2月2日  v1.00  wangzhongshun创建
*************************************************************************/

#ifndef __USB_VENDOR_H__
#define __USB_VENDOR_H__

#include <linux/notifier.h>

#define USB_NOTIF_PRIO_ADP		0	/* adp has lowest priority */
#define USB_NOTIF_PRIO_FD		100	/* function drvier */
#define USB_NOTIF_PRIO_CORE		200	/* usb core */
#define USB_NOTIF_PRIO_HAL		300	/* hardware has highest priority */

#define USB_BALONG_DEVICE_INSERT	1
#define USB_BALONG_CHARGER_IDEN		2
#define USB_BALONG_ENUM_DONE		3
#define USB_BALONG_PERIP_INSERT		4
#define USB_BALONG_PERIP_REMOVE		5
#define USB_BALONG_DEVICE_REMOVE	0
/* if the version is not support pmu detect
 * and all the device is disable, we assume that the usb is remove,
 */
#define USB_BALONG_DEVICE_DISABLE	(0xF1)

#define USB_FD_DEVICE_MAX		32
#define USB_CDEV_NAME_MAX		64

/*
 * interface descriptor for pnp2.1
 */
#define HW_PNP21_CLASS       0xff
#define HW_PNP21_SUBCLASS    0x13


typedef enum tagUSB_PID_UNIFY_IF_PROT_T {
	USB_IF_PROTOCOL_VOID		= 0x00,
	USB_IF_PROTOCOL_3G_DIAG		= 0x03,
	USB_IF_PROTOCOL_3G_GPS		= 0x05,
	USB_IF_PROTOCOL_CTRL		= 0x06,
	USB_IF_PROTOCOL_BLUETOOTH	= 0x0A,
	USB_IF_PROTOCOL_MODEM		= 0x10,
	USB_IF_PROTOCOL_PCUI		= 0x12,
	USB_IF_PROTOCOL_DIAG		= 0x13,
	USB_IF_PROTOCOL_GPS		= 0x14,
	USB_IF_PROTOCOL_CDMA_LOG	= 0x17,
	USB_IF_PROTOCOL_SKYTONE		= 0x1e,
	USB_IF_PROTOCOL_HW_MODEM	= 0x21,
	USB_IF_PROTOCOL_HW_PCUI		= 0x22,
	USB_IF_PROTOCOL_HW_DIAG		= 0x23,
	USB_IF_PROTOCOL_CDROM		= 0xA1,
	USB_IF_PROTOCOL_SDRAM		= 0xA2,
	USB_IF_PROTOCOL_RNDIS		= 0xA3,

	USB_IF_PROTOCOL_NOPNP		= 0xFF
} USB_PID_UNIFY_IF_PROT_T;


typedef struct usb_enum_stat {
	char *fd_name;                  /* function drvier file name */
	unsigned usb_intf_id;           /* usb interface id */
	unsigned is_enum;               /* whether the dev is enum */
} usb_enum_stat_t;


/* notify interface */
void bsp_usb_register_notify(struct notifier_block *nb);
void bsp_usb_unregister_notify(struct notifier_block *nb);

/* usb status change interface*/
void bsp_usb_status_change(int status);

/* usb enum done interface */
void bsp_usb_init_enum_stat(void);
int bsp_usb_is_all_enum(void);
int bsp_usb_is_all_disable(void);
void bsp_usb_add_setup_dev_fdname(unsigned intf_id, char *fd_name);
static inline void bsp_usb_add_setup_dev(unsigned intf_id)
{
	bsp_usb_add_setup_dev_fdname(intf_id, __FILE__);
}
void bsp_usb_set_enum_stat(unsigned intf_id, int enum_stat);
void bsp_usb_set_last_cdev_name(char *dev_name);

#endif /* __USB_VENDOR_H__ */
