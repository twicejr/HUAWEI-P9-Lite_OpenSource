#include <linux/device.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <huawei_platform/log/hw_log.h>

#ifdef CONFIG_LLT_TEST
#include "vio_static_llt.h"
#endif
#define DEVICE_NAME "vio"
#define DTS_WIFI_NAME "hisilicon,bcm_wifi"
#define SET_VIO    1
#define HWLOG_TAG       vio

int gpio_vio;

HWLOG_REGIST();

static int vio_dev_ioctl(struct file *filp, int cmd, int arg)
{
    int ret = 0;
    hwlog_info(": vio_dev_ioctl in\n");
    ret = gpio_request(gpio_vio, NULL);

	if (ret < 0) {
        hwlog_info(": gpio_request failed, ret=%d\n", ret);
        return ret;
    }

    gpio_direction_output(gpio_vio, 0);

    switch(arg) {
        case 1:
            gpio_set_value(gpio_vio, 1);
            hwlog_info(": %d %d\n", cmd, arg);
            break;
        case 0:
            gpio_set_value(gpio_vio, 0);
            hwlog_info(": %d %d\n", cmd, arg);
            break;
        default:
            hwlog_info(": invalid value, %d %d\n", cmd, arg);
            return -EINVAL;
    }

    gpio_free(gpio_vio);
    return 0;
}

static struct file_operations vio_dev_fops = {
    .owner             = THIS_MODULE,
    .unlocked_ioctl    = vio_dev_ioctl,
};

static struct miscdevice vio_dev = {
    .minor           = MISC_DYNAMIC_MINOR,
    .name            = DEVICE_NAME,
    .fops            = &vio_dev_fops,
};

static int __init vio_dev_init(void)
{
    int ret;
    struct device_node *np;

    np = of_find_compatible_node(NULL, NULL, DTS_WIFI_NAME);	// should be the same as dts node compatible property
    if (np == NULL) {
        hwlog_err("Unable to find dts wifi.\n");
        return -ENOENT;
    }

    gpio_vio = of_get_named_gpio(np, "wlan_enable,gpio_vio", 0);
    hwlog_err("vio gpio number %d.\n", gpio_vio);
	if (gpio_vio<0) {
        hwlog_err("Get vio gpio number failed.\n");
        return -1;
    }

    ret = misc_register(&vio_dev);
    return ret;
}

static void __exit vio_dev_exit(void)
{
    misc_deregister(&vio_dev);
}

#ifdef CONFIG_LLT_TEST
#include "vio_static_llt.c"
#endif
module_init(vio_dev_init);
module_exit(vio_dev_exit);
