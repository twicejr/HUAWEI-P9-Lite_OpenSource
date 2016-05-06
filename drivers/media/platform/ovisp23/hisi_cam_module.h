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

#ifndef _HISI_CAMERA_MODULE_H_
#define _HISI_CAMERA_MODULE_H_

#include <linux/types.h>
#include <linux/version.h>
#include <linux/wakelock.h>
#include <linux/iommu.h>
#include <linux/uaccess.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <media/v4l2-dev.h>
#include <media/v4l2-ioctl.h>
#include <media/v4l2-device.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-event.h>
#include <media/v4l2-mediabus.h>
#include "hisi_subdev.h"
#include "cam_log.h"

#define SEATTLE_FPGA

struct hisi_video_device {
	struct video_device *vdev;
	atomic_t opened;
};

int hisi_sd_register(struct hisi_sd_subdev *hisi_subdev);
int hisi_sd_unregister(struct hisi_sd_subdev *hisi_subdev);
int is_fpga_board(void);
void camdrv_msleep(unsigned int ms);

#endif /*_HISI_CAMERA_MODULE_H_ */