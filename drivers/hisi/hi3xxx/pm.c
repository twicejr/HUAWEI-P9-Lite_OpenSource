#include <linux/init.h>
#include <linux/suspend.h>
#include <linux/syscore_ops.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/err.h>
#include <asm/suspend.h>
#include <linux/platform_device.h>
#include <linux/cpu_pm.h>
#include <asm/cputype.h>
#include <linux/hw_power_monitor.h>
#include <soc_sctrl_interface.h>
#include <soc_crgperiph_interface.h>
#include <soc_acpu_baseaddr_interface.h>
#ifdef CONFIG_HISI_SR_DEBUG
#include <linux/mfd/hisi_pmic.h>
#include "hisi_lpregs.h"
#endif

#define POWER_STATE_TYPE_SYS_SUSPEND	3

/*lint -e750 -esym(750,*) */
#define REG_SCBAKDATA8_OFFSET	SOC_SCTRL_SCBAKDATA8_ADDR(0)
#define REG_SCBAKDATA9_OFFSET	SOC_SCTRL_SCBAKDATA9_ADDR(0)
#define CPUIDLE_FLAG_REG(cluster)	\
	((cluster == 0) ? REG_SCBAKDATA8_OFFSET :  REG_SCBAKDATA9_OFFSET)


#define AP_SUSPEND_FLAG					BIT(16)

#define GIC_ENABLE_OFFSET					(0x100)
#define GIC_PENDING_OFFSET					(0x200)
#define IRQ_GROUP_MAX		(10)
#define IRQ_NUM_PER_WORD	(32)

/* FIXME: need to distinguish diff platform */
#define	AO_GPIO_GROUP		(22)
#define	AO_GPIO_GROUP_NUM	(6)
#define	AO_GPIO_IRQ_BASE	(138)

#define NO_SEQFILE 0

static void __iomem *g_bbpdrx1_base;
static void __iomem *sysctrl_base;
static void __iomem *g_enable_base;
static void __iomem *g_pending_base;
static void __iomem *crgctrl_base_addr;
static unsigned int g_enable_value[10];
static void __iomem *ao_gpio_base[AO_GPIO_GROUP_NUM];
static const char *g_plat_name;
unsigned int g_irq_num;
const char **g_irq_name;

static int pm_ao_gpio_irq_dump(unsigned int irq_num)
{
	int i, group, data;

	group = (int)irq_num - AO_GPIO_IRQ_BASE;
	if (group >= AO_GPIO_GROUP_NUM || group < 0)
		return -EINVAL;

	data = readl(ao_gpio_base[group] + 0x410)
			& readl(ao_gpio_base[group] + 0x418);

	for (i = 0; i < 8; i++)
		if (data & BIT(i))
			return (group + AO_GPIO_GROUP) * 8 + i;

	return  -EINVAL;
}

void pm_gic_dump(void)
{
	unsigned int i;

	for (i = 2; i < IRQ_GROUP_MAX; i++)
		g_enable_value[i] = readl(g_enable_base + i * 4);
}

void pm_gic_pending_dump(void)
{
	unsigned int i;
	unsigned int j;
	unsigned int value;
	unsigned int irq;
	int gpio;

	for (i = 2; i < IRQ_GROUP_MAX; i++) {
		value = readl(g_pending_base + i * 4);

		for (j = 0; j < IRQ_NUM_PER_WORD; j++) {
			if ((value & BIT_MASK(j)) && ((value & BIT_MASK(j))
					== (g_enable_value[i] & BIT_MASK(j)))) {
				irq = i * IRQ_NUM_PER_WORD + j;
				if (irq < g_irq_num)
					printk("wake up irq num: %d, irq name: %s", irq, g_irq_name[irq]);
				else
					printk("wake up irq num: %d, irq name: no name!", irq);
				power_monitor_report(WAKEUP_IRQ, "%s",
						g_irq_name[irq]);
				gpio = pm_ao_gpio_irq_dump(irq);
				if (gpio >= 0) {
					printk("(gpio-%d)", gpio);
					power_monitor_report(WAKEUP_GPIO, "%d",
							gpio);
				}
				printk("\n");
			}
		}
	}
}

void hisi_set_ap_suspend_flag(unsigned int cluster)
{
	unsigned int val;

	/* do not need lock, as the core is only one now. */
	val = readl(sysctrl_base + CPUIDLE_FLAG_REG(cluster));
	val |= AP_SUSPEND_FLAG;
	writel(val, sysctrl_base + CPUIDLE_FLAG_REG(cluster));
}

void hisi_clear_ap_suspend_flag(unsigned int cluster)
{
	unsigned int val;

	/* do not need lock, as the core is only one now. */
	val = readl(sysctrl_base + CPUIDLE_FLAG_REG(cluster));
	val &= ~AP_SUSPEND_FLAG;
	writel(val, sysctrl_base + CPUIDLE_FLAG_REG(cluster));
}

#define COREPWRACK_MASK (0x7F800)
#define PERPWRACK_OFFSET (0x15c)


static int hisi_test_pwrdn_othercores(unsigned int cluster, unsigned int core)
{
	unsigned int pwrack_stat = 0;
	unsigned int mask = 0;

	/* boot core mask */
	mask = (0x1 << (11 + cluster * 4 + core));
	pwrack_stat = readl(crgctrl_base_addr + PERPWRACK_OFFSET);
	/* non boot core mask */
	mask = COREPWRACK_MASK & (~mask);
	pwrack_stat &= mask;

	return pwrack_stat;
}

static int hisi_pm_enter(suspend_state_t state)
{
	unsigned int cluster = 0;
	unsigned int core = 0;
	unsigned long mpidr = read_cpuid_mpidr();
	unsigned int tickmark = 0;

	pr_err("%s ++\n", __func__);

	cluster = (mpidr >> 8) & 0xff;
	core = mpidr & 0xff;

	pm_gic_dump();
#ifdef CONFIG_HISI_SR_DEBUG
	get_ip_regulator_state();
	dbg_io_status_show();
	dbg_pmu_status_show();
	dbg_clk_status_show();
#endif
	while (hisi_test_pwrdn_othercores(cluster, core))
		;
	hisi_set_ap_suspend_flag(cluster);
	cpu_cluster_pm_enter();
	cpu_suspend(POWER_STATE_TYPE_SYS_SUSPEND);
	tickmark = readl(g_bbpdrx1_base);
#ifdef CONFIG_HISI_SR_DEBUG
	debuguart_reinit();
#endif
	cpu_cluster_pm_exit();
	hisi_clear_ap_suspend_flag(cluster);
#ifdef CONFIG_HISI_SR_DEBUG
	pr_info("%s tick: 0x%x, 0x%x, 0x%x\n",
			__func__, tickmark, readl(g_bbpdrx1_base),
			readl(g_bbpdrx1_base) - tickmark);
	pm_gic_pending_dump();
	pm_status_show(NO_SEQFILE);
#endif
	pr_err("%s --\n", __func__);

	return 0;
}

static const struct platform_suspend_ops hisi_pm_ops = {
	.enter		= hisi_pm_enter,
	.valid		= suspend_valid_only_mem,
};

static int hisi_get_gic_base(void)
{
	void __iomem *hisi_gic_dist_base;
	struct device_node *node;

	node = of_find_compatible_node(NULL, NULL, "arm,cortex-a9-gic");
	if (!node) {
		pr_err("%s: hisilicon,gic No compatible node found\n",
				__func__);
		return -ENODEV;
	}

	hisi_gic_dist_base = of_iomap(node, 0);
	if (!hisi_gic_dist_base) {
		pr_err("%s: hisilicon,gic_dist_base is NULL\n", __func__);
		return -ENODEV;
	}

	pr_info("hisi_gic_dist_base = %p\n", hisi_gic_dist_base);

	g_enable_base = hisi_gic_dist_base + GIC_ENABLE_OFFSET;
	g_pending_base = hisi_gic_dist_base + GIC_PENDING_OFFSET;

	return 0;
}

static int hisi_get_gpio_regs(void)
{
	int i;
	struct device_node *np = NULL;
	char *io_buffer;

	io_buffer = kmalloc(40 * sizeof(char), GFP_KERNEL);
	if (!io_buffer) {
		pr_err("%s: kmalloc err!!\n", __func__);
		return -ENOMEM;
	}

	for (i = 0; i < AO_GPIO_GROUP_NUM; i++) {
		memset(io_buffer, 0, 40*sizeof(char));
		snprintf(io_buffer, 40*sizeof(char), "arm,primecell%d",
				i + AO_GPIO_GROUP);
		np = of_find_compatible_node(NULL, NULL, io_buffer);
		if (!np) {
			pr_err("%s: hisilicon,primecell%d No compatible node found\n",
					__func__, i + AO_GPIO_GROUP);
			continue;
		}

		ao_gpio_base[i] = of_iomap(np, 0);
		if (!ao_gpio_base[i])
			goto err_put_node;

		of_node_put(np);
		if ((AO_GPIO_GROUP_NUM - 1) == i)
			pr_info("%s find ao gpio group num:%d\n",
					__func__, i + 1);
	}

	kfree(io_buffer);
	io_buffer = NULL;
	return 0;
err_put_node:
	of_node_put(np);
err_free_buffer:
	kfree(io_buffer);
	return -ENODEV;
}

static int init_lowpm_table(struct device_node *np)
{
	int ret = 0;
	u32 i = 0;

	/* init irq table */
	ret = of_property_count_strings(np, "irq-table");
	if (ret < 0) {
		pr_err("%s, not find irq-table property!\n", __func__);
		goto err;
	}
	g_irq_num = ret;
	pr_info("%s, irq-table num: %d!\n", __func__, g_irq_num);

	g_irq_name = kzalloc(g_irq_num * sizeof(char *), GFP_KERNEL);
	if (!g_irq_name) {
		pr_err("%s: kzalloc err!!\n", __func__);
		ret = -ENOMEM;
		goto err_put_node;
	}

	for (i = 0; i < g_irq_num; i++) {
		ret = of_property_read_string_index(np, "irq-table",
				i, &g_irq_name[i]);
		if (ret) {
			pr_err("%s, no irq-table %d!\n", __func__, i);
			goto err_free;
		}
	}

	pr_info("%s, init lowpm table success.\n", __func__);

err_free:
	kfree(g_irq_name);
err_put_node:
	of_node_put(np);
err:
	return ret;
}

static __init int hisi_pm_drvinit(void)
{
	struct device_node *np = NULL;
	int ret = 0;

	if (hisi_get_gpio_regs()) {
		pr_err("%s: hisilicon,get gpio base failed!\n", __func__);
		return -ENODEV;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,lowpm_func");
	if (!np) {
		pr_err("%s: hisilicon,lowpm_func No compatible node found\n",
				__func__);
		return -ENODEV;
	}

	ret = of_property_read_string(np, "plat-name", &g_plat_name);
	if (ret)
		pr_err("%s, no plat-name!\n", __func__);
	pr_info("%s: current plat is %s.\n", __func__, g_plat_name);

	ret = init_lowpm_table(np);
	if (ret) {
		pr_err("%s, init lowpm_table err!\n", __func__);
		return -ENODEV;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (!np) {
		pr_err("%s: hisilicon,sysctrl No compatible node found\n",
				__func__);
		return -ENODEV;
	}

	sysctrl_base = of_iomap(np, 0);
	if (!sysctrl_base) {
		pr_err("%s: hisilicon,sysctrl_base is NULL\n", __func__);
		return -ENODEV;
	}

	of_node_put(np);

	np = of_find_compatible_node(NULL, NULL, "hisilicon,crgctrl");
	if (!np) {
		pr_info("%s: hisilicon,crgctrl No compatible node found\n",
				__func__);
		return -ENODEV;
	}

	crgctrl_base_addr = of_iomap(np, 0);
	if (!crgctrl_base_addr) {
		pr_err("%s: hisilicon,crgctrl_base_addr is NULL\n", __func__);
		return -ENODEV;
	}

	of_node_put(np);

	if (hisi_get_gic_base()) {
		pr_err("%s: hisilicon,get gic base failed!\n", __func__);
		return -ENODEV;
	}

	suspend_set_ops(&hisi_pm_ops);

	g_bbpdrx1_base = ioremap(SOC_SCTRL_SCBBPDRXSTAT1_ADDR(SOC_ACPU_SCTRL_BASE_ADDR), 0x4);
	if (!g_bbpdrx1_base)
		pr_err("%s: get SCBBPDRXSTAT1_ADDR failed!\n", __func__);

	return 0;
}
arch_initcall(hisi_pm_drvinit);
