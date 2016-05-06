 /*
  * drivers/hisi/pm_common/suspend.c
  *
  * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License version 2 as
  * published by the Free Software Foundation.
  */

#include <linux/device.h>
#include <linux/mutex.h>
#include <linux/pm_wakeup.h>
#include <linux/wakelock.h>
#include <linux/syscalls.h>
#include <linux/suspend.h>

static int suspend_sys_sync_count = 0;
static DEFINE_SPINLOCK(suspend_sys_sync_lock);
static struct workqueue_struct *suspend_sys_sync_work_queue = NULL;
static DECLARE_COMPLETION(suspend_sys_sync_comp);

static bool suspend_sys_sync_abort;
static void suspend_sys_sync_handler(unsigned long);
static DEFINE_TIMER(suspend_sys_sync_timer, suspend_sys_sync_handler, 0, 0);

static void suspend_sys_sync(struct work_struct *work)
{
	printk("PM: Syncing filesystems +\n");
	sys_sync();
	printk("PM: Syncing filesystems -\n");

	spin_lock(&suspend_sys_sync_lock);
	suspend_sys_sync_count--;
	spin_unlock(&suspend_sys_sync_lock);
}
static DECLARE_WORK(suspend_sys_sync_work, suspend_sys_sync);

void hisi_sys_sync_queue(void)
{
	int ret;

	spin_lock(&suspend_sys_sync_lock);
	ret = queue_work(suspend_sys_sync_work_queue, &suspend_sys_sync_work);
	if (ret)
		suspend_sys_sync_count++;
	spin_unlock(&suspend_sys_sync_lock);
}
EXPORT_SYMBOL(hisi_sys_sync_queue);

/* value should be less then half of input event wake lock timeout value
 * which is currently set to 5*HZ (see drivers/input/evdev.c)
 */
#define SUSPEND_SYS_SYNC_TIMEOUT (HZ/4)
static void suspend_sys_sync_handler(unsigned long arg)
{
	if (suspend_sys_sync_count == 0) {
		complete(&suspend_sys_sync_comp);
	} else if (pm_wakeup_pending()) {
		suspend_sys_sync_abort = true;
		complete(&suspend_sys_sync_comp);
	} else {
		mod_timer(&suspend_sys_sync_timer, jiffies +
				SUSPEND_SYS_SYNC_TIMEOUT);
	}
}

int hisi_sys_sync_wait(void)
{
	suspend_sys_sync_abort = false;

	if (suspend_sys_sync_count != 0) {
		mod_timer(&suspend_sys_sync_timer, jiffies +
				SUSPEND_SYS_SYNC_TIMEOUT);
		wait_for_completion(&suspend_sys_sync_comp);
	}

	if (suspend_sys_sync_abort) {
		pr_info("suspend aborted....while waiting for sys_sync\n");
		return -EBUSY;
	}

	return 0;
}
EXPORT_SYMBOL(hisi_sys_sync_wait);

static int __init sys_sync_thread_init(void)
{
	init_completion(&suspend_sys_sync_comp);

	suspend_sys_sync_work_queue = alloc_ordered_workqueue("sys_sync_suspend", 0);
	if (suspend_sys_sync_work_queue)
		return 0;

	return -ENOMEM;
}

core_initcall(sys_sync_thread_init);
