


#include <linux/module.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

#include "hwsensor.h"

typedef struct _tag_imx135
{
    hwsensor_intf_t                           intf;
    hwsensor_board_info_t                     board_info;
    hwsensor_state_kind_t                     state;
} imx135_t;

#define I2S(i) container_of(i, imx135_t, intf)

static hwsensor_vtbl_t s_imx135_vtbl;

static imx135_t s_imx135 =
{
    .intf = { .vtbl = &s_imx135_vtbl, },
    .board_info = { .name = "imx135", },
};

static const struct of_device_id
s_imx135_dt_match[] =
{
	{
        .compatible = "huawei,imx135",
        .data = &s_imx135.intf,
    },
	{
    },
};

MODULE_DEVICE_TABLE(of, s_imx135_dt_match);

static struct platform_driver
s_imx135_driver =
{
	.driver =
    {
		.name = "huawei,imx135",
		.owner = THIS_MODULE,
		.of_match_table = s_imx135_dt_match,
	},
};

static int32_t
imx135_platform_probe(
        struct platform_device* pdev)
{
	return hwsensor_register(pdev, &s_imx135.intf);
}

static int __init
imx135_init_module(void)
{
    return platform_driver_probe(&s_imx135_driver,
            imx135_platform_probe);
}

static void __exit
imx135_exit_module(void)
{
    platform_driver_unregister(&s_imx135_driver);
}

int
imx135_config(
        hwsensor_intf_t* si,
        void __user *argp)
{
    imx135_t* imx = I2S(si);
	return 0;
}

char const*
imx135_get_name(
        hwsensor_intf_t* si)
{
    imx135_t* imx = I2S(si);
    return imx->board_info.name;
}

int
imx135_power_up(
        hwsensor_intf_t* si)
{
    imx135_t* imx = I2S(si);
    return 0;
}

int
imx135_power_down(
        hwsensor_intf_t* si)
{
    imx135_t* imx = I2S(si);
    return 0;
}

int
imx135_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;

    cam_info("%s TODO.", __func__);

/*
    id = read_i2c();
    if (id == chipid) {
        cam_info("%s succeed to match id.", __func__);
    } else {
        cam_info("%s failed to match id.", __func__);
        sensor->board_info->sensor_index = CAMERA_SENSOR_INVALID;
    }
*/
    memset(cdata->cfg.name, 0, sizeof(cdata->cfg.name));
    cdata->data = sensor->board_info->sensor_index;
    hwsensor_writefile(sensor->board_info->sensor_index,
        sensor->board_info->name);
    return 0;
}

static hwsensor_vtbl_t
s_imx135_vtbl =
{
	.get_name = imx135_get_name,
	.config = imx135_config,
	.power_up = imx135_power_up,
	.power_down = imx135_power_down,
	.match_id = imx135_match_id,
};

module_init(imx135_init_module);
module_exit(imx135_exit_module);
MODULE_DESCRIPTION("imx135");
MODULE_LICENSE("GPL v2");

