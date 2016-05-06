#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/limits.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/regulator/consumer.h>
#include <linux/gpio.h>
#include <linux/input.h>
#include <linux/input/mt.h>
#include <asm/unaligned.h>
#include <linux/firmware.h>
#include <cypress_params.h>
#include <../../huawei_touchscreen_chips.h>
#include "cypress.h"

#define CY_CHIP_INFO "CY8CTMA463"
#define TP_ANALOG_VDD "CYPRESS_TP_ANALOG_VDD"
#define TP_IO_VDD "CYPRESS_TP_IO_VDD"

static struct cypress_core_data core_data;
static const struct firmware *fw_entry = NULL;
static int *rawdatabuf = NULL;
static int rawdata_size = 0;
static int rawdata_index = 0;

struct touch_settings cypress_sett_param_regs = {
	.data = (uint8_t *)&cyttsp4_param_regs[0],
	.size = ARRAY_SIZE(cyttsp4_param_regs),
	.tag = 0,
};
static int cypress_chip_detect(struct device_node *device,struct ts_device_data *chip_data, struct platform_device *ts_dev);
static int cypress_init_chip(void);
static int cypress_parse_config(struct device_node *device, struct ts_device_data *chip_data);
static int cypress_input_config(struct input_dev *input_dev);
static int cypress_irq_bottom_half(struct ts_cmd_node *in_cmd, struct ts_cmd_node *out_cmd);
static int cypress_irq_top_half(struct ts_cmd_node *cmd);
static int cypress_fw_update_boot(char *file_name);
static int cypress_firmware_calibrate(void);
static int cypress_register_algo(struct ts_device_data *chip_data);
static int cypress_suspend(void);
static int cypress_resume(void);
static int cypress_exec_cmd(u8 mode,u8 *cmd_buf, size_t cmd_size, u8 *return_buf, size_t return_buf_size);
static int set_hst_mode(u8 new_mode);
static int cypress_switch_to_operate(void);
static int check_hst_mode(u8 hst_mode);
static int cypress_chip_get_info(struct ts_chip_info_param *info);
static void cypress_shutdown(void);
static int cypress_get_glove_switch(u8 *glove_switch);
static int cypress_set_glove_switch(u8 glove_switch);
static int cypress_glove_switch(struct ts_glove_info *info);
static int cypress_holster_switch(struct ts_holster_info *info);
static int cypress_hand_detect(struct ts_hand_info *info);
static int cypress_get_rawdata(struct ts_rawdata_info *info, struct ts_cmd_node *out_cmd);
static int cypress_check_status(void);
static int cypress_reset_chip(void);

static const u8 ldr_exit[] = {
	0xFF, 0x01, 0x3B, 0x00, 0x00, 0x4F, 0x6D, 0x17
};
static const u8 ldr_err_app[] = {
	0x01, 0x02, 0x00, 0x00, 0x55, 0xDD, 0x17
};

static const u8 cypress_security_key[] = {
	0xA5, 0x01, 0x02, 0x03, 0xFF, 0xFE, 0xFD, 0x5A
};
#define HI_BYTE(x) (u8)(((x) >> 8) & 0xFF)
#define LO_BYTE(x) (u8)((x) & 0xFF)
//#define CYTTSP4_LOADER_NAME "cyttsp4_loader"
#define CY_CORE_BL_HOST_SYNC_BYTE		0xFF

/* x & y-axis resolution of panel in pixels */
#define CY_PCFG_RESOLUTION_X_Y_MASK 0x7F

/* x & y-axis, 0:origin is on left and top side of panel, 1: right and bottom */
#define CY_PCFG_ORIGIN_X_Y_MASK 0x80

//#define CYPRESS_INPUT_ELEM_SZ (sizeof("0xHH") + 1)
//#define CY_OPE_INDEX   0
//#define CY_SYS_INDEX   1
//#define CY_CAT_INDEX   2
#define CY_CMD_IN_DATA_OFFSET_VALUE 0
#define CY_CMD_OUT_STATUS_OFFSET 0
#define CY_CMD_RET_PNL_OUT_ELMNT_SZ_OFFS_H 2
#define CY_CMD_RET_PNL_OUT_ELMNT_SZ_OFFS_L 3
#define CY_CMD_RET_PNL_OUT_DATA_FORMAT_OFFS 4
#define I2C_BUF_MAX_SIZE 512
#define CY_CMD_RET_PANEL_ELMNT_SZ_MASK 0x07
#define CY_CMD_RET_PANEL_ENDIAN_MASK 0x10
#define B_ENDIAN 0
//#define L_ENDIAN 0x10

#define CY_IRQ_GPIO "cypress/attn_gpio"
#define CY_RST_GPIO "cypress/reset_gpio"
#define CY_IRQ_CFG "cypress/irq_config"
/* MUT RAW Range */
#define CY_MUT_RAW_MIN		-2000
#define CY_MUT_RAW_MAX		-550
/* SELF RAW Range */
#define CY_SELF_RAW_MIN		-455
#define CY_SELF_RAW_MAX 	1115
/* MUT IDAC Range */
#define CY_MUT_IDAC_MIN		1
#define CY_MUT_IDAC_MAX		31
/* SELF IDAC Range */
//#define CY_SELF_IDAC_MIN	1
//#define CY_SELF_IDAC_MAX	31

struct ts_device_ops ts_cypress_ops = {
	.chip_detect = cypress_chip_detect,
	.chip_init = cypress_init_chip,
	.chip_parse_config = cypress_parse_config,
	.chip_register_algo = cypress_register_algo,
	.chip_input_config = cypress_input_config,
	.chip_irq_top_half = cypress_irq_top_half,
	.chip_irq_bottom_half = cypress_irq_bottom_half,
	.chip_fw_update_boot = cypress_fw_update_boot,
	.chip_get_info = cypress_chip_get_info,
	.chip_suspend = cypress_suspend,
	.chip_resume = cypress_resume,
	.chip_get_rawdata = cypress_get_rawdata,
	.chip_calibrate = cypress_firmware_calibrate,
	.chip_shutdown = cypress_shutdown,
	.chip_glove_switch = cypress_glove_switch,
	.chip_holster_switch = cypress_holster_switch,
	.chip_hand_detect = cypress_hand_detect,
	.chip_check_status=cypress_check_status,
	.chip_reset=cypress_reset_chip,
#ifdef HUAWEI_TOUCHSCREEN_TEST
	.chip_test = test_dbg_cmd_test,
#endif
 };

int cypress_algo_t1 (struct ts_device_data *dev_data, struct ts_fingers *in_info, struct ts_fingers *out_info)
{
	int index;
	int id;
	for(index = 0, id = 0; index < TS_MAX_FINGER; index++, id++){
		if(in_info->cur_finger_number == 0){
			out_info->fingers[0].status = TS_FINGER_RELEASE;
			if(id >= 1)
				out_info->fingers[id].status = 0;
		}else {
			if (in_info->fingers[index].x != 0 || in_info->fingers[index].y !=0) {
				if (CY_EV_TOUCHDOWN == in_info->fingers[index].event || CY_EV_MOVE == in_info->fingers[index].event || CY_EV_NO_EVENT== in_info->fingers[index].event) {
					out_info->fingers[id].x = in_info->fingers[index].x;
					out_info->fingers[id].y = in_info->fingers[index].y;
					out_info->fingers[id].pressure = in_info->fingers[index].pressure;
					out_info->fingers[id].status = TS_FINGER_PRESS;
				}else if (CY_EV_LIFTOFF == in_info->fingers[index].event) {
					out_info->fingers[id].status = TS_FINGER_RELEASE;
				}
			}else
				out_info->fingers[id].status = 0;
		}
	}


	return NO_ERR;
}

struct ts_algo_func cypress_algo_f1=
{
	.algo_name = "cypress_algo_t1",
	.chip_algo_func = cypress_algo_t1,
};
int cypress_register_algo(struct ts_device_data *chip_data)
{
	int rc = 0;
	TS_LOG_INFO("cypress_reg_algo called\n");

	rc = register_algo_func(chip_data, &cypress_algo_f1);		//put algo_f1 into list contained in chip_data, named algo_t1
	if(rc)
		goto out;
out:
	return rc;
}
static inline void debug_print_i2c_transfer(bool action, u8 addr, u8 *buf, int size)
{
	int index = 0;

	if(action)
		TS_LOG_DEBUG("[cypress debug] i2c action write addr:0x%x, size:%d\n", addr, size);
	else
		TS_LOG_DEBUG("[cypress debug] i2c action read addr:0x%x, size:%d\n", addr, size);

	for(;index < size; index++)
		TS_LOG_DEBUG("[cypress debug] buf value :0x%x\n", *(buf+index));
}

static int cypress_i2c_read(u8 *reg_addr, u16 reg_len, u8 *buf, u16 len)
{
	int rc = 0;
	rc = core_data.cypress_chip_data->bops->bus_read(reg_addr, reg_len, buf, len);
	if (rc < 0)
		TS_LOG_ERR("fail read  rc=%d\n", rc);

	debug_print_i2c_transfer(false, *reg_addr, buf, len);

	return rc;
}

static int cypress_i2c_write(u8 addr, u8 *buf, u16 length)
{
	u8 wr_buf[length+1];
	int rc = 0;

	wr_buf[0] = addr;
	memcpy(wr_buf+1, buf, length);
	rc = core_data.cypress_chip_data->bops->bus_write(wr_buf, sizeof(wr_buf));
	if(rc < 0)
		TS_LOG_ERR("failed to write, rc=%d\n", rc);

	debug_print_i2c_transfer(true, wr_buf[0], &wr_buf[1], length);

	return rc;

}

/*handshake is used to inform IC could send interrupt*/
static int cypress_handshake(u8 mode)
{
	u8 cmd = mode ^ CY_HST_TOGGLE;
	int rc;
	u8 reg_addr = CY_REG_BASE;
	TS_LOG_DEBUG("mode[0]: 0x%x\n", mode);

	if (mode & CY_HST_MODE_CHANGE) {
		TS_LOG_ERR("Host mode change bit set, NO handshake. mode = 0x%x\n", mode);
		return NO_ERR;
	}
	rc = cypress_i2c_write(reg_addr, &cmd, sizeof(cmd));
	if (rc < 0)
		TS_LOG_ERR("bus write fail on handshake, rc = %d\n", rc);

	return rc;
}

static int check_hst_mode(u8 hst_mode)
{
	int rc = NO_ERR;
	u8 mode[3] = {0};
	u8 cur_mode = 0;
	u8 reg_addr = CY_REG_BASE;
	u8 cmd_ofs = 2;
	core_data.complete_cmd = false;
	TS_LOG_DEBUG("make sure wheather in mode: 0x%x\n", hst_mode);

	rc = cypress_i2c_read(&reg_addr, sizeof(reg_addr), mode, sizeof(mode));
	if (rc < 0) {
		TS_LOG_ERR("Failed to read mode from 0x00, rc = %d\n", rc);
		return rc;
	}
	TS_LOG_DEBUG("mode[0-2]: 0x%02X 0x%02X 0x%02X, current mode: 0x%02X\n", mode[0], mode[1], mode[2], cur_mode);

	cur_mode = mode[0] & CY_HST_MODE;
	switch (cur_mode) {
		case CY_HST_OPERATE:								//operation mode  000
			TS_LOG_DEBUG("cur_mode:0x%x, operational mode\n", cur_mode);
			break;
		case CY_HST_CAT:									//configuration and test mode	010
			TS_LOG_DEBUG("cur_mode:0x%x, CaT mode\n", cur_mode);
			break;
		case CY_HST_SYSINFO:
			TS_LOG_DEBUG("cur_mode:0x%x, sysinfo mode\n", cur_mode);					//sysinfo mode  001
			break;
		default:
			TS_LOG_ERR("Unkown mode:0x%x, mode[0] = 0x%02X\n", cur_mode, mode[0]);
			break;
	}

	/*judge in which mode, register 0x00 bit 6,5,4. 000 is operation mode, 001 is sysinfo mode, 010 is cat mode, */
	if (cur_mode == hst_mode) {
		TS_LOG_DEBUG("OK, its correct mode\n");
	} else {
		TS_LOG_ERR("Sorry, its uncorrect mode, cur_mode = %d\n", cur_mode);
		return -EINVAL;
	}

	TS_LOG_DEBUG("cmd_ofs = %d, mode[cmd_ofs] = 0x%x\n", cmd_ofs, mode[cmd_ofs]);
	if (mode[cmd_ofs] & CY_CMD_COMPLETE) {
		TS_LOG_DEBUG("Received command complete\n");
		core_data.complete_cmd = true;
	} else {
		TS_LOG_ERR("command is not complete\n");
		core_data.complete_cmd = false;
	}

	rc = cypress_handshake(mode[0]);
	if (rc < 0)
		TS_LOG_ERR("Fail handshake mode[0] = 0x%X, rc = %d\n", mode[0], rc);

	return rc;
}

static int cypress_power_on_reset(void)
{
	int rc = 0;

	TS_LOG_INFO("in\n");
	/*disable regulator first*/
	regulator_disable(core_data.vbus);
	regulator_disable(core_data.vdd);
	msleep(5);

	rc = regulator_set_voltage(core_data.vdd, 2800000, 2800000);
	if(rc < 0){
		TS_LOG_ERR("failed to set cypress vdd to 2.8V, rc = %d\n", rc);
		return  -EINVAL;
	}

	rc = regulator_enable(core_data.vdd);
	if (rc < 0) {
		TS_LOG_ERR("failed to enable cypress vdd(2.8V), rc = %d\n", rc);
		return -EINVAL;
	}

	rc = regulator_enable(core_data.vbus);
	if (rc < 0) {
		TS_LOG_ERR("vbus enable error:%d \n", rc);
		return -EINVAL;
	}
	msleep(5);
	return rc;
}
static void cypress_hw_reset(void)
{
	TS_LOG_INFO("in\n");
	gpio_set_value(core_data.cypress_chip_data->reset_gpio, 1);
	msleep(20);
	gpio_set_value(core_data.cypress_chip_data->reset_gpio, 0);
	msleep(40);
	gpio_set_value(core_data.cypress_chip_data->reset_gpio, 1);
	msleep(30);
}

static int cypress_soft_reset(void)
{
	u8 cmd = CY_HST_RESET | CY_HST_MODE_CHANGE;
	int rc = cypress_i2c_write(CY_REG_BASE, &cmd, sizeof(cmd));
	if (rc < 0) {
		TS_LOG_ERR("FAILED to execute SOFT reset\n");
		return rc;
	}
	TS_LOG_INFO("execute SOFT reset\n");
	return 0;
}

static int cypress_checkout_bl(void)
{
	int rc = 0;
	int i;
	u8 reg_addr = CY_REG_BASE;
	u8 mode[3] = {0};

	/*checkout HST_MODE register (0x00) whether in bootloader mode, 200ms interrupts generated.
	**so, read 3 timer per 200ms, to make sure it is in bootloader mode, in which mode[0] is 0x01 */
	for (i = 0; i < I2C_RW_TRIES; i++) {
		rc = cypress_i2c_read(&reg_addr, sizeof(reg_addr), mode, sizeof(mode));
		if (rc < 0) {
			TS_LOG_ERR("Failed to read register 0x00, i = %d, rc = %d\n", i, rc);
		} else {
			TS_LOG_DEBUG("mode[0-2]:0x%X 0x%X 0x%X\n", mode[0], mode[1], mode[2]);
			if (IS_BOOTLOADER(mode[0])) {
				TS_LOG_INFO("In bootloader mode\n");
				return NO_ERR;
			} else {
				TS_LOG_ERR("NOT in bootloader mode!mode[0] = %d, i = %d\n", mode[0], i);
				cypress_soft_reset();
				rc = -EIO;
			}
		}
		msleep(200);
	}

	return rc;
}

/*   cypress_reset_checkout_bl
*    this function must assure goto bootloader mode. if it return false, any other methods are useless and the tp can't work. 
*/
static int cypress_goto_bl(void)
{
	int rc = 0;

	cypress_hw_reset();
	rc = cypress_checkout_bl();
	if (!rc) {
		return NO_ERR;
	}

	cypress_power_on_reset();
	cypress_hw_reset();
	rc = cypress_checkout_bl();
	if (!rc) {
		return NO_ERR;
	}

	return rc;
}

static int cypress_suspend()
{
	int rc= NO_ERR;
	u8 reg_addr = CY_REG_BASE;
	u8 mode = 0;

	input_mt_sync(core_data.input);
	input_sync(core_data.input);

	/*not suspend during updating the fw*/
	if (core_data.process_state == CY_STATE_FW_UPDATE) {
		TS_LOG_INFO("not suspend during updating the fw\n");
		goto out;
	}

	rc = cypress_i2c_read(&reg_addr, sizeof(reg_addr), &mode, sizeof(mode));
	if (rc) {
		TS_LOG_ERR("Fail read mode r=%d\n", rc);
		goto out;
	}
	mode |= CY_HST_SLEEP;
	rc = cypress_i2c_write(reg_addr, &mode, sizeof(mode));
	if (rc) {
		TS_LOG_ERR("Fail write mode r=%d\n", rc);
		goto out;
	}
	TS_LOG_INFO("write DEEP SLEEP succeeded\n");

	/* Give time to FW to sleep */
	msleep(50);
	rc = NO_ERR;

out:
	return rc;
}

static void cypress_shutdown(void)
{
	if(core_data.sysinfo.xy_mode)
		kfree(core_data.sysinfo.xy_mode);
	if(core_data.sysinfo.xy_data)
		kfree(core_data.sysinfo.xy_data);
	return;
}

static int cypress_get_glove_switch(u8 *glove_switch)
{
	int rc = NO_ERR;
	int retval = 0;
	u8 read_cmd_buf[CY_CMD_OP_GET_PARA_CMD_SZ] = {0};
	u8 read_return_buf[CY_CMD_OP_GET_PARA_RET_SZ] = {0};

	read_cmd_buf[0] = CY_CMD_OP_GET_PARA;
	read_cmd_buf[1] = CY_OP_PARA_SCAN_TYPE;
	rc = cypress_exec_cmd(CY_HST_OPERATE,
				read_cmd_buf, sizeof(read_cmd_buf),
				read_return_buf, sizeof(read_return_buf));
	if (rc < 0) {
		TS_LOG_ERR("exec cmd error\n");
		goto out;
	}

	TS_LOG_INFO("return_buf=0x%x,0x%x,0x%x\n", read_return_buf[0], read_return_buf[1], read_return_buf[2]);
	if (read_return_buf[0] != CY_OP_PARA_SCAN_TYPE) {
		TS_LOG_ERR("return data error: read_return_buf[0] = %d\n", read_return_buf[0]);
		rc= -EINVAL;
		goto out;
	}

	retval = read_return_buf[2];

	if (retval == 0) {
		*glove_switch = 0;
	} else if (retval == 136) {
		*glove_switch = 1;
	} else {
		TS_LOG_ERR("retval = %d\n", retval);
		rc = -EFAULT;
		goto out;
	}
out:
	return rc;
}

static int cypress_set_glove_switch(u8 glove_switch)
{
	int rc = NO_ERR;
	u8 write_cmd_buf[CY_CMD_OP_SET_PARA_CMD_SZ];
	u8 write_return_buf[CY_CMD_OP_SET_PARA_RET_SZ] = {0};
	u8 scan_type;

	switch (glove_switch) {
		case CY_SIGNAL_DISPARITY_NONE:
			core_data.opmode = OPMODE_FINGER;
			scan_type = CY_OP_PARA_SCAN_TYPE_APAMC_MASK;
			break;
		case CY_SIGNAL_DISPARITY_SENSITIVITY:
			core_data.opmode = OPMODE_GLOVE;
			scan_type = CY_OP_PARA_SCAN_TYPE_APAMC_MASK |
			CY_OP_PARA_SCAN_TYPE_GLOVE_MASK;
			break;
		case CY_SIGNAL_DISPARITY_STYLUS:
			scan_type = CY_OP_PARA_SCAN_TYPE_APAMC_MASK |
			CY_OP_PARA_SCAN_TYPE_STYLUS_MASK;
			break;
		default:
			TS_LOG_ERR("Invalid signal status=%d\n", 	(int)glove_switch);
			rc = -EINVAL;
			goto out;
	}

	write_cmd_buf[0] = CY_CMD_OP_SET_PARA;
	write_cmd_buf[1] = CY_OP_PARA_SCAN_TYPE;
	write_cmd_buf[2] = CY_OP_PARA_SCAN_TYPE_SZ;
	write_cmd_buf[3] = scan_type;
	rc = cypress_exec_cmd(CY_HST_OPERATE, write_cmd_buf, sizeof(write_cmd_buf),
				write_return_buf, sizeof(write_return_buf));
	if (rc < 0) {
		TS_LOG_ERR("exec cmd error. %d\n", rc);
		goto out;
	}
	TS_LOG_INFO("return_buf=0x%x,0x%x\n",write_return_buf[0],write_return_buf[1]);

out:
	return rc;
}

static int cypress_glove_switch(struct ts_glove_info *info)
{
	int rc = NO_ERR;

	switch (info->op_action){
		case TS_ACTION_WRITE:
			rc = cypress_set_glove_switch(info->glove_switch);
			if(rc < 0){
				TS_LOG_ERR("set glove switch(%d), failed : %d", info->glove_switch, rc);
			}
			break;
		case TS_ACTION_READ:
			rc = cypress_get_glove_switch(&info->glove_switch);
			if(rc < 0){
				TS_LOG_ERR("get glove switch(%d), failed : %d", info->glove_switch, rc);
			}
			break;
		default:
			TS_LOG_ERR("invalid switch status: %d", info->glove_switch);
			rc = -EINVAL;
			break;
	}

	return rc;
}

static int cypress_set_holster_switch(u8 holster_switch)
{
	int rc = NO_ERR;
	u8 write_cmd_buf[CY_CMD_OP_SET_PARA_CMD_SZ];
	u8 write_return_buf[CY_CMD_OP_SET_PARA_RET_SZ] = {0};
	u8 holster_type;

	switch (holster_switch) {
		case CY_HOLSTER_OFF_LOW:
			TS_LOG_DEBUG("to set holster low\n");
			holster_type = CY_OP_PARA_HOLSTER_COM_OFF;
			break;
		case CY_HOLSTER_ON_HIGH:
			TS_LOG_DEBUG("to set holster high\n");
			holster_type = CY_OP_PARA_HOLSTER_COM_ON;
			break;
		default:
			TS_LOG_ERR("Invalid signal status=%d\n",(int)holster_switch);
			rc = -EINVAL;
			goto out;
	}
	write_cmd_buf[0] = CY_CMD_OP_SET_PARA;
	write_cmd_buf[1] = CY_OP_PARA_HOLSTER;
	write_cmd_buf[2] = CY_OP_PARA_SCAN_TYPE_SZ;
	write_cmd_buf[3] = holster_type;
	rc = cypress_exec_cmd(CY_HST_OPERATE, write_cmd_buf, sizeof(write_cmd_buf),
				write_return_buf, sizeof(write_return_buf));

    if (rc < 0) {
		TS_LOG_ERR("exec cmd error. %d\n", rc);
		goto out;
    }
	TS_LOG_DEBUG("return_buf=0x%x,0x%x\n",write_return_buf[0],write_return_buf[1]);

out:
	return rc;
}

static int cypress_holster_switch(struct ts_holster_info *info)
{
	int rc = NO_ERR;

	switch (info->op_action) {
		case TS_ACTION_WRITE:
			rc = cypress_set_holster_switch(info->holster_switch);
			if (rc < 0) {
				TS_LOG_ERR("set holster switch(%d), failed : %d", info->holster_switch, rc);
			}
			break;
		default:
			TS_LOG_ERR("invalid  holster switch status: %d", info->holster_switch);
			rc = -EINVAL;
			break;
	}

	return rc;
}

static int cypress_hand_detect(struct ts_hand_info *info)
{
	int rc = NO_ERR;
	u8 cmd_buf[CY_CMD_OP_HAND_DETECT_CMD_SZ] = {0};
	u8 return_buf[CY_CMD_OP_HAND_DETECT_RET_SZ] = {0};

	/*init*/
	cmd_buf[0] = HANDEDNESS_DETECTION_INIT;
	rc = cypress_exec_cmd(CY_HST_OPERATE, cmd_buf, sizeof(cmd_buf),
			return_buf, sizeof(return_buf));
	if (rc < 0) {
		TS_LOG_ERR("send execute handness_detection init command fail!\n");
		goto err;
	}

	/*retrieve data*/
	cmd_buf[0] = HANDEDNESS_DETECTION;
	rc = cypress_exec_cmd(CY_HST_OPERATE,
			cmd_buf, sizeof(cmd_buf),
			return_buf, sizeof(return_buf));
	if (rc < 0) {
		TS_LOG_ERR("send execute handness_detection command fail!\n");
		goto err;
	}

	info->hand_value = return_buf[0];
	info->status = 1;
	return NO_ERR;
err:
	info->status = 0;
	return rc;
}

static int cypress_resume()
{
	int rc = NO_ERR;
	int i;

	/*not suspend during updating the fw*/
	if (core_data.process_state == CY_STATE_FW_UPDATE) {
		TS_LOG_INFO("not resume during updating the fw\n");
		goto out;
	}

	TS_LOG_INFO("wake up ...\n");
	/*sending a negative pluse 2ms will wake up touchic*/
	rc = gpio_direction_output(core_data.cypress_chip_data->irq_gpio, 0);
	if (rc < 0) {
		TS_LOG_ERR("Fail set output irq gpio=%d\n", core_data.cypress_chip_data->irq_gpio);
		goto out;
	} else {
		udelay(2000);
		rc = gpio_direction_input(core_data.cypress_chip_data->irq_gpio);
		if (rc < 0) {
			TS_LOG_ERR("Fail set input irq gpio=%d\n", core_data.cypress_chip_data->irq_gpio);
			goto out;
		}
		TS_LOG_INFO("HW power up succeeds, gpio=%d\n", core_data.cypress_chip_data->irq_gpio);
	}

	for (i=0; i < I2C_RW_TRIES-1; i++) {
		msleep(20);
		rc = check_hst_mode(CY_HST_OPERATE);
		if (rc < 0) {
			TS_LOG_ERR("goto CY_HST_OPERATE failed[%d], check again\n", i);
		} else {
			break;
		}
	}

out:
	return rc;
}

static inline int cypress_bits_to_bytes(int nbits, int *max)
{
	*max = 1 << nbits;
	return (nbits + 7) / 8;
}

static inline size_t merge_bytes(u8 high, u8 low)
{
	return (high << 8) + low;
}

static int cypress_chip_get_info(struct ts_chip_info_param *info)
{
	TS_LOG_INFO("in\n");

	memcpy(info->ic_vendor, CY_CHIP_INFO, strlen(CY_CHIP_INFO));
	snprintf(info->fw_vendor, sizeof(info->fw_vendor),
			"0x%x", core_data.sysinfo.ttconfig.version);

	return NO_ERR;
}

static int cypress_sysinfo_offsets(void)
{
	int rc = 0;
	u8 reg_addr = CY_REG_BASE;

	rc = cypress_i2c_read(&reg_addr, sizeof(reg_addr), (u8 *)&core_data.sysinfo.sysinfo_data, sizeof(core_data.sysinfo.sysinfo_data));
	if (rc < 0) {
		TS_LOG_ERR("failed to read HST_MODE register, rc = %d\n", rc);
		return rc;
	}
	/* convert sysinfo data offset bytes into integers */
	core_data.sysinfo.sysinfo_merged_data.map_sz = merge_bytes(core_data.sysinfo.sysinfo_data.map_szh, core_data.sysinfo.sysinfo_data.map_szl);
	core_data.sysinfo.sysinfo_merged_data.cydata_ofs = merge_bytes(core_data.sysinfo.sysinfo_data.cydata_ofsh, core_data.sysinfo.sysinfo_data.cydata_ofsl);
	core_data.sysinfo.sysinfo_merged_data.test_ofs = merge_bytes(core_data.sysinfo.sysinfo_data.test_ofsh, core_data.sysinfo.sysinfo_data.test_ofsl);
	core_data.sysinfo.sysinfo_merged_data.pcfg_ofs = merge_bytes(core_data.sysinfo.sysinfo_data.pcfg_ofsh, core_data.sysinfo.sysinfo_data.pcfg_ofsl);
	core_data.sysinfo.sysinfo_merged_data.opcfg_ofs = merge_bytes(core_data.sysinfo.sysinfo_data.opcfg_ofsh, core_data.sysinfo.sysinfo_data.opcfg_ofsl);
	core_data.sysinfo.sysinfo_merged_data.ddata_ofs = merge_bytes(core_data.sysinfo.sysinfo_data.ddata_ofsh, core_data.sysinfo.sysinfo_data.ddata_ofsl);
	core_data.sysinfo.sysinfo_merged_data.mdata_ofs = merge_bytes(core_data.sysinfo.sysinfo_data.mdata_ofsh, core_data.sysinfo.sysinfo_data.mdata_ofsl);

	TS_LOG_DEBUG("cydata_ofs:0x%4x, test_ofs:0x%4x, pcfg_ofs:0x%x, opcfg_ofs:0x%x, ddata_ofs:0x%x, mdata_ofs:0x%x\n",core_data.sysinfo.sysinfo_merged_data.cydata_ofs,
		core_data.sysinfo.sysinfo_merged_data.test_ofs, core_data.sysinfo.sysinfo_merged_data.pcfg_ofs, core_data.sysinfo.sysinfo_merged_data.opcfg_ofs,
		core_data.sysinfo.sysinfo_merged_data.ddata_ofs, core_data.sysinfo.sysinfo_merged_data.mdata_ofs);

	return rc;
}

static int cypress_sysinfo_test(void)
{
	int rc = 0;
	size_t test_size;
	struct cypress_test *test;

	/*test_size is size of test data*/
	TS_LOG_DEBUG("pcfg_ofs = 0x%x, test_ofs = 0x%x\n", core_data.sysinfo.sysinfo_merged_data.pcfg_ofs,
				core_data.sysinfo.sysinfo_merged_data.test_ofs);
	test_size = core_data.sysinfo.sysinfo_merged_data.pcfg_ofs - core_data.sysinfo.sysinfo_merged_data.test_ofs;
	test = kzalloc(test_size, GFP_KERNEL);
	if (test == NULL) {
		TS_LOG_ERR("Failed to alloc test memory, test_size = %d\n", test_size);
		rc = -ENOMEM;
		goto out;
	}

	rc = cypress_i2c_read((u8 *)&core_data.sysinfo.sysinfo_merged_data.test_ofs, 1, (u8 *)test, test_size);
	if (rc < 0) {
		TS_LOG_ERR("Failed to read test data, rc = %d\n", rc);
		goto free_test;
	}
	core_data.sysinfo.test.post_codeh = test->post_codeh;
	core_data.sysinfo.test.post_codel = test->post_codel;

	TS_LOG_DEBUG("post_codeh:0x%x, post_codel:0x%x\n", core_data.sysinfo.test.post_codeh,
			core_data.sysinfo.test.post_codel);

free_test:
	kfree(test);
out:
	return rc;
}
static int cypress_sysinfo_cydata(void)
{
	int rc = 0;
	int i;
	int mfgid_size;
	size_t cydata_size;
	u8 *buf;
	struct cypress_cydata *cydata;

	/* Allocate a temp buffer for reading CYDATA registers, cydata_size is the size of CYDATA.
	    CYDATA including some version information*/
	TS_LOG_DEBUG("test_ofs = 0x%x, cydata_ofs = 0x%x\n", core_data.sysinfo.sysinfo_merged_data.test_ofs,
				core_data.sysinfo.sysinfo_merged_data.cydata_ofs);
	cydata_size = core_data.sysinfo.sysinfo_merged_data.test_ofs - core_data.sysinfo.sysinfo_merged_data.cydata_ofs;

	buf = kzalloc(cydata_size, GFP_KERNEL);
	if (buf == NULL) {
		TS_LOG_ERR("Failed to alloc cydata buffer(null), cydata_size = %d\n", cydata_size);
		rc =  -ENOMEM;
		goto out;
	}

	/* Read the CYDA registers to the temp buf */
	rc = cypress_i2c_read((u8 *)&core_data.sysinfo.sysinfo_merged_data.cydata_ofs, 1, buf, cydata_size);
	if (rc < 0) {
		TS_LOG_ERR("Failed to read cydata, rc = %d\n", rc);
		goto free_buf;
	}
	cydata = (struct cypress_cydata *)buf;
	/* Copy all fields up to MFGID to local cydata structure */
	core_data.sysinfo.cydata.ttpidh = cydata->ttpidh;
	core_data.sysinfo.cydata.ttpidl = cydata->ttpidl;
	core_data.sysinfo.cydata.fw_ver_major = cydata->fw_ver_major;
	core_data.sysinfo.cydata.fw_ver_minor = cydata->fw_ver_minor;
	for(i = 0; i < CY_NUM_REVCTRL; i++){
		core_data.sysinfo.cydata.revctrl[i] = cydata->revctrl[i];
	}
	core_data.sysinfo.cydata.blver_major = cydata->blver_major;
	core_data.sysinfo.cydata.blver_minor = cydata->blver_minor;
	core_data.sysinfo.cydata.jtag_si_id3 = cydata->jtag_si_id3;
	core_data.sysinfo.cydata.jtag_si_id2 = cydata->jtag_si_id2;
	core_data.sysinfo.cydata.jtag_si_id1 = cydata->jtag_si_id1;
	core_data.sysinfo.cydata.jtag_si_id0 = cydata->jtag_si_id0;
	core_data.sysinfo.cydata.mfgid_sz = cydata->mfgid_sz;

	mfgid_size = core_data.sysinfo.cydata.mfgid_sz;
	core_data.sysinfo.cydata.cyito_idh = buf[19 + mfgid_size];
	core_data.sysinfo.cydata.cyito_idl = buf[19 + mfgid_size +1];
	core_data.sysinfo.cydata.cyito_verh = buf[19 + mfgid_size +2];
	core_data.sysinfo.cydata.cyito_verl = buf[19 + mfgid_size +3];
	core_data.sysinfo.cydata.ttsp_ver_major = buf[19 + mfgid_size +4];
	core_data.sysinfo.cydata.ttsp_ver_minor = buf[19 + mfgid_size +5];
	core_data.sysinfo.cydata.device_info = buf[19 + mfgid_size +6];

	TS_LOG_DEBUG("ttpidh:0x%x, ttpidl:0x%x\n", core_data.sysinfo.cydata.ttpidh, core_data.sysinfo.cydata.ttpidl);
	TS_LOG_DEBUG("fw_ver_major:0x%x, fw_ver_minor:0x%x\n", core_data.sysinfo.cydata.fw_ver_major, core_data.sysinfo.cydata.fw_ver_minor);
	for(i = 0; i < CY_NUM_REVCTRL; i++){
		TS_LOG_DEBUG("revctrl[%d]:0x%x\n",i, core_data.sysinfo.cydata.revctrl[i]);
	}
	TS_LOG_DEBUG("blver_major:0x%x, blver_minor:0x%x\n",core_data.sysinfo.cydata.blver_major, core_data.sysinfo.cydata.blver_minor);
	TS_LOG_DEBUG("jtag_si_id[3-0]:0x%x, 0x%x, 0x%x, 0x%x\n", core_data.sysinfo.cydata.jtag_si_id3, core_data.sysinfo.cydata.jtag_si_id2,
		core_data.sysinfo.cydata.jtag_si_id1,core_data.sysinfo.cydata.jtag_si_id0);
	TS_LOG_DEBUG("mfgid_sz:0x%x\n", core_data.sysinfo.cydata.mfgid_sz);
	TS_LOG_DEBUG("cyito_idh:0x%x, cydata.cyito_idl:0x%x\n", core_data.sysinfo.cydata.cyito_idh, core_data.sysinfo.cydata.cyito_idl);
	TS_LOG_DEBUG("cyito_verh:0x%x, cydata.cyito_verl:0x%x\n", core_data.sysinfo.cydata.cyito_verh, core_data.sysinfo.cydata.cyito_verl);
	TS_LOG_DEBUG("ttsp_ver_major:0x%x, ttsp_ver_minor:0x%x\n",core_data.sysinfo.cydata.ttsp_ver_major, core_data.sysinfo.cydata.ttsp_ver_minor);
	TS_LOG_DEBUG("device_info:0x%x\n",core_data.sysinfo.cydata.device_info);

free_buf:
	kfree(buf);
out:
	return rc;
}

static int cypress_sysinfo_pcfg(void)
{
	int rc = 0;
	size_t pcfg_size;
	struct cypress_pcfg *pcfg;

	TS_LOG_DEBUG("opcfg_ofs = 0x%x, pcfg_ofs = 0x%x\n", core_data.sysinfo.sysinfo_merged_data.opcfg_ofs,
				core_data.sysinfo.sysinfo_merged_data.pcfg_ofs);
	pcfg_size = core_data.sysinfo.sysinfo_merged_data.opcfg_ofs - core_data.sysinfo.sysinfo_merged_data.pcfg_ofs;
	pcfg = kzalloc(pcfg_size, GFP_KERNEL);
	if (pcfg == NULL) {
		TS_LOG_ERR("Failed alloc pcfg memory rc = %d\n", rc);
		return -ENOMEM;
	}
	rc = cypress_i2c_read((u8 *)&core_data.sysinfo.sysinfo_merged_data.pcfg_ofs, 1, (u8 *)pcfg, pcfg_size);
	if (rc < 0) {
		TS_LOG_ERR("Failed read cydata rc = %d\n", rc);
		goto out;
	}
	core_data.sysinfo.sysinfo_merged_data.max_x = merge_bytes((pcfg->res_xh & CY_PCFG_RESOLUTION_X_Y_MASK), pcfg->res_xl);
	core_data.sysinfo.sysinfo_merged_data.x_origin = !!(pcfg->res_xh & CY_PCFG_ORIGIN_X_Y_MASK);
	core_data.sysinfo.sysinfo_merged_data.max_y = merge_bytes((pcfg->res_yh & CY_PCFG_RESOLUTION_X_Y_MASK), pcfg->res_yl);
	core_data.sysinfo.sysinfo_merged_data.y_origin = !!(pcfg->res_yh & CY_PCFG_ORIGIN_X_Y_MASK);
	core_data.sysinfo.sysinfo_merged_data.max_p = merge_bytes(pcfg->max_zh, pcfg->max_zl);
	core_data.sysinfo.pcfg.electrodes_x = pcfg->electrodes_x;
	core_data.sysinfo.pcfg.electrodes_y = pcfg->electrodes_y;

	TS_LOG_DEBUG("electrodes_x:%d,electrodes_y:%d\n", pcfg->electrodes_x,pcfg->electrodes_y);
	TS_LOG_DEBUG("pcfg_size:%d\n", pcfg_size);
	TS_LOG_DEBUG("max_x:0x%04X\n", core_data.sysinfo.sysinfo_merged_data.max_x);
	TS_LOG_DEBUG("x_origin:%d (%s)\n", core_data.sysinfo.sysinfo_merged_data.x_origin,
		core_data.sysinfo.sysinfo_merged_data.x_origin == CY_NORMAL_ORIGIN ? "left corner" : "right corner");
	TS_LOG_DEBUG("max_y:0x%04X\n", core_data.sysinfo.sysinfo_merged_data.max_y);
	TS_LOG_DEBUG("y_origin:%d (%s)\n", core_data.sysinfo.sysinfo_merged_data.y_origin,
		core_data.sysinfo.sysinfo_merged_data.y_origin == CY_NORMAL_ORIGIN ? "upper corner" : "lower corner");
	TS_LOG_DEBUG("max_p:0x%04X\n", core_data.sysinfo.sysinfo_merged_data.max_p);

out:
	kfree(pcfg);
	return rc;
}

static int cypress_sysinfo_opcfg(void)
{
	int rc = 0;
	size_t opcfg_size;
	enum cypress_tch_abs abs;
	struct cypress_opcfg *opcfg;

	TS_LOG_DEBUG("ddata_ofs = 0x%x, opcfg_ofs = 0x%x\n",
				core_data.sysinfo.sysinfo_merged_data.ddata_ofs,
				core_data.sysinfo.sysinfo_merged_data.opcfg_ofs);
	opcfg_size = core_data.sysinfo.sysinfo_merged_data.ddata_ofs - core_data.sysinfo.sysinfo_merged_data.opcfg_ofs;
	opcfg = kzalloc(opcfg_size, GFP_KERNEL);
	if (opcfg == NULL) {
		TS_LOG_ERR("Failed to alloc opcfg memory, opcfg_size = %d\n", opcfg_size);
		rc = -ENOMEM;
		goto out;
	}

	rc = cypress_i2c_read((u8 *)&core_data.sysinfo.sysinfo_merged_data.opcfg_ofs, 1, (u8 *)opcfg, opcfg_size);
	if (rc < 0) {
		TS_LOG_ERR("Failed to read cydata rc = %d\n", rc);
		goto free_opcfg;
	}

	core_data.sysinfo.sysinfo_merged_data.cmd_ofs = opcfg->cmd_ofs;
	core_data.sysinfo.sysinfo_merged_data.rep_ofs = opcfg->rep_ofs;
	core_data.sysinfo.sysinfo_merged_data.rep_sz = merge_bytes(opcfg->rep_szh, opcfg->rep_szl);
	core_data.sysinfo.sysinfo_merged_data.tt_stat_ofs = opcfg->tt_stat_ofs;
	core_data.sysinfo.sysinfo_merged_data.max_tchs = opcfg->max_tchs & CY_BYTE_OFS_MASK;
	core_data.sysinfo.sysinfo_merged_data.tch_rec_size = opcfg->tch_rec_size & CY_BYTE_OFS_MASK;

	/* Get the old touch fields , opcfg->tch_rec_old[abs].size (bits), 7 touch type, x, y, z, touch id ...*/
	for (abs = CY_TCH_X; abs < CY_NUM_TCH_FIELDS; abs++) {
		core_data.sysinfo.sysinfo_merged_data.tch_abs[abs].ofs = opcfg->tch_rec_old[abs].loc & CY_BYTE_OFS_MASK;
		core_data.sysinfo.sysinfo_merged_data.tch_abs[abs].size
			= cypress_bits_to_bytes(opcfg->tch_rec_old[abs].size, &core_data.sysinfo.sysinfo_merged_data.tch_abs[abs].max);
		core_data.sysinfo.sysinfo_merged_data.tch_abs[abs].bofs = (opcfg->tch_rec_old[abs].loc & CY_BOFS_MASK) >> CY_BOFS_SHIFT;
	}
	core_data.sysinfo.sysinfo_merged_data.mode_size = core_data.sysinfo.sysinfo_merged_data.tt_stat_ofs + 1;
	core_data.sysinfo.sysinfo_merged_data.data_size = core_data.sysinfo.sysinfo_merged_data.max_tchs * opcfg->tch_rec_size; //contain all touch recoard data. for xy_data alloc.

	for (abs = 0; abs < CY_TCH_NUM_ABS; abs++) {
		TS_LOG_DEBUG("tch_rec_%s\n", cypress_tch_abs_string[abs]);
		TS_LOG_DEBUG("ofs =%2d\n", core_data.sysinfo.sysinfo_merged_data.tch_abs[abs].ofs);
		TS_LOG_DEBUG("siz =%2d\n", core_data.sysinfo.sysinfo_merged_data.tch_abs[abs].size);
		TS_LOG_DEBUG("max =%2d\n",core_data.sysinfo.sysinfo_merged_data.tch_abs[abs].max);
		TS_LOG_DEBUG("bofs=%2d\n",core_data.sysinfo.sysinfo_merged_data.tch_abs[abs].bofs);
	}

	TS_LOG_DEBUG("cmd_ofs =%4d\n", core_data.sysinfo.sysinfo_merged_data.cmd_ofs);
	TS_LOG_DEBUG("rep_ofs =%4d\n", core_data.sysinfo.sysinfo_merged_data.rep_ofs);
	TS_LOG_DEBUG("rep_sz =%4d\n", core_data.sysinfo.sysinfo_merged_data.rep_sz);
	TS_LOG_DEBUG("tt_stat_ofs =%4d\n", core_data.sysinfo.sysinfo_merged_data.tt_stat_ofs);
	TS_LOG_DEBUG("tch_rec_size =%4d\n", core_data.sysinfo.sysinfo_merged_data.tch_rec_size);
	TS_LOG_DEBUG("max_tchs =%4d\n", core_data.sysinfo.sysinfo_merged_data.max_tchs);
	TS_LOG_DEBUG("mode_size =%4d\n", core_data.sysinfo.sysinfo_merged_data.mode_size);
	TS_LOG_DEBUG("data_size =%4d\n", core_data.sysinfo.sysinfo_merged_data.data_size);

free_opcfg:
	kfree(opcfg);
out:
	return rc;
}

static int cypress_sysinfo_memory_alloc(void)
{
	int rc = 0;
	TS_LOG_DEBUG("xy_mode_size = %d, xy_data_size = %d\n", core_data.sysinfo.sysinfo_merged_data.mode_size,
			core_data.sysinfo.sysinfo_merged_data.data_size);
	core_data.sysinfo.xy_mode = kzalloc(core_data.sysinfo.sysinfo_merged_data.mode_size, GFP_KERNEL);
       if (core_data.sysinfo.xy_mode == NULL){
	   	TS_LOG_ERR("Failed to alloc memory for xy_mode, size is %d\n", core_data.sysinfo.sysinfo_merged_data.mode_size);
		return -1;
       }
       core_data.sysinfo.xy_data = kzalloc(core_data.sysinfo.sysinfo_merged_data.data_size, GFP_KERNEL);
       if (core_data.sysinfo.xy_data == NULL){
	   	TS_LOG_ERR("Failed to alloc memory for xy_data, size is %d\n", core_data.sysinfo.sysinfo_merged_data.data_size);
		rc = -1;
	   	goto err;
       }
	TS_LOG_DEBUG("xy_mode=%p xy_data=%p\n", core_data.sysinfo.xy_mode, core_data.sysinfo.xy_data);

	rc = NO_ERR;
	goto out;

err:
	kfree(core_data.sysinfo.xy_mode);
out:
       return rc;
}

static int cypress_switch_to_operate(void)
{
	int rc = NO_ERR;
	int i;

	for (i = 0; i <  I2C_RW_TRIES; i++) {
		rc = set_hst_mode(CY_HST_OPERATE);
		if (rc < 0) {
			TS_LOG_ERR("failed to set mode to Operational rc = %d\n", rc);
			continue;
		}
		msleep(2);
		rc = check_hst_mode(CY_HST_OPERATE);
		if (rc < 0) {
			TS_LOG_ERR("check operate failed, try again, rc = %d, i = %d\n", rc, i);
		} else {
			TS_LOG_INFO("operate mode\n");
			return NO_ERR;
		}
	}

	return rc;
}

static int cypress_get_sysinfo_regs(void)
{
	int rc = 0;

	rc = cypress_sysinfo_offsets();
	if (rc < 0) {
		TS_LOG_ERR("Failed to get sysinfo offsets, rc = %d\n", rc);
		return rc;
	}
	rc = cypress_sysinfo_cydata();			//some version information
	if (rc < 0){
		TS_LOG_ERR("Failed to get sysinfo cydata, rc = %d\n", rc);
		return rc;
	}
	rc = cypress_sysinfo_test();
	if(rc < 0){
		TS_LOG_ERR("Failed to get sysinfo test, rc = %d\n", rc);
		return rc;
	}
	rc = cypress_sysinfo_pcfg();
	if (rc < 0){
		TS_LOG_ERR("Failed to get sysinfo pcfg, rc = %d\n", rc);
		return rc;
	}
	/*operational mode offset*/
	rc = cypress_sysinfo_opcfg();
	if (rc < 0) {
		TS_LOG_ERR("Failed to get sysinfo opcfg, rc = %d\n", rc);
		return rc;
	}
       rc = cypress_sysinfo_memory_alloc();
       if (rc < 0) {
               TS_LOG_ERR("Failed to alloc memory, rc = %d\n", rc);
               return rc;
       }
	/* provide flow control handshake */
	rc = cypress_handshake(core_data.sysinfo.sysinfo_data.hst_mode);
	if (rc < 0)
		TS_LOG_ERR("handshake fail on sysinfo reg, rc = %d\n", rc);

	return rc;
}
static u16 cypress_calc_partial_app_crc(const u8 *data, int size, u16 crc)
{
	int i, j;

	for (i = 0; i < size; i++) {
		crc ^= ((u16)data[i] << 8);
		for (j = 8; j > 0; j--)
			if (crc & 0x8000)
				crc = (crc << 1) ^ 0x1021;
			else
				crc <<= 1;
	}
	return crc;
}

static int cypress_read_config_block(u8 ebid, u16 row, u8 *data, u16 length)
{
	u8 command_buf[6];
	u8 *return_buf;
	u16 crc;
	int rc;

	TS_LOG_DEBUG("ebid = %d, row = %d, data = %p, length = %d\n", ebid, row, data, length);
	/* Allocate buffer for read config block command response Header(5) + Data(length) + CRC(2) */
	return_buf = kmalloc(length + 7, GFP_KERNEL);
	if (!return_buf) {
		TS_LOG_ERR("Cannot allocate buffer, buffer size = %d\n", length + 7);
		rc = -ENOMEM;
		goto exit;
	}

	command_buf[0] = CY_CMD_CAT_READ_CFG_BLK;
	command_buf[1] = HI_BYTE(row);
	command_buf[2] = LO_BYTE(row);
	command_buf[3] = HI_BYTE(length);
	command_buf[4] = LO_BYTE(length);
	command_buf[5] = ebid;

	rc = cypress_exec_cmd(CY_HST_CAT, command_buf, 6, return_buf, length + 7);
	if (rc) {
		TS_LOG_ERR("Error executing command r=%d\n", rc);
		goto free_buffer;
	}

	crc = cypress_calc_partial_app_crc(&return_buf[5], length, 0xFFFF);
	/* Validate response */
	if (return_buf[0] != CY_CMD_STATUS_SUCCESS
			|| return_buf[1] != ebid
			|| return_buf[2] != HI_BYTE(length)
			|| return_buf[3] != LO_BYTE(length)
			|| return_buf[5 + length] != HI_BYTE(crc)
			|| return_buf[6 + length] != LO_BYTE(crc)) {
		TS_LOG_ERR("Fail executing command\n");
		rc = -1;
		goto free_buffer;
	}

	memcpy(data, &return_buf[5], length);

free_buffer:
	kfree(return_buf);
exit:
	return rc;
}

static int cypress_get_ttconfig_version(u16 *version)
{
	u8 data[CY_TTCONFIG_OFFSET + 2];
	int rc;

	rc = cypress_read_config_block(CY_TCH_PARM_EBID, 0, data, CY_TTCONFIG_OFFSET + 2);
	if (rc) {
		TS_LOG_ERR("Error on read config block\n");
		goto exit;
	}

	if (IS_LITTLEENDIAN(core_data.sysinfo.cydata.device_info))
		*version = get_unaligned_le16(&data[CY_TTCONFIG_OFFSET]);
	else
		*version = get_unaligned_be16(&data[CY_TTCONFIG_OFFSET]);

	TS_LOG_DEBUG("version = %d\n", *version);

exit:
	return rc;
}

static int cypress_get_config_length(u8 ebid, u16 *length, u16 *max_length)
{
	u8 data[4];
	int rc;

	rc = cypress_read_config_block(ebid, 0, data, 4);
	if (rc) {
		TS_LOG_ERR("Error on read config block\n");
		goto exit;
	}

	if (IS_LITTLEENDIAN(core_data.sysinfo.cydata.device_info)) {
		*length = get_unaligned_le16(&data[0]);
		*max_length = get_unaligned_le16(&data[2]);
	} else {
		*length = get_unaligned_be16(&data[0]);
		*max_length = get_unaligned_be16(&data[2]);
	}

exit:
	return rc;
}

static int cypress_get_config_block_crc(u8 ebid, u16 *crc)
{
	u8 command_buf[2] = {0};
	u8 return_buf[3] = {0};
	int rc;

	TS_LOG_DEBUG("ebid = %d\n", ebid);
	command_buf[0] = CY_CMD_OP_GET_CRC;
	command_buf[1] = ebid;

	rc = cypress_exec_cmd(CY_HST_OPERATE, command_buf, 2, return_buf, 3);
	if (rc) {
		TS_LOG_ERR("Error executing command r=%d\n", rc);
		return rc;
	}
	/* Validate response */
	if (return_buf[0] != CY_CMD_STATUS_SUCCESS) {
		TS_LOG_ERR("Fail executing command, return_buf[0] = %d\n", return_buf[0]);
		return -1;;
	}

	*crc = get_unaligned_be16(&return_buf[1]);
	TS_LOG_DEBUG("crc = %d\n", *crc);
	return NO_ERR;
}

static int cypress_switch_to_cat(void)
{
	int rc = NO_ERR;
	int i;

	for (i = 0; i < I2C_RW_TRIES; i++) {
		rc = set_hst_mode(CY_HST_CAT);	// there will be a interrupt
		if (rc < 0) {
			TS_LOG_ERR("Failed to set mode to cat rc = %d\n", rc);
			continue;
		}
		msleep(50);
		rc = check_hst_mode(CY_HST_CAT);
		if (rc < 0) {
			TS_LOG_ERR("wrong in cat mode, try again, rc = %d, i = %d\n", rc, i);
		} else {
			TS_LOG_INFO("OK, successfully in cat mode ...\n");
			return NO_ERR;
		}
	}

	return rc;
}

static int cypress_get_ttconfig_info(void)
{
	u16 length = 0;
	u16 max_length = 0;
	u16 version = 0;
	u16 crc = 0;
	int rc = 0;

	rc = cypress_switch_to_cat();
	if (rc < 0) {
		TS_LOG_ERR("failed to set mode to CAT rc = %d\n", rc);
		return rc;
	}

	rc = cypress_get_ttconfig_version(&version);
	if (rc < 0) {
		TS_LOG_ERR("failed to get ttconfig version rc=%d\n", rc);
		return rc;
	}

	rc = cypress_get_config_length(CY_TCH_PARM_EBID, &length, &max_length);
	if (rc < 0) {
		TS_LOG_ERR("failed to get ttconfig length rc=%d\n",rc);
		return rc;
	}

	/* switch to operational mode */
	rc = cypress_switch_to_operate();
	if (rc < 0) {
		TS_LOG_ERR("failed to set mode to Operational rc=%d\n", rc);
		return rc;
	}

	rc = cypress_get_config_block_crc(CY_TCH_PARM_EBID, &crc);
	if (rc < 0) {
		TS_LOG_ERR("failed to get ttconfig crc = %d, rc = %d\n", crc, rc);
		return rc;
	}

	core_data.sysinfo.ttconfig.version = version;
	core_data.sysinfo.ttconfig.length = length;
	core_data.sysinfo.ttconfig.max_length = max_length;
	core_data.sysinfo.ttconfig.crc = crc;

	TS_LOG_DEBUG("TT Config Version:%04X Length:%d Max Length:%d CRC:%04X\n",
		core_data.sysinfo.ttconfig.version, core_data.sysinfo.ttconfig.length,
		core_data.sysinfo.ttconfig.length, core_data.sysinfo.ttconfig.crc);

	return NO_ERR;
}

/*used in sysinfo\CAT\operat mode*/
static int cypress_exec_cmd(u8 mode, u8 *cmd_buf, size_t cmd_size, u8 *return_buf, size_t return_buf_size)
{
	int cmd_ofs;
	u8 command = 0;
	int reg_addr;
	int rc;
	int i;

	TS_LOG_DEBUG("mode = 0x%x\n", mode);
	for (i = 0; i < cmd_size; i++) {
		TS_LOG_DEBUG("cmd_buf[%d] = %d\n", i, cmd_buf[i]);
	}

	switch (mode) {
		case CY_HST_CAT:
			cmd_ofs = CY_REG_CAT_CMD;
			break;
		case CY_HST_OPERATE:
			cmd_ofs = core_data.sysinfo.sysinfo_merged_data.cmd_ofs;
			break;
		default:
			TS_LOG_ERR("Unsupported mode 0x%x for exec cmd\n", mode);
			return -EACCES;
	}

	for(i = 0; i < I2C_RW_TRIES + 2; i++){
		/* Check if complete is set, so write new command */
		rc = cypress_i2c_read((u8 *)&cmd_ofs, 1, &command, sizeof(command));
		if (rc < 0) {
			TS_LOG_ERR("Failed read complete bit rc = %d\n",rc);
			return rc;
		}
		if ((command & CY_CMD_COMPLETE_MASK) == 0) {
			TS_LOG_ERR("some command is not completed yet, i= %d\n", i);
			msleep(1000);
		} else {
			TS_LOG_INFO("command is completed, i =%d\n", i);
			break;
		}
	}
	if (i == I2C_RW_TRIES + 2) {
		TS_LOG_ERR("check cmd failed\n");
		return -EINVAL;
	}
	/*
	 * Write new command
	 * Only update command bits 0:5; Clear command complete bit & toggle bit
	 */
	cmd_buf[0] = cmd_buf[0] & CY_CMD_MASK;
	rc = cypress_i2c_write(cmd_ofs, cmd_buf, cmd_size);
	if (rc < 0) {
		TS_LOG_ERR("Error on write command rc = %d\n", rc);
		return rc;
	}

	msleep(30);
	/* Wait command to be completed */
	for (i = 0; i < I2C_RW_TRIES; i++) {
		rc = check_hst_mode(mode);
		if (rc < 0) {
			TS_LOG_ERR("rc = %d, i = %d\n", rc, i);
		} else {
			if (!core_data.complete_cmd) {
				TS_LOG_ERR("command is not completed, complete_cmd = %d, i =%d\n", core_data.complete_cmd, i);
				msleep(2000);
			}else{
				TS_LOG_INFO("everything is ok, i = %d\n", i);
				break;
			}
		}
	}

	if (return_buf_size == 0 || return_buf == NULL)
		return NO_ERR;

	reg_addr = cmd_ofs + 1;
	rc = cypress_i2c_read((u8 *)&reg_addr, 1, return_buf, return_buf_size);
	if (rc < 0) {
		TS_LOG_ERR("Error on read rc = %d\n", rc);
		return rc;
	}

	for (i = 0; i < return_buf_size; i++) {
		TS_LOG_DEBUG("return_buf[%d] = %d\n", i, return_buf[i]);
	}
	return NO_ERR;
}

static int cypress_set_opmode(void)
{
	u8 cmd_buf[CY_CMD_OP_SET_PARA_CMD_SZ];
	u8 return_buf[CY_CMD_OP_SET_PARA_RET_SZ];
	u8 scan_type = 0;
	int rc = 0;
	TS_LOG_INFO("opmode: 0x%x\n", core_data.opmode);

	switch (core_data.opmode) {
	case OPMODE_NONE:
		return NO_ERR;
	case OPMODE_FINGER:
		scan_type = CY_OP_PARA_SCAN_TYPE_NORMAL;
		break;
	case OPMODE_GLOVE:
		scan_type = CY_OP_PARA_SCAN_TYPE_APAMC_MASK |
				CY_OP_PARA_SCAN_TYPE_GLOVE_MASK;
		break;
	}

	cmd_buf[0] = CY_CMD_OP_SET_PARA;
	cmd_buf[1] = CY_OP_PARA_SCAN_TYPE;
	cmd_buf[2] = CY_OP_PARA_SCAN_TYPE_SZ;
	cmd_buf[3] = scan_type;

	rc = cypress_exec_cmd(CY_HST_OPERATE, cmd_buf, sizeof(cmd_buf), return_buf, sizeof(return_buf));
	if (rc < 0)
		TS_LOG_ERR("exec cmd error.\n");

	return rc;
}

static int set_hst_mode(u8 new_mode)
{
	u8 mode = 0;
	u8 reg_addr = CY_REG_BASE;
	int rc = NO_ERR;
	rc = cypress_i2c_read(&reg_addr, 1, &mode, sizeof(mode));
	if (rc < 0) {
		TS_LOG_ERR("Failed to read mode, rc = %d\n", rc);
		return rc;
	}

	/* Clear device mode bits 4,5,6 and set to new mode, CY_HST_MODE_CHANGE field (bit 3) is used to swtich mode */
	mode &= ~CY_HST_MODE;
	mode |= new_mode | CY_HST_MODE_CHANGE;

	rc = cypress_i2c_write(reg_addr, &mode, sizeof(mode)); //new mode is writen to reg 0x00, after mode switch, there will be a interrupt
	if (rc < 0)
		TS_LOG_ERR("Failed to write mode change, rc = %d, mode(value) = 0x%x\n", rc, mode);

	return rc;
}

/*  query the configure from dts and store in prv_data
*/
static int cypress_parse_config(struct device_node *device, struct ts_device_data *chip_data)
{
	int rc = NO_ERR;
	return rc;
}

static int cypress_exit_bl_into_sysinfo(void)
{
	int rc = 0;
	int i;
	u8 reg_addr = CY_REG_BASE;
	u8 output_packet[sizeof(ldr_err_app)] = {0};

	core_data.force_fw_update = false;
	rc = cypress_i2c_write(reg_addr, (u8 *)ldr_exit, sizeof(ldr_exit));
	if(rc < 0){
		TS_LOG_ERR("Failed to write ldr_exit to 0x00, rc = %d\n", rc);
		return rc;
	}
	msleep(500);

	/*check the output packet*/
	rc = cypress_i2c_read(&reg_addr, sizeof(reg_addr), output_packet, sizeof(output_packet));
	if (rc < 0) {
		TS_LOG_ERR("read output packet failed\n");
		return rc;
	}
	if(0 == memcmp(output_packet, ldr_err_app, sizeof(ldr_err_app))) {
		TS_LOG_ERR("output packet equal to ldr_err_app, force update fw\n");
		core_data.force_fw_update = true;
		return -EINVAL;
	}

	/*check if in sysinfo mode*/
	for (i = 0; i < I2C_RW_TRIES*10; i++) {
		rc = check_hst_mode(CY_HST_SYSINFO);
		if (rc < 0) {
			TS_LOG_DEBUG("not in sysinfo mode, rc = %d, i = %d. wait 200ms read again\n", rc, i);
			msleep(200);
		} else {
			TS_LOG_INFO("In sysinfo mode\n");
			break;
		}
	}
	if (rc<0)
		TS_LOG_ERR("not in sysinfo mode, rc =%d\n", rc);
	return rc;
}

static int cypress_get_status(u8 *buf, int size, unsigned long timeout_ms)
{
	int tries;
	int rc = 0;
	u8 reg_addr = CY_REG_BASE;

	if (timeout_ms != 0) {
		/* TODO: Reconsider purpose of having retries here */
		for (tries = 0; tries < I2C_RW_TRIES; tries++) {
			rc = cypress_i2c_read(&reg_addr, sizeof(reg_addr), buf, size);
			/* retry if bus read error or status byte shows not ready */
			if ((rc < 0) || buf[1] == CY_COMM_BUSY || buf[1] == CY_CMD_BUSY || (buf[0] != CY_START_OF_PACKET))
				msleep(20);
			else
				break;
		}
		TS_LOG_DEBUG("ries=%d rc =%d status=%02X\n", tries, rc, buf[1]);
	}
	return rc;
}

static u16 cypress_compute_crc(u8 *buf, int size)
{
	u16 crc = 0xffff;
	u16 tmp;
	int i;

	if (size == 0)
		crc = ~crc;
	else {

		do {
			for (i = 0, tmp = 0x00ff & *buf++; i < 8;
				i++, tmp >>= 1) {
				if ((crc & 0x0001) ^ (tmp & 0x0001))
					crc = (crc >> 1) ^ 0x8408;
				else
					crc >>= 1;
			}
		} while (--size);

		crc = ~crc;
		tmp = crc;
		crc = (crc << 8) | (tmp >> 8 & 0xFF);
	}

	return crc;
}

static u8 *cypress_get_row(u8 *row_buf, u8 *image_buf, int size)
{
	memcpy(row_buf, image_buf, size);
	image_buf = image_buf + size;
	return image_buf;
}

static u16 cypress_get_short(u8 *buf)
{
	return ((u16)(*buf) << 8) + *(buf+1);
}
static int cypress_ldr_parse_row(u8 *row_buf, struct cypress_hex_image *row_image)
{
	int rc = 0;

	row_image->array_id = row_buf[CY_ARRAY_ID_OFFSET];
	row_image->row_num = cypress_get_short(&row_buf[CY_ROW_NUM_OFFSET]);
	row_image->row_size = cypress_get_short(&row_buf[CY_ROW_SIZE_OFFSET]);
	if (row_image->row_size > ARRAY_SIZE(row_image->row_data)) {
		TS_LOG_ERR("row data buffer overflow\n");
		rc = -1;
		goto out;
	}

	memcpy(row_image->row_data, &row_buf[CY_ROW_DATA_OFFSET], row_image->row_size);

out:
	return rc;
}

static int cypress_get_crc_from_params(u16 *crc)
{
	struct touch_settings *param_regs = &cypress_sett_param_regs;
	u16 crc_loc;

	if (!param_regs || !param_regs->data || !param_regs->size) {
		TS_LOG_INFO("missing param regs for crc check.\n");
		return -1;
	}

	crc_loc = get_unaligned_le16(&param_regs->data[2]);
	*crc = get_unaligned_le16(&param_regs->data[crc_loc]);

	return NO_ERR;
}
static int cypress_check_ttconfig_crc(void)
{
	int rc = 0;
	u16 cfg_crc_new = 0;
	/* Version is equal. Check if config CRC different. */
	rc = cypress_get_crc_from_params(&cfg_crc_new);
	if (rc)
		return 0;

	TS_LOG_INFO("img_crc:0x%04X new_crc:0x%04X\n", core_data.sysinfo.ttconfig.crc, cfg_crc_new);

	if (cfg_crc_new != core_data.sysinfo.ttconfig.crc) {
		TS_LOG_INFO("Config CRC different, will upgrade\n");
		return 1;
	}

	TS_LOG_INFO("Config CRC equal, will NOT upgrade\n");
	return 0;
}
/*
 * return code:
 *  0: Version info same, no upgrade
 *  1: Do a firmware upgrade
 */
static int cypress_check_fw_version(u32 fw_ver_new, u32 fw_revctrl_new_h, u32 fw_revctrl_new_l)
{
	u32 fw_ver_img;
	u32 fw_revctrl_img_h;
	u32 fw_revctrl_img_l;

	fw_ver_img = core_data.sysinfo.cydata.fw_ver_major << 8;
	fw_ver_img += core_data.sysinfo.cydata.fw_ver_minor;

	TS_LOG_DEBUG("img vers:0x%04X new vers:0x%04X\n", fw_ver_img, fw_ver_new);

	if (fw_ver_new != fw_ver_img) {
		TS_LOG_INFO("FW_ver_Image is different, will upgrade\n");
		return 1;
	}

	fw_revctrl_img_h = be32_to_cpu(*(u32 *)(core_data.sysinfo.cydata.revctrl + 0));

	TS_LOG_INFO("img revctrl_h:0x%04X new revctrl_h:0x%04X\n", fw_revctrl_img_h, fw_revctrl_new_h);

	if (fw_revctrl_new_h != fw_revctrl_img_h) {
		TS_LOG_INFO("FW_revctrl_H Image is different, will upgrade\n");
		return 1;
	}

	fw_revctrl_img_l = be32_to_cpu(*(u32 *)(core_data.sysinfo.cydata.revctrl + 4));

	TS_LOG_INFO("img revctrl_l:0x%04X new revctrl_l:0x%04X\n", fw_revctrl_img_l, fw_revctrl_new_l);

	if (fw_revctrl_new_l != fw_revctrl_img_l) {
		TS_LOG_INFO("FW_revctrl_L Image is different, will upgrade\n");
		return 1;
	}

	return 0;
}
static bool cypress_check_version(const struct firmware *fw)
{
	u32 fw_ver_new;
	u32 fw_revctrl_new_h;
	u32 fw_revctrl_new_l;
	int upgrade_img;
	int upgrade_ttconfig;
	int upgrade;

	if (fw == NULL) {
		TS_LOG_ERR("NULL firmware received, update FW\n");
		return true;
	}
	if (fw->data == NULL || fw->size == 0) {
		TS_LOG_ERR("No firmware received, update FW\n");
		return true;
	}

	TS_LOG_INFO("Found firmware\n");

	fw_ver_new = (u8)fw->data[3] << 8;
	fw_ver_new += (u8)fw->data[4];
	fw_revctrl_new_h = be32_to_cpu(*(u32 *)(fw->data + 5));
	fw_revctrl_new_l = be32_to_cpu(*(u32 *)(fw->data + 9));

	upgrade_img = cypress_check_fw_version(fw_ver_new, fw_revctrl_new_h, fw_revctrl_new_l);
	upgrade_ttconfig = cypress_check_ttconfig_crc();	//get crc from params.h
	upgrade = upgrade_img | upgrade_ttconfig;

	if (upgrade)
		return true;
	else
		return false;
}


static int cypress_initialize_device(void)
{
	int rc = 0;
	int try_cnt = 2;
	int i;

	for (i = 0; i < try_cnt; i++) {
		/*reset first , ic is in bootloader mode, in which, there is 200ms interrupts signal, negative pulse is about 60us */
		rc = cypress_goto_bl();
		if (rc < 0) {
			TS_LOG_ERR("Failed to reset and check bl, rc = %d\n", rc);
			return rc;
		}
		/* exit bl into sysinfo mode, do nothing in bootloader mode, then switch to sysinfo mode,
			after mode switching, there is one interrput*/
		rc = cypress_exit_bl_into_sysinfo();
		if (!rc) {
			TS_LOG_INFO("cypress device goto SI mode successfully\n");
			break;
		}
	}
	if (i == try_cnt) {
		TS_LOG_ERR("sorry, failed into sysinfo mode! rc = %d\n", rc);
		return rc;
	}
	/* read sysinfo data */
	rc = cypress_get_sysinfo_regs();
	if (rc < 0){
		TS_LOG_ERR("failed to get sysinfo regs rc = %d\n", rc);
		return rc;
	}

	rc = cypress_get_ttconfig_info();
	if(rc < 0){
		TS_LOG_ERR("get ttconfig_info failed rc = %d\n", rc);
		return rc;
	}

	rc = cypress_set_opmode();
	if (rc < 0){
		TS_LOG_ERR("failed to set opmode rc = %d\n", rc);
		return rc;
	}

	TS_LOG_INFO("done\n");
	return NO_ERR;
}

static int cypress_dl_source_init(int fw_size)
{
	int rc = 0;
	/* Prevent loading if TMA ver not defined. */
	core_data.ld.image_rec_size = fw_size + 1;

	core_data.ld.image_rec_size = CY_DATA_ROW_SIZE_TMA400
							+ (sizeof(struct cypress_hex_image) - CY_DATA_ROW_SIZE);
	if (fw_size % core_data.ld.image_rec_size != 0) {
		TS_LOG_ERR("Firmware image is misaligned\n");
		rc = -EINVAL;
		return rc;
	}
	core_data.ld.row_buf_size = 1024 > CY_MAX_PRBUF_SIZE ? 1024 : CY_MAX_PRBUF_SIZE;

	core_data.ld.row_buf = kzalloc(core_data.ld.row_buf_size, GFP_KERNEL);
	if (core_data.ld.row_buf == NULL) {
		TS_LOG_ERR("Failed to alloc row buffers(%p)\n", core_data.ld.row_buf);
		rc = -ENOMEM;
		return rc;
	}
	core_data.ld.row_image = kzalloc(sizeof(struct cypress_hex_image), GFP_KERNEL);
	if (core_data.ld.row_image == NULL) {
		TS_LOG_ERR("Failed to alloc row buffers(%p)\n", core_data.ld.row_image);
		rc = -ENOMEM;
		return rc;
	}
	core_data.ld.dev_id = kzalloc(sizeof(struct cypress_dev_id), GFP_KERNEL);
	if (core_data.ld.dev_id == NULL) {
		TS_LOG_ERR("Failed to alloc row buffers(%p)\n",core_data.ld.dev_id);
		rc = -ENOMEM;
		return rc;
	}
	TS_LOG_INFO("done\n");
	return NO_ERR;
}

static int cypress_ldr_enter_result(void)
{
	int rc = 0;
	u8 *status_buf = &core_data.ld.status_buf[0];
	u8 status = 0;
	memset(status_buf, 0, sizeof(core_data.ld.status_buf));
	rc = cypress_get_status(status_buf, CY_CMD_LDR_ENTER_STAT_SIZE, 1);
	if (rc < 0) {
		TS_LOG_ERR("Fail get status to Enter Loader command r =%d\n", rc);
		return rc;
	}
	status = status_buf[CY_STATUS_BYTE];
	if (status == ERROR_SUCCESS) {
		core_data.ld.dev_id->bl_ver = status_buf[11] << 16 |status_buf[10] <<  8 |status_buf[9] <<  0;
		core_data.ld.dev_id->rev_id = status_buf[8] <<  0;
		core_data.ld.dev_id->silicon_id = status_buf[7] << 24 |status_buf[6] << 16
									|status_buf[5] <<  8 |status_buf[4] <<  0;
		rc = 0;
	} else{
		TS_LOG_ERR("Failed to ldr enter\n");
		rc = -EIO;
	}

	TS_LOG_DEBUG("status=%d, bl_ver=%08X rev_id=%02X silicon_id=%08X\n", status,
		 core_data.ld.dev_id->bl_ver, core_data.ld.dev_id->rev_id, core_data.ld.dev_id->silicon_id);

	return rc;
}

static int cypress_ldr_enter_command(void)
{
	u16 crc = 0;
	int rc = 0;
	int i = 0;
	size_t cmd_size = 0;
	u8 reg_addr = CY_REG_BASE;
	u8 ldr_enter_cmd[CY_CMD_LDR_ENTER_CMD_SIZE+1];		/* +1 for TMA400 host sync byte */

	core_data.ld.dev_id->bl_ver = 0;
	core_data.ld.dev_id->rev_id = 0;
	core_data.ld.dev_id->silicon_id = 0;

	ldr_enter_cmd[i++] = CY_CMD_LDR_HOST_SYNC;
	ldr_enter_cmd[i++] = CY_START_OF_PACKET;
	ldr_enter_cmd[i++] = CY_CMD_LDR_ENTER;
	ldr_enter_cmd[i++] = 0x00;	/* data len lsb */
	ldr_enter_cmd[i++] = 0x00;	/* data len msb */

	crc = cypress_compute_crc(&ldr_enter_cmd[1], i - 1);

	ldr_enter_cmd[i++] = (u8)crc;
	ldr_enter_cmd[i++] = (u8)(crc >> 8);
	ldr_enter_cmd[i++] = CY_END_OF_PACKET;

	cmd_size = sizeof(ldr_enter_cmd);

	rc = cypress_i2c_write(reg_addr, ldr_enter_cmd, cmd_size);
	if (rc < 0) {
		TS_LOG_ERR("write block failed %d\n", rc);
		return rc;
	}
	TS_LOG_DEBUG("done\n");
	return NO_ERR;
}

static int cypress_ldr_init_command(void)
{
	u16 crc;
	int i = 0;
	int rc = 0;
	size_t cmd_size = 0;
	u8 ldr_init_cmd[CY_CMD_LDR_INIT_CMD_SIZE+1];		/* +1 for TMA400 host sync byte */
	u8 reg_addr = CY_REG_BASE;

	ldr_init_cmd[i++] = CY_CMD_LDR_HOST_SYNC;
	ldr_init_cmd[i++] = CY_START_OF_PACKET;
	ldr_init_cmd[i++] = CY_CMD_LDR_INIT;
	ldr_init_cmd[i++] = 0x08;	/* data len lsb */
	ldr_init_cmd[i++] = 0x00;	/* data len msb */
	memcpy(&ldr_init_cmd[i], cypress_security_key, sizeof(cypress_security_key));
	i += sizeof(cypress_security_key);
	crc = cypress_compute_crc(&ldr_init_cmd[1], i - 1);
	ldr_init_cmd[i++] = (u8)crc;
	ldr_init_cmd[i++] = (u8)(crc >> 8);
	ldr_init_cmd[i++] = CY_END_OF_PACKET;
	cmd_size = sizeof(ldr_init_cmd);
	rc = cypress_i2c_write(reg_addr, ldr_init_cmd, cmd_size);
	if (rc < 0) {
		TS_LOG_ERR("Fail writing command=%02X\n", ldr_init_cmd[CY_CMD_BYTE]);
		return rc;
	}
	TS_LOG_DEBUG("done\n");
	return NO_ERR;
}

static int cypress_prog_row_command(u8 *image_buf)
{
	u16 crc;
	int data;
	int next = 0;
	int row_data = 0;
	int rc = 0;
	u16 row_sum = 0;
	size_t data_len;
	size_t cmd_size = 0;
	u8 reg_addr = CY_REG_BASE;
	u8 *cmd = NULL;

	TS_LOG_DEBUG("p=%p buf=%p buf[0]=%02X\n", image_buf, core_data.ld.row_buf,
								core_data.ld.row_buf[0]);

	cmd = kzalloc(CY_MAX_PACKET_LEN, GFP_KERNEL);
	if (cmd == NULL){
		TS_LOG_ERR("prog row error - cmd buf is NULL\n");
		rc = -EIO;
		return rc;
	}

	cmd[next++] = CY_CMD_LDR_HOST_SYNC;
	cmd[next++] = CY_START_OF_PACKET;
	cmd[next++] = CY_CMD_LDR_PROG_ROW;
	/*
	 * include array id size and row id size in CY_PACKET_DATA_LEN
	 */
	data_len = CY_DATA_ROW_SIZE_TMA400;
	cmd[next++] = (u8)(data_len+3);
	cmd[next++] = (u8)((data_len+3) >> 8);
	cmd[next++] = core_data.ld.row_image->array_id;
	cmd[next++] = (u8)core_data.ld.row_image->row_num;
	cmd[next++] = (u8)(core_data.ld.row_image->row_num >> 8);

	for (data = 0; 	data < data_len; data++) {
		cmd[next] = core_data.ld.row_image->row_data[row_data++];
		row_sum += cmd[next];
		next++;
	}

	crc = cypress_compute_crc(&cmd[1], next - 1);
	cmd[next++] = (u8)crc;
	cmd[next++] = (u8)(crc >> 8);
	cmd[next++] = CY_END_OF_PACKET;

	cmd_size = next;
	rc = cypress_i2c_write(reg_addr, cmd, cmd_size);
	if (rc < 0) {
		TS_LOG_ERR("Fail writing command=%02X\n", cmd[CY_CMD_BYTE]);
		goto out;
	}
	rc = NO_ERR;
	TS_LOG_INFO("done\n");
out:
	kfree(cmd);
	return rc;
}

static int cypress_ldr_verify_row_command(void)
{
	u16 crc = 0;
	int i = 0;
	int rc = 0;
	size_t cmd_size = 0;
	/* +1 for TMA400 host sync byte */
	u8 ldr_verify_row_cmd[CY_CMD_LDR_VERIFY_ROW_CMD_SIZE+1];
	u8 reg_addr = CY_REG_BASE;

	ldr_verify_row_cmd[i++] = CY_CMD_LDR_HOST_SYNC;
	ldr_verify_row_cmd[i++] = CY_START_OF_PACKET;
	ldr_verify_row_cmd[i++] = CY_CMD_LDR_VERIFY_ROW;
	ldr_verify_row_cmd[i++] = 0x03;	/* data len lsb */
	ldr_verify_row_cmd[i++] = 0x00;	/* data len msb */
	ldr_verify_row_cmd[i++] = core_data.ld.row_image->array_id;
	ldr_verify_row_cmd[i++] = (u8)core_data.ld.row_image->row_num;
	ldr_verify_row_cmd[i++] = (u8)(core_data.ld.row_image->row_num >> 8);
	crc = cypress_compute_crc(&ldr_verify_row_cmd[1], i - 1);
	ldr_verify_row_cmd[i++] = (u8)crc;
	ldr_verify_row_cmd[i++] = (u8)(crc >> 8);
	ldr_verify_row_cmd[i++] = CY_END_OF_PACKET;
	cmd_size = sizeof(ldr_verify_row_cmd);
	rc = cypress_i2c_write(reg_addr, ldr_verify_row_cmd, cmd_size);
	if (rc < 0) {
		TS_LOG_ERR("Fail writing command=%02X\n", ldr_verify_row_cmd[CY_CMD_BYTE]);
		return rc;
	}
	TS_LOG_DEBUG("done\n");
	return NO_ERR;
}

static int cypress_ldr_verify_chksum_command(void)
{
	u16 crc = 0;
	int i = 0;
	int rc = 0;
	size_t cmd_size = 0;
	u8 ldr_verify_chksum_cmd[CY_CMD_LDR_VERIFY_CHKSUM_CMD_SIZE+1];		/* +1 for TMA400 host sync byte */
	u8 reg_addr = CY_REG_BASE;

	ldr_verify_chksum_cmd[i++] = CY_CMD_LDR_HOST_SYNC;
	ldr_verify_chksum_cmd[i++] = CY_START_OF_PACKET;
	ldr_verify_chksum_cmd[i++] = CY_CMD_LDR_VERIFY_CHKSUM;
	ldr_verify_chksum_cmd[i++] = 0x00;	/* data len lsb */
	ldr_verify_chksum_cmd[i++] = 0x00;	/* data len msb */
	crc = cypress_compute_crc(&ldr_verify_chksum_cmd[1], i - 1);
	ldr_verify_chksum_cmd[i++] = (u8)crc;
	ldr_verify_chksum_cmd[i++] = (u8)(crc >> 8);
	ldr_verify_chksum_cmd[i++] = CY_END_OF_PACKET;

	cmd_size = sizeof(ldr_verify_chksum_cmd);
	rc = cypress_i2c_write(reg_addr, ldr_verify_chksum_cmd, cmd_size);
	if (rc < 0) {
		TS_LOG_ERR("Fail writing command=%02X\n", ldr_verify_chksum_cmd[CY_CMD_BYTE]);
		return rc;
	}
	TS_LOG_INFO("done\n");
	return NO_ERR;
}

static int cypress_ldr_exit_command(void)
{
	u16 crc = 0;
	int i = 0;
	int rc;
	size_t cmd_size = 0;
	u8 ldr_exit_cmd[CY_CMD_LDR_EXIT_CMD_SIZE+1];		/* +1 for TMA400 host sync byte */
	u8 reg_addr = CY_REG_BASE;

	ldr_exit_cmd[i++] = CY_CMD_LDR_HOST_SYNC;
	ldr_exit_cmd[i++] = CY_START_OF_PACKET;
	ldr_exit_cmd[i++] = CY_CMD_LDR_EXIT;
	ldr_exit_cmd[i++] = 0x00;	/* data len lsb */
	ldr_exit_cmd[i++] = 0x00;	/* data len msb */
	crc = cypress_compute_crc(&ldr_exit_cmd[1], i - 1);
	ldr_exit_cmd[i++] = (u8)crc;
	ldr_exit_cmd[i++] = (u8)(crc >> 8);
	ldr_exit_cmd[i++] = CY_END_OF_PACKET;
	cmd_size = sizeof(ldr_exit_cmd);
	rc = cypress_i2c_write(reg_addr, ldr_exit_cmd, cmd_size);
	if (rc < 0) {
		TS_LOG_ERR("Fail writing command=%02X\n", ldr_exit_cmd[CY_CMD_BYTE]);
		return rc;
	}
	return NO_ERR;
}

static int cypress_command_result(u8 *stat_ret, size_t num_stat_byte,
			     size_t status_size, unsigned long timeout_ms)
{
	int rc = 0;
	u8 *status_buf = core_data.ld.status_buf;
	if (timeout_ms > 0) {
		memset(status_buf, 0, sizeof(core_data.ld.status_buf));

		rc = cypress_get_status(status_buf, status_size, timeout_ms);
		if (rc < 0 || status_buf[0] != CY_START_OF_PACKET) {
			TS_LOG_ERR("Error getting status, rc = %d, status_buf[0]=%02X\n", rc, status_buf[0]);
			if (!(rc < 0))
				rc = -EIO;
			return rc;
		} else {
			if (status_buf[CY_STATUS_BYTE] != ERROR_SUCCESS) {
				TS_LOG_ERR("Status=0x%02X error\n", status_buf[CY_STATUS_BYTE]);
				rc = -EIO;
			} else if (stat_ret != NULL) {
				if (num_stat_byte < status_size)
					*stat_ret = status_buf[num_stat_byte];
				else
					*stat_ret = 0;
			}
		}
	}else {
		if (stat_ret != NULL)
			*stat_ret = ERROR_SUCCESS;
	}
	return rc;
}

static int cypress_ldr_init_result(u8 *stat_ret, size_t num_stat_byte,
			     size_t status_size, unsigned long timeout_ms)
{
	return cypress_command_result(stat_ret, num_stat_byte, status_size, timeout_ms);
}

static int cypress_prog_row_result(u8 *stat_ret, size_t num_stat_byte,
			     size_t status_size, unsigned long timeout_ms)
{
	return cypress_command_result(stat_ret, num_stat_byte, status_size, timeout_ms);
}

static int cypress_ldr_verify_row_result(u8 *stat_ret, size_t num_stat_byte,
			     size_t status_size, unsigned long timeout_ms)
{
	return cypress_command_result(stat_ret, num_stat_byte, status_size, timeout_ms);
}

static int cypress_ldr_verify_chksum_result(u8 *stat_ret, size_t num_stat_byte,
			     size_t status_size, unsigned long timeout_ms)
{
	return cypress_command_result(stat_ret, num_stat_byte, status_size, timeout_ms);
}

static int cypress_ldr_exit_result(u8 *stat_ret, size_t num_stat_byte,
			     size_t status_size, unsigned long timeout_ms)
{
	return cypress_command_result(stat_ret, num_stat_byte, status_size, timeout_ms);
}

static int cypress_load_app(const u8 *fw, int fw_size)
{
	static enum FW_UPDATE_STATE  state = FW_UP_INITED;
	static u8 *p;
	static int row_count = 0;
	u8 app_chksum;
	u8 verify_checksum;
	int rc = 0;
	int rc1 = 0;
	int rc2 = 0;
	int loop = 0;

	if (!state) {
		p = (u8 *)fw;
		rc1 = cypress_dl_source_init(fw_size);
		rc2 = cypress_goto_bl();
		if (rc1 < 0 || rc2 < 0)
			state = FW_UP_FAIL;
		else
			state = FW_UP_ENTER_LDR;
	}

	TS_LOG_DEBUG("p=%p, fw=%p, fw_size=%d\n", p, fw, fw_size);
LOOP:
	switch (state) {
		case FW_UP_ENTER_LDR:
			rc = cypress_ldr_enter_command();/* Enter Loader and return Silicon ID and Rev */
			if (rc < 0) {
				state = FW_UP_FAIL;
			} else {
				state = FW_UP_ENTER_LDR_RESULT;
			}
			break;
		case FW_UP_ENTER_LDR_RESULT:
			rc = cypress_ldr_enter_result();
			if (rc < 0) {
				state = FW_UP_FAIL;
			} else {
				loop = 1;
				state = FW_UP_LDR_INIT;
			}
			break;
		case FW_UP_LDR_INIT:
			udelay(1000);
			rc = cypress_ldr_init_command();
			if (rc < 0) {
				state = FW_UP_FAIL;
			} else {
				state = FW_UP_LDR_INT_RESULT;
			}
			break;
		case FW_UP_LDR_INT_RESULT:
			rc = cypress_ldr_init_result(NULL, 0,
				CY_CMD_LDR_INIT_STAT_SIZE, CY_CMD_LDR_INIT_TIMEOUT);
			if (rc < 0) {
				state = FW_UP_FAIL;
			} else {
				loop = 1;
				state = FW_UP_ROW_PRO;
			}
			break;
		case FW_UP_ROW_PRO:
			TS_LOG_DEBUG("read row = %d\n", ++row_count);
			memset(core_data.ld.row_buf, 0, core_data.ld.row_buf_size);
			p = cypress_get_row(core_data.ld.row_buf, p, core_data.ld.image_rec_size);/* Get row */
			rc1 = cypress_ldr_parse_row(core_data.ld.row_buf, core_data.ld.row_image); /* Parse row */
			rc2 = cypress_prog_row_command((u8 *)core_data.ld.row_image);
			if (rc1 < 0 || rc2 < 0){
				state = FW_UP_FAIL;
			} else {
				state = FW_UP_ROW_PRO_RESULT;
			}
			break;
		case FW_UP_ROW_PRO_RESULT:
			rc = cypress_prog_row_result(NULL, 0,
				CY_CMD_LDR_PROG_ROW_STAT_SIZE, CY_CMD_TIMEOUT);
			if (rc < 0) {
				state = FW_UP_FAIL;
			} else {
				loop = 1;
				state = FW_UP_ROW_VERIFY;
			}
			break;
		case FW_UP_ROW_VERIFY:
			rc = cypress_ldr_verify_row_command();				/* verify row */
			if (rc < 0) {
				state = FW_UP_FAIL;
			} else {
				state = FW_UP_ROW_VERIFY_RESULT;
			}
			break;
		case FW_UP_ROW_VERIFY_RESULT:
			rc = cypress_ldr_verify_row_result(&verify_checksum, 4,
				CY_CMD_LDR_VERIFY_ROW_STAT_SIZE, CY_CMD_TIMEOUT);
			if (rc < 0){
				state = FW_UP_FAIL;
			} else {
				loop = 1;
				state = FW_UP_ROW_PROG_OR_CHECKSUM;
			}
			break;
		case FW_UP_ROW_PROG_OR_CHECKSUM:
			TS_LOG_DEBUG("p=%p, fw+fw_size=%p\n", p, fw + fw_size);
			loop = 1;
			if(p < (fw + fw_size))
				state = FW_UP_ROW_PRO;
			else
				state = FW_UP_CHECKSUM;
			break;
		case FW_UP_CHECKSUM:
			rc = cypress_ldr_verify_chksum_command();			/* verify app checksum */
			if (rc < 0) {
				state = FW_UP_FAIL;
			} else {
				state = FW_UP_CHECKSUM_RESULT;
			}
			break;
		case FW_UP_CHECKSUM_RESULT:
			rc = cypress_ldr_verify_chksum_result(&app_chksum, 4,
			     CY_CMD_LDR_VERIFY_CHKSUM_STAT_SIZE, CY_CMD_TIMEOUT);
			if (rc < 0) {
				state = FW_UP_FAIL;
			} else {
				loop = 1;
				state = FW_UP_BL_EXIT;
			}
			break;
		case FW_UP_BL_EXIT:
			rc = cypress_ldr_exit_command();				/* exit loader */
			if (rc < 0) {
				state = FW_UP_FAIL;
				break;
			} else {
				state = FW_UP_BL_EXIT_RESULT;
			}
			/*not need break here, */
		case FW_UP_BL_EXIT_RESULT:
			rc = cypress_ldr_exit_result(NULL, 0, CY_CMD_LDR_EXIT_STAT_SIZE, 0);
			if (rc < 0) {
				state = FW_UP_FAIL;
			} else {
				state = FW_UP_SUC;
			}
			break;
		default:
			break;
	}
	if (loop) {
		loop =0;
		goto LOOP;
	}

	if ((state == FW_UP_SUC) || ((state == FW_UP_FAIL))) {
		TS_LOG_INFO("fw upload exit, state = %d\n", state);
		if(core_data.ld.row_buf)
			kfree(core_data.ld.row_buf);
		if(core_data.ld.row_image)
			kfree(core_data.ld.row_image);
		if(core_data.ld.dev_id)
			kfree(core_data.ld.dev_id);
		if (fw_entry != NULL)
			release_firmware(fw_entry);

		rc = cypress_initialize_device();
		if (rc < 0) {
			TS_LOG_ERR("Failed to initialize device\n");
		} else {
			cypress_firmware_calibrate();
		}

		core_data.process_state = CY_STATE_NORMAL;
	}

	return rc;
}

static int cypress_firmware_calibrate(void)
{
	u8 cmd_buf[4] = {0};
	u8 return_buf[2] ={0};
	int rc, rc2;

	TS_LOG_INFO("Requesting mode change to CAT\n");
	rc = cypress_switch_to_cat();
	if (rc < 0) {
		TS_LOG_ERR("Sorry, Error on request set mode rc = %d\n", rc);
		goto out;
	}

	TS_LOG_INFO("Calibrating for Mutual Capacitance Screen\n");
	cmd_buf[0] = CY_CMD_CAT_CALIBRATE_IDACS;
	cmd_buf[1] = 0x00; /* Mutual Capacitance Screen */
	rc = cypress_exec_cmd(CY_HST_CAT, cmd_buf, 2, return_buf, 1);
	if (rc < 0) {
		TS_LOG_ERR("Unable to execute calibrate command.\n");
		goto out;
	}
	if (return_buf[0] != 0) {
		TS_LOG_ERR("sorry, calibrate command unsuccessful\n");
		rc = -EINVAL;
		goto out;
	}

	TS_LOG_INFO("Calibrating for Mutual Capacitance Button\n");
	cmd_buf[1] = 0x01; /* Mutual Capacitance Button */
	rc = cypress_exec_cmd(CY_HST_CAT, cmd_buf, 2, return_buf, 1);
	if (rc < 0) {
		TS_LOG_ERR("Unable to execute Mutual Capacitance Button calibrate command.\n");
		goto out;
	}
	if (return_buf[0] != 0) {
		TS_LOG_ERR("Mutual Capacitance Button calibrate command unsuccessful\n");
		rc = -EINVAL;
		goto out;
	}

	TS_LOG_INFO("Calibrating for Self Capacitance Screen\n");
	cmd_buf[1] = 0x02; /* Self Capacitance */
	rc = cypress_exec_cmd(CY_HST_CAT, cmd_buf, 2, return_buf, 1);
	if (rc < 0) {
		TS_LOG_ERR("Unable to execute Self Capacitance calibrate command.\n");
		goto out;
	}
	if (return_buf[0] != 0) {
		TS_LOG_ERR("Self Capacitance calibrate command unsuccessful\n");
		rc = -EINVAL;
		goto out;
	}

out:
	TS_LOG_INFO("Requesting mode change to Operational\n");
	rc2 = cypress_switch_to_operate();
	if (rc2 < 0)
		TS_LOG_ERR("Error on request set mode rc2 = %d\n", rc2);
	else
		TS_LOG_INFO("Mode changed to Operational: %d\n", rc2);

	if(rc2 < 0)
		rc = rc2;
	return rc;
}

static bool cypress_need_fw_update(char *file_name)
{
	int rc = 0;
	bool fw_update = false;
	struct device *dev = &core_data.cypress_dev->dev;

	rc = request_firmware(&fw_entry, CY_FW_FILE_NAME, dev);
	if (rc < 0) {
		TS_LOG_ERR("Fail request firmware\n");
		return false;
	}

	if (core_data.force_fw_update ==  true) {
		TS_LOG_INFO("force to update fw\n");
		return true;
	}

	fw_update = cypress_check_version(fw_entry);

	if (fw_update == true) {
		TS_LOG_INFO("need to update fw\n");
	} else {
		TS_LOG_INFO("not need to update fw\n");
		if (fw_entry != NULL) {
			release_firmware(fw_entry);
			fw_entry = NULL;
		}
	}

	return fw_update;
}

static int cypress_fw_update_boot(char *file_name)
{
	u8 header_size = 0;
	int rc = 0;

	if (core_data.process_state == CY_STATE_INIT) {
		if (false == cypress_need_fw_update(file_name)) {
			core_data.process_state = CY_STATE_NORMAL;
			return NO_ERR;
		} else {
			core_data.process_state = CY_STATE_FW_UPDATE;
		}
	}

	if (fw_entry == NULL) {
		TS_LOG_ERR("fw_entry == NULL\n");
		rc = -EINVAL;
		goto entry_null;
	}
	if (fw_entry->data == NULL || fw_entry->size == 0) {
		TS_LOG_ERR("No firmware received\n");
		rc = -EINVAL;
		goto firmware_release;
	}
	header_size = fw_entry->data[0];
	if (header_size >= (fw_entry->size + 1)) {
		TS_LOG_ERR("Firmware format is invalid\n");
		rc = -1;
		goto firmware_release;
	}

	rc = cypress_load_app(&(fw_entry->data[header_size + 1]), fw_entry->size - (header_size + 1));
	if (rc < 0)
		TS_LOG_ERR("Firmware update failed with error rc = %d\n", rc);

	goto out;

firmware_release:
	TS_LOG_INFO("release_firmware\n");
	if (fw_entry != NULL) {
		release_firmware(fw_entry);
		fw_entry = NULL;
	}
entry_null:
	core_data.process_state = CY_STATE_NORMAL;
out:
	return rc;
}

static int cypress_regulator_get(void)
{
	core_data.vdd = regulator_get(NULL, TP_ANALOG_VDD);
	if (IS_ERR(core_data.vdd)) {
		TS_LOG_ERR("failed to get cypress vdd\n");
		return  -EINVAL;
	}

	core_data.vbus = regulator_get(NULL, TP_IO_VDD);
	if (IS_ERR(core_data.vbus)) {
		TS_LOG_ERR("failed to get cypress vbus\n");
		regulator_put(core_data.vdd);
		return -EINVAL;
	}

	return NO_ERR;
}

static int cypress_gpio_request(void)
{
	int rc = NO_ERR;

	if (!gpio_is_valid(core_data.cypress_chip_data->reset_gpio)){
		TS_LOG_ERR("reset gpio:%d gpio not provided\n", core_data.cypress_chip_data->reset_gpio);
		rc = -EIO;
		goto out;
	}
	if (!gpio_is_valid(core_data.cypress_chip_data->irq_gpio)){
		TS_LOG_ERR("reset gpio:%d gpio not provided\n", core_data.cypress_chip_data->irq_gpio);
		rc = -EIO;
		goto out;
	}

	rc = gpio_request(core_data.cypress_chip_data->reset_gpio, "ts_reset_gpio");
	if (rc < 0) {
		TS_LOG_ERR("Fail to request gpio:%d. rc = %d\n", core_data.cypress_chip_data->reset_gpio,
			rc);
		goto out;
	}
	rc = gpio_request(core_data.cypress_chip_data->irq_gpio, "ts_irq_gpio");
	if (rc < 0) {
		TS_LOG_ERR("Fail to request gpio:%d. rc = %d\n", core_data.cypress_chip_data->reset_gpio,
			rc);
		gpio_free(core_data.cypress_chip_data->reset_gpio);
		goto out;
	}

out:
	return rc;
}

static void cypress_regulator_set(void)
{
	int rc = NO_ERR;

	rc = regulator_set_voltage(core_data.vdd, 2800000, 2800000);
	if(rc < 0){
		TS_LOG_ERR("failed to set cypress vdd to 2.8V, rc = %d\n", rc);
	}
#if 0
	rc = regulator_set_voltage(vbus, 1800000, 1800000);
	if(rc < 0){
		TS_LOG_ERR("failed to set cypress vbus\n");
	}
#endif
	return;
}

static void cypress_regulator_enable(void)
{
	int rc = NO_ERR;

	rc = regulator_enable(core_data.vdd);
	if (rc < 0) {
		TS_LOG_ERR("failed to enable cypress vdd(2.8V), rc = %d\n", rc);
	}

	rc = regulator_enable(core_data.vbus);
	if (rc < 0) {
		TS_LOG_ERR("failed to enable cypress vbus, rc = %d\n", rc);
	}
	return;
}

static void cypress_gpio_set(void)
{
	gpio_direction_output(core_data.cypress_chip_data->reset_gpio, 1);
	gpio_direction_input(core_data.cypress_chip_data->irq_gpio);
	return;
}

static void cypress_gpio_free(void)
{
	gpio_free(core_data.cypress_chip_data->irq_gpio);
	gpio_free(core_data.cypress_chip_data->reset_gpio);
	return;
}


static void cypress_regulator_disable(void)
{
	if (!IS_ERR(core_data.vdd)) {
		regulator_disable(core_data.vdd);
	}

	if (!IS_ERR(core_data.vbus)) {
		regulator_disable(core_data.vbus);
	}
}

static void cypress_regulator_put(void)
{
	if (!IS_ERR(core_data.vdd)) {
		regulator_put(core_data.vdd);
	}

	if (!IS_ERR(core_data.vbus)) {
		regulator_put(core_data.vbus);
	}

	return;
}

static int i2c_communicate_check(void)
{
	int rc = NO_ERR;
	int i;
	u8 reg_addr = 0x00;
	u8 mode = 0;

	for (i = 0; i < I2C_RW_TRIES; i ++) {
		rc = cypress_i2c_read(&reg_addr, sizeof(reg_addr), &mode, sizeof(mode));
		if (rc < 0) {
			TS_LOG_ERR("Failed to read register 0x00, i = %d, rc = %d\n", i, rc);
			msleep(50);
		} else {
			TS_LOG_INFO("i2c communicate check success\n");
			rc = NO_ERR;
			return rc;
		}
	}

	return rc;
}

/*    init the chip.
*
*     (1) power up;  (2) reset gpio config;  (3) detect the chip thourgh bus(i2c).
*/
static int cypress_chip_detect(struct device_node *device,
		struct ts_device_data *chip_data, struct platform_device *ts_dev)
{
	int rc = NO_ERR;

	core_data.cypress_chip_data = chip_data;
	core_data.opmode = OPMODE_FINGER;
	core_data.cypress_dev = ts_dev;
	core_data.cypress_chip_data->is_in_cell = false;
	core_data.process_state = CY_STATE_INIT;

	/*in g_ts_device_map, cypress's chip_detect is at the back of synpatics, so just add msleep 50ms here*/
	msleep(50);

	/*get regulator for device*/
	rc = cypress_regulator_get();
	if (rc < 0) {
		TS_LOG_ERR("Failed to get regulator, rc = %d\n", rc);
		goto regulator_get_err;
	}

	rc = cypress_gpio_request();
	if(rc < 0){
		TS_LOG_ERR("Failed to request gpio, rc = %d\n", rc);
		goto gpio_request_err;
	}

	cypress_regulator_set();

	cypress_regulator_enable();

	msleep(5);

	cypress_gpio_set();

	cypress_hw_reset();

	rc = i2c_communicate_check();
	if (rc < 0) {
		TS_LOG_ERR("not find cypress device\n");
		goto err;
	} else {
		TS_LOG_INFO("find cypress device\n");
		goto out;
	}

out:
	TS_LOG_INFO("done\n");
	return NO_ERR;
err:
	TS_LOG_ERR("error\n");
	cypress_gpio_free();
	cypress_regulator_disable();
gpio_request_err:
	cypress_regulator_put();
regulator_get_err:
	return rc;
}

static int cypress_init_chip(void)
{
	int rc = NO_ERR;

	rc = cypress_initialize_device();
	if (rc < 0) {
		TS_LOG_ERR("Failed to initialize device, rc = %d\n", rc);
		return rc;
	}

	TS_LOG_INFO("done\n");
	return rc;
}
static void cypress_get_touch_axis(int *axis, int size, int max, u8 *xy_data, int bofs)
{
	int nbyte;
	int next;

	for (nbyte = 0, *axis = 0, next = 0; nbyte < size; nbyte++) {
		*axis = (*axis * 256) + (xy_data[next] >> bofs);
		next++;
	}
	*axis &= max - 1;
}

/* read xy_data for all current touches */
static int cypress_xy_worker(struct ts_fingers *info)
{
	struct cypress_touch tch;
	enum cypress_tch_abs abs;
	u8 num_cur_tch;
	u8 hst_mode, rep_len, rep_stat, tt_stat;
	u8 touch_id;
	u8 sysinfo_reg_addr =  core_data.sysinfo.sysinfo_merged_data.tt_stat_ofs + 1;
	int rc = -EINVAL;
	int n_finger;

	hst_mode = core_data.sysinfo.xy_mode[CY_REG_BASE];
	rep_len = core_data.sysinfo.xy_mode[core_data.sysinfo.sysinfo_merged_data.rep_ofs];		//data reported length
	rep_stat = core_data.sysinfo.xy_mode[core_data.sysinfo.sysinfo_merged_data.rep_ofs + 1];
	tt_stat = core_data.sysinfo.xy_mode[core_data.sysinfo.sysinfo_merged_data.tt_stat_ofs];
	TS_LOG_DEBUG("hst_mode(xy_mode(%d)) = 0x%x, rep_len(xy_mode(%d)) = 0x%x"
		"rep_stat (xy_mode(%d)) = 0x%x, tt_stat(xy_mode(%d)) = 0x%x", CY_REG_BASE, hst_mode,
		core_data.sysinfo.sysinfo_merged_data.rep_ofs, rep_len,
		core_data.sysinfo.sysinfo_merged_data.rep_ofs + 1, rep_stat,
		core_data.sysinfo.sysinfo_merged_data.tt_stat_ofs, tt_stat);

	num_cur_tch = GET_NUM_TOUCHES(tt_stat);		//tch_rec_size is the size of each touch record
	TS_LOG_DEBUG("num_cur_tch = %d, sysinfo_reg_addr = 0x%x, tch_rec_size(each touch record size) = 0x%x\n", num_cur_tch,
				sysinfo_reg_addr, core_data.sysinfo.sysinfo_merged_data.tch_rec_size);

	if (rep_len == 0 && num_cur_tch > 0) {
		TS_LOG_ERR("report length error, rep_len=%d num_tch=%d\n", rep_len, num_cur_tch);
		return rc;
	}
	/* read touches */
	if (num_cur_tch > 0) {
		rc = cypress_i2c_read(&sysinfo_reg_addr, 1, core_data.sysinfo.xy_data,
				num_cur_tch*core_data.sysinfo.sysinfo_merged_data.tch_rec_size);
		if (rc < 0) {
			TS_LOG_ERR("Failed to read on touch regs, sysinfo_reg_addr = 0x%x, size = %d, rc = %d\n", rc,
				sysinfo_reg_addr, num_cur_tch*core_data.sysinfo.sysinfo_merged_data.tch_rec_size);
			return rc;
		}
	}
	/* check any error conditions */
	if (IS_BAD_PKT(rep_stat)) {
		TS_LOG_INFO("Invalid buffer detected, report data invalid, rep_stat = 0x%x\n", rep_stat);
		return rc;
	}
	if (IS_LARGE_AREA(tt_stat)) {
		TS_LOG_INFO("Large area detected, set current num to 0, tt_stat = 0x%x\n", tt_stat);
		num_cur_tch = 0;
	}
	if (num_cur_tch > core_data.sysinfo.sysinfo_merged_data.max_tchs) {
		if (num_cur_tch > CY_MAX_TCH) {
			/* terminate all active tracks */
			TS_LOG_ERR("Num touch err detected (n=%d)\n", num_cur_tch);
			num_cur_tch = 0;
		} else {
			TS_LOG_ERR("(n=%d c=%d), too many tch, set num_cur_tch to max tch", num_cur_tch,
						core_data.sysinfo.sysinfo_merged_data.max_tchs);
			num_cur_tch = core_data.sysinfo.sysinfo_merged_data.max_tchs;
		}
	}
	/* extract xy_data for all currently reported touches */
	memset(&tch, 0, sizeof(struct cypress_touch));
	memset(info, 0, sizeof(struct ts_fingers));
	info->cur_finger_number = num_cur_tch;
	TS_LOG_DEBUG("outdata: current finger number = %d\n", info->cur_finger_number);

	if(num_cur_tch == 0)
		return  NO_ERR;
	for (n_finger = 0; n_finger < num_cur_tch; n_finger++) {
		for (abs = CY_TCH_X; abs < CY_TCH_NUM_ABS; abs++) {
			cypress_get_touch_axis(&tch.abs[abs], core_data.sysinfo.sysinfo_merged_data.tch_abs[abs].size,
				core_data.sysinfo.sysinfo_merged_data.tch_abs[abs].max,
				core_data.sysinfo.xy_data + (n_finger * core_data.sysinfo.sysinfo_merged_data.tch_rec_size)
					+ core_data.sysinfo.sysinfo_merged_data.tch_abs[abs].ofs,
				core_data.sysinfo.sysinfo_merged_data.tch_abs[abs].bofs);

			TS_LOG_DEBUG("get %s = %d\n", cypress_tch_abs_string[abs], tch.abs[abs]);
		}
		TS_LOG_DEBUG("X = %d, Y = %d, P = %d, T = %d, E = %d\n",
				tch.abs[CY_TCH_X], tch.abs[CY_TCH_Y], tch.abs[CY_TCH_P],
				tch.abs[CY_TCH_T], tch.abs[CY_TCH_E]);

		touch_id = tch.abs[CY_TCH_T];
		info->fingers[touch_id].event = tch.abs[CY_TCH_E];
		info->fingers[touch_id].x = tch.abs[CY_TCH_X];
		info->fingers[touch_id].y = tch.abs[CY_TCH_Y];
		info->fingers[touch_id].pressure = tch.abs[CY_TCH_P];
		TS_LOG_DEBUG("outdata: x = %d, y = %d, pressure = %d\n", info->fingers[touch_id].x,
			info->fingers[touch_id].y, info->fingers[touch_id].pressure);
	}

	return NO_ERR;
}

static int cypress_input_config(struct input_dev *input_dev)
{
	core_data.input = input_dev;
	set_bit(EV_SYN, input_dev->evbit);
	set_bit(EV_ABS, input_dev->evbit);
	set_bit(INPUT_PROP_DIRECT, input_dev->propbit);
	input_set_abs_params(input_dev, ABS_MT_POSITION_X, CY_ABS_MIN_X, CY_ABS_MAX_X, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y, CY_ABS_MIN_Y, CY_ABS_MAX_Y, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_PRESSURE, CY_ABS_MIN_P, CY_ABS_MAX_P, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TRACKING_ID, CY_ABS_MIN_T, CY_ABS_MAX_T, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TOUCH_MINOR, 0, 255, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_ORIENTATION, -128, 127, 0, 0);

	return NO_ERR;
}

static int cypress_irq_top_half(struct ts_cmd_node *cmd)
{
	cmd->command = TS_INT_PROCESS;
	TS_LOG_DEBUG("cmd is %d\n", cmd->command);
	return NO_ERR;
}

static int cypress_irq_bottom_half(struct ts_cmd_node *in_cmd, struct ts_cmd_node *out_cmd)
{
	u8 reg_addr = CY_REG_BASE;
	u8 mode[3] = {0};
	u8 cur_mode;
	int rc = 0;
	struct ts_fingers *info = &out_cmd->cmd_param.pub_params.algo_param.info;

	rc = cypress_i2c_read(&reg_addr, sizeof(reg_addr), mode, sizeof(mode));
	if (rc) {
		TS_LOG_ERR("Fail read mode rc =%d\n", rc);
		return rc;
	}

	TS_LOG_DEBUG("mode[0-2] = 0x%x, 0x%x, 0x%x\n",mode[0], mode[1], mode[2]);

	/* Check for false bootloader interrupt */
	if (unlikely(mode[0] == CY_CORE_BL_HOST_SYNC_BYTE)) {
		TS_LOG_DEBUG("False interrupt in bootloader mode, mode[0] = 0x%x\n", mode[0]);
		return NO_ERR;
	}

	if (IS_BOOTLOADER(mode[0])) {
		TS_LOG_DEBUG("bootloader mode is running\n");
	        if (core_data.process_state == CY_STATE_FW_UPDATE) {
			    out_cmd->command = TS_FW_UPDATE_BOOT;
	        } else {
			    TS_LOG_ERR("in bootloader and the state is %d\n", core_data.process_state);
	        }
		return NO_ERR;
	}

	out_cmd->command = TS_INPUT_ALGO;
	out_cmd->cmd_param.pub_params.algo_param.algo_order = TS_ALGO_FUNC_0;

	cur_mode = mode[0] & CY_HST_MODE;
	/* This should be status report, read status regs */
	if (cur_mode == CY_HST_OPERATE) {
		rc = cypress_i2c_read(&reg_addr, sizeof(reg_addr), core_data.sysinfo.xy_mode, core_data.sysinfo.sysinfo_merged_data.mode_size);
		if (rc){
			TS_LOG_ERR("fail read mode regs rc =%d\n",rc);
			return rc;
		}
	}else
		TS_LOG_ERR("not in operation mode, current mode = 0x%x\n", cur_mode);
	/* attention IRQ */
	rc = cypress_xy_worker(info);
	if (rc){
		TS_LOG_ERR("xy_worker error rc = %d\n", rc);
		return rc;
	}
	/* handshake the event */
	rc = cypress_handshake(mode[0]);
	if (rc){
		TS_LOG_ERR("Fail handshake mode=0x%02X, rc = %d\n", mode[0], rc);
		return rc;
	}

	TS_LOG_DEBUG("cypress irq_bottom_half done\n");
	return NO_ERR;
}

/*
 * Retrieve panel data command, readoffset is position offset of reading
 */
static int cypress_retrieve_scan_data(int readOffset, int numElement, u8 dataType, u8 *return_buf)
{
	u8 cmd_buf[CY_CMD_CAT_READ_CFG_BLK_CMD_SZ];
	int rc;
	TS_LOG_INFO("\n");
	cmd_buf[0] = CY_CMD_CAT_RETRIEVE_PANEL_SCAN;
	cmd_buf[1] = HI_BYTE(readOffset);
	cmd_buf[2] = LO_BYTE(readOffset);
	cmd_buf[3] = HI_BYTE(numElement);
	cmd_buf[4] = LO_BYTE(numElement);
	cmd_buf[5] = dataType;
	rc = cypress_exec_cmd(CY_HST_CAT, cmd_buf, CY_CMD_CAT_RET_PANEL_DATA_CMD_SZ,
			return_buf, CY_CMD_CAT_RET_PANEL_DATA_RET_SZ);
	if (rc < 0)
		return rc;

	return rc;
}

static int out_of_range(enum check_data_type type, int value)
{
	TS_LOG_INFO("value = %d\n", value);
	if (rawdatabuf && (rawdata_index < rawdata_size)) {
		rawdatabuf[rawdata_index] = value;
		rawdata_index++;/*update the data index*/
	}

	switch(type)
	{
	case CY_CHK_MUT_RAW:
		if (value < CY_MUT_RAW_MIN || value > CY_MUT_RAW_MAX)
			return 1;
		break;
	case CY_CHK_SELF_RAW:
		if (value < CY_SELF_RAW_MIN || value > CY_SELF_RAW_MAX)
			return 1;
		break;
	case CY_CHK_MUT_IDAC:
		if (value < CY_MUT_IDAC_MIN || value > CY_MUT_IDAC_MAX)
			return 1;
		break;
/*It's dead code never can be operated,in hisi fortify_report
	case CY_CHK_SELF_IDAC:
		if (value < CY_SELF_IDAC_MIN || value > CY_SELF_IDAC_MAX)
			return 1;
*/
		break;
	default:
		return 0;
	}
	return 0;
}

static int getHighPart(int num)
{
	switch(num)
	{
	case 1:
		return 0xFF000000;
	case 2:
		return 0xFFFF0000;
	case 3:
		return 0xFFFFFF00;
	default:
		return 0x0;
	}
}

static int cypress_check_range(enum check_data_type type, int endian, int datasize, int size)
{
	static int temp = 0;
	int index;
	int rc = 0;

	for(index = 8; index < size; ++index){
		if(endian == B_ENDIAN){
			if(0 == index%datasize){	 //high byte
				if(core_data.rawdate.ic_buf[index]&0x80)	 //extend
					temp |= getHighPart(4 -datasize);
				temp |= core_data.rawdate.ic_buf[index] << 8*(datasize -1);
				if(datasize ==1){
					if(out_of_range(type, temp))
					    rc = -1;
					temp = 0;
				}
			}else{
				temp |= core_data.rawdate.ic_buf[index] << 8*(datasize -  index%datasize - 1);
				if(index%datasize == datasize -1){	//low byte
					if(out_of_range(type, temp))
						rc = -1;
					temp = 0;
				}
			}
		}else {//little endian
			if( index%datasize == datasize -1){
				if(core_data.rawdate.ic_buf[index]&0x80)
					temp |= getHighPart(4 -datasize);
				temp |= core_data.rawdate.ic_buf[index] << 8*(datasize -1);
				if(out_of_range(type, temp))
					rc = -1;
				temp = 0;
			}else
				temp |= core_data.rawdate.ic_buf[index] << 8*( index%datasize);
		}
	}

	return rc;
}

/*return value:  >0 means success; <0 means failed; =0 means unknown*/
static int cypress_get_data_and_check(enum check_data_type type, int offset)
{
	u8 return_buf[CY_CMD_CAT_RET_PANEL_DATA_RET_SZ] = {0};
	int rc = 0;
	int dataIdx = -1;
	int leftOverElement = 0;
	int returnedElement = 0;
	int readElementOffset = 0;
	int datasize = 0;
	int endian = 0;
	u8 reg_addr = CY_REG_BASE;
	u8 cmdParam_ofs = core_data.sysinfo.sysinfo_merged_data.cmd_ofs + 1;
	u8 elementStartOffset = cmdParam_ofs + CY_CMD_CAT_RET_PANEL_DATA_RET_SZ;
	int readByte = cmdParam_ofs + CY_CMD_CAT_RET_PANEL_DATA_RET_SZ;

	/* retrieve scan data */
	rc = cypress_retrieve_scan_data(offset,
			core_data.rawdate.heatmap.numElement,
			core_data.rawdate.heatmap.dataType, return_buf);
	if (rc < 0){
		TS_LOG_ERR("retrieve_scan error\n");
		return 0;
	}
	if (return_buf[CY_CMD_OUT_STATUS_OFFSET] != CY_CMD_STATUS_SUCCESS)	//judge success or not
		return 0;
	datasize = return_buf[CY_CMD_RET_PNL_OUT_DATA_FORMAT_OFFS] & CY_CMD_RET_PANEL_ELMNT_SZ_MASK;	//bit2-0
	endian = return_buf[CY_CMD_RET_PNL_OUT_DATA_FORMAT_OFFS] & CY_CMD_RET_PANEL_ENDIAN_MASK;	//bit4

	/* read data */
	readByte += core_data.rawdate.heatmap.numElement *datasize;
	if (readByte >= I2C_BUF_MAX_SIZE){
		rc = cypress_i2c_read(&reg_addr, sizeof(reg_addr), core_data.rawdate.ic_buf, I2C_BUF_MAX_SIZE);
		dataIdx = I2C_BUF_MAX_SIZE;
	} else{
		rc = cypress_i2c_read(&reg_addr, sizeof(reg_addr), core_data.rawdate.ic_buf, readByte);
		dataIdx = readByte;
	}
	if (rc < 0){
		TS_LOG_ERR("Error on read rc = %d\n", readByte);
		return 0;
	}
	leftOverElement = core_data.rawdate.heatmap.numElement;
	readElementOffset = 0;
	returnedElement = return_buf[CY_CMD_RET_PNL_OUT_ELMNT_SZ_OFFS_H] * 256
					+ return_buf[CY_CMD_RET_PNL_OUT_ELMNT_SZ_OFFS_L];

	leftOverElement -= returnedElement;			//calc number of element that has not been read
	readElementOffset += returnedElement;			//calc number of element that has been read
	 while (leftOverElement > 0){
		/* get the data */
		rc = cypress_retrieve_scan_data(readElementOffset, leftOverElement, core_data.rawdate.heatmap.dataType, return_buf);
		if (rc < 0)
			return 0;

		if (return_buf[CY_CMD_OUT_STATUS_OFFSET] != CY_CMD_STATUS_SUCCESS)
			return 0;

		/* DO read */
		readByte = leftOverElement * (return_buf[CY_CMD_RET_PNL_OUT_DATA_FORMAT_OFFS]
				& CY_CMD_RET_PANEL_ELMNT_SZ_MASK);

		if (readByte >= (I2C_BUF_MAX_SIZE - elementStartOffset)) {
			rc = cypress_i2c_read(&elementStartOffset, 1, (u8 *)(core_data.rawdate.ic_buf + dataIdx), I2C_BUF_MAX_SIZE - elementStartOffset);
			dataIdx += (I2C_BUF_MAX_SIZE - elementStartOffset);
		} else {
			rc = cypress_i2c_read(&elementStartOffset, 1, (u8 *)(core_data.rawdate.ic_buf + dataIdx), readByte);
			dataIdx += readByte;
		}
		if (rc < 0) {
			TS_LOG_ERR("Error on read rc = %d\n", rc);
			return 0;
		}
		returnedElement = return_buf[CY_CMD_RET_PNL_OUT_ELMNT_SZ_OFFS_H] * 256
						+ return_buf[CY_CMD_RET_PNL_OUT_ELMNT_SZ_OFFS_L];
		/* Update element status */
		leftOverElement -= returnedElement;
		readElementOffset += returnedElement;

	}
	/* update on the buffer */
	core_data.rawdate.ic_buf[CY_CMD_RET_PNL_OUT_ELMNT_SZ_OFFS_H + cmdParam_ofs] = HI_BYTE(readElementOffset);
	core_data.rawdate.ic_buf[CY_CMD_RET_PNL_OUT_ELMNT_SZ_OFFS_L + cmdParam_ofs] = LO_BYTE(readElementOffset);

	rc = cypress_check_range(type, endian, datasize, dataIdx);
	if(rc < 0)	{
		TS_LOG_ERR("cypress_check_range failed\n");
		return -1;
	}

	return dataIdx;
}

/*
 * Execute scan command
 */
static int cypress_exec_scan_cmd(void)
{
	u8 cmd_buf[CY_CMD_CAT_EXEC_SCAN_CMD_SZ] = {0};
	u8 return_buf[CY_CMD_CAT_EXEC_SCAN_RET_SZ] = {0};
	int rc;

	cmd_buf[0] = CY_CMD_CAT_EXEC_PANEL_SCAN;
	rc = cypress_exec_cmd(CY_HST_CAT, cmd_buf, CY_CMD_CAT_EXEC_SCAN_CMD_SZ,
			return_buf, CY_CMD_CAT_EXEC_SCAN_RET_SZ);
	if (rc < 0) {
		TS_LOG_ERR("Unable to send execute panel scan command.\n");
		return rc;
	}
	if (return_buf[0] != 0)
		return -EINVAL;
	return rc;
}

/*return value:  >0 means success; <0 means failed; =0 means unknown*/
static int cypress_check_raw_data(void)
{
	int rc = 0;
	int i = 0;
	enum check_data_type type;
	for(i = 0; i < 2; ++i){
		if(0 == i){
			type = CY_CHK_MUT_RAW;
			core_data.rawdate.heatmap.numElement = 448;
			core_data.rawdate.heatmap.dataType = CY_MUT_RAW;
		}else{
			type = CY_CHK_SELF_RAW;
			core_data.rawdate.heatmap.numElement = 28;
			core_data.rawdate.heatmap.dataType = CY_SELF_RAW;
		}
		/* Start scan */
		rc = cypress_exec_scan_cmd();
		if (rc < 0)
			return 0;
		/* retrieve scan data */
		rc = cypress_get_data_and_check(type, CY_CMD_IN_DATA_OFFSET_VALUE);
		if(rc < 0)
			return -1;
	}
	return rc;
}

static int cypress_get_rawdata(struct ts_rawdata_info *info, struct ts_cmd_node *out_cmd)
{
	int rc, rc1, rc2;

	TS_LOG_INFO("cypress_get_rawdata\n");

	if (core_data.process_state != CY_STATE_NORMAL) {
		TS_LOG_ERR("can not get raw data,process state = %d\n", core_data.process_state);
		memcpy(info->buff, "busy", sizeof("busy"));
		return NO_ERR;
	}

	/*cal rawdata_size,first two element is the value of rx&tx*/
	rawdata_size = 2+core_data.sysinfo.pcfg.electrodes_y*core_data.sysinfo.pcfg.electrodes_x
					+core_data.sysinfo.pcfg.electrodes_y;
	rawdatabuf = (int *)kzalloc(rawdata_size*sizeof(int), GFP_KERNEL);
	if (!rawdatabuf) {
		TS_LOG_ERR("malloc rawdatabuf failed\n");
		rc = -ENOMEM;
		goto out;
	}
	rawdatabuf[0] = core_data.sysinfo.pcfg.electrodes_y;/*rx*/
	rawdatabuf[1] = core_data.sysinfo.pcfg.electrodes_x;/*tx*/
	rawdata_index = 2;

	/* Call relevant store handler. change mode to CAT*/
	rc1 = cypress_switch_to_cat();
	if (rc1 < 0) {
		TS_LOG_ERR("Sorry, failed to set mode to CAT rc = %d\n", rc1);
		goto cypress_get_rawdata;
	}
	rc2 = cypress_check_raw_data();
	if(rc2 <= 0)
		TS_LOG_ERR("cypress_check_raw_data return %d\n", rc2);

cypress_get_rawdata:
	if (rc1 < 0) {
		memcpy(info->result, "0F-1F-2P-3P", sizeof("0F-1F-2P-3P"));
	} else if (rc2  < 0) {
		memcpy(info->result, "0P-1F-2P-3P", sizeof("0P-1F-2P-3P"));
	} else {
		memcpy(info->result, "0P-1P-2P-3P", sizeof("0P-1P-2P-3P"));
	}
	memcpy(info->buff, rawdatabuf, rawdata_size*sizeof(int));
	info->used_size = rawdata_size;
	TS_LOG_INFO("info->used_size = %d\n",info->used_size);

	/*back to operational*/
	rc = cypress_switch_to_operate();
	if(rc < 0)
		TS_LOG_ERR("Sorry, Failed to set operational rc = %d\n", rc);
out:
	if (rawdatabuf) {
		kfree(rawdatabuf);
		rawdatabuf = NULL;
		rawdata_size = 0;
	}
	return rc;
}

static int cypress_check_status(void)
{
	int rc = 0;
	int rc1 = 0;
	u8 hst_mode_addr = CY_REG_BASE;
	u8 rep_stat_addr = CY_REG_BASE+core_data.sysinfo.sysinfo_merged_data.rep_ofs+1;
	u8 mode = 0;
	u8 rep_stat = 0;

	if (core_data.process_state == CY_STATE_NORMAL) {
		rc = cypress_i2c_read(&hst_mode_addr, sizeof(hst_mode_addr), &mode, 1);
		rc1 = cypress_i2c_read(&rep_stat_addr, sizeof(rep_stat_addr), &rep_stat, 1);
		if ((rc < 0) || (rc1 < 0)) {
			TS_LOG_ERR("failed to access device in watchdog timer rc=%d, rc1=%d\n", rc, rc1);
			rc = (rc < 0) ? rc : rc1;
		} else {
			TS_LOG_DEBUG("mode=0x%02x, rep_stat=0x%02x, rep_ofs=0x%02x\n",
				mode, rep_stat, core_data.sysinfo.sysinfo_merged_data.rep_ofs);
			if (IS_BOOTLOADER(mode) && IS_BOOTLOADER(rep_stat)) {
				TS_LOG_ERR("device found in bootloader mode when operational mode, rep_stat=0x%02X\n",rep_stat);
				rc = -EINVAL;
			}
		}
	} else {
		TS_LOG_ERR("not in normal state, state = %d\n", core_data.process_state);
	}

	return rc;
}

static int cypress_reset_chip(void)
{
	int rc = 0;
	TS_LOG_INFO("initialize device~~~~~~~~~~~~\n");
	rc = cypress_initialize_device();
	if (rc < 0) {
		TS_LOG_ERR("Failed to initialize device, rc = %d\n", rc);
		cypress_power_on_reset();
		cypress_hw_reset();
	}

	return rc;
}
