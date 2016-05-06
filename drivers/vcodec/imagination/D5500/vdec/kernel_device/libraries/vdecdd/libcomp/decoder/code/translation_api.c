/*!
 *****************************************************************************
 *
 * @File       translation_api.c
 * @Title      VDECDD Translation API.
 * @Description    This file contains the VDECDD translation API.
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

#include "translation_api.h"
#include "img_errors.h"
#include "rman_api.h"

#ifndef SYSBRG_BRIDGING
    #include "talmmu_api.h"
#else
    #include "msvdx_ext.h"
    #include "sysmem_utils.h"
#endif
#ifdef SECURE_MEDIA_SUPPORT
    #include "secureapi.h"
#endif

#ifdef HAS_AVS
#include "avsfw_data.h"
#endif /* HAS_AVS */
#ifdef HAS_H264
#include "h264fw_data.h"
#endif /* HAS_H264 */
#ifdef HAS_MPEG4
#include "mpeg4fw_data.h"
#endif /* HAS_MPEG4 */
#ifdef HAS_VP6
#include "vp6fw_data.h"
#endif /* HAS_VP6 */
#ifdef HAS_VP8
#include "vp8fw_data.h"
#endif /* HAS_VP8 */
#ifdef HAS_VC1
#include "vc1fw_data.h"
#endif /* HAS_VC1 */
#ifdef HAS_JPEG
#include "jpegfw_data.h"
#endif /* HAS_JPEG */
#ifdef HAS_MPEG2
#include "mpeg2fw_data.h"
#endif /* HAS_MPEG2 */
#ifdef HAS_REAL
#include "realfw_data.h"
#endif /* HAS_REAL */
#ifdef HAS_HEVC
#include "hevcfw_data.h"
#endif /* HAS_HEVC */

#include "hwctrl_api.h"
#include "report_api.h"

#ifdef VDEC_USE_PVDEC

#include "pvdec_int.h"
#include "interface/deva_fw_msg.h"
#include "hwdefs/pvdec_core_regs.h"
#include "hwdefs/msvdx_cmds.h"
#include "hwdefs/img_video_bus4_mmu_regs.h"
#include "hwdefs/msvdx_vec_regs.h"

#ifdef HAS_HEVC
#include "hwdefs/pvdec_entropy_regs.h"
#include "hwdefs/pvdec_vec_be_regs.h"
#include "hwdefs/pvdec_vec_be_hevc_regs.h"
#endif /* HAS_HEVC */

/* Included from PVDEC firmware. */
#include "source/core/vdec_fw_interface.h"

#else  /* ndef VDEC_USE_PVDEC */

#include "msvdx_vec_reg_io2.h"

#endif /* ndef VDEC_USE_PVDEC */

#define NO_VALUE    0

/* Discontinuity in layout of VEC_VLC_TABLE* registers.
 * Address of VEC_VLC_TABLE_ADDR16 does not immediately follow
 * VEC_VLC_TABLE_ADDR15, see TRM. */
#define VEC_VLC_TABLE_ADDR_PT1_SIZE  16 /* in 32-bit words */
#define VEC_VLC_TABLE_ADDR_DISCONT   (VEC_VLC_TABLE_ADDR_PT1_SIZE * PVDECIO_VLC_IDX_ADDR_PARTS)

/* Imply standard from OperatingMode */
#define CODEC_MODE_JPEG     0x0
#define CODEC_MODE_H264     0x1
#define CODEC_MODE_VC1      0x2
#define CODEC_MODE_MPEG2    0x3
#define CODEC_MODE_MPEG4    0x4
#define CODEC_MODE_AVS      0x5
#define CODEC_MODE_WMV9     0x6
#define CODEC_MODE_MPEG1    0x7
#define CODEC_MODE_REAL8    0x8
#define CODEC_MODE_REAL9    0x9
#define CODEC_MODE_VP6      0xA
#define CODEC_MODE_VP8      0xB
#define CODEC_MODE_HEVC     0xC

/*!
******************************************************************************
 This enum defines values of ENTDEC_BE_MODE field of VEC_ENTDEC_BE_CONTROL
 register and ENTDEC_FE_MODE field of VEC_ENTDEC_FE_CONTROL register.
*****************************************************************************/
typedef enum
{
    VDEC_ENTDEC_MODE_JPEG        = 0x0,    //!< JPEG
    VDEC_ENTDEC_MODE_H264        = 0x1,    //!< H264 (MPEG4/AVC)
    VDEC_ENTDEC_MODE_VC1         = 0x2,    //!< VC1
    VDEC_ENTDEC_MODE_MPEG2       = 0x3,    //!< MPEG2
    VDEC_ENTDEC_MODE_MPEG4       = 0x4,    //!< MPEG4
    VDEC_ENTDEC_MODE_AVS         = 0x5,    //!< AVS
    VDEC_ENTDEC_MODE_WMV9        = 0x6,    //!< WMV9
    VDEC_ENTDEC_MODE_MPEG1       = 0x7,    //!< MPEG1
    VDEC_ENTDEC_MODE_EXT_REAL8   = 0x0,    //!< RealVideo8, with ENTDEC_[BE|FE]_EXTENDED_MODE bit set
    VDEC_ENTDEC_MODE_EXT_REAL9   = 0x1,    //!< RealVideo9, with ENTDEC_[BE|FE]_EXTENDED_MODE bit set
    VDEC_ENTDEC_MODE_EXT_VP6     = 0x2,    //!< VP6, with ENTDEC_[BE|FE]_EXTENDED_MODE bit set
    VDEC_ENTDEC_MODE_EXT_VP8     = 0x3,    //!< VP8, with ENTDEC_[BE|FE]_EXTENDED_MODE bit set
    VDEC_ENTDEC_MODE_EXT_SVC     = 0x4,    //!< SVC, with ENTDEC_[BE|FE]_EXTENDED_MODE bit set
} VDEC_eMsvdxEntDecMode;


/*!
******************************************************************************

 @Function              translation_GetFeControl

 @Description

 Prepare value of VEC_ENTDEC_FE_CONTROL register.

 @Return            IMG_UINT32 : Value of register.

******************************************************************************/
static IMG_UINT32 translation_GetFeControl(
    IMG_UINT8                ui8FeMode,
    IMG_UINT8                ui8FeProfile
)
{
    IMG_UINT32 ui32Reg = 0;

    REGIO_WRITE_FIELD_LITE(ui32Reg, MSVDX_VEC, CR_VEC_ENTDEC_FE_CONTROL, ENTDEC_FE_PROFILE, ui8FeProfile);
    REGIO_WRITE_FIELD_LITE(ui32Reg, MSVDX_VEC, CR_VEC_ENTDEC_FE_CONTROL, ENTDEC_FE_MODE, ui8FeMode);

    return ui32Reg;
}

/*!
******************************************************************************

 @Function              translation_GetBeControl

 @Description

 Prepare value of VEC_ENTDEC_BE_CONTROL register.

 @Return            IMG_UINT32 : Value of register.

******************************************************************************/
static IMG_UINT32 translation_GetBeControl(
    IMG_UINT8                ui8BeMode,
    IMG_UINT8                ui8BeProfile
)
{
    IMG_UINT32 ui32Reg = 0;

    REGIO_WRITE_FIELD(ui32Reg, MSVDX_VEC, CR_VEC_ENTDEC_BE_CONTROL, ENTDEC_BE_PROFILE, ui8BeProfile);
    REGIO_WRITE_FIELD(ui32Reg, MSVDX_VEC, CR_VEC_ENTDEC_BE_CONTROL, ENTDEC_BE_MODE, ui8BeMode);

    return ui32Reg;
}

/*!
******************************************************************************

 @Function              translation_SetBuffer

 @Description

 This has all that it needs to translate a Stream Unit for a picture into a transaction.

 @Return            IMG_RESULT :

******************************************************************************/
static IMG_RESULT translation_SetBuffer(
    VDECDD_sDdPictBuf      * psPictBuf,
    VDECFW_sImageBuffer    * psBuffer
)
{
    IMG_UINT32 i;

    for (i = 0; i < VDEC_PLANE_MAX; i++)
    {
        psBuffer->aui32ByteOffset[i] = (IMG_UINT32)GET_HOST_ADDR(&psPictBuf->psPictBuf->sDdBufInfo, IMG_TRUE) +
                                            psPictBuf->sRendInfo.asPlaneInfo[i].ui32Offset;
    }

    return IMG_SUCCESS;
}

#ifdef HAS_AVS
/*!
******************************************************************************

 @Function              translation_AVSHeader

******************************************************************************/
static IMG_RESULT translation_AVSHeader(
    const BSPP_sSequHdrInfo  * psSeq,
    VDECDD_sPicture          * psPicture,
    DECODER_sDecPict         * psDecPict,
    AVSFW_sHeaderData        * psHeaderData
)
{
    const VDEC_sAVSSequHdrInfo * psAvsSequHdrInfo = &psSeq->sAVSSequHdrInfo;

    /* Set current sequence id */
    psHeaderData->ui16HorizontalSize = psSeq->sComSequHdrInfo.sOrigDisplayRegion.ui32Width;
    psHeaderData->ui16VerticalSize   = psSeq->sComSequHdrInfo.sOrigDisplayRegion.ui32Height;
    psHeaderData->bLowDelay          = psAvsSequHdrInfo->bLowDelay;

    psHeaderData->ui32MbParamsBaseAddress = psPicture->psPictResInt->psMBParamBuf == IMG_NULL ?
                0 : (IMG_UINT32)GET_HOST_ADDR(&psPicture->psPictResInt->psMBParamBuf->sDdBufInfo, IMG_TRUE);

    /* Set up buffer config */
    translation_SetBuffer(psDecPict->psReconPict, &psHeaderData->sPrimary);

    if (psDecPict->psAltPict)
    {
        translation_SetBuffer(psDecPict->psAltPict, &psHeaderData->sAlternate);
    }

    return IMG_SUCCESS;
}
#endif /* HAS_AVS */

#ifdef HAS_MPEG4
/*!
******************************************************************************

 @Function              translation_MPEG4Header

******************************************************************************/
static IMG_RESULT translation_MPEG4Header(
    const BSPP_sSequHdrInfo  * psSeq,
    VDECDD_sPicture          * psPicture,
    DECODER_sDecPict         * psDecPict,
    MPEG4FW_sHeaderData      * psHeaderData,
    VDEC_sStrConfigData      * psStrConfigData
)
{
    IMG_UINT32 ui32MaxHeldPicNum, ui32Result;

    psHeaderData->ui32Profile = psSeq->sComSequHdrInfo.ui32CodecProfile;

    ui32Result = VDECDDUTILS_RefPictGetMaxNum(psStrConfigData, &psSeq->sComSequHdrInfo, &ui32MaxHeldPicNum);
    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        return ui32Result;
    }
    psHeaderData->bBPictures = (ui32MaxHeldPicNum == 1) ? IMG_FALSE : IMG_TRUE;

    // Obtain the MB parameter address from the stream unit.
    psHeaderData->ui32MbParamsBaseAddress = psPicture->psPictResInt->psMBParamBuf == IMG_NULL ?
            0 : (IMG_UINT32)GET_HOST_ADDR(&psPicture->psPictResInt->psMBParamBuf->sDdBufInfo, IMG_TRUE);

    // Obtain the DP address from the stream unit.
    psHeaderData->ui32DataPartition0BaseAddress = psPicture->psPictResInt->psDP0Buf == IMG_NULL ?
            0 : (IMG_UINT32)GET_HOST_ADDR(&psPicture->psPictResInt->psDP0Buf->sDdBufInfo, IMG_TRUE);

    psHeaderData->ui32DataPartition1BaseAddress = psPicture->psPictResInt->psDP1Buf == IMG_NULL ?
            0 : (IMG_UINT32)GET_HOST_ADDR(&psPicture->psPictResInt->psDP1Buf->sDdBufInfo, IMG_TRUE);

    if (psDecPict->psPrevPictDecRes)
    {
        psHeaderData->ui32FEParserVLRBufferLoad = GET_HOST_ADDR(&psDecPict->psPrevPictDecRes->sMPEG4FEVLRBackup, IMG_TRUE);
    }
    else
    {
        // If no previous context exists, use the current context which should be all zeros.
        psHeaderData->ui32FEParserVLRBufferLoad = GET_HOST_ADDR(&psDecPict->psCurPictDecRes->sMPEG4FEVLRBackup, IMG_TRUE);
    }
//    UPDATE_DEVICE(psHeaderData->ui32FEParserVLRBufferLoad, IMG_TRUE);

    psHeaderData->ui32FEParserVLRBufferSave = GET_HOST_ADDR(&psDecPict->psCurPictDecRes->sMPEG4FEVLRBackup, IMG_TRUE);

    translation_SetBuffer(psDecPict->psReconPict, &psHeaderData->sPrimary);

    if (psDecPict->psAltPict)
    {
        translation_SetBuffer(psDecPict->psAltPict, &psHeaderData->sAlternate);
    }

    return IMG_SUCCESS;
}
#endif /* HAS_MPEG4 */


#ifdef HAS_VP6
/*!
******************************************************************************

 @Function              translation_VP6Header

******************************************************************************/
static IMG_RESULT translation_VP6Header(
    const BSPP_sSequHdrInfo  * psSeq,
    VDECDD_sPicture          * psPicture,
    DECODER_sDecPict         * psDecPict,
    VP6FW_sHeaderData        * psHeaderData,
    VDEC_sStrConfigData      * psStrConfigData
)
{
    VDECDD_sSeqResInt * psSeqResInt = psPicture->psPictResInt->psSeqResInt;
    psHeaderData->ui32FrameSize = psDecPict->psPictHdrInfo->ui32PicDataSize;

    // Obtain the First Partition Buffer address from the stream unit.
    psHeaderData->ui32FirstPartitionBaseAddress = (psSeqResInt->psPicBuffer == IMG_NULL) ?
       0 : ((IMG_UINT32)psSeqResInt->psPicBuffer->sDdBufInfo.ui32DevVirt);

    translation_SetBuffer(psDecPict->psReconPict, &psHeaderData->sPrimary);

    if (psDecPict->psAltPict)
    {
        translation_SetBuffer(psDecPict->psAltPict, &psHeaderData->sAlternate);
    }
    return IMG_SUCCESS;
}
#endif /* HAS_VP6 */

#ifdef HAS_VP8
/*!
******************************************************************************

 @Function              translation_VP8Header

******************************************************************************/
static IMG_RESULT translation_VP8Header(
    const BSPP_sSequHdrInfo  * psSeq,
    VDECDD_sPicture          * psPicture,
    DECODER_sDecPict         * psDecPict,
    VP8FW_sHeaderData        * psHeaderData,
    VDEC_sStrConfigData      * psStrConfigData
)
{
    DECODER_sDecPictSeg * psDecPictSeg;
    BSPP_sBitStrSeg * psBitStrSeg;
    VDECDD_sSeqResInt * psSeqResInt = psPicture->psPictResInt->psSeqResInt;

    //Calculate Frame Length
    psHeaderData->ui32FrameLength = psDecPict->psPictHdrInfo->ui32PicDataSize;

    psDecPictSeg = LST_last(&psDecPict->sDecPictSegList);
    psBitStrSeg = psDecPictSeg->psBitStrSeg;

    //Padding the buffer, assuming only 1 buffer in the list for VP8
    //Buffers should be less than 64Kb (1 DMA only allowed) and already
    //padded to 512bytes.
    //Multiple segments (but only if consecutive in memory) should be
    //possible but it's not supported here yet.
    if(psHeaderData->ui32FrameLength < 0x200)
    {
        psBitStrSeg->ui32DataSize = 0x200;
    }

    //Buffers point inside the BE buffers as the following
    //MB_FLAGS_BUFFER_OFFSET          (0)
    //FIRST_PARTITION_BUFFER_OFFSET   (MB_FLAGS_BUFFER_OFFSET_OFFSET+MB_FLAGS_BUFFER_SIZE)
    //CURRENT_PICTURE_BUFFER_OFFSET   (FIRST_PARTITION_BUFFER_OFFSET+FIRST_PARTITION_BUFFER_SIZE)
    //SEGMENTID_BUFFER_OFFSET         (CURRENT_PICTURE_BUFFER_OFFSET+CURRENT_PICTURE_BUFFER_SIZE)

#ifdef VDEC_USE_PVDEC
   psHeaderData->ui32SecondPartitionProbBaseAddress = (psSeqResInt->pasSecondPartitionProb[psDecPict->ui8Pipe-1] == IMG_NULL) ?
       0 : ((IMG_UINT32)psSeqResInt->pasSecondPartitionProb[psDecPict->ui8Pipe-1]->sDdBufInfo.ui32DevVirt);
#endif

    // Obtain the MB Flags Buffer address from the stream unit
   psHeaderData->ui32MbFlagsBaseAddress = (psSeqResInt->psMbFlagsBuffer == IMG_NULL) ?
       0 : ((IMG_UINT32)psSeqResInt->psMbFlagsBuffer->sDdBufInfo.ui32DevVirt);

    // Obtain the SegmentID Buffer address from the stream unit.
    psHeaderData->ui32SegmentIDBaseAddress = (psSeqResInt->psSegmentIDBuffer == IMG_NULL) ?
       0 : ((IMG_UINT32)psSeqResInt->psSegmentIDBuffer->sDdBufInfo.ui32DevVirt);

    // Obtain the First Partition Buffer address from the stream unit.
    psHeaderData->ui32FirstPartitionBaseAddress = (psSeqResInt->psFirstPartitionBuffer == IMG_NULL) ?
       0 : ((IMG_UINT32)psSeqResInt->psFirstPartitionBuffer->sDdBufInfo.ui32DevVirt);

    // Obtain the Current Picture Buffer address from the stream unit.
    psHeaderData->ui32CurrentPictureBaseAddress = (psSeqResInt->psCurrentPictureBuffer == IMG_NULL) ?
       0 : ((IMG_UINT32)psSeqResInt->psCurrentPictureBuffer->sDdBufInfo.ui32DevVirt);

    translation_SetBuffer(psDecPict->psReconPict, &psHeaderData->sPrimary);

    if (psDecPict->psAltPict)
    {
        translation_SetBuffer(psDecPict->psAltPict, &psHeaderData->sAlternate);
    }
    return IMG_SUCCESS;
}
#endif /* HAS_VP8 */

#ifdef HAS_VC1
/*!
******************************************************************************

 @Function              translation_VC1Header

******************************************************************************/
static IMG_RESULT translation_VC1Header(
    const BSPP_sSequHdrInfo  * psSeq,
    VDECDD_sPicture          * psPicture,
    DECODER_sDecPict         * psDecPict,
    VC1FW_sHeaderData        * psHeaderData,
    VDEC_sStrConfigData      * psStrConfigData
)
{
    IMG_UINT32 ui32MsvdxProfile = 0;
    VC1FW_sDdSequenceSPS * psDdSPS = &psHeaderData->sDdSequenceSPS;
    VDECDD_sSeqResInt * psSeqResInt = psPicture->psPictResInt->psSeqResInt;

    psHeaderData->ui16CodedWidth = psDecPict->psPictHdrInfo->sCodedFrameSize.ui32Width;
    psHeaderData->ui16CodedHeight = psDecPict->psPictHdrInfo->sCodedFrameSize.ui32Height;

    psHeaderData->ui32FrameSize = psDecPict->psPictHdrInfo->ui32PicDataSize;
    psHeaderData->bEmulationPrevention = psDecPict->psPictHdrInfo->bEmulationPrevention;

    // Derive SPS parameters
    if (psSeq->sComSequHdrInfo.ui32CodecProfile == VC1_PROFILE_SIMPLE)
    {
        ui32MsvdxProfile = 0;
    }
    else if (psSeq->sComSequHdrInfo.ui32CodecProfile == VC1_PROFILE_MAIN)
    {
        ui32MsvdxProfile = 1;
    }
    else if (psSeq->sComSequHdrInfo.ui32CodecProfile == VC1_PROFILE_ADVANCED)
    {
        ui32MsvdxProfile = 2;
    }

    psDdSPS->bAdvancedProfile = (psSeq->sComSequHdrInfo.ui32CodecProfile == VC1_PROFILE_ADVANCED);

    /* CR_VEC_ENTDEC_FE_CONTROL */
    psDdSPS->ui32RegEntdecFEControl = translation_GetFeControl(VDEC_ENTDEC_MODE_VC1, ui32MsvdxProfile);

    /* CR_VEC_ENTDEC_BE_CONTROL */
    psDdSPS->ui32RegEntdecBEControl = translation_GetBeControl(VDEC_ENTDEC_MODE_VC1, ui32MsvdxProfile);

    //Buffers point inside the BE buffers as the following
    //MB_FLAGS_BUFFER_OFFSET          (0)

    // Obtain VLC Index Table Info
    psHeaderData->ui32VlcIndexSize = (psDecPict->psVlcIdxTableBufInfo->ui32BufSize / (sizeof(IMG_UINT16)*3));

    // Obtain the MB parameter address from the stream unit.
    if (psPicture->psPictResInt->psMBParamBuf)
    {
    psHeaderData->ui32MbParamsSize = psPicture->psPictResInt->psMBParamBuf->sDdBufInfo.ui32BufSize;
        psHeaderData->ui32MbParamsBaseAddress = (IMG_UINT32)GET_HOST_ADDR(&psPicture->psPictResInt->psMBParamBuf->sDdBufInfo, IMG_TRUE);
    }
    else
    {
        psHeaderData->ui32MbParamsSize = 0;
        psHeaderData->ui32MbParamsBaseAddress = 0;
    }

    //AuxMSB is directly set in translation_SetReconPictCmds. It would be useless to pass it in the header and set it in the parser
    //because anyway it would be written in the common commands.
    // Obtain the AuxMSB buffer address from the stream unit.
    //psHeaderData->ui32AuxMSBParamsBaseAddress = psPicture->psPictResInt->psMBParamBuf == IMG_NULL ?
    //    0 : ((IMG_UINT32)(GET_HOST_ADDR(psDecPict->psBEBufInfo, IMG_TRUE))+VC1_MSB_BUFFER_OFFSET);

    //Obtain Bitplane 0 address address from the stream unit.
    psHeaderData->aui32BitPlanesBufferBaseAddress[0] = (psSeqResInt->pasBitPlaneBuffers[0] == IMG_NULL) ?
       0 : ((IMG_UINT32)psSeqResInt->pasBitPlaneBuffers[0]->sDdBufInfo.ui32DevVirt);

    //Obtain Bitplane 1 address address from the stream unit.
    psHeaderData->aui32BitPlanesBufferBaseAddress[1] = (psSeqResInt->pasBitPlaneBuffers[1] == IMG_NULL) ?
       0 : ((IMG_UINT32)psSeqResInt->pasBitPlaneBuffers[1]->sDdBufInfo.ui32DevVirt);

    //Obtain Bitplane 2 address address from the stream unit.
    psHeaderData->aui32BitPlanesBufferBaseAddress[2] = (psSeqResInt->pasBitPlaneBuffers[2] == IMG_NULL) ?
       0 : ((IMG_UINT32)psSeqResInt->pasBitPlaneBuffers[2]->sDdBufInfo.ui32DevVirt);

    translation_SetBuffer(psDecPict->psReconPict, &psHeaderData->sPrimary);

    if (psDecPict->psAltPict)
    {
        translation_SetBuffer(psDecPict->psAltPict, &psHeaderData->sAlternate);
    }

    return IMG_SUCCESS;
}
#endif /* HAS_VC1 */

#ifdef HAS_HEVC
/*!
******************************************************************************

 @Function              translation_HEVCHeader

******************************************************************************/
static IMG_RESULT translation_HEVCHeader(
    VDECDD_sPicture * psPicture,
    DECODER_sDecPict * psDecPict,
    HEVCFW_sHeaderData * psHeaderData
)
{
    translation_SetBuffer(psDecPict->psReconPict, &psHeaderData->sPrimary);

    if (psDecPict->psAltPict)
    {
        translation_SetBuffer(psDecPict->psAltPict, &psHeaderData->sAlternate);
    }

    IMG_ASSERT(psPicture != IMG_NULL);
    IMG_ASSERT(psPicture->psPictResInt != IMG_NULL);
    IMG_ASSERT(psPicture->psPictResInt->psMBParamBuf != IMG_NULL);
    psHeaderData->ui32TemporalOutAddr = (IMG_UINT32) GET_HOST_ADDR(
            &psPicture->psPictResInt->psMBParamBuf->sDdBufInfo, IMG_TRUE);

    return IMG_SUCCESS;
}
#endif /* HAS_HEVC */

#ifdef HAS_H264
/*!
******************************************************************************

 @Function              translation_H264Header

******************************************************************************/
static IMG_RESULT translation_H264Header(
    VDECDD_sPicture          * psPicture,
    DECODER_sDecPict         * psDecPict,
    H264FW_sHeaderData       * psHeaderData,
    VDEC_sStrConfigData      * psStrConfigData
)
{
    psHeaderData->bTwoPassFlag = psDecPict->psPictHdrInfo->bDiscontinuousMbs;
    psHeaderData->bDisableMvc = psStrConfigData->bDisableMvc;

    // Obtain the MB parameter address from the stream unit.
    if (psPicture->psPictResInt->psMBParamBuf)
    {
        psHeaderData->ui32MbParamsBaseAddress = (IMG_UINT32)GET_HOST_ADDR(&psPicture->psPictResInt->psMBParamBuf->sDdBufInfo, IMG_TRUE);
#ifdef ENABLE_SEPARATE_COLOUR_PLANES
        psHeaderData->ui32MbParamsSizePerPlane = psPicture->psPictResInt->psMBParamBuf->sDdBufInfo.ui32BufSize/3;
#endif
    }
    else
    {
        psHeaderData->ui32MbParamsBaseAddress = 0;
#ifdef ENABLE_SEPARATE_COLOUR_PLANES
        psHeaderData->ui32MbParamsSizePerPlane = 0;
#endif
    }

    UPDATE_DEVICE((&psDecPict->psCurPictDecRes->sH264SgmBuf), IMG_TRUE);

    psHeaderData->ui32SliceGroupMapBaseAddress = (IMG_UINT32)GET_HOST_ADDR(&psDecPict->psCurPictDecRes->sH264SgmBuf, IMG_TRUE);

#ifdef __FAKE_MTX_INTERFACE__
    psHeaderData->ui32MBBufInfo = &psPicture->psPictResInt->psMBParamBuf->sDdBufInfo;
#endif

    translation_SetBuffer(psDecPict->psReconPict, &psHeaderData->sPrimary);

    if (psDecPict->psAltPict)
    {
        translation_SetBuffer(psDecPict->psAltPict, &psHeaderData->sAlternate);
    }

    // Signal whether we have PPS for the second field. 
    if(psPicture->sDecPictAuxInfo.ui32SecondPPSId == BSPP_INVALID)
    {
        psHeaderData->bSecondPPS = IMG_FALSE;
    }
    else
    {
        psHeaderData->bSecondPPS = IMG_TRUE;
    }

    return IMG_SUCCESS;
}
#endif /* HAS_H264 */

#ifdef HAS_JPEG

/*!
******************************************************************************

 @Function              translation_JPEGHeader

******************************************************************************/
static IMG_RESULT translation_JPEGHeader(
    const BSPP_sSequHdrInfo              * psSeq,
    const DECODER_sDecPict               * psDecPict,
    const BSPP_sPictHdrInfo              * psPictHdrInfo,
    JPEGFW_sHeaderData                   * psHeaderData
)
{
    IMG_UINT32 ui32i;

    //psDecPict->psPictHdrInfo->sJPEGPictHdrInfo.sSOFComp;
    /* Output picture planes addresses */
    for (ui32i = 0; ui32i < psSeq->sComSequHdrInfo.sPixelInfo.ui32NoPlanes; ui32i++)
    {
        psHeaderData->aui32PlaneOffsets[ui32i] = (IMG_UINT32)GET_HOST_ADDR(&psDecPict->psReconPict->psPictBuf->sDdBufInfo, IMG_TRUE) +
            psDecPict->psReconPict->sRendInfo.asPlaneInfo[ui32i].ui32Offset;
    }

    /* copy the expected SOS fields number */
    psHeaderData->ui8HdrSOSCount = psPictHdrInfo->ui8SOSCount;

    translation_SetBuffer(psDecPict->psReconPict, &psHeaderData->sPrimary);

    return IMG_SUCCESS;
}
#endif /* HAS_JPEG */

#ifdef HAS_MPEG2

/*!
******************************************************************************

 @Function              translation_MPEG2Header

******************************************************************************/
static IMG_RESULT translation_MPEG2Header(
    const BSPP_sSequHdrInfo  * psSeq,
    VDECDD_sPicture          * psPicture,
    DECODER_sDecPict         * psDecPict,
    MPEG2FW_sHeaderData      * psHeaderData,
    VDEC_sStrConfigData      * psStrConfigData,
    IMG_UINT32               * pui32PictCmds
)
{
    /* Set up buffer config */
    translation_SetBuffer(psDecPict->psReconPict, &psHeaderData->sPrimary);

    if (psDecPict->psAltPict)
    {
        translation_SetBuffer(psDecPict->psAltPict, &psHeaderData->sAlternate);
    }

#if 1
    {
        IMG_UINT32 ui32CodedPicHeight;
        IMG_UINT32 ui32HeightMBs;

        /* Set up width and height in macroblock units  */
        if (psSeq->sComSequHdrInfo.bInterlacedFrames)
        {
            ui32HeightMBs = ((psSeq->sComSequHdrInfo.sMaxFrameSize.ui32Height + 31) >> 5) * 2;
        }
        else
        {
            ui32HeightMBs = (psSeq->sComSequHdrInfo.sMaxFrameSize.ui32Height + 15) >> 4;
        }

        /* Update coded picture size in array of common commands */
        ui32CodedPicHeight = ui32HeightMBs * 16 - 1;
        pui32PictCmds[VDECFW_CMD_CODED_PICTURE] |= VXD_GetCodedPicSize(0, ui32CodedPicHeight);
    }
#endif

    return IMG_SUCCESS;
}
#endif /* HAS_MPEG2 */

#ifdef HAS_REAL
/*!
******************************************************************************

 @Function              translation_RealHeader

******************************************************************************/
static IMG_RESULT translation_RealHeader(
    const BSPP_sSequHdrInfo  * psSeqHdr,
    const BSPP_sPictHdrInfo  * psPictHdr,
    VDECDD_sPicture          * psPicture,
    DECODER_sDecPict         * psDecPict,
    REALFW_sHeaderData       * psHeaderData
)
{
    IMG_MEMCPY (psHeaderData->sPicHdrInfo.aui32FragmentSize, psPictHdr->sRealExtraPictHdrInfo.aui32FragmentSize, sizeof (psHeaderData->sPicHdrInfo.aui32FragmentSize));
    psHeaderData->sPicHdrInfo.ui32NumFragments  =   psPictHdr->sRealExtraPictHdrInfo.ui32NumOfFragments;

    // Obtain the MB parameter address from the stream unit.
    psHeaderData->ui32MbParamsBaseAddress = psPicture->psPictResInt->psMBParamBuf == IMG_NULL ?
            0 : (IMG_UINT32)GET_HOST_ADDR(&psPicture->psPictResInt->psMBParamBuf->sDdBufInfo, IMG_TRUE);

    translation_SetBuffer(psDecPict->psReconPict, &psHeaderData->sPrimary);

    if (psDecPict->psAltPict)
    {
        translation_SetBuffer(psDecPict->psAltPict, &psHeaderData->sAlternate);
    }

    return IMG_SUCCESS;
}


#ifndef VDEC_USE_PVDEC
/*!
******************************************************************************

 @Function              translation_RealFragStartSegmentsCreate

******************************************************************************/
static IMG_RESULT translation_RealFragStartSegmentsCreate(
    const BSPP_sPictHdrInfo   * psPictHdrInfo,
    LST_T                     * psBitStrSegList,
    LST_T                     * psDecPictSegList
)
{
    IMG_INT32                   i = 0;
    IMG_UINT32                  ui32CurrOffsetInBuffer = 0;
    IMG_UINT32                  ui32PrevDataRemainingInBuffer = 0;
    IMG_UINT32                  ui32CurrDataRemainingInBuffer = 0;
    IMG_UINT32                  ui32SizeOfPrefixRequired = 0;
    IMG_UINT32                  ui32AddedSegmentsCounter = 0;

    DECODER_sDecPictSeg       * apsFragDecPictSeg[REALFW_MAX_FRAGMENTS+MAX_PICS_IN_SYSTEM]; // Array of wrapper elements
    BSPP_sBitStrSeg         * apsFragBitStrSeg[REALFW_MAX_FRAGMENTS+MAX_PICS_IN_SYSTEM];  // Array of bitstream segment elements

    BSPP_sBitStrSeg         * psBitStrSeg = (BSPP_sBitStrSeg *)LST_first(psBitStrSegList);

    IMG_ASSERT(psBitStrSeg != IMG_NULL);
    if (psBitStrSeg == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    ui32PrevDataRemainingInBuffer = psBitStrSeg->ui32DataSize;  // Before counting the Fragment Indeces in actual buffer
    if (psBitStrSeg->ui32DataSize > (1 + psPictHdrInfo->sRealExtraPictHdrInfo.ui32NumOfFragments * 8))  // Fragment Indeces are fully in the buffer with extra data too
    {
        ui32CurrOffsetInBuffer = psBitStrSeg->ui32DataByteOffset + (1 + psPictHdrInfo->sRealExtraPictHdrInfo.ui32NumOfFragments * 8);   // Offset after Fragment Indeces in actual buffer
        ui32CurrDataRemainingInBuffer = psBitStrSeg->ui32DataSize - (1 + psPictHdrInfo->sRealExtraPictHdrInfo.ui32NumOfFragments * 8);  // After counting the Fragment Indeces in actual buffer
    }
    else    // Skip to next buffer because there not fragment data in this
    {
        psBitStrSeg = LST_next(psBitStrSeg);
        IMG_ASSERT(psBitStrSeg != IMG_NULL);
        if (psBitStrSeg == IMG_NULL)
        {
            return IMG_ERROR_INVALID_PARAMETERS;
        }
        ui32CurrOffsetInBuffer = psBitStrSeg->ui32DataByteOffset + ((1 + psPictHdrInfo->sRealExtraPictHdrInfo.ui32NumOfFragments * 8) - ui32PrevDataRemainingInBuffer);   // Offset after Fragment Indeces in actual buffer (the PART OF THEM)
        ui32CurrDataRemainingInBuffer = psBitStrSeg->ui32DataSize - ((1 + psPictHdrInfo->sRealExtraPictHdrInfo.ui32NumOfFragments * 8) - ui32PrevDataRemainingInBuffer);  // After counting the Fragment Indeces in actual buffer (the PART OF THEM)
    }

    // Now we have skipped the Fragment Indices
    for (i=0; i<(IMG_INT32)psPictHdrInfo->sRealExtraPictHdrInfo.ui32NumOfFragments; i++)
    {
        // Calculate how much data we need to send from the fragment
        ui32SizeOfPrefixRequired =
            (psPictHdrInfo->sRealExtraPictHdrInfo.aui32FragmentSize[i] > REALFW_NUM_START_BYTES_COPIED) ?
            REALFW_NUM_START_BYTES_COPIED :
            psPictHdrInfo->sRealExtraPictHdrInfo.aui32FragmentSize[i];

        IMG_ASSERT(ui32AddedSegmentsCounter < REALFW_MAX_FRAGMENTS+MAX_PICS_IN_SYSTEM);
        if (ui32AddedSegmentsCounter >= REALFW_MAX_FRAGMENTS+MAX_PICS_IN_SYSTEM)
        {
            return IMG_ERROR_INVALID_PARAMETERS;
        }
        apsFragBitStrSeg[ui32AddedSegmentsCounter] = (BSPP_sBitStrSeg *)IMG_MALLOC(sizeof(BSPP_sBitStrSeg));
        IMG_ASSERT(apsFragBitStrSeg[ui32AddedSegmentsCounter] != IMG_NULL);
        if (apsFragBitStrSeg[ui32AddedSegmentsCounter] == IMG_NULL)
        {
            return IMG_ERROR_MALLOC_FAILED;
        }
        IMG_MEMCPY(apsFragBitStrSeg[ui32AddedSegmentsCounter], psBitStrSeg, sizeof(BSPP_sBitStrSeg));

        apsFragBitStrSeg[ui32AddedSegmentsCounter]->ui32DataByteOffset = ui32CurrOffsetInBuffer;
        if (ui32SizeOfPrefixRequired <= ui32CurrDataRemainingInBuffer)
        {
            apsFragBitStrSeg[ui32AddedSegmentsCounter]->ui32DataSize = ui32SizeOfPrefixRequired;
            ui32CurrOffsetInBuffer += ui32SizeOfPrefixRequired;
            ui32CurrDataRemainingInBuffer -= ui32SizeOfPrefixRequired;
        }
        else
        {
            ui32PrevDataRemainingInBuffer = ui32CurrDataRemainingInBuffer;
            apsFragBitStrSeg[ui32AddedSegmentsCounter]->ui32DataSize = ui32PrevDataRemainingInBuffer;
            // We need an extra segment
            ui32AddedSegmentsCounter++;
            psBitStrSeg = LST_next(psBitStrSeg);
            IMG_ASSERT(psBitStrSeg != IMG_NULL);
            if (psBitStrSeg == IMG_NULL)
            {
                return IMG_ERROR_INVALID_PARAMETERS;
            }

            IMG_ASSERT(ui32AddedSegmentsCounter < REALFW_MAX_FRAGMENTS+MAX_PICS_IN_SYSTEM);
            if (ui32AddedSegmentsCounter >= REALFW_MAX_FRAGMENTS+MAX_PICS_IN_SYSTEM)
            {
                return IMG_ERROR_INVALID_PARAMETERS;
            }
            apsFragBitStrSeg[ui32AddedSegmentsCounter] = (BSPP_sBitStrSeg *)IMG_MALLOC(sizeof(BSPP_sBitStrSeg));
            IMG_ASSERT(apsFragBitStrSeg[ui32AddedSegmentsCounter] != IMG_NULL);
            if (apsFragBitStrSeg[ui32AddedSegmentsCounter] == IMG_NULL)
            {
                return IMG_ERROR_MALLOC_FAILED;
            }
            IMG_MEMCPY(apsFragBitStrSeg[ui32AddedSegmentsCounter], psBitStrSeg, sizeof(BSPP_sBitStrSeg));

            apsFragBitStrSeg[ui32AddedSegmentsCounter]->ui32DataByteOffset = psBitStrSeg->ui32DataByteOffset + (ui32SizeOfPrefixRequired - ui32PrevDataRemainingInBuffer);
            apsFragBitStrSeg[ui32AddedSegmentsCounter]->ui32DataSize = ui32SizeOfPrefixRequired - ui32PrevDataRemainingInBuffer;
            ui32CurrOffsetInBuffer = psBitStrSeg->ui32DataByteOffset + (ui32SizeOfPrefixRequired - ui32PrevDataRemainingInBuffer);
            ui32CurrDataRemainingInBuffer = psBitStrSeg->ui32DataSize - (ui32SizeOfPrefixRequired - ui32PrevDataRemainingInBuffer);
        }
        ui32AddedSegmentsCounter++;

        if ((psPictHdrInfo->sRealExtraPictHdrInfo.aui32FragmentSize[i] - ui32SizeOfPrefixRequired) < ui32CurrDataRemainingInBuffer)
        {
            ui32CurrOffsetInBuffer += (psPictHdrInfo->sRealExtraPictHdrInfo.aui32FragmentSize[i] - ui32SizeOfPrefixRequired);
            ui32CurrDataRemainingInBuffer -= (psPictHdrInfo->sRealExtraPictHdrInfo.aui32FragmentSize[i] - ui32SizeOfPrefixRequired);
        }
        else
        {
            IMG_UINT32 ui32RemFragmentData = (psPictHdrInfo->sRealExtraPictHdrInfo.aui32FragmentSize[i] - ui32SizeOfPrefixRequired) - ui32CurrDataRemainingInBuffer;
            while(i < (IMG_INT32)psPictHdrInfo->sRealExtraPictHdrInfo.ui32NumOfFragments - 1) // Do not do anything else if this is the last segment
            {
                psBitStrSeg = LST_next(psBitStrSeg);
                IMG_ASSERT(psBitStrSeg != IMG_NULL);
                if (psBitStrSeg == IMG_NULL)
                {
                    return IMG_ERROR_INVALID_PARAMETERS;
                }
                if (ui32RemFragmentData < psBitStrSeg->ui32DataSize)
                {
                    break;
                }
                else
                {
                    ui32RemFragmentData -= psBitStrSeg->ui32DataSize;
                }
            }
            ui32CurrOffsetInBuffer = psBitStrSeg->ui32DataByteOffset + ui32RemFragmentData;
            ui32CurrDataRemainingInBuffer = psBitStrSeg->ui32DataSize - ui32RemFragmentData;
        }
    }

    // Now "apsFragBitStrSeg[]" contains all the segments we need to send, we need to push them in the list in the correct order:
    // 1) before the actual bitstream segment 2) with correct order (first at the head)
    // so, we push to the head starting from the end of the array with the segments
    // The number of them is "ui32AddedSegmentsCounter"
    for (i = ui32AddedSegmentsCounter - 1; i >= 0; i--)
    {
        //LST_addHead(psBitStrSegList, apsFragBitStrSeg[i]);  // This SHOULD NOT be added into the bitstream segment list, it will create problem with buffer recycling
        apsFragDecPictSeg[i] = (DECODER_sDecPictSeg *)IMG_MALLOC(sizeof(DECODER_sDecPictSeg));
        IMG_ASSERT(apsFragDecPictSeg[i] != IMG_NULL);
        if (apsFragDecPictSeg[i] == IMG_NULL)
        {
            return IMG_ERROR_MALLOC_FAILED;
        }
        apsFragDecPictSeg[i]->psBitStrSeg = apsFragBitStrSeg[i];    // connect the two lists
        LST_addHead(psDecPictSegList, apsFragDecPictSeg[i]);        // Add the wrapper element into the wrapper list
    }

    return IMG_SUCCESS;
}
#endif /* ndef VDEC_USE_PVDEC */
#endif /* HAS_REAL */

/*!
******************************************************************************

 @Function          translation_GetCodec

 @Description

 This function translates host video standard enum (VDEC_eVidStd) into
 firmware video standard enum (VDECFW_eCodecType);

 @Input     eVidStd             : Video standard in host format, to be
                                  translated.

 @Output    peCodec             : Translated video standard in firmware
                                  format.

 @Return    IMG_RESULT          : This function returns either IMG_SUCCESS or
                                  an error code.

******************************************************************************/
static IMG_RESULT translation_GetCodec(
    VDEC_eVidStd        eVidStd,
    VDECFW_eCodecType * peCodec
)
{
    VDECFW_eCodecType eCodec = VDEC_CODEC_NONE;
    IMG_RESULT ui32Result = IMG_ERROR_NOT_SUPPORTED;

    // Translate from video standard to firmware codec.
    switch (eVidStd)
    {
#ifdef HAS_MPEG2
    case VDEC_STD_MPEG2:
        eCodec = VDECFW_CODEC_MPEG2;
        ui32Result = IMG_SUCCESS;
        break;
#endif /* HAS_MPEG2 */
#ifdef HAS_MPEG4
    case VDEC_STD_MPEG4:
    case VDEC_STD_H263:
    case VDEC_STD_SORENSON:
        eCodec = VDECFW_CODEC_MPEG4;
        ui32Result = IMG_SUCCESS;
        break;
#endif /* HAS_MPEG4 */
#ifdef HAS_H264
    case VDEC_STD_H264:
        eCodec = VDECFW_CODEC_H264;
        ui32Result = IMG_SUCCESS;
        break;
#endif /* HAS_H264 */
#ifdef HAS_HEVC
    case VDEC_STD_HEVC:
        eCodec = VDECFW_CODEC_HEVC;
        ui32Result = IMG_SUCCESS;
        break;
#endif /* HAS_HEVC */
#ifdef HAS_VC1
    case VDEC_STD_VC1:
        eCodec = VDECFW_CODEC_VC1;
        ui32Result = IMG_SUCCESS;
        break;
#endif /* HAS_VC1 */
#ifdef HAS_AVS
    case VDEC_STD_AVS:
        eCodec = VDECFW_CODEC_AVS;
        ui32Result = IMG_SUCCESS;
        break;
#endif /* HAS_AVS */
#ifdef HAS_REAL
    case VDEC_STD_REAL:
        eCodec = VDECFW_CODEC_RV;
        ui32Result = IMG_SUCCESS;
        break;
#endif /* HAS_REAL */
#ifdef HAS_JPEG
    case VDEC_STD_JPEG:
        eCodec = VDECFW_CODEC_JPEG;
        ui32Result = IMG_SUCCESS;
        break;
#endif /* HAS_JPEG */
#ifdef HAS_VP6
    case VDEC_STD_VP6:
        eCodec = VDECFW_CODEC_VP6;
        ui32Result = IMG_SUCCESS;
        break;
#endif /* HAS_VP6 */
#ifdef HAS_VP8
    case VDEC_STD_VP8:
        eCodec = VDECFW_CODEC_VP8;
        ui32Result = IMG_SUCCESS;
        break;
#endif /* HAS_VP8 */
    default:
        IMG_ASSERT(IMG_FALSE);
        ui32Result = IMG_ERROR_NOT_SUPPORTED;
        break;
    }

    *peCodec = eCodec;

    return ui32Result;
}

/*!
******************************************************************************

 @Function          translation_getCtxSize

 @Description

 This function returns size of standard specific shared firmware context size.

 @Input     eVidStd             : Video standard.

 @Return    IMG_UINT32          : Size of shared firmware context.

******************************************************************************/
static IMG_UINT32 translation_getCtxSize(VDEC_eVidStd eVidStd)
{
    switch(eVidStd)
    {
#ifdef HAS_AVS
        case VDEC_STD_AVS:
            return sizeof(AVSFW_sContextData);
            break;
#endif /* HAS_AVS */
#ifdef HAS_H264
        case VDEC_STD_H264:
            return sizeof(H264FW_sContextData);
#endif /* HAS_H264 */
#ifdef HAS_MPEG4
        case VDEC_STD_MPEG4:
        case VDEC_STD_H263:
        case VDEC_STD_SORENSON:
            return sizeof(MPEG4FW_sContextData);
#endif /* HAS_MPEG4 */
#ifdef HAS_VP6
        case VDEC_STD_VP6:
            return sizeof(VP6FW_sContextData);
#endif /* HAS_VP6 */
#ifdef HAS_VP8
        case VDEC_STD_VP8:
            return sizeof(VP8FW_sContextData);
#endif /* HAS_VP8 */
#ifdef HAS_JPEG
        case VDEC_STD_JPEG:
            return sizeof(JPEGFW_sContextData);
#endif /* HAS_JPEG */
#ifdef HAS_MPEG2
        case VDEC_STD_MPEG2:
            return sizeof(MPEG2FW_sContextData);
#endif /* HAS_MPEG2 */
#ifdef HAS_REAL
        case VDEC_STD_REAL:
            return sizeof(REALFW_sContextData);
#endif /* HAS_REAL */
#ifdef HAS_VC1
        case VDEC_STD_VC1:
            return sizeof(VC1FW_sContextData);
#endif /* HAS_VC1 */
#ifdef HAS_HEVC
        case VDEC_STD_HEVC:
            return sizeof(HEVCFW_sContextData);
#endif /* HAS_HEVC */
        default:
            IMG_ASSERT(0=="Uknown context size!");
            return 0;
    }
}

/*!
******************************************************************************

 @Function          translation_GetSeqHdr

 @Description

 This function is used to obtain buffer for sequence header.

 @Input     psStrUnit           : Stream unit being submitted.

 @Input     psDecPict           : Picture being decoded.

 @Output    puipSeqAddr         : Host address of sequence header buffer.

 @Input     bFakeMTX            : Whether fake MTX is used.

 @Return    IMG_RESULT          : This function returns either IMG_SUCCESS or
                                  an error code.

******************************************************************************/
static IMG_RESULT
translation_GetSeqHdr(
    VDECDD_sStrUnit        * psStrUnit,
    DECODER_sDecPict       * psDecPict,
    VDECFW_SHARED_UINTPTR  * puipSeqAddr,
    IMG_BOOL                 bFakeMTX
)
{
    // Sending Sequence info only if its a First Pic of Sequence, or a Start of Closed GOP
    if (psStrUnit->psPictHdrInfo->bFirstPicOfSequence || psStrUnit->bClosedGOP)
    {
        VDECDD_sDdBufMapInfo *  psDdBufMapInfo;
        /* Get access to map info context...*/
        IMG_RESULT ui32Result = RMAN_GetResource(psStrUnit->psSequHdrInfo->ui32BufMapId,
                                                 VDECDD_BUFMAP_TYPE_ID,
                                                 (IMG_VOID **)&psDdBufMapInfo,
                                                 IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
        UPDATE_DEVICE((&psDdBufMapInfo->sDdBufInfo), !bFakeMTX);
// *puipSeqAddr = GET_HOST_ADDR(&psDdBufMapInfo->sDdBufInfo, !bFakeMTX);
        *puipSeqAddr = GET_HOST_ADDR_OFFSET(&psDdBufMapInfo->sDdBufInfo, !bFakeMTX, psStrUnit->psSequHdrInfo->ui32BufOffset);
    }
    else
    {
        *puipSeqAddr = 0;
    }
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function          translation_GetPPSHdr

 @Description

 This function is used to obtain buffer for picture parameter set.

 @Input     psStrUnit           : Stream unit being submitted.

 @Input     psDecPict           : Picture being decoded.

 @Output    puipPPSAddr         : Host address of picture parameter set
                                  buffer.

 @Input     bFakeMTX            : Whether fake MTX is used.

 @Return    IMG_RESULT          : This function returns either IMG_SUCCESS or
                                  an error code.

******************************************************************************/
static IMG_RESULT
translation_GetPPSHdr(
    VDECDD_sStrUnit         * psStrUnit,
    DECODER_sDecPict        * psDecPict,
    VDECFW_SHARED_UINTPTR   * puipPPSAddr,
    IMG_BOOL                  bFakeMTX
)
{
    if (psStrUnit->psPictHdrInfo->sPictAuxData.ui32Id != BSPP_INVALID)
    {
        VDECDD_sDdBufMapInfo *  psDdBufMapInfo;
        IMG_RESULT ui32Result;

        IMG_ASSERT(psStrUnit->psPictHdrInfo->sPictAuxData.pvData);
        /* Get access to map info context...*/
        ui32Result = RMAN_GetResource(psStrUnit->psPictHdrInfo->sPictAuxData.ui32BufMapId,
                                      VDECDD_BUFMAP_TYPE_ID,
                                      (IMG_VOID **)&psDdBufMapInfo,
                                      IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
        UPDATE_DEVICE((&psDdBufMapInfo->sDdBufInfo), !bFakeMTX);
// *puipPPSAddr  = GET_HOST_ADDR(&psDdBufMapInfo->sDdBufInfo, !bFakeMTX);
        *puipPPSAddr = GET_HOST_ADDR_OFFSET(&psDdBufMapInfo->sDdBufInfo, !bFakeMTX, psStrUnit->psPictHdrInfo->sPictAuxData.ui32BufOffset);
    }
    else
    {
        *puipPPSAddr = 0;
    }
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function          translation_GetSecondPPSHdr

 @Description

 This function is used to obtain buffer for second picture parameter set.

 @Input     psStrUnit           : Stream unit being submitted.

 @Output    puipSecondPPSAddr   : Host address of second picture parameter
                                  set buffer.

 @Input     bFakeMTX            : Whether fake MTX is used.

 @Return    IMG_RESULT          : This function returns either IMG_SUCCESS or
                                  an error code.

******************************************************************************/
static IMG_RESULT
translation_GetSecondPPSHdr(
    VDECDD_sStrUnit          * psStrUnit,
    VDECFW_SHARED_UINTPTR    * puipSecondPPSAddr,
    IMG_BOOL                   bFakeMTX
)
{
    if (psStrUnit->psPictHdrInfo->sSecondPictAuxData.ui32Id != BSPP_INVALID)
    {
        VDECDD_sDdBufMapInfo *  psDdBufMapInfo;
        IMG_RESULT ui32Result;

        IMG_ASSERT(psStrUnit->psPictHdrInfo->sSecondPictAuxData.pvData);

        ui32Result = RMAN_GetResource(psStrUnit->psPictHdrInfo->sSecondPictAuxData.ui32BufMapId,
                                      VDECDD_BUFMAP_TYPE_ID,
                                      (IMG_VOID **)&psDdBufMapInfo,
                                      IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
        UPDATE_DEVICE((&psDdBufMapInfo->sDdBufInfo), !bFakeMTX);
// *puipSecondPPSAddr = GET_HOST_ADDR(&psDdBufMapInfo->sDdBufInfo, !bFakeMTX);
        *puipSecondPPSAddr = GET_HOST_ADDR_OFFSET(&psDdBufMapInfo->sDdBufInfo, !bFakeMTX, psStrUnit->psPictHdrInfo->sSecondPictAuxData.ui32BufOffset);
    }
    else
    {
        *puipSecondPPSAddr = 0;
    }
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function          translation_GetCtxLoadAddr

 @Description

 Returns address from which FW should download its shared context.

 @Input     psDecPict             : Picture being decoded.

 @Input     bFakeMTX              : Whether fake MTX is used.

 @Return    VDECFW_SHARED_UINTPTR : Address from which context should be
                                    loaded.

******************************************************************************/
static VDECFW_SHARED_UINTPTR
translation_GetCtxLoadAddr(
    DECODER_sDecPict        * psDecPict,
    IMG_BOOL                  bFakeMTX
)
{
    if (psDecPict->psPrevPictDecRes)
    {
         return GET_HOST_ADDR(&psDecPict->psPrevPictDecRes->sFwCtxBuf, !bFakeMTX);
    }
    else
    {
        // If no previous context exists, use the current context which should be all zeros.
        return GET_HOST_ADDR(&psDecPict->psCurPictDecRes->sFwCtxBuf, !bFakeMTX);
    }
}

/*!
******************************************************************************

 @Function          translation_SetupStdHeader

******************************************************************************/
static IMG_RESULT
translation_SetupStdHeader(
    VDEC_sStrConfigData     * psStrConfigData,
    DECODER_sDecPict        * psDecPict,
    VDECDD_sStrUnit         * psStrUnit,
    IMG_BOOL                  bFakeMtx,
    IMG_UINT32              * pui32PsrHdrSize,
    VDECDD_sPicture         * psPicture,
    IMG_UINT32              * pui32PictCmds,
    VDECFW_eParserMode      * peParserMode
)
{
    switch(psStrConfigData->eVidStd)
    {
#ifdef HAS_AVS
        case VDEC_STD_AVS:
        {
            AVSFW_sHeaderData * psHeaderData =  (AVSFW_sHeaderData *)psDecPict->psHdrInfo->psDdBufInfo->pvCpuVirt;
            const BSPP_sSequHdrInfo * psSeq = psStrUnit->psSequHdrInfo;

            /* Reset header data. */
            VDEC_BZERO(psHeaderData);

            /* Prepare active parameter sets. */
            translation_AVSHeader(psSeq, psPicture, psDecPict, psHeaderData);

            /* Setup header size in the transaction. */
            *pui32PsrHdrSize = sizeof(AVSFW_sHeaderData);
            break;
        }
#endif /* HAS_AVS */
#ifdef HAS_H264
        case VDEC_STD_H264:
        {
            H264FW_sHeaderData       * psHeaderData = (H264FW_sHeaderData *)psDecPict->psHdrInfo->psDdBufInfo->pvCpuVirt;
            *peParserMode = psStrUnit->psPictHdrInfo->eParserMode;
#ifdef VDEC_USE_PVDEC
            if (psStrUnit->psPictHdrInfo->eParserMode != VDECFW_SCP_ONLY)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                       "NOTE: parsing modes other than VDECFW_SCP_ONLY are not supported yet in PVDEC FW!  eParserMode: %d",
                       psStrUnit->psPictHdrInfo->eParserMode);
            }
#endif /* VDEC_USE_PVDEC */
            /* Reset header data. */
            VDEC_BZERO(psHeaderData);

            /* Prepare active parameter sets. */
            translation_H264Header(psPicture, psDecPict, psHeaderData, psStrConfigData);

            /* Setup header size in the transaction. */
            *pui32PsrHdrSize = sizeof(H264FW_sHeaderData);
            break;
        }
#endif /* HAS_H264 */
#ifdef HAS_MPEG4
        case VDEC_STD_MPEG4:
        case VDEC_STD_H263:
        case VDEC_STD_SORENSON:
        {
            MPEG4FW_sHeaderData      * psHeaderData =  (MPEG4FW_sHeaderData *)psDecPict->psHdrInfo->psDdBufInfo->pvCpuVirt;
            const BSPP_sSequHdrInfo  * psSeq = psStrUnit->psSequHdrInfo;

            /* Reset header data. */
            VDEC_BZERO(psHeaderData);

            /* Prepare active parameter sets. */
            translation_MPEG4Header(psSeq, psPicture, psDecPict, psHeaderData, psStrConfigData);

            /* Setup header size in the transaction. */
            *pui32PsrHdrSize = sizeof(MPEG4FW_sHeaderData);
            break;
        }
#endif /* HAS_MPEG4 */
#ifdef HAS_VP6
    case VDEC_STD_VP6:
        {
            VP6FW_sHeaderData   * psHeaderData = (VP6FW_sHeaderData *)psDecPict->psHdrInfo->psDdBufInfo->pvCpuVirt;
            const BSPP_sSequHdrInfo   * psSeq = psStrUnit->psSequHdrInfo;


            /* Reset header data. */
            VDEC_BZERO(psHeaderData);

            /* Prepare Active parameter sets */
            translation_VP6Header(psSeq, psPicture, psDecPict, psHeaderData, psStrConfigData);

            /* Setup header size in the transaction. */
            *pui32PsrHdrSize = sizeof(VP6FW_sHeaderData);
        }
        break;
#endif /* HAS_VP6 */
#ifdef HAS_VP8
    case VDEC_STD_VP8:
        {
            VP8FW_sHeaderData   * psHeaderData = (VP8FW_sHeaderData *)psDecPict->psHdrInfo->psDdBufInfo->pvCpuVirt;
            const BSPP_sSequHdrInfo   * psSeq = psStrUnit->psSequHdrInfo;
            BSPP_sBitStrSeg *psBitStrSeg = (BSPP_sBitStrSeg *)LST_first(&psStrUnit->sBitStrSegList);

            /* Reset header data. */
            VDEC_BZERO(psHeaderData);

            /* Prepare Active parameter sets */
            translation_VP8Header(psSeq, psPicture, psDecPict, psHeaderData, psStrConfigData);

            while(psBitStrSeg && (psBitStrSeg->ui32BitStrSegFlag & VDECDD_BSSEG_SKIP)!=0)
            {
                psBitStrSeg = LST_next(psBitStrSeg);
            }

            IMG_ASSERT(psBitStrSeg != IMG_NULL);
            if(psBitStrSeg != IMG_NULL)
            {
                IMG_UINT32 ui32Result;
                VDECDD_sDdBufMapInfo *  psDdBufMapInfo;
                /* Get access to map info context...*/
                ui32Result = RMAN_GetResource(psBitStrSeg->ui32BufMapId, VDECDD_BUFMAP_TYPE_ID, (IMG_VOID **)&psDdBufMapInfo, IMG_NULL);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }
                psHeaderData->ui32DCTBaseAddress = ((psDdBufMapInfo->sDdBufInfo.ui32DevVirt) + psBitStrSeg->ui32DataByteOffset);
            }

            /* Setup header size in the transaction. */
            *pui32PsrHdrSize = sizeof(VP8FW_sHeaderData);

        }
        break;
#endif /* HAS_VP8 */
#ifdef HAS_JPEG
        case VDEC_STD_JPEG:
        {
            JPEGFW_sHeaderData            * psHeaderData = (JPEGFW_sHeaderData *)psDecPict->psHdrInfo->psDdBufInfo->pvCpuVirt;
            const BSPP_sSequHdrInfo       * psSeq = psStrUnit->psSequHdrInfo;
            const BSPP_sPictHdrInfo       * psPictHdrInfo = psStrUnit->psPictHdrInfo;

            /* Reset header data. */
            VDEC_BZERO(psHeaderData);

            /* Prepare active parameter sets. */
            translation_JPEGHeader(psSeq, psDecPict, psPictHdrInfo, psHeaderData);

            /* Setup header size in the transaction. */
            *pui32PsrHdrSize = sizeof(JPEGFW_sHeaderData);

            break;
        }
#endif /* HAS_JPEG */
#ifdef HAS_MPEG2
        case VDEC_STD_MPEG2:
        {
            MPEG2FW_sHeaderData      * psHeaderData =  (MPEG2FW_sHeaderData *)psDecPict->psHdrInfo->psDdBufInfo->pvCpuVirt;
            const BSPP_sSequHdrInfo  * psSeq = psStrUnit->psSequHdrInfo;

            /* Reset header data. */
            VDEC_BZERO(psHeaderData);

            /* Prepare active parameter sets. */
            translation_MPEG2Header(psSeq, psPicture, psDecPict, psHeaderData, psStrConfigData, pui32PictCmds);

            /* Setup header size in the transaction. */
            *pui32PsrHdrSize = sizeof(MPEG2FW_sHeaderData);
            break;
        }
#endif /* HAS_MPEG2 */
#ifdef HAS_REAL
        case VDEC_STD_REAL:
        {
            REALFW_sHeaderData        * psHeaderData = (REALFW_sHeaderData *)psDecPict->psHdrInfo->psDdBufInfo->pvCpuVirt;
            const BSPP_sSequHdrInfo   * psSeq = psStrUnit->psSequHdrInfo;
            const BSPP_sPictHdrInfo   * psPictHdrInfo = psStrUnit->psPictHdrInfo;

            /* Reset header data. */
            VDEC_BZERO(psHeaderData);

            translation_RealHeader(psSeq, psPictHdrInfo, psPicture, psDecPict, psHeaderData);

#ifndef VDEC_USE_PVDEC
            translation_RealFragStartSegmentsCreate(psPictHdrInfo, &psStrUnit->sBitStrSegList, &psDecPict->sDecPictSegList);
#endif /* ndef VDEC_USE_PVDEC */

            /* Setup header size in the transaction. */
            *pui32PsrHdrSize = sizeof(REALFW_sHeaderData);
            break;
        }
#endif /* HAS_REAL*/
#ifdef HAS_VC1
        case VDEC_STD_VC1:
        {
            VC1FW_sHeaderData      * psHeaderData =  (VC1FW_sHeaderData *)psDecPict->psHdrInfo->psDdBufInfo->pvCpuVirt;
            const BSPP_sSequHdrInfo  * psSeq = psStrUnit->psSequHdrInfo;

            *peParserMode = psStrUnit->psPictHdrInfo->eParserMode;

            /* Reset header data. */
            VDEC_BZERO(psHeaderData);

            /* Prepare active parameter sets. */
            translation_VC1Header(psSeq, psPicture, psDecPict, psHeaderData, psStrConfigData);

            /* Setup header size in the transaction. */
            *pui32PsrHdrSize = sizeof(VC1FW_sHeaderData);
            break;
        }
#endif /* HAS_VC1 */

#ifdef HAS_HEVC
        case VDEC_STD_HEVC:
        {
            HEVCFW_sHeaderData * psHeaderData =
                (HEVCFW_sHeaderData *) psDecPict->psHdrInfo->psDdBufInfo->pvCpuVirt;
            *peParserMode = psStrUnit->psPictHdrInfo->eParserMode;

            /* Reset header data. */
            VDEC_BZERO(psHeaderData);

            /* Prepare active parameter sets. */
            translation_HEVCHeader(psPicture, psDecPict, psHeaderData);

            /* Setup header size in the transaction. */
            *pui32PsrHdrSize = sizeof(HEVCFW_sHeaderData);
            break;
        }
#endif /* HAS_HEVC */

        default:
            IMG_ASSERT(0=="Unknown standard!");
            *pui32PsrHdrSize = 0;
            break;
    }
    return IMG_SUCCESS;
}


#ifndef VDEC_USE_PVDEC

/*!
******************************************************************************

 @Function              TRANSLATION_PicturePrepare

******************************************************************************/
IMG_RESULT TRANSLATION_PicturePrepare(
    IMG_UINT32                  ui32StrId,
    VDEC_sStrConfigData       * psStrConfigData,
    VDECDD_sStrUnit           * psStrUnit,
    DECODER_sDecPict          * psDecPict,
    const VXD_sCoreProps      * psCoreProps,
    IMG_BOOL                    bFakeMTX
)
{
    VDECFW_sTransaction   * psTransaction = (VDECFW_sTransaction *)psDecPict->psTransactionInfo->psDdBufInfo->pvCpuVirt;
    VDECDD_sPicture       * psPicture;
    VXD_sBuffers            sBuffers;

    //IMG_BOOL               bForceExtendedAsBaseline;
    IMG_RESULT              ui32Result;
#ifndef USE_FW_RELOC_INFO_PACKING
    IMG_UINT32 copyOffset = 0;
    IMG_UINT32 copySize = 0;
#endif /* USE_FW_RELOC_INFO_PACKING */

    /* Reset transaction data. */
    VDEC_BZERO(psTransaction);

    /* Construct transaction based on new picture. */
    IMG_ASSERT(psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_START);

    /* Obtain picture data. */
    psPicture = (VDECDD_sPicture*)psStrUnit->pvDdPictData;
    if (psPicture->psPictResInt && psPicture->psPictResInt->psDdPictBuf)
    {
        psDecPict->psReconPict = psPicture->psPictResInt->psDdPictBuf;
        psDecPict->psAltPict = &psPicture->sDisplayPictBuf;
    }
    else
    {
        psDecPict->psReconPict = &psPicture->sDisplayPictBuf;
    }

    /* Setup top-level parameters. */
    psTransaction->ui32StreamId = ui32StrId;
    psTransaction->ui32TransactionId = psDecPict->ui32TransactionId;

    //Propagating the Secure Stream Flag
    psTransaction->bSecureStream = psStrConfigData->bSecureStream;

    ui32Result = translation_GetCodec(psStrConfigData->eVidStd,
                                      &psTransaction->eCodec);

    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
    psTransaction->eParserMode = VDECFW_SCP_ONLY;

    // Get the MMUTileConfig from the buffer config in the stream unit
    ui32Result = MSVDX_GetMmuTileConfig(psPicture->sDisplayPictBuf.sBufConfig.eTileScheme,
                                        psPicture->sDisplayPictBuf.sBufConfig.bByteInterleave,
                                        &psTransaction->sMmuTileConfig);
    if (ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR,
                "Failed to obtain the MMU tile configuration");
        return ui32Result;
    }

    // Determine any dependencies for this picture.
    psTransaction->ui32FeSyncTransactionId = psDecPict->ui32FeSyncTransactionId;
    psTransaction->ui32BeSyncTransactionId = psDecPict->ui32BeSyncTransactionId;

    psTransaction->ui32FeWdt = psDecPict->ui32FeWdtPeriod;
    psTransaction->ui32BeWdt = psDecPict->ui32BeWdtPeriod;
    psTransaction->ui32PSRWdt = psDecPict->ui32PSRWdtPeriod;

    psTransaction->uispCtxLoadAddr = translation_GetCtxLoadAddr(psDecPict, bFakeMTX);

    psTransaction->uispCtxSaveAddr = GET_HOST_ADDR(&psDecPict->psCurPictDecRes->sFwCtxBuf, !bFakeMTX);
    psTransaction->ui32CtxSize = translation_getCtxSize(psStrConfigData->eVidStd);

    psTransaction->uispCtrlSaveAddr = GET_HOST_ADDR(&psDecPict->psPictRefRes->sFwCtrlBuf, !bFakeMTX);
    psTransaction->ui32CtrlSize = psDecPict->psPictRefRes->sFwCtrlBuf.ui32BufSize;

    IMG_ASSERT(psStrUnit);
    IMG_ASSERT(psStrUnit->psSequHdrInfo);
    IMG_ASSERT(psStrUnit->psPictHdrInfo);

    ui32Result = translation_GetSeqHdr(psStrUnit, psDecPict, &psTransaction->uipSequenceInfoSource, bFakeMTX);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    ui32Result = translation_GetPPSHdr(psStrUnit, psDecPict, &psTransaction->uipPPSInfoSource, bFakeMTX);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    ui32Result = translation_GetSecondPPSHdr(psStrUnit, &psTransaction->uipSecondPPSInfoSource, bFakeMTX);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    ui32Result = translation_SetupStdHeader(psStrConfigData,
                                            psDecPict,
                                            psStrUnit,
                                            bFakeMTX,
                                            &psTransaction->ui32PsrHdrSize,
                                            psPicture,
                                            psTransaction->aui32PictCmds,
                                            &psTransaction->eParserMode);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
    /* Setup header data address in the transaction. */
    UPDATE_DEVICE((psDecPict->psHdrInfo->psDdBufInfo), !bFakeMTX);
    psTransaction->uispPsrHdrAddr = GET_HOST_ADDR(psDecPict->psHdrInfo->psDdBufInfo, !bFakeMTX);

    if (psDecPict->psVlcTablesBufInfo->hMemory)
    {
        UPDATE_DEVICE((psDecPict->psVlcTablesBufInfo), IMG_TRUE);
        psTransaction->uispVlcTablesAddr = GET_HOST_ADDR(psDecPict->psVlcTablesBufInfo, IMG_TRUE);
        psTransaction->ui32VlcTablesSize = psDecPict->psVlcTablesBufInfo->ui32BufSize;
    }

    if (psDecPict->psVlcIdxTableBufInfo->hMemory)
    {
        UPDATE_DEVICE((psDecPict->psVlcIdxTableBufInfo), !bFakeMTX);
        psTransaction->uispVlcIdxTableAddr = GET_HOST_ADDR(psDecPict->psVlcIdxTableBufInfo, !bFakeMTX);
        psTransaction->ui32VlcIdxTableSize = psDecPict->psVlcIdxTableBufInfo->ui32BufSize;
    }


    /* We need to make sure there is minimum translation between Hdr Data populated */
    /* by the bspp and Picture Hdr data needed by the firmware. */

    /* Prepare BE Commands */
    sBuffers.psReconPict = psDecPict->psReconPict;
    sBuffers.psAltPict = psDecPict->psAltPict;
    sBuffers.psIntraBufInfo = psDecPict->psIntraBufInfo;
    sBuffers.psAuxLineBufInfo = psDecPict->psAuxLineBufInfo;

    /* Only one pipe so always zero */
    sBuffers.ui32IntraBufPipeOffset = 0;
    sBuffers.ui32AuxLineBufPipeOffset = 0;

    if (psPicture->psPictResInt && psPicture->psPictResInt->psSeqResInt && psPicture->psPictResInt->psSeqResInt->psMSBBuffer)
    {
        sBuffers.psMSBBufInfo = &psPicture->psPictResInt->psSeqResInt->psMSBBuffer->sDdBufInfo;
    }

    /* Reconstructed Picture Configuration */
    ui32Result = VXD_SetReconPictCmds(psStrUnit,
                                      psStrConfigData,
                                      &psPicture->sOutputConfig,
                                      psCoreProps,
                                      &sBuffers,
                                      psTransaction->aui32PictCmds);

    /* Alternative Picture Configuration */
    if (psDecPict->psAltPict)
    {
        psDecPict->bTwoPass = psPicture->sOutputConfig.bForceOold;

#ifdef HAS_H264
        if (psStrConfigData->eVidStd == VDEC_STD_H264)
        {
            psDecPict->bTwoPass = (psDecPict->bTwoPass || psStrUnit->psPictHdrInfo->bDiscontinuousMbs);
        }
#endif /* HAS_H264 */

        sBuffers.bTwoPass = psDecPict->bTwoPass;

        /* Alternative Picture Configuration */
        /* Configure second buffer for out-of-loop processing (e.g. scaling etc.). */
        ui32Result = VXD_SetAltPictCmds(psStrUnit,
                                        psStrConfigData,
                                        &psPicture->sOutputConfig,
                                        psCoreProps,
                                        &sBuffers,
                                        psTransaction->aui32PictCmds);
    }


    /* Prepare Parser configuration parameters */

    return IMG_SUCCESS;
}

#else /* def VDEC_USE_PVDEC */

#define VDEC_INITIAL_DEVA_DMA_CMD_SIZE 3
#define VDEC_SINLGE_DEVA_DMA_CMD_SIZE 2


static IMG_RESULT translation_PvdecAddDmaTransfers(
    LST_T                  * psDecPictSegList,
    VXDIO_sDdBufInfo       * psEndBytesBufInfo,
    IMG_UINT32            ** ppui32DmaCmdBuf,
    IMG_INT32                i32CmdBufSize, /* in words */
    DECODER_sDecPict       * psDecPict
)
{
    /* DEVA's bitstream DMA command is made out of chunks with following
     * layout ('+' sign is used to mark actual words in command):
     *
     * -----------------------------------------------------------------
     *
     * + Bitstream HDR, type IMG_UINT32, consists of:
     *     - command id (CMD_BITSTREAM_SEGMENTS),
     *     - number of segments in this chunk,
     *     - optional CMD_BITSTREAM_SEGMENTS_MORE_FOLLOW_MASK
     *
     * + Bitstream total size, type IMG_UINT32,
     *   represents size of all segments in all chunks
     *
     * - Segments of following type (can repeat up to
     *   CMD_BITSTREAM_SEGMENTS_MINUS1_MASK + 1 times)
     *
     *      + Bitstream segment address, type IMG_UINT32
     *
     *      + Bitstream segment size, type IMG_UINT32
     *
     * -----------------------------------------------------------------
     *
     *
     * Subsequent chunks are present when CMD_BITSTREAM_SEGMENTS_MORE_FOLLOW_MASK
     * flag is set in Bitstream HDR.
     *
     */
    DECODER_sDecPictSeg * psDecPictSeg = (DECODER_sDecPictSeg *) LST_first(psDecPictSegList);
    IMG_UINT32 * pui32Cmd = *ppui32DmaCmdBuf;
    IMG_UINT32 * pui32DmaHdr = pui32Cmd;
    IMG_UINT32   ui32SegCount = 0;
    IMG_UINT32   ui32BitstreamSize = 0;

    /* Two words for DMA command header (setup later as we need to find out count of BS segments) */
    pui32Cmd += CMD_BITSTREAM_HDR_DW_SIZE;
    i32CmdBufSize -= CMD_BITSTREAM_HDR_DW_SIZE;
    if (i32CmdBufSize < 0)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Buffer for DMA command too small.");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    if(psDecPictSeg == IMG_NULL)
    {
        /* No segments to be send to FW: preparing fake one */
        i32CmdBufSize -= VDEC_SINLGE_DEVA_DMA_CMD_SIZE;
        if (i32CmdBufSize < 0)
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Buffer for DMA command too small.");
            return IMG_ERROR_INVALID_PARAMETERS;
        }
        ui32SegCount++;

        /* zeroing bitstream size and bitstream offset */
        *(pui32Cmd++) = 0;
        *(pui32Cmd++) = 0;
    }

    /* Loop through all bitstream segments */
    while(psDecPictSeg != IMG_NULL)
    {
        if(psDecPictSeg->psBitStrSeg && (psDecPictSeg->psBitStrSeg->ui32BitStrSegFlag&VDECDD_BSSEG_SKIP) == 0)
        {
            IMG_UINT32 ui32Result;
            VDECDD_sDdBufMapInfo * psDdBufMapInfo;

            ui32SegCount++;
            /* Two words for each added bitstream segment */
            i32CmdBufSize -= VDEC_SINLGE_DEVA_DMA_CMD_SIZE;
            if (i32CmdBufSize < 0)
            {
                REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Buffer for DMA command too small.");
                return IMG_ERROR_INVALID_PARAMETERS;
            }
            /* Insert SCP/SC if needed */
            if (psDecPictSeg->psBitStrSeg->ui32BitStrSegFlag & VDECDD_BSSEG_INSERTSCP)
            {
                IMG_UINT32 ui32StartCodeLength = psDecPict->psStartCodeBufInfo->ui32BufSize;

                if (psDecPictSeg->psBitStrSeg->ui32BitStrSegFlag & VDECDD_BSSEG_INSERT_STARTCODE)
                {
                    IMG_UINT8 * pui8StartCode = psDecPict->psStartCodeBufInfo->pvCpuVirt;
                    pui8StartCode[ui32StartCodeLength - 1] = psDecPictSeg->psBitStrSeg->ui8StartCodeSuffix;
                    UPDATE_DEVICE(psDecPict->psStartCodeBufInfo, IMG_TRUE);
                }
                else
                {
                    ui32StartCodeLength -= 1;
                }

                ui32SegCount++;
                *(pui32Cmd++) = ui32StartCodeLength;
                ui32BitstreamSize += ui32StartCodeLength;

                *(pui32Cmd++) = psDecPict->psStartCodeBufInfo->ui32DevVirt;

                if(((ui32SegCount % (CMD_BITSTREAM_SEGMENTS_MINUS1_MASK+1)) == 0))
                {
                    // we have reached max number of bitstream segments for current command
                    // make pui32Cmd point to next BS command
                    pui32Cmd += CMD_BITSTREAM_HDR_DW_SIZE;
                }
            }
            /* Get access to map info context...*/
            ui32Result = RMAN_GetResource(psDecPictSeg->psBitStrSeg->ui32BufMapId, VDECDD_BUFMAP_TYPE_ID, (IMG_VOID **)&psDdBufMapInfo, IMG_NULL);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
            *(pui32Cmd++) = (psDecPictSeg->psBitStrSeg->ui32DataSize);
            ui32BitstreamSize += psDecPictSeg->psBitStrSeg->ui32DataSize;

            *(pui32Cmd++) = psDdBufMapInfo->sDdBufInfo.ui32DevVirt + psDecPictSeg->psBitStrSeg->ui32DataByteOffset;

            if(((ui32SegCount % (CMD_BITSTREAM_SEGMENTS_MINUS1_MASK+1)) == 0) && (LST_next(psDecPictSeg) != IMG_NULL))
            {
                // we have reached max number of bitstream segments for current command
                // make pui32Cmd point to next BS command
                pui32Cmd += CMD_BITSTREAM_HDR_DW_SIZE;
            }

            UPDATE_DEVICE((&psDdBufMapInfo->sDdBufInfo), IMG_TRUE);
        }
        psDecPictSeg = LST_next(psDecPictSeg);
    }

    while(ui32SegCount > (CMD_BITSTREAM_SEGMENTS_MINUS1_MASK+1))
    {
        *pui32DmaHdr++ = CMD_BITSTREAM_SEGMENTS | CMD_BITSTREAM_SEGMENTS_MORE_FOLLOW_MASK | CMD_BITSTREAM_SEGMENTS_MINUS1_MASK;
        *pui32DmaHdr++ = ui32BitstreamSize;
        // make pui32DmaHdr point to next chunk by skipping bitstream sements
        pui32DmaHdr += (2*(CMD_BITSTREAM_SEGMENTS_MINUS1_MASK+1));
        ui32SegCount -= (CMD_BITSTREAM_SEGMENTS_MINUS1_MASK+1);
    }
    *pui32DmaHdr++ = CMD_BITSTREAM_SEGMENTS | (ui32SegCount-1);
    *pui32DmaHdr = ui32BitstreamSize;

#if 0
    i32CmdBufSize -= VDEC_SINLGE_DEVA_DMA_CMD_SIZE;
    if (i32CmdBufSize < 0)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Buffer for DMA command too small.");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    *(pui32Cmd++) = ui32Cmd | psEndBytesBufInfo->ui32BufSize;
    *(pui32Cmd++) = psEndBytesBufInfo->ui32DevVirt;
    REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Added End bytes %08x, size: %08x",
            psEndBytesBufInfo->ui32DevVirt, psEndBytesBufInfo->ui32BufSize);

    UPDATE_DEVICE((psEndBytesBufInfo), IMG_TRUE);
#endif

    /* Let caller know where we finished. Pointer to location one word after end of our command buffer */
    *ppui32DmaCmdBuf = pui32Cmd;
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              translation_PvdecSetupCtrlHdr

 @Description

 Creates DEVA control allocation buffer header.

 @Input     psCtrlAllocHdr      : Pointer to control allocation header.

 @Input     aui32PictCmds       : Buffer with commands, in order defined in
                                  VDECFW_ePictureCmds enum.

 @Return    None.

******************************************************************************/
static IMG_VOID
translation_PvdecSetupCtrlHdr(
    CTRL_ALLOC_HEADER     * psCtrlAllocHdr,
    IMG_UINT32            * aui32PictCmds
)
{
    psCtrlAllocHdr->ui32Cmd_AdditionalParams = CMD_CTRL_ALLOC_HEADER;
    psCtrlAllocHdr->ui32ExtOpMode = aui32PictCmds[VDECFW_CMD_EXT_OP_MODE];
    psCtrlAllocHdr->uiChromaStrides = aui32PictCmds[VDECFW_CMD_CHROMA_ROW_STRIDE];
    psCtrlAllocHdr->ui32AltOutputAddr[0] =
        aui32PictCmds[VDECFW_CMD_LUMA_ALTERNATIVE_PICTURE_BASE_ADDRESS];
    psCtrlAllocHdr->ui32AltOutputAddr[1] =
        aui32PictCmds[VDECFW_CMD_CHROMA_ALTERNATIVE_PICTURE_BASE_ADDRESS];
    psCtrlAllocHdr->ui32AltOutputFlags =
        aui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION];
}

#ifdef HAS_VP8
/*!
******************************************************************************

 @Function              translation_PvdecSetupVP8AddParams

 @Description

 Sets up Vp8 specific allocation buffer header params.

 @Input     psCtrlAllocHdr      : Pointer to control allocation header.

 @Input     psDecPict           : Picture being decoded.

 @Return    None.

******************************************************************************/
static IMG_VOID
translation_PvdecSetupVP8AddParams(
    CTRL_ALLOC_HEADER     * psCtrlAllocHdr,
    DECODER_sDecPict      * psDecPict)
{
    IMG_UINT32 muiSliceParams = 0;

    psCtrlAllocHdr->ui32Cmd_AdditionalParams |= (( psDecPict->psPictHdrInfo->sVP8PictHdrInfo.ui32FirstPartSize + ((psDecPict->psPictHdrInfo->bIntraCoded) ? 10 : 3)) & VP8_BUFFOFFSET_MASK);
    psCtrlAllocHdr->ui32Cmd_AdditionalParams |= ((psDecPict->psPictHdrInfo->sVP8PictHdrInfo.ui8PartitionCount << VP8_PARTITIONSCOUNT_SHIFT)  & VP8_PARTITIONSCOUNT_MASK);

    REGIO_WRITE_FIELD_LITE( muiSliceParams, MSVDX_CMDS, SLICE_PARAMS, SLICE_FIELD_TYPE, 0x02 ); // always a frame
    REGIO_WRITE_FIELD_LITE( muiSliceParams, MSVDX_CMDS, SLICE_PARAMS, SLICE_CODE_TYPE, !psDecPict->psPictHdrInfo->bIntraCoded );
    psCtrlAllocHdr->ui32SliceParams = muiSliceParams;
}
#endif

#ifdef HAS_VP6
/*!
******************************************************************************

 @Function              translation_PvdecSetupVP6AddParams

 @Description

 Sets up Vp8 specific allocation buffer header params.

 @Input     psCtrlAllocHdr      : Pointer to control allocation header.

 @Input     psDecPict           : Picture being decoded.

 @Return    None.

******************************************************************************/
static IMG_VOID
translation_PvdecSetupVP6AddParams(
    CTRL_ALLOC_HEADER     * psCtrlAllocHdr,
    DECODER_sDecPict      * psDecPict)
{
    IMG_UINT32 muiSliceParams = 0;

    /*if VP6 bitstream is multi-partitioned then convey all the info including buffer offset information for 2nd partition to the firmware  */
    psCtrlAllocHdr->ui32Cmd_AdditionalParams |=  (psDecPict->psPictHdrInfo->sVP6PictHdrInfo.ui32Buff2Offset & VP6_BUFFOFFSET_MASK);
    if(psDecPict->psPictHdrInfo->sVP6PictHdrInfo.bMultiStream)
    {
        psCtrlAllocHdr->ui32Cmd_AdditionalParams  |=  VP6_MULTISTREAM_MASK ; /*if the bistream is multistream*/
        if(!psDecPict->psPictHdrInfo->bIntraCoded)
        {
            psCtrlAllocHdr->ui32Cmd_AdditionalParams  |= VP6_FRAMETYPE_MASK;
        }
    }

    REGIO_WRITE_FIELD_LITE( muiSliceParams, MSVDX_CMDS, SLICE_PARAMS, SLICE_FIELD_TYPE, 0x02 ); // always a frame
    REGIO_WRITE_FIELD_LITE( muiSliceParams, MSVDX_CMDS, SLICE_PARAMS, SLICE_CODE_TYPE, !psDecPict->psPictHdrInfo->bIntraCoded );
    psCtrlAllocHdr->ui32SliceParams = muiSliceParams;
}
#endif


static IMG_RESULT translation_PvdecSetupVlcDma(
    VXDIO_sDdBufInfo       * psVlcTablesBufInfo,
    IMG_UINT32            ** ppui32DmaCmdBuf,
    IMG_UINT32               ui32CmdBufSize /* in words */
)
{
    IMG_UINT32   ui32CmdDma;
    IMG_UINT32 * pui32Cmd = *ppui32DmaCmdBuf;

    /* Check if VLC tables fit in one DMA transfer */
    if (psVlcTablesBufInfo->ui32BufSize > CMD_DMA_DMA_SIZE_MASK)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "VLC tables won't fit into one DMA transfer!");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Check if we have enough space in control allocation buffer. */
    if (ui32CmdBufSize < VDEC_SINLGE_DEVA_DMA_CMD_SIZE)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Buffer for DMA command too small.");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Construct DMA command */
    ui32CmdDma = CMD_DMA | CMD_DMA_TYPE_VLC_TABLE | psVlcTablesBufInfo->ui32BufSize;

    /* Add command to control allocation */
    *pui32Cmd++ = ui32CmdDma;
    *pui32Cmd++ = psVlcTablesBufInfo->ui32DevVirt;

    /* Let caller know where we finished. Pointer to location one word after end of our buffer */
    *ppui32DmaCmdBuf = pui32Cmd;
    return IMG_SUCCESS;
}



static IMG_RESULT translation_PvdecSetupVlcTables(
    IMG_UINT16             aui16VlcIndexData[][3],
    IMG_UINT32             ui32NumTables,
    IMG_UINT32          ** ppui32CtrlAllocBuf,
    IMG_UINT32             ui32CtrlAllocSize, /* in words */
    IMG_UINT32             ui32MsvdxVecOffset
)
{
    IMG_UINT32    ui32i;
    IMG_UINT32    ui32WordCnt;
    IMG_UINT32    ui32RegVal;
    IMG_UINT32 *  pui32CtrlAllocHdr;

    IMG_UINT32 *  pui32CtrlAlloc = *ppui32CtrlAllocBuf;

    /* Calculate the number of words needed for VLC control allocations. */
    IMG_UINT32   ui32ReqElems = 3 + /* 3 words for control allocation headers (we are writing 3 chunks: addresses, widths, opcodes) */
                                (VDEC_ALIGN_SIZE(ui32NumTables, PVDECIO_VLC_IDX_WIDTH_PARTS)/PVDECIO_VLC_IDX_WIDTH_PARTS) +
                                (VDEC_ALIGN_SIZE(ui32NumTables, PVDECIO_VLC_IDX_ADDR_PARTS)/PVDECIO_VLC_IDX_ADDR_PARTS) +
                                (VDEC_ALIGN_SIZE(ui32NumTables, PVDECIO_VLC_IDX_OPCODE_PARTS)/PVDECIO_VLC_IDX_OPCODE_PARTS);

    /* Addresses chunk has to be split in two, if number of tables exceeds
     * VEC_VLC_TABLE_ADDR_DISCONT (see layout of VEC_VLC_TABLE_ADDR* registers in TRM) */
    if (ui32NumTables > VEC_VLC_TABLE_ADDR_DISCONT)
    {
        ui32ReqElems += 1; /* We need additional control allocation header */
    }

    if (ui32CtrlAllocSize < ui32ReqElems)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Buffer for VLC IDX commands too small.");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Write VLC IDX addresses. Chunks for VEC_VLC_TABLE_ADDR[0-15] and VEC_VLC_TABLE_ADDR[16-18] registers. */

    /* Reserve and preset command header for VEC_VLC_TABLE_ADDR[0-15] register chunk.*/
    pui32CtrlAllocHdr = pui32CtrlAlloc++;
    *pui32CtrlAllocHdr = CMD_REGISTER_BLOCK | CMD_REGISTER_BLOCK_FLAG_VLC_DATA |
                            (MSVDX_VEC_CR_VEC_VLC_TABLE_ADDR0_OFFSET + ui32MsvdxVecOffset);
    /* Reset the word count. */
    ui32WordCnt = 0;

    /* Process VLC index table. */
    ui32i = 0;
    ui32RegVal = 0;
    while(ui32i < ui32NumTables)
    {
        IMG_ASSERT((aui16VlcIndexData[ui32i][PVDECIO_VLC_IDX_ADDR_ID] & ~PVDECIO_VLC_IDX_ADDR_MASK) == 0);
        /* Pack the addresses into a word. */
        ui32RegVal |= ((aui16VlcIndexData[ui32i][PVDECIO_VLC_IDX_ADDR_ID] & PVDECIO_VLC_IDX_ADDR_MASK) <<
                                            ((ui32i % PVDECIO_VLC_IDX_ADDR_PARTS) * PVDECIO_VLC_IDX_ADDR_SHIFT));

        /* If we reached the end of VEC_VLC_TABLE_ADDR[0-15] area... */
        if(ui32i == VEC_VLC_TABLE_ADDR_DISCONT)
        {
            /* Finalise command header for VEC_VLC_TABLE_ADDR[0-15] register chunk.*/
            *pui32CtrlAllocHdr |= ui32WordCnt << 16;
            /* Reserve and preset command header for VEC_VLC_TABLE_ADDR[16-18] register chunk. */
            pui32CtrlAllocHdr = pui32CtrlAlloc++;
            *pui32CtrlAllocHdr = CMD_REGISTER_BLOCK | CMD_REGISTER_BLOCK_FLAG_VLC_DATA |
                                    (MSVDX_VEC_CR_VEC_VLC_TABLE_ADDR16_OFFSET + ui32MsvdxVecOffset);
            /* Reset the word count. */
            ui32WordCnt = 0;
        }

        /* If all the addresses are packed in this word or that's the last iteration... */
        if(((ui32i % PVDECIO_VLC_IDX_ADDR_PARTS) == (PVDECIO_VLC_IDX_ADDR_PARTS - 1)) || (ui32i == (ui32NumTables - 1)))
        {
            /* Add VLC table address to this chunk and increase words count. */
            *pui32CtrlAlloc++ = ui32RegVal;
            ui32WordCnt++;
            /* Reset address value. */
            ui32RegVal = 0;
        }

        ui32i++;
    }

    /* Finalise the current command header for VEC_VLC_TABLE_ADDR register chunk. */
    *pui32CtrlAllocHdr |= ui32WordCnt << 16;

    /* Start new commands chunk for VEC_VLC_TABLE_INITIAL_WIDTH[0-3] registers. */

    /* Reserve and preset command header for VEC_VLC_TABLE_INITIAL_WIDTH[0-3] register chunk.*/
    pui32CtrlAllocHdr = pui32CtrlAlloc++;
    *pui32CtrlAllocHdr = CMD_REGISTER_BLOCK | CMD_REGISTER_BLOCK_FLAG_VLC_DATA |
                            (MSVDX_VEC_CR_VEC_VLC_TABLE_INITIAL_WIDTH0_OFFSET + ui32MsvdxVecOffset);
    /* Reset the word count. */
    ui32WordCnt = 0;

    /* Process VLC index table. */
    ui32i = 0;
    ui32RegVal = 0;
    while(ui32i < ui32NumTables)
    {
        IMG_ASSERT((aui16VlcIndexData[ui32i][PVDECIO_VLC_IDX_WIDTH_ID] & ~PVDECIO_VLC_IDX_WIDTH_MASK) == 0);
        /* Pack the widths into a word. */
        ui32RegVal |= ((aui16VlcIndexData[ui32i][PVDECIO_VLC_IDX_WIDTH_ID] & PVDECIO_VLC_IDX_WIDTH_MASK) <<
                                            (ui32i % PVDECIO_VLC_IDX_WIDTH_PARTS) * PVDECIO_VLC_IDX_WIDTH_SHIFT);

        /* If all the widths are packed in this word or that's the last iteration... */
        if(((ui32i % PVDECIO_VLC_IDX_WIDTH_PARTS) == (PVDECIO_VLC_IDX_WIDTH_PARTS - 1)) || (ui32i == (ui32NumTables - 1)))
        {
            /* Add VLC table width to this chunk and increase words count. */
            *pui32CtrlAlloc++ = ui32RegVal;
            ui32WordCnt++;
            /* Reset width value. */
            ui32RegVal = 0;
        }

        ui32i++;
    }

    /* Finalise command header for VEC_VLC_TABLE_INITIAL_WIDTH[0-3] register chunk.*/
    *pui32CtrlAllocHdr |= ui32WordCnt << 16;

    /* Start new commands chunk for VEC_VLC_TABLE_INITIAL_OPCODE[0-2] registers. */
    /* Reserve and preset command header for VEC_VLC_TABLE_INITIAL_OPCODE[0-2] register chunk.*/
    pui32CtrlAllocHdr = pui32CtrlAlloc++;
    *pui32CtrlAllocHdr = CMD_REGISTER_BLOCK | CMD_REGISTER_BLOCK_FLAG_VLC_DATA |
                            (MSVDX_VEC_CR_VEC_VLC_TABLE_INITIAL_OPCODE0_OFFSET + ui32MsvdxVecOffset);
    /* Reset the word count. */
    ui32WordCnt = 0;

    /* Process VLC index table. */
    ui32i = 0;
    ui32RegVal = 0;
    while(ui32i < ui32NumTables)
    {
        IMG_ASSERT((aui16VlcIndexData[ui32i][PVDECIO_VLC_IDX_OPCODE_ID] & ~PVDECIO_VLC_IDX_OPCODE_MASK) == 0);
        /* Pack the opcodes into a word. */
        ui32RegVal |= ((aui16VlcIndexData[ui32i][PVDECIO_VLC_IDX_OPCODE_ID] & PVDECIO_VLC_IDX_OPCODE_MASK) <<
                                            (ui32i % PVDECIO_VLC_IDX_OPCODE_PARTS) * PVDECIO_VLC_IDX_OPCODE_SHIFT);

        /* If all the opcodes are packed in this word or that's the last iteration... */
        if(((ui32i % PVDECIO_VLC_IDX_OPCODE_PARTS) == (PVDECIO_VLC_IDX_OPCODE_PARTS - 1)) || (ui32i == (ui32NumTables - 1)))
        {
            /* Add VLC table opcodes to this chunk and increase words count. */
            *pui32CtrlAlloc++ = ui32RegVal;
            ui32WordCnt++;
            /* Reset width value. */
            ui32RegVal = 0;
        }

        ui32i++;
    }

    /* Finalise command header for VEC_VLC_TABLE_INITIAL_OPCODE[0-2] register chunk.*/
    *pui32CtrlAllocHdr |= ui32WordCnt << 16;

    /* Update caller with current location of control allocation pointer */
    *ppui32CtrlAllocBuf = pui32CtrlAlloc;
    return IMG_SUCCESS;
}



static IMG_RESULT translation_PvdecSetupCommands(
    IMG_UINT32           * aui32PictCmds,
    IMG_UINT32          ** ppui32CtrlAllocBuf,
    IMG_UINT32             ui32CtrlAllocSize, /* in words */
    IMG_UINT32             ui32VdmcCmdOffset
)
{
    /* Helper macros. */
    /*
     * This macro declares and sets up chunk filling auxiliary variables.
     */
    #define SETUP_CHUNK_VARS()               \
        IMG_UINT32  ui32ChunkWordCount = 0;  \
        IMG_UINT32  ui32UsedWordCount = 0    \

    /*
     * This macro fills in a rendec command chunk in the command buffer.
     * Inputs:
     *   offset : target register area offset
     *   ...    : list of picture command ids (see VDECFW_ePictureCmds)
     */
    #define FILL_RENDEC_CHUNK(offset, ...)                                                            \
    {                                                                                                 \
        VDECFW_ePictureCmds  aeAuxArray[] = {__VA_ARGS__};                                            \
        IMG_UINT32 *         pui32Buf = *ppui32CtrlAllocBuf;                                          \
        IMG_UINT32           ui32I;                                                                   \
                                                                                                      \
        ui32ChunkWordCount = sizeof(aeAuxArray)/sizeof(VDECFW_ePictureCmds);                          \
                                                                                                      \
        if((ui32ChunkWordCount + 1) > (ui32CtrlAllocSize - ui32UsedWordCount))                        \
        {                                                                                             \
            REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Buffer for commands is too small.");           \
            return IMG_ERROR_INVALID_PARAMETERS;                                                      \
        }                                                                                             \
        if((ui32ChunkWordCount & ~(CMD_RENDEC_WORD_COUNT_MASK >> CMD_RENDEC_WORD_COUNT_SHIFT)) != 0)  \
        {                                                                                             \
            REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Too many commands for a single chunk.");       \
            return IMG_ERROR_INVALID_PARAMETERS;                                                      \
        }                                                                                             \
                                                                                                      \
        ui32UsedWordCount += ui32ChunkWordCount + 1;                                                  \
        *pui32Buf++ = CMD_RENDEC_BLOCK | (ui32ChunkWordCount << 16) | (ui32VdmcCmdOffset + offset);   \
        for(ui32I = 0; ui32I < ui32ChunkWordCount; ui32I++)                                           \
        {                                                                                             \
            *pui32Buf++ = aui32PictCmds[aeAuxArray[ui32I]];                                           \
        }                                                                                             \
                                                                                                      \
        *ppui32CtrlAllocBuf = pui32Buf;                                                               \
    }

    SETUP_CHUNK_VARS();

    IMG_UINT32 ui32CodecMode;
    ui32CodecMode = REGIO_READ_FIELD(aui32PictCmds[VDECFW_CMD_OPERATING_MODE],
        MSVDX_CMDS, OPERATING_MODE, CODEC_MODE);

#ifdef HAS_VC1
    if (ui32CodecMode == CODEC_MODE_VC1)
    {
        /* chunk with aux msb buffer base address at 0x014, only for VC1 */
        FILL_RENDEC_CHUNK(MSVDX_CMDS_AUX_MSB_BUFFER_BASE_ADDRESSES_OFFSET,
                          VDECFW_CMD_AUX_MSB_BUFFER);
    }
#endif /* HAS_VC1 */

    if (ui32CodecMode != CODEC_MODE_JPEG)
    {
        /* chunk with intra buffer base address at 0x018 */
    FILL_RENDEC_CHUNK(MSVDX_CMDS_INTRA_BUFFER_BASE_ADDRESS_OFFSET,
                          VDECFW_CMD_INTRA_BUFFER_BASE_ADDRESS);
    }

    if (ui32CodecMode != CODEC_MODE_H264)
    {
        /* chunk with cache settings at 0x01C */
        FILL_RENDEC_CHUNK(MSVDX_CMDS_MC_CACHE_CONFIGURATION_OFFSET,
                          VDECFW_CMD_MC_CACHE_CONFIGURATION);
    }

    /* chunk with extended row stride at 0x03C */
    FILL_RENDEC_CHUNK(MSVDX_CMDS_EXTENDED_ROW_STRIDE_OFFSET,
                      VDECFW_CMD_EXTENDED_ROW_STRIDE);

    /* chunk with alternative output control at 0x1B4 */
    FILL_RENDEC_CHUNK(MSVDX_CMDS_ALTERNATIVE_OUTPUT_CONTROL_OFFSET,
                      VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL);

    /* chunk with aux line buffer base address at 0x1EC */
    FILL_RENDEC_CHUNK(MSVDX_CMDS_AUX_LINE_BUFFER_BASE_ADDRESS_OFFSET,
                      VDECFW_CMD_AUX_LINE_BUFFER_BASE_ADDRESS);

    /* scaling chunks */
    if (aui32PictCmds[VDECFW_CMD_SCALED_DISPLAY_SIZE])
    {
        if ((ui32CodecMode != CODEC_MODE_REAL8) && (ui32CodecMode != CODEC_MODE_REAL9))
        {
            /* chunk with scale display size, scale H/V control at 0x0050 */
            FILL_RENDEC_CHUNK(MSVDX_CMDS_SCALED_DISPLAY_SIZE_OFFSET,
                              VDECFW_CMD_SCALED_DISPLAY_SIZE,
                              VDECFW_CMD_HORIZONTAL_SCALE_CONTROL,
                              VDECFW_CMD_VERTICAL_SCALE_CONTROL);

            /* chunk with luma/chorma H/V coeffs at 0x0060 */
            FILL_RENDEC_CHUNK(MSVDX_CMDS_HORIZONTAL_LUMA_COEFFICIENTS_OFFSET,
                              VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_0,
                              VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_1,
                              VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_2,
                              VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_3,
                              VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_0,
                              VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_1,
                              VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_2,
                              VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_3,
                              VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_0,
                              VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_1,
                              VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_2,
                              VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_3,
                              VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_0,
                              VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_1,
                              VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_2,
                              VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_3);

            /* chunk with scale output size, scale H/V chroma at 0x01B8 */
            FILL_RENDEC_CHUNK(MSVDX_CMDS_SCALE_OUTPUT_SIZE_OFFSET,
                              VDECFW_CMD_SCALE_OUTPUT_SIZE,
                              VDECFW_CMD_SCALE_HORIZONTAL_CHROMA,
                              VDECFW_CMD_SCALE_VERTICAL_CHROMA);
        }
    }

    return IMG_SUCCESS;
}

#ifdef HAS_HEVC

static IMG_RESULT translation_PvdecSetupHEVCCommands(
    VDECDD_sPicture      * psPicture,
    DECODER_sDecPict     * psDecPict,
    VDECDD_sStrUnit      * psStrUnit,
    DECODER_sRegsOffsets * psRegsOffsets,
    IMG_UINT32          ** ppui32CtrlAllocBuf,
    IMG_UINT32             ui32CtrlAllocSize, /* in dwords */
    IMG_UINT32           * pui32MemToRegHostPart, /* in dwords */
    IMG_UINT32           * aui32PictCmds
)
{
    const IMG_UINT32 ui32GencBufferCount = 4;
    const IMG_UINT32 ui32GENCConfItems = 2; /* We have two chunks: for GENC buffers addresses and sizes*/
    const IMG_UINT32 ui32Pipe = 0xf << 16; /* Instruct H/W to write to current pipe */
    const IMG_UINT32 ui32GENCWordsCnt = ui32GencBufferCount * ui32GENCConfItems; /* We need to configure address and size of each GENC buffer */
    VDECDD_sDdBufMapInfo **pasGencBuffers = psPicture->psPictResInt->psSeqResInt->pasGencBuffers;
    IMG_UINT32  ui32MemtoRegUsed; /* in bytes */
    IMG_UINT32  ui32i;
    IMG_UINT32 *pui32CtrlAlloc = *ppui32CtrlAllocBuf;
    IMG_UINT32 *pui32MemToReg = (IMG_UINT32 *)psDecPict->psHevcInfo->psDdBufInfo->pvCpuVirt;
    IMG_UINT32  ui32Reg = 0;


    if (ui32CtrlAllocSize < ui32GENCWordsCnt + ui32GENCConfItems)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Buffer for GENC config too small.");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Insert command header for GENC buffers sizes */
    *pui32CtrlAlloc++ = CMD_REGISTER_BLOCK | (ui32GencBufferCount << 16) | (PVDEC_ENTROPY_CR_GENC_BUFFER_SIZE_OFFSET + psRegsOffsets->ui32EntropyOffset);
    for (ui32i = 0; ui32i < ui32GencBufferCount; ui32i++)
    {
        *pui32CtrlAlloc++ = pasGencBuffers[ui32i]->sDdBufInfo.ui32BufSize;
    }

    /* Insert command header for GENC buffers addresses */
    *pui32CtrlAlloc++ = CMD_REGISTER_BLOCK | (ui32GencBufferCount << 16) | (PVDEC_ENTROPY_CR_GENC_BUFFER_BASE_ADDRESS_OFFSET + psRegsOffsets->ui32EntropyOffset);
    for (ui32i = 0; ui32i < ui32GencBufferCount; ui32i++)
    {
        *pui32CtrlAlloc++ = pasGencBuffers[ui32i]->sDdBufInfo.ui32DevVirt;
    }

    /* Insert GENC fragment buffer address */
    *pui32CtrlAlloc++ = CMD_REGISTER_BLOCK | (1 << 16) | (PVDEC_ENTROPY_CR_GENC_FRAGMENT_BASE_ADDRESS_OFFSET + psRegsOffsets->ui32EntropyOffset);
    *pui32CtrlAlloc++ =
        psPicture->psPictResInt->psGencFragmentBuffer->sDdBufInfo.ui32DevVirt;

    /* Return current location in control allocation buffer to caller */
    *ppui32CtrlAllocBuf = pui32CtrlAlloc;

    ui32Reg = 0;
    REGIO_WRITE_FIELD_LITE(ui32Reg,
        MSVDX_CMDS, PVDEC_DISPLAY_PICTURE_SIZE, PVDEC_DISPLAY_PICTURE_WIDTH_MIN1,
        psStrUnit->psPictHdrInfo->sCodedFrameSize.ui32Width - 1);
    REGIO_WRITE_FIELD_LITE(ui32Reg,
        MSVDX_CMDS, PVDEC_DISPLAY_PICTURE_SIZE, PVDEC_DISPLAY_PICTURE_HEIGHT_MIN1,
        psStrUnit->psPictHdrInfo->sCodedFrameSize.ui32Height - 1);

    /* Pvdec operating mode needs to be submitted before any other commands. This will be set in FW.
     * Make sure it's the first command in Mem2Reg buffer. */
    IMG_ASSERT((IMG_UINT32 *)psDecPict->psHevcInfo->psDdBufInfo->pvCpuVirt == pui32MemToReg);

    *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_PVDEC_OPERATING_MODE_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
    *pui32MemToReg++ = 0x0; /* has to be updated in the F/W */

    *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_MC_CACHE_CONFIGURATION_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
    *pui32MemToReg++ = 0x0; /* has to be updated in the F/W */

    *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_PVDEC_DISPLAY_PICTURE_SIZE_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
    *pui32MemToReg++ = ui32Reg;

    *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_PVDEC_CODED_PICTURE_SIZE_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
    *pui32MemToReg++ = ui32Reg;

    /* scaling configuration */
    if (aui32PictCmds[VDECFW_CMD_SCALED_DISPLAY_SIZE])
    {
        *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_PVDEC_SCALED_DISPLAY_SIZE_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_SCALED_DISPLAY_SIZE];

        *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_HORIZONTAL_SCALE_CONTROL_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_HORIZONTAL_SCALE_CONTROL];
        *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_VERTICAL_SCALE_CONTROL_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_VERTICAL_SCALE_CONTROL];

        *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_SCALE_OUTPUT_SIZE_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_SCALE_OUTPUT_SIZE];

        *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_SCALE_HORIZONTAL_CHROMA_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_SCALE_HORIZONTAL_CHROMA];
        *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_SCALE_VERTICAL_CHROMA_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_SCALE_VERTICAL_CHROMA];

        *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_HORIZONTAL_LUMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_0];
        *pui32MemToReg++ = ui32Pipe | (4 + MSVDX_CMDS_HORIZONTAL_LUMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_1];
        *pui32MemToReg++ = ui32Pipe | (8 + MSVDX_CMDS_HORIZONTAL_LUMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_2];
        *pui32MemToReg++ = ui32Pipe | (12 + MSVDX_CMDS_HORIZONTAL_LUMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_3];

        *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_VERTICAL_LUMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_0];
        *pui32MemToReg++ = ui32Pipe | (4 + MSVDX_CMDS_VERTICAL_LUMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_1];
        *pui32MemToReg++ = ui32Pipe | (8 + MSVDX_CMDS_VERTICAL_LUMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_2];
        *pui32MemToReg++ = ui32Pipe | (12 + MSVDX_CMDS_VERTICAL_LUMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_3];

        *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_HORIZONTAL_CHROMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_0];
        *pui32MemToReg++ = ui32Pipe | (4 + MSVDX_CMDS_HORIZONTAL_CHROMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_1];
        *pui32MemToReg++ = ui32Pipe | (8 + MSVDX_CMDS_HORIZONTAL_CHROMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_2];
        *pui32MemToReg++ = ui32Pipe | (12 + MSVDX_CMDS_HORIZONTAL_CHROMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_3];

        *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_VERTICAL_CHROMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_0];
        *pui32MemToReg++ = ui32Pipe | (4 + MSVDX_CMDS_VERTICAL_CHROMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_1];
        *pui32MemToReg++ = ui32Pipe | (8 + MSVDX_CMDS_VERTICAL_CHROMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_2];
        *pui32MemToReg++ = ui32Pipe | (12 + MSVDX_CMDS_VERTICAL_CHROMA_COEFFICIENTS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_3];
    }

    *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_EXTENDED_ROW_STRIDE_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
    *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_EXTENDED_ROW_STRIDE];

    *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_ALTERNATIVE_OUTPUT_CONTROL_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
    *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL];

    *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_ALTERNATIVE_OUTPUT_PICTURE_ROTATION_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
    *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION];

    *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_CHROMA_ROW_STRIDE_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
    *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_CHROMA_ROW_STRIDE];

    /* Setup MEM_TO_REG buffer */
    for (ui32i = 0; ui32i < ui32GencBufferCount; ui32i++)
    {
        *pui32MemToReg++ = ui32Pipe | (PVDEC_VEC_BE_CR_GENC_BUFFER_SIZE_OFFSET + psRegsOffsets->ui32VecBeRegsOffset + ui32i*sizeof(IMG_UINT32));
        *pui32MemToReg++ = pasGencBuffers[ui32i]->sDdBufInfo.ui32BufSize;
        *pui32MemToReg++ = ui32Pipe | (PVDEC_VEC_BE_CR_GENC_BUFFER_BASE_ADDRESS_OFFSET + psRegsOffsets->ui32VecBeRegsOffset + ui32i*sizeof(IMG_UINT32));
        *pui32MemToReg++ = pasGencBuffers[ui32i]->sDdBufInfo.ui32DevVirt;
    }

    *pui32MemToReg++ = ui32Pipe | (PVDEC_VEC_BE_CR_GENC_FRAGMENT_BASE_ADDRESS_OFFSET + psRegsOffsets->ui32VecBeRegsOffset);
    *pui32MemToReg++ = psPicture->psPictResInt->psGencFragmentBuffer->sDdBufInfo.ui32DevVirt;

    *pui32MemToReg++ = ui32Pipe | (PVDEC_VEC_BE_CR_ABOVE_PARAM_BASE_ADDRESS_OFFSET + psRegsOffsets->ui32VecBeRegsOffset);
    *pui32MemToReg++ = psDecPict->psHevcInfo->psDdBufInfo->ui32DevVirt +
        MEM_TO_REG_BUF_SIZE + SLICE_PARAMS_BUF_SIZE;

    *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_LUMA_RECONSTRUCTED_PICTURE_BASE_ADDRESSES_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
    *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_LUMA_RECONSTRUCTED_PICTURE_BASE_ADDRESS];

    *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_CHROMA_RECONSTRUCTED_PICTURE_BASE_ADDRESSES_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
    *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_CHROMA_RECONSTRUCTED_PICTURE_BASE_ADDRESS];

    /* alternative picture configuration */
    if (psDecPict->psAltPict != IMG_NULL)
    {
        *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_VC1_LUMA_RANGE_MAPPING_BASE_ADDRESS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_LUMA_ALTERNATIVE_PICTURE_BASE_ADDRESS];

        *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_VC1_CHROMA_RANGE_MAPPING_BASE_ADDRESS_OFFSET  + psRegsOffsets->ui32VdmcCmdOffset);
        *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_CHROMA_ALTERNATIVE_PICTURE_BASE_ADDRESS];
    }

    *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_AUX_LINE_BUFFER_BASE_ADDRESS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
    *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_AUX_LINE_BUFFER_BASE_ADDRESS];

    *pui32MemToReg++ = ui32Pipe | (MSVDX_CMDS_INTRA_BUFFER_BASE_ADDRESS_OFFSET + psRegsOffsets->ui32VdmcCmdOffset);
    *pui32MemToReg++ = aui32PictCmds[VDECFW_CMD_INTRA_BUFFER_BASE_ADDRESS];

    /* Make sure we fit in buffer */
    ui32MemtoRegUsed =
        (IMG_UINTPTR) pui32MemToReg
        - (IMG_UINTPTR) psDecPict->psHevcInfo->psDdBufInfo->pvCpuVirt;
    IMG_ASSERT(ui32MemtoRegUsed < MEM_TO_REG_BUF_SIZE);

    *pui32MemToRegHostPart = ui32MemtoRegUsed / sizeof(IMG_UINT32);

    UPDATE_DEVICE((psDecPict->psHevcInfo->psDdBufInfo), IMG_TRUE);

    return IMG_SUCCESS;
}
#endif /* HAS_HEVC */

/*!
******************************************************************************

 @Function              translation_PvdecSetupVdecExt

 @Description

 Creates DEVA commands for configuring rendec and writes them into control
 allocation buffer.

 @Output    psVdecExt          : Structure with VDEC extension command to
                                 be set up in this function.

 @Input     psDecPict          : Picture being decoded.

 @Input     aui32PictCmds      : Buffer with commands, in order defined in
                                 VDECFW_ePictureCmds enum.

 @Input     psStrUnit          : Stream unit being submitted.

 @Input     eVidStd            : Video standard of decoded image.

 @Return    IMG_RESULT         : This function returns either IMG_SUCCESS or
                                 an error code.

******************************************************************************/
static IMG_RESULT
translation_PvdecSetupVdecExt(
    VDEC_EXT_CMD          * psVdecExt,
    DECODER_sDecPict      * psDecPict,
    IMG_UINT32            * aui32PictCmds,
    VDECDD_sStrUnit       * psStrUnit,
    VDEC_eVidStd            eVidStd,
    VDECFW_eParserMode      eParserMode
)
{
    IMG_RESULT             ui32Result;
    IMG_UINT32             ui32TransId = psDecPict->ui32TransactionId;
    IMG_BOOL               bTiling, bFakeMTX = IMG_FALSE;
    VDEC_eTileScheme       eTileScheme;
    VDECDD_sDdBufMapInfo   *psPictBuf;

    IMG_ASSERT(psDecPict->psReconPict);

    if (psDecPict->psAltPict)
    {
        psPictBuf = psDecPict->psAltPict->psPictBuf;
    }
    else
    {
        psPictBuf = psDecPict->psReconPict->psPictBuf;
    }
    eTileScheme = psPictBuf->psDdStrContext->sDispPictBuf.sBufConfig.eTileScheme;
    bTiling     = (eTileScheme == VDEC_TS_NONE) ? IMG_FALSE : IMG_TRUE;

    psVdecExt->ui32Cmd = CMD_VDEC_EXT;
    psVdecExt->ui32TransId = ui32TransId;

    ui32Result =
        translation_GetSeqHdr(psStrUnit, psDecPict, &psVdecExt->ui32SeqAddr, bFakeMTX);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    ui32Result =
        translation_GetPPSHdr(psStrUnit, psDecPict, &psVdecExt->ui32PPSAddr, bFakeMTX);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    ui32Result =
        translation_GetSecondPPSHdr(psStrUnit, &psVdecExt->ui32PPS2Addr, bFakeMTX);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    UPDATE_DEVICE((psDecPict->psHdrInfo->psDdBufInfo), !bFakeMTX);
    psVdecExt->ui32HdrAddr =
        GET_HOST_ADDR(psDecPict->psHdrInfo->psDdBufInfo, !bFakeMTX);

    psVdecExt->ui32CtxLoadAddr = translation_GetCtxLoadAddr(psDecPict, bFakeMTX);
    psVdecExt->ui32CtxSaveAddr =
        GET_HOST_ADDR(&psDecPict->psCurPictDecRes->sFwCtxBuf, !bFakeMTX);
    psVdecExt->ui32CtxSize = translation_getCtxSize(eVidStd);
    psVdecExt->ui32BufCtrlAddr =
        GET_HOST_ADDR(&psDecPict->psPictRefRes->sFwCtrlBuf, !bFakeMTX);
    if (psDecPict->psPrevPictDecRes)
    {
        /* Copy the previous firmware context to the current one in case
           picture management fails in firmware. */
        IMG_MEMCPY(psDecPict->psCurPictDecRes->sFwCtxBuf.pvCpuVirt,
                   psDecPict->psPrevPictDecRes->sFwCtxBuf.pvCpuVirt,
                   psVdecExt->ui32CtxSize);
        UPDATE_DEVICE(&(psDecPict->psCurPictDecRes->sFwCtxBuf), !bFakeMTX);
    }

    psVdecExt->ui32LastLumaRecon    =
            aui32PictCmds[VDECFW_CMD_LUMA_RECONSTRUCTED_PICTURE_BASE_ADDRESS];
    psVdecExt->ui32LastChromaRecon  =
            aui32PictCmds[VDECFW_CMD_CHROMA_RECONSTRUCTED_PICTURE_BASE_ADDRESS];

    psVdecExt->ui32ScaledDisplaySize = aui32PictCmds[VDECFW_CMD_SCALED_DISPLAY_SIZE];
    psVdecExt->ui32HorzScaleControl  = aui32PictCmds[VDECFW_CMD_HORIZONTAL_SCALE_CONTROL];
    psVdecExt->ui32VertScaleControl  = aui32PictCmds[VDECFW_CMD_VERTICAL_SCALE_CONTROL];
    psVdecExt->ui32ScaleOutputSize   = aui32PictCmds[VDECFW_CMD_SCALE_OUTPUT_SIZE];

    psVdecExt->ui32IntraBufBaseAddr         = aui32PictCmds[VDECFW_CMD_INTRA_BUFFER_BASE_ADDRESS];
    psVdecExt->ui32IntraBufSizePerPlane     = aui32PictCmds[VDECFW_CMD_INTRA_BUFFER_PLANE_SIZE];
    psVdecExt->ui32AuxLineBufferBaseAddr    = aui32PictCmds[VDECFW_CMD_AUX_LINE_BUFFER_BASE_ADDRESS];
    psVdecExt->ui32AltOutputPictRotation    = aui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION];
    psVdecExt->ui32Chroma2ReconstructedAddr = aui32PictCmds[VDECFW_CMD_CHROMA2_RECONSTRUCTED_PICTURE_BASE_ADDRESS];
    psVdecExt->ui32LumaAltAddr              = aui32PictCmds[VDECFW_CMD_LUMA_ALTERNATIVE_PICTURE_BASE_ADDRESS];
    psVdecExt->ui32ChromaAltAddr            = aui32PictCmds[VDECFW_CMD_CHROMA_ALTERNATIVE_PICTURE_BASE_ADDRESS];
    psVdecExt->ui32Chroma2AltAddr           = aui32PictCmds[VDECFW_CMD_CHROMA2_ALTERNATIVE_PICTURE_BASE_ADDRESS];

    if (eVidStd == VDEC_STD_VC1)
    {
        VXDIO_sDdBufInfo *psVlcIdxTableBufInfo = psDecPict->psVlcIdxTableBufInfo;
        VXDIO_sDdBufInfo *psVlcTablesBufInfo   = psDecPict->psVlcTablesBufInfo;

        psVdecExt->ui32VlcIdxTableSize = psVlcIdxTableBufInfo->ui32BufSize;
        psVdecExt->ui32VlcIdxTableAddr = psVlcIdxTableBufInfo->ui32DevVirt;
        psVdecExt->ui32VlcTablesSize   = psVlcTablesBufInfo->ui32BufSize;
        psVdecExt->ui32VlcTablesAddr   = psVlcTablesBufInfo->ui32DevVirt;
    }
    else
    {
        psVdecExt->ui32VlcIdxTableSize = 0;
        psVdecExt->ui32VlcIdxTableAddr = 0;
        psVdecExt->ui32VlcTablesSize   = 0;
        psVdecExt->ui32VlcTablesAddr   = 0;
    }

    psVdecExt->ui32DisplayPictureSize = aui32PictCmds[VDECFW_CMD_DISPLAY_PICTURE];
    psVdecExt->ui32ParserMode = eParserMode;

    /* MMU Tile configuration */
    // Get the MMUTileConfig from the buffer config in the stream unit
    if(bTiling)
    {
        IMG_UINT32              ui32NumTiledHeaps;
        MMU_sHeapTilingInfo     asTilingInfo[MMU_HEAP_MAX];
        MMU_eHeapId         eHeapId = psPictBuf->eMmuHeapId;
        IMG_BOOL            bByteInterleave =
            psPictBuf->psDdStrContext->sDispPictBuf.sBufConfig.bByteInterleave;
        /* Skip untiled heap */
        IMG_UINT8 ui8TiledHeapNo = eHeapId - MMU_HEAP_IMAGE_BUFFERS_512;

        ui32Result = PVDEC_GetTiledHeaps(eTileScheme, &ui32NumTiledHeaps, asTilingInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        if(ui32NumTiledHeaps > MSVDX_CORE_CR_MMU_TILE_NO_ENTRIES)
        {
            return IMG_ERROR_GENERIC_FAILURE;
        }

        psVdecExt->bMMUTiling         = IMG_TRUE;
        psVdecExt->bMMUTilingScheme1  =
            (eTileScheme == VDEC_TS1_512x8) ? IMG_TRUE : IMG_FALSE;
            psVdecExt->ui32MMUTileCfg     = 0;
            psVdecExt->ui32MMUTileMinAddr = 0;
            psVdecExt->ui32MMUTileMaxAddr = 0;

            REGIO_WRITE_FIELD(psVdecExt->ui32MMUTileCfg,
                IMG_VIDEO_BUS4_MMU, MMU_TILE_CFG, TILE_STRIDE,
                asTilingInfo[ui8TiledHeapNo].ui32HwTileStride);
            REGIO_WRITE_FIELD(psVdecExt->ui32MMUTileCfg,
                IMG_VIDEO_BUS4_MMU, MMU_TILE_CFG, TILE_ENABLE, 1);
            REGIO_WRITE_FIELD(psVdecExt->ui32MMUTileCfg,
                IMG_VIDEO_BUS4_MMU, MMU_TILE_CFG, TILE_128INTERLEAVE, bByteInterleave);

            REGIO_WRITE_FIELD(psVdecExt->ui32MMUTileMinAddr,
                IMG_VIDEO_BUS4_MMU, MMU_TILE_MIN_ADDR, TILE_MIN_ADDR,
                asTilingInfo[ui8TiledHeapNo].ui32StartOffset);

            REGIO_WRITE_FIELD(psVdecExt->ui32MMUTileMaxAddr,
                IMG_VIDEO_BUS4_MMU, MMU_TILE_MAX_ADDR, TILE_MAX_ADDR,
                asTilingInfo[ui8TiledHeapNo].ui32StartOffset +
                asTilingInfo[ui8TiledHeapNo].ui32Size);
        }
    else
    {
        psVdecExt->bMMUTiling = IMG_FALSE;
    }

    /* miscellaneous flags */
    {
        PIXEL_eChromaInterleaved eChromaInterleaved =
            psStrUnit->psSequHdrInfo->sComSequHdrInfo.sPixelInfo.eChromaInterleaved;
        psVdecExt->bChromaInterleaved =
            PIXEL_GET_HW_CHROMA_INTERLEAVED(eChromaInterleaved);
    }

#ifdef HAS_HEVC
    if (psDecPict->psHevcInfo)
    {
        psVdecExt->ui32MemToRegAddr =
            psDecPict->psHevcInfo->psDdBufInfo->ui32DevVirt;
        psVdecExt->ui32SliceParamsAddr =
            psDecPict->psHevcInfo->psDdBufInfo->ui32DevVirt + MEM_TO_REG_BUF_SIZE;
        psVdecExt->ui32SliceParamsSize = SLICE_PARAMS_BUF_SIZE;
    }

    if (VDEC_STD_HEVC == eVidStd)
    {
        VDECDD_sPicture * psPicture = (VDECDD_sPicture*)psStrUnit->pvDdPictData;
        IMG_ASSERT(IMG_NULL != psPicture);
        /* 10-bit packed output format indicator */
        psVdecExt->bPackedFormat = psPicture->sOutputConfig.sPixelInfo.eMemoryPacking == PIXEL_BIT10_MP ? 1: 0;
    }

#endif /* HAS_HEVC */

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              TRANSLATION_CtrlAllocPrepare

******************************************************************************/
IMG_RESULT TRANSLATION_CtrlAllocPrepare(
    VDEC_sStrConfigData       * psStrConfigData,
    VDECDD_sStrUnit           * psStrUnit,
    DECODER_sDecPict          * psDecPict,
    const VXD_sCoreProps      * psCoreProps,
    IMG_BOOL                    bFakeMTX,
    DECODER_sRegsOffsets      * psRegsOffsets
)
{
    IMG_RESULT             ui32Result;
    IMG_UINT32           * pui32CmdBuf;
    IMG_UINT32             ui32HdrSize = 0;
    IMG_UINT32             aui32PictCmds[VDECFW_CMD_MAX];
    VDECFW_eCodecType      eCodec;
    VXD_sBuffers           sBuffers;
    VDEC_EXT_CMD         * psVdecExt;
    VDECFW_eParserMode     eParserMode;

    VXDIO_sDdBufInfo     * psBatchMsgBufInfo = psDecPict->psBatchMsgInfo->psDdBufInfo;
    LST_T *                psDecPictSegList = &psDecPict->sDecPictSegList;

    IMG_UINT32             ui32MemToRegHostPart = 0; /* Number of dwords written to MemToReg buffer in this function */

    IMG_UINTPTR            pui32CtrlAlloc = (IMG_UINTPTR)psBatchMsgBufInfo->pvCpuVirt;
    IMG_UINTPTR            pui32CtrlAllocEnd = pui32CtrlAlloc + psBatchMsgBufInfo->ui32BufSize;

    VDECDD_sPicture      * psPicture = (VDECDD_sPicture*)psStrUnit->pvDdPictData;

    IMG_MEMSET(aui32PictCmds, 0, sizeof(aui32PictCmds));

    IMG_ASSERT(CTRL_ALLOC_MAX_SEGMENT_SIZE <= psBatchMsgBufInfo->ui32BufSize);
    IMG_MEMSET(psBatchMsgBufInfo->pvCpuVirt, 0, psBatchMsgBufInfo->ui32BufSize);

    /* Construct transaction based on new picture. */
    IMG_ASSERT(psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_START);

    /* Obtain picture data. */
    psPicture = (VDECDD_sPicture*)psStrUnit->pvDdPictData;
    if (psPicture->psPictResInt && psPicture->psPictResInt->psDdPictBuf)
    {
        if ((VDEC_STD_VC1 == psStrConfigData->eVidStd) &&
            psStrUnit->psSequHdrInfo->sComSequHdrInfo.bPostProcessing &&
            !psStrUnit->psPictHdrInfo->bPostProcessing &&
            !psCoreProps->abScalingSupport[0] &&
            psPicture->sOutputConfig.eRotMode == VDEC_ROTATE_0)
        {
            // IPGear30189: Only generate reconstructed (in-loop) buffer when
            // post processing feature is disabled for picture. The Plant will
            // have allocated internal buffers to match display so that display
            // can be used for reference.
            psDecPict->psReconPict = &psPicture->sDisplayPictBuf;
        }
        else
        {
            psDecPict->psReconPict = psPicture->psPictResInt->psDdPictBuf;
            psDecPict->psAltPict = &psPicture->sDisplayPictBuf;
        }
    }
    else
    {
        psDecPict->psReconPict = &psPicture->sDisplayPictBuf;
    }

    ui32Result = translation_GetCodec(psStrConfigData->eVidStd, &eCodec);
    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Failed to translate standard into firmware syntax.");
        return ui32Result;
    }

    ui32Result = translation_SetupStdHeader(psStrConfigData,
                                            psDecPict,
                                            psStrUnit,
                                            bFakeMTX,
                                            &ui32HdrSize,
                                            psPicture,
                                            aui32PictCmds,
                                            &eParserMode);
    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Failed to setup standard specific header.");
        return ui32Result;
    }

    sBuffers.psReconPict = psDecPict->psReconPict;
    sBuffers.psAltPict = psDecPict->psAltPict;

    /* Set pipe offsets to device buffers */
    if(psStrConfigData->eVidStd == VDEC_STD_HEVC)
    {
        /* FW in multipipe requires this buffers to be allocated per stream */
        sBuffers.ui32IntraBufPipeOffset = 0;
        sBuffers.ui32AuxLineBufPipeOffset = 0;
        if (psPicture->psPictResInt && psPicture->psPictResInt->psSeqResInt && 
            psPicture->psPictResInt->psSeqResInt->psIntraBuffer &&
            psPicture->psPictResInt->psSeqResInt->psAuxBuffer)
        {
            sBuffers.psIntraBufInfo = &psPicture->psPictResInt->psSeqResInt->psIntraBuffer->sDdBufInfo;
            sBuffers.psAuxLineBufInfo = &psPicture->psPictResInt->psSeqResInt->psAuxBuffer->sDdBufInfo;
        }
    }
    else
    {
    sBuffers.psIntraBufInfo = psDecPict->psIntraBufInfo;
    sBuffers.psAuxLineBufInfo = psDecPict->psAuxLineBufInfo;
        sBuffers.ui32IntraBufPipeOffset = (sBuffers.psIntraBufInfo->ui32BufSize / psCoreProps->ui32NumPixelPipes) * (psDecPict->ui8Pipe - 1);
        sBuffers.ui32AuxLineBufPipeOffset = (sBuffers.psAuxLineBufInfo->ui32BufSize / psCoreProps->ui32NumPixelPipes) * (psDecPict->ui8Pipe - 1);
    }

    if (psPicture->psPictResInt && psPicture->psPictResInt->psSeqResInt && psPicture->psPictResInt->psSeqResInt->psMSBBuffer)
    {
        sBuffers.psMSBBufInfo = &psPicture->psPictResInt->psSeqResInt->psMSBBuffer->sDdBufInfo;
    }

    /* Prepare Reconstructed Picture Configuration
     * Note: we are obtaining values of registers prepared basing on header files generated from MSVDX *dev files.
     * That's allowed, as layout of registers: MSVDX_CMDS_OPERATING_MODE, MSVDX_CMDS_EXTENDED_ROW_STRIDE,
     * MSVDX_CMDS_ALTERNATIVE_OUTPUT_PICTURE_ROTATION, MSVDX_CMDS_CHROMA_ROW_STRIDE is the same for both
     * MSVDX and PVDEC. */
    ui32Result = VXD_SetReconPictCmds(psStrUnit,
                                      psStrConfigData,
                                      &psPicture->sOutputConfig,
                                      psCoreProps,
                                      &sBuffers,
                                      aui32PictCmds);
    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Failed to preapre reconstructed picture commands.");
        return ui32Result;
    }

    /* Alternative Picture Configuration */
    if (psDecPict->psAltPict)
    {
        psDecPict->bTwoPass = psPicture->sOutputConfig.bForceOold;
        sBuffers.bTwoPass = psDecPict->bTwoPass;

        /* Alternative Picture Configuration
         * Note: we are obtaining values of registers prepared basing on header files generated from MSVDX *dev files.
         * That's allowed, as layout of registers: MSVDX_CMDS_OPERATING_MODE, MSVDX_CMDS_EXTENDED_ROW_STRIDE,
         * MSVDX_CMDS_ALTERNATIVE_OUTPUT_PICTURE_ROTATION, MSVDX_CMDS_CHROMA_ROW_STRIDE is the same for both
         * MSVDX and PVDEC. */
        /* Configure second buffer for out-of-loop processing (e.g. scaling etc.). */
        ui32Result = VXD_SetAltPictCmds(psStrUnit,
                                        psStrConfigData,
                                        &psPicture->sOutputConfig,
                                        psCoreProps,
                                        &sBuffers,
                                        aui32PictCmds);
        if (IMG_SUCCESS != ui32Result)
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Failed to preapre alternative picture commands.");
            return ui32Result;
        }
    }

    /* Setup initial simple bitstream configuration to be used by parser task */
    pui32CmdBuf = (IMG_UINT32 *)pui32CtrlAlloc;
    ui32Result = translation_PvdecAddDmaTransfers(psDecPictSegList,
                                                  psDecPict->psEndBytesBufInfo,
                                                  &pui32CmdBuf,
                                                  (pui32CtrlAllocEnd - (IMG_UINTPTR)pui32CmdBuf)/sizeof(IMG_UINT32),
                                                  psDecPict);
    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Failed to setup initial bistream DMA configuration.");
        return ui32Result;
    }

    if ((IMG_UINTPTR)(pui32CmdBuf + (sizeof(CTRL_ALLOC_HEADER) + sizeof(VDEC_EXT_CMD))/sizeof(IMG_UINT32)) >=
         pui32CtrlAllocEnd)
    {

        REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Failed to add control allocation header and VDEC extension.");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Setup regular control allocation message. Start with control allocation header*/
    translation_PvdecSetupCtrlHdr((CTRL_ALLOC_HEADER *)pui32CmdBuf, aui32PictCmds);
    /* Setup additional params for VP8 */
#ifdef HAS_VP8
    if (psStrConfigData->eVidStd == VDEC_STD_VP8)
    {
        translation_PvdecSetupVP8AddParams((CTRL_ALLOC_HEADER *)pui32CmdBuf, psDecPict);
    }
#endif
#ifdef HAS_VP6
    if (psStrConfigData->eVidStd == VDEC_STD_VP6)
    {
        translation_PvdecSetupVP6AddParams((CTRL_ALLOC_HEADER *)pui32CmdBuf, psDecPict);
    }
#endif
    pui32CmdBuf += sizeof(CTRL_ALLOC_HEADER)/sizeof(IMG_UINT32);

    /* Reserve space for VDEC extension command and fill it */
    psVdecExt = (VDEC_EXT_CMD *)pui32CmdBuf;
    pui32CmdBuf += sizeof(VDEC_EXT_CMD)/sizeof(IMG_UINT32);
    ui32Result = translation_PvdecSetupVdecExt(psVdecExt,
                                               psDecPict,
                                               aui32PictCmds,
                                               psStrUnit,
                                               psStrConfigData->eVidStd,
                                               eParserMode);
    if (IMG_SUCCESS != ui32Result)
    {
        REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Failed to setup VDEC extension command.");
        return ui32Result;
    }
    psVdecExt->ui32HdrSize = ui32HdrSize;

    UPDATE_DEVICE((&psDecPict->psCurPictDecRes->sFwCtxBuf), IMG_TRUE);

    /* Add VLC tables to control allocation, skip when VC1 */
    if (psStrConfigData->eVidStd != VDEC_STD_VC1
        && psDecPict->psVlcIdxTableBufInfo != IMG_NULL
        && psDecPict->psVlcIdxTableBufInfo->pvCpuVirt != IMG_NULL)
    {
        IMG_UINT16 * pui16VlcIdxTable = (IMG_UINT16 *)psDecPict->psVlcIdxTableBufInfo->pvCpuVirt;
        /* Get count of elements in VLC idx table. Each element is made of 3 IMG_UINT16, see e.g. mpeg2_idx.c */
        IMG_UINT32 ui32VlcIdxCount = psDecPict->psVlcIdxTableBufInfo->ui32BufSize / (3*sizeof(IMG_UINT16));

        /* Add command to DMA VLC */
        ui32Result = translation_PvdecSetupVlcDma(psDecPict->psVlcTablesBufInfo,
                                                  &pui32CmdBuf,
                                                  (pui32CtrlAllocEnd - (IMG_UINTPTR)pui32CmdBuf)/sizeof(IMG_UINT32));
        if (IMG_SUCCESS != ui32Result)
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Failed to setup VLC DMA firmware command.");
            return ui32Result;
        }

        /* Add command to configure VLC tables */
        ui32Result = translation_PvdecSetupVlcTables((IMG_UINT16 (*)[3])pui16VlcIdxTable,
                                                     ui32VlcIdxCount,
                                                     &pui32CmdBuf,
                                                     (pui32CtrlAllocEnd - (IMG_UINTPTR)pui32CmdBuf)/sizeof(IMG_UINT32),
                                                     psRegsOffsets->ui32VecOffset);
        if (IMG_SUCCESS != ui32Result)
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Failed to setup VLC IDX firmware commands.");
            return ui32Result;
        }
    }

    /* Setup commands for standards other than HEVC */
    if (psStrConfigData->eVidStd != VDEC_STD_HEVC)
    {
        ui32Result = translation_PvdecSetupCommands(aui32PictCmds,
                &pui32CmdBuf,
                (pui32CtrlAllocEnd - (IMG_UINTPTR)pui32CmdBuf)/sizeof(IMG_UINT32),
                psRegsOffsets->ui32VdmcCmdOffset);
        if (IMG_SUCCESS != ui32Result)
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Failed to setup VDMC & VDEB firmware commands.");
            return ui32Result;
        }
    }

    /* Setup commands for HEVC */
    psVdecExt->ui32MemToRegSize = 0;
#ifdef HAS_HEVC
    if (psStrConfigData->eVidStd == VDEC_STD_HEVC)
    {

        ui32Result = translation_PvdecSetupHEVCCommands(
                psPicture,
                psDecPict,
                psStrUnit,
                psRegsOffsets,
                &pui32CmdBuf,
                (pui32CtrlAllocEnd - (IMG_UINTPTR)pui32CmdBuf)/sizeof(IMG_UINT32),
                &ui32MemToRegHostPart,
                aui32PictCmds);
        if (IMG_SUCCESS != ui32Result)
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_ERR, "Failed to setup VDMC & VDEB firmware commands.");
            return ui32Result;
        }

        /* Set size of MemToReg buffer in VDEC extension command */
        IMG_ASSERT(MEM_TO_REG_BUF_SIZE < (MEM2REG_SIZE_BUF_TOTAL_MASK >> MEM2REG_SIZE_BUF_TOTAL_SHIFT));
        IMG_ASSERT(ui32MemToRegHostPart < (MEM2REG_SIZE_HOST_PART_MASK >> MEM2REG_SIZE_HOST_PART_SHIFT));
        psVdecExt->ui32MemToRegSize =
            (MEM_TO_REG_BUF_SIZE << MEM2REG_SIZE_BUF_TOTAL_SHIFT) |
            (ui32MemToRegHostPart << MEM2REG_SIZE_HOST_PART_SHIFT);
    }
#endif /* HAS_HEVC */

    /* Finally mark end of commands */
    *(pui32CmdBuf++) = CMD_COMPLETION;

#if 0
    /* Print message for debugging */
    {
        int i;
        for (i = 0; i < ((IMG_UINTPTR)pui32CmdBuf - pui32CtrlAlloc)/sizeof(IMG_UINT32); i++)
        {
            REPORT(REPORT_MODULE_DECODER, REPORT_NOTICE, "pui32CtrlAlloc[%d] == %08x", i, ((IMG_UINT32 *)pui32CtrlAlloc)[i]);
        }
    }
#endif

    /* Transfer control allocation command to device memory */
    UPDATE_DEVICE((psBatchMsgBufInfo), IMG_TRUE);

    psDecPict->ui32CtrlAllocBytes = ((IMG_UINTPTR)pui32CmdBuf - pui32CtrlAlloc);
    psDecPict->ui32OperatingMode = aui32PictCmds[VDECFW_CMD_OPERATING_MODE];

    return IMG_SUCCESS;
};
#endif /* def VDEC_USE_PVDEC */
