


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

extern struct hw_csi_pad hw_csi_pad;
static hwsensor_vtbl_t s_imx214_vtbl;

int imx214_config(hwsensor_intf_t* si, void  *argp);

struct sensor_power_setting hw_imx214_power_setting[] = {

    //MCAM1 AFVDD 2.85V
    {
        .seq_type = SENSOR_VCM_AVDD,
        .data = (void*)"cameravcm-vcc",
        .config_val = LDO_VOLTAGE_V2P85V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 AVDD 2.85V
    {
        .seq_type = SENSOR_AVDD,
        .data = (void*)"main-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P85V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 DVDD 1.0V
    {
        .seq_type = SENSOR_DVDD,
        .config_val = LDO_VOLTAGE_1P05V,
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

};

static sensor_t s_imx214 =
{
    .intf = { .vtbl = &s_imx214_vtbl, },
    .power_setting_array = {
            .size = ARRAY_SIZE(hw_imx214_power_setting),
            .power_setting = hw_imx214_power_setting,
     },
};

static const struct of_device_id
s_imx214_dt_match[] =
{
	{
        .compatible = "huawei,imx214",
        .data = &s_imx214.intf,
    },
	{
    },
};

MODULE_DEVICE_TABLE(of, s_imx214_dt_match);

static struct platform_driver
s_imx214_driver =
{
	.driver =
    {
		.name = "huawei,imx214",
		.owner = THIS_MODULE,
		.of_match_table = s_imx214_dt_match,
	},
};

char const*
imx214_get_name(
        hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

int
imx214_power_up(
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

int
imx214_power_down(
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

int imx214_csi_enable(hwsensor_intf_t* si)
{
    return 0;
}

int imx214_csi_disable(hwsensor_intf_t* si)
{
    return 0;
}

static int
imx214_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
//  hwsensor_board_info_t *board_info = sensor->board_info;
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
//    int sensor_index = CAMERA_SENSOR_INVALID;
//    int ret = 0;
//    int camif_id = -1;

    cam_info("%s TODO.", __func__);
#if	0
    if(0 == board_info->gpios[FSIN].gpio) {
		cam_err("%s gpio type[FSIN] is not actived.", __func__);
		ret = -1;
		goto out;
    }

    ret = gpio_request(board_info->gpios[FSIN].gpio, "camif_id");
    if(ret < 0) {
		cam_err("failed to request gpio[%d]", board_info->gpios[FSIN].gpio);
		goto out;
	}
    ret = gpio_direction_input(board_info->gpios[FSIN].gpio);
    if(ret < 0) {
		cam_err("failed to control gpio[%d]", board_info->gpios[FSIN].gpio);
		goto out_gpio;
	}

    ret = gpio_get_value(board_info->gpios[FSIN].gpio);
    if(ret < 0) {
		cam_err("failed to get gpio[%d]", board_info->gpios[FSIN].gpio);
		goto out_gpio;
	} else {
		camif_id = ret;
		cam_notice("%s camif id = %d.", __func__, camif_id);
	}

	if (camif_id != board_info->camif_id) {
		cam_notice("%s camera[%s] module is not match.", __func__, board_info->name);
		board_info->sensor_index = CAMERA_SENSOR_INVALID;
		ret = -1;
	} else {
		cam_notice("%s camera[%s] match successfully.", __func__, board_info->name);
		sensor_index = board_info->sensor_index;
		ret = 0;
	}

out_gpio:
	gpio_free(board_info->gpios[FSIN].gpio);
out:
    cdata->data = sensor_index;
    return ret;
#endif
    cdata->data = sensor->board_info->sensor_index;

	return 0;

}

static ssize_t imx214_powerctrl_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;
        cam_info("enter %s", __func__);

        return rc;
}
static ssize_t imx214_powerctrl_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int state = simple_strtol(buf, NULL, 10);
	cam_info("enter %s, state %d", __func__, state);

	if (state == POWER_ON)
		imx214_power_up(&s_imx214.intf);
	else
		imx214_power_down(&s_imx214.intf);

	return count;
}


static struct device_attribute imx214_powerctrl =
    __ATTR(power_ctrl, 0664, imx214_powerctrl_show, imx214_powerctrl_store);

int imx214_register_attribute(hwsensor_intf_t* intf, struct device* dev)
{
	int ret = 0;
	cam_info("enter %s", __func__);

	ret = device_create_file(dev, &imx214_powerctrl);
	if (ret < 0) {
		cam_err("%s failed to creat power ctrl attribute.", __func__);
		goto err_create_power_ctrl;
	}
	return 0;
err_create_power_ctrl:
	device_remove_file(dev, &imx214_powerctrl);
	return ret;
}

static hwsensor_vtbl_t
s_imx214_vtbl =
{
	.get_name = imx214_get_name,
	.config = imx214_config,
	.power_up = imx214_power_up,
	.power_down = imx214_power_down,
	.match_id = imx214_match_id,
	.csi_enable = imx214_csi_enable,
	.csi_disable = imx214_csi_disable,
#ifdef DEBUG_HISI_CAMERA
	.sensor_register_attribute = imx214_register_attribute,
#endif
};

int
imx214_config(
        hwsensor_intf_t* si,
        void  *argp)
{
	struct sensor_cfg_data *data;

	int ret =0;
	data = (struct sensor_cfg_data *)argp;
	cam_debug("imx214 cfgtype = %d",data->cfgtype);
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
imx214_platform_probe(
        struct platform_device* pdev)
{
	int rc = 0;
	cam_notice("enter %s",__func__);
	if (pdev->dev.of_node) {
		rc = hw_sensor_get_dt_data(pdev, &s_imx214);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			goto imx214_sensor_probe_fail;
		}
	} else {
		cam_err("%s imx214 of_node is NULL.\n", __func__);
		goto imx214_sensor_probe_fail;
	}

    s_imx214.dev = &pdev->dev;

	rc = hwsensor_register(pdev, &s_imx214.intf);
	rc = rpmsg_sensor_register(pdev, (void*)&s_imx214);

imx214_sensor_probe_fail:
	return rc;
}

static int __init
imx214_init_module(void)
{
    cam_notice("enter %s",__func__);
    return platform_driver_probe(&s_imx214_driver,
            imx214_platform_probe);
}

static void __exit
imx214_exit_module(void)
{
    rpmsg_sensor_unregister((void*)&s_imx214);
    hwsensor_unregister(&s_imx214.intf);
    platform_driver_unregister(&s_imx214_driver);
}

module_init(imx214_init_module);
module_exit(imx214_exit_module);
MODULE_DESCRIPTION("imx214");
MODULE_LICENSE("GPL v2");
