


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
static hwsensor_vtbl_t s_imx278_vtbl;

static char *sensor_dts_name = "IMX278_A";

int imx278_config(hwsensor_intf_t* si, void  *argp);

struct sensor_power_setting hw_imx278_power_setting[] = {

	//disable slave camera reset
	{
		.seq_type = SENSOR_SUSPEND,
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//enable gpio12 output iovdd 1.8v
	{
		.seq_type = SENSOR_LDO_EN,
		.config_val = SENSOR_GPIO_LOW,
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

	//enable gpio30 output ois vdd 3.6v
	{
		.seq_type = SENSOR_OIS,
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//SCAM AVDD 2.8V
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

	//MCAM1 AVDD 2.8V
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
		//FIXME: need check  1.05V
		.config_val = LDO_VOLTAGE_V1P1V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
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

static sensor_t s_imx278 =
{
    .intf = { .vtbl = &s_imx278_vtbl, },
    .power_setting_array = {
            .size = ARRAY_SIZE(hw_imx278_power_setting),
            .power_setting = hw_imx278_power_setting,
     },
};

static const struct of_device_id
s_imx278_dt_match[] =
{
	{
        .compatible = "huawei,imx278",
        .data = &s_imx278.intf,
    },
	{
    },
};

MODULE_DEVICE_TABLE(of, s_imx278_dt_match);

static struct platform_driver
s_imx278_driver =
{
	.driver =
    {
		.name = "huawei,imx278",
		.owner = THIS_MODULE,
		.of_match_table = s_imx278_dt_match,
	},
};

char const*
imx278_get_name(
        hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

int
imx278_power_up(
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
imx278_power_down(
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

int imx278_csi_enable(hwsensor_intf_t* si)
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

int imx278_csi_disable(hwsensor_intf_t* si)
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
imx278_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
    memset(cdata->cfg.name, 0, DEVICE_NAME_SIZE);
    int32_t module_id = 0;
    char *sensor_name [] = { "IMX278_LITEON", "IMX278_SUNNY" };
    int rc = 0;

    cam_info("%s TODO.", __func__);

    if (!strncmp(sensor->board_info->name, sensor_dts_name, strlen(sensor_dts_name))) {
        rc = gpio_request(sensor->board_info->gpios[FSIN].gpio, NULL);
        if(rc < 0) {
            cam_err("%s failed to request gpio[%d]", __func__, sensor->board_info->gpios[FSIN].gpio);
            return rc;
        }

        cam_info("%s gpio[%d].", __func__, sensor->board_info->gpios[FSIN].gpio);

        rc = gpio_direction_input(sensor->board_info->gpios[FSIN].gpio);
        if (rc < 0) {
            cam_err("%s failed to config gpio(%d) input.\n",
                __func__, sensor->board_info->gpios[FSIN].gpio);
        }

        module_id = gpio_get_value_cansleep(sensor->board_info->gpios[FSIN].gpio);
        if (module_id < 0) {
            cam_err("%s failed to get gpio(%d) value(%d).\n",
                    __func__, sensor->board_info->gpios[FSIN].gpio, module_id);
        }

        cam_info("%s module_id = %d", __func__,module_id);

        gpio_free(sensor->board_info->gpios[FSIN].gpio);
        if (0 == module_id) {
            cam_info("%s module_id == 0",__func__);
            strncpy(cdata->cfg.name, sensor_name[0], DEVICE_NAME_SIZE-1);
            cdata->data = sensor->board_info->sensor_index;
        } else {
            cam_info("%s module_id == 1", __func__);
            strncpy(cdata->cfg.name, sensor_name[1], DEVICE_NAME_SIZE-1);
            cdata->data = sensor->board_info->sensor_index;
        }
    } else {
        strncpy(cdata->cfg.name, sensor->board_info->name, DEVICE_NAME_SIZE-1);
        cdata->data = sensor->board_info->sensor_index;
    }
    cam_info("%s TODO. cdata->data=%d,cdata->cfg.name = %s", __func__, cdata->data,cdata->cfg.name);

    return 0;
}

static ssize_t imx278_powerctrl_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;
        cam_info("enter %s", __func__);

        return rc;
}
static ssize_t imx278_powerctrl_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int state = simple_strtol(buf, NULL, 10);
	cam_info("enter %s, state %d", __func__, state);

	if (state == POWER_ON)
		imx278_power_up(&s_imx278.intf);
	else
		imx278_power_down(&s_imx278.intf);

	return count;
}


static struct device_attribute imx278_powerctrl =
    __ATTR(power_ctrl, 0664, imx278_powerctrl_show, imx278_powerctrl_store);

int imx278_register_attribute(hwsensor_intf_t* intf, struct device* dev)
{
	int ret = 0;

	ret = device_create_file(dev, &imx278_powerctrl);
	if (ret < 0) {
		cam_err("%s failed to creat power ctrl attribute.", __func__);
		goto err_create_power_ctrl;
	}
	return 0;
err_create_power_ctrl:
	device_remove_file(dev, &imx278_powerctrl);
	return ret;
}

static hwsensor_vtbl_t
s_imx278_vtbl =
{
	.get_name = imx278_get_name,
	.config = imx278_config,
	.power_up = imx278_power_up,
	.power_down = imx278_power_down,
	.match_id = imx278_match_id,
	.csi_enable = imx278_csi_enable,
	.csi_disable = imx278_csi_disable,
#ifdef DEBUG_HISI_CAMERA
	.sensor_register_attribute = imx278_register_attribute,
#endif
};

int
imx278_config(
        hwsensor_intf_t* si,
        void  *argp)
{
    if (NULL == si || NULL == argp){
        cam_err("%s si or argp is null.\n", __func__);
        return -1;
    }
	struct sensor_cfg_data *data;

	int ret =0;
	static bool imx278_power_on = false;
	data = (struct sensor_cfg_data *)argp;
	cam_debug("imx278 cfgtype = %d",data->cfgtype);
	switch(data->cfgtype){
		case SEN_CONFIG_POWER_ON:
			if (!imx278_power_on) {
				ret = si->vtbl->power_up(si);
				imx278_power_on = true;
			}
			break;
		case SEN_CONFIG_POWER_OFF:
			if (imx278_power_on) {
				ret = si->vtbl->power_down(si);
				imx278_power_on = false;
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
	cam_debug("%s exit",__func__);
	return ret;
}

static int32_t
imx278_platform_probe(
        struct platform_device* pdev)
{
    if (NULL == pdev){
        cam_err("%s pdev is null.\n", __func__);
        return -1;
    }
	int rc = 0;
	cam_notice("enter %s",__func__);
	if (pdev->dev.of_node) {
		rc = hw_sensor_get_dt_data(pdev, &s_imx278);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			goto imx278_sensor_probe_fail;
		}
	} else {
		cam_err("%s imx278 of_node is NULL.\n", __func__);
		goto imx278_sensor_probe_fail;
	}

    s_imx278.dev = &pdev->dev;

	rc = hwsensor_register(pdev, &s_imx278.intf);
    if (0 != rc){
        cam_err("%s hwsensor_register fail.\n", __func__);
        goto imx278_sensor_probe_fail;
    }
	rc = rpmsg_sensor_register(pdev, (void *)&s_imx278);
    if (0 != rc){
        cam_err("%s rpmsg_sensor_register fail.\n", __func__);
        hwsensor_unregister(&s_imx278.intf);
        goto imx278_sensor_probe_fail;
    }

imx278_sensor_probe_fail:
	return rc;
}

static int __init
imx278_init_module(void)
{
    cam_notice("enter %s",__func__);
    return platform_driver_probe(&s_imx278_driver,
            imx278_platform_probe);
}

static void __exit
imx278_exit_module(void)
{
    rpmsg_sensor_unregister((void *)&s_imx278);
    hwsensor_unregister(&s_imx278.intf);
    platform_driver_unregister(&s_imx278_driver);
}

module_init(imx278_init_module);
module_exit(imx278_exit_module);
MODULE_DESCRIPTION("imx278");
MODULE_LICENSE("GPL v2");
