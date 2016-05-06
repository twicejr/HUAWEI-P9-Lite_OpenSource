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

uint32_t g_dss_module_base[DSS_CHN_MAX_DEFINE][MODULE_CHN_MAX] = {
	/* D2 */
	{
	MIF_CH0_OFFSET,
	AIF0_CH0_OFFSET,
	AIF1_CH0_OFFSET,
	MCTL_CTL_MUTEX_RCH0,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH0_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH0_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH0_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD0_DBG,
	DSS_RCH_D2_DMA_OFFSET,
	DSS_RCH_D2_DFC_OFFSET,
	0,
	0,
	0,
	0,
	DSS_RCH_D2_CSC_OFFSET,
	0,
	0,
	0,
	0,
	0
	},

	/* D3 */
	{
	MIF_CH1_OFFSET,
	AIF0_CH1_OFFSET,
	AIF1_CH1_OFFSET,
	MCTL_CTL_MUTEX_RCH1,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH1_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH1_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH1_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD1_DBG,
	DSS_RCH_D3_DMA_OFFSET,
	DSS_RCH_D3_DFC_OFFSET,
	0,
	0,
	0,
	0,
	DSS_RCH_D3_CSC_OFFSET,
	0,
	0,
	0,
	0,
	0
	},

	/* V0 */
	{
	MIF_CH2_OFFSET,
	AIF0_CH2_OFFSET,
	AIF1_CH2_OFFSET,
	MCTL_CTL_MUTEX_RCH2,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH2_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH2_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH2_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD2_DBG,
	DSS_RCH_VG0_DMA_OFFSET,
	DSS_RCH_VG0_DFC_OFFSET,
	DSS_RCH_VG0_SCL_OFFSET,
	DSS_RCH_VG0_SCL_LUT_OFFSET,
	DSS_RCH_VG0_SHARPNESS_OFFSET,
	DSS_RCH_VG0_POST_CLIP_OFFSET,
	DSS_RCH_VG0_CSC_OFFSET,
	DSS_RCH_VG0_CE_OFFSET,
	DSS_RCH_VG0_CE0_LUT_OFFSET,
	DSS_RCH_VG0_CE1_LUT_OFFSET,
	DSS_RCH_VG0_CE2_LUT_OFFSET,
	DSS_RCH_VG0_CE3_LUT_OFFSET,
	},

	/* G0 */
	{
	MIF_CH3_OFFSET,
	AIF0_CH3_OFFSET,
	AIF1_CH3_OFFSET,
	MCTL_CTL_MUTEX_RCH3,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH3_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH3_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH3_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD3_DBG,
	DSS_RCH_G0_DMA_OFFSET,
	DSS_RCH_G0_DFC_OFFSET,
	DSS_RCH_G0_SCL_OFFSET,
	0,
	0,
	DSS_RCH_G0_POST_CLIP_OFFSET,
	0,
	0,
	0,
	0,
	0,
	0
	},

	/* V1 */
	{
	MIF_CH4_OFFSET,
	AIF0_CH4_OFFSET,
	AIF1_CH4_OFFSET,
	MCTL_CTL_MUTEX_RCH4,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH4_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH4_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH4_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD4_DBG,
	DSS_RCH_VG1_DMA_OFFSET,
	DSS_RCH_VG1_DFC_OFFSET,
	DSS_RCH_VG1_SCL_OFFSET,
	DSS_RCH_VG1_SCL_LUT_OFFSET,
	DSS_RCH_VG1_SHARPNESS_OFFSET,
	DSS_RCH_VG1_POST_CLIP_OFFSET,
	DSS_RCH_VG1_CSC_OFFSET,
	DSS_RCH_VG1_CE_OFFSET,
	DSS_RCH_VG1_CE0_LUT_OFFSET,
	DSS_RCH_VG1_CE1_LUT_OFFSET,
	DSS_RCH_VG1_CE2_LUT_OFFSET,
	DSS_RCH_VG1_CE3_LUT_OFFSET,
	},

	/* G1 */
	{
	MIF_CH5_OFFSET,
	AIF0_CH5_OFFSET,
	AIF1_CH5_OFFSET,
	MCTL_CTL_MUTEX_RCH5,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH5_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH5_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH5_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD5_DBG,
	DSS_RCH_G1_DMA_OFFSET,
	DSS_RCH_G1_DFC_OFFSET,
	DSS_RCH_G1_SCL_OFFSET,
	0,
	0,
	DSS_RCH_G1_POST_CLIP_OFFSET,
	0,
	0,
	0,
	0,
	0,
	0
	},

	/* D0 */
	{
	MIF_CH6_OFFSET,
	AIF0_CH6_OFFSET,
	AIF1_CH6_OFFSET,
	MCTL_CTL_MUTEX_RCH6,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH6_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH6_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH6_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD6_DBG,
	DSS_RCH_D0_DMA_OFFSET,
	DSS_RCH_D0_DFC_OFFSET,
	0,
	0,
	0,
	0,
	DSS_RCH_D0_CSC_OFFSET,
	0,
	0,
	0,
	0,
	0
	},

	/* D1 */
	{
	MIF_CH7_OFFSET,
	AIF0_CH7_OFFSET,
	AIF1_CH7_OFFSET,
	MCTL_CTL_MUTEX_RCH7,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH7_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH7_OV_OEN,
	DSS_MCTRL_SYS_OFFSET + MCTL_RCH7_STARTY,
	DSS_MCTRL_SYS_OFFSET + MCTL_MOD7_DBG,
	DSS_RCH_D1_DMA_OFFSET,
	DSS_RCH_D1_DFC_OFFSET,
	0,
	0,
	0,
	0,
	DSS_RCH_D1_CSC_OFFSET,
	0,
	0,
	0,
	0,
	0
	},

	/* W0 */
	{
	MIF_CH8_OFFSET,
	AIF0_CH8_OFFSET,
	AIF1_CH8_OFFSET,
	MCTL_CTL_MUTEX_WCH0,
	DSS_MCTRL_SYS_OFFSET + MCTL_WCH0_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_WCH0_OV_IEN,
	0,
	0,
	DSS_WCH0_DMA_OFFSET,
	DSS_WCH0_DFC_OFFSET,
	0,
	0,
	0,
	0,
	DSS_WCH0_CSC_OFFSET,
	0,
	0,
	0,
	0,
	0
	},

	/* W1 */
	{
	MIF_CH9_OFFSET,
	AIF0_CH9_OFFSET,
	AIF1_CH9_OFFSET,
	MCTL_CTL_MUTEX_WCH1,
	DSS_MCTRL_SYS_OFFSET + MCTL_WCH1_FLUSH_EN,
	DSS_MCTRL_SYS_OFFSET + MCTL_WCH1_OV_IEN,
	0,
	0,
	DSS_WCH1_DMA_OFFSET,
	DSS_WCH1_DFC_OFFSET,
	0,
	0,
	0,
	0,
	DSS_WCH1_CSC_OFFSET,
	0,
	0,
	0,
	0,
	0
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
int g_scf_lut_chn_coef_idx[DSS_CHN_MAX_DEFINE] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};


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
};

uint32_t g_dss_mif_sid_map[DSS_CHN_MAX_DEFINE] = {
    0xa, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

uint32_t g_dss_smmu_smrx_idx[DSS_CHN_MAX_DEFINE] = {
    0xa, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

uint32_t g_fpga_flag = 0;
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
	BUG_ON(hisifd == NULL);

	outp32(hisifd->noc_dss_base + 0xc, 0x2);
	outp32(hisifd->noc_dss_base + 0x8c, 0x2);
	outp32(hisifd->noc_dss_base + 0x10c, 0x2);
	outp32(hisifd->noc_dss_base + 0x18c, 0x2);
}

/*******************************************************************************
** DSS AIF
*/
void hisi_dss_aif_init(char __iomem *aif_ch_base,
	dss_aif_t *s_aif)
{
	BUG_ON(aif_ch_base == NULL);
	BUG_ON(s_aif == NULL);

	memset(s_aif, 0, sizeof(dss_aif_t));

	//s_aif->aif_ch_ctl = inp32(aif_ch_base + AIF_CH_CTL);
	s_aif->aif_ch_ctl = 0x0000F000;
}

void hisi_dss_aif_ch_set_reg(struct hisi_fb_data_type *hisifd,
	char __iomem *aif_ch_base, dss_aif_t *s_aif)
{
	BUG_ON(hisifd == NULL);
	BUG_ON(aif_ch_base == NULL);
	BUG_ON(s_aif == NULL);

	hisifd->set_reg(hisifd, aif_ch_base + AIF_CH_CTL,
		s_aif->aif_ch_ctl, 32, 0);
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

	mid = 0x9 - chn_idx;
	BUG_ON(mid < 0);

	aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, aif_bw->axi_sel, 1, 0);
	aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, mid, 4, 4);

	if (g_fpga_flag == 0) {
		if ((ovl_idx == DSS_OVL2) || (ovl_idx == DSS_OVL3)) {
			if (layer) {
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
					credit_step = 0;
				}

				aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, 0x1, 1, 11);
				aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, credit_step, 7, 16);
			}
		}
	} else {
		if (chn_idx >= DSS_WCHN_W0) {
			aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, 0x1, 1, 11);
			if (wb_layer && (wb_layer->need_cap & CAP_AFBCE)) {
				aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, 0x1, 2, 8);
			}
			aif->aif_ch_ctl = set_bits32(aif->aif_ch_ctl, 0x20, 7, 16);
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

	mid = 0x9 - chn_idx;
	BUG_ON(mid < 0);

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
					credit_step = 0;
				}

				aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, 0x1, 1, 11);
				aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, credit_step, 7, 16);
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

				if (credit_step < 32) {
					credit_step = 32;
				}

				if (credit_step > 64) {
					credit_step = 0;
				}

				aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, 0x1, 1, 11);
				aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, credit_step, 7, 16);
			}
		}
	} else {
		if ((ovl_idx == DSS_OVL2) || (ovl_idx == DSS_OVL3)) {
			aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, 0x1, 1, 11);
			aif1->aif_ch_ctl = set_bits32(aif1->aif_ch_ctl, 0x10, 7, 16);
		}
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
	int idx3 = 0;
	uint32_t phy_pgd_base = 0;
	struct iommu_domain_data *domain_data = NULL;
	uint64_t smmu_rwerraddr_phys = 0;

	BUG_ON(hisifd == NULL);

	smmu_base = hisifd->dss_base + DSS_SMMU_OFFSET;

	set_reg(smmu_base + SMMU_SCR, 0x0, 1, 0);
	set_reg(smmu_base + SMMU_SCR, 0x7, 3, 3);
	set_reg(smmu_base + SMMU_SCR, g_dss_smmu_outstanding - 1, 4, 16);
	set_reg(smmu_base + SMMU_SCR, 0x1, 8, 20);

	//auto_clk_gt_en
	set_reg(smmu_base + SMMU_LP_CTRL, 0x1, 1, 0);
	//Short Descriptor
	set_reg(smmu_base + SMMU_CB_TTBCR, 0x0, 1, 0);

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

	//cmdlist
	set_reg(smmu_base + SMMU_RLD_EN0, DSS_SMMU_RLD_EN0_DEFAULT_VAL, 32, 0);
	set_reg(smmu_base + SMMU_RLD_EN1, DSS_SMMU_RLD_EN1_DEFAULT_VAL, 32, 0);

	/*
	idx0 = (0 << 4); //chn | (0 << 4)
	idx1 = (1 << 4);
	idx2 = (2 << 4);
	idx3 = (3 << 4);
	*/
	idx0 = (0 << 4); //chn | (0 << 4)
	idx1 = idx0 + DSS_MIF_SMMU_SMRX_IDX_STEP;
	idx2 = idx1 + DSS_MIF_SMMU_SMRX_IDX_STEP;
	idx3 = idx2 + DSS_MIF_SMMU_SMRX_IDX_STEP;

	set_reg(smmu_base + SMMU_SMRx + idx0 * 0x4, 0x9, 32, 0);
	set_reg(smmu_base + SMMU_SMRx + idx1 * 0x4, 0x9, 32, 0);
	set_reg(smmu_base + SMMU_SMRx + idx2 * 0x4, 0x9, 32, 0);
	set_reg(smmu_base + SMMU_SMRx + idx3 * 0x4, 0x9, 32, 0);

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
	int idx0 = 0;
	int idx1 = 0;
	int idx2 = 0;
	int idx3 = 0;

	BUG_ON(hisifd == NULL);
	BUG_ON(smmu_base == NULL);
	BUG_ON(s_smmu == NULL);

	/*
	if (chn_idx == DSS_RCHN_D2) {
		idx0 = 0xA | (0 << 4);
		idx1 = 0xA | (1 << 4);
		idx2 = 0xA | (2 << 4);
		idx3 = 0xA | (3 << 4);
	} else {
		idx0 = chn_idx | (0 << 4);
		idx1 = chn_idx | (1 << 4);
		idx2 = chn_idx | (2 << 4);
		idx3 = chn_idx | (3 << 4);
	}*/
	idx0 = g_dss_smmu_smrx_idx[chn_idx];
	idx1 = idx0 + DSS_MIF_SMMU_SMRX_IDX_STEP;
	idx2 = idx1 + DSS_MIF_SMMU_SMRX_IDX_STEP;
	idx3 = idx2 + DSS_MIF_SMMU_SMRX_IDX_STEP;

	BUG_ON((idx0 < 0) || (idx0 >= SMMU_SID_NUM));
	BUG_ON((idx1 < 0) || (idx1 >= SMMU_SID_NUM));
	BUG_ON((idx2 < 0) || (idx2 >= SMMU_SID_NUM));
	BUG_ON((idx3 < 0) || (idx3 >= SMMU_SID_NUM));

	if (s_smmu->smmu_smrx_used[chn_idx] == 1) {
		hisifd->set_reg(hisifd, smmu_base + SMMU_SMRx + idx0 * 0x4,
			s_smmu->smmu_smrx[idx0], 32, 0);
		hisifd->set_reg(hisifd, smmu_base + SMMU_SMRx + idx1 * 0x4,
			s_smmu->smmu_smrx[idx1], 32, 0);
		hisifd->set_reg(hisifd, smmu_base + SMMU_SMRx + idx2 * 0x4,
			s_smmu->smmu_smrx[idx2], 32, 0);
		hisifd->set_reg(hisifd, smmu_base + SMMU_SMRx + idx3 * 0x4,
			s_smmu->smmu_smrx[idx3], 32, 0);
	}
}


int hisi_dss_smmu_ch_config(struct hisi_fb_data_type *hisifd,
	dss_layer_t *layer, dss_wb_layer_t *wb_layer)
{
	dss_smmu_t *smmu = NULL;
	int chn_idx = 0;
	dss_img_t *img = NULL;
	int idx0 = 0;
	int idx1 = 0;
	int idx2 = 0;
	int idx3 = 0;

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

	idx0 = g_dss_smmu_smrx_idx[chn_idx];
	idx1 = idx0 + DSS_MIF_SMMU_SMRX_IDX_STEP;
	idx2 = idx1 + DSS_MIF_SMMU_SMRX_IDX_STEP;
	idx3 = idx2 + DSS_MIF_SMMU_SMRX_IDX_STEP;
	/*if (chn_idx == DSS_RCHN_D2) {
		idx0 = 0xA | (0 << 4);
		idx1 = 0xA | (1 << 4);
		idx2 = 0xA | (2 << 4);
		idx3 = 0xA | (3 << 4);
	} else {
		idx0 = chn_idx | (0 << 4);
		idx1 = chn_idx | (1 << 4);
		idx2 = chn_idx | (2 << 4);
		idx3 = chn_idx | (3 << 4);
	}*/

	BUG_ON((idx0 < 0) || (idx0 >= SMMU_SID_NUM));
	BUG_ON((idx1 < 0) || (idx1 >= SMMU_SID_NUM));
	BUG_ON((idx2 < 0) || (idx2 >= SMMU_SID_NUM));
	BUG_ON((idx3 < 0) || (idx3 >= SMMU_SID_NUM));

	smmu->smmu_smrx_used[chn_idx] = 1;

	if (img->mmu_enable == 0) {
		smmu->smmu_smrx[idx0] = set_bits32(smmu->smmu_smrx[idx0], 0x9, 4, 0);
		smmu->smmu_smrx[idx1] = set_bits32(smmu->smmu_smrx[idx1], 0x9, 4, 0);
		smmu->smmu_smrx[idx2] = set_bits32(smmu->smmu_smrx[idx2], 0x9, 4, 0);
		smmu->smmu_smrx[idx3] = set_bits32(smmu->smmu_smrx[idx3], 0x9, 4, 0);
	} else {
		smmu->smmu_smrx[idx0] = set_bits32(smmu->smmu_smrx[idx0], 0x0, 1, 0);
		smmu->smmu_smrx[idx0] = set_bits32(smmu->smmu_smrx[idx0], 0x1, 1, 3);
		smmu->smmu_smrx[idx0] = set_bits32(smmu->smmu_smrx[idx0], 0x1, 1, 4);
		smmu->smmu_smrx[idx0] = set_bits32(smmu->smmu_smrx[idx0], 0x3, 7, 5);

		smmu->smmu_smrx[idx1] = set_bits32(smmu->smmu_smrx[idx1], 0x0, 1, 0);
		smmu->smmu_smrx[idx1] = set_bits32(smmu->smmu_smrx[idx1], 0x1, 1, 3);
		smmu->smmu_smrx[idx1] = set_bits32(smmu->smmu_smrx[idx1], 0x1, 1, 4);
		smmu->smmu_smrx[idx1] = set_bits32(smmu->smmu_smrx[idx1], 0x3, 7, 5);

		smmu->smmu_smrx[idx2] = set_bits32(smmu->smmu_smrx[idx2], 0x0, 1, 0);
		smmu->smmu_smrx[idx2] = set_bits32(smmu->smmu_smrx[idx2], 0x1, 1, 3);
		smmu->smmu_smrx[idx2] = set_bits32(smmu->smmu_smrx[idx2], 0x1, 1, 4);
		smmu->smmu_smrx[idx2] = set_bits32(smmu->smmu_smrx[idx2], 0x3, 7, 5);

		smmu->smmu_smrx[idx3] = set_bits32(smmu->smmu_smrx[idx3], 0x0, 1, 0);
		smmu->smmu_smrx[idx3] = set_bits32(smmu->smmu_smrx[idx3], 0x1, 1, 3);
		smmu->smmu_smrx[idx3] = set_bits32(smmu->smmu_smrx[idx3], 0x1, 1, 4);
		smmu->smmu_smrx[idx3] = set_bits32(smmu->smmu_smrx[idx3], 0x3, 7, 5);
	}

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

/*
** Rec.601 for Computer
** [ p00 p01 p02 cscidc2 cscodc2 ]
** [ p10 p11 p12 cscidc1 cscodc1 ]
** [ p20 p21 p22 cscidc0 cscodc0 ]
*/
static int CSC_COE_YUV2RGB601_NARROW[CSC_ROW][CSC_COL] = {
	{0x12a, 0x000, 0x199, 0x1f0, 0x0},
	{0x12a, 0x79d, 0x731, 0x180, 0x0},
	{0x12a, 0x205, 0x000, 0x180, 0x0}
};

static int CSC_COE_RGB2YUV601_NARROW[CSC_ROW][CSC_COL] = {
	{0x042, 0x081, 0x019, 0x0, 0x010},
	{0x7DB, 0x7B7, 0x070, 0x0, 0x080},
	{0x070, 0x7A3, 0x7EF, 0x0, 0x080}
};

static int CSC_COE_YUV2RGB709_NARROW[CSC_ROW][CSC_COL] = {
	{0x12A, 0x000, 0x1CB, 0x1F0, 0x0},
	{0x12A, 0x7CA, 0x778, 0x180, 0x0},
	{0x12A, 0x21D, 0x000, 0x180, 0x0}
};

static int CSC_COE_RGB2YUV709_NARROW[CSC_ROW][CSC_COL] = {
	{0x02F, 0x09D, 0x010, 0x0, 0x010},
	{0x7E7, 0x7AA, 0x070, 0x0, 0x080},
	{0x070, 0x79B, 0x7F7, 0x0, 0x080}
};


static int CSC_COE_YUV2RGB601_WIDE[CSC_ROW][CSC_COL] = {
	{0x100, 0x000, 0x15f, 0x000, 0x0},
	{0x100, 0x7ab, 0x74e, 0x180, 0x0},
	{0x100, 0x1bb, 0x000, 0x180, 0x0}
};

static int CSC_COE_RGB2YUV601_WIDE[CSC_ROW][CSC_COL] = {
	{0x04d, 0x096, 0x01d, 0x0, 0x000},
	{0x7d5, 0x79b, 0x083, 0x0, 0x080},
	{0x083, 0x793, 0x7ec, 0x0, 0x080},
};

static int CSC_COE_YUV2RGB709_WIDE[CSC_ROW][CSC_COL] = {
	{0x100, 0x000, 0x18a, 0x000, 0x0},
	{0x100, 0x7d2, 0x78b, 0x180, 0x0},
	{0x100, 0x1d1, 0x000, 0x180, 0x0},
};

static int CSC_COE_RGB2YUV709_WIDE[CSC_ROW][CSC_COL] = {
	{0x037, 0x0b7, 0x012, 0x0, 0x000},
	{0x7e3, 0x79c, 0x083, 0x0, 0x080},
	{0x083, 0x78a, 0x7f5, 0x0, 0x080},
};

void hisi_dss_csc_init(char __iomem *csc_base, dss_csc_t *s_csc)
{
	BUG_ON(csc_base == NULL);
	BUG_ON(s_csc == NULL);

	memset(s_csc, 0, sizeof(dss_csc_t));

	s_csc->idc = inp32(csc_base + CSC_IDC);
	s_csc->odc = inp32(csc_base + CSC_ODC);
	s_csc->p0 = inp32(csc_base + CSC_P0);
	s_csc->p1 = inp32(csc_base + CSC_P1);
	s_csc->p2 = inp32(csc_base + CSC_P2);
	s_csc->p3 = inp32(csc_base + CSC_P3);
	s_csc->p4 = inp32(csc_base + CSC_P4);
	s_csc->icg_module = inp32(csc_base + CSC_ICG_MODULE);
}

void hisi_dss_csc_set_reg(struct hisi_fb_data_type *hisifd,
	char __iomem *csc_base, dss_csc_t *s_csc)
{
	BUG_ON(hisifd == NULL);
	BUG_ON(csc_base == NULL);
	BUG_ON(s_csc == NULL);

	hisifd->set_reg(hisifd, csc_base + CSC_IDC, s_csc->idc, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_ODC, s_csc->odc, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_P0, s_csc->p0, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_P1, s_csc->p1, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_P2, s_csc->p2, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_P3, s_csc->p3, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_P4, s_csc->p4, 32, 0);
	hisifd->set_reg(hisifd, csc_base + CSC_ICG_MODULE, s_csc->icg_module, 32, 0);
}

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

	if (!isYUV(format))
		return 0;

	if (csc_mode == DSS_CSC_601_WIDE) {
		csc_coe_yuv2rgb = CSC_COE_YUV2RGB601_WIDE;
		csc_coe_rgb2yuv = CSC_COE_RGB2YUV601_WIDE;
	} else if (csc_mode == DSS_CSC_601_NARROW) {
		csc_coe_yuv2rgb = CSC_COE_YUV2RGB601_NARROW;
		csc_coe_rgb2yuv = CSC_COE_RGB2YUV601_NARROW;
	} else if (csc_mode == DSS_CSC_709_WIDE) {
		csc_coe_yuv2rgb = CSC_COE_YUV2RGB709_WIDE;
		csc_coe_rgb2yuv = CSC_COE_RGB2YUV709_WIDE;
	} else if (csc_mode == DSS_CSC_709_NARROW) {
		csc_coe_yuv2rgb = CSC_COE_YUV2RGB709_NARROW;
		csc_coe_rgb2yuv = CSC_COE_RGB2YUV709_NARROW;
	} else {
		HISI_FB_ERR("not support this csc_mode(%d)!\n", csc_mode);
		csc_coe_yuv2rgb = CSC_COE_YUV2RGB601_WIDE;
		csc_coe_rgb2yuv = CSC_COE_RGB2YUV601_WIDE;
	}

	csc = &(hisifd->dss_module.csc[chn_idx]);
	hisifd->dss_module.csc_used[chn_idx] = 1;

	if (layer) {
		csc->idc = set_bits32(csc->idc, 0x1, 1, 27);
		csc->idc = set_bits32(csc->idc,
			(csc_coe_yuv2rgb[2][3] |
			(csc_coe_yuv2rgb[1][3] << 9) |
			(csc_coe_yuv2rgb[0][3] << 18)), 27, 0);

		csc->odc = set_bits32(csc->odc,
			(csc_coe_yuv2rgb[2][4] |
			(csc_coe_yuv2rgb[1][4] << 9) |
			(csc_coe_yuv2rgb[0][4] << 18)), 27, 0);

		csc->p0 = set_bits32(csc->p0, csc_coe_yuv2rgb[0][0], 11, 0);
		csc->p0 = set_bits32(csc->p0, csc_coe_yuv2rgb[0][1], 11, 16);

		csc->p1 = set_bits32(csc->p1, csc_coe_yuv2rgb[0][2], 11, 0);
		csc->p1 = set_bits32(csc->p1, csc_coe_yuv2rgb[1][0], 11, 16);

		csc->p2 = set_bits32(csc->p2, csc_coe_yuv2rgb[1][1], 11, 0);
		csc->p2 = set_bits32(csc->p2, csc_coe_yuv2rgb[1][2], 11, 16);

		csc->p3 = set_bits32(csc->p3, csc_coe_yuv2rgb[2][0], 11, 0);
		csc->p3 = set_bits32(csc->p3, csc_coe_yuv2rgb[2][1], 11, 16);

		csc->p4 = set_bits32(csc->p4, csc_coe_yuv2rgb[2][2], 11, 0);
	}

	if (wb_layer) {
		csc->idc = set_bits32(csc->idc, 0x1, 1, 27);
		csc->idc = set_bits32(csc->idc,
			(csc_coe_rgb2yuv[2][3] |
			(csc_coe_rgb2yuv[1][3] << 9) |
			(csc_coe_rgb2yuv[0][3] << 18)), 27, 0);

		csc->odc = set_bits32(csc->odc,
			(csc_coe_rgb2yuv[2][4] |
			(csc_coe_rgb2yuv[1][4] << 9) |
			(csc_coe_rgb2yuv[0][4] << 18)), 27, 0);

		csc->p0 = set_bits32(csc->p0, csc_coe_rgb2yuv[0][0], 11, 0);
		csc->p0 = set_bits32(csc->p0, csc_coe_rgb2yuv[0][1], 11, 16);

		csc->p1 = set_bits32(csc->p1, csc_coe_rgb2yuv[0][2], 11, 0);
		csc->p1 = set_bits32(csc->p1, csc_coe_rgb2yuv[1][0], 11, 16);

		csc->p2 = set_bits32(csc->p2, csc_coe_rgb2yuv[1][1], 11, 0);
		csc->p2 = set_bits32(csc->p2, csc_coe_rgb2yuv[1][2], 11, 16);

		csc->p3 = set_bits32(csc->p3, csc_coe_rgb2yuv[2][0], 11, 0);
		csc->p3 = set_bits32(csc->p3, csc_coe_rgb2yuv[2][1], 11, 16);

		csc->p4 = set_bits32(csc->p4, csc_coe_rgb2yuv[2][2], 27, 0);
	}

	csc->icg_module = set_bits32(csc->icg_module, 0x1, 1, 0);

	return 0;
}

void hisi_dss_mctl_ov_set_ctl_dbg_reg(struct hisi_fb_data_type *hisifd, char __iomem *mctl_dgb)
{
	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is null");
		return;
	}

	if (is_mipi_cmd_panel(hisifd) && (hisifd->ldi_data_gate_en == 1)) {
		//open underflow clear
		set_reg(mctl_dgb, 0x782620, 32, 0);
	} else {
		//open underflow clear
		set_reg(mctl_dgb, 0x78A620, 32, 0);
	}
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

//debug
void hisifb_disreset_dss(struct hisi_fb_data_type *hisifd)
{

}

void hisifb_sctrl_clk_rst_all_open(struct hisi_fb_data_type *hisifd)
{

}

void hisifb_crgperi_clk_rst_all_open(struct hisi_fb_data_type *hisifd)
{

}




