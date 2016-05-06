 

#include <linux/module.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/rpmsg.h>

#include "hwsensor.h"
#include "sensor_commom.h"
#include "hw_csi.h"

#define I2S(i) container_of(i, sensor_t, intf)

static hwsensor_vtbl_t s_ov8856_vtbl;

enum rear_sensor_dvdd_type_t{
	DVDD105V=0,//1.05V
	DVDD120V=1,//1.20V
};

int ov8856_config(hwsensor_intf_t* si, void  *argp);

struct sensor_power_setting ov8856_power_setting[] = {
    //disable main camera reset
    {
        .seq_type = SENSOR_SUSPEND,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    {
        .seq_type = SENSOR_MCLK,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 IOVDD 1.80V
    {
        .seq_type = SENSOR_IOVDD,
        .data = (void*)"main-sensor-iovdd",
        .config_val = LDO_VOLTAGE_1P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
    //MCAM1 AVDD 2.80V
    {
        .seq_type = SENSOR_AVDD2,
        .data = (void*)"main-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //MCAM1 DVDD 1.05V
    {
        .seq_type = SENSOR_DVDD2,
        .config_val = LDO_VOLTAGE_1P05V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //SCAM AVDD 2.80V
    {
        .seq_type = SENSOR_AVDD,
        .data = (void*)"slave-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //SCAM DVDD 1.2V
    {
        .seq_type = SENSOR_DVDD,
        .config_val = LDO_VOLTAGE_1P2V,
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

struct sensor_power_setting ov8856_power_setting_dvdd120[] = {
    //disable main camera reset
    {
        .seq_type = SENSOR_SUSPEND,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    {
        .seq_type = SENSOR_MCLK,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 IOVDD 1.80V
    {
        .seq_type = SENSOR_IOVDD,
        .data = (void*)"main-sensor-iovdd",
        .config_val = LDO_VOLTAGE_1P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
    //MCAM1 AVDD 2.80V
    {
        .seq_type = SENSOR_AVDD2,
        .data = (void*)"main-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //MCAM1 DVDD 1.2V
    {
        .seq_type = SENSOR_DVDD2,
        .config_val =  LDO_VOLTAGE_1P2V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //SCAM AVDD 2.80V
    {
        .seq_type = SENSOR_AVDD,
        .data = (void*)"slave-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //SCAM DVDD 1.2V
    {
        .seq_type = SENSOR_DVDD,
        .config_val = LDO_VOLTAGE_1P2V,
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

static sensor_t s_ov8856 =
{
    .intf = { .vtbl = &s_ov8856_vtbl, },
    .power_setting_array = {
            .size = ARRAY_SIZE(ov8856_power_setting),
            .power_setting = ov8856_power_setting,
     },
};

static const struct of_device_id s_ov8856_dt_match[] =
{
    {
        .compatible = "huawei,ov8856",
        .data = &s_ov8856.intf,
    },
    {
    },
};

MODULE_DEVICE_TABLE(of, s_ov8856_dt_match);

static struct platform_driver s_ov8856_driver =
{
    .driver =
    {
        .name = "huawei,ov8856",
        .owner = THIS_MODULE,
        .of_match_table = s_ov8856_dt_match,
    },
};

char const* ov8856_get_name(hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

int ov8856_power_up(hwsensor_intf_t* si)
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

int
ov8856_power_down(
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

int ov8856_csi_enable(hwsensor_intf_t* si)
{
    return 0;
}

int ov8856_csi_disable(hwsensor_intf_t* si)
{
    return 0;
}

static int ov8856_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;

    cam_info("%s enter.", __func__);

    cdata->data = sensor->board_info->sensor_index;

    hwsensor_writefile(sensor->board_info->sensor_index, sensor->board_info->name);
    return 0;
}

static hwsensor_vtbl_t s_ov8856_vtbl =
{
    .get_name = ov8856_get_name,
    .config = ov8856_config,
    .power_up = ov8856_power_up,
    .power_down = ov8856_power_down,
    .match_id = ov8856_match_id,
    .csi_enable = ov8856_csi_enable,
    .csi_disable = ov8856_csi_disable,
    .match_id = ov8856_match_id,
};

int ov8856_config(hwsensor_intf_t* si, void  *argp)
{
    struct sensor_cfg_data *data;

    int ret =0;

	if (NULL == si || NULL == argp){
		cam_err("%s : si or argp is null", __func__);
		return -1;
	}

    data = (struct sensor_cfg_data *)argp;
    cam_debug("ov8856 cfgtype = %d",data->cfgtype);
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
            //ret = si->vtbl->csi_enable(si);
            break;
        case SEN_CONFIG_DISABLE_CSI:
            //ret = si->vtbl->csi_disable(si);
            break;
        case SEN_CONFIG_MATCH_ID:
            ret = si->vtbl->match_id(si,argp);
            break;
        default:
            cam_err("%s cfgtype(%d) is error", __func__, data->cfgtype);
            break;
    }

    return ret;
}

static int32_t ov8856_platform_probe(struct platform_device* pdev)
{
    int rc = 0;
    cam_notice("enter %s",__func__);

    if (pdev->dev.of_node) {
        rc = hw_sensor_get_dt_data(pdev, &s_ov8856);
        if (rc < 0) {
            cam_err("%s failed line %d\n", __func__, __LINE__);
            goto ov8856_sensor_probe_fail;
        }

		/*CASE 1.2v dvdd, revew;CASE 1.05v use default; Other cases need add*/
		if(DVDD120V == s_ov8856.board_info->ldo_diverse){
			cam_info("%s change to relative power setting line %d\n", __func__, __LINE__);
			s_ov8856.power_setting_array.size = ARRAY_SIZE(ov8856_power_setting_dvdd120);
			s_ov8856.power_setting_array.power_setting = ov8856_power_setting_dvdd120;
		}
    } else {
        cam_err("%s ov8856 of_node is NULL.\n", __func__);
        goto ov8856_sensor_probe_fail;
    }
    s_ov8856.dev = &pdev->dev;
    rc = hwsensor_register(pdev, &s_ov8856.intf);
    rc = rpmsg_sensor_register(pdev, (void*)&s_ov8856);
ov8856_sensor_probe_fail:
    return rc;
}

static int __init ov8856_init_module(void)
{
    cam_info("Enter: %s", __func__);
    return platform_driver_probe(&s_ov8856_driver,
            ov8856_platform_probe);
}

static void __exit ov8856_exit_module(void)
{
    hwsensor_unregister(&s_ov8856.intf);
    platform_driver_unregister(&s_ov8856_driver);
}

module_init(ov8856_init_module);
module_exit(ov8856_exit_module);
MODULE_DESCRIPTION("ov8856");
MODULE_LICENSE("GPL v2");

