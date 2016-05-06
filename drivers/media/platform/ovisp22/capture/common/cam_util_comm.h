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

#ifndef __K3_CAM_COMM_UTIL_H__
#define __K3_CAM_COMM_UTIL_H__

#include <linux/list.h>
#include <linux/wait.h>
#include <linux/videodev2.h>
#include <linux/semaphore.h>

/*  buffer flags indicates which queue the current buffer in */
#define CAMERA_FLAG_READYQ      1
#define CAMERA_FLAG_WORKQ       2
#define CAMERA_FLAG_DONEQ       4

#define MAX_FRAME_NR            8
#define CAMERA_BUF_RSV_BUF_IDX  0   //reserved buffer index

//#define OVISP_DEBUG_MODE
//#define OVISP_OFFLINE_MODE
//#define READ_BACK_RAW
//#define ISP_ZSL_NO_MEMCPY     /* FIXME:HAL need to be changed */
#define SUPPORT_ZSL_FLASH
#define ISP_ZSL_ZOOM_FIX

#define META_DATA_INFOSIZE    (128)

#endif /*__K3_CAM_UTIL_H__ */

/********************** END ***********************/
