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

#ifndef CAMERA_SENSOR_H_INCLUDED
#define CAMERA_SENSOR_H_INCLUDED

#include <linux/videodev2.h>

/* control ID that is not in videodev2.h */
#define V4L2_CID_ISO                    (V4L2_CID_PRIVACY + 1)
#define V4L2_CID_EFFECT                 (V4L2_CID_PRIVACY + 2)
#define V4L2_CID_METERING               (V4L2_CID_PRIVACY + 3)
#define V4L2_CID_FLASH_MODE             (V4L2_CID_PRIVACY + 4)
#define V4L2_CID_EXT_FOCUS              (V4L2_CID_PRIVACY + 5)
#define V4L2_CID_SCENE                  (V4L2_CID_PRIVACY + 6)
#define V4L2_CID_SET_SENSOR             (V4L2_CID_PRIVACY + 7)
#define V4L2_CID_EXPOSURE_MAX           (V4L2_CID_PRIVACY + 8)
#define V4L2_CID_EXPOSURE_STEP          (V4L2_CID_PRIVACY + 9)

#define V4L2_CID_CAPTURE_BUFSIZE        (V4L2_CID_PRIVACY + 20)
#define V4L2_CID_CAPTURE_BUFCOUNT       (V4L2_CID_PRIVACY + 21)
#define V4L2_CID_SENSOR_COUNT           (V4L2_CID_PRIVACY + 22)
#define V4L2_CID_SENSOR_INFO            (V4L2_CID_PRIVACY + 23)

#define V4L2_CID_BUFFER_TYPE            (V4L2_CID_PRIVACY + 25)
#define V4L2_CID_BUFFER_INDEX           (V4L2_CID_PRIVACY + 26)
#define V4L2_CID_BUFFER_LENGTH          (V4L2_CID_PRIVACY + 27)
#define V4L2_CID_BUFFER_OFFSET          (V4L2_CID_PRIVACY + 28)

#define V4L2_CID_CAPTURE_MODE           (V4L2_CID_PRIVACY + 30)
#define V4L2_CID_PROCESS                (V4L2_CID_PRIVACY + 31)
#define V4L2_CID_BRACKET_INFO           (V4L2_CID_PRIVACY + 32)
#define V4L2_CID_ACTUAL_ISO             (V4L2_CID_PRIVACY + 33)
#define V4L2_CID_ACTUAL_EXPOSURE        (V4L2_CID_PRIVACY + 34)
#define V4L2_CID_FOCUS_MODE             (V4L2_CID_PRIVACY + 35)
#define V4L2_CID_MAX_FOCUS_AREA         (V4L2_CID_PRIVACY + 36)
#define V4L2_CID_FOCUS_AREA_INFO        (V4L2_CID_PRIVACY + 37)
#define V4L2_CID_FOCUS_RESULT           (V4L2_CID_PRIVACY + 38)
#define V4L2_CID_MAX_NUM_METERING_AREAS (V4L2_CID_PRIVACY + 39)
#define V4L2_CID_PHOTOMETRY_AREA_INFO   (V4L2_CID_PRIVACY + 40)
#define V4L2_CID_FPS_MAX                (V4L2_CID_PRIVACY + 41)
#define V4L2_CID_FPS_MIN                (V4L2_CID_PRIVACY + 42)
#define V4L2_CID_HDR                    (V4L2_CID_PRIVACY + 43)
#define V4L2_CID_WDR                    (V4L2_CID_PRIVACY + 44)
#define V4L2_CID_SMOOTHZOOM_SUPPORT     (V4L2_CID_PRIVACY + 45)

#define V4L2_CID_FOCAL_LENGTH           (V4L2_CID_PRIVACY + 50)
#define V4L2_CID_HORIZONTAL_VIEW_ANGLE  (V4L2_CID_PRIVACY + 51)
#define V4L2_CID_VERTICAL_VIEW_ANGLE    (V4L2_CID_PRIVACY + 52)

#define VIDIOC_CHECK_CAP  _IOWR('V', 200, struct v4l2_ext_controls)

#define FOCUS_AREA_MAX_NUM  10
enum {
    CAMERA_FACING_BACK = 0, /* The facing of the camera is opposite to that of the screen. */
    CAMERA_FACING_FRONT = 1 /* The facing of the camera is the same as that of the screen. */
};

struct CameraInfo
{
	int facing;
	int orientation;
};

typedef enum
{
	ISP_CAPTURE_ONLINE = 0,
	ISP_CAPTURE_OFFLINE,
} capture_mode_t;


typedef enum
{
	CAMERA_BYD_LENSCORRECTION = 0,
	CAMERA_LITEON_LENSCORRECTION,
	CAMERA_SUNNY_LENSCORRECTION,
} camera_lens_correction;

typedef enum
{
	CAMERA_CONTRAST_L2 = 0,
	CAMERA_CONTRAST_L1,
	CAMERA_CONTRAST_H0,
	CAMERA_CONTRAST_H1,
	CAMERA_CONTRAST_H2,
} camera_contrast;

typedef enum
{
	CAMERA_SATURATION_L2 = 0,
	CAMERA_SATURATION_L1,
	CAMERA_SATURATION_H0,
	CAMERA_SATURATION_H1,
	CAMERA_SATURATION_H2,
} camera_saturation;

typedef enum
{
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
} camera_effects;

typedef enum
{
	CAMERA_SHARPNESS_AUTO = 0,
	CAMERA_SHARPNESS_1,
	CAMERA_SHARPNESS_2,
	CAMERA_SHARPNESS_3,
	CAMERA_SHARPNESS_4,
	CAMERA_SHARPNESS_5,
} camera_sharpness;

typedef enum
{
	CAMERA_ISO_AUTO = 0,
	CAMERA_ISO_100,
	CAMERA_ISO_200,
	CAMERA_ISO_400,
	CAMERA_ISO_800,
} camera_iso;

typedef enum
{
	CAMERA_PHOTOMETRY_SPOT = 0,
	CAMERA_PHOTOMETRY_CWA,
	CAMERA_PHOTOMETRY_AVERAGE,
} camera_photo_metry;

typedef enum
{
	CAMERA_EV_L20 = 0,
	CAMERA_EV_L15,
	CAMERA_EV_L10,
	CAMERA_EV_L05,
	CAMERA_EV_H0,
	CAMERA_EV_H05,
	CAMERA_EV_H10,
	CAMERA_EV_H15,
	CAMERA_EV_H20,
	CAMERA_EV_MAX,
} camera_exposure;

typedef enum
{
	CAMERA_FLASH_OFF = 0,
	CAMERA_FLASH_AUTO,
	CAMERA_FLASH_ON,
	CAMERA_FLASH_RED_EYE,
	CAMERA_FLASH_TORCH,
} camera_flash;

typedef enum
{
	CAMERA_RESOLUTIONS_QCIF,	/* 176 x 144   */
	CAMERA_RESOLUTIONS_240x176,	/* 240 x 176   */
	CAMERA_RESOLUTIONS_QVGA,	/* 320 x 240   */
	CAMERA_RESOLUTIONS_CIF,	    /* 352 x 288   */
	CAMERA_RESOLUTIONS_HVGA,	/* 480 x 320   */
	CAMERA_RESOLUTIONS_VGA,	    /* 640 x 480   */
	CAMERA_RESOLUTIONS_800x480,	/* 800 x 480   */
	CAMERA_RESOLUTIONS_SVGA,	/* 800 x 600   */
	CAMERA_RESOLUTIONS_XGA,	    /* 1024 x 768  */
	CAMERA_RESOLUTIONS_VGA4,	/* 1280 x 960  */
	CAMERA_RESOLUTIONS_SXGA,	/* 1280 x 1024 */
	CAMERA_RESOLUTIONS_UXGA,	/* 1600 x 1200 */
	CAMERA_RESOLUTIONS_QXGA,	/* 2048 x 1536 */
	CAMERA_RESOLUTIONS_20MP,	/* 5164 x 3872 */
	CAMERA_RESOLUTIONS_MAX,
} camera_resolutions;

typedef enum
{
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
} camera_scene;

typedef enum
{
	CAMERA_NO_FLIP = 0,
	CAMERA_H_FLIP,
	CAMERA_V_FLIP,
	CAMERA_HV_FLIP,
} camera_flip;

typedef enum
{
	CAMERA_BRIGHTNESS_L2 = 0,
	CAMERA_BRIGHTNESS_L1,
	CAMERA_BRIGHTNESS_H0,
	CAMERA_BRIGHTNESS_H1,
	CAMERA_BRIGHTNESS_H2,
} camera_brightness;

typedef enum
{
	CAMERA_WHITEBALANCE_AUTO = 0,
	CAMERA_WHITEBALANCE_INCANDESCENT,
	CAMERA_WHITEBALANCE_FLUORESCENT,
	CAMERA_WHITEBALANCE_WARM_FLUORESCENT,
	CAMERA_WHITEBALANCE_DAYLIGHT,
	CAMERA_WHITEBALANCE_CLOUDY_DAYLIGHT,
	CAMERA_WHITEBALANCE_TWILIGHT,
	CAMERA_WHITEBALANCE_SHADE,
} camera_white_balance;

typedef enum
{
	CAMERA_FLICKER_AUTO = 0,
	CAMERA_FLICKER_50Hz,
	CAMERA_FLICKER_60Hz,
	CAMERA_FLICKER_OFF,
} camera_flicker;

typedef enum
{
	CAMERA_ZOOM_0 = 0,
	CAMERA_ZOOM_1,
	CAMERA_ZOOM_2,
	CAMERA_ZOOM_3,
	CAMERA_ZOOM_4,
	CAMERA_ZOOM_5,
} camera_zoom;

typedef enum
{
	CAMERA_FOCUS_AUTO = 0,
	CAMERA_FOCUS_INFINITY,
	CAMERA_FOCUS_MACRO,
	CAMERA_FOCUS_FIXED,
	CAMERA_FOCUS_EDOF,
    CAMERA_FOCUS_CONTINUOUS_VIDEO
} camera_focus;

typedef enum
{
    STATUS_FOCUSING = 0,
    STATUS_FOCUSED,
    STATUS_OUT_FOCUS
} FOCUS_STATUS;

typedef enum
{
	CAMERA_HDR_OFF = 0,
	CAMERA_HDR_ON,
} camera_hdr;

typedef enum
{
	CAMERA_WDR_OFF = 0,
	CAMERA_WDR_ON,
} camera_wdr;

typedef enum
{
	CAMERA_3D_OFF = 0,
	CAMERA_3D_ON,
} camera_3d;

typedef struct
{
	u32 id;
	u32 value;
} camera_capability;

typedef struct focus_result
{
    FOCUS_STATUS status;
    FOCUS_STATUS each_status[FOCUS_AREA_MAX_NUM];
} focus_result;


#endif /*CAMERA_SENSOR_H_INCLUDED*/

/********************************* END ***********************************************/
