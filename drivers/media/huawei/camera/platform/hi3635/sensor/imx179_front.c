


#include <linux/module.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

#include "hwsensor.h"
#include "sensor_commom.h"
#include "hw_csi.h"

#define I2S(i) container_of(i, sensor_t, intf)

#define SENSOR_SCAMIF_GPIO 28

extern struct hw_csi_pad hw_csi_pad;
static hwsensor_vtbl_t s_imx179_front_vtbl;

int imx179_front_config(hwsensor_intf_t* si, void  *argp);

struct sensor_power_setting imx179_front_power_setting[] = {

	//MINIISP CS
	{
		.seq_type = SENSOR_CS,
		.config_val = SENSOR_GPIO_HIGH,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},

	//MINIISP CORE 1.1V
	{
		.seq_type = SENSOR_SUSPEND,
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},

	//MINIISP DVDD 1.1V
	{
		.seq_type = SENSOR_PMIC,
		.seq_val = PMIC_LDO5,
		.config_val = PMIC_1P1V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},

	//MINIISP IOVDD 1.8V
	{
		.seq_type = SENSOR_PMIC,
		.seq_val = PMIC_LDO4,
		.config_val = PMIC_1P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},

	{
		.seq_type = SENSOR_AVDD,
		.data = (void*)"main-sensor-avdd",
		.config_val = LDO_VOLTAGE_V2P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_IOVDD,
		.data = (void*)"common-iovdd",
		.config_val = LDO_VOLTAGE_1P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},

	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_RST,
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},

        {
            .seq_type = SENSOR_PMIC,
            .seq_val = PMIC_BUCK2,
            .config_val = PMIC_1P2V,
            .sensor_index = SENSOR_INDEX_INVALID,
            .delay = 1,
        },
};

static sensor_t s_imx179_front =
{
    .intf = { .vtbl = &s_imx179_front_vtbl, },
    .power_setting_array = {
            .size = ARRAY_SIZE(imx179_front_power_setting),
            .power_setting = imx179_front_power_setting,
     },
};

static const struct of_device_id
s_imx179_front_dt_match[] =
{
	{
        .compatible = "huawei,imx179_front",
        .data = &s_imx179_front.intf,
    },
	{
    },
};

MODULE_DEVICE_TABLE(of, s_imx179_front_dt_match);

static struct platform_driver
s_imx179_front_driver =
{
	.driver =
    {
		.name = "huawei,imx179_front",
		.owner = THIS_MODULE,
		.of_match_table = s_imx179_front_dt_match,
	},
};

char const*
imx179_front_get_name(
        hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

int
imx179_front_power_up(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_sensor_power_up(sensor);
	return ret;
}

int
imx179_front_power_down(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_sensor_power_down(sensor);
	return ret;
}

int imx179_front_csi_enable(hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);

	ret = hw_csi_pad.hw_csi_enable(sensor->board_info->csi_index, sensor->board_info->csi_lane, sensor->board_info->csi_mipi_clk);
	return ret;
}

int imx179_front_csi_disable(hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_csi_pad.hw_csi_disable(sensor->board_info->csi_index);
	return ret;
}

static int
imx179_front_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
    uint32_t gpio_id;
    int ret, value;

    cam_info("%s TODO.", __func__);

/*
    id = read_i2c();
    if (id == chipid) {
        cam_info("%s succeed to match id.", __func__);
    } else {
        cam_info("%s failed to match id.", __func__);
        sensor->board_info->sensor_index = CAMERA_SENSOR_INVALID;
    }
*/
    cdata->data = sensor->board_info->sensor_index;

    hwsensor_writefile(sensor->board_info->sensor_index,
		sensor->board_info->name);

    gpio_id = SENSOR_SCAMIF_GPIO;
    ret = gpio_request(gpio_id, "factory_gpio");
    if (ret < 0) {
        cam_err("%s failed to request sensor factory gpio pin.", __func__);
        gpio_free(gpio_id);
        return ret;
    }
    gpio_direction_input(gpio_id);

    value = gpio_get_value(gpio_id);
    if(value < 0) {
        cam_err("%s failed to get sensor factory gpio value.", __func__);
        gpio_free(gpio_id);
        return value;
    }
    else {
        cdata->mode = value;
    }

    memset(cdata->cfg.name, 0, sizeof(cdata->cfg.name));
    snprintf(cdata->cfg.name, sizeof(cdata->cfg.name)-1,  "imx179_front_%s",  ((value == 0) ? "sunny":"liteon"));
    cam_debug("renew imx179 module name = %s.", cdata->cfg.name);
    gpio_free(gpio_id);

    return 0;
}

static hwsensor_vtbl_t
s_imx179_front_vtbl =
{
	.get_name = imx179_front_get_name,
	.config = imx179_front_config,
	.power_up = imx179_front_power_up,
	.power_down = imx179_front_power_down,
	.match_id = imx179_front_match_id,
	.csi_enable = imx179_front_csi_enable,
	.csi_disable = imx179_front_csi_disable,
	.match_id = imx179_front_match_id,
};

int
imx179_front_config(
        hwsensor_intf_t* si,
        void  *argp)
{
	struct sensor_cfg_data *data;

	int ret =0;
	static bool imx179f_power_on = false;
	static bool csi_enable = false;
	data = (struct sensor_cfg_data *)argp;
	cam_debug("imx179_front cfgtype = %d",data->cfgtype);
	switch(data->cfgtype){
		case SEN_CONFIG_POWER_ON:
			if (!imx179f_power_on) {
				ret = si->vtbl->power_up(si);
				imx179f_power_on = true;
			}
			break;
		case SEN_CONFIG_POWER_OFF:
			if (imx179f_power_on) {
				ret = si->vtbl->power_down(si);
				imx179f_power_on = false;
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
			if(!csi_enable)
			{
				ret = si->vtbl->csi_enable(si);
				csi_enable = true;
			}
			break;
		case SEN_CONFIG_DISABLE_CSI:
			if(csi_enable)
			{
				ret = si->vtbl->csi_disable(si);
				csi_enable = false;
			}
			break;
		case SEN_CONFIG_MATCH_ID:
			ret = si->vtbl->match_id(si,argp);
			break;
		default:
                cam_err("%s cfgtype(%d) is error", __func__, data->cfgtype);
			break;
	}
	cam_debug("%s exit",__func__);
	return ret;
}

static int32_t
imx179_front_platform_probe(
        struct platform_device* pdev)
{
	int rc = 0;
	cam_debug("enter %s",__func__);

	if (pdev->dev.of_node) {
		rc = hw_sensor_get_dt_data(pdev, &s_imx179_front);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			goto imx179_front_sensor_probe_fail;
		}
	} else {
		cam_err("%s imx179_front of_node is NULL.\n", __func__);
		goto imx179_front_sensor_probe_fail;
	}

	rc = hwsensor_register(pdev, &s_imx179_front.intf);
imx179_front_sensor_probe_fail:
	return rc;
}

static int __init
imx179_front_init_module(void)
{
    return platform_driver_probe(&s_imx179_front_driver,
            imx179_front_platform_probe);
}

static void __exit
imx179_front_exit_module(void)
{
    platform_driver_unregister(&s_imx179_front_driver);
}

module_init(imx179_front_init_module);
module_exit(imx179_front_exit_module);
MODULE_DESCRIPTION("imx179_front");
MODULE_LICENSE("GPL v2");

