/*
 * pwrio_hifi.c -- invert headset driver
 *
 * Copyright (c) 2015 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/notifier.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/kthread.h>
#include <linux/clk.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/ioctl.h>
#include <linux/io.h>
#include <linux/of_gpio.h>
#include "tps65133.h"

#define LOG_TAG "TPS65133"
#define TPS65133_ON   (1)
#define TPS65133_OFF   (0)

#define CODEC_GPIO_BASE                      (224)

static struct tps65133_platform_data *pdata = NULL;
static struct mutex tps65133_lock;
enum tps65133_gpio_type
{
    TPS65133_GPIO_SOC           = 0,
    TPS65133_GPIO_CODEC         = 1,
};

 int tps65133_gpio_get_value(void)
{
    if(pdata == NULL) {
         return -EFAULT;
     }
    if (!gpio_is_valid(pdata->gpio_tps65133_en)){
        pr_err("gpio is unvalid!\n");
        return -EINVAL;
    }
    if(pdata->gpio_type == TPS65133_GPIO_CODEC){
       return gpio_get_value_cansleep(pdata->gpio_tps65133_en);
    } else {
        return gpio_get_value(pdata->gpio_tps65133_en);
    }

}

int  tps65133_gpio_set_value( int value)
{
    if(pdata == NULL){
        return -EFAULT;
     }
    if (!gpio_is_valid(pdata->gpio_tps65133_en)){
         pr_err("gpio is unvalid!\n");
         return -EINVAL;
    }
    if((value!=TPS65133_ON) && (value!=TPS65133_OFF)){
        return -EINVAL;
    }

    if(pdata->gpio_type == TPS65133_GPIO_CODEC){
        gpio_set_value_cansleep(pdata->gpio_tps65133_en, value);
    } else{
        gpio_set_value(pdata->gpio_tps65133_en, value);
    }
    return 0;
}

static const struct of_device_id tps65133_of_match[] =
{
    {
        .compatible = "huawei,tps65133_hs_pa",
    },
    { },
};
MODULE_DEVICE_TABLE(of, tps65133_of_match);
static ssize_t tps65133_info_show(struct device* dev,
                                struct device_attribute* attr, char* buf)
{
    return snprintf(buf, 32, "%d\n", tps65133_gpio_get_value());
}
static ssize_t tps65133_info_store(struct device* dev,
                                      struct device_attribute* attr,
                                      const char* buf, size_t count)
{
    int ret, value;
    ret = kstrtoint(buf, 10, &value);
    if (ret){
        pr_err("%s : convert to int type failed\n", __FUNCTION__);
        return ret;
    }
    if (value){
         tps65133_gpio_set_value(TPS65133_ON);
    }
    else{
       tps65133_gpio_set_value(TPS65133_OFF);
    }
    return count;
}
static DEVICE_ATTR(tps65133, 0664, tps65133_info_show,
                   tps65133_info_store);
static struct attribute* tps65133_attributes[] =
{
    &dev_attr_tps65133.attr,
    NULL
};
static const struct attribute_group tps65133_attr_group =
{
    .attrs =tps65133_attributes,
};

static int tps65133_open(struct inode *inode, struct file *file)
{
    return 0;
}
static int tps65133_release(struct inode *inode, struct file *file)
{
    return 0;
}

static long tps65133_ioctl_do_ioctl(struct file *file,unsigned int cmd, void __user * arg,int compat_mode)
{
    int ret = 0;
    mutex_lock(&tps65133_lock);
    switch (cmd){
        case TPS65133_ENABLE:
            tps65133_gpio_set_value(TPS65133_ON);
            break;
        case TPS65133_DISABLE:
            tps65133_gpio_set_value(TPS65133_OFF);
            break;
        default:
            pr_err("%s: invalid command %d", __FUNCTION__, _IOC_NR(cmd));
            ret = -EINVAL;
            break;
        }
    mutex_unlock(&tps65133_lock);
    return ret;
}

static long tps65133_ioctl(struct file * file, unsigned int command, unsigned long arg)
{
    return tps65133_ioctl_do_ioctl(file, command, (void __user *)arg, 0);
}

#ifdef CONFIG_COMPAT
static long tps65133_ioctl_compat(struct file *file, unsigned int command, unsigned long arg)
{
    return tps65133_ioctl_do_ioctl(file, command, compat_ptr(arg), 1);
}
#else
#define tps65133_ioctl_compat    NULL
#endif
static const struct file_operations tps65133_fops = {
    .owner = THIS_MODULE,
    .open = tps65133_open,
    .release = tps65133_release,
    .unlocked_ioctl = tps65133_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl = tps65133_ioctl_compat,
#endif
 };
static struct miscdevice tps65133_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = TPS65133_NAME,
    .fops = &tps65133_fops,
 };

static int tps65133_probe(struct platform_device* pdev)
{
    struct device* dev = &pdev->dev;
    struct device_node* node;
    int ret = 0;
    pr_info("%s", __FUNCTION__);
    if(dev==NULL){
        pr_err("%s : dev is NULL\n", __FUNCTION__);
        return -ENOMEM;
    }
    node =  dev->of_node;
    if(node==NULL){
        pr_err("%s : node is NULL\n", __FUNCTION__);
        return -ENOMEM;
    }
    pdata = kzalloc(sizeof(struct tps65133_platform_data), GFP_KERNEL);
    if (NULL == pdata){
        pr_err("cannot allocate anc hs dev data\n");
        return -ENOMEM;
    }
    /* get mic->gnd control gpio */
     pdata->gpio_tps65133_en = of_get_named_gpio(node, "gpios", 0);

    if (pdata->gpio_tps65133_en < 0){
        pr_err("gpio_hifi_pwr is unvalid!\n");
        goto err_out;
    }

    if (!gpio_is_valid(pdata->gpio_tps65133_en)){
        pr_err("gpio is unvalid!\n");
        goto err_out;
    }
    /* applay for mic->gnd gpio */
    ret = gpio_request(pdata->gpio_tps65133_en, TPS65133_NAME);
    if (ret) {
        pr_err("error request GPIO for tps65133 fail %d\n", ret);
        goto err_out;
    }
    ret=gpio_direction_output(pdata->gpio_tps65133_en, 0);
    if (0 > ret){
         pr_err("%s: set gpio direction failed", __FUNCTION__);
         goto gpio_hifi_pwr_err;
   }

    /* check GPIO number for board difference */
    if(pdata->gpio_tps65133_en >= CODEC_GPIO_BASE)
    {
        pdata->gpio_type = TPS65133_GPIO_CODEC;
    }
    else
    {
        pdata->gpio_type = TPS65133_GPIO_SOC;
    }

    ret = misc_register(&tps65133_device);
    if(ret) {
         pr_err("%s: tps65133_device register failed", __FUNCTION__);
         goto gpio_hifi_pwr_err;
    }
    if((ret = sysfs_create_group(&dev->kobj, &tps65133_attr_group)) < 0){
         pr_err("failed to register sysfs\n");
      }
    return 0;
gpio_hifi_pwr_err:
    gpio_free(pdata->gpio_tps65133_en);
err_out:
     kfree(pdata);
    return ret;
}

static int tps65133_remove(struct platform_device *pdev)
{
   pr_info("%s", __FUNCTION__);
   gpio_free(pdata->gpio_tps65133_en);
   kfree(pdata);
   return 0;
}
static struct platform_driver tps65133_driver =
{
    .driver = {
    .name   =TPS65133_NAME,
    .owner  = THIS_MODULE,
    .of_match_table = tps65133_of_match,
    },
    .probe  = tps65133_probe,
    .remove = tps65133_remove,
};

static int __init tps65133_init(void)
{
    pr_info("%s:init", __FUNCTION__);
    mutex_init(&tps65133_lock);
    return platform_driver_register(&tps65133_driver);
}

static void __exit tps65133_exit(void)
{
    pr_info("%s:exit", __FUNCTION__);
    platform_driver_unregister(&tps65133_driver);

}

module_init(tps65133_init);
module_exit(tps65133_exit);
MODULE_DESCRIPTION("hifi power control");
MODULE_LICENSE("GPL");

