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

#include "hisi_overlay_utils.h"


/*dss_chn_idx
	DSS_RCHN_D2 = 0,	DSS_RCHN_D3,	DSS_RCHN_V0,	DSS_RCHN_G0,	DSS_RCHN_V1,
	DSS_RCHN_G1,	DSS_RCHN_D0,	DSS_RCHN_D1,	DSS_WCHN_W0,	DSS_WCHN_W1,
	DSS_RCHN_V2,   DSS_WCHN_W2,
*/
uint32_t g_dss_module_base[DSS_CHN_MAX_DEFINE][MODULE_CHN_MAX] = {
	/* D0 */
	{
	MIF_CH0_OFFSET,   //MODULE_MIF_CHN
	AIF0_CH0_OFFSET,  //MODULE_AIF0_CHN
	AIF1_CH0_OFFSET,  //MODULE_AIF1_CHN
	MCTL_CTL_MUTEX_RCH0,  //MODULE_MCTL_CHN_MUTEX
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH0_FLUSH_EN,  //MODULE_MCTL_CHN_FLUSH_EN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH0_OV_OEN,  //MODULE_MCTL_CHN_OV_OEN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH0_STARTY,  //MODULE_MCTL_CHN_STARTY
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD0_DBG,  //MODULE_MCTL_CHN_MOD_DBG
	DSS_RCH_D0_DMA_OFFSET,  //MODULE_DMA
	DSS_RCH_D0_DFC_OFFSET,  //MODULE_DFC
	0,  //MODULE_SCL
	0,  //MODULE_SCL_LUT
	0,  //MODULE_ARSR2P
	0,  //MODULE_ARSR2P_LUT
	0,  //MODULE_POST_CLIP
	0,  //MODULE_PCSC
	DSS_RCH_D0_CSC_OFFSET,  //MODULE_CSC
	DSS_RCH_D0_DEBUG_OFFSET,  //MODULE_DEBUG
	0,  //MODULE_VPP
	DSS_RCH_D0_DMA_BUF_OFFSET,  //MODULE_DMA_BUF
	0,  //MODULE_ROT
	DSS_RCH_D0_AFBCD_OFFSET,  //MODULE_AFBCD
	0  //MODULE_AFBCE
	},

	/* D1 */
	{
	MIF_CH1_OFFSET,   //MODULE_MIF_CHN
	AIF0_CH1_OFFSET,  //MODULE_AIF0_CHN
	AIF1_CH1_OFFSET,  //MODULE_AIF1_CHN
	MCTL_CTL_MUTEX_RCH1,  //MODULE_MCTL_CHN_MUTEX
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH1_FLUSH_EN,  //MODULE_MCTL_CHN_FLUSH_EN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH1_OV_OEN,  //MODULE_MCTL_CHN_OV_OEN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH1_STARTY,  //MODULE_MCTL_CHN_STARTY
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD1_DBG,  //MODULE_MCTL_CHN_MOD_DBG
	DSS_RCH_D1_DMA_OFFSET,  //MODULE_DMA
	DSS_RCH_D1_DFC_OFFSET,  //MODULE_DFC
	0,  //MODULE_SCL
	0,  //MODULE_SCL_LUT
	0,  //MODULE_ARSR2P
	0,  //MODULE_ARSR2P_LUT
	0,  //MODULE_POST_CLIP
	0,  //MODULE_PCSC
	DSS_RCH_D1_CSC_OFFSET,  //MODULE_CSC
	DSS_RCH_D1_DEBUG_OFFSET,  //MODULE_DEBUG
	0,  //MODULE_VPP
	DSS_RCH_D1_DMA_BUF_OFFSET,  //MODULE_DMA_BUF
	0,  //MODULE_ROT
	0,  //MODULE_AFBCD
	0  //MODULE_AFBCE
	},

	/* V0 */
	{
	MIF_CH2_OFFSET,   //MODULE_MIF_CHN
	AIF0_CH2_OFFSET,  //MODULE_AIF0_CHN
	AIF1_CH2_OFFSET,  //MODULE_AIF1_CHN
	MCTL_CTL_MUTEX_RCH2,  //MODULE_MCTL_CHN_MUTEX
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH2_FLUSH_EN,  //MODULE_MCTL_CHN_FLUSH_EN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH2_OV_OEN,  //MODULE_MCTL_CHN_OV_OEN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH2_STARTY,  //MODULE_MCTL_CHN_STARTY
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD2_DBG,  //MODULE_MCTL_CHN_MOD_DBG
	DSS_RCH_VG0_DMA_OFFSET,  //MODULE_DMA
	DSS_RCH_VG0_DFC_OFFSET,  //MODULE_DFC
	DSS_RCH_VG0_SCL_OFFSET,  //MODULE_SCL
	DSS_RCH_VG0_SCL_LUT_OFFSET,  //MODULE_SCL_LUT
	DSS_RCH_VG0_ARSR_OFFSET,  //MODULE_ARSR2P
	DSS_RCH_VG0_ARSR_LUT_OFFSET,  //MODULE_ARSR2P_LUT
	DSS_RCH_VG0_POST_CLIP_OFFSET,  //MODULE_POST_CLIP
	DSS_RCH_VG0_PCSC_OFFSET,  //MODULE_PCSC
	DSS_RCH_VG0_CSC_OFFSET,  //MODULE_CSC
	DSS_RCH_VG0_DEBUG_OFFSET,  //MODULE_DEBUG
	DSS_RCH_VG0_VPP_OFFSET,  //MODULE_VPP
	DSS_RCH_VG0_DMA_BUF_OFFSET,  //MODULE_DMA_BUF
	0,  //MODULE_ROT
	DSS_RCH_VG0_AFBCD_OFFSET,  //MODULE_AFBCD
	0  //MODULE_AFBCE
	},

	/* G0 */
	{
	MIF_CH3_OFFSET,   //MODULE_MIF_CHN
	AIF0_CH3_OFFSET,  //MODULE_AIF0_CHN
	AIF1_CH3_OFFSET,  //MODULE_AIF1_CHN
	MCTL_CTL_MUTEX_RCH3,  //MODULE_MCTL_CHN_MUTEX
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH3_FLUSH_EN,  //MODULE_MCTL_CHN_FLUSH_EN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH3_OV_OEN,  //MODULE_MCTL_CHN_OV_OEN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH3_STARTY,  //MODULE_MCTL_CHN_STARTY
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD3_DBG,  //MODULE_MCTL_CHN_MOD_DBG
	DSS_RCH_G0_DMA_OFFSET,  //MODULE_DMA
	DSS_RCH_G0_DFC_OFFSET,  //MODULE_DFC
	DSS_RCH_G0_SCL_OFFSET,  //MODULE_SCL
	0,  //MODULE_SCL_LUT
	0,  //MODULE_ARSR2P
	0,  //MODULE_ARSR2P_LUT
	DSS_RCH_G0_POST_CLIP_OFFSET,  //MODULE_POST_CLIP
	0,  //MODULE_PCSC
	DSS_RCH_G0_CSC_OFFSET,  //MODULE_CSC
	DSS_RCH_G0_DEBUG_OFFSET,  //MODULE_DEBUG
	0,  //MODULE_VPP
	DSS_RCH_G0_DMA_BUF_OFFSET,  //MODULE_DMA_BUF
	0,  //MODULE_ROT
	DSS_RCH_G0_AFBCD_OFFSET,  //MODULE_AFBCD
	0  //MODULE_AFBCE
	},

	/* V1 */
	{
	MIF_CH4_OFFSET,   //MODULE_MIF_CHN
	AIF0_CH4_OFFSET,  //MODULE_AIF0_CHN
	AIF1_CH4_OFFSET,  //MODULE_AIF1_CHN
	MCTL_CTL_MUTEX_RCH4,  //MODULE_MCTL_CHN_MUTEX
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH4_FLUSH_EN,  //MODULE_MCTL_CHN_FLUSH_EN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH4_OV_OEN,  //MODULE_MCTL_CHN_OV_OEN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH4_STARTY,  //MODULE_MCTL_CHN_STARTY
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD4_DBG,  //MODULE_MCTL_CHN_MOD_DBG
	DSS_RCH_VG1_DMA_OFFSET,  //MODULE_DMA
	DSS_RCH_VG1_DFC_OFFSET,  //MODULE_DFC
	DSS_RCH_VG1_SCL_OFFSET,  //MODULE_SCL
	DSS_RCH_VG1_SCL_LUT_OFFSET,  //MODULE_SCL_LUT
	0,  //MODULE_ARSR2P
	0,  //MODULE_ARSR2P_LUT
	DSS_RCH_VG1_POST_CLIP_OFFSET,  //MODULE_POST_CLIP
	0,  //MODULE_PCSC
	DSS_RCH_VG1_CSC_OFFSET,  //MODULE_CSC
	DSS_RCH_VG1_DEBUG_OFFSET,  //MODULE_DEBUG
	DSS_RCH_VG1_VPP_OFFSET,  //MODULE_VPP
	DSS_RCH_VG1_DMA_BUF_OFFSET,  //MODULE_DMA_BUF
	0,  //MODULE_ROT
	DSS_RCH_VG1_AFBCD_OFFSET,  //MODULE_AFBCD
	0  //MODULE_AFBCE
	},

	/* G1 */
	{
	MIF_CH5_OFFSET,   //MODULE_MIF_CHN
	AIF0_CH5_OFFSET,  //MODULE_AIF0_CHN
	AIF1_CH5_OFFSET,  //MODULE_AIF1_CHN
	MCTL_CTL_MUTEX_RCH5,  //MODULE_MCTL_CHN_MUTEX
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH5_FLUSH_EN,  //MODULE_MCTL_CHN_FLUSH_EN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH5_OV_OEN,  //MODULE_MCTL_CHN_OV_OEN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH5_STARTY,  //MODULE_MCTL_CHN_STARTY
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD5_DBG,  //MODULE_MCTL_CHN_MOD_DBG
	DSS_RCH_G1_DMA_OFFSET,  //MODULE_DMA
	DSS_RCH_G1_DFC_OFFSET,  //MODULE_DFC
	DSS_RCH_G1_SCL_OFFSET,  //MODULE_SCL
	0,  //MODULE_SCL_LUT
	0,  //MODULE_ARSR2P
	0,  //MODULE_ARSR2P_LUT
	DSS_RCH_G1_POST_CLIP_OFFSET,  //MODULE_POST_CLIP
	0,  //MODULE_PCSC
	DSS_RCH_G1_CSC_OFFSET,  //MODULE_CSC
	DSS_RCH_G1_DEBUG_OFFSET,  //MODULE_DEBUG
	0,  //MODULE_VPP
	DSS_RCH_G1_DMA_BUF_OFFSET,  //MODULE_DMA_BUF
	0,  //MODULE_ROT
	DSS_RCH_G1_AFBCD_OFFSET,  //MODULE_AFBCD
	0  //MODULE_AFBCE
	},

	/* D2 */
	{
	MIF_CH6_OFFSET,   //MODULE_MIF_CHN
	AIF0_CH6_OFFSET,  //MODULE_AIF0_CHN
	AIF1_CH6_OFFSET,  //MODULE_AIF1_CHN
	MCTL_CTL_MUTEX_RCH6,  //MODULE_MCTL_CHN_MUTEX
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH6_FLUSH_EN,  //MODULE_MCTL_CHN_FLUSH_EN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH6_OV_OEN,  //MODULE_MCTL_CHN_OV_OEN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH6_STARTY,  //MODULE_MCTL_CHN_STARTY
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD6_DBG,  //MODULE_MCTL_CHN_MOD_DBG
	DSS_RCH_D2_DMA_OFFSET,  //MODULE_DMA
	DSS_RCH_D2_DFC_OFFSET,  //MODULE_DFC
	0,  //MODULE_SCL
	0,  //MODULE_SCL_LUT
	0,  //MODULE_ARSR2P
	0,  //MODULE_ARSR2P_LUT
	0,  //MODULE_POST_CLIP
	0,  //MODULE_PCSC
	DSS_RCH_D2_CSC_OFFSET,  //MODULE_CSC
	DSS_RCH_D2_DEBUG_OFFSET,  //MODULE_DEBUG
	0,  //MODULE_VPP
	DSS_RCH_D2_DMA_BUF_OFFSET,  //MODULE_DMA_BUF
	0,  //MODULE_ROT
	0,  //MODULE_AFBCD
	0  //MODULE_AFBCE
	},

	/* D3 */
	{
	MIF_CH7_OFFSET,   //MODULE_MIF_CHN
	AIF0_CH7_OFFSET,  //MODULE_AIF0_CHN
	AIF1_CH7_OFFSET,  //MODULE_AIF1_CHN
	MCTL_CTL_MUTEX_RCH7,  //MODULE_MCTL_CHN_MUTEX
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH7_FLUSH_EN,  //MODULE_MCTL_CHN_FLUSH_EN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH7_OV_OEN,  //MODULE_MCTL_CHN_OV_OEN
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH7_STARTY,  //MODULE_MCTL_CHN_STARTY
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD7_DBG,  //MODULE_MCTL_CHN_MOD_DBG
	DSS_RCH_D3_DMA_OFFSET,  //MODULE_DMA
	DSS_RCH_D3_DFC_OFFSET,  //MODULE_DFC
	0,  //MODULE_SCL
	0,  //MODULE_SCL_LUT
	0,  //MODULE_ARSR2P
	0,  //MODULE_ARSR2P_LUT
	0,  //MODULE_POST_CLIP
	0,  //MODULE_PCSC
	DSS_RCH_D3_CSC_OFFSET,  //MODULE_CSC
	DSS_RCH_D3_DEBUG_OFFSET,  //MODULE_DEBUG
	0,  //MODULE_VPP
	DSS_RCH_D3_DMA_BUF_OFFSET,  //MODULE_DMA_BUF
	0,  //MODULE_ROT
	0,  //MODULE_AFBCD
	0  //MODULE_AFBCE
	},

	/* W0 */
	{
	MIF_CH8_OFFSET,   //MODULE_MIF_CHN
	AIF0_CH8_OFFSET,  //MODULE_AIF0_CHN
	AIF1_CH8_OFFSET,  //MODULE_AIF1_CHN
	MCTL_CTL_MUTEX_WCH0,  //MODULE_MCTL_CHN_MUTEX
	DSS_MCTRL_SYS_OFFSET + MCTL_WCH0_FLUSH_EN,  //MODULE_MCTL_CHN_FLUSH_EN
	DSS_MCTRL_SYS_OFFSET + MCTL_WCH0_OV_IEN,  //MODULE_MCTL_CHN_OV_OEN
	0,  //MODULE_MCTL_CHN_STARTY
	0,  //MODULE_MCTL_CHN_MOD_DBG
	DSS_WCH0_DMA_OFFSET,  //MODULE_DMA
	DSS_WCH0_DFC_OFFSET,  //MODULE_DFC
	0,  //MODULE_SCL
	0,  //MODULE_SCL_LUT
	0,  //MODULE_ARSR2P
	0,  //MODULE_ARSR2P_LUT
	0,  //MODULE_POST_CLIP
	0,  //MODULE_PCSC
	DSS_WCH0_CSC_OFFSET,  //MODULE_CSC
	DSS_WCH0_DEBUG_OFFSET,  //MODULE_DEBUG
	0,  //MODULE_VPP
	DSS_WCH0_DMA_BUFFER_OFFSET,  //MODULE_DMA_BUF
	DSS_WCH0_ROT_OFFSET,  //MODULE_ROT
	0,  //MODULE_AFBCD
	DSS_WCH0_AFBCE_OFFSET  //MODULE_AFBCE
	},

	/* W1 */
	{
	MIF_CH9_OFFSET,   //MODULE_MIF_CHN
	AIF0_CH9_OFFSET,  //MODULE_AIF0_CHN
	AIF1_CH9_OFFSET,  //MODULE_AIF1_CHN
	MCTL_CTL_MUTEX_WCH1,  //MODULE_MCTL_CHN_MUTEX
	DSS_MCTRL_SYS_OFFSET + MCTL_WCH1_FLUSH_EN,  //MODULE_MCTL_CHN_FLUSH_EN
	DSS_MCTRL_SYS_OFFSET + MCTL_WCH1_OV_IEN,  //MODULE_MCTL_CHN_OV_OEN
	0,  //MODULE_MCTL_CHN_STARTY
	0,  //MODULE_MCTL_CHN_MOD_DBG
	DSS_WCH1_DMA_OFFSET,  //MODULE_DMA
	DSS_WCH1_DFC_OFFSET,  //MODULE_DFC
	0,  //MODULE_SCL
	0,  //MODULE_SCL_LUT
	0,  //MODULE_ARSR2P
	0,  //MODULE_ARSR2P_LUT
	0,  //MODULE_POST_CLIP
	0,  //MODULE_PCSC
	DSS_WCH1_CSC_OFFSET,  //MODULE_CSC
	DSS_WCH1_DEBUG_OFFSET,  //MODULE_DEBUG
	0,  //MODULE_VPP
	DSS_WCH1_DMA_BUFFER_OFFSET,  //MODULE_DMA_BUF
	DSS_WCH1_ROT_OFFSET,  //MODULE_ROT
	0,  //MODULE_AFBCD
	DSS_WCH1_AFBCE_OFFSET  //MODULE_AFBCE
	},
	/* V2 */
	{
	MIF_CH10_OFFSET,   //MODULE_MIF_CHN
	AIF0_CH10_OFFSET,  //MODULE_AIF0_CHN
	AIF1_CH10_OFFSET,  //MODULE_AIF1_CHN
	MCTL_CTL_MUTEX_RCH8,  //MODULE_MCTL_CHN_MUTEX
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH8_FLUSH_EN,  //MODULE_MCTL_CHN_FLUSH_EN
	0,  //MODULE_MCTL_CHN_OV_OEN
	0,  //MODULE_MCTL_CHN_STARTY
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD8_DBG,  //MODULE_MCTL_CHN_MOD_DBG
	DSS_RCH_VG2_DMA_OFFSET,  //MODULE_DMA
	DSS_RCH_VG2_DFC_OFFSET,  //MODULE_DFC
	DSS_RCH_VG2_SCL_OFFSET,  //MODULE_SCL
	DSS_RCH_VG2_SCL_LUT_OFFSET,  //MODULE_SCL_LUT
	0,  //MODULE_ARSR2P
	0,  //MODULE_ARSR2P_LUT
	DSS_RCH_VG2_POST_CLIP_OFFSET,  //MODULE_POST_CLIP
	0,  //MODULE_PCSC
	DSS_RCH_VG2_CSC_OFFSET,  //MODULE_CSC
	DSS_RCH_VG2_DEBUG_OFFSET,  //MODULE_DEBUG
	DSS_RCH_VG2_VPP_OFFSET,  //MODULE_VPP
	DSS_RCH_VG2_DMA_BUF_OFFSET,  //MODULE_DMA_BUF
	0,  //MODULE_ROT
	DSS_RCH_VG2_AFBCD_OFFSET,  //MODULE_AFBCD
	0  //MODULE_AFBCE
	},
	/* W2 */
	{
	MIF_CH11_OFFSET,   //MODULE_MIF_CHN
	AIF0_CH11_OFFSET,  //MODULE_AIF0_CHN
	AIF1_CH11_OFFSET,  //MODULE_AIF1_CHN
	MCTL_CTL_MUTEX_WCH2,  //MODULE_MCTL_CHN_MUTEX
	DSS_MCTRL_SYS_OFFSET + MCTL_WCH2_FLUSH_EN,  //MODULE_MCTL_CHN_FLUSH_EN
	0,  //MODULE_MCTL_CHN_OV_OEN
	0,  //MODULE_MCTL_CHN_STARTY
	0,  //MODULE_MCTL_CHN_MOD_DBG
	DSS_WCH2_DMA_OFFSET,  //MODULE_DMA
	DSS_WCH2_DFC_OFFSET,  //MODULE_DFC
	0,  //MODULE_SCL
	0,  //MODULE_SCL_LUT
	0,  //MODULE_ARSR2P
	0,  //MODULE_ARSR2P_LUT
	0,  //MODULE_POST_CLIP
	0,  //MODULE_PCSC
	DSS_WCH2_CSC_OFFSET,  //MODULE_CSC
	DSS_WCH2_DEBUG_OFFSET,  //MODULE_DEBUG
	0,  //MODULE_VPP
	DSS_WCH2_DMA_BUFFER_OFFSET,  //MODULE_DMA_BUF
	DSS_WCH2_ROT_OFFSET,  //MODULE_ROT
	0,  //MODULE_AFBCD
	DSS_WCH2_AFBCE_OFFSET  //MODULE_AFBCE
	},
};

uint32_t g_dss_module_ovl_base[DSS_OVL_IDX_MAX][MODULE_OVL_MAX] = {
	{DSS_OVL0_OFFSET,
	DSS_MCTRL_CTL0_OFFSET},

	{DSS_OVL1_OFFSET,
	DSS_MCTRL_CTL1_OFFSET},

	{DSS_OVL2_OFFSET,
	DSS_MCTRL_CTL2_OFFSET},

	{DSS_OVL3_OFFSET,
	DSS_MCTRL_CTL3_OFFSET},
};

//SCF_LUT_CHN coef_idx
int g_scf_lut_chn_coef_idx[DSS_CHN_MAX_DEFINE] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

uint32_t g_dss_module_cap[DSS_CHN_MAX_DEFINE][MODULE_CAP_MAX] = {
	/* D2 */
	{0,0,1,0,0,0,1,0,0,0,1},
	/* D3 */
	{0,0,1,0,0,0,0,0,0,0,1},
	/* V0 */
	{0,1,1,0,1,1,1,0,0,1,1},
	/* G0 */
	{0,1,0,0,0,0,1,0,0,0,0},
	/* V1 */
	{0,1,1,1,0,1,1,0,1,1,1},
	/* G1 */
	{0,1,0,0,0,0,1,0,0,0,0},
	/* D0 */
	{0,0,1,0,0,0,0,0,0,0,1},
	/* D1 */
	{0,0,1,0,0,0,0,0,0,0,1},

	/* W0 */
	{1,0,1,0,0,0,0,1,0,1,1},
	/* W1 */
	{1,0,1,0,0,0,0,1,0,1,1},

	/* V2 */
	{0,1,1,1,0,1,1,0,1,1,1},
	/* W2 */
	{1,0,1,0,0,0,0,1,0,1,1},
};

/* number of smrx idx for each channel */
uint32_t g_dss_chn_sid_num[DSS_CHN_MAX_DEFINE] = {
    4, 1, 4, 4, 4, 4, 1, 1, 3, 3, 3, 2
};

/* start idx of each channel */
/* smrx_idx = g_dss_smmu_smrx_idx[chn_idx] + (0 ~ g_dss_chn_sid_num[chn_idx]) */
uint32_t g_dss_smmu_smrx_idx[DSS_CHN_MAX_DEFINE] = {
    0, 4, 5, 9, 13, 17, 21, 22, 26, 29, 23, 32
};

uint32_t g_fpga_flag = 1;
//static int g_dss_module_resource_initialized = 0;
void *g_smmu_rwerraddr_virt = NULL;

static void aif_bw_sort(dss_aif_bw_t a[], int n)
{
	int i = 0;
	int j = 0;
	dss_aif_bw_t tmp;

	for (; i < n; ++i) {
		for (j = i; j < n - 1; ++j) {
			if (a[j].bw > a[j+1].bw) {
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
}

int hisi_dss_aif_handler(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req, dss_overlay_block_t *pov_h_block)
{
	int i = 0;
	int k = 0;
	dss_layer_t *layer = NULL;
	dss_wb_layer_t *wb_layer = NULL;
	int chn_idx = 0;
	dss_aif_bw_t *aif_bw = NULL;
	uint32_t tmp = 0;
	uint32_t bw_sum = 0;

	int rch_cnt = 0;
	int axi0_cnt = 0;
	int axi1_cnt = 0;
	dss_aif_bw_t aif_bw_tmp[DSS_CHN_MAX_DEFINE];

	dss_aif_bw_t *aif1_bw = NULL;

	BUG_ON(hisifd == NULL);
	BUG_ON(pov_req == NULL);
	BUG_ON(pov_h_block== NULL);

	memset(aif_bw_tmp, 0, sizeof(aif_bw_tmp));

	if (pov_req->wb_enable) {
		for (k = 0; k < pov_req->wb_layer_nums; k++) {
			wb_layer = &(pov_req->wb_layer_infos[k]);
			chn_idx = wb_layer->chn_idx;

			//
			aif_bw = &(hisifd->dss_module.aif_bw[chn_idx]);
			aif_bw->bw = wb_layer->dst.buf_size *
				(wb_layer->src_rect.w * wb_layer->src_rect.h) / (wb_layer->dst.width * wb_layer->dst.height);
			aif_bw->chn_idx = chn_idx;
			aif_bw->axi_sel = AXI_CHN1;
			aif_bw->is_used = 1;
		}
	}

	rch_cnt = 0;
	//i is not chn_idx, is array idx
	for (i = 0; i < pov_h_block->layer_nums; i++) {
		layer = &pov_h_block->layer_infos[i];
		chn_idx = layer->chn_idx;

		if (layer->need_cap & (CAP_BASE | CAP_DIM | CAP_PURE_COLOR))
			continue;

		//MMBUF
		if (layer->need_cap & CAP_AFBCD) {
			aif1_bw = &(hisifd->dss_module.aif1_bw[chn_idx]);
			aif1_bw->is_used = 1;
			aif1_bw->chn_idx = chn_idx;
			if ((pov_req->ovl_idx == DSS_OVL0) ||
				(pov_req->ovl_idx == DSS_OVL1)) {
				if ((i % 2) == 0) {
					aif1_bw->axi_sel = AXI_CHN0;
				} else {
					aif1_bw->axi_sel = AXI_CHN1;
				}
			} else {
				if ((i % 2) == 0) {
					aif1_bw->axi_sel = AXI_CHN1;
				} else {
					aif1_bw->axi_sel = AXI_CHN0;
				}
			}

			if (g_debug_ovl_online_composer || g_debug_ovl_offline_composer) {
				HISI_FB_INFO("fb%d, aif1, chn_idx=%d, axi_sel=%d.\n",
					hisifd->index, chn_idx, aif1_bw->axi_sel);
			}
		}

		//
		aif_bw_tmp[i].bw = layer->img.buf_size *
			(layer->src_rect.w * layer->src_rect.h) / (layer->img.width * layer->img.height);
		aif_bw_tmp[i].chn_idx = chn_idx;
		aif_bw_tmp[i].axi_sel = 0;
		aif_bw_tmp[i].is_used = 1;

		bw_sum += aif_bw_tmp[i].bw;
		rch_cnt++;
	}

	//sort
	aif_bw_sort(aif_bw_tmp, rch_cnt);

	//i is not chn_idx, is array idx
	for (i = 0; i < DSS_CHN_MAX_DEFINE; i++) {
		if (aif_bw_tmp[i].is_used != 1)
			continue;

		tmp += aif_bw_tmp[i].bw;

		if ((pov_req->ovl_idx == DSS_OVL0) || (pov_req->ovl_idx == DSS_OVL1)) {
			if (tmp <= (bw_sum / 2)) {
				aif_bw_tmp[i].axi_sel = AXI_CHN0;
				if (axi0_cnt >= AXI0_MAX_DSS_CHN_THRESHOLD) {
					aif_bw_tmp[i - AXI0_MAX_DSS_CHN_THRESHOLD].axi_sel = AXI_CHN1;
					axi1_cnt++;
					axi0_cnt--;
				}
				axi0_cnt++;
			} else {
				aif_bw_tmp[i].axi_sel = AXI_CHN1;
				axi1_cnt++;
			}
		} else {
			if (tmp <= (bw_sum / 2)) {
				aif_bw_tmp[i].axi_sel = AXI_CHN1;
				if (axi1_cnt >= AXI1_MAX_DSS_CHN_THRESHOLD) {
					aif_bw_tmp[i - AXI1_MAX_DSS_CHN_THRESHOLD].axi_sel = AXI_CHN0;
					axi0_cnt++;
					axi1_cnt--;
				}
				axi1_cnt++;
			} else {
				aif_bw_tmp[i].axi_sel = AXI_CHN0;
				axi0_cnt++;
			}
		}

		chn_idx = aif_bw_tmp[i].chn_idx;
		hisifd->dss_module.aif_bw[chn_idx] = aif_bw_tmp[i];

		if (g_debug_ovl_online_composer || g_debug_ovl_offline_composer) {
			HISI_FB_INFO("fb%d, aif0, chn_idx=%d, axi_sel=%d, bw=%u.\n",
				hisifd->index, chn_idx, aif_bw_tmp[i].axi_sel, aif_bw_tmp[i].bw);
		}
	}

	return 0;
}

void hisi_dss_qos_on(struct hisi_fb_data_type *hisifd)
{
	return;
}

/*******************************************************************************
** DSS AIF
*/
static int mid_array[DSS_CHN_MAX_DEFINE] = {0xb, 0xa, 0x9, 0x8, 0x7, 0x6, 0x5, 0x4, 0x1, 0x3, 0x2, 0x0};
#define CREDIT_STEP_LOWER_ENABLE  //to be deleted

void hisi_dss_aif_init(char __iomem *aif_ch_base,
	dss_aif_t *s_aif)
{
	BUG_ON(aif_ch_base == NULL);
	BUG_ON(s_aif == NULL);

	memset(s_aif, 0, sizeof(dss_aif_t));

	s_aif->aif_ch_ctl = inp32(aif_ch_base + AIF_CH_CTL);
	s_aif->aif_ch_ctl_add = inp32(aif_ch_base + AIF_CH_CTL_ADD);
}

void hisi_dss_aif_ch_set_reg(struct hisi_fb_data_type *hisifd,
	char __iomem *aif_ch_base, dss_aif_t *s_aif)
{
	BUG_ON(hisifd == NULL);
	BUG_ON(aif_ch_base == NULL);
	BUG_ON(s_aif == NULL);

	hisifd->set_reg(hisifd, aif_ch_base + AIF_CH_CTL,
		s_aif->aif_ch_ctl, 32, 0);
	hisifd->set_reg(hisifd, aif_ch_base + AIF_CH_CTL_ADD,
		s_aif->aif_ch_ctl_add, 32, 0);
}

int hisi_dss_aif_ch_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req,
	dss_layer_t *layer, dss_rect_t *wb_dst_rect, dss_wb_layer_t *wb_layer, int ovl_idx)
{
	dss_aif_t *aif = NULL;
	dss_aif_bw_t *aif_bw = NULL;
	int chn_idx = 0;
	int mid = 0;
	uint32_t credit_step = 0;
	uint64_t dss_core_rate = 0;
	uint32_t scfd_h = 0;
	uint32_t scfd_v = 0;
	uint32_t online_offline_rate = 1;

	BUG_ON(hisifd == NULL);
	BUG_ON(pov_req == NULL);
	BUG_ON((layer == NULL) && (wb_layer == NULL));
	BUG_ON((ovl_idx < DSS_OVL0) || (ovl_idx >= DSS_OVL_IDX_MAX));

	if (wb_layer) {
		chn_idx = wb_layer->chn_idx;
	} else {
		chn_idx = layer->chn_idx;
	}

	aif = &(hisifd->dss_module.aif[chn_idx]);
	hisifd->dss_module.aif_ch_used[chn_idx] = 1;

	aif_bw = &(hisifd->dss_module.aif_bw[chn_idx]);
	BUG_ON(aif_bw->is_used != 1);

	mid = mid_array[chn_idx];
	BUG_ON(mid < 0 || mid > 0xb);

	aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, aif_bw->axi_sel, 1, 0);
	aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, mid, 4, 4);

	if (g_fpga_flag == 0) {
		if ((ovl_idx == DSS_OVL2) || (ovl_idx == DSS_OVL3)) {
			if (layer && ((layer->need_cap & CAP_AFBCD) != CAP_AFBCD)) {
				dss_core_rate = hisifd->dss_clk_rate.dss_pri_clk_rate;
				if (dss_core_rate == 0) {
					HISI_FB_ERR("fb%d, dss_core_rate(%llu) is invalid!",
						hisifd->index, dss_core_rate);
					dss_core_rate = DEFAULT_DSS_CORE_CLK_RATE;
				}

				if ((layer->src_rect.w > layer->dst_rect.w) &&
					(layer->src_rect.w > get_panel_xres(hisifd))) {
					scfd_h = layer->src_rect.w * 100 / get_panel_xres(hisifd);
				} else {
					scfd_h = 100;
				}

				//after stretch
				if (layer->src_rect.h > layer->dst_rect.h) {
					scfd_v = layer->src_rect.h * 100 / layer->dst_rect.h;
				} else {
					scfd_v = 100;
				}

				if (pov_req->wb_compose_type == DSS_WB_COMPOSE_COPYBIT) {
					if (wb_dst_rect) {
						online_offline_rate = wb_dst_rect->w * wb_dst_rect->h /
							(hisifd->panel_info.xres * hisifd->panel_info.yres);
					}

					if (online_offline_rate == 0)
						online_offline_rate = 1;
				}

				//credit_step = pix_f*128/(core_f*16/4)*scfd_h*scfd_v
				credit_step = hisifd->panel_info.pxl_clk_rate * online_offline_rate * 32 * scfd_h * scfd_v /
						dss_core_rate  / (100 * 100);

				if (g_debug_ovl_online_composer || g_debug_ovl_offline_composer || g_debug_ovl_credit_step) {
					HISI_FB_INFO("fb%d, layer_idx(%d), chn_idx(%d), src_rect(%d,%d,%d,%d),"
						"dst_rect(%d,%d,%d,%d), scfd_h=%d, scfd_v=%d, credit_step=%d.\n",
						hisifd->index, layer->layer_idx, layer->chn_idx,
						layer->src_rect.x, layer->src_rect.y, layer->src_rect.w, layer->src_rect.h,
						layer->dst_rect.x, layer->dst_rect.y, layer->dst_rect.w, layer->dst_rect.h,
						scfd_h, scfd_v, credit_step);
				}

				if (credit_step < 32) {
					credit_step = 32;
				}

				if (credit_step > 64) {
					aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, 0x0, 1, 11);   //credit en disable
				} else {
					aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, 0x1, 1, 11);   //credit en enable
					aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, credit_step, 7, 16);
				}

				/* credit en lower */
#ifdef CREDIT_STEP_LOWER_ENABLE
				aif->aif_ch_ctl_add = set_bits32(aif->aif_ch_ctl_add, 1, 1, 11);
#endif
				aif->aif_ch_ctl_add = set_bits32(aif->aif_ch_ctl_add, 8, 4, 12);
				aif->aif_ch_ctl_add = set_bits32(aif->aif_ch_ctl_add, 16, 7, 16);
			}
		}
	} else {
		if ((ovl_idx == DSS_OVL2) || (ovl_idx == DSS_OVL3)) {
			aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, 0x1, 1, 11);
			if (wb_layer && (wb_layer->need_cap & CAP_AFBCE)) {
				aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, 0x1, 2, 8);
			}
			aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, 0x20, 7, 16);

#ifdef CREDIT_STEP_LOWER_ENABLE
			/* credit en lower */
			aif->aif_ch_ctl_add = set_bits32(aif->aif_ch_ctl_add, 1, 1, 11);
#endif
			aif->aif_ch_ctl_add = set_bits32(aif->aif_ch_ctl_add, 8, 4, 12);
			aif->aif_ch_ctl_add = set_bits32(aif->aif_ch_ctl_add, 0x16, 7, 16);
		}
	}

	return 0;
}

int hisi_dss_aif1_ch_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req,
	dss_layer_t *layer, dss_wb_layer_t *wb_layer, int ovl_idx)
{
	dss_aif_t *aif1 = NULL;
	dss_aif_bw_t *aif1_bw = NULL;
	int chn_idx = 0;
	uint32_t need_cap = 0;
	int mid = 0;
	uint32_t credit_step = 0;
	uint64_t dss_core_rate = 0;
	uint32_t scfd_h = 0;
	uint32_t scfd_v = 0;

	BUG_ON(hisifd == NULL);
	BUG_ON(pov_req == NULL);
	BUG_ON((layer == NULL) && (wb_layer == NULL));
	BUG_ON((ovl_idx < DSS_OVL0) || (ovl_idx >= DSS_OVL_IDX_MAX));

	if (wb_layer) {
		chn_idx = wb_layer->chn_idx;
		need_cap = wb_layer->need_cap;
	} else {
		chn_idx = layer->chn_idx;
		need_cap = layer->need_cap;
	}

	if (!(need_cap & CAP_AFBCD))
		return 0;

	aif1 = &(hisifd->dss_module.aif1[chn_idx]);
	hisifd->dss_module.aif1_ch_used[chn_idx] = 1;

	aif1_bw = &(hisifd->dss_module.aif1_bw[chn_idx]);
	BUG_ON(aif1_bw->is_used != 1);

	mid = mid_array[chn_idx];
	BUG_ON(mid < 0 || mid > 0xb);

	aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, aif1_bw->axi_sel, 1, 0);
	aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, mid, 4, 4);

	if (g_fpga_flag == 0) {
		if ((ovl_idx == DSS_OVL0) || (ovl_idx == DSS_OVL1)) {
			if (layer && (layer->need_cap & CAP_AFBCD)) {
				dss_core_rate = hisifd->dss_clk_rate.dss_pri_clk_rate;
				if (dss_core_rate == 0) {
					HISI_FB_ERR("fb%d, dss_core_rate(%llu) is invalid!",
						hisifd->index, dss_core_rate);
					dss_core_rate = DEFAULT_DSS_CORE_CLK_RATE;
				}

				if ((layer->src_rect.w > layer->dst_rect.w) &&
					(layer->src_rect.w > get_panel_xres(hisifd))) {
					scfd_h = layer->src_rect.w * 100 / get_panel_xres(hisifd);
				} else {
					scfd_h = 100;
				}

				//after stretch
				if (layer->src_rect.h > layer->dst_rect.h) {
					scfd_v = layer->src_rect.h * 100 / layer->dst_rect.h;
				} else {
					scfd_v = 100;
				}

				//credit_step = pix_f*128/(core_f*16/4)*1.25*scfd_h*scfd_v
				credit_step = hisifd->panel_info.pxl_clk_rate * 32 * 150 * scfd_h * scfd_v /
					dss_core_rate  / (100 * 100 * 100);

				if (g_debug_ovl_online_composer || g_debug_ovl_offline_composer || g_debug_ovl_credit_step) {
					HISI_FB_INFO("fb%d, layer_idx(%d), chn_idx(%d), src_rect(%d,%d,%d,%d),"
						"dst_rect(%d,%d,%d,%d), scfd_h=%d, scfd_v=%d, credit_step=%d.\n",
						hisifd->index, layer->layer_idx, layer->chn_idx,
						layer->src_rect.x, layer->src_rect.y, layer->src_rect.w, layer->src_rect.h,
						layer->dst_rect.x, layer->dst_rect.y, layer->dst_rect.w, layer->dst_rect.h,
						scfd_h, scfd_v, credit_step);
				}

				if (credit_step < 32) {
					credit_step = 32;
				}

				if (credit_step > 64) {
					aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, 0x0, 1, 11);   //credit en disable
				} else {
					aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, 0x1, 1, 11);   //credit en enable
					aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, credit_step, 7, 16);
				}

			}
		} else {
			if (layer && (layer->need_cap & CAP_AFBCD)) {
				dss_core_rate = hisifd->dss_clk_rate.dss_pri_clk_rate;
				if (dss_core_rate == 0) {
					HISI_FB_ERR("fb%d, dss_core_rate(%llu is invalid!",
						hisifd->index, dss_core_rate);
					dss_core_rate = DEFAULT_DSS_CORE_CLK_RATE;
				}

				if ((layer->src_rect.w > layer->dst_rect.w) &&
					(layer->src_rect.w > get_panel_xres(hisifd))) {
					scfd_h = layer->src_rect.w * 100 / get_panel_xres(hisifd);
				} else {
					scfd_h = 100;
				}

				//after stretch
				if (layer->src_rect.h > layer->dst_rect.h) {
					scfd_v = layer->src_rect.h * 100 / layer->dst_rect.h;
				} else {
					scfd_v = 100;
				}

				//credit_step = pix_f*128/(core_f*16/4)*scfd_h*scfd_v
				credit_step = hisifd->panel_info.pxl_clk_rate * 32 * scfd_h * scfd_v /
					dss_core_rate  / (100 * 100);

				if (g_debug_ovl_online_composer || g_debug_ovl_offline_composer || g_debug_ovl_credit_step) {
					HISI_FB_INFO("fb%d, layer_idx(%d), chn_idx(%d), src_rect(%d,%d,%d,%d),"
						"dst_rect(%d,%d,%d,%d), scfd_h=%d, scfd_v=%d, credit_step=%d.\n",
						hisifd->index, layer->layer_idx, layer->chn_idx,
						layer->src_rect.x, layer->src_rect.y, layer->src_rect.w, layer->src_rect.h,
						layer->dst_rect.x, layer->dst_rect.y, layer->dst_rect.w, layer->dst_rect.h,
						scfd_h, scfd_v, credit_step);
				}

				if (credit_step > 64) {
					aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, 0x0, 1, 11);   //credit en disable
				} else {
					aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, 0x1, 1, 11);   //credit en enable
					aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, credit_step, 7, 16);
				}

				/* credit en lower */
#ifdef CREDIT_STEP_LOWER_ENABLE
				aif1->aif_ch_ctl_add = set_bits32(aif1->aif_ch_ctl_add, 1, 1, 11);
#endif
				aif1->aif_ch_ctl_add = set_bits32(aif1->aif_ch_ctl_add, 8, 4, 12);
				aif1->aif_ch_ctl_add = set_bits32(aif1->aif_ch_ctl_add, 16, 7, 16);
			}
		}
	} else {
		if ((ovl_idx == DSS_OVL2) || (ovl_idx == DSS_OVL3)) {
			aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, 0x1, 1, 11);
			aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, 0x10, 7, 16);
		}

#ifdef CREDIT_STEP_LOWER_ENABLE
		/* credit en lower */
		aif1->aif_ch_ctl_add = set_bits32(aif1->aif_ch_ctl_add, 1, 1, 11);
#endif
		aif1->aif_ch_ctl_add = set_bits32(aif1->aif_ch_ctl_add, 8, 4, 12);
		aif1->aif_ch_ctl_add = set_bits32(aif1->aif_ch_ctl_add, 0x16, 7, 16);

	}

	return 0;
}

/*******************************************************************************
** DSS SMMU
*/
void hisi_dss_smmu_on(struct hisi_fb_data_type *hisifd)
{
	char __iomem *smmu_base = NULL;
	int idx0 = 0;
	int idx1 = 0;
	int idx2 = 0;
	uint32_t phy_pgd_base = 0;
	struct iommu_domain_data *domain_data = NULL;
	uint64_t smmu_rwerraddr_phys = 0;

	BUG_ON(hisifd == NULL);

	smmu_base = hisifd->dss_base + DSS_SMMU_OFFSET;

	set_reg(smmu_base + SMMU_SCR, 0x0, 1, 0);  //global bypass cancel
	//set_reg(smmu_base + SMMU_SCR_S, 0x3, 2, 0);  //nscfg  using default value 0x3
	set_reg(smmu_base + SMMU_SCR, 0x1, 8, 20);   //ptw_mid
	set_reg(smmu_base + SMMU_SCR, g_dss_smmu_outstanding - 1, 4, 16);  //pwt_pf
	set_reg(smmu_base + SMMU_SCR, 0x7, 3, 3);  //interrupt cachel1 cach3l2 en
	set_reg(smmu_base + SMMU_LP_CTRL, 0x1, 1, 0);  //auto_clk_gt_en

	//Long Descriptor for chicago
	set_reg(smmu_base + SMMU_CB_TTBCR, 0x1, 1, 0);

	//RWERRADDR
	if (g_smmu_rwerraddr_virt) {
		smmu_rwerraddr_phys = virt_to_phys(g_smmu_rwerraddr_virt);

		set_reg(smmu_base + SMMU_ERR_RDADDR,
			(uint32_t)(smmu_rwerraddr_phys & 0xFFFFFFFF), 32, 0);
		//set_reg(smmu_base + SMMU_ADDR_MSB,
		//	(uint32_t)((smmu_rwerraddr_phys >> 32) & 0x3), 2, 0);
		set_reg(smmu_base + SMMU_ERR_WRADDR,
			(uint32_t)(smmu_rwerraddr_phys & 0xFFFFFFFF), 32, 0);
		//set_reg(smmu_base + SMMU_ADDR_MSB,
		//	(uint32_t)((smmu_rwerraddr_phys >> 32) & 0x3), 2, 2);
	} else {
		set_reg(smmu_base + SMMU_ERR_RDADDR, 0x7FF00000, 32, 0);
		//set_reg(smmu_base + SMMU_ADDR_MSB, 0x0, 2, 0);
		set_reg(smmu_base + SMMU_ERR_WRADDR, 0x7FFF0000, 32, 0);
		//set_reg(smmu_base + SMMU_ADDR_MSB, 0x0, 2, 2);
	}

	// disable cmdlist, dbg, v2, w2 reload
	set_reg(smmu_base + SMMU_RLD_EN0_NS, DSS_SMMU_RLD_EN0_DEFAULT_VAL, 32, 0);
	set_reg(smmu_base + SMMU_RLD_EN1_NS, DSS_SMMU_RLD_EN1_DEFAULT_VAL, 32, 0);

	idx0 = 36; //debug stream id
	idx1 = 37; //cmd unsec stream id
	idx2 = 38; //cmd sec stream id

	//cmdlist stream bypass
	set_reg(smmu_base + SMMU_SMRx_NS + idx0 * 0x4, 0x1, 32, 0);
	set_reg(smmu_base + SMMU_SMRx_NS + idx1 * 0x4, 0x1, 32, 0);
	set_reg(smmu_base + SMMU_SMRx_NS + idx2 * 0x4, 0x1, 32, 0);

	//TTBR0
	domain_data = (struct iommu_domain_data *)(hisifd->hisi_domain->priv);
	phy_pgd_base = (uint32_t)(domain_data->phy_pgd_base);
	set_reg(smmu_base + SMMU_CB_TTBR0, phy_pgd_base, 32, 0);
}

void hisi_dss_smmu_init(char __iomem *smmu_base,
	dss_smmu_t *s_smmu)
{
	BUG_ON(smmu_base == NULL);
	BUG_ON(s_smmu == NULL);

	memset(s_smmu, 0, sizeof(dss_smmu_t));
}

void hisi_dss_smmu_ch_set_reg(struct hisi_fb_data_type *hisifd,
	char __iomem *smmu_base, dss_smmu_t *s_smmu, int chn_idx)
{
	uint32_t idx = 0;
	uint32_t i = 0;

	BUG_ON(hisifd == NULL);
	BUG_ON(smmu_base == NULL);
	BUG_ON(s_smmu == NULL);

	if (s_smmu->smmu_smrx_ns_used[chn_idx] == 0)
		return;

	for (i = 0; i < g_dss_chn_sid_num[chn_idx]; i++) {
		idx = g_dss_smmu_smrx_idx[chn_idx] + i;
		BUG_ON((idx < 0) || (idx >= SMMU_SID_NUM));

		hisifd->set_reg(hisifd, smmu_base + SMMU_SMRx_NS + idx * 0x4,
			s_smmu->smmu_smrx_ns[idx], 32, 0);
	}

}

int hisi_dss_smmu_ch_config(struct hisi_fb_data_type *hisifd,
	dss_layer_t *layer, dss_wb_layer_t *wb_layer)
{
	dss_smmu_t *smmu = NULL;
	int chn_idx = 0;
	dss_img_t *img = NULL;
	uint32_t idx = 0;
	uint32_t i = 0;

	BUG_ON(hisifd == NULL);
	BUG_ON((layer == NULL) && (wb_layer == NULL));

	if (wb_layer) {
		img = &(wb_layer->dst);
		chn_idx = wb_layer->chn_idx;
	} else {
		img = &(layer->img);
		chn_idx = layer->chn_idx;
	}

	smmu = &(hisifd->dss_module.smmu);
	hisifd->dss_module.smmu_used = 1;

	smmu->smmu_smrx_ns_used[chn_idx] = 1;

	for (i = 0; i < g_dss_chn_sid_num[chn_idx]; i++) {
		idx = g_dss_smmu_smrx_idx[chn_idx] + i;
		BUG_ON((idx < 0) || (idx >= SMMU_SID_NUM));

		if (img->mmu_enable == 0) {
			smmu->smmu_smrx_ns[idx] = set_bits32(smmu->smmu_smrx_ns[idx], 0x1, 1, 0);
		} else {
			/* stream config */
			smmu->smmu_smrx_ns[idx] = set_bits32(smmu->smmu_smrx_ns[idx], 0x0, 1, 0);  //smr_bypass
			smmu->smmu_smrx_ns[idx] = set_bits32(smmu->smmu_smrx_ns[idx], 0x1, 1, 4);  //smr_invld_en
			smmu->smmu_smrx_ns[idx] = set_bits32(smmu->smmu_smrx_ns[idx], 0x3, 7, 5);  //smr_ptw_qos
			//smmu->smmu_smrx_ns[idx] = set_bits32(smmu->smmu_smrx_ns[idx],  , 20, 12);  //smr_offset_addr

		}
       }

	//if (img->mmu_enable != 0) {
		/* context config */
		//smmu->smmu_cb_sctrl = set_bits32(smmu->smmu_cb_sctrl,  , 1, 0);
		//smmu->smmu_cb_ttbr0 = set_bits32(smmu->smmu_cb_ttbr0,  , 1, 0);
		//smmu->smmu_cb_ttbr1 = set_bits32(smmu->smmu_cb_ttbr1,  , 1, 0);
		//smmu->smmu_cb_ttbcr = set_bits32(smmu->smmu_cb_ttbcr,  , 1, 0);//cb_ttbrc_des
		//smmu->smmu_offset_addr_ns = set_bits32(smmu->smmu_offset_addr_ns,  , 14, 0);

		/* FAMA config */
		//smmu->smmu_fama_ctrl0_ns = set_bits32(smmu->smmu_fama_ctrl0_ns,  , 7, 0); //fama_sdes_msb_ns
		//smmu->smmu_fama_ctrl0_ns = set_bits32(smmu->smmu_fama_ctrl0_ns,  , 1, 7); //fama_chn_sel_ns
		//smmu->smmu_fama_ctrl0_ns = set_bits32(smmu->smmu_fama_ctrl0_ns,  , 6, 8); //fama_bps_msb_ns
		//smmu->smmu_fama_ctrl1_ns = set_bits32(smmu->smmu_fama_ctrl1_ns,  , 7, 0); //fama_ptw_msb_ns
       //}

	return 0;
}
void hisifb_adjust_block_rect(int block_num, dss_rect_t *ov_block_rects[], dss_wb_layer_t *wb_layer)
{
	int i = 0;
	dss_rect_t block_rect;
	bool need_adjust_block = false;

	BUG_ON(ov_block_rects == NULL);
	BUG_ON(wb_layer == NULL);

	if ((block_num > 1) && (ov_block_rects[block_num - 1]->w < HISI_DSS_MIN_ROT_AFBCE_BLOCK_SIZE)) {
		if ((wb_layer->transform == (HISI_FB_TRANSFORM_ROT_90 | HISI_FB_TRANSFORM_FLIP_V))
			&& (wb_layer->need_cap == CAP_AFBCE)) {
			if (g_debug_ovl_block_composer) {
				HISI_FB_INFO("before_adjust:ov_block_rects[%d]:[%d:%d:%d:%d]\n",
					block_num - 1, ov_block_rects[block_num-1]->x, ov_block_rects[block_num-1]->y, ov_block_rects[block_num-1]->w,
					ov_block_rects[block_num-1]->h);
			}

			block_rect = *ov_block_rects[block_num - 1];

			ov_block_rects[block_num - 1]->w += HISI_DSS_MIN_ROT_AFBCE_BLOCK_SIZE;
			if (ov_block_rects[block_num - 1]->w > HISI_DSS_MAX_ROT_AFBCE_BLOCK_SIZE) {
				ov_block_rects[block_num - 1]->w = HISI_DSS_MAX_ROT_AFBCE_BLOCK_SIZE;
			}

			block_rect.x -= ov_block_rects[block_num - 1]->w - block_rect.w;
			ov_block_rects[block_num - 1]->x = ALIGN_UP(block_rect.x, AFBC_BLOCK_ALIGN);
			ov_block_rects[block_num - 1]->w -= ov_block_rects[block_num - 1]->x - block_rect.x;

			need_adjust_block = true;
		}
	}

	if (need_adjust_block && g_debug_ovl_block_composer) {
		for (i = 0; i < block_num; i++) {
			HISI_FB_INFO("after_adjust:ov_block_rects[%d]:[%d:%d:%d:%d]\n",
				i, ov_block_rects[i]->x, ov_block_rects[i]->y, ov_block_rects[i]->w,
				ov_block_rects[i]->h);
		}
	}
}

/*******************************************************************************
** DSS CSC
*/
#define CSC_ROW	(3)
#define CSC_COL	(5)

/* application: mode 2 is used in rgb2yuv, mode 0 is used in yuv2rgb */
#define CSC_MPREC_MODE_0 (0)
#define CSC_MPREC_MODE_1 (1)  //never used for chicago
#define CSC_MPREC_MODE_2 (2)  //yuv2rgb is not supported by mode 2

#define CSC_MPREC_MODE_RGB2YUV (CSC_MPREC_MODE_2)
#define CSC_MPREC_MODE_YUV2RGB (CSC_MPREC_MODE_0)

/*
** Rec.601 for Computer
** [ p00 p01 p02 cscidc2 cscodc2 ]
** [ p10 p11 p12 cscidc1 cscodc1 ]
** [ p20 p21 p22 cscidc0 cscodc0 ]
*/
static int CSC_COE_YUV2RGB601_NARROW_MPREC0[CSC_ROW][CSC_COL] = {
	{0x4a8, 0x000, 0x662, 0x7f0, 0x000},
	{0x4a8, 0x1e6f, 0x1cc0, 0x77f, 0x000},
	{0x4a8, 0x812, 0x000, 0x77f, 0x000}
};

static int CSC_COE_RGB2YUV601_NARROW_MPREC2[CSC_ROW][CSC_COL] = {
	{0x41C, 0x811, 0x191, 0x000, 0x010},
	{0x1DA1, 0x1B58, 0x707, 0x000, 0x081},
	{0x707, 0x1A1E, 0x1EDB, 0x000, 0x081}
};

static int CSC_COE_YUV2RGB709_NARROW_MPREC0[CSC_ROW][CSC_COL] = {
	{0x4a8, 0x000, 0x72c, 0x7f0, 0x000},
	{0x4a8, 0x1f26, 0x1dde, 0x77f, 0x000},
	{0x4a8, 0x873, 0x000, 0x77f, 0x000}
};

static int CSC_COE_RGB2YUV709_NARROW_MPREC2[CSC_ROW][CSC_COL] = {
	{0x2EC, 0x9D4, 0x0FE, 0x000, 0x010},
	{0x1E64, 0x1A95, 0x707, 0x000, 0x081},
	{0x707, 0x199E, 0x1F5B, 0x000, 0x081}
};

static int CSC_COE_YUV2RGB601_WIDE_MPREC0[CSC_ROW][CSC_COL] = {
	{0x400, 0x000, 0x59c, 0x000, 0x000},
	{0x400, 0x1ea0, 0x1d25, 0x77f, 0x000},
	{0x400, 0x717, 0x000, 0x77f, 0x000}
};

static int CSC_COE_RGB2YUV601_WIDE_MPREC2[CSC_ROW][CSC_COL] = {
	{0x4C9, 0x964, 0x1d3, 0x000, 0x000},
	{0x1D4D, 0x1AB3, 0x800, 0x000, 0x081},
	{0x800, 0x194D, 0x1EB3, 0x000, 0x081},
};

static int CSC_COE_YUV2RGB709_WIDE_MPREC0[CSC_ROW][CSC_COL] = {
	{0x400, 0x000, 0x64d, 0x000, 0x000},
	{0x400, 0x1f40, 0x1e21, 0x77f, 0x000},
	{0x400, 0x76c, 0x000, 0x77f, 0x000}
};

static int CSC_COE_RGB2YUV709_WIDE_MPREC2[CSC_ROW][CSC_COL] = {
	{0x367, 0xB71, 0x128, 0x000, 0x000},
	{0x1E2B, 0x19D5, 0x800, 0x000, 0x081},
	{0x800, 0x18BC, 0x1F44, 0x000, 0x081},
};

void hisi_dss_csc_init(char __iomem *csc_base, dss_csc_t *s_csc)
{
	BUG_ON(csc_base == NULL);
	BUG_ON(s_csc == NULL);

	memset(s_csc, 0, sizeof(dss_csc_t));

	s_csc->idc0 = inp32(csc_base + CSC_IDC0);
	s_csc->idc2 = inp32(csc_base + CSC_IDC2);
	s_csc->odc0 = inp32(csc_base + CSC_ODC0);
	s_csc->odc2 = inp32(csc_base + CSC_ODC2);
	s_csc->p0 = inp32(csc_base + CSC_P0);
	s_csc->p1 = inp32(csc_base + CSC_P1);
	s_csc->p2 = inp32(csc_base + CSC_P2);
	s_csc->p3 = inp32(csc_base + CSC_P3);
	s_csc->p4 = inp32(csc_base + CSC_P4);
	s_csc->icg_module = inp32(csc_base + CSC_ICG_MODULE);
	s_csc->mprec= inp32(csc_base + CSC_MPREC);
}

void hisi_dss_csc_set_reg(struct hisi_fb_data_type *hisifd,
	char __iomem *csc_base, dss_csc_t *s_csc)
{
	BUG_ON(hisifd == NULL);
	BUG_ON(csc_base == NULL);
	BUG_ON(s_csc == NULL);

	hisifd->set_reg(hisifd, csc_base + CSC_IDC0, s_csc->idc0, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_IDC2, s_csc->idc2, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_ODC0, s_csc->odc0, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_ODC2, s_csc->odc2, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_P0, s_csc->p0, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_P1, s_csc->p1, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_P2, s_csc->p2, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_P3, s_csc->p3, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_P4, s_csc->p4, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_ICG_MODULE, s_csc->icg_module, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_MPREC, s_csc->mprec, 32, 0);
}

bool is_pcsc_needed(dss_layer_t *layer)
{
	if (layer->chn_idx != DSS_RCHN_V0)
		return false;

	if (layer->need_cap == CAP_2D_SHARPNESS)
		return true;

	/*horizental shrink is not supported by arsr2p */
	if ((layer->dst_rect.h != layer->src_rect.h) || (layer->dst_rect.w > layer->src_rect.w))
		return true;

	return false;
}

//only for csc8b
int hisi_dss_csc_config(struct hisi_fb_data_type *hisifd,
	dss_layer_t *layer, dss_wb_layer_t *wb_layer)
{
	dss_csc_t *csc = NULL;
	int chn_idx = 0;
	uint32_t format = 0;
	uint32_t csc_mode = 0;
	int (*csc_coe_yuv2rgb)[CSC_COL];
	int (*csc_coe_rgb2yuv)[CSC_COL];

	BUG_ON(hisifd == NULL);

	if (wb_layer) {
		chn_idx = wb_layer->chn_idx;
		format = wb_layer->dst.format;
		csc_mode = wb_layer->dst.csc_mode;
	} else {
		chn_idx = layer->chn_idx;
		format = layer->img.format;
		csc_mode = layer->img.csc_mode;
	}

	if (chn_idx != DSS_RCHN_V0) {
		if (!isYUV(format))
			return 0;
		hisifd->dss_module.csc_used[chn_idx] = 1;
	} else if ((chn_idx == DSS_RCHN_V0) && (!isYUV(format))){ //v0, rgb format
		if (!is_pcsc_needed(layer))
			return 0;

		hisifd->dss_module.csc_used[DSS_RCHN_V0] = 1;
		hisifd->dss_module.pcsc_used[DSS_RCHN_V0] = 1;
	} else {//v0, yuv format
		hisifd->dss_module.csc_used[chn_idx] = 1;
	}

	if (csc_mode == DSS_CSC_601_WIDE) {
		csc_coe_yuv2rgb = CSC_COE_YUV2RGB601_WIDE_MPREC0;
		csc_coe_rgb2yuv = CSC_COE_RGB2YUV601_WIDE_MPREC2;
	} else if (csc_mode == DSS_CSC_601_NARROW) {
		csc_coe_yuv2rgb = CSC_COE_YUV2RGB601_NARROW_MPREC0;
		csc_coe_rgb2yuv = CSC_COE_RGB2YUV601_NARROW_MPREC2;
	} else if (csc_mode == DSS_CSC_709_WIDE) {
		csc_coe_yuv2rgb = CSC_COE_YUV2RGB709_WIDE_MPREC0;
		csc_coe_rgb2yuv = CSC_COE_RGB2YUV709_WIDE_MPREC2;
	} else if (csc_mode == DSS_CSC_709_NARROW) {
		csc_coe_yuv2rgb = CSC_COE_YUV2RGB709_NARROW_MPREC0;
		csc_coe_rgb2yuv = CSC_COE_RGB2YUV709_NARROW_MPREC2;
	} else {
	    /* TBD  add csc mprec mode 1 and mode 2*/
		HISI_FB_ERR("not support this csc_mode(%d)!\n", csc_mode);
		csc_coe_yuv2rgb = CSC_COE_YUV2RGB601_WIDE_MPREC0;
		csc_coe_rgb2yuv = CSC_COE_RGB2YUV601_WIDE_MPREC2;
	}

	/* config rch csc */
	if (layer && hisifd->dss_module.csc_used[chn_idx]) {
		csc = &(hisifd->dss_module.csc[chn_idx]);
		csc->mprec = CSC_MPREC_MODE_YUV2RGB;
		csc->icg_module = set_bits32(csc->icg_module, 0x1, 1, 0);

		csc->idc0 = set_bits32(csc->idc0,
			(csc_coe_yuv2rgb[2][3]) |
			(csc_coe_yuv2rgb[1][3] << 16), 27, 0);
		csc->idc2 = set_bits32(csc->idc2,
			(csc_coe_yuv2rgb[0][3]), 11, 0);

		csc->odc0 = set_bits32(csc->odc0,
			(csc_coe_yuv2rgb[2][4]) |
			(csc_coe_yuv2rgb[1][4] << 16), 27, 0);
		csc->odc2 = set_bits32(csc->odc2,
			(csc_coe_yuv2rgb[0][4]), 11, 0);

		csc->p0 = set_bits32(csc->p0, csc_coe_yuv2rgb[0][0], 13, 0);
		csc->p0 = set_bits32(csc->p0, csc_coe_yuv2rgb[0][1], 13, 16);

		csc->p1 = set_bits32(csc->p1, csc_coe_yuv2rgb[0][2], 13, 0);
		csc->p1 = set_bits32(csc->p1, csc_coe_yuv2rgb[1][0], 13, 16);

		csc->p2 = set_bits32(csc->p2, csc_coe_yuv2rgb[1][1], 13, 0);
		csc->p2 = set_bits32(csc->p2, csc_coe_yuv2rgb[1][2], 13, 16);

		csc->p3 = set_bits32(csc->p3, csc_coe_yuv2rgb[2][0], 13, 0);
		csc->p3 = set_bits32(csc->p3, csc_coe_yuv2rgb[2][1], 13, 16);

		csc->p4 = set_bits32(csc->p4, csc_coe_yuv2rgb[2][2], 13, 0);
	}

	/* config rch pcsc */
	if (layer && hisifd->dss_module.pcsc_used[chn_idx]) {
		csc = &(hisifd->dss_module.pcsc[chn_idx]);
		csc->mprec = CSC_MPREC_MODE_RGB2YUV;
		csc->icg_module = set_bits32(csc->icg_module, 0x1, 1, 0);

		csc->idc0 = set_bits32(csc->idc0,
			(csc_coe_rgb2yuv[2][3]) |
			(csc_coe_rgb2yuv[1][3] << 16), 27, 0);
		csc->idc2 = set_bits32(csc->idc2,
			(csc_coe_rgb2yuv[0][3]), 11, 0);

		csc->odc0 = set_bits32(csc->odc0,
			(csc_coe_rgb2yuv[2][4]) |
			(csc_coe_rgb2yuv[1][4] << 16), 27, 0);
		csc->odc2 = set_bits32(csc->odc2,
			(csc_coe_rgb2yuv[0][4]), 11, 0);

		csc->p0 = set_bits32(csc->p0, csc_coe_rgb2yuv[0][0], 13, 0);
		csc->p0 = set_bits32(csc->p0, csc_coe_rgb2yuv[0][1], 13, 16);

		csc->p1 = set_bits32(csc->p1, csc_coe_rgb2yuv[0][2], 13, 0);
		csc->p1 = set_bits32(csc->p1, csc_coe_rgb2yuv[1][0], 13, 16);

		csc->p2 = set_bits32(csc->p2, csc_coe_rgb2yuv[1][1], 13, 0);
		csc->p2 = set_bits32(csc->p2, csc_coe_rgb2yuv[1][2], 13, 16);

		csc->p3 = set_bits32(csc->p3, csc_coe_rgb2yuv[2][0], 13, 0);
		csc->p3 = set_bits32(csc->p3, csc_coe_rgb2yuv[2][1], 13, 16);

		csc->p4 = set_bits32(csc->p4, csc_coe_rgb2yuv[2][2], 13, 0);
	}

	/* config wch csc */
	if (wb_layer) {
		csc = &(hisifd->dss_module.csc[chn_idx]);
		csc->mprec = CSC_MPREC_MODE_RGB2YUV;
		csc->icg_module = set_bits32(csc->icg_module, 0x1, 1, 0);

		csc->idc0 = set_bits32(csc->idc0,
			(csc_coe_rgb2yuv[2][3]) |
			(csc_coe_rgb2yuv[1][3] << 16), 27, 0);
		csc->idc2 = set_bits32(csc->idc2,
			(csc_coe_rgb2yuv[0][3]), 11, 0);

		csc->odc0 = set_bits32(csc->odc0,
			(csc_coe_rgb2yuv[2][4]) |
			(csc_coe_rgb2yuv[1][4] << 16), 27, 0);
		csc->odc2 = set_bits32(csc->odc2,
			(csc_coe_rgb2yuv[0][4]), 11, 0);

		csc->p0 = set_bits32(csc->p0, csc_coe_rgb2yuv[0][0], 13, 0);
		csc->p0 = set_bits32(csc->p0, csc_coe_rgb2yuv[0][1], 13, 16);

		csc->p1 = set_bits32(csc->p1, csc_coe_rgb2yuv[0][2], 13, 0);
		csc->p1 = set_bits32(csc->p1, csc_coe_rgb2yuv[1][0], 13, 16);

		csc->p2 = set_bits32(csc->p2, csc_coe_rgb2yuv[1][1], 13, 0);
		csc->p2 = set_bits32(csc->p2, csc_coe_rgb2yuv[1][2], 13, 16);

		csc->p3 = set_bits32(csc->p3, csc_coe_rgb2yuv[2][0], 13, 0);
		csc->p3 = set_bits32(csc->p3, csc_coe_rgb2yuv[2][1], 13, 16);

		csc->p4 = set_bits32(csc->p4, csc_coe_rgb2yuv[2][2], 13, 0);
	}

	return 0;
}

uint32_t hisi_dss_mif_get_invalid_sel(dss_img_t *img, uint32_t transform, int v_scaling_factor,
	uint8_t is_tile, bool rdma_stretch_enable)
{
	uint32_t invalid_sel_val = 0;
	uint32_t tlb_tag_org = 0;

	if (img == NULL) {
		HISI_FB_ERR("img is null");
		return 0;
	}

	if ((transform == (HISI_FB_TRANSFORM_ROT_90 | HISI_FB_TRANSFORM_FLIP_H))
		|| (transform == (HISI_FB_TRANSFORM_ROT_90 | HISI_FB_TRANSFORM_FLIP_V))) {
		transform = HISI_FB_TRANSFORM_ROT_90;
	}

	tlb_tag_org =  (transform & 0x7) |
		((is_tile ? 1 : 0) << 3) | ((rdma_stretch_enable ? 1 : 0) << 4);

	switch (tlb_tag_org) {
	case MMU_TLB_TAG_ORG_0x0:
		invalid_sel_val = 1;
		break;
	case MMU_TLB_TAG_ORG_0x1:
		invalid_sel_val = 1;
		break;
	case MMU_TLB_TAG_ORG_0x2:
		invalid_sel_val = 2;
		break;
	case MMU_TLB_TAG_ORG_0x3:
		invalid_sel_val = 2;
		break;
	case MMU_TLB_TAG_ORG_0x4:
		invalid_sel_val = 0;
		break;
	case MMU_TLB_TAG_ORG_0x7:
		invalid_sel_val = 0;
		break;

	case MMU_TLB_TAG_ORG_0x8:
		invalid_sel_val = 3;
		break;
	case MMU_TLB_TAG_ORG_0x9:
		invalid_sel_val = 3;
		break;
	case MMU_TLB_TAG_ORG_0xA:
		invalid_sel_val = 3;
		break;
	case MMU_TLB_TAG_ORG_0xB:
		invalid_sel_val = 3;
		break;
	case MMU_TLB_TAG_ORG_0xC:
		invalid_sel_val = 0;
		break;
	case MMU_TLB_TAG_ORG_0xF:
		invalid_sel_val = 0;
		break;

	case MMU_TLB_TAG_ORG_0x10:
		invalid_sel_val = 1;
		break;
	case MMU_TLB_TAG_ORG_0x11:
		invalid_sel_val = 1;
		break;
	case MMU_TLB_TAG_ORG_0x12:
		invalid_sel_val = 2;
		break;
	case MMU_TLB_TAG_ORG_0x13:
		invalid_sel_val = 2;
		break;
	case MMU_TLB_TAG_ORG_0x14:
		invalid_sel_val = 0;
		break;
	case MMU_TLB_TAG_ORG_0x17:
		invalid_sel_val = 0;
		break;

	case MMU_TLB_TAG_ORG_0x18:
		invalid_sel_val = 3;
		break;
	case MMU_TLB_TAG_ORG_0x19:
		invalid_sel_val = 3;
		break;
	case MMU_TLB_TAG_ORG_0x1A:
		invalid_sel_val = 3;
		break;
	case MMU_TLB_TAG_ORG_0x1B:
		invalid_sel_val = 3;
		break;
	case MMU_TLB_TAG_ORG_0x1C:
		invalid_sel_val = 0;
		break;
	case MMU_TLB_TAG_ORG_0x1F:
		invalid_sel_val = 0;
		break;

	default:
		invalid_sel_val = 0;
		HISI_FB_ERR("not support this tlb_tag_org(0x%x)!\n", tlb_tag_org);
		break;
	}

	return invalid_sel_val;
}

void hisifb_disreset_dss(struct hisi_fb_data_type *hisifd)
{

	char __iomem *peri_crg_base = hisifd->peri_crg_base;
	char __iomem *pmctrl_base = hisifd->pmctrl_base;
	uint32_t ret = 0;

	////////////////////////////////////////////////////////////////////////////
	//
	// VIVO BUS POWERUP
	//
	//1:module clk enable
	//PLL2 16div vivo bus clock
	//outp32(peri_crg_base + CLKDIV10, 0x0f800780);
	//PLL3 16div 100M
	//outp32(peri_crg_base + CLKDIV10, 0x30003000);
	//gt_clk_vivobus
	outp32(peri_crg_base + 0xf8, 0x00020002);
	//gt_clk_vivobus2ddrc
	outp32(peri_crg_base + 0x00, 0x00001000);
	//2:module unrst: ip_rst_vivobus
	outp32(peri_crg_base + 0x94, 0x00000002);

	////////////////////////////////////////////////////////////////////////////
	//
	// DSS POWERUP
	//
	//1:module mtcmos on, dsssubsyspwren
	outp32(peri_crg_base + 0x150, 0x00000020);
	//udelay(100);
	mdelay(1);

	//Fix bug
	//2:vivo bus module clk enable, //PLL3 16div
	outp32(peri_crg_base + 0xf0, 0x01c001c0);
	outp32(peri_crg_base + 0x00, 0x00002000);
	outp32(peri_crg_base + 0x30, 0x0403f000);
	mdelay(1);

	//3:module clk disable
	outp32(peri_crg_base + 0x34, 0x0403f000);
	outp32(peri_crg_base + 0x04, 0x00002000);
	outp32(peri_crg_base + 0xf0, 0x01c00000);
	//udelay(1);
	mdelay(1);

	//4:module iso disable, dsssubsysisoen
	outp32(peri_crg_base + 0x148, 0x00000040);

	//5:memory rempair

	//6:module unrst, ip_prst_dss ip_rst_dss
	outp32(peri_crg_base + 0x94, 0x00000016);
	outp32(peri_crg_base + 0x88, 0x00000c00);

	outp32(peri_crg_base + 0xf0, 0x01c001c0);
	outp32(peri_crg_base + 0x00, 0x00002000);
	outp32(peri_crg_base + 0x30, 0x0403f000);

	//bus idle clear
	//not included in austin and dallas
	outp32(pmctrl_base + 0x380, 0x20000000);

	ret = inp32(pmctrl_base + 0x384);
	udelay(10);
	HISI_FB_ERR("pmctrl_base + 0x384 = 0x%x\n", ret);

	ret = inp32(pmctrl_base + 0x388);
	udelay(10);
	HISI_FB_ERR("pmctrl_base + 0x388 = 0x%x\n", ret);

	ret = inp32(peri_crg_base + 0x98);
	HISI_FB_ERR("peri_crg_base + 0x98 = 0x%x\n", ret);

}
void hisifb_reset_dss(struct hisi_fb_data_type *hisifd)
{
	char __iomem *peri_crg_base = hisifd->peri_crg_base;
	char __iomem *pctrl_base = hisifd->pctrl_base;

	//1:bus idle set
	//TBD not included in austin and dallas

	//2:module reset
	outp32(peri_crg_base + PERRSTEN4, 0x00000010);
	outp32(peri_crg_base + PERRSTEN4, 0x00000006);
	outp32(peri_crg_base + PERRSTEN3, 0x00000C00);

	//3:module clock disable
	outp32(peri_crg_base + PERDIS3, 0x0403F000);
	outp32(peri_crg_base + PERDIS0, 0x00002000);
	outp32(peri_crg_base + CLKDIV18, 0x01C00000);

	//4:module iso
	outp32(peri_crg_base + ISOEN, 0x00000040);


	//5:module mtcmos off
	outp32(peri_crg_base + PERPWRDIS, 0x00000020);

    	//6:vivo bus off


}




