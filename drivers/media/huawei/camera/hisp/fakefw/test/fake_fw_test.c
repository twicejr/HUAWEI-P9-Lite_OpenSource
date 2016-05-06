
#define FAKE_FW_TEST_FLAG 0

#if (FAKE_FW_TEST_FLAG)
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/kthread.h>
#include <linux/rpmsg.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/delay.h>

#include <media/huawei/hisp_msg.h>
#include "../../../cam_log.h"
#include "../fake_fw.h"

#define TEST_STREAM_BUFFER_SIZE 50

typedef enum {
	ACQUIRE_CAMERA_RESPONSE_OK = 0x100,
	RELEASE_CAMERA_RESPONSE_OK,
	USECASE_CONFIG_RESPONSE_OK,
	REQUEST_RESPONSE_OK,
	GET_CAP_RESPONSE_OK,
	USE_BUFFER_RESPONSE_OK,
	UNMAP_BUFFER_RESPONSE_OK,
	SET_ISP_REGISTERS_RESPONSE_OK,
	GET_ISP_REGISTER_RESPONSE_OK,
	SET_I2C_REGISTER_RESPONSE_OK,
	GET_I2C_REGISTER_RESPONSE_OK,
	SET_CALIBRATION_DATA_RESPONSE_OK,

	ACQUIRE_CAMERA_RESPONSE_ERROR,
	RELEASE_CAMERA_RESPONSE_ERROR,
	USECASE_CONFIG_RESPONSE_ERROR,
	REQUEST_RESPONSE_ERROR,
	GET_CAP_RESPONSE_ERROR,
	USE_BUFFER_RESPONSE_ERROR,
	UNMAP_BUFFER_RESPONSE_ERROR,
	SET_ISP_REGISTERS_RESPONSE_ERROR,
	GET_ISP_REGISTER_RESPONSE_ERROR,
	SET_I2C_REGISTER_RESPONSE_ERROR,
	GET_I2C_REGISTER_RESPONSE_ERROR,
	SET_CALIBRATION_DATA_RESPONSE_ERROR,
} callback_result_e;

static callback_result_e callback_result;
static unsigned int camera_handle0;
static unsigned int camera_handle1;
static int acquire_id = -1;
static msg_req_usecase_config_t usecase_config0;
static msg_req_usecase_config_t usecase_config1;

struct rpmsg_driver rpmsg_client;

extern int fake_rpmsg_send(struct rpmsg_channel *rpdev, void *data, int len);

extern int fake_fw_unregister_rpmsg_driver(struct rpmsg_driver *rpdrv);

extern int fake_fw_register_rpmsg_driver(struct rpmsg_driver *rpmsg_client);

static void rpmsg_cb(struct rpmsg_channel *rpdev,
		     void *data, int len, void *priv, unsigned int src)
{
	int i = 0;
	hisp_msg_t *msg_call_back = (hisp_msg_t *) data;
	unsigned int camera_handle = 0;
	msg_ack_usecase_config_t *ack_config = NULL;

	switch (msg_call_back->api_name) {
	case ACQUIRE_CAMERA_RESPONSE:
		camera_handle =
		    msg_call_back->u.ack_require_camera.camera_handle;
		if (camera_handle == 0) {
			cam_debug("rpmsg_cb ACQUIRE_CAMERA_REGISTER_ERROR");
			callback_result = ACQUIRE_CAMERA_RESPONSE_ERROR;
		} else {
			cam_debug
			    ("ACQUIRE_CAMERA_RESPONSE OK! handle:0x%x name:%s",
			     camera_handle,
			     msg_call_back->u.ack_require_camera.sensor_name);
			if (acquire_id == 0)
				camera_handle0 = camera_handle;
			else if (acquire_id == 1)
				camera_handle1 = camera_handle;

			callback_result = ACQUIRE_CAMERA_RESPONSE_OK;
		}
		break;
	case RELEASE_CAMERA_RESPONSE:
		if (msg_call_back->u.ack_release_camera.camera_handle == 0) {
			cam_debug("RELEASE_CAMERA_REGISTER_ERROR");
			callback_result = RELEASE_CAMERA_RESPONSE_ERROR;
		} else {
			cam_debug
			    ("RELEASE_CAMERA_RESPONSE OK! handle:0x%x",
			     msg_call_back->u.ack_release_camera.camera_handle);
			callback_result = RELEASE_CAMERA_RESPONSE_OK;
		}
		break;
	case USECASE_CONFIG_RESPONSE:
		if (msg_call_back->u.ack_usecase_config.status == 0) {
			cam_debug("USECASE_CONFIG_RESPONSE OK!");

			ack_config = &msg_call_back->u.ack_usecase_config;

			cam_debug("status:%d stream_nr:%d",
				  ack_config->status, ack_config->stream_nr);

			for (i = 0;
			     i < msg_call_back->u.ack_usecase_config.stream_nr;
			     i++) {
				cam_debug("stream_buf_info[%d]:", i);
				cam_debug("stream id:%d width:%d height:%d format:%d buf_size:%d",
				     ack_config->stream_buf_info[i].stream_id,
				     ack_config->stream_buf_info[i].width,
				     ack_config->stream_buf_info[i].height,
				     ack_config->stream_buf_info[i].format,
				     ack_config->stream_buf_info[i].buf_size);
			}

			callback_result = USECASE_CONFIG_RESPONSE_OK;
		} else {
			cam_debug("rpmsg_cb USECASE_CONFIG_REGISTER_ERROR");
			callback_result = USECASE_CONFIG_RESPONSE_ERROR;
		}
		break;
	case REQUEST_RESPONSE:
		if (msg_call_back->u.ack_request.camera_handle == 0) {
			cam_debug("rpmsg_cb REQUEST_REGISTER_ERROR");
			callback_result = REQUEST_RESPONSE_ERROR;
		} else {
			cam_debug("rpmsg_cb REQUEST_RESPONSE OK! handle:0x%x",
				  msg_call_back->u.ack_request.camera_handle);
			callback_result = REQUEST_RESPONSE_OK;
		}
		break;
	case GET_CAP_RESPONSE:
		if (msg_call_back->u.ack_get_cap.camera_handle == 0) {
			cam_debug("rpmsg_cb GET_CAP_REGISTER_ERROR");
			callback_result = GET_CAP_RESPONSE_ERROR;
		} else {
			cam_debug("rpmsg_cb GET_CAP_RESPONSE OK! handle:0x%x buffer:0x%x",
			     msg_call_back->u.ack_get_cap.camera_handle,
			     msg_call_back->u.ack_get_cap.
			     output_metadata_buffer);
			callback_result = GET_CAP_RESPONSE_OK;
		}
		break;
	case USE_BUFFER_RESPONSE:
		if (msg_call_back->u.ack_use_mem_pool.status != 0) {
			cam_debug("rpmsg_cb USE_BUFFER_REGISTER_ERROR");
			callback_result = USE_BUFFER_RESPONSE_ERROR;
		} else {
			cam_debug
			    ("rpmsg_cb USE_BUFFER_RESPONSE OK! status:0x%x",
			     msg_call_back->u.ack_use_mem_pool.status);
			callback_result = USE_BUFFER_RESPONSE_OK;
		}
		break;
	case UNMAP_BUFFER_RESPONSE:
		if (msg_call_back->u.ack_unmap_buffer.status != 0) {
			cam_debug("rpmsg_cb UNMAP_BUFFER_REGISTER_ERROR");
			callback_result = UNMAP_BUFFER_RESPONSE_ERROR;
		} else {
			cam_debug
			    ("rpmsg_cb UNMAP_BUFFER_RESPONSE OK! status:0x%x",
			     msg_call_back->u.ack_use_mem_pool.status);
			callback_result = UNMAP_BUFFER_RESPONSE_OK;
		}
		break;
	case SET_ISP_REGISTERS_RESPONSE:
		if (msg_call_back->u.ack_set_isp_regs.status != 0) {
			cam_debug("rpmsg_cb SET_ISP_REGISTERS_REGISTER_ERROR");
			callback_result = SET_ISP_REGISTERS_RESPONSE_ERROR;
		} else {
			cam_debug("rpmsg_cb SET_ISP_REGISTERS_RESPONSE OK! status:0x%x",
			     msg_call_back->u.ack_set_isp_regs.status);
			callback_result = SET_ISP_REGISTERS_RESPONSE_OK;
		}
		break;
	case GET_ISP_REGISTER_RESPONSE:
		if (msg_call_back->u.ack_get_isp_regs.status != 0) {
			cam_debug("rpmsg_cb GET_ISP_REGISTERS_REGISTER_ERROR");
			callback_result = GET_ISP_REGISTER_RESPONSE_ERROR;
		} else {
			cam_debug("rpmsg_cb GET_ISP_REGISTERS_RESPONSE OK! status:0x%x",
			     msg_call_back->u.ack_get_isp_regs.status);
			callback_result = GET_ISP_REGISTER_RESPONSE_OK;
		}
		break;
	case SET_I2C_REGISTER_RESPONSE:
		if (msg_call_back->u.ack_set_i2c_regs.status != 0) {
			cam_debug("rpmsg_cb SET_I2C_REGISTER_REGISTER_ERROR");
			callback_result = SET_I2C_REGISTER_RESPONSE_ERROR;
		} else {
			cam_debug("rpmsg_cb SET_I2C_REGISTER_RESPONSE OK! handle:0x%x",
			     msg_call_back->u.ack_set_i2c_regs.status);
			callback_result = SET_I2C_REGISTER_RESPONSE_OK;
		}
		break;
	case GET_I2C_REGISTER_RESPONSE:
		if (msg_call_back->u.ack_get_i2c_regs.status != 0) {
			cam_debug("rpmsg_cb GET_I2C_REGISTERS_REGISTER_ERROR");
			callback_result = GET_I2C_REGISTER_RESPONSE_ERROR;
		} else {
			cam_debug("rpmsg_cb GET_I2C_REGISTERS_RESPONSE OK! status:0x%x",
			     msg_call_back->u.ack_get_i2c_regs.status);
			callback_result = GET_I2C_REGISTER_RESPONSE_OK;
		}
		break;
	case SET_CALIBRATION_DATA_RESPONSE:
		if (msg_call_back->u.ack_set_cal_data.status != 0) {
			cam_debug
			    ("rpmsg_cb SET_CALIBRATION_DATA_REGISTER_ERROR");
			callback_result = SET_CALIBRATION_DATA_RESPONSE_ERROR;
		} else {
			cam_debug("rpmsg_cb SET_CALIBRATION_DATA_RESPONSE OK! status:0x%x",
			     msg_call_back->u.ack_set_cal_data.status);
			callback_result = SET_CALIBRATION_DATA_RESPONSE_OK;
		}
		break;

	default:
		cam_debug("%s apiname(%d) is error",
			  __func__, msg_call_back->api_name);
		break;
	}
}

static int rpmsg_probe(struct rpmsg_channel *rpdev)
{
	int ret = 0;

	cam_debug("rpmsg client driver is probe");

	return ret;
}

static void rpmsg_remove(struct rpmsg_channel *rpdev)
{
	cam_debug("rpmsg client driver is removed");
}

static void acquire_camera(int id, char *name)
{
	hisp_msg_t send_data = { 0 };
	send_data.api_name = COMMAND_ACQUIRE_CAMERA;
	send_data.u.req_acquire_camera.camera_id = id;
	memset(send_data.u.req_acquire_camera.sensor_name, 0, 32);

	if (name) {
		memcpy(send_data.u.req_acquire_camera.sensor_name, name,
		       strlen(name));
	}

	acquire_id = id;
	fake_rpmsg_send(NULL, &send_data, sizeof(hisp_msg_t));
}

static void acquire_camera_test(void)
{
	cam_debug("================begin acquire_camera_test================");

	cam_debug("1:test COMMAND_ACQUIRE_CAMERA 0, name:null");
	callback_result = 0;
	acquire_camera(0, NULL);
	while (callback_result != ACQUIRE_CAMERA_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("2:test COMMAND_ACQUIRE_CAMERA 1, name:null");
	callback_result = 0;
	acquire_camera(1, NULL);
	while (callback_result != ACQUIRE_CAMERA_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("3:test COMMAND_ACQUIRE_CAMERA 0, name:imx214");
	callback_result = 0;
	acquire_camera(0, "imx214");
	while (callback_result != ACQUIRE_CAMERA_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("4:test COMMAND_ACQUIRE_CAMERA 1, name:imx135");
	callback_result = 0;
	acquire_camera(1, "imx135");
	while (callback_result != ACQUIRE_CAMERA_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("5:test COMMAND_ACQUIRE_CAMERA 0, name:imx135");
	callback_result = 0;
	acquire_camera(0, "imx135");
	while (callback_result != ACQUIRE_CAMERA_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("6:test COMMAND_ACQUIRE_CAMERA 1, name:imx214");
	callback_result = 0;
	acquire_camera(1, "imx214");
	while (callback_result != ACQUIRE_CAMERA_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("7:test COMMAND_ACQUIRE_CAMERA 1, name:hello");
	callback_result = 0;
	acquire_camera(1, "hello");
	while (callback_result != ACQUIRE_CAMERA_RESPONSE_ERROR)
		;
	cam_debug("\tpass");
	cam_debug("================end acquire_camera_test================\n");

}

static void release_camera(unsigned int camera_handle)
{
	hisp_msg_t send_data = { 0 };
	send_data.api_name = COMMAND_RELEASE_CAMERA;
	send_data.u.req_release_camera.camera_handle = camera_handle;

	fake_rpmsg_send(NULL, &send_data, sizeof(hisp_msg_t));
}

static void release_camera_test(void)
{
	cam_debug("================begin release_camera_test================");

	cam_debug("1:test COMMAND_RELEASE_CAMERA 0, handle:camera_handle0");
	callback_result = 0;
	release_camera(camera_handle0);
	while (callback_result != RELEASE_CAMERA_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("2:test COMMAND_RELEASE_CAMERA 1, handle:camera_handle1");
	callback_result = 0;
	release_camera(camera_handle1);
	while (callback_result != RELEASE_CAMERA_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("3:test COMMAND_RELEASE_CAMERA, with wrong handle:0x100000");
	callback_result = 0;
	release_camera(0x100000);
	while (callback_result != RELEASE_CAMERA_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("4:test COMMAND_RELEASE_CAMERA, with wrong handle:0x200000");
	callback_result = 0;
	release_camera(0x200000);
	while (callback_result != RELEASE_CAMERA_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("5:test repeat release camera 0, handle:camera_handle0");
	callback_result = 0;
	release_camera(camera_handle0);
	while (callback_result != RELEASE_CAMERA_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("6:test repeat release camera 1, handle:camera_handle1");
	callback_result = 0;
	release_camera(camera_handle1);
	while (callback_result != RELEASE_CAMERA_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug
	    ("7:test repeat acquire/release camera 0, handle:camera_handle0");
	acquire_camera(0, NULL);
	callback_result = 0;
	release_camera(camera_handle0);
	while (callback_result != RELEASE_CAMERA_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug
	    ("8:test repeat acquire/release camera 1, handle:camera_handle0");
	acquire_camera(1, NULL);
	callback_result = 0;
	release_camera(camera_handle1);
	while (callback_result != RELEASE_CAMERA_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("================end release_camera_test================\n");

}

static void usecase_config(msg_req_usecase_config_t *usecase_config)
{
	hisp_msg_t send_data = { 0 };
	send_data.api_name = COMMAND_USECASE_CONFIG;
	send_data.u.req_usecase_config = *(usecase_config);

	if (usecase_config->camera_handle == camera_handle0)
		usecase_config0 = *(usecase_config);
	else if (usecase_config->camera_handle == camera_handle1)
		usecase_config1 = *(usecase_config);

	fake_rpmsg_send(NULL, &send_data, sizeof(hisp_msg_t));
}

static void usecase_config_test(void)
{
	msg_req_usecase_config_t req_usecase_config = { 0 };

	cam_debug("================begin usecase_config_test================");

	cam_debug
	    ("1:test COMMAND_USECASE_CONFIG, handle:camera_handle0 not open");
	callback_result = 0;
	req_usecase_config.camera_handle = camera_handle0;
	usecase_config(&req_usecase_config);
	while (callback_result != USECASE_CONFIG_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug
	    ("2:test COMMAND_USECASE_CONFIG, handle:camera_handle1 not open");
	callback_result = 0;
	req_usecase_config.camera_handle = camera_handle1;
	usecase_config(&req_usecase_config);
	while (callback_result != USECASE_CONFIG_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("3:test COMMAND_USECASE_CONFIG, handle:camera_handle0");
	acquire_camera(0, NULL);
	callback_result = 0;
	req_usecase_config.camera_handle = camera_handle0;
	req_usecase_config.stream_nr = 2;
	req_usecase_config.stream_cfg[0].stream_id = 0;
	req_usecase_config.stream_cfg[0].type = STREAM_TYPE_INPUT;
	req_usecase_config.stream_cfg[0].width = 720;
	req_usecase_config.stream_cfg[0].height = 576;
	req_usecase_config.stream_cfg[0].format = PIX_FMT_RAW;

	req_usecase_config.stream_cfg[1].stream_id = 1;
	req_usecase_config.stream_cfg[1].type = STREAM_TYPE_OUTPUT;
	req_usecase_config.stream_cfg[1].width = 1080;
	req_usecase_config.stream_cfg[1].height = 720;
	req_usecase_config.stream_cfg[1].format = PIX_FMT_JPEG;

	usecase_config(&req_usecase_config);
	while (callback_result != USECASE_CONFIG_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("4:test COMMAND_USECASE_CONFIG, handle:camera_handle1");
	acquire_camera(1, NULL);
	callback_result = 0;
	req_usecase_config.camera_handle = camera_handle1;
	req_usecase_config.stream_nr = 2;
	req_usecase_config.stream_cfg[0].stream_id = 0;
	req_usecase_config.stream_cfg[0].type = STREAM_TYPE_OUTPUT;
	req_usecase_config.stream_cfg[0].width = 720;
	req_usecase_config.stream_cfg[0].height = 576;
	req_usecase_config.stream_cfg[0].format = PIX_FMT_RAW;

	req_usecase_config.stream_cfg[1].stream_id = 1;
	req_usecase_config.stream_cfg[1].type = STREAM_TYPE_OUTPUT;
	req_usecase_config.stream_cfg[1].width = 1080;
	req_usecase_config.stream_cfg[1].height = 720;
	req_usecase_config.stream_cfg[1].format = PIX_FMT_JPEG;
	usecase_config(&req_usecase_config);
	while (callback_result != USECASE_CONFIG_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("================end usecase_config_test================\n");
}

static void request(msg_req_request_t *req_request)
{
	hisp_msg_t send_data = { 0 };
	send_data.api_name = COMMAND_REQUEST;
	send_data.u.req_request = *req_request;

	fake_rpmsg_send(NULL, &send_data, sizeof(hisp_msg_t));
}

static void print_output_buffer(char *output_buffer, int index)
{
	stream_config_t *in_config = NULL;
	stream_config_t *out_config = NULL;
	int size = 0;
	int i = 0;

	cam_debug("after requset, output buffer%d is:", index);
	size = sizeof(stream_config_t);
	in_config = (stream_config_t *) output_buffer;
	out_config = (stream_config_t *) (output_buffer + size);

	cam_debug("%04d,%04d,%04d,%04d,%04d,",
		  in_config->stream_id,
		  in_config->type,
		  in_config->width, in_config->height, in_config->format);

	cam_debug("%04d,%04d,%04d,%04d,%04d,",
		  out_config->stream_id,
		  out_config->type,
		  out_config->width, out_config->height, out_config->format);

	for (i = 0; i < (TEST_STREAM_BUFFER_SIZE - 2 * size); i++)
		cam_debug("%c", *(output_buffer + 2 * size + i));

	cam_debug("");
}

static void request_test(void)
{
	msg_req_usecase_config_t req_usecase_config = { 0 };
	msg_req_request_t req_request = { 0 };
	char *input_buffer = NULL;
	char *output_buffer0 = NULL;
	char *output_buffer1 = NULL;
	int i = 0;

	cam_debug("================begin request_test================");

	cam_debug("1:test COMMAND_REQUEST, handle:camera_handle0 not open");
	callback_result = 0;
	release_camera(camera_handle0);
	req_request.camera_handle = camera_handle0;
	request(&req_request);
	while (callback_result != REQUEST_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("2:test COMMAND_REQUEST, handle:camera_handle1 not open");
	callback_result = 0;
	release_camera(camera_handle1);
	req_request.camera_handle = camera_handle1;
	request(&req_request);
	while (callback_result != REQUEST_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	input_buffer = kmalloc(TEST_STREAM_BUFFER_SIZE, GFP_KERNEL);
	output_buffer0 = kmalloc(TEST_STREAM_BUFFER_SIZE, GFP_KERNEL);
	output_buffer1 = kmalloc(TEST_STREAM_BUFFER_SIZE, GFP_KERNEL);

	if ((!input_buffer) || (!output_buffer0) || (!output_buffer1)) {
		cam_debug("request_test alloc buffer error");
		return;
	}

	cam_debug("3:test COMMAND_REQUEST, camera0, 1 input, 2 output");
	acquire_camera(0, NULL);
	callback_result = 0;
	req_usecase_config.camera_handle = camera_handle0;
	req_usecase_config.stream_nr = 3;
	req_usecase_config.stream_cfg[0].stream_id = 0;
	req_usecase_config.stream_cfg[0].type = STREAM_TYPE_INPUT;
	req_usecase_config.stream_cfg[0].width = 720;
	req_usecase_config.stream_cfg[0].height = 576;
	req_usecase_config.stream_cfg[0].format = PIX_FMT_RAW;

	req_usecase_config.stream_cfg[1].stream_id = 1;
	req_usecase_config.stream_cfg[1].type = STREAM_TYPE_OUTPUT;
	req_usecase_config.stream_cfg[1].width = 1080;
	req_usecase_config.stream_cfg[1].height = 720;
	req_usecase_config.stream_cfg[1].format = PIX_FMT_JPEG;

	req_usecase_config.stream_cfg[2].stream_id = 1;
	req_usecase_config.stream_cfg[2].type = STREAM_TYPE_OUTPUT;
	req_usecase_config.stream_cfg[2].width = 1920;
	req_usecase_config.stream_cfg[2].height = 1080;
	req_usecase_config.stream_cfg[2].format = PIX_FMT_YUV422;
	usecase_config(&req_usecase_config);
	while (callback_result != USECASE_CONFIG_RESPONSE_OK)
		;

	callback_result = 0;

	cam_debug("before requset, input buffer0 is:");
	for (i = 0; i < TEST_STREAM_BUFFER_SIZE; i++) {
		*(input_buffer + i) = 'I';
		cam_debug("%c", *(input_buffer + i));
	}
	cam_debug("");

	memset(output_buffer0, 0, TEST_STREAM_BUFFER_SIZE);

	cam_debug("before requset, output buffer0 is None");
	cam_debug("before requset, output buffer1 is None");

	memset(&req_request, 0, sizeof(req_request));
	req_request.camera_handle = camera_handle0;
	req_request.num_targets = 0x3;
	req_request.target_map = 0x7;
	req_request.buffers[0] = (unsigned int)input_buffer;
	req_request.buffers[1] = (unsigned int)output_buffer0;
	req_request.buffers[2] = (unsigned int)output_buffer1;
	req_request.buffers[3] = 0;
	req_request.buffers[4] = 0;
	req_request.buffers[5] = 0;

	request(&req_request);

	while (callback_result != REQUEST_RESPONSE_OK)
		;

	print_output_buffer(output_buffer0, 0);
	print_output_buffer(output_buffer1, 1);

	cam_debug("\tpass");

	cam_debug("4:test COMMAND_REQUEST, camera0, 0 input, 2 output");
	acquire_camera(0, NULL);
	callback_result = 0;
	if ((!input_buffer) || (!output_buffer0) || (!output_buffer1)) {
		cam_debug("request_test alloc buffer error");
		return;
	}

	cam_debug("before requset, input buffer0 is:");
	for (i = 0; i < TEST_STREAM_BUFFER_SIZE; i++) {
		*(input_buffer + i) = 'I';
		cam_debug("%c", *(input_buffer + i));
	}
	cam_debug("");

	memset(output_buffer0, 0, TEST_STREAM_BUFFER_SIZE);

	cam_debug("before requset, output buffer0 is None");
	cam_debug("before requset, output buffer1 is None");

	memset(&req_request, 0, sizeof(req_request));
	req_request.camera_handle = camera_handle0;
	req_request.num_targets = 0x2;
	req_request.target_map = 0x6;
	req_request.buffers[0] = 0;
	req_request.buffers[1] = (unsigned int)output_buffer0;
	req_request.buffers[2] = (unsigned int)output_buffer1;
	req_request.buffers[3] = 0;
	req_request.buffers[4] = 0;
	req_request.buffers[5] = 0;

	request(&req_request);

	while (callback_result != REQUEST_RESPONSE_OK)
		;

	print_output_buffer(output_buffer0, 0);
	print_output_buffer(output_buffer1, 1);

	cam_debug("\tpass");

	kfree(input_buffer);
	input_buffer = NULL;

	kfree(output_buffer0);
	output_buffer0 = NULL;

	kfree(output_buffer1);
	output_buffer1 = NULL;

	cam_debug("================end request_test================\n");
}

static void get_cap(msg_req_get_cap_t *req_get_cap)
{
	hisp_msg_t send_data = { 0 };
	send_data.api_name = COMMAND_GET_CAP;
	send_data.u.req_get_cap = *req_get_cap;

	fake_rpmsg_send(NULL, &send_data, sizeof(hisp_msg_t));
}

static void get_cap_test(void)
{
	msg_req_get_cap_t req_get_cap = { 0 };

	cam_debug("================begin get_cap_test================");

	cam_debug("1:test COMMAND_GET_CAP, not open handle0");
	release_camera(camera_handle0);
	callback_result = 0;
	req_get_cap.camera_handle = camera_handle0;
	req_get_cap.output_metadata_buffer = 0x12345678;
	get_cap(&req_get_cap);
	while (callback_result != GET_CAP_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("2:test COMMAND_GET_CAP, not open handle1");
	release_camera(camera_handle1);
	callback_result = 0;
	req_get_cap.camera_handle = camera_handle1;
	req_get_cap.output_metadata_buffer = 0x12345678;
	get_cap(&req_get_cap);
	while (callback_result != GET_CAP_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("3:test COMMAND_GET_CAP 0, handle:camera_handle0");
	acquire_camera(0, NULL);
	callback_result = 0;
	req_get_cap.camera_handle = camera_handle0;
	req_get_cap.output_metadata_buffer = 0x12345678;
	get_cap(&req_get_cap);
	while (callback_result != GET_CAP_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("4:test COMMAND_GET_CAP 1, handle:camera_handle1");
	acquire_camera(1, NULL);
	callback_result = 0;
	req_get_cap.camera_handle = camera_handle1;
	req_get_cap.output_metadata_buffer = 0x87654321;
	get_cap(&req_get_cap);
	while (callback_result != GET_CAP_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("================end get_cap_test================\n");
}

static void use_mem_pool(msg_req_use_mem_pool_t *req_use_mem_pool)
{
	hisp_msg_t send_data = { 0 };
	send_data.api_name = COMMAND_USE_BUFFER;
	send_data.u.req_use_mem_pool = *req_use_mem_pool;

	fake_rpmsg_send(NULL, &send_data, sizeof(hisp_msg_t));
}

static void use_mem_pool_test(void)
{
	msg_req_use_mem_pool_t req_use_mem_pool = { 0 };

	cam_debug("================begin use_mem_pool_test================");

	cam_debug("1:test COMMAND_USE_BUFFER, not open handle0");
	release_camera(camera_handle0);
	callback_result = 0;
	req_use_mem_pool.camera_handle = camera_handle0;
	req_use_mem_pool.buffer_size = 0x100;
	req_use_mem_pool.mem_pool_buffer = 0x12345678;
	use_mem_pool(&req_use_mem_pool);
	while (callback_result != USE_BUFFER_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("2:test COMMAND_USE_BUFFER, not open handle1");
	release_camera(camera_handle1);
	callback_result = 0;
	req_use_mem_pool.camera_handle = camera_handle1;
	req_use_mem_pool.buffer_size = 0x20;
	req_use_mem_pool.mem_pool_buffer = 0x87654321;
	use_mem_pool(&req_use_mem_pool);
	while (callback_result != USE_BUFFER_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("3:test COMMAND_USE_BUFFER 0, handle:camera_handle0");
	acquire_camera(0, NULL);
	req_use_mem_pool.camera_handle = camera_handle0;
	req_use_mem_pool.buffer_size = 0x100;
	req_use_mem_pool.mem_pool_buffer = 0x12345678;
	use_mem_pool(&req_use_mem_pool);
	while (callback_result != USE_BUFFER_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("4:test COMMAND_USE_BUFFER 1, handle:camera_handle1");
	acquire_camera(1, NULL);
	callback_result = 0;
	req_use_mem_pool.camera_handle = camera_handle1;
	req_use_mem_pool.buffer_size = 0x20;
	req_use_mem_pool.mem_pool_buffer = 0x87654321;
	use_mem_pool(&req_use_mem_pool);
	while (callback_result != USE_BUFFER_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("================end use_mem_pool_test================\n");

}

static void set_cal_data(msg_req_set_cal_data_t *req_set_cal_data)
{
	hisp_msg_t send_data = { 0 };
	send_data.api_name = COMMAND_CALIBRATION_DATA;
	send_data.u.req_set_cal_data = *req_set_cal_data;

	fake_rpmsg_send(NULL, &send_data, sizeof(hisp_msg_t));
}

static void set_cal_data_test(void)
{
	msg_req_set_cal_data_t req_set_cal_data = { 0 };

	cam_debug("================begin set_cal_data_test================");

	cam_debug("1:test COMMAND_CALIBRATION_DATA, not open handle0");
	release_camera(camera_handle0);
	callback_result = 0;
	req_set_cal_data.camera_handle = camera_handle0;
	req_set_cal_data.buffer_size = 0x100;
	req_set_cal_data.cal_data_buffer = 0x12345678;
	set_cal_data(&req_set_cal_data);
	while (callback_result != SET_CALIBRATION_DATA_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("2:test COMMAND_CALIBRATION_DATA, not open handle1");
	release_camera(camera_handle1);
	callback_result = 0;
	req_set_cal_data.camera_handle = camera_handle1;
	req_set_cal_data.buffer_size = 0x20;
	req_set_cal_data.cal_data_buffer = 0x87654321;
	set_cal_data(&req_set_cal_data);
	while (callback_result != SET_CALIBRATION_DATA_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("3:test COMMAND_CALIBRATION_DATA 0, handle:camera_handle0");
	acquire_camera(0, NULL);
	callback_result = 0;
	req_set_cal_data.camera_handle = camera_handle0;
	req_set_cal_data.buffer_size = 0x100;
	req_set_cal_data.cal_data_buffer = 0x12345678;
	set_cal_data(&req_set_cal_data);
	while (callback_result != SET_CALIBRATION_DATA_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("4:test COMMAND_CALIBRATION_DATA 1, handle:camera_handle1");
	acquire_camera(1, NULL);
	callback_result = 0;
	req_set_cal_data.camera_handle = camera_handle1;
	req_set_cal_data.buffer_size = 0x20;
	req_set_cal_data.cal_data_buffer = 0x87654321;
	set_cal_data(&req_set_cal_data);
	while (callback_result != SET_CALIBRATION_DATA_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("================end set_cal_data_test================\n");
}

static void unmap_buffer(msg_req_unmap_buffer_t *req_unmap_buffer)
{
	hisp_msg_t send_data = { 0 };
	send_data.api_name = COMMAND_UNMAP_BUFFER;
	send_data.u.req_unmap_buffer = *req_unmap_buffer;

	fake_rpmsg_send(NULL, &send_data, sizeof(hisp_msg_t));
}

static void unmap_buffer_test(void)
{
	msg_req_unmap_buffer_t req_unmap_buffer = { 0 };

	cam_debug("================begin unmap_buffer_test================");

	cam_debug("1:test COMMAND_UNMAP_BUFFER, not open handle0");
	release_camera(camera_handle0);
	callback_result = 0;
	req_unmap_buffer.camera_handle = camera_handle0;
	req_unmap_buffer.buffer = 0x12345678;
	unmap_buffer(&req_unmap_buffer);
	while (callback_result != UNMAP_BUFFER_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("2:test COMMAND_UNMAP_BUFFER, not open handle1");
	release_camera(camera_handle1);
	callback_result = 0;
	req_unmap_buffer.camera_handle = camera_handle1;
	req_unmap_buffer.buffer = 0x87654321;
	unmap_buffer(&req_unmap_buffer);
	while (callback_result != UNMAP_BUFFER_RESPONSE_ERROR)
		;
	cam_debug("\tpass");

	cam_debug("3:test COMMAND_UNMAP_BUFFER 0, handle:camera_handle0");
	acquire_camera(0, NULL);
	callback_result = 0;
	req_unmap_buffer.camera_handle = camera_handle0;
	req_unmap_buffer.buffer = 0x12345678;
	unmap_buffer(&req_unmap_buffer);
	while (callback_result != UNMAP_BUFFER_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("4:test COMMAND_UNMAP_BUFFER 1, handle:camera_handle1");
	acquire_camera(1, NULL);
	callback_result = 0;
	req_unmap_buffer.camera_handle = camera_handle1;
	req_unmap_buffer.buffer = 0x87654321;
	unmap_buffer(&req_unmap_buffer);
	while (callback_result != UNMAP_BUFFER_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("================end unmap_buffer_test================\n");
}

static void set_isp_regs(msg_req_set_isp_regs_t *req_set_isp_regs)
{
	hisp_msg_t send_data = { 0 };
	send_data.api_name = COMMAND_SET_ISP_REGISTERS;
	send_data.u.req_set_isp_regs = *req_set_isp_regs;

	fake_rpmsg_send(NULL, &send_data, sizeof(hisp_msg_t));
}

static void set_isp_regs_test(void)
{
	msg_req_set_isp_regs_t req_set_isp_regs = { 0 };

	cam_debug("================begin set_isp_regs_test================");

	cam_debug("1:test COMMAND_SET_ISP_REGISTERS");
	release_camera(camera_handle0);
	callback_result = 0;
	/*do something */
	set_isp_regs(&req_set_isp_regs);
	while (callback_result != SET_ISP_REGISTERS_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("================end set_isp_regs_test================\n");
}

static void get_isp_regs(msg_req_get_isp_regs_t *req_get_isp_regs)
{
	hisp_msg_t send_data = { 0 };
	send_data.api_name = COMMAND_GET_ISP_REGISTER;
	send_data.u.req_get_isp_regs = *req_get_isp_regs;

	fake_rpmsg_send(NULL, &send_data, sizeof(hisp_msg_t));
}

static void get_isp_regs_test(void)
{
	msg_req_get_isp_regs_t req_get_isp_regs = { 0 };

	cam_debug("================begin get_isp_regs_test================");

	cam_debug("1:test COMMAND_GET_ISP_REGISTER");
	release_camera(camera_handle0);
	callback_result = 0;
	/*do something */
	get_isp_regs(&req_get_isp_regs);
	while (callback_result != GET_ISP_REGISTER_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("================end get_isp_regs_test================\n");
}

static void set_i2c_regs(msg_req_set_i2c_regs_t *req_set_i2c_regs)
{
	hisp_msg_t send_data = { 0 };
	send_data.api_name = COMMAND_SET_I2C_REGISTER;
	send_data.u.req_set_i2c_regs = *req_set_i2c_regs;

	fake_rpmsg_send(NULL, &send_data, sizeof(hisp_msg_t));
}

static void set_i2c_regs_test(void)
{
	msg_req_set_i2c_regs_t req_set_i2c_regs = { 0 };

	cam_debug("================begin set_i2c_regs_test================");

	cam_debug("1:test COMMAND_SET_I2C_REGISTER");
	release_camera(camera_handle0);
	callback_result = 0;
	/*do something */
	set_i2c_regs(&req_set_i2c_regs);
	while (callback_result != SET_I2C_REGISTER_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("================end set_i2c_regs_test================\n");
}

static void get_i2c_regs(msg_req_get_i2c_regs_t *req_get_i2c_regs)
{
	hisp_msg_t send_data = { 0 };
	send_data.api_name = COMMAND_GET_I2C_REGISTER;
	send_data.u.req_get_i2c_regs = *req_get_i2c_regs;

	fake_rpmsg_send(NULL, &send_data, sizeof(hisp_msg_t));
}

static void get_i2c_regs_test(void)
{
	msg_req_get_i2c_regs_t req_get_i2c_regs = { 0 };

	cam_debug("================begin get_i2c_regs_test================");

	cam_debug("1:test COMMAND_GET_I2C_REGISTER");
	release_camera(camera_handle0);
	callback_result = 0;
	/*do something */
	get_i2c_regs(&req_get_i2c_regs);
	while (callback_result != GET_I2C_REGISTER_RESPONSE_OK)
		;
	cam_debug("\tpass");

	cam_debug("================end get_i2c_regs_test================\n");
}

static void stress_test(void)
{
	int i = 0;
	cam_debug("================begin stress_test================");

	for (i = 0; i < 20; i++) {
		cam_debug("1 stress_test:%d", i);
		acquire_camera(0, NULL);
		release_camera(camera_handle0);
	}

	ssleep(1);

	for (i = 0; i < 20; i++) {
		cam_debug("2 stress_test:%d", i);
		acquire_camera(0, NULL);
		release_camera(camera_handle0);
	}

	ssleep(1);

	for (i = 0; i < 20; i++) {
		cam_debug("2 stress_test:%d", i);
		acquire_camera(0, NULL);
		release_camera(camera_handle0);
	}

	request_test();

	cam_debug("================end stress_test================");

}

static int __init fake_fw_test_init_module(void)
{
	int ret = 0;

	cam_debug("fake_fw_test_init_module");

	rpmsg_client.probe = rpmsg_probe;
	rpmsg_client.remove = rpmsg_remove;
	rpmsg_client.callback = rpmsg_cb;

	cam_debug("registe_rpmsg_driver");
	fake_fw_register_rpmsg_driver(&rpmsg_client);

	ssleep(3);

	cam_debug("Enter command test");

	acquire_camera_test();
	release_camera_test();
	usecase_config_test();
	request_test();
	get_cap_test();
	use_mem_pool_test();
	unmap_buffer_test();
	set_cal_data_test();
	set_isp_regs_test();
	get_isp_regs_test();
	set_i2c_regs_test();
	get_i2c_regs_test();
	stress_test();

	cam_debug("End command test, All test OK");

	return ret;
}

static void __exit fake_fw_test_exit_module(void)
{
	cam_debug("%s", __func__);
}

module_init(fake_fw_test_init_module);
module_exit(fake_fw_test_exit_module);
MODULE_DESCRIPTION("fake_fw");
MODULE_LICENSE("GPL v2");
#endif
