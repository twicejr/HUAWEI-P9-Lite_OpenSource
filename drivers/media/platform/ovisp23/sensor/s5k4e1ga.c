/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#include "hisi_sensor.h"
#include "../cci/hisi_cci.h"
#include "sensor_common.h"

#define S5K4E1GA_GROUP_HOLD_REG			0x0104
#define S5K4E1GA_EXPOSURE_REG_H			0x0202
#define S5K4E1GA_EXPOSURE_REG_L			0x0203
#define S5K4E1GA_GAIN_REG_H				0x0204
#define S5K4E1GA_GAIN_REG_L				0x0205

struct sensor_power_setting s5k4e1ga_power_setting[] = {
	{
		.seq_type = SENSOR_AVDD,
		.data = (void*)"main-sensor-avdd",
		.config_val = LDO_VOLTAGE_2P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_IOVDD,
		.data = (void*)"common-iovdd",
		.config_val = LDO_VOLTAGE_1P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_DVDD,
		.config_val = LDO_VOLTAGE_1P05V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_AVDD2,
		.data = (void*)"slave-sensor-avdd",
		.config_val = LDO_VOLTAGE_2P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_PWDN,
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_RST,
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_I2C,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_SUSPEND,
		.config_val = SENSOR_GPIO_HIGH,
		.sensor_index = SENSOR_INDEX_INVALID,
	},
};

int s5k4e1ga_match_id(struct hisi_sensor_ctrl_t *s_ctrl)
{
	int ret = 0;
	u16 id_h = 0;
	u16 id_l = 0;
	u16 sensor_id = 0;

	cam_info( "%s, sensor_chipid:0x%x\n",
		__func__, s_ctrl->sensor->sensor_info->sensor_chipid);

	ret = hisi_sensor_power_up(s_ctrl);
	if(ret) {
		cam_err("sensor[%s] power up failed.", s_ctrl->sensor->sensor_info->name);
		ret = -1;
		goto out;
	}

	/* check sensor id */
	isp_read_sensor_byte(&s_ctrl->sensor->sensor_info->i2c_config, 0x0000, &id_h);

	isp_read_sensor_byte(&s_ctrl->sensor->sensor_info->i2c_config, 0x0001, &id_l);

	sensor_id = id_h << 8 | id_l;

	cam_notice( "sensor id:  0x%x", sensor_id);
	if (sensor_id != s_ctrl->sensor->sensor_info->sensor_chipid) {
		ret =  -1;
	}

out:
	hisi_sensor_power_down(s_ctrl);

	return ret;
}

int s5k4e1ga_ioctl(struct hisi_sensor_ctrl_t *s_ctrl, void *data)
{
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data*)data;
	int   rc = 0;

	cam_debug("%s enter.\n", __func__);

	switch (cdata->cfgtype) {
	case CFG_SENSOR_SET_VTS:
		cam_info("%s set vts.\n", __func__);
		break;
	default:
		rc = -EFAULT;
		break;
	}

	return rc;
}

int s5k4e1ga_set_expo_gain(struct hisi_sensor_t *cur_sensor, u32 expo, u16 gain)
{
	int rc = 0;

	isp_write_sensor_byte(&cur_sensor->sensor_info->i2c_config,
		S5K4E1GA_GROUP_HOLD_REG, 0x01, 0x00);

	gain = gain << 1;

	isp_write_sensor_byte(&cur_sensor->sensor_info->i2c_config,
		S5K4E1GA_GAIN_REG_H, (gain >> 8) & 0xff, 0x00);
	isp_write_sensor_byte(&cur_sensor->sensor_info->i2c_config,
		S5K4E1GA_GAIN_REG_L, gain & 0xff, 0x00);

	expo = expo >> 4;

	isp_write_sensor_byte(&cur_sensor->sensor_info->i2c_config,
		S5K4E1GA_EXPOSURE_REG_H, (expo >> 8) & 0xff, 0x00);
	isp_write_sensor_byte(&cur_sensor->sensor_info->i2c_config,
		S5K4E1GA_EXPOSURE_REG_L, expo & 0xff, 0x00);

	isp_write_sensor_byte(&cur_sensor->sensor_info->i2c_config,
		S5K4E1GA_GROUP_HOLD_REG, 0x00, 0x00);

	return rc;
}

struct hisi_sensor_fn_t s5k4e1ga_func_tbl = {
	.sensor_config = hisi_sensor_config,
	.sensor_power_up = hisi_sensor_power_up,
	.sensor_power_down = hisi_sensor_power_down,
	.sensor_i2c_read = hisi_sensor_i2c_read,
	.sensor_i2c_write = hisi_sensor_i2c_write,
	.sensor_i2c_read_seq = hisi_sensor_i2c_read_seq,
	.sensor_i2c_write_seq = hisi_sensor_i2c_write_seq,
	.sensor_ioctl = s5k4e1ga_ioctl,
	.sensor_match_id = s5k4e1ga_match_id,
	.sensor_set_expo_gain = s5k4e1ga_set_expo_gain,
};

static int32_t s5k4e1ga_sensor_probe(struct platform_device *pdev)
{
	int32_t rc = 0;
	struct hisi_sensor_t *sensor = NULL;

	cam_info("%s pdev name %s\n", __func__, pdev->name);

	sensor = (struct hisi_sensor_t*)kzalloc(sizeof(struct hisi_sensor_t),
						GFP_KERNEL);
	if (NULL == sensor) {
		return -ENOMEM;
	}

	sensor->func_tbl = &s5k4e1ga_func_tbl;
	sensor->power_setting_array.power_setting = s5k4e1ga_power_setting;
	sensor->power_setting_array.size = ARRAY_SIZE(s5k4e1ga_power_setting);

	if (pdev->dev.of_node) {
		rc = hisi_sensor_get_dt_data(pdev, sensor);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			return rc;
		}
	} else {
		cam_err("%s s5k4e1ga of_node is NULL.\n", __func__);
		kfree(sensor);
		sensor = NULL;
		return rc;
	}

	rc = hisi_sensor_add(sensor);
	if (rc < 0) {
		cam_err("%s fail to add sensor into sensor array.\n", __func__);
		kfree(sensor);
		sensor = NULL;
		return rc;
	}
	if (!dev_get_drvdata(&pdev->dev)) {
		dev_set_drvdata(&pdev->dev, (void *)sensor);
	}
	return rc;
}

static const struct of_device_id hisi_s5k4e1ga_dt_match[] = {
	{.compatible = "hisi,s5k4e1gx_sunny"},
	{}
};
MODULE_DEVICE_TABLE(of, hisi_s5k4e1ga_dt_match);
static struct platform_driver s5k4e1ga_platform_driver = {
	.driver = {
		.name = "s5k4e1ga",
		.owner = THIS_MODULE,
		.of_match_table = hisi_s5k4e1ga_dt_match,
	},
};

static int32_t s5k4e1ga_platform_probe(struct platform_device *pdev)
{
	int32_t rc = 0;
	const struct of_device_id *match;

	match = of_match_device(hisi_s5k4e1ga_dt_match, &pdev->dev);
	cam_notice("%s compatible=%s.\n", __func__, match->compatible);
	rc = s5k4e1ga_sensor_probe(pdev);
	return rc;
}

static int __init s5k4e1ga_module_init(void)
{
	int rc = 0;
	cam_info("%s:%d\n", __func__, __LINE__);

	rc = platform_driver_probe(&s5k4e1ga_platform_driver,
		s5k4e1ga_platform_probe);
	if (rc < 0) {
		cam_err("%s platform_driver_probe error.\n", __func__);
	}
	return rc;
}

static void __exit s5k4e1ga_module_exit(void)
{
	platform_driver_unregister(&s5k4e1ga_platform_driver);
}

MODULE_AUTHOR("HISI");
module_init(s5k4e1ga_module_init);
module_exit(s5k4e1ga_module_exit);
MODULE_LICENSE("GPL");
