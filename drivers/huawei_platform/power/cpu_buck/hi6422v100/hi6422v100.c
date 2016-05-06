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

#define HWLOG_TAG hi6422v100
#define HI6422V100_REG_SIZE 3
#define HI6422V100_PMU_TYPE "0003_"
HWLOG_REGIST();

static char hi6422v100_reg_val[HI6422V100_REG_SIZE];
static struct cpu_buck_info hi6422v100_error_array[] =
{
    /*IRQ0*/
    {HI6422V100_VSYS_UV, 0x40, 0, "HI6422V100_VSYS_UV"},
    {HI6422V100_VSYS_OV, 0x20, 0, "HI6422V100_VSYS_OV"},
    {HI6422V100_OTMP_R, 0x10, 0, "HI6422V100_OTMP_R"},
    {HI6422V100_OTMP150_D10R, 0x08, 0, "HI6422V100_OTMP150_D10R"},
    {HI6422V100_VBAT2P6_F, 0x04, 0, "HI6422V100_VBAT2P6_F"},
    {HI6422V100_VBAT2P3_2D, 0x02, 0, "HI6422V100_VBAT2P3_2D"},
    /*OCP_IRQ0*/
    {HI6422V100_BUCK34_SCP, 0x40, 1, "HI6422V100_BUCK34_SCP"},
    {HI6422V100_BUCK012_SCP, 0x20, 1, "HI6422V100_BUCK012_SCP"},
    {HI6422V100_OCPBUCK4, 0x10, 1, "HI6422V100_OCPBUCK4"},
    {HI6422V100_OCPBUCK3, 0x08, 1, "HI6422V100_OCPBUCK3"},
    {HI6422V100_OCPBUCK2, 0x04, 1, "HI6422V100_OCPBUCK2"},
    {HI6422V100_OCPBUCK1, 0x02, 1, "HI6422V100_OCPBUCK1"},
    {HI6422V100_OCPBUCK0, 0x01, 1, "HI6422V100_OCPBUCK0"},
    /*OCP_IRQ1*/
    {VBAT_OCPBUCK4, 0x10, 2, "VBAT_OCPBUCK4"},
    {VBAT_OCPBUCK3, 0x08, 2, "VBAT_OCPBUCK3"},
    {VBAT_OCPBUCK2, 0x04, 2, "VBAT_OCPBUCK2"},
    {VBAT_OCPBUCK1, 0x02, 2, "VBAT_OCPBUCK1"},
    {VBAT_OCPBUCK0, 0x01, 2, "VBAT_OCPBUCK0"},
};

static int __init early_parse_cpu_buck_reg_cmdline(char * p)
{
    char* start;
    int i;
    if (p)
        return 0;
    start = strstr(p, HI6422V100_PMU_TYPE);
    if (NULL == start)
    {
        hwlog_info("can not find hi6422v100 regs\n");
        return 0;
    }
    str_to_reg(start+5, hi6422v100_reg_val, HI6422V100_REG_SIZE);
    for (i = 0; i < HI6422V100_REG_SIZE; ++i)
    {
        hwlog_info("reg[%d] = 0x%x\n", i, hi6422v100_reg_val[i]);
    }
    return 0;
}

early_param("cpu_buck_reg", early_parse_cpu_buck_reg_cmdline);
static struct cpu_buck_sample hi6422v100;

static int hi6422v100_probe(struct platform_device *pdev)
{
    struct device_node* np;

    np = pdev->dev.of_node;
    if (NULL == np)
    {
        hwlog_err("np is NULL\n");
        return -1;
    }
    hi6422v100.cbs = NULL;
    hi6422v100.cbi = hi6422v100_error_array;
    hi6422v100.reg = hi6422v100_reg_val;
    hi6422v100.info_size = sizeof(hi6422v100_error_array) / sizeof(struct cpu_buck_info);

    cpu_buck_register(&hi6422v100);
    hwlog_info("register success\n");
    return 0;
}

static struct of_device_id hi6422v100_match_table[] =
{
    {
        .compatible = "huawei,hi6422v100",
        .data = NULL,
    },
    {
    },
};

static struct platform_driver hi6422v100_driver = {
    .probe = hi6422v100_probe,
    .driver = {
        .name = "huawei,hi6422v100",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(hi6422v100_match_table),
    },
};

static int __init hi6422v100_init(void)
{
    return platform_driver_register(&hi6422v100_driver);
}

fs_initcall_sync(hi6422v100_init);

static void __exit hi6422v100_exit(void)
{
    platform_driver_unregister(&hi6422v100_driver);
}

module_exit(hi6422v100_exit);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hi6422v100");
MODULE_AUTHOR("HUAWEI Inc");
