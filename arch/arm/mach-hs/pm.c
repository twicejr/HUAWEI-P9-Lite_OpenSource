/*
 * Power Management suspend/resume routines for HiSilicon platform
 *
 * Copyright © 2011-2013 HiSilicon Technologies Co., Ltd.
 *              http://www.hisilicon.com
 * Copyright © 2012-2013 Linaro Ltd.
 *              http://www.linaro.org
 *
 * Author: Guodong Xu <guodong.xu@linaro.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 */

#define CONFIG_HSK3_RTC_WAKEUP
#define CONFIG_HSK3_CONSOLE_WORKAROUND

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pm.h>
#include <linux/suspend.h>
#include <linux/cpu.h>
#include <linux/notifier.h>
#include <linux/reboot.h>
#include <asm/memory.h>
#include <linux/delay.h>
#include <linux/suspend.h>
#include <asm/mach/time.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <linux/clk.h>
#include <asm/cacheflush.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/cpu_pm.h>
#include <asm/fncpy.h>
#include "core.h"
#include "hipm.h"
#ifdef CONFIG_HSK3_RTC_WAKEUP
#include <linux/irqchip/arm-gic.h>
#include <linux/irq.h>
#endif
#ifdef CONFIG_HSK3_CONSOLE_WORKAROUND
#include <linux/console.h>
#endif

/* resources in power management */
struct iomap_resource {
	struct resource *res;
	void __iomem *virt_addr;
};

struct pm_resources {
	struct iomap_resource pmu_spi;
	struct iomap_resource secram;
	struct iomap_resource pctrl;
	struct iomap_resource a9_per;
#ifdef CONFIG_HSK3_CONSOLE_WORKAROUND
	struct iomap_resource uart0;
	struct iomap_resource io;
#endif
};

struct pm_resources hs_pm_resources;
void __iomem *timer0_base_addr;
void __iomem *hs_secram_va_base;
void __iomem *hs_a9per_va_base;
void __iomem *hs_pctrl_va_base;
void __iomem *hs_pmuspi_va_base;

#ifdef CONFIG_HSK3_CONSOLE_WORKAROUND
static void __iomem *hs_uart0_va_base;
static void __iomem *hs_io_va_base;

/* re-init debug uart */
static void debuguart_reinit(void)
{
	void __iomem *usctrl_base = hs_sctrl_base;
	void __iomem *uuart_base  = hs_uart0_va_base;
	void __iomem *io_base = hs_io_va_base;
	unsigned int uregv = 0;

	/* Config necessary IOMG configuration */
	writel(0, (io_base + 0xF4));

	/* config necessary IOCG configuration */
	writel(0, (io_base + 0xA08));
	writel(0, (io_base + 0xA0C));

	/* disable clk */
	uregv = 0x10000;
	writel(uregv, (usctrl_base + 0x44));

	/* select 26MHz clock */
	uregv = (1 << 23);
	writel(uregv, (usctrl_base + 0x100));

	/* enable clk */
	uregv = 0x10000;
	writel(uregv, (usctrl_base + 0x40));

	/* disable recieve and send */
	uregv = 0x0;
	writel(uregv, (uuart_base + 0x30));

	/* enable FIFO */
	uregv = 0x70;
	writel(uregv, (uuart_base + 0x2c));

	/* set baudrate */
	uregv = 0xE;
	writel(uregv, (uuart_base + 0x24));

	uregv = 0x7;
	writel(uregv, (uuart_base + 0x28));

	/* clear buffer */
	uregv = readl(uuart_base);

	/* enable FIFO */
	uregv = 0x70;
	writel(uregv, (uuart_base + 0x2C));

	/* set FIFO depth */
	uregv = 0x10A;
	writel(uregv, (uuart_base + 0x34));

	uregv = 0x50;
	writel(uregv, (uuart_base + 0x38));

	/* enable uart trans */
	uregv = 0xF01;
	writel(uregv, (uuart_base + 0x30));
}
#endif /* CONFIG_HSK3_CONSOLE_WORKAROUND */

/* power-off GPIO pin handle */
static int pmu_power_off_handle;

/* system power off func */
static void hisik3_power_off(void)
{
	int ret;

	ret = gpio_request(pmu_power_off_handle, 0);
	if (ret != 0)
		pr_emerg("request PMU_POWER_OFF gpio error:%d\n", ret);

	/* clear HRST_REG */
	writel(0, PMU_HRST_REG);

	while (1) {
		pr_emerg("system power off now\n");

		gpio_direction_output(pmu_power_off_handle, 0);
		gpio_set_value(pmu_power_off_handle, 0);

		msleep(1000);
	}

	gpio_free(pmu_power_off_handle);
}

static int wrapper_hs_godpsleep(void)
{

	hilpm_cpu_godpsleep();

#ifdef CONFIG_HSK3_CONSOLE_WORKAROUND
	/* debuguart needs to be reinit when "no_console_suspend" is set.
	 */
	if (!console_suspend_enabled)
		debuguart_reinit();
#endif

	return 0;
}

static int hisik3_pm_enter(suspend_state_t state)
{
	void __iomem *addr;
	unsigned long flage = 0;

	pr_notice("[PM] Enter sleep, in %s()\n", __func__);

	switch (state) {
	case PM_SUSPEND_STANDBY:
	case PM_SUSPEND_MEM:
		break;
	default:
		return -EINVAL;
	}

	/* store master cpu resume addree into SCTRL */
	addr = (MASTER_SR_BACK_PHY_ADDR - REG_BASE_SCTRL) + hs_sctrl_base;
	writel(hisi_v2p(master_cpu_resume), addr);

	/* copy securam code */
	fncpy(hs_secram_va_base + DPSLEEP_CODE_ADDR_OFFSET,
			&hs_finish_suspend, DPSLEEP_CODE_LEN);

	local_irq_save(flage);

#ifdef CONFIG_CACHE_L2X0
	outer_flush_all();
	outer_disable();
#endif
	/* config pmu low power */
	pmulowpower(1);

	/* Entering deep sleep */
	wrapper_hs_godpsleep();

	/*PMU regs restore*/
	pmulowpower(0);

#ifdef CONFIG_CACHE_L2X0
	outer_resume();
#endif

	flush_cache_all();

	local_irq_restore(flage);

	pr_notice("[PM] Restore OK\n");

	return 0;
}

static const struct platform_suspend_ops hisik3_pm_ops = {
	.enter		= hisik3_pm_enter,
	.valid		= suspend_valid_only_mem,
};

static int hs_pm_get_resources(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct resource *res;
	int ret = 0;

	/* get the base address of pmu_spi */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		ret = -ENOMEM;
		dev_err(dev, "platform_get_resource 0 err, ret=%d\n", ret);
		goto error_res_1;
	}
	hs_pm_resources.pmu_spi.res = res;
	hs_pm_resources.pmu_spi.virt_addr = ioremap(res->start,
							 resource_size(res));
	if (!hs_pm_resources.pmu_spi.virt_addr) {
		ret = -ENOMEM;
		dev_err(dev, "cannot ioremap pmu_spi register memory\n");
		goto error_res_1;
	}
	hs_pmuspi_va_base = hs_pm_resources.pmu_spi.virt_addr;

	/* get the base address of secram */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!res) {
		ret = -ENOMEM;
		dev_err(dev, "platform_get_resource 1 err, ret=%d\n", ret);
		goto error_res_2;
	}
	hs_pm_resources.secram.res = res;
	hs_pm_resources.secram.virt_addr = ioremap(res->start,
							 resource_size(res));
	if (!hs_pm_resources.secram.virt_addr) {
		ret = -ENOMEM;
		dev_err(dev, "cannot ioremap secram register memory\n");
		goto error_res_2;
	}
	hs_secram_va_base = hs_pm_resources.secram.virt_addr;

	/* get the base address of pctrl */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	if (!res) {
		ret = -ENOMEM;
		dev_err(dev, "platform_get_resource 2 err, ret=%d\n", ret);
		goto error_res_3;
	}
	hs_pm_resources.pctrl.res = res;
	hs_pm_resources.pctrl.virt_addr = ioremap(res->start,
							 resource_size(res));
	if (!hs_pm_resources.pctrl.virt_addr) {
		ret = -ENOMEM;
		dev_err(dev, "cannot ioremap pctrl register memory\n");
		goto error_res_3;
	}
	hs_pctrl_va_base = hs_pm_resources.pctrl.virt_addr;

	/* get the base address of a9_per */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 3);
	if (!res) {
		ret = -ENOMEM;
		dev_err(dev, "platform_get_resource 3 err, ret=%d\n", ret);
		goto error_res_4;
	}
	hs_pm_resources.a9_per.res = res;
	hs_pm_resources.a9_per.virt_addr = ioremap(res->start,
							 resource_size(res));
	if (!hs_pm_resources.a9_per.virt_addr) {
		ret = -ENOMEM;
		dev_err(dev, "cannot ioremap a9_per register memory\n");
		goto error_res_4;
	}
	hs_a9per_va_base = hs_pm_resources.a9_per.virt_addr;

#ifdef CONFIG_HSK3_CONSOLE_WORKAROUND
	/* get the base address of uart0 */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 4);
	if (!res) {
		ret = -ENOMEM;
		dev_err(dev, "platform_get_resource 4 err, ret=%d\n", ret);
		goto error_res_5;
	}
	hs_pm_resources.uart0.res = res;
	hs_pm_resources.uart0.virt_addr = ioremap(res->start,
							 resource_size(res));
	if (!hs_pm_resources.uart0.virt_addr) {
		ret = -ENOMEM;
		dev_err(dev, "cannot ioremap uart0 register memory\n");
		goto error_res_5;
	}
	hs_uart0_va_base = hs_pm_resources.uart0.virt_addr;

	/* get the base address of io */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 5);
	if (!res) {
		ret = -ENOMEM;
		dev_err(dev, "platform_get_resource 5 err, ret=%d\n", ret);
		goto error_res_6;
	}
	hs_pm_resources.io.res = res;
	hs_pm_resources.io.virt_addr = ioremap(res->start,
							 resource_size(res));
	if (!hs_pm_resources.io.virt_addr) {
		ret = -ENOMEM;
		dev_err(dev, "cannot ioremap io register memory\n");
		goto error_res_6;
	}
	hs_io_va_base = hs_pm_resources.io.virt_addr;
#endif /* CONFIG_HSK3_CONSOLE_WORKAROUND */

	/* get pmu_power_off GPIO */
	pmu_power_off_handle = of_get_named_gpio(np, "pmu-power-hold-gpios", 0);

	if (!gpio_is_valid(pmu_power_off_handle)) {
		dev_err(dev, "Fail to get pmu_power_off gpio, err=%d\n",
							pmu_power_off_handle);
		ret = pmu_power_off_handle;
		goto error_pmu_gpio;
	}

	goto get_res_end;

error_pmu_gpio:
#ifdef CONFIG_HSK3_CONSOLE_WORKAROUND
	iounmap(hs_pm_resources.io.virt_addr);
error_res_6:
	iounmap(hs_pm_resources.uart0.virt_addr);
error_res_5:
#endif
	iounmap(hs_pm_resources.a9_per.virt_addr);
error_res_4:
	iounmap(hs_pm_resources.pctrl.virt_addr);
error_res_3:
	iounmap(hs_pm_resources.secram.virt_addr);
error_res_2:
	iounmap(hs_pm_resources.pmu_spi.virt_addr);
error_res_1:

get_res_end:
	return ret;
}

static int hs_pm_free_resources(struct platform_device *pdev)
{
#ifdef CONFIG_HSK3_CONSOLE_WORKAROUND
	iounmap(hs_pm_resources.io.virt_addr);
	iounmap(hs_pm_resources.uart0.virt_addr);
#endif /* CONFIG_HSK3_CONSOLE_WORKAROUND */
	iounmap(hs_pm_resources.a9_per.virt_addr);
	iounmap(hs_pm_resources.pctrl.virt_addr);
	iounmap(hs_pm_resources.secram.virt_addr);
	iounmap(hs_pm_resources.pmu_spi.virt_addr);
	return 0;
}

#ifdef CONFIG_HSK3_RTC_WAKEUP
static int hs_set_wake(struct irq_data *data, unsigned int state)
{
      return 0;
}
#endif

static int hs_pm_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	void __iomem *addr;
	int ret = 0;

	/* alloc memmory for suspend */
	hi_cpu_godpsleep_ddrbase = (unsigned long)kzalloc(
			(SR_PROTECT_CTX_BUFF_SIZE), GFP_DMA|GFP_KERNEL);
	if (!hi_cpu_godpsleep_ddrbase) {
		dev_err(dev, "kzalloc err for hi_cpu_godpsleep_ddrbase!\n");
		return -ENOMEM;
	}

	hi_cpu_godpsleep_phybase = hisi_v2p(hi_cpu_godpsleep_ddrbase);

	/* get resources, parse from device tree */
	ret = hs_pm_get_resources(pdev);
	if (ret) {
		dev_err(dev, "hs_pm_get_resources err, ret=%d\n", ret);
		goto error_res;
	}

	addr = hs_sctrl_base + 0x10;
	writel(SCXTALCTRL_CFG_VAL_200MS, addr);

	suspend_set_ops(&hisik3_pm_ops);

	/* power off function */
	pm_power_off = hisik3_power_off;

#ifdef CONFIG_HSK3_RTC_WAKEUP
	/* set wakeup funciton */
	gic_arch_extn.irq_set_wake = hs_set_wake;
#endif

	goto probe_end;

error_res:
	kfree((void *)hi_cpu_godpsleep_ddrbase);
probe_end:
	return ret;
}

static int hs_pm_remove(struct platform_device *pdev)
{
	hs_pm_free_resources(pdev);
	kfree((void *)hi_cpu_godpsleep_ddrbase);
	return 0;
}

static struct of_device_id of_hs_pm_match_tbl[] = {
	{
		.compatible = "hisilicon,hs-power-management",
	},
	{ /* end */ }
};

static struct platform_driver hs_pm_driver = {
	.driver = {
		.name	= "hs_pm",
		.owner  = THIS_MODULE,
		.of_match_table = of_hs_pm_match_tbl,
	},
	.probe	= hs_pm_probe,
	.remove	= hs_pm_remove,
};

static int __init hs_pm_init(void)
{
	return platform_driver_register(&hs_pm_driver);
}
module_init(hs_pm_init);

static void __exit hs_pm_exit(void)
{
	platform_driver_unregister(&hs_pm_driver);
}
module_exit(hs_pm_exit);

MODULE_AUTHOR("Guodong Xu <guodong.xu@linaro.org>");
MODULE_DESCRIPTION("HiSilicon power management driver");
MODULE_LICENSE("GPL v2");
