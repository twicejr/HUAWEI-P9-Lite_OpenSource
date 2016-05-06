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

#ifndef __MINI_K3_ISPV1_AFAE_H__
#define __MINI_K3_ISPV1_AFAE_H__

#include "k3_ispv1_afae_comm.h"
/* vcm focus position information */

typedef enum {
	FOCUS_STATE_STOPPED = 0,
	FOCUS_STATE_CAF_PREPARING,
	FOCUS_STATE_CAF_DETECTING,
	FOCUS_STATE_CAF_RUNNING,
	FOCUS_STATE_AF_PREPARING,
	FOCUS_STATE_AF_RUNNING,
	FOCUS_STATE_S1_ABORT,
	FOCUS_STATE_MAX,
} focus_state_e;

typedef struct _mini_pos_info {
	u32	contrast;
	u32	code;
} mini_pos_info;

typedef struct _mini_af_trip_info {
	int start_pos;
	int end_pos;
	u32 step;
	af_run_direction direction;
	u32 step_cnt;
} mini_af_trip_info;

typedef struct _mini_af_run_param {
	mini_af_trip_info trip;
	mini_pos_info top;
	mini_pos_info histtop;
	u8 hold_cnt;
	u8 af_analysis;
} mini_af_run_param;

/* frame's statistic data */
typedef struct _mini_focus_frame_stat_s {
	u32 contrast;
	u32 lum;
	u32 ae;
	u32 rbratio;
	mini_axis_triple xyz;

	u32 contrast_var;
	u32 lum_var;
	mini_axis_triple xyz_var;

	u32 fps;
} mini_focus_frame_stat_s;

typedef struct _mini_um_win_info_s {
	/* In fact ISP raw win is divided to 8x6, we select 4 wins which are nearest to current focus center pointer. */
	u32 index[4];
	u32 width;
	u32 height;
} mini_lum_win_info_s;

typedef struct _mini_lum_table_s {
	u32 lum;
	u32 value;
} mini_lum_table_s;

typedef struct _mini_ispv1_afae_ctrl_s {
	mini_focus_area_s af_area;

	bool area_changed;

	mini_lum_win_info_s lum_info;

	camera_focus mode;
	camera_focus pre_mode;

	u32 zoom;

	mini_camera_rect_s cur_rect;

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
	mini_focus_frame_stat_s compare_data;

	/*
	 * save several frame's statistic data,
	 * used to judge scene change.
	 */
	mini_focus_frame_stat_s frame_stat[CAF_STAT_FRAME];

	
	int gsensor_interval;

	/*
	 * Define each focus rect's win ID, maybe several win IDs.
	 * If focus rect 0 is include win ID 0, 1, 2,
	 * then table[0][0]/table[0][1]/table[0][2] is 1, other is 0.
	 * After ispv1_exit_focus is called, all table value will be 0.
	 */
	int *map_table;
	mini_pos_info curr;
	u8 af_result; /* equals focus_state */

	struct semaphore	af_run_sem;
	u8 target_high;
} mini_ispv1_afae_ctrl;
#define ISP_MAX_FOCUS_WIN		25
typedef struct _mini_focus_win_info_s{
	u32 left;
	u32 top;
	u32 width;
	u32 height;

	u32 width1;
	u32 height1;

	u32 weight[ISP_MAX_FOCUS_WIN];
} mini_focus_win_info_s;


/* For auto focus, public API, temporarily we just support one point focus.
 * y36721 todo
 */
int mini_ispv1_auto_focus(int flag);
int mini_ispv1_set_focus_mode(camera_focus focus_mode);
int mini_ispv1_set_focus_area(mini_focus_area_s *area, u32 zoom);
int mini_ispv1_get_focus_result(mini_focus_result_s *result);
int mini_ispv1_set_focus_zoom(u32 zoom);
int mini_ispv1_set_sharpness_zoom(u32 zoom);

/* For auto focus, following are private functions for ispv1*/

/* called by mini_ispv1_tune_ops_init() */
int mini_ispv1_focus_init(void);
/* called by mini_ispv1_tune_ops_init() */
int mini_ispv1_focus_exit(void);

/* Called by start_preview */
int mini_ispv1_focus_prepare(void);
/* Called by stop_preview */
int mini_ispv1_focus_withdraw(void);

/*
 * set metering mode
 */
int mini_ispv1_set_metering_mode(camera_metering mode);
/*
 * set metering area
 */
int mini_ispv1_set_metering_area(mini_metering_area_s *area, u32 zoom);
int mini_ispv1_set_focus_range(camera_focus focus_mode);
int mini_ispv1_get_focus_distance(void);

focus_state_e mini_get_focus_state(void);
FOCUS_STATUS mini_get_focus_result(void);

bool mini_afae_ctrl_is_valid(void);
void mini_save_target_high(void);

int mini_ispv1_set_gsensor_stat(mini_axis_triple *xyz);
int mini_ispv1_set_ae_statwin(mini_pic_attr_t *pic_attr, mini_coordinate_s *center, METERING_STATWIN_MODE statwin_mode, u32 zoom);
void mini_ispv1_wakeup_focus_schedule(bool force_flag);

void mini_ispv1_get_raw_lum_info(mini_aec_data_t *ae_data, u32 stat_unit_area);
u32 mini_ispv1_get_stat_unit_area(void);
void mini_ispv1_set_stat_unit_area(u32 unit_area);
bool mini_ispv1_get_aec_state(void);
int mini_ispv1_set_vcm_dest_code(u32 dest_code);
int mini_ispv1_face_yuvrect_to_rawrect(void* face_area_s);

#endif /*__K3_ISPV1_AFAE_H__ */
/********************************* END ****************************************/
