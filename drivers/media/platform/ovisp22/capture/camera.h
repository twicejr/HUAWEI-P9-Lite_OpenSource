
/*
 *  Hisilicon K3 soc camera sensor header file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *	Author :
 *  Version:  1.2
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
#ifndef __CAMERA_H__
#define __CAMERA_H__

/* control ID that is not in videodev2.h */
#define V4L2_CID_ISO				(V4L2_CID_PRIVACY + 1)
#define V4L2_CID_EFFECT				(V4L2_CID_PRIVACY + 2)
#define V4L2_CID_METERING			(V4L2_CID_PRIVACY + 3)
#define V4L2_CID_FLASH_MODE			(V4L2_CID_PRIVACY + 4)
#define V4L2_CID_EXT_FOCUS			(V4L2_CID_PRIVACY + 5)
#define V4L2_CID_SCENE				(V4L2_CID_PRIVACY + 6)
#define V4L2_CID_SET_SENSOR			(V4L2_CID_PRIVACY + 7)
#define V4L2_CID_EXPOSURE_MAX		(V4L2_CID_PRIVACY + 8)
#define V4L2_CID_EXPOSURE_STEP		(V4L2_CID_PRIVACY + 9)
#define V4L2_CID_ANTI_SHAKING		(V4L2_CID_PRIVACY + 11)

#define V4L2_CID_CAPTURE_BUFSIZE	(V4L2_CID_PRIVACY + 20)
#define V4L2_CID_CAPTURE_BUFCOUNT	(V4L2_CID_PRIVACY + 21)
#define V4L2_CID_SENSOR_COUNT		(V4L2_CID_PRIVACY + 22)
#define V4L2_CID_SENSOR_INFO		(V4L2_CID_PRIVACY + 23)

#define  V4L2_CID_BUFFER_SHARE_FD   (V4L2_CID_PRIVACY + 24)

#define V4L2_CID_BUFFER_TYPE		(V4L2_CID_PRIVACY + 25)
#define V4L2_CID_BUFFER_INDEX		(V4L2_CID_PRIVACY + 26)
#define V4L2_CID_BUFFER_LENGTH		(V4L2_CID_PRIVACY + 27)
#define V4L2_CID_BUFFER_OFFSET		(V4L2_CID_PRIVACY + 28)

#define V4L2_CID_CAPTURE_MODE       (V4L2_CID_PRIVACY + 30)
#define V4L2_CID_PROCESS			(V4L2_CID_PRIVACY + 31)
#define V4L2_CID_BRACKET_INFO		(V4L2_CID_PRIVACY + 32)
#define V4L2_CID_ACTUAL_ISO			(V4L2_CID_PRIVACY + 33)
#define V4L2_CID_ACTUAL_EXPOSURE	(V4L2_CID_PRIVACY + 34)

#define V4L2_CID_FOCUS_MODE			(V4L2_CID_PRIVACY + 35)
#define V4L2_CID_MAX_FOCUS_AREA		(V4L2_CID_PRIVACY + 36)
#define V4L2_CID_FOCUS_AREA_INFO	(V4L2_CID_PRIVACY + 37)
#define V4L2_CID_FOCUS_RESULT		(V4L2_CID_PRIVACY + 38)

#define V4L2_CID_MAX_METERING_AREA		(V4L2_CID_PRIVACY + 39)
#define V4L2_CID_METERING_AREA_INFO		(V4L2_CID_PRIVACY + 40)

#define V4L2_CID_FPS_MAX				(V4L2_CID_PRIVACY + 41)
#define V4L2_CID_FPS_MIN				(V4L2_CID_PRIVACY + 42)
#define V4L2_CID_HDR					(V4L2_CID_PRIVACY + 43)
#define V4L2_CID_WDR					(V4L2_CID_PRIVACY + 44)
#define V4L2_CID_SMOOTHZOOM_SUPPORT		(V4L2_CID_PRIVACY + 45)
#define V4L2_CID_FOCAL_LENGTH			(V4L2_CID_PRIVACY + 50)
#define V4L2_CID_HORIZONTAL_VIEW_ANGLE	(V4L2_CID_PRIVACY + 51)
#define V4L2_CID_VERTICAL_VIEW_ANGLE	(V4L2_CID_PRIVACY + 52)

#define V4L2_CID_PROCESS_RAW_2_YUV      (V4L2_CID_PRIVACY + 55)
#define V4L2_CID_PROCESS_HDR            (V4L2_CID_PRIVACY + 56)

#define V4L2_CID_SET_METERING_FLASH	(V4L2_CID_PRIVACY + 57)
#define V4L2_CID_GET_METERING_FLASH_RESULT	(V4L2_CID_PRIVACY + 58)

#define V4L2_CID_AUTO_EXPOSURE_LOCK_SUPPORTED      (V4L2_CID_PRIVACY + 60)
#define V4L2_CID_AUTO_EXPOSURE_LOCK                (V4L2_CID_PRIVACY + 61)
#define V4L2_CID_AUTO_WHITE_BALANCE_LOCK_SUPPORTED (V4L2_CID_PRIVACY + 62)
#define V4L2_CID_AUTO_WHITE_BALANCE_LOCK           (V4L2_CID_PRIVACY + 63)

#define V4L2_CID_GET_FOCUS_DISTANCE                (V4L2_CID_PRIVACY + 64)
#define V4L2_CID_GET_CURRENT_VTS                   (V4L2_CID_PRIVACY + 65)
#define V4L2_CID_GET_CURRENT_FPS                   (V4L2_CID_PRIVACY + 66)
#define V4L2_CID_SET_FPS_LOCK                      (V4L2_CID_PRIVACY + 67)
#define V4L2_CID_GET_BAND_THRESHOLD                (V4L2_CID_PRIVACY + 68)

#define V4L2_CID_GET_AWB_GAIN			(V4L2_CID_PRIVACY + 70)
#define V4L2_CID_GET_AWB_GAIN_ORI		(V4L2_CID_PRIVACY + 71)

#define V4L2_CID_GET_FOCUS_CODE		(V4L2_CID_PRIVACY + 72)

#define V4L2_CID_PM_MODE                     (V4L2_CID_PRIVACY + 73)

#define V4L2_CID_SNAPSHOOT_MODE                     (V4L2_CID_PRIVACY + 74)

#define V4L2_CID_SET_GSENSOR_STAT		(V4L2_CID_PRIVACY + 75)

#define V4L2_CID_GET_EXPO_LINE		(V4L2_CID_PRIVACY + 80)
#define V4L2_CID_GET_SENSOR_VTS		(V4L2_CID_PRIVACY + 81)
#define V4L2_CID_GET_FOCUS_RECT		(V4L2_CID_PRIVACY + 82)

#define V4L2_CID_GET_CURRENT_CCM_RGAIN	(V4L2_CID_PRIVACY + 83)
#define V4L2_CID_GET_CURRENT_CCM_BGAIN	(V4L2_CID_PRIVACY + 84)

#define V4L2_CID_ZSL	                (V4L2_CID_PRIVACY + 90)
#define V4L2_CID_CAP_RAW	            (V4L2_CID_PRIVACY + 91)/*0:stop cap raw;1~6:start cap raw with raw buf cnt.  */
#define V4L2_CID_PROCESS_IMG            (V4L2_CID_PRIVACY + 92)

#define V4L2_CID_MINI_ISP_SUPPORTED     (V4L2_CID_PRIVACY + 95)

#define V4L2_CID_GET_APERTURE			(V4L2_CID_PRIVACY + 120)
#define V4L2_CID_GET_EQUIV_FOCUS		(V4L2_CID_PRIVACY + 121)
#define V4L2_CID_STATBUFFER_OFFSET		(V4L2_CID_PRIVACY + 130)

#define V4L2_CID_SET_3A_MODE             (V4L2_CID_PRIVACY +131)


#define V4L2_CID_SET_HW_3A_PARAM         (V4L2_CID_PRIVACY +132)

#define V4L2_CID_SET_VIDEO_STABILIZATION		(V4L2_CID_PRIVACY + 201)
#define V4L2_CID_GET_YUV_CROP_RECT		(V4L2_CID_PRIVACY + 202)
#define V4L2_CID_SET_YUV_CROP_POS		(V4L2_CID_PRIVACY + 203)
#define V4L2_CID_SET_MINIISP_TEST                   (V4L2_CID_PRIVACY + 204)
#define V4L2_CID_GET_MINIISP_TEST_RESULT   (V4L2_CID_PRIVACY + 205)

/*zoom with center */
#define V4L2_CID_SET_ZOOM_CENTER		(V4L2_CID_PRIVACY + 211)
#define V4L2_CID_GET_ZOOM_CENTER		(V4L2_CID_PRIVACY + 212)


#define V4L2_CID_HWA_BASE				(V4L2_CID_PRIVACY + 500)
#define V4L2_CID_HWA_MAX				(V4L2_CID_HWA_BASE + 128)
#define MAX_BRACKET_COUNT	3
/* FIXME: now we only support 1 area focus and metering */
#define MAX_METERING_RECT		1
#define MAX_FOCUS_RECT		1

#define CAMERA_SENSOR_NUM_MAX 10


#define SENSOR_NAME_MAX_LENTH    20

/* capbility definition */
#define THIS_AUTO_WHITE_BALANCE (1 << CAMERA_WHITEBALANCE_AUTO)
#define THIS_WHITE_BALANCE ( \
				(1 << CAMERA_WHITEBALANCE_INCANDESCENT)	| \
				(1 << CAMERA_WHITEBALANCE_FLUORESCENT)	| \
				(1 << CAMERA_WHITEBALANCE_DAYLIGHT)	| \
				(1 << CAMERA_WHITEBALANCE_CLOUDY_DAYLIGHT) \
			   )
#define THIS_BRIGHTNESS (\
				(1 << CAMERA_BRIGHTNESS_L2) | \
				(1 << CAMERA_BRIGHTNESS_L1) | \
				(1 << CAMERA_BRIGHTNESS_H0) | \
				(1 << CAMERA_BRIGHTNESS_H1) | \
				(1 << CAMERA_BRIGHTNESS_H2)   \
			)
#define THIS_CONTRAST (\
				(1 << CAMERA_CONTRAST_L2) | \
				(1 << CAMERA_CONTRAST_L1) | \
				(1 << CAMERA_CONTRAST_H0) | \
				(1 << CAMERA_CONTRAST_H1) | \
				(1 << CAMERA_CONTRAST_H2)   \
			)
#define THIS_SATURATION	(\
				(1 << CAMERA_SATURATION_L2) | \
				(1 << CAMERA_SATURATION_L1) | \
				(1 << CAMERA_SATURATION_H0) | \
				(1 << CAMERA_SATURATION_H1) | \
				(1 << CAMERA_SATURATION_H2)   \
			)
#define THIS_ISO	(\
				(1 << CAMERA_ISO_AUTO) | \
				(1 << CAMERA_ISO_100) | \
				(1 << CAMERA_ISO_200) | \
				(1 << CAMERA_ISO_400) | \
				(1 << CAMERA_ISO_800)   \
			)
#define THIS_EFFECT	(\
				(1 << CAMERA_EFFECT_NONE)      | \
				(1 << CAMERA_EFFECT_MONO)      | \
				(1 << CAMERA_EFFECT_NEGATIVE)  | \
				(1 << CAMERA_EFFECT_SEPIA)   \
			)
#define THIS_EXPOSURE    (CAMERA_EXPOSURE_MAX)
#define THIS_EXPOSURE_STEP (CAMERA_EXPOSURE_STEP)
#define THIS_SHARPNESS	(\
				(1 << CAMERA_SHARPNESS_AUTO)   | \
				(1 << CAMERA_SHARPNESS_1)      | \
				(1 << CAMERA_SHARPNESS_2)      | \
				(1 << CAMERA_SHARPNESS_3)      | \
				(1 << CAMERA_SHARPNESS_4)      | \
				(1 << CAMERA_SHARPNESS_5)        \
			)
#define THIS_METERING	(\
				(1 << CAMERA_METERING_SPOT)   | \
				(1 << CAMERA_METERING_CWA)   | \
				(1 << CAMERA_METERING_AVERAGE)  \
			)


#define THIS_HFLIP	(1 << CAMERA_H_FLIP)
#define THIS_VFLIP	(\
				(1 << CAMERA_NO_FLIP) | \
				(1 << CAMERA_H_FLIP)  | \
				(1 << CAMERA_V_FLIP)  | \
					(1 << CAMERA_HV_FLIP)   \
				)

#define THIS_HDR	(\
				(1 << CAMERA_HDR_ON) | \
				(1 << CAMERA_HDR_OFF) \
			)

#define THIS_ANTI_BANDING (\
				(1 << V4L2_CID_POWER_LINE_FREQUENCY_50HZ) | \
				(1 << V4L2_CID_POWER_LINE_FREQUENCY_60HZ) \
			)

#define THIS_SCENE	(\
				(1 << CAMERA_SCENE_AUTO) | \
				(1 << CAMERA_SCENE_ACTION) | \
				(1 << CAMERA_SCENE_PORTRAIT) | \
				(1 << CAMERA_SCENE_LANDSPACE) | \
				(1 << CAMERA_SCENE_NIGHT) | \
				(1 << CAMERA_SCENE_NIGHT_PORTRAIT) | \
				(1 << CAMERA_SCENE_THEATRE) | \
				(1 << CAMERA_SCENE_BEACH) | \
				(1 << CAMERA_SCENE_SNOW) | \
				(1 << CAMERA_SCENE_FIREWORKS) | \
				(1 << CAMERA_SCENE_CANDLELIGHT) |\
				(1 << CAMERA_SCENE_HDR) |\
				(1 << CAMERA_SCENE_HWAUTO)  \
			)

#define THIS_FOCUS_MODE	(\
				(1 << CAMERA_FOCUS_AUTO) | \
				(1 << CAMERA_FOCUS_INFINITY) | \
				(1 << CAMERA_FOCUS_MACRO) | \
				(1 << CAMERA_FOCUS_CONTINUOUS_VIDEO) | \
				(1 << CAMERA_FOCUS_CONTINUOUS_PICTURE)   \
			)

#define THIS_FLASH	(\
				(1 << CAMERA_FLASH_ON)   | \
				(1 << CAMERA_FLASH_TORCH)| \
				(1 << CAMERA_FLASH_OFF)  | \
				(1 << CAMERA_FLASH_AUTO)   \
			)

#define THIS_ZSL  (\
                (1 << CAMERA_ZSL_ON)        | \
                (1 << CAMERA_ZSL_OFF)         \
            )

/* process image type in zsl */
typedef enum {
    ZSL_PROC_IMG_STOP ,
    ZSL_PROC_IMG_HISTORY_BACKWARD_ONE ,
    ZSL_PROC_IMG_HISTORY_FORWARD_MULTI  ,
    ZSL_PROC_IMG_NEW_MULTI  ,
#if 0
    ZSL_PROC_IMG_HISTORY_BACKWARD_ONE_AND_NEW_MULTI ,
    ZSL_PROC_IMG_HISTORY_FORWARD_ONE_AND_NEW_MULTI  ,
    ZSL_PROC_IMG_HISTORY_FORWARD_MULTI_AND_NEW_MULTI  ,
#endif
    ZSL_PROC_IMG_MODE_MAX
} zsl_proc_img_t;

typedef enum {
	ISP_CAPTURE_ONLINE = 0,
	ISP_CAPTURE_OFFLINE,
} isp_process_mode_t;

enum {
	/* The facing of the camera is opposite to that of the screen. */
	CAMERA_FACING_BACK = 0,
	/* The facing of the camera is the same as that of the screen. */
	CAMERA_FACING_FRONT = 1,
};

typedef struct camera_info {
	int cameraId;
	int facing;
	int orientation;
	int focal_length;
	int h_view_angle;
	int v_view_angle;
	char name[SENSOR_NAME_MAX_LENTH];
} camera_info_t;

typedef enum {
	STATE_PREVIEW = 0,
	STATE_CAPTURE,
	STATE_IPP,
	STATE_MAX,
} camera_state;

typedef enum {
	BUFFERTYPE_PREVIEW = 0,
	BUFFERTYPE_CAPTURE,
	BUFFERTYPE_IPP,
	BUFFERTYPE_MAX,
} buffer_type;

typedef enum {
	POWER_ON = 0,
	POWER_OFF,
} camera_power_state;

typedef enum {
	MCLK_ENABLE = 0,
	MCLK_DISABLE,
} mclk_state;

typedef enum {
	DVP,
	MIPI1,
	MIPI2,
} data_interface_t;

typedef enum {
	CSI_LINES_1 = 0,
	CSI_LINES_2,
	CSI_LINES_3,
	CSI_LINES_4,
	CSI_LINES_5,
	CSI_LINES_6,
	CSI_LINES_7,
	CSI_LINES_8,
	CSI_LINES_INVALID,
} csi_lane_t;

typedef enum {
	CSI_INDEX_0 = 0,
	CSI_INDEX_1,
	CSI_INDEX_INVALID,
} csi_index_t;

typedef enum {
	CAMERA_SENSOR_PRIMARY = 0,
	CAMERA_SENSOR_SECONDARY,
	CAMERA_SENSOR_MAX
} sensor_index_t;

typedef enum {
	CAMERA_SENSOR_UNKNOWN = 0,
	CAMERA_SENSOR_KNOWN,
	CAMERA_SENSOR_INVALID,
} sensor_known_t;

typedef enum {
	CAMERA_USE_K3ISP = 0,
	CAMERA_USE_SENSORISP,
} isp_location_t;

typedef enum {
	I2C_PRIMARY = 0,
	I2C_SECONDARY
} i2c_index_t;

typedef enum {
	I2C_8BIT = 0,
	I2C_16BIT
} i2c_length;

typedef enum {
	PIXEL_ORDER_NO_CHANGED = 0x00,
	PIXEL_ORDER_CHANGED = 0x03,
} pixel_order;

/*
*	i2c_clk = 131M / 64 / i2c_div
*/
typedef enum {
	I2C_SPEED_100 = 0,
	I2C_SPEED_200 = 1,
	I2C_SPEED_400 = 2,
	I2C_SPEED_MAX = 3,
} i2c_speed_t;

typedef enum {
	LOW_VALID = 0,
	HIGH_VALID,
} electrical_valid_t;

#endif /*__CAMERA_H__*/

/************************* END ****************************/
