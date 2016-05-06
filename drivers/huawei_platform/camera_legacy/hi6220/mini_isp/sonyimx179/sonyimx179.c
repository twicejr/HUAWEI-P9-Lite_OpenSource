

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
#include <mach/boardid.h>
#include <mach/gpio.h>
#include "mini_sensor_common.h"
#include "sonyimx179.h"
#include <asm/bug.h>
#include <linux/device.h>

#define LOG_TAG "SONYIMX179"
//#define DEBUG_DEBUG 1
#include "mini_cam_log.h"
#include <cam_util.h>
#include "drv_regulator_user.h"
#include "hsad/config_interface.h"
#include <mach/pmussi_drv.h>
#include "mini_effect.h"
#include <hsad/config_mgr.h>
//#include "../camera_agent.h"
#include "mini_k3_isp.h"
#include "camera_agent.h"
#ifdef _IS_DEBUG_AE
#undef _IS_DEBUG_AE
#define _IS_DEBUG_AE 0
#endif
#define SONYIMX179_ZSL                       (0x00)
#define SONYIMX179_MODULE_ID             (GPIO_18_4) //sunny or liteon
#define DIG_GAIN_GR_H                        0x020E
#define DIG_GAIN_GR_L                        0x020F
#define DIG_GAIN_R_H                         0x0210
#define DIG_GAIN_R_L                         0x0211
#define DIG_GAIN_B_H                         0x0212
#define DIG_GAIN_B_L                         0x0213
#define DIG_GAIN_GB_H                        0x0214
#define DIG_GAIN_GB_L                        0x0215

#define WD_COARSE_INTEG_TIME_DS_H     		 (0x0230)
#define WD_COARSE_INTEG_TIME_DS_L     		 (0x0231)
#define WD_ANA_GAIN_DS                    	 (0x0233)

#define ATR_OFF_SETTING_1             		 (0x446D)
#define ATR_OFF_SETTING_2             		 (0x446E)
#define TRIGGER_SETTING                  	 (0x446C)

#define WB_LMT_REG_H                         (0x441E)
#define WB_LMT_REG_L                         (0x441F)

#define AE_SAT_REG_H                         (0x4446)
#define AE_SAT_REG_L                         (0x4447)

#define SONYIMX179_ABS_GAIN_B_H				 (0x0716)
#define SONYIMX179_ABS_GAIN_B_L				 (0x0717)
#define SONYIMX179_ABS_GAIN_GB_H			 (0x0718)
#define SONYIMX179_ABS_GAIN_GB_L			 (0x0719)
#define SONYIMX179_ABS_GAIN_GR_H			 (0x0712)
#define SONYIMX179_ABS_GAIN_GR_L			 (0x0713)
#define SONYIMX179_ABS_GAIN_R_H				 (0x0714)
#define SONYIMX179_ABS_GAIN_R_L				 (0x0715)

#define GROUP_HOLD_FUNCTION_REG   			 (0x0104)
#define SONYIMX179_MAX_ISO 			         1550
#define SONYIMX179_MIN_ISO                   100

/* support 3 level framerate now, if mid fps same as min, set to 2 level framerate */
#define SONYIMX179_AUTOFPS_GAIN_HIGH2MID		0x24
#define SONYIMX179_AUTOFPS_GAIN_MID2LOW		    0x24
#define SONYIMX179_AUTOFPS_GAIN_LOW2MID		    0x60
#define SONYIMX179_AUTOFPS_GAIN_MID2HIGH		0x60

#define SONYIMX179_MAX_FRAMERATE                30
#define SONYIMX179_MID_FRAMERATE		        15
#define SONYIMX179_MIN_FRAMERATE                10
#define SONYIMX179_MIN_CAP_FRAMERATE            8
#define SONYIMX179_FLASH_TRIGGER_GAIN           0xff
#define SONYIMX179_SHARPNESS_PREVIEW            0x30
#define SONYIMX179_SHARPNESS_CAPTURE            0x08

#define SONYIMX179_SLAVE_ADDRESS                0x10
#define SONYIMX179_CHIP_ID                      (0x0134)

#define SONYIMX179_FLIP		                    0x0101

#define SONYIMX179_EXPOSURE_REG_H	            0x0202
#define SONYIMX179_EXPOSURE_REG_L	            0x0203
#define SONYIMX179_GAIN_REG_H		            0x0204
#define SONYIMX179_GAIN_REG_L		            0x0205

#define SONYIMX179_VTS_REG_H		            0x0340
#define SONYIMX179_VTS_REG_L		            0x0341

#define SONYIMX179_APERTURE_FACTOR              200 //F2.0
#define SONYIMX179_EQUIVALENT_FOCUS	            0

#define SONYIMX179_AP_WRITEAE_MODE
#define SONYIMX179_MAX_ANALOG_GAIN	            8

enum sensor_module_type
{
	MODULE_LITEON,
	MODULE_SUNNY,
	MODULE_UNSUPPORT
};

static u32 sensor_module;

static mini_camera_capability sonyimx179_cap[] = {
	//{V4L2_CID_FLASH_MODE, THIS_FLASH},
	//{V4L2_CID_FOCUS_MODE, THIS_FOCUS_MODE},
	{V4L2_CID_ZSL,		  SONYIMX179_ZSL},
	{V4L2_CID_MINI_ISP_SUPPORTED, 1}  //add by zhoutian for mini-ISP
};

static mini_awb_gain_t flash_platform_awb[] = {
	{0xbd, 0x80, 0x80, 0xdc}, /*EDGE*/
};

/*
 * should be calibrated, three lights, from 0x1c264
 * here is long exposure
 */
static char sonyimx179_lensc_param[86*3] = {
};

/* should be calibrated, 6 groups 3x3, from 0x1c1d8 */
static short sonyimx179_ccm_param[54] = {
};

static char sonyimx179_awb_param[] = {
};

static mini_vcm_info_s vcm_dw9714_Sunny = {
    #include "vcm_dw9714_Sunny.h"
};

static mini_vcm_info_s vcm_dw9714_Liteon = {
    #include "vcm_dw9714_Liteon.h"
};

static mini_effect_params effect_imx179_sunny = {
    #include "effect_imx179_sunny_edge.h"
};

static mini_effect_params effect_imx179_liteon = {
    #include "effect_imx179_liteon_edge.h"
};


static mini_framesize_s sonyimx179_framesizes[] = {
    /*1280x720, hdr movie*/
	{0, 0, 1600, 1200, 4800, 4800, 30, 30, 0x2F3, 0x275,0x100, VIEW_FULL, RESOLUTION_4_3,false,false,{sonyimx179_rgb_framesize_1280x720_HDR, ARRAY_SIZE(sonyimx179_rgb_framesize_1280x720_HDR)},0},
	{0, 0, 1920, 1080, 4800, 4800, 30, 30, 100, 120, 0x100, VIEW_FULL, RESOLUTION_16_9,false,false,{sonyimx179_rgb_framesize_1280x720_HDR, ARRAY_SIZE(sonyimx179_rgb_framesize_1280x720_HDR)},4},
	{0, 0, 3280, 2464, 4800, 4800, 30, 30, 100, 120, 0x100, VIEW_FULL, RESOLUTION_4_3,false,false,{sonyimx179_rgb_framesize_1280x720_HDR, ARRAY_SIZE(sonyimx179_rgb_framesize_1280x720_HDR)},1},
	//{0, 0, 1280, 720, 4800, 4800, 10, 10, 0x2F3, 0x275,0x100, VIEW_FULL, RESOLUTION_16_9,false,false,{sonyimx179_rgb_framesize_1280x720_HDR, ARRAY_SIZE(sonyimx179_rgb_framesize_1280x720_HDR)} },
	//{0, 0, 4208, 3120, 4800, 4800, 1, 1, 0x2F3, 0x275,0x100, VIEW_FULL, RESOLUTION_4_3,false,false,{sonyimx179_rgb_framesize_1280x720_HDR, ARRAY_SIZE(sonyimx179_rgb_framesize_1280x720_HDR)} },
};

static mini_camera_sensor sonyimx179_sensor;

/*
 **************************************************************************
 * FunctionName: sonyimx179_read_reg;
 * Description : read sonyimx179 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
extern  int lm3642_write_reg16(u16 reg, u8 val,u8 addr);
extern int lm3642_read_reg16(u16 reg, u8 *val,u8 addr);
static int sonyimx179_read_reg(u16 reg, u8 *val)
{
return 0;
#if 0
	return k3_ispio_read_reg(sonyimx179_sensor.i2c_config.index,
			 sonyimx179_sensor.i2c_config.addr, reg, (u16*)val, sonyimx179_sensor.i2c_config.val_bits,sonyimx179_sensor.i2c_config.addr_bits);
#else
	//return lm3642_read_reg16(reg,val,sonyimx179_sensor.i2c_config.addr);
#endif

}

/*
 **************************************************************************
 * FunctionName: sonyimx179_write_reg;
 * Description : write sonyimx179 reg by i2c;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int sonyimx179_write_reg(u16 reg, u8 val, u8 mask)
{
return 0;
#if 0
	return k3_ispio_write_reg(sonyimx179_sensor.i2c_config.index,
			sonyimx179_sensor.i2c_config.addr, reg, val, sonyimx179_sensor.i2c_config.val_bits, mask,sonyimx179_sensor.i2c_config.addr_bits);
#else
	//return lm3642_write_reg16(reg,val,sonyimx179_sensor.i2c_config.addr);
#endif
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_write_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int sonyimx179_write_seq(const struct _mini_sensor_reg_t *seq, u32 size, u8 mask)
{
return 0;
#if 0
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	return k3_ispio_write_seq(sonyimx179_sensor.i2c_config.index,
			sonyimx179_sensor.i2c_config.addr, seq, size, sonyimx179_sensor.i2c_config.val_bits, mask,sonyimx179_sensor.i2c_config.addr_bits);

u16 i;
for(i=0;i<size;i++)
{
	sonyimx179_write_reg(seq[i].subaddr,seq[i].value, 0x00);
}
#endif
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_write_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void sonyimx179_write_isp_seq(const struct mini_isp_reg_t *seq, u32 size)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	mini_k3_ispio_write_isp_seq(seq, size);
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_read_isp_seq;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
#if 0
static void sonyimx179_read_isp_seq(struct mini_isp_reg_t *seq, u32 size)
{
	print_debug("Enter %s, seq[%#x], size=%d", __func__, (int)seq, size);
	mini_k3_ispio_read_isp_seq(seq, size);
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_read_isp_reg;
 * Description : Read ISP register;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */

static u32 sonyimx179_read_isp_reg(u32 reg_addr, u32 size)
{
	struct mini_isp_reg_t reg_seq[4];
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

	/*read register of isp for imx179 */
	sonyimx179_read_isp_seq(reg_seq, size);
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
 * FunctionName: sonyimx179_enum_frame_intervals;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx179_enum_frame_intervals(struct v4l2_frmivalenum *fi)
{
    if(!fi) {
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

/*
 **************************************************************************
 * FunctionName: sonyimx179_get_format;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx179_get_format(struct v4l2_fmtdesc *fmt)
{
	if (fmt->type == V4L2_BUF_TYPE_VIDEO_OVERLAY) {
		fmt->pixelformat = sonyimx179_sensor.fmt[STATE_PREVIEW];
	} else {
		fmt->pixelformat = sonyimx179_sensor.fmt[STATE_CAPTURE];
	}
	return 0;
}

static int sonyimx179_get_capability(u32 id, u32 *value)
{
	int i;
	for (i = 0; i < sizeof(sonyimx179_cap) / sizeof(sonyimx179_cap[0]); ++i) {
		if (id == sonyimx179_cap[i].id) {
			*value = sonyimx179_cap[i].value;
			break;
		}
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_enum_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx179_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 max_index = ARRAY_SIZE(mini_camera_framesizes) - 1;
	u32 this_max_index = ARRAY_SIZE(sonyimx179_framesizes) - 1;

    if(!framesizes) {
        return -EINVAL;
    }

	print_debug("enter %s; ", __func__);

	if (framesizes->index > max_index) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	if ((mini_camera_framesizes[framesizes->index].width > sonyimx179_framesizes[this_max_index].width)
		|| (mini_camera_framesizes[framesizes->index].height > sonyimx179_framesizes[this_max_index].height)) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}

	framesizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	framesizes->discrete.width = sonyimx179_framesizes[this_max_index].width;
	framesizes->discrete.height = sonyimx179_framesizes[this_max_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_try_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx179_try_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	int max_index = ARRAY_SIZE(sonyimx179_framesizes) - 1;

    if(!framesizes) {
        return -EINVAL;
    }

	print_debug("Enter Function:%s  ", __func__);

	if ((framesizes->discrete.width <= sonyimx179_framesizes[max_index].width)
	    && (framesizes->discrete.height <= sonyimx179_framesizes[max_index].height)) {
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
 * FunctionName: sonyimx179_set_framesizes;
 * Description : NA;
 * Input       : flag: if 1, set framesize to sensor,
 *					   if 0, only store framesize to camera_interface;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx179_set_framesizes(camera_state state,
				 struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type,bool zsl_preview)
{
	int i = 0;
	bool match = false;
	int size = 0;
    if(!fs) {
        return -EINVAL;
    }

	print_info("Enter Function:%s State(%d), flag=%d, width=%d, height=%d",
		   __func__, state, flag, fs->width, fs->height);
	size = ARRAY_SIZE(sonyimx179_framesizes);
    if(HDR_MOVIE_ON == sonyimx179_sensor.sensor_hdr_movie.hdrInfo.hdr_on) {
		for (i = 0; i < size; i++) {
			if ((sonyimx179_framesizes[i].width >= fs->width)
			    && (sonyimx179_framesizes[i].height >= fs->height)
			    && (mini_camera_get_resolution_type(fs->width, fs->height)
				   <= sonyimx179_framesizes[i].resolution_type)
			    && (VIEW_HDR_MOVIE == sonyimx179_framesizes[i].view_type)) {
    				fs->width = sonyimx179_framesizes[i].width;
    				fs->height = sonyimx179_framesizes[i].height;
    				match = true;
                    break;
			}
		}
	} else {
    	if (VIEW_FULL == view_type) {
    		for (i = 0; i < size; i++) {
    		    if ((zsl_preview == false) && sonyimx179_framesizes[i].zsl_only )
    		    {
    		        continue;
    		    }
    			if ((sonyimx179_framesizes[i].width >= fs->width)
    			    && (sonyimx179_framesizes[i].height >= fs->height)
    			    && (VIEW_FULL == sonyimx179_framesizes[i].view_type)
    			    && (mini_camera_get_resolution_type(fs->width, fs->height)
    			    <= sonyimx179_framesizes[i].resolution_type)) {
        				fs->width = sonyimx179_framesizes[i].width;
        				fs->height = sonyimx179_framesizes[i].height;
        				match = true;
        				break;
    			}
    		}
    	}
	}
	if (false == match) {
		for (i = 0; i < size; i++) {
		    if ((zsl_preview == false) && sonyimx179_framesizes[i].zsl_only)
		    {
		        continue;
		    }

			if ((sonyimx179_framesizes[i].width >= fs->width)
				    && (sonyimx179_framesizes[i].height >= fs->height)
				    && (mini_camera_get_resolution_type(fs->width, fs->height)
    				    <= sonyimx179_framesizes[i].resolution_type)
				    && (VIEW_HDR_MOVIE != sonyimx179_framesizes[i].view_type)){
					fs->width = sonyimx179_framesizes[i].width;
					fs->height = sonyimx179_framesizes[i].height;
					break;
			}
		}
	}

	if (i >= size) {
		print_error("request resolution larger than sensor's max resolution");
		return -EINVAL;
	}

	if (state == STATE_PREVIEW) {
		sonyimx179_sensor.preview_frmsize_index = i;
	} else {
		sonyimx179_sensor.capture_frmsize_index = i;
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_get_framesizes;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx179_get_framesizes(camera_state state,
				     struct v4l2_frmsize_discrete *fs)
{
	int frmsize_index;

    if(!fs) {
        return -EINVAL;
    }

	if (state == STATE_PREVIEW) {
		frmsize_index = sonyimx179_sensor.preview_frmsize_index;
	} else if (state == STATE_CAPTURE) {
		frmsize_index = sonyimx179_sensor.capture_frmsize_index;
	} else {
		return -EINVAL;
	}
	fs->width = sonyimx179_framesizes[frmsize_index].width;
	fs->height = sonyimx179_framesizes[frmsize_index].height;

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_init_isp_reg;
 * Description : load initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx179_init_isp_reg(void)
{
	int size = 0;
	mini_camera_sensor *sensor = &sonyimx179_sensor;

    size = CAMERA_MAX_SETTING_SIZE;
    if( HDR_MOVIE_ON == sensor->sensor_hdr_movie.hdrInfo.hdr_on) {
		sonyimx179_write_isp_seq(sensor->effect->hdr_movie_isp_settings, size);
	} else {
    	sonyimx179_write_isp_seq(sensor->effect->isp_settings, size);
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_support_hdr_movie;
 * Description : check sensor support hdr movie or not;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx179_support_hdr_movie(void)
{
    return HDR_MOVIE_SUPPORT;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_get_hdr_movie_switch;
 * Description : the function that get hdr movie status on or off;
 * Input       : NA;
 * Output      : the status of hdr movie status;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx179_get_hdr_movie_switch(void)
{
    return sonyimx179_sensor.sensor_hdr_movie.hdrInfo.hdr_on;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_set_hdr_movie_switch;
 * Description : the function that set hdr movie status;
 * Input       : the status of hdr movie on or off;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx179_set_hdr_movie_switch(hdr_movie_switch on)
{
	print_debug("Enter Function:%s on = %d",__func__,on);
	sonyimx179_sensor.sensor_hdr_movie.hdrInfo.hdr_on = on;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_init_reg;
 * Description : download initial seq for sensor init;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx179_init_reg(void)
{
	int size = 0;

	print_debug("Enter Function:%s  , initsize=%d",
		    __func__, sizeof(sonyimx179_init_regs));

	if (0 != mini_k3_ispio_init_csi(sonyimx179_sensor.mipi_index,
			sonyimx179_sensor.mipi_lane_count, sonyimx179_sensor.lane_clk)) {
		return -EFAULT;
	}

	size = ARRAY_SIZE(sonyimx179_init_regs);
	if (0 != sonyimx179_write_seq(sonyimx179_init_regs, size, 0x00)) {
		print_error("line %d, fail to init sonyimx179 sensor",__LINE__);
		return -EFAULT;
	}

	if(E_CAMERA_SENSOR_FLIP_TYPE_H_V == get_primary_sensor_flip_type()) {
		sonyimx179_write_reg(SONYIMX179_FLIP, 0x03, 0x00); //turn camera layout
		print_info("%s:change flip and mirror",__func__);
	}

	return 0;
}

static int sonyimx179_set_hflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);
	sonyimx179_sensor.hflip = flip;
	return 0;
}
static int sonyimx179_get_hflip(void)
{
	print_debug("enter %s", __func__);

	return sonyimx179_sensor.hflip;
}
static int sonyimx179_set_vflip(int flip)
{
	print_debug("enter %s flip=%d", __func__, flip);

	sonyimx179_sensor.vflip = flip;

	return 0;
}
static int sonyimx179_get_vflip(void)
{
	print_debug("enter %s", __func__);
	return sonyimx179_sensor.vflip;
}

static int sonyimx179_update_flip(u16 width, u16 height)
{
	u8 new_flip = ((sonyimx179_sensor.vflip << 1) | sonyimx179_sensor.hflip);

	print_debug("Enter %s  ", __func__);

	mini_k3_ispio_update_flip(( sonyimx179_sensor.old_flip^new_flip) & 0x03, width, height, PIXEL_ORDER_CHANGED);

	sonyimx179_sensor.old_flip = new_flip;

	return 0;
}
/*
 **************************************************************************
 * FunctionName: sonyimx179_framesize_switch;
 * Description : switch frame size, used by preview and capture
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
#if 0
static int sonyimx179_framesize_switch(camera_state state)
{
	u8 next_frmsize_index;

	if (state == STATE_PREVIEW)
		next_frmsize_index = sonyimx179_sensor.preview_frmsize_index;
	else
		next_frmsize_index = sonyimx179_sensor.capture_frmsize_index;

	print_debug("Enter Function:%s frm index=%d", __func__, next_frmsize_index);

	if (next_frmsize_index >= ARRAY_SIZE(sonyimx179_framesizes)){
		print_error("Unsupport sensor setting index: %d",next_frmsize_index);
		return -ETIME;
	}

	if (0 != sonyimx179_write_seq(sonyimx179_sensor.frmsize_list[next_frmsize_index].sensor_setting.setting
		,sonyimx179_sensor.frmsize_list[next_frmsize_index].sensor_setting.seq_size, 0x00)) {
		print_error("fail to init sonyimx179 sensor");
		return -ETIME;
	}

	return 0;
}
#endif
/*
 **************************************************************************
 * FunctionName: sonyimx179_stream_on;
 * Description : download preview seq for sensor preview;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
extern u32 misp_cmd_delay_time;
static int sonyimx179_stream_on(camera_state state)
{
	u8 frmsize_index;
	u8 hv_flip = 0;
	mini_camera_sensor *sensor = &sonyimx179_sensor;

	print_info("Enter Function:%s ", __func__);

	if(sensor->hflip==1)
		hv_flip |=0x01;
	if(sensor->vflip==1)
		hv_flip |=0x02;

	if (state == STATE_PREVIEW){
		frmsize_index = sensor->preview_frmsize_index;
		frmsize_index = sensor->frmsize_list[frmsize_index].mini_isp_index;
		camera_agent_set_sensormode(sensor->sensor_index, frmsize_index,hv_flip);
		msleep(10);
		camera_agent_streamonoff(sensor->sensor_index, stream_state_on);
		msleep(100);
	} else {
		frmsize_index = sensor->capture_frmsize_index;
		frmsize_index = sensor->frmsize_list[frmsize_index].mini_isp_index;
		camera_agent_take_pictures(sensor->sensor_index, frmsize_index,hv_flip,0,0);
		msleep(misp_cmd_delay_time);
	}


	return 0;
}

static int sonyimx179_stream_off(camera_state state)
{
//	u8	frmsize_index;
	int ret;

	print_info("Enter Function:%s ", __func__);

	ret = camera_agent_streamonoff(sonyimx179_sensor.sensor_index, stream_state_off);
	return ret;
}



/*  **************************************************************************
* FunctionName: sonyimx179_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int sonyimx179_check_sensor(void)
{
	u8 idl = 0;
	u8 idh = 0;
	u16 id = 0;
	int pin_id = 0;
    mini_camera_sensor *sensor = &sonyimx179_sensor;

	print_info("Enter miniisp:%s ", __func__);

	sonyimx179_read_reg(0x0016, &idh);
	sonyimx179_read_reg(0x0017, &idl);

	id = ((idh << 8) | idl);
	print_info("sonyimx179 product id:0x%x", id);

	if (SONYIMX179_CHIP_ID != id) {
		//print_error("Invalid product id ,Could not load sensor sonyimx179\n");
		//return -ENODEV;
	}
	pin_id = gpio_get_value(SONYIMX179_MODULE_ID);
	if(pin_id < 0) {
		pin_id = 0;
		print_error("sonyimx179_check_sensor fail to get gpio value!!! set pin_id to 0 by default MODULE_LITEON !\n");
	}
	sensor_module = (pin_id==0) ? MODULE_SUNNY: MODULE_LITEON;

	if(sensor_module ==  MODULE_SUNNY) {
		sonyimx179_sensor.vcm = &vcm_dw9714_Sunny;
        sensor->effect = &effect_imx179_sunny;
		snprintf(sonyimx179_sensor.info.name, sizeof(sonyimx179_sensor.info.name),"sonyimx179_sunny");
	}else {
		sonyimx179_sensor.vcm = &vcm_dw9714_Liteon;
        sensor->effect = &effect_imx179_liteon;
		snprintf(sonyimx179_sensor.info.name, sizeof(sonyimx179_sensor.info.name),"sonyimx179_liteon");
	}

	print_info("check module = %s", sonyimx179_sensor.info.name);
	return 0;
}

/****************************************************************************
* FunctionName: sonyimx179_check_sensor;
* Description : NA;
* Input       : NA;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/
static int sonyimx179_power(camera_power_state power)
{
	int ret = 0;

	print_debug("Enter Function:%s\n ", __func__);

	if(0 == get_sensor_iopower()) {
		if (power == POWER_ON) {
			/*slave camera*/
			mini_k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
			//mini_k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);
			mini_k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);
			udelay(1);
			/*main camera*/
			mini_k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
			//gpio
			gpio_direction_output(GPIO_18_0, 1);
			udelay(200);
			mini_k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
			udelay(1);
			mini_k3_ispio_ioconfig(&sonyimx179_sensor, power);
			mini_k3_ispgpio_power_sensor(&sonyimx179_sensor, power);
			msleep(3);
		} else {
			mini_k3_ispio_deinit_csi(sonyimx179_sensor.mipi_index);
			mini_k3_ispgpio_power_sensor(&sonyimx179_sensor, power);
			mini_k3_ispio_ioconfig(&sonyimx179_sensor, power);
			/*slave camera*/
			mini_k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD);
			mini_k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
			//mini_k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);
			/*main camera*/
			mini_k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
			//gpio
			gpio_direction_output(GPIO_18_0, 0);
			gpio_free(GPIO_18_0);
			udelay(200);
			mini_k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
		}
	} else {
		if (power == POWER_ON) {
			mini_k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
			//ret = camera_power_core_ldo(power);
			mini_k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);
			udelay(200);
			//mini_k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);
			mini_k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
			udelay(1);

			mini_k3_ispio_ioconfig(&sonyimx179_sensor, power);
			mini_k3_ispgpio_power_sensor(&sonyimx179_sensor, power);
			msleep(3);
		} else {
			mini_k3_ispio_deinit_csi(sonyimx179_sensor.mipi_index);
			mini_k3_ispgpio_power_sensor(&sonyimx179_sensor, power);
			mini_k3_ispio_ioconfig(&sonyimx179_sensor, power);

	        	//mini_k3_ispldo_power_sensor(power, "sec-cameralog-vcc");
			mini_k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
			mini_k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);
			//camera_power_core_ldo(power);
			udelay(200);
			mini_k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
			//mini_k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);

#ifdef DUMP_SCCTRL_ISP_REG
            mini_dump_scctrl_isp_reg();
#endif
		}
	}
	return ret;
}

static int sonyimx179_get_sensor_aperture(void)
{
	return SONYIMX179_APERTURE_FACTOR;
}

/*
 * Here gain is in unit 1/16 of sensor gain,
 * y36721 todo, temporarily if sensor gain=0x10, ISO is 100
 * in fact we need calibrate an ISO-ET-gain table.
 */
static u32 sonyimx179_gain_to_iso(int gain)
{
	return (gain * 100) / 0x10;
}

static u32 sonyimx179_iso_to_gain(int iso)
{
    return (iso * 0x10) / 100;
}

static void sonyimx179_set_gain(u32 gain)
{
	if (gain == 0)
		return;
	gain = 256 - (256 * 16) / gain;
	//sonyimx179_write_reg(SONYIMX179_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_GAIN_REG_L, gain & 0xff, 0x00);
}

static void sonyimx179_set_exposure(u32 exposure)
{
	exposure >>= 4;
	sonyimx179_write_reg(SONYIMX179_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_EXPOSURE_REG_L, exposure & 0xff, 0x00);
}


static void sonyimx179_set_exposure_gain(u32 exposure, u32 gain)
{
	u32	 tmp_digital_gain = 0;
	u8    digital_ratio = 0;
	u8    digital_h = 0;
	u8    digital_l = 0;
	u32  analog_gain = 0;
	sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold

    /*adapter isp2.2 register value*/
	exposure >>= 4; //isp2.2 exposure = register_value/0x10

	sonyimx179_write_reg(SONYIMX179_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_EXPOSURE_REG_L, exposure & 0xff, 0x00);

	if (gain == 0)
		goto out;

    //isp2.2 gain = register_value/0x10
    /*
    digital_h = (gain/SONYIMX179_MAX_ANALOG_GAIN)/16;
    digital_l = (digital_h'decimal)*256
    analog_gain = 256 - (256/(gain/16))
    */
	if(gain > SONYIMX179_MAX_ANALOG_GAIN*16)
	{
        /*tmp_digital_gain*256 is keep the decimal part*/
		tmp_digital_gain = (gain*256) >> 4;
		tmp_digital_gain = tmp_digital_gain >> 3;

		digital_ratio = (gain/SONYIMX179_MAX_ANALOG_GAIN) >> 4;
		digital_h = digital_ratio;
		digital_l = tmp_digital_gain - digital_ratio*256;
		analog_gain = SONYIMX179_MAX_ANALOG_GAIN*16;
	}
	else
	{
		analog_gain = gain;
		digital_h = 1;
		digital_l = 0;
	}

	analog_gain = 256 - (256 * 16) / analog_gain;
	sonyimx179_write_reg(SONYIMX179_GAIN_REG_L, analog_gain & 0xff, 0x00);
	sonyimx179_write_reg(DIG_GAIN_GR_H, digital_h & 0xff, 0x00);
	sonyimx179_write_reg(DIG_GAIN_GR_L, digital_l & 0xff, 0x00);
	sonyimx179_write_reg(DIG_GAIN_R_H, digital_h & 0xff, 0x00);
	sonyimx179_write_reg(DIG_GAIN_R_L, digital_l & 0xff, 0x00);
	sonyimx179_write_reg(DIG_GAIN_B_H, digital_h & 0xff, 0x00);
	sonyimx179_write_reg(DIG_GAIN_B_L, digital_l & 0xff, 0x00);
	sonyimx179_write_reg(DIG_GAIN_GB_H, digital_h & 0xff, 0x00);
	sonyimx179_write_reg(DIG_GAIN_GB_L, digital_l & 0xff, 0x00);
out:
	sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group hold
	return;
}

/****************************************************************************
* FunctionName: sonyimx179_set_awb_gain;
* Description : NA;
* Input       : R,GR,GB,B gain from isp;
* Output      : NA;
* ReturnValue : NA;
* Other       : NA;
***************************************************************************/

static void sonyimx179_set_awb_gain(u16 b_gain, u16 gb_gain, u16 gr_gain, u16 r_gain)
{

	sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
	sonyimx179_write_reg(SONYIMX179_ABS_GAIN_B_H, (b_gain >> 8) & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_ABS_GAIN_B_L, b_gain & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_ABS_GAIN_GB_H, (gb_gain >> 8) & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_ABS_GAIN_GB_L, gb_gain & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_ABS_GAIN_GR_H, (gr_gain >> 8) & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_ABS_GAIN_GR_L, gr_gain & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_ABS_GAIN_R_H, (r_gain >> 8) & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_ABS_GAIN_R_L, r_gain & 0xff, 0x00);

	sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group open
}

static void sonyimx179_set_vts(u16 vts)
{
	print_debug("Enter %s  ", __func__);
	sonyimx179_write_reg(SONYIMX179_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_VTS_REG_L, vts & 0xff, 0x00);
}

static u32 sonyimx179_get_vts_reg_addr(void)
{
	return SONYIMX179_VTS_REG_H;
}

extern u32 sensor_override_params[OVERRIDE_TYPE_MAX];
static  u32 sonyimx179_get_override_param(camera_override_type_t type)
{
	u32 ret_val = sensor_override_params[type];

	switch (type) {
	case OVERRIDE_ISO_HIGH:
		ret_val = SONYIMX179_MAX_ISO;
		break;

	case OVERRIDE_ISO_LOW:
		ret_val = SONYIMX179_MIN_ISO;
		break;

	/* increase frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_LOW2MID:
		ret_val = SONYIMX179_AUTOFPS_GAIN_LOW2MID;
		break;
	case OVERRIDE_AUTOFPS_GAIN_MID2HIGH:
		ret_val = SONYIMX179_AUTOFPS_GAIN_MID2HIGH;
		break;

	/* reduce frame rate gain threshold */
	case OVERRIDE_AUTOFPS_GAIN_MID2LOW:
		ret_val = SONYIMX179_AUTOFPS_GAIN_MID2LOW;
		break;
	case OVERRIDE_AUTOFPS_GAIN_HIGH2MID:
		ret_val = SONYIMX179_AUTOFPS_GAIN_HIGH2MID;
		break;

	case OVERRIDE_FPS_MAX:
		ret_val = SONYIMX179_MAX_FRAMERATE;
		break;

    case OVERRIDE_FPS_MID:
        ret_val = SONYIMX179_MID_FRAMERATE;
        break;

	case OVERRIDE_FPS_MIN:
		ret_val = SONYIMX179_MIN_FRAMERATE;
		break;

	case OVERRIDE_CAP_FPS_MIN:
		ret_val = SONYIMX179_MIN_CAP_FRAMERATE;
		break;

	case OVERRIDE_FLASH_TRIGGER_GAIN:
		ret_val = SONYIMX179_FLASH_TRIGGER_GAIN;
		break;

	case OVERRIDE_SHARPNESS_PREVIEW:
		ret_val = SONYIMX179_SHARPNESS_PREVIEW;
		break;

	case OVERRIDE_SHARPNESS_CAPTURE:
		ret_val = SONYIMX179_SHARPNESS_CAPTURE;
		break;

	default:
		print_error("%s:not override or invalid type %d, use default",__func__, type);
		break;
	}

	return ret_val;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_get_gain;
 * Description :get gain from sensor
 * Input       	 NA;
 * Output      	 gain value from sensor
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static u32 sonyimx179_get_gain(void)
{
	u8 gain_l = 0;
	u32 gain = 0;
	sonyimx179_read_reg(SONYIMX179_GAIN_REG_L, &gain_l);
	gain = gain_l;
	if(_IS_DEBUG_AE) {
		print_info("%s-0x0205=%x",__func__,gain_l);
	}
	return gain;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_get_exposure;
 * Description :get exposure from sensor
 * Input       	 NA;
 * Output      	 exposure value from sensor
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static u32  sonyimx179_get_exposure(void)
{
	u32 expo = 0;
	u8 expo_h = 0;
	u8 expo_l = 0;

	sonyimx179_read_reg(SONYIMX179_EXPOSURE_REG_H, &expo_h);
	sonyimx179_read_reg(SONYIMX179_EXPOSURE_REG_L, &expo_l);

	if(_IS_DEBUG_AE) {
		print_info("sonyimx179_get_exposure-0x0202=%x,0x0203=%x",expo_h,expo_l);
	}
	expo = expo_h &0xff;
	expo = expo << 8 | expo_l;
	return expo;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_set_hdr_exposure_gain;
 * Description 	   : set exposure and gain to sensor.
 * Input		   : the value of exposure and gain ,that include long exposure short exposure and long gain db ,short gain db
 		          :  gain is db but not times
 * Output      	   : NA
 * ReturnValue   : NA;
 * Other       	   : NA;
 **************************************************************************
*/

static void sonyimx179_set_hdr_exposure_gain(u32 expo_long,u16 gain_global,u32 expo_short,u16 short_gain)
{
    u16 gain_switch_long = 0;
	u16 gain_switch_short = 0;

	gain_switch_long = gain_global;
	gain_switch_short = short_gain;
	if(_IS_DEBUG_AE) {
       print_info("__debug_esen: Enter %s  gain_switch_long = %d ", __func__,gain_switch_long);
       print_info("__debug_esen: Enter %s  expo_long = %d ", __func__,expo_long);
	   print_info("__debug_esen: Enter %s  gain_switch_short = %d ", __func__,gain_switch_short);
       print_info("__debug_esen: Enter %s  expo_short = %d", __func__,expo_short);
	}

	sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
	sonyimx179_write_reg(SONYIMX179_EXPOSURE_REG_H, (expo_long >> 8) & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_EXPOSURE_REG_L, expo_long & 0xff, 0x00);
	sonyimx179_write_reg(WD_COARSE_INTEG_TIME_DS_H, (expo_short >> 8) & 0xff, 0x00);
	sonyimx179_write_reg(WD_COARSE_INTEG_TIME_DS_L, expo_short & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_GAIN_REG_L, gain_switch_long, 0x00);
	sonyimx179_write_reg(WD_ANA_GAIN_DS, gain_switch_short, 0x00);
	sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release

}

/*
 **************************************************************************
 * FunctionName: sonyimx179_set_ATR;
 * Description : turn on or off atr curve;
 * Input       : 1 turn on atr ,0 turn off atr;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/

static void sonyimx179_set_ATR(int on)
{
   if(on == 0) {//ATR off
    	sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
    	sonyimx179_write_reg(ATR_OFF_SETTING_1,0x00, 0x00);
    	sonyimx179_write_reg(ATR_OFF_SETTING_2,0x00, 0x00);
    	sonyimx179_write_reg(TRIGGER_SETTING,0x01, 0x00);
    	sonyimx179_write_reg(0x4344,0x01, 0x00);//ARNR
    	sonyimx179_write_reg(0x4364,0x0B, 0x00);
    	sonyimx179_write_reg(0x436C,0x00, 0x00);
    	sonyimx179_write_reg(0x436D,0x00, 0x00);
    	sonyimx179_write_reg(0x436E,0x00, 0x00);
    	sonyimx179_write_reg(0x436F,0x00, 0x00);
    	sonyimx179_write_reg(0x4369,0x00, 0x00);
    	sonyimx179_write_reg(0x437B,0x00, 0x00);
    	sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
    } else {//ATR on
		sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
		sonyimx179_write_reg(0x437B,0x01, 0x00);
		sonyimx179_write_reg(0x4369,0x0f, 0x00);
		sonyimx179_write_reg(0x436F,0x06, 0x00);
		sonyimx179_write_reg(0x436E,0x00, 0x00);
		sonyimx179_write_reg(0x436D,0x00, 0x00);
		sonyimx179_write_reg(0x436C,0x00, 0x00);
		sonyimx179_write_reg(0x4364,0x0B, 0x00);

		sonyimx179_write_reg(0x4344,0x01, 0x00);

		sonyimx179_write_reg(TRIGGER_SETTING,0x00, 0x00);
		sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
	}
	sonyimx179_sensor.sensor_hdr_movie.hdrInfo.atr_on = on;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_over_exposure_adjust;
 * Description :
 * Input       	:
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/

static void sonyimx179_over_exposure_adjust(int on,stats_hdr_frm * frm_stats)
{
	print_debug("enter %s  on = %d",__func__,on);
	if(on == 1)	{
		sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
		sonyimx179_write_reg(0x4470,frm_stats->frm_ave_h&0xff,0x00);//frm_ave
		sonyimx179_write_reg(0x4471,frm_stats->frm_ave_l&0xff,0x00);//frm_ave2
		sonyimx179_write_reg(0x4472,frm_stats->frm_min_h&0xff,0x00);//frm_min1
		sonyimx179_write_reg(0x4473,frm_stats->frm_min_l&0xff,0x00);//frm_min2
		sonyimx179_write_reg(0x4474,frm_stats->frm_max_h&0xff,0x00);//frm_max1
		sonyimx179_write_reg(0x4475,frm_stats->frm_max_l&0xff,0x00);//frm_max2
		sonyimx179_write_reg(0x4476,0x01,0x00);
		sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
		if(_IS_DEBUG_AE) {
			print_info(" frm_ave_h = %d,frm_ave_l =%d,frm_min_h=%d,frm_min_l=%d,frm_max_h=%d,frm_max_l=%d,",
				frm_stats->frm_ave_h,frm_stats->frm_ave_l,frm_stats->frm_min_h,frm_stats->frm_min_l,
				frm_stats->frm_max_h,frm_stats->frm_max_l);
		}
	} else {
		sonyimx179_write_reg(0x4476,0x00,0x00);
	}
	sonyimx179_sensor.sensor_hdr_movie.hdrInfo.atr_over_expo_on = on;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_set_ATR;
 * Description : turn on or off atr curve;
 * Input       : 1 turn on atr ,0 turn off atr;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/

static void sonyimx179_set_lmt_sat(u32 lmt_value, u32 sat_value)
{
	if(_IS_DEBUG_AE) {
        print_info(" Enter %s  lmt_value = %x ", __func__,lmt_value);
        print_info(" Enter %s  sat_value = %x ", __func__,sat_value);
    }

	sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
	sonyimx179_write_reg(WB_LMT_REG_H, (lmt_value >> 8) & 0xff, 0x00);
	sonyimx179_write_reg(WB_LMT_REG_L, lmt_value & 0xff, 0x00);
	sonyimx179_write_reg(AE_SAT_REG_H, (sat_value >> 8) & 0xff, 0x00);
	sonyimx179_write_reg(AE_SAT_REG_L, sat_value & 0xff, 0x00);
	sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_get_hdr_movie_ae_param;
 * Description : The ae arith in HAL get init parm from sensor by this interface.
 * Input       : the space of hdr_ae_constant_param for keeping ratio,max gain,min gain and vts;
 * Output      : the value of ratio,max gain,min gain and vts;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/

static int sonyimx179_get_hdr_movie_ae_param(hdr_ae_constant_param * hdr_ae_param)
{
	if(NULL != hdr_ae_param) {
		hdr_ae_param->hdr_ae_ratio 		= sonyimx179_sensor.sensor_hdr_movie.ae_hdr_ratio;
		hdr_ae_param->sensor_max_gain	= sonyimx179_sensor.sensor_hdr_movie.sensor_max_gain;
		hdr_ae_param->sensor_min_gain	= sonyimx179_sensor.sensor_hdr_movie.sensor_min_gain;
		hdr_ae_param->max_analog_gain	= sonyimx179_sensor.sensor_hdr_movie.sensor_max_analog_gain;
	}
	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_set_digital_gain;
 * Description : set digital gain to sensor's digital registers
 * Input       : the struct of digital_gain_st saving digital value
 * Output      : NA
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/

static void sonyimx179_set_digital_gain(digital_gain_st * digital_gain)
{
	u8 digital_gain_h = digital_gain->digital_gain_h;
	u8 digital_gain_l = digital_gain->digital_gain_l;
	if(_IS_DEBUG_AE) {
       print_info("Enter %s  digital_gain_h = %d ,digital_gain_l=%d", __func__,digital_gain_h,digital_gain_l);
	}
	sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x01 , 0x00);//group hold
	sonyimx179_write_reg(DIG_GAIN_GR_H, digital_gain_h, 0x00);
	sonyimx179_write_reg(DIG_GAIN_GR_L, digital_gain_l, 0x00);
	sonyimx179_write_reg(DIG_GAIN_R_H, digital_gain_h, 0x00);
	sonyimx179_write_reg(DIG_GAIN_R_L, digital_gain_l, 0x00);
	sonyimx179_write_reg(DIG_GAIN_B_H,digital_gain_h, 0x00);
	sonyimx179_write_reg(DIG_GAIN_B_L, digital_gain_l, 0x00);
	sonyimx179_write_reg(DIG_GAIN_GB_H, digital_gain_h, 0x00);
	sonyimx179_write_reg(DIG_GAIN_GB_L,digital_gain_l, 0x00);
	sonyimx179_write_reg(GROUP_HOLD_FUNCTION_REG, 0x00 , 0x00);//group release
}


 /*
  *************************************************************************
  * FunctionName: 	:sonyimx179_get_digital_gain;
  * Description 	: get digital gain from sensor's digital registers
  * Input			: the struct of digital_gain_st for storging digital value
  * Output			: NA;
  * ReturnValue 	: NA;
  * Other       		:
  **************************************************************************
  */

static void sonyimx179_get_digital_gain(digital_gain_st * digital_gain)
{
	u8 digital_gain_h = 0;
	u8 digital_gain_l  = 0;
	sonyimx179_read_reg(DIG_GAIN_GR_H, &digital_gain_h);
	sonyimx179_read_reg(DIG_GAIN_GR_L, &digital_gain_l);
	sonyimx179_read_reg(DIG_GAIN_R_H, &digital_gain_h);
	sonyimx179_read_reg(DIG_GAIN_R_L, &digital_gain_l);
	sonyimx179_read_reg(DIG_GAIN_B_H,&digital_gain_h);
	sonyimx179_read_reg(DIG_GAIN_B_L, &digital_gain_l);
	sonyimx179_read_reg(DIG_GAIN_GB_H, &digital_gain_h);
	sonyimx179_read_reg(DIG_GAIN_GB_L,&digital_gain_l);

	digital_gain->digital_gain_h = digital_gain_h;
	digital_gain->digital_gain_l = digital_gain_l;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_reset;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx179_reset(camera_power_state power_state)
{
	print_debug("%s  \n", __func__);

	if (POWER_ON == power_state) {
		mini_k3_isp_io_enable_mclk(MCLK_ENABLE, sonyimx179_sensor.sensor_index);
		udelay(100);
		mini_k3_ispgpio_reset_sensor(sonyimx179_sensor.sensor_index, power_state,
			      sonyimx179_sensor.power_conf.reset_valid);
		udelay(500);
	} else {
		mini_k3_ispgpio_reset_sensor(sonyimx179_sensor.sensor_index, power_state,
			      sonyimx179_sensor.power_conf.reset_valid);
		udelay(10);
		mini_k3_isp_io_enable_mclk(MCLK_DISABLE, sonyimx179_sensor.sensor_index);
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_init;
 * Description : sonyimx179 init function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : Error code indicating success or failure;
 * Other       : NA;
 **************************************************************************
*/
static int sonyimx179_init(void)
{
	static bool sonyimx179_check = false;
	int ret = 0;

    print_debug("%s  ", __func__);

	if (false == sonyimx179_check) {
		#if 0
		if (check_suspensory_camera("SONYIMX179") != 1) {
            return -ENODEV;
        }
		#endif
        sonyimx179_check = true;
    }

	if (!mini_camera_timing_is_match(0)) {
		print_error("%s: sensor timing don't match.\n", __func__);
		return -ENODEV;
	}

	if (sonyimx179_sensor.owner && !try_module_get(sonyimx179_sensor.owner)) {
		print_error("%s: try_module_get fail", __func__);
		return -ENOENT;
	}

    /* 1. M_CAMERA_IO_VDD and S_CAMERA_IO_VDD have the same power.
       2. Only power on one sensor cause leakage, so pri-sensor and sec-sensor
          power on at the same time. Then pull down sec-sensor's PWDN/RESET GPIO for low power.
    */
	//if(E_CAMERA_SENSOR_FLIP_TYPE_H_V == get_primary_sensor_flip_type())
	//	sonyimx179_sensor.sensor_rgb_type = SENSOR_BGGR;
	//else
	//	sonyimx179_sensor.sensor_rgb_type = SENSOR_RGGB;
	sonyimx179_sensor.old_flip = 0;
	if(0 == get_sensor_iopower()) {
      /*slave camera*/
		mini_k3_ispio_power_init(S_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	//analog 2.85V - sec camera
      //	k3_ispio_power_init(S_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);	//io 1.8V - sec camera
		mini_k3_ispio_power_init(S_CAMERA_CORE_VDD, LDO_VOLTAGE_12V, LDO_VOLTAGE_12V); //core 1.2V - sec camera
      /*main camera*/
		mini_k3_ispio_power_init(M_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - pri camera*/
    	mini_k3_ispio_power_init(M_CAMERA_VCM_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*AF 2.85V - pri camera*/
	    //core gpio 18_0
	    ret = gpio_request(GPIO_18_0, NULL);
	    if (ret) {
		     print_error("failed to request dcdc core for imx179");
	    }

	} else {
		mini_k3_ispio_power_init(M_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - pri camera*/
		//k3_ispio_power_init(M_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);		/*IO 1.8V - pri camera*/
		mini_k3_ispio_power_init(M_CAMERA_VCM_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*AF 2.85V - pri camera*/
		mini_k3_ispio_power_init(M_CAMERA_CORE_VDD, LDO_VOLTAGE_10V, LDO_VOLTAGE_10V);	/*core 1.05V - pri camera*/
	}

	return 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_exit;
 * Description : sonyimx179 exit function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx179_exit(void)
{
	print_debug("enter %s", __func__);

	mini_k3_ispio_power_deinit();

	if (sonyimx179_sensor.owner) {
		module_put(sonyimx179_sensor.owner);
	}
	print_debug("exit %s", __func__);
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_shut_down;
 * Description : sonyimx179 shut down function;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx179_shut_down(void)
{
	print_debug("enter %s", __func__);
	mini_k3_ispgpio_power_sensor(&sonyimx179_sensor, POWER_OFF);
}

static void sonyimx179_get_flash_awb(flash_platform_t type, mini_awb_gain_t *flash_awb)
{
	*flash_awb = flash_platform_awb[0];
	print_info("sonyimx179_get_flash_awb: type 0x%x,", type);
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_set_hdr_default;
 * Description : init hdr;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx179_set_hdr_default(void)
{
    sonyimx179_sensor.sensor_hdr_movie.ae_hdr_ratio = 8;

    sonyimx179_sensor.sensor_hdr_movie.set_ATR_switch = sonyimx179_set_ATR;
    sonyimx179_sensor.sensor_hdr_movie.set_hdr_exposure_gain = sonyimx179_set_hdr_exposure_gain;
    sonyimx179_sensor.sensor_hdr_movie.support_hdr_movie = sonyimx179_support_hdr_movie;
    sonyimx179_sensor.sensor_hdr_movie.get_hdr_movie_switch = sonyimx179_get_hdr_movie_switch;
    sonyimx179_sensor.sensor_hdr_movie.set_hdr_movie_switch = sonyimx179_set_hdr_movie_switch;
    sonyimx179_sensor.sensor_hdr_movie.over_exposure_adjust = sonyimx179_over_exposure_adjust;
    sonyimx179_sensor.sensor_hdr_movie.set_lmt_sat = sonyimx179_set_lmt_sat;
    sonyimx179_sensor.sensor_hdr_movie.get_hdr_movie_ae_param = sonyimx179_get_hdr_movie_ae_param;
    sonyimx179_sensor.sensor_hdr_movie.set_digital_gain = sonyimx179_set_digital_gain;
    sonyimx179_sensor.sensor_hdr_movie.get_digital_gain = sonyimx179_get_digital_gain;
    sonyimx179_sensor.sensor_hdr_movie.set_awb_gain = sonyimx179_set_awb_gain;

    sonyimx179_sensor.sensor_hdr_movie.hdrInfo.atr_on = ATR_ON;
    sonyimx179_sensor.sensor_hdr_movie.hdrInfo.hdr_on = HDR_MOVIE_OFF;
    sonyimx179_sensor.sensor_hdr_movie.stats_data.stats_h =1024;
	sonyimx179_sensor.sensor_hdr_movie.stats_data.stats_v =2;
    sonyimx179_sensor.sensor_hdr_movie.sensor_max_gain =32;
    sonyimx179_sensor.sensor_hdr_movie.sensor_max_analog_gain = 8;
    sonyimx179_sensor.sensor_hdr_movie.sensor_min_gain =1;
    sonyimx179_sensor.sensor_hdr_movie.ae_arithmatic_switch_gain = 0;
    sonyimx179_sensor.sensor_hdr_movie.stats_diff_threshold = 0;
    sonyimx179_sensor.sensor_hdr_movie.stats_max_threshold = 0;
    sonyimx179_sensor.sensor_hdr_movie.ae_target_low = 0;
    sonyimx179_sensor.sensor_hdr_movie.ae_target_high = 0;

    sonyimx179_sensor.sensor_hdr_movie.gain_switch = 0;
    sonyimx179_sensor.sensor_hdr_movie.gain_interval = 0;
    sonyimx179_sensor.sensor_hdr_movie.gain_switch2 = 0;
    sonyimx179_sensor.sensor_hdr_movie.gain_interval2 = 0;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_set_default;
 * Description : init sonyimx179_sensor;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
*/
static void sonyimx179_set_default(void)
{
    sonyimx179_sensor.init = sonyimx179_init;
	sonyimx179_sensor.exit = sonyimx179_exit;
	sonyimx179_sensor.shut_down = sonyimx179_shut_down;
	sonyimx179_sensor.reset = sonyimx179_reset;
	sonyimx179_sensor.check_sensor = sonyimx179_check_sensor;
	sonyimx179_sensor.power = sonyimx179_power;
	sonyimx179_sensor.init_reg = sonyimx179_init_reg;
	sonyimx179_sensor.stream_on = sonyimx179_stream_on;
	sonyimx179_sensor.stream_off = sonyimx179_stream_off;

	sonyimx179_sensor.get_format = sonyimx179_get_format;
	sonyimx179_sensor.set_flash = NULL;
	sonyimx179_sensor.get_flash = NULL;
	sonyimx179_sensor.set_scene = NULL;
	sonyimx179_sensor.get_scene = NULL;

	sonyimx179_sensor.enum_framesizes = sonyimx179_enum_framesizes;
	sonyimx179_sensor.try_framesizes = sonyimx179_try_framesizes;
	sonyimx179_sensor.set_framesizes = sonyimx179_set_framesizes;
	sonyimx179_sensor.get_framesizes = sonyimx179_get_framesizes;

	sonyimx179_sensor.enum_frame_intervals = sonyimx179_enum_frame_intervals;
	sonyimx179_sensor.try_frame_intervals = NULL;
	sonyimx179_sensor.set_frame_intervals = NULL;
	sonyimx179_sensor.get_frame_intervals = NULL;

	sonyimx179_sensor.get_vts_reg_addr = sonyimx179_get_vts_reg_addr;

	sonyimx179_sensor.get_capability = sonyimx179_get_capability;

	sonyimx179_sensor.set_hflip = sonyimx179_set_hflip;
	sonyimx179_sensor.get_hflip = sonyimx179_get_hflip;
	sonyimx179_sensor.set_vflip = sonyimx179_set_vflip;
	sonyimx179_sensor.get_vflip = sonyimx179_get_vflip;
	sonyimx179_sensor.update_flip = sonyimx179_update_flip;

	strncpy(sonyimx179_sensor.info.name,"sonyimx179",sizeof(sonyimx179_sensor.info.name));
	sonyimx179_sensor.interface_type = MIPI1;
	sonyimx179_sensor.mipi_lane_count = CSI_LINES_4;
	sonyimx179_sensor.mipi_index = CSI_INDEX_0;
	sonyimx179_sensor.sensor_index = CAMERA_SENSOR_SECONDARY;
	sonyimx179_sensor.skip_frames = 4;//sonyimx179_sensor.skip_frames = 1;

	sonyimx179_sensor.power_conf.pd_valid = LOW_VALID;
	sonyimx179_sensor.power_conf.reset_valid = LOW_VALID;
	sonyimx179_sensor.power_conf.vcmpd_valid = LOW_VALID;

	sonyimx179_sensor.i2c_config.index = I2C_PRIMARY;
	sonyimx179_sensor.i2c_config.speed = I2C_SPEED_400;
	sonyimx179_sensor.i2c_config.addr = SONYIMX179_SLAVE_ADDRESS;
	sonyimx179_sensor.i2c_config.addr_bits = I2C_16BIT;
	sonyimx179_sensor.i2c_config.val_bits = I2C_8BIT;

	sonyimx179_sensor.preview_frmsize_index = 0;
	sonyimx179_sensor.capture_frmsize_index = 0;
	sonyimx179_sensor.frmsize_list = sonyimx179_framesizes;
	sonyimx179_sensor.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW10;
	sonyimx179_sensor.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW10;

#ifdef SONYIMX179_AP_WRITEAE_MODE /* just an example and test case for AP write AE mode */
	sonyimx179_sensor.aec_addr[0] = 0;
	sonyimx179_sensor.aec_addr[1] = 0;
	sonyimx179_sensor.aec_addr[2] = 0;
	sonyimx179_sensor.agc_addr[0] = 0;
	sonyimx179_sensor.agc_addr[1] = 0;
	sonyimx179_sensor.ap_writeAE_delay = 6000; /* 5 expo and gain registers, 6000 us is enough */
#else
	sonyimx179_sensor.aec_addr[0] = 0x0000;
	sonyimx179_sensor.aec_addr[1] = 0x0202;
	sonyimx179_sensor.aec_addr[2] = 0x0203;
	sonyimx179_sensor.agc_addr[0] = 0x0000; /*0x0204 high byte not needed*/
	sonyimx179_sensor.agc_addr[1] = 0x0205;
#endif
	sonyimx179_sensor.sensor_type = SENSOR_SONY;
	sonyimx179_sensor.sensor_rgb_type = SENSOR_RGGB;

	sonyimx179_sensor.set_gain = sonyimx179_set_gain;
	sonyimx179_sensor.set_exposure = sonyimx179_set_exposure;
	sonyimx179_sensor.set_exposure_gain = sonyimx179_set_exposure_gain;
	sonyimx179_sensor.set_vts = sonyimx179_set_vts;

	sonyimx179_sensor.get_override_param = sonyimx179_get_override_param;

	sonyimx179_sensor.sensor_gain_to_iso = sonyimx179_gain_to_iso;
	sonyimx179_sensor.sensor_iso_to_gain = sonyimx179_iso_to_gain;

	sonyimx179_sensor.get_sensor_aperture = sonyimx179_get_sensor_aperture;
	sonyimx179_sensor.get_equivalent_focus = NULL;

	sonyimx179_sensor.set_effect = NULL;

	sonyimx179_sensor.isp_location = CAMERA_USE_K3ISP;
	sonyimx179_sensor.sensor_tune_ops = NULL;

	sonyimx179_sensor.af_enable = 0;
	sonyimx179_sensor.get_flash_awb = sonyimx179_get_flash_awb;

	sonyimx179_sensor.image_setting.lensc_param = sonyimx179_lensc_param;
	sonyimx179_sensor.image_setting.ccm_param = sonyimx179_ccm_param;
	sonyimx179_sensor.image_setting.awb_param = sonyimx179_awb_param;
	sonyimx179_sensor.fps_max = 30;
	sonyimx179_sensor.fps_min = 15;
	sonyimx179_sensor.fps = 25;
	sonyimx179_sensor.owner = THIS_MODULE;

	sonyimx179_sensor.info.facing = CAMERA_FACING_FRONT;
	sonyimx179_sensor.info.orientation = 270;
	sonyimx179_sensor.info.focal_length = 296;	/* 2.96mm */
	sonyimx179_sensor.info.h_view_angle = 75;	/*  66.1 degree */
	sonyimx179_sensor.info.v_view_angle = 75;
	sonyimx179_sensor.lane_clk = CLK_750M;
	sonyimx179_sensor.hflip = 0;
	sonyimx179_sensor.vflip = 0;
	sonyimx179_sensor.old_flip = 0;

	sonyimx179_sensor.get_gain     				= sonyimx179_get_gain;
	sonyimx179_sensor.get_exposure   			= sonyimx179_get_exposure;
	sonyimx179_sensor.init_isp_reg 				= sonyimx179_init_isp_reg;
	sonyimx179_sensor.support_summary = false;
    sonyimx179_sensor.get_ccm_pregain = NULL;
    sonyimx179_sensor.set_awb = NULL;
    sonyimx179_sensor.set_anti_banding = NULL;
    sonyimx179_sensor.update_framerate = NULL;
    sonyimx179_sensor.awb_dynamic_ccm_gain = NULL;
    sonyimx179_sensor.pclk = 0;
    sonyimx179_sensor.max_int_lines = 0;
    sonyimx179_sensor.min_int_lines = 0;
    sonyimx179_sensor.real_int_lines = 0;
    sonyimx179_sensor.min_gain = 0;
    sonyimx179_sensor.max_gain = 0;
    sonyimx179_sensor.real_gain = 0;
    sonyimx179_sensor.rcc_enable = false;
    sonyimx179_set_hdr_default();
    sonyimx179_sensor.isp_idi_skip = false;
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_module_init;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static __init int sonyimx179_module_init(void)
{
	u32 val;
	if(get_hw_config_int("camera/miniisp", &val, NULL)!=true)
		return -1;
	if(val != 1)
		return -1;
	sonyimx179_set_default();
	return mini_register_camera_sensor(sonyimx179_sensor.sensor_index, &sonyimx179_sensor);
}

/*
 **************************************************************************
 * FunctionName: sonyimx179_module_exit;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void __exit sonyimx179_module_exit(void)
{
	mini_unregister_camera_sensor(sonyimx179_sensor.sensor_index, &sonyimx179_sensor);
}

MODULE_AUTHOR("Hisilicon");
module_init(sonyimx179_module_init);
module_exit(sonyimx179_module_exit);
MODULE_LICENSE("GPL");

/********************************** END **********************************************/


