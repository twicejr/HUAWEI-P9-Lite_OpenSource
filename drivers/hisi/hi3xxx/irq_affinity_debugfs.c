/*
 * HI3630, debug code for irq affinity recovery driver.
 *
 * Copyright (c) 2014- Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/debugfs.h>
#include <linux/uaccess.h>
#include <linux/hisi/hi3xxx_irq_affinity.h>

#define MODULE_NAME "IRQAFF DEBUGFS"

static struct dentry *irqaff_debug_dir;
static struct dentry *irqaff_debug_fn;

static int irqaff_debugfs_show(struct seq_file *s, void *data)
{
	hisi_irqaffinity_status();
	return 0;
}

static int irqaff_debugfs_open(struct inode *inode, struct file *file)
{
	return single_open(file, irqaff_debugfs_show, inode->i_private);
}

static ssize_t
irqaff_debugfs_write(struct file *filp, const char __user *ubuf,
					size_t cnt, loff_t *ppos)
{
	char debugfs_cmd[128];
	char *_cmd = NULL;
	char *_tmp = NULL;
	unsigned int irq;
	unsigned int cpu;

	if (copy_from_user(debugfs_cmd, ubuf, cnt - 1)) {
		cnt = -EINVAL;
		goto out;
	}

	debugfs_cmd[cnt - 1] = '\0';
	_cmd = debugfs_cmd;
	pr_debug("%s: [cmd: %s[cnt: %d]]\n", MODULE_NAME, debugfs_cmd, (int)cnt);

	if (!strncmp("register ", _cmd, strlen("register "))) {
		_cmd = _cmd + strlen("register ");
		_tmp = _cmd;
		while ((' ' != *_tmp) && ('\0' != *_tmp))
			_tmp++;
		if ('\0' == *_tmp) {
			cnt = -EINVAL;
			goto out;
		}

		*_tmp = '\0';
		if (kstrtou32(_cmd, 10, &irq)) {
			cnt = -EINVAL;
			goto out;
		}

		*_tmp = ' ';
		_cmd = _tmp + 1;
		_tmp = _cmd;
		while ((' ' != *_tmp) && ('\0' != *_tmp))
			_tmp++;

		*_tmp = '\0';
		if (kstrtou32(_cmd, 10, &cpu)) {
			cnt = -EINVAL;
			goto out;
		}

		hisi_irqaffinity_register(irq, cpu);
	} else if (!strncmp("unregister ", _cmd, strlen("unregister "))) {
		_cmd = _cmd + strlen("unregister ");
		_tmp = _cmd;
		while ((' ' != *_tmp) && ('\0' != *_tmp))
			_tmp++;

		*_tmp = '\0';
		if (kstrtou32(_cmd, 10, &irq)) {
			cnt = -EINVAL;
			goto out;
		}

		hisi_irqaffinity_unregister(irq);
	} else {
		cnt = -EINVAL;
		goto out;
	}

out:
	return cnt;
}

static const struct file_operations irqaff_debugfs_fops = {
	.open		= irqaff_debugfs_open,
	.read		= seq_read,
	.write		= irqaff_debugfs_write,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init irqaff_debugfs_init(void)
{
	irqaff_debug_dir = debugfs_create_dir("hisi_irqaff_debug", NULL);
	if (irqaff_debug_dir)
		irqaff_debug_fn = debugfs_create_file("debug",
			S_IRUGO, irqaff_debug_dir, NULL, &irqaff_debugfs_fops);

	return 0;
}
module_init(irqaff_debugfs_init);

static void __exit irqaff_debugfs_exit(void)
{
	debugfs_remove(irqaff_debug_fn);
	debugfs_remove(irqaff_debug_dir);

	return;
}
module_exit(irqaff_debugfs_exit);

MODULE_DESCRIPTION("HI3630, debug code for irq affinity recovery driver.");
MODULE_LICENSE("GPL V2");
