/*
 * copyright (C) 2013 HUAWEI, Inc.
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

#ifndef HALL_AK8789_H
#define HALL_AK8789_H



#include <asm/io.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/wakelock.h>
#include <linux/workqueue.h>
#include <uapi/asm-generic/errno-base.h>
#include <asm/atomic.h>
#include <linux/board_sensors.h>
#include	<linux/sensors.h>

#define HALL_SUPPORT_NUM_MAX                (4)
#define MAX_IRQ_NAME_LEN            (50)
#define HALL_SENSOR_NAME            "hall,sensor"
#define GPIO_HIGH_VOLTAGE           (1)
#define GPIO_LOW_VOLTAGE                (0)
#define HALL0_NORTH_POLE_NAME             "hall0_north_pole"
#define HALL0_SOUTH_POLE_NAME             "hall0_south_pole"
#define HALL1_NORTH_POLE_NAME             "hall1_north_pole"
#define HALL1_SOUTH_POLE_NAME             "hall1_south_pole"
#define HALL_ID                 "hall_id"
#define HALL_TYPE               "hall_type"
#define HALL0_NORTH_WAKE_UP                "hall0_north_wake_up_flag"
#define HALL1_NORTH_WAKE_UP                "hall1_north_wake_up_flag"
#define HALL0_SOUTH_WAKE_UP                "hall0_south_wake_up_flag"
#define HALL1_SOUTH_WAKE_UP                "hall1_south_wake_up_flag"
#define HALL0_X_COR                   "hall0_x_coordinate"
#define HALL0_Y_COR                   "hall0_y_coordinate"
#define HALL1_X_COR                   "hall1_x_coordinate"
#define HALL1_Y_COR                   "hall1_y_coordinate"

typedef int packet_data;

typedef enum _hall_type {
    single_north_pole = 0,
    single_south_pole,
    north_one_south_one,
    north_two_south_one,
    north_two_south_two
} hall_type_t;

typedef enum _hall_status {
    hall_work_status = 1,
    hall_removed_status
} hall_status_t;

struct irq_info {
    int irq;
    int trigger_value;
    int wake_up;
    char name[MAX_IRQ_NAME_LEN];
};

struct hall_dev {
    int hall_type;
    hall_status_t hall_status;
    int hall_id;
    int hall0_x_coordinate;
    int hall1_x_coordinate;
    int hall0_y_coordinate;
    int hall1_y_coordinate;
    void *hall_device;
    struct platform_device *hall_dev;
    struct sensors_classdev cdev;
    struct work_struct hall_work;
    struct hall_ops *ops;
    struct irq_info irq_info[HALL_SUPPORT_NUM_MAX];
    struct input_dev *hw_input_hall;
};

struct hall_ops {
    int (*packet_event_data)(struct hall_dev *);
    int (*hall_event_report)(packet_data, struct hall_dev *);
    int (*hall_device_irq_top_handler)(int , struct hall_dev *);
    int (*hall_release)(struct hall_dev *);
       int (*hall_device_init)(struct platform_device *pdev,\
        struct hall_dev *phall_dev);
};

#define HALL_EVENT_START_SHIFT          (2)
#define MAX_GPIO_NAME_LEN           (50)

struct hall_ak8789_dev {
    hall_type_t hall_ak8789_type;
    int gpio_poles[HALL_SUPPORT_NUM_MAX];
};
static int gpio_index_to_name(int index, char *name);
static int setup_gpio (int gpio_id, const char *gpio_name);
static int gpio_irq_trigger_inversion(int irq);
static int hall_ak8789_irq_top_handler(int irq, struct hall_dev *phall_dev);
static packet_data hall_ak8789_packet_event_data(struct hall_dev *phall_dev);
static int hall_ak8789_release(struct hall_dev *phall_dev);
static int hall_ak8789_device_init(struct platform_device *pdev,struct hall_dev *phall_dev);
static int hall_ak8789_event_report(packet_data packet_data,struct hall_dev *phall_dev);
static struct hall_ops hall_device_ops = {
    .packet_event_data = hall_ak8789_packet_event_data,
    .hall_event_report = hall_ak8789_event_report,
    .hall_device_irq_top_handler = hall_ak8789_irq_top_handler,
    .hall_release = hall_ak8789_release,
    .hall_device_init = hall_ak8789_device_init,
};
#endif
