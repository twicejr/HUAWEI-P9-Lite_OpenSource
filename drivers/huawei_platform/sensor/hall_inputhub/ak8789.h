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

#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/device.h>
#include <linux/workqueue.h>
#include <linux/wakelock.h>
#include <linux/time.h>
#include <linux/gpio.h>
#include <linux/list.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/irq.h>
#include <dsm/dsm_pub.h>
#include "hall_sensor.h"

#ifdef CONFIG_HUAWEI_HALL_INPUTHUB
#define HALL_DATA_REPORT_INPUTHUB
#endif

#ifdef CONFIG_HUAWEI_HALL_INPUTDEV
#define HALL_DATA_REPORT_INPUTDEV
#endif

#if defined (CONFIG_HUAWEI_DSM) && defined (DSM_HALL_ERROR_NO)
#define HALL_DSM_CONFIG
#endif
#define HALL_SINGLE_N_POLE				"huawei,single-n-pole"
#define HALL_SINGLE_S_POLE				"huawei,single-s-pole"
#define HALL_DOUBLE_POLE				"huawei,double-pole"
#define HALL_ID							"huawei,id"
#define HALL_TYPE						"huawei,type"
#define HALL_HW_WAKEUP_SUPPORT			"huawei,hw-wakeup-support"
#define HALL_WAKEUP_FLAG				"huawei,wakeup-flag"
#define HALL_DEFAULT_STATE				"huawei,default-state"
#define HALL_X_COORDINATE				"huawei,x-coordinate"
#define HALL_Y_COORDINATE				"huawei,y-coordinate"
#define HALL_AUXILIARY_ID				"huawei,auxiliary-id"
#define HALL_AUXILIARY_N				"huawei,auxiliary-north"
#define HALL_AUXILIARY_S				"huawei,auxiliary-south"
#define HALL_MAX_STRING_LEN				16
#define HALL_MXA_INFO_LEN				256
#define HALL_SENSOR_NAME 				"hall,sensor"
#define GPIO_HIGH_VOLTAGE  				(1)
#define GPIO_LOW_VOLTAGE    			(0)
#define NORTH_POLE_NAME 				"hall_north_pole"
#define SOUTH_POLE_NAME 				"hall_south_pole"
#define X_COR 							"x_coordinate"
#define Y_COR 							"y_coordinate"
#define HALL_1000000					1000000L
#define HALL_IRQ_ABNORMAL_TIME			50000L

struct hall_info {
	unsigned int h_type;
	unsigned int gpio[2];
	int irq[2];
	int trigger_style[2];
	unsigned int auxiliary_io[2];
	char name[2][HALL_MAX_STRING_LEN];

#ifdef HALL_TEST
	atomic_t irq_err_count[2];
	long irq_time;		//du to the the type of menbers of the struct timeval is long, so use long type to defne irq_time
	struct timeval last_time[2];
	struct timeval now_time[2];
#endif
};

struct hall_device {
	struct platform_device *pdev;
	int hall_id;
	int hall_type;
	int hall_wakeup_flag;
	int hall_x_coordinate;
	int hall_y_coordinate;
	int hall_auxiliary_flag;
	int hall_hw_wakeup_support;
	int default_state;

	struct list_head list;
	struct delayed_work h_delayed_work;
	char name[HALL_MAX_STRING_LEN];
	struct hall_info h_info;
};

struct ak8789_data {
	struct hall_cdev cdev;
	struct list_head head;
	struct platform_device *pdev;

	int count;
	int state;
	struct workqueue_struct *hall_wq;
	struct wake_lock wakelock;
	spinlock_t spinlock;

	struct work_struct inter_work;

#ifdef HALL_DATA_REPORT_INPUTDEV
	struct input_dev        *input_dev;
#endif

#ifdef HALL_TEST
	int enable;
	int report_count;
	packet_data value;
	int flag;
	int period;
#ifdef HALL_DSM_CONFIG
	struct dsm_client *hall_dclient;
#endif
#endif
};

#ifdef HALL_DATA_REPORT_INPUTDEV
int ak8789_input_register(struct ak8789_data *data);
void ak8789_input_unregister(struct ak8789_data *data);
#endif
int ak8789_report_data(void *data, packet_data pdata);
