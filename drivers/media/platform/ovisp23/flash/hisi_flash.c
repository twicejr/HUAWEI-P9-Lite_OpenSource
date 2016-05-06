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

#include "../hisi_subdev.h"
#include "../hisi_cam_module.h"
#include "hisi_flash.h"
#include "hisi_flash_i2c.h"
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif


static unsigned int flash_led_state = 0;


unsigned int hisi_flash_get_state(void)
{
	return (flash_led_state & (FLASH_LED_THERMAL_PROTECT_ENABLE
		| FLASH_LED_LOWPOWER_PROTECT_ENABLE));
}

void hisi_flash_set_state(unsigned int state)
{
	flash_led_state |= state;
}

void hisi_flash_clear_state(unsigned int state)
{
	flash_led_state &= (~state);
}

void hisi_flash_enable_thermal_protect(void)
{
	cam_info("%s enter.", __func__);
	hisi_flash_set_state(FLASH_LED_THERMAL_PROTECT_ENABLE);
}

void hisi_flash_disable_thermal_protect(void)
{
	cam_info("%s enter.", __func__);
	hisi_flash_clear_state(FLASH_LED_THERMAL_PROTECT_ENABLE);
}

static ssize_t hisi_flash_thermal_protect_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
	int rc=0;
	unsigned int state = hisi_flash_get_state();

	snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "%d", state);
	rc = strlen(buf)+1;
	return rc;
}

static ssize_t hisi_flash_thermal_protect_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	if ('0' == buf[0]) {
		cam_notice("%s disable thermal protect.", __func__);
		hisi_flash_clear_state(FLASH_LED_THERMAL_PROTECT_ENABLE);
	} else {
		cam_notice("%s enable thermal protect.", __func__);
		hisi_flash_set_state(FLASH_LED_THERMAL_PROTECT_ENABLE);
	}

	return count;
}

static ssize_t hisi_flash_lowpower_protect_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
	int rc=0;
	unsigned int state = hisi_flash_get_state();

	snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "%d", state);
	rc = strlen(buf)+1;
	return rc;
}

static ssize_t hisi_flash_lowpower_protect_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	if ('0' == buf[0]) {
		cam_notice("%s disable lowpower protect.", __func__);
		hisi_flash_clear_state(FLASH_LED_LOWPOWER_PROTECT_ENABLE);
	} else {
		cam_notice("%s enable lowpower protect.", __func__);
		hisi_flash_set_state(FLASH_LED_LOWPOWER_PROTECT_ENABLE);
	}

	return count;
}

static struct device_attribute hisi_flash_lowpower_protect =
    __ATTR(flash_lowpower_protect, 0664, hisi_flash_lowpower_protect_show, hisi_flash_lowpower_protect_store);

static struct device_attribute hisi_flash_thermal_protect =
    __ATTR(flash_thermal_protect, 0664, hisi_flash_thermal_protect_show, hisi_flash_thermal_protect_store);

static int hisi_flash_register_attribute(struct hisi_flash_ctrl_t *flash_ctrl, struct device *dev)
{
	int rc = 0;

	if ((NULL == flash_ctrl) || (NULL == dev)) {
		cam_err("%s flash_ctrl or dev is NULL.", __func__);
		return -1;
	}

	rc = device_create_file(dev, &hisi_flash_lowpower_protect);
	if (rc < 0) {
		cam_err("%s failed to creat flash lowpower protect attribute.", __func__);
		return rc;
	}

	rc = device_create_file(flash_ctrl->cdev_torch.dev, &hisi_flash_thermal_protect);
	if (rc < 0) {
		cam_err("%s failed to creat flash lowpower protect attribute.", __func__);
		return rc;
	}

	return 0;
}

int hisi_flash_get_dt_data(struct hisi_flash_ctrl_t *flash_ctrl)
{
	struct device_node *of_node;
	struct hisi_flash_info *flash_info;
	int rc = -1;

	cam_debug("%s enter.\n", __func__);

	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return rc;
	}

	of_node = flash_ctrl->dev->of_node;

	flash_info = &flash_ctrl->flash_info;

	rc = of_property_read_string(of_node, "hisi,flash-name", &flash_info->name);
	cam_info("%s hisi,flash-name %s, rc %d\n", __func__, flash_info->name, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,flash-index",
		&flash_info->index);
	cam_info("%s hisi,flash-index %d, rc %d\n", __func__,
		flash_info->index, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,flash-type",
		&flash_info->type);
	cam_info("%s hisi,flash-type %d, rc %d\n", __func__,
		flash_info->type, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,slave-address",
		&flash_info->slave_address);
	cam_info("%s slave-address %d, rc %d\n", __func__,
		flash_info->slave_address, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

fail:
	return rc;
}

static struct hisi_flash_ctrl_t *get_sctrl(struct v4l2_subdev *sd)
{
	return container_of(container_of(sd, struct hisi_sd_subdev, sd),
		struct hisi_flash_ctrl_t, hisi_sd);
}

int hisi_flash_config(struct hisi_flash_ctrl_t *flash_ctrl, void *arg)
{
	struct flash_cfg_data *cdata = (struct flash_cfg_data *)arg;
	int rc = 0;
	unsigned int state;

	cam_info("%s enter cfgtype=%d.\n", __func__, cdata->cfgtype);

	//mutex_lock(flash_ctrl->hisi_flash_mutex);

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

	//mutex_unlock(flash_ctrl->hisi_flash_mutex);

	return rc;
}
EXPORT_SYMBOL(hisi_flash_config);

static long hisi_flash_subdev_ioctl(struct v4l2_subdev *sd,
			unsigned int cmd, void *arg)
{
	struct hisi_flash_ctrl_t *flash_ctrl = get_sctrl(sd);
	//long rc = 0;

	if (!flash_ctrl) {
		cam_err("%s flash_ctrl is NULL\n", __func__);
		return -EBADF;
	}

	cam_info("%s cmd = 0x%x\n", __func__, cmd);

	switch (cmd) {
	case VIDIOC_HISI_FLASH_CFG:
		return flash_ctrl->func_tbl->flash_config(flash_ctrl, arg);
	default:
		cam_err("%s cmd is error .", __func__);
		return -ENOIOCTLCMD;
	}
}

static struct v4l2_subdev_core_ops hisi_flash_subdev_core_ops = {
	.ioctl = hisi_flash_subdev_ioctl,
};

static struct v4l2_subdev_ops hisi_flash_subdev_ops = {
	.core = &hisi_flash_subdev_core_ops,
};

int32_t hisi_flash_platform_probe(struct platform_device *pdev,
	void *data)
{
	int32_t rc = 0;
	uint32_t group_id;
	struct hisi_flash_ctrl_t *flash_ctrl;

	flash_ctrl = (struct hisi_flash_ctrl_t *)data;

	flash_ctrl->pdev = pdev;
	flash_ctrl->dev = &pdev->dev;

	cam_debug("%s enter.\n", __func__);

	hisi_flash_get_dt_data(flash_ctrl);
	rc = flash_ctrl->func_tbl->flash_get_dt_data(flash_ctrl);
	if (rc < 0) {
		cam_err("%s flash_get_dt_data failed.", __func__);
		return -EFAULT;
	}

	rc = flash_ctrl->func_tbl->flash_init(flash_ctrl);
	if (rc < 0) {
		cam_err("%s flash init failed.\n", __func__);
		return -EFAULT;
	}

	rc = flash_ctrl->func_tbl->flash_match(flash_ctrl);
	if (rc < 0) {
		cam_err("%s flash match failed.\n", __func__);
		return -EFAULT;
	}

	if (!flash_ctrl->flash_v4l2_subdev_ops)
		flash_ctrl->flash_v4l2_subdev_ops = &hisi_flash_subdev_ops;

	v4l2_subdev_init(&flash_ctrl->hisi_sd.sd,
			flash_ctrl->flash_v4l2_subdev_ops);

	snprintf(flash_ctrl->hisi_sd.sd.name,
		sizeof(flash_ctrl->hisi_sd.sd.name), "%s",
		flash_ctrl->flash_info.name);

	v4l2_set_subdevdata(&flash_ctrl->hisi_sd.sd, pdev);

	group_id = flash_ctrl->flash_info.index ? HISI_CAMERA_SUBDEV_FLASH1
				: HISI_CAMERA_SUBDEV_FLASH0;

	flash_ctrl->hisi_sd.sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	media_entity_init(&flash_ctrl->hisi_sd.sd.entity, 0, NULL, 0);
	flash_ctrl->hisi_sd.sd.entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
	flash_ctrl->hisi_sd.sd.entity.group_id = group_id;
	flash_ctrl->hisi_sd.sd.entity.name = flash_ctrl->hisi_sd.sd.name;
	hisi_sd_register(&flash_ctrl->hisi_sd);

	rc = flash_ctrl->func_tbl->flash_register_attribute(flash_ctrl,
			&flash_ctrl->hisi_sd.sd.devnode->dev);
	if (rc < 0) {
		cam_err("%s failed to register flash attribute node.", __func__);
		return rc;
	}

	rc = hisi_flash_register_attribute(flash_ctrl,
			&flash_ctrl->hisi_sd.sd.devnode->dev);
	if (rc < 0) {
		cam_err("%s failed to register hisi flash attribute node.", __func__);
		return rc;
	}
	return rc;
}

int32_t hisi_flash_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter;
	struct hisi_flash_ctrl_t *flash_ctrl;
	//char *flash_name = NULL;
	uint32_t group_id;
	int32_t rc=0;

	cam_debug("%s enter.\n", __func__);

	cam_info("%s client name = %s.\n", __func__, client->name);

	adapter = client->adapter;
	if (!i2c_check_functionality(adapter, I2C_FUNC_I2C)) {
		cam_err("%s i2c_check_functionality failed.\n", __func__);
		return -EIO;
	}

	flash_ctrl = (struct hisi_flash_ctrl_t *)id->driver_data;
	flash_ctrl->flash_i2c_client->client = client;
	flash_ctrl->dev = &client->dev;
	flash_ctrl->flash_i2c_client->i2c_func_tbl = &hisi_flash_i2c_func_tbl;

	rc = hisi_flash_get_dt_data(flash_ctrl);
	if (rc < 0) {
		cam_err("%s hisi_flash_get_dt_data failed.", __func__);
		return -EFAULT;
	}

	rc = flash_ctrl->func_tbl->flash_get_dt_data(flash_ctrl);
	if (rc < 0) {
		cam_err("%s flash_get_dt_data failed.", __func__);
		return -EFAULT;
	}

	rc = flash_ctrl->func_tbl->flash_init(flash_ctrl);
	if (rc < 0) {
		cam_err("%s flash init failed.\n", __func__);
		return -EFAULT;
	}

	rc = flash_ctrl->func_tbl->flash_match(flash_ctrl);
	if (rc < 0) {
		cam_err("%s flash match failed.\n", __func__);
		flash_ctrl->func_tbl->flash_exit(flash_ctrl);
		return -EFAULT;
	}

	if (!flash_ctrl->flash_v4l2_subdev_ops)
		flash_ctrl->flash_v4l2_subdev_ops = &hisi_flash_subdev_ops;

	v4l2_subdev_init(&flash_ctrl->hisi_sd.sd,
			flash_ctrl->flash_v4l2_subdev_ops);

	snprintf(flash_ctrl->hisi_sd.sd.name,
		sizeof(flash_ctrl->hisi_sd.sd.name), "%s",
		flash_ctrl->flash_info.name);

	v4l2_set_subdevdata(&flash_ctrl->hisi_sd.sd, client);

	group_id = flash_ctrl->flash_info.index ? HISI_CAMERA_SUBDEV_FLASH1
					: HISI_CAMERA_SUBDEV_FLASH0;

	flash_ctrl->hisi_sd.sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	media_entity_init(&flash_ctrl->hisi_sd.sd.entity, 0, NULL, 0);
	flash_ctrl->hisi_sd.sd.entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
	flash_ctrl->hisi_sd.sd.entity.group_id = group_id;
	flash_ctrl->hisi_sd.sd.entity.name = flash_ctrl->hisi_sd.sd.name;
	hisi_sd_register(&flash_ctrl->hisi_sd);
	rc = flash_ctrl->func_tbl->flash_register_attribute(flash_ctrl,
			&flash_ctrl->hisi_sd.sd.devnode->dev);
	if (rc < 0) {
		cam_err("%s failed to register flash attribute node.", __func__);
		return rc;
	}

	rc = hisi_flash_register_attribute(flash_ctrl,
			&flash_ctrl->hisi_sd.sd.devnode->dev);
	if (rc < 0) {
		cam_err("%s failed to register hisi flash attribute node.", __func__);
		return rc;
	}
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
	/* detect current device successful, set the flag as present */
	set_hw_dev_flag(DEV_I2C_TPS);
#endif
	return rc;
}
