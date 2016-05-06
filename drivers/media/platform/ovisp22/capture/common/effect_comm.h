#ifndef __EFFECT_COMM_H__
#define __EFFECT_COMM_H__


#define CAMERA_MAX_SETTING_SIZE	2000
#define CAMERA_MAX_EXPO_TABLE_SIZE 10
#define DNS_MAX_STEP 6
//#define DNS_MAX_FINE_STEP 3
#define SHARPNESS_MAX_STEP 7

typedef enum {
	CAMERA_METERING_SPOT = 0,
	CAMERA_METERING_CWA,
	CAMERA_METERING_AVERAGE,
	CAMERA_MERERING_MAX,
} camera_metering;


typedef enum {
	OV_STAT,
	YUV_EDGE_STAT,
} contrast_stat;

/******************************************************************************
	manual_wb_gain
 ******************************************************************************/
typedef enum {
	CAMERA_WHITEBALANCE_AUTO = 0,
	CAMERA_WHITEBALANCE_INCANDESCENT,
	CAMERA_WHITEBALANCE_FLUORESCENT,
	CAMERA_WHITEBALANCE_WARM_FLUORESCENT,
	CAMERA_WHITEBALANCE_DAYLIGHT,
	CAMERA_WHITEBALANCE_CLOUDY_DAYLIGHT,
	CAMERA_WHITEBALANCE_TWILIGHT,
	CAMERA_WHITEBALANCE_CANDLELIGHT,
	CAMERA_WHITEBALANCE_MAX,
} camera_white_balance;


/******************************************************************************
	scene_params
 ******************************************************************************/
typedef enum {
	CAMERA_SCENE_AUTO = 0,
	CAMERA_SCENE_ACTION,
	CAMERA_SCENE_PORTRAIT,
	CAMERA_SCENE_LANDSPACE,
	CAMERA_SCENE_NIGHT,
	CAMERA_SCENE_NIGHT_PORTRAIT,
	CAMERA_SCENE_THEATRE,
	CAMERA_SCENE_BEACH,
	CAMERA_SCENE_SNOW,
	CAMERA_SCENE_SUNSET,
	CAMERA_SCENE_STEADYPHOTO,
	CAMERA_SCENE_FIREWORKS,
	CAMERA_SCENE_SPORTS,
	CAMERA_SCENE_PARTY,
	CAMERA_SCENE_CANDLELIGHT,
	CAMERA_SCENE_BARCODE,
	CAMERA_SCENE_FLOWERS,
	CAMERA_SCENE_HDR,
	CAMERA_SCENE_HWAUTO,
	CAMERA_SCENE_MAX,   
} camera_scene;

#if 0
/******************************************************************************
	ev_bracket_ratios
 ******************************************************************************/
typedef struct _ev_bracket_ratios {
	u32 numerator;
	u32 denominator;
} ev_bracket_ratios;
#endif

/******************************************************************************
	red_clip_params
 ******************************************************************************/
typedef enum {
	RED_CLIP_NONE = 0,
	RED_CLIP_SHADE,
	RED_CLIP,
} red_clip_status;

typedef enum {
	LUM_LEVEL0 = 0,
	LUM_LEVEL1,
	LUM_LEVEL2,
	LUM_LEVEL3,
	LUM_LEVEL4,
	LUM_LEVEL5,
	LUM_LEVEL6,
	LUM_LEVEL7,
	LUM_LEVEL_MAX,
} flash_lum_level;

#endif

