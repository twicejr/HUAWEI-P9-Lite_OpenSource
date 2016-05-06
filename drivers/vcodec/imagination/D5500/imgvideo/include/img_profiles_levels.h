/*!
 *****************************************************************************
 *
 * @File       img_profiles_levels.h
 * @Title      Macro Definitions for all the supported video profiles and levels by MSVDX.
 * @Description    This file contains Macro definitions of the profiles and levels of all the video codec standards that can be used
 *  across drives.
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#ifndef __IMG_PROFILES_LEVELS_H
#define __IMG_PROFILES_LEVELS_H

#if defined(__cplusplus)
extern "C" {
#endif

/*****************************************************************************
 * HEVC related definitions
******************************************************************************/
#define HEVC_LEVEL_MIN             (30) /*!< Minimum level value for HEVC */
#define HEVC_LEVEL_MAX            (186) /*!< Maximum level value for HEVC */
#define HEVC_LEVEL_MAJOR_NUM        (6) /*!< Number of major levels for HEVC */
#define HEVC_LEVEL_MINOR_NUM        (3) /*!< Number of minor levels for HEVC */

#define HEVC_PROFILE_MAIN           (1) /*!< HEVC Main general_profile_idc value */
#define HEVC_PROFILE_MAIN10         (2) /*!< HEVC Main 10 general_profile_idc value */
#define HEVC_PROFILE_MAINSP         (3) /*!< HEVC Main Still Picture general_profile_idc value */

/*****************************************************************************
 * h.264 related definitions
******************************************************************************/
#define H264_LEVEL_MIN              (9)  /*!< Minimum level value for h.264.                                */
#define H264_LEVEL_MAX             (52)  /*!< Maximum level value for h.264.                                */
#define H264_LEVEL_MAJOR_NUM        (6)  /*!< Number of major levels for h.264 (5 + 1 for special levels).  */
#define H264_LEVEL_MINOR_NUM        (4)  /*!< Number of minor levels for h.264.                             */

#define H264_PROFILE_BASELINE      (66)  /*!< h.264 Baseline/Constrained Baseline profile id.  */
#define H264_PROFILE_MAIN          (77)  /*!< h.264 Main profile id.                           */
#define H264_PROFILE_EXTENDED      (88)  /*!< h.264 Extended profile id.                       */
#define H264_PROFILE_HIGH         (100)  /*!< h.264 High profile id.                           */
#define H264_PROFILE_HIGH444      (244)  /*!< h.264 High 4:4:4 profile id.                     */
#define H264_PROFILE_HIGH422      (122)  /*!< h.264 High 4:2:2 profile id.                     */
#define H264_PROFILE_HIGH10       (110)  /*!< h.264 High 10 profile id.                        */
#define H264_PROFILE_CAVLC444      (44)  /*!< h.264 CAVLC 4:4:4 Intra profile id.              */
#define H264_PROFILE_MVC_HIGH     (118)  /*!< h.264 Multiview High profile id.                 */
#define H264_PROFILE_STEREO_HIGH  (128)  /*!< h.264 Stereo High profile id.                    */

/*****************************************************************************
 * MPEG-2 related definitions
******************************************************************************/
#define MPEG2_PROFILE_SIMPLE              (5)  /*!< MPEG-2 Simple profile id.              */
#define MPEG2_PROFILE_MAIN                (4)  /*!< MPEG-2 Main profile id.                */
#define MPEG2_PROFILE_SNR_SCALABLE        (3)  /*!< MPEG-2 SNR Scalable profile id.        */
#define MPEG2_PROFILE_SPATIALLY_SCALABLE  (2)  /*!< MPEG-2 Spatially Scalable profile id.  */
#define MPEG2_PROFILE_HIGH                (1)  /*!< MPEG-2 High profile id.                */

/* Profiles for which escape bit is set to 1 are not supported.*/
#define MPEG2_PROFILE_MVP_LL         (0x8E)
#define MPEG2_PROFILE_MVP_ML         (0x8D)
#define MPEG2_PROFILE_MVP_HIGH1440   (0x8B)
#define MPEG2_PROFILE_MVP_HL         (0x8A)
#define MPEG2_PROFILE_422_LL         (0x85)
#define MPEG2_PROFILE_422_HL         (0x82)

#define MPEG2_LEVEL_HIGH             (4)
#define MPEG2_LEVEL_HIGH_1440        (6)
#define MPEG2_LEVEL_MAIN             (8)
#define MPEG2_LEVEL_LOW              (10)

/*****************************************************************************
 * VC-1 related definitions
******************************************************************************/
#define VC1_PROFILE_SIMPLE              (0)     /*!< VC1 Simple profile id.                 */
#define VC1_PROFILE_MAIN                (1)     /*!< VC1 Main profile id.                   */
#define VC1_PROFILE_ADVANCED            (3)     /*!< VC1 Advanced profile id.               */

#define VC1_LEVEL_L0                    (0x00)  /*!< Level 0 For VC1 Advanced Profile       */
#define VC1_LEVEL_L1                    (0x01)  /*!< Level 1 For VC1 Advanced Profile       */
#define VC1_LEVEL_L2                    (0x02)  /*!< Level 2 For VC1 Advanced Profile       */
#define VC1_LEVEL_L3                    (0x03)  /*!< Level 3 For VC1 Advanced Profile       */
#define VC1_LEVEL_L4                    (0x04)  /*!< Level 4 For VC1 Advanced Profile       */
#define VC1_LEVEL_Low                   (0x00)  /*!< Level Low with Simple/Main Profile     */
#define VC1_LEVEL_Medium                (0x02)  /*!< Level Medium with Simple/Main Profile  */
#define VC1_LEVEL_High                  (0x04)  /*!< Level Medium with only Main Profile    */

/*****************************************************************************
 * MPEG-4 related definitions
******************************************************************************/
#define MPEG4_PROFILE_SIMPLE_L0            (0x08)  /*!< MPEG-4 Simple Profile Level 0 id.            */
#define MPEG4_PROFILE_SIMPLE_L1            (0x01)  /*!< MPEG-4 Simple Profile Level 1 id.            */
#define MPEG4_PROFILE_SIMPLE_L2            (0x02)  /*!< MPEG-4 Simple Profile Level 2 id.            */
#define MPEG4_PROFILE_SIMPLE_L3            (0x03)  /*!< MPEG-4 Simple Profile Level 3 id.            */
#define MPEG4_PROFILE_ADVANCED_SIMPLE_L0   (0xf0)  /*!< MPEG-4 Advanced Simple Profile Level 0 id.   */
#define MPEG4_PROFILE_ADVANCED_SIMPLE_L1   (0xf1)  /*!< MPEG-4 Advanced Simple Profile Level 1 id.   */
#define MPEG4_PROFILE_ADVANCED_SIMPLE_L2   (0xf2)  /*!< MPEG-4 Advanced Simple Profile Level 2 id.   */
#define MPEG4_PROFILE_ADVANCED_SIMPLE_L3   (0xf3)  /*!< MPEG-4 Advanced Simple Profile Level 3 id.   */
#define MPEG4_PROFILE_ADVANCED_SIMPLE_L4   (0xf4)  /*!< MPEG-4 Advanced Simple Profile Level 4 id.   */
#define MPEG4_PROFILE_ADVANCED_SIMPLE_L5   (0xf5)  /*!< MPEG-4 Advanced Simple Profile Level 5 id.   */
#define MPEG4_PROFILE_ADVANCED_SIMPLE_L3b  (0xf7)  /*!< MPEG-4 Advanced Simple Profile Level 3b id.  */

/* Some more Mpeg profiles. We only support Simple and Advanced Simple profiles but can decode others
   and it should be upto the client to continue or not. Adding these here so that if we do not have
   profile_and_level_indication in VisualObjectSequence(), we can infer Codec Profile from
   video_object_type_indication in VideoObjectLayer(). We need this infered codec profile, and is used
   by vdecdd_utils_buf to set Max Number of reference pictures for the stream */

#define MPEG4_PROFILE_SIMPLE_SCLABLE_L2             (0x12)           /*!< MPEG-4 Simple Scalable Profile Level 2 id.   */
#define MPEG4_PROFILE_CORE_L2                       (0x22)           /*!< MPEG-4 Core Profile Level 2 id.              */
#define MPEG4_PROFILE_MAIN_L4                       (0x34)           /*!< MPEG-4 MAIN Profile Level 4 id.              */
#define MPEG4_PROFILE_NBIT_L2                       (0x42)           /*!< MPEG-4 NBIT Profile Level 2 id.              */
#define MPEG4_PROFILE_SCALABLE_TEXTURE_L1           (0x51)           /*!< MPEG-4 Scalable texture Profile Level 1 id.              */
#define MPEG4_PROFILE_BASIC_SIMPLE_FACE_L2          (0x62)           /*!< MPEG-4 Simple face Profile Level 2 id.              */
#define MPEG4_PROFILE_SIMPLE_FBA_L2                 (0x64)           /*!< MPEG-4 Simple FBA Profile Level 2 id.              */
#define MPEG4_PROFILE_BASIC_ANIMATED_TEXTURE_L2     (0x72)           /*!< MPEG-4 Basic Animated texture Profile Level 2 id.              */
#define MPEG4_PROFILE_ADVANCED_REAL_TIME_SIMPLE_L4  (0x94)           /*!< MPEG-4 Adavanced Real Time Simple Profile Level 4 id.              */
#define MPEG4_PROFILE_CORE_SCALABLE_L3              (0xA3)           /*!< MPEG-4 Core Scalable Profile Level 3 id.              */
#define MPEG4_PROFILE_ADVANCED_CODING_EFFIENCY_L4   (0xB4)           /*!< MPEG-4 Advanced coding efficiency Profile Level 4 id.              */
#define MPEG4_PROFILE_ADVANCED_SCALABLE_TEXTURE_L3  (0xD3)           /*!< MPEG-4 Advanced scalable texture Profile Level 3 id.              */
#define MPEG4_PROFILE_SIMPLE_STUDIO_L4              (0xE4)           /*!< MPEG-4 Simple Studio Profile Level 4 id.              */
#define MPEG4_PROFILE_CORE_STUDIO_L4                (0xE8)           /*!< MPEG-4 Core Studio Profile Level 4 id.              */
#define MPEG4_PROFILE_FGS_L5                        (0xFD)           /*!< MPEG-4 FGS Profile Level 5 id.               */

/*****************************************************************************
 * VP6 related definitions
******************************************************************************/
#define VP6_PROFILE_SIMPLE                  (0)
#define VP6_PROFILE_ADVANCED                (3)

/*****************************************************************************
 * AVS related definitions
******************************************************************************/
#define AVS_PROFILE_UNUSED              (0x00)
#define AVS_JIZHUN_PROFILE              (0x20)

#define AVS_LEVEL_UNUSED                (0x00)
#define AVS_LEVEL_20                    (0x10)
#define AVS_LEVEL_40                    (0x20)
#define AVS_LEVEL_42                    (0x22)
#define AVS_LEVEL_60                    (0x40)
#define AVS_LEVEL_62                    (0x42)

/*****************************************************************************
 * VP8 related definitions
******************************************************************************/
#define VP8_LEVEL_VERSION_0           (0)
#define VP8_LEVEL_VERSION_1           (1)
#define VP8_LEVEL_VERSION_2           (2)
#define VP8_LEVEL_VERSION_3           (3)


/*****************************************************************************
 * H263 related definitions
******************************************************************************/
// These are reserved MPEG4 profile values. May need to be changed
#define H263_PROFILE_BASELINE                                           (0)
#define H263_PROFILE_H320_VER2_BACKWARD_COMPATIBLITY                    (1)
#define H263_PROFILE_VER1_BACKWARD_COMPATIBLITY                         (2)
#define H263_PROFILE_VER2_INTERACTIVE_AND_STREAMING_WIRELESS            (3)
#define H263_PROFILE_VER3_INTERACTIVE_AND_STREAMING_WIRELESS            (4)
#define H263_PROFILE_CONVERSATIONAL_HIGH                                (5)
#define H263_PROFILE_CONVERSATIONAL_INTERNET                            (6)
#define H263_PROFILE_CONVERSATIONAL_INTERLACE                           (7)
#define H263_PROFILE_HIGH_LATENCY                                       (8)

#define H263_LEVEL_10                   (0)
#define H263_LEVEL_20                   (1)
#define H263_LEVEL_30                   (2)
#define H263_LEVEL_40                   (3)
#define H263_LEVEL_45                   (4)
#define H263_LEVEL_50                   (5)
#define H263_LEVEL_60                   (6)
#define H263_LEVEL_70                   (7)


/*****************************************************************************
 * Real Video related definitions
******************************************************************************/
#define RV_VIDEO_10                     (1)
#define RV_VIDEO_20                     (2)
#define RV_VIDEO_30                     (3)
#define RV_VIDEO_40                     (4)

#if defined(__cplusplus)
}
#endif

#endif /*__IMG_PROFILES_LEVELS_H*/
