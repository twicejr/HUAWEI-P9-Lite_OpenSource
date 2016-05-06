/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#ifndef _HW_FLASH_H_
#define _HW_FLASH_H_

#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <media/v4l2-subdev.h>
#include <linux/pinctrl/consumer.h>
#include <linux/leds.h>
#include <linux/iommu.h>
#include <media/huawei/flash_cfg.h>
#include "hw_subdev.h"
#include "cam_log.h"
#include <dsm/dsm_pub.h>

#define CAMERA_FLASH_MAX	2
#define CAMERA_FLASH_ARRAY_SIZE	10

#define DEFINE_HISI_FLASH_MUTEX(name) \
	static struct mutex flash_mut_##name = __MUTEX_INITIALIZER(flash_mut_##name)

#define MAX_ATTRIBUTE_BUFFER_SIZE       128

#define LOW                             0
#define HIGH                            1


#define FLASH_LED_THERMAL_PROTECT_ENABLE		(1<<0)
#define FLASH_LED_LOWPOWER_PROTECT_ENABLE		(1<<1)

#ifdef CONFIG_LLT_TEST

struct UT_TEST_HW_FLASH
{
    ssize_t (*hw_flash_thermal_protect_show)(struct device *dev, struct device_attribute *attr,char *buf);

    ssize_t (*hw_flash_thermal_protect_store)(struct device *dev,struct device_attribute *attr, const char *buf, size_t count);

    ssize_t (*hw_flash_led_fault_show)(struct device *dev, struct device_attribute *attr, char *buf);

    ssize_t (*hw_flash_lowpower_protect_show)(struct device *dev,struct device_attribute *attr,char *buf);

    ssize_t (*hw_flash_lowpower_protect_store)(struct device *dev,struct device_attribute *attr, const char *buf, size_t count);

    int (*hw_flash_register_attribute)(struct hw_flash_ctrl_t *flash_ctrl, struct device *dev);

    long (*hw_flash_subdev_ioctl)(struct v4l2_subdev *sd,unsigned int cmd, void *arg);
};

extern struct UT_TEST_HW_FLASH UT_hw_flash;

extern unsigned int hw_flash_led_state_read(void);

extern void hw_flash_led_state_write(unsigned int x);

#endif /* CONFIG_LLT_TEST */
/********************** flash base data struct define **********************/


/********************** flash controler struct define **********************/

/* check flash led open or short */
typedef enum {
	FLASH_LED_NORMAL = 0,
	FLASH_LED_FAULT,
	FLASH_LED_UNSUPPORTED,
	FLASH_LED_ERROR
} flash_fault_t;

struct hw_flash_info {
	const char *name;
	flash_type type;
	int index;
	unsigned int slave_address;
};

struct hw_flash_state {
	int mode;
	int data;
};

struct hw_flash_ctrl_t;

struct hw_flash_fn_t {
	/* flash function table */
	int (*flash_config) (struct hw_flash_ctrl_t *, void *);
	int (*flash_on) (struct hw_flash_ctrl_t *, void *);
	int (*flash_off) (struct hw_flash_ctrl_t *);
	int (*flash_init) (struct hw_flash_ctrl_t *);
	int (*flash_exit) (struct hw_flash_ctrl_t *);
	int (*flash_match) (struct hw_flash_ctrl_t *);
	int (*flash_get_dt_data) (struct hw_flash_ctrl_t *);
	/* add check flash short & open*/
	int (*flash_check) (struct hw_flash_ctrl_t *);
	int (*flash_register_attribute)(struct hw_flash_ctrl_t *, struct device *);
};

struct hw_flash_i2c_client {
	struct hw_flash_i2c_fn_t *i2c_func_tbl;
	struct i2c_client *client;
};

struct hw_flash_i2c_fn_t {
	int (*i2c_read) (struct hw_flash_i2c_client *, u8, u8 *);
	int (*i2c_write) (struct hw_flash_i2c_client *, u8, u8);
};

struct hw_flash_ctrl_t {
	struct platform_device *pdev;
	struct mutex *hw_flash_mutex;
	struct device *dev;
	struct pinctrl *pctrl;
	struct hw_sd_subdev hw_sd;
	struct v4l2_subdev_ops *flash_v4l2_subdev_ops;
	struct hw_flash_fn_t *func_tbl;
	struct hw_flash_i2c_client *flash_i2c_client;
	struct hw_flash_info flash_info;
	struct hw_flash_state state;
	bool flash_mask_enable;
	struct led_classdev cdev_flash;
	struct led_classdev cdev_torch;
	void *pdata;
};





/***************extern function declare******************/
int32_t hw_flash_platform_probe(struct platform_device *pdev, void *data);
int32_t hw_flash_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id);
int hw_flash_config(struct hw_flash_ctrl_t *flash_ctrl, void *argp);
int hw_flash_get_dt_data(struct hw_flash_ctrl_t *flash_ctrl);

void hw_flash_enable_thermal_protect(void);
void hw_flash_disable_thermal_protect(void);

#endif
