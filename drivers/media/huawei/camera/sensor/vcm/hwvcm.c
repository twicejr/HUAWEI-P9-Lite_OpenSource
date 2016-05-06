/*
 *  Hisilicon K3 SOC camera driver source file
 *
 *  Copyright (C) Huawei Technology Co., Ltd.
 *
 * Author:
 * Email:
 * Date:	  2014-11-15
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


#include <linux/compiler.h>
#include <linux/gpio.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <media/huawei/camera.h>
#include <media/v4l2-subdev.h>
#include "hwvcm.h"

#define SD2Vcm(sd) container_of(sd, hw_vcm_t, subdev)

int hw_vcm_get_dt_data(struct platform_device *pdev, vcm_t *vcm)
{
	struct device_node *of_node = pdev->dev.of_node;
	struct hw_vcm_info *vcm_info = NULL;
	int rc = 0;

	vcm_info = kzalloc(sizeof(struct hw_vcm_info), GFP_KERNEL);
	if (!vcm_info) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return -ENOMEM;
	}
	vcm->vcm_info = vcm_info;

	rc = of_property_read_string(of_node, "hisi,vcm-name", &vcm_info->vcm_name);
	cam_info("%s hisi,vcm-name %s, rc %d\n", __func__, vcm_info->vcm_name, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,vcm-index", &vcm_info->index);
	cam_info("%s hisi,vcm-index %d, rc %d\n", __func__, vcm_info->index, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,slave-addr", &vcm_info->slave_address);
	cam_info("%s hisi,slave-addr 0x%x, rc %d\n", __func__, vcm_info->slave_address, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "hisi,data-type", &vcm_info->data_type);
	cam_info("%s hisi,data-type 0x%x, rc %d\n", __func__, vcm_info->data_type, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}
	return rc;
fail:
	cam_err("%s can not read vcm info exit.\n", __func__);
	kfree(vcm_info);
	vcm_info = NULL;
	return rc;
}

int hw_vcm_config(hw_vcm_t *hw_vcm, void *arg)
{
	int rc = 0;
	struct hw_vcm_cfg_data *cdata = (struct hw_vcm_cfg_data *)arg;

	if (NULL == cdata) {
		cam_debug("%s, arg is NULL.\n", __func__);
		return -EINVAL;	
	}

	cam_debug("%s enter cfgtype=%d.\n", __func__, cdata->cfgtype);

	mutex_lock(&hw_vcm->lock);

	switch (cdata->cfgtype) {
	case CFG_VCM_I2C_READ:
		rc = hw_vcm->intf->vtbl->vcm_i2c_read(hw_vcm->intf, arg);
		break;
	case CFG_VCM_I2C_WRITE:
		rc = hw_vcm->intf->vtbl->vcm_i2c_write(hw_vcm->intf, arg);
		break;
	case CFG_VCM_GET_VCM_NAME:
		strncpy(cdata->cfg.name, hw_vcm->vcm_info->vcm_name,
			sizeof(cdata->cfg.name) - 1);
		break;
	default:
		rc = hw_vcm->intf->vtbl->vcm_ioctl(hw_vcm->intf, arg);
		break;
	}

	mutex_unlock(&hw_vcm->lock);

	return rc;
}

static long
hw_vcm_subdev_ioctl(
		struct v4l2_subdev *sd,
		unsigned int cmd,
		void *arg)
{
	long rc = -EINVAL;
	hw_vcm_t* s = NULL;

	if (arg == NULL) {
		cam_err("%s, the parameters is a null pointer!", __func__);
	}

	s = SD2Vcm(sd);
	cam_debug("hw vcm cmd = %x",cmd);

	switch (cmd)
	{
	case VIDIOC_HISI_VCM_CFG:
		rc = s->intf->vtbl->vcm_config(s, arg);
		break;
	default:
		cam_err("%s, invalid IOCTL CMD(%d)! \n", __func__, cmd);
		break;
	}
	return rc;
}

static int hw_vcm_subdev_open(
		struct v4l2_subdev *sd,
		struct v4l2_subdev_fh *fh)
{
	cam_notice("hw_vcm_sbudev open! \n");
	return 0;
}

static int
hw_vcm_subdev_close(
		struct v4l2_subdev *sd,
		struct v4l2_subdev_fh *fh)
{
	cam_notice("hw_vcm_sbudev close! \n");
	return 0;
}

static struct v4l2_subdev_internal_ops
s_subdev_internal_ops_hw_vcm =
{
	.open = hw_vcm_subdev_open,
	.close = hw_vcm_subdev_close,
};

static struct v4l2_subdev_core_ops
s_subdev_core_ops_hw_vcm =
{
	.ioctl = hw_vcm_subdev_ioctl,
};

static struct v4l2_subdev_ops
s_subdev_ops_hw_vcm =
{
	.core = &s_subdev_core_ops_hw_vcm,
};

int hw_vcm_register(struct platform_device *pdev,
		hw_vcm_intf_t* intf, struct hw_vcm_info *hw_vcm_info)
{
	int rc = 0;
	hw_vcm_t *hw_vcm = NULL;
	struct v4l2_subdev *subdev = NULL;

	if (intf == NULL || pdev == NULL || hw_vcm_info == NULL) {
		rc = -ENOMEM;
		cam_err("%s, the parameters is a null pointer!", __func__);
		goto register_fail;
	}

	hw_vcm = (hw_vcm_t*)kzalloc(sizeof(hw_vcm_t), GFP_KERNEL);
	if (hw_vcm == NULL) {
		rc = -ENOMEM;
		cam_err("%s, vcm is null!!", __func__);
		goto register_fail;
	}

	subdev = &hw_vcm->subdev;
	mutex_init(&hw_vcm->lock);

	v4l2_subdev_init(subdev, &s_subdev_ops_hw_vcm);
	subdev->internal_ops = &s_subdev_internal_ops_hw_vcm;
	snprintf(subdev->name, sizeof(subdev->name),
			"%s", hw_vcm_info->vcm_name);
	subdev->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	v4l2_set_subdevdata(subdev, pdev);

	media_entity_init(&subdev->entity, 0, NULL, 0);
	subdev->entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
	subdev->entity.group_id = hw_vcm_info->index ? HWCAM_SUBDEV_VCM1
			: HWCAM_SUBDEV_VCM0;
	subdev->entity.name = subdev->name;

	hwcam_cfgdev_register_subdev(subdev);
	hw_vcm->intf = intf;
	hw_vcm->vcm_info = hw_vcm_info;
	hw_vcm->pdev = pdev;

register_fail:
	return rc;
}

#define Intf2Hwvcm(si) container_of(si, hw_vcm_t, intf)
extern void hw_vcm_unregister(hw_vcm_intf_t *intf)
{
	struct v4l2_subdev* subdev = NULL;
	hw_vcm_t* hw_vcm = Intf2Hwvcm(intf);

	subdev = &hw_vcm->subdev;
	media_entity_cleanup(&subdev->entity);
	hwcam_cfgdev_unregister_subdev(subdev);

	kzfree(hw_vcm->vcm_info);
	kzfree(hw_vcm);
}
