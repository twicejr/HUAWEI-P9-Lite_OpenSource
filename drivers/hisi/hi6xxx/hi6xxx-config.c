
/*
 * hi6xxx soc misc driver, for soc configuration no included in other driver 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *
 * Copyright (C) 2014 Hisilicon Limited
 */

#include <linux/jiffies.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/stat.h>
#include <linux/reboot.h>
#include <linux/suspend.h>
#include <linux/cpu.h>
#include <linux/io.h>
#include <linux/interrupt.h>

/*soc interface*/
#include <soc_ao_sctrl_interface.h>
#include <soc_baseaddr_interface.h>
#include <soc_peri_sctrl_interface.h>
#include <soc_mddrc_dmc_interface.h>
#include <soc_baseaddr_interface.h>
#include <general_sram_map.h>
#include <linux/hisi/pm/pwrctrl_multi_memcfg.h>


static int hi6xxx_soc_cpu_notify(struct notifier_block *this,
					unsigned long action, void *hcpu)
{
	switch (action) {
	case CPU_UP_PREPARE:
        /*todo here*/
        break;
	case CPU_UP_PREPARE_FROZEN:
        /*todo here*/
		break;

#ifdef CONFIG_HOTPLUG_CPU
	case CPU_DYING:
        /*todo here*/
		break;
	case CPU_DYING_FROZEN:
        /*todo here*/
		break;
	case CPU_DEAD:
        /*todo here*/
		break;
	case CPU_DEAD_FROZEN:
        /*todo here*/
		break;
#endif

	default:
		break;
	}

	return NOTIFY_DONE;
}

static struct notifier_block hi6xxx_soc_cpu_notifier = {
	.notifier_call = hi6xxx_soc_cpu_notify,
};
static int hi6xxx_soc_pm_notify(struct notifier_block *this, unsigned long event, void *ptr)
{
	switch (event) {
	case PM_HIBERNATION_PREPARE:
        /*todo here*/
		break;

	case PM_POST_HIBERNATION:
        /*todo here*/
		break;

	case PM_SUSPEND_PREPARE:
        /*todo here*/
		break;

	case PM_POST_SUSPEND:
        /*todo here*/
		break;

	case PM_RESTORE_PREPARE:
        /*todo here*/
		break;

	case PM_POST_RESTORE:
        /*todo here*/
		break;

	default:
        /*todo here*/
		break;
	}

    /*todo here*/
    return NOTIFY_DONE;
}

static struct notifier_block hi6xxx_soc_pm_notifier = {
    .notifier_call = hi6xxx_soc_pm_notify,
    /*.priority = INT_MAX,*/ /*to change notifier's priority*/
};

static int hi6xxx_soc_reboot_notify(struct notifier_block *this,
            unsigned long code, void *reason)
{
	switch (code) {
	case SYS_RESTART:
        /*todo here*/
		break;
	case SYS_HALT:
        /*todo here*/
		break;
	case SYS_POWER_OFF:
        /*todo here*/
		break;
	default:
        /*todo here*/
        break;
	}

    return NOTIFY_DONE;
}

static struct notifier_block hi6xxx_soc_reboot_notifier = {
    .notifier_call = hi6xxx_soc_reboot_notify,
    /*.priority = INT_MAX,*/ /*to change notifier's priority*/
};

static void __init hi6xxx_soc_config_watchdog_mode(void)
{
    void __iomem *addr = NULL;

    addr = ioremap(SOC_AO_SCTRL_BASE_ADDR, SZ_8K);
    if (!addr){
        printk(KERN_ERR "%s : failed to ioremap AO SCTRL \r\n", __FUNCTION__);
        return;
    }

    /*now, not reboot system when acpu watchdog timeout*/
    writel( (0x1<<16)|(0x0<<0) , SOC_AO_SCTRL_SC_SYS_CTRL1_ADDR(addr));

    iounmap(addr);

    return;
}

static void __init hi6xxx_soc_config_pclk_reset(void)
{
    void __iomem *addr = NULL;
    
    addr = ioremap(SOC_PERI_SCTRL_BASE_ADDR, SZ_4K);
    if (!addr){
        printk(KERN_ERR "%s : failed to ioremap PERI SCTRL \r\n", __FUNCTION__);
        return;
    }

    /* UART1 disable reset  and set pclk */
    writel(0x1<<5, SOC_PERI_SCTRL_SC_PERIPH_RSTDIS3_ADDR(addr));
    writel(0x1<<5, SOC_PERI_SCTRL_SC_PERIPH_CLKEN3_ADDR(addr));

    /* UART2 disable reset  and set pclk */
    writel(0x1<<6, SOC_PERI_SCTRL_SC_PERIPH_RSTDIS3_ADDR(addr));
    writel(0x1<<6, SOC_PERI_SCTRL_SC_PERIPH_CLKEN3_ADDR(addr));

    /* UART3 disable reset  and set pclk */
    writel(0x1<<7, SOC_PERI_SCTRL_SC_PERIPH_RSTDIS3_ADDR(addr));
    writel(0x1<<7, SOC_PERI_SCTRL_SC_PERIPH_CLKEN3_ADDR(addr));

    /* UART4 disable reset  and set pclk */
    writel(0x1<<8, SOC_PERI_SCTRL_SC_PERIPH_RSTDIS3_ADDR(addr));
    writel(0x1<<8, SOC_PERI_SCTRL_SC_PERIPH_CLKEN3_ADDR(addr));

    iounmap(addr);

    return;
}

static int __init hi6xxx_soc_config_probe(struct platform_device *pdev)
{
    int err;

    hi6xxx_soc_config_watchdog_mode();

    err = register_reboot_notifier(&hi6xxx_soc_reboot_notifier);
    if (err){
        printk(KERN_ERR "failed to register hi6xxx soc reboot notifier !\r\n");
    }

    err = register_pm_notifier(&hi6xxx_soc_pm_notifier);
    if (err){
        printk(KERN_ERR "failed to register hi6xxx soc pm notifier !\r\n");
    }

    err = register_cpu_notifier(&hi6xxx_soc_cpu_notifier);
    if (err){
        printk(KERN_ERR "failed to register hi6xxx soc cpu notifier !\r\n");
    }

    return 0;
}

static struct of_device_id hi6xxx_soc_config_of_match[] = {
	{
		.compatible = "hisilicon,hi6xxx-soc-config",
		.data = NULL,
	},
	{}
};

static struct platform_driver hi6xxx_soc_config_driver = {
	.probe = hi6xxx_soc_config_probe,
	.driver = {
		.name = "hi6xxx-soc-config",
		.of_match_table = hi6xxx_soc_config_of_match,
	},
};

static int __init hi6xxx_soc_pre_config(void)
{
    /*config MUST be done before devices probe*/

    hi6xxx_soc_config_pclk_reset();

    return 0;
}

static int __init hi6xxx_soc_config_init(void)
{
    hi6xxx_soc_pre_config();

    return platform_driver_register(&hi6xxx_soc_config_driver);
}
postcore_initcall(hi6xxx_soc_config_init);

#ifdef CONFIG_ARM64
#ifdef CONFIG_SPARSE_IRQ
#define NR_IRQS_LEGACY_HI6XXXX 16

int __init arch_probe_nr_irqs(void)
{
	return NR_IRQS_LEGACY_HI6XXXX;
}
#endif
#endif

