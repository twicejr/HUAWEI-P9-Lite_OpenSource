#include <linux/platform_device.h>
#include <linux/io.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <linux/init.h>
#include <soc_irqs.h>
#if defined(CHIP_BB_HI6210)
#include <soc_modem_sctrl_interface.h>
#else
#include <soc_sctrl_interface.h>
#endif
#include <soc_ao_sctrl_interface.h>
#include <mach/util.h>
#include <linux/etb.h>

static struct etb_platform_data etb_data ={
	.iobase = (ACPU_BASE + ETM_BASE),
	.size = 0x1000,
};

static struct platform_device plat_etb_dev = {
	.name = "etb",
	.id = -1,
	.dev = {
		.platform_data = &etb_data,
	},
};

static int __init plat_etb_dev_init(void)
{
	int ret = 0;

	ret = platform_device_register(&plat_etb_dev);

	return ret;
};
arch_initcall(plat_etb_dev_init);

MODULE_DESCRIPTION("Hisilicon Balong Platform ETM Device Declaration");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("l00189326");