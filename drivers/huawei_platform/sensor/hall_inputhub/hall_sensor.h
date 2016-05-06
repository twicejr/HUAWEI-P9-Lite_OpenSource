/*
 * copyright (C) 2014 HUAWEI, Inc.
 * Author: tuhaibo <tuhaibo@huawei.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/slab.h>

//define
#ifndef HALL_SENSOR
#define HALL_TEST
#define HALL_SENSOR

#ifdef HALL_TEST
#define HALL_REPORT_MAX_COUNT 1000
#define HALL_REPORT_MIN_COUNT 1
#define HALL_REPORT_MAX_PERIOD 1000
#define HALL_REPORT_MIN_PERIOD  50
#endif

typedef int packet_data;

typedef enum _hall_type {
	single_north_pole = 0,
	single_south_pole,
	double_poles,
} hall_type_t;

struct hall_cdev {
	struct device *dev;
	int hall_count;
	int (*hall_report_debug_data)(struct hall_cdev *, packet_data);
	int (*hall_report_state)(struct hall_cdev *);
	int (*hall_get_state)(struct hall_cdev *);
	int (*hall_get_info)(struct hall_cdev *, char *);
#ifdef HALL_TEST
	int count;
	packet_data value;
	int flag;
	int period;
	int enable;
	void (*hall_set_report_value)(struct hall_cdev *);
#endif
};

int hall_first_report(bool enable);
int ak8789_register_report_data(int ms);
int hall_register(struct hall_cdev *cdev);
void hall_unregister(struct hall_cdev *cdev);
#endif
