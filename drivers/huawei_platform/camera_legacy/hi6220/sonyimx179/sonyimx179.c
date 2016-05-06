/*
 *  sonyimx179 camera driver head file
 *
 *  Author: 	
 *  Date:  	    2013/10/28
 *  Version:	1.0
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
#include <asm/bug.h>
#include <mach/hisi_mem.h>
#include <mach/hardware.h>
#include <mach/boardid.h>
#include <mach/gpio.h>
#include <mach/pmussi_drv.h>
#include "drv_regulator_user.h"
#include "hsad/config_interface.h"
#include "sensor_common.h"
#include "sonyimx179.h"
#include "effect.h"

#define LOG_TAG "SONYIMX179"
#include "cam_log.h"
#include "cam_util.h"

#define SONYIMX179_AP_WRITEAE_MODE

#define SONYIMX179_ZSL                   (0x00) //(1 << CAMERA_ZSL_OFF) 
#define SONYIMX179_CHIP_ID               (0xa00)
#define SONYIMX179_SLAVE_ADDRESS         (0x20)
#define SONYIMX179_MODULE_ID             (GPIO_18_4) //sunny or liteon

/*exposure*/
#define SONYIMX179_EXPOSURE_REG_H        (0x0202) //coarse_integration_time
#define SONYIMX179_EXPOSURE_REG_L        (0x0203)

/*analogue gain & digital gain*/
#define SONYIMX179_MAX_ANALOG_GAIN       (8)
#define SONYIMX179_ANA_GAIN_GLOBAL       (0x0205) //analogue_gain_code_global
#define SONYIMX179_DIG_GAIN_GR_H         (0x020E) //digital_gain_greenR
#define SONYIMX179_DIG_GAIN_GR_L         (0x020F)
#define SONYIMX179_DIG_GAIN_R_H          (0x0210) //digital_gain_red
#define SONYIMX179_DIG_GAIN_R_L          (0x0211)
#define SONYIMX179_DIG_GAIN_B_H          (0x0212) //digital_gain_blue
#define SONYIMX179_DIG_GAIN_B_L          (0x0213)
#define SONYIMX179_DIG_GAIN_GB_H         (0x0214) //digital_gain_greenB
#define SONYIMX179_DIG_GAIN_GB_L         (0x0215)

/*image_orientation*/
#define SONYIMX179_FLIP		             (0x0101)

/*grouped_parameter_hold*/
#define SONYIMX179_GROUP_HOLD_REG        (0x0104)

/*Frame Timing Registers*/
#define SONYIMX179_VTS_REG_H		     (0x0340) //frame_length_lines
#define SONYIMX179_VTS_REG_L		     (0x0341)

/* support 3 level framerate now, if mid fps same as min, set to 2 level framerate */
#define SONYIMX179_AUTOFPS_GAIN_HIGH2MID (0x24)
#define SONYIMX179_AUTOFPS_GAIN_MID2LOW	 (0x24)
#define SONYIMX179_AUTOFPS_GAIN_LOW2MID	 (0x60)
#define SONYIMX179_AUTOFPS_GAIN_MID2HIGH (0x60)
#define SONYIMX179_MAX_FRAMERATE         (30)
#define SONYIMX179_MID_FRAMERATE		 (15)
#define SONYIMX179_MIN_FRAMERATE         (10)
#define SONYIMX179_MIN_CAP_FRAMERATE     (8)

#define SONYIMX179_APERTURE_FACTOR       (200) //F2.0

/*iso*/
#define SONYIMX179_MAX_ISO               (1550)
#define SONYIMX179_MIN_ISO               (100)

#define SONYIMX179_FLASH_TRIGGER_GAIN    (0xff)

/*sharpness*/
#define SONYIMX179_SHARPNESS_PREVIEW     (0x30)
#define SONYIMX179_SHARPNESS_CAPTURE     (0x08)

#define SONYIMX179_I2C_RETRY_TIMES       (5)

#ifdef IMX179_OTP
/*otp status*/
#define SONYIMX179_OTP_MODE              (0x3380)
#define SONYIMX179_OTP_CTRL              (0x3400)
#define SONYIMX179_OTP_STATUS            (0x3401)
#define SONYIMX179_OTP_PAGE_SLECT        (0x3402)

/*otp reg*/
#define SONYIMX179_OTP_MODULE_ID         (0x3404)
#define SONYIMX179_OTP_AWB_REG           (0x3409)

/*otp flag*/
#define SONYIMX179_OTP_READY             (1<<0)
#define SONYIMX179_OTP_READ_ID_AWB       (1<<1)

/*golden data*/
/*====================need to check=================================================*/
#define GOLDEN_RG_RATIO                  (0x26e)
#define GOLDEN_BG_RATIO                  (0x2e9)

/*sonyimx179 otp data*/
#define MAX_OTP_MODULE_INFO  5
#define MAX_OTP_AWB_DATA     6
typedef struct _otp_data {
    u8 moduleInfo[MAX_OTP_MODULE_INFO]; //module info:year,month,date,cameraid,moduleid
    u8 awbData[MAX_OTP_AWB_DATA]; //awb:rgh,rgl,bgh,bgl,gbgrh,gbgrl
}otp_data;

static u8 sonyimx179_otp_flag = 0;
static otp_data sonyimx179_otp = {0};
static void sonyimx179_otp_get_data(void);
static void sonyimx179_otp_set_awb(void);
#endif

char sonyimx179_lensc_param[86*3] = {
};

short sonyimx179_ccm_param[54] = {
};

char sonyimx179_awb_param[] = {
};


static framesize_s sonyimx179_framesizes[] = {
    /* 1600x1200, 30fps quarter size */
	{0, 0, 1600, 1200, 3440, 1712, 30, 30, 0x201, 0x1AB, 0x24F, VIEW_FULL, RESOLUTION_4_3, true, false,{sonyimx179_framesize_1600x1200, ARRAY_SIZE(sonyimx179_framesize_1600x1200)} }, 

	/* 3264x2448, 15fps full size */
	{0, 0, 3264, 2448, 3440, 3424, 15, 15, 0x201, 0x1AB, 0x24F, VIEW_FULL, RESOLUTION_4_3, false, false, {sonyimx179_framesize_3264x2448, ARRAY_SIZE(sonyimx179_framesize_3264x2448)} },
};

static camera_capability sonyimx179_cap[] = {
    {V4L2_CID_FOCAL_LENGTH, 341},//3.406mm
    {V4L2_CID_ZSL, SONYIMX179_ZSL},
};

/*efect parameter*/
static effect_params effect_imx179_sunny = {
    #include "effect_imx179_sunny.h"
};

static effect_params effect_imx179_liteon = {
    #include "effect_imx179_liteon.h"
};

static camera_sensor sonyimx179_sensor;

/*read sonyimx179 reg by i2c*/
static int sonyimx179_read_reg(u16 reg, u8 *val)
{
    return k3_ispio_read_reg(sonyimx179_sensor.i2c_config.index, sonyimx179_sensor.i2c_config.addr, reg, 
        (u16*)val, sonyimx179_sensor.i2c_config.val_bits, sonyimx179_sensor.i2c_config.addr_bits);
}

/*write sonyimx179 reg by i2c*/
static int sonyimx179_write_reg(u16 reg, u8 val, u8 mask)
{
    return k3_ispio_write_reg(sonyimx179_sensor.i2c_config.index, sonyimx179_sensor.i2c_config.addr, reg, 
        (u16)val, sonyimx179_sensor.i2c_config.val_bits, mask, sonyimx179_sensor.i2c_config.addr_bits);
}

/*write sequeuence to select I2C though isp command set*/
static int sonyimx179_write_seq(const struct _sensor_reg_t *seq, u32 size, u8 mask)
{
    return k3_ispio_write_seq(sonyimx179_sensor.i2c_config.index, sonyimx179_sensor.i2c_config.addr, 
        seq, size, sonyimx179_sensor.i2c_config.val_bits, mask,sonyimx179_sensor.i2c_config.addr_bits);
}

/*sonyimx179 init function*/
static int sonyimx179_init(void)
{
	int ret;
    print_debug("Enter %s.\n", __func__);
    if (check_suspensory_camera("SONYIMX179") != 1) {
        print_error("%s: can't find sonyimx179.\n", __func__);
        return -ENODEV;     
    }
	if (sonyimx179_sensor.owner && !try_module_get(sonyimx179_sensor.owner)) {
		print_error("%s: try_module_get fail.\n", __func__);
		return -ENOENT;
	}
    /*main & slave use the same power*/
    if(0 == get_sensor_iopower()) {
        /*slave camera*/
        k3_ispio_power_init(S_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	//analog 2.85V - sec camera
    	k3_ispio_power_init(S_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);	//io 1.8V - sec camera
    	k3_ispio_power_init(S_CAMERA_CORE_VDD, LDO_VOLTAGE_12V, LDO_VOLTAGE_12V); //core 1.2V - sec camera
        /*main camera*/
        k3_ispio_power_init(M_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - pri camera*/
    	k3_ispio_power_init(M_CAMERA_VCM_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*AF 2.85V - pri camera*/
	//core gpio 18_0
	ret = gpio_request(GPIO_18_0, NULL);
	if (ret) {
		print_error("failed to request dcdc core for imx179");
	}
    } else { //main & slave use the different power
    	k3_ispio_power_init(S_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	//analog 2.85V - sec camera
    	k3_ispio_power_init(S_CAMERA_CORE_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V); //core 1.8V - sec camera
    }
	return 0;
}

/*sonyimx179 exit function*/
static void sonyimx179_exit(void)
{
	print_debug("Enter %s.\n", __func__);
	k3_ispio_power_deinit();
	if (sonyimx179_sensor.owner) {
        module_put(sonyimx179_sensor.owner);
	}
}

/*sonyimx179 shut down function*/
static void sonyimx179_shut_down(void)
{
	print_debug("Enter %s.\n", __func__);  
	k3_ispgpio_power_sensor(&sonyimx179_sensor, POWER_OFF);
}

/*sonyimx179 reset function*/
static int sonyimx179_reset(camera_power_state power_state)
{
	print_debug("Enter %s.\n", __func__);
	if (POWER_ON == power_state) {
		k3_isp_io_enable_mclk(MCLK_ENABLE, sonyimx179_sensor.sensor_index);
		udelay(100);
		k3_ispgpio_reset_sensor(sonyimx179_sensor.sensor_index, power_state, sonyimx179_sensor.power_conf.reset_valid);
		udelay(500);
	} else {
		k3_ispgpio_reset_sensor(sonyimx179_sensor.sensor_index, power_state, sonyimx179_sensor.power_conf.reset_valid);
		udelay(10);
		k3_isp_io_enable_mclk(MCLK_DISABLE, sonyimx179_sensor.sensor_index);
	}
	return 0;
}

/*sonyimx179 power up function*/
static int sonyimx179_power(camera_power_state power)
{
	print_debug("Enter %s.\n", __func__);
    /*main & slave use the same power*/
	if(0 == get_sensor_iopower()) {
		if (power == POWER_ON) {
			/*slave camera*/
			k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
			k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);
			k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD); 
			udelay(1);
			/*main camera*/
			k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
			//gpio
			gpio_direction_output(GPIO_18_0, 1);
			udelay(200);
			k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
			udelay(1);
			k3_ispio_ioconfig(&sonyimx179_sensor, power);
			k3_ispgpio_power_sensor(&sonyimx179_sensor, power);
			msleep(3);
		} else {
			k3_ispio_deinit_csi(sonyimx179_sensor.mipi_index);
			k3_ispgpio_power_sensor(&sonyimx179_sensor, power);
			k3_ispio_ioconfig(&sonyimx179_sensor, power);
			/*slave camera*/
			k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD); 
			k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
			k3_ispldo_power_sensor(power, S_CAMERA_IO_VDD);
			/*main camera*/
			k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
			//gpio
			gpio_direction_output(GPIO_18_0, 0);
			gpio_free(GPIO_18_0);
			udelay(200);
			k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
		}
	} else { //main & slave use the different power
        if (power == POWER_ON) {
    		k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
		k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD); 
		udelay(1);
		k3_ispio_ioconfig(&sonyimx179_sensor, power);
		k3_ispgpio_power_sensor(&sonyimx179_sensor, power);
		msleep(3);
    	} else {
		k3_ispio_deinit_csi(sonyimx179_sensor.mipi_index);
		k3_ispgpio_power_sensor(&sonyimx179_sensor, power);
		k3_ispio_ioconfig(&sonyimx179_sensor, power);
		k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD); 
		k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
    	}
    }
	return 0;
}

/*sonyimx179 check sensor state function*/
static int sonyimx179_check_sensor(void)
{
	u8 idl = 0;
	u8 idh = 0;
	u16 id = 0;
    int moduleid = 0;
    int retry = 0;

    for(retry = 0; retry < SONYIMX179_I2C_RETRY_TIMES; retry++) {
    	sonyimx179_read_reg(0x0016, &idh);
    	sonyimx179_read_reg(0x0017, &idl);

    	id = ((idh << 8) | idl);
    	print_info("sonyimx179 product id:0x%x, retrytimes:%d.\n", id, retry);
        if (SONYIMX179_CHIP_ID == id) {
            break;
        }
        udelay(100);
    }

	if (SONYIMX179_CHIP_ID != id) {
		print_error("Invalid product id ,Could not load sensor sonyimx179.\n");
		return -ENODEV;
	}

    moduleid = gpio_get_value(SONYIMX179_MODULE_ID);
	if(moduleid < 0) {
		moduleid = 0;
		print_error("%s fail to get gpio value!!! set pin_id to 0 by default sunny module!\n", __func__);
	}

	if(moduleid > 0) { //liteon module
        sonyimx179_sensor.effect = &effect_imx179_liteon;  
		snprintf(sonyimx179_sensor.info.name, sizeof(sonyimx179_sensor.info.name),"sonyimx179_liteon");
	} else { //sunny module
        sonyimx179_sensor.effect = &effect_imx179_sunny;
		snprintf(sonyimx179_sensor.info.name, sizeof(sonyimx179_sensor.info.name),"sonyimx179_sunny");
	}
#ifdef IMX179_OTP
    sonyimx179_otp_get_data();
#endif
	return 0;
}

/*download initial seq for sensor init*/
static int sonyimx179_init_reg(void)
{
	print_debug("Enter %s.\n", __func__);
	if (0 != k3_ispio_init_csi(sonyimx179_sensor.mipi_index, sonyimx179_sensor.mipi_lane_count, sonyimx179_sensor.lane_clk)) {
		return -EFAULT;
	}
	if (0 != sonyimx179_write_seq(sonyimx179_init_regs, ARRAY_SIZE(sonyimx179_init_regs), 0x00)) {
		print_error("%s fail to init sonyimx179 sensor.\n", __func__);
		return -EFAULT;
	}
#ifdef IMX179_OTP
    sonyimx179_otp_set_awb();
#endif
	return 0;
}

/*set sensor effect reg to isp*/
static int sonyimx179_init_isp_reg(void)
{    
    k3_ispio_write_isp_seq(sonyimx179_sensor.effect->isp_settings, CAMERA_MAX_SETTING_SIZE);
	return 0;
}

/*download preview seq for sensor preview*/
static int sonyimx179_stream_on(camera_state state)
{
	u8 next_frmsize_index = (state == STATE_PREVIEW) ? sonyimx179_sensor.preview_frmsize_index : sonyimx179_sensor.capture_frmsize_index;
	print_debug("Enter %s frm index=%d.\n", __func__, next_frmsize_index);
	if (next_frmsize_index >= ARRAY_SIZE(sonyimx179_framesizes)){
		print_error("Unsupport sensor setting index: %d",next_frmsize_index);
		return -EINVAL;
	}
	if (0 != sonyimx179_write_seq(sonyimx179_sensor.frmsize_list[next_frmsize_index].sensor_setting.setting,
                sonyimx179_sensor.frmsize_list[next_frmsize_index].sensor_setting.seq_size, 0x00)) {
		print_error("fail to init sonyimx179 sensor");
		return -EINVAL;
	}
	return 0;
}

/*sonyimx179_set_hflip*/
static int sonyimx179_set_hflip(int flip)
{
	print_debug("Enter %s flip=%d.\n", __func__, flip);
	sonyimx179_sensor.hflip = flip;
	return 0;
}

/*sonyimx179_get_hflip*/
static int sonyimx179_get_hflip(void)
{
	print_debug("Enter %s.\n", __func__);
	return sonyimx179_sensor.hflip;
}

/*sonyimx179_set_vflip*/
static int sonyimx179_set_vflip(int flip)
{
	print_debug("Enter %s flip=%d.\n", __func__, flip);
	sonyimx179_sensor.vflip = flip;
	return 0;
}

/*sonyimx179_get_vflip*/
static int sonyimx179_get_vflip(void)
{
	return sonyimx179_sensor.vflip;
}

/*sonyimx179_update_flip*/
static int sonyimx179_update_flip(u16 width, u16 height)
{
	u8 new_flip = ((sonyimx179_sensor.vflip << 1) | sonyimx179_sensor.hflip);
	
	print_debug("Enter %s.\n", __func__);	
	k3_ispio_update_flip(( sonyimx179_sensor.old_flip^new_flip) & 0x03, width, height, PIXEL_ORDER_CHANGED);

	sonyimx179_sensor.old_flip = new_flip;
	sonyimx179_write_reg(SONYIMX179_FLIP, sonyimx179_sensor.vflip ? 0x02 : 0x00, ~0x02);
	sonyimx179_write_reg(SONYIMX179_FLIP, sonyimx179_sensor.hflip ? 0x01 : 0x00, ~0x01);
	return 0;
}

/*sonyimx179_get_format*/
static int sonyimx179_get_format(struct v4l2_fmtdesc *fmt)
{
    if(!fmt) {
        return -EINVAL;
    }
    print_debug("Enter %s.\n", __func__);
	if (fmt->type == V4L2_BUF_TYPE_VIDEO_OVERLAY) {
		fmt->pixelformat = sonyimx179_sensor.fmt[STATE_PREVIEW];
	} else {
		fmt->pixelformat = sonyimx179_sensor.fmt[STATE_CAPTURE];
	}
	return 0;
}

/*sonyimx179_enum_framesizes*/
static int sonyimx179_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 this_max_index = ARRAY_SIZE(sonyimx179_framesizes) - 1;

    if(!framesizes) {
        return -EINVAL;
    }
	print_debug("Enter %s.\n", __func__);
	if (framesizes->index > ARRAY_SIZE(camera_framesizes) - 1) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}
	if ((camera_framesizes[framesizes->index].width > sonyimx179_framesizes[this_max_index].width)
		|| (camera_framesizes[framesizes->index].height > sonyimx179_framesizes[this_max_index].height)) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}
	framesizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	framesizes->discrete.width = sonyimx179_framesizes[this_max_index].width;
	framesizes->discrete.height = sonyimx179_framesizes[this_max_index].height;
	return 0;
}

/*sonyimx179_try_framesizes*/
static int sonyimx179_try_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	int max_index = ARRAY_SIZE(sonyimx179_framesizes) - 1;

    if(!framesizes) {
        return -EINVAL;
    }
	print_debug("Enter %s.\n", __func__);

	if ((framesizes->discrete.width <= sonyimx179_framesizes[max_index].width)
	    && (framesizes->discrete.height <= sonyimx179_framesizes[max_index].height)) {
		print_debug("width = %d, height = %d", framesizes->discrete.width, framesizes->discrete.height);
		return 0;
	}

	print_error("frame size too large, [%d,%d]", framesizes->discrete.width, framesizes->discrete.height);
	return -EINVAL;
}

/*sonyimx179_set_framesizes,flag=1, set framesize to sensor,flag=0, only store framesize to camera_interface*/
static int sonyimx179_set_framesizes(camera_state state, struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type, bool zsl_preview)
{
	int i = 0;
	bool match = false;
	int size = ARRAY_SIZE(sonyimx179_framesizes);
    if(!fs) {
        return -EINVAL;
    }
	print_info("Enter %s State(%d), flag=%d, width=%d, height=%d", __func__, state, flag, fs->width, fs->height);
	if (VIEW_FULL == view_type) {
		for (i = 0; i < size; i++) {
			if ((sonyimx179_framesizes[i].width >= fs->width)
			    && (sonyimx179_framesizes[i].height >= fs->height)
			    && (VIEW_FULL == sonyimx179_framesizes[i].view_type)
			    && (camera_get_resolution_type(fs->width, fs->height) <= sonyimx179_framesizes[i].resolution_type)) {
    				fs->width = sonyimx179_framesizes[i].width;
    				fs->height = sonyimx179_framesizes[i].height;
    				match = true;
    				break;
			}
		}
	}
	if (false == match) {
		for (i = 0; i < size; i++) {
			if ((sonyimx179_framesizes[i].width >= fs->width)
			    && (sonyimx179_framesizes[i].height >= fs->height)
			    && (camera_get_resolution_type(fs->width, fs->height) <= sonyimx179_framesizes[i].resolution_type)) {
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

/*sonyimx179_get_framesizes*/
static int sonyimx179_get_framesizes(camera_state state, struct v4l2_frmsize_discrete *fs)
{
	int frmsize_index = (state == STATE_PREVIEW) ? sonyimx179_sensor.preview_frmsize_index : sonyimx179_sensor.capture_frmsize_index;

    if(!fs) {
        return -EINVAL;
    }
    print_debug("Enter %s.\n", __func__);
	fs->width = sonyimx179_framesizes[frmsize_index].width;
	fs->height = sonyimx179_framesizes[frmsize_index].height;
	return 0;
}

/*sonyimx179_enum_frame_intervals*/
static int sonyimx179_enum_frame_intervals(struct v4l2_frmivalenum *fi)
{
    if(!fi) {
        return -EINVAL;
    }
	print_debug("Enter %s.\n", __func__);
    
	if (fi->index >= CAMERA_MAX_FRAMERATE) {
		return -EINVAL;
	}

	fi->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fi->discrete.numerator = 1;
	fi->discrete.denominator = (fi->index + 1);
	return 0;
}

/*sonyimx179_get_capability*/
static int sonyimx179_get_capability(u32 id, u32 *value)
{
	int i;
    print_debug("Enter %s.\n", __func__);
	for (i = 0; i < sizeof(sonyimx179_cap) / sizeof(sonyimx179_cap[0]); i++) {
		if (id == sonyimx179_cap[i].id) {
			*value = sonyimx179_cap[i].value;
			break;
		}
	}
	return 0;
}

/*sonyimx179_gain_to_iso*/
static u32 sonyimx179_gain_to_iso(int gain)
{
	return (gain * 100) / 0x10;
}

/*sonyimx179_iso_to_gain*/
static u32 sonyimx179_iso_to_gain(int iso)
{
    return (iso * 0x10) / 100;
}

/*get gain from sensor*/
static u32 sonyimx179_get_gain(void)
{
	u8 gain = 0;
	sonyimx179_read_reg(SONYIMX179_ANA_GAIN_GLOBAL, &gain);
	return (u32)gain;
}

/*get exposure from sensor*/
static u32 sonyimx179_get_exposure(void)
{
	u32 expo = 0;
	u8 expo_h = 0;
	u8 expo_l = 0;
	sonyimx179_read_reg(SONYIMX179_EXPOSURE_REG_H, &expo_h);
	sonyimx179_read_reg(SONYIMX179_EXPOSURE_REG_L, &expo_l);
	expo = expo_h &0xff;
	expo = expo << 8 | expo_l;
	return expo;
}

/*set gain & exposure to sensor*/
static void sonyimx179_set_exposure_gain(u32 exposure, u32 gain)
{
	u32	tmp_digital_gain = 0;
	u8 digital_ratio = 0;
	u8 digital_h = 0;
	u8 digital_l = 0;
	u32 analog_gain = 0;

    print_debug("Enter %s.\n", __func__);
	sonyimx179_write_reg(SONYIMX179_GROUP_HOLD_REG, 0x01 , 0x00);//group hold

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
	sonyimx179_write_reg(SONYIMX179_ANA_GAIN_GLOBAL, analog_gain & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_GR_H, digital_h & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_GR_L, digital_l & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_R_H, digital_h & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_R_L, digital_l & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_B_H, digital_h & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_B_L, digital_l & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_GB_H, digital_h & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_GB_L, digital_l & 0xff, 0x00);
out:
	sonyimx179_write_reg(SONYIMX179_GROUP_HOLD_REG, 0x00 , 0x00);//group hold
}

/*sonyimx179_set_vts*/
static void sonyimx179_set_vts(u16 vts)
{
	print_debug("Enter %s.\n", __func__);
	sonyimx179_write_reg(SONYIMX179_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
	sonyimx179_write_reg(SONYIMX179_VTS_REG_L, vts & 0xff, 0x00);
}

/*sonyimx179_get_vts_reg_addr*/
static u32 sonyimx179_get_vts_reg_addr(void)
{
	return SONYIMX179_VTS_REG_H;
}

/*sonyimx179_get_sensor_aperture*/
static int sonyimx179_get_sensor_aperture()
{
	return SONYIMX179_APERTURE_FACTOR;
}

/*sonyimx179_get_override_param*/
static u32 sonyimx179_get_override_param(camera_override_type_t type)
{
	u32 ret_val = sensor_override_params[type];
	switch (type) {
	case OVERRIDE_ISO_HIGH:
		ret_val = SONYIMX179_MAX_ISO;
		break;

	case OVERRIDE_ISO_LOW:
		ret_val = SONYIMX179_MIN_ISO;
		break;

	case OVERRIDE_AUTOFPS_GAIN_LOW2MID:
		ret_val = SONYIMX179_AUTOFPS_GAIN_LOW2MID;
		break;
	case OVERRIDE_AUTOFPS_GAIN_MID2HIGH:
		ret_val = SONYIMX179_AUTOFPS_GAIN_MID2HIGH;
		break;

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

/*init sonyimx179_sensor default parameter*/
static void sonyimx179_set_default(void)
{
    /*function*/
    sonyimx179_sensor.init = sonyimx179_init;
    sonyimx179_sensor.exit = sonyimx179_exit;
    sonyimx179_sensor.shut_down = sonyimx179_shut_down;
    sonyimx179_sensor.reset = sonyimx179_reset;
    sonyimx179_sensor.power = sonyimx179_power;
    sonyimx179_sensor.check_sensor = sonyimx179_check_sensor;
    sonyimx179_sensor.init_reg = sonyimx179_init_reg;
    sonyimx179_sensor.init_isp_reg = sonyimx179_init_isp_reg;
    sonyimx179_sensor.stream_on = sonyimx179_stream_on;
    sonyimx179_sensor.set_flash = NULL;
    sonyimx179_sensor.get_flash = NULL;
    sonyimx179_sensor.set_scene = NULL;
    sonyimx179_sensor.get_scene = NULL;
    sonyimx179_sensor.set_hflip = sonyimx179_set_hflip;
    sonyimx179_sensor.get_hflip = sonyimx179_get_hflip;
    sonyimx179_sensor.set_vflip = sonyimx179_set_vflip;
    sonyimx179_sensor.get_vflip = sonyimx179_get_vflip;
    sonyimx179_sensor.update_flip = sonyimx179_update_flip;
    sonyimx179_sensor.get_format = sonyimx179_get_format;
    sonyimx179_sensor.enum_framesizes = sonyimx179_enum_framesizes;
    sonyimx179_sensor.try_framesizes = sonyimx179_try_framesizes;
    sonyimx179_sensor.set_framesizes = sonyimx179_set_framesizes;
    sonyimx179_sensor.get_framesizes = sonyimx179_get_framesizes;
    sonyimx179_sensor.enum_frame_intervals = sonyimx179_enum_frame_intervals;
    sonyimx179_sensor.try_frame_intervals = NULL;
    sonyimx179_sensor.set_frame_intervals = NULL;
    sonyimx179_sensor.get_frame_intervals = NULL;
    sonyimx179_sensor.get_capability = sonyimx179_get_capability;
    sonyimx179_sensor.sensor_gain_to_iso = sonyimx179_gain_to_iso;
    sonyimx179_sensor.sensor_iso_to_gain = sonyimx179_iso_to_gain;
    sonyimx179_sensor.get_ccm_pregain = NULL;
    sonyimx179_sensor.get_flash_awb = NULL;
    sonyimx179_sensor.set_gain = NULL;
    sonyimx179_sensor.get_gain = sonyimx179_get_gain;
    sonyimx179_sensor.set_exposure = NULL;
    sonyimx179_sensor.get_exposure = sonyimx179_get_exposure;
    sonyimx179_sensor.set_exposure_gain = sonyimx179_set_exposure_gain;
    sonyimx179_sensor.set_vts = sonyimx179_set_vts;
    sonyimx179_sensor.get_vts_reg_addr = sonyimx179_get_vts_reg_addr;
    sonyimx179_sensor.set_effect = NULL;
    sonyimx179_sensor.set_awb = NULL;
    sonyimx179_sensor.set_anti_banding = NULL;
    sonyimx179_sensor.update_framerate = NULL;
    sonyimx179_sensor.awb_dynamic_ccm_gain = NULL;
    sonyimx179_sensor.get_sensor_aperture = sonyimx179_get_sensor_aperture;
    sonyimx179_sensor.get_equivalent_focus = NULL;
    sonyimx179_sensor.get_override_param = sonyimx179_get_override_param;
    /*parameter*/
    sonyimx179_sensor.hflip = 0;
    sonyimx179_sensor.vflip = 0;
    sonyimx179_sensor.old_flip = 0;
    sonyimx179_sensor.skip_frames = 1;
    sonyimx179_sensor.interface_type = MIPI2;
    sonyimx179_sensor.mipi_lane_count = CSI_LINES_2;
    sonyimx179_sensor.mipi_index = CSI_INDEX_1;
    sonyimx179_sensor.power_conf.pd_valid = LOW_VALID;
    sonyimx179_sensor.power_conf.reset_valid = LOW_VALID;
    //sonyimx179_sensor.power_conf.vcmpd_valid = LOW_VALID;
    sonyimx179_sensor.sensor_index = CAMERA_SENSOR_SECONDARY;
    sonyimx179_sensor.i2c_config.index = I2C_SECONDARY;
    sonyimx179_sensor.i2c_config.speed = I2C_SPEED_400;
    sonyimx179_sensor.i2c_config.addr = SONYIMX179_SLAVE_ADDRESS;
    sonyimx179_sensor.i2c_config.addr_bits = I2C_16BIT;
    sonyimx179_sensor.i2c_config.val_bits = I2C_8BIT;
    sonyimx179_sensor.sensor_type = SENSOR_SONY;
    sonyimx179_sensor.sensor_rgb_type = SENSOR_RGGB;
    #ifdef SONYIMX179_AP_WRITEAE_MODE 
    sonyimx179_sensor.aec_addr[0] = 0;
    sonyimx179_sensor.aec_addr[1] = 0;
    sonyimx179_sensor.aec_addr[2] = 0;
    sonyimx179_sensor.agc_addr[0] = 0;
    sonyimx179_sensor.agc_addr[1] = 0;
    sonyimx179_sensor.ap_writeAE_delay = 0; 
    #else
    sonyimx179_sensor.aec_addr[0] = 0x0000;
    sonyimx179_sensor.aec_addr[1] = 0x0202;
    sonyimx179_sensor.aec_addr[2] = 0x0203;
    sonyimx179_sensor.agc_addr[0] = 0x0000; 
    sonyimx179_sensor.agc_addr[1] = 0x0205;
    #endif
    sonyimx179_sensor.isp_location = CAMERA_USE_K3ISP;
    sonyimx179_sensor.sensor_tune_ops = NULL;
    sonyimx179_sensor.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW10;
    sonyimx179_sensor.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW10;
    sonyimx179_sensor.preview_frmsize_index = 0;
    sonyimx179_sensor.capture_frmsize_index = 0;
    sonyimx179_sensor.frmsize_list = sonyimx179_framesizes;
    //sonyimx179_sensor.pclk = 0; //no use
    //sonyimx179_sensor.fps_max = 30; //isp will init
    //sonyimx179_sensor.fps_min = 15; //isp will init
    //sonyimx179_sensor.fps = 25; //isp will init
    sonyimx179_sensor.max_int_lines = 0;
    sonyimx179_sensor.min_int_lines = 0;
    sonyimx179_sensor.real_int_lines = 0;
    sonyimx179_sensor.min_gain = 0;
    sonyimx179_sensor.max_gain = 0;
    sonyimx179_sensor.real_gain = 0;
    sonyimx179_sensor.af_enable = 0;
    sonyimx179_sensor.vcm = NULL;
    sonyimx179_sensor.image_setting.lensc_param = sonyimx179_lensc_param;
    sonyimx179_sensor.image_setting.ccm_param = sonyimx179_ccm_param;
    sonyimx179_sensor.image_setting.awb_param = sonyimx179_awb_param;
    //sonyimx179_sensor.rcc_enable = false; //no use
    sonyimx179_sensor.owner = THIS_MODULE;
    strncpy(sonyimx179_sensor.info.name,"sonyimx179",sizeof(sonyimx179_sensor.info.name));
    sonyimx179_sensor.info.focal_length = 341;//3.406mm
    sonyimx179_sensor.info.h_view_angle = 80;
    sonyimx179_sensor.info.v_view_angle = 80;
    //sonyimx179_sensor.info.orientation = 270;//no use
    //sonyimx179_sensor.info.facing = CAMERA_FACING_BACK;//no use    
    sonyimx179_sensor.lane_clk = CLK_450M;
    sonyimx179_sensor.effect = NULL;
    sonyimx179_sensor.support_summary = false;
    sonyimx179_sensor.isp_idi_skip = false;   
}

#ifdef IMX179_OTP
/*set module id info*/
static void sonyimx179_otp_set_module_id(void)
{
    if((sonyimx179_otp_flag & SONYIMX179_OTP_READ_ID_AWB) == 0) {
        print_error("%s otp module id is error.\n",__func__);
        return;
    }
    /*now no use*/
}

/*set awb info*/
static void sonyimx179_otp_set_awb(void)
{
    int g_gain, b_gain, r_gain, gr_gain, gb_gain;
    int rg, bg;
    if(sonyimx179_otp_flag & SONYIMX179_OTP_READ_ID_AWB == 0) {
        print_error("%s otp awb data is error.\n",__func__);
        return;
    }
    
    /*calculate digital gain*/
    rg = (sonyimx179_otp.awbData[0] << 8) + sonyimx179_otp.awbData[1];
	bg = (sonyimx179_otp.awbData[2] << 8) + sonyimx179_otp.awbData[3];

    //0x400 = 1x gain
    if(bg < GOLDEN_BG_RATIO) {
		if (rg < GOLDEN_RG_RATIO) {
   			g_gain = 0x400;
			b_gain = 0x400 * GOLDEN_BG_RATIO / bg;
    		r_gain = 0x400 * GOLDEN_RG_RATIO / rg; 
		} else {
    		r_gain = 0x400;
   	 		g_gain = 0x400 * rg / GOLDEN_RG_RATIO;
    		b_gain = g_gain * GOLDEN_BG_RATIO /bg;
		}
	} else {
		if (rg < GOLDEN_RG_RATIO) {
    		b_gain = 0x400;
    		g_gain = 0x400 * bg / GOLDEN_BG_RATIO;
    		r_gain = g_gain * GOLDEN_RG_RATIO / rg;
		} else {
    		gb_gain = 0x400 * bg / GOLDEN_BG_RATIO;
   	 		gr_gain = 0x400 * rg / GOLDEN_RG_RATIO;

    		if(gb_gain > gr_gain ) {
        		b_gain = 0x400;
        		g_gain = gb_gain;
 	     		r_gain = g_gain * GOLDEN_RG_RATIO /rg;
  			} else {
        		r_gain = 0x400;
       			g_gain = gr_gain;
        		b_gain = g_gain * GOLDEN_BG_RATIO / bg;
			}
    	}    
	}

    /*set gain*/
    if(r_gain > 0x400) {
    	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_R_H, (r_gain>>8) & 0xff, 0x00);
    	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_R_L, r_gain & 0x00ff, 0x00);
    }
    if(b_gain > 0x400) {
    	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_B_H, (b_gain>>8) & 0xff, 0x00);
    	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_B_L, b_gain & 0x00ff, 0x00);
    }
    if(gr_gain > 0x400) {
    	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_GR_H, (gr_gain>>8) & 0xff, 0x00);
    	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_GR_L, gr_gain & 0x00ff, 0x00);
    }
    if(gb_gain > 0x400) {
    	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_GB_H, (gb_gain>>8) & 0xff, 0x00);
    	sonyimx179_write_reg(SONYIMX179_DIG_GAIN_GB_L, gb_gain & 0x00ff, 0x00);
    }
    
}

/*read module info & awb from otp, page1~page4*/
static void sonyimx179_otp_read_id_awb(void)
{
    int i = 0;

    /*check page whether validate*/
    for(i = 4; i > 0; i--) {
        sonyimx179_write_reg(SONYIMX179_OTP_PAGE_SLECT, i, 0x00);
        sonyimx179_read_reg(SONYIMX179_OTP_MODULE_ID, &sonyimx179_otp.moduleInfo[0]);
        sonyimx179_read_reg(SONYIMX179_OTP_AWB_REG, &sonyimx179_otp.awbData[0]);
        if(sonyimx179_otp.moduleInfo[0] | sonyimx179_otp.awbData[0]) {
            print_debug("%s the validate page is %d.\n",__func__,i);
            break;
        }
    }

    if(i == 0) {
        sonyimx179_otp_flag &= ~SONYIMX179_OTP_READ_ID_AWB;
        print_error("%s it doesn't have validate page.\n",__func__);
        return;
    }

    /*get module id*/
    for(i = 1; i < MAX_OTP_MODULE_INFO; i++) {
        /*year has get, month, day, camera_id, module_id*/
        sonyimx179_read_reg(SONYIMX179_OTP_MODULE_ID+i, &sonyimx179_otp.moduleInfo[i]);
    }

    print_debug("%s module info: year 20%02d month %d day %d, SNO. 0x%x, vendor id&version 0x%x\n",__func__,
        sonyimx179_otp.moduleInfo[0], sonyimx179_otp.moduleInfo[1],sonyimx179_otp.moduleInfo[2],
        sonyimx179_otp.moduleInfo[3], sonyimx179_otp.moduleInfo[4]);

    /*get awb data*/
    for(i = 1; i < MAX_OTP_AWB_DATA; i++) {
        /*R/G (High) has get, R/G (Low), B/G (High), B/G (Low), Gb/Gr (High), Gb/Gr (Low)*/
        sonyimx179_read_reg(SONYIMX179_OTP_AWB_REG+i,&sonyimx179_otp.awbData[i]); 
    }

    print_debug("%s awb: R/G(High) 0x%0x, R/G(Low) 0x%0x, B/G(High) 0x%0x, B/G(Low) 0x%0x, Gb/Gr(High) 0x%0x, Gb/Gr(Low) 0x%0x, \n",__func__,
        sonyimx179_otp.awbData[0], sonyimx179_otp.awbData[1], sonyimx179_otp.awbData[2],
        sonyimx179_otp.awbData[3], sonyimx179_otp.awbData[4], sonyimx179_otp.awbData[5]);
    
    sonyimx179_otp_flag |= SONYIMX179_OTP_READ_ID_AWB;
    return;
}

/*get otp data*/
static void sonyimx179_otp_get_data(void)
{
    u8 status = 0;
    int ret = 0;

    ret = sonyimx179_write_reg(SONYIMX179_OTP_MODE, 0x00, 0x00); //depend on the last writing mode
    ret += sonyimx179_write_reg(SONYIMX179_OTP_CTRL, 0x01, 0x00); //set r/w
    if(!ret) {
        sonyimx179_otp_flag = 0;
        print_error("%s otp mode set fail.\n",__func__);
        return;
    }

    /*check otp status*/
    /*============================need to check======================================================*/
    ret = sonyimx179_read_reg(SONYIMX179_OTP_STATUS, &status);
    if(ret || status) { // 0:reday, 1:err
        sonyimx179_otp_flag &= ~SONYIMX179_OTP_READY;
        print_error("%s otp data is not ready.\n",__func__);
        return;
    }
    sonyimx179_otp_flag |= SONYIMX179_OTP_READY;

    /*read module id&awb in page01~page04*/
	sonyimx179_otp_read_id_awb();
    return;
}
#endif

/*sonyimx179_module_init*/
static __init int sonyimx179_module_init(void)
{
	sonyimx179_set_default();
	return register_camera_sensor(sonyimx179_sensor.sensor_index, &sonyimx179_sensor);
}

/*sonyimx179_module_exit*/
static void __exit sonyimx179_module_exit(void)
{
	unregister_camera_sensor(sonyimx179_sensor.sensor_index, &sonyimx179_sensor);
}

MODULE_AUTHOR("Hisilicon");
module_init(sonyimx179_module_init);
module_exit(sonyimx179_module_exit);
MODULE_LICENSE("GPL");
/********************************** END **********************************************/
