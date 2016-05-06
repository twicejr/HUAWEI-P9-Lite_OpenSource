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


#include "hisi_isp.h"
#include "../hisi_subdev.h"
#include "../hisi_cam_module.h"
#include "../camera/hisi_camera.h"
#include "isp_driver.h"

DEFINE_HISI_MUTEX(isp_mut);
struct hisi_isp_ctrl_t hisi_s_ctrl = {
	.hisi_isp_mutex = &isp_mut,

};

static struct hisi_isp_ctrl_t *get_sctrl(struct v4l2_subdev *sd)
{
	return container_of(container_of(sd, struct hisi_sd_subdev, sd),
		struct hisi_isp_ctrl_t, hisi_sd);
}

static long hisi_isp_subdev_ioctl(struct v4l2_subdev *sd,
			unsigned int cmd, void *arg)
{
	struct hisi_isp_ctrl_t *isp_ctrl = get_sctrl(sd);

	if (!isp_ctrl) {
		cam_err("%s isp_ctrl NULL\n", __func__);
		return -EBADF;
	}

	switch (cmd) {
	case VIDIOC_HISI_ISP_CFG:
		return isp_ctrl->func_tbl->isp_config(isp_ctrl, arg);
	default:
		cam_err("%s cmd error.\n", __func__);
		return -ENOIOCTLCMD;
	}
}

static struct v4l2_subdev_core_ops hisi_isp_subdev_core_ops = {
	.ioctl = hisi_isp_subdev_ioctl,
};

static struct v4l2_subdev_ops hisi_isp_subdev_ops = {
	.core = &hisi_isp_subdev_core_ops,
};

static int hisi_isp_platform_probe(struct platform_device *pdev, void *data)
{
	int rc = 0;
	struct hisi_isp_ctrl_t *isp_ctrl = (struct hisi_isp_ctrl_t *)data;
	const char *sd_name=NULL;

	isp_ctrl->pdev = pdev;
	//isp_ctrl->dev = &pdev->dev;

	cam_debug("%s enter\n", __func__);

	if (!isp_ctrl->func_tbl)
		isp_ctrl->func_tbl = &hisi_isp_func_tbl;

	if (!isp_ctrl->isp_v4l2_subdev_ops)
		isp_ctrl->isp_v4l2_subdev_ops = &hisi_isp_subdev_ops;

	v4l2_subdev_init(&isp_ctrl->hisi_sd.sd,
			isp_ctrl->isp_v4l2_subdev_ops);

	rc = of_property_read_string(pdev->dev.of_node, "hisi,isp-name",
		&sd_name);
	cam_info("%s name %s, rc %d\n", __func__, sd_name, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	snprintf(isp_ctrl->hisi_sd.sd.name,
		sizeof(isp_ctrl->hisi_sd.sd.name), "%s",
		sd_name);

	v4l2_set_subdevdata(&isp_ctrl->hisi_sd.sd, pdev);
	isp_ctrl->hisi_sd.sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	media_entity_init(&isp_ctrl->hisi_sd.sd.entity, 0, NULL, 0);
	isp_ctrl->hisi_sd.sd.entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
	isp_ctrl->hisi_sd.sd.entity.group_id = HISI_CAMERA_SUBDEV_ISP;
	isp_ctrl->hisi_sd.sd.entity.name = isp_ctrl->hisi_sd.sd.name;

	rc = camera_init_v4l2(isp_ctrl->pdev);
	if (rc < 0) {
		cam_err("%s: camera init v4l2 error rc=%d.\n", __func__, rc);
		return rc;
	}

	rc = hisi_sd_register(&isp_ctrl->hisi_sd);
	if (rc < 0) {
		cam_err("%s: hisi_sd_register error rc=%d.\n", __func__, rc);
		return rc;
	}

	return rc;
}

static const struct of_device_id hisi_isp_dt_match[] = {
	{.compatible = "hisi,hisi_isp", .data = &hisi_s_ctrl},
	{}
};
MODULE_DEVICE_TABLE(of, hisi_isp_dt_match);
static struct platform_driver isp_platform_driver = {
	.driver = {
		.name = "hisi_isp",
		.owner = THIS_MODULE,
		.of_match_table = hisi_isp_dt_match,
	},
};

static int32_t isp_platform_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	match = of_match_device(hisi_isp_dt_match, &pdev->dev);
	if(!match) {
		cam_err("isp match device failed");
		return -1;
	}
	cam_notice("%s compatible=%s.\n", __func__, match->compatible);
	return hisi_isp_platform_probe(pdev, (void*)match->data);
}

static int __init isp_module_init(void)
{
	int rc = 0;
	cam_debug("%s:%d\n", __func__, __LINE__);

	rc = platform_driver_probe(&isp_platform_driver,
		isp_platform_probe);
	if (rc < 0) {
		cam_err("%s platform_driver_probe error.\n", __func__);
	}
	return rc;
}

static void __exit isp_module_exit(void)
{
	platform_driver_unregister(&isp_platform_driver);
}

module_init(isp_module_init);
module_exit(isp_module_exit);
MODULE_DESCRIPTION("hisi_isp");
MODULE_LICENSE("GPL v2");
