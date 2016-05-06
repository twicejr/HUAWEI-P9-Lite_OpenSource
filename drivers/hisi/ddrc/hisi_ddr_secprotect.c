/*
 * Hisilicon DDR TEST driver (master only).
 *
 * Copyright (c) 2012-2013 Linaro Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/pm.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/of.h>
#include <linux/mutex.h>

#include "hisi_ddr_secprotect.h"
#include <global_ddr_map.h>
#include <linux/hisi/rdr_pub.h>
#include <linux/hisi/util.h>

u64 *g_dmss_intr_fiq;

void fiq_print_src(u64 intrsrc)
{
	unsigned int intr = intrsrc & 0xFF;

	/* check with FIQ number */
	if (IRQ_WDT_INTR_FIQ == intr) {
		printk(KERN_ERR "fiq triggered by: Watchdog\n");
	} else if (IRQ_DMSS_INTR_FIQ == intr) {
		printk(KERN_ERR "fiq triggered by: DMSS\n");
	} else {
		printk(KERN_ERR "fiq triggered by: Unknown, intr=0x%x\n", (unsigned int)intrsrc);
	}

}

void dmss_fiq_handler(void)
{
	if (NULL != g_dmss_intr_fiq ) {
		fiq_print_src(*g_dmss_intr_fiq);
	} else {
		printk(KERN_ERR "fiq_handler intr ptr is null,please see bl31 log.\n");
		rdr_syserr_process_for_ap(MODID_AP_S_DDRC_SEC, 0, 0);
	}

	if ((NULL != g_dmss_intr_fiq )&&((u64)(DMSS_INTR_FIQ_FLAG|IRQ_DMSS_INTR_FIQ) == (*g_dmss_intr_fiq))) {
		printk("dmss_fiq_handler\n");
		printk("dmss intr happened. please see bl31 log.\n");

		/*rdr reboot  because of DDR_SEC*/
		rdr_syserr_process_for_ap(MODID_AP_S_DDRC_SEC, 0, 0);
	}
}

static int hisi_ddr_secprotect_probe(struct platform_device *pdev)
{
	g_dmss_intr_fiq = ioremap_nocache(HISI_SUB_RESERVED_BL31_SHARE_MEM_PHYMEM_BASE, 8);
	if (NULL == g_dmss_intr_fiq) {
		printk(" ddr ioremap_nocache fail\n");
		return -ENOMEM;
	}
	return 0;
}

static int hisi_ddr_secprotect_remove(struct platform_device *pdev)
{
	if (g_dmss_intr_fiq)
	{
		iounmap(g_dmss_intr_fiq);
	}
	g_dmss_intr_fiq = NULL;
	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id hs_ddr_of_match[] = {
	{ .compatible = "hisilicon,ddr_secprotect", },
	{},
};
MODULE_DEVICE_TABLE(of, hs_ddr_of_match);
#endif

static struct platform_driver hisi_ddr_secprotect_driver = {
	.probe		= hisi_ddr_secprotect_probe,
	.remove		= hisi_ddr_secprotect_remove,
	.driver		= {
		.name	= "ddr_secprotect",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(hs_ddr_of_match),
	},
};
module_platform_driver(hisi_ddr_secprotect_driver);

MODULE_DESCRIPTION("hisi ddr secprotect driver");
MODULE_ALIAS("hisi ddr_secprotect module");
MODULE_LICENSE("GPL");
