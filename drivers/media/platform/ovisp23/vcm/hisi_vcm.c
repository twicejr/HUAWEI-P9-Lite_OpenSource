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


#include "hisi_vcm.h"
#include "../hisi_subdev.h"
#include "../hisi_cam_module.h"
#include "../sensor/hisi_sensor.h"


#define FILE_NAME_LEN	64

static struct hisi_vcm_t *vcm_array[CAMERA_VCM_MAX][CAMERA_VCM_ARRAY_SIZE];

DEFINE_HISI_VCM_CTRL(0);
DEFINE_HISI_VCM_CTRL(1);

int hisi_vcm_add(struct hisi_vcm_t *vcm)
{
	int i;

	for (i = 0; i < CAMERA_VCM_ARRAY_SIZE; i++) {
		if (NULL == vcm_array[vcm->vcm_info->index][i]) {
			vcm_array[vcm->vcm_info->index][i] = vcm;
			cam_notice("%s index=%d, i=%d, name=%s.\n", __func__,
				vcm->vcm_info->index, i, vcm->vcm_info->name);
			return 0;
		}
	}

	cam_err("%s: vcm_array[%d] is overflow!!!", __func__, vcm->vcm_info->index);
	return -EFAULT;
}
EXPORT_SYMBOL(hisi_vcm_add);

void hisi_vcm_del(struct hisi_vcm_t *vcm)
{
	int i;

	for (i = 0; i < CAMERA_VCM_ARRAY_SIZE; i++) {
		if (vcm == vcm_array[vcm->vcm_info->index][i]) {
			kfree(vcm_array[vcm->vcm_info->index][i]->vcm_info);
			vcm_array[vcm->vcm_info->index][i]->vcm_info = NULL;
			kfree(vcm_array[vcm->vcm_info->index][i]);
			vcm_array[vcm->vcm_info->index][i] = NULL;
			return;
		}
	}
}
EXPORT_SYMBOL(hisi_vcm_del);

int hisi_vcm_get_dt_data(struct platform_device *pdev,
	struct hisi_vcm_t *vcm)
{
	struct device_node *of_node = pdev->dev.of_node;
	struct hisi_vcm_info *vcm_info = NULL;
	int rc = 0;

	vcm_info = kzalloc(sizeof(struct hisi_vcm_info), GFP_KERNEL);
	if (!vcm_info) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return -ENOMEM;
	}
	vcm->vcm_info = vcm_info;

	rc = of_property_read_string(of_node, "hisi,vcm-name", &vcm_info->name);
	cam_info("%s hisi,vcm-name %s, rc %d\n", __func__, vcm_info->name, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,vcm-index",
		&vcm_info->index);
	cam_info("%s hisi,vcm-index %d, rc %d\n", __func__,
		vcm_info->index, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,slave-addr",
		&vcm_info->slave_address);
	cam_info("%s hisi,slave-addr 0x%x, rc %d\n", __func__,
		vcm_info->slave_address, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,data-type",
		&vcm_info->data_type);
	cam_info("%s hisi,data-type 0x%x, rc %d\n", __func__,
		vcm_info->data_type, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}
	return rc;
fail:
	cam_err("%s error exit.\n", __func__);
	kfree(vcm_info);
	vcm_info = NULL;
	return rc;
}
EXPORT_SYMBOL(hisi_vcm_get_dt_data);

static struct hisi_vcm_ctrl_t *get_sctrl(struct v4l2_subdev *sd)
{
	return container_of(container_of(sd, struct hisi_sd_subdev, sd),
		struct hisi_vcm_ctrl_t, hisi_sd);
}

static int hisi_vcm_get_sensor_vcm (
	struct hisi_vcm_ctrl_t *vcm_ctrl, char *sensor_vcm)
{
	struct hisi_sd_req_sd vcm_req_sd = {0};
	char sd_name[DEV_NAME_SIZE]={0};
	struct hisi_sensor_t *sensor;
	struct hisi_sensor_ctrl_t *s_ctrl;

	cam_debug("%s enter.\n", __func__);

	snprintf(sd_name, sizeof(sd_name), "hisi_sensor_%d", vcm_ctrl->index);
	vcm_req_sd.name = sd_name;
	v4l2_subdev_notify(&vcm_ctrl->hisi_sd.sd, HISI_SD_NOTIFY_GET_SD, &vcm_req_sd);

	s_ctrl = container_of(container_of(vcm_req_sd.subdev, struct hisi_sd_subdev, sd),
				struct hisi_sensor_ctrl_t, hisi_sd);
	if(!s_ctrl) {
		cam_err("%s fail to get s_ctrl", __func__);
		return -EFAULT;		
	}
	sensor = s_ctrl->sensor;

	if (NULL != sensor) {
		cam_info("%s sensor name=%s, sensor_index=%d.\n",__func__,
			sensor->sensor_info->name,
			sensor->sensor_info->sensor_index);
		if (sensor->sensor_info->vcm_enable) {
			strncpy(sensor_vcm, sensor->sensor_info->vcm_name,
			DEV_NAME_SIZE);
		}
	} else {
		cam_err("%s fail to get sensor, sensor maybe don't probe.\n", __func__);
		return -EFAULT;
	}

	return sensor->sensor_info->vcm_enable;
}

static int hisi_vcm_init(struct hisi_vcm_ctrl_t *vcm_ctrl )
{
	int i;
	int rc = 0;
	int vcm_enable = 0;
	char sensor_vcm[DEV_NAME_SIZE] = {0};

	cam_debug("%s enter.\n", __func__);

	vcm_enable = hisi_vcm_get_sensor_vcm(vcm_ctrl, sensor_vcm);
	if (vcm_enable < 0) {
		cam_err("%s fail to get sensor vcm.\n", __func__);
		return -EFAULT;
	}

	cam_info("%s vcm_enable=%d, sensor_vcm=%s.\n", __func__, vcm_enable, sensor_vcm);

	if (!vcm_enable) {
		cam_info("%s the sensor disable vcm.\n", __func__);
		return -EFAULT;
	}

	for (i = 0; i < CAMERA_VCM_ARRAY_SIZE; i++) {
		vcm_ctrl->vcm = vcm_ctrl->vcm_array[i];
		if (NULL != vcm_ctrl->vcm) {
			rc = strncmp(sensor_vcm, vcm_ctrl->vcm->vcm_info->name,
			sizeof(sensor_vcm));
			if(0 == rc) {
				cam_info("%s vcm is %s, index=%d.\n", __func__,
				vcm_ctrl->vcm->vcm_info->name,
				vcm_ctrl->vcm->vcm_info->index);
				return 0;
			}
		} else {
			break;
		}
	}

	cam_err("%s failed to match vcm name.", __func__);
	vcm_ctrl->vcm = NULL;
	return -EFAULT;
}

int hisi_vcm_config(struct hisi_vcm_ctrl_t *vcm_ctrl, void *arg)
{
	struct vcm_cfg_data *cdata = (struct vcm_cfg_data *)arg;
	long   rc = 0;

	cam_debug("%s enter cfgtype=%d.\n", __func__, cdata->cfgtype);

	mutex_lock(vcm_ctrl->hisi_vcm_mutex);

	switch (cdata->cfgtype) {
	case CFG_VCM_I2C_READ:
		rc = vcm_ctrl->vcm->func_tbl->vcm_i2c_read(vcm_ctrl, arg);
		break;
	case CFG_VCM_I2C_WRITE:
		rc = vcm_ctrl->vcm->func_tbl->vcm_i2c_write(vcm_ctrl, arg);
		break;
	case CFG_VCM_GET_VCM_NAME:
		strncpy(cdata->cfg.name, vcm_ctrl->vcm->vcm_info->name,
			sizeof(cdata->cfg.name) - 1);
		break;
	default:
		rc = vcm_ctrl->vcm->func_tbl->vcm_ioctl(vcm_ctrl, arg);
		break;
	}

	mutex_unlock(vcm_ctrl->hisi_vcm_mutex);

	return rc;
}
EXPORT_SYMBOL(hisi_vcm_config);

static long hisi_vcm_subdev_ioctl(struct v4l2_subdev *sd,
			unsigned int cmd, void *arg)
{
	struct hisi_vcm_ctrl_t *vcm_ctrl = get_sctrl(sd);
	int rc=0;

	if (!vcm_ctrl) {
		cam_err("%s vcm_ctrl is NULL\n", __func__);
		return -EBADF;
	}

	if (!vcm_ctrl->vcm) {
		rc = hisi_vcm_init(vcm_ctrl);
		if (rc < 0) {
			cam_err("%s vcm is NULL\n", __func__);
			return -EBADF;
		}
	}

	if (!vcm_ctrl->vcm || !vcm_ctrl->vcm->func_tbl) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		return -EBADF;
	}

	cam_debug("%s cmd = 0x%x\n", __func__, cmd);

	switch (cmd) {
	case VIDIOC_HISI_VCM_CFG:
		return vcm_ctrl->vcm->func_tbl->vcm_config(vcm_ctrl, arg);
	default:
		cam_err("%s cmd is error .", __func__);
		return -ENOIOCTLCMD;
	}
}

static struct v4l2_subdev_core_ops hisi_vcm_subdev_core_ops = {
	.ioctl = hisi_vcm_subdev_ioctl,
};

static struct v4l2_subdev_ops hisi_vcm_subdev_ops = {
	.core = &hisi_vcm_subdev_core_ops,
};

static int32_t hisi_vcm_platform_probe(struct platform_device *pdev,
	void *data)
{
	int32_t rc = 0;
	uint32_t group_id;
	struct hisi_vcm_ctrl_t *vcm_ctrl;
	const char *sd_name = NULL;

	vcm_ctrl = (struct hisi_vcm_ctrl_t *)data;

	vcm_ctrl->pdev = pdev;
	vcm_ctrl->dev = &pdev->dev;
	group_id = vcm_ctrl->index ? HISI_CAMERA_SUBDEV_VCM1
				: HISI_CAMERA_SUBDEV_VCM0;

	cam_debug("%s enter.\n", __func__);

	if (!vcm_ctrl->vcm_v4l2_subdev_ops)
		vcm_ctrl->vcm_v4l2_subdev_ops = &hisi_vcm_subdev_ops;

	v4l2_subdev_init(&vcm_ctrl->hisi_sd.sd,
			vcm_ctrl->vcm_v4l2_subdev_ops);

	rc = of_property_read_string(pdev->dev.of_node, "hisi,vcm-name",
		&sd_name);
	cam_info("%s name %s, rc %d\n", __func__, sd_name, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
	}

	snprintf(vcm_ctrl->hisi_sd.sd.name,
		sizeof(vcm_ctrl->hisi_sd.sd.name), "%s",
		sd_name);

	v4l2_set_subdevdata(&vcm_ctrl->hisi_sd.sd, pdev);
	vcm_ctrl->hisi_sd.sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	media_entity_init(&vcm_ctrl->hisi_sd.sd.entity, 0, NULL, 0);
	vcm_ctrl->hisi_sd.sd.entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
	vcm_ctrl->hisi_sd.sd.entity.group_id = group_id;
	vcm_ctrl->hisi_sd.sd.entity.name = vcm_ctrl->hisi_sd.sd.name;
	hisi_sd_register(&vcm_ctrl->hisi_sd);

	return rc;
}

static const struct of_device_id hisi_vcm_dt_match[] = {
	{.compatible = "hisi,hisi_vcm_0", .data = &hisi_vcm_ctrl_0},
	{.compatible = "hisi,hisi_vcm_1", .data = &hisi_vcm_ctrl_1},
	{}
};
MODULE_DEVICE_TABLE(of, hisi_vcm_dt_match);
static struct platform_driver vcm_platform_driver = {
	.driver = {
		.name = "hisi_vcm",
		.owner = THIS_MODULE,
		.of_match_table = hisi_vcm_dt_match,
	},
};

static int32_t vcm_platform_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	match = of_match_device(hisi_vcm_dt_match, &pdev->dev);
	if(!match) {
		cam_err("vcm match device failed");
		return -1;
	}	
	cam_info("%s compatible=%s.\n", __func__, match->compatible);
	return hisi_vcm_platform_probe(pdev, (void*)match->data);
}

static int __init vcm_init_module(void)
{
	int rc = 0;
	cam_debug("%s:%d\n", __func__, __LINE__);

	rc = platform_driver_probe(&vcm_platform_driver,
		vcm_platform_probe);
	if (rc < 0) {
		cam_err("%s platform_driver_probe error.\n", __func__);
	}
	return rc;
}

static void __exit vcm_exit_module(void)
{
	platform_driver_unregister(&vcm_platform_driver);
}

module_init(vcm_init_module);
module_exit(vcm_exit_module);
MODULE_DESCRIPTION("hisi_vcm");
MODULE_LICENSE("GPL v2");
