/*!
 *****************************************************************************
 *
 * @File       msvdx_ext.h
 * @Title      Low-level MSVDX interface component
 * @Description    This file contains the interface to communicate with an MSVDX core.
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

#if !defined (__MSVDX_EXT_H__)
#define __MSVDX_EXT_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_include.h"
#include "vdec.h"

#include "vdecfw.h"
#include "vdecfw_bin.h"

#include "mem_io.h"
#include "reg_io2.h"
#include "vxd_buf.h"

/*! Maxmium number of DMA linked list elements:
 *  - max 3 elements of 64kB parts of firmware,
 *  - 1 potential element to fill gap between text and data section,
 *  - 2 elements for MTX enable,
 *  - 1 element to purge DMA state,
 *  - 1 element for storing MTX enable register values.
 *  See msvdxio_DMAMTX() */
#define VDEC_DMAC_LL_BUFS_COUNT 8

#define MSVDX_DEF_WR_MASK -1
#define MSVDX_DEF_WR_PIPE 0

/*!
******************************************************************************
 This structure contains MTX software information.
 @brief  MTX Software Information
******************************************************************************/
typedef struct
{
    IMG_UINT32    ui32TextOrigin;
    IMG_UINT32    ui32TextAddr;
    IMG_UINT32 *  pui32Text;
    IMG_UINT32    ui32TextDmaSize;
    IMG_UINT32    ui32TextBufSize;
    IMG_UINT32    ui32DataOrigin;
    IMG_UINT32    ui32DataAddr;
    IMG_UINT32 *  pui32Data;
    IMG_UINT32    ui32DataSize;
    IMG_UINT32 *  pui32TextReloc;
    IMG_UINT8 *   pui8TextRelocType;
    IMG_UINT32 *  pui32TextRelocFullAddr;
    IMG_UINT32    ui32TextRelocSize;
    IMG_UINT32 *  pui32DataReloc;
    IMG_UINT32    ui32DataRelocSize;

} MSVDXIO_sMTXSwInfo;


typedef struct
{
    VDECFW_sFirmwareBinInfo  sFwBaseBinInfo;                 /*!< Firmware base text, data and relocation sections info.    */
    VDECFW_sFirmwareBinInfo  asFwBinModInfo[VDEC_STD_MAX];   /*!< Firmware module text, data and relocation sections info.  */

    VXDIO_sDdBufInfo         sFwBaseBufInfo;                 /*!< Firmware base text and data buffer info.                  */

    VXDIO_sDdBufInfo         asFwTextBufInfo[VDEC_STD_MAX];  /*!< Firmware modules text buffer info.                        */
    VXDIO_sDdBufInfo         asFwDataBufInfo[VDEC_STD_MAX];  /*!< Firmware modules data buffer info.                        */

    VXDIO_sDdBufInfo         sDmaLLBufInfo;                  /*!< DMA linked list buffer info.                              */

    VXDIO_sDdBufInfo         sPsrModInfo;                    /*!< Parser Module buffer info.                                */

} MSVDXIO_sFw;

/*!
******************************************************************************

 @Function              MSVDXIO_Initialise

 @Description

 Initialises an MSVDXIO context.

 @Input     bFakeMtx        : Flag to indicate whether fake mtx is being used.

 @Input     ui32CoreNum     : Core number.

 @Output    phCoreContext   : A pointer to handle to the MSVDX IO context.

 @Input     hCommonCtx      : A handle to the common video decoder device IO
                              context.

 @Return    IMG_RESULT      : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
MSVDXIO_Initialise(
    IMG_BOOL                    bFakeMtx,
	IMG_BOOL					bPostReq,
	IMG_BOOL					bStackUsageTestReq,
    IMG_UINT32                  ui32CoreNum,
    IMG_HANDLE                * phCoreContext,
    IMG_HANDLE                * hCommonCtx
);


#if defined(__cplusplus)
}
#endif

#endif /* __MSVDXIO_H__ */



