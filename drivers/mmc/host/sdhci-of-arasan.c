/*
 * Arasan Secure Digital Host Controller Interface.
 * Copyright (C) 2011 - 2012 Michal Simek <monstr@monstr.eu>
 * Copyright (c) 2012 Wind River Systems, Inc.
 * Copyright (C) 2013 Pengutronix e.K.
 * Copyright (C) 2013 Xilinx Inc.
 *
 * Based on sdhci-of-esdhc.c
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 * Copyright (c) 2009 MontaVista Software, Inc.
 *
 * Authors: Xiaobo Xie <X.Xie@freescale.com>
 *	    Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 */
/*lint --e{750}*/
#include <linux/module.h>
#include "sdhci-pltfm.h"
#include <linux/dma-mapping.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_address.h>
#include <linux/mmc/mmc.h>
#include <linux/slab.h>
#include <linux/scatterlist.h>
#include <linux/mmc/cmdq_hci.h>
#include <linux/pm_runtime.h>
#include <linux/mmc/card.h>
#ifdef CONFIG_HUAWEI_EMMC_DSM
#include <linux/mmc/mmc.h>
#include <linux/mmc/sdio.h>
#include <linux/mmc/sd.h>
#include <linux/mmc/dsm_emmc.h>
#include <linux/workqueue.h>
#endif

#define CLK_CTRL_TIMEOUT_SHIFT		16
#define CLK_CTRL_TIMEOUT_MASK		(0xf << CLK_CTRL_TIMEOUT_SHIFT)
#define CLK_CTRL_TIMEOUT_MIN_EXP	13

#define SDHCI_ARASAN_MIN_FREQ				400000
#define SDHCI_ARASAN_AHB_CLK_FREQ			120000000
#define SDHCI_ARASAN_XIN_CLK_FREQ			200000000

#define PERI_CRG_RSTEN4   			(0x90)
#define PERI_CRG_RSTDIS4  			(0x94)
#define PERI_CRG_RSTSTAT4			(0x98)

#define HS400_DLL_FREQ_DATA_HI6250  (0x0)
#define HS400_DLL_FREQ_DATA_HI3650  (0x1)
#define HS400_TX_PHASE_HI6250   (0x5)
#define HS400_TX_PHASE_HI3650   (0x6)

#define PERI_CRG_RST_EMMC0_BIT			(0x1 << 16)
static void __iomem *pericrg_base = NULL;

static u32 xin_clk = SDHCI_ARASAN_XIN_CLK_FREQ;
static u32 ahb_clk = SDHCI_ARASAN_AHB_CLK_FREQ;

static u32 hs400_dll_freq_data = HS400_DLL_FREQ_DATA_HI3650;
static u32 hs400_tx_phase = HS400_TX_PHASE_HI3650;

struct sdhci_host *g_sdhci_for_mmctrace;

/**
 * struct sdhci_arasan_data
 * @clk:						Pointer to the sd clock
 * @clk_ahb:					Pointer to the AHB clock
 * @clock:					record current clock rate
 * @tuning_current_sample:		record current sample when soft tuning
 * @tuning_init_sample:			record the optimum sample of soft tuning
 * @tuning_sample_count:		record the tuning count for soft tuning
 * @tuning_move_sample:		record the move sample when data or cmd error occor
 * @tuning_move_count:		record the move count
 * @tuning_sample_flag:			record the sample OK or NOT of soft tuning
 * @tuning_strobe_init_sample:	default strobe sample
 * @tuning_strobe_move_sample:	record the strobe move sample when data or cmd error occor
 * @tuning_strobe_move_count:	record the strobe move count
 */
struct sdhci_arasan_data {
	struct clk *clk;
	struct clk *clk_ahb;
	unsigned int clock;
	unsigned int enhanced_strobe_enabled;
	int tuning_current_sample;
	int tuning_init_sample;
	int tuning_sample_count;
	int tuning_move_sample;
	int tuning_move_count;
	unsigned long tuning_sample_flag;
	int tuning_strobe_init_sample;
	int tuning_strobe_move_sample;
	int tuning_strobe_move_count;
#ifdef CONFIG_HUAWEI_EMMC_DSM
	u64 para;
	u32 cmd_data_status;
	void *data;
	struct work_struct dsm_work;
#endif
};
void __iomem *iosoc_acpu_pmc_base_addr = NULL;
static int sdhci_get_pmctrl_resocure(void)
{
	struct device_node *np = NULL;
	np = of_find_compatible_node(NULL, NULL, "hisilicon,clk-pmctrl");
	if (!np) {
		pr_err("can't find clk-pmctrl!\n");
		return -1;
	} else {
		iosoc_acpu_pmc_base_addr = of_iomap(np, 0);
	}
	if (!iosoc_acpu_pmc_base_addr) {
		pr_err("clk-pmctrl iomap error!\n");
		return -1;
	}
	return 0;
}

static void sdhci_set_strobe_sample(struct sdhci_host *host, unsigned char timing, int sam_phase);

static unsigned int sdhci_arasan_get_min_clock(struct sdhci_host *host)
{
	return SDHCI_ARASAN_MIN_FREQ;
}

static unsigned int sdhci_arasan_get_timeout_clock(struct sdhci_host *host)
{
	u32 div;
	unsigned long freq;
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;

	div = sdhci_readl(host, SDHCI_CLOCK_CONTROL);
	div = (div & CLK_CTRL_TIMEOUT_MASK) >> CLK_CTRL_TIMEOUT_SHIFT;

	freq = clk_get_rate(sdhci_arasan->clk);
	freq /= 1 << (CLK_CTRL_TIMEOUT_MIN_EXP + div);

	pr_debug("%s: freq=%lx\n", __func__, freq);

	return freq;
}

static void sdhci_of_arasan_hardware_reset(struct sdhci_host *host, unsigned char set)
{
	unsigned int loop_count;

	if (pericrg_base == NULL) {
		pr_err("%s: pericrg_base is null, can't reset mmc!\n", __func__);
		return;
	}

	if (set) {					/* eMMC0 reset */
		writel(PERI_CRG_RST_EMMC0_BIT, pericrg_base + PERI_CRG_RSTEN4);
		loop_count = 0xF;
		do {
			if (PERI_CRG_RST_EMMC0_BIT & readl(pericrg_base + PERI_CRG_RSTSTAT4)) {
				break;
			}
			loop_count--;
		} while (loop_count);
		if (!loop_count)
			pr_err("wait eMMC0 reset time out!\n");
		else
			pr_info("%s: rest emmc ok!\n", __func__);
	} else {					/* eMMC0 dis-reset */
		writel(PERI_CRG_RST_EMMC0_BIT, pericrg_base + PERI_CRG_RSTDIS4);
		loop_count = 0xF;
		do {
			if (!(PERI_CRG_RST_EMMC0_BIT & readl(pericrg_base + PERI_CRG_RSTSTAT4))) {
				break;
			}
			loop_count--;
		} while (loop_count);
		if (!loop_count)
			pr_err("wait eMMC0 unreset time out!\n");
		else
			pr_info("%s: unrest emmc ok!\n", __func__);
	}
}

static void sdhci_of_arasan_PHY_set_dll(struct sdhci_host *host, u32 dll_freq_sel)
{
	u32 reg_data = 0;
	unsigned long loop_count = 0;

	if (dll_freq_sel == 0xff) {
		/*disable dll */
		reg_data = sdhci_readl(host, SDHCI_PHY_CTRL1);
		reg_data = reg_data & (~SDHCI_PHY_CTRL1_EN_DLL);
		sdhci_writel(host, reg_data, SDHCI_PHY_CTRL1);
		udelay(10);
		/*enable dll */
		reg_data = sdhci_readl(host, SDHCI_PHY_CTRL1);
		reg_data = reg_data | SDHCI_PHY_CTRL1_EN_DLL;
		sdhci_writel(host, reg_data, SDHCI_PHY_CTRL1);
		udelay(10);
		/*disable dll */
		reg_data = sdhci_readl(host, SDHCI_PHY_CTRL1);
		reg_data = reg_data & (~SDHCI_PHY_CTRL1_EN_DLL);
		sdhci_writel(host, reg_data, SDHCI_PHY_CTRL1);
	} else {
		/*disable dll */
		reg_data = sdhci_readl(host, SDHCI_PHY_CTRL1);
		reg_data = reg_data & (~SDHCI_PHY_CTRL1_EN_DLL);
		sdhci_writel(host, reg_data, SDHCI_PHY_CTRL1);
		udelay(10);
		/*set dll freq */
		reg_data = sdhci_readl(host, SDHCI_PHY_CTRL3);
		reg_data = reg_data & (~(SDHCI_PHY_CTRL3_DLL_FREQ_SEL_MASK << SDHCI_PHY_CTRL3_DLL_FREQ_SEL));
		reg_data = reg_data | ((dll_freq_sel & SDHCI_PHY_CTRL3_DLL_FREQ_SEL_MASK) << SDHCI_PHY_CTRL3_DLL_FREQ_SEL);
		sdhci_writel(host, reg_data, SDHCI_PHY_CTRL3);

		/*enable dll */
		reg_data = sdhci_readl(host, SDHCI_PHY_CTRL1);
		reg_data = reg_data | SDHCI_PHY_CTRL1_EN_DLL;
		sdhci_writel(host, reg_data, SDHCI_PHY_CTRL1);
		/*need to delay 10us after enable dll*/
		udelay(10);

		loop_count = 0x1000;	/*100us for 1GHz cpu */
		do {
			if (SDHCI_PHY_STATUS_DLLRDY & sdhci_readl(host, SDHCI_PHY_STATUS)) {
				break;
			}
			loop_count--;
		} while (loop_count);
		if (!loop_count)
			pr_err("%s: wait DLL ready time out!\n", __func__);


		pr_debug("%s: enable dll done\n", __func__);
	}
}

static void sdhci_of_arasan_PHY_init(struct sdhci_host *host)
{
	u32 reg_data;
	unsigned long loop_count = 0;

	/*  PHY initialization */
	reg_data = sdhci_readl(host, SDHCI_PHY_CTRL1);
	reg_data = reg_data | SDHCI_PHY_CTRL1_EN_RTRIM;
	reg_data = reg_data & (~(SDHCI_PHY_CTRL1_DLL_TRIM_ICP_MASK << SDHCI_PHY_CTRL1_DLL_TRIM_ICP));
	reg_data = reg_data | ((0x4 & SDHCI_PHY_CTRL1_DLL_TRIM_ICP_MASK) << SDHCI_PHY_CTRL1_DLL_TRIM_ICP);
	sdhci_writel(host, reg_data, SDHCI_PHY_CTRL1);

	reg_data = sdhci_readl(host, SDHCI_PHY_CTRL1);
	reg_data = reg_data | SDHCI_PHY_CTRL1_PDB;
	sdhci_writel(host, reg_data, SDHCI_PHY_CTRL1);
	loop_count = 0x1000;		/*100us for 1GHz cpu */
	do {
		if (SDHCI_PHY_STATUS_CALDONE & sdhci_readl(host, SDHCI_PHY_STATUS)) {
			break;
		}
		loop_count--;
	} while (loop_count);
	if (!loop_count)
		pr_err("wait CALDONE time out!\n");

	loop_count = 0xF;
	do {
		if (!(SDHCI_PHY_STATUS_EXR_NINST & sdhci_readl(host, SDHCI_PHY_STATUS))) {
			break;
		}
		loop_count--;
	} while (loop_count);
	if (!loop_count)
		pr_err("wait EXR_NINST time out!\n");

}

static void sdhci_of_arasan_platform_init(struct sdhci_host *host)
{
	u32 reg_data;

	sdhci_of_arasan_PHY_init(host);

	/* configure OD enable */
	reg_data = sdhci_readl(host, SDHCI_PHY_CTRL1);
	reg_data = reg_data | SDHCI_PHY_CTRL1_ODEN_CMD;
	sdhci_writel(host, reg_data, SDHCI_PHY_CTRL1);
	reg_data = 0;
	reg_data = reg_data | (0xFF << SDHCI_PHY_CTRL2_ODEN_DAT);
	sdhci_writel(host, reg_data, SDHCI_PHY_CTRL2);

	pr_debug("%s: end!\n", __func__);
}

static int sdhci_disable_open_drain(struct sdhci_host *host)
{
	u32 reg_data;

	reg_data = sdhci_readl(host, SDHCI_PHY_CTRL1);
	reg_data = reg_data & (~SDHCI_PHY_CTRL1_ODEN_CMD);
	sdhci_writel(host, reg_data, SDHCI_PHY_CTRL1);
	/*enable data cmd pull up, strobe pull down. */
	reg_data = 0x003FF7FC;
	sdhci_writel(host, reg_data, SDHCI_PHY_CTRL2);

	pr_debug("%s\n", __func__);
	return 0;
}

static int sdhci_of_arasan_enable_enhanced_strobe(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;

	sdhci_writew(host, 0x1, SDHCI_ENHANCED_STROBE_EBABLE);
	sdhci_arasan->enhanced_strobe_enabled = 1;
	return 0;
}

static u32 freq_sel_efuse_enable = 0;
static u32 freq_sel_efuse_value = 0;
#define FREQ_SEL_CMDLINE_ENABLE_BIT	(1 << 4)
#define FREQ_SEL_CMDLINE_VALUE_MASK	(0x7)

static int __init early_parse_emmc_freqsel_cmdline(char *arg)
{
	char cmdline_buf[11];
	u32 len = 0;
	int value = 0;

	if (arg) {
		memset(cmdline_buf, 0, sizeof(cmdline_buf));
		len = strlen(arg);
		if (len >= sizeof(cmdline_buf))
			len = sizeof(cmdline_buf) - 1;
		memcpy(cmdline_buf, arg, len);
		value = (int)simple_strtol(cmdline_buf, NULL, 0);
		freq_sel_efuse_enable = ! !(value & FREQ_SEL_CMDLINE_ENABLE_BIT);
		freq_sel_efuse_value = value & FREQ_SEL_CMDLINE_VALUE_MASK;
		pr_err("eMMC freq_sel cmdline, enable:0x%x, value:0x%x\n", freq_sel_efuse_enable, freq_sel_efuse_value);
	} else {
		pr_err("no eMMC freq_sel cmdline\n");
	}
	return 0;
}

early_param("emmc_freqsel", early_parse_emmc_freqsel_cmdline);
static void sdhci_of_arasan_update_phy_control(struct sdhci_host *host, unsigned char timing)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;
	u32 reg_data = 0;
	u32 dll_freq_data = 0xff;
	u32 tx_phase = 0xff;
	u32 rx_phase = 0xff;
	u32 drv_strength = 0x0;
	u32 strb_sel = 0xff;
	u8 enable_ES = 0;
	static unsigned char old_bus_mode = MMC_BUSMODE_OPENDRAIN;

	pr_debug("%s: timing=%d, host->clock=%d\n", __func__, timing, host->clock);
/*
DLL支持50MHz 到 200MHz时钟配置。0: 200-170MHz, 1: 170-140MHz, 2: 140-110MHz, 3: 110-80MHz, 4: 80-50MHz, 7: 200-225MHz
*/
	if ((host->clock <= 200000000) && (host->clock >= 190000000)) {
		if (freq_sel_efuse_enable)
			dll_freq_data = freq_sel_efuse_value;
		else
			dll_freq_data = hs400_dll_freq_data;
	} else if ((host->clock < 190000000) && (host->clock >= 170000000)) {
		dll_freq_data = 0x0;
	} else if ((host->clock < 170000000) && (host->clock >= 140000000)) {
		dll_freq_data = 0x1;
	} else if ((host->clock < 140000000) && (host->clock >= 110000000)) {
		dll_freq_data = 0x2;
	} else if ((host->clock < 110000000) && (host->clock >= 80000000)) {
		dll_freq_data = 0x3;
	} else if ((host->clock < 80000000) && (host->clock >= 50000000)) {
		dll_freq_data = 0x4;
	} else {
		dll_freq_data = 0xff;
		/*OD disable */
		if ((host->clock > 0)
			&& (old_bus_mode != MMC_BUSMODE_PUSHPULL)
			&& (host->mmc->ios.bus_mode == MMC_BUSMODE_PUSHPULL)) {
			sdhci_disable_open_drain(host);
		}
		old_bus_mode = host->mmc->ios.bus_mode;
	}
/*
SDHCI_PHY_CTRL3_OTAPDLYENA:使能手动调整TX时钟相位
SDHCI_PHY_CTRL3_OTAPDLYSEL:TX时钟相位:0-0xF，默认值0
SDHCI_PHY_CTRL3_ITAPDLYENA:使能手动调整RX时钟相位,不使能使使用自动tuning的相位值
初始化时软件配置为不使能
SDHCI_PHY_CTRL3_ITAPDLYSEL:RX时钟相位:0-0x1F，默认值0
SDHCI_PHY_CTRL1_DR_TY:阻抗值，驱动力调整，支持如下四种，默认值0x0
0x0-50欧
0x1-33欧驱动力最强
0x2-66欧
0x3-100欧驱动力最弱
0x4-40欧
*/
	if (timing == MMC_TIMING_MMC_HS400) {
		tx_phase = hs400_tx_phase;
		rx_phase = sdhci_arasan->tuning_move_sample;
		drv_strength = 0x4;
		strb_sel = sdhci_arasan->tuning_strobe_move_sample;
		if (sdhci_arasan->enhanced_strobe_enabled)
			enable_ES = 1;
	} else if (timing == MMC_TIMING_MMC_HS200) {
		tx_phase = 0x7;
		rx_phase = sdhci_arasan->tuning_move_sample;
		drv_strength = 0x4;
	} else if ((timing == MMC_TIMING_UHS_DDR50) || (timing == MMC_TIMING_MMC_DDR52)) {
		tx_phase = 0x4;
		rx_phase = 0x0;
		drv_strength = 0x4;
	} else if (timing == MMC_TIMING_MMC_HS) {
		tx_phase = 0xff;
		rx_phase = 0xff;
		drv_strength = 0x4;
		dll_freq_data = 0xff;
	} else {
		tx_phase = 0xff;
		rx_phase = 0xff;
		drv_strength = 0x0;
		dll_freq_data = 0xff;
	}

/*set tx phase*/
	reg_data = sdhci_readl(host, SDHCI_PHY_CTRL3);
	if (tx_phase == 0xff) {		/*disable tx phase */
		reg_data = reg_data & (~SDHCI_PHY_CTRL3_OTAPDLYENA);
	} else {
		reg_data = reg_data | SDHCI_PHY_CTRL3_OTAPDLYENA;
		reg_data = reg_data & (~(SDHCI_PHY_CTRL3_OTAPDLYSEL_MASK << SDHCI_PHY_CTRL3_OTAPDLYSEL));
		reg_data = reg_data | ((tx_phase & SDHCI_PHY_CTRL3_OTAPDLYSEL_MASK) << SDHCI_PHY_CTRL3_OTAPDLYSEL);
	}
	sdhci_writel(host, reg_data, SDHCI_PHY_CTRL3);
	pr_debug("%s: set tx=0X%x phase done!\n", __func__, tx_phase);
/*set rx phase*/
	reg_data = sdhci_readl(host, SDHCI_PHY_CTRL3);
	if (rx_phase == 0xff) {		/*disable rx phase */
		reg_data = reg_data & (~SDHCI_PHY_CTRL3_ITAPDLYENA);
	} else {
		reg_data = reg_data | SDHCI_PHY_CTRL3_ITAPDLYENA;
		reg_data = reg_data & (~(SDHCI_PHY_CTRL3_ITAPDLYSEL_MASK << SDHCI_PHY_CTRL3_ITAPDLYSEL));
		reg_data = reg_data | ((rx_phase & SDHCI_PHY_CTRL3_ITAPDLYSEL_MASK) << SDHCI_PHY_CTRL3_ITAPDLYSEL);
	}
	sdhci_writel(host, reg_data, SDHCI_PHY_CTRL3);
	pr_debug("%s: set rx=0X%x phase done!\n", __func__, rx_phase);
/*set strbsel*/
	sdhci_set_strobe_sample(host, timing, strb_sel);
/*set drv strength*/
	reg_data = sdhci_readl(host, SDHCI_PHY_CTRL1);
	reg_data = reg_data & (~(SDHCI_PHY_CTRL1_DR_TY_MASK << SDHCI_PHY_CTRL1_DR_TY));
	reg_data = reg_data | ((drv_strength & SDHCI_PHY_CTRL1_DR_TY_MASK) << SDHCI_PHY_CTRL1_DR_TY);
	sdhci_writel(host, reg_data, SDHCI_PHY_CTRL1);
	pr_debug("%s: config drv strength =0X%x done!\n", __func__, drv_strength);
/*set dll*/
	sdhci_of_arasan_PHY_set_dll(host, dll_freq_data);
/*set enhanced strobe*/
	if (enable_ES)
		sdhci_writew(host, 0x1, SDHCI_ENHANCED_STROBE_EBABLE);
	else
		sdhci_writew(host, 0x0, SDHCI_ENHANCED_STROBE_EBABLE);
}

#define SDHCI_TUNING_MIN_SAMPLE		0
#define SDHCI_TUNING_MAX_SAMPLE		31
#define MAX_TUNING_LOOP 				32
#define SDHCI_TUNING_COUNT			64
#define SDHCI_TUNING_STROBE_MIN_SAMPLE		0
#define SDHCI_TUNING_STROBE_MAX_SAMPLE		3

/*to init tuning para before soft tuning*/
static void sdhci_of_arasan_init_tuning_para(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;

	pr_err("%s enter\n", __func__);
	sdhci_arasan->tuning_current_sample = -1;
	sdhci_arasan->tuning_init_sample = 0xff;
	sdhci_arasan->tuning_sample_count = 0;
	sdhci_arasan->tuning_move_sample = 0xff;
	sdhci_arasan->tuning_move_count = 0;
	sdhci_arasan->tuning_strobe_init_sample = 0;	/* 0x0, 0x1, 0x2, 0x3 */
	sdhci_arasan->tuning_strobe_move_sample = 0xff;
	sdhci_arasan->tuning_strobe_move_count = 0;
	sdhci_arasan->tuning_sample_flag = 0;
}

static void sdhci_set_strobe_sample(struct sdhci_host *host, unsigned char timing, int sam_phase)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;
	u32 reg_data = 0;
	u32 sam_phase_set = 0;

	reg_data = sdhci_readl(host, SDHCI_PHY_CTRL3);
	reg_data = reg_data & (~(SDHCI_PHY_CTRL3_STRBSEL_MASK << SDHCI_PHY_CTRL3_STRBSEL));
	if (sam_phase == 0xff) {	/*use default strbsel 0x0 */
		sam_phase_set = sdhci_arasan->tuning_strobe_init_sample;
	} else {
		sam_phase_set = sam_phase;
	}
	/* 0x0, 0x5, 0xa, 0xf */
	sam_phase_set += (sam_phase_set << 2);
	reg_data = reg_data | ((sam_phase_set & SDHCI_PHY_CTRL3_STRBSEL_MASK) << SDHCI_PHY_CTRL3_STRBSEL);
	sdhci_writel(host, reg_data, SDHCI_PHY_CTRL3);
	pr_debug("%s: timing=%d, sam_phase_set=0X%x\n", __func__, timing, sam_phase_set);
}

static void sdhci_set_sample(struct sdhci_host *host, unsigned char timing, int sam_phase)
{
	u32 reg_data = 0;

	pr_debug("%s: timing=%d,sam_phase=0X%x\n", __func__, timing, sam_phase);

	reg_data = sdhci_readl(host, SDHCI_PHY_CTRL3);
	if (sam_phase == 0xff) {
		reg_data = reg_data & (~SDHCI_PHY_CTRL3_ITAPDLYENA);
		reg_data = reg_data & (~(SDHCI_PHY_CTRL3_ITAPDLYSEL_MASK << SDHCI_PHY_CTRL3_ITAPDLYSEL));
	} else {
		reg_data = reg_data | SDHCI_PHY_CTRL3_ITAPDLYENA;
		reg_data = reg_data | SDHCI_PHY_CTRL3_ITAPCHGWIN;
		reg_data = reg_data & (~(SDHCI_PHY_CTRL3_ITAPDLYSEL_MASK << SDHCI_PHY_CTRL3_ITAPDLYSEL));
		reg_data = reg_data | ((sam_phase & SDHCI_PHY_CTRL3_ITAPDLYSEL_MASK) << SDHCI_PHY_CTRL3_ITAPDLYSEL);
		sdhci_writel(host, reg_data, SDHCI_PHY_CTRL3);
		udelay(10);
		reg_data = sdhci_readl(host, SDHCI_PHY_CTRL3);
		reg_data = reg_data & (~SDHCI_PHY_CTRL3_ITAPCHGWIN);
	}
	sdhci_writel(host, reg_data, SDHCI_PHY_CTRL3);
	pr_debug("%s: timing=%d,SDHCI_PHY_CTRL3=0X%x\n", __func__, timing, sdhci_readl(host, SDHCI_PHY_CTRL3));
}

static void sdhci_tuning_clear_flags(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;

	pr_debug("%s\n", __func__);
	sdhci_arasan->tuning_sample_flag = (unsigned long)0;
}

static void sdhci_tuning_set_flags(struct sdhci_host *host, int sample, int ok)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;

	pr_debug("%s: tuning_sample_flag=0X%lx, sample = 0X%x, flag=0X%x\n", __func__, sdhci_arasan->tuning_sample_flag, sample, ok);
	if (ok)
		sdhci_arasan->tuning_sample_flag |= ((unsigned long)1 << sample);
	else
		sdhci_arasan->tuning_sample_flag &= ~((unsigned long)1 << sample);
}

/* By tuning, find the best timing condition
 *  1 -- tuning is not finished. And this function should be called again
 *  0 -- Tuning successfully.
 *    If this function be called again, another round of tuning would be start
 *  -1 -- Tuning failed. Maybe slow down the clock and call this function again
 */
static int sdhci_of_arasan_tuning_find_condition(struct sdhci_host *host, unsigned char timing)
{
	int i, j;
	int ret = -1;
	unsigned long mask;
	int mask_lenth;
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;

	pr_debug("%s: timing is %d, tuning_current_sample = 0X%x, tuning_init_sample=0X%x\n", __func__, timing, sdhci_arasan->tuning_current_sample, sdhci_arasan->tuning_init_sample);

	if (SDHCI_TUNING_MAX_SAMPLE == SDHCI_TUNING_MIN_SAMPLE) {
		sdhci_arasan->tuning_init_sample = (SDHCI_TUNING_MAX_SAMPLE + SDHCI_TUNING_MIN_SAMPLE) / 2;
		sdhci_set_sample(host, timing, sdhci_arasan->tuning_init_sample);
		pr_debug("%s: no need tuning: timing is %d, tuning sample = %d\n", __func__, timing, sdhci_arasan->tuning_init_sample);
		return 0;
	}

	if (-1 == sdhci_arasan->tuning_current_sample) {
		sdhci_tuning_clear_flags(host);
		/* set the first sam del as the min_sam_del */
		sdhci_arasan->tuning_current_sample = SDHCI_TUNING_MIN_SAMPLE;
		/* a trick for next "++" */
		sdhci_arasan->tuning_current_sample--;
	}

	if (sdhci_arasan->tuning_sample_count >= MAX_TUNING_LOOP) {
		/*use 0-31 fill 32-64 bits. */
		sdhci_arasan->tuning_sample_flag |= ((sdhci_arasan->tuning_sample_flag & ((1UL << (SDHCI_TUNING_COUNT - MAX_TUNING_LOOP)) - 1)) << MAX_TUNING_LOOP);

		/* tuning finish, select the best sam_del */
		/* set sam del to -1, for next tuning */
		sdhci_arasan->tuning_current_sample = -1;
		sdhci_arasan->tuning_init_sample = 0xff;
		for (mask_lenth = (((SDHCI_TUNING_COUNT - 1 - SDHCI_TUNING_MIN_SAMPLE) >> 1) << 1) + 1; mask_lenth >= 1; mask_lenth -= 2) {
			mask = ((unsigned long)1 << mask_lenth) - 1;
			for (i = (SDHCI_TUNING_MIN_SAMPLE + SDHCI_TUNING_COUNT - 1 - mask_lenth + 1) / 2, j = 1; (i <= SDHCI_TUNING_COUNT - 1 - mask_lenth + 1) && (i >= SDHCI_TUNING_MIN_SAMPLE); i = ((SDHCI_TUNING_MIN_SAMPLE + SDHCI_TUNING_COUNT - 1 - mask_lenth + 1) / 2) + ((j % 2) ? -1 : 1) * (j / 2)) {
				if ((sdhci_arasan->tuning_sample_flag & (mask << i)) == (mask << i)) {
					sdhci_arasan->tuning_init_sample = i + mask_lenth / 2;
					break;
				}

				j++;
			}
			if (sdhci_arasan->tuning_init_sample != 0xff) {
				if (sdhci_arasan->tuning_init_sample >= MAX_TUNING_LOOP) {
					sdhci_arasan->tuning_init_sample = sdhci_arasan->tuning_init_sample - MAX_TUNING_LOOP;
				}
				pr_err("kernel tuning OK: timing is %d, tuning sample = %d, tuning_flag = 0x%lx\n", timing, sdhci_arasan->tuning_init_sample, sdhci_arasan->tuning_sample_flag);
				ret = 0;
				break;
			}
		}
		if (ret) {
			pr_err("tuning err: no good sam_del, " "timing is %d, tuning_init_sample=%d, tuning_flag = 0x%lx.\n", timing, sdhci_arasan->tuning_init_sample, sdhci_arasan->tuning_sample_flag);
			ret = -1;
			sdhci_set_sample(host, timing, sdhci_arasan->tuning_init_sample);
		}
		/* soft done, then still use auto tuning */
		sdhci_set_sample(host, timing, 0xff);
	} else {
		sdhci_arasan->tuning_current_sample++;
		sdhci_arasan->tuning_sample_count++;
		if (sdhci_arasan->tuning_current_sample > SDHCI_TUNING_MAX_SAMPLE) {
			sdhci_arasan->tuning_current_sample = SDHCI_TUNING_MIN_SAMPLE;
		}
		sdhci_set_sample(host, timing, sdhci_arasan->tuning_current_sample);
		ret = 1;
	}
	return ret;
}

static void sdhci_of_arasan_tuning_set_current_state(struct sdhci_host *host, int ok)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;

	sdhci_tuning_set_flags(host, sdhci_arasan->tuning_sample_count - 1, ok);
}

static int sdhci_of_arasan_tuning_move_strobe(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;
	int loop = 0;
	int ret = 0;

	/* first move tuning, set soft tuning optimum strobe sample. When second or more move tuning, use the sample near optimum sample */
	for (loop = 0; loop < 2; loop++) {
		sdhci_arasan->tuning_strobe_move_count++;
		sdhci_arasan->tuning_strobe_move_sample = sdhci_arasan->tuning_strobe_init_sample + ((sdhci_arasan->tuning_strobe_move_count % 2) ? 1 : -1) * (sdhci_arasan->tuning_strobe_move_count / 2);

		if ((sdhci_arasan->tuning_strobe_move_sample > SDHCI_TUNING_STROBE_MAX_SAMPLE) || (sdhci_arasan->tuning_strobe_move_sample < SDHCI_TUNING_STROBE_MIN_SAMPLE)) {
			continue;
		} else {
			break;
		}
	}
	if ((sdhci_arasan->tuning_strobe_move_sample > SDHCI_TUNING_STROBE_MAX_SAMPLE) || (sdhci_arasan->tuning_strobe_move_sample < SDHCI_TUNING_STROBE_MIN_SAMPLE)) {
		pr_err("%s: tuning strobe move fail.\n", __func__);
		sdhci_arasan->tuning_strobe_move_sample = 0xff;
		ret = -1;
	} else {
		sdhci_set_strobe_sample(host, host->mmc->ios.timing, sdhci_arasan->tuning_strobe_move_sample);
		pr_err("%s: tuning strobe move to sample=%d\n", __func__, sdhci_arasan->tuning_strobe_move_sample);
	}
	return ret;
}

static int sdhci_of_arasan_tuning_move_clk(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;
	int loop = 0;
	int ret = 0;

	/* soft tuning fail or error then return error */
	if (sdhci_arasan->tuning_init_sample > SDHCI_TUNING_MAX_SAMPLE) {
		pr_err("%s: soft tuning fail, can not move tuning, tuning_init_sample=%d.\n", __func__, sdhci_arasan->tuning_init_sample);
		return -1;
	}
	/* first move tuning, set soft tuning optimum sample. When second or more move tuning, use the sample near optimum sample */
	for (loop = 0; loop < 2; loop++) {
		sdhci_arasan->tuning_move_count++;
		sdhci_arasan->tuning_move_sample = sdhci_arasan->tuning_init_sample + ((sdhci_arasan->tuning_move_count % 2) ? 1 : -1) * (sdhci_arasan->tuning_move_count / 2);

		if ((sdhci_arasan->tuning_move_sample > SDHCI_TUNING_MAX_SAMPLE) || (sdhci_arasan->tuning_move_sample < SDHCI_TUNING_MIN_SAMPLE)) {
			continue;
		} else {
			break;
		}
	}
	if ((sdhci_arasan->tuning_move_sample > SDHCI_TUNING_MAX_SAMPLE) || (sdhci_arasan->tuning_move_sample < SDHCI_TUNING_MIN_SAMPLE)) {
		pr_err("%s: tuning move fail.\n", __func__);
		sdhci_arasan->tuning_move_sample = 0xff;
		ret = -1;
	} else {
		sdhci_set_sample(host, host->mmc->ios.timing, sdhci_arasan->tuning_move_sample);
		pr_err("%s: tuning move to sample=%d\n", __func__, sdhci_arasan->tuning_move_sample);
	}
	return ret;
}

/*
struct sdhci_host *host	:	sdhci host point.
int is_move_strobe		:	1-move strobe phase; 0-move clk phase.
int flag				:	1-reset move_count; 0-tuning move without reset.
*/
static int sdhci_of_arasan_tuning_move(struct sdhci_host *host, int is_move_strobe, int flag)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;

	/* set tuning_strobe_move_count to 0, next tuning move will begin from optimum sample */
	if (flag) {
		sdhci_arasan->tuning_move_count = 0;
		sdhci_arasan->tuning_strobe_move_count = 0;
		return 0;
	}

	if (is_move_strobe) {
		return sdhci_of_arasan_tuning_move_strobe(host);
	} else {
		return sdhci_of_arasan_tuning_move_clk(host);
	}
}

static const u8 tuning_blk_pattern_4bit[] = {
	0xff, 0x0f, 0xff, 0x00, 0xff, 0xcc, 0xc3, 0xcc,
	0xc3, 0x3c, 0xcc, 0xff, 0xfe, 0xff, 0xfe, 0xef,
	0xff, 0xdf, 0xff, 0xdd, 0xff, 0xfb, 0xff, 0xfb,
	0xbf, 0xff, 0x7f, 0xff, 0x77, 0xf7, 0xbd, 0xef,
	0xff, 0xf0, 0xff, 0xf0, 0x0f, 0xfc, 0xcc, 0x3c,
	0xcc, 0x33, 0xcc, 0xcf, 0xff, 0xef, 0xff, 0xee,
	0xff, 0xfd, 0xff, 0xfd, 0xdf, 0xff, 0xbf, 0xff,
	0xbb, 0xff, 0xf7, 0xff, 0xf7, 0x7f, 0x7b, 0xde,
};

static const u8 tuning_blk_pattern_8bit[] = {
	0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00,
	0xff, 0xff, 0xcc, 0xcc, 0xcc, 0x33, 0xcc, 0xcc,
	0xcc, 0x33, 0x33, 0xcc, 0xcc, 0xcc, 0xff, 0xff,
	0xff, 0xee, 0xff, 0xff, 0xff, 0xee, 0xee, 0xff,
	0xff, 0xff, 0xdd, 0xff, 0xff, 0xff, 0xdd, 0xdd,
	0xff, 0xff, 0xff, 0xbb, 0xff, 0xff, 0xff, 0xbb,
	0xbb, 0xff, 0xff, 0xff, 0x77, 0xff, 0xff, 0xff,
	0x77, 0x77, 0xff, 0x77, 0xbb, 0xdd, 0xee, 0xff,
	0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00,
	0x00, 0xff, 0xff, 0xcc, 0xcc, 0xcc, 0x33, 0xcc,
	0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc, 0xcc, 0xff,
	0xff, 0xff, 0xee, 0xff, 0xff, 0xff, 0xee, 0xee,
	0xff, 0xff, 0xff, 0xdd, 0xff, 0xff, 0xff, 0xdd,
	0xdd, 0xff, 0xff, 0xff, 0xbb, 0xff, 0xff, 0xff,
	0xbb, 0xbb, 0xff, 0xff, 0xff, 0x77, 0xff, 0xff,
	0xff, 0x77, 0x77, 0xff, 0x77, 0xbb, 0xdd, 0xee,
};

static int sdhci_of_arasan_tuning_soft(struct sdhci_host *host, u32 opcode)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;
	int tuning_loop_counter = MAX_TUNING_LOOP;
	int ret = 0;
	const u8 *tuning_blk_pattern = NULL;
	u8 *tuning_blk = NULL;
	int blksz = 0;

	/* soft tuning will be execute only once */
	if ((sdhci_arasan->tuning_init_sample <= SDHCI_TUNING_MAX_SAMPLE)
		&& (sdhci_arasan->tuning_init_sample >= SDHCI_TUNING_MIN_SAMPLE)) {
		pr_err("%s: no need soft tuning, tuning_init_sample=%d\n", __func__, sdhci_arasan->tuning_init_sample);
		return ret;
	}

	if (opcode == MMC_SEND_TUNING_BLOCK_HS200) {
		if (host->mmc->ios.bus_width == MMC_BUS_WIDTH_8) {
			tuning_blk_pattern = tuning_blk_pattern_8bit;
			blksz = 128;
		} else if (host->mmc->ios.bus_width == MMC_BUS_WIDTH_4) {
			tuning_blk_pattern = tuning_blk_pattern_4bit;
			blksz = 64;
		}
	} else {
		tuning_blk_pattern = tuning_blk_pattern_4bit;
		blksz = 64;
	}
	tuning_blk = kmalloc(blksz, GFP_KERNEL);
	if (!tuning_blk)
		return -ENOMEM;

	do {
		struct mmc_request mrq = { NULL };
		struct mmc_command cmd = { 0 };
		struct mmc_data data = { 0 };
		struct scatterlist sg;

		cmd.opcode = opcode;
		cmd.arg = 0;
		cmd.flags = MMC_RSP_R1 | MMC_CMD_ADTC;
		cmd.error = 0;

		data.blksz = blksz;
		data.blocks = 1;
		data.flags = MMC_DATA_READ;
		data.sg = &sg;
		data.sg_len = 1;
		data.error = 0;

		sg_init_one(&sg, tuning_blk, blksz);

		mrq.cmd = &cmd;
		mrq.data = &data;

		ret = sdhci_of_arasan_tuning_find_condition(host, host->mmc->ios.timing);
		if (ret == 0) {			/* tuning ok */
			break;
		} else if (ret == -1) {	/* tuning fail */
			break;
		}
		mmc_wait_for_req(host->mmc, &mrq);
		/* no cmd or data error and tuning data is ok, then set sample flag */
		if (!cmd.error && !data.error && (memcmp(tuning_blk, tuning_blk_pattern, sizeof(blksz)) == 0)) {
			sdhci_of_arasan_tuning_set_current_state(host, 1);
		} else {
			sdhci_of_arasan_tuning_set_current_state(host, 0);
			dev_dbg(&host->mmc->class_dev, "Tuning error: cmd.error:%d, data.error:%d\n", cmd.error, data.error);
		}
	} while (tuning_loop_counter--);
	kfree(tuning_blk);

	return ret;
}

static struct sdhci_ops sdhci_arasan_ops = {
	.get_min_clock = sdhci_arasan_get_min_clock,
	.set_clock = sdhci_set_clock,
	.get_max_clock = sdhci_pltfm_clk_get_max_clock,
	.get_timeout_clock = sdhci_arasan_get_timeout_clock,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_signaling = sdhci_set_uhs_signaling,
	.platform_init = sdhci_of_arasan_platform_init,
	.update_phy_control = sdhci_of_arasan_update_phy_control,
	.tuning_soft = sdhci_of_arasan_tuning_soft,
	.tuning_move = sdhci_of_arasan_tuning_move,
	.enable_enhanced_strobe = sdhci_of_arasan_enable_enhanced_strobe,
	.init_tuning_para = sdhci_of_arasan_init_tuning_para,
};

static struct sdhci_pltfm_data sdhci_arasan_pdata = {
	.ops = &sdhci_arasan_ops,
};

#ifdef CONFIG_PM_SLEEP
/**
 * sdhci_arasan_suspend - Suspend method for the driver
 * @dev:	Address of the device structure
 * Returns 0 on success and error value on error
 *
 * Put the device in a low power state.
 */
static int sdhci_arasan_suspend(struct device *dev)
{
	int ret;
	struct sdhci_host *host = dev_get_drvdata(dev);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;

	dev_info(dev, "%s: suspend +\n", __func__);

	pm_runtime_get_sync(dev);

	ret = sdhci_suspend_host(host);
	if (ret)
		return ret;

	clk_disable_unprepare(sdhci_arasan->clk);

	/*disable dll then enable dll & wait ready, finally disable dll again. */
	sdhci_of_arasan_PHY_set_dll(host, 0xff);

	clk_disable_unprepare(sdhci_arasan->clk_ahb);

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	dev_info(dev, "%s: suspend -\n", __func__);

	return 0;
}

/**
 * sdhci_arasan_resume - Resume method for the driver
 * @dev:	Address of the device structure
 * Returns 0 on success and error value on error
 *
 * Resume operation after suspend
 */
static int sdhci_arasan_resume(struct device *dev)
{
	int ret;
	struct sdhci_host *host = dev_get_drvdata(dev);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;
	u32 dll_freq_data = 0xff;

	dev_info(dev, "%s: resume +\n", __func__);

	sdhci_of_arasan_hardware_reset(host, 1);
	sdhci_of_arasan_hardware_reset(host, 0);

	pm_runtime_get_sync(dev);

	ret = clk_set_rate(sdhci_arasan->clk_ahb, ahb_clk);
	if (ret)
		dev_err(dev, "Error setting desired ahb_clk=%u, get clk=%lu.\n", ahb_clk, clk_get_rate(sdhci_arasan->clk_ahb));
	ret = clk_prepare_enable(sdhci_arasan->clk_ahb);
	if (ret) {
		dev_err(dev, "Cannot enable AHB clock.\n");
		return ret;
	}

	ret = clk_set_rate(sdhci_arasan->clk, xin_clk);
	if (ret)
		dev_err(dev, "Error setting desired xin_clk=%u, get clk=%lu.\n", xin_clk, clk_get_rate(sdhci_arasan->clk));
	ret = clk_prepare_enable(sdhci_arasan->clk);
	if (ret) {
		dev_err(dev, "Cannot enable SD clock.\n");
		clk_disable_unprepare(sdhci_arasan->clk_ahb);
		return ret;
	}
	pr_debug("%s: sdhci_arasan->clk_ahb=%lu, sdhci_arasan->clk=%lu.\n", __func__, clk_get_rate(sdhci_arasan->clk_ahb), clk_get_rate(sdhci_arasan->clk));

	sdhci_of_arasan_PHY_init(host);
	sdhci_disable_open_drain(host);

	pr_debug("%s: host->mmc->ios.clock=%d, timing=%d.\n", __func__, host->mmc->ios.clock, host->mmc->ios.timing);

	/*use soft tuning sample send wake up cmd then retuning */
	if (host->mmc->ios.timing >= MMC_TIMING_MMC_HS200) {
		pr_info("%s: tuning_move_sample=%d, tuning_init_sample=%d, tuning_strobe_move_sample=%d, tuning_strobe_init_sample=%d.\n", __func__, sdhci_arasan->tuning_move_sample, sdhci_arasan->tuning_init_sample, sdhci_arasan->tuning_strobe_move_sample, sdhci_arasan->tuning_strobe_init_sample);
		if (sdhci_arasan->tuning_move_sample == 0xff) {
			sdhci_arasan->tuning_move_sample = sdhci_arasan->tuning_init_sample;
		}
		sdhci_set_sample(host, host->mmc->ios.timing, sdhci_arasan->tuning_move_sample);
		if (sdhci_arasan->tuning_strobe_move_sample == 0xff) {
			sdhci_arasan->tuning_strobe_move_sample = sdhci_arasan->tuning_strobe_init_sample;
		}
		sdhci_set_strobe_sample(host, host->mmc->ios.timing, sdhci_arasan->tuning_strobe_move_sample);

		/*START for emmc data crc & end bit error when resume first transfer data. */
		sdhci_set_clock(host, host->mmc->ios.clock);
		if ((host->mmc->ios.clock <= 200000000) && (host->mmc->ios.clock >= 190000000)) {
			if (freq_sel_efuse_enable)
				dll_freq_data = freq_sel_efuse_value;
			else
				dll_freq_data = hs400_dll_freq_data;
		}
		else if ((host->mmc->ios.clock < 190000000) && (host->mmc->ios.clock >= 170000000)) {
			dll_freq_data = 0x0;
		}
		else if ((host->mmc->ios.clock < 170000000) && (host->mmc->ios.clock >= 140000000)) {
			dll_freq_data = 0x1;
		}
		else if ((host->mmc->ios.clock < 140000000) && (host->mmc->ios.clock >= 110000000)) {
			dll_freq_data = 0x2;
		}
		else if ((host->mmc->ios.clock < 110000000) && (host->mmc->ios.clock >= 80000000)) {
			dll_freq_data = 0x3;
		}
		else if ((host->mmc->ios.clock < 80000000) && (host->mmc->ios.clock >= 50000000)) {
			dll_freq_data = 0x4;
		}
		else {
			dll_freq_data = 0xff;
		}
		sdhci_of_arasan_PHY_set_dll(host, dll_freq_data);
		/*END for emmc data crc & end bit error when resume first transfer data.*/
	}

	ret = sdhci_resume_host(host);
	if (ret)
		return ret;

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	dev_info(dev, "%s: resume -\n", __func__);

	return 0;
}
#endif /* ! CONFIG_PM_SLEEP */

#ifdef CONFIG_PM
static int sdhci_arasan_runtime_suspend(struct device *dev)
{
	struct sdhci_host *host = dev_get_drvdata(dev);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;
	int ret = 0;

	ret = sdhci_runtime_suspend_host(host);

	if (!IS_ERR(sdhci_arasan->clk))
		clk_disable_unprepare(sdhci_arasan->clk);

	/*disable dll then enable dll & wait ready, finally disable dll again. */
	sdhci_of_arasan_PHY_set_dll(host, 0xff);

	if (!IS_ERR(sdhci_arasan->clk_ahb))
		clk_disable_unprepare(sdhci_arasan->clk_ahb);

	return ret;
}

static int sdhci_arasan_runtime_resume(struct device *dev)
{
	struct sdhci_host *host = dev_get_drvdata(dev);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;

	if (!IS_ERR(sdhci_arasan->clk_ahb)) {
		if (clk_prepare_enable(sdhci_arasan->clk_ahb))
			pr_warn("%s: clk_prepare_enable clk_ahb failed.\n", __func__);
	}

	if (!IS_ERR(sdhci_arasan->clk)) {
		if (clk_prepare_enable(sdhci_arasan->clk))
			pr_warn("%s: clk_prepare_enable sdhci_arasan->clk failed.\n", __func__);
	}

	sdhci_of_arasan_PHY_init(host);
	sdhci_disable_open_drain(host);

	return sdhci_runtime_resume_host(host);
}
#endif

static const struct dev_pm_ops sdhci_arasan_dev_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(sdhci_arasan_suspend, sdhci_arasan_resume)
	SET_RUNTIME_PM_OPS(sdhci_arasan_runtime_suspend, sdhci_arasan_runtime_resume,
						   NULL)
};

static int sdhci_arasan_get_resource(void)
{
	struct device_node *np = NULL;

	if (!pericrg_base) {
		np = of_find_compatible_node(NULL, NULL, "Hisilicon,crgctrl");
		if (!np) {
			printk("can't find crgctrl!\n");
			return -1;
		}
		pericrg_base = of_iomap(np, 0);
		if (!pericrg_base) {
			printk("crgctrl iomap error!\n");
			return -1;
		}
	}
	return 0;
}

#ifdef CONFIG_HUAWEI_EMMC_DSM
void sdhci_dsm_set_host_status(struct sdhci_host *host, u32 error_bits)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;
	sdhci_arasan->cmd_data_status |= error_bits;
}

#ifdef CONFIG_MMC_CQ_HCI
void sdhci_cmdq_dsm_set_host_status(struct sdhci_host *host, u32 error_bits)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;
	if (error_bits != -1U)
		sdhci_arasan->para = ((error_bits << 16) | 0x8000000000000000ULL);
	else
		sdhci_arasan->para = 0;	// timeout
}

void sdhci_cmdq_dsm_work(struct cmdq_host *cq_host, bool dsm)
{
	struct mmc_card *card;
	struct sdhci_host *host = mmc_priv(cq_host->mmc);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;

	u32 error_bits, opcode;
	u64 para;
	unsigned long flags;
	spin_lock_irqsave(&cq_host->cmdq_lock, flags);
	para = sdhci_arasan->para;
	sdhci_arasan->para = 0;
	spin_unlock_irqrestore(&cq_host->cmdq_lock, flags);
	if (!dsm)
		return;
	card = host->mmc->card;
	opcode = para & 0x3f;
	error_bits = ((para >> 16) & 0xffffffff);
	if (para & 0x8000000000000000ULL) {
		DSM_EMMC_LOG(card, DSM_EMMC_HOST_ERR, "opcode:%d failed, status:%x\n", opcode, error_bits);
	} else {
		DSM_EMMC_LOG(card, DSM_EMMC_RW_TIMEOUT_ERR, "opcode:%d failed, status:%x\n", opcode, error_bits);
	}
}
#endif

static void sdhci_dsm_work(struct work_struct *work)
{
	struct mmc_card *card;
	struct sdhci_arasan_data *sdhci_arasan = container_of(work, struct sdhci_arasan_data, dsm_work);
	struct sdhci_host *host = (struct sdhci_host *)sdhci_arasan->data;
	u32 error_bits, opcode;
	u64 para;
	unsigned long flags;
	spin_lock_irqsave(&host->lock, flags);
	para = sdhci_arasan->para;
	sdhci_arasan->para = 0;
	spin_unlock_irqrestore(&host->lock, flags);
	card = host->mmc->card;
	opcode = para & 0x3f;
	error_bits = ((para >> 16) & 0xffffffff);
	if (para & 0x8000000000000000ULL) {
		DSM_EMMC_LOG(card, DSM_EMMC_HOST_ERR, "opcode:%d failed, status:%x\n", opcode, error_bits);
	} else {
		DSM_EMMC_LOG(card, DSM_EMMC_RW_TIMEOUT_ERR, "opcode:%d failed, status:%x\n", opcode, error_bits);
	}
}

static inline void sdhci_dsm_host_error_filter(struct sdhci_host *host, struct mmc_request *mrq, u32 * error_bits)
{
	if (mrq->cmd) {
		if (mrq->cmd->opcode == MMC_SEND_TUNING_BLOCK_HS200)
			*error_bits = 0;
		else if (host->mmc->ios.clock <= 400000UL) {
			if (((mrq->cmd->opcode == SD_IO_RW_DIRECT) || (mrq->cmd->opcode == SD_SEND_IF_COND) || (mrq->cmd->opcode == SD_IO_SEND_OP_COND) || (mrq->cmd->opcode == MMC_APP_CMD)))
				*error_bits = 0;
			else if (mrq->cmd->opcode == MMC_SEND_STATUS)
				*error_bits &= ~SDHCI_INT_CRC;
		}
	}
}

void sdhci_dsm_handle(struct sdhci_host *host, struct mmc_request *mrq)
{
	u32 error_bits;
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;
	error_bits = sdhci_arasan->cmd_data_status;
	if (error_bits) {
		sdhci_arasan->cmd_data_status = 0;
		sdhci_dsm_host_error_filter(host, mrq, &error_bits);
		if (error_bits) {
			sdhci_arasan->para = ((error_bits << 16) | ((mrq->cmd ? mrq->cmd->opcode : 0) & 0x3f) | 0x8000000000000000ULL);
			queue_work(system_freezable_wq, &sdhci_arasan->dsm_work);
		}
	}
}
#endif

static int sdhci_arasan_probe(struct platform_device *pdev)
{
	int ret;
	struct sdhci_host *host = NULL;
	struct sdhci_pltfm_host *pltfm_host;
	struct sdhci_arasan_data *sdhci_arasan;
	struct device_node *np = pdev->dev.of_node;
	static const char *const hi_mci0 = "hi_mci.0";
#ifdef CONFIG_MMC_CQ_HCI
	bool cmdq_fix_qbr = false;
#endif
	pr_debug("%s: start!\n", __func__);

	ret = sdhci_get_pmctrl_resocure();
	if (ret < 0)
		pr_err("%s :sdhci_get_pmctrl_resocure fail\n", __func__);
	ret = sdhci_arasan_get_resource();
	if (ret)
		return ret;

	sdhci_arasan = devm_kzalloc(&pdev->dev, sizeof(*sdhci_arasan), GFP_KERNEL);
	if (!sdhci_arasan)
		return -ENOMEM;

	if (of_device_is_available(np)) {
		if (of_property_read_u32(np, "clk-ahb", &ahb_clk))
			dev_err(&pdev->dev, "clk-ahb cannot get from dts, use the default value!\n");

		if (of_property_read_u32(np, "clk-xin", &xin_clk))
			dev_err(&pdev->dev, "clk-xin  cannot get from dts, use the default value!\n");
#ifdef CONFIG_MMC_CQ_HCI
		if (of_find_property(np, "fix-qbr", NULL))
			cmdq_fix_qbr = true;
#endif
		if (of_find_property(np, "hi6250-phy-config", NULL)) {
			hs400_dll_freq_data = HS400_DLL_FREQ_DATA_HI6250;
			hs400_tx_phase = HS400_TX_PHASE_HI6250;
		}
	}

	sdhci_arasan->clk_ahb = devm_clk_get(&pdev->dev, "clk_ahb");
	if (IS_ERR(sdhci_arasan->clk_ahb)) {
		dev_err(&pdev->dev, "clk_ahb clock not found.\n");
		return PTR_ERR(sdhci_arasan->clk_ahb);
	}
	ret = clk_set_rate(sdhci_arasan->clk_ahb, ahb_clk);
	if (ret)
		dev_err(&pdev->dev, "Error setting desired ahb_clk=%u, get clk=%lu.\n", ahb_clk, clk_get_rate(sdhci_arasan->clk_ahb));
	ret = clk_prepare_enable(sdhci_arasan->clk_ahb);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable AHB clock.\n");
		return ret;
	}

	sdhci_arasan->clk = devm_clk_get(&pdev->dev, "clk_xin");
	if (IS_ERR(sdhci_arasan->clk)) {
		dev_err(&pdev->dev, "clk_xin clock not found.\n");
		return PTR_ERR(sdhci_arasan->clk);
	}
	ret = clk_set_rate(sdhci_arasan->clk, xin_clk);
	if (ret)
		dev_err(&pdev->dev, "Error setting desired xin_clk=%u, get clk=%lu.\n", xin_clk, clk_get_rate(sdhci_arasan->clk));
	ret = clk_prepare_enable(sdhci_arasan->clk);
	if (ret) {
		dev_err(&pdev->dev, "Unable to enable SD clock.\n");
		goto clk_dis_ahb;
	}

	pr_info("%s: clk_ahb=%lu, clk_xin=%lu\n", __func__, clk_get_rate(sdhci_arasan->clk_ahb), clk_get_rate(sdhci_arasan->clk));

	sdhci_of_arasan_hardware_reset(host, 1);
	sdhci_of_arasan_hardware_reset(host, 0);
	sdhci_arasan->enhanced_strobe_enabled = 0;
	sdhci_arasan->tuning_current_sample = -1;
	sdhci_arasan->tuning_init_sample = 0xff;
	sdhci_arasan->tuning_sample_count = 0;
	sdhci_arasan->tuning_move_sample = 0xff;
	sdhci_arasan->tuning_move_count = 0;
	sdhci_arasan->tuning_strobe_init_sample = 0;	/* 0x0, 0x1, 0x2, 0x3 */
	sdhci_arasan->tuning_strobe_move_sample = 0xff;
	sdhci_arasan->tuning_strobe_move_count = 0;
	sdhci_arasan->tuning_sample_flag = 0;

	host = sdhci_pltfm_init(pdev, &sdhci_arasan_pdata, 0);
	if (IS_ERR(host)) {
		ret = PTR_ERR(host);
		goto clk_disable_all;
	}

	g_sdhci_for_mmctrace = host;

	sdhci_get_of_property(pdev);
	pltfm_host = sdhci_priv(host);
	pltfm_host->priv = sdhci_arasan;
	pltfm_host->clk = sdhci_arasan->clk;

#ifdef CONFIG_MMC_CQ_HCI
#define HW_CMDQ_REG_OFF                0x200
	if (host->mmc->caps2 & MMC_CAP2_CMD_QUEUE) {
		host->cq_host = cmdq_pltfm_init(pdev, host->ioaddr + HW_CMDQ_REG_OFF);
		if (IS_ERR(host->cq_host)) {
			ret = PTR_ERR(host->cq_host);
			dev_err(&pdev->dev, "cmd queue platform init failed (%u)\n", ret);
			host->mmc->caps2 &= ~MMC_CAP2_CMD_QUEUE;
		} else {
			host->cq_host->fix_qbr = cmdq_fix_qbr;
		}
	}
#endif

	host->quirks |= SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN;
	host->quirks2 |= SDHCI_QUIRK2_PRESET_VALUE_BROKEN;
	host->quirks2 |= SDHCI_QUIRK2_USE_1_8_V_VMMC;

	if (host->mmc->pm_caps & MMC_PM_KEEP_POWER) {
		host->mmc->pm_flags |= MMC_PM_KEEP_POWER;
		host->quirks2 |= SDHCI_QUIRK2_HOST_OFF_CARD_ON;
	}

	/* import, ADMA support 64 or 32 bit address, here we use 32 bit. SDMA only support 32 bit mask. */
	if (!(host->quirks2 & SDHCI_QUIRK2_BROKEN_64_BIT_DMA)) {
		host->dma_mask = DMA_BIT_MASK(64);
	} else {
		host->dma_mask = DMA_BIT_MASK(32);
	}
	mmc_dev(host->mmc)->dma_mask = &host->dma_mask;

	/**
	 * BUG: device rename krees old name, which would be realloced for other
	 * device, pdev->name points to freed space, driver match may cause a panic
	 * for wrong device
	 */
	pdev->name = hi_mci0;
	ret = device_rename(&pdev->dev, hi_mci0);
	if (ret < 0) {
		dev_err(&pdev->dev, "dev set name hi_mci.0 fail \n");
		/* if failed, keep pdev->name same to dev.kobj.name */
		pdev->name = pdev->dev.kobj.name;
		goto err_pltfm_free;
	}
	/* keep pdev->name pointing to dev.kobj.name */
	pdev->name = pdev->dev.kobj.name;
	host->hw_name = dev_name(&pdev->dev);

#ifdef CONFIG_HUAWEI_EMMC_DSM
	sdhci_arasan->data = (void *)host;
	INIT_WORK(&sdhci_arasan->dsm_work, sdhci_dsm_work);
#endif

	ret = sdhci_add_host(host);
	if (ret)
		goto err_pltfm_free;

	if (host->mmc->caps2 & MMC_CAP2_CMD_QUEUE) {
		if (!(host->quirks2 & SDHCI_QUIRK2_BROKEN_64_BIT_DMA)) {
			host->cq_host->quirks |= CMDQ_QUIRK_SHORT_TXFR_DESC_SZ;
			host->cq_host->caps |= CMDQ_TASK_DESC_SZ_128;
			pr_info("cmdq using ADMA-64bit\n");
		}
	}

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);
	pm_runtime_set_autosuspend_delay(&pdev->dev, 50);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_suspend_ignore_children(&pdev->dev, 1);

	pr_info("%s: done!\n", __func__);

	return 0;

err_pltfm_free:
	sdhci_pltfm_free(pdev);

clk_disable_all:
	clk_disable_unprepare(sdhci_arasan->clk);
clk_dis_ahb:
	clk_disable_unprepare(sdhci_arasan->clk_ahb);

	pr_err("%s: error = %d!\n", __func__, ret);

	return ret;
}

static int sdhci_arasan_remove(struct platform_device *pdev)
{
	struct sdhci_host *host = platform_get_drvdata(pdev);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = pltfm_host->priv;

	pr_debug("%s:\n", __func__);

	pm_runtime_get_sync(&pdev->dev);
	sdhci_remove_host(host, 1);
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	clk_disable_unprepare(sdhci_arasan->clk);
	clk_disable_unprepare(sdhci_arasan->clk_ahb);

	sdhci_pltfm_free(pdev);

	return 0;
}

static const struct of_device_id sdhci_arasan_of_match[] = {
	{.compatible = "arasan,sdhci"},
	{}
};

MODULE_DEVICE_TABLE(of, sdhci_arasan_of_match);

static struct platform_driver sdhci_arasan_driver = {
	.driver = {
			   .name = "sdhci-arasan",
			   .of_match_table = sdhci_arasan_of_match,
			   .pm = &sdhci_arasan_dev_pm_ops,
			   },
	.probe = sdhci_arasan_probe,
	.remove = sdhci_arasan_remove,
};

module_platform_driver(sdhci_arasan_driver);

MODULE_DESCRIPTION("Driver for the Arasan SDHCI Controller");
MODULE_AUTHOR("Soeren Brinkmann <soren.brinkmann@xilinx.com>");
MODULE_LICENSE("GPL");
