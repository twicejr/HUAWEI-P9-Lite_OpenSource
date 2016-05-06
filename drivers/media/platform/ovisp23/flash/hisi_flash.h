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


#ifndef _HISI_FLASH_H_
#define _HISI_FLASH_H_

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
#include "../hisi_subdev.h"
#include "../hisi_cam_module.h"

#define CAMERA_FLASH_MAX	2
#define CAMERA_FLASH_ARRAY_SIZE	10

#define DEFINE_HISI_FLASH_MUTEX(name) \
	static struct mutex flash_mut_##name = __MUTEX_INITIALIZER(flash_mut_##name)

#define MAX_ATTRIBUTE_BUFFER_SIZE       128

#define LOW                             0
#define HIGH                            1


#define FLASH_LED_THERMAL_PROTECT_ENABLE		(1<<0)
#define FLASH_LED_LOWPOWER_PROTECT_ENABLE		(1<<1)

/********************** v4l2 subdev ioctl case id define **********************/
struct flash_cfg_data;

#define VIDIOC_HISI_FLASH_CFG	\
	_IOWR('V', BASE_VIDIOC_PRIVATE + 41, struct flash_cfg_data)




/***************************** cfg type define *******************************/
#define CFG_FLASH_TURN_ON		0
#define CFG_FLASH_TURN_OFF		1
#define CFG_FLASH_GET_FLASH_NAME	2
#define CFG_FLASH_GET_FLASH_STATE	3

#define CFG_FLASH_SET_CFG		21


/********************** flash base data struct define **********************/


/********************** flash controler struct define **********************/
typedef enum {
	STANDBY_MODE=0,
	FLASH_MODE,
	TORCH_MODE,
	TORCH_LEFT_MODE,
	TORCH_RIGHT_MODE,
	MAX_MODE,
} flash_mode;

typedef enum {
	LED_FLASH = 0,
	XEON_FLASH,
} flash_type;

struct hisi_flash_info {
	const char *name;
	flash_type type;
	int index;
	unsigned int slave_address;
};

struct hisi_flash_state {
	int mode;
	int data;
};

struct hisi_flash_ctrl_t;

struct hisi_flash_fn_t {
	/* flash function table */
	int (*flash_config) (struct hisi_flash_ctrl_t *, void *);
	int (*flash_on) (struct hisi_flash_ctrl_t *, void *);
	int (*flash_off) (struct hisi_flash_ctrl_t *);
	int (*flash_init) (struct hisi_flash_ctrl_t *);
	int (*flash_exit) (struct hisi_flash_ctrl_t *);
	int (*flash_match) (struct hisi_flash_ctrl_t *);
	int (*flash_get_dt_data) (struct hisi_flash_ctrl_t *);
	int (*flash_register_attribute)(struct hisi_flash_ctrl_t *, struct device *);
};

struct hisi_flash_i2c_client {
	struct hisi_flash_i2c_fn_t *i2c_func_tbl;
	struct i2c_client *client;
};

struct hisi_flash_i2c_fn_t {
	int (*i2c_read) (struct hisi_flash_i2c_client *, u8, u8 *);
	int (*i2c_write) (struct hisi_flash_i2c_client *, u8, u8);
};

struct hisi_flash_ctrl_t {
	struct platform_device *pdev;
	struct mutex *hisi_flash_mutex;
	struct device *dev;
	struct pinctrl *pctrl;
	struct hisi_sd_subdev hisi_sd;
	struct v4l2_subdev_ops *flash_v4l2_subdev_ops;
	struct hisi_flash_fn_t *func_tbl;
	struct hisi_flash_i2c_client *flash_i2c_client;
	struct hisi_flash_info flash_info;
	struct hisi_flash_state state;
	bool flash_mask_enable;
	struct led_classdev cdev_flash;
	struct led_classdev cdev_torch;
	void *pdata;
};

/********************* cfg data define ************************************/

struct flash_i2c_reg {
	unsigned int address;
	unsigned int value;
};

struct flash_cfg_data {
	int cfgtype;
	flash_mode mode;
	int data;

	union {
	char name[32];
	} cfg;
};



/***************extern function declare******************/
int32_t hisi_flash_platform_probe(struct platform_device *pdev, void *data);
int32_t hisi_flash_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id);
int hisi_flash_config(struct hisi_flash_ctrl_t *flash_ctrl, void *argp);
int hisi_flash_get_dt_data(struct hisi_flash_ctrl_t *flash_ctrl);

void hisi_flash_enable_thermal_protect(void);
void hisi_flash_disable_thermal_protect(void);

#endif