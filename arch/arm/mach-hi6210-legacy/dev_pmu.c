/*pmu device declare and register*/
#include <linux/platform_device.h>
#include <linux/io.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <mach/irqs.h>
#include <mach/io.h>
#include <mach/board-hi6421-regulator.h>

#if 0

static struct resource  A9_pmu_resource[] = {
	[0] = {
		.start = IRQ_PMIRQ0,
		.end   = IRQ_PMIRQ0,
		.flags = IORESOURCE_IRQ,
	},
#if (CONFIG_NR_CPUS >= 2)
	[1] = {
		.start = IRQ_PMIRQ1,
		.end   = IRQ_PMIRQ1,
		.flags = IORESOURCE_IRQ,
	},
#endif

#if (CONFIG_NR_CPUS >= 3)
	[2] = {
		.start = IRQ_PMIRQ2,
		.end   = IRQ_PMIRQ2,
		.flags = IORESOURCE_IRQ,
	},
#endif

#if (CONFIG_NR_CPUS >= 4)
	[3] = {
		.start = IRQ_PMIRQ3,
		.end   = IRQ_PMIRQ3,
		.flags = IORESOURCE_IRQ,
	},
#endif
};


static struct platform_device A9_pmu_device = {
	.name			= "arm-pmu",
	.id				= ARM_PMU_DEVICE_CPU,
	.resource			= &A9_pmu_resource,
	.num_resources	= ARRAY_SIZE(A9_pmu_resource),
};

static int __init plat_pmu_init(void)
{
	int ret = 0;
	ret = platform_device_register(&A9_pmu_device);
	return ret;
};


arch_initcall(plat_pmu_init);
#endif
/* please add all pmu related platform device in the struct.*/
static struct platform_device *plat_pmu_dev[] __initdata = {
	&hi6421_regulator_device
       /*add other pmu device here*/
};

static int __init plat_hi6421_regulator_dev_init(void)
{
	int ret = 0;

	ret = platform_add_devices(plat_pmu_dev, ARRAY_SIZE(plat_pmu_dev));

	return ret;
};

arch_initcall(plat_hi6421_regulator_dev_init);
