/*
 *  ov5642 camera driver source file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *	Author :
 *  Version:  1.2
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

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/ctype.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/clk.h>
#include <linux/videodev2.h>
#include <linux/time.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/fb.h>
#include <linux/fs.h>
#include <linux/io.h>
#include <linux/unistd.h>
#include <linux/uaccess.h>
#include <asm/div64.h>
#include <mach/hisi_mem.h>
#include "mach/hardware.h"
#include "mach/gpio.h"
#include "../isp/sensor_common.h"
#include "ov5642.h"
/*#include "../isp/k3_isp_io.h"*/
#include <asm/bug.h>
#include <linux/device.h>

#define LOG_TAG "OV5642"
/* #define DEBUG_DEBUG 1 */
#include "../isp/cam_log.h"

#define OV5642_SLAVE_ADDRESS 0x78
#define OV5642_CHIP_ID       (0x5642)

#define OV5642_CAM_MODULE_SKIPFRAME     4

#define OV5642_HFLIP    0
#define OV5642_VFLIP    0

#define OV5642_NO_FLIP  0x00
#define OV5642_H_FLIP   0x01
#define OV5642_V_FLIP   0x02
#define OV5642_HV_FLIP  0x03

#define OV5642_EXPOSURE_REG_H	0x3501
#define OV5642_EXPOSURE_REG_L	0x3502
#define OV5642_EXPOSURE_REG_0		0x3500
#define OV5642_EXPOSURE_REG_1		0x3501
#define OV5642_EXPOSURE_REG_2		0x3502
#define OV5642_GAIN_REG_H		0x350a
#define OV5642_GAIN_REG_L		0x350b

#define OV5642_HTS_REG_H		0x380c
#define OV5642_HTS_REG_L		0x380d
#define OV5642_VTS_REG_H		0x380e
#define OV5642_VTS_REG_L		0x380f
const struct isp_reg_t isp_mipi_init_regs_ov5642[] = {
	{0x1c138, 0x02},
	{0x1c13d, 0x00},
	{0x1c13e, 0x00},
	{0x1c144, 0x88},
	{0x1c145, 0x00},
	{0x1c150, 0x00},
	{0x1c151, 0x7f},
	{0x1c152, 0x00},
	{0x1c153, 0x7f},
	{0x1c154, 0x00},
	{0x1c155, 0x10},
	{0x1c156, 0x00},
	{0x1c157, 0x10},
	{0x1c158, 0x7c},
	{0x1c159, 0x00},
	{0x1c15a, 0x7c},
	{0x1c15b, 0x00},
	{0x1c15c, 0x00},
	{0x1c15d, 0x10},
	{0x1c15e, 0x00},
	{0x1c15f, 0x10},
	{0x1c176, 0x03},
	{0x1c177, 0x48},
	{0x1c470, 0x01},
	{0x1c471, 0x00},
	{0x1c52a, 0x09},
	{0x1c52b, 0x09},
	{0x1c52c, 0x35},
	{0x1c52d, 0x01},
	{0x1c52e, 0x35},
	{0x1c52f, 0x02},
	{0x1c530, 0x00},
	{0x1c531, 0x00},
	{0x1c532, 0x00},
	{0x1c533, 0x00},
	{0x1c534, 0x00},
	{0x1c535, 0x00},
	{0x1c536, 0x00},
	{0x1c537, 0x00},
	{0x1c538, 0x35},
	{0x1c539, 0x0a},
	{0x1c53a, 0x35},
	{0x1c53b, 0x0b},
	{0x1c53c, 0x00},
	{0x1c53d, 0x00},
	{0x1c53e, 0x00},
	{0x1c53f, 0x00},
	{0x1c540, 0x00},
	{0x1c541, 0x00},
	{0x1c542, 0x00},
	{0x1c543, 0x00},
	{0x1c544, 0x00},
	{0x1c545, 0x00},
	{0x1c546, 0x00},
	{0x1c547, 0x00},
	{0x1c548, 0x00},
	{0x1c549, 0x00},
	{0x1c54a, 0x00},
	{0x1c54b, 0x00},
	{0x1c54c, 0x00},
	{0x1c54d, 0x00},
	{0x1c54e, 0x00},
	{0x1c54f, 0x00},
	{0x1c550, 0x00},
	{0x1c551, 0x00},
	{0x1c552, 0x00},
	{0x1c553, 0x00},
	{0x1c554, 0x00},
	{0x1c555, 0x00},
	{0x1c556, 0x00},
	{0x1c557, 0x00},
	{0x1c558, 0x00},
	{0x1c559, 0x00},
	{0x1c55a, 0x00},
	{0x1c55b, 0x00},
	{0x1c55c, 0xff},
	{0x1c55d, 0xff},
	{0x1c55e, 0x00},
	{0x1c55f, 0x00},
	{0x1c560, 0x00},
	{0x1c561, 0x00},
	{0x1c562, 0xff},
	{0x1c563, 0xff},
	{0x1c564, 0x00},
	{0x1c565, 0x00},
	{0x1c566, 0x00},
	{0x1c567, 0x00},
	{0x1c568, 0x00},
	{0x1c569, 0x00},
	{0x1c56a, 0x00},
	{0x1c56b, 0x00},
	{0x1c56c, 0x00},
	{0x1c56d, 0x00},
	{0x1c56e, 0x00},
	{0x1c56f, 0x00},
	{0x1c570, 0x00},
	{0x1c571, 0x00},
	{0x1c572, 0x00},
	{0x1c573, 0x00},

};

const struct isp_reg_t isp_dvp_init_regs_ov5642[] = {
	/* cclk0 cclk2 enable */
	{0x63023, 0x22},

// for bg white phone
// add new US settings
/* system initial */	
	{0x1c174, 0x01},//y36721 set it as manual aec/agc at first.
	{0x1c139, 0x01},//AECAGC function write sensor enable
	{0x1c179, 0x00},//not hdr sensor
	{0x1c528, 0x20},//pSensorDeviceID[0]
	{0x1c529, 0x20},
	{0x1c52a, 0x09},//pSensorI2COption[0]
	{0x1c52b, 0x09},
	{0x1c52c, 0x35},
	{0x1c52d, 0x00},
	{0x1c52e, 0x35},
	{0x1c52f, 0x01},
	{0x1c530, 0x35},
	{0x1c531, 0x02},
	{0x1c532, 0x00},
	{0x1c533, 0x00},
	{0x1c534, 0x00},
	{0x1c535, 0x00},
	{0x1c536, 0x00},
	{0x1c537, 0x00},
	{0x1c538, 0x35},
	{0x1c539, 0x0a},
	{0x1c53a, 0x35},
	{0x1c53b, 0x0b},
	{0x1c53c, 0x00},
	{0x1c53d, 0x00},
	{0x1c53e, 0x00},
	{0x1c53f, 0x00},
	{0x1c540, 0x00},
	{0x1c541, 0x00},
	{0x1c542, 0x00},
	{0x1c543, 0x00},
	{0x1c55c, 0xff},
	{0x1c55d, 0xff},
	{0x1c55e, 0xff},
	{0x1c55f, 0x00},
	{0x1c560, 0x00},
	{0x1c561, 0x00},
	{0x1c562, 0xff},
	{0x1c563, 0xff},
	{0x1c564, 0x00},
	{0x1c565, 0x00},
	{0x1c566, 0x00},
	{0x1c567, 0x00},	

	/* ISP input size */
	{0x65010, 0x05},
	{0x65011, 0x10},
	{0x65012, 0x03},
	{0x65013, 0xcc},

	/* AE AGC */
	{0x1c150, 0x00},
	{0x1c151, 0x7f},
	{0x1c152, 0x00},
	{0x1c153, 0x7f},
	{0x1c154, 0x00},
	{0x1c155, 0x10},
	{0x1c156, 0x00},
	{0x1c157, 0x10},
	{0x1c158, 0x7c},
	{0x1c159, 0x00},
	{0x1c15a, 0x7c},
	{0x1c15b, 0x00},
	{0x1c15c, 0x00},
	{0x1c15d, 0x10},
	{0x1c15e, 0x00},
	{0x1c15f, 0x10},
};

/*should be calibrated, three lights, from 0x1c264*/
/*here is long exposure*/
char ov5642_lensc_param[86 * 3] = {
	/*first 86 is for daylight */
	0x30, 0x1a, 0x12, 0x9, 0xa, 0x25, 0x11, 0xb,
	0x8, 0x5, 0x4, 0x6, 0xc, 0x7, 0x2, 0x0,
	0x1, 0x4, 0x13, 0x7, 0x1, 0x0, 0x3, 0x5,
	0x20, 0xd, 0x7, 0x5, 0x6, 0xa, 0x3f, 0x23,
	0x11, 0xe, 0x16, 0x30, 0x1e, 0x1e, 0x1e, 0x1e,
	0x1d, 0x20, 0x20, 0x1f, 0x1f, 0x1f, 0x20, 0x20,
	0x21, 0x20, 0x1e, 0x20, 0x20, 0x20, 0x1f, 0x1e,
	0x1d, 0x1e, 0x1e, 0x1e, 0x1d, 0x2d, 0x29, 0x29,
	0x28, 0x29, 0x25, 0x24, 0x22, 0x23, 0x26, 0x26,
	0x21, 0x1e, 0x20, 0x24, 0x26, 0x24, 0x22, 0x23,
	0x25, 0x2e, 0x2a, 0x28, 0x28, 0x27,

	/*second 86 is for CWF light */
	0x23, 0x9, 0x2, 0x2, 0xa, 0x27, 0xb, 0x4,
	0x2, 0x3, 0x5, 0xa, 0x8, 0x4, 0x0, 0x0,
	0x3, 0x8, 0xe, 0x7, 0x1, 0x1, 0x6, 0x9,
	0x18, 0xc, 0xa, 0x9, 0xa, 0x11, 0x3f, 0x25,
	0x17, 0x15, 0x1f, 0x3f, 0x20, 0x1f, 0x1f, 0x1f,
	0x1d, 0x21, 0x20, 0x20, 0x1f, 0x1f, 0x20, 0x20,
	0x20, 0x1f, 0x1d, 0x21, 0x20, 0x1f, 0x1e, 0x1e,
	0x1f, 0x1e, 0x1d, 0x1e, 0x1b, 0x26, 0x26, 0x25,
	0x25, 0x25, 0x23, 0x22, 0x20, 0x21, 0x24, 0x23,
	0x20, 0x20, 0x20, 0x21, 0x24, 0x22, 0x20, 0x21,
	0x24, 0x27, 0x27, 0x26, 0x26, 0x23,

	/*last 86 is for A light */
	0x3f, 0x3a, 0x1f, 0x21, 0x1f, 0x3f, 0x2d, 0x1c,
	0x11, 0x7, 0x0, 0x3f, 0x1e, 0x13, 0x6, 0x5,
	0x6, 0x3f, 0x1c, 0x11, 0x6, 0x0, 0x0, 0x37,
	0x2a, 0x17, 0xf, 0x5, 0x0, 0x3f, 0x3f, 0x3d,
	0x20, 0x24, 0x31, 0x3f, 0x1a, 0x1c, 0x1b, 0x1e,
	0x11, 0x1e, 0x1f, 0x21, 0x21, 0x15, 0x1d, 0x20,
	0x20, 0x20, 0x18, 0x1e, 0x1e, 0x20, 0x21, 0x17,
	0x13, 0x1e, 0x1e, 0x1d, 0x18, 0x2d, 0x29, 0x2b,
	0x27, 0x2c, 0x27, 0x24, 0x20, 0x22, 0x28, 0x29,
	0x1f, 0x19, 0x1d, 0x28, 0x27, 0x25, 0x21, 0x23,
	0x28, 0x2c, 0x29, 0x2a, 0x29, 0x29,
};

/*should be calibrated, 6 groups 3x3, from 0x1c1d8*/
short ov5642_ccm_param[54] = {
	/*center 3x3 color matrix for long exposure */
	0x017E, 0xFF73, 0x000F,
	0xFFBE, 0x0195, 0xFFAD,
	0xFFB6, 0xFF72, 0x01D8,

	/*center 3x3 color matrix for short exposure */
	0x017E, 0xFF73, 0x000F,
	0xFFBE, 0x0195, 0xFFAD,
	0xFFB6, 0xFF72, 0x01D8,

	/*left 3x3 color matrix for long exposure */
	0x0015, 0xFFF1, 0xFFFA,
	0xFFF3, 0x0016, 0xFFF7,
	0xFFF0, 0x001A, 0xFFF6,

	/*left 3x3 color matrix for short exposure */
	0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000,

	/*right 3x3 color matrix for long exposure */
	0xFFF6, 0x0014, 0xFFF6,
	0x0009, 0xFFEB, 0x000C,
	0x002C, 0xFFEE, 0xFFE6,

	/*right 3x3 color matrix for short exposure */
	0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000,
};

char ov5642_awb_param[] = {
	/*
	 * 0x66206-0x66212, awb control, 11 regs
	 */
	0x10, 0x10, 0x10, 0x6a, 0x61, 0xd4, 0xda, 0x3c, 0x1b, 0x5a, 0x49,

	/*
	 * 0x1c1c8~1c1d7 are CT thresholds, current CT value is compared with
	 * these thresholds to decide to apply which group color matrix
	 * long: 3 16bit, 0x1c1c8-0x1c1c9, 0x1c1cc-0x1c1cd, 0x1c1d0-0x1c1d1
	 */
	0x1, 0x18, 0x0, 0xa1, 0x2, 0xc0,

	/*
	 * 0x1c254~1c263 are CT thresholds, current CT value is compared with
	 * these thresholds to decide to apply which group lens correction matrix
	 * long: 4 16bit, 0x1c254-0x1c25b
	 */
	0x0, 0xc8, 0x0, 0xef, 0x1, 0xa5, 0x2, 0x32,
};

/*y36721 todo*/
char ov5642_awb_param_short[] = {

};

static framesize_s ov5642_framesizes[] = {
	/* quarter 5M
	{1296, 972, 1600, 1000},*/
	//{0, 120, 1280, 720, 1604, 1101, 30, 30, 0, 0, 0x100, VIEW_FULL, RESOLUTION_16_9, {ov5642_framesize_full, ARRAY_SIZE(ov5642_framesize_full)} },
    //{0, 0, 1280, 960, 1604, 1101, 30, 30, 0, 0, 0x100, VIEW_FULL, RESOLUTION_4_3, {ov5642_framesize_full, ARRAY_SIZE(ov5642_framesize_full)} },
    {0, 0, 1280, 960, 3200, 3000, 10, 10, 0, 0, 0x100, VIEW_FULL, RESOLUTION_4_3, false, false, {ov5642_1296x972, ARRAY_SIZE(ov5642_1296x972)}},
	//{0, 0, 2592, 1944, 3200, 2000, 30, 30, 0, 0, 0x100, VIEW_FULL, RESOLUTION_4_3, false, {ov5642_framesize_full, ARRAY_SIZE(ov5642_framesize_full)} },
	/* full 5M
	{2592, 1944, 3200, 2000},*/
};

static camera_sensor ov5642_sensor;

static void ov5642_set_default(void);

/*
 **************************************************************************
 * FunctionName: ov5642_read_reg;
 * Description : read ov5642 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5642_read_reg(u16 reg, u8 *val)
{
	return k3_ispio_read_reg(ov5642_sensor.i2c_config.index, ov5642_sensor.i2c_config.addr,
		reg, val,ov5642_sensor.i2c_config.val_bits, ov5642_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov5642_write_reg;
 * Description : write ov5642 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5642_write_reg(u16 reg, u8 val, u8 mask)
{
	return k3_ispio_write_reg(ov5642_sensor.i2c_config.index, ov5642_sensor.i2c_config.addr,
		 reg, val, ov5642_sensor.i2c_config.val_bits,mask, ov5642_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov5642_write_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ov5642_write_seq(const struct _sensor_reg_t *seq, u32 size, u8 mask)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	return k3_ispio_write_seq(ov5642_sensor.i2c_config.index, ov5642_sensor.i2c_config.addr,
		seq, size,  ov5642_sensor.i2c_config.val_bits, mask, ov5642_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov5642_write_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ov5642_write_isp_seq(const struct isp_reg_t *seq, u32 size)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	k3_ispio_write_isp_seq(seq, size);
}

/*
 **************************************************************************
 * FunctionName: ov5642_enum_frame_intervals;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5642_enum_frame_intervals(struct v4l2_frmivalenum *fi)
{
	WARN_ON(fi == NULL);
	print_debug("enter %s", __func__);
	if (fi->index >= CAMERA_MAX_FRAMERATE) {
		return -EINVAL;
	}

	fi->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fi->discrete.numerator = 1;
	fi->discrete.denominator = (fi->index + 1);
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5642_get_format;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5642_get_format(struct v4l2_fmtdesc *fmt)
{
	if (fmt->type == V4L2_BUF_TYPE_VIDEO_OVERLAY)
		fmt->pixelformat = ov5642_sensor.fmt[STATE_PREVIEW];
	else
		fmt->pixelformat = ov5642_sensor.fmt[STATE_CAPTURE];
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5642_enum_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5642_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 max_index = ARRAY_SIZE(camera_framesizes) - 1;
	u32 this_max_index = ARRAY_SIZE(ov5642_framesizes) - 1;

	WARN_ON(framesizes == NULL);
	print_debug("enter %s; ", __func__);

	if (framesizes->index > max_index) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	if ((camera_framesizes[framesizes->index].width > ov5642_framesizes[this_max_index].width)
		|| (camera_framesizes[framesizes->index].height > ov5642_framesizes[this_max_index].height)) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	framesizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	framesizes->discrete.width = ov5642_framesizes[this_max_index].width;
	framesizes->discrete.height = ov5642_framesizes[this_max_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5642_try_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5642_try_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	int max_index = ARRAY_SIZE(ov5642_framesizes) - 1;

	WARN_ON(framesizes == NULL);
	print_debug("Enter Function:%s  ", __func__);

	if (framesizes->discrete.width <= ov5642_framesizes[max_index].width
	    && framesizes->discrete.height <= ov5642_framesizes[max_index].height) {
		print_debug("===========width = %d", framesizes->discrete.width);
		print_debug("===========height = %d", framesizes->discrete.height);
		return 0;
	}

	print_error("frame size too large, [%d,%d]",
		    framesizes->discrete.width, framesizes->discrete.height);
	return -EINVAL;
}

/*
 **************************************************************************
 * FunctionName: ov5642_set_framesizes;
 * Description : NA;
 * Input       : flag: if 1, set framesize to sensor,
 *					   if 0, only store framesize to camera_interface;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5642_set_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type)
{
	int i = 0;
	WARN_ON(fs == NULL);

	print_debug("Enter Function:%s State(%d), flag=%d, width=%d, height=%d",
		    __func__, state, flag, fs->width, fs->height);

	for (i = 0; i < ARRAY_SIZE(ov5642_framesizes); i++) {
		if ((ov5642_framesizes[i].width >= fs->width)
		    && (ov5642_framesizes[i].height >= fs->height)) {
			fs->width = ov5642_framesizes[i].width;
			fs->height = ov5642_framesizes[i].height;
			break;
		}
	}
	if (i >= ARRAY_SIZE(ov5642_framesizes)) {
		print_error("request resolution larger than sensor's max resolution");
		return -EINVAL;
	}

	if (state == STATE_PREVIEW)
		ov5642_sensor.preview_frmsize_index = i;
	else
		ov5642_sensor.capture_frmsize_index = i;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5642_get_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5642_get_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs)
{
	int frmsize_index;
	WARN_ON(fs == NULL);

	if (state == STATE_PREVIEW)
		frmsize_index = ov5642_sensor.preview_frmsize_index;
	else if (state == STATE_CAPTURE)
		frmsize_index = ov5642_sensor.capture_frmsize_index;
	else
		return -EINVAL;
	fs->width = ov5642_framesizes[frmsize_index].width;
	fs->height = ov5642_framesizes[frmsize_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5642_init_reg;
 * Description : download initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5642_init_reg(void)
{
	int size = 0;
	print_debug("Enter Function:%s  , initsize=%d",
		    __func__, sizeof(ov5642_init_regs));

	if (ov5642_sensor.interface_type != DVP) {
		size = ARRAY_SIZE(isp_mipi_init_regs_ov5642);
		ov5642_write_isp_seq(isp_mipi_init_regs_ov5642, size);
	} else {
		size = ARRAY_SIZE(isp_dvp_init_regs_ov5642);
		ov5642_write_isp_seq(isp_dvp_init_regs_ov5642, size);
	}

	size = ARRAY_SIZE(ov5642_quarter_raw8);
	if (0 != ov5642_write_seq(ov5642_quarter_raw8, size, 0x00)) {
		print_error("fail to init ov5642 sensor");
		return -ETIME;
	}

	return 0;
}
static int ov5642_set_hflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);
	ov5642_sensor.hflip = flip;
	return 0;
}
static int ov5642_get_hflip(void)
{
	print_debug("enter %s", __func__);

	return ov5642_sensor.hflip;
}
static int ov5642_set_vflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);

	ov5642_sensor.vflip = flip;

	return 0;
}
static int ov5642_get_vflip(void)
{
	print_debug("enter %s", __func__);
	return ov5642_sensor.vflip;
}

static int ov5642_update_flip(u16 width, u16 height)
{
	u8 new_flip = ((ov5642_sensor.vflip << 1) | ov5642_sensor.hflip);
    print_debug("Enter %s  ", __func__);
	k3_ispio_update_flip((ov5642_sensor.old_flip ^ new_flip) & 0x03, width, height, PIXEL_ORDER_NO_CHANGED);

	ov5642_sensor.old_flip = new_flip;
	/* fixme:  yjl  2012-08-06 */
	//ov5642_write_reg(OV5642REG_TIMING_FORMAT1, ov5642_sensor.vflip ? 0x00 : 0x42, ~0x42);
	//ov5642_write_reg(OV5642REG_TIMING_FORMAT2, ov5642_sensor.hflip ? 0x06 : 0x00, ~0x06);
	//ov5642_write_reg(OV5642REG_TIMING_FORMAT1, ov5642_sensor.vflip ? 0x20 : 0x00, ~0x20);
	//ov5642_write_reg(OV5642REG_TIMING_FORMAT2, ov5642_sensor.vflip ? 0x20 : 0x00, ~0x20);
	
	//ov5642_write_reg(OV5642REG_TIMING_FORMAT1, ov5642_sensor.hflip ? 0x40 : 0x00, ~0x40);
	//ov5642_write_reg(OV5642REG_TIMING_FORMAT2, ov5642_sensor.hflip ? 0x00 : 0x20, ~0x20);
	return 0;
}

void ov5642_set_vts(u16 vts)
{
	print_debug("Enter %s  ", __func__);
	ov5642_write_reg(OV5642_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
	ov5642_write_reg(OV5642_VTS_REG_L, vts & 0xff, 0x00);
}

u32 ov5642_get_vts_reg_addr(void)
{
	return OV5642_VTS_REG_H;
}



/*
 **************************************************************************
 * FunctionName: ov5642_framesize_switch;
 * Description : switch frame size, used by preview and capture
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5642_framesize_switch(camera_state state)
{
	int size = 0;
	int next_frmsize_index;

	if (state == STATE_PREVIEW)
		next_frmsize_index = ov5642_sensor.preview_frmsize_index;
	else
		next_frmsize_index = ov5642_sensor.capture_frmsize_index;

	print_debug("Enter Function:%s frm index=%d", __func__, next_frmsize_index);
#if 0
	switch (next_frmsize_index) {
	case 0:
		size = ARRAY_SIZE(ov5642_framesize_quarter);
		if (0 != ov5642_write_seq(ov5642_framesize_quarter, size, 0x00)) {
			print_error("fail to init ov5642 sensor");
			return -ETIME;
		}
		break;

	case 1:
		size = ARRAY_SIZE(ov5642_framesize_full);
		if (0 != ov5642_write_seq(ov5642_framesize_full, size, 0x00)) {
			print_error("fail to init ov5642 sensor");
			return -ETIME;
		}
		break;

	default:
		print_error("fail to init ov5642 sensor");
		return -ETIME;
		break;
	}
#endif

		if (next_frmsize_index >= ARRAY_SIZE(ov5642_framesizes)){
		print_error("Unsupport sensor setting index: %d",next_frmsize_index);
		return -ETIME;
	}

	if (0 != ov5642_write_seq(ov5642_sensor.frmsize_list[next_frmsize_index].sensor_setting.setting
		,ov5642_sensor.frmsize_list[next_frmsize_index].sensor_setting.seq_size, 0x00)) {
		print_error("fail to init ov5642 sensor");
		return -ETIME;
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5642_start_preview;
 * Description : download preview seq for sensor preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5642_stream_on(camera_state state)
{
	print_debug("Enter Function:%s  , preview frmsize index=%d",
		    __func__, ov5642_sensor.preview_frmsize_index);

	return ov5642_framesize_switch(state);
}

/*  **************************************************************************
* FunctionName: ov5642_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int ov5642_check_sensor(void)
{
	u8 idl = 0;
	u8 idh = 0;
	u16 id = 0;
	ov5642_read_reg(0x300A, &idh);
	ov5642_read_reg(0x300B, &idl);

	id = ((idh << 8) | idl);
	print_info("ov5642 product id:0x%x", id);
	if (OV5642_CHIP_ID != id) {
		print_error("Invalid product id ,Could not load sensor ov5642");
		return -1;
	}
	return 0;
}

/*  **************************************************************************
* FunctionName: ov5642_power;
* Description : power on/off ov5642;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
int ov5642_power(camera_power_state power)
{
    int                         ret = 0;

#if 0   /* for B05X */
	if (POWER_ON == power){
	    //k3_ispldo_power_sensor(power,"cameralog-vcc");
	    //k3_ispldo_power_sensor(power,"camera-vcc");
	    k3_ispgpio_power_sensor(&ov5642_sensor,power);
	    k3_ispio_ioconfig(&ov5642_sensor, power);
	    //ret = camera_power_core_ldo(power);
	    //k3_ispldo_power_sensor(power,"cameravcm-vcc");
	} else {
	    //k3_ispldo_power_sensor(power,"cameravcm-vcc");
	    //ret = camera_power_core_ldo(power);
	    udelay(200);
	    k3_ispio_ioconfig(&ov5642_sensor,power);
	    k3_ispgpio_power_sensor(&ov5642_sensor,power);
	    //k3_ispldo_power_sensor(power, "camera-vcc");
	    udelay(10);
	    //k3_ispldo_power_sensor(power, "cameralog-vcc");
	}
#else
	if (POWER_ON == power){
	    k3_socgpio_power_sensor(0, CAMERA_ANALOG_VDD);
	    k3_socgpio_power_sensor(0, CAMERA_IO_VCC);
	    k3_ispgpio_power_sensor(&ov5642_sensor, power);
	    //k3_ispio_ioconfig(&ov5642_sensor, power);
	    k3_socgpio_power_sensor(1, CAMERA_CORE_VDD);
	} else {
	    k3_socgpio_power_sensor(0, CAMERA_CORE_VDD);
	    udelay(200);
	    //k3_ispio_ioconfig(&ov5642_sensor,power);
	    k3_ispgpio_power_sensor(&ov5642_sensor, power);
	    k3_socgpio_power_sensor(1, CAMERA_IO_VCC);
	    udelay(10);
	    k3_socgpio_power_sensor(1, CAMERA_ANALOG_VDD);
	}
#endif

	return ret;
}

/*
 * Here gain is in unit 1/16 of sensor gain,
 * y36721 todo, temporarily if sensor gain=0x10, ISO is 100
 * in fact we need calibrate an ISO-ET-gain table.
 */
u32 ov5642_gain_to_iso(int gain)
{
	return (gain * 100) / 0x10;
}

u32 ov5642_iso_to_gain(int iso)
{
	return (iso * 0x10) / 100;
}

void ov5642_set_gain(u32 gain)
{
	ov5642_write_reg(OV5642_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	ov5642_write_reg(OV5642_GAIN_REG_L, gain & 0xff, 0x00);
}

u32 ov5642_get_gain(void)
{
	u8 gain_h = 0;
	u8 gain_l = 0;
	u32 gain;
	ov5642_read_reg(OV5642_GAIN_REG_H, &gain_h);
	ov5642_read_reg(OV5642_GAIN_REG_L, &gain_l);
	gain = (gain_h << 8) | gain_l;
	return gain;
}

void ov5642_set_exposure(u32 exposure)
{
	//ov5642_write_reg(OV5642_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	//ov5642_write_reg(OV5642_EXPOSURE_REG_L, exposure & 0xff, 0x00);
	ov5642_write_reg(OV5642_EXPOSURE_REG_0, (exposure >> 16) & 0x0f, 0x00);
	ov5642_write_reg(OV5642_EXPOSURE_REG_1, (exposure >> 8) & 0xff, 0x00);
	ov5642_write_reg(OV5642_EXPOSURE_REG_2, exposure & 0xff, 0x00);
}

u32 ov5642_get_exposure(void)
{
	//u8 exposure[2] = { 0, 0 };
	u8 exposure[3] = { 0, 0, 0 };
	u32 expo;

	//ov5642_read_reg(OV5642_EXPOSURE_REG_H, &exposure[0]);
	//ov5642_read_reg(OV5642_EXPOSURE_REG_L, &exposure[1]);
	ov5642_read_reg(OV5642_EXPOSURE_REG_0, &exposure[0]);
	ov5642_read_reg(OV5642_EXPOSURE_REG_1, &exposure[1]);
	ov5642_read_reg(OV5642_EXPOSURE_REG_2, &exposure[2]);

	//expo = (exposure[0] << 8) | (exposure[1] << 8) ;
	expo = (exposure[0] << 16) | (exposure[1] << 8) |exposure[2];

	return expo;
}


/*
 **************************************************************************
 * FunctionName: ov5642_reset;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5642_reset(camera_power_state power_state)
{
	print_debug("%s  ", __func__);

	if (POWER_ON == power_state) {
		k3_isp_io_enable_mclk(MCLK_ENABLE, ov5642_sensor.sensor_index);
		k3_ispgpio_reset_sensor(ov5642_sensor.sensor_index, power_state,
					ov5642_sensor.power_conf.reset_valid);
	} else {
		k3_ispgpio_reset_sensor(ov5642_sensor.sensor_index, power_state,
					ov5642_sensor.power_conf.reset_valid);
		udelay(20);
		k3_isp_io_enable_mclk(MCLK_DISABLE, ov5642_sensor.sensor_index);
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5642_init;
 * Description : ov5642 init function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : Error code indicating success or failure;
 * Other       : NA;
 **************************************************************************
*/
static int ov5642_init(void)
{
	print_debug("%s  ", __func__);

	if (ov5642_sensor.owner && !try_module_get(ov5642_sensor.owner)) {
		print_error("%s: try_module_get fail", __func__);
		return -ENOENT;
	}

#if 0   /* del for B05X */
	k3_ispio_power_init(M_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V */
	k3_ispio_power_init(CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);       /*IO 1.8V */
	k3_ispio_power_init(M_CAMERA_CORE_VDD, LDO_VOLTAGE_12V, LDO_VOLTAGE_12V);   /*CORE 1.2V */
#endif

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5642_exit;
 * Description : ov5642 exit function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov5642_exit(void)
{
	print_debug("enter %s", __func__);

	k3_ispio_power_deinit();

	if (ov5642_sensor.owner) {
		module_put(ov5642_sensor.owner);
	}
	print_debug("exit %s", __func__);
}

/*
 **************************************************************************
 * FunctionName: ov5642_shut_down;
 * Description : ov5642 shut down function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov5642_shut_down(void)
{
    print_info("enter %s.",__func__);
    k3_ispgpio_power_sensor(&ov5642_sensor,POWER_OFF);
}




/*
 **************************************************************************
 * FunctionName: ov5642_set_default;
 * Description : init ov5642_sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov5642_set_default(void)
{
	ov5642_sensor.init = ov5642_init;
	ov5642_sensor.exit = ov5642_exit;
	ov5642_sensor.shut_down = ov5642_shut_down;
	ov5642_sensor.reset = ov5642_reset;
	ov5642_sensor.check_sensor = ov5642_check_sensor;
	ov5642_sensor.power = ov5642_power;
	ov5642_sensor.init_reg = ov5642_init_reg;
	ov5642_sensor.stream_on = ov5642_stream_on;

	ov5642_sensor.get_format = ov5642_get_format;
	ov5642_sensor.set_flash = NULL;
	ov5642_sensor.get_flash = NULL;
	ov5642_sensor.set_scene = NULL;
	ov5642_sensor.get_scene = NULL;

	ov5642_sensor.enum_framesizes = ov5642_enum_framesizes;
	ov5642_sensor.try_framesizes = ov5642_try_framesizes;
	ov5642_sensor.set_framesizes = ov5642_set_framesizes;
	ov5642_sensor.get_framesizes = ov5642_get_framesizes;

	ov5642_sensor.enum_frame_intervals = ov5642_enum_frame_intervals;
	ov5642_sensor.try_frame_intervals = NULL;
	ov5642_sensor.set_frame_intervals = NULL;
	ov5642_sensor.get_frame_intervals = NULL;
	ov5642_sensor.get_capability = NULL;

	ov5642_sensor.set_hflip = ov5642_set_hflip;
	ov5642_sensor.get_hflip = ov5642_get_hflip;
	ov5642_sensor.set_vflip = ov5642_set_vflip;
	ov5642_sensor.get_vflip = ov5642_get_vflip;
	ov5642_sensor.update_flip = ov5642_update_flip;

	strncpy(ov5642_sensor.info.name, "ov5642", sizeof(ov5642_sensor.info.name));
	ov5642_sensor.interface_type = DVP;
	ov5642_sensor.mipi_lane_count = CSI_LINES_INVALID;
	ov5642_sensor.mipi_index = CSI_INDEX_INVALID;
	ov5642_sensor.sensor_type = SENSOR_OV;
	ov5642_sensor.sensor_rgb_type = SENSOR_BGGR;
	ov5642_sensor.skip_frames = OV5642_CAM_MODULE_SKIPFRAME;	/* y36721 todo */
	ov5642_sensor.sensor_index = CAMERA_SENSOR_PRIMARY;

	ov5642_sensor.power_conf.pd_valid = HIGH_VALID;
	ov5642_sensor.power_conf.reset_valid = LOW_VALID;
    ov5642_sensor.power_conf.vcmpd_valid = LOW_VALID;
	ov5642_sensor.i2c_config.index = I2C_PRIMARY;
	ov5642_sensor.i2c_config.speed = I2C_SPEED_400;
	ov5642_sensor.i2c_config.addr = OV5642_SLAVE_ADDRESS;
	ov5642_sensor.i2c_config.addr_bits = I2C_16BIT;
	ov5642_sensor.i2c_config.val_bits  = I2C_8BIT;

	ov5642_sensor.preview_frmsize_index = 0;
	ov5642_sensor.capture_frmsize_index = 1;
    ov5642_sensor.frmsize_list = ov5642_framesizes;
	//ov5642_sensor.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW10;
	//ov5642_sensor.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW10;
	ov5642_sensor.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW8;
	ov5642_sensor.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW8;

    /* chenchaofei:need to be check */
	//ov5642_sensor.aec_addr[0] = OV5642_EXPOSURE_REG_H;
	//ov5642_sensor.aec_addr[1] = OV5642_EXPOSURE_REG_L;
	ov5642_sensor.aec_addr[0] = OV5642_EXPOSURE_REG_0;
	ov5642_sensor.aec_addr[1] = OV5642_EXPOSURE_REG_1;
	ov5642_sensor.aec_addr[2] = OV5642_EXPOSURE_REG_2;

	ov5642_sensor.agc_addr[0] = OV5642_GAIN_REG_H;
	ov5642_sensor.agc_addr[1] = OV5642_GAIN_REG_L;
	//ov5642_sensor.aec_addr[0] = 0;	/*new firmware support AP write sensor. */

	ov5642_sensor.set_gain = ov5642_set_gain;
    ov5642_sensor.get_gain = ov5642_get_gain;
	ov5642_sensor.set_exposure = ov5642_set_exposure;
    ov5642_sensor.get_exposure = ov5642_get_exposure;

	ov5642_sensor.set_vts = ov5642_set_vts;
	ov5642_sensor.get_vts_reg_addr = ov5642_get_vts_reg_addr;
	ov5642_sensor.sensor_gain_to_iso = ov5642_gain_to_iso;
	ov5642_sensor.sensor_iso_to_gain = ov5642_iso_to_gain;

	ov5642_sensor.get_sensor_aperture = NULL;
	ov5642_sensor.get_equivalent_focus = NULL;

	ov5642_sensor.isp_location = CAMERA_USE_K3ISP;
	ov5642_sensor.sensor_tune_ops = NULL;

	ov5642_sensor.af_enable = 0;

	ov5642_sensor.image_setting.lensc_param = ov5642_lensc_param;
	ov5642_sensor.image_setting.ccm_param = ov5642_ccm_param;
	ov5642_sensor.image_setting.awb_param = ov5642_awb_param;

	/*default is preview size */
	ov5642_sensor.fps_max = 30;
	ov5642_sensor.fps_min = 5;
	/* modify by zfk78283 fps from 15 to 30 */
	//ov5642_sensor.fps = 15;
	ov5642_sensor.fps = 10;

	ov5642_sensor.owner = THIS_MODULE;

	ov5642_sensor.info.facing = CAMERA_FACING_BACK;
	ov5642_sensor.info.orientation = 90;
    ov5642_sensor.info.focal_length = 439;	/* 4.39mm */
	ov5642_sensor.info.h_view_angle = 66;	/*  66.1 degree */
	ov5642_sensor.info.v_view_angle = 50;
	ov5642_sensor.lane_clk = CLK_800M;
	ov5642_sensor.hflip = 0;
	ov5642_sensor.vflip = 0;
	ov5642_sensor.old_flip = 0;
}

/*
 **************************************************************************
 * FunctionName: UT_ov5642_module_init;
 * Description : ov5642 UT
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
#ifdef MED_UT
camera_sensor *sensor_ov5642;
int UT_ov5642_module_init(void)
{
	sensor_ov5642=&ov5642_sensor;
	ov5642_set_default();
}
#endif

/*
 **************************************************************************
 * FunctionName: ov5642_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int ov5642_module_init(void)
{
	ov5642_set_default();
	return register_camera_sensor(ov5642_sensor.sensor_type, &ov5642_sensor);
}

/*
 **************************************************************************
 * FunctionName: ov5642_module_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void __exit ov5642_module_exit(void)
{
	unregister_camera_sensor(ov5642_sensor.sensor_index,&ov5642_sensor);
}

MODULE_AUTHOR("Hisilicon");
module_init(ov5642_module_init);
module_exit(ov5642_module_exit);
MODULE_LICENSE("GPL");

/********************************** END **********************************************/
