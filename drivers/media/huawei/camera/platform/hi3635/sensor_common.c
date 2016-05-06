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
#include "sensor_commom.h"
#include "hw_cci.h"
#include "hw_isp_io.h"
#include "hw_pmic.h"
#include "extisp.h"
//#include "isp_ops.h"

#define SEATTLE_FPGA

extern bool is_ovisp23_poweron(void);

void hwcam_mclk_enable(int index, int enable)
{
	cam_info("%s index = %d, enable=%d", __func__,index, enable);

	if (POWER_ON == enable) {
		if (CAMERA_SENSOR_PRIMARY == index) {
			ISP_SETREG8(REG_ISP_CLK_DIVIDER, 0x44);
		} else {
			ISP_SETREG8(REG_ISP_CLK_DIVIDER, 0x44);
		}
	} else {
		ISP_SETREG8(REG_ISP_CLK_DIVIDER, 0);
	}
}


int hw_mclk_config(sensor_t *s_ctrl,
	struct sensor_power_setting *power_setting, int state)
{
	int sensor_index;

	cam_debug("%s enter.state:%d", __func__, state);
	if (!is_ovisp23_poweron()) {
		cam_notice("%s the ovisp has powered down.", __func__);
		return 0;
	}

	if (SENSOR_INDEX_INVALID != power_setting->sensor_index) {
		sensor_index = power_setting->sensor_index;
	} else {
		sensor_index = s_ctrl->board_info->sensor_index;
	}

	if (hw_is_fpga_board())
		return 0;

	hwcam_mclk_enable(sensor_index, state);

	if (0 != power_setting->delay) {
		hw_camdrv_msleep(power_setting->delay);
	}

	return 0;
}

int hw_sensor_gpio_config(gpio_t pin_type, hwsensor_board_info_t *sensor_info,
	struct sensor_power_setting *power_setting, int state)
{
	int rc = -1;

	cam_debug("%s enter, pin_type: %d", __func__, pin_type);

	if (hw_is_fpga_board())
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
		} else {
                cam_debug("%s config gpio[%d] output[%d].", __func__,
                 sensor_info->gpios[pin_type].gpio,
                (state ? (power_setting->config_val + 1) % 2 : power_setting->config_val));
        }
	}

	gpio_free(sensor_info->gpios[pin_type].gpio);

	if (0 != power_setting->delay) {
		hw_camdrv_msleep(power_setting->delay);
	}

	return rc;

}

int hw_sensor_ldo_config(ldo_index_t ldo, hwsensor_board_info_t *sensor_info,
	struct sensor_power_setting *power_setting, int state)
{
	int index;
	int rc = -1;
	const char *ldo_names[LDO_MAX]
		= {"dvdd", "dvdd2", "avdd", "avdd2", "vcm", "vcm2", "iopw","miniisp"};

	cam_debug("%s enter, ldo: %d", __func__, ldo);

	if (hw_is_fpga_board())
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
		if((LDO_IOPW != ldo) && (LDO_MINI_ISP != ldo)) {
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
			hw_camdrv_msleep(power_setting->delay);
		}
	} else {
		regulator_bulk_disable(1, &sensor_info->ldo[index]);
		rc = 0;
	}

	return rc;

}

void hw_sensor_i2c_config(sensor_t *s_ctrl,
	struct sensor_power_setting *power_setting, int state)
{
	cam_debug("enter %s, state:%d", __func__, state);

	if (hw_is_fpga_board())
		return;

	if (POWER_ON == state) {
		hw_isp_config_i2c(&s_ctrl->board_info->i2c_config);

		if (0 != power_setting->delay) {
			hw_camdrv_msleep(power_setting->delay);
		}
	}

	return;
}

extern struct hisi_pmic_ctrl_t ncp6925_ctrl;
int hw_sensor_pmic_config(hwsensor_board_info_t *sensor_info,
	struct sensor_power_setting *power_setting, int state)
{
    int rc = 0;
    cam_notice("%s enter.", __func__);
    cam_notice("%s seq_val=%d, config_val=%d, state=%d",
        __func__, power_setting->seq_val, power_setting->config_val, state);
    //todo ...
    //use wangzhengyong pmic interface
    if (ncp6925_ctrl.func_tbl->pmic_seq_config) {
	rc = ncp6925_ctrl.func_tbl->pmic_seq_config(&ncp6925_ctrl, power_setting->seq_val, power_setting->config_val, state);
    }

    if (0 != power_setting->delay) {
    	hw_camdrv_msleep(power_setting->delay);
    }

    return rc;
}

#ifdef SEATTLE_FPGA
//#define GPIO_8_0	64
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
//#define GPIO_13_2	106
//#define GPIO_13_3	107
//#define GPIO_13_4	108
//#define GPIO_13_5	109
//#define GPIO_13_6	110
//#define GPIO_13_7	111

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

int hisi_sensor_power_up_fpga(void)
{
    int ret = 0;
    int index = 0;
    int rc = 0;
    u32 regbase = 0x63600 + 0x0;
    cam_notice("%s,enter", __func__);

    //primary camera reset OK
    rc = gpio_request(sensor_gpois.reset[index], sensor_gpois.l_reset);
    if(rc < 0) {
        cam_err("failed to request gpio reset");
        return rc;
    }
    gpio_direction_output(sensor_gpois.reset[index], HIGH);
    msleep(1);

    //primary camera powerdown OK
    rc = gpio_request(sensor_gpois.power[index], sensor_gpois.l_power);
    if(rc < 0) {
        cam_err("failed to request gpio power");
        goto err1;
    }
    gpio_direction_output(sensor_gpois.power[index], LOW);
    msleep(1);

    //TXRX_BYTECLKHS_SEL
    rc = gpio_request(sensor_gpois.txrx_byteclkhs_sel[index], sensor_gpois.l_txrx_byteclkhs_sel);
    if(rc < 0) {
        cam_err("failed to request gpio txrx_byteclkhs_sel");
        goto err2;
    }
    gpio_direction_output(sensor_gpois.txrx_byteclkhs_sel[index], HIGH);
    msleep(1);

    //"cameralog-vcc", 2.85V OK
    rc = gpio_request(sensor_gpois.cameralog_vcc[index], sensor_gpois.l_cameralog_vcc);
    if(rc < 0) {
        cam_err("failed to request gpio cameralog_vcc");
        goto err3;
    }
    gpio_direction_output(sensor_gpois.cameralog_vcc[index], HIGH);
    msleep(1);

    //"camera-core",  1.05V OK
    rc = gpio_request(sensor_gpois.camera_core[index], sensor_gpois.l_camera_core);
    if(rc < 0) {
        cam_err("failed to request gpio camera_core");
        goto err4;
    }
    gpio_direction_output(sensor_gpois.camera_core[index], HIGH);
    msleep(1);

    //"camera-vcc",  1.8V OK
    rc = gpio_request(sensor_gpois.camera_vcc[index], sensor_gpois.l_camera_vcc);
    if(rc < 0) {
        cam_err("failed to request gpio camera_vcc");
        goto err5;
    }
    gpio_direction_output(sensor_gpois.camera_vcc[index], HIGH);
    msleep(10);

    /* mclk */
    ISP_SETREG8(REG_ISP_CLK_DIVIDER, 0x44);

    /* I2C speed */
    ISP_SETREG8((regbase + I2C_SPEED), 0x14);
    ISP_SETREG8((regbase + I2C_SLAVE_ID), 0x34);
    gpio_free(sensor_gpois.camera_vcc[index]);
err5:
    gpio_free(sensor_gpois.camera_core[index]);
err4:
    gpio_free(sensor_gpois.cameralog_vcc[index]);
err3:
    gpio_free(sensor_gpois.txrx_byteclkhs_sel[index]);
err2:
    gpio_free(sensor_gpois.power[index]);
err1:
    gpio_free(sensor_gpois.reset[index]);
    return ret;
}
#endif


int hw_sensor_power_up(sensor_t *s_ctrl)
{
	struct sensor_power_setting_array *power_setting_array
		= &s_ctrl->power_setting_array;
	struct sensor_power_setting *power_setting = NULL;
	int index = 0, rc = 0;
	struct hisi_pmic_ctrl_t *pmic_ctrl = NULL;

	cam_debug("%s enter.", __func__);

	/* fpga board compatibility */

	if (hw_is_fpga_board()) {
		hisi_sensor_power_up_fpga();
		return 0;
	}

	pmic_ctrl = hisi_get_pmic_ctrl();
	if(pmic_ctrl != NULL) {
		cam_info("pmic power on!");
		pmic_ctrl->func_tbl->pmic_on(pmic_ctrl, 0);
	}

	for (index = 0; index < power_setting_array->size; index++) {
		power_setting = &power_setting_array->power_setting[index];
		switch(power_setting->seq_type) {
		case SENSOR_DVDD:
			rc = hw_sensor_ldo_config(LDO_DVDD, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_DVDD2:
			rc = hw_sensor_ldo_config(LDO_DVDD2, s_ctrl->board_info,
				power_setting, POWER_ON);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_IOVDD:
			rc = hw_sensor_ldo_config(LDO_IOPW, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_AVDD:
			rc = hw_sensor_ldo_config(LDO_AVDD, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_AVDD2:
			rc = hw_sensor_ldo_config(LDO_AVDD2, s_ctrl->board_info,
				power_setting, POWER_ON);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_VCM_AVDD:
			rc = hw_sensor_ldo_config(LDO_VCM, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_VCM_AVDD2:
			rc = hw_sensor_ldo_config(LDO_VCM2, s_ctrl->board_info,
				power_setting, POWER_ON);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_MINIISP_VPP:
			rc = hw_sensor_ldo_config(LDO_MINI_ISP, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_MCLK:
			rc = hw_mclk_config(s_ctrl, power_setting, POWER_ON);
			break;
		case SENSOR_I2C:
			hw_sensor_i2c_config(s_ctrl, power_setting, POWER_ON);
			break;

		case SENSOR_CHECK_LEVEL:
			rc = hw_sensor_gpio_config(FSIN, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_RST:
			rc = hw_sensor_gpio_config(RESETB, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_PWDN:
			rc = hw_sensor_gpio_config(PWDN, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_VCM_PWDN:
			rc = hw_sensor_gpio_config(VCM, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_SUSPEND:
			rc = hw_sensor_gpio_config(SUSPEND, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_RST2:
			rc = hw_sensor_gpio_config(RESETB2, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_OIS:
			rc = hw_sensor_gpio_config(OIS, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_OIS2:
			rc = hw_sensor_gpio_config(OIS2, s_ctrl->board_info,
				power_setting, POWER_ON);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_PMIC:
			rc = hw_sensor_pmic_config(s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_CS:
			rc = misp_init();
			break;
		case SENSOR_LDO_EN:
			gpio_direction_output(66,1);
			rc = hw_sensor_gpio_config(LDO_EN, s_ctrl->board_info,
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

int hw_sensor_power_down(sensor_t *s_ctrl)
{
	struct sensor_power_setting_array *power_setting_array
		= &s_ctrl->power_setting_array;
	struct sensor_power_setting *power_setting = NULL;
	int index = 0, rc = 0;
	struct hisi_pmic_ctrl_t *pmic_ctrl = NULL;


	cam_debug("%s enter.", __func__);

	//according to hardware request:pull down reset before power down
	for (index = (power_setting_array->size - 1); index >= 0; index--) {
		power_setting = &power_setting_array->power_setting[index];
		if(power_setting->seq_type == SENSOR_CS) {
			misp_exit();
		}
	}

	for (index = (power_setting_array->size - 1); index >= 0; index--) {
		power_setting = &power_setting_array->power_setting[index];
		switch(power_setting->seq_type) {
		case SENSOR_DVDD:
			rc = hw_sensor_ldo_config(LDO_DVDD, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_DVDD2:
			rc = hw_sensor_ldo_config(LDO_DVDD2, s_ctrl->board_info,
				power_setting, POWER_OFF);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_IOVDD:
			rc = hw_sensor_ldo_config(LDO_IOPW, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_AVDD:
			rc = hw_sensor_ldo_config(LDO_AVDD, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_AVDD2:
			rc = hw_sensor_ldo_config(LDO_AVDD2, s_ctrl->board_info,
				power_setting, POWER_OFF);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_VCM_AVDD:
			rc = hw_sensor_ldo_config(LDO_VCM, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_VCM_AVDD2:
			rc = hw_sensor_ldo_config(LDO_VCM2, s_ctrl->board_info,
				power_setting, POWER_OFF);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
        case SENSOR_MINIISP_VPP:
			rc = hw_sensor_ldo_config(LDO_MINI_ISP, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;

		case SENSOR_MCLK:
			hw_mclk_config(s_ctrl, power_setting, POWER_OFF);
			break;
		case SENSOR_I2C:
			break;

		case SENSOR_CHECK_LEVEL:
			break;
		case SENSOR_PWDN:
			rc = hw_sensor_gpio_config(PWDN, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_RST:
			rc = hw_sensor_gpio_config(RESETB, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_VCM_PWDN:
			rc = hw_sensor_gpio_config(VCM, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_SUSPEND:
			rc = hw_sensor_gpio_config(SUSPEND, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_RST2:
			rc = hw_sensor_gpio_config(RESETB2, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_OIS:
			rc = hw_sensor_gpio_config(OIS, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_OIS2:
			rc = hw_sensor_gpio_config(OIS2, s_ctrl->board_info,
				power_setting, POWER_OFF);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_PMIC:
			rc = hw_sensor_pmic_config(s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_CS:
			rc = misp_exit();
			break;
		case SENSOR_LDO_EN:
			rc = hw_sensor_gpio_config(LDO_EN, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		default:
			cam_err("%s invalid seq_type.", __func__);
			break;
		}

	}

	pmic_ctrl = hisi_get_pmic_ctrl();
	if(pmic_ctrl != NULL) {
		pmic_ctrl->func_tbl->pmic_off(pmic_ctrl);
	}

	return rc;
}

int hw_sensor_i2c_read(sensor_t *s_ctrl, void *data)
{
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
	long   rc = 0;
	unsigned int reg, *val;

	cam_debug("%s: address=0x%x\n", __func__, cdata->cfg.reg.subaddr);

	/* parse the I2C parameters */
	reg = cdata->cfg.reg.subaddr;
	val = &cdata->cfg.reg.value;

	rc = hw_isp_read_sensor_byte(&s_ctrl->board_info->i2c_config, reg, (u16 *)val);

	return rc;
}

int hw_sensor_i2c_write(sensor_t *s_ctrl, void *data)
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

	rc = hw_isp_write_sensor_byte(&s_ctrl->board_info->i2c_config, reg, val, mask);

	return rc;
}

int hw_sensor_i2c_read_seq(sensor_t *s_ctrl, void *data)
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

	/* test
	{
		int i=0;
		for(i=0; i<cdata->cfg.setting.size; i++) {
			cam_debug("%s subaddr=0x%x.\n",
				__func__,
				setting.setting[i].subaddr);
				setting.setting[i].value = i;
		}
	}
	*/
	{
		int i=0;
		struct sensor_cfg_data temp;
		memset(&temp,0,sizeof(struct sensor_cfg_data));
		for(i=0; i<cdata->cfg.setting.size; i++) {
			temp.cfg.reg.subaddr = setting.setting[i].subaddr;
			temp.cfg.reg.mask = setting.setting[i].mask;
			hw_sensor_i2c_read(s_ctrl,&temp);
			setting.setting[i].value = temp.cfg.reg.value;
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

int hw_sensor_i2c_write_seq( sensor_t *s_ctrl, void *data)
{
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
	struct sensor_i2c_setting setting;
	int data_length = sizeof(struct sensor_i2c_reg)*cdata->cfg.setting.size;
	long rc = 0;

	cam_info("%s: enter setting=%p size=%d.\n", __func__,
			cdata->cfg.setting.setting,
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

	rc = hw_isp_write_sensor_seq(&s_ctrl->board_info->i2c_config, setting.setting, cdata->cfg.setting.size);
out:
	kfree(setting.setting);
	return rc;
}
#if 0
int hisi_sensor_apply_expo_gain(struct hisi_sensor_ctrl_t *s_ctrl, void *data)
{
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
	struct expo_gain_seq me_seq = cdata->cfg.me_seq;
	struct hisi_sensor_t *sensor = s_ctrl->sensor;
	int i;

	cam_notice("seq_size[%d]", me_seq.seq_size);
	for(i = 0; i < me_seq.seq_size; i++) {
		cam_notice("expo[0x%04x], gain[0x%02x]", me_seq.expo[i], me_seq.gain[i]);
	}
	cam_notice("eof trigger[%d]\n", me_seq.eof_trigger);

	if(sensor->sensor_info->sensor_type == 1) {/*ov sensor*/
		memmove(me_seq.gain + 1, me_seq.gain, sizeof(u32) * me_seq.seq_size);
		me_seq.expo[me_seq.seq_size] = me_seq.expo[me_seq.seq_size - 1];
		me_seq.seq_size++;
	}

	for(i = 0; i < me_seq.seq_size; i++) {
		cam_notice("expo[0x%04x], gain[0x%02x], hts[0x%02x], vts[0x%02x]",
			me_seq.expo[i], me_seq.gain[i], me_seq.hts, me_seq.vts);
	}

	return hw_setup_eof_tasklet(sensor, &me_seq);

}

int hisi_sensor_suspend_eg_task(struct hisi_sensor_ctrl_t *s_ctrl)
{
	cam_notice("enter %s", __func__);

	return hw_destory_eof_tasklet();
}
#endif

int hwsensor_writefile(int index, const char *sensor_name)
{
    mm_segment_t fs;
    struct file *filp = NULL;
    char file_name[FILE_NAME_LEN]={0};
    char data[FILE_NAME_LEN]={0};
    int rc=0;
    int pos = index;

    if (index == CAMERA_SENSOR_INVALID)
        return -1;
    cam_info("%s index=%d,sensor_name=%s.\n", __func__, index, sensor_name);

    snprintf(file_name, FILE_NAME_LEN, "/data/camera/hisi_sensor%d", index);

    filp = filp_open(file_name, O_CREAT|O_WRONLY, 0666);
    if (IS_ERR_OR_NULL(filp)) {
        rc = -EFAULT;
        cam_err("%s, fail to open file.\n", __func__);
        return rc;
    }

    fs = get_fs();
    set_fs(KERNEL_DS);

    if (sizeof(pos) != vfs_write(filp, (char*)&pos, sizeof(pos), &filp->f_pos)) {
        rc = -EFAULT;
        cam_err("%s, fail to write pos into file.\n", __func__);
        goto fail;
    }

    snprintf(data, FILE_NAME_LEN, ":%s", sensor_name);
    if (sizeof(data) != vfs_write(filp, data, sizeof(data), &filp->f_pos)) {
        rc = -EFAULT;
        cam_err("%s, fail to write sensor name into file.\n", __func__);
    }

fail:
    set_fs(fs);
    filp_close(filp, NULL);

    return rc;
}
int hw_sensor_get_dt_data(struct platform_device *pdev,
	sensor_t *sensor)
{
	struct device_node *of_node = pdev->dev.of_node;
	hwsensor_board_info_t *sensor_info = NULL;
	int rc = 0;
	u32 i, index = 0;
	char *gpio_tag = NULL;
	const char *gpio_ctrl_types[IO_MAX] =
		{"reset", "fsin", "pwdn", "vcm_pwdn", "suspend", "reset2", "ldo_en", "ois", "ois2"};

	cam_debug("enter %s", __func__);
	sensor_info = kzalloc(sizeof(hwsensor_board_info_t),
				GFP_KERNEL);
	if (!sensor_info) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return -ENOMEM;
	}
	sensor->board_info= sensor_info;

	rc = of_property_read_string(of_node, "huawei,sensor_name",
		&sensor_info->name);
	cam_debug("%s huawei,sensor_name %s, rc %d\n", __func__,
		sensor_info->name, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,extisp_type",
	&sensor_info->extisp_type);
	cam_debug("%s huawei,extisp_type %d, rc %d\n", __func__,
		sensor_info->extisp_type, rc);
	if (rc < 0) {
		sensor_info->extisp_type = EXTISP_NULL;
		cam_err("%s failed %d\n", __func__, __LINE__);
		//goto fail;
	}


	rc = of_property_read_u32(of_node, "huawei,sensor_index",
		(u32*)(&sensor_info->sensor_index));
	cam_debug("%s huawei,sensor_index %d, rc %d\n", __func__,
		sensor_info->sensor_index, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,interface_type",
		&sensor_info->interface_type);
	cam_debug("%s huawei,interface_type %d, rc %d\n", __func__,
		sensor_info->interface_type, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,csi_lane",
		&sensor_info->csi_lane);
	cam_debug("%s huawei,csi_lane %d, rc %d\n", __func__,
		sensor_info->csi_lane, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,csi_mipi_clk",
		&sensor_info->csi_mipi_clk);
	cam_debug("%s huawei,csi_mipi_clk %d, rc %d\n", __func__,
		sensor_info->csi_mipi_clk, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,csi_index",
		&sensor_info->csi_index);
	cam_debug("%s huawei,csi_index %d, rc %d\n", __func__,
		sensor_info->csi_index, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,pd_valid",
		&sensor_info->power_conf.pd_valid);
	cam_debug("%s huawei,pd_valid %d, rc %d\n", __func__,
		sensor_info->power_conf.pd_valid, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,reset_valid",
		&sensor_info->power_conf.reset_valid);
	cam_debug("%s huawei,reset_valid %d, rc %d\n", __func__,
		sensor_info->power_conf.reset_valid, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,vcmpd_valid",
		&sensor_info->power_conf.vcmpd_valid);
	cam_debug("%s huawei,vcmpd_valid %d, rc %d\n", __func__,
		sensor_info->power_conf.vcmpd_valid, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,i2c-index",
		&sensor_info->i2c_config.index);
	cam_debug("%s huawei,i2c-index %d, rc %d\n", __func__,
		sensor_info->i2c_config.index, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,i2c-speed",
		&sensor_info->i2c_config.speed);
	cam_debug("%s huawei,i2c-speed %d, rc %d\n", __func__,
		sensor_info->i2c_config.speed, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,i2c-addr",
		&sensor_info->i2c_config.addr);
	cam_debug("%s huawei,i2c-addr 0x%x, rc %d\n", __func__,
		sensor_info->i2c_config.addr, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,i2c-addr_bits",
		&sensor_info->i2c_config.addr_bits);
	cam_debug("%s huawei,i2c-addr_bits %d, rc %d\n", __func__,
		sensor_info->i2c_config.addr_bits, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,i2c-val_bits",
		&sensor_info->i2c_config.val_bits);
	cam_debug("%s huawei,i2c-val_bits %d, rc %d\n", __func__,
		sensor_info->i2c_config.val_bits, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,sensor_chipid",
		&sensor_info->sensor_chipid);
	cam_debug("%s huawei,sensor_chipid 0x%x, rc %d\n", __func__,
		sensor_info->sensor_chipid, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,camif_id",
		&sensor_info->camif_id);
	cam_debug("%s huawei,camif_id 0x%x, rc %d\n", __func__,
		sensor_info->camif_id, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,vcm_enable",
		&sensor_info->vcm_enable);
	cam_debug("%s huawei,vcm_enable %d, rc %d\n", __func__,
		sensor_info->vcm_enable, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,sensor_type",
		&sensor_info->sensor_type);
	cam_debug("%s huawei,sensor_type %d, rc %d\n", __func__,
		sensor_info->sensor_type, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	if (sensor_info->vcm_enable) {
		rc = of_property_read_string(of_node, "huawei,vcm_name",
			&sensor_info->vcm_name);
		cam_debug("%s huawei,vcm_name %s, rc %d\n", __func__,
			sensor_info->vcm_name, rc);
		if (rc < 0) {
			cam_err("%s failed %d\n", __func__, __LINE__);
			goto fail;
		}
	}

	if (hw_is_fpga_board())
		return rc;

	/* get ldo */
	sensor_info->ldo_num = of_property_count_strings(of_node, "huawei,ldo-names");
	if(sensor_info->ldo_num < 0) {
			cam_err("%s failed %d\n", __func__, __LINE__);
			goto fail;
	}
	cam_debug("ldo num = %d", sensor_info->ldo_num);
	for (i = 0; i < sensor_info->ldo_num; i++) {
		rc = of_property_read_string_index(of_node, "huawei,ldo-names",
			i, &sensor_info->ldo[i].supply);
		if(rc < 0) {
			cam_err("%s failed %d\n", __func__, __LINE__);
			goto fail;
		}
	}

	rc = devm_regulator_bulk_get(&(pdev->dev), sensor_info->ldo_num, sensor_info->ldo);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	sensor_info->gpio_num = of_gpio_count(of_node);
	if(sensor_info->gpio_num < 0 ) {
			cam_err("%s failed %d, ret is %d\n", __func__, __LINE__, sensor_info->gpio_num);
			goto fail;
	}
	for(i = 0; i < sensor_info->gpio_num; i++) {
		rc = of_property_read_string_index(of_node, "huawei,gpio-ctrl-types",
			i, (const char **)&gpio_tag);
		if(rc < 0) {
			cam_err("%s failed %d\n", __func__, __LINE__);
			goto fail;
		}
		for(index = 0; index < IO_MAX; index++) {
			if(!strcmp(gpio_ctrl_types[index], gpio_tag))
				sensor_info->gpios[index].gpio = of_get_gpio(of_node, i);
		}
		cam_info("gpio ctrl types: %s\n", gpio_tag);
	}

	return rc;
fail:
	cam_err("%s error exit.\n", __func__);
	kfree(sensor_info);
	sensor_info = NULL;
	return rc;
}

void hw_camdrv_msleep(unsigned int ms)
{
	struct timeval now;
	unsigned long jiffies;

	if (ms > 0) {
		now.tv_sec  = ms / 1000;
		now.tv_usec = (ms % 1000) * 1000;
		jiffies = timeval_to_jiffies(&now);
		schedule_timeout_interruptible(jiffies);
	}
}
EXPORT_SYMBOL(hw_camdrv_msleep);

static int is_fpga = 0; //default is no fpga
int hw_is_fpga_board(void)
{
	//cam_debug("%s is_fpga=%d.", __func__, is_fpga);
	return is_fpga;
}
EXPORT_SYMBOL(hw_is_fpga_board);

