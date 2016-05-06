


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
#include "hwextisp.h"

typedef struct _tag_hwextisp hwextisp_t;

typedef struct _tag_hwextisp
{
    struct v4l2_subdev                          subdev;
    struct platform_device*                     pdev;
	struct mutex                                lock;

    const hwextisp_intf_t*                      hw;

    hwcam_data_table_t*                         cfg;
    struct ion_handle*                          cfg_hdl;
    hwextisp_notify_intf_t                         notify;
} hwextisp_t;

#define SD2ExtISP(sd) container_of(sd, hwextisp_t, subdev)

static long
hwextisp_subdev_config(
        hwextisp_t* s,
        hwextisp_config_data_t* data);

static int hwextisp_v4l2_open(
        struct v4l2_subdev* sd,
        struct v4l2_subdev_fh* fh)
{
    hwextisp_t* s = SD2ExtISP(sd);
    HWCAM_CFG_INFO("instance(0x%p)", s);
    return 0;
}

static int
hwextisp_v4l2_close(
        struct v4l2_subdev* sd,
        struct v4l2_subdev_fh* fh)
{
    struct ion_handle* hdl = NULL;
    hwextisp_t* s = SD2ExtISP(sd);
    hwextisp_config_data_t edata;
    hwcam_data_table_t* cfg = NULL;

    HWCAM_CFG_INFO("instance(0x%p)", s);
    edata.cfgtype = HWCAM_EXTISP_POWEROFF;
    hwextisp_subdev_config(s, &edata);

    swap(s->cfg_hdl, hdl);
    swap(s->cfg, cfg);
    if (hdl) {
        HWCAM_CFG_ERR("release extisp driver data table!");
        hwcam_cfgdev_release_data_table(hdl);
    }

    return 0;
}

static struct v4l2_subdev_internal_ops
s_hwextisp_subdev_internal_ops =
{
	.open = hwextisp_v4l2_open,
	.close = hwextisp_v4l2_close,
};

static long
hwextisp_subdev_get_info(
        hwextisp_t* isp,
        hwextisp_info_t* info)
{
    memcpy(info->name, hwextisp_intf_get_name(isp->hw),
            HWEXTISP_NAME_SIZE);
    return 0;
}

static long
hwextisp_subdev_mount_buf(
        hwextisp_t* s,
        hwcam_buf_info_t* bi)
{
    long rc = -EINVAL;
    switch (bi->kind)
    {
    case HWCAM_BUF_KIND_PIPELINE_PARAM:
        if (!s->cfg) {
            s->cfg = hwcam_cfgdev_import_data_table(
                    "extisp_drv_cfg", bi, &s->cfg_hdl);
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
hwextisp_subdev_unmount_buf(
        hwextisp_t* s,
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
hwextisp_subdev_config(
        hwextisp_t* s,
        hwextisp_config_data_t* data)
{
    long rc = -EINVAL;
    static bool hwextisp_power_on = false;
    switch (data->cfgtype)
    {
    case HWCAM_EXTISP_CMD:
        rc = s->hw->vtbl->exec_cmd(s->hw, data);
        break;
    case HWCAM_EXTISP_POWERON:
        if (!hwextisp_power_on) {
            rc = s->hw->vtbl->power_on(s->hw);
            hwextisp_power_on = true;
        }
        break;
    case HWCAM_EXTISP_POWEROFF:
        if (hwextisp_power_on) {
            rc = s->hw->vtbl->power_off(s->hw);
            hwextisp_power_on = false;
        }
        break;
    case HWCAM_EXTISP_LOADFW:
         rc = s->hw->vtbl->load_firmware(s->hw, data);
        break;
case HWCAM_EXTISP_MATCHID:
         rc = s->hw->vtbl->matchid(s->hw, data);
        break;
    default:
        HWCAM_CFG_ERR("invalid cfgtype(%d)! \n", data->cfgtype);
        break;
    }
    return rc;
}

static long
hwextisp_subdev_ioctl(
        struct v4l2_subdev* sd,
        unsigned int cmd,
        void *arg)
{
    long rc = -EINVAL;
    hwextisp_t* s = SD2ExtISP(sd);
    switch (cmd)
    {
    case HWEXTISP_IOCTL_GET_INFO:
        rc = hwextisp_subdev_get_info(s, arg);
        break;
    case HWCAM_V4L2_IOCTL_MOUNT_BUF:
        rc = hwextisp_subdev_mount_buf(s, arg);
        break;
    case HWCAM_V4L2_IOCTL_UNMOUNT_BUF:
        rc = hwextisp_subdev_unmount_buf(s, arg);
        break;
    case HWEXTISP_IOCTL_CONFIG:
        rc = hwextisp_subdev_config(s, arg);
        break;
    default:
        HWCAM_CFG_ERR("invalid IOCTL CMD(%d)! \n", cmd);
        break;
    }
    return rc;
}

static int
hwextisp_subdev_subscribe_event(
        struct v4l2_subdev* sd,
        struct v4l2_fh* fh,
        struct v4l2_event_subscription* sub)
{
    return v4l2_event_subscribe(fh, sub, 128, NULL);
}

static int
hwextisp_subdev_unsubscribe_event(
        struct v4l2_subdev* sd,
        struct v4l2_fh* fh,
        struct v4l2_event_subscription* sub)
{
    return v4l2_event_unsubscribe(fh, sub);
}

static int
hwextisp_power(
        struct v4l2_subdev* sd,
        int on)
{
	return 0;
}

#define NotifytoHwextisp(i) container_of(i, hwextisp_t, notify)

static void hwextisp_notify_cmd_finish(hwextisp_notify_intf_t* i, hwextisp_event_t* extisp_ev)
{
	hwextisp_t *extisp = NULL;
	struct v4l2_event ev;
	struct video_device *vdev = NULL;
	hwextisp_event_t* req = (hwextisp_event_t*)ev.u.data;

	extisp = NotifytoHwextisp(i);
	vdev = extisp->subdev.devnode;

	ev.type = HWEXTISP_V4L2_EVENT_TYPE;
	ev.id = HWEXTISP_HIGH_PRIO_EVENT;

	req->kind = extisp_ev->kind;
	req->data.cmd_finish.cmd = extisp_ev->data.cmd_finish.cmd;
	req->data.cmd_finish.result = extisp_ev->data.cmd_finish.result;

	v4l2_event_queue(vdev, &ev);
}

static void hwextisp_notify_error(hwextisp_notify_intf_t* i, hwextisp_event_t* extisp_ev)
{
	hwextisp_t *extisp = NULL;
	struct v4l2_event ev;
	struct video_device *vdev = NULL;
	hwextisp_event_t* req = (hwextisp_event_t*)ev.u.data;

	extisp = NotifytoHwextisp(i);
	vdev = extisp->subdev.devnode;

	ev.type = HWEXTISP_V4L2_EVENT_TYPE;
	ev.id = HWEXTISP_HIGH_PRIO_EVENT;

	req->kind = extisp_ev->kind;
	req->data.error.id = extisp_ev->data.error.id;

	v4l2_event_queue(vdev, &ev);
}

static void hwextisp_notify_dump(hwextisp_notify_intf_t* i, hwextisp_event_t* extisp_ev)
{
	hwextisp_t *extisp = NULL;
	struct v4l2_event ev;
	struct video_device *vdev = NULL;
	hwextisp_event_t* req = (hwextisp_event_t*)ev.u.data;

	extisp = NotifytoHwextisp(i);
	vdev = extisp->subdev.devnode;

	ev.type = HWEXTISP_V4L2_EVENT_TYPE;
	ev.id = HWEXTISP_HIGH_PRIO_EVENT;

	req->kind = extisp_ev->kind;
	req->data.dump.type = extisp_ev->data.dump.type;

	v4l2_event_queue(vdev, &ev);
}


static hwextisp_notify_vtbl_t s_notify_hwextisp =
{
    .cmd_finish = hwextisp_notify_cmd_finish,
    .error         = hwextisp_notify_error,
    .dump        = hwextisp_notify_dump,
};

static struct v4l2_subdev_core_ops
s_hwextisp_subdev_core_ops =
{
	.ioctl = hwextisp_subdev_ioctl,
    .subscribe_event = hwextisp_subdev_subscribe_event,
    .unsubscribe_event = hwextisp_subdev_unsubscribe_event,
	.s_power = hwextisp_power,
};

static struct v4l2_subdev_ops
s_hwextisp_subdev_ops =
{
	.core = &s_hwextisp_subdev_core_ops,
};

int32_t
hwextisp_register(
        struct platform_device* pdev, const hwextisp_intf_t* i,
        hwextisp_notify_intf_t** notify)
{
	int rc = 0;
    struct v4l2_subdev* subdev = NULL;
    hwextisp_t* extisp = kzalloc(sizeof(hwextisp_t), GFP_KERNEL);
    if (extisp == NULL) {
        rc = -ENOMEM;
        goto alloc_fail;
    }

    subdev = &extisp->subdev;
    v4l2_subdev_init(subdev, &s_hwextisp_subdev_ops);
	subdev->internal_ops = &s_hwextisp_subdev_internal_ops;
    snprintf(subdev->name, sizeof(subdev->name), "hwcam-cfg-extisp");
	subdev->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	subdev->flags |= V4L2_SUBDEV_FL_HAS_EVENTS;
    v4l2_set_subdevdata(subdev, pdev);
	platform_set_drvdata(pdev, subdev);

	mutex_init(&extisp->lock);

    media_entity_init(&subdev->entity, 0, NULL, 0);
    subdev->entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
    subdev->entity.group_id = HWCAM_SUBDEV_EXTISP;
    subdev->entity.name = subdev->name;

    hwcam_cfgdev_register_subdev(subdev);
    subdev->devnode->lock = &extisp->lock;
    extisp->hw = pdev->dev.driver->of_match_table->data;
    extisp->pdev = pdev;

    extisp->notify.vtbl = &s_notify_hwextisp;
    *notify = &(extisp->notify);

    if (i->vtbl->mini_isp_get_dt_data)
        rc = i->vtbl->mini_isp_get_dt_data(i, pdev->dev.of_node);

    if (i->vtbl->mini_isp_register_attribute)
        rc = i->vtbl->mini_isp_register_attribute(i, &subdev->devnode->dev);
alloc_fail:
    return rc;
}

