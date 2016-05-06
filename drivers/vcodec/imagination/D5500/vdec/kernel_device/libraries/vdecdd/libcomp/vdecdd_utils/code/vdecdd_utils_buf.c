/*!
 *****************************************************************************
 *
 * @File       vdecdd_utils_buf.c
 * @Title      VDEC Buffer Utilities
 * @Description    This file contains the VDEC buffer utilities compiled into user
 *  and kernel mode.
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

#include "vdecdd_utils.h"
#include "pixel_api.h"

#include "report_api.h"


// Tests if chroma offset (immediately after size of luma) is exactly aligned to buffer alignment constraint.
#define IS_PACKEDBUF_CHROMA_ALIGNED(offset, colour_plane)                   \
    (colour_plane != VDEC_PLANE_VIDEO_Y ? IMG_TRUE :                        \
        (offset == VDEC_ALIGN_SIZE(offset, VDEC_MSVDX_PICTBUF_ALIGNMENT) ?  \
            IMG_TRUE : IMG_FALSE))


/*!< h.264 MaxDpbMbs values per profile (see Table A-1 of Rec. ITU-T H.264 (03/2010)).
 *
 *   NOTE: Level 1b will be treated as 1.1 in case of Baseline, Constrained Baseline,
 *         Main, and Extended profiles as the value of the constraint_set3_flag is
 *         not available in the #VDEC_sComSequHdrInfo structure.
 */
static IMG_UINT32 aui32H264MaxDpbMbs[H264_LEVEL_MAJOR_NUM][H264_LEVEL_MINOR_NUM] =
{
    /* level: n/a     n/a     n/a     1.0b */
            { 396,    396,    396,    396  },
    /* level: 1.0     1.1     1.2     1.3  */
            { 396,    900,    2376,   2376 },
    /* level: 2.0     2.1     2.2     n/a  */
            { 2376,   4752,   8100,   8100 },
    /* level: 3.0     3.1     3.2     n/a  */
            { 8100,   18000,  20480,  20480},
    /* level: 4.0     4.1     4.2     n/a  */
            { 32768,  32768,  34816,  34816},
    /* level: 5.0     5.1     5.2     n/a  */
            { 110400, 184320, 184320, 184320}
};

#define VDEC_PVDEC_BURST4_SIZE 64

/*!
******************************************************************************
 These macros check the type of the plane alignment.
******************************************************************************/
#define VDEC_IS_LUMA_PLANE(id)         (0 == id)
#define VDEC_IS_LUMA_TYPE_PLANE(id)   ((0 == id) || (3 == id))
#define VDEC_IS_CHROMA_TYPE_PLANE(id) ((1 == id) || (2 == id))


/*!< MSVDX row strides for video buffers. */
static const IMG_UINT32  caui32Msvdx64ByteRowStride[] = {
#ifdef VDEC_TARGET_CEDARVIEW
    352,
#else
    384,
#endif
    768, 1280, 1920, 512, 1024, 2048, 4096
};

/*!< MSVDX row strides for jpeg buffers. */
static const IMG_UINT32  caui32MsvdxJpegRowStride[] = {
    256,
#ifdef VDEC_TARGET_CEDARVIEW
    352,
#else
    384,
#endif
    512, 768, 1024, 1536, 2048, 3072, 4096, 6144, 8192, 12288, 16384, 24576, 32768
};

/*!< MSVDX 256x16 tiling row strides for video buffers. */
#ifdef VDEC_USE_PVDEC
/* Disable 512 stride for PVDEC, when 512 stride is used transformations
 * in 256B interleave method depend on the virtual base address, to avoid this
 * we need 16k alignment. Buffer is aligned to multiple of 16 * stride */
const IMG_UINT32 aui32Tile256x16RowStride[] =
{
    0, 1024, 2048, 4096,
};
#else /* ndef VDEC_USE_PVDEC */
const IMG_UINT32 aui32Tile256x16RowStride[] =
{
    512, 1024, 2048, 4096,
};
#endif /* ndef VDEC_USE_PVDEC */


/*!< MSVDX 512x8 tiling row strides for video buffers. */
const IMG_UINT32 aui32Tile512x8RowStride[] =
{
    1024, 2048, 4096, 8192
};


/*!
******************************************************************************

 @Function              pfnRefPicGetMaxNum

 @Description

 This is the prototype for functions calculating the maximum number of reference
 pictures required per video standard.

 @Input    psComSequHdrInfo  : A pointer to the common VSH information structure.

 @Output   pui32MaxRefPicNum :  A pointer used to return the maximum number
                                of reference frames required.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
typedef IMG_RESULT (*pfnRefPicGetMaxNum)(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
);

/* Declarations of functions calculating the maximum number of reference pictures
 * required for each supported video standard. */
static IMG_RESULT vdecddutils_RefPicMpeg2GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
);
static IMG_RESULT vdecddutils_RefPicMpeg4GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
);
static IMG_RESULT vdecddutils_RefPicMpeg4SHeadersGetMaxNum(
    const VDEC_sComSequHdrInfo *  psComSequHdrInfo,
    IMG_UINT32 *            pui32MaxRefPicNum
);
static IMG_RESULT vdecddutils_RefPicH264GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
);
static IMG_RESULT vdecddutils_RefPicVc1GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
);
static IMG_RESULT vdecddutils_RefPicAvsGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
);
static IMG_RESULT vdecddutils_RefPicRealGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
);
static IMG_RESULT vdecddutils_RefPicJpegGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
);
static IMG_RESULT vdecddutils_RefPicVp6GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
);
static IMG_RESULT vdecddutils_RefPicVp8GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
);
static IMG_RESULT vdecddutils_RefPicHEVCGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
);

/*!< The array of pointers to functions calculating the maximum number
 *   of reference pictures required for each supported video standard.
 *
 *   NOTE: The table is indexed by #VDEC_eVidStd enum values. */
static pfnRefPicGetMaxNum aRefPicGetMaxNumFns[VDEC_STD_MAX - 1] =
{
    vdecddutils_RefPicMpeg2GetMaxNum,
    vdecddutils_RefPicMpeg4GetMaxNum,
    vdecddutils_RefPicMpeg4SHeadersGetMaxNum,
    vdecddutils_RefPicH264GetMaxNum,
    vdecddutils_RefPicVc1GetMaxNum,
    vdecddutils_RefPicAvsGetMaxNum,
    vdecddutils_RefPicRealGetMaxNum,
    vdecddutils_RefPicJpegGetMaxNum,
    vdecddutils_RefPicVp6GetMaxNum,
    vdecddutils_RefPicVp8GetMaxNum,
    vdecddutils_RefPicMpeg4SHeadersGetMaxNum,
    vdecddutils_RefPicHEVCGetMaxNum
};


/*!
******************************************************************************

 @Function              pfnOooPicGetMaxNum

 @Description

 This is the prototype for functions calculating the maximum number
 of out-of-(display)-order pictures required per video standard.

 @Input    psComSequHdrInfo  : A pointer to the common VSH information structure.

 @Output   pui32MaxRefPicNum :  A pointer used to return the maximum number
                                of out-of-(display)-order frames required.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
typedef IMG_RESULT (*pfnOooPicGetMaxNum)(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
);

/* Declarations of functions calculating the maximum number of out-of-(display)-order
 * pictures required for each supported video standard. */
static IMG_RESULT vdecddutils_OooPicMpeg2GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
);
static IMG_RESULT vdecddutils_OooPicMpeg4GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
);
static IMG_RESULT vdecddutils_OooPicMpeg4SHeadersGetMaxNum(
    const VDEC_sComSequHdrInfo *  psComSequHdrInfo,
    IMG_UINT32 *            pui32MaxOooPicNum
);
static IMG_RESULT vdecddutils_OooPicH264GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
);
static IMG_RESULT vdecddutils_OooPicVc1GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
);
static IMG_RESULT vdecddutils_OooPicAvsGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
);
static IMG_RESULT vdecddutils_OooPicRealGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
);
static IMG_RESULT vdecddutils_OooPicJpegGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
);
static IMG_RESULT vdecddutils_OooPicVp6GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
);
static IMG_RESULT vdecddutils_OooPicVp8GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
);

/*!< The array of pointers to functions calculating the maximum number
 *   of out-of-(display)-order pictures required for each supported video standard.
 *
 *   NOTE: The table is indexed by #VDEC_eVidStd enum values. */
static pfnOooPicGetMaxNum aOooPicGetMaxNumFns[VDEC_STD_MAX - 1] =
{
    vdecddutils_OooPicMpeg2GetMaxNum,
    vdecddutils_OooPicMpeg4GetMaxNum,
    vdecddutils_OooPicMpeg4SHeadersGetMaxNum,
    vdecddutils_OooPicH264GetMaxNum,
    vdecddutils_OooPicVc1GetMaxNum,
    vdecddutils_OooPicAvsGetMaxNum,
    vdecddutils_OooPicRealGetMaxNum,
    vdecddutils_OooPicJpegGetMaxNum,
    vdecddutils_OooPicVp6GetMaxNum,
    vdecddutils_OooPicVp8GetMaxNum,
    vdecddutils_OooPicMpeg4SHeadersGetMaxNum
};








/*!
******************************************************************************

 @Function              vdecddutils_RefPicMpeg2GetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_RefPicMpeg2GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
)
{
    // Set the maximum number of required pictures as the default in case
    // the profile is specified incorrectly.
    *pui32MaxRefPicNum = 2;

    /* For MPEG-2 the maximum number of reference pictures
     * is based on the profile only. */
    switch (psComSequHdrInfo->ui32CodecProfile)
    {
        case MPEG2_PROFILE_SIMPLE:
#ifdef FORCE_PROFILE_PROPERTIES
            *pui32MaxRefPicNum = 1;
#endif
            break;

        case MPEG2_PROFILE_MAIN:
        case MPEG2_PROFILE_SNR_SCALABLE:
        case MPEG2_PROFILE_SPATIALLY_SCALABLE:
        case MPEG2_PROFILE_HIGH:
        case MPEG2_PROFILE_MVP_LL:
        case MPEG2_PROFILE_MVP_ML:
        case MPEG2_PROFILE_MVP_HIGH1440:
        case MPEG2_PROFILE_MVP_HL:
        case MPEG2_PROFILE_422_LL:
        case MPEG2_PROFILE_422_HL:
#ifdef FORCE_PROFILE_PROPERTIES
            *pui32MaxRefPicNum = 2;
#endif
            break;

        default:
            REPORT(REPORT_MODULE_VDECDD, REPORT_WARNING,
                "Wrong MPEG2 profile value: %u\n",
                psComSequHdrInfo->ui32CodecProfile);
            break;
    }

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_RefPicMpeg4GetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_RefPicMpeg4GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
)
{

    // Set the maximum number of required pictures as the default in case
    // the profile is specified incorrectly.
    *pui32MaxRefPicNum = 2;

    /* For MPEG-4 the maximum number of reference pictures
     * is based on the profile only. */
    /* NOTE: Following VIDDEC, only Simple and Advanced Simple profiles are supported. */
    switch (psComSequHdrInfo->ui32CodecProfile)
    {
        case MPEG4_PROFILE_SIMPLE_L0:
        case MPEG4_PROFILE_SIMPLE_L1:
        case MPEG4_PROFILE_SIMPLE_L2:
        case MPEG4_PROFILE_SIMPLE_L3:
#ifdef FORCE_PROFILE_PROPERTIES
           *pui32MaxRefPicNum = 1;
#endif
            break;

        case MPEG4_PROFILE_ADVANCED_SIMPLE_L0:
        case MPEG4_PROFILE_ADVANCED_SIMPLE_L1:
        case MPEG4_PROFILE_ADVANCED_SIMPLE_L2:
        case MPEG4_PROFILE_ADVANCED_SIMPLE_L3:
        case MPEG4_PROFILE_ADVANCED_SIMPLE_L4:
        case MPEG4_PROFILE_ADVANCED_SIMPLE_L5:
        case MPEG4_PROFILE_ADVANCED_SIMPLE_L3b:
#ifdef FORCE_PROFILE_PROPERTIES
           *pui32MaxRefPicNum = 2;
#endif
            break;

        case MPEG4_PROFILE_SIMPLE_SCLABLE_L2:
        case MPEG4_PROFILE_CORE_L2:
        case MPEG4_PROFILE_MAIN_L4:
        case MPEG4_PROFILE_FGS_L5:
        case MPEG4_PROFILE_NBIT_L2:
        case MPEG4_PROFILE_SCALABLE_TEXTURE_L1:
        case MPEG4_PROFILE_BASIC_SIMPLE_FACE_L2:
        case MPEG4_PROFILE_SIMPLE_FBA_L2:
        case MPEG4_PROFILE_BASIC_ANIMATED_TEXTURE_L2:
        case MPEG4_PROFILE_ADVANCED_REAL_TIME_SIMPLE_L4:
        case MPEG4_PROFILE_CORE_SCALABLE_L3:
        case MPEG4_PROFILE_ADVANCED_CODING_EFFIENCY_L4:
        case MPEG4_PROFILE_ADVANCED_SCALABLE_TEXTURE_L3:
        case MPEG4_PROFILE_SIMPLE_STUDIO_L4:
        case MPEG4_PROFILE_CORE_STUDIO_L4:
#ifdef FORCE_PROFILE_PROPERTIES
            *pui32MaxRefPicNum = 2;
#endif
            break;

        default:
            REPORT(REPORT_MODULE_VDECDD, REPORT_WARNING,
                   "Wrong MPEG4 profile value: %u\n",
                   psComSequHdrInfo->ui32CodecProfile);
            break;
    }

    /* Return success. */
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              vdecddutils_RefPicMpeg4SHeadersGetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_RefPicMpeg4SHeadersGetMaxNum(
    const VDEC_sComSequHdrInfo *  psComSequHdrInfo,
    IMG_UINT32 *            pui32MaxRefPicNum
)
{
    /* For MPEG-4 short headers the maximum number of reference pictures
     * is not based on the profile. */
    *pui32MaxRefPicNum = 1;

    /* Return success. */
    return IMG_SUCCESS;
}
/*!
******************************************************************************

 @Function              vdecddutils_RefPicH264GetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_RefPicH264GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
)
{
    IMG_UINT32 ui32PicWidthMB;
    IMG_UINT32 ui32PicHeightMB;
    IMG_UINT32 ui32LvlMajor = 0;
    IMG_UINT32 ui32LvlMinor = 0;

    /* Pre-validate level. */
    if((psComSequHdrInfo->ui32CodecLevel < H264_LEVEL_MIN) || (psComSequHdrInfo->ui32CodecLevel > H264_LEVEL_MAX))
    {
        DEBUG_REPORT(REPORT_MODULE_VDECDD, "Wrong H264 level value: %u", psComSequHdrInfo->ui32CodecLevel);
    }

    if (psComSequHdrInfo->ui32MaxReorderPicts)
    {
        *pui32MaxRefPicNum = psComSequHdrInfo->ui32MaxReorderPicts;
    }
    else
    {
        /* Calculate level major and minor. */
        ui32LvlMajor = psComSequHdrInfo->ui32CodecLevel / 10;
        ui32LvlMinor = psComSequHdrInfo->ui32CodecLevel % 10;

        /* Calculate picture sizes in MBs. */
        ui32PicWidthMB = (psComSequHdrInfo->sMaxFrameSize.ui32Width + (VDEC_MB_DIMENSION - 1)) / VDEC_MB_DIMENSION;
        ui32PicHeightMB = (psComSequHdrInfo->sMaxFrameSize.ui32Height + (VDEC_MB_DIMENSION - 1)) / VDEC_MB_DIMENSION;

        /* Validate ui32LvlMinor */
        if(ui32LvlMinor > 3)
        {
            DEBUG_REPORT(REPORT_MODULE_VDECDD, "Wrong H264 ui32LvlMinor level value: %u, overriding with 3", ui32LvlMinor);
            ui32LvlMinor = 3;
        }
        /* Validate ui32LvlMajor */
        if(ui32LvlMajor > 5)
        {
            DEBUG_REPORT(REPORT_MODULE_VDECDD, "Wrong H264 ui32LvlMajor level value:%u, overriding with 5", ui32LvlMajor);
            ui32LvlMajor = 5;
        }

        /* Calculate the maximum number of reference pictures required based on level. */
        *pui32MaxRefPicNum = aui32H264MaxDpbMbs[ui32LvlMajor][ui32LvlMinor] / (ui32PicWidthMB * ui32PicHeightMB);
        if(*pui32MaxRefPicNum > 16)
        {
            *pui32MaxRefPicNum = 16;
        }
    }

    /* Return success. */
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              vdecddutils_RefPicVc1GetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_RefPicVc1GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
)
{
    // Set the maximum number of required pictures as the default in case
    // the profile is specified incorrectly.
    *pui32MaxRefPicNum = 2;

    /* For VC-1 the maximum number of reference pictures
     * is based on the profile only. */
    switch (psComSequHdrInfo->ui32CodecProfile)
    {
        case VC1_PROFILE_SIMPLE:
#ifdef FORCE_PROFILE_PROPERTIES
            *pui32MaxRefPicNum = 1;
#endif
            break;

        case VC1_PROFILE_MAIN:
        case VC1_PROFILE_ADVANCED:
#ifdef FORCE_PROFILE_PROPERTIES
            *pui32MaxRefPicNum = 2;
#endif
            break;

        default:
            REPORT(REPORT_MODULE_VDECDD, REPORT_WARNING,
                "Wrong VC1 profile value: %u\n",
                psComSequHdrInfo->ui32CodecProfile);
            break;
    }

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_RefPicAvsGetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_RefPicAvsGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
)
{
    /* For AVS the maximum number of reference pictures is constant. */
    *pui32MaxRefPicNum = 2;

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_RefPicRealGetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_RefPicRealGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
)
{
    /* For RealVideo the maximum number of reference pictures is constant. */
    *pui32MaxRefPicNum = 2;

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_RefPicJpegGetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_RefPicJpegGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
)
{
    /* No reference frames for JPEG. */
    *pui32MaxRefPicNum = 0;

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_RefPicVp6GetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_RefPicVp6GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
)
{
    /* For VP6 the maximum number of reference pictures is constant. */
    *pui32MaxRefPicNum = 2;

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_RefPicVp8GetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_RefPicVp8GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
)
{
    /* For VP8 the maximum number of reference pictures is constant. */
    *pui32MaxRefPicNum = 3;

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_RefPicHEVCGetMaxNum

******************************************************************************/
IMG_RESULT vdecddutils_RefPicHEVCGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxRefPicNum
)
{
    const static IMG_UINT32 HEVC_LEVEL_IDC_MIN = 30;
    const static IMG_UINT32 HEVC_LEVEL_IDC_MAX = 186;
    const static IMG_UINT32
        aui32MaxLumaPs[HEVC_LEVEL_MAJOR_NUM][HEVC_LEVEL_MINOR_NUM] =
    {
        /* level: 1.0       1.1       1.2       */
                { 36864,    0,        0,        },
        /* level: 2.0       2.1       2.2       */
                { 122880,   245760,   0,        },
        /* level: 3.0       3.1       3.2       */
                { 552960,   983040,   0,        },
        /* level: 4.0       4.1       4.2       */
                { 2228224,  2228224,  0,        },
        /* level: 5.0       5.1       5.2       */
                { 8912896,  8912896,  8912896,  },
        /* level: 6.0       6.1       6.2       */
                { 35651584, 35651584, 35651584, }
    };

    // ITU-T H.265 04/2013 A.4.1

    const IMG_UINT32 ui32MaxDpbPicBuf = 6;

    // this is rounded to whole Ctbs
    IMG_UINT32 ui32PicSizeInSamplesY =
        psComSequHdrInfo->sFrameSize.ui32Height *
        psComSequHdrInfo->sFrameSize.ui32Width;

    IMG_UINT8 ui8LevelMaj, ui8LevelMin;
    IMG_UINT32 ui32MaxLumaPs;

    /* some error resilience */
    if (psComSequHdrInfo->ui32CodecLevel > HEVC_LEVEL_IDC_MAX
        || psComSequHdrInfo->ui32CodecLevel < HEVC_LEVEL_IDC_MIN)
    {
        REPORT(REPORT_MODULE_VDECDD,
               REPORT_NOTICE,
               "HEVC Codec level out of range: %u, falling back to %u",
               psComSequHdrInfo->ui32CodecLevel,
               psComSequHdrInfo->ui32MinPicBufNum);

        *pui32MaxRefPicNum = psComSequHdrInfo->ui32MinPicBufNum;
        return IMG_SUCCESS;
    }

    ui8LevelMaj = psComSequHdrInfo->ui32CodecLevel / 30;
    ui8LevelMin = (psComSequHdrInfo->ui32CodecLevel % 30) / 3;
    IMG_ASSERT(ui8LevelMaj > 0);
    ui32MaxLumaPs = aui32MaxLumaPs[ui8LevelMaj - 1][ui8LevelMin];

    if (ui32MaxLumaPs == 0)
    {
        REPORT(REPORT_MODULE_VDECDD,
               REPORT_ERR,
               "Wrong HEVC level value: %u.%u (general_level_idc: %u)",
               ui8LevelMaj,
               ui8LevelMin,
               psComSequHdrInfo->ui32CodecLevel);

        return IMG_ERROR_VALUE_OUT_OF_RANGE;
    }

    if (ui32MaxLumaPs < ui32PicSizeInSamplesY)
    {
        REPORT(REPORT_MODULE_VDECDD,
               REPORT_WARNING,
               "HEVC PicSizeInSamplesY too large for level (%u > %u)",
               ui32PicSizeInSamplesY,
               ui32MaxLumaPs);
    }

    #define DPB_MIN(a,b) (((a) <= (b)) ? (a) : (b))

    if (ui32PicSizeInSamplesY <= (ui32MaxLumaPs >> 2))
    {
        *pui32MaxRefPicNum = DPB_MIN(4 * ui32MaxDpbPicBuf, 16);
    }
    else if (ui32PicSizeInSamplesY <= (ui32MaxLumaPs >> 1))
    {
        *pui32MaxRefPicNum = DPB_MIN(2 * ui32MaxDpbPicBuf, 16);
    }
    else if (ui32PicSizeInSamplesY <= ((3 * ui32MaxLumaPs) >> 2))
    {
        *pui32MaxRefPicNum = DPB_MIN((4 * ui32MaxDpbPicBuf) / 3, 16);
    }
    else
    {
        *pui32MaxRefPicNum = ui32MaxDpbPicBuf;
    }

    #undef DPB_MIN

    //(*pui32MaxRefPicNum) += 2;

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_OooPicMpeg2GetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_OooPicMpeg2GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
)
{

    // Set the maximum number of required pictures as the default in case
    // the profile is specified incorrectly.
    *pui32MaxOooPicNum = 2;

    /* For MPEG-2 the maximum number of out-of-(display)-order pictures
     * is based on the profile only. */
    switch (psComSequHdrInfo->ui32CodecProfile)
    {
        case MPEG2_PROFILE_SIMPLE:
#ifdef FORCE_PROFILE_PROPERTIES
            /* B pictures are not supported. */
            *pui32MaxOooPicNum = 1;
#endif
            break;

        case MPEG2_PROFILE_MAIN:
        case MPEG2_PROFILE_SNR_SCALABLE:
        case MPEG2_PROFILE_SPATIALLY_SCALABLE:
        case MPEG2_PROFILE_HIGH:
        case MPEG2_PROFILE_MVP_LL:
        case MPEG2_PROFILE_MVP_ML:
        case MPEG2_PROFILE_MVP_HIGH1440:
        case MPEG2_PROFILE_MVP_HL:
        case MPEG2_PROFILE_422_LL:
        case MPEG2_PROFILE_422_HL:
#ifdef FORCE_PROFILE_PROPERTIES
            /* B pictures are supported. */
            *pui32MaxOooPicNum = 2;
#endif
            break;

        default:
            REPORT(REPORT_MODULE_VDECDD, REPORT_WARNING,
                   "Wrong MPEG2 profile value: %u\n",
                   psComSequHdrInfo->ui32CodecProfile);
            break;
    }

    /* Return success. */
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              vdecddutils_OooPicMpeg4SHeadersGetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_OooPicMpeg4SHeadersGetMaxNum(
    const VDEC_sComSequHdrInfo *  psComSequHdrInfo,
    IMG_UINT32 *            pui32MaxOooPicNum
)
{
    /* For MPEG-4 short headers the maximum number of out-of-(display)-order pictures
     * is not based upon the profile. */
    *pui32MaxOooPicNum = 0;

    /* Return success. */
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              vdecddutils_OooPicMpeg4GetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_OooPicMpeg4GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
)
{
    // Set the maximum number of required pictures as the default in case
    // the profile is specified incorrectly.
    *pui32MaxOooPicNum = 1;

    /* For MPEG-4 the maximum number of out-of-(display)-order pictures
     * is based on the profile only. */
    /* NOTE: Following VIDDEC, only Simple and Advanced Simple profiles are supported. */
    switch (psComSequHdrInfo->ui32CodecProfile)
    {
        case MPEG4_PROFILE_SIMPLE_L0:
        case MPEG4_PROFILE_SIMPLE_L1:
        case MPEG4_PROFILE_SIMPLE_L2:
        case MPEG4_PROFILE_SIMPLE_L3:
#ifdef FORCE_PROFILE_PROPERTIES
            /* B pictures are not supported. */
           *pui32MaxOooPicNum = 0;
#endif
            break;

        case MPEG4_PROFILE_ADVANCED_SIMPLE_L0:
        case MPEG4_PROFILE_ADVANCED_SIMPLE_L1:
        case MPEG4_PROFILE_ADVANCED_SIMPLE_L2:
        case MPEG4_PROFILE_ADVANCED_SIMPLE_L3:
        case MPEG4_PROFILE_ADVANCED_SIMPLE_L4:
        case MPEG4_PROFILE_ADVANCED_SIMPLE_L5:
        case MPEG4_PROFILE_ADVANCED_SIMPLE_L3b:
#ifdef FORCE_PROFILE_PROPERTIES
            /* B pictures are supported. */
            *pui32MaxOooPicNum = 1;
#endif
            break;

        case MPEG4_PROFILE_SIMPLE_SCLABLE_L2:
        case MPEG4_PROFILE_CORE_L2:
        case MPEG4_PROFILE_MAIN_L4:
        case MPEG4_PROFILE_FGS_L5:
        case MPEG4_PROFILE_NBIT_L2:
        case MPEG4_PROFILE_SCALABLE_TEXTURE_L1:
        case MPEG4_PROFILE_BASIC_SIMPLE_FACE_L2:
        case MPEG4_PROFILE_SIMPLE_FBA_L2:
        case MPEG4_PROFILE_BASIC_ANIMATED_TEXTURE_L2:
        case MPEG4_PROFILE_ADVANCED_REAL_TIME_SIMPLE_L4:
        case MPEG4_PROFILE_CORE_SCALABLE_L3:
        case MPEG4_PROFILE_ADVANCED_CODING_EFFIENCY_L4:
        case MPEG4_PROFILE_ADVANCED_SCALABLE_TEXTURE_L3:
        case MPEG4_PROFILE_SIMPLE_STUDIO_L4:
        case MPEG4_PROFILE_CORE_STUDIO_L4:
#ifdef FORCE_PROFILE_PROPERTIES
            *pui32MaxOooPicNum = 1;
#endif
            break;

        default:
            REPORT(REPORT_MODULE_VDECDD, REPORT_WARNING,
                   "Wrong MPEG4 profile value: %u\n",
                   psComSequHdrInfo->ui32CodecProfile);
            break;
    }

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_OooPicH264GetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_OooPicH264GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
)
{
    /* For H.264 the maximum number of out-of-(display)-order pictures is equal
     * to the maximum number of reference frames. */
    return vdecddutils_RefPicH264GetMaxNum(psComSequHdrInfo, pui32MaxOooPicNum);
}


/*!
******************************************************************************

 @Function              vdecddutils_OooPicVc1GetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_OooPicVc1GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
)
{
    // Set the maximum number of required pictures as the default in case
    // the profile is specified incorrectly.
    *pui32MaxOooPicNum = 1;

    /* For VC-1 the maximum number of out-of-(display)-order pictures
     * is based on the profile only. */
    switch (psComSequHdrInfo->ui32CodecProfile)
    {
        case VC1_PROFILE_SIMPLE:
#ifdef FORCE_PROFILE_PROPERTIES
            /* B pictures are not supported. */
            *pui32MaxOooPicNum = 0;
#endif
            break;

        case VC1_PROFILE_MAIN:
        case VC1_PROFILE_ADVANCED:
#ifdef FORCE_PROFILE_PROPERTIES
            /* B pictures are supported. */
            *pui32MaxOooPicNum = 1;
#endif
            break;

        default:
            REPORT(REPORT_MODULE_VDECDD, REPORT_WARNING,
                   "Wrong VC1 profile value: %u\n",
                   psComSequHdrInfo->ui32CodecProfile);
            break;
    }

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_OooPicAvsGetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_OooPicAvsGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
)
{
    /* For AVS the maximum number of out-of-(display)-order pictures is constant. */
    /* B pictures are always supported. */
    *pui32MaxOooPicNum = 1;

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_OooPicRealGetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_OooPicRealGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
)
{
    /* For RealVideo the maximum number of out-of-(display)-order pictures
     * is constant. */
    /* B pictures are always supported. */
    *pui32MaxOooPicNum = 1;

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_OooPicJpegGetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_OooPicJpegGetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
)
{
    /* No out-of-(display)-order frames for JPEG. */
    *pui32MaxOooPicNum = 0;

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_OooPicVp6GetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_OooPicVp6GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
)
{
    /* No out-of-(display)-order frames for VP6. */
    *pui32MaxOooPicNum = 0;

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              vdecddutils_OooPicVp8GetMaxNum

******************************************************************************/
static IMG_RESULT vdecddutils_OooPicVp8GetMaxNum(
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32MaxOooPicNum
)
{
    /* No out-of-(display)-order frames for VP8. */
    *pui32MaxOooPicNum = 0;

    /* Return success. */
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              VDECDDUTILS_RefPictGetMaxNum

 ******************************************************************************/
IMG_RESULT VDECDDUTILS_RefPictGetMaxNum(
    const VDEC_sStrConfigData   * psStrConfigData,
    const VDEC_sComSequHdrInfo  * psComSequHdrInfo,
    IMG_UINT32                  * pui32NumPicts
)
{
    IMG_RESULT ui32Result = IMG_SUCCESS;

    /* Validate input params. */
    if ((VDEC_STD_UNDEFINED == psStrConfigData->eVidStd) || (psStrConfigData->eVidStd >= VDEC_STD_MAX))
    {
        return IMG_ERROR_VALUE_OUT_OF_RANGE;
    }

    /* Call the function related to the provided video standard. */
    ui32Result = aRefPicGetMaxNumFns[psStrConfigData->eVidStd - 1](psComSequHdrInfo, pui32NumPicts);
    if(ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,"[USERSID=0x%08X] Failed to get number of reference pictures", psStrConfigData->ui32UserStrId);
    }

    //For non-conformant stream use the max(*pui32NumPicts,psComSequHdrInfo->ui32MinPicBufNum)
    if(*pui32NumPicts < psComSequHdrInfo->ui32MinPicBufNum)
    {
        *pui32NumPicts = psComSequHdrInfo->ui32MinPicBufNum;
    }

    if(psComSequHdrInfo->ui32NumViews > 1)
    {
        *pui32NumPicts *= 2;
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              VDECDDUTILS_OooPictGetMaxNum

 ******************************************************************************/
IMG_RESULT VDECDDUTILS_OooPictGetMaxNum(
    const VDEC_sStrConfigData  * psStrConfigData,
    const VDEC_sComSequHdrInfo * psComSequHdrInfo,
    IMG_UINT32                 * pui32NumPicts
)
{
    IMG_RESULT ui32Result = IMG_SUCCESS;

    /* Validate input params. */
    if ((VDEC_STD_UNDEFINED == psStrConfigData->eVidStd) || (psStrConfigData->eVidStd >= VDEC_STD_MAX))
    {
        return IMG_ERROR_VALUE_OUT_OF_RANGE;
    }

    /* Call the function related to the provided video standard. */
    ui32Result = aOooPicGetMaxNumFns[psStrConfigData->eVidStd - 1](psComSequHdrInfo, pui32NumPicts);
    IMG_ASSERT(IMG_SUCCESS == ui32Result);

    //For non-conformant stream use the max(*pui32NumPicts,psComSequHdrInfo->ui32MinPicBufNum)
    if(*pui32NumPicts < psComSequHdrInfo->ui32MinPicBufNum)
    {
        *pui32NumPicts = psComSequHdrInfo->ui32MinPicBufNum;
    }

    return ui32Result;
}

/*!
******************************************************************************

 @Function              VDECDDUTILS_IsSecondaryOutputRequired

 ******************************************************************************/
IMG_BOOL
VDECDDUTILS_IsSecondaryOutputRequired(
    const VDEC_sComSequHdrInfo    * psComSequHdrInfo,
    const VDEC_sStrOutputConfig   * psOutputConfig
)
{
    IMG_BOOL bResult = IMG_TRUE;

    if (IMG_FALSE == psOutputConfig->bScale &&
        IMG_FALSE == psOutputConfig->bForceOold &&
        IMG_FALSE == psComSequHdrInfo->bPostProcessing &&
        VDEC_ROTATE_0 == psOutputConfig->eRotMode &&
        psComSequHdrInfo->sPixelInfo.eChromaFormatIdc == psOutputConfig->sPixelInfo.eChromaFormatIdc &&
        psComSequHdrInfo->sPixelInfo.ui32BitDepthY == psOutputConfig->sPixelInfo.ui32BitDepthY &&
        psComSequHdrInfo->sPixelInfo.ui32BitDepthC == psOutputConfig->sPixelInfo.ui32BitDepthC)
    {
        //The secondary output is not required (if we have it we will not use it for
        //transformation (e.g. scaling. rotating or up/down-sampling).
        bResult = IMG_FALSE;
    }

    return bResult;
}

/*!
******************************************************************************

 @Function              VDECDDUTILS_GetMinRequiredNumPicts

 ******************************************************************************/
IMG_RESULT
VDECDDUTILS_GetMinRequiredNumPicts(
    const VDEC_sStrConfigData     * psStrConfigData,
    const VDEC_sComSequHdrInfo    * psComSequHdrInfo,
    const VDEC_sStrOutputConfig   * psOutputConfig,
    IMG_UINT32                    * pui32NumPicts
)
{
    IMG_RESULT ui32Result;
    IMG_UINT32 ui32MaxHeldPicNum;

    /* If any operation requiring internal buffers is to be applied... */
    if ( IMG_TRUE == VDECDDUTILS_IsSecondaryOutputRequired( psComSequHdrInfo, psOutputConfig ) )
    {
        /* ...reference picture buffers will be allocated internally, but there may be a number of picture
         * buffers to which out-of-display-order pictures will be decoded. These buffers need to be allocated
         * externally, so there's a need to calculate the number of out-of-(display)-order pictures required
         * for the provided video standard. */

        ui32Result = VDECDDUTILS_RefPictGetMaxNum(psStrConfigData, psComSequHdrInfo, &ui32MaxHeldPicNum);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }
    }
    /* Otherwise... */
    else
    {
        /* ...all the reference picture buffers have to be allocated externally, so there's a need to calculate
         * the number of reference picture buffers required for the provided video standard. */
        ui32Result = VDECDDUTILS_RefPictGetMaxNum(psStrConfigData, psComSequHdrInfo, &ui32MaxHeldPicNum);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }
    }

    /* Calculate the number of picture buffers required as the maximum number of picture buffers
     * to be held onto by the driver plus the current picture buffer. */
    *pui32NumPicts = ui32MaxHeldPicNum + (psComSequHdrInfo->bInterlacedFrames?2:1);  // 2 or 1 for decode

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              vdecddutils_UpdateRendPictSize

******************************************************************************/
static IMG_RESULT
vdecddutils_UpdateRendPictSize(
    VDEC_sPictSize      sPictSize,
    VDEC_sPictSize    * psRendPictSize
)
{
    if (psRendPictSize->ui32Width == 0)
    {
        psRendPictSize->ui32Width = sPictSize.ui32Width;
    }
    else
    {
        // Take the smallest resolution supported by all of the planes.
        psRendPictSize->ui32Width = (sPictSize.ui32Width < psRendPictSize->ui32Width)
                                  ? sPictSize.ui32Width : psRendPictSize->ui32Width;
    }
    if (psRendPictSize->ui32Height == 0)
    {
        psRendPictSize->ui32Height = sPictSize.ui32Height;
    }
    else
    {
        // Take the smallest resolution supported by all of the planes.
        psRendPictSize->ui32Height = (sPictSize.ui32Height < psRendPictSize->ui32Height)
                                   ? sPictSize.ui32Height : psRendPictSize->ui32Height;
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              vdecddutils_UpdateRendPictSize

******************************************************************************/
static IMG_RESULT
vdecddutils_GetCodedSize(
    const VDEC_sPictRendConfig    * psPictRendConfig,
    VDEC_eRotMode                   eRotation,
    VDEC_sPictSize                * psDecodedPictSize
)
{
    // Rotate picture to decoded orientation by swapping width and height.
    if (eRotation == VDEC_ROTATE_90 || eRotation == VDEC_ROTATE_270)
    {
        psDecodedPictSize->ui32Width = psPictRendConfig->sCodedPictSize.ui32Height;
        psDecodedPictSize->ui32Height = psPictRendConfig->sCodedPictSize.ui32Width;
    }
    else
    {
        psDecodedPictSize->ui32Width = psPictRendConfig->sCodedPictSize.ui32Width;
        psDecodedPictSize->ui32Height = psPictRendConfig->sCodedPictSize.ui32Height;
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              VDECDDUTILS_BufMsvdxAdjustSize

******************************************************************************/
IMG_VOID VDECDDUTILS_BufMsvdxAdjustSize(
    IMG_UINT32 *  pui32BufSize
)
{
    /* Align the buffer size to MSVDX page size. */
    *pui32BufSize = VDEC_ALIGN_SIZE(*pui32BufSize, VDEC_MSVDX_BUF_ALIGNMENT);
}



/*
******************************************************************************

 @Function              VDECDDUTILS_GetStrideCode

******************************************************************************/
IMG_UINT32 VDECDDUTILS_GetStrideCode(
    VDEC_eVidStd    eVidStd,
    IMG_UINT32      ui32RowStride
)
{
    IMG_UINT32 i;

    if (eVidStd == VDEC_STD_JPEG)
    {
        for (i = 0; i < VDEC_ARRAY_SIZE(caui32MsvdxJpegRowStride); i++)
        {
            if (caui32MsvdxJpegRowStride[i] == ui32RowStride)
            {
                return i;
            }
        }
    }
    else
    {
        for (i = 0; i < VDEC_ARRAY_SIZE(caui32Msvdx64ByteRowStride); i++)
        {
            if (caui32Msvdx64ByteRowStride[i] == ui32RowStride)
            {
                return i;
            }
        }
    }

    return -1;
}



/*!
******************************************************************************

 @Function              vdecddutils_GetTiledRowStride

******************************************************************************/
static IMG_UINT32 vdecddutils_GetTiledRowStride(
    IMG_UINT32                  ui32HorizStride,
    IMG_UINT32                  ui32VertSamples,
    VDEC_eColourPlanes          eColourPlane,
    VDEC_eTileScheme            eTileScheme,
    IMG_BOOL                    bPacked
)
{
    IMG_UINT32          i;
    const IMG_UINT32  * pui32TileStrides;
    IMG_UINT32          ui32NumStrides;

    IMG_ASSERT(eTileScheme > VDEC_TS_NONE && eTileScheme < VDEC_TS_MAX);

    switch (eTileScheme)
    {
    case VDEC_TS0_256x16:
        pui32TileStrides = aui32Tile256x16RowStride;
        ui32NumStrides = VDEC_ARRAY_SIZE(aui32Tile256x16RowStride);
        break;

    case VDEC_TS1_512x8:
        pui32TileStrides = aui32Tile512x8RowStride;
        ui32NumStrides = VDEC_ARRAY_SIZE(aui32Tile512x8RowStride);
        break;

    default:
        IMG_ASSERT(IMG_FALSE);
        return 0;
        break;
    }

    /* Test all tile strides and check alignment of plane to 4kB for packed buffers */
    for (i = 0; i < ui32NumStrides; i++)
    {
        if (bPacked && !IS_PACKEDBUF_CHROMA_ALIGNED(pui32TileStrides[i] * ui32VertSamples, eColourPlane))
        {
            // Skip this stride since it is not compatible with chroma.
            continue;
        }

        if (pui32TileStrides[i] >= ui32HorizStride)
        {
            break;
        }
    }

    return (i == ui32NumStrides) ? 0 : pui32TileStrides[i];
}



/*!
******************************************************************************

 @Function              vdecddutils_GetFixedRowStride

******************************************************************************/
static IMG_UINT32 vdecddutils_GetFixedRowStride(
    const VDEC_sStrConfigData * psStrConfigData,
    IMG_UINT32                  ui32HorizStride,
    IMG_UINT32                  ui32VertSamples,
    VDEC_eColourPlanes          eColourPlane,
    IMG_BOOL                    bPacked
)
{
    /* Try indexed strides. */
    if (psStrConfigData->eVidStd == VDEC_STD_JPEG)
    {
        IMG_UINT32 i;

        /* Find the appropriate stride. */
        for (i = 0; i < VDEC_ARRAY_SIZE(caui32MsvdxJpegRowStride); i++)
        {
            if (caui32MsvdxJpegRowStride[i] >= ui32HorizStride)
            {
                return caui32MsvdxJpegRowStride[i];
            }
        }
    }
    else
    {
        IMG_UINT32 i, j;

        /* Test all strides ( video first ) and check alignment of plane to 4kB for packed buffers */
        for (i = 0; i < VDEC_ARRAY_SIZE(caui32Msvdx64ByteRowStride); i++)
        {
            if (bPacked && !IS_PACKEDBUF_CHROMA_ALIGNED(caui32Msvdx64ByteRowStride[i] * ui32VertSamples, eColourPlane))
            {
                // Skip this stride since it is not compatible with chroma.
                continue;
            }

            if (caui32Msvdx64ByteRowStride[i] >= ui32HorizStride)
            {
                break;
            }
        }

        /* Test 512-byte aligned strides and check alignment of plane to 4kB for packed buffers */
        for (j = 4; j < VDEC_ARRAY_SIZE(caui32Msvdx64ByteRowStride); j++)
        {
            if (bPacked && !IS_PACKEDBUF_CHROMA_ALIGNED(caui32Msvdx64ByteRowStride[j] * ui32VertSamples, eColourPlane))
            {
                // Skip this stride since it is not compatible with chroma.
                continue;
            }

            if (caui32Msvdx64ByteRowStride[j] >= ui32HorizStride)
            {
                break;
            }
        }

        if((i < VDEC_ARRAY_SIZE(caui32Msvdx64ByteRowStride)) && (j < VDEC_ARRAY_SIZE(caui32Msvdx64ByteRowStride)))
        {
            /* Return the appropriate stride. */
            return caui32Msvdx64ByteRowStride[i] < caui32Msvdx64ByteRowStride[j] ?
                                caui32Msvdx64ByteRowStride[i] : caui32Msvdx64ByteRowStride[j];
        }
    }

    return 0;
}



/*!
******************************************************************************

 @Function              vdecddutils_GetStride

******************************************************************************/
static IMG_RESULT vdecddutils_GetStride(
    const VDEC_sStrConfigData     * psStrConfigData,
    const VDEC_sPictRendConfig    * psPictRendConfig,
    IMG_UINT32                      ui32VertSamples,
    IMG_UINT32                    * pui32HorizStride,
    VDEC_eColourPlanes              eColourPlane,
    VDEC_eRotMode                   eRotMode,
    IMG_BOOL                        bAllocRotation
)
{
    IMG_UINT32 ui32HwHorizStride = *pui32HorizStride;

#ifdef HAS_HEVC
    if ((eRotMode != VDEC_ROTATE_0 || bAllocRotation)
        && psStrConfigData->eVidStd == VDEC_STD_HEVC)
    {
        ui32HwHorizStride = (ui32HwHorizStride / VDEC_PVDEC_BURST4_SIZE + 1)
                            * VDEC_PVDEC_BURST4_SIZE;
    }
#endif

    if (!psPictRendConfig->bUseExtendedStrides)
    {
        if (psPictRendConfig->eTileScheme == VDEC_TS_NONE)
        {
            ui32HwHorizStride = vdecddutils_GetFixedRowStride(psStrConfigData,
                                                              ui32HwHorizStride,
                                                              ui32VertSamples,
                                                              eColourPlane,
                                                              psPictRendConfig->bPacked);
        }
        else
        {
            ui32HwHorizStride = vdecddutils_GetTiledRowStride(ui32HwHorizStride,
                                                              ui32VertSamples,
                                                              eColourPlane,
                                                              psPictRendConfig->eTileScheme,
                                                              psPictRendConfig->bPacked);
        }
    }
    else
    {
        if (psPictRendConfig->eTileScheme != VDEC_TS_NONE)
        {
            ui32HwHorizStride = vdecddutils_GetTiledRowStride(ui32HwHorizStride,
                                                              ui32VertSamples,
                                                              eColourPlane,
                                                              psPictRendConfig->eTileScheme,
                                                              psPictRendConfig->bPacked);
        }

        /* If extended strides are to be used or indexed strides failed,
         * make extended stride alignment. */
        ui32HwHorizStride = VDEC_ALIGN_SIZE(ui32HwHorizStride, VDEC_MSVDX_EXT_STRIDE_ALIGNMENT);
    }

    // A zero-value indicates unsupported stride.
    if (ui32HwHorizStride == 0)
    {
        // No valid stride found.
        IMG_ASSERT(IMG_FALSE);

        return IMG_ERROR_NOT_SUPPORTED;
    }

    *pui32HorizStride = ui32HwHorizStride;

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              vdecddutils_GetRenderInfo1

******************************************************************************/
static IMG_RESULT
vdecddutils_GetRenderInfo1(
    const VDEC_sStrConfigData    * psStrConfigData,
    const VDEC_sPictRendConfig   * psPictRendConfig,
    const PIXEL_sPixelInfo       * psPixelInfo,
    VDEC_eRotMode                  eOrientation,
    VDEC_sPictRendInfo           * psPictBufInfo,
    IMG_BOOL                       bAllocRotation
)
{
    IMG_UINT32              i;
    IMG_sPixelFormatDesc    sPixFmt;
    VDEC_sPictSize          sCodedPictSize;
    IMG_BOOL                bSingleStride = IMG_FALSE;
    IMG_UINT32              aui32VertSamples[IMG_MAX_NUM_PLANES];
    IMG_UINT32              ui32TotalVertSamples;
    IMG_UINT32              ui32LargestStride;
    IMG_UINT32              ui32Result;

    /* Reset the output structure. */
    VDEC_BZERO(psPictBufInfo);

    // Ensure that the coded sizes are in whole macroblocks.
    if ((psPictRendConfig->sCodedPictSize.ui32Width & (VDEC_MB_DIMENSION-1)) != 0 ||
        (psPictRendConfig->sCodedPictSize.ui32Height & (VDEC_MB_DIMENSION-1)) != 0)
    {
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
               "Invalid render configuration coded picture size [%dx%d]. It should be a whole number of MBs in each dimension",
               psPictRendConfig->sCodedPictSize.ui32Width,
               psPictRendConfig->sCodedPictSize.ui32Height);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* Get pixel format info for regular pixel formats... */
    if ((psPixelInfo->ePixelFormat < IMG_PIXFMT_ARBPLANAR8))
    {
        /* Get pixel format info */
        PIXEL_YUVGetDescriptor((PIXEL_sPixelInfo*)psPixelInfo, &sPixFmt);
    }
    /* ...or for factor specified pixel format (JPEG) */
    else
    {
        PIXEL_GetFormatDesc(psPixelInfo->ePixelFormat, &sPixFmt);
    }

    // Get the coded size for the appropriate orientation.
    ui32Result = vdecddutils_GetCodedSize(psPictRendConfig,
                                          eOrientation,
                                          &sCodedPictSize);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    // Calculate the hardware (inc. constraints) strides and
    // number of vertical samples for each plane.
    ui32TotalVertSamples = 0;
    ui32LargestStride = 0;
    for (i = 0; i < IMG_MAX_NUM_PLANES; i++)
    {
        if (sPixFmt.abPlanes[i])
        {
            IMG_UINT32  ui32HorizStride;

            // Horizontal stride must be for a multiple of BOPs.
            ui32HorizStride = ((sCodedPictSize.ui32Width + sPixFmt.ui32BOPDenom - 1) / sPixFmt.ui32BOPDenom)
                                    * sPixFmt.aui32BOPNumer[i];
            // Vertical only has to satisfy whole pixel of samples.
            aui32VertSamples[i] = ((sCodedPictSize.ui32Height + sPixFmt.ui32VDenom - 1) / sPixFmt.ui32VDenom)
                                    * sPixFmt.aui32VNumer[i];

            // Obtain a horizontal stride supported by the hardware (inc. constraints).
            ui32Result = vdecddutils_GetStride(psStrConfigData,
                                               psPictRendConfig,
                                               aui32VertSamples[i],
                                               &ui32HorizStride,
                                               i,
                                               eOrientation,
                                               bAllocRotation);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                if (ui32Result == IMG_ERROR_NOT_SUPPORTED)
                {
                    REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
                           "No valid MSVDX stride found for picture with decoded dimensions [%dx%d] and min stride [%d]",
                           sCodedPictSize.ui32Width,
                           sCodedPictSize.ui32Height,
                           ui32HorizStride);
                }
                return ui32Result;
            }

            psPictBufInfo->asPlaneInfo[i].ui32Stride = ui32HorizStride;
            if((i == VDEC_PLANE_VIDEO_UV) && (psPictRendConfig->bUseExtendedStrides) && (psStrConfigData->eVidStd == VDEC_STD_H264))
            {
                PIXEL_sPixelInfo *info = PIXEL_GetPixelInfo(psPixelInfo->ePixelFormat);
                IMG_ASSERT(PIXEL_FORMAT_INVALID != info->eChromaFormatIdc);
                if ((info->eChromaFormatIdc == PIXEL_FORMAT_444) && !sPixFmt.abPlanes[VDEC_PLANE_VIDEO_V])
                {
                    // 444 format and not separate colour planes
                    psPictBufInfo->asPlaneInfo[i].ui32Stride = psPictBufInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride * 2;
                }
            }

            ui32TotalVertSamples += aui32VertSamples[i];
            if (ui32HorizStride > ui32LargestStride)
            {
                ui32LargestStride = ui32HorizStride;
            }
        }
    }

    if (psPictRendConfig->bPacked)
    {
        // Packed buffers must have a single stride.
        bSingleStride = IMG_TRUE;
    }

    if (psPictRendConfig->eTileScheme != VDEC_TS_NONE)
    {
        bSingleStride = IMG_TRUE;
    }

    // JPEG hardware uses a single (luma) stride for all planes.
    if (psStrConfigData->eVidStd == VDEC_STD_JPEG)
    {
        bSingleStride = IMG_TRUE;

        // Luma should be largest for this to be used for all planes.
        IMG_ASSERT(ui32LargestStride == psPictBufInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride);
    }

    // Calculate plane sizes.
    for (i = 0; i < IMG_MAX_NUM_PLANES; i++)
    {
        if (sPixFmt.abPlanes[i])
        {
            VDEC_sPictSize  sPictSize;
            IMG_UINT32 ui32VertSamples = aui32VertSamples[i];

            if (bSingleStride)
            {
                psPictBufInfo->asPlaneInfo[i].ui32Stride = ui32LargestStride;
            }

            psPictBufInfo->asPlaneInfo[i].ui32Size = psPictBufInfo->asPlaneInfo[i].ui32Stride * ui32VertSamples;

            // Ensure that the total buffer rendered size is rounded-up to the picture buffer alignment
            // so that this plane (within this single buffer) can be correctly addressed by the hardware at this byte offset.
            if (i == 1 && psPictRendConfig->bPacked)
            {
                // Packed buffers must have chroma plane already aligned since this was factored into the stride/size calculation.
                IMG_ASSERT(psPictBufInfo->ui32RenderedSize == VDEC_ALIGN_SIZE(psPictBufInfo->ui32RenderedSize, VDEC_MSVDX_PICTBUF_ALIGNMENT));
            }
            psPictBufInfo->ui32RenderedSize = VDEC_ALIGN_SIZE(psPictBufInfo->ui32RenderedSize, VDEC_MSVDX_PICTBUF_ALIGNMENT);
            psPictBufInfo->asPlaneInfo[i].ui32Offset = psPictBufInfo->ui32RenderedSize;

            /* Update the total buffer size (inc. this plane). */
            psPictBufInfo->ui32RenderedSize += psPictBufInfo->asPlaneInfo[i].ui32Size;

            // Update the maximum render picture size supported by all planes of this buffer.
            sPictSize.ui32Width = (psPictBufInfo->asPlaneInfo[i].ui32Stride * sPixFmt.ui32BOPDenom) / sPixFmt.aui32BOPNumer[i];
            sPictSize.ui32Height = (aui32VertSamples[i] * sPixFmt.ui32VDenom) / sPixFmt.aui32VNumer[i];
            ui32Result = vdecddutils_UpdateRendPictSize(sPictSize, &psPictBufInfo->sRendPictSize);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            DEBUG_REPORT(REPORT_MODULE_VDECDD,
                         "vdecddutils_GetRenderInfo() plane %d stride %u size %u offset %u",
                         i,
                         psPictBufInfo->asPlaneInfo[i].ui32Stride,
                         psPictBufInfo->asPlaneInfo[i].ui32Size,
                         psPictBufInfo->asPlaneInfo[i].ui32Offset);
        }
    }

    // Tiled buffers must be rounded-up to the nearest whole tile in both dimensions.
    // Since all VDEC pictures are stored in a single buffer these restrictions can
    // be satisfied once for all planes.
    // The strides for each plane must be the same and will have been selected to fit within
    // the virtual memory heaps.
    // Now the buffer height must be rounded-up to a whole number of samples in tile height.
    if (psPictRendConfig->eTileScheme != VDEC_TS_NONE)
    {
        IMG_UINT32  ui32VertSampAlign = 1;      // vertical alignment in samples.
        IMG_UINT32  ui32RenderRegion;

        // Vertical alignment is governed by height of tile.
        if (psPictRendConfig->eTileScheme == VDEC_TS1_512x8)
        {
            ui32VertSampAlign = 8;
        }
        else if (psPictRendConfig->eTileScheme == VDEC_TS0_256x16)
        {
            ui32VertSampAlign = 16;
        }

        ui32TotalVertSamples = VDEC_ALIGN_SIZE(ui32TotalVertSamples, ui32VertSampAlign);
        ui32RenderRegion = ui32LargestStride * ui32TotalVertSamples;

        // For tiling size should be rounded up to whole rows of tiles.
        switch(psPictRendConfig->eTileScheme)
        {
        case VDEC_TS0_256x16:
            ui32RenderRegion = VDEC_ALIGN_SIZE(ui32RenderRegion, 16*ui32LargestStride);
            break;
        case VDEC_TS1_512x8:
            ui32RenderRegion = VDEC_ALIGN_SIZE(ui32RenderRegion, 8*ui32LargestStride);
            break;
        default:
            break;
        }

        // Render region occupied by tiles must be larger than sum of all plane sizes.
        IMG_ASSERT(ui32RenderRegion >= psPictBufInfo->ui32RenderedSize);
        psPictBufInfo->ui32RenderedSize = ui32RenderRegion;

    }

    /* Adjust picture buffer size for MSVDX. */
    psPictBufInfo->ui32RenderedSize = VDEC_ALIGN_SIZE(psPictBufInfo->ui32RenderedSize, VDEC_MSVDX_PICTBUF_ALIGNMENT);

    DEBUG_REPORT(REPORT_MODULE_VDECDD,
                 "vdecddutils_GetRenderInfo() total %u (inc. alignment for addressing/tiling)",
                 psPictBufInfo->ui32RenderedSize);

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              vdecddutils_GetRenderInfo

******************************************************************************/
static IMG_RESULT
vdecddutils_GetRenderInfo(
    const VDEC_sStrConfigData    * psStrConfigData,
    const VDEC_sPictRendConfig   * psPictRendConfig,
    const PIXEL_sPixelInfo       * psPixelInfo,
    VDEC_eRotMode                  eOrientation,
    IMG_BOOL                       bAllocRotation,
    VDEC_sPictRendInfo           * psPictBufInfo
)
{
    IMG_UINT32      ui32Result;

    if (psPictRendConfig->bPacked && bAllocRotation)
    {
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
               "Cannot define packed buffers that are rotatable. \
               Try again with bPacked = IMG_FALSE in VDEC_sPictRendConfig or bAllocRotation = IMG_FALSE");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    ui32Result = vdecddutils_GetRenderInfo1(psStrConfigData,
                                            psPictRendConfig,
                                            psPixelInfo,
                                            eOrientation,
                                            psPictBufInfo,
                                            bAllocRotation);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    if (bAllocRotation)
    {
        VDEC_sPictRendInfo  sRotPictBufInfo;
        VDEC_eRotMode       eRotatedOrientation;

        if (eOrientation == VDEC_ROTATE_0 ||
            eOrientation == VDEC_ROTATE_180)
        {
            eRotatedOrientation = VDEC_ROTATE_90;
        }
        else
        {
            eRotatedOrientation = VDEC_ROTATE_0;
        }

        ui32Result = vdecddutils_GetRenderInfo1(psStrConfigData,
                                                psPictRendConfig,
                                                psPixelInfo,
                                                eRotatedOrientation,
                                                &sRotPictBufInfo,
                                                bAllocRotation);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        if (sRotPictBufInfo.ui32RenderedSize > psPictBufInfo->ui32RenderedSize)
        {
            // Update the render size of picture buffer to allow for rotation if reconfigured.
            psPictBufInfo->ui32RenderedSize = sRotPictBufInfo.ui32RenderedSize;
        }
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              VDECDDUTILS_IsPacked

******************************************************************************/
IMG_BOOL VDECDDUTILS_IsPacked(
    const VDEC_sPictRendInfo  * psPictRendInfo
)
{
    IMG_BOOL bPacked = IMG_TRUE;

    /* Validate inputs. */
    IMG_ASSERT(psPictRendInfo);

    if (psPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Size !=
        psPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Offset)
    {
        // Planes that are not adjacent cannot be packed.
        bPacked = IMG_FALSE;
    }
    else if (!IS_PACKEDBUF_CHROMA_ALIGNED(psPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Offset, VDEC_PLANE_VIDEO_Y))
    {
        // Chroma plane must be aligned for packed buffers.
        IMG_ASSERT(psPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Size ==
                       psPictRendInfo->asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Offset);
        bPacked = IMG_FALSE;
    }

    return bPacked;
}



/*!
******************************************************************************

 @Function              VDECDDUTILS_PrintBufferProperties

******************************************************************************/
IMG_RESULT
VDECDDUTILS_PrintBufferProperties(
    const VDEC_sStrOutputConfig * psOutputConfig,
    const VDEC_sPictRendInfo    * psPictBufInfo,
    const VDEC_sPictBufConfig   * psPictBufConfig
)
{
    IMG_ASSERT(psOutputConfig);
    IMG_ASSERT(psPictBufInfo);
    if (psOutputConfig == IMG_NULL ||
        psPictBufInfo == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

#ifdef __RELEASE_RELEASE__
    if (psPictBufConfig)
    {
        DEBUG_REPORT(REPORT_MODULE_VDECDD,
                     "[%s] Coded:%ux%u, Rend:%ux%u, PixFmt:%d, TileScheme:%s, 128ByteInt:%s, Packed:%s, Pl[0]:{Type:%s, Offset:%u, Stride:%u, Size:%u}, Pl[1]:{Type:%s, Offset:%u, Stride:%u, Size:%u}, Pl[2]:{Type:%s, Offset:%u, Stride:%u, Size:%u}",
                     "Buffer Configuration",
                     psPictBufConfig->ui32CodedWidth,
                     psPictBufConfig->ui32CodedHeight,
                     psPictBufInfo->sRendPictSize.ui32Width,
                     psPictBufInfo->sRendPictSize.ui32Height,
                     psPictBufConfig->ePixelFormat,
                    (psPictBufConfig->eTileScheme == VDEC_TS_NONE) ? "Untiled" :
                        (psPictBufConfig->eTileScheme == VDEC_TS0_256x16) ? "VDEC_TS0_256x16" :
                        (psPictBufConfig->eTileScheme == VDEC_TS1_512x8) ? "VDEC_TS1_512x8" : "unknown",
                    psPictBufConfig->bByteInterleave ? "y" : "n",
                    psPictBufConfig->bPacked ? "y" : "n",
                    (0 == VDEC_PLANE_VIDEO_Y) ? "Y" : (0 == VDEC_PLANE_VIDEO_UV) ? "UV" : "Unknown",
                    psPictBufInfo->asPlaneInfo[0].ui32Offset,
                    psPictBufInfo->asPlaneInfo[0].ui32Stride,
                    psPictBufInfo->asPlaneInfo[0].ui32Size,
                    (1 == VDEC_PLANE_VIDEO_Y) ? "Y" : (1 == VDEC_PLANE_VIDEO_UV) ? "UV" : "Unknown",
                    psPictBufInfo->asPlaneInfo[1].ui32Offset,
                    psPictBufInfo->asPlaneInfo[1].ui32Stride,
                    psPictBufInfo->asPlaneInfo[1].ui32Size,
                    (2 == VDEC_PLANE_VIDEO_Y) ? "Y" : (2 == VDEC_PLANE_VIDEO_UV) ? "UV" : "Unknown",
                    psPictBufInfo->asPlaneInfo[2].ui32Offset,
                    psPictBufInfo->asPlaneInfo[2].ui32Stride,
                    psPictBufInfo->asPlaneInfo[2].ui32Size);
    }

#else

    if (psPictBufConfig)
    {
        DEBUG_REPORT(REPORT_MODULE_PLANT,
                     "Coded size:           %dx%d (pixels)",
                     psPictBufConfig->ui32CodedWidth,
                     psPictBufConfig->ui32CodedHeight);
    }

    DEBUG_REPORT(REPORT_MODULE_PLANT,
                 "Rendered size:        %dx%d (pixels)",
                 psPictBufInfo->sRendPictSize.ui32Width,
                 psPictBufInfo->sRendPictSize.ui32Height);

    if (psPictBufConfig)
    {
        DEBUG_REPORT(REPORT_MODULE_PLANT,
                     "Pixel Format:         %d",
                     psPictBufConfig->ePixelFormat);
        DEBUG_REPORT(REPORT_MODULE_PLANT,
                     "Tile Scheme:          %s",
                     (psPictBufConfig->eTileScheme == VDEC_TS_NONE) ? "Untiled" :
                     (psPictBufConfig->eTileScheme == VDEC_TS0_256x16) ? "VDEC_TS0_256x16" :
                     (psPictBufConfig->eTileScheme == VDEC_TS1_512x8) ? "VDEC_TS1_512x8" : "unknown");
        DEBUG_REPORT(REPORT_MODULE_PLANT,
                     "128Byte Interleave:   %s",
                     psPictBufConfig->bByteInterleave ? "yes" : "no");
        DEBUG_REPORT(REPORT_MODULE_PLANT,
                     "Packed:               %s",
                     psPictBufConfig->bPacked ? "yes" : "no");
    }

    DEBUG_REPORT(REPORT_MODULE_PLANT,
                 "Buffer size:          %d (bytes)",
                 psPictBufInfo->ui32RenderedSize);
    {
        IMG_UINT32 i;
        for (i = 0; i < psOutputConfig->sPixelInfo.ui32NoPlanes; i++)
        {
            DEBUG_REPORT(REPORT_MODULE_PLANT,
                         "Plane[%s]...",
                         (i == VDEC_PLANE_VIDEO_Y) ? "Y" :
                         (i == VDEC_PLANE_VIDEO_UV) ? "UV" :
                         "Unknown");

            DEBUG_REPORT(REPORT_MODULE_PLANT,
                         "    Offset:         %d (bytes)",
                         psPictBufInfo->asPlaneInfo[i].ui32Offset);
            DEBUG_REPORT(REPORT_MODULE_PLANT,
                         "    Stride:         %d (bytes)",
                         psPictBufInfo->asPlaneInfo[i].ui32Stride);
            DEBUG_REPORT(REPORT_MODULE_PLANT,
                         "    Size:           %d (bytes)",
                         psPictBufInfo->asPlaneInfo[i].ui32Size);
        }
    }

#endif

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              VDECDDUTILS_PictBufGetConfig

******************************************************************************/
IMG_RESULT VDECDDUTILS_PictBufGetConfig(
    const VDEC_sStrConfigData     * psStrConfigData,
    const VDEC_sPictRendConfig    * psPictRendConfig,
    IMG_BOOL                        bAllocRotation,
    const VDEC_sStrOutputConfig   * psStrOutputConfig,
    VDEC_sPictBufConfig           * psPictBufConfig
)
{
    VDEC_sPictRendInfo      sDispPictRendInfo;
    VDEC_sPictSize          sCodedPictSize;
    IMG_UINT32              ui32Result,i;

    /* Validate inputs. */
    IMG_ASSERT(psStrConfigData);
    IMG_ASSERT(psPictRendConfig);
    IMG_ASSERT(psStrOutputConfig);
    IMG_ASSERT(psPictBufConfig);

    // Clear the picture buffer config before populating.
    VDEC_BZERO(psPictBufConfig);

    // Determine the rounded-up coded sizes (compatible with hardware).
    ui32Result = vdecddutils_GetRenderInfo(psStrConfigData,
                                           psPictRendConfig,
                                           &psStrOutputConfig->sPixelInfo,
                                           psStrOutputConfig->eRotMode,
                                           bAllocRotation,
                                           &sDispPictRendInfo);
    IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
    // Get the coded size for the appropriate orientation.
    ui32Result = vdecddutils_GetCodedSize(psPictRendConfig,
                                          psStrOutputConfig->eRotMode,
                                          &sCodedPictSize);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
    psPictBufConfig->ui32CodedWidth = sCodedPictSize.ui32Width;
    psPictBufConfig->ui32CodedHeight = sCodedPictSize.ui32Height;

    // Use the luma stride for all planes in buffer.
    // Additional chroma stride may be needed for other pixel formats.
    for (i=0; i<VDEC_PLANE_MAX; i++)
        psPictBufConfig->aui32Stride[i] = sDispPictRendInfo.asPlaneInfo[i].ui32Stride;
#if 0
    if (psStrOutputConfig->sPixelInfo.ui32NoPlanes > 1)
    {
        // Current stride representation must be the same across all planes.
        IMG_ASSERT(psPictBufConfig->ui32Stride == sDispPictRendInfo.asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Stride);
    }
#endif
    // Pixel information is taken from that specified for display.
    psPictBufConfig->ePixelFormat = psStrOutputConfig->sPixelInfo.ePixelFormat;

    // Tiling scheme is taken from render configuration.
    psPictBufConfig->eTileScheme = psPictRendConfig->eTileScheme;

    // Chroma offset taken as calculated for render configuration.
    psPictBufConfig->aui32ChromaOffset[0] = sDispPictRendInfo.asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Offset;
    psPictBufConfig->aui32ChromaOffset[1] = sDispPictRendInfo.asPlaneInfo[VDEC_PLANE_VIDEO_V].ui32Offset;

    if (psPictRendConfig->bPacked &&
        psStrOutputConfig->sPixelInfo.ui32NoPlanes > 1)
    {
        psPictBufConfig->bPacked = VDECDDUTILS_IsPacked(&sDispPictRendInfo);
        if (!psPictBufConfig->bPacked)
        {
            // Report if unable to meet request to pack.
            REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
                "Request for packed buffer could not be met");
            return IMG_ERROR_NOT_SUPPORTED;
        }

        if (psPictRendConfig->bPacked)
        {
            if (psPictBufConfig->aui32ChromaOffset[0] != VDEC_ALIGN_SIZE(psPictBufConfig->aui32ChromaOffset[0], VDEC_MSVDX_PICTBUF_ALIGNMENT) ||
                psPictBufConfig->aui32ChromaOffset[1] != VDEC_ALIGN_SIZE(psPictBufConfig->aui32ChromaOffset[1], VDEC_MSVDX_PICTBUF_ALIGNMENT))
            {
                REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
                       "Chroma plane could not be located on a %d byte boundary (investigate stride calculations)",
                       VDEC_MSVDX_PICTBUF_ALIGNMENT);
                return IMG_ERROR_NOT_SUPPORTED;
            }
        }
    }
    else
    {
        psPictBufConfig->bPacked = IMG_FALSE;
    }

    psPictBufConfig->ui32BufSize = sDispPictRendInfo.ui32RenderedSize;

    /* Return success.*/
    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              VDECDDUTILS_PictBufGetInfo

******************************************************************************/
IMG_RESULT VDECDDUTILS_PictBufGetInfo(
    const VDEC_sStrConfigData     * psStrConfigData,
    const VDEC_sPictRendConfig    * psPictRendConfig,
    const VDEC_sStrOutputConfig   * psStrOutputConfig,
    VDEC_sPictRendInfo            * psPictRendInfo
)
{
    IMG_UINT32  ui32Result;

    /* Validate inputs. */
    IMG_ASSERT(psStrConfigData);
    IMG_ASSERT(psPictRendConfig);
    IMG_ASSERT(psStrOutputConfig);
    IMG_ASSERT(psPictRendInfo);

    ui32Result = vdecddutils_GetRenderInfo(psStrConfigData,
                                           psPictRendConfig,
                                           &psStrOutputConfig->sPixelInfo,
                                           psStrOutputConfig->eRotMode,
                                           IMG_FALSE,
                                           psPictRendInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Return success.*/
    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              VDECDDUTILS_ConvertBufferConfig

******************************************************************************/
IMG_RESULT VDECDDUTILS_ConvertBufferConfig(
    const VDEC_sStrConfigData   * psStrConfigData,
    const VDEC_sPictBufConfig   * psPictBufConfig,
    const VDEC_sComSequHdrInfo  * psComSequHdrInfo,
    VDEC_sPictRendInfo          * psPictRendInfo
)
{
    const PIXEL_sPixelInfo    * psPixelInfo;
    IMG_sPixelFormatDesc        sPixFmt;
    IMG_UINT32                  ui32Result;
    IMG_UINT32                  i;
    IMG_UINT32                  ui32TotalVertSamples = 0;
    IMG_UINT32                  aui32VertSamples[IMG_MAX_NUM_PLANES];
    IMG_UINT32                  ui32PlaneSize = 0;
    IMG_UINT32                  ui32PlaneOffset = 0;
    VDEC_sPictSize              sPictSize;

    /* Validate inputs. */
    IMG_ASSERT(psStrConfigData);
    IMG_ASSERT(psPictBufConfig);
    IMG_ASSERT(psComSequHdrInfo);
    IMG_ASSERT(psPictRendInfo);

    /* Reset picture buffer allocation data. */
    VDEC_BZERO(psPictRendInfo);

    /* Get pixel format info for regular pixel formats... */
    if ((psPictBufConfig->ePixelFormat < IMG_PIXFMT_ARBPLANAR8))
    {
        psPixelInfo = PIXEL_GetPixelInfo(psPictBufConfig->ePixelFormat);
        PIXEL_YUVGetDescriptor((PIXEL_sPixelInfo*)psPixelInfo, &sPixFmt);
    }
    /* ...or for factor specified pixel format (JPEG) */
    else
    {
        PIXEL_GetFormatDesc(psPictBufConfig->ePixelFormat, &sPixFmt);
    }

    // Construct the render region information from the picture buffer configuration.
    for (i = 0; i < IMG_MAX_NUM_PLANES; i++)
    {
        if (sPixFmt.abPlanes[i])
        {
            // Determine the offset (in bytes) to this plane.
            // This is zero for the first (luma) plane and at the end of the previous plane
            // for all subsequent planes.
            ui32PlaneOffset = ui32PlaneOffset + ui32PlaneSize;

            // Calculate the minimum number of vertical samples for this plane.
            aui32VertSamples[i] = ((psPictBufConfig->ui32CodedHeight + sPixFmt.ui32VDenom - 1) / sPixFmt.ui32VDenom)
                                        * sPixFmt.aui32VNumer[i];

            // Calculate the mimimum plane size from the stride and decode picture height.
            // Packed buffers have the luma and chroma exactly adjacent and consequently
            // the chroma plane offset is equal to this plane size.
            ui32PlaneSize = psPictBufConfig->aui32Stride[i] * aui32VertSamples[i];

            if (!psPictBufConfig->bPacked && psPictBufConfig->aui32ChromaOffset[i])
            {
                IMG_UINT32 ui32MaxPlaneSize;
                ui32MaxPlaneSize = psPictBufConfig->aui32ChromaOffset[i] - ui32PlaneOffset;

                if (ui32PlaneSize > ui32MaxPlaneSize)
                {
                    REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
                           "Chroma offset [%d bytes] is not large enough to fit minimum plane data [%d bytes] at offset [%d]",
                           psPictBufConfig->aui32ChromaOffset[i], ui32PlaneSize, ui32PlaneOffset);
                    return IMG_ERROR_INVALID_PARAMETERS;
                }

                ui32PlaneSize = ui32MaxPlaneSize;

                aui32VertSamples[i] = ui32PlaneSize / psPictBufConfig->aui32Stride[i];
            }
            else
            {
                if (psPictBufConfig->aui32ChromaOffset[i] &&
                    (ui32PlaneOffset + ui32PlaneSize) != psPictBufConfig->aui32ChromaOffset[i])
                {
                    REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
                           "Chroma offset specified [%d bytes] should match that required for plane size calculated from stride and height [%d bytes]",
                           psPictBufConfig->aui32ChromaOffset[i], ui32PlaneOffset + ui32PlaneSize);
                    return IMG_ERROR_INVALID_PARAMETERS;
                }
            }

            psPictRendInfo->asPlaneInfo[i].ui32Offset = ui32PlaneOffset;
            psPictRendInfo->asPlaneInfo[i].ui32Stride = psPictBufConfig->aui32Stride[i];
            psPictRendInfo->asPlaneInfo[i].ui32Size = ui32PlaneSize;

            DEBUG_REPORT(REPORT_MODULE_VDECDD,
                         "VDECDDUTILS_ConvertBufferConfig() plane %d stride %u size %u offset %u",
                         i,
                         psPictRendInfo->asPlaneInfo[i].ui32Stride,
                         psPictRendInfo->asPlaneInfo[i].ui32Size,
                         psPictRendInfo->asPlaneInfo[i].ui32Offset);

            psPictRendInfo->ui32RenderedSize += psPictRendInfo->asPlaneInfo[i].ui32Size;

            ui32TotalVertSamples += aui32VertSamples[i];

            // Calculate the render region maximum picture size.
            sPictSize.ui32Width = (psPictRendInfo->asPlaneInfo[i].ui32Stride * sPixFmt.ui32BOPDenom) / sPixFmt.aui32BOPNumer[i];
            sPictSize.ui32Height = (aui32VertSamples[i] * sPixFmt.ui32VDenom) / sPixFmt.aui32VNumer[i];
            ui32Result = vdecddutils_UpdateRendPictSize(sPictSize, &psPictRendInfo->sRendPictSize);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }
    }

    if (psPictBufConfig->eTileScheme != VDEC_TS_NONE)
    {
        IMG_UINT32  ui32VertSampAlign = 1;      // vertical alignment in samples.
        IMG_UINT32  ui32RenderRegion;

        // Make sure that the buffer size is made to exactly fit a whole number of tiles.
        // Round the height to 8 or 16 samples (depending upon tile shape).
        if (psPictBufConfig->eTileScheme == VDEC_TS1_512x8)
        {
            ui32VertSampAlign = 8;
        }
        else if (psPictBufConfig->eTileScheme == VDEC_TS0_256x16)
        {
            ui32VertSampAlign = 16;
        }

        ui32TotalVertSamples = VDEC_ALIGN_SIZE(ui32TotalVertSamples, ui32VertSampAlign);
        ui32RenderRegion = psPictBufConfig->aui32Stride[VDEC_PLANE_VIDEO_Y] * ui32TotalVertSamples;

        // Render region occupied by tiles must be larger than sum of all plane sizes.
        IMG_ASSERT(ui32RenderRegion >= psPictRendInfo->ui32RenderedSize);
        psPictRendInfo->ui32RenderedSize = ui32RenderRegion;
    }

    DEBUG_REPORT(REPORT_MODULE_VDECDD,
                 "VDECDDUTILS_ConvertBufferConfig() total required %u (inc. alignment for addressing/tiling) vs. buffer %u",
                 psPictRendInfo->ui32RenderedSize,
                 psPictBufConfig->ui32BufSize);

    // Ensure that the buffer size is large enough to hold the data.
    if (psPictBufConfig->ui32BufSize < psPictRendInfo->ui32RenderedSize)
    {
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,
               "Buffer size [%d bytes] should be at least as large as rendered data (inc. any enforced gap between planes) [%d bytes]",
               psPictBufConfig->ui32BufSize,
               psPictRendInfo->ui32RenderedSize);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    // Whole buffer should be marked as rendered region.
    psPictRendInfo->ui32RenderedSize = psPictBufConfig->ui32BufSize;

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              VDECUTILS_GetDisplayRegion

******************************************************************************/
IMG_RESULT VDECUTILS_GetDisplayRegion(
    const VDEC_sPictSize        * psCodedSize,
    const VDEC_sRect            * psOrigDisplayRegion,
    const VDEC_sStrOutputConfig * psOutputConfig,
    VDEC_sRect                  * psDisplayRegion
)
{
    IMG_RESULT ui32Result = IMG_SUCCESS;

    /* Validate inputs. */
    IMG_ASSERT(psCodedSize);
    IMG_ASSERT(psOrigDisplayRegion);
    IMG_ASSERT(psOutputConfig);
    IMG_ASSERT(psDisplayRegion);
    if(psCodedSize==IMG_NULL || psOrigDisplayRegion==IMG_NULL || psOutputConfig==IMG_NULL || psDisplayRegion==IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    // In the simplest case the display region is the same as that defined in the bitstream.
    *psDisplayRegion = *psOrigDisplayRegion;

    if(psOrigDisplayRegion->ui32Height == 0 ||
        psOrigDisplayRegion->ui32Width == 0 ||
        psCodedSize->ui32Height == 0 ||
        psCodedSize->ui32Width == 0)
    {
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,"Invalid parameters while trying to calculate display region:");
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,"    Display Size: [%d,%d]",
            psOrigDisplayRegion->ui32Width,psOrigDisplayRegion->ui32Height);
        REPORT(REPORT_MODULE_VDECDD, REPORT_ERR,"    Coded Size  : [%d,%d]",
            psCodedSize->ui32Width, psCodedSize->ui32Height);
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    if (psOutputConfig->bScale)
    {
        IMG_ASSERT(psOrigDisplayRegion->ui32LeftOffset == 0 && psOrigDisplayRegion->ui32TopOffset == 0);

        psDisplayRegion->ui32Width = psOutputConfig->sScaledPictSize.ui32Width;
        psDisplayRegion->ui32Height = psOutputConfig->sScaledPictSize.ui32Height;
    }
    else if (psOutputConfig->eRotMode != VDEC_ROTATE_0)
    {
        switch (psOutputConfig->eRotMode)
        {
        case VDEC_ROTATE_90:
            psDisplayRegion->ui32LeftOffset = psCodedSize->ui32Height - (psOrigDisplayRegion->ui32Height + psOrigDisplayRegion->ui32TopOffset);
            psDisplayRegion->ui32TopOffset = psOrigDisplayRegion->ui32LeftOffset;
            psDisplayRegion->ui32Width = psOrigDisplayRegion->ui32Height;
            psDisplayRegion->ui32Height = psOrigDisplayRegion->ui32Width;
            break;

        case VDEC_ROTATE_180:
            psDisplayRegion->ui32LeftOffset = psCodedSize->ui32Width - (psOrigDisplayRegion->ui32Width + psOrigDisplayRegion->ui32LeftOffset);
            psDisplayRegion->ui32TopOffset = psCodedSize->ui32Height - (psOrigDisplayRegion->ui32Height + psOrigDisplayRegion->ui32TopOffset);
            psDisplayRegion->ui32Width = psOrigDisplayRegion->ui32Width;
            psDisplayRegion->ui32Height = psOrigDisplayRegion->ui32Height;
            break;

        case VDEC_ROTATE_270:
            psDisplayRegion->ui32LeftOffset = psOrigDisplayRegion->ui32TopOffset;
            psDisplayRegion->ui32TopOffset = psCodedSize->ui32Width - (psOrigDisplayRegion->ui32Width + psOrigDisplayRegion->ui32LeftOffset);
            psDisplayRegion->ui32Width = psOrigDisplayRegion->ui32Height;
            psDisplayRegion->ui32Height = psOrigDisplayRegion->ui32Width;
            break;

        default:
            IMG_ASSERT(IMG_FALSE);
            ui32Result = IMG_ERROR_NOT_SUPPORTED;
            break;
        }
    }

    return ui32Result;
}
