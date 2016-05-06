/*!
 *****************************************************************************
 *
 * @File       msvdx_int.h
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

#if !defined (__MSVDX_INT_H__)
#define __MSVDX_INT_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_defs.h"
#include "vdecdd_int.h"
#include "scaler_setup.h"
#include "vxd_ext.h"
#include "msvdx_ext.h"
#include "hwctrl_int.h"
#include "vxd_int.h"


/*!
******************************************************************************

 @Function              MSVDXIO_fnTimer

 @Description

 This callback function is used on the expiry of a timer.

 @Input     pvParam : Parameter registered with timer.

 @Return    IMG_BOOL :

******************************************************************************/
extern IMG_BOOL
MSVDXIO_fnTimer(
    IMG_VOID * pvParam
);

/*!
******************************************************************************

 @Function              MSVDX_DeInitialise

******************************************************************************/
extern IMG_RESULT
MSVDX_DeInitialise(
    const IMG_HANDLE  hVxd
);

/*
******************************************************************************

 @Function              MSVDX_GetScalerCoeffCmds

******************************************************************************/
extern IMG_RESULT
MSVDX_GetScalerCoeffCmds(
    const SCALER_sCoeffs  * psScalerCoeffs,
    IMG_UINT32            * pui32PictCmds
);

/*
******************************************************************************

 @Function              MSVDX_GetScalerCmds

******************************************************************************/
extern IMG_RESULT
MSVDX_GetScalerCmds(
    const SCALER_sConfig    * psScalerConfig,
    const SCALER_sPitch     * psPitch,
    const SCALER_sFilter    * psFilter,
    const PIXEL_sPixelInfo  * psOutLoopPixelInfo,
    SCALER_sParams          * psParams,
    IMG_UINT32              * pui32PictCmds
);

/*!
******************************************************************************

 @Function              MSVDX_GetMmuTileConfig

 This function returns the MMU Tile config for the core.

 @Input     eTileScheme         : Tiling scheme.

 @Input     bByteInterleaved : IMG_TRUE if twidling.

 @Output    psMmuTileConfig        : A pointer to strcuture for Tile Config.

 @Return   IMG_RESULT        : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
MSVDX_GetMmuTileConfig(
    VDEC_eTileScheme        eTileScheme,
    IMG_BOOL                bByteInterleaved,
    VDECFW_sMmuTileConfig * psMmuTileConfig
);

/*
******************************************************************************

 @Function              MSVDX_DumpRegisters

 @Description

 Dump the Core state.

 @Input     hMsvdxContext   : A handle to the MSVDX context.

******************************************************************************/
extern IMG_RESULT MSVDX_DumpRegisters(
    const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              MSVDX_GetCoreState

******************************************************************************/
extern IMG_RESULT
MSVDX_GetCoreState(
    const IMG_HANDLE    hVxd,
    VXDIO_sState      * psState
);

/*!
******************************************************************************

 @Function              MSVDX_FlushMmuCache

******************************************************************************/
extern IMG_RESULT
MSVDX_FlushMmuCache(
    const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              MSVDX_HandleInterrupts

******************************************************************************/
extern IMG_RESULT
MSVDX_HandleInterrupts(
    const IMG_HANDLE    hVxd,
    VXD_sIntStatus    * psIntStatus
);

/*!
******************************************************************************

 @Function              MSVDX_HandleInterrupts

 Fills in VXD_sIntStatus

 @note: it's not calling it VDXIO counterpart to do the whole job, but
 accesses 3 registers via VXDIO_ReadRegister instead, which makes it expensive

******************************************************************************/
extern IMG_RESULT
MSVDX_GetIntStatus(
    const IMG_HANDLE    hVxd,
    VXD_sIntStatus    * psIntStatus
);

/*!
******************************************************************************

 @Function              MSVDX_SendFirmwareMessage

******************************************************************************/
extern IMG_RESULT
MSVDX_SendFirmwareMessage(
    const IMG_HANDLE    hVxd,
    VXD_eCommsArea      eArea,
    const IMG_VOID    * psMsgHdr
);

#ifdef STACK_USAGE_TEST
/*!
******************************************************************************

 @Function              MSVDX_GetStackUsage

******************************************************************************/
extern IMG_RESULT
MSVDX_GetStackUsage(
    const IMG_HANDLE    hVxd,
    IMG_UINT32        * paui32StackInfo
);

#endif

/*!
******************************************************************************

 @Function              MSVDX_Initialise

******************************************************************************/
extern IMG_RESULT
MSVDX_Initialise(
    const IMG_HANDLE        hVxd,
    VDECFW_sCoreInitData  * psInitConfig
);

/*!
******************************************************************************

 @Function              MSVDX_PrepareFirmware

******************************************************************************/
extern IMG_RESULT
MSVDX_PrepareFirmware(
    const IMG_HANDLE        hVxd,
    const MSVDXIO_sFw     * psFw,
    const VXDIO_sPtdInfo  * psPtdInfo
);

/*!
******************************************************************************

 @Function              MSVDX_Create

******************************************************************************/
extern IMG_RESULT
MSVDX_Create(
    const VDECDD_sDdDevConfig * psDdDevConfig,
    IMG_UINT32                  ui32CoreNum,
    VXD_sCoreProps            * psCoreProps,
    HWCTRL_sRendec            * psRendec,
    IMG_HANDLE                * phMsvdxContext,
    HWCTRL_sFunctions         * psVxdFuncs
);

/*!
******************************************************************************

 @Function              MSVDX_ReadVLR

******************************************************************************/
extern IMG_RESULT MSVDX_ReadVLR(
    const IMG_HANDLE    hVxd,
    IMG_UINT32          ui32Offset,
    IMG_UINT32        * pui32,
    IMG_UINT32          ui32Words
);

/*!
******************************************************************************

 @Function              MSVDX_WriteVLR

******************************************************************************/
extern IMG_RESULT MSVDX_WriteVLR(
    const IMG_HANDLE    hVxd,
    IMG_UINT32          ui32Offset,
    IMG_UINT32        * pui32,
    IMG_UINT32          ui32Words
);

/*!
******************************************************************************

 @Function              MSVDX_Destroy

******************************************************************************/
IMG_RESULT
MSVDX_Destroy(
    const IMG_HANDLE  hVxd
);

#ifndef IMG_KERNEL_MODULE
/*!
******************************************************************************

 @Function              MSVDX_PDUMPSync

 This syncs pdump contexts

 @Input     hVxd       : Handle to #MSVDX_sContext

******************************************************************************/
extern IMG_RESULT
MSVDX_PDUMPSync(
     const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              MSVDX_PDUMPLock

 This locks pdump contexts

 @Input     hVxd       : Handle to #MSVDX_sContext

******************************************************************************/
extern IMG_RESULT
MSVDX_PDUMPLock(
    const IMG_HANDLE  hVxd
);

/*!
******************************************************************************

 @Function              MSVDX_PDUMPUnLock

 This unlocks pdump contexts

 @Input     hVxd       : Handle to #MSVDX_sContext

******************************************************************************/
extern IMG_RESULT
MSVDX_PDUMPUnLock(
    const IMG_HANDLE  hVxd
);

#endif

#if defined(__cplusplus)
}
#endif

#endif /* __MSVDX_INT_H__ */

