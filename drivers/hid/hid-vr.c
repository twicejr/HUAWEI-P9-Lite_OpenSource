/*
 * Oculus VR driver for Linux
 *
 * Copyright (c) 2013 Lee Cooper <lee.cooper@oculusvr.com>
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

/*
 * Driver for Oculus VR devices. Based on hidraw driver.
 */

#include <linux/cdev.h>
#include <linux/poll.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/hidraw.h>
#include "hid-ids.h"

/*lint -e750 -esym(750,*)*/
#define USB_TRACKER_INTERFACE_PROTOCOL	0
/*lint -e750 +esym(750,*)*/
#ifdef HID_VR_DEBUG
#define D(format, arg...) pr_info("[%s]"format, __func__, ##arg)
#else
#define D(format, arg...)
#endif

/* number of reports to buffer */
#define OVR_HIDRAW_BUFFER_SIZE 64

#define OVR_HIDRAW_MAX_DEVICES 8

#define OVR_FIRST_MINOR 0

static struct class *ovr_class;

static struct hidraw *ovr_hidraw_table[OVR_HIDRAW_MAX_DEVICES];
static DEFINE_MUTEX(minors_lock);

static int ovr_major;
static struct cdev ovr_cdev;

#define MONITOR_MAX 5
struct hwvr_monitor {
	unsigned int minor;
	int opens;
	unsigned int isr_count;
	unsigned long last_isr;
	unsigned long monitor_info[MONITOR_MAX][3];
};

static struct hwvr_monitor hwvr_monitors[OVR_HIDRAW_MAX_DEVICES] = {{0,},};

static ssize_t ovr_hidraw_read(struct file *file,
				char __user *buffer,
				size_t count,
				loff_t *ppos)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	unsigned int minor = iminor(inode);
	struct hwvr_monitor *monitor = &hwvr_monitors[minor];
	struct hidraw_list *list = file->private_data;
	int ret = 0, len;
	DECLARE_WAITQUEUE(wait, current);

	mutex_lock(&list->read_mutex);

	while (ret == 0) {
		if (list->head == list->tail) {
			add_wait_queue(&list->hidraw->wait, &wait);
			set_current_state(TASK_INTERRUPTIBLE);

			while (list->head == list->tail) {
				if (signal_pending(current)) {
					ret = -ERESTARTSYS;
					break;
				}
				if (!list->hidraw->exist) {
					ret = -EIO;
					break;
				}
				if (file->f_flags & O_NONBLOCK) {
					ret = -EAGAIN;
					break;
				}

				/* allow O_NONBLOCK to work well
				 * from other threads */
				mutex_unlock(&list->read_mutex);
				schedule();
				mutex_lock(&list->read_mutex);
				set_current_state(TASK_INTERRUPTIBLE);
			}

			set_current_state(TASK_RUNNING);
			remove_wait_queue(&list->hidraw->wait, &wait);
		}

		if (ret)
			goto out;

		len = list->buffer[list->tail].len > count ?
			count : list->buffer[list->tail].len;

		if (list->buffer[list->tail].value) {
			D("hidvr copy %d to user\n", len);
			if (copy_to_user(buffer,
					list->buffer[list->tail].value,
					len)) {
				ret = -EFAULT;
				goto out;
			}
			ret = len;

			if (monitor->opens > 0) {
				int i;
				for (i = 0; i < MONITOR_MAX; i++) {
					if (monitor->monitor_info[i][0] == current->pid) {
						monitor->monitor_info[i][1]++;
						monitor->monitor_info[i][2] = jiffies;
						break;
					}
				}
			}
		}

		D("free list buffer 0x%p\n", list->buffer[list->tail].value);
		kfree(list->buffer[list->tail].value);
		list->buffer[list->tail].value = NULL;
		list->tail = (list->tail + 1) & (OVR_HIDRAW_BUFFER_SIZE - 1);
	}
out:
	mutex_unlock(&list->read_mutex);

	return ret;
}

/* The first byte is expected to be a report number.
 * This function is to be called with the minors_lock mutex held */
static ssize_t ovr_hidraw_send_report(struct file *file,
					const char __user *buffer,
					size_t count,
					unsigned char report_type)
{
	unsigned int minor = iminor(file->f_path.dentry->d_inode);
	struct hid_device *dev;
	__u8 *buf;
	int ret = 0;

	if (!ovr_hidraw_table[minor]) {
		ret = -ENODEV;
		goto out;
	}

	dev = ovr_hidraw_table[minor]->hid;

	if (!dev->hid_output_raw_report) {
		ret = -ENODEV;
		goto out;
	}

	if (count > HID_MAX_BUFFER_SIZE) {
		hid_warn(dev, "ovr - pid %d passed too large report\n",
			 task_pid_nr(current));
		ret = -EINVAL;
		goto out;
	}

	if (count == 0) {
		hid_warn(dev, "ovr - pid %d passed too short report\n",
			 task_pid_nr(current));
		ret = -EINVAL;
		goto out;
	}

	buf = kmalloc(count * sizeof(__u8), GFP_KERNEL);
	if (!buf) {
		ret = -ENOMEM;
		goto out;
	}

	if (copy_from_user(buf, buffer, count)) {
		ret = -EFAULT;
		goto out_free;
	}

	ret = dev->hid_output_raw_report(dev, buf, count, report_type);
out_free:
	kfree(buf);
out:
	return ret;
}

/* the first byte is expected to be a report number */
static ssize_t ovr_hidraw_write(struct file *file,
				const char __user *buffer,
				size_t count,
				loff_t *ppos)
{
	ssize_t ret;
	mutex_lock(&minors_lock);
	ret = ovr_hidraw_send_report(file, buffer, count, HID_OUTPUT_REPORT);
	mutex_unlock(&minors_lock);
	return ret;
}

/* This function performs a Get_Report transfer over the control endpoint
 * per section 7.2.1 of the HID specification, version 1.1.  The first byte
 * of buffer is the report number to request, or 0x0 if the defice does not
 * use numbered reports. The report_type parameter can be HID_FEATURE_REPORT
 * or HID_INPUT_REPORT.  This function is to be called with the minors_lock
 *  mutex held. */
static ssize_t ovr_hidraw_get_report(struct file *file,
					char __user *buffer,
					size_t count,
					unsigned char report_type)
{
	unsigned int minor = iminor(file->f_path.dentry->d_inode);
	struct hid_device *dev;
	__u8 *buf;
	int ret = 0, len;
	unsigned char report_number;

	dev = ovr_hidraw_table[minor]->hid;

	if (!dev->hid_get_raw_report) {
		ret = -ENODEV;
		goto out;
	}

	if (count > HID_MAX_BUFFER_SIZE) {
		pr_warn("ovr - hidraw: pid %d passed too large report\n",
				task_pid_nr(current));
		ret = -EINVAL;
		goto out;
	}

	if (count == 0) {
		pr_warn("ovr - hidraw: pid %d passed too short report\n",
				task_pid_nr(current));
		ret = -EINVAL;
		goto out;
	}

	buf = kmalloc(count * sizeof(__u8), GFP_KERNEL);
	if (!buf) {
		ret = -ENOMEM;
		goto out;
	}

	/* Read the first byte from the user. This is the report number,
	 * which is passed to dev->hid_get_raw_report(). */
	if (copy_from_user(&report_number, buffer, 1)) {
		ret = -EFAULT;
		goto out_free;
	}

	ret = dev->hid_get_raw_report(dev, report_number,
			buf, count, report_type);

	if (ret < 0)
		goto out_free;

	len = (ret < count) ? ret : count;

	if (copy_to_user(buffer, buf, len)) {
		ret = -EFAULT;
		goto out_free;
	}

	ret = len;

out_free:
	kfree(buf);
out:
	return ret;
}

static unsigned int ovr_hidraw_poll(struct file *file, poll_table *wait)
{
	struct hidraw_list *list = file->private_data;

	poll_wait(file, &list->hidraw->wait, wait);
	if (list->head != list->tail)
		return POLLIN | POLLRDNORM;
	if (!list->hidraw->exist)
		return POLLERR | POLLHUP;
	return 0;
}

static int ovr_hidraw_open(struct inode *inode, struct file *file)
{
	unsigned int minor = iminor(inode);
	struct hidraw *dev;
	struct hidraw_list *list;
	struct hwvr_monitor *monitor = &hwvr_monitors[minor];
	int err = 0;

	list = kzalloc(sizeof(struct hidraw_list), GFP_KERNEL);
	if (!list) {
		err = -ENOMEM;
		goto out;
	}

	mutex_lock(&minors_lock);
	if (!ovr_hidraw_table[minor]) {
		err = -ENODEV;
		goto out_unlock;
	}

	D("OVR: open (%d:%s) >>>\n", current->pid, current->comm);

	dev = ovr_hidraw_table[minor];

	list->hidraw = dev;
	mutex_init(&list->read_mutex);

	if (!dev->open++) {
		err = hid_hw_power(dev->hid, PM_HINT_FULLON);
		if (err < 0) {
			dev->open--;
			goto out_unlock;
		}

		err = hid_hw_open(dev->hid);
		if (err < 0) {
			hid_hw_power(dev->hid, PM_HINT_NORMAL);
			dev->open--;
			goto out_unlock;
		} else {
			/* 1st open */
			int i;

			for (i = 0; i < MONITOR_MAX; i++)
				monitor->monitor_info[i][0] = 0;

			monitor->opens = 0;
			monitor->isr_count = 0;
			monitor->minor = minor;
		}
	}

	spin_lock_irq(&dev->list_lock);
	list_add_tail(&list->node, &dev->list);
	spin_unlock_irq(&dev->list_lock);

	file->private_data = list;

	if (dev->open > monitor->opens) {
		int i;

		for (i = 0; i < MONITOR_MAX; i++) {
			if (monitor->monitor_info[i][0] == current->pid)
				break;
		}
		if (i >= MONITOR_MAX) {
			for (i = 0; i < MONITOR_MAX; i++) {
				if (monitor->monitor_info[i][0] == 0) {
					monitor->monitor_info[i][0] = current->pid;
					break;
				}
			}
		}
	}
	monitor->opens = dev->open;

out_unlock:
	mutex_unlock(&minors_lock);
	D("OVR: open(%d) err %d <<<\n", monitor->opens, err);
out:
	if (err < 0)
		kfree(list);
	return err;
}

static int ovr_hidraw_fasync(int fd, struct file *file, int on)
{
	struct hidraw_list *list = file->private_data;

	return fasync_helper(fd, file, on, &list->fasync);
}

static int ovr_hidraw_release(struct inode *inode, struct file *file)
{
	unsigned int minor = iminor(inode);
	struct hidraw *dev;
	struct hidraw_list *list = file->private_data;
	struct hwvr_monitor *monitor = &hwvr_monitors[minor];
	int ret = 0;
	int i;
	unsigned long flags;

	D("OVR: release (%d:%s) >>>\n", current->pid, current->comm);

	mutex_lock(&minors_lock);
	if (!ovr_hidraw_table[minor]) {
		ret = -ENODEV;
		goto unlock;
	}

	dev = ovr_hidraw_table[minor];

	spin_lock_irqsave(&dev->list_lock, flags);
	list_del(&list->node);
	spin_unlock_irqrestore(&dev->list_lock, flags);

	if (!--dev->open) {
		if (list->hidraw->exist) {
			hid_hw_power(dev->hid, PM_HINT_NORMAL);
			hid_hw_close(dev->hid);
		} else {
			kfree(dev);
			ovr_hidraw_table[minor] = NULL;
		}
	}

	for (i = 0; i < MONITOR_MAX; i++) {
		if (monitor->monitor_info[i][0] == current->pid) {
			monitor->monitor_info[i][0] = 0;
			monitor->monitor_info[i][1] = 0;
			monitor->monitor_info[i][2] = 0;
		}
	}

	monitor->opens = dev->open;

	D("OVR: release(%d) <<<\n", dev->open);

unlock:
	for (i = 0; i < OVR_HIDRAW_BUFFER_SIZE; ++i) {
		if (list->buffer[i].value) {
			D("free list buffer 0x%p\n", list->buffer[i].value);
			kfree(list->buffer[i].value);
		}
	}
	kfree(list);

	mutex_unlock(&minors_lock);

	return ret;
}

int ovr_report_event(struct hid_device *hid, u8 *data, int len)
{
	struct hidraw *dev = hid->hidvr;
	struct hidraw_list *list;
	int ret = 0;
	unsigned long flags;

	spin_lock_irqsave(&dev->list_lock, flags);
	list_for_each_entry(list, &dev->list, node) {
		int new_head = (list->head + 1) & (OVR_HIDRAW_BUFFER_SIZE - 1);

		if (new_head == list->tail)
			continue;

		list->buffer[list->head].value = kmemdup(data, len, GFP_ATOMIC);
		if (!list->buffer[list->head].value) {
			ret = -ENOMEM;
			spin_unlock_irqrestore(&dev->list_lock, flags);
			break;
		}

		D("alloc list buffer 0x%p\n", list->buffer[list->head].value);
		list->buffer[list->head].len = len;
		list->head = new_head;
		kill_fasync(&list->fasync, SIGIO, POLL_IN);
	}
	spin_unlock_irqrestore(&dev->list_lock, flags);

	wake_up_interruptible(&dev->wait);

	return ret;
}

int ovr_connect(struct hid_device *hid)
{
	int minor, result;
	struct hidraw *dev;
	char *device_name = "hwvr";
	D("+\n");

	/* we accept any HID device, no matter the applications */

	dev = kzalloc(sizeof(struct hidraw), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	result = -EINVAL;

	mutex_lock(&minors_lock);

	for (minor = 0; minor < OVR_HIDRAW_MAX_DEVICES; minor++) {
		if (ovr_hidraw_table[minor])
			continue;

		ovr_hidraw_table[minor] = dev;
		result = 0;
		break;
	}

	if (result) {
		mutex_unlock(&minors_lock);
		kfree(dev);
		goto out;
	}

	dev->dev = device_create(ovr_class, &hid->dev, MKDEV(ovr_major, minor),
				 NULL, "%s%d", device_name, minor);

	D("devname: %s\n", dev_name(dev->dev));

	if (IS_ERR(dev->dev)) {
		ovr_hidraw_table[minor] = NULL;
		mutex_unlock(&minors_lock);
		result = PTR_ERR(dev->dev);
		kfree(dev);
		goto out;
	}

	mutex_unlock(&minors_lock);
	init_waitqueue_head(&dev->wait);
	INIT_LIST_HEAD(&dev->list);
	spin_lock_init(&dev->list_lock);

	dev->hid = hid;
	dev->minor = minor;

	dev->exist = 1;
	hid->hidvr = dev;
	D("-\n");

out:
	return result;
}

void ovr_disconnect(struct hid_device *hid)
{
	struct hidraw *hidraw = hid->hidvr;
	struct hwvr_monitor *monitor = &hwvr_monitors[hidraw->minor];

	D("+\n");
	mutex_lock(&minors_lock);

	hidraw->exist = 0;

	device_destroy(ovr_class, MKDEV(ovr_major, hidraw->minor));

	ovr_hidraw_table[hidraw->minor] = NULL;

	if (hidraw->open) {
		hid_hw_close(hid);

		wake_up_interruptible(&hidraw->wait);
	} else {
		kfree(hidraw);
	}

	/* clear monitor info */
	memset(monitor, 0, sizeof(struct hwvr_monitor));

	mutex_unlock(&minors_lock);
	D("-\n");
}

static long ovr_hidraw_ioctl(struct file *file,
				unsigned int cmd,
				unsigned long arg)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	unsigned int minor = iminor(inode);
	long ret = 0;
	struct hidraw *dev;
	void __user *user_arg = (void __user *)arg;

	mutex_lock(&minors_lock);
	dev = ovr_hidraw_table[minor];
	if (!dev || (dev && !dev->exist)) {
		ret = -ENODEV;
		goto out;
	}

	switch (cmd) {
	case HIDIOCGRDESCSIZE:
		if (put_user(dev->hid->rsize, (int __user *)arg))
			ret = -EFAULT;
		break;

	case HIDIOCGRDESC:
		{
			__u32 len;

			if (get_user(len, (int __user *)arg))
				ret = -EFAULT;
			else if (len > HID_MAX_DESCRIPTOR_SIZE - 1)
				ret = -EINVAL;
			else if (copy_to_user(user_arg + offsetof(
							struct hidraw_report_descriptor,
							value[0]),
						dev->hid->rdesc,
						min(dev->hid->rsize, len)))
				ret = -EFAULT;
			break;
		}
	case HIDIOCGRAWINFO:
		{
			struct hidraw_devinfo dinfo;

			dinfo.bustype = dev->hid->bus;
			dinfo.vendor = dev->hid->vendor;
			dinfo.product = dev->hid->product;
			if (copy_to_user(user_arg, &dinfo, sizeof(dinfo)))
				ret = -EFAULT;
			break;
		}
	default:
		{
			struct hid_device *hid = dev->hid;
			if (_IOC_TYPE(cmd) != 'H') {
				ret = -EINVAL;
				break;
			}

			if (_IOC_NR(cmd) == _IOC_NR(HIDIOCSFEATURE(0))) {
				int len = _IOC_SIZE(cmd);

				ret = ovr_hidraw_send_report(file, user_arg,
						len, HID_FEATURE_REPORT);
				break;
			}
			if (_IOC_NR(cmd) == _IOC_NR(HIDIOCGFEATURE(0))) {
				int len = _IOC_SIZE(cmd);

				ret = ovr_hidraw_get_report(file, user_arg,
						len, HID_FEATURE_REPORT);
				break;
			}

			/* Begin Read-only ioctls. */
			if (_IOC_DIR(cmd) != _IOC_READ) {
				ret = -EINVAL;
				break;
			}

			if (_IOC_NR(cmd) == _IOC_NR(HIDIOCGRAWNAME(0))) {
				int len = strlen(hid->name) + 1;

				if (len > _IOC_SIZE(cmd))
					len = _IOC_SIZE(cmd);
				ret = copy_to_user(user_arg, hid->name, len) ?
					-EFAULT : len;
				break;
			}

			if (_IOC_NR(cmd) == _IOC_NR(HIDIOCGRAWPHYS(0))) {
				int len = strlen(hid->phys) + 1;

				if (len > _IOC_SIZE(cmd))
					len = _IOC_SIZE(cmd);
				ret = copy_to_user(user_arg, hid->phys, len) ?
					-EFAULT : len;
				break;
			}
		}

		ret = -ENOTTY;
	}
out:
	mutex_unlock(&minors_lock);
	return ret;
}

void dump_hwvr_monitors(void)
{
	int i, j;

	for (i = 0; i < OVR_HIDRAW_MAX_DEVICES; i++) {
		if (hwvr_monitors[i].opens != 0) {
			pr_info("Devices hwvr%d, opens %d, isr_count %u,\
				last_isr %lu, user process infos:\n",
				hwvr_monitors[i].minor, hwvr_monitors[i].opens,
				hwvr_monitors[i].isr_count,
				hwvr_monitors[i].last_isr);

			for (j = 0; j < MONITOR_MAX; j++) {
				pr_info("pid %lu, read count %lu,\
					read timestamp %lu\n",
					hwvr_monitors[i].monitor_info[j][0],
					hwvr_monitors[i].monitor_info[j][1],
					hwvr_monitors[i].monitor_info[j][2]);
			}
		}
	}
}

static const struct file_operations ovr_ops = {
	.owner = THIS_MODULE,
	.read = ovr_hidraw_read,
	.write = ovr_hidraw_write,
	.poll = ovr_hidraw_poll,
	.open = ovr_hidraw_open,
	.release = ovr_hidraw_release,
	.unlocked_ioctl = ovr_hidraw_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl   = ovr_hidraw_ioctl,
#endif
	.fasync = ovr_hidraw_fasync,
	.llseek = noop_llseek,
};

static int ovr_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int retval;

	D("+\n");
	retval = hid_parse(hdev);
	if (retval) {
		hid_err(hdev, "ovr - parse failed\n");
		goto exit;
	}

	retval = hid_hw_start(hdev, HID_CONNECT_HIDINPUT | HID_CONNECT_HIDDEV |
				HID_CONNECT_FF);
	if (retval) {
		hid_err(hdev, "ovr - hw start failed\n");
		goto exit;
	}

	retval = ovr_connect(hdev);

	if (retval) {
		hid_err(hdev, "ovr - Couldn't connect\n");
		goto exit_stop;
	}
	D("-\n");
	return 0;

exit_stop:
	hid_hw_stop(hdev);
exit:
	return retval;
}

static void ovr_remove(struct hid_device *hdev)
{
	ovr_disconnect(hdev);

	hid_hw_stop(hdev);
}

static int ovr_raw_event(struct hid_device *hdev,
			struct hid_report *report,
			u8 *data,
			int size)
{
	int retval = 0;

	if (hdev->hidvr) {
		struct hidraw *hidraw = hdev->hidvr;

		hwvr_monitors[hidraw->minor].isr_count++;
		hwvr_monitors[hidraw->minor].last_isr = jiffies;

		retval = ovr_report_event(hdev, data, size);
		if (retval < 0)
			pr_err("OVR: raw event err %d\n", retval);
	}

	return retval;
}

static const struct hid_device_id ovr_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOR_ID_HUAWEI_VR, USB_DEVICE_ID_HUAWEI_VR) },
	{ HID_USB_DEVICE(0x04e8, 0xa500) },
	{ HID_USB_DEVICE(0x04e8, 0xa501) },
	{ HID_USB_DEVICE(0x04e8, 0xa502) },
	{ HID_USB_DEVICE(0x04e8, 0xa503) },
	{ HID_USB_DEVICE(0x04e8, 0xa504) },
	{ HID_USB_DEVICE(0x04e8, 0xa505) },
	{ }
};

MODULE_DEVICE_TABLE(hid, ovr_devices);

static struct hid_driver ovr_driver = {
		.name = "hwvr",
		.id_table = ovr_devices,
		.probe = ovr_probe,
		.remove = ovr_remove,
		.raw_event = ovr_raw_event
};

static int __init ovr_init(void)
{
	int retval;
	dev_t dev_id;

	ovr_class = class_create(THIS_MODULE, "hwvr");
	if (IS_ERR(ovr_class))
		return PTR_ERR(ovr_class);

	retval = hid_register_driver(&ovr_driver);
	if (retval < 0) {
		pr_warn("ovr_init - Can't register drive.\n");
		goto out_class;
	}

	retval = alloc_chrdev_region(&dev_id, OVR_FIRST_MINOR,
			OVR_HIDRAW_MAX_DEVICES, "hwvr");
	if (retval < 0) {
		pr_warn("ovr_init - Can't allocate chrdev region.\n");
		goto out_register;
	}

	ovr_major = MAJOR(dev_id);
	cdev_init(&ovr_cdev, &ovr_ops);
	cdev_add(&ovr_cdev, dev_id, OVR_HIDRAW_MAX_DEVICES);

	return 0;

out_register:
	hid_unregister_driver(&ovr_driver);

out_class:
	class_destroy(ovr_class);

	return retval;
}

static void __exit ovr_exit(void)
{
	dev_t dev_id = MKDEV(ovr_major, 0);

	cdev_del(&ovr_cdev);

	unregister_chrdev_region(dev_id, OVR_HIDRAW_MAX_DEVICES);

	hid_unregister_driver(&ovr_driver);

	class_destroy(ovr_class);
}

module_init(ovr_init);
module_exit(ovr_exit);

MODULE_AUTHOR("Lee Cooper");
MODULE_DESCRIPTION("USB VR char device driver.");
MODULE_LICENSE("GPL v2");
