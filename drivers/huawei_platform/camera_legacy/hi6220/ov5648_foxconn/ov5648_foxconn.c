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
#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <asm/div64.h>
#include "sensor_common.h"

#include "cherryplus/ov5648_foxconn_cherryplus.h"
#include "chm/ov5648_foxconn_chm.h"
#include "alice/ov5648_foxconn_alice.h"
#include "cherrypro/ov5648_foxconn_cherrypro.h"

#include <asm/bug.h>
#include <linux/device.h>

#define LOG_TAG "OV5648_FOXCONN"
/* #define DEBUG_DEBUG 1 */
#include "cam_log.h"
#include "video_config.h"
//#include "../isp/effect.h"
#define OV5648_FOXCONN_AP_WRITEAE_MODE
#include "effect.h"
#include "cam_util.h"

#define OV5648_FOXCONN_SLAVE_ADDRESS    0x6C
#define OV5648_FOXCONN_CHIP_ID          0x5648

#define OV5648_FOXCONN_FLIP_REG         0x3820
#define OV5648_FOXCONN_MIRROR_REG       0x3821

#define OV5648_FOXCONN_EXPOSURE_REG_0	0x3500
#define OV5648_FOXCONN_EXPOSURE_REG_1	0x3501
#define OV5648_FOXCONN_EXPOSURE_REG_2	0x3502
#define OV5648_FOXCONN_GAIN_REG_H		0x350a
#define OV5648_FOXCONN_GAIN_REG_L		0x350b
#define OV5648_FOXCONN_VTS_REG_H	    0x380e
#define OV5648_FOXCONN_VTS_REG_L	    0x380f

#define OV5648_FOXCONN_EQUIVALENT_FOCUS		22 // 22mm
/* camera sensor override parameters, define in binning preview mode */
#define OV5648_FOXCONN_MAX_ISO			800
#define OV5648_FOXCONN_MIN_ISO			100

#define OV5648_FOXCONN_APERTURE_FACTOR              240 //F2.4

#define OV5648_FOXCONN_AUTOFPS_GAIN_LOW2MID		0x16
#define OV5648_FOXCONN_AUTOFPS_GAIN_MID2HIGH		0x16
#define OV5648_FOXCONN_AUTOFPS_GAIN_HIGH2MID		0x40
#define OV5648_FOXCONN_AUTOFPS_GAIN_MID2LOW		0x40

#define OV5648_FOXCONN_MAX_FRAMERATE		30
#define OV5648_FOXCONN_MIDDLE_FRAMERATE		15
#define OV5648_FOXCONN_MIN_FRAMERATE		15

#define OV5648_FOXCONN_MIN_CAP_FRAMERATE	8

#define OV5648_FOXCONN_FLASH_TRIGGER_GAIN	0x80

#define OV5648_FOXCONN_SHARPNESS_PREVIEW	0x10
#define OV5648_FOXCONN_SHARPNESS_CAPTURE	0x10

#define OV5648_FOXCONN_ZSL    (0x00)//(1 << CAMERA_ZSL_OFF)

#define OV5648_FOXCONN_OTP_FEATURE 1

#define OV5648_FOXCONN_I2C_RETRY_TIMES      5

enum sensor_module_type
{
	MODULE_FOXCONN=0,
	MODULE_OFILM,
	MODULE_UNSUPPORT
};
#ifdef OV5648_FOXCONN_OTP_FEATURE
struct otp_struct {
	u8 year;
	u8 month;
	u8 date;
	u8 user_id;
	u8 vendor_version;
	u8 version_id;
	u8 rg_l;
	u8 rg_h;
	u8 bg_h;
	u8 bg_l;
	u8 gbgr_h;
	u8 gbgr_l;
	int rgain;
	int bgain;
	int ggain;
};
//HUAWEIMODOULE ID, 23060132
#define HUAWEI_MODULE_ID 0x84 //HUAWEIMODOULE ID 23060132
#define VENDOR_ID        0x02//foxconn
static int RG_Ratio_Typical = 0x278;//The average value of the three golden samples
static int BG_Ratio_Typical = 0x2d2;//The average value of the three golden samples
static u8 otp_group_idx = 3;
static struct otp_struct ov5648_foxconn_otp;

#define OV5648_FOXCONN_OTP_INVALID 0x00
#define OV5648_FOXCONN_OTP_VALID 0xff
static int ov5648_foxconn_otp_flag = OV5648_FOXCONN_OTP_INVALID;
#endif

static camera_capability ov5648_foxconn_cap[] = {
    {V4L2_CID_FOCAL_LENGTH, 238},//2.38mm
    {V4L2_CID_ZSL,OV5648_FOXCONN_ZSL},
    {V4L2_CID_HORIZONTAL_VIEW_ANGLE, 7560},//add FOV angel
    {V4L2_CID_VERTICAL_VIEW_ANGLE, 6000},
};

/*should be calibrated, three lights, from 0x1c264*/
/*here is long exposure*/
char ov5648_foxconn_lensc_param[86 * 3] = {
};

/*should be calibrated, 6 groups 3x3, from 0x1c1d8*/
short ov5648_foxconn_ccm_param[54] = {
};

char ov5648_foxconn_awb_param[] = {
};

/*y36721 todo*/
char ov5648_foxconn_awb_param_short[] = {
};

/******************effect begin*************************/
static effect_params effect_ov5648_foxconn_cherryplus = {
#include "cherryplus/effect_ov5648_foxconn_cherryplus.h"
};

static effect_params effect_ov5648_foxconn_chm = {
#include "chm/effect_ov5648_foxconn_chm.h"
};

static effect_params effect_ov5648_foxconn_alice = {
#include "alice/effect_ov5648_foxconn_alice.h"
};
/*******************effect end*************************/

static const struct _sensor_reg_t ov5648_foxconn_stream_off_regs[] = {
//	{0x301a, 0xf1},
//	{0x301c, 0xd6},
	{0x0100, 0x00}
};
static const struct _sensor_reg_t ov5648_foxconn_stream_on_regs[] = {
    {0x301c, 0xd2},
	{0x301a, 0xf0},
};

static const sensor_config_s ov5648_foxconn_config_settings[]= {
    {
        "cherryplus",
        {ov5648_foxconn_cherryplus_init_array,  ARRAY_SIZE(ov5648_foxconn_cherryplus_init_array) },
        {ov5648_foxconn_cherryplus_framesizes, ARRAY_SIZE(ov5648_foxconn_cherryplus_framesizes)},
        &effect_ov5648_foxconn_cherryplus,
        NULL,
    },

    {
        "chm",
        {ov5648_foxconn_chm_init_array,  ARRAY_SIZE(ov5648_foxconn_chm_init_array) },
        {ov5648_foxconn_chm_framesizes, ARRAY_SIZE(ov5648_foxconn_chm_framesizes)},
        &effect_ov5648_foxconn_chm,
        NULL,
    },

    {
        "alice",
        {ov5648_foxconn_alice_init_array,  ARRAY_SIZE(ov5648_foxconn_alice_init_array) },
        {ov5648_foxconn_alice_framesizes, ARRAY_SIZE(ov5648_foxconn_alice_framesizes)},
        &effect_ov5648_foxconn_alice,
        NULL,
    },
    //cherrypro use the same effect params as cherryplus,while drv setting is individual.
    {
        "cherrypro",
        {ov5648_foxconn_cherrypro_init_array,  ARRAY_SIZE(ov5648_foxconn_cherrypro_init_array) },
        {ov5648_foxconn_cherrypro_framesizes, ARRAY_SIZE(ov5648_foxconn_cherrypro_framesizes)},
        &effect_ov5648_foxconn_cherryplus,
        NULL,
    },
};
static const sensor_config_s* ov5648_foxconn_config = ov5648_foxconn_config_settings;

static camera_sensor ov5648_foxconn_sensor;

static void ov5648_foxconn_set_default(void);
void ov5648_foxconn_set_vts(u32 vts);
static void ov5648_foxconn_config_dphy_clk(camera_state state);
static void ov5648_foxconn_reset_dphy(void);
/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_read_reg;
 * Description : read ov5648 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_read_reg(u16 reg, u8 *val)
{
	return k3_ispio_read_reg(ov5648_foxconn_sensor.i2c_config.index,
				 ov5648_foxconn_sensor.i2c_config.addr, reg, (u16*)val, ov5648_foxconn_sensor.i2c_config.val_bits,ov5648_foxconn_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_write_reg;
 * Description : write ov5648 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_write_reg(u16 reg, u8 val, u8 mask)
{
	return k3_ispio_write_reg(ov5648_foxconn_sensor.i2c_config.index,
			ov5648_foxconn_sensor.i2c_config.addr, reg, val, ov5648_foxconn_sensor.i2c_config.val_bits, mask,ov5648_foxconn_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_write_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ov5648_foxconn_write_seq(const struct _sensor_reg_t *seq, u32 size, u8 mask)
{
	print_info("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	return k3_ispio_write_seq(ov5648_foxconn_sensor.i2c_config.index,
			ov5648_foxconn_sensor.i2c_config.addr, seq, size, ov5648_foxconn_sensor.i2c_config.val_bits, mask,ov5648_foxconn_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_write_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ov5648_foxconn_write_isp_seq(const struct isp_reg_t *seq, u32 size)
{
	print_info("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	k3_ispio_write_isp_seq(seq, size);
}


#ifdef OV5648_FOXCONN_OTP_FEATURE
static int ov5648_foxconn_check_otp_group(int inx)
{
	u8 blank, i;
	u16 address;
	u8 temp_value;

	print_info("enter %s", __func__);
	for(i = 0; i < 16; i++) {
		ov5648_foxconn_write_reg(0x3d00 + i, 0x00, 0x00);
	}
	ov5648_foxconn_write_reg(0x3d84, 0xc0, 0x00);
	switch(inx) {
		case 0:
			blank = 0x05;
			ov5648_foxconn_write_reg(0x3d85, 0x00, 0x00);
			ov5648_foxconn_write_reg(0x3d86, 0x0f, 0x00);
			break;
		case 1:
			blank = 0x00;
			ov5648_foxconn_write_reg(0x3d85, 0x10, 0x00);
			ov5648_foxconn_write_reg(0x3d86, 0x1f, 0x00);
			break;
		default:
			return -1;
	}
/* set address */
	address = 0x3d00 + blank;
	print_info("S: enter %s   address = %d", __func__,address);
/* load otp to buffer */
	ov5648_foxconn_write_reg(0x3d81, 0x01, 0x00);
	mdelay(5);
/* check value */
	ov5648_foxconn_read_reg(address, &temp_value);
/* disable otp read */
	ov5648_foxconn_write_reg(0x3d81, 0x00, 0x00);
	print_info("S: enter %s   temp_value = %d", __func__,temp_value);
	temp_value = temp_value >> 6;
	if(1 == temp_value) {
		print_info("S: enter %s   idx = %d", __func__,inx);
		otp_group_idx = inx;
		return 0;
	}
	return -1;
}


static int ov5648_foxconn_support_awb_otp(void)
{
	return AWB_OTP_SUPPORT;
}

static int ov5648_foxconn_read_otp_id_wb(void)
{
	u8 blank;
	u16 address;

	print_info("enter %s", __func__);
	ov5648_foxconn_write_reg(0x3d84, 0xc0, 0x00);
	switch(otp_group_idx) {
		case 0:
			blank = 0x05;
			ov5648_foxconn_write_reg(0x3d85, 0x00, 0x00);
			ov5648_foxconn_write_reg(0x3d86, 0x0f, 0x00);
			break;
		case 1:
			blank = 0x00;
			ov5648_foxconn_write_reg(0x3d85, 0x10, 0x00);
			ov5648_foxconn_write_reg(0x3d86, 0x1f, 0x00);
			break;
		default:
			return -1;
	}
/* set address */
	address = 0x3d00 + blank;
/* select bank */

/* load otp to buffer */
	ov5648_foxconn_write_reg(0x3d81, 0x01, 0x00);
	mdelay(5);
/* get value */
	ov5648_foxconn_read_reg(address, &(ov5648_foxconn_otp.year));
	ov5648_foxconn_otp.year &= 0x3f;
	ov5648_foxconn_read_reg(address+1, &(ov5648_foxconn_otp.month));
	ov5648_foxconn_read_reg(address+2, &(ov5648_foxconn_otp.date));
	ov5648_foxconn_read_reg(address+3, &(ov5648_foxconn_otp.user_id));
	ov5648_foxconn_read_reg(address+4, &(ov5648_foxconn_otp.vendor_version));
	ov5648_foxconn_otp.version_id  = (ov5648_foxconn_otp.vendor_version >> 4) & 0x0f;
	ov5648_foxconn_otp.vendor_version = (ov5648_foxconn_otp.vendor_version) & 0x0f;
	print_info("%s year = %d mouth = %d data = %d user_id=0x%x vendor_id=0x%x", __func__,ov5648_foxconn_otp.year,ov5648_foxconn_otp.month,ov5648_foxconn_otp.date,ov5648_foxconn_otp.user_id,ov5648_foxconn_otp.version_id);
	ov5648_foxconn_read_reg(address+5, &(ov5648_foxconn_otp.rg_h));
	ov5648_foxconn_read_reg(address+6, &(ov5648_foxconn_otp.rg_l));
	ov5648_foxconn_read_reg(address+7, &(ov5648_foxconn_otp.bg_h));
	ov5648_foxconn_read_reg(address+8, &(ov5648_foxconn_otp.bg_l));
	ov5648_foxconn_read_reg(address+9, &(ov5648_foxconn_otp.gbgr_h));
	ov5648_foxconn_read_reg(address+10, &(ov5648_foxconn_otp.gbgr_l));

	ov5648_foxconn_sensor.sensor_hw_3a.awb_otp_value.r_g_high = ov5648_foxconn_otp.rg_h;
	ov5648_foxconn_sensor.sensor_hw_3a.awb_otp_value.r_g_low = ov5648_foxconn_otp.rg_l;
	ov5648_foxconn_sensor.sensor_hw_3a.awb_otp_value.b_g_high = ov5648_foxconn_otp.bg_h;
	ov5648_foxconn_sensor.sensor_hw_3a.awb_otp_value.b_g_low = ov5648_foxconn_otp.bg_l;
	ov5648_foxconn_sensor.sensor_hw_3a.awb_otp_value.gb_gr_high = ov5648_foxconn_otp.gbgr_h;
	ov5648_foxconn_sensor.sensor_hw_3a.awb_otp_value.gb_gr_low = ov5648_foxconn_otp.gbgr_l;

/* disable otp read */
	ov5648_foxconn_write_reg(0x3d81, 0x00, 0x00);
	return 0;
}

static int ov5648_foxconn_update_wb_gain(u16 R_gain, u16 G_gain, u16 B_gain)
{

	print_info("enter %s  r_gain = 0x%x   g_gain = 0x%x  b_gain = 0x%x", __func__,R_gain,G_gain,B_gain);
	if (R_gain > 0x400) {
		ov5648_foxconn_write_reg(0x5186, R_gain>>8, 0x00);
		ov5648_foxconn_write_reg(0x5187, R_gain & 0x00ff, 0x00);
	}

	if (G_gain > 0x400) {
		ov5648_foxconn_write_reg(0x5188, G_gain>>8, 0x00);
		ov5648_foxconn_write_reg(0x5189, G_gain & 0x00ff, 0x00);
	}

	if (B_gain > 0x400) {
		ov5648_foxconn_write_reg(0x518a, B_gain>>8, 0x00);
		ov5648_foxconn_write_reg(0x518b, B_gain & 0x00ff, 0x00);
	}

	return 0;
}

static int ov5648_foxconn_update_otp(void)
{
	int R_gain, G_gain, B_gain, G_gain_R, G_gain_B;
	int rg,bg;
	ov5648_foxconn_read_otp_id_wb();
	rg = (ov5648_foxconn_otp.rg_h << 8) + ov5648_foxconn_otp.rg_l;
	bg = (ov5648_foxconn_otp.bg_h << 8) + ov5648_foxconn_otp.bg_l;
	print_info("rg_ratio 0x%x, bg_ratio 0x%x",rg, bg);

	if ((HUAWEI_MODULE_ID != ov5648_foxconn_otp.user_id)||(VENDOR_ID != ov5648_foxconn_otp.version_id))
	{
		print_error("%s Invalid otp value for id is not correct!",__func__);
		ov5648_foxconn_otp_flag = OV5648_FOXCONN_OTP_INVALID;
		return -1;
	}

	if ((0==rg)||(0==bg))
	{
		print_error("%s Invalid awb otp value for AWB data is zero!",__func__);
		ov5648_foxconn_otp_flag = OV5648_FOXCONN_OTP_INVALID;
		return -1;
	}

	//calculate G gain
	//0x400 = 1x gain
	if(bg < BG_Ratio_Typical) {
		if (rg< RG_Ratio_Typical) {
   			G_gain = 0x400;
			B_gain = 0x400 * BG_Ratio_Typical / bg;
    		R_gain = 0x400 * RG_Ratio_Typical / rg;
		} else {
    		R_gain = 0x400;
   	 		G_gain = 0x400 * rg / RG_Ratio_Typical;
    		B_gain = G_gain * BG_Ratio_Typical /bg;
		}
	} else {
		if (rg < RG_Ratio_Typical) {
    		B_gain = 0x400;
    		G_gain = 0x400 * bg / BG_Ratio_Typical;
    		R_gain = G_gain * RG_Ratio_Typical / rg;
		} else {
    		G_gain_B = 0x400 * bg / BG_Ratio_Typical;
   	 		G_gain_R = 0x400 * rg / RG_Ratio_Typical;

    		if(G_gain_B > G_gain_R ) {
        		B_gain = 0x400;
        		G_gain = G_gain_B;
 	     		R_gain = G_gain * RG_Ratio_Typical /rg;
  			} else {
        		R_gain = 0x400;
       			G_gain = G_gain_R;
        		B_gain = G_gain * BG_Ratio_Typical / bg;
			}
    	}
	}
	ov5648_foxconn_otp.rgain = R_gain;
	ov5648_foxconn_otp.bgain = B_gain;
	ov5648_foxconn_otp.ggain = G_gain;

	ov5648_foxconn_otp_flag = OV5648_FOXCONN_OTP_VALID;
	return 0;
}
#endif
/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_enum_frame_intervals;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_enum_frame_intervals(struct v4l2_frmivalenum *fi)
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
	fi->discrete.denominator = (fi->index + 1);
	return 0;
}

static int ov5648_foxconn_get_capability(u32 id, u32 *value)
{
	int i;
	for (i = 0; i < sizeof(ov5648_foxconn_cap) / sizeof(ov5648_foxconn_cap[0]); ++i) {
		if (id == ov5648_foxconn_cap[i].id) {
			*value = ov5648_foxconn_cap[i].value;
			break;
		}
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_get_format;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_get_format(struct v4l2_fmtdesc *fmt)
{
	if (fmt->type == V4L2_BUF_TYPE_VIDEO_OVERLAY)
		fmt->pixelformat = V4L2_PIX_FMT_RAW10;
	else
		fmt->pixelformat = V4L2_PIX_FMT_RAW10;
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_enum_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 max_index = ARRAY_SIZE(camera_framesizes) - 1;
	u32 this_max_index =   ov5648_foxconn_config->framesizes.size-1;
	framesize_s * ov5648_foxconn_framesizes = ov5648_foxconn_config->framesizes.framesize_setting;

	assert(framesizes);
	if(NULL == framesizes) {
		return -EINVAL;
	}

	print_debug("enter %s;", __func__);

	if (framesizes->index > max_index) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	if ((camera_framesizes[framesizes->index].width > ov5648_foxconn_framesizes[this_max_index].width)
		|| (camera_framesizes[framesizes->index].height > ov5648_foxconn_framesizes[this_max_index].height)) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	framesizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	framesizes->discrete.width = ov5648_foxconn_framesizes[this_max_index].width;
	framesizes->discrete.height = ov5648_foxconn_framesizes[this_max_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_try_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_try_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 max_index = ov5648_foxconn_config->framesizes.size - 1;
	framesize_s * ov5648_foxconn_framesizes =  ov5648_foxconn_config->framesizes.framesize_setting;

	assert(framesizes);

	if(NULL == framesizes) {
		return -EINVAL;
	}

	print_debug("Enter Function:%s ", __func__);

	if (framesizes->discrete.width <= ov5648_foxconn_framesizes[max_index].width
	    && framesizes->discrete.height <= ov5648_foxconn_framesizes[max_index].height) {
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
 * FunctionName: ov5648_foxconn_set_framesizes;
 * Description : NA;
 * Input       : flag: if 1, set framesize to sensor,
 *					   if 0, only store framesize to camera_interface;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_set_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type, bool zsl_preview)
{
	int i = 0;
	bool match = false;
	int size = 0;

	framesize_s * ov5648_foxconn_framesizes = NULL;
	assert(fs);

	if(NULL == fs) {
		return -EINVAL;
	}

	print_debug("Enter Function:%s State(%d), flag=%d, width=%d, height=%d",
		    __func__, state, flag, fs->width, fs->height);

	size = ov5648_foxconn_config->framesizes.size;
	ov5648_foxconn_framesizes = ov5648_foxconn_config->framesizes.framesize_setting;
	if (VIEW_FULL == view_type) {
		for (i = 0; i < size; i++) {
			if ((ov5648_foxconn_framesizes[i].width >= fs->width)
			    && (ov5648_foxconn_framesizes[i].height >= fs->height)
			    && (VIEW_FULL == ov5648_foxconn_framesizes[i].view_type)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= ov5648_foxconn_framesizes[i].resolution_type)) {
				fs->width = ov5648_foxconn_framesizes[i].width;
				fs->height = ov5648_foxconn_framesizes[i].height;
				match = true;
				break;
			}
		}
	}

	if (false == match) {
		for (i = 0; i < size; i++) {
			if ((ov5648_foxconn_framesizes[i].width >= fs->width)
			    && (ov5648_foxconn_framesizes[i].height >= fs->height)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= ov5648_foxconn_framesizes[i].resolution_type)) {
				fs->width = ov5648_foxconn_framesizes[i].width;
				fs->height = ov5648_foxconn_framesizes[i].height;
				break;
			}
		}
	}
#if 0
	for (i = 0; i < ARRAY_SIZE(ov5648_foxconn_framesizes); i++) {
		if ((ov5648_foxconn_framesizes[i].width >= fs->width)
		    && (ov5648_foxconn_framesizes[i].height >= fs->height)) {
			fs->width = ov5648_foxconn_framesizes[i].width;
			fs->height = ov5648_foxconn_framesizes[i].height;
			break;
		}
	}
#endif
	if (i >= size) {
		print_error("request resolution larger than sensor's max resolution");
		return -EINVAL;
	}

	if (state == STATE_PREVIEW)
		ov5648_foxconn_sensor.preview_frmsize_index = i;
	else
		ov5648_foxconn_sensor.capture_frmsize_index = i;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_get_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_get_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs)
{
	int frmsize_index;
	framesize_s * ov5648_foxconn_framesizes = NULL;

	assert(fs);

	if(NULL == fs) {
		return -EINVAL;
	}
	ov5648_foxconn_framesizes = ov5648_foxconn_config->framesizes.framesize_setting;
	if (state == STATE_PREVIEW)
		frmsize_index = ov5648_foxconn_sensor.preview_frmsize_index;
	else if (state == STATE_CAPTURE)
		frmsize_index = ov5648_foxconn_sensor.capture_frmsize_index;
	else
		return -EINVAL;
	fs->width = ov5648_foxconn_framesizes[frmsize_index].width;
	fs->height = ov5648_foxconn_framesizes[frmsize_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_init_reg;
 * Description : download initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_init_reg(void)
{
	int size = 0;
	const sensor_reg_t* ov5648_foxconn_init_regs = NULL;

	print_info("Enter Function:%s  , initsize=%d", __func__,ov5648_foxconn_config->init_setting.settings[0].seq_size);
        #if 0
    size = CAMERA_MAX_SETTING_SIZE;
	ov5648_foxconn_write_isp_seq(sensor->effect->isp_settings, size);
        #endif
	if (0 != k3_ispio_init_csi(ov5648_foxconn_sensor.mipi_index,
		 ov5648_foxconn_sensor.mipi_lane_count, ov5648_foxconn_sensor.lane_clk)) {
    	return -EFAULT;
	}
	ov5648_foxconn_write_reg(0x0100, 0x00, 0x00);
//	ov5648_foxconn_write_reg(0x301a, 0xf1, 0x00);
//	ov5648_foxconn_write_reg(0x301c, 0xd6, 0x00);	
	ov5648_foxconn_write_reg(0x0103, 0x01, 0x00);
	mdelay(5);

	size = ov5648_foxconn_config->init_setting.settings[0].seq_size;
	ov5648_foxconn_init_regs = ov5648_foxconn_config->init_setting.settings[0].setting;

	if (0 != ov5648_foxconn_write_seq(ov5648_foxconn_init_regs, size, 0x00)) {
		print_error("fail to init ov5648 sensor");
		return -EFAULT;
	}

	return 0;
}

static int ov5648_foxconn_get_sensor_aperture(void)
{
	return OV5648_FOXCONN_APERTURE_FACTOR;
}

static int ov5648_foxconn_set_hflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);
	ov5648_foxconn_sensor.hflip = flip;
	return 0;
}

static int ov5648_foxconn_set_vflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);
	ov5648_foxconn_sensor.vflip = flip;
	return 0;
}

static int ov5648_foxconn_get_hflip(void)
{
	print_debug("enter %s flip=%d", __func__, ov5648_foxconn_sensor.hflip);
	return ov5648_foxconn_sensor.hflip;
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_dump_reg_debug;
 * Description : dump standby, frame count, cap relate reg for debug
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov5648_foxconn_dump_reg_debug(void)
{
     u16 reg = 0;
     u8 val = 0;

     reg=0x0100;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);

     reg=0x4868;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x4869;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);

     reg=0x3035;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x3036;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x3708;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x3709;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x370c;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x3808;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x3809;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x380a;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x380b;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x380c;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x380d;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x380e;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x380f;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x3811;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x3813;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x3814;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x3815;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
     reg=0x4837;ov5648_foxconn_read_reg(reg,&val);print_info("0x%0x=0x%0x", reg, val);
}

static int ov5648_foxconn_get_vflip(void)
{
	print_debug("enter %s flip=%d", __func__, ov5648_foxconn_sensor.vflip);
	return ov5648_foxconn_sensor.vflip;
}

static int ov5648_foxconn_update_flip(u16 width, u16 height)
{
	u8 new_flip = ((ov5648_foxconn_sensor.vflip << 1) | ov5648_foxconn_sensor.hflip);
	print_info("Enter %s", __func__);
	k3_ispio_update_flip((ov5648_foxconn_sensor.old_flip ^ new_flip) & 0x03, width, height, PIXEL_ORDER_NO_CHANGED);
	ov5648_foxconn_write_reg(OV5648_FOXCONN_FLIP_REG, ov5648_foxconn_sensor.vflip ? 0x06 : 0x00, ~0x06);
	ov5648_foxconn_write_reg(OV5648_FOXCONN_MIRROR_REG, ov5648_foxconn_sensor.hflip ? 0x00 : 0x06, ~0x06);
	ov5648_foxconn_sensor.old_flip = new_flip;
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_framesize_switch;
 * Description : switch frame size, used by preview and capture
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_framesize_switch(camera_state state)
{
	u8 next_frmsize_index;
	u32 size = ov5648_foxconn_config->framesizes.size;

	if (state == STATE_PREVIEW)
		next_frmsize_index = ov5648_foxconn_sensor.preview_frmsize_index;
	else
		next_frmsize_index = ov5648_foxconn_sensor.capture_frmsize_index;

	print_info("Enter Function:%s frm index=%d", __func__, next_frmsize_index);

	if (next_frmsize_index >= size){
		print_error("Unsupport sensor setting index: %d",next_frmsize_index);
		return -ETIME;
	}

	if (0 != ov5648_foxconn_write_seq( ov5648_foxconn_sensor.frmsize_list[next_frmsize_index].sensor_setting.setting
		, ov5648_foxconn_sensor.frmsize_list[next_frmsize_index].sensor_setting.seq_size, 0x00)) {
		print_error("fail to init ov5648 sensor");
		return -ETIME;
	}

	if(NULL != ov5648_foxconn_sensor.stream_on_setting)
	{
		if (0 != ov5648_foxconn_write_seq(ov5648_foxconn_sensor.stream_on_setting, ov5648_foxconn_sensor.stream_on_setting_size, 0x00)) {
			print_error("%s fail to stream on ov5648 sensor", __func__);
			return -ETIME;
		}		
	}

	#if 0
	msleep(3);
	/* use auto fps level at coolboot */
	vts = ov5648_foxconn_sensor.frmsize_list[next_frmsize_index].vts *
		ov5648_foxconn_sensor.frmsize_list[next_frmsize_index].fps / ov5648_foxconn_sensor.fps;
	ov5648_foxconn_set_vts(vts);
	ov5648_foxconn_update_flip(ov5648_foxconn_framesizes[next_frmsize_index].width,
		ov5648_foxconn_framesizes[next_frmsize_index].height);
	#endif
    return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_start_preview;
 * Description : download preview seq for sensor preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_stream_on(camera_state state)
{
    int                                 ret = 0;

	print_debug("Enter Function:%s  , preview frmsize index=%d",
		    __func__, ov5648_foxconn_sensor.preview_frmsize_index);

	ov5648_foxconn_config_dphy_clk(state);

	ret = ov5648_foxconn_framesize_switch(state);
	if (ret != 0)
	{
	    print_warn("%s,ov5648_foxconn_framesize_switch fail.ret=%d.",__func__,ret);
	    return ret;
	}

#ifdef OV5648_FOXCONN_OTP_FEATURE
    if(OV5648_FOXCONN_OTP_VALID == ov5648_foxconn_otp_flag) {
        ov5648_foxconn_update_wb_gain(ov5648_foxconn_otp.rgain, ov5648_foxconn_otp.ggain, ov5648_foxconn_otp.bgain);
    }
#endif

	return 0;
}

/*  **************************************************************************
* FunctionName: ov5648_foxconn_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int ov5648_foxconn_check_sensor(void)
{
	u8 idl = 0;
	u8 idh = 0;
	u16 id = 0;
	u8 i;
	int retry = 0;
	int ret = 0;

    for(retry = 0; retry < OV5648_FOXCONN_I2C_RETRY_TIMES; retry++) {
    	ov5648_foxconn_read_reg(0x300A, &idh);
    	ov5648_foxconn_read_reg(0x300B, &idl);

    	id = ((idh << 8) | idl);
    	print_info("ov5648 product id:0x%x ,retrytimes:%d", id, retry);
        if(OV5648_FOXCONN_CHIP_ID == id) {
            break;
        }
        udelay(100);
    }
	if (OV5648_FOXCONN_CHIP_ID != id) {
		print_error("Invalid product id ,Could not load sensor ov5648");
		return -1;
	}

	ret = k3_socgpio_get_id_value(S_CAMERA_ID_PIN);
	if(ret < 0) {
		print_error("ov5648_foxconn_sensor fail to get gpio value!!!so return -1!\n");
		return -1;
	}

	if(ret != MODULE_FOXCONN){
		print_info("%s this moudle is not ov5648_foxconn moudle",__func__);
		return -1;
	}

	#ifdef OV5648_FOXCONN_OTP_FEATURE
	ov5648_foxconn_write_reg(0x0100, 0x01, 0x00);
	for(i = 0; i < 2; i++) {
		if(0 == ov5648_foxconn_check_otp_group(i))
			break;
	}
	if(otp_group_idx < 2) {
		ov5648_foxconn_update_otp();
	}
	ov5648_foxconn_write_reg(0x0100, 0x00, 0x00);
	#endif
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_init_isp_reg;
 * Description : load initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_init_isp_reg(void)
{
	int size = 0;

	camera_sensor *sensor = &ov5648_foxconn_sensor;

        size = CAMERA_MAX_SETTING_SIZE;

        ov5648_foxconn_write_isp_seq(sensor->effect->isp_settings, size);

	return 0;
}

/*  **************************************************************************
* FunctionName: ov5648_foxconn_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
int ov5648_foxconn_power(camera_power_state power)
{
	if (power == POWER_ON) {
		k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);
		udelay(100);
		//k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);
		//udelay(100);
		k3_socgpio_power_sensor(1, S_CAMERA_ANALOG_VDD);//for external AVDD LDO
		k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
		udelay(100);
		k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);//power on main sensor's DVDD
		udelay(100);
		k3_ispio_ioconfig(&ov5648_foxconn_sensor, power);
		mdelay(8);
		k3_ispgpio_power_sensor(&ov5648_foxconn_sensor, power);
		udelay(1200);
		k3_ispgpio_reset_sensor(ov5648_foxconn_sensor.sensor_index, power, ov5648_foxconn_sensor.power_conf.reset_valid);
		msleep(20);
		k3_isp_io_enable_mclk(MCLK_ENABLE, ov5648_foxconn_sensor.sensor_index);
		msleep(5);
	} else {
		k3_ispio_deinit_csi(ov5648_foxconn_sensor.mipi_index);
		k3_isp_io_enable_mclk(MCLK_DISABLE, ov5648_foxconn_sensor.sensor_index);
		k3_ispio_ioconfig(&ov5648_foxconn_sensor, power);
		k3_ispgpio_power_sensor(&ov5648_foxconn_sensor, power);
		udelay(100);
		k3_ispgpio_reset_sensor(ov5648_foxconn_sensor.sensor_index, power, ov5648_foxconn_sensor.power_conf.reset_valid);
		udelay(100);

		k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);//power off main sensor' DVDD
		k3_socgpio_power_sensor(0, S_CAMERA_ANALOG_VDD);//for external AVDD  LDO
		k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
		udelay(100);
		//k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);
		//udelay(100);
		k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_shut_down;
 * Description : ov5648 shut down function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov5648_foxconn_shut_down(void)
{
	print_debug("enter %s", __func__);
	k3_ispgpio_power_sensor(&ov5648_foxconn_sensor, POWER_OFF);
}

/*
 * Here gain is in unit 1/16 of sensor gain,
 * y36721 todo, temporarily if sensor gain=0x10, ISO is 100
 * in fact we need calibrate an ISO-ET-gain table.
 */
u32 ov5648_foxconn_gain_to_iso(int gain)
{
	return (gain * 100) / 0x10;
}

u32 ov5648_foxconn_iso_to_gain(int iso)
{
	return (iso * 0x10) / 100;
}

void ov5648_foxconn_set_gain(u32 gain)
{
	if (gain)
	{
		ov5648_foxconn_write_reg(OV5648_FOXCONN_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
		ov5648_foxconn_write_reg(OV5648_FOXCONN_GAIN_REG_L, gain & 0xff, 0x00);
	}

}

void ov5648_foxconn_set_exposure(u32 exposure)
{
	ov5648_foxconn_write_reg(OV5648_FOXCONN_EXPOSURE_REG_0, (exposure >> 16) & 0x0f, 0x00);
	ov5648_foxconn_write_reg(OV5648_FOXCONN_EXPOSURE_REG_1, (exposure >> 8) & 0xff, 0x00);
	ov5648_foxconn_write_reg(OV5648_FOXCONN_EXPOSURE_REG_2, exposure & 0xf0, 0x00);	/*fraction part not used */
}

static void ov5648_foxconn_set_exposure_gain(u32 exposure, u32 gain)
{
	ov5648_foxconn_write_reg(OV5648_FOXCONN_EXPOSURE_REG_0, (exposure >> 16) & 0x0f, 0x00);
	ov5648_foxconn_write_reg(OV5648_FOXCONN_EXPOSURE_REG_1, (exposure >> 8) & 0xff, 0x00);
	ov5648_foxconn_write_reg(OV5648_FOXCONN_EXPOSURE_REG_2, exposure & 0xf0, 0x00);	/*fraction part not used */

	if (gain)
	{
		ov5648_foxconn_write_reg(OV5648_FOXCONN_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
		ov5648_foxconn_write_reg(OV5648_FOXCONN_GAIN_REG_L, gain & 0xff, 0x00);
	}
}

u32 ov5648_foxconn_get_vts_reg_addr(void)
{
	return OV5648_FOXCONN_VTS_REG_H;
}

void ov5648_foxconn_set_vts(u32 vts)
{
	ov5648_foxconn_write_reg(OV5648_FOXCONN_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
	ov5648_foxconn_write_reg(OV5648_FOXCONN_VTS_REG_L, vts & 0xff, 0x00);
}

static u32 ov5648_foxconn_get_override_param(camera_override_type_t type)
{
	u32 ret_val = sensor_override_params[type];

	switch (type) {
	case OVERRIDE_ISO_HIGH:
		ret_val = OV5648_FOXCONN_MAX_ISO;
		break;

	case OVERRIDE_ISO_LOW:
		ret_val = OV5648_FOXCONN_MIN_ISO;
		break;

	/* increase frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_LOW2MID:
		ret_val = OV5648_FOXCONN_AUTOFPS_GAIN_LOW2MID;
		break;
	case OVERRIDE_AUTOFPS_GAIN_MID2HIGH:
		ret_val = OV5648_FOXCONN_AUTOFPS_GAIN_MID2HIGH;
		break;

	/* reduce frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_MID2LOW:
		ret_val = OV5648_FOXCONN_AUTOFPS_GAIN_MID2LOW;
		break;
	case OVERRIDE_AUTOFPS_GAIN_HIGH2MID:
		ret_val = OV5648_FOXCONN_AUTOFPS_GAIN_HIGH2MID;
		break;

	case OVERRIDE_FPS_MAX:
		ret_val = OV5648_FOXCONN_MAX_FRAMERATE;
		break;

	case OVERRIDE_FPS_MIN:
		ret_val = OV5648_FOXCONN_MIN_FRAMERATE;
		break;

    case OVERRIDE_FPS_MID:
        ret_val = OV5648_FOXCONN_MIDDLE_FRAMERATE;
        break;

	case OVERRIDE_CAP_FPS_MIN:
		ret_val = OV5648_FOXCONN_MIN_CAP_FRAMERATE;
		break;

	case OVERRIDE_FLASH_TRIGGER_GAIN:
		ret_val = OV5648_FOXCONN_FLASH_TRIGGER_GAIN;
		break;

	case OVERRIDE_SHARPNESS_PREVIEW:
		ret_val = OV5648_FOXCONN_SHARPNESS_PREVIEW;
		break;

	case OVERRIDE_SHARPNESS_CAPTURE:
		ret_val = OV5648_FOXCONN_SHARPNESS_CAPTURE;
		break;

	default:
		print_error("%s:not override or invalid type %d, use default",__func__, type);
		break;
	}

	return ret_val;
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_reset;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_reset(camera_power_state power_state)
{
	print_debug("%s", __func__);
	ov5648_foxconn_sensor.old_flip = 0;
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_init;
 * Description : ov5648 init function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : Error code indicating success or failure;
 * Other       : NA;
 **************************************************************************
*/
static int ov5648_foxconn_init(void)
{
    static bool ov5648_foxconn_check = false;
    int ret = 0;
    print_debug("%s", __func__);

    if (false == ov5648_foxconn_check) {
        if (video_check_suspensory_camera("ov5648fx_sensor") != 1) {
            print_error("%s: product not have this sensor", __func__);
            return -ENODEV;
        }

        ret = camera_get_matching_sensor_config(ov5648_foxconn_config_settings, ARRAY_SIZE(ov5648_foxconn_config_settings),&ov5648_foxconn_config);
        if( ret < 0 ){
            print_error("%s: fail to match sensor config.", __func__);
            return -ENODEV;
        } else {
            print_info("%s: choose the %s's setting.",__func__,ov5648_foxconn_config->product);
        }

        ov5648_foxconn_sensor.frmsize_list = ov5648_foxconn_config->framesizes.framesize_setting;
        ov5648_foxconn_sensor.effect = ov5648_foxconn_config->effect;
        ov5648_foxconn_sensor.lane_clk = ov5648_foxconn_config->framesizes.framesize_setting[0].lane_clk;

        ov5648_foxconn_check = true;
    }

    if (ov5648_foxconn_sensor.owner && !try_module_get(ov5648_foxconn_sensor.owner)) {
        print_error("%s: try_module_get fail", __func__);
        return -ENOENT;
    }

    // S_CAMERA_CORE_VDD and S_CAMERA_IO_VDD use same vdd source, so only init once
    k3_ispio_power_init(S_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - sec camera*/
    k3_ispio_power_init(S_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);		/*IO 1.8V - sec camera*/
    //k3_ispio_power_init(S_CAMERA_CORE_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);	/*core 1.8V - sec camera*/
    k3_ispio_power_init(M_CAMERA_CORE_VDD, LDO_VOLTAGE_12V, LDO_VOLTAGE_12V);	/*core 1.05V - pri camera*/

    return 0;
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_exit;
 * Description : ov5648 exit function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov5648_foxconn_exit(void)
{
	print_debug("enter %s", __func__);

	k3_ispio_power_deinit();

	if (ov5648_foxconn_sensor.owner) {
		module_put(ov5648_foxconn_sensor.owner);
	}
	print_debug("exit %s", __func__);
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_config_dphy_clk;
 * Description : set MIPI clock to dphy;
 * Input       : camera state
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov5648_foxconn_config_dphy_clk(camera_state state)
{
	u8 lane_clk;

	if (state == STATE_PREVIEW) {
		lane_clk =ov5648_foxconn_sensor.frmsize_list[ov5648_foxconn_sensor.preview_frmsize_index].lane_clk;
	} else {
		lane_clk =ov5648_foxconn_sensor.frmsize_list[ov5648_foxconn_sensor.capture_frmsize_index].lane_clk;
	}

	print_info("%s lane_clk = 0x%x state = %d",__func__, lane_clk, state);
	k3_ispio_config_lane_clk(ov5648_foxconn_sensor.mipi_index, ov5648_foxconn_sensor.mipi_lane_count, lane_clk);
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_reset_dphy;
 * Description : reset dphy;
 * Input       : index:sensor index; mipi_lane_count: mipi land count;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov5648_foxconn_reset_dphy(void)
{
       k3_ispio_reset_phy(ov5648_foxconn_sensor.mipi_index, ov5648_foxconn_sensor.mipi_lane_count);
}
/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_get_sensor_reg;
 * Description : read sensor's reg value;
 * Input       : reg, register to be read;
 * Output      : pvalue, value readed from reg;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/

static void  ov5648_foxconn_get_sensor_reg(int reg, int *pvalue)
{
	u8 value = 0;
	if (NULL == pvalue)
	{
		print_error("%s, NULL data pointer!", __func__);
		return;
	}
	 ov5648_foxconn_read_reg(reg, &value);
	*pvalue = value;
	//print_info("%s, reg:0x%x, value:0x%x", __func__, reg, *pvalue);
	return;
}
/*
 **************************************************************************
 * FunctionName:  ov5648_foxconn_set_sensor_reg;
 * Description : write sensor's reg value;
 * Input       : reg, register to be write;
 * Output      : value, value to be writen;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void  ov5648_foxconn_set_sensor_reg(int reg, int value)
{
	 ov5648_foxconn_write_reg(reg, value & 0xff, 0x00);
	return;
}
/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_check_otp;
 * Description : check otp's status;
 * Input       : NA;
 * Output      : current otp status;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov5648_foxconn_check_otp(sensor_otp_status * status)
{
	if (NULL == status)
	{
		print_error("%s, NULL data pointer!", __func__);
		return;
	}
	if (OV5648_FOXCONN_OTP_VALID ==ov5648_foxconn_otp_flag)
	{
		*status = OTP_VALID;
	}
	else
	{
		*status = OTP_INVALID;
	}
	print_info("otp status:%d", *status);
}
static int ov5648_foxconn_get_equivalent_focus(void)
{
	print_debug("enter %s", __func__);
	return OV5648_FOXCONN_EQUIVALENT_FOCUS;
}
/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_set_default;
 * Description : init ov5648_foxconn_sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov5648_foxconn_set_default(void)
{
	ov5648_foxconn_sensor.init = ov5648_foxconn_init;
	ov5648_foxconn_sensor.exit = ov5648_foxconn_exit;
	ov5648_foxconn_sensor.reset = ov5648_foxconn_reset;
	ov5648_foxconn_sensor.shut_down = ov5648_foxconn_shut_down;
	ov5648_foxconn_sensor.check_sensor = ov5648_foxconn_check_sensor;
	ov5648_foxconn_sensor.power = ov5648_foxconn_power;
	ov5648_foxconn_sensor.init_reg = ov5648_foxconn_init_reg;
	ov5648_foxconn_sensor.stream_on = ov5648_foxconn_stream_on;

	ov5648_foxconn_sensor.get_format = ov5648_foxconn_get_format;
	ov5648_foxconn_sensor.set_flash = NULL;
	ov5648_foxconn_sensor.get_flash = NULL;
	ov5648_foxconn_sensor.set_scene = NULL;
	ov5648_foxconn_sensor.get_scene = NULL;

	ov5648_foxconn_sensor.enum_framesizes = ov5648_foxconn_enum_framesizes;
	ov5648_foxconn_sensor.try_framesizes = ov5648_foxconn_try_framesizes;
	ov5648_foxconn_sensor.set_framesizes = ov5648_foxconn_set_framesizes;
	ov5648_foxconn_sensor.get_framesizes = ov5648_foxconn_get_framesizes;

	ov5648_foxconn_sensor.enum_frame_intervals = ov5648_foxconn_enum_frame_intervals;
	ov5648_foxconn_sensor.try_frame_intervals = NULL;
	ov5648_foxconn_sensor.set_frame_intervals = NULL;
	ov5648_foxconn_sensor.get_frame_intervals = NULL;
	ov5648_foxconn_sensor.get_capability = ov5648_foxconn_get_capability;

	ov5648_foxconn_sensor.sensor_hw_3a.support_awb_otp = ov5648_foxconn_support_awb_otp;

	strncpy(ov5648_foxconn_sensor.info.name, "ov5648_foxconn", sizeof(ov5648_foxconn_sensor.info.name));
	ov5648_foxconn_sensor.interface_type = MIPI2;
	ov5648_foxconn_sensor.mipi_lane_count = CSI_LINES_2;
	ov5648_foxconn_sensor.mipi_index = CSI_INDEX_1;
	ov5648_foxconn_sensor.sensor_index = CAMERA_SENSOR_SECONDARY;
	ov5648_foxconn_sensor.skip_frames = 2;

	ov5648_foxconn_sensor.capture_skip_frames = CAPTURE_SKIP_2;


	ov5648_foxconn_sensor.power_conf.pd_valid = LOW_VALID;
	ov5648_foxconn_sensor.power_conf.reset_valid = LOW_VALID;
	ov5648_foxconn_sensor.i2c_config.index = I2C_SECONDARY;
	ov5648_foxconn_sensor.i2c_config.speed = I2C_SPEED_400;
	ov5648_foxconn_sensor.i2c_config.addr = OV5648_FOXCONN_SLAVE_ADDRESS;
	ov5648_foxconn_sensor.i2c_config.addr_bits = I2C_16BIT;
	ov5648_foxconn_sensor.i2c_config.val_bits = I2C_8BIT;

	ov5648_foxconn_sensor.preview_frmsize_index = 0;
	ov5648_foxconn_sensor.capture_frmsize_index = 0;
	ov5648_foxconn_sensor.frmsize_list =  ov5648_foxconn_config_settings[0].framesizes.framesize_setting;
	ov5648_foxconn_sensor.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW10;
	ov5648_foxconn_sensor.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW10;
#ifdef OV5648_FOXCONN_AP_WRITEAE_MODE
	ov5648_foxconn_sensor.aec_addr[0] = 0;
	ov5648_foxconn_sensor.aec_addr[1] = 0;
	ov5648_foxconn_sensor.aec_addr[2] = 0;
	ov5648_foxconn_sensor.agc_addr[0] = 0;
	ov5648_foxconn_sensor.agc_addr[1] = 0;
	ov5648_foxconn_sensor.ap_writeAE_delay = 0;
#else
	ov5648_foxconn_sensor.aec_addr[0] = 0x3500;
	ov5648_foxconn_sensor.aec_addr[1] = 0x3501;
	ov5648_foxconn_sensor.aec_addr[2] = 0x3502;
	ov5648_foxconn_sensor.agc_addr[0] = 0x350a;
	ov5648_foxconn_sensor.agc_addr[1] = 0x350b;
#endif
	ov5648_foxconn_sensor.sensor_type = SENSOR_OV;
//	ov5648_foxconn_sensor.sensor_type = SENSOR_LIKE_SONY;
	ov5648_foxconn_sensor.get_vts_reg_addr = ov5648_foxconn_get_vts_reg_addr;
    ov5648_foxconn_sensor.set_vts = ov5648_foxconn_set_vts;
	ov5648_foxconn_sensor.set_gain = ov5648_foxconn_set_gain;
	ov5648_foxconn_sensor.set_exposure = ov5648_foxconn_set_exposure;
//	ov5648_foxconn_sensor.set_exposure_gain = ov5648_foxconn_set_exposure_gain;

       ov5648_foxconn_sensor.sensor_dump_reg = ov5648_foxconn_dump_reg_debug;

	ov5648_foxconn_sensor.get_override_param = ov5648_foxconn_get_override_param;

	ov5648_foxconn_sensor.sensor_gain_to_iso = ov5648_foxconn_gain_to_iso;
	ov5648_foxconn_sensor.sensor_iso_to_gain = ov5648_foxconn_iso_to_gain;

	ov5648_foxconn_sensor.get_sensor_aperture = ov5648_foxconn_get_sensor_aperture;
	ov5648_foxconn_sensor.get_equivalent_focus = ov5648_foxconn_get_equivalent_focus;
	ov5648_foxconn_sensor.isp_location = CAMERA_USE_K3ISP;
	ov5648_foxconn_sensor.sensor_tune_ops = NULL;

	ov5648_foxconn_sensor.af_enable = 0;

	ov5648_foxconn_sensor.sensor_gain_to_iso = ov5648_foxconn_gain_to_iso;
	ov5648_foxconn_sensor.sensor_iso_to_gain = ov5648_foxconn_iso_to_gain;
	ov5648_foxconn_sensor.image_setting.lensc_param = ov5648_foxconn_lensc_param;
	ov5648_foxconn_sensor.image_setting.ccm_param = ov5648_foxconn_ccm_param;
	ov5648_foxconn_sensor.image_setting.awb_param = ov5648_foxconn_awb_param;

	/*default is preview size */
	ov5648_foxconn_sensor.fps_max = 30;
	ov5648_foxconn_sensor.fps_min = 16;
	ov5648_foxconn_sensor.fps = 25;

	/*defalt flip*/
	ov5648_foxconn_sensor.vflip			= 0;
	ov5648_foxconn_sensor.hflip			= 0;
	ov5648_foxconn_sensor.old_flip		= 0;
	ov5648_foxconn_sensor.set_vflip		= ov5648_foxconn_set_vflip;
	ov5648_foxconn_sensor.set_hflip		= ov5648_foxconn_set_hflip;
	ov5648_foxconn_sensor.get_vflip		= ov5648_foxconn_get_vflip;
	ov5648_foxconn_sensor.get_hflip		= ov5648_foxconn_get_hflip;
	ov5648_foxconn_sensor.update_flip		= ov5648_foxconn_update_flip;
	ov5648_foxconn_sensor.sensor_rgb_type = SENSOR_BGGR;

	ov5648_foxconn_sensor.owner = THIS_MODULE;

	ov5648_foxconn_sensor.info.facing = CAMERA_FACING_FRONT;
	ov5648_foxconn_sensor.info.orientation = 270;
	ov5648_foxconn_sensor.info.focal_length = 238; /* 2.38mm*/
	ov5648_foxconn_sensor.info.h_view_angle = 75;
	ov5648_foxconn_sensor.info.v_view_angle = 60;

	ov5648_foxconn_sensor.lane_clk = CLK_450M;
	ov5648_foxconn_sensor.effect = ov5648_foxconn_config_settings[0].effect;
	ov5648_foxconn_sensor.support_summary = false;
	ov5648_foxconn_sensor.init_isp_reg = ov5648_foxconn_init_isp_reg;
	ov5648_foxconn_sensor.isp_idi_skip = false;

	ov5648_foxconn_sensor.stream_off_setting = ov5648_foxconn_stream_off_regs;
	ov5648_foxconn_sensor.stream_off_setting_size = ARRAY_SIZE(ov5648_foxconn_stream_off_regs);
//	ov5648_foxconn_sensor.stream_on_setting = ov5648_foxconn_stream_on_regs;
//	ov5648_foxconn_sensor.stream_on_setting_size = ARRAY_SIZE(ov5648_foxconn_stream_on_regs);

	/*if there have different data rate of sensor resolution we need this config_dphy_clk
	   otherwise if all resolution is same rate config_dphy_clk must to be null*/
	ov5648_foxconn_sensor.config_dphy_clk = ov5648_foxconn_config_dphy_clk;
	ov5648_foxconn_sensor.get_sensor_reg = ov5648_foxconn_get_sensor_reg;
	ov5648_foxconn_sensor.set_sensor_reg = ov5648_foxconn_set_sensor_reg;
	ov5648_foxconn_sensor.reset_dphy = ov5648_foxconn_reset_dphy;
	ov5648_foxconn_sensor.check_otp_status = ov5648_foxconn_check_otp;

}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int ov5648_foxconn_module_init(void)
{
	ov5648_foxconn_set_default();
	return register_camera_sensor(ov5648_foxconn_sensor.sensor_index, &ov5648_foxconn_sensor);
}

/*
 **************************************************************************
 * FunctionName: ov5648_foxconn_module_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void __exit ov5648_foxconn_module_exit(void)
{
	unregister_camera_sensor(ov5648_foxconn_sensor.sensor_index, &ov5648_foxconn_sensor);
}

MODULE_AUTHOR("Hisilicon");
module_init(ov5648_foxconn_module_init);
module_exit(ov5648_foxconn_module_exit);
MODULE_LICENSE("GPL");

/********************************** END **********************************************/
