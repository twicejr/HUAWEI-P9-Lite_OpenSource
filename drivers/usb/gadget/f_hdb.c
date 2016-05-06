/*
 * Gadget Driver for Android hdb
 *
 * Copyright (C) 2008 Google, Inc.
 * Author: Mike Lockwood <lockwood@android.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/poll.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/miscdevice.h>

#define hdb_BULK_BUFFER_SIZE           32768

/* number of tx requests to allocate */
#define TX_REQ_MAX 4

static const char hdb_shortname[] = "android_hdb";

struct hdb_dev {
	struct usb_function function;
	struct usb_composite_dev *cdev;
	spinlock_t lock;

	struct usb_ep *ep_in;
	struct usb_ep *ep_out;

	int online;
	int error;

	atomic_t read_excl;
	atomic_t write_excl;
	atomic_t open_excl;

	struct list_head tx_idle;

	wait_queue_head_t read_wq;
	wait_queue_head_t write_wq;
	struct usb_request *rx_req;
	int rx_done;
};

static struct usb_interface_descriptor hdb_interface_desc = {
	.bLength                = USB_DT_INTERFACE_SIZE,
	.bDescriptorType        = USB_DT_INTERFACE,
	.bInterfaceNumber       = 0,
	.bNumEndpoints          = 2,
	.bInterfaceClass        = 0xFF,
	.bInterfaceSubClass     = 0x48,
	.bInterfaceProtocol     = 1,
};

static struct usb_endpoint_descriptor hdb_superspeed_in_desc = {
       .bLength                = USB_DT_ENDPOINT_SIZE,
       .bDescriptorType        = USB_DT_ENDPOINT,
       .bEndpointAddress       = USB_DIR_IN,
       .bmAttributes           = USB_ENDPOINT_XFER_BULK,
       .wMaxPacketSize         = __constant_cpu_to_le16(1024),
};

static struct usb_endpoint_descriptor hdb_superspeed_out_desc = {
       .bLength                = USB_DT_ENDPOINT_SIZE,
       .bDescriptorType        = USB_DT_ENDPOINT,
       .bEndpointAddress       = USB_DIR_OUT,
       .bmAttributes           = USB_ENDPOINT_XFER_BULK,
       .wMaxPacketSize         = __constant_cpu_to_le16(1024),
};

static struct usb_ss_ep_comp_descriptor hdb_superspeed_comp_desc = {
       .bLength                = USB_DT_SS_EP_COMP_SIZE,
       .bDescriptorType        = USB_DT_SS_ENDPOINT_COMP,
       .bMaxBurst              = 1,
};
static struct usb_endpoint_descriptor hdb_highspeed_in_desc = {
	.bLength                = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType        = USB_DT_ENDPOINT,
	.bEndpointAddress       = USB_DIR_IN,
	.bmAttributes           = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize         = __constant_cpu_to_le16(512),
};

static struct usb_endpoint_descriptor hdb_highspeed_out_desc = {
	.bLength                = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType        = USB_DT_ENDPOINT,
	.bEndpointAddress       = USB_DIR_OUT,
	.bmAttributes           = USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize         = __constant_cpu_to_le16(512),
};

static struct usb_endpoint_descriptor hdb_fullspeed_in_desc = {
	.bLength                = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType        = USB_DT_ENDPOINT,
	.bEndpointAddress       = USB_DIR_IN,
	.bmAttributes           = USB_ENDPOINT_XFER_BULK,
};

static struct usb_endpoint_descriptor hdb_fullspeed_out_desc = {
	.bLength                = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType        = USB_DT_ENDPOINT,
	.bEndpointAddress       = USB_DIR_OUT,
	.bmAttributes           = USB_ENDPOINT_XFER_BULK,
};

static struct usb_descriptor_header *fs_hdb_descs[] = {
	(struct usb_descriptor_header *) &hdb_interface_desc,
	(struct usb_descriptor_header *) &hdb_fullspeed_in_desc,
	(struct usb_descriptor_header *) &hdb_fullspeed_out_desc,
	NULL,
};

static struct usb_descriptor_header *hs_hdb_descs[] = {
	(struct usb_descriptor_header *) &hdb_interface_desc,
	(struct usb_descriptor_header *) &hdb_highspeed_in_desc,
	(struct usb_descriptor_header *) &hdb_highspeed_out_desc,
	NULL,
};

static struct usb_descriptor_header *ss_hdb_descs[] = {
       (struct usb_descriptor_header *) &hdb_interface_desc,
       (struct usb_descriptor_header *) &hdb_superspeed_in_desc,
       (struct usb_descriptor_header *) &hdb_superspeed_comp_desc,
       (struct usb_descriptor_header *) &hdb_superspeed_out_desc,
       (struct usb_descriptor_header *) &hdb_superspeed_comp_desc,
       NULL,
};
#if 0
static void hdb_ready_callback(void);
static void hdb_closed_callback(void);
#endif

/* temporary variable used between hdb_open() and hdb_gadget_bind() */
static struct hdb_dev *_hdb_dev;

static inline struct hdb_dev *func_to_hdb(struct usb_function *f)
{
	return container_of(f, struct hdb_dev, function);
}


static struct usb_request *hdb_request_new(struct usb_ep *ep, int buffer_size)
{
	struct usb_request *req = usb_ep_alloc_request(ep, GFP_KERNEL);
	if (!req)
		return NULL;

	/* now allocate buffers for the requests */
	req->buf = kmalloc(buffer_size, GFP_KERNEL);
	if (!req->buf) {
		usb_ep_free_request(ep, req);
		return NULL;
	}

	return req;
}

static void hdb_request_free(struct usb_request *req, struct usb_ep *ep)
{
	if (req) {
		kfree(req->buf);
		usb_ep_free_request(ep, req);
	}
}

static inline int hdb_lock(atomic_t *excl)
{
	if (atomic_inc_return(excl) == 1) {
		return 0;
	} else {
		atomic_dec(excl);
		return -1;
	}
}

static inline void hdb_unlock(atomic_t *excl)
{
	atomic_dec(excl);
}

/* add a request to the tail of a list */
void hdb_req_put(struct hdb_dev *dev, struct list_head *head,
		struct usb_request *req)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->lock, flags);
	list_add_tail(&req->list, head);
	spin_unlock_irqrestore(&dev->lock, flags);
}

/* remove a request from the head of a list */
struct usb_request *hdb_req_get(struct hdb_dev *dev, struct list_head *head)
{
	unsigned long flags;
	struct usb_request *req;

	spin_lock_irqsave(&dev->lock, flags);
	if (list_empty(head)) {
		req = 0;
	} else {
		req = list_first_entry(head, struct usb_request, list);
		list_del(&req->list);
	}
	spin_unlock_irqrestore(&dev->lock, flags);
	return req;
}

static void hdb_complete_in(struct usb_ep *ep, struct usb_request *req)
{
	struct hdb_dev *dev = _hdb_dev;

	if (req->status != 0)
		dev->error = 1;

	hdb_req_put(dev, &dev->tx_idle, req);

	wake_up(&dev->write_wq);
}

static void hdb_complete_out(struct usb_ep *ep, struct usb_request *req)
{
	struct hdb_dev *dev = _hdb_dev;

	dev->rx_done = 1;
	if (req->status != 0 && req->status != -ECONNRESET)
		dev->error = 1;

	wake_up(&dev->read_wq);
}

static int hdb_create_bulk_endpoints(struct hdb_dev *dev,
				struct usb_endpoint_descriptor *in_desc,
				struct usb_endpoint_descriptor *out_desc)
{
	struct usb_composite_dev *cdev = dev->cdev;
	struct usb_request *req;
	struct usb_ep *ep;
	int i;

	DBG(cdev, "create_bulk_endpoints dev: %p\n", dev);

	ep = usb_ep_autoconfig(cdev->gadget, in_desc);
	if (!ep) {
		DBG(cdev, "usb_ep_autoconfig for ep_in failed\n");
		return -ENODEV;
	}
	DBG(cdev, "usb_ep_autoconfig for ep_in got %s\n", ep->name);
	ep->driver_data = dev;		/* claim the endpoint */
	dev->ep_in = ep;

	ep = usb_ep_autoconfig(cdev->gadget, out_desc);
	if (!ep) {
		DBG(cdev, "usb_ep_autoconfig for ep_out failed\n");
		return -ENODEV;
	}
	DBG(cdev, "usb_ep_autoconfig for hdb ep_out got %s\n", ep->name);
	ep->driver_data = dev;		/* claim the endpoint */
	dev->ep_out = ep;

	/* now allocate requests for our endpoints */
	req = hdb_request_new(dev->ep_out, hdb_BULK_BUFFER_SIZE);
	if (!req)
		goto fail;
	req->complete = hdb_complete_out;
	dev->rx_req = req;

	for (i = 0; i < TX_REQ_MAX; i++) {
		req = hdb_request_new(dev->ep_in, hdb_BULK_BUFFER_SIZE);
		if (!req)
			goto fail;
		req->complete = hdb_complete_in;
		hdb_req_put(dev, &dev->tx_idle, req);
	}

	return 0;

fail:
	printk(KERN_ERR "hdb_bind() could not allocate requests\n");
	return -1;
}

static ssize_t hdb_read(struct file *fp, char __user *buf,
				size_t count, loff_t *pos)
{
	struct hdb_dev *dev = fp->private_data;
	struct usb_request *req;
	int r = count, xfer;
	int ret;

	pr_debug("hdb_read(%zu)\n", count);
	if (!_hdb_dev)
		return -ENODEV;

	if (count > hdb_BULK_BUFFER_SIZE)
		return -EINVAL;

	if (hdb_lock(&dev->read_excl))
		return -EBUSY;

	/* we will block until we're online */
	while (!(dev->online || dev->error)) {
		pr_debug("hdb_read: waiting for online state\n");
		ret = wait_event_interruptible(dev->read_wq,
				(dev->online || dev->error));
		if (ret < 0) {
			hdb_unlock(&dev->read_excl);
			return ret;
		}
	}
	if (dev->error) {
		r = -EIO;
		goto done;
	}

requeue_req:
	/* queue a request */
	req = dev->rx_req;
	req->length = count;
	dev->rx_done = 0;
	ret = usb_ep_queue(dev->ep_out, req, GFP_ATOMIC);
	if (ret < 0) {
		pr_debug("hdb_read: failed to queue req %p (%d)\n", req, ret);
		r = -EIO;
		dev->error = 1;
		goto done;
	} else {
		pr_debug("rx %p queue\n", req);
	}

	/* wait for a request to complete */
	ret = wait_event_interruptible(dev->read_wq, dev->rx_done);
	if (ret < 0) {
		if (ret != -ERESTARTSYS)
			dev->error = 1;
		r = ret;
		usb_ep_dequeue(dev->ep_out, req);
		goto done;
	}
	if (!dev->error) {
		/* If we got a 0-len packet, throw it back and try again. */
		if (req->actual == 0)
			goto requeue_req;

		pr_debug("rx %p %d\n", req, req->actual);
		xfer = (req->actual < count) ? req->actual : count;
		if (copy_to_user(buf, req->buf, xfer))
			r = -EFAULT;

	} else
		r = -EIO;

done:
	hdb_unlock(&dev->read_excl);
	pr_debug("hdb_read returning %d\n", r);
	return r;
}

static ssize_t hdb_write(struct file *fp, const char __user *buf,
				 size_t count, loff_t *pos)
{
	struct hdb_dev *dev = fp->private_data;
	struct usb_request *req = 0;
	int r = count, xfer;
	int ret;

	if (!_hdb_dev)
		return -ENODEV;
	pr_debug("hdb_write(%lu)\n", count);
	if (hdb_lock(&dev->write_excl))
		return -EBUSY;

	while (count > 0) {
		if (dev->error) {
			pr_debug("hdb_write dev->error\n");
			r = -EIO;
			break;
		}

		/* get an idle tx request to use */
		req = 0;
		ret = wait_event_interruptible(dev->write_wq,
			(req = hdb_req_get(dev, &dev->tx_idle)) || dev->error);

		if (ret < 0) {
			r = ret;
			break;
		}

		if (req != 0) {
			if (count > hdb_BULK_BUFFER_SIZE)
				xfer = hdb_BULK_BUFFER_SIZE;
			else
				xfer = count;
			if (copy_from_user(req->buf, buf, xfer)) {
				r = -EFAULT;
				break;
			}

			req->length = xfer;
			ret = usb_ep_queue(dev->ep_in, req, GFP_ATOMIC);
			if (ret < 0) {
				pr_debug("hdb_write: xfer error %d\n", ret);
				dev->error = 1;
				r = -EIO;
				break;
			}

			buf += xfer;
			count -= xfer;

			/* zero this so we don't try to free it on error exit */
			req = 0;
		}
	}

	if (req)
		hdb_req_put(dev, &dev->tx_idle, req);

	hdb_unlock(&dev->write_excl);
	pr_debug("hdb_write returning %d\n", r);
	return r;
}

static int hdb_open(struct inode *ip, struct file *fp)
{
	pr_info("hdb_open\n");
	if (!_hdb_dev)
		return -ENODEV;

	if (hdb_lock(&_hdb_dev->open_excl))
		return -EBUSY;

	fp->private_data = _hdb_dev;

	/* clear the error latch */
	_hdb_dev->error = 0;

//	hdb_ready_callback();

	return 0;
}

static int hdb_release(struct inode *ip, struct file *fp)
{
	pr_info("hdb_release\n");

//	hdb_closed_callback();

	hdb_unlock(&_hdb_dev->open_excl);
	return 0;
}

/* file operations for hdb device /dev/android_hdb */
static const struct file_operations hdb_fops = {
	.owner = THIS_MODULE,
	.read = hdb_read,
	.write = hdb_write,
	.open = hdb_open,
	.release = hdb_release,
};

static struct miscdevice hdb_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = hdb_shortname,
	.fops = &hdb_fops,
};




static int
hdb_function_bind(struct usb_configuration *c, struct usb_function *f)
{
	struct usb_composite_dev *cdev = c->cdev;
	struct hdb_dev	*dev = func_to_hdb(f);
	int			id;
	int			ret;

	dev->cdev = cdev;
	DBG(cdev, "hdb_function_bind dev: %p\n", dev);

	/* allocate interface ID(s) */
	id = usb_interface_id(c, f);
	if (id < 0)
		return id;
	hdb_interface_desc.bInterfaceNumber = id;

	/* allocate endpoints */
	ret = hdb_create_bulk_endpoints(dev, &hdb_fullspeed_in_desc,
			&hdb_fullspeed_out_desc);
	if (ret)
		return ret;

	/* support high speed hardware */
	if (gadget_is_dualspeed(c->cdev->gadget)) {
		hdb_highspeed_in_desc.bEndpointAddress =
			hdb_fullspeed_in_desc.bEndpointAddress;
		hdb_highspeed_out_desc.bEndpointAddress =
			hdb_fullspeed_out_desc.bEndpointAddress;
	}
	/* support super speed hardware */
	if (gadget_is_superspeed(c->cdev->gadget)) {
		hdb_superspeed_in_desc.bEndpointAddress =
			hdb_fullspeed_in_desc.bEndpointAddress;
		hdb_superspeed_out_desc.bEndpointAddress =
			hdb_fullspeed_out_desc.bEndpointAddress;
	}

	DBG(cdev, "%s speed %s: IN/%s, OUT/%s\n",
			gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
			f->name, dev->ep_in->name, dev->ep_out->name);
	printk(KERN_INFO "%s speed %s: IN/%s, OUT/%s\n",
			gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
			f->name, dev->ep_in->name, dev->ep_out->name);

	return 0;
}

static void
hdb_function_unbind(struct usb_configuration *c, struct usb_function *f)
{
	struct hdb_dev	*dev = func_to_hdb(f);
	struct usb_request *req;


	dev->online = 0;
	dev->error = 1;

	wake_up(&dev->read_wq);

	hdb_request_free(dev->rx_req, dev->ep_out);
	while ((req = hdb_req_get(dev, &dev->tx_idle)))
		hdb_request_free(req, dev->ep_in);
}

static int hdb_function_set_alt(struct usb_function *f,
		unsigned intf, unsigned alt)
{
	struct hdb_dev	*dev = func_to_hdb(f);
	struct usb_composite_dev *cdev = f->config->cdev;
	int ret;

	printk("hdb_function_set_alt intf: %d alt: %d\n", intf, alt);
	DBG(cdev, "hdb_function_set_alt intf: %d alt: %d\n", intf, alt);

	ret = config_ep_by_speed(cdev->gadget, f, dev->ep_in);
	if (ret)
		return ret;

	ret = usb_ep_enable(dev->ep_in);
	if (ret)
		return ret;

	ret = config_ep_by_speed(cdev->gadget, f, dev->ep_out);
	if (ret)
		return ret;

	ret = usb_ep_enable(dev->ep_out);
	if (ret) {
		usb_ep_disable(dev->ep_in);
		return ret;
	}
	dev->online = 1;

	/* readers may be blocked waiting for us to go online */
	wake_up(&dev->read_wq);
	wake_up(&dev->write_wq);
	return 0;
}

static void hdb_function_disable(struct usb_function *f)
{
	struct hdb_dev	*dev = func_to_hdb(f);

	DBG(dev->cdev, "hdb_function_disable cdev %p\n", dev->cdev);
	dev->online = 0;
	dev->error = 1;
	usb_ep_disable(dev->ep_in);
	usb_ep_disable(dev->ep_out);

	/* readers may be blocked waiting for us to go online */
	wake_up(&dev->read_wq);
	wake_up(&dev->write_wq);

	VDBG(dev->cdev, "%s disabled\n", dev->function.name);
}

static int hdb_bind_config(struct usb_configuration *c)
{
	struct hdb_dev *dev = _hdb_dev;
	int ret;

	printk(KERN_INFO "hdb_bind_config\n");

	dev->cdev = c->cdev;
	dev->function.name = "hdb";
	dev->function.fs_descriptors = fs_hdb_descs;
	dev->function.hs_descriptors = hs_hdb_descs;
	dev->function.ss_descriptors = ss_hdb_descs;
	dev->function.bind = hdb_function_bind;
	dev->function.unbind = hdb_function_unbind;
	dev->function.set_alt = hdb_function_set_alt;
	dev->function.disable = hdb_function_disable;


	ret = usb_add_function(c, &dev->function);
	return ret;
}

static int hdb_setup(void)
{
	struct hdb_dev *dev;
	int ret;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	spin_lock_init(&dev->lock);

	init_waitqueue_head(&dev->read_wq);
	init_waitqueue_head(&dev->write_wq);

	atomic_set(&dev->open_excl, 0);
	atomic_set(&dev->read_excl, 0);
	atomic_set(&dev->write_excl, 0);

	INIT_LIST_HEAD(&dev->tx_idle);

	_hdb_dev = dev;

	ret = misc_register(&hdb_device);
	if (ret)
		goto err;

	return 0;

err:
	kfree(dev);
	printk(KERN_ERR "hdb gadget driver failed to initialize\n");
	return ret;
}

static void hdb_cleanup(void)
{
	misc_deregister(&hdb_device);

	kfree(_hdb_dev);
	_hdb_dev = NULL;
}
