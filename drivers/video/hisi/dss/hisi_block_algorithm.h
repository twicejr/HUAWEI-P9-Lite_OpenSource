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

#ifndef __HISI_BLOCK_ALGORITHM_H__
#define __HISI_BLOCK_ALGORITHM_H__

#include "hisi_dss.h"


int get_ov_block_rect(dss_overlay_t *pov_req_h, dss_overlay_block_t *pov_h_block,
	dss_wb_layer_t *wb_layer, int *block_num, dss_rect_t *ov_block_rects[]);
int get_block_layers(dss_overlay_t *pov_req_h, dss_overlay_block_t *pov_h_block,
	dss_rect_t ov_block_rect, dss_overlay_t *pov_req_v_block);
int rect_across_rect(dss_rect_t rect1, dss_rect_t rect2, dss_rect_t *cross_rect);


#endif
