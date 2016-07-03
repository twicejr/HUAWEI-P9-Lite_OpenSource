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
#include <linux/clk.h>
#include "sensor_commom.h"
#include "hw_cci.h"
#include "hw_isp_io.h"
#include "hw_pmic.h"
//#include "isp_ops.h"

static int is_fpga = 0; //default is no fpga
static atomic_t volatile s_powered = ATOMIC_INIT(0);

int mclk_config(sensor_t *s_ctrl, unsigned int id, unsigned int clk, int on)
{
    int ret = 0;
    struct device *dev;

    if(NULL == s_ctrl) {
        cam_err("%s invalid parameter.\n", __func__);
        return -1;
    }
    dev = s_ctrl->dev;

    cam_info("%s enter.id(%u), clk(%u), on(%d)", __func__, id, clk, on);



    /* clk_isp_snclk max value is 48000000 */
    if((id > 2) || (clk > 48000000)) {
        cam_err("input(id[%d],clk[%d]) is error!\n", id, clk);
        return -1;
    }

    if(on) {
        if(0 == id) {
            s_ctrl->isp_snclk0 = devm_clk_get(dev, "clk_isp_snclk0");

            if(IS_ERR_OR_NULL(s_ctrl->isp_snclk0)) {
                dev_err(dev, "could not get snclk0.\n");
                ret = PTR_ERR(s_ctrl->isp_snclk0);
                return ret;
            }

            ret = clk_set_rate(s_ctrl->isp_snclk0, clk);
            if(ret < 0) {
                dev_err(dev, "failed set_rate snclk0 rate.\n");
                return ret;
            }

            ret = clk_prepare_enable(s_ctrl->isp_snclk0);
            if(ret) {
                dev_err(dev, "cloud not prepare_enalbe clk_isp_snclk0. \n");
                return ret;
            }
        }else if(1 == id) {
            s_ctrl->isp_snclk1 = devm_clk_get(dev, "clk_isp_snclk1");

            if(IS_ERR_OR_NULL(s_ctrl->isp_snclk1)) {
                dev_err(dev, "could not get snclk1.\n");
                ret = PTR_ERR(s_ctrl->isp_snclk1);
                return ret;
            }

            ret = clk_set_rate(s_ctrl->isp_snclk1, clk);
            if(ret < 0) {
                dev_err(dev, "failed set_rate snclk1 rate.\n");
                return ret;
            }

            ret = clk_prepare_enable(s_ctrl->isp_snclk1);
            if(ret) {
                dev_err(dev, "cloud not prepare_enalbe clk_isp_snclk1. \n");
                return ret;
            }
        }else if(2 == id)
        {
            s_ctrl->isp_snclk2 = devm_clk_get(dev, "clk_isp_snclk2");

            if(IS_ERR_OR_NULL(s_ctrl->isp_snclk2)) {
                dev_err(dev, "could not get snclk2.\n");
                ret = PTR_ERR(s_ctrl->isp_snclk2);
                return ret;
            }

            ret = clk_set_rate(s_ctrl->isp_snclk2, clk);
            if(ret < 0) {
                dev_err(dev, "failed set_rate snclk2 rate.\n");
                return ret;
            }

            ret = clk_prepare_enable(s_ctrl->isp_snclk2);
            if(ret) {
                dev_err(dev, "cloud not prepare_enalbe clk_isp_snclk2. \n");
                return ret;
            }
        }
    } else {
        if((0 == id) && (NULL != s_ctrl->isp_snclk0)) {
            clk_disable_unprepare(s_ctrl->isp_snclk0);
            cam_info("clk_disable_unprepare snclk0.\n");
        }else if((1 == id) && (NULL != s_ctrl->isp_snclk1)) {
            clk_disable_unprepare(s_ctrl->isp_snclk1);
            cam_info("clk_disable_unprepare snclk1.\n");
        }else if((2 == id) && (NULL != s_ctrl->isp_snclk2)) {
            clk_disable_unprepare(s_ctrl->isp_snclk2);
            cam_info("clk_disable_unprepare snclk2.\n");
        }
    }

    return 0;
}

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

	cam_debug("%s enter.state:%d!", __func__, state);

	if (hw_is_fpga_board()) {
		return 0;
	}

	if (SENSOR_INDEX_INVALID != power_setting->sensor_index) {
		sensor_index = power_setting->sensor_index;
	} else {
		sensor_index = s_ctrl->board_info->sensor_index;
	}

	//hwcam_mclk_enable(sensor_index, state);
       mclk_config(s_ctrl,sensor_index,
            s_ctrl->board_info->mclk, state);

	if (0 != power_setting->delay) {
		hw_camdrv_msleep(power_setting->delay);
	}

	return 0;
}

int hw_sensor_gpio_config(gpio_t pin_type, hwsensor_board_info_t *sensor_info,
	struct sensor_power_setting *power_setting, int state)
{
	int rc = -1;

	cam_debug("%s enter, pin_type:%d state:%d delay:%u", __func__, pin_type, state, power_setting->delay);

	if (hw_is_fpga_board())
		return 0;

	if(0 == sensor_info->gpios[pin_type].gpio) {
		cam_err("gpio type[%d] is not actived", pin_type);
		return 0;//skip this
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
		= {"dvdd", "dvdd2", "avdd", "avdd2", "vcm", "vcm2", "iopw","misp", "avdd0", "avdd1"};

	cam_info("%s enter, ldo:%s state:%d", __func__, ldo_names[ldo], state);

	if (hw_is_fpga_board())
		return 0;

	for(index = 0; index < sensor_info->ldo_num; index++) {
		if(!strcmp(sensor_info->ldo[index].supply, ldo_names[ldo]))
			break;
	}

	if(index == sensor_info->ldo_num) {
		cam_err("ldo [%s] is not actived", ldo_names[ldo]);
		return 0;//skip this
	}
	if (POWER_ON == state) {
		if((LDO_IOPW != ldo)) {
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
		rc = regulator_bulk_disable(1, &sensor_info->ldo[index]);
		if (rc) {
			cam_err("failed to disable regulators %d\n", rc);
			return rc;
		}
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
    cam_debug("%s enter.", __func__);
    cam_debug("%s seq_val=%d, config_val=%d, state=%d",
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

int hw_sensor_power_up(sensor_t *s_ctrl)
{
	struct sensor_power_setting_array *power_setting_array
		= &s_ctrl->power_setting_array;
	struct sensor_power_setting *power_setting = NULL;
	int index = 0, rc = 0;
	struct hisi_pmic_ctrl_t *pmic_ctrl = NULL;

	cam_debug("%s enter.", __func__);

	if (atomic_read(&s_powered)) {
		cam_info("%s: sensor has already powered up.", __func__);
		return 0;
	}

	/* fpga board compatibility */
	if (hw_is_fpga_board()) {
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
			cam_debug("%s, seq_type:%u SENSOR_DVDD", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_DVDD, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_DVDD2:
			cam_debug("%s, seq_type:%u SENSOR_DVDD2", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_DVDD2, s_ctrl->board_info,
				power_setting, POWER_ON);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_IOVDD:
			cam_debug("%s, seq_type:%u SENSOR_IOVDD", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_IOPW, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_AVDD:
			cam_debug("%s, seq_type:%u SENSOR_AVDD", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_AVDD, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_AVDD2:
			cam_debug("%s, seq_type:%u SENSOR_AVDD2", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_AVDD2, s_ctrl->board_info,
				power_setting, POWER_ON);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_VCM_AVDD:
			cam_info("%s, seq_type:%u SENSOR_VCM_AVDD", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_VCM, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_VCM_AVDD2:
			cam_info("%s, seq_type:%u SENSOR_VCM_AVDD2", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_VCM2, s_ctrl->board_info,
				power_setting, POWER_ON);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_MCLK:
			cam_info("%s, seq_type:%u SENSOR_MCLK", __func__, power_setting->seq_type);
			rc = hw_mclk_config(s_ctrl, power_setting, POWER_ON);
			break;
		case SENSOR_I2C:
			cam_debug("%s, seq_type:%u SENSOR_I2C", __func__, power_setting->seq_type);
			hw_sensor_i2c_config(s_ctrl, power_setting, POWER_ON);
			break;

		case SENSOR_CHECK_LEVEL:
			cam_debug("%s, seq_type:%u SENSOR_CHECK_LEVEL", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(FSIN, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_RST:
			cam_info("%s, seq_type:%u SENSOR_RST", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(RESETB, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_PWDN:
			cam_debug("%s, seq_type:%u SENSOR_PWDN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(PWDN, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_VCM_PWDN:
			cam_debug("%s, seq_type:%u SENSOR_VCM_PWDN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(VCM, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_SUSPEND:
			cam_debug("%s, seq_type:%u SENSOR_SUSPEND", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(SUSPEND, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_RST2:
			cam_info("%s, seq_type:%u SENSOR_RST2", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(RESETB2, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_OIS:
			cam_debug("%s, seq_type:%u SENSOR_OIS", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(OIS, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_OIS2:
			cam_debug("%s, seq_type:%u SENSOR_OIS2", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(OIS2, s_ctrl->board_info,
				power_setting, POWER_ON);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_PMIC:
			cam_debug("%s, seq_type:%u SENSOR_PMIC", __func__, power_setting->seq_type);
			rc = hw_sensor_pmic_config(s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_CS:
			break;
		case SENSOR_LDO_EN:
			cam_debug("%s, seq_type:%u SENSOR_LDO_EN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(LDO_EN, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;

		case SENSOR_DVDD0_EN:
			cam_info("%s, seq_type:%u SENSOR_DVDD0_EN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(DVDD0_EN, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_DVDD1_EN:
			cam_info("%s, seq_type:%u SENSOR_DVDD1_EN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(DVDD1_EN, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_IOVDD_EN:
			cam_info("%s, seq_type:%u SENSOR_IOVDD_EN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(IOVDD_EN, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_MISPDCDC_EN:
			cam_info("%s, seq_type:%u SENSOR_MISPDCDC_EN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(MISPDCDC_EN, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_AVDD0:
			cam_info("%s, seq_type:%u SENSOR_AVDD0", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_AVDD0, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_AVDD1:
			cam_info("%s, seq_type:%u SENSOR_AVDD1", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_AVDD1, s_ctrl->board_info,
				power_setting, POWER_ON);
			break;
		case SENSOR_MISP_VDD:
			cam_info("%s, seq_type:%u SENSOR_MISP_VDD", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_MISP, s_ctrl->board_info,
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

	atomic_set(&s_powered, 1);
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

	if (!atomic_read(&s_powered)) {
		cam_info("%s: sensor hasn't powered up.", __func__);
		return 0;
	}

	for (index = (power_setting_array->size - 1); index >= 0; index--) {
		power_setting = &power_setting_array->power_setting[index];
		switch(power_setting->seq_type) {
		case SENSOR_DVDD:
			cam_debug("%s, seq_type:%u SENSOR_DVDD", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_DVDD, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_DVDD2:
			cam_debug("%s, seq_type:%u SENSOR_DVDD2", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_DVDD2, s_ctrl->board_info,
				power_setting, POWER_OFF);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_IOVDD:
			cam_debug("%s, seq_type:%u SENSOR_IOVDD", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_IOPW, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_AVDD:
			cam_debug("%s, seq_type:%u SENSOR_AVDD", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_AVDD, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_AVDD2:
			cam_debug("%s, seq_type:%u SENSOR_AVDD", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_AVDD2, s_ctrl->board_info,
				power_setting, POWER_OFF);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_VCM_AVDD:
			cam_debug("%s, seq_type:%u SENSOR_VCM_AVDD", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_VCM, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_VCM_AVDD2:
			cam_debug("%s, seq_type:%u SENSOR_VCM_AVDD2", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_VCM2, s_ctrl->board_info,
				power_setting, POWER_OFF);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;

		case SENSOR_MCLK:
			cam_debug("%s, seq_type:%u SENSOR_MCLK", __func__, power_setting->seq_type);
			hw_mclk_config(s_ctrl, power_setting, POWER_OFF);
			break;
		case SENSOR_I2C:
			break;

		case SENSOR_CHECK_LEVEL:
			break;
		case SENSOR_PWDN:
			cam_debug("%s, seq_type:%u SENSOR_PWDN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(PWDN, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_RST:
			cam_info("%s, seq_type:%u SENSOR_RST", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(RESETB, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_VCM_PWDN:
			cam_debug("%s, seq_type:%u SENSOR_VCM_PWDN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(VCM, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_SUSPEND:
			cam_debug("%s, seq_type:%u SENSOR_SUSPEND", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(SUSPEND, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_RST2:
			cam_debug("%s, seq_type:%u SENSOR_RST2", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(RESETB2, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_OIS:
			cam_debug("%s, seq_type:%u SENSOR_OIS", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(OIS, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_OIS2:
			cam_debug("%s, seq_type:%u SENSOR_OIS2", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(OIS2, s_ctrl->board_info,
				power_setting, POWER_OFF);
			if(rc) {
				cam_err("%s power up procedure error.", __func__);
				rc = 0;
			}
			break;
		case SENSOR_PMIC:
			cam_debug("%s, seq_type:%u SENSOR_PMIC", __func__, power_setting->seq_type);
			rc = hw_sensor_pmic_config(s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_CS:
			break;
		case SENSOR_LDO_EN:
			cam_debug("%s, seq_type:%u SENSOR_LDO_EN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(LDO_EN, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;

		case SENSOR_DVDD0_EN:
			cam_info("%s, seq_type:%u SENSOR_DVDD0_EN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(DVDD0_EN, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_DVDD1_EN:
			cam_info("%s, seq_type:%u SENSOR_DVDD1_EN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(DVDD1_EN, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_IOVDD_EN:
			cam_info("%s, seq_type:%u SENSOR_IOVDD_EN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(IOVDD_EN, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_MISPDCDC_EN:
			cam_info("%s, seq_type:%u SENSOR_MISPDCDC_EN", __func__, power_setting->seq_type);
			rc = hw_sensor_gpio_config(MISPDCDC_EN, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_AVDD0:
			cam_info("%s, seq_type:%u SENSOR_AVDD0", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_AVDD0, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_AVDD1:
			cam_info("%s, seq_type:%u SENSOR_AVDD1", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_AVDD1, s_ctrl->board_info,
				power_setting, POWER_OFF);
			break;
		case SENSOR_MISP_VDD:
			cam_info("%s, seq_type:%u SENSOR_MISP_VDD", __func__, power_setting->seq_type);
			rc = hw_sensor_ldo_config(LDO_MISP, s_ctrl->board_info,
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

	atomic_set(&s_powered, 0);

	return rc;
}

int hw_sensor_power_on(void *psensor)
{
    sensor_t *s_ctrl = NULL;

    if (NULL == psensor) {
        cam_err("%s psensor is NULL!.\n", __func__);
        return -1;
    }

    s_ctrl = (sensor_t*)(psensor);
    return hw_sensor_power_up(s_ctrl);
}
EXPORT_SYMBOL(hw_sensor_power_on);

int hw_sensor_power_off(void *psensor)
{
    sensor_t *s_ctrl = NULL;

    if (NULL == psensor) {
        cam_err("%s psensor is NULL!.\n", __func__);
        return -1;
    }

    s_ctrl = (sensor_t*)(psensor);
    return hw_sensor_power_down(s_ctrl);
}
EXPORT_SYMBOL(hw_sensor_power_off);
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
    if (NULL == data || NULL == s_ctrl) {
		cam_err("%s data or s_ctrl is null.\n", __func__);
		return -EFAULT;
    }
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
	struct sensor_i2c_setting setting;
	int size = sizeof(struct sensor_i2c_reg)*cdata->cfg.setting.size;
	long rc = 0;

	cam_debug("%s: enter.\n", __func__);

	setting.setting = (struct sensor_i2c_reg*)kzalloc(size, GFP_KERNEL);
	if (IS_ERR_OR_NULL(setting.setting)) {
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
	if (NULL == data || NULL == s_ctrl) {
		cam_err("%s data or s_ctrl is null.\n", __func__);
		return -EFAULT;
	}
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
	struct sensor_i2c_setting setting;
	int data_length = sizeof(struct sensor_i2c_reg)*cdata->cfg.setting.size;
	long rc = 0;

	cam_info("%s: enter setting=%p size=%d.\n", __func__,
			cdata->cfg.setting.setting,
			(unsigned int)cdata->cfg.setting.size);

	if (data_length <= 0) {
		cam_err("%s data_length(%d).\n", __func__, data_length);
		return -EFAULT;
	}

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

	cam_debug("seq_size[%d]", me_seq.seq_size);
	for(i = 0; i < me_seq.seq_size; i++) {
		cam_debug("expo[0x%04x], gain[0x%02x]", me_seq.expo[i], me_seq.gain[i]);
	}
	cam_debug("eof trigger[%d]\n", me_seq.eof_trigger);

	if(sensor->sensor_info->sensor_type == 1) {/*ov sensor*/
		memmove(me_seq.gain + 1, me_seq.gain, sizeof(u32) * me_seq.seq_size);
		me_seq.expo[me_seq.seq_size] = me_seq.expo[me_seq.seq_size - 1];
		me_seq.seq_size++;
	}

	for(i = 0; i < me_seq.seq_size; i++) {
		cam_debug("expo[0x%04x], gain[0x%02x], hts[0x%02x], vts[0x%02x]",
			me_seq.expo[i], me_seq.gain[i], me_seq.hts, me_seq.vts);
	}

	return hw_setup_eof_tasklet(sensor, &me_seq);

}

int hisi_sensor_suspend_eg_task(struct hisi_sensor_ctrl_t *s_ctrl)
{
	cam_debug("enter %s", __func__);

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
    int ret = 0;
    int count = 0;
	u32 i, index = 0;
	char *gpio_tag = NULL;
	const char *gpio_ctrl_types[IO_MAX] =
		{"reset", "fsin", "pwdn", "vcm_pwdn", "suspend", "reset2", "ldo_en", "ois", "ois2", "dvdd0-en", "dvdd1-en", "iovdd-en", "mispdcdc-en"};

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

	rc = of_property_read_u32(of_node, "huawei,is_fpga",
		&is_fpga);
	cam_debug("%s huawei,is_fpga: %d, rc %d\n", __func__,
		is_fpga, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

	rc = of_property_read_u32(of_node, "huawei,sensor_index",
		(u32*)(&sensor_info->sensor_index));
	cam_debug("%s huawei,sensor_index %d, rc %d\n", __func__,
		sensor_info->sensor_index, rc);
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

	if (hw_is_fpga_board())
		return rc;

	rc = of_property_read_u32(of_node, "huawei,mclk",
		&sensor_info->mclk);
	cam_debug("%s huawei,mclk 0x%x, rc %d\n", __func__,
		sensor_info->mclk, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		goto fail;
	}

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

	cam_debug("gpio num = %d", sensor_info->gpio_num);
	for(i = 0; i < sensor_info->gpio_num; i++) {
		rc = of_property_read_string_index(of_node, "huawei,gpio-ctrl-types",
			i, (const char **)&gpio_tag);
		if(rc < 0) {
			cam_err("%s failed %d", __func__, __LINE__);
			goto fail;
		}
		for(index = 0; index < IO_MAX; index++) {
			if (gpio_ctrl_types[index]) {
				if(!strcmp(gpio_ctrl_types[index], gpio_tag))
					sensor_info->gpios[index].gpio = of_get_gpio(of_node, i);
			}
		}
		cam_debug("gpio ctrl types: %s", gpio_tag);
	}

    //add csi_index and i2c_index for dual camera.
    count = of_property_count_elems_of_size(of_node, "huawei,csi_index",
        sizeof(u32));
    if (count > 0) {
        ret = of_property_read_u32_array(of_node, "huawei,csi_index",
            &sensor_info->csi_id, count);
    } else {
        sensor_info->csi_id[0] = sensor_info->sensor_index;
        sensor_info->csi_id[1] = -1;
    }
    cam_info("sensor:%s csi_id[0-1]=%d:%d", sensor_info->name,
		sensor_info->csi_id[0], sensor_info->csi_id[1]);

    count = of_property_count_elems_of_size(of_node, "huawei,i2c_index",
        sizeof(u32));
    if (count > 0) {
        ret = of_property_read_u32_array(of_node, "huawei,i2c_index",
           &sensor_info->i2c_id, count);
    } else {
        sensor_info->i2c_id[0] = sensor_info->sensor_index;
        sensor_info->i2c_id[1] = -1;
    }
    cam_info("sensor:%s i2c_id[0-1]=%d:%d", sensor_info->name,
			sensor_info->i2c_id[0], sensor_info->i2c_id[1]);

    rc = of_property_read_u32(of_node, "module_type", &sensor_info->module_type);
    cam_info("%s module_type 0x%x, rc %d\n", __func__, sensor_info->module_type, rc);
    if (rc < 0) {
        sensor_info->module_type = 0;
        cam_warn("%s read module_type failed, rc %d, set default value %d\n",
        __func__, rc, sensor_info->module_type);
        rc = 0;
    }

	return rc;
fail:
	cam_err("%s error exit.\n", __func__);
	kfree(sensor_info);
	sensor_info = NULL;
	sensor->board_info = NULL;
	return rc;
}

void hw_camdrv_msleep(unsigned int ms)
{
	ktime_t wait = ns_to_ktime((u64)ms * 1000 * 1000);
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule_hrtimeout(&wait, HRTIMER_MODE_REL);
}
EXPORT_SYMBOL(hw_camdrv_msleep);

int hw_is_fpga_board(void)
{
	cam_debug("%s is_fpga=%d.", __func__, is_fpga);
	return is_fpga;
}
EXPORT_SYMBOL(hw_is_fpga_board);

