/*!
 *****************************************************************************
 *
 * @File       mpeg4fw_data_shared.h
 * @Title      Public data structures for the mpeg4 parser firmware module
 * @Description    Public data structures for the mpeg4 parser firmware module
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

#ifndef _MPEG4FW_DATA_H_
#define _MPEG4FW_DATA_H_

#include "vdecfw_share.h"

#include "img_types.h"
#include "vdecfw.h"


typedef enum
{
    MPEG4FW_RECTANGULAR = 0,
    MPEG4FW_BINARY,
    MPEG4FW_BINARY_ONLY,
    MPEG4FW_GRAYSCALE,

} MPEG4FW_eVideoObjectLayerShape;


typedef enum
{
    MPEG4FW_I = 0,
    MPEG4FW_P,
    MPEG4FW_B,
    MPEG4FW_S,
    MPEG4FW_DISPOSABLE,        //!< Sorenson disposable frame (same as P but not used for reference)

} MPEG4FW_eCodingType;


typedef enum
{
    MPEG4FW_MPEG4 = 0,
    MPEG4FW_H263,
    MPEG4FW_SORENSON,

} MPEG4FW_eCodecType;


/*!
******************************************************************************

 This describes the Define Vop complexity estimation header data required
 by the MPEG4 firmware that should be supplied by the Host.

******************************************************************************/

typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, estimation_method);                            // 2    uimsbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, shape_complexity_estimation_disable);          // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, opaque);                                       // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, transparent);                                  // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, intra_cae);                                    // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, inter_cae);                                    // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, no_update);                                    // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, upsampling);                                   // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, texture_complexity_estimation_set_1_disable);  // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, intra_blocks);                                 // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, inter_blocks);                                 // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, inter4v_blocks);                               // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, not_coded_blocks);                             // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, texture_complexity_estimation_set_2_disable);  // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, dct_coefs);                                    // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, dct_lines);                                    // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, vlc_symbols);                                  // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, vlc_bits);                                     // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, motion_compensation_complexity_disable);       // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, apm);                                          // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, npm);                                          // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, interpolate_mc_q);                             // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, forw_back_mc_q);                               // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, halfpel2);                                     // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, halfpel4);                                     // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, sadct);                                        // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, quarterpel);                                   // 1    bslbf
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, version2_complexity_estimation_disable);       // 1    bslbf

} MPEG4FW_sDefineVopComplEstHdr;


/*!
******************************************************************************

 This describes the Video Object Layer header data required by the MPEG4
 firmware that should be supplied by the Host.

******************************************************************************/

typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, vop_time_increment_resolution);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, video_object_layer_width);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, video_object_layer_height);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, complexity_estimation_disable);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, interlaced);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, sprite_enable);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, no_of_sprite_warping_points);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, quant_type);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, intra_quant_mat[64]);     //raster scan order
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, nonintra_quant_mat[64]);  //raster scan order
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, resync_marker_disable);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, quant_precision);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, reduced_resolution_vop_enable);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, newpred_enable);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, sprite_warping_accuracy);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, quarter_sample);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, data_partitioned);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, reversible_vlc);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, obmc_disable);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, MPEG4FW_eVideoObjectLayerShape, video_object_layer_shape);
    MPEG4FW_sDefineVopComplEstHdr   define_vop_compl_est_header;

} MPEG4FW_sVideoObjectLayer;


/*!
******************************************************************************

 This describes the MPEG4 Short header sequence level data required by the MPEG4
 firmware that should be supplied by the Host.

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, width);   // values in pixels derived from source format
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, height);  // fields in H263/Sorensons headers.

} MPEG4FW_sSHSequenceInfo;


/*!
******************************************************************************
 This structure contains MPEG4 sequence header information.
 NOTE: Should only contain MPEG4 specific information.
 @brief  MPEG4 sequence header Information
******************************************************************************/
typedef struct
{
    MPEG4FW_sVideoObjectLayer  sVideoObjectLayer;  /*!< video object layer header information needed by mpeg4 firmware  */
    MPEG4FW_sSHSequenceInfo    sSHSequence;        /*!< short header mpeg4 variant sequence information                 */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, MPEG4FW_eCodecType, eCodecType);         /*!< sequence codec type (mpeg4, h263, sorensons)                    */

} MPEG4FW_sSequHdrInfo;


/*!
******************************************************************************

 This describes the MPEG4 parser component "Header data", shown in the
 Firmware Memory Layout diagram. This data is required by the MPEG4 firmware
 and should be supplied by the Host.

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Profile);                    //!< Video Standard Profile, see img_profiles_levels.h

    VDECFW_sImageBuffer        sPrimary;                       //!< Primary decode buffer base addresses
    VDECFW_sImageBuffer        sAlternate;                     //!< buffer base addresses for alternate output

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bBPictures);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MbParamsBaseAddress);        //!< Macroblock parameters base address for the picture
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FEParserVLRBufferSave);      //!< Addr to save FE parser not_coded bits between pictures
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FEParserVLRBufferLoad);      //!< Addr to load FE parser not_coded bits between pictures

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32DataPartition0BaseAddress);  //!< Used for storing phase 0 parameters when decoding a Data Partitioned stream
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32DataPartition1BaseAddress);  //!< Used for storing phase 1 parameters when decoding a Data Partitioned stream

} MPEG4FW_sHeaderData;


/*!
******************************************************************************

 This describes an MPEG4 picture. It is part of the Context data

******************************************************************************/
typedef struct
{

    VDECFW_sImageBuffer  sPrimary;                       //!< Primary decode buffer base addresses
    VDECFW_sImageBuffer  sAlternate;                     //!< buffer base addresses for alternate output

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MbParamsBaseAddress);        //!< Macroblock parameters base address for the picture
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FEParserVLRBufferSave);      //!< Addr to save FE parser not_coded bits between pictures
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FEParserVLRBufferLoad);      //!< Addr to load FE parser not_coded bits between pictures
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32DataPartition0BaseAddress);  //!< Used for storing phase 0 parameters when decoding a Data Partitioned stream
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32DataPartition1BaseAddress);  //!< Used for storing phase 1 parameters when decoding a Data Partitioned stream

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TransactionId);              //!< Unique ID for this picture
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8DisplayFlags);                //!< Flags for this picture for the display process
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bSentForDisplay);                //!< If this picture has been sent for display
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, MPEG4FW_eCodingType, eCodingType);                    //!< Frame type
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bSkip);                          //!< Indicate if this is a skip picture.

} MPEG4FW_sPicture;

/*!
******************************************************************************

 This describes the MPEG4 parser component "Context data", shown in the
 Firmware Memory Layout diagram. This data is the state preserved across
 pictures. It is loaded and saved by the Firmware, but requires the host to
 provide buffer(s) for this.

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL8, bStoreFlags);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32First32NotCodedFlags);

    /* Needed for Trb and Trd calculation */

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PastRefTime);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FutureRefTime);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32CurrentTime);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32ModuloBaseDecd);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32ModuloBaseDisp);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Gtframe);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL8, bCalcTFrameOnNextBFrame);

    MPEG4FW_sSequHdrInfo         sMPEG4SequHdrInfo;   //!< Sequence Information

    /* The reference picture logic here works with msvdx hardware terms rather
       than mpeg4 spec terms. So instead of backward and forward reference
       pictures we maintain a stack of two pictures. */

    MPEG4FW_sPicture  sOldRefPic;
    MPEG4FW_sPicture  sNewRefPic;

} MPEG4FW_sContextData;


#endif /* _MPEG4FW_DATA_H_ */
