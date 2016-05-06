


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
static hwsensor_vtbl_t s_ov8865_rear_vtbl;

int ov8865_rear_config(hwsensor_intf_t* si, void  *argp);

struct sensor_power_setting ov8865_rear_power_setting[] = {

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

    //MCAM2 AFVDD 2.85V
    {
        .seq_type = SENSOR_PMIC,
        .seq_val = PMIC_LDO2,
        .config_val = PMIC_2P85V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 AFVDD 2.85V
    {
        .seq_type = SENSOR_VCM_AVDD,
        .data = (void*)"cameravcm-vcc",
        .config_val = LDO_VOLTAGE_V2P85V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM2 AVDD 2.8V
    {
        .seq_type = SENSOR_PMIC,
        .seq_val = PMIC_LDO1,
        .config_val = PMIC_2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 AVDD 2.8V
    {
        .seq_type = SENSOR_AVDD,
        .data = (void*)"main-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM2 IOVDD 1.8V
    {
        .seq_type = SENSOR_PMIC,
        .seq_val = PMIC_LDO3,
        .config_val = PMIC_1P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 IOVDD 1.8V
    {
        .seq_type = SENSOR_IOVDD,
        .data = (void*)"common-iovdd",
        .config_val = LDO_VOLTAGE_1P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM2 DVDD 1.2V
    {
        .seq_type = SENSOR_PMIC,
        .seq_val = PMIC_BUCK1,
        .config_val = PMIC_1P2V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 DVDD 1.2V
    {
        .seq_type = SENSOR_DVDD,
        .config_val = LDO_VOLTAGE_1P2V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    {
        .seq_type = SENSOR_MCLK,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM2 RESET
    {
        .seq_type = SENSOR_RST2,
        .config_val = SENSOR_GPIO_LOW,
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


static sensor_t s_ov8865_rear =
{
    .intf = { .vtbl = &s_ov8865_rear_vtbl, },
    .power_setting_array = {
            .size = ARRAY_SIZE(ov8865_rear_power_setting),
            .power_setting = ov8865_rear_power_setting,
     },
};

static const struct of_device_id
s_ov8865_rear_dt_match[] =
{
	{
        .compatible = "huawei,ov8865_rear",
        .data = &s_ov8865_rear.intf,
    },
	{
    },
};

MODULE_DEVICE_TABLE(of, s_ov8865_rear_dt_match);

static int ov8865_suspend(struct platform_device *pdev, pm_message_t state)
{
    return 0;
}
static int ov8865_resume(struct platform_device *pdev)
{
    int ret = 0;
    struct v4l2_event event =
    {
        .type = HWCAM_V4L2_EVENT_TYPE,
        .id = HWCAM_HARDWARE_RESUME,
    };
    cam_info("%s +", __func__);
    ret = hwsensor_notify(&pdev->dev,&event);
    if(ret!=0){
        cam_err("%s fail to notify resume event to video device user",__func__);
    }
    cam_info("%s -", __func__);
    return ret;
}

static struct platform_driver
s_ov8865_rear_driver =
{
	.driver =
    {
		.name = "huawei,ov8865_rear",
		.owner = THIS_MODULE,
		.of_match_table = s_ov8865_rear_dt_match,
	},
    .suspend = ov8865_suspend,
    .resume = ov8865_resume,
};

char const*
ov8865_rear_get_name(
        hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

int
ov8865_rear_power_up(
        hwsensor_intf_t* si)
{
    int ret = 0;
    sensor_t* sensor = NULL;
    sensor = I2S(si);

    //step1 enable sensor afvdd 2.8v
    //enable mcam2 pmic ldo2 2.8v
    //enable mcam1 ldo25 2.8v

    //step2 enable sensor avdd 2.8v
    //enable mcam2 pmic ldo1 2.8v
    //enable mcam1 ldo21 2.8v

    //step3 enable sensor iovdd 1.8v
    //enable mcam2 pmic ldo3 1.8v
    //enable mcam1 lsw51 1.8v

    //step4 enable sensor dvdd 1.2v
    //enable mcam2 pmic buck1 1.2v
    //enable mcam1 ldo20 1.2v

    //step5 enable mclk0 20mhz
    //enable mclk0 20mhz

    //step6 pullup sensor reset
    //pullup gpio33
    //pullup gpio25

    ret = hw_sensor_power_up(sensor);

    return ret;
}

int
ov8865_rear_power_down(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_sensor_power_down(sensor);
	return ret;
}

int ov8865_rear_csi_enable(hwsensor_intf_t* si)
{
    int ret = 0;
    sensor_t* sensor = NULL;

    sensor = I2S(si);

	//ret = hw_csi_pad.hw_csi_enable(sensor->board_info->csi_index, sensor->board_info->csi_lane, sensor->board_info->csi_mipi_clk);
    ret = hw_csi_pad.hw_csi_enable(0, sensor->board_info->csi_lane, sensor->board_info->csi_mipi_clk);//by hefei
    if(ret)
    {
        cam_err("failed to csi enable index 0 ");
        return ret;
    }

    ret = hw_csi_pad.hw_csi_enable(1, sensor->board_info->csi_lane, sensor->board_info->csi_mipi_clk);
    if(ret)
    {
        cam_err("failed to csi enable index 1 ");
        return ret;
    }

    return 0;
}

int ov8865_rear_csi_disable(hwsensor_intf_t* si)
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

    ret = hw_csi_pad.hw_csi_disable(1);
    if(ret)
    {
        cam_err("failed to csi disable index 1 ");
        return ret;
    }

    return 0;
}

static int
ov8865_rear_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    hwsensor_board_info_t *board_info = sensor->board_info;
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
    int sensor_index = CAMERA_SENSOR_INVALID;
    int ret = 0;
    int camif_id = -1;

    cam_info("%s TODO.", __func__);

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
    memset(cdata->cfg.name, 0, sizeof(cdata->cfg.name));
    cdata->data = sensor_index;
    if (ret == 0)
        hwsensor_writefile(sensor->board_info->sensor_index,
            sensor->board_info->name);
    return ret;
}

static ssize_t ov8865_powerctrl_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;
        cam_info("enter %s", __func__);

        return rc;
}
static ssize_t ov8865_powerctrl_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int state = simple_strtol(buf, NULL, 10);
	cam_info("enter %s, state %d", __func__, state);

	if (state == POWER_ON)
		ov8865_rear_power_up(&s_ov8865_rear.intf);
	else
		ov8865_rear_power_down(&s_ov8865_rear.intf);

	return count;
}


static struct device_attribute ov8865_powerctrl =
    __ATTR(power_ctrl, 0664, ov8865_powerctrl_show, ov8865_powerctrl_store);

int ov8865_register_attribute(hwsensor_intf_t* intf, struct device* dev)
{
	int ret = 0;
	cam_info("enter %s", __func__);

	ret = device_create_file(dev, &ov8865_powerctrl);
	if (ret < 0) {
		cam_err("%s failed to creat power ctrl attribute.", __func__);
		goto err_create_power_ctrl;
	}
	return 0;
err_create_power_ctrl:
	device_remove_file(dev, &ov8865_powerctrl);
	return ret;
}

static hwsensor_vtbl_t
s_ov8865_rear_vtbl =
{
	.get_name = ov8865_rear_get_name,
	.config = ov8865_rear_config,
	.power_up = ov8865_rear_power_up,
	.power_down = ov8865_rear_power_down,
	.match_id = ov8865_rear_match_id,
	.csi_enable = ov8865_rear_csi_enable,
	.csi_disable = ov8865_rear_csi_disable,
	.sensor_register_attribute = ov8865_register_attribute,
};

int
ov8865_rear_config(
        hwsensor_intf_t* si,
        void  *argp)
{
	struct sensor_cfg_data *data;
	static bool ov8865_power_on = false;
	static bool csi_enable = false;
	int ret =0;
	data = (struct sensor_cfg_data *)argp;
	cam_debug("ov8865_rear cfgtype = %d",data->cfgtype);
	switch(data->cfgtype){
		case SEN_CONFIG_POWER_ON:
			if (!ov8865_power_on) {
				ret = si->vtbl->power_up(si);
			    ov8865_power_on = true;
			}
			break;
		case SEN_CONFIG_POWER_OFF:
			if (ov8865_power_on) {
				ret = si->vtbl->power_down(si);
                ov8865_power_on = false;
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
ov8865_rear_platform_probe(
        struct platform_device* pdev)
{
	int rc = 0;
	cam_notice("enter %s",__func__);

	if (pdev->dev.of_node) {
		rc = hw_sensor_get_dt_data(pdev, &s_ov8865_rear);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			goto ov8865_rear_sensor_probe_fail;
		}
	} else {
		cam_err("%s ov8865_rear of_node is NULL.\n", __func__);
		goto ov8865_rear_sensor_probe_fail;
	}

	rc = hwsensor_register(pdev, &s_ov8865_rear.intf);

ov8865_rear_sensor_probe_fail:
	return rc;
}

static int __init
ov8865_rear_init_module(void)
{
    cam_notice("enter %s",__func__);
    return platform_driver_probe(&s_ov8865_rear_driver,
            ov8865_rear_platform_probe);
}

static void __exit
ov8865_rear_exit_module(void)
{
    platform_driver_unregister(&s_ov8865_rear_driver);
}

module_init(ov8865_rear_init_module);
module_exit(ov8865_rear_exit_module);
MODULE_DESCRIPTION("ov8865_rear");
MODULE_LICENSE("GPL v2");
