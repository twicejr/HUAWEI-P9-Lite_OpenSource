
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/miscdevice.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#include <linux/input.h>
#include <huawei_platform/log/hw_log.h>

#include "earpiece_pa.h"

#define HWLOG_TAG earpiece_pa
HWLOG_REGIST();

struct ear_pa_data 
{
    int gpio_handle;
};

static struct ear_pa_data* g_pdata = NULL;

static int earpa_open(struct inode* inode, struct file* file)
{
    return 0;
}

static int earpa_release(struct inode* inode, struct file* file)
{
    return 0;
}

static long earpa_ioctl(struct file* file, unsigned int cmd, unsigned long argc)
{
    long ret = 0;

    switch(cmd) {
        case EAR_PA_OPEN :
            gpio_set_value(g_pdata->gpio_handle, 1);
            hwlog_debug("%s, open earpice pa", __FUNCTION__);
            break;

        case EAR_PA_CLOSE :
            gpio_set_value(g_pdata->gpio_handle, 0);
            hwlog_debug("%s, close earpice pa", __FUNCTION__);
            break;

        default:
            ret = (long)(-1);
            hwlog_err("%s, invalid cmd", __FUNCTION__);
            break;
        }

    return ret;
}

static const struct file_operations earpa_fops = {
    .owner          = THIS_MODULE,
    .open           = earpa_open,
    .release        = earpa_release,
    .unlocked_ioctl = earpa_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl   = earpa_ioctl,
#endif
};

static struct miscdevice earpa_device = {
    .minor      = MISC_DYNAMIC_MINOR,
    .name       = "ear_pa",
    .fops       = &earpa_fops,
};

static const struct of_device_id earpa_table[] = {
    {
        .compatible = "huawei,earpicePA",
    },
    {},
};

MODULE_DEVICE_TABLE(of, earpa_table);

static int earpa_probe(struct platform_device* pdev)
{
    int ret = 0;
    struct device* dev = &pdev->dev;
    struct device_node* node =  dev->of_node;
    hwlog_debug("%s, in function", __FUNCTION__);

    g_pdata = kzalloc(sizeof(struct ear_pa_data), GFP_KERNEL);
    if (NULL == g_pdata) {
        hwlog_err("malloc earpice pa memory fail!");
        return -ENOMEM;
    }

    //get gpio handle
    g_pdata->gpio_handle = of_get_named_gpio(node, "gpio", 0);
    if (g_pdata->gpio_handle < 0) {
        hwlog_err("earpice gpio is unvalid!");
        return -ENOENT;
    }
    //gpio is valid or not
    if (!gpio_is_valid(g_pdata->gpio_handle)) {
        hwlog_err("earpice gpio is unvalid!");
        return -ENOENT;
    }

    ret = gpio_request(g_pdata->gpio_handle, "ear_pa_gpio");
    if (ret) {
        hwlog_err("request earpice pa gpio error!");
        goto gpio_error;
    }
    gpio_direction_output(g_pdata->gpio_handle, 0);

    ret = misc_register(&earpa_device);
    if (ret) {
        hwlog_err("register earpice pa device error!");
    }

    hwlog_debug("%s, out function", __FUNCTION__);
    return ret;

gpio_error:
    gpio_free(g_pdata->gpio_handle);
        
    return ret;
}

static int earpa_remove(struct platform_device* pdev)
{
    gpio_free(g_pdata->gpio_handle);
    misc_deregister(&earpa_device);

    return 0;
}

static struct platform_driver earpa_driver = {
    .driver = 
    {
        .name  = "earpa_driver",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(earpa_table),
    },
    .probe  = earpa_probe,
    .remove = earpa_remove,
};

int __init earpa_init(void)
{
    int ret = 0;
    hwlog_info("earpa init \n");

    ret = platform_driver_register(&earpa_driver);
    if (0 != ret) {
        hwlog_err("earpa driver register fail , ERROR is %d\n", ret);
    }

    return ret;
}

void __exit earpa_exit(void)
{
    platform_driver_unregister(&earpa_driver);
}

module_init(earpa_init);
module_exit(earpa_exit);

MODULE_DESCRIPTION("earpice pa driver");
MODULE_LICENSE("GPL");
