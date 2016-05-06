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

#ifndef HWA_CAM_TUNE_H_COMM_INCLUDED
#define HWA_CAM_TUNE_H_COMM_INCLUDED


//#include <mach/boardid.h>

#define V4L2_CID_GET_MULTI_ISP_REG				(V4L2_CID_HWA_BASE + 0)
#define V4L2_CID_SET_MULTI_ISP_REG				(V4L2_CID_HWA_BASE + 1)
#define V4L2_CID_GET_BRACKET_ISO_VALUE			(V4L2_CID_HWA_BASE + 2)
#define V4L2_CID_GET_BRACKET_EXP_VALUE			(V4L2_CID_HWA_BASE + 3)
#define V4L2_CID_GET_AE_COFF					(V4L2_CID_HWA_BASE + 4)
#define V4L2_CID_GET_EXTRA_COFF					(V4L2_CID_HWA_BASE + 5)
#define V4L2_CID_HWSCOPE						(V4L2_CID_HWA_BASE + 20)
#define V4L2_CID_SET_CAP_ISO_RATIO_VALUE		(V4L2_CID_HWA_BASE + 22)
#define V4L2_CID_GET_LCD_COMPENSATION_SUPPORTED (V4L2_CID_HWA_BASE + 23)
#define V4L2_CID_GET_LCD_COMPENSATION_NEEDED    (V4L2_CID_HWA_BASE + 24)

#define V4L2_CID_GET_MAX_EXPO_TIME				(V4L2_CID_HWA_BASE + 25)
#define V4L2_CID_SET_MAX_EXPO_TIME				(V4L2_CID_HWA_BASE + 26)
#define V4L2_CID_SET_HDR_MOVIE_MODE                 (V4L2_CID_HWA_BASE + 27)
#define V4L2_CID_GET_HDR_MOVIE_CONSTANT_PARAM       (V4L2_CID_HWA_BASE + 28)
#define V4L2_CID_GET_HDR_MOVIE_VOLATILE_PARAM       (V4L2_CID_HWA_BASE + 29)
#define V4L2_CID_SET_HDR_MOVIE_AE_RESULT            (V4L2_CID_HWA_BASE + 30)
#define V4L2_CID_GET_HDR_MOVIE_SUPPORTED            (V4L2_CID_HWA_BASE + 31)
#define V4L2_CID_GET_HDR_STATS_INFO                 (V4L2_CID_HWA_BASE + 32)
#define V4L2_CID_SET_VCM_DEST_CODE                  (V4L2_CID_HWA_BASE + 33)
#define V4L2_CID_GET_AWB_OTP_INFO                   (V4L2_CID_HWA_BASE + 34)
#define V4L2_CID_FLASH_STATUS                       (V4L2_CID_HWA_BASE + 35)
#define V4L2_CID_GET_FOCUS_FRAME_CNT                (V4L2_CID_HWA_BASE + 36)
#define V4L2_CID_SET_ALC_AWB_SATUS					(V4L2_CID_HWA_BASE +37)
#define V4L2_CID_GET_ALGORITHM_ISO				    (V4L2_CID_HWA_BASE +40)
#define V4L2_CID_SET_META_DATA_VC_SWITCH            (V4L2_CID_HWA_BASE + 41)  //add by zhoutian for mini-ISP meta data
#define V4L2_CID_SET_MINI_ISP_FACE_INFO				(V4L2_CID_HWA_BASE + 42)
#define V4L2_CID_GET_MINI_ISP_DEBUG_INFO            (V4L2_CID_HWA_BASE + 43)  //add by zhoutian for mini-ISP meta data
#define V4L2_CID_SET_OVER_EXPOSURE                  (V4L2_CID_HWA_BASE + 44)
#define V4L2_CID_SET_MOTION                         (V4L2_CID_HWA_BASE + 45)
#define V4L2_CID_SET_MULTIDENOISE                   (V4L2_CID_HWA_BASE + 46)
#define V4L2_CID_SET_SCENE_MODE                     (V4L2_CID_HWA_BASE + 47)
#define V4L2_CID_SET_FAST_SNAPSHOT_MODE             (V4L2_CID_HWA_BASE + 48)
#define V4L2_CID_SET_CAPTURE_MODE                   (V4L2_CID_HWA_BASE + 49)
#define V4L2_CID_GET_AF_LEVEL                            (V4L2_CID_HWA_BASE + 50)
#define V4L2_CID_GET_AF_RANGE_MIN                   (V4L2_CID_HWA_BASE + 51)
#define V4L2_CID_GET_AF_RANGE_MAX                   (V4L2_CID_HWA_BASE + 52)

#define V4L2_CID_GET_OTP_STATUS                   (V4L2_CID_HWA_BASE + 53)


typedef struct hwq_multi_reg_data{
	u32 length;
        u32 reserved32;
        union {
            u32 *reg;
            u64 reserved64;
        };

        union{
           u32 *value;
           u64 reserved64_2;
        };
}hwq_multi_reg_data;


#endif /*HWA_CAM_TUNE_H_INCLUDED */

/********************************* END ***********************************************/
