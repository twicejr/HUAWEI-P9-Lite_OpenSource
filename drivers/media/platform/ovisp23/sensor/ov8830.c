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
#include "sensor_common.h"

struct sensor_power_setting ov8830_power_setting[] = {
	{
		.seq_type = SENSOR_AVDD,
		.data = (void*)"pri-cameralog-vcc",
		.config_val = LDO_VOLTAGE_2P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
	},
	{
		.seq_type = SENSOR_IOVDD,
		.data = (void*)"camera-vcc",
		.config_val = LDO_VOLTAGE_1P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
	},
	{
		.seq_type = SENSOR_PWDN,
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
	},
	{
		.seq_type = SENSOR_VCM_PWDN,
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
	},
	{
		.seq_type = SENSOR_IOCFG,
		.config_val = SENSOR_IO_ENABLE,
		.sensor_index = SENSOR_INDEX_INVALID,
	},
	{
		.seq_type = SENSOR_DVDD,
		.config_val = SENSOR_GPIO_HIGH,
		.sensor_index = SENSOR_INDEX_INVALID,
	},
	{
		.seq_type = SENSOR_VCM_AVDD,
		.data = (void*)"cameravcm-vcc",
		.config_val = LDO_VOLTAGE_2P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
	},
	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = SENSOR_INDEX_INVALID,
	},
	{
		.seq_type = SENSOR_RST,
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
	},
};

int ov8830_match_id(struct hisi_sensor_ctrl_t *s_ctrl)
{
	cam_debug("%s enter.\n", __func__);

	return 0;
}

int ov8830_ioctl(struct hisi_sensor_ctrl_t *s_ctrl, void *data)
{
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data*)data;
	long   rc = 0;

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

struct hisi_sensor_fn_t ov8830_func_tbl = {
	.sensor_config = hisi_sensor_config,
	.sensor_power_up = hisi_sensor_power_up,
	.sensor_power_down = hisi_sensor_power_down,
	.sensor_i2c_read = hisi_sensor_i2c_read,
	.sensor_i2c_write = hisi_sensor_i2c_write,
	.sensor_i2c_read_seq = hisi_sensor_i2c_read_seq,
	.sensor_i2c_write_seq = hisi_sensor_i2c_write_seq,
	.sensor_ioctl = ov8830_ioctl,
	.sensor_match_id = ov8830_match_id,
};

static int32_t ov8830_sensor_probe(struct platform_device *pdev)
{
	int32_t rc = 0;
	struct hisi_sensor_t *sensor = NULL;

	cam_info("%s pdev name %s\n", __func__, pdev->name);

	sensor = (struct hisi_sensor_t*)kzalloc(sizeof(struct hisi_sensor_t),
						GFP_KERNEL);
	if (NULL == sensor) {
		return -ENOMEM;
	}

	sensor->func_tbl = &ov8830_func_tbl;
	sensor->power_setting_array.power_setting = ov8830_power_setting;
	sensor->power_setting_array.size = ARRAY_SIZE(ov8830_power_setting);
	if (pdev->dev.of_node) {
		rc = hisi_sensor_get_dt_data(pdev, sensor);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			return rc;
		}
	} else {
		cam_err("%s ov8830 of_node is NULL.\n", __func__);
	}

	rc = hisi_sensor_add(sensor);
	if (rc < 0) {
		cam_err("%s fail to add sensor into sensor array.\n", __func__);
	}
	if (!dev_get_drvdata(&pdev->dev)) {
		dev_set_drvdata(&pdev->dev, (void *)sensor);
	}
	return rc;
}

static const struct of_device_id hisi_ov8830_dt_match[] = {
	{.compatible = "hisi,ov8830_liteon"},
	{.compatible = "hisi,ov8830_sunny"},
	{}
};
MODULE_DEVICE_TABLE(of, hisi_ov8830_dt_match);
static struct platform_driver ov8830_platform_driver = {
	.driver = {
		.name = "ov8830",
		.owner = THIS_MODULE,
		.of_match_table = hisi_ov8830_dt_match,
	},
};

static int32_t ov8830_platform_probe(struct platform_device *pdev)
{
	int32_t rc = 0;
	const struct of_device_id *match;

	match = of_match_device(hisi_ov8830_dt_match, &pdev->dev);
	cam_notice("%s compatible=%s.\n", __func__, match->compatible);
	rc = ov8830_sensor_probe(pdev);
	return rc;
}

static int __init ov8830_module_init(void)
{
	int rc = 0;
	cam_debug("%s:%d\n", __func__, __LINE__);

	rc = platform_driver_probe(&ov8830_platform_driver,
		ov8830_platform_probe);
	if (rc < 0) {
		cam_err("%s platform_driver_probe error(%d).\n", __func__, rc);
	}
	return rc;
}

static void __exit ov8830_module_exit(void)
{
	platform_driver_unregister(&ov8830_platform_driver);
}

MODULE_AUTHOR("HISI");
module_init(ov8830_module_init);
module_exit(ov8830_module_exit);
MODULE_LICENSE("GPL");
