/*
 *  Hisilicon K3 soc camera ISP afae driver header file
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

#ifndef __K3_ISPV1_AFAE_H__
#define __K3_ISPV1_AFAE_H__

#include "k3_ispv1_afae_comm.h"

/* vcm focus position information */
typedef struct _pos_info {
	u32	contrast;
	u32	code;
} pos_info;

typedef struct _af_trip_info {
	int start_pos;
	int end_pos;
	u32 step;
	af_run_direction direction;
	u32 step_cnt;
} af_trip_info;

typedef struct _af_run_param {
	af_trip_info trip;
	pos_info top;
	pos_info histtop;
	u8 hold_cnt;
	u8 af_analysis;
} af_run_param;

/* frame's statistic data */
typedef struct _focus_frame_stat_s {
	u32 contrast;
	u32 lum;
	u32 ae;
	u32 rbratio;
	axis_triple xyz;

	u32 contrast_var;
	u32 lum_var;
	axis_triple xyz_var;

	u32 fps;
} focus_frame_stat_s;

typedef struct _lum_win_info_s {
	/* In fact ISP raw win is divided to 8x6, we select 4 wins which are nearest to current focus center pointer. */
	u32 index[4];
	u32 width;
	u32 height;
} lum_win_info_s;

typedef struct _lum_table_s {
	u32 lum;
	u32 value;
} lum_table_s;

typedef struct _ispv1_afae_ctrl_s {
	focus_area_s af_area;

	bool area_changed;

	lum_win_info_s lum_info;

	camera_focus mode;
	camera_focus pre_mode;

	u32 zoom;

	camera_rect_s cur_rect;

	/* u32 raw_unit_area; */

	int binning;
	int multi_win;

	/* save current focus state. */
	focus_state_e focus_state;

	af_run_stage af_stage;

	/* previous focus action is failed or not. 0:success; 1:failed */
	int focus_failed;

	/* save statistic frames count */
	int focus_stat_frames;

	/* force CAF start flag */
	u16 force_start;

	bool k3focus_running;

	/* stat data is copy from preview yuv, used to calculate contrast_ext_threshold */
	u8 *stat_data;

	/*
	 * save previous single snapshot's or CAF success contrast/gain/expo/lum
	 * when focus succeeded and stop focus,
	 * if swith to continuous video af mode,
	 * we can not switch to continuous video af mode really
	 * this value can be compare with current contrast,
	 * used to judge scene change.
	 * If compare_contrast and current contrast differ too much,
	 * then we can switch to continuous video af mode really
	 */
	focus_frame_stat_s compare_data;

	/*
	 * save several frame's statistic data,
	 * used to judge scene change.
	 */
	focus_frame_stat_s frame_stat[CAF_STAT_FRAME];

	
	int gsensor_interval;

	/*
	 * Define each focus rect's win ID, maybe several win IDs.
	 * If focus rect 0 is include win ID 0, 1, 2,
	 * then table[0][0]/table[0][1]/table[0][2] is 1, other is 0.
	 * After ispv1_exit_focus is called, all table value will be 0.
	 */
	int *map_table;
	pos_info curr;
	u8 af_result; /* equals focus_state */

	struct semaphore	af_run_sem;
	u8 target_high;
	bool point_light; /* added for detecting whether there is point light in focus window */
	camera_bool_e fast_shoot; /* true:enable; false:disable */
} ispv1_afae_ctrl;

/* For auto focus, public API, temporarily we just support one point focus.
 * y36721 todo
 */
int ispv1_auto_focus(int flag);
int ispv1_set_focus_mode(camera_focus focus_mode);
int ispv1_set_focus_area(focus_area_s *area, u32 zoom);
int ispv1_get_focus_result(focus_result_s *result);
int ispv1_set_focus_zoom(u32 zoom);
int ispv1_set_sharpness_zoom(u32 zoom);

/* For auto focus, following are private functions for ispv1*/

/* called by ispv1_tune_ops_init() */
int ispv1_focus_init(void);
/* called by ispv1_tune_ops_init() */
int ispv1_focus_exit(void);

/* Called by start_preview */
int ispv1_focus_prepare(void);
/* Called by stop_preview */
int ispv1_focus_withdraw(void);

/*
 * set metering mode
 */
int ispv1_set_metering_mode(camera_metering mode);
/*
 * set metering area
 */
int ispv1_set_metering_area(metering_area_s *area, u32 zoom);
int ispv1_set_focus_range(camera_focus focus_mode);
int ispv1_get_focus_distance(void);

focus_state_e get_focus_state(void);
FOCUS_STATUS get_focus_result(void);


bool afae_ctrl_is_valid(void);
void save_target_high(void);

int ispv1_set_gsensor_stat(axis_triple *xyz);
int ispv1_set_ae_statwin(pic_attr_t *pic_attr, coordinate_s *center, METERING_STATWIN_MODE statwin_mode, u32 zoom);
void ispv1_wakeup_focus_schedule(bool force_flag);

void ispv1_get_raw_lum_info(aec_data_t *ae_data, u32 stat_unit_area);
u32 ispv1_get_stat_unit_area(void);
void ispv1_set_stat_unit_area(u32 unit_area);
bool ispv1_get_aec_state(void);
int ispv1_set_vcm_dest_code(u32 dest_code);
u32 ispv1_get_af_code(void);
u32 ispv1_get_af_range_min(void);
u32 ispv1_get_af_range_max(void);
void isp1_check_ae_stable(int *ae_stable);
int ispv1_af_set_fast_shoot(camera_bool_e fast_shoot);
u32 ispv1_af_determine_timeout_frame(void);
#endif /*__K3_ISPV1_AFAE_H__ */
/********************************* END ****************************************/
