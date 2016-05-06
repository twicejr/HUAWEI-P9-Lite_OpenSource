/*!
 *****************************************************************************
 *
 * @File       vp6fw_data_shared.h
 * @Title      Public data structures for the vp6 parser firmware module
 * @Description    Public data structures for the vp6 parser firmware module
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

#ifndef _VP6FW_DATA_H_
#define _VP6FW_DATA_H_

#include "vdecfw_share.h"

#include "img_types.h"
#include "vdecfw.h"


/* max number of bits allowed in a VLC code */
#define VLC_MAX_CODE_LEN        (16)

/* max num bits to decode in any one decode direct operation */
#define VLC_MAX_DIRECT_WIDTH    (4)

/*
******************************************************************************

 This structure defines the VLC code used for a partiular symbol

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT16, ui16Code);    // VLC code with valid data in top-most bits
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8CodeLen);   // VLC code length
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8Symbol);    // Symbol

} VLC_sSymbolCode;


/*
******************************************************************************

 This structure describes a set of VLC codes for a particular Huffman tree

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32NumCodes);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MinLen);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MaxLen);

} VLC_sSymbolStats;


/*
******************************************************************************

 This structure describes the generated VLC code table

******************************************************************************/
typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Size);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32InitialWidth);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32InitialOpcode);

} VLC_sTableStats;


/****************************************************************************
*  Module statics
****************************************************************************/
#define MODETYPES       3
#define MODEVECTORS     16
#define PROBVECTORXMIT  174
#define PROBIDEALXMIT   254

#define PROB_UPDATE_BASELINE_COST	7
#define SCAN_ORDER_BANDS		    16
#define SCAN_BAND_UPDATE_BITS       4

#define DC_TOKEN_CONTEXTS		    3 // 00, 0!0, !0!0
#define CONTEXT_NODES			    (MAX_ENTROPY_TOKENS-7)

#define PREC_CASES				    3
#define VP6_AC_BANDS			    6

#define ZRL_BANDS				    2
#define ZERO_RUN_PROB_CASES         14

#define DCT_EOB_TOKEN               11		//EOB		Extra Bits 0+0
#define MAX_ENTROPY_TOKENS          (DCT_EOB_TOKEN + 1)

#define MAX_MODES                   10
#define MV_NODES	                17
#define LONG_MV_BITS                8
#define BLOCK_HEIGHT_WIDTH          8
#define VP6FW_BLOCK_SIZE                  (BLOCK_HEIGHT_WIDTH * BLOCK_HEIGHT_WIDTH)

#define DCProbOffset(A,B)           ( (A) * (MAX_ENTROPY_TOKENS-1) + (B) )


// Tokens								    Value		Extra Bits (range + sign)
#define ZERO_TOKEN                  0		//0			Extra Bits 0+0
#define ONE_TOKEN                   1		//1			Extra Bits 0+1
#define TWO_TOKEN                   2  		//2			Extra Bits 0+1
#define THREE_TOKEN                 3		//3			Extra Bits 0+1
#define FOUR_TOKEN                  4		//4			Extra Bits 0+1
#define DCT_VAL_CATEGORY1		    5		//5-6		Extra Bits 1+1
#define DCT_VAL_CATEGORY2		    6		//7-10		Extra Bits 2+1
#define DCT_VAL_CATEGORY3		    7		//11-26		Extra Bits 4+1
#define DCT_VAL_CATEGORY4		    8		//11-26		Extra Bits 5+1
#define DCT_VAL_CATEGORY5		    9		//27-58		Extra Bits 5+1
#define DCT_VAL_CATEGORY6		    10		//59+		Extra Bits 11+1
#define DCT_EOB_TOKEN               11		//EOB		Extra Bits 0+0
//#define MAX_ENTROPY_TOKENS        (DCT_EOB_TOKEN + 1)
//#define ILLEGAL_TOKEN			    255


// *************** VP6 defines - enums ***************

#define VP6_VLC_MAX_NUM_CODES   (12)
#define VP6_VLC_NUM_TABLES      (29)
#define VP6_VLC_TABLE_SPACE     (40)

#define VP6_FRAME_TYPE_I        (0x00)
#define VP6_FRAME_TYPE_P        (0x01)

#define FW_VP6_PROFILE_SIMPLE      (0x00)
#define FW_VP6_PROFILE_ADVANCED    (0x03)

#define VEC_MODE_VP6 10


typedef enum
{
    CODE_INTER_NO_MV        = 0x0,      // INTER prediction, (0,0) motion vector implied.
    CODE_INTRA              = 0x1,      // INTRA i.e. no prediction.
    CODE_INTER_PLUS_MV      = 0x2,      // INTER prediction, non zero motion vector.
    CODE_INTER_NEAREST_MV   = 0x3,      // Use Last Motion vector
    CODE_INTER_NEAR_MV      = 0x4,      // Prior last motion vector
    CODE_USING_GOLDEN       = 0x5,      // 'Golden frame' prediction (no MV).
    CODE_GOLDEN_MV          = 0x6,      // 'Golden frame' prediction plus MV.
    CODE_INTER_FOURMV       = 0x7,      // Inter prediction 4MV per macro block.
    CODE_GOLD_NEAREST_MV    = 0x8,      // Use Last Motion vector
    CODE_GOLD_NEAR_MV       = 0x9,      // Prior last motion vector
    DO_NOT_CODE             = 0x10       // Fake Mode

} CODING_MODE;

typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT32, M);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_INT32, C);

} VP6FW_LINE_EQ;


typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Symbol);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Probability);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32NextIdx);         // pointer to next node
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Branch);          // branch value: 0 or 1

} VP6FW_sVlcCode;


typedef struct
{
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, int, next);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, int, freq);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32NextIdx);         // pointer to next node
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Branch);          // branch value: 0 or 1

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Code);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Symbol);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32Len);

} sortnode;


/*!
******************************************************************************

 This describes the VP6 parser component "Header data", shown in the
 Firmware Memory Layout diagram. This data is required by the VP6 firmware
 and should be supplied by the Host.

******************************************************************************/
typedef struct
{
    VDECFW_sImageBuffer        sPrimary;                       //!< Primary decode buffer base addresses
    VDECFW_sImageBuffer        sAlternate;                     //!< buffer base addresses for alternate output

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FrameSize);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32FirstPartitionBaseAddress);  //!< Used for storing first partition parameters

} VP6FW_sHeaderData;


/*!
******************************************************************************

 This describes an VP6 picture. It is part of the Context data

******************************************************************************/
typedef struct
{
    VDECFW_sImageBuffer sPrimary;                                   //!< Primary (reconstructed) picture buffers
    VDECFW_sImageBuffer sAlternate;                                 //!< Secondary (alternative) picture buffers

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32TransactionId);                          //!< Unique ID for this picture
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8DisplayFlags);                            //!< Flags for this picture for the display process

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8HeldFlags);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8Last);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ui8Golden);

} VP6FW_sPicture;


/*!
******************************************************************************

 This describes the VP6 parser component "Context data", shown in the
 Firmware Memory Layout diagram. This data is the state preserved across
 pictures. It is loaded and saved by the Firmware, but requires the host to
 provide buffer(s) for this.

******************************************************************************/
typedef struct
{
    // Picture reference/reordering management
    VP6FW_sPicture  sGoldenPic;
    VP6FW_sPicture  sLastPic;

    /* scan order */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ScanBands[VP6FW_BLOCK_SIZE]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ModifiedScanOrder[VP6FW_BLOCK_SIZE]);        // built from scan bands

    /* ModeDecisionTree */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, probXmitted[3][2][MAX_MODES]);     // not sent
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, probMode[3][MAX_MODES][MAX_MODES]);  // combines probMode and probModeSame (in probMode[i][j][9])

    /* Ac and Dc Probs */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, AcProbs[PREC_CASES][2][VP6_AC_BANDS][(MAX_ENTROPY_TOKENS-1)]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, DcProbs[2*(MAX_ENTROPY_TOKENS-1)]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, DcNodeContexts[2][DC_TOKEN_CONTEXTS][MAX_ENTROPY_TOKENS-1]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, ZeroRunProbs[ZRL_BANDS][ZERO_RUN_PROB_CASES]);

    /* probabilities */
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, MvShortProbs[2][8]); // combines MvShortProbs and IsMvShortProb (in MvShortProbs[i][7])
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, MvSignProbs[2]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, MvSizeProbs[2][LONG_MV_BITS]);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT8, LastProb[MAX_ENTROPY_TOKENS-1]);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, sortnode, sn[MAX_ENTROPY_TOKENS+MAX_ENTROPY_TOKENS-1]);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32Sort[MAX_ENTROPY_TOKENS]);           // Canonical (probability) sort order for the leaf nodes

    /* Intermediate table for generation of VLC codes from Huff trees */
    VLC_sSymbolCode asVlcCodes[VP6_VLC_MAX_NUM_CODES];
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, aui32HuffProbs[MAX_ENTROPY_TOKENS]);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MbWidth);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32MbHeight);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32VpProfile);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bOldVersion);

    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bUseLoopFilter);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PredictionFilterAlpha);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bAutoSelectPMFlag);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PredictionFilterVarThresh);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_UINT32, ui32PredictionFilterMvSizeThresh);
    IMG_ALIGN_FIELD(VDECFW_SHARE_DEFAULT_ALIGNMENT, IMG_BOOL, bBiCubicOrBiLinearFiltFlag);

} VP6FW_sContextData;


#endif /* _VP6FW_DATA_H_ */
