


#include <linux/compiler.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <media/huawei/camera.h>
#include <media/v4l2-event.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-subdev.h>
#include <media/videobuf2-core.h>

#include "hwcam_intf.h"
#include "hwdepthisp.h"

typedef struct _tag_hwdepthisp hwdepthisp_t;

typedef struct _tag_hwdepthisp
{
    struct v4l2_subdev                          subdev;
    struct platform_device*                     pdev;
	struct mutex                                lock;

    const hwdepthisp_intf_t*                      hw;

    hwcam_data_table_t*                         cfg;
    struct ion_handle*                          cfg_hdl;
    hwdepthisp_notify_intf_t                         notify;
} hwdepthisp_t;

#define SD2DepthISP(sd) container_of(sd, hwdepthisp_t, subdev)

static long
hwdepthisp_subdev_config(
        hwdepthisp_t* s,
        hwdepthisp_config_data_t* data);

static int hwdepthisp_v4l2_open(
        struct v4l2_subdev* sd,
        struct v4l2_subdev_fh* fh)
{
    hwdepthisp_t* s = SD2DepthISP(sd);
    HWCAM_CFG_INFO("instance(0x%p)", s);
    return 0;
}

static int
hwdepthisp_v4l2_close(
        struct v4l2_subdev* sd,
        struct v4l2_subdev_fh* fh)
{
    struct ion_handle* hdl = NULL;
    hwdepthisp_t* s = SD2DepthISP(sd);
    hwdepthisp_config_data_t edata;
    hwcam_data_table_t* cfg = NULL;

    HWCAM_CFG_INFO("instance(0x%p)", s);
    edata.cfgtype = HWCAM_DEPTHISP_POWEROFF;
    hwdepthisp_subdev_config(s, &edata);

    swap(s->cfg_hdl, hdl);
    swap(s->cfg, cfg);
    if (hdl) {
        HWCAM_CFG_ERR("release depthisp driver data table!");
        hwcam_cfgdev_release_data_table(hdl);
    }

    return 0;
}

static struct v4l2_subdev_internal_ops
s_hwdepthisp_subdev_internal_ops =
{
	.open = hwdepthisp_v4l2_open,
	.close = hwdepthisp_v4l2_close,
};

static long
hwdepthisp_subdev_get_info(
        hwdepthisp_t* isp,
        hwdepthisp_info_t* info)
{
    memcpy(info->name, hwdepthisp_intf_get_name(isp->hw),
            HWDEPTHISP_NAME_SIZE);
    return 0;
}

static long
hwdepthisp_subdev_mount_buf(
        hwdepthisp_t* s,
        hwcam_buf_info_t* bi)
{
    long rc = -EINVAL;
    switch (bi->kind)
    {
    case HWCAM_BUF_KIND_PIPELINE_PARAM:
        if (!s->cfg) {
            s->cfg = hwcam_cfgdev_import_data_table(
                    "depthisp_drv_cfg", bi, &s->cfg_hdl);
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
hwdepthisp_subdev_unmount_buf(
        hwdepthisp_t* s,
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
hwdepthisp_subdev_config(
        hwdepthisp_t* s,
        hwdepthisp_config_data_t* data)
{
    long rc = -EINVAL;
    static bool hwdepthisp_power_on = false;
    switch (data->cfgtype)
    {
    case HWCAM_DEPTHISP_CMD:
        rc = s->hw->vtbl->exec_cmd(s->hw, data);
        break;
    case HWCAM_DEPTHISP_POWERON:
        if (!hwdepthisp_power_on) {
            rc = s->hw->vtbl->power_on(s->hw);
            hwdepthisp_power_on = true;
        }
        break;
    case HWCAM_DEPTHISP_POWEROFF:
        if (hwdepthisp_power_on) {
            rc = s->hw->vtbl->power_off(s->hw);
            hwdepthisp_power_on = false;
        }
        break;
    case HWCAM_DEPTHISP_LOADFW:
         rc = s->hw->vtbl->load_firmware(s->hw, data);
        break;
    case HWCAM_DEPTHISP_MATCHID:
         rc = s->hw->vtbl->matchid(s->hw, data);
        break;
    default:
        HWCAM_CFG_ERR("invalid cfgtype(%d)! \n", data->cfgtype);
        break;
    }
    return rc;
}

static long
hwdepthisp_subdev_ioctl(
        struct v4l2_subdev* sd,
        unsigned int cmd,
        void *arg)
{
    long rc = -EINVAL;
    hwdepthisp_t* s = SD2DepthISP(sd);
    switch (cmd)
    {
    case HWDEPTHISP_IOCTL_GET_INFO:
        rc = hwdepthisp_subdev_get_info(s, arg);
        break;
    case HWCAM_V4L2_IOCTL_MOUNT_BUF:
        rc = hwdepthisp_subdev_mount_buf(s, arg);
        break;
    case HWCAM_V4L2_IOCTL_UNMOUNT_BUF:
        rc = hwdepthisp_subdev_unmount_buf(s, arg);
        break;
    case HWDEPTHISP_IOCTL_CONFIG:
        rc = hwdepthisp_subdev_config(s, arg);
        break;
    default:
        HWCAM_CFG_ERR("invalid IOCTL CMD(%d)! \n", cmd);
        break;
    }
    return rc;
}

static int
hwdepthisp_subdev_subscribe_event(
        struct v4l2_subdev* sd,
        struct v4l2_fh* fh,
        struct v4l2_event_subscription* sub)
{
    return v4l2_event_subscribe(fh, sub, 128, NULL);
}

static int
hwdepthisp_subdev_unsubscribe_event(
        struct v4l2_subdev* sd,
        struct v4l2_fh* fh,
        struct v4l2_event_subscription* sub)
{
    return v4l2_event_unsubscribe(fh, sub);
}

static int
hwdepthisp_power(
        struct v4l2_subdev* sd,
        int on)
{
	return 0;
}

#define NotifytoHwdepthisp(i) container_of(i, hwdepthisp_t, notify)

static void hwdepthisp_notify_cmd_finish(hwdepthisp_notify_intf_t* i, hwdepthisp_event_t* depthisp_ev)
{
	hwdepthisp_t *depthisp = NULL;
	struct v4l2_event ev;
	struct video_device *vdev = NULL;
	hwdepthisp_event_t* req = (hwdepthisp_event_t*)ev.u.data;

	depthisp = NotifytoHwdepthisp(i);
	vdev = depthisp->subdev.devnode;

	ev.type = HWDEPTHISP_V4L2_EVENT_TYPE;
	ev.id = HWDEPTHISP_HIGH_PRIO_EVENT;

	req->kind = depthisp_ev->kind;
	req->data.cmd_finish.cmd = depthisp_ev->data.cmd_finish.cmd;
	req->data.cmd_finish.result = depthisp_ev->data.cmd_finish.result;

	v4l2_event_queue(vdev, &ev);
}

static void hwdepthisp_notify_error(hwdepthisp_notify_intf_t* i, hwdepthisp_event_t* depthisp_ev)
{
	hwdepthisp_t *depthisp = NULL;
	struct v4l2_event ev;
	struct video_device *vdev = NULL;
	hwdepthisp_event_t* req = (hwdepthisp_event_t*)ev.u.data;

	depthisp = NotifytoHwdepthisp(i);
	vdev = depthisp->subdev.devnode;

	ev.type = HWDEPTHISP_V4L2_EVENT_TYPE;
	ev.id = HWDEPTHISP_HIGH_PRIO_EVENT;

	req->kind = depthisp_ev->kind;
	req->data.error.id = depthisp_ev->data.error.id;

	v4l2_event_queue(vdev, &ev);
}

static void hwdepthisp_notify_dump(hwdepthisp_notify_intf_t* i, hwdepthisp_event_t* depthisp_ev)
{
	hwdepthisp_t *depthisp = NULL;
	struct v4l2_event ev;
	struct video_device *vdev = NULL;
	hwdepthisp_event_t* req = (hwdepthisp_event_t*)ev.u.data;

	depthisp = NotifytoHwdepthisp(i);
	vdev = depthisp->subdev.devnode;

	ev.type = HWDEPTHISP_V4L2_EVENT_TYPE;
	ev.id = HWDEPTHISP_HIGH_PRIO_EVENT;

	req->kind = depthisp_ev->kind;
	req->data.dump.type = depthisp_ev->data.dump.type;

	v4l2_event_queue(vdev, &ev);
}


static hwdepthisp_notify_vtbl_t s_notify_hwdepthisp =
{
    .cmd_finish = hwdepthisp_notify_cmd_finish,
    .error         = hwdepthisp_notify_error,
    .dump        = hwdepthisp_notify_dump,
};

static struct v4l2_subdev_core_ops
s_hwdepthisp_subdev_core_ops =
{
	.ioctl = hwdepthisp_subdev_ioctl,
    .subscribe_event = hwdepthisp_subdev_subscribe_event,
    .unsubscribe_event = hwdepthisp_subdev_unsubscribe_event,
	.s_power = hwdepthisp_power,
};

static struct v4l2_subdev_ops
s_hwdepthisp_subdev_ops =
{
	.core = &s_hwdepthisp_subdev_core_ops,
};

int32_t
hwdepthisp_register(
        struct platform_device* pdev, const hwdepthisp_intf_t* i,
        hwdepthisp_notify_intf_t** notify)
{
	int rc = 0;
    struct v4l2_subdev* subdev = NULL;
    hwdepthisp_t* depthisp = kzalloc(sizeof(hwdepthisp_t), GFP_KERNEL);
    if (depthisp == NULL) {
        rc = -ENOMEM;
        goto alloc_fail;
    }

    subdev = &depthisp->subdev;
    v4l2_subdev_init(subdev, &s_hwdepthisp_subdev_ops);
	subdev->internal_ops = &s_hwdepthisp_subdev_internal_ops;
    snprintf(subdev->name, sizeof(subdev->name), "hwcam-cfg-depthisp");
	subdev->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	subdev->flags |= V4L2_SUBDEV_FL_HAS_EVENTS;
    v4l2_set_subdevdata(subdev, pdev);
	platform_set_drvdata(pdev, subdev);

	mutex_init(&depthisp->lock);

    media_entity_init(&subdev->entity, 0, NULL, 0);
    subdev->entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
    subdev->entity.group_id = HWCAM_SUBDEV_DEPTHISP;
    subdev->entity.name = subdev->name;

    hwcam_cfgdev_register_subdev(subdev);
    subdev->devnode->lock = &depthisp->lock;
    depthisp->hw = pdev->dev.driver->of_match_table->data;
    depthisp->pdev = pdev;

    depthisp->notify.vtbl = &s_notify_hwdepthisp;
    *notify = &(depthisp->notify);

    if (i->vtbl->depth_isp_get_dt_data)
        rc = i->vtbl->depth_isp_get_dt_data(i, pdev->dev.of_node);

    if (i->vtbl->depth_isp_register_attribute)
        rc = i->vtbl->depth_isp_register_attribute(i, &subdev->devnode->dev);
alloc_fail:
    return rc;
}


/*added for memory hwisp_t leak  **/
void
hwdepthisp_unregister(hwdepthisp_intf_t* depthisp_intf)
{
    hwdepthisp_t* depthisp = NULL;
    struct v4l2_subdev* subdev = NULL;

    depthisp = container_of(depthisp_intf, hwdepthisp_t, hw);
    subdev  = &depthisp->subdev;
    media_entity_cleanup(&subdev->entity);
    hwcam_cfgdev_unregister_subdev(subdev);

    kzfree(depthisp);
}
/*added for memory hwdepthisp_t leak **/