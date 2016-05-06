

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
#include <media/huawei/hisp_cfg.h>
#include <media/v4l2-event.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-subdev.h>
#include <media/videobuf2-core.h>

#include "hisp_intf.h"
#include "cam_log.h"
#include <dsm/dsm_pub.h>

#define  DSM_DEV_BUFF_SIZE 30000
#define  HwtoHisp(isp_intf) container_of(isp_intf, hisp_t, hw)
#define CREATE_TRACE_POINTS
#include "trace_hisp.h"


static struct dsm_dev dev_hisp = {
	.name = "dsm_hisp",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = NULL,
	.buff_size = DSM_DEV_BUFF_SIZE,
};

static struct dsm_client *client_hisp = NULL;
int hisi_isp_rproc_setpinctl(struct pinctrl *isp_pinctrl, struct pinctrl_state *pinctrl_def, struct pinctrl_state *pinctrl_idle);
int hisi_isp_rproc_setclkdepend(struct clk *aclk_dss, struct clk *pclk_dss);
/**@brief adapt to all Histar ISP
 *
 *When Histar ISP is probed, this sturcture will be initialized,
 *the object will be found will be found by subdev and notify.
 *
 *@end
 */
typedef struct _tag_hisp {
	struct v4l2_subdev subdev;	/*subscribe event to camera daemon */
	struct mutex lock;
	hisp_intf_t *hw;	/*call the specfic Histar ISP implement */
	/*get notification from specfic Histar ISP call back */
	hisp_notify_intf_t notify;
} hisp_t;

#define SD2HISP(sd) container_of(sd, hisp_t, subdev)
#define Notify2HISP(i) container_of(i, hisp_t, notify)

/*Function declaration */
/**********************************************
 *when get call back from rpmsg, notify
 *camera daemon throuth v4l2 event
 *i: hisp_notify_intf_t to find hisp_t object
 *hisp_ev: hisp event with specific rpmsg type
 *********************************************/
static void hisp_notify_rpmsg_cb(hisp_notify_intf_t *i, hisp_event_t *hisp_ev)
{
	hisp_t *isp = NULL;
	struct v4l2_event ev;
	struct video_device *vdev = NULL;
	hisp_event_t *req = (hisp_event_t *) ev.u.data;
	memset(&ev, 0, sizeof(struct v4l2_event));
	cam_debug("enter %s", __func__);
	if (NULL == hisp_ev || NULL == i){
		cam_err("func %s: hisp_ev or i is NULL", __func__);
		return;
	}
	isp = Notify2HISP(i);
	hisp_assert(NULL != isp);
	vdev = isp->subdev.devnode;

	ev.type = HISP_V4L2_EVENT_TYPE;
	ev.id = HISP_HIGH_PRIO_EVENT;

	req->kind = hisp_ev->kind;

	v4l2_event_queue(vdev, &ev);
}

static hisp_notify_vtbl_t s_notify_hisp = {
	.rpmsg_cb = hisp_notify_rpmsg_cb,
};

static void * hisp_subdev_get_info(hisp_t *isp, hisp_info_t *info)
{
	char * name = NULL;
	if (NULL == isp || NULL == info){
		cam_err("func %s: isp or info is NULL",__func__);
		return NULL;
	}
    name = hisp_intf_get_name(isp->hw);
    if(NULL != name){
        memset(info->name, 0, HISP_NAME_SIZE);
        return memcpy(info->name, name, HISP_NAME_SIZE - 1);
    }else{
		cam_err("%s: hisp_intf_get_name() is NULL",__func__);
		return NULL;
	}
}

/*Function declaration */
/**********************************************
 *ioctl function for v4l2 subdev
 *********************************************/
static long
hisp_vo_subdev_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	long rc = 0;
	hisp_msg_t isp_msg;
	size_t len = sizeof(hisp_msg_t);
	hisp_t *isp = NULL;
	memset(&isp_msg, 0, sizeof(hisp_msg_t));
	hisp_assert(NULL != sd);
	if (NULL == arg || NULL == sd){
		cam_err("func %s: arg or sd is NULL",__func__);
		return -1;
	}
	isp = SD2HISP(sd);
	if (NULL == isp){
		cam_err("func %s: isp is NULL",__func__);
		return -1;
	}
	cam_debug("cmd is (0x%x), arg(%p)!\n", cmd, arg);

	switch (cmd) {
	case HISP_IOCTL_CFG_ISP:
		cam_info("Enter HISP_IOCTL_CFG_ISP!\n");
		rc = isp->hw->vtbl->config(isp->hw, arg);
		break;
	case HISP_IOCTL_GET_INFO:
		cam_info("Enter HISP_IOCTL_GET_INFO!\n");
		if(!hisp_subdev_get_info(isp, (hisp_info_t *) arg)) {
			rc = -EFAULT;
			cam_err("func %s, line %d: ret = %ld\n", __func__, __LINE__,
				rc);
		}
		break;
	case HISP_IOCTL_POWER_ON:
		/* cam_info("Enter HISP_IOCTL_POWER_ON!\n"); */
		/* rc = isp->hw->vtbl->power_on(isp->hw); */
		break;
	case HISP_IOCTL_POWER_OFF:
		/* cam_info("Enter HISP_IOCTL_POWER_OFF!\n"); */
		/* rc = isp->hw->vtbl->power_off(isp->hw); */
		break;
	case HISP_IOCTL_SEND_RPMSG:
		cam_debug("Enter HISP_IOCTL_SEND_RPMSG!\n");
		memcpy(&isp_msg, (hisp_msg_t *)arg, len);
		trace_hisp_rpmsg_send(&isp_msg);
		rc = isp->hw->vtbl->send_rpmsg(isp->hw, &isp_msg, len);
		break;
	case HISP_IOCTL_RECV_RPMSG:
		cam_debug("Enter HISP_IOCTL_RECV_RPMSG!\n");
		rc = isp->hw->vtbl->recv_rpmsg(isp->hw, arg, len);
		trace_hisp_rpmsg_recv(arg);
		break;
	default:
		cam_err("invalid IOCTL CMD(0x%x)!\n", cmd);
		rc = -EINVAL;
		break;
	}

	return rc;
}

static int
hisp_subdev_subscribe_event(struct v4l2_subdev *sd,
			    struct v4l2_fh *fh,
			    struct v4l2_event_subscription *sub)
{
	cam_info("enter %s", __func__);
	return v4l2_event_subscribe(fh, sub, 128, NULL);
}

static int
hisp_subdev_unsubscribe_event(struct v4l2_subdev *sd,
			      struct v4l2_fh *fh,
			      struct v4l2_event_subscription *sub)
{
	cam_info("enter %s", __func__);
	return v4l2_event_unsubscribe(fh, sub);
}

static struct v4l2_subdev_core_ops
s_subdev_core_ops_hisp = {
	.ioctl = hisp_vo_subdev_ioctl,
	.subscribe_event = hisp_subdev_subscribe_event,
	.unsubscribe_event = hisp_subdev_unsubscribe_event,
};

static struct v4l2_subdev_ops
s_subdev_ops_hisp = {
	.core = &s_subdev_core_ops_hisp,
};

int hisp_get_dt_data(struct platform_device *pdev, hisp_dt_data_t *dt)
{
	int ret = 0;
	struct device *dev = NULL;
	struct device_node *of_node = NULL;
	int is_fpga = 0;
	const char *clk_name = NULL;
	if (NULL == pdev || NULL == dt) {
		cam_err("%s: pdev or dt is NULL.", __func__);
		return -1;
	}
	dev = &pdev->dev;
	of_node = dev->of_node;

	if (NULL == of_node) {
		cam_err("%s: of node NULL.", __func__);
		return -1;
	}

	ret = of_property_read_u32(of_node, "hisi,is_fpga", &is_fpga);
	if (ret < 0) {
		cam_err("%s: get FPGA flag failed.", __func__);
	}

	if (is_fpga) {
		cam_info("%s: Ignored FPGA.", __func__);
		return 0;
	}

	ret = of_property_read_string_index(of_node, "clock-names", 0, &clk_name);
	cam_info("%s: clk(%s)", __func__, clk_name);
	if (ret < 0) {
		cam_err("%s: could not get aclk name.", __func__);
		goto err_aclk;
	}

	dt->aclk = devm_clk_get(dev, clk_name);
	if (IS_ERR_OR_NULL(dt->aclk)) {
		cam_err("%s: could not get aclk.", __func__);
		ret = PTR_ERR(dt->aclk);
		goto err_aclk;
	}

	ret = of_property_read_string_index(of_node, "clock-names", 1, &clk_name);
	cam_info("%s: clk(%s)", __func__, clk_name);
	if (ret < 0) {
		cam_err("%s: could not get aclk_dss name.", __func__);
		goto err_aclk;
	}

	dt->aclk_dss = devm_clk_get(dev, clk_name);
	if (IS_ERR_OR_NULL(dt->aclk_dss)) {
		cam_err("%s: could not get aclk_dss.", __func__);
		ret = PTR_ERR(dt->aclk_dss);
		goto err_aclk;
	}

	ret = of_property_read_string_index(of_node, "clock-names", 2, &clk_name);
	cam_info("%s: clk(%s)", __func__, clk_name);
	if (ret < 0) {
		cam_err("%s: could not get pclk_dss name.", __func__);
		goto err_aclk;
	}

	dt->pclk_dss = devm_clk_get(dev, clk_name);
	if (IS_ERR_OR_NULL(dt->pclk_dss)) {
		cam_err("%s: could not get pclk_dss.", __func__);
		ret = PTR_ERR(dt->pclk_dss);
		goto err_aclk;
	} else {
		ret = clk_set_rate(dt->pclk_dss, 120000000UL);
		if (ret < 0) {
			cam_err("%s: could not set pclk_dss rate.", __func__);
		}
	}

	dt->pinctrl = devm_pinctrl_get(dev);
	if (IS_ERR_OR_NULL(dt->pinctrl)) {
		cam_err("%s: could not get pinctrl.", __func__);
		ret = PTR_ERR(dt->pinctrl);
		goto err_no_pinctrl;
	}

	dt->pinctrl_default = pinctrl_lookup_state(dt->pinctrl, PINCTRL_STATE_DEFAULT);
	if (IS_ERR_OR_NULL(dt->pinctrl_default)) {
		cam_err("%s: could not get default pinstate.", __func__);
		return -1;
	}

	dt->pinctrl_idle = pinctrl_lookup_state(dt->pinctrl, PINCTRL_STATE_IDLE);
	if (IS_ERR_OR_NULL(dt->pinctrl_idle)) {
		cam_err("%s: could not get idle pinstate.", __func__);
		return -1;
	} else {
		ret = pinctrl_select_state(dt->pinctrl, dt->pinctrl_idle);
		if (ret) {
			cam_err("%s: could not set idle pinstate.", __func__);
			return -1;
		}
	}
	if ( hisi_isp_rproc_setpinctl(dt->pinctrl, dt->pinctrl_default, dt->pinctrl_idle) < 0 ) {
		cam_err("%s Failed: setpinctl.", __func__);
		return -1;
	}

	if ( hisi_isp_rproc_setclkdepend(dt->aclk_dss, dt->pclk_dss) < 0 ) {
		cam_err("%s Failed: clkdepend.", __func__);
		return -1;
	}

	return 0;

err_no_pinctrl:
err_aclk:
	cam_err("%s: failed.", __func__);
	return ret;
}

/*Function declaration */
/**********************************************
 *Initialize the hisp_t structure, called from Histar ISP probe
 *pdev: the rpmsg_channel used in Histar ISP driver
 *hw: to call the hook functions in Histar ISP driver
 *notify: get notified when Histar ISP driver needs
 *********************************************/
int32_t
hisp_register(
	      hisp_intf_t *hw, hisp_notify_intf_t **notify)
{
	int rc = 0;
	struct v4l2_subdev *subdev = NULL;
	hisp_t *isp = NULL;

	cam_notice("%s enter\n", __func__);

	if (NULL == notify){
		cam_err("func %s: notify is NULL",__func__);
		return -1;
	}

	isp = kzalloc(sizeof(hisp_t), GFP_KERNEL);
	if (isp == NULL) {
		rc = -ENOMEM;
		cam_err("func %s, line %d: out of memory!\n", __func__, __LINE__);
		goto alloc_fail;
	}

	//hisp_assert(NULL != pdev);
	hisp_assert(NULL != hw);

	subdev = &isp->subdev;
	mutex_init(&isp->lock);

	v4l2_subdev_init(subdev, &s_subdev_ops_hisp);
	snprintf(subdev->name, sizeof(subdev->name), "hwcam-cfg-hisp");
	subdev->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	subdev->flags |= V4L2_SUBDEV_FL_HAS_EVENTS;
	//v4l2_set_subdevdata(subdev, pdev);

	media_entity_init(&subdev->entity, 0, NULL, 0);
	subdev->entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
	subdev->entity.group_id = HWCAM_SUBDEV_HISP;
	subdev->entity.name = subdev->name;

	hwcam_cfgdev_register_subdev(subdev);
	subdev->devnode->lock = &isp->lock;

	isp->hw = hw;
	isp->notify.vtbl = &s_notify_hisp;
	*notify = &(isp->notify);

	/* register hisp dsm client */
	client_hisp = dsm_register_client(&dev_hisp);

alloc_fail:
	return rc;
}



void
hisp_unregister(hisp_intf_t* isp_intf)
{
    hisp_t* isp = NULL;
    struct v4l2_subdev* subdev = NULL;
    isp = HwtoHisp(isp_intf);
    subdev  = &isp->subdev;
    media_entity_cleanup(&subdev->entity);
    hwcam_cfgdev_unregister_subdev(subdev);
    mutex_destroy(&isp->lock);
    kzfree(isp);
}
