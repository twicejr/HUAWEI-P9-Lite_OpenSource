/*
* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
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
#include "hisi_block_algorithm.h"
#include "hisi_overlay_utils.h"



#define SCF_INPUT_OV  (16)

#define WDMA_ROT_LINEBUF	(480)
#define AFBCE_LINEBUF	(480)
#define SHARPNESS_LINE_BUF	(1600)

#define MAX_OFFLINE_SCF 4
#define BLOCK_SIZE_INVALID	(0xFFFF)


extern bool isYUV(int format);

int rect_across_rect(dss_rect_t rect1, dss_rect_t rect2, dss_rect_t *cross_rect)
{
	uint32_t center_x = 0;
	uint32_t center_y = 0;

	BUG_ON(cross_rect == NULL);

	memset(cross_rect, 0x0, sizeof(dss_rect_t));

	if (rect1.w == 0 || rect1.h == 0 || rect2.w == 0 || rect2.h == 0)
		return 0;

	center_x = abs(rect2.x + rect2.w - 1 + rect2.x - (rect1.x + rect1.w - 1 + rect1.x));
	center_y = abs(rect2.y + rect2.h - 1 + rect2.y - (rect1.y + rect1.h - 1 + rect1.y));

	if ((center_x < rect2.w + rect1.w) && (center_y < rect2.h + rect1.h)) {
		// rect cross case
		cross_rect->x = MAX(rect1.x, rect2.x);
		cross_rect->y = MAX(rect1.y, rect2.y);
		cross_rect->w = MIN(rect1.x + rect1.w - 1,rect2.x + rect2.w - 1) - cross_rect->x + 1;
		cross_rect->h = MIN(rect1.y + rect1.h - 1,rect2.y + rect2.h - 1) - cross_rect->y + 1;

		return 1;
	}

	return 0;
}

uint32_t calc_dest_block_size(dss_overlay_t *pov_req, dss_overlay_block_t *pov_h_block)
{
	uint32_t i = 0;
	uint32_t block_width = BLOCK_SIZE_INVALID;
	dss_layer_t *layer = NULL;
	dss_wb_layer_t *wb_layer = NULL;

	BUG_ON(pov_req == NULL);
	BUG_ON(pov_h_block == NULL);

	for (i = 0; i < pov_h_block->layer_nums; i++) {
		layer = &(pov_h_block->layer_infos[i]);

		if (layer->need_cap & (CAP_DIM | CAP_BASE))
			continue;

		if ((layer->need_cap & CAP_2D_SHARPNESS) &&
			(layer->src_rect.w > SHARPNESS_LINE_BUF)) {
			block_width = MIN(block_width, SHARPNESS_LINE_BUF);
		}

		if (layer->src_rect.h != layer->dst_rect.h) {
			if (((layer->src_rect.w >= layer->dst_rect.w) && (layer->dst_rect.w > SCF_LINE_BUF)) ||
				((layer->src_rect.w < layer->dst_rect.w) && (layer->src_rect.w > SCF_LINE_BUF))) {
				block_width = MIN(block_width, SCF_LINE_BUF);
			}
		}
	}

	for (i = 0; i < pov_req->wb_layer_nums; i++) {
		wb_layer = &(pov_req->wb_layer_infos[i]);

		if (wb_layer->transform & HISI_FB_TRANSFORM_ROT_90) {
			block_width = MIN(block_width, WDMA_ROT_LINEBUF);
		}

		if (wb_layer->need_cap & CAP_AFBCE) {
			block_width = MIN(block_width, AFBCE_LINEBUF);
		}
	}

	return block_width;
}

int scf_output_suitable(uint32_t x_start, uint32_t x_end, uint32_t pos)
{
	if ((x_start > pos) || (x_end < pos))
		return 0;

	if ((pos - x_start < SCF_MIN_OUTPUT) || (x_end - pos + 1 < SCF_MIN_OUTPUT))
		return 1;

	return 0;
}

int block_fix_scf_constraint(dss_overlay_t *pov_req, dss_overlay_block_t *pov_h_block,
	uint32_t block_size, uint32_t end_pos, uint32_t *fix_size)
{
	uint32_t i = 0;
	uint32_t end = end_pos;
	uint32_t scf_layer_num = 0;

	dss_rect_t scf_dst_rect[MAX_OFFLINE_SCF];
	dss_layer_t *layer = NULL;

	BUG_ON(pov_h_block == NULL);
	BUG_ON(fix_size == NULL);

	*fix_size = block_size;

	if (block_size <= SCF_MIN_OUTPUT) {
		HISI_FB_ERR("block size[%d] is too small!\n", block_size);
		return -1;
	}

	for (i = 0; i < pov_h_block->layer_nums; i++) {
		layer = &(pov_h_block->layer_infos[i]);

		if ((layer->need_cap & (CAP_BASE | CAP_DIM | CAP_PURE_COLOR))
			|| ((layer->src_rect.w == layer->dst_rect.w) && (layer->src_rect.h == layer->dst_rect.h))) {
			continue;
		}

		scf_dst_rect[scf_layer_num].x = layer->dst_rect.x;
		scf_dst_rect[scf_layer_num].y = layer->dst_rect.y;
		scf_dst_rect[scf_layer_num].w = layer->dst_rect.w;
		scf_dst_rect[scf_layer_num].h = layer->dst_rect.h;
		scf_layer_num++;

		if (scf_layer_num > MAX_OFFLINE_SCF) {
			HISI_FB_ERR("scf layer in offline [%d] is more than scf moudle [%d]\n",
				scf_layer_num, MAX_OFFLINE_SCF);
			return -1;
		}
	}

	if (scf_layer_num == 0)
		return 0;

REDO:
	for (i = 0; i < scf_layer_num; i++) {
		if (scf_output_suitable(scf_dst_rect[i].x,
			scf_dst_rect[i].x + scf_dst_rect[i].w - 1, pov_req->wb_ov_rect.x + end)) {
			end = end - SCF_MIN_OUTPUT;
			goto REDO;
		}
	}

	*fix_size = block_size - (end_pos - end);
	return 0;
}

int adjust_layers_cap(dss_overlay_t *pov_req, dss_overlay_block_t *pov_h_block, dss_wb_layer_t *wb_layer)
{
	int i = 0;
	int temp = 0;
	dss_layer_t *layer = NULL;
	bool has_rot = false;

	BUG_ON(pov_h_block == NULL);
	BUG_ON(wb_layer == NULL);

	for (i = 0; i < pov_h_block->layer_nums; i++) {
		layer = &pov_h_block->layer_infos[i];

		if (layer->transform & HISI_FB_TRANSFORM_ROT_90) {
			temp = layer->dst_rect.x;
			layer->dst_rect.x = pov_req->wb_ov_rect.x + (layer->dst_rect.y - pov_req->wb_ov_rect.y);
			layer->dst_rect.y = pov_req->wb_ov_rect.y + temp - pov_req->wb_ov_rect.x;

			temp = layer->dst_rect.w;
			layer->dst_rect.w = layer->dst_rect.h;
			layer->dst_rect.h = temp;

			if (layer->transform == HISI_FB_TRANSFORM_ROT_90) {
				layer->transform = HISI_FB_TRANSFORM_FLIP_V;
			} else if (layer->transform == HISI_FB_TRANSFORM_ROT_270) {
				layer->transform = HISI_FB_TRANSFORM_FLIP_H;
			} else if (layer->transform == (HISI_FB_TRANSFORM_ROT_90 | HISI_FB_TRANSFORM_FLIP_H)) {
				layer->transform = HISI_FB_TRANSFORM_ROT_180;
			} else if (layer->transform == (HISI_FB_TRANSFORM_ROT_90 | HISI_FB_TRANSFORM_FLIP_V)) {
				layer->transform = HISI_FB_TRANSFORM_NOP;
			} else {
				; //do nothing
			}

			has_rot = true;
		}
	}

	//FIXME: 2 wb layer
	if (has_rot) {
		for (i = 0; i < pov_req->wb_layer_nums; i++) {
			wb_layer = &(pov_req->wb_layer_infos[i]);
			temp = wb_layer->src_rect.w;
			wb_layer->src_rect.w = wb_layer->src_rect.h;
			wb_layer->src_rect.h = temp;

			wb_layer->transform = (HISI_FB_TRANSFORM_ROT_90 | HISI_FB_TRANSFORM_FLIP_V);
		}
	}

	return 0;
}

int get_ov_block_rect(dss_overlay_t *pov_req, dss_overlay_block_t *pov_h_block, dss_wb_layer_t *wb_layer,
	int *block_num, dss_rect_t *ov_block_rects[])
{
	int ret = 0;
	uint32_t block_size = 0xFFFF;
	uint32_t current_offset = 0;
	uint32_t last_offset = 0;
	uint32_t fix_scf_span = 0;
	dss_layer_t *layer = NULL;
	uint32_t i = 0;
	int block_has_layer = 0;
	int last_block_has_layer = 1;
	int w = 0;
	int h = 0;

	BUG_ON(pov_req == NULL);
	BUG_ON(pov_h_block == NULL);
	BUG_ON(ov_block_rects == NULL);
	BUG_ON(block_num == NULL);
	BUG_ON(wb_layer == NULL);

	*block_num = 0;

	adjust_layers_cap(pov_req, pov_h_block, wb_layer);
	w = wb_layer->src_rect.w;
	h = wb_layer->src_rect.h;

	block_size = calc_dest_block_size(pov_req, pov_h_block);
	if ((block_size == BLOCK_SIZE_INVALID) || (block_size >= w)) {
		ov_block_rects[*block_num]->x = wb_layer->src_rect.x;
		ov_block_rects[*block_num]->y = wb_layer->src_rect.y;
		ov_block_rects[*block_num]->w = wb_layer->src_rect.w;
		ov_block_rects[*block_num]->h = wb_layer->src_rect.h;

		*block_num = 1;
		return ret;
	}

	current_offset = block_size;
	fix_scf_span = block_size;

	for (current_offset = block_size; last_offset < w; last_offset = current_offset, current_offset += block_size) {
		if (block_fix_scf_constraint(pov_req, pov_h_block, block_size, current_offset, &fix_scf_span) != 0) {
			HISI_FB_ERR("block_fix_scf_constraint err!\n");
			return -3;
		}

		current_offset = current_offset - (block_size - fix_scf_span);
		block_has_layer = 0;

		for (i = 0; i < pov_h_block->layer_nums; i++) {
			layer = &(pov_h_block->layer_infos[i]);

			if (((last_offset + pov_req->wb_ov_rect.x) <= (layer->dst_rect.x + layer->dst_rect.w - 1)) &&
				(layer->dst_rect.x < (current_offset + pov_req->wb_ov_rect.x))) {
				block_has_layer = 1;
				last_block_has_layer = 0;

				if((*block_num) >= HISI_DSS_OFFLINE_MAX_BLOCK)
					return -5;

				ov_block_rects[*block_num]->x = wb_layer->src_rect.x + last_offset;
				ov_block_rects[*block_num]->y = wb_layer->src_rect.y;
				ov_block_rects[*block_num]->w = MIN(current_offset - last_offset, w - last_offset);
				ov_block_rects[*block_num]->h = h;

				(*block_num)++;
				break;
			}
		}

		if (block_has_layer == 0) {
			if ((last_block_has_layer == 0) || (*block_num == 0)) {

				if((*block_num) >= HISI_DSS_OFFLINE_MAX_BLOCK)
					return -6;

				ov_block_rects[*block_num]->x = wb_layer->src_rect.x + last_offset;
				ov_block_rects[*block_num]->y = wb_layer->src_rect.y;
				ov_block_rects[*block_num]->w = MIN(current_offset - last_offset, w - last_offset);
				ov_block_rects[*block_num]->h = h;

				(*block_num)++;
			} else {
				ov_block_rects[*block_num - 1]->w += MIN(current_offset - last_offset, w - last_offset);
			}
			last_block_has_layer = 1;
		}

		if (g_debug_ovl_block_composer) {
			HISI_FB_INFO("ov_block_rects[%d]:[%d:%d:%d:%d],current_offset=%d, fix_scf_span=%d, last_offset=%d, w=%d!\n",
				*block_num, ov_block_rects[*block_num-1]->x, ov_block_rects[*block_num-1]->y, ov_block_rects[*block_num-1]->w,
				ov_block_rects[*block_num-1]->h, current_offset, fix_scf_span, last_offset, w);
		}
	}

	hisifb_adjust_block_rect(*block_num, ov_block_rects, wb_layer);

	return ret;
}

static int create_h_v_block_layer(dss_layer_t *h_layer, dss_layer_t *h_v_layer,
	dss_rect_t dst_cross_rect, dss_rect_t ov_block_rect)
{
	int input_startpos = 0;
	int input_span = 0;
	uint32_t output_startpos = 0; //relative to overlay plane
	uint32_t output_span = 0;
	int h_ratio = 0;
	int acc_hscl = 0;
	int scf_read_start = 0;
	int scf_read_end = 0;
	dss_rect_t rect_transform = {0};
	int first_block = 0;
	int last_block = 0;

	int scf_in_start = 0;
	int scf_in_end = 0;

	BUG_ON(h_layer == NULL);
	BUG_ON(h_v_layer == NULL);

	first_block = (h_layer->dst_rect.x >= ov_block_rect.x) ? 1 : 0;
	last_block = ((ov_block_rect.x + ov_block_rect.w) >= (h_layer->dst_rect.x + h_layer->dst_rect.w)) ? 1 : 0;

	output_startpos = dst_cross_rect.x - h_layer->dst_rect.x;
	output_span = dst_cross_rect.w;
	input_startpos = output_startpos;
	input_span = output_span;

	//handle SCF
	if (h_layer->src_rect.w != h_layer->dst_rect.w) {
		h_ratio = (DSS_WIDTH(h_layer->src_rect.w) * SCF_INC_FACTOR + SCF_INC_FACTOR / 2 - acc_hscl) /
			DSS_WIDTH(h_layer->dst_rect.w);

		scf_in_start = output_startpos * h_ratio / SCF_INC_FACTOR;
		scf_in_end = DSS_WIDTH(output_startpos + dst_cross_rect.w) * h_ratio / SCF_INC_FACTOR;

		if ((first_block == 1) && (last_block == 1)) {
			acc_hscl = 0;
			scf_read_start = 0;
			scf_read_end = DSS_WIDTH(h_layer->src_rect.w);
		} else if (first_block == 1) {
			acc_hscl = 0;
			scf_read_start = 0;
			scf_read_end = scf_in_end + SCF_INPUT_OV;
		} else {
			scf_read_start= scf_in_start - SCF_INPUT_OV;
			if (scf_read_start < 0)
				scf_read_start = 0;
			acc_hscl = output_startpos * h_ratio - scf_read_start * SCF_INC_FACTOR;

			if (last_block == 1) {
				scf_read_end = DSS_WIDTH(h_layer->src_rect.w);
			} else {
				scf_read_end = scf_in_end + SCF_INPUT_OV;
			}
		}

		if (scf_read_end > DSS_WIDTH(h_layer->src_rect.w))
			scf_read_end = DSS_WIDTH(h_layer->src_rect.w);

		input_startpos = scf_read_start;
		input_span = scf_read_end - scf_read_start + 1;
		h_v_layer->block_info.h_ratio = h_ratio;
		h_v_layer->block_info.acc_hscl = acc_hscl;

		if (g_debug_ovl_block_composer) {
			HISI_FB_INFO("first_block=%d, last_block=%d, output_startpos=%d, output_span=%d, "
				"h_ratio=%d, acc_hscl=%d, scf_read_start=%d, scf_read_end=%d, input_startpos=%d, input_span=%d\n",
				first_block, last_block, output_startpos, output_span,
				h_ratio, acc_hscl, scf_read_start, scf_read_end, input_startpos, input_span);
		}
	}

	// handle ROT
	switch (h_v_layer->transform) {
	case HISI_FB_TRANSFORM_NOP:
	case HISI_FB_TRANSFORM_FLIP_V:
		rect_transform.x = h_layer->src_rect.x + input_startpos;
		rect_transform.y = h_layer->src_rect.y;
		rect_transform.w = input_span;
		rect_transform.h = h_layer->src_rect.h;
		break;
	case HISI_FB_TRANSFORM_ROT_180:
	case HISI_FB_TRANSFORM_FLIP_H:
		rect_transform.x = h_layer->src_rect.x + h_layer->src_rect.w - input_startpos - input_span;
		rect_transform.y = h_layer->src_rect.y;
		rect_transform.w = input_span;
		rect_transform.h = h_layer->src_rect.h;
		break;
	default:
		HISI_FB_ERR("unknow h_v_layer->transform=%d!\n", h_v_layer->transform);
		return -EINVAL;
	}

	h_v_layer->src_rect = rect_transform;
	rect_across_rect(h_v_layer->src_rect, h_v_layer->src_rect_mask, &h_v_layer->src_rect_mask);
	h_v_layer->dst_rect = dst_cross_rect;
	return 0;
}

int get_block_layers(dss_overlay_t *pov_req, dss_overlay_block_t *pov_h_block,
	dss_rect_t ov_block_rect, dss_overlay_t *pov_req_h_v)
{
	uint32_t i = 0;
	int ret = 0;
	dss_rect_t dst_cross_rect;
	dss_rect_t wb_ov_rect;
	dss_overlay_block_t *pov_h_v_block = NULL;
	dss_layer_t *h_layer = NULL;
	dss_layer_t *h_v_layer = NULL;
	int h_v_layer_idx = 0;

	BUG_ON(pov_req == NULL);
	BUG_ON(pov_h_block == NULL);
	BUG_ON(pov_req_h_v == NULL);

	if (!ov_block_rect.w || !ov_block_rect.h) {
		HISI_FB_ERR("invaild args, ov_block_rect(%d,%d,%d,%d)!\n",
			ov_block_rect.x, ov_block_rect.y, ov_block_rect.w, ov_block_rect.y);
		return -1;
	}

	// init pov_req_v_block
	pov_h_v_block = (dss_overlay_block_t *)pov_req_h_v->ov_block_infos_ptr;
	memcpy(pov_req_h_v, pov_req, sizeof(dss_overlay_t));
	pov_req_h_v->ov_block_infos_ptr = (uint64_t)(pov_h_v_block);

	if (calc_dest_block_size(pov_req, pov_h_block) == BLOCK_SIZE_INVALID) {
		pov_req_h_v->ov_block_nums = 1;
		memcpy(pov_h_v_block, pov_h_block, sizeof(dss_overlay_block_t));
		return 0;
	}

	pov_h_v_block->layer_nums = 0;
	h_v_layer_idx = 0;
	memcpy(&pov_h_v_block->ov_block_rect, &pov_h_block->ov_block_rect, sizeof(dss_rect_t));
	wb_ov_rect.x = pov_req->wb_ov_rect.x + ov_block_rect.x;
	wb_ov_rect.y = pov_req->wb_ov_rect.y;
	wb_ov_rect.w = ov_block_rect.w;
	wb_ov_rect.h = ov_block_rect.h;

	for (i = 0; i < pov_h_block->layer_nums; i++) {
		h_layer = &(pov_h_block->layer_infos[i]);

		ret = rect_across_rect(h_layer->dst_rect, wb_ov_rect, &dst_cross_rect);
		if (ret == 0)
			continue;

		h_v_layer = &(pov_h_v_block->layer_infos[h_v_layer_idx]);
		memcpy(h_v_layer, h_layer, sizeof(dss_layer_t));
		h_v_layer->layer_idx = h_v_layer_idx;

		ret = create_h_v_block_layer(h_layer, h_v_layer, dst_cross_rect, wb_ov_rect);
		if ((ret != 0) || g_debug_ovl_block_composer) {
			HISI_FB_INFO("h_layer[%d](transform[%d], wb_ov_rect[%d,%d,%d,%d], src_rect[%d,%d,%d,%d], dst_rect[%d,%d,%d,%d]), "
				"h_v_layer[%d](transform[%d], src_rect[%d,%d,%d,%d], dst_rect[%d,%d,%d,%d], dst_cross_rect[%d,%d,%d,%d])\n",
				i, h_layer->transform, wb_ov_rect.x, wb_ov_rect.y, wb_ov_rect.w, wb_ov_rect.h,
				h_layer->src_rect.x, h_layer->src_rect.y, h_layer->src_rect.w, h_layer->src_rect.h,
				h_layer->dst_rect.x, h_layer->dst_rect.y, h_layer->dst_rect.w, h_layer->dst_rect.h,
				h_v_layer_idx, h_v_layer->transform,
				h_v_layer->src_rect.x, h_v_layer->src_rect.y, h_v_layer->src_rect.w, h_v_layer->src_rect.h,
				h_v_layer->dst_rect.x, h_v_layer->dst_rect.y, h_v_layer->dst_rect.w, h_v_layer->dst_rect.h,
				dst_cross_rect.x, dst_cross_rect.y, dst_cross_rect.w, dst_cross_rect.h);
		}

		if (ret != 0) {
			HISI_FB_ERR("create_h_v_block_layer failed, h_layer[%d], h_v_layer[%d]!\n",
				i, h_v_layer_idx);
			break;
		}

		h_v_layer_idx++;
		pov_h_v_block->layer_nums = h_v_layer_idx;
	}

	return ret;
}
