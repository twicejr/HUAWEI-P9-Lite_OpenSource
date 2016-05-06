/* Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
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

#ifndef _HISI_CAMERA_H_
#define _HISI_CAMERA_H_

#define V4L2_CTRL_CLASS_CAMERA 0x009a0000

/********************** v4l2 subdev ioctl case id define **********************/
#define V4L2_CID_MEM_INFO (V4L2_CID_PRIVACY + 80)
#define V4L2_CID_MMU_INFO (V4L2_CID_PRIVACY + 81)

int camera_init_v4l2(struct platform_device *dev);

#endif /*_HISI_CAMERA_H */