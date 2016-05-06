


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
static hwsensor_vtbl_t s_ov13850_vtbl;

int ov13850_config(hwsensor_intf_t* si, void  *argp);

struct sensor_power_setting hw_ov13850_power_setting[] = {
    //MINIISP DVDD 1.1V
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



	{
		.seq_type = SENSOR_IOVDD,
		.data = (void*)"common-iovdd",
		.config_val = LDO_VOLTAGE_1P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},


	{
		.seq_type = SENSOR_VCM_AVDD,
		.data = (void*)"cameravcm-vcc",
		.config_val = LDO_VOLTAGE_2P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},

	{
		.seq_type = SENSOR_AVDD,
		.data = (void*)"main-sensor-avdd",
		.config_val = LDO_VOLTAGE_2P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},

	{
		.seq_type = SENSOR_DVDD,
		.config_val = LDO_VOLTAGE_1P2V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},

        {
		.seq_type = SENSOR_MINIISP_VPP,
		.config_val = LDO_VOLTAGE_1P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},

	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},

    //MCAM1 RESET
    {
        .seq_type = SENSOR_RST,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

	{
		.seq_type = SENSOR_VCM_PWDN,
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
};

static sensor_t s_ov13850 =
{
    .intf = { .vtbl = &s_ov13850_vtbl, },
    .power_setting_array = {
            .size = ARRAY_SIZE(hw_ov13850_power_setting),
            .power_setting = hw_ov13850_power_setting,
     },
};

static const struct of_device_id
s_ov13850_dt_match[] =
{
	{
        .compatible = "huawei,ov13850_foxconn",
        .data = &s_ov13850.intf,
    },
	{
    },
};

MODULE_DEVICE_TABLE(of, s_ov13850_dt_match);

static struct platform_driver
s_ov13850_driver =
{
	.driver =
    {
		.name = "huawei,ov13850",
		.owner = THIS_MODULE,
		.of_match_table = s_ov13850_dt_match,
	},
};

char const*
ov13850_get_name(
        hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}


int
ov13850_power_up(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_sensor_power_up(sensor);
	return ret;
}

int
ov13850_power_down(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_sensor_power_down(sensor);
	return ret;
}

int ov13850_csi_enable(hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);

    ret = hw_csi_pad.hw_csi_enable(0, sensor->board_info->csi_lane, sensor->board_info->csi_mipi_clk);//by hefei
    if(ret)
    {
        cam_err("failed to csi enable index 0 ");
        return ret;
    }

    return 0;
}

int ov13850_csi_disable(hwsensor_intf_t* si)
{
    int ret = 0;
    sensor_t* sensor = NULL;

    sensor = I2S(si);

    ret = hw_csi_pad.hw_csi_disable(0);//by hefei
    if(ret)
    {
        cam_err("failed to csi disable index 0 ");
        return ret;
    }

    return 0;
}
static int ov13850_match_id(hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
    uint16_t sensor_id = 0;
    uint8_t modue_id = 0;

    cam_info("%s TODO.", __func__);

    misp_get_module_info(sensor->board_info->sensor_index,&sensor_id,&modue_id);

    if(sensor_id == 0xd850) {
        cdata->data = sensor->board_info->sensor_index;
        hwsensor_writefile(sensor->board_info->sensor_index,
                   sensor->board_info->name);
    } else {
        cdata->data = SENSOR_INDEX_INVALID;
    }

    cam_info("%s TODO.  cdata->data=%d", __func__, cdata->data);

    return 0;
}

static ssize_t ov13850_powerctrl_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;
        cam_info("enter %s", __func__);

        return rc;
}
static ssize_t ov13850_powerctrl_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int state = simple_strtol(buf, NULL, 10);
	cam_info("enter %s, state %d", __func__, state);

	if (state == POWER_ON)
		ov13850_power_up(&s_ov13850.intf);
	else
		ov13850_power_down(&s_ov13850.intf);

	return count;
}


static struct device_attribute ov13850_powerctrl =
    __ATTR(power_ctrl, 0664, ov13850_powerctrl_show, ov13850_powerctrl_store);

int ov13850_register_attribute(hwsensor_intf_t* intf, struct device* dev)
{
	int ret = 0;
	cam_info("enter %s", __func__);

	ret = device_create_file(dev, &ov13850_powerctrl);
	if (ret < 0) {
		cam_err("%s failed to creat power ctrl attribute.", __func__);
		goto err_create_power_ctrl;
	}
	return 0;
err_create_power_ctrl:
	device_remove_file(dev, &ov13850_powerctrl);
	return ret;
}

static hwsensor_vtbl_t
s_ov13850_vtbl =
{
	.get_name = ov13850_get_name,
	.config = ov13850_config,
	.power_up = ov13850_power_up,
	.power_down = ov13850_power_down,


	.match_id = ov13850_match_id,

	.csi_enable = ov13850_csi_enable,
	.csi_disable = ov13850_csi_disable,
	.sensor_register_attribute = ov13850_register_attribute,
};

int
ov13850_config(
        hwsensor_intf_t* si,
        void  *argp)
{
	struct sensor_cfg_data *data;

	int ret =0;
	static bool ov13850_power_on = false;
	static bool csi_enable = false;
	data = (struct sensor_cfg_data *)argp;
	cam_debug("ov13850 cfgtype = %d",data->cfgtype);
	switch(data->cfgtype){
		case SEN_CONFIG_POWER_ON:
			if (!ov13850_power_on) {
				ret = si->vtbl->power_up(si);
				ov13850_power_on = true;
			}
			break;
		case SEN_CONFIG_POWER_OFF:
			if (ov13850_power_on) {
				ret = si->vtbl->power_down(si);
				ov13850_power_on = false;
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
			break;
	}
	cam_debug("%s exit",__func__);
	return ret;
}

static int32_t
ov13850_platform_probe(
        struct platform_device* pdev)
{
	int rc = 0;
	cam_notice("enter %s",__func__);
	if (pdev->dev.of_node) {
		rc = hw_sensor_get_dt_data(pdev, &s_ov13850);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			goto ov13850_sensor_probe_fail;
		}
	} else {
		cam_err("%s ov13850 of_node is NULL.\n", __func__);
		goto ov13850_sensor_probe_fail;
	}

	rc = hwsensor_register(pdev, &s_ov13850.intf);
ov13850_sensor_probe_fail:
	return rc;
}

static int __init
ov13850_init_module(void)
{
    cam_notice("enter %s",__func__);
     return platform_driver_probe(&s_ov13850_driver,
            ov13850_platform_probe);

}

static void __exit
ov13850_exit_module(void)
{
    hwsensor_unregister(&s_ov13850.intf);
    platform_driver_unregister(&s_ov13850_driver);
}

module_init(ov13850_init_module);
module_exit(ov13850_exit_module);
MODULE_DESCRIPTION("ov13850");
MODULE_LICENSE("GPL v2");

