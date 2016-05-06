
#include <linux/amba/bus.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <asm/system.h>
#include <asm/setup.h>
#include <linux/amba/serial.h>
#include <linux/spi/spi.h>
#include <linux/mux.h>
#include <linux/delay.h>
#include <linux/ioport.h>



#define AMBA_DEVICE(name, busid, base, plat)			\
static struct amba_device name##_device = {			\
	.dev		= {					\
		.coherent_dma_mask = ~0,			\
		.init_name = busid,				\
		.platform_data = plat,				\
	},							\
	.res		= {					\
		.start	= REG_BASE_##base,			\
		.end	= (REG_BASE_##base) + SZ_4K - 1,	\
		.flags	= IORESOURCE_MEM,			\
	},							\
	.dma_mask	= ~0,					\
	.irq		= { IRQ_##base, NO_IRQ },		\
}


