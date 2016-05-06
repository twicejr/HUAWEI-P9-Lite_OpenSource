/*
 *  linux/arch/arm/mach-k3v2/dev_watchdog.c
 *
 * balong watchdog platform device declaration
 *
 * Copyright (C) 2012 Hisilicon, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <linux/platform_device.h>
#include <linux/io.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <linux/init.h>
#include <soc_irqs.h>
#if defined(CHIP_BB_HI6210)
#else
#include <soc_sctrl_interface.h>
#endif
#include <soc_ao_sctrl_interface.h>
#include <mach/util.h>
#include <linux/hiwdt100_wdt.h>
#include <hsad/config_mgr.h>

/*hiwdt100 driver private data*/
static struct hiwdt100_wdt_platform_data plat_wdt_data = {
    .iobase = REG_BASE_WD0,
    .size = REG_WD0_IOSIZE,
    .irq = IRQ_WD0,
    .clk_name = "clk_watchdog0",
};

/* watchdog platform device definition*/
static struct platform_device plat_wdt_dev = {
	.name = "hiwdt100",
	.id = 0,
	.dev = {
		.platform_data = &plat_wdt_data,
	},
};

/*****************************************************************************
   defined in sctrl register nmanager,
   the 2 bits below must be set together to tak effect, mask indicate which bit to set
   so, no need to read->set->write sequence
*****************************************************************************/
#define WDT_RESET_DEVICE_CFG_BIT  0
#define WDT_RESET_DEVICE_MASK_BIT 16


static void __init sctrl_reset_mode_init(void)
{
/*改为报中断给mcu*/
	void __iomem *base = NULL;
	unsigned int val = 1;
	unsigned int val_org = 1;

	base = (void __iomem *)IO_ADDRESS(REG_BASE_SC_ON);
#if defined(CHIP_BB_HI6210)
	writel(BIT(SOC_AO_SCTRL_SC_INT_EN_SET_sc_int_en0_0awd_START)
	        | BIT(SOC_AO_SCTRL_SC_INT_EN_SET_sc_int_en0_1cm3wdg0_START),
	            SOC_AO_SCTRL_SC_INT_EN_SET_ADDR(base));

    val = readl(SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_ADDR(base));
    writel((val | BIT(SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_WatchDog0_START)),
            SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_ADDR(base));
#else
	writel(val, SOC_AO_SCTRL_SC_INT_EN0_ADDR(base));	
    val = readl(SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_ADDR(base));
    printk(KERN_INFO"sctrl_reset_mode_init, val1 = 0x%X\n", val);

    writel((val | (1 << 5)), SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_ADDR(base));
    val = readl(SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_ADDR(base));
    printk(KERN_INFO"sctrl_reset_mode_init, val1 = 0x%X\n", val);

    val_org = readl(SOC_AO_SCTRL_SC_SYS_CTRL1_ADDR(base));
    printk(KERN_INFO"sctrl_reset_mode_init, val_org = 0x%X\n", val_org);
    val_org = (~(1<<WDT_RESET_DEVICE_MASK_BIT)) & val_org;
    val = (~(1<<WDT_RESET_DEVICE_CFG_BIT)) & val_org;
    printk(KERN_INFO"sctrl_reset_mode_init, val_new = 0x%X\n", val);
    writel(val, SOC_AO_SCTRL_SC_SYS_CTRL1_ADDR(base));
#endif
	return;
}


static int __init plat_wdt_dev_init(void)
{
	int ret = 0;
	int watchdog_enable = 0;

	ret = get_hw_config_int("watchdog/watchdog_enable", &watchdog_enable, NULL);
	if (false == ret){
		printk(KERN_ERR"%s %d : fail to get watchdog/watchdog_enable %d \r\n", __FUNCTION__, __LINE__, ret);
		watchdog_enable = 1;
	}

	/*watchdog is disable*/
	if (0 == watchdog_enable){
		return 0;
	}

	/*always success*/
	sctrl_reset_mode_init();

	ret = platform_device_register(&plat_wdt_dev);

	return ret;
};
arch_initcall(plat_wdt_dev_init);

MODULE_DESCRIPTION("Hisilicon Balong Platform Watchdog Device Declaration");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");

