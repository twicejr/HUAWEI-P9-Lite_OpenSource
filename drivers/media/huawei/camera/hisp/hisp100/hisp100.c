 

#include <linux/compiler.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/rpmsg.h>
#include <linux/skbuff.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <media/huawei/camera.h>
#include <media/huawei/hisp_cfg.h>
#include <media/v4l2-event.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-subdev.h>
#include <media/videobuf2-core.h>
#include <linux/pm_qos.h>
#include <clocksource/arm_arch_timer.h>
#include <asm/arch_timer.h>
#include <linux/time.h>
#include <linux/jiffies.h>
#include "cam_log.h"
#include "hisp_intf.h"
#include "platform/sensor_commom.h"
#include <linux/wakelock.h>
#include "trace_hisp.h"


//add for HiLOGE
#include <hisi/hilog.h>
#define HILOG_CAMERA_MODULE_NAME    "Camera"
#define HILOG_CAMERA_SUBMODULE_NAME    "FW_Interaction"

DEFINE_MUTEX(hisi_rpmsg_service_mutex);
DEFINE_MUTEX(hisp_wake_lock_mutex);

static struct pm_qos_request qos_request_ddr_down_record;
static int current_ddr_bandwidth = 0;
static struct wake_lock hisp_power_wakelock;

extern void hisi_isp_boot_stat_dump(void);

typedef enum _timestamp_state_t{
    TIMESTAMP_UNINTIAL = 0,
    TIMESTAMP_INTIAL,
}timestamp_state_t;
static timestamp_state_t s_timestamp_state;
static struct timeval s_timeval;
static u32 s_system_couter_rate;
static u64 s_system_counter;

enum hisp100_rpmsg_state {
	RPMSG_UNCONNECTED,
	RPMSG_CONNECTED,
	RPMSG_FAIL,
};

/*
 *These are used for distinguish the rpmsg_msg status
 *The process in hisp100_rpmsg_ept_cb are different
 *for the first receive and later.
 */
enum {
	HISP_SERV_FIRST_RECV,
	HISP_SERV_NOT_FIRST_RECV,
};

/**@brief the instance for rpmsg service
 *
 *When Histar ISP is probed, this sturcture will be initialized,
 *the object is used to send/recv rpmsg and store the rpmsg data
 *
 *@end
 */
struct rpmsg_hisp100_service {
	struct rpmsg_channel *rpdev;
	struct mutex send_lock;
	struct mutex recv_lock;
	struct completion *comp;
	struct sk_buff_head queue;
	wait_queue_head_t readq;
	struct rpmsg_endpoint *ept;
	u32 dst;
	int state;
	char recv_count;
};

/**@brief the instance to talk to hisp driver
 *
 *When Histar ISP is probed, this sturcture will be initialized,
 *the object is used to notify hisp driver when needed.
 *
 *@end
 */
typedef struct _tag_hisp100 {
	hisp_intf_t intf;
	hisp_notify_intf_t *notify;
	char const *name;
	atomic_t opened;
	struct platform_device*  pdev; //by used to get dts node
	hisp_dt_data_t dt;
} hisp100_t;

struct rpmsg_service_info {
	struct rpmsg_hisp100_service *hisi_isp_serv;
	struct completion isp_comp;
	int isp_minor;
};

/*Store the only rpmsg_hisp100_service pointer to local static rpmsg_local*/
static struct rpmsg_service_info rpmsg_local;
static bool remote_processor_up = false;

#define I2HI(i) container_of(i, hisp100_t, intf)

static void hisp100_notify_rpmsg_cb(void);

char const *hisp100_get_name(hisp_intf_t *i);

static int hisp100_config(hisp_intf_t *i, void *cfg);

static int hisp100_power_on(hisp_intf_t *i);

static int hisp100_power_off(hisp_intf_t *i);

static int hisp100_send_rpmsg(hisp_intf_t *i, hisp_msg_t *m, size_t len);

static int hisp100_recv_rpmsg(hisp_intf_t *i,
				  hisp_msg_t *user_addr, size_t len);

static void hisp100_set_ddrfreq(int ddr_bandwidth);

static void hisp100_release_ddrfreq(void);

static void hisp100_update_ddrfreq(unsigned int ddr_bandwidth);

void hisp100_init_timestamp(void);
void hisp100_destroy_timestamp(void);
void hisp100_set_timestamp(msg_ack_request_t *ack);
void hisp100_handle_msg(hisp_msg_t *msg);

void hisp100_init_timestamp(void)
{
	s_timestamp_state  		= TIMESTAMP_INTIAL;
	s_system_counter  		= arch_counter_get_cntvct();
	s_system_couter_rate 	= arch_timer_get_rate();
	do_gettimeofday(&s_timeval);

	cam_info("%s state=%u system_counter=%llu rate=%u"
		" time_second=%ld time_usecond=%ld size=%lu",
		__func__,
		(unsigned int)s_timestamp_state,
		s_system_counter,
		s_system_couter_rate,
		s_timeval.tv_sec,
		s_timeval.tv_usec,
		sizeof(s_timeval)/sizeof(u32));//FIXME
}

void hisp100_destroy_timestamp(void)
{
	s_timestamp_state		= TIMESTAMP_UNINTIAL;
	s_system_counter 		= 0;
	s_system_couter_rate	= 0;
	memset(&s_timeval, 0x00, sizeof(s_timeval));
}

/*Function declaration */
/**********************************************
 * |-----pow-on------->||<----  fw-SOF ---->|
 *  timeval(got)       ----------------->fw_timeval=?
 *  system_counter(got)----------------->fw_sys_counter(got)
 *
 *  fw_timeval = timeval + (fw_sys_counter - system_counter)
 *
 *With a base position(<timeval, system_counter>, we get it at same time),
 *we can calculate fw_timeval with fw syscounter
 *and deliver it to hal. Hal then gets second and microsecond
 *********************************************/
void hisp100_set_timestamp(msg_ack_request_t *ack)
{
#define NANOSECOND_PER_SECOND 	(1000000000)
#define MICROSECOND_PER_SECOND 	(1000000)
	u64 fw_micro_second = 0;
	u64 fw_sys_counter = 0;
	u64 nano_second = 0;

	if (NULL == ack){
		cam_err("%s err ack is NULL.", __func__);
		return;
	}

	if (TIMESTAMP_UNINTIAL ==  s_timestamp_state){
		cam_err("%s wouldn't enter this branch.\n", __func__);
		hisp100_init_timestamp();
	}

	cam_debug("%s ack_high:0x%x ack_low:0x%x", __func__,
		ack->timestampH, ack->timestampL);

	if (ack->timestampH == 0 && ack->timestampL == 0) {
		return;
	}

	fw_sys_counter = ((u64)ack->timestampH<< 32) | (u64)ack->timestampL;
	nano_second = (fw_sys_counter - s_system_counter) * NANOSECOND_PER_SECOND / s_system_couter_rate;

	//chang nano second to micro second
	fw_micro_second =
	    (nano_second / NANOSECOND_PER_SECOND + s_timeval.tv_sec) * MICROSECOND_PER_SECOND
		+ ((nano_second % NANOSECOND_PER_SECOND) / 1000 + s_timeval.tv_usec);
#if 0
	do_gettimeofday(&s_timeval);
	fw_micro_second= s_timeval.tv_sec * MICROSECOND_PER_SECOND + s_timeval.tv_usec;
#endif

	ack->timestampH = (u32)(fw_micro_second >>32 & 0xFFFFFFFF);
	ack->timestampL = (u32)(fw_micro_second & 0xFFFFFFFF);

	cam_debug("%s h:0x%x l:0x%x", __func__, ack->timestampH, ack->timestampL);
}

void hisp100_handle_msg(hisp_msg_t *msg)
{
	if (NULL == msg)
		return;
	switch (msg->api_name)
	{
		case REQUEST_RESPONSE:
			hisp100_set_timestamp(&(msg->u.ack_request));
			break;

		default:
			break;
	}
}

static hisp_vtbl_t s_vtbl_hisp100 = {
	.get_name = hisp100_get_name,
	.config = hisp100_config,
	.power_on = hisp100_power_on,
	.power_off = hisp100_power_off,
	.send_rpmsg = hisp100_send_rpmsg,
	.recv_rpmsg = hisp100_recv_rpmsg,
};

static hisp100_t s_hisp100 = {
	.intf = {.vtbl = &s_vtbl_hisp100,},
	.name = "hisp100",
};

static void hisp100_notify_rpmsg_cb(void)
{
	hisp_event_t isp_ev;
	isp_ev.kind = HISP_RPMSG_CB;
	cam_debug("%s, %d",__func__,__LINE__);
	hisp_notify_intf_rpmsg_cb(s_hisp100.notify, &isp_ev);
}


/*Function declaration */
/**********************************************
 *Save the rpmsg from isp to locally skb queue.
 *Only called by hisp100_rpmsg_ept_cb when api_name
 *is NOT POWER_REQ, will notify user space through HISP
 *********************************************/
static void hisp100_save_rpmsg_data(void *data, int len)
{
	struct rpmsg_hisp100_service *hisi_serv = rpmsg_local.hisi_isp_serv;
	struct sk_buff *skb = NULL;
	char *skbdata = NULL;

	cam_debug("Enter %s\n", __func__);
	if (NULL == hisi_serv){
		cam_err("func %s: hisi_serv is NULL",__func__);
		return;
	}
	if (NULL == data){
		cam_err("func %s: hisi_serv is NULL",__func__);
		return;
	}

	if (len <= 0){
		cam_err("func %s: len = %d",__func__, len);
		return;
	}

	skb = alloc_skb(len, GFP_KERNEL);
	if (!skb) {
		cam_err("%s() %d failed: alloc_skb len is %u!\n", __func__,
			__LINE__, len);
		return;
	}

	skbdata = skb_put(skb, len);
	memcpy(skbdata, data, len);

	/*add skb to skb queue */
	mutex_lock(&hisi_serv->recv_lock);
	skb_queue_tail(&hisi_serv->queue, skb);
	mutex_unlock(&hisi_serv->recv_lock);

	wake_up_interruptible(&hisi_serv->readq);
	hisp100_notify_rpmsg_cb();

	trace_hisp_rpmsg_notify((hisp_msg_t*)data);
}

/*Function declaration */
/**********************************************
 *Power up CSI/DPHY/sensor according to isp req
 *Only called by hisp100_rpmsg_ept_cb when api_name
 *is POWER_REQ, and will send a POWER_RSP to isp
 *after power request done.
 *********************************************/
#if 0
static void
hisp100_power_req(hisp_msg_t *msg, int len)
{
	struct rpmsg_hisp100_service *hisi_serv = rpmsg_local.hisi_isp_serv;

	cam_info("Enter %s\n", __func__);
	if (NULL == hisi_serv){
		cam_err("func %s: hisi_serv is NULL",__func__);
		return;
	}
	if (NULL == msg){
		cam_err("func %s: msg is NULL",__func__);
		return;
	}
#if 0
	hisp_assert(POWER_REQ == msg->api_name);
	hisp_assert(HISP_SERV_FIRST_RECV != hisi_serv->recv_count);

	switch (msg->u.req_power.power_req_nr) {
		/*TODO: power up csi/DPHY/sensor according to isp req*/
	default:
		cam_info("%s invalid req_power!\n", __func__);
		break;
	}
	msg->api_name = POWER_RSP;
#endif
#ifdef FAKE_FW
	fake_rpmsg_send(hisi_serv->rpdev, (void *)msg, len);
#else
	if (0 != rpmsg_send_offchannel(hisi_serv->rpdev, hisi_serv->ept->addr,
		hisi_serv->dst, (void *)msg, len)){
		cam_err("func %s failed  \n", __func__);
		return;
	}
#endif
	cam_info("%s Not implement yet ....\n", __func__);
}
#endif

static void
hisp100_rpmsg_ept_cb(struct rpmsg_channel *rpdev,
			 void *data, int len, void *priv, u32 src)
{
	struct rpmsg_hisp100_service *hisi_serv = rpmsg_local.hisi_isp_serv;
	hisp_msg_t *msg = NULL;
	struct rpmsg_hdr *rpmsg_msg = NULL;

	cam_debug("Enter %s\n", __func__);
	if (NULL == hisi_serv){
		cam_err("func %s: hisi_serv is NULL",__func__);
		return;
	}
	if (NULL == data){
		cam_err("func %s: data is NULL",__func__);
		return;
	}

	if (len <= 0){
		cam_err("func %s: len = %d",__func__, len);
		return;
	}

	if (RPMSG_CONNECTED != hisi_serv->state) {
		hisp_assert(RPMSG_UNCONNECTED == hisi_serv->state);
		rpmsg_msg = container_of(data, struct rpmsg_hdr, data);
		cam_info("msg src.%u, msg dst.%u\n", rpmsg_msg->src,
			  rpmsg_msg->dst);

		/*add instance dst and modify the instance state */
		hisi_serv->dst = rpmsg_msg->src;
		hisi_serv->state = RPMSG_CONNECTED;
	}

	msg = (hisp_msg_t *) (data);
	trace_hisp_rpmsg_ept_cb(msg);
	/* save the data and wait for hisp100_recv_rpmsg to get the data*/
	hisp100_save_rpmsg_data(data, len);
}

char const *hisp100_get_name(hisp_intf_t *i)
{
	hisp100_t *hi = NULL;
	hisp_assert(NULL != i);
	hi = I2HI(i);
	if (NULL == hi){
		cam_err("func %s: hi is NULL",__func__);
		return NULL;
	}
	return hi->name;
}

static int hisp100_config(hisp_intf_t *i, void *cfg)
{
	int rc = 0;
	hisp100_t *hi = NULL;
	struct hisp_cfg_data *pcfg = NULL;

	if ((NULL == cfg) || (NULL == i)){
		cam_err("func %s: cfg(%p) i(%p)", __func__, cfg, i);
		return -1;
	}
	pcfg = (struct hisp_cfg_data *)cfg;
	hi = I2HI(i);
	if (NULL == hi){
		cam_err("func %s: hi is NULL",__func__);
		return -1;
	}

	switch (pcfg->cfgtype) {
	case HISP_CONFIG_POWER_ON:
		if (!remote_processor_up) {
			cam_notice("%s power on the hisp100.\n", __func__);
			rc = hisp100_power_on(i);
		}
		else{
			cam_warn("%s hisp100 is still on power-on state, power off it.\n",
				__func__);
			rc = hisp100_power_off(i);
			if (0 != rc){
				break;
			}

			cam_warn("%s begin to power on the hisp100.\n", __func__);
			rc = hisp100_power_on(i);
		}
		break;
	case HISP_CONFIG_POWER_OFF:
		if (remote_processor_up) {
			cam_notice("%s power off the hisp100.\n", __func__);
			rc = hisp100_power_off(i);
		}
		break;
	default:
		break;
	}
	return rc;
}

/* TRICY:
 * the chip issue: Need keep dss aclk, pclk enable while ISP is accessing DDRC.
 * Enable dss aclk, pclk before ISP power on, diable them after ISP power off.
 */

static int hisp100_dependent_clock_enable(hisp100_t *hi)
{
	int rc = 0;

	cam_info("%s: enter. Enable dss aclk, pclk.", __func__);

	rc = clk_prepare(hi->dt.aclk_dss);
	if (rc) {
		cam_err("%s: isp aclk_dss prepare failed.", __func__);
	}

	rc = clk_enable(hi->dt.aclk_dss);
	if (rc) {
		cam_err("%s: isp aclk_dss enable failed.", __func__);
	}

	rc = clk_prepare(hi->dt.pclk_dss);
	if (rc) {
		cam_err("%s: isp pclk_dss prepare failed.", __func__);
	}

	rc = clk_enable(hi->dt.pclk_dss);
	if (rc) {
		cam_err("%s: isp pclk_dss enable failed.", __func__);
	}

	return rc;
}

static int hisp100_dependent_clock_disable(hisp100_t *hi)
{
	cam_info("%s: enter. Disable dss aclk, pclk.", __func__);

	clk_disable(hi->dt.pclk_dss);
	clk_unprepare(hi->dt.pclk_dss);

	clk_disable(hi->dt.aclk_dss);
	clk_unprepare(hi->dt.aclk_dss);

	return 0;
}

static int hisp100_power_on(hisp_intf_t *i)
{
	int rc = 0;
	bool rproc_enable = false;
	bool hi_opened = false;
	bool clock_enable = false;
	hisp100_t *hi = NULL;
	unsigned long current_jiffies = jiffies;

	struct rpmsg_hisp100_service *hisi_serv = NULL;
	if (NULL == i){
            HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME, "func %s: i is NULL",__func__);
            return -1;
	}
	hi = I2HI(i);

	cam_info("%s enter ....\n", __func__);

	mutex_lock(&hisp_wake_lock_mutex);
	if (!wake_lock_active(&hisp_power_wakelock)) {
		wake_lock(&hisp_power_wakelock);
		cam_info("%s hisp power on enter, wake lock\n", __func__);
	}
	mutex_unlock(&hisp_wake_lock_mutex);

	mutex_lock(&hisi_rpmsg_service_mutex);
	if (!atomic_read((&hi->opened))) {
		if (!hw_is_fpga_board()) {
				hisp100_dependent_clock_enable(hi);
				clock_enable = true;
				if (!IS_ERR(hi->dt.pinctrl_default)) {
					rc = pinctrl_select_state(hi->dt.pinctrl, hi->dt.pinctrl_default);
					if (0 != rc) {
						HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME, "could not set pins to default state.\n");
						goto FAILED_RET;
					}
				}
		}

		rc = hisi_isp_rproc_enable();
		if (rc != 0) {
			HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME, "Failed: hisi_isp_rproc_enable.%d!\n", rc);
			goto FAILED_RET;
		}
		rproc_enable = true;

		rc  = wait_for_completion_timeout(&channel_sync, msecs_to_jiffies(15000));
		if (0 == rc ) {
			HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME, "Boot failed: wait_for_completion_interruptible_timeout timed out, ret.%d!\n", rc);
			rc = -ETIME;
			hisi_isp_boot_stat_dump();
			goto FAILED_RET;
		}else {
			cam_info("%s() %d after wait completion, rc = %d!\n", __func__, __LINE__, rc);
			rc = 0;
		}
		atomic_inc(&hi->opened);
		hi_opened = true;
	} else {
		cam_notice("%s isp has been opened.\n", __func__);
	}
	remote_processor_up = true;
	hisi_serv = rpmsg_local.hisi_isp_serv;
	if (!hisi_serv) {
		HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME, "failed: hisi_serv does not exist!\n");
		rc = -ENODEV;
		goto FAILED_RET;
	}

	/*assign a new, unique, local address and associate instance with it */
	hisi_serv->ept =
		rpmsg_create_ept(hisi_serv->rpdev, hisp100_rpmsg_ept_cb, hisi_serv,
				 RPMSG_ADDR_ANY);
	if (!hisi_serv->ept) {
		HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME, "failed: create ept!\n");
		hisi_serv->state = RPMSG_FAIL;
		rc = -ENOMEM;
		goto FAILED_RET;
	}
	cam_info("%s() %d hisi_serv->rpdev:src.%d, dst.%d\n",
			__func__, __LINE__,
			hisi_serv->rpdev->src, hisi_serv->rpdev->dst);
	hisi_serv->state = RPMSG_CONNECTED;
	/*set the instance recv_count */
	hisi_serv->recv_count = HISP_SERV_FIRST_RECV;

	hisp100_init_timestamp();
	mutex_unlock(&hisi_rpmsg_service_mutex);
	cam_info("%s exit ,power on time:%d....\n", __func__, jiffies_to_msecs(jiffies - current_jiffies) );
	return rc;

FAILED_RET:
	if(hi_opened){
		atomic_dec(&hi->opened);
	}

	if (rproc_enable) {
		hisi_isp_rproc_disable();
        rproc_set_sync_flag(true);
	}

	if(clock_enable){
		hisp100_dependent_clock_disable(hi);
	}
	remote_processor_up = false;

	mutex_unlock(&hisi_rpmsg_service_mutex);

	mutex_lock(&hisp_wake_lock_mutex);
	if (wake_lock_active(&hisp_power_wakelock)) {
		wake_unlock(&hisp_power_wakelock);
		cam_info("%s hisp power on failed, wake unlock\n", __func__);
	}
	mutex_unlock(&hisp_wake_lock_mutex);
	return rc;
}

static int hisp100_power_off(hisp_intf_t *i)
{
	int rc = 0;
	hisp100_t *hi = NULL;
	unsigned long current_jiffies = jiffies;
	struct rpmsg_hisp100_service *hisi_serv = NULL;
	if (NULL == i){
            HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME, "func %s: i is NULL",__func__);
            return -1;
	}
	hi = I2HI(i);

	cam_info("%s enter ....\n", __func__);

	/*check the remote processor boot flow */
	if (false == remote_processor_up) {
            HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME, "failed: rproc boot failure: BOOT_FAILURE!\n");
            rc = -EPERM;
            goto RET;
	}

	hisi_serv = rpmsg_local.hisi_isp_serv;
	if (!hisi_serv) {
            HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME, "failed: hisi_serv does not exist!\n");
            rc = -ENODEV;
            goto RET;
	}

	if (RPMSG_FAIL == hisi_serv->state) {
            HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME, "failed: hisi_serv->state is RPMSG_FAIL!\n");
            rc = -EFAULT;
            goto RET;
	}

	mutex_lock(&hisi_rpmsg_service_mutex);

	if (!hisi_serv->ept) {
            HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME, "failed: hisi_serv->ept is NULL!\n");
            rc = -ENODEV;
            goto UNLOCK_RET;
	}
	rpmsg_destroy_ept(hisi_serv->ept);

	hisi_serv->state = RPMSG_UNCONNECTED;
	hisi_serv->recv_count = HISP_SERV_FIRST_RECV;

	if (atomic_read((&hi->opened))) {

#if 0
		rc = rpmsg_reset_device();
		if (rc != 0) {
			cam_err("%s() %d failed: rpmsg_reset_device ret is %d!\n", __func__,
					__LINE__, rc);
		}

		/*todo: release resources here */
		/*
		 *If state == fail, remote processor crashed, so don't send it
		 *any message.
		 */
		hisi_rproc_flush();
		hisi_isp_rproc_device_disable();
		//print_rpmsg_vq_msg();
#else
		hisi_isp_rproc_disable();
#endif

		if (!hw_is_fpga_board()) {
			if (!IS_ERR(hi->dt.pinctrl_idle)) {
				rc = pinctrl_select_state(hi->dt.pinctrl, hi->dt.pinctrl_idle);
				if (0 != rc) {
                                HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME, "could not set pins to default state.");
				}
			}

			hisp100_dependent_clock_disable(hi);
		}

		remote_processor_up = false;
		atomic_dec(&hi->opened);
	} else {
		cam_notice("%s isp hasn't been opened.\n", __func__);
	}

	hisp100_destroy_timestamp();
UNLOCK_RET:
	mutex_unlock(&hisi_rpmsg_service_mutex);
RET:

	cam_info("%s exit ,power 0ff time:%d....\n", __func__, jiffies_to_msecs(jiffies - current_jiffies) );

	mutex_lock(&hisp_wake_lock_mutex);
	if (wake_lock_active(&hisp_power_wakelock)) {
		wake_unlock(&hisp_power_wakelock);
		cam_info("%s hisp power off exit, wake unlock\n", __func__);
	}
	mutex_unlock(&hisp_wake_lock_mutex);
	return rc;
}

static void hisp100_rpmsg_remove(struct rpmsg_channel *rpdev)
{
	struct rpmsg_hisp100_service *hisi_serv = dev_get_drvdata(&rpdev->dev);

	cam_info("%s enter ....\n", __func__);

	if(hisi_serv == NULL){
		cam_err("%s: hisi_serv == NULL!", __func__);
		return;
	}

//	mutex_lock(&hisi_rpmsg_service_mutex);
	/*unblock any pending thread */
	//complete(hisi_serv->comp);
	mutex_destroy(&hisi_serv->send_lock);
	mutex_destroy(&hisi_serv->recv_lock);

	kfree(hisi_serv);
	rpmsg_local.hisi_isp_serv = NULL;
//	mutex_unlock(&hisi_rpmsg_service_mutex);
	cam_notice("rpmsg hisi driver is removed\n");
}

static void
hisp100_rpmsg_driver_cb(struct rpmsg_channel *rpdev,
			void *data, int len, void *priv, u32 src)
{
	cam_info("%s enter ....\n", __func__);
	cam_warn("%s() %d uhm, unexpected message!\n", __func__,
		__LINE__);
    if (NULL == data || len <= 0){
        cam_err("%s: data(%p) len(%d)",__func__, data, len);
        return;
    }
	print_hex_dump(KERN_DEBUG, __func__, DUMP_PREFIX_NONE, 16, 1,
			   data, len, true);
}

static int
hisp100_send_rpmsg(hisp_intf_t *i, hisp_msg_t *from_user, size_t len)
{
	int rc = 0;
	hisp100_t *hi = NULL;
	struct rpmsg_hisp100_service *hisi_serv = NULL;
	hisp_msg_t *msg = from_user;
	if ((NULL == i) || (NULL == from_user || (0 >= len))){
		cam_err("func %s: from_user(%p) i(%p) len(%zu)",__func__, from_user, i, len);
		return -1;
	}
	hi = I2HI(i);

	cam_debug("%s enter. api_name(0x%x)\n", __func__, msg->api_name);

	hisi_serv = rpmsg_local.hisi_isp_serv;
	if (!hisi_serv) {
		cam_err("%s() %d failed: hisi_serv does not exist!\n", __func__,
			__LINE__);
		rc = -ENODEV;
		goto RET;
	}

	if (!hisi_serv->ept) {
		cam_err("%s() %d failed:hisi_serv->ept does not exist!\n", __func__,
			__LINE__);
		rc = -ENODEV;
		goto RET;
	}

	mutex_lock(&hisi_serv->send_lock);
	/*if the msg is the first msg, let's treat it special */
	if (RPMSG_CONNECTED != hisi_serv->state) {
		if (!hisi_serv->rpdev) {
			cam_err("%s() %d failed:hisi_serv->rpdev does not exist!\n", __func__,
				__LINE__);
			rc = -ENODEV;
			goto UNLOCK_RET;
		}

		rc = rpmsg_send_offchannel(hisi_serv->rpdev,
					   hisi_serv->ept->addr,
					   hisi_serv->rpdev->dst, (void *)msg,
					   len);
		if (rc) {
			cam_err("%s() %d failed: first rpmsg_send_offchannel ret is %d!\n", __func__,
				__LINE__, rc);
		}
		goto UNLOCK_RET;
	}

	rc = rpmsg_send_offchannel(hisi_serv->rpdev, hisi_serv->ept->addr,
				   hisi_serv->dst, (void *)msg, len);
	if (rc) {
		cam_err("%s() %d failed: rpmsg_send_offchannel ret is %d!\n", __func__,
			__LINE__, rc);
		goto UNLOCK_RET;
	}

UNLOCK_RET:
	mutex_unlock(&hisi_serv->send_lock);
RET:
	return rc;
}

static int
hisp100_recv_rpmsg(hisp_intf_t *i, hisp_msg_t *user_addr, size_t len)
{
	int rc = len;
	hisp100_t *hi = NULL;
	struct rpmsg_hisp100_service *hisi_serv = NULL;
	struct sk_buff *skb = NULL;
	hisp_msg_t *msg = NULL;
	if ((NULL == user_addr) || (NULL == i)){
		cam_err("func %s: user_addr(%p) i(%p)",__func__,user_addr, i);
		return -1;
	}
	hi = I2HI(i);

	cam_debug("%s enter. \n", __func__);

	hisi_serv = rpmsg_local.hisi_isp_serv;
	if (!hisi_serv) {
		cam_err("%s() %d failed: hisi_serv does not exist!\n", __func__,
			__LINE__);
		rc = -ENODEV;
		goto RET;
	}

	if (HISP_SERV_FIRST_RECV == hisi_serv->recv_count) {
		hisi_serv->recv_count = HISP_SERV_NOT_FIRST_RECV;
	}

	if (mutex_lock_interruptible(&hisi_serv->recv_lock)) {
		cam_err("%s() %d failed: mutex_lock_interruptible!\n", __func__,
			__LINE__);
		rc = -ERESTARTSYS;
		goto RET;
	}

	if (RPMSG_CONNECTED != hisi_serv->state) {
		cam_err("%s() %d hisi_serv->state != RPMSG_CONNECTED!\n",
			__func__, __LINE__);
		rc = -ENOTCONN;
		goto UNLOCK_RET;
	}

	/*nothing to read ? */
	/*check if skb_queue is NULL ? */
	if (skb_queue_empty(&hisi_serv->queue)) {
		mutex_unlock(&hisi_serv->recv_lock);
		cam_err("%s() %d skb_queue is empty!\n", __func__, __LINE__);

		/*otherwise block, and wait for data */
		if (wait_event_interruptible_timeout(hisi_serv->readq,
						 (!skb_queue_empty
						  (&hisi_serv->queue)
						  || hisi_serv->state ==
						  RPMSG_FAIL),
						  HISP_WAIT_TIMEOUT)) { //lint !e666
			cam_err("%s() %d hisi_serv->state = %d!\n", __func__,
			__LINE__, hisi_serv->state);
			rc = -ERESTARTSYS;
			goto RET;
		}

		if (mutex_lock_interruptible(&hisi_serv->recv_lock)) {
			cam_err("%s() %d failed: mutex_lock_interruptible!\n",
				__func__, __LINE__);
			rc = -ERESTARTSYS;
			goto RET;
		}
	}

	if (RPMSG_FAIL == hisi_serv->state) {
		cam_err("%s() %d state = RPMSG_FAIL!\n", __func__, __LINE__);
		rc = -ENXIO;
		goto UNLOCK_RET;
	}

	skb = skb_dequeue(&hisi_serv->queue);
	if (!skb) {
		cam_err("%s() %d skb is NULL!\n", __func__, __LINE__);
		rc = -EIO;
		goto UNLOCK_RET;
	}

	rc = min((unsigned int)len, skb->len);
	msg = (hisp_msg_t *) (skb->data);

	cam_debug("%s: api_name(0x%x)\n", __func__, msg->api_name);

	hisp100_handle_msg(msg);
	if (!memcpy(user_addr, msg, rc)) {
		rc = -EFAULT;
		cam_err("Fail: %s()%d ret = %d\n", __func__, __LINE__, rc);
	}
	kfree_skb(skb);

UNLOCK_RET:
	mutex_unlock(&hisi_serv->recv_lock);
RET:
	return rc;
}

static void hisp100_set_ddrfreq(int ddr_bandwidth)
{
	cam_info("%s enter,ddr_bandwidth:%d\n",__func__,ddr_bandwidth);
	qos_request_ddr_down_record.pm_qos_class = 0;
	pm_qos_add_request(&qos_request_ddr_down_record,PM_QOS_MEMORY_THROUGHPUT , ddr_bandwidth);
	current_ddr_bandwidth = ddr_bandwidth;
}

static void hisp100_release_ddrfreq(void)
{
	cam_info("%s enter\n",__func__);
	if(current_ddr_bandwidth == 0)
		return;
	pm_qos_remove_request(&qos_request_ddr_down_record);
	current_ddr_bandwidth = 0;
}

static void hisp100_update_ddrfreq(unsigned int ddr_bandwidth)
{
	cam_info("%s enter,ddr_bandwidth:%u\n",__func__,ddr_bandwidth);
	if(!atomic_read(&s_hisp100.opened)){
		cam_info("%s ,cam is not opened,so u can not set ddr bandwidth\n",__func__);
		return;
	}

	if(current_ddr_bandwidth == 0){
		hisp100_set_ddrfreq(ddr_bandwidth);
	}else if(current_ddr_bandwidth > 0){
		pm_qos_update_request(&qos_request_ddr_down_record, ddr_bandwidth);
		current_ddr_bandwidth = ddr_bandwidth;
	}else{
		cam_err("%s,current_ddr_bandwidth is invalid\n",__func__);
	}
}

static ssize_t hisp_ddr_freq_ctrl_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
	cam_info("enter %s,current_ddr_bandwidth:%d\n", __func__, current_ddr_bandwidth);

	return snprintf(buf, PAGE_SIZE, "%d\n", current_ddr_bandwidth);
}

static ssize_t hisp_ddr_freq_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int ddr_bandwidth = 0;
	if (buf == NULL) {
		cam_err("%s,input buffer is invalid\n",__func__);
		return -EINVAL;
	}

	ddr_bandwidth = simple_strtol(buf, NULL, 10);
	cam_info("%s enter,ddr_bandwidth:%d\n", __func__, ddr_bandwidth);

	if (ddr_bandwidth < 0){
		cam_err("%s,ddr_bandwidth is invalid\n",__func__);
		return -EINVAL;
	}else if (ddr_bandwidth == 0) {
		hisp100_release_ddrfreq();
	}else if (ddr_bandwidth > 0) {
		hisp100_update_ddrfreq(ddr_bandwidth);
	}

	return count;
}


static int32_t hisp100_rpmsg_probe(struct rpmsg_channel *rpdev)
{
	int32_t ret = 0;
	struct rpmsg_hisp100_service *hisi_serv = NULL;
	cam_notice("%s enter\n", __func__);

	if (NULL != rpmsg_local.hisi_isp_serv) {
		cam_notice("%s hisi_serv is already up!\n", __func__);
		goto SERVER_UP;
	}

	hisi_serv = kzalloc(sizeof(*hisi_serv), GFP_KERNEL);
	if (!hisi_serv) {
		cam_err("%s() %d kzalloc failed!\n", __func__, __LINE__);
		ret = -ENOMEM;
		goto ERROR_RET;
	}
	mutex_init(&hisi_serv->send_lock);
	mutex_init(&hisi_serv->recv_lock);
	skb_queue_head_init(&hisi_serv->queue);
	init_waitqueue_head(&hisi_serv->readq);
	hisi_serv->ept = NULL;
	hisi_serv->comp = &rpmsg_local.isp_comp;

	rpmsg_local.hisi_isp_serv = hisi_serv;
SERVER_UP:
	if (NULL == hisi_serv){
		cam_err("func %s: hisi_serv is NULL",__func__);
		return -1;
	}
	hisi_serv->rpdev = rpdev;
	hisi_serv->state = RPMSG_UNCONNECTED;
	dev_set_drvdata(&rpdev->dev, hisi_serv);

	complete(hisi_serv->comp);

	cam_info("new HISI connection srv channel: %u -> %u!\n",
						rpdev->src, rpdev->dst);
ERROR_RET:
	return ret;
}

static struct rpmsg_device_id rpmsg_hisp100_id_table[] = {
	{.name = "rpmsg-hisi"},
	{},
};

MODULE_DEVICE_TABLE(platform, rpmsg_hisp100_id_table);

static const struct of_device_id s_hisp100_dt_match[] = {
	{
	 .compatible = "huawei,hisi_isp100",
	 .data = &s_hisp100.intf,
	 },
	{
	 },
};

MODULE_DEVICE_TABLE(of, s_hisp100_dt_match);

static struct rpmsg_driver rpmsg_hisp100_driver = {
	.id_table = rpmsg_hisp100_id_table,
	.probe = hisp100_rpmsg_probe,
	.callback = hisp100_rpmsg_driver_cb,
	.remove = hisp100_rpmsg_remove,
};


static struct device_attribute hisp_ddr_freq_ctrl_attr =
    __ATTR(ddr_freq_ctrl, 0664, hisp_ddr_freq_ctrl_show, hisp_ddr_freq_store);

static int32_t
hisp100_platform_probe(
	struct platform_device* pdev)
{
	int32_t ret = 0;

	cam_info("%s: enter", __func__);
	wake_lock_init(&hisp_power_wakelock, WAKE_LOCK_SUSPEND, "hisp_power_wakelock");

	ret = hisp_get_dt_data(pdev, &s_hisp100.dt);
	if (ret < 0) {
		cam_err("%s: get dt failed.", __func__);
		goto error;
	}

	init_completion(&rpmsg_local.isp_comp);
	ret = hisp_register(&s_hisp100.intf, &s_hisp100.notify);
	if (0 == ret) {
		atomic_set(&s_hisp100.opened, 0);
	} else {
		cam_err("%s() %d hisp_register failed with ret %d!\n", __func__, __LINE__, ret);
		goto error;
	}

	rpmsg_local.hisi_isp_serv = NULL;

	ret = register_rpmsg_driver(&rpmsg_hisp100_driver);
	if (0 != ret){
		cam_err("%s() %d register_rpmsg_driver failed with ret %d!\n", __func__, __LINE__, ret);
		hisp_unregister(&s_hisp100.intf);
		goto error;
	}

    s_hisp100.pdev = pdev;

#ifdef DEBUG_HISI_CAMERA
	ret = device_create_file(&pdev->dev, &hisp_ddr_freq_ctrl_attr);
	if (ret < 0) {
		cam_err("%s failed to creat hisp ddr freq ctrl attribute.", __func__);
		unregister_rpmsg_driver(&rpmsg_hisp100_driver);
		hisp_unregister(&s_hisp100.intf);
		goto error;
	}
#endif
	return 0;

error:
	wake_lock_destroy(&hisp_power_wakelock);
	cam_notice("%s exit with ret = %d\n", __func__, ret);
	return ret;
}

static struct platform_driver
s_hisp100_driver =
{
	.probe = hisp100_platform_probe,
	.driver =
	{
		.name = "huawei,hisi_isp100",
		.owner = THIS_MODULE,
		.of_match_table = s_hisp100_dt_match,
	},
};

static int __init
hisp100_init_module(void)
{
	cam_notice("%s enter\n", __func__);
	return platform_driver_register(&s_hisp100_driver);
}

static void __exit
hisp100_exit_module(void)
{
	cam_notice("%s enter\n", __func__);
	unregister_rpmsg_driver(&rpmsg_hisp100_driver);
	hisp_unregister(&s_hisp100.intf);
	platform_driver_unregister(&s_hisp100_driver);
	wake_lock_destroy(&hisp_power_wakelock);
}

module_init(hisp100_init_module);
module_exit(hisp100_exit_module);
MODULE_DESCRIPTION("hisp100 driver");
MODULE_LICENSE("GPL v2");
