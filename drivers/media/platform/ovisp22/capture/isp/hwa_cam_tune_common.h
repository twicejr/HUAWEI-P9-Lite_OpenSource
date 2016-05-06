/*
 *  Hisilicon K3 soc camera ISP driver header file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef HWA_CAM_TUNE_COMMON_H_INCLUDED
#define HWA_CAM_TUNE_COMMON_H_INCLUDED


#include "sensor_common.h"
#include "k3_isp.h"

typedef enum {
	HW_SCOPE_OFF,
	HW_SCOPE_ON
}hwa_hwscope_mode;

typedef struct hwq_hwscope_ctl{
	hwa_hwscope_mode mode;
	int border;
}hwa_hwscope_ctl;

extern hwa_hwscope_ctl hwa_hwscope;
void ispv1_change_max_exposure(camera_sensor *sensor, camera_max_exposrure mode);
void ispv1_change_fps(camera_frame_rate_mode mode);

void hwa_calc_zoom_with_crop(camera_state state, scale_strategy_t scale_strategy, u32 *in_width, u32 *in_height);


#endif /*HWA_CAM_TUNE_COMMON_H_INCLUDED */

/********************************* END ***********************************************/
