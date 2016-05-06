


#include <linux/compiler.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <media/huawei/isp_cfg.h>
#include <media/v4l2-event.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-subdev.h>
#include <media/videobuf2-core.h>

#include "hwisp_intf.h"

typedef struct _tag_hwisp hwisp_t;

typedef struct _tag_hwisp
{
    struct v4l2_subdev                          subdev;
    struct platform_device*                     pdev;
    hwisp_notify_intf_t                         notify;
    struct mutex                                lock;

    hwisp_intf_t*                               hw;

    hwcam_data_table_t*                         cfg;
    struct ion_handle*                          cfg_hdl;
} hwisp_t;

#define SD2ISP(sd) container_of(sd, hwisp_t, subdev)
static int hwisp_vo_open(
        struct v4l2_subdev* sd,
        struct v4l2_subdev_fh* fh)
{
    hwisp_t* s = SD2ISP(sd);
    HWCAM_CFG_INFO("instance(0x%p)", s);
    return 0;
}

static int
hwisp_vo_close(
        struct v4l2_subdev* sd,
        struct v4l2_subdev_fh* fh)
{
    struct isp_cfg_data data;
    struct ion_handle* hdl = NULL;
    hwisp_t* s = SD2ISP(sd);
    hwcam_data_table_t* cfg = NULL;
    HWCAM_CFG_INFO("instance(0x%p)", s);

    if (mutex_lock_interruptible(&s->lock))
        return -ERESTARTSYS;
    data.cfgtype = CONFIG_POWER_OFF;
    s->hw->vtbl->config(s->hw,(void *)&data);
    mutex_unlock(&s->lock);

    swap(s->cfg_hdl, hdl);
    swap(s->cfg, cfg);
    if (hdl) {
        HWCAM_CFG_ERR("release isp driver data table!");
        hwcam_cfgdev_release_data_table(hdl);
    }

    return 0;
}

static struct v4l2_subdev_internal_ops
s_subdev_internal_ops_hwisp =
{
	.open = hwisp_vo_open,
	.close = hwisp_vo_close,
};

#define NotifytoHwisp(i) container_of(i, hwisp_t, notify)
static void hwisp_notify_sof(hwisp_notify_intf_t* i, hwisp_event_t* isp_ev)
{
    hwisp_t *isp = NULL;
    struct v4l2_event ev;
    struct video_device *vdev = NULL;
    hwisp_event_t* req = (hwisp_event_t*)ev.u.data;

    isp = NotifytoHwisp(i);
    vdev = isp->subdev.devnode;

    ev.type = HWISP_V4L2_EVENT_TYPE;
    ev.id = HWISP_HIGH_PRIO_EVENT;

    req->kind = isp_ev->kind;
    req->data.sof.pipeline = isp_ev->data.sof.pipeline;

    v4l2_event_queue(vdev, &ev);

}

static void hwisp_notify_eof(hwisp_notify_intf_t* i, hwisp_event_t* isp_ev)
{
    hwisp_t *isp = NULL;
    struct v4l2_event ev;
    struct video_device *vdev = NULL;
    hwisp_event_t* req = (hwisp_event_t*)ev.u.data;

    isp = NotifytoHwisp(i);
    vdev = isp->subdev.devnode;

    ev.type = HWISP_V4L2_EVENT_TYPE;
    ev.id = HWISP_HIGH_PRIO_EVENT;

    req->kind = isp_ev->kind;
    req->data.eof.pipeline = isp_ev->data.eof.pipeline;

    v4l2_event_queue(vdev, &ev);
}

static void hwisp_notify_cmd_ready(hwisp_notify_intf_t* i, hwisp_event_t* isp_ev)
{
    hwisp_t *isp = NULL;
    struct v4l2_event ev;
    struct video_device *vdev = NULL;
    hwisp_event_t* req = (hwisp_event_t*)ev.u.data;

    isp = NotifytoHwisp(i);
    vdev = isp->subdev.devnode;

    ev.type = HWISP_V4L2_EVENT_TYPE;
    ev.id = HWISP_HIGH_PRIO_EVENT;

    req->kind = isp_ev->kind;
    req->data.ready.cmd = isp_ev->data.ready.cmd;
    req->data.ready.result = isp_ev->data.ready.result;
    HWCAM_CFG_INFO("cmd = %d result = %d",isp_ev->data.ready.cmd,isp_ev->data.ready.result);
    v4l2_event_queue(vdev, &ev);
}

static hwisp_notify_vtbl_t s_notify_hwisp =
{
    .sof = hwisp_notify_sof,
    .eof = hwisp_notify_eof,
    .cmd_ready = hwisp_notify_cmd_ready,
};


static long
hwisp_vo_create_isp_stream(
        hwisp_t* isp,
        hwisp_stream_info_t* si)
{
    return hwisp_intf_create_stream(isp->hw, isp->subdev.devnode, si);
}

static long
hwisp_subdev_get_info(
        hwisp_t* isp,
        hwisp_info_t* info)
{
    memcpy(info->name, hwisp_intf_get_name(isp->hw),
            HWISP_NAME_SIZE);
    return 0;
}

static long
hwisp_subdev_mount_buf(
        hwisp_t* s,
        hwcam_buf_info_t* bi)
{
    long rc = -EINVAL;
    switch (bi->kind)
    {
    case HWCAM_BUF_KIND_PIPELINE_PARAM:
        if (!s->cfg) {
            s->cfg = hwcam_cfgdev_import_data_table(
                    "isp_drv_cfg", bi, &s->cfg_hdl);
            if (s->cfg) { rc = 0; }
        }
        break;
    default:
        HWCAM_CFG_ERR("invalid buffer kind(%d)! \n", bi->kind);
        break;
    }
    return rc;
}

static long
hwisp_subdev_unmount_buf(
        hwisp_t* s,
        hwcam_buf_info_t* bi)
{
    long rc = -EINVAL;
    switch (bi->kind)
    {
    case HWCAM_BUF_KIND_PIPELINE_PARAM:
        hwcam_cfgdev_release_data_table(s->cfg_hdl);
        s->cfg_hdl = NULL;
        s->cfg = NULL;
        rc = 0;
        break;
    default:
        HWCAM_CFG_ERR("invalid buffer kind(%d)! \n", bi->kind);
        break;
    }
    return rc;
}

static long
hwisp_vo_subdev_ioctl(
        struct v4l2_subdev* sd,
        unsigned int cmd,
        void *arg)
{
    long rc = 0;
    hwisp_t* isp = SD2ISP(sd);
    switch (cmd)
    {
    case HWISP_IOCTL_CREATE_ISP_STREAM:
        rc = hwisp_vo_create_isp_stream(isp, arg);
        break;
    case HWISP_IOCTL_GET_INFO:
        rc = hwisp_subdev_get_info(isp, arg);
        break;
    case HWCAM_V4L2_IOCTL_MOUNT_BUF:
        rc = hwisp_subdev_mount_buf(isp, arg);
        break;
    case HWCAM_V4L2_IOCTL_UNMOUNT_BUF:
        rc = hwisp_subdev_unmount_buf(isp, arg);
        break;
    case HWISP_IOCTL_CFG_ISP:
        rc = isp->hw->vtbl->config(isp->hw,arg);
        break;
    case HWISP_IOCTL_FIX_DDR:
        rc = isp->hw->vtbl->fix_ddrfreq(isp->hw, arg);
        break;
    default:
        HWCAM_CFG_ERR("invalid IOCTL CMD(%d)! \n", cmd);
        rc = -ENOENT;
        break;
    }
    return rc;
}

static int
hwisp_vo_power(
        struct v4l2_subdev* sd,
        int on)
{
	return 0;
}

static int
hwisp_subdev_subscribe_event(
        struct v4l2_subdev* sd,
        struct v4l2_fh* fh,
        struct v4l2_event_subscription* sub)
{
    HWCAM_CFG_INFO("enter ");
    return v4l2_event_subscribe(fh, sub, 128, NULL);
}

static int
hwisp_subdev_unsubscribe_event(
        struct v4l2_subdev* sd,
        struct v4l2_fh* fh,
        struct v4l2_event_subscription* sub)
{
    HWCAM_CFG_INFO("enter ");
    return v4l2_event_unsubscribe(fh, sub);
}


static struct v4l2_subdev_core_ops
s_subdev_core_ops_hwisp =
{
    .ioctl = hwisp_vo_subdev_ioctl,
    .s_power = hwisp_vo_power,
    .subscribe_event = hwisp_subdev_subscribe_event,
    .unsubscribe_event = hwisp_subdev_unsubscribe_event,
};

static struct v4l2_subdev_ops
s_subdev_ops_hwisp =
{
	.core = &s_subdev_core_ops_hwisp,
};

int32_t
hwisp_register(
    struct platform_device* pdev,
    hwisp_intf_t* hw,
    hwisp_notify_intf_t** notify)
{
    int rc = 0;
    struct v4l2_subdev* subdev = NULL;
    hwisp_t* isp = kzalloc(sizeof(hwisp_t), GFP_KERNEL);

    if (isp == NULL) {
        rc = -ENOMEM;
        goto alloc_fail;
    }

    subdev = &isp->subdev;
    mutex_init(&isp->lock);

    v4l2_subdev_init(subdev, &s_subdev_ops_hwisp);
    subdev->internal_ops = &s_subdev_internal_ops_hwisp;
    snprintf(subdev->name, sizeof(subdev->name), "hwcam-cfg-isp");
    subdev->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
    subdev->flags |= V4L2_SUBDEV_FL_HAS_EVENTS;
    v4l2_set_subdevdata(subdev, pdev);
    platform_set_drvdata(pdev, subdev);

    media_entity_init(&subdev->entity, 0, NULL, 0);
    subdev->entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
    subdev->entity.group_id = HWCAM_SUBDEV_ISP;
    subdev->entity.name = subdev->name;

    hwcam_cfgdev_register_subdev(subdev);
    subdev->devnode->lock = &isp->lock;

    isp->hw = hw;
    isp->pdev = pdev;
    isp->notify.vtbl = &s_notify_hwisp;
    *notify = &(isp->notify);

alloc_fail:
    return rc;
}

#define HwtoHwisp(isp_intf) container_of(isp_intf, hwisp_t, hw)
void
hwisp_unregister(hwisp_intf_t* isp_intf)
{
    hwisp_t* isp = NULL;
    struct v4l2_subdev* subdev = NULL;

    isp = HwtoHwisp(isp_intf);
    subdev  = &isp->subdev;
    media_entity_cleanup(&subdev->entity);
    hwcam_cfgdev_unregister_subdev(subdev);

    kzfree(isp);
}

