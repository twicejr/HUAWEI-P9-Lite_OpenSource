/*
 *  Hisilicon K3 soc camera sensors source file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
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
//#include <mach/gpio.h>
#include <linux/hisi/hi6xxx-boardid.h>
//#include <linux/mux.h>

/* #define DEBUG_DEBUG 0 */
#define LOG_TAG "SENSOR_COMMON"
#include "cam_log.h"
#include "sensor_common.h"
#include "video_config.h"

#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
#endif

#if 0
static struct iomux_pin *gpio_core_ldo;
static struct iomux_pin *gpio_main_camera_id;
static struct iomux_pin *gpio_slave_camera_id;
#endif
/* camera sensors array */
static camera_sensor *primary_sensor_array[CAMERA_SENSOR_NUM_MAX];
static camera_sensor *secondary_sensor_array[CAMERA_SENSOR_NUM_MAX];
static camera_sensor *primary_sensor;
static camera_sensor *secondary_sensor;

/* camera timing type
 * 0: samsung & sony sensor timing,
 * 1: ov8830 sensor timing.
 */
static int camera_timing_type;

static camera_flashlight *camera_flash_dev = NULL;
framesize_s camera_framesizes[CAMERA_RESOLUTION_MAX] = {
	/* CAMERA_RESOLUTION_QCIF */
	{176, 144},
	/* CAMERA_RESOLUTION_240x176 */
	{240, 176},
	/* CAMERA_RESOLUTION_QVGA */
	{320, 240},
	/* CAMERA_RESOLUTION_CIF */
	{352, 288},
	/* CAMERA_RESOLUTION_HVGA */
	{480, 320},
	/* CAMERA_RESOLUTION_VGA */
	{640, 480},
	/* CAMERA_RESOLUTION_800x480 */
	{800, 480},
	/* CAMERA _RESOLUTION_SVGA */
	{800, 600},
	/* CAMERA_RESOLUTIONS_XGA */
	{1024, 768},
	{1280, 720},
	/* CAMERA_RESOLUTIONS_VGA4 */
	{1280, 960},
	/* CAMERA_RESOLUTION_QTR_5M,     1296 x 972 (2592 x 1944/4) */
	{1296, 972},
	/* CAMERA_RESOLUTIONS_SXGA */
	{1280, 1024},
	/* CAMERA_RESOLUTIONS_UXGA */
	{1600, 1200},
	/* CAMERA_RESOLUTION_1080P,      1920 x 1080  add by y26721 */
	{1920, 1080},

	/* CAMERA_RESOLUTION_QTR_8M,    1632 x 1224 (3264 x 2448/4) */
	{1632, 1224},
	/*  3M */
	/* CAMERA_RESOLUTIONS_QXGA */
	{2048, 1536},
	/* CAMERA_RESOLUTION_QTR_12M,   2104 x 1560 (4208 x 3120/4) */
	{2104, 1560},

	/* CAMERA_RESOLUTION_QTR_16M,   2304 x 1728 (4608 x 3456/4) */
	{2304, 1728},

	/* CAMERA_RESOLUTION_QTR_20M,    2582 x 1936(5164 x 3872/4) */
	{2582, 1936},

	/* CAMERA_RESOLUTION_FULL_5M,    2592 x 1944  */
	{2592, 1944},

	/* CAMERA_RESOLUTION_FULL_8M,    3264 x 2448  */
	{3264, 2448},

	/* CAMERA_RESOLUTION_FULL_12M,   4208 x 3120 */
	{4208, 3120},

	/* CAMERA_RESOLUTION_FULL_16M,   4608 x 3456  */
	{4608, 3456},

	/* CAMERA_RESOLUTION_FULL_20M,   5164 x 3872  */
	{5164, 3872},
};

EXPORT_SYMBOL(camera_framesizes);

/*
 * Focus driver ic dw9714 information:
 * Sunny ov8830/SonyImx105/S5k3h2yx use this driver ic
 */
vcm_info_s vcm_dw9714 = {
	.vcm_type = VCM_DW9714,
	.offsetInit = 0, /* maybe different in each AF mode */
	.fullRange = 1023, /* maybe different in each AF mode */

	.infiniteDistance = 0x50, /* should be calibrated */

	.normalDistanceEnd = 0x2b0,
	.normalStep = 0x20, /* coarse step */
	.normalStrideRatio = 0x18,

	.videoDistanceEnd = 0x200,
	.videoStep = 0x10,
	.videoStrideRatio = 0x20,

	.strideOffset = 0xc0,  /* large stride will start at (infiniteDistance+videoStrideOffset), this value must common multiple of videoStep and normalStep*/

	.vcm_bits = 9,
	.vcm_id = 0x18,
	/* moveLensAddr can be ommitted for DW9714 */
	.moveLensAddr[0] = 0,
	.moveLensAddr[1] = 0,


	.motorResTime = 10,
	.motorDelayTime = 12,
	.strideDivideOffset = 0x60,

	.startCurrentOffset = 0x40,


	.moveRange = RANGE_NORMAL,
};
EXPORT_SYMBOL(vcm_dw9714);

/*
 * Focus driver ic ad5823 information:
 * Foxconn ov8830 use this driver ic
 */
vcm_info_s vcm_ad5823 = {
	.vcm_type = VCM_AD5823,
	.offsetInit = 0, /* maybe different in each AF mode */
	.fullRange = 1023,	/* maybe different in each AF mode */

	.infiniteDistance = 0x20, /* default, should be calibrated */

	.normalDistanceEnd = 0x270,
	.normalStep = 0x20, /* coarse step */
	.normalStrideRatio = 0x18,

	.videoDistanceEnd = 0x1c0,
	.videoStep = 0x10,
	.videoStrideRatio = 0x20,

	.strideOffset = 0xc0, /* video large stride will start at (infiniteDistance+videoStrideOffset), this value must common multiple of videoStep and normalStep*/

	.vcm_bits = 1,
	.vcm_id = 0x18,
	/* msb is 0x4, lsb is 0x5 for AD5823 */
	.moveLensAddr[0] = 0x4,
	.moveLensAddr[1] = 0x5,

	.motorResTime = 7,
	.motorDelayTime = 5,
	.strideDivideOffset = 0x50,

	.moveRange = RANGE_NORMAL,
};
EXPORT_SYMBOL(vcm_ad5823);

/* sensor override parameter definitions. */
u32 sensor_override_params[OVERRIDE_TYPE_MAX] = {
	CAMERA_MAX_ISO,
	CAMERA_MIN_ISO,

	CAMERA_AUTOFPS_GAIN_HIGH2MID,
	CAMERA_AUTOFPS_GAIN_MID2LOW,

	CAMERA_AUTOFPS_GAIN_LOW2MID,
	CAMERA_AUTOFPS_GAIN_MID2HIGH,

	CAMERA_MAX_FRAMERATE,
	CAMERA_MID_FRAMERATE,
	CAMERA_MIN_FRAMERATE,
	CAMERA_MIN_CAP_FRAMERATE,

	CAMERA_FLASH_TRIGGER_GAIN,

	CAMERA_SHARPNESS_PREVIEW,
	CAMERA_SHARPNESS_CAPTURE,
};
EXPORT_SYMBOL(sensor_override_params);

/*
 **************************************************************************
 * FunctionName: camera_get_size_by_resolution;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int camera_get_size_by_resolution(camera_resolutions res, u32 *width,
				  u32 *height)
{
	if (res >= CAMERA_RESOLUTION_MAX) {
		return -1;
	}
	*width = camera_framesizes[res].width;
	*height = camera_framesizes[res].height;

	return 0;
}

EXPORT_SYMBOL(camera_get_size_by_resolution);

/*
 **************************************************************************
 * FunctionName: camera_match_resolution;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
camera_resolution_type camera_get_resolution_type(u32 width, u32 height)
{
	camera_resolution_type resolution_type;
	if (abs(width * 3 - height * 4) < abs(width * 9 - height * 16))
		resolution_type = RESOLUTION_4_3;
	else
		resolution_type = RESOLUTION_16_9;
	print_info("width:%d, height:%d, resolution_type:%d", width, height, resolution_type);

	return resolution_type;
}
EXPORT_SYMBOL(camera_get_resolution_type);

/*
 **************************************************************************
 * FunctionName: camera_get_resolution_by_width_height;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int camera_get_resolution_by_size(u32 width, u32 height)
{
	int i = 0;

	print_debug("%s(width=%d, height=%d)\n", __FUNCTION__, width, height);
	for (i = 0; i < ARRAY_SIZE(camera_framesizes); i++) {
		if (width == camera_framesizes[i].width  && height == camera_framesizes[i].height) {
			return i;
		}
	}

	return -1;
}
EXPORT_SYMBOL(camera_get_resolution_by_size);

/*
 **************************************************************************
 * FunctionName: relocate_camera_sensor_by_name;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */

void relocate_camera_sensor_by_name(sensor_index_t sensor_index,char *sensor_name)
{
    int i = 0;
    char* ret = NULL;
	camera_sensor **sensor_array = NULL;
    camera_sensor *target_sensor = NULL;


	if (sensor_index >= CAMERA_SENSOR_MAX) {
		print_error("invalid sensor index [%d]", sensor_index);
		return ;
	}

	if (CAMERA_SENSOR_PRIMARY == sensor_index)
		sensor_array = primary_sensor_array;
	else
		sensor_array = secondary_sensor_array;

	for (i = 0; i < CAMERA_SENSOR_NUM_MAX; i++)
	{
		if (NULL == sensor_array[i]){
            continue;
		}

        ret = strstr(sensor_name, sensor_array[i]->info.name);
        if (ret == NULL){
            continue;
        }

        target_sensor = sensor_array[i];
        sensor_array[i] = sensor_array[0];
        sensor_array[0] = target_sensor;
        print_info("i=%d target sensor =%s",i,target_sensor->info.name);
	}

}
EXPORT_SYMBOL(relocate_camera_sensor_by_name);



/*
 **************************************************************************
 * FunctionName: get_camera_sensor_from_array;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
camera_sensor *get_camera_sensor_from_array(sensor_index_t sensor_index)
{
	int i = 0;
	camera_sensor **sensor_array = NULL;


	if (sensor_index >= CAMERA_SENSOR_MAX) {
		print_error("invalid sensor index [%d]", sensor_index);
		return NULL;
	}

	if (CAMERA_SENSOR_PRIMARY == sensor_index)
		sensor_array = primary_sensor_array;
	else
		sensor_array = secondary_sensor_array;

	for (i = 0; i < CAMERA_SENSOR_NUM_MAX; i++)
	{
		if (NULL != sensor_array[i])
			break;
	}

	if (i >= CAMERA_SENSOR_NUM_MAX) {
		print_error("Unsupport sensor!!!");
		return NULL;
	}
	print_info("%s, sensor_index[%d], name[%s]", __func__, sensor_index, sensor_array[i]->info.name);
	return sensor_array[i];
}
EXPORT_SYMBOL(get_camera_sensor_from_array);
camera_sensor **get_camera_sensor_array(sensor_index_t sensor_index)
{
	if (sensor_index >= CAMERA_SENSOR_MAX) {
		print_error("invalid sensor index [%d]", sensor_index);
		return NULL;
	}
	if(CAMERA_SENSOR_PRIMARY == sensor_index)
		return primary_sensor_array;
	else
		return secondary_sensor_array;
}
EXPORT_SYMBOL(get_camera_sensor_array);
/*
 **************************************************************************
 * FunctionName: get_camera_sensor;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
camera_sensor **get_camera_sensor(sensor_index_t sensor_index)
{
	camera_sensor **ret = NULL;
	if (CAMERA_SENSOR_PRIMARY == sensor_index)
		ret = &primary_sensor;
	else
		ret = &secondary_sensor;
	return ret;
}
EXPORT_SYMBOL(get_camera_sensor);

/*
 **************************************************************************
 * FunctionName: get_camera_sensor;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void set_camera_sensor(sensor_index_t sensor_index, camera_sensor *sensor)
{
	assert(sensor);

	if (CAMERA_SENSOR_PRIMARY == sensor_index)
		primary_sensor = sensor;
	else
		secondary_sensor = sensor;
}
EXPORT_SYMBOL(set_camera_sensor);

/*
 **************************************************************************
 * FunctionName: clean_camera_sensor;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int clean_camera_sensor(sensor_index_t sensor_index)
{
	if (sensor_index >= CAMERA_SENSOR_MAX) {
		print_error("invalid sensor index [%d]", sensor_index);
		return -1;
	}

	if (CAMERA_SENSOR_PRIMARY == sensor_index)
		memset(primary_sensor_array, 0, sizeof(primary_sensor_array));
	else
		memset(secondary_sensor_array, 0, sizeof(secondary_sensor_array));

	return 0;
}
EXPORT_SYMBOL(clean_camera_sensor);

/*
 **************************************************************************
 * FunctionName: register_camera_sensor;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int register_camera_sensor(sensor_index_t sensor_index, camera_sensor *sensor)
{
	int i = 0;
	camera_sensor **sensor_array = NULL;
	print_debug("enter %s", __func__);

	if (sensor_index >= CAMERA_SENSOR_MAX) {
		print_error("register invalid sensor index [%d]", sensor_index);
		return -EINVAL;
	}
	if (NULL == sensor) {
		print_error("register NULL sensor pointer");
		return -EINVAL;
	}

	if (CAMERA_SENSOR_PRIMARY == sensor_index)
		sensor_array = primary_sensor_array;
	else
		sensor_array = secondary_sensor_array;

	for (i = 0; i < CAMERA_SENSOR_NUM_MAX; i++) {
		if (sensor_array[i] == NULL)
			break;
		if (0 == strcmp(sensor_array[i]->info.name, sensor->info.name)) {
			print_warn("sensor [%s] already registered", sensor->info.name);
			return 0;
		}
	}

	if (i >= CAMERA_SENSOR_NUM_MAX) {
		print_error("%s too many sensors", __func__);
	} else {
		sensor_array[i] = sensor;
	}

	print_info("register sensor [%s] with type [%d] to [%d]", sensor->info.name, sensor_index, i);

	return 0;
}
EXPORT_SYMBOL(register_camera_sensor);

/*
 **************************************************************************
 * FunctionName: unregister_camera_sensor;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int unregister_camera_sensor(sensor_index_t sensor_index, camera_sensor *sensor)
{
	int i = 0;
	camera_sensor **sensor_array = NULL;

	print_debug("enter %s", __func__);

	if (sensor_index >= CAMERA_SENSOR_MAX) {
		print_error("register invalid sensor index [%d]", sensor_index);
		return -EINVAL;
	}
	if (sensor == NULL) {
		print_warn("unregister NULL Sensor");
		return 0;
	}

	if (CAMERA_SENSOR_PRIMARY == sensor_index)
		sensor_array = primary_sensor_array;
	else
		sensor_array = secondary_sensor_array;

	for (i = 0; i < CAMERA_SENSOR_NUM_MAX; ++i) {
		if (sensor == sensor_array[i]) {
			sensor_array[i] = NULL;
			print_info("unregister camera sensor[%d][%d] name [%s]", sensor_index, i, sensor->info.name);
		}
	}

	return 0;
}
EXPORT_SYMBOL(unregister_camera_sensor);

/*
 **************************************************************************
 * FunctionName: dump_camera_sensors;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void dump_camera_sensors(void)
{
	int i = 0;
	print_debug("enter %s", __func__);

	print_debug("dump primary sensors:");
	for (i = 0; i < CAMERA_SENSOR_NUM_MAX; ++i) {
		if (primary_sensor_array[i])
			print_debug("[%s]", primary_sensor_array[i]->info.name);
	}

	print_debug("dump secondary sensors:");
	for (i = 0; i < CAMERA_SENSOR_NUM_MAX; ++i) {
		if (secondary_sensor_array[i])
			print_debug("[%s]", secondary_sensor_array[i]->info.name);
	}
}
EXPORT_SYMBOL(dump_camera_sensors);

int get_camera_count(void)
{
	int i = 0;
	int count = 0;

	for (i = 0; i < CAMERA_SENSOR_NUM_MAX; i++)
		if (NULL != primary_sensor_array[i])
			count++;

	for (i = 0; i < CAMERA_SENSOR_NUM_MAX; i++)
		if (NULL != secondary_sensor_array[i])
			count++;
	print_debug("camera count[%d]", count);
	return count;
}
EXPORT_SYMBOL(get_camera_count);

/*
 **************************************************************************
 * FunctionName: get_camera_flash;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
camera_flashlight *get_camera_flash()
{
	return camera_flash_dev;
}

EXPORT_SYMBOL(get_camera_flash);

/*
 **************************************************************************
 * FunctionName: register_camera_flash;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int register_camera_flash(camera_flashlight *flash)
{
	print_debug("enter %s", __FUNCTION__);
	if (NULL == flash) {
		print_error("register NULL sensor pointer");
		return -EINVAL;
	}

	if (camera_flash_dev != NULL && camera_flash_dev != flash) {
		print_error("flash has been registered");
		return -EINVAL;
	}

	camera_flash_dev = flash;

	print_info("register flash device [%d]", flash->type);
	return 0;
}

EXPORT_SYMBOL(register_camera_flash);

/*
 **************************************************************************
 * FunctionName: unregister_camera_flash;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int unregister_camera_flash(camera_flashlight *flash)
{
	print_debug("enter %s", __FUNCTION__);

	if (flash == NULL) {
		return 0;
	}

	if (flash == camera_flash_dev) {
		camera_flash_dev = NULL;
		print_info("unregister camera flash [%d]", flash->type);
	} else {
		print_error("invlid parameters: flash device[%p] not exit", flash);
		return -EINVAL;
	}

	return 0;
}

EXPORT_SYMBOL(unregister_camera_flash);

/*
 **************************************************************************
 * FunctionName: camera_power_core_ldo;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int camera_power_core_ldo(camera_power_state power)
{
	int ret = 0;

        /*V9R1 do not need this to power sensor core vcc*/

#if 0
	print_debug("enter %s", __FUNCTION__);
	if (NULL == gpio_core_ldo) {
		gpio_core_ldo = iomux_get_pin(CAM_VCC_PIN);
		if (!gpio_core_ldo) {
			print_error("fail to get CAM_VCC_PIN");
			return -EINVAL;
		}
	}

	if (POWER_ON == power) {
		print_info("power on core ldo");
		ret = pinmux_setpullupdown(gpio_core_ldo, NOPULL);
		if (ret < 0)
			print_error("fail to set gpio_core_ldo to NOPULL");

		ret = gpio_request(GPIO_21_5, "cam_vcc_en");
		if (ret < 0)
			print_error("fail to get GPIO_21_5");
		ret = gpio_direction_output(GPIO_21_5, 1);
		if (ret < 0)
			print_error("fail to set GPIO_21_5 to 1");

	} else {
		print_info("power off core ldo");
		ret = gpio_direction_output(GPIO_21_5, 0);
		if (ret < 0)
			print_error("fail to set GPIO_21_5 to 0");
		gpio_free(GPIO_21_5);
	}
#endif

	return ret;
}

EXPORT_SYMBOL(camera_power_core_ldo);

/*
 **************************************************************************
 * FunctionName: set_camera_timing_type;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
void set_camera_timing_type(int status)
{
	print_info("%s : status=%d.\n", __func__, status);
	camera_timing_type = status;
	return;
}

/*
 **************************************************************************
 * FunctionName: camera_timing_is_match;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int camera_timing_is_match(int type)
{
#if 0 /*Balong not sure how to identify different two sensor, just return 1, 20121225*/
	int timing = 0;

	timing = get_sensor_timing_type();

	print_info("%s : timing=%d.", __func__, timing);

	/* big board don't identify camera timing. */
	if (0 != timing) {
		return 1;
	} else {
		return (type == camera_timing_type);
	}
#else
    return 1;
#endif
}

/*
 **************************************************************************
 * FunctionName: camera_power_id_gpio;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int camera_power_id_gpio(camera_power_state power)
{
	int ret = 0;

	print_debug("enter %s", __FUNCTION__);

        /*FIXME:on V9R1 do not have this id gpio*/

#if 0
	if (POWER_ON == power) {
		if (NULL == gpio_main_camera_id) {
			gpio_main_camera_id = iomux_get_pin(CAM_ID_PIN);
			if (!gpio_main_camera_id) {
				print_error("fail to get CAM_ID_PIN");
				return -EINVAL;
			}
		}

		ret = pinmux_setpullupdown(gpio_main_camera_id, PULLUP);
		if (ret < 0)
			print_error("fail to set gpio_main_camera_id to PULLUP");

		ret = gpio_request(GPIO_13_7, NULL);
		if (ret < 0)
			print_error("fail to get GPIO_13_7");
		ret = gpio_direction_input(GPIO_13_7);
		if (ret < 0) {
			print_error("fail to set GPIO_13_7 input");
		} else {
			ret = gpio_get_value(GPIO_13_7);
			if (ret < 0)
				print_error("fail to get GPIO_13_7 value");
			set_camera_timing_type(ret);
		}

		if (NULL == gpio_slave_camera_id) {
			gpio_slave_camera_id = iomux_get_pin(SCAM_ID_PIN);
			if (!gpio_slave_camera_id) {
				print_error("fail to get CAM_ID_PIN");
				return -EINVAL;
			}
		}

		ret = pinmux_setpullupdown(gpio_slave_camera_id, PULLUP);
		if (ret < 0)
			print_error("fail to set gpio_slave_camera_id to PULLUP");

		ret = gpio_request(GPIO_14_0, NULL);
		if (ret < 0)
			print_error("fail to get GPIO_14_0");
		ret = gpio_direction_input(GPIO_14_0);
		if (ret < 0)
			print_error("fail to set GPIO_14_0 input");

	} else {
		if (NULL != gpio_main_camera_id) {
			if (pinmux_setpullupdown(gpio_main_camera_id, NOPULL) < 0)
				print_error("fail to set gpio_main_camera_id to NOPULL");
			gpio_main_camera_id = NULL;
			gpio_free(GPIO_13_7);
		}

		if (NULL != gpio_slave_camera_id) {
			if (pinmux_setpullupdown(gpio_slave_camera_id, NOPULL))
				print_error("fail to set gpio_slave_camera_id to NOPULL");
			gpio_slave_camera_id = NULL;
			gpio_free(GPIO_14_0);
		}
	}
#endif

	return ret;
}

EXPORT_SYMBOL(camera_power_id_gpio);

/*
 **************************************************************************
 * FunctionName: camera_get_i2c_speed;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
/* sccb clock = sclk / (64 * sccb speed) */
static int i2c_speed_array[][I2C_SPEED_MAX] = {
	{20, 10, 6},		/* SCLK = 131MHz */
	//{25, 12, 7},		/* SCLK = 160MHz */
	//{30, 15, 8},		/* SCLK = 200MHz */
	{30, 15, 9},		/* SCLK = 200MHz *//*i2c speed=347k*/
};

int camera_get_i2c_speed(unsigned int chip_id, i2c_speed_t i2c_speed_idx)
{
    print_info("chip_id = %u, i2c_speed_index = %d", chip_id, i2c_speed_idx);

    return i2c_speed_array[1][i2c_speed_idx];

}
EXPORT_SYMBOL(camera_get_i2c_speed);


/*
 **************************************************************************
 * FunctionName: camera_get_matching_sensor_config;
 * Description :  matching product,get the correct config sensor config setting;
 * Input       : sensor_config_array:the sensor's connfig array related to supported product;
                 array_size:sensor_config_array's size;
 * Output      : out_config: match config;
 * ReturnValue : 0 the matching config
                 other:get failed;
 * Other       : NA;
 **************************************************************************
 */
int camera_get_matching_sensor_config( const sensor_config_s sensor_config_array[], int array_size, const sensor_config_s**out_config)
{
    int temp_index = 0;
    const char* product = NULL;
    int ret = 0;

    print_debug("enter:%s,array_size:%d", __FUNCTION__,array_size);

    if(NULL == sensor_config_array){
        print_error("%s: fatal error, NULL ptr",__FUNCTION__);
        ret = -EINVAL;
        goto out;
    }

    if(video_get_product_name(&product) !=  0){
        print_error("%s: get product name failed",__FUNCTION__);
        ret = -EINVAL;
        goto out;
    }

    for(temp_index= 0; temp_index < array_size; temp_index++ )
    {
       if( !strncmp(product, sensor_config_array[temp_index].product, strlen(product)+1)){
            print_info("%s, find out the matching config,index:%d", __FUNCTION__,temp_index);
            break;
        }
    }

    if(temp_index >= array_size){
        print_error("%s: no correct config",__func__);
        ret = -EINVAL;
        goto out;
    }

    *out_config = &sensor_config_array[temp_index];
    ret = 0;
out:
    return ret;
}
EXPORT_SYMBOL(camera_get_matching_sensor_config);

/********************************** END **********************************************/
