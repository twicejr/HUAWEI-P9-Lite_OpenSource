


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
static hwsensor_vtbl_t s_ov2680_vtbl;

int ov2680_config(hwsensor_intf_t* si, void  *argp);

struct sensor_power_setting hw_ov2680_power_setting[] = {
#if 0
	{
		.seq_type = SENSOR_AVDD,
		.data = (void*)"main-sensor-avdd",
		.config_val = LDO_VOLTAGE_2P8V,
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
		.seq_type = SENSOR_DVDD,
		.config_val = LDO_VOLTAGE_1P05V,
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
		.delay = 1,
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

static sensor_t s_ov2680 =
{
    .intf = { .vtbl = &s_ov2680_vtbl, },
    .power_setting_array = {
            .size = ARRAY_SIZE(hw_ov2680_power_setting),
            .power_setting = hw_ov2680_power_setting,
     },
};

static const struct of_device_id
s_ov2680_dt_match[] =
{
	{
        .compatible = "huawei,ov2680",
        .data = &s_ov2680.intf,
    },
	{
    },
};

MODULE_DEVICE_TABLE(of, s_ov2680_dt_match);

static struct platform_driver
s_ov2680_driver =
{
	.driver =
    {
		.name = "huawei,ov2680",
		.owner = THIS_MODULE,
		.of_match_table = s_ov2680_dt_match,
	},
};

char const*
ov2680_get_name(
        hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

int
ov2680_power_up(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_sensor_power_up(sensor);
	return ret;
}

int
ov2680_power_down(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_sensor_power_down(sensor);
	return ret;
}

int ov2680_csi_enable(hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);

	ret = hw_csi_pad.hw_csi_enable(sensor->board_info->csi_index, sensor->board_info->csi_lane, sensor->board_info->csi_mipi_clk);
	return ret;
}

int ov2680_csi_disable(hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_csi_pad.hw_csi_disable(sensor->board_info->csi_index);
	return ret;
}

static int ov2680_i2c_read (hwsensor_intf_t* intf, void * data)
{
	sensor_t* sensor = NULL;
	int ret = 0;

	sensor= I2S(intf);
	ret = hw_sensor_i2c_read(sensor,data);

	return ret;
}

static int
ov2680_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
	struct sensor_cfg_data cdata_h;
	struct sensor_cfg_data cdata_l;
	u16 sensor_id = 0;

       cam_info("%s TODO.", __func__);
    
	cdata_h.cfg.reg.subaddr = 0x300A;
	cdata_h.cfg.reg.value = 0;

	cdata_l.cfg.reg.subaddr = 0x300B;
	cdata_l.cfg.reg.value = 0;

	ov2680_i2c_read((hwsensor_intf_t*)sensor, &cdata_h);
	ov2680_i2c_read((hwsensor_intf_t*)sensor, &cdata_l);

	sensor_id = (cdata_h.cfg.reg.value) << 8 | (cdata_l.cfg.reg.value);

	cam_notice( "%s, line %d, sensor id: 0x%x", __func__, __LINE__, sensor_id);


    if (0x2680 == sensor_id) {
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

static int ov2680_i2c_write (hwsensor_intf_t* intf, void * data)
{
	sensor_t* sensor = NULL;
	int ret = 0;

	sensor= I2S(intf);
	ret = hw_sensor_i2c_write(sensor,data);

	return ret;
}

static int ov2680_i2c_read_seq (hwsensor_intf_t* intf, void * data)
{
	sensor_t* sensor = NULL;
	int ret = 0;

	sensor= I2S(intf);
	ret = hw_sensor_i2c_read_seq(sensor,data);

	return ret;
}

static int ov2680_i2c_write_seq (hwsensor_intf_t* intf, void * data)
{
	sensor_t* sensor = NULL;
	int ret = 0;

	sensor= I2S(intf);
	ret = hw_sensor_i2c_write_seq(sensor,data);

	return ret;
}

static hwsensor_vtbl_t
s_ov2680_vtbl =
{
	.get_name = ov2680_get_name,
	.config = ov2680_config,
	.power_up = ov2680_power_up,
	.power_down = ov2680_power_down,
	.i2c_read = ov2680_i2c_read,
	.i2c_write = ov2680_i2c_write,
	.i2c_read_seq = ov2680_i2c_read_seq,
	.i2c_write_seq = ov2680_i2c_write_seq,
	//.ioctl = ov2680_ioctl,
	.match_id = ov2680_match_id,
	//.set_expo_gain = ov2680_set_expo_gain,
	//.apply_expo_gain = ov2680_apply_expo_gain,
	//.suspend_eg_task = ov2680_suspend_eg_task,
	//.set_hts = ov2680_set_hts,
	//.set_vts = ov2680_set_vts,
	.csi_enable = ov2680_csi_enable,
	.csi_disable = ov2680_csi_disable,
};

int
ov2680_config(
        hwsensor_intf_t* si,
        void  *argp)
{
	struct sensor_cfg_data *data;

	int ret =0;
	static bool ov2680_power_on = false;
	static bool csi_enable = false;
	data = (struct sensor_cfg_data *)argp;
	cam_debug("ov2680 cfgtype = %d",data->cfgtype);
	switch(data->cfgtype){
		case SEN_CONFIG_POWER_ON:
			if (!ov2680_power_on) {
				ret = si->vtbl->power_up(si);
				ov2680_power_on = true;
			}
			break;
		case SEN_CONFIG_POWER_OFF:
			if (ov2680_power_on) {
				ret = si->vtbl->power_down(si);
				ov2680_power_on = false;
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
ov2680_platform_probe(
        struct platform_device* pdev)
{
	int rc = 0;
	cam_debug("enter %s",__func__);

	if (pdev->dev.of_node) {
		rc = hw_sensor_get_dt_data(pdev, &s_ov2680);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			goto ov2680_sensor_probe_fail;
		}
	} else {
		cam_err("%s ov2680 of_node is NULL.\n", __func__);
		goto ov2680_sensor_probe_fail;
	}

	rc = hwsensor_register(pdev, &s_ov2680.intf);
ov2680_sensor_probe_fail:
	return rc;
}

static int __init
ov2680_init_module(void)
{
    cam_notice("enter %s",__func__);
    return platform_driver_probe(&s_ov2680_driver,
            ov2680_platform_probe);
}

static void __exit
ov2680_exit_module(void)
{
    cam_notice("enter %s",__func__);
    platform_driver_unregister(&s_ov2680_driver);
}

module_init(ov2680_init_module);
module_exit(ov2680_exit_module);
MODULE_DESCRIPTION("ov2680");
MODULE_LICENSE("GPL v2");

