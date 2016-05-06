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

#include <linux/fs.h>
#include <linux/of_gpio.h>
#include "hisi_sensor.h"
#include "../hisi_subdev.h"
#include "../hisi_cam_module.h"
#include "../csi/hisi_csi.h"

#define FILE_NAME_LEN	64


static struct hisi_sensor_t *sensor_array[CAMERA_SENSOR_MAX][CAMERA_SENSOR_ARRAY_SIZE];

DEFINE_HISI_SENSOR_CTRL(0);
DEFINE_HISI_SENSOR_CTRL(1);

/*************************************/
int hisi_sensor_add(struct hisi_sensor_t *sensor)
{
	int i;

	for (i = 0; i < CAMERA_SENSOR_ARRAY_SIZE; i++) {
		if (NULL == sensor_array[sensor->sensor_info->sensor_index][i]) {
			sensor_array[sensor->sensor_info->sensor_index][i]
				= sensor;
			cam_debug("%s index=%d, i=%d, name=%s.\n", __func__,
			sensor->sensor_info->sensor_index, i,
			sensor->sensor_info->name);
			return 0;
		}
	}

	cam_err("%s: sensor_array[%d] is overflow!!!", __func__,
	sensor->sensor_info->sensor_index);
	return -EFAULT;
}
EXPORT_SYMBOL(hisi_sensor_add);


int hisi_sensor_del(struct hisi_sensor_t *sensor)
{
	int i;

	for (i = 0; i < CAMERA_SENSOR_ARRAY_SIZE; i++) {
		if (sensor == sensor_array[sensor->sensor_info->sensor_index][i]) {
			sensor_array[sensor->sensor_info->sensor_index][i] = NULL;
			kfree(sensor);
			return 0;
		}
	}

	cam_err("%s del sensor error.\n", __func__);
	return -EFAULT;
}
EXPORT_SYMBOL(hisi_sensor_del);


int hisi_sensor_get_dt_data(struct platform_device *pdev,
	struct hisi_sensor_t *sensor)
{
	struct device_node *of_node = pdev->dev.of_node;
	struct hisi_sensor_info *sensor_info = NULL;
	int rc = 0;
	u32 i, index = 0;
	char *gpio_tag = NULL;
	const char *gpio_ctrl_types[IO_MAX] =
		{"reset", "fsin", "pwdn", "vcm_pwdn", "suspend"};

	cam_debug("enter %s", __func__);
	sensor_info = kzalloc(sizeof(struct hisi_sensor_info),
				GFP_KERNEL);
	if (!sensor_info) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return -ENOMEM;
	}
	sensor->sensor_info = sensor_info;

	rc = of_property_read_string(of_node, "hisi,sensor_name",
		&sensor_info->name);
	cam_debug("%s hisi,sensor_name %s, rc %d\n", __func__,
		sensor_info->name, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,sensor_index",
		&sensor_info->sensor_index);
	cam_debug("%s hisi,sensor_index %d, rc %d\n", __func__,
		sensor_info->sensor_index, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,interface_type",
		&sensor_info->interface_type);
	cam_debug("%s hisi,interface_type %d, rc %d\n", __func__,
		sensor_info->interface_type, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,csi_lane",
		&sensor_info->csi_lane);
	cam_debug("%s hisi,csi_lane %d, rc %d\n", __func__,
		sensor_info->csi_lane, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,csi_mipi_clk",
		&sensor_info->csi_mipi_clk);
	cam_debug("%s hisi,csi_mipi_clk %d, rc %d\n", __func__,
		sensor_info->csi_mipi_clk, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,csi_index",
		&sensor_info->csi_index);
	cam_debug("%s hisi,csi_index %d, rc %d\n", __func__,
		sensor_info->csi_index, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,pd_valid",
		&sensor_info->power_conf.pd_valid);
	cam_debug("%s hisi,pd_valid %d, rc %d\n", __func__,
		sensor_info->power_conf.pd_valid, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,reset_valid",
		&sensor_info->power_conf.reset_valid);
	cam_debug("%s hisi,reset_valid %d, rc %d\n", __func__,
		sensor_info->power_conf.reset_valid, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,vcmpd_valid",
		&sensor_info->power_conf.vcmpd_valid);
	cam_debug("%s hisi,vcmpd_valid %d, rc %d\n", __func__,
		sensor_info->power_conf.vcmpd_valid, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,i2c-index",
		&sensor_info->i2c_config.index);
	cam_debug("%s hisi,i2c-index %d, rc %d\n", __func__,
		sensor_info->i2c_config.index, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,i2c-speed",
		&sensor_info->i2c_config.speed);
	cam_debug("%s hisi,i2c-speed %d, rc %d\n", __func__,
		sensor_info->i2c_config.speed, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,i2c-addr",
		&sensor_info->i2c_config.addr);
	cam_debug("%s hisi,i2c-addr 0x%x, rc %d\n", __func__,
		sensor_info->i2c_config.addr, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,i2c-addr_bits",
		&sensor_info->i2c_config.addr_bits);
	cam_debug("%s hisi,i2c-addr_bits %d, rc %d\n", __func__,
		sensor_info->i2c_config.addr_bits, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,i2c-val_bits",
		&sensor_info->i2c_config.val_bits);
	cam_debug("%s hisi,i2c-val_bits %d, rc %d\n", __func__,
		sensor_info->i2c_config.val_bits, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,sensor_chipid",
		&sensor_info->sensor_chipid);
	cam_debug("%s hisi,sensor_chipid 0x%x, rc %d\n", __func__,
		sensor_info->sensor_chipid, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,camif_id",
		&sensor_info->camif_id);
	cam_debug("%s hisi,camif_id 0x%x, rc %d\n", __func__,
		sensor_info->camif_id, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,vcm_enable",
		&sensor_info->vcm_enable);
	cam_debug("%s hisi,vcm_enable %d, rc %d\n", __func__,
		sensor_info->vcm_enable, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	if (sensor_info->vcm_enable) {
		rc = of_property_read_string(of_node, "hisi,vcm_name",
			&sensor_info->vcm_name);
		cam_debug("%s hisi,vcm_name %s, rc %d\n", __func__,
			sensor_info->vcm_name, rc);
		if (rc < 0) {
			cam_err("%s failed %d\n", __func__, __LINE__);
			goto fail;
		}
	}

	if (is_fpga_board())
		return rc;

	/* get ldo */
	sensor_info->ldo_num = of_property_count_strings(of_node, "hisi,ldo-names");
	if(sensor_info->ldo_num < 0) {
			cam_err("%s failed %d\n", __func__, __LINE__);
			goto fail;
	}
	cam_debug("ldo num = %d", sensor_info->ldo_num);
	for (i = 0; i < sensor_info->ldo_num; i++) {
		rc = of_property_read_string_index(of_node, "hisi,ldo-names",
			i, &sensor_info->ldo[i].supply);
		if(rc < 0) {
			cam_err("%s failed %d\n", __func__, __LINE__);
			goto fail;
		}
	}

	rc = devm_regulator_bulk_get(&(pdev->dev), sensor_info->ldo_num, sensor_info->ldo);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	sensor_info->gpio_num = of_gpio_count(of_node);
	if(sensor_info->gpio_num < 0 ) {
			cam_err("%s failed %d\n", __func__, __LINE__);
			goto fail;
	}
	for(i = 0; i < sensor_info->gpio_num; i++) {
		rc = of_property_read_string_index(of_node, "hisi,gpio-ctrl-types",
			i, (const char **)&gpio_tag);
		if(rc < 0) {
			cam_err("%s failed %d\n", __func__, __LINE__);
			goto fail;
		}
		for(index = 0; index < IO_MAX; index++) {
			if(!strcmp(gpio_ctrl_types[index], gpio_tag))
				sensor_info->gpios[index].gpio = of_get_gpio(of_node, i);
		}
		cam_info("gpio ctrl types: %s\n", gpio_tag);
	}

	return rc;
fail:
	cam_err("%s error exit.\n", __func__);
	kfree(sensor_info);
	sensor_info = NULL;
	return rc;
}
EXPORT_SYMBOL(hisi_sensor_get_dt_data);

/*************************************/


static struct hisi_sensor_ctrl_t *get_sctrl(struct v4l2_subdev *sd)
{
	return container_of(container_of(sd, struct hisi_sd_subdev, sd),
		struct hisi_sensor_ctrl_t, hisi_sd);
}

static int hisi_sensor_get_pos(int index)
{
	mm_segment_t fs;
	struct file *filp = NULL;
	char file_name[FILE_NAME_LEN]={0};
	int pos=-1;

	snprintf(file_name, FILE_NAME_LEN, "/data/camera/hisi_sensor%d", index);
	cam_debug("%s index=%d.sensor name:%s\n", __func__, index, file_name);

	filp = filp_open(file_name, O_RDONLY, 0444);
	if (IS_ERR_OR_NULL(filp)) {
		cam_err("%s, fail to open file.\n", __func__);
		return pos;
	}

	fs = get_fs();
	set_fs(KERNEL_DS);
	if (sizeof(pos) != vfs_read(filp, (char*)&pos, sizeof(pos), &filp->f_pos)) {
		cam_err("%s, fail to read file.\n", __func__);
		pos=-EFAULT;
	} else {
		cam_debug("%s pos=%d.\n", __func__, pos);
	}

	set_fs(fs);

	if (NULL != filp) {
		filp_close(filp, NULL);
	}

	return pos;
}

static int hisi_sensor_set_pos(int index, int pos, const char *sensor_name)
{
	mm_segment_t fs;
	struct file *filp = NULL;
	char file_name[FILE_NAME_LEN]={0};
	char data[FILE_NAME_LEN]={0};
	int rc=0;

	cam_info("%s index=%d,pos=%d,sensor_name=%s.\n", __func__, index, pos, sensor_name);

	snprintf(file_name, FILE_NAME_LEN, "/data/camera/hisi_sensor%d", index);

	filp = filp_open(file_name, O_CREAT|O_WRONLY, 0666);
	if (IS_ERR_OR_NULL(filp)) {
		rc = -EFAULT;
		cam_err("%s, fail to open file.\n", __func__);
		return rc;
	}

	fs = get_fs();
	set_fs(KERNEL_DS);
	if (sizeof(pos) != vfs_write(filp, (char*)&pos, sizeof(pos), &filp->f_pos)) {
		rc = -EFAULT;
		cam_err("%s, fail to write pos into file.\n", __func__);
		goto fail;
	}

	snprintf(data, FILE_NAME_LEN, ":%s", sensor_name);
	if (sizeof(data) != vfs_write(filp, data, sizeof(data), &filp->f_pos)) {
		rc = -EFAULT;
		cam_err("%s, fail to write sensor name into file.\n", __func__);
	}

fail:
	set_fs(fs);

	if (NULL != filp) {
		filp_close(filp, NULL);
	}

	return rc;
}

static int hisi_sensor_check(struct hisi_sensor_ctrl_t *s_ctrl)
{
	int rc = -EFAULT;

	if (NULL != s_ctrl && NULL != s_ctrl->sensor
		&& NULL != s_ctrl->sensor->func_tbl->sensor_match_id) {
		rc = s_ctrl->sensor->func_tbl->sensor_match_id(s_ctrl);
	} else {
		cam_err("%s check sensor error.", __func__);
	}

	return rc;
}

static int hisi_sensor_init(struct hisi_sensor_ctrl_t *s_ctrl)
{
	int i;
	int rc = 0;
	int pos = 0;

	cam_info("%s enter.\n", __func__);

	pos = hisi_sensor_get_pos(s_ctrl->index);
	if (pos >= 0 && pos < CAMERA_SENSOR_ARRAY_SIZE) {
		s_ctrl->sensor = s_ctrl->sensor_array[pos];
		rc = hisi_sensor_check(s_ctrl);
		if(0 == rc) {
			return 0;
		}
	}

	for (i = 0; i < CAMERA_SENSOR_ARRAY_SIZE; i++) {
		if (i == pos) {
			continue;
		}

		s_ctrl->sensor = s_ctrl->sensor_array[i];
		rc = hisi_sensor_check(s_ctrl);
		if (0 == rc) {
			hisi_sensor_set_pos(s_ctrl->index, i,
				s_ctrl->sensor->sensor_info->name);
			return 0;
		}
	}

	s_ctrl->sensor = NULL;

	cam_err("%s init sensor error.\n", __func__);
	return -EFAULT;
}

int hisi_sensor_config(struct hisi_sensor_ctrl_t *s_ctrl, void *arg)
{
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)arg;
	long   rc = 0;

	cam_info("%s enter cfgtype=%d.\n", __func__, cdata->cfgtype);

	mutex_lock(s_ctrl->hisi_sensor_mutex);

	switch (cdata->cfgtype) {
	case CFG_SENSOR_POWER_DOWN:
		rc = s_ctrl->sensor->func_tbl->sensor_power_down(s_ctrl);
		break;
	case CFG_SENSOR_POWER_UP:
		rc = s_ctrl->sensor->func_tbl->sensor_power_up(s_ctrl);
		break;
	case CFG_SENSOR_I2C_READ:
		rc = s_ctrl->sensor->func_tbl->sensor_i2c_read(s_ctrl, arg);
		break;
	case CFG_SENSOR_I2C_WRITE:
		rc = s_ctrl->sensor->func_tbl->sensor_i2c_write(s_ctrl, arg);
		break;
	case CFG_SENSOR_I2C_READ_SEQ:
		rc = s_ctrl->sensor->func_tbl->sensor_i2c_read_seq(s_ctrl, arg);
		break;
	case CFG_SENSOR_I2C_WRITE_SEQ:
		rc = s_ctrl->sensor->func_tbl->sensor_i2c_write_seq(s_ctrl, arg);
		break;
	case CFG_SENSOR_GET_SENSOR_NAME:
		strncpy(cdata->cfg.name, s_ctrl->sensor->sensor_info->name,
			sizeof(cdata->cfg.name) - 1);
		rc = 0;
		break;
	default:
		rc = s_ctrl->sensor->func_tbl->sensor_ioctl(s_ctrl, arg);
		break;
	}

	mutex_unlock(s_ctrl->hisi_sensor_mutex);

	return rc;
}
EXPORT_SYMBOL(hisi_sensor_config);


static long hisi_sensor_subdev_ioctl(struct v4l2_subdev *sd,
			unsigned int cmd, void *arg)
{
	struct hisi_sensor_ctrl_t *s_ctrl = get_sctrl(sd);
	int rc=0;

	if (!s_ctrl) {
		cam_err("%s s_ctrl NULL\n", __func__);
		return -EBADF;
	}

	if (!s_ctrl->sensor) {
		rc = hisi_sensor_init(s_ctrl);
		if (rc < 0) {
			cam_err("%s s_ctrl NULL\n", __func__);
			return -EBADF;
		}
	}

	switch (cmd) {
	case VIDIOC_HISI_SENSOR_CFG:
		rc =  s_ctrl->sensor->func_tbl->sensor_config(s_ctrl, arg);
		break;
	case VIDIOC_HISI_CSI_ENABLE:
		rc = s_ctrl->csi_ctrl->hisi_csi_enable(
				s_ctrl->sensor->sensor_info->csi_index,
				s_ctrl->sensor->sensor_info->csi_lane,
				s_ctrl->sensor->sensor_info->csi_mipi_clk);
		break;
	case VIDIOC_HISI_CSI_DISABLE:
		rc = s_ctrl->csi_ctrl->hisi_csi_disable(
				s_ctrl->sensor->sensor_info->csi_index);
		break;
	default:
		cam_err("%s cmd is error .", __func__);
		rc = -ENOIOCTLCMD;
		break;
	}

	return rc;
}


static struct v4l2_subdev_core_ops hisi_sensor_subdev_core_ops = {
	.ioctl = hisi_sensor_subdev_ioctl,
};

static struct v4l2_subdev_ops hisi_sensor_subdev_ops = {
	.core = &hisi_sensor_subdev_core_ops,
};

static int32_t hisi_sensor_platform_probe(struct platform_device *pdev,
	void *data)
{
	int32_t rc = 0;
	uint32_t group_id;
	struct hisi_sensor_ctrl_t *s_ctrl =
		(struct hisi_sensor_ctrl_t *)data;
	const char *sd_name = NULL;

	s_ctrl->pdev = pdev;
	s_ctrl->dev = &pdev->dev;
	group_id = s_ctrl->index ? HISI_CAMERA_SUBDEV_SENSOR1
				: HISI_CAMERA_SUBDEV_SENSOR0;

	if (!s_ctrl->sensor_v4l2_subdev_ops)
		s_ctrl->sensor_v4l2_subdev_ops = &hisi_sensor_subdev_ops;

	v4l2_subdev_init(&s_ctrl->hisi_sd.sd,
			s_ctrl->sensor_v4l2_subdev_ops);

	rc = of_property_read_string(pdev->dev.of_node, "hisi,sensor-name",
		&sd_name);
	cam_notice("%s name %s, rc %d\n", __func__, sd_name, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
	}

	snprintf(s_ctrl->hisi_sd.sd.name,
		sizeof(s_ctrl->hisi_sd.sd.name), "%s",
		sd_name);

	cam_debug("%s sd.name is %s.\n", __func__, s_ctrl->hisi_sd.sd.name);

	v4l2_set_subdevdata(&s_ctrl->hisi_sd.sd, pdev);
	s_ctrl->hisi_sd.sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	media_entity_init(&s_ctrl->hisi_sd.sd.entity, 0, NULL, 0);
	s_ctrl->hisi_sd.sd.entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
	s_ctrl->hisi_sd.sd.entity.group_id = group_id;
	s_ctrl->hisi_sd.sd.entity.name = s_ctrl->hisi_sd.sd.name;
	hisi_sd_register(&s_ctrl->hisi_sd);

	return rc;
}

static const struct of_device_id hisi_sensor_dt_match[] = {
	{.compatible = "hisi,hisi_sensor_0", .data = &hisi_s_ctrl_0},
	{.compatible = "hisi,hisi_sensor_1", .data = &hisi_s_ctrl_1},
	{}
};
MODULE_DEVICE_TABLE(of, hisi_sensor_dt_match);

static struct platform_driver sensor_platform_driver = {
	.driver = {
		.name = "hisi_sensor",
		.owner = THIS_MODULE,
		.of_match_table = hisi_sensor_dt_match,
	},
};

static int32_t sensor_platform_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;

	match = of_match_device(hisi_sensor_dt_match, &pdev->dev);
	if(!match) {
		cam_err("pmu led match device failed");
		return -1;
	}	
	cam_notice("%s compatible=%s.\n", __func__, match->compatible);
	return hisi_sensor_platform_probe(pdev, (void*)match->data);
}

static int __init sensor_module_init(void)
{
	int rc = 0;
	cam_debug("%s:%d\n", __func__, __LINE__);

	rc = platform_driver_probe(&sensor_platform_driver,
		sensor_platform_probe);
	if (rc < 0) {
		cam_err("%s platform_driver_probe error(%d).\n", __func__, rc);
	}
	return rc;
}

static void __exit sensor_module_exit(void)
{
	platform_driver_unregister(&sensor_platform_driver);
}

module_init(sensor_module_init);
module_exit(sensor_module_exit);
MODULE_DESCRIPTION("hisi_sensor");
MODULE_LICENSE("GPL v2");
