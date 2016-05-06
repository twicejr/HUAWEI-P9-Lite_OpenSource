/*
 * hi3630_asp_dma.h -- ALSA SoC HI3630 ASP DMA driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __HI3630_PCM_HDMI_H__
#define __HI3630_PCM_HDMI_H__

#include <linux/regulator/consumer.h>

/* HI3630_HDMI base addr */
#define HI3630_HDMI_BASE                            (0xE804E400 - 0xE804E000)

/******************************************************************************/
#define HI3630_ASP_TX3                              (HI3630_HDMI_BASE + 0x0)
#define HI3630_ASP_DMA_EN                           (HI3630_HDMI_BASE + 0x4)
#define HI3630_ASP_DMA_STOP                         (HI3630_HDMI_BASE + 0x8)
#define HI3630_ASP_GLB_INT_STATE                    (HI3630_HDMI_BASE + 0xC)
#define HI3630_ASP_INT_STATE                        (HI3630_HDMI_BASE + 0x10)
#define HI3630_ASP_INT_EN                           (HI3630_HDMI_BASE + 0x14)
#define HI3630_ASP_INT_MSK_STATE                    (HI3630_HDMI_BASE + 0x18)
#define HI3630_ASP_INT_CLR                          (HI3630_HDMI_BASE + 0x1C)
#define HI3630_ASP_PCM_NEW_SNG                      (HI3630_HDMI_BASE + 0x20)
#define HI3630_ASP_RSMP                             (HI3630_HDMI_BASE + 0x24)
#define HI3630_ASP_P30CGR                           (HI3630_HDMI_BASE + 0x28)
#define HI3630_ASP_P31CGR                           (HI3630_HDMI_BASE + 0x2C)
#define HI3630_ASP_P32CGR                           (HI3630_HDMI_BASE + 0x30)
#define HI3630_ASP_P33CGR                           (HI3630_HDMI_BASE + 0x34)
#define HI3630_ASP_P34CGR                           (HI3630_HDMI_BASE + 0x38)
#define HI3630_ASP_P35CGR                           (HI3630_HDMI_BASE + 0x3C)
#define HI3630_ASP_P36CGR                           (HI3630_HDMI_BASE + 0x40)
#define HI3630_ASP_P37CGR                           (HI3630_HDMI_BASE + 0x44)
#define HI3630_ASP_A_ADDR                           (HI3630_HDMI_BASE + 0x48)
#define HI3630_ASP_A_LEN                            (HI3630_HDMI_BASE + 0x4C)
#define HI3630_ASP_B_ADDR                           (HI3630_HDMI_BASE + 0x50)
#define HI3630_ASP_B_LEN                            (HI3630_HDMI_BASE + 0x54)
#define HI3630_ASP_SPDIF_SEL                        (HI3630_HDMI_BASE + 0x58)
#define HI3630_ASP_A_LEN_STATE                      (HI3630_HDMI_BASE + 0x5C)
#define HI3630_ASP_B_LEN_STATE                      (HI3630_HDMI_BASE + 0x60)
#define HI3630_ASP_FDS                              (HI3630_HDMI_BASE + 0x64)
#define HI3630_ASP_A_LEN_LFT                        (HI3630_HDMI_BASE + 0x68)
#define HI3630_ASP_B_LEN_LFT                        (HI3630_HDMI_BASE + 0x6C)
#define HI3630_ASP_SECURE                           (HI3630_HDMI_BASE + 0x70)

#if 1
#define HI3630_SIO1_ASPIF_SEL                      (HI3630_HDMI_BASE + 0x200)
#define HI3630_SIO1_RAW_INT                        (HI3630_HDMI_BASE + 0x208)
#define HI3630_SIO1_INT_CLR                        (HI3630_HDMI_BASE + 0x20C)
#define HI3630_SIO1_INT_ENABLE                     (HI3630_HDMI_BASE + 0x210)
#define HI3630_SIO1_INT_MASKED_STATUS              (HI3630_HDMI_BASE + 0x214)
#define HI3630_SIO1_I2S_SET                        (HI3630_HDMI_BASE + 0x21C)
#define HI3630_SIO1_I2S_CLR                        (HI3630_HDMI_BASE + 0x220)
#define HI3630_SIO1_TX_STA                         (HI3630_HDMI_BASE + 0x22C)
#define HI3630_SIO1_CLR                            (HI3630_HDMI_BASE + 0x238)
#define HI3630_SIO1_TST_TX0_DATA                   (HI3630_HDMI_BASE + 0x240)
#define HI3630_SIO1_TST_TX1_DATA                   (HI3630_HDMI_BASE + 0x244)
#define HI3630_SIO1_TST_TX2_DATA                   (HI3630_HDMI_BASE + 0x248)
#define HI3630_SIO1_TST_TX3_DATA                   (HI3630_HDMI_BASE + 0x24C)
#define HI3630_SIO1_TST_TX4_DATA                   (HI3630_HDMI_BASE + 0x250)
#define HI3630_SIO1_TST_TX5_DATA                   (HI3630_HDMI_BASE + 0x254)
#define HI3630_SIO1_TST_TX6_DATA                   (HI3630_HDMI_BASE + 0x258)
#define HI3630_SIO1_TST_TX7_DATA                   (HI3630_HDMI_BASE + 0x25C)
#endif

#define HI3630_SPDIF_CTRL                          (HI3630_HDMI_BASE + 0x300)
#define HI3630_SPDIF_CONFIG                        (HI3630_HDMI_BASE + 0x304)
#define HI3630_SPDIF_INTRUPT                       (HI3630_HDMI_BASE + 0x308)
#define HI3630_SPDIF_INTR_MASK                     (HI3630_HDMI_BASE + 0x30C)
#define HI3630_SPDIF_FIFO_STATE                    (HI3630_HDMI_BASE + 0x310)
#define HI3630_SPDIF_CH_STATUS1                    (HI3630_HDMI_BASE + 0x320)
#define HI3630_SPDIF_CH_STATUS2                    (HI3630_HDMI_BASE + 0x324)
#define HI3630_SPDIF_CH_STATUS3                    (HI3630_HDMI_BASE + 0x328)
#define HI3630_SPDIF_CH_STATUS4                    (HI3630_HDMI_BASE + 0x32C)
#define HI3630_SPDIF_CH_STATUS5                    (HI3630_HDMI_BASE + 0x330)
#define HI3630_SPDIF_USER_DATA1                    (HI3630_HDMI_BASE + 0x340)
#define HI3630_SPDIF_USER_DATA2                    (HI3630_HDMI_BASE + 0x344)
#define HI3630_SPDIF_USER_DATA3                    (HI3630_HDMI_BASE + 0x348)
#define HI3630_SPDIF_USER_DATA4                    (HI3630_HDMI_BASE + 0x34C)
#define HI3630_SPDIF_USER_DATA5                    (HI3630_HDMI_BASE + 0x350)
#define HI3630_SPDIF_EDITION                       (HI3630_HDMI_BASE + 0x3F0)


//******************************************************************************
//REG FIELD
//******************************************************************************
#define HDMI_DMA_A 0
#define HDMI_DMA_B 1

#define HDMI_DMA_MASK			0x3
#define HDMI_INT_MASK			0x7

#define HDMI_TX3_EN_BIT             (0)
#define HDMI_A_INT_EN_BIT           (0)
#define HDMI_B_INT_EN_BIT           (1)
#define HDMI_BUS_ERR_EN_BIT         (2)

#define HDMI_DMA_A_MASK (0x1 << HDMI_DMA_A)
#define HDMI_DMA_B_MASK (0x1 << HDMI_DMA_B)

#define HI3630_MIN_DMA_TIME_US      20000
#define HI3630_MAX_DMA_TIME_US      22000
#define HI3630_MIN_STOP_DMA_TIME_US 1000
#define HI3630_MAX_STOP_DMA_TIME_US 2000

#define HDMI_BIG_DIAN_BIT		(0x1 << 11)
/*****************************************************************/

enum HI3630_HDMI_STATUS {
	STATUS_HDMI_STOP = 0,
	STATUS_HDMI_RUNNING,
};

enum HI3630_HDMI_WIDTH {
	STEREO_16BIT = 0,
	STEREO_18BIT,
	STEREO_20BIT,
	STEREO_24BIT,
	STEREO_8BIT,
};

struct hi3630_hdmi_data {
	struct hi3630_asp_irq *hi3630_asp_irq;
	struct regulator_bulk_data regu;
	int irq;
	struct device *dev;
};

struct hi3630_hdmi_runtime_data {
	struct hi3630_hdmi_data *pdata;
	spinlock_t lock;
	struct mutex mutex;
	enum HI3630_HDMI_STATUS status;
	bool two_dma_flag;
	unsigned int dma_addr;
	unsigned int period_size;
	int period_cur;
	int period_next;
};

#endif


