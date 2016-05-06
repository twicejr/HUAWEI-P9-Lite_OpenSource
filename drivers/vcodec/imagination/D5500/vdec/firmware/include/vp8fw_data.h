/*!
 *****************************************************************************
 *
 * @File       vp8fw_data.h
 * @Title      Public data structures for the vp8 parser firmware module
 * @Description    Public data structures for the vp8 parser firmware module
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

#ifdef USE_SHARING
#include "vp8fw_data_shared.h" /* Include shared header version here to replace the standard version. */
#endif

#ifndef _VP8FW_DATA_H_
#define _VP8FW_DATA_H_

#include <img_types.h>
#include "vdecfw.h"

/*!
******************************************************************************
 This type defines the picture type.
******************************************************************************/
typedef enum
{
    VP8FW_TYPE_NONE = 0,   //!< No valid picture
    VP8FW_TYPE_TOP,        //!< Picture contains the top (even) lines of the frame
    VP8FW_TYPE_BOTTOM,     //!< Picture contains the bottom (odd) lines of the frame
    VP8FW_TYPE_FRAME,      //!< Picture contains the entire frame
    VP8FW_TYPE_PAIR,       //!< Picture contains top and bottom lines of the frame
} VP8FW_ePictureType;

/*!
******************************************************************************
 This type defines the encoding type.
******************************************************************************/
typedef enum
{
    VP8FW_I_FRAME = 0x01,   //!< I endoded picture - no forward or backward references
    VP8FW_P_FRAME,          //!< P encoded picture - forward references only.
    VP8FW_SKIP_FRAME,       //!< Skipped frame
    VP8FW_UNKNOWN_FRAME,    //!< Unknown picture type
} VP8FW_eEncodingType;

// VP8 spec originating constants
#define VP8FW_MAX_MB_SEGMENTS         4
#define VP8FW_MB_FEATURE_TREE_PROBS   3
#define VP8FW_MAX_REF_LF_DELTAS       4
#define VP8FW_MAX_MODE_LF_DELTAS      4
#define VP8FW_MAX_PARTITIONS          9
#define VP8FW_BLOCK_TYPES             4
#define VP8FW_COEF_BANDS              8
#define VP8FW_PREV_COEF_CONTEXTS      3
#define VP8FW_MAX_COEF_TOKENS         12
#define VP8FW_MAX_ENTROPY_TOKENS      12
#define VP8FW_MB_LVL_MAX              2
#define VP8FW_SEGMENT_DELTADATA       0
#define VP8FW_SEGMENT_ABSDATA         1
#define VP8FW_MAX_LOOP_FILTER         63
#define VP8FW_MAX_QINDEX              127

   ///* 16x16 intra modes */
    //DC_PRED, V_PRED, H_PRED, TM_PRED, B_PRED,
    ///* 16x16 inter modes */
    //NEARESTMV, NEARMV, ZEROMV, NEWMV, SPLITMV,
    //MB_MODE_COUNT,
    ///* 4x4 intra modes */
    //B_DC_PRED = 0, B_TM_PRED, B_VE_PRED, B_HE_PRED, B_LD_PRED,
    //B_RD_PRED, B_VR_PRED, B_VL_PRED, B_HD_PRED, B_HU_PRED,
    ///* 4x4 inter modes */
    //LEFT4X4, ABOVE4X4, ZERO4X4, NEW4X4,
    //B_MODE_COUNT

typedef enum
{
    B_DC_PRED,          // average of above and left pixels
    B_TM_PRED,
    B_VE_PRED,           // vertical prediction
    B_HE_PRED,           // horizontal prediction
    B_LD_PRED,
    B_RD_PRED,
    B_VR_PRED,
    B_VL_PRED,
    B_HD_PRED,
    B_HU_PRED,
    LEFT4X4,
    ABOVE4X4,
    ZERO4X4,
    NEW4X4,
    B_MODE_COUNT
} VP8FW_eBPredictionMode;

typedef enum
{
    DC_PRED,            // average of above and left pixels
    V_PRED,             // vertical prediction
    H_PRED,             // horizontal prediction
    TM_PRED,            // Truemotion prediction
    B_PRED,             // block based prediction, each block has its own prediction mode
    NEARESTMV,
    NEARMV,
    ZEROMV,
    NEWMV,
    SPLITMV,
    MB_MODE_COUNT
} VP8FW_eMBPredictionMode;

#define VP8FW_BINTRAMODES ( B_HU_PRED + 1 )  /* 9 + 1 = 10 */
#define VP8FW_SUBMVREFS ( 1 + NEW4X4 - LEFT4X4 ) /* 1 + 13 - 10 = 7 */

#define VP8FW_NUM_UV_MODES ( B_PRED )
#define VP8FW_NUM_Y_MODES (VP8FW_NUM_UV_MODES + 1)

enum
{
    VP8FW_MV_MAX  = 1023,              /* max absolute value of a MV component */
    VP8FW_MV_VALS = (2 * VP8FW_MV_MAX) + 1,   /* # possible values "" , ( 2 * 1023 ) + 1  = 2047 */
    VP8FW_MV_LONG_WIDTH = 10,       /* Large MVs have 9 bit magnitudes */
    VP8FW_MV_NUM_SHORT = 8,         /* magnitudes 0 through 7 */
    /* probability offsets for coding each MV component */
    VP8FW_MV_PIS_SHORT = 0,         /* short (<= 7) vs long (>= 8) */
    VP8FW_MV_PSIGN,                /* sign for non-zero */
    VP8FW_MV_PSHORT,               /* 8 short values = 7-position tree */
    VP8FW_MV_PBITS = VP8FW_MV_PSHORT + VP8FW_MV_NUM_SHORT - 1, /* mvlong_width long value bits, 2+8-1 = 9 */
    VP8FW_MV_PCOUNT = VP8FW_MV_PBITS + VP8FW_MV_LONG_WIDTH    /* (with independent probabilities), 9 + 10 = 19 */
};

// Segment Feature Masks
#define VP8FW_SEGMENT_ALTQ    0x01
#define VP8FW_SEGMENT_ALT_LF  0x02

#define VP8FW_YMODES  (B_PRED + 1)
#define VP8FW_UVMODES (TM_PRED + 1)

#define VP8FW_MVREFS (1 + SPLITMV - NEARESTMV)

/*!
******************************************************************************

 This describes the VP8 parser component "Header data", shown in the
 Firmware Memory Layout diagram. This data is required by the VP8 firmware
 and should be supplied by the Host.

******************************************************************************/
typedef struct
{
    VDECFW_sImageBuffer				sPrimary;						//!< Primary decode buffer base addresses
    VDECFW_sImageBuffer				sAlternate;						//!< buffer base addresses for alternate output
    VP8FW_eEncodingType             eEncodingType;                  //!< Encoding type

    IMG_UINT32  ui32FrameLength;                //!< Frame Length from the container
#ifdef VDEC_USE_PVDEC_COMPATIBILITY
    IMG_UINT32  ui32SecondPartitionProbBaseAddress;   //!< Used for storing second partition probabilities
#endif
    IMG_UINT32  ui32DCTBaseAddress;             //!< DCT DMA Address for MPC
    IMG_UINT32  ui32MbFlagsBaseAddress;         //!< Macroblock Flags base address for the picture
    IMG_UINT32  ui32FirstPartitionBaseAddress;  //!< Used for storing first partition parameters
    IMG_UINT32  ui32CurrentPictureBaseAddress;  //!< Used for storing current picture parameters
    IMG_UINT32  ui32SegmentIDBaseAddress;       //!< Used for storing segmentID parameters

} VP8FW_sHeaderData;

/*!
******************************************************************************

 This describes an VP8 picture. It is part of the Context data

******************************************************************************/
typedef struct
{
    VDECFW_sImageBuffer sPrimary;                                   //!< Primary (reconstructed) picture buffers
    VDECFW_sImageBuffer sAlternate;                                 //!< Secondary (alternative) picture buffers

    IMG_UINT32          ui32TransactionId;                          //!< Unique ID for this picture
    //VP8FW_eEncodingType eEncodingType;                              //!< Encoding type
    IMG_UINT8           ui8DisplayFlags;                            //!< Flags for this picture for the display process
} VP8FW_sPicture;

/*
******************************************************************************

 This caches data needed from initial state of sContext structure before
 picture managment happens

******************************************************************************/
typedef struct
{
    VP8FW_sPicture  sGoldenPic;
    VP8FW_sPicture  sAltPic;
    VP8FW_sPicture  sLastPic;
} VP8FW_sCachedData;

// Frame context
typedef struct
{
    IMG_UINT8               aui8DCT_Coefficients[VP8FW_BLOCK_TYPES][VP8FW_COEF_BANDS][VP8FW_PREV_COEF_CONTEXTS][VP8FW_MAX_COEF_TOKENS-1];
    IMG_UINT8               aui8MVContext[2][VP8FW_MV_PCOUNT];
    IMG_UINT8               aui8vp8YModeProb[VP8FW_NUM_Y_MODES - 1];
    IMG_UINT8               aui8vp8UVModeProb[VP8FW_NUM_UV_MODES - 1];
} VP8FW_sFrameContextData;

// H/V Scaling
typedef enum
{
    VP8FW_UPSCALE_0 = 0,
    VP8FW_UPSCALE_5_4,
    VP8FW_UPSCALE_5_3,
    VP8FW_UPSCALE_2,
    VP8FW_UPSCALE_MAX
} VP8FW_eScalingType;

// Color Space
typedef enum
{
    VP8FW_COLORSPACE_YUV_YCRCBITU = 0,
    VP8FW_COLORSPACE_YUV_TORGBNOMULDIV,
    VP8FW_COLORSPACE_MAX,
} VP8FW_eColorSpaceType;

// I-Frame only data
typedef struct
{
    IMG_UINT32              ui32FrameWidth;
    IMG_UINT32              ui32FrameHeight;
    VP8FW_eScalingType      eScaleHorizontal;
    VP8FW_eScalingType      eScaleVertical;
    VP8FW_eColorSpaceType   eColorSpace;
    IMG_BOOL                bClampingRequired;
} VP8FW_sKeyFrameData;

/*!
******************************************************************************
 This enum defines the macroblock level features
******************************************************************************/
typedef enum
{
    VP8FW_LEVEL_ALTQUANT = 0,
    VP8FW_LEVEL_ALTLOOPFILTER,
    VP8FW_LEVEL_MAX
} VP8FW_eLevelFeatures;

/*!
******************************************************************************

 This describes the VP8 parser component "Context data", shown in the
 Firmware Memory Layout diagram. This data is the state preserved across
 pictures. It is loaded and saved by the Firmware, but requires the host to
 provide buffer(s) for this.

******************************************************************************/
typedef struct
{
    IMG_UINT8   aui8DCT_Coefficients[VP8FW_BLOCK_TYPES][VP8FW_COEF_BANDS][VP8FW_PREV_COEF_CONTEXTS][VP8FW_MAX_COEF_TOKENS-1];
    IMG_UINT8   aui8MVContext[2][VP8FW_MV_PCOUNT];

#ifdef VDEC_USE_PVDEC_COMPATIBILITY
    IMG_UINT32  ui32SecondPartitionProbBaseAddress;                        //!< Second partition probabilities
#endif
    IMG_UINT32  ui32DCTBaseAddress;                             //!< DCT DMA Address for MPC
    IMG_UINT32  ui32MbFlagsBaseAddress;                         //!< Macroblock Flags base address for the picture
    IMG_UINT32  ui32FirstPartitionBaseAddress;                  //!< Used for storing first partition parameters
    IMG_UINT32  ui32CurrentPictureBaseAddress;                  //!< Used for storing current picture parameters
    IMG_UINT32  ui32SegmentIDBaseAddress;                       //!< Used for storing segmentID parameters

    IMG_BOOL    bAbsDelta;

    IMG_INT8    ai8FeatureData[VP8FW_LEVEL_MAX][VP8FW_MAX_MB_SEGMENTS];
    IMG_INT8    ai8DeltasRef[VP8FW_MAX_REF_LF_DELTAS];
    IMG_INT8    ai8DeltasMode[VP8FW_MAX_REF_LF_DELTAS];

    IMG_UINT8   aui8ProbYPlane[4];
    IMG_UINT8   aui8ProbUVPlane[3];

    VP8FW_sKeyFrameData             sKeyFrame;                  //!< I-Frame only data

    VP8FW_sFrameContextData         sFrameContext;              //!< Current Frame Context

    //VP8FW_sCachedData			    sCache;					    //!< Cached context data before picture managment happens

    // Picture reference/reordering management
    VP8FW_sPicture  sGoldenPic;
    VP8FW_sPicture  sAltPic;
    VP8FW_sPicture  sLastPic;

} VP8FW_sContextData;

#endif /* _VP8FW_DATA_H_ */
