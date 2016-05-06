#include <mach/irqs.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>

//#include <mach/platform.h>
//#define IRQ_PMU_BASE		            (SOC_PMUSSI_BASE_ADDR + 0x003)

#define IRQ_POWER_KEY_LONG_PRESS_4S		POWERON_D4sR_TYPE//(IRQ_PMU_BASE + 4)
#define IRQ_POWER_KEY_RELEASE	        POWERON_D20F_TYPE//(IRQ_PMU_BASE + 5)
#define IRQ_POWER_KEY_PRESS	            POWERON_D20R_TYPE//(IRQ_PMU_BASE + 6)

/*power-key*/
static struct resource dvp_power_key_resources[] = {
	[0] = {
		.start = IRQ_POWER_KEY_PRESS,
		.end = IRQ_POWER_KEY_PRESS,
		.flags = IORESOURCE_IRQ,
	},
	[1] = {
		.start = IRQ_POWER_KEY_RELEASE,
		.end = IRQ_POWER_KEY_RELEASE,
		.flags = IORESOURCE_IRQ,
	},
	[2] = {
		.start = IRQ_POWER_KEY_LONG_PRESS_4S,
		.end = IRQ_POWER_KEY_LONG_PRESS_4S,
		.flags = IORESOURCE_IRQ,
	},
};

static struct platform_device dvp_power_key_device = {
	.name = "k3v2_power_key",
	.id = -1,
	.num_resources = ARRAY_SIZE(dvp_power_key_resources),
	.resource = dvp_power_key_resources,
};

static int __init keyboard_dev_init(void)
{
    int ret = -1;

    ret = platform_device_register(&dvp_power_key_device);

    return ret;
}

arch_initcall(keyboard_dev_init);

