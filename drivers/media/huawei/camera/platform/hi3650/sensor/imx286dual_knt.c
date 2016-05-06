


#include <linux/module.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/rpmsg.h>

#include "hwsensor.h"
#include "sensor_commom.h"
#include "hw_csi.h"
#include "../pmic/hw_pmic.h"

#define I2S(i) container_of(i, sensor_t, intf)
#define CTL_RESET_HOLD    (0)
#define CTL_RESET_RELEASE (1)

static bool s_imx286dual_power_on = false;

static struct sensor_power_setting imx286dual_power_setting[] = {

    //Misp DCDC-EN  0.9V  [GPIO]
    {
		.seq_type = SENSOR_MISPDCDC_EN,
		.data = (void*)"misp-dcdc-en",
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//Misp VDD Core  0.92V  [CAM_PMIC_BUCK1]
	{
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_BUCK_1,
		.config_val = 930000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//Misp + M0 + M1  IOVDD  1.8V  [CAM_PMIC_LDO4]
	{
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_LDO_4,
		.config_val = LDO_VOLTAGE_1P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//M0 VCM  3V  [LDO25]
    {
		.seq_type = SENSOR_VCM_AVDD,
		.config_val = 3000000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
    },

	//M1 VCM  3V  [LDO13]
	{
		.seq_type = SENSOR_VCM_AVDD2,
		.config_val = 3000000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//M0 AVDD0  2.85V  [CAM_PMIC_LDO1]
    {
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_LDO_1,
		.config_val = 2800000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
    },

	//M1 AVDD1  2.85V  [CAM_PMIC_LDO2]
	{
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_LDO_2,
		.config_val = 2800000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//M0 DVDD0  1.1V  [LDO20]
    {
        .seq_type = SENSOR_DVDD,
		.data = (void*)"main-sensor-dvdd0",
        .config_val = LDO_VOLTAGE_V1P1V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

	//M1 DVDD1  1.1V  [LDO32]
	{
		.seq_type = SENSOR_DVDD2,
		.data = (void*)"main-sensor-dvdd1",
		.config_val = LDO_VOLTAGE_V1P1V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = 0,
		.delay = 1,
	},

	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = 1,
		.delay = 1,
	},

    //M0 RESET  [GPIO_018]
    {
        .seq_type = SENSOR_RST,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

	//M1 RESET  [GPIO_134]
	{
        .seq_type = SENSOR_RST2,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

};

static struct sensor_power_setting imx286legacydual_power_setting[] = {

	//Misp VDD Core  1.1V  [CAM_PMIC_BUCK1]
	{
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_BUCK_1,
		.config_val = PMIC_1P1V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

    //Misp DCDC-EN  0.9V  [GPIO]
    {
		.seq_type = SENSOR_MISPDCDC_EN,
		.data = (void*)"misp-dcdc-en",
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//Misp + M0 + M1  IOVDD  1.8V  [CAM_PMIC_LDO4]
	{
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_LDO_4,
		.config_val = LDO_VOLTAGE_1P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//M0 VCM  3V  [LDO25]
    {
		.seq_type = SENSOR_VCM_AVDD,
		.config_val = 3000000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
    },

	//M1 VCM  3V  [LDO13]
	{
		.seq_type = SENSOR_VCM_AVDD2,
		.config_val = 3000000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//M0 AVDD0  2.85V  [CAM_PMIC_LDO1]
    {
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_LDO_1,
		.config_val = 2800000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
    },

	//M1 AVDD1  2.85V  [CAM_PMIC_LDO2]
	{
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_LDO_2,
		.config_val = 2800000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//M0 DVDD0  1.1V  [LDO20]
    {
        .seq_type = SENSOR_DVDD,
		.data = (void*)"main-sensor-dvdd0",
        .config_val = LDO_VOLTAGE_V1P1V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

	//M1 DVDD1  1.1V  [LDO32]
	{
		.seq_type = SENSOR_DVDD2,
		.data = (void*)"main-sensor-dvdd1",
		.config_val = LDO_VOLTAGE_V1P1V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = 0,
		.delay = 1,
	},

	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = 1,
		.delay = 1,
	},

    //M0 RESET  [GPIO_018]
    {
        .seq_type = SENSOR_RST,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

	//M1 RESET  [GPIO_134]
	{
        .seq_type = SENSOR_RST2,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

};

/* For FRD oversea boards */
static struct sensor_power_setting imx286dOversea_power_setting[] = {

    //Misp DCDC-EN  0.9V  [GPIO]
    {
		.seq_type = SENSOR_MISPDCDC_EN,
		.data = (void*)"misp-dcdc-en",
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//Misp VDD Core  0.92V	[CAM_PMIC_BUCK1]
	{
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_BUCK_1,
		.config_val = 930000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//Misp + M0 + M1  IOVDD  1.8V  [CAM_PMIC_LDO4]
	{
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_LDO_4,
		.config_val = LDO_VOLTAGE_1P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//M0 VCM  3V  [LDO25]
    {
		.seq_type = SENSOR_VCM_AVDD,
		.config_val = 3000000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
    },

	//M1 VCM  3V  [LDO13]
	{
		.seq_type = SENSOR_VCM_AVDD2,
		.config_val = 3000000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//M0 AVDD0  2.85V  [CAM_PMIC_LDO1]
    {
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_LDO_1,
		.config_val = 2800000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
    },

	//M1 AVDD1  2.85V  [CAM_PMIC_LDO2]
	{
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_LDO_2,
		.config_val = 2800000,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//M0 DVDD + M1 DVDD  1.1V  [CAM_PMIC_BUCK2]
    {
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_BUCK_2,
		.config_val = PMIC_1P1V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
    },

	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = 0,
		.delay = 1,
	},

	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = 1,
		.delay = 1,
	},

    //M0 RESET  [GPIO_018]
    {
        .seq_type = SENSOR_RST,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

	//M1 RESET  [GPIO_134]
	{
        .seq_type = SENSOR_RST2,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

};

static char const*
imx286dual_get_name(
        hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

static int
imx286dual_power_up(
        hwsensor_intf_t* si)
{
    int ret = 0;
    sensor_t* sensor = NULL;
    sensor = I2S(si);
	cam_info("enter %s. index = %d name = %s", __func__, sensor->board_info->sensor_index, sensor->board_info->name);
	if (hw_is_fpga_board()) {
		ret = do_sensor_power_on(sensor->board_info->sensor_index, sensor->board_info->name);
	} else {
		ret = hw_sensor_power_up(sensor);
	}
    if (0 == ret )
    {
        cam_info("%s. power up sensor success.", __func__);
    }
    else
    {
        cam_err("%s. power up sensor fail.", __func__);
    }
    return ret;
}

static int
imx286dual_power_down(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	cam_info("enter %s. index = %d name = %s", __func__, sensor->board_info->sensor_index, sensor->board_info->name);
	if (hw_is_fpga_board()) {
		ret = do_sensor_power_off(sensor->board_info->sensor_index, sensor->board_info->name);
	} else {
		ret = hw_sensor_power_down(sensor);
	}
    if (0 == ret )
    {
        cam_info("%s. power down sensor success.", __func__);
    }
    else
    {
        cam_err("%s. power down sensor fail.", __func__);
    }
	return ret;
}

static int imx286dual_csi_enable(hwsensor_intf_t* si)
{
    return 0;
}

static int imx286dual_csi_disable(hwsensor_intf_t* si)
{
    return 0;
}

static int
imx286dual_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;

    cam_info("%s name:%s", __func__, sensor->board_info->name);

    strncpy(cdata->cfg.name, sensor->board_info->name, DEVICE_NAME_SIZE-1);
    cdata->data = sensor->board_info->sensor_index;

    return 0;
}

static int imx286dual_do_hw_reset(hwsensor_intf_t* si, int ctl, int id)
{
    char *state = NULL;
    sensor_t* sensor = I2S(si);
    hwsensor_board_info_t *b_info = NULL;
    int ret = 0;

    b_info = sensor->board_info;
    if (NULL == b_info) {
        cam_warn("%s invalid sensor board info", __func__);
        return 0;
    }

    ret  = gpio_request(b_info->gpios[RESETB].gpio, "imx286reset-0");
    ret |= gpio_request(b_info->gpios[RESETB2].gpio, "imx286reset-1");
    if (ret) {
        cam_err("%s requeset reset pin failed", __func__);
        return ret;
    }

    if (ctl == CTL_RESET_HOLD) {
        state = "hold";
        ret  = gpio_direction_output(b_info->gpios[RESETB].gpio, 0);
        ret |= gpio_direction_output(b_info->gpios[RESETB2].gpio, 0);
    } else {
        state = "release";
        ret  = gpio_direction_output(b_info->gpios[RESETB].gpio, 1);
        ret |= gpio_direction_output(b_info->gpios[RESETB2].gpio, 1);
        udelay(2000);
    }
    gpio_free(b_info->gpios[RESETB].gpio);
    gpio_free(b_info->gpios[RESETB2].gpio);

    if (ret) {
        cam_err("%s set reset pin failed", __func__);
    } else {
        cam_info("%s: set reset state=%s", __func__, state);
    }
    return ret;
}

static int
imx286dual_config(
        hwsensor_intf_t* si,
        void  *argp)
{
	struct sensor_cfg_data *data;

	int ret =0;
	data = (struct sensor_cfg_data *)argp;
	cam_debug("imx286dual cfgtype = %d",data->cfgtype);
	switch(data->cfgtype){
		case SEN_CONFIG_POWER_ON:
			if (!s_imx286dual_power_on) {
				ret = si->vtbl->power_up(si);
				s_imx286dual_power_on = true;
			}
			break;
		case SEN_CONFIG_POWER_OFF:
			if (s_imx286dual_power_on) {
				ret = si->vtbl->power_down(si);
				s_imx286dual_power_on = false;
			}
			break;
		case SEN_CONFIG_WRITE_REG:
			break;
		case SEN_CONFIG_READ_REG:
			break;
		case SEN_CONFIG_WRITE_REG_SETTINGS:
			break;
		case SEN_CONFIG_READ_REG_SETTINGS:
			break;
		case SEN_CONFIG_ENABLE_CSI:
			break;
		case SEN_CONFIG_DISABLE_CSI:
			break;
		case SEN_CONFIG_MATCH_ID:
			ret = si->vtbl->match_id(si,argp);
			break;
		case SEN_CONFIG_RESET_HOLD:
			ret = imx286dual_do_hw_reset(si, CTL_RESET_HOLD, data->mode);
			break;
		case SEN_CONFIG_RESET_RELEASE:
			ret = imx286dual_do_hw_reset(si, CTL_RESET_RELEASE, data->mode);
			break;
		default:
			cam_err("%s cfgtype(%d) is error", __func__, data->cfgtype);
			break;
	}
	return ret;
}

static hwsensor_vtbl_t s_imx286dual_vtbl =
{
    .get_name = imx286dual_get_name,
    .config = imx286dual_config,
    .power_up = imx286dual_power_up,
    .power_down = imx286dual_power_down,
    .match_id = imx286dual_match_id,
    .csi_enable = imx286dual_csi_enable,
    .csi_disable = imx286dual_csi_disable,
};
/* individual driver data for each device */
static sensor_t s_imx286dual =
{
    .intf = { .vtbl = &s_imx286dual_vtbl, },//common intf
    .power_setting_array = {
        .size = ARRAY_SIZE(imx286dual_power_setting),
        .power_setting = imx286dual_power_setting,
     },
};

static sensor_t s_imx286legacydual =
{
    .intf = { .vtbl = &s_imx286dual_vtbl, },//common intf
    .power_setting_array = {
        .size = ARRAY_SIZE(imx286legacydual_power_setting),
        .power_setting = imx286legacydual_power_setting,
    },
};

static sensor_t s_imx286dOversea =
{
    .intf = { .vtbl = &s_imx286dual_vtbl, },//common intf
    .power_setting_array = {
        .size = ARRAY_SIZE(imx286dOversea_power_setting),
        .power_setting = imx286dOversea_power_setting,
    },
};

/* support both imx286dual & imx286legacydual */
static const struct of_device_id
s_imx286dual_dt_match[] =
{
    {
        .compatible = "huawei,imx286d_knt",
        .data = &s_imx286dual.intf,
    },
    {
        .compatible = "huawei,imx286legacydual_knt",
        .data = &s_imx286legacydual.intf,
    },
	{
		.compatible = "huawei,imx286dOversea_knt",
		.data = &s_imx286dOversea.intf,
	},
    { } /* terminate list */
};
MODULE_DEVICE_TABLE(of, s_imx286dual_dt_match);
/* platform driver struct */
static int32_t imx286dual_platform_probe(struct platform_device* pdev);
static int32_t imx286dual_platform_remove(struct platform_device* pdev);
static struct platform_driver
s_imx286dual_driver =
{
    .probe = imx286dual_platform_probe,
    .remove = imx286dual_platform_remove,
    .driver =
    {
        .name = "huawei,imx286d_knt",
        .owner = THIS_MODULE,
        .of_match_table = s_imx286dual_dt_match,
    },
};


static int32_t
imx286dual_platform_probe(
        struct platform_device* pdev)
{
    int rc = 0;
    struct device_node *np = pdev->dev.of_node;
    const struct of_device_id *id;
    hwsensor_intf_t *intf;
    sensor_t *sensor;

    cam_info("enter %s",__func__);

    if (!np) {
        cam_err("%s of_node is NULL", __func__);
        return -ENODEV;
    }

    id = of_match_node(s_imx286dual_dt_match, np);
    if (!id) {
        cam_err("%s none id matched", __func__);
        return -ENODEV;
    }

    intf = (hwsensor_intf_t*)id->data;
    sensor = I2S(intf);
    rc = hw_sensor_get_dt_data(pdev, sensor);
    if (rc < 0) {
        cam_err("%s no dt data", __func__);
        return -ENODEV;
    }
    sensor->dev = &pdev->dev;

    rc = hwsensor_register(pdev, intf);
    rc = rpmsg_sensor_register(pdev, (void*)sensor);

    return rc;
}

static int32_t
imx286dual_platform_remove(
    struct platform_device * pdev)
{
    struct device_node *np = pdev->dev.of_node;
    const struct of_device_id *id;
    hwsensor_intf_t *intf;
    sensor_t *sensor;

    cam_info("enter %s",__func__);

    if (!np) {
        cam_info("%s of_node is NULL", __func__);
        return 0;
    }
    /* don't use dev->p->driver_data
     * we need to search again */
    id = of_match_node(s_imx286dual_dt_match, np);
    if (!id) {
        cam_info("%s none id matched", __func__);
        return 0;
    }

    intf = (hwsensor_intf_t*)id->data;
    sensor = I2S(intf);

    rpmsg_sensor_unregister((void*)&sensor);
    hwsensor_unregister(intf);
    return 0;
}
static int __init
imx286dual_init_module(void)
{
    cam_notice("enter %s",__func__);
    return platform_driver_probe(&s_imx286dual_driver,
            imx286dual_platform_probe);
}

static void __exit
imx286dual_exit_module(void)
{
    platform_driver_unregister(&s_imx286dual_driver);
}

module_init(imx286dual_init_module);
module_exit(imx286dual_exit_module);
MODULE_DESCRIPTION("imx286dual");
MODULE_LICENSE("GPL v2");
