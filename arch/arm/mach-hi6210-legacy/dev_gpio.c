#include <linux/amba/bus.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/init.h>
#include <asm/hardware/cache-l2x0.h>
#include <asm/system.h>
#include <asm/pmu.h>
#include <asm/setup.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <mach/lm.h>
#include <mach/irqs.h>
#include <mach/io.h>
#include "soc_irqs.h"
#include <linux/amba/pl061.h>
#include <mach/early-debug.h>
#include <mach/mmc.h>
#include <mach/dma.h>
#include <mach/dev.h>
#include <linux/amba/serial.h>
#include <linux/i2c/designware.h>
#include <linux/spi/spi.h>
#include <linux/mux.h>
#include <linux/delay.h>

/*gpio device declare and register*/
#define PL061_GPIO_PLATFORM_DATA(id)	\
static struct pl061_platform_data gpio##id##_plat_data = {	\
	.gpio_base	= (id * 8),	\
	.irq_base	= IRQ_GPIO_BASE + (id * 8),	\
}

/*we have 13 gpio chips*/

PL061_GPIO_PLATFORM_DATA(0);
PL061_GPIO_PLATFORM_DATA(1);
PL061_GPIO_PLATFORM_DATA(2);
PL061_GPIO_PLATFORM_DATA(3);
PL061_GPIO_PLATFORM_DATA(4);
PL061_GPIO_PLATFORM_DATA(5);
PL061_GPIO_PLATFORM_DATA(6);
PL061_GPIO_PLATFORM_DATA(7);
PL061_GPIO_PLATFORM_DATA(8);
PL061_GPIO_PLATFORM_DATA(9);
PL061_GPIO_PLATFORM_DATA(10);
PL061_GPIO_PLATFORM_DATA(11);
PL061_GPIO_PLATFORM_DATA(12);
PL061_GPIO_PLATFORM_DATA(13);
PL061_GPIO_PLATFORM_DATA(14);
PL061_GPIO_PLATFORM_DATA(15);
PL061_GPIO_PLATFORM_DATA(16);
PL061_GPIO_PLATFORM_DATA(17);
PL061_GPIO_PLATFORM_DATA(18);
PL061_GPIO_PLATFORM_DATA(19);


AMBA_DEVICE(gpio0, "gpio0", GPIO0, &gpio0_plat_data);
AMBA_DEVICE(gpio1, "gpio1", GPIO1, &gpio1_plat_data);
AMBA_DEVICE(gpio2, "gpio2", GPIO2, &gpio2_plat_data);
AMBA_DEVICE(gpio3, "gpio3", GPIO3, &gpio3_plat_data);
AMBA_DEVICE(gpio4, "gpio4", GPIO4, &gpio4_plat_data);
AMBA_DEVICE(gpio5, "gpio5", GPIO5, &gpio5_plat_data);
AMBA_DEVICE(gpio6, "gpio6", GPIO6, &gpio6_plat_data);
AMBA_DEVICE(gpio7, "gpio7", GPIO7, &gpio7_plat_data);
AMBA_DEVICE(gpio8, "gpio8", GPIO8, &gpio8_plat_data);
AMBA_DEVICE(gpio9, "gpio9", GPIO9, &gpio9_plat_data);
AMBA_DEVICE(gpio10, "gpio10", GPIO10, &gpio10_plat_data);
AMBA_DEVICE(gpio11, "gpio11", GPIO11, &gpio11_plat_data);
AMBA_DEVICE(gpio12, "gpio12", GPIO12, &gpio12_plat_data);
AMBA_DEVICE(gpio13, "gpio13", GPIO13, &gpio13_plat_data);
AMBA_DEVICE(gpio14, "gpio14", GPIO14, &gpio14_plat_data);
AMBA_DEVICE(gpio15, "gpio15", GPIO15, &gpio15_plat_data);
AMBA_DEVICE(gpio16, "gpio16", GPIO16, &gpio16_plat_data);
AMBA_DEVICE(gpio17, "gpio17", GPIO17, &gpio17_plat_data);
AMBA_DEVICE(gpio18, "gpio18", GPIO18, &gpio18_plat_data);
AMBA_DEVICE(gpio19, "gpio19", GPIO19, &gpio19_plat_data);

#ifdef _DRV_LLT_
struct amba_device *amba_gpio_devs[] __initdata = {
#else
static struct amba_device *amba_gpio_devs[] __initdata = {
#endif
	&gpio0_device,
	&gpio1_device,
	&gpio2_device,
	&gpio3_device,
	&gpio4_device,
#if defined(CHIP_BB_HI6210)
#else
	&gpio5_device,
	&gpio6_device,
	&gpio7_device,
	&gpio8_device,
	&gpio9_device,
	&gpio10_device,
	&gpio11_device,
	&gpio12_device,
	&gpio13_device,
	&gpio14_device,
	&gpio15_device,
	&gpio16_device,
	&gpio17_device,
	&gpio18_device,
	&gpio19_device
#endif
};


static int __init amba_gpio_dev_init(void)
{

	int i;
	int ret = -1;

	edb_trace(1);

	for (i = 0; i < ARRAY_SIZE(amba_gpio_devs); i++) {
		struct amba_device *d = amba_gpio_devs[i];

		ret = amba_device_register(d, &iomem_resource);
		if (ret != 0) {
			break;
		}

	}
	edb_trace(1);

	return ret;
}

arch_initcall(amba_gpio_dev_init);

