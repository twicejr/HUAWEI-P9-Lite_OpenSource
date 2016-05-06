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


#ifndef _HISI_ISP_H_
#define _HISI_ISP_H_

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


#define DEFINE_HISI_MUTEX(mutexname) \
	static struct mutex mutexname = __MUTEX_INITIALIZER(mutexname)


/********************** v4l2 subdev ioctl case id define **********************/
struct isp_cfg_data;

#define VIDIOC_HISI_ISP_CFG _IOWR('V', BASE_VIDIOC_PRIVATE + 21, struct isp_cfg_data)



/********************** define cfg type ********************************/

#define CFG_ISP_POWER_UP	0
#define CFG_ISP_POWER_DOWN	1


/********************** isp controler struct define **********************/
struct isp_reg_t {
	unsigned int address;
	unsigned int value;
};
struct isp_cfg_data {
	int cfgtype;
	int mode;
	int data;
	union {
	struct isp_reg_t reg;
	} cfg;
};

struct hisi_isp_ctrl_t {
	struct platform_device *pdev;
	struct mutex *hisi_isp_mutex;
	//struct device *dev;
	struct hisi_sd_subdev hisi_sd;
	struct v4l2_subdev_ops *isp_v4l2_subdev_ops;
	struct hisi_isp_fn_t *func_tbl;
};


struct hisi_isp_fn_t {
	int (*isp_config) (struct hisi_isp_ctrl_t *isp_ctrl , void *arg);
	int (*isp_power_down) (struct hisi_isp_ctrl_t *isp_ctrl);
	int (*isp_power_up) (struct hisi_isp_ctrl_t *isp_ctrl );
};

#endif