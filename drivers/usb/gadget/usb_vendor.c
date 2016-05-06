/*
 * usb_vendor.c -- Hisilicon usb notifier
 *
 * Copyright (C) 2015 by Hisilicon
 * Author: Hisilicon
 *
 * This software is distributed under the terms of the GNU General
 * Public License ("GPL") as published by the Free Software Foundation,
 * either version 2 of that License or (at your option) any later version.
 */
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/export.h>
#include <linux/delay.h>
#include <linux/fcntl.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/wakelock.h>

#include "usb_vendor.h"

/*
 * usb adapter for charger
 */
typedef struct usb_notifer_ctx {
	int usb_status;
	int usb_old_status;
	char last_cdev_name[USB_CDEV_NAME_MAX];
	unsigned stat_usb_insert;
	unsigned stat_usb_insert_proc;
	unsigned stat_usb_insert_proc_end;
	unsigned stat_usb_enum_done;
	unsigned stat_usb_enum_done_proc;
	unsigned stat_usb_enum_done_proc_end;
	unsigned stat_usb_remove;
	unsigned stat_usb_remove_proc;
	unsigned stat_usb_remove_proc_end;
	unsigned stat_usb_disable;
	unsigned stat_usb_disable_proc;
	unsigned stat_usb_disable_proc_end;
	unsigned stat_usb_no_need_notify;
	unsigned stat_wait_cdev_created;

	struct workqueue_struct *usb_notify_wq;
	struct delayed_work usb_notify_wk;
} usb_notifer_ctx_t;

static BLOCKING_NOTIFIER_HEAD(usb_balong_notifier_list);
static usb_notifer_ctx_t g_usb_notifier;

/*
 * usb enum done management
 */

static usb_enum_stat_t g_usb_devices_enum_stat[USB_FD_DEVICE_MAX];
static unsigned g_usb_dev_enum_done_num;
static unsigned g_usb_dev_setup_num;

/*
 * usb enum done management implement
 */
void bsp_usb_init_enum_stat(void)
{
	g_usb_dev_enum_done_num = 0;
	g_usb_dev_setup_num = 0;
	memset(g_usb_devices_enum_stat, 0, sizeof(g_usb_devices_enum_stat));
}

void bsp_usb_add_setup_dev_fdname(unsigned intf_id, char *fd_name)
{
	if (g_usb_dev_setup_num >= USB_FD_DEVICE_MAX) {
		pr_err("%s error, setup_num:%d, USB_FD_DEVICE_MAX:%d\n",
			   __FUNCTION__, g_usb_dev_setup_num, USB_FD_DEVICE_MAX);
		return;
	}
	g_usb_devices_enum_stat[g_usb_dev_setup_num].usb_intf_id = intf_id;
	g_usb_devices_enum_stat[g_usb_dev_setup_num].fd_name = fd_name;
	g_usb_dev_setup_num++;
}

int bsp_usb_is_all_enum(void)
{
	return (g_usb_dev_setup_num != 0 && g_usb_dev_setup_num == g_usb_dev_enum_done_num);
}

int bsp_usb_is_all_disable(void)
{
	return (g_usb_dev_setup_num != 0 && 0 == g_usb_dev_enum_done_num);
}

void bsp_usb_set_enum_stat(unsigned intf_id, int enum_stat)
{
	int i;
	usb_enum_stat_t *find_dev = NULL;

	if (enum_stat) {
		/* if all dev is already enum, do nothing */
		if (bsp_usb_is_all_enum()) {
			return;
		}

		for (i = 0; i < g_usb_dev_setup_num; i++) {
			if (g_usb_devices_enum_stat[i].usb_intf_id == intf_id) {
				find_dev = &g_usb_devices_enum_stat[i];
			}
		}
		if (find_dev) {
			/* if the dev is already enum, do nothing */
			if (find_dev->is_enum) {
				return;
			}
			find_dev->is_enum = enum_stat;
			g_usb_dev_enum_done_num++;

			/* after change stat, if all dev enum done, notify callback */
			if (bsp_usb_is_all_enum()) {
				bsp_usb_status_change(USB_BALONG_ENUM_DONE);
			}
		}
	} else {
		if (bsp_usb_is_all_disable()) {
			return;
		}

		for (i = 0; i < g_usb_dev_setup_num; i++) {
			if (g_usb_devices_enum_stat[i].usb_intf_id == intf_id) {
				find_dev = &g_usb_devices_enum_stat[i];
			}
		}
		if (find_dev) {
			/* if the dev is already disable, do nothing */
			if (!find_dev->is_enum) {
				return;
			}
			find_dev->is_enum = enum_stat;

			/* g_usb_dev_enum_done_num is always > 0,
			 * we protect it in check bsp_usb_is_all_disable
			 */
			if (g_usb_dev_enum_done_num > 0) {
				g_usb_dev_enum_done_num--;
			}

			/* if the version is not support pmu detect
			 * and all the device is disable, we assume that the usb is remove,
			 * so notify disable callback, tell the other modules
			 * else, we use the pmu remove detect.
			 */
			if (bsp_usb_is_all_disable()) {
				bsp_usb_status_change(USB_BALONG_DEVICE_DISABLE);
			}
		}
	}

	return;
}

void bsp_usb_enum_info_dump(void)
{
	int i;

	printk("balong usb is enum done:%d\n", bsp_usb_is_all_enum());
	printk("setup_num:%d, enum_done_num:%d\n",
		   g_usb_dev_setup_num, g_usb_dev_enum_done_num);
	printk("device enum info details:\n\n");
	for (i = 0; i < g_usb_dev_setup_num; i++) {
		printk("enum dev:%d\n", i);
		printk("usb_intf_id:%d\n", g_usb_devices_enum_stat[i].usb_intf_id);
		printk("is_enum:%d\n", g_usb_devices_enum_stat[i].is_enum);
		printk("fd_name:%s\n\n", g_usb_devices_enum_stat[i].fd_name);
	}
}


/*
 * usb charger adapter implement
 */
void bsp_usb_status_change(int status)
{
	unsigned long timeout = 0;

	if (USB_BALONG_ENUM_DONE == status)
		g_usb_notifier.stat_usb_enum_done++;
	else if (USB_BALONG_DEVICE_INSERT == status)
		g_usb_notifier.stat_usb_insert++;
	else if (USB_BALONG_DEVICE_REMOVE == status)
		g_usb_notifier.stat_usb_remove++;
	else if (USB_BALONG_DEVICE_DISABLE == status)
		g_usb_notifier.stat_usb_disable++;
	else
		pr_err("%s: error status:%d\n", __func__, status);

	g_usb_notifier.usb_status = status;

	queue_delayed_work(g_usb_notifier.usb_notify_wq,
			&g_usb_notifier.usb_notify_wk, timeout); /* usb_notify_handler */
}
EXPORT_SYMBOL_GPL(bsp_usb_status_change);

static void bsp_usb_insert_process(void)
{
	g_usb_notifier.stat_usb_insert_proc++;

	blocking_notifier_call_chain(&usb_balong_notifier_list,
			 USB_BALONG_DEVICE_INSERT, (void *)&g_usb_notifier);
	blocking_notifier_call_chain(&usb_balong_notifier_list,
			 USB_BALONG_CHARGER_IDEN, (void *)&g_usb_notifier);

	g_usb_notifier.stat_usb_insert_proc_end++;
	return;
}

void bsp_usb_set_last_cdev_name(char *dev_name)
{
	if (dev_name) {
		strncpy(g_usb_notifier.last_cdev_name, dev_name, USB_CDEV_NAME_MAX - 1);
		g_usb_notifier.last_cdev_name[USB_CDEV_NAME_MAX - 1] = '\0';
	}
}

void bsp_usb_clear_last_cdev_name(void)
{
	g_usb_notifier.last_cdev_name[0] = 0;
}

static void bsp_usb_wait_cdev_created(void)
{
	mm_segment_t old_fs;

	/* if there are no cdev, do nothing */
	if (strlen(g_usb_notifier.last_cdev_name) == 0)
		return;

	old_fs = get_fs();
	set_fs(KERNEL_DS);
	while (sys_faccessat(AT_FDCWD, g_usb_notifier.last_cdev_name, O_RDWR)) {
		g_usb_notifier.stat_wait_cdev_created++;
		msleep(100);
	}
	set_fs(old_fs);
}

static void bsp_usb_enum_done_process(void)
{
	pr_info("balong usb enum done.\n");
	g_usb_notifier.stat_usb_enum_done_proc++;

	/*
	 * wait for /dev/xxx created by udev
	 */
	bsp_usb_wait_cdev_created();

	/* notify kernel notifier */
	blocking_notifier_call_chain(&usb_balong_notifier_list,
			USB_BALONG_ENUM_DONE, (void *)&g_usb_notifier);

	g_usb_notifier.stat_usb_enum_done_proc_end++;
}

static void bsp_usb_remove_device_process(void)
{
	pr_info("balong usb remove.\n");
	bsp_usb_clear_last_cdev_name();
	g_usb_notifier.stat_usb_remove_proc++;

	/* notify kernel notifier,
	 * we must call notifier list before disable callback,
	 * there are something need to do before user
	 */
	blocking_notifier_call_chain(&usb_balong_notifier_list,
			USB_BALONG_DEVICE_REMOVE, (void *)&g_usb_notifier);

	g_usb_notifier.stat_usb_remove_proc_end++;

	return;
}

static void bsp_usb_disable_device_process(void)
{
	pr_info("balong usb disable.\n");
	bsp_usb_clear_last_cdev_name();
	g_usb_notifier.stat_usb_disable_proc++;

	/* notify kernel notifier */
	blocking_notifier_call_chain(&usb_balong_notifier_list,
			USB_BALONG_DEVICE_DISABLE, (void *)&g_usb_notifier);

	g_usb_notifier.stat_usb_disable_proc_end++;

	return;
}


/**
 * usb_register_notify - register a notifier callback whenever a usb change happens
 * @nb: pointer to the notifier block for the callback events.
 *
 * These changes are either USB devices or busses being added or removed.
 */
void bsp_usb_register_notify(struct notifier_block *nb)
{
	blocking_notifier_chain_register(&usb_balong_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(bsp_usb_register_notify);

/**
 * usb_unregister_notify - unregister a notifier callback
 * @nb: pointer to the notifier block for the callback events.
 *
 * usb_register_notify() must have been previously called for this function
 * to work properly.
 */
void bsp_usb_unregister_notify(struct notifier_block *nb)
{
	blocking_notifier_chain_unregister(&usb_balong_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(bsp_usb_unregister_notify);

void bsp_usb_notifier_dump(void)
{
	pr_info("stat_usb_insert:            %d\n", g_usb_notifier.stat_usb_insert);
	pr_info("stat_usb_insert_proc:       %d\n", g_usb_notifier.stat_usb_insert_proc);
	pr_info("stat_usb_insert_proc_end:   %d\n", g_usb_notifier.stat_usb_insert_proc_end);
	pr_info("stat_usb_enum_done:         %d\n", g_usb_notifier.stat_usb_enum_done);
	pr_info("stat_usb_enum_done_proc:    %d\n", g_usb_notifier.stat_usb_enum_done_proc);
	pr_info("stat_usb_enum_done_proc_end:%d\n", g_usb_notifier.stat_usb_enum_done_proc_end);
	pr_info("stat_usb_remove:            %d\n", g_usb_notifier.stat_usb_remove);
	pr_info("stat_usb_remove_proc:       %d\n", g_usb_notifier.stat_usb_remove_proc);
	pr_info("stat_usb_remove_proc_end:   %d\n", g_usb_notifier.stat_usb_remove_proc_end);
	pr_info("stat_usb_disable:           %d\n", g_usb_notifier.stat_usb_disable);
	pr_info("stat_usb_disable_proc:      %d\n", g_usb_notifier.stat_usb_disable_proc);
	pr_info("stat_usb_disable_proc_end:  %d\n", g_usb_notifier.stat_usb_disable_proc_end);
	pr_info("usb_status:                 %d\n", g_usb_notifier.usb_status);
	pr_info("usb_old_status:             %d\n", g_usb_notifier.usb_old_status);
	pr_info("stat_wait_cdev_created:     %d\n", g_usb_notifier.stat_wait_cdev_created);
	pr_info("last_cdev_name:             %s\n", g_usb_notifier.last_cdev_name);
	pr_info("stat_usb_no_need_notify:    %d\n", g_usb_notifier.stat_usb_no_need_notify);
}

int usb_notifier_mem_dump(char *buffer, unsigned int buf_size)
{
	unsigned int need_size = sizeof(g_usb_notifier);

	if (need_size > buf_size)
		return -1;

	memcpy(buffer, &g_usb_notifier, need_size);
	return (int)need_size;
}

static void usb_notify_handler(struct work_struct *work)
{
	int cur_status = g_usb_notifier.usb_status;

	if (g_usb_notifier.usb_old_status == cur_status) {
		g_usb_notifier.stat_usb_no_need_notify++;
		return;
	}

	switch (cur_status) {
	case USB_BALONG_DEVICE_INSERT:
		bsp_usb_insert_process();
		break;
	case USB_BALONG_ENUM_DONE:
		bsp_usb_enum_done_process();
		break;
	case USB_BALONG_DEVICE_REMOVE:
		bsp_usb_remove_device_process();
		break;
	case USB_BALONG_DEVICE_DISABLE:
		bsp_usb_disable_device_process();
		break;
	default:
		pr_err("%s, invalid status:%d\n", __func__, cur_status);
		return;
	}
	g_usb_notifier.usb_old_status = cur_status;
	return;
}

static int bsp_usb_notifier_init(void)
{
	/* init local ctx resource */
	g_usb_notifier.usb_notify_wq = create_singlethread_workqueue("usb_notify");
	if (!g_usb_notifier.usb_notify_wq) {
		pr_err("%s: create_singlethread_workqueue fail\n", __func__);
		return -ENOMEM;
	}
	INIT_DELAYED_WORK(&g_usb_notifier.usb_notify_wk, (void *)usb_notify_handler);
	return 0;
}

/* we don't need exit for adapter module */
int __init bsp_usb_vendor_init(void)
{
	return bsp_usb_notifier_init();
}
module_init(bsp_usb_vendor_init);
