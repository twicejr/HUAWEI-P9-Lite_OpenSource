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


#ifndef _VL53L0_LASER_H_
#define _VL53L0_LASER_H_
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
#include <linux/of_gpio.h>
#include <media/v4l2-subdev.h>
#include <media/huawei/laser_cfg.h>
#include "cam_log.h"
#include "hwcam_intf.h"

#define LOW                             0
#define HIGH                            1

typedef enum {
	XSHUT = 0,
	IOVDD,
	IO_MAX
} gpio_t;

/* laser controler struct define */
struct hw_laser_info {
	const char* product_name;
	const char* laser_name;
	unsigned int i2c_index;
	struct gpio laser_gpio[IO_MAX];
	int gpio_num;
	/* pin control config */
	struct pinctrl *pinctrl;
	struct pinctrl_state *pins_default;
	struct pinctrl_state *pins_idle;
};


typedef struct _tag_hw_vl53l0
{
	struct v4l2_subdev subdev;
	struct platform_device *pdev;
	struct hw_laser_info *laser_info;
	struct mutex lock;
} hw_vl53l0_t;

#endif

