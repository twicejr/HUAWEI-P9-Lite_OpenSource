


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

#include "hwcam_intf.h"
#include "hwsensor.h"
#include "sensor_commom.h"
#include "cam_log.h"

typedef struct _tag_hwsensor
{
    struct v4l2_subdev                          subdev;
    struct platform_device*                     pdev;

    hwsensor_intf_t*                            intf;
    int                                         cam_dev_num;
    struct mutex                                lock;
    hwcam_data_table_t*                         cfg;
    struct ion_handle*                          cfg_hdl;
} hwsensor_t;

#define SD2Sensor(sd) container_of(sd, hwsensor_t, subdev)
#define I2S(i) container_of(i, sensor_t, intf)

static int hw_sensor_subdev_internal_close(struct v4l2_subdev *sd, struct v4l2_subdev_fh *fh)
{
    hwsensor_t *s = SD2Sensor(sd);
    int rc=0;
    struct sensor_cfg_data cdata = {0};
    cdata.cfgtype = SEN_CONFIG_POWER_OFF;

    if (s == NULL) {
        cam_err("%s get s_strl error", __func__);
        return -1;
    }
    if (s->intf == NULL || s->intf->vtbl == NULL
        || s->intf->vtbl->config == NULL || s->intf->vtbl->csi_disable == NULL)
        return rc;

    rc = s->intf->vtbl->csi_disable(s->intf);
    rc |= s->intf->vtbl->config(s->intf,(void *)(&cdata));

    cam_notice(" enter %s,return value %d", __func__,rc);
    return rc;
}

static int hwsensor_init(hwsensor_t* s_ctrl)
{

    //sensor_t *sensor = I2S(s_ctrl->intf);
    cam_info("%s enter.\n", __func__);
    //to do
    return 0;
}


static int hwsensor_subdev_open(
        struct v4l2_subdev* sd,
        struct v4l2_subdev_fh* fh)
{
    hwsensor_t* s = NULL;
    s = SD2Sensor(sd);
    HWCAM_CFG_INFO("instance(0x%p). \n", s);
    hwsensor_init(s);
    return 0;
}

static int
hwsensor_subdev_close(
        struct v4l2_subdev* sd,
        struct v4l2_subdev_fh* fh)
{
    hwsensor_t* s = NULL;
    struct ion_handle* hdl = NULL;
    hwcam_data_table_t* cfg = NULL;
    HWCAM_CFG_INFO("hwsensor_sbudev close");
    hw_sensor_subdev_internal_close(sd,fh);

    s = SD2Sensor(sd);
    swap(s->cfg_hdl, hdl);
    swap(s->cfg, cfg);
    if (hdl) {
        HWCAM_CFG_ERR("release sensor driver data table! \n");
        hwcam_cfgdev_release_data_table(hdl);
    }

    HWCAM_CFG_INFO("instance(0x%p). \n", s);
    return 0;
}

static long
hwsensor_subdev_get_info(
        hwsensor_t* s,
        hwsensor_info_t* info)
{
    unsigned int index;
    int i=0;
	sensor_t *sensor = NULL;
    if (NULL == s || NULL == info){
        HWCAM_CFG_ERR("s or info is null");
        return -1;
    }
    sensor = I2S(s->intf);
    memset(info->name, 0, DEVICE_NAME_SIZE);
    memcpy(info->name, hwsensor_intf_get_name(s->intf),
            DEVICE_NAME_SIZE - 1);
    info->vcm_enable= sensor->board_info->vcm_enable;

    memset(info->vcm_name, 0, DEVICE_NAME_SIZE);
    if(info->vcm_enable) {
        memcpy(info->vcm_name, sensor->board_info->vcm_name, DEVICE_NAME_SIZE - 1);
    } else {
        memset(info->vcm_name, 0, DEVICE_NAME_SIZE);
    }
    info->dev_id = s->cam_dev_num;
    index = sensor->board_info->sensor_index;
    info->mount_position = (hwsensor_position_kind_t)index;
    info->extisp_type = sensor->board_info->extisp_type;
    info->module_type = sensor->board_info->module_type;
    for (i=0; i<CSI_NUM; i++) {
        info->csi_id[i] = sensor->board_info->csi_id[i];
        info->i2c_id[i] = sensor->board_info->i2c_id[i];
    }
    return 0;
}

static long
hwsensor_subdev_mount_buf(
        hwsensor_t* s,
        hwcam_buf_info_t* bi)
{
    long rc = -EINVAL;
    switch (bi->kind)
    {
    case HWCAM_BUF_KIND_PIPELINE_PARAM:
        if (!s->cfg) {
            s->cfg = hwcam_cfgdev_import_data_table(
                    "sensor_drv_cfg", bi, &s->cfg_hdl);
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
hwsensor_subdev_unmount_buf(
        hwsensor_t* s,
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
hwsensor_subdev_ioctl(
        struct v4l2_subdev *sd,
        unsigned int cmd,
        void *arg)
{
    long rc = -EINVAL;
    hwsensor_t* s = NULL;

    if (NULL == sd) {
        HWCAM_CFG_ERR("sd is NULL \n");
        return -EINVAL;
    }

    s = SD2Sensor(sd);
    cam_debug("hwsensor cmd = %x",cmd);

    switch (cmd)
    {
    case HWSENSOR_IOCTL_GET_INFO:
        rc = hwsensor_subdev_get_info(s, arg);
        break;
    case HWCAM_V4L2_IOCTL_MOUNT_BUF:
        rc = hwsensor_subdev_mount_buf(s, arg);
        break;
    case HWCAM_V4L2_IOCTL_UNMOUNT_BUF:
        rc = hwsensor_subdev_unmount_buf(s, arg);
        break;
    case HWSENSOR_IOCTL_SENSOR_CFG:
     rc = s->intf->vtbl->config(s->intf,arg);
     break;
    default:
        HWCAM_CFG_ERR("invalid IOCTL CMD(%d)! \n", cmd);
        break;
    }
    return rc;
}

static int
hwsensor_power(
        struct v4l2_subdev *sd,
        int on)
{
    return 0;
}

static struct v4l2_subdev_internal_ops
s_subdev_internal_ops_hwsensor =
{
    .open = hwsensor_subdev_open,
    .close = hwsensor_subdev_close,
};

static struct v4l2_subdev_core_ops
s_subdev_core_ops_hwsensor =
{
    .ioctl = hwsensor_subdev_ioctl,
    .s_power = hwsensor_power,
};

static int
hwsensor_v4l2_enum_fmt(
        struct v4l2_subdev* sd,
        unsigned int index,
        enum v4l2_mbus_pixelcode* code)
{
    return 0;
}

static struct v4l2_subdev_video_ops
s_subdev_video_ops_hwsensor =
{
    .enum_mbus_fmt = hwsensor_v4l2_enum_fmt,
};

static struct v4l2_subdev_ops
s_subdev_ops_hwsensor =
{
    .core = &s_subdev_core_ops_hwsensor,
    .video = &s_subdev_video_ops_hwsensor,
};

int
hwsensor_register(
        struct platform_device* pdev,
        hwsensor_intf_t* si)
{
    int rc = 0;

    struct v4l2_subdev* subdev = NULL;
    hwsensor_t* sensor = (hwsensor_t*)kzalloc(
            sizeof(hwsensor_t), GFP_KERNEL);

    if (sensor == NULL) {
        rc = -ENOMEM;
        goto register_fail;
    }

    subdev = &sensor->subdev;
    mutex_init(&sensor->lock);

    v4l2_subdev_init(subdev, &s_subdev_ops_hwsensor);
    subdev->internal_ops = &s_subdev_internal_ops_hwsensor;
    snprintf(subdev->name, sizeof(subdev->name),
            "%s", hwsensor_intf_get_name(si));
    subdev->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
    v4l2_set_subdevdata(subdev, pdev);
    //platform_set_drvdata(pdev, subdev);

    media_entity_init(&subdev->entity, 0, NULL, 0);
    subdev->entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
    subdev->entity.group_id = HWCAM_SUBDEV_SENSOR;
    subdev->entity.name = subdev->name;

    hwcam_cfgdev_register_subdev(subdev);
    subdev->devnode->lock = &sensor->lock;

    hwcam_dev_create(&pdev->dev, &sensor->cam_dev_num);
    sensor->intf = si;
    sensor->pdev = pdev;
    sensor->cfg = NULL;
    sensor->cfg_hdl = NULL;

    if (si->vtbl->sensor_register_attribute)
        rc = si->vtbl->sensor_register_attribute(si, &subdev->devnode->dev);

register_fail:
    return rc;
}

#define Intf2Hwsensor(si) container_of(si, hwsensor_t, intf)
extern void
hwsensor_unregister(hwsensor_intf_t* si)
{
    struct v4l2_subdev* subdev = NULL;
    hwsensor_t* sensor = Intf2Hwsensor(si);

    subdev = &sensor->subdev;
    media_entity_cleanup(&subdev->entity);
    hwcam_cfgdev_unregister_subdev(subdev);

    kzfree(sensor);
}

