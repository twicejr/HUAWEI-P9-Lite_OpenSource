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

#ifndef CAMERA_SENSOR_COMMON_COMM_H_INCLUDED
#define CAMERA_SENSOR_COMMON_COMM_H_INCLUDED

#include <linux/videodev2.h>
//#define ISP_ZSL_BURST_OPT  /*to be debug */


#define M_CAMERA_ANALOG_VDD     "mcamera_avdd"
#define M_CAMERA_CORE_VDD       "mcamera_core"
#define M_CAMERA_IO_VDD         "mcamera_io"
#define M_CAMERA_VCM_VDD        "mcamera_vcm"
#define S_CAMERA_ANALOG_VDD     "scamera_avdd"
#define S_CAMERA_CORE_VDD       "scamera_core"
#define S_CAMERA_IO_VDD         "scamera_io"
#define S_BACKUP_CAMERA_CORE_VDD "S_BACKUP_CAMERA_CORE_VDD"
#define M_CAMERA_IO_RESERVE_VDD "M_CAMERA_IO_RESERVE_VDD"
#define MINI_ISP_ANALOG_VDD     "MINI_ISP_ANALOG_VDD"
#define S_CAMERA_ID_PIN             "scamera_id_pin"
#define M_CAMERA_ID_PIN             "mcamera_id_pin"

#define LDO_VOLTAGE_10V  1050000
#define LDO_VOLTAGE_11V  1100000
#define LDO_VOLTAGE_12V  1200000
#define LDO_VOLTAGE_15V  1500000
#define LDO_VOLTAGE_18V  1800000
#define LDO_VOLTAGE_28V  2800000

/* Default camera sensor definitions(use K3 ISP), maybe override by sensor*/
#define CAMERA_MAX_ISO			800
#define CAMERA_MIN_ISO			100

#define CAMERA_AUTOFPS_GAIN_HIGH2MID		0x60
#define CAMERA_AUTOFPS_GAIN_MID2LOW		0x60
#define CAMERA_AUTOFPS_GAIN_LOW2MID		0x24
#define CAMERA_AUTOFPS_GAIN_MID2HIGH		0x24

/* support 3 level framerate now, if mid fps same as min, set to 2 level framerate */
#define CAMERA_MAX_FRAMERATE		30
#define CAMERA_MID_FRAMERATE		14
#define CAMERA_MIN_FRAMERATE		14
#define CAMERA_MIN_CAP_FRAMERATE	14

#define CAMERA_FLASH_TRIGGER_GAIN	0x70

#define CAMERA_SHARPNESS_PREVIEW	0x30
#define CAMERA_SHARPNESS_CAPTURE	0x0A

/* Below is recommended to be fixed parameters */
#define AUTO_FRAME_RATE_TRIGER_COUNT		4
#define FLASH_TRIGGER_LUM_RATIO	0xc0
/* 600mA flash lum maybe only 4 times of 100mA. */
#define FLASH_CAP2PRE_RATIO			0x04

#define CAMERA_EXPOSURE_MAX		2
#define CAMERA_EXPOSURE_STEP	100

typedef enum {
	CAMERA_CONTRAST_L2 = 0,
	CAMERA_CONTRAST_L1,
	CAMERA_CONTRAST_H0,
	CAMERA_CONTRAST_H1,
	CAMERA_CONTRAST_H2,
	CAMERA_CONTRAST_MAX,
} camera_contrast;

typedef enum {
	CAMERA_SATURATION_L2 = 0,
	CAMERA_SATURATION_L1,
	CAMERA_SATURATION_H0,
	CAMERA_SATURATION_H1,
	CAMERA_SATURATION_H2,
	CAMERA_SATURATION_MAX,
} camera_saturation;

typedef enum {
	CAMERA_FPS_MAX = 0,
	CAMERA_FPS_MIN,
	CAMERA_FPS_MID,
} camera_fps;

typedef enum {
	CAMERA_FRAME_RATE_FIX_MAX = 0,
	CAMERA_FRAME_RATE_FIX_MIN,
	CAMERA_FRAME_RATE_AUTO,
	CAMERA_FRAME_RATE_MAX,
} camera_frame_rate_mode;

typedef enum {
	CAMERA_MAX_EXPOSURE_LIMIT = 0,
	CAMERA_MAX_EXPOSURE_RESUME,
} camera_max_exposrure;

typedef enum {
	CAMERA_EFFECT_NONE = 0,
	CAMERA_EFFECT_MONO,
	CAMERA_EFFECT_NEGATIVE,
	CAMERA_EFFECT_SOLARIZE,
	CAMERA_EFFECT_SEPIA,
	CAMERA_EFFECT_POSTERIZE,
	CAMERA_EFFECT_WHITEBOARD,
	CAMERA_EFFECT_BLACKBOARD,
	CAMERA_EFFECT_AQUA,
	CAMERA_EFFECT_PASTEL,
	CAMERA_EFFECT_MOSAIC,
	CAMERA_EFFECT_REDTINT,
	CAMERA_EFFECT_BLUETINT,
	CAMERA_EFFECT_GREENTINT,
	CAMERA_EFFECT_MAX,
} camera_effects;

typedef enum {
	CAMERA_SHARPNESS_AUTO = 0,
	CAMERA_SHARPNESS_1,
	CAMERA_SHARPNESS_2,
	CAMERA_SHARPNESS_3,
	CAMERA_SHARPNESS_4,
	CAMERA_SHARPNESS_5,
} camera_sharpness;

typedef enum {
	CAMERA_ISO_AUTO = 0,
	CAMERA_ISO_100,
	CAMERA_ISO_200,
	CAMERA_ISO_400,
	CAMERA_ISO_800,
	CAMERA_ISO_1600,
} camera_iso;


typedef enum {
	CAMERA_FLASH_ON = 0,
	CAMERA_FLASH_TORCH,
	CAMERA_FLASH_OFF,
	CAMERA_FLASH_AUTO,
	CAMERA_FLASH_MAX,
} camera_flash;

typedef enum {
	CAMERA_RESOLUTION_QCIF,	/* 176 x 144   */
	CAMERA_RESOLUTION_240x176,	/* 240 x 176   */
	CAMERA_RESOLUTION_QVGA,	/* 320 x 240   */
	CAMERA_RESOLUTION_CIF,	/* 352 x 288   */
	CAMERA_RESOLUTION_HVGA,	/* 480 x 320   */
	CAMERA_RESOLUTION_VGA,	/* 640 x 480   */
	CAMERA_RESOLUTION_800x480,	/* 800 x 480   */
	CAMERA_RESOLUTION_SVGA,	/* 800 x 600   */
	CAMERA_RESOLUTION_XGA,	/* 1024 x 768  same as CAMERA_RESOLUTION_QTR_3M */
	CAMERA_RESOLUTION_720P,	/* 1280 x 720   add by y36721 */
	CAMERA_RESOLUTION_VGA4,	/* 1280 x 960  */
	CAMERA_RESOLUTION_QTR_5M,	/* 1296 x 972 (2592 x 1944/4) */
	CAMERA_RESOLUTION_SXGA,	/* 1280 x 1024 */
	CAMERA_RESOLUTION_UXGA,	/* 1600 x 1200 */
	CAMERA_RESOLUTION_1080P,	/* 1920 x 1080  add by y36721 */

	CAMERA_RESOLUTION_QTR_8M,	/*1632 x 1224 (3264 x 2448/4) */
	CAMERA_RESOLUTION_FULL_3M,	/* 2048 x 1536 */
	CAMERA_RESOLUTION_QTR_12M,	/*2104 x 1560 (4208 x 3120/4) */
	CAMERA_RESOLUTION_QTR_16M,	/*2304 x 1728 (4608 x 3456/4) */
	CAMERA_RESOLUTION_QTR_20M,	/* 2582 x 1936(5164 x 3872/4) */
	CAMERA_RESOLUTION_FULL_5M,	/* 2592 x 1944 */
	CAMERA_RESOLUTION_FULL_8M,	/* 3264 x 2448 */
	CAMERA_RESOLUTION_FULL_12M,	/* 4208 x 3120 */
	CAMERA_RESOLUTION_FULL_16M,	/* 4608 x 3456 */
	CAMERA_RESOLUTION_FULL_20M,	/* 5164 x 3872 */
	CAMERA_RESOLUTION_MAX,
} camera_resolutions;


typedef enum {
	CAMERA_NO_FLIP = 0,
	CAMERA_H_FLIP,
	CAMERA_V_FLIP,
	CAMERA_HV_FLIP,
} camera_flip;

typedef enum {
	CAMERA_BRIGHTNESS_L2 = 0,
	CAMERA_BRIGHTNESS_L1,
	CAMERA_BRIGHTNESS_H0,
	CAMERA_BRIGHTNESS_H1,
	CAMERA_BRIGHTNESS_H2,
	CAMERA_BRIGHTNESS_MAX,
} camera_brightness;


typedef enum {
	CAMERA_ANTI_BANDING_AUTO = 0,
	CAMERA_ANTI_BANDING_50Hz,
	CAMERA_ANTI_BANDING_60Hz,
	CAMERA_ANTI_BANDING_OFF,
} camera_anti_banding;

typedef enum {
	CAMERA_ZOOM_0 = 0,
	CAMERA_ZOOM_1,
	CAMERA_ZOOM_2,
	CAMERA_ZOOM_3,
	CAMERA_ZOOM_4,
	CAMERA_ZOOM_5,
} camera_zoom;

typedef enum {
	CAMERA_FOCUS_AUTO = 0,
	CAMERA_FOCUS_INFINITY,
	CAMERA_FOCUS_MACRO,
	CAMERA_FOCUS_FIXED,
	CAMERA_FOCUS_EDOF,
	CAMERA_FOCUS_CONTINUOUS_VIDEO,
	CAMERA_FOCUS_CONTINUOUS_PICTURE,
	CAMERA_FOCUS_AUTO_VIDEO,
	CAMERA_FOCUS_CAF_FORCE_AF,
	CAMERA_FOCUS_FAST_SHOOT,
	CAMERA_FOCUS_MAX,
} camera_focus;

typedef enum {
	CAMERA_ANTI_SHAKING_OFF = 0,
	CAMERA_ANTI_SHAKING_ON,
} camera_anti_shaking;

typedef enum {
	CAMERA_HDR_OFF = 0,
	CAMERA_HDR_ON,
} camera_hdr;

typedef enum {
	CAMERA_EDR_OFF = 0,
	CAMERA_EDR_ON,
} camera_edr;

typedef enum {
	CAMERA_3D_OFF = 0,
	CAMERA_3D_ON,
} camera_3d;

typedef enum {
	CAPTURE_ONLINE,
	CAPTURE_OFFLINE,
} capture_type;

typedef enum {
	CAMERA_IPP_MODE_RAW_2_YUV = 0,
	CAMERA_IPP_MODE_HDR,
	CAMERA_IPP_MODE_MAX
} ipp_mode;

typedef enum {
	CAMERA_SHOOT_SINGLE = 0,
	CAMERA_SHOOT_BURST
} camera_shoot_mode;

typedef enum {
	CAMERA_FPS_STATE_HIGH = 0,
	CAMERA_FPS_STATE_MIDDLE,
	CAMERA_FPS_STATE_LOW,

	CAMERA_EXPO_PRE_REDUCE1, /* before change fps from middle to high, maybe enter this state */
	CAMERA_EXPO_PRE_REDUCE2, /* before change fps from low to middle, maybe enter this state */
	CAMERA_FRAME_RATE_STATE_MAX
} camera_frame_rate_state;

typedef enum {
	CAMERA_FRAME_RATE_UP = 0,
	CAMERA_FRAME_RATE_DOWN,
} camera_frame_rate_dir;



typedef enum {
    CAMERA_ZSL_OFF = 0,
    CAMERA_ZSL_ON
} camera_zsl;

typedef enum {
    CAMERA_ZSL_OFFLINE = 0,
    CAMERA_ZSL_ONLINE
} camera_zsl_proc;

typedef enum {
    CAMERA_ZSL_CAP_CMD_START = 0,
    CAMERA_ZSL_CAP_CMD_STOP,
    CAMERA_ZSL_CAP_CMD_SUSPEND,
    CAMERA_ZSL_CAP_CMD_RESUME
} camera_zsl_cap_cmd;


typedef enum {
	VIEW_HDR_MOVIE = 0,
	VIEW_FULL = 1,
	VIEW_CROP,
	VIEW_ZOOM_MODE,
} camera_setting_view_type;

typedef enum {
	RESOLUTION_16_9 = 0,
	RESOLUTION_4_3,
} camera_resolution_type;


/* For focus start or stop command */
typedef enum _FOCUS_ACTION {
	FOCUS_STOP = 0,
	FOCUS_START,
	FOCUS_CAF_FORCE_AF,
	FOCUS_AF_RESUME_CAF,
} FOCUS_ACTION;

/* For focus result */
typedef enum _FOCUS_STATUS {
	STATUS_FOCUSING = 0,
	STATUS_FOCUSED,
	STATUS_OUT_FOCUS,
} FOCUS_STATUS;

typedef enum _FOCUS_RANGE{
	RANGE_NORMAL = 0,
	RANGE_INFINITY,
	RANGE_MACRO,
} FOCUS_RANGE;

typedef enum _VCM_TYPE{
	VCM_AD5823 = 0,
	VCM_DW9714,
	VCM_DW9714_Sunny,
	VCM_DW9714_Liteon,
	VCM_OTHER,
} VCM_TYPE;


typedef enum {
	LED_FLASH = 0,
	XEON_FLASH,
} flash_type;

typedef enum {
	FLASH_MODE = 0,
	TORCH_MODE,
} work_mode;

typedef enum {
	CLK_100M = 0x0a,
	CLK_150M = 0x0d,
	CLK_200M = 0x10,
	CLK_250M = 0x12,
	CLK_300M = 0x15,
	CLK_350M = 0x17,
	
	CLK_400M = 0x1a,
	CLK_450M = 0x1d,
	CLK_500M = 0x1f,
	CLK_550M = 0x24,
	CLK_650M = 0x2a,
	CLK_750M = 0x30,
	CLK_900M = 0x38,
	CLK_1100M = 0x46,
	CLK_1300M = 0x50,
	CLK_1500M = 0x5a,

} mipi_clk;


typedef enum {
	FLASH_100MA = 0x04,
	FLASH_200MA = 0x08,
	FLASH_300MA = 0x0b,
	FLASH_400MA = 0x10,
	FLASH_500MA = 0x14,
	FLASH_600MA = 0x18,
	FLASH_700MA = 0x1b,
	FLASH_800MA = 0x20,
	FLASH_MA_MAX = 0x20,
} flash_value;

typedef enum {
	FLASH_ON = 0,
	FLASH_OFF,
} camera_flash_state;

typedef enum {
	FLASH_TESTING = 0,
	FLASH_DONE,
	FLASH_FROZEN,
	FLASH_ASSIST_AF,
	FLASH_ASSIST_AF_DONE,
	FLASH_PREFLASH_DONE,
	FLASH_CAPFLASH_START,
} camera_flash_flow;

typedef enum {
	SENSOR_OV = 0,
	SENSOR_SONY,
	SENSOR_SAMSUNG,
	SENSOR_LIKE_OV,	/* sensor gain effect next frame, expo effect next 2 frames. */
	SENSOR_LIKE_SONY,	/* sensor gain and expo effect next 2 frames. */
} camera_sensor_type;

typedef enum {
	CAPTURE_SKIP_0 = 0,
	CAPTURE_SKIP_1,
	CAPTURE_SKIP_2,
	CAPTURE_SKIP_3,
} camera_capture_skip_frame;

typedef enum {
	SENSOR_GRBG = 0,
	SENSOR_RGGB,
	SENSOR_BGGR,
	SENSOR_GBRG,
} camera_sensor_rgb_type;

typedef enum {
	OFFLINE_RUNNING = 0,
	OFFLINE_READY,
} offline_state_t;

typedef enum {
	FRAMESIZE_NOSUMMARY = 0,
	FRAMESIZE_SUMMARY,
	FRAMESIZE_SUMMARY_MAX,
} summary_t;

typedef enum {
	FLASH_PLATFORM_U9510 = 0,
	FLASH_PLATFORM_9510E,
	FLASH_PLATFORM_S10,
	FLASH_PLATFORM_MAX,
} flash_platform_t;

typedef enum {
	OVERRIDE_ISO_HIGH = 0,
	OVERRIDE_ISO_LOW,

	/* reduce frame rate gain threshold */
	OVERRIDE_AUTOFPS_GAIN_HIGH2MID,
	OVERRIDE_AUTOFPS_GAIN_MID2LOW,

	/* increase frame rate gain threshold */
	OVERRIDE_AUTOFPS_GAIN_LOW2MID,
	OVERRIDE_AUTOFPS_GAIN_MID2HIGH,

	OVERRIDE_FPS_MAX,
	OVERRIDE_FPS_MID,
	OVERRIDE_FPS_MIN,
	OVERRIDE_CAP_FPS_MIN,

	OVERRIDE_FLASH_TRIGGER_GAIN,

	OVERRIDE_SHARPNESS_PREVIEW,
	OVERRIDE_SHARPNESS_CAPTURE,

	OVERRIDE_TYPE_MAX,
} camera_override_type_t;

#endif /*CAMERA_SENSOR_H_INCLUDED */

/********************************* END ***********************************************/
