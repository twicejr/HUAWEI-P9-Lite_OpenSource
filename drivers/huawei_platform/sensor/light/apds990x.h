/* drivers/input/misc/tmd2771.h
 *
 * Copyright (C) 2011 HUAWEI, Inc.
 * Author: chenlian <chenlian@huawei.com>
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
#include <linux/regulator/consumer.h>
#include <linux/wakelock.h>
#include "rpr0521_driver.h"
#include	<linux/sensors.h>
#define APDS990x_DRV_NAME    "apds990x"
#define DRIVER_VERSION        "1.0.4"

#define    PL990x_POWER_NAME    "PROXIMITY_LIGHT_VDD_SENSOR"
#define APDS990x_INT        IRQ_EINT20

#define APDS990x_PS_DETECTION_THRESHOLD        550
#define APDS990x_PS_HSYTERESIS_THRESHOLD    450

#define APDS990x_ALS_THRESHOLD_HSYTERESIS    20    /* 20 = 20% */
#define SCALE 35
#define APDS990x_ENABLE_REG    0x00
#define APDS990x_ATIME_REG    0x01
#define APDS990x_PTIME_REG    0x02
#define APDS990x_WTIME_REG    0x03
#define APDS990x_AILTL_REG    0x04
#define APDS990x_AILTH_REG    0x05
#define APDS990x_AIHTL_REG    0x06
#define APDS990x_AIHTH_REG    0x07
#define APDS990x_PILTL_REG    0x08
#define APDS990x_PILTH_REG    0x09
#define APDS990x_PIHTL_REG    0x0A
#define APDS990x_PIHTH_REG    0x0B
#define APDS990x_PERS_REG    0x0C
#define APDS990x_CONFIG_REG    0x0D
#define APDS990x_PPCOUNT_REG    0x0E
#define APDS990x_CONTROL_REG    0x0F
#define APDS990x_REV_REG    0x11
#define APDS990x_ID_REG        0x12
#define APDS990x_STATUS_REG    0x13
#define APDS990x_CDATAL_REG    0x14
#define APDS990x_CDATAH_REG    0x15
#define APDS990x_IRDATAL_REG    0x16
#define APDS990x_IRDATAH_REG    0x17
#define APDS990x_PDATAL_REG    0x18
#define APDS990x_PDATAH_REG    0x19

#define CMD_BYTE    0x80
#define CMD_WORD    0xA0
#define CMD_SPECIAL    0xE0

#define CMD_CLR_PS_INT    0xE5
#define CMD_CLR_ALS_INT    0xE6
#define CMD_CLR_PS_ALS_INT    0xE7
//#define APDS993X_REG_LEN  0x1a
#define APDS990X_REG_LEN  0x1a


/*
 * Structs
 */
struct apds990x_data {
	struct i2c_client *client;
	struct mutex update_lock;
	struct mutex single_lock;
	struct workqueue_struct *ps_wq;
	struct delayed_work	dwork;    /* for PS interrupt */
	struct delayed_work	als_dwork; /* for ALS polling */
	struct delayed_work    power_work;
	struct input_dev *input_dev_als;
	struct input_dev *input_dev_ps;
       struct sensors_classdev als_cdev;
       struct sensors_classdev ps_cdev;
	unsigned int enable;
	unsigned int atime;
	unsigned int ptime;
	unsigned int wtime;
	unsigned int ailt;
	unsigned int aiht;
	unsigned int pilt;
	unsigned int piht;
	unsigned int pers;
	unsigned int config;
	unsigned int ppcount;
	unsigned int control;
	int	irq;
	int apds_gpio;

	/* control flag from HAL */
	unsigned int enable_ps_sensor;
	unsigned int enable_als_sensor;

	/* PS parameters */
	unsigned int ps_lock;
	unsigned int ps_threshold;
	unsigned int ps_hysteresis_threshold; /* always lower than ps_threshold */
	unsigned int ps_detection;        /* 0 = near-to-far; 1 = far-to-near */
	unsigned int ps_data;            /* to store PS data */

    /* ALS parameters */
	unsigned int als_threshold_l;    /* low threshold */
	unsigned int als_threshold_h;    /* high threshold */
	unsigned int als_data;            /* to store ALS data */

	unsigned int als_gain;            /* needed for Lux calculation */
	unsigned int als_poll_delay;    /* needed for light sensor polling : micro-second (us) */
	unsigned int als_atime;            /* storage for als integratiion time */
//	struct early_suspend early_suspend;
	struct regulator *apds990x_vdd;
	struct regulator *apds990x_io_vdd;
	struct wake_lock wake_lock;
#if defined(CONFIG_FB)
	struct notifier_block fb_notify;
#endif
};

extern ssize_t ts_chip_info_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count);
extern ssize_t ts_chip_info_show(struct device *dev, struct device_attribute *attr, char *buf);
extern ssize_t cyttsp5_chip_info_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count);
extern ssize_t cyttsp5_chip_info_show(struct device *dev, struct device_attribute *attr, char *buf);
struct apds990x_platform_data {
	int (*gpio_config_interrupt)(void);
	int (*power_on)(struct device *);
	int (*power_off)(void);
	int apds990x_gpio;
};
