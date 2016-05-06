#ifndef __BALONG_ACM_H
#define __BALONG_ACM_H

#include <linux/usb/composite.h>
#include <linux/usb/cdc.h>

#include "usb_vendor.h"

#define U_ACM_CTRL_DTR  (1 << 0)
#define U_ACM_CTRL_RTS  (1 << 1)
#define U_ACM_CTRL_RING (1 << 3)

struct balong_acm_instance {
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
	struct usb_function     func;

	void                    *ioport;

	struct usb_ep           *in;
	struct usb_ep           *out;

	/* REVISIT avoid this CDC-ACM support harder ... */
	struct usb_cdc_line_coding port_line_coding;    /* 9600-8-N-1 etc */

	/* notification callbacks */
	void (*connect)(struct gserial *p);
	void (*disconnect)(struct gserial *p);

	void (*notify_state)(struct gserial *p, u16 state);
	void (*flow_control)(struct gserial *p, u32 rx_is_on, u32 tx_is_on);

	int (*send_break)(struct gserial *p, int duration);
};

struct acm_name_type_tbl {
	char *name;
	USB_PID_UNIFY_IF_PROT_T type;
};

/* utilities to allocate/free request and buffer */
struct usb_request *gs_acm_cdev_alloc_req(struct usb_ep *ep,
				unsigned len, gfp_t flags);
void gs_acm_cdev_free_req(struct usb_ep *, struct usb_request *req);

/* management of individual TTY ports */
int gs_acm_cdev_alloc_line(unsigned char *port_line);
void gs_acm_cdev_free_line(unsigned char port_line);

/* connect/disconnect is handled by individual functions */
int gacm_cdev_connect(struct gserial *, u8 port_num);
void gacm_cdev_disconnect(struct gserial *);

int gacm_cdev_line_state(struct gserial *, u8 port_num, u32 state);

void gacm_cdev_suspend_notify(struct gserial *gser);
void gacm_cdev_resume_notify(struct gserial *gser);

/* ---------------------------------------------- */
char *ACM_CDEV_GET_NAME(unsigned int index);
unsigned char ACM_CDEV_GET_TYPE(unsigned int index);
int is_modem_port(unsigned int port_num);
int is_a_shell_cdma_port(unsigned int port_num);

int gs_acm_open(unsigned int port_num);
int gs_acm_close(unsigned int port_num);
ssize_t gs_acm_read(unsigned int port_num, char *buf,
				size_t count, loff_t *ppos);
ssize_t gs_acm_write(unsigned int port_num, const char *buf,
				size_t count, loff_t *ppos);
int gs_acm_ioctl(unsigned int port_num, unsigned int cmd, unsigned long arg);

/* -------------- acm support cap --------------- */
/* max dev driver support */
#define ACM_CDEV_COUNT      10

#define ACM_IS_SINGLE_INTF          1


struct gs_acm_evt_manage {
	void *port_evt_array[ACM_CDEV_COUNT + 1];
	int port_evt_pos;
	char *name;
	spinlock_t evt_lock;
};

static inline void gs_acm_evt_init(struct gs_acm_evt_manage *evt, char *name)
{
	spin_lock_init(&evt->evt_lock);
	evt->port_evt_pos = 0;
	evt->name = name;
	memset(evt->port_evt_array, 0, sizeof(evt->port_evt_array));
}

#define gs_acm_evt_push(port, evt) __gs_acm_evt_push((void *)port, evt)
static inline void __gs_acm_evt_push(void *port, struct gs_acm_evt_manage *evt)
{
	unsigned long flags;
	int add_new = 1;
	int i;

	spin_lock_irqsave(&evt->evt_lock, flags);
	for (i = 0; i <= evt->port_evt_pos; i++) {
		if (evt->port_evt_array[i] == port) {
			add_new = 0;
			break;
		}
	}
	if (add_new) {
		evt->port_evt_array[evt->port_evt_pos] =  port;
		evt->port_evt_pos++;
	}
	spin_unlock_irqrestore(&evt->evt_lock, flags);
}

static inline void *gs_acm_evt_get(struct gs_acm_evt_manage *evt)
{
	unsigned long flags;
	struct gs_acm_cdev_port *ret_port = NULL;

	spin_lock_irqsave(&evt->evt_lock, flags);
	if (evt->port_evt_pos > 0) {
		ret_port = evt->port_evt_array[evt->port_evt_pos-1];
		evt->port_evt_array[evt->port_evt_pos-1] = NULL;
		evt->port_evt_pos--;
	}
	spin_unlock_irqrestore(&evt->evt_lock, flags);

	return ret_port;
}

static inline void gs_acm_evt_dump_info(struct gs_acm_evt_manage *evt)
{
	int i;
	struct gs_acm_cdev_port *port;

	pr_emerg("--- dump evt_pos:%d, name:%s ---\n",
		    evt->port_evt_pos, (evt->name) ? (evt->name) : ("NULL"));
	for (i = 0; i <= evt->port_evt_pos; i++) {
		port = evt->port_evt_array[i];
		if (port) {
			pr_emerg("port[%p]_0x%x : %s\n", port,
				    evt->port_evt_pos,
				    (evt->name) ? (evt->name) : ("NULL"));
		}
	}
}

#endif /* __BALONG_ACM_H */
