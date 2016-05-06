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

#ifndef __K3_ISP_COMM_H__
#define __K3_ISP_COMM_H__

#include <linux/videodev2.h>
#include <linux/platform_device.h>
#include <linux/semaphore.h>
#include <linux/platform_device.h>
#include <linux/pm_qos.h>


#define V4L2_PIX_FMT_INVALID  0

/* ISP IDI reg control */
#define IDI_SCALE_DOWN_ENABLE				(1 << 2)
#define IDI_SCALE_DOWN_DISABLE				(0)
#define IDI_SCALE_DOWN_1667_1667			(0)
#define IDI_SCALE_DOWN_2_2					(1)
#define IDI_SCALE_DOWN_3_3					(2)

#define CAPTURE_STREAM_TRY_MAX_TIMES        (10)      //cap raw try max times.

/* yuv scale down ratio = N/0x10000 */
/* yuv scale up ratio = 0x10000/N */
#define YUV_SCALE_DIVIDEND	0x10000

#define ZOOM_BASE	0x100	/* 1x */
#define isp_zoom_to_ratio(zoom, video_stab) \
		(video_stab) ? (0x120 + (zoom)*24):(((zoom) * 10 + 100) * 0x100 / 100)

/* ZSL definition */
/*******************************************************************************
online process capability threshold: (process size)*30*(1+10%) < (isp_sclk)
10% means blank,5M is recommanded.
*******************************************************************************/
//#define ISP_DUAL_STREAM_ONLINE_CAP_THRESHOLD  (3264*2448+1)//(2592*1944)

/* command set CMD_ZOOM_IN_MODE relative parameters */
/* REG1 bit[0] : 1 for high quality, 0 for save power mode */
typedef enum {
	SAVE_POWER_MODE = 0x0,
	HIGH_QUALITY_MODE = 0x1,
} zoom_quality_t;

/* ISP In/Out data type */
enum {
	RAW_DATA = 0,
	YUV_DATA,
	RGB_DATA,
	JPEG_DATA,
	PACKED_DATA
};

/* RAW_DATA type */
enum {
	RAW8 = 0,
	RAW10,
	RAW12,
	RAW14
};

/* YUV422 type */
enum {
	UYVY = 0,
	VYUY,
	YUYV,
	YVYU
};

enum {
	CAMERA_CTL_OFF = 0,
	CAMERA_CTL_OVERLAY_START,
	CAMERA_CTL_CAPTURE_START,
	CAMERA_CTL_OVERLAY,
	CAMERA_CTL_CAPTURE,
};

enum {
	BUF_LEFT = 0,
	BUF_RIGHT,
	BUF_INVALID,
};

/* IDI choice enum */
enum {
    IDI_DISABLE         = 0,
    IDI_SCALEDOWN_1667,
    IDI_SCALEDOWN_2,
    IDI_SCALEDOWN_3,
};

typedef enum {
	AUTO_AECAGC = 0,
	MANUAL_AECAGC,
} aecagc_mode_t;

typedef enum {
	AUTO_AWB = 0,
	MANUAL_AWB,
} awb_mode_t;

typedef enum {
	RAW_SCALE_FIRST,
	YUV_SCALE_FIRST,
} scale_strategy_t;

typedef enum {
	UV_ADJUST_DISABLE,
	UV_ADJUST_ENABLE,
} uv_adjust_t;

#endif /*__K3_ISP_H__ */

/********************** END ***********************/
