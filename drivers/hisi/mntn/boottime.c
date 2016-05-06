/*
 * arch/arm/mach-hi6620/util.c
 *
 * balong platform misc utilities function
 *
 * Copyright (C) 2012 Hisilicon, Inc.
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
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/sysctl.h>
#include <linux/hisi/util.h>
#include <linux/uaccess.h>

static ssize_t boot_time_proc_read(struct file *file, char __user *userbuf,
				   size_t bytes, loff_t *off)
{
	/*do nothing */
	return bytes;
}

static ssize_t boot_time_proc_write(struct file *file, const char __user *buf,
				    size_t nr, loff_t *off)
{
	/*only need the print time */
	pr_err("bootanim has been complete, turn to Lancher!\n");

	return nr;
}

static const struct file_operations boot_time_proc_fops = {
	.read = boot_time_proc_read,
	.write = boot_time_proc_write,
};

static int __init boot_time_proc_init(void)
{
	balong_create_stats_proc_entry("boot_time", (S_IWUSR),
				       &boot_time_proc_fops, NULL);

	return 0;
}

module_init(boot_time_proc_init);
