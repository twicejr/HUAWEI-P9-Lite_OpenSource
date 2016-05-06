/*
 *  Hisilicon K3 soc camera v4l2 driver header file
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

#ifndef __MINI_K3_V4L2_CAPTURE_H__
#define __MINI_K3_V4L2_CAPTURE_H__

#include "k3_v4l2_capture_comm.h"
#include "mini_cam_util.h"
#include "../camera.h"
#include "mini_sensor_common.h"

enum {
	all_wrong,
	front_right,
	back_right,
	all_right,
};

typedef struct _mini_keypair_struct {
	int key;
	union {
		u32 uint_value;
		int int_value;
		char ch_value;
		int *pint_value;
		char *pchar_value;
		void *pv_value;
	} value;

} mini_keypair_struct;

typedef struct _mini_pic_fmt_s{
    struct v4l2_format       *preview_fmt;
    struct v4l2_format       *capture_fmt;
    struct v4l2_format       *ipp_fmt;
    camera_setting_view_type preview_view_type;
    camera_setting_view_type capture_view_type;
    camera_setting_view_type ipp_view_type;
}mini_pic_fmt_s;

struct platform_device;
/* camera data struct */
typedef struct _mini_v4l2_ctl_struct {
	struct video_device *video_dev;
	struct platform_device *pdev;
	struct semaphore busy_lock;
	struct semaphore busy_lock_capture;
	int open_count;

	char running[STATE_MAX];
	pid_t pid[STATE_MAX];

	struct v4l2_fract frame_rate;

	/* format info */
	struct v4l2_format fmt[STATE_MAX];

	/* camera frame buffer */
	mini_buffer_arr_t buffer_arr[STATE_MAX];
	mini_data_queue_t data_queue;

	/* camera sensors */
	mini_camera_sensor *sensor;
	int cur_sensor;

	/* dvfs variables */
	int pm_client_id;
	int pm_profile_flag;

} mini_v4l2_ctl_struct;

/* ISP related interface */
int mini_k3_isp_init(struct platform_device *pdev, mini_data_queue_t *data_queue);
int mini_k3_isp_exit(void *);
int mini_k3_isp_set_parameter(struct _mini_keypair_struct *argv, int argc);
int mini_k3_isp_hw_init_regs(mini_camera_sensor *sensor);
int mini_k3_isp_set_camera(mini_camera_sensor *sensor, mini_camera_sensor *close_sensor);
int mini_k3_isp_enum_fmt(struct v4l2_fmtdesc *f, camera_state state);
int mini_k3_isp_stream_on(struct v4l2_pix_format *pixfmt, enum v4l2_buf_type buf_type, camera_state state,mini_buffer_arr_t *buf_arr);
#ifdef READ_BACK_RAW
void mini_k3_isp_update_read_ready(u8 buf_used);
#endif
int mini_k3_isp_stream_off(camera_state state);
int mini_k3_isp_start_process(struct v4l2_pix_format *pixfmt, u8 mode,mini_buffer_arr_t *ipp_buf_arr);
int mini_k3_isp_stop_process(u8 mode);
int mini_k3_isp_try_fmt(struct v4l2_format *fmt, camera_state state, camera_setting_view_type view_type);
int mini_k3_isp_enum_framesizes(struct v4l2_frmsizeenum *fs);
int mini_k3_isp_enum_frameintervals(struct v4l2_frmivalenum *fi);
int mini_k3_isp_try_frameintervals(struct v4l2_frmivalenum *fi);
int mini_k3_isp_set_zoom(char preview_running, u32 zoom);
int mini_k3_isp_set_ae_lock(int mode);
int mini_k3_isp_get_zoom(void);
int mini_k3_isp_get_process_mode(void);
int mini_k3_isp_poweron(void);
void mini_k3_isp_poweroff(void);
int mini_k3_isp_get_common_capability(u32 id, u32 *value);
int mini_k3_isp_get_k3_capability(u32 id, u32 *value);
int mini_k3_isp_get_primary_capability(u32 id, u32 *value);
void mini_k3_isp_check_flash_level(camera_flash_state state);
int mini_k3_isp_get_flash_result(void);

/* All below functions are used for focus */
void mini_k3_isp_auto_focus(int flag);
int mini_k3_isp_set_focus_mode(camera_focus mode);
int mini_k3_isp_get_focus_mode(void);
int mini_k3_isp_set_focus_area(mini_focus_area_s *area);
void mini_k3_isp_get_focus_result(mini_focus_result_s *result);

/* For bracket information settings */
int mini_k3_isp_set_bracket_info(int *ev);

/* All below functions are used for anti_shaking */
int mini_k3_isp_set_anti_shaking(camera_anti_shaking flag);
int mini_k3_isp_get_anti_shaking(void);
int mini_k3_isp_set_anti_shaking_block(int block);
int mini_k3_isp_get_anti_shaking_coordinate(mini_coordinate_s *coordinate);

int mini_k3_isp_set_awb_mode(camera_white_balance awb_mode);
int mini_k3_isp_get_awb_mode(void);
int mini_k3_isp_set_awb_lock(int lock);
int mini_k3_isp_set_iso(camera_iso iso);
int mini_k3_isp_get_iso(void);

int mini_k3_isp_set_ev(int ev);
int mini_k3_isp_get_ev(void);

/* For metering area information settings */
int mini_k3_isp_set_metering_area(mini_metering_area_s *area);
int mini_k3_isp_set_metering_mode(camera_metering mode);
int mini_k3_isp_get_metering_mode(void);

int mini_k3_isp_set_gsensor_stat(mini_axis_triple *xyz);

int mini_k3_isp_set_anti_banding(camera_anti_banding banding);
int mini_k3_isp_get_anti_banding(void);

int mini_k3_isp_set_sharpness(camera_sharpness sharpness);
int mini_k3_isp_get_sharpness(void);

int mini_k3_isp_set_saturation(camera_saturation saturation);
int mini_k3_isp_get_saturation(void);

int mini_k3_isp_set_contrast(camera_contrast contrast);
int mini_k3_isp_get_contrast(void);

int mini_k3_isp_set_scene(camera_scene scene);
int mini_k3_isp_get_scene(void);

int mini_k3_isp_set_brightness(camera_brightness brightness);
int mini_k3_isp_get_brightness(void);

int mini_k3_isp_set_effect(camera_effects effect);
int mini_k3_isp_get_effect(void);

int mini_k3_isp_get_exposure_time(void);
int mini_k3_isp_get_fps(camera_fps fps);
int mini_k3_isp_set_fps(camera_fps fps, u8 value);
int mini_k3_isp_get_actual_iso(void);
int mini_k3_isp_get_awb_gain(int withShift);
int mini_k3_isp_get_focus_code(void);
int mini_k3_isp_get_focus_rect(mini_camera_rect_s *rect);
int mini_k3_isp_get_expo_line(void);
int mini_k3_isp_get_sensor_vts(void);
int mini_k3_isp_get_current_ccm_rgain(void);
int mini_k3_isp_get_current_ccm_bgain(void);

int mini_k3_isp_set_flash_mode(camera_flash flash_mode);
int mini_k3_isp_get_flash_mode(void);

int mini_k3_isp_set_hflip(int flip);
int mini_k3_isp_get_hflip(void);
int mini_k3_isp_set_vflip(int flip);
int mini_k3_isp_get_vflip(void);

int mini_k3_isp_get_focus_distance(void);
int mini_k3_isp_get_current_vts(void);
int mini_k3_isp_get_current_fps(void);
int mini_k3_isp_get_band_threshold(void);
void mini_k3_isp_set_fps_lock(int);

void mini_k3_isp_set_shoot_mode(camera_shoot_mode shoot_mode);

void mini_k3_isp_set_pm_mode(u8 pm_mode);

int mini_k3_isp_get_sensor_aperture(void);
int mini_k3_isp_get_equivalent_focus(void);

void mini_k3_isp_set_video_stabilization(int bStabilization);
void mini_k3_isp_set_yuv_crop_pos(int point);
void mini_k3_isp_get_yuv_crop_rect(mini_crop_rect_s *rect);
void mini_k3_isp_set_process_mode(capture_type debug_type);
void mini_k3_isp_set_zsl_state(camera_zsl zsl_state);
camera_zsl mini_k3_isp_get_zsl_state(void);
void mini_k3_isp_set_zsl_proc(camera_zsl_proc zsl_proc);
camera_zsl_proc mini_k3_isp_get_zsl_proc(void);
int mini_k3_isp_set_zsl_cap_raw(u8 zsl_cap_raw,struct v4l2_pix_format *pixfmt,mini_buffer_arr_t *buf_arr);
u8 mini_k3_isp_get_zsl_proc_img(void);
void mini_k3_isp_set_zsl_proc_img(u8 zsl_proc_img);
void mini_k3_isp_set_zsl_cap_cmd(camera_zsl_cap_cmd zsl_cap_cmd);
void mini_k3_isp_set_zsl_proc_valid(bool zsl_proc_valid);
void mini_k3_isp_set_zsl_cap_valid(bool zsl_cap_valid);

int mini_k3_isp_zsl_try_fmt(mini_pic_fmt_s *pic_fmt,char preview_state);
int mini_k3_isp_zsl_set_private_fmt(struct v4l2_format *fmt_private);
int mini_k3_isp_zsl_refresh_fmt(struct v4l2_format       *preview_fmt,
                                  struct v4l2_format *fmt_try,
                                  struct v4l2_format *fmt_refresh,
                                  camera_state        state_try,
                                  camera_state        state_refresh);

void mini_k3_isp_lock_ddr_freq(void);
void mini_k3_isp_unlock_ddr_freq(void);
void mini_k3_isp_try_cpuidle_vote(void);
void mini_k3_isp_cancel_cpuidle_vote(void);
void mini_k3_isp_set_hw_3a_mode(int mode);


int mini_isp_camera_init(void);
void mini_isp_camera_exit(void);
#endif /*__K3_V4L2_CAPTURE_H__ */

/********************************* END ***********************************************/
