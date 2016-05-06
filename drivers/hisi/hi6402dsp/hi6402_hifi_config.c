/*
 * hi6402_hifi_config.c -- adapt 64xx hifi misc to 6402
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/hisi/hi64xx_hifi_misc.h>
#include <hisi/hilog.h>
#include <linux/hisi/hi64xx/hi6402_dsp_regs.h>
#include "hi64xx_hifi_debug.h"
#include "hi6402_hifi_config.h"
#include "hi64xx_hifi_img_dl.h"

static void hi6402_hifi_autoclk_enable(bool enable)
{
	if (enable) {
		/* clr sc_mad_mic_bp only when mainpga selected mainmic. */
		if (hi64xx_hifi_read_reg(HI64xx_CODEC_MAINPGA_SEL)
			& (1 << HI64xx_CODEC_MAINPGA_SEL_BIT)) {
			/* mainpga selected hsmic. */
			hi64xx_hifi_write_reg(HI64xx_SC_MAD_CTRL0, 0x4d);
		} else {
			/* mainpga selected mainmic. */
			hi64xx_hifi_write_reg(HI64xx_SC_MAD_CTRL0, 0x45);
		}
	} else {
		hi64xx_hifi_write_reg(HI64xx_SC_MAD_CTRL0, 0x3e);
	}
}

static int hi6402_hifi_cfg_sw_mode(int val)
{
	u32 loopcount = 0;
	u32 state = 0xffff;

	while (state != val && loopcount < 1000) {
		udelay(60);
		state = hi64xx_hifi_read_reg(HI64xx_CFG_REG_CLK_STATUS);
		loopcount++;
	}

	HI64XX_DSP_INFO("%s cfg switch %s wait %d us\n", __FUNCTION__,
		val == HI6402_CFG_SW_ENTER ? "++" : "--", loopcount * 60);

	if (state != val) {
		return -1;
	} else {
		return 0;
	}
}

static void hi6402_hifi_apb_clk(bool enable)
{
	if (enable) {
		hi64xx_hifi_reg_clr_bit(HI6402_APB_CLK_CFG_REG, HI6402_APB_CLK_EN_BIT);
		hi64xx_hifi_reg_set_bit(HI6402_APB_CLK_CFG_REG, HI6402_PERI_CLK_SEL_BIT);
		hi64xx_hifi_reg_set_bit(HI6402_APB_CLK_CFG_REG, HI6402_APB_CLK_EN_BIT);
	} else {
		hi64xx_hifi_reg_clr_bit(HI6402_APB_CLK_CFG_REG, HI6402_APB_CLK_EN_BIT);
		hi64xx_hifi_reg_clr_bit(HI6402_APB_CLK_CFG_REG, HI6402_PERI_CLK_SEL_BIT);
		hi64xx_hifi_reg_set_bit(HI6402_APB_CLK_CFG_REG, HI6402_APB_CLK_EN_BIT);
	}
}

static void hi6402_hifi_mad_auto_clk(bool enable)
{
	if (enable) {
		HI64XX_DSP_INFO("set mad mode[enable] \n");

		/* sc_dsp_en lowpower 0:disable 1:enable */
		hi64xx_hifi_reg_set_bit(HI64xx_IRQ_SC_DSP_CTRL0, 0);
		/* sc_dsp_bp hifi clk enable 0:hardware ctl  1:software ctl */
		hi64xx_hifi_reg_clr_bit(HI64xx_IRQ_SC_DSP_CTRL0, 1);

		/* sc_mad_mode 0:disable 1:enable */
		hi64xx_hifi_reg_set_bit(HI64xx_IRQ_SC_DSP_CTRL0, 4);
		/* sc_dsp_runstall_bp 0:hardware ctl  1:software ctl */
		hi64xx_hifi_reg_clr_bit(HI64xx_IRQ_SC_DSP_CTRL0, 5);
		/* sc_dsp_hifi_div_bp:0:hardware 1:software */
		hi64xx_hifi_reg_clr_bit(HI64xx_IRQ_SC_DSP_CTRL0, 6);

	} else {
		HI64XX_DSP_INFO("set mad mode[disable] \n");

		/* open hifi clk */
		hi64xx_hifi_reg_clr_bit(HI64xx_IRQ_SC_DSP_CTRL0, 0);
		hi64xx_hifi_reg_set_bit(HI64xx_IRQ_SC_DSP_CTRL0, 1);
		hi64xx_hifi_reg_clr_bit(HI64xx_IRQ_SC_DSP_CTRL0, 4);
		hi64xx_hifi_reg_set_bit(HI64xx_IRQ_SC_DSP_CTRL0, 5);
		hi64xx_hifi_reg_set_bit(HI64xx_IRQ_SC_DSP_CTRL0, 6);

	}
}

static int hi6402_hifi_cfg_clk(bool enable)
{
	int ret = 0;

	/* request setup cfg clk switch */
	hi64xx_hifi_reg_set_bit(HI64xx_CFG_REG_CLK_CTRL_REG,
				HI64xx_CFG_REG_CLK_SW_REQ_BIT);

	/* wait 6402 dsp enter cfg clk sel mode */
	ret = hi6402_hifi_cfg_sw_mode(HI6402_CFG_SW_ENTER);
	if(0 != ret) {
		HI64XX_DSP_ERROR("%s dsp state err\n",__FUNCTION__);
		HiLOGE("audio","hi64xx_hifi_misc", "%s dsp state err\n",__FUNCTION__);
	}

	/* switch hi6402 cfg_clk */
	if(enable) {/* sw ->hifi */
		hi6402_hifi_apb_clk(enable);
		hi6402_hifi_mad_auto_clk(true);
		hi64xx_hifi_reg_clr_bit(HI64xx_CFG_REG_CLK_CTRL_REG,
				HI64xx_CFG_REG_TMUX_CLKB_BP_BIT);
		hi64xx_hifi_reg_set_bit(HI64xx_CFG_REG_CLK_CTRL_REG,
				HI64xx_CFG_REG_CLK_SEL_BIT);
	}else {/* sw->ap */
		hi64xx_hifi_reg_clr_bit(HI64xx_CFG_REG_CLK_CTRL_REG,
				HI64xx_CFG_REG_CLK_SEL_BIT);
		hi64xx_hifi_reg_set_bit(HI64xx_CFG_REG_CLK_CTRL_REG,
				HI64xx_CFG_REG_TMUX_CLKB_BP_BIT);
		hi6402_hifi_mad_auto_clk(false);
		hi6402_hifi_apb_clk(enable);
	}
	/* notify dsp cfg clk switch done */
	hi64xx_hifi_reg_clr_bit(HI64xx_CFG_REG_CLK_CTRL_REG,
			HI64xx_CFG_REG_CLK_SW_REQ_BIT);
	return ret;
}

static int hi6402_hifi_suspend(void)
{
	int ret = 0;

	hi6402_hifi_autoclk_enable(true);

	ret = hi6402_hifi_cfg_clk(true);
	if (ret)
		HI64XX_DSP_ERROR("6402 cfg clk switch to dsp err\n");

	return ret;
}

static int hi6402_hifi_resume(void)
{
	int ret = 0;

	ret = hi6402_hifi_cfg_clk(false);

	if (ret)
		HI64XX_DSP_ERROR("6402 cfg clk switch to ap err\n");

	hi6402_hifi_autoclk_enable(false);

	return ret;
}

static void hi6402_hifi_runstall_cfg(bool pull_down)
{
	IN_FUNCTION;

	if (pull_down) {
		/* Pull down runstall of HIFI*/
		hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SC_DSP_CTRL0, 2);
	} else {
		/* Pull up runstall of HIFI*/
		hi64xx_hifi_reg_set_bit(HI64xx_DSP_SC_DSP_CTRL0, 2);
	}
	OUT_FUNCTION;
}

static void hi6402_hifi_watchdog_enable(bool enable)
{
	IN_FUNCTION;
	if (enable) {
		/*bit3:wd_pclk_en 0:disable 1:enable*/
		hi64xx_hifi_reg_set_bit(HI64xx_DSP_APB_CLK_CFG, 3);
	} else {
		/*bit3:wd_pclk_en 0:disable 1:enable*/
		hi64xx_hifi_reg_clr_bit(HI64xx_DSP_APB_CLK_CFG, 3);
	}
	OUT_FUNCTION;
}

static void hi6402_hifi_notify_dsp(void)
{
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_DSP_NMI, 2);
}


/* when hifi is not running, ap access APB register with 0x20007020 bit[2]=1'b0
 * when hifi is running, ap & hifi access APB register with 0x20007020 bit[2]=0'b0*/
static void hi6402_hifi_ram2axi_cfg(bool enable)
{
	unsigned int val;

	IN_FUNCTION;

	if (enable) {
		val = hi64xx_hifi_read_reg(HI64xx_DSP_RAM2AXI_CTRL);
		if(0 == (val & 0x1))
			HI64XX_DSP_ERROR("reg error! 0x20007020 = 0x%x\n", val);

		hi64xx_hifi_write_reg(HI64xx_DSP_RAM2AXI_CTRL, 0x1);
	} else {
		val = hi64xx_hifi_read_reg(HI64xx_DSP_RAM2AXI_CTRL);
		if(0 == (val & 0x1))
			HI64XX_DSP_ERROR("reg error! 0x20007020 = 0x%x\n", val);

		hi64xx_hifi_write_reg(HI64xx_DSP_RAM2AXI_CTRL, 0x5);
	}

	OUT_FUNCTION;
}

static void hi6402_hifi_clk_enable(bool enable)
{
	IN_FUNCTION;

	if (enable) {
		hi64xx_hifi_reg_set_bit(HI64xx_DSP_SC_DSP_CTRL0, 3);
		/*bit6:hifi_div_clk_en 0:disable 1:enable*/
		hi64xx_hifi_reg_set_bit(HI64xx_DSP_CLK_CFG, 6);
	} else {
		hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SC_DSP_CTRL0, 3);
		/*bit6:hifi_div_clk_en 0:disable 1:enable*/
		hi64xx_hifi_reg_clr_bit(HI64xx_DSP_CLK_CFG, 6);
	}

	OUT_FUNCTION;
}

static void hi6402_hifi_init(void)
{
	IN_FUNCTION;

	/* 1.reset dsp_pd_srst_req */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SW_RST_REQ, 4);

	/* 2.close dspif clocks, and soft reset dspif */
	hi64xx_hifi_write_reg(HI6402_DSP_I2S_DSPIF_CLK_EN, 0x0);
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_DAC_DP_CLK_EN_1, 4);

	/* 3.turn on dsp_top_mtcmos_ctrl*/
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_LP_CTRL, 0);
	/* 4.enable dsp_top_iso_ctrl */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_LP_CTRL, 1);

	/* 5.sc_dsp_en dsp low power enable */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SC_DSP_CTRL0, 0);
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SC_DSP_CTRL0, 5);
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SC_DSP_CTRL0, 6);

	/* pull up runstall */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SC_DSP_CTRL0, 2);

	/* 6.apb_pd_pclk_en Open APB clock of power-off area */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_APB_CLK_CFG, 6);

	/* 7.Release dsp_pd_srst_req */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SW_RST_REQ, 4);

	/* disable watchdog */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_APB_CLK_CFG, 3);

	/* sc_dsp_sft_clk_en */
	hi6402_hifi_clk_enable(true);

	OUT_FUNCTION;
}

static void hi6402_hifi_deinit(void)
{
	IN_FUNCTION;

	/* Close watchdog clock */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_APB_CLK_CFG, 3);

	/* Close HIFI clock */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SC_DSP_CTRL0, 0);
	hi6402_hifi_clk_enable(false);

	/* Close APB clock */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_APB_CLK_CFG, 6);

	/* Close DSPIF clocks, and soft reset DSPIF */
	hi64xx_hifi_write_reg(HI6402_DSP_I2S_DSPIF_CLK_EN, 0x0);
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_DAC_DP_CLK_EN_1, 4);

	/* Enable isolation cell */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_LP_CTRL, 1);

	/* Soft reset HIFI */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SW_RST_REQ, 4);

	/* Turn off power of power-off area */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_LP_CTRL, 0);

	/* Pull up runstall of HIFI */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SC_DSP_CTRL0, 2);

	/* disable axi */
	hi64xx_hifi_write_reg(HI64xx_DSP_RAM2AXI_CTRL, 0x05);

	OUT_FUNCTION;
}

int hi6402_hifi_config_init(struct snd_soc_codec *codec,
				struct hi64xx_resmgr *resmgr,
				struct hi64xx_irq *irqmgr)
{
	struct hi64xx_dsp_config dsp_config;
	struct hi64xx_hifi_img_dl_config dl_config;
	int ret = 0;

	if (!codec || !resmgr|| !irqmgr)
		return -EINVAL;

	HI64XX_DSP_INFO("%s++\n", __FUNCTION__);

	memset(&dsp_config, 0, sizeof(dsp_config));
	memset(&dl_config, 0, sizeof(dl_config));

	dsp_config.slimbus_load = false;
	dsp_config.msg_addr = HI6402_MSG_ADDR;
	dsp_config.para_addr = HI6402_PARA_ADDR;
	dsp_config.cmd0_addr = HI6402_DSP_CMD0;
	dsp_config.cmd1_addr = HI6402_DSP_CMD1;
	dsp_config.cmd2_addr = HI6402_DSP_CMD2;
	dsp_config.cmd3_addr = HI6402_DSP_CMD3;
	dsp_config.wtd_irq_num = IRQ_WTD;
	dsp_config.vld_irq_num = IRQ_CMD_VALID;

	dsp_config.dsp_ops.init = hi6402_hifi_init;
	dsp_config.dsp_ops.deinit = hi6402_hifi_deinit;
	dsp_config.dsp_ops.clk_enable = hi6402_hifi_clk_enable;
	dsp_config.dsp_ops.ram2axi = hi6402_hifi_ram2axi_cfg;
	dsp_config.dsp_ops.runstall = hi6402_hifi_runstall_cfg;
	dsp_config.dsp_ops.wtd_enable = hi6402_hifi_watchdog_enable;
	dsp_config.dsp_ops.notify_dsp = hi6402_hifi_notify_dsp;
	dsp_config.dsp_ops.suspend = hi6402_hifi_suspend;
	dsp_config.dsp_ops.resume = hi6402_hifi_resume;

	dl_config.dspif_clk_en_addr = HI6402_DSP_I2S_DSPIF_CLK_EN;

	ret = hi64xx_hifi_misc_init(codec, resmgr, irqmgr, &dsp_config);

	ret += hi64xx_hifi_img_dl_init(irqmgr, &dl_config);

	HI64XX_DSP_INFO("%s--\n", __FUNCTION__);

	return ret;
}
EXPORT_SYMBOL(hi6402_hifi_config_init);

void hi6402_hifi_config_deinit(void)
{
	hi64xx_hifi_misc_deinit();

	hi64xx_hifi_img_dl_deinit();
}
EXPORT_SYMBOL(hi6402_hifi_config_deinit);

MODULE_DESCRIPTION("hi64xx hifi misc driver");
MODULE_LICENSE("GPL");
