/*!
 *****************************************************************************
 *
 * @File       vdec_params.h
 * @Title      VDEC API Parameter structures (VDEC)
 * @Description    This file contains the data structures for video bitstream headers.
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

#ifndef __VDEC_PARAMS_H__
#define __VDEC_PARAMS_H__

#include "img_defs.h"
#include "avsfw_data.h"
#include "mpeg4fw_data.h"
#include "h264fw_data.h"
#include "hevcfw_data.h"
#include "vp6fw_data.h"
#include "vp8fw_data.h"
#include "jpegfw_data.h"
#include "mpeg2fw_data.h"
#include "realfw_data.h"
#include "vc1fw_data.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VDEC_H264_MAXIMUMVALUEOFCPB_CNT  32                       //!< Maximum number of alternative CPB specifications in the stream
#define VDEC_H264_MAX_SLICE_GROUPMBS     65536                    //!< Maximum number of H264 slice group maps, CHANGED FROM 810
#define VDEC_H264_MVC_MAX_VIEWS          (H264FW_MAX_NUM_VIEWS)   //!< Maximum number of MVC views
#define VDEC_H264_MVC_MAX_REFS           (H264FW_MAX_NUM_MVC_REFS)//!< Maximum number of MVC references
#define VDEC_H264_MVC_MAX_LEVELS         (16UL)                   //!< Maximum number of MVC levels (H.7.4.2.1.4)
#define VDEC_H264_MVC_MAX_APP_OP_TID     (16UL)                   //!< Maximum number of MVC operation points that apply to the level (H.7.4.2.1.4)
#define VDEC_H264_MVC_MAX_TARGET_VIEW    (8UL)                    //!< Maximum number of MVC views that apply to an operation point and a level (H.7.4.2.1.4)

#define VDEC_H264_MVC_REF_LIST_ANCHOR_L0        0      //!<Mayby make it private?
#define VDEC_H264_MVC_REF_LIST_ANCHOR_L1        1      //!<
#define VDEC_H264_MVC_REF_LIST_NON_ANCHOR_L0    0      //!<
#define VDEC_H264_MVC_REF_LIST_NON_ANCHOR_L1    1      //!<


/*!
******************************************************************************
 This structure contains AVS sequence header information.
 NOTE: Should only contain AVS specific information.
 @brief  AVS sequence header Information
******************************************************************************/
typedef struct
{
    IMG_UINT8   ui8ProfileId;          /*!< AVS profile information.                              */
    IMG_UINT8   ui8LevelId;            /*!< AVS level information.                                */
    IMG_BOOL    bProgressiveSequence;  /*!< if set, sequence does not contain interlaced frames.  */
    IMG_UINT8   ui8ChromaFormat;       /*!< chroma format (4:2:0 or 4:2:2).                       */
    IMG_UINT8   ui8SamplePrecision;    /*!< precision of luma and chroma samples.                 */
    IMG_UINT8   ui8AspectRatio;        /*!< Aspect ratio code                                     */
    IMG_BOOL    bLowDelay;             /*!< if set, sequence does not contain B-pictures.         */
    IMG_UINT32  ui32BbvBufferSize;     /*!< BBV buffer size                                       */

} VDEC_sAVSSequHdrInfo;


/*!
******************************************************************************
 This structure contains JPEG sequence header information.
 NOTE: Should only contain JPEG specific information.
 @brief  JPEG sequence header Information
******************************************************************************/
typedef struct
{
    IMG_UINT8  ui8NumComponent;  /*!< total component in jpeg  */
    IMG_UINT8  ui8Precision;     /*!< precision                */

} VDEC_sJPEGSequHdrInfo;


/*!
******************************************************************************
 This structure contains VP6 sequence header information.
 NOTE: Should only contain VP6 specific information.
 @brief  VP6 sequence header Information
******************************************************************************/
typedef struct
{
    IMG_UINT8  ui8VP3VersionNo;  /*!< Version number.  */

} VDEC_sVP6SequHdrInfo;


/*!
******************************************************************************
 This structure contains VP8 sequence header information.
 NOTE: Should only contain VP8 specific information.
 @brief  VP8 sequence header Information
******************************************************************************/
typedef struct
{
    IMG_UINT32  ui32FourCC;   /*!< FourCC of Codec.  */
    IMG_UINT32  ui32Version;  /*!< Version number.   */

} VDEC_sVP8SequHdrInfo;


/*!
******************************************************************************
 This structure contains H264 PPS (picture parameter set).
 NOTE: Should only contain H264 specific information.
******************************************************************************/
typedef struct
{
    /* These fields should be deprecated? Or maybe moved to H264FW_sPicturePS if necessary and needed for decode */
    IMG_BOOL        bEntropycodingModeFlag;                 /*!< entropy_coding_mode_flag;                  */
    //IMG_UINT8       ui8aScalingListPresentFlag[12];         /*!< seq_scaling_list_present_flag              */
    //IMG_UINT8       ui8aScalingList4x4[6][16];              /*!< ScalingList4x4[6][16]                      */
    //IMG_UINT8       ui8aScalingList8x8[6][64];              /*!< ScalingList8x8[6][64]                      */
    IMG_BOOL        bWightedPredFlag;                       /*!< weighted_pred_flag;                        */
    IMG_UINT8       ui8WightedBiPredFlag;                   /*!< weighted_bipred_idc;                       */
    IMG_INT32       i32PicInitQpMinus26;                    /*!< pic_init_qp_minus26;                       */
    IMG_INT32       i32PicInitQsMinus26;                    /*!< pic_init_qs_minus26;                       */
    IMG_BOOL        bDeblockingFilterControlPresentFlag;    /*!< deblocking_filter_control_present_flag;    */
    IMG_BOOL        bConstrainedIntraPredFlag;              /*!< constrained_intra_pred_flag;               */
    IMG_BOOL        bRedundantPicCntPresentFlag;            /*!< redundant_pic_cnt_present_flag;            */

    //IMG_UINT8       ui8SliceGroupMapType;
    IMG_UINT8       ui8NumSliceGroupMaps;                   /*!< num_slice_groups_minus1 + 1                */
    IMG_BOOL        bPicOrderPresentFlag;                   /*!< pic_order_present_flag                     */
    IMG_UINT8       aui8NumRefIdxlXActiveMinus1[2];         /*!< num_ref_idx_lX_active_minus1[] + 1         */
    IMG_UINT16      ui16SliceGroupChangeRateMinus1;         /*!< slice_group_change_rate_minus1             */

    /* These should be populated by the BSPP instead */
    H264FW_sPicturePS sH264FwPicturePS;               /*!< Syntax elements from PPS                */

} VDEC_sH264PPS;


/*!
******************************************************************************
 This structure contains JPEG start of frame segment header
 NOTE: Should only contain JPEG specific information.
 @brief  JPEG SOF header Information
******************************************************************************/
typedef struct
{
    IMG_UINT8  ui8Identifier;  /*!<  component identifier.  */
    IMG_UINT8  ui8HorzFactor;  /*!<  Horizontal scaling.    */
    IMG_UINT8  ui8VertFactor;  /*!<  Verticale scaling      */
    IMG_UINT8  ui8QuantTable;  /*!<  Qunatisation tables .  */

} VDEC_sJPEGSOFComponentHdr;


/*!
******************************************************************************
 This structure contains JPEG start of scan segment header
 NOTE: Should only contain JPEG specific information.
 @brief  JPEG SOS header Information
******************************************************************************/
typedef struct
{
    IMG_UINT8  ui8ComponentIndex;  /*!<  component identifier.  */
    IMG_UINT8  ui8DCTable;         /*!<  Huffman DC tables.     */
    IMG_UINT8  ui8ACTable;         /*!<  Huffman AC table .     */

} VDEC_sJPEGSOSComponentHdr;

/*!
******************************************************************************
 This structure contains JPEG picture header information.
 NOTE: Should only contain JPEG specific information.
 @brief  JPEG picture header Information
******************************************************************************/
typedef struct
{
    VDEC_sJPEGSOFComponentHdr   sSOFComp[JPEG_VDEC_MAX_COMPONENTS];                                                /*!< Start of frame component header       */
    VDEC_sJPEGSOSComponentHdr   sSOSComp[JPEG_VDEC_MAX_COMPONENTS];                                                /*!< Start of Scan component header        */
    VDEC_sJPEGHuffmanTableInfo  asHuffTables[JPEG_VDEC_TABLE_CLASS_NUM][JPEG_VDEC_MAX_SETS_HUFFMAN_TABLES];        /*!< Huffman tables                        */
    VDEC_sJPEGDeQuantTableInfo  asQuantTables[JPEG_VDEC_MAX_QUANT_TABLES];                                         /*!< Quantization tables                   */
    IMG_UINT16                  ui16Interval;                                                                      /*!< Number of MCU in the restart interval */
    IMG_UINT32                  test;

} VDEC_sJPEGPictHdrInfo;


#ifdef __cplusplus
}
#endif

#endif /* __VDEC_PARAMS_H__   */



