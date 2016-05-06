/* Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
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
#include <linux/hisi/hisi-iommu.h>
#include <media/v4l2-fh.h>

#include "hisi_camera.h"
#include "../hisi_cam_module.h"
#include "isp_ops.h"

#include <linux/hisi/hi3xxx/global_ddr_map.h>

u32 cam_debug_mask = CAM_DEBUG_EMERG|CAM_DEBUG_ALERT|CAM_DEBUG_CRIT| \
									CAM_DEBUG_ERR|CAM_DEBUG_WARING | CAM_DEBUG_NOTICE;
#define CAM_DEBUG_MASK_LENGTH    32

static ssize_t camera_debug_set_mask(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	u32 value = 0;
	value = simple_strtoul(buf, NULL, 0);
	cam_debug_mask = value;
	return count;
}

static ssize_t camera_debug_get_mask(struct device *dev, struct device_attribute *attr, char *buf)
{
	 int ret;
        snprintf(buf, CAM_DEBUG_MASK_LENGTH, "cam_debug_mask= 0x%x\n", cam_debug_mask);
        ret = strlen(buf)+1;
        return ret;
}

static ssize_t camera_thermal_adjust_set_fps(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	u32 value = 0;
	value = simple_strtoul(buf, NULL, 0);
	//todo
	cam_info("enter %s, set fps level = %d", __func__, value);
	return count;
}

static ssize_t camera_thermal_adjust_get_fps(struct device *dev, struct device_attribute *attr, char *buf)
{
	//todo
	return 1;
}
/*this node establish for controlling camera debug print*/
static struct device_attribute camera_for_debug=
    __ATTR(camera_debug_onoff, 0664, camera_debug_get_mask,
                        camera_debug_set_mask);

/*this node establish for adjusting camera frame rate according to temperature*/
static struct device_attribute camera_thermal_adjust_fps=
    __ATTR(camera_fps_adjust, 0664, camera_thermal_adjust_get_fps,
                        camera_thermal_adjust_set_fps);

static int camera_v4l2_g_ext_ctrls(struct file *file, void *fh, struct v4l2_ext_controls *arg)
{
	u32 cid_idx;
	int ret							= 0;
	struct v4l2_ext_controls *ext_ctls	= arg;
	struct v4l2_ext_control *controls	= NULL;
	cam_debug("enter %s", __func__);

	if (ext_ctls->ctrl_class != V4L2_CTRL_CLASS_CAMERA) {
		cam_err("unsupported ctrl class!");
		ret = -EINVAL;
		goto out;
	}

	controls = (struct v4l2_ext_control *) ext_ctls->controls;

	for (cid_idx = 0; cid_idx < ext_ctls->count; cid_idx++) {
		switch (controls[cid_idx].id) {

		case V4L2_CID_MEM_INFO:
		{
			controls[cid_idx].value = k3_get_isp_base_addr();
			controls[cid_idx].size = k3_get_isp_mem_size();
			break;
		}

		case V4L2_CID_MMU_INFO:
		{
			//controls[cid_idx].value = HISI_RESERVED_SMMU_PHYMEM_BASE;
			//controls[cid_idx].value = HISI_IOMMU_PTABLE_ADDR;
			hisi_iommu_get_info(&controls[cid_idx].size, &controls[cid_idx].value);
			break;
		}

		default:
			break;
		}
	}
out:
	return ret;
}


static const struct v4l2_ioctl_ops camera_v4l2_ioctl_ops = {
	.vidioc_g_ext_ctrls = camera_v4l2_g_ext_ctrls,
};


static int camera_v4l2_open(struct file *filep)
{
	int rc = 0;
	struct hisi_video_device *pvdev = video_drvdata(filep);
	if(!pvdev) {
		cam_err("pvdev is NULL");
		rc = -1;
		return rc;
	}

	cam_debug("%s enter.\n", __func__);
	if (!atomic_read(&pvdev->opened)) {
		rc = k3_isp_init(pvdev->vdev->v4l2_dev->dev);
		if (rc) {
			cam_err("%s failed to init isp.\n", __func__);
			return rc;
		}

		rc = k3_isp_poweron();
		if(rc) {
			cam_err("%s failed to power on isp.\n", __func__);
			return rc;
		}
	} else {
		cam_notice("%s isp has been opened.\n", __func__);
	}

	atomic_add(1, &pvdev->opened);
	return rc;
}

static unsigned int camera_v4l2_poll(struct file *filep,
	struct poll_table_struct *wait)
{
	unsigned int rc = 0;

	cam_debug("enter %s\n", __func__);

	rc = k3_poll_irq(filep, wait);

	return rc;
}

ssize_t camera_v4l2_read(struct file *filp, char __user *buf, size_t size, loff_t *offset)
{
	struct irq_reg_t irq_buf;

	cam_debug("enter %s\n", __func__);

	k3_query_irq(&irq_buf);

	if (copy_to_user(buf, &irq_buf, size)) {
		cam_err("failed to query irq info!");
		return -EFAULT;
	}

	return 0;
}


static int camera_v4l2_close(struct file *filep)
{
	int rc = -1;
	struct hisi_video_device *pvdev = video_drvdata(filep);
	cam_debug("enter %s.\n", __func__);
	if(!pvdev) {
		cam_err("pvdev is NULL");
		return rc;
	}

	if (atomic_dec_and_test(&pvdev->opened)) {
		rc = k3_isp_poweroff();
		if (rc) {
			cam_err("failed to poweroff isp!");
			return rc;
		}

		rc = k3_isp_deinit();
		if (rc) {
			cam_err("failed to deinit isp!");
			return rc;
		}

	} else {
		cam_err("camera dev has been closed!");
	}

	return rc;
}

static int camera_v4l2_mmap(struct file *file, struct vm_area_struct *vma)
{
	unsigned long size;
	int ret = 0;

	size = vma->vm_end - vma->vm_start;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	if (remap_pfn_range(vma, vma->vm_start,
			    vma->vm_pgoff, size, vma->vm_page_prot)) {
		cam_err("%s, remap_pfn_range fail", __func__);
		ret = -ENOBUFS;
	} else {
		vma->vm_flags &= ~VM_IO;
		ret = 0;
	}

	return ret;
}

static struct v4l2_file_operations camera_v4l2_fops = {
	.owner   = THIS_MODULE,
	.open	= camera_v4l2_open,
	.poll	= camera_v4l2_poll,
	.read	= camera_v4l2_read,
	.mmap	= camera_v4l2_mmap,
	.release = camera_v4l2_close,
	.ioctl   = video_ioctl2,
	.compat_ioctl32 = video_ioctl2,
};

int camera_init_v4l2(struct platform_device *pdev)
{
	struct hisi_video_device *pvdev;
	struct v4l2_device *v4l2_dev;
	int rc = 0;

	cam_debug("%s enter.\n", __func__);

	pvdev = kzalloc(sizeof(struct hisi_video_device),
		GFP_KERNEL);
	if (!pvdev) {
		rc = -ENOMEM;
		goto init_end;
	}

	pvdev->vdev = video_device_alloc();
	if (WARN_ON(!pvdev->vdev)) {
		rc = -ENOMEM;
		goto video_fail;
	}

	v4l2_dev = kzalloc(sizeof(struct v4l2_device), GFP_KERNEL);
	if (!v4l2_dev) {
		rc = -ENOMEM;
		goto v4l2_fail;
	}

#if defined(CONFIG_MEDIA_CONTROLLER)
	v4l2_dev->mdev = kzalloc(sizeof(struct media_device), GFP_KERNEL);
	if (!v4l2_dev->mdev) {
		rc = -ENOMEM;
		cam_err("%s, %d", __func__, __LINE__);
		goto mdev_fail;
	}
	strlcpy(v4l2_dev->mdev->model, HISI_CAMERA_NAME,
			sizeof(v4l2_dev->mdev->model));

	v4l2_dev->mdev->dev = &pdev->dev;

	rc = media_device_register(v4l2_dev->mdev);
	if (WARN_ON(rc < 0))
		goto media_fail;

	rc = media_entity_init(&pvdev->vdev->entity, 0, NULL, 0);
	if (WARN_ON(rc < 0))
		goto entity_fail;
	pvdev->vdev->entity.type = MEDIA_ENT_T_DEVNODE_V4L;
	pvdev->vdev->entity.group_id = CAMERA_VNODE_GROUP_ID;
#endif

	v4l2_dev->notify = NULL;
	pvdev->vdev->v4l2_dev = v4l2_dev;

	rc = v4l2_device_register(&pdev->dev, pvdev->vdev->v4l2_dev);
	if (WARN_ON(rc < 0))
		goto register_fail;

	strlcpy(pvdev->vdev->name, "hisi-isp", sizeof(pvdev->vdev->name));
	pvdev->vdev->release  = video_device_release;
	pvdev->vdev->fops     = &camera_v4l2_fops;
	pvdev->vdev->ioctl_ops = &camera_v4l2_ioctl_ops;
	rc = video_register_device(pvdev->vdev,
		VFL_TYPE_GRABBER, -1);
	if (WARN_ON(rc < 0))
		goto video_register_fail;

	rc = device_create_file(&pvdev->vdev->dev, &camera_for_debug);
	if (WARN_ON(rc < 0))
	{
		cam_err("camera_for_debug node create  failed %d\n", rc);
		goto video_register_fail;
	}

	rc = device_create_file(&pvdev->vdev->dev, &camera_thermal_adjust_fps);
	if (WARN_ON(rc < 0))
	{
		cam_err("camera_thermal_adjust_fps node create failed %d\n", rc);
		goto video_register_fail;
	}

#if defined(CONFIG_MEDIA_CONTROLLER)
	pvdev->vdev->entity.name = video_device_node_name(pvdev->vdev);
#endif

	atomic_set(&pvdev->opened, 0);
	video_set_drvdata(pvdev->vdev, pvdev);
	goto init_end;

video_register_fail:
	v4l2_device_unregister(pvdev->vdev->v4l2_dev);
register_fail:
#if defined(CONFIG_MEDIA_CONTROLLER)
	media_entity_cleanup(&pvdev->vdev->entity);
entity_fail:
	media_device_unregister(v4l2_dev->mdev);
media_fail:
	kfree(v4l2_dev->mdev);
mdev_fail:
#endif
	kfree(v4l2_dev);
v4l2_fail:
	video_device_release(pvdev->vdev);
video_fail:
	kfree(pvdev);
init_end:
	return rc;
}
EXPORT_SYMBOL(camera_init_v4l2);
