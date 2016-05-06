/*
  * hisi_pm_psci.c
  *
  * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License version 2 as
  * published by the Free Software Foundation.
  */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/irqchip/arm-gic.h>
#include <asm/proc-fns.h>
#include <asm/cacheflush.h>
#include <asm/psci.h>
#include <asm/atomic.h>
#include <asm/cputype.h>
#include <linux/cpu_pm.h>
#include <linux/arm-cci.h>
#include <linux/suspend.h>
#include <asm/suspend.h>
#include <linux/of_address.h>
#include <linux/hisi/hi6xxx-iomap.h>                   /* For IO_ADDRESS access */
#include "soc_ao_sctrl_interface.h"
#include "soc_acpu_sctrl_interface.h"
#include <linux/hisi/pm/pwrctrl_multi_memcfg.h>
#include <linux/dma-mapping.h>
#include <asm/tlbflush.h>
#include <linux/hisi/pm/pwrctrl_multi_def.h>
#include <linux/hisi/pm/hi6xxx-power-common.h>

#define ACPU_SUBSYS_POWERDOWN_FLAG 0xDEAD

static void __iomem *g_cci_base;
static void __iomem *g_acpu_sc_base_map;
static void __iomem *g_acpu_subsys_powerdown_flag_base;

static void hisi_set_acpu_subsys_powerdown_flag(void)
{
	writel(ACPU_SUBSYS_POWERDOWN_FLAG, g_acpu_subsys_powerdown_flag_base);
}

void hisi_clear_acpu_subsys_powerdown_flag(void)
{
	writel(0, g_acpu_subsys_powerdown_flag_base);
}

void coherent_init(void)
{
    /*CCI init*/
    /*使能各Master和Slave接口的 speculative fetch功能*/
    writel(0x180003, (g_cci_base + 0x90004));
    /*使能snoop/DVM/speculative fetch/terminate barrier功能*/
    writel(0x18, (g_cci_base + 0x90000));
}

/*fixme:Cluster上电完成，L2 Cache使能后，启动SMP前*/
void coherent_slave_port_config(void)
{
    /*unsigned int reg_val = 0;*/

    /*CCI slave port config*/ /*S3和S4都需要配置*/
    /*1 设置Latency目标为128个周期*/
    writel(0x500050, (g_cci_base + 0x94130));
    writel(0x500050, (g_cci_base + 0x95130));

    /*2 设置每256个周期Qos增加1*/
    writel(0x30003, (g_cci_base + 0x94134));
    writel(0x30003, (g_cci_base + 0x95134));

    /*3 设置ACPU最低优先级为1，最高优先级为6*/
    writel(0x6010601, (g_cci_base + 0x94138));
    writel(0x6010601, (g_cci_base + 0x95138));

    /*4 使能Qos*/
    writel(0x3, (g_cci_base + 0x9410c));
    writel(0x3, (g_cci_base + 0x9510c));

    return;
}

static int hi6xxx_pm_enter(suspend_state_t state)
{
	//volatile int wait_loop = 600000;

	pr_info("%s ++\n", __func__);

	//while(wait_loop >= 0)
	//	wait_loop--;
	cpu_pm_enter();
/*
	setup_mm_for_reboot();
	gic_cpu_if_down();
	hisi_cluster_exit_coherence(0);
*/
	hisi_set_acpu_subsys_powerdown_flag();
	cpu_suspend(3);
	hisi_clear_acpu_subsys_powerdown_flag();
	//coherent_init();
	//coherent_slave_port_config();
	cpu_pm_exit();

    g_pwcAcpuWakeFlagIcc = 1;
    g_pwcAcpuWakeFlagRfile = 1;

	pr_info("%s --\n", __func__);

	pwrctrl_mcu_debug_info_show();
	pwrctrl_ccpu_debug_info_show();

	return 0;
}

static const struct platform_suspend_ops hi6xxx_pm_ops = {
	.enter		= hi6xxx_pm_enter,
	.valid		= suspend_valid_only_mem,
};

static __init int addr_init(void)
{
	g_cci_base = (void __iomem *)ioremap(SOC_ACPU_CCI_BASE_ADDR+0x90000,SZ_128K) - 0x90000;
	printk(KERN_INFO"%s g_cci_base:0x%p.\n", __FUNCTION__, g_cci_base);

	g_acpu_sc_base_map = (void __iomem *)HISI_VA_ADDRESS(SOC_ACPU_SCTRL_BASE_ADDR);
	printk(KERN_INFO"%s g_acpu_sc_base_map:0x%p.\n", __FUNCTION__, g_acpu_sc_base_map);

	g_acpu_subsys_powerdown_flag_base = (void __iomem *)HISI_VA_ADDRESS(ACPU_SUBSYS_POWERDOWN_FLAGS_ADDR);
	printk(KERN_INFO"%s acpu subsys power flag addr:0x%p.\n", __FUNCTION__, g_acpu_subsys_powerdown_flag_base);
#if 0
	writel( PWRCTRL_ACPU_ASM_CODE_BASE >> 2, SOC_ACPU_SCTRL_ACPU_SC_CPU0_RVBARADDR_ADDR((unsigned long)g_acpu_sc_base_map)); /*cluster 0 cpu 0*/
	writel( PWRCTRL_ACPU_ASM_CODE_BASE >> 2, SOC_ACPU_SCTRL_ACPU_SC_CPU1_RVBARADDR_ADDR((unsigned long)g_acpu_sc_base_map)); /*cluster 0 cpu 1*/
	writel( PWRCTRL_ACPU_ASM_CODE_BASE >> 2, SOC_ACPU_SCTRL_ACPU_SC_CPU2_RVBARADDR_ADDR((unsigned long)g_acpu_sc_base_map)); /*cluster 0 cpu 2*/
	writel( PWRCTRL_ACPU_ASM_CODE_BASE >> 2, SOC_ACPU_SCTRL_ACPU_SC_CPU3_RVBARADDR_ADDR((unsigned long)g_acpu_sc_base_map)); /*cluster 0 cpu 3*/
	writel( PWRCTRL_ACPU_ASM_CODE_BASE >> 2, SOC_ACPU_SCTRL_ACPU_SC_CPU4_RVBARADDR_ADDR((unsigned long)g_acpu_sc_base_map)); /*cluster 1 cpu 0*/
	writel( PWRCTRL_ACPU_ASM_CODE_BASE >> 2, SOC_ACPU_SCTRL_ACPU_SC_CPU5_RVBARADDR_ADDR((unsigned long)g_acpu_sc_base_map)); /*cluster 1 cpu 1*/
	writel( PWRCTRL_ACPU_ASM_CODE_BASE >> 2, SOC_ACPU_SCTRL_ACPU_SC_CPU6_RVBARADDR_ADDR((unsigned long)g_acpu_sc_base_map)); /*cluster 1 cpu 2*/
	writel( PWRCTRL_ACPU_ASM_CODE_BASE >> 2, SOC_ACPU_SCTRL_ACPU_SC_CPU7_RVBARADDR_ADDR((unsigned long)g_acpu_sc_base_map)); /*cluster 1 cpu 3*/
#endif
	return 0;
}

int  dt_insmod_pm_asleep(void)
{
	struct device_node *root = NULL;
	const char *out_string;


    root = of_find_compatible_node(NULL, NULL, "hisilicon,hi6xxxx-pm-asleep");
    if (!root)
    {
        pr_err("%s of_find_compatible_node failed\n",__func__);
        return -1;
    }

	if(of_property_read_string(root,"status",&out_string))
	{
		pr_err("%s of_property_read_string failed\n",__func__);
		return -1;
	}

	if(0 == strcmp("ok",out_string))
	{
		pr_info("%s\n",__func__);
		return 0;
	}

	return -1;

}


static __init int hi6xxx_pm_drvinit(void)
{
	if(dt_insmod_pm_asleep())return 0;

	addr_init();

	suspend_set_ops(&hi6xxx_pm_ops);

	return 0;
}

arch_initcall(hi6xxx_pm_drvinit);
/*early_initcall(hi6xxx_pm_drvinit);*/
