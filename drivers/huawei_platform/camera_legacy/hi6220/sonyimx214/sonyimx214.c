/*
 *  sonyimx214 camera driver head file
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
#include "sonyimx214.h"
#include "effect.h"

#define LOG_TAG "SONYIMX214"
#include "cam_log.h"
#include "cam_util.h"

#define SONYIMX214_AP_WRITEAE_MODE

#define SONYIMX214_ZSL                   (0x00) //(1 << CAMERA_ZSL_OFF)
#define SONYIMX214_CHIP_ID               (0x0214)
#define SONYIMX214_SLAVE_ADDRESS         (0x34)

/*exposure*/
#define SONYIMX214_EXPOSURE_REG_H        (0x0202) //coarse_integration_time
#define SONYIMX214_EXPOSURE_REG_L        (0x0203)


/*analogue gain & digital gain*/
#define SONYIMX214_MAX_ANALOG_GAIN       (8)
#define SONYIMX214_ANA_GAIN_GLOBAL_H     (0x0204)
#define SONYIMX214_ANA_GAIN_GLOBAL_L     (0x0205) //analogue_gain_code_global
#define SONYIMX214_DIG_GAIN_GR_H         (0x020E) //digital_gain_greenR
#define SONYIMX214_DIG_GAIN_GR_L         (0x020F)
#define SONYIMX214_DIG_GAIN_R_H          (0x0210) //digital_gain_red
#define SONYIMX214_DIG_GAIN_R_L          (0x0211)
#define SONYIMX214_DIG_GAIN_B_H          (0x0212) //digital_gain_blue
#define SONYIMX214_DIG_GAIN_B_L          (0x0213)
#define SONYIMX214_DIG_GAIN_GB_H         (0x0214) //digital_gain_greenB
#define SONYIMX214_DIG_GAIN_GB_L         (0x0215)


/*image_orientation*/
#define SONYIMX214_FLIP		             (0x0101)

/*grouped_parameter_hold*/
#define SONYIMX214_GROUP_HOLD_REG        (0x0104)

/*Frame Timing Registers*/
#define SONYIMX214_VTS_REG_H		     (0x0340) //frame_length_lines
#define SONYIMX214_VTS_REG_L		     (0x0341)
#define SONYIMX214_APERTURE_FACTOR       (200) //F2.0

#define SONYIMX214_I2C_RETRY_TIMES       (5)
enum sensor_module_type
{
	MODULE_FOXCONN,
	MODULE_SUNNY,
	MODULE_UNSUPPORT
};
static u8 sensor_module;

#if 0
/* support 3 level framerate now, if mid fps same as min, set to 2 level framerate */
#define SONYIMX214_AUTOFPS_GAIN_HIGH2MID (0x24)
#define SONYIMX214_AUTOFPS_GAIN_MID2LOW	 (0x24)
#define SONYIMX214_AUTOFPS_GAIN_LOW2MID	 (0x60)
#define SONYIMX214_AUTOFPS_GAIN_MID2HIGH (0x60)
#define SONYIMX214_MAX_FRAMERATE         (30)
#define SONYIMX214_MID_FRAMERATE		 (15)
#define SONYIMX214_MIN_FRAMERATE         (10)
#define SONYIMX214_MIN_CAP_FRAMERATE     (8)
/*iso*/
#define SONYIMX214_MAX_ISO               (1550)
#define SONYIMX214_MIN_ISO               (100)

#define SONYIMX214_FLASH_TRIGGER_GAIN    (0xff)

/*sharpness*/
#define SONYIMX214_SHARPNESS_PREVIEW     (0x30)
#define SONYIMX214_SHARPNESS_CAPTURE     (0x08)
#endif


char sonyimx214_lensc_param[86*3] = {
};

short sonyimx214_ccm_param[54] = {
};

char sonyimx214_awb_param[] = {
};

static framesize_s sonyimx214_framesizes[] = {
	//{0, 0, 1920, 1088, 5008, 1330, 30, 30, 0x18F, 0x14C, 0x189, VIEW_FULL, RESOLUTION_16_9, true, false,{sonyimx214_30fps_framesize_1920x1088, ARRAY_SIZE(sonyimx214_30fps_framesize_1920x1088)} },
	{0, 0, 2104, 1560, 5008, 1730, 30, 30, 0x207, 0x1B0, 0x100, VIEW_FULL, RESOLUTION_4_3, false, false,{sonyimx214_30fps_framesize_2104x1560, ARRAY_SIZE(sonyimx214_30fps_framesize_2104x1560)} },
	{0, 0, 4160, 3120, 5008, 3490, 10, 10, 0x13F, 0x10A, 0x9D, VIEW_FULL, RESOLUTION_4_3, false, false,{sonyimx214_10fps_framesize_4160x3120, ARRAY_SIZE(sonyimx214_10fps_framesize_4160x3120)} },	
	//{0, 0, 4160, 3120, 5008, 3490, 15, 15, 0x207, 0x1B0, 0x200, VIEW_FULL, RESOLUTION_4_3, false, false,{sonyimx214_14fps_framesize_4160x3120, ARRAY_SIZE(sonyimx214_14fps_framesize_4160x3120)} },	
};

static camera_capability sonyimx214_cap[] = {
	{V4L2_CID_FLASH_MODE, THIS_FLASH},
	{V4L2_CID_FOCUS_MODE, THIS_FOCUS_MODE},
	{V4L2_CID_FOCAL_LENGTH, 379},//3.79mm
	{V4L2_CID_ZSL, SONYIMX214_ZSL},
};

/*efect parameter*/
static effect_params effect_imx214_sunny = {
    #include "effect_imx214_sunny.h"
};
static vcm_info_s vcm_dw9714_sunny = {
    #include "vcm_dw9714_sunny.h"
};
static effect_params effect_imx214_foxconn = {
    #include "effect_imx214_foxconn.h"
};
static vcm_info_s vcm_dw9714_foxconn = {
    #include "vcm_dw9714_foxconn.h"
};
static awb_gain_t flash_platform_awb[] = {
	{0xbd, 0x80, 0x80, 0xdc}, /*EDGE*/
};
static camera_sensor sonyimx214_sensor;

/*read sonyimx214 reg by i2c*/
static int sonyimx214_read_reg(u16 reg, u8 *val)
{
	return k3_ispio_read_reg(sonyimx214_sensor.i2c_config.index,
		sonyimx214_sensor.i2c_config.addr, reg, (u16*)val, sonyimx214_sensor.i2c_config.val_bits,sonyimx214_sensor.i2c_config.addr_bits);
}

/*write sonyimx214 reg by i2c*/
static int sonyimx214_write_reg(u16 reg, u8 val, u8 mask)
{
    return k3_ispio_write_reg(sonyimx214_sensor.i2c_config.index, sonyimx214_sensor.i2c_config.addr, reg, 
        (u16)val, sonyimx214_sensor.i2c_config.val_bits, mask, sonyimx214_sensor.i2c_config.addr_bits);
}

/*write sequeuence to select I2C though isp command set*/
static int sonyimx214_write_seq(const struct _sensor_reg_t *seq, u32 size, u8 mask)
{
    return k3_ispio_write_seq(sonyimx214_sensor.i2c_config.index, sonyimx214_sensor.i2c_config.addr, 
        seq, size, sonyimx214_sensor.i2c_config.val_bits, mask,sonyimx214_sensor.i2c_config.addr_bits);
}

/*sonyimx214 init function*/
static int sonyimx214_init(void)
{
	int ret;
	print_debug("Enter %s.\n", __func__);
	if (check_suspensory_camera("SONYIMX214") != 1) {
	    print_error("%s: can't find SONYIMX214.\n", __func__);
	    return -ENODEV;     
	}
	if (sonyimx214_sensor.owner && !try_module_get(sonyimx214_sensor.owner)) {
		print_error("%s: try_module_get fail.\n", __func__);
		return -ENOENT;
	}
	/*main & slave use the same power*/
	if(0 == get_sensor_iopower()) {
	    /*slave camera*/
		k3_ispio_power_init(S_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	//analog 2.85V - sec camera
		k3_ispio_power_init(S_CAMERA_CORE_VDD, LDO_VOLTAGE_12V, LDO_VOLTAGE_12V); //core 1.2V - sec camera
	    /*main camera*/
		k3_ispio_power_init(M_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - pri camera*/
		k3_ispio_power_init(M_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);		/*IO 1.8V - pri camera*/
		ret = gpio_request(GPIO_18_0, NULL);
		if (ret) {
			print_error("failed to request dcdc core for imx214");
			return -EIO;
		}
		k3_ispio_power_init(M_CAMERA_VCM_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*AF 2.85V - pri camera*/

	} else { //main & slave use the different power
		k3_ispio_power_init(M_CAMERA_ANALOG_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*analog 2.85V - pri camera*/
		k3_ispio_power_init(M_CAMERA_IO_VDD, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);		/*IO 1.8V - pri camera*/
		k3_ispio_power_init(M_CAMERA_VCM_VDD, LDO_VOLTAGE_28V, LDO_VOLTAGE_28V);	/*AF 2.85V - pri camera*/
		k3_ispio_power_init(M_CAMERA_CORE_VDD, LDO_VOLTAGE_10V, LDO_VOLTAGE_10V);	/*core 1.05V - pri camera*/
	}
	return 0;
}

/*sonyimx214 exit function*/
static void sonyimx214_exit(void)
{
	print_debug("Enter %s.\n", __func__);
	k3_ispio_power_deinit();
	if (sonyimx214_sensor.owner) {
        module_put(sonyimx214_sensor.owner);
	}
}

/*sonyimx214 shut down function*/
static void sonyimx214_shut_down(void)
{
	print_debug("Enter %s.\n", __func__);  
	k3_ispgpio_power_sensor(&sonyimx214_sensor, POWER_OFF);
}

/*sonyimx214 reset function*/
static int sonyimx214_reset(camera_power_state power_state)
{
	print_debug("Enter %s.\n", __func__);

	if (POWER_ON == power_state) {
		k3_isp_io_enable_mclk(MCLK_ENABLE, sonyimx214_sensor.sensor_index);
        udelay(100);
		k3_ispgpio_reset_sensor(sonyimx214_sensor.sensor_index, power_state, sonyimx214_sensor.power_conf.reset_valid);
		udelay(500);
	} else {
		k3_ispgpio_reset_sensor(sonyimx214_sensor.sensor_index, power_state, sonyimx214_sensor.power_conf.reset_valid);
		udelay(10);
		k3_isp_io_enable_mclk(MCLK_DISABLE, sonyimx214_sensor.sensor_index);
	}

	return 0;
}

/*sonyimx214 power up function*/
static int sonyimx214_power(camera_power_state power)
{
	print_debug("Enter %s.\n", __func__);
	/*main & slave use the same power*/
	if(0 == get_sensor_iopower()) {
		if (power == POWER_ON) {
			/*slave camera*/
			k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
			k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD); 
			udelay(1);
			/*main camera*/
			k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
			k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);
			//gpio
			gpio_direction_output(GPIO_18_0, 1);
			udelay(200);
			k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
			udelay(1);
			k3_ispio_ioconfig(&sonyimx214_sensor, power);
			k3_ispgpio_power_sensor(&sonyimx214_sensor, power);
			msleep(3);
		} else {
			k3_ispio_deinit_csi(sonyimx214_sensor.mipi_index);
			k3_ispgpio_power_sensor(&sonyimx214_sensor, power);
			k3_ispio_ioconfig(&sonyimx214_sensor, power);
			/*slave camera*/
			k3_ispldo_power_sensor(power, S_CAMERA_CORE_VDD); 
			k3_ispldo_power_sensor(power, S_CAMERA_ANALOG_VDD);
			/*main camera*/
			k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
			k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);
			//gpio
			gpio_direction_output(GPIO_18_0, 0);
			gpio_free(GPIO_18_0);
			udelay(200);
			k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
			
		}
	} else { //main & slave use the different power
	    if (power == POWER_ON) {
		k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);
		udelay(200);
		k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
		udelay(1);
		k3_ispio_ioconfig(&sonyimx214_sensor, power);
		k3_ispgpio_power_sensor(&sonyimx214_sensor, power);
		msleep(2);
		} else {
		k3_ispio_deinit_csi(sonyimx214_sensor.mipi_index);
		k3_ispgpio_power_sensor(&sonyimx214_sensor, power);
		k3_ispio_ioconfig(&sonyimx214_sensor, power);
		k3_ispldo_power_sensor(power, M_CAMERA_VCM_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_CORE_VDD);
		udelay(200);
		k3_ispldo_power_sensor(power, M_CAMERA_ANALOG_VDD);
		k3_ispldo_power_sensor(power, M_CAMERA_IO_VDD);
		}
	}
	return 0;
}

/*sonyimx214 check sensor state function*/
static int sonyimx214_check_sensor(void)
{
	u8 idl = 0;
	u8 idh = 0;
	u16 id = 0;
	int pin_id = 0;
    int retry = 0;

    for(retry = 0; retry < SONYIMX214_I2C_RETRY_TIMES; retry++) {
    	sonyimx214_read_reg(0x0016, &idh);
    	sonyimx214_read_reg(0x0017, &idl);

    	id = ((idh << 8) | idl);
    	print_info("sonyimx214 product id:0x%x, retrytimes:%d.\n", id, retry);
        if (SONYIMX214_CHIP_ID == id) {
            break;
        }
        udelay(100);
    }
	if (SONYIMX214_CHIP_ID != id) {
		print_error("Invalid product id ,Could not load sensor sonyimx214.\n");
		return -ENODEV;
	}
	pin_id = gpio_get_value(GPIO_18_3);
	if(pin_id < 0) {
		pin_id = 0;
		print_error("sonyimx214_check_sensor fail to get gpio value!!! set pin_id to 0 by default MODULE_SUNNY !\n");
	}
	sensor_module = pin_id>0 ? MODULE_SUNNY:MODULE_FOXCONN;
	if(sensor_module ==  MODULE_SUNNY) {
		sonyimx214_sensor.effect = &effect_imx214_sunny;
		sonyimx214_sensor.vcm = &vcm_dw9714_sunny;
		snprintf(sonyimx214_sensor.info.name, sizeof(sonyimx214_sensor.info.name),"sonyimx214_sunny");
	}else {
		sonyimx214_sensor.vcm = &vcm_dw9714_foxconn;
		sonyimx214_sensor.effect = &effect_imx214_foxconn;  
		snprintf(sonyimx214_sensor.info.name, sizeof(sonyimx214_sensor.info.name),"sonyimx214_foxconn");
	}
	return 0;
}

/*download initial seq for sensor init*/
static int sonyimx214_init_reg(void)
{
	print_debug("Enter %s.\n", __func__);
	if (0 != k3_ispio_init_csi(sonyimx214_sensor.mipi_index, sonyimx214_sensor.mipi_lane_count, sonyimx214_sensor.lane_clk)) {
		return -EFAULT;
	}
	if (0 != sonyimx214_write_seq(sonyimx214_init_regs, ARRAY_SIZE(sonyimx214_init_regs), 0x00)) {
		print_error("%s fail to init sonyimx214 sensor.\n", __func__);
		return -EFAULT;
	}
	return 0;
}

/*set sensor effect reg to isp*/
static int sonyimx214_init_isp_reg(void)
{    
    k3_ispio_write_isp_seq(sonyimx214_sensor.effect->isp_settings, CAMERA_MAX_SETTING_SIZE);
	return 0;
}

/*download preview seq for sensor preview*/
static int sonyimx214_stream_on(camera_state state)
{
	u8 next_frmsize_index = (state == STATE_PREVIEW) ? sonyimx214_sensor.preview_frmsize_index : sonyimx214_sensor.capture_frmsize_index;
	print_debug("Enter %s frm index=%d.\n", __func__, next_frmsize_index);
	if (next_frmsize_index >= ARRAY_SIZE(sonyimx214_framesizes)){
		print_error("Unsupport sensor setting index: %d",next_frmsize_index);
		return -EINVAL;
	}
	if (0 != sonyimx214_write_seq(sonyimx214_sensor.frmsize_list[next_frmsize_index].sensor_setting.setting,
                sonyimx214_sensor.frmsize_list[next_frmsize_index].sensor_setting.seq_size, 0x00)) {
		print_error("fail to init sonyimx214 sensor");
		return -EINVAL;
	}
	return 0;
}

/*sonyimx214_set_hflip*/
static int sonyimx214_set_hflip(int flip)
{
	print_debug("Enter %s flip=%d.\n", __func__, flip);
	sonyimx214_sensor.hflip = flip;
	return 0;
}

/*sonyimx214_get_hflip*/
static int sonyimx214_get_hflip(void)
{
	print_debug("Enter %s.\n", __func__);
	return sonyimx214_sensor.hflip;
}

/*sonyimx214_set_vflip*/
static int sonyimx214_set_vflip(int flip)
{
	print_debug("Enter %s flip=%d.\n", __func__, flip);
	sonyimx214_sensor.vflip = flip;
	return 0;
}

/*sonyimx214_get_vflip*/
static int sonyimx214_get_vflip(void)
{
	return sonyimx214_sensor.vflip;
}

/*sonyimx214_update_flip*/
static int sonyimx214_update_flip(u16 width, u16 height)
{
	u8 new_flip = ((sonyimx214_sensor.vflip << 1) | sonyimx214_sensor.hflip);
	
	print_debug("Enter %s.\n", __func__);	
	k3_ispio_update_flip(( sonyimx214_sensor.old_flip^new_flip) & 0x03, width, height, PIXEL_ORDER_CHANGED);

	sonyimx214_sensor.old_flip = new_flip;
	sonyimx214_write_reg(SONYIMX214_FLIP, sonyimx214_sensor.vflip ? 0x02 : 0x00, ~0x02);
	sonyimx214_write_reg(SONYIMX214_FLIP, sonyimx214_sensor.hflip ? 0x01 : 0x00, ~0x01);
	return 0;
}

/*sonyimx214_get_format*/
static int sonyimx214_get_format(struct v4l2_fmtdesc *fmt)
{
    if(!fmt) {
        return -EINVAL;
    }
    print_debug("Enter %s.\n", __func__);
	if (fmt->type == V4L2_BUF_TYPE_VIDEO_OVERLAY) {
		fmt->pixelformat = sonyimx214_sensor.fmt[STATE_PREVIEW];
	} else {
		fmt->pixelformat = sonyimx214_sensor.fmt[STATE_CAPTURE];
	}
	return 0;
}
void sonyimx214_get_flash_awb(flash_platform_t type, awb_gain_t *flash_awb)
{
	*flash_awb = flash_platform_awb[0];
	print_info("sonyimx214_get_flash_awb: type 0x%x,", type);
}

/*sonyimx214_enum_framesizes*/
static int sonyimx214_enum_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	u32 this_max_index = ARRAY_SIZE(sonyimx214_framesizes) - 1;

    if(!framesizes) {
        return -EINVAL;
    }
	print_debug("Enter %s.\n", __func__);
	if (framesizes->index > ARRAY_SIZE(camera_framesizes) - 1) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}
	if ((camera_framesizes[framesizes->index].width > sonyimx214_framesizes[this_max_index].width)
		|| (camera_framesizes[framesizes->index].height > sonyimx214_framesizes[this_max_index].height)) {
		print_error("framesizes->index = %d error", framesizes->index);
		return -EINVAL;
	}
	framesizes->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	framesizes->discrete.width = sonyimx214_framesizes[this_max_index].width;
	framesizes->discrete.height = sonyimx214_framesizes[this_max_index].height;
	return 0;
}

/*sonyimx214_try_framesizes*/
static int sonyimx214_try_framesizes(struct v4l2_frmsizeenum *framesizes)
{
	int max_index = ARRAY_SIZE(sonyimx214_framesizes) - 1;

    if(!framesizes) {
        return -EINVAL;
    }
	print_debug("Enter %s.\n", __func__);

	if ((framesizes->discrete.width <= sonyimx214_framesizes[max_index].width)
	    && (framesizes->discrete.height <= sonyimx214_framesizes[max_index].height)) {
		print_debug("width = %d, height = %d", framesizes->discrete.width, framesizes->discrete.height);
		return 0;
	}

	print_error("frame size too large, [%d,%d]", framesizes->discrete.width, framesizes->discrete.height);
	return -EINVAL;
}

/*sonyimx214_set_framesizes,flag=1, set framesize to sensor,flag=0, only store framesize to camera_interface*/
static int sonyimx214_set_framesizes(camera_state state, struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type, bool zsl_preview)
{
	int i = 0;
	bool match = false;
	int size = ARRAY_SIZE(sonyimx214_framesizes);
    if(!fs) {
        return -EINVAL;
    }
	print_info("Enter %s State(%d), flag=%d, width=%d, height=%d", __func__, state, flag, fs->width, fs->height);
	if (VIEW_FULL == view_type) {
		for (i = 0; i < size; i++) {
		    if ((!zsl_preview && sonyimx214_framesizes[i].zsl_only) || (zsl_preview && !sonyimx214_framesizes[i].zsl_only)) {
		        continue;
		    }
			if ((sonyimx214_framesizes[i].width >= fs->width)
			    && (sonyimx214_framesizes[i].height >= fs->height)
			    && (VIEW_FULL == sonyimx214_framesizes[i].view_type)
			    && (camera_get_resolution_type(fs->width, fs->height)
			    <= sonyimx214_framesizes[i].resolution_type)) {
    				fs->width = sonyimx214_framesizes[i].width;
    				fs->height = sonyimx214_framesizes[i].height;
    				match = true;
    				break;
			}
		}
	}
	if (false == match) {
		for (i = 0; i < size; i++) {
		    if ((zsl_preview == false) && sonyimx214_framesizes[i].zsl_only) {
		        continue;
		    }

			if ((sonyimx214_framesizes[i].width >= fs->width)
				    && (sonyimx214_framesizes[i].height >= fs->height)
				    && (camera_get_resolution_type(fs->width, fs->height)
    				    <= sonyimx214_framesizes[i].resolution_type)) {
					fs->width = sonyimx214_framesizes[i].width;
					fs->height = sonyimx214_framesizes[i].height;
					break;
			}
		}
	}

	if (i >= size) {
		print_error("request resolution larger than sensor's max resolution");
		return -EINVAL;
	}

	if (state == STATE_PREVIEW) {
		sonyimx214_sensor.preview_frmsize_index = i;
	} else {
		sonyimx214_sensor.capture_frmsize_index = i;
	}
	return 0;
}

/*sonyimx214_get_framesizes*/
static int sonyimx214_get_framesizes(camera_state state, struct v4l2_frmsize_discrete *fs)
{
	int frmsize_index = (state == STATE_PREVIEW) ? sonyimx214_sensor.preview_frmsize_index : sonyimx214_sensor.capture_frmsize_index;

    if(!fs) {
        return -EINVAL;
    }
    print_debug("Enter %s.\n", __func__);
	fs->width = sonyimx214_framesizes[frmsize_index].width;
	fs->height = sonyimx214_framesizes[frmsize_index].height;
	return 0;
}

/*sonyimx214_enum_frame_intervals*/
static int sonyimx214_enum_frame_intervals(struct v4l2_frmivalenum *fi)
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

/*sonyimx214_get_capability*/
static int sonyimx214_get_capability(u32 id, u32 *value)
{
	int i;
    print_debug("Enter %s.\n", __func__);
	for (i = 0; i < sizeof(sonyimx214_cap) / sizeof(sonyimx214_cap[0]); i++) {
		if (id == sonyimx214_cap[i].id) {
			*value = sonyimx214_cap[i].value;
			break;
		}
	}
	return 0;
}

/*sonyimx214_gain_to_iso*/
static u32 sonyimx214_gain_to_iso(int gain)
{
	return (gain * 100) / 0x10;
}

/*sonyimx214_iso_to_gain*/
static u32 sonyimx214_iso_to_gain(int iso)
{
    return (iso * 0x10) / 100;
}
/*sonyimx214_set_gain*/
void sonyimx214_set_gain(u32 gain)
{
	if (gain == 0)
		return;
	gain = 256 - (256 * 16) / gain;
	sonyimx214_write_reg(SONYIMX214_ANA_GAIN_GLOBAL_H, (gain >> 8) & 0xff, 0x00);
	sonyimx214_write_reg(SONYIMX214_ANA_GAIN_GLOBAL_L, gain & 0xff, 0x00);
}
/*sonyimx214_set_exposure*/
void sonyimx214_set_exposure(u32 exposure)
{
	exposure >>= 4;
	sonyimx214_write_reg(SONYIMX214_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	sonyimx214_write_reg(SONYIMX214_EXPOSURE_REG_L, exposure & 0xff, 0x00);
}
/*get gain from sensor*/
static u32 sonyimx214_get_gain(void)
{
	u8 gain = 0;
	sonyimx214_read_reg(SONYIMX214_ANA_GAIN_GLOBAL_L, &gain);
	return (u32)gain;
}

/*get exposure from sensor*/
static u32 sonyimx214_get_exposure(void)
{
	u32 expo = 0;
	u8 expo_h = 0;
	u8 expo_l = 0;
	sonyimx214_read_reg(SONYIMX214_EXPOSURE_REG_H, &expo_h);
	sonyimx214_read_reg(SONYIMX214_EXPOSURE_REG_L, &expo_l);
	expo = expo_h &0xff;
	expo = expo << 8 | expo_l;
	return expo;
}

/*set gain & exposure to sensor*/
static void sonyimx214_set_exposure_gain(u32 exposure, u32 gain)
{
	u32	tmp_digital_gain = 0;
	u8 digital_ratio = 0;
	u8 digital_h = 0;
	u8 digital_l = 0;
	u32 analog_gain = 0;

	print_debug("Enter %s.\n", __func__);
	sonyimx214_write_reg(SONYIMX214_GROUP_HOLD_REG, 0x01 , 0x00);//group hold

    /*adapter isp2.2 register value*/
	exposure >>= 4; //isp2.2 exposure = register_value/0x10
	
	sonyimx214_write_reg(SONYIMX214_EXPOSURE_REG_H, (exposure >> 8) & 0xff, 0x00);
	sonyimx214_write_reg(SONYIMX214_EXPOSURE_REG_L, exposure & 0xff, 0x00);

	if (gain == 0)
		goto out;

    //isp2.2 gain = register_value/0x10
    /*
    digital_h = (gain/SONYIMX214_MAX_ANALOG_GAIN)/16;
    digital_l = (digital_h'decimal)*256
    analog_gain = 256 - (256/(gain/16))
    */
	if(gain > SONYIMX214_MAX_ANALOG_GAIN*16)
	{
        /*tmp_digital_gain*256 is keep the decimal part*/
		tmp_digital_gain = (gain*256) >> 4;
		tmp_digital_gain = tmp_digital_gain >> 3;

		digital_ratio = (gain/SONYIMX214_MAX_ANALOG_GAIN) >> 4;
		digital_h = digital_ratio;
		digital_l = tmp_digital_gain - digital_ratio*256;
		analog_gain = SONYIMX214_MAX_ANALOG_GAIN*16;
	}
	else
	{
		analog_gain = gain;
		digital_h = 1;
		digital_l = 0;
	}

	analog_gain = 256 - (256 * 16) / analog_gain;
	sonyimx214_write_reg(SONYIMX214_ANA_GAIN_GLOBAL_L, analog_gain & 0xff, 0x00);
	sonyimx214_write_reg(SONYIMX214_DIG_GAIN_GR_H, digital_h & 0xff, 0x00);
	sonyimx214_write_reg(SONYIMX214_DIG_GAIN_GR_L, digital_l & 0xff, 0x00);
	sonyimx214_write_reg(SONYIMX214_DIG_GAIN_R_H, digital_h & 0xff, 0x00);
	sonyimx214_write_reg(SONYIMX214_DIG_GAIN_R_L, digital_l & 0xff, 0x00);
	sonyimx214_write_reg(SONYIMX214_DIG_GAIN_B_H, digital_h & 0xff, 0x00);
	sonyimx214_write_reg(SONYIMX214_DIG_GAIN_B_L, digital_l & 0xff, 0x00);
	sonyimx214_write_reg(SONYIMX214_DIG_GAIN_GB_H, digital_h & 0xff, 0x00);
	sonyimx214_write_reg(SONYIMX214_DIG_GAIN_GB_L, digital_l & 0xff, 0x00);
out:
	sonyimx214_write_reg(SONYIMX214_GROUP_HOLD_REG, 0x00 , 0x00);//group hold
}

/*sonyimx214_set_vts*/
static void sonyimx214_set_vts(u16 vts)
{
	print_debug("Enter %s.\n", __func__);
	sonyimx214_write_reg(SONYIMX214_VTS_REG_H, (vts >> 8) & 0xff, 0x00);
	sonyimx214_write_reg(SONYIMX214_VTS_REG_L, vts & 0xff, 0x00);
}

/*sonyimx214_get_vts_reg_addr*/
static u32 sonyimx214_get_vts_reg_addr(void)
{
	return SONYIMX214_VTS_REG_H;
}

/*sonyimx214_get_sensor_aperture*/
static int sonyimx214_get_sensor_aperture(void)
{
	return SONYIMX214_APERTURE_FACTOR;
}

/*init sonyimx214_sensor default parameter*/
static void sonyimx214_set_default(void)
{
	sonyimx214_sensor.init = sonyimx214_init;
	sonyimx214_sensor.exit = sonyimx214_exit;
	sonyimx214_sensor.shut_down = sonyimx214_shut_down;
	sonyimx214_sensor.reset = sonyimx214_reset;
	sonyimx214_sensor.power = sonyimx214_power;
	sonyimx214_sensor.check_sensor = sonyimx214_check_sensor;
	sonyimx214_sensor.init_reg = sonyimx214_init_reg;
	sonyimx214_sensor.init_isp_reg = sonyimx214_init_isp_reg;
	sonyimx214_sensor.stream_on = sonyimx214_stream_on;
	sonyimx214_sensor.get_format = sonyimx214_get_format;

	sonyimx214_sensor.set_flash = NULL;
	sonyimx214_sensor.get_flash = NULL;
	sonyimx214_sensor.set_scene = NULL;
	sonyimx214_sensor.get_scene = NULL;

	sonyimx214_sensor.set_hflip = sonyimx214_set_hflip;
	sonyimx214_sensor.get_hflip = sonyimx214_get_hflip;
	sonyimx214_sensor.set_vflip = sonyimx214_set_vflip;
	sonyimx214_sensor.get_vflip = sonyimx214_get_vflip;
	sonyimx214_sensor.update_flip = sonyimx214_update_flip;
	sonyimx214_sensor.hflip = 0;
	sonyimx214_sensor.vflip = 0;
	sonyimx214_sensor.old_flip = 0;

	sonyimx214_sensor.enum_framesizes = sonyimx214_enum_framesizes;
	sonyimx214_sensor.try_framesizes = sonyimx214_try_framesizes;
	sonyimx214_sensor.set_framesizes = sonyimx214_set_framesizes;
	sonyimx214_sensor.get_framesizes = sonyimx214_get_framesizes;
	sonyimx214_sensor.enum_frame_intervals = sonyimx214_enum_frame_intervals;
	sonyimx214_sensor.try_frame_intervals = NULL;
	sonyimx214_sensor.set_frame_intervals = NULL;
	sonyimx214_sensor.get_frame_intervals = NULL;
	sonyimx214_sensor.get_capability = sonyimx214_get_capability;

	sonyimx214_sensor.sensor_gain_to_iso = sonyimx214_gain_to_iso;
	sonyimx214_sensor.sensor_iso_to_gain = sonyimx214_iso_to_gain;
	sonyimx214_sensor.set_gain = sonyimx214_set_gain;
	sonyimx214_sensor.get_gain = sonyimx214_get_gain;
	sonyimx214_sensor.set_exposure = sonyimx214_set_exposure;
	sonyimx214_sensor.get_exposure = sonyimx214_get_exposure;
	sonyimx214_sensor.set_exposure_gain = sonyimx214_set_exposure_gain;
	sonyimx214_sensor.set_vts = sonyimx214_set_vts;
	sonyimx214_sensor.get_vts_reg_addr = sonyimx214_get_vts_reg_addr;

	sonyimx214_sensor.get_flash_awb = sonyimx214_get_flash_awb;
	sonyimx214_sensor.update_framerate = NULL;
	sonyimx214_sensor.get_sensor_aperture = sonyimx214_get_sensor_aperture;
	sonyimx214_sensor.get_equivalent_focus = NULL;
	/*parameter*/
	sonyimx214_sensor.set_effect = NULL;
	sonyimx214_sensor.skip_frames = 2;

	sonyimx214_sensor.interface_type = MIPI1;
	sonyimx214_sensor.mipi_lane_count = CSI_LINES_4;
	sonyimx214_sensor.mipi_index = CSI_INDEX_0;

	sonyimx214_sensor.power_conf.pd_valid = LOW_VALID;
	sonyimx214_sensor.power_conf.reset_valid = LOW_VALID;
	sonyimx214_sensor.power_conf.vcmpd_valid = LOW_VALID;

	sonyimx214_sensor.sensor_index = CAMERA_SENSOR_PRIMARY;
	sonyimx214_sensor.i2c_config.index = I2C_PRIMARY;
	sonyimx214_sensor.i2c_config.speed = I2C_SPEED_400;
	sonyimx214_sensor.i2c_config.addr = SONYIMX214_SLAVE_ADDRESS;
	sonyimx214_sensor.i2c_config.addr_bits = I2C_16BIT;
	sonyimx214_sensor.i2c_config.val_bits = I2C_8BIT;
	sonyimx214_sensor.sensor_type = SENSOR_SONY;
	sonyimx214_sensor.sensor_rgb_type = SENSOR_RGGB;

#ifdef SONYIMX214_AP_WRITEAE_MODE 
	sonyimx214_sensor.aec_addr[0] = 0;
	sonyimx214_sensor.aec_addr[1] = 0;
	sonyimx214_sensor.aec_addr[2] = 0;
	sonyimx214_sensor.agc_addr[0] = 0;
	sonyimx214_sensor.agc_addr[1] = 0;
	sonyimx214_sensor.ap_writeAE_delay = 0; 
#else
	sonyimx214_sensor.aec_addr[0] = 0x0000;
	sonyimx214_sensor.aec_addr[1] = 0x0202;
	sonyimx214_sensor.aec_addr[2] = 0x0203;
	sonyimx214_sensor.agc_addr[0] = 0x0000; 
	sonyimx214_sensor.agc_addr[1] = 0x0205;
#endif
	sonyimx214_sensor.fps_max = 30;
	sonyimx214_sensor.fps_min = 10;
	sonyimx214_sensor.fps = 25;
	sonyimx214_sensor.isp_location = CAMERA_USE_K3ISP;
	sonyimx214_sensor.sensor_tune_ops = NULL;
	sonyimx214_sensor.fmt[STATE_PREVIEW] = V4L2_PIX_FMT_RAW10;
	sonyimx214_sensor.fmt[STATE_CAPTURE] = V4L2_PIX_FMT_RAW10;
	sonyimx214_sensor.preview_frmsize_index = 0;
	sonyimx214_sensor.capture_frmsize_index = 0;
	sonyimx214_sensor.frmsize_list = sonyimx214_framesizes;
	sonyimx214_sensor.af_enable = 1;
	sonyimx214_sensor.image_setting.lensc_param = NULL;
	sonyimx214_sensor.image_setting.ccm_param = NULL;
	sonyimx214_sensor.image_setting.awb_param = NULL;
	sonyimx214_sensor.rcc_enable = false;

	sonyimx214_sensor.owner = THIS_MODULE;
	sonyimx214_sensor.lane_clk = CLK_750M;
	sonyimx214_sensor.support_summary = false;
	sonyimx214_sensor.isp_idi_skip = false;
}

/*sonyimx214_module_init*/
static __init int sonyimx214_module_init(void)
{
	sonyimx214_set_default();
	return register_camera_sensor(sonyimx214_sensor.sensor_index, &sonyimx214_sensor);
}

/*sonyimx214_module_exit*/
static void __exit sonyimx214_module_exit(void)
{
	unregister_camera_sensor(sonyimx214_sensor.sensor_index, &sonyimx214_sensor);
}

MODULE_AUTHOR("Hisilicon");
module_init(sonyimx214_module_init);
module_exit(sonyimx214_module_exit);
MODULE_LICENSE("GPL");
/********************************** END **********************************************/
