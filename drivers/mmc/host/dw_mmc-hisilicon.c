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
#include <linux/mmc/host.h>
#include <linux/mmc/dw_mmc.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/pinctrl/consumer.h>
#include <linux/of_address.h>
#include <linux/pm_runtime.h>
#include <linux/clk-private.h>

#include "dw_mmc.h"
#include "dw_mmc-pltfm.h"

#include "soc_peri_sctrl_interface.h"
#include "soc_baseaddr_interface.h"

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

#define DRIVER_NAME "dwmmc_hs"
static void __iomem *pericrg_base = NULL;

#define PERI_CRG_RSTEN4             (0x90)
#define PERI_CRG_RSTDIS4            (0x94)
#define PERI_CRG_RSTSTAT4           (0x98)

#define BIT_RST_MMC2         (1<<19)
#define BIT_RST_SD           (1<<18)
#define BIT_RST_EMMC         (1<<17)

#define GPIO_CLK_ENABLE			(0x1 << 16)

#define UHS_REG_EXT_SAMPLE_PHASE(x)	(((x) & 0x1f) << 16)
#define UHS_REG_EXT_SAMPLE_DLY(x)	(((x) & 0x1f) << 23)
#define SDMMC_UHS_REG_EXT_VALUE(x, y)	(UHS_REG_EXT_SAMPLE_PHASE(x) |	\
					UHS_REG_EXT_SAMPLE_DLY(y))

#define GPIO_CLK_DIV(x)	(((x) & 0xf) << 8)
#define GPIO_USE_SAMPLE_DLY(x)	(((x) & 0x1) << 13)
#define GPIO_DRIVE_SEL(x)	(((x) & 0x1) << 12)
#define SDMMC_GPIO_VALUE(x, y, z)	(GPIO_CLK_DIV(x) |	\
					GPIO_USE_SAMPLE_DLY(y) | GPIO_DRIVE_SEL(z))

static struct dw_mci_hisi_compatible {
	char *compatible;
	enum dw_mci_hisilicon_type type;
} hs_compat[] = {
	{
		.compatible = "hisilicon,hi3620-dw-mshc",
		.type = DW_MCI_TYPE_HI3620,
	}, {
		.compatible = "hisilicon,hi3630-dw-mshc",
		.type = DW_MCI_TYPE_HI3630,
	},
};

static int hs_timing_config[][9][TUNING_INIT_CONFIG_NUM] = {
/* bus_clk, div, drv_sel, sam_dly, sam_phase_max, sam_phase_min, input_clk */
	{
		{360000000, 9, 1, 0, 0, 0, 36000000},		/* 0: LEGACY 100k */
	 	{360000000, 6, 1, 0, 1, 1, 52000000},		/* 1: MMC_HS */
	 	{0},					/* 2: SD_HS */
	 	{0},					/* 3: SDR12 */
	 	{0},					/* 4: SDR25 */
	 	{0},					/* 5: SDR50 */
	 	{0},					/* 6: SDR104 */
	 	{720000000, 6, 0, 4, 6, 0, 102000000},	/* 7: DDR50 */
	 	{1440000000, 7, 0, 3, 15, 0, 180000000},	/* 8: HS200 */
	 }, {
	 	{360000000, 9, 1, 0, 0, 0, 36000000},		/* 0: LEGACY 400k */
		{0},					/* 1: MMC_HS */
		{360000000, 6, 1, 0, 1, 1, 50000000},		/* 2: SD_HS */
		{180000000, 6, 1, 2, 13, 13, 25000000},	/* 3: SDR12 */
		{360000000, 6, 1, 0, 1, 1, 50000000},		/* 4: SDR25 */
		{720000000, 6, 0, 3, 9, 0, 100000000},	/* 5: SDR50 */
		{1440000000, 7, 0, 5, 15, 0, 180000000},	/* 6: SDR104 */
		{0},					/* 7: DDR50 */
		{0},					/* 8: HS200 */
	}, {
		{360000000, 9, 1, 0, 0, 0, 36000000},		/* 0: LEGACY 400k */
		{0},					/* 1: MMC_HS */
		{360000000, 6, 1, 0, 4, 4, 50000000},		/* 2: SD_HS */
		{180000000, 6, 1, 2, 0, 0, 25000000},		/* 3: SDR12 */
		{360000000, 6, 1, 0, 4, 4, 50000000},		/* 4: SDR25 */
		{720000000, 6, 0, 2, 9, 0, 100000000},	/* 5: SDR50 */
		{1440000000, 7, 0, 4, 15, 0, 180000000},	/* 6: SDR104 */
		{720000000, 15, 0, 5, 11, 1, 45000000},	/* 7: DDR50 */
		{0},					/* 8: HS200 */
	}
};

/*当read、massread操作时发包使用*/
struct semaphore sem_to_rfile_sync_req;

extern int gpio_direction_output(unsigned gpio, int value);

static void dw_mci_hs_set_timing(struct dw_mci *host, int id, int timing, int sam_phase, int clk_div)
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

static void dw_mci_hs_set_parent(struct dw_mci *host, int timing)
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

static void mshci_clock_onoff(struct dw_mci *host, bool val)
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

void mshci_set_clock(struct dw_mci *host, unsigned int clock)
{
	int div;
	u32 loop_count, reg;

	/* before changing clock. clock needs to be off */
	mshci_clock_onoff(host, CLK_DISABLE);

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

	mshci_clock_onoff(host, CLK_ENABLE);

}

/*SOC1008*/
static void dw_mci_hs_set_ios(struct dw_mci *host, struct mmc_ios *ios)
{
	struct dw_mci_hs_priv_data *priv = host->priv;
	int id = priv->id;
	int ret;

#ifdef CONFIG_ARM64
	dw_board_type = 1;
#endif

	if (priv->old_power_mode != ios->power_mode) {
		switch (ios->power_mode) {
		case MMC_POWER_OFF:
			dev_info(host->dev, "set io to lowpower\n");
			/* set pin to idle */
			/*继承V9，emmc常供电 */

			if (MMC_SD == id) {
				if ((host->pinctrl) && (host->pins_idle)) {
					ret = pinctrl_select_state(host->pinctrl, host->pins_idle);
					if (ret)
						dev_warn(host->dev, "could not set idle pins\n");
				}
				if (host->vqmmc)
					regulator_disable(host->vqmmc);
				if ((host->vmmc) && (priv->sd_slot_ldo10_status == SD_SLOT_VOL_CLOSE))
					regulator_disable(host->vmmc);
			}

			break;

		case MMC_POWER_UP:
			dev_info(host->dev, "set io to normal\n");

/*继承V9，emmc常供电*/
			/*
			   ldo5不需要配置，硬件默认上电；
			   ldo19配置为3V；
			 */
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

			break;
		case MMC_POWER_ON:
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
				if (1 == priv->id) {
					host->bus_hz = MMC_CCLK_MAX_24M;
				} else {
					host->bus_hz = MMC_CCLK_MAX_25M;
				}
				break;
			case MMC_TIMING_MMC_HS:
			case MMC_TIMING_UHS_SDR25:
				host->bus_hz = MMC_CCLK_MAX_50M;
				break;
			case MMC_TIMING_UHS_DDR50:
				/*SOC1000:在DDR50（8bit）模式时MMC内部固定为2:1分频 ? */
				if (0 == priv->id) {
					host->bus_hz = MMC_CCLK_MAX_100M;
				} else {
					host->bus_hz = MMC_CCLK_MAX_50M;
				}
				break;
			case MMC_TIMING_MMC_HS200:

				printk(KERN_ERR "dw_mci_hs_set_ios:$$$$$$$$ WE GOT HS200 \n");

				host->tuning_needed = true;

				host->bus_hz = MMC_CCLK_MAX_150M;
				break;
			case MMC_TIMING_UHS_SDR50:
				if (DWMMC_SD_ID == priv->id) {
					host->bus_hz = MMC_CCLK_MAX_80M;
				} else {
					host->bus_hz = MMC_CCLK_MAX_100M;
				}
				break;
			default:
				printk(KERN_ERR "error the timing we can not support \n");

			}

		}

		if (BOARDTYPE_SFT == dw_board_type) {
			/*sft 单板最高支持频率为30MHz */
			host->bus_hz = 30000000;
		} else {
			;
		}

		clk_set_rate(host->biu_clk, host->bus_hz);

		mshci_set_clock(host, ios->clock);

		priv->old_timing = ios->timing;
	}

}

static void dw_mci_hs_prepare_command(struct dw_mci *host, u32 *cmdr)
{
	*cmdr |= SDMMC_CMD_USE_HOLD_REG;
}

static void dw_mci_hs_tuning_clear_flags(struct dw_mci *host)
{
	host->tuning_sample_flag = 0;
}

static void dw_mci_hs_tuning_set_flags(struct dw_mci *host, int sample, int ok)
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
static int dw_mci_hs_tuning_find_condition(struct dw_mci *host, int timing)
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
		dw_mci_hs_set_timing(host, id, timing, host->tuning_init_sample, host->current_div);
		dev_info(host->dev, "no need tuning: timing is %d, tuning sample = %d", timing, host->tuning_init_sample);
		return 0;
	}

	if (-1 == host->tuning_current_sample) {

		dw_mci_hs_tuning_clear_flags(host);

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
			for (i = (sample_min + sample_max - mask_lenth + 1) / 2, j = 1; (i <= sample_max - mask_lenth + 1) && (i >= sample_min); i = ((sample_min + sample_max - mask_lenth + 1) / 2) + ((j % 2) ? -1 : 1) * (j / 2)) {
				if ((host->tuning_sample_flag & (mask << i)) == (mask << i)) {
					host->tuning_init_sample = i + mask_lenth / 2;
					break;
				}

				j++;
			}

			if (host->tuning_init_sample != -1) {
				if ((host->hw_mmc_id == DWMMC_SD_ID) && (mask_lenth < 3)) {
					dev_info(host->dev, "sd card tuning need slow down clk, timing is %d, tuning_flag = 0x%x \n", timing, host->tuning_sample_flag);
					return -1;
				} else {
					dev_info(host->dev, "tuning OK: timing is %d, tuning sample = %d, tuning_flag = 0x%x", timing, host->tuning_init_sample, host->tuning_sample_flag);
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

		dw_mci_hs_set_timing(host, id, timing, host->tuning_init_sample, host->current_div);
		return ret;
	} else {
		host->tuning_current_sample++;
		dw_mci_hs_set_timing(host, id, timing, host->tuning_current_sample, host->current_div);
		return 1;
	}

	return 0;
}

static void dw_mci_hs_tuning_set_current_state(struct dw_mci *host, int ok)
{
	dw_mci_hs_tuning_set_flags(host, host->tuning_current_sample, ok);
}

static int dw_mci_hs_slowdown_clk(struct dw_mci *host, int timing)
{
	struct dw_mci_hs_priv_data *priv = host->priv;
	int id = priv->id;

	host->current_div++;
	dev_info(host->dev, "begin slowdown clk, current_div=%d\n", host->current_div);
	if (host->current_div > 15) {
		host->current_div = 15;
		return -1;
	} else
		dw_mci_hs_set_timing(host, id, timing, host->tuning_init_sample, host->current_div);

	return 0;
}

static int dw_mci_hs_set_controller(struct dw_mci *host, bool set)
{
	struct dw_mci_hs_priv_data *priv = host->priv;
	int id = priv->id;

	if (pericrg_base == NULL) {
		dev_err(host->dev, "pericrg_base is null, can't reset mmc! \n");
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

#ifdef CONFIG_HI110X_WIFI_ENABLE
static struct dw_mci *hi_sdio_host = NULL;
void hi110x_sdio_detectcard_to_core(int enable)
{
	if (hi_sdio_host == NULL) {
		printk(KERN_ERR "hi_sdio detect, host is null,can not used to detect sdio\n");
		return;
	}

	dw_mci_set_cd(hi_sdio_host);
	printk("Hisi wlan detect mmc control:%d,[%s]\n", hi_sdio_host->hw_mmc_id, enable ? "start sdio enum" : "deinit sdio enum");
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

static int dw_mci_hs_priv_init(struct dw_mci *host)
{
	struct dw_mci_hs_priv_data *priv;
	int i, sw[2], err;
	void __iomem *sc_periph_addr = 0;

	priv = devm_kzalloc(host->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		dev_err(host->dev, "mem alloc failed for private data\n");
		return -ENOMEM;
	}

	priv->id = of_alias_get_id(host->dev->of_node, "mshc");

	if (priv->id == MMC_EMMC) {
		sema_init(&sem_to_rfile_sync_req, 0);

		priv->peri_sysctrl = (void __iomem *)HISI_VA_ADDRESS(SOC_PERI_SCTRL_BASE_ADDR);
		if (!priv->peri_sysctrl) {
			printk(KERN_ERR "dw_mci_hs_priv_init :peri_sysctrl err  \n");
			return -1;
		}

	}

	if (priv->id == MMC_SD) {
		if (of_property_read_u32_array(host->dev->of_node, "sw_gpio", &sw[0], 2)) {
			printk("[%s] %s node doesn't have sw_gpio property!\n", __func__, host->dev->of_node->name);
		} else {

			priv->gpio_sw = sw[0];
			priv->sw_value = sw[1];

			err = gpio_request_one(priv->gpio_sw, 0, "sw_gpio");
			if (err) {
				printk(KERN_ERR "request gpio fail!\n");
				return -1;
			}
			/*控制I/O口电平 1V8 or 3V3 */
			gpio_direction_output(priv->gpio_sw, priv->sw_value);
		}
		/*解复位 */
		sc_periph_addr = (void __iomem *)HISI_VA_ADDRESS(SOC_PERI_SCTRL_BASE_ADDR);
		if (!sc_periph_addr) {
			printk(KERN_ERR "dw_mci_hs_priv_init :sc_periph_addr err  \n");
			return -1;
		}

		writel(readl(SOC_PERI_SCTRL_SC_PERIPH_RSTDIS0_ADDR(sc_periph_addr)) | 0x6,
					SOC_PERI_SCTRL_SC_PERIPH_RSTDIS0_ADDR(sc_periph_addr));	/* for sdcard, sdio*/

		priv->ao_sysctrl = (void __iomem *)HISI_VA_ADDRESS(SOC_AO_SCTRL_BASE_ADDR);
		if (!priv->ao_sysctrl) {
			printk(KERN_ERR "dw_mci_hs_priv_init :ao_sysctrl err  \n");
			return -1;
		}

		mci_writel(host, CARDTHRCTL, 0x02000001);

	}

	if (priv->id == MMC_SDIO) {
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

	for (i = 0; i < ARRAY_SIZE(hs_compat); i++) {
		if (of_device_is_compatible(host->dev->of_node, hs_compat[i].compatible))
			priv->type = hs_compat[i].type;
	}

	return 0;
}

static int dw_mci_hs_setup_clock(struct dw_mci *host)
{
	struct dw_mci_hs_priv_data *priv = host->priv;
	int timing = MMC_TIMING_LEGACY;
	int id = priv->id;
	int ret;

	dw_mci_hs_set_parent(host, timing);

	ret = clk_set_rate(host->ciu_clk, hs_timing_config[id][timing][0]);
	if (ret)
		dev_err(host->dev, "clk_set_rate failed\n");

	dw_mci_hs_set_controller(host, 0);

	host->tuning_current_sample = -1;
	host->sd_reinit = 0;
	host->current_div = hs_timing_config[id][timing][1];

	host->tuning_init_sample = (hs_timing_config[id][timing][4] + hs_timing_config[id][timing][5]) / 2;

	dw_mci_hs_set_timing(host, id, timing, host->tuning_init_sample, host->current_div);

	if (priv->priv_bus_hz == 0)
		host->bus_hz = hs_timing_config[id][timing][6];
	else
		host->bus_hz = priv->priv_bus_hz;

	priv->old_timing = timing;

	return 0;
}

static int dw_mci_hs_parse_dt(struct dw_mci *host)
{
	struct dw_mci_hs_priv_data *priv = host->priv;
	struct device_node *np = host->dev->of_node;
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
	return 0;
}

static irqreturn_t dw_mci_hs_card_detect(int irq, void *data)
{
	struct dw_mci *host = (struct dw_mci *)data;
	host->sd_reinit = 0;
	host->flags &= ~DWMMC_IN_TUNING;
	host->flags &= ~DWMMC_TUNING_DONE;
	/*dw_mci_work_routine_card */
	queue_work(host->card_workqueue, &host->card_work);
	return IRQ_HANDLED;
};

static int dw_mci_hs_get_cd(struct dw_mci *host, u32 slot_id)
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

static int dw_mci_hs_cd_detect_init(struct dw_mci *host)
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
			host->pdata->get_cd = dw_mci_hs_get_cd;
			err = devm_request_irq(host->dev, gpio_to_irq(gpio),
								dw_mci_hs_card_detect, IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING | IRQF_NO_SUSPEND,
								DRIVER_NAME, host);
			if (err)
				dev_warn(mmc_dev(host->dev), "request gpio irq error\n");
		}

	} else {
		dev_info(host->dev, "cd gpio not available");
	}

	return 0;
}

#if 0
static int hs_dwmmc_card_busy(struct dw_mci *host)
{
	if ((mci_readl(host, STATUS) & SDMMC_DATA_BUSY)
		|| host->cmd || host->data || host->mrq || (host->state != STATE_IDLE)) {
		dev_vdbg(host->dev, " card is busy!");
		return 1;
	}

	return 0;
}
#endif

/* Common capabilities of hi3630 SoC */
static unsigned long hs_dwmmc_caps[3] = {
	/* emmc */
	MMC_CAP_NONREMOVABLE | MMC_CAP_8_BIT_DATA | MMC_CAP_MMC_HIGHSPEED | MMC_CAP_ERASE | MMC_CAP_CMD23,
	/* sd */
	MMC_CAP_DRIVER_TYPE_A | MMC_CAP_4_BIT_DATA | MMC_CAP_SD_HIGHSPEED
		| MMC_CAP_MMC_HIGHSPEED | MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 | MMC_CAP_UHS_SDR50,
	/* sdio */
	MMC_CAP_4_BIT_DATA | MMC_CAP_SDIO_IRQ | MMC_CAP_SD_HIGHSPEED | MMC_CAP_NONREMOVABLE,
};

static const struct dw_mci_drv_data hs_drv_data = {
	.caps = hs_dwmmc_caps,
	.init = dw_mci_hs_priv_init,
	.set_ios = dw_mci_hs_set_ios,
	.setup_clock = dw_mci_hs_setup_clock,
	.prepare_command = dw_mci_hs_prepare_command,
	.parse_dt = dw_mci_hs_parse_dt,
	.cd_detect_init = dw_mci_hs_cd_detect_init,
	.tuning_find_condition = dw_mci_hs_tuning_find_condition,
	.tuning_set_current_state = dw_mci_hs_tuning_set_current_state,
	.slowdown_clk = dw_mci_hs_slowdown_clk,
};

static const struct of_device_id dw_mci_hs_match[] = {
	{.compatible = "hisilicon,hi3620-dw-mshc",
	 .data = &hs_drv_data,},
	{.compatible = "hisilicon,hi3630-dw-mshc",
	 .data = &hs_drv_data,},
	{},
};

MODULE_DEVICE_TABLE(of, dw_mci_hs_match);

static int dw_mci_hs_probe(struct platform_device *pdev)
{
	const struct dw_mci_drv_data *drv_data = NULL;
	const struct of_device_id *match;
	int err;

	match = of_match_node(dw_mci_hs_match, pdev->dev.of_node);

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
static int dw_mci_hs_suspend(struct device *dev)
{
	int ret;
	struct dw_mci *host = dev_get_drvdata(dev);
	struct dw_mci_hs_priv_data *priv = host->priv;
	dev_info(host->dev, " %s ++ \n", __func__);

	pm_runtime_get_sync(dev);

#if 0
	if (priv->gpio_cd) {
		disable_irq_nosync(gpio_to_irq(priv->gpio_cd));
		dev_info(host->dev, " disable gpio detect \n");
	}
#endif

	ret = dw_mci_suspend(host);
	if (ret)
		return ret;
	priv->old_timing = -1;
	priv->old_power_mode = MMC_POWER_OFF;
	if (!IS_ERR(host->biu_clk))
		clk_disable_unprepare(host->biu_clk);

	if (!IS_ERR(host->ciu_clk))
		clk_disable_unprepare(host->ciu_clk);

	dw_mci_hs_set_controller(host, 1);

	host->current_speed = 0;

	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	dev_info(host->dev, " %s -- \n", __func__);
	return 0;
}

static int dw_mci_hs_resume(struct device *dev)
{
	int ret;
	struct dw_mci *host = dev_get_drvdata(dev);
	struct mmc_host *mmc = host->slot[0]->mmc;

#if 0
	struct dw_mci_hs_priv_data *priv = host->priv;
#endif

	dev_info(host->dev, " %s ++ \n", __func__);

	pm_runtime_get_sync(dev);
	dw_mci_hs_set_controller(host, 0);

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

	ret = dw_mci_resume(host);
	if (ret)
		return ret;

	/*SOC1005:from V9 turning process */
	if (host->tuning_needed && !(host->flags & DWMMC_IN_TUNING) && !host->tuning_done) {
		mmc_claim_host(mmc);
		mshci_execute_tuning(mmc);
		mmc_release_host(mmc);
	}
#if 0
	if (priv->gpio_cd) {
		enable_irq(gpio_to_irq(priv->gpio_cd));
		dev_info(host->dev, " enable gpio detect \n");
	}
#endif
	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_autosuspend(dev);

	dev_info(host->dev, " %s -- \n", __func__);
	return 0;
}
#endif

#ifdef CONFIG_PM_RUNTIME
static int dw_mci_hs_runtime_suspend(struct device *dev)
{
#if 0
	struct dw_mci *host = dev_get_drvdata(dev);
	dev_vdbg(host->dev, " %s ++ \n", __func__);

	if (hs_dwmmc_card_busy(host))
		return 0;

	if (!IS_ERR(host->biu_clk))
		clk_disable_unprepare(host->biu_clk);

	if (!IS_ERR(host->ciu_clk))
		clk_disable_unprepare(host->ciu_clk);

	dev_vdbg(host->dev, " %s -- \n", __func__);
#endif
	return 0;
}

static int dw_mci_hs_runtime_resume(struct device *dev)
{
#if 0
	struct dw_mci *host = dev_get_drvdata(dev);
	dev_vdbg(host->dev, " %s ++ \n", __func__);

	if (!IS_ERR(host->biu_clk)) {
		if (clk_prepare_enable(host->biu_clk))
			dev_err(host->dev, "biu_clk clk_prepare_enable failed\n");
	}

	if (!IS_ERR(host->ciu_clk)) {
		if (clk_prepare_enable(host->ciu_clk))
			dev_err(host->dev, "ciu_clk clk_prepare_enable failed\n");
	}

	dev_vdbg(host->dev, " %s -- \n", __func__);
#endif

	return 0;
}
#endif

static const struct dev_pm_ops dw_mci_hs_pmops = {
	SET_SYSTEM_SLEEP_PM_OPS(dw_mci_hs_suspend, dw_mci_hs_resume)
	SET_RUNTIME_PM_OPS(dw_mci_hs_runtime_suspend,
						dw_mci_hs_runtime_resume, NULL)
};

static struct platform_driver dw_mci_hs_pltfm_driver = {
	.probe = dw_mci_hs_probe,
	.remove = dw_mci_pltfm_remove,
	.driver = {
			   .name = DRIVER_NAME,
			   .of_match_table = of_match_ptr(dw_mci_hs_match),
			   .pm = &dw_mci_hs_pmops,
			   },
};

module_platform_driver(dw_mci_hs_pltfm_driver);

MODULE_DESCRIPTION("Hisilicon Specific DW-MSHC Driver Extension");
MODULE_LICENSE("GPL v2");
