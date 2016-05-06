/*
 * record the data to rdr. (RDR: kernel run data recorder.)
 * This file wraps the ring buffer.
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <linux/rproc_share.h>
#include <linux/atomic.h>

#define MEM_SHARED_SIZE     0x1000
#define ISP_IOCTL_MAGIC     (0x70)
#define ISP_IOCTL_MAX_NR    (0x10)

extern int __inval_cache_range(unsigned int, unsigned int);
struct log_user_para {
	unsigned int log_write;
	unsigned int log_head_size;
};

#define LOG_WR_OFFSET       _IOWR(ISP_IOCTL_MAGIC, 0x00, struct log_user_para)

struct cdev_info {
	dev_t devt;
	struct cdev log_chrdev;
	struct device *log_dev;
	struct class *log_dev_class;
};

struct log_device {
	void __iomem *share_mem;
	struct rproc_shared_para *share_para;
	wait_queue_head_t wait_ctl;
	struct timer_list sync_timer;
	atomic_t open_cnt;
	int use_cacheable_rdr;
};

static struct log_device log_local_dev;
static struct cdev_info log_cdev;
extern u32 g_isp_rdr_addr;

static void isp_log_vm_open(struct vm_area_struct *area)
{
	pr_info("%s: enter.\n", __func__);
}

static void isp_log_vm_close(struct vm_area_struct *area)
{
	pr_info("%s: enter.\n", __func__);
}

static const struct vm_operations_struct isp_log_vm_ops = {
	.open = isp_log_vm_open,
	.close = isp_log_vm_close,
};

static void sync_timer_fn(unsigned long data)
{
	struct log_device *dev = &log_local_dev;

	pr_debug("sync_timer_fn enter.\n");
	if (dev->share_para->log_flush_flag)
		wake_up(&dev->wait_ctl);

	mod_timer(&dev->sync_timer, jiffies + msecs_to_jiffies(10));
}

static int isp_log_open(struct inode *inode, struct file *filp)
{
	struct log_device *dev = &log_local_dev;

	pr_info("%s: enter.\n", __func__);

	if (0 != atomic_read(&dev->open_cnt)) {
		pr_err("%s: Failed: has been opened\n", __func__);
		return -EBUSY;
	}

	dev->share_mem = ioremap_nocache(get_a7sharedmem_addr(), MEM_SHARED_SIZE);
	if (!dev->share_mem) {
		pr_err("%s: ioremap_nocache failed.\n", __func__);
		return -ENOMEM;
	}
	dev->share_para = (struct rproc_shared_para *)dev->share_mem;

	setup_timer(&dev->sync_timer, sync_timer_fn, 0);
	mod_timer(&dev->sync_timer, jiffies + msecs_to_jiffies(10));
	atomic_inc(&dev->open_cnt);
	pr_info("%s: exit.\n", __func__);

	return 0;
}

static long isp_log_ioctl(struct file *filp, unsigned int cmd,
			  unsigned long args)
{
	struct log_device *dev = &log_local_dev;
	struct log_user_para tmp;
	int ret;

	pr_debug("%s: enter.\n", __func__);
	if (_IOC_TYPE(cmd) != ISP_IOCTL_MAGIC) {
		pr_err("%s: type is wrong.\n", __func__);
		return -EINVAL;
	}

	if (_IOC_NR(cmd) >= ISP_IOCTL_MAX_NR) {
		pr_err("%s: number is wrong.\n", __func__);
		return -EINVAL;
	}

	switch (cmd) {
	case LOG_WR_OFFSET:
		ret = wait_event_timeout(dev->wait_ctl,
				       dev->share_para->log_flush_flag,
				       msecs_to_jiffies(400));
		if (0 == ret) {
			pr_debug("%s: wait timeout, ret = %d\n", __func__, ret);
			return -ETIMEDOUT;
		}

		if (dev->use_cacheable_rdr)
			dev->share_para->log_flush_flag = 0;

		tmp.log_write = dev->share_para->log_cache_write;
		tmp.log_head_size = dev->share_para->log_head_size;
		pr_debug("%s: write = %u, size = %d.\n", __func__,
			 tmp.log_write, tmp.log_head_size);
		if (copy_to_user((void __user *)args, &tmp, sizeof(tmp))) {
			pr_err("%s: copy_to_user failed.\n", __func__);
			return -EFAULT;
		}
		break;
	default:
		pr_err("%s: don't support cmd.\n", __func__);
		break;
	};

	return 0;
}

static int isp_log_mmap(struct file *filp, struct vm_area_struct *vma)
{
	unsigned long size;
	int ret;

    if (vma->vm_start == NULL)
        return -EINVAL;

	size = vma->vm_end - vma->vm_start;
	pr_alert("%s: enter, paddr = 0x%x, vaddr.0x%lx, size.0x%lx.(0x%lx - 0x%lx), _prot0x%lx\n",
	     __func__, g_isp_rdr_addr, vma->vm_start, size, vma->vm_end,
	     vma->vm_start, vma->vm_page_prot);
	ret = remap_pfn_range(vma, vma->vm_start,
						(g_isp_rdr_addr >> PAGE_SHIFT),
						size, vma->vm_page_prot);
	if (ret) {
		pr_err("%s: remap_pfn_range failed, ret.%d\n", __func__, ret);
		return ret;
	}

	isp_log_vm_open(vma);
	pr_info("%s: exit.\n", __func__);

	return 0;
}

static int isp_log_release(struct inode *inode, struct file *filp)
{
	struct log_device *dev = &log_local_dev;

	pr_info("%s: enter.\n", __func__);
	del_timer_sync(&dev->sync_timer);

	dev->share_para = NULL;
	iounmap(dev->share_mem);
	atomic_dec(&dev->open_cnt);
	pr_info("%s: exit.\n", __func__);

	return 0;
}

static const struct file_operations isp_log_ops = {
	.open = isp_log_open,
	.release = isp_log_release,
	.unlocked_ioctl = isp_log_ioctl,
	.compat_ioctl = isp_log_ioctl,
	.mmap = isp_log_mmap,
	.owner = THIS_MODULE,
};

static int __init isp_log_init(void)
{
	int ret = 0, major;

	pr_info("%s: enter.\n", __func__);

	init_waitqueue_head(&log_local_dev.wait_ctl);
	ret = alloc_chrdev_region(&log_cdev.devt, 0, 1, KBUILD_MODNAME);
	if (ret) {
		pr_err("%s: alloc_chrdev_region failed, ret.%d\n", __func__,
		       ret);
		goto out;
	}

	log_cdev.log_dev_class = class_create(THIS_MODULE, KBUILD_MODNAME);
	if (IS_ERR(log_cdev.log_dev_class)) {
		ret = PTR_ERR(log_cdev.log_dev_class);
		pr_err("%s: class_create failed, ret.%d\n", __func__, ret);
		goto unreg_region;
	}

	major = MAJOR(log_cdev.devt);
	pr_info("%s: log cdev major.%d.\n", __func__, major);

	cdev_init(&log_cdev.log_chrdev, &isp_log_ops);
	log_cdev.log_chrdev.owner = THIS_MODULE;

	ret = cdev_add(&log_cdev.log_chrdev, log_cdev.devt, 1);
	if (ret) {
		pr_err("%s: cdev_add failed, ret.%d\n", __func__, ret);
		goto destroy_class;
	}

	log_cdev.log_dev = device_create(log_cdev.log_dev_class, NULL,
									log_cdev.devt, NULL, "isp_log");
	if (IS_ERR(log_cdev.log_dev)) {
		ret = PTR_ERR(log_cdev.log_dev);
		pr_err("%s: device_create failed, ret.%d\n", __func__, ret);
		goto clean_cdev;
	}

	atomic_set(&log_local_dev.open_cnt, 0);
	log_local_dev.use_cacheable_rdr = 1;

	pr_info("%s: exit.\n", __func__);

	return 0;
clean_cdev:
	cdev_del(&log_cdev.log_chrdev);
destroy_class:
	class_destroy(log_cdev.log_dev_class);
unreg_region:
	unregister_chrdev_region(log_cdev.devt, 1);
out:
	pr_info("%s: Error, exit.\n", __func__);

	return ret;
}

module_init(isp_log_init);

static void __exit isp_log_exit(void)
{
	pr_info("%s: enter.\n", __func__);

	device_destroy(log_cdev.log_dev_class, log_cdev.devt);
	cdev_del(&log_cdev.log_chrdev);
	class_destroy(log_cdev.log_dev_class);
	unregister_chrdev_region(log_cdev.devt, 1);

	pr_info("%s: exit.\n", __func__);
}

module_exit(isp_log_exit);

MODULE_LICENSE("GPL v2");
