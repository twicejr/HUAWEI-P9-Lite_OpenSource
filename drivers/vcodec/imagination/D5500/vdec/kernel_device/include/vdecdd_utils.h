/*!
 *****************************************************************************
 *
 * @File       vdecdd_utils.h
 * @Title      VDEC Utilities
 * @Description    This file contains the VDEC utitlities compiled into user and kernel mode.
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

#ifndef __VDECDD_UTILS_H__
#define __VDECDD_UTILS_H__

#include "img_defs.h"
#include "img_errors.h"
#include "vdec_api.h"
#include "vdecdd.h"

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
 * Common definitions
******************************************************************************/

#ifdef VDEC_TARGET_CEDARVIEW
#define VDEC_MSVDX_PICTBUF_ALIGNMENT        (4096)  /*!< The picture buffer alignment (in bytes) for MSVDX. */
#else
#define VDEC_MSVDX_PICTBUF_ALIGNMENT        (64)    /*!< The picture buffer alignment (in bytes) for MSVDX. */
#endif
#define VDEC_MSVDX_BUF_ALIGNMENT            (4096)  /*!< The buffer alignment (in bytes) for MSVDX.         */
#define VDEC_MSVDX_EXT_STRIDE_ALIGNMENT     (64)    /*!< The extended stride alignment for MSVDX.           */
#define VDEC_MB_DIMENSION  (16)                     /*!< Macroblock dimension (width and height) in pixels  */

/*!
******************************************************************************
 This macro aligns the given size to the provided alignment.
******************************************************************************/
#define VDEC_ALIGN_SIZE(size, alignment) (((size) + (alignment) - 1) & ~((alignment)-1))


/*!
******************************************************************************
 This macro determines whether stride is compatible with extended strides.
******************************************************************************/
#define VDEC_IS_EXTENDED_STRIDE(sPictBufInfo)                                                               \
(                                                                                                           \
    ((sPictBufInfo.asPlaneInfo[VDEC_PLANE_VIDEO_Y].ui32Stride % VDEC_MSVDX_EXT_STRIDE_ALIGNMENT) == 0) &&    \
    ((sPictBufInfo.asPlaneInfo[VDEC_PLANE_VIDEO_UV].ui32Stride % VDEC_MSVDX_EXT_STRIDE_ALIGNMENT) == 0) &&   \
    ((sPictBufInfo.asPlaneInfo[VDEC_PLANE_VIDEO_V].ui32Stride % VDEC_MSVDX_EXT_STRIDE_ALIGNMENT) == 0)       \
)


/* Macros for size comparison. */
#define VDEC_SIZE_GT(sa, sb) \
    (((sa.ui32Width > sb.ui32Width) && (sa.ui32Height >= sb.ui32Height)) || ((sa.ui32Width >= sb.ui32Width) && (sa.ui32Height > sb.ui32Height)))
#define VDEC_SIZE_LT(sa, sb) \
    (((sa.ui32Width < sb.ui32Width) && (sa.ui32Height <= sb.ui32Height)) || ((sa.ui32Width <= sb.ui32Width) && (sa.ui32Height < sb.ui32Height)))
#define VDEC_SIZE_GE(sa, sb) \
    ((sa.ui32Width >= sb.ui32Width) && (sa.ui32Height >= sb.ui32Height))
#define VDEC_SIZE_LE(sa, sb) \
    ((sa.ui32Width <= sb.ui32Width) && (sa.ui32Height <= sb.ui32Height))
#define VDEC_SIZE_EQ(sa, sb) \
    ((sa.ui32Width == sb.ui32Width) && (sa.ui32Height == sb.ui32Height))
#define VDEC_SIZE_NE(sa, sb) \
    ((sa.ui32Width != sb.ui32Width) || (sa.ui32Height != sb.ui32Height))
#define VDEC_SIZE_NZ(sa) \
    ((sa.ui32Width != 0) && (sa.ui32Height != 0))
#define VDEC_SIZE_EZ(sa) \
    ((sa.ui32Width == 0) && (sa.ui32Height == 0))
/* Macros for setting size. */
#define VDEC_SIZE_SET(sa, w, h) \
{ \
    sa.ui32Width = w; \
    sa.ui32Height = h; \
}
#define VDEC_SIZE_SETW(sa, w) \
{ \
    sa.ui32Width = w; \
}
#define VDEC_SIZE_SETH(sa, h) \
{ \
    sa.ui32Height = h; \
}
#define VDEC_SIZE_ZERO(sa) \
{ \
    sa.ui32Width = 0; \
    sa.ui32Height = 0; \
}

/* Macros for allocating/resetting typed vars. */
#define VDEC_MALLOC(p)  p = IMG_MALLOC(sizeof(*(p)))
#define VDEC_BZERO(p)   IMG_MEMSET(p, 0, sizeof(*(p)))

/* Macro for calculating array size. */
#define VDEC_ARRAY_SIZE(aname) (sizeof(aname)/sizeof(aname[0]))


/*!< MSVDX 256x16 tiling row strides for video buffers. */
extern const IMG_UINT32 aui32Tile256x16RowStride[4];
/*!< MSVDX 512x8 tiling row strides for video buffers. */
extern const IMG_UINT32 aui32Tile512x8RowStride[4];






/*!
******************************************************************************

 @Function              VDECDDUTILS_CreateStrUnit

 @Description

 This function is used to Create a VDECDD stream unit structure,
 if an element pointer is passed.

 @Input    ppsStrUnit : A pointer to pointer to stream unit information.

 @Input    sBSList    : Bitstream segment data list.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDDUTILS_CreateStrUnit(
    VDECDD_sStrUnit    ** ppsStrUnit,
    LST_T               * sBSList
);


/*!
******************************************************************************

 @Function              VDECDDUTILS_CreateStrUnitOld

 @Description           this function allocate a structure for a complete data unit


******************************************************************************/
extern IMG_RESULT VDECDDUTILS_CreateStrUnitOld(
    VDECDD_sStrUnit    ** ppsStrUnit,
    BSPP_sSequHdrInfo   * psSeqInfo,
    BSPP_sPictHdrInfo   * psPicInfo,
    LST_T               * sBSList
);


/*!
******************************************************************************

 @Function              VDECDDUTILS_FreeStrUnit

 @Description

 This function is used to free a VDECDD stream unit structure.

 @Input    psStrUnit : A pointer to stream unit information.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDDUTILS_FreeStrUnit(
    VDECDD_sStrUnit  * psStrUnit
);


/*!
******************************************************************************

 @Function              VDECDDUTILS_RefPictGetMaxNum

 @Description

 This function is used to calculate the maximum number of reference pictures
 required per video standard.

 @Input    psStrConfigData  : A pointer to stream configuration information.

 @Input    psComSequHdrInfo : A pointer to common VSH information.

 @Output   pui32NumPicts    : A pointer used to return the maximum number
                              of reference pictures required.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDDUTILS_RefPictGetMaxNum(
    const VDEC_sStrConfigData   * psStrConfigData,
    const VDEC_sComSequHdrInfo  * psComSequHdrInfo,
    IMG_UINT32                  * pui32NumPicts
);


/*!
******************************************************************************

 @Function              VDECDDUTILS_OooPictGetMaxNum

 @Description

 This function is used to calculate the maximum number of out-of-(display)-order
 pictures required per video standard.

 @Input    psStrConfigData  : A pointer to stream configuration information.

 @Input    psComSequHdrInfo : A pointer to common VSH information.

 @Output   pui32NumPicts    : A pointer used to return the maximum number
                              of out-of-(display)-order pictures required.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDDUTILS_OooPictGetMaxNum(
    const VDEC_sStrConfigData   * psStrConfigData,
    const VDEC_sComSequHdrInfo  * psComSequHdrInfo,
    IMG_UINT32                  * pui32NumPicts
);

/*!
******************************************************************************

 @Function              VDECDDUTILS_IsSecondaryOutputRequired

 @Description

 This function is used to check if the secondary output is required (if we have
 it we may use it for transformation (e.g. scaling. rotating or up/down-sampling)
 or not.

 @Input    psComSequHdrInfo : A pointer to common VSH information.

 @Input    psOutputConfig   : A pointer to output configuration information.

 @Output   None

 @Return   IMG_BOOL         : Returns IMG_TRUE if the secondary output is required, 
                              IMG_FALSE otherwise.

 ******************************************************************************/
IMG_BOOL
VDECDDUTILS_IsSecondaryOutputRequired(
    const VDEC_sComSequHdrInfo    * psComSequHdrInfo,
    const VDEC_sStrOutputConfig   * psOutputConfig
);

/*!
******************************************************************************

 @Function              VDECDDUTILS_GetMinRequiredNumPicts

 @Description

 This function is used to calculate the minimum number of picture buffers required.

 @Input    psStrConfigData  : A pointer to stream configuration information.

 @Input    psComSequHdrInfo : A pointer to common VSH information.

 @Input    psOutputConfig   : A pointer to output configuration information.

 @Output   pui32NumPicts    : A pointer used to return the maximum number
                              of out-of-(display)-order pictures required.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

 ******************************************************************************/
extern IMG_RESULT
VDECDDUTILS_GetMinRequiredNumPicts(
    const VDEC_sStrConfigData    * psStrConfigData,
    const VDEC_sComSequHdrInfo   * psComSequHdrInfo,
    const VDEC_sStrOutputConfig  * psOutputConfig,
    IMG_UINT32                   * pui32NumPicts
);


/*
******************************************************************************

 @Function              VDECDDUTILS_GetStrideCode

 @Description

 Obtains the hardware defined video profile.

 @Input     eVidStd       : Width of the reference picture

 @Input     ui32RowStride : Row stride in bytes

 @Return    IMG_UINT32 : Row stride code as used by hardware.

******************************************************************************/
extern IMG_UINT32 VDECDDUTILS_GetStrideCode(
    VDEC_eVidStd  eVidStd,
    IMG_UINT32    ui32RowStride
);


/*!
******************************************************************************

 @Function              VDECDDUTILS_BufMsvdxAdjustSize

 @Description

 This function is used to adjust buffer size for MSVDX needs.

 @Input    pui32BufSize : A pointer to buffer size to be adjusted.

 @Output   pui32BufSize : A pointer used to return the adjusted buffer size.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
IMG_VOID VDECDDUTILS_BufMsvdxAdjustSize(
    IMG_UINT32  * pui32BufSize
);


/*!
******************************************************************************

 @Function              VDECDDUTILS_IsPacked

 @Description

 This function determines whether the picture render region is packed.

 @Input   psPictRendInfo  : A pointer used to return the picture render
                            information.

 @Return   IMG_BOOL : If IMG_TRUE, the picture render region is packed.
                      IMG_FALSE otherwise.

******************************************************************************/
extern IMG_BOOL VDECDDUTILS_IsPacked(
    const VDEC_sPictRendInfo  * psPictRendInfo
);


/*!
******************************************************************************

 @Function              VDECDDUTILS_PrintBufferProperties

 @Description

 This function is used to print the buffer information.

 @Input    psOutputConfig  : A pointer to stream output configuration data.

 @Input    psPictBufInfo   : A pointer to the rendered region data.

 @Input    psPictBufConfig : A pointer to the buffer configuration data.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDDUTILS_PrintBufferProperties(
    const VDEC_sStrOutputConfig  * psOutputConfig,
    const VDEC_sPictRendInfo     * psPictBufInfo,
    const VDEC_sPictBufConfig    * psPictBufConfig
);


/*!
******************************************************************************

 @Function              VDECDDUTILS_PictBufGetConfig

 @Description

 This function is used to get the buffer information based on the stream
 and output configuration.

 @Input    psStrConfigData   : A pointer to stream configuration information.

 @Input    psPictRendConfig  : A pointer to buffer allocation information.

 @Input    bAllocRotation    : If set to IMG_TRUE, it is assumed that rotation
                               will be required somewhere in the bitstream.
                               The allocated buffer size takes this possibility
                               into account to avoid re-allocation.

 @Input    psStrOutputConfig : A pointer to output configuration information.

 @Output   psPictBufConfig   : A pointer used to return the picture buffer
                               information.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDDUTILS_PictBufGetConfig(
    const VDEC_sStrConfigData     * psStrConfigData,
    const VDEC_sPictRendConfig    * psPictRendConfig,
    IMG_BOOL                        bAllocRotation,
    const VDEC_sStrOutputConfig   * psStrOutputConfig,
    VDEC_sPictBufConfig           * psPictBufConfig
);


/*!
******************************************************************************

 @Function              VDECDDUTILS_PictBufGetInfo

 @Description

 This function is used to get the buffer information based on the stream
 and output configuration.

 @Input    psStrConfigData   : A pointer to stream configuration information.

 @Input    psPictRendConfig  : A pointer to rendered region configuration.

 @Input    psStrOutputConfig : A pointer to output configuration information.

 @Output   psPictRendInfo    : A pointer used to return the internal picture
                               buffer information.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDDUTILS_PictBufGetInfo(
    const VDEC_sStrConfigData    * psStrConfigData,
    const VDEC_sPictRendConfig   * psPictRendConfig,
    const VDEC_sStrOutputConfig  * psStrOutputConfig,
    VDEC_sPictRendInfo           * psPictRendInfo
);


/*!
******************************************************************************

 @Function              VDECDDUTILS_ConvertBufferConfig

 @Description

 This function is used to convert the buffer information into the rendered region
 of this picture buffer.

 @Input    psStrConfigData  : A pointer to the stream configuration data.

 @Input    psPictBufConfig  : A pointer to the picture buffer configuration data.

 @Input    psComSequHdrInfo : A pointer to the common sequence header data.

 @Output   psPictRendInfo   : A pointer used to return the rendered region information.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDDUTILS_ConvertBufferConfig(
    const VDEC_sStrConfigData   * psStrConfigData,
    const VDEC_sPictBufConfig   * psPictBufConfig,
    const VDEC_sComSequHdrInfo  * psComSequHdrInfo,
    VDEC_sPictRendInfo          * psPictRendInfo
);


/*!
******************************************************************************

 @Function              VDECUTILS_GetDisplayRegion

 @Description

 This function is used to get the display region of frame.

 @Input    psCodedSize         : A pointer to the coded picture size.

 @Input    psOrigDisplayRegion : A pointer to the original display information.

 @Input    psOutputConfig      : A pointer to the output configuration information.

 @Output   psDisplayRegion     : A pointer used to return the display region information.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECUTILS_GetDisplayRegion(
    const VDEC_sPictSize         * psCodedSize,
    const VDEC_sRect             * psOrigDisplayRegion,
    const VDEC_sStrOutputConfig  * psOutputConfig,
    VDEC_sRect                   * psDisplayRegion
);


#ifdef __cplusplus
}
#endif

#endif /* __VDECDD_UTILS_H__   */


