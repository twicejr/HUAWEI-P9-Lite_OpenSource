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
#include "hisi_dpe_utils.h"

void dss_underflow_stop_perf_state_online(struct hisi_fb_data_type *hisifd)
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


static int hisi_get_ov_data_from_user(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req, void __user *argp)
{
	int ret = 0;
	dss_overlay_block_t *pov_h_block_infos = NULL;

	BUG_ON(hisifd == NULL);
	BUG_ON(pov_req == NULL);

	if (NULL == argp) {
		HISI_FB_ERR("user data is invalid\n");
		return -EINVAL;
	}

	pov_h_block_infos = hisifd->ov_block_infos;

	ret = copy_from_user(pov_req, argp, sizeof(dss_overlay_t));
	if (ret) {
		HISI_FB_ERR("fb%d, copy_from_user failed!\n", hisifd->index);
		return -EINVAL;
	}

	if ((pov_req->ov_block_nums <= 0) ||
		(pov_req->ov_block_nums > HISI_DSS_OV_BLOCK_NUMS)) {
		HISI_FB_ERR("fb%d, ov_block_nums(%d) is out of range!\n",
			hisifd->index, pov_req->ov_block_nums);
		return -EINVAL;
	}

	ret = copy_from_user(pov_h_block_infos, (dss_overlay_block_t *)pov_req->ov_block_infos_ptr,
		pov_req->ov_block_nums * sizeof(dss_overlay_block_t));
	if (ret) {
		HISI_FB_ERR("fb%d, dss_overlay_block_t copy_from_user failed!\n",
			hisifd->index);
		return -EINVAL;
	}

	pov_req->ov_block_infos_ptr = (uint64_t)pov_h_block_infos;

	return ret;
}

int hisi_overlay_pan_display(struct hisi_fb_data_type *hisifd)
{
	int ret = 0;
	struct fb_info *fbi = NULL;
	dss_overlay_t *pov_req = NULL;
	dss_overlay_t *pov_req_prev = NULL;
	dss_overlay_block_t *pov_h_block_infos = NULL;
	dss_overlay_block_t *pov_h_block = NULL;
	dss_layer_t *layer = NULL;
	dss_rect_ltrb_t clip_rect;
	dss_rect_t aligned_rect;
	bool rdma_stretch_enable = false;
	uint32_t offset = 0;
	uint32_t addr = 0;
	int hal_format = 0;
	uint32_t cmdlist_pre_idxs = 0;
	uint32_t cmdlist_idxs = 0;
	int enable_cmdlist = 0;
	bool has_base = false;

	if (NULL == hisifd) {
		HISI_FB_ERR("hisi fd is invalid\n");
		return -EINVAL;
	}
	fbi = hisifd->fbi;
	if (NULL == fbi) {
		HISI_FB_ERR("hisifd fbi is invalid\n");
		return -EINVAL;
	}

	pov_req = &(hisifd->ov_req);
	pov_req_prev = &(hisifd->ov_req_prev);

	if (!hisifd->panel_power_on) {
		HISI_FB_INFO("fb%d, panel is power off!", hisifd->index);
		return 0;
	}

	if (g_debug_ldi_underflow) {
		if (g_err_status & (DSS_PDP_LDI_UNDERFLOW | DSS_SDP_LDI_UNDERFLOW))
			return 0;
	}

	offset = fbi->var.xoffset * (fbi->var.bits_per_pixel >> 3) +
		fbi->var.yoffset * fbi->fix.line_length;
	addr = fbi->fix.smem_start + offset;
	if (!fbi->fix.smem_start) {
		HISI_FB_ERR("fb%d, smem_start is null!\n", hisifd->index);
		return -EINVAL;
	}

	if (fbi->fix.smem_len <= 0) {
		HISI_FB_ERR("fb%d, smem_len(%d) is out of range!\n",
			hisifd->index, fbi->fix.smem_len);
		return -EINVAL;
	}

	hal_format = hisi_get_hal_format(fbi);
	if (hal_format < 0) {
		HISI_FB_ERR("fb%d, not support this fb_info's format!\n", hisifd->index);
		return -EINVAL;
	}

	enable_cmdlist = g_enable_ovl_cmdlist_online;
	if ((hisifd->index == EXTERNAL_PANEL_IDX) && hisifd->panel_info.fake_hdmi)
		enable_cmdlist = 0;

	hisifb_activate_vsync(hisifd);

	ret = hisi_vactive0_start_config(hisifd, pov_req);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, hisi_vactive0_start_config failed! ret = %d\n", hisifd->index, ret);
		goto err_return;
	}

	if (g_debug_ovl_online_composer == 1) {
		HISI_FB_INFO("offset=%u.\n", offset);
		dumpDssOverlay(hisifd, pov_req, false);
	}

	memset(pov_req, 0, sizeof(dss_overlay_t));
	pov_req->ov_block_infos_ptr = (uint64_t)(&(hisifd->ov_block_infos));
	pov_req->ov_block_nums = 1;
	pov_req->ovl_idx = DSS_OVL0;
	pov_req->dirty_rect.x = 0;
	pov_req->dirty_rect.y = 0;
	pov_req->dirty_rect.w = fbi->var.xres;
	pov_req->dirty_rect.h = fbi->var.yres;

	pov_req->res_updt_rect.x = 0;
	pov_req->res_updt_rect.y = 0;
	pov_req->res_updt_rect.w = fbi->var.xres;
	pov_req->res_updt_rect.h = fbi->var.yres;

	pov_h_block_infos = (dss_overlay_block_t *)(pov_req->ov_block_infos_ptr);
	pov_h_block = &(pov_h_block_infos[0]);
	pov_h_block->layer_nums = 1;

	layer = &(pov_h_block->layer_infos[0]);
	layer->img.format = hal_format;
	layer->img.width = fbi->var.xres;
	layer->img.height = fbi->var.yres;
	layer->img.bpp = fbi->var.bits_per_pixel >> 3;
	layer->img.stride = fbi->fix.line_length;
	layer->img.phy_addr = addr;
	layer->img.vir_addr = addr;
#ifdef CONFIG_HISI_FB_HEAP_CARVEOUT_USED
	layer->img.mmu_enable = 0;
#else
	layer->img.mmu_enable = 1;
#endif
	layer->src_rect.x = 0;
	layer->src_rect.y = 0;
	layer->src_rect.w = fbi->var.xres;
	layer->src_rect.h = fbi->var.yres;
	layer->dst_rect.x = 0;
	layer->dst_rect.y = 0;
	layer->dst_rect.w = fbi->var.xres;
	layer->dst_rect.h = fbi->var.yres;
	layer->transform = HISI_FB_TRANSFORM_NOP;
	layer->blending = HISI_FB_BLENDING_NONE;
	layer->glb_alpha = 0xFF;
	layer->color = 0x0;
	layer->layer_idx = 0x0;
	layer->chn_idx = DSS_RCHN_D2;
	layer->need_cap = 0;

	hisi_dss_handle_cur_ovl_req(hisifd, pov_req);

	ret = hisi_dss_module_init(hisifd);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, hisi_dss_module_init failed! ret = %d\n", hisifd->index, ret);
		goto err_return;
	}

	hisi_mmbuf_info_get_online(hisifd);

	if (enable_cmdlist) {
		hisifd->set_reg = hisi_cmdlist_set_reg;

		hisi_cmdlist_data_get_online(hisifd);

		ret = hisi_cmdlist_get_cmdlist_idxs(pov_req_prev, &cmdlist_pre_idxs, NULL);
		if (ret != 0) {
			HISI_FB_ERR("fb%d, hisi_cmdlist_get_cmdlist_idxs pov_req_prev failed! ret = %d\n", hisifd->index, ret);
			goto err_return;
		}

		ret = hisi_cmdlist_get_cmdlist_idxs(pov_req, &cmdlist_pre_idxs, &cmdlist_idxs);
		if (ret != 0) {
			HISI_FB_ERR("fb%d, hisi_cmdlist_get_cmdlist_idxs pov_req failed! ret = %d\n", hisifd->index, ret);
			goto err_return;
		}

		hisi_cmdlist_add_nop_node(hisifd, cmdlist_pre_idxs, 0, 0);
		hisi_cmdlist_add_nop_node(hisifd, cmdlist_idxs, 0, 0);
	} else {
		hisifd->set_reg = hisifb_set_reg;

		hisi_dss_mctl_mutex_lock(hisifd, pov_req->ovl_idx);
		cmdlist_pre_idxs = ~0;
	}

	hisi_dss_prev_module_set_regs(hisifd, pov_req_prev, cmdlist_pre_idxs, enable_cmdlist, NULL);

	hisi_dss_aif_handler(hisifd, pov_req, pov_h_block);

	ret = hisi_dss_ovl_base_config(hisifd, pov_req, NULL, NULL, pov_req->ovl_idx, 0);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, hisi_dss_ovl_init failed! ret = %d\n", hisifd->index, ret);
		goto err_return;
	}

	ret = hisi_ov_compose_handler(hisifd, pov_req, pov_h_block, layer, NULL, NULL,
		&clip_rect, &aligned_rect, &rdma_stretch_enable, &has_base, true, enable_cmdlist);
	if (ret != 0) {
		HISI_FB_ERR("hisi_ov_compose_handler failed! ret = %d\n", ret);
		goto err_return;
	}

	ret = hisi_dss_mctl_ov_config(hisifd, pov_req, pov_req->ovl_idx, has_base, true);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, hisi_dss_mctl_config failed! ret = %d\n", hisifd->index, ret);
		goto err_return;
	}

	if (hisifd->panel_info.dirty_region_updt_support) {
		ret= hisi_dss_dirty_region_dbuf_config(hisifd, pov_req);
		if (ret != 0) {
			HISI_FB_ERR("fb%d, hisi_dss_dirty_region_dbuf_config failed! ret = %d\n", hisifd->index, ret);
			goto err_return;
		}
	}

#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
	ret = hisi_dss_post_scf_config(hisifd, pov_req);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, hisi_dss_post_scf_config failed! ret = %d\n", hisifd->index, ret);
		goto err_return;
	}
#endif

	ret = hisi_dss_ov_module_set_regs(hisifd, pov_req->ovl_idx, enable_cmdlist, 0, 0, true);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, hisi_dss_module_config failed! ret = %d\n", hisifd->index, ret);
		goto err_return;
	}

	if (!g_fake_lcd_flag) {
		hisi_dss_unflow_handler(hisifd, pov_req, true);
	}

	if (enable_cmdlist) {
		//add taskend for share channel
		hisi_cmdlist_add_nop_node(hisifd, cmdlist_idxs, 0, 0);

		//remove ch cmdlist
		hisi_cmdlist_config_stop(hisifd, cmdlist_pre_idxs);

		cmdlist_idxs |= cmdlist_pre_idxs;
		hisi_cmdlist_flush_cache(hisifd, hisifd->ion_client, cmdlist_idxs);

		if (g_debug_ovl_cmdlist) {
			hisi_cmdlist_dump_all_node(hisifd, NULL, cmdlist_idxs);
		}

		hisi_cmdlist_config_start(hisifd, pov_req->ovl_idx, cmdlist_idxs, 0);
	} else {
		hisi_dss_mctl_mutex_unlock(hisifd, pov_req->ovl_idx);
	}

	if (hisifd->panel_info.dirty_region_updt_support) {
		hisi_dss_dirty_region_updt_config(hisifd, pov_req);
	}

	single_frame_update(hisifd);
	hisifb_frame_updated(hisifd);

	hisifb_deactivate_vsync(hisifd);

	hisifd->frame_count++;
	memcpy(&hisifd->ov_req_prev_prev, &hisifd->ov_req_prev, sizeof(dss_overlay_t));
	memcpy(&(hisifd->ov_block_infos_prev_prev), &(hisifd->ov_block_infos_prev),
		hisifd->ov_req_prev.ov_block_nums * sizeof(dss_overlay_block_t));
	hisifd->ov_req_prev_prev.ov_block_infos_ptr = (uint64_t)(&(hisifd->ov_block_infos_prev_prev));

	memcpy(&hisifd->ov_req_prev, pov_req, sizeof(dss_overlay_t));
	memcpy(&(hisifd->ov_block_infos_prev), &(hisifd->ov_block_infos),
		pov_req->ov_block_nums * sizeof(dss_overlay_block_t));
	hisifd->ov_req_prev.ov_block_infos_ptr = (uint64_t)(&(hisifd->ov_block_infos_prev));

	return 0;

err_return:
	if (is_mipi_cmd_panel(hisifd)) {
		hisifd->vactive0_start_flag = 1;
	} else {
		single_frame_update(hisifd);
	}
	hisifb_deactivate_vsync(hisifd);

	return ret;
}

int hisi_ov_online_play(struct hisi_fb_data_type *hisifd, void __user *argp)
{
	static int dss_free_buffer_refcount = 0;
	dss_overlay_t *pov_req = NULL;
	dss_overlay_t *pov_req_prev = NULL;
	dss_overlay_block_t *pov_h_block_infos = NULL;
	dss_overlay_block_t *pov_h_block = NULL;
	dss_layer_t *layer = NULL;
	dss_rect_ltrb_t clip_rect;
	dss_rect_t aligned_rect;
	bool rdma_stretch_enable = false;
	uint32_t cmdlist_pre_idxs = 0;
	uint32_t cmdlist_idxs = 0;
	int enable_cmdlist = 0;
	bool has_base = false;
#ifdef CONFIG_BUF_SYNC_USED
	unsigned long flags = 0;
#endif
	int need_skip = 0;
	int i = 0;
	int m = 0;
	int ret = 0;
	uint32_t timediff = 0;
	struct list_head lock_list;
	struct timeval tv0;
	struct timeval tv1;
	struct timeval tv2;
	struct timeval tv3;

	BUG_ON(hisifd == NULL);
	pov_req = &(hisifd->ov_req);
	pov_req_prev = &(hisifd->ov_req_prev);
	INIT_LIST_HEAD(&lock_list);

	if (!hisifd->panel_power_on) {
		HISI_FB_INFO("fb%d, panel is power off!\n", hisifd->index);
		return 0;
	}

	if (g_debug_ldi_underflow) {
		if (g_err_status & (DSS_PDP_LDI_UNDERFLOW | DSS_SDP_LDI_UNDERFLOW)) {
			dss_underflow_stop_perf_state_online(hisifd);
			mdelay(HISI_DSS_COMPOSER_HOLD_TIME);
			return 0;
		}
	}

	if (g_debug_ovl_online_composer_return) {
		return 0;
	}

	if (g_debug_ovl_online_composer_timediff & 0x2) {
		hisifb_get_timestamp(&tv0);
	}

	enable_cmdlist = g_enable_ovl_cmdlist_online;
	if ((hisifd->index == EXTERNAL_PANEL_IDX) && hisifd->panel_info.fake_hdmi) {
		enable_cmdlist = 0;
	}

	hisifb_activate_vsync(hisifd);

	if (g_debug_ovl_online_composer_timediff & 0x4) {
		hisifb_get_timestamp(&tv2);
	}

	ret = hisi_get_ov_data_from_user(hisifd, pov_req, argp);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, hisi_get_ov_data_from_user failed! ret=%d\n", hisifd->index, ret);
		need_skip = 1;
		goto err_return;
	}

#ifdef CONFIG_BUF_SYNC_USED
	if (is_mipi_video_panel(hisifd)) {
		ret = hisifb_buf_sync_handle(hisifd, pov_req);
		if (ret < 0) {
			HISI_FB_ERR("fb%d, hisifb_buf_sync_handle failed! ret=%d\n", hisifd->index, ret);
			need_skip = 1;
			goto err_return;
		}
	}
#endif

	ret = hisi_vactive0_start_config(hisifd, pov_req);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, hisi_vactive0_start_config failed! ret=%d\n", hisifd->index, ret);
		need_skip = 1;
		goto err_return;
	}
	down(&hisifd->blank_sem0);

	if (g_debug_ovl_online_composer_timediff & 0x4) {
		hisifb_get_timestamp(&tv3);
		timediff = hisifb_timestamp_diff(&tv2, &tv3);
		if (timediff >= g_debug_ovl_online_composer_time_threshold)
			HISI_FB_ERR("ONLINE_VACTIVE_TIMEDIFF is %u us!\n", timediff);
	}

	if (g_debug_ovl_online_composer == 1) {
		dumpDssOverlay(hisifd, pov_req, false);
	}

	ret = hisifb_layerbuf_lock(hisifd, pov_req, &lock_list);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, hisifb_layerbuf_lock failed! ret=%d\n", hisifd->index, ret);
		goto err_return;
	}

	hisi_dss_handle_cur_ovl_req(hisifd, pov_req);

	ret = hisi_dss_module_init(hisifd);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, hisi_dss_module_init failed! ret = %d\n", hisifd->index, ret);
		goto err_return;
	}

	hisi_mmbuf_info_get_online(hisifd);

	if (enable_cmdlist) {
		hisifd->set_reg = hisi_cmdlist_set_reg;

		hisi_cmdlist_data_get_online(hisifd);

		ret = hisi_cmdlist_get_cmdlist_idxs(pov_req_prev, &cmdlist_pre_idxs, NULL);
		if (ret != 0) {
			HISI_FB_ERR("fb%d, hisi_cmdlist_get_cmdlist_idxs pov_req_prev failed! ret = %d\n", hisifd->index, ret);
			goto err_return;
		}

		ret = hisi_cmdlist_get_cmdlist_idxs(pov_req, &cmdlist_pre_idxs, &cmdlist_idxs);
		if (ret != 0) {
			HISI_FB_ERR("fb%d, hisi_cmdlist_get_cmdlist_idxs pov_req failed! ret = %d\n", hisifd->index, ret);
			goto err_return;
		}

		hisi_cmdlist_add_nop_node(hisifd, cmdlist_pre_idxs, 0, 0);
		hisi_cmdlist_add_nop_node(hisifd, cmdlist_idxs, 0, 0);
	} else {
		hisifd->set_reg = hisifb_set_reg;
		hisi_dss_mctl_mutex_lock(hisifd, pov_req->ovl_idx);
		cmdlist_pre_idxs = ~0;
	}

	hisi_dss_prev_module_set_regs(hisifd, pov_req_prev, cmdlist_pre_idxs, enable_cmdlist, NULL);

	pov_h_block_infos = (dss_overlay_block_t *)(pov_req->ov_block_infos_ptr);
	for (m = 0; m < pov_req->ov_block_nums; m++) {
		pov_h_block = &(pov_h_block_infos[m]);

		ret = hisi_dss_module_init(hisifd);
		if (ret != 0) {
			HISI_FB_ERR("fb%d, hisi_dss_module_init failed! ret = %d\n", hisifd->index, ret);
			goto err_return;
		}

		hisi_dss_aif_handler(hisifd, pov_req, pov_h_block);

		ret = hisi_dss_ovl_base_config(hisifd, pov_req, pov_h_block, NULL, pov_req->ovl_idx, m);
		if (ret != 0) {
			HISI_FB_ERR("fb%d, hisi_dss_ovl_init failed! ret = %d\n", hisifd->index, ret);
			goto err_return;
		}

		/* Go through all layers */
		for (i = 0; i < pov_h_block->layer_nums; i++) {
			layer = &(pov_h_block->layer_infos[i]);
			memset(&clip_rect, 0, sizeof(dss_rect_ltrb_t));
			memset(&aligned_rect, 0, sizeof(dss_rect_ltrb_t));
			rdma_stretch_enable = false;

			ret = hisi_ov_compose_handler(hisifd, pov_req, pov_h_block, layer, NULL, NULL,
				&clip_rect, &aligned_rect, &rdma_stretch_enable, &has_base, true, enable_cmdlist);
			if (ret != 0) {
				HISI_FB_ERR("fb%d, hisi_ov_compose_handler failed! ret = %d\n", hisifd->index, ret);
				goto err_return;
			}
		}

		ret = hisi_dss_mctl_ov_config(hisifd, pov_req, pov_req->ovl_idx, has_base, (m == 0));
		if (ret != 0) {
			HISI_FB_ERR("fb%d, hisi_dss_mctl_config failed! ret = %d\n", hisifd->index, ret);
			goto err_return;
		}

		if (m == 0) {
			if (hisifd->panel_info.dirty_region_updt_support) {
				ret= hisi_dss_dirty_region_dbuf_config(hisifd, pov_req);
				if (ret != 0) {
					HISI_FB_ERR("fb%d, hisi_dss_dirty_region_dbuf_config failed! ret = %d\n", hisifd->index, ret);
					goto err_return;
				}
			}
		}

#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
		ret = hisi_dss_post_scf_config(hisifd, pov_req);
		if (ret != 0) {
			HISI_FB_ERR("fb%d, hisi_dss_post_scf_config failed! ret = %d\n", hisifd->index, ret);
			goto err_return;
		}
#endif

		ret = hisi_dss_ov_module_set_regs(hisifd, pov_req->ovl_idx, enable_cmdlist, 0, 0, (m == 0));
		if (ret != 0) {
			HISI_FB_ERR("fb%d, hisi_dss_module_config failed! ret = %d\n", hisifd->index, ret);
			goto err_return;
		}
	}

	if (enable_cmdlist) {
		g_online_cmdlist_idxs |= cmdlist_idxs;
		//add taskend for share channel
		hisi_cmdlist_add_nop_node(hisifd, cmdlist_idxs, 0, 0);

		//remove ch cmdlist
		hisi_cmdlist_config_stop(hisifd, cmdlist_pre_idxs);

		cmdlist_idxs |= cmdlist_pre_idxs;
		hisi_cmdlist_flush_cache(hisifd, hisifd->ion_client, cmdlist_idxs);
	}

	ret = hisi_crc_enable(hisifd, pov_req);
	if (ret != 0) {
		HISI_FB_ERR("fb%d, hisi_crc_enable failed!\n", hisifd->index);
		goto err_return;
	}

	if (!g_fake_lcd_flag) {
		hisi_dss_unflow_handler(hisifd, pov_req, true);
	}

#ifdef CONFIG_BUF_SYNC_USED
	if (is_mipi_cmd_panel(hisifd)) {
		ret = hisifb_buf_sync_handle(hisifd, pov_req);
		if (ret < 0) {
			HISI_FB_ERR("fb%d, hisifb_buf_sync_handle failed! ret=%d\n", hisifd->index, ret);
			goto err_return;
		}
	}

	pov_req->release_fence = hisifb_buf_sync_create_fence(hisifd, ++hisifd->buf_sync_ctrl.timeline_max);
	if (pov_req->release_fence < 0) {
		HISI_FB_ERR("fb%d, hisi_create_fence failed! pov_req->release_fence = 0x%x\n", hisifd->index, pov_req->release_fence);
		goto err_return;
	}

	spin_lock_irqsave(&hisifd->buf_sync_ctrl.refresh_lock, flags);
	hisifd->buf_sync_ctrl.refresh++;
	spin_unlock_irqrestore(&hisifd->buf_sync_ctrl.refresh_lock, flags);
#endif

	if (enable_cmdlist) {
		hisi_cmdlist_config_start(hisifd, pov_req->ovl_idx, cmdlist_idxs, 0);
	} else {
		hisi_dss_mctl_mutex_unlock(hisifd, pov_req->ovl_idx);
	}

	if (hisifd->panel_info.dirty_region_updt_support) {
		hisi_dss_dirty_region_updt_config(hisifd, pov_req);
	}

	single_frame_update(hisifd);
	hisifb_frame_updated(hisifd);
	hisi_crc_config(hisifd, pov_req);

	if (copy_to_user((struct dss_overlay_t __user *)argp,
			pov_req, sizeof(dss_overlay_t))) {
		ret = -EFAULT;

		if (pov_req->release_fence >= 0)
			put_unused_fd(pov_req->release_fence);

		goto err_return;
	}

	hisifb_deactivate_vsync(hisifd);

	hisifb_layerbuf_flush(hisifd, &lock_list);

	if ((hisifd->index == PRIMARY_PANEL_IDX) && (dss_free_buffer_refcount > 1)) {
		if (!hisifd->fb_mem_free_flag) {
			hisifb_free_fb_buffer(hisifd);
			hisifd->fb_mem_free_flag = true;
		}

		if (g_logo_buffer_base && g_logo_buffer_size) {
			hisifb_free_logo_buffer(hisifd);
			HISI_FB_INFO("dss_free_buffer_refcount = %d !\n", dss_free_buffer_refcount);
		}
	}

	if (g_debug_ovl_online_composer == 2) {
		dumpDssOverlay(hisifd, pov_req, true);
	}

	if (g_debug_ovl_cmdlist && enable_cmdlist)
		hisi_cmdlist_dump_all_node(hisifd, NULL, cmdlist_idxs);

	hisifd->frame_count++;
	dss_free_buffer_refcount++;
	memcpy(&hisifd->ov_req_prev_prev, &hisifd->ov_req_prev, sizeof(dss_overlay_t));
	memcpy(&(hisifd->ov_block_infos_prev_prev), &(hisifd->ov_block_infos_prev),
		hisifd->ov_req_prev.ov_block_nums * sizeof(dss_overlay_block_t));
	hisifd->ov_req_prev_prev.ov_block_infos_ptr = (uint64_t)(&(hisifd->ov_block_infos_prev_prev));

	memcpy(&hisifd->ov_req_prev, pov_req, sizeof(dss_overlay_t));
	memcpy(&(hisifd->ov_block_infos_prev), &(hisifd->ov_block_infos),
		pov_req->ov_block_nums * sizeof(dss_overlay_block_t));
	hisifd->ov_req_prev.ov_block_infos_ptr = (uint64_t)(&(hisifd->ov_block_infos_prev));

	if (g_debug_ovl_online_composer_timediff & 0x2) {
		hisifb_get_timestamp(&tv1);
		timediff = hisifb_timestamp_diff(&tv0, &tv1);
		if (timediff >= g_debug_ovl_online_composer_time_threshold)
			HISI_FB_ERR("ONLINE_TIMEDIFF is %u us!\n", timediff);
	}
	up(&hisifd->blank_sem0);

	return 0;

err_return:
	if (is_mipi_cmd_panel(hisifd)) {
		hisifd->vactive0_start_flag = 1;
	}
	hisifb_layerbuf_lock_exception(hisifd, &lock_list);
	hisifb_deactivate_vsync(hisifd);
	if (!need_skip) {
		up(&hisifd->blank_sem0);
	}
	return ret;
}
