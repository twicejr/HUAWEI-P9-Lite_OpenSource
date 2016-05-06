/*
 * hi6403_hifi_config.c -- adapt 64xx hifi misc to 6403
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
//#include <../../../sound/soc/codecs/hi6403.h>
#include <linux/hisi/hi64xx_hifi_misc.h>
#include <linux/hisi/hi64xx/hi6403_dsp_regs.h>
#include "hi64xx_hifi_debug.h"
#include "hi6403_hifi_config.h"
#include "hi64xx_hifi_img_dl.h"

static void hi6403_hifi_runstall_cfg(bool pull_down)
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

static void hi6403_hifi_watchdog_enable(bool enable)
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

static void hi6403_hifi_notify_dsp(void)
{
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_DSP_NMI, 2);
}

/* when hifi is not running, ap access APB register with 0x20007020 bit[2]=1'b0
 * when hifi is running, ap & hifi access APB register with 0x20007020 bit[2]=0'b0*/
static void hi6403_ram2axi_cfg_with_hifi(bool enable)
{
	IN_FUNCTION;

	hi64xx_hifi_write_reg(HI64xx_DSP_RAM2AXI_CTRL, 0x1);

	OUT_FUNCTION;
}

static void hi6403_hifi_clk_enable(bool enable)
{
	IN_FUNCTION;

	if (enable) {
		hi64xx_hifi_reg_set_bit(HI64xx_DSP_SC_DSP_CTRL0, 3);
		hi64xx_hifi_reg_set_bit(HI64xx_DSP_SC_DSP_CTRL0, 4);

		/*bit6:hifi_div_clk_en 0:disable 1:enable*/
		hi64xx_hifi_reg_set_bit(HI64xx_DSP_CLK_CFG, 6);
		hi64xx_hifi_reg_set_bit(HI6403_DSP_CTRL6_DMAC, 6);

	} else {
		hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SC_DSP_CTRL0, 3);

		hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SC_DSP_CTRL0, 4);
		/*bit6:hifi_div_clk_en 0:disable 1:enable*/
		hi64xx_hifi_reg_clr_bit(HI64xx_DSP_CLK_CFG, 6);
		hi64xx_hifi_reg_clr_bit(HI6403_DSP_CTRL6_DMAC, 6);
	}

	OUT_FUNCTION;
}

static void hi6403_hifi_init(void)
{
	IN_FUNCTION;

	/* 1.reset dsp_pd_srst_req */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SW_RST_REQ, 2);
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SW_RST_REQ, 3);
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SW_RST_REQ, 5);
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SW_RST_REQ, 6);

	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_OCDHALTON_RST, 0);
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_DEBUG_RST, 0);

	/* 2.close dspif clocks, and soft reset dspif */
	hi64xx_hifi_write_reg(HI6403_DSP_I2S_DSPIF_CLK_EN, 0x0);

	/* 3.turn on dsp_top_mtcmos_ctrl*/
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_LP_CTRL, 0);
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_LP_CTRL, 3);
	hi64xx_hifi_reg_clr_bit(HI6403_DSP_LP_CTRL1,0);

	/* 4.enable dsp_top_iso_ctrl */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_LP_CTRL, 1);
	hi64xx_hifi_reg_clr_bit(HI6403_DSP_LP_CTRL1,1);
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_LP_CTRL, 4);

	/* 5.sc_dsp_en dsp low power enable */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SC_DSP_CTRL0, 0);

	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SC_DSP_CTRL0, 3);
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SC_DSP_CTRL0, 4);
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SC_DSP_CTRL0, 6);

	/* pull up runstall */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SC_DSP_CTRL0, 2);

	/* 6.apb_pd_pclk_en Open APB clock of power-off area */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_APB_CLK_CFG, 6);

	//hi64xx_hifi_write_reg(HI6403_CFG_REG_CLK_CTRL, 0x4);
	/* 7.Release dsp_pd_srst_req */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SW_RST_REQ, 5);
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SW_RST_REQ, 6);
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SW_RST_REQ, 2);
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SW_RST_REQ, 3);
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_OCDHALTON_RST, 0);
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_DEBUG_RST, 0);

	/* disable watchdog */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_APB_CLK_CFG, 3);

	/* sc_dsp_sft_clk_en */
	hi6403_hifi_clk_enable(true);

	OUT_FUNCTION;
}

static void hi6403_hifi_deinit(void)
{
	IN_FUNCTION;

	/* Close watchdog clock */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_APB_CLK_CFG, 3);

	/* Close HIFI clock */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_SC_DSP_CTRL0, 0);
	hi6403_hifi_clk_enable(false);

	/* Close APB clock */
	hi64xx_hifi_reg_clr_bit(HI64xx_DSP_APB_CLK_CFG, 6);

	/* Close DSPIF clocks, and soft reset DSPIF */
	hi64xx_hifi_write_reg(HI6403_DSP_I2S_DSPIF_CLK_EN, 0x0);

	/* Enable isolation cell */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_LP_CTRL, 1);

	/* Soft reset HIFI */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SW_RST_REQ, 5);

	hi64xx_hifi_reg_set_bit(HI6403_DSP_LP_CTRL1,0);
	hi64xx_hifi_reg_set_bit(HI6403_DSP_LP_CTRL1,1);

	/* Turn off power of power-off area */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_LP_CTRL, 0);

	/* Pull up runstall of HIFI */
	hi64xx_hifi_reg_set_bit(HI64xx_DSP_SC_DSP_CTRL0, 2);

	OUT_FUNCTION;
}

int hi6403_hifi_config_init(struct snd_soc_codec *codec,
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

	dsp_config.para_addr = HI6403_PARA_ADDR;
	dsp_config.msg_addr = HI6403_MSG_ADDR;
	dsp_config.slimbus_load = true;
	dsp_config.cmd0_addr = HI6403_DSP_CMD0;
	dsp_config.cmd1_addr = HI6403_DSP_CMD1;
	dsp_config.cmd2_addr = HI6403_DSP_CMD2;
	dsp_config.cmd3_addr = HI6403_DSP_CMD3;
	dsp_config.wtd_irq_num = IRQ_WTD;
	dsp_config.vld_irq_num = IRQ_CMD_VALID;

	dsp_config.dsp_ops.init = hi6403_hifi_init;
	dsp_config.dsp_ops.deinit = hi6403_hifi_deinit;
	dsp_config.dsp_ops.clk_enable = hi6403_hifi_clk_enable;
	dsp_config.dsp_ops.ram2axi = hi6403_ram2axi_cfg_with_hifi;
	dsp_config.dsp_ops.runstall = hi6403_hifi_runstall_cfg;
	dsp_config.dsp_ops.wtd_enable = hi6403_hifi_watchdog_enable;
	dsp_config.dsp_ops.notify_dsp = hi6403_hifi_notify_dsp;

	dl_config.dspif_clk_en_addr = HI6403_DSP_I2S_DSPIF_CLK_EN;

	ret = hi64xx_hifi_misc_init(codec, resmgr, irqmgr, &dsp_config);

	ret += hi64xx_hifi_img_dl_init(irqmgr, &dl_config);

	HI64XX_DSP_INFO("%s--\n", __FUNCTION__);

	return ret;
}
EXPORT_SYMBOL(hi6403_hifi_config_init);

void hi6403_hifi_config_deinit(void)
{
	hi64xx_hifi_misc_deinit();

	hi64xx_hifi_img_dl_deinit();
}
EXPORT_SYMBOL(hi6403_hifi_config_deinit);

MODULE_DESCRIPTION("hi64xx hifi misc driver");
MODULE_LICENSE("GPL");
