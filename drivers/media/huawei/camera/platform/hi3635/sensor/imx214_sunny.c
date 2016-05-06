


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
static hwsensor_vtbl_t s_imx214_sunny_vtbl;

int imx214_sunny_config(hwsensor_intf_t* si, void  *argp);

struct sensor_power_setting hw_imx214_sunny_power_setting[] = {
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
        .seq_type = SENSOR_RST2,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MINIISP IOVDD 1.8V
    {
        .seq_type = SENSOR_IOVDD,
        .data = (void*)"common-iovdd",
        .config_val = LDO_VOLTAGE_1P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 IOVDD 1.8V
//    {
//        .seq_type = SENSOR_IOVDD,
//        .data = (void*)"common-iovdd",
//        .config_val = LDO_VOLTAGE_1P8V,
//        .sensor_index = SENSOR_INDEX_INVALID,
//        .delay = 1,
//    },
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

//	{
//		.seq_type = SENSOR_VCM_PWDN,
//		.config_val = SENSOR_GPIO_LOW,
//		.sensor_index = SENSOR_INDEX_INVALID,
//		.delay = 1,
//	},
};

static sensor_t s_imx214_sunny =
{
    .intf = { .vtbl = &s_imx214_sunny_vtbl, },
    .power_setting_array = {
            .size = ARRAY_SIZE(hw_imx214_sunny_power_setting),
            .power_setting = hw_imx214_sunny_power_setting,
     },
};

static const struct of_device_id
s_imx214_sunny_dt_match[] =
{
	{
        .compatible = "huawei,imx214_sunny",
        .data = &s_imx214_sunny.intf,
    },
	{
    },
};

MODULE_DEVICE_TABLE(of, s_imx214_sunny_dt_match);

static struct platform_driver
s_imx214_sunny_driver =
{
	.driver =
    {
		.name = "huawei,imx214_sunny",
		.owner = THIS_MODULE,
		.of_match_table = s_imx214_sunny_dt_match,
	},
};

char const*
imx214_sunny_get_name(
        hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

int
imx214_sunny_power_up(
        hwsensor_intf_t* si)
{
    int ret = 0;
    sensor_t* sensor = NULL;
    sensor = I2S(si);

    ret = hw_sensor_power_up(sensor);

    return ret;
}

int
imx214_sunny_power_down(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_sensor_power_down(sensor);
	return ret;
}

int imx214_sunny_csi_enable(hwsensor_intf_t* si)
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

int imx214_sunny_csi_disable(hwsensor_intf_t* si)
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

static int
imx214_sunny_match_id(
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

    hwsensor_writefile(sensor->board_info->sensor_index,
		sensor->board_info->name);
	return 0;

}

static ssize_t imx214_sunny_powerctrl_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;
        cam_info("enter %s", __func__);

        return rc;
}
static ssize_t imx214_sunny_powerctrl_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int state = simple_strtol(buf, NULL, 10);
	cam_info("enter %s, state %d", __func__, state);

	if (state == POWER_ON)
		imx214_sunny_power_up(&s_imx214_sunny.intf);
	else
		imx214_sunny_power_down(&s_imx214_sunny.intf);

	return count;
}


static struct device_attribute imx214_sunny_powerctrl =
    __ATTR(power_ctrl, 0664, imx214_sunny_powerctrl_show, imx214_sunny_powerctrl_store);

int imx214_sunny_register_attribute(hwsensor_intf_t* intf, struct device* dev)
{
	int ret = 0;
	cam_info("enter %s", __func__);

	ret = device_create_file(dev, &imx214_sunny_powerctrl);
	if (ret < 0) {
		cam_err("%s failed to creat power ctrl attribute.", __func__);
		goto err_create_power_ctrl;
	}
	return 0;
err_create_power_ctrl:
	device_remove_file(dev, &imx214_sunny_powerctrl);
	return ret;
}

static hwsensor_vtbl_t
s_imx214_sunny_vtbl =
{
	.get_name = imx214_sunny_get_name,
	.config = imx214_sunny_config,
	.power_up = imx214_sunny_power_up,
	.power_down = imx214_sunny_power_down,
	.match_id = imx214_sunny_match_id,
	.csi_enable = imx214_sunny_csi_enable,
	.csi_disable = imx214_sunny_csi_disable,
	.sensor_register_attribute = imx214_sunny_register_attribute,
};

int
imx214_sunny_config(
        hwsensor_intf_t* si,
        void  *argp)
{
	struct sensor_cfg_data *data;

	int ret =0;
	static bool imx214_sunny_power_on = false;
	static bool csi_enable = false;
	data = (struct sensor_cfg_data *)argp;
	cam_debug("imx214_sunny cfgtype = %d",data->cfgtype);
	switch(data->cfgtype){
		case SEN_CONFIG_POWER_ON:
			if (!imx214_sunny_power_on) {
				ret = si->vtbl->power_up(si);
				imx214_sunny_power_on = true;
			}
			break;
		case SEN_CONFIG_POWER_OFF:
			if (imx214_sunny_power_on) {
				ret = si->vtbl->power_down(si);
				imx214_sunny_power_on = false;
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
imx214_sunny_platform_probe(
        struct platform_device* pdev)
{
	int rc = 0;
	cam_notice("enter %s",__func__);
	if (pdev->dev.of_node) {
		rc = hw_sensor_get_dt_data(pdev, &s_imx214_sunny);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			goto imx214_sunny_sensor_probe_fail;
		}
	} else {
		cam_err("%s imx214_sunny of_node is NULL.\n", __func__);
		goto imx214_sunny_sensor_probe_fail;
	}

	rc = hwsensor_register(pdev, &s_imx214_sunny.intf);

imx214_sunny_sensor_probe_fail:
	return rc;
}

static int __init
imx214_sunny_init_module(void)
{
    cam_notice("enter %s",__func__);
    return platform_driver_probe(&s_imx214_sunny_driver,
            imx214_sunny_platform_probe);
}

static void __exit
imx214_sunny_exit_module(void)
{
    platform_driver_unregister(&s_imx214_sunny_driver);
}

module_init(imx214_sunny_init_module);
module_exit(imx214_sunny_exit_module);
MODULE_DESCRIPTION("imx214_sunny");
MODULE_LICENSE("GPL v2");
