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

#include "hisi_dpe_utils.h"
#include "hisi_overlay_utils.h"
#include "hisi_cfg_sbl.h"

DEFINE_SEMAPHORE(hisi_fb_dss_inner_clk_sem);
static int dss_inner_clk_refcount = 0;
static unsigned  int g_comform_value = 0;
static unsigned  int g_acm_State = 0;
static unsigned  int g_cinema_value = 0;
static unsigned int g_led_rg_csc_value[9];
static unsigned int g_is_led_rg_csc_set;
unsigned int g_led_rg_para1 = 7;
unsigned int g_led_rg_para2 = 30983;
#define OFFSET_FRACTIONAL_BITS	(11)
#define ROUND1(x,y)	((x) / (y) + ((x) % (y)  ? 1 : 0))
static  uint32_t sbl_al_calib_lut[33] = {0,768,2048,3072,4091,5120,6140,7183,8192,
                                         9216,10240,11264,24576,26624,28672,30720,32768,
                                         34815,36863,38911,40959,43007,45055,47103,49151,
                                         51199,53247,55295,57343,59391,61439,63487,65535};
#ifdef NEW_SBL_CTRL
static uint32_t bl_linearity_lut[33] = {0, 128, 256, 384, 512, 640, 768, 896, 1024, 1152, 1280,
                                               1408, 1536, 1664, 1792, 1920, 2048, 2176, 2304, 2432, 2560, 2688,
                                               2816, 2944, 3072, 3200, 3328, 3456, 3584, 3712, 3840, 3968, 4096};

static uint32_t bl_att_lut[33] = {0, 128, 256, 384, 470, 559, 618, 665, 706, 745, 785,
                                       826, 872, 924, 982, 1047, 1118, 1198, 1285, 1382, 1490, 1608,
                                       1738, 1881, 2039, 2213, 2405, 2618, 2853, 3115, 3406, 3731, 4095};

static uint32_t bl_linearity_inverse_lut[33] = {0, 128, 256, 384, 512, 640, 768, 896, 1024, 1152, 1280,
                                               1408, 1536, 1664, 1792, 1920, 2048, 2176, 2304, 2432, 2560, 2688,
                                               2816, 2944, 3072, 3200, 3328, 3456, 3584, 3712, 3840, 3968, 4096};
#endif


struct dss_clk_rate * get_dss_clk_rate(struct hisi_fb_data_type *hisifd)
{
	struct hisi_panel_info *pinfo = NULL;
	struct dss_clk_rate *pdss_clk_rate = NULL;

	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);
	pdss_clk_rate = &(hisifd->dss_clk_rate);

	/* FIXME: TBD  */
	if (g_fpga_flag == 1) {
		if (pdss_clk_rate->dss_pclk_dss_rate == 0) {
			pdss_clk_rate->dss_pri_clk_rate = 40 * 1000000UL;
			pdss_clk_rate->dss_pclk_dss_rate = 20 * 1000000UL;
			pdss_clk_rate->dss_pclk_pctrl_rate = 20 * 1000000UL;
		}
	} else {
		if (pdss_clk_rate->dss_pclk_dss_rate == 0) {
			if ((pinfo->xres * pinfo->yres) >= (2560 * 1600)) {
				pdss_clk_rate->dss_pri_clk_rate = DEFAULT_DSS_CORE_CLK_RATE;
				pdss_clk_rate->dss_pclk_dss_rate = DEFAULT_PCLK_DSS_RATE;
				pdss_clk_rate->dss_pclk_pctrl_rate = DEFAULT_PCLK_PCTRL_RATE;
			} else if ((pinfo->xres * pinfo->yres) >= (1920 * 1080)) {
				pdss_clk_rate->dss_pri_clk_rate = DEFAULT_DSS_CORE_CLK_RATE;
				pdss_clk_rate->dss_pclk_dss_rate = DEFAULT_PCLK_DSS_RATE;
				pdss_clk_rate->dss_pclk_pctrl_rate = DEFAULT_PCLK_PCTRL_RATE;
			} else if ((pinfo->xres * pinfo->yres) >= (1280 * 720)) {
				pdss_clk_rate->dss_pri_clk_rate = DEFAULT_DSS_CORE_CLK_RATE;
				pdss_clk_rate->dss_pclk_dss_rate = DEFAULT_PCLK_DSS_RATE;
				pdss_clk_rate->dss_pclk_pctrl_rate = DEFAULT_PCLK_PCTRL_RATE;
			} else {
				pdss_clk_rate->dss_pri_clk_rate = DEFAULT_DSS_CORE_CLK_RATE;
				pdss_clk_rate->dss_pclk_dss_rate = DEFAULT_PCLK_DSS_RATE;
				pdss_clk_rate->dss_pclk_pctrl_rate = DEFAULT_PCLK_PCTRL_RATE;
			}
		}
	}

	return pdss_clk_rate;
}

int set_dss_clk_rate(struct hisi_fb_data_type *hisifd)
{
	int ret = 0;

	BUG_ON(hisifd == NULL);


	return ret;
}

void dss_inner_clk_common_enable(struct hisi_fb_data_type *hisifd, bool fastboot_enable)
{
	char __iomem *dss_base = NULL;
	int prev_refcount = 0;

	BUG_ON(hisifd == NULL);

	dss_base = hisifd->dss_base;

	down(&hisi_fb_dss_inner_clk_sem);

	prev_refcount = dss_inner_clk_refcount++;
	if (!prev_refcount && !fastboot_enable) {
		//gt_clk_dis_edc0/ldi0/ldi1/aclk/pclk
		//outp32(hisifd->peri_crg_base + PERDIS3, 0x0002C000);
		//gt_clk_mmbuf_dss
		//outp32(hisifd->sctrl_base + SCPERDIS1, 0x01000000);

		//gt_pclk_dss_enable
		//outp32(hisifd->peri_crg_base + PEREN3, 0x00001000);

	#ifdef CONFIG_DSS_LP_USED
		//first DSS LP
		//outp32(dss_base + GLB_MODULE_CLK_SEL, 0xF0000008);
		//outp32(dss_base + GLB_MODULE1_CLK_SEL, 0x00000000);
		//outp32(dss_base + GLB_DSS_MEM_CTRL, 0x01A800A8);
		//outp32(dss_base + GLB_DSS_PM_CTRL, 0x00002009);
		outp32(dss_base + GLB_PXL0_DIV2_GT_EN, 0x00000001);
	#endif

		//All dss interrupts init mask
		//outp32(dss_base + GLB_MCU_ITF0_INT_MSK, 0x00003FFF);
		//outp32(dss_base + GLB_MCU_ITF1_INT_MSK, 0x00003FFF);
		outp32(dss_base + GLB_GLB_CPU_ITF0_INT_MSK, 0x00003FFF);
		outp32(dss_base + GLB_GLB_CPU_ITF1_INT_MSK, 0x00003FFF);
		outp32(dss_base + GLB_GLB_DPP_INT_MSK, 0x000000FF);
		outp32(dss_base + GLB_RCH_CE_INT_MSK, 0x0000000F);
		outp32(dss_base + GLB_DBG_MCTL_INT_MSK, 0x000000FF);
		outp32(dss_base + GLB_DBG_WCH0_INT_MSK, 0x00003FFF);
		outp32(dss_base + GLB_DBG_WCH1_INT_MSK, 0x00003FFF);
		outp32(dss_base + GLB_DBG_RCH0_INT_MSK, 0x3FFFFFFF);
		outp32(dss_base + GLB_DBG_RCH1_INT_MSK, 0x3FFFFFFF);
		outp32(dss_base + GLB_DBG_RCH2_INT_MSK, 0x3FFFFFFF);
		outp32(dss_base + GLB_DBG_RCH3_INT_MSK, 0x3FFFFFFF);
		outp32(dss_base + GLB_DBG_RCH4_INT_MSK, 0x3FFFFFFF);
		outp32(dss_base + GLB_DBG_RCH5_INT_MSK, 0x3FFFFFFF);
		outp32(dss_base + GLB_DBG_RCH6_INT_MSK, 0x3FFFFFFF);
		outp32(dss_base + GLB_DBG_RCH7_INT_MSK, 0x3FFFFFFF);
		outp32(dss_base + GLB_INT_MSK, 0x0000003F);
		//outp32(dss_base + GLB_MCU_PDP_INT_MSK, 0x7FFFFFFF);
		//outp32(dss_base + GLB_MCU_SDP_INT_MSK, 0x3FFFFFFF);
		//outp32(dss_base + GLB_MCU_OFF_INT_MSK, 0xFFFFFFFF);
		outp32(dss_base + GLB_CPU_PDP_INT_MSK, 0x7FFFFFFF);
		outp32(dss_base + GLB_CPU_SDP_INT_MSK, 0x3FFFFFFF);
		outp32(dss_base + GLB_CPU_OFF_INT_MSK, 0xFFFFFFFF);

		//gt_clk_enable_aclk
		//outp32(hisifd->peri_crg_base + PEREN3, 0x00002000);
		//gt_clk_mmbuf_dss
		//outp32(hisifd->sctrl_base + SCPEREN1, 0x01000000);

	#ifdef CONFIG_DSS_LP_USED
		//second DSS LP
		//cmd
		outp32(dss_base + DSS_CMDLIST_OFFSET + CMD_CLK_SEL, 0x00000000);
		//aif0
		outp32(dss_base + DSS_VBIF0_AIF + AIF_CLK_SEL0, 0x00000000);
		//aif0
		outp32(dss_base + DSS_VBIF0_AIF + AIF_CLK_SEL1, 0x00000000);
		//aif1
		outp32(dss_base + DSS_VBIF1_AIF + AIF_CLK_SEL0, 0x00000000);
		//aif1
		outp32(dss_base + DSS_VBIF1_AIF + AIF_CLK_SEL1, 0x00000000);
		//mmu
		outp32(dss_base + DSS_SMMU_OFFSET + SMMU_LP_CTRL, 0x00000001);
	#endif

		//gt_clk_enable_edc0
		//outp32(hisifd->peri_crg_base + PEREN3, 0x00020000);

	#ifdef CONFIG_DSS_LP_USED
		//third DSS LP
		//mif
		outp32(dss_base + DSS_MIF_OFFSET + MIF_CLK_CTL,  0x00000001);
		//mctl mutex0
		outp32(dss_base + DSS_MCTRL_CTL0_OFFSET + MCTL_CTL_CLK_SEL, 0x00000000);
		//mctl mutex1
		outp32(dss_base + DSS_MCTRL_CTL1_OFFSET + MCTL_CTL_CLK_SEL, 0x00000000);
		//mctl mutex2
		outp32(dss_base + DSS_MCTRL_CTL2_OFFSET + MCTL_CTL_CLK_SEL, 0x00000000);
		//mctl mutex3
		outp32(dss_base + DSS_MCTRL_CTL3_OFFSET + MCTL_CTL_CLK_SEL, 0x00000000);
		//mctl mutex4
		outp32(dss_base + DSS_MCTRL_CTL4_OFFSET + MCTL_CTL_CLK_SEL, 0x00000000);
		//mctl mutex5
		outp32(dss_base + DSS_MCTRL_CTL5_OFFSET + MCTL_CTL_CLK_SEL, 0x00000000);
		//mctl sys
		outp32(dss_base + DSS_MCTRL_SYS_OFFSET + MCTL_MCTL_CLK_SEL, 0x00000000);
		//mctl sys
		outp32(dss_base + DSS_MCTRL_SYS_OFFSET + MCTL_MOD_CLK_SEL, 0x00000000);
		//scf
		outp32(dss_base + DSS_POST_SCF_OFFSET + SCF_CLK_SEL, 0x00000000);
		//rch_v0
		outp32(dss_base + DSS_RCH_VG0_DMA_OFFSET + CH_CLK_SEL, 0x80000100);
		//rch_v1
		outp32(dss_base + DSS_RCH_VG1_DMA_OFFSET + CH_CLK_SEL, 0x80000100);
		//rch_g0
		outp32(dss_base + DSS_RCH_G0_DMA_OFFSET + CH_CLK_SEL, 0x80000000);
		//rch_g1
		outp32(dss_base + DSS_RCH_G1_DMA_OFFSET + CH_CLK_SEL, 0x80000000);
		//rch_d0
		outp32(dss_base + DSS_RCH_D0_DMA_OFFSET + CH_CLK_SEL, 0x80000000);
		//rch_d1
		outp32(dss_base + DSS_RCH_D1_DMA_OFFSET + CH_CLK_SEL, 0x80000000);
		//rch_d2
		outp32(dss_base + DSS_RCH_D2_DMA_OFFSET + CH_CLK_SEL, 0x80000000);
		//rch_d3
		outp32(dss_base + DSS_RCH_D3_DMA_OFFSET + CH_CLK_SEL, 0x80000000);
		//wch0
		outp32(dss_base + DSS_WCH0_DMA_OFFSET + CH_CLK_SEL, 0x80000000);
		//wch1
		outp32(dss_base + DSS_WCH1_DMA_OFFSET + CH_CLK_SEL, 0x80000000);
		//ov0
		outp32(dss_base + DSS_OVL0_OFFSET + OVL6_OV_CLK_SEL, 0x00000000);
		//ov2
		outp32(dss_base + DSS_OVL2_OFFSET + OVL6_OV_CLK_SEL, 0x00000000);
		//ov1
		outp32(dss_base + DSS_OVL1_OFFSET + OVL2_OV_CLK_SEL, 0x00000000);
		//0v3
		outp32(dss_base + DSS_OVL3_OFFSET + OVL2_OV_CLK_SEL, 0x00000000);
		//dbuf0
		outp32(dss_base + DSS_DBUF0_OFFSET + DBUF_CLK_SEL, 0x00000000);
		//dbuf1
		outp32(dss_base + DSS_DBUF1_OFFSET + DBUF_CLK_SEL, 0x00000000);
	#else
		outp32(dss_base + DSS_CMDLIST_OFFSET + CMD_MEM_CTRL, 0x00000008);

		outp32(dss_base + DSS_RCH_VG0_SHARPNESS_OFFSET + SHARPNESS_MEM_CTRL, 0x00000088);
		outp32(dss_base + DSS_RCH_VG0_CE_OFFSET + CE_MEM_CTRL, 0x00000088);
		outp32(dss_base + DSS_RCH_VG0_DMA_OFFSET + VPP_MEM_CTRL, 0x00000008);
		outp32(dss_base + DSS_RCH_VG0_DMA_OFFSET + DMA_BUF_MEM_CTRL, 0x00000008);
		outp32(dss_base + DSS_RCH_VG0_DMA_OFFSET + AFBCD_MEM_CTRL, 0x00000888);

		outp32(dss_base + DSS_RCH_VG1_SHARPNESS_OFFSET + SHARPNESS_MEM_CTRL, 0x00000088);
		outp32(dss_base + DSS_RCH_VG1_CE_OFFSET + CE_MEM_CTRL, 0x00000088);
		outp32(dss_base + DSS_RCH_VG1_DMA_OFFSET + VPP_MEM_CTRL, 0x00000008);
		outp32(dss_base + DSS_RCH_VG1_DMA_OFFSET + DMA_BUF_MEM_CTRL, 0x00000008);
		outp32(dss_base + DSS_RCH_VG1_DMA_OFFSET + AFBCD_MEM_CTRL, 0x00000888);

		outp32(dss_base + DSS_RCH_G0_SCL_OFFSET + SCF_COEF_MEM_CTRL, 0x00000088);
		outp32(dss_base + DSS_RCH_G0_SCL_OFFSET + SCF_LB_MEM_CTRL, 0x0000008);
		outp32(dss_base + DSS_RCH_G0_DMA_OFFSET + DMA_BUF_MEM_CTRL, 0x00000008);
		outp32(dss_base + DSS_RCH_G0_DMA_OFFSET + AFBCD_MEM_CTRL, 0x00000888);

		outp32(dss_base + DSS_RCH_G1_SCL_OFFSET + SCF_COEF_MEM_CTRL, 0x00000088);
		outp32(dss_base + DSS_RCH_G1_SCL_OFFSET + SCF_LB_MEM_CTRL, 0x0000008);
		outp32(dss_base + DSS_RCH_G1_DMA_OFFSET + DMA_BUF_MEM_CTRL, 0x00000008);
		outp32(dss_base + DSS_RCH_G1_DMA_OFFSET + AFBCD_MEM_CTRL, 0x00000888);

		outp32(dss_base + DSS_RCH_D0_DMA_OFFSET + DMA_BUF_MEM_CTRL, 0x00000008);
		outp32(dss_base + DSS_RCH_D0_DMA_OFFSET + AFBCD_MEM_CTRL, 0x00000888);

		outp32(dss_base + DSS_RCH_D1_DMA_OFFSET + DMA_BUF_MEM_CTRL, 0x00000008);
		outp32(dss_base + DSS_RCH_D1_DMA_OFFSET + AFBCD_MEM_CTRL, 0x00000888);

		outp32(dss_base + DSS_RCH_D2_DMA_OFFSET + DMA_BUF_MEM_CTRL, 0x00000008);
		outp32(dss_base + DSS_RCH_D2_DMA_OFFSET + AFBCD_MEM_CTRL, 0x00000888);

		outp32(dss_base + DSS_RCH_D3_DMA_OFFSET + DMA_BUF_MEM_CTRL, 0x00000008);
		outp32(dss_base + DSS_RCH_D3_DMA_OFFSET + AFBCD_MEM_CTRL, 0x00000888);

		outp32(dss_base + DSS_WCH0_DMA_OFFSET + DMA_BUF_MEM_CTRL, 0x00000008);
		outp32(dss_base + DSS_WCH0_DMA_OFFSET + AFBCE_MEM_CTRL, 0x00000888);

		outp32(dss_base + DSS_WCH1_DMA_OFFSET + DMA_BUF_MEM_CTRL, 0x00000008);
		outp32(dss_base + DSS_WCH1_DMA_OFFSET + AFBCE_MEM_CTRL, 0x00000888);

		outp32(dss_base + DSS_OVL0_OFFSET + OVL6_GATE_CTRL, 0x00000002);
		outp32(dss_base + DSS_OVL1_OFFSET + OVL2_GATE_CTRL, 0x00000002);
		outp32(dss_base + DSS_OVL2_OFFSET + OVL6_GATE_CTRL, 0x00000002);
		outp32(dss_base + DSS_OVL3_OFFSET + OVL2_GATE_CTRL, 0x00000002);
		#ifdef CONFIG_HISI_FB_6250
		//scf mem
		outp32(dss_base + DSS_POST_SCF_OFFSET + SCF_COEF_MEM_CTRL, 0x00000088);
		//scf mem
		outp32(dss_base + DSS_POST_SCF_OFFSET + SCF_LB_MEM_CTRL, 0x00000008);
		//rch_v0 mem
		outp32(dss_base + DSS_RCH_VG0_SCL_OFFSET + SCF_COEF_MEM_CTRL, 0x00000088);
		//rch_v0 mem
		outp32(dss_base + DSS_RCH_VG0_SCL_OFFSET + SCF_LB_MEM_CTRL, 0x00000008);
		//rch_v1 mem
		outp32(dss_base + DSS_RCH_VG1_SCL_OFFSET + SCF_COEF_MEM_CTRL, 0x00000088);
		//rch_v1 mem
		outp32(dss_base + DSS_RCH_VG1_SCL_OFFSET + SCF_LB_MEM_CTRL, 0x00000008);
		//wch0 rot mem
		outp32(dss_base + DSS_WCH0_DMA_OFFSET + ROT_MEM_CTRL, 0x00000008);
		//wch1 rot mem
		outp32(dss_base + DSS_WCH1_DMA_OFFSET + ROT_MEM_CTRL, 0x00000008);
		#endif
	#endif
		#ifdef CONFIG_HISI_FB_3650
		//glb
		//outp32(dss_base + DSS_GLB0_OFFSET + GLB_MODULE_CLK_SEL, 0xf0000029);
		//cmd
		//outp32(dss_base + DSS_CMDLIST_OFFSET + CMD_CLK_SEL, 0x00000009);
		//scf mem
		outp32(dss_base + DSS_POST_SCF_OFFSET + SCF_COEF_MEM_CTRL, 0x00000088);
		//scf mem
		outp32(dss_base + DSS_POST_SCF_OFFSET + SCF_LB_MEM_CTRL, 0x00000008);
		//rch_v0 mem
		outp32(dss_base + DSS_RCH_VG0_SCL_OFFSET + SCF_COEF_MEM_CTRL, 0x00000088);
		//rch_v0 mem
		outp32(dss_base + DSS_RCH_VG0_SCL_OFFSET + SCF_LB_MEM_CTRL, 0x00000008);
		//rch_v1 mem
		outp32(dss_base + DSS_RCH_VG1_SCL_OFFSET + SCF_COEF_MEM_CTRL, 0x00000088);
		//rch_v1 mem
		outp32(dss_base + DSS_RCH_VG1_SCL_OFFSET + SCF_LB_MEM_CTRL, 0x00000008);
		//wch0 rot mem
		outp32(dss_base + DSS_WCH0_DMA_OFFSET + ROT_MEM_CTRL, 0x00000008);
		//wch1 rot mem
		outp32(dss_base + DSS_WCH1_DMA_OFFSET + ROT_MEM_CTRL, 0x00000008);
		#endif
	}

	HISI_FB_DEBUG("fb%d, dss_inner_clk_refcount=%d\n",
		hisifd->index, dss_inner_clk_refcount);

	up(&hisi_fb_dss_inner_clk_sem);
}

void dss_inner_clk_common_disable(struct hisi_fb_data_type *hisifd)
{
	int new_refcount = 0;

	BUG_ON(hisifd == NULL);

	down(&hisi_fb_dss_inner_clk_sem);
	new_refcount = --dss_inner_clk_refcount;
	WARN_ON(new_refcount < 0);
	if (!new_refcount) {
		;
	}

	HISI_FB_DEBUG("fb%d, dss_inner_clk_refcount=%d\n",
		hisifd->index, dss_inner_clk_refcount);
	up(&hisi_fb_dss_inner_clk_sem);
}

void dss_inner_clk_pdp_enable(struct hisi_fb_data_type *hisifd, bool fastboot_enable)
{
	char __iomem *dss_base = NULL;

	BUG_ON(hisifd == NULL);

	dss_base = hisifd->dss_base;

	if (fastboot_enable)
		return ;

	//enable ldi0 clk
	//outp32(hisifd->peri_crg_base + PEREN3, 0x00008000);

#ifdef CONFIG_DSS_LP_USED
	//dpp
	outp32(dss_base + DSS_DPP_OFFSET + DPP_CLK_SEL, 0x00000000);
	//ifbc
	outp32(dss_base + DSS_IFBC_OFFSET + IFBC_CLK_SEL, 0x00000000);
	//dsc
	outp32(dss_base + DSS_DSC_OFFSET + DSC_CLK_SEL, 0x00000000);
	//ldi0
	outp32(dss_base + DSS_LDI0_OFFSET + LDI_CLK_SEL, 0x00000004);
#else
	outp32(dss_base + DSS_IFBC_OFFSET + IFBC_MEM_CTRL, 0x00000088);
	outp32(dss_base + DSS_DSC_OFFSET + DSC_MEM_CTRL, 0x00000888);
	outp32(dss_base + DSS_LDI0_OFFSET + LDI_MEM_CTRL, 0x00000008);
	#ifdef CONFIG_HISI_FB_6250
	//dbuf0 mem
	outp32(dss_base + DSS_DBUF0_OFFSET + DBUF_MEM_CTRL, 0x00000008);
	#endif
#endif
	#ifdef CONFIG_HISI_FB_3650
	//dbuf0 mem
	outp32(dss_base + DSS_DBUF0_OFFSET + DBUF_MEM_CTRL, 0x00000008);
	#endif
}

void dss_inner_clk_pdp_disable(struct hisi_fb_data_type *hisifd)
{
}

void dss_inner_clk_sdp_enable(struct hisi_fb_data_type *hisifd)
{
	char __iomem *dss_base = NULL;

	BUG_ON(hisifd == NULL);

	dss_base = hisifd->dss_base;

	//enable ldi1 clk
	//outp32(hisifd->peri_crg_base + PEREN3, 0x00004000);

#ifdef CONFIG_DSS_LP_USED
	//ldi1
	outp32(dss_base + DSS_LDI1_OFFSET + LDI_CLK_SEL, 0x00000000);
#else
	outp32(dss_base + DSS_LDI1_OFFSET + LDI_MEM_CTRL, 0x00000008);
#endif
	//dbuf1 mem
	outp32(dss_base + DSS_DBUF1_OFFSET + DBUF_MEM_CTRL, 0x00000008);
}

void dss_inner_clk_sdp_disable(struct hisi_fb_data_type *hisifd)
{
}

void init_dpp(struct hisi_fb_data_type *hisifd)
{
	char __iomem *dpp_base = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		dpp_base = hisifd->dss_base + DSS_DPP_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return ;
	}

	set_reg(dpp_base + DPP_IMG_HRZ, DSS_WIDTH(pinfo->xres), 13, 0);
	set_reg(dpp_base + DPP_IMG_VRT, DSS_HEIGHT(pinfo->yres), 13, 0);
	set_reg(dpp_base + DPP_DBG, 0x00000001, 32, 0);

}

void init_sbl(struct hisi_fb_data_type *hisifd)
{
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *dpp_base = NULL;
	char __iomem *sbl_base = NULL;
	uint32_t tmp = 0;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	if (pinfo->sbl_support != 1) {
		return;
	}

	if (!HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_SBL)) {
		return;
	}

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		dpp_base = hisifd->dss_base + DSS_DPP_OFFSET;
		sbl_base = hisifd->dss_base + DSS_DPP_SBL_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return ;
	}

	if (is_mipi_cmd_panel(hisifd)) {
		outp32(sbl_base + SBL_CONFIG_BUFFER_MODE, 0x2);
	} else {
		outp32(sbl_base + SBL_CONFIG_BUFFER_MODE, 0x0);
	}

	outp32(sbl_base + SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL, 0x81);
	tmp = pinfo->xres;
	outp32(sbl_base + SBL_FRAME_WIDTH_L, (tmp & 0xff));
	outp32(sbl_base + SBL_FRAME_WIDTH_H, ((tmp >> 8) & 0xff));
	tmp = pinfo->yres;
	outp32(sbl_base + SBL_FRAME_HEIGHT_L, (tmp & 0xff));
	outp32(sbl_base + SBL_FRAME_HEIGHT_H, ((tmp >> 8) & 0xff));
	outp32(sbl_base + SBL_APICAL_DITHER, 0x5);
	tmp = hisifd->bl_level;
	outp32(sbl_base + SBL_BACKLIGHT_L, (tmp & 0xff));
	outp32(sbl_base + SBL_BACKLIGHT_H, ((tmp >> 8) & 0xff));
	tmp = pinfo->smart_bl.backlight_scale;
	outp32(sbl_base + SBL_BACKLIGHT_SCALE_L, (tmp & 0xff));
	outp32(sbl_base + SBL_BACKLIGHT_SCALE_H, (tmp >> 8) & 0xff);
	tmp = pinfo->smart_bl.strength_limit;
	outp32(sbl_base + SBL_STRENGTH_LIMIT, tmp);
	tmp = pinfo->smart_bl.calibration_a;
	outp32(sbl_base + SBL_CALIBRATION_A_L, (tmp & 0xff));
	outp32(sbl_base + SBL_CALIBRATION_A_H, ((tmp >> 8) & 0xff));
	tmp = pinfo->smart_bl.calibration_b;
	outp32(sbl_base + SBL_CALIBRATION_B_L, (tmp & 0xff));
	outp32(sbl_base + SBL_CALIBRATION_B_H, ((tmp >> 8) & 0xff));
	tmp = pinfo->smart_bl.calibration_c;
	outp32(sbl_base + SBL_CALIBRATION_C_L, (tmp & 0xff));
	outp32(sbl_base + SBL_CALIBRATION_C_H, ((tmp >> 8) & 0xff));
	tmp = pinfo->smart_bl.calibration_d;
	outp32(sbl_base + SBL_CALIBRATION_D_L, (tmp & 0xff));
	outp32(sbl_base + SBL_CALIBRATION_D_H, ((tmp >> 8) & 0xff));
	tmp = pinfo->smart_bl.t_filter_control;
	outp32(sbl_base + SBL_T_FILTER_CONTROL, tmp);
	tmp = pinfo->smart_bl.backlight_min;
	outp32(sbl_base + SBL_BACKLIGHT_MIN_L, (tmp & 0xff));
	outp32(sbl_base + SBL_BACKLIGHT_MIN_H, ((tmp >> 8) & 0xff));
	tmp = pinfo->smart_bl.backlight_max;
	outp32(sbl_base + SBL_BACKLIGHT_MAX_L, (tmp & 0xff));
	outp32(sbl_base + SBL_BACKLIGHT_MAX_H, ((tmp >> 8) & 0xff));
	tmp = pinfo->smart_bl.ambient_light_min;
	outp32(sbl_base + SBL_AMBIENT_LIGHT_MIN_L, (tmp & 0xff));
	outp32(sbl_base + SBL_AMBIENT_LIGHT_MIN_H, ((tmp >> 8) & 0xff));
	tmp = pinfo->smart_bl.filter_a;
	outp32(sbl_base + SBL_FILTER_A_L, (tmp & 0xff));
	outp32(sbl_base + SBL_FILTER_A_H, ((tmp >> 8) & 0xff));
	tmp = pinfo->smart_bl.filter_b;
	outp32(sbl_base + SBL_FILTER_B, tmp);
	tmp = pinfo->smart_bl.logo_left;
	outp32(sbl_base + SBL_LOGO_LEFT, tmp);
	tmp = pinfo->smart_bl.logo_top;
	outp32(sbl_base + SBL_LOGO_TOP, tmp);

	tmp = pinfo->smart_bl.variance_intensity_space;
	outp32(sbl_base + SBL_VARIANCE_INTENSITY_SPACE, tmp);
	tmp = pinfo->smart_bl.slope_max;
	outp32(sbl_base + SBL_SLOPE_MAX, tmp);
	tmp = pinfo->smart_bl.slope_min;
	outp32(sbl_base + SBL_SLOPE_MIN, tmp);

	for(tmp = 0; tmp < 33; tmp++){
		outp32(sbl_base + SBL_AL_CALIB_LUT_LUT_ADDR, tmp);
		outp32(sbl_base + SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L, (sbl_al_calib_lut[tmp] & 0xff));
		outp32(sbl_base + SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H, ((sbl_al_calib_lut[tmp] >> 8) & 0xff));
	}

	outp32(sbl_base + SBL_ENABLE, 0x0);
	if (hisifd->panel_info.sbl_support == 1) {
		outp32(dpp_base + DPP_SBL, 0x1);
	} else {
		outp32(dpp_base + DPP_SBL, 0x0);
	}
#ifdef NEW_SBL_CTRL
	pinfo->smart_bl.BL_linearity_LUT = bl_linearity_lut;
	pinfo->smart_bl.BL_linearity_inverse_LUT = bl_linearity_inverse_lut;
	pinfo->smart_bl.BL_att_LUT = bl_att_lut;
#endif

#ifdef CONFIG_SBL_BY_FILE
	init_sbl_by_cfg(pinfo, sbl_base);
#endif

}

static void init_dsc(struct hisi_fb_data_type *hisifd)
{
	char __iomem *dsc_base = NULL;
	struct hisi_panel_info *pinfo = NULL;
	struct dsc_panel_info *dsc = NULL;

	uint32_t dsc_en = 0;
	uint32_t pic_width = 0;
	uint32_t pic_height = 0;
	uint32_t chunk_size = 0;
	uint32_t groups_per_line = 0;
	uint32_t rbs_min = 0;
	uint32_t hrd_delay = 0;
	uint32_t target_bpp_x16 =0;
	uint32_t num_extra_mux_bits = 0;
	uint32_t slice_bits = 0;
	uint32_t final_offset = 0;
	uint32_t final_scale = 0;
	uint32_t nfl_bpg_offset = 0;
	uint32_t groups_total = 0;
	uint32_t slice_bpg_offset = 0;
	uint32_t scale_increment_interval = 0;
	uint32_t initial_scale_value = 0;
	uint32_t scale_decrement_interval = 0;
	uint32_t adjustment_bits =0;
	uint32_t adj_bits_per_grp = 0;
	uint32_t bits_per_grp = 0;
	uint32_t slices_per_line = 0;
	uint32_t pic_line_grp_num = 0;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);
	dsc = &(pinfo->vesa_dsc);

	dsc_base = hisifd->dss_base + DSS_DSC_OFFSET;

	if ((pinfo->ifbc_type == IFBC_TYPE_VESA2X_SINGLE) ||
		(pinfo->ifbc_type == IFBC_TYPE_VESA3X_SINGLE)) {
		// crc_ldi0_en = 1
		set_reg(hisifd->dss_base + GLB_CRC_LDI0_EN, 0x1, 1, 0);

		// dual_dsc_en = 0, dsc_if_bypass = 1, reset_ich_per_line = 0
		dsc_en = 0x5;
		pic_width = DSS_WIDTH(pinfo->xres);
	} else {
		// dual_dsc_en = 1, dsc_if_bypass = 0, reset_ich_per_line = 1
		dsc_en = 0xb;
		pic_width = DSS_WIDTH(pinfo->xres / 2);
	}

	pic_height =  DSS_HEIGHT(pinfo->yres);
	chunk_size = ROUND1((dsc->slice_width + 1) * dsc->bits_per_pixel, 8);

	groups_per_line = (dsc->slice_width + 3) / 3;
	rbs_min = dsc->rc_model_size - dsc->initial_offset + dsc->initial_xmit_delay * dsc->bits_per_pixel +
		groups_per_line * dsc->first_line_bpg_offset;
	hrd_delay = ROUND1(rbs_min, dsc->bits_per_pixel);

	target_bpp_x16 = dsc->bits_per_pixel * 16;
	slice_bits = 8 * chunk_size * (dsc->slice_height + 1);

	num_extra_mux_bits = 3 * (dsc->mux_word_size + (4 * dsc->bits_per_component + 4) - 2);
	while ((num_extra_mux_bits > 0) && ((slice_bits - num_extra_mux_bits) % dsc->mux_word_size))
		num_extra_mux_bits--;

	final_offset =  dsc->rc_model_size - ((dsc->initial_xmit_delay * target_bpp_x16 + 8) >> 4) + num_extra_mux_bits; //4336(0x10f0)
	final_scale = 8 * dsc->rc_model_size / (dsc->rc_model_size - final_offset);
	nfl_bpg_offset = ROUND1(dsc->first_line_bpg_offset << OFFSET_FRACTIONAL_BITS, dsc->slice_height); //793(0x319)
	groups_total = groups_per_line * (dsc->slice_height + 1);
	slice_bpg_offset = ROUND1((1 << OFFSET_FRACTIONAL_BITS) *
		(dsc->rc_model_size - dsc->initial_offset + num_extra_mux_bits), groups_total); // 611(0x263)
	scale_increment_interval = (1 << OFFSET_FRACTIONAL_BITS) * final_offset /
		((final_scale - 9) * (nfl_bpg_offset + slice_bpg_offset)); // 903(0x387)

	initial_scale_value = 8 * dsc->rc_model_size / (dsc->rc_model_size - dsc->initial_offset);
	if (groups_per_line < initial_scale_value - 8)	{
		initial_scale_value = groups_per_line + 8;
	}

	if (initial_scale_value > 8) {
		scale_decrement_interval = groups_per_line / (initial_scale_value - 8);
	} else {
		scale_decrement_interval = 4095;
	}

	adjustment_bits = (8 - (dsc->bits_per_pixel * (dsc->slice_width + 1)) % 8) % 8;
	adj_bits_per_grp = dsc->bits_per_pixel * 3 - 3;
	bits_per_grp = dsc->bits_per_pixel * 3;
	slices_per_line = (pic_width > dsc->slice_width) ? 1 : 0;
	pic_line_grp_num = ((dsc->slice_width + 3)/3)*(slices_per_line+1)-1;

	set_reg(dsc_base + DSC_REG_DEFAULT, 0x1, 1, 0);

	// dsc_en
	set_reg(dsc_base + DSC_EN, dsc_en, 4, 0);

	// bits_per_component, convert_rgb, bits_per_pixel
	set_reg(dsc_base + DSC_CTRL, dsc->bits_per_component | (dsc->linebuf_depth << 4) | (dsc->block_pred_enable << 10) |
		(0x1 << 11) | (dsc->bits_per_pixel << 16), 26, 0);

	// pic_width, pic_height
	set_reg(dsc_base + DSC_PIC_SIZE, (pic_width << 16) | pic_height, 32, 0);

	// slice_width, slice_height
	set_reg(dsc_base + DSC_SLICE_SIZE, (dsc->slice_width << 16) | dsc->slice_height, 32, 0);

	// chunk_size
	set_reg(dsc_base + DSC_CHUNK_SIZE, chunk_size, 16, 0);

	// initial_xmit_delay, initial_dec_delay = hrd_delay -initial_xmit_delay
	set_reg(dsc_base + DSC_INITIAL_DELAY, dsc->initial_xmit_delay |
		((hrd_delay - dsc->initial_xmit_delay) << 16), 32, 0);

	// initial_scale_value, scale_increment_interval
	set_reg(dsc_base + DSC_RC_PARAM0, initial_scale_value | (scale_increment_interval << 16), 32, 0);

	// scale_decrement_interval, first_line_bpg_offset
	set_reg(dsc_base + DSC_RC_PARAM1, (dsc->first_line_bpg_offset << 16) | scale_decrement_interval, 21, 0);

	// nfl_bpg_offset, slice_bpg_offset
	set_reg(dsc_base + DSC_RC_PARAM2, nfl_bpg_offset | (slice_bpg_offset << 16), 32, 0);

	//DSC_RC_PARAM3
	set_reg(dsc_base + DSC_RC_PARAM3,
		((final_offset << 16) | dsc->initial_offset), 32, 0);

	//DSC_FLATNESS_QP_TH
	set_reg(dsc_base + DSC_FLATNESS_QP_TH,
		((dsc->flatness_max_qp << 16) | (dsc->flatness_min_qp << 0)), 24, 0);

	//DSC_RC_PARAM4
	set_reg(dsc_base + DSC_RC_PARAM4,
		((dsc->rc_edge_factor << 20) | (dsc->rc_model_size << 0)), 24, 0);
	//DSC_RC_PARAM5
	set_reg(dsc_base + DSC_RC_PARAM5,
		((dsc->rc_tgt_offset_lo << 20) |(dsc->rc_tgt_offset_hi << 16) |
		(dsc->rc_quant_incr_limit1 << 8) |(dsc->rc_quant_incr_limit0 << 0)), 24, 0);

	//DSC_RC_BUF_THRESH
	set_reg(dsc_base + DSC_RC_BUF_THRESH0,
		((dsc->rc_buf_thresh0 << 24) | (dsc->rc_buf_thresh1 << 16) |
		(dsc->rc_buf_thresh2 << 8) | (dsc->rc_buf_thresh3 << 0)), 32, 0);
	set_reg(dsc_base + DSC_RC_BUF_THRESH1,
		((dsc->rc_buf_thresh4 << 24) | (dsc->rc_buf_thresh5 << 16) |
		(dsc->rc_buf_thresh6 << 8) | (dsc->rc_buf_thresh7 << 0)), 32, 0);
	set_reg(dsc_base + DSC_RC_BUF_THRESH2,
		((dsc->rc_buf_thresh8 << 24) | (dsc->rc_buf_thresh9 << 16) |
		(dsc->rc_buf_thresh10 << 8) | (dsc->rc_buf_thresh11 << 0)), 32, 0);
	set_reg(dsc_base + DSC_RC_BUF_THRESH3,
		((dsc->rc_buf_thresh12 << 24) | (dsc->rc_buf_thresh13 << 16)), 32, 0);

	//DSC_RC_RANGE_PARAM
	set_reg(dsc_base + DSC_RC_RANGE_PARAM0,
		((dsc->range_min_qp0 << 27) | (dsc->range_max_qp0 << 22) |
		(dsc->range_bpg_offset0 << 16) | (dsc->range_min_qp1 << 11) |
		(dsc->range_max_qp1 << 6) | (dsc->range_bpg_offset1 << 0)), 32, 0);
	set_reg(dsc_base + DSC_RC_RANGE_PARAM1,
		((dsc->range_min_qp2 << 27) | (dsc->range_max_qp2 << 22) |
		(dsc->range_bpg_offset2 << 16) | (dsc->range_min_qp3 << 11) |
		(dsc->range_max_qp3 << 6) | (dsc->range_bpg_offset3 << 0)), 32, 0);
	set_reg(dsc_base + DSC_RC_RANGE_PARAM2,
		((dsc->range_min_qp4 << 27) | (dsc->range_max_qp4 << 22) |
		(dsc->range_bpg_offset4 << 16) | (dsc->range_min_qp5 << 11) |
		(dsc->range_max_qp5 << 6) | (dsc->range_bpg_offset5 << 0)), 32, 0);
	set_reg(dsc_base + DSC_RC_RANGE_PARAM3,
		((dsc->range_min_qp6 << 27) | (dsc->range_max_qp6 << 22) |
		(dsc->range_bpg_offset6 << 16) | (dsc->range_min_qp7 << 11) |
		(dsc->range_max_qp7 << 6) | (dsc->range_bpg_offset7 << 0)), 32, 0);
	set_reg(dsc_base + DSC_RC_RANGE_PARAM4,
		((dsc->range_min_qp8 << 27) | (dsc->range_max_qp8 << 22) |
		(dsc->range_bpg_offset8 << 16) | (dsc->range_min_qp9 << 11) |
		(dsc->range_max_qp9 << 6) | (dsc->range_bpg_offset9 << 0)), 32, 0);
	set_reg(dsc_base + DSC_RC_RANGE_PARAM5,
		((dsc->range_min_qp10 << 27) | (dsc->range_max_qp10 << 22) |
		(dsc->range_bpg_offset10 << 16) | (dsc->range_min_qp11 << 11) |
		(dsc->range_max_qp11 << 6) | (dsc->range_bpg_offset11 << 0)), 32, 0);
	set_reg(dsc_base + DSC_RC_RANGE_PARAM6,
		((dsc->range_min_qp12 << 27) | (dsc->range_max_qp12 << 22) |
		(dsc->range_bpg_offset12 << 16) | (dsc->range_min_qp13 << 11) |
		(dsc->range_max_qp13 << 6) | (dsc->range_bpg_offset13 << 0)), 32, 0);
	set_reg(dsc_base + DSC_RC_RANGE_PARAM7,
		((dsc->range_min_qp14 << 27) | (dsc->range_max_qp14 << 22) |
		(dsc->range_bpg_offset14 << 16)), 32, 0);

	// adjustment_bits
	set_reg(dsc_base + DSC_ADJUSTMENT_BITS, adjustment_bits, 4, 0);

	// bits_per_grp, adj_bits_per_grp
	set_reg(dsc_base + DSC_BITS_PER_GRP, bits_per_grp | (adj_bits_per_grp << 8), 14, 0);

	//slices_per_line, pic_line_grp_num
	set_reg(dsc_base + DSC_MULTI_SLICE_CTL, slices_per_line |
		(pic_line_grp_num << 16), 32, 0);

	//dsc_out_mode
	if ((chunk_size % 3 == 0)) {
		set_reg(dsc_base + DSC_OUT_CTRL, 0x0, 1, 0);
	} else if ((chunk_size % 2 == 0)) {
		set_reg(dsc_base + DSC_OUT_CTRL, 0x1, 1, 0);
	} else {
		HISI_FB_ERR("fb%d, chunk_size should be mode by 3 or 2, but chunk_size = %u\n",
			hisifd->index, chunk_size);
		return;
	}

	set_reg(dsc_base + DSC_CLK_SEL, 0x0, 32, 0);
	set_reg(dsc_base + DSC_CLK_EN, 0x7, 32, 0);
	set_reg(dsc_base + DSC_MEM_CTRL, 0x0, 32, 0);
	set_reg(dsc_base + DSC_ST_DATAIN, 0x0, 28, 0);
	set_reg(dsc_base + DSC_ST_DATAOUT, 0x0, 16, 0);
	set_reg(dsc_base + DSC0_ST_SLC_POS, 0x0, 28, 0);
	set_reg(dsc_base + DSC1_ST_SLC_POS, 0x0, 28, 0);
	set_reg(dsc_base + DSC0_ST_PIC_POS, 0x0, 28, 0);
	set_reg(dsc_base + DSC1_ST_PIC_POS, 0x0, 28, 0);
	set_reg(dsc_base + DSC0_ST_FIFO, 0x0, 14, 0);
	set_reg(dsc_base + DSC1_ST_FIFO, 0x0, 14, 0);
	set_reg(dsc_base + DSC0_ST_LINEBUF, 0x0, 24, 0);
	set_reg(dsc_base + DSC1_ST_LINEBUF, 0x0, 24, 0);
	set_reg(dsc_base + DSC_ST_ITFC, 0x0, 10, 0);
	set_reg(dsc_base + DSC_RD_SHADOW_SEL, 0x1, 1, 0);
	set_reg(dsc_base + DSC_REG_DEFAULT, 0x0, 1, 0);
}

void init_ifbc(struct hisi_fb_data_type *hisifd)
{
	char __iomem *ifbc_base = NULL;
	struct hisi_panel_info *pinfo = NULL;
	uint32_t mipi_idx = 0;
	uint32_t comp_mode = 0;

	uint32_t ifbc_out_mode = 0;
	uint32_t dpk_mode_sel = 0;
	uint32_t dup_mode_sel = 0;
	uint32_t porch_num = 0;
	uint32_t insert_byte_num = 0;
	uint32_t insert_byte = 0;
	uint32_t num_pad = 0;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);
	BUG_ON((pinfo->ifbc_type < IFBC_TYPE_NONE) || (pinfo->ifbc_type >= IFBC_TYPE_MAX));

	if (pinfo->ifbc_type == IFBC_TYPE_NONE)
		return ;

	if (!HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_IFBC))
		return;

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		ifbc_base = hisifd->dss_base + DSS_IFBC_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return ;
	}

	mipi_idx = is_dual_mipi_panel(hisifd) ? 1 : 0;
	comp_mode = g_mipi_ifbc_division[mipi_idx][pinfo->ifbc_type].comp_mode;

	if (is_ifbc_vesa_panel(hisifd)) {
		init_dsc(hisifd);

		// select comp_mode
		set_reg(ifbc_base + IFBC_CTRL, comp_mode, 3, 0);
		return ;
	}

	// git ifbc_out_mode
	if (pinfo->bpp == LCD_RGB888)
		ifbc_out_mode = 1;
	else if (pinfo->bpp == LCD_RGB565)
		ifbc_out_mode = 0;

	if (((pinfo->ifbc_type == IFBC_TYPE_ORISE2X) && (pinfo->ifbc_cmp_dat_rev0 == 1)) ||
		((pinfo->ifbc_type == IFBC_TYPE_RSP3X) &&
		(pinfo->type != PANEL_MIPI_VIDEO) &&
		(pinfo->xres % 3 != 0)))
		if (pinfo->ifbc_auto_sel != 0) {
			HISI_FB_ERR("fb%d, auto_sel = %u not support!", hisifd->index, pinfo->ifbc_auto_sel);
			return ;
		}

	if (pinfo->ifbc_type == IFBC_TYPE_ORISE2X) {
		if ((pinfo->xres % 2 != 0) &&
			(pinfo->yres % 2 != 0)) {
			HISI_FB_ERR("fb%d, IFBC_ORISE2X not support (xres = %u, yres = %u)!",
				hisifd->index, pinfo->xres, pinfo->yres);
			return;
		}

		dpk_mode_sel = 1;
		dup_mode_sel = 2;
		porch_num = 0;
	} else if (pinfo->ifbc_type == IFBC_TYPE_ORISE3X) {
		dpk_mode_sel = 0;
		dup_mode_sel = 3;
		porch_num = 5;
	} else if (pinfo->ifbc_type == IFBC_TYPE_HIMAX2X) {
		if ((pinfo->xres % 2 != 0) &&
			(pinfo->yres % 2 != 0)) {
			HISI_FB_ERR("fb%d, IFBC_HIMAX2X not support (xres = %u, yres = %u)!",
				hisifd->index, pinfo->xres, pinfo->yres);
			return;
		}

		dpk_mode_sel = 1;
		dup_mode_sel = 2;
		porch_num = 0;
	} else if (pinfo->ifbc_type == IFBC_TYPE_RSP2X) {
		dpk_mode_sel = 1;
		dup_mode_sel = 0;
		porch_num = 0;

		if ((pinfo->type == PANEL_MIPI_CMD) ||
			(pinfo->type == PANEL_DUAL_MIPI_CMD))
			num_pad = (4 - pinfo->xres % 4) % 4;
		else
			num_pad = 0;
	} else if (pinfo->ifbc_type == IFBC_TYPE_RSP3X) {
		if ((pinfo->yres % 2 != 0) || (pinfo->yres < 8)) {
			HISI_FB_ERR("fb%d, IFBC_RSP3X not support (xres = %u, yres = %u)!",
				hisifd->index, pinfo->xres, pinfo->yres);
			return;
		}

		dpk_mode_sel = 2;
		dup_mode_sel = 1;
		porch_num = 0;

		insert_byte = DSS_WIDTH(pinfo->xres) / (mipi_idx + 1) + 1;

		if ((pinfo->type == PANEL_MIPI_VIDEO) ||
			(pinfo->type == PANEL_DUAL_MIPI_VIDEO)) {
			insert_byte_num = (3 - insert_byte % 3) % 3;
			num_pad = (8 - pinfo->xres % 8) % 8;
		} else if ((pinfo->type == PANEL_MIPI_CMD) ||
			(pinfo->type == PANEL_DUAL_MIPI_CMD)) {
			insert_byte_num = 0;
			num_pad = (4 - pinfo->xres % 4) % 4;
		}
	}

	// crc_ldi0_en = 1
	set_reg(hisifd->dss_base + GLB_CRC_LDI0_EN, 0x1, 1, 0);

	// reg_default
	//set_reg(ifbc_base + IFBC_REG_DEFAULT, 0x1, 1, 0);

	// ifbc_rd_shadow = 1
	//set_reg(ifbc_base + IFBC_RD_SHADOW, 0x1, 1, 0);

	// set ifbc_size
	set_reg(ifbc_base + IFBC_SIZE,
		((DSS_WIDTH(pinfo->xres) << 16) |
		DSS_HEIGHT(pinfo->yres)), 32, 0);

	// set IFBC_CTRL
	set_reg(ifbc_base + IFBC_CTRL, comp_mode, 3, 0);
	set_reg(ifbc_base + IFBC_CTRL, ifbc_out_mode, 1, 3);
	set_reg(ifbc_base + IFBC_CTRL, pinfo->ifbc_cmp_dat_rev0, 1, 4);
	set_reg(ifbc_base + IFBC_CTRL, pinfo->ifbc_cmp_dat_rev1, 1, 5);
	set_reg(ifbc_base + IFBC_CTRL, pinfo->ifbc_auto_sel, 1, 6);

	if (pinfo->ifbc_auto_sel == 0) {
		set_reg(ifbc_base + IFBC_CTRL, dpk_mode_sel, 3, 7);
		set_reg(ifbc_base + IFBC_CTRL, dup_mode_sel, 3, 10);
		set_reg(ifbc_base + IFBC_CTRL, porch_num, 8, 13);

		// set insert_byte_num, insert_byte
		set_reg(ifbc_base + IFBC_INSERT, insert_byte_num | (insert_byte << 16), 32, 0);

		// set num_pad
		set_reg(ifbc_base + IFBC_PAD, num_pad, 3, 0);
	}

	//orise3x initialization
	if (pinfo->ifbc_type == IFBC_TYPE_ORISE3X) {
		if (pinfo->ifbc_orise_ctr == 1) {
			set_reg(ifbc_base + IFBC_CORE_GT, 0x0, 2, 0);

			if (pinfo->ifbc_orise_ctl == IFBC_ORISE_CTL_8LINE)
				set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0208, 32, 0);
			else if (pinfo->ifbc_orise_ctl == IFBC_ORISE_CTL_16LINE)
				set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0210, 32, 0);
			else if (pinfo->ifbc_orise_ctl == IFBC_ORISE_CTL_32LINE)
				set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0220, 32, 0);
			else
				set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0200, 32, 0);

			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0300, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0419, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0500, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x063f, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0700, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0801, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0900, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0a64, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0b00, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0c5c, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0d00, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0e01, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x0f00, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x10a0, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x1100, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x125f, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x1300, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x14a0, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x1500, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x16ff, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x1700, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x200c, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x2100, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x4000, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x4100, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x4200, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x4300, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x4800, 32, 0);
			set_reg(ifbc_base + IFBC_ORISE_CTL, 0x4900, 32, 0);
		} else {
			set_reg(ifbc_base + IFBC_CORE_GT, 0x2, 2, 0);
		}
	}

	// set ifbc_clk_sel
	set_reg(ifbc_base + IFBC_CLK_SEL, 0x0, 32, 0);

	// ifbc_rd_shadow = 1
	//set_reg(ifbc_base + IFBC_RD_SHADOW, 0x0, 1, 0);

	//enable ifbc
	set_reg(ifbc_base + IFBC_EN, 0x3, 2, 0);
}

void init_post_scf(struct hisi_fb_data_type *hisifd)
{
	char __iomem *scf_lut_base = NULL;

	BUG_ON(hisifd == NULL);
	scf_lut_base = hisifd->dss_base + DSS_POST_SCF_LUT_OFFSET;

	if (!HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_POST_SCF)) {
		return;
	}

	hisi_dss_post_scl_load_filter_coef(hisifd, false, scf_lut_base, SCL_COEF_RGB_IDX);
}

static int get_dfs_sram_valid_num(struct hisi_fb_data_type *hisifd)
{
	int sram_valid_num = 0;
	int frame_size = 0;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);
	frame_size = pinfo->xres * pinfo->yres;

	if (frame_size <= RES_720P) {
		sram_valid_num = 0;
	} else if (frame_size <= RES_1080P) {
		sram_valid_num = 1;
	} else {
		sram_valid_num = 2;
	}

	return sram_valid_num;
}

void init_dbuf(struct hisi_fb_data_type *hisifd)
{
	char __iomem *dbuf_base = NULL;
	struct hisi_panel_info *pinfo = NULL;
	int sram_valid_num = 0;
	int sram_max_mem_depth = 0;

	uint32_t thd_rqos_in = 0;
	uint32_t thd_rqos_out = 0;
	uint32_t thd_wqos_in = 0;
	uint32_t thd_wqos_out = 0;
	uint32_t thd_cg_in = 0;
	uint32_t thd_cg_out = 0;
	uint32_t thd_wr_wait = 0;
	uint32_t thd_cg_hold = 0;
	uint32_t thd_fill_lev1 = 0;
	uint32_t thd_fill_lev2 = 0;
	uint32_t thd_fill_lev3 = 0;
	uint32_t thd_fill_lev4 = 0;
	uint32_t thd_flux_req_out = 0;
	uint32_t thd_flux_req_in = 0;

	int dfs_time = 0;
	int depth = 0;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		dbuf_base = hisifd->dss_base + DSS_DBUF0_OFFSET;
		if (!HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_DBUF)) {
			return;
		}

		if (g_fpga_flag == 1) {
			sram_valid_num = get_dfs_sram_valid_num(hisifd);
			sram_max_mem_depth = (sram_valid_num + 1) * DBUF0_DEPTH;

			thd_rqos_in = GET_THD_RQOS_IN(sram_max_mem_depth);
			thd_rqos_out = GET_THD_RQOS_OUT(sram_max_mem_depth);
			thd_wqos_in = GET_THD_WQOS_IN(sram_max_mem_depth);
			thd_wqos_out = GET_THD_WQOS_OUT(sram_max_mem_depth);
			#if 0
			thd_cg_in = GET_THD_CG_IN(sram_max_mem_depth);
			thd_cg_out = GET_THD_CG_OUT(sram_max_mem_depth);
			#else
			thd_cg_in = 0x3fff;
			thd_cg_out = 0x3fff;
			#endif
			thd_wr_wait = GET_THD_OTHER_WR_WAIT(sram_max_mem_depth);
			thd_cg_hold = GET_THD_OTHER_DFS_CG_HOLD(sram_max_mem_depth);

			thd_flux_req_out = GET_THD_FLUX_REQ_OUT(sram_max_mem_depth);
			thd_flux_req_in  = GET_THD_FLUX_REQ_IN(sram_max_mem_depth);
		} else {
			dfs_time = DFS_TIME;
			depth = DBUF0_DEPTH;

			/*
			** int K = 0;
			** int Tp = 1000000  / pinfo->pxl_clk_rate;
			** K = (pinfo->ldi.h_pulse_width + pinfo->ldi.h_back_porch + pinfo->xres +
			**	pinfo->ldi.h_front_porch) / pinfo->xres;
			** thd_cg_out = dfs_time / (Tp * K * 6);
			*/
			if (pinfo->pxl_clk_rate_div <= 0)
				pinfo->pxl_clk_rate_div = 1;

			thd_cg_out = (dfs_time * pinfo->pxl_clk_rate * pinfo->xres) /
				(((pinfo->ldi.h_pulse_width + pinfo->ldi.h_back_porch + pinfo->ldi.h_front_porch) * pinfo->pxl_clk_rate_div
				+ pinfo->xres) * 6 * 1000000UL);
			sram_valid_num = thd_cg_out / depth;
			thd_cg_in = (sram_valid_num + 1) * depth - 1;

			thd_rqos_in = thd_cg_out * 85 / 100;
			thd_rqos_out = thd_cg_out;
			thd_fill_lev1 = thd_cg_in * 2 / 10;
			thd_fill_lev2 = thd_cg_in * 4 / 10;
			thd_fill_lev3 = thd_cg_in * 6 / 10;
			thd_fill_lev4 = thd_cg_in * 8 / 10;

			thd_flux_req_out = ((sram_valid_num + 1) * depth * 9) / 10;
			thd_flux_req_in  = ((sram_valid_num + 1) * depth * 5) / 10;
		}
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		dbuf_base = hisifd->dss_base + DSS_DBUF1_OFFSET;

		if (g_fpga_flag == 1) {
			thd_rqos_in = GET_THD_RQOS_IN(sram_max_mem_depth);
			thd_rqos_out = GET_THD_RQOS_OUT(sram_max_mem_depth);
			thd_wqos_in = GET_THD_WQOS_IN(sram_max_mem_depth);
			thd_wqos_out = GET_THD_WQOS_OUT(sram_max_mem_depth);
			#if 0
			thd_cg_in = GET_THD_CG_IN(sram_max_mem_depth);
			thd_cg_out = GET_THD_CG_OUT(sram_max_mem_depth);
			#else
			thd_cg_in = 0x3fff;
			thd_cg_out = 0x3fff;
			#endif
			thd_wr_wait = GET_THD_OTHER_WR_WAIT(sram_max_mem_depth);
			thd_cg_hold = GET_THD_OTHER_DFS_CG_HOLD(sram_max_mem_depth);
		} else {
			dfs_time = DFS_TIME;
			depth = DBUF1_DEPTH;

			/*
			** int K = 0;
			** int Tp = 1000000  / pinfo->pxl_clk_rate;
			** K = (pinfo->ldi.h_pulse_width + pinfo->ldi.h_back_porch + pinfo->xres +
			**	pinfo->ldi.h_front_porch) / pinfo->xres;
			** thd_cg_out = dfs_time / (Tp * K * 6);
			*/
			thd_cg_out = (dfs_time * pinfo->pxl_clk_rate * pinfo->xres) /
				((pinfo->ldi.h_pulse_width + pinfo->ldi.h_back_porch + pinfo->xres + pinfo->ldi.h_front_porch) * 6 * 1000000UL);
			sram_valid_num = thd_cg_out / depth;
			thd_cg_in = (sram_valid_num + 1) * depth - 1;

			thd_rqos_in = thd_cg_out * 85 / 100;
			thd_rqos_out = thd_cg_out;
			thd_fill_lev1 = thd_cg_in * 2 / 10;
			thd_fill_lev2 = thd_cg_in * 4 / 10;
			thd_fill_lev3 = thd_cg_in * 6 / 10;
			thd_fill_lev4 = thd_cg_in * 8 / 10;
		}
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return ;
	}

	HISI_FB_DEBUG("sram_valid_num=%d,\n"
		"thd_rqos_in=0x%x\n"
		"thd_rqos_out=0x%x\n"
		"thd_cg_in=0x%x\n"
		"thd_cg_out=0x%x\n"
		"thd_fill_lev1=0x%x\n"
		"thd_fill_lev2=0x%x\n"
		"thd_fill_lev3=0x%x\n"
		"thd_fill_lev4=0x%x\n",
		sram_valid_num,
		thd_rqos_in,
		thd_rqos_out,
		thd_cg_in,
		thd_cg_out,
		thd_fill_lev1,
		thd_fill_lev2,
		thd_fill_lev3,
		thd_fill_lev4);

	outp32(dbuf_base + DBUF_FRM_SIZE, pinfo->xres * pinfo->yres);
	outp32(dbuf_base + DBUF_FRM_HSIZE, DSS_WIDTH(pinfo->xres));
	outp32(dbuf_base + DBUF_SRAM_VALID_NUM, sram_valid_num);

	outp32(dbuf_base + DBUF_THD_RQOS, (thd_rqos_out<< 16) | thd_rqos_in);
	outp32(dbuf_base + DBUF_THD_WQOS, (thd_wqos_out << 16) | thd_wqos_in);
	outp32(dbuf_base + DBUF_THD_CG, (thd_cg_out << 16) | thd_cg_in);
	outp32(dbuf_base + DBUF_THD_OTHER, (thd_cg_hold << 16) | thd_wr_wait);
	outp32(dbuf_base + DBUF_THD_FILL_LEV0, (thd_fill_lev2 << 16) | thd_fill_lev1);
	outp32(dbuf_base + DBUF_DFS_FILL_LEV1, (thd_fill_lev4 << 16) | thd_fill_lev3);
	outp32(dbuf_base + DBUF_THD_FLUX_REQ, (thd_flux_req_out << 16) | thd_flux_req_in);

	outp32(dbuf_base + DBUF_DFS_LP_CTRL, 0x1);

	/* dfs_core_gt: use default value */
	/*set_reg(dbuf_base + DBUF_DFS_LP_CTRL, 0, 2, 26);*/
	/* ret_aft_prefetch: use default value */
	/*set_reg(dbuf_base + DBUF_DFS_LP_CTRL, 1, 1, 25);*/
	/* pd_upon_frm_end: use default value */
	/*set_reg(dbuf_base + DBUF_DFS_LP_CTRL, 1, 1, 24);*/
}

static void init_ldi_pxl_div(struct hisi_fb_data_type *hisifd)
{
	struct hisi_panel_info *pinfo = NULL;
	uint32_t ifbc_type = 0;
	uint32_t mipi_idx = 0;
	uint32_t pxl0_div2_gt_en = 0;
	uint32_t pxl0_div4_gt_en = 0;
	uint32_t pxl0_divxcfg = 0;
	uint32_t pxl0_dsi_gt_en = 0;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	ifbc_type = pinfo->ifbc_type;
	BUG_ON((ifbc_type < IFBC_TYPE_NONE) || (ifbc_type >= IFBC_TYPE_MAX));

	mipi_idx = is_dual_mipi_panel(hisifd) ? 1 : 0;

	pxl0_div2_gt_en = g_mipi_ifbc_division[mipi_idx][ifbc_type].pxl0_div2_gt_en;
	pxl0_div4_gt_en = g_mipi_ifbc_division[mipi_idx][ifbc_type].pxl0_div4_gt_en;
	pxl0_divxcfg = g_mipi_ifbc_division[mipi_idx][ifbc_type].pxl0_divxcfg;
	pxl0_dsi_gt_en = g_mipi_ifbc_division[mipi_idx][ifbc_type].pxl0_dsi_gt_en;

	set_reg(hisifd->dss_base + GLB_PXL0_DIV2_GT_EN, pxl0_div2_gt_en, 1, 0);
	set_reg(hisifd->dss_base + GLB_PXL0_DIV4_GT_EN, pxl0_div4_gt_en, 1, 0);
	set_reg(hisifd->dss_base + GLB_PXL0_GT_EN, 0x1, 1, 0);
	set_reg(hisifd->dss_base + GLB_PXL0_DSI_GT_EN, pxl0_dsi_gt_en, 2, 0);
	set_reg(hisifd->dss_base + GLB_PXL0_DIVXCFG, pxl0_divxcfg, 3, 0);
}

void init_ldi(struct hisi_fb_data_type *hisifd, bool fastboot_enable)
{
	char __iomem *ldi_base = NULL;
	struct hisi_panel_info *pinfo = NULL;
	dss_rect_t rect = {0,0,0,0};
	uint32_t te0_enable = 0;
	uint32_t te1_enable = 0;
	uint32_t te_source = 0;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI0_OFFSET;
		te0_enable = 1;
	#ifndef CONFIG_FPGA_SDP_TEST
		if (g_fpga_flag == 1) {
			set_reg(hisifd->dss_base + GLB_TP_SEL, 0x2, 2, 0);
		}
	#endif
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		te1_enable = 1;
		ldi_base = hisifd->dss_base + DSS_LDI1_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return ;
	}

	rect.x = 0;
	rect.y = 0;
	rect.w = pinfo->xres;
	rect.h = pinfo->yres;
	mipi_ifbc_get_rect(hisifd, &rect);

	init_ldi_pxl_div(hisifd);

	if (is_dual_mipi_panel(hisifd)) {
		if (is_mipi_video_panel(hisifd)) {
			outp32(ldi_base + LDI_DPI1_HRZ_CTRL0, (pinfo->ldi.h_back_porch + DSS_WIDTH(pinfo->ldi.h_pulse_width)) << 16);
			outp32(ldi_base + LDI_DPI1_HRZ_CTRL1, 0);
			outp32(ldi_base + LDI_DPI1_HRZ_CTRL2, DSS_WIDTH(rect.w));
		} else {
			outp32(ldi_base + LDI_DPI1_HRZ_CTRL0, pinfo->ldi.h_back_porch << 16);
			outp32(ldi_base + LDI_DPI1_HRZ_CTRL1, DSS_WIDTH(pinfo->ldi.h_pulse_width));
			outp32(ldi_base + LDI_DPI1_HRZ_CTRL2, DSS_WIDTH(rect.w));
		}
		outp32(ldi_base + LDI_OVERLAP_SIZE,
			pinfo->ldi.dpi0_overlap_size | (pinfo->ldi.dpi1_overlap_size << 16));

		/* dual_mode_en */
		set_reg(ldi_base + LDI_CTRL, 1, 1, 5);

		/* split mode */
		set_reg(ldi_base + LDI_CTRL, 0, 1, 16);

		//dual lcd: 0x1, dual mipi: 0x0
		set_reg(hisifd->dss_base + GLB_DSI1_CLK_SEL, 0x0, 1, 0);
	}
	if (is_mipi_video_panel(hisifd)) {
		outp32(ldi_base + LDI_DPI0_HRZ_CTRL0,
				pinfo->ldi.h_front_porch | ((pinfo->ldi.h_back_porch + DSS_WIDTH(pinfo->ldi.h_pulse_width)) << 16));
		outp32(ldi_base + LDI_DPI0_HRZ_CTRL1, 0);
		outp32(ldi_base + LDI_DPI0_HRZ_CTRL2, DSS_WIDTH(rect.w));
	} else {
		outp32(ldi_base + LDI_DPI0_HRZ_CTRL0,
				pinfo->ldi.h_front_porch | (pinfo->ldi.h_back_porch << 16));
		outp32(ldi_base + LDI_DPI0_HRZ_CTRL1, DSS_WIDTH(pinfo->ldi.h_pulse_width));
		outp32(ldi_base + LDI_DPI0_HRZ_CTRL2, DSS_WIDTH(rect.w));
	}
	outp32(ldi_base + LDI_VRT_CTRL0,
		pinfo->ldi.v_front_porch | (pinfo->ldi.v_back_porch << 16));
	outp32(ldi_base + LDI_VRT_CTRL1, DSS_HEIGHT(pinfo->ldi.v_pulse_width));
	outp32(ldi_base + LDI_VRT_CTRL2, DSS_HEIGHT(rect.h));

	outp32(ldi_base + LDI_PLR_CTRL,
		pinfo->ldi.vsync_plr | (pinfo->ldi.hsync_plr << 1) |
		(pinfo->ldi.pixelclk_plr << 2) | (pinfo->ldi.data_en_plr << 3));

	//sensorhub int msk
	//outp32(ldi_base + LDI_SH_MASK_INT, 0x0);

	// bpp
	set_reg(ldi_base + LDI_CTRL, pinfo->bpp, 2, 3);
	// bgr
	set_reg(ldi_base + LDI_CTRL, pinfo->bgr_fmt, 1, 13);

	// for ddr pmqos
	outp32(ldi_base + LDI_VINACT_MSK_LEN,
		pinfo->ldi.v_front_porch);

	//cmd event sel
	outp32(ldi_base + LDI_CMD_EVENT_SEL, 0x1);

	//outp32(ldi_base + LDI_FRM_VALID_DBG, 0x1);

	// for 1Hz LCD and mipi command LCD
	if (is_mipi_cmd_panel(hisifd)) {
		set_reg(ldi_base + LDI_DSI_CMD_MOD_CTRL, 0x1, 1, 0);
		//set_reg(ldi_base + LDI_DSI_TE_CTRL, 0x20041, 32, 0); //te_enable
		//set_reg(ldi_base + LDI_DSI_TE_CTRL, 0x20040, 32, 0); //te_disable


		//DSI_TE_CTRL
		// te_source = 0, select te_pin
		// te_source = 1, select te_triger
		te_source = 0;

		// dsi_te_hard_en
		set_reg(ldi_base + LDI_DSI_TE_CTRL, 0x1, 1, 0);
		// dsi_te0_pin_p , dsi_te1_pin_p
		set_reg(ldi_base + LDI_DSI_TE_CTRL, 0x0, 2, 1);
		// dsi_te_hard_sel
		set_reg(ldi_base + LDI_DSI_TE_CTRL, te_source, 1, 3);
		if (te_source == 0) {
			// dsi_te_pin_hd_sel
			set_reg(ldi_base + LDI_DSI_TE_CTRL, te0_enable, 1, 6);
			set_reg(ldi_base + LDI_DSI_TE_CTRL, te1_enable, 1, 7);
		} else {
			// dsi_te_tri_sel
			set_reg(ldi_base + LDI_DSI_TE_CTRL, te0_enable, 1, 4);
			set_reg(ldi_base + LDI_DSI_TE_CTRL, te1_enable, 1, 5);
		}
		// dsi_te_mask_en
		set_reg(ldi_base + LDI_DSI_TE_CTRL, 0x0, 1, 8);
		// dsi_te_mask_dis
		set_reg(ldi_base + LDI_DSI_TE_CTRL, 0x0, 4, 9);
		// dsi_te_mask_und
		set_reg(ldi_base + LDI_DSI_TE_CTRL, 0x0, 4, 13);
		// dsi_te_pin_en
		set_reg(ldi_base + LDI_DSI_TE_CTRL, 0x1, 1, 17);


		set_reg(ldi_base + LDI_DSI_TE_HS_NUM, 0x0, 32, 0);
		set_reg(ldi_base + LDI_DSI_TE_HS_WD, 0x24024, 32, 0);

		// dsi_te0_vs_wd = lcd_te_width / T_pxl_clk, experience lcd_te_width = 2us
		if (pinfo->pxl_clk_rate_div== 0) {
			HISI_FB_ERR("pxl_clk_rate_div is NULL, not support !\n");
			pinfo->pxl_clk_rate_div = 1;
		}
		set_reg(ldi_base + LDI_DSI_TE_VS_WD,
			(0x3FC << 12) | (2 * pinfo->pxl_clk_rate / pinfo->pxl_clk_rate_div / 1000000), 32, 0);
		//set_reg(ldi_base + LDI_DSI_TE_VS_WD, 0x3FC0FF, 32, 0);
		//set_reg(ldi_base + LDI_DSI_TE_VS_WD, 0x3FC01F, 32, 0);
	} else {
		set_reg(ldi_base + LDI_DSI_CMD_MOD_CTRL, 0x1, 1, 1);
	}
	//ldi_data_gate(hisifd, true);

#ifdef CONFIG_HISI_FB_COLORBAR_USED
	// colorbar width
	set_reg(ldi_base + LDI_CTRL, DSS_WIDTH(0x3c), 7, 6);
	// colorbar ort
	set_reg(ldi_base + LDI_WORK_MODE, 0x0, 1, 1);
	// colorbar enable
	set_reg(ldi_base + LDI_WORK_MODE, 0x0, 1, 0);
#else
	// normal
	set_reg(ldi_base + LDI_WORK_MODE, 0x1, 1, 0);
#endif

	if (is_mipi_cmd_panel(hisifd)) {
		set_reg(ldi_base + LDI_FRM_MSK,
			(hisifd->frame_update_flag == 1) ? 0x0 : 0x1, 1, 0);
	}

	// ldi disable
	if (!fastboot_enable)
		set_reg(ldi_base + LDI_CTRL, 0x0, 1, 0);

	HISI_FB_DEBUG("-.!\n");
}

void deinit_ldi(struct hisi_fb_data_type *hisifd)
{
	char __iomem *ldi_base = NULL;

	BUG_ON(hisifd == NULL);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI0_OFFSET;
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI1_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return ;
	}

	set_reg(ldi_base + LDI_CTRL, 0, 1, 0);
}

void enable_ldi(struct hisi_fb_data_type *hisifd)
{
	char __iomem *ldi_base = NULL;

	BUG_ON(hisifd == NULL);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI0_OFFSET;
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI1_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return ;
	}

	/* ldi enable */
	set_reg(ldi_base + LDI_CTRL, 0x1, 1, 0);
}

void disable_ldi(struct hisi_fb_data_type *hisifd)
{
	char __iomem *ldi_base = NULL;

	BUG_ON(hisifd == NULL);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI0_OFFSET;
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI1_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return ;
	}

	/* ldi disable */
	set_reg(ldi_base + LDI_CTRL, 0x0, 1, 0);
}

void ldi_frame_update(struct hisi_fb_data_type *hisifd, bool update)
{
	char __iomem *ldi_base = NULL;

	BUG_ON(hisifd == NULL);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI0_OFFSET;

		if (is_mipi_cmd_panel(hisifd)) {
			set_reg(ldi_base + LDI_FRM_MSK, (update ? 0x0 : 0x1), 1, 0);
			if (update)
				set_reg(ldi_base + LDI_CTRL, 0x1, 1, 0);
		}
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
	}
}

extern int updateCabcPwm(struct hisi_fb_data_type *hisifd);
void single_frame_update(struct hisi_fb_data_type *hisifd)
{
	char __iomem *ldi_base = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		ldi_base = hisifd->dss_base+ DSS_LDI0_OFFSET;
		if (is_mipi_cmd_panel(hisifd)) {
			set_reg(ldi_base + LDI_FRM_MSK_UP, 0x1, 1, 0);
			set_reg(ldi_base + LDI_CTRL, 0x1, 1, 0);
		} else {
			set_reg(ldi_base + LDI_CTRL, 0x1, 1, 0);
		}

		if (pinfo->blpwm_input_ena) {
			updateCabcPwm(hisifd);
		}

	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI1_OFFSET;

		if (is_mipi_cmd_panel(hisifd)) {
			set_reg(ldi_base + LDI_FRM_MSK_UP, 0x1, 1, 0);
			set_reg(ldi_base + LDI_CTRL, 0x1, 1, 0);
		} else {
			set_reg(ldi_base + LDI_CTRL, 0x1, 1, 0);
		}
	} else {
		;
	}
}

void ldi_data_gate(struct hisi_fb_data_type *hisifd, bool enble)
{
	char __iomem *ldi_base = NULL;

	BUG_ON(hisifd == NULL);

	if (!is_mipi_cmd_panel(hisifd)) {
		hisifd->ldi_data_gate_en = (enble ? 1 : 0);
		return ;
	}

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI0_OFFSET;
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		ldi_base = hisifd->dss_base + DSS_LDI1_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return ;
	}

	if (g_ldi_data_gate_en == 1) {
		hisifd->ldi_data_gate_en = (enble ? 1 : 0);
		set_reg(ldi_base + LDI_CTRL, (enble ? 0x1 : 0x0), 1, 2);
	} else {
		hisifd->ldi_data_gate_en = 0;
		set_reg(ldi_base + LDI_CTRL, 0x0, 1, 2);
	}

	HISI_FB_DEBUG("ldi_data_gate_en=%d!\n", hisifd->ldi_data_gate_en);
}

void dpe_interrupt_clear(struct hisi_fb_data_type *hisifd)
{
	char __iomem *dss_base = 0;
	uint32_t clear = 0;

	BUG_ON(hisifd == NULL);

	dss_base = hisifd->dss_base;

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		clear = ~0;
		outp32(dss_base + GLB_CPU_PDP_INTS, clear);
		outp32(dss_base + GLB_GLB_CPU_ITF0_INTS, clear);
		outp32(dss_base + GLB_GLB_DPP_INTS, clear);
		outp32(dss_base + GLB_RCH_CE_INTS, clear);

		outp32(dss_base + GLB_INTS, clear);
		outp32(dss_base + GLB_DBG_MCTL_INTS, clear);
		outp32(dss_base + GLB_DBG_WCH0_INTS, clear);
		outp32(dss_base + GLB_DBG_WCH1_INTS, clear);
		outp32(dss_base + GLB_DBG_RCH0_INTS, clear);
		outp32(dss_base + GLB_DBG_RCH1_INTS, clear);
		outp32(dss_base + GLB_DBG_RCH2_INTS, clear);
		outp32(dss_base + GLB_DBG_RCH3_INTS, clear);
		outp32(dss_base + GLB_DBG_RCH4_INTS, clear);
		outp32(dss_base + GLB_DBG_RCH5_INTS, clear);
		outp32(dss_base + GLB_DBG_RCH6_INTS, clear);
		outp32(dss_base + GLB_DBG_RCH7_INTS, clear);
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		clear = ~0;
		outp32(dss_base + GLB_CPU_SDP_INTS, clear);
		outp32(dss_base + GLB_GLB_CPU_ITF1_INTS, clear);
	} else if (hisifd->index == AUXILIARY_PANEL_IDX) {
		clear = ~0;
		outp32(dss_base + GLB_CPU_OFF_INTS, clear);
	} else {
		HISI_FB_ERR("fb%d, not support this device!\n", hisifd->index);
	}

}

void dpe_interrupt_unmask(struct hisi_fb_data_type *hisifd)
{
	char __iomem *dss_base = 0;
	uint32_t unmask = 0;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);
	dss_base = hisifd->dss_base;

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		unmask = ~0;
		//unmask &= ~(BIT_DPP_INTS | BIT_ITF0_INTS | BIT_DSS_GLB_INTS | BIT_MMU_IRPT_NS);
		unmask &= ~(BIT_DPP_INTS | BIT_ITF0_INTS | BIT_MMU_IRPT_NS);
		outp32(dss_base + GLB_CPU_PDP_INT_MSK, unmask);

		unmask = ~0;
		if (is_mipi_cmd_panel(hisifd)) {
			unmask &= ~(BIT_LCD_TE0_PIN | BIT_VACTIVE0_START | BIT_VACTIVE0_END);
		} else {
			unmask &= ~(BIT_VSYNC | BIT_VACTIVE0_START | BIT_VACTIVE0_END);
		}
		outp32(dss_base + GLB_GLB_CPU_ITF0_INT_MSK, unmask);

		unmask = ~0;
		//unmask &= ~(BIT_CE_END_IND | BIT_BACKLIGHT_INTP);
		if ((pinfo->acm_ce_support == 1) && HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_ACE))
			unmask &= ~(BIT_CE_END_IND);
		outp32(dss_base + GLB_GLB_DPP_INT_MSK, unmask);

		unmask = ~0;
		if (pinfo->prefix_ce_support == 1)
			unmask &= ~(BIT_CE_END_RCH4_IND | BIT_CE_END_RCH2_IND);
		outp32(dss_base + GLB_RCH_CE_INT_MSK, unmask);
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		unmask = ~0;
		//unmask &= ~(BIT_SDP_ITF1_INTS  | BIT_SDP_DSS_GLB_INTS | BIT_SDP_MMU_IRPT_NS);
		unmask &= ~(BIT_SDP_ITF1_INTS | BIT_SDP_MMU_IRPT_NS);
		outp32(dss_base + GLB_CPU_SDP_INT_MSK, unmask);

		unmask = ~0;
		unmask &= ~(BIT_VSYNC | BIT_VACTIVE0_START | BIT_VACTIVE0_END);
		outp32(dss_base + GLB_GLB_CPU_ITF1_INT_MSK, unmask);
	} else if (hisifd->index == AUXILIARY_PANEL_IDX) {
		unmask = ~0;
	#ifdef CONFIG_FIX_DSS_WCH_ISR_BUG
		unmask &= ~(BIT_OFF_CMDLIST8 | BIT_OFF_CMDLIST9 | BIT_OFF_MMU_IRPT_NS);
	#else
		unmask &= ~(BIT_OFF_WCH0_INTS | BIT_OFF_WCH1_INTS | BIT_OFF_WCH0_WCH1_FRM_END_INT | BIT_OFF_MMU_IRPT_NS);
	#endif
		outp32(dss_base + GLB_CPU_OFF_INT_MSK, unmask);
	} else {
		HISI_FB_ERR("fb%d, not support this device!\n", hisifd->index);
	}

}

void dpe_interrupt_mask(struct hisi_fb_data_type *hisifd)
{
	char __iomem *dss_base = 0;
	uint32_t mask = 0;

	BUG_ON(hisifd == NULL);

	dss_base = hisifd->dss_base;

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		mask = ~0;
		outp32(dss_base + GLB_CPU_PDP_INT_MSK, mask);

		mask = ~0;
		outp32(dss_base + GLB_GLB_CPU_ITF0_INT_MSK, mask);

		mask = ~0;
		outp32(dss_base + GLB_GLB_DPP_INT_MSK, mask);

		mask = ~0;
		outp32(dss_base + GLB_RCH_CE_INT_MSK, mask);

		mask = ~0;
		outp32(dss_base + GLB_INT_MSK, mask);
		outp32(dss_base + GLB_DBG_MCTL_INT_MSK, mask);
		outp32(dss_base + GLB_DBG_WCH0_INT_MSK, mask);
		outp32(dss_base + GLB_DBG_WCH1_INT_MSK, mask);
		outp32(dss_base + GLB_DBG_RCH0_INT_MSK, mask);
		outp32(dss_base + GLB_DBG_RCH1_INT_MSK, mask);
		outp32(dss_base + GLB_DBG_RCH2_INT_MSK, mask);
		outp32(dss_base + GLB_DBG_RCH3_INT_MSK, mask);
		outp32(dss_base + GLB_DBG_RCH4_INT_MSK, mask);
		outp32(dss_base + GLB_DBG_RCH5_INT_MSK, mask);
		outp32(dss_base + GLB_DBG_RCH6_INT_MSK, mask);
		outp32(dss_base + GLB_DBG_RCH7_INT_MSK, mask);
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		mask = ~0;
		outp32(dss_base + GLB_CPU_SDP_INT_MSK, mask);

		mask = ~0;
		outp32(dss_base + GLB_GLB_CPU_ITF1_INT_MSK, mask);
	} else if (hisifd->index == AUXILIARY_PANEL_IDX) {
		mask = ~0;
		outp32(dss_base + GLB_CPU_OFF_INT_MSK, mask);
	} else {
		HISI_FB_ERR("fb%d, not support this device!\n", hisifd->index);
	}

}


inline void acm_set_lut(char __iomem *address, uint32_t table[], uint32_t size)
{
	uint32_t data = 0;
	uint32_t index = 0;
	uint32_t i = 0;

	size /= 2;

	for (i = 0; i < size; i++) {
		index = i << 1;
		data = table[index] + (table[index + 1] << 8);
		outp32(address + (i << 2), data);
	}
}

inline void acm_set_lut_hue(char __iomem *address, uint32_t table[], uint32_t size)
{
	uint32_t data = 0;
	uint32_t index = 0;
	uint32_t i = 0;

	size /= 2;

	for (i = 0; i < size; i++) {
		index = i << 1;
		data = table[index] + (table[index + 1] << 16);
		outp32(address + (i << 2), data);
	}
}

void init_acm(struct hisi_fb_data_type *hisifd)
{
	char __iomem *acm_base = NULL;
	char __iomem *dpp_base = NULL;
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);
	if (pinfo->acm_support != 1) {
		HISI_FB_DEBUG("fb%d, not support acm!\n", hisifd->index);
		return;
	}

	if (!HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_ACM)) {
		return;
	}

	acm_base = hisifd->dss_base + DSS_DPP_ACM_OFFSET;
	dpp_base = hisifd->dss_base + DSS_DPP_OFFSET;

	set_reg(hisifd->dss_base + DSS_DPP_RD_SHADOW_OFFSET, 0x1, 1, 0);

	set_reg(acm_base + ACM_EN, 0x0, 1, 0);
	set_reg(acm_base + ACM_R0_H, ((pinfo->r0_hh & 0x3ff) << 16) | (pinfo->r0_lh & 0x3ff), 32, 0);
	set_reg(acm_base + ACM_R1_H, ((pinfo->r1_hh & 0x3ff) << 16) | (pinfo->r1_lh & 0x3ff), 32, 0);
	set_reg(acm_base + ACM_R2_H, ((pinfo->r2_hh & 0x3ff) << 16) | (pinfo->r2_lh & 0x3ff), 32, 0);
	set_reg(acm_base + ACM_R3_H, ((pinfo->r3_hh & 0x3ff) << 16) | (pinfo->r3_lh & 0x3ff), 32, 0);
	set_reg(acm_base + ACM_R4_H, ((pinfo->r4_hh & 0x3ff) << 16) | (pinfo->r4_lh & 0x3ff), 32, 0);
	set_reg(acm_base + ACM_R5_H, ((pinfo->r5_hh & 0x3ff) << 16) | (pinfo->r5_lh & 0x3ff), 32, 0);
	set_reg(acm_base + ACM_R6_H, ((pinfo->r6_hh & 0x3ff) << 16) | (pinfo->r6_lh & 0x3ff), 32, 0);

	if (pinfo->acm_lut_hue_table && pinfo->acm_lut_hue_table_len > 0) {
		acm_set_lut_hue(dpp_base + ACM_LUT_HUE, pinfo->acm_lut_hue_table, pinfo->acm_lut_hue_table_len);
	} else {
		HISI_FB_ERR("fb%d, acm_lut_hue_table is NULL or acm_lut_hue_table_len less than 0!\n", hisifd->index);
		return;
	}

	if (pinfo->acm_lut_sata_table && pinfo->acm_lut_sata_table_len > 0) {
		acm_set_lut(dpp_base + ACM_LUT_SATA, pinfo->acm_lut_sata_table, pinfo->acm_lut_sata_table_len);
	} else {
		HISI_FB_ERR("fb%d, acm_lut_sata_table is NULL or acm_lut_sata_table_len less than 0!\n", hisifd->index);
		return;
	}

	if (pinfo->acm_lut_satr_table && pinfo->acm_lut_satr_table_len > 0) {
		acm_set_lut(dpp_base + ACM_LUT_SATR, pinfo->acm_lut_satr_table, pinfo->acm_lut_satr_table_len);
	} else {
		HISI_FB_ERR("fb%d, acm_lut_satr_table is NULL or acm_lut_satr_table_len less than 0!\n", hisifd->index);
		return;
	}

	set_reg(acm_base + ACM_EN, 0x1, 1, 0);
	set_reg(acm_base + ACM_EN, pinfo->acm_valid_num & 0x7, 3, 4);

	set_reg(hisifd->dss_base + DSS_DPP_RD_SHADOW_OFFSET, 0x0, 1, 0);
	g_acm_State = 1;
}

static void init_acm_ce_lut(char __iomem *lut_base)
{
	int i = 0;
	for (i = 0; i < CE_VALUE_RANK; i++) {
		outp32(lut_base + i * 4, (uint32_t)i);
	}
}

void init_acm_ce(struct hisi_fb_data_type *hisifd)
{
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *dpp_base = NULL;
	char __iomem *acm_ce_base = NULL;

	BUG_ON(hisifd == NULL);

	pinfo = &(hisifd->panel_info);

	if (!pinfo->acm_ce_support) {
		return;
	}

	if (!HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_ACE)) {
		return;
	}

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		acm_ce_base = hisifd->dss_base + DSS_DPP_ACM_CE_OFFSET;
		dpp_base = hisifd->dss_base + DSS_DPP_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return ;
	}

	set_reg(acm_ce_base + ACM_CE_HIST_CTL, 0x0, 3, 0);
	set_reg(acm_ce_base + ACM_CE_HIST_FRAME_CNT, 1, 6, 0);
	set_reg(acm_ce_base + ACM_CE_SIZE,
		(DSS_WIDTH(hisifd->panel_info.xres) << 16) | (DSS_HEIGHT(hisifd->panel_info.yres)), 32, 0);
	set_reg(acm_ce_base + ACM_CE_NO_STAT_LINES, 1, 8, 0);
	set_reg(acm_ce_base + ACM_CE_BLACK_REGION_THRE, 20, 8, 0);
	set_reg(acm_ce_base + ACM_CE_WHITE_REGION_THRE, 220, 8, 0);
	// default LUT
	if ((inp32(acm_ce_base + ACM_CE_LUT_USING_IND) & 0x1) == 0) {
		init_acm_ce_lut(dpp_base + ACM_CE_LUT0_OFFSET);
		set_reg(acm_ce_base + ACM_CE_LUT_SEL, 0x1, 1, 0);
	} else {
		init_acm_ce_lut(dpp_base + ACM_CE_LUT1_OFFSET);
		set_reg(acm_ce_base + ACM_CE_LUT_SEL, 0x0, 1, 0);
	}
	//bit0: remap; bit1: hist
	set_reg(acm_ce_base + ACM_CE_LUT_ENABLE, 0x0, 2, 0);
}

void init_igm_gmp_xcc_gm(struct hisi_fb_data_type *hisifd)
{
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *dpp_base = NULL;
	char __iomem *lcp_base = NULL;
	char __iomem *gamma_base = NULL;
	uint32_t i = 0, j = 0, k = 0;
	uint32_t pos0 = 0, pos1 = 0;
	uint32_t color_temp_rectify_R = 32768, color_temp_rectify_G = 32768, color_temp_rectify_B = 32768;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		dpp_base = hisifd->dss_base + DSS_DPP_OFFSET;
		lcp_base = hisifd->dss_base + DSS_DPP_LCP_OFFSET;
		gamma_base = hisifd->dss_base + DSS_DPP_GAMMA_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!\n", hisifd->index);
		return;
	}

	if (pinfo->color_temp_rectify_support && pinfo->color_temp_rectify_R) {
		color_temp_rectify_R = pinfo->color_temp_rectify_R;
	}

	if (pinfo->color_temp_rectify_support && pinfo->color_temp_rectify_G) {
		color_temp_rectify_G = pinfo->color_temp_rectify_G;
	}

	if (pinfo->color_temp_rectify_support && pinfo->color_temp_rectify_B) {
		color_temp_rectify_B = pinfo->color_temp_rectify_B;
	}

	//GAMMA
	if (pinfo->gamma_support == 1) {
		if (!HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_GAMA)) return;

		//disable gamma
		set_reg(gamma_base + GAMA_BYPASS_EN, 0x1, 1, 0);

		//inverse gamma
		if (pinfo->igm_lut_table_len > 0
			&& pinfo->igm_lut_table_R
			&& pinfo->igm_lut_table_G
			&& pinfo->igm_lut_table_B) {
			for (i = 0; i < pinfo->igm_lut_table_len; i++) {
				outp32(dpp_base + (LUT_IGM_R_COEF_OFFSET +  i * 4), pinfo->igm_lut_table_R[i]);
				outp32(dpp_base + (LUT_IGM_G_COEF_OFFSET +  i * 4), pinfo->igm_lut_table_G[i]);
				outp32(dpp_base + (LUT_IGM_B_COEF_OFFSET +  i * 4), pinfo->igm_lut_table_B[i]);
			}
		}

		//gamma
		if (pinfo->gamma_lut_table_len > 0
			&& pinfo->gamma_lut_table_R
			&& pinfo->gamma_lut_table_G
			&& pinfo->gamma_lut_table_B) {
			for (i = 0; i < pinfo->gamma_lut_table_len; i++) {
				outp32(dpp_base + (LUT_GAMA_R_COEF_OFFSET + i * 4), pinfo->gamma_lut_table_R[i]);
				outp32(dpp_base + (LUT_GAMA_G_COEF_OFFSET + i * 4), pinfo->gamma_lut_table_G[i]);
				outp32(dpp_base + (LUT_GAMA_B_COEF_OFFSET + i * 4), pinfo->gamma_lut_table_B[i]);
			}
		}

		//0:36bit input   1:24bit input (only IGM & GAMMA)
		set_reg(gamma_base + GAMA_SHORTBIT_EN, 0x1, 1, 0);

		//enable gamma
		set_reg(gamma_base + GAMA_BYPASS_EN, 0x0, 1, 0);
	}

	// GMP
	if (pinfo->gmp_support == 1) {
		if (!HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_LCP_GMP)) return;

		//disable gmp
		set_reg(dpp_base + LCP_GMP_BYPASS_EN, 0x1, 1, 0);

		//gmp lut
		if (pinfo->gmp_lut_table_len > 0
			&& pinfo->gmp_lut_table_low32bit
			&& pinfo->gmp_lut_table_high4bit) {
			for (i = 0; i < pinfo->gmp_lut_table_len; i++) {
				pos1 = LUT_GMP_COEF_OFFSET + i * 0x800;
				for (j = 0; j < pinfo->gmp_lut_table_len; j++) {
					pos0 = pos1 + 0x80 * j;
					for (k = 0; k < pinfo->gmp_lut_table_len; k++) {
						outp32(dpp_base + pos0 +  k * 8,
							pinfo->gmp_lut_table_low32bit[(i * pinfo->gmp_lut_table_len + j) * pinfo->gmp_lut_table_len + k]);
						outp32(dpp_base + pos0 +  k * 8 + 4,
							pinfo->gmp_lut_table_high4bit[(i * pinfo->gmp_lut_table_len + j) * pinfo->gmp_lut_table_len + k]);
					}
				}
			}
		}

		//enable gmp
		set_reg(dpp_base + LCP_GMP_BYPASS_EN, 0x0, 1, 0);

		//0:36bit input (use GMP)   1:24bit input
		set_reg(gamma_base + GAMA_SHORTBIT_EN, 0x0, 1, 0);
	}

	//XCC
	if (pinfo->xcc_support == 1) {
		if (!HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_LCP_XCC)) return;
		// XCC matrix
		if (pinfo->xcc_table_len > 0 && pinfo->xcc_table) {
			outp32(lcp_base + LCP_XCC_COEF_00, pinfo->xcc_table[0]);
			outp32(lcp_base + LCP_XCC_COEF_01, pinfo->xcc_table[1]
				* g_led_rg_csc_value[0] / 32768 * color_temp_rectify_R / 32768);
			outp32(lcp_base + LCP_XCC_COEF_02, pinfo->xcc_table[2]);
			outp32(lcp_base + LCP_XCC_COEF_03, pinfo->xcc_table[3]);
			outp32(lcp_base + LCP_XCC_COEF_10, pinfo->xcc_table[4]);
			outp32(lcp_base + LCP_XCC_COEF_11, pinfo->xcc_table[5]);
			outp32(lcp_base + LCP_XCC_COEF_12, pinfo->xcc_table[6]
				* g_led_rg_csc_value[4] / 32768 * color_temp_rectify_G / 32768);
			outp32(lcp_base + LCP_XCC_COEF_13, pinfo->xcc_table[7]);
			outp32(lcp_base + LCP_XCC_COEF_20, pinfo->xcc_table[8]);
			outp32(lcp_base + LCP_XCC_COEF_21, pinfo->xcc_table[9]);
			outp32(lcp_base + LCP_XCC_COEF_22, pinfo->xcc_table[10]);
			outp32(lcp_base + LCP_XCC_COEF_23, pinfo->xcc_table[11]
				* g_led_rg_csc_value[8] / 32768 * DISCOUNT_COEFFICIENT(g_comform_value)
				* color_temp_rectify_B / 32768);
		}

		//enable xcc
		set_reg(lcp_base + LCP_XCC_BYPASS_EN, 0x0, 1, 0);

		//0:36bit input (use XCC)   1:24bit input
		set_reg(gamma_base + GAMA_SHORTBIT_EN, 0x0, 1, 0);
	}
}

void dpe_store_ct_cscValue(struct hisi_fb_data_type *hisifd, unsigned int csc_value[])
{
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	if (pinfo->xcc_support == 0 || pinfo->xcc_table == NULL) {
		return;
	}

	pinfo->xcc_table[1] = csc_value[0];
	pinfo->xcc_table[2] = csc_value[1];
	pinfo->xcc_table[3] = csc_value[2];
	pinfo->xcc_table[5] = csc_value[3];
	pinfo->xcc_table[6] = csc_value[4];
	pinfo->xcc_table[7] = csc_value[5];
	pinfo->xcc_table[9] = csc_value[6];
	pinfo->xcc_table[10] = csc_value[7];
	pinfo->xcc_table[11] = csc_value[8];

	return;
}

void dpe_update_g_comform_discount(unsigned int value)
{
    g_comform_value = value;
    HISI_FB_INFO(" g_comform_value = %d" , g_comform_value);
}

int dpe_set_ct_cscValue(struct hisi_fb_data_type *hisifd)
{
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *lcp_base = NULL;
	uint32_t color_temp_rectify_R = 32768, color_temp_rectify_G = 32768, color_temp_rectify_B = 32768;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		lcp_base = hisifd->dss_base + DSS_DPP_LCP_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return -1;
	}

	if (pinfo->color_temp_rectify_support && pinfo->color_temp_rectify_R) {
		color_temp_rectify_R = pinfo->color_temp_rectify_R;
	}

	if (pinfo->color_temp_rectify_support && pinfo->color_temp_rectify_G) {
		color_temp_rectify_G = pinfo->color_temp_rectify_G;
	}

	if (pinfo->color_temp_rectify_support && pinfo->color_temp_rectify_B) {
		color_temp_rectify_B = pinfo->color_temp_rectify_B;
	}

	//XCC
	if (pinfo->xcc_support == 1) {
		// XCC matrix
		if (pinfo->xcc_table_len > 0 && pinfo->xcc_table) {
			outp32(lcp_base + LCP_XCC_COEF_00, pinfo->xcc_table[0]);
			outp32(lcp_base + LCP_XCC_COEF_01, pinfo->xcc_table[1]
				* g_led_rg_csc_value[0] / 32768 * color_temp_rectify_R / 32768);
			outp32(lcp_base + LCP_XCC_COEF_02, pinfo->xcc_table[2]);
			outp32(lcp_base + LCP_XCC_COEF_03, pinfo->xcc_table[3]);
			outp32(lcp_base + LCP_XCC_COEF_10, pinfo->xcc_table[4]);
			outp32(lcp_base + LCP_XCC_COEF_11, pinfo->xcc_table[5]);
			outp32(lcp_base + LCP_XCC_COEF_12, pinfo->xcc_table[6]
				* g_led_rg_csc_value[4] / 32768 * color_temp_rectify_G / 32768);
			outp32(lcp_base + LCP_XCC_COEF_13, pinfo->xcc_table[7]);
			outp32(lcp_base + LCP_XCC_COEF_20, pinfo->xcc_table[8]);
			outp32(lcp_base + LCP_XCC_COEF_21, pinfo->xcc_table[9]);
			outp32(lcp_base + LCP_XCC_COEF_22, pinfo->xcc_table[10]);
			outp32(lcp_base + LCP_XCC_COEF_23, pinfo->xcc_table[11]
				* g_led_rg_csc_value[8] / 32768 * DISCOUNT_COEFFICIENT(g_comform_value)
				* color_temp_rectify_B / 32768);
			hisifd->color_temperature_flag = 2;
		}
	}

	return 0;
}

ssize_t dpe_show_ct_cscValue(struct hisi_fb_data_type *hisifd, char *buf)
{
	struct hisi_panel_info *pinfo = NULL;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	if (pinfo->xcc_support == 0 || pinfo->xcc_table == NULL) {
		return 0;
	}

	return snprintf(buf, PAGE_SIZE, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
							pinfo->xcc_table[1], pinfo->xcc_table[2], pinfo->xcc_table[3],
							pinfo->xcc_table[5], pinfo->xcc_table[6], pinfo->xcc_table[7],
							pinfo->xcc_table[9], pinfo->xcc_table[10], pinfo->xcc_table[11]);
}

int dpe_set_comform_ct_cscValue(struct hisi_fb_data_type *hisifd)
{
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *lcp_base = NULL;
	uint32_t color_temp_rectify_R = 32768, color_temp_rectify_G = 32768, color_temp_rectify_B = 32768;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		lcp_base = hisifd->dss_base + DSS_DPP_LCP_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return -1;
	}

	if (pinfo->color_temp_rectify_support && pinfo->color_temp_rectify_R) {
		color_temp_rectify_R = pinfo->color_temp_rectify_R;
	}

	if (pinfo->color_temp_rectify_support && pinfo->color_temp_rectify_G) {
		color_temp_rectify_G = pinfo->color_temp_rectify_G;
	}

	if (pinfo->color_temp_rectify_support && pinfo->color_temp_rectify_B) {
		color_temp_rectify_B = pinfo->color_temp_rectify_B;
	}

	//XCC
	if (pinfo->xcc_support == 1) {
		// XCC matrix
		if (pinfo->xcc_table_len > 0 && pinfo->xcc_table) {
			outp32(lcp_base + LCP_XCC_COEF_00, pinfo->xcc_table[0]);
			outp32(lcp_base + LCP_XCC_COEF_01, pinfo->xcc_table[1]
				* g_led_rg_csc_value[0] / 32768 * color_temp_rectify_R / 32768);
			outp32(lcp_base + LCP_XCC_COEF_02, pinfo->xcc_table[2]);
			outp32(lcp_base + LCP_XCC_COEF_03, pinfo->xcc_table[3]);
			outp32(lcp_base + LCP_XCC_COEF_10, pinfo->xcc_table[4]);
			outp32(lcp_base + LCP_XCC_COEF_11, pinfo->xcc_table[5]);
			outp32(lcp_base + LCP_XCC_COEF_12, pinfo->xcc_table[6]
				* g_led_rg_csc_value[4] / 32768 * color_temp_rectify_G / 32768);
			outp32(lcp_base + LCP_XCC_COEF_13, pinfo->xcc_table[7]);
			outp32(lcp_base + LCP_XCC_COEF_20, pinfo->xcc_table[8]);
			outp32(lcp_base + LCP_XCC_COEF_21, pinfo->xcc_table[9]);
			outp32(lcp_base + LCP_XCC_COEF_22, pinfo->xcc_table[10]);
			outp32(lcp_base + LCP_XCC_COEF_23, pinfo->xcc_table[11]
				* g_led_rg_csc_value[8] / 32768 * DISCOUNT_COEFFICIENT(g_comform_value)
				* color_temp_rectify_B / 32768);
		}
	}

	return 0;
}

ssize_t dpe_show_comform_ct_cscValue(struct hisi_fb_data_type *hisifd, char *buf)
{
	struct hisi_panel_info *pinfo = NULL;
	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	if (pinfo->xcc_support == 0 || pinfo->xcc_table == NULL) {
		return 0;
	}

	return snprintf(buf, PAGE_SIZE, "%d,%d,%d,%d,%d,%d,%d,%d,%d,g_comform_value = %d\n",
							pinfo->xcc_table[1], pinfo->xcc_table[2], pinfo->xcc_table[3],
							pinfo->xcc_table[5], pinfo->xcc_table[6], pinfo->xcc_table[7],
							pinfo->xcc_table[9], pinfo->xcc_table[10], pinfo->xcc_table[11],
							g_comform_value);
}

void dpe_init_led_rg_ct_cscValue(void)
{
	g_led_rg_csc_value[0] = 32768;
	g_led_rg_csc_value[1] = 0;
	g_led_rg_csc_value[2] = 0;
	g_led_rg_csc_value[3] = 0;
	g_led_rg_csc_value[4] = 32768;
	g_led_rg_csc_value[5] = 0;
	g_led_rg_csc_value[6] = 0;
	g_led_rg_csc_value[7] = 0;
	g_led_rg_csc_value[8] = 32768;
	g_is_led_rg_csc_set = 0;

	return;
}

void dpe_store_led_rg_ct_cscValue(unsigned int csc_value[])
{
	g_led_rg_csc_value [0] = csc_value[0];
	g_led_rg_csc_value [1] = csc_value[1];
	g_led_rg_csc_value [2] = csc_value[2];
	g_led_rg_csc_value [3] = csc_value[3];
	g_led_rg_csc_value [4] = csc_value[4];
	g_led_rg_csc_value [5] = csc_value[5];
	g_led_rg_csc_value [6] = csc_value[6];
	g_led_rg_csc_value [7] = csc_value[7];
	g_led_rg_csc_value [8] = csc_value[8];
	g_is_led_rg_csc_set = 1;

	return;
}

int dpe_set_led_rg_ct_cscValue(struct hisi_fb_data_type *hisifd)
{
	struct hisi_panel_info *pinfo = NULL;
	char __iomem *lcp_base = NULL;
	uint32_t color_temp_rectify_R = 32768, color_temp_rectify_G = 32768, color_temp_rectify_B = 32768;

	BUG_ON(hisifd == NULL);
	pinfo = &(hisifd->panel_info);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		lcp_base = hisifd->dss_base + DSS_DPP_LCP_OFFSET;
	} else {
		HISI_FB_ERR("fb%d, not support!", hisifd->index);
		return -1;
	}

	if (pinfo->color_temp_rectify_support && pinfo->color_temp_rectify_R) {
		color_temp_rectify_R = pinfo->color_temp_rectify_R;
	}

	if (pinfo->color_temp_rectify_support && pinfo->color_temp_rectify_G) {
		color_temp_rectify_G = pinfo->color_temp_rectify_G;
	}

	if (pinfo->color_temp_rectify_support && pinfo->color_temp_rectify_B) {
		color_temp_rectify_B = pinfo->color_temp_rectify_B;
	}

	//XCC
	if (1 == g_is_led_rg_csc_set && 1 == pinfo->xcc_support) {
		HISI_FB_DEBUG("real set color temperature: g_is_led_rg_csc_set = %d, R = 0x%x, G = 0x%x, B = 0x%x .\n",
				g_is_led_rg_csc_set, g_led_rg_csc_value[0], g_led_rg_csc_value[4], g_led_rg_csc_value[8]);
		// XCC matrix
		if (pinfo->xcc_table_len > 0 && pinfo->xcc_table) {
			outp32(lcp_base + LCP_XCC_COEF_00, pinfo->xcc_table[0]);
			outp32(lcp_base + LCP_XCC_COEF_01, pinfo->xcc_table[1]
				* g_led_rg_csc_value[0] / 32768 * color_temp_rectify_R / 32768);
			outp32(lcp_base + LCP_XCC_COEF_02, pinfo->xcc_table[2]);
			outp32(lcp_base + LCP_XCC_COEF_03, pinfo->xcc_table[3]);
			outp32(lcp_base + LCP_XCC_COEF_10, pinfo->xcc_table[4]);
			outp32(lcp_base + LCP_XCC_COEF_11, pinfo->xcc_table[5]);
			outp32(lcp_base + LCP_XCC_COEF_12, pinfo->xcc_table[6]
				* g_led_rg_csc_value[4] / 32768 * color_temp_rectify_G / 32768);
			outp32(lcp_base + LCP_XCC_COEF_13, pinfo->xcc_table[7]);
			outp32(lcp_base + LCP_XCC_COEF_20, pinfo->xcc_table[8]);
			outp32(lcp_base + LCP_XCC_COEF_21, pinfo->xcc_table[9]);
			outp32(lcp_base + LCP_XCC_COEF_22, pinfo->xcc_table[10]);
			outp32(lcp_base + LCP_XCC_COEF_23, pinfo->xcc_table[11]
				* g_led_rg_csc_value[8] / 32768 * DISCOUNT_COEFFICIENT(g_comform_value)
				* color_temp_rectify_B / 32768);
		}
	}

	return 0;
}

ssize_t dpe_show_led_rg_ct_cscValue(char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", g_led_rg_para1, g_led_rg_para2,
							g_led_rg_csc_value [0], g_led_rg_csc_value [1], g_led_rg_csc_value [2],
							g_led_rg_csc_value [3], g_led_rg_csc_value [4], g_led_rg_csc_value [5],
							g_led_rg_csc_value [6], g_led_rg_csc_value [7], g_led_rg_csc_value [8]);
}

ssize_t dpe_show_cinema_value(char *buf)
{
	return snprintf(buf, PAGE_SIZE, "g_cinema_value = %d\n", g_cinema_value);
}

void dpe_set_cinema_acm(struct hisi_fb_data_type *hisifd, unsigned int value)
{
	char __iomem *acm_base = NULL;
	char __iomem *dpp_base = NULL;
	struct hisi_panel_info *pinfo = NULL;

	if (hisifd == NULL) {
		return;
	}

	pinfo = &(hisifd->panel_info);
	if (pinfo->acm_support != 1) {
		HISI_FB_DEBUG("fb%d, not support acm!\n", hisifd->index);
		return;
	}

	if (!HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_ACM)) {
		return ;
	}

	acm_base = hisifd->dss_base + DSS_DPP_ACM_OFFSET;
	dpp_base = hisifd->dss_base + DSS_DPP_OFFSET;
	/*Protect other register is not modified. */
	set_reg(hisifd->dss_base + DSS_DPP_RD_SHADOW_OFFSET, 0x1, 1, 0);
	/*disable acm. */
	set_reg(acm_base + ACM_EN, 0x0, 1, 0);
	/*if value == 1,it will be into cineme mode. */
	if(1 == value) {
		/*set ACM. */
		set_reg(acm_base + ACM_R0_H, ((pinfo->cinema_r0_hh & 0x3ff) << 16) | (pinfo->cinema_r0_lh & 0x3ff), 32, 0);
		set_reg(acm_base + ACM_R1_H, ((pinfo->cinema_r1_hh & 0x3ff) << 16) | (pinfo->cinema_r1_lh & 0x3ff), 32, 0);
		set_reg(acm_base + ACM_R2_H, ((pinfo->cinema_r2_hh & 0x3ff) << 16) | (pinfo->cinema_r2_lh & 0x3ff), 32, 0);
		set_reg(acm_base + ACM_R3_H, ((pinfo->cinema_r3_hh & 0x3ff) << 16) | (pinfo->cinema_r3_lh & 0x3ff), 32, 0);
		set_reg(acm_base + ACM_R4_H, ((pinfo->cinema_r4_hh & 0x3ff) << 16) | (pinfo->cinema_r4_lh & 0x3ff), 32, 0);
		set_reg(acm_base + ACM_R5_H, ((pinfo->cinema_r5_hh & 0x3ff) << 16) | (pinfo->cinema_r5_lh & 0x3ff), 32, 0);
		set_reg(acm_base + ACM_R6_H, ((pinfo->cinema_r6_hh & 0x3ff) << 16) | (pinfo->cinema_r6_lh & 0x3ff), 32, 0);
		/*set ACM_LUT_HUE. */
		if (pinfo->cinema_acm_lut_hue_table && pinfo->cinema_acm_lut_hue_table_len > 0) {
			acm_set_lut_hue(dpp_base + ACM_LUT_HUE, pinfo->cinema_acm_lut_hue_table, pinfo->cinema_acm_lut_hue_table_len);
		} else {
			HISI_FB_ERR("fb%d, acm_lut_hue_table is NULL or acm_lut_hue_table_len less than 0!\n", hisifd->index);
			return;
		}
		/*set ACM_LUT_SATA. */
		if (pinfo->cinema_acm_lut_sata_table && pinfo->cinema_acm_lut_sata_table_len > 0) {
			acm_set_lut(dpp_base + ACM_LUT_SATA, pinfo->cinema_acm_lut_sata_table, pinfo->cinema_acm_lut_sata_table_len);
		} else {
			HISI_FB_ERR("fb%d, acm_lut_sata_table is NULL or acm_lut_sata_table_len less than 0!\n", hisifd->index);
			return;
		}
		/*set ACM_LUT_SATA. */
		if (pinfo->cinema_acm_lut_satr_table && pinfo->cinema_acm_lut_satr_table_len > 0) {
			acm_set_lut(dpp_base + ACM_LUT_SATR, pinfo->cinema_acm_lut_satr_table, pinfo->cinema_acm_lut_satr_table_len);
		} else {
			HISI_FB_ERR("fb%d, acm_lut_satr_table is NULL or acm_lut_satr_table_len less than 0!\n", hisifd->index);
			return;
		}
	} else {
		/*set ACM. */
		set_reg(acm_base + ACM_R0_H, ((pinfo->r0_hh & 0x3ff) << 16) | (pinfo->r0_lh & 0x3ff), 32, 0);
		set_reg(acm_base + ACM_R1_H, ((pinfo->r1_hh & 0x3ff) << 16) | (pinfo->r1_lh & 0x3ff), 32, 0);
		set_reg(acm_base + ACM_R2_H, ((pinfo->r2_hh & 0x3ff) << 16) | (pinfo->r2_lh & 0x3ff), 32, 0);
		set_reg(acm_base + ACM_R3_H, ((pinfo->r3_hh & 0x3ff) << 16) | (pinfo->r3_lh & 0x3ff), 32, 0);
		set_reg(acm_base + ACM_R4_H, ((pinfo->r4_hh & 0x3ff) << 16) | (pinfo->r4_lh & 0x3ff), 32, 0);
		set_reg(acm_base + ACM_R5_H, ((pinfo->r5_hh & 0x3ff) << 16) | (pinfo->r5_lh & 0x3ff), 32, 0);
		set_reg(acm_base + ACM_R6_H, ((pinfo->r6_hh & 0x3ff) << 16) | (pinfo->r6_lh & 0x3ff), 32, 0);
		/*set ACM_LUT_HUE. */
		if (pinfo->acm_lut_hue_table && pinfo->acm_lut_hue_table_len > 0) {
			acm_set_lut_hue(dpp_base + ACM_LUT_HUE, pinfo->acm_lut_hue_table, pinfo->acm_lut_hue_table_len);
		} else {
			HISI_FB_ERR("fb%d, acm_lut_hue_table is NULL or acm_lut_hue_table_len less than 0!\n", hisifd->index);
			return;
		}
		/*set ACM_LUT_SATA. */
		if (pinfo->acm_lut_sata_table && pinfo->acm_lut_sata_table_len > 0) {
			acm_set_lut(dpp_base + ACM_LUT_SATA, pinfo->acm_lut_sata_table, pinfo->acm_lut_sata_table_len);
		} else {
			HISI_FB_ERR("fb%d, acm_lut_sata_table is NULL or acm_lut_sata_table_len less than 0!\n", hisifd->index);
			return;
		}
		/*set ACM_LUT_SATR. */
		if (pinfo->acm_lut_satr_table && pinfo->acm_lut_satr_table_len > 0) {
			acm_set_lut(dpp_base + ACM_LUT_SATR, pinfo->acm_lut_satr_table, pinfo->acm_lut_satr_table_len);
		} else {
			HISI_FB_ERR("fb%d, acm_lut_satr_table is NULL or acm_lut_satr_table_len less than 0!\n", hisifd->index);
			return;
		}
	}
	/*enable acm. */
	set_reg(acm_base + ACM_EN, 0x1, 1, 0);
	if(1 == value) {
		set_reg(acm_base + ACM_EN, pinfo->cinema_acm_valid_num & 0x7, 3, 4);
	} else {
		set_reg(acm_base + ACM_EN, pinfo->acm_valid_num & 0x7, 3, 4);
	}
	/*Protect other register is not modified. */
	set_reg(hisifd->dss_base + DSS_DPP_RD_SHADOW_OFFSET, 0x0, 1, 0);

	return;
}

int dpe_set_cinema(struct hisi_fb_data_type *hisifd, unsigned int value)
{
	if (hisifd == NULL) {
		return -1;
	}

	if(value == g_cinema_value)
	{
		HISI_FB_DEBUG("fb%d, cinema mode is already in %d!\n", hisifd->index, value);
		return -1;
	}

	dpe_set_cinema_acm(hisifd, value);

	g_cinema_value = value;
	hisifd->panel_info.gamma_type = g_cinema_value;
	return 0;
}

void dpe_update_g_acm_state(unsigned int value)
{
	g_acm_State = value;
}

void dpe_set_acm_state(struct hisi_fb_data_type *hisifd)
{
	char __iomem *acm_base = NULL;
	struct hisi_panel_info *pinfo = NULL;

	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer!\n");
		return;
	}

	pinfo = &(hisifd->panel_info);
	if (pinfo->acm_support != 1) {
		HISI_FB_DEBUG("fb%d, not support acm!\n", hisifd->index);
		return;
	}

	acm_base = hisifd->dss_base + DSS_DPP_ACM_OFFSET;
	if (0 == g_acm_State) {
		set_reg(acm_base + ACM_EN, 0x0, 1, 0);
	} else {
		set_reg(acm_base + ACM_EN, 0x1, 1, 0);
	}
}

ssize_t dpe_show_acm_state(char *buf)
{
	ssize_t ret = 0;

	if (NULL == buf) {
		HISI_FB_ERR("NULL Pointer!\n");
		return 0;
	}

	ret = snprintf(buf, PAGE_SIZE, "g_acm_State = %d\n", g_acm_State);
	return ret;
}


