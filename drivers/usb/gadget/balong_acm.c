#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/slab.h>
#include <linux/export.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/tty.h>

#include <linux/usb/drv_acm.h>
#include <linux/usb/drv_udi.h>

#include "balong_acm.h"
#include "usb_vendor.h"

#ifdef DEBUG
#define D(format, arg...) pr_info("[%s]" format, __func__, ##arg)
#else
#define D(format, arg...) do {} while (0)
#endif

#define ACM_CDEV_PREFIX			"acm_"
#define ACM_CDEV_DRV_NAME		"acm_cdev"
#define ACM_CDEV_DFT_RD_BUF_SIZE	2048
#define ACM_CDEV_DFT_RD_REQ_NUM		8
#define ACM_CDEV_DFT_WT_REQ_NUM		16
#define ACM_CDEV_AT_WT_REQ_NUM		256
#define ACM_CDEV_NAME_MAX		64
#define ACM_CDEV_MAX_XFER_SIZE		(0x1000000 - 1)
#define DOMAIN_NAME_LEN			8

/* cdev driver */
struct u_cdev_driver {
	struct kref kref;           /* Reference management */
	struct cdev cdev;
	dev_t dev_no;
	struct module *owner;
	const char *driver_name;
	const char *name;
	int name_base;              /* offset of printed name */
	int major;                  /* major device number */
	int minor_start;            /* start of minor device number */
	int num;                    /* number of devices allocated */

	struct workqueue_struct *acm_work_queue;
};

/*
 * The port structure holds info for each port, one for each minor number
 * (and thus for each /dev/ node).
 */
struct gs_acm_cdev_port {
	spinlock_t port_lock;               /* guard port_* access */

	struct gserial *port_usb;

	unsigned open_count;
	bool openclose;                     /* open/close in progress */
	u8 port_num;
	wait_queue_head_t close_wait;       /* wait for last close */
	ACM_EVENT_CB_T event_notify_cb;
	u16 cur_evt;
	u16 line_state_on;
	u16 line_state_change;
	char *in_name;
	char *out_name;

	MODEM_MSC_STRU flow_msg;
	ACM_MODEM_MSC_READ_CB_T read_sig_cb;
	ACM_MODEM_REL_IND_CB_T	rel_ind_cb;

	char read_domain[DOMAIN_NAME_LEN];
	struct list_head read_pool;         /* free read req list */
	struct list_head read_done_queue;        /* done read req list */
	struct list_head read_using_queue;  /* req in using list */
	struct list_head read_queue_in_usb;
	int read_started;
	int read_allocated;
	int read_req_enqueued;
	int read_completed;
	unsigned read_req_num;
	unsigned read_buf_size;
	unsigned reading_pos;
	struct usb_request  *reading_req;
	int read_blocked;
	wait_queue_head_t read_wait;
	struct mutex read_lock;
	ACM_READ_DONE_CB_T read_done_cb;

	char write_domain[DOMAIN_NAME_LEN];
	struct list_head write_pool;        /* free write req list */
	struct list_head write_queue;       /* done write req list */
	unsigned write_req_num;
	int write_started;
	int write_allocated;
	int write_blocked;
	int write_block_status;
	int write_completed;
	bool is_do_copy;
	struct mutex write_lock;
	wait_queue_head_t write_wait;
	ACM_WRITE_DONE_CB_T write_done_cb;
	ACM_FREE_CB_T write_done_free_cb;

	struct delayed_work rw_work;
	struct usb_cdc_line_coding port_line_coding;    /* 8-N-1 etc */
	unsigned is_realloc;
	wait_queue_head_t realloc_wait;

	char debug_tx_domain[DOMAIN_NAME_LEN];
	unsigned stat_write_async_call;
	unsigned stat_write_param_err;
	unsigned stat_sync_tx_submit;
	unsigned stat_sync_tx_done;
	unsigned stat_sync_tx_fail;
	unsigned stat_sync_tx_wait_fail;
	unsigned stat_tx_submit;
	unsigned stat_tx_submit_fail;
	unsigned stat_tx_submit_bytes;
	unsigned stat_tx_done;
	unsigned stat_tx_done_fail;
	unsigned stat_tx_done_bytes;
	unsigned stat_tx_done_schdule;
	unsigned stat_tx_done_disconnect;
	unsigned stat_tx_wakeup_block;
	unsigned stat_tx_callback;
	unsigned stat_tx_no_req;
	unsigned stat_tx_copy_fail;
	unsigned stat_tx_alloc_fail;
	unsigned stat_tx_disconnect;

	char debug_rx_domain[DOMAIN_NAME_LEN];
	unsigned stat_read_call;
	unsigned stat_get_buf_call;
	unsigned stat_ret_buf_call;
	unsigned stat_read_param_err;
	unsigned stat_sync_rx_submit;
	unsigned stat_sync_rx_done;
	unsigned stat_sync_rx_done_fail;
	unsigned stat_sync_rx_done_bytes;
	unsigned stat_sync_rx_copy_fail;
	unsigned stat_sync_rx_disconnect;
	unsigned stat_sync_rx_wait_fail;
	unsigned stat_rx_submit;
	unsigned stat_rx_submit_fail;
	unsigned stat_rx_disconnect;
	unsigned stat_rx_no_req;
	unsigned stat_rx_done;
	unsigned stat_rx_done_fail;
	unsigned stat_rx_done_bytes;
	unsigned stat_rx_done_disconnect;
	unsigned stat_rx_done_schdule;
	unsigned stat_rx_wakeup_block;
	unsigned stat_rx_wakeup_realloc;
	unsigned stat_rx_callback;
	unsigned stat_rx_cb_not_start;
	unsigned stat_rx_dequeue;

	char debug_port_domain[DOMAIN_NAME_LEN];
	unsigned stat_port_is_connect;
	unsigned stat_port_connect;
	unsigned stat_port_disconnect;
	unsigned stat_enable_in_fail;
	unsigned stat_enable_out_fail;
	unsigned stat_notify_sched;
	unsigned stat_notify_on_cnt;
	unsigned stat_notify_off_cnt;

	unsigned stat_send_cts_stat;
	unsigned stat_send_cts_enable;
	unsigned stat_send_cts_disable;
	unsigned stat_send_ri;
	unsigned stat_send_dsr;
	unsigned stat_send_dcd;
	unsigned stat_send_capability;
};

struct gs_acm_cdev_rw_priv {
	struct list_head list;
	bool is_sync;
	bool is_copy;
	int copy_pos;
	struct usb_request *req;
	struct kiocb *iocb;
	void *user_p_skb;
};

static struct acm_cdev_port_manager {
	char name_domain[DOMAIN_NAME_LEN];
	struct mutex open_close_lock;		/* protect open/close */
	struct gs_acm_cdev_port *port;
	struct device   *cdev;
	ACM_EVENT_CB_T event_cb;		/* when usb is remove */
} gs_acm_cdev_ports[ACM_CDEV_COUNT];

static struct notifier_block gs_acm_nb;
static struct notifier_block *gs_acm_nb_ptr;

static unsigned gs_acm_cdev_n_ports;
static unsigned gs_stat_drv_invalid;
static unsigned gs_stat_port_num_err;

static struct gs_acm_evt_manage gs_acm_write_evt_manage;
static struct gs_acm_evt_manage gs_acm_read_evt_manage;
static struct gs_acm_evt_manage gs_acm_sig_stat_evt_manage;

static struct u_cdev_driver *gs_cdev_driver;

static void gs_acm_cdev_free_request(struct usb_ep *ep,
		struct usb_request  *req);
static struct usb_request *gs_acm_cdev_alloc_request(struct usb_ep *ep,
		unsigned int buf_size);
static void gs_acm_cdev_free_requests(struct usb_ep *ep,
		struct list_head *head, int *allocated);
static void gs_acm_cdev_write_complete(struct usb_ep *ep,
		struct usb_request *req);
static void gs_acm_cdev_read_complete(struct usb_ep *ep,
		struct usb_request *req);

/*-------------------------------------------------------------------------*/
static unsigned int gs_acm_cdev_get_tx_buf_num(unsigned int index)
{
	switch (ACM_CDEV_GET_TYPE(index)) {
	case USB_IF_PROTOCOL_PCUI:
		return ACM_CDEV_AT_WT_REQ_NUM;
	case USB_IF_PROTOCOL_MODEM:
		return ACM_CDEV_AT_WT_REQ_NUM;
	default:
		break;
	}
	return ACM_CDEV_DFT_WT_REQ_NUM;
}

/*
 * gs_acm_cdev_start_tx
 *
 * This function finds available write requests, calls
 * usb_ep_queue to send the data.
 *
 */
static int gs_acm_cdev_start_tx(struct gs_acm_cdev_port *port,
			char *buf, unsigned int len, bool is_sync)
{
	struct list_head *pool = &port->write_pool;
	int status = 0;
	struct usb_request *req;
	bool is_do_copy = port->is_do_copy;
	struct gs_acm_cdev_rw_priv *write_priv;
	unsigned long flags;
	struct sk_buff *send_skb = NULL;

	D("port_num %d\n", port->port_num);
	spin_lock_irqsave(&port->port_lock, flags);

	if (unlikely(list_empty(pool))) {
		spin_unlock_irqrestore(&port->port_lock, flags);
		port->stat_tx_no_req++;
		pr_err("acm[%s]%s: no req\n",
				__func__, ACM_CDEV_GET_NAME(port->port_num));
		return -EAGAIN;
	}

	/* get a write req from the write pool */
	req = list_entry(pool->next, struct usb_request, list);
	list_del_init(&req->list);
	port->write_started++;

	spin_unlock_irqrestore(&port->port_lock, flags);
	if (is_modem_port(port->port_num)) {
		send_skb = (struct sk_buff *)buf;
		buf = send_skb->data;
		len = send_skb->len;
	}
	/* check whether copy the data */
	if (is_do_copy) {
		D("do copy\n");
		/* alloc a new buffer first time or the room is not enough */
		if (0 == req->length || req->length < len) {
			if (req->buf) {
				kfree(req->buf);
				req->buf = NULL;
				req->length = 0;
			}
			req->buf = kmalloc(len, GFP_KERNEL);
			if (NULL == req->buf) {
				pr_err("gs_acm_cdev_start_tx:malloc req->buf error\n");
				port->stat_tx_alloc_fail++;
				return -ENOMEM;
			}
		}
		/* we don't need to free req->buf, if fail */
		if (copy_from_user(req->buf, buf, len)) {
			port->stat_tx_copy_fail++;
			return -ENOMEM;
		}
	} else {
		D("no copy\n");
		req->buf = buf;
	}

	req->length = len;
	write_priv = (struct gs_acm_cdev_rw_priv *)req->context;
	write_priv->user_p_skb = send_skb;
	write_priv->is_sync = is_sync;
	write_priv->is_copy = is_do_copy;

	spin_lock_irqsave(&port->port_lock, flags);
	if (!port->port_usb) {
		status = -ENODEV;
		port->stat_tx_disconnect++;
		pr_err("[%s] no usb port\n", __func__);
		goto tx_fail_restore;
	}

	if (is_sync) {
		/* wait the write req complete */
		port->write_blocked = 1;
	}

	if (len % port->port_usb->in->maxpacket == 0)
		req->zero = 1;

	spin_unlock_irqrestore(&port->port_lock, flags);

	status = usb_ep_queue(port->port_usb->in, req, GFP_ATOMIC);
	if (status) {
		pr_err("%s: usb_ep_queue fail, status %d!\n", __func__, status);
		spin_lock_irqsave(&port->port_lock, flags);
		port->stat_tx_submit_fail++;
		goto tx_fail_restore;
	}
	port->stat_tx_submit_bytes += len;
	port->stat_tx_submit++;

	return 0;

tx_fail_restore:
	list_add_tail(&req->list, pool);
	port->write_started--;
	port->write_blocked = 0;
	spin_unlock_irqrestore(&port->port_lock, flags);
	return status;
}

/*
 * Context: caller owns port_lock, and port_usb is set
 */
static unsigned gs_acm_cdev_start_rx(struct gs_acm_cdev_port *port)
{
	struct list_head    *pool = &port->read_pool;
	struct usb_ep       *out = port->port_usb->out;
	struct usb_request  *req;
	struct gs_acm_cdev_rw_priv *rw_priv;

	D("port_num %d\n", port->port_num);

start_rx_beg:
	while (!list_empty(pool)) {
		int status;

		/* revise the pool length to smaller */
		if (port->read_started >= port->read_req_num) {
			pr_emerg("%s: try to shrink the read buff num "
				   "to %d at port %d\n", __func__, port->read_req_num, port->port_num);

			gs_acm_cdev_free_requests(out, pool, &port->read_allocated);
			break;
		}

		req = list_first_entry(pool, struct usb_request, list);
		list_del_init(&req->list);
		port->read_started++;

		if (req->length < port->read_buf_size) {
			D("realloc req\n");
			gs_acm_cdev_free_request(out, req);
			req = gs_acm_cdev_alloc_request(out, port->read_buf_size);
			if (!req) {
				pr_err("[%s]gs_acm_cdev_alloc_request is fail\n", __func__);
				goto start_rx_ret;
			}
			req->complete = gs_acm_cdev_read_complete;
		}

		/* drop lock while we call out; the controller driver
		 * may need to call us back (e.g. for disconnect)
		 */
		spin_unlock(&port->port_lock);
		status = usb_ep_queue(out, req, GFP_ATOMIC);
		spin_lock(&port->port_lock);

		if (status) {
			pr_err("[%s]ep queue failed, status %d!\n", __func__, status);
			list_add(&req->list, pool);
			port->read_started--;
			port->stat_rx_submit_fail++;
			goto start_rx_ret;
		}

		rw_priv = (struct gs_acm_cdev_rw_priv *)req->context;
		list_add_tail(&rw_priv->list, &port->read_queue_in_usb);

		port->read_req_enqueued++;
		port->stat_rx_submit++;

		/* abort immediately after disconnect */
		if (!port->port_usb) {
			pr_err("[%s]no usb port\n", __func__);
			port->stat_rx_disconnect++;
			goto start_rx_ret;
		}
	}

	/* if there are no read req in usb core,
	 * get the read done req and submit to usb core.
	 * this mechamism may cause loosing packets.
	 */
	if (port->port_usb && 0 == port->read_req_enqueued) {
		struct list_head *queue = &port->read_done_queue;

		if (!list_empty(queue)) {
			req = list_entry(queue->prev, struct usb_request, list);
			list_move(&req->list, pool);
			port->read_started--;

			/* go to beginning of the function,
			 * re-submit the read req
			 */
			port->stat_rx_no_req++;
			pr_info("get read done req for rx, drop a packet\n");
			goto start_rx_beg;
		}
	}

start_rx_ret:
	return (unsigned)port->read_started;
}

/*
 * Context: caller owns port_lock, and port_usb is set
 */
static void gs_acm_cdev_stop_rx(struct gs_acm_cdev_port *port)
{
	struct gs_acm_cdev_rw_priv *rw_priv;
	struct usb_ep *out = port->port_usb->out;

	D("port_num %d\n", port->port_num);

	while (!list_empty(&port->read_queue_in_usb)) {
		rw_priv = list_first_entry(&port->read_queue_in_usb,
					struct gs_acm_cdev_rw_priv, list);
		port->stat_rx_dequeue++;
		list_del_init(&rw_priv->list);
		spin_unlock(&port->port_lock);
		usb_ep_dequeue(out, rw_priv->req);
		spin_lock(&port->port_lock);
	}
}

static int gs_acm_cdev_get_read_buf(struct gs_acm_cdev_port *port,
				ACM_WR_ASYNC_INFO *read_info)
{
	struct list_head *queue = &port->read_done_queue;
	struct usb_request  *req = NULL;
	int status;
	unsigned long flags;
	unsigned actual_len;
	struct sk_buff *skb = NULL;

	D("port_num %d\n", port->port_num);

	mutex_lock(&port->read_lock);

	spin_lock_irqsave(&port->port_lock, flags);
	if (!list_empty(queue)) {
		req = list_first_entry(queue, struct usb_request, list);
		list_move_tail(&req->list, &port->read_using_queue);
	}
	spin_unlock_irqrestore(&port->port_lock, flags);

	if (NULL == req) {
		read_info->pVirAddr = NULL;
		read_info->pPhyAddr = (char *)(~0);
		read_info->u32Size = 0;
		status = -EAGAIN;
		pr_err("[%s]no req\n", __func__);
		goto out;
	}

	if (req->status) {
		pr_warn("%s: port %d, req status %d\n", __func__,
				port->port_num, req->status);
	}

	actual_len = req->actual;
	if (is_modem_port(port->port_num)) {
		skb = dev_alloc_skb(actual_len);
		if (!skb) {
			pr_err("dev_alloc_skb(%d) fail!\n", actual_len);
			status = -EAGAIN;
		} else {
			memcpy((void *)skb->data, (void *)req->buf, actual_len);
			skb_put(skb, actual_len);
			read_info->pVirAddr = (char *)skb;
			read_info->pPhyAddr = (char *)(~0);
			read_info->u32Size = actual_len;
			status = 0;
		}

		spin_lock_irqsave(&port->port_lock, flags);
		list_move(&req->list, &port->read_pool);
		port->read_started--;
		spin_unlock_irqrestore(&port->port_lock, flags);
	} else {
		read_info->pVirAddr = (char *)req->buf;
		read_info->pPhyAddr = (char *)(~0);
		read_info->u32Size = actual_len;
		status = 0;
	}

out:
	mutex_unlock(&port->read_lock);
	return status;
}

static int gs_acm_cdev_ret_read_buf(struct gs_acm_cdev_port *port,
				ACM_WR_ASYNC_INFO *read_info)
{
	struct usb_request *cur_req = NULL;
	struct usb_request *next_req = NULL;
	unsigned long flags;

	D("port_num %d\n", port->port_num);

	spin_lock_irqsave(&port->port_lock, flags);
	if (is_modem_port(port->port_num)) {
		dev_kfree_skb_any((struct sk_buff *)read_info->pVirAddr);
		read_info->pVirAddr = NULL;
		spin_unlock_irqrestore(&port->port_lock, flags);
		return 0;
	}

	list_for_each_entry_safe(cur_req, next_req, &port->read_using_queue, list) {
		if ((unsigned long)cur_req->buf == (unsigned long)read_info->pVirAddr) {
			list_move(&cur_req->list, &port->read_pool);
			port->read_started--;
			spin_unlock_irqrestore(&port->port_lock, flags);

			return 0;
		}
	}
	spin_unlock_irqrestore(&port->port_lock, flags);

	return -EFAULT;
}

static void gs_acm_cdev_notify_cb(struct gs_acm_cdev_port *port)
{
	ACM_EVENT_CB_T event_cb = NULL;
	u16 line_state = 0;
	unsigned long flags;
	MODEM_MSC_STRU *flow_msg = &port->flow_msg;
	ACM_MODEM_MSC_READ_CB_T read_sig_cb = NULL;

	D("port_num %d\n", port->port_num);

	spin_lock_irqsave(&port->port_lock, flags);
	if (port->line_state_change) {
		/* event_cb is for common serial port  */
		event_cb = port->event_notify_cb;
		line_state = port->line_state_on;
		port->line_state_change = 0;

		/* read_sig_cb is for modem port */
		read_sig_cb = port->read_sig_cb;
		flow_msg->OP_Dtr = SIGNALCH;
		flow_msg->ucDtr = line_state;
	}
	spin_unlock_irqrestore(&port->port_lock, flags);

	if (event_cb) {
		if (line_state)
			port->stat_notify_on_cnt++;
		else
			port->stat_notify_off_cnt++;

		event_cb((ACM_EVT_E)line_state);
	}

	if (read_sig_cb) {
		if (line_state)
			port->stat_notify_on_cnt++;
		else
			port->stat_notify_off_cnt++;

		pr_info("acm[%s] read_sig_cb OP_Dtr=%d ucDtr=%d\n",
				ACM_CDEV_GET_NAME(port->port_num), flow_msg->OP_Dtr,
				flow_msg->ucDtr);
		read_sig_cb(flow_msg);
		flow_msg->OP_Dtr = SIGNALNOCH;
	}

	return;
}

static void gs_acm_cdev_read_cb(struct gs_acm_cdev_port *port)
{
	struct list_head *queue = &port->read_done_queue;
	struct usb_request  *req = NULL;
	ACM_READ_DONE_CB_T read_cb = NULL;
	unsigned long flags;
	int status = 0;

	D("port_num %d\n", port->port_num);

	for (;;) {
		spin_lock_irqsave(&port->port_lock, flags);
		if (port->read_completed <= 0) {
			spin_unlock_irqrestore(&port->port_lock, flags);
			return;
		}
		port->read_completed--;

		read_cb = NULL;
		if (!list_empty(queue)) {
			req = list_first_entry(queue, struct usb_request, list);
			status = req->status;

			/* if there are data in queue, prepare the read callback */
			if (!req->status && port->open_count) {
				read_cb = port->read_done_cb;
			} else {
				list_move(&req->list, &port->read_pool);
				port->read_started--;
			}
		}

		/* submit the next read req */
		if (-ESHUTDOWN != status && port->port_usb)
			gs_acm_cdev_start_rx(port);
		else
			port->stat_rx_cb_not_start++;

		spin_unlock_irqrestore(&port->port_lock, flags);

		if (NULL != read_cb) {
			port->stat_rx_callback++;
			read_cb();
		}
	}
}

static void gs_acm_cdev_write_cb(struct gs_acm_cdev_port *port)
{
	struct usb_request  *req = NULL;
	struct list_head    *queue = &port->write_queue;
	char *buf;
	int actual_size;
	ACM_WRITE_DONE_CB_T write_cb = NULL;
	ACM_FREE_CB_T free_cb = NULL;
	struct gs_acm_cdev_rw_priv *write_priv = NULL;
	struct sk_buff *send_skb = NULL;
	unsigned long flags;

	D("port_num %d\n", port->port_num);

	for (;;) {
		spin_lock_irqsave(&port->port_lock, flags);
		if (port->write_completed <= 0) {
			spin_unlock_irqrestore(&port->port_lock, flags);
			return;
		}
		write_cb = port->write_done_cb;
		free_cb = port->write_done_free_cb;
		actual_size = 0;
		buf = NULL;
		port->write_completed--;

		if (!list_empty(queue)) {
			req = list_first_entry(queue, struct usb_request, list);

			/* if there is data in queue, prepare the write callback */
			buf = req->buf;
			actual_size = (!req->status) ? (int)req->actual : (int)req->status;
			write_priv = (struct gs_acm_cdev_rw_priv *)req->context;
			if (write_priv != NULL)
				send_skb = write_priv->user_p_skb;
			list_move(&req->list, &port->write_pool);
			port->write_started--;
		}
		spin_unlock_irqrestore(&port->port_lock, flags);

		if (NULL != write_cb) {
			port->stat_tx_callback++;
			write_cb(buf, (char *)(~0), actual_size);
		} else if (NULL != free_cb) {
			if (is_modem_port(port->port_num) && send_skb != NULL) {
				port->stat_tx_callback++;
				free_cb((char *)send_skb);
			}
		}
	}
}

/*
 * rw workqueue takes data out of the RX queue and hands it up to the TTY
 * layer until it refuses to take any more data (or is throttled back).
 * Then it issues reads for any further data.
 */
static void gs_acm_cdev_rw_push(struct work_struct *work)
{
	struct gs_acm_cdev_port *port;

	/* notify callback */
	while (NULL != (port = gs_acm_evt_get(&gs_acm_sig_stat_evt_manage)))
		gs_acm_cdev_notify_cb(port);

	/* read callback */
	while (NULL != (port = gs_acm_evt_get(&gs_acm_read_evt_manage)))
		gs_acm_cdev_read_cb(port);

	/* write callback */
	while (NULL != (port = gs_acm_evt_get(&gs_acm_write_evt_manage)))
		gs_acm_cdev_write_cb(port);

	/* other callback ... */

	return;
}

static void gs_acm_cdev_read_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct gs_acm_cdev_port *port = ep->driver_data;
	struct gs_acm_cdev_rw_priv *rw_priv;

	D("port_num %d, actual %d\n", port->port_num, req->actual);

	/* Queue all received data until the tty layer is ready for it. */
	spin_lock(&port->port_lock);

	if (!req->status) {
		port->stat_rx_done++;
		port->stat_rx_done_bytes += req->actual;
	} else {
		port->stat_rx_done_fail++;
	}

	rw_priv = (struct gs_acm_cdev_rw_priv *)req->context;
	list_del_init(&rw_priv->list);
	port->read_req_enqueued--;

	if (port->port_usb && !port->is_realloc && req->actual) {
		list_add_tail(&req->list, &port->read_done_queue);
		port->stat_rx_done_schdule++;
		port->read_completed++;
		gs_acm_evt_push(port, &gs_acm_read_evt_manage);
		queue_delayed_work(gs_cdev_driver->acm_work_queue, &port->rw_work, 0);
	} else {
		list_add_tail(&req->list, &port->read_pool);
		port->read_started--;
		port->stat_rx_done_disconnect++;
	}
	spin_unlock(&port->port_lock);

	/* if there is blocked read, wake up it */
	if (port->read_blocked) {
		port->read_blocked = 0;
		port->stat_rx_wakeup_block++;
		wake_up_interruptible(&port->read_wait);
	}

	/* if clean up all read reqs, wake up the realloc task */
	if (port->is_realloc && !port->read_started) {
		port->stat_rx_wakeup_realloc++;
		wake_up(&port->realloc_wait);
	}
}

static void gs_acm_cdev_write_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct gs_acm_cdev_port *port = ep->driver_data;
	struct gs_acm_cdev_rw_priv *write_priv;

	D("port_num %d\n", port->port_num);

	spin_lock(&port->port_lock);
	write_priv = (struct gs_acm_cdev_rw_priv *)req->context;

	if (!req->status) {
		port->stat_tx_done++;
		port->stat_tx_done_bytes += req->actual;
	} else {
		pr_err("%s: req->status(%d) is fail\n", __func__, req->status);
		port->stat_tx_done_fail++;
	}

	/* sync read wake up the blocked task*/
	if (write_priv->is_sync) {
		list_add_tail(&req->list, &port->write_pool);
		port->write_started--;
		port->write_block_status = req->status;
		port->write_blocked = 0;
		write_priv->is_sync = 0;
		port->stat_tx_wakeup_block++;
		wake_up_interruptible(&port->write_wait);
	}
	/* async read schedule the workqueue to call the callback */
	else {
		if (port->port_usb) {
			list_add_tail(&req->list, &port->write_queue);
			port->stat_tx_done_schdule++;
			port->write_completed++;
			gs_acm_evt_push(port, &gs_acm_write_evt_manage);

			queue_delayed_work(gs_cdev_driver->acm_work_queue,
						&port->rw_work, 0);
		} else {
			list_add_tail(&req->list, &port->write_pool);
			port->write_started--;
			port->stat_tx_done_disconnect++;
		}
	}
	spin_unlock(&port->port_lock);
}

/*-------------------------------------------------------------------------*/

static void gs_acm_cdev_free_request(struct usb_ep *ep,
				struct usb_request  *req)
{
	struct gs_acm_cdev_rw_priv *write_priv;
	write_priv = (struct gs_acm_cdev_rw_priv *)req->context;

	/* if copy_data flag is ture,
	 * the data buffer is belong to usr, don't free it
	 */
	if (!write_priv->is_copy)
		req->buf = NULL;

	if (req->context) {
		kfree(req->context);
		req->context = NULL;
	}
	gs_acm_cdev_free_req(ep, req);
}

static void gs_acm_cdev_free_requests(struct usb_ep *ep, struct list_head *head,
					int *allocated)
{
	struct usb_request  *req;

	while (!list_empty(head)) {
		req = list_entry(head->next, struct usb_request, list);
		list_del_init(&req->list);
		gs_acm_cdev_free_request(ep, req);
		if (allocated)
			(*allocated)--;
	}
}

struct usb_request *gs_acm_cdev_alloc_req(struct usb_ep *ep, unsigned len,
					gfp_t kmalloc_flags)
{
	struct usb_request *req;

	req = usb_ep_alloc_request(ep, kmalloc_flags);

	if (req != NULL) {
		req->length = len;
		if (0 == len) {
			req->buf = NULL;
		} else {
			req->buf = kmalloc(len, kmalloc_flags);
			if (req->buf == NULL) {
				usb_ep_free_request(ep, req);
				return NULL;
			}
		}
	}

	return req;
}
EXPORT_SYMBOL_GPL(gs_acm_cdev_alloc_req);

void gs_acm_cdev_free_req(struct usb_ep *ep, struct usb_request *req)
{
	if (req->buf)
		kfree(req->buf);
	usb_ep_free_request(ep, req);
}
EXPORT_SYMBOL_GPL(gs_acm_cdev_free_req);

static struct usb_request *
gs_acm_cdev_alloc_request(struct usb_ep *ep, unsigned int buf_size)
{
	struct gs_acm_cdev_rw_priv *rw_priv;
	struct usb_request *req;

	req = gs_acm_cdev_alloc_req(ep, buf_size, GFP_ATOMIC);
	if (!req) {
		pr_err("[%s]gs_acm_cdev_alloc_req fail\n", __func__);
		return NULL;
	}

	rw_priv = (struct gs_acm_cdev_rw_priv *)
			  kzalloc(sizeof(struct gs_acm_cdev_rw_priv), GFP_ATOMIC);
	if (!rw_priv) {
		pr_err("[%s]kzalloc fail\n", __func__);
		gs_acm_cdev_free_req(ep, req);
		return NULL;
	}
	req->context = (void *)rw_priv;
	rw_priv->req = req;

	if (buf_size)
		rw_priv->is_copy = 1;

	INIT_LIST_HEAD(&rw_priv->list);

	return req;
}

static int gs_acm_cdev_alloc_requests(struct usb_ep *ep,
		struct list_head *head,
		void (*fn)(struct usb_ep *, struct usb_request *),
		int *allocated, unsigned int buf_size, unsigned int buf_num)
{
	int			i;
	struct usb_request	*req;
	int			n = allocated ? buf_num - *allocated : buf_num;

	for (i = 0; i < n; i++) {
		req = gs_acm_cdev_alloc_request(ep, buf_size);
		if (!req)
			return list_empty(head) ? -ENOMEM : 0;
		req->complete = fn;
		list_add_tail(&req->list, head);
		if (allocated)
			(*allocated)++;
	}
	return 0;
}

/*
 * Context: holding port_lock;
 */
static int gs_acm_cdev_prepare_io(struct gs_acm_cdev_port *port)
{
	struct list_head	*head = &port->read_pool;
	struct usb_ep		*ep = port->port_usb->out;
	int			status;

	/* alloc requests for bulk out ep */
	status = gs_acm_cdev_alloc_requests(ep, head, gs_acm_cdev_read_complete,
			&port->read_allocated, port->read_buf_size,
			port->read_req_num);
	if (status) {
		pr_err("port%d alloc request for bulk out ep failed!\n",
				port->port_num);
		return status;
	}
	D("port%d: alloc %d reqs for bulk out ep, buf_size 0x%x, allocated %d\n",
			port->port_num, port->read_req_num, port->read_buf_size,
			port->read_allocated);

	/* alloc request for bulk in ep */
	status = gs_acm_cdev_alloc_requests(port->port_usb->in, &port->write_pool,
			gs_acm_cdev_write_complete, &port->write_allocated, 0,
			port->write_req_num);
	if (status) {
		pr_err("port%d alloc request for bulk out ep failed!\n",
				port->port_num);
		gs_acm_cdev_free_requests(ep, head, &port->read_allocated);
		return status;
	}
	D("port%d: alloc %d reqs for bulk in ep, buf_size 0x%x, allocated %d\n",
			port->port_num, port->write_req_num, 0,
			port->write_allocated);

	return 0;
}

/*-------------------------------------------------------------------------*/

static inline int gs_acm_cdev_get_port_num(struct inode *inode)
{
	int     port_num;

	if (!gs_cdev_driver || !inode) {
		gs_stat_drv_invalid++;
		return -ENXIO;
	}

	port_num = inode->i_rdev - gs_cdev_driver->dev_no;

	if (port_num >= gs_acm_cdev_n_ports) {
		gs_stat_port_num_err++;
		return -ENXIO;
	}

	return port_num;
}

static int gs_acm_cdev_open(struct inode *inode, struct file *filp)
{
	int port_num;
	struct gs_acm_cdev_port *port;
	int status;
	unsigned long flags;

	D("+\n");

	port_num = gs_acm_cdev_get_port_num(inode);
	if (port_num < 0)
		return port_num;
	/* block operation acm_modem port,because if operation acm_modem port,
	 * the phone maybe reboot and go to fastboot mode */
	if (!is_a_shell_cdma_port(port_num)) {
		pr_err("%s: can't operation port %d!\n", __func__, port_num);
		return -EOPNOTSUPP;
	}

	D("port_num %d\n", port_num);

	do {
		mutex_lock(&gs_acm_cdev_ports[port_num].open_close_lock);
		port = gs_acm_cdev_ports[port_num].port;
		if (!port)
			status = -ENODEV;
		else {
			spin_lock_irqsave(&port->port_lock, flags);

			/* already open?  Great. */
			if (port->open_count) {
				status = 0;
				port->open_count++;

				/* currently opening/closing? wait ... */
			} else if (port->openclose) {
				status = -EBUSY;

				/* ... else we do the work */
			} else {
				status = -EAGAIN;
				port->openclose = true;
			}
			spin_unlock_irqrestore(&port->port_lock, flags);
		}
		mutex_unlock(&gs_acm_cdev_ports[port_num].open_close_lock);

		switch (status) {
		default:
			D("return\n");
			/* fully handled */
			return status;
		case -EAGAIN:
			/* must do the work */
			break;
		case -EBUSY:
			/* wait for EAGAIN task to finish */
			msleep(10);
			/* REVISIT could have a waitchannel here, if
			 * concurrent open performance is important
			 */
			break;
		}
	} while (status != -EAGAIN);

	spin_lock_irqsave(&port->port_lock, flags);
	port->open_count = 1;
	port->openclose = false;

	/* if connected, start the I/O stream */
	if (port->port_usb) {
		struct gserial  *gser = port->port_usb;
		if (gser->connect)
			gser->connect(gser);
	}

	spin_unlock_irqrestore(&port->port_lock, flags);

	D("-\n");
	return 0;
}

static int gs_acm_cdev_close(struct inode *inode, struct file *file)
{
	struct gs_acm_cdev_port *port;
	unsigned long flags;
	int status;

	D("+\n");

	status = gs_acm_cdev_get_port_num(inode);
	if (status < 0)
		return status;
	D("port_num %d\n", status);
	/* block operation acm_modem port,because if operation acm_modem port,
	 * the phone maybe reboot and go to fastboot mode */
	if (!is_a_shell_cdma_port(status)) {
		pr_err("%s: can't operation port %d!\n", __func__, status);
		return -EOPNOTSUPP;
	}

	port = gs_acm_cdev_ports[status].port;

	spin_lock_irqsave(&port->port_lock, flags);

	if (port->open_count != 1) {
		if (port->open_count == 0) {
			WARN_ON(1);
			return -EBADF;
		} else {
			--port->open_count;
		}
		goto exit;
	}

	/* mark port as closing but in use; we can drop port lock
	 * and sleep if necessary
	 */
	port->openclose = true;
	port->open_count = 0;
	port->line_state_on = 0;
	port->line_state_change = 0;

	{
		struct gserial  *gser;
		gser = port->port_usb;
		if (gser && gser->disconnect)
			gser->disconnect(gser);
	}

	port->openclose = false;

	wake_up_interruptible(&port->close_wait);
exit:
	spin_unlock_irqrestore(&port->port_lock, flags);

	D("-\n");

	return 0;
}

static int gs_acm_cdev_write_base(struct gs_acm_cdev_port *port,
				char *buf, unsigned int len, bool is_sync)
{
	int status = 0;

	D("+\n");

	if (len == 0) {
		pr_err("gs_acm_cdev_write_base: zero length packet to send\n");
		return status;
	}

	if (len > ACM_CDEV_MAX_XFER_SIZE) {
		pr_err("[%s]port %d, len too large\n", __func__, port->port_num);
		return -EINVAL;
	}

	if (!buf) {
		pr_err("[%s]port %d, buf is NULL\n", __func__, port->port_num);
		return -EINVAL;
	}

	mutex_lock(&port->write_lock);

	status = gs_acm_cdev_start_tx(port, buf, len, is_sync);
	if (status) {
		goto write_mutex_exit;
	}

	/* async write don't need to wait write complete */
	if (!is_sync) {
		goto write_mutex_exit;
	}

	status = wait_event_interruptible(port->write_wait, (port->write_blocked == 0));
	if (status) {
		port->stat_sync_tx_wait_fail++;
		goto write_mutex_exit;
	}

	/* check status */
	if (port->write_block_status) {
		status = port->write_block_status;
		port->write_block_status = 0;
	} else {
		status = (int)len;
	}

write_mutex_exit:
	mutex_unlock(&port->write_lock);
	D("-\n");
	return status;
}

/**
 *  gs_acm_cdev_write       -   write method for tty device file
 *  @file: acm file pointer
 *  @buf: user data to write
 *  @count: bytes to write
 *  @ppos: unused
 *
 *  Write data to a acm device.
 *
 */
static ssize_t gs_acm_cdev_write(struct file *file, const char __user *buf,
				size_t count, loff_t *ppos)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	int     port_num;
	struct gs_acm_cdev_port *port;
	unsigned int len = (unsigned int)count;
	int status;

	D("+\n");
	if (unlikely(NULL == buf || 0 == count)) {
		pr_err("%s invalid param buf:%p, count:%zu\n",
					__func__, buf, count);
		return -EFAULT;
	}

	port_num = gs_acm_cdev_get_port_num(inode);
	if (port_num < 0)
		return port_num;
	/* block operation acm_modem port,because if operation acm_modem port,
	 * the phone maybe reboot and go to fastboot mode */
	if (!is_a_shell_cdma_port(port_num)) {
		pr_err("%s: can't operation port %d!\n", __func__, port_num);
		return -EOPNOTSUPP;
	}

	port = gs_acm_cdev_ports[port_num].port;

	port->stat_sync_tx_submit++;
	status = gs_acm_cdev_write_base(port, (char *)buf, len, true);
	if (status > 0)
		port->stat_sync_tx_done++;
	else
		port->stat_sync_tx_fail++;

	D("-\n");
	return (ssize_t)status;
}

static struct usb_request *
gs_acm_cdev_get_reading_req(struct gs_acm_cdev_port *port)
{
	struct usb_request *reading_req;

	if (NULL == port->reading_req) {
		if (list_empty(&port->read_done_queue))
			reading_req = NULL;
		else {
			reading_req = list_first_entry(&port->read_done_queue,
						struct usb_request, list);
			list_del_init(&reading_req->list);
		}
	} else {
		reading_req = port->reading_req;
	}

	return reading_req;
}

static void
gs_acm_cdev_ret_reading_req(struct gs_acm_cdev_port *port, struct usb_request *req)
{
	unsigned long flags;

	spin_lock_irqsave(&port->port_lock, flags);
	list_add_tail(&req->list, &port->read_pool);
	port->read_started--;
	spin_unlock_irqrestore(&port->port_lock, flags);

	return;
}

/**
 *  gs_acm_cdev_read        -   read method for cdev device file
 *  @file: acm file pointer
 *  @buf: user data to read
 *  @count: bytes to read
 *  @ppos: unused
 *
 *  read data form a acm device.
 *
 */
static ssize_t gs_acm_cdev_read(struct file *file, char __user *buf,
				size_t count, loff_t *ppos)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	int port_num;
	struct gs_acm_cdev_port *port;
	struct usb_request *reading_req;
	unsigned long flags;
	struct gs_acm_cdev_rw_priv *read_priv;
	unsigned int need_size = (unsigned int)count;
	unsigned int copy_size;
	unsigned int left_size;
	char *copy_addr;
	int status = 0;

	D("+\n");

	port_num = gs_acm_cdev_get_port_num(inode);
	if (port_num < 0)
		return port_num;
	/* block operation acm_modem port,because if operation acm_modem port,
	 * the phone maybe reboot and go to fastboot mode */
	if (!is_a_shell_cdma_port(port_num)) {
		pr_err("%s: can't operation port %d!\n", __func__, port_num);
		return -EOPNOTSUPP;
	}
	port = gs_acm_cdev_ports[port_num].port;
	port->stat_read_call++;
	if (unlikely(NULL == buf || 0 == count)) {
		D("buf == NULL, count == 0\n");
		port->stat_read_param_err++;
		return -EFAULT;
	}

	mutex_lock(&port->read_lock);
	do {
		spin_lock_irqsave(&port->port_lock, flags);
		if (!port->port_usb) {
			port->stat_sync_rx_disconnect++;
			spin_unlock_irqrestore(&port->port_lock, flags);
			goto read_exit;
		}

		reading_req = gs_acm_cdev_get_reading_req(port);

		if (NULL == reading_req) {
			D("no reading_req\n");
			/* if no req, wait for reading complete */
			port->read_blocked = 1;
			spin_unlock_irqrestore(&port->port_lock, flags);
			status = wait_event_interruptible(port->read_wait,
						(port->read_blocked == 0));
			if (status) {
				pr_err("[%s]interrupted by signal\n", __func__);
				port->stat_sync_rx_wait_fail++;
				goto read_exit;
			}
		} else {
			spin_unlock_irqrestore(&port->port_lock, flags);
		}
	} while (NULL == reading_req);

	if (reading_req->status) {
		port->stat_sync_rx_done_fail++;
		goto read_drop_data;
	}

	/* prepare copy address and copy size */
	read_priv = (struct gs_acm_cdev_rw_priv *)reading_req->context;
	copy_addr = (char *)reading_req->buf + read_priv->copy_pos;
	left_size = reading_req->actual - read_priv->copy_pos;
	if (left_size > need_size) {
		copy_size = need_size;
		read_priv->copy_pos += copy_size;
		port->reading_req = reading_req;
	} else {
		copy_size = left_size;
		read_priv->copy_pos = 0;
		port->reading_req = NULL;
	}

	/* copy data to usr buffer */
	D("do copy_to_user\n");
	if (copy_to_user((void *)buf, (void *)copy_addr, copy_size)) {
		status = -EFAULT;
		pr_err("%s:copy_to_user fail\n", __func__);
		port->stat_sync_rx_copy_fail++;
		goto read_drop_data;
	}
	status = (int)copy_size;

	if (NULL == port->reading_req) {
		gs_acm_cdev_ret_reading_req(port, reading_req);
	}
	port->stat_sync_rx_done++;
	port->stat_sync_rx_done_bytes += copy_size;

	goto read_exit;

read_drop_data:
	port->reading_req = NULL;
	gs_acm_cdev_ret_reading_req(port, reading_req);
read_exit:
	mutex_unlock(&port->read_lock);

	D("-\n");

	return (ssize_t)status;
}

static int gs_acm_cdev_realloc_read_buf(struct gs_acm_cdev_port *port,
				ACM_READ_BUFF_INFO *buf_info)
{
	int status = 0;
	struct usb_ep *out;
	struct list_head *head = &port->read_pool;
	unsigned long flags = 0;

	/* get the read lock to stop usr use the read interface */
	mutex_lock(&port->read_lock);

	/* 1. dequeue all read req in usb core */
	spin_lock_irqsave(&port->port_lock, flags);
	if (unlikely(!port->port_usb)) {
		status = -ENODEV;
		goto realloc_exit;
	}
	port->is_realloc = 1;

	out = port->port_usb->out;
	gs_acm_cdev_stop_rx(port);
	spin_unlock_irqrestore(&port->port_lock, flags);

	/* 2. wait for all read req complete */
	(void)wait_event_timeout(port->realloc_wait, (!port->read_started), 300);

	spin_lock_irqsave(&port->port_lock, flags);
	if (unlikely(!port->port_usb)) {
		status = -ENODEV;
		pr_err("%s:no usb port\n", __func__);
		goto realloc_exit;
	}

	/* make sure the read reqs have been clean up */

	/* 3. free the old req pool */
	gs_acm_cdev_free_requests(out, head, &port->read_allocated);


	/* 4. alloc the new req pool */
	port->read_req_num = buf_info->u32BuffNum;
	port->read_buf_size = buf_info->u32BuffSize;
	if (port->read_buf_size > ACM_CDEV_MAX_XFER_SIZE) {
		pr_err("[%s]port %d, read_buf_size too large\n",
			   __func__, port->port_num);
		port->read_buf_size = ACM_CDEV_MAX_XFER_SIZE;
	}

	status = gs_acm_cdev_alloc_requests(out, head, gs_acm_cdev_read_complete,
			&port->read_allocated, port->read_buf_size, port->read_req_num);

	D("port%d: realloc %d reqs for bulk out ep, buf_size 0x%x, allocated %d\n",
			port->port_num, port->read_req_num, port->read_buf_size,
			port->read_allocated);

	/* 5. restart the rx */
	gs_acm_cdev_start_rx(port);

realloc_exit:
	port->is_realloc = 0;
	spin_unlock_irqrestore(&port->port_lock, flags);
	mutex_unlock(&port->read_lock);

	return status;
}


static int gs_acm_cdev_write_cmd(struct gs_acm_cdev_port *port,
				MODEM_MSC_STRU *flow_msg)
{
	u16 capability = 0;
	struct gserial *gser = NULL;

	if (port->port_usb) {
		gser = port->port_usb;
	} else {
		pr_err("%s: write cmd when disconnected\n", __func__);
		return -ENODEV;
	}

	if (SIGNALCH == flow_msg->OP_Cts) {
		if (SIGNALNOCH == flow_msg->ucCts) {
			if (gser->flow_control)
				gser->flow_control(gser, RECV_DISABLE, SEND_ENABLE);
			port->stat_send_cts_stat = RECV_DISABLE;
			port->stat_send_cts_disable++;
		} else {
			if (gser->flow_control)
				gser->flow_control(gser, RECV_ENABLE, SEND_ENABLE);
			port->stat_send_cts_stat = RECV_ENABLE;
			port->stat_send_cts_enable++;
		}
		pr_info("acm[%s] flow_control: %s\n",
			ACM_CDEV_GET_NAME(port->port_num),
			flow_msg->ucCts == SIGNALNOCH ?
				"disable recv" : "enable recv");
	}

	if ((SIGNALCH == flow_msg->OP_Ri) || (SIGNALCH == flow_msg->OP_Dsr)
				|| (SIGNALCH == flow_msg->OP_Dcd)) {

		if ((SIGNALCH == flow_msg->OP_Ri)
				&& (HIGHLEVEL == flow_msg->ucRi)) {
			capability |= MODEM_CTRL_RI;
			pr_info("acm[%s] OP_Ri CHANGE capability=0x%x\n",
				ACM_CDEV_GET_NAME(port->port_num), capability);
			port->stat_send_ri++;
		};

		/* DSR SIGNAL CHANGE */
		if ((SIGNALCH == flow_msg->OP_Dsr)
				&& (HIGHLEVEL == flow_msg->ucDsr)) {
			capability |= MODEM_CTRL_DSR;
			pr_info("acm[%s] OP_Dsr CHANGE capability=0x%x\n",
				ACM_CDEV_GET_NAME(port->port_num), capability);
			port->stat_send_dsr++;
		};

		/* DCD SIGNAL CHANGE*/
		if ((SIGNALCH == flow_msg->OP_Dcd)
				&& (HIGHLEVEL == flow_msg->ucDcd)) {
			capability |= MODEM_CTRL_DCD;
			pr_info("acm[%s] OP_Dcd CHANGE capability=0x%x\n",
				ACM_CDEV_GET_NAME(port->port_num), capability);
			port->stat_send_dcd++;
		};

		if (gser->notify_state)
			gser->notify_state(gser, capability);

		port->stat_send_capability = capability;
	}

	return 0;
}

static const struct file_operations gs_acm_cdev_fops = {
	.llseek     = no_llseek,
	.read       =       gs_acm_cdev_read,
	.write      =       gs_acm_cdev_write,
	.open       =       gs_acm_cdev_open,
	.release    =       gs_acm_cdev_close,
};

int gs_acm_open(unsigned int port_num)
{
	struct gs_acm_cdev_port *port;
	unsigned long flags;
	int status;

	D("port_num %d\n", port_num);

	if (port_num >= ACM_CDEV_COUNT) {
		pr_err("%s: invalid port_num %d\n", __func__, port_num);
		return -EINVAL;
	}

	do {
		mutex_lock(&gs_acm_cdev_ports[port_num].open_close_lock);
		port = gs_acm_cdev_ports[port_num].port;
		if (!port)
			status = -ENODEV;
		else {
			spin_lock_irqsave(&port->port_lock, flags);

			/* already open?  Great. */
			if (port->open_count) {
				status = 0;
				port->open_count++;

				/* currently opening/closing? wait ... */
			} else if (port->openclose) {
				status = -EBUSY;

				/* ... else we do the work */
			} else {
				status = -EAGAIN;
				port->openclose = true;
			}
			spin_unlock_irqrestore(&port->port_lock, flags);
		}
		mutex_unlock(&gs_acm_cdev_ports[port_num].open_close_lock);

		switch (status) {
		default:
			D("return\n");
			/* fully handled */
			return status;
		case -EAGAIN:
			/* must do the work */
			break;
		case -EBUSY:
			/* wait for EAGAIN task to finish */
			msleep(10);
			/* REVISIT could have a waitchannel here, if
			 * concurrent open performance is important
			 */
			break;
		}
	} while (status != -EAGAIN);

	spin_lock_irqsave(&port->port_lock, flags);
	port->open_count = 1;
	port->openclose = false;

	/* if connected, start the I/O stream */
	if (port->port_usb) {
		struct gserial  *gser = port->port_usb;
		if (gser->connect)
			gser->connect(gser);
	}

	spin_unlock_irqrestore(&port->port_lock, flags);

	D("-\n");
	return 0;
}

int gs_acm_close(unsigned int port_num)
{
	struct gs_acm_cdev_port *port;
	unsigned long flags;

	D("port_num %d\n", port_num);

	if (port_num >= ACM_CDEV_COUNT) {
		pr_err("%s: invalid port_num %d\n", __func__, port_num);
		return -EINVAL;
	}

	port = gs_acm_cdev_ports[port_num].port;
	if (!port) {
		pr_err("%s: port %d is not allocated\n", __func__, port_num);
		return -ENODEV;
	}

	spin_lock_irqsave(&port->port_lock, flags);

	if (port->open_count != 1) {
		if (port->open_count == 0) {
			WARN_ON(1);
		} else {
			--port->open_count;
		}
		goto exit;
	}

	/* mark port as closing but in use; we can drop port lock
	 * and sleep if necessary
	 */
	port->openclose = true;
	port->open_count = 0;
	port->line_state_on = 0;
	port->line_state_change = 0;

	if (port->port_usb) {
		struct gserial  *gser;
		gser = port->port_usb;
		if (gser && gser->disconnect)
			gser->disconnect(gser);
	}

	port->openclose = false;

	wake_up_interruptible(&port->close_wait);
exit:
	spin_unlock_irqrestore(&port->port_lock, flags);

	D("-\n");

	return 0;
}

ssize_t gs_acm_read(unsigned int port_num, char *buf,
				size_t count, loff_t *ppos)
{
	struct gs_acm_cdev_port *port;
	struct usb_request *reading_req;
	unsigned long flags;
	struct gs_acm_cdev_rw_priv *read_priv;
	unsigned int need_size = (unsigned int)count;
	unsigned int copy_size;
	unsigned int left_size;
	char *copy_addr;
	int status = 0;

	D("+\n");
	D("port_num %d\n", port_num);

	if (port_num >= ACM_CDEV_COUNT)
		return -EINVAL;

	port = gs_acm_cdev_ports[port_num].port;
	if (!port) {
		pr_err("[%s]port %d is not allocated\n", __func__, port_num);
		return -ENODEV;
	}

	port->stat_read_call++;
	if (unlikely(NULL == buf || 0 == count)) {
		pr_err("%s: param err, buf %p, count %ld\n",
					__func__, buf, count);
		port->stat_read_param_err++;
		return -EFAULT;
	}

	mutex_lock(&port->read_lock);
	do {
		spin_lock_irqsave(&port->port_lock, flags);
		if (!port->port_usb) {
			port->stat_sync_rx_disconnect++;
			spin_unlock_irqrestore(&port->port_lock, flags);
			goto read_exit;
		}

		reading_req = gs_acm_cdev_get_reading_req(port);

		if (NULL == reading_req) {
			D("no reading_req\n");
			/* if no req, wait for reading complete */
			port->read_blocked = 1;
			spin_unlock_irqrestore(&port->port_lock, flags);
			status = wait_event_interruptible
					 (port->read_wait, (port->read_blocked == 0));
			if (status) {
				pr_err("[%s]interrupted by signal, status %d\n", __func__, status);
				port->stat_sync_rx_wait_fail++;
				goto read_exit;
			}
		} else {
			spin_unlock_irqrestore(&port->port_lock, flags);
		}
	} while (NULL == reading_req);

	if (reading_req->status) {
		port->stat_sync_rx_done_fail++;
		port->reading_req = NULL;
		gs_acm_cdev_ret_reading_req(port, reading_req);
		goto read_exit;
	}

	/* prepare copy address and copy size */
	read_priv = (struct gs_acm_cdev_rw_priv *)reading_req->context;
	copy_addr = (char *)reading_req->buf + read_priv->copy_pos;
	left_size = reading_req->actual - read_priv->copy_pos;
	if (left_size > need_size) {
		copy_size = need_size;
		read_priv->copy_pos += copy_size;
		port->reading_req = reading_req;
	} else {
		copy_size = left_size;
		read_priv->copy_pos = 0;
		port->reading_req = NULL;
	}

	memcpy((void *)buf, (void *)copy_addr, copy_size);
	status = (int)copy_size;

	if (NULL == port->reading_req) {
		gs_acm_cdev_ret_reading_req(port, reading_req);
	}
	port->stat_sync_rx_done++;
	port->stat_sync_rx_done_bytes += copy_size;

read_exit:
	mutex_unlock(&port->read_lock);

	D("-\n");
	return (ssize_t)status;
}

ssize_t gs_acm_write(unsigned int port_num, const char *buf,
				size_t count, loff_t *ppos)
{
	struct gs_acm_cdev_port *port;
	unsigned int len = (unsigned int)count;
	int status;

	D("+\n");
	D("port_num %d\n", port_num);

	if (unlikely(NULL == buf || 0 == count)) {
		pr_err("%s invalid param buf:%p, count:%zu\n",
					__func__, buf, count);
		return -EFAULT;
	}

	if (port_num >= ACM_CDEV_COUNT)
		return -EINVAL;

	port = gs_acm_cdev_ports[port_num].port;
	if (!port) {
		pr_err("[%s]port %d is not allocated\n", __func__, port_num);
		return -ENODEV;
	}

	port->stat_sync_tx_submit++;
	status = gs_acm_cdev_write_base(port, (char *)buf, len, true);
	if (status > 0)
		port->stat_sync_tx_done++;
	else
		port->stat_sync_tx_fail++;

	D("-\n");
	return (ssize_t)status;
}

int gs_acm_ioctl(unsigned int port_num, unsigned int cmd, unsigned long arg)
{
	ACM_WR_ASYNC_INFO *rw_info;
	struct sk_buff *send_skb;
	struct gs_acm_cdev_port *port;
	int status = 0;

	D("+\n");

	if (port_num >= ACM_CDEV_COUNT) {
		pr_err("invalid port_num %d\n", port_num);
		return -EINVAL;
	}

	port = gs_acm_cdev_ports[port_num].port;
	if (!port) {
		pr_err("port %d is not allocated\n", port_num);
		return -ENODEV;
	}

	switch (cmd) {
	case ACM_IOCTL_SET_READ_CB:
	case UDI_IOCTL_SET_READ_CB:
		port->read_done_cb = (ACM_READ_DONE_CB_T)arg;
		break;

	case ACM_IOCTL_SET_WRITE_CB:
	case UDI_IOCTL_SET_WRITE_CB:
		port->write_done_cb = (ACM_WRITE_DONE_CB_T)arg;
		break;

	case ACM_IOCTL_SET_EVT_CB:
		port->event_notify_cb = (ACM_EVENT_CB_T)arg;
		if (port->port_num < ACM_CDEV_COUNT)
			gs_acm_cdev_ports[port->port_num].event_cb
						= (ACM_EVENT_CB_T)arg;
		break;

	case ACM_IOCTL_SET_FREE_CB:
		if (is_modem_port(port->port_num)) {
			port->write_done_free_cb = (ACM_FREE_CB_T)arg;
		} else {
			pr_err("ACM_IOCTL_SET_FREE_CB only for modem port\n");
			status = -EINVAL;
		}
		break;

	case ACM_IOCTL_WRITE_ASYNC:
		if (0 == arg) {
			pr_err("%s: %d: ACM_IOCTL_WRITE_ASYNC invalid param\n",
						__func__, port_num);
			return -EFAULT;
		}

		rw_info = (ACM_WR_ASYNC_INFO *)arg;
		port->stat_write_async_call++;

		/* For modem port, user may not init rw_info->u32Size */
		if (is_modem_port(port->port_num)) {
			send_skb = (struct sk_buff *)rw_info->pVirAddr;
			rw_info->u32Size = send_skb->len;
		}

		status = gs_acm_cdev_write_base(port, rw_info->pVirAddr, rw_info->u32Size, false);
		break;

	case ACM_IOCTL_GET_RD_BUFF:
		if (0 == arg) {
			pr_err("%s: %d: ACM_IOCTL_GET_RD_BUFF invalid param\n",
							__func__, port_num);
			return -EFAULT;
		}
		port->stat_get_buf_call++;
		status = gs_acm_cdev_get_read_buf(port, (ACM_WR_ASYNC_INFO *)arg);
		break;

	case ACM_IOCTL_RETURN_BUFF:
		if (0 == arg) {
			pr_err("%s: %d: ACM_IOCTL_RETURN_BUFF invalid param\n",
							__func__, port_num);
			return -EFAULT;
		}
		port->stat_ret_buf_call++;
		status = gs_acm_cdev_ret_read_buf(port, (ACM_WR_ASYNC_INFO *)arg);
		break;

	case ACM_IOCTL_RELLOC_READ_BUFF:
		if (0 == arg) {
			pr_err("%s: %d: ACM_IOCTL_RELLOC_READ_BUFF invalid param\n",
							__func__, port_num);
			return -EFAULT;
		}
		status = gs_acm_cdev_realloc_read_buf(port, (ACM_READ_BUFF_INFO *)arg);
		break;
	case ACM_IOCTL_WRITE_DO_COPY:
		port->is_do_copy = (bool)arg;
		break;
	case ACM_MODEM_IOCTL_SET_MSC_READ_CB:
		if (is_modem_port(port->port_num))
			port->read_sig_cb = (ACM_MODEM_MSC_READ_CB_T)arg;
		break;
	case ACM_MODEM_IOCTL_MSC_WRITE_CMD:
		if (is_modem_port(port->port_num))
			gs_acm_cdev_write_cmd(port, (MODEM_MSC_STRU *)arg);
		break;
	case ACM_MODEM_IOCTL_SET_REL_IND_CB:
		if (!is_modem_port(port->port_num))
			break;
		port->rel_ind_cb = (ACM_MODEM_REL_IND_CB_T)arg;
		/* if enumeration has done and rel_ind_cb has been registered,
		   then call rel_ind_cb for modem port */
		if (port->rel_ind_cb && (port->cur_evt == ACM_EVT_DEV_READY)) {
			pr_info("acm[%s] rel_ind_cb(%d)\n",
					ACM_CDEV_GET_NAME(port->port_num),
					ACM_EVT_DEV_READY);
			port->rel_ind_cb(ACM_EVT_DEV_READY);
		}
		break;
	default:
		pr_err("%s: unknown cmd 0x%x!\n", __func__, cmd);
		status = -1;
		break;
	}
	D("-\n");

	return status;
}

/*-------------------------------------------------------------------------*/

static int gs_acm_cdev_port_alloc(unsigned port_num, struct usb_cdc_line_coding *coding)
{
	struct gs_acm_cdev_port *port;
	int ret = 0;

	mutex_lock(&gs_acm_cdev_ports[port_num].open_close_lock);

	if (NULL != gs_acm_cdev_ports[port_num].port) {
		ret = -EBUSY;
		goto out;
	}

	port = kzalloc(sizeof(*port), GFP_KERNEL);
	if (port == NULL) {
		ret = -ENOMEM;
		goto out;
	}

	spin_lock_init(&port->port_lock);
	init_waitqueue_head(&port->close_wait);

	INIT_DELAYED_WORK(&port->rw_work, gs_acm_cdev_rw_push);

	INIT_LIST_HEAD(&port->read_pool);
	INIT_LIST_HEAD(&port->read_done_queue);
	INIT_LIST_HEAD(&port->read_using_queue);
	INIT_LIST_HEAD(&port->read_queue_in_usb);
	INIT_LIST_HEAD(&port->write_pool);
	INIT_LIST_HEAD(&port->write_queue);

	init_waitqueue_head(&port->write_wait);
	init_waitqueue_head(&port->read_wait);
	init_waitqueue_head(&port->realloc_wait);

	mutex_init(&port->write_lock);
	mutex_init(&port->read_lock);

	port->port_num = port_num;
	port->port_line_coding = *coding;

	port->read_buf_size = ACM_CDEV_DFT_RD_BUF_SIZE;
	port->read_req_num = ACM_CDEV_DFT_RD_REQ_NUM;
	port->write_req_num = gs_acm_cdev_get_tx_buf_num(port_num);
	port->is_do_copy = 1;

	scnprintf(port->read_domain, DOMAIN_NAME_LEN, "%d_rd", port_num);
	scnprintf(port->write_domain, DOMAIN_NAME_LEN, "%d_wt", port_num);
	scnprintf(port->debug_tx_domain, DOMAIN_NAME_LEN, "dtx%d", port_num);
	scnprintf(port->debug_rx_domain, DOMAIN_NAME_LEN, "drx%d", port_num);
	scnprintf(port->debug_port_domain, DOMAIN_NAME_LEN, "dpt%d", port_num);

	/* mark the asic string for debug */
	scnprintf(gs_acm_cdev_ports[port_num].name_domain, DOMAIN_NAME_LEN, "acm%d", port_num);

	gs_acm_cdev_ports[port_num].port = port;

	D("alloc port %d done!\n", port_num);

out:
	mutex_unlock(&gs_acm_cdev_ports[port_num].open_close_lock);

	return ret;
}

static int gs_acm_cdev_closed(struct gs_acm_cdev_port *port)
{
	int cond;
	unsigned long flags;

	spin_lock_irqsave(&port->port_lock, flags);
	cond = (port->open_count == 0) && !port->openclose;
	spin_unlock_irqrestore(&port->port_lock, flags);

	return cond;
}

static void gs_acm_cdev_port_free(unsigned int port_num)
{
	struct gs_acm_cdev_port *port;
	int ret;

	D("+\n");

	/* prevent new opens */
	mutex_lock(&gs_acm_cdev_ports[port_num].open_close_lock);

	port = gs_acm_cdev_ports[port_num].port;
	gs_acm_cdev_ports[port_num].port = NULL;

	mutex_unlock(&gs_acm_cdev_ports[port_num].open_close_lock);

	/* wait for old opens to finish */
	ret = wait_event_interruptible(port->close_wait, gs_acm_cdev_closed(port));
	if (ret)
		pr_err("[%s]wait for old opens finish failed\n", __func__);

	WARN_ON(port->port_usb != NULL);

	mutex_destroy(&port->write_lock);
	mutex_destroy(&port->read_lock);

	kfree(port);

	D("-\n");
}

static struct u_cdev_driver *gs_acm_cdev_alloc_driver(int lines)
{
	struct u_cdev_driver *driver;

	D("+\n");

	driver = kzalloc(sizeof(struct u_cdev_driver), GFP_KERNEL);
	if (driver) {
		kref_init(&driver->kref);
		driver->num = lines;
	}

	D("-\n");
	return driver;
}

static int gs_acm_cdev_register_driver(struct u_cdev_driver *driver)
{
	int error;
	dev_t dev;

	D("+\n");

	error = alloc_chrdev_region(&dev, driver->minor_start,
				driver->num, driver->name);
	if (error < 0)
		return error;

	driver->major = MAJOR(dev);
	driver->minor_start = MINOR(dev);

	cdev_init(&driver->cdev, &gs_acm_cdev_fops);
	driver->cdev.owner = driver->owner;
	error = cdev_add(&driver->cdev, dev, driver->num);
	if (error) {
		unregister_chrdev_region(dev, driver->num);
		return error;
	}
	driver->dev_no = dev;

	D("-\n");

	return 0;
}

static void gs_acm_cdev_unregister_driver(struct u_cdev_driver *driver)
{
	cdev_del(&driver->cdev);
	return unregister_chrdev_region(gs_cdev_driver->dev_no, gs_cdev_driver->num);
}

static struct device *gs_acm_cdev_register_device(struct u_cdev_driver *driver,
		unsigned index, struct device *parent)
{
	char name[ACM_CDEV_NAME_MAX];
	dev_t dev = MKDEV(driver->major, driver->minor_start) + index;

	if (index >= driver->num) {
		pr_err("Attempt to register invalid tty line number (%d).\n", index);
		return ERR_PTR(-EINVAL);
	}
	scnprintf(name, ACM_CDEV_NAME_MAX, "%s",
			  ACM_CDEV_GET_NAME(index));

	return device_create(tty_class, parent, dev, NULL, name);
}

static void gs_acm_cdev_unregister_device(struct u_cdev_driver *driver,
		unsigned index)
{
	device_destroy(tty_class,
			MKDEV(driver->major, driver->minor_start) + index);
}

static int gs_acm_usb_notifier_cb(struct notifier_block *nb,
				unsigned long event, void *priv)
{
	int i;
	struct gs_acm_cdev_port *port = NULL;
	MODEM_MSC_STRU *flow_msg = NULL;

	D("+\n");
	pr_info("%s: event:%lu\n", __func__, event);

	/*  event <= 0 means:
	 *  USB_BALONG_DEVICE_DISABLE or USB_BALONG_DEVICE_REMOVE
	 */
	if (USB_BALONG_DEVICE_DISABLE == event ||
			USB_BALONG_DEVICE_REMOVE == event) {

		for (i = 0; i < ACM_CDEV_COUNT; i++) {
			if (gs_acm_cdev_ports[i].event_cb)
				gs_acm_cdev_ports[i].event_cb(
						ACM_EVT_DEV_SUSPEND);

			port = gs_acm_cdev_ports[i].port;
			if (port && port->line_state_on) {
				if (port->read_sig_cb) {
					flow_msg = &port->flow_msg;
					flow_msg->OP_Dtr = SIGNALCH;
					flow_msg->ucDtr = SIGNALNOCH;
					pr_info("acm[%s] read_sig_cb\n",
						ACM_CDEV_GET_NAME(port->port_num));
					port->read_sig_cb(flow_msg);
					flow_msg->OP_Dtr = SIGNALNOCH;
				}
				port->line_state_on = 0;
			}

			if (port && port->rel_ind_cb
				&& (port->cur_evt == ACM_EVT_DEV_READY)) {
				pr_info("acm[%s] rel_ind_cb(%d)\n",
					    ACM_CDEV_GET_NAME(port->port_num),
					    ACM_EVT_DEV_SUSPEND);
				port->rel_ind_cb(ACM_EVT_DEV_SUSPEND);
				port->cur_evt = ACM_EVT_DEV_SUSPEND;
			}
		}
	}

	D("-\n");
	return 0;
}

/* called by free instance */
void gs_acm_cdev_free_line(unsigned char port_num)
{
	D("+\n");
	gs_acm_cdev_unregister_device(gs_cdev_driver, port_num);
	gs_acm_cdev_port_free(port_num);
	D("-\n");
}

/* called by alloc instance */
int gs_acm_cdev_alloc_line(unsigned char *line_num)
{
	struct usb_cdc_line_coding  coding;
	struct device   *cdev;
	int port_num;
	int ret = 0;

	D("+\n");

	if (NULL == gs_cdev_driver) {
		pr_err("[%s]NOENT!n", __func__);
		return -ENODEV;
	}

	coding.dwDTERate = cpu_to_le32(115200);
	coding.bCharFormat = 8;
	coding.bParityType = USB_CDC_NO_PARITY;
	coding.bDataBits = USB_CDC_1_STOP_BITS;


	/* alloc and init each port */
	for (port_num = 0; port_num < ACM_CDEV_COUNT; port_num++) {

		ret = gs_acm_cdev_port_alloc(port_num, &coding);
		if (ret == -EBUSY)
			continue;
		if (ret)
			return ret;
		break;
	}
	if (ret)
		return ret;

	D("got a free port, port_num: %d\n", port_num);

	/* will call device_create, ueventd will mknod for this device */
	cdev = gs_acm_cdev_register_device(gs_cdev_driver, port_num, NULL);
	if (IS_ERR(cdev)) {
		pr_err("%s: regist cdev failed for port %d, err %ld\n",
				   __func__, port_num, PTR_ERR(cdev));
		ret = PTR_ERR(cdev);
		goto fail;
	}
	gs_acm_cdev_ports[port_num].cdev = cdev;

	*line_num = port_num;

	D("-\n");

	return ret;
fail:
	pr_err("[%s]failed!\n", __func__);
	gs_acm_cdev_port_free(port_num);
	return ret;
}

static int balong_acm_init(void)
{
	unsigned i;
	int status;

	D("+\n");

	gs_cdev_driver = gs_acm_cdev_alloc_driver(ACM_CDEV_COUNT);
	if (!gs_cdev_driver)
		return -ENOMEM;

	gs_cdev_driver->owner = THIS_MODULE;
	gs_cdev_driver->driver_name = ACM_CDEV_DRV_NAME;
	gs_cdev_driver->name = ACM_CDEV_PREFIX;

	gs_acm_evt_init(&gs_acm_write_evt_manage, "write_evt");
	gs_acm_evt_init(&gs_acm_read_evt_manage, "read_evt");
	gs_acm_evt_init(&gs_acm_sig_stat_evt_manage, "sig_stat_evt");

	/* this num equals to ACM_CDEV_COUNT */
	gs_acm_cdev_n_ports = gs_cdev_driver->num;

	for (i = 0; i < ACM_CDEV_COUNT; i++)
		mutex_init(&gs_acm_cdev_ports[i].open_close_lock);

	/* register char devices and it's driver  */
	status = gs_acm_cdev_register_driver(gs_cdev_driver);
	if (status) {
		pr_err("%s: cannot register, err %d\n", __func__, status);
		goto fail1;
	}

	gs_cdev_driver->acm_work_queue = create_singlethread_workqueue("acm_cdev");
	if (!gs_cdev_driver->acm_work_queue) {
		status = -ENOMEM;
		pr_err("[%s]no memory\n", __func__);
		goto fail2;
	}

	/* we just regist once, and don't unregist any more */
	if (!gs_acm_nb_ptr) {
		gs_acm_nb_ptr = &gs_acm_nb;
		gs_acm_nb.priority = USB_NOTIF_PRIO_FD;
		gs_acm_nb.notifier_call = gs_acm_usb_notifier_cb;
		bsp_usb_register_notify(gs_acm_nb_ptr);
	}

	D("-\n");

	return status;

fail2:
	gs_acm_cdev_unregister_driver(gs_cdev_driver);
fail1:
	if (gs_cdev_driver) {
		kfree(gs_cdev_driver);
		gs_cdev_driver = NULL;
	}
	return status;
}
module_init(balong_acm_init);

static void balong_acm_exit(void)
{
	D("+\n");
	if (!gs_cdev_driver)
		return;

	gs_acm_cdev_n_ports = 0;
	gs_acm_cdev_unregister_driver(gs_cdev_driver);

	if (gs_cdev_driver->acm_work_queue) {
		destroy_workqueue(gs_cdev_driver->acm_work_queue);
		gs_cdev_driver->acm_work_queue = NULL;
	}

	if (gs_cdev_driver) {
		kfree(gs_cdev_driver);
		gs_cdev_driver = NULL;
	}
	D("-\n");
}
module_exit(balong_acm_exit);

/* called by acm_setup f_balong_acm.c */
int gacm_cdev_line_state(struct gserial *gser, u8 port_num, u32 state)
{
	struct gs_acm_cdev_port *port;
	unsigned long flags;
	u16 line_state;

	D("+\n");

	if (!gs_cdev_driver || port_num >= gs_acm_cdev_n_ports) {
		pr_emerg("gacm_cdev_connect fail drv:%p, port_num:%d, n_ports:%d\n",
				gs_cdev_driver, port_num, gs_acm_cdev_n_ports);
		return -ENXIO;
	}

	port = gs_acm_cdev_ports[port_num].port;
	D("port_num %d, state 0x%x\n", port->port_num, state);

	spin_lock_irqsave(&port->port_lock, flags);
	line_state = port->line_state_on;

	/* if line state is change notify the callback */
	if (line_state != (u16)(state & U_ACM_CTRL_DTR)) {
		port->line_state_on = (u16)(state & U_ACM_CTRL_DTR);
		port->line_state_change = 1;

		pr_info("acm[%d] old_DTR_value = %d, ucDtr = %d\n",
			port_num, line_state, port->line_state_on);
	}
	spin_unlock_irqrestore(&port->port_lock, flags);

	/* host may change the state in a short time, delay it, use the last state */
	if (port->line_state_change) {
		gs_acm_evt_push(port, &gs_acm_sig_stat_evt_manage);
		queue_delayed_work(gs_cdev_driver->acm_work_queue,
				&port->rw_work, 50); /* gs_acm_cdev_rw_push */

		port->stat_notify_sched++;
	}

	D("-\n");

	return 0;
}

/**
 * gacm_cdev_connect - notify TTY I/O glue that USB link is active
 * @gser: the function, set up with endpoints and descriptors
 * @port_num: which port is active
 * Context: any (usually from irq)
 *
 * This is called activate endpoints and let the TTY layer know that
 * the connection is active ... not unlike "carrier detect".  It won't
 * necessarily start I/O queues; unless the TTY is held open by any
 * task, there would be no point.  However, the endpoints will be
 * activated so the USB host can perform I/O, subject to basic USB
 * hardware flow control.
 *
 * Caller needs to have set up the endpoints and USB function in @dev
 * before calling this, as well as the appropriate (speed-specific)
 * endpoint descriptors, and also have set up the TTY driver by calling
 * @gserial_setup().
 *
 * Returns negative errno or zero.
 * On success, ep->driver_data will be overwritten.
 */
int gacm_cdev_connect(struct gserial *gser, u8 port_num)
{
	struct gs_acm_cdev_port *port;
	unsigned long flags;
	int status;

	D("+\n");
	D("port_num: %d\n", port_num);

	if (!gs_cdev_driver || port_num >= gs_acm_cdev_n_ports) {
		pr_emerg("gacm_cdev_connect fail drv:%p, port_num:%d, n_ports:%d\n",
				 gs_cdev_driver, port_num, gs_acm_cdev_n_ports);
		BUG();
		return -ENXIO;
	}

	/* we "know" gserial_cleanup() hasn't been called */
	port = gs_acm_cdev_ports[port_num].port;

	/* activate the endpoints */
	status = usb_ep_enable(gser->in);
	if (status < 0) {
		port->stat_enable_in_fail++;
		pr_err("[%s] in fail, status %d\n", __func__, status);
		return status;
	}

	status = usb_ep_enable(gser->out);
	if (status < 0) {
		port->stat_enable_out_fail++;
		pr_err("[%s] out fail, status %d\n", __func__, status);
		goto fail_out;
	}

	/* then tell the tty glue that I/O can work */
	spin_lock_irqsave(&port->port_lock, flags);

	gser->in->driver_data = port;
	gser->out->driver_data = port;

	gser->ioport = (void *)port;
	port->port_usb = gser;
	port->cur_evt = ACM_EVT_DEV_READY;
	/* REVISIT unclear how best to handle this state...
	 * we don't really couple it with the Linux TTY.
	 */
	gser->port_line_coding = port->port_line_coding;

	/* prepare requests */
	gs_acm_cdev_prepare_io(port);

	/* if it's already open, start I/O ... and notify the serial
	 * protocol about open/close status (connect/disconnect).
	 * don't need to notify host now ...
	 */
	if (port->open_count) {
		if (gser->connect)
			gser->connect(gser);
	} else {
		if (gser->disconnect)
			gser->disconnect(gser);
	}

	/* start read requests */
	D("port %d strat rx\n", port_num);
	gs_acm_cdev_start_rx(port);

	spin_unlock_irqrestore(&port->port_lock, flags);

	port->in_name = (char *)gser->in->name;
	port->out_name = (char *)gser->out->name;
	port->stat_port_connect++;
	port->stat_port_is_connect = 1;

	D("-\n");
	return status;

fail_out:
	usb_ep_disable(gser->in);
	gser->in->driver_data = NULL;
	port->stat_port_is_connect = 0;
	return status;
}

/**
 * gacm_cdev_disconnect - notify TTY I/O glue that USB link is inactive
 * @gser: the function, on which gserial_connect() was called
 * Context: any (usually from irq)
 *
 * This is called to deactivate endpoints and let the TTY layer know
 * that the connection went inactive ... not unlike "hangup".
 *
 * On return, the state is as if gserial_connect() had never been called;
 * there is no active USB I/O on these endpoints.
 */
void gacm_cdev_disconnect(struct gserial *gser)
{
	struct gs_acm_cdev_port *port = gser->ioport;
	unsigned long   flags;

	D("+\n");

	if (!port) {
		BUG();
		return;
	}

	/* disable endpoints, aborting down any active I/O */
	usb_ep_disable(gser->out);
	usb_ep_disable(gser->in);

	spin_lock_irqsave(&port->port_lock, flags);

	port->port_usb = NULL;
	gser->ioport = NULL;
	gser->out->driver_data = NULL;
	gser->in->driver_data = NULL;

	gs_acm_cdev_free_requests(gser->out, &port->read_pool, NULL);
	gs_acm_cdev_free_requests(gser->out, &port->read_done_queue, NULL);
	gs_acm_cdev_free_requests(gser->out, &port->read_using_queue, NULL);
	gs_acm_cdev_free_requests(gser->in, &port->write_pool, NULL);
	gs_acm_cdev_free_requests(gser->in, &port->write_queue, NULL);
	port->read_allocated = 0;
	port->write_allocated = 0;

	spin_unlock_irqrestore(&port->port_lock, flags);

	port->stat_port_disconnect++;
	port->stat_port_is_connect = 0;

	if (port->read_blocked) {
		port->read_blocked = 0;

		port->stat_rx_wakeup_block++;

		wake_up_interruptible(&port->read_wait);
	}
	D("-\n");
}

/* called by f_balong_acm.c acm_resume */
void gacm_cdev_resume_notify(struct gserial *gser)
{
	struct gs_acm_cdev_port *port = gser->ioport;

	pr_info("acm[%s] resume\n", ACM_CDEV_GET_NAME(port->port_num));

	if (port->rel_ind_cb && (port->cur_evt == ACM_EVT_DEV_SUSPEND)) {
		pr_info("acm[%s] rel_ind_cb(%d)\n",
			ACM_CDEV_GET_NAME(port->port_num), ACM_EVT_DEV_READY);
		port->rel_ind_cb(ACM_EVT_DEV_READY);
		port->cur_evt = ACM_EVT_DEV_READY;
	}
}

/* called by f_balong_acm.c acm_suspend */
void gacm_cdev_suspend_notify(struct gserial *gser)
{
	struct gs_acm_cdev_port *port = gser->ioport;
	MODEM_MSC_STRU *flow_msg = &port->flow_msg;

	pr_info("acm[%s] suspend\n", ACM_CDEV_GET_NAME(port->port_num));

	if (port->line_state_on) {
		if (port->read_sig_cb) {
			flow_msg->OP_Dtr = SIGNALCH;
			flow_msg->ucDtr = SIGNALNOCH;
			pr_info("acm[%s] read_sig_cb\n",
					ACM_CDEV_GET_NAME(port->port_num));
			port->read_sig_cb(flow_msg);
			flow_msg->OP_Dtr = SIGNALNOCH;
		}

		if (port->event_notify_cb) {
			pr_info("acm[%s] event_notify_cb\n\n",
					ACM_CDEV_GET_NAME(port->port_num));
			port->event_notify_cb(ACM_EVT_DEV_SUSPEND);
		}
		port->line_state_on = 0;

	}

	if (port->rel_ind_cb && (port->cur_evt == ACM_EVT_DEV_READY)) {
		pr_info("acm[%s] rel_ind_cb(%d)\n",
			ACM_CDEV_GET_NAME(port->port_num), ACM_EVT_DEV_SUSPEND);
		port->rel_ind_cb(ACM_EVT_DEV_SUSPEND);
		port->cur_evt = ACM_EVT_DEV_SUSPEND;
	}
}

#define ACM_PRINT_IOCTL(cmd, s) seq_printf(s, "comand:%s\t\t\t\tcode:0x%x\n", #cmd, cmd);
int acm_cdev_ioctl_dump(struct seq_file *s)
{
	if (!s) {
		pr_err("dump ioctl error, seq file is null\n");
		return -ENOMEM;
	}
	ACM_PRINT_IOCTL(ACM_IOCTL_SET_WRITE_CB, s);
	ACM_PRINT_IOCTL(ACM_IOCTL_SET_READ_CB, s);
	ACM_PRINT_IOCTL(ACM_IOCTL_SET_EVT_CB, s);
	ACM_PRINT_IOCTL(ACM_IOCTL_SET_FREE_CB, s);
	ACM_PRINT_IOCTL(ACM_IOCTL_WRITE_DO_COPY, s);
	ACM_PRINT_IOCTL(ACM_IOCTL_WRITE_ASYNC, s);
	ACM_PRINT_IOCTL(ACM_IOCTL_GET_RD_BUFF, s);
	ACM_PRINT_IOCTL(ACM_IOCTL_RETURN_BUFF, s);
	ACM_PRINT_IOCTL(ACM_IOCTL_RELLOC_READ_BUFF, s);
	return 0;
}
#undef ACM_PRINT_IOCTL

#define ACM_PRINT_ERRNO(err, s) seq_printf(s, "%s\t\t\t\t%d\t0x%08x\n", #err, -err, -err);
int acm_cdev_errno_dump(struct seq_file *s)
{
	if (!s) {
		pr_err("dump errno error, seq file is null\n");
		return -ENOMEM;
	}
	ACM_PRINT_ERRNO(EAGAIN, s);
	ACM_PRINT_ERRNO(ENOMEM, s);
	ACM_PRINT_ERRNO(ENODEV, s);
	ACM_PRINT_ERRNO(EFAULT, s);
	ACM_PRINT_ERRNO(ESHUTDOWN, s);
	ACM_PRINT_ERRNO(ENXIO, s);
	ACM_PRINT_ERRNO(EBUSY, s);
	ACM_PRINT_ERRNO(EBADF, s);
	ACM_PRINT_ERRNO(EINVAL, s);
	return 0;
}
#undef ACM_PRINT_ERRNO

static void acm_cdev_dump_ep_info(struct seq_file *s, struct gs_acm_cdev_port *port)
{
	char *find;
	unsigned ep_num;

	if (!s) {
		pr_err("dump ep info, seq file is null\n");
		return ;
	}

	if (port->stat_port_is_connect) {
		seq_printf(s, "in ep name:\t\t <%s>\n", port->in_name);
		find = strstr(port->in_name, "ep");
		if (find) {
			/* skip "ep" */
			find += 2;
			ep_num = simple_strtoul(find, NULL, 0);
			seq_printf(s, "in ep num:\t\t <%d>\n", ep_num * 2 + 1);
		}
		seq_printf(s, "out ep name:\t\t <%s>\n", port->out_name);
		find = strstr(port->out_name, "ep");
		if (find) {
			/* skip "ep" */
			find += 2;
			ep_num = simple_strtoul(find, NULL, 0);
			seq_printf(s, "out ep num:\t\t <%d>\n", ep_num * 2);
		}
	} else {
		seq_printf(s, "the acm dev is not connect\n");
	}
}

void hiusb_do_acm_cdev_dump(struct seq_file *s, unsigned int port_num)
{
	struct gs_acm_cdev_port *port;

	if (!s) {
		pr_err("hiusb_do_acm_cdev_dump err, seq file is null\n");
		return ;
	}

	if (!gs_cdev_driver || port_num >= gs_acm_cdev_n_ports) {
		seq_printf(s, "gacm_dump fail drv:%p, port_num:%d, n_ports:%d\n",
				 gs_cdev_driver, port_num, gs_acm_cdev_n_ports);
		return ;
	}

	port = gs_acm_cdev_ports[port_num].port;

	seq_printf(s, "=== dump stat dev ctx info ===\n");
	seq_printf(s, "port_usb                  %p\n", port->port_usb);
	seq_printf(s, "build version:            %s\n", __VERSION__);
	seq_printf(s, "build date:               %s\n", __DATE__);
	seq_printf(s, "build time:               %s\n", __TIME__);
	seq_printf(s, "dev name                  %s\n", ACM_CDEV_GET_NAME(port_num));
	seq_printf(s, "gs_stat_drv_invalid       %d\n", gs_stat_drv_invalid);
	seq_printf(s, "gs_stat_port_num_err      %d\n", gs_stat_port_num_err);
	seq_printf(s, "open_count                %d\n", port->open_count);
	seq_printf(s, "openclose                 %d\n", port->openclose);
	seq_printf(s, "is_do_copy                %d\n", port->is_do_copy);
	seq_printf(s, "port_num                  %d\n", port->port_num);
	seq_printf(s, "line_state_on             %d\n", port->line_state_on);
	seq_printf(s, "line_state_change         %d\n", port->line_state_change);
	acm_cdev_dump_ep_info(s, port);

	mdelay(10);
	seq_printf(s, "\n=== dump stat read info ===\n");
	seq_printf(s, "read_started              %d\n", port->read_started);
	seq_printf(s, "read_allocated            %d\n", port->read_allocated);
	seq_printf(s, "read_req_enqueued         %d\n", port->read_req_enqueued);
	seq_printf(s, "read_req_num              %d\n", port->read_req_num);
	seq_printf(s, "read_buf_size             %d\n", port->read_buf_size);
	seq_printf(s, "read_completed            %d\n", port->read_completed);
	seq_printf(s, "reading_pos               %d\n", port->reading_pos);

	seq_printf(s, "\n=== dump rx status info ===\n");
	seq_printf(s, "stat_read_call            %d\n", port->stat_read_call);
	seq_printf(s, "stat_get_buf_call         %d\n", port->stat_get_buf_call);
	seq_printf(s, "stat_ret_buf_call         %d\n", port->stat_ret_buf_call);
	seq_printf(s, "stat_read_param_err       %d\n", port->stat_read_param_err);
	seq_printf(s, "read_blocked              %d\n", port->read_blocked);
	seq_printf(s, "stat_sync_rx_submit       %d\n", port->stat_sync_rx_submit);
	seq_printf(s, "stat_sync_rx_done         %d\n", port->stat_sync_rx_done);
	seq_printf(s, "stat_sync_rx_done_fail    %d\n", port->stat_sync_rx_done_fail);
	seq_printf(s, "stat_sync_rx_done_bytes   %d\n", port->stat_sync_rx_done_bytes);
	seq_printf(s, "stat_sync_rx_copy_fail    %d\n", port->stat_sync_rx_copy_fail);
	seq_printf(s, "stat_sync_rx_disconnect   %d\n", port->stat_sync_rx_disconnect);
	seq_printf(s, "stat_sync_rx_wait_fail    %d\n", port->stat_sync_rx_wait_fail);
	seq_printf(s, "stat_rx_submit            %d\n", port->stat_rx_submit);
	seq_printf(s, "stat_rx_submit_fail       %d\n", port->stat_rx_submit_fail);
	seq_printf(s, "stat_rx_disconnect        %d\n", port->stat_rx_disconnect);
	seq_printf(s, "stat_rx_no_req            %d\n", port->stat_rx_no_req);
	seq_printf(s, "stat_rx_done              %d\n", port->stat_rx_done);
	seq_printf(s, "stat_rx_done_fail         %d\n", port->stat_rx_done_fail);
	seq_printf(s, "stat_rx_done_bytes        %d\n", port->stat_rx_done_bytes);
	seq_printf(s, "stat_rx_done_disconnect   %d\n", port->stat_rx_done_disconnect);
	seq_printf(s, "stat_rx_done_schdule      %d\n", port->stat_rx_done_schdule);
	seq_printf(s, "stat_rx_wakeup_block      %d\n", port->stat_rx_wakeup_block);
	seq_printf(s, "stat_rx_wakeup_realloc    %d\n", port->stat_rx_wakeup_realloc);
	seq_printf(s, "stat_rx_callback          %d\n", port->stat_rx_callback);
	seq_printf(s, "stat_rx_cb_not_start      %d\n", port->stat_rx_cb_not_start);
	seq_printf(s, "stat_rx_dequeue           %d\n", port->stat_rx_dequeue);

	mdelay(10);
	seq_printf(s, "\n=== dump stat write info ===\n");
	seq_printf(s, "write_req_num             %d\n", port->write_req_num);
	seq_printf(s, "write_started             %d\n", port->write_started);
	seq_printf(s, "write_completed           %d\n", port->write_completed);
	seq_printf(s, "write_allocated           %d\n", port->write_allocated);
	seq_printf(s, "write_blocked             %d\n", port->write_blocked);
	seq_printf(s, "write_block_status        %d\n", port->write_block_status);

	seq_printf(s, "\n=== dump tx status info ===\n");
	seq_printf(s, "stat_write_async_call     %d\n", port->stat_write_async_call);
	seq_printf(s, "stat_write_param_err      %d\n", port->stat_write_param_err);
	seq_printf(s, "stat_sync_tx_submit       %d\n", port->stat_sync_tx_submit);
	seq_printf(s, "stat_sync_tx_done         %d\n", port->stat_sync_tx_done);
	seq_printf(s, "stat_sync_tx_fail         %d\n", port->stat_sync_tx_fail);
	seq_printf(s, "stat_sync_tx_wait_fail    %d\n", port->stat_sync_tx_wait_fail);
	seq_printf(s, "stat_tx_submit            %d\n", port->stat_tx_submit);
	seq_printf(s, "stat_tx_submit_fail       %d\n", port->stat_tx_submit_fail);
	seq_printf(s, "stat_tx_submit_bytes      %d\n", port->stat_tx_submit_bytes);
	seq_printf(s, "stat_tx_done              %d\n", port->stat_tx_done);
	seq_printf(s, "stat_tx_done_fail         %d\n", port->stat_tx_done_fail);
	seq_printf(s, "stat_tx_done_bytes        %d\n", port->stat_tx_done_bytes);
	seq_printf(s, "stat_tx_done_schdule      %d\n", port->stat_tx_done_schdule);
	seq_printf(s, "stat_tx_done_disconnect   %d\n", port->stat_tx_done_disconnect);
	seq_printf(s, "stat_tx_wakeup_block      %d\n", port->stat_tx_wakeup_block);
	seq_printf(s, "stat_tx_callback          %d\n", port->stat_tx_callback);
	seq_printf(s, "stat_tx_no_req            %d\n", port->stat_tx_no_req);
	seq_printf(s, "stat_tx_copy_fail         %d\n", port->stat_tx_copy_fail);
	seq_printf(s, "stat_tx_alloc_fail        %d\n", port->stat_tx_alloc_fail);
	seq_printf(s, "stat_tx_disconnect        %d\n", port->stat_tx_disconnect);

	mdelay(10);
	seq_printf(s, "\n=== dump port status info ===\n");
	seq_printf(s, "stat_port_connect         %d\n", port->stat_port_connect);
	seq_printf(s, "stat_port_disconnect      %d\n", port->stat_port_disconnect);
	seq_printf(s, "stat_enable_in_fail       %d\n", port->stat_enable_in_fail);
	seq_printf(s, "stat_enable_out_fail      %d\n", port->stat_enable_out_fail);
	seq_printf(s, "stat_notify_sched         %d\n", port->stat_notify_sched);
	seq_printf(s, "stat_notify_on_cnt        %d\n", port->stat_notify_on_cnt);
	seq_printf(s, "stat_notify_off_cnt       %d\n", port->stat_notify_off_cnt);
	seq_printf(s, "cur_evt                   %d\n", port->cur_evt);

	mdelay(10);
	seq_printf(s, "\n=== dump call back info ===\n");
	seq_printf(s, "read_done_cb              %p\n", port->read_done_cb);
	seq_printf(s, "write_done_cb             %p\n", port->write_done_cb);
	seq_printf(s, "write_done_free_cb        %p\n", port->write_done_free_cb);
	seq_printf(s, "event_notify_cb           %p\n", port->event_notify_cb);
	seq_printf(s, "read_sig_cb               %p\n", port->read_sig_cb);
	seq_printf(s, "rel_ind_cb                %p\n", port->rel_ind_cb);

	if (is_modem_port(port_num)) {
		seq_printf(s, "\n=== dump send signal info ===\n");
		seq_printf(s, "stat_send_cts_stat        %d\n", port->stat_send_cts_stat);
		seq_printf(s, "stat_send_cts_enable      %d\n", port->stat_send_cts_enable);
		seq_printf(s, "stat_send_cts_disable     %d\n", port->stat_send_cts_disable);
		seq_printf(s, "stat_send_ri              %d\n", port->stat_send_ri);
		seq_printf(s, "stat_send_dsr             %d\n", port->stat_send_dsr);
		seq_printf(s, "stat_send_dcd             %d\n", port->stat_send_dcd);
		seq_printf(s, "stat_send_capability    0x%x\n", port->stat_send_capability);
	}
}

void hiusb_do_acm_cdev_port_dump(struct seq_file *s)
{
	int port_num = 0;

	if (!s) {
		pr_err("%s err, seq file is null\n", __func__);
		return ;
	}
	seq_printf(s, "\n== current acm port list ==\n");
	for (port_num = 0; port_num < gs_acm_cdev_n_ports; port_num++) {
		seq_printf(s, "port: %d : %s\n", port_num, ACM_CDEV_GET_NAME(port_num));
	}
}
