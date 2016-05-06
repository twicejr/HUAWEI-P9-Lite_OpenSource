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
#include "hisi_overlay_utils.h"

/*******************************************************************************
** handle isr
*/
#if defined (CONFIG_HUAWEI_DSM)
void dss_get_power_clk_status(struct hisi_fb_data_type *hisifd)
{
	static int already_dump = 0;
	u32 temp_reg_base = 0;

	if (hisifd == NULL) {
		return;
	}

	if (already_dump) return;
/* PERI_CRG */
#define PERCLKEN0 (0x08)
#define PERCLKEN1 (0x18)
#define PERCLKEN4 (0x48)
#define PERRSTSTAT0 (0x68)
#define PERRSTSTAT1 (0x74)
#define PERRSTSTAT2 (0x80)
#define PERRSTSTAT4 (0x98)
#define PERRSTSTAT5 (0xA4)
#define PERI_STAT2 (0x118)
#define PERI_STAT3 (0x11C)
#define PERPWRSTAT (0x158)
#define PERPWRACK  (0x15C)
	HISI_FB_ERR("----- PERI_CRG dump ----\n");
	temp_reg_base = 0xFFF35000;
	HISI_FB_ERR("PERCLKEN0[0x%x]=0x%x \n \
				 PERCLKEN1[0x%x]=0x%x \n \
				 PERCLKEN2[0x%x]=0x%x \n \
				 PERCLKEN3[0x%x]=0x%x \n \
				 PERCLKEN4[0x%x]=0x%x \n \
				 PERCLKEN5[0x%x]=0x%x \n \
				 PERRSTSTAT0[0x%x]=0x%x \n \
				 PERRSTSTAT1[0x%x]=0x%x \n \
				 PERRSTSTAT2[0x%x]=0x%x \n \
				 PERRSTSTAT3[0x%x]=0x%x \n \
				 PERRSTSTAT4[0x%x]=0x%x \n \
				 PERRSTSTAT5[0x%x]=0x%x \n \
				 CLKDIV5[0x%x]=0x%x \n \
				 CLKDIV18[0x%x]=0x%x \n \
				 PERI_STAT2[0x%x]=0x%x \n \
				 PERI_STAT3[0x%x]=0x%x \n \
				 PERPWRSTAT[0x%x]=0x%x \n \
				 PERPWRACK[0x%x]=0x%x \n",
		temp_reg_base + PERCLKEN0, inp32(hisifd->peri_crg_base + PERCLKEN0),
		temp_reg_base + PERCLKEN1, inp32(hisifd->peri_crg_base + PERCLKEN1),
		temp_reg_base + PERCLKEN2, inp32(hisifd->peri_crg_base + PERCLKEN2),
		temp_reg_base + PERCLKEN3, inp32(hisifd->peri_crg_base + PERCLKEN3),
		temp_reg_base + PERCLKEN4, inp32(hisifd->peri_crg_base + PERCLKEN4),
		temp_reg_base + PERCLKEN5, inp32(hisifd->peri_crg_base + PERCLKEN5),
		temp_reg_base + PERRSTSTAT0, inp32(hisifd->peri_crg_base + PERRSTSTAT0),
		temp_reg_base + PERRSTSTAT1, inp32(hisifd->peri_crg_base + PERRSTSTAT1),
		temp_reg_base + PERRSTSTAT2, inp32(hisifd->peri_crg_base + PERRSTSTAT2),
		temp_reg_base + PERRSTSTAT3, inp32(hisifd->peri_crg_base + PERRSTSTAT3),
		temp_reg_base + PERRSTSTAT4, inp32(hisifd->peri_crg_base + PERRSTSTAT4),
		temp_reg_base + PERRSTSTAT5, inp32(hisifd->peri_crg_base + PERRSTSTAT5),
		temp_reg_base + CLKDIV5, inp32(hisifd->peri_crg_base + CLKDIV5),
		temp_reg_base + CLKDIV18, inp32(hisifd->peri_crg_base + CLKDIV18),
		temp_reg_base + PERI_STAT2, inp32(hisifd->peri_crg_base + PERI_STAT2),
		temp_reg_base + PERI_STAT3, inp32(hisifd->peri_crg_base + PERI_STAT3),
		temp_reg_base + PERPWRSTAT, inp32(hisifd->peri_crg_base + PERPWRSTAT),
		temp_reg_base + PERPWRACK, inp32(hisifd->peri_crg_base + PERPWRACK));
/* scrtl */
#define SCPWRSTAT (0x68)
#define SCPERCLKEN0 (0x168)
#define SCPERRSTSTAT0 (0x208)
#define SCPERRSTSTAT1 (0x214)
#define SCCLKDIV2 	  (0x258)
	HISI_FB_ERR("----- scrtl dump ----\n");
	temp_reg_base = 0xFFF0A000;
	HISI_FB_ERR("SCPWRSTAT[0x%x]=0x%x \n \
				 SCPERCLKEN0[0x%x]=0x%x \n \
				 SCPERCLKEN1[0x%x]=0x%x \n \
				 SCPERRSTSTAT0[0x%x]=0x%x \n \
				 SCPERRSTSTAT1[0x%x]=0x%x \n \
				 SCCLKDIV2[0x%x]=0x%x \n",
		temp_reg_base + SCPWRSTAT, inp32(hisifd->sctrl_base + SCPWRSTAT),
		temp_reg_base + SCPERCLKEN0, inp32(hisifd->sctrl_base + SCPERCLKEN0),
		temp_reg_base + SCPERCLKEN1, inp32(hisifd->sctrl_base + SCPERCLKEN1),
		temp_reg_base + SCPERRSTSTAT0, inp32(hisifd->sctrl_base + SCPERRSTSTAT0),
		temp_reg_base + SCPERRSTSTAT1, inp32(hisifd->sctrl_base + SCPERRSTSTAT1),
		temp_reg_base + SCCLKDIV2, inp32(hisifd->sctrl_base + SCCLKDIV2));

	/* mmbuf */
	HISI_FB_ERR("----- mmbuf dump ----\n");
	temp_reg_base = 0xFFF02000;
	HISI_FB_ERR("SMC_LOCK[0x%x]=0x%x \n \
				 SMC_MEM_LP[0x%x]=0x%x \n \
				 SMC_GCLK_CS[0x%x]=0x%x \n \
				 SMC_QOS_BACKDOOR[0x%x]=0x%x \n \
				 SMC_DFX_WCMD_CNT_1ST[0x%x]=0x%x \n \
				 SMC_DFX_WCMD_CNT_2ND[0x%x]=0x%x \n \
				 SMC_DFX_WCMD_CNT_3RD[0x%x]=0x%x \n \
				 SMC_DFX_WCMD_CNT_4TH[0x%x]=0x%x \n \
				 SMC_DFX_RCMD_CNT_1ST[0x%x]=0x%x \n \
				 SMC_DFX_RCMD_CNT_2ND[0x%x]=0x%x \n \
				 SMC_DFX_RCMD_CNT_3RD[0x%x]=0x%x \n \
				 SMC_DFX_RCMD_CNT_4TH[0x%x]=0x%x \n \
				 SMC_CS_IDLE[0x%x]=0x%x \n \
				 SMC_DFX_BFIFO_CNT0[0x%x]=0x%x \n \
				 SMC_DFX_RDFIFO_CNT1[0x%x]=0x%x \n \
				 SMC_SP_SRAM_STATE0[0x%x]=0x%x \n \
				 SMC_SP_SRAM_STATE1[0x%x]=0x%x \n",
		temp_reg_base + SMC_LOCK, inp32(hisifd->mmbuf_crg_base + SMC_LOCK),
		temp_reg_base + SMC_MEM_LP, inp32(hisifd->mmbuf_crg_base + SMC_MEM_LP),
		temp_reg_base + SMC_GCLK_CS, inp32(hisifd->mmbuf_crg_base + SMC_GCLK_CS),
		temp_reg_base + SMC_QOS_BACKDOOR, inp32(hisifd->mmbuf_crg_base + SMC_QOS_BACKDOOR),
		temp_reg_base + SMC_DFX_WCMD_CNT_1ST, inp32(hisifd->mmbuf_crg_base + SMC_DFX_WCMD_CNT_1ST),
		temp_reg_base + SMC_DFX_WCMD_CNT_2ND, inp32(hisifd->mmbuf_crg_base + SMC_DFX_WCMD_CNT_2ND),
		temp_reg_base + SMC_DFX_WCMD_CNT_3RD, inp32(hisifd->mmbuf_crg_base + SMC_DFX_WCMD_CNT_3RD),
		temp_reg_base + SMC_DFX_WCMD_CNT_4TH, inp32(hisifd->mmbuf_crg_base + SMC_DFX_WCMD_CNT_4TH),
		temp_reg_base + SMC_DFX_RCMD_CNT_1ST, inp32(hisifd->mmbuf_crg_base + SMC_DFX_RCMD_CNT_1ST),
		temp_reg_base + SMC_DFX_RCMD_CNT_2ND, inp32(hisifd->mmbuf_crg_base + SMC_DFX_RCMD_CNT_2ND),
		temp_reg_base + SMC_DFX_RCMD_CNT_3RD, inp32(hisifd->mmbuf_crg_base + SMC_DFX_RCMD_CNT_3RD),
		temp_reg_base + SMC_DFX_RCMD_CNT_4TH, inp32(hisifd->mmbuf_crg_base + SMC_DFX_RCMD_CNT_4TH),
		temp_reg_base + SMC_CS_IDLE, inp32(hisifd->mmbuf_crg_base + SMC_CS_IDLE),
		temp_reg_base + SMC_DFX_BFIFO_CNT0, inp32(hisifd->mmbuf_crg_base + SMC_DFX_BFIFO_CNT0),
		temp_reg_base + SMC_DFX_RDFIFO_CNT1, inp32(hisifd->mmbuf_crg_base + SMC_DFX_RDFIFO_CNT1),
		temp_reg_base + SMC_SP_SRAM_STATE0, inp32(hisifd->mmbuf_crg_base + SMC_SP_SRAM_STATE0),
		temp_reg_base + SMC_SP_SRAM_STATE1, inp32(hisifd->mmbuf_crg_base + SMC_SP_SRAM_STATE1));

		already_dump = 1;
}

void dss_underflow_stop_perf_state(struct hisi_fb_data_type *hisifd)
{
#ifdef DSS_DEVMEM_PERF_BASE
	void __iomem * perf_stat_base;

	if (inp32(hisifd->peri_crg_base + CRG_PERIPH_APB_PERRSTSTAT0_REG) & (1 << CRG_PERIPH_APB_IP_RST_PERF_STAT_BIT)) {
		HISI_FB_INFO("Failed : perf might not be used");
		return ;
	}

	perf_stat_base = ioremap(DSS_DEVMEM_PERF_BASE, DEVMEM_PERF_SIZE);
	outp32(perf_stat_base + PERF_SAMPSTOP_REG, 0x1);
	iounmap(perf_stat_base);
	HISI_FB_INFO("OK : perf state stop succ");
#endif
}

void dss_underflow_debug_func(struct work_struct *work)
{
	struct clk *ddr_clk = NULL;
	unsigned long curr_ddr = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	static u32 underflow_index = 0;
	static ktime_t underflow_timestamp[UNDERFLOW_EXPIRE_COUNT];
	s64 underflow_msecs = 0;
	static bool init_underflow_timestamp = false;
	int i;

	if (!init_underflow_timestamp) {
		underflow_timestamp[underflow_index] = ktime_get();
		underflow_index ++;
	}
	if (underflow_index == UNDERFLOW_EXPIRE_COUNT) {
		init_underflow_timestamp = true;
		underflow_timestamp[UNDERFLOW_EXPIRE_COUNT - 1] = ktime_get();
		underflow_msecs = ktime_to_ms(underflow_timestamp[UNDERFLOW_EXPIRE_COUNT - 1]) - ktime_to_ms(underflow_timestamp[0]);
		for(i = 0; i < UNDERFLOW_EXPIRE_COUNT - 1; i ++)
			underflow_timestamp[i] = underflow_timestamp[i+1];
	}

	ddr_clk = clk_get(NULL, "clk_ddrc_freq");
	if (ddr_clk) {
		curr_ddr = clk_get_rate(ddr_clk);
		clk_put(ddr_clk);
	} else {
		HISI_FB_ERR("Get ddr clk failed");
	}

	if (work) {
		hisifd = container_of(work, struct hisi_fb_data_type, dss_underflow_debug_work);
		if (g_underflow_stop_perf_stat) {
			dumpDssOverlay(hisifd, &hisifd->ov_req, false);
		}
	} else {
		HISI_FB_ERR("Get hisifd failed");
	}

	HISI_FB_INFO("Current ddr is %lu\n", curr_ddr);

	if ((underflow_msecs <= UNDERFLOW_INTERVAL) && (underflow_msecs > 0)) {
		HISI_FB_INFO("abnormal, underflow times:%d, interval:%llu, expire interval:%d\n", UNDERFLOW_EXPIRE_COUNT, underflow_msecs, UNDERFLOW_INTERVAL);
	} else {
		HISI_FB_INFO("normal, underflow times:%d, interval:%llu, expire interval:%d\n", UNDERFLOW_EXPIRE_COUNT, underflow_msecs, UNDERFLOW_INTERVAL);
	#ifdef CONFIG_HISI_FB_6250
		dss_get_power_clk_status(hisifd);
	#endif
		return;
	}

	if (!dsm_client_ocuppy(lcd_dclient)) {
		dsm_client_record(lcd_dclient, "ldi underflow!\n");
		dsm_client_notify(lcd_dclient, DSM_LCD_LDI_UNDERFLOW_NO);
	}

}

void dss_smmu_isr_dump_layer_info(uint32_t block_num, struct dss_overlay_block *layer_block)
{
	dss_overlay_block_t *block_info;
	dss_layer_t *layer_info;
	uint32_t chn_idx = 0;
	int i = 0;
	int j = 0;

	if (layer_block == NULL) {
		return;
	}

	if (block_num > HISI_DSS_OV_BLOCK_NUMS) {
		return;
	}

	for (i = 0; i < block_num; i++) {
		block_info = &layer_block[i];
		for (j = 0; j < block_info->layer_nums; j++) {
			layer_info = &block_info->layer_infos[j];
			if (!(chn_idx & (1 << layer_info->chn_idx))) {
				chn_idx |= 1 << layer_info->chn_idx;
				HISI_FB_ERR("shared_fd = %d, chn_idx = %d, layer_idx = %d, need_cap = 0x%x, vir_addr = 0x%llx, buf_size = 0x%x, format =%d \n",
							layer_info->img.shared_fd, layer_info->chn_idx, layer_info->layer_idx, layer_info->need_cap,
							layer_info->img.vir_addr, layer_info->img.buf_size, layer_info->img.format);
			}
		}
	}
}

void dss_smmu_isr_dump_layer_buf(struct hisi_fb_data_type *hisifd)
{
	struct hisifb_layerbuf *node, *_node_;

	if (hisifd == NULL) {
		return;
	}

	g_debug_layerbuf_sync = 3;
	list_for_each_entry_safe(node, _node_, &hisifd->buf_sync_ctrl.layerbuf_list, list_node) {
		if (node) {
			HISI_FB_ERR("node->frame_no = %d, node->shared_fd = %d, node->ion_handle = %p, node->vaddr = 0x%llx, chn_idx = %d, mmbuf = 0x%x \n",
						 node->frame_no, node->shared_fd, node->ion_handle, node->vir_addr, node->chn_idx, node->mmbuf.addr);
		}
	}

	HISI_FB_ERR("current frame no = %d,current ov_block_infos: \n", hisifd->ov_req.frame_no);
	dss_smmu_isr_dump_layer_info(hisifd->ov_req.ov_block_nums, (dss_overlay_block_t *)(hisifd->ov_req.ov_block_infos_ptr));

	HISI_FB_ERR("prev frame no = %d,prev ov_block_infos: \n", hisifd->ov_req_prev.frame_no);
	dss_smmu_isr_dump_layer_info(hisifd->ov_req_prev.ov_block_nums, (dss_overlay_block_t *)(hisifd->ov_req_prev.ov_block_infos_ptr));

	HISI_FB_ERR("ov_req_prev_prev frame no = %d,ov_req_prev_prev ov_block_infos: \n", hisifd->ov_req_prev_prev.frame_no);
	dss_smmu_isr_dump_layer_info(hisifd->ov_req_prev_prev.ov_block_nums, (dss_overlay_block_t *)(hisifd->ov_req_prev_prev.ov_block_infos_ptr));
}
#endif
irqreturn_t dss_pdp_isr(int irq, void *ptr)
{
	struct hisi_fb_data_type *hisifd = NULL;
	uint32_t isr_s1 = 0;
	uint32_t isr_s2 = 0;
	uint32_t isr_s2_dpp = 0;
#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
	uint32_t isr_s2_rch = 0;
#endif
	uint32_t isr_s2_smmu = 0;
	uint32_t mask = 0;
	uint32_t isr_te_vsync = 0;
	uint32_t i = 0;
	uint32_t temp = 0;
	struct timeval tv;
	struct hisifb_secure *secure_ctrl = NULL;
	dss_module_reg_t *dss_module = NULL;

	hisifd = (struct hisi_fb_data_type *)ptr;
	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);
	BUG_ON(secure_ctrl == NULL);
	dss_module = &(hisifd->dss_module);

#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
	isr_s1 = inp32(hisifd->dss_base + GLB_CPU_PDP_INTS);
	isr_s2 = inp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INTS);
	isr_s2_dpp = inp32(hisifd->dss_base + GLB_GLB_DPP_INTS);
	isr_s2_rch = inp32(hisifd->dss_base + GLB_RCH_CE_INTS);
	isr_s2_smmu = inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTSTAT_NS);

	outp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTCLR_NS, isr_s2_smmu);
	outp32(hisifd->dss_base + GLB_RCH_CE_INTS, isr_s2_rch);
	outp32(hisifd->dss_base + GLB_GLB_DPP_INTS, isr_s2_dpp);
	outp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INTS, isr_s2);
	outp32(hisifd->dss_base + GLB_CPU_PDP_INTS, isr_s1);

	isr_s1 &= ~(inp32(hisifd->dss_base + GLB_CPU_PDP_INT_MSK));
	isr_s2 &= ~(inp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INT_MSK));
	isr_s2_dpp &= ~(inp32(hisifd->dss_base + GLB_GLB_DPP_INT_MSK));
	isr_s2_rch &= ~(inp32(hisifd->dss_base + GLB_RCH_CE_INT_MSK));

#elif defined(CONFIG_HISI_FB_3660)
	isr_s1 = inp32(hisifd->dss_base + GLB_CPU_PDP_INTS);
	isr_s2 = inp32(hisifd->dss_base + DSS_LDI0_OFFSET + LDI_CPU_ITF_INTS);
	isr_s2_dpp = inp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_INTS);
	isr_s2_smmu = inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTSTAT_NS);

	outp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTCLR_NS, isr_s2_smmu);
	outp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_INTS, isr_s2_dpp);
	outp32(hisifd->dss_base + DSS_LDI0_OFFSET + LDI_CPU_ITF_INTS, isr_s2);
	outp32(hisifd->dss_base + GLB_CPU_PDP_INTS, isr_s1);

	isr_s1 &= ~(inp32(hisifd->dss_base + GLB_CPU_PDP_INT_MSK));
	isr_s2 &= ~(inp32(hisifd->dss_base + DSS_LDI0_OFFSET + LDI_CPU_ITF_INT_MSK));
	isr_s2_dpp &= ~(inp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_INT_MSK));
#endif

	if (is_mipi_cmd_panel(hisifd)) {
		isr_te_vsync = BIT_LCD_TE0_PIN;
	} else {
		isr_te_vsync = BIT_VSYNC;
	}

	if (isr_s2 & BIT_VACTIVE0_END) {
		hisifd->vactive0_end_flag = 1;

		if (hisifd->color_temperature_flag > 0)
			hisifd->color_temperature_flag--;

		if (hisifd->mipi_dsi_bit_clk_upt_isr_handler &&
			hisifd->panel_info.dsi_bit_clk_upt_support &&
			!(isr_s2 & BIT_VACTIVE0_START)) {
			hisifd->mipi_dsi_bit_clk_upt_isr_handler(hisifd);
		}

		if (g_err_status & DSS_PDP_LDI_UNDERFLOW) {
			temp = inp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_DBG_CNT);
			HISI_FB_INFO("BIT_VACTIVE0_END:frame_no = %d,dpp_dbg = 0x%x\n", hisifd->ov_req.frame_no, temp);
			g_err_status &= ~DSS_PDP_LDI_UNDERFLOW;
		}
	}

	if (isr_s2 & BIT_VACTIVE0_START) {
		if (hisifd->ov_vactive0_start_isr_handler)
			hisifd->ov_vactive0_start_isr_handler(hisifd);

		if (secure_ctrl->notify_secure_switch) {
			secure_ctrl->notify_secure_switch(hisifd);
		}

		if (hisifd->mipi_dsi_bit_clk_upt_isr_handler &&
			hisifd->panel_info.dsi_bit_clk_upt_support &&
			is_mipi_video_panel(hisifd) &&
			(hisifd->panel_info.mipi.dsi_bit_clk_upt != hisifd->panel_info.mipi.dsi_bit_clk)) {
			disable_ldi(hisifd);
			hisifd->video_ldi_dis_at_vac_start = true;
		}

		if (g_err_status & DSS_PDP_LDI_UNDERFLOW) {
		    temp = inp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_DBG_CNT);
			HISI_FB_INFO("BIT_VACTIVE0_START frame_no = %d,dpp_dbg = 0x%x\n", hisifd->ov_req.frame_no, temp);
		}
	}

	if (isr_s2 & isr_te_vsync) {

		if (hisifd->vsync_isr_handler) {
			hisifd->vsync_isr_handler(hisifd);
		}

		if (hisifd->buf_sync_signal) {
			hisifd->buf_sync_signal(hisifd);
		}


		if (g_err_status & (DSS_PDP_LDI_UNDERFLOW | DSS_PDP_SMMU_ERR | DSS_SDP_SMMU_ERR)) {
			temp = inp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_DBG_CNT);
			HISI_FB_INFO("isr_te_vsync:frame_no = %d,dpp_dbg = 0x%x\n", hisifd->ov_req.frame_no, temp);
		}

		if (g_debug_ldi_underflow) {
			hisifb_get_timestamp(&tv);
			HISI_FB_INFO("isr_te_vsync:frame_no = %d,isr_s2 = 0x%x\n", hisifd->ov_req.frame_no, isr_s2);
		}
	}

	if (isr_s2 & BIT_LDI_UNFLOW) {
#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
		mask = inp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INT_MSK);
		mask |= BIT_LDI_UNFLOW;
		outp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INT_MSK, mask);
#elif defined(CONFIG_HISI_FB_3660)
		mask = inp32(hisifd->dss_base + DSS_LDI0_OFFSET + LDI_CPU_ITF_INT_MSK);
		mask |= BIT_LDI_UNFLOW;
		outp32(hisifd->dss_base + DSS_LDI0_OFFSET + LDI_CPU_ITF_INT_MSK, mask);
#endif
		if (g_debug_ldi_underflow_clear) {
			if (is_mipi_cmd_panel(hisifd)) {
				if (g_ldi_data_gate_en == 0) {
					if (hisifd->ldi_underflow_wq) {
						disable_ldi(hisifd);
						queue_work(hisifd->ldi_underflow_wq, &hisifd->ldi_underflow_work);
					}
				}
			} else {
				if (hisifd->ldi_underflow_wq) {
					disable_ldi(hisifd);
					queue_work(hisifd->ldi_underflow_wq, &hisifd->ldi_underflow_work);
				}
			}
		}

		if (g_debug_ldi_underflow) {
			if (g_debug_ovl_online_composer) {
				if (hisifd->dss_debug_wq)
					queue_work(hisifd->dss_debug_wq, &hisifd->dss_debug_work);
			}
		}

		g_err_status |= DSS_PDP_LDI_UNDERFLOW;

		if (hisifd->ldi_data_gate_en == 0) {
			temp = inp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_DBG_CNT);
			HISI_FB_INFO("ldi underflow! frame_no = %d,dpp_dbg = 0x%x!\n", hisifd->ov_req.frame_no,temp);

			for (i = 0; i < DSS_WCHN_W0; i++) {
			    if ((i != DSS_RCHN_V0) && (i != DSS_RCHN_G0)) {
					HISI_FB_INFO("ldi underflow!! rch%d, DMA_BUF_DBG0 = 0x%x,DMA_BUF_DBG1 = 0x%x!!\n", i,
						inp32(dss_module->dma_base[i]+ DMA_BUF_DBG0),
						inp32(dss_module->dma_base[i]+ DMA_BUF_DBG1));
				}
			}

			for (i = 0; i < 18; i++) {
				HISI_FB_INFO("ldi underflow!!! i=%d,MCTL_MODx_STATUS = 0x%x\n",
					i, inp32(dss_module->mctl_sys_base + MCTL_MOD0_STATUS + i * 0x4));
			}

			#if defined (CONFIG_HUAWEI_DSM)
			if (hisifd->dss_underflow_debug_workqueue && !g_fake_lcd_flag)
				queue_work(hisifd->dss_underflow_debug_workqueue, &hisifd->dss_underflow_debug_work);
			#endif
		}
	}

#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
	if (isr_s2_rch & BIT_CE_END_RCH4_IND) {
		if (hisifd->panel_info.prefix_ce_support && hisifd->rch4_ce_end_wq) {
			queue_work(hisifd->rch4_ce_end_wq, &hisifd->rch4_ce_end_work);
		}
	}

	if (isr_s2_rch & BIT_CE_END_RCH2_IND) {
		if (hisifd->panel_info.prefix_ce_support && hisifd->rch2_ce_end_wq) {
			queue_work(hisifd->rch2_ce_end_wq, &hisifd->rch2_ce_end_work);
		}
	}

	if (isr_s2_dpp & BIT_CE_END_IND) {
		if (hisifd->panel_info.acm_ce_support
		 && g_dss_effect_acm_ce_en == 1
		 && hisifd->dpp_ce_end_wq
		 && HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_ACE)) {
			queue_work(hisifd->dpp_ce_end_wq, &hisifd->dpp_ce_end_work);
		}
	}

	if (isr_s2_dpp & BIT_BACKLIGHT_INTP) {
		hisifb_sbl_isr_handler(hisifd);
	}

	if (isr_s2_smmu & 0x3f) {
		if (g_debug_mmu_error == 1) {
			g_err_status |= DSS_PDP_SMMU_ERR;
			//dss_smmu_isr_dump_layer_buf(hisifd);
			HISI_FB_ERR("fb%d, SMMU_INTSTAT_NS=0x%x, SMMU_FAULT_ADDR=0x%x, SMMU_FAULT_ID=0x%x,"
				"SMMU_FAULT_INFO=0x%x!\n", hisifd->index, isr_s2_smmu,
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ADDR),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ID),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_INFO));
		#ifdef CONFIG_HISI_FB_6250
			//dss_get_power_clk_status(hisifd);
		#endif
		}
	} else {
		g_err_status &= ~DSS_PDP_SMMU_ERR;
		if (g_debug_layerbuf_sync) {
			g_debug_layerbuf_sync--;
		}
	}

#endif

#ifdef CONFIG_HISI_FB_3660
	if (hisifd->sbl_enable && hisifd->panel_info.sbl_support) {
		if (isr_s2_dpp & BIT_SBL_SEND_FRAME_OUT) {
			HISI_FB_INFO("BIT_SBL_SEND_FRAME_OUT \n");
		}

		if (isr_s2_dpp & BIT_SBL_STOP_FRAME_OUT) {
			HISI_FB_INFO("BIT_SBL_STOP_FRAME_OUT \n");
		}

		if (isr_s2_dpp & BIT_SBL_BACKLIGHT_OUT) {
			HISI_FB_INFO("BIT_SBL_BACKLIGHT_OUT \n");
		}

		if (isr_s2_dpp & BIT_SBL_DARKENH_OUT) {
			HISI_FB_INFO("BIT_SBL_DARKENH_OUT \n");
		}

		if (isr_s2_dpp & BIT_SBL_BRIGHTPTR_OUT) {
			HISI_FB_INFO("BIT_SBL_BRIGHTPTR_OUT \n");
		}

		if (isr_s2_dpp & BIT_STRENGTH_INROI_OUT) {
			HISI_FB_INFO("BIT_STRENGTH_INROI_OUT \n");
		}

		if (isr_s2_dpp & BIT_STRENGTH_OUTROI_OUT) {
			HISI_FB_INFO("BIT_STRENGTH_OUTROI_OUT \n");
		}

		if (isr_s2_dpp & BIT_DONE_OUT) {
			HISI_FB_INFO("BIT_DONE_OUT \n");
		}

		if (isr_s2_dpp & BIT_PPROC_DONE_OUT) {
			HISI_FB_INFO("BIT_PPROC_DONE_OUT \n");
		}
	}

	if (isr_s2_dpp & BIT_HIACE_IND) {
		if (hisifd->panel_info.hiace_support
			&&hisifd->hiace_end_wq) {
			queue_work(hisifd->hiace_end_wq, &hisifd->hiace_end_work);
		}
	}

	if (isr_s2_dpp & BIT_CE_END_IND) {
		if (hisifd->panel_info.acm_ce_support
		 && hisifd->dpp_ce_end_wq) {
			queue_work(hisifd->dpp_ce_end_wq, &hisifd->dpp_ce_end_work);
		}
	}
#endif

	return IRQ_HANDLED;
}

irqreturn_t dss_sdp_isr(int irq, void *ptr)
{
	struct hisi_fb_data_type *hisifd = NULL;
	uint32_t isr_s1 = 0;
	uint32_t isr_s2 = 0;
	uint32_t isr_s2_smmu = 0;
	uint32_t mask = 0;

	hisifd = (struct hisi_fb_data_type *)ptr;
	BUG_ON(hisifd == NULL);

#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
	isr_s1 = inp32(hisifd->dss_base + GLB_CPU_SDP_INTS);
	isr_s2 = inp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INTS);
	isr_s2_smmu = inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTSTAT_NS);

	outp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTCLR_NS, isr_s2_smmu);
	outp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INTS, isr_s2);
	outp32(hisifd->dss_base + GLB_CPU_SDP_INTS, isr_s1);

	isr_s1 &= ~(inp32(hisifd->dss_base + GLB_CPU_SDP_INT_MSK));
	isr_s2 &= ~(inp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INT_MSK));
#elif defined(CONFIG_HISI_FB_3660)
	isr_s1 = inp32(hisifd->dss_base + GLB_CPU_SDP_INTS);
	isr_s2 = inp32(hisifd->dss_base + DSS_LDI1_OFFSET + LDI_CPU_ITF_INTS);
	isr_s2_smmu = inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTSTAT_NS);

	outp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTCLR_NS, isr_s2_smmu);
	outp32(hisifd->dss_base + DSS_LDI1_OFFSET + LDI_CPU_ITF_INTS, isr_s2);
	outp32(hisifd->dss_base + GLB_CPU_SDP_INTS, isr_s1);

	isr_s1 &= ~(inp32(hisifd->dss_base + GLB_CPU_SDP_INT_MSK));
	isr_s2 &= ~(inp32(hisifd->dss_base + DSS_LDI1_OFFSET + LDI_CPU_ITF_INT_MSK));
#endif

	if (isr_s2 & BIT_VACTIVE0_END) {
		hisifd->vactive0_end_flag = 1;
	}

	if (isr_s2 & BIT_VACTIVE0_START) {
		if (hisifd->ov_vactive0_start_isr_handler)
			hisifd->ov_vactive0_start_isr_handler(hisifd);
	}

	if (isr_s2 & BIT_VSYNC) {
		if (hisifd->vsync_isr_handler) {
			hisifd->vsync_isr_handler(hisifd);
		}

		if (hisifd->buf_sync_signal) {
			hisifd->buf_sync_signal(hisifd);
		}
	}

	if (isr_s2 & BIT_LDI_UNFLOW) {
#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
		mask = inp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INT_MSK);
		mask |= BIT_LDI_UNFLOW;
		outp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INT_MSK, mask);
#elif defined(CONFIG_HISI_FB_3660)
		mask = inp32(hisifd->dss_base + DSS_LDI1_OFFSET + LDI_CPU_ITF_INT_MSK);
		mask |= BIT_LDI_UNFLOW;
		outp32(hisifd->dss_base + DSS_LDI1_OFFSET + LDI_CPU_ITF_INT_MSK, mask);
#endif
		if (g_debug_ldi_underflow_clear) {
			if (is_mipi_cmd_panel(hisifd)) {
				if (g_ldi_data_gate_en == 0) {
					if (hisifd->ldi_underflow_wq) {
						disable_ldi(hisifd);
						queue_work(hisifd->ldi_underflow_wq, &hisifd->ldi_underflow_work);
					}
				}
			} else {
				if (hisifd->ldi_underflow_wq) {
					disable_ldi(hisifd);
					queue_work(hisifd->ldi_underflow_wq, &hisifd->ldi_underflow_work);
				}
			}
		}

		if (g_debug_ldi_underflow) {
			if (g_debug_ovl_online_composer) {
				if (hisifd->dss_debug_wq)
					queue_work(hisifd->dss_debug_wq, &hisifd->dss_debug_work);
			}
		}

		g_err_status |= DSS_SDP_LDI_UNDERFLOW;

		if (hisifd->ldi_data_gate_en == 0)
			HISI_FB_ERR("ldi underflow!\n");
	}

#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
	if (isr_s2_smmu & 0x3f) {
		if (g_debug_mmu_error == 1) {
			g_err_status |= DSS_PDP_SMMU_ERR;
			HISI_FB_INFO("fb%d, SMMU_FAULT_ADDR=0x%x, SMMU_FAULT_ID=0x%x, SMMU_FAULT_INFO=0x%x!\n",
				hisifd->index,
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ADDR),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ID),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_INFO));
		}
	} else {
		g_err_status &= ~DSS_PDP_SMMU_ERR;
	}
#endif
	return IRQ_HANDLED;
}

irqreturn_t dss_adp_isr(int irq, void *ptr)
{
	struct hisi_fb_data_type *hisifd = NULL;
	uint32_t isr_s1 = 0;
	uint32_t isr_s2_smmu = 0;

	hisifd = (struct hisi_fb_data_type *)ptr;
	BUG_ON(hisifd == NULL);

	isr_s1 = inp32(hisifd->dss_base + GLB_CPU_OFF_INTS);
	isr_s2_smmu = inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTSTAT_NS);

	outp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTCLR_NS, isr_s2_smmu);
	outp32(hisifd->dss_base + GLB_CPU_OFF_INTS, isr_s1);

	isr_s1 &= ~(inp32(hisifd->dss_base + GLB_CPU_OFF_INT_MSK));

#ifdef CONFIG_FIX_DSS_WCH_ISR_BUG
	if (isr_s1 & BIT_OFF_CMDLIST8) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH0] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH0] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH0]));
		}

		outp32(hisifd->dss_base + DSS_CMDLIST_OFFSET + CMDLIST_CH0_INTC + DSS_CMDLIST_W0 *0x40, 0xFF);
	}

	if (isr_s1 & BIT_OFF_CMDLIST9) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH1] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH1] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH1]));
		}

		outp32(hisifd->dss_base + DSS_CMDLIST_OFFSET + CMDLIST_CH0_INTC + DSS_CMDLIST_W1 *0x40, 0xFF);
	}
#else
	if (isr_s1 & BIT_OFF_WCH0_INTS) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH0] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH0] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH0]));
		}
	}

	if (isr_s1 & BIT_OFF_WCH1_INTS) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH1] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH1] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH1]));
		}
	}

	if (isr_s1 & BIT_OFF_WCH0_WCH1_FRM_END_INT) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH0_WCH1] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH0_WCH1] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH0_WCH1]));
		}
	}
#endif

#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
	if (isr_s2_smmu & 0x3f) {
		if (g_debug_mmu_error == 1) {
			HISI_FB_INFO("fb%d, SMMU_FAULT_ADDR=0x%x, SMMU_FAULT_ID=0x%x, SMMU_FAULT_INFO=0x%x!\n",
				hisifd->index,
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ADDR),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ID),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_INFO));
		}
	}
#endif  //TBD for chicago b020
	return IRQ_HANDLED;
}
