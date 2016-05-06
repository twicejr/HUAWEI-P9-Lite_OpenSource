/*
 * Hisilicon's hi6210 SFT board support
 *
 * Copyright (c) 2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/clk-provider.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/smp.h>
#include <linux/memblock.h>
#include <linux/irqchip.h>
#include <linux/cache.h>
#include <asm/hardware/arm_timer.h>
#include <asm/arch_timer.h>
#include <asm/hardware/timer-sp.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/time.h>
#include <asm/smp_plat.h>
#include <asm/smp_twd.h>
#include <asm/proc-fns.h>
#include <asm/psci.h>
#include <asm/sched_clock.h>
#include <asm/cacheflush.h>
#include <linux/of_device.h>
#include <global_ddr_map.h>
#include <linux/mmzone.h>

#ifdef CONFIG_MCPM
#include <asm/mcpm.h>
#endif
#include <linux/hisi/hi6xxx-iomap.h>                   /* For IO_ADDRESS access */
/*#include "board_diff.h"*/
#include "soc_ao_sctrl_interface.h"
#include <soc_baseaddr_interface.h>
#include <soc_peri_sctrl_interface.h>
#include <soc_mddrc_dmc_interface.h> /* config ddr autorefresh in sram_reboot() */
#include <linux/hisi/pm/pwrctrl_multi_memcfg.h>    /* config ddr autorefresh in sram_reboot() */


/*auxdata table for lookup the preferred Linux name of matching device nodes*/
static const struct of_dev_auxdata of_hi6xxx_lookup_table[] = {
    {.compatible = "hisilicon,ddr_devfreq",
     .name = "ddrfreq",
     .platform_data = NULL,
    },
    {.compatible = "hisilicon,ddr_devfreq_up_threshold",
     .name = "ddrfreq_up_threshold",
     .platform_data = NULL,
    },
    {.compatible = "hisilicon,gpu_devfreq",
     .name = "gpufreq",
     .platform_data = NULL,
    },
    {}
};


void __init hi6210_map_common_io(void);

static void __init acore_timer_enable(void)
{
	struct device_node *node;
	void __iomem *sctrl_base;

	node = of_find_compatible_node(NULL, NULL,"hisilicon,aosctrl");
	if (node)
		sctrl_base = of_iomap(node, 0);
	else {
		printk("HI6210sft dual timer enable failed!\n");
		return;
	}

	/*For timer0~timer7*/
	writel(0xFFFF0000, SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(sctrl_base));
}
extern int hisi_local_timer_register(void);
static void __init hisi_timer_init(void)
{
	acore_timer_enable();

	of_clk_init(NULL);

	clocksource_of_init();

	hisi_local_timer_register();
}
/*extern int early_hiwdt100_wdt_init(void);*/
static void __init hisi_init(void)
{
	of_platform_populate(NULL, of_default_bus_match_table, of_hi6xxx_lookup_table, NULL);

	/*if (early_hiwdt100_wdt_init()) {
		pr_err("%s: failed to initial wdt\n", __FUNCTION__);
	}*/
}


bool __init hisi_smp_init_ops(void)
{
#ifdef CONFIG_MCPM
	mcpm_smp_set_ops();
	return true;
#endif
	return false;
}

static const char *hisi_compat[] __initdata = {
	"hisilicon,hi6210",
	NULL,
};

static int __init free_fastboot_memory(void)
{
	u32 size = FASTBOOT_SYS_MEM_SIZE + FASTBOOT_DUMP_LOG_SIZE;
	u32 alignment = PAGE_SIZE << max(MAX_ORDER - 1, pageblock_order);
	phys_addr_t addr = FASTBOOT_SYS_MEM_ADDR;
	int pageblocks = size >> (PAGE_SHIFT + pageblock_order);
	int i;

	if((size&(alignment - 1)) || (addr&(alignment - 1))) {
		printk(KERN_EMERG "%s error: the address or size is not aligned to 0x%x\n", __FUNCTION__, alignment);
	}

	for(i = 0; i < pageblocks; i++) {
		init_cma_reserved_pageblock(phys_to_page(addr));
		addr += (PAGE_SIZE < pageblock_order);
	}

	return 0;
}
late_initcall(free_fastboot_memory);

DT_MACHINE_START(HS_DT, "hi6210sft")
	.dt_compat		= hisi_compat,
	.smp_init		= smp_init_ops(hisi_smp_init_ops),
	.map_io			= hi6210_map_common_io,
	.init_irq		= irqchip_init,
	.init_time		= hisi_timer_init,
	.init_machine       = hisi_init,
MACHINE_END
