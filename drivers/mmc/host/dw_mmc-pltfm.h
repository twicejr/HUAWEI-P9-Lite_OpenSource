/*
 * Synopsys DesignWare Multimedia Card Interface Platform driver
 *
 * Copyright (C) 2012, Samsung Electronics Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _DW_MMC_PLTFM_H_
#define _DW_MMC_PLTFM_H_

#define INTMSK_ALL	0xFFFFFFFF
#define INTMSK_CDETECT	(0x1 << 0)
#define INTMSK_RE	(0x1 << 1)
#define INTMSK_CDONE	(0x1 << 2)
#define INTMSK_DTO	(0x1 << 3)
#define INTMSK_TXDR	(0x1 << 4)
#define INTMSK_RXDR	(0x1 << 5)
#define INTMSK_RCRC	(0x1 << 6)
#define INTMSK_DCRC	(0x1 << 7)
#define INTMSK_RTO	(0x1 << 8)
#define INTMSK_DRTO	(0x1 << 9)
#define INTMSK_HTO	(0x1 << 10)
#define INTMSK_VOLT_SWITCH	(0x1 << 10)
#define INTMSK_FRUN	(0x1 << 11)
#define INTMSK_HLE	(0x1 << 12)
#define INTMSK_SBE	(0x1 << 13)
#define INTMSK_ACD	(0x1 << 14)
#define INTMSK_EBE	(0x1 << 15)
#define INTMSK_DMA	(INTMSK_ACD | INTMSK_RXDR | INTMSK_TXDR)

#define INT_SRC_IDMAC	(0x0)
#define INT_SRC_MINT	(0x1)


#define CMD_RESP_EXP_BIT	(0x1 << 6)
#define CMD_RESP_LENGTH_BIT	(0x1 << 7)
#define CMD_CHECK_CRC_BIT	(0x1 << 8)
#define CMD_DATA_EXP_BIT	(0x1 << 9)
#define CMD_RW_BIT		(0x1 << 10)
#define CMD_TRANSMODE_BIT	(0x1 << 11)
#define CMD_WAIT_PRV_DAT_BIT	(0x1 << 13)
#define CMD_STOP_ABORT_CMD	(0x1 << 14)
#define CMD_SEND_INITIALIZATION	(0x1 << 15)
#define CMD_SEND_CLK_ONLY	(0x1 << 21)
#define CMD_VOLT_SWITCH     (0x1 << 28)
#define CMD_USE_HOLD_REG    (0x1 << 29)
#define CMD_STRT_BIT		(0x1 << 31)
#define CMD_ONLY_CLK		(CMD_STRT_BIT | CMD_SEND_CLK_ONLY | \
						CMD_WAIT_PRV_DAT_BIT)
						
#define CLK_ENABLE	(0x1 << 0)
#define CLK_DISABLE	(0x0 << 0)

#define MMC_CCLK_MAX_24M     (24000000)
#define MMC_CCLK_MAX_25M     (25000000)
#define MMC_CCLK_MAX_48M     (48000000)
#define MMC_CCLK_MAX_50M     (50000000)
#define MMC_CCLK_MAX_80M     (80000000)
#define MMC_CCLK_MAX_96M     (96000000)
#define MMC_CCLK_MAX_100M    (100000000)
#define MMC_CCLK_MAX_150M    (150000000)
#define MMC_CCLK_MAX_180M    (180000000)
#define MMC_CCLK_MAX_200M    (200000000)

#define MMC_EMMC  (0x0)
#define MMC_SD    (0x1)
#define MMC_SDIO  (0x2)

extern int dw_mci_pltfm_register(struct platform_device *pdev,
				const struct dw_mci_drv_data *drv_data);
extern int dw_mci_pltfm_remove(struct platform_device *pdev);
extern const struct dev_pm_ops dw_mci_pltfm_pmops;

#endif /* _DW_MMC_PLTFM_H_ */
