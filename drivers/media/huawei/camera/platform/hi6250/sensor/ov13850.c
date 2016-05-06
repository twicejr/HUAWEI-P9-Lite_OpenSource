


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

static char *sensor_dts_name = "OV13850_VENDOR";

enum module_type_t{
	MODULE_LITEON=0,
	MODULE_OFILM=1,
	MODULE_UNKNOWN,
};

extern struct hw_csi_pad hw_csi_pad;
static hwsensor_vtbl_t s_ov13850_vtbl;

int ov13850_config(hwsensor_intf_t* si, void  *argp);

struct sensor_power_setting hw_ov13850_power_setting[] = {

    //disable sec camera reset
    {
        .seq_type = SENSOR_SUSPEND,
        .config_val = SENSOR_GPIO_LOW,
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

    //SCAM DVDD1.2V
    {
        .seq_type = SENSOR_DVDD,
        .config_val = LDO_VOLTAGE_1P2V,
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
        .config_val = LDO_VOLTAGE_1P2V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //MCAM1 AFVDD 2.85V
    {
        .seq_type = SENSOR_VCM_AVDD,
        .data = (void*)"cameravcm-vcc",
        .config_val = LDO_VOLTAGE_V2P85V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 VCM Enable
    {
        .seq_type = SENSOR_VCM_PWDN,
        .config_val = SENSOR_GPIO_LOW,
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
        .compatible = "huawei,ov13850",
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

char const* ov13850_get_name(hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

int ov13850_power_up(hwsensor_intf_t* si)
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

int ov13850_power_down(hwsensor_intf_t* si)
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

int ov13850_csi_enable(hwsensor_intf_t* si)
{
    return 0;
}

int ov13850_csi_disable(hwsensor_intf_t* si)
{
    return 0;
}

static int
ov13850_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
	int32_t module_id = 0;
	char *sensor_name [] = { "OV13850_LITEON", "OV13850_OFILM" };
	int rc = 0;

    memset(cdata->cfg.name, 0, DEVICE_NAME_SIZE);
	if (!strncmp(sensor->board_info->name, sensor_dts_name, strlen(sensor_dts_name))) {
		rc = gpio_request(sensor->board_info->gpios[FSIN].gpio, NULL);
		if(rc < 0) {
			cam_err("%s failed to request gpio[%d]", __func__, sensor->board_info->gpios[FSIN].gpio);
			return rc;
		}

              cam_info("%s gpio[%d].", __func__, sensor->board_info->gpios[FSIN].gpio);
		rc = gpio_direction_input(sensor->board_info->gpios[FSIN].gpio);

		if (rc < 0) {
		    cam_err("%s failed to config gpio(%d) input.\n",__func__, sensor->board_info->gpios[FSIN].gpio);
		}

		module_id = gpio_get_value_cansleep(sensor->board_info->gpios[FSIN].gpio);
		if (module_id < 0) {
		    cam_err("%s failed to get gpio(%d) value(%d).\n",__func__, sensor->board_info->gpios[FSIN].gpio, module_id);
		}

		cam_info("%s module_id = %d", __func__,module_id);

		gpio_free(sensor->board_info->gpios[FSIN].gpio);

		if (MODULE_LITEON == module_id) {
		    strncpy(cdata->cfg.name, sensor_name[0], strlen(sensor_name[0])+1);
		    cdata->data = sensor->board_info->sensor_index;
		}
		else if(MODULE_OFILM == module_id){
		    strncpy(cdata->cfg.name, sensor_name[1], strlen(sensor_name[1])+1);
		    cdata->data = sensor->board_info->sensor_index;
		}else{
			cam_err("%s module unknown %d", __func__,module_id);
		}
	} else {
	    strncpy(cdata->cfg.name, sensor->board_info->name, strlen(sensor->board_info->name)+1);
	    cdata->data = sensor->board_info->sensor_index;
	}

	if (cdata->data != SENSOR_INDEX_INVALID) {
	    hwsensor_writefile(sensor->board_info->sensor_index, cdata->cfg.name);
	    cam_info("%s, cdata->cfg.name = %s", __func__,cdata->cfg.name );
	}
    
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

	if (NULL == si || NULL == argp){
		cam_err("%s : si or argp is null", __func__);
		return -1;
	}

	data = (struct sensor_cfg_data *)argp;
	cam_debug("ov13850 cfgtype = %d",data->cfgtype);
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
			break;
		case SEN_CONFIG_DISABLE_CSI:
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

    s_ov13850.dev = &pdev->dev;

	rc = hwsensor_register(pdev, &s_ov13850.intf);
	rc = rpmsg_sensor_register(pdev, (void*)&s_ov13850);

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
    rpmsg_sensor_unregister((void*)&s_ov13850);
    hwsensor_unregister(&s_ov13850.intf);
    platform_driver_unregister(&s_ov13850_driver);
}

module_init(ov13850_init_module);
module_exit(ov13850_exit_module);
MODULE_DESCRIPTION("ov13850");
MODULE_LICENSE("GPL v2");
