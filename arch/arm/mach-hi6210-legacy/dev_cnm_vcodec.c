/*video/jpeg device declare and register*/

#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/init.h>

#ifndef __ASSEMBLY__
#include <asm/sizes.h>
#include <linux/mm.h>
#endif

#include "soc_baseaddr_interface.h"
#include "soc_irqs.h"

/* VPU */
static struct resource cnm_vpu_resources[] = {
	[0] = {
	       .start = SOC_VPU_S_BASE_ADDR,
	       .end = SOC_VPU_S_BASE_ADDR + PAGE_ALIGN(SZ_4K) - 1,
	       .flags = IORESOURCE_MEM,
	       },

	[1] = {
	       .start = IRQ_VDEC,
	       .end = IRQ_VDEC,
	       .flags = IORESOURCE_IRQ,
	       }
};

static struct platform_device balong_cnm_vpu_device = {
	.name = "cnm_vpu",
	.id = 0,
	.resource = cnm_vpu_resources,
	.num_resources = 2,
};

/* JPU */
static struct resource cnm_jpu_resources[] = {
	[0] = {
	       .start = SOC_JPU_S_BASE_ADDR,
	       .end = SOC_JPU_S_BASE_ADDR + PAGE_ALIGN(SZ_4K) - 1,
	       .flags = IORESOURCE_MEM,
	       },

	[1] = {
	       .start = IRQ_JPEG,
	       .end = IRQ_JPEG,
	       .flags = IORESOURCE_IRQ,
	       }
};

static struct platform_device balong_cnm_jpu_device = {
	.name = "cnm_jpu",
	.id = 0,
	.resource = cnm_jpu_resources,
	.num_resources = 2,
};

/* please add platform device in the struct.*/
static struct platform_device *plat_vcodec_dev[] __initdata = {
	&balong_cnm_vpu_device,
	&balong_cnm_jpu_device
};

static int __init plat_vcodec_dev_init(void)
{
	int ret = 0;
	printk("enter plat_vcodec_dev_init()\n");

	ret = platform_add_devices(plat_vcodec_dev, ARRAY_SIZE(plat_vcodec_dev));

	return ret;
};

arch_initcall(plat_vcodec_dev_init);

