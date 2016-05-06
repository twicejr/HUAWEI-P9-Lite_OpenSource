#ifndef __VIDEO_CONFIG_H__
#define __VIDEO_CONFIG_H__

typedef enum {
	VIDEO_BOARD_TYPE_BBIT   = 0,
    VIDEO_BOARD_TYPE_SFT, 
	VIDEO_BOARD_TYPE_ASIC,
	VIDEO_BOARD_TYPE_MAX
}video_board_type;

typedef enum {
	VIDEO_HI6210   = 0,
    VIDEO_HI6220, 
}video_chip_id;

typedef enum _camera_sensor_flip_type {
	CAMERA_SENSOR_FLIP_TYPE_NONE = 0,
	CAMERA_SENSOR_FLIP_TYPE_H_V,
	CAMERA_SENSOR_FLIP_TYPE_H,
	CAMERA_SENSOR_FLIP_TYPE_V
} camera_sensor_flip_type;

typedef struct
{
    unsigned int primary_sensor_flip_type;
    unsigned int secondary_sensor_flip_type;
}video_sensor_config;


unsigned int video_get_chip_id(void);
unsigned int video_get_board_type(void);
unsigned int video_get_support_isp(void);
unsigned int video_get_support_vpu(void);
unsigned int video_get_support_jpu(void);
unsigned int video_get_primary_sensor_flip_type(void);
unsigned int video_get_secondary_sensor_flip_type(void);
unsigned int video_check_suspensory_camera(char *cname);

int video_get_product_name(const char ** name);

#endif

