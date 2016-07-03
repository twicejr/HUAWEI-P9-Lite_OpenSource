/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/

#include "hisi_fb.h"
#include "hisi_dpe_utils.h"
#include "hisi_overlay_utils.h"

DEFINE_SEMAPHORE(hisi_fb_dss_regulator_sem);
static int dss_regulator_refcount = 0;


/*******************************************************************************
**
*/
static int dpe_init(struct hisi_fb_data_type *hisifd, bool fastboot_enable)
{
	BUG_ON(hisifd == NULL);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		init_post_scf(hisifd);
		init_dbuf(hisifd);
		init_dpp(hisifd);
		init_sbl(hisifd);
		init_acm(hisifd);
		init_acm_ce(hisifd);
	#ifdef CONFIG_HISI_FB_3660
		init_hiace(hisifd);
		init_dither(hisifd);
		init_arsr1p(hisifd);
	#endif
		init_igm_gmp_xcc_gm(hisifd);
		//reserved for HIACE, dither and arsr1p csc8b csc10b module init

		init_ifbc(hisifd);
		init_ldi(hisifd, fastboot_enable);

	#if defined(CONFIG_HISI_FB_3660) && !defined(HISI_CMDLIST_VERSION_NEW)
		//debug for chicago,TBD , to be deleted
		init_cmdlist(hisifd);
	#endif
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
	#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
		//dual lcd: 0x1, dual mipi: 0x0
		set_reg(hisifd->dss_base + GLB_DSI1_CLK_SEL, 0x1, 1, 0);
	#elif defined(CONFIG_HISI_FB_3660)
		set_reg(hisifd->dss_base + DSS_LDI0_OFFSET + LDI_DSI1_RST_SEL, 0x1, 1, 0);
	#endif
		// dual lcd: dsi_mux_sel=1, dual mipi: dsi_mux_sel=0
		set_reg(hisifd->dss_base + DSS_MCTRL_SYS_OFFSET + MCTL_DSI_MUX_SEL, 0x1, 1, 0);

		init_dbuf(hisifd);
		init_ldi(hisifd, fastboot_enable);
	} else if (hisifd->index == AUXILIARY_PANEL_IDX) {
		;
	} else {
		HISI_FB_ERR("fb%d, not support this device!\n", hisifd->index);
	}

	return 0;
}

static int dpe_deinit(struct hisi_fb_data_type *hisifd)
{
	BUG_ON(hisifd == NULL);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		deinit_ldi(hisifd);
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		deinit_ldi(hisifd);
	} else if (hisifd->index == AUXILIARY_PANEL_IDX) {
		;
	} else {
		HISI_FB_ERR("fb%d, not support this device!\n", hisifd->index);
	}

	return 0;
}

static void dpe_check_itf_status(struct hisi_fb_data_type *hisifd)
{
	int tmp = 0;
	int delay_count = 0;
	bool is_timeout = true;
	int itf_idx = 0;
	char __iomem *mctl_sys_base = NULL;

	BUG_ON(hisifd == NULL);

	if ((hisifd->index == PRIMARY_PANEL_IDX) ||
		(hisifd->index == EXTERNAL_PANEL_IDX)) {
		itf_idx = hisifd->index;
		mctl_sys_base =  hisifd->dss_base + DSS_MCTRL_SYS_OFFSET;

		while (1) {
			tmp = inp32(mctl_sys_base + MCTL_MOD17_STATUS + itf_idx * 0x4);
			if (((tmp & 0x10) == 0x10) || delay_count > 100) {
				is_timeout = (delay_count > 100) ? true : false;
				delay_count = 0;
				break;
			} else {
				mdelay(1);
				++delay_count;
			}
		}

		if (is_timeout) {
			HISI_FB_DEBUG("mctl_itf%d not in idle status,ints=0x%x !\n", hisifd->index, tmp);
		}
	}
}

static int dpe_irq_enable(struct hisi_fb_data_type *hisifd)
{
	BUG_ON(hisifd == NULL);

	if (hisifd->dpe_irq)
		enable_irq(hisifd->dpe_irq);

	return 0;
}

static int dpe_irq_disable(struct hisi_fb_data_type *hisifd)
{
	BUG_ON(hisifd == NULL);

	if (hisifd->dpe_irq)
		disable_irq(hisifd->dpe_irq);

	/*disable_irq_nosync(hisifd->dpe_irq);*/

	return 0;
}

static int dpe_irq_disable_nosync(struct hisi_fb_data_type *hisifd)
{
	BUG_ON(hisifd == NULL);

	if (hisifd->dpe_irq)
		disable_irq_nosync(hisifd->dpe_irq);

	return 0;
}

int dpe_regulator_enable(struct hisi_fb_data_type *hisifd)
{
	int ret = 0;

	BUG_ON(hisifd == NULL);

	down(&hisi_fb_dss_regulator_sem);

	ret = regulator_bulk_enable(1, hisifd->dpe_regulator);
	if (ret) {
		HISI_FB_ERR("fb%d dpe regulator_enable failed, error=%d!\n", hisifd->index, ret);
		goto regulator_sem;
	}

	ret = regulator_bulk_enable(1, hisifd->mmbuf_regulator);
	if (ret) {
		HISI_FB_ERR("fb%d mmbuf regulator_enable failed, error=%d!\n", hisifd->index, ret);
		goto regulator_sem;
	}

	dss_regulator_refcount++;
	if (hisifd->index == PRIMARY_PANEL_IDX) {
		HISI_FB_INFO("fb%d, dss_regulator_refcount=%d\n", hisifd->index, dss_regulator_refcount);
	}

regulator_sem:
	up(&hisi_fb_dss_regulator_sem);

	return ret;
}

int dpe_regulator_disable(struct hisi_fb_data_type *hisifd)
{
	int ret = 0;

	BUG_ON(hisifd == NULL);

	down(&hisi_fb_dss_regulator_sem);

	ret = regulator_bulk_disable(1, hisifd->mmbuf_regulator);
	if (ret != 0) {
		HISI_FB_ERR("fb%d mmbuf regulator_disable failed, error=%d!\n", hisifd->index, ret);
		goto regulator_sem;
	}

	ret = regulator_bulk_disable(1, hisifd->dpe_regulator);
	if (ret != 0) {
		HISI_FB_ERR("fb%d dpe regulator_disable failed, error=%d!\n", hisifd->index, ret);
		goto regulator_sem;
	}

	dss_regulator_refcount--;
	if (dss_regulator_refcount < 0) {
		HISI_FB_ERR("fb%d, dss_regulator_refcount=%d is error\n", hisifd->index, dss_regulator_refcount);
	}

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		HISI_FB_INFO("fb%d, dss_regulator_refcount=%d\n", hisifd->index, dss_regulator_refcount);
	}

regulator_sem:
	up(&hisi_fb_dss_regulator_sem);

	return ret;
}

int dpe_common_clk_enable(struct hisi_fb_data_type *hisifd)
{
	int ret = 0;
	struct clk *clk_tmp = NULL;

	BUG_ON(hisifd == NULL);

#ifdef CONFIG_DSS_MMBUF_CLK_USED
	clk_tmp = hisifd->dss_mmbuf_clk;
	if (clk_tmp) {
		ret = clk_prepare(clk_tmp);
		if (ret) {
			HISI_FB_ERR("fb%d dss_mmbuf_clk clk_prepare failed, error=%d!\n",
				hisifd->index, ret);
			return -EINVAL;
		}

		ret = clk_enable(clk_tmp);
		if (ret) {
			HISI_FB_ERR("fb%d dss_mmbuf_clk clk_enable failed, error=%d!\n",
				hisifd->index, ret);
			return -EINVAL;
		}
	}
#endif

	clk_tmp = hisifd->dss_axi_clk;
	if (clk_tmp) {
		ret = clk_prepare(clk_tmp);
		if (ret) {
			HISI_FB_ERR("fb%d dss_axi_clk clk_prepare failed, error=%d!\n",
				hisifd->index, ret);
			return -EINVAL;
		}

		ret = clk_enable(clk_tmp);
		if (ret) {
			HISI_FB_ERR("fb%d dss_axi_clk clk_enable failed, error=%d!\n",
				hisifd->index, ret);
			return -EINVAL;
		}
	}

	clk_tmp = hisifd->dss_pclk_dss_clk;
	if (clk_tmp) {
		ret = clk_prepare(clk_tmp);
		if (ret) {
			HISI_FB_ERR("fb%d dss_pclk_dss_clk clk_prepare failed, error=%d!\n",
				hisifd->index, ret);
			return -EINVAL;
		}

		ret = clk_enable(clk_tmp);
		if (ret) {
			HISI_FB_ERR("fb%d dss_pclk_dss_clk clk_enable failed, error=%d!\n",
				hisifd->index, ret);
			return -EINVAL;
		}
	}

	return 0;
}

int dpe_inner_clk_enable(struct hisi_fb_data_type *hisifd)
{
	int ret = 0;
	struct clk *clk_tmp = NULL;

	BUG_ON(hisifd == NULL);

	clk_tmp = hisifd->dss_pri_clk;
	if (clk_tmp) {
		ret = clk_prepare(clk_tmp);
		if (ret) {
			HISI_FB_ERR("fb%d dss_pri_clk clk_prepare failed, error=%d!\n",
				hisifd->index, ret);
			return -EINVAL;
		}

		ret = clk_enable(clk_tmp);
		if (ret) {
			HISI_FB_ERR("fb%d dss_pri_clk clk_enable failed, error=%d!\n",
				hisifd->index, ret);
			return -EINVAL;
		}
	}

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		clk_tmp = hisifd->dss_pxl0_clk;
		if (clk_tmp) {
			ret = clk_prepare(clk_tmp);
			if (ret) {
				HISI_FB_ERR("fb%d dss_pxl0_clk clk_prepare failed, error=%d!\n",
					hisifd->index, ret);
				return -EINVAL;
			}

			ret = clk_enable(clk_tmp);
			if (ret) {
				HISI_FB_ERR("fb%d dss_pxl0_clk clk_enable failed, error=%d!\n",
					hisifd->index, ret);
				return -EINVAL;
			}
		}
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		clk_tmp = hisifd->dss_pxl1_clk;
		if (clk_tmp) {
			ret = clk_prepare(clk_tmp);
			if (ret) {
				HISI_FB_ERR("fb%d dss_pxl1_clk clk_prepare failed, error=%d!\n",
					hisifd->index, ret);
				return -EINVAL;
			}

			ret = clk_enable(clk_tmp);
			if (ret) {
				HISI_FB_ERR("fb%d dss_pxl1_clk clk_enable failed, error=%d!\n",
					hisifd->index, ret);
				return -EINVAL;
			}
		}
	} else {
		;
	}

	return 0;
}

int dpe_common_clk_disable(struct hisi_fb_data_type *hisifd)
{
	struct clk *clk_tmp = NULL;

	BUG_ON(hisifd == NULL);

	clk_tmp = hisifd->dss_pclk_dss_clk;
	if (clk_tmp) {
		clk_disable(clk_tmp);
		clk_unprepare(clk_tmp);
	}

	clk_tmp = hisifd->dss_axi_clk;
	if (clk_tmp) {
		clk_disable(clk_tmp);
		clk_unprepare(clk_tmp);
	}

#ifdef CONFIG_DSS_MMBUF_CLK_USED
	clk_tmp = hisifd->dss_mmbuf_clk;
	if (clk_tmp) {
		clk_disable(clk_tmp);
		clk_unprepare(clk_tmp);
	}
#endif

	return 0;
}

int dpe_inner_clk_disable(struct hisi_fb_data_type *hisifd)
{
	struct clk *clk_tmp = NULL;

	BUG_ON(hisifd == NULL);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		clk_tmp = hisifd->dss_pxl0_clk;
		if (clk_tmp) {
			clk_disable(clk_tmp);
			clk_unprepare(clk_tmp);
		}
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		clk_tmp = hisifd->dss_pxl1_clk;
		if (clk_tmp) {
			clk_disable(clk_tmp);
			clk_unprepare(clk_tmp);
		}
	} else {
		;
	}

	clk_tmp = hisifd->dss_pri_clk;
	if (clk_tmp) {
		clk_disable(clk_tmp);
		clk_unprepare(clk_tmp);
	}

	return 0;
}


/*******************************************************************************
**
*/
static int dpe_set_fastboot(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);/*[false alarm]*/
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	//in probe
	//dpe_regulator_enable(hisifd);
	dpe_common_clk_enable(hisifd);
	dpe_inner_clk_enable(hisifd);

	dss_inner_clk_common_enable(hisifd, false);
	if (hisifd->index == PRIMARY_PANEL_IDX) {
		dss_inner_clk_pdp_enable(hisifd, false);
	}

#if 1
	dpe_init(hisifd, true);
#else
	// int dpe_init
	init_post_scf(hisifd);
	init_sbl(hisifd);
	init_acm(hisifd);
	init_acm_ce(hisifd);
	init_igm_gmp_xcc_gm(hisifd);
#endif

	ret = panel_next_set_fastboot(pdev);

	if (hisifd->panel_info.vsync_ctrl_type == VSYNC_CTRL_NONE) {
		dpe_interrupt_mask(hisifd);
		dpe_interrupt_clear(hisifd);
		dpe_irq_enable(hisifd);
		dpe_interrupt_unmask(hisifd);
	}

	//ldi_data_gate(hisifd, true);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int dpe_on(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	dpe_common_clk_enable(hisifd);
	dpe_regulator_enable(hisifd);
	dpe_inner_clk_enable(hisifd);

	dss_inner_clk_common_enable(hisifd, false);
	if (hisifd->index == PRIMARY_PANEL_IDX) {
		dss_inner_clk_pdp_enable(hisifd, false);
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		dss_inner_clk_sdp_enable(hisifd);
	} else {
		;
	}

	dpe_init(hisifd, false);

	if (is_ldi_panel(hisifd)) {
		hisifd->panel_info.lcd_init_step = LCD_INIT_POWER_ON;
		ret = panel_next_on(pdev);
	}

	ret = panel_next_on(pdev);

	if (hisifd->panel_info.vsync_ctrl_type == VSYNC_CTRL_NONE) {
	#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
		dpe_interrupt_mask(hisifd);
    #endif
		dpe_interrupt_clear(hisifd);
		dpe_irq_enable(hisifd);
		dpe_interrupt_unmask(hisifd);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int dpe_off(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (hisifd->panel_info.vsync_ctrl_type == VSYNC_CTRL_NONE) {
		dpe_interrupt_mask(hisifd);
		dpe_irq_disable(hisifd);
	} else {
		if (hisifd->vsync_ctrl.vsync_ctrl_enabled == 1) {
			if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_ISR_OFF) {
				dpe_interrupt_mask(hisifd);
				dpe_irq_disable(hisifd);
				HISI_FB_INFO("fb%d, need to disable dpe irq! vsync_ctrl_enabled=%d.\n",
					hisifd->index, hisifd->vsync_ctrl.vsync_ctrl_enabled);
			}
		}
	}

	ret = panel_next_off(pdev);

	dpe_deinit(hisifd);

	//FIXME:
	dpe_check_itf_status(hisifd);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		dss_inner_clk_pdp_disable(hisifd);
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		dss_inner_clk_sdp_disable(hisifd);
	} else {
		;
	}
	dss_inner_clk_common_disable(hisifd);

	dpe_inner_clk_disable(hisifd);
	dpe_regulator_disable(hisifd);
	dpe_common_clk_disable(hisifd);

	if (hisifd->vsync_ctrl_type != VSYNC_CTRL_NONE) {
		if (!is_dss_idle_enable())
			hisifd->panel_info.vsync_ctrl_type = VSYNC_CTRL_NONE;
		else
			hisifd->panel_info.vsync_ctrl_type = hisifd->vsync_ctrl_type;
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int dpe_lp_ctrl(struct platform_device *pdev, bool lp_enter)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (lp_enter) {
		ret = panel_next_lp_ctrl(pdev, lp_enter);

		if (hisifd->index == PRIMARY_PANEL_IDX) {
			dss_inner_clk_pdp_disable(hisifd);
		} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
			dss_inner_clk_sdp_disable(hisifd);
		} else {
			;
		}
		dss_inner_clk_common_disable(hisifd);
	} else {
		dss_inner_clk_common_enable(hisifd, false);
		if (hisifd->index == PRIMARY_PANEL_IDX) {
			dss_inner_clk_pdp_enable(hisifd, false);
		} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
			dss_inner_clk_sdp_enable(hisifd);
		} else {
			;
		}

		dpe_init(hisifd, false);

		ret = panel_next_lp_ctrl(pdev, lp_enter);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int dpe_remove(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = panel_next_remove(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int dpe_set_backlight(struct platform_device *pdev, uint32_t bl_level)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	HISI_FB_DEBUG("fb%d, bl_level=%d.\n", hisifd->index, bl_level);

	if (pinfo->bl_max < 1) {
		HISI_FB_ERR("bl_max(%d) is out of range!!", pinfo->bl_max);
		return -EINVAL;
	}

	if (bl_level > pinfo->bl_max) {
		bl_level = pinfo->bl_max;
	}

	if (bl_level < pinfo->bl_min && bl_level) {
		bl_level = pinfo->bl_min;
	}

	ret = panel_next_set_backlight(pdev, bl_level);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

#ifdef CONFIG_HISI_FB_3660
static int dpe_sbl_ctrl(struct platform_device *pdev, int enable)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *sbl_base = NULL;
	char __iomem *dpp_base = NULL;

	if (pdev == NULL) {
		return;
	}
	hisifd = platform_get_drvdata(pdev);
	if (hisifd == NULL) {
		return;
	}
	sbl_base = hisifd->dss_base + DSS_DPP_SBL_OFFSET;
	dpp_base = hisifd->dss_base + DSS_DPP_OFFSET;

	if (hisifd->panel_info.sbl_support == 0) {
		HISI_FB_INFO("fb%d not support SBL !\n", hisifd->index);
		return 0;
	}

	if (!HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_SBL)) {
		HISI_FB_INFO("fb%d not support SBL!, DPP_MODULE_SBL=%d\n", hisifd->index, DPP_MODULE_SBL);
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	set_reg(sbl_base + SBL_REG_CALC_BACKLIGHT_7_TO_0, hisifd->sbl.sbl_backlight_l, 8, 0);
	set_reg(sbl_base + SBL_REG_CALC_BACKLIGHT_15_TO_8, hisifd->sbl.sbl_backlight_h, 8, 0);
	set_reg(sbl_base + SBL_REG_CALC_AMBIENT_LIGHT_7_TO_0, hisifd->sbl.sbl_ambient_light_l, 8, 0);
	set_reg(sbl_base + SBL_REG_CALC_AMBIENT_LIGHT_15_TO_8, hisifd->sbl.sbl_ambient_light_h, 8, 0);
	set_reg(dpp_base + DPP_SBL, hisifd->sbl.sbl_enable, 1, 0);

	ret = panel_next_sbl_ctrl(pdev, enable);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}
#else
static int dpe_sbl_ctrl(struct platform_device *pdev, int enable)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	char __iomem *sbl_base = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	sbl_base = hisifd->dss_base + DSS_DPP_SBL_OFFSET;

	if (hisifd->panel_info.sbl_support == 0) {
		HISI_FB_INFO("fb%d not support SBL!\n", hisifd->index);
		return 0;
	}

	if (!HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_SBL)) {
		HISI_FB_INFO("fb%d not support SBL!, DPP_MODULE_SBL=%d\n", hisifd->index, DPP_MODULE_SBL);
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	set_reg(sbl_base + SBL_BACKLIGHT_L, hisifd->sbl.sbl_backlight_l, 8, 0);
	set_reg(sbl_base + SBL_BACKLIGHT_H, hisifd->sbl.sbl_backlight_h, 8, 0);
	set_reg(sbl_base + SBL_AMBIENT_LIGHT_L, hisifd->sbl.sbl_ambient_light_l, 8, 0);
	set_reg(sbl_base + SBL_AMBIENT_LIGHT_H, hisifd->sbl.sbl_ambient_light_h, 8, 0);
#ifndef NEW_SBL_CTRL
	set_reg(sbl_base + SBL_CALIBRATION_A_L, hisifd->sbl.sbl_calibration_a_l, 8, 0);
	set_reg(sbl_base + SBL_CALIBRATION_A_H, hisifd->sbl.sbl_calibration_a_h, 8, 0);
	set_reg(sbl_base + SBL_CALIBRATION_B_L, hisifd->sbl.sbl_calibration_b_l, 8, 0);
	set_reg(sbl_base + SBL_CALIBRATION_B_H, hisifd->sbl.sbl_calibration_b_h, 8, 0);
	set_reg(sbl_base + SBL_CALIBRATION_C_L, hisifd->sbl.sbl_calibration_c_l, 8, 0);
	set_reg(sbl_base + SBL_CALIBRATION_C_H, hisifd->sbl.sbl_calibration_c_h, 8, 0);
	set_reg(sbl_base + SBL_CALIBRATION_D_L, hisifd->sbl.sbl_calibration_d_l, 8, 0);
	set_reg(sbl_base + SBL_CALIBRATION_D_H, hisifd->sbl.sbl_calibration_d_h, 8, 0);
#endif
	set_reg(sbl_base + SBL_ENABLE, hisifd->sbl.sbl_enable, 1, 0);

	ret = panel_next_sbl_ctrl(pdev, enable);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}
#endif

static int dpe_vsync_ctrl(struct platform_device *pdev, int enable)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (enable) {
		ret = panel_next_vsync_ctrl(pdev, enable);
		if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_ISR_OFF) {
			dpe_interrupt_mask(hisifd);
			dpe_interrupt_clear(hisifd);
			dpe_irq_enable(hisifd);
			dpe_interrupt_unmask(hisifd);
		}
	} else {
		ret = panel_next_vsync_ctrl(pdev, enable);
		if (hisifd->panel_info.vsync_ctrl_type & VSYNC_CTRL_ISR_OFF) {
			dpe_interrupt_mask(hisifd);
			dpe_interrupt_clear(hisifd);
			dpe_irq_disable_nosync(hisifd);
		}
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int dpe_frc_handle(struct platform_device *pdev, int fps)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = panel_next_frc_handle(pdev, fps);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int dpe_esd_handle(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = panel_next_esd_handle(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static int dpe_set_display_region(struct platform_device *pdev,
	struct dss_rect *dirty)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL || dirty == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("index=%d, enter!\n", hisifd->index);

	ret = panel_next_set_display_region(pdev, dirty);

	HISI_FB_DEBUG("index=%d, exit!\n", hisifd->index);

	return ret;
}

static int dpe_get_lcd_id(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	return panel_next_get_lcd_id(pdev);
}

static int dpe_set_pixclk_rate(struct platform_device *pdev)
{
	char __iomem *ldi_base = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	struct dss_clk_rate *pdss_clk_rate = NULL;
	int ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);
	pdss_clk_rate = get_dss_clk_rate(hisifd);
	BUG_ON(pdss_clk_rate == NULL);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		ldi_base = hisifd->dss_base+ DSS_LDI0_OFFSET;

		if (IS_ERR(hisifd->dss_pxl0_clk)) {
			ret = PTR_ERR(hisifd->dss_pxl0_clk);
			return ret;
		}

		ret = clk_set_rate(hisifd->dss_pxl0_clk, pinfo->pxl_clk_rate);
		if (ret < 0) {
			HISI_FB_ERR("fb%d dss_pxl1_clk clk_set_rate(%llu) failed, error=%d!\n",
				hisifd->index, pinfo->pxl_clk_rate, ret);
			return -EINVAL;
		}

		HISI_FB_INFO("dss_pxl1_clk:[%llu]->[%llu].\n",
			pinfo->pxl_clk_rate, (uint64_t)clk_get_rate(hisifd->dss_pxl0_clk));
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		ldi_base = hisifd->dss_base+ DSS_LDI1_OFFSET;

		if (IS_ERR(hisifd->dss_pxl1_clk)) {
			ret = PTR_ERR(hisifd->dss_pxl1_clk);
			return ret;
		}

		ret = clk_set_rate(hisifd->dss_pxl1_clk, pinfo->pxl_clk_rate);
		if (ret < 0) {
			HISI_FB_ERR("fb%d dss_pxl1_clk clk_set_rate(%llu) failed, error=%d!\n",
				hisifd->index, pinfo->pxl_clk_rate, ret);
			return -EINVAL;
		}

		HISI_FB_INFO("dss_pxl1_clk:[%llu]->[%llu].\n",
			pinfo->pxl_clk_rate, (uint64_t)clk_get_rate(hisifd->dss_pxl1_clk));
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return -EINVAL;
	}

	init_dbuf(hisifd);

	if (is_mipi_video_panel(hisifd)) {
		outp32(ldi_base + LDI_DPI0_HRZ_CTRL0,
				pinfo->ldi.h_front_porch | ((pinfo->ldi.h_back_porch + DSS_WIDTH(pinfo->ldi.h_pulse_width)) << 16));
		outp32(ldi_base + LDI_DPI0_HRZ_CTRL1, 0);
		outp32(ldi_base + LDI_DPI0_HRZ_CTRL2, DSS_WIDTH(pinfo->xres));
	} else {
		outp32(ldi_base + LDI_DPI0_HRZ_CTRL0,
			pinfo->ldi.h_front_porch | (pinfo->ldi.h_back_porch << 16));
		outp32(ldi_base + LDI_DPI0_HRZ_CTRL1, DSS_WIDTH(pinfo->ldi.h_pulse_width));
		outp32(ldi_base + LDI_DPI0_HRZ_CTRL2, DSS_WIDTH(pinfo->xres));
	}
	outp32(ldi_base + LDI_VRT_CTRL0,
		pinfo->ldi.v_front_porch | (pinfo->ldi.v_back_porch << 16));
	outp32(ldi_base + LDI_VRT_CTRL1, DSS_HEIGHT(pinfo->ldi.v_pulse_width));
	outp32(ldi_base + LDI_VRT_CTRL2, DSS_HEIGHT(pinfo->yres));

	outp32(ldi_base + LDI_PLR_CTRL,
		pinfo->ldi.vsync_plr | (pinfo->ldi.hsync_plr << 1) |
		(pinfo->ldi.pixelclk_plr << 2) | (pinfo->ldi.data_en_plr << 3));

	return 0;
}

static ssize_t dpe_lcd_model_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_model_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_check_reg_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_check_reg(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_mipi_detect_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_mipi_detect(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_hkadc_debug_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_hkadc_debug_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_hkadc_debug_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_hkadc_debug_store(pdev, buf, count);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_gram_check_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_gram_check_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_gram_check_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_gram_check_store(pdev, buf, count);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_dynamic_sram_checksum_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_dynamic_sram_checksum_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_dynamic_sram_checksum_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_dynamic_sram_checksum_store(pdev, buf, count);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}


static ssize_t dpe_lcd_color_temperature_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = dpe_show_ct_cscValue(hisifd, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);
	return ret;
}

static ssize_t dpe_lcd_color_temperature_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t flag = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	unsigned int csc_value[100];
	char *cur;
	char *token;
	int i = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	cur = (char*)buf;
	token = strsep(&cur, ",");
	while (token) {
		csc_value[i++] = simple_strtol(token, NULL, 0);
		token = strsep(&cur, ",");
	}

	if (pinfo->xcc_support) {
		dpe_store_ct_cscValue(hisifd, csc_value);
		flag = dpe_set_ct_cscValue(hisifd);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

static ssize_t dpe_lcd_ic_color_enhancement_mode_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_ic_color_enhancement_mode_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_ic_color_enhancement_mode_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}
	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_ic_color_enhancement_mode_store(pdev, buf, count);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_led_rg_lcd_color_temperature_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = dpe_show_led_rg_ct_cscValue(buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);
	return ret;
}

static ssize_t dpe_led_rg_lcd_color_temperature_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t flag = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	unsigned int csc_value[100];
	char *token, *cur;
	int i = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	cur = (char*)buf;
	token = strsep(&cur, ",");
	while (token) {
		csc_value[i++] = simple_strtol(token, NULL, 0);
		token = strsep(&cur, ",");
	}

	if (pinfo->color_temperature_support) {
		dpe_store_led_rg_ct_cscValue(csc_value);
		flag = dpe_set_led_rg_ct_cscValue(hisifd);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

static ssize_t dpe_lcd_comform_mode_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = dpe_show_comform_ct_cscValue(hisifd, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);
	return ret;
}

static ssize_t dpe_lcd_comform_mode_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t flag = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	unsigned int val = 0;
	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (pinfo->comform_mode_support) {
		val = simple_strtoul(buf, NULL, 0);
		if(val <= COMFORM_MAX){
			HISI_FB_INFO("comform_mode = %d !\n", val);
			dpe_update_g_comform_discount(val);
			flag = dpe_set_comform_ct_cscValue(hisifd);
		}else{
			HISI_FB_ERR("comform_mode = %d, not support this level!\n", val);
		}
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}

#ifdef CONFIG_HISI_FB_3650
static ssize_t dpe_lcd_cinema_mode_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = dpe_show_cinema_value(buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);
	return ret;
}

static ssize_t dpe_lcd_cinema_mode_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	unsigned int val = 0;
	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (pinfo->cinema_mode_support) {
		val = simple_strtoul(buf, NULL, 0);
		if(1 == val || 0 == val){
			HISI_FB_INFO("cinema_mode = %d !\n", val);
			dpe_set_cinema(hisifd,val);
		}else{
			HISI_FB_ERR("cinema_mode = %d, not support this value!\n", val);
		}
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}
#endif

static ssize_t dpe_lcd_support_mode_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_support_mode_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_support_mode_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_support_mode_store(pdev, buf, count);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_voltage_enable_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_voltage_enable_store(pdev, buf, count);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_bist_check(struct platform_device *pdev,
	char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_bist_check(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_sleep_ctrl_show(struct platform_device *pdev,
	char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_sleep_ctrl_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_sleep_ctrl_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_sleep_ctrl_store(pdev, buf, count);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_test_config_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_test_config_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_test_config_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_test_config_store(pdev, buf, count);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_support_checkmode_show(struct platform_device *pdev,
	char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_support_checkmode_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_lp2hs_mipi_check_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_lp2hs_mipi_check_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_lp2hs_mipi_check_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_lp2hs_mipi_check_store(pdev, buf, count);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_amoled_pcd_errflag_check(struct platform_device *pdev,
	char *buf)
{
	ssize_t ret = 0;
    ret = panel_next_amoled_pcd_errflag_check(pdev, buf);
	return ret;
}
static ssize_t dpe_lcd_hbm_ctrl_store(struct platform_device *pdev, const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_hbm_ctrl_store(pdev, buf, count);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_hbm_ctrl_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_hbm_ctrl_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_acl_ctrl_store(struct platform_device *pdev, const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	if (NULL == buf) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_acl_ctrl_store(pdev, buf, count);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_lcd_acl_ctrl_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	if (NULL == buf) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_lcd_acl_ctrl_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_acm_state_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	if (NULL == buf) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = dpe_show_acm_state(buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);
	return ret;
}
static ssize_t dpe_acm_state_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	unsigned int val = 0;

	if (NULL == pdev) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	if (NULL == buf) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	hisifd = platform_get_drvdata(pdev);
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	pinfo = &(hisifd->panel_info);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (pinfo->acm_support) {
		val = simple_strtoul(buf, NULL, 0);
		dpe_update_g_acm_state(val);
		dpe_set_acm_state(hisifd);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return count;
}


static ssize_t dpe_sharpness2d_table_store(struct platform_device *pdev, const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_sharpness2d_table_store(pdev, buf, count);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}
static ssize_t dpe_sharpness2d_table_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_sharpness2d_table_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_panel_info_show(struct platform_device *pdev, char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_panel_info_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_mipi_dsi_bit_clk_upt_show(struct platform_device *pdev,
	char *buf)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_mipi_dsi_bit_clk_upt_show(pdev, buf);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static ssize_t dpe_mipi_dsi_bit_clk_upt_store(struct platform_device *pdev,
	const char *buf, size_t count)
{
	ssize_t ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);
	ret = panel_next_mipi_dsi_bit_clk_upt_store(pdev, buf, count);
	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

/*******************************************************************************
**
*/
/*only for hi6250 mmbuf asc test */
#define MMBUF_ASC_INT_STATUS	(0x120)
#define MMBUF_ASC_INT_CLEAR		(0x124)
irqreturn_t dss_mmbuf_asc0_isr(int irq, void *ptr)
{
	struct hisi_fb_data_type *hisifd = NULL;
	uint32_t isr_flag = 0;

	hisifd = (struct hisi_fb_data_type *)ptr;
	BUG_ON(hisifd == NULL);

	if (hisifd->mmbuf_asc0_base) {
		isr_flag = inp32(hisifd->mmbuf_asc0_base + MMBUF_ASC_INT_STATUS);
		HISI_FB_ERR("mmbuf access error!!!< irq: %d flag: %d  >\n", irq, isr_flag);

		outp32(hisifd->dss_base + DSS_RCH_D0_DMA_OFFSET + CH_SECU_EN, 0x1);
		outp32(hisifd->dss_base + DSS_RCH_D1_DMA_OFFSET + CH_SECU_EN, 0x1);
		outp32(hisifd->dss_base + DSS_RCH_D2_DMA_OFFSET + CH_SECU_EN, 0x1);
		outp32(hisifd->dss_base + DSS_RCH_D3_DMA_OFFSET + CH_SECU_EN, 0x1);
		outp32(hisifd->dss_base + DSS_RCH_G1_DMA_OFFSET + CH_SECU_EN, 0x1);
		outp32(hisifd->dss_base + DSS_RCH_VG1_DMA_OFFSET + CH_SECU_EN, 0x1);

		outp32(hisifd->mmbuf_asc0_base + MMBUF_ASC_INT_CLEAR, isr_flag);
	}
	return IRQ_HANDLED;
}

static int dpe_regulator_clk_irq_setup(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;
	struct dss_clk_rate *pdss_clk_rate = NULL;
	const char *irq_name = NULL;
	irqreturn_t (*isr_fnc)(int irq, void *ptr);
	int ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);
	pdss_clk_rate = get_dss_clk_rate(hisifd);
	BUG_ON(pdss_clk_rate == NULL);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		irq_name = IRQ_PDP_NAME;
		isr_fnc = dss_pdp_isr;
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		irq_name = IRQ_SDP_NAME;
		isr_fnc = dss_sdp_isr;
	} else if (hisifd->index == AUXILIARY_PANEL_IDX) {
		irq_name = IRQ_ADP_NAME;
		isr_fnc = dss_adp_isr;
	} else {
		HISI_FB_ERR("fb%d, not support this device!\n", hisifd->index);
		return -EINVAL;
	}

#ifdef CONFIG_DSS_MMBUF_CLK_USED
	hisifd->dss_mmbuf_clk = devm_clk_get(&pdev->dev, hisifd->dss_mmbuf_clk_name);
	if (IS_ERR(hisifd->dss_mmbuf_clk)) {
		ret = PTR_ERR(hisifd->dss_mmbuf_clk);
		HISI_FB_ERR("dss_mmbuf_clk error, ret = %d", ret);
		return ret;
	}

	hisifd->dss_pclk_mmbuf_clk = devm_clk_get(&pdev->dev, hisifd->dss_pclk_mmbuf_name);
	if (IS_ERR(hisifd->dss_pclk_mmbuf_clk)) {
		ret = PTR_ERR(hisifd->dss_pclk_mmbuf_clk);
		HISI_FB_ERR("dss_pclk_mmbuf_clk error, ret = %d", ret);
		return ret;
	}
#endif

	hisifd->dss_axi_clk = devm_clk_get(&pdev->dev, hisifd->dss_axi_clk_name);
	if (IS_ERR(hisifd->dss_axi_clk)) {
		ret = PTR_ERR(hisifd->dss_axi_clk);
		HISI_FB_ERR("dss_axi_clk error, ret = %d", ret);
		return ret;
	}

	hisifd->dss_pclk_dss_clk = devm_clk_get(&pdev->dev, hisifd->dss_pclk_dss_name);
	if (IS_ERR(hisifd->dss_pclk_dss_clk)) {
		ret = PTR_ERR(hisifd->dss_pclk_dss_clk);
		HISI_FB_ERR("dss_pclk_dss_clk error, ret = %d", ret);
		return ret;
	} else {
		ret = clk_set_rate(hisifd->dss_pclk_dss_clk, pdss_clk_rate->dss_pclk_dss_rate);
		if (ret < 0) {
			HISI_FB_ERR("fb%d dss_pclk_dss_clk clk_set_rate(%llu) failed, error=%d!\n",
				hisifd->index, pdss_clk_rate->dss_pclk_dss_rate, ret);
			return -EINVAL;
		}

		HISI_FB_INFO("dss_pclk_dss_clk:[%llu]->[%llu].\n",
			pdss_clk_rate->dss_pclk_dss_rate, (uint64_t)clk_get_rate(hisifd->dss_pclk_dss_clk));
	}

	hisifd->dss_pri_clk = devm_clk_get(&pdev->dev, hisifd->dss_pri_clk_name);
	if (IS_ERR(hisifd->dss_pri_clk)) {
		ret = PTR_ERR(hisifd->dss_pri_clk);
		HISI_FB_ERR("dss_pri_clk error, ret = %d", ret);
		return ret;
	} else {
		ret = clk_set_rate(hisifd->dss_pri_clk, pdss_clk_rate->dss_pri_clk_rate);
		if (ret < 0) {
			HISI_FB_ERR("fb%d dss_pri_clk clk_set_rate(%llu) failed, error=%d!\n",
				hisifd->index, pdss_clk_rate->dss_pri_clk_rate, ret);
			return -EINVAL;
		}

		HISI_FB_INFO("dss_pri_clk:[%llu]->[%llu].\n",
			pdss_clk_rate->dss_pri_clk_rate, (uint64_t)clk_get_rate(hisifd->dss_pri_clk));
	}

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		hisifd->dss_pxl0_clk = devm_clk_get(&pdev->dev, hisifd->dss_pxl0_clk_name);
		if (IS_ERR(hisifd->dss_pxl0_clk)) {
			ret = PTR_ERR(hisifd->dss_pxl0_clk);
			HISI_FB_ERR("dss_pxl0_clk error, ret = %d", ret);
			return ret;
		} else {
			if (pinfo->pxl_clk_rate == 313600000) {  //PLL3
				pinfo->pxl_clk_rate = 320 * 1000000UL;
			}

			ret = clk_set_rate(hisifd->dss_pxl0_clk, pinfo->pxl_clk_rate);
			if (ret < 0) {
				HISI_FB_ERR("fb%d dss_pxl0_clk clk_set_rate(%llu) failed, error=%d!\n",
					hisifd->index, pinfo->pxl_clk_rate, ret);
				if (g_fpga_flag == 0)
					return -EINVAL;
			}

			HISI_FB_INFO("dss_pxl0_clk:[%llu]->[%llu].\n",
				pinfo->pxl_clk_rate, (uint64_t)clk_get_rate(hisifd->dss_pxl0_clk));
		}
	} else if ((hisifd->index == EXTERNAL_PANEL_IDX) && !hisifd->panel_info.fake_hdmi) {
		hisifd->dss_pxl1_clk = devm_clk_get(&pdev->dev, hisifd->dss_pxl1_clk_name);
		if (IS_ERR(hisifd->dss_pxl1_clk)) {
			ret = PTR_ERR(hisifd->dss_pxl1_clk);
			HISI_FB_ERR("dss_pxl1_clk error, ret = %d, hisifd->dss_pxl1_clk_name=%s, hisifd->panel_info.fake_hdmi=%d", ret, hisifd->dss_pxl1_clk_name, hisifd->panel_info.fake_hdmi);
			return ret;
		} else {
			ret = clk_set_rate(hisifd->dss_pxl1_clk, pinfo->pxl_clk_rate);
			if (ret < 0) {
				HISI_FB_ERR("fb%d dss_pxl1_clk clk_set_rate(%llu) failed, error=%d!\n",
					hisifd->index, pinfo->pxl_clk_rate, ret);

				if (g_fpga_flag == 0)
					return -EINVAL;
			}

			HISI_FB_INFO("dss_pxl1_clk:[%llu]->[%llu].\n",
				pinfo->pxl_clk_rate, (uint64_t)clk_get_rate(hisifd->dss_pxl1_clk));
		}
	} else {
		;
	}

	if (hisifd->dpe_irq) {
		ret = request_irq(hisifd->dpe_irq, isr_fnc, IRQF_DISABLED, irq_name, (void *)hisifd);
		if (ret != 0) {
			HISI_FB_ERR("fb%d request_irq failed, irq_no=%d error=%d!\n", hisifd->index, hisifd->dpe_irq, ret);
			return ret;
		} else {
			disable_irq(hisifd->dpe_irq);
		}
	}

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		if (hisifd->mmbuf_asc0_irq) {
			ret = request_irq(hisifd->mmbuf_asc0_irq, dss_mmbuf_asc0_isr, IRQF_DISABLED, "irq_mmbuf_asc0", (void *)hisifd);
			if (ret != 0) {
				HISI_FB_ERR("fb%d request_irq failed, irq_no=%d error=%d!\n", hisifd->index, hisifd->mmbuf_asc0_irq, ret);
				return ret;
			} else {
				disable_irq(hisifd->mmbuf_asc0_irq);
			}
		}
	}

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		if (is_fastboot_display_enable()) {
			dpe_regulator_enable(hisifd);
		}
	}

	//hisi_irqaffinity_register(hisifd->dpe_irq, 1);

	return 0;
}

static int dpe_probe(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct platform_device *hisi_fb_dev = NULL;
	struct hisi_fb_panel_data *pdata = NULL;
	struct fb_info *fbi = NULL;
	int ret = 0;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	ret = dpe_regulator_clk_irq_setup(pdev);
	if (ret) {
		HISI_FB_ERR("fb%d dpe_irq_clk_setup failed, error=%d!\n", hisifd->index, ret);
		goto err;
	}

	/* alloc device */
	hisi_fb_dev = platform_device_alloc(DEV_NAME_FB, pdev->id);
	if (!hisi_fb_dev) {
		HISI_FB_ERR("fb%d platform_device_alloc failed, error=%d!\n", hisifd->index, ret);
		ret = -ENOMEM;
		goto err_device_alloc;
	}

	/* link to the latest pdev */
	hisifd->pdev = hisi_fb_dev;

	/* alloc panel device data */
	ret = platform_device_add_data(hisi_fb_dev, dev_get_platdata(&pdev->dev),
		sizeof(struct hisi_fb_panel_data));
	if (ret) {
		HISI_FB_ERR("fb%d platform_device_add_data failed, error=%d!\n", hisifd->index, ret);
		goto err_device_put;
	}

	/* data chain */
	pdata = dev_get_platdata(&hisi_fb_dev->dev);
	pdata->set_fastboot = dpe_set_fastboot;
	pdata->on = dpe_on;
	pdata->off = dpe_off;
	pdata->lp_ctrl = dpe_lp_ctrl;
	pdata->remove = dpe_remove;
	pdata->set_backlight = dpe_set_backlight;
	pdata->sbl_ctrl = dpe_sbl_ctrl;
	pdata->vsync_ctrl = dpe_vsync_ctrl;
	pdata->frc_handle = dpe_frc_handle;
	pdata->esd_handle = dpe_esd_handle;
	pdata->set_display_region = dpe_set_display_region;
	pdata->set_pixclk_rate = dpe_set_pixclk_rate;
	pdata->lcd_model_show = dpe_lcd_model_show;
	pdata->lcd_check_reg = dpe_lcd_check_reg_show;
	pdata->lcd_mipi_detect = dpe_lcd_mipi_detect_show;
	pdata->lcd_hkadc_debug_show = dpe_lcd_hkadc_debug_show;
	pdata->lcd_hkadc_debug_store = dpe_lcd_hkadc_debug_store;
	pdata->lcd_gram_check_show = dpe_lcd_gram_check_show;
	pdata->lcd_gram_check_store = dpe_lcd_gram_check_store;
	pdata->lcd_dynamic_sram_checksum_show = dpe_lcd_dynamic_sram_checksum_show;
	pdata->lcd_dynamic_sram_checksum_store = dpe_lcd_dynamic_sram_checksum_store;
	pdata->lcd_color_temperature_show = dpe_lcd_color_temperature_show;
	pdata->lcd_color_temperature_store = dpe_lcd_color_temperature_store;
	pdata->lcd_ic_color_enhancement_mode_show = dpe_lcd_ic_color_enhancement_mode_show;
	pdata->lcd_ic_color_enhancement_mode_store = dpe_lcd_ic_color_enhancement_mode_store;
	pdata->led_rg_lcd_color_temperature_show = dpe_led_rg_lcd_color_temperature_show;
	pdata->led_rg_lcd_color_temperature_store = dpe_led_rg_lcd_color_temperature_store;
	pdata->lcd_comform_mode_show = dpe_lcd_comform_mode_show;
	pdata->lcd_comform_mode_store = dpe_lcd_comform_mode_store;
#ifdef CONFIG_HISI_FB_3650
	pdata->lcd_cinema_mode_show = dpe_lcd_cinema_mode_show;
	pdata->lcd_cinema_mode_store = dpe_lcd_cinema_mode_store;
#endif
	pdata->lcd_support_mode_show = dpe_lcd_support_mode_show;
	pdata->lcd_support_mode_store = dpe_lcd_support_mode_store;
	pdata->lcd_voltage_enable_store = dpe_lcd_voltage_enable_store;
	pdata->lcd_bist_check = dpe_lcd_bist_check;
	pdata->mipi_dsi_bit_clk_upt_show = dpe_mipi_dsi_bit_clk_upt_show;
	pdata->mipi_dsi_bit_clk_upt_store = dpe_mipi_dsi_bit_clk_upt_store;
	pdata->lcd_sleep_ctrl_show = dpe_lcd_sleep_ctrl_show;
	pdata->lcd_sleep_ctrl_store = dpe_lcd_sleep_ctrl_store;
	pdata->lcd_test_config_show = dpe_lcd_test_config_show;
	pdata->lcd_test_config_store = dpe_lcd_test_config_store;
	pdata->lcd_support_checkmode_show = dpe_lcd_support_checkmode_show;
	pdata->lcd_lp2hs_mipi_check_show = dpe_lcd_lp2hs_mipi_check_show;
	pdata->lcd_lp2hs_mipi_check_store = dpe_lcd_lp2hs_mipi_check_store;
	pdata->amoled_pcd_errflag_check = dpe_amoled_pcd_errflag_check;
	pdata->sharpness2d_table_store = dpe_sharpness2d_table_store;
	pdata->sharpness2d_table_show = dpe_sharpness2d_table_show;
	pdata->panel_info_show = dpe_panel_info_show;
	pdata->lcd_hbm_ctrl_show = dpe_lcd_hbm_ctrl_show;
	pdata->lcd_hbm_ctrl_store = dpe_lcd_hbm_ctrl_store;
	pdata->lcd_acm_state_show = dpe_acm_state_show;
	pdata->lcd_acm_state_store = dpe_acm_state_store;
	pdata->lcd_acl_ctrl_show = dpe_lcd_acl_ctrl_show;
	pdata->lcd_acl_ctrl_store = dpe_lcd_acl_ctrl_store;
	pdata->get_lcd_id = dpe_get_lcd_id;
	pdata->next = pdev;

	/* get/set panel info */
	memcpy(&hisifd->panel_info, pdata->panel_info, sizeof(struct hisi_panel_info));

	fbi = hisifd->fbi;
	fbi->var.pixclock = hisifd->panel_info.pxl_clk_rate;
	/*fbi->var.pixclock = clk_round_rate(hisifd->dpe_clk, hisifd->panel_info.pxl_clk_rate);*/
	fbi->var.left_margin = hisifd->panel_info.ldi.h_back_porch;
	fbi->var.right_margin = hisifd->panel_info.ldi.h_front_porch;
	fbi->var.upper_margin = hisifd->panel_info.ldi.v_back_porch;
	fbi->var.lower_margin = hisifd->panel_info.ldi.v_front_porch;
	fbi->var.hsync_len = hisifd->panel_info.ldi.h_pulse_width;
	fbi->var.vsync_len = hisifd->panel_info.ldi.v_pulse_width;

	hisifd->vsync_ctrl_type = hisifd->panel_info.vsync_ctrl_type;

	/* set driver data */
	platform_set_drvdata(hisi_fb_dev, hisifd);
	ret = platform_device_add(hisi_fb_dev);
	if (ret) {
		HISI_FB_ERR("fb%d platform_device_add failed, error=%d!\n", hisifd->index, ret);
		goto err_device_put;
	}

	dpe_init_led_rg_ct_cscValue();

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;

err_device_put:
	platform_device_put(hisi_fb_dev);
err_device_alloc:
err:
	return ret;
}

static struct platform_driver this_driver = {
	.probe = dpe_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = DEV_NAME_DSS_DPE,
	},
};

static int __init dpe_driver_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		HISI_FB_ERR("platform_driver_register failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(dpe_driver_init);
