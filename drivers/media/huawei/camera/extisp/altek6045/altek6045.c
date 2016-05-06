


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
#include "../hwextisp.h"
#include "hw_pmic.h"
#include "extisp.h"
#include "cam_log.h"
#include "sensor_commom.h"

typedef enum {
	ISP_DVDD = 0,
	ISP_RST,
	ISP_INT,
	ISP_MAX,
}altek6045_pin_type;

enum mini_isp_power_state_t{
	MINI_ISP_POWER_OFF = 0,
	MINI_ISP_POWER_ON,
};

typedef struct _altek6045_private_data_t {
	unsigned int pin[ISP_MAX];
}altek6045_private_data_t;



enum {
	ALTEK6045_PIPE_0 = 0,
	ALTEK6045_PIPE_1 = 1,
	ALTEK6045_PIPE_DUAL = 2,
	ALTEK6045_PIPE_MAX = 3,
};

enum altek6045_pipe_test_stage {
	ALTEK6045_PIPE_UNTESTED = 0,
	ALTEK6045_PIPE_TESTING = 1,
	ALTEK6045_PIPE_TEST_CMD_ERR = 2,
	ALTEK6045_PIPE_GET_CMD_ERR = 3,
	ALTEK6045_PIPE_TEST_BAD = 4,
	ALTEK6045_PIPE_TEST_DONE = 5,
	ALTEK6045_PIPE_TEST_MAX = 6,
};


typedef struct _tag_altek6045
{
    char 				name[32];
    hwextisp_intf_t                             intf;
    altek6045_private_data_t*		pdata;
    hwextisp_notify_intf_t*          notify;
} altek6045_t;

#define I2A(i) container_of(i, altek6045_t, intf)

#define VOLTAGE_1P1V		1100000
#define VOLTAGE_1P8V		1800000

altek6045_private_data_t altek6045_pdata;
static altek6045_t s_altek6045;
// add for mmi test
static int cross_width = 0;
static int cross_height = 0;
static int ois_done = 0;
static int ois_check = 0;
wait_queue_head_t ois_queue;

#define OIS_TEST_TIMEOUT        (HZ * 8)
//---
extern struct hisi_pmic_ctrl_t ncp6925_ctrl;

static uint32_t misp_cmd_filter = 0;
extern char misp_firmware_path[NAME_MAX];

void altek6045_notify_error( uint32_t id);

int altek6045_power_on(const hwextisp_intf_t* i)
{
    return misp_init();;
}

int altek6045_power_off(const hwextisp_intf_t* i)
{
    return misp_exit();
}

int altek6045_load_firmware(const hwextisp_intf_t* i, hwextisp_config_data_t *data)
{
	cam_notice("enter %s.", __func__);
	return misp_load_fw(data->u.buf);
}

int altek6045_matchid(const hwextisp_intf_t* i, hwextisp_config_data_t *data)
{
	int rc = 0;
	cam_info("enter %s", __func__);

	data->extisp_type = misp_get_chipid();
	cam_info(" %s extisp_type %d", __func__,data->extisp_type);
	return rc;
}

extern unsigned int get_boot_into_recovery_flag(void);
int altek6045_exec_cmd(const hwextisp_intf_t* i, hwextisp_config_data_t *data)
{
	int rc = 0;
	u8 *in_buf = NULL, *out_buf = NULL;
	u32 opcode, dir_type, block_response, out_len, in_len, bulk_len;
	bool out_to_block, out_from_block;

	if (get_boot_into_recovery_flag()||(misp_cmd_filter==1)) {
		cam_info("%s cmd=0x%x is blocked", __func__, data->cmd);
		return 0;
	}

	if(((data->cmd & 0x0000FFFF )!= 0x2106)&&((data->cmd & 0x0000FFFF )!= 0x2105))
		cam_info("%s cmd=0x%x", __func__, data->cmd);

	dir_type = (data->cmd & EXTISP_CMD_DIR_FLAG_MASK)>>EXTISP_CMD_DIR_FLAG_SHIT;
	block_response = (data->cmd & EXTISP_CMD_RESP_FLAG_MASK)>>EXTISP_CMD_RESP_FLAG_SHIT;
	out_len = (data->cmd & EXTISP_CMD_OUT_LEN_MASK)>>EXTISP_CMD_OUT_LEN_SHIT;
	in_len = (data->cmd & EXTISP_CMD_IN_LEN_MASK)>>EXTISP_CMD_IN_LEN_SHIT;
	opcode = (data->cmd & EXTISP_CMD_OPCODE_MASK)>>EXTISP_CMD_OPCODE_SHIT;
	cam_info("%s :dir_type %d, block_response %d, out_len %d, in_len %d, opcode %x ", __func__, dir_type, block_response, out_len, in_len, opcode);
	out_buf = in_buf = data->u.buf;
	out_to_block = (EXTISP_BLOCK_RESPONSE_CMD == block_response)? true: false;
	out_from_block = (EXTISP_BLOCK_WRITE_CMD == block_response) ? true : false;

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

	if (EXTISP_INOUT_CMD == dir_type) {
		if (out_from_block) {
			rc = misp_exec_write_block_res((u16)opcode, in_buf, in_len, out_to_block, out_buf,bulk_len, out_len);
		} else {
			rc = misp_exec_bidir_cmd((u16)opcode, data->u.buf, in_len, out_to_block, out_buf, out_len);
		}
	} else if (EXTISP_SET_CMD == dir_type) {
		if (out_from_block) {
			rc = misp_exec_write_block((u16)opcode, in_buf, in_len, out_buf, bulk_len);
		} else {
			rc = misp_exec_unidir_cmd((u16)opcode, true, out_to_block, in_buf, in_len);
		}
	} else if (EXTISP_GET_CMD == dir_type) {
		rc = misp_exec_unidir_cmd((u16)opcode, false, out_to_block, out_buf, out_len);
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

static ssize_t altel6045_powerctrl_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;
        cam_info("enter %s", __func__);

        return rc;
}
static ssize_t altel6045_powerctrl_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int state = simple_strtol(buf, NULL, 10);
	cam_info("enter %s, state %d", __func__, state);

	if (state == MINI_ISP_POWER_ON)
		altek6045_power_on(&s_altek6045.intf);
	else
		altek6045_power_off(&s_altek6045.intf);

	return count;
}


static struct device_attribute altel6045_powerctrl =
    __ATTR(power_ctrl, 0664, altel6045_powerctrl_show, altel6045_powerctrl_store);

int altel6045_register_attribute(const hwextisp_intf_t* i, struct device *dev)
{
	int ret = 0;
	cam_info("enter %s", __func__);

	ret = device_create_file(dev, &altel6045_powerctrl);
	if (ret < 0) {
		cam_err("%s failed to creat power ctrl attribute.", __func__);
		goto err_create_power_ctrl;
	}
	return 0;
err_create_power_ctrl:
	device_remove_file(dev, &altel6045_powerctrl);
	return ret;
}

/*
maybe used later
static char *test_raw_buf[ALTEK6045_PIPE_MAX][33];
*/
static int   test_result[ALTEK6045_PIPE_MAX];
#define set_test_result(pipe, result) \
	do { \
		test_result[pipe] = result;\
	} while(0)

static const char *test_report[ALTEK6045_PIPE_TEST_MAX] =
{
	[ALTEK6045_PIPE_UNTESTED] = "untested",
	[ALTEK6045_PIPE_TESTING] = "still in testing",
	[ALTEK6045_PIPE_TEST_CMD_ERR] = "test cmd error",
	[ALTEK6045_PIPE_GET_CMD_ERR] = "get cmd error",
	[ALTEK6045_PIPE_TEST_BAD] = "bad",
	[ALTEK6045_PIPE_TEST_DONE] = "ok",
};

static ssize_t altel6045_test_pipe_show(struct device_driver *drv,
								char *buf);
static ssize_t altel6045_test_pipe_store(struct device_driver *drv,
								const char *buf, size_t count);
static DRIVER_ATTR(test_pipe, 0664, altel6045_test_pipe_show, altel6045_test_pipe_store);


static ssize_t altel6045_test_pipe_store(struct device_driver *drv,
												  const char *buf, size_t count)
{
	int ret = 0, test_pipe_id = -1, index = 0;
	u8 in_buf[7], out_buf[53];
	u8 sizeout = 0;
	u16 opcode = 0;
	const char *pos = buf;
       int  extisp_type = EXTISP_NULL;

	cam_info("%s enter %s", __func__, buf);
       extisp_type = misp_get_chipid();

        if (0 == strncmp("DBC_Begin", pos, strlen("DBC_Begin")))
        {
            misp_cmd_filter = 1;
            cam_info("%s misp set  DBC mode to on",__func__);
            return count;
        }

        if (0 == strncmp("DBC_End", pos, strlen("DBC_End")))
        {
            misp_cmd_filter = 0;
            cam_info("%s misp set  DBC mode to off",__func__);
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
		test_pipe_id = ALTEK6045_PIPE_0;
	} else if (*pos == '1') {
		test_pipe_id = ALTEK6045_PIPE_1;
	} else if (*pos == '2') {
		test_pipe_id = ALTEK6045_PIPE_DUAL;
	} else {
	//	test_pipe_id = -1;
		cam_info("%s invalid argument", __func__);
		goto err;
	}

	set_test_result(test_pipe_id, ALTEK6045_PIPE_TESTING);

	/* start test mode */
	memset(in_buf, 0, sizeof(in_buf));
	if (test_pipe_id == ALTEK6045_PIPE_DUAL) {
		in_buf[0] = in_buf[2] = 1;
		in_buf[1] = in_buf[3] = 99;
		sizeout = 33;
	} else {
            if(extisp_type == EXTISP_AL6045){
                in_buf[test_pipe_id * 2] = 1;
                in_buf[test_pipe_id * 2 + 1] = 99;
                sizeout = 33;
            }else{
        		in_buf[0] = 1;
        		if(test_pipe_id == ALTEK6045_PIPE_0) {
        			in_buf[1]=101;
        		} else {
        			in_buf[1]=100;
        		}
                    sizeout = 53;
            }
	}
	opcode = ISPCMD_CAMERA_SET_SENSORMODE;
	ret = misp_exec_unidir_cmd(opcode, true, false, in_buf, sizeof(in_buf));
	if (ret) {
		set_test_result(test_pipe_id, ALTEK6045_PIPE_TEST_CMD_ERR);
		cam_err("%s set test mode cmd failed ret:%d", __func__, ret);
		goto err;
	}

	msleep(1000);

	/* get test mode */
	opcode = ISPCMD_GET_BULK_CHIPTEST_REPORT;
	memset(out_buf, 0, sizeout);
	ret = misp_exec_unidir_cmd(opcode, false, false, out_buf, sizeout);
	if (ret) {
		set_test_result(test_pipe_id, ALTEK6045_PIPE_GET_CMD_ERR);
		cam_err("%s get test result cmd failed ret:%d", __func__, ret);
		goto err;
	}

	for (index = 0; index < sizeout; index++) {
		if(out_buf[index] != 1) {
			set_test_result(test_pipe_id, ALTEK6045_PIPE_TEST_BAD);
			goto err;
		}
	}
	set_test_result(test_pipe_id, ALTEK6045_PIPE_TEST_DONE);

err:
	msleep(100);
	return count;
}


static ssize_t altel6045_test_pipe_show(struct device_driver *drv,
												char *buf)
{
	char *offset = buf;
	int ret, index, stage;
	const char *report;

	cam_info("%s enter", __func__);

	for (index = ALTEK6045_PIPE_0; index < ALTEK6045_PIPE_MAX; index++) {
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

// add for ois mmi test
static ssize_t altel6045_test_mmi_show(struct device_driver *drv,
								char *buf);
static ssize_t altel6045_test_mmi_store(struct device_driver *drv,
								const char *buf, size_t count);
static DRIVER_ATTR(ois_pixel, 0664, altel6045_test_mmi_show, altel6045_test_mmi_store);

static ssize_t altel6045_test_mmi_show(struct device_driver *drv,
								char *buf)
{
    int ret = -1;
    char *offset = buf;

    cam_info("Enter: %s", __func__);
    ret = snprintf(offset, PAGE_SIZE, "%d,%d\n",
            cross_width, cross_height);
    offset += ret;

    return (offset - buf);
}

static ssize_t altel6045_test_mmi_store(struct device_driver *drv,
								const char *buf, size_t count)
{
    int width, height;

    sscanf(buf, "%d%d", &width, &height);
    cross_width = width;
    cross_height = height;
    return count;
}
//---
// add for ois running test
static ssize_t altel6045_test_ois_show(struct device_driver *drv,
								char *buf);
static ssize_t altel6045_test_ois_store(struct device_driver *drv,
								const char *buf, size_t count);
static DRIVER_ATTR(test_ois, 0664, altel6045_test_ois_show, altel6045_test_ois_store);

static ssize_t altel6045_test_ois_show(struct device_driver *drv,
								char *buf)
{
    int ret = -1;
    char *offset = buf;

    cam_info("Enter: %s", __func__);
    ois_done = 0;
    //wait for start command
    msleep(50);
    ret = wait_event_interruptible_timeout(ois_queue, ois_done != 0, OIS_TEST_TIMEOUT);
    if(ret <= 0) {
        cam_warn("%s: wait ois signal timeout", __func__);
    }
    ret = snprintf(offset, PAGE_SIZE, "%d", ois_done);
    offset += ret;

    return (offset - buf);
}

static ssize_t altel6045_test_ois_store(struct device_driver *drv,
								const char *buf, size_t count)
{
    int done_flag;

    sscanf(buf, "%d", &done_flag);
    cam_info("%s: done_flag = %d", __func__, done_flag);
    ois_done = done_flag;
    wake_up_interruptible(&ois_queue);
    return count;
}
//for ois check
static ssize_t altel6045_check_ois_show(struct device_driver *drv,
                                char *buf);
static ssize_t altel6045_check_ois_store(struct device_driver *drv,
                                const char *buf, size_t count);
static DRIVER_ATTR(check_ois, 0664, altel6045_check_ois_show, altel6045_check_ois_store);

static ssize_t altel6045_check_ois_show(struct device_driver *drv,
                                char *buf)
{
    int ret = -1;
    char *offset = buf;

    cam_info("Enter: %s", __func__);
    ois_check = 0;
    //wait for start command
    msleep(50);
    ret = wait_event_interruptible_timeout(ois_queue, ois_check != 0, OIS_TEST_TIMEOUT);
    if(ret <= 0) {
        cam_warn("%s: wait ois signal timeout", __func__);
    }
    ret = snprintf(offset, PAGE_SIZE, "%d", ois_check);
    offset += ret;

    return (offset - buf);
}

static ssize_t altel6045_check_ois_store(struct device_driver *drv,
                                const char *buf, size_t count)
{
    int done_flag;

    sscanf(buf, "%d", &done_flag);
    cam_info("%s: done_flag = %d", __func__, done_flag);
    ois_check = done_flag;
    wake_up_interruptible(&ois_queue);
    return count;
}

static ssize_t altel6045_firmware_show(struct device_driver *drv,
								char *buf);
static ssize_t altel6045_firmware_store(struct device_driver *drv,
								const char *buf, size_t count);
static DRIVER_ATTR(firmware, 0664, altel6045_firmware_show, altel6045_firmware_store);

static ssize_t altel6045_firmware_store(struct device_driver *drv,
												  const char *buf, size_t count)
{
	cam_info("%s enter buf(%s),count(%u)", __func__, buf,count);
    strncpy(misp_firmware_path, buf, sizeof(misp_firmware_path));
    cam_info("%s exit extisp_firmware(%s),count(%u)", __func__,
        misp_firmware_path,strlen(misp_firmware_path));
    return count;
}

static ssize_t altel6045_firmware_show(struct device_driver *drv,
												char *buf)
{
    strncpy(buf, misp_firmware_path, strlen(misp_firmware_path)+1);
    cam_info("%s extisp_firmware(%s),count(%u)", __func__, misp_firmware_path,strlen(misp_firmware_path));
	return (strlen(misp_firmware_path));
}

int altel6045_get_dt_data(const hwextisp_intf_t *i, struct device_node *of_node)
{
	return 0;
}

char const* altel6045_get_name(const hwextisp_intf_t* i)
{
    altek6045_t* mini_isp = NULL;
    mini_isp = I2A(i);
    return mini_isp->name;
}

void altek6045_notify_cmd_done( uint32_t cmd, uint32_t result)
{
	hwextisp_event_t extisp_ev;
	extisp_ev.kind = HWEXTISP_INFO_CMD_FINISH;
	extisp_ev.data.cmd_finish.cmd = cmd;
	extisp_ev.data.cmd_finish.result = result;
	cam_debug("%s cmd  = %x result = %d",__func__,cmd, result);
	hwextisp_intf_notify_error(s_altek6045.notify,&extisp_ev);
}

void altek6045_notify_dump( uint32_t type)
{
	hwextisp_event_t extisp_ev;
	extisp_ev.kind = HWEXTISP_INFO_DUMP;
	extisp_ev.data.dump.type = type;
	cam_info("%s dump type = %x",__func__,type);
	hwextisp_intf_notify_error(s_altek6045.notify, &extisp_ev);
}

void altek6045_notify_error( uint32_t id)
{
	hwextisp_event_t extisp_ev;
	extisp_ev.kind = HWEXTISP_INFO_ERROR;
	extisp_ev.data.error.id = id;
	cam_info("%s id = %x",__func__,id);
	hwextisp_intf_notify_error(s_altek6045.notify, &extisp_ev);
}

void altek6045_notify_ois_done( uint32_t id)
{
	hwextisp_event_t extisp_ev;
	extisp_ev.kind = HWEXTISP_INFO_OIS_DONE;
	extisp_ev.data.error.id = id;
	cam_info("%s id = %x",__func__,id);
	hwextisp_intf_notify_error(s_altek6045.notify, &extisp_ev);
}

static hwextisp_vtbl_t
s_vtbl_altek6045 =
{
    .get_name = altel6045_get_name,
    .power_on = altek6045_power_on,
    .power_off = altek6045_power_off,
    .load_firmware = altek6045_load_firmware,
    .exec_cmd = altek6045_exec_cmd,
    .matchid = altek6045_matchid,

    .mini_isp_get_dt_data = altel6045_get_dt_data,
    .mini_isp_register_attribute = altel6045_register_attribute,
    //TODO ...

};

static altek6045_t
s_altek6045 =
{
    .name = "altek6045",
    .intf = { .vtbl = &s_vtbl_altek6045, },
    .pdata = &altek6045_pdata,
};

static const struct of_device_id
s_altek6045_dt_match[] =
{
	{
        .compatible = "huawei,altek6045",
        .data = &s_altek6045.intf,
    },
	{
    },
};

MODULE_DEVICE_TABLE(of, s_altek6045_dt_match);

static struct platform_driver
s_altek6045_driver =
{
	.driver =
    {
		.name = "huawei,altek6045",
		.owner = THIS_MODULE,
		.of_match_table = s_altek6045_dt_match,
	},
};

static int32_t
altek6045_platform_probe(
        struct platform_device* pdev)
{
	cam_notice("%s enter", __func__);
    return hwextisp_register(pdev, &s_altek6045.intf, &s_altek6045.notify);
}

static int __init
altek6045_init_module(void)
{
	int ret = 0;

	cam_notice("%s enter", __func__);

	ret = platform_driver_probe(&s_altek6045_driver,
			altek6045_platform_probe);

	/* NOTE: use driver attribute */
	if (ret == 0) {
		if (driver_create_file(&s_altek6045_driver.driver, &driver_attr_test_pipe))
			cam_warn("%s create driver attr failed", __func__);
		if (driver_create_file(&s_altek6045_driver.driver, &driver_attr_ois_pixel))
			cam_warn("%s create driver attr failed", __func__);
		if (driver_create_file(&s_altek6045_driver.driver, &driver_attr_test_ois))
			cam_warn("%s create driver attr failed", __func__);
		if (driver_create_file(&s_altek6045_driver.driver, &driver_attr_check_ois))
			cam_warn("%s create driver attr failed", __func__);
		if (driver_create_file(&s_altek6045_driver.driver, &driver_attr_firmware))
			cam_warn("%s create driver attr firmware failed", __func__);
	}
    //init queue
    init_waitqueue_head(&ois_queue);

	return ret;
}

static void __exit
altek6045_exit_module(void)
{
    platform_driver_unregister(&s_altek6045_driver);
}

module_init(altek6045_init_module);
module_exit(altek6045_exit_module);
MODULE_DESCRIPTION("altek6045");
MODULE_LICENSE("GPL v2");

