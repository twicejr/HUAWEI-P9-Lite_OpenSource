/*
 * Copyright (C) huawei company
 *
 * This	program	is free	software; you can redistribute it and/or modify
 * it under	the	terms of the GNU General Public	License	version	2 as
 * published by	the	Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/types.h>
#include <linux/of.h>
#include "sensor_sys_info.h"


#define READ_CURRENT_INTERVAL 500

int (*send_func)(int) = NULL;
static atomic_t enabled = ATOMIC_INIT(0);
struct delayed_work read_current_work;


extern int hisi_battery_current(void);
static void get_current_work_func(struct work_struct *work);

DECLARE_DELAYED_WORK(read_current_work, get_current_work_func);

/* 0 means not send current to IOM3;  1 means need to send current to IOM3*/
int check_if_need_current(void)
{
	int len = 0;
	struct device_node *sensorhub_node = NULL;
	const char *need_current = NULL;

	sensorhub_node = of_find_compatible_node(NULL, NULL, "huawei,sensorhub");
	if (!sensorhub_node) {
		printk("%s, can't find node sensorhub\n", __func__);
		return 0;
	}

	need_current = of_get_property(sensorhub_node, "akm_need_current", &len);
	if (!need_current) {
		printk("%s, can't find property boardname\n", __func__);
		return 0;
	}

	/*just send current to IOM3 in Mogolia*/
	if (strstr(need_current, "yes")) {
		printk("%s, akm need current\n", __func__);
		return 1;
	} else {
		printk("%s, not need current\n", __func__);
		return 0;
	}
}

int open_send_current(int (*send)(int))
{
	if (!atomic_cmpxchg(&enabled, 0, 1)) {
		schedule_delayed_work(&read_current_work,
				msecs_to_jiffies(READ_CURRENT_INTERVAL));

		send_func = send;
	} else {
		printk("%s allready opend\n", __func__);
	}

	return 0;
}

int close_send_current(void)
{
	if (atomic_cmpxchg(&enabled, 1, 0))
				cancel_delayed_work_sync(&read_current_work);
	return 0;
}

static void get_current_work_func(struct work_struct *work)
{
	int value = 0;

#if 0
	value = hisi_battery_current();
#endif
	/*send current to iom3*/
	if (send_func) {
		(*send_func)(value);
	}

	if(atomic_read(&enabled))
		schedule_delayed_work(&read_current_work, msecs_to_jiffies(READ_CURRENT_INTERVAL));
}
