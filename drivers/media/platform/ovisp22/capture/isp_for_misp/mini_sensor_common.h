/*
 *  Hisilicon K3 soc camera sensor header file
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

#ifndef MINI_CAMERA_SENSOR_H_INCLUDED
#define MINI_CAMERA_SENSOR_H_INCLUDED

#include "sensor_common_comm.h"

#include "../camera.h"
#include "mini_effect.h"
#include "mini_hdr_movie.h"
#include "mini_hw_soft_3a.h"
//#define ISP_ZSL_BURST_OPT  /*to be debug */
typedef enum {
	S1_3A_LOCKED = 0,
	S1_3A_UNLOCKED_BY_TAF,
	S1_3A_UNLOCKED_BY_PRE_WITH_AF,
	S1_3A_UNLOCKED_BY_PRE_WITHOUT_AF
} mini_isp_3a_state;


typedef struct {
	u32 id;
	u32 value;
} mini_camera_capability;


typedef struct _mini_sensor_reg_t {
	u32 subaddr;
	u32 value;
	u8 mask;
	u16 size;
} mini_sensor_reg_t;

typedef struct _mini_sensor_setting_t {
	mini_sensor_reg_t *setting;
	u32 seq_size;
} mini_sensor_setting_t;

typedef struct _mini_sensor_power_t {
	electrical_valid_t pd_valid;
	electrical_valid_t reset_valid;
	electrical_valid_t vcmpd_valid;
} mini_sensor_power_t;

struct mini_i2c_t {
	i2c_index_t index;
	i2c_speed_t speed;
	u32 addr;
	i2c_length addr_bits;
	i2c_length val_bits;
};

/* For sensor framesize definition */
typedef struct _mini_framesize_s {
	u32 left;
	u32 top;
	u32 width;
	u32 height;
	u32 hts;		/* horizontal total size */
	u32 vts;		/* vertical total size */
	u32 fps;
	u32 fps_es;
	u32 banding_step_50hz;
	u32 banding_step_60hz;
	u32 capture_ratio;
	camera_setting_view_type view_type;
	camera_resolution_type resolution_type;
	bool summary;
	bool zsl_only;
	mini_sensor_setting_t sensor_setting;	/* sensor setting for cmdset */
	u8 mini_isp_index;
} mini_framesize_s;

/* For ISP coordinate structure */
typedef struct _mini_coordinate_s {
	u32 x;
	u32 y;
} mini_coordinate_s;

/* For camera rect definition */
typedef struct _mini_camera_rect_s {
	u32 left;
	u32 top;
	u32 width;
	u32 height;

	/*
	 * used for focus and metering areas; anti-shaking can ignore it.
	 * focus can define windows weight.
	 * every rect can have its own focus weight.
	 */
	u32 weight;
} mini_camera_rect_s;
typedef struct mini_crop_rect_s {
	u32 ori_width;
	u32 ori_height;
	u32 crop_width;
	u32 crop_height;
} mini_crop_rect_s;


typedef struct _mini_axis_triple {
	int x;
	int y;
	int z;
	struct timeval time;
} mini_axis_triple;


/*default should be designed as center area focus*/
typedef struct _mini_focus_area_s {
	u32 focus_rect_num;
	mini_camera_rect_s rect[MAX_FOCUS_RECT];
} mini_focus_area_s;

/* focus result structure */
typedef struct _mini_focus_result_s {
	FOCUS_STATUS status;
	FOCUS_STATUS each_status[MAX_FOCUS_RECT];
} mini_focus_result_s;

/* metering area definition */
typedef struct _mini_metering_area_s {
	u32 metering_rect_num;
	mini_camera_rect_s rect[MAX_METERING_RECT];
} mini_metering_area_s;

/* AF vcm information definition */
typedef struct _mini_vcm_info_s {
	VCM_TYPE vcm_type;
	u32 vcm_bits;		/* 16bits or 8bits */
	u32 vcm_id;		/* for example, "DW9714" is 0x18 */
	u32 moveLensAddr[2];

	u32 offsetInit;		/* should be calibrated by focus at infinite distance */
	u32 fullRange;		/* should be calibrated by focus at an macro distance */

	u32 infiniteDistance;	/* should be calibrated by focus at infinite distance */

	u32 normalDistanceEnd;
	u32 normalStep;
	u32 normalStrideRatio; /* 0x10 is 1:1, 0x18 is 1:1.5, 0x20 is 1:2 */

	u32 videoDistanceEnd;
	u32 videoStep;
	u32 videoStrideRatio;

	u32 strideOffset;

	u32 coarseStep;
	u32 fineStep; /* half of coarseStep */

	u32 motorResTime;	/* response time, in unit of ms */
	u32 motorDelayTime;	/* delay time of each step in stride divide case */
	u32 strideDivideOffset;
	u32 startCurrentOffset;

	FOCUS_RANGE moveRange;/*0:Auto; 1:Infinite; 2:Macro*/

	
	void (*get_vcm_otp) (u16 *vcm_start, u16 *vcm_end);
} mini_vcm_info_s;

struct _mini_camera_sensor;

/* camera tune operations function definitions. */
typedef struct {
	/*
	 * isp_auto_focus:
	 * param: int flag=1 start, flag=0 cancel or stop
	 */
	int (*isp_auto_focus) (int flag);
	int (*isp_set_focus_mode) (camera_focus focus_mode);
	/*
	 * param: mini_focus_area_s *area, rects definition;
	 */
	int (*isp_set_focus_area) (mini_focus_area_s *area, u32 zoom);
	int (*isp_get_focus_result) (mini_focus_result_s *result);
	int (*isp_set_focus_zoom) (u32 zoom);
	int (*isp_set_sharpness_zoom) (u32 zoom);

	/* For anti-shaking */
	int (*isp_set_anti_shaking) (camera_anti_shaking flag);
	int (*isp_set_anti_shaking_block) (int blocksize);
	int (*isp_get_anti_shaking_coordinate) (mini_coordinate_s *coordinate);

	/* For other functions */
	int (*set_iso) (camera_iso iso);
	int (*set_ev) (int ev);
	int (*set_metering_mode) (camera_metering mode);
	int (*set_metering_area) (mini_metering_area_s *area, u32 zoom);

	int (*set_gsensor_stat) (mini_axis_triple *xyz);

	int (*set_bracket_info) (int *ev);

	int (*set_anti_banding) (camera_anti_banding banding);
	int (*get_anti_banding) (void);
	int (*set_awb) (camera_white_balance awb_mode);

	int (*set_sharpness) (camera_sharpness sharpness);
	int (*set_saturation) (camera_saturation saturation);
	int (*set_contrast) (camera_contrast contrast);
	int (*set_scene) (camera_scene scene);
	int (*set_brightness) (camera_brightness brightness);
	int (*set_effect) (camera_effects effect);
	int (*isp_get_actual_iso) (void);
	int (*isp_get_exposure_time) (void);

	int (*isp_get_focus_distance) (void);
	void (*isp_set_fps_lock) (int);
	u32 (*isp_get_awb_gain)(int withShift);
	u32 (*isp_get_focus_code)(void);
	u32 (*isp_get_focus_rect)(mini_camera_rect_s *rect);
	u32 (*isp_get_expo_line)(void);
	u32 (*isp_get_sensor_vts)(void);

	u32 (*isp_get_current_ccm_rgain)(void);
	u32 (*isp_get_current_ccm_bgain)(void);

} mini_isp_tune_ops;

typedef struct _mini_camera_flashlight {
	int (*init) (void);
	void (*exit) (void);
	int (*reset) (void);
	int (*turn_on) (work_mode mode, flash_lum_level lum);
	int (*test) (void);
	int (*turn_off) (void);

	flash_type type;
} mini_camera_flashlight;

typedef struct _mini_image_setting {
	u8 *lensc_param;
	u16 *ccm_param;
	u8 *awb_param;
} mini_image_setting_t;


typedef struct _mini_ccm_gain {
	u16 b_gain;
	u16 g_gain;
	u16 r_gain;
} mini_ccm_gain_t;

typedef struct _mini_camera_sensor {
	/* init and exit function */
	int (*init) (void);
	void (*exit) (void);

	/* shut down sensor */
	void (*shut_down) (void);

	/* reset camera */
	int (*reset) (camera_power_state power_state);

	/* set camera power */
	int (*power) (camera_power_state power);

	int (*check_sensor) (void);
	int (*init_reg) (void);
	int (*init_isp_reg)(void);
	int (*stream_on) (camera_state state);
	int (*stream_off)(camera_state state);

	/* get camera clock */
	/* unsigned long (*get_camera_clock)(void); */

	/* set/get camera flash mode */
	int (*set_flash) (camera_flash flash);
	int (*get_flash) (void);

	/* set/get camera scene */
	int (*set_scene) (camera_scene scene);
	int (*get_scene) (void);

	/* set/get camera horizontal/vertical image flip */
	int (*set_hflip) (int);
	int (*get_hflip) (void);
	int (*set_vflip) (int);
	int (*get_vflip) (void);
	int (*update_flip) (u16 width, u16 height);
	u8 hflip;
	u8 vflip;
	u8 old_flip;

	int (*get_format) (struct v4l2_fmtdesc *fmt);

	/* enum/try/set the resolutions */
	int (*enum_framesizes) (struct v4l2_frmsizeenum *framesizes);
	int (*try_framesizes) (struct v4l2_frmsizeenum *framesizes);
	int (*set_framesizes) (camera_state state,
			       struct v4l2_frmsize_discrete *fs, int flag, camera_setting_view_type view_type,bool zsl_preview);
	int (*get_framesizes) (camera_state state,
			       struct v4l2_frmsize_discrete *fs);

	/* enum/try/set/get frame intervals */
	int (*enum_frame_intervals) (struct v4l2_frmivalenum *fi);
	int (*try_frame_intervals) (struct v4l2_frmivalenum *fi);
	int (*set_frame_intervals) (struct v4l2_fract *f);
	int (*get_frame_intervals) (struct v4l2_fract *f);

	/* get capabilities of sensor */
	int (*get_capability) (u32 id, u32 *value);

	int skip_frames;	/* y36721 use it 2012-04-10 for SONY sensor. */

	/* interface_type : MIPI or DVP */
	data_interface_t interface_type;
	csi_lane_t mipi_lane_count;
	csi_index_t mipi_index;
	mini_sensor_power_t power_conf;
	sensor_index_t sensor_index;
	struct mini_i2c_t i2c_config;

	camera_sensor_type sensor_type;
	camera_sensor_rgb_type sensor_rgb_type;

	u32 aec_addr[3];
	u32 agc_addr[2];	/*high and low byte */

	/*in AP write AE mode, delay time(unit us) between report expo&gain and ISP download sensor settings.*/
	u32 ap_writeAE_delay;

	/*if 1, then isp is integrated in sensor */
	isp_location_t isp_location;

	mini_isp_tune_ops *sensor_tune_ops;

	u32 (*sensor_gain_to_iso) (int gain);
	u32 (*sensor_iso_to_gain) (int iso);
	void (*get_ccm_pregain) (camera_state state, u32 frame_index, u8 *bgain, u8 *rgain);
	void(*get_flash_awb)(flash_platform_t type, mini_awb_gain_t *flash_awb);

	/*set ISP gain and exposure to sensor */
	void (*set_gain) (u32 gain);
	u32 (*get_gain) (void);
	void (*set_exposure) (u32 exposure);
	u32 (*get_exposure) (void);

	void (*set_exposure_gain) (u32 exposure, u32 gain);

	void (*set_vts) (u16 vts);
	u32 (*get_vts_reg_addr) (void);

	/* effect */
	void (*set_effect) (camera_effects effect);
	void (*set_awb) (camera_white_balance awb_mode);

	/* anti-banding */
	int (*set_anti_banding) (camera_anti_banding banding);

	/* update_framerate*/
	void (*update_framerate) (camera_frame_rate_mode mode);

	void (*awb_dynamic_ccm_gain) (u32 frame_index, u32 ae, mini_awb_gain_t  *awb_gain, mini_ccm_gain_t *ccm_gain);

	int (*get_sensor_aperture)(void);
	int (*get_equivalent_focus)(void);

	/*get sensor override parameters */
	u32 (*get_override_param)(camera_override_type_t type);

	u32 fmt[STATE_MAX];
	u32 preview_frmsize_index;
	u32 capture_frmsize_index;
	mini_framesize_s *frmsize_list;

	/* following struct can decide a sensor's frame rate and some AF feature */
	/* frame configs */
	u32 pclk;

	/* all above parameter decide this fps */
	u32 fps_max;
	u32 fps_min;
	u32 fps;

	/* for AEC/AGC
	 * integrate time
	 * gain
	 */
	u32 max_int_lines;
	u32 min_int_lines;
	u32 real_int_lines;

    /*begin: import sensor8850 from G710, the var "get_iso_limit" is only used in 8850 drv, 20130312*/
	/*get sensor supported iso upper limit or lower limit value*/
	/*int (*get_iso_limit)(camear_iso_limit_t type);*/
    /*end: import sensor8850 from G710, the var "get_iso_limit" is only used in 8850 drv, 20130312*/

	/*here gain is in unit of 1/16, it is same as OV8830 */
	u32 min_gain;
	u32 max_gain;
	u32 real_gain;

	/* af information */
	/* if false, following vcm info is invalid */
	u32 af_enable;
	mini_vcm_info_s *vcm;

	/* some sensor related params */
	mini_image_setting_t image_setting;

	/* red clip correcttion function for raw sensor switch*/
	bool rcc_enable;

	struct module *owner;
	camera_info_t info;
	u8 lane_clk;
    mini_effect_params *effect; //hefei add
	mini_sensor_hdr_movie_s sensor_hdr_movie;
	mini_hw_3a_mode  sensor_hw_3a;
	bool support_summary;
	bool isp_idi_skip;
	int lcd_compensation_supported;
} mini_camera_sensor;

extern mini_framesize_s mini_camera_framesizes[CAMERA_RESOLUTION_MAX];
extern mini_vcm_info_s mini_vcm_ad5823;
extern mini_vcm_info_s mini_vcm_dw9714;
extern u32 mini_sensor_override_params[];

/* get camera control data struct */
mini_camera_sensor *mini_get_camera_sensor_from_array(sensor_index_t sensor_index);
mini_camera_sensor **mini_get_camera_sensor(sensor_index_t sensor_index);
void mini_set_camera_sensor(sensor_index_t sensor_index, mini_camera_sensor *sensor);
int mini_clean_camera_sensor(sensor_index_t sensor_index);

/* register a sensor to system */
int mini_register_camera_sensor(sensor_index_t sensor_index, mini_camera_sensor *sensor);

/* unregister a sensor to system */
int mini_unregister_camera_sensor(sensor_index_t sensor_index, mini_camera_sensor *sensor);

mini_camera_flashlight *mini_get_camera_flash(void);

int mini_register_camera_flash(mini_camera_flashlight *flash);

int mini_unregister_camera_flash(mini_camera_flashlight *flash);

/* dump all registered sensors */
void mini_dump_camera_sensors(void);

/* get width and height value by resolution index */
int mini_camera_get_size_by_resolution(camera_resolutions res, u32 *width,
				  u32 *height);

/* get resolution index by width and height: -1 means failed */
int mini_camera_get_resolution_by_size(u32 width, u32 height);
camera_resolution_type mini_camera_get_resolution_type(u32 width, u32 height);

/* get camera count */
int mini_get_camera_count(void);
void mini_relocate_camera_sensor_by_name(sensor_index_t sensor_index,char *sensor_name);

/* power core ldo */
int mini_camera_power_core_ldo(camera_power_state power);
int mini_camera_power_id_gpio(camera_power_state power);

int mini_camera_get_i2c_speed(unsigned int chip_id, i2c_speed_t i2c_speed_idx);
int mini_camera_timing_is_match(int type);
mini_camera_sensor **mini_get_camera_sensor_array(sensor_index_t sensor_index);
#endif /*CAMERA_SENSOR_H_INCLUDED */

/********************************* END ***********************************************/
