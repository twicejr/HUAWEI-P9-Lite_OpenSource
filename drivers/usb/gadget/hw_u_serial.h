/*
 * u_serial.h - interface to USB gadget "serial port"/TTY utilities
 *
 * Copyright (C) 2008 David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 *
 * This software is distributed under the terms of the GNU General
 * Public License ("GPL") as published by the Free Software Foundation,
 * either version 2 of that License or (at your option) any later version.
 */

#ifndef __U_SERIAL_H
#define __U_SERIAL_H

#include <linux/usb/composite.h>
#include <linux/usb/cdc.h>
#include "usb_vendor.h"

#define HW_MAX_U_SERIAL_PORTS	4
#define HW_ACM_IS_SINGLE		1
#define HW_ACM_SUPPORT_NOTIFY	0



struct f_serial_opts {
	struct usb_function_instance func_inst;
	u8 port_num;
};

/*
 * One non-multiplexed "serial" I/O port ... there can be several of these
 * on any given USB peripheral device, if it provides enough endpoints.
 *
 * The "u_serial" utility component exists to do one thing:  manage TTY
 * style I/O using the USB peripheral endpoints listed here, including
 * hookups to sysfs and /dev for each logical "tty" device.
 *
 * REVISIT at least ACM could support tiocmget() if needed.
 *
 * REVISIT someday, allow multiplexing several TTYs over these endpoints.
 */
struct gserial {
	struct usb_function		func;

	/* port is managed by gserial_{connect,disconnect} */
	struct gs_port			*ioport;

	struct usb_ep			*in;
	struct usb_ep			*out;

	/* REVISIT avoid this CDC-ACM support harder ... */
	struct usb_cdc_line_coding port_line_coding;	/* 9600-8-N-1 etc */

	/* notification callbacks */
	void (*connect)(struct gserial *p);
	void (*disconnect)(struct gserial *p);

	void (*notify_state)(struct gserial *p, u16 state);
	void (*flow_control)(struct gserial *p, u32 rx_is_on, u32 tx_is_on);

	int (*send_break)(struct gserial *p, int duration);
};

/* table for acm interface name and corresponding protocol */
struct acm_name_type_tbl {
	char *name;
	USB_PID_UNIFY_IF_PROT_T type;
};

/* utilities to allocate/free request and buffer */
struct usb_request *hw_gs_alloc_req(struct usb_ep *ep, unsigned len, gfp_t flags);
void hw_gs_free_req(struct usb_ep *, struct usb_request *req);

/* management of individual TTY ports */
int hw_gserial_alloc_line(unsigned char *port_line);
void hw_gserial_free_line(unsigned char port_line);

/* connect/disconnect is handled by individual functions */
int hw_gserial_connect(struct gserial *, u8 port_num);
void hw_gserial_disconnect(struct gserial *);

/* functions are bound to configurations by a config or gadget driver */
int gser_bind_config(struct usb_configuration *c, u8 port_num);
int obex_bind_config(struct usb_configuration *c, u8 port_num);

#endif /* __U_SERIAL_H */
