/*
 * hi3630_hdmi_i2s.h -- HI6401 ALSA SoC HI6401 codec driver
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _HI3630_HDMI_I2S_H
#define _HI3630_HDMI_I2S_H

#define HDMI_I2S_ADDR		            (0xE804E400 + 0x200)

#define HI3630_SIO1_ASPIF_SEL           (0x200)
#define HI3630_SIO1_RAW_INT             (0x208)
#define HI3630_SIO1_INT_CLR             (0x20C)
#define HI3630_SIO1_INT_ENABLE          (0x210)
#define HI3630_SIO1_INT_MASKED_STATUS   (0x214)
#define HI3630_SIO1_I2S_SET             (0x21C)
#define HI3630_SIO1_I2S_CLR             (0x220)
#define HI3630_SIO1_TX_STA              (0x22C)
#define HI3630_SIO1_TX_CLR              (0x238)
#define HI3630_SIO1_TST_TX0_DATA        (0x240)
#define HI3630_SIO1_TST_TX1_DATA        (0x244)
#define HI3630_SIO1_TST_TX2_DATA        (0x248)
#define HI3630_SIO1_TST_TX3_DATA        (0x24C)
#define HI3630_SIO1_TST_TX4_DATA        (0x250)
#define HI3630_SIO1_TST_TX5_DATA        (0x254)
#define HI3630_SIO1_TST_TX6_DATA        (0x258)
#define HI3630_SIO1_TST_TX7_DATA        (0x25C)

#define HDMI_I2S_ACC_CTL                (0x1 << 0)

#define HDMI_I2S_TX_EN                  (0x1 << 16)
#define HDMI_I2S_FIFO_DIS               (0x0 << 14)
#define HDMI_I2S_FIFO_THD               (0xF << 4)

#define HDMI_I2S_TX_CLR                 (0x1 << 16)
#define HDMI_I2S_FIFO_DIS_CLR           (0x1 << 14)
#define HDMI_I2S_FIFO_THD_CLR           (0x1F << 4)

struct hi3630_hdmi_i2s_platform_data {
	void		__iomem *reg_base_addr;
	struct resource	*res;
};

#endif
