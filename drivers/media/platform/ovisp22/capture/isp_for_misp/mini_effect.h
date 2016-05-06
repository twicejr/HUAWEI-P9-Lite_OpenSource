#ifndef __MINI_EFFECT_H__
#define __MINI_EFFECT_H__


#include "effect_comm.h"
#include "mini_k3_isp_io.h"

/******************************************************************************
	mini_ae_params_s
 ******************************************************************************/
 typedef struct _mini_ae_target_s {
	u8 default_target_y_low;
	u8 default_target_y_high;
} mini_ae_target_s;

typedef struct _mini_percent_s{
	u8 percent_w;
	u8 percent_h;
 } mini_percent_s;

typedef struct _mini_ae_win_s {
	mini_percent_s win_2x2;
	mini_percent_s win_3x3[CAMERA_MERERING_MAX];

	bool roi_enable;

	u8 default_weight[13];
	u8 default_weight_shift;

	u8 touch_weight[13];
	u8 touch_weight_shift;
} mini_ae_win_s;

typedef struct _mini_expo_table {
	u32 expo; /* in fact this is the reciprocal of expo */
	u32 iso;
} mini_expo_table_t;

typedef struct _mini_ae_params_s {
	mini_ae_target_s target_y[5];
	mini_ae_win_s ae_win;
	u8 max_expo_gap;

	u32 iso_max;
	u32 iso_min;

	u16 auto_fps_th[4]; /* low2mid, mid2high,high2mid, mid2low */
    u16 auto_fps_manual_iso_th[4];
      
	u32 fps[4]; /* fps_max, fps_middle, fps_min, fps_min_cap*/

	u8 expo_night; /* for example: 5 mean max expo is 1/5s */
	u8 expo_action; /* for example: 100 mean max expo is 1/100s */

	mini_expo_table_t cap_expo_table[CAMERA_MAX_EXPO_TABLE_SIZE];
	u32 ev_numerator;
	u32 ev_denominator;
} mini_ae_params_s;

/******************************************************************************
	mini_af_param_s
 ******************************************************************************/
typedef struct _mini_focus_area_param {
	u32 percent_w;
	u32 percent_h;
	u32 max_zoom_ratio;
	u32 min_height_ratio;

	/* to be used for multiwindow focus */
	u32 weight[25];
} mini_focus_area_param;

typedef struct _mini_contrast_threshold_s {
	u32 base_low;
	u32 base_high;
	u32 ultralow;
	u32 low;
} mini_contrast_threshold;

typedef struct _mini_judge_result_s {
	u32 error_mindiff;
	u32 error_minsteps;
	u32 low_contrast;
	u32 error_lum;
	u32 stat_th_percent;
} mini_judge_result;

typedef struct _mini_caf_trigger_s {
	u32 cmp_contrast;
	u32 cmp_lum;
	u32 cmp_ae;
	u32 cmp_awb;
	u32 cmp_diff_xyz;

	u32 var_ratio_contrast;
	u32 var_ratio_lum;
	u32 var_diff_xyz;

	u32 min_trigger_lum;
	u32 min_trigger_contrast_diff;
	u32 min_trigger_lum_diff;

	u32 goto_infinite_timeout;

	int stat_cmp_start_frame;
	int stat_cmp_end_frame;
	u32 stat_skip_frame;

	u32 stat_frame;
	u32 stat_frame_low;

	u32 restart_diff_xyz;
} mini_caf_trigger_s;


typedef struct _mini_focus_algo_s {
	bool software_stat;
	mini_contrast_threshold param_th;
	mini_judge_result  param_judge;

	u32 infinity_hold_frames;
	u32 rewind_hold_frames;

	u32 try_dir_range;
	mini_caf_trigger_s  caf_trigger;
	u32 calc_coarse_size;
} mini_focus_algo_s;

typedef struct _mini_af_param_s {
	mini_focus_area_param focus_area;
	mini_focus_algo_s focus_algo;
} mini_af_param_s;

/******************************************************************************
	flash_param
 ******************************************************************************/
typedef struct _mini_awb_gain {
	u16 b_gain;
	u16 gb_gain;
	u16 gr_gain;
	u16 r_gain;
} mini_awb_gain_t;

#if 0
/******************************************************************************
	ev_bracket_ratios
 ******************************************************************************/
typedef struct _ev_bracket_ratios {
	u32 numerator;
	u32 denominator;
} ev_bracket_ratios;
#endif

typedef struct _mini_red_clip_s {
	bool rcc_enable;

	u8 frame_interval;

	u8 detect_range;

	u8 rect_row_num;
	u8 rect_col_num;

	u16 preview_width_high;
	u16 preview_width_low;
	u8 uv_resample_high;
	u8 uv_resample_middle;
	u8 uv_resample_low;

	u8 refbin_low;
	u8 refbin_high;

	u8 v_th_high;
	u8 v_th_low;
} mini_red_clip_s;

/******************************************************************************
	sharpness
 ******************************************************************************/
typedef struct _mini_sharpness_s {
	u32 sharpness_preview;
	u32 sharpness_capture;
} mini_sharpness_cfg_s;


/******************************************************************************
	Denoise
 ******************************************************************************/
typedef struct _mini_denoise_s {
	u8 g_dns_preview[DNS_MAX_STEP];

	u8 g_dns_capture[DNS_MAX_STEP];
	u8 g_dns_capture_1band;

	u8 g_dns_flash[DNS_MAX_STEP];
	u8 g_dns_flash_1band;

	u16 br_dns[DNS_MAX_STEP];
	u8 uv_dns[DNS_MAX_STEP];
} mini_denoise_s;


/******************************************************************************
	mini_flash_param_s
 ******************************************************************************/
typedef struct _mini_aecawb_step {
	u8 stable_range0; /* UNSTABLE2STABLE_RANGE: 0x1c14a */
	u8 stable_range1; /* STABLE2UNSTABLE_RANGE: 0x1c14b */
	u8 fast_step; /* 0x1c14c */
	u8 slow_step; /* 0x1c14e */
	u8 awb_step; /* 0x1c184 */
} mini_aecawb_step_t;

typedef struct _mini_assistant_af_s {
	u32 gainth_high;
	u32 lumth_1ow;
	u32 lumth_high;

	u32 test_max_cnt;
	flash_lum_level flash_level;
} mini_assistant_af_s;

typedef struct _mini_flash_capture_s {
	u32 trigger_gain;

	flash_lum_level preflash_level;
	flash_lum_level capflash_level;
	u8 cap2pre_ratio;

	u32 default_target_y;
	u32 test_max_cnt;
	u32 over_expo_th;
	u32 lowlight_th;
	u32 lowCT_th;
} mini_flash_capture_s;


typedef struct _mini_flash_param_s {
	mini_awb_gain_t gain;
	mini_aecawb_step_t aecawb_step;
	flash_lum_level videoflash_level;
	mini_assistant_af_s assistant_af;
	mini_flash_capture_s flash_capture;
} mini_flash_param_s;


/******************************************************************************
	mini_effect_params
 ******************************************************************************/
typedef struct _mini_effect_params {

	struct mini_isp_reg_t isp_settings[CAMERA_MAX_SETTING_SIZE];

	mini_ae_params_s ae_param;

	mini_af_param_s af_param;

	mini_awb_gain_t mwb_gain[CAMERA_WHITEBALANCE_MAX];

	mini_red_clip_s rcc;

	mini_sharpness_cfg_s sharpness[SHARPNESS_MAX_STEP];

	mini_denoise_s dns;

	u8 uv_saturation[CAMERA_SCENE_MAX];

	mini_flash_param_s flash;
	struct mini_isp_reg_t hdr_movie_isp_settings[CAMERA_MAX_SETTING_SIZE];
} mini_effect_params;

#endif

