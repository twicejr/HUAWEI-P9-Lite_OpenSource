/*
 *  Hisilicon K3 SOC camera driver source file
 *
 *  Copyright (C) Huawei Technology Co., Ltd.
 *
 * Author:
 * Email:
 * Date:	  2014-11-15
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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
#include <media/huawei/vcm_cfg.h>
#include "cam_log.h"
#include "hwcam_intf.h"
#include "../../cci/hw_cci.h"

typedef struct _tag_hw_vcm_vtbl hw_vcm_vtbl_t;
typedef struct _tag_hw_vcm_intf hw_vcm_intf_t;

/* vcm controler struct define */
struct hw_vcm_info {
	const char *vcm_name;
	unsigned int slave_address;
	int index;
	int data_type;
};

typedef struct _tag_hw_vcm_intf
{
	hw_vcm_vtbl_t *vtbl;
} hw_vcm_intf_t;


typedef struct _vcm_t {
	hw_vcm_intf_t intf;
	struct hw_vcm_info *vcm_info;
} vcm_t;

typedef struct _tag_hw_vcm
{
	struct v4l2_subdev subdev;
	struct platform_device *pdev;
	hw_vcm_intf_t *intf;
	struct hw_vcm_info *vcm_info;
	struct mutex lock;
} hw_vcm_t;

/* vcm function table */
struct _tag_hw_vcm_vtbl {
	int (*vcm_match_id) (hw_vcm_intf_t *, void *);
	int (*vcm_config) (hw_vcm_t *, void *);
	int (*vcm_i2c_read) (hw_vcm_intf_t *, void *);
	int (*vcm_i2c_write) (hw_vcm_intf_t *, void *);
	int (*vcm_ioctl) (hw_vcm_intf_t *, void *);
};

/* extern function declare */
extern int hw_vcm_register(struct platform_device *pdev,
		hw_vcm_intf_t *intf, struct hw_vcm_info *hw_vcm_info);
extern void hw_vcm_unregister(hw_vcm_intf_t *intf);
int hw_vcm_config(hw_vcm_t *hw_vcm, void *arg);
int hw_vcm_get_dt_data(struct platform_device *pdev, vcm_t *vcm);

#endif

