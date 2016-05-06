#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/ioport.h>
#include "soc_irqs.h"
#include <mach/platform.h>

static struct resource balong_fb_resources[] = {
	[0] = {
		.name = "reg_base_ade",
		.start = REG_BASE_ADE,
		.end = REG_BASE_ADE + REG_ADE_IOSIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.name = "irq_ade",
		.start = IRQ_ADE,
		.end = IRQ_ADE,
		.flags = IORESOURCE_IRQ,
	},
	[2] = {
		.name = "irq_ldi",
		.start = IRQ_ADE_LDI,
		.end = IRQ_ADE_LDI,
		.flags = IORESOURCE_IRQ,
	},
};

static struct platform_device balong_fb_device = {
	.name	= "balong_fb",
	.id	= 0,
	.num_resources	= ARRAY_SIZE(balong_fb_resources),
	.resource	= balong_fb_resources,
};

static struct platform_device *fb_devices[] __initdata = {
	&balong_fb_device,
};


static int __init fb_device_init(void)
{
	int ret = 0;   
	ret = platform_device_register(&balong_fb_device);
	return ret;
};

arch_initcall(fb_device_init);



