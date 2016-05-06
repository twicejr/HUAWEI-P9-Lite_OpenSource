


#include <linux/compiler.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/ctype.h>
#include <linux/videodev2.h>
#include <media/huawei/camera.h>
#include <media/v4l2-event.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-subdev.h>
#include <media/videobuf2-core.h>

#include "hwcam_intf.h"
#include "../hwdepthisp.h"
#include "hw_pmic.h"
#include "depthisp.h"
#include "cam_log.h"
#include "sensor_commom.h"


enum {
	ALD2_PIPE_0 = 0,
	ALD2_PIPE_1 = 1,
	ALD2_PIPE_DUAL = 2,
	ALD2_PIPE_MAX = 3,
};

enum ald2_pipe_test_stage {
	ALD2_PIPE_UNTESTED = 0,
	ALD2_PIPE_TESTING = 1,
	ALD2_PIPE_TEST_CMD_ERR = 2,
	ALD2_PIPE_GET_CMD_ERR = 3,
	ALD2_PIPE_TEST_BAD = 4,
	ALD2_PIPE_TEST_DONE = 5,
	ALD2_PIPE_TEST_MAX = 6,
};


typedef struct _tag_ald2
{
    char 				name[32];
    hwdepthisp_intf_t                  intf;
    hwdepthisp_notify_intf_t*          notify;
} ald2_t;

#define I2A(i) container_of(i, ald2_t, intf)


static ald2_t s_ald2;

static uint32_t disp_cmd_filter = 0;

static int ocram_test = 0;
static int ocram_result = 0xFF;

void ald2_notify_error( uint32_t id);

int ald2_power_on(const hwdepthisp_intf_t* i)
{
    return disp_init();
}

int ald2_power_off(const hwdepthisp_intf_t* i)
{
    return disp_exit();
}

int ald2_load_firmware(const hwdepthisp_intf_t* i, hwdepthisp_config_data_t *data)
{
	int ret = 0;
	u8 *ext_buf = NULL;
	u32 ext_len = 0;

	cam_info("enter %s fw_type=%d", __func__, data->cmd);

	/*Ocram test mode only load OcramBoot*/
	if (ocram_test) {
		if(DEPTHISP_FW_BASIC == data->cmd) {
			return disp_load_ocram_boot();
		}
		return ret;
	}

	/* allocate kernel buffer for ext calibration data */
	if (data->ext_buf.user_buf_ptr) {
		ext_len = data->ext_buf.user_buf_len;
		if (ext_len > 0 && ext_len < (20*1024)) {
			ext_buf = vmalloc(ext_len);
			if (NULL == ext_buf) {
				cam_err("%s vmalloc failed", __func__);
				return -ENOMEM;
			}
			if (copy_from_user(ext_buf, data->ext_buf.user_buf_ptr, ext_len)) {
				cam_err("%s copy user failed", __func__);
				vfree(ext_buf);
				return -EFAULT;
			}
		} else {
			cam_err("%s invalid ext_buf_len=%d", __func__, ext_len);
			return -EINVAL;
		}
	}

	switch (data->cmd) {
		case DEPTHISP_FW_BASIC:
			ret = disp_load_fw();
			if (0 != ret) {
				disp_flush_reg();
			}
			break;
		case DEPTHISP_FW_SCENARIO_TAB:
		case DEPTHISP_FW_CALIBRATION_OTP:
		case DEPTHISP_FW_CALIBRATION_PACK:
			/*DBC test must not to load Calibrations*/
			if(0 == disp_cmd_filter) {
				ret = disp_load_calibration_data(data->cmd, ext_buf, ext_len);
			}
			break;
		default:
			cam_err("%s invalid tpye:%d", __func__, data->cmd);
			break;
	}

	/* reclaimed kernel bufffer */
	if (ext_buf) {
		vfree(ext_buf);
	}

	return ret;
}

int ald2_matchid(const hwdepthisp_intf_t* i, hwdepthisp_config_data_t *data)
{
	int rc = 0;
	cam_info("enter %s", __func__);

	data->depthisp_type = disp_get_chipid();
	cam_info("%s depthisp_type %d", __func__, data->depthisp_type);
	return rc;
}

extern unsigned int get_boot_into_recovery_flag(void);
int ald2_exec_cmd(const hwdepthisp_intf_t* i, hwdepthisp_config_data_t *data)
{
	int rc = 0;
	u8 *in_buf = NULL, *out_buf = NULL;
	u32 opcode, dir_type, block_response, out_len, in_len, bulk_len;
	bool out_to_block, out_from_block;

	if (get_boot_into_recovery_flag()||(disp_cmd_filter==1)) {
		cam_info("%s cmd=0x%x is blocked", __func__, data->cmd);
		return 0;
	}

	dir_type = (data->cmd & DEPTHISP_CMD_DIR_FLAG_MASK)>>DEPTHISP_CMD_DIR_FLAG_SHIT;
	block_response = (data->cmd & DEPTHISP_CMD_RESP_FLAG_MASK)>>DEPTHISP_CMD_RESP_FLAG_SHIT;
	out_len = (data->cmd & DEPTHISP_CMD_OUT_LEN_MASK)>>DEPTHISP_CMD_OUT_LEN_SHIT;
	in_len = (data->cmd & DEPTHISP_CMD_IN_LEN_MASK)>>DEPTHISP_CMD_IN_LEN_SHIT;
	opcode = (data->cmd & DEPTHISP_CMD_OPCODE_MASK)>>DEPTHISP_CMD_OPCODE_SHIT;
	cam_info("%s :dir_type %d, block_response %d, out_len %d, in_len %d, opcode %x ", __func__, dir_type, block_response, out_len, in_len, opcode);
	out_buf = in_buf = data->u.buf;
	out_to_block = (DEPTHISP_BLOCK_RESPONSE_CMD == block_response)? true : false;
	out_from_block = (DEPTHISP_BLOCK_WRITE_CMD == block_response) ? true : false;

	/* allocate kernel buf: override out_buf out_len*/
	if (out_to_block) {
		out_len = data->ext_buf.user_buf_len;
		if (out_len > 4096) {
			cam_err("%s invalid ext_buf_len=%d", __func__, out_len);
			return -EINVAL;
		}
		out_buf = kmalloc(out_len, GFP_KERNEL);
		if (NULL == out_buf) {
			cam_err("%s kmalloc failed", __func__);
			return -ENOMEM;
		}
	} else if (out_from_block) {
		bulk_len = data->ext_buf.user_buf_len;
		out_buf = kmalloc(bulk_len, GFP_KERNEL);
		if (NULL == out_buf) {
			cam_err("%s kmalloc failed", __func__);
			return -ENOMEM;
		}
		if (copy_from_user(out_buf, data->ext_buf.user_buf_ptr, bulk_len)) {
			cam_err("%s copy from user failed", __func__);
			kfree(out_buf);
			out_buf = NULL;
			return -EFAULT;
		}
	}

	if (DEPTHISP_INOUT_CMD == dir_type) {
		if (out_from_block) {
			rc = disp_exec_write_block_res((u16)opcode, in_buf, in_len, out_to_block, out_buf, bulk_len, out_len);
		} else {
			rc = disp_exec_bidir_cmd((u16)opcode, data->u.buf, in_len, out_to_block, out_buf, out_len);
		}
	} else if (DEPTHISP_SET_CMD == dir_type) {
		if (out_from_block) {
			rc = disp_exec_write_block((u16)opcode, in_buf, in_len, out_buf, bulk_len);
		} else {
			rc = disp_exec_unidir_cmd((u16)opcode, true, out_to_block, in_buf, in_len);
		}
	} else if (DEPTHISP_GET_CMD == dir_type) {
		rc = disp_exec_unidir_cmd((u16)opcode, false, out_to_block, out_buf, out_len);
	} else {
		cam_err("%s unkown cmd direction", __func__);
		rc = -EINVAL;
	}

	/* reclaimed kernel buf*/
	if (out_to_block) {
		if (copy_to_user(data->ext_buf.user_buf_ptr, out_buf, out_len)) {
			cam_err("%s copy to user failed", __func__);
			rc = -EFAULT;
		}
	}

	if (out_buf) {
		kfree(out_buf);
		out_buf = NULL;
	}

	return rc;
}


/*
maybe used later
static char *test_raw_buf[ALD2_PIPE_MAX][33];
*/
static int   test_result[ALD2_PIPE_MAX];
#define set_test_result(pipe, result) \
	do { \
		test_result[pipe] = result;\
	} while(0)

static const char *test_report[ALD2_PIPE_TEST_MAX] =
{
	[ALD2_PIPE_UNTESTED] = "untested",
	[ALD2_PIPE_TESTING] = "still in testing",
	[ALD2_PIPE_TEST_CMD_ERR] = "test cmd error",
	[ALD2_PIPE_GET_CMD_ERR] = "get cmd error",
	[ALD2_PIPE_TEST_BAD] = "bad",
	[ALD2_PIPE_TEST_DONE] = "ok",
};

static ssize_t ald2_test_pipe_show(struct device_driver *drv,
								char *buf);
static ssize_t ald2_test_pipe_store(struct device_driver *drv,
								const char *buf, size_t count);
static DRIVER_ATTR(test_pipe, 0664, ald2_test_pipe_show, ald2_test_pipe_store);


static ssize_t ald2_test_pipe_store(struct device_driver *drv,
								const char *buf, size_t count)
{
	int ret = 0, test_pipe_id = -1, index = 0;
	u8 in_buf[7], out_buf[53];
	u8 sizeout = 0;
	u16 opcode = 0;
	const char *pos = buf;
	int depthisp_type;

	cam_info("%s enter %s", __func__, buf);
	depthisp_type = disp_get_chipid();
	if (DEPTHISP_DUMMY == depthisp_type) {
		set_test_result(ALD2_PIPE_0, ALD2_PIPE_TEST_DONE);
		set_test_result(ALD2_PIPE_1, ALD2_PIPE_TEST_DONE);
		set_test_result(ALD2_PIPE_DUAL, ALD2_PIPE_TEST_DONE);
		cam_info("%s dummy chip, nothing need to do", __func__);
		return count;
	}

	if (0 == strncmp("DBC_Begin", pos, strlen("DBC_Begin"))) {
		disp_cmd_filter = 1;
		cam_info("%s disp set  DBC mode to on",__func__);
		return count;
	}

	if (0 == strncmp("DBC_End", pos, strlen("DBC_End"))) {
		disp_cmd_filter = 0;
		cam_info("%s disp set  DBC mode to off",__func__);
		return count;
	}

	/* input:test_pipe=0 test_pipe=1 test_pipe=2 */
	if (0 == strncmp("test_pipe", pos, strlen("test_pipe"))) {
		while (*pos) {
			if (isdigit(*pos))
				break;
			else
				pos++;
		}
	}

	if (*pos == '0' ) {
		test_pipe_id = ALD2_PIPE_0;
	} else if (*pos == '1') {
		test_pipe_id = ALD2_PIPE_1;
	} else if (*pos == '2') {
		test_pipe_id = ALD2_PIPE_DUAL;
	} else {
	//	test_pipe_id = -1;
		cam_info("%s invalid argument", __func__);
		goto err;
	}

	set_test_result(test_pipe_id, ALD2_PIPE_TESTING);

	/* start test mode */
	memset(in_buf, 0, sizeof(in_buf));
	if (test_pipe_id == ALD2_PIPE_DUAL) {
		in_buf[0] = 1;
		in_buf[1]=101;
		sizeout = 43;
	} else {
		if(depthisp_type == DEPTHISP_AL6045){
			in_buf[test_pipe_id * 2] = 1;
			in_buf[test_pipe_id * 2 + 1] = 99;
			sizeout = 33;
		}else{
			in_buf[0] = 1;
			if(test_pipe_id == ALD2_PIPE_0) {
				in_buf[1]=101;
			} else {
				in_buf[1]=100;
			}
			sizeout = 53;
		}
	}
	opcode = ISPCMD_CAMERA_SET_SENSORMODE;
	ret = disp_exec_unidir_cmd(opcode, true, false, in_buf, sizeof(in_buf));
	if (ret) {
		set_test_result(test_pipe_id, ALD2_PIPE_TEST_CMD_ERR);
		cam_err("%s set test mode cmd failed ret:%d", __func__, ret);
		goto err;
	}

	msleep(10);

	/* get test mode */
	opcode = ISPCMD_GET_BULK_CHIPTEST_REPORT;
	memset(out_buf, 0, sizeout);
	ret = disp_exec_unidir_cmd(opcode, false, false, out_buf, sizeout);
	if (ret) {
		set_test_result(test_pipe_id, ALD2_PIPE_GET_CMD_ERR);
		cam_err("%s get test result cmd failed ret:%d", __func__, ret);
		goto err;
	}

	for (index = 0; index < sizeout; index++) {
		if(out_buf[index] != 1) {
			set_test_result(test_pipe_id, ALD2_PIPE_TEST_BAD);
			goto err;
		}
	}
	set_test_result(test_pipe_id, ALD2_PIPE_TEST_DONE);

err:
	msleep(100);
	return count;
}


static ssize_t ald2_test_pipe_show(struct device_driver *drv,
												char *buf)
{
	char *offset = buf;
	int ret, index, stage;
	const char *report;

	cam_info("%s enter", __func__);

	for (index = ALD2_PIPE_0; index < ALD2_PIPE_MAX; index++) {
		stage = test_result[index];
		report = test_report[stage];
		ret = snprintf(offset, PAGE_SIZE, "[PIPE%d:%s] ", index, report);
		offset += ret;
	}
	cam_info("%s:%s",  __func__, buf);

	ret = snprintf(offset, PAGE_SIZE, "\n");
	offset += ret;
	return (offset - buf);
}


/*add for ocram test*/
static ssize_t ald2_test_ocram_store(struct device_driver *drv, const char *buf, size_t count);
static ssize_t ald2_test_ocram_show(struct device_driver *drv, char *buf);
static DRIVER_ATTR(test_ocram, 0664, ald2_test_ocram_show, ald2_test_ocram_store);

static ssize_t ald2_test_ocram_store(struct device_driver *drv,
												  const char *buf, size_t count)
{
	const char *pos = buf;
	cam_info("%s enter %s", __func__, buf);

	if (0 == strncmp("OCRAM_Begin", pos, strlen("OCRAM_Begin")))
	{
		ocram_test = 1;
		cam_info("%s disp set OCRAM test mode to on",__func__);
		return count;
	}

	if (0 == strncmp("OCRAM_End", pos, strlen("OCRAM_End")))
	{
		ocram_test = 0;
		cam_info("%s disp set OCRAM test mode to off",__func__);
		return count;
	}

    return count;
}

static ssize_t ald2_test_ocram_show(struct device_driver *drv,
												char *buf)
{
	char *offset = buf;
	int ret, stage, depthisp_type;
	const char *report;

	cam_info("%s enter", __func__);

	if(0 == ocram_test) {
		depthisp_type = disp_get_chipid();
		if(DEPTHISP_AL6610 == depthisp_type) {
			ret = snprintf(offset, PAGE_SIZE, "support_ocram");
		} else {
			ret = snprintf(offset, PAGE_SIZE, "unsupport_ocram");
		}
	} else {
		if (0 == ocram_result) {
			stage = ALD2_PIPE_TEST_DONE;
		} else if (1 == ocram_result) {
			stage = ALD2_PIPE_TEST_BAD;
		} else {
			stage = ALD2_PIPE_TESTING;
		}
		ocram_test = 0;
		ocram_result = 0xFF;
		report = test_report[stage];
		ret = snprintf(offset, PAGE_SIZE, "[OCRAM:%s] ", report);
	}
	offset += ret;
	cam_info("%s:%s",  __func__, buf);
	ret = snprintf(offset, PAGE_SIZE, "\n");
	offset += ret;
	return (offset - buf);
}

char const* ald2_get_name(const hwdepthisp_intf_t* i)
{
    ald2_t* depth_isp = NULL;
    depth_isp = I2A(i);
    return depth_isp->name;
}

void ald2_notify_cmd_done( uint32_t cmd, uint32_t result)
{
	hwdepthisp_event_t depthisp_ev;
	depthisp_ev.kind = HWDEPTHISP_INFO_CMD_FINISH;
	depthisp_ev.data.cmd_finish.cmd = cmd;
	depthisp_ev.data.cmd_finish.result = result;
	cam_debug("%s cmd  = %x result = %d",__func__,cmd, result);
	hwdepthisp_intf_notify_error(s_ald2.notify,&depthisp_ev);
}

void ald2_notify_dump( uint32_t type)
{
	hwdepthisp_event_t depthisp_ev;
	depthisp_ev.kind = HWDEPTHISP_INFO_DUMP;
	depthisp_ev.data.dump.type = type;
	cam_info("%s dump type = %x",__func__,type);
	hwdepthisp_intf_notify_error(s_ald2.notify, &depthisp_ev);
}

void ald2_notify_error( uint32_t id)
{
	hwdepthisp_event_t depthisp_ev;
	depthisp_ev.kind = HWDEPTHISP_INFO_ERROR;
	depthisp_ev.data.error.id = id;
	cam_info("%s id = %x",__func__,id);
	hwdepthisp_intf_notify_error(s_ald2.notify, &depthisp_ev);
}

void ald2_notify_ocram_done(bool flag)
{
    if (true == flag) {
        ocram_result = 0;
    } else {
        ocram_result = 1;
    }
    cam_info("%s ocram_result = %d",__func__,ocram_result);
}


static hwdepthisp_vtbl_t
s_vtbl_ald2 =
{
    .get_name = ald2_get_name,
    .power_on = ald2_power_on,
    .power_off = ald2_power_off,
    .load_firmware = ald2_load_firmware,
    .exec_cmd = ald2_exec_cmd,
    .matchid = ald2_matchid,
};

static ald2_t
s_ald2 =
{
    .name = "ald2",
    .intf = { .vtbl = &s_vtbl_ald2, },
};

static const struct of_device_id
s_ald2_dt_match[] =
{
	{
        .compatible = "huawei,ald2",
        .data = &s_ald2.intf,
    },
	{
    },
};

MODULE_DEVICE_TABLE(of, s_ald2_dt_match);

static struct platform_driver
s_ald2_driver =
{
	.driver =
    {
		.name = "huawei,ald2",
		.owner = THIS_MODULE,
		.of_match_table = s_ald2_dt_match,
	},
};

static int32_t
ald2_platform_probe(
        struct platform_device* pdev)
{
	cam_notice("%s enter", __func__);
    return hwdepthisp_register(pdev, &s_ald2.intf, &s_ald2.notify);
}

static int __init
ald2_init_module(void)
{
	int ret = 0;

	cam_notice("%s enter", __func__);

	ret = platform_driver_probe(&s_ald2_driver,
			ald2_platform_probe);

	/* NOTE: use driver attribute */
	if (ret == 0) {
		if (driver_create_file(&s_ald2_driver.driver, &driver_attr_test_pipe))
			cam_warn("%s create driver attr failed", __func__);
		if (driver_create_file(&s_ald2_driver.driver, &driver_attr_test_ocram))
			cam_warn("%s create driver attr failed", __func__);
	}

	return ret;
}

static void __exit
ald2_exit_module(void)
{
    platform_driver_unregister(&s_ald2_driver);
    hwdepthisp_unregister(&s_ald2.intf);
}

module_init(ald2_init_module);
module_exit(ald2_exit_module);
MODULE_DESCRIPTION("ald2");
MODULE_LICENSE("GPL v2");

