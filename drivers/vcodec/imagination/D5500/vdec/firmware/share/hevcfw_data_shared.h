/*!
 *****************************************************************************
 *
 * @File       hevcfw_data_shared.h
 * @Title      Public data structures for the HEVC parser firmware module
 * @Description    Public data structures for the HEVC parser firmware module
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
#endif

#ifndef _HEVCFW_DATA_H_
#define _HEVCFW_DATA_H_

#include "vdecfw_share.h"

#include "img_types.h"
#include "vdecfw.h"


#define HEVCFW_MAX_NUM_REF_PICS 16
#define HEVCFW_MAX_NUM_ST_REF_PIC_SETS 65
#define HEVCFW_MAX_NUM_LT_REF_PICS 32
#define HEVCFW_MAX_NUM_SUBLAYERS 7
#define HEVCFW_SCALING_LISTS_BUFSIZE 256
#define HEVCFW_MAX_TILE_COLS 20
#define HEVCFW_MAX_TILE_ROWS 22

#define HEVCFW_MAX_CHROMA_QP 6

#define HEVCFW_MAX_DPB_SIZE HEVCFW_MAX_NUM_REF_PICS
#define HEVCFW_REF_PIC_LIST0 0
#define HEVCFW_REF_PIC_LIST1 1
#define HEVCFW_NUM_REF_PIC_LISTS 2
#define HEVCFW_NUM_DPB_DIFF_REGS 4


/*!
******************************************************************************
    HEVC Short Term Reference Picture Set
******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, NumNegativePics);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, NumPositivePics);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT16, DeltaPocS0[HEVCFW_MAX_NUM_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT16, DeltaPocS1[HEVCFW_MAX_NUM_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, UsedByCurrPicS0[HEVCFW_MAX_NUM_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, UsedByCurrPicS1[HEVCFW_MAX_NUM_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, NumDeltaPocs);
} HEVCFW_sShortTermRefPicSet;

/*!
******************************************************************************
 This describes the SPS header data required by the HEVC firmware that should
 be supplied by the Host.
******************************************************************************/
typedef struct
{
    /* syntax elements from SPS */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, pic_width_in_luma_samples);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, pic_height_in_luma_samples);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, num_short_term_ref_pic_sets);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, num_long_term_ref_pics_sps);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, lt_ref_pic_poc_lsb_sps[HEVCFW_MAX_NUM_LT_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, used_by_curr_pic_lt_sps_flag[HEVCFW_MAX_NUM_LT_REF_PICS]);
    HEVCFW_sShortTermRefPicSet asStRpsList[HEVCFW_MAX_NUM_ST_REF_PIC_SETS];
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, sps_max_sub_layers_minus1);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, sps_max_dec_pic_buffering_minus1[HEVCFW_MAX_NUM_SUBLAYERS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, sps_max_num_reorder_pics[HEVCFW_MAX_NUM_SUBLAYERS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, sps_max_latency_increase_plus1[HEVCFW_MAX_NUM_SUBLAYERS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, max_transform_hierarchy_depth_inter);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, max_transform_hierarchy_depth_intra);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, log2_diff_max_min_transform_block_size);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, log2_min_transform_block_size_minus2);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, log2_diff_max_min_luma_coding_block_size);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, log2_min_luma_coding_block_size_minus3);

    struct
    {
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, chroma_format_idc : 2);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, separate_colour_plane_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, num_extra_slice_header_bits : 3);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, log2_max_pic_order_cnt_lsb_minus4 : 4);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, long_term_ref_pics_present_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, sample_adaptive_offset_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, sps_temporal_mvp_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, bit_depth_luma_minus8 : 3);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, bit_depth_chroma_minus8 : 3);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, pcm_sample_bit_depth_luma_minus1 : 4);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, pcm_sample_bit_depth_chroma_minus1 : 4);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, log2_min_pcm_luma_coding_block_size_minus3 : 2);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, log2_diff_max_min_pcm_luma_coding_block_size : 2);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, pcm_loop_filter_disabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, amp_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, pcm_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, strong_intra_smoothing_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, scaling_list_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, high_precision_offsets_enabled_flag : 1);
    };

    /* derived elements */
    IMG_UINT32 ui32PicSizeInCtbsY;
    IMG_UINT16 ui16PicHeightInCtbsY;
    IMG_UINT16 ui16PicWidthInCtbsY;
    IMG_UINT8 ui8CtbSizeY;
    IMG_UINT8 ui8CtbLog2SizeY;
    IMG_INT32 i32MaxPicOrderCntLsb;
    IMG_UINT32 ui32SpsMaxLatencyPictures[HEVCFW_MAX_NUM_SUBLAYERS];

} HEVCFW_sSequencePS;

/*!
******************************************************************************
 This describes the HEVC parser component "Header data", shown in the
 Firmware Memory Layout diagram. This data is required by the HEVC firmware
 and should be supplied by the Host.
******************************************************************************/
typedef struct
{
    /* Decode buffers and output control for the current picture */
    VDECFW_sImageBuffer sPrimary; //!< Primary decode buffer base addresses
    VDECFW_sImageBuffer sAlternate; //!< buffer base addresses for alternate output

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TemporalOutAddr); //!< address of buffer for temporal mv params

} HEVCFW_sHeaderData;

/*!
******************************************************************************
 This describes the PPS header data required by the HEVC firmware that should
 be supplied by the Host.
******************************************************************************/
typedef struct
{
    /* syntax elements from the PPS */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, pps_pic_parameter_set_id);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, num_tile_columns_minus1);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, num_tile_rows_minus1);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, diff_cu_qp_delta_depth);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT8, init_qp_minus26);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT8, pps_beta_offset_div2);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT8, pps_tc_offset_div2);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT8, pps_cb_qp_offset);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT8, pps_cr_qp_offset);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, log2_parallel_merge_level_minus2);

    struct
    {
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, dependent_slice_segments_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, output_flag_present_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, num_extra_slice_header_bits : 3);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, lists_modification_present_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, cabac_init_present_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, weighted_pred_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, weighted_bipred_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, pps_slice_chroma_qp_offsets_present_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, deblocking_filter_override_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, pps_loop_filter_accross_slices_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, tiles_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, entropy_coding_sync_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, slice_segment_header_extension_present_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, transquant_bypass_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, cu_qp_delta_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, transform_skip_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, sign_data_hiding_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, num_ref_idx_l0_default_active_minus1 : 4);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, num_ref_idx_l1_default_active_minus1 : 4);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, constrained_intra_pred_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, pps_deblocking_filter_disabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, pps_loop_filter_across_slices_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, loop_filter_across_tiles_enabled_flag : 1);

        /* rewritten from SPS, maybe at some point we could get rid of this */
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, scaling_list_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, chroma_qp_offset_list_enabled_flag : 1);
        IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, unsigned, diff_cu_chroma_qp_offset_depth : 2);
    };

    /* PVDEC derived elements. HEVCFW_SCALING_LISTS_BUFSIZE is multiplied by 2
     * to ensure that there will be space for address of each element. 
     * These addresses are completed in lower layer. */
    IMG_UINT32 aui32ScalingLists[HEVCFW_SCALING_LISTS_BUFSIZE * 2];

    /* derived elements */
    IMG_UINT16 aui16ColBd[HEVCFW_MAX_TILE_COLS + 1];
    IMG_UINT16 aui16RowBd[HEVCFW_MAX_TILE_ROWS + 1];

    IMG_UINT8 chroma_qp_offset_list_len_minus1;
    IMG_INT8 cb_qp_offset_list[HEVCFW_MAX_CHROMA_QP];
    IMG_INT8 cr_qp_offset_list[HEVCFW_MAX_CHROMA_QP];

} HEVCFW_sPicturePS;

/*!
******************************************************************************
 This enum determines reference picture status
******************************************************************************/
typedef enum
{
    HEVCFW_REF_UNUSED = 0,
    HEVCFW_REF_SHORTTERM,
    HEVCFW_REF_LONGTERM
} HEVCFW_eReferenceType;

/*!
******************************************************************************
 This describes an HEVC picture. It is part of the Context data
******************************************************************************/
typedef IMG_INT32 HEVCFW_Poc;
typedef struct
{
    VDECFW_sImageBuffer sPrimary; //!< Primary (reconstructed) picture buffers
    VDECFW_sImageBuffer sAlternate; //!< Secondary (alternative) picture buffers

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TransactionId); //!< Unique ID for this picture

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8NalUnitType); //!< nut of first ssh of picture, determines picture type
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_Poc, iPicOrderCntVal); //!< Picture Order Count (frame number)
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_Poc, iSlicePicOrderCntLsb); //!< Slice Picture Order Count Lsb
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL8, bPicOutputFlag); //!< PicOutputFlag

    /* information for collocated pictures */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16DpbLongtermFlags); //!< information about long-term pictures
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32DpbPicOrderDiff[HEVCFW_NUM_DPB_DIFF_REGS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TemporalOutAddr); //!< address of buffer for temporal mv params
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32DpbDiff); //!<  worst case Dpb diff for the current pic
} HEVCFW_sPicture;

/*!
******************************************************************************
 This is a wrapper for a picture to hold it in a Decoded Picture Buffer
 for further reference
******************************************************************************/
typedef struct
{
    /* DPB data about the picture */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_eReferenceType, eRefType);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL8, bValid);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL8, bNeededForOutput);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT8, i16PicLatencyCount);

    /* Picture itself */
    HEVCFW_sPicture sPicture;
} HEVCFW_sPictureInDpb;

/*!
******************************************************************************
 This describes an HEVC's Decoded Picture Buffer (DPB).
 It is part of the Context data
******************************************************************************/
typedef IMG_INT8 HEVCFW_DpbIdx;
#define HEVCFW_DPB_IDX_INVALID -1
typedef struct
{
    /* reference pictures */
    HEVCFW_sPictureInDpb asPictures[HEVCFW_MAX_DPB_SIZE];

    /* organizational data of DPB */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Fullness);
} HEVCFW_sDecodedPictureBuffer;

/*!
******************************************************************************
 This describes an HEVC's Reference Picture Set (RPS).
 It is part of the Context data
******************************************************************************/
typedef struct
{
    /* sizes of poc lists */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8NumPocStCurrBefore);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8NumPocStCurrAfter);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8NumPocStFoll);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8NumPocLtCurr);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8NumPocLtFoll);

    /* poc lists */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_Poc, aiPocStCurrBefore[HEVCFW_MAX_NUM_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_Poc, aiPocStCurrAfter[HEVCFW_MAX_NUM_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_Poc, aiPocStFoll[HEVCFW_MAX_NUM_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_Poc, aiPocLtCurr[HEVCFW_MAX_NUM_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_Poc, aiPocLtFoll[HEVCFW_MAX_NUM_REF_PICS]);

    /* derived elements */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL8, abCurrDeltaPocMsbPresentFlag[HEVCFW_MAX_NUM_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL8, abFollDeltaPocMsbPresentFlag[HEVCFW_MAX_NUM_REF_PICS]);

    /* reference picture sets: indices in DPB */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_DpbIdx, iRefPicSetLtCurr[HEVCFW_MAX_NUM_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_DpbIdx, iRefPicSetLtFoll[HEVCFW_MAX_NUM_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_DpbIdx, iRefPicSetStCurrBefore[HEVCFW_MAX_NUM_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_DpbIdx, iRefPicSetStCurrAfter[HEVCFW_MAX_NUM_REF_PICS]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_DpbIdx, iRefPicSetStFoll[HEVCFW_MAX_NUM_REF_PICS]);

} HEVCFW_sReferencePictureSet;

/*!
******************************************************************************
 This describes the HEVC parser component "Context data", shown in the
 Firmware Memory Layout diagram. This data is the state preserved across
 pictures. It is loaded and saved by the Firmware, but requires the host to
 provide buffer(s) for this.
******************************************************************************/
typedef struct
{
    HEVCFW_sSequencePS sSps;
    HEVCFW_sPicturePS sPps;

    /* data from last picture with TemporalId = 0 that is not a RASL, RADL
     * or sub-layer non-reference picture */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_Poc, iPrevPicOrderCntLsb);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_Poc, iPrevPicOrderCntMsb);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL8, bLastIrapNoRaslOutputFlag);

    /* Decoded Pictures Buffer holds information about decoded pictures
     * needed for further INTER decoding */
    HEVCFW_sDecodedPictureBuffer sDpb;
    /* Reference Picture Set is determined on per-picture basis */
    HEVCFW_sReferencePictureSet sRps;
    /* Reference Picture List is determined using data from Reference Picture
     * Set and from Slice (Segment) Header on per-slice basis */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, HEVCFW_DpbIdx, aiRefPicList[HEVCFW_NUM_REF_PIC_LISTS][HEVCFW_MAX_NUM_REF_PICS]);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PicCount);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32SliceSegmentCount);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bEOSdetected); /* There was EOS NAL detected and no new picture yet */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bFirstAfterEOS); /* This is first picture after EOS NAL */

} HEVCFW_sContextData;


#endif /* _HEVCFW_DATA_H_ */

