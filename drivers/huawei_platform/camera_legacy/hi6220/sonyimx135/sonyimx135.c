/*
 *  sonyimx135 camera driver source file
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
#include "sonyimx135.h"
#include <asm/bug.h>
#include <linux/device.h>
#include "video_config.h"
#include "effect.h"

#define LOG_TAG "SONYIMX135"
/* #define DEBUG_DEBUG 1 */
#include "cam_log.h"
#include <cam_util.h>

#define _IS_DEBUG_AE	0

#define SONYIMX135_SLAVE_ADDRESS1		0x20
//#define SONYIMX135_SLAVE_ADDRESS2		0x34

//#define SONYIMX135_CHIP_ID				(0x0087)

//#define SONYIMX135_CHIP_ID_ES1_ADRESS_H		(0x0000)
//#define SONYIMX135_CHIP_ID_ES1_ADRESS_L		(0x0001)
//#define SONYIMX135_CHIP_ID_ES1				(0x0087)

#define SONYIMX135_CHIP_ID_ES2_ADRESS_H		(0x0016)
#define SONYIMX135_CHIP_ID_ES2_ADRESS_L		(0x0017)
#define SONYIMX135_CHIP_ID_ES2				(0x0135)

//#define SONYIMX135_CAM_MODULE_SKIPFRAME     4

#define SONYIMX135_FLIP						(0x0101)

#define SONYIMX135_VTS_REG_H					(0x0340)
#define SONYIMX135_VTS_REG_L					(0x0341)

#define SONYIMX135_AP_WRITEAE_MODE
#define SONYIMX135_MAX_ANALOG_GAIN			8

#define SONYIMX135_GROUP_HOLD_FUNCTION_REG	(0x0104)

#define SONYIMX135_EXPOSURE_REG_H		(0x0202)
#define SONYIMX135_EXPOSURE_REG_L		(0x0203)
//#define SONYIMX135_ANA_GAIN_REG_H		(0x0204)
#define SONYIMX135_ANA_GAIN_REG_L		(0x0205)
#define SONYIMX135_DIG_GAIN_GR_REG_H 	(0x020E)
#define SONYIMX135_DIG_GAIN_GR_REG_L 	(0x020F)
#define SONYIMX135_DIG_GAIN_GB_REG_H 	(0x0214)
#define SONYIMX135_DIG_GAIN_GB_REG_L 	(0x0215)
#define SONYIMX135_DIG_GAIN_R_REG_H         (0x0210)
#define SONYIMX135_DIG_GAIN_R_REG_L     	(0x0211)
#define SONYIMX135_DIG_GAIN_B_REG_H    	(0x0212)
#define SONYIMX135_DIG_GAIN_B_REG_L    	(0x0213)

#if 0  /*not referenced, pclint fail, 20140509*/
/* registers for hdr_movie_mode begin */
#define SONYIMX135_WD_COARSE_INTEG_TIME_DS_H     		(0x0230)
#define SONYIMX135_WD_COARSE_INTEG_TIME_DS_L     		(0x0231)
#define SONYIMX135_COARSE_INTEG_TIME_WHT_DIRECT_H    	(0x0240)
#define SONYIMX135_COARSE_INTEG_TIME_WHT_DIRECT_L    	(0x0241)
#define SONYIMX135_COARSE_INTEG_TIME_WHT_DS_DIRECT_H 	(0x023E)
#define SONYIMX135_COARSE_INTEG_TIME_WHT_DS_DIRECT_L 	(0x023F)
#define SONYIMX135_WD_ANA_GAIN_DS						(0x0233)

#define SONYIMX135_ATR_OFF_SETTING_1             	(0x446D)
#define SONYIMX135_ATR_OFF_SETTING_2             	(0x446E)
#define SONYIMX135_TRIGGER_SETTING                  	(0x446C)

#define  SONYIMX135_WB_LMT_REG_H                       (0x441E)
#define  SONYIMX135_WB_LMT_REG_L                        (0x441F)

#define SONYIMX135_AE_SAT_REG_H				(0x4446)
#define SONYIMX135_AE_SAT_REG_L                          (0x4447)
#define SONYIMX135_ATR_OUT_NOISE_REG_H        	(0x4452)
#define SONYIMX135_ATR_OUT_NOISE_REG_L        	(0x4453)
#define SONYIMX135_ATR_OUT_MID_REG_H        	(0x4454)
#define SONYIMX135_ATR_OUT_MID_REG_L        	(0x4455)
#define SONYIMX135_ATR_OUT_SAT_REG_H        	(0x4456)
#define SONYIMX135_ATR_OUT_SAT_REG_L        	(0x4457)
#define SONYIMX135_ATR_NOISE_BRATE_REG     	(0x4458)
#define SONYIMX135_ATR_MID_BRATE_REG        	(0x4459)
#define SONYIMX135_ATR_SAT_BRATE_REG        	(0x445a)

#define SONYIMX135_ABS_GAIN_B_REG_H			(0x0716)
#define SONYIMX135_ABS_GAIN_B_REG_L			(0x0717)
#define SONYIMX135_ABS_GAIN_GB_REG_H		(0x0718)
#define SONYIMX135_ABS_GAIN_GB_REG_L		(0x0719)
#define SONYIMX135_ABS_GAIN_GR_REG_H		(0x0712)
#define SONYIMX135_ABS_GAIN_GR_REG_L		(0x0713)
#define SONYIMX135_ABS_GAIN_R_REG_H			(0x0714)
#define SONYIMX135_ABS_GAIN_R_REG_L			(0x0715)
/* registers for hdr_movie_mode end */

#define SONYIMX135_ZSL		(0x00)
#endif

#define SONYIMX135_OTP_MODE_ENABLE_REG		0x3B00
#define SONYIMX135_OTP_STATUS_REG			0x3B01
#define SONYIMX135_OTP_PAGE_SELECT_REG		0x3B02
//#define SONYIMX135_OTP_CFA_FMT_REG			0x3B2C

#define SONYIMX135_SENSOR_LSC_MODE			0x0700
#define SONYIMX135_SENSOR_LSC_EN				0x4500
#define SONYIMX135_SENSOR_RAM_SEL			0x3A63

#define SONYIMX135_SENSOR_LSC_RAM			0x4800

#define SONYIMX135_I2C_RETRY_TIMES          5
/* OTP lens shading parameters are 9*7*4 in toal, each parameter takes 2 bytes. */
#define SONYIMX135_OTP_LSC_SIZE				504

#define SONYIMX135_OTP_LSC_FILE				"/data/lsc_param"

#define SONYIMX135_OTP_ID_WB_READ			(1 << 0)
#define SONYIMX135_OTP_VCM_READ				(1 << 1)
#define SONYIMX135_OTP_LSC_READ				(1 << 2)
#define SONYIMX135_OTP_LSC_WRITED			(1 << 3)
#define SONYIMX135_OTP_LSC_FILE_ERR         		(1 << 4)

#define SONYIMX135_DPC_THRESHOLD_ISO		400
static u8 sonyimx135_otp_flag = 0;

/* OTP lens shading ID. */
static u8 sonyimx135_otp_lsc_id = 0x00;
/* VCM start and end values */
static u16 sonyimx135_vcm_start = 0;
static u16 sonyimx135_vcm_end = 0;
#define SONYIMX135_STARTCODE_OFFSET             	0x40
/* OTP parameters. */
static otp_id_wb_t sonyimx135_otp_id_wb;
static otp_vcm_t sonyimx135_otp_vcm;
static u8 sonyimx135_otp_lsc_param[SONYIMX135_OTP_LSC_SIZE] = {0
};
static camera_capability sonyimx135_cap[] = {
	{V4L2_CID_FLASH_MODE, THIS_FLASH},
	{V4L2_CID_FOCUS_MODE, THIS_FOCUS_MODE},
	{V4L2_CID_FOCAL_LENGTH, 385},//3.85mm
	//{V4L2_CID_ZSL,SONYIMX135_ZSL} ,
};

static int sensor_mode_index = -1;
static framesize_s *sonyimx135_framesizes = NULL;

typedef enum _sonyimx135_sensor_check
{
  IMX135_UNKOWN = -1,
  IMX135_FOUND,
}sonyimx135_sensor_check;

/*
 * should be calibrated, three lights, from 0x1c264
 * here is long exposure
 */
static char sonyimx135_lensc_param[86*3] = {
};

/* should be calibrated, 6 groups 3x3, from 0x1c1d8 */
static short sonyimx135_ccm_param[54] = {
};

static char sonyimx135_awb_param[] = {
};

static vcm_info_s vcm_dw9714_param = {
    #include "vcm_dw9714.h"
};

static effect_params effect_imx135_liteon = {
#include "effect_imx135_liteon.h"
};

#if 0
static framesize_s sonyimx135_rgbw_es1_framesizes[] = {
	{0, 2, 2048, 1536, 4572, 1850, 30, 25, 0x19A, 0x155, 0x100, VIEW_FULL, RESOLUTION_4_3, true, false,{sonyimx135_rgbw_es1_framesize_2048x1536, ARRAY_SIZE(sonyimx135_rgbw_es1_framesize_2048x1536)} },
	{0, 2, 4160, 3120, 4572, 3142, 10, 5, 0x15D, 0x123, 0xA0, VIEW_FULL, RESOLUTION_4_3, false, false,{sonyimx135_rgbw_es1_framesize_full, ARRAY_SIZE(sonyimx135_rgbw_es1_framesize_full)} },
};
#endif

static const struct _sensor_reg_t sonyimx135_stream_off_regs[] = {
	{0x0100, 0x00}
};


static framesize_s sonyimx135_rgb_framesizes[] = {
	//{0, 0, 1920, 1088, 4572, 2624, 30, 25, 0x313, 0x290, 0x100, VIEW_HDR_MOVIE, RESOLUTION_16_9, false, false,{sonyimx135_rgb_framesize_1920x1088_HDR, ARRAY_SIZE(sonyimx135_rgb_framesize_1920x1088_HDR)} },
	//{0, 0, 2048, 1536, 4572, 3236, 21, 21, 0x313, 0x290, 0x100, VIEW_HDR_MOVIE, RESOLUTION_4_3, false, false,{sonyimx135_rgb_framesize_2048x1536_HDR, ARRAY_SIZE(sonyimx135_rgb_framesize_2048x1536_HDR)} },
       //{0, 0, 1920, 1088, 4572, 2324, 30, 30, 0X2BB, 0X247, 0x280, VIEW_FULL, RESOLUTION_16_9, true, false,{sonyimx135_rgb_framesize_1920x1088, ARRAY_SIZE(sonyimx135_rgb_framesize_1920x1088)}, CLK_750M},
	{0, 0, 2080, 1560, 4572, 2330, 30, 30, 0x2BB, 0x247, 0x280, VIEW_FULL, RESOLUTION_4_3, true, false,{sonyimx135_rgb_framesize_2080x1560, ARRAY_SIZE(sonyimx135_rgb_framesize_2080x1560)}, CLK_750M },
	{0, 0, 3264, 2448, 4572, 3142, 30, 30, 0x3B0, 0x313, 0x360, VIEW_FULL, RESOLUTION_4_3, false, true,{sonyimx135_rgb_framesize_3264x2448, ARRAY_SIZE(sonyimx135_rgb_framesize_3264x2448)}, CLK_1100M },
	{0, 0, 3280, 1960, 4572, 2566, 30, 30, 0x301, 0x281, 0x2C0, VIEW_FULL, RESOLUTION_16_9, false, true,{sonyimx135_rgb_framesize_3280x1960, ARRAY_SIZE(sonyimx135_rgb_framesize_3280x1960)},CLK_900M },
	{0, 0, 4160, 3120, 4572, 3264, 23, 23, 0x2F0, 0x273, 0x2B0, VIEW_FULL, RESOLUTION_4_3, false, true,{sonyimx135_rgb_framesize_4160x3120_zsl, ARRAY_SIZE(sonyimx135_rgb_framesize_4160x3120_zsl)},CLK_900M },	
	{0, 0, 4160, 3120, 4582, 4664, 10, 10, 0x1A3, 0x15D, 0x17F, VIEW_FULL, RESOLUTION_4_3, false, false,{sonyimx135_rgb_framesize_4160x3120_nozsl_full, ARRAY_SIZE(sonyimx135_rgb_framesize_4160x3120_nozsl_full)}, CLK_450M},	
};

#if 0
static framesize_s sonyimx135_rgbw_es2_framesizes[] = {
	{0, 2, 2048, 1536, 4572, 1850, 30, 25, 0x19A, 0x155, 0x100, VIEW_FULL, RESOLUTION_4_3, true, false,{sonyimx135_rgbw_es2_framesize_2048x1536, ARRAY_SIZE(sonyimx135_rgbw_es2_framesize_2048x1536)} },
	{0, 2, 4160, 3120, 4572, 3142, 10, 5, 0x15D, 0x123, 0xA0, VIEW_FULL, RESOLUTION_4_3, false, false,{sonyimx135_rgbw_es2_framesize_full, ARRAY_SIZE(sonyimx135_rgbw_es2_framesize_full)} },
};
#endif

/******************************************/

typedef struct _imx135_sensor_module{
	char  *sensor_name;
	u16    i2c_address_h;
	u16    i2c_address_l;
	u16   chip_id;
	u32   slave_addr;
	u8   cfa_fmt;
	const sensor_reg_t *preg;
	u32   reg_size;
	framesize_s *framesizes;
	u32   frame_size;
} imx135_sensor_module;

static imx135_sensor_module sonyimx135_sensor_module[] = {
	{"sonyimx135_RGB_ES2_ADDR1",  SONYIMX135_CHIP_ID_ES2_ADRESS_H,SONYIMX135_CHIP_ID_ES2_ADRESS_L,SONYIMX135_CHIP_ID_ES2, SONYIMX135_SLAVE_ADDRESS1, 0x00,
	     sonyimx135_rgb_init_regs, ARRAY_SIZE(sonyimx135_rgb_init_regs),sonyimx135_rgb_framesizes,ARRAY_SIZE(sonyimx135_rgb_framesizes)},
	//{"sonyimx135_RGB_ES2_ADDR2",  SONYIMX135_CHIP_ID_ES2_ADRESS_H,SONYIMX135_CHIP_ID_ES2_ADRESS_L,SONYIMX135_CHIP_ID_ES2, SONYIMX135_SLAVE_ADDRESS2, 0x80,
	//  sonyimx135_rgb_init_regs, ARRAY_SIZE(sonyimx135_rgb_init_regs),sonyimx135_rgb_framesizes,ARRAY_SIZE(sonyimx135_rgb_framesizes)},
	//{"sonyimx135_RGBW_ES1_ADDR1", SONYIMX135_CHIP_ID_ES1_ADRESS_H,SONYIMX135_CHIP_ID_ES1_ADRESS_L,SONYIMX135_CHIP_ID_ES1, SONYIMX135_SLAVE_ADDRESS1, 0x00,
	//	sonyimx135_rgbw_es1_init_regs, ARRAY_SIZE(sonyimx135_rgbw_es1_init_regs),sonyimx135_rgbw_es1_framesizes,ARRAY_SIZE(sonyimx135_rgbw_es1_framesizes)},
	//{"sonyimx135_RGBW_ES2_ADDR1", SONYIMX135_CHIP_ID_ES2_ADRESS_H,SONYIMX135_CHIP_ID_ES2_ADRESS_L,SONYIMX135_CHIP_ID_ES2, SONYIMX135_SLAVE_ADDRESS1, 0x00,
	//      sonyimx135_rgbw_es2_init_regs, ARRAY_SIZE(sonyimx135_rgbw_es2_init_regs),sonyimx135_rgbw_es2_framesizes,ARRAY_SIZE(sonyimx135_rgbw_es2_framesizes)},
};

static camera_sensor sonyimx135_sensor;
static void sonyimx135_set_default(void);
static void sonyimx135_otp_get_vcm(u16 *vcm_start, u16 *vcm_end);
static void sonyimx135_otp_update_afwb(void);
static void sonyimx135_otp_enable_lsc(bool enable);
static void sonyimx135_otp_record_lsc_func(struct work_struct *work);
static struct work_struct record_otp_lsc_work;
static bool sonyimx135_otp_read_lsc(void);
static bool sonyimx135_otp_set_lsc(void);
#ifdef CONFIG_DEBUG_FS
extern u32 get_main_sensor_id(void);
#endif
static void sonyimx135_config_dphy_clk(camera_state state);

/*
 **************************************************************************
 * FunctionName: sonyimx135_read_reg;
 * Description : read sonyimx135 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_read_reg(u16 reg, u8 *val)
{
	return k3_ispio_read_reg(sonyimx135_sensor.i2c_config.index,
				 sonyimx135_sensor.i2c_config.addr, reg, (u16 *)val, sonyimx135_sensor.i2c_config.val_bits,sonyimx135_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_write_reg;
 * Description : write sonyimx135 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_write_reg(u16 reg, u8 val, u8 mask)
{
	return k3_ispio_write_reg(sonyimx135_sensor.i2c_config.index,
			sonyimx135_sensor.i2c_config.addr, reg, val, sonyimx135_sensor.i2c_config.val_bits, mask,sonyimx135_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_write_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int sonyimx135_write_seq(const struct _sensor_reg_t *seq, u32 size, u8 mask)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	return k3_ispio_write_seq(sonyimx135_sensor.i2c_config.index,
			sonyimx135_sensor.i2c_config.addr, seq, size, sonyimx135_sensor.i2c_config.val_bits, mask,sonyimx135_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_write_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void sonyimx135_write_isp_seq(const struct isp_reg_t *seq, u32 size)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	k3_ispio_write_isp_seq(seq, size);
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_enum_frame_intervals;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_enum_frame_intervals(struct v4l2_frmivalenum *fi)
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
 * FunctionName: sonyimx135_get_format;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_get_format(struct v4l2_fmtdesc *fmt)
{
	if (fmt->type == V4L2_BUF_TYPE_VIDEO_OVERLAY)
		fmt->pixelformat = sonyimx135_sensor.fmt[STATE_PREVIEW];
	else
		fmt->pixelformat = sonyimx135_sensor.fmt[STATE_CAPTURE];

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_enum_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 max_index = ARRAY_SIZE(camera_framesizes) - 1;
	u32 this_max_index =    sonyimx135_sensor_module[sensor_mode_index].frame_size -1;

	assert(framesizes);

	if(NULL == framesizes) {
		return -EINVAL;
	}

	print_debug("enter %s; ", __func__);

	if (framesizes->index > max_index) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	if ((camera_framesizes[framesizes->index].width > sonyimx135_framesizes[this_max_index].width)
		|| (camera_framesizes[framesizes->index].height > sonyimx135_framesizes[this_max_index].height)) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	framesizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	framesizes->discrete.width = sonyimx135_framesizes[this_max_index].width;
	framesizes->discrete.height = sonyimx135_framesizes[this_max_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_try_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_try_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	int max_index = sonyimx135_sensor_module[sensor_mode_index].frame_size -1;

	assert(framesizes);

	if(NULL == framesizes) {
		return -EINVAL;
	}

	print_debug("Enter Function:%s  ", __func__);


	if ((framesizes->discrete.width <= sonyimx135_framesizes[max_index].width)
	    && (framesizes->discrete.height <= sonyimx135_framesizes[max_index].height)) {
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
 * FunctionName: sonyimx135_set_framesizes;
 * Description : NA;
 * Input       : flag: if 1, set framesize to sensor,
 *					   if 0, only store framesize to camera_interface;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_set_framesizes(camera_state state,
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

        size = sonyimx135_sensor_module[sensor_mode_index].frame_size;
#if 0//not include HDR moive
	if(HDR_MOVIE_ON == sonyimx135_sensor.sensor_hdr_movie.hdrInfo.hdr_on){
		for (i = 0; i < size; i++) {
			if ((sonyimx135_framesizes[i].width >= fs->width)
				    && (sonyimx135_framesizes[i].height >= fs->height)
				    && (camera_get_resolution_type(fs->width, fs->height)
					   <= sonyimx135_framesizes[i].resolution_type)
				    && (VIEW_HDR_MOVIE == sonyimx135_framesizes[i].view_type))
			 {
					fs->width = sonyimx135_framesizes[i].width;
					fs->height = sonyimx135_framesizes[i].height;
					match = true;
					print_info("enter %s,resolution_type=%d,i= %d",__func__,camera_get_resolution_type(fs->width, fs->height),i);
					break;
			}
		}
	}else{
#endif//
		if (VIEW_FULL == view_type) {
			for (i = 0; i < size; i++) {
				if ((zsl_preview == false) && sonyimx135_framesizes[i].zsl_only )
				{
				    continue;
				}
				if ((sonyimx135_framesizes[i].width >= fs->width)
				    && (sonyimx135_framesizes[i].height >= fs->height)
				    && (VIEW_FULL == sonyimx135_framesizes[i].view_type)
				    && (camera_get_resolution_type(fs->width, fs->height)
				    <= sonyimx135_framesizes[i].resolution_type)) {
					fs->width = sonyimx135_framesizes[i].width;
					fs->height = sonyimx135_framesizes[i].height;
					match = true;
					break;
				}
			}
		}
//	}

	if (false == match) {
		for (i = 0; i < size; i++) {
			if ((zsl_preview == false) && sonyimx135_framesizes[i].zsl_only )
			{
			    continue;
			}
			if ((sonyimx135_framesizes[i].width >= fs->width)
			    && (sonyimx135_framesizes[i].height >= fs->height)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= sonyimx135_framesizes[i].resolution_type)){
				fs->width = sonyimx135_framesizes[i].width;
				fs->height = sonyimx135_framesizes[i].height;
				break;
			}
		}
	}

	if (i >= size) {
		print_error("request resolution larger than sensor's max resolution");
		return -EINVAL;
	}

	if (state == STATE_PREVIEW)
		sonyimx135_sensor.preview_frmsize_index = i;
	else
		sonyimx135_sensor.capture_frmsize_index = i;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_init_isp_reg;
 * Description : load initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_init_isp_reg(void)
{
	int size = 0;
	camera_sensor *sensor = &sonyimx135_sensor;

	size = CAMERA_MAX_SETTING_SIZE;
#if 0
	if( HDR_MOVIE_ON== sonyimx135_sensor.sensor_hdr_movie.hdrInfo.hdr_on)
	{
		sonyimx135_write_isp_seq(sensor->effect->hdr_movie_isp_settings, size);
	}
	else
	{
	sonyimx135_write_isp_seq(sensor->effect->isp_settings, size);
	}
#endif
	sonyimx135_write_isp_seq(sensor->effect->isp_settings, size);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_get_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_get_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs)
{
	int frmsize_index;

	assert(fs);

	if(NULL == fs){
		return -EINVAL;
	}

	if (state == STATE_PREVIEW)
		frmsize_index = sonyimx135_sensor.preview_frmsize_index;
	else if (state == STATE_CAPTURE)
		frmsize_index = sonyimx135_sensor.capture_frmsize_index;
	else
		return -EINVAL;

	fs->width = sonyimx135_framesizes[frmsize_index].width;
	fs->height = sonyimx135_framesizes[frmsize_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_init_reg;
 * Description : download initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_init_reg(void)
{
	int size = 0;
    const sensor_reg_t *sonyimx135_init_regs = sonyimx135_sensor_module[sensor_mode_index].preg;
	print_debug("Enter Function:%s  , initsize=%d",
		    __func__, sizeof(sonyimx135_init_regs));

	if (0 != k3_ispio_init_csi(sonyimx135_sensor.mipi_index,
			sonyimx135_sensor.mipi_lane_count, sonyimx135_sensor.lane_clk)) {
		return -EFAULT;
	}

	//k3_ispio_config_lane_clk(sonyimx135_sensor.mipi_index, sonyimx135_sensor.mipi_lane_count, sonyimx135_sensor.lane_clk);

	size = sonyimx135_sensor_module[sensor_mode_index].reg_size;
	if (0 != sonyimx135_write_seq(sonyimx135_init_regs, size, 0x00)) {
		print_error("line %d, fail to init sonyimx135 sensor", __LINE__);
		return -EFAULT;
	}
	sonyimx135_otp_enable_lsc(false);
	if ((sonyimx135_otp_flag & SONYIMX135_OTP_LSC_READ) || sonyimx135_otp_read_lsc()) {
		if (sonyimx135_otp_set_lsc()) {
			sonyimx135_otp_enable_lsc(true);
		}
	}
	print_info("%s, OTP flag = %#x", __func__, sonyimx135_otp_flag);
	if (!(sonyimx135_otp_flag & SONYIMX135_OTP_LSC_WRITED)) {
		schedule_work(&record_otp_lsc_work);
	}
	return 0;
}

static int sonyimx135_set_hflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);
	sonyimx135_sensor.hflip = flip;
	return 0;
}
static int sonyimx135_get_hflip(void)
{
	print_debug("enter %s", __func__);

	return sonyimx135_sensor.hflip;
}
static int sonyimx135_set_vflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);

	sonyimx135_sensor.vflip = flip;

	return 0;
}
static int sonyimx135_get_vflip(void)
{
	print_debug("enter %s", __func__);
	return sonyimx135_sensor.vflip;
}

static int sonyimx135_update_flip(u16 width, u16 height)
{
	u8 new_flip = ((sonyimx135_sensor.vflip << 1) | sonyimx135_sensor.hflip);
	print_debug("Enter %s  ", __func__);
	//if (sonyimx135_sensor.old_flip != new_flip) {
		k3_ispio_update_flip((sonyimx135_sensor.old_flip ^ new_flip) & 0x03, width, height, PIXEL_ORDER_CHANGED);

		sonyimx135_sensor.old_flip = new_flip;
		if(CAMERA_SENSOR_FLIP_TYPE_H_V == video_get_primary_sensor_flip_type())
		{
			sonyimx135_write_reg(SONYIMX135_FLIP, sonyimx135_sensor.vflip ? 0x00 : 0x02, ~0x02);
			sonyimx135_write_reg(SONYIMX135_FLIP, sonyimx135_sensor.hflip ? 0x00 : 0x01, ~0x01);
		}
		else
		{
			sonyimx135_write_reg(SONYIMX135_FLIP, sonyimx135_sensor.vflip ? 0x02 : 0x00, ~0x02);
			sonyimx135_write_reg(SONYIMX135_FLIP, sonyimx135_sensor.hflip ? 0x01 : 0x00, ~0x01);
		}
		//msleep(200);
	//}
	return 0;
}

static int sonyimx135_get_capability(u32 id, u32 *value)
{
	int i;
	for (i = 0; i < sizeof(sonyimx135_cap) / sizeof(sonyimx135_cap[0]); ++i) {
		if (id == sonyimx135_cap[i].id) {
			*value = sonyimx135_cap[i].value;
			break;
		}
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_framesize_switch;
 * Description : switch frame size, used by preview and capture
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_framesize_switch(camera_state state)
{
	u32 size = 0;
	u8 next_frmsize_index;

	if (state == STATE_PREVIEW)
		next_frmsize_index = sonyimx135_sensor.preview_frmsize_index;
	else
		next_frmsize_index = sonyimx135_sensor.capture_frmsize_index;

	print_debug("Enter Function:%s frm index=%d", __func__, next_frmsize_index);

    size = sonyimx135_sensor_module[sensor_mode_index].frame_size;
	if (next_frmsize_index >= size) {
		print_error("Unsupport sensor setting index: %d", next_frmsize_index);
		return -ETIME;
	}

	if (0 != sonyimx135_write_seq(sonyimx135_sensor.frmsize_list[next_frmsize_index].sensor_setting.setting
		, sonyimx135_sensor.frmsize_list[next_frmsize_index].sensor_setting.seq_size, 0x00)) {
		print_error("fail to init sonyimx135 sensor");
		return -ETIME;
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_stream_on;
 * Description : download preview seq for sensor preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_stream_on(camera_state state)
{
	print_debug("Enter Function:%s ", __func__);
	sonyimx135_config_dphy_clk(state);
	return sonyimx135_framesize_switch(state);
}

/****************************************************************************
* FunctionName: sonyimx135_open_otp_page;
* Description : Open selected OTP page.;
* Input       : page;
* Output      : NA;
* ReturnValue : bool;
* Other       : NA;
***************************************************************************/
static bool sonyimx135_open_otp_page(u8 page)
{
	int loop = 0;
	u8 status = 0;

	sonyimx135_write_reg(SONYIMX135_OTP_PAGE_SELECT_REG, page, 0x00); /* Select OTP page. */
	sonyimx135_write_reg(SONYIMX135_OTP_MODE_ENABLE_REG, 0x01, 0x00); /* Turn on OTP read mode. */
	udelay(2);

	/* Check OTP read ready status. */
	for (loop=0; loop<5; loop++) {
		sonyimx135_read_reg(SONYIMX135_OTP_STATUS_REG, &status);
		status &= 0x01;
		udelay(1);
		if(status)
			break;
		mdelay(1);
	}
	if (!status) {
		print_error("%s: Wait OTP page%d read ready status timeout.", __func__, page);
		return false;
	}

	return true;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_reset_i2c;
 * Description : reset i2c address to isp;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx135_reset_i2c(struct i2c_t *i2c)
{
	//k3_ispio_reset_i2c(i2c);
	print_info("%s, addr=%#x", __func__, i2c->addr);
	memcpy(&isp_hw_data.i2c_config, i2c, sizeof(struct i2c_t));

	if (i2c->index == I2C_PRIMARY) {
		SETREG8(REG_SCCB_MAST1_SLAVE_ID, i2c->addr);
		SETREG8(REG_SCCB_FIRMWARE1_ID, i2c->addr);
	} else {
		SETREG8(REG_SCCB_MAST2_SLAVE_ID, i2c->addr);
		SETREG8(REG_SCCB_FIRMWARE2_ID, i2c->addr);
	}
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_find_sensor;
 * Description :    The function is that finding valid sensor by use of  I2c address , camera id register, cfa_fmt register which
 *                       disinguish rgbw and rgb
 * Input         : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */

static int sonyimx135_find_sensor(imx135_sensor_module fix_sensor)
{
	//u8 fmt = 0;
	u16 id   = 0;
	u8  idh = 0;
	u8  idl  = 0;
       u16 address_h  = 0;
	u16 address_l  = 0;
	u16 chip_id;
	u8  fix_sensor_fmt = -1;
    int retry = 0;
	print_debug("enter %s", __func__);
	sonyimx135_sensor.i2c_config.addr = fix_sensor.slave_addr;
       address_h =  fix_sensor.i2c_address_h;
       address_l  =  fix_sensor.i2c_address_l;

    	sonyimx135_reset_i2c(&sonyimx135_sensor.i2c_config);
        chip_id = fix_sensor.chip_id;
    for(retry = 0; retry < SONYIMX135_I2C_RETRY_TIMES; retry++) {
    	sonyimx135_read_reg(address_h, &idh);
    	sonyimx135_read_reg(address_l, &idl);
    	id = ((idh << 8) | idl);

        print_info("sonyimx135_find_sensor product id:0x%x, retrytimes:%d", id, retry);
        if(chip_id == id) {
            break;
        }
        udelay(100);
    }
	if (chip_id == id)
	{
	      fix_sensor_fmt = fix_sensor.cfa_fmt;
#if 0
	      if(!sonyimx135_open_otp_page(0))
	      {
	            print_error("otp access error. ");
		     return IMX135_UNKOWN;
	      }

	      sonyimx135_read_reg(OTP_CFA_FMT_REG, &fmt);

	      print_info("enter %s,fmt = %d,fix_sensor_fmt=%d", __func__,fmt,fix_sensor_fmt);
		if(fmt != fix_sensor_fmt)
		{
		     print_error("invalid sensor,it is not rgbw or rgb.");
		     return IMX135_UNKOWN;
		}
#endif

	}
	else
	{
	      print_error("Invalid chip_id  ,Could not load sensor sonyimx135 %s,chip_id = 0x%x,id =0x%x",fix_sensor.sensor_name,chip_id,id);
	      return IMX135_UNKOWN;
	}



	return IMX135_FOUND;
}

#if 0
/*  **************************************************************************
* FunctionName: sonyimx135_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int sonyimx135_check_sensor(void)
{
	u8 idl = 0x1;
	u8 idh = 0x1;
	u16 id = 0;

	int ret = -1;

	ret = sonyimx135_read_reg(0x0000, &idh);
	ret = sonyimx135_read_reg(0x0001, &idl);

#if 0
	ret = sonyimx135_read_reg(0x0002, &val);
	print_info("%s: read 0x0002, ret=%d, val=%d.", __func__, ret, val);

	ret = sonyimx135_read_reg(0x0004, &val);
	print_info("%s: read 0x0004, ret=%d, val=%d.", __func__, ret, val);

	sonyimx135_write_reg(SONYIMX135_FLIP, 0x3,  0);
	ret = sonyimx135_read_reg(SONYIMX135_FLIP, &val);
	print_info("%s: read 0x0101, ret=%d, val=%d.", __func__, ret, val);
#endif
	id = ((idh << 8) | idl);
	print_info("sonyimx135 product id:0x%x", id);
#ifdef CONFIG_DEBUG_FS
	//if (SONYIMX135_CHIP_ID != id) {
	//	id = (u16)get_main_sensor_id();
	//	print_info("sonyimx135 debugfs product id:0x%x", id);
	//}
#endif
	if (SONYIMX135_CHIP_ID != id) {
		print_error("Invalid product id ,Could not load sensor sonyimx135");
		return -ENODEV;
	}

	sonyimx135_sensor.vcm = &vcm_dw9714_param;

	return 0;
}
#endif

/*  **************************************************************************
* FunctionName: sonyimx135_check_sensor_new;
* Description :   The function work for distinguishing all kinds of sensor,include rgbw and rgb
*                       , I2c adress  different camera id;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int sonyimx135_check_sensor_new(void)
{
	int size;
	int i;
       int ret = IMX135_UNKOWN;
	print_debug("enter %s", __func__);
	size = sizeof(sonyimx135_sensor_module) / sizeof(sonyimx135_sensor_module[0]);
      	msleep(20);
	for (i = 0; i < size; i++) {

		ret = sonyimx135_find_sensor(sonyimx135_sensor_module[i]);
		if(ret != IMX135_UNKOWN)
		{
		       sensor_mode_index = i;
                     sonyimx135_framesizes = sonyimx135_sensor_module[i].framesizes;
			sonyimx135_sensor.frmsize_list = sonyimx135_sensor_module[i].framesizes;
			if(!sonyimx135_framesizes)
			{
                           print_error("pointer of sonyimx135_framesizes is Null.");
		             return -ENODEV;
			}
                     break;
		}
	}

	if (ret == IMX135_UNKOWN) {
		print_error("Invalid product id ,Could not load sensor sonyimx135");
		return -ENODEV;
	} else {
		print_info("sonyimx135 sensor mode index :%d,sensor name =%s", sensor_mode_index,sonyimx135_sensor_module[sensor_mode_index].sensor_name);
	}
	sensor_mode_index = 0;
	sonyimx135_framesizes = sonyimx135_sensor_module[sensor_mode_index].framesizes;
	sonyimx135_sensor.frmsize_list = sonyimx135_sensor_module[sensor_mode_index].framesizes;
	sonyimx135_sensor.vcm = &vcm_dw9714_param;
	sonyimx135_sensor.vcm->get_vcm_otp = sonyimx135_otp_get_vcm;
	sonyimx135_otp_update_afwb();
	print_info("%s, OTP flag = %#x", __func__, sonyimx135_otp_flag);
       sonyimx135_sensor.effect = &effect_imx135_liteon;

	return 0;
}

/****************************************************************************
* FunctionName: sonyimx135_power;
* Description : NA;
* Input       : power state of camera;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int sonyimx135_power(camera_power_state power)
{
	int ret = 0;

	if(power == POWER_ON) {
		k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);	
		k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
		udelay(200);
		
		k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
		udelay(1);
		k3_ispio_ioconfig(&sonyimx135_sensor, power);
		k3_ispgpio_power_sensor(&sonyimx135_sensor, power);
		msleep(2);
	} else{
		k3_ispio_deinit_csi(sonyimx135_sensor.mipi_index);
		k3_ispgpio_power_sensor(&sonyimx135_sensor, power);
		k3_ispio_ioconfig(&sonyimx135_sensor, power);
		k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);
		udelay(200);
		k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);
	}
	return ret;
}
/*
 * Here gain is in unit 1/16 of sensor gain,
 * y36721 todo, temporarily if sensor gain=0x10, ISO is 100
 * in fact we need calibrate an ISO-ET-gain table.
 */
static u32 sonyimx135_gain_to_iso(int gain)
{
	return (u32)((gain * 100) / 0x10);
}

static u32 sonyimx135_iso_to_gain(int iso)
{
	return (u32)((iso * 0x10) / 100);
}

 /* *************************************************************************
  * FunctionName: 	: sonyimx135_set_dpc_funciton;
  * Description 	: set dpc register to isp and sensor according to iso
  * Input			: gain
  * Output			: NA;
  * ReturnValue 	: NA;
  * Other       	: NA;
  ***************************************************************************/
static void  sonyimx135_set_dpc_function(u32 gain)
{
	u32	iso = 0 ;
	u32	isp_dpc_size = 0;

	iso = sonyimx135_gain_to_iso(gain);

	if(iso > SONYIMX135_DPC_THRESHOLD_ISO)
	{
		const struct isp_reg_t  isp_dpc_reg[]={
			{0x65409,0x08},
			{0x6540a,0x08},
			{0x6540b,0x01},
			{0x6540c,0x01},
			{0x6540d,0x08},
			{0x6540e,0x08},
			{0x6540f,0x01},
			{0x65410,0x01},
			{0x65408,0x0b},
		};
		isp_dpc_size = ARRAY_SIZE(isp_dpc_reg);
		sonyimx135_write_isp_seq(isp_dpc_reg, isp_dpc_size);
		sonyimx135_write_reg(0x4100, 0xF8, 0x00);
	}else{
		const struct isp_reg_t  isp_dpc_reg[]={
			{0x65409,0x08},
			{0x6540a,0x08},
			{0x6540b,0x08},
			{0x6540c,0x08},
			{0x6540d,0x0c},
			{0x6540e,0x08},
			{0x6540f,0x08},
			{0x65410,0x08},
			{0x65408,0x0b},
		};
		isp_dpc_size = ARRAY_SIZE(isp_dpc_reg);
		sonyimx135_write_isp_seq(isp_dpc_reg, isp_dpc_size);
		sonyimx135_write_reg(0x4100, 0xE8, 0x00);
	}

}
static void sonyimx135_set_exposure_gain(u32 exposure, u32 gain)
{
	u32  analog_gain = 0;
	u32	 tmp_digital_gain = 0;
	u8    digital_ratio = 0;
	u8    digital_h = 0;
	u8    digital_l = 0;
	sonyimx135_set_dpc_function(gain);//modify DPC effect of sonyimx135 sensor
	sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold

	exposure >>= 4; //isp2.2 exposure = register_value/0x10

	sonyimx135_write_reg(SONYIMX135_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_EXPOSURE_REG_L, exposure & 0xff, 0x00);

	if (gain == 0)
		goto out;

	if(gain > SONYIMX135_MAX_ANALOG_GAIN*16)
	{
		/*tmp_digital_gain*256 is keep the decimal part*/
		tmp_digital_gain = (gain*256) >> 4;
		tmp_digital_gain = tmp_digital_gain >> 3;

		digital_ratio = (gain/SONYIMX135_MAX_ANALOG_GAIN) >> 4;
		digital_h = digital_ratio;
		digital_l = tmp_digital_gain - digital_ratio*256;
		analog_gain = SONYIMX135_MAX_ANALOG_GAIN*16;
	}
	else
	{
		analog_gain = gain;
		digital_h = 1;
		digital_l = 0;
	}

	analog_gain = 256 - (256 * 16) / analog_gain;
	sonyimx135_write_reg(SONYIMX135_ANA_GAIN_REG_L, analog_gain & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_GR_REG_H, digital_h & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_GR_REG_L, digital_l & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_GB_REG_H, digital_h & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_GB_REG_L, digital_l & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_R_REG_H, digital_h & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_R_REG_L, digital_l & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_B_REG_H, digital_h & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_B_REG_L, digital_l & 0xff, 0x00);
out:
	sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release

	return;
}

static void sonyimx135_set_exposure(u32 exposure)
{
	exposure >>= 4;
	sonyimx135_write_reg(SONYIMX135_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_EXPOSURE_REG_L, exposure & 0xff, 0x00);
}

static void sonyimx135_set_gain(u32 gain)
{
	if(gain == 0)
		return ;

	gain = 256 - (256 * 16) / gain;
	//sonyimx135_write_reg(SONYIMX135_ANA_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_ANA_GAIN_REG_L, gain & 0xff, 0x00);
}

static void sonyimx135_set_vts(u16 vts)
{
	print_debug("Enter %s  ", __func__);
	sonyimx135_write_reg(SONYIMX135_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_VTS_REG_L, vts & 0xff, 0x00);
}

static u32 sonyimx135_get_vts_reg_addr(void)
{
	return SONYIMX135_VTS_REG_H;
}

/****************************************************************************
* FunctionName: sonyimx135_otp_lsc_file_exist;
* Description : Check if LSC parameter file exist;
* Input       : NA;
* Output      : NA;
* ReturnValue : bool;
* Other       : NA;
***************************************************************************/
static bool sonyimx135_otp_lsc_file_exist(void)
{
	struct file *filp = NULL;

	filp = filp_open(SONYIMX135_OTP_LSC_FILE, O_RDONLY, 0666);
	if (!IS_ERR_OR_NULL(filp)) {
		filp_close(filp, NULL);
		return true;
	}
	print_info("%s, OTP file is not exist.", __func__);

	return false;
}

/****************************************************************************
* FunctionName: sonyimx135_otp_read_file;
* Description : Read OTP LSC parameters to file;
* Input       : NA;
* Output      : NA;
* ReturnValue : bool;
* Other       : NA;
***************************************************************************/
static bool sonyimx135_otp_read_file(void)
{
	bool ret = true;
	mm_segment_t fs;
	struct file *filp = NULL;

	print_debug("enter %s", __func__);
	filp = filp_open(SONYIMX135_OTP_LSC_FILE, O_RDONLY, 0666);
	if (IS_ERR_OR_NULL(filp)) {
		print_error("%s, failed to open file!", __func__);
		ret = false;
		goto ERROR;
	}
	fs = get_fs();
	set_fs(KERNEL_DS);
	if (SONYIMX135_OTP_LSC_SIZE != vfs_read(filp, (char*)sonyimx135_otp_lsc_param, SONYIMX135_OTP_LSC_SIZE, &filp->f_pos)) {
		set_fs(fs);
		ret = false;
		print_error("%s, read file error!", __func__);
		goto ERROR;
	}
	set_fs(fs);
	print_info("%s, read OTP file OK.", __func__);

ERROR:
	if (NULL != filp) {
		filp_close(filp, NULL);
	}

	if (ret) {
		sonyimx135_otp_flag |= SONYIMX135_OTP_LSC_READ;
		sonyimx135_otp_flag |= SONYIMX135_OTP_LSC_WRITED;
	} else {
		sonyimx135_otp_flag |= SONYIMX135_OTP_LSC_FILE_ERR;
	}

	return ret;
}
/****************************************************************************
* FunctionName: sonyimx135_otp_write_file;
* Description : Write OTP LSC parameters to file;
* Input       : NA;
* Output      : NA;
* ReturnValue : bool;
* Other       : NA;
***************************************************************************/
static bool sonyimx135_otp_write_file(void)
{
	bool ret = true;
	mm_segment_t fs;
	struct file *filp = NULL;

	print_debug("enter %s", __func__);
	filp = filp_open(SONYIMX135_OTP_LSC_FILE, O_CREAT|O_WRONLY, 0666);
	if (IS_ERR_OR_NULL(filp)) {
		ret = false;
		print_error("%s, OTP failed to open file!", __func__);
		goto ERROR;
	}
	fs = get_fs();
	set_fs(KERNEL_DS);
	if (SONYIMX135_OTP_LSC_SIZE != vfs_write(filp, (char*)sonyimx135_otp_lsc_param, SONYIMX135_OTP_LSC_SIZE, &filp->f_pos)) {
		set_fs(fs);
		ret = false;
		print_error("%s, OTP write file error!", __func__);
		goto ERROR;
	}
	set_fs(fs);
	print_info("%s, write OTP file OK.", __func__);

ERROR:
	if (NULL != filp) {
		filp_close(filp, NULL);
	}

	if (ret) {
		sonyimx135_otp_flag |= SONYIMX135_OTP_LSC_WRITED;
		sonyimx135_otp_flag &= ~SONYIMX135_OTP_LSC_FILE_ERR;
	}

	return ret;
}
/****************************************************************************
* FunctionName: sonyimx135_otp_check_page;
* Description : Check which page this parameters belong to.;
* Input       : otp_type;
* Output      : NA;
* ReturnValue : bool;
* Other       : NA;
***************************************************************************/
static bool sonyimx135_otp_check_page(otp_type type)
{
	int index = 0;
	int start = 0;
	int end = 0;
	u8 page = 0;
	u8 val1 = 0;
	u8 val2 = 0;

	print_debug("enter %s, OTP type is %d", __func__, type);

	switch (type) {
		case OTP_ID_WB:
			/* Module ID and WB parameters take up Page9~Page12, and can be burned 4 times.*/
			start = OTP_PAGE12;
			end = OTP_PAGE9;
			page = OTP_PAGE12;
			break;
		case OTP_VCM:
			/* AF VCM parameters take up Page13~Page16, and can be burned 4 times. */
			start = OTP_PAGE16;
			end = OTP_PAGE13;
			page = OTP_PAGE16;
			break;
		default:
			print_error("%s: Unsupported OTP type %d.", __func__, type);
			return false;
	}

	/* Find out valid OTP page. */
	for (index=start; index>=end; index--) {
		if (sonyimx135_open_otp_page(page)) {
			/* Check whether current page is valid. */
			sonyimx135_read_reg(0x3B05, &val1);
			sonyimx135_read_reg(0x3B07, &val2);
			if (val1 | val2) {
				break;
			}
		}
		page--;
	}
	if (index < end) {
		print_error("%s: There is no OTP data written.", __func__);
		return false;
	}

	return true;
}
/****************************************************************************
* FunctionName: sonyimx135_otp_read_id_wb;
* Description : Get module ID and WB parameters form OTP.;
* Input       : otp_id_wb_t;
* Output      : NA;
* ReturnValue : bool;
* Other       : NA;
***************************************************************************/
static bool sonyimx135_otp_read_id_wb(void)
{
	print_debug("enter %s", __func__);

	if (!sonyimx135_otp_check_page(OTP_ID_WB)) {
		print_error("%s: Check OTP module info and WB parameters page failed.", __func__);
		return false;
	}

	/* Read module information */
	sonyimx135_read_reg(0x3B04, &sonyimx135_otp_id_wb.year);
	sonyimx135_read_reg(0x3B05, &sonyimx135_otp_id_wb.month);
	sonyimx135_read_reg(0x3B06, &sonyimx135_otp_id_wb.day);
	sonyimx135_read_reg(0x3B07, &sonyimx135_otp_id_wb.cam_code);
	sonyimx135_read_reg(0x3B08, &sonyimx135_otp_id_wb.vend_ver);
	print_debug("%s: Module yield date: %x-%x-%x", __func__,
		sonyimx135_otp_id_wb.year, sonyimx135_otp_id_wb.month, sonyimx135_otp_id_wb.day);
	print_debug("%s: Module code is: %#x, vendor and version info is %#x: ",
		__func__, sonyimx135_otp_id_wb.cam_code, sonyimx135_otp_id_wb.vend_ver);

    /* Read WB parameters */
	sonyimx135_read_reg(0x3B09, &sonyimx135_otp_id_wb.rg_h);
	sonyimx135_read_reg(0x3B0A, &sonyimx135_otp_id_wb.rg_l);
	sonyimx135_read_reg(0x3B0B, &sonyimx135_otp_id_wb.bg_h);
	sonyimx135_read_reg(0x3B0C, &sonyimx135_otp_id_wb.bg_l);
	sonyimx135_read_reg(0x3B0D, &sonyimx135_otp_id_wb.gbgr_h);
	sonyimx135_read_reg(0x3B0E, &sonyimx135_otp_id_wb.gbgr_l);

	sonyimx135_sensor.sensor_hw_3a.awb_otp_value.r_g_high = sonyimx135_otp_id_wb.rg_h;
	sonyimx135_sensor.sensor_hw_3a.awb_otp_value.r_g_low = sonyimx135_otp_id_wb.rg_l;
	sonyimx135_sensor.sensor_hw_3a.awb_otp_value.b_g_high = sonyimx135_otp_id_wb.bg_h;
	sonyimx135_sensor.sensor_hw_3a.awb_otp_value.b_g_low = sonyimx135_otp_id_wb.bg_l;
	sonyimx135_sensor.sensor_hw_3a.awb_otp_value.gb_gr_high = sonyimx135_otp_id_wb.gbgr_h;
	sonyimx135_sensor.sensor_hw_3a.awb_otp_value.gb_gr_low = sonyimx135_otp_id_wb.gbgr_l;

	/* Read lens shading ID */
	sonyimx135_read_reg(0x3B0F, &sonyimx135_otp_lsc_id);

	/* OTP module info and WB param are read  */
	sonyimx135_otp_flag |= SONYIMX135_OTP_ID_WB_READ;

	return true;
}
/****************************************************************************
* FunctionName: sonyimx135_otp_set_id;
* Description : Set module ID information.;
* Input       : otp_id_wb_t;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static void sonyimx135_otp_set_id(void)
{
	print_debug("enter %s", __func__);
}
/****************************************************************************
* FunctionName: sonyimx135_otp_set_wb;
* Description : Set WB parameters to ISP.;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static void sonyimx135_otp_set_wb(void)
{
	print_debug("enter %s", __func__);
}

/****************************************************************************
* FunctionName: sonyimx135_otp_read_lsc;
* Description : Read lens shading parameters form OTP.;
* Input       : NA;
* Output      : NA;
* ReturnValue : bool;
* Other       : NA;
***************************************************************************/
static bool sonyimx135_otp_read_lsc(void)
{
	u8 *pval = NULL;
	u8 page = 0;
	u16 addr_start = 0;
	u16 addr_end = 0;

	print_debug("enter %s", __func__);

	/* If lens shading ID is not read, then read it first. */
	if (0x00 == sonyimx135_otp_lsc_id) {
		if (sonyimx135_otp_check_page(OTP_ID_WB)) {
			sonyimx135_read_reg(0x3B0F, &sonyimx135_otp_lsc_id);
		} else {
			print_error("%s: Read lens shading ID failed.", __func__);
			return false;
		}
	}

	/* Lens shading burned OK. */
	if (0xFF == sonyimx135_otp_lsc_id) {
		if (sonyimx135_otp_lsc_file_exist() && sonyimx135_otp_read_file()) {
			/* LSC param is read  */
			print_info("%s, read OTP LSC form file.", __func__);
			return true;
		}

		pval = &sonyimx135_otp_lsc_param[0];
		memset(sonyimx135_otp_lsc_param, 0, SONYIMX135_OTP_LSC_SIZE);

		/* Lens shading parameters take up Page1~Page8 of OTP, and can be burned only once. */
		for (page=OTP_PAGE1; page<=OTP_PAGE8; page++) {
			if (sonyimx135_open_otp_page(page)) {
				/* Get lens shading parameters from each page. */
				addr_start = 0x3B04;
				if (OTP_PAGE8 == page) {
					addr_end = 0x3B3B; /* In page8, the valid data range is 0x3B04~0x3B3B. */
				} else {
					addr_end = 0x3B43; /* From page1 to page7, the valid data range is 0x3B04~0x3B43. */
				}
				do {
					sonyimx135_read_reg(addr_start, pval);
					addr_start++;
					pval++;
				} while (addr_start <= addr_end);
			}
		}
		print_info("%s, read OTP LSC from sensor OK.", __func__);
	}

	/* LSC param is read  */
	sonyimx135_otp_flag |= SONYIMX135_OTP_LSC_READ;

	return true;
}
/****************************************************************************
* FunctionName: sonyimx135_otp_set_lsc;
* Description : Set lens shading parameters to sensor registers.;
* Input       : NA;
* Output      : NA;
* ReturnValue : bool;
* Other       : NA;
***************************************************************************/
static bool sonyimx135_otp_set_lsc(void)
{
	u8 *pval = NULL;
	int i = 0;

	print_debug("enter %s", __func__);

	/* Lens shading parameters are burned OK. */
	if (0xFF == sonyimx135_otp_lsc_id) {
		/* Get parameters from static array, which read from OTP. */
		pval = sonyimx135_otp_lsc_param;
	} else {
		print_error("%s: Unsupported lens shading ID, %#x", __func__, sonyimx135_otp_lsc_id);
		return false;
	}

	/* Write lens shading parameters to sensor registers. */
	for (i=0; i<SONYIMX135_OTP_LSC_SIZE; i++) {
		sonyimx135_write_reg(SONYIMX135_SENSOR_LSC_RAM+i, *(pval+i), 0x00);
	}
    print_info("%s, set OTP LSC to sensor OK.", __func__);

	return true;
}
/****************************************************************************
* FunctionName: sonyimx135_otp_enable_lsc;
* Description : Enable LSC correct.;
* Input       : bool;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static void sonyimx135_otp_enable_lsc(bool enable)
{
	u8 lscMode = 0x00;
	u8 selToggle = 0x00;
	u8 lscEnable = 0x00;

	print_debug("enter %s", __func__);

	/* Open OTP lsc mode */
	if (enable) {
		lscMode = 0x01;
		selToggle = 0x01;
		lscEnable = 0x1F;
		print_info("%s, OTP LSC enabled!", __func__);
	}

	sonyimx135_write_reg(SONYIMX135_SENSOR_LSC_MODE, lscMode, 0x00);
	sonyimx135_write_reg(SONYIMX135_SENSOR_RAM_SEL, selToggle, 0x00);
	sonyimx135_write_reg(SONYIMX135_SENSOR_LSC_EN, lscEnable, 0x00);
}
/****************************************************************************
* FunctionName: sonyimx135_otp_read_vcm;
* Description : Get AF motor parameters from OTP.;
* Input       : NA;
* Output      : NA;
* ReturnValue : bool;
* Other       : NA;
***************************************************************************/
static bool sonyimx135_otp_read_vcm(void)
{
	print_debug("enter %s", __func__);

	if (!sonyimx135_otp_check_page(OTP_VCM)) {
		print_error("%s: Check OTP AF VCM page failed.", __func__);
		return false;
	}

	sonyimx135_read_reg(0x3B04, &sonyimx135_otp_vcm.start_curr_h);
	sonyimx135_read_reg(0x3B05, &sonyimx135_otp_vcm.start_curr_l);
	sonyimx135_read_reg(0x3B06, &sonyimx135_otp_vcm.infinity_curr_h);
	sonyimx135_read_reg(0x3B07, &sonyimx135_otp_vcm.infinity_curr_l);
	sonyimx135_read_reg(0x3B08, &sonyimx135_otp_vcm.macro_curr_h);
	sonyimx135_read_reg(0x3B09, &sonyimx135_otp_vcm.macro_curr_l);
	sonyimx135_read_reg(0x3B0A, &sonyimx135_otp_vcm.meter_curr_h);
	sonyimx135_read_reg(0x3B0B, &sonyimx135_otp_vcm.meter_curr_l);

	/* VCM param is read  */
	sonyimx135_otp_flag |= SONYIMX135_OTP_VCM_READ;

	return true;
}
/****************************************************************************
* FunctionName: sonyimx135_otp_set_vcm;
* Description : Set AF motor parameters to ISP.;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static void sonyimx135_otp_set_vcm(void)
{
	u16 start_curr = 0;
	u16 infinity_curr = 0;
	u16 macro_curr = 0;
	u8 otp_h = 0;
	u8 otp_l = 0;

	print_debug("enter %s", __func__);

	otp_h = sonyimx135_otp_vcm.start_curr_h;
	otp_l = sonyimx135_otp_vcm.start_curr_l;
	start_curr = (otp_h << 8) | otp_l;

	otp_h = sonyimx135_otp_vcm.infinity_curr_h;
	otp_l = sonyimx135_otp_vcm.infinity_curr_l;
	infinity_curr = (otp_h << 8) | otp_l;

	otp_h = sonyimx135_otp_vcm.macro_curr_h;
	otp_l = sonyimx135_otp_vcm.macro_curr_l;
	macro_curr = (otp_h << 8) | otp_l;

	sonyimx135_vcm_start = start_curr;
	sonyimx135_vcm_end = sonyimx135_sensor.vcm->normalDistanceEnd;

	print_debug("%s, start = %#x, infinity = %#x, macro = %#x",
		__func__, start_curr, infinity_curr, macro_curr);
}
/****************************************************************************
* FunctionName: sonyimx135_otp_get_vcm;
* Description : Get vcm start and stop parameters read from OTP.;
* Input       : NA;
* Output      : vcm_start vcm_end
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static void sonyimx135_otp_get_vcm(u16 *vcm_start, u16 *vcm_end)
{
	if (0 == sonyimx135_vcm_start) {
		*vcm_start = sonyimx135_sensor.vcm->infiniteDistance;
	} else {
		 if (sonyimx135_vcm_start > SONYIMX135_STARTCODE_OFFSET )
			*vcm_start = sonyimx135_vcm_start - SONYIMX135_STARTCODE_OFFSET;
		else
			*vcm_start = 0;
	}

	if (0 == sonyimx135_vcm_end) {
		*vcm_end = sonyimx135_sensor.vcm->normalDistanceEnd;
	} else {
		*vcm_end = sonyimx135_vcm_end;
	}

	print_info("%s, start: %#x, end: %#x", __func__, sonyimx135_vcm_start, sonyimx135_vcm_end);
}
/****************************************************************************
* FunctionName: sonyimx135_otp_update_afwb;
* Description : Update parameters form OTP when initializing.;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static void sonyimx135_otp_update_afwb(void)
{
	print_debug("enter %s", __func__);

	if ((sonyimx135_otp_flag & SONYIMX135_OTP_ID_WB_READ)
		|| sonyimx135_otp_read_id_wb()) {
		sonyimx135_otp_set_id();
		sonyimx135_otp_set_wb();
	} else {
		print_error("%s: Read OTP Module info and WB parameters failed.", __func__);
	}

	if ((sonyimx135_otp_flag & SONYIMX135_OTP_VCM_READ) || sonyimx135_otp_read_vcm()) {
		sonyimx135_otp_set_vcm();
	} else {
		print_error("%s: Read OTP AF VCM parameters failed.", __func__);
	}
}
/****************************************************************************
* FunctionName: sonyimx135_otp_record_lsc_func;
* Description : Recored OTP LSC parameter function, schedule by workqueue.;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static void sonyimx135_otp_record_lsc_func(struct work_struct *work)
{
	print_debug("enter %s", __func__);

	if ((sonyimx135_otp_flag & SONYIMX135_OTP_LSC_FILE_ERR) || (!sonyimx135_otp_lsc_file_exist())) {
		sonyimx135_otp_write_file();
		print_info("%s, OTP flag is: %#x", __func__, sonyimx135_otp_flag);
	}
}
/*
 **************************************************************************
 * FunctionName: sonyimx135_reset;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_reset(camera_power_state power_state)
{
	print_debug("%s  ", __func__);

	if (POWER_ON == power_state) {
		k3_isp_io_enable_mclk(MCLK_ENABLE, sonyimx135_sensor.sensor_index);
		k3_ispgpio_reset_sensor(sonyimx135_sensor.sensor_index, power_state,
			      sonyimx135_sensor.power_conf.reset_valid);
		msleep(5);
//		udelay(500);
	} else {
		k3_ispgpio_reset_sensor(sonyimx135_sensor.sensor_index, power_state,
			      sonyimx135_sensor.power_conf.reset_valid);
		udelay(10);
		k3_isp_io_enable_mclk(MCLK_DISABLE, sonyimx135_sensor.sensor_index);
	}

	return 0;
}


/*
 **************************************************************************
 * FunctionName: sonyimx135_init;
 * Description : sonyimx135 init function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : Error code indicating success or failure;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_init(void)
{
	static bool sonyimx135_check = false;
	print_debug("%s  ", __func__);

	if (false == sonyimx135_check) {
		if (video_check_suspensory_camera("sonyimx135_sensor") != 1) {
			print_error("%s: product not have this sensor", __func__);
			return -ENODEV;
		}
		sonyimx135_check = true;
	}

#if 0
	if (!camera_timing_is_match(0)) {
		print_error("%s: sensor timing don't match.\n", __func__);
		return -ENODEV;
	}
#endif
	if(CAMERA_SENSOR_FLIP_TYPE_H_V == video_get_primary_sensor_flip_type())
		sonyimx135_sensor.sensor_rgb_type = SENSOR_BGGR;
	else
		sonyimx135_sensor.sensor_rgb_type =SENSOR_RGGB;

	if (sonyimx135_sensor.owner && !try_module_get(sonyimx135_sensor.owner)) {
		print_error("%s: try_module_get fail", __func__);
		return -ENOENT;
	}
sonyimx135_sensor.old_flip = 0;
	k3_ispio_power_init(M_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - pri camera*/
	k3_ispio_power_init(M_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);		/*IO 1.8V - pri camera*/
	k3_ispio_power_init(M_CAMERA_VCM_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*AF 2.85V - pri camera*/
	k3_ispio_power_init(M_CAMERA_CORE_VDD, LDO_VOLTAGE_10V, LDO_VOLTAGE_10V);	/*core 1.05V - pri camera*/

	INIT_WORK(&record_otp_lsc_work, sonyimx135_otp_record_lsc_func);
	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_exit;
 * Description : sonyimx135 exit function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx135_exit(void)
{
	print_debug("enter %s", __func__);

	k3_ispio_power_deinit();

	if (sonyimx135_sensor.owner)
		module_put(sonyimx135_sensor.owner);

	print_debug("exit %s", __func__);
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_shut_down;
 * Description : sonyimx135 shut down function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx135_shut_down(void)
{
	print_debug("enter %s", __func__);
	k3_ispgpio_power_sensor(&sonyimx135_sensor, POWER_OFF);
}
#if 0
/*
 **************************************************************************
 * FunctionName: sonyimx135_support_hdr_movie;
 * Description : check sensor support hdr movie or not;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_support_hdr_movie(void)
{
	   return HDR_MOVIE_SUPPORT;
}
#endif
/*
 **************************************************************************
 * FunctionName: sonyimx135_support_awb_otp;
 * Description : check sensor support awb otp or not;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx135_support_awb_otp(void)
{
	return AWB_OTP_SUPPORT;
}
#if 0
/*
 **************************************************************************
 * FunctionName: sonyimx135_get_hdr_movie_switch;
 * Description : the function that get hdr movie status on or off;
 * Input       : NA;
 * Output      : the status of hdr movie status;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/

static int sonyimx135_get_hdr_movie_switch(void)
{
	   return sonyimx135_sensor.sensor_hdr_movie.hdrInfo.hdr_on;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_get_hdr_movie_ae_param;
 * Description : The ae arith in HAL get init parm from sensor by this interface.
 * Input       : the space of hdr_ae_constant_param for keeping ratio,max gain,min gain and vts;
 * Output      : the value of ratio,max gain,min gain and vts;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
int  sonyimx135_get_hdr_movie_ae_param(hdr_ae_constant_param * hdr_ae_param)
{
	if(NULL != hdr_ae_param)
	{
		hdr_ae_param->hdr_ae_ratio = sonyimx135_sensor.sensor_hdr_movie.ae_hdr_ratio;
		hdr_ae_param->sensor_max_gain = sonyimx135_sensor.sensor_hdr_movie.sensor_max_gain;
		hdr_ae_param->sensor_min_gain = sonyimx135_sensor.sensor_hdr_movie.sensor_min_gain;
		hdr_ae_param->max_analog_gain= sonyimx135_sensor.sensor_hdr_movie.sensor_max_analog_gain;
	}
	return 0;
}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_get_gain;
 * Description :get gain from sensor
 * Input       	 NA;
 * Output      	 gain value from sensor
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static u32 sonyimx135_get_gain(void)
{
	u8 gain_l = 0;

	//u8 short_gain = 0;
	u32 gain = 0;
	sonyimx135_read_reg(SONYIMX135_ANA_GAIN_REG_L, &gain_l);

	//sonyimx135_read_reg(SONYIMX135_WD_ANA_GAIN_DS  , &short_gain);
	//gain = (gain_h << 8) | gain_l;
	gain = gain_l;

	if(_IS_DEBUG_AE)
	{
		print_info("enter %s, 0x0205=%x",__func__,gain_l);
		//print_info("enter %s, 0x0233=%x",__func__,short_gain);
	}
	return gain;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_get_exposure;
 * Description :get exposure from sensor
 * Input       	 NA;
 * Output      	 exposure value from sensor
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static u32  sonyimx135_get_exposure(void)
{
	u32 expo = 0;
	u8 expo_h = 0;
	u8 expo_l = 0;
	//u8 expo_short_h = 0;
	//u8 expo_shot_l = 0;
	sonyimx135_read_reg(SONYIMX135_EXPOSURE_REG_H, &expo_h);
	sonyimx135_read_reg(SONYIMX135_EXPOSURE_REG_L, &expo_l);

	//sonyimx135_read_reg(SONYIMX135_WD_COARSE_INTEG_TIME_DS_H, &expo_short_h);
	//sonyimx135_read_reg(SONYIMX135_WD_COARSE_INTEG_TIME_DS_L, &expo_shot_l);

	if(_IS_DEBUG_AE)
	{
		print_info("enter %s,0x0202=%x,0x0203=%x",__func__,expo_h,expo_l);
		//print_info("enter %s,0x0230=%x,0x0231=%x",__func__,expo_short_h,expo_shot_l);
	}
	expo = expo_h &0xff;
	expo = expo << 8 | expo_l;
	return expo;
}

#if 0
/*
 **************************************************************************
 * FunctionName: sonyimx135_set_hdr_movie_switch;
 * Description : the function that set hdr movie status;
 * Input       : the status of hdr movie on or off;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx135_set_hdr_movie_switch(hdr_movie_switch on)
{
	print_info("enter %s,on = %d",__func__,on);
	sonyimx135_sensor.sensor_hdr_movie.hdrInfo.hdr_on = on;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_set_ATR_swtich;
 * Description : turn on or off atr curve;
 * Input       : 1 turn on atr ,0 turn off atr;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
void sonyimx135_set_ATR_switch(int on)
{
       if(on == 0)
       {//ATR off
		sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
		sonyimx135_write_reg(SONYIMX135_ATR_OFF_SETTING_1,0x00, 0x00);
		sonyimx135_write_reg(SONYIMX135_ATR_OFF_SETTING_2,0x00, 0x00);
		sonyimx135_write_reg(SONYIMX135_TRIGGER_SETTING ,0x01, 0x00);
		sonyimx135_write_reg(0x4344,0x01, 0x00);//ARNR
		sonyimx135_write_reg(0x4364,0x0B, 0x00);
		sonyimx135_write_reg(0x436C,0x00, 0x00);
		sonyimx135_write_reg(0x436D,0x00, 0x00);
		sonyimx135_write_reg(0x436E,0x00, 0x00);
		sonyimx135_write_reg(0x436F,0x00, 0x00);
		sonyimx135_write_reg(0x4369,0x00, 0x00);
		sonyimx135_write_reg(0x437B,0x00, 0x00);
		sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
	}
	else
	{//ATR on
		sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
		sonyimx135_write_reg(0x437B,0x01, 0x00);
		sonyimx135_write_reg(0x4369,0x0f, 0x00);
		sonyimx135_write_reg(0x436F,0x06, 0x00);
		sonyimx135_write_reg(0x436E,0x00, 0x00);
		sonyimx135_write_reg(0x436D,0x00, 0x00);
		sonyimx135_write_reg(0x436C,0x00, 0x00);
		sonyimx135_write_reg(0x4364,0x0B, 0x00);

		sonyimx135_write_reg(0x4344,0x01, 0x00);//ARNR

		sonyimx135_write_reg(SONYIMX135_TRIGGER_SETTING,0x00, 0x00);
		sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
	}
	sonyimx135_sensor.sensor_hdr_movie.hdrInfo.atr_on  = on;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_over_exposure_adjust;
 * Description :
 * Input       	:
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
void sonyimx135_over_exposure_adjust(int on,stats_hdr_frm * frm_stats)
{
	print_debug("enter %s  on = %d",__func__,on);
	if(on == 1)
	{
		sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
		sonyimx135_write_reg(0x4470,frm_stats->frm_ave_h&0xff,0x00);//frm_ave
		sonyimx135_write_reg(0x4471,frm_stats->frm_ave_l&0xff,0x00);//frm_ave2
		sonyimx135_write_reg(0x4472,frm_stats->frm_min_h&0xff,0x00);//frm_min1
		sonyimx135_write_reg(0x4473,frm_stats->frm_min_l&0xff,0x00);//frm_min2
		sonyimx135_write_reg(0x4474,frm_stats->frm_max_h&0xff,0x00);//frm_max1
		sonyimx135_write_reg(0x4475,frm_stats->frm_max_l&0xff,0x00);//frm_max2
		sonyimx135_write_reg(0x4476,0x01,0x00);
		sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
		if(_IS_DEBUG_AE)
		{
			print_info("frm_ave_h = %d,frm_ave_l =%d,frm_min_h=%d,frm_min_l=%d,frm_max_h=%d,frm_max_l=%d,",
			frm_stats->frm_ave_h,frm_stats->frm_ave_l,frm_stats->frm_min_h,frm_stats->frm_min_l,
			frm_stats->frm_max_h,frm_stats->frm_max_l);
		}
	}
	else
	{
		sonyimx135_write_reg(0x4476,0x00,0x00);
	}
	sonyimx135_sensor.sensor_hdr_movie.hdrInfo.atr_over_expo_on = on;
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_set_hdr_exposure_gain;
 * Description 	   : set exposure and gain to sensor.
 * Input		   : the value of exposure and gain ,that include long exposure short exposure and long gain db ,short gain db
 		          :  gain is db but not times
 * Output      	   : NA
 * ReturnValue   : NA;
 * Other       	   : NA;
 **************************************************************************
*/
void sonyimx135_set_hdr_exposure_gain(u32 expo_long,u16 gain_global,u32 expo_short,u16 short_gain)
{
	u16 gain_switch_long = 0;
	u16 gain_switch_short = 0;

	gain_switch_long = gain_global;
	gain_switch_short = short_gain;
	if(_IS_DEBUG_AE)
	{
	       print_info("enter %s, gain_switch_long = %d,expo_long = %d,gain_switch_short = %d,expo_short = %d ", __func__,gain_switch_long,expo_long,gain_switch_short,expo_short);
	}

	sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
	sonyimx135_write_reg(SONYIMX135_EXPOSURE_REG_H, (expo_long >> 8) & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_EXPOSURE_REG_L, expo_long & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_WD_COARSE_INTEG_TIME_DS_H, (expo_short >> 8) & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_WD_COARSE_INTEG_TIME_DS_L, expo_short & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_ANA_GAIN_REG_L, gain_switch_long, 0x00);
	sonyimx135_write_reg(SONYIMX135_WD_ANA_GAIN_DS, gain_switch_short, 0x00);
	sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release

}


/*
 **************************************************************************
 * FunctionName: sonyimx135_set_lmt_sat;
 * Description :
 * Input       :
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
void sonyimx135_set_lmt_sat(u32 lmt_value, u32 sat_value)
{
	if(_IS_DEBUG_AE)
	{
		print_info("enter %s,lmt_value = %x,sat_value = %x", __func__,lmt_value,sat_value);
	}

	sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
	sonyimx135_write_reg(SONYIMX135_WB_LMT_REG_H, (lmt_value >> 8) & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_WB_LMT_REG_L, lmt_value & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_AE_SAT_REG_H, (sat_value >> 8) & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_AE_SAT_REG_L, sat_value & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
}


/****************************************************************************
* FunctionName: sonyimx135_set_awb_gain;
* Description : NA;
* Input       : R,GR,GB,B gain from isp;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
void sonyimx135_set_awb_gain(u16 b_gain, u16 gb_gain, u16 gr_gain, u16 r_gain)
{
	if(_IS_DEBUG_AE)
	{
		print_info("enter%s, b_gain = %d ,gb_gain=%d,gr_gain = %d ,r_gain=%d", __func__,b_gain,gb_gain,gr_gain,r_gain);
	}

	sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
	sonyimx135_write_reg(SONYIMX135_ABS_GAIN_B_REG_H, (b_gain >> 8) & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_ABS_GAIN_B_REG_L, b_gain & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_ABS_GAIN_GB_REG_H, (gb_gain >> 8) & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_ABS_GAIN_GB_REG_L, gb_gain & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_ABS_GAIN_GR_REG_H, (gr_gain >> 8) & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_ABS_GAIN_GR_REG_L, gr_gain & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_ABS_GAIN_R_REG_H, (r_gain >> 8) & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_ABS_GAIN_R_REG_L, r_gain & 0xff, 0x00);
	sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_set_digital_gain;
 * Description : set digital gain to sensor's digital registers
 * Input       : the struct of digital_gain_st saving digital value
 * Output      : NA
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
void sonyimx135_set_digital_gain(digital_gain_st * digital_gain)
{
	u8 digital_gain_h = digital_gain->digital_gain_h;
	u8 digital_gain_l = digital_gain->digital_gain_l;
	if(_IS_DEBUG_AE)
	{
	       print_info("enter%s, digital_gain_h = %d ,digital_gain_l=%d", __func__,digital_gain_h,digital_gain_l);
	}
	sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_GR_REG_H , digital_gain_h, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_GR_REG_L, digital_gain_l, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_R_REG_H , digital_gain_h, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_R_REG_L , digital_gain_l, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_B_REG_H,digital_gain_h, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_B_REG_L, digital_gain_l, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_GB_REG_H, digital_gain_h, 0x00);
	sonyimx135_write_reg(SONYIMX135_DIG_GAIN_GB_REG_L,digital_gain_l, 0x00);
	sonyimx135_write_reg(SONYIMX135_GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
}
#endif


/*
 **************************************************************************
 * FunctionName: ov13850_config_dphy_clk;
 * Description : set MIPI clock to dphy;
 * Input       : camera state
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx135_config_dphy_clk(camera_state state)
{
	u8 lane_clk;
	
	if (state == STATE_PREVIEW) {
		lane_clk =sonyimx135_sensor.frmsize_list[sonyimx135_sensor.preview_frmsize_index].lane_clk;
	} else {
		lane_clk =sonyimx135_sensor.frmsize_list[sonyimx135_sensor.capture_frmsize_index].lane_clk;
	}

	print_info("%s lane_clk = 0x%x state = %d",__func__, lane_clk, state);
	k3_ispio_config_lane_clk(sonyimx135_sensor.mipi_index, sonyimx135_sensor.mipi_lane_count, lane_clk);
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_set_default;
 * Description : init sonyimx135_sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx135_set_default(void)
{

	sonyimx135_sensor.init = sonyimx135_init;
	sonyimx135_sensor.exit = sonyimx135_exit;
	sonyimx135_sensor.shut_down = sonyimx135_shut_down;
	sonyimx135_sensor.reset = sonyimx135_reset;
	sonyimx135_sensor.check_sensor = sonyimx135_check_sensor_new;
	sonyimx135_sensor.power = sonyimx135_power;
	sonyimx135_sensor.init_reg = sonyimx135_init_reg;
	sonyimx135_sensor.init_isp_reg = sonyimx135_init_isp_reg;
	sonyimx135_sensor.stream_on = sonyimx135_stream_on;

	sonyimx135_sensor.get_format = sonyimx135_get_format;
	sonyimx135_sensor.set_flash = NULL;
	sonyimx135_sensor.get_flash = NULL;
	sonyimx135_sensor.set_scene = NULL;
	sonyimx135_sensor.get_scene = NULL;

	sonyimx135_sensor.enum_framesizes = sonyimx135_enum_framesizes;
	sonyimx135_sensor.try_framesizes = sonyimx135_try_framesizes;
	sonyimx135_sensor.set_framesizes = sonyimx135_set_framesizes;
	sonyimx135_sensor.get_framesizes = sonyimx135_get_framesizes;

	sonyimx135_sensor.enum_frame_intervals = sonyimx135_enum_frame_intervals;
	sonyimx135_sensor.try_frame_intervals = NULL;
	sonyimx135_sensor.set_frame_intervals = NULL;
	sonyimx135_sensor.get_frame_intervals = NULL;

	sonyimx135_sensor.get_capability = sonyimx135_get_capability;

	sonyimx135_sensor.set_hflip = sonyimx135_set_hflip;
	sonyimx135_sensor.get_hflip = sonyimx135_get_hflip;
	sonyimx135_sensor.set_vflip = sonyimx135_set_vflip;
	sonyimx135_sensor.get_vflip = sonyimx135_get_vflip;
	sonyimx135_sensor.update_flip = sonyimx135_update_flip;

	sonyimx135_sensor.sensor_hw_3a.support_awb_otp = sonyimx135_support_awb_otp;

	strncpy(sonyimx135_sensor.info.name, "sonyimx135_liteon",sizeof(sonyimx135_sensor.info.name));
	sonyimx135_sensor.interface_type = MIPI1;
	sonyimx135_sensor.mipi_lane_count = CSI_LINES_4;
	sonyimx135_sensor.mipi_index = CSI_INDEX_0;
	sonyimx135_sensor.sensor_index = CAMERA_SENSOR_PRIMARY;
	sonyimx135_sensor.skip_frames = 2;
	sonyimx135_sensor.power_conf.pd_valid = LOW_VALID;
	sonyimx135_sensor.power_conf.reset_valid = LOW_VALID;
	sonyimx135_sensor.power_conf.vcmpd_valid = LOW_VALID;

	sonyimx135_sensor.i2c_config.index = I2C_PRIMARY;
	sonyimx135_sensor.i2c_config.speed = I2C_SPEED_400;
	//sonyimx135_sensor.i2c_config.addr = SONYIMX135_SLAVE_ADDRESS;
	sonyimx135_sensor.i2c_config.addr_bits = I2C_16BIT;
	sonyimx135_sensor.i2c_config.val_bits = I2C_8BIT;

	sonyimx135_sensor.preview_frmsize_index = 0;
	sonyimx135_sensor.capture_frmsize_index = 0;
	//sonyimx135_sensor.frmsize_list = sonyimx135_framesizes;
	sonyimx135_sensor.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW10;
	sonyimx135_sensor.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW10;

#ifdef SONYIMX135_AP_WRITEAE_MODE		/* just an example and test case for AP write AE mode */
	sonyimx135_sensor.aec_addr[0] = 0;
	sonyimx135_sensor.aec_addr[1] = 0;
	sonyimx135_sensor.aec_addr[2] = 0;
	sonyimx135_sensor.agc_addr[0] = 0;
	sonyimx135_sensor.agc_addr[1] = 0;
	sonyimx135_sensor.ap_writeAE_delay = 6000; /* 5 expo and gain registers, 6000 us is enough */
#else
	sonyimx135_sensor.aec_addr[0] = 0x0000;
	sonyimx135_sensor.aec_addr[1] = 0x0202;
	sonyimx135_sensor.aec_addr[2] = 0x0203;
	sonyimx135_sensor.agc_addr[0] = 0x0000; /*0x0204 high byte not needed*/
	sonyimx135_sensor.agc_addr[1] = 0x0205;
#endif
	sonyimx135_sensor.sensor_type = SENSOR_SONY;

	sonyimx135_sensor.set_exposure_gain= sonyimx135_set_exposure_gain;
	sonyimx135_sensor.set_gain = sonyimx135_set_gain;
	sonyimx135_sensor.set_exposure = sonyimx135_set_exposure;

	sonyimx135_sensor.set_vts = sonyimx135_set_vts;
	sonyimx135_sensor.get_vts_reg_addr = sonyimx135_get_vts_reg_addr;

	sonyimx135_sensor.sensor_gain_to_iso = sonyimx135_gain_to_iso;
	sonyimx135_sensor.sensor_iso_to_gain = sonyimx135_iso_to_gain;

	sonyimx135_sensor.set_effect = NULL;

	sonyimx135_sensor.isp_location = CAMERA_USE_K3ISP;
	sonyimx135_sensor.sensor_tune_ops = NULL;

	sonyimx135_sensor.af_enable = 1;
	sonyimx135_sensor.vcm = &vcm_dw9714_param;

	sonyimx135_sensor.image_setting.lensc_param = sonyimx135_lensc_param;
	sonyimx135_sensor.image_setting.ccm_param = sonyimx135_ccm_param;
	sonyimx135_sensor.image_setting.awb_param = sonyimx135_awb_param;

	sonyimx135_sensor.fps_max = 30;
	sonyimx135_sensor.fps_min = 10;
	sonyimx135_sensor.fps = 25;

	sonyimx135_sensor.owner = THIS_MODULE;

	sonyimx135_sensor.info.facing = CAMERA_FACING_BACK;
	sonyimx135_sensor.info.orientation = 90;   /*270;*/
	sonyimx135_sensor.info.focal_length = 385; /* 3.85mm*/
	sonyimx135_sensor.info.h_view_angle = 66; /*  66.1 degree */
	sonyimx135_sensor.info.v_view_angle = 50;
	sonyimx135_sensor.lane_clk = CLK_750M;
	sonyimx135_sensor.hflip = 0;
	sonyimx135_sensor.vflip = 0;
	sonyimx135_sensor.old_flip = 0;
	sonyimx135_sensor.support_summary = false;

#if 0
	// for HDR movie funtion
	sonyimx135_sensor.sensor_hdr_movie.support_hdr_movie = sonyimx135_support_hdr_movie;
	sonyimx135_sensor.sensor_hdr_movie.get_hdr_movie_switch= sonyimx135_get_hdr_movie_switch;
	sonyimx135_sensor.sensor_hdr_movie.get_hdr_movie_ae_param = sonyimx135_get_hdr_movie_ae_param;
#endif
	sonyimx135_sensor.get_gain = sonyimx135_get_gain;
	sonyimx135_sensor.get_exposure = sonyimx135_get_exposure;
#if 0
	sonyimx135_sensor.sensor_hdr_movie.set_hdr_movie_switch= sonyimx135_set_hdr_movie_switch;
	sonyimx135_sensor.sensor_hdr_movie.set_ATR_switch = sonyimx135_set_ATR_switch;
	sonyimx135_sensor.sensor_hdr_movie.over_exposure_adjust = sonyimx135_over_exposure_adjust;
	sonyimx135_sensor.sensor_hdr_movie.set_hdr_exposure_gain = sonyimx135_set_hdr_exposure_gain;
	sonyimx135_sensor.sensor_hdr_movie.set_digital_gain = sonyimx135_set_digital_gain;
	sonyimx135_sensor.sensor_hdr_movie.set_lmt_sat = sonyimx135_set_lmt_sat;
	sonyimx135_sensor.sensor_hdr_movie.set_awb_gain = sonyimx135_set_awb_gain;

	//check default parameter
	sonyimx135_sensor.sensor_hdr_movie.stats_data.stats_h =1024;
	sonyimx135_sensor.sensor_hdr_movie.stats_data.stats_v =2;
	sonyimx135_sensor.sensor_hdr_movie.ae_hdr_ratio = 8;
	sonyimx135_sensor.sensor_hdr_movie.hdrInfo.atr_on = ATR_ON;
	sonyimx135_sensor.sensor_hdr_movie.sensor_max_gain =32;
	sonyimx135_sensor.sensor_hdr_movie.sensor_max_analog_gain = 8;
	sonyimx135_sensor.sensor_hdr_movie.sensor_min_gain =1;
	sonyimx135_sensor.sensor_hdr_movie.hdrInfo.hdr_on= HDR_MOVIE_OFF;//default atr on
#endif
	sonyimx135_sensor.isp_idi_skip = false;

	sonyimx135_sensor.stream_off_setting = sonyimx135_stream_off_regs;
	sonyimx135_sensor.stream_off_setting_size = ARRAY_SIZE(sonyimx135_stream_off_regs);

	/*if there have different data rate of sensor resolution we need this config_dphy_clk 
	   otherwise if all resolution is same rate config_dphy_clk must to be null*/
	sonyimx135_sensor.config_dphy_clk = sonyimx135_config_dphy_clk;

}

/*
 **************************************************************************
 * FunctionName: sonyimx135_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int sonyimx135_module_init(void)
{
	sonyimx135_set_default();
	return register_camera_sensor(sonyimx135_sensor.sensor_index, &sonyimx135_sensor);
}

/*
 **************************************************************************
 * FunctionName: sonyimx135_module_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void __exit sonyimx135_module_exit(void)
{
	unregister_camera_sensor(sonyimx135_sensor.sensor_index, &sonyimx135_sensor);
}

MODULE_AUTHOR("Hisilicon");
module_init(sonyimx135_module_init);
module_exit(sonyimx135_module_exit);
MODULE_LICENSE("GPL");

/********************************** END **********************************************/
