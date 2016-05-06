/*
 * hi3630_asp_common.c -- HI3630 ASP COMMON DRIVER
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define LOG_TAG "HI3630_COMMON"

#include <linux/slab.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/delay.h>
#include <linux/mfd/hi3630_asp_irq.h>
#include <linux/mutex.h>

#include "hi3630_asp_common.h"
#include "hi3630_log.h"

#define ASP_DELAY udelay(10)

struct hi3630_asp_cfg_data {
	struct hi3630_asp_irq *hi3630_asp_irq;
	struct mutex mutex;
	spinlock_t lock;

	/* ref_count of module */
	unsigned int sio_audio_module_count;
	unsigned int sio_voice_module_count;
	unsigned int sio_bt_module_count;
	unsigned int sio_modem_module_count;
	unsigned int srcup_module_count;
	unsigned int srcdown_module_count;
	unsigned int hdmi_module_count;
	unsigned int asp_h2x_module_count;

	unsigned int sio_audio_clk_count;
	unsigned int sio_voice_clk_count;
	unsigned int sio_bt_clk_count;
	unsigned int sio_modem_clk_count;

	bool sio_audio_master;
	bool sio_voice_master;
	bool sio_bt_master;
	bool sio_modem_master;

	unsigned int srcup_interrupt_ref;
	unsigned int srcdown_interrupt_ref;
	unsigned int hdmi_interrupt_ref;

	unsigned int siobclk_div_count;
};

static const struct of_device_id hi3630_asp_common_match[] = {
	{ .compatible = "hisilicon,hi3630-asp-common", },
	{},
};
MODULE_DEVICE_TABLE(of, hi3630_asp_common_match);

static struct hi3630_asp_cfg_data *g_hi3630_asp_cfg_data = NULL;

extern int  hi3630_asp_irq_read(struct hi3630_asp_irq *irq,
				unsigned int reg);
extern void hi3630_asp_irq_write(struct hi3630_asp_irq *irq,
				unsigned int reg, unsigned int value);
extern void hi3630_asp_irq_set_bit(struct hi3630_asp_irq *irq,
				unsigned int reg, unsigned int offset);
extern void hi3630_asp_irq_clr_bit(struct hi3630_asp_irq *irq,
				unsigned int reg, unsigned int offset);
#if 0
static int hi3630_cfg_read(int reg)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);
	return hi3630_asp_irq_read(g_hi3630_asp_cfg_data->hi3630_asp_irq, reg);
}
#endif

static void hi3630_cfg_write(int reg, unsigned int value)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);
	hi3630_asp_irq_write(g_hi3630_asp_cfg_data->hi3630_asp_irq, reg, value);
}

static void hi3630_cfg_set_bit(int reg, unsigned int offset)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);
	hi3630_asp_irq_set_bit(g_hi3630_asp_cfg_data->hi3630_asp_irq, reg, offset);
}

static void hi3630_cfg_clr_bit(int reg, unsigned int offset)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);
	hi3630_asp_irq_clr_bit(g_hi3630_asp_cfg_data->hi3630_asp_irq, reg, offset);
}

static void asp_h2x_module_enable(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->asp_h2x_module_count) {
			hi3630_cfg_write(HI3630_CFG_R_RST_CTRLDIS_REG, RST_ASP_H2X_BIT);
		}
		g_hi3630_asp_cfg_data->asp_h2x_module_count++;
	} else {
		g_hi3630_asp_cfg_data->asp_h2x_module_count--;
		if (0 == g_hi3630_asp_cfg_data->asp_h2x_module_count) {
			hi3630_cfg_write(HI3630_CFG_R_RST_CTRLEN_REG, RST_ASP_H2X_BIT);
		}
	}
}

static void siobclk_div_enable(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->siobclk_div_count) {
			hi3630_cfg_write(HI3630_CFG_R_CLK1_DIV_REG, FRAC_DIV_VALUE);
			hi3630_cfg_set_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_SIOBCLK_DIV_OFFSET);
			hi3630_cfg_write(HI3630_CFG_R_CLK_SEL_REG, ASP_CFG_SIOBCLK_360M_BIT);
		}
		g_hi3630_asp_cfg_data->siobclk_div_count++;
	} else {
		if (0 == g_hi3630_asp_cfg_data->siobclk_div_count) {
			loge("siobclk_div has already closed.\n");
			return;
		}

		g_hi3630_asp_cfg_data->siobclk_div_count--;

		if (0 == g_hi3630_asp_cfg_data->siobclk_div_count) {
			hi3630_cfg_clr_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_SIOBCLK_DIV_OFFSET);
		}
	}
}

void sio_audio_clk_enable(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->sio_audio_clk_count) {
			siobclk_div_enable(true);
			hi3630_cfg_write(HI3630_CFG_R_CLK3_DIV_REG, AUDIO_BCLK_DIV_VALUE);
			hi3630_cfg_write(HI3630_CFG_R_CLK5_DIV_REG, AUDIO_FS_DIV_VALUE);
			hi3630_cfg_set_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_SIO_AUDIO_BCLK_DIV_OFFSET);

		}
		g_hi3630_asp_cfg_data->sio_audio_clk_count++;
	} else {
		if (0 == g_hi3630_asp_cfg_data->sio_audio_clk_count) {
			loge("sio audio clk has already closed.\n");
			return;
		}

		g_hi3630_asp_cfg_data->sio_audio_clk_count--;

		if (0 == g_hi3630_asp_cfg_data->sio_audio_clk_count) {
			hi3630_cfg_clr_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_SIO_AUDIO_BCLK_DIV_OFFSET);
			siobclk_div_enable(false);
		}
	}
}

void sio_voice_clk_enable(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->sio_voice_clk_count) {
			siobclk_div_enable(true);
			hi3630_cfg_write(HI3630_CFG_R_CLK3_DIV_REG, VOICE_BCLK_DIV_VALUE);
			hi3630_cfg_write(HI3630_CFG_R_CLK5_DIV_REG, VOICE_FS_DIV_VALUE);
			hi3630_cfg_set_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_SIO_VOICE_BCLK_DIV_OFFSET);
		}
		g_hi3630_asp_cfg_data->sio_voice_clk_count++;
		loge("g_hi3630_asp_cfg_data->sio_voice_clk_count:%d.\n", g_hi3630_asp_cfg_data->sio_voice_clk_count);
	} else {
		if (0 == g_hi3630_asp_cfg_data->sio_voice_clk_count) {
			loge("sio voice clk has already closed.\n");
			return;
		}

		g_hi3630_asp_cfg_data->sio_voice_clk_count--;

		if (0 == g_hi3630_asp_cfg_data->sio_voice_clk_count) {
			hi3630_cfg_clr_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_SIO_VOICE_BCLK_DIV_OFFSET);
			siobclk_div_enable(false);
		}
	}
}

void sio_bt_clk_enable(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->sio_bt_clk_count) {
			siobclk_div_enable(true);
			hi3630_cfg_write(HI3630_CFG_R_CLK4_DIV_REG, BT_BCLK_DIV_VALUE);
			hi3630_cfg_write(HI3630_CFG_R_CLK6_DIV_REG, BT_FS_DIV_VALUE);
			hi3630_cfg_set_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_SIO_BT_BCLK_DIV_OFFSET);
		}
		g_hi3630_asp_cfg_data->sio_bt_clk_count++;
	} else {
		if (0 == g_hi3630_asp_cfg_data->sio_bt_clk_count) {
			loge("sio bt clk has already closed.\n");
			return;
		}

		g_hi3630_asp_cfg_data->sio_bt_clk_count--;

		if (0 == g_hi3630_asp_cfg_data->sio_bt_clk_count) {
			hi3630_cfg_clr_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_SIO_BT_BCLK_DIV_OFFSET);
			siobclk_div_enable(false);
		}
	}
}

void sio_modem_clk_enable(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->sio_modem_clk_count) {
			siobclk_div_enable(true);
			hi3630_cfg_write(HI3630_CFG_R_CLK4_DIV_REG, MODEM_BCLK_DIV_VALUE);
			hi3630_cfg_write(HI3630_CFG_R_CLK6_DIV_REG, MODEM_FS_DIV_VALUE);
			hi3630_cfg_set_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_SIO_MODEM_BCLK_DIV_OFFSET);
		}
		g_hi3630_asp_cfg_data->sio_modem_clk_count++;
	} else {
		if (0 == g_hi3630_asp_cfg_data->sio_modem_clk_count) {
			loge("sio modem clk has already closed.\n");
			return;
		}

		g_hi3630_asp_cfg_data->sio_modem_clk_count--;

		if (0 == g_hi3630_asp_cfg_data->sio_modem_clk_count) {
			hi3630_cfg_clr_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_SIO_MODEM_BCLK_DIV_OFFSET);
			siobclk_div_enable(false);
		}
	}
}

void set_sio_audio_master(bool is_master)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	mutex_lock(&g_hi3630_asp_cfg_data->mutex);
	g_hi3630_asp_cfg_data->sio_audio_master = is_master;
	mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
}

void set_sio_voice_master(bool is_master)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	mutex_lock(&g_hi3630_asp_cfg_data->mutex);
	g_hi3630_asp_cfg_data->sio_voice_master = is_master;
	mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
}

void set_sio_bt_master(bool is_master)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	mutex_lock(&g_hi3630_asp_cfg_data->mutex);
	g_hi3630_asp_cfg_data->sio_bt_master = is_master;
	mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
}

void set_sio_modem_master(bool is_master)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	mutex_lock(&g_hi3630_asp_cfg_data->mutex);
	g_hi3630_asp_cfg_data->sio_modem_master = is_master;
	mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
}

void sio_audio_module_enable(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	mutex_lock(&g_hi3630_asp_cfg_data->mutex);
	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->sio_audio_module_count) {
			/* disable reset & enable clk */
			hi3630_cfg_write(HI3630_CFG_R_RST_CTRLDIS_REG, RST_SIO_AUDIO_BIT);
			hi3630_cfg_write(HI3630_CFG_R_GATE_EN_REG, CLK_SIO_AUDIO_BIT);
			/* hifi_pcm_play */
			/* bit[0]:sio_audio
			 * 0: request send to srcup
			 * 1: request send to asp dmac
			 */
			hi3630_cfg_write(HI3630_CFG_R_DMAC_SEL_REG,0x00010001);

			if (g_hi3630_asp_cfg_data->sio_audio_master) {
				hi3630_cfg_write(HI3630_CFG_R_CLK_SEL_REG, ASP_CFG_SIO_AUDIO_MASTER_BIT);
				sio_audio_clk_enable(enable);
				hi3630_cfg_write(HI3630_CFG_R_GATE_EN_REG, CLK_SIO_AUDIO_BCLK_BIT);
			} else {
				hi3630_cfg_write(HI3630_CFG_R_CLK_SEL_REG, ASP_CFG_SIO_AUDIO_SLAVE_BIT);
			}

			ASP_DELAY;
		}

		g_hi3630_asp_cfg_data->sio_audio_module_count++;
	} else {
		if (0 == g_hi3630_asp_cfg_data->sio_audio_module_count) {
			loge("sio audio has already closed.\n");
			mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
			return;
		}

		g_hi3630_asp_cfg_data->sio_audio_module_count--;

		if (0 == g_hi3630_asp_cfg_data->sio_audio_module_count) {

			if (g_hi3630_asp_cfg_data->sio_audio_master) {
				hi3630_cfg_write(HI3630_CFG_R_GATE_DIS_REG, CLK_SIO_AUDIO_BCLK_BIT);
				sio_audio_clk_enable(enable);
			}

			hi3630_cfg_write(HI3630_CFG_R_GATE_DIS_REG, CLK_SIO_AUDIO_BIT);
			hi3630_cfg_write(HI3630_CFG_R_RST_CTRLEN_REG, RST_SIO_AUDIO_BIT);
		}
	}
	mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
}

void sio_voice_module_enable(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	mutex_lock(&g_hi3630_asp_cfg_data->mutex);
	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->sio_voice_module_count) {
			/* bit[1]:sio_voice
			 * 0: request send to srcdown
			 * 1: request send to asp dmac
			 */
			hi3630_cfg_write(HI3630_CFG_R_DMAC_SEL_REG,0x00020002);

			if (g_hi3630_asp_cfg_data->sio_voice_master) {
				hi3630_cfg_write(HI3630_CFG_R_CLK_SEL_REG, ASP_CFG_SIO_VOICE_MASTER_BIT);
				sio_voice_clk_enable(enable);
				hi3630_cfg_write(HI3630_CFG_R_GATE_EN_REG, CLK_SIO_VOICE_BCLK_BIT);
			}

			ASP_DELAY;
		}

		g_hi3630_asp_cfg_data->sio_voice_module_count++;
	} else {
		if (0 == g_hi3630_asp_cfg_data->sio_voice_module_count) {
			loge("sio voice has already closed.\n");
			mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
			return;
		}

		g_hi3630_asp_cfg_data->sio_voice_module_count--;

		if (0 == g_hi3630_asp_cfg_data->sio_voice_module_count) {

			if (g_hi3630_asp_cfg_data->sio_voice_master) {
				hi3630_cfg_write(HI3630_CFG_R_GATE_DIS_REG, CLK_SIO_VOICE_BCLK_BIT);
				sio_voice_clk_enable(enable);
			}
		}
	}
	mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
}

void sio_bt_module_enable(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	mutex_lock(&g_hi3630_asp_cfg_data->mutex);
	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->sio_bt_module_count) {
			/* disable reset & enable clk */
			hi3630_cfg_write(HI3630_CFG_R_RST_CTRLDIS_REG, RST_SIO_BT_BIT);
			hi3630_cfg_write(HI3630_CFG_R_GATE_EN_REG, CLK_SIO_BT_BIT);

			if (g_hi3630_asp_cfg_data->sio_bt_master) {
				hi3630_cfg_write(HI3630_CFG_R_CLK_SEL_REG, ASP_CFG_SIO_BT_MASTER_BIT);
				sio_bt_clk_enable(enable);
				hi3630_cfg_write(HI3630_CFG_R_GATE_EN_REG, CLK_SIO_BT_BCLK_BIT);
			} else {
				hi3630_cfg_write(HI3630_CFG_R_CLK_SEL_REG, ASP_CFG_SIO_BT_SLAVE_BIT);
			}

			ASP_DELAY;
		}

		g_hi3630_asp_cfg_data->sio_bt_module_count++;
	} else {
		if (0 == g_hi3630_asp_cfg_data->sio_bt_module_count) {
			loge("sio bt has already closed.\n");
			mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
			return;
		}

		g_hi3630_asp_cfg_data->sio_bt_module_count--;

		if (0 == g_hi3630_asp_cfg_data->sio_bt_module_count) {

			if (g_hi3630_asp_cfg_data->sio_bt_master) {
				hi3630_cfg_write(HI3630_CFG_R_GATE_DIS_REG, CLK_SIO_BT_BCLK_BIT);
				sio_bt_clk_enable(enable);
			}

			hi3630_cfg_write(HI3630_CFG_R_GATE_DIS_REG, CLK_SIO_BT_BIT);
			hi3630_cfg_write(HI3630_CFG_R_RST_CTRLEN_REG, RST_SIO_BT_BIT);
		}
	}
	mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
}

void sio_modem_module_enable(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	mutex_lock(&g_hi3630_asp_cfg_data->mutex);
	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->sio_modem_module_count) {
			/* disable reset & enable clk */
			hi3630_cfg_write(HI3630_CFG_R_RST_CTRLDIS_REG, RST_SIO_MODEM_BIT);
			hi3630_cfg_write(HI3630_CFG_R_GATE_EN_REG, CLK_SIO_MODEM_BIT);

			if (g_hi3630_asp_cfg_data->sio_modem_master) {
				hi3630_cfg_write(HI3630_CFG_R_CLK_SEL_REG, ASP_CFG_SIO_MODEM_MASTER_BIT);
				sio_modem_clk_enable(enable);
				hi3630_cfg_write(HI3630_CFG_R_GATE_EN_REG, CLK_SIO_MODEM_BCLK_BIT);

			} else {
				hi3630_cfg_write(HI3630_CFG_R_CLK_SEL_REG, ASP_CFG_SIO_MODEM_SLAVE_BIT);
			}

			ASP_DELAY;
		}

		g_hi3630_asp_cfg_data->sio_modem_module_count++;
	} else {
		if (0 == g_hi3630_asp_cfg_data->sio_modem_module_count) {
			loge("sio modem has already closed.\n");
			mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
			return;
		}

		g_hi3630_asp_cfg_data->sio_modem_module_count--;

		if (0 == g_hi3630_asp_cfg_data->sio_modem_module_count) {

			if (g_hi3630_asp_cfg_data->sio_modem_master) {
				hi3630_cfg_write(HI3630_CFG_R_GATE_DIS_REG, CLK_SIO_MODEM_BCLK_BIT);
				sio_modem_clk_enable(enable);
			}

			hi3630_cfg_write(HI3630_CFG_R_GATE_DIS_REG, CLK_SIO_MODEM_BIT);
			hi3630_cfg_write(HI3630_CFG_R_RST_CTRLEN_REG, RST_SIO_MODEM_BIT);
		}
	}
	mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
}

void srcup_module_enable(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	mutex_lock(&g_hi3630_asp_cfg_data->mutex);
	if (enable) {
		/* enable clk */
		if (0 == g_hi3630_asp_cfg_data->srcup_module_count) {
			hi3630_cfg_write(SRCUP_EN_REG, SRCUP_ENABLE);

			/*set output fix addr*/
			hi3630_cfg_write(SRCUP_LEFT_FIX_ADDR_REG, HI3630_SRCUP_SIO_FIXED_ADDR);
			hi3630_cfg_write(SRCUP_RIGHT_FIX_ADDR_REG, HI3630_SRCUP_SIO_FIXED_ADDR);
		}

		g_hi3630_asp_cfg_data->srcup_module_count++;
	} else {
		if (0 == g_hi3630_asp_cfg_data->srcup_module_count) {
			loge("srcup has already closed.\n");
			mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
			return;
		}

		g_hi3630_asp_cfg_data->srcup_module_count--;

		/* disable clk */
		if (0 == g_hi3630_asp_cfg_data->srcup_module_count)
			hi3630_cfg_write(SRCUP_EN_REG, SRCUP_DISABLE);
	}
	mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
}

void srcdown_module_enable(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	mutex_lock(&g_hi3630_asp_cfg_data->mutex);
	if (enable) {
		/* enable clk */
		if (0 == g_hi3630_asp_cfg_data->srcdown_module_count) {
			hi3630_cfg_write(HI3630_CFG_R_RST_CTRLDIS_REG, RST_SRCDOWN_BIT);
			hi3630_cfg_write(HI3630_CFG_R_GATE_EN_REG, CLK_SRCDOWN_HCLK_BIT);

			ASP_DELAY;

			hi3630_cfg_write(SRCDOWN_EN_REG, SRCDOWN_ENABLE);

			/*set output fix addr*/
			hi3630_cfg_write(SRCDOWN_LEFT_FIX_ADDR_REG, HI3630_SRCDOWN_SIO_FIXED_ADDR);
			hi3630_cfg_write(SRCDOWN_RIGHT_FIX_ADDR_REG, HI3630_SRCDOWN_SIO_FIXED_ADDR);
		}

		g_hi3630_asp_cfg_data->srcdown_module_count++;
	} else {
		if (0 == g_hi3630_asp_cfg_data->srcdown_module_count) {
			loge("srcdown has already closed.\n");
			mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
			return;
		}

		g_hi3630_asp_cfg_data->srcdown_module_count--;

		/* disable clk */
		if (0 == g_hi3630_asp_cfg_data->srcdown_module_count) {

			hi3630_cfg_write(SRCDOWN_EN_REG, SRCDOWN_DISABLE);

			hi3630_cfg_write(HI3630_CFG_R_GATE_DIS_REG, CLK_SRCDOWN_HCLK_BIT);
			hi3630_cfg_write(HI3630_CFG_R_RST_CTRLEN_REG, RST_SRCDOWN_BIT);
		}
	}
	mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
}

void enable_srcup_interrupeter(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	mutex_lock(&g_hi3630_asp_cfg_data->mutex);
	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->srcup_interrupt_ref) {
			hi3630_cfg_set_bit(HI3630_CFG_R_INTR_NS_EN_REG, ASP_CFG_SRC_UP_INTR_OFFSET);
		}

		g_hi3630_asp_cfg_data->srcup_interrupt_ref++;
	} else {
		if(0 == g_hi3630_asp_cfg_data->srcup_interrupt_ref){
			loge("srcup interrupt has already disabled.\n");
			mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
			return;
		}

		g_hi3630_asp_cfg_data->srcup_interrupt_ref--;

		/* disable interrupt*/
		if (0 == g_hi3630_asp_cfg_data->srcup_interrupt_ref) {
			hi3630_cfg_clr_bit(HI3630_CFG_R_INTR_NS_EN_REG, ASP_CFG_SRC_UP_INTR_OFFSET);
		}
	}
	mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
}

void enable_srcdown_interrupeter(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	mutex_lock(&g_hi3630_asp_cfg_data->mutex);
	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->srcdown_interrupt_ref) {
			hi3630_cfg_set_bit(HI3630_CFG_R_INTR_NS_EN_REG, ASP_CFG_SRC_DOWN_INTR_OFFSET);
		}

		g_hi3630_asp_cfg_data->srcdown_interrupt_ref++;
	} else {
		if(0 == g_hi3630_asp_cfg_data->srcdown_interrupt_ref){
			loge("srcdown interrupt has already disabled.\n");
			mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
			return;
		}

		g_hi3630_asp_cfg_data->srcdown_interrupt_ref--;

		/* disable interrupt*/
		if (0 == g_hi3630_asp_cfg_data->srcdown_interrupt_ref) {
			hi3630_cfg_clr_bit(HI3630_CFG_R_INTR_NS_EN_REG, ASP_CFG_SRC_DOWN_INTR_OFFSET);
		}
	}
	mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
}

void hdmi_module_enable(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	mutex_lock(&g_hi3630_asp_cfg_data->mutex);
	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->hdmi_module_count) {
			asp_h2x_module_enable(true);
			/*disable reset*/
			hi3630_cfg_write(HI3630_CFG_R_RST_CTRLDIS_REG, RST_ASP_HDMI_BIT);
			/*enable hdmimclk_div & hdmirefclk_div*/
			hi3630_cfg_set_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_HDMIMCLK_DIV_OFFSET);
			hi3630_cfg_set_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_HDMIREF_DIV_OFFSET);
			/*todo: enable clk & disable reset */
			hi3630_cfg_write(HI3630_CFG_R_GATE_EN_REG, CLK_HDMI_HCLK_BIT);
			hi3630_cfg_write(HI3630_CFG_R_GATE_EN_REG, CLK_HDMI_MCLK_BIT);
			hi3630_cfg_write(HI3630_CFG_R_GATE_EN_REG, CLK_HDMI_BCLK_BIT);

			ASP_DELAY;
		}

		g_hi3630_asp_cfg_data->hdmi_module_count++;
	} else {
		if (0 == g_hi3630_asp_cfg_data->hdmi_module_count) {
			loge("sio modem has already closed.\n");
			mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
			return;
		}

		g_hi3630_asp_cfg_data->hdmi_module_count--;

		if (0 == g_hi3630_asp_cfg_data->hdmi_module_count) {
			/*dis clk*/
			hi3630_cfg_write(HI3630_CFG_R_GATE_DIS_REG, CLK_HDMI_BCLK_BIT);
			hi3630_cfg_write(HI3630_CFG_R_GATE_DIS_REG, CLK_HDMI_MCLK_BIT);
			hi3630_cfg_write(HI3630_CFG_R_GATE_DIS_REG, CLK_HDMI_HCLK_BIT);
			/*disable hdmimclk_div & hdmirefclk_div*/
			hi3630_cfg_clr_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_HDMIMCLK_DIV_OFFSET);
			hi3630_cfg_clr_bit(HI3630_CFG_R_GATE_CLKDIV_EN_REG, ASP_CFG_GT_HDMIREF_DIV_OFFSET);

			/*enable reset*/
			hi3630_cfg_write(HI3630_CFG_R_RST_CTRLEN_REG, RST_ASP_HDMI_BIT);
			asp_h2x_module_enable(false);
		}
	}
	mutex_unlock(&g_hi3630_asp_cfg_data->mutex);
}

void enable_hdmi_interrupeter(bool enable)
{
	BUG_ON(NULL == g_hi3630_asp_cfg_data);

	if (enable) {
		if (0 == g_hi3630_asp_cfg_data->hdmi_interrupt_ref) {
			hi3630_cfg_set_bit(HI3630_CFG_R_INTR_NS_EN_REG, ASP_CFG_ASP_HDMI_INT_OFFSET);
		}

		g_hi3630_asp_cfg_data->hdmi_interrupt_ref++;
	} else {
		if(0 == g_hi3630_asp_cfg_data->hdmi_interrupt_ref){
			loge("srcup interrupt has already disabled.\n");
			return;
		}

		g_hi3630_asp_cfg_data->hdmi_interrupt_ref--;

		/* disable interrupt*/
		if (0 == g_hi3630_asp_cfg_data->hdmi_interrupt_ref) {
			hi3630_cfg_clr_bit(HI3630_CFG_R_INTR_NS_EN_REG, ASP_CFG_ASP_HDMI_INT_OFFSET);
		}
	}
}


void hi3630_hdmi_set_freq(const unsigned int value)
{
	/*hdmi frequency 48k or 96k
	 *48k:0x45E7B2
	 *96k:0x8BCF65
	 */
	hi3630_cfg_write(HI3630_CFG_R_CLK2_DIV_REG, value);
}

static int hi3630_asp_common_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hi3630_asp_cfg_data *pdata = NULL;

	if (!dev) {
		loge("platform_device has no device\n");
		return -ENOENT;
	}

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata){
		dev_err(dev, "cannot allocate hi3630 asp cfg platform data\n");
		return -ENOMEM;
	}

	pdata->hi3630_asp_irq = dev_get_drvdata(pdev->dev.parent);
	if (!pdata->hi3630_asp_irq) {
		dev_err(dev, "get parend device error\n");
		return -ENOENT;
	}

	g_hi3630_asp_cfg_data = pdata;

	/* init pdata */
	mutex_init(&pdata->mutex);
	spin_lock_init(&pdata->lock);

	pdata->sio_audio_module_count = 0;
	pdata->sio_voice_module_count = 0;
	pdata->sio_bt_module_count = 0;
	pdata->sio_modem_module_count = 0;
	pdata->srcup_module_count = 0;
	pdata->srcdown_module_count = 0;
	pdata->hdmi_module_count = 0;
	pdata->asp_h2x_module_count = 0;

	pdata->sio_audio_clk_count = 0;
	pdata->sio_voice_clk_count = 0;
	pdata->sio_bt_clk_count = 0;
	pdata->sio_modem_clk_count = 0;

	pdata->sio_audio_master = false;
	pdata->sio_voice_master = false;
	pdata->sio_bt_master = false;
	pdata->sio_modem_master = false;

	pdata->srcup_interrupt_ref = 0;
	pdata->srcdown_interrupt_ref = 0;
	pdata->hdmi_interrupt_ref = 0;
	pdata->siobclk_div_count = 0;

	platform_set_drvdata(pdev, pdata);

	return 0;
}

static int hi3630_asp_common_remove(struct platform_device *pdev)
{
	return 0;
}

static struct platform_driver hi3630_asp_common_driver = {
	.probe	= hi3630_asp_common_probe,
	.remove	= hi3630_asp_common_remove,
	.driver	= {
		.owner	= THIS_MODULE,
		.name	= "hi3630-asp-common",
		.of_match_table = of_match_ptr(hi3630_asp_common_match),
	},
};

//module_platform_driver(hi3630_asp_common_driver);

static int __init hi3630_asp_common_init( void )
{
    platform_driver_register(&hi3630_asp_common_driver);

    return 0;
}

static void __exit hi3630_asp_common_exit( void )
{
    platform_driver_unregister(&hi3630_asp_common_driver);
}

device_initcall(hi3630_asp_common_init);
module_exit(hi3630_asp_common_exit);


MODULE_DESCRIPTION("ASoC hi3630 asp common driver");
MODULE_AUTHOR("chengong <apollo.chengong@huawei.com>");
MODULE_LICENSE("GPL");
