/*
 * invert_hs.c -- invert headset driver
 *
 * Copyright (c) 2015 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/string.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/wakelock.h>
#include <linux/regulator/consumer.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <linux/uaccess.h>
#include <huawei_platform/log/hw_log.h>

#include "huawei_platform/audio/invert_hs.h"

#define HWLOG_TAG invert_hs
HWLOG_REGIST();

enum invert_hs_gpio_type
{
    INVERT_HS_GPIO_SOC           = 0,
    INVERT_HS_GPIO_CODEC         = 1,
};

struct invert_hs_data
{
    int gpio_mic_gnd;         /* switch chip control gpio*/
    int gpio_type;
};

static struct invert_hs_data* pdata = NULL;


static inline int invert_hs_gpio_get_value(int gpio)
{
    if(pdata->gpio_type == INVERT_HS_GPIO_CODEC) {
        return gpio_get_value_cansleep(gpio);
    } else {
        return gpio_get_value(gpio);
    }
}

static inline void invert_hs_gpio_set_value(int gpio, int value)
{
    if(pdata->gpio_type == INVERT_HS_GPIO_CODEC) {
        gpio_set_value_cansleep(gpio, value);
    } else {
        gpio_set_value(gpio, value);
    }
}


/**
 * invert_hs_control - call this function to connect mic and gnd pin
 *                       for invert headset
 *
 **/
int invert_hs_control(int connect)
{
    /* invert_hs driver not be probed, just return */
    if(pdata == NULL) {
        return -ENODEV;
    }

    /* connect mic and gnd pin */
    invert_hs_gpio_set_value(pdata->gpio_mic_gnd, connect);

    hwlog_info("%s(%u) :real invert headset,status:%d\n", __FUNCTION__, __LINE__, connect);

    return 0;
}


static const struct of_device_id invert_hs_of_match[] =
{
    {
        .compatible = "huawei,invert_hs",
    },
    { },
};
MODULE_DEVICE_TABLE(of, invert_hs_of_match);

/* load dts config for board difference */
static void load_invert_hs_config(struct device_node* node)
{
    int temp;

    if (!of_property_read_u32(node, "gpio_type", &temp)) {
        pdata->gpio_type = temp;
    } else {
        pdata->gpio_type = INVERT_HS_GPIO_SOC;
    }

}

static int invert_hs_probe(struct platform_device* pdev)
{
    struct device* dev = &pdev->dev;
    struct device_node* node =  dev->of_node;
    int ret = 0;

    pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
    if (NULL == pdata) {
        hwlog_err("cannot allocate anc hs dev data\n");
        return -ENOMEM;
    }


    /* get mic->gnd control gpio */
    pdata->gpio_mic_gnd =  of_get_named_gpio(node, "gpios", 0);
    if (pdata->gpio_mic_gnd < 0) {
        hwlog_err("gpio_mic_gnd is unvalid!\n");
        return -ENOENT;
    }

    if (!gpio_is_valid(pdata->gpio_mic_gnd)) {
        hwlog_err("gpio is unvalid!\n");
        return -ENOENT;
    }

    /* applay for mic->gnd gpio */
    ret = gpio_request(pdata->gpio_mic_gnd, "gpio_mic_gnd");
    if (ret) {
        hwlog_err("error request GPIO for mic_gnd fail %d\n", ret);
        goto gpio_mic_gnd_err;
    }
    gpio_direction_output(pdata->gpio_mic_gnd, INVERT_HS_MIC_GND_DISCONNECT);

    /* load dts config for board difference */
    load_invert_hs_config(node);

    hwlog_info("invert_hs probe success!\n");

    return 0;


gpio_mic_gnd_err:
    gpio_free(pdata->gpio_mic_gnd);
    return ret;

}

static int invert_hs_remove(struct platform_device* pdev)
{
    if (pdata == NULL) {
        return 0;
    }

    gpio_free(pdata->gpio_mic_gnd);

    return 0;
}

static struct platform_driver invert_hs_driver =
{
    .driver = {
        .name   = "invert_hs",
        .owner  = THIS_MODULE,
        .of_match_table = invert_hs_of_match,
    },
    .probe  = invert_hs_probe,
    .remove = invert_hs_remove,
};

static int __init invert_hs_init(void)
{
    return platform_driver_register(&invert_hs_driver);
}

static void __exit invert_hs_exit(void)
{
    platform_driver_unregister(&invert_hs_driver);
}

device_initcall(invert_hs_init);
module_exit(invert_hs_exit);

MODULE_DESCRIPTION("invert headset driver");
MODULE_LICENSE("GPL");
