

#include <linux/module.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/kthread.h>
#include <linux/rpmsg.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#include <media/huawei/hisp_msg.h>
#include "../../cam_log.h"
#include "fake_fw.h"

/* Maximum number of receive buffers at once */
#define MSG_RECEIVE_MAX_BUFF  30

/* Value of camera handle */
#define CAMERA_HANDLE_START   100

/*
 * Module parameters
 */

typedef struct _tag_fake_fw {
	fake_fw_intf_t intf;
	struct task_struct *thread;
	struct rpmsg_driver rpmsg;
	struct rpmsg_channel rpdev;
	struct mutex num_lock;
	wait_queue_head_t done_wq;
	int msg_num;
	hisp_msg_t *msg_base;
	hisp_msg_t *msg_read;
	hisp_msg_t *msg_write;
} fake_fw_t;

static fake_fw_t s_fake_fw;

/*
 * Current camera informations.
 */

fake_fw_camera_info_t fake_fw_camera_info[] = {
	{
	 .handle = 0,
	 .camera_id = 0,
	 .sensor_name = "imx214",
	 .status = CAMERA_CLOSED,
	 .usecase_config = {0},
	 },
	{
	 .handle = 0,
	 .camera_id = 1,
	 .sensor_name = "imx179",
	 .status = CAMERA_CLOSED,
	 .usecase_config = {0},
	 },
};

/*
 * Open the camera.
 * @isp_msg: hisp message of open parameters.
 *
 * If input sensor_name of req_release_camera isn't empty,
 * then driver campare input sensor_name with camera informations.
 * else driver copy sensor_name of camera informations to input sensor_name.
 */

static int fake_fw_acquire_camera(hisp_msg_t *isp_msg)
{
	int ret = 0;
	int i = 0;
	int cmp = 0;
	int len;
	hisp_msg_t isp_msg_ack;
	int name_len = strlen(isp_msg->u.req_acquire_camera.sensor_name);

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = ACQUIRE_CAMERA_RESPONSE;
	isp_msg_ack.u.ack_require_camera.camera_handle = 0;

	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		/*
		 * Try to find matched camera name
		 * from current camera informations.
		 */
		cmp = strcmp(fake_fw_camera_info[i].sensor_name,
				(isp_msg->u.req_acquire_camera.sensor_name));

		if ((isp_msg->u.req_acquire_camera.cam_id ==
				fake_fw_camera_info[i].camera_id) &&
			((0 == name_len) || (0 == cmp))) {

			isp_msg_ack.u.ack_require_camera.camera_handle
				= fake_fw_camera_info[i].handle;
			fake_fw_camera_info[i].status = CAMERA_OPENED;
			len = strlen(fake_fw_camera_info[i].sensor_name);
			strncpy(isp_msg_ack.u.ack_require_camera.sensor_name,
				fake_fw_camera_info[i].sensor_name,
				len+1);

			cam_info("%s , camera id:%u name:%s,save_name=%s. api_name = %d", __func__,
			isp_msg->u.req_acquire_camera.cam_id,
			isp_msg->u.req_acquire_camera.sensor_name,
			isp_msg_ack.u.ack_require_camera.sensor_name,
			isp_msg_ack.api_name);

			break;
		}
	}

	if (0 == isp_msg_ack.u.ack_require_camera.camera_handle) {
		cam_err("%s error, camera id:%u name:%s", __func__,
			isp_msg->u.req_acquire_camera.cam_id,
			isp_msg->u.req_acquire_camera.sensor_name);
	}

	/* Act upon a hisp driver notification */
	s_fake_fw.rpmsg.callback(
					&s_fake_fw.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t),
					NULL,
					0);
	return ret;
}

/*
 * Close the camera.
 * @isp_msg: hisp message of close parameters.
 */

static int fake_fw_release_camera(hisp_msg_t *isp_msg)
{
	int i = 0;
	int ret = 0;
	int index = -1;
	hisp_msg_t isp_msg_ack;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = RELEASE_CAMERA_RESPONSE;
	isp_msg_ack.u.ack_release_camera.camera_handle = 0;

	/*
	 * Try to find matched camera handle
	 * from current camera informations.
	 */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		if (isp_msg->u.req_release_camera.camera_handle ==
			fake_fw_camera_info[i].handle) {

			index = i;
			break;
		}
	}

	if (index >= 0) {
		if (fake_fw_camera_info[index].status == CAMERA_OPENED) {
			fake_fw_camera_info[index].status = CAMERA_CLOSED;
			isp_msg_ack.u.ack_release_camera.camera_handle
				= fake_fw_camera_info[index].handle;
		} else {
			cam_err("%s error, camera handle:0x%x not opened.",
				__func__,
				isp_msg->u.req_release_camera.camera_handle);
		}
	} else {
		cam_err("%s error, camera handle:0x%x not index.",
			__func__, isp_msg->u.req_release_camera.camera_handle);
	}

	/* Act upon a hisp driver notification */
	s_fake_fw.rpmsg.callback(
					&s_fake_fw.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t),
					NULL,
					0);
	return ret;
}

/*
 * Calculate stream buffer size
 */

static unsigned int get_stream_buffer_size(unsigned int width,
							unsigned int height,
							unsigned int format)
{
	unsigned int size = 0;
	cam_debug("%s(%u)", __func__, __LINE__);

	switch (format) {
	/* Raw stream buffer size*/
	case PIXEL_FMT_RAW:
		size = width * height * 2;
		break;
	/* Jpeg stream buffer size*/
	case PIXEL_FMT_JPEG:
		size = ((width * height * 3) >> 1);
		break;
	/* YUV422 stream buffer size*/
	case PIXEL_FMT_YUV422:
		size = width * height * 2;
		break;
	/* YUV420_NV12 stream buffer size*/
	case PIXEL_FMT_YUV420_NV12:
		size = ((width * height * 3) >> 1);
		break;
	/* YUV420_NV21 stream buffer size*/
	case PIXEL_FMT_YUV420_NV21:
		size = ((width * height * 3) >> 1);
		break;
	default:
		size = 0;
		break;
	}

	return size;
}

/*
 * usecase config buffers.
 * @isp_msg: hisp message of usecase config parameters.
 */

static int fake_fw_usecase_config(hisp_msg_t *isp_msg)
{
#ifdef PORTING_L
	return 0;
#else
	int ret = 0;
	int i = 0;
	int index = -1;
	hisp_msg_t isp_msg_ack;
	stream_buf_info_t *buf_info = NULL;
	stream_config_t *stream_cfg = NULL;
	msg_ack_usecase_config_t *config = NULL;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = USECASE_CONFIG_RESPONSE;
	config = &(isp_msg_ack.u.ack_usecase_config);
	config->status = -1;

	/*
	 * Try to find matched camera handle
	 * from current camera informations.
	 */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		if (isp_msg->u.req_usecase_config.camera_handle ==
			fake_fw_camera_info[i].handle) {
			index = i;
			break;
		}
	}

	if (index >= 0) {
		/* Packet ack usecase config parameters. */
		if (fake_fw_camera_info[index].status == CAMERA_OPENED) {
			fake_fw_camera_info[index].usecase_config =
				isp_msg->u.req_usecase_config;
			config->status = 0;
			config->stream_nr =
				isp_msg->u.req_usecase_config.stream_nr;

			buf_info = config->stream_buf_info;
			stream_cfg =
				isp_msg->u.req_usecase_config.stream_cfg;

			cam_debug("%s,stream_nr:%u",
				__func__, config->stream_nr);

			/* Packet stream buffer information. */
			for (i = 0; i < config->stream_nr; i++) {
				buf_info[i].stream_id = stream_cfg[i].stream_id;
				buf_info[i].width = stream_cfg[i].width;
				buf_info[i].height = stream_cfg[i].height;
				buf_info[i].format = stream_cfg[i].format;
				buf_info[i].stride = 0;

				/* Get stream buffer size */
				buf_info[i].buf_size =
					get_stream_buffer_size(
							buf_info[i].width,
							buf_info[i].height,
							buf_info[i].format);
			}
		} else {
			cam_err("%s error, camera handle:0x%x not opened.",
				__func__,
				isp_msg->u.req_usecase_config.camera_handle);
		}
	} else {
		cam_err("%s error, camera handle:0x%x not index.",
			__func__, isp_msg->u.req_usecase_config.camera_handle);
	}

	/* Act upon a hisp driver notification */
	s_fake_fw.rpmsg.callback(
					&s_fake_fw.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t),
					NULL,
					0);

	cam_debug("exit %s(%u)", __func__, __LINE__);
	return ret;
#endif
}

/*
 * Fill output buffer.
 * @in_addr   : address of input buffer.
 * @in_config : config of input buffer.
 * @out_addr  : address of output buffer.
 * @out_config: config of output buffer.
 */

static int fill_output_buffer(unsigned long in_addr,
				 stream_config_t *in_config,
				 unsigned long out_addr,
				 stream_config_t *out_config)
{
	int ret = 0;
	cam_debug("enter %s(%u)", __func__, __LINE__);

	/*
	 * The buffer address is actually a physical buffer,
	 * so driver won't be able to write it directly.
	 * Do nothing in driver for now.
	 */
#if 0
	int size = 50;

	if (in_addr > 0) {
		memcpy(out_addr, in_addr, size);
		memcpy(out_addr, in_config, sizeof(stream_config_t));
		memcpy((stream_config_t *)
			((unsigned long)out_addr + sizeof(stream_config_t)),
			  out_config, sizeof(stream_config_t));
	} else {
		memset(out_addr, 0, size);
		memcpy((stream_config_t *)
			((unsigned long)out_addr + sizeof(stream_config_t)),
			out_config, sizeof(stream_config_t));
	}
#endif

	cam_debug("exit %s(%u)", __func__, __LINE__);

	return ret;
}

/*
 * Request buffers.
 * @isp_msg: hisp message of request parameters.
 */

static int fake_fw_request(hisp_msg_t *isp_msg)
{
#ifdef PORTING_L
	return 0;
#else
	int ret = 0;
	int i = 0;
	int index = -1;
	unsigned long input_addr = 0;
	unsigned long output_addr = 0;
	stream_config_t *intput_config = NULL;
	stream_config_t *output_config = NULL;
	msg_req_usecase_config_t *usecase_config = NULL;

	hisp_msg_t isp_msg_ack;
	msg_ack_request_t *ack_req = &isp_msg_ack.u.ack_request;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = REQUEST_RESPONSE;

	ack_req->camera_handle = 0;
	ack_req->frame_number = isp_msg->u.ack_request.frame_number;
	ack_req->output_metadata_buffer =
		isp_msg->u.req_request.output_metadata_buffer;

	/*
	 * Try to find matched camera handle
	 * from current camera informations.
	 */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		if (isp_msg->u.req_request.camera_handle ==
			fake_fw_camera_info[i].handle) {
			index = i;
			break;
		}
	}

	usecase_config = &(fake_fw_camera_info[index].usecase_config);

	if (index >= 0) {
		if (fake_fw_camera_info[index].status == CAMERA_CLOSED) {
			cam_err("%s error, camera handle:0x%x not opened.",
				__func__,
				isp_msg->u.req_release_camera.camera_handle);
			goto out;
		}

		cam_debug("%s,stream_nr:%u target_map:0x%x",
			__func__, usecase_config->stream_nr,
			isp_msg->u.req_request.target_map);

		/*
		 * Try to find input stream buffer
		 * from request parameters.
		 */
		for (i = 0; i < usecase_config->stream_nr; i++) {
			cam_debug("%s,request[%u] type:%u",
				__func__,
				i,
				usecase_config->stream_cfg[i].type);

			/* Find input stream buffer and get address.*/
			if ((usecase_config->stream_cfg[i].type
					== STREAM_TYPE_INPUT)
				&& ((isp_msg->u.req_request.target_map >> i)
					& 0x1)) {

				input_addr = isp_msg->u.req_request.buffers[i];

				if (0 == input_addr ) {
					ack_req->camera_handle = 0;
					cam_alert
						("%s error, read buffer:0",
						__func__);
					goto out;
				}

				intput_config =
					&(usecase_config->stream_cfg[i]);
				break;
			}
		}

		ack_req->num_targets = 0;
		ack_req->target_map = 0;

		cam_debug("%s,stream_nr:%u",
			__func__, usecase_config->stream_nr);

		/*
		 * Try to find output stream buffer from request parameters.
		 * Then fill output buffers.
		 */
		for (i = 0; i < usecase_config->stream_nr; i++) {
			if ((usecase_config->stream_cfg[i].type ==
					STREAM_TYPE_OUTPUT)
				&& ((isp_msg->u.req_request.target_map >> i) &
					0x1)) {

				output_addr = isp_msg->u.req_request.buffers[i];

				if (0 == output_addr ) {
					ack_req->camera_handle = 0;
					cam_alert("%s error, read buffer:0",
						__func__);
					goto out;
				}

				output_config =
					&(usecase_config->stream_cfg[i]);
				ack_req->num_targets++;
				ack_req->target_map |= (0x1 << i);
				fill_output_buffer(
							input_addr,
							intput_config,
							output_addr,
							output_config);
			}
		}

		cam_debug("%s,num_targets:%u target_map:%u", __func__,
			ack_req->num_targets,
			ack_req->target_map);

		ack_req->camera_handle =
			fake_fw_camera_info[index].handle;

	} else {
		cam_err("%s error, camera handle:0x%x not index.",
			__func__, isp_msg->u.req_release_camera.camera_handle);
	}

out:
	cam_debug("%s, num_targets:%u, target_map:0x%x", __func__,
		ack_req->num_targets,
		ack_req->target_map);

	/* Act upon a hisp driver notification */
	s_fake_fw.rpmsg.callback(
					&s_fake_fw.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t),
					NULL,
					0);
	return ret;
#endif
}

static int fake_req_get_cap(hisp_msg_t *isp_msg)
{

#ifdef PORTING_L
	return 0;
#else
	int ret = 0;
	int i = 0;
	int index = -1;
	hisp_msg_t isp_msg_ack;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = GET_CAP_RESPONSE;

	isp_msg_ack.u.ack_get_cap.camera_handle = 0;

	/*
	 * Try to find matched camera handle
	 * from current camera informations.
	 */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		if (isp_msg->u.req_get_cap.camera_handle ==
			fake_fw_camera_info[i].handle) {
			index = i;
			break;
		}
	}

	if (index >= 0) {
		if (fake_fw_camera_info[index].status == CAMERA_OPENED) {

			/* Do something. */

			isp_msg_ack.u.ack_get_cap.camera_handle
				= fake_fw_camera_info[index].handle;
			isp_msg_ack.u.ack_get_cap.output_metadata_buffer
				= isp_msg_ack.u.req_get_cap.output_metadata_buffer;
		} else {
			cam_err("%s error, camera handle:0x%x not opened.",
				__func__, isp_msg->u.req_get_cap.camera_handle);
		}
	} else {
		cam_err("%s error, camera handle:0x%x not index.",
			__func__, isp_msg->u.req_get_cap.camera_handle);
	}

	/* Act upon a hisp driver notification */
	s_fake_fw.rpmsg.callback(
					&s_fake_fw.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t),
					NULL,
					0);
	return ret;
#endif
}

static int fake_fw_use_mem_pool(hisp_msg_t *isp_msg)
{
	int ret = 0;
	int i = 0;
	int index = -1;
	hisp_msg_t isp_msg_ack;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = MAP_BUFFER_RESPONSE;

	isp_msg_ack.u.ack_map_buffer.status = -1;

	/*
	 * Try to find matched camera handle
	 * from current camera informations.
	 */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		if (isp_msg->u.req_map_buffer.camera_handle ==
			fake_fw_camera_info[i].handle) {
			index = i;
			break;
		}
	}
#ifdef PORTING_L
		return 0;
#else
	if (index >= 0) {
		if (fake_fw_camera_info[index].status == CAMERA_OPENED) {

			/* Do something. */

			isp_msg_ack.u.ack_use_mem_pool.status = 0;
		} else {
			cam_err("%s error, camera handle:0x%x not opened.",
				__func__, isp_msg->u.req_get_cap.camera_handle);
		}
	} else {
		cam_err("%s error, camera handle:0x%x not index.",
			__func__, isp_msg->u.req_get_cap.camera_handle);
	}
#endif
	/* Act upon a hisp driver notification */
	s_fake_fw.rpmsg.callback(
					&s_fake_fw.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t),
					NULL,
					0);
	return ret;
}

static int fake_fw_set_cal_data(hisp_msg_t *isp_msg)
{
#if 0

	int ret = 0;
	int i = 0;
	int index = -1;
	hisp_msg_t isp_msg_ack;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = SET_CALIBRATION_DATA_RESPONSE;

	isp_msg_ack.u.ack_set_cal_data.status = -1;

	/*
	 * Try to find matched camera handle
	 * from current camera informations.
	 */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		if (isp_msg->u.req_set_cal_data.camera_handle ==
			fake_fw_camera_info[i].handle) {
			index = i;
			break;
		}
	}

	if (index >= 0) {
		if (fake_fw_camera_info[index].status == CAMERA_OPENED) {

			/* Do something */

			isp_msg_ack.u.ack_set_cal_data.status = 0;
		} else {
			cam_err("%s error, camera handle:0x%x not opened.",
				__func__,
				isp_msg->u.req_set_cal_data.camera_handle);
		}
	} else {
		cam_err("%s error, camera handle:0x%x not index.", __func__,
			isp_msg->u.req_set_cal_data.camera_handle);
	}

	/* Act upon a hisp driver notification */
	s_fake_fw.rpmsg.callback(
					&s_fake_fw.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t),
					NULL,
					0);
	return ret;
#endif
    return 0;
}

static int fake_fw_unmap_buffer(hisp_msg_t *isp_msg)
{
	int ret = 0;
	int i = 0;
	int index = -1;
	hisp_msg_t isp_msg_ack;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = UNMAP_BUFFER_RESPONSE;

	isp_msg_ack.u.ack_unmap_buffer.status = -1;

	/*
	 * Try to find matched camera handle
	 * from current camera informations.
	 */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		if (isp_msg->u.req_unmap_buffer.camera_handle ==
			fake_fw_camera_info[i].handle) {
			index = i;
			break;
		}
	}

	if (index >= 0) {
		if (fake_fw_camera_info[index].status == CAMERA_OPENED) {

			/* Do something. */

			isp_msg_ack.u.ack_unmap_buffer.status = 0;
		} else {
			cam_err("%s error, camera handle:0x%x not opened.",
				__func__,
				isp_msg->u.req_unmap_buffer.camera_handle);
		}
	} else {
		cam_err("%s error, camera handle:0x%x not index.",
			__func__, isp_msg->u.req_unmap_buffer.camera_handle);
	}

	/* Act upon a hisp driver notification */
	s_fake_fw.rpmsg.callback(
					&s_fake_fw.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t),
					NULL,
					0);
	return ret;
}

static int fake_fw_set_isp_regs(hisp_msg_t *isp_msg)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = SET_ISP_REGISTERS_RESPONSE;

	isp_msg_ack.u.ack_set_isp_regs.status = 0;

	/* Do something. */

	/* Act upon a hisp driver notification */
	s_fake_fw.rpmsg.callback(
					&s_fake_fw.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t),
					NULL,
					0);
	return ret;
}

static int fake_fw_get_isp_regs(hisp_msg_t *isp_msg)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = GET_ISP_REGISTER_RESPONSE;

	isp_msg_ack.u.ack_get_isp_regs.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	s_fake_fw.rpmsg.callback(
					&s_fake_fw.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t),
					NULL,
					0);
	return ret;
}

static int fake_fw_set_i2c_regs(hisp_msg_t *isp_msg)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = SET_IIC_REGISTER_RESPONSE;

	isp_msg_ack.u.ack_set_i2c_regs.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	s_fake_fw.rpmsg.callback(
					&s_fake_fw.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t),
					NULL,
					0);
	return ret;
}

static int fake_fw_get_i2c_regs(hisp_msg_t *isp_msg)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = GET_IIC_REGISTER_RESPONSE;

	isp_msg_ack.u.ack_get_i2c_regs.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	s_fake_fw.rpmsg.callback(
					&s_fake_fw.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t),
					NULL,
					0);
	return ret;
}

static int fake_fw_msg_event(hisp_msg_t *isp_msg)
{
	int ret = 0;

	return ret;
}

static int fake_fw_msg_log(hisp_msg_t *isp_msg)
{
	int ret = 0;

	return ret;
}

struct rpmsg_endpoint *fake_fw_rpmsg_create_ept(struct rpmsg_channel *rpdev,
						rpmsg_rx_cb_t cb, void *priv, u32 addr)
{
	struct rpmsg_endpoint *ept;
	ept = kzalloc(sizeof(*ept), GFP_KERNEL);
	if (!ept) {
		cam_err("%s() failed to kzalloc a new ept\n", __func__);
		return NULL;
	}
	ept->cb = cb;
	ept->rpdev = rpdev;
	ept->priv = priv;
/*	ept->addr = addr;*/
	s_fake_fw.rpmsg.callback = cb;
cam_info("%s() ept is %p", __func__, ept);
	return ept;
}
EXPORT_SYMBOL(fake_fw_rpmsg_create_ept);

void fake_fw_rpmsg_destroy_ept(struct rpmsg_endpoint *ept)
{
	if (!ept) {
		cam_err("%s() destroy a NULL ept\n", __func__);
		return;
	}
cam_info("%s() ept is %p", __func__, ept);
	s_fake_fw.rpmsg.callback = NULL;
	//ept->cb = NULL;
	kfree(ept);
	return;
}
EXPORT_SYMBOL(fake_fw_rpmsg_destroy_ept);

int fake_fw_rproc_device_enable(void)
{
	if (s_fake_fw.rpmsg.probe)
		s_fake_fw.rpmsg.probe(&s_fake_fw.rpdev);
	return 0;
}
EXPORT_SYMBOL(fake_fw_rproc_device_enable);

int fake_fw_rproc_device_disable(void)
{
	if (s_fake_fw.rpmsg.remove)
		s_fake_fw.rpmsg.remove(&s_fake_fw.rpdev);
	return 0;
}
EXPORT_SYMBOL(fake_fw_rproc_device_disable);

/* Register fake firmware driver */
int fake_fw_register_rpmsg_driver(struct rpmsg_driver *rpmsg_client)
{
	int ret = 0;
	cam_debug("%s enter", __func__);

	if (NULL == rpmsg_client)
		return -1;

	s_fake_fw.rpmsg = *rpmsg_client;

/*	if (s_fake_fw.rpmsg.probe)
		s_fake_fw.rpmsg.probe(&s_fake_fw.rpdev);*/

	cam_debug("%s exit", __func__);

	return ret;
}
EXPORT_SYMBOL(fake_fw_register_rpmsg_driver);

/* Unregister fake firmware driver */
int fake_fw_unregister_rpmsg_driver(struct rpmsg_driver *rpdrv)
{
	int ret = 0;
	cam_debug("%s enter", __func__);

	if (s_fake_fw.rpmsg.remove)
		s_fake_fw.rpmsg.remove(&s_fake_fw.rpdev);

	memset(&s_fake_fw.rpmsg, 0, sizeof(struct rpmsg_driver));

	cam_debug("%s exit", __func__);

	return ret;
}
EXPORT_SYMBOL(fake_fw_unregister_rpmsg_driver);

/*
 * Cyclical Buffer for rpmsg.
 *
 *    __           max _____            max _____
 * /\   |  /\         |_/_/_|_read         |_____|_write
 * ||   |  ||         |_____|              |_/_/_|
 * ||   |  ||  .      |_____|              |_/_/_|
 * ||   |  ||  .      |_____|              |_/_/_|
 * ||   |  ||  .      |_____|              |_/_/_|
 * ||   |  ||         |_____|_write        |_/_/_|_read
 * ||   |__||         |_/_/_|              |_____|
 * buffer          min                  min
 * read/write      read > write.        write > read.
 * direction
 *
 *
 * max _____                            max _____
 *    |_____|                              |_/_/_|
 *    |_____|                              |_/_/_|
 *    |_____|                              |_/_/_|
 *    |_____|                              |_/_/_|
 *    |_____|_write                        |_/_/_|_read
 *    |_____|_read                         |_/_/_|_write
 *    |_____|                              |_/_/_|
 * min                                  min
 * write = read + 1,                    read = write + 1,
 * after read,                          after write,
 * buffer is empty.                     buffer is full.
 *
 *  _____                                _____
 * |_/_/_| used buffer                  |_____| free buffer
 */

int fake_rpmsg_send(struct rpmsg_channel *rpdev, void *data, int len)
{
	int ret = 0;

	cam_debug("%s fw_api_name = %u", __func__,
		  ((hisp_msg_t *) data)->api_name);

	mutex_lock(&s_fake_fw.num_lock);

	if (s_fake_fw.msg_write == s_fake_fw.msg_base + MSG_RECEIVE_MAX_BUFF)
		s_fake_fw.msg_write = s_fake_fw.msg_base;

	if (s_fake_fw.msg_write == s_fake_fw.msg_read) {
		ret = -1;
		cam_err("msg buffer is overflow,write:0x%p read:0x%p",
			s_fake_fw.msg_write, s_fake_fw.msg_read);
	} else {
		memcpy(s_fake_fw.msg_write,
			data,
			sizeof(hisp_msg_t));
		/*
		 * s_fake_fw.msg_num > 0 is condition of
		 * fake firmware thread wakeup.
		 * We flag this condition for now and generate the event later.
		 */
		s_fake_fw.msg_num++;
		s_fake_fw.msg_write++;

		/* Wake up the sleep thread on the Tx msg */
		wake_up_interruptible(&s_fake_fw.done_wq);
	}

	mutex_unlock(&s_fake_fw.num_lock);

	cam_debug("%s exit", __func__);
	return ret;
}
EXPORT_SYMBOL(fake_rpmsg_send);

/*
 * Fake firmware thread .
 * Wake up the sleep thread on fake_rpmsg_send.
 */
static int fake_fw_thread(void *data)
{
	fake_fw_msg_pro_t *pro = NULL;

	while (!kthread_should_stop()) {

		/* Wait for any transmission to end */
		wait_event_interruptible(s_fake_fw.done_wq,
					 s_fake_fw.msg_num > 0);

		mutex_lock(&s_fake_fw.num_lock);
		s_fake_fw.msg_num--;
		mutex_unlock(&s_fake_fw.num_lock);

		if (NULL == s_fake_fw.msg_read) {
			s_fake_fw.msg_read = s_fake_fw.msg_base;
		} else {
			s_fake_fw.msg_read++;

			if (s_fake_fw.msg_read ==
				(s_fake_fw.msg_base + MSG_RECEIVE_MAX_BUFF)) {
				s_fake_fw.msg_read = s_fake_fw.msg_base;
			}
		}

		pro = s_fake_fw.intf.msg_pro;
		//msleep(25);
		msleep(1000);

		/* Receive hisp message */
		switch (s_fake_fw.msg_read->api_name) {
		case COMMAND_ACQUIRE_CAMERA:
			pro->acquire_camera(s_fake_fw.msg_read);
			break;
		case COMMAND_RELEASE_CAMERA:
			pro->release_camera(s_fake_fw.msg_read);
			break;
		case COMMAND_USECASE_CONFIG:
			pro->usecase_config(s_fake_fw.msg_read);
			break;
		case COMMAND_REQUEST:
			pro->request(s_fake_fw.msg_read);
			break;
#ifndef PORTING_L
		case COMMAND_GET_CAP:
			pro->req_get_cap(s_fake_fw.msg_read);
			break;
#endif
		case COMMAND_MAP_BUFFER:
			pro->use_mem_pool(s_fake_fw.msg_read);
			break;
		case COMMAND_CALIBRATION_DATA:
			pro->set_cal_data(s_fake_fw.msg_read);
			break;
		case COMMAND_UNMAP_BUFFER:
			pro->unmap_buffer(s_fake_fw.msg_read);
			break;
		case COMMAND_SET_ISP_REGISTERS:
			pro->set_isp_regs(s_fake_fw.msg_read);
			break;
		case COMMAND_GET_ISP_REGISTER:
			pro->get_isp_regs(s_fake_fw.msg_read);
			break;
		case COMMAND_SET_IIC_REGISTER:
			pro->set_i2c_regs(s_fake_fw.msg_read);
			break;
		case COMMAND_GET_IIC_REGISTER:
			pro->get_i2c_regs(s_fake_fw.msg_read);
			break;
		default:
			cam_err("%s apiname(%u) is error",
				__func__, s_fake_fw.msg_read->api_name);
			break;
		}
	}

	return 0;
}

/*
 *	fake_fw_platform_probe - attach a platform interface
 */

static int32_t fake_fw_platform_probe(void)
{
	int i;
	hisp_msg_t *buffbase = NULL;

	cam_notice("enter %s", __func__);
	s_fake_fw.msg_base = NULL;
	s_fake_fw.msg_base =
	    kmalloc(sizeof(hisp_msg_t) * MSG_RECEIVE_MAX_BUFF, GFP_KERNEL);

	if (NULL == s_fake_fw.msg_base) {
		cam_alert("%s(%d) kmalloc failed.", __func__, __LINE__);
		return -1;
	}

	buffbase = s_fake_fw.msg_base;

	s_fake_fw.msg_num = 0;
	s_fake_fw.msg_write = buffbase;
	s_fake_fw.msg_read = NULL;

	mutex_init(&s_fake_fw.num_lock);

	init_waitqueue_head(&s_fake_fw.done_wq);

	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++)
		fake_fw_camera_info[i].handle = CAMERA_HANDLE_START + i;

	s_fake_fw.thread = kthread_run(fake_fw_thread, NULL, "fake firmware");
	return 0;
}

/*
 * Hisp message processor.
 */

static fake_fw_msg_pro_t s_fake_fw_msg_pro = {
	.acquire_camera = fake_fw_acquire_camera,
	.release_camera = fake_fw_release_camera,
	.usecase_config = fake_fw_usecase_config,
	.request = fake_fw_request,
	.req_get_cap = fake_req_get_cap,
	.use_mem_pool = fake_fw_use_mem_pool,
	.set_cal_data = fake_fw_set_cal_data,
	.unmap_buffer = fake_fw_unmap_buffer,
	.set_isp_regs = fake_fw_set_isp_regs,
	.get_isp_regs = fake_fw_get_isp_regs,
	.set_i2c_regs = fake_fw_set_i2c_regs,
	.get_i2c_regs = fake_fw_get_i2c_regs,
	.msg_event = fake_fw_msg_event,
	.msg_log = fake_fw_msg_log,
};

static fake_fw_t s_fake_fw = {
	.intf = {.msg_pro = &s_fake_fw_msg_pro,},
	.thread = NULL,
	.rpmsg = {},
	.rpdev = {},
	.num_lock = {},
	.done_wq = {},
	.msg_num = 0,
	.msg_base = NULL,
	.msg_read = NULL,
	.msg_write = NULL,
};

static int __init fake_fw_init_module(void)
{
	cam_notice("enter %s", __func__);
	return fake_fw_platform_probe();
}

static void __exit fake_fw_exit_module(void)
{
	cam_notice("exit %s", __func__);

	kthread_stop(s_fake_fw.thread);
	s_fake_fw.thread = (struct task_struct *)NULL;

	mutex_destroy(&s_fake_fw.num_lock);

	kfree(s_fake_fw.msg_base);
	s_fake_fw.msg_base = NULL;
}

module_init(fake_fw_init_module);
module_exit(fake_fw_exit_module);
MODULE_DESCRIPTION("fake_fw");
MODULE_LICENSE("GPL v2");
