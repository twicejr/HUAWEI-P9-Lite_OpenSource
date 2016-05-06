

#include <linux/module.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

#include "hwsensor.h"
#include "sensor_commom.h"
#include "hw_csi.h"

#define I2S(i) container_of(i, sensor_t, intf)

//add s5k4e1ga_sunny
extern struct hw_csi_pad hw_csi_pad;
static hwsensor_vtbl_t s_s5k4e1ga_sunny_vtbl;

int s5k4e1ga_sunny_config(hwsensor_intf_t* si, void  *argp);

static bool is_poweron = false;

struct sensor_power_setting s5k4e1ga_sunny_power_setting[] = {
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
        .seq_type = SENSOR_RST2,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MINIISP IOVDD 1.8V
    {
		.seq_type = SENSOR_MINIISP_VPP,
		.config_val = LDO_VOLTAGE_1P8V,
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


	//SCAM IOVDD 1.8V
//	{
//		.seq_type = SENSOR_IOVDD,
//		.data = (void*)"common-iovdd",
//		.config_val = LDO_VOLTAGE_1P8V,
//		.sensor_index = SENSOR_INDEX_INVALID,
//		.delay = 1,
//	},

	//SCAM AVDD 2.85V
	{
		.seq_type = SENSOR_AVDD,
		.data = (void*)"main-sensor-avdd",
		.config_val = LDO_VOLTAGE_V2P85V,
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
};

static sensor_t s_s5k4e1ga_sunny =
{
    .intf = { .vtbl = &s_s5k4e1ga_sunny_vtbl, },
    .power_setting_array = {
            .size = ARRAY_SIZE(s5k4e1ga_sunny_power_setting),
            .power_setting = s5k4e1ga_sunny_power_setting,
     },
};

static const struct of_device_id
s_s5k4e1ga_sunny_dt_match[] =
{
	{
        .compatible = "huawei,s5k4e1ga_sunny",
        .data = &s_s5k4e1ga_sunny.intf,
    },
	{
    },
};

MODULE_DEVICE_TABLE(of, s_s5k4e1ga_sunny_dt_match);

static struct platform_driver
s_s5k4e1ga_sunny_driver =
{
	.driver =
    {
		.name = "huawei,s5k4e1ga_sunny",
		.owner = THIS_MODULE,
		.of_match_table = s_s5k4e1ga_sunny_dt_match,
	},
};

char const*
s5k4e1ga_sunny_get_name(
        hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

int
s5k4e1ga_sunny_power_up(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	if(!is_poweron) {
		ret = hw_sensor_power_up(sensor);
		cam_notice("+++s5k4e1ga_sunny power on!+++");
		is_poweron = true;
	} else {
		cam_notice("+++not power on+++");
	}
	return ret;
}

int
s5k4e1ga_sunny_power_down(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	if(is_poweron) {
		ret = hw_sensor_power_down(sensor);
		cam_notice("---s5k4e1ga_sunny power off!---");
		is_poweron = false;
	} else {
		cam_notice("---not power off---");
	}
	return ret;
}

int s5k4e1ga_sunny_csi_enable(hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);

	ret = hw_csi_pad.hw_csi_enable(sensor->board_info->csi_index, sensor->board_info->csi_lane, sensor->board_info->csi_mipi_clk);
	return ret;
}

int s5k4e1ga_sunny_csi_disable(hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_csi_pad.hw_csi_disable(sensor->board_info->csi_index);
	return ret;
}

static int
s5k4e1ga_sunny_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
    uint16_t sensor_id = 0;
    uint8_t modue_id = 0;

    cam_info("%s TODO.", __func__);

    misp_get_module_info(sensor->board_info->sensor_index,&sensor_id,&modue_id);

    if(sensor_id == 0xf541) {
        cdata->data = sensor->board_info->sensor_index;
        hwsensor_writefile(sensor->board_info->sensor_index,
                           sensor->board_info->name);
    } else {
        cdata->data = SENSOR_INDEX_INVALID;
    }

    cam_info("%s TODO.  cdata->data=%d", __func__, cdata->data);

    return 0;
}

static hwsensor_vtbl_t
s_s5k4e1ga_sunny_vtbl =
{
	.get_name = s5k4e1ga_sunny_get_name,
	.config = s5k4e1ga_sunny_config,
	.power_up = s5k4e1ga_sunny_power_up,
	.power_down = s5k4e1ga_sunny_power_down,
	.match_id = s5k4e1ga_sunny_match_id,
	.csi_enable = s5k4e1ga_sunny_csi_enable,
	.csi_disable = s5k4e1ga_sunny_csi_disable,
	.match_id = s5k4e1ga_sunny_match_id,
};

int
s5k4e1ga_sunny_config(
        hwsensor_intf_t* si,
        void  *argp)
{
	struct sensor_cfg_data *data;

	int ret =0;
	data = (struct sensor_cfg_data *)argp;
	cam_debug("s5k4e1ga_sunny cfgtype = %d",data->cfgtype);
	switch(data->cfgtype){
		case SEN_CONFIG_POWER_ON:
			ret = si->vtbl->power_up(si);
			break;
		case SEN_CONFIG_POWER_OFF:
			ret = si->vtbl->power_down(si);
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
			ret = si->vtbl->csi_enable(si);
			break;
		case SEN_CONFIG_DISABLE_CSI:
			ret = si->vtbl->csi_disable(si);
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
s5k4e1ga_sunny_platform_probe(
        struct platform_device* pdev)
{
	int rc = 0;
	cam_debug("enter %s",__func__);

	if (pdev->dev.of_node) {
		rc = hw_sensor_get_dt_data(pdev, &s_s5k4e1ga_sunny);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			goto s5k4e1ga_sunny_sensor_probe_fail;
		}
	} else {
		cam_err("%s s5k4e1ga_sunny of_node is NULL.\n", __func__);
		goto s5k4e1ga_sunny_sensor_probe_fail;
	}

	rc = hwsensor_register(pdev, &s_s5k4e1ga_sunny.intf);
s5k4e1ga_sunny_sensor_probe_fail:
	return rc;
}

static int __init
s5k4e1ga_sunny_init_module(void)
{
	cam_info("Enter: %s", __func__);
    return platform_driver_probe(&s_s5k4e1ga_sunny_driver,
            s5k4e1ga_sunny_platform_probe);
}

static void __exit
s5k4e1ga_sunny_exit_module(void)
{
    hwsensor_unregister(&s_s5k4e1ga_sunny.intf);
    platform_driver_unregister(&s_s5k4e1ga_sunny_driver);
}

module_init(s5k4e1ga_sunny_init_module);
module_exit(s5k4e1ga_sunny_exit_module);
MODULE_DESCRIPTION("s5k4e1ga_sunny");
MODULE_LICENSE("GPL v2");

