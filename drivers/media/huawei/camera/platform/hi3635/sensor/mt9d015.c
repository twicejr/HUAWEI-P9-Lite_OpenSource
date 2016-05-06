


#include <linux/module.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

#include "hwsensor.h"
#include "sensor_commom.h"
#include "hw_csi.h"

#define I2S(i) container_of(i, sensor_t, intf)

extern struct hw_csi_pad hw_csi_pad;
static hwsensor_vtbl_t s_mt9d015_vtbl;

int mt9d015_config(hwsensor_intf_t* si, void  *argp);

struct sensor_power_setting hw_mt9d015_power_setting[] = {
#if 0
	{
		.seq_type = SENSOR_IOVDD,
		.data = (void*)"common-iovdd",
		.config_val = LDO_VOLTAGE_1P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_AVDD2,
		.data = (void*)"slave-sensor-avdd",
		.config_val = LDO_VOLTAGE_2P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 2,
	},
	{
		.seq_type = SENSOR_PWDN,
		.config_val = SENSOR_GPIO_LOW,
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
		.seq_type = SENSOR_I2C,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 5,
	},
#else

	{
		.seq_type = SENSOR_IOVDD,
		.data = (void*)"common-iovdd",
		.config_val = LDO_VOLTAGE_1P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_AVDD2,
		.data = (void*)"slave-sensor-avdd",
		.config_val = LDO_VOLTAGE_2P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 5,
	},
	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	{
		.seq_type = SENSOR_PWDN,
		.config_val = SENSOR_GPIO_LOW,
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
		.seq_type = SENSOR_I2C,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 20,
	},
	/*
	{
		.seq_type = SENSOR_SUSPEND,
		.config_val = SENSOR_GPIO_HIGH,
		.sensor_index = SENSOR_INDEX_INVALID,
	},
	*/
#endif
};

static sensor_t s_mt9d015 =
{
    .intf = { .vtbl = &s_mt9d015_vtbl, },
    .power_setting_array = {
            .size = ARRAY_SIZE(hw_mt9d015_power_setting),
            .power_setting = hw_mt9d015_power_setting,
     },
};

static const struct of_device_id
s_mt9d015_dt_match[] =
{
	{
        .compatible = "huawei,mt9d015",
        .data = &s_mt9d015.intf,
    },
	{
    },
};

MODULE_DEVICE_TABLE(of, s_mt9d015_dt_match);

static struct platform_driver
s_mt9d015_driver =
{
	.driver =
    {
		.name = "huawei,mt9d015",
		.owner = THIS_MODULE,
		.of_match_table = s_mt9d015_dt_match,
	},
};

char const*
mt9d015_get_name(
        hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

int
mt9d015_power_up(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_sensor_power_up(sensor);
	return ret;
}

int
mt9d015_power_down(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_sensor_power_down(sensor);
	return ret;
}

int mt9d015_csi_enable(hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);

	ret = hw_csi_pad.hw_csi_enable(sensor->board_info->csi_index, sensor->board_info->csi_lane, sensor->board_info->csi_mipi_clk);
	return ret;
}

int mt9d015_csi_disable(hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_csi_pad.hw_csi_disable(sensor->board_info->csi_index);
	return ret;
}

static int mt9d015_i2c_read (hwsensor_intf_t* intf, void * data)
{
	sensor_t* sensor = NULL;
	int ret = 0;

	sensor= I2S(intf);
	ret = hw_sensor_i2c_read(sensor,data);

	return ret;
}

static int
mt9d015_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
    struct sensor_cfg_data cdata_reg;

    cam_info("%s TODO.", __func__);

    cdata_reg.cfg.reg.subaddr = 0x0;
    cdata_reg.cfg.reg.value = 0;

    mt9d015_i2c_read((hwsensor_intf_t*)sensor, &cdata_reg);

    cam_notice( "%s, line %d, sensor id: 0x%x", __func__, __LINE__, cdata_reg.cfg.reg.value);


    if (0x1501 == cdata_reg.cfg.reg.value) {
        cam_info("%s succeed to match id.", __func__);
    } else {
        cam_info("%s failed to match id.", __func__);
        sensor->board_info->sensor_index = CAMERA_SENSOR_INVALID;
    }

    cdata->data = sensor->board_info->sensor_index;
    hwsensor_writefile(sensor->board_info->sensor_index,
    sensor->board_info->name);
    return 0;
}

static int mt9d015_i2c_write (hwsensor_intf_t* intf, void * data)
{
	sensor_t* sensor = NULL;
	int ret = 0;

	sensor= I2S(intf);
	ret = hw_sensor_i2c_write(sensor,data);

	return ret;
}

static int mt9d015_i2c_read_seq (hwsensor_intf_t* intf, void * data)
{
	sensor_t* sensor = NULL;
	int ret = 0;

	sensor= I2S(intf);
	ret = hw_sensor_i2c_read_seq(sensor,data);

	return ret;
}

static int mt9d015_i2c_write_seq (hwsensor_intf_t* intf, void * data)
{
	sensor_t* sensor = NULL;
	int ret = 0;

	sensor= I2S(intf);
	ret = hw_sensor_i2c_write_seq(sensor,data);

	return ret;
}

static hwsensor_vtbl_t
s_mt9d015_vtbl =
{
	.get_name = mt9d015_get_name,
	.config = mt9d015_config,
	.power_up = mt9d015_power_up,
	.power_down = mt9d015_power_down,
	.i2c_read = mt9d015_i2c_read,
	.i2c_write = mt9d015_i2c_write,
	.i2c_read_seq = mt9d015_i2c_read_seq,
	.i2c_write_seq = mt9d015_i2c_write_seq,
	//.ioctl = mt9d015_ioctl,
	.match_id = mt9d015_match_id,
	//.set_expo_gain = mt9d015_set_expo_gain,
	//.apply_expo_gain = mt9d015_apply_expo_gain,
	//.suspend_eg_task = mt9d015_suspend_eg_task,
	//.set_hts = mt9d015_set_hts,
	//.set_vts = mt9d015_set_vts,
	.csi_enable = mt9d015_csi_enable,
	.csi_disable = mt9d015_csi_disable,
};

int
mt9d015_config(
        hwsensor_intf_t* si,
        void  *argp)
{
	struct sensor_cfg_data *data;

	int ret =0;
	static bool mt9d015_power_on = false;
	static bool csi_enable = false;
	data = (struct sensor_cfg_data *)argp;
	cam_debug("mt9d015 cfgtype = %d",data->cfgtype);
	switch(data->cfgtype){
		case SEN_CONFIG_POWER_ON:
			if (!mt9d015_power_on) {
				ret = si->vtbl->power_up(si);
				mt9d015_power_on = true;
			}
			break;
		case SEN_CONFIG_POWER_OFF:
			if (mt9d015_power_on) {
				ret = si->vtbl->power_down(si);
				mt9d015_power_on = false;
			}
			break;
		case SEN_CONFIG_WRITE_REG:
			ret = si->vtbl->i2c_read(si,argp);
			break;
		case SEN_CONFIG_READ_REG:
			ret = si->vtbl->i2c_read(si,argp);
			break;
		case SEN_CONFIG_WRITE_REG_SETTINGS:
			ret = si->vtbl->i2c_write_seq(si,argp);
			break;
		case SEN_CONFIG_READ_REG_SETTINGS:
			ret = si->vtbl->i2c_read_seq(si,argp);
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
			break;
	}
	cam_debug("%s exit",__func__);
	return ret;
}

static int32_t
mt9d015_platform_probe(
        struct platform_device* pdev)
{
	int rc = 0;
	cam_debug("enter %s",__func__);

	if (pdev->dev.of_node) {
		rc = hw_sensor_get_dt_data(pdev, &s_mt9d015);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			goto mt9d015_sensor_probe_fail;
		}
	} else {
		cam_err("%s mt9d015 of_node is NULL.\n", __func__);
		goto mt9d015_sensor_probe_fail;
	}

	rc = hwsensor_register(pdev, &s_mt9d015.intf);
mt9d015_sensor_probe_fail:
	return rc;
}

static int __init
mt9d015_init_module(void)
{
    cam_notice("enter %s",__func__);
    return platform_driver_probe(&s_mt9d015_driver,
            mt9d015_platform_probe);
}

static void __exit
mt9d015_exit_module(void)
{
    cam_notice("enter %s",__func__);
    platform_driver_unregister(&s_mt9d015_driver);
}

module_init(mt9d015_init_module);
module_exit(mt9d015_exit_module);
MODULE_DESCRIPTION("mt9d015");
MODULE_LICENSE("GPL v2");

