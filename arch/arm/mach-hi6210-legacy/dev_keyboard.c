#include <mach/irqs.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <mach/gpio.h>

/* Keypad device and platform data start, use GPIO realizing keypad. */

static struct resource dvp_gpio_key_resources[] = {
	[0] = {
		.start = IRQ_GPIO(GPIO_1_4),
		.end = IRQ_GPIO(GPIO_1_4),
		.flags = IORESOURCE_IRQ,
	},
	[1] = {
		.start = IRQ_GPIO(GPIO_1_5),
		.end = IRQ_GPIO(GPIO_1_5),
		.flags = IORESOURCE_IRQ,
	},
	[2] = {
		.start = IRQ_GPIO(GPIO_1_6),
		.end = IRQ_GPIO(GPIO_1_6),
		.flags = IORESOURCE_IRQ,
	},
};

static struct platform_device dvp_gpio_key_device = {
	.name = "k3v2_gpio_key",
	.id = -1,
	.num_resources = ARRAY_SIZE(dvp_gpio_key_resources),
	.resource = dvp_gpio_key_resources,
};

static int __init keyboard_dev_init(void)
{
    int ret = -1;

    ret = platform_device_register(&dvp_gpio_key_device);

    return ret;
}

arch_initcall(keyboard_dev_init);

