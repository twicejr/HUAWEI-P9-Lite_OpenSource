

/************************** END ***************************/

#ifndef __CAMERA_AGENT_H__
#define __CAMERA_AGENT_H__

#include "mini_k3_isp.h"
#include "mini_k3_ispv1.h"
#include "mini_k3_ispv1_afae.h"
#include "mini_k3_isp_io.h"
#include "mini_sensor_common.h"
#include "mini_isp.h"

enum stream_state {
	stream_state_off = 0,
	stream_state_on  = 1,
	stream_state_invalid = 2,
};

typedef enum _AE_mode {
	AUTO_MODE = 0,
	AVERAGE_MODE,
	CENTER_WEIGHTING_MODE,
	SPOT_MODE,
	MODE_MAX,
}AE_mode;

#define MINIISP_MAX_FACE_WIN  5
typedef struct _face_rect_s {
	u32 left;
	u32 top;
	u32 width;
	u32 height;
} face_rect_s;
typedef struct _face_win_info_s{
	face_rect_s face_area[MINIISP_MAX_FACE_WIN];
	u16 width; //length of preview size
	u16 height;//length of preview size
	u8   face_number;
	u8   index_max_face;
} face_win_info_s;


int camera_agent_get_test_result(void);
int camera_agent_set_sensormode(sensor_index_t sensor_index,u8 size_index,u8 hv_flip);
int camera_agent_s1_lock(sensor_index_t sensor_index);
int camera_agent_s1_lock_abort(void);
int camera_agent_set_s1_AF_enable(sensor_index_t sensor_index,u8 onoff);
int camera_agent_take_pictures(sensor_index_t sensor_index, u8 size_index,u8 hv_flip, u32 exposure,u32 ad_gain);
int camera_agent_streamonoff(sensor_index_t sensor_index, u8 state);
int camera_agent_set_focusarea(mini_focus_win_info_s *win_info);
int camera_agent_set_focusmode(sensor_index_t sensor_index,camera_focus mode);
int camera_agent_set_meteringarea(mini_camera_rect_s *win_info);
int camera_agent_set_facearea(face_win_info_s *win_info);
int camera_agent_set_PreviewAFLock(sensor_index_t sensor_index,u8 onoff);
int camera_agent_set_PreviewAELock(sensor_index_t sensor_index,u8 onoff);
int camera_agent_set_PreviewAWBLock(sensor_index_t sensor_index,u8 onoff);
int camera_agent_set_GSensorInfo(mini_axis_triple *xyz);
int camera_agent_set_Motion_Detected(u8 flag);
int camera_agent_set_ANTIFLICKER(sensor_index_t sensor_index,camera_anti_banding banding);
int camera_agent_get_ANTIFLICKER(sensor_index_t sensor_index);
int camera_agent_set_ISOLEVEL(sensor_index_t sensor_index,camera_iso iso);
int camera_agent_set_EV(sensor_index_t sensor_index,int ev);
int camera_agent_set_awb(sensor_index_t sensor_index,camera_white_balance awb_mode);
int camera_agent_set_flash_mode(camera_flash flash_mode);
int camera_agent_set_AFlevel(sensor_index_t sensor_index,u8 level);
int camera_agent_set_scene_mode(sensor_index_t sensor_index,camera_scene scene);
int camera_agent_set_exposuretime(u32 expotime);
int camera_agent_set_ADgain(u16 gain);
int camera_agent_set_ae_mode(sensor_index_t sensor_index,AE_mode mode);
int camera_agent_take_ae_image(void);
int camera_agent_set_auto_exposure(sensor_index_t sensor_index,u8 onoff);
int camera_agent_set_burst_shoot(u8 onoff);

void mini_ov_set_wb_value(mini_isp_meta_data *meta_data);
void mini_ov_set_ae_value(mini_isp_meta_data *meta_data);
void mini_ov_set_af_status(mini_isp_meta_data *meta_data);

void mini_isp_meta_data_parser(void *statphyaddr, void *meta_data_ptr);
void mini_isp_meta_data_init(mini_isp_meta_data **meta_data_ptr);
void mini_isp_meta_data_exit(void **meta_data_ptr);

int mini_ov_get_band_threshold(mini_camera_sensor *sensor, camera_anti_banding banding);
int mini_ov_get_val_meta_data(mini_isp_meta_data *meta_data);

int camera_agent_set_Preflashon(void);
bool mini_isp_check_s1_lock_need_af(void);
camera_flash mini_isp_check_af_flash_mode(void);
camera_flash mini_isp_check_pre_flash_mode(void);
void mini_isp_flash_controller(mini_isp_meta_data *meta_data);
#endif
