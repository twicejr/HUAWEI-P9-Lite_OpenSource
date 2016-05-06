/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 *******************************************************************************
  文 件 名   : dev_spi.c
  版 本 号   : 初稿
  作    者   : 张彪 zkf67996
  生成日期   : 2012年8月9日
  最近修改   :
  功能描述   : header
  修改历史   :
  1.日    期   : 2012年8月9日
    作    者   : 张彪 zkf67996
    修改内容   : 创建文件

*******************************************************************************/

/*******************************************************************************
  1 头文件包含
*******************************************************************************/
#include <mach/early-debug.h>
#include <linux/spi/spi.h>
#include <linux/amba/bus.h>
#include <mach/platform.h>
#include <mach/irqs.h>
#include <linux/amba/pl022.h>
#include <linux/mux.h>



/*******************************************************************************
  2 全局变量定义
*******************************************************************************/

extern struct iomux_block *iomux_get_block(char *name);
extern struct block_config *iomux_get_blockconfig(char *name);
extern int blockmux_set(struct iomux_block *blockmux,
        	struct block_config *config, enum iomux_func newmode);

#ifdef _DRV_LLT_
void common_block_set(char *block_name, enum iomux_func newmode);
#else
static void common_block_set(char *block_name, enum iomux_func newmode);
#endif


#define PL022_CONFIG_CHIP(id)						\
static struct pl022_config_chip spidev##id##_chip_info = {		\
	.com_mode 		= POLLING_TRANSFER,				\
	.iface			= SSP_INTERFACE_MOTOROLA_SPI,         	\
	.hierarchy		= SSP_MASTER,				\
	.slave_tx_disable	= 0,					\
	.rx_lev_trig		= SSP_RX_16_OR_MORE_ELEM,		\
	.tx_lev_trig		= SSP_TX_16_OR_MORE_EMPTY_LOC,		\
	.ctrl_len		= SSP_BITS_8,				\
	.wait_state		= SSP_MWIRE_WAIT_ZERO,			\
	.duplex 		= SSP_MICROWIRE_CHANNEL_FULL_DUPLEX,	\
	.cs_control		= NULL,         	                \
}

PL022_CONFIG_CHIP(0);
PL022_CONFIG_CHIP(1);

#define K3_SPI_PLAT_DATA(dev_name, num_id, num_cs, en_dma)		\
	{             							\
		.bus_id = num_id,					\
		.num_chipselect = num_cs,				\
		.enable_dma = en_dma,					\
		.dma_filter = NULL,			\
		.dma_rx_param = NULL,	\
		.dma_tx_param = NULL,	\
		.init = NULL,				\
		.exit = NULL,				\
	}

static struct pl022_ssp_controller spi_plat_data[] = {
	K3_SPI_PLAT_DATA(SPI0, 0, 1, 0),
	K3_SPI_PLAT_DATA(SPI1, 1, 1, 0),
};

#ifdef _DRV_LLT_
#define AMBA_DEVICE(name, busid, base, plat)			\
 struct amba_device name##_device = {			\
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
#else
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
#endif

AMBA_DEVICE(spi0, "dev:ssp0", SSP0, &spi_plat_data[0]);
//AMBA_DEVICE(spi1, "dev:ssp1", SSP1, &spi_plat_data[1]);

/*******************************************************************************
  4 函数实现
*******************************************************************************/
#ifdef _DRV_LLT_
void common_block_set(char *block_name, enum iomux_func newmode)
#else
static void common_block_set(char *block_name, enum iomux_func newmode)
#endif
{
	struct iomux_block *block_tmp = NULL;
	struct block_config *config_tmp = NULL;
	int ret = -1;

	block_tmp = iomux_get_block(block_name);
	if (!block_tmp) {
		pr_err("%s: iomux_get_block(%s) error.\n",
			__func__, block_name);
		return;
	}

	config_tmp = iomux_get_blockconfig(block_name);
	if (!config_tmp) {
		pr_err("%s: iomux_get_blockconfig(%s) error.\n",
			__func__, block_name);
		return;
	}

	ret = blockmux_set(block_tmp, config_tmp, newmode);
	if (ret) {
		pr_err("%s: blockmux_set error.\n", __func__);
		return;
	}
}

/* spi_devs driver registration */
#ifdef _DRV_LLT_
int k3v2_spi_board_register(void)
#else
static int k3v2_spi_board_register(void)
#endif
{
	static struct spi_board_info info[] = {
		[0] = {
			.modalias = "spi_dev0",
			.max_speed_hz = 6000000,
			.bus_num = 0,
			.chip_select = 0,
			.controller_data = &spidev0_chip_info,
		},
		[1] = {
			.modalias = "spi_dev1",
			.max_speed_hz = 6000000,
			.bus_num = 1,
			.chip_select = 0,
			.controller_data = &spidev1_chip_info,
		},
	};

	return spi_register_board_info(info, ARRAY_SIZE(info));
}

#ifdef _DRV_LLT_
 struct amba_device *amba_spi_devs[]  = {
	&spi0_device,
    //&spi1_device,
};
#else
static struct amba_device *amba_spi_devs[] __initdata = {
	&spi0_device,
      // &spi1_device,
};
#endif

#ifdef _DRV_LLT_
void  hisik3_spi_init(void)
#else
void __init hisik3_spi_init(void)
#endif
{
	int i;
       int ret;

	edb_trace(1);

	ret = k3v2_spi_board_register();
	if(0!=ret)
	{
		printk(KERN_ERR "k3v2_spi_board_register failed  ret = %d.\n", ret);
	}

	for (i = 0; i < ARRAY_SIZE(amba_spi_devs); i++) {
		struct amba_device *d = amba_spi_devs[i];
		amba_device_register(d, &iomem_resource);
	}
	edb_trace(1);
}

arch_initcall(hisik3_spi_init);
