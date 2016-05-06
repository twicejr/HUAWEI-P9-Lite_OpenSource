#include <linux/init.h>
#include <linux/cpu_pm.h>
#include <linux/suspend.h>
#include <linux/syscore_ops.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/clockchips.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/arm-cci.h>
#include <linux/irqchip/arm-gic.h>
#include <asm/suspend.h>
#include <asm/mcpm.h>
#include <asm/idmap.h>
#include <asm/cacheflush.h>
#include <asm/cputype.h>
#include <asm/cp15.h>
#include <asm/psci.h>
#include <linux/platform_device.h>
#include <linux/delay.h>

#define PMU_RESET_REG                 (0x1C4 << 2)

static void __iomem *gpio24_base;
static void __iomem *pmu_base;

static void hisi_power_off(void)
{
	if (pmu_base != NULL) {
		/* clear the abnormal reset flag*/
		writel(0, pmu_base + PMU_RESET_REG);
	}

	while(1) {
		/*pr_info("system power off now\n");*/
		writel((0x1 << 3) | readl(gpio24_base + 0x400), gpio24_base + 0x400);
		writel((0x0 << 3), gpio24_base + (0x1 << (3 + 2)));
		mdelay(1000);
	}

}

static __init int k3v3_poweroff_init(void)
{
	struct device_node *np = NULL;

	np = of_find_compatible_node(NULL, NULL, "hisi,poweroff");
	/* get power_off GPIO */
	if (!np) {
		printk(KERN_ERR "get hisi,poweroff np error !\n");
	}
	gpio24_base = of_iomap(np, 0);
	if (gpio24_base == NULL) {
		printk(KERN_ERR "get gpio24_base error !\n");
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,hi6421-pmic");
	if (!np) {
		printk(KERN_ERR "get hisilicon,hi6421-pmic error !\n");
	}
	pmu_base = of_iomap(np, 0);
	if (pmu_base == NULL) {
		printk(KERN_ERR "get gpio24_base error !\n");
	}

	/* power off function */
	pm_power_off = hisi_power_off;

	return 0;
}

late_initcall(k3v3_poweroff_init);
