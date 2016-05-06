/*dma device declare and register*/
/*
 * Copyright (C) Hisilicon Technologies Co.,Ltd.
 *	k3<k3dma@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#if 0
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <mach/dma.h>

static u64 k3_dma_mask = DMA_BIT_MASK(32);
static bool set_acp(bool on)
{
	void __iomem		*pctrl;
	if (!request_mem_region(REG_BASE_PCTRL, 4, DEVICE_NAME))
		return false;

	pctrl = ioremap(REG_BASE_PCTRL, 4);
	if (!pctrl) {
		release_mem_region(REG_BASE_PCTRL, 4);
		return false;
	}

	if (on)
		writel((1 << 22), pctrl);
	else
		writel((1 << 22) | (1 << 6), pctrl);

	iounmap(pctrl);
	release_mem_region(REG_BASE_PCTRL, 4);
	return true;
}

static bool set_clkgate(bool on)
{
	void __iomem		*pctrl;
	if (!request_mem_region(REG_BASE_PCTRL, 4, DEVICE_NAME))
		return false;

	pctrl = ioremap(REG_BASE_PCTRL, 4);
	if (!pctrl) {
		release_mem_region(REG_BASE_PCTRL, 4);
		return false;
	}

	if (on)
		writel((1 << 24), pctrl);
	else
		writel((1 << 24) | (1 << 8), pctrl);

	iounmap(pctrl);
	release_mem_region(REG_BASE_PCTRL, 4);
	return true;
}

static struct clk *get_clkacp(void)
{
	struct clk *clkacp = clk_get(NULL, "clk_acp");
	if (IS_ERR(clkacp))
		return NULL;

	return clkacp;
}

/*resources*/
static struct resource k3_dma_resources[] = {
	[0] = {
		.start	= REG_BASE_DMAC,
		.end	= REG_BASE_DMAC + REG_DMAC_IOSIZE - 1,
		.flags	= IORESOURCE_DMA,
	},
	[1] = {
		.start	= IRQ_DMAC,
		.end	= IRQ_DMAC,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct k3dma_platform_data k3_dma_data = {
	.nr_phy_channels	= 16,
	.nr_slave_channels	= DMACH_NUMBER,
	.hasacp = true,
	.cd = {
		[0] = {
			.peri		= DMACH_UART0_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[1] = {
			.peri		= DMACH_UART0_TX,
			.pri		= DMACH_PRIORITY_0,
		},
		[2] = {
			.peri		= DMACH_UART1_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[3] = {
			.peri		= DMACH_UART1_TX,
			.pri		= DMACH_PRIORITY_0,
		},
		[4] = {
			.peri		= DMACH_UART2_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[5] = {
			.peri		= DMACH_UART2_TX,
			.pri		= DMACH_PRIORITY_0,
		},
		[6] = {
			.peri		= DMACH_UART3_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[7] = {
			.peri		= DMACH_UART3_TX,
			.pri		= DMACH_PRIORITY_0,
		},
		[8] = {
			.peri		= DMACH_UART4_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[9] = {
			.peri		= DMACH_UART4_TX,
			.pri		= DMACH_PRIORITY_0,
		},
		[10] = {
			.peri		= DMACH_SPI0_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[11] = {
			.peri		= DMACH_SPI0_TX,
			.pri		= DMACH_PRIORITY_0,
		},
		[12] = {
			.peri		= DMACH_SPI1_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[13] = {
			.peri		= DMACH_SPI1_TX,
			.pri		= DMACH_PRIORITY_0,
		},
		[14] = {
			.peri		= DMACH_SPI2_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[15] = {
			.peri		= DMACH_SPI2_TX,
			.pri		= DMACH_PRIORITY_0,
		},
		[16] = {
			.peri		= DMACH_SCI_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[17] = {
			.peri		= DMACH_SCI_TX,
			.pri		= DMACH_PRIORITY_0,
		},
		[18] = {
			.peri		= DMACH_I2C0_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[19] = {
			.peri		= DMACH_I2C0_TX,
			.pri		= DMACH_PRIORITY_0,
		},
		[20] = {
			.peri		= DMACH_I2C1_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[21] = {
			.peri		= DMACH_I2C1_TX,
			.pri		= DMACH_PRIORITY_0,
		},
		[22] = {
			.peri		= DMACH_GPS_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[23] = {
			.peri		= DMACH_I2C2_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[24] = {
			.peri		= DMACH_I2C2_TX,
			.pri		= DMACH_PRIORITY_0,
		},
		[25] = {
			.peri		= DMACH_I2C3_RX,
			.pri		= DMACH_PRIORITY_0,
		},
		[26] = {
			.peri		= DMACH_I2C3_TX,
			.pri		= DMACH_PRIORITY_0,
		},
	},
	.acp_enable = set_acp,
	.clkgate_enable = set_clkgate,
	.clkacp_get = get_clkacp,
};

static struct platform_device k3_dma_device = {
	.name			= DEVICE_NAME,
	.id			= 0,
	.dev			= {
				.dma_mask		= &k3_dma_mask,
				.coherent_dma_mask	= DMA_BIT_MASK(32),
				.platform_data		= &k3_dma_data,
				.init_name		= DEVICE_NAME,
	},
	.resource	= k3_dma_resources,
	.num_resources	= ARRAY_SIZE(k3_dma_resources),
};

static struct platform_device *k3_dmacs[] __initdata = {
	&k3_dma_device,
};

static int __init k3_dma_init(void)
{
	platform_add_devices(k3_dmacs, ARRAY_SIZE(k3_dmacs));

	return 0;
}
arch_initcall(k3_dma_init);
#endif
