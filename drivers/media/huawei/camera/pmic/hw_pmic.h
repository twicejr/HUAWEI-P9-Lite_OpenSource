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


#ifndef _HISI_PMIC_H_
#define _HISI_PMIC_H_

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


#define DEFINE_HISI_PMIC_MUTEX(name) \
	static struct mutex pmic_mut_##name = __MUTEX_INITIALIZER(pmic_mut_##name)

/********************** v4l2 subdev ioctl case id define **********************/
struct pmic_cfg_data;

/***************************** cfg type define *******************************/
#define CFG_PMIC_INIT			0
#define CFG_PMIC_POWER_ON		1
#define CFG_PMIC_POWER_OFF		2
#define BUCK_REG_MAX			90
#define LDO_REG_MAX			66

/********************** pmic base data struct define **********************/

typedef enum 
{	VOUT_LDO_1 = 0,	
	VOUT_LDO_2,
	VOUT_LDO_3,
	VOUT_LDO_4,
	VOUT_LDO_5,
	VOUT_BUCK_1,
	VOUT_BUCK_2,
	VOUT_MAX,
} pmic_seq_index_t;

/********************** pmic controler struct define **********************/
struct hisi_pmic_info {
	const char *name;
	int index;
	unsigned int slave_address;
};

struct hisi_pmic_ctrl_t;

struct hisi_pmic_fn_t {
	/* pmic function table */
	int (*pmic_config) (struct hisi_pmic_ctrl_t *, void *);
	int (*pmic_on) (struct hisi_pmic_ctrl_t *, void *);
	int (*pmic_off) (struct hisi_pmic_ctrl_t *);
	int (*pmic_init) (struct hisi_pmic_ctrl_t *);
	int (*pmic_exit) (struct hisi_pmic_ctrl_t *);
	int (*pmic_match) (struct hisi_pmic_ctrl_t *);
	int (*pmic_get_dt_data) (struct hisi_pmic_ctrl_t *);
	int (*pmic_seq_config)(struct hisi_pmic_ctrl_t *, pmic_seq_index_t, u32, int);
	int (*pmic_register_attribute)(struct hisi_pmic_ctrl_t *, struct device *);
};

struct hisi_pmic_i2c_client {
	struct hisi_pmic_i2c_fn_t *i2c_func_tbl;
	struct i2c_client *client;
};

struct hisi_pmic_i2c_fn_t {
	int (*i2c_read) (struct hisi_pmic_i2c_client *, u8, u8 *);
	int (*i2c_write) (struct hisi_pmic_i2c_client *, u8, u8);
};

struct hisi_pmic_ctrl_t {
	struct platform_device *pdev;
	struct mutex *hisi_pmic_mutex;
	struct device *dev;
	struct pinctrl *pctrl;
	struct v4l2_subdev subdev;
	struct v4l2_subdev_ops *pmic_v4l2_subdev_ops;
	struct hisi_pmic_fn_t *func_tbl;
	struct hisi_pmic_i2c_client *pmic_i2c_client;
	struct hisi_pmic_info pmic_info;
	void *pdata;
};

/********************* cfg data define ************************************/

struct pmic_i2c_reg {
	unsigned int address;
	unsigned int value;
};

struct pmic_cfg_data {
	int cfgtype;
	int mode;
	int data;

	union {
	char name[32];
	} cfg;
};

/***************extern function declare******************/
int32_t hisi_pmic_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id);
int hisi_pmic_config(struct hisi_pmic_ctrl_t *pmic_ctrl, void *argp);
int hisi_pmic_get_dt_data(struct hisi_pmic_ctrl_t *pmic_ctrl);
struct hisi_pmic_ctrl_t * hisi_get_pmic_ctrl(void);
#endif
