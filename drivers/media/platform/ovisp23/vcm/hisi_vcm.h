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


#ifndef _HISI_VCM_H_
#define _HISI_VCM_H_

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
#include "../hisi_subdev.h"
#include "../hisi_cam_module.h"
#include "../cci/hisi_cci.h"
#include "../sensor/hisi_sensor.h"

#define CAMERA_VCM_MAX	2
#define CAMERA_VCM_ARRAY_SIZE	10

#define DEFINE_HISI_VCM_MUTEX(id) \
	static struct mutex vcm_mut_##id = __MUTEX_INITIALIZER(vcm_mut_##id)

#define DEFINE_HISI_VCM_CTRL(id)	\
	DEFINE_HISI_VCM_MUTEX(id);	\
	static struct hisi_vcm_ctrl_t hisi_vcm_ctrl_##id = {	\
		.index = id,	\
		.hisi_vcm_mutex = &vcm_mut_##id,	\
		.vcm_array = vcm_array[id],	\
	};


/********************** v4l2 subdev ioctl case id define **********************/
struct vcm_cfg_data;

#define VIDIOC_HISI_VCM_CFG	\
	_IOWR('V', BASE_VIDIOC_PRIVATE + 31, struct vcm_cfg_data)


/***************************** cfg type define *******************************/
#define CFG_VCM_I2C_READ	0
#define CFG_VCM_I2C_WRITE	1
#define CFG_VCM_GET_VCM_NAME	2


#define CFG_VCM_SET_CFG	21
#define CFG_VCM_GET_OTP_AF	22


/********************** vcm base data struct define **********************/


/********************** vcm controler struct define **********************/

struct hisi_vcm_info {
	const char *name;   /* vcm name */
	unsigned int slave_address;
	int index;
	int data_type;
};

struct hisi_vcm_ctrl_t;

struct hisi_vcm_fn_t {
	/* vcm function table */
	int (*vcm_match_id)(struct hisi_vcm_ctrl_t *);
	int (*vcm_config) (struct hisi_vcm_ctrl_t *, void *);
	int (*vcm_i2c_read) (struct hisi_vcm_ctrl_t *, void *);
	int (*vcm_i2c_write) (struct hisi_vcm_ctrl_t *, void *);
	int (*vcm_ioctl) (struct hisi_vcm_ctrl_t *, void *);
};

struct hisi_vcm_t {
	struct hisi_vcm_fn_t *func_tbl;
	struct hisi_vcm_info *vcm_info;
};

struct hisi_vcm_ctrl_t {
	int index;
	struct platform_device *pdev;
	struct mutex *hisi_vcm_mutex;
	struct device *dev;
	struct hisi_sd_subdev hisi_sd;
	struct v4l2_subdev_ops *vcm_v4l2_subdev_ops;
	struct hisi_vcm_t *vcm;
	struct hisi_vcm_t **vcm_array;
};

/********************* cfg data define ************************************/

struct vcm_i2c_reg {
	unsigned short address;
	unsigned short value;
};

struct vcm_cfg_data {
	int cfgtype;
	int mode;
	int data;

	union {
		char name[32];
		struct vcm_i2c_reg reg;
		struct hisi_sensor_af_otp af_otp;
	} cfg;
};

/***************extern function declare******************/

int hisi_vcm_add(struct hisi_vcm_t *vcm);
void hisi_vcm_del(struct hisi_vcm_t *vcm);
int hisi_vcm_config(struct hisi_vcm_ctrl_t *s_ctrl, void *argp);
int hisi_vcm_get_dt_data(struct platform_device *pdev, struct hisi_vcm_t *vcm);

#endif