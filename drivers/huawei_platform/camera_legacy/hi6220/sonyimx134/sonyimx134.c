

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
//#include <mach/hisi_mem.h>
//#include "mach/hardware.h"
#include <linux/hisi/hi6xxx-boardid.h>
//#include <mach/gpio.h>
#include "../isp/sensor_common.h"
#include "sonyimx134.h"
/*#include "../isp/k3_isp_io.h"*/
#include <asm/bug.h>
#include <linux/device.h>

#define LOG_TAG "SONYIMX134"
//#define DEBUG_DEBUG 1
#include "../isp/cam_log.h"
#include <../isp/cam_util.h>
#include "imx134_tune.h"
//#include "../isp/k3_ispv1_hdr_movie_ae.h"
#include "../isp/k3_isp.h"
#include "../isp/k3_ispv1.h"
#include "../isp/k3_ispv1_afae.h"
#include "../isp/cam_dbg.h"
#include "video_config.h"

#define _IS_DEBUG_AE 0



#define DIG_GAIN_GR_H                        0x020E
#define DIG_GAIN_GR_L                        0x020F
#define DIG_GAIN_R_H                         0x0210
#define DIG_GAIN_R_L                         0x0211
#define DIG_GAIN_B_H                         0x0212
#define DIG_GAIN_B_L                         0x0213
#define DIG_GAIN_GB_H                        0x0214
#define DIG_GAIN_GB_L                        0x0215

#define HDR_MODE_ADRESS                 								(0x0238)
#define WD_INTEG_RATIO                        							(0x0239)
#define SONYIMX134_DIGITAL_GAIN_REG_GREEN_R_H 				(0x020E)
#define SONYIMX134_DIGITAL_GAIN_REG_GREEN_R_L 				(0x020F)
#define SONYIMX134_DIGITAL_GAIN_REG_GREEN_B_H 				(0x0214)
#define SONYIMX134_DIGITAL_GAIN_REG_GREEN_B_L 				(0x0215)
#define SONYIMX134_DIGITAL_GAIN_REG_RED_H         			(0x0210)
#define SONYIMX134_DIGITAL_GAIN_REG_RED_L     				(0x0211)
#define SONYIMX134_DIGITAL_GAIN_REG_BLUE_H    				(0x0212)
#define SONYIMX134_DIGITAL_GAIN_REG_BLUE_L    				(0x0213)

#define WD_COARSE_INTEG_TIME_DS_H     						(0x0230)
#define WD_COARSE_INTEG_TIME_DS_L     						(0x0231)
#define COARSE_INTEG_TIME_WHT_DIRECT_H    					(0x0240)
#define COARSE_INTEG_TIME_WHT_DIRECT_L    					(0x0241)
#define COARSE_INTEG_TIME_WHT_DS_DIRECT_H 					(0x023E)
#define COARSE_INTEG_TIME_WHT_DS_DIRECT_L 					(0x023F)
#define WD_ANA_GAIN_DS                    			    	(0x0233)

#define ATR_OFF_SETTING_1             						(0x446D)
#define ATR_OFF_SETTING_2             						(0x446E)
#define TRIGGER_SETTING                  					(0x446C)

#define  WB_LMT_REG_H                             			(0x441E)
#define  WB_LMT_REG_L                             			(0x441F)

#define  AE_SAT_REG_H                              			(0x4446)
#define  AE_SAT_REG_L                              			(0x4447)

#define SONYIMX134_ABS_GAIN_B_H								(0x0716)
#define SONYIMX134_ABS_GAIN_B_L								(0x0717)
#define SONYIMX134_ABS_GAIN_GB_H							(0x0718)
#define SONYIMX134_ABS_GAIN_GB_L							(0x0719)
#define SONYIMX134_ABS_GAIN_GR_H							(0x0712)
#define SONYIMX134_ABS_GAIN_GR_L							(0x0713)
#define SONYIMX134_ABS_GAIN_R_H								(0x0714)
#define SONYIMX134_ABS_GAIN_R_L								(0x0715)

#define ATR_OUT_NOISE_REG_H        							(0x4452)
#define ATR_OUT_NOISE_REG_L        							(0x4453)
#define ATR_OUT_MID_REG_H        							(0x4454)
#define ATR_OUT_MID_REG_L        							(0x4455)
#define ATR_OUT_SAT_REG_H        							(0x4456)
#define ATR_OUT_SAT_REG_L        							(0x4457)
#define ATR_NOISE_BRATE_REG     							(0x4458)
#define ATR_MID_BRATE_REG        							(0x4459)
#define ATR_SAT_BRATE_REG        							(0x445a)

#define CURVE_CHANGE_REG                  					(0x441C)

#define GROUP_HOLD_FUNCTION_REG   							(0x0104)
//#define SONYIMX135_AP_WRITEAE_MODE
#define  SONYIMX134_MAX_ISO 			1550
#define SONYIMX134_MIN_ISO                      100

/* support 3 level framerate now, if mid fps same as min, set to 2 level framerate */
#define SONYIMX134_AUTOFPS_GAIN_HIGH2MID		0x60
#define SONYIMX134_AUTOFPS_GAIN_MID2LOW		    0x60
#define SONYIMX134_AUTOFPS_GAIN_LOW2MID		    0x24
#define SONYIMX134_AUTOFPS_GAIN_MID2HIGH		0x24

#define SONYIMX134_MAX_FRAMERATE         30
#define SONYIMX134_MID_FRAMERATE		 14
#define SONYIMX134_MIN_FRAMERATE          14
#define SONYIMX134_MIN_CAP_FRAMERATE  4
#define SONYIMX134_FLASH_TRIGGER_GAIN 0xff



#define SONYIMX134_SHARPNESS_PREVIEW  0x30
#define SONYIMX134_SHARPNESS_CAPTURE  0x08

#define SONYIMX134_SLAVE_ADDRESS 0x20
#define SONYIMX134_CHIP_ID       (0x0134)

#define SONYIMX134_CAM_MODULE_SKIPFRAME     4

#define SONYIMX134_FLIP		0x0101

#define SONYIMX134_EXPOSURE_REG_H	0x0202
#define SONYIMX134_EXPOSURE_REG_L	0x0203
#define SONYIMX134_GAIN_REG_H		0x0204
#define SONYIMX134_GAIN_REG_L		0x0205

#define SONYIMX134_VTS_REG_H		0x0340
#define SONYIMX134_VTS_REG_L		0x0341

#define SONYIMX134_APERTURE_FACTOR   200 //F2.0
#define SONYIMX134_EQUIVALENT_FOCUS	0

#define SONYIMX134_ISP_ZOOM_LIMIT		0
#define SONYIMX134_DPC_THRESHOLD_ISO			(0x800)

#define SONYIMX134_AP_WRITEAE_MODE
#define SONYIMX134_MAX_ANALOG_GAIN	8

#define SONYIMX134_ISO	(\
				(1 << CAMERA_ISO_AUTO) | \
				(1 << CAMERA_ISO_100) | \
				(1 << CAMERA_ISO_200) | \
				(1 << CAMERA_ISO_400) | \
				(1 << CAMERA_ISO_800) | \
				(1 << CAMERA_ISO_1600) \
			)


enum sensor_module_type
{
	MODULE_LITEON,
	MODULE_SUNNY,
	MODULE_UNSUPPORT
};

static u8 sensor_module;
#ifdef IMX134_OTP
#define OTP_VCM  		0xa6
#define OTP_VCM_REG 	0x40
#define OTP_ID_AWB  	0xa4
#define OTP_ID_REG 		0x00
#define OTP_AWB_REG 	0x05
#define OTP_LSC_1  		0xa4
#define OTP_LSC_2  		0xa6
#define OTP_LSC_1_REG 	0x0b
#define OTP_LSC_2_REG	0x00
#define OTP_CHECKSUM    0xa6
#define OTP_CHECKSUM_REG 0x44
#define OTP_CHECKSUM_FLAG_REG 0x45

#define SONYIMX134_OTP_ID_READ				(1 << 0)
#define SONYIMX134_OTP_VCM_READ				(1 << 1)
#define SONYIMX134_OTP_LSC_READ				(1 << 2)
#define SONYIMX134_OTP_LSC_WRITED			(1 << 3)
#define SONYIMX134_OTP_LSC_FILE_ERR         		(1 << 4)
#define SONYIMX134_OTP_AWB_READ				(1 << 5)
#define SONYIMX134_OTP_CHECKSUM_ERR			(1 << 6)
#define SONYIMX134_OTP_CHECKSUM_READ		(1 << 7)

#define SONYIMX134_SENSOR_LSC_MODE			0x0700
#define SONYIMX134_SENSOR_LSC_EN				0x4500
#define SONYIMX134_SENSOR_RAM_SEL			0x3A63

#define SONYIMX134_SENSOR_LSC_RAM			0x4800
//7*5*4*2
#define SONYIMX134_OTP_LSC_SIZE  280
static u8 sonyimx134_otp_flag = 0;
/* VCM start and end values */
static u16 sonyimx134_vcm_start = 0;
static u16 sonyimx134_vcm_end = 0;

static u8 framesizes_index = 0;
#ifdef ISP_DEBUG_ZSL
extern u8 ap_ae_flg;
extern u8 color_bar_flg;
#endif

static u32 OTPSUMVAL = 0;
static u8   OTPCHECKSUMVAL = 0;
static u8   OTPCHECKSUMFLAG = 0;
#define  OTPCHECKSUM_FLAG    0xA5


static u8 sonyimx134_otp_lsc_param[SONYIMX134_OTP_LSC_SIZE] ;
extern int ispv1_read_sensor_byte_addr8(i2c_index_t index, u8 i2c_addr, u16 reg, u16 *val, i2c_length length);//add by zhoujie
static void sonyimx134_get_otp_from_sensor(void);
static void sonyimx134_otp_get_vcm(u16 *vcm_start, u16 *vcm_end);
static bool sonyimx134_otp_enable_lsc(bool enable);
static bool  sonyimx134_otp_read_vcm(void);
static bool sonyimx134_otp_set_lsc(void);
int sonyimx134_read_otp(u8 i2c_addr,u16 reg,u8 *buf,u16 count);
extern void _sonyimx134_otp_get_vcm(u16 *vcm_start, u16 *vcm_end,vcm_info_s *vcm,u16 otp_vcm_start, u16 otp_vcm_end);
#endif
extern void sonyimx134_get_flash_awb(flash_platform_t type, awb_gain_t *flash_awb);
#if 0
extern int sonyimx134_get_af_param(camera_af_param_t type);
#endif
extern int k3_ispio_read_seq(i2c_index_t index,u8 i2c_addr,struct _sensor_reg_t *seq,u32 size,i2c_length length);

static camera_capability sonyimx134_cap[] = {
	{V4L2_CID_FLASH_MODE, THIS_FLASH},
	{V4L2_CID_FOCUS_MODE, THIS_FOCUS_MODE},
	{V4L2_CID_ISO, SONYIMX134_ISO},
	{V4L2_CID_FOCAL_LENGTH, 296},
};

/*
 * should be calibrated, three lights, from 0x1c264
 * here is long exposure
 */
char sonyimx134_lensc_param[86*3] = {
};

/* should be calibrated, 6 groups 3x3, from 0x1c1d8 */
short sonyimx134_ccm_param[54] = {
};

char sonyimx134_awb_param[] = {
};
static effect_params effect_imx134_sunny = {
#include "effect_imx134_sunny_edge.h"
};
static effect_params effect_imx134_liteon = {
#include "effect_imx134_liteon_edge.h"
};
const struct _sensor_reg_t sonyimx134_stream_off_regs[] = {
	{0x0100, 0x00}
};
const struct _sensor_reg_t sonyimx134_stream_on_regs[] = {
	{0x0100, 0x01}
};
typedef struct{
	char* platform_name;
	framesize_s *frmsize_list;
	u32	list_cnt;
}framesizes_resource;
static framesize_s sonyimx134_sft_framesizes[] = {
//1280x720
	{0, 0, 1280, 720, 3600, 3000, 3, 1, 0x1BC, 0x172, 0x100, VIEW_FULL, RESOLUTION_16_9, false, false, {sonyimx134_framesize_1280x720_sft, ARRAY_SIZE(sonyimx134_framesize_1280x720_sft)} },

//1600x1200
	{0, 0, 1600, 1200, 3600, 3000, 3, 1, 0x1BC, 0x172, 0x100, VIEW_FULL, RESOLUTION_4_3, false, false, {sonyimx134_framesize_1600x1200_sft, ARRAY_SIZE(sonyimx134_framesize_1600x1200_sft)} },

//1920x1088
	{0, 0, 1920, 1088, 3600, 3000, 3, 1, 0x22b, 0x1CE,0x100, VIEW_FULL, RESOLUTION_16_9,false, false, {sonyimx134_framesize_1920x1088_sft, ARRAY_SIZE(sonyimx134_framesize_1920x1088_sft)} },

    {0, 0, 3264, 1840, 3600, 2960, 1, 1, 0x1BC, 0x172, 0x100, VIEW_FULL, RESOLUTION_16_9, false, false, {sonyimx134_framesize_3264x1840_sft, ARRAY_SIZE(sonyimx134_framesize_3264x1840_sft)} },

//3264x2448
	{0, 0, 3264, 2448, 3600, 2960, 1, 1, 0x1BC, 0x172, 0x100, VIEW_FULL, RESOLUTION_4_3, false, false, {sonyimx134_framesize_full_sft, ARRAY_SIZE(sonyimx134_framesize_full_sft)} },
};
static framesize_s sonyimx134_oem_framesizes[] = {
	/* 1600x1200, just close with quarter size */
	{0, 0, 1600, 1200, 3600, 1480, 30, 30, 0x1BC, 0x172, 0x100, VIEW_FULL, RESOLUTION_4_3, false, false, {sonyimx134_framesize_1600x1200_oem, ARRAY_SIZE(sonyimx134_framesize_1600x1200_oem)} },

	/* 1920x1088, 30fps for 1080P video, edge & sony mipi 720 */
	//{0, 0, 1920, 1088, 3600, 1858, 30, 10, 0x22b, 0x1CE,0x100, VIEW_CROP, RESOLUTION_16_9,false, false, {sonyimx134_framesize_1920x1088, ARRAY_SIZE(sonyimx134_framesize_1920x1088)} },
    /* hts will scale with image (reg 0x0340=2592,hts=2592/1.6875=1536),vts will not. */
	{0, 0, 1920, 1088, 3600, 2592, 30, 30, 0x309, 0x288, 0x100, VIEW_FULL, RESOLUTION_16_9, false, false, {sonyimx134_framesize_1920x1088_oem, ARRAY_SIZE(sonyimx134_framesize_1920x1088_oem)} },

    /* 3264x2448@30fps base 3600x2774@750M: */
    {0, 0, 3264, 2448, 3600, 2774, 30, 30, 0x340, 0x2B5, 0x200, VIEW_FULL, RESOLUTION_4_3, false, true, {sonyimx134_framesize_3264x2448_750M_oem, ARRAY_SIZE(sonyimx134_framesize_3264x2448_750M_oem)} },

    /* 3264x2448@20fps base 3600x2722@490M_test: */
    //{0, 0, 3264, 2448, 3600, 2722, 20, 20, 0x340, 0x2B5, 0x200, VIEW_FULL, RESOLUTION_4_3, false, false, {sonyimx134_framesize_3264x2448_490M_test, ARRAY_SIZE(sonyimx134_framesize_3264x2448_490M_test)} },

	/* full size 15fps cs, es will revise a little(not correct 13fps) */
	{0, 0, 3264, 2448, 4150, 2962, 13, 15, 0x181, 0x141, 0xDE, VIEW_FULL, RESOLUTION_4_3, false, false, {sonyimx134_framesize_full_oem, ARRAY_SIZE(sonyimx134_framesize_full_oem)} },

    /* 3280x1840@30fps base 3600x2000@540M:change 1840 to 2448. */
    //{0, 0, 3280, 2448, 3600, 2000, 30, 30, 0x341, 0x258, 0x1F4, VIEW_FULL, RESOLUTION_4_3, false, true, {sonyimx134_framesize_3280x1840_540M, ARRAY_SIZE(sonyimx134_framesize_3280x1840_540M)} },

    /* 3280x1960@30fps base 3600x2148@580M. */
    {0, 0, 3280, 1960, 3600, 2148, 30, 30, 0, 0, 0x1F4, VIEW_FULL, RESOLUTION_16_9, false, true, {sonyimx134_framesize_3280x1960_580M_oem, ARRAY_SIZE(sonyimx134_framesize_3280x1960_580M_oem)} },

    /* 3280x2464@30fps base 3542x2598@690M. */
    {0, 0, 3280, 2464, 3600, 2728, 28, 28, 0, 0, 0x1F4, VIEW_FULL, RESOLUTION_4_3, false, true, {sonyimx134_framesize_3280x2464_690M_oem, ARRAY_SIZE(sonyimx134_framesize_3280x2464_690M_oem)} },

};
static framesizes_resource sonyimx134_framesize_resource[] = {
	{"sft", sonyimx134_sft_framesizes, ARRAY_SIZE(sonyimx134_sft_framesizes) },
	{"oem",  sonyimx134_oem_framesizes, ARRAY_SIZE(sonyimx134_oem_framesizes)}
};

static camera_sensor sonyimx134_sensor;
static void sonyimx134_set_default(void);

/*
 **************************************************************************
 * FunctionName: sonyimx134_read_reg;
 * Description : read sonyimx134 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_read_reg(u16 reg, u8 *val)
{
	return k3_ispio_read_reg(sonyimx134_sensor.i2c_config.index, sonyimx134_sensor.i2c_config.addr,
                reg, (u16*)val, sonyimx134_sensor.i2c_config.val_bits, sonyimx134_sensor.i2c_config.addr_bits );
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_read_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/

#if 0
static int sonyimx134_read_seq(struct _sensor_reg_t *seq, u32 size)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	return k3_ispio_read_seq(sonyimx134_sensor.i2c_config.index,
			sonyimx134_sensor.i2c_config.addr, seq, size, sonyimx134_sensor.i2c_config.val_bits);
}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_write_reg;
 * Description : write sonyimx134 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_write_reg(u16 reg, u8 val, u8 mask)
{
	return k3_ispio_write_reg(sonyimx134_sensor.i2c_config.index, sonyimx134_sensor.i2c_config.addr,
	reg, val, sonyimx134_sensor.i2c_config.val_bits, mask,  sonyimx134_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_write_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int sonyimx134_write_seq(const struct _sensor_reg_t *seq, u32 size, u8 mask)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	return k3_ispio_write_seq(sonyimx134_sensor.i2c_config.index, sonyimx134_sensor.i2c_config.addr,
                seq, size, sonyimx134_sensor.i2c_config.val_bits, mask,  sonyimx134_sensor.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_write_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void sonyimx134_write_isp_seq(const struct isp_reg_t *seq, u32 size)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	k3_ispio_write_isp_seq(seq, size);
}

#if 0
/*
 **************************************************************************
 * FunctionName: sonyimx134_read_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void sonyimx134_read_isp_seq(struct isp_reg_t *seq, u32 size)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	k3_ispio_read_isp_seq(seq, size);
}
#endif

#if 0
/*
 **************************************************************************
 * FunctionName: sonyimx134_read_isp_reg;
 * Description : Read ISP register;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static u32 sonyimx134_read_isp_reg(u32 reg_addr, u32 size)
{
	struct isp_reg_t reg_seq[4];
	int i = 0;
	u32 reg_value = 0x00;
	print_debug("Enter %s, size=%d", __func__, size);

	/*initialize buffer */
	for (i = 0; i < size; i++) {
		reg_seq[i].subaddr = reg_addr;
		reg_seq[i].value = 0x00;
		reg_seq[i].mask = 0x00;
		reg_addr++;
	}

	/*read register of isp for imx134 */
	sonyimx134_read_isp_seq(reg_seq, size);
	/*construct return value */
	do {
		i--;
		reg_value = reg_value << 8;
		reg_value |= reg_seq[i].value;
		print_debug("reg_seq[%d].value:%x", i, reg_seq[i].value);
	} while (i > 0);
	return reg_value;
}
#endif
/*
 **************************************************************************
 * FunctionName: sonyimx134_enum_frame_intervals;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_enum_frame_intervals(struct v4l2_frmivalenum *fi)
{
	assert(fi);

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
 * FunctionName: sonyimx134_get_format;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_get_format(struct v4l2_fmtdesc *fmt)
{
	if (fmt->type == V4L2_BUF_TYPE_VIDEO_OVERLAY) {
		fmt->pixelformat = sonyimx134_sensor.fmt[STATE_PREVIEW];
	} else {
		fmt->pixelformat = sonyimx134_sensor.fmt[STATE_CAPTURE];
	}
	return 0;
}

static int sonyimx134_get_capability(u32 id, u32 *value)
{
	int i;
	for (i = 0; i < sizeof(sonyimx134_cap) / sizeof(sonyimx134_cap[0]); ++i) {
		if (id == sonyimx134_cap[i].id) {
			*value = sonyimx134_cap[i].value;
			break;
		}
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_enum_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 max_index = ARRAY_SIZE(camera_framesizes) - 1;
	u32 this_max_index = sonyimx134_framesize_resource[framesizes_index].list_cnt - 1;

	assert(framesizes);
	print_debug("enter %s; ", __func__);

	if (framesizes->index > max_index) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	if ((camera_framesizes[framesizes->index].width > sonyimx134_framesize_resource[framesizes_index].frmsize_list[this_max_index].width)
		|| (camera_framesizes[framesizes->index].height > sonyimx134_framesize_resource[framesizes_index].frmsize_list[this_max_index].height)) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	framesizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	framesizes->discrete.width = sonyimx134_framesize_resource[framesizes_index].frmsize_list[this_max_index].width;
	framesizes->discrete.height = sonyimx134_framesize_resource[framesizes_index].frmsize_list[this_max_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_try_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_try_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	int max_index = sonyimx134_framesize_resource[framesizes_index].list_cnt - 1;

	assert(framesizes);

	print_debug("Enter Function:%s  ", __func__);


	if ((framesizes->discrete.width <= sonyimx134_framesize_resource[framesizes_index].frmsize_list[max_index].width)
	    && (framesizes->discrete.height <= sonyimx134_framesize_resource[framesizes_index].frmsize_list[max_index].height)) {
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
 * FunctionName: sonyimx134_set_framesizes;
 * Description : NA;
 * Input       : flag: if 1, set framesize to sensor,
 *					   if 0, only store framesize to camera_interface;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_set_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type,bool zsl_preview)
{
	int i = 0;
	bool match = false;
	int size = 0;
	assert(fs);

	print_info("Enter Function:%s State(%d), flag=%d, width=%d, height=%d",
		   __func__, state, flag, fs->width, fs->height);
	size = sonyimx134_framesize_resource[framesizes_index].list_cnt;

	#if 0
			if(HDR_MOVIE_ON == sonyimx134_sensor.hdrInfo.hdr_on){
				for (i = 0; i < size; i++) {
					if ((sonyimx134_framesizes[i].width >= fs->width)
					    && (sonyimx134_framesizes[i].height >= fs->height)
					    && (VIEW_HDR_MOVIE == sonyimx134_framesizes[i].view_type))
				     {
						fs->width = sonyimx134_framesizes[i].width;
						fs->height = sonyimx134_framesizes[i].height;
						match = true;
						break;
					}
				}
			}else
			{
				if (VIEW_FULL == view_type) {
					for (i = 0; i < sonyimx134_framesize_resource[framesizes_index].list_cnt; i++) {
						if ((sonyimx134_framesizes[i].width >= fs->width)
						    && (sonyimx134_framesizes[i].height >= fs->height)
						    && (VIEW_FULL == sonyimx134_framesizes[i].view_type)
						    && (camera_get_resolution_type(fs->width, fs->height)
						    <= sonyimx134_framesizes[i].resolution_type)) {
							fs->width = sonyimx134_framesizes[i].width;
							fs->height = sonyimx134_framesizes[i].height;
							match = true;
							break;
						}
					}
				}
			}

			if (false == match) {
					for (i = 0; i < size; i++) {
						if ((sonyimx134_framesizes[i].width >= fs->width)
						    && (sonyimx134_framesizes[i].height >= fs->height)
						    && (camera_get_resolution_type(fs->width, fs->height)
						   <= sonyimx134_framesizes[i].resolution_type)
				    			&& (VIEW_HDR_MOVIE != sonyimx134_framesizes[i].view_type)) {
							fs->width = sonyimx134_framesizes[i].width;
							fs->height = sonyimx134_framesizes[i].height;
							break;
						}
					}
				}
		#else
			{
				if (VIEW_FULL == view_type) {
					for (i = 0; i < sonyimx134_framesize_resource[framesizes_index].list_cnt; i++) {
					    if ((zsl_preview == false) && sonyimx134_framesize_resource[framesizes_index].frmsize_list[i].zsl_only )
					    {
					        continue;
					    }
						if ((sonyimx134_framesize_resource[framesizes_index].frmsize_list[i].width >= fs->width)
						    && (sonyimx134_framesize_resource[framesizes_index].frmsize_list[i].height >= fs->height)
						    && (VIEW_FULL == sonyimx134_framesize_resource[framesizes_index].frmsize_list[i].view_type)
						    && (camera_get_resolution_type(fs->width, fs->height)
						    <= sonyimx134_framesize_resource[framesizes_index].frmsize_list[i].resolution_type)) {
							fs->width = sonyimx134_framesize_resource[framesizes_index].frmsize_list[i].width;
							fs->height = sonyimx134_framesize_resource[framesizes_index].frmsize_list[i].height;
							match = true;
							break;
						}
					}
				}
			}

			if (false == match) {
				for (i = 0; i < size; i++) {
				    if ((zsl_preview == false) && sonyimx134_framesize_resource[framesizes_index].frmsize_list[i].zsl_only)
				    {
				        continue;
				    }

					if ((sonyimx134_framesize_resource[framesizes_index].frmsize_list[i].width >= fs->width)
						    && (sonyimx134_framesize_resource[framesizes_index].frmsize_list[i].height >= fs->height)
						    && (camera_get_resolution_type(fs->width, fs->height)
						   <= sonyimx134_framesize_resource[framesizes_index].frmsize_list[i].resolution_type)) {
							fs->width = sonyimx134_framesize_resource[framesizes_index].frmsize_list[i].width;
							fs->height = sonyimx134_framesize_resource[framesizes_index].frmsize_list[i].height;
							break;
					}
				}
			}
		#endif

		if (i >= sonyimx134_framesize_resource[framesizes_index].list_cnt) {
			print_error("request resolution larger than sensor's max resolution");
			return -EINVAL;
		}

		if (state == STATE_PREVIEW) {
			sonyimx134_sensor.preview_frmsize_index = i;
		} else {
			sonyimx134_sensor.capture_frmsize_index = i;
		}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_get_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_get_framesizes(camera_state state,
				     struct v4l2_frmsize_discrete *fs)
{
	int frmsize_index;

	assert(fs);

	if (state == STATE_PREVIEW) {
		frmsize_index = sonyimx134_sensor.preview_frmsize_index;
	} else if (state == STATE_CAPTURE) {
		frmsize_index = sonyimx134_sensor.capture_frmsize_index;
	} else {
		return -EINVAL;
	}
	fs->width = sonyimx134_framesize_resource[framesizes_index].frmsize_list[frmsize_index].width;
	fs->height = sonyimx134_framesize_resource[framesizes_index].frmsize_list[frmsize_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_init_isp_reg;
 * Description : load initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_init_isp_reg(void)
{
	int size = 0;
	camera_sensor *sensor = &sonyimx134_sensor;

    size = CAMERA_MAX_SETTING_SIZE;
	sonyimx134_write_isp_seq(sensor->effect->isp_settings, size);
#if 0 //hefei delete for putting isp setting into effect.h
#if 0
	if( HDR_MOVIE_ON== sonyimx134_sensor.hdrInfo.hdr_on)
	{
		if(sensor_module ==  MODULE_SUNNY){
			size = ARRAY_SIZE(isp_init_regs_sonyimx134_HDR_Sunny);
			sonyimx134_write_isp_seq(isp_init_regs_sonyimx134_HDR_Sunny, size);
		}else{
			size = ARRAY_SIZE(isp_init_regs_sonyimx134_HDR_Liteon);
			sonyimx134_write_isp_seq(isp_init_regs_sonyimx134_HDR_Liteon, size);
		}

	}
	else if (true == sonyimx134_sensor.hw_lowlight_on)
	{
		if(sensor_module == MODULE_SUNNY)
		{
			size = ARRAY_SIZE(isp_init_regs_sonyimx134_Sunny_lowlight);
			sonyimx134_write_isp_seq(isp_init_regs_sonyimx134_Sunny_lowlight, size);
		}
		else
		{
			size = ARRAY_SIZE(isp_init_regs_sonyimx134_Liteon_lowlight);
			sonyimx134_write_isp_seq(isp_init_regs_sonyimx134_Liteon_lowlight, size);
		}
	}
	else
	{
		if(sensor_module ==  MODULE_SUNNY)
		{
			size = ARRAY_SIZE(isp_init_regs_sonyimx134_Sunny);
			sonyimx134_write_isp_seq(isp_init_regs_sonyimx134_Sunny, size);
		}
		else
		{
			size = ARRAY_SIZE(isp_init_regs_sonyimx134_Liteon);
			sonyimx134_write_isp_seq(isp_init_regs_sonyimx134_Liteon, size);
		}
	}
#else
	if(sensor_module ==  MODULE_SUNNY)
		{
			size = ARRAY_SIZE(isp_init_regs_sonyimx134_Sunny);
			sonyimx134_write_isp_seq(isp_init_regs_sonyimx134_Sunny, size);
		}
		else
		{
			size = ARRAY_SIZE(isp_init_regs_sonyimx134_Liteon);
			sonyimx134_write_isp_seq(isp_init_regs_sonyimx134_Liteon, size);
		}
#endif
#endif
	return 0;
}
/*
 **************************************************************************
 * FunctionName: sonyimx134_support_hdr_movie;
 * Description : check sensor support hdr movie or not;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
#if 0
static int sonyimx134_support_hdr_movie(void)
{
	   return HDR_MOVIE_SUPPORT;
}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_get_hdr_movie_switch;
 * Description : the function that get hdr movie status on or off;
 * Input       : NA;
 * Output      : the status of hdr movie status;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
#if 0
static int sonyimx134_get_hdr_movie_switch(void)
{
	   return sonyimx134_sensor.hdrInfo.hdr_on;
}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_set_hdr_movie_switch;
 * Description : the function that set hdr movie status;
 * Input       : the status of hdr movie on or off;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
#if 0
static void sonyimx134_set_hdr_movie_switch(hdr_movie_switch on)
{
	print_info("Enter Function:%s on = %d",__func__,on);
	sonyimx134_sensor.hdrInfo.hdr_on = on;
}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx135_support_hw_lowlight;
 * Description : check sensor support hw lowlight or not;
 * ReturnValue : 1-supported 0-not;
 **************************************************************************
*/
#if 0
static int sonyimx134_support_hw_lowlight(void)
{
	return 1;
}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_init_reg;
 * Description : download initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_init_reg(void)
{
	int size = 0;

	print_debug("Enter Function:%s  , initsize=%d",
		    __func__, sizeof(sonyimx134_init_regs));


	if(sensor_module ==  MODULE_SUNNY)
	{
		size = ARRAY_SIZE(isp_init_regs_sonyimx134_Sunny);
		sonyimx134_write_isp_seq(isp_init_regs_sonyimx134_Sunny, size);
	}
	else
	{
		size = ARRAY_SIZE(isp_init_regs_sonyimx134_Liteon);
		sonyimx134_write_isp_seq(isp_init_regs_sonyimx134_Liteon, size);
	}

	if (0 != k3_ispio_init_csi(sonyimx134_sensor.mipi_index,
			sonyimx134_sensor.mipi_lane_count, sonyimx134_sensor.lane_clk)) {
		return -EFAULT;
	}
	
	k3_ispio_config_lane_clk(sonyimx134_sensor.mipi_index, sonyimx134_sensor.mipi_lane_count, sonyimx134_sensor.lane_clk);

	size = ARRAY_SIZE(sonyimx134_init_regs);
	if (0 != sonyimx134_write_seq(sonyimx134_init_regs, size, 0x00)) {
		print_error("line %d, fail to init sonyimx134 sensor",__LINE__);
		return -EFAULT;
	}
	if(CAMERA_SENSOR_FLIP_TYPE_H_V == video_get_primary_sensor_flip_type()) {
		sonyimx134_write_reg(SONYIMX134_FLIP, 0x03, 0x00); //turn camera layout
		print_info("%s:change flip and mirror",__func__);
	}
    /* end */

#ifdef IMX134_OTP
	if((sonyimx134_otp_flag & SONYIMX134_OTP_LSC_READ) ==SONYIMX134_OTP_LSC_READ)
	{
		sonyimx134_otp_enable_lsc(false);
		sonyimx134_otp_set_lsc();
		sonyimx134_otp_enable_lsc(true);
	}
#endif
	return 0;
}

static int sonyimx134_set_hflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);
	sonyimx134_sensor.hflip = flip;
	return 0;
}
static int sonyimx134_get_hflip(void)
{
	print_debug("enter %s", __func__);

	return sonyimx134_sensor.hflip;
}
static int sonyimx134_set_vflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);

	sonyimx134_sensor.vflip = flip;

	return 0;
}
static int sonyimx134_get_vflip(void)
{
	print_debug("enter %s", __func__);
	return sonyimx134_sensor.vflip;
}

static int sonyimx134_update_flip(u16 width, u16 height)
{
	u8 new_flip = ((sonyimx134_sensor.vflip << 1) | sonyimx134_sensor.hflip);
    print_debug("Enter %s  ", __func__);
	if(sonyimx134_sensor.old_flip != new_flip) {
		k3_ispio_update_flip((sonyimx134_sensor.old_flip ^ new_flip) & 0x03, width, height, PIXEL_ORDER_CHANGED);

		sonyimx134_sensor.old_flip = new_flip;

	    if(CAMERA_SENSOR_FLIP_TYPE_H_V == video_get_primary_sensor_flip_type()){
            sonyimx134_write_reg(SONYIMX134_FLIP, sonyimx134_sensor.vflip ? 0x00 : 0x02, ~0x02);
    		sonyimx134_write_reg(SONYIMX134_FLIP, sonyimx134_sensor.hflip ? 0x00 : 0x01, ~0x01);
    	}
        else
    	{
            sonyimx134_write_reg(SONYIMX134_FLIP, sonyimx134_sensor.vflip ? 0x02 : 0x00, ~0x02);
    		sonyimx134_write_reg(SONYIMX134_FLIP, sonyimx134_sensor.hflip ? 0x01 : 0x00, ~0x01);
        }
		//msleep(200);
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_framesize_switch;
 * Description : switch frame size, used by preview and capture
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_framesize_switch(camera_state state)
{
	u8 next_frmsize_index;

	if (state == STATE_PREVIEW)
		next_frmsize_index = sonyimx134_sensor.preview_frmsize_index;
	else
		next_frmsize_index = sonyimx134_sensor.capture_frmsize_index;

	print_debug("Enter Function:%s frm index=%d", __func__, next_frmsize_index);

	if (next_frmsize_index >= sonyimx134_framesize_resource[framesizes_index].list_cnt){
		print_error("Unsupport sensor setting index: %d",next_frmsize_index);
		return -ETIME;
	}

	if (0 != sonyimx134_write_seq(sonyimx134_sensor.frmsize_list[next_frmsize_index].sensor_setting.setting
		,sonyimx134_sensor.frmsize_list[next_frmsize_index].sensor_setting.seq_size, 0x00)) {
		print_error("fail to init sonyimx134 sensor");
		return -ETIME;
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_stream_on;
 * Description : download preview seq for sensor preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_stream_on(camera_state state)
{
	print_debug("Enter Function:%s ", __func__);

#ifdef ISP_DEBUG_ZSL
    if(color_bar_flg == 1){
    	sonyimx134_write_reg(0x0601, 0x02, 0x00);
    }
    else{
    	sonyimx134_write_reg(0x0601, 0x00, 0x00);
    }
#endif

	return sonyimx134_framesize_switch(state);
}

/*  **************************************************************************
* FunctionName: sonyimx134_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int sonyimx134_check_sensor(void)
{
	u8 idl = 0;
	u8 idh = 0;
	u16 id = 0;
	//int pin_id = 0;
    camera_sensor *sensor = &sonyimx134_sensor;

	sonyimx134_read_reg(0x0016, &idh);
	sonyimx134_read_reg(0x0017, &idl);

	id = ((idh << 8) | idl);
	print_info("sonyimx134 product id:0x%x", id);
	if (SONYIMX134_CHIP_ID != id) {
		print_error("Invalid product id ,Could not load sensor sonyimx134\n");
		return -ENODEV;
	}
/* FIXME:balong V9R1 TBD 2013/4/28 start */
#if 0
	pin_id = gpio_get_value(GPIO_13_7);
	if(pin_id < 0)
	{
		pin_id = 0;
		print_error("sonyimx134_check_sensor fail to get gpio value!!! set pin_id to 0 by default MODULE_LITEON !\n");
	}
	sensor_module = pin_id>0 ? MODULE_SUNNY:MODULE_LITEON;
#endif
	sensor_module = MODULE_SUNNY;
/* FIXME:balong V9R1 TBD 2013/4/28 end */

	if(sensor_module ==  MODULE_SUNNY){
		sonyimx134_sensor.vcm = &vcm_dw9714_Sunny;
        sensor->effect = &effect_imx134_sunny;
		snprintf(sonyimx134_sensor.info.name, sizeof(sonyimx134_sensor.info.name),"sonyimx134_sunny");
	}else{
		sonyimx134_sensor.vcm = &vcm_dw9714_Liteon;
        sensor->effect = &effect_imx134_liteon;
		snprintf(sonyimx134_sensor.info.name, sizeof(sonyimx134_sensor.info.name),"sonyimx134_liteon");
	}

#ifdef IMX134_OTP
	sonyimx134_sensor.vcm->get_vcm_otp = sonyimx134_otp_get_vcm;
	sonyimx134_get_otp_from_sensor();
#endif
	return 0;
}

#ifdef ISP_DEBUG_ZSL
static int sonyimx134_debug_init(void)
{
    if(ap_ae_flg == 1){ /* just an example and test case for AP write AE mode */
    	sonyimx134_sensor.aec_addr[0] = 0;
    	sonyimx134_sensor.aec_addr[1] = 0;
    	sonyimx134_sensor.aec_addr[2] = 0;
    	sonyimx134_sensor.agc_addr[0] = 0;
    	sonyimx134_sensor.agc_addr[1] = 0;
    	sonyimx134_sensor.ap_writeAE_delay = 6000; /* 5 expo and gain registers, 6000 us is enough */
    }
    else{
        sonyimx134_sensor.aec_addr[0] = 0x0000;
    	sonyimx134_sensor.aec_addr[1] = 0x0202;
    	sonyimx134_sensor.aec_addr[2] = 0x0203;
    	sonyimx134_sensor.agc_addr[0] = 0x0000; /*0x0204 high byte not needed*/
    	sonyimx134_sensor.agc_addr[1] = 0x0205;
    }

    return 0;
}
#endif


/****************************************************************************
* FunctionName: sonyimx134_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
int sonyimx134_power(camera_power_state power)
{
	int ret = 0;

	print_debug("Enter Function:%s\n ", __func__);

	if(VIDEO_BOARD_TYPE_SFT == video_get_board_type()) {
		if (power == POWER_ON) {
			k3_socgpio_power_sensor(1, M_CAMERA_ANALOG_VDD);
			k3_socgpio_power_sensor(0, M_CAMERA_IO_VDD);
				k3_ispgpio_power_sensor(&sonyimx134_sensor, power);
			k3_socgpio_power_sensor(1, M_CAMERA_CORE_VDD);
			k3_socgpio_power_sensor(1, M_CAMERA_VCM_VDD);
		} else {
			k3_ispio_deinit_csi(sonyimx134_sensor.mipi_index);

			k3_socgpio_power_sensor(0, M_CAMERA_VCM_VDD);
			k3_socgpio_power_sensor(0, M_CAMERA_CORE_VDD);
			udelay(200);
			k3_ispgpio_power_sensor(&sonyimx134_sensor, power);
			k3_socgpio_power_sensor(1, M_CAMERA_IO_VDD);
			udelay(10);
			k3_socgpio_power_sensor(0, M_CAMERA_ANALOG_VDD);
		}	
	} else {

		if (power == POWER_ON) {

			k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);
			
			k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);
			k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);//k3_ispldo_power_sensor(power, "sec-cameralog-vcc");
			k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);
			
			k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
			k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
			udelay(1);
			k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);//ret = camera_power_core_ldo(power);
			udelay(200);

			k3_ispio_ioconfig(&sonyimx134_sensor, power);
			k3_ispgpio_power_sensor(&sonyimx134_sensor, power);
			msleep(3);
		} else {
			k3_ispio_deinit_csi(sonyimx134_sensor.mipi_index);

			k3_ispgpio_power_sensor(&sonyimx134_sensor, power);
			k3_ispio_ioconfig(&sonyimx134_sensor, power);

			k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);//camera_power_core_ldo(power);
			udelay(200);
	       		 k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
			k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
			
			k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);
			k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);//k3_ispldo_power_sensor(power, "sec-cameralog-vcc");
			k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);

			
			k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);
		}
	}


#ifdef ISP_DEBUG_ZSL
    sonyimx134_debug_init();
#endif

	return ret;
}

static int sonyimx134_get_sensor_aperture(void)
{
	return SONYIMX134_APERTURE_FACTOR;
}

#if 0
static int sonyimx134_get_equivalent_focus()
{
	return SONYIMX134_EQUIVALENT_FOCUS;
}
#endif

/*
 * Here gain is in unit 1/16 of sensor gain,
 * y36721 todo, temporarily if sensor gain=0x10, ISO is 100
 * in fact we need calibrate an ISO-ET-gain table.
 */
u32 sonyimx134_gain_to_iso(int gain)
{
	return (gain * 100) / 0x10;
}

u32 sonyimx134_iso_to_gain(int iso)
{
	return (iso * 0x10) / 100;
}

void sonyimx134_set_gain(u32 gain)
{
	if (gain == 0)
		return;
	gain = 256 - (256 * 16) / gain;
	//sonyimx134_write_reg(SONYIMX134_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	sonyimx134_write_reg(SONYIMX134_GAIN_REG_L, gain & 0xff, 0x00);
}

void sonyimx134_set_exposure(u32 exposure)
{
	exposure >>= 4;
	sonyimx134_write_reg(SONYIMX134_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	sonyimx134_write_reg(SONYIMX134_EXPOSURE_REG_L, exposure & 0xff, 0x00);
}


void sonyimx134_set_exposure_gain(u32 exposure, u32 gain)
{
//	u32	 tmp_digital_gain = 0;
//	u8    digital_ratio = 0;
	u8    digital_h = 0;
	u8    digital_l = 0;
	u32  analog_gain = 0;
	sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold

	exposure >>= 4;
	sonyimx134_write_reg(SONYIMX134_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	sonyimx134_write_reg(SONYIMX134_EXPOSURE_REG_L, exposure & 0xff, 0x00);

	if (gain == 0)
		goto out;

#if 0
	if(gain>SONYIMX134_MAX_ANALOG_GAIN*Q16)
	{
		tmp_digital_gain = (gain*256) >> 4;
		tmp_digital_gain = tmp_digital_gain >> 3;

		digital_ratio = (gain/SONYIMX134_MAX_ANALOG_GAIN) >> 4;
		digital_h = digital_ratio;
		digital_l = tmp_digital_gain - digital_ratio*256;
		analog_gain = SONYIMX134_MAX_ANALOG_GAIN*Q16;
	}
	else
	{
		analog_gain = gain;
		digital_h = 1;
		digital_l = 0;
	}
#else
	analog_gain = gain;
	digital_h = 1;
	digital_l = 0;
#endif

	analog_gain = 256 - (256 * 16) / analog_gain;
	sonyimx134_write_reg(SONYIMX134_GAIN_REG_L, analog_gain & 0xff, 0x00);
	sonyimx134_write_reg(DIG_GAIN_GR_H, digital_h & 0xff, 0x00);
	sonyimx134_write_reg(DIG_GAIN_GR_L, digital_l & 0xff, 0x00);
	sonyimx134_write_reg(DIG_GAIN_R_H, digital_h & 0xff, 0x00);
	sonyimx134_write_reg(DIG_GAIN_R_L, digital_l & 0xff, 0x00);
	sonyimx134_write_reg(DIG_GAIN_B_H, digital_h & 0xff, 0x00);
	sonyimx134_write_reg(DIG_GAIN_B_L, digital_l & 0xff, 0x00);
	sonyimx134_write_reg(DIG_GAIN_GB_H, digital_h & 0xff, 0x00);
	sonyimx134_write_reg(DIG_GAIN_GB_L, digital_l & 0xff, 0x00);
out:
	sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group hold
	return;
}

/****************************************************************************
* FunctionName: sonyimx134_set_awb_gain;
* Description : NA;
* Input       : R,GR,GB,B gain from isp;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
#if 0
void sonyimx134_set_awb_gain(u16 b_gain, u16 gb_gain, u16 gr_gain, u16 r_gain)
{

	sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
	sonyimx134_write_reg(SONYIMX134_ABS_GAIN_B_H, (b_gain >> 8) & 0xff, 0x00);
	sonyimx134_write_reg(SONYIMX134_ABS_GAIN_B_L, b_gain & 0xff, 0x00);
	sonyimx134_write_reg(SONYIMX134_ABS_GAIN_GB_H, (gb_gain >> 8) & 0xff, 0x00);
	sonyimx134_write_reg(SONYIMX134_ABS_GAIN_GB_L, gb_gain & 0xff, 0x00);
	sonyimx134_write_reg(SONYIMX134_ABS_GAIN_GR_H, (gr_gain >> 8) & 0xff, 0x00);
	sonyimx134_write_reg(SONYIMX134_ABS_GAIN_GR_L, gr_gain & 0xff, 0x00);
	sonyimx134_write_reg(SONYIMX134_ABS_GAIN_R_H, (r_gain >> 8) & 0xff, 0x00);
	sonyimx134_write_reg(SONYIMX134_ABS_GAIN_R_L, r_gain & 0xff, 0x00);

	sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group open
}
#endif

void sonyimx134_set_vts(u16 vts)
{
	print_debug("Enter %s  ", __func__);
	sonyimx134_write_reg(SONYIMX134_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
	sonyimx134_write_reg(SONYIMX134_VTS_REG_L, vts & 0xff, 0x00);
}

u32 sonyimx134_get_vts_reg_addr(void)
{
	return SONYIMX134_VTS_REG_H;
}

#if 0
static sensor_reg_t* sonyimx134_construct_vts_reg_buf(u16 vts, u16 *psize)
{
	static sensor_reg_t sonyimx134_vts_regs[] = {
		{SONYIMX134_VTS_REG_H, 0x00},
		{SONYIMX134_VTS_REG_L, 0x00},
	};

	print_debug("Enter %s,vts=%u", __func__, vts);
	sonyimx134_vts_regs[0].value = (vts >> 8) & 0xff ;
	sonyimx134_vts_regs[1].value = vts & 0xff;

	*psize = ARRAY_SIZE(sonyimx134_vts_regs);
	return sonyimx134_vts_regs;
}
#endif

extern u32 sensor_override_params[OVERRIDE_TYPE_MAX];
static u32 sonyimx134_get_override_param(camera_override_type_t type)
{
	u32 ret_val = sensor_override_params[type];

	switch (type) {
	case OVERRIDE_ISO_HIGH:
		ret_val = SONYIMX134_MAX_ISO;
		break;

	case OVERRIDE_ISO_LOW:
		ret_val = SONYIMX134_MIN_ISO;
		break;

	/* decrease frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_HIGH2MID:
		ret_val = SONYIMX134_AUTOFPS_GAIN_HIGH2MID;
		break;
	case OVERRIDE_AUTOFPS_GAIN_MID2LOW:
		ret_val = SONYIMX134_AUTOFPS_GAIN_MID2LOW;
		break;

	/* increase frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_LOW2MID:
		ret_val = SONYIMX134_AUTOFPS_GAIN_LOW2MID;
		break;
	case OVERRIDE_AUTOFPS_GAIN_MID2HIGH:
		ret_val = SONYIMX134_AUTOFPS_GAIN_MID2HIGH;
		break;

	case OVERRIDE_FPS_MAX:
		ret_val = SONYIMX134_MAX_FRAMERATE;
		break;

	case OVERRIDE_FPS_MID:
		ret_val = SONYIMX134_MID_FRAMERATE;
		break;

	case OVERRIDE_FPS_MIN:
		ret_val = SONYIMX134_MIN_FRAMERATE;
		break;

	case OVERRIDE_CAP_FPS_MIN:
		ret_val = SONYIMX134_MIN_CAP_FRAMERATE;
		break;

	case OVERRIDE_FLASH_TRIGGER_GAIN:
		ret_val = SONYIMX134_FLASH_TRIGGER_GAIN;
		break;

	case OVERRIDE_SHARPNESS_PREVIEW:
		ret_val = SONYIMX134_SHARPNESS_PREVIEW;
		break;

	case OVERRIDE_SHARPNESS_CAPTURE:
		ret_val = SONYIMX134_SHARPNESS_CAPTURE;
		break;

	default:
		print_error("%s:not override or invalid type %d, use default",__func__, type);
		break;
	}

	return ret_val;
}

#if 0
static int sonyimx134_fill_denoise_buf(u8 *ybuf, u16 *uvbuf, u8 size, camera_state state, bool flash_on)
{
	u32 ae_th[3];
	u32 ae_value = get_writeback_gain() * get_writeback_expo() / 0x10;
	int index = sonyimx134_sensor.preview_frmsize_index;

	if( (ybuf==NULL)||(uvbuf==NULL)||(size <7 ) ){
		print_error("%s invalid arguments",__func__);
		return -1;
	}

	ybuf[0] = SONYIMX134_ISP_YDENOISE_COFF_1X;
	ybuf[1] = SONYIMX134_ISP_YDENOISE_COFF_2X;
	ybuf[2] = SONYIMX134_ISP_YDENOISE_COFF_4X;
	ybuf[3] = SONYIMX134_ISP_YDENOISE_COFF_8X;
	ybuf[4] = SONYIMX134_ISP_YDENOISE_COFF_16X;
	ybuf[5] = SONYIMX134_ISP_YDENOISE_COFF_32X;
	ybuf[6] = SONYIMX134_ISP_YDENOISE_COFF_64X;

	uvbuf[0] = SONYIMX134_ISP_UVDENOISE_COFF_1X;
	uvbuf[1] = SONYIMX134_ISP_UVDENOISE_COFF_2X;
	uvbuf[2] = SONYIMX134_ISP_UVDENOISE_COFF_4X;
	uvbuf[3] = SONYIMX134_ISP_UVDENOISE_COFF_8X;
	uvbuf[4] = SONYIMX134_ISP_UVDENOISE_COFF_16X;
	uvbuf[5] = SONYIMX134_ISP_UVDENOISE_COFF_32X;
	uvbuf[6] = SONYIMX134_ISP_UVDENOISE_COFF_64X;

	if (flash_on == false) {
		ae_th[0] = sonyimx134_sensor.frmsize_list[index].banding_step_50hz * 0x18;
		ae_th[1] = 3 * sonyimx134_sensor.frmsize_list[index].banding_step_50hz * 0x10;
		ae_th[2] = sonyimx134_sensor.frmsize_list[index].vts * 0x20;

		if (sonyimx134_sensor.frmsize_list[index].binning == false) {
			ae_th[0] *= 2;
			ae_th[1] *= 2;
			ae_th[2] *= 2;
		}

		/* simplify dynamic denoise threshold*/
		if (ae_value <= ae_th[0]) {
			ybuf[0] = SONYIMX134_ISP_YDENOISE_COFF_1X;
			ybuf[1] = SONYIMX134_ISP_YDENOISE_COFF_2X;
		} else {
			ybuf[0] = SONYIMX134_ISP_YDENOISE_COFF_2X;
			ybuf[1] = SONYIMX134_ISP_YDENOISE_COFF_2X;
		}
	} else {
		/* should calculated in capture_cmd again. */
		ybuf[0] = SONYIMX134_ISP_YDENOISE_COFF_1X;
		ybuf[1] = SONYIMX134_ISP_YDENOISE_COFF_2X;
	}

	return 0;
}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_get_hdr_y;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
#if 0
static int sonyimx134_get_lux_matrix(struct _sensor_reg_t *buf,lux_stat_matrix_tbl *lux_tbl )
{
	u32 size = sizeof(sonyimx134_hdr_regs_y)/sizeof(sonyimx134_hdr_regs_y[0]);
	u16 y = 0;
	int i ,j;
	u16 y_l = 0;
	u16 y_h = 0;
	assert(buf);
	assert(lux_tbl);
	sonyimx134_read_seq(buf,size);

	lux_tbl->size = size/2;
	sonyimx134_sensor.lux_matrix.size = lux_tbl->size;
	for (i = 0,j = 0; i< size;i+=2,j++)
	{
		y_h = sonyimx134_hdr_regs_y[i].value & 0xff;
		y_l = sonyimx134_hdr_regs_y[i+1].value;
		y   = y_h;
		y   = y<<8|y_l;
		lux_tbl->matrix_table[j] = y;
		sonyimx134_sensor.lux_matrix.matrix_table[j] = y;
		print_debug("j = %d,every y = 0x%d",j,lux_tbl->matrix_table[j]);
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
u32 sonyimx134_get_gain(void)
{
	u8 gain_l = 0;

	u8 short_gain = 0;
	u32 gain = 0;
	sonyimx134_read_reg(SONYIMX134_GAIN_REG_L, &gain_l);

	sonyimx134_read_reg(WD_ANA_GAIN_DS, &short_gain);
	//gain = (gain_h << 8) | gain_l;
	gain = gain_l;

	if(_IS_DEBUG_AE)
	{
		print_info("%s-0x0205=%x",__func__,gain_l);
		print_info("%s-0x0233=%x",__func__,short_gain);
	}
	return gain;
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_get_exposure;
 * Description :get exposure from sensor
 * Input       	 NA;
 * Output      	 exposure value from sensor
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
u32  sonyimx134_get_exposure(void)
{
	u32 expo = 0;
	u8 expo_h = 0;
	u8 expo_l = 0;
	u8 expo_short_h = 0;
	u8 expo_shot_l = 0;
	sonyimx134_read_reg(SONYIMX134_EXPOSURE_REG_H, &expo_h);
	sonyimx134_read_reg(SONYIMX134_EXPOSURE_REG_L, &expo_l);

	sonyimx134_read_reg(WD_COARSE_INTEG_TIME_DS_H, &expo_short_h);
	sonyimx134_read_reg(WD_COARSE_INTEG_TIME_DS_L, &expo_shot_l);

	if(_IS_DEBUG_AE)
	{
		print_info("sonyimx134_get_exposure-0x0202=%x,0x0203=%x",expo_h,expo_l);
		print_info("sonyimx134_get_exposure-0x0230=%x,0x0231=%x",expo_short_h,expo_shot_l);
	}
	expo = expo_h &0xff;
	expo = expo << 8 | expo_l;
	return expo;
}
/*
 **************************************************************************
 * FunctionName: sonyimx134_set_hdr_exposure_gain;
 * Description 	   : set exposure and gain to sensor.
 * Input		   : the value of exposure and gain ,that include long exposure short exposure and long gain db ,short gain db
 		          :  gain is db but not times
 * Output      	   : NA
 * ReturnValue   : NA;
 * Other       	   : NA;
 **************************************************************************
*/
#if 0
void sonyimx134_set_hdr_exposure_gain(u32 expo_long,u16 gain_global,u32 expo_short,u16 short_gain)
{
       u16 gain_switch_long = 0;
	u16 gain_switch_short = 0;

	gain_switch_long = gain_global;
	gain_switch_short = short_gain;
	if(_IS_DEBUG_AE)
	{
	       print_info("__debug_esen: Enter %s  gain_switch_long = %d ", __func__,gain_switch_long);
	       print_info("__debug_esen: Enter %s  expo_long = %d ", __func__,expo_long);
		print_info("__debug_esen: Enter %s  gain_switch_short = %d ", __func__,gain_switch_short);
	       print_info("__debug_esen: Enter %s  expo_short = %d", __func__,expo_short);
	}

	sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
	sonyimx134_write_reg(SONYIMX134_EXPOSURE_REG_H, (expo_long >> 8) & 0xff, 0x00);
	sonyimx134_write_reg(SONYIMX134_EXPOSURE_REG_L, expo_long & 0xff, 0x00);
	sonyimx134_write_reg(WD_COARSE_INTEG_TIME_DS_H, (expo_short >> 8) & 0xff, 0x00);
	sonyimx134_write_reg(WD_COARSE_INTEG_TIME_DS_L, expo_short & 0xff, 0x00);
	sonyimx134_write_reg(SONYIMX134_GAIN_REG_L, gain_switch_long, 0x00);
	sonyimx134_write_reg(WD_ANA_GAIN_DS, gain_switch_short, 0x00);
	sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release

}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_set_ATR_ctrl_points;
 * Description 	   : modify hdr atr curve with parameter inputed atr_ctrl_points .
 * Input		   : ATR control points parameter atr_ctrl_points
 * Output      	   : NA
 * ReturnValue   : NA;
 * Other       	   : NA;
 **************************************************************************
*/
#if 0
void sonyimx134_set_ATR_ctrl_points(atr_ctrl_points * in_atr_ctr_pints)
{
 	print_debug("enter %s",__func__);
 	assert(in_atr_ctr_pints);

	sonyimx134_sensor.hdr_points.tc_out_sat = in_atr_ctr_pints->tc_out_sat;
	sonyimx134_sensor.hdr_points.tc_out_mid = in_atr_ctr_pints->tc_out_mid;
	sonyimx134_sensor.hdr_points.tc_out_noise = in_atr_ctr_pints->tc_out_noise;
	sonyimx134_sensor.hdr_points.tc_sat_brate = in_atr_ctr_pints->tc_sat_brate;
	sonyimx134_sensor.hdr_points.tc_mid_brate= in_atr_ctr_pints->tc_mid_brate;
	sonyimx134_sensor.hdr_points.tc_noise_brate= in_atr_ctr_pints->tc_noise_brate;
	sonyimx134_sensor.hdr_points.ae_sat= in_atr_ctr_pints->ae_sat;
	sonyimx134_sensor.hdr_points.wb_lmt= in_atr_ctr_pints->wb_lmt;

	sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
	sonyimx134_write_reg(ATR_OUT_NOISE_REG_H, (in_atr_ctr_pints->tc_out_noise >> 8) & 0x03f, 0x00);
	sonyimx134_write_reg(ATR_OUT_NOISE_REG_L, in_atr_ctr_pints->tc_out_noise & 0xff, 0x00);
	sonyimx134_write_reg(ATR_OUT_MID_REG_H, (in_atr_ctr_pints->tc_out_mid >> 8) & 0x03f, 0x00);
	sonyimx134_write_reg(ATR_OUT_MID_REG_L, in_atr_ctr_pints->tc_out_mid & 0xff, 0x00);
	sonyimx134_write_reg(ATR_OUT_SAT_REG_H, (in_atr_ctr_pints->tc_out_sat >> 8) & 0x03f, 0x00);
	sonyimx134_write_reg(ATR_OUT_SAT_REG_L, in_atr_ctr_pints->tc_out_sat & 0xff, 0x00);
	sonyimx134_write_reg(ATR_NOISE_BRATE_REG, in_atr_ctr_pints->tc_noise_brate& 0x03f, 0x00);
	sonyimx134_write_reg(ATR_MID_BRATE_REG, in_atr_ctr_pints->tc_mid_brate & 0xff, 0x00);
	sonyimx134_write_reg(ATR_SAT_BRATE_REG, in_atr_ctr_pints->tc_sat_brate & 0xff, 0x00);
#if 0
	sonyimx134_write_reg(WB_LMT_REG_H, (in_atr_ctr_pints->ae_sat >> 8) & 0xff,0x00);
	sonyimx134_write_reg(WB_LMT_REG_L, in_atr_ctr_pints->ae_sat & 0xff,0x00);
	sonyimx134_write_reg(AE_SAT_REG_H, (in_atr_ctr_pints->wb_lmt >> 8) & 0xff,0x00);
	sonyimx134_write_reg(AE_SAT_REG_L, in_atr_ctr_pints->wb_lmt & 0xff,0x00);
#endif
	sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_get_ATR_ctrl_points;
 * Description 	   : get ATR control points info with atr_ctrl_points struct.
 * Input		   : the storage space of atr_ctrl_points
 * Output      	   : NA
 * ReturnValue   : NA;
 * Other       	   : NA;
 **************************************************************************
*/
#if 0
void sonyimx134_get_ATR_ctrl_points(atr_ctrl_points * in_atr_ctr_pints)
{
	u8 tc_out_noise_h = 0;
	u8 tc_out_noise_l = 0;
	u8 tc_out_mid_h = 0;
	u8 tc_out_mid_l = 0;
	u8 tc_out_sat_h = 0;
	u8 tc_out_sat_l = 0;
	u8 tc_out_noise = 0;
	u8 tc_out_mid = 0;
	u8 tc_out_sat = 0;
	 print_debug("enter %s",__func__);
	 assert(in_atr_ctr_pints);
	sonyimx134_read_reg(ATR_OUT_NOISE_REG_H, &tc_out_noise_h);
	sonyimx134_read_reg(ATR_OUT_NOISE_REG_L, &tc_out_noise_l);
	sonyimx134_read_reg(ATR_OUT_MID_REG_H, &tc_out_noise_h);
	sonyimx134_read_reg(ATR_OUT_MID_REG_L, &tc_out_mid_l);
	sonyimx134_read_reg(ATR_OUT_SAT_REG_H, &tc_out_sat_h);
	sonyimx134_read_reg(ATR_OUT_SAT_REG_L, &tc_out_sat_l);
	tc_out_noise = tc_out_noise_h;
	tc_out_noise = (tc_out_noise << 8)|tc_out_noise_l;
	tc_out_mid = tc_out_mid_h;
	tc_out_mid = (tc_out_mid << 8)|tc_out_mid_l;
	tc_out_sat = tc_out_sat_h;
	tc_out_sat = (tc_out_sat << 8)|tc_out_sat_l;
	in_atr_ctr_pints->tc_out_noise = tc_out_noise;
	in_atr_ctr_pints->tc_out_mid = tc_out_mid;
	in_atr_ctr_pints->tc_out_sat = tc_out_sat;
}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_set_ATR;
 * Description : turn on or off atr curve;
 * Input       : 1 turn on atr ,0 turn off atr;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
#if 0
void sonyimx134_set_ATR(int on)
{
       if(on == 0)
       {//ATR off
		sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
		sonyimx134_write_reg(ATR_OFF_SETTING_1,0x00, 0x00);
		sonyimx134_write_reg(ATR_OFF_SETTING_2,0x00, 0x00);
		sonyimx134_write_reg(TRIGGER_SETTING,0x01, 0x00);
		sonyimx134_write_reg(0x4344,0x01, 0x00);//ARNR
		sonyimx134_write_reg(0x4364,0x0B, 0x00);
		sonyimx134_write_reg(0x436C,0x00, 0x00);
		sonyimx134_write_reg(0x436D,0x00, 0x00);
		sonyimx134_write_reg(0x436E,0x00, 0x00);
		sonyimx134_write_reg(0x436F,0x00, 0x00);
		sonyimx134_write_reg(0x4369,0x00, 0x00);
		sonyimx134_write_reg(0x437B,0x00, 0x00);
		sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
	}
	else
	{//ATR on
		sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
		sonyimx134_write_reg(0x437B,0x01, 0x00);
		sonyimx134_write_reg(0x4369,0x0f, 0x00);
		sonyimx134_write_reg(0x436F,0x06, 0x00);
		sonyimx134_write_reg(0x436E,0x00, 0x00);
		sonyimx134_write_reg(0x436D,0x00, 0x00);
		sonyimx134_write_reg(0x436C,0x00, 0x00);
		sonyimx134_write_reg(0x4364,0x0B, 0x00);

		sonyimx134_write_reg(0x4344,0x01, 0x00);

		sonyimx134_write_reg(TRIGGER_SETTING,0x00, 0x00);
		sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
	}
	sonyimx134_sensor.hdrInfo.atr_on  = on;
}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_over_exposure_adjust;
 * Description :
 * Input       	:
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
#if 0
void sonyimx134_over_exposure_adjust(int on,stats_hdr_frm * frm_stats)
{
	print_debug("enter %s  on = %d",__func__,on);
	if(on == 1)
	{
		sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
		sonyimx134_write_reg(0x4470,frm_stats->frm_ave_h&0xff,0x00);//frm_ave
		sonyimx134_write_reg(0x4471,frm_stats->frm_ave_l&0xff,0x00);//frm_ave2
		sonyimx134_write_reg(0x4472,frm_stats->frm_min_h&0xff,0x00);//frm_min1
		sonyimx134_write_reg(0x4473,frm_stats->frm_min_l&0xff,0x00);//frm_min2
		sonyimx134_write_reg(0x4474,frm_stats->frm_max_h&0xff,0x00);//frm_max1
		sonyimx134_write_reg(0x4475,frm_stats->frm_max_l&0xff,0x00);//frm_max2
		sonyimx134_write_reg(0x4476,0x01,0x00);
		sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
		if(_IS_DEBUG_AE)
		{
			print_info(" frm_ave_h = %d,frm_ave_l =%d,frm_min_h=%d,frm_min_l=%d,frm_max_h=%d,frm_max_l=%d,",
				frm_stats->frm_ave_h,frm_stats->frm_ave_l,frm_stats->frm_min_h,frm_stats->frm_min_l,
				frm_stats->frm_max_h,frm_stats->frm_max_l);
		}
	}
	else
	{
		sonyimx134_write_reg(0x4476,0x00,0x00);
	}
	sonyimx134_sensor.hdrInfo.atr_over_expo_on = on;
}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_set_ATR;
 * Description : turn on or off atr curve;
 * Input       : 1 turn on atr ,0 turn off atr;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
#if 0
void sonyimx134_set_lmt_sat(u32 lmt_value, u32 sat_value)
{
	if(_IS_DEBUG_AE)
	{
		       print_info(" Enter %s  lmt_value = %x ", __func__,lmt_value);
			print_info(" Enter %s  sat_value = %x ", __func__,sat_value);

}

	sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
	sonyimx134_write_reg(WB_LMT_REG_H, (lmt_value >> 8) & 0xff, 0x00);
	sonyimx134_write_reg(WB_LMT_REG_L, lmt_value & 0xff, 0x00);
	sonyimx134_write_reg(AE_SAT_REG_H, (sat_value >> 8) & 0xff, 0x00);
	sonyimx134_write_reg(AE_SAT_REG_L, sat_value & 0xff, 0x00);
	sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_get_hdr_movie_ae_param;
 * Description : The ae arith in HAL get init parm from sensor by this interface.
 * Input       : the space of hdr_ae_constant_param for keeping ratio,max gain,min gain and vts;
 * Output      : the value of ratio,max gain,min gain and vts;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
#if 0
int  sonyimx134_get_hdr_movie_ae_param(hdr_ae_constant_param * hdr_ae_param)
{
	if(NULL != hdr_ae_param)
	{
		hdr_ae_param->hdr_ae_ratio 		= sonyimx134_sensor.ae_hdr_ratio;
		hdr_ae_param->sensor_max_gain	= sonyimx134_sensor.sensor_max_gain;
		hdr_ae_param->sensor_min_gain	= sonyimx134_sensor.sensor_min_gain;
		hdr_ae_param->max_analog_gain	= sonyimx134_sensor.sensor_max_analog_gain;
	}
	return 0;
}
#endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_set_digital_gain;
 * Description : set digital gain to sensor's digital registers
 * Input       : the struct of digital_gain_st saving digital value
 * Output      : NA
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
#if 0
void sonyimx134_set_digital_gain(digital_gain_st * digital_gain)
{
	u8 digital_gain_h = digital_gain->digital_gain_h;
	u8 digital_gain_l = digital_gain->digital_gain_l;
	if(_IS_DEBUG_AE)
	{
	       print_info("Enter %s  digital_gain_h = %d ,digital_gain_l=%d", __func__,digital_gain_h,digital_gain_l);
	}
	sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
	sonyimx134_write_reg(DIG_GAIN_GR_H, digital_gain_h, 0x00);
	sonyimx134_write_reg(DIG_GAIN_GR_L, digital_gain_l, 0x00);
	sonyimx134_write_reg(DIG_GAIN_R_H, digital_gain_h, 0x00);
	sonyimx134_write_reg(DIG_GAIN_R_L, digital_gain_l, 0x00);
	sonyimx134_write_reg(DIG_GAIN_B_H,digital_gain_h, 0x00);
	sonyimx134_write_reg(DIG_GAIN_B_L, digital_gain_l, 0x00);
	sonyimx134_write_reg(DIG_GAIN_GB_H, digital_gain_h, 0x00);
	sonyimx134_write_reg(DIG_GAIN_GB_L,digital_gain_l, 0x00);
	sonyimx134_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
}
#endif

 /*
  *************************************************************************
  * FunctionName: 	:sonyimx134_get_digital_gain;
  * Description 	: get digital gain from sensor's digital registers
  * Input			: the struct of digital_gain_st for storging digital value
  * Output			: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
#if 0
void sonyimx134_get_digital_gain(digital_gain_st * digital_gain)
{
	u8 digital_gain_h = 0;
	u8 digital_gain_l  = 0;
	sonyimx134_read_reg(DIG_GAIN_GR_H, &digital_gain_h);
	sonyimx134_read_reg(DIG_GAIN_GR_L, &digital_gain_l);
	sonyimx134_read_reg(DIG_GAIN_R_H, &digital_gain_h);
	sonyimx134_read_reg(DIG_GAIN_R_L, &digital_gain_l);
	sonyimx134_read_reg(DIG_GAIN_B_H,&digital_gain_h);
	sonyimx134_read_reg(DIG_GAIN_B_L, &digital_gain_l);
	sonyimx134_read_reg(DIG_GAIN_GB_H, &digital_gain_h);
	sonyimx134_read_reg(DIG_GAIN_GB_L,&digital_gain_l);


	digital_gain->digital_gain_h = digital_gain_h;
	digital_gain->digital_gain_l = digital_gain_l;
}
#endif

  /*
  *************************************************************************
  * FunctionName: 	:sonyimx134_check_zoom_limit
  * Description 	: check zoom limit for zoom problem for isp defect
  * Input			: zoom value
  * Output		: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
  #if 0
 int sonyimx134_check_zoom_limit(u32 *zoom)
 {
	if(zoom == NULL)
	{
		return -1;
	}
	if(*zoom < SONYIMX134_ISP_ZOOM_LIMIT && *zoom  > 0)
	{
	       *zoom = SONYIMX134_ISP_ZOOM_LIMIT;
	}
	return 0;
 }
 #endif

/*
 **************************************************************************
 * FunctionName: sonyimx134_reset;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_reset(camera_power_state power_state)
{
	print_debug("%s  \n", __func__);

	if (POWER_ON == power_state) {
		k3_isp_io_enable_mclk(MCLK_ENABLE, sonyimx134_sensor.sensor_index);
		udelay(100);
		k3_ispgpio_reset_sensor(sonyimx134_sensor.sensor_index, power_state,
			      sonyimx134_sensor.power_conf.reset_valid);
		udelay(500);
	} else {
		k3_ispgpio_reset_sensor(sonyimx134_sensor.sensor_index, power_state,
			      sonyimx134_sensor.power_conf.reset_valid);
		udelay(10);
		k3_isp_io_enable_mclk(MCLK_DISABLE, sonyimx134_sensor.sensor_index);
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_init;
 * Description : sonyimx134 init function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : Error code indicating success or failure;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx134_init(void)
{
	static bool sonyimx134_check = false;
	print_debug("%s  ", __func__);

	if (false == sonyimx134_check) {
		if (video_check_suspensory_camera("sonyimx134_sensor") != 1) {
			print_error("%s: product not have this sensor", __func__);
			return -ENODEV;
		}
		sonyimx134_check = true;
	}
	if (!camera_timing_is_match(0)) {
		print_error("%s: sensor timing don't match.\n", __func__);
		return -ENODEV;
	}

	if (sonyimx134_sensor.owner && !try_module_get(sonyimx134_sensor.owner)) {
		print_error("%s: try_module_get fail", __func__);
		return -ENOENT;
	}

	if(CAMERA_SENSOR_FLIP_TYPE_H_V == video_get_primary_sensor_flip_type())
		sonyimx134_sensor.sensor_rgb_type = SENSOR_BGGR;
	else
		sonyimx134_sensor.sensor_rgb_type = SENSOR_RGGB;

	print_info("%s, board type=%d.", __func__, video_get_board_type());

	if(VIDEO_BOARD_TYPE_SFT == video_get_board_type()){
	}else{
	    /* for ASIC platform */
	    /* 1. M_CAMERA_IO_VDD and S_CAMERA_IO_VDD have the same power.
	       2. Only power on one sensor cause leakage, so pri-sensor and sec-sensor
	          power on at the same time. Then pull down sec-sensor's PWDN/RESET GPIO for low power.
	    */
		sonyimx134_sensor.old_flip = 0;
		k3_ispio_power_init(M_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - pri camera*/
		k3_ispio_power_init(M_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);		/*IO 1.8V - pri camera*/
		k3_ispio_power_init(M_CAMERA_VCM_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*AF 2.85V - pri camera*/
		k3_ispio_power_init(M_CAMERA_CORE_VDD, LDO_VOLTAGE_10V, LDO_VOLTAGE_10V);	/*core 1.05V - pri camera*/
		
		k3_ispio_power_init(S_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - sec camera*/
		k3_ispio_power_init(S_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);		/*IO 1.8V - sec camera*/
		k3_ispio_power_init(S_CAMERA_CORE_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);	/*core 1.8V - sec camera*/

	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_exit;
 * Description : sonyimx134 exit function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx134_exit(void)
{
	print_debug("enter %s", __func__);

	k3_ispio_power_deinit();

	if (sonyimx134_sensor.owner) {
		module_put(sonyimx134_sensor.owner);
	}
	print_debug("exit %s", __func__);
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_shut_down;
 * Description : sonyimx134 shut down function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx134_shut_down(void)
{
	print_debug("enter %s", __func__);
	k3_ispgpio_power_sensor(&sonyimx134_sensor, POWER_OFF);
}

#ifdef IMX134_OTP
int sonyimx134_read_otp(u8 i2c_addr,u16 reg,u8 *buf,u16 count)
{
	u16 i;
	int ret;
	u16 val = 0;
	for(i=0;i<count;i++)
	{
		ret =ispv1_read_sensor_byte_addr8(sonyimx134_sensor.i2c_config.index,i2c_addr,reg+i,&val,sonyimx134_sensor.i2c_config.val_bits);
		if(ret !=0)
			print_error("sonyimx134_read_otp  %d\n",ret);
		buf[i] = (val&0xff);
		OTPSUMVAL +=buf[i];
	}
	return 0;
}

static bool sonyimx134_otp_read_id(void)
{
	u8 buf[5];
	u8 vendor_id =0;
	u8 module_type = MODULE_UNSUPPORT;

	print_debug("enter %s", __func__);

	if((sonyimx134_otp_flag & SONYIMX134_OTP_ID_READ) ==SONYIMX134_OTP_ID_READ)//we think OTP data is not correct at all
	{
		print_debug("%s OTP ID data is read allread!!!\n",__func__);
		return true;
	}

	sonyimx134_read_otp(OTP_ID_AWB,OTP_ID_REG,buf,5);

	print_debug("module info year 20%02d month %d day %d, SNO. 0x%x  vendor id&version 0x%x\n",
		buf[0],buf[1],buf[2],buf[3],buf[4]);

	vendor_id = buf[4]>>4;
	if(vendor_id ==0x01) //sunny
	{
		module_type = MODULE_SUNNY;
	}

	if(vendor_id == 0x03) //Liteon
	{
		module_type = MODULE_LITEON;
	}

	if(sensor_module == module_type)
	{
		sonyimx134_otp_flag |= SONYIMX134_OTP_ID_READ;
	}
	else
	{
		print_error("%s OTP data is worng!!!\n",__func__);
		return false;
	}
	return true;
}


static bool sonyimx134_otp_read_awb(void)
{
	u8 buf[6];
	//u16 i;

	print_debug("enter %s", __func__);
	if((sonyimx134_otp_flag & SONYIMX134_OTP_ID_READ) ==0)//we think OTP data is not correct at all
	{
		print_error("%s OTP data is worng!!!\n",__func__);
		return false;
	}

	if((sonyimx134_otp_flag & SONYIMX134_OTP_AWB_READ) ==SONYIMX134_OTP_AWB_READ)//we think OTP data is not correct at all
	{
		print_debug("%s OTP AWB data is read allread!!!\n",__func__);
		return true;
	}

	sonyimx134_read_otp(OTP_ID_AWB,OTP_AWB_REG,buf,6);
	//for(i=0;i<6;i++)
	//{
	//	print_debug("awb otp data[%d]=%x\n",i,buf[i]);
	//}
	sonyimx134_otp_flag |= SONYIMX134_OTP_AWB_READ;
	return true;
}

static bool sonyimx134_otp_read_lsc(void)
{
	print_debug("enter %s", __func__);
	if((sonyimx134_otp_flag & SONYIMX134_OTP_ID_READ) ==0)//we think OTP data is not correct at all
	{
		print_error("%s OTP data is worng!!!\n",__func__);
		return false;
	}

	if((sonyimx134_otp_flag & SONYIMX134_OTP_LSC_READ) ==SONYIMX134_OTP_LSC_READ)//we think OTP data is not correct at all
	{
		print_debug("%s OTP LSC data is read allread!!!\n",__func__);
		return true;
	}

	memset(sonyimx134_otp_lsc_param, 0, SONYIMX134_OTP_LSC_SIZE);
	//LSC 0xa4:0b--0xff  / 0xa6:00--0x22  total = 280
	sonyimx134_read_otp(OTP_LSC_1,OTP_LSC_1_REG,sonyimx134_otp_lsc_param,0xff-0x0b+1);
	sonyimx134_read_otp(OTP_LSC_2,OTP_LSC_2_REG,&sonyimx134_otp_lsc_param[0xff-0x0b+1],0x22+1);

	print_debug("%s LCS[0]= %x,LSC[247] = %x  LSC[248]=%x,LSC[279]=%d\n",__func__,
		sonyimx134_otp_lsc_param[0],sonyimx134_otp_lsc_param[247],sonyimx134_otp_lsc_param[248],sonyimx134_otp_lsc_param[279]);
	sonyimx134_otp_flag |= SONYIMX134_OTP_LSC_READ;
	return true;
}


/****************************************************************************
* FunctionName: sonyimx134_otp_set_lsc;
* Description : Set lens shading parameters to sensor registers.; cost time is 0.0341s on sunny module
* Input       : NA;
* Output      : NA;
* ReturnValue : bool;
* Other       : NA;
***************************************************************************/
static bool sonyimx134_otp_set_lsc(void)
{
	u8 *pval = NULL;
	int i = 0;

	print_debug("enter %s\n", __func__);

	/* Lens shading parameters are burned OK. */
	if((sonyimx134_otp_flag & SONYIMX134_OTP_LSC_READ) ==0)
	{
		print_error("%s OTP data is worng!!!\n",__func__);
		return false;
	}
	pval = sonyimx134_otp_lsc_param;
	/* Write lens shading parameters to sensor registers. */
	for (i=0; i<SONYIMX134_OTP_LSC_SIZE; i++)
	{
		sonyimx134_write_reg(SONYIMX134_SENSOR_LSC_RAM+i, *(pval+i), 0x00);
		print_debug("LSC[%d] = %d  \n",i,*(pval+i));
	}
	print_debug("%s, set OTP LSC to sensor OK.\n", __func__);

	return true;
}


/****************************************************************************
* FunctionName: sonyimx134_otp_enable_lsc;
* Description : Enable LSC correct.;
* Input       : bool;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static bool sonyimx134_otp_enable_lsc(bool enable)
{
	u8 lscMode = 0x00;
	u8 selToggle = 0x00;
	u8 lscEnable = 0x00;

	print_debug("enter %s", __func__);
	if((sonyimx134_otp_flag & SONYIMX134_OTP_LSC_READ) ==0)
	{
		print_error("%s OTP data is worng!!!\n",__func__);
		return false;
	}
	/* Open OTP lsc mode */
	if (enable) {
		lscMode = 0x01;
		selToggle = 0x01;
		lscEnable = 0x1F;
		print_debug("%s, OTP LSC enabled!", __func__);
	}
	sonyimx134_write_reg(SONYIMX134_SENSOR_LSC_EN, lscEnable, 0x00);
	sonyimx134_write_reg(SONYIMX134_SENSOR_LSC_MODE, lscMode, 0x00);
	sonyimx134_write_reg(SONYIMX134_SENSOR_RAM_SEL, selToggle, 0x00);

	return true;
}

/****************************************************************************
* FunctionName: sonyimx134_otp_read_vcm;
* Description : Get AF motor parameters from OTP.;
* Input       : NA;
* Output      : NA;
* ReturnValue : bool;
* Other       : NA;
***************************************************************************/
static bool sonyimx134_otp_read_vcm(void)
{
	u8 buf[4];
    u16 start_code,end_code;

	print_debug("enter %s", __func__);
	if((sonyimx134_otp_flag & SONYIMX134_OTP_ID_READ) ==0)//we think OTP data is not correct at all
	{
		print_error("%s OTP data is worng!!!\n",__func__);
		return false;
	}

	if((sonyimx134_otp_flag & SONYIMX134_OTP_VCM_READ) ==SONYIMX134_OTP_VCM_READ)//we think OTP data is not correct at all
	{
		print_debug("%s OTP VCM data is read allread!!!\n",__func__);
		return true;
	}

	sonyimx134_read_otp(OTP_VCM,OTP_VCM_REG,buf,4);
	print_debug("raw buf_vcm[0]= %x, buf_vcm[1] = %x buf_vcm[2] = %x buf_vcm[3] = %x\n",buf[0],buf[1],buf[2],buf[3]);

	sonyimx134_otp_flag |= SONYIMX134_OTP_VCM_READ;
	start_code = buf[0];
	start_code <<= 8;
	start_code +=buf[1];
	end_code = buf[2];
	end_code <<= 8;
	end_code += buf[3];

	if((start_code != end_code) &&(end_code>start_code))
	{
		/* VCM param is read  */
		sonyimx134_otp_flag |= SONYIMX134_OTP_VCM_READ;
		sonyimx134_vcm_start = start_code;
		sonyimx134_vcm_end = end_code;
		print_debug("sonyimx134_vcm_start= %x, sonyimx134_vcm_end = %x \n",sonyimx134_vcm_start,sonyimx134_vcm_end);
		return true;
	}
	else
	{
		print_error("%s VCM OTP data is worng!!!\n",__func__);
		return false;
	}
}
/****************************************************************************
* FunctionName: sonyimx134_otp_get_vcm;
* Description : Get vcm start and stop parameters read from OTP.;
* Input       : NA;
* Output      : vcm_start vcm_end
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static void sonyimx134_otp_get_vcm(u16 *vcm_start, u16 *vcm_end)
{
	_sonyimx134_otp_get_vcm(vcm_start, vcm_end,sonyimx134_sensor.vcm,sonyimx134_vcm_start,sonyimx134_vcm_end);
	print_debug("%s, start: %#x, end: %#x", __func__, *vcm_start, *vcm_end);
}
//this function time cost is about 0.0475s on sunny module
static void sonyimx134_get_otp_from_sensor(void)
{
	u8 sum;
	if((sonyimx134_otp_flag & SONYIMX134_OTP_CHECKSUM_ERR) ==SONYIMX134_OTP_CHECKSUM_ERR)
	{
		print_error("OTP data is worng!\n");
		return;
	}
	sonyimx134_otp_read_id();
	sonyimx134_otp_read_awb();
	sonyimx134_otp_read_vcm();
	sonyimx134_otp_read_lsc();//cost 0.042996s on sunny module

	if((sonyimx134_otp_flag & SONYIMX134_OTP_CHECKSUM_READ) ==SONYIMX134_OTP_CHECKSUM_READ)
	{
		print_debug("%s OTP checksum data is read allread!!!\n",__func__);
		return ;
	}

	sonyimx134_read_otp(OTP_CHECKSUM,OTP_CHECKSUM_REG,&OTPCHECKSUMVAL,1);
	sonyimx134_read_otp(OTP_CHECKSUM,OTP_CHECKSUM_FLAG_REG,&OTPCHECKSUMFLAG,1);

	sum = (OTPSUMVAL - OTPCHECKSUMVAL-OTPCHECKSUMFLAG)%0xff;

	print_debug("%s, OTPSUMVAL: %d, OTPCHECKSUMVAL: %d ,sum:%d, OTPCHECKSUMFLAG =%x \n", __func__, OTPSUMVAL, OTPCHECKSUMVAL,sum,OTPCHECKSUMFLAG);

	/*
	*the value for OTPCHECKSUMFLAG shoule be one of them
	*1.0xa5 means checksum enabel
	*2.0xff  means checksum disable
	*3. other means write or read OTP have error or otp data is writend by mistake
	*/
	if(((OTPCHECKSUMVAL==sum)&&(OTPCHECKSUMFLAG ==OTPCHECKSUM_FLAG))
		||(OTPCHECKSUMFLAG ==0xff))
	{
		sonyimx134_otp_flag |= SONYIMX134_OTP_CHECKSUM_READ;
	}
	else
	{
		sonyimx134_otp_flag = SONYIMX134_OTP_CHECKSUM_ERR;
		sonyimx134_vcm_start = 0;
		sonyimx134_vcm_end = 0;
		print_error("OTP checksum is worng!\n");
	}
}
#endif

  /*
  *************************************************************************
  * FunctionName: 	: sonyimx134_set_dpc_funciton;
  * Description 	: set dpc register to isp and sensor according to iso
  * Input			: the struct of _sensor_reg_t for storging sensor register
  * address and value, iso is used for differentiating dpc strong and weak, size is
  * used for keeping the size of  dpc_reg array.
  * Output			: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */
#if 0
 int sonyimx134_set_dpc_funciton(struct _sensor_reg_t *dpc_reg,u32 iso,u16 * size)
 {
	print_info("%s,iso=%d",__func__,iso);
	int isp_dpc_size = 0;
	if(dpc_reg == NULL|| size == NULL)
	{
		return -1;
	}
	dpc_reg->subaddr = 0x4100;
	if(iso > SONYIMX134_DPC_THRESHOLD_ISO)
	{
		dpc_reg->value	  = 0xF8;
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
		sonyimx134_write_isp_seq(isp_dpc_reg, isp_dpc_size);
	}
	else
	{
		dpc_reg->value	  = 0xE8;
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
		sonyimx134_write_isp_seq(isp_dpc_reg, isp_dpc_size);
	}
	*size = 1;

	return 0;
 }
#endif
#if 0
static void sonyimx134_config_dphy_clk(camera_state state)
{
	u8 lane_clk;
	
	if (state == STATE_PREVIEW) {
		lane_clk =sonyimx134_sensor.frmsize_list[sonyimx134_sensor.preview_frmsize_index] .lane_clk;
	} else {
		lane_clk =sonyimx134_sensor.frmsize_list[sonyimx134_sensor.capture_frmsize_index] .lane_clk;
	}

	print_info("%s lane_clk = 0x%x state = %d",__func__, lane_clk, state);
	k3_ispio_config_lane_clk(sonyimx134_sensor.mipi_index, sonyimx134_sensor.mipi_lane_count, lane_clk);
}
#endif
/*
 **************************************************************************
 * FunctionName: sonyimx134_set_default;
 * Description : init sonyimx134_sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx134_set_default(void)
{
	sonyimx134_sensor.init = sonyimx134_init;
	sonyimx134_sensor.exit = sonyimx134_exit;
	sonyimx134_sensor.shut_down = sonyimx134_shut_down;
	sonyimx134_sensor.reset = sonyimx134_reset;
	sonyimx134_sensor.check_sensor = sonyimx134_check_sensor;
	sonyimx134_sensor.power = sonyimx134_power;
	sonyimx134_sensor.init_reg = sonyimx134_init_reg;
	sonyimx134_sensor.stream_on = sonyimx134_stream_on;

	sonyimx134_sensor.get_format = sonyimx134_get_format;
	sonyimx134_sensor.set_flash = NULL;
	sonyimx134_sensor.get_flash = NULL;
	sonyimx134_sensor.set_scene = NULL;
	sonyimx134_sensor.get_scene = NULL;

	sonyimx134_sensor.enum_framesizes = sonyimx134_enum_framesizes;
	sonyimx134_sensor.try_framesizes = sonyimx134_try_framesizes;
	sonyimx134_sensor.set_framesizes = sonyimx134_set_framesizes;
	sonyimx134_sensor.get_framesizes = sonyimx134_get_framesizes;

	sonyimx134_sensor.enum_frame_intervals = sonyimx134_enum_frame_intervals;
	sonyimx134_sensor.try_frame_intervals = NULL;
	sonyimx134_sensor.set_frame_intervals = NULL;
	sonyimx134_sensor.get_frame_intervals = NULL;

	sonyimx134_sensor.get_vts_reg_addr = sonyimx134_get_vts_reg_addr;

	sonyimx134_sensor.get_capability = sonyimx134_get_capability;

	sonyimx134_sensor.set_hflip = sonyimx134_set_hflip;
	sonyimx134_sensor.get_hflip = sonyimx134_get_hflip;
	sonyimx134_sensor.set_vflip = sonyimx134_set_vflip;
	sonyimx134_sensor.get_vflip = sonyimx134_get_vflip;
	sonyimx134_sensor.update_flip = sonyimx134_update_flip;

	strcpy(sonyimx134_sensor.info.name,"sonyimx134");
	sonyimx134_sensor.interface_type = MIPI1;
	sonyimx134_sensor.mipi_lane_count = CSI_LINES_4;
	sonyimx134_sensor.mipi_index = CSI_INDEX_0;
	sonyimx134_sensor.sensor_index = CAMERA_SENSOR_PRIMARY;
	sonyimx134_sensor.skip_frames = 2;

	sonyimx134_sensor.power_conf.pd_valid = LOW_VALID;
	sonyimx134_sensor.power_conf.reset_valid = LOW_VALID;
	sonyimx134_sensor.power_conf.vcmpd_valid = LOW_VALID;

	sonyimx134_sensor.i2c_config.index = I2C_PRIMARY;
	sonyimx134_sensor.i2c_config.speed = I2C_SPEED_400;
	sonyimx134_sensor.i2c_config.addr = SONYIMX134_SLAVE_ADDRESS;
	sonyimx134_sensor.i2c_config.addr_bits = I2C_16BIT;
	sonyimx134_sensor.i2c_config.val_bits = I2C_8BIT;

	sonyimx134_sensor.preview_frmsize_index = 0;
	sonyimx134_sensor.capture_frmsize_index = 0;
	sonyimx134_sensor.frmsize_list = sonyimx134_framesize_resource[framesizes_index].frmsize_list;
	sonyimx134_sensor.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW10;
	sonyimx134_sensor.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW10;

#ifdef SONYIMX134_AP_WRITEAE_MODE /* just an example and test case for AP write AE mode */
	sonyimx134_sensor.aec_addr[0] = 0;
	sonyimx134_sensor.aec_addr[1] = 0;
	sonyimx134_sensor.aec_addr[2] = 0;
	sonyimx134_sensor.agc_addr[0] = 0;
	sonyimx134_sensor.agc_addr[1] = 0;
	sonyimx134_sensor.ap_writeAE_delay = 6000; /* 5 expo and gain registers, 6000 us is enough */
#else
	sonyimx134_sensor.aec_addr[0] = 0x0000;
	sonyimx134_sensor.aec_addr[1] = 0x0202;
	sonyimx134_sensor.aec_addr[2] = 0x0203;
	sonyimx134_sensor.agc_addr[0] = 0x0000; /*0x0204 high byte not needed*/
	sonyimx134_sensor.agc_addr[1] = 0x0205;
#endif
	sonyimx134_sensor.sensor_type = SENSOR_SONY;
	sonyimx134_sensor.sensor_rgb_type = SENSOR_RGGB;

	sonyimx134_sensor.set_gain = sonyimx134_set_gain;
	sonyimx134_sensor.set_exposure = sonyimx134_set_exposure;
	sonyimx134_sensor.set_exposure_gain = sonyimx134_set_exposure_gain;
	sonyimx134_sensor.set_vts = sonyimx134_set_vts;
#if 0
	sonyimx134_sensor.construct_vts_reg_buf =sonyimx134_construct_vts_reg_buf;
#endif

	sonyimx134_sensor.get_override_param = sonyimx134_get_override_param;
#if 0
	sonyimx134_sensor.get_af_param = sonyimx134_get_af_param;
	sonyimx134_sensor.fill_denoise_buf = sonyimx134_fill_denoise_buf;
#endif

	sonyimx134_sensor.sensor_gain_to_iso = sonyimx134_gain_to_iso;
	sonyimx134_sensor.sensor_iso_to_gain = sonyimx134_iso_to_gain;

	sonyimx134_sensor.get_sensor_aperture = sonyimx134_get_sensor_aperture;
	sonyimx134_sensor.get_equivalent_focus = NULL;

	sonyimx134_sensor.set_effect = NULL;

	sonyimx134_sensor.isp_location = CAMERA_USE_K3ISP;
	sonyimx134_sensor.sensor_tune_ops = NULL;

	sonyimx134_sensor.af_enable = 1;
	sonyimx134_sensor.vcm = &vcm_dw9714;
	sonyimx134_sensor.get_flash_awb = sonyimx134_get_flash_awb;

	sonyimx134_sensor.image_setting.lensc_param = sonyimx134_lensc_param;
	sonyimx134_sensor.image_setting.ccm_param = sonyimx134_ccm_param;
	sonyimx134_sensor.image_setting.awb_param = sonyimx134_awb_param;
	if(VIDEO_BOARD_TYPE_SFT == video_get_board_type()){
		sonyimx134_sensor.fps_max = 30;
		sonyimx134_sensor.fps_min = 1;
		sonyimx134_sensor.fps = 3;

	}else{
		sonyimx134_sensor.fps_max = 30;
		sonyimx134_sensor.fps_min = 15;
		sonyimx134_sensor.fps = 25;
	}

	sonyimx134_sensor.owner = THIS_MODULE;

	sonyimx134_sensor.info.facing = CAMERA_FACING_BACK;
	sonyimx134_sensor.info.orientation = 270;
	sonyimx134_sensor.info.focal_length = 296;	/* 2.96mm */
	sonyimx134_sensor.info.h_view_angle = 75;	/*  66.1 degree */
	sonyimx134_sensor.info.v_view_angle = 75;
	if(VIDEO_BOARD_TYPE_SFT == video_get_board_type()){
		sonyimx134_sensor.lane_clk = CLK_100M;//CLK_400M;

	}else{
		sonyimx134_sensor.lane_clk = CLK_750M;	
	}
	sonyimx134_sensor.hflip = 0;
	sonyimx134_sensor.vflip = 0;
	sonyimx134_sensor.old_flip = 0;

#if 0
		//modiy format
	// for HDR movie funtion
	sonyimx134_sensor.set_awb_gain 				= sonyimx134_set_awb_gain;
	sonyimx134_sensor.set_hdr_exposure_gain 		= sonyimx134_set_hdr_exposure_gain;
	sonyimx134_sensor.set_atr_ctrl_points   		= sonyimx134_set_ATR_ctrl_points;
	sonyimx134_sensor.get_atr_ctrl_points 			= sonyimx134_get_ATR_ctrl_points;
	sonyimx134_sensor.hdr_regs_y 				= sonyimx134_hdr_regs_y;
	sonyimx134_sensor.set_ATR_switch     			= sonyimx134_set_ATR;
	sonyimx134_sensor.get_hdr_lux_matrix    		= sonyimx134_get_lux_matrix;
#endif
	sonyimx134_sensor.get_gain     				= sonyimx134_get_gain;
	sonyimx134_sensor.get_exposure   			= sonyimx134_get_exposure;
	sonyimx134_sensor.init_isp_reg 				= sonyimx134_init_isp_reg;
#if 0
	sonyimx134_sensor.support_hdr_movie			= sonyimx134_support_hdr_movie;
	sonyimx134_sensor.get_hdr_movie_switch		= sonyimx134_get_hdr_movie_switch;
	sonyimx134_sensor.set_hdr_movie_switch		= sonyimx134_set_hdr_movie_switch;
	sonyimx134_sensor.over_exposure_adjust		= sonyimx134_over_exposure_adjust;
	sonyimx134_sensor.set_lmt_sat 				= sonyimx134_set_lmt_sat;
	sonyimx134_sensor.get_hdr_movie_ae_param	= sonyimx134_get_hdr_movie_ae_param;
	sonyimx134_sensor.sensor_write_reg 			= sonyimx134_write_reg;
	sonyimx134_sensor.set_digital_gain			= sonyimx134_set_digital_gain;
	sonyimx134_sensor.get_digital_gain			= sonyimx134_get_digital_gain;

	sonyimx134_sensor.set_dpc_funciton 			= sonyimx134_set_dpc_funciton;
	sonyimx134_sensor.check_zoom_limit 			= sonyimx134_check_zoom_limit;

	//check default parameter
	sonyimx134_sensor.ae_hdr_ratio          			= 8;
	sonyimx134_sensor.hdrInfo.atr_on     			= ATR_ON;
	sonyimx134_sensor.sensor_max_gain			=32;
	sonyimx134_sensor.sensor_max_analog_gain       = 8;
	sonyimx134_sensor.sensor_min_gain			=1;
	sonyimx134_sensor.gain_switch 				= 100;//0x66
	sonyimx134_sensor.hdrInfo.hdr_on 			= HDR_MOVIE_OFF;//default atr on
#endif
#if 0
	sonyimx134_sensor.support_hw_lowlight		= sonyimx134_support_hw_lowlight;
	sonyimx134_sensor.hw_lowlight_on			= false;
#endif

	sonyimx134_sensor.support_summary		= false;
	sonyimx134_sensor.isp_idi_skip = false;
	
	sonyimx134_sensor.stream_off_setting = sonyimx134_stream_off_regs;
	sonyimx134_sensor.stream_off_setting_size = ARRAY_SIZE(sonyimx134_stream_off_regs);
	/*if there have different data rate of sensor resolution we need this config_dphy_clk 
	   otherwise if all resolution is same rate config_dphy_clk must to be null*/
	//sonyimx134_sensor.config_dphy_clk = sonyimx134_config_dphy_clk;
	sonyimx134_sensor.config_dphy_clk = NULL;

}

/*
 **************************************************************************
 * FunctionName: sonyimx134_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int sonyimx134_module_init(void)
{
	framesizes_index = video_get_board_type() - 1;

	print_info("%s framesizes_index = %d",__func__, framesizes_index);
	sonyimx134_set_default();
	return register_camera_sensor(sonyimx134_sensor.sensor_index, &sonyimx134_sensor);
}

/*
 **************************************************************************
 * FunctionName: sonyimx134_module_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void __exit sonyimx134_module_exit(void)
{
	unregister_camera_sensor(sonyimx134_sensor.sensor_index, &sonyimx134_sensor);
}

MODULE_AUTHOR("Hisilicon");
module_init(sonyimx134_module_init);
module_exit(sonyimx134_module_exit);
MODULE_LICENSE("GPL");

/********************************** END **********************************************/
