/*
 *  s5k4e1gx_foxconn camera driver source file
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
#include <mach/gpio.h>
#include "sensor_common.h"
#include "s5k4e1gx_foxconn.h"
#include <asm/bug.h>
#include <linux/device.h>
#include "drv_regulator_user.h"

#include <hsad/config_interface.h>
#include "effect.h"

#define LOG_TAG "S5K4E1GX_FOXCONN"
#define DEBUG_DEBUG 1
#include "cam_log.h"
#include "cam_util.h"


#define S5K4ELGX_FOXCONN_AP_WRITEAE_MODE

#define S5K4E1GX_MAX_ISO 			1550
#define S5K4E1GX_MIN_ISO                      100
#define S5K4E1GX_AUTOFPS_GAIN_LOW2MID		0x60
#define S5K4E1GX_AUTOFPS_GAIN_MID2HIGH		0x60
#define S5K4E1GX_AUTOFPS_GAIN_HIGH2MID		0x24
#define S5K4E1GX_AUTOFPS_GAIN_MID2LOW		0x24
#define S5K4E1GX_MAX_FRAMERATE         30
#define S5K4E1GX_MID_FRAMERATE         10
#define S5K4E1GX_MIN_FRAMERATE          10
#define S5K4E1GX_MIN_CAP_FRAMERATE  8
#define S5K4E1GX_FLASH_TRIGGER_GAIN 0xff
#define S5K4E1GX_SHARPNESS_PREVIEW  0x30
#define S5K4E1GX_SHARPNESS_CAPTURE  0x08

#define S5K4E1GX_FOXCONN_SLAVE_ADDRESS 0x30
#define S5K4E1GX_FOXCONN_CHIP_ID       (0x4e10)

#define S5K4E1GX_FOXCONN_CAM_MODULE_SKIPFRAME     4

#define S5K4E1GX_FOXCONN_HFLIP    0
#define S5K4E1GX_FOXCONN_VFLIP    0

#define S5K4E1GX_FOXCONN_NO_FLIP	0x00
#define S5K4E1GX_FOXCONN_H_FLIP	0x01
#define S5K4E1GX_FOXCONN_V_FLIP	0x02
#define S5K4E1GX_FOXCONN_HV_FLIP	0x03

#define S5K4E1GX_FLIP		0x0101

#define S5K4E1GX_FOXCONN_EXPOSURE_REG_H	0x0202
#define S5K4E1GX_FOXCONN_EXPOSURE_REG_L	0x0203
#define S5K4E1GX_FOXCONN_GAIN_REG_H		0x0204
#define S5K4E1GX_FOXCONN_GAIN_REG_L		0x0205

#define S5K4E1GX_FOXCONN_VTS_REG_H		0x0340
#define S5K4E1GX_FOXCONN_VTS_REG_L		0x0341

#define S5K4E1GX_FOXCONN_I2C_RETRY_TIMES 5
#define S5K4E1GX_ZSL    (0x00)//(1 << CAMERA_ZSL_OFF)

extern u32 get_slave_sensor_id(void);

const struct isp_reg_t isp_init_regs_s5k4e1gx_foxconn[] = {
};

/*
 * should be calibrated, three lights, from 0x1c264
 * here is long exposure
 */
char s5k4e1gx_foxconn_lensc_param[86*3] = {
};

/* should be calibrated, 6 groups 3x3, from 0x1c1d8 */
short s5k4e1gx_foxconn_ccm_param[54] = {
};

char s5k4e1gx_foxconn_awb_param[] = {
};

static effect_params effect_s5k4e1gx_foxconn = {
#include "effect_s5k4e1gx_foxconn_edge.h"
};

static framesize_s s5k4e1gx_foxconn_framesizes[] = {
	{0, 0, 1280, 960, 2982, 1072, 30, 30, 0x141, 0x10C, 0x100, VIEW_FULL, RESOLUTION_4_3, false, false,{s5k4e1gx_foxconn_framesize_1280x960, ARRAY_SIZE(s5k4e1gx_foxconn_framesize_1280x960)} },
	//{0, 0, 1920, 1088, 2982, 1200, 27, 27, 0x141, 0x10C, 0x200, VIEW_FULL, RESOLUTION_4_3, false,false, {s5k4e1gx_foxconn_framesize_1080p, ARRAY_SIZE(s5k4e1gx_foxconn_framesize_1080p)} },
	{0, 0, 2592, 1952, 2982, 2148, 15, 15, 0x141, 0x10C, 0x100, VIEW_FULL, RESOLUTION_4_3, false, false,{s5k4e1gx_foxconn_framesize_full, ARRAY_SIZE(s5k4e1gx_foxconn_framesize_full)} },
};

static camera_capability s5k4e1gx_cap[] = {
    {V4L2_CID_FOCAL_LENGTH, 238},//2.38mm
	{V4L2_CID_ZSL,S5K4E1GX_ZSL}
};
static camera_sensor s5k4e1gx_foxconn_sensor;
static void s5k4e1gx_foxconn_set_default(void);

static int s5k4e1gx_get_capability(u32 id, u32 *value)
{
	int i;
	for (i = 0; i < sizeof(s5k4e1gx_cap) / sizeof(s5k4e1gx_cap[0]); ++i) {
		if (id == s5k4e1gx_cap[i].id) {
			*value = s5k4e1gx_cap[i].value;
			break;
		}
	}
	return 0;
}
/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_read_reg;
 * Description : read s5k4e1gx_foxconn reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_read_reg(u16 reg, u8 *val)
{
	return k3_ispio_read_reg(s5k4e1gx_foxconn_sensor.i2c_config.index,
				 s5k4e1gx_foxconn_sensor.i2c_config.addr, reg, (u16 *)val, s5k4e1gx_foxconn_sensor.i2c_config.val_bits,s5k4e1gx_foxconn_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_write_reg;
 * Description : write s5k4e1gx_foxconn reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_write_reg(u16 reg, u8 val, u8 mask)
{
	return k3_ispio_write_reg(s5k4e1gx_foxconn_sensor.i2c_config.index,
			s5k4e1gx_foxconn_sensor.i2c_config.addr, reg, val, s5k4e1gx_foxconn_sensor.i2c_config.val_bits, mask,s5k4e1gx_foxconn_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_write_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int s5k4e1gx_foxconn_write_seq(const struct _sensor_reg_t *seq, u32 size, u8 mask)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	return k3_ispio_write_seq(s5k4e1gx_foxconn_sensor.i2c_config.index,
			s5k4e1gx_foxconn_sensor.i2c_config.addr, seq, size, s5k4e1gx_foxconn_sensor.i2c_config.val_bits, mask,s5k4e1gx_foxconn_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_write_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void s5k4e1gx_foxconn_write_isp_seq(const struct isp_reg_t *seq, u32 size)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	k3_ispio_write_isp_seq(seq, size);
}


/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_enum_frame_intervals;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_enum_frame_intervals(struct v4l2_frmivalenum *fi)
{
	assert(fi);

	if(NULL == fi) {
		return -EINVAL;
	}

	print_debug("enter %s", __func__);
	if (fi->index >= CAMERA_MAX_FRAMERATE) {
		return -EINVAL;
	}

	fi->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fi->discrete.numerator = 1;
	fi->discrete.denominator = (fi->index+1);
	return 0;
}


/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_get_format;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_get_format(struct v4l2_fmtdesc *fmt)
{
	if (fmt->type == V4L2_BUF_TYPE_VIDEO_OVERLAY) {
		fmt->pixelformat = s5k4e1gx_foxconn_sensor.fmt[STATE_PREVIEW];
	} else {
		fmt->pixelformat = s5k4e1gx_foxconn_sensor.fmt[STATE_CAPTURE];
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_enum_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 max_index = ARRAY_SIZE(camera_framesizes) - 1;
	u32 this_max_index = ARRAY_SIZE(s5k4e1gx_foxconn_framesizes) - 1;

	assert(framesizes);

	if(NULL == framesizes) {
		return -EINVAL;
	}

	print_debug("enter %s; ", __func__);

	if (framesizes->index > max_index) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	if ((camera_framesizes[framesizes->index].width > s5k4e1gx_foxconn_framesizes[this_max_index].width)
		|| (camera_framesizes[framesizes->index].height > s5k4e1gx_foxconn_framesizes[this_max_index].height)) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	framesizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	framesizes->discrete.width = s5k4e1gx_foxconn_framesizes[this_max_index].width;
	framesizes->discrete.height = s5k4e1gx_foxconn_framesizes[this_max_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_try_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_try_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	int max_index = ARRAY_SIZE(s5k4e1gx_foxconn_framesizes) - 1;

	assert(framesizes);

	if(NULL == framesizes) {
		return -EINVAL;
	}

	print_debug("Enter Function:%s  ", __func__);


	if ((framesizes->discrete.width <= s5k4e1gx_foxconn_framesizes[max_index].width)
	    && (framesizes->discrete.height <= s5k4e1gx_foxconn_framesizes[max_index].height)) {
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
 * FunctionName: s5k4e1gx_foxconn_init_isp_reg;
 * Description : load initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_init_isp_reg(void)
{
	int size = 0;

	camera_sensor *sensor = &s5k4e1gx_foxconn_sensor;

        size = CAMERA_MAX_SETTING_SIZE;

        s5k4e1gx_foxconn_write_isp_seq(sensor->effect->isp_settings, size);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_set_framesizes;
 * Description : NA;
 * Input       : flag: if 1, set framesize to sensor,
 *					   if 0, only store framesize to camera_interface;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_set_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type,bool zsl_preview)
{
	int i = 0;
	bool match = false;

	assert(fs);

	if(NULL == fs) {
		return -EINVAL;
	}

	print_debug("Enter Function:%s State(%d), flag=%d, width=%d, height=%d",
		    __func__, state, flag, fs->width, fs->height);

	if (VIEW_FULL == view_type) {
		for (i = 0; i < ARRAY_SIZE(s5k4e1gx_foxconn_framesizes); i++) {
			if ((s5k4e1gx_foxconn_framesizes[i].width >= fs->width)
			    && (s5k4e1gx_foxconn_framesizes[i].height >= fs->height)
			    && (VIEW_FULL == s5k4e1gx_foxconn_framesizes[i].view_type)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= s5k4e1gx_foxconn_framesizes[i].resolution_type)) {
				fs->width = s5k4e1gx_foxconn_framesizes[i].width;
				fs->height = s5k4e1gx_foxconn_framesizes[i].height;
				match = true;
				break;
			}
		}
	}

	if (false == match) {
		for (i = 0; i < ARRAY_SIZE(s5k4e1gx_foxconn_framesizes); i++) {
			if ((s5k4e1gx_foxconn_framesizes[i].width >= fs->width)
			    && (s5k4e1gx_foxconn_framesizes[i].height >= fs->height)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= s5k4e1gx_foxconn_framesizes[i].resolution_type)) {
				fs->width = s5k4e1gx_foxconn_framesizes[i].width;
				fs->height = s5k4e1gx_foxconn_framesizes[i].height;
				break;
			}
		}
	}

	if (i >= ARRAY_SIZE(s5k4e1gx_foxconn_framesizes)) {
		print_error("request resolution larger than sensor's max resolution");
		return -EINVAL;
	}

	if (state == STATE_PREVIEW) {
		s5k4e1gx_foxconn_sensor.preview_frmsize_index = i;
	} else {
		s5k4e1gx_foxconn_sensor.capture_frmsize_index = i;
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_get_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_get_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs)
{
	int frmsize_index;

	assert(fs);

	if(NULL == fs) {
		return -EINVAL;
	}

	if (state == STATE_PREVIEW) {
		frmsize_index = s5k4e1gx_foxconn_sensor.preview_frmsize_index;
	} else if (state == STATE_CAPTURE) {
		frmsize_index = s5k4e1gx_foxconn_sensor.capture_frmsize_index;
	} else {
		return -EINVAL;
	}
	fs->width = s5k4e1gx_foxconn_framesizes[frmsize_index].width;
	fs->height = s5k4e1gx_foxconn_framesizes[frmsize_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_init_reg;
 * Description : download initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_init_reg(void)
{
	camera_sensor *sensor = &s5k4e1gx_foxconn_sensor;
	int size = 0;
	print_debug("Enter Function:%s  , initsize=%d",
		    __func__, sizeof(s5k4e1gx_foxconn_init_regs));
#if 0
         size = CAMERA_MAX_SETTING_SIZE;
	s5k4e1gx_foxconn_write_isp_seq(sensor->effect->isp_settings, size);
#endif
	if (0 != k3_ispio_init_csi(s5k4e1gx_foxconn_sensor.mipi_index,
				 s5k4e1gx_foxconn_sensor.mipi_lane_count, s5k4e1gx_foxconn_sensor.lane_clk)) {
		return -EFAULT;
	}

	size = ARRAY_SIZE(s5k4e1gx_foxconn_init_regs);
	if (0 != s5k4e1gx_foxconn_write_seq(s5k4e1gx_foxconn_init_regs, size, 0x00)) {
		print_error("fail to init s5k4e1gx_foxconn sensor");
		return -EFAULT;
	}
    
	if(E_CAMERA_SENSOR_FLIP_TYPE_H_V == get_secondary_sensor_flip_type()) {
		s5k4e1gx_foxconn_write_reg(S5K4E1GX_FLIP, 0x03, 0x00); //turn camera layout
		print_info("%s:change flip and mirror", __func__);
	}

	return 0;
}

static int s5k4e1gx_update_flip(u16 width, u16 height)
{
	
	print_info("Enter %s  ", __func__);
	u8 new_flip = ((s5k4e1gx_foxconn_sensor.vflip << 1) | s5k4e1gx_foxconn_sensor.hflip);
	u8 old_flip = s5k4e1gx_foxconn_sensor.old_flip;
	if (old_flip != new_flip) { 
		k3_ispio_update_flip((s5k4e1gx_foxconn_sensor.old_flip ^ new_flip) & 0x03, width, height, (old_flip ^ new_flip) & 0x03);
   		print_info("secondary_sensor_flip_type = %d", get_secondary_sensor_flip_type());

		if(E_CAMERA_SENSOR_FLIP_TYPE_H_V == get_secondary_sensor_flip_type()){
			s5k4e1gx_foxconn_write_reg(S5K4E1GX_FLIP, s5k4e1gx_foxconn_sensor.vflip ? 0x00 : 0x02, ~0x02);
			s5k4e1gx_foxconn_write_reg(S5K4E1GX_FLIP, s5k4e1gx_foxconn_sensor.hflip ? 0x00 : 0x01, ~0x01);
		}else{
			s5k4e1gx_foxconn_write_reg(S5K4E1GX_FLIP, s5k4e1gx_foxconn_sensor.vflip ? 0x02 : 0x00, ~0x02);
			s5k4e1gx_foxconn_write_reg(S5K4E1GX_FLIP, s5k4e1gx_foxconn_sensor.hflip ? 0x01 : 0x00, ~0x01);
		}
	s5k4e1gx_foxconn_sensor.old_flip = new_flip;
	}
	return 0;
}

static int s5k4e1gx_foxconn_set_hflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);
	s5k4e1gx_foxconn_sensor.hflip = flip;
	return 0;
}
static int s5k4e1gx_foxconn_get_hflip(void)
{
	print_debug("enter %s", __func__);

	return s5k4e1gx_foxconn_sensor.hflip;
}
static int s5k4e1gx_foxconn_set_vflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);

	s5k4e1gx_foxconn_sensor.vflip = flip;

	return 0;
}
static int s5k4e1gx_foxconn_get_vflip(void)
{
	print_debug("enter %s", __func__);
	return s5k4e1gx_foxconn_sensor.vflip;
}


/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_framesize_switch;
 * Description : switch frame size, used by preview and capture
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_framesize_switch(camera_state state)
{
	u32 size = 0;
	u8 next_frmsize_index;


	if (state == STATE_PREVIEW)
		next_frmsize_index = s5k4e1gx_foxconn_sensor.preview_frmsize_index;
	else
		next_frmsize_index = s5k4e1gx_foxconn_sensor.capture_frmsize_index;

	print_debug("Enter Function:%s frm index=%d", __func__, next_frmsize_index);

	if (next_frmsize_index >= ARRAY_SIZE( s5k4e1gx_foxconn_framesizes)){
		print_error("Unsupport sensor setting index: %d",next_frmsize_index);
		return -ETIME;
	}

	if (0 != s5k4e1gx_foxconn_write_seq( s5k4e1gx_foxconn_sensor.frmsize_list[next_frmsize_index].sensor_setting.setting
		, s5k4e1gx_foxconn_sensor.frmsize_list[next_frmsize_index].sensor_setting.seq_size, 0x00)) {
		print_error("fail to init s5k4e1gx_foxconn sensor");
		return -ETIME;
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_stream_on;
 * Description : download preview seq for sensor preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_stream_on(camera_state state)
{
	print_debug("Enter Function:%s ", __func__);
	return s5k4e1gx_foxconn_framesize_switch(state);
}


/*  **************************************************************************
* FunctionName: s5k4e1gx_foxconn_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int s5k4e1gx_foxconn_check_sensor(void)
{
	u8 idl = 0;
	u8 idh = 0;
	u16 id = 0;
    int retry = 0;
	msleep(3);
    for(retry = 0; retry < S5K4E1GX_FOXCONN_I2C_RETRY_TIMES; retry++) {
    	s5k4e1gx_foxconn_read_reg(0x0000, &idh);
    	s5k4e1gx_foxconn_read_reg(0x0001, &idl);

    	id = ((idh << 8) | idl);
    	print_info("s5k4e1gx_foxconn product id:0x%x, retrytimes:%d", id, retry);
        if(S5K4E1GX_FOXCONN_CHIP_ID == id) {
            break;
        }
        udelay(100);
    }
	if (S5K4E1GX_FOXCONN_CHIP_ID != id) {
		print_error("Invalid product id ,Could not load sensor s5k4e1gx_foxconn");
		return -ENODEV;
	}

	return 0;
}

/****************************************************************************
* FunctionName: s5k4e1gx_foxconn_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
int s5k4e1gx_foxconn_power(camera_power_state power)
{
	int ret = 0;

	if (power == POWER_ON) {
		k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);
		k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
		//k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);

		k3_ispio_ioconfig(&s5k4e1gx_foxconn_sensor, power);
	} else {
		k3_ispio_deinit_csi(s5k4e1gx_foxconn_sensor.mipi_index);
		k3_ispio_ioconfig(&s5k4e1gx_foxconn_sensor, power);

		k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
		k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);		
		//k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);
	}

	return ret;
}

void s5k4e1gx_foxconn_set_gain(u32 gain)
{
	gain = gain << 1;
	s5k4e1gx_foxconn_write_reg(S5K4E1GX_FOXCONN_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	s5k4e1gx_foxconn_write_reg(S5K4E1GX_FOXCONN_GAIN_REG_L, gain & 0xff, 0x00);
}
void s5k4e1gx_foxconn_set_exposure_gain(u32 exposure, u32 gain)
{
	s5k4e1gx_foxconn_write_reg(0x0104, 0x01, 0x00);//hold on

	//print_info("enter %s, gain: 0x%x, exposure: 0x%x", __func__, gain, exposure);
	u16 vts = 0;
/*	
	if(s5k4e1gx_foxconn_sensor.vts_change == 1)
	{
		vts = s5k4e1gx_foxconn_sensor.vts_value;
		s5k4e1gx_foxconn_write_reg(S5K4E1GX_FOXCONN_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
		s5k4e1gx_foxconn_write_reg(S5K4E1GX_FOXCONN_VTS_REG_L, vts & 0xff, 0x00);
		s5k4e1gx_foxconn_sensor.vts_change = 0;
	}
*/	
	gain = gain << 1;

	s5k4e1gx_foxconn_write_reg(S5K4E1GX_FOXCONN_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	s5k4e1gx_foxconn_write_reg(S5K4E1GX_FOXCONN_GAIN_REG_L, gain & 0xff, 0x00);

	exposure = exposure >> 4;
	//print_info("enter %s, expo:%d", __func__, exposure);
	s5k4e1gx_foxconn_write_reg(S5K4E1GX_FOXCONN_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	s5k4e1gx_foxconn_write_reg(S5K4E1GX_FOXCONN_EXPOSURE_REG_L, exposure & 0xff, 0x00);

	s5k4e1gx_foxconn_write_reg(0x0104, 0x00, 0x00);//hold off
}

void s5k4e1gx_foxconn_set_exposure(u32 exposure)
{
	exposure = exposure >> 4;
	s5k4e1gx_foxconn_write_reg(S5K4E1GX_FOXCONN_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	s5k4e1gx_foxconn_write_reg(S5K4E1GX_FOXCONN_EXPOSURE_REG_L, exposure & 0xff, 0x00);
}

void s5k4e1gx_foxconn_set_vts(u16 vts)
{
	print_debug("Enter %s  ", __func__);
//	if(s5k4e1gx_foxconn_sensor.vts_change != 1)
//	{
	s5k4e1gx_foxconn_write_reg(S5K4E1GX_FOXCONN_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
	s5k4e1gx_foxconn_write_reg(S5K4E1GX_FOXCONN_VTS_REG_L, vts & 0xff, 0x00);
//	}
//	s5k4e1gx_foxconn_sensor.vts_value = vts;
}

/*
void s5k4e1gx_foxconn_set_vts_change(u16 change)
{
	print_info("Enter %s change=%d ", __func__,change);
	s5k4e1gx_foxconn_sensor.vts_change = change;
}
*/
u32 s5k4e1gx_foxconn_get_vts_reg_addr(void)
{
	return S5K4E1GX_FOXCONN_VTS_REG_H;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_reset;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_reset( camera_power_state power_state)
{
	print_info("%s  ", __func__);

	if (POWER_ON == power_state) {
		k3_isp_io_enable_mclk(MCLK_ENABLE, s5k4e1gx_foxconn_sensor.sensor_index);
		k3_ispgpio_reset_sensor(s5k4e1gx_foxconn_sensor.sensor_index, power_state,
			      s5k4e1gx_foxconn_sensor.power_conf.reset_valid);
		udelay(500);
	} else {
		k3_ispgpio_reset_sensor(s5k4e1gx_foxconn_sensor.sensor_index, power_state,
			      s5k4e1gx_foxconn_sensor.power_conf.reset_valid);
		udelay(10);
		k3_isp_io_enable_mclk(MCLK_DISABLE, s5k4e1gx_foxconn_sensor.sensor_index);
	}

	return 0;
}


/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_init;
 * Description : s5k4e1gx_foxconn init function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : Error code indicating success or failure;
 * Other       : NA;
 **************************************************************************
*/
static int s5k4e1gx_foxconn_init(void)
{
	static bool s5k4e1gx_check = false;
	print_debug("%s  ", __func__);

	if (false == s5k4e1gx_check) {
        if (check_suspensory_camera("S5K4E1GX") != 1) {
    		print_error("%s: product not have this sensor", __func__);
            return -ENODEV;     
        }       
        s5k4e1gx_check = true;
    }

	k3_ispio_power_init(S_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - sec camera*/
	//k3_ispio_power_init(S_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);		/*IO 1.8V - sec camera*/
	k3_ispio_power_init(S_CAMERA_CORE_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);	/*core 1.8V - sec camera*/


	return 0;
}

static u32 s5k4e1gx_get_override_param(camera_override_type_t type)
{
	u32 ret_val = sensor_override_params[type];

	switch (type) {
	case OVERRIDE_ISO_HIGH:
		ret_val = S5K4E1GX_MAX_ISO;
		break;

	case OVERRIDE_ISO_LOW:
		ret_val = S5K4E1GX_MIN_ISO;
		break;

	/* increase frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_LOW2MID:
		ret_val = S5K4E1GX_AUTOFPS_GAIN_LOW2MID;
		break;
	case OVERRIDE_AUTOFPS_GAIN_MID2HIGH:
		ret_val = S5K4E1GX_AUTOFPS_GAIN_MID2HIGH;
		break;

	/* reduce frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_MID2LOW:
		ret_val = S5K4E1GX_AUTOFPS_GAIN_MID2LOW;
		break;
	case OVERRIDE_AUTOFPS_GAIN_HIGH2MID:
		ret_val = S5K4E1GX_AUTOFPS_GAIN_HIGH2MID;
		break;

	case OVERRIDE_FPS_MAX:
		ret_val = S5K4E1GX_MAX_FRAMERATE;
		break;

    case OVERRIDE_FPS_MID:
		ret_val = S5K4E1GX_MID_FRAMERATE;
		break;

	case OVERRIDE_FPS_MIN:
		ret_val = S5K4E1GX_MIN_FRAMERATE;
		break;

	case OVERRIDE_CAP_FPS_MIN:
		ret_val = S5K4E1GX_MIN_CAP_FRAMERATE;
		break;

	case OVERRIDE_FLASH_TRIGGER_GAIN:
		ret_val = S5K4E1GX_FLASH_TRIGGER_GAIN;
		break;

	case OVERRIDE_SHARPNESS_PREVIEW:
		ret_val = S5K4E1GX_SHARPNESS_PREVIEW;
		break;

	case OVERRIDE_SHARPNESS_CAPTURE:
		ret_val = S5K4E1GX_SHARPNESS_CAPTURE;
		break;

	default:
		print_error("%s:not override or invalid type %d, use default",__func__, type);
		break;
	}

	return ret_val;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_exit;
 * Description : s5k4e1gx_foxconn exit function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void s5k4e1gx_foxconn_exit(void)
{
	print_debug("enter %s", __func__);

	k3_ispio_power_deinit();

	if (s5k4e1gx_foxconn_sensor.owner) {
		module_put(s5k4e1gx_foxconn_sensor.owner);
	}
	print_debug("exit %s", __func__);
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_shut_down;
 * Description : s5k4e1gx_foxconn shut down function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void s5k4e1gx_foxconn_shut_down(void)
{
	print_debug("enter %s", __func__);
	k3_ispgpio_power_sensor(&s5k4e1gx_foxconn_sensor, POWER_OFF);
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_set_default;
 * Description : init s5k4e1gx_foxconn_sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void s5k4e1gx_foxconn_set_default(void)
{
	s5k4e1gx_foxconn_sensor.init = s5k4e1gx_foxconn_init;
	s5k4e1gx_foxconn_sensor.exit = s5k4e1gx_foxconn_exit;
	s5k4e1gx_foxconn_sensor.shut_down = s5k4e1gx_foxconn_shut_down;
	s5k4e1gx_foxconn_sensor.reset = s5k4e1gx_foxconn_reset;
	s5k4e1gx_foxconn_sensor.check_sensor = s5k4e1gx_foxconn_check_sensor;
	s5k4e1gx_foxconn_sensor.power = s5k4e1gx_foxconn_power;
	s5k4e1gx_foxconn_sensor.init_reg = s5k4e1gx_foxconn_init_reg;
	s5k4e1gx_foxconn_sensor.init_isp_reg = s5k4e1gx_foxconn_init_isp_reg;
	s5k4e1gx_foxconn_sensor.stream_on = s5k4e1gx_foxconn_stream_on;

	s5k4e1gx_foxconn_sensor.get_format = s5k4e1gx_foxconn_get_format;
	s5k4e1gx_foxconn_sensor.set_flash = NULL;
	s5k4e1gx_foxconn_sensor.get_flash = NULL;
	s5k4e1gx_foxconn_sensor.set_scene = NULL;
	s5k4e1gx_foxconn_sensor.get_scene = NULL;

	s5k4e1gx_foxconn_sensor.enum_framesizes = s5k4e1gx_foxconn_enum_framesizes;
	s5k4e1gx_foxconn_sensor.try_framesizes = s5k4e1gx_foxconn_try_framesizes;
	s5k4e1gx_foxconn_sensor.set_framesizes = s5k4e1gx_foxconn_set_framesizes;
	s5k4e1gx_foxconn_sensor.get_framesizes = s5k4e1gx_foxconn_get_framesizes;

	if(E_CAMERA_SENSOR_FLIP_TYPE_H_V == get_secondary_sensor_flip_type()) {
    	s5k4e1gx_foxconn_sensor.sensor_rgb_type = SENSOR_GBRG;
    } else {
    	s5k4e1gx_foxconn_sensor.sensor_rgb_type = SENSOR_GRBG;
    }
	s5k4e1gx_foxconn_sensor.update_flip = s5k4e1gx_update_flip;

	s5k4e1gx_foxconn_sensor.enum_frame_intervals = s5k4e1gx_foxconn_enum_frame_intervals;
	s5k4e1gx_foxconn_sensor.try_frame_intervals = NULL;
	s5k4e1gx_foxconn_sensor.set_frame_intervals = NULL;
	s5k4e1gx_foxconn_sensor.get_frame_intervals = NULL;

	s5k4e1gx_foxconn_sensor.get_capability = NULL;

	strcpy(s5k4e1gx_foxconn_sensor.info.name,"s5k4e1gx_foxconn");
	s5k4e1gx_foxconn_sensor.interface_type = MIPI2;
	s5k4e1gx_foxconn_sensor.mipi_lane_count = CSI_LINES_2;
	s5k4e1gx_foxconn_sensor.mipi_index = CSI_INDEX_1;
	s5k4e1gx_foxconn_sensor.sensor_index = CAMERA_SENSOR_SECONDARY;
	s5k4e1gx_foxconn_sensor.skip_frames = 2; 

	s5k4e1gx_foxconn_sensor.power_conf.pd_valid = LOW_VALID;
	s5k4e1gx_foxconn_sensor.power_conf.reset_valid = LOW_VALID;
	s5k4e1gx_foxconn_sensor.power_conf.vcmpd_valid = LOW_VALID;

	s5k4e1gx_foxconn_sensor.i2c_config.index = I2C_SECONDARY;
	s5k4e1gx_foxconn_sensor.i2c_config.speed = I2C_SPEED_400;
	s5k4e1gx_foxconn_sensor.i2c_config.addr = S5K4E1GX_FOXCONN_SLAVE_ADDRESS;
	s5k4e1gx_foxconn_sensor.i2c_config.addr_bits = I2C_16BIT;
	s5k4e1gx_foxconn_sensor.i2c_config.val_bits = I2C_8BIT;

	s5k4e1gx_foxconn_sensor.preview_frmsize_index = 0;
	s5k4e1gx_foxconn_sensor.capture_frmsize_index = 0;
	s5k4e1gx_foxconn_sensor.frmsize_list = s5k4e1gx_foxconn_framesizes;
	s5k4e1gx_foxconn_sensor.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW10;
	s5k4e1gx_foxconn_sensor.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW10;
#ifdef S5K4ELGX_FOXCONN_AP_WRITEAE_MODE
	s5k4e1gx_foxconn_sensor.aec_addr[0] = 0;
	s5k4e1gx_foxconn_sensor.aec_addr[1] = 0;
	s5k4e1gx_foxconn_sensor.aec_addr[2] = 0;
	s5k4e1gx_foxconn_sensor.agc_addr[0] = 0;
	s5k4e1gx_foxconn_sensor.agc_addr[1] = 0;
	s5k4e1gx_foxconn_sensor.ap_writeAE_delay = 0;
#else
	s5k4e1gx_foxconn_sensor.aec_addr[0] = 0x0000;
	s5k4e1gx_foxconn_sensor.aec_addr[1] = 0x0202;
	s5k4e1gx_foxconn_sensor.aec_addr[2] = 0x0203;
	s5k4e1gx_foxconn_sensor.agc_addr[0] = 0x0204;
	s5k4e1gx_foxconn_sensor.agc_addr[1] = 0x0205;
#endif
	s5k4e1gx_foxconn_sensor.sensor_type = SENSOR_LIKE_SONY;
	s5k4e1gx_foxconn_sensor.set_exposure_gain = s5k4e1gx_foxconn_set_exposure_gain;

	s5k4e1gx_foxconn_sensor.set_gain = s5k4e1gx_foxconn_set_gain;
	s5k4e1gx_foxconn_sensor.set_exposure = s5k4e1gx_foxconn_set_exposure;
//	s5k4e1gx_foxconn_sensor.set_vts_change =  s5k4e1gx_foxconn_set_vts_change;

	s5k4e1gx_foxconn_sensor.set_vts =  s5k4e1gx_foxconn_set_vts;
	s5k4e1gx_foxconn_sensor.get_vts_reg_addr = s5k4e1gx_foxconn_get_vts_reg_addr;

	s5k4e1gx_foxconn_sensor.get_override_param = s5k4e1gx_get_override_param;

	s5k4e1gx_foxconn_sensor.sensor_gain_to_iso = NULL;
	s5k4e1gx_foxconn_sensor.sensor_iso_to_gain = NULL;

	s5k4e1gx_foxconn_sensor.get_sensor_aperture = NULL;
	s5k4e1gx_foxconn_sensor.get_equivalent_focus = NULL;

	s5k4e1gx_foxconn_sensor.isp_location = CAMERA_USE_K3ISP;
	s5k4e1gx_foxconn_sensor.sensor_tune_ops = NULL;

	s5k4e1gx_foxconn_sensor.af_enable = 0;

	s5k4e1gx_foxconn_sensor.image_setting.lensc_param = s5k4e1gx_foxconn_lensc_param;
	s5k4e1gx_foxconn_sensor.image_setting.ccm_param = s5k4e1gx_foxconn_ccm_param;
	s5k4e1gx_foxconn_sensor.image_setting.awb_param = s5k4e1gx_foxconn_awb_param;

	s5k4e1gx_foxconn_sensor.set_effect = NULL;

	s5k4e1gx_foxconn_sensor.fps_max = 30;
	s5k4e1gx_foxconn_sensor.fps_min = 16;
	s5k4e1gx_foxconn_sensor.fps = 25;

	s5k4e1gx_foxconn_sensor.owner = THIS_MODULE;

	s5k4e1gx_foxconn_sensor.info.facing = CAMERA_FACING_BACK;
	s5k4e1gx_foxconn_sensor.info.orientation = 270;
	s5k4e1gx_foxconn_sensor.info.focal_length = 238; /* 2.38mm*/
	s5k4e1gx_foxconn_sensor.info.h_view_angle = 66; /*  66.1 degree */
	s5k4e1gx_foxconn_sensor.info.v_view_angle = 50;
	s5k4e1gx_foxconn_sensor.lane_clk = CLK_500M;
	s5k4e1gx_foxconn_sensor.hflip = 0;
	s5k4e1gx_foxconn_sensor.vflip = 0;
	s5k4e1gx_foxconn_sensor.old_flip = 0;
    s5k4e1gx_foxconn_sensor.effect = &effect_s5k4e1gx_foxconn;
	s5k4e1gx_foxconn_sensor.support_summary = false;
//	s5k4e1gx_foxconn_sensor.vts_change = 0;
    s5k4e1gx_foxconn_sensor.set_hflip = s5k4e1gx_foxconn_set_hflip;
	s5k4e1gx_foxconn_sensor.get_hflip = s5k4e1gx_foxconn_get_hflip;
	s5k4e1gx_foxconn_sensor.set_vflip = s5k4e1gx_foxconn_set_vflip;
	s5k4e1gx_foxconn_sensor.get_vflip = s5k4e1gx_foxconn_get_vflip;
	s5k4e1gx_foxconn_sensor.get_capability = s5k4e1gx_get_capability;

	s5k4e1gx_foxconn_sensor.isp_idi_skip = false;
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int s5k4e1gx_foxconn_module_init(void)
{
	s5k4e1gx_foxconn_set_default();
	return register_camera_sensor(s5k4e1gx_foxconn_sensor.sensor_index, &s5k4e1gx_foxconn_sensor);
}

/*
 **************************************************************************
 * FunctionName: s5k4e1gx_foxconn_module_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void __exit s5k4e1gx_foxconn_module_exit(void)
{
	unregister_camera_sensor(s5k4e1gx_foxconn_sensor.sensor_index, &s5k4e1gx_foxconn_sensor);
}

MODULE_AUTHOR("Hisilicon");
module_init(s5k4e1gx_foxconn_module_init);
module_exit(s5k4e1gx_foxconn_module_exit);
MODULE_LICENSE("GPL");

/********************************** END **********************************************/
