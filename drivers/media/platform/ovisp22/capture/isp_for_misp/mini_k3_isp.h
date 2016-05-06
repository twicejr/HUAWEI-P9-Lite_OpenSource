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

#ifndef __MINI_K3_ISP_H__
#define __MINI_K3_ISP_H__

#include "k3_isp_comm.h"

#include "mini_sensor_common.h"
#include "mini_cam_util.h"

typedef enum {
	FLASH_IDLE = 0,
	FLASH_WAIT,
	NO_FLASH,
	TAF_FLASH,
	PRE_FLASH,
	MAIN_FLASH,
} mini_isp_flash_period_t;

typedef struct _mini_pic_attr {
	u32 sensor_width;	/* sensor output width */
	u32 sensor_height;
	u32 in_width;		/* isp input width */
	u32 in_height;
	u32 startx;
	u32 starty;
	u32 crop_x;
	u32 crop_y;
	u32 crop_width;
	u32 crop_height;
	u32 out_width;
	u32 out_height;
	u32 out_stride;

	u32 raw_scale_down;
	u32 yuv_dcw;
	u32 yuv_in_width;
	u32 yuv_in_height;
	u32 yuv_down_scale_nscale;
	u32 yuv_up_scale_nscale;

	u32 in_fmt;
	u32 out_fmt;
} mini_pic_attr_t;

typedef struct _mini_uv_offset {
	u32 uoffset;
	u32 voffset;
} mini_uv_offset;

typedef struct _mini_zsl_ctrl {
    camera_zsl          zsl_state;

    bool                zsl_online_enable;/* if support zsl online */
    camera_zsl_proc     zsl_proc_mode;
    camera_zsl_cap_cmd  zsl_cap_cmd;
    u8                  zsl_cap_int;
    u8                  zsl_proc_type;
    u8                  zsl_back_idx;
    u8                  zsl_proc_idx;

    /* cap raw and proc img retry */
    bool                zsl_proc_valid;
    bool                zsl_cap_valid;

    /* when stop_cap_with_preview,get captured buf cnt and buf idx */
    u8                  history_buf_cnt;
    u8                  history_buf_idx;

	u8                  focused_frame_cnt; /* continuous focused frame count */
}mini_zsl_ctrl_t;


typedef struct _mini_common_st {
	u32 frame_index;
	u16 frame_rate;
	u16 scene_mode;
	u8 scene_change_flg;
	u8 digital_zoom;
	u8 filcker_detect_reslut;
	u8 module_id;
	u16 frame_type;
}mini_common_st;

typedef struct _mini_ae_st {
	s16 result_BV;
	u32 expo_time;
	u16 expo_line;
	u16 iso;
	u16 gain;
	u16 avg_raw_lum;
	u16 target;
	s16 manual_ev_comp;
	u8 mode;
	u8 flash_turnon_flag;
	u8 converge_state;
}mini_ae_st;

typedef struct _mini_awb_st {
	u8 converge_state;
	u8 mode;
	u16 r_gain;
	u16 g_gain;
	u16 b_gain;
	int light_source;
}mini_awb_st;

typedef struct _mini_af_st {
	u8 converge_state;
	u8 assist_flash_turnon_flag;
	u8 code;
	u8 mode;
	s16 final_peak_step;
	u16 bar_level;
}mini_af_st;

typedef struct _mini_fe_st {
	u8 preflash1_state;
	u8 ae_image_cal_ready;
	u8 preflash1_cal_ready;
	u8 preflash2_cal_ready;
	u32 mainflash_led_enerage;
}mini_fe_st;

typedef struct _meta_data_st {
	mini_common_st common_info;
	mini_ae_st ae_info;
	mini_awb_st awb_info;
	mini_af_st af_info;
	mini_fe_st fe_info;
	u8 reserved[32];
	u8 sw_debug[256];
	u8 debug_info[1692];
}meta_data_st;

typedef struct _mini_isp_meta_data {
	void (*exit)(void **);
	void (*parse)(void *, void *);

	meta_data_st data_buff;
	meta_data_st data;
}mini_isp_meta_data;


typedef struct _mini_k3_isp_data {
	bool powered;
	bool cold_boot;
#if 0 //#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
	struct pm_qos_request_list qos_request;
	struct pm_qos_request_list qos_request_gpu;
	struct pm_qos_request_list qos_request_cpu;
#endif
	struct pm_qos_request_list qos_req_ddr_freq;
	struct pm_qos_request_list qos_req_cpu_int_latency;

	/* picture attribute varibles */
	mini_pic_attr_t pic_attr[STATE_MAX];
	int bracket_ev[MAX_BRACKET_COUNT];	/* [-4, 4] step is 0.5 */
	u32 *support_pixfmt;
	u32 pixfmt_count;
	u32 zoom;
	int video_stab;
	struct v4l2_fract frame_rate;

	mini_camera_sensor *sensor;

	camera_focus focus;

	camera_anti_shaking	anti_shaking_enable;
	camera_metering	        metering;
	mini_metering_area_s         ae_area;
	camera_anti_banding	anti_banding;
	camera_white_balance	awb_mode;
	awb_mode_t                 awb_lock;
	aecagc_mode_t             ae_lock;
	camera_iso		iso;
	camera_sharpness	sharpness;
	camera_saturation	saturation;
	camera_contrast		contrast;
	camera_brightness	brightness;
	camera_effects		effect;

	camera_flash		flash_mode;
	camera_flash_flow	flash_flow;
	camera_flash_state	flash_state;
	bool 				flash_on;
	bool				assistant_af_flash;
	bool			    af_need_flash;
	camera_shoot_mode	shoot_mode;

	camera_scene		scene;
	int					ev;
	camera_frame_rate_mode fps_mode;
	mini_camera_frame_buf		*current_frame;
	int			next_crop_pos;
	int			cur_crop_pos;
	struct semaphore frame_sem;

	mini_zsl_ctrl_t          zsl_ctrl;

	bool        		hw_3a_switch;
    int                 idi;

	mini_isp_meta_data	*meta_data;  //add by zhoutian for mini-ISP meta data
	bool				meta_data_vc_on;
	bool				is_using_mini_isp;
	mini_isp_flash_period_t	mini_isp_flash_period;
	struct mutex		mini_isp_flash_period_lock;
	mini_isp_3a_state	s1_3a_state;
	u32					capture_iso;
	u32					capture_expo_time;
} mini_k3_isp_data;

typedef struct _mini_k3_last_state {
	camera_saturation	saturation;
	camera_contrast	contrast;
	camera_brightness	brightness;
	camera_effects	effect;
} mini_k3_last_state;

typedef struct _mini_v4l2_callback {
	int (*preview_start_callback) (void);
	int (*preview_done_callback) (void);

	int (*capture_start_callback) (void);
	int (*capture_done_callback) (void);
} mini_frame_callback_t;

struct mini_i2c_t;
typedef struct _mini_isp_hw_controller {
	int (*isp_hw_init)(struct platform_device *pdev, mini_data_queue_t *data_queue);
	void (*isp_hw_deinit) (void);
	void (*isp_hw_init_regs) (data_interface_t data_interface);
	void (*isp_hw_deinit_regs) (void);

	void (*set_i2c) (struct mini_i2c_t *i2c);
#if 0
	void (*isp_set_process_mode) (u32 w, u32 h);
#else
    void (*isp_set_process_mode) (capture_type process_mode);
#endif
	isp_process_mode_t(*isp_get_process_mode) (void);
	int (*isp_check_config) (struct v4l2_pix_format *pixfmt, camera_state state);
	int (*isp_set_zoom) (u32 ratio, zoom_quality_t quality);
	void (*isp_set_ae_lock)(aecagc_mode_t mode);
	int (*isp_get_fps) (mini_camera_sensor *sensor, camera_fps fps);
	int (*isp_set_fps) (mini_camera_sensor *sensor, camera_fps fps, u8 value);

	int (*start_preview) (mini_pic_attr_t *pic_attr, mini_camera_sensor *sensor, bool cold_boot, camera_scene scene);
	int (*start_capture) (mini_pic_attr_t *pic_attr, mini_camera_sensor *sensor,  int *ev, bool flash_on, camera_scene scene,	mini_buffer_arr_t *buf_arr);
	#ifdef READ_BACK_RAW
	void (*update_read_ready) (u8 buf_used);
	#endif
	int (*start_process) (mini_pic_attr_t *pic_attr, u8 mode, mini_buffer_arr_t *ipp_buf_arr);
	int (*stop_preview) (void);
	int (*stop_capture) (void);
	int (*stop_process) (u8 mode);
	void (*refresh_support_fmt) (u32 **pixfmt, u32 *cnt);
	void (*isp_fill_fmt_info) (struct v4l2_pix_format *f);
	int (*capture_update_addr) (u32 phyaddr);
	int (*preview_update_addr) (u32 phyaddr);

	int (*isp_poweron) (void);
	void (*isp_poweroff) (void);

	int (*isp_tune_ops_init) (mini_k3_isp_data *ispdata);
	void (*isp_tune_ops_prepare) (camera_state state);
	void (*isp_tune_ops_withdraw) (camera_state state);
	void (*isp_tune_ops_exit) (void);

	mini_isp_tune_ops *isp_tune_ops;

	void (*isp_set_auto_flash) (int status, camera_flash flash_mode);
	bool (*isp_is_need_flash) (mini_camera_sensor *sensor);

	void (*isp_set_aecagc_mode) (aecagc_mode_t mode);
	/*h00206029_20120221*/
	void (*isp_set_awb_mode) (awb_mode_t mode);

	void (*isp_check_flash_prepare) (void);

	int (*cold_boot_set)(mini_camera_sensor *sensor);

	int (*isp_get_current_vts)(mini_camera_sensor *sensor);
	int (*isp_get_current_fps)(mini_camera_sensor *sensor);
	int (*isp_get_band_threshold)(mini_camera_sensor *sensor, camera_anti_banding banding);
	void (*isp_set_video_stabilization)(int bStabilization);
	void (*isp_set_yuv_crop_pos)(int point);
	void (*isp_get_yuv_crop_rect)(mini_crop_rect_s *rect);
} mini_isp_hw_controller;

#ifdef ISP_DEBUG_ZSL
extern u8 mini_zsl_online_enable;
#endif

/* get isp hardware control data struct */
mini_isp_hw_controller *mini_get_isp_hw_controller(void);

int mini_k3_ispio_init(struct platform_device *pdev);
void mini_k3_ispio_deinit(void);

/* Used to switch between yuv rect and raw rect */
int mini_k3_isp_yuvrect_to_rawrect(mini_camera_rect_s *yuv, mini_camera_rect_s *raw);
int mini_k3_isp_yuvrect_to_rawrect2(mini_camera_rect_s *yuv, mini_camera_rect_s *raw);
int mini_k3_isp_rawrect_to_yuvrect(mini_camera_rect_s *yuv, mini_camera_rect_s *raw);
int mini_k3_isp_antishaking_rect_stat2out(mini_camera_rect_s *out, mini_camera_rect_s *stat);
int mini_k3_isp_antishaking_rect_out2stat(mini_camera_rect_s *out, mini_camera_rect_s *stat);

#endif /*__K3_ISP_H__ */

/********************** END ***********************/
