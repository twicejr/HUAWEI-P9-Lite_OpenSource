/*
 * Copyright (C) 2012-2015 HUAWEI, Inc.
 * Author: HUAWEI, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <huawei_platform/log/hw_log.h>
#include <../cpu_buck.h>

#define HWLOG_TAG lp8758
#define LP8758_REG_SIZE 2
#define LP8758_PMU_TYPE "0004_"
HWLOG_REGIST();

static char lp8758_reg_val[LP8758_REG_SIZE];
static struct cpu_buck_info lp8758_error_array[] =
{
    /*0x18*/
    {LP8758_INT_BUCK3, 0x80, 0, "LP8758_INT_BUCK3"},
    {LP8758_INT_BUCK2, 0x40, 0, "LP8758_INT_BUCK2"},
    {LP8758_INT_BUCK1, 0x20, 0, "LP8758_INT_BUCK1"},
    {LP8758_INT_BUCK0, 0x10, 0, "LP8758_INT_BUCK0"},
    {LP8758_TDIE_SD, 0x08, 0, "LP8758_TDIE_SD"},
    {LP8758_TDIE_WARN, 0x04, 0, "LP8758_TDIE_WARN"},
    /*0x19*/
    {LP8758_BUCK1_ILIM_INT, 0x10, 1, "LP8758_BUCK1_ILIM_INT"},
    {LP8758_BUCK0_PG_INT, 0x04, 1, "LP8758_BUCK0_PG_INT"},
    {LP8758_BUCK0_SC_INT, 0x02, 1, "LP8758_BUCK0_SC_INT"},
    {LP8758_BUCK0_ILIM_INT, 0x01, 1, "LP8758_BUCK0_ILIM_INT"},
};

static int __init early_parse_cpu_buck_reg_cmdline(char * p)
{
    char* start;
    int i;
    if (p)
        return 0;
    start = strstr(p, LP8758_PMU_TYPE);
    if (NULL == start)
    {
        hwlog_info("can not find lp8758 regs\n");
        return 0;
    }
    str_to_reg(start+5, lp8758_reg_val, LP8758_REG_SIZE);
    for (i = 0; i < LP8758_REG_SIZE; ++i)
    {
        hwlog_info("reg[%d] = 0x%x\n", i, lp8758_reg_val[i]);
    }
    return 0;
}
early_param("cpu_buck_reg", early_parse_cpu_buck_reg_cmdline);
static struct cpu_buck_sample lp8758;

static int lp8758_probe(struct platform_device *pdev)
{
    struct device_node* np;

    np = pdev->dev.of_node;
    if (NULL == np)
    {
        hwlog_err("np is NULL\n");
        return -1;
    }
    lp8758.cbs = NULL;
    lp8758.cbi = lp8758_error_array;
    lp8758.reg = lp8758_reg_val;
    lp8758.info_size = sizeof(lp8758_error_array) / sizeof(struct cpu_buck_info);

    cpu_buck_register(&lp8758);
    hwlog_info("register success\n");
    return 0;
}

static struct of_device_id lp8758_match_table[] =
{
    {
        .compatible = "huawei,lp8758",
        .data = NULL,
    },
    {
    },
};
static struct platform_driver lp8758_driver = {
    .probe = lp8758_probe,
    .driver = {
        .name = "huawei,lp8758",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(lp8758_match_table),
    },
};

static int __init lp8758_init(void)
{
    return platform_driver_register(&lp8758_driver);
}

fs_initcall_sync(lp8758_init);

static void __exit lp8758_exit(void)
{
    platform_driver_unregister(&lp8758_driver);
}

module_exit(lp8758_exit);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lp8758");
MODULE_AUTHOR("HUAWEI Inc");
