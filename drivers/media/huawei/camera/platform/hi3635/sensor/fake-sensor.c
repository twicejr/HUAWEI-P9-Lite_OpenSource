


#include <linux/module.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

#include "hwsensor.h"

typedef struct _tag_fake_sensor
{
    hwsensor_intf_t                           intf; 
    hwsensor_board_info_t                     board_info; 
    hwsensor_state_kind_t                     state; 
} fake_sensor_t;

#define I2S(i) container_of(i, fake_sensor_t, intf)

static hwsensor_vtbl_t s_fake_sensor_vtbl; 

static fake_sensor_t s_fake_sensor_fore = 
{
    .intf = { .vtbl = &s_fake_sensor_vtbl, }, 
    .board_info = { .name = "fake", }, 
}; 

static fake_sensor_t s_fake_sensor_rear = 
{
    .intf = { .vtbl = &s_fake_sensor_vtbl, }, 
    .board_info = { .name = "fake", }, 
}; 

static const struct platform_device_id 
s_fake_sensor_id[] = 
{
	{
        .name = "huawei,fake-fore", 
        .driver_data = (kernel_ulong_t)&s_fake_sensor_fore.intf, 
    },
	{
        .name = "huawei,fake-rear", 
        .driver_data = (kernel_ulong_t)&s_fake_sensor_rear.intf, 
    },
	{
    }, 
};

MODULE_DEVICE_TABLE(of, fake_sensor_dt_match);

static struct platform_driver 
s_fake_sensor_driver = 
{
	.driver = 
    {
		.name = "huawei,fake-sensor",
		.owner = THIS_MODULE,
	},
    .id_table = s_fake_sensor_id, 
};

static int32_t 
fake_sensor_platform_probe(
        struct platform_device* pdev)
{
    struct platform_device_id* id = platform_get_device_id(pdev); 
	return hwsensor_register(pdev, (hwsensor_intf_t*)id->driver_data);
}

static int __init 
fake_sensor_init_module(void)
{
    return platform_driver_probe(&s_fake_sensor_driver, 
            fake_sensor_platform_probe);
}

static void __exit 
fake_sensor_exit_module(void)
{
    platform_driver_unregister(&s_fake_sensor_driver);
}

int 
fake_sensor_config(
        hwsensor_intf_t* si,  
        void __user *argp)
{
    fake_sensor_t* s = I2S(si);
	return 0;
}

char const* 
fake_sensor_get_name(
        hwsensor_intf_t* si)
{
    fake_sensor_t* s = I2S(si);
    return s->board_info.name; 
}

int 
fake_sensor_power_up(
        hwsensor_intf_t* si)
{
    fake_sensor_t* s = I2S(si);
    return 0; 
}

int 
fake_sensor_power_down(
        hwsensor_intf_t* si)
{
    fake_sensor_t* s = I2S(si);
    return 0; 
}

int 
fake_sensor_match_id(
        hwsensor_intf_t* si)
{
    fake_sensor_t* s = I2S(si);
    return 0; 
}

static hwsensor_vtbl_t
s_fake_sensor_vtbl = 
{
	.get_name = fake_sensor_get_name,
	.config = fake_sensor_config,
	.power_up = fake_sensor_power_up,
	.power_down = fake_sensor_power_down,
	.match_id = fake_sensor_match_id,
};

module_init(fake_sensor_init_module);
module_exit(fake_sensor_exit_module);
MODULE_DESCRIPTION("huawei,fake-sensor");
MODULE_LICENSE("GPL v2");

