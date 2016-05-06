/*
 * f_acm.c -- USB CDC serial (ACM) function driver
 *
 * Copyright (C) 2003 Al Borchers (alborchers@steinerpoint.com)
 * Copyright (C) 2008 by David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 * Copyright (C) 2009 by Samsung Electronics
 * Author: Michal Nazarewicz (mina86@mina86.com)
 *
 * This software is distributed under the terms of the GNU General
 * Public License ("GPL") as published by the Free Software Foundation,
 * either version 2 of that License or (at your option) any later version.
 */

/* #define VERBOSE_DEBUG */

#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/err.h>

#include "gadget_chips.h"
#include "balong_acm.h"

#ifdef DEBUG
#define D(format, arg...) pr_info("[%s]" format, __func__, ##arg)
#else
#define D(format, arg...) do {} while (0)
#endif

extern int gserial_line_state(struct gserial *gser, u8 port_num, u32 state);
/*
 * This CDC ACM function support just wraps control functions and
 * notifications around the generic serial-over-usb code.
 *
 * Because CDC ACM is standardized by the USB-IF, many host operating
 * systems have drivers for it.  Accordingly, ACM is the preferred
 * interop solution for serial-port type connections.  The control
 * models are often not necessary, and in any case don't do much in
 * this bare-bones implementation.
 *
 * Note that even MS-Windows has some support for ACM.  However, that
 * support is somewhat broken because when you use ACM in a composite
 * device, having multiple interfaces confuses the poor OS.  It doesn't
 * seem to understand CDC Union descriptors.  The new "association"
 * descriptors (roughly equivalent to CDC Unions) may sometimes help.
 */

struct f_acm {
	struct gserial          port;
	u8              ctrl_id, data_id;
	u8              port_num;

	u8              pending;

	/* lock is mostly for pending and notify_req ... they get accessed
	 * by callbacks both from tty (open/close/break) under its spinlock,
	 * and notify_req.complete() which can't use that lock.
	 */
	spinlock_t          lock;

	int             support_notify;

	struct usb_ep           *notify;
	struct usb_request      *notify_req;

	int (*pending_notify)(struct f_acm *acm);
	/* cdc vendor flow control notify */
	u32             rx_is_on;
	u32             tx_is_on;

	struct usb_cdc_line_coding  port_line_coding;   /* 8-N-1 etc */

	/* SetControlLineState request -- CDC 1.1 section 6.2.14 (INPUT) */
	u16             port_handshake_bits;

	/* SerialState notification -- CDC 1.1 section 6.3.5 (OUTPUT) */
	u16             serial_state;
#define ACM_CTRL_BRK        (1 << 2)
#define ACM_CTRL_DSR        (1 << 1)
#define ACM_CTRL_DCD        (1 << 0)
};

struct acm_name_type_tbl g_acm_cdev_type_table[ACM_CDEV_COUNT] = {
	/* name			type(protocol id) */
	{"acm_at",		USB_IF_PROTOCOL_PCUI},		/*PC UI interface*/
	{"acm_3g_diag",		USB_IF_PROTOCOL_3G_DIAG},	/*3G Application interface*/
	{"acm_a_shell",		USB_IF_PROTOCOL_3G_GPS},	/*3G gps inerface*/
	{"acm_c_shell",		USB_IF_PROTOCOL_BLUETOOTH},	/*Bluetooth interface*/
	{"acm_ctrl",		USB_IF_PROTOCOL_CTRL},		/*Control interface*/
	{"acm_4g_diag",		USB_IF_PROTOCOL_DIAG},		/*Application interface*/
	{"acm_gps",		USB_IF_PROTOCOL_GPS},		/*GPS interface*/
	{"acm_cdma_log",	USB_IF_PROTOCOL_CDMA_LOG},	/*CDMA log interface*/
	{"acm_skytone",		USB_IF_PROTOCOL_SKYTONE},
	{"acm_modem",		USB_IF_PROTOCOL_MODEM},
};

static int g_acm_is_single_interface = ACM_IS_SINGLE_INTF;

int is_modem_port(unsigned int port_num)
{
	if (port_num >= ACM_CDEV_COUNT)
		return 0;
	return (g_acm_cdev_type_table[port_num].type == USB_IF_PROTOCOL_MODEM);
}

/* is acm_a_shell port ? yes or no */
int is_a_shell_cdma_port(unsigned int port_num)
{
	enum tagUSB_PID_UNIFY_IF_PROT_T ptype = USB_IF_PROTOCOL_NOPNP;
	if (port_num >= ACM_CDEV_COUNT)
		return 0;
	ptype = g_acm_cdev_type_table[port_num].type;
	return (ptype == USB_IF_PROTOCOL_3G_GPS)
		|| (ptype == USB_IF_PROTOCOL_CDMA_LOG);
}

static inline int is_support_notify(unsigned int port_num)
{
	return is_modem_port(port_num);
}

/* function name should be verb + noun */
static inline unsigned char GET_ACM_TYPE(struct f_acm *acm)
{
	return (unsigned char)g_acm_cdev_type_table[acm->port_num].type;
}

unsigned char ACM_CDEV_GET_TYPE(unsigned int index)
{
	if (index >= ACM_CDEV_COUNT)
		return 0;
	return (unsigned char)g_acm_cdev_type_table[index].type;
}

char *ACM_CDEV_GET_NAME(unsigned int index)
{
	if ((index >= ACM_CDEV_COUNT)
			|| (g_acm_cdev_type_table[index].name == NULL))
		return "unknown";
	else
		return g_acm_cdev_type_table[index].name;
}

static inline struct f_acm *func_to_acm(struct usb_function *f)
{
	return container_of(f, struct f_acm, port.func);
}

static inline struct f_acm *port_to_acm(struct gserial *p)
{
	return container_of(p, struct f_acm, port);
}

/*-------------------------------------------------------------------------*/

/* notification endpoint uses smallish and infrequent fixed-size messages */

#define GS_NOTIFY_INTERVAL_MS       32
/* only notification + 2 bytes(10)isn't enough, flowctrol need 16 bytes  */
#define GS_NOTIFY_MAXPACKET     64

/* interface and class descriptors: */

static struct usb_interface_assoc_descriptor acm_iad_descriptor = {
	.bLength =      sizeof(acm_iad_descriptor),
	.bDescriptorType =  USB_DT_INTERFACE_ASSOCIATION,

	/* .bFirstInterface =   DYNAMIC, */
	.bInterfaceCount =  2,
	.bFunctionClass =   USB_CLASS_COMM,
	.bFunctionSubClass =    USB_CDC_SUBCLASS_ACM,
	.bFunctionProtocol =    USB_CDC_ACM_PROTO_AT_V25TER,
	/* .iFunction =     DYNAMIC */
};


static struct usb_interface_descriptor acm_control_interface_desc = {
	.bLength =      USB_DT_INTERFACE_SIZE,
	.bDescriptorType =  USB_DT_INTERFACE,
	/* .bInterfaceNumber = DYNAMIC */
	.bNumEndpoints =    1,
	.bInterfaceClass =  USB_CLASS_COMM,
	.bInterfaceSubClass =   USB_CDC_SUBCLASS_ACM,
	.bInterfaceProtocol =   USB_CDC_ACM_PROTO_AT_V25TER,
	/* .iInterface = DYNAMIC */
};

static struct usb_interface_descriptor acm_data_interface_desc = {
	.bLength =      USB_DT_INTERFACE_SIZE,
	.bDescriptorType =  USB_DT_INTERFACE,
	/* .bInterfaceNumber = DYNAMIC */
	.bNumEndpoints =    2,
	.bInterfaceClass =  USB_CLASS_CDC_DATA,
	.bInterfaceSubClass =   0,
	.bInterfaceProtocol =   0,
	/* .iInterface = DYNAMIC */
};


static struct usb_cdc_header_desc acm_header_desc = {
	.bLength =      sizeof(acm_header_desc),
	.bDescriptorType =  USB_DT_CS_INTERFACE,
	.bDescriptorSubType =   USB_CDC_HEADER_TYPE,
	.bcdCDC =       cpu_to_le16(0x0110),
};

static struct usb_cdc_call_mgmt_descriptor
		acm_call_mgmt_descriptor = {
	.bLength =      sizeof(acm_call_mgmt_descriptor),
	.bDescriptorType =  USB_DT_CS_INTERFACE,
	.bDescriptorSubType =   USB_CDC_CALL_MANAGEMENT_TYPE,
	.bmCapabilities =   0,
	/* .bDataInterface = DYNAMIC */
};

static struct usb_cdc_acm_descriptor acm_descriptor = {
	.bLength =      sizeof(acm_descriptor),
	.bDescriptorType =  USB_DT_CS_INTERFACE,
	.bDescriptorSubType =   USB_CDC_ACM_TYPE,
	.bmCapabilities =   USB_CDC_CAP_LINE,
};

static struct usb_cdc_union_desc acm_union_desc = {
	.bLength =      sizeof(acm_union_desc),
	.bDescriptorType =  USB_DT_CS_INTERFACE,
	.bDescriptorSubType =   USB_CDC_UNION_TYPE,
	/* .bMasterInterface0 = DYNAMIC */
	/* .bSlaveInterface0 =  DYNAMIC */
};


static struct usb_interface_descriptor acm_single_interface_desc = {
	.bLength =      USB_DT_INTERFACE_SIZE,
	.bDescriptorType =  USB_DT_INTERFACE,
	/* .bInterfaceNumber = DYNAMIC */
	/* .bNumEndpoints = DYNAMIC, */
	.bInterfaceClass =  0xff,
	.bInterfaceSubClass =   0x02,
	.bInterfaceProtocol =   0x01,
	/* .iInterface = DYNAMIC */
};

/* full speed support: */


static struct usb_endpoint_descriptor acm_fs_notify_desc = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bEndpointAddress = USB_DIR_IN,
	.bmAttributes =     USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize =   cpu_to_le16(GS_NOTIFY_MAXPACKET),
	.bInterval =        GS_NOTIFY_INTERVAL_MS,
};

static struct usb_endpoint_descriptor acm_fs_in_desc = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bEndpointAddress = USB_DIR_IN,
	.bmAttributes =     USB_ENDPOINT_XFER_BULK,
};

static struct usb_endpoint_descriptor acm_fs_out_desc = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bEndpointAddress = USB_DIR_OUT,
	.bmAttributes =     USB_ENDPOINT_XFER_BULK,
};

static struct usb_descriptor_header **acm_fs_cur_function;
static struct usb_descriptor_header *acm_fs_function_single[] = {
	(struct usb_descriptor_header *) &acm_single_interface_desc,
	(struct usb_descriptor_header *) &acm_header_desc,
	(struct usb_descriptor_header *) &acm_descriptor,
	(struct usb_descriptor_header *) &acm_call_mgmt_descriptor,
	(struct usb_descriptor_header *) &acm_union_desc,
	(struct usb_descriptor_header *) &acm_fs_in_desc,
	(struct usb_descriptor_header *) &acm_fs_out_desc,
	NULL,
};

static struct usb_descriptor_header *acm_fs_function_single_notify[] = {
	(struct usb_descriptor_header *) &acm_single_interface_desc,
	(struct usb_descriptor_header *) &acm_header_desc,
	(struct usb_descriptor_header *) &acm_descriptor,
	(struct usb_descriptor_header *) &acm_call_mgmt_descriptor,
	(struct usb_descriptor_header *) &acm_union_desc,
	(struct usb_descriptor_header *) &acm_fs_notify_desc,
	(struct usb_descriptor_header *) &acm_fs_in_desc,
	(struct usb_descriptor_header *) &acm_fs_out_desc,
	NULL,
};

static struct usb_descriptor_header *acm_fs_function[] = {
	(struct usb_descriptor_header *) &acm_iad_descriptor,
	(struct usb_descriptor_header *) &acm_control_interface_desc,
	(struct usb_descriptor_header *) &acm_header_desc,
	(struct usb_descriptor_header *) &acm_call_mgmt_descriptor,
	(struct usb_descriptor_header *) &acm_descriptor,
	(struct usb_descriptor_header *) &acm_union_desc,
	(struct usb_descriptor_header *) &acm_fs_notify_desc,
	(struct usb_descriptor_header *) &acm_data_interface_desc,
	(struct usb_descriptor_header *) &acm_fs_in_desc,
	(struct usb_descriptor_header *) &acm_fs_out_desc,
	NULL,
};

/* high speed support: */
static struct usb_endpoint_descriptor acm_hs_notify_desc = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bEndpointAddress = USB_DIR_IN,
	.bmAttributes =     USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize =   cpu_to_le16(GS_NOTIFY_MAXPACKET),
	.bInterval =        USB_MS_TO_HS_INTERVAL(GS_NOTIFY_INTERVAL_MS),
};

static struct usb_endpoint_descriptor acm_hs_in_desc = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bmAttributes =     USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =   cpu_to_le16(512),
};

static struct usb_endpoint_descriptor acm_hs_out_desc = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bmAttributes =     USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =   cpu_to_le16(512),
};

static struct usb_descriptor_header **acm_hs_cur_function;
static struct usb_descriptor_header *acm_hs_function_single[] = {
	(struct usb_descriptor_header *) &acm_single_interface_desc,
	(struct usb_descriptor_header *) &acm_header_desc,
	(struct usb_descriptor_header *) &acm_descriptor,
	(struct usb_descriptor_header *) &acm_call_mgmt_descriptor,
	(struct usb_descriptor_header *) &acm_union_desc,
	(struct usb_descriptor_header *) &acm_hs_in_desc,
	(struct usb_descriptor_header *) &acm_hs_out_desc,
	NULL,
};

static struct usb_descriptor_header *acm_hs_function_single_notify[] = {
	(struct usb_descriptor_header *) &acm_single_interface_desc,
	(struct usb_descriptor_header *) &acm_header_desc,
	(struct usb_descriptor_header *) &acm_descriptor,
	(struct usb_descriptor_header *) &acm_call_mgmt_descriptor,
	(struct usb_descriptor_header *) &acm_union_desc,
	(struct usb_descriptor_header *) &acm_hs_notify_desc,
	(struct usb_descriptor_header *) &acm_hs_in_desc,
	(struct usb_descriptor_header *) &acm_hs_out_desc,
	NULL,
};

static struct usb_descriptor_header *acm_hs_function[] = {
	(struct usb_descriptor_header *) &acm_iad_descriptor,
	(struct usb_descriptor_header *) &acm_control_interface_desc,
	(struct usb_descriptor_header *) &acm_header_desc,
	(struct usb_descriptor_header *) &acm_call_mgmt_descriptor,
	(struct usb_descriptor_header *) &acm_descriptor,
	(struct usb_descriptor_header *) &acm_union_desc,
	(struct usb_descriptor_header *) &acm_hs_notify_desc,
	(struct usb_descriptor_header *) &acm_data_interface_desc,
	(struct usb_descriptor_header *) &acm_hs_in_desc,
	(struct usb_descriptor_header *) &acm_hs_out_desc,
	NULL,
};

static struct usb_endpoint_descriptor acm_ss_in_desc = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bmAttributes =     USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =   cpu_to_le16(1024),
};

static struct usb_endpoint_descriptor acm_ss_out_desc = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bmAttributes =     USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =   cpu_to_le16(1024),
};

static struct usb_ss_ep_comp_descriptor acm_ss_bulk_comp_desc = {
	.bLength =              sizeof(acm_ss_bulk_comp_desc),
	.bDescriptorType =      USB_DT_SS_ENDPOINT_COMP,
};



static struct usb_descriptor_header *acm_ss_function[] = {
	(struct usb_descriptor_header *) &acm_iad_descriptor,
	(struct usb_descriptor_header *) &acm_control_interface_desc,
	(struct usb_descriptor_header *) &acm_header_desc,
	(struct usb_descriptor_header *) &acm_call_mgmt_descriptor,
	(struct usb_descriptor_header *) &acm_descriptor,
	(struct usb_descriptor_header *) &acm_union_desc,
	(struct usb_descriptor_header *) &acm_hs_notify_desc,
	(struct usb_descriptor_header *) &acm_ss_bulk_comp_desc,
	(struct usb_descriptor_header *) &acm_data_interface_desc,
	(struct usb_descriptor_header *) &acm_ss_in_desc,
	(struct usb_descriptor_header *) &acm_ss_bulk_comp_desc,
	(struct usb_descriptor_header *) &acm_ss_out_desc,
	(struct usb_descriptor_header *) &acm_ss_bulk_comp_desc,
	NULL,
};


static struct usb_descriptor_header **acm_ss_cur_function;
static struct usb_descriptor_header *acm_ss_function_single[] = {
	(struct usb_descriptor_header *) &acm_single_interface_desc,
	(struct usb_descriptor_header *) &acm_header_desc,
	(struct usb_descriptor_header *) &acm_descriptor,
	(struct usb_descriptor_header *) &acm_call_mgmt_descriptor,
	(struct usb_descriptor_header *) &acm_union_desc,
	(struct usb_descriptor_header *) &acm_ss_in_desc,
	(struct usb_descriptor_header *) &acm_ss_bulk_comp_desc,
	(struct usb_descriptor_header *) &acm_ss_out_desc,
	(struct usb_descriptor_header *) &acm_ss_bulk_comp_desc,
	NULL,
};

static struct usb_descriptor_header *acm_ss_function_single_notify[] = {
	(struct usb_descriptor_header *) &acm_single_interface_desc,
	(struct usb_descriptor_header *) &acm_header_desc,
	(struct usb_descriptor_header *) &acm_descriptor,
	(struct usb_descriptor_header *) &acm_call_mgmt_descriptor,
	(struct usb_descriptor_header *) &acm_union_desc,
	(struct usb_descriptor_header *) &acm_hs_notify_desc,
	(struct usb_descriptor_header *) &acm_ss_bulk_comp_desc,
	(struct usb_descriptor_header *) &acm_ss_in_desc,
	(struct usb_descriptor_header *) &acm_ss_bulk_comp_desc,
	(struct usb_descriptor_header *) &acm_ss_out_desc,
	(struct usb_descriptor_header *) &acm_ss_bulk_comp_desc,
	NULL,
};


/* string descriptors: */

#define ACM_CTRL_IDX    0
#define ACM_DATA_IDX    1
#define ACM_IAD_IDX 2

/* static strings, in UTF-8 */
static struct usb_string acm_string_defs[] = {
	[ACM_CTRL_IDX].s = "CDC Abstract Control Model (ACM)",
	[ACM_DATA_IDX].s = "CDC ACM Data",
	[ACM_IAD_IDX].s = "CDC Serial",
};

static struct usb_gadget_strings acm_string_table = {
	.language =     0x0409, /* en-us */
	.strings =      acm_string_defs,
};

static struct usb_gadget_strings *acm_strings[] = {
	&acm_string_table,
	NULL,
};

/*-------------------------------------------------------------------------*/

/* ACM control ... data handling is delegated to tty library code.
 * The main task of this function is to activate and deactivate
 * that code based on device state; track parameters like line
 * speed, handshake state, and so on; and issue notifications.
 */
static void acm_complete_set_line_coding(struct usb_ep *ep,
			struct usb_request *req)
{
	struct f_acm    *acm = ep->driver_data;
	struct usb_composite_dev *cdev = acm->port.func.config->cdev;

	D("+\n");

	if (req->status != 0) {
		DBG(cdev, "acm ttyGS%d completion, err %d\n",
			acm->port_num, req->status);
		return;
	}

	/* normal completion */
	if (req->actual != sizeof(acm->port_line_coding)) {
		DBG(cdev, "acm ttyGS%d short resp, len %d\n",
			acm->port_num, req->actual);
		usb_ep_set_halt(ep);
	} else {
		struct usb_cdc_line_coding  *value = req->buf;

		/* REVISIT:  we currently just remember this data.
		 * If we change that, (a) validate it first, then
		 * (b) update whatever hardware needs updating,
		 * (c) worry about locking.  This is information on
		 * the order of 9600-8-N-1 ... most of which means
		 * nothing unless we control a real RS232 line.
		 */
		acm->port_line_coding = *value;
	}
	D("-\n");
}

static void acm_complete_nop(struct usb_ep *ep,
							 struct usb_request *req)
{
}

static int acm_setup(struct usb_function *f, const struct usb_ctrlrequest *ctrl)
{
	struct f_acm        *acm = func_to_acm(f);
	struct usb_composite_dev *cdev = f->config->cdev;
	struct usb_request  *req = cdev->req;
	int         value = -EOPNOTSUPP;
	u16         w_index = le16_to_cpu(ctrl->wIndex);
	u16         w_value = le16_to_cpu(ctrl->wValue);
	u16         w_length = le16_to_cpu(ctrl->wLength);

	D("+\n");
	D("ctrl: %02x %02x %04x %04x %04x\n", ctrl->bRequestType,
			ctrl->bRequest, ctrl->wValue, ctrl->wIndex,
			ctrl->wLength);

	/* composite driver infrastructure handles everything except
	 * CDC class messages; interface activation uses set_alt().
	 *
	 * Note CDC spec table 4 lists the ACM request profile.  It requires
	 * encapsulated command support ... we don't handle any, and respond
	 * to them by stalling.  Options include get/set/clear comm features
	 * (not that useful) and SEND_BREAK.
	 */
	switch ((ctrl->bRequestType << 8) | ctrl->bRequest) {

	case ((USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE) << 8)
			| 0xa3:
	case ((USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
			| 0x02:
	case ((USB_DIR_OUT | USB_TYPE_STANDARD | USB_RECIP_INTERFACE) << 8)
			| 0x81:
		pr_debug("f_acm request: wValue: 0x%04x, wIndex: 0x%04x, wLength: 0x%04x\n",
				 w_value, w_index, w_length);
		value = w_length;
		cdev->gadget->ep0->driver_data = acm;
		req->complete = acm_complete_nop;
		break;

		/* SET_LINE_CODING ... just read and save what the host sends */
	case ((USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
			| USB_CDC_REQ_SET_LINE_CODING:
		if (w_length != sizeof(struct usb_cdc_line_coding)
			|| w_index != acm->ctrl_id)
			goto invalid;

		value = w_length;
		cdev->gadget->ep0->driver_data = acm;
		req->complete = acm_complete_set_line_coding;
		break;

		/* GET_LINE_CODING ... return what host sent, or initial value */
	case ((USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
			| USB_CDC_REQ_GET_LINE_CODING:
		if (w_index != acm->ctrl_id)
			goto invalid;

		value = min_t(unsigned, w_length,
					  sizeof(struct usb_cdc_line_coding));
		memcpy(req->buf, &acm->port_line_coding, value);
		break;

		/* SET_CONTROL_LINE_STATE ... save what the host sent */
	case ((USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
			| USB_CDC_REQ_SET_CONTROL_LINE_STATE:
		if (w_index != (u16)acm->ctrl_id)
			goto invalid;

		value = 0;

		/* FIXME we should not allow data to flow until the
		 * host sets the ACM_CTRL_DTR bit; and when it clears
		 * that bit, we should return to that no-flow state.
		 */
		acm->port_handshake_bits = w_value;
		gacm_cdev_line_state(&acm->port, acm->port_num, (u32)w_value);
		break;

	default:
invalid:
		VDBG(cdev, "invalid control req%02x.%02x v%04x i%04x l%d\n",
			 ctrl->bRequestType, ctrl->bRequest,
			 w_value, w_index, w_length);
	}

	/* respond with data transfer or status phase? */
	if (value >= 0) {
		DBG(cdev, "acm ttyGS%d req%02x.%02x v%04x i%04x l%d\n",
			acm->port_num, ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
		req->zero = 0;
		req->length = value;
		value = usb_ep_queue(cdev->gadget->ep0, req, GFP_ATOMIC);
		if (value < 0)
			ERROR(cdev, "acm response on ttyGS%d, err %d\n",
				  acm->port_num, value);
	}

	/* device either stalls (value < 0) or reports success */
	D("-\n");
	return value;
}

static void acm_suspend(struct usb_function *f)
{
	struct f_acm *acm = func_to_acm(f);
	gacm_cdev_suspend_notify(&acm->port);
}

static void acm_resume(struct usb_function *f)
{
	struct f_acm *acm = func_to_acm(f);
	gacm_cdev_resume_notify(&acm->port);
}
static int acm_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct f_acm        *acm = func_to_acm(f);
	struct usb_composite_dev *cdev = f->config->cdev;
	bool is_setting = 0;
	int ret;

	D("+\n");
	/* we know alt == 0, so this is an activation or a reset */

	/* if it is single interface, intf, acm->ctrl_id and acm->data_id
	 * are the same, so we can setting data and notify interface in the same time.
	 *
	 * if it is multi interface, acm->ctrl_id and acm->data_id are different,
	 * so the setting is go ahead in different times.
	 */
	if (intf == acm->ctrl_id) {
		is_setting = 1;
		if (acm->notify) {
			if (acm->notify->driver_data) {
				VDBG(cdev, "reset acm control interface %d\n", intf);
				usb_ep_disable(acm->notify);
			} else {
				VDBG(cdev, "init acm ctrl interface %d\n", intf);
				if (config_ep_by_speed(cdev->gadget, f, acm->notify))
					return -EINVAL;
			}
			ret = usb_ep_enable(acm->notify);
			if (ret < 0) {
				ERROR(cdev, "Enable acm interface ep failed\n");
				return ret;
			}
			acm->notify->driver_data = acm;
		}
	}

	if (intf == acm->data_id) {
		is_setting = 1;
		if (acm->port.in->driver_data) {
			DBG(cdev, "reset acm ttyGS%d\n", acm->port_num);
			gacm_cdev_disconnect(&acm->port);
		}
		if (!acm->port.in->desc || !acm->port.out->desc) {
			DBG(cdev, "activate acm ttyGS%d\n", acm->port_num);
			if (config_ep_by_speed(cdev->gadget, f,
								   acm->port.in) ||
				config_ep_by_speed(cdev->gadget, f,
								   acm->port.out)) {
				acm->port.in->desc = NULL;
				acm->port.out->desc = NULL;
				return -EINVAL;
			}
		}
		gacm_cdev_connect(&acm->port, acm->port_num);

		bsp_usb_set_enum_stat(acm->data_id, 1);
	}

	if (!is_setting)
		return -EINVAL;

	D("-\n");
	return 0;
}

static void acm_disable(struct usb_function *f)
{
	struct f_acm    *acm = func_to_acm(f);
	struct usb_composite_dev *cdev = f->config->cdev;
	D("+\n");

	DBG(cdev, "acm ttyGS%d deactivated\n", acm->port_num);

	gacm_cdev_disconnect(&acm->port);

	if (acm->notify) {
		usb_ep_disable(acm->notify);
		acm->notify->driver_data = NULL;
	}

	bsp_usb_set_enum_stat(acm->data_id, 0);

	D("-\n");
}

/*-------------------------------------------------------------------------*/

/**
 * acm_cdc_notify - issue CDC notification to host
 * @acm: wraps host to be notified
 * @type: notification type
 * @value: Refer to cdc specs, wValue field.
 * @data: data to be sent
 * @length: size of data
 * Context: irqs blocked, acm->lock held, acm_notify_req non-null
 *
 * Returns zero on success or a negative errno.
 *
 * See section 6.3.5 of the CDC 1.1 specification for information
 * about the only notification we issue:  SerialState change.
 */
static int acm_cdc_notify(struct f_acm *acm, u8 type, u16 value,
				void *data, unsigned length, bool is_vendor)
{
	struct usb_ep           *ep = acm->notify;
	struct usb_request      *req;
	struct usb_cdc_notification *notify;
	const unsigned          len = sizeof(*notify) + length;
	void                *buf;
	int             status;
	D("+\n");

	req = acm->notify_req;
	acm->notify_req = NULL;
	acm->pending = false;

	req->length = len;
	notify = req->buf;
	buf = notify + 1;

	notify->bmRequestType = USB_DIR_IN
			| (is_vendor ? USB_TYPE_VENDOR : USB_TYPE_CLASS)
			| USB_RECIP_INTERFACE;
	notify->bNotificationType = type;
	notify->wValue = cpu_to_le16(value);
	notify->wIndex = cpu_to_le16(acm->ctrl_id);
	notify->wLength = cpu_to_le16(length);

	if (length && data)
		memcpy(buf, data, length);

	/* ep_queue() can complete immediately if it fills the fifo... */
	spin_unlock(&acm->lock);
	status = usb_ep_queue(ep, req, GFP_ATOMIC);
	spin_lock(&acm->lock);

	if (status < 0) {
		ERROR(acm->port.func.config->cdev,
			  "acm ttyGS%d can't notify serial state, %d\n",
			  acm->port_num, status);
		acm->notify_req = req;
	}

	D("-\n");
	return status;
}

static int acm_notify_serial_state(struct f_acm *acm)
{
	struct usb_composite_dev *cdev = acm->port.func.config->cdev;
	int         status;
	D("+\n");

	spin_lock(&acm->lock);
	if (acm->notify_req) {
		DBG(cdev, "acm ttyGS%d serial state %04x\n",
			acm->port_num, acm->serial_state);
		status = acm_cdc_notify(acm, USB_CDC_NOTIFY_SERIAL_STATE,
					0, &acm->serial_state, sizeof(acm->serial_state), 0);
	} else {
		acm->pending = true;
		acm->pending_notify = acm_notify_serial_state;
		status = 0;
	}
	spin_unlock(&acm->lock);
	D("-\n");
	return status;
}

static int acm_notify_flow_control(struct f_acm *acm)
{
	int status;
	u16 value;

	D("+\n");

	spin_lock(&acm->lock);
	if (acm->notify_req) {
		/* send flow control messages adapt JUNGO host vcom driver */
		value = (acm->rx_is_on ? 0x1 : 0x0) | (acm->tx_is_on ? 0x2 : 0x0);
		status = acm_cdc_notify(acm, USB_CDC_VENDOR_NTF_FLOW_CONTROL,
				value, NULL, 0, 1);
	} else {
		acm->pending = true;
		acm->pending_notify = acm_notify_flow_control;
		status = 0;
	}
	spin_unlock(&acm->lock);
	D("-\n");
	return status;
}

static void acm_cdc_notify_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct f_acm *acm = req->context;
	u8 doit = false;
	D("+\n");

	/* on this call path we do NOT hold the port spinlock,
	 * which is why ACM needs its own spinlock
	 */
	spin_lock(&acm->lock);
	if (req->status != -ESHUTDOWN)
		doit = acm->pending;
	acm->notify_req = req;
	spin_unlock(&acm->lock);

	if (doit && acm->pending_notify)
		acm->pending_notify(acm);
	D("-\n");
}

static void acm_connect(struct gserial *port)
{
	struct f_acm *acm = port_to_acm(port);
	D("+\n");

	acm->serial_state |= ACM_CTRL_DSR | ACM_CTRL_DCD;
	acm_notify_serial_state(acm);
	D("-\n");
}

static void acm_disconnect(struct gserial *port)
{
	struct f_acm *acm = port_to_acm(port);
	D("+\n");

	acm->serial_state &= ~(ACM_CTRL_DSR | ACM_CTRL_DCD);
	acm_notify_serial_state(acm);
	D("-\n");
}

static void acm_notify_state(struct gserial *port, u16 state)
{
	struct f_acm        *acm = port_to_acm(port);
	D("+\n");

	acm->serial_state = state;
	(void)acm_notify_serial_state(acm);
	D("-\n");
}

static void acm_flow_control(struct gserial *port, u32 rx_is_on, u32 tx_is_on)
{
	struct f_acm        *acm = port_to_acm(port);
	D("+\n");

	acm->rx_is_on = rx_is_on;
	acm->tx_is_on = tx_is_on;
	(void)acm_notify_flow_control(acm);
	D("-\n");
}

static int acm_send_break(struct gserial *port, int duration)
{
	struct f_acm        *acm = port_to_acm(port);
	u16         state;
	D("+\n");

	state = acm->serial_state;
	state &= ~ACM_CTRL_BRK;
	if (duration)
		state |= ACM_CTRL_BRK;

	acm->serial_state = state;

	D("-\n");

	return acm_notify_serial_state(acm);
}

/*-------------------------------------------------------------------------*/

/*
 * choose descriptors according to single interface or not,
 * and support notify or not.
 */
static inline void acm_set_config_vendor(struct f_acm *acm)
{
	D("+\n");
	if (g_acm_is_single_interface) {
		if (acm->support_notify) {
			/* bulk in + bulk out + interrupt in */
			acm_single_interface_desc.bNumEndpoints = 3;
			acm_fs_cur_function = acm_fs_function_single_notify;
			acm_hs_cur_function = acm_hs_function_single_notify;
			acm_ss_cur_function = acm_ss_function_single_notify;
		} else {
			/* bulk in + bulk out */
			acm_single_interface_desc.bNumEndpoints = 2;
			acm_fs_cur_function = acm_fs_function_single;
			acm_hs_cur_function = acm_hs_function_single;
			acm_ss_cur_function = acm_ss_function_single;
		}

		acm_single_interface_desc.bInterfaceClass = 0xFF;
		acm_single_interface_desc.bInterfaceSubClass = 0x13;
		acm_single_interface_desc.bInterfaceProtocol = GET_ACM_TYPE(acm);
	} else {
		acm_control_interface_desc.bInterfaceClass = 0xFF;
		acm_control_interface_desc.bInterfaceSubClass = 0x13;
		acm_control_interface_desc.bInterfaceProtocol = GET_ACM_TYPE(acm);
		acm_fs_cur_function = acm_fs_function;
		acm_hs_cur_function = acm_hs_function;
		acm_ss_cur_function = acm_ss_function;

	}
	D("-\n");
}

/* ACM function driver setup/binding */
static int
acm_bind(struct usb_configuration *c, struct usb_function *f)
{
	struct usb_composite_dev *cdev = c->cdev;
	struct f_acm        *acm = func_to_acm(f);
	struct usb_string   *us;
	int         status;
	struct usb_ep       *ep;

	D("+\n");


	/* REVISIT might want instance-specific strings to help
	 * distinguish instances ...
	 */

	/* maybe allocate device-global string IDs, and patch descriptors */
	us = usb_gstrings_attach(cdev, acm_strings,
				ARRAY_SIZE(acm_string_defs));
	if (IS_ERR(us))
		return PTR_ERR(us);
	acm_control_interface_desc.iInterface = us[ACM_CTRL_IDX].id;
	acm_data_interface_desc.iInterface = us[ACM_DATA_IDX].id;
	acm_iad_descriptor.iFunction = us[ACM_IAD_IDX].id;

	/* allocate instance-specific interface IDs, and patch descriptors */
	status = usb_interface_id(c, f);
	if (status < 0)
		goto fail;

	D("interface id: %d\n", status);

	if (g_acm_is_single_interface) {
		D("single interface\n");
		acm->ctrl_id = acm->data_id = status;
		acm_single_interface_desc.bInterfaceNumber = status;
		acm_call_mgmt_descriptor.bDataInterface = status;
	} else {
		acm->ctrl_id = (u8)status;
		acm_iad_descriptor.bFirstInterface = status;

		acm_control_interface_desc.bInterfaceNumber = status;
		acm_union_desc .bMasterInterface0 = status;

		status = usb_interface_id(c, f);
		if (status < 0)
			goto fail;
		acm->data_id = status;

		acm_data_interface_desc.bInterfaceNumber = status;
		acm_union_desc.bSlaveInterface0 = status;
		acm_call_mgmt_descriptor.bDataInterface = status;
	}

	bsp_usb_add_setup_dev((unsigned)acm->data_id);

	status = -ENODEV;

	/* allocate instance-specific endpoints */
	D("to ep autoconfig\n");
	ep = usb_ep_autoconfig(cdev->gadget, &acm_fs_in_desc);
	if (!ep)
		goto fail;
	acm->port.in = ep;
	ep->driver_data = cdev; /* claim */

	ep = usb_ep_autoconfig(cdev->gadget, &acm_fs_out_desc);
	if (!ep)
		goto fail;
	acm->port.out = ep;
	ep->driver_data = cdev; /* claim */

	if (acm->support_notify) {
		ep = usb_ep_autoconfig(cdev->gadget, &acm_fs_notify_desc);
		if (!ep)
			goto fail;
		acm->notify = ep;
		ep->driver_data = cdev; /* claim */

		/* allocate notification */
		acm->notify_req = gs_acm_cdev_alloc_req(ep,
					sizeof(struct usb_cdc_notification) + 2,
					GFP_KERNEL);
		if (!acm->notify_req)
			goto fail;

		acm->notify_req->complete = acm_cdc_notify_complete;
		acm->notify_req->context = acm;
	} else {
		acm->notify = NULL;
		acm->notify_req = NULL;
	}

	/* support all relevant hardware speeds... we expect that when
	 * hardware is dual speed, all bulk-capable endpoints work at
	 * both speeds
	 */
	D("do desc\n");
	acm_hs_in_desc.bEndpointAddress = acm_fs_in_desc.bEndpointAddress;
	acm_hs_out_desc.bEndpointAddress = acm_fs_out_desc.bEndpointAddress;

	if (acm->support_notify)
		acm_hs_notify_desc.bEndpointAddress =
			acm_fs_notify_desc.bEndpointAddress;

	acm_ss_in_desc.bEndpointAddress = acm_fs_in_desc.bEndpointAddress;
	acm_ss_out_desc.bEndpointAddress = acm_fs_out_desc.bEndpointAddress;

	D("to assign desc\n");
	acm_set_config_vendor(acm);

	status = usb_assign_descriptors(f, acm_fs_cur_function, acm_hs_cur_function,
				acm_ss_cur_function);
	if (status)
		goto fail;

	DBG(cdev, "acm_cdev%d: %s speed IN/%s OUT/%s NOTIFY/%s\n",
		acm->port_num,
		gadget_is_superspeed(c->cdev->gadget) ? "super" :
		gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
		acm->port.in->name, acm->port.out->name,
		acm->notify ? acm->notify->name : "null");

	printk(KERN_INFO "acm_cdev%d: %s speed IN/%s OUT/%s NOTIFY/%s\n",
		acm->port_num,
		gadget_is_superspeed(c->cdev->gadget) ? "super" :
		gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
		acm->port.in->name, acm->port.out->name,
		acm->notify ? acm->notify->name : "null");

	return 0;

fail:
	if (acm->notify_req)
		gs_acm_cdev_free_req(acm->notify, acm->notify_req);

	/* we might as well release our claims on endpoints */
	if (acm->notify)
		acm->notify->driver_data = NULL;
	if (acm->port.out)
		acm->port.out->driver_data = NULL;
	if (acm->port.in)
		acm->port.in->driver_data = NULL;

	ERROR(cdev, "%s/%p: can't bind, err %d\n", f->name, f, status);

	D("-\n");
	return status;
}

static void acm_unbind(struct usb_configuration *c, struct usb_function *f)
{
	struct f_acm        *acm = func_to_acm(f);
	D("+\n");
	acm_string_defs[0].id = 0;
	usb_free_all_descriptors(f);
	if (acm->notify_req)
		gs_acm_cdev_free_req(acm->notify, acm->notify_req);
	D("-\n");
}

static void acm_free_func(struct usb_function *f)
{
	struct f_acm *acm = func_to_acm(f);

	D("+\n");
	kfree(acm);
	D("-\n");
}
static struct usb_function *acm_alloc_func(struct usb_function_instance *fi)
{
	struct balong_acm_instance *inst;
	struct f_acm *acm;
	D("+\n");

	acm = kzalloc(sizeof(*acm), GFP_KERNEL);
	if (!acm)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&acm->lock);

	inst = container_of(fi, struct balong_acm_instance, func_inst);
	acm->support_notify = is_support_notify(inst->port_num);
	if (acm->support_notify) {
		acm->port.connect = acm_connect;
		acm->port.disconnect = acm_disconnect;

		acm->port.notify_state = acm_notify_state;
		acm->port.flow_control = acm_flow_control;

		acm->port.send_break = acm_send_break;

		acm->port.func.suspend = acm_suspend;
		acm->port.func.resume = acm_resume;
	}

	acm->port.func.name = "balong_acm";
	acm->port.func.strings = acm_strings;

	acm->port.func.bind = acm_bind;
	acm->port.func.set_alt = acm_set_alt;
	acm->port.func.setup = acm_setup;
	acm->port.func.disable = acm_disable;

	acm->port_num = inst->port_num;

	acm->port.func.unbind = acm_unbind;
	acm->port.func.free_func = acm_free_func;

	D("-\n");
	return &acm->port.func;
}

static void acm_free_instance(struct usb_function_instance *fi)
{
	struct balong_acm_instance *inst;
	D("+\n");

	inst = container_of(fi, struct balong_acm_instance, func_inst);
	gs_acm_cdev_free_line(inst->port_num);
	kfree(inst);
	D("-\n");
}

static struct usb_function_instance *acm_alloc_instance(void)
{
	struct balong_acm_instance *inst;
	int ret;
	D("+\n");
	inst = kzalloc(sizeof(*inst), GFP_KERNEL);
	if (!inst)
		return ERR_PTR(-ENOMEM);
	inst->func_inst.free_func_inst = acm_free_instance;

	ret = gs_acm_cdev_alloc_line(&inst->port_num);
	if (ret) {
		kfree(inst);
		return ERR_PTR(ret);
	}
	D("-\n");

	return &inst->func_inst;
}
DECLARE_USB_FUNCTION_INIT(balong_acm, acm_alloc_instance, acm_alloc_func);
MODULE_LICENSE("GPL");
