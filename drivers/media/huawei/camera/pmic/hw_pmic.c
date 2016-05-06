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

#include "hwcam_intf.h"
#include "cam_log.h"
#include "hw_pmic.h"
#include "hw_pmic_i2c.h"
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif

struct hisi_pmic_ctrl_t *hisi_pmic_ctrl = NULL;

void hisi_set_pmic_ctrl(struct hisi_pmic_ctrl_t *pmic_ctrl)
{
	hisi_pmic_ctrl = pmic_ctrl;
}

struct hisi_pmic_ctrl_t * hisi_get_pmic_ctrl(void)
{
	return hisi_pmic_ctrl;
}

int hisi_pmic_get_dt_data(struct hisi_pmic_ctrl_t *pmic_ctrl)
{
	struct device_node *of_node;
	struct hisi_pmic_info *pmic_info;
	int rc = -1;

	cam_info("%s enter.\n", __func__);

	if (NULL == pmic_ctrl) {
		cam_err("%s pmic_ctrl is NULL.", __func__);
		return rc;
	}

	of_node = pmic_ctrl->dev->of_node;

	pmic_info = &pmic_ctrl->pmic_info;

	rc = of_property_read_string(of_node, "hisi,pmic_name", &pmic_info->name);
	cam_info("%s hisi,pmic_name %s, rc %d\n", __func__, pmic_info->name, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,pmic_index",
		&pmic_info->index);
	cam_info("%s hisi,pmic_index %d, rc %d\n", __func__,
		pmic_info->index, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,slave_address",
		&pmic_info->slave_address);
	cam_info("%s slave_address %d, rc %d\n", __func__,
		pmic_info->slave_address, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}
fail:
	return rc;
}

static struct hisi_pmic_ctrl_t *get_sctrl(struct v4l2_subdev *sd)
{
	return container_of(sd, struct hisi_pmic_ctrl_t, subdev);
}

int hisi_pmic_config(struct hisi_pmic_ctrl_t *pmic_ctrl, void *argp)
{
	/*
	struct pmic_cfg_data *cdata = (struct pmic_cfg_data *)argp;
	*/
	int rc = 0;
	//unsigned int state;
	/*
	cam_info("%s enter cfgtype=%d.\n", __func__, cdata->cfgtype);
	*/
	//mutex_lock(flash_ctrl->hisi_flash_mutex);

	/*
	switch (cdata->cfgtype) {
	case CFG_FLASH_TURN_ON:
		state = hisi_flash_get_state();
		if (0 == state) {
			rc = flash_ctrl->func_tbl->flash_on(flash_ctrl, arg);
		} else {
			cam_notice("%s flashe led is disable(0x%x).", __func__, state);
			rc = -1;
		}
		break;
	case CFG_FLASH_TURN_OFF:
		rc = flash_ctrl->func_tbl->flash_off(flash_ctrl);
		break;
	case CFG_FLASH_GET_FLASH_NAME:
		mutex_lock(flash_ctrl->hisi_flash_mutex);
		strncpy(cdata->cfg.name, flash_ctrl->flash_info.name,
			sizeof(cdata->cfg.name) - 1);
		mutex_unlock(flash_ctrl->hisi_flash_mutex);
		break;
	case CFG_FLASH_GET_FLASH_STATE:
		mutex_lock(flash_ctrl->hisi_flash_mutex);
		cdata->mode = flash_ctrl->state.mode;
		cdata->data = flash_ctrl->state.data;
		mutex_unlock(flash_ctrl->hisi_flash_mutex);
		break;
	default:
		cam_err("%s cfgtype error.\n", __func__);
		rc = -EFAULT;
		break;
	}
	*/

	//mutex_unlock(flash_ctrl->hisi_flash_mutex);

	return rc;
}

EXPORT_SYMBOL(hisi_pmic_config);

static long hisi_pmic_subdev_ioctl(struct v4l2_subdev *sd,
			unsigned int cmd, void *arg)
{
	struct hisi_pmic_ctrl_t *pmic_ctrl = get_sctrl(sd);
	//long rc = 0;

	if (!pmic_ctrl) {
		cam_err("%s pmic_ctrl is NULL\n", __func__);
		return -EBADF;
	}

	cam_info("%s cmd = 0x%x\n", __func__, cmd);

	switch (cmd) {
	case 0:
		return pmic_ctrl->func_tbl->pmic_config(pmic_ctrl, arg);
	default:
		cam_err("%s cmd is error .", __func__);
		return -ENOIOCTLCMD;
	}
}

static struct v4l2_subdev_core_ops hisi_pmic_subdev_core_ops = {
	.ioctl = hisi_pmic_subdev_ioctl,
};

static struct v4l2_subdev_ops hisi_pmic_subdev_ops = {
	.core = &hisi_pmic_subdev_core_ops,
};

int32_t hisi_pmic_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter;
	struct hisi_pmic_ctrl_t *pmic_ctrl;
	int32_t rc=0;

	cam_info("%s client name = %s.\n", __func__, client->name);

	adapter = client->adapter;
	if (!i2c_check_functionality(adapter, I2C_FUNC_I2C)) {
		cam_err("%s i2c_check_functionality failed.\n", __func__);
		return -EIO;
	}

	pmic_ctrl = (struct hisi_pmic_ctrl_t *)id->driver_data;
	pmic_ctrl->pmic_i2c_client->client = client;/*[false alarm]:pmic_ctrl is not alarm*/
	pmic_ctrl->dev = &client->dev;
	pmic_ctrl->pmic_i2c_client->i2c_func_tbl = &hisi_pmic_i2c_func_tbl;

	rc = hisi_pmic_get_dt_data(pmic_ctrl);
	if (rc < 0) {
		cam_err("%s hisi_pmic_get_dt_data failed.", __func__);
		return -EFAULT;
	}

	rc = pmic_ctrl->func_tbl->pmic_get_dt_data(pmic_ctrl);
	if (rc < 0) {
		cam_err("%s flash_get_dt_data failed.", __func__);
		return -EFAULT;
	}

	rc = pmic_ctrl->func_tbl->pmic_init(pmic_ctrl);
	if (rc < 0) {
		cam_err("%s pmic init failed.\n", __func__);
		return -EFAULT;
	}

	rc = pmic_ctrl->func_tbl->pmic_match(pmic_ctrl);
	if (rc < 0) {
		cam_err("%s pmic match failed.\n", __func__);
		return -EFAULT;
	}

	if (!pmic_ctrl->pmic_v4l2_subdev_ops)
		pmic_ctrl->pmic_v4l2_subdev_ops = &hisi_pmic_subdev_ops;

	v4l2_subdev_init(&pmic_ctrl->subdev,
			pmic_ctrl->pmic_v4l2_subdev_ops);

	snprintf(pmic_ctrl->subdev.name,
		sizeof(pmic_ctrl->subdev.name), "%s",
		pmic_ctrl->pmic_info.name);

	v4l2_set_subdevdata(&pmic_ctrl->subdev, client);

	pmic_ctrl->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	media_entity_init(&pmic_ctrl->subdev.entity, 0, NULL, 0);
	pmic_ctrl->subdev.entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
	pmic_ctrl->subdev.entity.group_id = HWCAM_SUBDEV_PMIC;
	pmic_ctrl->subdev.entity.name = pmic_ctrl->subdev.name;
	hwcam_cfgdev_register_subdev(&pmic_ctrl->subdev);
	rc = pmic_ctrl->func_tbl->pmic_register_attribute(pmic_ctrl,
			&pmic_ctrl->subdev.devnode->dev);
	if (rc < 0) {
		cam_err("%s failed to register pmic attribute node.", __func__);
		return rc;
	}

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
	/* detect current device successful, set the flag as present */
	//set_hw_dev_flag(DEV_I2C_CAMERA_PMU);
#endif
	hisi_set_pmic_ctrl(pmic_ctrl);
	return rc;
}
