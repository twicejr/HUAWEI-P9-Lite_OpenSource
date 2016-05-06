/*
 *  ov5648 camera driver source file
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
#include "sensor_common.h"
#include "ov5648_sunny.h"
#include <asm/bug.h>
#include <linux/device.h>

#define LOG_TAG "OV5648_SUNNY"
/* #define DEBUG_DEBUG 1 */
#include "cam_log.h"
#include "drv_regulator_user.h"
#include <hsad/config_interface.h>

//#include "../isp/effect.h"
#define OV5648_SUNNY_AP_WRITEAE_MODE

#include "effect.h"
#include "cam_util.h"

#define OV5648_SUNNY_SLAVE_ADDRESS    0x6C
#define OV5648_SUNNY_CHIP_ID          0x5648

#define OV5648_SUNNY_FLIP_REG         0x3820
#define OV5648_SUNNY_MIRROR_REG       0x3821

#define OV5648_SUNNY_EXPOSURE_REG_0	0x3500
#define OV5648_SUNNY_EXPOSURE_REG_1	0x3501
#define OV5648_SUNNY_EXPOSURE_REG_2	0x3502
#define OV5648_SUNNY_GAIN_REG_H		0x350a
#define OV5648_SUNNY_GAIN_REG_L		0x350b
#define OV5648_SUNNY_VTS_REG_H	    0x380e
#define OV5648_SUNNY_VTS_REG_L	    0x380f

/* camera sensor override parameters, define in binning preview mode */
#define OV5648_SUNNY_MAX_ISO			800
#define OV5648_SUNNY_MIN_ISO			100

#define OV5648_SUNNY_AUTOFPS_GAIN_LOW2MID		0x16
#define OV5648_SUNNY_AUTOFPS_GAIN_MID2HIGH		0x16
#define OV5648_SUNNY_AUTOFPS_GAIN_HIGH2MID		0x40
#define OV5648_SUNNY_AUTOFPS_GAIN_MID2LOW		0x40

#define OV5648_SUNNY_MAX_FRAMERATE		30
#define OV5648_SUNNY_MIDDLE_FRAMERATE		15
#define OV5648_SUNNY_MIN_FRAMERATE		15

#define OV5648_SUNNY_MIN_CAP_FRAMERATE	8

#define OV5648_SUNNY_FLASH_TRIGGER_GAIN	0x80

#define OV5648_SUNNY_SHARPNESS_PREVIEW	0x10
#define OV5648_SUNNY_SHARPNESS_CAPTURE	0x10

#define OV5648_SUNNY_ZSL    (0x00)//(1 << CAMERA_ZSL_OFF)

static effect_params effect_ov5648_sunny = {
#include "effect_ov5648_sunny.h"
};

static camera_capability ov5648_sunny_cap[] = {
	{V4L2_CID_ZSL,OV5648_SUNNY_ZSL},
};

/*should be calibrated, three lights, from 0x1c264*/
/*here is long exposure*/
char ov5648_sunny_lensc_param[86 * 3] = {
};

/*should be calibrated, 6 groups 3x3, from 0x1c1d8*/
short ov5648_sunny_ccm_param[54] = {
};

char ov5648_sunny_awb_param[] = {
};

/*y36721 todo*/
char ov5648_sunny_awb_param_short[] = {
};

static framesize_s ov5648_sunny_framesizes[] = {
	{0, 0, 1280, 960, 2816, 1048, 30, 30, 0x141, 0x10C, 0x100, VIEW_FULL, RESOLUTION_4_3, false, false, {ov5648_sunny_framesize_quarter, ARRAY_SIZE(ov5648_sunny_framesize_quarter)} },
	{0, 0, 2592, 1952, 2816, 2088, 15, 15, 0x141, 0x10C, 0x100, VIEW_FULL, RESOLUTION_4_3, false, false, {ov5648_sunny_framesize_full, ARRAY_SIZE(ov5648_sunny_framesize_full)} },
};

static camera_sensor ov5648_sunny_sensor;

static void ov5648_sunny_set_default(void);
void ov5648_sunny_set_vts(u32 vts);

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_read_reg;
 * Description : read ov5648 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_read_reg(u16 reg, u8 *val)
{
	return k3_ispio_read_reg(ov5648_sunny_sensor.i2c_config.index,
				 ov5648_sunny_sensor.i2c_config.addr, reg, (u16*)val, ov5648_sunny_sensor.i2c_config.val_bits,ov5648_sunny_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_write_reg;
 * Description : write ov5648 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_write_reg(u16 reg, u8 val, u8 mask)
{
	return k3_ispio_write_reg(ov5648_sunny_sensor.i2c_config.index,
			ov5648_sunny_sensor.i2c_config.addr, reg, val, ov5648_sunny_sensor.i2c_config.val_bits, mask,ov5648_sunny_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_write_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ov5648_sunny_write_seq(const struct _sensor_reg_t *seq, u32 size, u8 mask)
{
	print_info("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	return k3_ispio_write_seq(ov5648_sunny_sensor.i2c_config.index,
			ov5648_sunny_sensor.i2c_config.addr, seq, size, ov5648_sunny_sensor.i2c_config.val_bits, mask,ov5648_sunny_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_write_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ov5648_sunny_write_isp_seq(const struct isp_reg_t *seq, u32 size)
{
	print_info("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	k3_ispio_write_isp_seq(seq, size);
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_enum_frame_intervals;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_enum_frame_intervals(struct v4l2_frmivalenum *fi)
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

static int ov5648_sunny_get_capability(u32 id, u32 *value)
{
	int i;
	for (i = 0; i < sizeof(ov5648_sunny_cap) / sizeof(ov5648_sunny_cap[0]); ++i) {
		if (id == ov5648_sunny_cap[i].id) {
			*value = ov5648_sunny_cap[i].value;
			break;
		}
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_get_format;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_get_format(struct v4l2_fmtdesc *fmt)
{
	if (fmt->type == V4L2_BUF_TYPE_VIDEO_OVERLAY)
		fmt->pixelformat = V4L2_PIX_FMT_RAW10;
	else
		fmt->pixelformat = V4L2_PIX_FMT_RAW10;
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_enum_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 max_index = ARRAY_SIZE(camera_framesizes) - 1;
	u32 this_max_index = ARRAY_SIZE(ov5648_sunny_framesizes) - 1;

	WARN_ON(framesizes == NULL);
	print_debug("enter %s; ", __func__);

	if (framesizes->index > max_index) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	if ((camera_framesizes[framesizes->index].width > ov5648_sunny_framesizes[this_max_index].width)
		|| (camera_framesizes[framesizes->index].height > ov5648_sunny_framesizes[this_max_index].height)) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	framesizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	framesizes->discrete.width = ov5648_sunny_framesizes[this_max_index].width;
	framesizes->discrete.height = ov5648_sunny_framesizes[this_max_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_try_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_try_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	int max_index = ARRAY_SIZE(ov5648_sunny_framesizes) - 1;

	WARN_ON(framesizes == NULL);
	print_debug("Enter Function:%s  ", __func__);

	if (framesizes->discrete.width <= ov5648_sunny_framesizes[max_index].width
	    && framesizes->discrete.height <= ov5648_sunny_framesizes[max_index].height) {
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
 * FunctionName: ov5648_sunny_set_framesizes;
 * Description : NA;
 * Input       : flag: if 1, set framesize to sensor,
 *					   if 0, only store framesize to camera_interface;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_set_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type, bool zsl_preview)
{
	int i = 0;
    bool match = false;
	WARN_ON(fs == NULL);

	print_debug("Enter Function:%s State(%d), flag=%d, width=%d, height=%d",
		    __func__, state, flag, fs->width, fs->height);

	if (VIEW_FULL == view_type) {
		for (i = 0; i < ARRAY_SIZE(ov5648_sunny_framesizes); i++) {
			if ((ov5648_sunny_framesizes[i].width >= fs->width)
			    && (ov5648_sunny_framesizes[i].height >= fs->height)
			    && (VIEW_FULL == ov5648_sunny_framesizes[i].view_type)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= ov5648_sunny_framesizes[i].resolution_type)) {
				fs->width = ov5648_sunny_framesizes[i].width;
				fs->height = ov5648_sunny_framesizes[i].height;
				match = true;
				break;
			}
		}
	}

	if (false == match) {
		for (i = 0; i < ARRAY_SIZE(ov5648_sunny_framesizes); i++) {
			if ((ov5648_sunny_framesizes[i].width >= fs->width)
			    && (ov5648_sunny_framesizes[i].height >= fs->height)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= ov5648_sunny_framesizes[i].resolution_type)) {
				fs->width = ov5648_sunny_framesizes[i].width;
				fs->height = ov5648_sunny_framesizes[i].height;
				break;
			}
		}
	}
#if 0
	for (i = 0; i < ARRAY_SIZE(ov5648_sunny_framesizes); i++) {
		if ((ov5648_sunny_framesizes[i].width >= fs->width)
		    && (ov5648_sunny_framesizes[i].height >= fs->height)) {
			fs->width = ov5648_sunny_framesizes[i].width;
			fs->height = ov5648_sunny_framesizes[i].height;
			break;
		}
	}
#endif
	if (i >= ARRAY_SIZE(ov5648_sunny_framesizes)) {
		print_error("request resolution larger than sensor's max resolution");
		return -EINVAL;
	}

	if (state == STATE_PREVIEW)
		ov5648_sunny_sensor.preview_frmsize_index = i;
	else
		ov5648_sunny_sensor.capture_frmsize_index = i;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_get_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_get_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs)
{
	int frmsize_index;
	WARN_ON(fs == NULL);

	if (state == STATE_PREVIEW)
		frmsize_index = ov5648_sunny_sensor.preview_frmsize_index;
	else if (state == STATE_CAPTURE)
		frmsize_index = ov5648_sunny_sensor.capture_frmsize_index;
	else
		return -EINVAL;
	fs->width = ov5648_sunny_framesizes[frmsize_index].width;
	fs->height = ov5648_sunny_framesizes[frmsize_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_init_reg;
 * Description : download initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_init_reg(void)
{

	int size = 0;
	print_info("Enter Function:%s  , initsize=%d", __func__, sizeof(ov5648_sunny_init_regs));
        #if 0
    size = CAMERA_MAX_SETTING_SIZE;
	ov5648_sunny_write_isp_seq(sensor->effect->isp_settings, size);
        #endif
	if (0 != k3_ispio_init_csi(ov5648_sunny_sensor.mipi_index,
		 ov5648_sunny_sensor.mipi_lane_count, ov5648_sunny_sensor.lane_clk)) {
    	return -EFAULT;
	}

	ov5648_sunny_write_reg(0x0100, 0x00, 0x00);
	ov5648_sunny_write_reg(0x0103, 0x01, 0x00);
	msleep(5);
	size = ARRAY_SIZE(ov5648_sunny_init_regs);
	if (0 != ov5648_sunny_write_seq(ov5648_sunny_init_regs, size, 0x00)) {
		print_error("fail to init ov5648 sensor");
		return -EFAULT;
	}
//	ov5648_sunny_write_reg(0x0100, 0x01, 0x00);
	return 0;
}

static int ov5648_sunny_set_hflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);
	ov5648_sunny_sensor.hflip = flip;
	return 0;
}

static int ov5648_sunny_set_vflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);
	ov5648_sunny_sensor.vflip = flip;
	return 0;
}

static int ov5648_sunny_get_hflip(void)
{
	print_debug("enter %s flip=%d", __func__, ov5648_sunny_sensor.hflip);
	return ov5648_sunny_sensor.hflip;
}

static int ov5648_sunny_get_vflip(void)
{
	print_debug("enter %s flip=%d", __func__, ov5648_sunny_sensor.vflip);
	return ov5648_sunny_sensor.vflip;
}

static int ov5648_sunny_update_flip(u16 width, u16 height)
{
	u8 new_flip = ((ov5648_sunny_sensor.vflip << 1) | ov5648_sunny_sensor.hflip);
	print_info("Enter %s  ", __func__);
	k3_ispio_update_flip((ov5648_sunny_sensor.old_flip ^ new_flip) & 0x03, width, height, PIXEL_ORDER_NO_CHANGED);
	ov5648_sunny_write_reg(OV5648_SUNNY_FLIP_REG, ov5648_sunny_sensor.vflip ? 0x16 : 0x00, ~0x16);
	ov5648_sunny_write_reg(OV5648_SUNNY_MIRROR_REG, ov5648_sunny_sensor.hflip ? 0x00 : 0x06, ~0x06);
	ov5648_sunny_sensor.old_flip = new_flip;
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_framesize_switch;
 * Description : switch frame size, used by preview and capture
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_framesize_switch(camera_state state)
{
	u8 next_frmsize_index;

	if (state == STATE_PREVIEW)
		next_frmsize_index = ov5648_sunny_sensor.preview_frmsize_index;
	else
		next_frmsize_index = ov5648_sunny_sensor.capture_frmsize_index;

	print_info("Enter Function:%s frm index=%d", __func__, next_frmsize_index);

	if (next_frmsize_index >= ARRAY_SIZE( ov5648_sunny_framesizes )){
		print_error("Unsupport sensor setting index: %d",next_frmsize_index);
		return -ETIME;
	}

	if (0 != ov5648_sunny_write_seq( ov5648_sunny_sensor.frmsize_list[next_frmsize_index].sensor_setting.setting
		, ov5648_sunny_sensor.frmsize_list[next_frmsize_index].sensor_setting.seq_size, 0x00)) {
		print_error("fail to init ov5648 sensor");
		return -ETIME;
	}
	#if 0
	msleep(3);
	/* use auto fps level at coolboot */
	vts = ov5648_sunny_sensor.frmsize_list[next_frmsize_index].vts *
		ov5648_sunny_sensor.frmsize_list[next_frmsize_index].fps / ov5648_sunny_sensor.fps;
	ov5648_sunny_set_vts(vts);
	ov5648_sunny_update_flip(ov5648_sunny_framesizes[next_frmsize_index].width,
		ov5648_sunny_framesizes[next_frmsize_index].height);
	#endif
    return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_start_preview;
 * Description : download preview seq for sensor preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_stream_on(camera_state state)
{
    int                                 ret = 0;

	print_debug("Enter Function:%s  , preview frmsize index=%d",
		    __func__, ov5648_sunny_sensor.preview_frmsize_index);

	ret = ov5648_sunny_framesize_switch(state);
	if (ret != 0)
	{
	    print_warn("%s:ov5648_sunny_framesize_switch fail.ret=%d.",__func__,ret);
	    return ret;
	}

	return 0;
}

/*  **************************************************************************
* FunctionName: ov5648_sunny_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int ov5648_sunny_check_sensor(void)
{
	u8 idl = 0;
	u8 idh = 0;
	u16 id = 0;
	ov5648_sunny_read_reg(0x300A, &idh);
	ov5648_sunny_read_reg(0x300B, &idl);

	id = ((idh << 8) | idl);
	print_info("ov5648 product id:0x%x", id);
	if (OV5648_SUNNY_CHIP_ID != id) {
		print_error("Invalid product id ,Could not load sensor ov5648");
		return -1;
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_init_isp_reg;
 * Description : load initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_init_isp_reg(void)
{
	int size = 0;
	print_info("%s  ", __func__);
	camera_sensor *sensor = &ov5648_sunny_sensor;

        size = CAMERA_MAX_SETTING_SIZE;

        ov5648_sunny_write_isp_seq(sensor->effect->isp_settings, size);

	return 0;
}

/*  **************************************************************************
* FunctionName: ov5648_sunny_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
int ov5648_sunny_power(camera_power_state power)
{
	print_info("%s  ", __func__);
	if(0 == get_sensor_iopower()) {
		if (power == POWER_ON) {
			// Slave Camera Power Up
			k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);
			udelay(100);
			//k3_ispldo_power_sensor(power, S_BACKUP_CAMERA_CORE_VDD);
			udelay(100);
			k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
			udelay(100);
			k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);
			//udelay(100);

			// Primary Camera Power Up
			k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
			k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);
			udelay(200);
			k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);
			k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
			udelay(1);

			k3_ispio_ioconfig(&ov5648_sunny_sensor, power);
			mdelay(8);
			k3_ispgpio_power_sensor(&ov5648_sunny_sensor, power);
			udelay(100);
			k3_ispgpio_reset_sensor(ov5648_sunny_sensor.sensor_index, power, ov5648_sunny_sensor.power_conf.reset_valid);
			udelay(100);
			k3_isp_io_enable_mclk(MCLK_ENABLE, ov5648_sunny_sensor.sensor_index);
			msleep(20);
		} else {
			k3_ispio_deinit_csi(ov5648_sunny_sensor.mipi_index);
			k3_isp_io_enable_mclk(MCLK_DISABLE, ov5648_sunny_sensor.sensor_index);
			k3_ispio_ioconfig(&ov5648_sunny_sensor, power);
			k3_ispgpio_power_sensor(&ov5648_sunny_sensor, power);
			udelay(100);
			k3_ispgpio_reset_sensor(ov5648_sunny_sensor.sensor_index, power, ov5648_sunny_sensor.power_conf.reset_valid);
			udelay(100);

			// Slave Camera Power Down
			k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
			udelay(100);
			//k3_ispldo_power_sensor(power, S_BACKUP_CAMERA_CORE_VDD);
			udelay(100);
			k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);
			udelay(100);
			k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);
			//udelay(100);
			k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
			k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);
			udelay(200);
			k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
			k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);
		}
	} else {
		if (power == POWER_ON) {
			// Slave Camera Power Up
			k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);
			udelay(100);
			k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
			udelay(100);
			k3_ispio_ioconfig(&ov5648_sunny_sensor, power);
			mdelay(8);
			k3_ispgpio_power_sensor(&ov5648_sunny_sensor, power);
			udelay(100);
			k3_ispgpio_reset_sensor(ov5648_sunny_sensor.sensor_index, power, ov5648_sunny_sensor.power_conf.reset_valid);
			udelay(100);
			k3_isp_io_enable_mclk(MCLK_ENABLE, ov5648_sunny_sensor.sensor_index);
			msleep(20);
		} else {
			k3_ispio_deinit_csi(ov5648_sunny_sensor.mipi_index);
			k3_isp_io_enable_mclk(MCLK_DISABLE, ov5648_sunny_sensor.sensor_index);
			k3_ispio_ioconfig(&ov5648_sunny_sensor, power);
			k3_ispgpio_power_sensor(&ov5648_sunny_sensor, power);
			udelay(100);
			k3_ispgpio_reset_sensor(ov5648_sunny_sensor.sensor_index, power, ov5648_sunny_sensor.power_conf.reset_valid);
			udelay(100);

			// Slave Camera Power Down
			k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
			udelay(100);
			k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);
		}
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_shut_down;
 * Description : ov5648 shut down function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov5648_sunny_shut_down(void)
{
	print_debug("enter %s", __func__);
	k3_ispgpio_power_sensor(&ov5648_sunny_sensor, POWER_OFF);
}

/*
 * Here gain is in unit 1/16 of sensor gain,
 * y36721 todo, temporarily if sensor gain=0x10, ISO is 100
 * in fact we need calibrate an ISO-ET-gain table.
 */
u32 ov5648_sunny_gain_to_iso(int gain)
{
	return (gain * 100) / 0x10;
}

u32 ov5648_sunny_iso_to_gain(int iso)
{
	return (iso * 0x10) / 100;
}

void ov5648_sunny_set_gain(u32 gain)
{
	ov5648_sunny_write_reg(OV5648_SUNNY_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	ov5648_sunny_write_reg(OV5648_SUNNY_GAIN_REG_L, gain & 0xff, 0x00);
}

void ov5648_sunny_set_exposure(u32 exposure)
{
	ov5648_sunny_write_reg(OV5648_SUNNY_EXPOSURE_REG_0, (exposure >> 16) & 0x0f, 0x00);
	ov5648_sunny_write_reg(OV5648_SUNNY_EXPOSURE_REG_1, (exposure >> 8) & 0xff, 0x00);
	ov5648_sunny_write_reg(OV5648_SUNNY_EXPOSURE_REG_2, exposure & 0xf0, 0x00);	/*fraction part not used */
}

u32 ov5648_sunny_get_vts_reg_addr(void)
{
	return OV5648_SUNNY_VTS_REG_H;
}

void ov5648_sunny_set_vts(u32 vts)
{
	ov5648_sunny_write_reg(OV5648_SUNNY_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
	ov5648_sunny_write_reg(OV5648_SUNNY_VTS_REG_L, vts & 0xff, 0x00);
}

static u32 ov5648_sunny_get_override_param(camera_override_type_t type)
{
	u32 ret_val = sensor_override_params[type];

	switch (type) {
	case OVERRIDE_ISO_HIGH:
		ret_val = OV5648_SUNNY_MAX_ISO;
		break;

	case OVERRIDE_ISO_LOW:
		ret_val = OV5648_SUNNY_MIN_ISO;
		break;

	/* increase frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_LOW2MID:
		ret_val = OV5648_SUNNY_AUTOFPS_GAIN_LOW2MID;
		break;
	case OVERRIDE_AUTOFPS_GAIN_MID2HIGH:
		ret_val = OV5648_SUNNY_AUTOFPS_GAIN_MID2HIGH;
		break;

	/* reduce frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_MID2LOW:
		ret_val = OV5648_SUNNY_AUTOFPS_GAIN_MID2LOW;
		break;
	case OVERRIDE_AUTOFPS_GAIN_HIGH2MID:
		ret_val = OV5648_SUNNY_AUTOFPS_GAIN_HIGH2MID;
		break;

	case OVERRIDE_FPS_MAX:
		ret_val = OV5648_SUNNY_MAX_FRAMERATE;
		break;

	case OVERRIDE_FPS_MIN:
		ret_val = OV5648_SUNNY_MIN_FRAMERATE;
		break;

    case OVERRIDE_FPS_MID:
        ret_val = OV5648_SUNNY_MIDDLE_FRAMERATE;
        break;

	case OVERRIDE_CAP_FPS_MIN:
		ret_val = OV5648_SUNNY_MIN_CAP_FRAMERATE;
		break;

	case OVERRIDE_FLASH_TRIGGER_GAIN:
		ret_val = OV5648_SUNNY_FLASH_TRIGGER_GAIN;
		break;

	case OVERRIDE_SHARPNESS_PREVIEW:
		ret_val = OV5648_SUNNY_SHARPNESS_PREVIEW;
		break;

	case OVERRIDE_SHARPNESS_CAPTURE:
		ret_val = OV5648_SUNNY_SHARPNESS_CAPTURE;
		break;

	default:
		print_error("%s:not override or invalid type %d, use default",__func__, type);
		break;
	}

	return ret_val;
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_reset;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_reset(camera_power_state power_state)
{
	print_debug("%s  ", __func__);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_init;
 * Description : ov5648 init function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : Error code indicating success or failure;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_sunny_init(void)
{
	static bool ov5648_sunny_check = false;
	print_info("%s  ", __func__);

	if (!camera_timing_is_match(0)) {
		print_error("%s: sensor timing don't match.\n", __func__);
		return -ENODEV;
	}

	if (ov5648_sunny_sensor.owner && !try_module_get(ov5648_sunny_sensor.owner)) {
		print_error("%s: try_module_get fail", __func__);
		return -ENOENT;
	}

	if(0 == get_sensor_iopower()) {
		k3_ispio_power_init(S_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - sec camera*/
		k3_ispio_power_init(S_CAMERA_CORE_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);	/*core 1.8V - sec camera*/
		//k3_ispio_power_init(S_BACKUP_CAMERA_CORE_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);	/*core 1.8V - sec camera*/
		k3_ispio_power_init(S_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);
		k3_ispio_power_init(M_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - pri camera*/
		k3_ispio_power_init(M_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);		/*IO 1.8V - pri camera*/
		k3_ispio_power_init(M_CAMERA_VCM_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*AF 2.85V - pri camera*/
		k3_ispio_power_init(M_CAMERA_CORE_VDD, LDO_VOLTAGE_10V, LDO_VOLTAGE_10V);	/*core 1.05V - pri camera*/
	} else {
		k3_ispio_power_init(S_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - sec camera*/
		k3_ispio_power_init(S_CAMERA_CORE_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);	/*core 1.8V - sec camera*/
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_exit;
 * Description : ov5648 exit function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov5648_sunny_exit(void)
{
	print_debug("enter %s", __func__);

	k3_ispio_power_deinit();

	if (ov5648_sunny_sensor.owner) {
		module_put(ov5648_sunny_sensor.owner);
	}
	print_debug("exit %s", __func__);
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_set_default;
 * Description : init ov5648_sunny_sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov5648_sunny_set_default(void)
{
	ov5648_sunny_sensor.init = ov5648_sunny_init;
	ov5648_sunny_sensor.exit = ov5648_sunny_exit;
	ov5648_sunny_sensor.reset = ov5648_sunny_reset;
	ov5648_sunny_sensor.shut_down = ov5648_sunny_shut_down;
	ov5648_sunny_sensor.check_sensor = ov5648_sunny_check_sensor;
	ov5648_sunny_sensor.power = ov5648_sunny_power;
	ov5648_sunny_sensor.init_reg = ov5648_sunny_init_reg;
	ov5648_sunny_sensor.stream_on = ov5648_sunny_stream_on;

	ov5648_sunny_sensor.get_format = ov5648_sunny_get_format;
	ov5648_sunny_sensor.set_flash = NULL;
	ov5648_sunny_sensor.get_flash = NULL;
	ov5648_sunny_sensor.set_scene = NULL;
	ov5648_sunny_sensor.get_scene = NULL;

	ov5648_sunny_sensor.enum_framesizes = ov5648_sunny_enum_framesizes;
	ov5648_sunny_sensor.try_framesizes = ov5648_sunny_try_framesizes;
	ov5648_sunny_sensor.set_framesizes = ov5648_sunny_set_framesizes;
	ov5648_sunny_sensor.get_framesizes = ov5648_sunny_get_framesizes;

	ov5648_sunny_sensor.enum_frame_intervals = ov5648_sunny_enum_frame_intervals;
	ov5648_sunny_sensor.try_frame_intervals = NULL;
	ov5648_sunny_sensor.set_frame_intervals = NULL;
	ov5648_sunny_sensor.get_frame_intervals = NULL;
	ov5648_sunny_sensor.get_capability = ov5648_sunny_get_capability;

	strncpy(ov5648_sunny_sensor.info.name, "ov5648_sunny", sizeof(ov5648_sunny_sensor.info.name));
	ov5648_sunny_sensor.interface_type = MIPI2;
	ov5648_sunny_sensor.mipi_lane_count = CSI_LINES_2;
	ov5648_sunny_sensor.mipi_index = CSI_INDEX_1;
	ov5648_sunny_sensor.sensor_index = CAMERA_SENSOR_SECONDARY;
	ov5648_sunny_sensor.skip_frames = 2;

	ov5648_sunny_sensor.power_conf.pd_valid = LOW_VALID;
	ov5648_sunny_sensor.power_conf.reset_valid = LOW_VALID;
	ov5648_sunny_sensor.i2c_config.index = I2C_SECONDARY;
	ov5648_sunny_sensor.i2c_config.speed = I2C_SPEED_400;
	ov5648_sunny_sensor.i2c_config.addr = OV5648_SUNNY_SLAVE_ADDRESS;
	ov5648_sunny_sensor.i2c_config.addr_bits = I2C_16BIT;
	ov5648_sunny_sensor.i2c_config.val_bits = I2C_8BIT;

	ov5648_sunny_sensor.preview_frmsize_index = 0;
	ov5648_sunny_sensor.capture_frmsize_index = 0;
	ov5648_sunny_sensor.frmsize_list = ov5648_sunny_framesizes;
	ov5648_sunny_sensor.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW10;
	ov5648_sunny_sensor.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW10;
#ifdef OV5648_SUNNY_AP_WRITEAE_MODE
	ov5648_sunny_sensor.aec_addr[0] = 0;
	ov5648_sunny_sensor.aec_addr[1] = 0;
	ov5648_sunny_sensor.aec_addr[2] = 0;
	ov5648_sunny_sensor.agc_addr[0] = 0;
	ov5648_sunny_sensor.agc_addr[1] = 0;
	ov5648_sunny_sensor.ap_writeAE_delay = 6000;
#else
	ov5648_sunny_sensor.aec_addr[0] = 0x3500;
	ov5648_sunny_sensor.aec_addr[1] = 0x3501;
	ov5648_sunny_sensor.aec_addr[2] = 0x3502;
	ov5648_sunny_sensor.agc_addr[0] = 0x350a;
	ov5648_sunny_sensor.agc_addr[1] = 0x350b;
#endif
	ov5648_sunny_sensor.sensor_type = SENSOR_OV;

	ov5648_sunny_sensor.get_vts_reg_addr = ov5648_sunny_get_vts_reg_addr;
    ov5648_sunny_sensor.set_vts = ov5648_sunny_set_vts;
	ov5648_sunny_sensor.set_gain = ov5648_sunny_set_gain;
	ov5648_sunny_sensor.set_exposure = ov5648_sunny_set_exposure;

	ov5648_sunny_sensor.get_override_param = ov5648_sunny_get_override_param;

	ov5648_sunny_sensor.sensor_gain_to_iso = ov5648_sunny_gain_to_iso;
	ov5648_sunny_sensor.sensor_iso_to_gain = ov5648_sunny_iso_to_gain;

	ov5648_sunny_sensor.get_sensor_aperture = NULL;
	ov5648_sunny_sensor.get_equivalent_focus = NULL;

	ov5648_sunny_sensor.isp_location = CAMERA_USE_K3ISP;
	ov5648_sunny_sensor.sensor_tune_ops = NULL;

	ov5648_sunny_sensor.af_enable = 0;

	ov5648_sunny_sensor.sensor_gain_to_iso = ov5648_sunny_gain_to_iso;
	ov5648_sunny_sensor.sensor_iso_to_gain = ov5648_sunny_iso_to_gain;

	ov5648_sunny_sensor.image_setting.lensc_param = ov5648_sunny_lensc_param;
	ov5648_sunny_sensor.image_setting.ccm_param = ov5648_sunny_ccm_param;
	ov5648_sunny_sensor.image_setting.awb_param = ov5648_sunny_awb_param;

	/*default is preview size */
	ov5648_sunny_sensor.fps_max = 30;
	ov5648_sunny_sensor.fps_min = 16;
	ov5648_sunny_sensor.fps = 25;

	/*defalt flip*/
	ov5648_sunny_sensor.vflip			= 0;
	ov5648_sunny_sensor.hflip			= 0;
	ov5648_sunny_sensor.old_flip		= 0;
	ov5648_sunny_sensor.set_vflip		= ov5648_sunny_set_vflip;
	ov5648_sunny_sensor.set_hflip		= ov5648_sunny_set_hflip;
	ov5648_sunny_sensor.get_vflip		= ov5648_sunny_get_vflip;
	ov5648_sunny_sensor.get_hflip		= ov5648_sunny_get_hflip;
	ov5648_sunny_sensor.update_flip		= ov5648_sunny_update_flip;
	ov5648_sunny_sensor.sensor_rgb_type = SENSOR_BGGR;


	ov5648_sunny_sensor.owner = THIS_MODULE;

	ov5648_sunny_sensor.info.facing = CAMERA_FACING_FRONT;
	ov5648_sunny_sensor.info.orientation = 90;
	ov5648_sunny_sensor.lane_clk = CLK_450M;
	ov5648_sunny_sensor.effect = &effect_ov5648_sunny;
	ov5648_sunny_sensor.support_summary = false;
	ov5648_sunny_sensor.init_isp_reg = ov5648_sunny_init_isp_reg;
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int ov5648_sunny_module_init(void)
{
	ov5648_sunny_set_default();
	return register_camera_sensor(ov5648_sunny_sensor.sensor_index, &ov5648_sunny_sensor);
}

/*
 **************************************************************************
 * FunctionName: ov5648_sunny_module_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void __exit ov5648_sunny_module_exit(void)
{
	unregister_camera_sensor(ov5648_sunny_sensor.sensor_index, &ov5648_sunny_sensor);
}

MODULE_AUTHOR("Hisilicon");
module_init(ov5648_sunny_module_init);
module_exit(ov5648_sunny_module_exit);
MODULE_LICENSE("GPL");

/********************************** END **********************************************/
