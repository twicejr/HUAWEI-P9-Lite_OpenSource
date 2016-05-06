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

#include <linux/fb.h>
#include <linux/of.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ioctl.h>
#include <linux/spinlock.h>
#include <linux/proc_fs.h>
#include <linux/atomic.h>
#include <linux/wait.h>
#include <linux/videodev2.h>
#include <linux/iommu.h>
#include <linux/platform_device.h>
#include <media/v4l2-fh.h>
#include "hisi_cam_module.h"
#include "hisi_subdev.h"

static struct v4l2_device *hisi_v4l2_dev;
static int is_fpga = 0; //default is no fpga

static void hisi_sd_unregister_subdev(struct video_device *vdev)
{
	struct v4l2_subdev *sd = video_get_drvdata(vdev);
	kfree(sd->devnode);
	sd->devnode = NULL;
}

static inline int __hisi_sd_register_subdev(struct v4l2_subdev *sd)
{
	int rc = 0;
	struct video_device *vdev;

	if (!hisi_v4l2_dev || !sd || !sd->name[0]) {
		return -EINVAL;
	}

	rc = v4l2_device_register_subdev(hisi_v4l2_dev, sd);
	if (rc < 0) {
		return rc;
	}

	/* Register a device node for every subdev marked with the
	 * V4L2_SUBDEV_FL_HAS_DEVNODE flag.
	 */
	if (!(sd->flags & V4L2_SUBDEV_FL_HAS_DEVNODE))
		return rc;

	vdev = kzalloc(sizeof(*vdev), GFP_KERNEL);
	if (!vdev) {
		rc = -ENOMEM;
		goto fail;
	}

	video_set_drvdata(vdev, sd);
	strlcpy(vdev->name, sd->name, sizeof(vdev->name));
	vdev->v4l2_dev = hisi_v4l2_dev;
	vdev->fops = &v4l2_subdev_fops;
	vdev->release = hisi_sd_unregister_subdev;
	rc = __video_register_device(vdev, VFL_TYPE_SUBDEV, -1, 1,
		  sd->owner);
	if (rc < 0) {
		kfree(vdev);
		vdev = NULL;
		goto fail;
	}

#if defined(CONFIG_MEDIA_CONTROLLER)
	sd->entity.info.v4l.major = VIDEO_MAJOR;
	sd->entity.info.v4l.minor = vdev->minor;
	sd->entity.name = video_device_node_name(vdev);
#endif
	sd->devnode = vdev;
	return 0;

fail:
	video_unregister_device(sd->devnode);

	return rc;
}

int hisi_sd_register(struct hisi_sd_subdev *hisi_subdev)
{
	if (!hisi_subdev)
		return -EINVAL;

	if (!hisi_v4l2_dev && !hisi_v4l2_dev->dev)
		return -EIO;

	return __hisi_sd_register_subdev(&hisi_subdev->sd);
}
EXPORT_SYMBOL(hisi_sd_register);

int hisi_sd_unregister(struct hisi_sd_subdev *hisi_subdev)
{
	if (!hisi_subdev)
		return -EINVAL;

	v4l2_device_unregister_subdev(&hisi_subdev->sd);
	return 0;
}
EXPORT_SYMBOL(hisi_sd_unregister);

int is_fpga_board(void)
{
	cam_debug("%s is_fpga=%d.", __func__, is_fpga);
	return is_fpga;
}
EXPORT_SYMBOL(is_fpga_board);

void camdrv_msleep(unsigned int ms)
{
	struct timeval now;
	unsigned long jiffies;

	if (ms > 0) {
		now.tv_sec  = ms / 1000;
		now.tv_usec = (ms % 1000) * 1000;
		jiffies = timeval_to_jiffies(&now);
		schedule_timeout_interruptible(jiffies);
	}
}
EXPORT_SYMBOL(camdrv_msleep);

static struct v4l2_subdev *hisi_sd_find(const char *name)
{
	unsigned long flags;
	struct v4l2_subdev *subdev = NULL;

	spin_lock_irqsave(&hisi_v4l2_dev->lock, flags);
	if (!list_empty(&hisi_v4l2_dev->subdevs)) {
		list_for_each_entry(subdev, &hisi_v4l2_dev->subdevs, list)
			if (!strcmp(name, subdev->name))
				break;
	}
	spin_unlock_irqrestore(&hisi_v4l2_dev->lock, flags);

	return subdev;
}

static void hisi_sd_notify(struct v4l2_subdev *sd,
	unsigned int notification, void *arg)
{

	if(sd == NULL || arg == NULL) {
		cam_err("%s: invalid parameters", __func__);
		return;
	}

	/* Check if subdev exists before processing */
	if (!hisi_sd_find(sd->name))
		return;

	switch (notification) {
	case HISI_SD_NOTIFY_GET_SD: {
		struct hisi_sd_req_sd *get_sd = arg;

		get_sd->subdev = hisi_sd_find(get_sd->name);
		/* TODO: might need to add ref count on ret_sd */
	}
		break;

	default:
		cam_err("%s notification error.\n", __func__);
		break;
	}

}

static int hisi_camera_get_dt_data(struct platform_device *pdev)
{
	int rc=0;

	rc = of_property_read_u32(pdev->dev.of_node, "hisi,is_fpga",
		&is_fpga);
	cam_notice("%s hisi,is_fpga %d, rc %d\n", __func__,
		is_fpga, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
	}

	return rc;
}

static int hisi_camera_probe(struct platform_device *pdev)
{
	int rc = 0;

	cam_notice("%s enter.\n", __func__);

	hisi_v4l2_dev = kzalloc(sizeof(*hisi_v4l2_dev),
		GFP_KERNEL);
	if (WARN_ON(!hisi_v4l2_dev)) {
		rc = -ENOMEM;
		cam_err("%s failed line %d\n", __func__, __LINE__);
		goto probe_end;
	}

	if (pdev->dev.of_node) {
		rc = hisi_camera_get_dt_data(pdev);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			goto mdev_fail;
		}
	} else {
		cam_err("%s hisi camera of_node is NULL.\n", __func__);
	}

#if defined(CONFIG_MEDIA_CONTROLLER)
	hisi_v4l2_dev->mdev = kzalloc(sizeof(struct media_device),
		GFP_KERNEL);
	if (!hisi_v4l2_dev->mdev) {
		rc = -ENOMEM;
		cam_err("%s failed line %d\n", __func__, __LINE__);
		goto mdev_fail;
	}
	strlcpy(hisi_v4l2_dev->mdev->model, HISI_CONFIGURATION_NAME,
			sizeof(hisi_v4l2_dev->mdev->model));
	hisi_v4l2_dev->mdev->dev = &(pdev->dev);

	rc = media_device_register(hisi_v4l2_dev->mdev);
	if (WARN_ON(rc < 0)) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		goto media_fail;
	}
#endif

	hisi_v4l2_dev->notify = hisi_sd_notify;

	rc = v4l2_device_register(&(pdev->dev), hisi_v4l2_dev);
	if (WARN_ON(rc < 0)) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		goto register_fail;
	}

	goto probe_end;

register_fail:
#if defined(CONFIG_MEDIA_CONTROLLER)
media_fail:
	kfree(hisi_v4l2_dev->mdev);
mdev_fail:
	kfree(hisi_v4l2_dev);
#endif

probe_end:
	return rc;
}

static const struct of_device_id hisi_camera_dt_match[] = {
	{.compatible = "hisi,hisi_camera"},
	{}
};
MODULE_DEVICE_TABLE(of, hisi_camera_dt_match);
static struct platform_driver hisi_camera_driver = {
	.probe = hisi_camera_probe,
	.driver = {
		.name = "hisi_camera",
		.owner = THIS_MODULE,
		.of_match_table = hisi_camera_dt_match,
	},
};

static int __init hisi_camera_init(void)
{
	return platform_driver_register(&hisi_camera_driver);
}

static void __exit hisi_camera_exit(void)
{
	kfree(hisi_v4l2_dev->mdev);
	kfree(hisi_v4l2_dev);
	platform_driver_unregister(&hisi_camera_driver);
}

module_init(hisi_camera_init);
module_exit(hisi_camera_exit);
MODULE_DESCRIPTION("HISI V4L2 Camera");
MODULE_LICENSE("GPL v2");