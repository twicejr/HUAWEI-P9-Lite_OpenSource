/*!
 *****************************************************************************
 *
 * @File       pvdec_io.h
 * @Title      Low-level PVDEC interface component
 * @Description    This file contains the interface to communicate with an PVDEC core.
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

#if !defined (__PVDECIO_H__)
#define __PVDECIO_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "vxd_ext.h"

/*!
******************************************************************************

 @Function              PVDECIO_GetCoreState

 @Description

 Obtain the PVDEC core state.

 @Input     hCoreContext    : Handle to PVDEC IO context.

 @Output    psState         : Pointer to state information.

 @Return    IMG_RESULT      : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
PVDECIO_GetCoreState(
    const IMG_HANDLE    hCoreContext,
    VXDIO_sState      * psState
);


/*
******************************************************************************

 @Function              PVDECIO_EnableCoreClocks

 @Description

 This function enables PVDEC core clocks.

 @Input     hCoreContext     : A handle to the PVDEC IO context.

******************************************************************************/
extern IMG_VOID
PVDECIO_EnableCoreClocks(IMG_HANDLE hCoreContext);

/*
******************************************************************************

 @Function              PVDECIO_EnableCoreAndProcClocks

 @Description

 This function enables PVDEC core and processor clocks.

 @Input     hCoreContext     : A handle to the PVDEC IO context.

 @Return    IMG_RESULT       : This function returns either IMG_SUCCESS or an
                               error code.

******************************************************************************/
extern IMG_RESULT
PVDECIO_EnableCoreAndProcClocks(
    const IMG_HANDLE    hCoreContext,
    IMG_BOOL            bAutoClockGatingSupport,
    IMG_BOOL            bExtClockGating,
    IMG_BOOL            bForceManual
);

/*
******************************************************************************

 @Function              PVDECIO_GetMemSpaces

 @Description

 This function obtains PVDEC memory spaces handles.

 @Input     ui32CoreNum      : Core number.

 @Output    pahMemSpace      : Buffer where memory space handles will be
                               written.

 @Return    IMG_RESULT       : This function returns either IMG_SUCCESS or an
                               error code.

******************************************************************************/
extern IMG_RESULT
PVDECIO_GetMemSpaces(
    IMG_UINT32          ui32CoreNum,
    IMG_HANDLE        * pahMemSpace
);

/*
******************************************************************************

 @Function              PVDECIO_Initialise

 @Description

 This function initialises an PVDECIO context.

 @Input     bFakeMtx         : Flag to indicate whether fake mtx is being used.

 @Input     ui32CoreNum      : Core number.

 @Input     hCommonCtx       : A handle to the VXDIO context.

 @Output    phCoreContext    : Pointer used to return handle to new
                               PVDEC IO context.

 @Return    IMG_RESULT       : This function returns either IMG_SUCCESS or an
                               error code.

******************************************************************************/
extern IMG_RESULT
PVDECIO_Initialise(
    IMG_BOOL            bFakeMtx,
    IMG_UINT32          ui32CoreNum,
    IMG_HANDLE        * hCommonCtx,
    IMG_HANDLE        * phCoreContext
);

/*
******************************************************************************

 @Function              PVDECIO_DeInitialise

 @Description

 This function deinitialises an PVDECIO context.

 @Input     ui32CoreNum      : Core number.

 @Input     hCoreContext     : A handle to the PVDEC IO context.

 @Return    IMG_RESULT       : This function returns either IMG_SUCCESS or an
                               error code.

******************************************************************************/
extern IMG_RESULT
PVDECIO_DeInitialise(IMG_UINT32   ui32CoreNum,
                     IMG_HANDLE   hCoreContext
);


/*!
******************************************************************************

 @Function              PVDECIO_PvdecReset

 @Description

 Resets PVDEC core.

 @Input     hCoreContext     : A handle to the PVDEC IO context.

******************************************************************************/
extern IMG_RESULT
PVDECIO_PvdecReset(
    IMG_HANDLE          hCoreContext
);


/*!
******************************************************************************

 @Function              PVDECIO_SendFirmwareMessage

 @Description

 Send message to firmware.

 @Input     hCoreContext     : A handle to the PVDEC IO context.

 @Input     eArea            : Communication area to use.

 @Input     psMsgHdr         : Pointer to buffer with message in DEVA format.


******************************************************************************/
extern IMG_RESULT
PVDECIO_SendFirmwareMessage(
    const IMG_HANDLE           hCoreContext,
    VXD_eCommsArea             eArea,
    const IMG_VOID           * psMsgHdr
);

/*!
******************************************************************************

 @Function              PVDECIO_LoadBaseFirmware

 @Description

 Loads base firmware component to MTX.

 @Input     hCoreContext     : A handle to the PVDEC IO context.

******************************************************************************/
extern IMG_RESULT
PVDECIO_LoadBaseFirmware(
    const IMG_HANDLE        hCoreContext
);


/*!
******************************************************************************

 @Function              PVDECIO_HandleInterrupts

******************************************************************************/
IMG_RESULT
PVDECIO_HandleInterrupts(
    const IMG_HANDLE    hCoreContext,
    VXD_sIntStatus    * psIntStatus
);

/*!
******************************************************************************

 @Function              PVDECIO_FlushMmuCache

 @Description

 Flushes PVDEC MMU cache.

 @Input     hCoreContext     : A handle to the PVDEC IO context.


******************************************************************************/
IMG_RESULT
PVDECIO_FlushMmuCache(
    const IMG_HANDLE    hCoreContext
);

/*!
******************************************************************************

 @Function              PVDECIO_PrepareFirmware

******************************************************************************/
IMG_RESULT
PVDECIO_PrepareFirmware(
    const IMG_HANDLE            hCoreContext,
    const IMG_HANDLE            hFirmware
);

/*
******************************************************************************

 @Function              PVDECIO_KickMTX

 @Description

 Triggers MTX interrupt.

 @Input     hCoreContext     : A handle to the PVDEC IO context.

******************************************************************************/
IMG_VOID
PVDECIO_KickMTX(
    const IMG_HANDLE   * hCoreContext
);

#if !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG)
/*
******************************************************************************

 @Function              PVDECIO_HandleDebugFifo

 @Description

 Handles PVDEC debug fifo with logs from firmware.

 @Input     hCoreContext     : A handle to the PVDEC IO context.

******************************************************************************/
IMG_VOID
PVDECIO_HandleDebugFifo(
    const IMG_HANDLE   * hCoreContext
);

/*
******************************************************************************

 @Function              PVDECIO_EnableDebugFifo

 @Description

 Enables PVDEC debug fifo.

 @Input     hCoreContext     : A handle to the PVDEC IO context.

******************************************************************************/
IMG_VOID
PVDECIO_EnableDebugFifo(
    const IMG_HANDLE   * hCoreContext
);

/*
******************************************************************************

 @Function              PVDECIO_DisableDebugFifo

 @Description

 Disables PVDEC debug fifo.

 @Input     hCoreContext     : A handle to the PVDEC IO context.

******************************************************************************/
IMG_VOID
PVDECIO_DisableDebugFifo(
    const IMG_HANDLE   * hCoreContext
);

/*
******************************************************************************

 @Function              PVDECIO_GetDebugFifoSize

 @Description

 Returns PVDEC debug fifo size.

 @Input     hCoreContext     : A handle to the PVDEC IO context.

******************************************************************************/
IMG_UINT32
PVDECIO_GetDebugFifoSize(
    const IMG_HANDLE   * hCoreContext
);

#endif /* !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG) */

#if defined(__cplusplus)
}
#endif

#endif /* __PVDECIO_H__ */



