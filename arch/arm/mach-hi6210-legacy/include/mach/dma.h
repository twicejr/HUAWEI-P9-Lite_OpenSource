/*
 * arch/arm/mach-k3v2/include/mach/dma.h
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 * Clockdev definitions and inline macros
 */
#ifndef __MACH_DMA_H
#define __MACH_DMA_H

#include <mach/platform.h>
#include <mach/irqs.h>
#include <linux/dmaengine.h>

#define	DEVICE_NAME			"hidmav300"

/*
 * Dma channels assigned to devices
 */
enum dma_ch {
	DMACH_uart0_RX = 0,
	DMACH_uart0_TX,
	DMACH_uart1_RX,
	DMACH_uart1_TX,
	DMACH_uart2_RX,
	DMACH_uart2_TX,
	DMACH_uart3_RX,
	DMACH_uart3_TX,
	DMACH_uart4_RX,
	DMACH_uart4_TX,
	DMACH_uart5_RX,
	DMACH_uart5_TX,
	DMACH_uart6_RX,
	DMACH_uart6_TX,
#if 0
	DMACH_SPI0_RX,
	DMACH_SPI0_TX,
	DMACH_SPI1_RX,
	DMACH_SPI1_TX,
	DMACH_SPI2_RX,
	DMACH_SPI2_TX,
	DMACH_SCI_RX,
	DMACH_SCI_TX,
	DMACH_I2C0_RX,
	DMACH_I2C0_TX,
	DMACH_I2C1_RX,
	DMACH_I2C1_TX,
	DMACH_GPS_RX,
	DMACH_I2C2_RX,
	DMACH_I2C2_TX,
	DMACH_I2C3_RX,
	DMACH_I2C3_TX,
#endif
	DMACH_NUMBER,
};

/* dma channels priority*/
enum dma_ch_priority {
	DMACH_PRIORITY_0	= 0,
	DMACH_PRIORITY_1,
	DMACH_PRIORITY_2,
	DMACH_PRIORITY_3,
};

/*
 * Default dma param structure
 * used by dma filter function to check matched dma channel
 */
struct k3_def_dma_param {
	int chan_id;
};

#define K3_DMA_PARAM_NAME(req_name)	dma_##req_name

/*
 * Use this macro to define the dma param in device's platform data
 */
#define K3_DEF_DMA_PARAM(req_name)				\
static struct k3_def_dma_param K3_DMA_PARAM_NAME(req_name) =	\
{								\
	.chan_id = DMACH_##req_name,				\
}

/* Default dma filter function */
static inline bool
k3_def_dma_filter(struct dma_chan *chan, void *filter_param) {
	if ((chan == NULL) || (filter_param == NULL))
		return false;

	return (chan->chan_id ==
		((struct k3_def_dma_param *)filter_param)->chan_id);
}

/*channels*/
struct k3dma_channel_data {
	enum dma_ch peri;
	enum dma_ch_priority pri;
};
/*platforms*/
struct k3dma_platform_data {
	u32	nr_phy_channels;
	u32	nr_slave_channels;
	bool	hasacp;
	dma_cap_mask_t	cap_mask;
	struct k3dma_channel_data cd[DMACH_NUMBER];

	bool (*acp_enable)(bool on);
	bool (*clkgate_enable)(bool on);
	struct clk *(*clkacp_get)(void);
};
#endif
