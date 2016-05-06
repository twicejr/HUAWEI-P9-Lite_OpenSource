/*
 *  sonyimx328 camera driver source file
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
#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <asm/div64.h>
#include "sensor_common.h"
#include "sonyimx328_171.h"
#include <asm/bug.h>
#include <linux/device.h>
#include "video_config.h"
#include "effect.h"

#define LOG_TAG "IMX328_SUNNY_171"
/* #define DEBUG_DEBUG 1 */
#include "cam_log.h"
#include <cam_util.h>

#define _IS_DEBUG_AE	0

#define  SONYIMX328_MAX_ISO 			1550
#define SONYIMX328_MIN_ISO                      100

/* support 3 level framerate now, if mid fps same as min, set to 2 level framerate */
#define SONYIMX328_AUTOFPS_GAIN_HIGH2MID		0x60
#define SONYIMX328_AUTOFPS_GAIN_MID2LOW		    0x60
#define SONYIMX328_AUTOFPS_GAIN_LOW2MID		    0x24
#define SONYIMX328_AUTOFPS_GAIN_MID2HIGH		0x24

#define SONYIMX328_MAX_FRAMERATE         30
#define SONYIMX328_MID_FRAMERATE		 14
#define SONYIMX328_MIN_FRAMERATE          14
#define SONYIMX328_MIN_CAP_FRAMERATE  4
#define SONYIMX328_FLASH_TRIGGER_GAIN 0xff

#define SONYIMX328_SHARPNESS_PREVIEW  0x30
#define SONYIMX328_SHARPNESS_CAPTURE  0x08

#define SONYIMX328_ZSL_MODE            (0x00)

#define SONYIMX328_SLAVE_ADDRESS		0x20

#define SONYIMX328_CHIP_ID				(0x0091)
#define SONYIMX328_I2C_RETRY_TIMES      3

//#define SONYIMX328_CAM_MODULE_SKIPFRAME     4

#define SONYIMX328_FLIP						(0x0101)

#define SONYIMX328_VTS_REG_H					(0x0340)
#define SONYIMX328_VTS_REG_L					(0x0341)

#define SONYIMX328_AP_WRITEAE_MODE
#define SONYIMX328_MAX_ANALOG_GAIN			8
#define SONYIMX328_MAX_DIGITAL_GAIN			16

#define SONYIMX328_APERTURE_FACTOR          200

#define SONYIMX328_GROUP_HOLD_FUNCTION_REG	(0x0104)

#define SONYIMX328_EXPOSURE_REG_H		(0x0202)
#define SONYIMX328_EXPOSURE_REG_L		(0x0203)
//#define SONYIMX328_ANA_GAIN_REG_H		(0x0204)
#define SONYIMX328_ANA_GAIN_REG_L		(0x0205)
#define SONYIMX328_DIG_GAIN_GR_REG_H 	(0x020E)
#define SONYIMX328_DIG_GAIN_GR_REG_L 	(0x020F)
#define SONYIMX328_DIG_GAIN_GB_REG_H 	(0x0214)
#define SONYIMX328_DIG_GAIN_GB_REG_L 	(0x0215)
#define SONYIMX328_DIG_GAIN_R_REG_H         (0x0210)
#define SONYIMX328_DIG_GAIN_R_REG_L     	(0x0211)
#define SONYIMX328_DIG_GAIN_B_REG_H    	(0x0212)
#define SONYIMX328_DIG_GAIN_B_REG_L    	(0x0213)

#define SONYIMX328_ISO	(\
				(1 << CAMERA_ISO_AUTO) | \
				(1 << CAMERA_ISO_100) | \
				(1 << CAMERA_ISO_200) | \
				(1 << CAMERA_ISO_400) | \
				(1 << CAMERA_ISO_800) | \
				(1 << CAMERA_ISO_1600) \
			)


#define DIGITAL_GAIN_CALC_BASE 0x1000
#define DIGITAL_GAIN_BASE 0x100

typedef struct {
	u32 rgain;
	u32 ggain;
	u32 bgain;
} awb_gain;

static awb_gain dgain_base = {
	DIGITAL_GAIN_BASE, DIGITAL_GAIN_BASE, DIGITAL_GAIN_BASE};

#ifdef IMX328_171_OTP
#define OTP_SLAVE_ADDR1       0xA0
#define OTP_SLAVE_ADDR2       0xAC

#define OTP_ID_REG 		      0x00
#define OTP_AWB_REG 	      0x05
#define OTP_VCM_REG 	      0x00
#define OTP_CHECKSUM_REG      0x05

#define SONYIMX328_OTP_ID_READ	       (1 << 0)
#define SONYIMX328_OTP_VCM_READ       (1 << 1)
#define SONYIMX328_OTP_AWB_READ       (1 << 2)
#define SONYIMX328_OTP_CHECKSUM_READ  (1 << 3)
#define SONYIMX328_OTP_CHECKSUM_ERR   (1 << 4)
#define SONYIMX328_OTP_FAIL_FLAG      (1 << 5)

#define SONYIMX328_MODULE_VENDOR_ID    0x01//SUNNY
#define SONYIMX328_MODULE_HUAWEI_ID    0xAB//23060171

static awb_gain awb_gain_typical[] = {
	{0xe9d, 0x794, 0xaf5}, //sunny
};

typedef struct sonyimx328_otp_struct_type {
	u32 rgain;
	u32 bgain;
	u32 ggain;
	u16 vcm_start;
	u16 vcm_end;
}sonyimx328_otp_struct;

static sonyimx328_otp_struct sonyimx328_otp;

static u32 OTPSUMVAL         = 0;
static u8  sonyimx328_otp_flag  = 0;

extern int  ispv1_read_sensor_byte_addr8(i2c_index_t index, u8 i2c_addr, u16 reg, u16 *val, i2c_length length);
static bool sonyimx328_get_otp_from_sensor(void);
static void sonyimx328_otp_get_vcm(u16 *vcm_start, u16 *vcm_end);
//static void sonyimx328_otp_set_awb(void);
static int sonyimx328_calc_digital_gain_base(awb_gain *dgain);
#endif

static camera_capability sonyimx328_cap[] = {
	{V4L2_CID_FLASH_MODE, THIS_FLASH},
	{V4L2_CID_FOCUS_MODE, THIS_FOCUS_MODE},
	{V4L2_CID_ISO, SONYIMX328_ISO},
	{V4L2_CID_FOCAL_LENGTH, 368},//3.68mm
	{V4L2_CID_ZSL,SONYIMX328_ZSL_MODE} ,
};

typedef enum _sonyimx328_sensor_check
{
  IMX328_UNKOWN = -1,
  IMX328_FOUND,
}sonyimx328_sensor_check;

/*
 * should be calibrated, three lights, from 0x1c264
 * here is long exposure
 */
static char sonyimx328_lensc_param[86*3] = {
};

/* should be calibrated, 6 groups 3x3, from 0x1c1d8 */
static short sonyimx328_ccm_param[54] = {
};

static char sonyimx328_awb_param[] = {
};

static vcm_info_s vcm_dw9714_param = {
    #include "vcm_dw9714_sunny171.h"
};

static effect_params effect_imx328_sunny = {
#include "effect_imx328_sunny171.h"
};

static awb_gain_t flash_platform_awb[] = {
	{0xbd, 0x80, 0x80, 0xdc},
};

static const struct _sensor_reg_t sonyimx328_stream_off_regs[] = {
	{0x0100, 0x00}
};

static framesize_s sonyimx328_framesizes[] = {
	{0, 0, 2080, 1560, 4620, 1632, 30, 30, 0x1EA, 0x198, 0x100, VIEW_FULL, RESOLUTION_4_3, false, false,{sonyimx328_framesize_quater, ARRAY_SIZE(sonyimx328_framesize_quater)}, CLK_300M },
	{0, 0, 4160, 3120, 4620, 3290, 10, 10, 0x152, 0x11A, 0xB1, VIEW_FULL, RESOLUTION_4_3, false, false,{sonyimx328_framesize_fullsize_nonzsl, ARRAY_SIZE(sonyimx328_framesize_fullsize_nonzsl)}, CLK_400M},	
};


/******************************************/

static camera_sensor sonyimx328_sensor;
static void sonyimx328_set_default(void);
static void sonyimx328_config_dphy_clk(camera_state state);

/*
 **************************************************************************
 * FunctionName: sonyimx328_read_reg;
 * Description : read sonyimx328 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_read_reg(u16 reg, u8 *val)
{
	return k3_ispio_read_reg(sonyimx328_sensor.i2c_config.index,
			sonyimx328_sensor.i2c_config.addr, reg, (u16 *)val, sonyimx328_sensor.i2c_config.val_bits,sonyimx328_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_write_reg;
 * Description : write sonyimx328 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_write_reg(u16 reg, u8 val, u8 mask)
{
	return k3_ispio_write_reg(sonyimx328_sensor.i2c_config.index,
			sonyimx328_sensor.i2c_config.addr, reg, val, sonyimx328_sensor.i2c_config.val_bits, mask,sonyimx328_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_write_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int sonyimx328_write_seq(const struct _sensor_reg_t *seq, u32 size, u8 mask)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	return k3_ispio_write_seq(sonyimx328_sensor.i2c_config.index,
			sonyimx328_sensor.i2c_config.addr, seq, size, sonyimx328_sensor.i2c_config.val_bits, mask,sonyimx328_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_write_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void sonyimx328_write_isp_seq(const struct isp_reg_t *seq, u32 size)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	k3_ispio_write_isp_seq(seq, size);
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_enum_frame_intervals;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_enum_frame_intervals(struct v4l2_frmivalenum *fi)
{
	assert(fi);

	if(NULL == fi) {
		return -EINVAL;
	}

	print_debug("enter %s", __func__);
	if (fi->index >= CAMERA_MAX_FRAMERATE)
		return -EINVAL;

	fi->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fi->discrete.numerator = 1;
	fi->discrete.denominator = (fi->index+1);
	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_get_format;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_get_format(struct v4l2_fmtdesc *fmt)
{
	if (fmt->type == V4L2_BUF_TYPE_VIDEO_OVERLAY)
		fmt->pixelformat = sonyimx328_sensor.fmt[STATE_PREVIEW];
	else
		fmt->pixelformat = sonyimx328_sensor.fmt[STATE_CAPTURE];

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_enum_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 max_index = ARRAY_SIZE(camera_framesizes) - 1;
	u32 this_max_index =    ARRAY_SIZE(sonyimx328_framesizes) -1;

	assert(framesizes);

	if(NULL == framesizes) {
		return -EINVAL;
	}

	print_debug("enter %s; ", __func__);

	if (framesizes->index > max_index) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	if ((camera_framesizes[framesizes->index].width > sonyimx328_framesizes[this_max_index].width)
		|| (camera_framesizes[framesizes->index].height > sonyimx328_framesizes[this_max_index].height)) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	framesizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	framesizes->discrete.width = sonyimx328_framesizes[this_max_index].width;
	framesizes->discrete.height = sonyimx328_framesizes[this_max_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_try_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_try_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	int max_index = ARRAY_SIZE(sonyimx328_framesizes) -1;
       assert(framesizes);

       if(NULL == framesizes) {
	   	return -EINVAL;
	}
	
	print_debug("Enter Function:%s  ", __func__);

	if ((framesizes->discrete.width <= sonyimx328_framesizes[max_index].width)
	    && (framesizes->discrete.height <= sonyimx328_framesizes[max_index].height)) {
	         print_debug("===========width = %d", framesizes->discrete.width);
	         print_debug("===========height = %d", framesizes->discrete.height);
	         return 0;
	}

	print_error("frame size too large, [%d,%d]",
              framesizes->discrete.width, framesizes->discrete.height);
	
       return -EINVAL;
}

/***************************************************************************
* FunctionName: sonyimx328_set_framesizes;
* Description : NA;
* Input       : flag: if 1, set framesize to sensor,
*		if 0, only store framesize to camera_interface;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
 ***
***********************************************************************
*/
static int sonyimx328_set_framesizes(camera_state state,
                struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type,bool zsl_preview)
{
    int i = 0;
    bool match = false;
    int size = 0;
	
    assert(fs);
    
    if(NULL == fs){
		return -EINVAL;
    }
    
    print_info("Enter Function:%s State(%d), flag=%d, width=%d, height=%d",
               __func__, state, flag, fs->width, fs->height);
 
    size = ARRAY_SIZE(sonyimx328_framesizes);
    if(VIEW_FULL == view_type) {
		for (i = 0; i < ARRAY_SIZE(sonyimx328_framesizes); i++) {
                   if ((zsl_preview == false) && sonyimx328_framesizes[i].zsl_only )
                   {
                        continue;
                   }
				
                   if ((sonyimx328_framesizes[i].width >= fs->width)
                      && (sonyimx328_framesizes[i].height >= fs->height)
                      && (VIEW_FULL == sonyimx328_framesizes[i].view_type)
                      && (camera_get_resolution_type(fs->width, fs->height)
                      <= sonyimx328_framesizes[i].resolution_type)) {
                         fs->width = sonyimx328_framesizes[i].width;
                         fs->height = sonyimx328_framesizes[i].height;
                         match = true;
                         break;
                   }
		}
	}

	if (false == match) {
		for (i = 0; i < size; i++) {
			if ((zsl_preview == false) && sonyimx328_framesizes[i].zsl_only )
			{
			    continue;
			}
			if ((sonyimx328_framesizes[i].width >= fs->width)
			    && (sonyimx328_framesizes[i].height >= fs->height)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= sonyimx328_framesizes[i].resolution_type)){
				fs->width = sonyimx328_framesizes[i].width;
				fs->height = sonyimx328_framesizes[i].height;
				break;
			}
		}
	}

	if (i >= size) {
		print_error("request resolution larger than sensor's max resolution");
		return -EINVAL;
	}

	if (state == STATE_PREVIEW)
		sonyimx328_sensor.preview_frmsize_index = i;
	else
		sonyimx328_sensor.capture_frmsize_index = i;

       print_info("Enter Function:%s  preview index =%d, capture=%d ", __func__, sonyimx328_sensor.preview_frmsize_index, sonyimx328_sensor.capture_frmsize_index);
	return 0;
}
/*
 **************************************************************************
 * FunctionName: sonyimx328_init_isp_reg;
 * Description : load initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_init_isp_reg(void)
{
	int size = 0;
	camera_sensor *sensor = &sonyimx328_sensor;

	size = CAMERA_MAX_SETTING_SIZE;
	sonyimx328_write_isp_seq(sensor->effect->isp_settings, size);

	return 0;
}
/*
 **************************************************************************
 * FunctionName: sonyimx328_get_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_get_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs)
{
	int frmsize_index;

	assert(fs);

	if(NULL == fs){
		return -EINVAL;
	}

	if (state == STATE_PREVIEW)
		frmsize_index = sonyimx328_sensor.preview_frmsize_index;
	else if (state == STATE_CAPTURE)
		frmsize_index = sonyimx328_sensor.capture_frmsize_index;
	else
		return -EINVAL;

	fs->width = sonyimx328_framesizes[frmsize_index].width;
	fs->height = sonyimx328_framesizes[frmsize_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_init_reg;
 * Description : download initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_init_reg(void)
{
	int size = 0;
	print_debug("Enter Function:%s  , initsize=%d",
		    __func__, sizeof(sonyimx328_init_regs));

	if (0 != k3_ispio_init_csi(sonyimx328_sensor.mipi_index,
			sonyimx328_sensor.mipi_lane_count, sonyimx328_sensor.lane_clk)) {
		return -EFAULT;
	}


	size = ARRAY_SIZE(sonyimx328_init_regs);
	if (0 != sonyimx328_write_seq(sonyimx328_init_regs, size, 0x00)) {
		print_error("line %d, fail to init sonyimx328 sensor", __LINE__);
		return -EFAULT;
	}

	return 0;
}

static int sonyimx328_set_hflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);
	sonyimx328_sensor.hflip = flip;
	return 0;
}
static int sonyimx328_get_hflip(void)
{
	print_debug("enter %s", __func__);

	return sonyimx328_sensor.hflip;
}
static int sonyimx328_set_vflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);

	sonyimx328_sensor.vflip = flip;

	return 0;
}
static int sonyimx328_get_vflip(void)
{
	print_debug("enter %s", __func__);
	return sonyimx328_sensor.vflip;
}
static int sonyimx328_update_flip(u16 width, u16 height)
{
	u8 new_flip = ((sonyimx328_sensor.vflip << 1) | sonyimx328_sensor.hflip);
	print_info("Enter %s   new_flip 0x%x ", __func__, new_flip);

	if (sonyimx328_sensor.old_flip != new_flip) {
	     k3_ispio_update_flip((sonyimx328_sensor.old_flip ^ new_flip) & 0x03, width, height, PIXEL_ORDER_CHANGED);

	     sonyimx328_sensor.old_flip = new_flip;

	     sonyimx328_write_reg(SONYIMX328_FLIP, sonyimx328_sensor.vflip ? 0x00 : 0x02, ~0x02);
	     sonyimx328_write_reg(SONYIMX328_FLIP, sonyimx328_sensor.hflip ? 0x00 : 0x01, ~0x01);
	}

	return 0;
}

static int sonyimx328_get_capability(u32 id, u32 *value)
{
	int i;
	for (i = 0; i < sizeof(sonyimx328_cap) / sizeof(sonyimx328_cap[0]); ++i) {
		if (id == sonyimx328_cap[i].id) {
			*value = sonyimx328_cap[i].value;
			break;
		}
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_framesize_switch;
 * Description : switch frame size, used by preview and capture
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_framesize_switch(camera_state state)
{
	u8 next_frmsize_index;

	if (state == STATE_PREVIEW)
		next_frmsize_index = sonyimx328_sensor.preview_frmsize_index;
	else
		next_frmsize_index = sonyimx328_sensor.capture_frmsize_index;

	print_debug("Enter Function:%s frm index=%d", __func__, next_frmsize_index);

	if (next_frmsize_index >= ARRAY_SIZE(sonyimx328_framesizes)) {
		print_error("Unsupport sensor setting index: %d", next_frmsize_index);
		return -ETIME;
	}

	if (0 != sonyimx328_write_seq(sonyimx328_sensor.frmsize_list[next_frmsize_index].sensor_setting.setting
		, sonyimx328_sensor.frmsize_list[next_frmsize_index].sensor_setting.seq_size, 0x00)) {
		print_error("fail to init sonyimx328 sensor");
		return -ETIME;
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_stream_on;
 * Description : download preview seq for sensor preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_stream_on(camera_state state)
{
	print_debug("Enter Function:%s ", __func__);
	sonyimx328_config_dphy_clk(state);
	return sonyimx328_framesize_switch(state);
}

/*  **************************************************************************
* FunctionName: sonyimx328_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int sonyimx328_check_sensor(void)
{
	u8 idl = 0x1;
	u8 idh = 0x1;
	u16 id = 0;
       #ifdef IMX328_171_OTP
	bool retVal = false;
	#endif
	camera_sensor *sensor = &sonyimx328_sensor;
	int retry = 0;

       for (retry = 0; retry <SONYIMX328_I2C_RETRY_TIMES; retry++)
       {
	    sonyimx328_read_reg(0x0000, &idh);
	    sonyimx328_read_reg(0x0001, &idl);

	    id = ((idh << 8) | idl);
	    print_info("sonyimx328 product id:0x%x retry times:%d", id, retry);
	    if (SONYIMX328_CHIP_ID == id)
		{
			break;
		}
		udelay(100);
       }

	if (SONYIMX328_CHIP_ID != id) {
		print_error("Invalid product id ,Could not load sensor sonyimx328");
		return -ENODEV;
	}

	sonyimx328_sensor.vcm = &vcm_dw9714_param;
	sensor->effect = &effect_imx328_sunny;

	#ifdef IMX328_171_OTP
	retVal = sonyimx328_get_otp_from_sensor();
	if(true != retVal){
		print_error("%s  return false for OTP FAIL\n",__func__);
	}
	else{
	    sonyimx328_calc_digital_gain_base(&dgain_base);
	}
	sonyimx328_sensor.vcm->get_vcm_otp = sonyimx328_otp_get_vcm;
	#endif

	return 0;
}

/****************************************************************************
* FunctionName: sonyimx328_power;
* Description : NA;
* Input       : power state of camera;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int sonyimx328_power(camera_power_state power)
{
	int ret = 0;

	if(power == POWER_ON) {
		k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);	
		k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);
		
		udelay(200);
		k3_ispio_ioconfig(&sonyimx328_sensor, power);
		k3_ispgpio_power_sensor(&sonyimx328_sensor, power);
		msleep(3);
	} else{
		k3_ispio_deinit_csi(sonyimx328_sensor.mipi_index);
		k3_ispgpio_power_sensor(&sonyimx328_sensor, power);
		k3_ispio_ioconfig(&sonyimx328_sensor, power);
		k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);
		udelay(200);
		k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);
		udelay(500);
	}
	return ret;
}

static int sonyimx328_get_sensor_aperture(void)
{
	return SONYIMX328_APERTURE_FACTOR;
}

/*
 * Here gain is in unit 1/16 of sensor gain,
 * y36721 todo, temporarily if sensor gain=0x10, ISO is 100
 * in fact we need calibrate an ISO-ET-gain table.
 */
static u32 sonyimx328_gain_to_iso(int gain)
{
	return (u32)((gain * 100) / 0x10);
}

static u32 sonyimx328_iso_to_gain(int iso)
{
	return (u32)((iso * 0x10) / 100);
}

static void sonyimx328_set_exposure_gain(u32 exposure, u32 gain)
{
	u32  analog_gain = 0;
	u32	 tmp_digital_gain = 0;
	u8    digital_ratio = 0;
	u8    digital_h = 0;
	u8    digital_l = 0;
	u32 digital_gain_r, digital_gain_g, digital_gain_b;

	sonyimx328_write_reg(SONYIMX328_GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold

	if ((gain == 0) || (gain >= SONYIMX328_MAX_ANALOG_GAIN * SONYIMX328_MAX_DIGITAL_GAIN * 16))
	{
	       print_error("%s set gain error, gain value 0x%x", __func__, gain);
		goto out;
	}

	if(gain > SONYIMX328_MAX_ANALOG_GAIN*16)
	{
		/*tmp_digital_gain*256 is keep the decimal part*/
		tmp_digital_gain = (gain*256) >> 4;
		tmp_digital_gain = tmp_digital_gain >> 3;

		digital_ratio = (gain/SONYIMX328_MAX_ANALOG_GAIN) >> 4;
		digital_h = digital_ratio;
		digital_l = tmp_digital_gain - digital_ratio*256;
		analog_gain = SONYIMX328_MAX_ANALOG_GAIN*16;
	}
	else
	{
		analog_gain = gain;
		digital_h = 1;
		digital_l = 0;
	}

	/* re-calculate digital gain */
	digital_gain_r = ((digital_h<<8) | digital_l) * dgain_base.rgain / 0x100;
	digital_gain_g = ((digital_h<<8) | digital_l) * dgain_base.ggain / 0x100;
	digital_gain_b = ((digital_h<<8) | digital_l) * dgain_base.bgain / 0x100;

       /* digital gain high bit max is 0xf */
	if(((digital_gain_r >> 8) > 0xf) || ((digital_gain_g >> 8) > 0xf) || ((digital_gain_b >> 8) > 0xf))
	{
              print_error("%s digital gain error,  digital_h 0x%x digital_l 0x%x dgain_base[r 0x%x g 0x%x b 0x%x]",
		                    __func__, digital_h, digital_l, dgain_base.rgain, dgain_base.ggain, dgain_base.bgain);
		goto out;
	}

	exposure >>= 4; //isp2.2 exposure = register_value/0x10

	sonyimx328_write_reg(SONYIMX328_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_EXPOSURE_REG_L, exposure & 0xff, 0x00);

	analog_gain = 256 - (256 * 16) / analog_gain;
	sonyimx328_write_reg(SONYIMX328_ANA_GAIN_REG_L, analog_gain & 0xff, 0x00);
	
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_GR_REG_H, (digital_gain_g >> 8) & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_GR_REG_L, digital_gain_g & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_GB_REG_H, (digital_gain_g >> 8) & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_GB_REG_L, digital_gain_g & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_R_REG_H, (digital_gain_r >> 8) & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_R_REG_L, digital_gain_r & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_B_REG_H, (digital_gain_b >> 8) & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_B_REG_L, digital_gain_b & 0xff, 0x00);
out:
	sonyimx328_write_reg(SONYIMX328_GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release

	return;
}

#if 0
static void sonyimx328_set_exposure(u32 exposure)
{
	exposure >>= 4;
	sonyimx328_write_reg(SONYIMX328_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_EXPOSURE_REG_L, exposure & 0xff, 0x00);
}

static void sonyimx328_set_gain(u32 gain)
{
	u32  analog_gain = 0;
	u32	 tmp_digital_gain = 0;
	u8    digital_ratio = 0;
	u8    digital_h = 0;
	u8    digital_l = 0;
	u32 digital_gain_r, digital_gain_g, digital_gain_b;

	if(gain == 0)
		return ;

	if(gain > SONYIMX328_MAX_ANALOG_GAIN*16)
	{
		/*tmp_digital_gain*256 is keep the decimal part*/
		tmp_digital_gain = (gain*256) >> 4;
		tmp_digital_gain = tmp_digital_gain >> 3;

		digital_ratio = (gain/SONYIMX328_MAX_ANALOG_GAIN) >> 4;
		digital_h = digital_ratio;
		digital_l = tmp_digital_gain - digital_ratio*256;
		analog_gain = SONYIMX328_MAX_ANALOG_GAIN*16;
	}
	else
	{
		analog_gain = gain;
		digital_h = 1;
		digital_l = 0;
	}

	/* re-calculate digital gain */
	digital_gain_r = ((digital_h<<8) | digital_l) * dgain_base.rgain / 0x100;
	digital_gain_g = ((digital_h<<8) | digital_l) * dgain_base.ggain / 0x100;
	digital_gain_b = ((digital_h<<8) | digital_l) * dgain_base.bgain / 0x100;

	analog_gain = 256 - (256 * 16) / analog_gain;
	sonyimx328_write_reg(SONYIMX328_ANA_GAIN_REG_L, analog_gain & 0xff, 0x00);
	
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_GR_REG_H, (digital_gain_g >> 8) & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_GR_REG_L, digital_gain_g & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_GB_REG_H, (digital_gain_g >> 8) & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_GB_REG_L, digital_gain_g & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_R_REG_H, (digital_gain_r >> 8) & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_R_REG_L, digital_gain_r & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_B_REG_H, (digital_gain_b >> 8) & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_DIG_GAIN_B_REG_L, digital_gain_b & 0xff, 0x00);
}
#endif

static void sonyimx328_set_vts(u16 vts)
{
	print_debug("Enter %s  ", __func__);
	sonyimx328_write_reg(SONYIMX328_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
	sonyimx328_write_reg(SONYIMX328_VTS_REG_L, vts & 0xff, 0x00);
}

static u32 sonyimx328_get_vts_reg_addr(void)
{
	return SONYIMX328_VTS_REG_H;
}


#ifdef IMX328_171_OTP
/****************************************************************************
* FunctionName: sonyimx328_read_otp;
* Description : i2c api used to read information from eeprom.
* Input       : NA;
* Output      : sonyimx328_otp;
* ReturnValue : NONEl;
* Other       : NA;
***************************************************************************/
static void sonyimx328_read_otp(u8 i2c_addr,u16 reg,u8 *buf,u16 count)
{
	u16 i   = 0;
	int ret = 0;
	u16 val = 0;

	for(;i<count;i++) {
		ret =ispv1_read_sensor_byte_addr8(sonyimx328_sensor.i2c_config.index,i2c_addr,reg+i,&val,sonyimx328_sensor.i2c_config.val_bits);
		if(ret !=0)
			print_error("%s fail to read otp with error code %d, i2c_addr=0x%x reg_addr=0x%x\n", __func__,ret,i2c_addr,reg+i);

		buf[i] = (val&0xff);
		OTPSUMVAL += buf[i];

		//print_info("######OTPPrint~~~%s::I2CAddr=0x%x, RegAddr=0x%x, RegVal=0x%x ######\n", __func__, i2c_addr, reg+i, buf[i]);
	}

	return;
}

/****************************************************************************
* FunctionName: sonyimx328_otp_read_id;
* Description : Get id etc. parameters from eeprom.
* Input       : NA;
* Output      : sonyimx328_otp;
* ReturnValue : true-success,false-fail;
* Other       : NA;
***************************************************************************/
static bool sonyimx328_otp_read_id(void)
{
	u8 buf[5] = {0};
	u8 vendor_id = 0;

	sonyimx328_read_otp(OTP_SLAVE_ADDR1,OTP_ID_REG,buf,5);

	print_info("module info year 20%02d month %d day %d, SNO. 0x%x  vendor id&version 0x%x\n", buf[0],buf[1],buf[2],buf[3],buf[4]);

	vendor_id = (buf[4]>>4)&0x0F;

	//Sunny 0x01 & huaweiModuleCode is 23060167(0n167 = 0xA7)
	if((vendor_id == SONYIMX328_MODULE_VENDOR_ID) && (buf[3] == SONYIMX328_MODULE_HUAWEI_ID))
	{
		sonyimx328_otp_flag |= SONYIMX328_OTP_ID_READ;
		return true;
	} else {
		print_error("%s OTP data is worng for with wrong vender id!!!\n",__func__);
		return false;
	}
}

/****************************************************************************
* FunctionName: sonyimx328_otp_read_awb;
* Description : Get awb parameters from eeprom.
* Input       : NA;
* Output      : sonyimx328_otp;
* ReturnValue : true-success,false-fail;
* Other       : NA;
***************************************************************************/
static bool sonyimx328_otp_read_awb(void)
{
	u8  buf[8] = {0};

	sonyimx328_read_otp(OTP_SLAVE_ADDR1,OTP_AWB_REG,buf,8);

	print_info("%s OTP data are rgain_h=%x, rgain_1=%x, ggain_h=%x, ggain_l=%x, bgain_h=%x, bgain_l=%x!!!\n", __func__, buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);

	sonyimx328_otp.rgain = buf[2];
	sonyimx328_otp.rgain <<= 8;
	sonyimx328_otp.rgain += buf[3];
	sonyimx328_otp.ggain = buf[4];
	sonyimx328_otp.ggain <<= 8;
	sonyimx328_otp.ggain += buf[5];
	sonyimx328_otp.bgain = buf[6];
	sonyimx328_otp.bgain <<= 8;
	sonyimx328_otp.bgain += buf[7];
	print_info("%s OTP data are rgain=0x%x, ggain=0x%x, bgain=0x%x\n",__func__, sonyimx328_otp.rgain, sonyimx328_otp.ggain, sonyimx328_otp.bgain);

	if(0 == sonyimx328_otp.rgain || 0 ==sonyimx328_otp.ggain || 0 == sonyimx328_otp.bgain){//if awb value read is error for zero, abnormal branch deal
		print_error("%s OTP data is worng!!!\n",__func__);
		return false;
	}

	sonyimx328_otp_flag |= SONYIMX328_OTP_AWB_READ;

	return true;
}

/****************************************************************************
* FunctionName: sonyimx328_otp_read_vcm;
* Description : Get AF motor parameters from EEPROM.;
* Input       : NA;
* Output      : sonyimx328_otp;
* ReturnValue :ture-success,false-fail;
* Other       : NA;
***************************************************************************/
static bool sonyimx328_otp_read_vcm(void)
{
	u8  buf[4] = {0};
	u16 vcm_start = 0;
	u16 vcm_end =0;

	sonyimx328_read_otp(OTP_SLAVE_ADDR2,OTP_VCM_REG,buf,4);

	vcm_start = buf[0];
	vcm_start <<= 8;
	vcm_start += buf[1];
	vcm_end   = buf[2];
	vcm_end   <<= 8;
	vcm_end   += buf[3];

	if((vcm_end > vcm_start) && (vcm_start != 0) && ( vcm_end  != 0))
	{
		sonyimx328_otp_flag |= SONYIMX328_OTP_VCM_READ;
		sonyimx328_otp.vcm_start = vcm_start;
		sonyimx328_otp.vcm_end = vcm_end;
		print_info("%s vcm_start=0x%x, vcm_end=0x%x \n",__func__, sonyimx328_otp.vcm_start,sonyimx328_otp.vcm_end);
	} else {
	       //Abnormal branch deal
		sonyimx328_otp.vcm_start = 0;
		sonyimx328_otp.vcm_end = 0;
		print_error("%s VCM OTP data is worng! vcm_start=0x%x, vcm_end=0x%x\n",__func__, sonyimx328_otp.vcm_start,sonyimx328_otp.vcm_end);
		return false;
	}

	return true;
}

/****************************************************************************
* FunctionName: sonyimx328_otp_get_vcm;
* Description : Get vcm start and stop parameters read from OTP.;
* Input       : NA;
* Output      : vcm_start, vcm_end
* ReturnValue : NONE;
* Other       : NA;
***************************************************************************/
static void sonyimx328_otp_get_vcm(u16 *vcm_start, u16 *vcm_end)
{
       if( 0 != (sonyimx328_otp_flag & (SONYIMX328_OTP_FAIL_FLAG | SONYIMX328_OTP_CHECKSUM_ERR)))
       {
             sonyimx328_otp.vcm_start = 0;
	      sonyimx328_otp.vcm_end = 0;
       }

	if (0 == sonyimx328_otp.vcm_start) {
		*vcm_start = sonyimx328_sensor.vcm->infiniteDistance;
	} else {
            if (sonyimx328_otp.vcm_start > sonyimx328_sensor.vcm->startCurrentOffset)
                 *vcm_start = sonyimx328_otp.vcm_start - sonyimx328_sensor.vcm->startCurrentOffset;
            else
                 *vcm_start = 0;
	}

	if (0 == sonyimx328_otp.vcm_end) {
		*vcm_end = sonyimx328_sensor.vcm->normalDistanceEnd;
	} else {
		*vcm_end = sonyimx328_otp.vcm_end;
	}

	print_info("%s, vcm_start:%#x, vcm_end:%#x", __func__, *vcm_start, *vcm_end);
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_get_otp_from_sensor;
 * Description : the api to use sonyimx328 sensor module OTP function;
 * Input         : NULL;
 * Output       : the sonyimx328_otp;
 * ReturnValue : true-OTP can be used, false-OTP is error, cannot be used;
 * Other         : NA;
 **************************************************************************
*/
static bool sonyimx328_get_otp_from_sensor(void)
{
	u8   sum = 0;
	u8   otpCheckSumVal = 0;
	bool retVal = false;

	print_info("%s enters!\n",__func__);
	if((sonyimx328_otp_flag & SONYIMX328_OTP_FAIL_FLAG) == SONYIMX328_OTP_FAIL_FLAG) {//Just check OTP once whether success or not
		print_error("%s OTP data is worng, sonyimx328_otp_flag=0x%x\n", __func__,sonyimx328_otp_flag);
		return false;
	}else if((sonyimx328_otp_flag & SONYIMX328_OTP_CHECKSUM_READ) == SONYIMX328_OTP_CHECKSUM_READ){//branch for read success, no need read more
		print_info("%s OTP has been read success already, sonyimx328_otp_flag=0x%x\n", __func__,sonyimx328_otp_flag);
		return true;
	}

	sonyimx328_read_otp(OTP_SLAVE_ADDR2,OTP_CHECKSUM_REG,&otpCheckSumVal,1);
	if(otpCheckSumVal == 0xFF){
		print_error("%s OTP data has not flashed!\n", __func__);
		goto OTP_FAIL;
	}

	memset(&sonyimx328_otp,0,sizeof(sonyimx328_otp));//initial sonyimx328_otp

	retVal = sonyimx328_otp_read_id();
	if(false == retVal){
		print_error("%s sonyimx328_otp_read_id() failed!\n",__func__);
		goto OTP_FAIL;
	}

	retVal = sonyimx328_otp_read_awb();
	if(false == retVal){
		print_error("%s sonyimx328_otp_read_awb() failed!\n",__func__);
		goto OTP_FAIL;
	}

	retVal = sonyimx328_otp_read_vcm();
	if(false == retVal){
		print_error("%s sonyimx328_otp_read_vcm() failed!\n",__func__);
		goto OTP_FAIL;
	}

	sum = (OTPSUMVAL - otpCheckSumVal) % 0xff;

	if(otpCheckSumVal == sum){
		sonyimx328_otp_flag |= SONYIMX328_OTP_CHECKSUM_READ;
		print_info("%s success, OTPSUMVAL: %d, otpCheckSumVal: %d ,sum:%d, sonyimx328_otp_flag=0x%x\n", __func__, OTPSUMVAL, otpCheckSumVal,sum,sonyimx328_otp_flag);
		return true;
	} else {
		sonyimx328_otp_flag |= SONYIMX328_OTP_CHECKSUM_ERR;
		print_error("%s fail, OTPSUMVAL: %d, otpCheckSumVal: %d ,sum:%d \n", __func__, OTPSUMVAL, otpCheckSumVal,sum);
	}

OTP_FAIL:
	sonyimx328_otp_flag |= SONYIMX328_OTP_FAIL_FLAG;
	print_error("%s sonyimx328_otp_flag=0x%x \n", __func__,sonyimx328_otp_flag);
	return false;
}

static int sonyimx328_calc_digital_gain_base(awb_gain *dgain)
{
	unsigned int rg_ratio, bg_ratio;
	unsigned int rg_ratio_typical, bg_ratio_typical;

	if(0 == sonyimx328_otp.rgain || 0 == sonyimx328_otp.ggain || 0 == sonyimx328_otp.bgain) {
		print_error("%s otp value error.", __func__);
		return -1;
	}

	rg_ratio = DIGITAL_GAIN_CALC_BASE * sonyimx328_otp.rgain / sonyimx328_otp.ggain;
	bg_ratio = DIGITAL_GAIN_CALC_BASE * sonyimx328_otp.bgain / sonyimx328_otp.ggain;

	rg_ratio_typical = DIGITAL_GAIN_CALC_BASE * awb_gain_typical[0].rgain
		/ awb_gain_typical[0].ggain;
	bg_ratio_typical = DIGITAL_GAIN_CALC_BASE * awb_gain_typical[0].bgain
		/ awb_gain_typical[0].ggain;

	/* set init value */
	dgain->rgain = DIGITAL_GAIN_CALC_BASE;
	dgain->ggain = DIGITAL_GAIN_CALC_BASE;
	dgain->bgain = DIGITAL_GAIN_CALC_BASE;

	if (rg_ratio > rg_ratio_typical && bg_ratio > bg_ratio_typical) {
		dgain->ggain = DIGITAL_GAIN_CALC_BASE;
		dgain->rgain = DIGITAL_GAIN_CALC_BASE * rg_ratio / rg_ratio_typical;
		dgain->bgain = DIGITAL_GAIN_CALC_BASE * bg_ratio / bg_ratio_typical;
	} else {
		/* select smaller divider as base 0x100 */
		if (rg_ratio * bg_ratio_typical < bg_ratio * rg_ratio_typical) {
			dgain->rgain = DIGITAL_GAIN_CALC_BASE;
			dgain->ggain = DIGITAL_GAIN_CALC_BASE * rg_ratio_typical / rg_ratio;
			dgain->bgain = dgain->ggain * bg_ratio / bg_ratio_typical;
		} else {
			dgain->bgain = DIGITAL_GAIN_CALC_BASE;
			dgain->ggain = DIGITAL_GAIN_CALC_BASE * bg_ratio_typical / bg_ratio;
			dgain->rgain = dgain->ggain * rg_ratio / rg_ratio_typical;
		}
	}

	/* change CALC_BASE to BASE for more accurate */
	dgain->rgain = (dgain->rgain + 0x8) / 0x10;
	dgain->ggain = (dgain->ggain + 0x8) / 0x10;
	dgain->bgain = (dgain->bgain + 0x8) / 0x10;

	print_info("%s RGB otp[0x%x,0x%x,0x%x],dgain_base[0x%x,0x%x,0x%x]",
		__func__, sonyimx328_otp.rgain, sonyimx328_otp.ggain, sonyimx328_otp.bgain,
		dgain->rgain, dgain->ggain, dgain->bgain);

	return 0;
}
#endif


/*
**************************************************************************
* FunctionName: sonyimx328_check_otp;
* Description : check otp's status;
* Input       : NA;
* Output      : current otp status;
* ReturnValue : NA;
* Other       : NA;
**************************************************************************
*/
static void sonyimx328_check_otp(sensor_otp_status * status)
{
      if (NULL == status)
	  {
          print_error("%s, NULL data pointer!", __func__);
          return;
      }

#ifdef IMX328_171_OTP
      if((sonyimx328_otp_flag & SONYIMX328_OTP_FAIL_FLAG) != SONYIMX328_OTP_FAIL_FLAG){
	     *status = OTP_VALID;
      }else{
	     *status = OTP_INVALID;
      }
      print_info("otp status:%d, sonyimx328_otp_flag:0x%x", *status,sonyimx328_otp_flag);
#else
      *status = OTP_VALID;
      print_info("otp status:%d", *status);
#endif

      return;
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_get_sensor_reg;
 * Description : read sensor's reg value;
 * Input       : reg, register to be read;
 * Output      : pvalue, value readed from reg;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/

static void sonyimx328_get_sensor_reg(int reg, int *pvalue)
{
	u8 value = 0;
	if (NULL == pvalue)
	{
		print_error("%s, NULL data pointer!", __func__);
		return;
	}
	sonyimx328_read_reg(reg, &value);
	*pvalue = value;
	//print_info("%s, reg:0x%x, value:0x%x", __func__, reg, *pvalue);
	return;
}
/*
 **************************************************************************
 * FunctionName: sonyimx328_set_sensor_reg;
 * Description : write sensor's reg value;
 * Input       : reg, register to be write;
 * Output      : value, value to be writen;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx328_set_sensor_reg(int reg, int value)
{
	sonyimx328_write_reg(reg, value & 0xff, 0x00);
	return;
}
/*
 **************************************************************************
 * FunctionName: sonyimx328_reset;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_reset(camera_power_state power_state)
{
	print_debug("%s  ", __func__);

	if (POWER_ON == power_state) {
		k3_ispgpio_reset_sensor(sonyimx328_sensor.sensor_index, power_state,
			      sonyimx328_sensor.power_conf.reset_valid);
		udelay(300);
		k3_isp_io_enable_mclk(MCLK_ENABLE, sonyimx328_sensor.sensor_index);
		msleep(5);
	} else {
	       sonyimx328_write_reg(0x0100, 0x00, 0x00);
		msleep(30);
	       k3_isp_io_enable_mclk(MCLK_DISABLE, sonyimx328_sensor.sensor_index);
	       udelay(10);
		k3_ispgpio_reset_sensor(sonyimx328_sensor.sensor_index, power_state,
			      sonyimx328_sensor.power_conf.reset_valid);
		udelay(1);
	}

	return 0;
}


/*
 **************************************************************************
 * FunctionName: sonyimx328_init;
 * Description : sonyimx328 init function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : Error code indicating success or failure;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_init(void)
{
	static bool sonyimx328_check = false;
	print_debug("%s  ", __func__);

	if (false == sonyimx328_check) {
		if (video_check_suspensory_camera("sonyimx328_sensor_171") != 1) {
			print_error("%s: product not have this sensor", __func__);
			return -ENODEV;
		}
		sonyimx328_check = true;
	}

	if (sonyimx328_sensor.owner && !try_module_get(sonyimx328_sensor.owner)) {
		print_error("%s: try_module_get fail", __func__);
		return -ENOENT;
	}
	sonyimx328_sensor.old_flip = 0;
	k3_ispio_power_init(M_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - pri camera*/
	k3_ispio_power_init(M_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);		/*IO 1.8V - pri camera*/
	k3_ispio_power_init(M_CAMERA_VCM_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*AF 2.85V - pri camera*/
	k3_ispio_power_init(M_CAMERA_CORE_VDD, LDO_VOLTAGE_12V, LDO_VOLTAGE_12V);	/*core 1.2V - pri camera*/

    return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_exit;
 * Description : sonyimx328 exit function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx328_exit(void)
{
	print_debug("enter %s", __func__);

	k3_ispio_power_deinit();

	if (sonyimx328_sensor.owner)
		module_put(sonyimx328_sensor.owner);

	print_debug("exit %s", __func__);
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_shut_down;
 * Description : sonyimx328 shut down function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx328_shut_down(void)
{
	print_debug("enter %s", __func__);
	k3_ispgpio_power_sensor(&sonyimx328_sensor, POWER_OFF);
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_support_awb_otp;
 * Description : check sensor support awb otp or not;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx328_support_awb_otp(void)
{
	return AWB_OTP_SUPPORT;
}

extern u32 sensor_override_params[OVERRIDE_TYPE_MAX];
static u32 sonyimx328_get_override_param(camera_override_type_t type)
{
	u32 ret_val = sensor_override_params[type];

	switch (type) {
	case OVERRIDE_ISO_HIGH:
		ret_val = SONYIMX328_MAX_ISO;
		break;

	case OVERRIDE_ISO_LOW:
		ret_val = SONYIMX328_MIN_ISO;
		break;

	/* decrease frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_HIGH2MID:
		ret_val = SONYIMX328_AUTOFPS_GAIN_HIGH2MID;
		break;
	case OVERRIDE_AUTOFPS_GAIN_MID2LOW:
		ret_val = SONYIMX328_AUTOFPS_GAIN_MID2LOW;
		break;

	/* increase frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_LOW2MID:
		ret_val = SONYIMX328_AUTOFPS_GAIN_LOW2MID;
		break;
	case OVERRIDE_AUTOFPS_GAIN_MID2HIGH:
		ret_val = SONYIMX328_AUTOFPS_GAIN_MID2HIGH;
		break;

	case OVERRIDE_FPS_MAX:
		ret_val = SONYIMX328_MAX_FRAMERATE;
		break;

	case OVERRIDE_FPS_MID:
		ret_val = SONYIMX328_MID_FRAMERATE;
		break;

	case OVERRIDE_FPS_MIN:
		ret_val = SONYIMX328_MIN_FRAMERATE;
		break;

	case OVERRIDE_CAP_FPS_MIN:
		ret_val = SONYIMX328_MIN_CAP_FRAMERATE;
		break;

	case OVERRIDE_FLASH_TRIGGER_GAIN:
		ret_val = SONYIMX328_FLASH_TRIGGER_GAIN;
		break;

	case OVERRIDE_SHARPNESS_PREVIEW:
		ret_val = SONYIMX328_SHARPNESS_PREVIEW;
		break;

	case OVERRIDE_SHARPNESS_CAPTURE:
		ret_val = SONYIMX328_SHARPNESS_CAPTURE;
		break;

	default:
		print_error("%s:not override or invalid type %d, use default",__func__, type);
		break;
	}

	return ret_val;
}


static void sonyimx328_get_flash_awb(flash_platform_t type, awb_gain_t *flash_awb)
{
	*flash_awb = flash_platform_awb[0];
	print_info("sonyimx328_get_flash_awb: type 0x%x,", type);
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_get_gain;
 * Description :get gain from sensor
 * Input       	 NA;
 * Output      	 gain value from sensor
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static u32 sonyimx328_get_gain(void)
{
	u8 gain_l = 0;
	u32 gain = 0;

	sonyimx328_read_reg(SONYIMX328_ANA_GAIN_REG_L, &gain_l);

	gain = gain_l;

	if(_IS_DEBUG_AE)
	{
		print_info("enter %s, 0x0205=%x",__func__,gain_l);
	}
	return gain;
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_get_exposure;
 * Description :get exposure from sensor
 * Input       	 NA;
 * Output      	 exposure value from sensor
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static u32  sonyimx328_get_exposure(void)
{
	u32 expo = 0;
	u8 expo_h = 0;
	u8 expo_l = 0;

	sonyimx328_read_reg(SONYIMX328_EXPOSURE_REG_H, &expo_h);
	sonyimx328_read_reg(SONYIMX328_EXPOSURE_REG_L, &expo_l);

	if(_IS_DEBUG_AE)
	{
		print_info("enter %s,0x0202=%x,0x0203=%x",__func__,expo_h,expo_l);
	}
	expo = expo_h &0xff;
	expo = expo << 8 | expo_l;
	return expo;
}


/*
 **************************************************************************
 * FunctionName: sonyimx328_config_dphy_clk;
 * Description : set MIPI clock to dphy;
 * Input       : camera state
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx328_config_dphy_clk(camera_state state)
{
	u8 lane_clk;
	
	if (state == STATE_PREVIEW) {
		lane_clk =sonyimx328_sensor.frmsize_list[sonyimx328_sensor.preview_frmsize_index].lane_clk;
	} else {
		lane_clk =sonyimx328_sensor.frmsize_list[sonyimx328_sensor.capture_frmsize_index].lane_clk;
	}

	print_info("%s lane_clk = 0x%x state = %d",__func__, lane_clk, state);
	k3_ispio_config_lane_clk(sonyimx328_sensor.mipi_index, sonyimx328_sensor.mipi_lane_count, lane_clk);
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_set_default;
 * Description : init sonyimx328_sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx328_set_default(void)
{

	sonyimx328_sensor.init = sonyimx328_init;
	sonyimx328_sensor.exit = sonyimx328_exit;
	sonyimx328_sensor.shut_down = sonyimx328_shut_down;
	sonyimx328_sensor.reset = sonyimx328_reset;
	sonyimx328_sensor.check_sensor = sonyimx328_check_sensor;
	sonyimx328_sensor.power = sonyimx328_power;
	sonyimx328_sensor.init_reg = sonyimx328_init_reg;
	sonyimx328_sensor.init_isp_reg = sonyimx328_init_isp_reg;
	sonyimx328_sensor.stream_on = sonyimx328_stream_on;

	sonyimx328_sensor.get_format = sonyimx328_get_format;
	sonyimx328_sensor.set_flash = NULL;
	sonyimx328_sensor.get_flash = NULL;
	sonyimx328_sensor.set_scene = NULL;
	sonyimx328_sensor.get_scene = NULL;

	sonyimx328_sensor.enum_framesizes = sonyimx328_enum_framesizes;
	sonyimx328_sensor.try_framesizes = sonyimx328_try_framesizes;
	sonyimx328_sensor.set_framesizes = sonyimx328_set_framesizes;
	sonyimx328_sensor.get_framesizes = sonyimx328_get_framesizes;

	sonyimx328_sensor.enum_frame_intervals = sonyimx328_enum_frame_intervals;
	sonyimx328_sensor.try_frame_intervals = NULL;
	sonyimx328_sensor.set_frame_intervals = NULL;
	sonyimx328_sensor.get_frame_intervals = NULL;

	sonyimx328_sensor.get_capability = sonyimx328_get_capability;

	sonyimx328_sensor.set_hflip = sonyimx328_set_hflip;
	sonyimx328_sensor.get_hflip = sonyimx328_get_hflip;
	sonyimx328_sensor.set_vflip = sonyimx328_set_vflip;
	sonyimx328_sensor.get_vflip = sonyimx328_get_vflip;
	sonyimx328_sensor.update_flip = sonyimx328_update_flip;

	sonyimx328_sensor.sensor_hw_3a.support_awb_otp = sonyimx328_support_awb_otp;

	strncpy(sonyimx328_sensor.info.name, "imx328_sunny_171",sizeof(sonyimx328_sensor.info.name));
	sonyimx328_sensor.interface_type = MIPI1;
	sonyimx328_sensor.mipi_lane_count = CSI_LINES_4;
	sonyimx328_sensor.mipi_index = CSI_INDEX_0;
	sonyimx328_sensor.sensor_index = CAMERA_SENSOR_PRIMARY;
	sonyimx328_sensor.skip_frames = 2;
	sonyimx328_sensor.power_conf.pd_valid = LOW_VALID;
	sonyimx328_sensor.power_conf.reset_valid = LOW_VALID;
	sonyimx328_sensor.power_conf.vcmpd_valid = LOW_VALID;

	sonyimx328_sensor.i2c_config.index = I2C_PRIMARY;
	sonyimx328_sensor.i2c_config.speed = I2C_SPEED_400;
	sonyimx328_sensor.i2c_config.addr = SONYIMX328_SLAVE_ADDRESS;
	sonyimx328_sensor.i2c_config.addr_bits = I2C_16BIT;
	sonyimx328_sensor.i2c_config.val_bits = I2C_8BIT;

	sonyimx328_sensor.preview_frmsize_index = 0;
	sonyimx328_sensor.capture_frmsize_index = 0;
	sonyimx328_sensor.frmsize_list = sonyimx328_framesizes;
	sonyimx328_sensor.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW10;
	sonyimx328_sensor.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW10;

#ifdef SONYIMX328_AP_WRITEAE_MODE		/* just an example and test case for AP write AE mode */
	sonyimx328_sensor.aec_addr[0] = 0;
	sonyimx328_sensor.aec_addr[1] = 0;
	sonyimx328_sensor.aec_addr[2] = 0;
	sonyimx328_sensor.agc_addr[0] = 0;
	sonyimx328_sensor.agc_addr[1] = 0;
	sonyimx328_sensor.ap_writeAE_delay = 6000; /* 5 expo and gain registers, 6000 us is enough */
#else
	sonyimx328_sensor.aec_addr[0] = 0x0000;
	sonyimx328_sensor.aec_addr[1] = 0x0202;
	sonyimx328_sensor.aec_addr[2] = 0x0203;
	sonyimx328_sensor.agc_addr[0] = 0x0000;
	sonyimx328_sensor.agc_addr[1] = 0x0205;
#endif
	sonyimx328_sensor.sensor_type = SENSOR_SONY;
       sonyimx328_sensor.sensor_rgb_type = SENSOR_BGGR;

	sonyimx328_sensor.set_exposure_gain= sonyimx328_set_exposure_gain;
	sonyimx328_sensor.set_gain = NULL;
	sonyimx328_sensor.set_exposure = NULL;

	sonyimx328_sensor.set_vts = sonyimx328_set_vts;
	sonyimx328_sensor.get_vts_reg_addr = sonyimx328_get_vts_reg_addr;
	sonyimx328_sensor.get_override_param = sonyimx328_get_override_param;


	sonyimx328_sensor.sensor_gain_to_iso = sonyimx328_gain_to_iso;
	sonyimx328_sensor.sensor_iso_to_gain = sonyimx328_iso_to_gain;

       sonyimx328_sensor.get_sensor_aperture =sonyimx328_get_sensor_aperture;
	sonyimx328_sensor.set_effect = NULL;

	sonyimx328_sensor.isp_location = CAMERA_USE_K3ISP;
	sonyimx328_sensor.sensor_tune_ops = NULL;

	sonyimx328_sensor.af_enable = 1;
	sonyimx328_sensor.vcm = &vcm_dw9714_param;
	sonyimx328_sensor.get_flash_awb = sonyimx328_get_flash_awb;

	sonyimx328_sensor.image_setting.lensc_param = sonyimx328_lensc_param;
	sonyimx328_sensor.image_setting.ccm_param = sonyimx328_ccm_param;
	sonyimx328_sensor.image_setting.awb_param = sonyimx328_awb_param;

	sonyimx328_sensor.fps_max = 30;
	sonyimx328_sensor.fps_min = 10;
	sonyimx328_sensor.fps = 25;

	sonyimx328_sensor.owner = THIS_MODULE;

	sonyimx328_sensor.info.facing = CAMERA_FACING_BACK;
	sonyimx328_sensor.info.orientation = 90;
	sonyimx328_sensor.info.focal_length = 368; /* 3.68mm*/
	sonyimx328_sensor.info.h_view_angle = 64; /*  64.5 degree */
	sonyimx328_sensor.info.v_view_angle = 50; /*  50.1 degree */
	sonyimx328_sensor.lane_clk = CLK_300M;
	sonyimx328_sensor.hflip = 0;
	sonyimx328_sensor.vflip = 0;
	sonyimx328_sensor.old_flip = 0;
	sonyimx328_sensor.support_summary = false;

	sonyimx328_sensor.get_gain = sonyimx328_get_gain;
	sonyimx328_sensor.get_exposure = sonyimx328_get_exposure;
	
	sonyimx328_sensor.isp_idi_skip = false;

	sonyimx328_sensor.stream_off_setting = sonyimx328_stream_off_regs;
	sonyimx328_sensor.stream_off_setting_size = ARRAY_SIZE(sonyimx328_stream_off_regs);

	/*if there have different data rate of sensor resolution we need this config_dphy_clk 
	   otherwise if all resolution is same rate config_dphy_clk must to be null*/
	sonyimx328_sensor.config_dphy_clk = sonyimx328_config_dphy_clk;

	sonyimx328_sensor.get_sensor_reg = sonyimx328_get_sensor_reg;
	sonyimx328_sensor.set_sensor_reg = sonyimx328_set_sensor_reg;
	sonyimx328_sensor.check_otp_status = sonyimx328_check_otp;

}

/*
 **************************************************************************
 * FunctionName: sonyimx328_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int imx328_171_module_init(void)
{
	sonyimx328_set_default();
	//print_info("\nEnter %s yinxr-0829 \n", __func__);
	return register_camera_sensor(sonyimx328_sensor.sensor_index, &sonyimx328_sensor);
}

/*
 **************************************************************************
 * FunctionName: sonyimx328_module_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void __exit imx328_171_module_exit(void)
{
	unregister_camera_sensor(sonyimx328_sensor.sensor_index, &sonyimx328_sensor);
}

MODULE_AUTHOR("Hisilicon");
module_init(imx328_171_module_init);
module_exit(imx328_171_module_exit);
MODULE_LICENSE("GPL");

/********************************** END **********************************************/
