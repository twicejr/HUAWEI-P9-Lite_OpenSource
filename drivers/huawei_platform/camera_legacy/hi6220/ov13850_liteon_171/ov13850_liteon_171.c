

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
//#include <mach/boardid.h>
//#include <mach/gpio.h>
#include "sensor_common.h"
#include "ov13850_liteon_171.h"
/*#include "../isp/k3_isp_io.h"*/
#include <asm/bug.h>
#include <linux/device.h>

#define LOG_TAG "OV13850_LIT171"
//#define DEBUG_DEBUG 1
#include "cam_log.h"


//#include "drv_regulator_user.h"
#include "video_config.h"


#define  OV13850_MAX_ISO 			1550
#define OV13850_MIN_ISO                      100

/* support 3 level framerate now, if mid fps same as min, set to 2 level framerate */
#define OV13850_AUTOFPS_GAIN_HIGH2MID		0x60
#define OV13850_AUTOFPS_GAIN_MID2LOW		    0x60
#define OV13850_AUTOFPS_GAIN_LOW2MID		    0x24
#define OV13850_AUTOFPS_GAIN_MID2HIGH		0x24

#define OV13850_MAX_FRAMERATE         30
#define OV13850_MID_FRAMERATE		 14
#define OV13850_MIN_FRAMERATE          14
#define OV13850_MIN_CAP_FRAMERATE  4
#define OV13850_FLASH_TRIGGER_GAIN 0xff

#define OV13850_SHARPNESS_PREVIEW  0x30
#define OV13850_SHARPNESS_CAPTURE  0x08

//#define GROUP_HOLD_FUNCTION_REG    0x3208

//slave add: write 0x20, read 0x21
#define OV13850_SLAVE_ADDRESS 0x20

//chip id
#define OV13850_CHIP_ID_REG_H       0x300a
#define OV13850_CHIP_ID_REG_L       0x300b
#define OV13850_CHIP_ID       0xd850

//mirror flip
#define OV13850_FLIP_REG		0x3820 //bit2
#define OV13850_MIRROR_REG		0x3821 //bit2

//aec and agc
#define OV13850_EXPOSURE_REG_H	0x3500
#define OV13850_EXPOSURE_REG_M	0x3501
#define OV13850_EXPOSURE_REG_L	0x3502

#define OV13850_GAIN_REG_H	0x350a
#define OV13850_GAIN_REG_L		0x350b

#define OV13850_VTS_REG_H		0x380e
#define OV13850_VTS_REG_L		0x380f

//#define OV13850_TEST_PATTERN	0x5e00

#define OV13850_APERTURE_FACTOR   200 //F2.0
//#define OV13850_EQUIVALENT_FOCUS	0

#define OV13850_ZSL_MODE            (0x00)

#define OV13850_I2C_RETRY_TIMES     3

#define OV13850_AP_WRITEAE_MODE


#define OV13850_ISO	(\
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

#ifdef OV13850_LIT171_OTP
static u16 RG_Ratio_Typical = 0x248;//average of the five golden samples with 23060167
static u16 BG_Ratio_Typical = 0x257;//average of the five golden samples with 23060167

//#define OV13850_OTP_READ_TIME_PRINT
#define OTP_SLAVE_ADDR1       0xa4
#define OTP_SLAVE_ADDR2       0xa6

#define OTP_ID_REG 		      0x00
#define OTP_AWB_REG 	      0x05
#define OTP_LSC_1_REG 	      0x0b
#define OTP_LSC_2_REG	      0x00
#define OTP_VCM_REG 	      0x73
#define OTP_CHECKSUM_REG      0x77

#define OV13850_OTP_ID_READ	       (1 << 0)
#define OV13850_OTP_VCM_READ       (1 << 1)
#define OV13850_OTP_LSC_READ       (1 << 2)
#define OV13850_OTP_AWB_READ       (1 << 3)
#define OV13850_OTP_CHECKSUM_READ  (1 << 4)
#define OV13850_OTP_CHECKSUM_ERR   (1 << 5)
#define OV13850_OTP_FAIL_FLAG      (1 << 6)

#define OV1385_MODULE_VENDOR_ID    0x03//LETION
#define OV1385_MODULE_HUAWEI_ID    0xAB//23060171
#define OV13850_OTP_LSC_SIZE       360

typedef struct ov13850_otp_struct_type {
	u16 rg_ratio;
	u16 bg_ratio;
	u16 grgb;
	u16 vcm_start;
	u16 vcm_end;
	u8  lsc[OV13850_OTP_LSC_SIZE];
}ov13850_otp_struct;

static ov13850_otp_struct ov13850_otp;

static u32 OTPSUMVAL         = 0;
static u8  ov13850_otp_flag  = 0;

extern int  ispv1_read_sensor_byte_addr8(i2c_index_t index, u8 i2c_addr, u16 reg, u16 *val, i2c_length length);
static bool ov13850_get_otp_from_sensor(void);
static void ov13850_otp_get_vcm(u16 *vcm_start, u16 *vcm_end);
static void ov13850_otp_set_lsc(void);
static void ov13850_otp_set_awb(void);
#endif
extern int k3_ispio_read_seq(i2c_index_t index,u8 i2c_addr,struct _sensor_reg_t *seq,u32 size,i2c_length length);

static camera_capability ov13850_cap[] = {
	{V4L2_CID_FLASH_MODE, THIS_FLASH},
	{V4L2_CID_FOCUS_MODE, THIS_FOCUS_MODE},
	{V4L2_CID_ISO, OV13850_ISO},
	{V4L2_CID_FOCAL_LENGTH, 379},
	{V4L2_CID_ZSL,OV13850_ZSL_MODE},
};

/*
 * should be calibrated, three lights, from 0x1c264
 * here is long exposure
 */
static char ov13850_lensc_param[86*3] = {
};

/* should be calibrated, 6 groups 3x3, from 0x1c1d8 */
static short ov13850_ccm_param[54] = {
};

static char ov13850_awb_param[] = {
};

static vcm_info_s vcm_dw9714a_param = {
    #include "vcm_dw9714_liteon.h"
};
static effect_params effect_ov13850_liteon = {
#include "effect_ov13850_liteon_g760s.h"
};

static awb_gain_t flash_platform_awb[] = {
	{0xbd, 0x80, 0x80, 0xdc},
};

static const struct _sensor_reg_t ov13850_stream_off_regs[] = {
	{0x0100, 0x00}
};
static framesize_s ov13850_framesizes[] = {
//2080x1560, 30fps
	{0, 0, 2080, 1560, 4736, 1728, 30, 30, 0x209, 0x1b2, 0x100, VIEW_FULL, RESOLUTION_4_3, false, false, {ov13850_framesize_quater, ARRAY_SIZE(ov13850_framesize_quater)}, CLK_500M},
//4160x3120, 10fps
	{0, 0, 4160, 3120, 7200, 3328, 10, 10, 0x156, 0x11e, 0xa8, VIEW_FULL, RESOLUTION_4_3, false, false, {ov13850_framesize_fullsize_nonzsl, ARRAY_SIZE(ov13850_framesize_fullsize_nonzsl)}, CLK_500M},

};
static camera_sensor ov13850_lit171;
static void ov13850_set_default(void);
static void ov13850_config_dphy_clk(camera_state state);

/*
 **************************************************************************
 * FunctionName: ov13850_read_reg;
 * Description : read ov13850 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_read_reg(u16 reg, u8 *val)
{
	return k3_ispio_read_reg(ov13850_lit171.i2c_config.index, ov13850_lit171.i2c_config.addr,
                reg, (u16*)val, ov13850_lit171.i2c_config.val_bits, ov13850_lit171.i2c_config.addr_bits );
}


/*
 **************************************************************************
 * FunctionName: ov13850_write_reg;
 * Description : write ov13850 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_write_reg(u16 reg, u8 val, u8 mask)
{
	return k3_ispio_write_reg(ov13850_lit171.i2c_config.index, ov13850_lit171.i2c_config.addr,
	reg, val, ov13850_lit171.i2c_config.val_bits, mask,  ov13850_lit171.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov13850_write_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ov13850_write_seq(const struct _sensor_reg_t *seq, u32 size, u8 mask)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	return k3_ispio_write_seq(ov13850_lit171.i2c_config.index, ov13850_lit171.i2c_config.addr,
                seq, size, ov13850_lit171.i2c_config.val_bits, mask,  ov13850_lit171.i2c_config.addr_bits);
}

/*
 **************************************************************************
 * FunctionName: ov13850_write_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ov13850_write_isp_seq(const struct isp_reg_t *seq, u32 size)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	k3_ispio_write_isp_seq(seq, size);
}


/*
 **************************************************************************
 * FunctionName: ov13850_enum_frame_intervals;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_enum_frame_intervals(struct v4l2_frmivalenum *fi)
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
 * FunctionName: ov13850_get_format;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_get_format(struct v4l2_fmtdesc *fmt)
{
	if (fmt->type == V4L2_BUF_TYPE_VIDEO_OVERLAY) {
		fmt->pixelformat = ov13850_lit171.fmt[STATE_PREVIEW];
	} else {
		fmt->pixelformat = ov13850_lit171.fmt[STATE_CAPTURE];
	}
	return 0;
}

static int ov13850_get_capability(u32 id, u32 *value)
{
	int i;
	for (i = 0; i < sizeof(ov13850_cap) / sizeof(ov13850_cap[0]); ++i) {
		if (id == ov13850_cap[i].id) {
			*value = ov13850_cap[i].value;
			break;
		}
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov13850_enum_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 max_index = ARRAY_SIZE(camera_framesizes) - 1;
	u32 this_max_index = ARRAY_SIZE(ov13850_framesizes) - 1;

	assert(framesizes);

	print_debug("enter %s; ", __func__);

	if (framesizes->index > max_index) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	if ((camera_framesizes[framesizes->index].width > ov13850_framesizes[this_max_index].width)
		|| (camera_framesizes[framesizes->index].height > ov13850_framesizes[this_max_index].height)) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	framesizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	framesizes->discrete.width = ov13850_framesizes[this_max_index].width;
	framesizes->discrete.height = ov13850_framesizes[this_max_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov13850_try_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_try_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	int max_index = ARRAY_SIZE(ov13850_framesizes) - 1;

	assert(framesizes);

	print_debug("Enter Function:%s  ", __func__);


	if ((framesizes->discrete.width <= ov13850_framesizes[max_index].width)
	    && (framesizes->discrete.height <= ov13850_framesizes[max_index].height)) {
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
 * FunctionName: ov13850_set_framesizes;
 * Description : NA;
 * Input       : flag: if 1, set framesize to sensor,
 *					   if 0, only store framesize to camera_interface;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_set_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type,bool zsl_preview)
{
	int i = 0;
	bool match = false;
	int size = 0;
	assert(fs);

	if(NULL == fs) {
		return -EINVAL;
	}
	print_info("Enter Function:%s State(%d), flag=%d, width=%d, height=%d",
		   __func__, state, flag, fs->width, fs->height);
	size = ARRAY_SIZE(ov13850_framesizes);

	if (VIEW_FULL == view_type) {
		for (i = 0; i < ARRAY_SIZE(ov13850_framesizes); i++) {
		    if ((zsl_preview == false) && ov13850_framesizes[i].zsl_only )
		    {
		        continue;
		    }
			if ((ov13850_framesizes[i].width >= fs->width)
			    && (ov13850_framesizes[i].height >= fs->height)
			    && (VIEW_FULL == ov13850_framesizes[i].view_type)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= ov13850_framesizes[i].resolution_type)) {
				fs->width = ov13850_framesizes[i].width;
				fs->height = ov13850_framesizes[i].height;
				match = true;
				break;
			}
		}
	}
	

	if (false == match) {
		for (i = 0; i < size; i++) {
		    if ((zsl_preview == false) && ov13850_framesizes[i].zsl_only)
		    {
		        continue;
		    }

			if ((ov13850_framesizes[i].width >= fs->width)
				    && (ov13850_framesizes[i].height >= fs->height)
				    && (camera_get_resolution_type(fs->width, fs->height)
				   <= ov13850_framesizes[i].resolution_type)) {
					fs->width = ov13850_framesizes[i].width;
					fs->height = ov13850_framesizes[i].height;
					break;
			}
		}
	}


	if (i >= ARRAY_SIZE(ov13850_framesizes)) {
		print_error("request resolution larger than sensor's max resolution");
		return -EINVAL;
	}

	if (state == STATE_PREVIEW) {
		ov13850_lit171.preview_frmsize_index = i;
	} else {
		ov13850_lit171.capture_frmsize_index = i;
	}
	print_info("Enter Function:%s  preview index =%d, capture=%d ", __func__, ov13850_lit171.preview_frmsize_index, ov13850_lit171.capture_frmsize_index);
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov13850_get_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_get_framesizes(camera_state state,
				     struct v4l2_frmsize_discrete *fs)
{
	int frmsize_index;

	assert(fs);

	if (state == STATE_PREVIEW) {
		frmsize_index = ov13850_lit171.preview_frmsize_index;
	} else if (state == STATE_CAPTURE) {
		frmsize_index = ov13850_lit171.capture_frmsize_index;
	} else {
		return -EINVAL;
	}
	fs->width = ov13850_framesizes[frmsize_index].width;
	fs->height = ov13850_framesizes[frmsize_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov13850_init_isp_reg;
 * Description : load initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_init_isp_reg(void)
{
	int size = 0;
	camera_sensor *sensor = &ov13850_lit171;

	size = CAMERA_MAX_SETTING_SIZE;
	ov13850_write_isp_seq(sensor->effect->isp_settings, size);
	return 0;
}


/*
 **************************************************************************
 * FunctionName: ov13850_init_reg;
 * Description : download initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_init_reg(void)
{
	int size = 0;

	print_debug("Enter Function:%s  , initsize=%d",
		    __func__, sizeof(ov13850_init_regs));

	if (0 != k3_ispio_init_csi(ov13850_lit171.mipi_index,
			ov13850_lit171.mipi_lane_count, ov13850_lit171.lane_clk)) {
		return -EFAULT;
	}

	ov13850_write_reg(0x0103, 0x01, 0x00);
	mdelay(5);

	size = ARRAY_SIZE(ov13850_init_regs);
	if (0 != ov13850_write_seq(ov13850_init_regs, size, 0x00)) {
		print_error("line %d, fail to init ov13850 sensor",__LINE__);
		return -EFAULT;
	}

#ifdef OV13850_LIT171_OTP
	if((ov13850_otp_flag & OV13850_OTP_FAIL_FLAG) != OV13850_OTP_FAIL_FLAG){
	    ov13850_otp_set_lsc();
	    ov13850_otp_set_awb();
	}
#endif
	return 0;
}

static int ov13850_set_hflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);
	ov13850_lit171.hflip = flip;
	return 0;
}
static int ov13850_get_hflip(void)
{
	print_debug("enter %s", __func__);

	return ov13850_lit171.hflip;
}
static int ov13850_set_vflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);

	ov13850_lit171.vflip = flip;

	return 0;
}
static int ov13850_get_vflip(void)
{
	print_debug("enter %s", __func__);
	return ov13850_lit171.vflip;
}

 
static int ov13850_update_flip(u16 width, u16 height)
{
	u8 new_flip = ((ov13850_lit171.vflip << 1) | ov13850_lit171.hflip);
 
	print_debug("Enter %s  ", __func__);
	if(ov13850_lit171.old_flip != new_flip) 
	{

		k3_ispio_update_flip((ov13850_lit171.old_flip ^ new_flip) & 0x03, width, height, PIXEL_ORDER_NO_CHANGED);

		ov13850_lit171.old_flip = new_flip;

 		ov13850_write_reg(OV13850_FLIP_REG, ov13850_lit171.vflip ? 0x04 : 0x00,  ~0x04);
		ov13850_write_reg(OV13850_MIRROR_REG, ov13850_lit171.hflip ? 0x00 : 0x04, ~0x04);

	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov13850_framesize_switch;
 * Description : switch frame size, used by preview and capture
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_framesize_switch(camera_state state)
{
	u8 next_frmsize_index;

	if (state == STATE_PREVIEW)
		next_frmsize_index = ov13850_lit171.preview_frmsize_index;
	else
		next_frmsize_index = ov13850_lit171.capture_frmsize_index;

	print_debug("Enter Function:%s frm index=%d", __func__, next_frmsize_index);

	if (next_frmsize_index >= ARRAY_SIZE(ov13850_framesizes)){
		print_error("Unsupport sensor setting index: %d",next_frmsize_index);
		return -ETIME;
	}

	if (0 != ov13850_write_seq(ov13850_lit171.frmsize_list[next_frmsize_index].sensor_setting.setting
		,ov13850_lit171.frmsize_list[next_frmsize_index].sensor_setting.seq_size, 0x00)) {
		print_error("fail to init ov13850 sensor");
		return -ETIME;
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov13850_stream_on;
 * Description : download preview seq for sensor preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_stream_on(camera_state state)
{
	print_debug("Enter Function:%s ", __func__);
	ov13850_config_dphy_clk(state);
	return ov13850_framesize_switch(state);
}

/*  **************************************************************************
* FunctionName: ov13850_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int ov13850_check_sensor(void)
{
	u8 idl = 0, idh = 0;
	u16 id = 0;
	bool retVal = false;
	camera_sensor *sensor = &ov13850_lit171;
	int retry = 0;

	for (retry = 0; retry <OV13850_I2C_RETRY_TIMES; retry++)
	{
		ov13850_read_reg(OV13850_CHIP_ID_REG_H, &idh);
		ov13850_read_reg(OV13850_CHIP_ID_REG_L, &idl);

		id = ((idh << 8) | idl);
		print_info("ov13850 product id:0x%x, retry times:%d", id, retry);
		if (OV13850_CHIP_ID == id)
		{
			break;
		}
		udelay(100);
	}

	if (OV13850_CHIP_ID != id) {
		print_error("Invalid product id ,Could not load sensor ov13850\n");
		return -ENODEV;
	}

	ov13850_lit171.vcm = &vcm_dw9714a_param;
       sensor->effect = &effect_ov13850_liteon;
	//strncpy(ov13850_lit171.info.name, "ov13850_liteon", sizeof(ov13850_lit171.info.name));

#ifdef OV13850_LIT171_OTP
	retVal = ov13850_get_otp_from_sensor();
    if(true != retVal){
		print_error("%s~~~~~~ov13850_get_otp_from_sensor() return false for OTP FAIL\n",__func__);
	}
	ov13850_lit171.vcm->get_vcm_otp = ov13850_otp_get_vcm;
#endif

	return 0;
}


/****************************************************************************
* FunctionName: ov13850_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int ov13850_power(camera_power_state power)
{
	int ret = 0;

	print_debug("Enter Function:%s\n ", __func__);


	if (power == POWER_ON) {

		k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);

		k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
		udelay(1);
		k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);
		udelay(200);

		k3_ispio_ioconfig(&ov13850_lit171, power);
		k3_ispgpio_power_sensor(&ov13850_lit171, power);
		msleep(3);

	} else {
		k3_ispio_deinit_csi(ov13850_lit171.mipi_index);

		k3_ispgpio_power_sensor(&ov13850_lit171, power);
		k3_ispio_ioconfig(&ov13850_lit171, power);

		k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);
		udelay(200);
		k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);
		udelay(500);
	}

	return ret;
}

static int ov13850_get_sensor_aperture(void)
{
	return OV13850_APERTURE_FACTOR;
}

/*
 * Here gain is in unit 1/16 of sensor gain,
 * y36721 todo, temporarily if sensor gain=0x10, ISO is 100
 * in fact we need calibrate an ISO-ET-gain table.
 */
static u32 ov13850_gain_to_iso(int gain)
{
	return (u32)((gain * 100) / 0x10);
}

static u32 ov13850_iso_to_gain(int iso)
{
	return (u32)((iso * 0x10) / 100);
}

static void ov13850_set_gain(u32 gain)
{
	if (gain == 0)
	{
		return;//wrong gain
	}
	else if (gain > 0xf8) //0xf8 = 15.5 * 0x10
	{
		gain = 0xf8;//max gain is 15.5
	}

	ov13850_write_reg(OV13850_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	ov13850_write_reg(OV13850_GAIN_REG_L, gain & 0xff, 0x00);
}

static void ov13850_set_exposure(u32 exposure)
{
	ov13850_write_reg(OV13850_EXPOSURE_REG_H, (exposure >> 16) & 0x0f, 0x00);
	ov13850_write_reg(OV13850_EXPOSURE_REG_M, (exposure >> 8) & 0xff, 0x00);
	ov13850_write_reg(OV13850_EXPOSURE_REG_L, exposure & 0xf0, 0x00); /*fraction part not used */
}

#if 0
static void ov13850_set_exposure_gain(u32 exposure, u32 gain)
{
	ov13850_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group hold start

	ov13850_write_reg(OV13850_EXPOSURE_REG_H, (exposure >> 16) & 0x0f, 0x00);
	ov13850_write_reg(OV13850_EXPOSURE_REG_M, (exposure >> 8) & 0xff, 0x00);
	ov13850_write_reg(OV13850_EXPOSURE_REG_L, exposure & 0xf0, 0x00); /*fraction part not used */

	gain <<=1; //sensor:0x20 = 1x,  isp:0x10 = 1x

	if (gain == 0)
	{
		goto out;//wrong gain
	}
	else if (gain > 0xf8)
	{
		gain = 0xf8;//max gain is 7.75
	}
	ov13850_write_reg(OV13850_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	ov13850_write_reg(OV13850_GAIN_REG_L, gain & 0xff, 0x00);

out:
	ov13850_write_reg(GROUP_HOLD_FUNCTION_REG, 0x10 , 0x00);//group hold end
	ov13850_write_reg(GROUP_HOLD_FUNCTION_REG, 0x10 , 0x00);//group hold launch

	return;
}
#endif

static void ov13850_set_vts(u16 vts)
{
	print_debug("Enter %s  ", __func__);
	ov13850_write_reg(OV13850_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
	ov13850_write_reg(OV13850_VTS_REG_L, vts & 0xff, 0x00);
}

static u32 ov13850_get_vts_reg_addr(void)
{
	return OV13850_VTS_REG_H;
}


extern u32 sensor_override_params[OVERRIDE_TYPE_MAX];
static u32 ov13850_get_override_param(camera_override_type_t type)
{
	u32 ret_val = sensor_override_params[type];

	switch (type) {
	case OVERRIDE_ISO_HIGH:
		ret_val = OV13850_MAX_ISO;
		break;

	case OVERRIDE_ISO_LOW:
		ret_val = OV13850_MIN_ISO;
		break;

	/* decrease frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_HIGH2MID:
		ret_val = OV13850_AUTOFPS_GAIN_HIGH2MID;
		break;
	case OVERRIDE_AUTOFPS_GAIN_MID2LOW:
		ret_val = OV13850_AUTOFPS_GAIN_MID2LOW;
		break;

	/* increase frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_LOW2MID:
		ret_val = OV13850_AUTOFPS_GAIN_LOW2MID;
		break;
	case OVERRIDE_AUTOFPS_GAIN_MID2HIGH:
		ret_val = OV13850_AUTOFPS_GAIN_MID2HIGH;
		break;

	case OVERRIDE_FPS_MAX:
		ret_val = OV13850_MAX_FRAMERATE;
		break;

	case OVERRIDE_FPS_MID:
		ret_val = OV13850_MID_FRAMERATE;
		break;

	case OVERRIDE_FPS_MIN:
		ret_val = OV13850_MIN_FRAMERATE;
		break;

	case OVERRIDE_CAP_FPS_MIN:
		ret_val = OV13850_MIN_CAP_FRAMERATE;
		break;

	case OVERRIDE_FLASH_TRIGGER_GAIN:
		ret_val = OV13850_FLASH_TRIGGER_GAIN;
		break;

	case OVERRIDE_SHARPNESS_PREVIEW:
		ret_val = OV13850_SHARPNESS_PREVIEW;
		break;

	case OVERRIDE_SHARPNESS_CAPTURE:
		ret_val = OV13850_SHARPNESS_CAPTURE;
		break;

	default:
		print_error("%s:not override or invalid type %d, use default",__func__, type);
		break;
	}

	return ret_val;
}

static void ov13850_get_flash_awb(flash_platform_t type, awb_gain_t *flash_awb)
{
	*flash_awb = flash_platform_awb[0];
	print_info("ov13850_get_flash_awb: type 0x%x,", type);
}

/*
 **************************************************************************
 * FunctionName: ov13850_get_gain;
 * Description :get gain from sensor
 * Input       	 NA;
 * Output      	 gain value from sensor
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static u32 ov13850_get_gain(void)
{
	u8 gain_h = 0, gain_l = 0;
	u32 gain = 0;
	ov13850_read_reg(OV13850_GAIN_REG_H, &gain_h);
	ov13850_read_reg(OV13850_GAIN_REG_L, &gain_l);

	gain = (gain_h << 8) | gain_l;//16 = 1x
	return gain;
}

/*
 **************************************************************************
 * FunctionName: ov13850_get_exposure;
 * Description :get exposure from sensor
 * Input       	 NA;
 * Output      	 exposure value from sensor
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static u32  ov13850_get_exposure(void)
{
	u32 expo = 0;
	u8 expo_h = 0, expo_m = 0, expo_l = 0;

	ov13850_read_reg(OV13850_EXPOSURE_REG_H, &expo_h);
	ov13850_read_reg(OV13850_EXPOSURE_REG_M, &expo_m);
	ov13850_read_reg(OV13850_EXPOSURE_REG_L, &expo_l);

	expo = (expo_h  << 16) | (expo_m << 8) | expo_l;
	return expo;
}

/*
 **************************************************************************
 * FunctionName: ov13850_reset;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_reset(camera_power_state power_state)
{
	print_debug("%s  \n", __func__);

	if (POWER_ON == power_state) {
		k3_ispgpio_reset_sensor(ov13850_lit171.sensor_index, power_state,
			      ov13850_lit171.power_conf.reset_valid);
		udelay(100);			      		
		k3_isp_io_enable_mclk(MCLK_ENABLE, ov13850_lit171.sensor_index);
		mdelay(5);
	} else {
		k3_isp_io_enable_mclk(MCLK_DISABLE, ov13850_lit171.sensor_index);
		udelay(10);
		k3_ispgpio_reset_sensor(ov13850_lit171.sensor_index, power_state,
			      ov13850_lit171.power_conf.reset_valid);	
	}
	ov13850_lit171.old_flip = 0;
	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov13850_init;
 * Description : ov13850 init function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : Error code indicating success or failure;
 * Other       : NA;
 **************************************************************************
*/
static int ov13850_init(void)
{
	static bool ov13850_check = false;
	print_debug("%s  ", __func__);

	if (false == ov13850_check) {
		if (video_check_suspensory_camera("ov13850_sensor_171") != 1) {
			print_error("%s: product not have this sensor", __func__);
			return -ENODEV;
		}
		ov13850_check = true;
	}

	if (ov13850_lit171.owner && !try_module_get(ov13850_lit171.owner)) {
		print_error("%s: try_module_get fail", __func__);
		return -ENOENT;
	}

	ov13850_lit171.old_flip = 0;
	k3_ispio_power_init(M_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - pri camera*/
	k3_ispio_power_init(M_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);		/*IO 1.8V - pri camera*/
	k3_ispio_power_init(M_CAMERA_VCM_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*AF 2.85V - pri camera*/
	k3_ispio_power_init(M_CAMERA_CORE_VDD, LDO_VOLTAGE_12V, LDO_VOLTAGE_12V);	/*core 1.2V - pri camera*/

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ov13850_exit;
 * Description : ov13850 exit function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov13850_exit(void)
{
	print_debug("enter %s", __func__);

	k3_ispio_power_deinit();

	if (ov13850_lit171.owner) {
		module_put(ov13850_lit171.owner);
	}
	print_debug("exit %s", __func__);
}

/*
 **************************************************************************
 * FunctionName: ov13850_shut_down;
 * Description : ov13850 shut down function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov13850_shut_down(void)
{
	print_debug("enter %s", __func__);
	k3_ispgpio_power_sensor(&ov13850_lit171, POWER_OFF);
}

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
static void ov13850_config_dphy_clk(camera_state state)
{
	u8 lane_clk;
	
	if (state == STATE_PREVIEW) {
		lane_clk =ov13850_lit171.frmsize_list[ov13850_lit171.preview_frmsize_index].lane_clk;
	} else {
		lane_clk =ov13850_lit171.frmsize_list[ov13850_lit171.capture_frmsize_index].lane_clk;
	}

	print_info("%s lane_clk = 0x%x state = %d",__func__, lane_clk, state);
	k3_ispio_config_lane_clk(ov13850_lit171.mipi_index, ov13850_lit171.mipi_lane_count, lane_clk);
}

/*
 **************************************************************************
 * FunctionName: ov13850_get_sensor_reg;
 * Description : read sensor's reg value;
 * Input       : reg, register to be read;
 * Output      : pvalue, value readed from reg;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/

static void ov13850_get_sensor_reg(int reg, int *pvalue)
{
	u8 value = 0;
	if (NULL == pvalue)
	{
		print_error("%s, NULL data pointer!", __func__);
		return;
	}
	ov13850_read_reg(reg, &value);
	*pvalue = value;
	//print_info("%s, reg:0x%x, value:0x%x", __func__, reg, *pvalue);
	return;
}
/*
 **************************************************************************
 * FunctionName: ov13850_set_sensor_reg;
 * Description : write sensor's reg value;
 * Input       : reg, register to be write;
 * Output      : value, value to be writen;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov13850_set_sensor_reg(int reg, int value)
{
	ov13850_write_reg(reg, value & 0xff, 0x00);
	return;
}

#ifdef OV13850_LIT171_OTP
/****************************************************************************
* FunctionName: ov13850_read_otp;
* Description : i2c api used to read information from eeprom.
* Input       : NA;
* Output      : ov13850_otp;
* ReturnValue : NONEl;
* Other       : NA;
***************************************************************************/
static void ov13850_read_otp(u8 i2c_addr,u16 reg,u8 *buf,u16 count)
{
	u16 i   = 0;
	int ret = 0;
	u16 val = 0;

	for(;i<count;i++) {
		ret =ispv1_read_sensor_byte_addr8(ov13850_lit171.i2c_config.index,i2c_addr,reg+i,&val,ov13850_lit171.i2c_config.val_bits);
		if(ret !=0)
			print_error("%s fail to read otp with error code %d, i2c_addr=0x%x reg_addr=0x%x\n", __func__,ret,i2c_addr,reg+i);

		buf[i] = (val&0xff);
		OTPSUMVAL += buf[i];

		//print_info("######OTPPrint~~~%s::I2CAddr=0x%x, RegAddr=0x%x, RegVal=0x%x ######\n", __func__, i2c_addr, reg+i, buf[i]);
	}

	return;
}

/****************************************************************************
* FunctionName: ov13850_otp_read_id;
* Description : Get id etc. parameters from eeprom.
* Input       : NA;
* Output      : ov13850_otp;
* ReturnValue : true-success,false-fail;
* Other       : NA;
***************************************************************************/
static bool ov13850_otp_read_id(void)
{
	u8 buf[5] = {0};
	u8 vendor_id = 0;

	ov13850_read_otp(OTP_SLAVE_ADDR1,OTP_ID_REG,buf,5);

	print_info("module info year 20%02d month %d day %d, SNO. 0x%x  vendor id&version 0x%x\n", buf[0],buf[1],buf[2],buf[3],buf[4]);

	vendor_id = (buf[4]>>4)&0x0F;
	if(vendor_id == OV1385_MODULE_VENDOR_ID && buf[3] == OV1385_MODULE_HUAWEI_ID) { //Liteon 0x03 & huaweiModuleCode is 23060167(0n167 = 0xA7)
		ov13850_otp_flag |= OV13850_OTP_ID_READ;
		return true;
	} else {
		print_error("%s OTP data is worng for with wrong vender id!!!\n",__func__);
		return false;
	}
}

/****************************************************************************
* FunctionName: ov13850_otp_read_awb;
* Description : Get awb parameters from eeprom.
* Input       : NA;
* Output      : ov13850_otp;
* ReturnValue : true-success,false-fail;
* Other       : NA;
***************************************************************************/
static bool ov13850_otp_read_awb(void)
{
	u8  buf[6] = {0};

	ov13850_read_otp(OTP_SLAVE_ADDR1,OTP_AWB_REG,buf,6);

	//print_info("%s OTP data are Rg_high=%x, Rg_low=%x, Bg_high=%x, Bg_low=%x, gbgr_high=%x, gbgr_low=%x!!!\n", __func__, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);

	ov13850_otp.rg_ratio = buf[0];
	ov13850_otp.rg_ratio <<= 8;
	ov13850_otp.rg_ratio += buf[1];
	ov13850_otp.bg_ratio = buf[2];
	ov13850_otp.bg_ratio <<= 8;
	ov13850_otp.bg_ratio += buf[3];
	ov13850_otp.grgb = buf[4];
	ov13850_otp.grgb <<= 8;
	ov13850_otp.grgb += buf[5];
	print_info("%s OTP data are rg_ratio=0x%x, bg_ratio=0x%x, grgb=0x%x\n",__func__, ov13850_otp.rg_ratio, ov13850_otp.bg_ratio, ov13850_otp.grgb);

	if(0 == ov13850_otp.rg_ratio || 0 ==ov13850_otp.bg_ratio || 0 == ov13850_otp.grgb){//if awb value read is error for zero, abnormal branch deal
		print_error("%s OTP data is worng!!!\n",__func__);
		return false;
	}
	ov13850_otp_flag |= OV13850_OTP_AWB_READ;

	return true;
}

/****************************************************************************
* FunctionName: ov13850_otp_set_awb;
* Description : Set AWB parameters to sensor registers.
* Input       : NA;
* Output      : ov13850_otp;
* ReturnValue : true-success,false-fail;
* Other       : NA;
***************************************************************************/
static void ov13850_otp_set_awb(void)
{
	u16 R_gain = 0;
	u16 G_gain = 0;
	u16 B_gain = 0;
	u16 Base_gain = 0;
	u8  temp = 0;

    /*calculate the expect reg gain form the otp awb data by ov provided algorithm*/
	R_gain = (RG_Ratio_Typical*1000) / ov13850_otp.rg_ratio;
	B_gain = (BG_Ratio_Typical*1000) / ov13850_otp.bg_ratio;
	G_gain = 1000;
	if (R_gain < 1000 || B_gain < 1000){
		if (R_gain < B_gain)
			Base_gain = R_gain;
		else
			Base_gain = B_gain;
	}else{
		Base_gain = G_gain;
	}
	R_gain = 0x400 * R_gain / (Base_gain);
	B_gain = 0x400 * B_gain / (Base_gain);
	G_gain = 0x400 * G_gain / (Base_gain);

	print_info("ov13850_get_otp_from_sensor() ~ %s R_gain=0x%x, B_gain=0x%x, G_gain=0x%x\n",__func__, R_gain, B_gain, G_gain);

	ov13850_read_reg(0x5001, &temp);
	temp = 0x02 | temp;
	ov13850_write_reg(0x5001, temp, 0x00);
	if (R_gain>0x400){
		ov13850_write_reg(0x5056, R_gain>>8, 0x00);
		ov13850_write_reg(0x5057, R_gain & 0x00ff, 0x00);
	}
	if (G_gain>0x400){
		ov13850_write_reg(0x5058, G_gain>>8, 0x00);
		ov13850_write_reg(0x5059, G_gain & 0x00ff, 0x00);
	}
	if (B_gain>0x400){
		ov13850_write_reg(0x505a, B_gain>>8, 0x00);
		ov13850_write_reg(0x505b, B_gain & 0x00ff, 0x00);
	}

	return;
}

/****************************************************************************
* FunctionName: ov13850_otp_read_lsc;
* Description : Get lens shading parameters from eeprom.
* Input       : NA;
* Output      : ov13850_otp;
* ReturnValue : true-success,false-fail;
* Other       : NA;
***************************************************************************/
static bool ov13850_otp_read_lsc(void)
{
	//LSC 0xa0:0b--0xff & 0xa2:00--0x72  total = 360
	ov13850_read_otp(OTP_SLAVE_ADDR1,OTP_LSC_1_REG,ov13850_otp.lsc,0xff-0x0b+1);
	ov13850_read_otp(OTP_SLAVE_ADDR2,OTP_LSC_2_REG,&ov13850_otp.lsc[0xff-0x0b+1],0x72+1);

	print_info("%s LCS[0]=%x, LSC[244]=%x, LSC[245]=%x, LSC[359]=%x\n",__func__,
		ov13850_otp.lsc[0],ov13850_otp.lsc[244],ov13850_otp.lsc[245],ov13850_otp.lsc[359]);

	ov13850_otp_flag |= OV13850_OTP_LSC_READ;

	return true;
}

/****************************************************************************
* FunctionName: ov13850_otp_set_lsc;
* Description : Set lens shading parameters to sensor registers.
* Input       : NA;
* Output      : NA;
* ReturnValue : NONE;
* Other       : NA;
***************************************************************************/
static void ov13850_otp_set_lsc(void)
{
	u16 i = 0;
	u8  temp = 0;

	ov13850_read_reg(0x5000, &temp);
	temp = 0x01 | temp;
	ov13850_write_reg(0x5000, temp, 0x00);

	for(;i<OV13850_OTP_LSC_SIZE;i++) {
		ov13850_write_reg(0x5200+i, ov13850_otp.lsc[i], 0x00);
	}
	print_info("%s, set OTP LSC to sensor OK.\n", __func__);

	return;
}

/****************************************************************************
* FunctionName: ov13850_otp_read_vcm;
* Description : Get AF motor parameters from EEPROM.;
* Input       : NA;
* Output      : ov13850_otp;
* ReturnValue :ture-success,false-fail;
* Other       : NA;
***************************************************************************/
static bool ov13850_otp_read_vcm(void)
{
	u8  buf[4] = {0};
    u16 vcm_start = 0;
	u16 vcm_end =0;

	ov13850_read_otp(OTP_SLAVE_ADDR2,OTP_VCM_REG,buf,4);

	vcm_start = buf[0];
	vcm_start <<= 8;
	vcm_start += buf[1];
	vcm_end   = buf[2];
	vcm_end   <<= 8;
	vcm_end   += buf[3];

	if((vcm_start != vcm_end ) &&(vcm_end > vcm_start) && vcm_start != 0 && vcm_end  != 0) {
		ov13850_otp_flag |= OV13850_OTP_VCM_READ;
		ov13850_otp.vcm_start = vcm_start;
		ov13850_otp.vcm_end = vcm_end;
		print_info("%s cm_start=0x%x, vcm_end=0x%x \n",__func__, ov13850_otp.vcm_start,ov13850_otp.vcm_end);
	} else {//Abnormal branch deal
		ov13850_otp.vcm_start = 0;
		ov13850_otp.vcm_end = 0;
		print_error("%s VCM OTP data is worng! vcm_start=0x%x, vcm_end=0x%x\n",__func__, ov13850_otp.vcm_start,ov13850_otp.vcm_end);
		return false;
	}

	return true;
}

/****************************************************************************
* FunctionName: ov13850_otp_get_vcm;
* Description : Get vcm start and stop parameters read from OTP.;
* Input       : NA;
* Output      : vcm_start, vcm_end
* ReturnValue : NONE;
* Other       : NA;
***************************************************************************/
static void ov13850_otp_get_vcm(u16 *vcm_start, u16 *vcm_end)
{
	if (0 == ov13850_otp.vcm_start) {
		*vcm_start = ov13850_lit171.vcm->infiniteDistance;
	} else {
        if (ov13850_otp.vcm_start > ov13850_lit171.vcm->startCurrentOffset)
            *vcm_start = ov13850_otp.vcm_start - ov13850_lit171.vcm->startCurrentOffset;
        else
            *vcm_start = 0;
	}

	if (0 == ov13850_otp.vcm_end) {
		*vcm_end = ov13850_lit171.vcm->normalDistanceEnd;
	} else {
		*vcm_end = ov13850_otp.vcm_end;
	}

	print_info("%s, vcm_start:%#x, vcm_end:%#x", __func__, *vcm_start, *vcm_end);
}

/*
 **************************************************************************
 * FunctionName: ov13850_get_otp_from_sensor;
 * Description : the api to use ov13850 sensor module OTP function;
 * Input         : NULL;
 * Output       : the ov13850_otp;
 * ReturnValue : true-OTP can be used, false-OTP is error, cannot be used;
 * Other         : NA;
 **************************************************************************
*/
static bool ov13850_get_otp_from_sensor(void)
{
	u8   sum = 0;
    u8   otpCheckSumVal = 0;
	bool retVal = false;
#ifdef OV13850_OTP_READ_TIME_PRINT
	u16 otpReadUsed = 0;
	struct timeval otpReadBegin, otpReadEnd;
#endif

	print_info("%s enters!\n",__func__);
	if((ov13850_otp_flag & OV13850_OTP_FAIL_FLAG) == OV13850_OTP_FAIL_FLAG) {//Just check OTP once whether success or not
		print_error("%s OTP data is worng, ov13850_otp_flag=0x%x\n", __func__,ov13850_otp_flag);
		return false;
	}else if((ov13850_otp_flag & OV13850_OTP_CHECKSUM_READ) == OV13850_OTP_CHECKSUM_READ){//branch for read success, no need read more
		print_info("%s OTP has been read success already, ov13850_otp_flag=0x%x\n", __func__,ov13850_otp_flag);
		return true;
	}

#ifdef OV13850_OTP_READ_TIME_PRINT
	memset(&otpReadBegin,0,sizeof(otpReadBegin));
	memset(&otpReadEnd,0,sizeof(otpReadEnd));
	do_gettimeofday(&otpReadBegin);
#endif

	ov13850_read_otp(OTP_SLAVE_ADDR2,OTP_CHECKSUM_REG,&otpCheckSumVal,1);
	if(otpCheckSumVal == 0xFF){
		print_error("%s OTP data has not flashed!\n", __func__);
		goto OTP_FAIL;
	}

	memset(&ov13850_otp,0,sizeof(ov13850_otp));//initial ov13850_otp

	retVal = ov13850_otp_read_id();
	if(false == retVal){
		print_error("%s ov13850_otp_read_id() failed!\n",__func__);
		goto OTP_FAIL;
	}

	retVal = ov13850_otp_read_awb();
	if(false == retVal){
		print_error("%s ov13850_otp_read_awb() failed!\n",__func__);
		goto OTP_FAIL;
	}

	retVal = ov13850_otp_read_vcm();
	if(false == retVal){
		print_error("%s ov13850_otp_read_vcm() failed!\n",__func__);
		goto OTP_FAIL;
	}

	ov13850_otp_read_lsc();

	sum = (OTPSUMVAL - otpCheckSumVal) % 0xff;

#ifdef OV13850_OTP_READ_TIME_PRINT
	do_gettimeofday(&otpReadEnd);
	otpReadUsed = (otpReadEnd.tv_sec - otpReadBegin.tv_sec) * 1000 + (otpReadEnd.tv_usec - otpReadBegin.tv_usec) / 1000;
	print_info("%s used time is %d ms\n", __func__,otpReadUsed);
#endif

	if(otpCheckSumVal == sum){
		ov13850_otp_flag |= OV13850_OTP_CHECKSUM_READ;
		print_info("%s success, OTPSUMVAL: %d, otpCheckSumVal: %d ,sum:%d, ov13850_otp_flag=0x%x\n", __func__, OTPSUMVAL, otpCheckSumVal,sum,ov13850_otp_flag);
		return true;
	} else {
		ov13850_otp_flag |= OV13850_OTP_CHECKSUM_ERR;
		print_error("%s fail, OTPSUMVAL: %d, otpCheckSumVal: %d ,sum:%d \n", __func__, OTPSUMVAL, otpCheckSumVal,sum);
	}

OTP_FAIL:
	ov13850_otp_flag |= OV13850_OTP_FAIL_FLAG;
	print_error("%s ov13850_otp_flag=0x%x \n", __func__,ov13850_otp_flag);
	return false;
}
#endif

/*
**************************************************************************
* FunctionName: ov13850_check_otp;
* Description : check otp's status;
* Input       : NA;
* Output      : current otp status;
* ReturnValue : NA;
* Other       : NA;
**************************************************************************
*/
static void ov13850_check_otp(sensor_otp_status * status)
{
      if (NULL == status)
	  {
          print_error("%s, NULL data pointer!", __func__);
          return;
      }
#ifdef OV13850_LIT171_OTP
      if((ov13850_otp_flag & OV13850_OTP_FAIL_FLAG) != OV13850_OTP_FAIL_FLAG){
	     *status = OTP_VALID;
	  }else{
		 *status = OTP_INVALID;
	  }
#else
	  *status = OTP_VALID;
#endif
      print_info("otp status:%d, ov13850_otp_flag:0x%x", *status,ov13850_otp_flag);

	  return;
}

/*
 **************************************************************************
 * FunctionName: ov13850_set_default;
 * Description : init ov13850_lit171;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void ov13850_set_default(void)
{
	ov13850_lit171.init = ov13850_init;
	ov13850_lit171.exit = ov13850_exit;
	ov13850_lit171.shut_down = ov13850_shut_down;
	ov13850_lit171.reset = ov13850_reset;
	ov13850_lit171.check_sensor = ov13850_check_sensor;
	ov13850_lit171.power = ov13850_power;
	ov13850_lit171.init_reg = ov13850_init_reg;
	ov13850_lit171.stream_on = ov13850_stream_on;

	ov13850_lit171.get_format = ov13850_get_format;
	ov13850_lit171.set_flash = NULL;
	ov13850_lit171.get_flash = NULL;
	ov13850_lit171.set_scene = NULL;
	ov13850_lit171.get_scene = NULL;

	ov13850_lit171.enum_framesizes = ov13850_enum_framesizes;
	ov13850_lit171.try_framesizes = ov13850_try_framesizes;
	ov13850_lit171.set_framesizes = ov13850_set_framesizes;
	ov13850_lit171.get_framesizes = ov13850_get_framesizes;

	ov13850_lit171.enum_frame_intervals = ov13850_enum_frame_intervals;
	ov13850_lit171.try_frame_intervals = NULL;
	ov13850_lit171.set_frame_intervals = NULL;
	ov13850_lit171.get_frame_intervals = NULL;

	ov13850_lit171.get_vts_reg_addr = ov13850_get_vts_reg_addr;

	ov13850_lit171.get_capability = ov13850_get_capability;

	ov13850_lit171.set_hflip = ov13850_set_hflip;
	ov13850_lit171.get_hflip = ov13850_get_hflip;
	ov13850_lit171.set_vflip = ov13850_set_vflip;
	ov13850_lit171.get_vflip = ov13850_get_vflip;
	ov13850_lit171.update_flip = ov13850_update_flip;

	strncpy(ov13850_lit171.info.name,"ov13850_liteon_171",sizeof(ov13850_lit171.info.name));
	ov13850_lit171.interface_type = MIPI1;
	ov13850_lit171.mipi_lane_count = CSI_LINES_4;
	ov13850_lit171.mipi_index = CSI_INDEX_0;
	ov13850_lit171.sensor_index = CAMERA_SENSOR_PRIMARY;
	ov13850_lit171.skip_frames = 2;

	ov13850_lit171.power_conf.pd_valid = LOW_VALID;
	ov13850_lit171.power_conf.reset_valid = LOW_VALID;
	ov13850_lit171.power_conf.vcmpd_valid = LOW_VALID;

	ov13850_lit171.i2c_config.index = I2C_PRIMARY;
	ov13850_lit171.i2c_config.speed = I2C_SPEED_400;
	ov13850_lit171.i2c_config.addr = OV13850_SLAVE_ADDRESS;
	ov13850_lit171.i2c_config.addr_bits = I2C_16BIT;
	ov13850_lit171.i2c_config.val_bits = I2C_8BIT;

	ov13850_lit171.preview_frmsize_index = 0;
	ov13850_lit171.capture_frmsize_index = 0;
	ov13850_lit171.frmsize_list = ov13850_framesizes;
	ov13850_lit171.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW10;
	ov13850_lit171.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW10;

#ifdef OV13850_AP_WRITEAE_MODE /* just an example and test case for AP write AE mode */
	ov13850_lit171.aec_addr[0] = 0;
	ov13850_lit171.aec_addr[1] = 0;
	ov13850_lit171.aec_addr[2] = 0;
	ov13850_lit171.agc_addr[0] = 0;
	ov13850_lit171.agc_addr[1] = 0;
	ov13850_lit171.ap_writeAE_delay = 6000; /* 5 expo and gain registers, 6000 us is enough */
#else
	ov13850_lit171.aec_addr[0] = 0x3500;
	ov13850_lit171.aec_addr[1] = 0x3501;
	ov13850_lit171.aec_addr[2] = 0x3502;
	ov13850_lit171.agc_addr[0] = 0x350a; 
	ov13850_lit171.agc_addr[1] = 0x350b;
#endif
	ov13850_lit171.sensor_type = SENSOR_OV;
	ov13850_lit171.sensor_rgb_type = SENSOR_BGGR;;

	ov13850_lit171.set_gain = ov13850_set_gain;
	ov13850_lit171.set_exposure = ov13850_set_exposure;
	ov13850_lit171.set_exposure_gain = NULL;
	ov13850_lit171.set_vts = ov13850_set_vts;

	ov13850_lit171.get_override_param = ov13850_get_override_param;

	ov13850_lit171.sensor_gain_to_iso = ov13850_gain_to_iso;
	ov13850_lit171.sensor_iso_to_gain = ov13850_iso_to_gain;

	ov13850_lit171.get_sensor_aperture = ov13850_get_sensor_aperture;
	ov13850_lit171.get_equivalent_focus = NULL;

	ov13850_lit171.set_effect = NULL;

	ov13850_lit171.isp_location = CAMERA_USE_K3ISP;
	ov13850_lit171.sensor_tune_ops = NULL;

	ov13850_lit171.af_enable = 1;
	ov13850_lit171.vcm = &vcm_dw9714;
	ov13850_lit171.get_flash_awb = ov13850_get_flash_awb;

	ov13850_lit171.image_setting.lensc_param = ov13850_lensc_param;
	ov13850_lit171.image_setting.ccm_param = ov13850_ccm_param;
	ov13850_lit171.image_setting.awb_param = ov13850_awb_param;

	ov13850_lit171.fps_max = 30;
	ov13850_lit171.fps_min = 10;
	ov13850_lit171.fps = 25;


	ov13850_lit171.owner = THIS_MODULE;

	ov13850_lit171.info.facing = CAMERA_FACING_BACK;
	ov13850_lit171.info.orientation = 90;
	ov13850_lit171.info.focal_length = 379;	/* 3.79mm */
	ov13850_lit171.info.h_view_angle = 63;//63.2
	ov13850_lit171.info.v_view_angle = 49;

	ov13850_lit171.lane_clk = CLK_500M;

	ov13850_lit171.hflip = 0;
	ov13850_lit171.vflip = 0;
	ov13850_lit171.old_flip = 0;

	ov13850_lit171.get_gain     				= ov13850_get_gain;
	ov13850_lit171.get_exposure   			= ov13850_get_exposure;
	ov13850_lit171.init_isp_reg 				= ov13850_init_isp_reg;

	ov13850_lit171.support_summary		= false;
	ov13850_lit171.isp_idi_skip = false;

	ov13850_lit171.stream_off_setting = ov13850_stream_off_regs;
	ov13850_lit171.stream_off_setting_size = ARRAY_SIZE(ov13850_stream_off_regs);

	/*if there have different data rate of sensor resolution we need this config_dphy_clk 
	   otherwise if all resolution is same rate config_dphy_clk must to be null*/
	ov13850_lit171.config_dphy_clk = ov13850_config_dphy_clk;

	ov13850_lit171.get_sensor_reg = ov13850_get_sensor_reg;
	ov13850_lit171.set_sensor_reg = ov13850_set_sensor_reg;
	ov13850_lit171.check_otp_status = ov13850_check_otp;

}

/*
 **************************************************************************
 * FunctionName: ov13850_lit171_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int ov13850_lit171_module_init(void)
{
	ov13850_set_default();
	//print_info("\n autumn add for test Function for new driver~~~~~\n",__func__);	
	return register_camera_sensor(ov13850_lit171.sensor_index, &ov13850_lit171);
}

/*
 **************************************************************************
 * FunctionName: ov13850_lit171_module_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void __exit ov13850_lit171_module_exit(void)
{
	unregister_camera_sensor(ov13850_lit171.sensor_index, &ov13850_lit171);
}

MODULE_AUTHOR("Hisilicon");
module_init(ov13850_lit171_module_init);
module_exit(ov13850_lit171_module_exit);
MODULE_LICENSE("GPL");

/********************************** END **********************************************/
