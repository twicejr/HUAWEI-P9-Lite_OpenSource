/*!
 *****************************************************************************
 *
 * @File       pvdec_int.h
 * @Title      Low-level PVDEC interface component
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

#if !defined (__PVDECINT_H__)
#define __PVDECINT_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_defs.h"
#include "vxd_ext.h"
#include "hwctrl_int.h"
#include "vxd.h"

/* How many VLC IDX addresses fits in single address register */
#define PVDECIO_VLC_IDX_ADDR_PARTS 2
/* Mask for VLC IDX address field. We're taking [0][0] here, as it corresponds to unshifted mask */
#define PVDECIO_VLC_IDX_ADDR_MASK MSVDX_VEC_CR_VEC_VLC_TABLE_ADDR0_VLC_TABLE_ADDR0_MASK
/* Length (shift) of VLC IDX address field. We're taking [0][1] here, as it corresponds to shift of one element */
#define PVDECIO_VLC_IDX_ADDR_SHIFT MSVDX_VEC_CR_VEC_VLC_TABLE_ADDR0_VLC_TABLE_ADDR1_SHIFT

/* How many VLC IDX initial fits in single width register */
#define PVDECIO_VLC_IDX_WIDTH_PARTS 10
/* Mask for VLC IDX width field. We're taking [0][0] here, as it corresponds to unshifted mask */
#define PVDECIO_VLC_IDX_WIDTH_MASK MSVDX_VEC_CR_VEC_VLC_TABLE_INITIAL_WIDTH0_VLC_TABLE_INITIAL_WIDTH0_MASK
/* Length (shift) of VLC IDX width field. We're taking [0][1] here, as it corresponds to shift of one element */
#define PVDECIO_VLC_IDX_WIDTH_SHIFT MSVDX_VEC_CR_VEC_VLC_TABLE_INITIAL_WIDTH0_VLC_TABLE_INITIAL_WIDTH1_SHIFT

/* How many VLC IDX initial opcodes fits in single opcode register */
#define PVDECIO_VLC_IDX_OPCODE_PARTS 16
/* Mask for VLC IDX opcode field. We're taking [0][0] here, as it corresponds to unshifted mask */
#define PVDECIO_VLC_IDX_OPCODE_MASK MSVDX_VEC_CR_VEC_VLC_TABLE_INITIAL_OPCODE0_VLC_TABLE_INITIAL_OPCODE0_MASK
/* Length (shift) of VLC IDX opcode field. We're taking [0][1] here, as it corresponds to shift of one element */
#define PVDECIO_VLC_IDX_OPCODE_SHIFT MSVDX_VEC_CR_VEC_VLC_TABLE_INITIAL_OPCODE0_VLC_TABLE_INITIAL_OPCODE1_SHIFT

#define PVDECIO_VLC_IDX_ADDR_ID 2
#define PVDECIO_VLC_IDX_WIDTH_ID 1
#define PVDECIO_VLC_IDX_OPCODE_ID 0

#define CTRL_ALLOC_MAX_SEGMENT_SIZE 1024 /* This comes from DEVA PVDEC FW */


/*!
******************************************************************************

 @Function              PVDEC_Create

******************************************************************************/
extern IMG_RESULT
PVDEC_Create(
    const VDECDD_sDdDevConfig * psDdDevConfig,
    IMG_UINT32                  ui32CoreNum,
    VXD_sCoreProps            * psCoreProps,
    HWCTRL_sRendec            * psRendec,
    IMG_HANDLE                * phPvdecContext,
    HWCTRL_sFunctions         * psVxdFuncs
);

/*!
******************************************************************************

 @Function              PVDEC_Destroy

******************************************************************************/
IMG_RESULT PVDEC_Destroy(
    const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              PVDEC_Initialise

******************************************************************************/
extern IMG_RESULT
PVDEC_Initialise(
    const IMG_HANDLE        hVxd,
    VDECFW_sCoreInitData  * psInitConfig
);

/*!
******************************************************************************

 @Function              PVDEC_DeInitialise

******************************************************************************/
extern IMG_RESULT
PVDEC_DeInitialise(
    const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              PVDEC_SendFirmwareMessage

******************************************************************************/
extern IMG_RESULT
PVDEC_SendFirmwareMessage(
    const IMG_HANDLE    hVxd,
    VXD_eCommsArea      eArea,
    const IMG_VOID    * psMsgHdr
);

/*!
******************************************************************************

 @Function              PVDEC_GetCoreState

******************************************************************************/
extern IMG_RESULT
PVDEC_GetCoreState(
    IMG_HANDLE      hVxd,
    VXDIO_sState  * psState
);

/*!
******************************************************************************

 @Function              PVDEC_HandleInterrupts

******************************************************************************/
extern IMG_RESULT
PVDEC_HandleInterrupts(
    const IMG_HANDLE    hVxd,
    VXD_sIntStatus    * psIntStatus
);

/*!
******************************************************************************

 @Function              PVDEC_GetIntStatus

******************************************************************************/
extern IMG_RESULT
PVDEC_GetIntStatus(
    const IMG_HANDLE    hVxd,
    VXD_sIntStatus    * psIntStatus
);

/*!
******************************************************************************

 @Function              PVDEC_FlushMmuCache

******************************************************************************/
extern IMG_RESULT
PVDEC_FlushMmuCache(
    const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              PVDEC_DisableCoreInterrupts

******************************************************************************/
IMG_RESULT PVDEC_DisableCoreInterrupts(
    const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              PVDEC_GetMemSpaceOffset

******************************************************************************/
extern IMG_RESULT
PVDEC_GetMemSpaceOffset(
    const IMG_HANDLE    hVxd,
    IMG_UINT16          ui16MemRegion,
    IMG_UINT64        * pui64MemSpaceOffset
);

/*!
******************************************************************************

 @Function              PVDEC_PrepareFirmware

******************************************************************************/
extern IMG_RESULT
PVDEC_PrepareFirmware(
    const IMG_HANDLE        hVxd,
    const MSVDXIO_sFw     * psFw,
    const VXDIO_sPtdInfo  * psPtdInfo
);

/*!
******************************************************************************

 @Function              PVDEC_GetRegsOffsets

******************************************************************************/
extern IMG_RESULT
PVDEC_GetRegsOffsets(
    const IMG_HANDLE        hVxd,
    DECODER_sRegsOffsets  * psRegsOffsets
);

/*!
******************************************************************************

 @Function              PVDEC_GetTiledHeaps

******************************************************************************/
extern IMG_RESULT
PVDEC_GetTiledHeaps(
VDEC_eTileScheme        eTileScheme,
IMG_UINT32            * pui32NumHeaps,
MMU_sHeapTilingInfo   * pasTilingInfo
);

#if defined(__cplusplus)
}
#endif

#endif /* __PVDECINT_H__ */
