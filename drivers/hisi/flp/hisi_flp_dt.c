/*
 * hisi flp dt driver.
 *
 * Copyright (C) 2015 huawei Ltd.
 * Author: lijiangxiong<lijiangxiong@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/of.h>
#include <linux/pm.h>
#include <linux/platform_device.h>

extern int  hisi_flp_register(void);
extern int  hisi_flp_unregister(void);
extern int  hisi_softtimer_init (struct platform_device *pdev);
extern void hisi_softtimer_uninit(void);
extern void flp_port_resume(void);

static int hisi_flp_pm_suspend(struct device *dev)
{
    printk(KERN_ERR "%s %d: \n", __func__, __LINE__);

    return 0;
}

static int hisi_flp_pm_resume(struct device *dev)
{
    printk(KERN_ERR "%s %d: \n", __func__, __LINE__);
    flp_port_resume();
    return 0;
}


static int generic_flp_probe(struct platform_device *pdev)
{
    printk(KERN_ERR "generic_flp_probe \n");
    hisi_softtimer_init(pdev);
    return hisi_flp_register();
}

static int generic_flp_remove(struct platform_device *pdev)
{
    printk(KERN_ERR "%s %d: \n", __func__, __LINE__);
    hisi_softtimer_uninit();
    hisi_flp_unregister();
    return 0;
}
static const struct of_device_id generic_flp[] = {
    { .compatible = "hisilicon,flp-common" },
    {},
};

struct dev_pm_ops hisi_flp_pm_ops = {
#ifdef  CONFIG_PM_SLEEP
    .suspend = hisi_flp_pm_suspend ,
    .resume  = hisi_flp_pm_resume ,
#endif
};

MODULE_DEVICE_TABLE(of, generic_flp);

static struct platform_driver generic_flp_platdrv = {
    .driver = {
        .name	= "hisi-flp",
        .owner	= THIS_MODULE,
        .of_match_table = of_match_ptr(generic_flp),
        .pm = &hisi_flp_pm_ops,
    },
    .probe		= generic_flp_probe,
    .remove     = generic_flp_remove,
};

module_platform_driver(generic_flp_platdrv);

MODULE_AUTHOR(" hisi<hisi@huawei.com>");
MODULE_DESCRIPTION("Generic huawei flp driver via DT");
MODULE_LICENSE("GPL");

