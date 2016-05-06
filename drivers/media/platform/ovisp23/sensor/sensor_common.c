/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/delay.h>
#include "sensor_common.h"
#include "../cci/hisi_cci.h"
#include "../io/hisi_isp_io.h"

void hisi_mclk_config(struct hisi_sensor_ctrl_t *s_ctrl,
	struct sensor_power_setting *power_setting, int state)
{
	int sensor_index;

	cam_debug("%s enter.state:%d", __func__, state);
	if (SENSOR_INDEX_INVALID != power_setting->sensor_index) {
		sensor_index = power_setting->sensor_index;
	} else {
		sensor_index = s_ctrl->sensor->sensor_info->sensor_index;
	}

	if (is_fpga_board())
		return;

	if (POWER_ON == state) {
		/* mclk */
		if (CAMERA_SENSOR_PRIMARY == sensor_index) {
			SETREG8(REG_ISP_CLK_DIVIDER, 0x44);
		} else {
			SETREG8(REG_ISP_CLK_DIVIDER, 0x44);
		}
	} else {
		SETREG8(REG_ISP_CLK_DIVIDER, 0);
	}
	if (0 != power_setting->delay) {
		camdrv_msleep(power_setting->delay);
	}

	return;
}

int hisi_sensor_gpio_config(gpio_t pin_type, struct hisi_sensor_info *sensor_info,
	struct sensor_power_setting *power_setting, int state)
{
	int rc = -1;

	cam_debug("%s enter, pin_type: %d", __func__, pin_type);

	if (is_fpga_board())
		return 0;

	if(0 == sensor_info->gpios[pin_type].gpio) {
		cam_err("gpio type[%d] is not actived", pin_type);
		return rc;
	}

	rc = gpio_request(sensor_info->gpios[pin_type].gpio, NULL);
	if(rc < 0) {
		cam_err("failed to request gpio[%d]", sensor_info->gpios[pin_type].gpio);
		return rc;
	}

	if(pin_type == FSIN) {
		cam_info("pin_level: %d", gpio_get_value(sensor_info->gpios[pin_type].gpio));
		rc = 0;
	} else {
		rc = gpio_direction_output(sensor_info->gpios[pin_type].gpio,
			state ? (power_setting->config_val + 1) % 2 : power_setting->config_val);
		if(rc < 0) {
			cam_err("failed to control gpio[%d]", sensor_info->gpios[pin_type].gpio);
		}
	}

	gpio_free(sensor_info->gpios[pin_type].gpio);

	if (0 != power_setting->delay) {
		camdrv_msleep(power_setting->delay);
	}

	return rc;

}

int hisi_sensor_ldo_config(ldo_index_t ldo, struct hisi_sensor_info *sensor_info,
	struct sensor_power_setting *power_setting, int state)
{
	int index;
	int rc = -1;
	const char *ldo_names[LDO_MAX]
		= {"dvdd", "dvdd2", "avdd", "avdd2", "vcm", "vcm2", "iopw"};

	cam_debug("%s enter, ldo: %d", __func__, ldo);

	if (is_fpga_board())
		return 0;

	for(index = 0; index < sensor_info->ldo_num; index++) {
		if(!strcmp(sensor_info->ldo[index].supply, ldo_names[ldo]))
			break;
	}

	if(index == sensor_info->ldo_num) {
		cam_err("ldo [%s] is not actived", ldo_names[ldo]);
		return rc;
	}

	if (POWER_ON == state) {
		if(LDO_IOPW != ldo) {
			rc = regulator_set_voltage(sensor_info->ldo[index].consumer, power_setting->config_val, power_setting->config_val);
			if(rc < 0) {
				cam_err("failed to set ldo[%s] to %d V", ldo_names[ldo], power_setting->config_val);
				return rc;
			}
		}
		rc = regulator_bulk_enable(1, &sensor_info->ldo[index]);
		if (rc) {
			cam_err("failed to enable regulators %d\n", rc);
			return rc;
		}
		if (0 != power_setting->delay) {
			camdrv_msleep(power_setting->delay);
		}
	} else {
		regulator_bulk_disable(1, &sensor_info->ldo[index]);
		rc = 0;
	}

	return rc;

}

void hisi_sensor_i2c_config(struct hisi_sensor_ctrl_t *s_ctrl,
	struct sensor_power_setting *power_setting, int state)
{
	cam_debug("enter %s, state:%d", __func__, state);

	if (is_fpga_board())
		return;

	if (POWER_ON == state) {
		isp_config_i2c(&s_ctrl->sensor->sensor_info->i2c_config);

		if (0 != power_setting->delay) {
			camdrv_msleep(power_setting->delay);
		}
	}

	return;
}

#ifdef SEATTLE_FPGA
#define GPIO_8_0	64
#define GPIO_8_1	65
#define GPIO_8_2	66
#define GPIO_8_3	67
#define GPIO_8_4	68
#define GPIO_8_5	69
#define GPIO_8_6	70
#define GPIO_8_7	71

#define GPIO_9_0	72
#define GPIO_9_1	73
#define GPIO_9_2	74
#define GPIO_9_3	75
#define GPIO_9_4	76
#define GPIO_9_5	77
#define GPIO_9_6	78
#define GPIO_9_7	79

#define GPIO_10_0	80
#define GPIO_10_1	81
#define GPIO_10_2	82
#define GPIO_10_3	83
#define GPIO_10_4	84
#define GPIO_10_5	85
#define GPIO_10_6	86
#define GPIO_10_7	87

#define GPIO_11_0	88
#define GPIO_11_1	89
#define GPIO_11_2	90
#define GPIO_11_3	91
#define GPIO_11_4	92
#define GPIO_11_5	93
#define GPIO_11_6	94
#define GPIO_11_7	95

#define GPIO_12_0	96
#define GPIO_12_1	97
#define GPIO_12_2	98
#define GPIO_12_3	99
#define GPIO_12_4	100
#define GPIO_12_5	101
#define GPIO_12_6	102
#define GPIO_12_7	103

#define GPIO_13_0	104
#define GPIO_13_1	105
#define GPIO_13_2	106
#define GPIO_13_3	107
#define GPIO_13_4	108
#define GPIO_13_5	109
#define GPIO_13_6	110
#define GPIO_13_7	111

typedef enum sensor_index_t {
	PRI_SENSOR = 0,
	SEC_SENSOR,

	MAX_SENSOR
} sensor_index;


#define LOW 0
#define HIGH 1

struct sensor_poweron {
	/* lable */
	const char *l_reset;
	u16 reset[MAX_SENSOR];
	const char *l_power;
	u16 power[MAX_SENSOR];

	const char *l_txrx_byteclkhs_sel;
	u16 txrx_byteclkhs_sel[MAX_SENSOR];
	const char *l_cameralog_vcc;
	u16 cameralog_vcc[MAX_SENSOR];
	const char *l_camera_core;
	u16 camera_core[MAX_SENSOR];
	const char *l_camera_vcc;
	u16 camera_vcc[MAX_SENSOR];
};

static const struct sensor_poweron sensor_gpois = {
	.l_reset = "camera_reset",
	.reset = {
		[PRI_SENSOR] = GPIO_12_3,
		[SEC_SENSOR] = GPIO_10_6,
	},
	.l_power = "camera_power",
	.power = {
		[PRI_SENSOR] = GPIO_12_1,
		[SEC_SENSOR] = GPIO_10_4,
	},
	.l_txrx_byteclkhs_sel = "txrx_byteclkhs_sel",
	.txrx_byteclkhs_sel = {
		[PRI_SENSOR] = GPIO_11_6,
		[SEC_SENSOR] = GPIO_10_1,
	},
	.l_cameralog_vcc = "cameralog-vcc",
	.cameralog_vcc = {
		[PRI_SENSOR] = GPIO_13_0,
		[SEC_SENSOR] = GPIO_11_3,
	},
	.l_camera_core = "camera-core",
	.camera_core= {
		[PRI_SENSOR] = GPIO_13_1,
		[SEC_SENSOR] = GPIO_11_4,
	},
	.l_camera_vcc = "camera-vcc",
	.camera_vcc = {
		[PRI_SENSOR] = GPIO_12_5,
		[SEC_SENSOR] = GPIO_11_0,
	},
};

int hisi_sensor_power_up_fpga(struct hisi_sensor_ctrl_t *s_ctrl)
{
	int ret = 0;
	int index = 0;
	u32 regbase = 0x63600 + 0x0;
	cam_notice("%s,enter", __func__);

	//primary camera reset OK
	gpio_request(sensor_gpois.reset[index], sensor_gpois.l_reset);
	gpio_direction_output(sensor_gpois.reset[index], HIGH);
	msleep(1);

	//primary camera powerdown OK
	gpio_request(sensor_gpois.power[index], sensor_gpois.l_power);
	gpio_direction_output(sensor_gpois.power[index], LOW);
	msleep(1);

	//TXRX_BYTECLKHS_SEL
	gpio_request(sensor_gpois.txrx_byteclkhs_sel[index], sensor_gpois.l_txrx_byteclkhs_sel);
	gpio_direction_output(sensor_gpois.txrx_byteclkhs_sel[index], HIGH);
	msleep(1);

	//"cameralog-vcc", 2.85V OK
	gpio_request(sensor_gpois.cameralog_vcc[index], sensor_gpois.l_cameralog_vcc);
	gpio_direction_output(sensor_gpois.cameralog_vcc[index], HIGH);
	msleep(1);

	//"camera-core",  1.05V OK
	gpio_request(sensor_gpois.camera_core[index], sensor_gpois.l_camera_core);
	gpio_direction_output(sensor_gpois.camera_core[index], HIGH);
	msleep(1);

	//"camera-vcc",  1.8V OK
	gpio_request(sensor_gpois.camera_vcc[index], sensor_gpois.l_camera_vcc);
	gpio_direction_output(sensor_gpois.camera_vcc[index], HIGH);
	msleep(10);

	/* mclk */
	SETREG8(REG_ISP_CLK_DIVIDER, 0x44);

	/* I2C speed */
	SETREG8(regbase + I2C_SPEED, 0x14);
	SETREG8(regbase + I2C_SLAVE_ID, 0x34);
	return ret;
}
#endif

int hisi_sensor_power_up(struct hisi_sensor_ctrl_t *s_ctrl)
{
	struct sensor_power_setting_array *power_setting_array
		= &s_ctrl->sensor->power_setting_array;
	struct sensor_power_setting *power_setting = NULL;
	int index = 0, rc = 0;

	cam_debug("%s enter.", __func__);

	/* fpga board compatibility */

	if (is_fpga_board()) {
		hisi_sensor_power_up_fpga(s_ctrl);
		return 0;
	}

	for (index = 0; index < power_setting_array->size; index++) {
		power_setting = &power_setting_array->power_setting[index];
		switch(power_setting->seq_type) {
		case SENSOR_DVDD:
			rc = hisi_sensor_ldo_config(LDO_DVDD, s_ctrl->sensor->sensor_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_DVDD2:
			rc = hisi_sensor_ldo_config(LDO_DVDD2, s_ctrl->sensor->sensor_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_IOVDD:
			rc = hisi_sensor_ldo_config(LDO_IOPW, s_ctrl->sensor->sensor_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_AVDD:
			rc = hisi_sensor_ldo_config(LDO_AVDD, s_ctrl->sensor->sensor_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_AVDD2:
			rc = hisi_sensor_ldo_config(LDO_AVDD2, s_ctrl->sensor->sensor_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_VCM_AVDD:
			rc = hisi_sensor_ldo_config(LDO_VCM, s_ctrl->sensor->sensor_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_VCM_AVDD2:
			rc = hisi_sensor_ldo_config(LDO_VCM2, s_ctrl->sensor->sensor_info,
				power_setting, POWER_ON);
			break;

		case SENSOR_MCLK:
			hisi_mclk_config(s_ctrl, power_setting, POWER_ON);
			break;
		case SENSOR_I2C:
			hisi_sensor_i2c_config(s_ctrl, power_setting, POWER_ON);
			break;

		case SENSOR_CHECK_LEVEL:
			rc = hisi_sensor_gpio_config(FSIN, s_ctrl->sensor->sensor_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_RST:
			rc = hisi_sensor_gpio_config(RESETB, s_ctrl->sensor->sensor_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_PWDN:
			rc = hisi_sensor_gpio_config(PWDN, s_ctrl->sensor->sensor_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_VCM_PWDN:
			rc = hisi_sensor_gpio_config(VCM, s_ctrl->sensor->sensor_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_SUSPEND:
			rc = hisi_sensor_gpio_config(SUSPEND, s_ctrl->sensor->sensor_info,
				power_setting, POWER_ON);
			break;

		default:
			cam_err("%s invalid seq_type.", __func__);
			break;
		}

		if(rc) {
			cam_err("%s power up procedure error.", __func__);
			break;
		}
	}
	return rc;
}

int hisi_sensor_power_down(struct hisi_sensor_ctrl_t *s_ctrl)
{
	struct sensor_power_setting_array *power_setting_array
		= &s_ctrl->sensor->power_setting_array;
	struct sensor_power_setting *power_setting = NULL;
	int index = 0, rc = 0;

	cam_debug("%s enter.", __func__);

	for (index = (power_setting_array->size - 1); index >= 0; index--) {
		power_setting = &power_setting_array->power_setting[index];
		switch(power_setting->seq_type) {
		case SENSOR_DVDD:
			rc = hisi_sensor_ldo_config(LDO_DVDD, s_ctrl->sensor->sensor_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_DVDD2:
			rc = hisi_sensor_ldo_config(LDO_DVDD2, s_ctrl->sensor->sensor_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_IOVDD:
			rc = hisi_sensor_ldo_config(LDO_IOPW, s_ctrl->sensor->sensor_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_AVDD:
			rc = hisi_sensor_ldo_config(LDO_AVDD, s_ctrl->sensor->sensor_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_AVDD2:
			rc = hisi_sensor_ldo_config(LDO_AVDD2, s_ctrl->sensor->sensor_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_VCM_AVDD:
			rc = hisi_sensor_ldo_config(LDO_VCM, s_ctrl->sensor->sensor_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_VCM_AVDD2:
			rc = hisi_sensor_ldo_config(LDO_VCM2, s_ctrl->sensor->sensor_info,
				power_setting, POWER_OFF);
			break;


		case SENSOR_MCLK:
			hisi_mclk_config(s_ctrl, power_setting, POWER_OFF);
			break;
		case SENSOR_I2C:
			break;

		case SENSOR_CHECK_LEVEL:
			break;
		case SENSOR_PWDN:
			rc = hisi_sensor_gpio_config(PWDN, s_ctrl->sensor->sensor_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_RST:
			rc = hisi_sensor_gpio_config(RESETB, s_ctrl->sensor->sensor_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_VCM_PWDN:
			rc = hisi_sensor_gpio_config(VCM, s_ctrl->sensor->sensor_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_SUSPEND:
			break;

		default:
			cam_err("%s invalid seq_type.", __func__);
			break;
		}

	}
	return rc;
}

int hisi_sensor_i2c_read(struct hisi_sensor_ctrl_t *s_ctrl, void *data)
{
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
	long   rc = 0;
	unsigned int reg, *val;

	cam_debug("%s: address=0x%x\n", __func__, cdata->cfg.reg.subaddr);

	/* parse the I2C parameters */
	reg = cdata->cfg.reg.subaddr;
	val = &cdata->cfg.reg.value;

	rc = isp_read_sensor_byte(&s_ctrl->sensor->sensor_info->i2c_config, reg, (u16 *)val);

	return rc;
}

int hisi_sensor_i2c_write(struct hisi_sensor_ctrl_t *s_ctrl, void *data)
{
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
	long   rc = 0;
	unsigned int reg, val, mask;

	cam_debug("%s enter.\n", __func__);

	cam_debug("%s: address=0x%x, value=0x%x\n", __func__,
		cdata->cfg.reg.subaddr, cdata->cfg.reg.value);

	/* parse the I2C parameters */
	reg = cdata->cfg.reg.subaddr;
	val = cdata->cfg.reg.value;
	mask = cdata->cfg.reg.mask;

	rc = isp_write_sensor_byte(&s_ctrl->sensor->sensor_info->i2c_config, reg, val, mask);

	return rc;
}

int hisi_sensor_i2c_read_seq(struct hisi_sensor_ctrl_t *s_ctrl, void *data)
{
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
	struct sensor_i2c_setting setting;
	int size = sizeof(struct sensor_i2c_reg)*cdata->cfg.setting.size;
	long rc = 0;

	cam_debug("%s: enter.\n", __func__);

	setting.setting = (struct sensor_i2c_reg*)kzalloc(size, GFP_KERNEL);
	if (NULL == setting.setting) {
		cam_err("%s kmalloc error.\n", __func__);
		return -ENOMEM;
	}

	if (copy_from_user(setting.setting,
		(void __user *)cdata->cfg.setting.setting, size)) {
		cam_err("%s copy_from_user error.\n", __func__);
		rc = -EFAULT;
		goto fail;
	}

	/* test */
	{
		int i=0;
		for(i=0; i<cdata->cfg.setting.size; i++) {
			cam_debug("%s subaddr=0x%x.\n",
				__func__,
				setting.setting[i].subaddr);
				setting.setting[i].value = i;
		}
	}

	if (copy_to_user((void __user *)cdata->cfg.setting.setting,
		setting.setting, size)) {
		cam_err("%s copy_to_user error.\n", __func__);
		rc = -EFAULT;
		goto fail;
	}

fail:
	kfree(setting.setting);
	return rc;
}

int hisi_sensor_i2c_write_seq(struct hisi_sensor_ctrl_t *s_ctrl, void *data)
{
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
	struct sensor_i2c_setting setting;
	int data_length = sizeof(struct sensor_i2c_reg)*cdata->cfg.setting.size;
	long rc = 0;

	cam_info("%s: enter setting=0x%x size=%d.\n", __func__,
			(unsigned int)cdata->cfg.setting.setting,
			(unsigned int)cdata->cfg.setting.size);

	setting.setting = (struct sensor_i2c_reg*)kzalloc(data_length, GFP_KERNEL);
	if (NULL == setting.setting) {
		cam_err("%s kmalloc error.\n", __func__);
		return -ENOMEM;
	}

	if (copy_from_user(setting.setting,
		(void __user *)cdata->cfg.setting.setting, data_length)) {
		cam_err("%s copy_from_user error.\n", __func__);
		rc = -EFAULT;
		goto out;
	}

	rc = isp_write_sensor_seq(&s_ctrl->sensor->sensor_info->i2c_config, setting.setting, cdata->cfg.setting.size);
out:
	kfree(setting.setting);
	return rc;
}
