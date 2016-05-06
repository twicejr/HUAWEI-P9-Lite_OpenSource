/*
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (c) 2013 Hisilicon Limited.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/host.h>
#include <linux/mmc/dw_mmc.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/pinctrl/consumer.h>
#include <linux/of_address.h>
#include <linux/pm_runtime.h>
#include <linux/clk-private.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/hisi/hi6xxx-iomap.h>

#include <../drivers/pinctrl/core.h>

#include "dw_mmc_hi6xxx.h"

#include "dw_mmc.h"
#include "dw_mmc-pltfm.h"

#include "soc_peri_sctrl_interface.h"
#include "soc_baseaddr_interface.h"
#include "soc_ao_sctrl_interface.h"

#ifdef CONFIG_HI110X_WIFI_ENABLE
#include <linux/huawei/hw_connectivity.h>
#endif

#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>

static struct dsm_dev dsm_dw_mmc = {
	.name = "dw_mmc",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
	.fops = NULL,
	.buff_size = 1024,
};

static struct dsm_client *dclient = NULL;
#endif

static void __iomem *pericrg_base = NULL;

static int hs_timing_config[][9][TUNING_INIT_CONFIG_NUM] = {
/* bus_clk, div, drv_sel, sam_dly, sam_phase_max, sam_phase_min, input_clk */
	{
		{360000000, 9, 1, 0, 0, 0, 36000000},		/* 0: LEGACY 100k */
	 	{360000000, 6, 1, 0, 1, 1, 52000000},		/* 1: MMC_HS */
	 	{0},									/* 2: SD_HS */
	 	{0},									/* 3: SDR12 */
	 	{0},									/* 4: SDR25 */
	 	{0},									/* 5: SDR50 */
	 	{0},									/* 6: SDR104 */
	 	{720000000, 6, 0, 4, 6, 0, 102000000},	/* 7: DDR50 */
	 	{1440000000, 7, 0, 3, 15, 0, 180000000},	/* 8: HS200 */
	 }, {
	 	{360000000, 9, 1, 0, 0, 0, 36000000},		/* 0: LEGACY 400k */
		{0},									/* 1: MMC_HS */
		{360000000, 6, 1, 0, 1, 1, 50000000},		/* 2: SD_HS */
		{180000000, 6, 1, 2, 13, 13, 25000000},	/* 3: SDR12 */
		{360000000, 6, 1, 0, 1, 1, 50000000},		/* 4: SDR25 */
		{720000000, 6, 0, 3, 9, 0, 100000000},	/* 5: SDR50 */
		{1440000000, 7, 0, 5, 15, 0, 180000000},	/* 6: SDR104 */
		{0},									/* 7: DDR50 */
		{0},									/* 8: HS200 */
	}, {
		{360000000, 9, 1, 0, 0, 0, 36000000},		/* 0: LEGACY 400k */
		{0},									/* 1: MMC_HS */
		{360000000, 6, 1, 0, 4, 4, 50000000},		/* 2: SD_HS */
		{180000000, 6, 1, 2, 0, 0, 25000000},		/* 3: SDR12 */
		{360000000, 6, 1, 0, 4, 4, 50000000},		/* 4: SDR25 */
		{720000000, 6, 0, 2, 9, 0, 100000000},	/* 5: SDR50 */
		{1440000000, 7, 0, 4, 15, 0, 180000000},	/* 6: SDR104 */
		{720000000, 15, 0, 5, 11, 1, 45000000},	/* 7: DDR50 */
		{0},									/* 8: HS200 */
	}
};

static const u32 tuning_block_128[] = {
	0xFF00FFFF, 0x0000FFFF, 0xCCCCFFFF, 0xCCCC33CC,
	0xCC3333CC, 0xFFFFCCCC, 0xFFFFEEFF, 0xFFEEEEFF,
	0xFFDDFFFF, 0xDDDDFFFF, 0xBBFFFFFF, 0xBBFFFFFF,
	0xFFFFFFBB, 0xFFFFFF77, 0x77FF7777, 0xFFEEDDBB,
	0x00FFFFFF, 0x00FFFFFF, 0xCCFFFF00, 0xCC33CCCC,
	0x3333CCCC, 0xFFCCCCCC, 0xFFEEFFFF, 0xEEEEFFFF,
	0xDDFFFFFF, 0xDDFFFFFF, 0xFFFFFFDD, 0xFFFFFFBB,
	0xFFFFBBBB, 0xFFFF77FF, 0xFF7777FF, 0xEEDDBB77
};

static const u32 tuning_block_64[] = {
	0x00FF0FFF, 0xCCC3CCFF, 0xFFCC3CC3, 0xEFFEFFFE,
	0xDDFFDFFF, 0xFBFFFBFF, 0xFF7FFFBF, 0xEFBDF777,
	0xF0FFF0FF, 0x3CCCFC0F, 0xCFCC33CC, 0xEEFFEFFF,
	0xFDFFFDFF, 0xFFBFFFDF, 0xFFF7FFBB, 0xDE7B7FF7
};

static int emmc_hs200_tuning_point = 0;
static int sd_sdr104_tuning_point = 0;

/*当read、massread操作时发包使用*/
struct semaphore sem_to_rfile_sync_req;

extern void mshci_set_clock(struct dw_mci *host, unsigned int clock);

extern int gpio_direction_output(unsigned gpio, int value);

static void dw_mci_hi6xxx_set_timing(struct dw_mci *host, int id, int timing, int sam_phase, int clk_div)
{
	int cclk_div;
	int drive_sel;
	int sam_dly;
	int sam_phase_max, sam_phase_min;
	int sam_phase_val;
	int reg_value;
	int enable_shift = 0;
	int use_sam_dly = 0;
	int d_value = 0;

	if (host->hw_mmc_id == DWMMC_SD_ID) {
		d_value = clk_div - hs_timing_config[id][timing][1];
	}

	cclk_div = clk_div;
	drive_sel = hs_timing_config[id][timing][2];
	sam_dly = hs_timing_config[id][timing][3] + d_value;
	sam_phase_max = hs_timing_config[id][timing][4];
	sam_phase_min = hs_timing_config[id][timing][5];

	if (sam_phase == -1)
		sam_phase_val = (sam_phase_max + sam_phase_min) / 2;
	else
		sam_phase_val = sam_phase;

	if (timing == MMC_TIMING_LEGACY)
		enable_shift = 1;

	if ((id == 0) && (timing == MMC_TIMING_MMC_HS200)) {
		switch (sam_phase_val) {
		case 0:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			use_sam_dly = 1;
			break;
		default:
			use_sam_dly = 0;
		}
	}

	if ((id == 1) && (timing == MMC_TIMING_UHS_SDR104)) {
		if ((sam_phase_val == 0) || (sam_phase_val >= 10))
			use_sam_dly = 1;
	}

	if ((id == 2) && (timing == MMC_TIMING_UHS_SDR104)) {
		switch (sam_phase_val) {
		case 0:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			use_sam_dly = 1;
			break;
		default:
			use_sam_dly = 0;
		}
	}

	/* first disabl clk */
	mci_writel(host, GPIO, ~GPIO_CLK_ENABLE);
	reg_value = SDMMC_UHS_REG_EXT_VALUE(sam_phase_val, sam_dly);
	mci_writel(host, UHS_REG_EXT, reg_value);

	mci_writel(host, ENABLE_SHIFT, enable_shift);

	reg_value = SDMMC_GPIO_VALUE(cclk_div, use_sam_dly, drive_sel);
	mci_writel(host, GPIO, reg_value | GPIO_CLK_ENABLE);

	dev_info(host->dev, "id=%d, timing=%d, UHS_REG_EXT=0x%x,\
		ENABLE_SHIFT=0x%x, GPIO=0x%x \n", id, timing, mci_readl(host, UHS_REG_EXT),
			mci_readl(host, ENABLE_SHIFT), mci_readl(host, GPIO));
}

static void dw_mci_hi6xxx_set_parent(struct dw_mci *host, int timing)
{
	struct dw_mci_hs_priv_data *priv = host->priv;
	int id = priv->id;
	struct clk *clk_parent = NULL;

	if (id != 0)
		return;
#if 0
	/* select 19.2M clk */
	if (timing == MMC_TIMING_LEGACY) {
		clk_parent = clk_get_parent_by_index(host->parent_clk, 0);
		if (IS_ERR_OR_NULL(clk_parent)) {
			dev_err(host->dev, " fail to get parent clk. \n");
		}

		clk_set_parent(host->parent_clk, clk_parent);
	} else {
		clk_parent = clk_get_parent_by_index(host->parent_clk, 4);
		if (IS_ERR_OR_NULL(clk_parent)) {
			dev_err(host->dev, " fail to get parent clk. \n");
		}

		clk_set_parent(host->parent_clk, clk_parent);
	}
#endif

	clk_parent = clk_get_parent_by_index(host->parent_clk, 4);
	if (IS_ERR_OR_NULL(clk_parent)) {
		dev_err(host->dev, " fail to get parent clk. \n");
	}

	clk_set_parent(host->parent_clk, clk_parent);
}

static void dw_mci_hi6xxx_clock_onoff(struct dw_mci *host, bool val)
{
	u32 loop_count;
	u32 reg = 0;

	loop_count = 0x100000;

	if (val) {
		/* use internal clock gating */
		mci_writel(host, CLKENA, (0x1 << 0));

		mci_writel(host, CMD, 0);
		mci_writel(host, RINTSTS, (0x1 << 12));
		mci_writel(host, CMD, CMD_ONLY_CLK);
		do {
			if (!(mci_readl(host, CMD) & CMD_STRT_BIT))
				break;
			loop_count--;
		} while (loop_count);
	} else {
		mci_writel(host, CLKENA, (0x0 << 0));
		mci_writel(host, CMD, 0);
		mci_writel(host, RINTSTS, INTMSK_HLE);
		mci_writel(host, CMD, CMD_ONLY_CLK);
		do {
			if (!(mci_readl(host, CMD) & CMD_STRT_BIT))
				break;
			loop_count--;
		} while (loop_count);
	}

	reg = mci_readl(host, RINTSTS);
	if (reg & INTMSK_HLE) {
		mci_writel(host, CMD, 0);
		mci_writel(host, RINTSTS, INTMSK_HLE);
	} else if (loop_count == 0) {
	}

	mci_writel(host, CMD, 0);

}

void dw_mci_hi6xxx_set_clock(struct dw_mci *host, unsigned int clock)
{
	int div;
	u32 loop_count, reg;

	/* before changing clock. clock needs to be off */
	dw_mci_hi6xxx_clock_onoff(host, CLK_DISABLE);

	/*if the clock is setted to 0Hz, here do return */
	if (clock == 0)
		return;

	if (clock >= host->bus_hz) {
		div = 0;
	} else {
		for (div = 1; div < 255; div++) {
			if ((host->bus_hz / (div << 1)) <= clock)
				break;
		}
	}

	loop_count = 0x100000;

	mci_writel(host, CLKDIV, div);
	mci_writel(host, CLKSRC, 0);
	mci_writel(host, CMD, 0);
	mci_writel(host, RINTSTS, INTMSK_HLE);
	mci_writel(host, CMD, CMD_ONLY_CLK);

	do {
		if (!(mci_readl(host, CMD) & CMD_STRT_BIT))
			break;
		loop_count--;
	} while (loop_count);

	reg = mci_readl(host, RINTSTS);
	if (reg & INTMSK_HLE) {
		printk(KERN_ERR "HLE in Changing clock. RINTSTS = 0x%x\n ", reg);
		mci_writel(host, CMD, 0);
		mci_writel(host, RINTSTS, INTMSK_HLE);
	} else if (loop_count == 0) {
		printk(KERN_ERR "Changing clock has been failed.\n ");
	}

	mci_writel(host, CMD, 0);

	dw_mci_hi6xxx_clock_onoff(host, CLK_ENABLE);

}

static void dw_mci_hi6xxx_sd_ioctrl_gpio(struct dw_mci_hs_priv_data *priv)
{
	unsigned gpio_8_3 = GPIO_8_3;
	unsigned gpio_8_4 = GPIO_8_4;
	unsigned gpio_8_5 = GPIO_8_5;
	unsigned gpio_8_6 = GPIO_8_6;
	unsigned gpio_8_7 = GPIO_8_7;
	unsigned gpio_9_0 = GPIO_9_0;
	int ret;

	ret = gpio_request(gpio_8_3, "gpio8-3");
	if (ret) {
		printk(KERN_ERR "dw_mci_hi6xxx_sd_ioctrl_gpio:gpio_8_3 fail.\n ");
	}
	gpio_direction_output(gpio_8_3, 0);
	gpio_free(gpio_8_3);
	ret = gpio_request(gpio_8_4, "gpio8-4");
	if (ret) {
		printk(KERN_ERR "dw_mci_hi6xxx_sd_ioctrl_gpio:gpio_8_4 fail.\n ");
	}
	gpio_direction_output(gpio_8_4, 0);
	gpio_free(gpio_8_4);

	ret = gpio_request(gpio_8_5, "gpio8-5");
	if (ret) {
		printk(KERN_ERR "dw_mci_hi6xxx_sd_ioctrl_gpio:gpio_8_5 fail.\n ");
	}
	gpio_direction_output(gpio_8_5, 0);
	gpio_free(gpio_8_5);

	ret = gpio_request(gpio_8_6, "gpio8-6");
	if (ret) {
		printk(KERN_ERR "dw_mci_hi6xxx_sd_ioctrl_gpio:gpio_8_6 fail.\n ");
	}
	gpio_direction_output(gpio_8_6, 0);
	gpio_free(gpio_8_6);

	ret = gpio_request(gpio_8_7, "gpio8-7");
	if (ret) {
		printk(KERN_ERR "dw_mci_hi6xxx_sd_ioctrl_gpio:gpio_8_7 fail.\n ");
	}
	gpio_direction_output(gpio_8_7, 0);
	gpio_free(gpio_8_7);

	ret = gpio_request(gpio_9_0, "gpio9-0");
	if (ret) {
		printk(KERN_ERR "dw_mci_hi6xxx_sd_ioctrl_gpio:gpio_9_0 fail.\n ");
	}
	gpio_direction_output(gpio_9_0, 0);
	gpio_free(gpio_9_0);
}

/*SOC1008*/
static void dw_mci_hi6xxx_set_ios(struct dw_mci *host, struct mmc_ios *ios)
{
	struct dw_mci_hs_priv_data *priv = host->priv;
	int id = priv->id;
	int ret;

	if (priv->old_power_mode != ios->power_mode) {
		switch (ios->power_mode) {
		case MMC_POWER_OFF:
			dev_info(host->dev, "set io to lowpower\n");
			/* set pin to idle */
			/*继承V9，emmc常供电 */

			if (MMC_SD == id) {
				/*sd powerdown1: gpio */
				/*sd powerdown2: OL/NP */
				dw_mci_hi6xxx_sd_ioctrl_gpio(priv);

				/*sd powerdown3: LDO10 */
				if ((host->vmmc) && (priv->sd_slot_ldo10_status == SD_SLOT_VOL_CLOSE))
					regulator_disable(host->vmmc);
				usleep_range(20000, 20000);
				/*sd powerdown4: LDO7 */
				if (host->vqmmc)
					regulator_disable(host->vqmmc);

				/*sd powerdown5: gpio */
				if ((host->pinctrl) && (host->pins_idle)) {
					ret = pinctrl_select_state(host->pinctrl, host->pins_idle);
					if (ret)
						dev_warn(host->dev, "could not set idle pins\n");
				}

				/*code for sd SDR104 mode tuning */
				mci_writel(host, UHS_REG_EXT, 0x00);

			}

			break;

		case MMC_POWER_UP:
			dev_info(host->dev, "set io to normal\n");

			/*继承V9，emmc常供电 */
			/*
			   ldo5不需要配置，硬件默认上电；
			   ldo19配置为3V；
			 */
			if (MMC_SD != id) {
				if (host->vmmc) {
					ret = regulator_set_voltage(host->vmmc, 3000000, 3000000);
					if (ret)
						dev_err(host->dev, "regulator_set_voltage failed !\n");

					ret = regulator_enable(host->vmmc);
					if (ret)
						dev_err(host->dev, "regulator_enable failed !\n");
				}

				if ((host->pinctrl) && (host->pins_default)) {
					ret = pinctrl_select_state(host->pinctrl, host->pins_default);
					if (ret)
						dev_warn(host->dev, "could not set default pins\n");
				}
			}

			if (MMC_SD == id) {
				/*sd powerup1: gpio ol */
				if ((host->pinctrl) && (host->pins_idle)) {
					ret = pinctrl_select_state(host->pinctrl, host->pins_idle);
					if (ret)
						dev_warn(host->dev, "could not set idle pins\n");
				}

				dw_mci_hi6xxx_sd_ioctrl_gpio(priv);
			}

			break;

		case MMC_POWER_ON:

			if (MMC_SD == id) {
				/*sd powerup3: LDO10 */
				if (host->vmmc) {
					ret = regulator_set_voltage(host->vmmc, 3000000, 3000000);
					if (ret)
						dev_err(host->dev, "regulator_set_voltage failed !\n");

					ret = regulator_enable(host->vmmc);
					if (ret)
						dev_err(host->dev, "regulator_enable failed !\n");
				}

				usleep_range(1000, 1000);

#if 0
				/*sd powerup4: MMC IO */
				if ((host->pinctrl) && (host->pins_default)) {
					ret = pinctrl_select_state(host->pinctrl, host->pins_default);
					if (ret)
						dev_err(host->dev, "could not set default pins\n");
				}
#endif

				/*配置pinctrl 状态，在设置为idle时需要 */
				host->pinctrl->state = host->pins_default;

				/*配置sd 管脚复用，除clk 管脚外 */
				*(volatile u32 *)(priv->ioc_off + 0x10) = 0;
				*(volatile u32 *)(priv->ioc_off + 0x14) = 0;
				*(volatile u32 *)(priv->ioc_off + 0x18) = 0;
				*(volatile u32 *)(priv->ioc_off + 0x1c) = 0;
				*(volatile u32 *)(priv->ioc_off + 0x20) = 0;

				/*配置sd管脚配置 */
				*(volatile u32 *)(priv->ioc_off + 0x80c) = 0x34;
				*(volatile u32 *)(priv->ioc_off + 0x810) = 0x24;
				*(volatile u32 *)(priv->ioc_off + 0x814) = 0x24;
				*(volatile u32 *)(priv->ioc_off + 0x818) = 0x24;
				*(volatile u32 *)(priv->ioc_off + 0x81c) = 0x24;
				*(volatile u32 *)(priv->ioc_off + 0x820) = 0x24;

				usleep_range(1000, 1000);

				/*延时后配置clk 管脚复用为sd */
				*(volatile u32 *)(priv->ioc_off + 0xc) = 0;

			}

			break;
		default:
			dev_info(host->dev, "unknown power supply mode\n");
			break;
		}
		priv->old_power_mode = ios->power_mode;
	}

	if (priv->old_timing != ios->timing) {

		/*SOC1005:from V9 turning process */
		host->tuning_needed = false;
		host->tuning_done = false;

		/*SOC1007 */
		if (priv->priv_bus_hz == 0) {
			switch (ios->timing) {
			case MMC_TIMING_LEGACY:
				/*芯片时序约束要求 */
				if (DWMMC_SD_ID == priv->id) {
					host->bus_hz = MMC_CCLK_MAX_24M;
				} else {
					host->bus_hz = MMC_CCLK_MAX_25M;
				}
				break;
			case MMC_TIMING_MMC_HS:
			case MMC_TIMING_UHS_SDR25:
				if (DWMMC_SD_ID == priv->id) {
					host->bus_hz = MMC_CCLK_MAX_48M;
				} else {
					host->bus_hz = MMC_CCLK_MAX_50M;
				}
				break;
			case MMC_TIMING_UHS_DDR50:
				/*SOC1000:在DDR50（8bit）模式时MMC内部固定为2:1分频 ? */
				if (DWMMC_EMMC_ID == priv->id) {
					host->bus_hz = MMC_CCLK_MAX_100M;
				} else {
					host->bus_hz = MMC_CCLK_MAX_50M;
				}
				break;
			case MMC_TIMING_UHS_SDR104:
			case MMC_TIMING_MMC_HS200:

				printk(KERN_INFO "dw_mci_hs_set_ios:$$$$$$$$ WE GOT HS200 \n");

				host->tuning_needed = true;

				if (EMMC_CS_BOARD == priv->cs) {
					printk(KERN_ERR "dw_mci_hs_set_ios:$$$$$$$$ CS Board \n");

					host->bus_hz = MMC_CCLK_MAX_180M;
				} else {
					host->bus_hz = MMC_CCLK_MAX_150M;
				}

				break;
			case MMC_TIMING_UHS_SDR50:

				if (DWMMC_SD_ID == priv->id) {
					if (SD_CS_BOARD == priv->cs) {
						host->bus_hz = MMC_CCLK_MAX_96M;
					} else {
						host->bus_hz = MMC_CCLK_MAX_80M;
					}
				} else {
					host->bus_hz = MMC_CCLK_MAX_100M;
				}

				break;
			default:
				printk(KERN_ERR "error the timing we can not support \n");

			}

		}

		if (0 != priv->dw_mmc_bus_clk) {
			/*sft 单板最高支持频率为30MHz */
			host->bus_hz = priv->dw_mmc_bus_clk;
		} else {
			;
		}

		clk_set_rate(host->biu_clk, host->bus_hz);

		dw_mci_hi6xxx_set_clock(host, ios->clock);

		priv->old_timing = ios->timing;
	}

}

static void dw_mci_hi6xxx_prepare_command(struct dw_mci *host, u32 *cmdr)
{
	*cmdr |= SDMMC_CMD_USE_HOLD_REG;
}

static void dw_mci_hi6xxx_tuning_clear_flags(struct dw_mci *host)
{
	host->tuning_sample_flag = 0;
}

static void dw_mci_hi6xxx_tuning_set_flags(struct dw_mci *host, int sample, int ok)
{
	if (ok)
		host->tuning_sample_flag |= (1 << sample);
	else
		host->tuning_sample_flag &= ~(1 << sample);
}

/* By tuning, find the best timing condition
 *	1 -- tuning is not finished. And this function should be called again
 *	0 -- Tuning successfully.
 *		If this function be called again, another round of tuning would be start
 *	-1 -- Tuning failed. Maybe slow down the clock and call this function again
 */
static int dw_mci_hi6xxx_tuning_find_condition(struct dw_mci *host, int timing)
{
	struct dw_mci_hs_priv_data *priv = host->priv;
	int id = priv->id;
	int sample_min, sample_max;
	int i, j;
	int ret = 0;
	int mask, mask_lenth;
	int d_value = 0;

	if (host->hw_mmc_id == DWMMC_SD_ID) {
		d_value = host->current_div - hs_timing_config[id][timing][1];
	}

	sample_max = hs_timing_config[id][timing][4] + 2 * d_value;
	sample_min = hs_timing_config[id][timing][5];

	if (sample_max == sample_min) {
		host->tuning_init_sample = (sample_max + sample_min) / 2;
		dw_mci_hi6xxx_set_timing(host, id, timing, host->tuning_init_sample, host->current_div);
		dev_info(host->dev, "no need tuning: timing is %d, tuning sample = %d", timing, host->tuning_init_sample);
		return 0;
	}

	if (-1 == host->tuning_current_sample) {

		dw_mci_hi6xxx_tuning_clear_flags(host);

		/* set the first sam del as the min_sam_del */
		host->tuning_current_sample = sample_min;
		/* a trick for next "++" */
		host->tuning_current_sample--;
	}

	if (host->tuning_current_sample >= sample_max) {
		/* tuning finish, select the best sam_del */

		/* set sam del to -1, for next tuning */
		host->tuning_current_sample = -1;

		host->tuning_init_sample = -1;
		for (mask_lenth = (((sample_max - sample_min) >> 1) << 1) + 1; mask_lenth >= 1; mask_lenth -= 2) {

			mask = (1 << mask_lenth) - 1;
			for (i = (sample_min + sample_max - mask_lenth + 1) / 2, j = 1;
				(i <= sample_max - mask_lenth + 1) && (i >= sample_min);
					i = ((sample_min + sample_max - mask_lenth + 1) / 2) + ((j % 2) ? -1 : 1) * (j / 2)) {
				if ((host->tuning_sample_flag & (mask << i)) == (mask << i)) {
					host->tuning_init_sample = i + mask_lenth / 2;
					break;
				}

				j++;
			}

			if (host->tuning_init_sample != -1) {
				if ((host->hw_mmc_id == DWMMC_SD_ID) && (mask_lenth < 3)) {
					dev_info(host->dev, "sd card tuning need slow down clk, timing is %d, tuning_flag = 0x%x \n",
						timing, host->tuning_sample_flag);
					return -1;
				} else {
					dev_info(host->dev, "tuning OK: timing is %d, tuning sample = %d, tuning_flag = 0x%x",
						timing, host->tuning_init_sample, host->tuning_sample_flag);
					ret = 0;
					break;
				}
			}
		}

		if (-1 == host->tuning_init_sample) {
			host->tuning_init_sample = (sample_min + sample_max) / 2;
			dev_info(host->dev, "tuning err: no good sam_del, timing is %d, tuning_flag = 0x%x", timing, host->tuning_sample_flag);
			ret = -1;
		}

		dw_mci_hi6xxx_set_timing(host, id, timing, host->tuning_init_sample, host->current_div);
		return ret;
	} else {
		host->tuning_current_sample++;
		dw_mci_hi6xxx_set_timing(host, id, timing, host->tuning_current_sample, host->current_div);
		return 1;
	}

	return 0;
}

static void dw_mci_hi6xxx_tuning_set_current_state(struct dw_mci *host, int ok)
{
	dw_mci_hi6xxx_tuning_set_flags(host, host->tuning_current_sample, ok);
}

static int dw_mci_hi6xxx_set_controller(struct dw_mci *host, bool set)
{
	struct dw_mci_hs_priv_data *priv = host->priv;
	int id = priv->id;

	if (pericrg_base == NULL) {
		return -1;
	}

	if (set) {
		if (0 == id) {
			writel(BIT_RST_EMMC, pericrg_base + PERI_CRG_RSTEN4);
			dev_info(host->dev, "rest emmc \n");
			goto out;
		} else if (1 == id) {
			writel(BIT_RST_SD, pericrg_base + PERI_CRG_RSTEN4);
			dev_info(host->dev, "rest sd \n");
			goto out;
		} else if (2 == id) {
			writel(BIT_RST_MMC2, pericrg_base + PERI_CRG_RSTEN4);
			dev_info(host->dev, "rest sdio \n");
			goto out;
		}
	} else {
		if (0 == id) {
			writel(BIT_RST_EMMC, pericrg_base + PERI_CRG_RSTDIS4);
			dev_info(host->dev, "unrest emmc \n");
			goto out;
		} else if (1 == id) {
			writel(BIT_RST_SD, pericrg_base + PERI_CRG_RSTDIS4);
			dev_info(host->dev, "unrest sd \n");
			goto out;
		} else if (2 == id) {
			writel(BIT_RST_MMC2, pericrg_base + PERI_CRG_RSTDIS4);
			dev_info(host->dev, "unrest sdio \n");
			goto out;
		}
	}
out:
	return 0;
}

#ifdef CONFIG_BCMDHD
extern struct dw_mci *sdio_host;

void dw_mci_sdio_card_detect(struct dw_mci *host)
{
	if (host == NULL) {
		printk(KERN_ERR "sdio detect, host is null,can not used to detect sdio\n");
		return;
	}

	dw_mci_set_cd(host);
	/*dw_mci_work_routine_card */
	queue_work(host->card_workqueue, &host->card_work);
	return;
}
#endif

void dw_mci_set_cd(struct dw_mci *host)
{

	if (host == NULL)
		return;

	if (host->slot[0] && host->slot[0]->mmc) {
		dev_dbg(&host->slot[0]->mmc->class_dev, "sdio_present = %d\n", host->slot[0]->mmc->sdio_present);
		host->slot[0]->mmc->sdio_present = 1;
	}
}

EXPORT_SYMBOL(dw_mci_set_cd);

#ifdef CONFIG_HI110X_WIFI_ENABLE
static struct dw_mci *hi_sdio_host = NULL;
void hi110x_sdio_detectcard_to_core(int enable)
{
	if (hi_sdio_host == NULL) {
		printk(KERN_ERR "hi_sdio detect, host is null,can not used to detect sdio\n");
		return;
	}

	dw_mci_set_cd(hi_sdio_host);
	printk(KERN_INFO "Hisi wlan detect mmc control:%d,[%s]\n", hi_sdio_host->hw_mmc_id, enable ? "start sdio enum" : "deinit sdio enum");
	/*dw_mci_work_routine_card */
	queue_work(hi_sdio_host->card_workqueue, &hi_sdio_host->card_work);
	return;
}

EXPORT_SYMBOL(hi110x_sdio_detectcard_to_core);
#endif

#if defined (CONFIG_HUAWEI_DSM)
void dw_mci_dsm_dump(struct dw_mci *host, int err_num)
{
	if (dclient == NULL) {
		printk(KERN_ERR "dclient is not initialization\n");
		return;
	}

	if (!dsm_client_ocuppy(dclient)) {
		dsm_client_record(dclient, "MCI  ID: %d\n", host->hw_mmc_id);
		dsm_client_record(dclient, "CTRL: 0x%x\n", mci_readl(host, CTRL));
		dsm_client_record(dclient, "PWREN: 0x%x\n", mci_readl(host, PWREN));
		dsm_client_record(dclient, "CLKDIV: 0x%x\n", mci_readl(host, CLKDIV));
		dsm_client_record(dclient, "CLKSRC: 0x%x\n", mci_readl(host, CLKSRC));
		dsm_client_record(dclient, "CLKENA: 0x%x\n", mci_readl(host, CLKENA));
		dsm_client_record(dclient, "TMOUT: 0x%x\n", mci_readl(host, TMOUT));
		dsm_client_record(dclient, "CTYPE: 0x%x\n", mci_readl(host, CTYPE));
		dsm_client_record(dclient, "BLKSIZ: 0x%x\n", mci_readl(host, BLKSIZ));
		dsm_client_record(dclient, "BYTCNT: 0x%x\n", mci_readl(host, BYTCNT));
		dsm_client_record(dclient, "INTMSK: 0x%x\n", mci_readl(host, INTMASK));
		dsm_client_record(dclient, "CMDARG: 0x%x\n", mci_readl(host, CMDARG));
		dsm_client_record(dclient, "CMD: 0x%x\n", mci_readl(host, CMD));
		dsm_client_record(dclient, "MINTSTS: 0x%x\n", mci_readl(host, MINTSTS));
		dsm_client_record(dclient, "RINTSTS: 0x%x\n", mci_readl(host, RINTSTS));
		dsm_client_record(dclient, "STATUS: 0x%x\n", mci_readl(host, STATUS));
		dsm_client_record(dclient, "FIFOTH: 0x%x\n", mci_readl(host, FIFOTH));
		dsm_client_record(dclient, "CDETECT: 0x%x\n", mci_readl(host, CDETECT));
		dsm_client_record(dclient, "WRTPRT: 0x%x\n", mci_readl(host, WRTPRT));
		dsm_client_record(dclient, "GPIO: 0x%x\n", mci_readl(host, GPIO));
		dsm_client_record(dclient, "TCBCNT: 0x%x\n", mci_readl(host, TCBCNT));
		dsm_client_record(dclient, "TBBCNT: 0x%x\n", mci_readl(host, TBBCNT));
		dsm_client_record(dclient, "DEBNCE: 0x%x\n", mci_readl(host, DEBNCE));
		dsm_client_record(dclient, "USRID: 0x%x\n", mci_readl(host, USRID));
		dsm_client_record(dclient, "VERID: 0x%x\n", mci_readl(host, VERID));
		dsm_client_record(dclient, "HCON: 0x%x\n", mci_readl(host, HCON));
		dsm_client_record(dclient, "UHS_REG: 0x%x\n", mci_readl(host, UHS_REG));
		dsm_client_record(dclient, "BMOD: 0x%x\n", mci_readl(host, BMOD));
		dsm_client_record(dclient, "PLDMND: 0x%x\n", mci_readl(host, PLDMND));
		dsm_client_record(dclient, "DBADDR: 0x%x\n", mci_readl(host, DBADDR));
		dsm_client_record(dclient, "IDSTS: 0x%x\n", mci_readl(host, IDSTS));
		dsm_client_record(dclient, "IDINTEN: 0x%x\n", mci_readl(host, IDINTEN));
		dsm_client_record(dclient, "DSCADDR: 0x%x\n", mci_readl(host, DSCADDR));
		dsm_client_record(dclient, "BUFADDR: 0x%x\n", mci_readl(host, BUFADDR));
		dsm_client_record(dclient, "RESP0: 0x%x\n", mci_readl(host, RESP0));
		dsm_client_record(dclient, "RESP1: 0x%x\n", mci_readl(host, RESP1));
		dsm_client_record(dclient, "RESP2: 0x%x\n", mci_readl(host, RESP2));
		dsm_client_record(dclient, "RESP3: 0x%x\n", mci_readl(host, RESP3));
		dsm_client_notify(dclient, err_num);
	} else
		printk("DSM CALL FAIL, MCI  ID: %d\n", host->hw_mmc_id);
}

EXPORT_SYMBOL(dw_mci_dsm_dump);

#endif

static int dw_mci_hi6xxx_priv_init(struct dw_mci *host)
{
	struct dw_mci_hs_priv_data *priv;
	int sw[2] = { 0 };
	int err = -1;
	static void __iomem *sc_periph_addr = 0;
	int error = -1;

	priv = devm_kzalloc(host->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		dev_err(host->dev, "mem alloc failed for private data\n");
		return -ENOMEM;
	}

	priv->id = of_alias_get_id(host->dev->of_node, "mshc");

	if (!sc_periph_addr)
		sc_periph_addr = (void __iomem *)HISI_VA_ADDRESS(SOC_PERI_SCTRL_BASE_ADDR);

	if (priv->id == MMC_EMMC) {

		error = dev_set_name(host->dev, "hi_mci.0");
		if (error < 0) {
			dev_err(host->dev, "dev set name hi_mci.0 fail \n");
			goto fail;
		}

		mci_writel(host, CARDTHRCTL, 0x02000001);

		sema_init(&sem_to_rfile_sync_req, 0);

		priv->peri_sysctrl = sc_periph_addr;
		if (!priv->peri_sysctrl) {
			printk(KERN_ERR "dw_mci_hs_priv_init :peri_sysctrl err  \n");
			goto fail;
		}

		/*默认tuning是失败，表示没有经过tuning或者tuning失败 */
		host->tuning_result_flag = EMMC_TUNING_FAIL;

	}

	if (priv->id == MMC_SD) {

		/*解决SD resume 识别失败 */
		priv->ioc_off = (void __iomem *)ioremap_nocache(SOC_IOC_OFF_BASE_ADDR, 4096);
		if (!priv->ioc_off) {
			printk(KERN_ERR "dw_mci_hs_priv_init :priv->ioc_off err  \n");
			goto fail;
		}

		error = dev_set_name(host->dev, "hi_mci.1");
		if (error < 0) {
			dev_err(host->dev, "dev set name hi_mci.1 fail \n");
			goto fail;
		}

		if (of_property_read_u32_array(host->dev->of_node, "sw_gpio", &sw[0], 2)) {
			printk("[%s] %s node doesn't have sw_gpio property!\n", __func__, host->dev->of_node->name);
		} else {

			priv->gpio_sw = sw[0];
			priv->sw_value = sw[1];

			err = gpio_request_one(priv->gpio_sw, 0, "sw_gpio");
			if (err) {
				printk(KERN_ERR "request gpio fail!\n");
				goto fail;
			}
			/*控制I/O口电平 1V8 or 3V3 */
			gpio_direction_output(priv->gpio_sw, priv->sw_value);
		}
		/*解复位 */
		if (!sc_periph_addr) {
			printk(KERN_ERR "dw_mci_hs_priv_init :sc_periph_addr err  \n");
			goto fail;
		}

		writel(readl(SOC_PERI_SCTRL_SC_PERIPH_RSTDIS0_ADDR(sc_periph_addr)) | 0x6,
			SOC_PERI_SCTRL_SC_PERIPH_RSTDIS0_ADDR(sc_periph_addr));	/* for sdcard, sdio*/

		priv->ao_sysctrl = (void __iomem *)HISI_VA_ADDRESS(SOC_AO_SCTRL_BASE_ADDR);
		if (!priv->ao_sysctrl) {
			printk(KERN_ERR "dw_mci_hs_priv_init :ao_sysctrl err  \n");
			goto fail;
		}

		mci_writel(host, CARDTHRCTL, 0x02000001);

		/*默认为ASIC平台 */
		priv->dw_voltage_switch_gpio = SDMMC_ASIC_PLATFORM;

		priv->peri_sysctrl = sc_periph_addr;
		if (!priv->peri_sysctrl) {
			printk(KERN_ERR "dw_mci_hs_priv_init sd :peri_sysctrl err  \n");
			goto fail;
		}

		/*默认tuning是失败，表示没有经过tuning或者tuning失败 */
		host->tuning_result_flag = EMMC_TUNING_FAIL;

	}

	if (priv->id == MMC_SDIO) {
		error = dev_set_name(host->dev, "hi_mci.2");
		if (error < 0) {
			dev_err(host->dev, "dev set name hi_mci.2 fail \n");
			goto fail;
		}

		mci_writel(host, CARDTHRCTL, 0x02000001);
	}

	priv->old_timing = -1;
	host->priv = priv;
	host->hw_mmc_id = priv->id;
	host->flags &= ~DWMMC_IN_TUNING;
	host->flags &= ~DWMMC_TUNING_DONE;

#ifdef CONFIG_BCMDHD
	if (DWMMC_SDIO_ID == priv->id) {
		sdio_host = host;
	}
#endif

#ifdef CONFIG_HI110X_WIFI_ENABLE
	if (isMyConnectivityChip(CHIP_TYPE_HI110X)) {
		if (DWMMC_SDIO_ID == host->hw_mmc_id) {
			hi_sdio_host = host;
		}
	}
#endif

	return 0;

fail:
	devm_kfree(host->dev, priv);
	return -1;

}

static int dw_mci_hi6xxx_setup_clock(struct dw_mci *host)
{
	struct dw_mci_hs_priv_data *priv = host->priv;
	int timing = MMC_TIMING_LEGACY;
	int id = priv->id;
	int ret;

	dw_mci_hi6xxx_set_parent(host, timing);

	ret = clk_set_rate(host->ciu_clk, hs_timing_config[id][timing][0]);
	if (ret)
		dev_err(host->dev, "clk_set_rate failed\n");

	dw_mci_hi6xxx_set_controller(host, 0);

	host->tuning_current_sample = -1;
	host->current_div = hs_timing_config[id][timing][1];

	host->tuning_init_sample = (hs_timing_config[id][timing][4] + hs_timing_config[id][timing][5]) / 2;

	dw_mci_hi6xxx_set_timing(host, id, timing, host->tuning_init_sample, host->current_div);

	if (priv->priv_bus_hz == 0)
		host->bus_hz = hs_timing_config[id][timing][6];
	else
		host->bus_hz = priv->priv_bus_hz;

	priv->old_timing = timing;

	return 0;
}

static int dw_mci_hi6xxx_parse_dt(struct dw_mci *host)
{
	struct dw_mci_hs_priv_data *priv = host->priv;
	struct device_node *np = host->dev->of_node;
	enum of_gpio_flags gpio_flags;
	int value = 0;

	if (of_property_read_u32(np, "hisi,bus_hz", &value)) {
		dev_info(host->dev, "bus_hz property not found, using " "value of 0 as default\n");
		value = 0;
	}

	priv->priv_bus_hz = value;

	value = 0;
	if (of_property_read_u32(np, "cd-vol", &value)) {
		dev_info(host->dev, "cd-vol property not found, using " "value of 0 as default\n");
		value = 0;
	}

	priv->cd_vol = value;
	if (of_find_property(np, "card_slot_ldo10_status", NULL)) {
		priv->sd_slot_ldo10_status = SD_SLOT_VOL_OPEN;
	} else {
		priv->sd_slot_ldo10_status = SD_SLOT_VOL_CLOSE;
	}

	dev_info(host->dev, "dts bus_hz = %d \n", priv->priv_bus_hz);
	dev_info(host->dev, "dts cd-vol = %d \n", priv->cd_vol);
	dev_info(host->dev, "dts sd_slot_ldo10_status = %d\n", priv->sd_slot_ldo10_status);

	/* find out mmc_bus_clk supported */
	if (of_property_read_u32(np, "board-mmc-bus-clk", &(priv->dw_mmc_bus_clk))) {
		dev_info(host->dev, "board mmc_bus_clk property not found, " "assuming asic board is available\n");
	}

	dev_info(host->dev, "######board-mmc-bus-clk is %x \n", priv->dw_mmc_bus_clk);

	/* find out voltage_switch of sft supported */
	priv->dw_voltage_switch_gpio = of_get_gpio_by_prop(np, "board-sd-voltage-switch-gpio", 0, 0, &gpio_flags);
	if (!gpio_is_valid(priv->dw_voltage_switch_gpio)) {
		dev_info(host->dev, "board-sd-voltage-switch-gpio not available");
		priv->dw_voltage_switch_gpio = SDMMC_ASIC_PLATFORM;
	}

	dev_info(host->dev, "######dw_voltage_switch_gpio is %x \n", priv->dw_voltage_switch_gpio);

	if (of_find_property(np, "cs_board", NULL)) {
		printk(KERN_ERR "$$$ cs board \n");
		if (DWMMC_EMMC_ID == priv->id)
			priv->cs = EMMC_CS_BOARD;
		else if (DWMMC_SD_ID == priv->id)
			priv->cs = SD_CS_BOARD;
	} else {
		printk(KERN_ERR "$$$ not cs board \n");
		priv->cs = 0;
	}

	/*for support SD sdr104 tuning mode */
	if (of_find_property(np, "sd_tuning_sdr104", NULL)) {
		if (host->drv_data && host->drv_data->caps)
			host->drv_data->caps[1] |= MMC_CAP_UHS_SDR104;
	}

	return 0;
}

static irqreturn_t dw_mci_hi6xxx_card_detect(int irq, void *data)
{
	struct dw_mci *host = (struct dw_mci *)data;
	host->sd_reinit = 0;
	host->sd_hw_timeout = 0;
	host->flags &= ~DWMMC_IN_TUNING;
	host->flags &= ~DWMMC_TUNING_DONE;
	/*dw_mci_work_routine_card */
	queue_work(host->card_workqueue, &host->card_work);
	return IRQ_HANDLED;
};

static int dw_mci_hi6xxx_get_cd(struct dw_mci *host, u32 slot_id)
{
	unsigned int status;
	struct dw_mci_hs_priv_data *priv = host->priv;

	if (priv->cd_vol)			/* cd_vol = 1 means sdcard gpio detect pin active-high */
		status = !gpio_get_value(priv->gpio_cd);
	else						/* cd_vol = 0 means sdcard gpio detect pin active-low */
		status = gpio_get_value(priv->gpio_cd);

	dev_info(host->dev, " sd status = %d\n", status);
	return status;
}

static int dw_mci_hi6xxx_cd_detect_init(struct dw_mci *host)
{
	struct device_node *np = host->dev->of_node;
	enum of_gpio_flags gpio_flags;
	int gpio;
	int err;

	if (host->pdata->quirks & DW_MCI_QUIRK_BROKEN_CARD_DETECTION)
		return 0;

	gpio = of_get_gpio_by_prop(np, "cd-gpio", 0, 0, &gpio_flags);
	if (gpio_is_valid(gpio)) {
		if (devm_gpio_request(host->dev, gpio, "dw-mci-cd")) {
			dev_err(host->dev, "gpio [%d] request failed\n", gpio);
		} else {
			struct dw_mci_hs_priv_data *priv = host->priv;
			priv->gpio_cd = gpio;
			host->pdata->get_cd = dw_mci_hi6xxx_get_cd;
			err = devm_request_irq(host->dev, gpio_to_irq(gpio), dw_mci_hi6xxx_card_detect, IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING | IRQF_NO_SUSPEND, DRIVER_NAME, host);
			if (err)
				dev_warn(mmc_dev(host->dev), "request gpio irq error\n");
		}

	} else {
		dev_info(host->dev, "cd gpio not available");
	}

	return 0;
}

static int dw_mci_hi6xxx_card_busy(struct dw_mci *host)
{
	if ((mci_readl(host, STATUS) & SDMMC_DATA_BUSY)
		|| host->cmd || host->data || host->mrq || (host->state != STATE_IDLE)) {
		dev_vdbg(host->dev, " card is busy!");
		return 1;
	}

	return 0;
}

/* Common capabilities of hi3630 SoC */
static unsigned long hi6xxx_dwmmc_caps[3] = {
	/* emmc */
	MMC_CAP_NONREMOVABLE | MMC_CAP_8_BIT_DATA | MMC_CAP_MMC_HIGHSPEED | MMC_CAP_ERASE | MMC_CAP_CMD23,
	/* sd */
	MMC_CAP_DRIVER_TYPE_A | MMC_CAP_4_BIT_DATA | MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED | MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 | MMC_CAP_UHS_SDR50,
	/* sdio */
	MMC_CAP_4_BIT_DATA | MMC_CAP_SDIO_IRQ | MMC_CAP_SD_HIGHSPEED | MMC_CAP_NONREMOVABLE,
};

static void dw_mci_hi6xxx_set_sel18(bool set)
{
	struct device_node *np = NULL;
	void __iomem *sys_base;
	u32 reg;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (np) {
		sys_base = of_iomap(np, 0);
	} else {
		return;
	}

	reg = readl(sys_base + SCPERCTRL5);
	if (set)
		reg |= BIT_SDCARD_IO_SEL18;
	else
		reg &= ~BIT_SDCARD_IO_SEL18;

	printk(KERN_INFO " dw_mci_set_sel18 reg = 0x%x\n", reg);

	writel(reg, sys_base + SCPERCTRL5);
}

/*SOC1006*/
static int dw_mci_hi6xxx_3_3v_signal_voltage_switch(struct dw_mci_slot *slot)
{
	struct dw_mci *host = slot->host;
	int ret = 0;
	unsigned int ao_sysctrl_sd_io = 0;
	struct dw_mci_hs_priv_data *priv = host->priv;

	if (SDMMC_ASIC_PLATFORM != priv->dw_voltage_switch_gpio) {
		/*控制I/O口电平 3V3 */
		gpio_direction_output(priv->dw_voltage_switch_gpio, 1);
		return ret;
	} else {
		/*
		   设置AO_SCTRL寄存器SC_MCU_SUBSYS_CTRL3. aob_io_sel18_sd为0，
		   选择SD的IO电平为3.0V
		 */
		ao_sysctrl_sd_io = readl((SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_ADDR(priv->ao_sysctrl)));
		ao_sysctrl_sd_io &= ~(0x1 << SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_aob_io_sel18_sd_START);

		writel(ao_sysctrl_sd_io, SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_ADDR(priv->ao_sysctrl));

		if (host->vqmmc) {
			ret = regulator_set_voltage(host->vqmmc, 3000000, 3000000);
			if (ret) {
				dev_warn(host->dev, "Switching to 3.0V signalling " "voltage failed\n");
				return -EIO;
			}

			ret = regulator_enable(host->vqmmc);
			if (ret) {
				dev_err(host->dev, "regulator_enable 3.0V failed !\n");
				return -EIO;
			}

		}

		/* Wait for 5ms */
		usleep_range(5000, 5500);

		return ret;
	}

}

/*SOC1006*/
static int dw_mci_hi6xxx_1_8v_signal_voltage_switch(struct dw_mci_slot *slot)
{
	unsigned long loop_count = 0x100000;
	struct dw_mci *host = slot->host;
	int ret = 0;
	int intrs;
	unsigned int ao_sysctrl_sd_io = 0;
	struct dw_mci_hs_priv_data *priv = host->priv;

	/* disable interrupt upon voltage switch. handle interrupt here
	   and DO NOT triggle irq */
	mci_writel(host, CTRL, (mci_readl(host, CTRL) & ~SDMMC_CTRL_INT_ENABLE));

	/* stop clock */
	mci_writel(host, CLKENA, (0x0 << 0));
	mci_writel(host, CMD, SDMMC_CMD_ONLY_CLK | SDMMC_VOLT_SWITCH);
	do {
		if (!(mci_readl(host, CMD) & SDMMC_CMD_START))
			break;
		loop_count--;
	} while (loop_count);

	if (!loop_count)
		dev_err(host->dev, " disable clock failed in voltage_switch\n");

	mmiowb();

	if (SDMMC_ASIC_PLATFORM != priv->dw_voltage_switch_gpio) {
		/*控制I/O口电平 1V8 */
		gpio_direction_output(priv->dw_voltage_switch_gpio, 0);
	} else {
		if (host->vqmmc) {
			if (host->vqmmc)
				regulator_disable(host->vqmmc);

			/*
			   设置AO_SCTRL寄存器SC_MCU_SUBSYS_CTRL3. aob_io_sel18_sd为1，
			   选择SD的IO电平为1.8V
			 */
			ao_sysctrl_sd_io = readl(SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_ADDR(priv->ao_sysctrl));
			ao_sysctrl_sd_io |= (0x1 << SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_aob_io_sel18_sd_START);

			writel(ao_sysctrl_sd_io, SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_ADDR(priv->ao_sysctrl));

			ret = regulator_set_voltage(host->vqmmc, 1800000, 1800000);
			if (ret) {
				dev_warn(host->dev, "Switching to 1.8V signalling " "voltage failed\n");
				return -EIO;
			}

			ret = regulator_enable(host->vqmmc);
			if (ret) {
				dev_err(host->dev, "regulator_enable 1v8 failed !\n");
				return -EIO;
			}
		}
	}

	/* Wait for 5ms */
	usleep_range(5000, 5500);

	dw_mci_hi6xxx_set_sel18(1);
	/* voltage switch cont. */

	/* start clock */
	mci_writel(host, CLKENA, (0x1 << 0));
	mci_writel(host, CMD, SDMMC_CMD_ONLY_CLK | SDMMC_VOLT_SWITCH);
	loop_count = 0x100000;
	do {
		if (!(mci_readl(host, CMD) & SDMMC_CMD_START))
			break;
		loop_count--;
	} while (loop_count);

	if (!loop_count)
		dev_err(host->dev, " enable clock failed in voltage_switch\n");

	/* poll cd interrupt */
	loop_count = 0x100000;
	do {
		intrs = mci_readl(host, RINTSTS);
		if (intrs & SDMMC_INT_CMD_DONE) {
			dev_err(host->dev, " cd 0x%x in voltage_switch\n", intrs);
			mci_writel(host, RINTSTS, intrs);
			break;
		}
		loop_count--;
	} while (loop_count);

	if (!loop_count)
		dev_err(host->dev, " poll cd failed in voltage_switch\n");

	/* enable interrupt */
	mci_writel(host, CTRL, (mci_readl(host, CTRL) | SDMMC_CTRL_INT_ENABLE));

	mmiowb();

	return ret;
}

static int dw_mci_hi6xxx_start_signal_voltage_switch(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	int ret = 0;

	/* only sd need to switch voltage */
	if (slot->host->hw_mmc_id != DWMMC_SD_ID)
		return ret;
	pm_runtime_get_sync(mmc_dev(mmc));

	if (ios->signal_voltage == MMC_SIGNAL_VOLTAGE_330)
		ret = dw_mci_hi6xxx_3_3v_signal_voltage_switch(slot);
	else if (ios->signal_voltage == MMC_SIGNAL_VOLTAGE_180)
		ret = dw_mci_hi6xxx_1_8v_signal_voltage_switch(slot);

	pm_runtime_mark_last_busy(mmc_dev(mmc));
	pm_runtime_put_autosuspend(mmc_dev(mmc));

	return ret;
}

static void dw_mci_hi6xxx_clear_set_irqs(struct dw_mci *host, u32 clear, u32 set)
{
	u32 ier;

	ier = mci_readl(host, INTMASK);
	ier &= ~clear;
	ier |= set;
	mci_writel(host, INTMASK, ier);
}

static void dw_mci_hi6xxx_unmask_irqs(struct dw_mci *host, u32 irqs)
{
	dw_mci_hi6xxx_clear_set_irqs(host, 0, irqs);
}

static void dw_mci_hi6xxx_set_card_detection(struct dw_mci *host, bool enable)
{
	u32 irqs = INTMSK_CDETECT;

	if (enable)
		dw_mci_hi6xxx_unmask_irqs(host, irqs);
	else
		;
}

static void dw_mci_hi6xxx_enable_card_detection(struct dw_mci *host)
{
	dw_mci_hi6xxx_set_card_detection(host, true);
}

static void dw_mci_hi6xxx_reset_ciu(struct dw_mci *host)
{
	u32 timeout = 100;
	u32 ier;

	ier = mci_readl(host, CTRL);
	ier |= CTRL_RESET;

	mci_writel(host, CTRL, ier);
	while (mci_readl(host, CTRL) & CTRL_RESET) {
		if (timeout == 0) {
			printk(KERN_ERR "Reset CTRL never completed.\n");
			return;
		}
		timeout--;
		mdelay(1);
	}
}

static void dw_mci_hi6xxx_reset_fifo(struct dw_mci *host)
{
	u32 timeout = 100;
	u32 ier;

	ier = mci_readl(host, CTRL);
	ier |= FIFO_RESET;

	mci_writel(host, CTRL, ier);
	while (mci_readl(host, CTRL) & FIFO_RESET) {
		if (timeout == 0) {
			printk(KERN_ERR "Reset FIFO never completed.\n");
			return;
		}
		timeout--;
		mdelay(1);
	}
}

static void dw_mci_hi6xxx_reset_all(struct dw_mci *host)
{
	dw_mci_hi6xxx_reset_ciu(host);
	dw_mci_hi6xxx_reset_fifo(host);
}

static void dw_mci_hi6xxx_init(struct dw_mci *host)
{
	dw_mci_hi6xxx_reset_all(host);
}

static void dw_mci_hi6xxx_reinit(struct dw_mci *host)
{
	dw_mci_hi6xxx_init(host);

	dw_mci_hi6xxx_enable_card_detection(host);
}

static void dw_mci_hi6xxx_tuning_fail_excprocess(struct dw_mci *host)
{
	unsigned int ctype_flags;
	unsigned int uhs_flags;
	unsigned int fifoth;
	unsigned int timeout;
	unsigned int _timeout;
	unsigned int cardthrctrl;
	unsigned int intmask_flags;
	unsigned int _intmask_flags;
	unsigned int retval = 0;
	unsigned int _rintsts;
	unsigned int _tcbcnt;
	unsigned int _tbbcnt;
	unsigned int _idsts;
	unsigned int _bufaddr;
	unsigned int _clkena;
	unsigned int _fifoth;

	if (NULL == host) {
		printk("mshci_tuning_fail_excprocess: host is null \n");
		return;
	}

	udelay(450);

	/*配置寄存器CTRL bit4为0，禁止MMC0中断 */
	mci_writel(host, CTRL, (mci_readl(host, CTRL) & (~INT_ENABLE)));
	mci_writel(host, INTMASK, 0);

	/*配置RINTSTS寄存器，清除所有中断 */
	mci_writel(host, RINTSTS, INTMSK_ALL);

	/*配置IDSTA寄存器，清除所有内部DMA中断 */
	retval = mci_readl(host, IDSTS);
	mci_writel(host, IDSTS, retval | 0x337);

	/*备份寄存器 CTYPE,FIFOTH,TIMOUT,CardThrCtl和HS_REG */
	ctype_flags = mci_readl(host, CTYPE);
	fifoth = mci_readl(host, FIFOTH);
	timeout = mci_readl(host, TMOUT);
	cardthrctrl = mci_readl(host, CARDTHRCTL);
	uhs_flags = mci_readl(host, UHS_REG);
	intmask_flags = mci_readl(host, INTMASK);
#if 0
	/*配置SC_PERIPH_RSTEN0[0]:使能mmc0 ip复位 */
	writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_mmc0_START, SOC_PERI_SCTRL_SC_PERIPH_RSTEN0_ADDR(priv->peri_sysctrl));

	udelay(10);

	/*配置SC_PERIPH_RSTDIS0[0]:去使能mmc0 ip复位 */
	writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_mmc0_START, SOC_PERI_SCTRL_SC_PERIPH_RSTDIS0_ADDR(priv->peri_sysctrl));
#endif
	/*mmc0 ip复位后检查寄存器 */
	_intmask_flags = mci_readl(host, INTMASK);
	_timeout = mci_readl(host, TMOUT);
	_rintsts = mci_readl(host, RINTSTS);
	_tcbcnt = mci_readl(host, TCBCNT);
	_tbbcnt = mci_readl(host, TBBCNT);
	_idsts = mci_readl(host, IDSTS);
	_bufaddr = mci_readl(host, BUFADDR);
	retval = mci_readl(host, CTRL);

	printk(KERN_ERR "before  mshci_tuning_fail_excprocess: CTRL=%x, INTMASK=%x," "TMOUT=%x, RINTSTS=%x, TCBCNT=%x, TBBCNT=%x, IDSTS=%x, BUFADDR=%x, FIFOTH=%x \n", retval, _intmask_flags, _timeout, _rintsts, _tcbcnt, _tbbcnt, _idsts, _bufaddr, fifoth);

	udelay(20);

	dw_mci_hi6xxx_reinit(host);

	/*恢复备份寄存器 */
	mci_writel(host, CTYPE, ctype_flags);
	mci_writel(host, FIFOTH, fifoth);
	mci_writel(host, TMOUT, timeout);
	mci_writel(host, CARDTHRCTL, cardthrctrl);
	mci_writel(host, UHS_REG, uhs_flags);

	/*配置IDSTA寄存器，清除所有内部DMA中断 */
	retval = mci_readl(host, IDSTS);
	mci_writel(host, IDSTS, retval | 0x337);

	/* clear interrupt status */
	mci_writel(host, RINTSTS, INTMSK_ALL);

	dw_mci_hi6xxx_clear_set_irqs(host, INTMSK_ALL, INTMSK_CDETECT | INTMSK_RE
		| INTMSK_CDONE | INTMSK_DTO | INTMSK_RCRC | INTMSK_DCRC | INTMSK_RTO
			| INTMSK_DRTO | INTMSK_HTO | INTMSK_HLE | INTMSK_SBE | INTMSK_EBE);

	/*配置寄存器CTRL bit25为1-使能IDMA；bit4为1-使能MMC0中断 */
	mci_writel(host, CTRL, 0x2000010);

	/*配置MMC0内部寄存器，重新eMMC接口时钟 */
	host->clock_to_restore = host->bus_hz;

	dw_mci_hi6xxx_set_clock(host, host->clock_to_restore);

	/*复位恢复时钟使能后检查寄存器 */
	retval = mci_readl(host, CTRL);
	intmask_flags = mci_readl(host, INTMASK);
	_rintsts = mci_readl(host, RINTSTS);
	_tcbcnt = mci_readl(host, TCBCNT);
	_tbbcnt = mci_readl(host, TBBCNT);
	_idsts = mci_readl(host, IDSTS);
	_bufaddr = mci_readl(host, BUFADDR);
	_clkena = mci_readl(host, CLKENA);
	_fifoth = mci_readl(host, FIFOTH);

	printk(KERN_ERR "after mshci_tuning_fail_excprocess: CTR=%x, INTMASK=%x,"
		"RINTSTS=%x, TCBCNT=%x, TBBCNT=%x, IDSTS=%x, BUFADDR=%x，CLKENA=%x, FIFOTH=%x\n",
			retval, intmask_flags, _rintsts, _tcbcnt, _tbbcnt, _idsts, _bufaddr, _clkena, _fifoth);
}

/*
SOC1005
turing 的策略:
一共15个turning点
  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
  1 1 1 0 0 0 1 1 1 1 1   0  0  1  1

如上图，如果turning成功，那么对应bit设置为1，turning完毕后，选择连续为1最多的频点
取中间频点作为最优频点设置
*/
int dw_mci_hi6xxx_mmc_es_tuning(struct dw_mci_slot *slot)
{
	struct dw_mci *host = slot->host;
	struct dw_mci_hs_priv_data *priv = host->priv;
	struct mmc_host *mmc = slot->mmc;
	struct mmc_command cmd = { 0 };
	struct mmc_command stop = { 0 };
	struct mmc_request mrq = { 0 };
	struct mmc_data data = { 0 };
	struct scatterlist sg;
	void *data_buf;
	unsigned len = sizeof(tuning_block_128);

	unsigned int use_delay_cell = 0;

	/*是否需要全频率turning */
	bool is_tuning_all_phased = false;

	/*具体开始第一个OK的点 */
	int start_point = -1;

	/*连续OK点的长度 */
	int tuning_point_len = 0;

	int best_start_point = -1;

	int best_tuning_point_len = 0;

	/*记录每个turning点的结果，如果OK，就设置为1 */
	int tuning_result_index[MMC_MAX_TUNING_VALUE + 1] = { 0 };

	int best_tuning_sample_point = 0;

	/*保存开头的成功turning的长度，这个可以和末尾成功turning的合并 */
	int tmp_value = 0;

	int ret = 0;

	int i = 0;

	int tuning_times = 0;

	unsigned mshci_ctrl = 0;

	/* only emmc  work in hs200 need tuning process */
	if (!((host->pdata->quirks & DW_MCI_QUIRK_BROKEN_CARD_DETECTION) && (MMC_TIMING_MMC_HS200 == mmc->ios.timing))) {
		return 0;
	}

	printk(KERN_INFO "mshci_execute_tuning: get into tuning \n");

	/*如果saved_tuning_phase 不等于INVALID_TUNING_PHASE，不turning */
	is_tuning_all_phased = !(mmc->card && (INVALID_TUNING_PHASE != host->saved_tuning_phase));

	printk(KERN_INFO "mshci_execute_tuning: the is_tuning_all_phased is %x,%x \n", is_tuning_all_phased, host->saved_tuning_phase);

	data_buf = kmalloc(len, GFP_KERNEL);
	if (data_buf == NULL)
		return -ENOMEM;

	mrq.cmd = &cmd;
	mrq.data = &data;
	mrq.stop = NULL;

	cmd.opcode = MMC_SEND_TUNING_BLOCK_HS200;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;
	data.error = 0;
	data.stop = mrq.stop;
	data.mrq = &mrq;
	data.blksz = 512;

	stop.retries = 0;
	stop.error = 0;
	stop.data = NULL;
	stop.opcode = MMC_STOP_TRANSMISSION;
	stop.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;

	pm_runtime_get_sync(mmc_dev(mmc));
	mci_writel(host, UHS_REG_EXT, 0x00);

	if (data.blksz > len)
		data.blksz = len;

	sg_init_one(&sg, data_buf, data.blocks * data.blksz);

	memset(data_buf, 0, len);

	host->flags |= DWMMC_IN_TUNING;

	host->flags &= ~DWMMC_TUNING_DONE;

	/*SOC1002:MMC0在HS200模式下必须将SC_PERIPH_CTRL2[0]设为0，以使能采样时钟移相 */
	writel(readl(SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl)) & (~0x1),
		SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl));

	/*SOC1004:SC_PERIPH_CLKEN12[7:6]: 移相高频时钟门控 */
	/*writel(0x1<<SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mmc0_hf_START,*/
	/*     SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_ADDR(priv->peri_sysctrl));*/

	/* enter tuning */
retry:

	/*需要全部turning */
	if (is_tuning_all_phased) {
		tuning_times++;

		for (i = 0; i <= MMC_MAX_TUNING_VALUE; i++) {
			printk(KERN_INFO "mshci_execute_tuning: the %d times \n", i);

			/* this timeout setting may not be called */
			if (mmc->card) {
				mmc_set_data_timeout(&data, mmc->card);
			}

			mshci_ctrl = mci_readl(host, CTRL);

			printk(KERN_INFO "mshci_execute_tuning: ctrl is the %x  \n", mshci_ctrl);

			/*SOC:步骤 1    配置寄存器UHS_REG_EXT[22]为1'b1,使能寄存器打拍功能 */
			/*SOC:步骤 2    配置寄存器UHS_REG_EXT[19:16]为4'bXXXX，MMC_UHS_REG_EXT[21]为1'b0，移相相位为XXXX° */
			writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mmc0_hf_START,
				SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_ADDR(priv->peri_sysctrl));

			mci_writel(host, UHS_REG_EXT, (0x1 << MMC_UHS_REG_EXT_22BIT) | (0x0 << MMC_UHS_REG_EXT_MIN) | (i << MMC_UHS_REG_EXT_MACRO));

			writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mmc0_hf_START,
				SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_ADDR(priv->peri_sysctrl));

			cmd.error = 0;

			data.error = 0;

			mmc_wait_for_req(mmc, &mrq);

			mshci_ctrl = mci_readl(host, CTRL);

			printk(KERN_INFO "######mshci_execute_tuning: ctrl is the %x  \n", mshci_ctrl);

			if (cmd.error != 0 || data.error != 0 || memcmp(data_buf, tuning_block_128, sizeof(tuning_block_128)) != 0) {

				dw_mci_hi6xxx_tuning_fail_excprocess(host);

				if (start_point != -1) {
					if (tuning_point_len > best_tuning_point_len) {
						best_tuning_point_len = tuning_point_len;
						best_start_point = start_point;
					}

					if (TURNING_SUCCESS_FIRST_POINT == start_point) {
						tmp_value = tuning_point_len;
					}
				}

				start_point = -1;

				tuning_point_len = 0;

			} else {
				if (-1 == start_point) {
					start_point = i;
				}

				tuning_point_len++;

				tuning_result_index[i] = 1;

			}
		}
	}

	printk(KERN_INFO "tuning_point_len is %d,best_tuning_point_len is %d,start_point is %d, best_start_point is %d \n", tuning_point_len, best_tuning_point_len, start_point, best_start_point);

	if (tuning_point_len > best_tuning_point_len) {
		best_tuning_point_len = tuning_point_len;
		best_start_point = start_point;
	}

	/*如果头尾都turning成功，则合并 */
	if (tuning_result_index[MMC_MAX_TUNING_VALUE] & tuning_result_index[0]) {
		if ((tuning_point_len + tmp_value) > best_tuning_point_len) {
			best_tuning_point_len = tuning_point_len + tmp_value;
			best_start_point = start_point;
		}
	}

	if ((best_tuning_point_len > 1) && (0 == best_tuning_point_len % 2)) {	/*偶数 */

		best_tuning_sample_point = best_start_point + best_tuning_point_len / 2 - 1;

		if (best_tuning_sample_point > MMC_MAX_TUNING_VALUE) {
			best_tuning_sample_point = best_tuning_sample_point - MMC_MAX_TUNING_VALUE - 1;
		}

		/*步骤 10   如果N为偶数，则选取N/2的相位点，再通过配置UHS_REG_EXT[21]使能DELAY_CELL */
		/*mci_writel(host,UHS_REG_EXT,mci_readl(host,UHS_REG_EXT)|(0x1<<MMC_UHS_REG_EXT_MIN));*/
		use_delay_cell = 1;

		emmc_hs200_tuning_point = best_tuning_sample_point;
	}

	if ((best_tuning_point_len > 1) && (1 == best_tuning_point_len % 2)) {	/*奇数 */
		best_tuning_sample_point = best_start_point + best_tuning_point_len / 2;

		if (best_tuning_sample_point > MMC_MAX_TUNING_VALUE) {
			best_tuning_sample_point = best_tuning_sample_point - MMC_MAX_TUNING_VALUE - 1;
		}

		emmc_hs200_tuning_point = best_tuning_sample_point;
	}

	/*tuning failed or noneed turning */
	if (best_tuning_point_len < 2) {
		if (!is_tuning_all_phased) {
			printk(KERN_ERR "dw_mci_hi6xxx_tuning: ####resume#### \n");

			best_tuning_sample_point = host->saved_tuning_phase;
		} else {
			best_tuning_sample_point = -1;
		}
	}

	if (best_tuning_sample_point >= 0) {
		best_tuning_point_len = best_tuning_point_len >> 0x1;
tryagain:
		/*mci_writel(host,UHS_REG_EXT,(mci_readl(host,UHS_REG_EXT)&0xFFF0FFFF)|(best_tuning_sample_point << MMC_UHS_REG_EXT_MACRO));*/
		writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mmc0_hf_START, SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_ADDR(priv->peri_sysctrl));

		mci_writel(host, UHS_REG_EXT, (0x1 << MMC_UHS_REG_EXT_22BIT) | (use_delay_cell << MMC_UHS_REG_EXT_MIN) | (best_tuning_sample_point << MMC_UHS_REG_EXT_MACRO));

		writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mmc0_hf_START, SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_ADDR(priv->peri_sysctrl));

		printk(KERN_INFO "the best tuning point is %d eMMC HS200 tuning success \n", best_tuning_sample_point);
		/* check again */
		cmd.error = 0;
		data.error = 0;

		mmc_wait_for_req(mmc, &mrq);

		if (cmd.error != 0 || data.error != 0 || memcmp(data_buf, tuning_block_128, sizeof(tuning_block_128)) != 0) {
			/*稳定性提升修改:如果最佳tuning点失败，使用就近点继续tuning，确保找到可以的点 */
			if (best_tuning_point_len > 0) {
				use_delay_cell = 0;

				best_tuning_point_len--;
				if (best_tuning_sample_point == 0) {
					best_tuning_sample_point = 15;
					goto tryagain;
				}

				best_tuning_sample_point--;

				goto tryagain;
			}

			if (!is_tuning_all_phased) {
				is_tuning_all_phased = true;
				goto retry;
			} else {
				if (tuning_times < 3) {
					is_tuning_all_phased = true;
					goto retry;
				}
				udelay(450);

				printk(KERN_INFO "eMMC HS200 tuning failed \n");

				/*SEL SYS-PLL */
				writel(readl(SOC_PERI_SCTRL_SC_CLK_SEL0_ADDR(priv->peri_sysctrl)) | (0x1 << SOC_PERI_SCTRL_SC_CLK_SEL0_sel_clk_mmc_START), SOC_PERI_SCTRL_SC_CLK_SEL0_ADDR(priv->peri_sysctrl));

				/* when tuning fail give up HS200 choose DDR50 */
				mmc->caps2 &= ~MMC_CAP2_HS200_1_8V_SDR;

				/*SOC1002:bypass en，低频 */
				writel(readl(SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl)) | (0x1), SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl));

				/*SOC1004:关闭高频时钟门控 */
				writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mmc0_hf_START, SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_ADDR(priv->peri_sysctrl));

				host->tuning_result_flag = EMMC_TUNING_FAIL;

				ret = -1;
			}
		} else {
			host->saved_tuning_phase = best_tuning_sample_point;
			printk(KERN_ERR "eMMC HS200 tuning OK,the tuning point is %d\n", host->saved_tuning_phase);
			host->tuning_result_flag = EMMC_TUNING_SUCCESS;
		}
	} else {
		printk(KERN_ERR "$eMMC HS200 tuning failed \n");
		/* when tuning fail give up HS200 choose DDR50 */

		/*SEL SYS-PLL */
		writel(readl(SOC_PERI_SCTRL_SC_CLK_SEL0_ADDR(priv->peri_sysctrl)) | (0x1 << SOC_PERI_SCTRL_SC_CLK_SEL0_sel_clk_mmc_START), SOC_PERI_SCTRL_SC_CLK_SEL0_ADDR(priv->peri_sysctrl));

		mmc->caps2 &= ~MMC_CAP2_HS200_1_8V_SDR;

		/*SOC1002:bypass en，低频 */
		writel(readl(SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl)) | (0x1), SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl));

		/*SOC1004:关闭高频时钟门控 */
		writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mmc0_hf_START, SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_ADDR(priv->peri_sysctrl));

		host->tuning_result_flag = EMMC_TUNING_FAIL;

		ret = -1;
	}

	host->flags &= ~DWMMC_IN_TUNING;

	host->flags |= DWMMC_TUNING_DONE;

	host->tuning_done = true;

	kfree(data_buf);
	pm_runtime_mark_last_busy(mmc_dev(mmc));
	pm_runtime_put_autosuspend(mmc_dev(mmc));
	return ret;
}

/*
SOC1005
turing 的策略:
一共15个turning点
  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
  1 1 1 0 0 0 1 1 1 1 1   0  0  1  1

如上图，如果turning成功，那么对应bit设置为1，turning完毕后，选择连续为1最多的频点
取中间频点作为最优频点设置
*/
int dw_mci_hi6xxx_mmc_cs_tuning(struct dw_mci_slot *slot)
{
	struct dw_mci *host = slot->host;
	struct dw_mci_hs_priv_data *priv = host->priv;
	struct mmc_host *mmc = slot->mmc;
	struct mmc_command cmd = { 0 };
	struct mmc_command stop = { 0 };
	struct mmc_request mrq = { 0 };
	struct mmc_data data = { 0 };
	struct scatterlist sg;
	void *data_buf;
	unsigned len = sizeof(tuning_block_128);

	unsigned int use_delay_cell = 0;

	/*是否需要全频率turning */
	bool is_tuning_all_phased = false;

	/*具体开始第一个OK的点 */
	int start_point = -1;

	/*连续OK点的长度 */
	int tuning_point_len = 0;

	int best_start_point = -1;

	int best_tuning_point_len = 0;

	/*记录每个turning点的结果，如果OK，就设置为1 */
	int tuning_result_index[MMC_MAX_TUNING_CS_VALUE + 1] = { 0 };

	unsigned int best_tuning_sample_point = 0;

	/*保存开头的成功turning的长度，这个可以和末尾成功turning的合并 */
	int tmp_value = 0;

	int ret = 0;

	unsigned int i = 0;

	unsigned int tuning_phase = 0;

	int tuning_times = 0;

	unsigned mshci_ctrl = 0;

	int tuning_all_success_flag = 0;

	int odd_even = 0;			/*1:odd  0:even */

	/* only emmc  work in hs200 need tuning process */
	if (!((host->pdata->quirks & DW_MCI_QUIRK_BROKEN_CARD_DETECTION) && (MMC_TIMING_MMC_HS200 == mmc->ios.timing))) {
		return 0;
	}

	printk(KERN_INFO "mshci_execute_tuning: get into tuning \n");

	/*如果saved_tuning_phase 不等于INVALID_TUNING_PHASE，不turning */
	is_tuning_all_phased = !(mmc->card && (INVALID_TUNING_PHASE != host->saved_tuning_phase));

	printk(KERN_INFO "mshci_execute_tuning: the is_tuning_all_phased is %x,%x \n", is_tuning_all_phased, host->saved_tuning_phase);

	data_buf = kmalloc(len, GFP_KERNEL);
	if (data_buf == NULL)
		return -ENOMEM;

	mrq.cmd = &cmd;
	mrq.data = &data;
	mrq.stop = NULL;

	cmd.opcode = MMC_SEND_TUNING_BLOCK_HS200;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;
	data.error = 0;
	data.stop = mrq.stop;
	data.mrq = &mrq;
	data.blksz = 128;

	stop.retries = 0;
	stop.error = 0;
	stop.data = NULL;
	stop.opcode = MMC_STOP_TRANSMISSION;
	stop.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;

	pm_runtime_get_sync(mmc_dev(mmc));

	mci_writel(host, UHS_REG_EXT, 0x00);

	if (data.blksz > len)
		data.blksz = len;

	sg_init_one(&sg, data_buf, data.blocks * data.blksz);

	memset(data_buf, 0, len);

	host->flags |= DWMMC_IN_TUNING;

	host->flags &= ~DWMMC_TUNING_DONE;

	/*SOC1002:MMC0在HS200模式下必须将SC_PERIPH_CTRL2[0]设为0，以使能采样时钟移相 */
	writel(readl(SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl)) & (~0x1), SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl));

	/* enter tuning */
retry:

	/*需要全部turning */
	if (is_tuning_all_phased) {

		for (i = 0; i <= MMC_MAX_TUNING_CS_VALUE; i++) {
			odd_even = EMMC_IS_ODD(i) ? (EMMC_TUNING_POINT_ODD) : (EMMC_TUNING_POINT_EVEN);

			tuning_phase = EMMC_IS_ODD(i) ? ((i - 1) / 2) : (i / 2);

			printk(KERN_INFO "mshci_execute_tuning: the %d times, odd_even is %d , tuning_phase is %d \n", i, odd_even, tuning_phase);

			/* this timeout setting may not be called */
			if (mmc->card) {
				mmc_set_data_timeout(&data, mmc->card);
			}

			mshci_ctrl = mci_readl(host, CTRL);

			printk(KERN_INFO "mshci_execute_tuning: ctrl is the %x  \n", mshci_ctrl);

			/*SOC:步骤 1    配置寄存器UHS_REG_EXT[22]为1'b1,使能寄存器打拍功能 */
			/*SOC:步骤 2    配置寄存器UHS_REG_EXT[19:16]为4'bXXXX，MMC_UHS_REG_EXT[21]为1'b0，移相相位为XXXX° */
			writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mmc0_hf_START, SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_ADDR(priv->peri_sysctrl));

			if (EMMC_TUNING_POINT_ODD == odd_even) {
				mci_writel(host, UHS_REG_EXT, (0x1 << MMC_UHS_REG_EXT_22BIT) | (0x1 << MMC_UHS_REG_EXT_MIN) | (tuning_phase << MMC_UHS_REG_EXT_MACRO));
			} else {
				mci_writel(host, UHS_REG_EXT, (0x1 << MMC_UHS_REG_EXT_22BIT) | (0x0 << MMC_UHS_REG_EXT_MIN) | (tuning_phase << MMC_UHS_REG_EXT_MACRO));
			}

			writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mmc0_hf_START, SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_ADDR(priv->peri_sysctrl));

			cmd.error = 0;

			data.error = 0;

			mmc_wait_for_req(mmc, &mrq);

			mshci_ctrl = mci_readl(host, CTRL);

			printk(KERN_INFO "######mshci_execute_tuning: ctrl is the %x  \n", mshci_ctrl);

			if (cmd.error != 0 || data.error != 0 || memcmp(data_buf, tuning_block_128, sizeof(tuning_block_128)) != 0) {

				dw_mci_hi6xxx_tuning_fail_excprocess(host);

				if (start_point != -1) {
					if (tuning_point_len > best_tuning_point_len) {
						best_tuning_point_len = tuning_point_len;
						best_start_point = start_point;
					}

					if (TURNING_SUCCESS_FIRST_POINT == start_point) {
						tmp_value = tuning_point_len;
					}
				}

				start_point = -1;

				tuning_point_len = 0;

			} else {
				if (-1 == start_point) {
					start_point = i;
				}

				tuning_point_len++;

				tuning_result_index[i] = 1;
			}
		}
	}

	printk(KERN_INFO "tuning_point_len is %d,best_tuning_point_len is %d,start_point is %d, best_start_point is %d \n", tuning_point_len, best_tuning_point_len, start_point, best_start_point);

	if (tuning_point_len > best_tuning_point_len) {
		best_tuning_point_len = tuning_point_len;
		best_start_point = start_point;
	}

	/*如果头尾都turning成功，则合并 */
	if (tuning_result_index[MMC_MAX_TUNING_CS_VALUE] & tuning_result_index[0]) {
		if ((tuning_point_len + tmp_value) > best_tuning_point_len) {
			best_tuning_point_len = tuning_point_len + tmp_value;
			best_start_point = start_point;
		}
	}

	if ((best_tuning_point_len > 1) && (0 == best_tuning_point_len % 2)) {	/*偶数 */

		best_tuning_sample_point = best_start_point + best_tuning_point_len / 2 - 1;

		if (best_tuning_sample_point > MMC_MAX_TUNING_CS_VALUE) {
			best_tuning_sample_point = best_tuning_sample_point - MMC_MAX_TUNING_CS_VALUE - 1;
		}

		emmc_hs200_tuning_point = best_tuning_sample_point;
	}

	if ((best_tuning_point_len > 1) && (1 == best_tuning_point_len % 2)) {	/*奇数 */
		best_tuning_sample_point = best_start_point + best_tuning_point_len / 2;

		if (best_tuning_sample_point > MMC_MAX_TUNING_CS_VALUE) {
			best_tuning_sample_point = best_tuning_sample_point - MMC_MAX_TUNING_CS_VALUE - 1;
		}

		emmc_hs200_tuning_point = best_tuning_sample_point;
	}

	printk(KERN_INFO "dw_mci_hi6xxx_tuning: before ######## our best tuning is %d \n", best_tuning_sample_point);

	if (1 == best_tuning_sample_point % 2) {
		best_tuning_sample_point = (best_tuning_sample_point - 1) / 2;
		use_delay_cell = 1;
	} else {
		best_tuning_sample_point = best_tuning_sample_point / 2;
	}

	printk(KERN_INFO "dw_mci_hi6xxx_tuning: after ######## our best tuning is %d \n", best_tuning_sample_point);

	/*tuning failed or noneed turning */
	if (best_tuning_point_len < 2) {
		if (!is_tuning_all_phased) {
			printk(KERN_ERR "dw_mci_hi6xxx_tuning: ####resume#### \n");

			best_tuning_sample_point = host->saved_tuning_phase;
		} else {
			best_tuning_sample_point = -1;
		}
	}

	if (best_tuning_sample_point >= 0) {
		best_tuning_point_len = best_tuning_point_len >> 0x1;
tryagain:
		writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mmc0_hf_START, SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_ADDR(priv->peri_sysctrl));

		mci_writel(host, UHS_REG_EXT, (0x1 << MMC_UHS_REG_EXT_22BIT) | (use_delay_cell << MMC_UHS_REG_EXT_MIN) | (best_tuning_sample_point << MMC_UHS_REG_EXT_MACRO));

		writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mmc0_hf_START, SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_ADDR(priv->peri_sysctrl));

		printk(KERN_ERR "the best tuning point is %d \n", best_tuning_sample_point);
		/* check again */
		cmd.error = 0;
		data.error = 0;

		mmc_wait_for_req(mmc, &mrq);

		if (cmd.error != 0 || data.error != 0 || memcmp(data_buf, tuning_block_128, sizeof(tuning_block_128)) != 0) {
			/*稳定性提升修改:如果最佳tuning点失败，使用就近点继续tuning，确保找到可以的点 */
			if (best_tuning_point_len > 0) {
				use_delay_cell = 0;

				best_tuning_point_len--;
				if (best_tuning_sample_point == 0) {
					best_tuning_sample_point = 15;
					goto tryagain;
				}

				best_tuning_sample_point--;

				goto tryagain;
			}

			if (!is_tuning_all_phased) {
				is_tuning_all_phased = true;
				goto retry;
			} else {

				udelay(450);

				printk(KERN_ERR "eMMC HS200 tuning failed,reserve to cond \n");

				/*SEL SYS-PLL */
				writel(readl(SOC_PERI_SCTRL_SC_CLK_SEL0_ADDR(priv->peri_sysctrl)) | (0x1 << SOC_PERI_SCTRL_SC_CLK_SEL0_sel_clk_mmc_START), SOC_PERI_SCTRL_SC_CLK_SEL0_ADDR(priv->peri_sysctrl));

				/* when tuning fail give up HS200 choose DDR50 */
				mmc->caps2 &= ~MMC_CAP2_HS200_1_8V_SDR;

				/*SOC1002:bypass en，低频 */
				writel(readl(SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl)) | (0x1), SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl));

				/*SOC1004:关闭高频时钟门控 */
				writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mmc0_hf_START, SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_ADDR(priv->peri_sysctrl));

				mci_writel(host, UHS_REG_EXT, 0);

				dw_mci_hi6xxx_tuning_fail_excprocess(host);

				host->tuning_result_flag = EMMC_TUNING_FAIL;

				ret = -1;
			}
		} else {
			host->saved_tuning_phase = best_tuning_sample_point;
			printk(KERN_ERR "eMMC HS200 tuning OK,the tuning point is %d\n", host->saved_tuning_phase);
			host->tuning_result_flag = EMMC_TUNING_SUCCESS;
		}
	} else {
		printk(KERN_ERR "$eMMC HS200 tuning failed, no good point \n");
		/* when tuning fail give up HS200 choose DDR50 */

		/*SEL SYS-PLL */
		writel(readl(SOC_PERI_SCTRL_SC_CLK_SEL0_ADDR(priv->peri_sysctrl)) | (0x1 << SOC_PERI_SCTRL_SC_CLK_SEL0_sel_clk_mmc_START), SOC_PERI_SCTRL_SC_CLK_SEL0_ADDR(priv->peri_sysctrl));

		mmc->caps2 &= ~MMC_CAP2_HS200_1_8V_SDR;

		/*SOC1002:bypass en，低频 */
		writel(readl(SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl)) | (0x1), SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl));

		/*SOC1004:关闭高频时钟门控 */
		writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mmc0_hf_START, SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_ADDR(priv->peri_sysctrl));

		mci_writel(host, UHS_REG_EXT, 0);

		dw_mci_hi6xxx_tuning_fail_excprocess(host);

		host->tuning_result_flag = EMMC_TUNING_FAIL;

		ret = -1;
	}

	host->flags &= ~DWMMC_IN_TUNING;

	host->flags |= DWMMC_TUNING_DONE;

	host->tuning_done = true;

	kfree(data_buf);

	pm_runtime_mark_last_busy(mmc_dev(mmc));
	pm_runtime_put_autosuspend(mmc_dev(mmc));
	return ret;
}

 /*code for sd SDR104 mode tuning */
int dw_mci_hi6xxx_sd_tuning(struct dw_mci_slot *slot)
{
	struct dw_mci *host = slot->host;
	struct dw_mci_hs_priv_data *priv = host->priv;
	struct mmc_host *mmc = slot->mmc;
	struct mmc_command cmd = { 0 };
	struct mmc_command stop = { 0 };
	struct mmc_request mrq = { 0 };
	struct mmc_data data = { 0 };
	struct scatterlist sg;
	void *data_buf;
	unsigned len = sizeof(tuning_block_64);

	unsigned int use_delay_cell = 0;

	/*是否需要全频率turning */
	bool is_tuning_all_phased = false;

	/*具体开始第一个OK的点 */
	int start_point = -1;

	/*连续OK点的长度 */
	int tuning_point_len = 0;

	int best_start_point = -1;

	int best_tuning_point_len = 0;

	/*记录每个turning点的结果，如果OK，就设置为1 */
	int tuning_result_index[MMC_MAX_TUNING_VALUE + 1] = { 0 };

	int best_tuning_sample_point = 0;

	/*保存开头的成功turning的长度，这个可以和末尾成功turning的合并 */
	int tmp_value = 0;

	int ret = 0;

	int i = 0;

	int tuning_times = 0;

	unsigned mshci_ctrl = 0;

	/* only SD  work in SDR104 need tuning process */
	if (!(MMC_TIMING_UHS_SDR104 == mmc->ios.timing)) {
		return 0;
	}

	printk(KERN_INFO "dw_mci_hi6xxx_sd_tuning: get into tuning \n");

	/*如果saved_tuning_phase 不等于INVALID_TUNING_PHASE，不turning */
	is_tuning_all_phased = !(mmc->card && (INVALID_TUNING_PHASE != host->saved_tuning_phase));

	printk(KERN_INFO "dw_mci_hi6xxx_sd_tuning: the is_tuning_all_phased is %x,%x \n", is_tuning_all_phased, host->saved_tuning_phase);

	data_buf = kmalloc(len, GFP_KERNEL);
	if (data_buf == NULL)
		return -ENOMEM;

	mrq.cmd = &cmd;
	mrq.data = &data;
	mrq.stop = NULL;

	cmd.opcode = MMC_SEND_TUNING_BLOCK;
	cmd.arg = 0;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_ADTC;

	data.blocks = 1;
	data.flags = MMC_DATA_READ;
	data.sg = &sg;
	data.sg_len = 1;
	data.error = 0;
	data.stop = mrq.stop;
	data.mrq = &mrq;
	data.blksz = 512;

	stop.retries = 0;
	stop.error = 0;
	stop.data = NULL;
	stop.opcode = MMC_STOP_TRANSMISSION;
	stop.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;

	pm_runtime_get_sync(mmc_dev(mmc));
	mci_writel(host, UHS_REG_EXT, 0x00);

	if (data.blksz > len)
		data.blksz = len;

	sg_init_one(&sg, data_buf, data.blocks * data.blksz);

	memset(data_buf, 0, len);

	host->flags |= DWMMC_IN_TUNING;

	host->flags &= ~DWMMC_TUNING_DONE;

	/*SOC1002:MMC1在SDR104模式下必须将SC_PERIPH_CTRL2[2]设为0，以使能采样时钟移相 */
	writel(readl(SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl)) & (~(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CTRL2_mmc_clk_phase_bypass_en_mmc1_START)), SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl));

retry:

	/*需要全部turning */
	if (is_tuning_all_phased) {
		tuning_times++;

		for (i = 0; i <= MMC_MAX_TUNING_VALUE; i++) {
			printk(KERN_INFO "dw_mci_hi6xxx_sd_tuning: the %d times \n", i);

			/* this timeout setting may not be called */
			if (mmc->card) {
				mmc_set_data_timeout(&data, mmc->card);
			}

			mshci_ctrl = mci_readl(host, CTRL);

			printk(KERN_INFO "dw_mci_hi6xxx_sd_tuning: ctrl is the %x  \n", mshci_ctrl);

			/*SOC:步骤 1    配置寄存器UHS_REG_EXT[22]为1'b1,使能寄存器打拍功能 */
			/*SOC:步骤 2    配置寄存器UHS_REG_EXT[19:16]为4'bXXXX，MMC_UHS_REG_EXT[21]为1'b0，移相相位为XXXX° */
			writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mmc1_hf_START,
				SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_ADDR(priv->peri_sysctrl));

			mci_writel(host, UHS_REG_EXT, (0x1 << MMC_UHS_REG_EXT_22BIT)
				| (0x0 << MMC_UHS_REG_EXT_MIN) | (i << MMC_UHS_REG_EXT_MACRO));

			writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mmc1_hf_START,
				SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_ADDR(priv->peri_sysctrl));

			cmd.error = 0;

			data.error = 0;

			mmc_wait_for_req(mmc, &mrq);

			mshci_ctrl = mci_readl(host, CTRL);

			printk(KERN_INFO "######mshci_execute_tuning: ctrl is the %x  \n", mshci_ctrl);

			if (cmd.error != 0 || data.error != 0 || memcmp(data_buf, tuning_block_64, sizeof(tuning_block_64)) != 0) {

				dw_mci_hi6xxx_tuning_fail_excprocess(host);

				if (start_point != -1) {
					if (tuning_point_len > best_tuning_point_len) {
						best_tuning_point_len = tuning_point_len;
						best_start_point = start_point;
					}

					if (TURNING_SUCCESS_FIRST_POINT == start_point) {
						tmp_value = tuning_point_len;
					}
				}

				start_point = -1;

				tuning_point_len = 0;

			} else {
				if (-1 == start_point) {
					start_point = i;
				}

				tuning_point_len++;

				tuning_result_index[i] = 1;

			}
		}
	}

	printk(KERN_INFO "tuning_point_len is %d,best_tuning_point_len is %d,start_point is %d, best_start_point is %d \n",
		tuning_point_len, best_tuning_point_len, start_point, best_start_point);

	if (tuning_point_len > best_tuning_point_len) {
		best_tuning_point_len = tuning_point_len;
		best_start_point = start_point;
	}

	/*如果头尾都turning成功，则合并 */
	if (tuning_result_index[MMC_MAX_TUNING_VALUE] & tuning_result_index[0]) {
		if ((tuning_point_len + tmp_value) > best_tuning_point_len) {
			best_tuning_point_len = tuning_point_len + tmp_value;
			best_start_point = start_point;
		}
	}

	if ((best_tuning_point_len > 1) && (0 == best_tuning_point_len % 2)) {	/*偶数 */

		best_tuning_sample_point = best_start_point + best_tuning_point_len / 2 - 1;

		if (best_tuning_sample_point > MMC_MAX_TUNING_VALUE) {
			best_tuning_sample_point = best_tuning_sample_point - MMC_MAX_TUNING_VALUE - 1;
		}

		/*步骤 10   如果N为偶数，则选取N/2的相位点，再通过配置UHS_REG_EXT[21]使能DELAY_CELL */
		/*mci_writel(host,UHS_REG_EXT,mci_readl(host,UHS_REG_EXT)|(0x1<<MMC_UHS_REG_EXT_MIN));*/
		use_delay_cell = 1;

		sd_sdr104_tuning_point = best_tuning_sample_point;
	}

	if ((best_tuning_point_len > 1) && (1 == best_tuning_point_len % 2)) {	/*奇数 */
		best_tuning_sample_point = best_start_point + best_tuning_point_len / 2;

		if (best_tuning_sample_point > MMC_MAX_TUNING_VALUE) {
			best_tuning_sample_point = best_tuning_sample_point - MMC_MAX_TUNING_VALUE - 1;
		}

		sd_sdr104_tuning_point = best_tuning_sample_point;
	}

	/*tuning failed or noneed turning */
	if (best_tuning_point_len < 2) {
		if (!is_tuning_all_phased) {
			printk(KERN_ERR "dw_mci_hi6xxx_sd_tuning: ####resume#### \n");

			best_tuning_sample_point = host->saved_tuning_phase;
		} else {
			best_tuning_sample_point = -1;
		}
	}

	if (best_tuning_sample_point >= 0) {
		best_tuning_point_len = best_tuning_point_len >> 0x1;
tryagain:
		writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mmc1_hf_START,
			SOC_PERI_SCTRL_SC_PERIPH_CLKDIS12_ADDR(priv->peri_sysctrl));

		mci_writel(host, UHS_REG_EXT, (0x1 << MMC_UHS_REG_EXT_22BIT)
			| (use_delay_cell << MMC_UHS_REG_EXT_MIN) | (best_tuning_sample_point << MMC_UHS_REG_EXT_MACRO));

		writel(0x1 << SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mmc1_hf_START,
			SOC_PERI_SCTRL_SC_PERIPH_CLKEN12_ADDR(priv->peri_sysctrl));

		printk(KERN_INFO "the best tuning point is %d sd sdr104 tuning success \n", best_tuning_sample_point);

		/* check again */
		cmd.error = 0;
		data.error = 0;

		mmc_wait_for_req(mmc, &mrq);

		if (cmd.error != 0 || data.error != 0 || memcmp(data_buf, tuning_block_64, sizeof(tuning_block_64)) != 0) {
			/*稳定性提升修改:如果最佳tuning点失败，使用就近点继续tuning，确保找到可以的点 */
			if (best_tuning_point_len > 0) {
				use_delay_cell = 0;

				best_tuning_point_len--;
				if (best_tuning_sample_point == 0) {
					best_tuning_sample_point = 15;
					goto tryagain;
				}

				best_tuning_sample_point--;

				goto tryagain;
			}

			if (!is_tuning_all_phased) {
				is_tuning_all_phased = true;
				goto retry;
			} else {
				if (tuning_times < 3) {
					tuning_point_len = 0;

					best_start_point = -1;

					best_tuning_point_len = 0;

					for (i = 0; i <= MMC_MAX_TUNING_VALUE; i++) {
						tuning_result_index[i] = 0;
					}

					tmp_value = 0;

					start_point = -1;

					is_tuning_all_phased = true;

					goto retry;
				}
				udelay(450);

				printk(KERN_INFO "sd sdr104 tuning failed \n");

				mmc->caps &= ~MMC_CAP_UHS_SDR104;

				/*SOC1002:bypass en，低频 */
				writel(readl(SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl))
					| (0x1 << SOC_PERI_SCTRL_SC_PERIPH_CTRL2_mmc_clk_phase_bypass_en_mmc1_START),
						SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl));

				host->tuning_result_flag = EMMC_TUNING_FAIL;

				ret = -1;
			}
		} else {
			host->saved_tuning_phase = best_tuning_sample_point;
			printk(KERN_ERR "sd sdr104 tuning OK,the tuning point is %d\n", host->saved_tuning_phase);
			host->tuning_result_flag = EMMC_TUNING_SUCCESS;
		}
	} else {
		printk(KERN_ERR "$sd sdr104 tuning failed \n");
		/* when tuning fail give up HS200 choose DDR50 */

		mmc->caps &= ~MMC_CAP_UHS_SDR104;

		/*SOC1002:bypass en，低频 */
		writel(readl(SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl))
			| (0x4), SOC_PERI_SCTRL_SC_PERIPH_CTRL2_ADDR(priv->peri_sysctrl));

		host->tuning_result_flag = EMMC_TUNING_FAIL;

		ret = -1;
	}

	host->flags &= ~DWMMC_IN_TUNING;

	host->flags |= DWMMC_TUNING_DONE;

	host->tuning_done = true;

	kfree(data_buf);
	pm_runtime_mark_last_busy(mmc_dev(mmc));
	pm_runtime_put_autosuspend(mmc_dev(mmc));
	return ret;
}

/*
SOC1005
turing 的策略:
一共15个turning点
  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
  1 1 1 0 0 0 1 1 1 1 1   0  0  1  1

如上图，如果turning成功，那么对应bit设置为1，turning完毕后，选择连续为1最多的频点
取中间频点作为最优频点设置
*/
int dw_mci_hi6xxx_tuning(struct dw_mci_slot *slot, u32 opcode, struct dw_mci_tuning_data *tuning_data)
{
	struct dw_mci *host = slot->host;
	struct dw_mci_hs_priv_data *priv = host->priv;
	int ret = 0;

	if (priv->id == MMC_EMMC) {
		if (EMMC_CS_BOARD == priv->cs) {
			ret = dw_mci_hi6xxx_mmc_cs_tuning(slot);
		} else {
			ret = dw_mci_hi6xxx_mmc_es_tuning(slot);
		}
	}

	if (priv->id == MMC_SD) {
		ret = dw_mci_hi6xxx_sd_tuning(slot);
	}

	return ret;

}

static const struct dw_mci_drv_data hi6xxx_drv_data = {
	.caps = hi6xxx_dwmmc_caps,
	.init = dw_mci_hi6xxx_priv_init,
	.set_ios = dw_mci_hi6xxx_set_ios,
	.setup_clock = dw_mci_hi6xxx_setup_clock,
	.prepare_command = dw_mci_hi6xxx_prepare_command,
	.parse_dt = dw_mci_hi6xxx_parse_dt,
	.cd_detect_init = dw_mci_hi6xxx_cd_detect_init,
	.tuning_find_condition = dw_mci_hi6xxx_tuning_find_condition,
	.tuning_set_current_state = dw_mci_hi6xxx_tuning_set_current_state,
	.slowdown_clk = dw_mci_hi6xxx_slowdown_clk,
	.execute_tuning = dw_mci_hi6xxx_tuning,
	.start_signal_voltage_switch = dw_mci_hi6xxx_start_signal_voltage_switch,
};

static const struct of_device_id dw_mci_hi6xxx_match[] = {
	{.compatible = "hisilicon,hi3620-dw-mshc",
	 .data = &hi6xxx_drv_data,},
	{.compatible = "hisilicon,hi3630-dw-mshc",
	 .data = &hi6xxx_drv_data,},
	{},
};

MODULE_DEVICE_TABLE(of, dw_mci_hi6xxx_match);

static int dw_mci_hi6xxx_probe(struct platform_device *pdev)
{
	const struct dw_mci_drv_data *drv_data = NULL;
	const struct of_device_id *match;
	int err;

	match = of_match_node(dw_mci_hi6xxx_match, pdev->dev.of_node);

	if (match)
		drv_data = match->data;

	err = dw_mci_pltfm_register(pdev, drv_data);
	if (err)
		return err;

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);
	pm_runtime_set_autosuspend_delay(&pdev->dev, 50);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_suspend_ignore_children(&pdev->dev, 1);

#if defined (CONFIG_HUAWEI_DSM)
	if (!dclient)
		dclient = dsm_register_client(&dsm_dw_mmc);
#endif

	return 0;
}

#ifdef CONFIG_PM_SLEEP
static int dw_mci_hi6xxx_suspend(struct device *dev)
{
	int ret;
	struct dw_mci *host = dev_get_drvdata(dev);
	struct dw_mci_hs_priv_data *priv = host->priv;
	dev_info(host->dev, " %s ++ \n", __func__);

	pm_runtime_get_sync(dev);

	ret = dw_mci_suspend(host);
	if (ret)
		return ret;
	priv->old_timing = -1;
	priv->old_power_mode = MMC_POWER_OFF;
	if (!IS_ERR(host->biu_clk))
		clk_disable_unprepare(host->biu_clk);

	if (!IS_ERR(host->ciu_clk))
		clk_disable_unprepare(host->ciu_clk);

	dw_mci_hi6xxx_set_controller(host, 1);

	host->current_speed = 0;

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	dev_info(host->dev, " %s -- \n", __func__);
	return 0;
}

static int dw_mci_hi6xxx_resume(struct device *dev)
{
	int ret;
	struct dw_mci *host = dev_get_drvdata(dev);
	struct dw_mci_slot *slot = host->slot[0];
	struct dw_mci_hs_priv_data *priv = host->priv;
	int id = priv->id;

	dev_info(host->dev, " %s ++ \n", __func__);

	pm_runtime_get_sync(dev);
	dw_mci_hi6xxx_set_controller(host, 0);

	if (!IS_ERR(host->biu_clk)) {
		if (clk_prepare_enable(host->biu_clk))
			dev_err(host->dev, "biu_clk clk_prepare_enable failed\n");
	}

	if (!IS_ERR(host->ciu_clk)) {
		if (clk_prepare_enable(host->ciu_clk))
			dev_err(host->dev, "ciu_clk clk_prepare_enable failed\n");
	}

	host->flags &= ~DWMMC_IN_TUNING;
	host->flags &= ~DWMMC_TUNING_DONE;

	mci_writel(host, CARDTHRCTL, 0x02000001);

	/*emmc freq from 150M to 25M,wake the emmc */
	if ((MMC_EMMC == id) && (host->tuning_result_flag != EMMC_TUNING_FAIL)) {
		slot->mmc->ios.timing = MMC_TIMING_LEGACY;
		slot->mmc->ios.clock = MMC_CCLK_MAX_25M;
	}

	ret = dw_mci_resume(host);
	if (ret)
		return ret;

	/*emmc freq from 25M to 150M,resume to HS200 */
	if ((MMC_EMMC == id) && (host->tuning_result_flag != EMMC_TUNING_FAIL)) {
		slot->mmc->ios.timing = MMC_TIMING_MMC_HS200;
		if (EMMC_CS_BOARD == priv->cs) {
			slot->mmc->ios.clock = MMC_CCLK_MAX_180M;
		} else {
			slot->mmc->ios.clock = MMC_CCLK_MAX_150M;
		}

		dw_mci_hi6xxx_set_ios(host, &slot->mmc->ios);
	}

	/*SOC1005:from V9 turning process */
	if (host->tuning_needed && !(host->flags & DWMMC_IN_TUNING) && !host->tuning_done && (host->tuning_result_flag != EMMC_TUNING_FAIL)) {
		mmc_claim_host(slot->mmc);
		dw_mci_hi6xxx_tuning(slot, 0, 0);
		mmc_release_host(slot->mmc);
	}

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	dev_info(host->dev, " %s -- \n", __func__);
	return 0;
}
#endif

#ifdef CONFIG_PM_RUNTIME
static int dw_mci_hi6xxx_runtime_suspend(struct device *dev)
{
	struct dw_mci *host = dev_get_drvdata(dev);
	dev_vdbg(host->dev, " %s ++ \n", __func__);

	if (dw_mci_hi6xxx_card_busy(host))
		return 0;

	if (!IS_ERR(host->biu_clk))
		clk_disable_unprepare(host->biu_clk);

	dev_vdbg(host->dev, " %s -- \n", __func__);

	return 0;
}

static int dw_mci_hi6xxx_runtime_resume(struct device *dev)
{
	struct dw_mci *host = dev_get_drvdata(dev);
	dev_vdbg(host->dev, " %s ++ \n", __func__);

	if (!IS_ERR(host->biu_clk)) {
		if (clk_prepare_enable(host->biu_clk))
			dev_err(host->dev, "biu_clk clk_prepare_enable failed\n");
	}

	dev_vdbg(host->dev, " %s -- \n", __func__);

	return 0;
}
#endif

static const struct dev_pm_ops dw_mci_hi6xxx_pmops = {
	SET_SYSTEM_SLEEP_PM_OPS(dw_mci_hi6xxx_suspend, dw_mci_hi6xxx_resume)
	SET_RUNTIME_PM_OPS(dw_mci_hi6xxx_runtime_suspend,
						   dw_mci_hi6xxx_runtime_resume, NULL)
};

static struct platform_driver dw_mci_hi6xxx_pltfm_driver = {
	.probe = dw_mci_hi6xxx_probe,
	.remove = dw_mci_pltfm_remove,
	.driver = {
			   .name = DRIVER_NAME,
			   .of_match_table = of_match_ptr(dw_mci_hi6xxx_match),
			   .pm = &dw_mci_hi6xxx_pmops,
			   },
};

module_platform_driver(dw_mci_hi6xxx_pltfm_driver);

MODULE_DESCRIPTION("Hisilicon Specific DW-MSHC Driver Extension");
MODULE_LICENSE("GPL v2");
