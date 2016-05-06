/*
 * Synaptics DSX touchscreen driver
 *
 * Copyright (C) 2012 Synaptics Incorporated
 *
 * Copyright (C) 2012 Alexandra Chin <alexandra.chin@tw.synaptics.com>
 * Copyright (C) 2012 Scott Lin <scott.lin@tw.synaptics.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include "synaptics.h"
#include <../../huawei_touchscreen_chips.h>

#define CHAR_DEVICE_NAME "rmi"
#define DEVICE_CLASS_NAME "rmidev"
#define SYSFS_FOLDER_NAME "rmidev"
#define DEV_NUMBER 1
#define REG_ADDR_LIMIT 0xFFFF

static ssize_t rmidev_sysfs_data_show(struct file *data_file,
		struct kobject *kobj, struct bin_attribute *attributes,
		char *buf, loff_t pos, size_t count);

static ssize_t rmidev_sysfs_data_store(struct file *data_file,
		struct kobject *kobj, struct bin_attribute *attributes,
		char *buf, loff_t pos, size_t count);

static ssize_t rmidev_sysfs_open_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count);

static ssize_t rmidev_sysfs_release_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count);

static ssize_t rmidev_sysfs_attn_state_show(struct device *dev,
		struct device_attribute *attr, char *buf);

struct rmidev_handle {
	dev_t dev_no;
	unsigned char *tmpbuf;
	unsigned int tmpbuf_size;
	struct device dev;
	struct synaptics_rmi4_data *rmi4_data;
	struct synaptics_rmi4_exp_fn_ptr *fn_ptr;
	struct kobject *sysfs_dir;
	void *data;
	bool irq_enabled;
};

struct rmidev_data {
	int ref_count;
	struct cdev main_dev;
	struct class *device_class;
	struct mutex file_mutex;
	struct rmidev_handle *rmi_dev;
};

static struct bin_attribute attr_data = {
	.attr = {
		.name = "data",
		.mode = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP),
	},
	.size = 0,
	.read = rmidev_sysfs_data_show,
	.write = rmidev_sysfs_data_store,
};

static struct device_attribute attrs[] = {
	__ATTR(open, (S_IWUSR|S_IWGRP),
			NULL,
			rmidev_sysfs_open_store),
	__ATTR(release, (S_IWUSR|S_IWGRP),
			NULL,
			rmidev_sysfs_release_store),
	__ATTR(attn_state, (S_IRUSR | S_IRGRP),
			rmidev_sysfs_attn_state_show,
			NULL),
};

static int rmidev_major_num = 0;

static struct class *rmidev_device_class;

static struct rmidev_handle *rmidev;

static DECLARE_COMPLETION(rmidev_remove_complete);

void rmidev_sysfs_irq(void *data)
{
	struct synaptics_rmi4_data *rmi4_data = data;

	sysfs_notify(&rmi4_data->input_dev->dev.kobj,
			SYSFS_FOLDER_NAME, "attn_state");

	return;
}

static ssize_t rmidev_sysfs_data_show(struct file *data_file,
		struct kobject *kobj, struct bin_attribute *attributes,
		char *buf, loff_t pos, size_t count)
{
	int retval;
	unsigned int length = (unsigned int)count;
	unsigned short address = (unsigned short)pos;

	if (length > (REG_ADDR_LIMIT - address)) {
		TS_LOG_ERR("Out of register map limit\n");
		return -EINVAL;
	}

	if (length) {
		retval = rmidev->fn_ptr->read(rmidev->rmi4_data, address, (unsigned char *)buf, length);
		if (retval < 0) {
			TS_LOG_ERR("Failed to read data\n");
			return retval;
		}
	} else {
		TS_LOG_ERR("write length is %d\n", length);
		return -EINVAL;
	}

	return length;
}

static ssize_t rmidev_sysfs_data_store(struct file *data_file,
		struct kobject *kobj, struct bin_attribute *attributes,
		char *buf, loff_t pos, size_t count)
{
	int retval;
	unsigned int length = (unsigned int)count;
	unsigned short address = (unsigned short)pos;

	if (length > (REG_ADDR_LIMIT - address)) {
		TS_LOG_ERR("Out of register map limit\n");
		return -EINVAL;
	}

	if (length) {
		retval = rmidev->fn_ptr->write(rmidev->rmi4_data, address, (unsigned char *)buf, length);
		if (retval < 0) {
			TS_LOG_ERR("Failed to write data\n");
			return retval;
		}
	} else {
		return -EINVAL;
	}

	return length;
}

static ssize_t rmidev_sysfs_open_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned int input;
	struct synaptics_rmi4_data *rmi4_data = rmidev->rmi4_data;

	if (sscanf(buf, "%u", &input) != 1)
		return -EINVAL;

	if (input != 1)
		return -EINVAL;

	rmi4_data->fw_debug = true;
	TS_LOG_INFO("Attention interrupt disabled\n");

	return count;
}

static ssize_t rmidev_sysfs_release_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned int input;
	struct synaptics_rmi4_data *rmi4_data = rmidev->rmi4_data;

	if (sscanf(buf, "%u", &input) != 1)
		return -EINVAL;

	if (input != 1)
		return -EINVAL;

	rmi4_data->reset_device(rmi4_data);
	rmi4_data->fw_debug = false;

	TS_LOG_INFO("Attention interrupt enabled\n");

	return count;
}

static ssize_t rmidev_sysfs_attn_state_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int attn_state;

	attn_state = gpio_get_value(rmidev->rmi4_data->synaptics_chip_data->irq_gpio);

	return snprintf(buf, PAGE_SIZE, "%u\n", attn_state);
}

static int rmidev_allocate_buffer(int count)
{
	if (count + 1 > rmidev->tmpbuf_size) {
		if (rmidev->tmpbuf_size)
			kfree(rmidev->tmpbuf);
		rmidev->tmpbuf = kzalloc(count + 1, GFP_KERNEL);
		if (!rmidev->tmpbuf) {
			TS_LOG_ERR("%s: Failed to alloc mem for buffer\n",__func__);
			rmidev->tmpbuf_size = 0;
			return -ENOMEM;
		}
		rmidev->tmpbuf_size = count + 1;
	}

	return 0;
}

/*
 * rmidev_llseek - used to set up register address
 *
 * @filp: file structure for seek
 * @off: offset
 *   if whence == SEEK_SET,
 *     high 16 bits: page address
 *     low 16 bits: register address
 *   if whence == SEEK_CUR,
 *     offset from current position
 *   if whence == SEEK_END,
 *     offset from end position (0xFFFF)
 * @whence: SEEK_SET, SEEK_CUR, or SEEK_END
 */
static loff_t rmidev_llseek(struct file *filp, loff_t off, int whence)
{
	loff_t newpos;
	struct rmidev_data *dev_data = filp->private_data;

	if (IS_ERR(dev_data)) {
		TS_LOG_ERR("Pointer of char device data is invalid");
		return -EBADF;
	}

	mutex_lock(&(dev_data->file_mutex));

	switch (whence) {
	case SEEK_SET:
		newpos = off;
		break;
	case SEEK_CUR:
		newpos = filp->f_pos + off;
		break;
	case SEEK_END:
		newpos = REG_ADDR_LIMIT + off;
		break;
	default:
		newpos = -EINVAL;
		goto clean_up;
	}

	if (newpos < 0 || newpos > REG_ADDR_LIMIT) {
		TS_LOG_ERR("New position 0x%04x is invalid\n", (unsigned int)newpos);
		newpos = -EINVAL;
		goto clean_up;
	}

	filp->f_pos = newpos;

clean_up:
	mutex_unlock(&(dev_data->file_mutex));

	return newpos;
}

/*
 * rmidev_read: - use to read data from rmi device
 *
 * @filp: file structure for read
 * @buf: user space buffer pointer
 * @count: number of bytes to read
 * @f_pos: offset (starting register address)
 */
static ssize_t rmidev_read(struct file *filp, char __user *buf,
		size_t count, loff_t *f_pos)
{
	ssize_t retval;
	struct rmidev_data *dev_data = filp->private_data;

	if (IS_ERR(dev_data)) {
		TS_LOG_ERR("Pointer of char device data is invalid");
		return -EBADF;
	}

	if (count == 0)
		return 0;

	if (count > (REG_ADDR_LIMIT - *f_pos))
		count = REG_ADDR_LIMIT - *f_pos;

	rmidev_allocate_buffer(count);

	mutex_lock(&(dev_data->file_mutex));

	retval = rmidev->fn_ptr->read(rmidev->rmi4_data,
			*f_pos,
			rmidev->tmpbuf,
			count);
	if (retval < 0)
		goto clean_up;

	if (copy_to_user(buf, rmidev->tmpbuf, count))
		retval = -EFAULT;
	else
		*f_pos += retval;

clean_up:
	mutex_unlock(&(dev_data->file_mutex));

	return retval;
}

/*
 * rmidev_write: - used to write data to rmi device
 *
 * @filep: file structure for write
 * @buf: user space buffer pointer
 * @count: number of bytes to write
 * @f_pos: offset (starting register address)
 */
static ssize_t rmidev_write(struct file *filp, const char __user *buf,
		size_t count, loff_t *f_pos)
{
	ssize_t retval;
	struct rmidev_data *dev_data = filp->private_data;

	if (IS_ERR(dev_data)) {
		TS_LOG_ERR("Pointer of char device data is invalid");
		return -EBADF;
	}

	if (count == 0)
		return 0;

	if (count > (REG_ADDR_LIMIT - *f_pos))
		count = REG_ADDR_LIMIT - *f_pos;

	rmidev_allocate_buffer(count);

	if (copy_from_user(rmidev->tmpbuf, buf, count))
		return -EFAULT;

	mutex_lock(&(dev_data->file_mutex));

	retval = rmidev->fn_ptr->write(rmidev->rmi4_data,
			*f_pos,
			rmidev->tmpbuf,
			count);
	if (retval >= 0)
		*f_pos += retval;

	mutex_unlock(&(dev_data->file_mutex));

	return retval;
}

/*
 * rmidev_open: enable access to rmi device
 * @inp: inode struture
 * @filp: file structure
 */
static int rmidev_open(struct inode *inp, struct file *filp)
{
	int retval = 0;
	struct synaptics_rmi4_data *rmi4_data = rmidev->rmi4_data;
	struct rmidev_data *dev_data =
			container_of(inp->i_cdev, struct rmidev_data, main_dev);

	if (!dev_data)
		return -EACCES;

	filp->private_data = dev_data;

	mutex_lock(&(dev_data->file_mutex));

	rmi4_data->fw_debug = true;
	TS_LOG_INFO("Attention interrupt disabled\n");

	if (dev_data->ref_count < 1)
		dev_data->ref_count++;
	else
		retval = -EACCES;

	mutex_unlock(&(dev_data->file_mutex));

	return retval;
}

/*
 * rmidev_release: - release access to rmi device
 * @inp: inode structure
 * @filp: file structure
 */
static int rmidev_release(struct inode *inp, struct file *filp)
{
	struct synaptics_rmi4_data *rmi4_data = rmidev->rmi4_data;
	struct rmidev_data *dev_data =
			container_of(inp->i_cdev, struct rmidev_data, main_dev);

	if (!dev_data)
		return -EACCES;

	rmi4_data->reset_device(rmi4_data);

	mutex_lock(&(dev_data->file_mutex));

	dev_data->ref_count--;
	if (dev_data->ref_count < 0)
		dev_data->ref_count = 0;

	rmi4_data->fw_debug = false;
	TS_LOG_INFO("Attention interrupt enabled\n");

	mutex_unlock(&(dev_data->file_mutex));

	return 0;
}

static const struct file_operations rmidev_fops = {
	.owner = THIS_MODULE,
	.llseek = rmidev_llseek,
	.read = rmidev_read,
	.write = rmidev_write,
	.open = rmidev_open,
	.release = rmidev_release,
};

static void rmidev_device_cleanup(struct rmidev_data *dev_data)
{
	dev_t devno;

	if (dev_data) {
		devno = dev_data->main_dev.dev;

		if (dev_data->device_class)
			device_destroy(dev_data->device_class, devno);

		cdev_del(&dev_data->main_dev);

		unregister_chrdev_region(devno, 1);

		TS_LOG_INFO("rmidev device removed\n");
	}

	return;
}

static char *rmi_char_devnode(struct device *dev, mode_t *mode)
{
	if (!mode)
		return NULL;

	*mode = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	return kasprintf(GFP_KERNEL, "rmi/%s", dev_name(dev));
}

static int rmidev_create_device_class(void)
{
	rmidev_device_class = class_create(THIS_MODULE, DEVICE_CLASS_NAME);

	if (IS_ERR(rmidev_device_class)) {
		TS_LOG_ERR("Failed to create /dev/%s\n", CHAR_DEVICE_NAME);
		return -ENODEV;
	}

	rmidev_device_class->devnode = rmi_char_devnode;

	return 0;
}

void synaptics_fw_debug_dev_init(struct synaptics_rmi4_data *rmi4_data)
{
	int retval = NO_ERR;
	dev_t dev_no = 0;
	int attr_count;
	struct rmidev_data *dev_data;
	struct device *device_ptr;

	TS_LOG_INFO("synaptics_fw_debug_dev_init called\n");
	rmidev = kzalloc(sizeof(*rmidev), GFP_KERNEL);
	if (!rmidev) {
		TS_LOG_ERR("Failed to alloc mem for rmidev\n");
		goto err_rmidev;
	}
	rmidev->fn_ptr = kzalloc(sizeof(*(rmidev->fn_ptr)), GFP_KERNEL);
	if (!rmidev->fn_ptr) {
		TS_LOG_ERR("Failed to alloc mem for fn_ptr\n");
		goto err_fn_ptr;
	}

	rmidev->fn_ptr->read = rmi4_data->i2c_read;
	rmidev->fn_ptr->write = rmi4_data->i2c_write;
	rmidev->rmi4_data = rmi4_data;

	retval = rmidev_create_device_class();
	if (retval < 0) {
		TS_LOG_ERR("Failed to create device class\n");
		goto err_device_class;
	}

	if (rmidev_major_num) {
		dev_no = MKDEV(rmidev_major_num, DEV_NUMBER);
		retval = register_chrdev_region(dev_no, 1, CHAR_DEVICE_NAME);
		if (retval < 0) {
			TS_LOG_ERR("Failed to register chrdev region\n");
			goto err_device_region;
		}
	} else {
		retval = alloc_chrdev_region(&dev_no, 0, 1, CHAR_DEVICE_NAME);
		if (retval < 0) {
			TS_LOG_ERR("Failed to allocate char device region\n");
			goto err_device_region;
		}
		rmidev_major_num = MAJOR(dev_no);
		TS_LOG_INFO("Major number of rmidev = %d\n", rmidev_major_num);
	}

	dev_data = kzalloc(sizeof(*dev_data), GFP_KERNEL);
	if (!dev_data) {
		TS_LOG_ERR("Failed to alloc mem for dev_data\n");
		goto err_dev_data;
	}

	mutex_init(&dev_data->file_mutex);
	dev_data->rmi_dev = rmidev;
	rmidev->data = dev_data;

	cdev_init(&dev_data->main_dev, &rmidev_fops);

	retval = cdev_add(&dev_data->main_dev, dev_no, 1);
	if (retval < 0) {
		TS_LOG_ERR("Failed to add rmi char device\n");
		goto err_char_device;
	}

	dev_set_name(&rmidev->dev, "rmidev%d", MINOR(dev_no));
	dev_data->device_class = rmidev_device_class;

	device_ptr = device_create(dev_data->device_class, NULL, dev_no,
			NULL, CHAR_DEVICE_NAME"%d", MINOR(dev_no));
	if (IS_ERR(device_ptr)) {
		TS_LOG_ERR("Failed to create rmi char device\n");
		//retval = -ENODEV;
		goto err_char_device;
	}

	retval = gpio_export(rmi4_data->synaptics_chip_data->irq_gpio, false);
	if (retval < 0) {
		TS_LOG_ERR("Failed to export attention gpio\n");
	} else {
		retval = gpio_export_link(&(rmi4_data->input_dev->dev),
				"attn", rmi4_data->synaptics_chip_data->irq_gpio);
		if (retval < 0) {
			TS_LOG_ERR("Failed to create gpio symlink\n");
		} else {
			TS_LOG_INFO("Exported attention gpio %d\n", rmi4_data->synaptics_chip_data->irq_gpio);
		}
	}

	rmidev->sysfs_dir = kobject_create_and_add(SYSFS_FOLDER_NAME,
			&rmi4_data->input_dev->dev.kobj);
	if (!rmidev->sysfs_dir) {
		TS_LOG_ERR("Failed to create sysfs directory\n");
		goto err_sysfs_dir;
	}

	retval = sysfs_create_bin_file(rmidev->sysfs_dir,
			&attr_data);
	if (retval < 0) {
		TS_LOG_ERR("Failed to create sysfs bin file\n");
		goto err_sysfs_bin;
	}

	for (attr_count = 0; attr_count < ARRAY_SIZE(attrs); attr_count++) {
		retval = sysfs_create_file(rmidev->sysfs_dir,
				&attrs[attr_count].attr);
		if (retval < 0) {
			TS_LOG_ERR("Failed to create sysfs attributes\n");
			retval = -ENODEV;
			goto err_sysfs_attrs;
		}
	}

	return;

err_sysfs_attrs:
	for (attr_count--; attr_count >= 0; attr_count--)
		sysfs_remove_file(rmidev->sysfs_dir, &attrs[attr_count].attr);

	sysfs_remove_bin_file(rmidev->sysfs_dir, &attr_data);
err_sysfs_bin:
	kobject_put(rmidev->sysfs_dir);
err_sysfs_dir:
err_char_device:
	rmidev_device_cleanup(dev_data);
	kfree(dev_data);
	dev_data = NULL;
err_dev_data:
	unregister_chrdev_region(dev_no, 1);
err_device_region:
	class_destroy(rmidev_device_class);
err_device_class:
	kfree(rmidev->fn_ptr);
	rmidev->fn_ptr = NULL;
err_fn_ptr:
	kfree(rmidev);
	rmidev = NULL;
err_rmidev:
	return;
}

