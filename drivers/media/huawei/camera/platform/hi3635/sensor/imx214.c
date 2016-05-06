


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
static hwsensor_vtbl_t s_imx214_vtbl;

int imx214_config(hwsensor_intf_t* si, void  *argp);

struct sensor_power_setting hw_imx214_power_setting[] = {
         //MINIISP CS
        {
        	.seq_type = SENSOR_CS,
        	.config_val = SENSOR_GPIO_HIGH,
        	.sensor_index = SENSOR_INDEX_INVALID,
        	.delay = 1,
        },
        //MINIISP DVDD 1.1V
        {
            .seq_type = SENSOR_LDO_EN,
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
		.seq_type = SENSOR_AVDD,
		.data = (void*)"main-sensor-avdd",
		.config_val = LDO_VOLTAGE_2P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	#if 0
	{
		.seq_type = SENSOR_IOVDD,
		.data = (void*)"common-iovdd",
		.config_val = LDO_VOLTAGE_1P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
	#endif
	{
		.seq_type = SENSOR_DVDD,
		.config_val = LDO_VOLTAGE_1P05V,
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
		.seq_type = SENSOR_VCM_PWDN,
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
	/*
	{
		.seq_type = SENSOR_I2C,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},	
	{
		.seq_type = SENSOR_SUSPEND,
		.config_val = SENSOR_GPIO_HIGH,
		.sensor_index = SENSOR_INDEX_INVALID,
	},
	*/
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
	ret = hw_sensor_power_up(sensor);
	return ret;
}

int
imx214_power_down(
        hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_sensor_power_down(sensor);
	return ret;
}

int imx214_csi_enable(hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);

	ret = hw_csi_pad.hw_csi_enable(sensor->board_info->csi_index, sensor->board_info->csi_lane, sensor->board_info->csi_mipi_clk);
	return ret;
}

int imx214_csi_disable(hwsensor_intf_t* si)
{
	int ret = 0;
	sensor_t* sensor = NULL;
	sensor = I2S(si);
	ret = hw_csi_pad.hw_csi_disable(sensor->board_info->csi_index);
	return ret;
}

static int imx214_i2c_read (hwsensor_intf_t* intf, void * data)
{
	sensor_t* sensor = NULL;
	int ret = 0;

	sensor= I2S(intf);
	ret = hw_sensor_i2c_read(sensor,data);

	return ret;
}


static int
imx214_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;

    #if 0
	struct sensor_cfg_data cdata_h;
	struct sensor_cfg_data cdata_l;
	u16 id_h = 0;
	u16 id_l = 0;
	u16 sensor_id = 0;

    cam_info("%s TODO.", __func__);

	cdata_h.cfg.reg.subaddr = 0x0016;
	cdata_h.cfg.reg.value = 0;

	cdata_l.cfg.reg.subaddr = 0x0017;
	cdata_l.cfg.reg.value = 0;

	imx214_i2c_read(sensor, &cdata_h);
	imx214_i2c_read(sensor, &cdata_l);

	sensor_id = (cdata_h.cfg.reg.value) << 8 | (cdata_l.cfg.reg.value);

	cam_notice( "%s, line %d, sensor id: 0x%x", __func__, __LINE__, sensor_id);
    id = read_i2c();
    if (id == chipid) {
        cam_info("%s succeed to match id.", __func__);
    } else {
        cam_info("%s failed to match id.", __func__);
        sensor->board_info->sensor_index = CAMERA_SENSOR_INVALID;
    }
#endif

    cdata->data = sensor->board_info->sensor_index;
    hwsensor_writefile(sensor->board_info->sensor_index,
        sensor->board_info->name);
    return 0;
}

static int imx214_i2c_write (hwsensor_intf_t* intf, void * data)
{
	sensor_t* sensor = NULL;
	int ret = 0;

	sensor= I2S(intf);
	ret = hw_sensor_i2c_write(sensor,data);

	return ret;
}

static int imx214_i2c_read_seq (hwsensor_intf_t* intf, void * data)
{
	sensor_t* sensor = NULL;
	int ret = 0;

	sensor= I2S(intf);
	ret = hw_sensor_i2c_read_seq(sensor,data);

	return ret;
}

static int imx214_i2c_write_seq (hwsensor_intf_t* intf, void * data)
{
	sensor_t* sensor = NULL;
	int ret = 0;

	sensor= I2S(intf);
	ret = hw_sensor_i2c_write_seq(sensor,data);

	return ret;
}

static hwsensor_vtbl_t
s_imx214_vtbl =
{
	.get_name = imx214_get_name,
	.config = imx214_config,
	.power_up = imx214_power_up,
	.power_down = imx214_power_down,
	.i2c_read = imx214_i2c_read,
	.i2c_write = imx214_i2c_write,
	.i2c_read_seq = imx214_i2c_read_seq,
	.i2c_write_seq = imx214_i2c_write_seq,
	//.ioctl = imx214_ioctl,
	.match_id = imx214_match_id,
	//.set_expo_gain = imx214_set_expo_gain,
	//.apply_expo_gain = imx214_apply_expo_gain,
	//.suspend_eg_task = imx214_suspend_eg_task,
	//.set_hts = imx214_set_hts,
	//.set_vts = imx214_set_vts,
	.csi_enable = imx214_csi_enable,
	.csi_disable = imx214_csi_disable,
};

int
imx214_config(
        hwsensor_intf_t* si,
        void  *argp)
{
	struct sensor_cfg_data *data;

	int ret =0;
	static bool imx214_power_on = false;
	static bool csi_enable = false;
	data = (struct sensor_cfg_data *)argp;
	cam_debug("imx214 cfgtype = %d",data->cfgtype);
	switch(data->cfgtype){
		case SEN_CONFIG_POWER_ON:
			if (!imx214_power_on) {
				ret = si->vtbl->power_up(si);
				imx214_power_on = true;
			}
			break;
		case SEN_CONFIG_POWER_OFF:
			if (imx214_power_on) {
				ret = si->vtbl->power_down(si);
				imx214_power_on = false;
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

	rc = hwsensor_register(pdev, &s_imx214.intf);
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
    platform_driver_unregister(&s_imx214_driver);
}

module_init(imx214_init_module);
module_exit(imx214_exit_module);
MODULE_DESCRIPTION("imx214");
MODULE_LICENSE("GPL v2");

