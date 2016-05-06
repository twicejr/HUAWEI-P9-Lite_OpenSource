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


#ifndef __HW_KERNEL_HWCAM_VCM_CFG_H__
#define __HW_KERNEL_HWCAM_VCM_CFG_H__

#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <media/huawei/camera.h>

/* cfg type define */
#define CFG_VCM_I2C_READ	0
#define CFG_VCM_I2C_WRITE	1
#define CFG_VCM_GET_VCM_NAME	2
#define CFG_VCM_SET_VCM_CODE	3

#define CFG_VCM_SET_CFG	21
#define CFG_VCM_GET_OTP_AF	22

#define MAX_VCM_NAME_LEN	32

typedef enum
{
	DW9714 = 0,
	AD5816,
	AD5823,
	VCMMAX,
}vcm_type;

struct HwVcmInfo{
	const char name[MAX_VCM_NAME_LEN];
	vcm_type type;
};

/* cfg data define */
struct vcm_i2c_reg {
	uint16_t address;
	uint16_t value;
};

struct vcm_otp {
	uint32_t start_code;
	uint32_t end_code;
};

struct hw_vcm_cfg_data {
	int cfgtype;
	int mode;
	int data;

	union {
		char name[MAX_VCM_NAME_LEN];
		struct vcm_i2c_reg reg;
		struct vcm_otp af_otp;
	} cfg;
};

/* v4l2 subdev ioctl case id define */
#define VIDIOC_HISI_VCM_CFG	_IOWR('V', BASE_VIDIOC_PRIVATE + 31, struct hw_vcm_cfg_data)

#endif

