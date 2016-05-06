/*!
 *****************************************************************************
 *
 * @File       vxd_int.c
 * @Description    Low-level MSVDX interface component
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

#include "img_defs.h"
#include "vxd_int.h"
#include "vdecfw.h"

#ifdef SECURE_MEDIA_SUPPORT
    #include "secureapi.h"
    #include "vxd_secure_msg.h"
#else
    #include "tal.h"
    #include "vxd_io.h"
#endif

#ifdef VDEC_USE_PVDEC
#include "hwdefs/msvdx_cmds.h"
#else /* ndef VDEC_USE_PVDEC */
#include "msvdx_cmds_io2.h"
#endif /* ndef VDEC_USE_PVDEC */

#ifdef USE_REAL_FW
    #include "vdecfw_bin.h"
#endif


/*
******************************************************************************
 Cache Config
 ******************************************************************************/
#define MSVDX_CACHE_REF_OFFSET_V100     (72L)
#define MSVDX_CACHE_ROW_OFFSET_V100     (4L)

#define MSVDX_CACHE_REF_OFFSET_V550     (144L)
#define MSVDX_CACHE_ROW_OFFSET_V550     (8L)


/*!
******************************************************************************
 This enum defines an MSVDX specific parameter
*****************************************************************************/
typedef enum
{
    VDEC_MSVDX_ASYNC_NORMAL,              //!< VDMC and VDEB
    VDEC_MSVDX_ASYNC_VDMC,                //!< VDMC only
    VDEC_MSVDX_ASYNC_VDEB,                //!< VDEB only

} VDEC_eMsvdxAsyncMode;


/*!
******************************************************************************
 This type defines the Codec Mode and should be ordered as #VDEC_eVidStd.
*****************************************************************************/
static IMG_UINT32 aui32MsvdxCodecMode[VDEC_STD_MAX] =
{
    -1,     //!< Invalid
     3,     //!< MPEG2
     4,     //!< MPEG4
     4,     //!< H263
     1,     //!< H264
     2,     //!< VC1
     5,     //!< AVS
     8,     //!< RealVideo (8)
     0,     //!< JPEG
     10,    //!< On2 VP6
     11,    //!< On2 VP8
     4,     //!< Sorenson
     12,    //!< HEVC
};


/*!
******************************************************************************
 This struct contains Scaler parameters prepared for hardware
******************************************************************************/
typedef struct
{
    IMG_UINT32  aui32CmdHorizLumaCoeff[VDECFW_NUM_SCALE_COEFFS];    //!< HORIZONTAL_LUMA_COEFFICIENTS
    IMG_UINT32  aui32CmdVertLumaCoeff[VDECFW_NUM_SCALE_COEFFS];     //!< VERTICAL_LUMA_COEFFICIENTS
    IMG_UINT32  aui32CmdHorizChromaCoeff[VDECFW_NUM_SCALE_COEFFS];  //!< HORIZONTAL_CHROMA_COEFFICIENTS
    IMG_UINT32  aui32CmdVertChromaCoeff[VDECFW_NUM_SCALE_COEFFS];   //!< VERTICAL_CHROMA_COEFFICIENTS

} MSVDX_sScalerCoeffCmds;


/*
******************************************************************************

 @Function              msvdx_GetProfile

 @Description

 Obtains the hardware defined video profile.

 @Input     eVidStd :   Width of the reference picture

 @Input     ui32StdProfile :   Height of the reference picture

 @Return    IMG_UINT32 : Video Profile as defined by hardware.

******************************************************************************/
static IMG_UINT32
vxd_GetProfile(
    VDEC_eVidStd  eVidStd,
    IMG_UINT32    ui32StdProfile
)
{
    IMG_UINT32  ui32Profile = 0;

    switch (eVidStd)
    {
#ifdef HAS_AVS
        case VDEC_STD_AVS:
            ui32Profile = 0;
            break;
#endif /* HAS_AVS */
#ifdef HAS_VC1
        case VDEC_STD_VC1:
            if (ui32StdProfile == VC1_PROFILE_SIMPLE)
            {
                ui32Profile = 0;
            }
            else if (ui32StdProfile == VC1_PROFILE_MAIN)
            {
                ui32Profile = 1;
            }
            else if (ui32StdProfile == VC1_PROFILE_ADVANCED)
            {
                ui32Profile = 2;
            }
            else
            {
                IMG_ASSERT(IMG_FALSE);
            }
            break;
#endif /* HAS_VC1 */

#ifdef HAS_H264
        case VDEC_STD_H264:
            switch (ui32StdProfile)
            {
            case H264_PROFILE_BASELINE:
                ui32Profile = 0;
                break;

            /* Extended may be attempted as Baseline or Main depending on the constraint_set_flags */
            case H264_PROFILE_EXTENDED:
            case H264_PROFILE_MAIN:
                ui32Profile = 1;
                break;

            case H264_PROFILE_HIGH:
            case H264_PROFILE_HIGH444:
            case H264_PROFILE_HIGH422:
            case H264_PROFILE_HIGH10:
            case H264_PROFILE_CAVLC444:
            case H264_PROFILE_MVC_HIGH:
            case H264_PROFILE_STEREO_HIGH:
                ui32Profile = 2;
                break;

            default:
                ui32Profile = 2;
                IMG_ASSERT(IMG_FALSE);
                break;
            }
            break;
#endif /* HAS_H264 */
#ifdef HAS_VP6
        case VDEC_STD_VP6:
            ui32Profile = 0;
            break;
#endif /* HAS_VP6 */
#ifdef HAS_VP8
        case VDEC_STD_VP8:
            ui32Profile = ui32StdProfile;
            break;
#endif /* HAS_VP8 */
#ifdef HAS_MPEG2
        case VDEC_STD_MPEG2:
            ui32Profile = 1;
            break;
#endif /* HAS_MPEG2 */
        default:
            ui32Profile = 0;
            break;
    }

    return ui32Profile;
}


/*
******************************************************************************

 @Function              scaler_ApplyRestrictions

******************************************************************************/
static IMG_RESULT
scaler_ApplyRestrictions(
    const SCALER_sConfig  * psScalerConfig,
    SCALER_sParams        * psParams
)
{
    const VXD_sCoreProps * psCoreProps = psScalerConfig->psCoreProps;

    // When display picture height is 2048, vertical start position must
    // be set to zero to avoid overflow when calculating last pixel position (BRN29870).
    if (psCoreProps->BRN29870 && psScalerConfig->ui32ReconHeight == 2048)
    {
        psParams->iVertStartPos = 0;
    }

    return IMG_SUCCESS;
}


#ifdef VDEC_USE_PVDEC_COMPATIBILITY
/*!
******************************************************************************

 @Function              VXD_IsSupportedByAtLeastOnePipe

******************************************************************************/
static IMG_BOOL vxd_IsSupportedByAtLeastOnePipe(
    const IMG_BOOL *aFeatures,
    IMG_UINT32 ui32NumPipes
)
{
    IMG_UINT32 i32;
    IMG_ASSERT(aFeatures);
    IMG_ASSERT(ui32NumPipes <= VDEC_MAX_PIXEL_PIPES);

    for(i32 = 0; i32 < ui32NumPipes; i32++)
    {
        if(aFeatures[i32])
        {
            return IMG_TRUE;
        }
    }

    return IMG_FALSE;
}
#endif /* VDEC_USE_PVDEC_COMPATIBILITY */


/*!
******************************************************************************

 @Function              VXD_SetReconPictCmds

******************************************************************************/
IMG_RESULT
VXD_SetReconPictCmds(
    const VDECDD_sStrUnit        * psStrUnit,
    const VDEC_sStrConfigData    * psStrConfigData,
    const VDEC_sStrOutputConfig  * psOutputConfig,
    const VXD_sCoreProps         * psCoreProps,
    const VXD_sBuffers           * psBuffers,
    IMG_UINT32                   * pui32PictCmds
)
{
    PIXEL_sPixelInfo  * psPixelInfo;
    IMG_UINT32          ui32RowStrideCode;
    IMG_UINT32          ui32CacheRefOffset;
    IMG_UINT32          ui32CacheRowOffset;
    IMG_BOOL            bEnableAuxLineBuf = IMG_TRUE;

    IMG_UINT32          ui32CodedHeight;
    IMG_UINT32          ui32CodedWidth;
    IMG_UINT32          ui32DisplayHeight;
    IMG_UINT32          ui32DisplayWidth;

#if 0
    TRANSLATION_sRprParams    sRprParams;
    IMG_BOOL                  bRPR = IMG_FALSE;
#endif

    // Ensure that a reconstructed buffer has been provided.
    IMG_ASSERT(psBuffers->psReconPict);

    // Display and coded picture size commands are not considered by H/W when decoding JPEG.
    // Fields of VDECFW_CMD_DISPLAY_PICTURE and VDECFW_CMD_CODED_PICTURE commands are 12bit,
    // and JPEG size can be up to 32k, so it wouldn't fit. Set those sizes to 0 to avoid assert.
#ifdef HAS_JPEG
    if (psStrConfigData->eVidStd == VDEC_STD_JPEG)
    {
        ui32DisplayHeight = 0;
        ui32DisplayWidth = 0;
        ui32CodedHeight = 0;
        ui32CodedWidth = 0;
    }
    else
#endif /* HAS_JPEG */
    {
        ui32CodedHeight = VDEC_ALIGN_SIZE(psStrUnit->psPictHdrInfo->sCodedFrameSize.ui32Height,
                                          (psStrUnit->psPictHdrInfo->bField) ? 2*VDEC_MB_DIMENSION : VDEC_MB_DIMENSION);
        ui32CodedHeight -= 1;   // Hardware field is coded size - 1

        ui32CodedWidth = VDEC_ALIGN_SIZE(psStrUnit->psPictHdrInfo->sCodedFrameSize.ui32Width, VDEC_MB_DIMENSION);
        ui32CodedWidth -= 1;    // Hardware field is coded size - 1

        ui32DisplayHeight = psStrUnit->psPictHdrInfo->sDispInfo.sEncDispRegion.ui32Height +  psStrUnit->psPictHdrInfo->sDispInfo.sEncDispRegion.ui32TopOffset - 1;
        ui32DisplayWidth = psStrUnit->psPictHdrInfo->sDispInfo.sEncDispRegion.ui32Width + psStrUnit->psPictHdrInfo->sDispInfo.sEncDispRegion.ui32LeftOffset - 1;
    }

    // Display picture size (DISPLAY_PICTURE)
    //The display to be written is not the actual video size to be displayed but a number that has to differ from
    //the coded pixel size by less than 1MB (coded_size-display_size <= 0x0F). Because H264 can have a different
    //display size, we need to check and write the coded_size again in the display_size register if this condition
    //is not fulfilled.
    // For HEVC "PVDEC Display Picture Size" is used

    if (psStrConfigData->eVidStd != VDEC_STD_HEVC)
    {
        if( VDEC_STD_VC1 != psStrConfigData->eVidStd && ( ( ui32CodedHeight - ui32DisplayHeight ) > 0x0F ))
        {
            REGIO_WRITE_FIELD_LITE(pui32PictCmds[VDECFW_CMD_DISPLAY_PICTURE],
                    MSVDX_CMDS, DISPLAY_PICTURE_SIZE, DISPLAY_PICTURE_HEIGHT,
                    ui32CodedHeight);
        }
        else
        {
            REGIO_WRITE_FIELD_LITE(pui32PictCmds[VDECFW_CMD_DISPLAY_PICTURE],
                    MSVDX_CMDS, DISPLAY_PICTURE_SIZE, DISPLAY_PICTURE_HEIGHT,
                    ui32DisplayHeight);
        }

        if( VDEC_STD_VC1 != psStrConfigData->eVidStd && ( ( ui32CodedWidth - ui32DisplayWidth ) > 0x0F))
        {
            REGIO_WRITE_FIELD_LITE(pui32PictCmds[VDECFW_CMD_DISPLAY_PICTURE],
                    MSVDX_CMDS, DISPLAY_PICTURE_SIZE, DISPLAY_PICTURE_WIDTH,
                    ui32CodedWidth);
        }
        else
        {
            REGIO_WRITE_FIELD_LITE(pui32PictCmds[VDECFW_CMD_DISPLAY_PICTURE],
                    MSVDX_CMDS, DISPLAY_PICTURE_SIZE, DISPLAY_PICTURE_WIDTH,
                    ui32DisplayWidth);
        }

        // Coded picture size (CODED_PICTURE), for HEVC "PVDEC Coded Picture Size" is used
        REGIO_WRITE_FIELD_LITE(pui32PictCmds[VDECFW_CMD_CODED_PICTURE],
            MSVDX_CMDS, CODED_PICTURE_SIZE, CODED_PICTURE_HEIGHT,
            ui32CodedHeight);
        REGIO_WRITE_FIELD_LITE(pui32PictCmds[VDECFW_CMD_CODED_PICTURE],
            MSVDX_CMDS, CODED_PICTURE_SIZE, CODED_PICTURE_WIDTH,
            ui32CodedWidth);
    }

    // Real video might have reference picture resampling
    if (psStrConfigData->eVidStd == VDEC_STD_REAL)
    {
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_EXTENDED_ROW_STRIDE],
            MSVDX_CMDS, EXTENDED_ROW_STRIDE, RPR_ROW_STRIDE,
            psBuffers->psReconPict->sRendInfo.asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride >> 6);
    }

#ifdef VDEC_USE_PVDEC_COMPATIBILITY
    /* For standards where dpb_diff != 1 and chroma format != 420
     * ui32CacheRefOffset has to be calculated in the F/W. */
    if (psStrConfigData->eVidStd != VDEC_STD_HEVC &&
        psStrConfigData->eVidStd != VDEC_STD_H264)
    {
        IMG_UINT32 ui32Log2_size, ui32CacheSize, ui32LumaSize;
        IMG_BOOL bHevcSupported, bHevc444Supported = IMG_FALSE;

        bHevcSupported = vxd_IsSupportedByAtLeastOnePipe(psCoreProps->abHEVC,
            psCoreProps->ui32NumPixelPipes);

        if (bHevcSupported)
        {
            bHevc444Supported =
                psCoreProps->asVidStdProps[VDEC_STD_HEVC].eMaxChromaFormat ==
                PIXEL_FORMAT_444 ? IMG_TRUE : IMG_FALSE;
        }

        ui32Log2_size = 9 + (bHevcSupported ? 1 : 0) + (bHevc444Supported ? 1 : 0);
        ui32CacheSize = 3 << ui32Log2_size;
        ui32LumaSize = (ui32CacheSize * 2) / 3;
        ui32CacheRefOffset = (ui32LumaSize * 15) / 32;
        ui32CacheRefOffset = (ui32CacheRefOffset + 7) & (~7);
        ui32CacheRowOffset = 0x0C;

        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_MC_CACHE_CONFIGURATION],
            MSVDX_CMDS, MC_CACHE_CONFIGURATION, CONFIG_REF_CHROMA_ADJUST, 1);
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_MC_CACHE_CONFIGURATION],
            MSVDX_CMDS, MC_CACHE_CONFIGURATION, CONFIG_REF_OFFSET,
            ui32CacheRefOffset);
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_MC_CACHE_CONFIGURATION],
            MSVDX_CMDS, MC_CACHE_CONFIGURATION, CONFIG_ROW_OFFSET,
            ui32CacheRowOffset);
    }
#else /* not VDEC_USE_PVDEC_COMPATIBILITY */
    if (psCoreProps->bNewCacheSettings)
    {
        ui32CacheRefOffset = MSVDX_CACHE_REF_OFFSET_V550;
        ui32CacheRowOffset = MSVDX_CACHE_ROW_OFFSET_V550;

    }
    else
    {
        ui32CacheRefOffset = MSVDX_CACHE_REF_OFFSET_V100;
        ui32CacheRowOffset = MSVDX_CACHE_ROW_OFFSET_V100;
    }

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_MC_CACHE_CONFIGURATION],
        MSVDX_CMDS, MC_CACHE_CONFIGURATION, CONFIG_REF_OFFSET,
        ui32CacheRefOffset);
    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_MC_CACHE_CONFIGURATION],
        MSVDX_CMDS, MC_CACHE_CONFIGURATION, CONFIG_ROW_OFFSET,
        ui32CacheRowOffset);
#endif /* VDEC_USE_PVDEC_COMPATIBILITY */

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
        MSVDX_CMDS, OPERATING_MODE, CODEC_MODE,
        aui32MsvdxCodecMode[psStrConfigData->eVidStd]);
    if (psStrConfigData->eVidStd == VDEC_STD_REAL)
    {
        if (psStrUnit->psSequHdrInfo->sComSequHdrInfo.ui32CodecProfile == RV_VIDEO_30)
        {
            REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE], MSVDX_CMDS, OPERATING_MODE, CODEC_MODE, 0x8);
        }
        if (psStrUnit->psSequHdrInfo->sComSequHdrInfo.ui32CodecProfile == RV_VIDEO_40)
        {
            REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE], MSVDX_CMDS, OPERATING_MODE, CODEC_MODE, 0x9);
        }
    }

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
        MSVDX_CMDS, OPERATING_MODE, CODEC_PROFILE,
        vxd_GetProfile(psStrConfigData->eVidStd, psStrUnit->psSequHdrInfo->sComSequHdrInfo.ui32CodecProfile));

    psPixelInfo = &psStrUnit->psSequHdrInfo->sComSequHdrInfo.sPixelInfo;
    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
        MSVDX_CMDS, OPERATING_MODE, CHROMA_FORMAT, psStrUnit->psSequHdrInfo->sComSequHdrInfo.bSeparateChromaPlanes ? 0 : psPixelInfo->bChromaFormat);
        //MSVDX_CMDS, OPERATING_MODE, CHROMA_FORMAT,
        //psPixelInfo->bChromaFormat);

    if (psStrConfigData->eVidStd != VDEC_STD_JPEG)
    {
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_EXT_OP_MODE],
                MSVDX_CMDS, EXT_OP_MODE, CHROMA_FORMAT_IDC, psStrUnit->psSequHdrInfo->sComSequHdrInfo.bSeparateChromaPlanes ? 0 : PIXEL_GET_HW_CHROMA_FORMAT_IDC(psPixelInfo->eChromaFormatIdc));
                //MSVDX_CMDS, EXT_OP_MODE, CHROMA_FORMAT_IDC,
                //PIXEL_GET_HW_CHROMA_FORMAT_IDC(psPixelInfo->eChromaFormatIdc));

        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_EXT_OP_MODE],
            MSVDX_CMDS, EXT_OP_MODE, MEMORY_PACKING,
            psOutputConfig->sPixelInfo.eMemoryPacking == PIXEL_BIT10_MP ? 1 : 0);

        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_EXT_OP_MODE],
            MSVDX_CMDS, EXT_OP_MODE, BIT_DEPTH_LUMA_MINUS8,
            psPixelInfo->ui32BitDepthY - 8);

        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_EXT_OP_MODE],
            MSVDX_CMDS, EXT_OP_MODE, BIT_DEPTH_CHROMA_MINUS8,
            psPixelInfo->ui32BitDepthC - 8);
    }
    else
    {
        pui32PictCmds[VDECFW_CMD_EXT_OP_MODE] = 0;
    }

    if (psStrConfigData->eVidStd != VDEC_STD_JPEG)
    {
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
            MSVDX_CMDS, OPERATING_MODE, CHROMA_INTERLEAVED,
            PIXEL_GET_HW_CHROMA_INTERLEAVED(psOutputConfig->sPixelInfo.eChromaInterleaved));
    }
#ifdef HAS_AVS
    if (psStrConfigData->eVidStd == VDEC_STD_AVS)
    {
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
            MSVDX_CMDS, OPERATING_MODE, ASYNC_MODE, VDEC_MSVDX_ASYNC_NORMAL);
    }
    else
#endif /* HAS_AVS */
#ifdef HAS_REAL
    if (psStrConfigData->eVidStd == VDEC_STD_REAL)
    {
            REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
            MSVDX_CMDS, OPERATING_MODE, DEBLOCK_STRENGTH,
            0);
    }
    else
#endif /* HAS_REAL */
#ifdef HAS_MPEG4
    if (psStrConfigData->eVidStd == VDEC_STD_MPEG4 ||
        psStrConfigData->eVidStd == VDEC_STD_H263 ||
        psStrConfigData->eVidStd == VDEC_STD_SORENSON)
    {
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
            MSVDX_CMDS, OPERATING_MODE, ASYNC_MODE, VDEC_MSVDX_ASYNC_VDMC);
    }
    else
#endif /* HAS_MPEG4 */
#ifdef HAS_VP6
    if (psStrConfigData->eVidStd == VDEC_STD_VP6)
    {
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
        MSVDX_CMDS, OPERATING_MODE, ASYNC_MODE, VDEC_MSVDX_ASYNC_VDMC)
    }
    else
#endif /* HAS_VP6 */
#ifdef HAS_VP8
    if (psStrConfigData->eVidStd == VDEC_STD_VP8)
    {
    }
    else
#endif /* HAS_VP8 */
#ifdef HAS_JPEG
    if (psStrConfigData->eVidStd == VDEC_STD_JPEG)
    {
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
            MSVDX_CMDS, OPERATING_MODE, ASYNC_MODE, VDEC_MSVDX_ASYNC_VDMC)
    }
    else
#endif /* HAS_JPEG */
#ifdef HAS_MPEG2
    if (psStrConfigData->eVidStd == VDEC_STD_MPEG2)
    {
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
            MSVDX_CMDS, OPERATING_MODE, ASYNC_MODE, VDEC_MSVDX_ASYNC_VDMC)
    }
    else
#endif /* HAS_MPEG2 */
#ifdef HAS_H264
    if (psStrConfigData->eVidStd == VDEC_STD_H264)
    {
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
            MSVDX_CMDS, OPERATING_MODE, ASYNC_MODE,
            psStrUnit->psPictHdrInfo->bDiscontinuousMbs ? VDEC_MSVDX_ASYNC_VDMC : VDEC_MSVDX_ASYNC_NORMAL)
    }
    else
#endif /* HAS_H264 */
    {};  /* Dummy, to allow for #ifdefs above. */

    // Stride (reconstructed buffer)
    if (psCoreProps->bExtendedStrides && VDEC_IS_EXTENDED_STRIDE(psBuffers->psReconPict->sRendInfo))
    {
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
            MSVDX_CMDS, OPERATING_MODE, USE_EXT_ROW_STRIDE,
            1);

        // 64-byte (min) aligned luma stride value.
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_EXTENDED_ROW_STRIDE],
            MSVDX_CMDS, EXTENDED_ROW_STRIDE, EXT_ROW_STRIDE,
            psBuffers->psReconPict->sRendInfo.asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride >> 6);

        // 64-byte (min) aligned chroma stride value.
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_CHROMA_ROW_STRIDE],
            MSVDX_CMDS, CHROMA_ROW_STRIDE, CHROMA_ROW_STRIDE,
            psBuffers->psReconPict->sRendInfo.asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Stride >> 6);
    }
    else
    {
        // Obtain the code for buffer stride
        ui32RowStrideCode = VDECDDUTILS_GetStrideCode(
            psStrConfigData->eVidStd,
            psBuffers->psReconPict->sRendInfo.asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride);

        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
            MSVDX_CMDS, OPERATING_MODE, ROW_STRIDE,
            ui32RowStrideCode & 0x7);

        if (psStrConfigData->eVidStd == VDEC_STD_JPEG)
        {
            // Use the unused chroma interleaved flag to hold MSB of row stride code
            IMG_ASSERT(ui32RowStrideCode < 16);
            REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_OPERATING_MODE],
                MSVDX_CMDS, OPERATING_MODE, CHROMA_INTERLEAVED,
                ui32RowStrideCode >> 3);
        }
        else
        {
            IMG_ASSERT(ui32RowStrideCode < 8);
        }
    }
    pui32PictCmds[VDECFW_CMD_LUMA_RECONSTRUCTED_PICTURE_BASE_ADDRESS] =
            (IMG_UINT32)GET_HOST_ADDR(&psBuffers->psReconPict->psPictBuf->sDdBufInfo, IMG_TRUE) +
            psBuffers->psReconPict->sRendInfo.asPlaneInfo[0].ui32Offset;

    pui32PictCmds[VDECFW_CMD_CHROMA_RECONSTRUCTED_PICTURE_BASE_ADDRESS] =
            (IMG_UINT32)GET_HOST_ADDR(&psBuffers->psReconPict->psPictBuf->sDdBufInfo, IMG_TRUE) +
            psBuffers->psReconPict->sRendInfo.asPlaneInfo[1].ui32Offset;

    pui32PictCmds[VDECFW_CMD_CHROMA2_RECONSTRUCTED_PICTURE_BASE_ADDRESS] =
            (IMG_UINT32)GET_HOST_ADDR(&psBuffers->psReconPict->psPictBuf->sDdBufInfo, IMG_TRUE) +
            psBuffers->psReconPict->sRendInfo.asPlaneInfo[2].ui32Offset;

    pui32PictCmds[VDECFW_CMD_INTRA_BUFFER_BASE_ADDRESS] = (IMG_UINT32)GET_HOST_ADDR(psBuffers->psIntraBufInfo, IMG_TRUE) + psBuffers->ui32IntraBufPipeOffset;
    pui32PictCmds[VDECFW_CMD_INTRA_BUFFER_PLANE_SIZE] = psBuffers->psIntraBufInfo->ui32BufSize/3;
    pui32PictCmds[VDECFW_CMD_AUX_LINE_BUFFER_BASE_ADDRESS] = (IMG_UINT32)GET_HOST_ADDR(psBuffers->psAuxLineBufInfo, IMG_TRUE) + psBuffers->ui32AuxLineBufPipeOffset;

#ifdef HAS_VC1
    if (psStrConfigData->eVidStd == VDEC_STD_VC1)
    {
        pui32PictCmds[VDECFW_CMD_AUX_MSB_BUFFER] = (IMG_NULL == psBuffers->psMSBBufInfo) ?
            0 : ((IMG_UINT32)(GET_HOST_ADDR(psBuffers->psMSBBufInfo, IMG_TRUE)));
    }
#endif /* HAS_VC1 */

    if (psCoreProps->bAuxLineBufSupported)
    {
#ifdef VDEC_USE_PVDEC
        // this is causing corruption in RV40 and VC1 streams with scaling/rotation enabled on Coral, so setting to 0
        bEnableAuxLineBuf = bEnableAuxLineBuf &&
                            (psStrConfigData->eVidStd != VDEC_STD_REAL) &&
                            (psStrConfigData->eVidStd != VDEC_STD_VC1);
#endif /* VDEC_USE_PVDEC */
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION],
            MSVDX_CMDS, ALTERNATIVE_OUTPUT_PICTURE_ROTATION, USE_AUX_LINE_BUF,
            bEnableAuxLineBuf ? 1 : 0);
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              VXD_SetAltPictCmds

******************************************************************************/
IMG_RESULT
VXD_SetAltPictCmds(
    const VDECDD_sStrUnit       * psStrUnit,
    const VDEC_sStrConfigData   * psStrConfigData,
    const VDEC_sStrOutputConfig * psOutputConfig,
    const VXD_sCoreProps        * psCoreProps,
    const VXD_sBuffers          * psBuffers,
    IMG_UINT32                  * pui32PictCmds
)
{
    IMG_UINT32    ui32RowStrideCode;
    IMG_BOOL      bReconWrite = IMG_TRUE;
    IMG_BOOL      bUseScalerBypass = IMG_FALSE;

    if(!psOutputConfig->bForceOold && !psOutputConfig->bScale &&
        psOutputConfig->eRotMode == VDEC_ROTATE_0 &&
        psOutputConfig->sPixelInfo.eChromaFormatIdc == psStrUnit->psSequHdrInfo->sComSequHdrInfo.sPixelInfo.eChromaFormatIdc &&
        psOutputConfig->sPixelInfo.ui32BitDepthY == psStrUnit->psSequHdrInfo->sComSequHdrInfo.sPixelInfo.ui32BitDepthY &&
        psOutputConfig->sPixelInfo.ui32BitDepthC == psStrUnit->psSequHdrInfo->sComSequHdrInfo.sPixelInfo.ui32BitDepthC)
    {
        // When supplied with an alternate output buffer and not using it for
        // transformation (e.g. scaling. rotating or up/down-sampling) signal
        // to use the scaler as a means of generating output with an arbitrary stride.
        if(VDEC_STD_VC1 == psStrConfigData->eVidStd)
        {
            if(psStrUnit->psSequHdrInfo->sComSequHdrInfo.bPostProcessing && !psStrUnit->psPictHdrInfo->bPostProcessing)
            {
                bUseScalerBypass = IMG_TRUE;
            }
        }
        else
        {
            bUseScalerBypass = IMG_TRUE;
        }
    }

    // Stride (Out-of-loop buffer)
    if (psCoreProps->bExtendedStrides && VDEC_IS_EXTENDED_STRIDE(psBuffers->psAltPict->sRendInfo))
    {
        // Ensure that it's supported by the hardware.
        IMG_ASSERT(psCoreProps->bExtendedStrides);

        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION],
            MSVDX_CMDS, ALTERNATIVE_OUTPUT_PICTURE_ROTATION, USE_EXT_ROT_ROW_STRIDE,
            1);

        // 64-byte (min) aligned luma stride value.
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION],
            MSVDX_CMDS, ALTERNATIVE_OUTPUT_PICTURE_ROTATION, EXT_ROT_ROW_STRIDE,
            psBuffers->psAltPict->sRendInfo.asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride >> 6);

        // 64-byte (min) aligned chroma stride value.
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_CHROMA_ROW_STRIDE],
            MSVDX_CMDS, CHROMA_ROW_STRIDE, ALT_CHROMA_ROW_STRIDE,
            psBuffers->psAltPict->sRendInfo.asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Stride >> 6);
    }
    else
    {
        // Obtain the code for buffer stride (must be less than 8, i.e. not JPEG strides)
        ui32RowStrideCode = VDECDDUTILS_GetStrideCode(
            psStrConfigData->eVidStd,
            psBuffers->psAltPict->sRendInfo.asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride);
        IMG_ASSERT(ui32RowStrideCode < 8);

        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION],
            MSVDX_CMDS, ALTERNATIVE_OUTPUT_PICTURE_ROTATION, ROTATION_ROW_STRIDE,
            ui32RowStrideCode & 0x7);
    }

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_PICTURE_ROTATION, SCALE_INPUT_SIZE_SEL,
        (psOutputConfig->bScale ||
        (psOutputConfig->sPixelInfo.eChromaFormatIdc != psStrUnit->psSequHdrInfo->sComSequHdrInfo.sPixelInfo.eChromaFormatIdc))
        ? 1 : 0);

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_PICTURE_ROTATION, PACKED_422_OUTPUT,
        (psOutputConfig->sPixelInfo.eChromaFormatIdc == PIXEL_FORMAT_422 &&
         psOutputConfig->sPixelInfo.ui32NoPlanes == 1) ? 1 : 0);

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, ALT_OUTPUT_FORMAT,
        PIXEL_GET_HW_CHROMA_FORMAT_IDC(psOutputConfig->sPixelInfo.eChromaFormatIdc));

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL], MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, ALT_BIT_DEPTH_CHROMA_MINUS8, psOutputConfig->sPixelInfo.ui32BitDepthC - 8);
    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL], MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, ALT_BIT_DEPTH_LUMA_MINUS8, psOutputConfig->sPixelInfo.ui32BitDepthY - 8);
    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL], MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, ALT_MEMORY_PACKING, (psOutputConfig->sPixelInfo.eMemoryPacking == PIXEL_BIT10_MP)?1:0);


    if (bUseScalerBypass ||
        psOutputConfig->bScale ||
        (psStrUnit->psSequHdrInfo->sComSequHdrInfo.sPixelInfo.eChromaFormatIdc != psOutputConfig->sPixelInfo.eChromaFormatIdc) ||
        (psOutputConfig->sPixelInfo.ui32BitDepthY != psStrUnit->psSequHdrInfo->sComSequHdrInfo.sPixelInfo.ui32BitDepthY) ||
        (psOutputConfig->sPixelInfo.ui32BitDepthC != psStrUnit->psSequHdrInfo->sComSequHdrInfo.sPixelInfo.ui32BitDepthC) )
    {
        SCALER_sConfig      sScalerConfig;

        // Must include cropped region in top-left since scaler must use this data.
        sScalerConfig.ui32ReconWidth = psStrUnit->psPictHdrInfo->sDispInfo.sEncDispRegion.ui32Width + psStrUnit->psPictHdrInfo->sDispInfo.sEncDispRegion.ui32LeftOffset;
        sScalerConfig.ui32ReconHeight = psStrUnit->psPictHdrInfo->sDispInfo.sEncDispRegion.ui32Height + psStrUnit->psPictHdrInfo->sDispInfo.sEncDispRegion.ui32TopOffset;

        // Adjust recon width to solve the odd width issue with HW. (applies to cores rev 3 and earlier)
        // May need to be disabled for later cores
        // This is BRN32651 so ...
        if (psCoreProps->BRN32651)
        {
            sScalerConfig.ui32ReconWidth &= ~1;
        }

        sScalerConfig.ui32MbWidth  = VDEC_ALIGN_SIZE(psStrUnit->psPictHdrInfo->sCodedFrameSize.ui32Width, VDEC_MB_DIMENSION);
        sScalerConfig.ui32MbHeight = VDEC_ALIGN_SIZE(psStrUnit->psPictHdrInfo->sCodedFrameSize.ui32Height,
                                            (psStrUnit->psPictHdrInfo->bField) ? 2*VDEC_MB_DIMENSION : VDEC_MB_DIMENSION);

        sScalerConfig.ui32ScaleWidth = psOutputConfig->bScale ?
            psOutputConfig->sScaledPictSize.ui32Width :
            psStrUnit->psPictHdrInfo->sDispInfo.sEncDispRegion.ui32Width;

        sScalerConfig.ui32ScaleHeight = psOutputConfig->bScale ?
            psOutputConfig->sScaledPictSize.ui32Height :
            psStrUnit->psPictHdrInfo->sDispInfo.sEncDispRegion.ui32Height;

        sScalerConfig.bFieldCoded = psStrUnit->psPictHdrInfo->bField;

        sScalerConfig.psInPixelInfo = &psStrUnit->psSequHdrInfo->sComSequHdrInfo.sPixelInfo;
        //IMG_ASSERT(psPictBuf->sDispPictRendInfo.ePixelFormat == psStrUnit->psSequHdrInfo->sComSequHdrInfo.ePixelFormat);

        sScalerConfig.psOutPixelInfo = &psOutputConfig->sPixelInfo;
        //IMG_ASSERT(psAltPictBuf->sDispPictRendInfo.ePixelFormat == psOutputConfig->ePixelFormat);

        sScalerConfig.psCoreProps = psCoreProps;
        sScalerConfig.eVidStd = psStrConfigData->eVidStd;

        sScalerConfig.bSeparateChromaPlanes = psStrUnit->psSequHdrInfo->sComSequHdrInfo.bSeparateChromaPlanes;

        SCALER_GetScalerCmds(&sScalerConfig, pui32PictCmds);
    }


    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_PICTURE_ROTATION, ALT_PICTURE_ENABLE, 1);

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_PICTURE_ROTATION, SCALE_ENABLE,
        (bUseScalerBypass ||
         psOutputConfig->bScale ||
         (psStrUnit->psSequHdrInfo->sComSequHdrInfo.sPixelInfo.eChromaFormatIdc != psOutputConfig->sPixelInfo.eChromaFormatIdc) ||
         (psOutputConfig->sPixelInfo.ui32BitDepthY != psStrUnit->psSequHdrInfo->sComSequHdrInfo.sPixelInfo.ui32BitDepthY) ||
         (psOutputConfig->sPixelInfo.ui32BitDepthC != psStrUnit->psSequHdrInfo->sComSequHdrInfo.sPixelInfo.ui32BitDepthC)) ? 1 : 0);

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_PICTURE_ROTATION, ROTATION_MODE,
        psOutputConfig->eRotMode);

    if (bUseScalerBypass || psOutputConfig->bScale || psOutputConfig->eRotMode != VDEC_ROTATE_0)
    {
        bReconWrite = IMG_TRUE;
    }

    if ((bUseScalerBypass || psOutputConfig->bScale) &&
        psStrConfigData->eVidStd == VDEC_STD_VC1 && psCoreProps->BRN31777 && psStrUnit->psPictHdrInfo->bPostProcessing)
    {
        bReconWrite =  IMG_TRUE;
    }

    if (psBuffers->bTwoPass)
    {
        bReconWrite = IMG_TRUE;
    }

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_PICTURE_ROTATION],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_PICTURE_ROTATION, RECON_WRITE_DISABLE,
        bReconWrite ? 0 : 1);


    pui32PictCmds[VDECFW_CMD_LUMA_ALTERNATIVE_PICTURE_BASE_ADDRESS] = (IMG_UINT32)GET_HOST_ADDR(&psBuffers->psAltPict->psPictBuf->sDdBufInfo, IMG_TRUE) +
                                                            psBuffers->psAltPict->sRendInfo.asPlaneInfo[0].ui32Offset;

    pui32PictCmds[VDECFW_CMD_CHROMA_ALTERNATIVE_PICTURE_BASE_ADDRESS] = (IMG_UINT32)GET_HOST_ADDR(&psBuffers->psAltPict->psPictBuf->sDdBufInfo, IMG_TRUE) +
                                                            psBuffers->psAltPict->sRendInfo.asPlaneInfo[1].ui32Offset;

    pui32PictCmds[VDECFW_CMD_CHROMA2_ALTERNATIVE_PICTURE_BASE_ADDRESS] = (IMG_UINT32)GET_HOST_ADDR(&psBuffers->psAltPict->psPictBuf->sDdBufInfo, IMG_TRUE) +
                                                            psBuffers->psAltPict->sRendInfo.asPlaneInfo[2].ui32Offset;

    return IMG_SUCCESS;
}


/*
******************************************************************************

 @Function              VXD_GetScalerCoeffCmds

******************************************************************************/
IMG_RESULT
VXD_GetScalerCoeffCmds(
    const SCALER_sCoeffs  * psScalerCoeffs,
    IMG_UINT32            * pui32PictCmds
)
{
    IMG_UINT32 i, j;
    MSVDX_sScalerCoeffCmds  sCoeffCmds;
    MSVDX_sScalerCoeffCmds * psCoeffCmds = &sCoeffCmds;

    if (psScalerCoeffs->paui8HorizLuma)
    {
        for (i = 0; i < 4; i++)
        {
            j = 1 + (2 * i);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdHorizLumaCoeff[i],
                MSVDX_CMDS, HORIZONTAL_LUMA_COEFFICIENTS, HOR_LUMA_COEFF_3,
                psScalerCoeffs->paui8HorizLuma[0][j]);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdHorizLumaCoeff[i],
                MSVDX_CMDS, HORIZONTAL_LUMA_COEFFICIENTS, HOR_LUMA_COEFF_2,
                psScalerCoeffs->paui8HorizLuma[1][j]);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdHorizLumaCoeff[i],
                MSVDX_CMDS, HORIZONTAL_LUMA_COEFFICIENTS, HOR_LUMA_COEFF_1,
                psScalerCoeffs->paui8HorizLuma[2][j]);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdHorizLumaCoeff[i],
                MSVDX_CMDS, HORIZONTAL_LUMA_COEFFICIENTS, HOR_LUMA_COEFF_0,
                psScalerCoeffs->paui8HorizLuma[3][j]);
        }
    }
    else
    {
        psCoeffCmds->aui32CmdHorizLumaCoeff[0] = 0;
        psCoeffCmds->aui32CmdHorizLumaCoeff[1] = 0;
        psCoeffCmds->aui32CmdHorizLumaCoeff[2] = 0;
        psCoeffCmds->aui32CmdHorizLumaCoeff[3] = 0x00400000;
    }


    if (psScalerCoeffs->paui8HorizChroma)
    {
        for (i = 0; i < 4; i++)
        {
            j = 1 + (2 * i);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdHorizChromaCoeff[i],
                MSVDX_CMDS, HORIZONTAL_CHROMA_COEFFICIENTS, HOR_CHROMA_COEFF_3,
                psScalerCoeffs->paui8HorizChroma[0][j]);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdHorizChromaCoeff[i],
                MSVDX_CMDS, HORIZONTAL_CHROMA_COEFFICIENTS, HOR_CHROMA_COEFF_2,
                psScalerCoeffs->paui8HorizChroma[1][j]);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdHorizChromaCoeff[i],
                MSVDX_CMDS, HORIZONTAL_CHROMA_COEFFICIENTS, HOR_CHROMA_COEFF_1,
                psScalerCoeffs->paui8HorizChroma[2][j]);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdHorizChromaCoeff[i],
                MSVDX_CMDS, HORIZONTAL_CHROMA_COEFFICIENTS, HOR_CHROMA_COEFF_0,
                psScalerCoeffs->paui8HorizChroma[3][j]);
        }
    }
    else
    {
        psCoeffCmds->aui32CmdHorizChromaCoeff[0] = 0;
        psCoeffCmds->aui32CmdHorizChromaCoeff[1] = 0;
        psCoeffCmds->aui32CmdHorizChromaCoeff[2] = 0;
        psCoeffCmds->aui32CmdHorizChromaCoeff[3] = 0x00400000;
    }

    if (psScalerCoeffs->paui8VertLuma)
    {
        for (i = 0; i < 4; i++)
        {
            j = 1 + (2 * i);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdVertLumaCoeff[i],
                MSVDX_CMDS, VERTICAL_LUMA_COEFFICIENTS, VER_LUMA_COEFF_3,
                psScalerCoeffs->paui8VertLuma[0][j]);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdVertLumaCoeff[i],
                MSVDX_CMDS, VERTICAL_LUMA_COEFFICIENTS, VER_LUMA_COEFF_2,
                psScalerCoeffs->paui8VertLuma[1][j]);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdVertLumaCoeff[i],
                MSVDX_CMDS, VERTICAL_LUMA_COEFFICIENTS, VER_LUMA_COEFF_1,
                psScalerCoeffs->paui8VertLuma[2][j]);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdVertLumaCoeff[i],
                MSVDX_CMDS, VERTICAL_LUMA_COEFFICIENTS, VER_LUMA_COEFF_0,
                psScalerCoeffs->paui8VertLuma[3][j]);
        }
    }
    else
    {
        psCoeffCmds->aui32CmdVertLumaCoeff[0] = 0;
        psCoeffCmds->aui32CmdVertLumaCoeff[1] = 0;
        psCoeffCmds->aui32CmdVertLumaCoeff[2] = 0;
        psCoeffCmds->aui32CmdVertLumaCoeff[3] = 0x00400000;
    }


    if (psScalerCoeffs->paui8VertChroma)
    {
        for (i = 0; i < 4; i++)
        {
            j = 1 + (2 * i);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdVertChromaCoeff[i],
                MSVDX_CMDS, VERTICAL_CHROMA_COEFFICIENTS, VER_CHROMA_COEFF_3,
                psScalerCoeffs->paui8VertChroma[0][j]);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdVertChromaCoeff[i],
                MSVDX_CMDS, VERTICAL_CHROMA_COEFFICIENTS, VER_CHROMA_COEFF_2,
                psScalerCoeffs->paui8VertChroma[1][j]);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdVertChromaCoeff[i],
                MSVDX_CMDS, VERTICAL_CHROMA_COEFFICIENTS, VER_CHROMA_COEFF_1,
                psScalerCoeffs->paui8VertChroma[2][j]);

            REGIO_WRITE_FIELD(psCoeffCmds->aui32CmdVertChromaCoeff[i],
                MSVDX_CMDS, VERTICAL_CHROMA_COEFFICIENTS, VER_CHROMA_COEFF_0,
                psScalerCoeffs->paui8VertChroma[3][j]);
        }
    }
    else
    {
        // Scaler by-pass
        psCoeffCmds->aui32CmdVertChromaCoeff[0] = 0;
        psCoeffCmds->aui32CmdVertChromaCoeff[1] = 0;
        psCoeffCmds->aui32CmdVertChromaCoeff[2] = 0;
        psCoeffCmds->aui32CmdVertChromaCoeff[3] = 0x00400000;
    }

    // Copy the coefficients into the commands array.
    pui32PictCmds[VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_0] = psCoeffCmds->aui32CmdHorizLumaCoeff[0];
    pui32PictCmds[VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_1] = psCoeffCmds->aui32CmdHorizLumaCoeff[1];
    pui32PictCmds[VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_2] = psCoeffCmds->aui32CmdHorizLumaCoeff[2];
    pui32PictCmds[VDECFW_CMD_HORIZONTAL_LUMA_COEFFICIENTS_3] = psCoeffCmds->aui32CmdHorizLumaCoeff[3];
    pui32PictCmds[VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_0] = psCoeffCmds->aui32CmdVertLumaCoeff[0];
    pui32PictCmds[VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_1] = psCoeffCmds->aui32CmdVertLumaCoeff[1];
    pui32PictCmds[VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_2] = psCoeffCmds->aui32CmdVertLumaCoeff[2];
    pui32PictCmds[VDECFW_CMD_VERTICAL_LUMA_COEFFICIENTS_3] = psCoeffCmds->aui32CmdVertLumaCoeff[3];
    pui32PictCmds[VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_0] = psCoeffCmds->aui32CmdHorizChromaCoeff[0];
    pui32PictCmds[VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_1] = psCoeffCmds->aui32CmdHorizChromaCoeff[1];
    pui32PictCmds[VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_2] = psCoeffCmds->aui32CmdHorizChromaCoeff[2];
    pui32PictCmds[VDECFW_CMD_HORIZONTAL_CHROMA_COEFFICIENTS_3] = psCoeffCmds->aui32CmdHorizChromaCoeff[3];
    pui32PictCmds[VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_0] = psCoeffCmds->aui32CmdVertChromaCoeff[0];
    pui32PictCmds[VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_1] = psCoeffCmds->aui32CmdVertChromaCoeff[1];
    pui32PictCmds[VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_2] = psCoeffCmds->aui32CmdVertChromaCoeff[2];
    pui32PictCmds[VDECFW_CMD_VERTICAL_CHROMA_COEFFICIENTS_3] = psCoeffCmds->aui32CmdVertChromaCoeff[3];

    return IMG_SUCCESS;
}


/*
******************************************************************************

 @Function              VXD_GetScalerCmds

******************************************************************************/
IMG_RESULT
VXD_GetScalerCmds(
    const SCALER_sConfig    * psScalerConfig,
    const SCALER_sPitch     * psPitch,
    const SCALER_sFilter    * psFilter,
    const PIXEL_sPixelInfo  * psOutLoopPixelInfo,
    SCALER_sParams          * psParams,
    IMG_UINT32              * pui32PictCmds
)
{
    const VXD_sCoreProps * psCoreProps = psScalerConfig->psCoreProps;
    /* Indirectly detect decoder core type (if HEVC is supported, it has to be PVDEC core)
     * and decide if to force luma re-sampling. */
    IMG_BOOL bForceLumaResampling = psCoreProps->abHEVC[0];

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, ALT_OUTPUT_FORMAT,
        psScalerConfig->bSeparateChromaPlanes ? 0 : PIXEL_GET_HW_CHROMA_FORMAT_IDC(psOutLoopPixelInfo->eChromaFormatIdc));

#ifdef FXDPNT_SCALER_CALC

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, SCALE_CHROMA_RESAMP_ONLY,
        bForceLumaResampling ? 0 : (psPitch->iHorizLuma == FIXED(1,HIGHP)) && (psPitch->iVertLuma == FIXED(1,HIGHP)));

#else

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, SCALE_CHROMA_RESAMP_ONLY,
        bForceLumaResampling ? 0 : (psPitch->fHorizLuma == 1) && (psPitch->fVertLuma == 1));

#endif

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, ALT_MEMORY_PACKING,
        PIXEL_GET_HW_MEMORY_PACKING(psOutLoopPixelInfo->eMemoryPacking) );

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, ALT_BIT_DEPTH_LUMA_MINUS8,
        psOutLoopPixelInfo->ui32BitDepthY - 8);

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, ALT_BIT_DEPTH_CHROMA_MINUS8,
        psOutLoopPixelInfo->ui32BitDepthC - 8);

    /* Scale luma bifilter is always 0 for now */
    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, SCALE_LUMA_BIFILTER_HORIZ,
        0);

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, SCALE_LUMA_BIFILTER_VERT,
        0);

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, SCALE_CHROMA_BIFILTER_HORIZ,
        psFilter->bHorizBilinear ? 1 : 0);

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_ALTERNATIVE_OUTPUT_CONTROL],
        MSVDX_CMDS, ALTERNATIVE_OUTPUT_CONTROL, SCALE_CHROMA_BIFILTER_VERT,
        psFilter->bVertBilinear ? 1 : 0);

    // for cores 7.x.x and more, precision 3.13
    if (psCoreProps->b8kScalingCoeffs)
    {
        psParams->iFixedPointShift = 13;
    }
    // for cores 5.x.x and more, precision 3.12
    else if (psCoreProps->b4kScalingCoeffs)
    {
        psParams->iFixedPointShift = 12;
    }
    else
    {
        psParams->iFixedPointShift = 11;
    }

#ifdef FXDPNT_SCALER_CALC
    /* Calculate the fixed-point versions for use by the hardware. */
    psParams->iVertPitch = (int)((psPitch->iVertLuma + (1 << (HIGHP - psParams->iFixedPointShift - 1))) >> (HIGHP - psParams->iFixedPointShift));
    psParams->iVertStartPos = psParams->iVertPitch >> 1;
    psParams->iVertPitchChroma = (int)((psPitch->iVertChroma + (1 << (HIGHP - psParams->iFixedPointShift - 1))) >> (HIGHP - psParams->iFixedPointShift));
    psParams->iVertStartPosChroma = psParams->iVertPitchChroma >> 1;
    psParams->iHorzPitch = (int)(psPitch->iHorizLuma >> (HIGHP - psParams->iFixedPointShift));
    psParams->iHorzStartPos = psParams->iHorzPitch >> 1;
    psParams->iHorzPitchChroma = (int)(psPitch->iHorizChroma >> (HIGHP - psParams->iFixedPointShift));
    psParams->iHorzStartPosChroma = psParams->iHorzPitchChroma >> 1;

#else

    psParams->iVertPitch = (int)(psPitch->fVertLuma * (1 << psParams->iFixedPointShift) + 0.5f);
    psParams->iVertStartPos = (int)(psPitch->fVertLuma * 0.5f * (1 << psParams->iFixedPointShift) + 0.5f);
    psParams->iVertPitchChroma = (int)(psPitch->fVertChroma * (1 << psParams->iFixedPointShift) + 0.5f);
    psParams->iVertStartPosChroma = (int)(psPitch->fVertChroma * 0.5f * (1 << psParams->iFixedPointShift) + 0.5f);
    psParams->iHorzPitch = (int)(psPitch->fHorizLuma * (1 << psParams->iFixedPointShift));
    psParams->iHorzStartPos = (int)(psPitch->fHorizLuma * 0.5f * (1 << psParams->iFixedPointShift));
    psParams->iHorzPitchChroma = (int)(psPitch->fHorizChroma * (1 << psParams->iFixedPointShift));
    psParams->iHorzStartPosChroma = (int)(psPitch->fHorizChroma * 0.5f * (1 << psParams->iFixedPointShift));

#endif

#if 0
    psParams->iVertPitch = 0x1000;
    psParams->iVertStartPos = 0x800;
    psParams->iVertPitchChroma = 0x1000;
    psParams->iVertStartPosChroma = 0x800;
    psParams->iHorzPitch = 0x1000;
    psParams->iHorzStartPos = 0x800;
    psParams->iHorzPitchChroma = 0x1000;
    psParams->iHorzStartPosChroma = 0x800;

#endif

    scaler_ApplyRestrictions(psScalerConfig, psParams);

#ifdef HAS_HEVC
    if (psScalerConfig->eVidStd == VDEC_STD_HEVC)
    {
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_SCALED_DISPLAY_SIZE],
            MSVDX_CMDS, PVDEC_SCALED_DISPLAY_SIZE, PVDEC_SCALE_DISPLAY_WIDTH,
            psScalerConfig->ui32ReconWidth - 1);
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_SCALED_DISPLAY_SIZE],
            MSVDX_CMDS, PVDEC_SCALED_DISPLAY_SIZE, PVDEC_SCALE_DISPLAY_HEIGHT,
            psScalerConfig->ui32ReconHeight - 1);
    }
    else
#endif
    {
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_SCALED_DISPLAY_SIZE],
            MSVDX_CMDS, SCALED_DISPLAY_SIZE, SCALE_DISPLAY_WIDTH,
            psScalerConfig->ui32ReconWidth - 1);
        REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_SCALED_DISPLAY_SIZE],
            MSVDX_CMDS, SCALED_DISPLAY_SIZE, SCALE_DISPLAY_HEIGHT,
            psScalerConfig->ui32ReconHeight - 1);
    }

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_SCALE_OUTPUT_SIZE],
        MSVDX_CMDS, SCALE_OUTPUT_SIZE, SCALE_OUTPUT_WIDTH_MIN1,
        psScalerConfig->ui32ScaleWidth - 1);
    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_SCALE_OUTPUT_SIZE],
        MSVDX_CMDS, SCALE_OUTPUT_SIZE, SCALE_OUTPUT_HEIGHT_MIN1,
        psScalerConfig->ui32ScaleHeight - 1);

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_HORIZONTAL_SCALE_CONTROL],
        MSVDX_CMDS, HORIZONTAL_SCALE_CONTROL, HORIZONTAL_SCALE_PITCH,
        psParams->iHorzPitch);
    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_HORIZONTAL_SCALE_CONTROL],
        MSVDX_CMDS, HORIZONTAL_SCALE_CONTROL, HORIZONTAL_INITIAL_POS,
        psParams->iHorzStartPos);

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_SCALE_HORIZONTAL_CHROMA],
        MSVDX_CMDS, SCALE_HORIZONTAL_CHROMA, CHROMA_HORIZONTAL_PITCH,
        psParams->iHorzPitchChroma);
    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_SCALE_HORIZONTAL_CHROMA],
        MSVDX_CMDS, SCALE_HORIZONTAL_CHROMA, CHROMA_HORIZONTAL_INITIAL,
        psParams->iHorzStartPosChroma);

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_VERTICAL_SCALE_CONTROL],
        MSVDX_CMDS, VERTICAL_SCALE_CONTROL, VERTICAL_SCALE_PITCH,
        psParams->iVertPitch);
    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_VERTICAL_SCALE_CONTROL],
        MSVDX_CMDS, VERTICAL_SCALE_CONTROL, VERTICAL_INITIAL_POS,
        psParams->iVertStartPos);

    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_SCALE_VERTICAL_CHROMA],
        MSVDX_CMDS, SCALE_VERTICAL_CHROMA, CHROMA_VERTICAL_PITCH, psParams->iVertPitchChroma);
    REGIO_WRITE_FIELD(pui32PictCmds[VDECFW_CMD_SCALE_VERTICAL_CHROMA],
        MSVDX_CMDS, SCALE_VERTICAL_CHROMA, CHROMA_VERTICAL_INITIAL, psParams->iVertStartPosChroma);

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              VXD_GetCodedPicSize

******************************************************************************/
IMG_UINT32 VXD_GetCodedPicSize(
    IMG_UINT16   ui16WidthMin1,
    IMG_UINT16   ui16HeightMin1
)
{
    IMG_UINT32 ui32Reg = 0;

    REGIO_WRITE_FIELD_LITE(ui32Reg, MSVDX_CMDS, CODED_PICTURE_SIZE,
                          CODED_PICTURE_WIDTH, ui16WidthMin1);
    REGIO_WRITE_FIELD_LITE(ui32Reg, MSVDX_CMDS, CODED_PICTURE_SIZE,
                           CODED_PICTURE_HEIGHT, ui16HeightMin1);

    return ui32Reg;
}

/* EOF */
