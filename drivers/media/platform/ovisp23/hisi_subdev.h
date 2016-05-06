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


#ifndef _HISI_SUBDEV_H_
#define _HISI_SUBDEV_H_

#include <media/v4l2-subdev.h>

#define CAMERA_DEVICE_GROUP_ID		1
#define CAMERA_VNODE_GROUP_ID		2
#define HISI_CAMERA_NAME		"hisi_camera"
#define HISI_CONFIGURATION_NAME		"hisi_config"

#define HISI_CAMERA_SUBDEV_SENSOR0	0
#define HISI_CAMERA_SUBDEV_SENSOR1	1
#define HISI_CAMERA_SUBDEV_ISP		2
#define HISI_CAMERA_SUBDEV_VCM0		3
#define HISI_CAMERA_SUBDEV_VCM1		4
#define HISI_CAMERA_SUBDEV_FLASH0   	5
#define HISI_CAMERA_SUBDEV_FLASH1   	6

#define DEV_NAME_SIZE			32

struct hisi_sd_subdev {
	struct v4l2_subdev sd;
	int close_seq;
};

struct hisi_sd_req_sd {
	char *name;
	struct v4l2_subdev *subdev;
};


#define HISI_SD_NOTIFY_GET_SD 0x00000001
#define HISI_SD_NOTIFY_PUT_SD 0x00000002


int hisi_sd_register(struct hisi_sd_subdev *hisi_subdev);
int hisi_sd_unregister(struct hisi_sd_subdev *sd);
struct v4l2_subdev *hisi_sd_get_subdev(struct v4l2_subdev *sd,
					const char *get_name);
void hisi_sd_put_subdev(struct v4l2_subdev *sd, struct v4l2_subdev *put);



#endif /* _HISI_SD_H_ */
