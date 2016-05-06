/*!
 *****************************************************************************
 *
 * @File       vxd_io.h
 * @Title      Low-level video device interface component
 * @Description    This file contains the interface to communicate with a video device.
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

#if !defined (__VXDIO_H__)
#define __VXDIO_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include "img_include.h"
#include "vdec.h"

#include "secure_defs.h"

#include "vdecfw.h"
#include "vdecfw_bin.h"
#include "msvdx_ext.h"
#include "vxd_ext.h"
#include "vxd_buf.h"

#include "mem_io.h"
#include "reg_io2.h"


#define VXDIO_MEMSPACE_PREFIX_MAX     4
#define VXDIO_MEMSPACE_NAME_MAX       60

/*!
******************************************************************************

 @Function              VXDIO_ReadRegister

 @Description

 Read value from register.

 @Input     hVxdCtx         : Handle to video device IO context.

 @Input     ui32MemRegion   : Memory region of register.

 @Input     ui32Offset      : Register offset within register/memory space.

 @Input     ui8Pipe         : Id of pipe, only meaningful for some cores.

 @Return    IMG_RESULT      : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_UINT32
VXDIO_ReadRegister(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset,
    IMG_UINT8           ui8Pipe
);


/*!
******************************************************************************

 @Function              VXDIO_WriteRegister

 @Description

 Write value to register.

 @Input     hVxdCtx         : Handle to video device IO context.

 @Input     ui32MemRegion   : Memory region of register.

 @Input     ui32Offset      : Register offset within register/memory space.

 @Input     ui32Value       : Value to write to register.

 @Input     ui32Mask        : Mask of bits to modify to register.

 @Input     ui8Pipe         : Id of pipe, only meaningful for some cores.

 @Return    IMG_RESULT      : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXDIO_WriteRegister(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset,
    IMG_UINT32          ui32Value,
    IMG_UINT32          ui32Mask,
    IMG_UINT8           ui8Pipe
);


/*!
******************************************************************************

 @Function              VXDIO_VLRWriteWords

 @Description

 This function writes an array of words to VEC local RAM (VLR).

 @Input     hVxdCtx          : Handle to video device IO context.

 @Input     ui32MemRegion    : VLR memory space.

 @Input     ui32Addr         : Address (byte) in VLR.

 @Input     ui32NumWords     : Number of 32-bits words to write.

 @Input     pui32Values      : Array of words to write.

 @Return    IMG_RESULT       : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXDIO_VLRWriteWords(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Addr,
    IMG_UINT32          ui32NumWords,
    const IMG_UINT32  * pui32Values
);


/*!
******************************************************************************

 @Function              VXDIO_VLRReadWords

 @Description

 This function reads an array of words from VEC local RAM (VLR).

 @Input     hVxdCtx          : Handle to video device IO context.

 @Input     ui32MemRegion    : VLR memory space.

 @Input     ui32Addr         : Address (byte) in VLR.

 @Input     ui32NumWords     : Number of 32-bits words to read.

 @Input     pui32Values      : Array of words to read.

 @Input     bValidate        : POL values read from VLR

 @Return    IMG_RESULT       : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXDIO_VLRReadWords(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Addr,
    IMG_UINT32          ui32NumWords,
    IMG_UINT32        * pui32Values,
    IMG_BOOL            bValidate
);


/*!
******************************************************************************

 @Function              VXDIO_Poll

 @Description

 Poll for a specific register value.

 @Input     hVxdCtx         : Handle to video device IO context.

 @Input     ui32MemRegion   : Memory region of register.

 @Input     ui32Offset      : Register offset within register/memory space.

 @Input     ui32RequValue   : Required register value.

 @Input     ui32Enable      : Mask of live bits to apply to register.

 @Input     VXDIO_ePollMode : Check function to be used (equals, !equals ect)

 @Return    IMG_RESULT      : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXDIO_Poll(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset,
    IMG_UINT32          ui32RequValue,
    IMG_UINT32          ui32Enable,
    VXDIO_ePollMode     ePollMode
);

#if !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING)
/*!
******************************************************************************

 @Function              VXDIO_PDUMPVerifPoll

 @Description

 Poll only for pdump purposes (to force the pdump script to verify this value.

 @Input     hVxdCtx         : Handle to video device IO context.

 @Input     ui32MemRegion   : Memory region of register.

 @Input     ui32Offset      : Register offset within register/memory space.

 @Input     ui32RequValue   : Required register value.

 @Input     ui32Enable      : Mask of live bits to apply to register.

******************************************************************************/
extern IMG_RESULT
VXDIO_PDUMPVerifPoll(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset,
    IMG_UINT32          ui32RequValue,
    IMG_UINT32          ui32Enable
);

/*!
******************************************************************************

 @Function              VXDIO_PDUMPComment

 @Description

 Insert a comment in the pdump script

 @Input     hVxdCtx         : Handle to video device IO context.

 @Input     ui32MemRegion   : Memory region of register.

 @Input     pszComment      : Comment

******************************************************************************/
extern IMG_RESULT
VXDIO_PDUMPComment(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    const IMG_CHAR *    pszComment
);

/*!
******************************************************************************

 @Function              VXDIO_PDUMPSync

 @Description

 Sync pdump contexts

 @Input     hVxdCtx         : Handle to video device IO context.

******************************************************************************/
IMG_RESULT
VXDIO_PDUMPSync(
    const IMG_HANDLE    hVxdCtx
);

/*!
******************************************************************************

 @Function              VXDIO_PDUMPLock

 @Description

 Lock pdump contexts

 @Input     hVxdCtx         : Handle to video device IO context.

******************************************************************************/
extern IMG_RESULT
VXDIO_PDUMPLock(
    const IMG_HANDLE    hVxdCtx
);

/*!
******************************************************************************

 @Function              VXDIO_PDUMPUnLock

 @Description

 Unlock pdump contexts

 @Input     hVxdCtx         : Handle to video device IO context.

******************************************************************************/
extern IMG_RESULT
VXDIO_PDUMPUnLock(
    const IMG_HANDLE    hVxdCtx
);

/*!
******************************************************************************

 @Function              VXDIO_PDUMPPollCircBuff

 @Description

 Poll only for pdump purposes (to force the pdump script to verify this value.

 @Input     hVxdCtx              : Handle to video device IO context.

 @Input     ui32MemRegion        : Memory region of register.

 @Input     ui32Offset           : Register offset within register/memory space.

 @Input     ui32WriteOffsetVal   : Required register value.

 @Input     ui32PacketSize       : Required register value.

 @Input     ui32BufferSize       : Required register value.

******************************************************************************/
IMG_RESULT
VXDIO_PDUMPPollCircBuff(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset,
    IMG_UINT32          ui32WriteOffsetVal,
    IMG_UINT32          ui32PacketSize,
    IMG_UINT32          ui32BufferSize
);

/*!
******************************************************************************

 @Function              VXDIO_PDUMPDisableCmds

 @Description

 Disable the capture of specified PDUMP commands for a specific register.

 @Input     hVxdCtx          : Handle to video device IO context.

 @Input     ui32MemRegion    : Memory region of register.

 @Input     ui32Offset       : Register offset within register/memory space.

 @Input     ui32DisableFlags : PDUMP commands disable flags.

 @Return    IMG_RESULT       : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_UINT32
VXDIO_PDUMPDisableCmds(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset,
    IMG_UINT32          ui32DisableFlags
);

/*!
******************************************************************************

 @Function              VXDIO_PDUMPGetDisableCmds

 @Description

 Get PDUMP commands disable flags for a specific register.

 @Input     hVxdCtx          : Handle to video device IO context.

 @Input     ui32MemRegion    : Memory region of register.

 @Input     ui32Offset       : Register offset within register/memory space.

 @Return    IMG_RESULT       : Returns PDUMP disable flags for ui32Offset.

******************************************************************************/
extern IMG_UINT32
VXDIO_PDUMPGetDisableCmds(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32          ui32MemRegion,
    IMG_UINT32          ui32Offset
);

#endif /* !defined(SECURE_MEDIA_SUPPORT) && !defined(VXD_BRIDGING) */

/*!
******************************************************************************

 @Function              VXDIO_GetCoreState

 Obtain the video decoder device core state.

 @Input     hVxdCtx         : Handle to video device IO context.

 @Output    psState         : Pointer to state information.

 @Return    IMG_RESULT      : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
IMG_RESULT
VXDIO_GetCoreState(
    const IMG_HANDLE    hVxdCtx,
    VXDIO_sState      * psState
);


/*!
******************************************************************************

 @Function              VXDIO_HandleInterrupts

 @Description

 Handle any pending video decoder device interrupts and clear.

 @Input     hVxdCtx         : Handle to video device IO context.

 @Output    psIntStatus     : Pointer to interrupt status information.

 @Return    IMG_RESULT      : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_UINT32
VXDIO_HandleInterrupts(
    const IMG_HANDLE      hVxdCtx,
    VXD_sIntStatus      * psIntStatus
);


/*!
******************************************************************************

 @Function              VXDIO_SendFirmwareMessage

 @Description

 Send a message to firmware.

 @Input     hVxdCtx         : Handle to video device IO context.

 @Input     eArea           : Comms area into which the message should be written.

 @Input     psMsgHdr        : Pointer to message to send.

 @Return    IMG_RESULT      : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXDIO_SendFirmwareMessage(
    const IMG_HANDLE         hVxdCtx,
    VXD_eCommsArea           eArea,
    const IMG_VOID         * psMsgHdr
);


/*!
******************************************************************************

 @Function              VXDIO_LoadBaseFirmware

 @Description

 Load the firmware base component into embedded processor RAM.

 @Input     hVxdCtx         : Handle to video device IO context.

 @Return    IMG_RESULT      : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXDIO_LoadBaseFirmware(
    const IMG_HANDLE      hVxdCtx
);


/*!
******************************************************************************

 @Function              VXDIO_PrepareFirmware

 @Description

 Prepares the firmware for loading to embedded processor.

 @Input     hVxdCtx         : Handle to video device IO context.

 @Input     hFirmware       : Handle to structure containing core specific
                              firmware layout information.

 @Return    IMG_RESULT      : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXDIO_PrepareFirmware(
    const IMG_HANDLE     hVxdCtx,
    const IMG_HANDLE     hFirmware
);


/*!
******************************************************************************

 @Function              VXDIO_DisableClocks

 @Description

 Disables video decoder device clocks.

 @Input     hVxdCtx         : Handle to video device IO context.

 @Return    IMG_RESULT      : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXDIO_DisableClocks(
    const IMG_HANDLE    hVxdCtx
);


#ifdef STACK_USAGE_TEST
/*!
******************************************************************************

 @Function              VXDIO_GetStackUsage

 @Description

 Get stack usage info

 @Input     hVxdCtx                : Handle to video device IO context.

 @Input     * paui32StackInfoArray : Handle to stack info array

 @Return    IMG_RESULT             : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXDIO_GetStackUsage(
    const IMG_HANDLE    hVxdCtx,
    IMG_UINT32        * paui32StackInfoArray
);
#endif


/*!
******************************************************************************

 @Function              VXDIO_EnableClocks

 @Description

 Enables video decoder device clocks.

 @Input     hVxdCtx                 : Handle to video device IO context.

 @Input     bAutoClockGatingSupport : Auto clock-gating is supported by the core.

 @Input     bExtClockGating         : Extended clock-gating register are present on core.

 @Input     bForceManual            : Force manual clock-gating.

 @Return    IMG_RESULT              : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXDIO_EnableClocks(
    const IMG_HANDLE    hVxdCtx,
    IMG_BOOL            bAutoClockGatingSupport,
    IMG_BOOL            bExtClockGating,
    IMG_BOOL            bForceManual
);

/*!
******************************************************************************

 @Function              VXDIO_Initialise

 @Description

 Initialises an VXDIO context.

 @Input     bFakeMtx        : Flag to indicate whether fake mtx is being used.

 @Input     ui32CoreNum     : Core number.

 @Output    phVxdCtx        : A pointer to handle to the video decoder context.

 @Return    IMG_RESULT      : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXDIO_Initialise(
    IMG_BOOL                    bFakeMtx,
    IMG_BOOL                    bPost,
    IMG_BOOL                    bStackUsageTest,
    IMG_UINT32                  ui32CoreNum,
    IMG_HANDLE                * phVxdCtx
);
/*
******************************************************************************

 @Function              VXDIO_DeInitialise

 @Input     ui32CoreNum     : Core number.

 @Input     hVxdCtx         : A handle to the video decoder context.

 @Return    IMG_RESULT      : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
IMG_RESULT
VXDIO_DeInitialise(
    IMG_UINT32          ui32CoreNum,
    IMG_HANDLE          hVxdCtx
);

/*
******************************************************************************

 @Function              msvdxio_GetHandle

******************************************************************************/
extern IMG_HANDLE
VXDIO_GetHandle(
    const IMG_CHAR    * pszPrefix,
    IMG_CHAR          * pszMemSpceName
);

/*!
******************************************************************************

 @Function              VXDIO_GetMemSpaceOffset

 @Description

 Returns offset to select memory/register space.

 @Input     hVxdCtx                 : Handle to video device IO context.

 @Input     ui32MemRegion           : Seleceted memory/register space.

 @Output    pui64MemSpaceOffset     : Offset will be placed here.

 @Return    IMG_RESULT              : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXDIO_GetMemSpaceOffset(
    IMG_HANDLE               hVxdCtx,
    IMG_UINT32               ui32MemRegion,
    IMG_UINT64             * pui64MemSpaceOffset
);

/*!
******************************************************************************

 @Function              VXDIO_GetMemSpacesHandles

 @Description

 Returns offset to select memory/register space.


 @Input     ui32CoreNum             : Core number.

 @Output    ppahMemSpaces           : Pointer to buffer where memory space
                                      handles will be placed. Buffer will be
                                      allocated in this function, caller has to
                                      free it after use.

 @Return    IMG_RESULT              : Returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
VXDIO_GetMemSpacesHandles(IMG_UINT32          ui32CoreNum,
                          IMG_HANDLE       ** ppahMemSpaces
);

/*!
******************************************************************************

 @Function              VXDIO_TriggerSim

 @Description

 This functions triggers internal processing loop of simulator.

 @Input     hVxdCtx                 : Handle to video device IO context.

 @Return    none

******************************************************************************/
extern IMG_VOID
VXDIO_TriggerSim(
    const IMG_HANDLE    hVxdCtx
);

#if !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG)
/*!
******************************************************************************

 @Function              VXDIO_ProcessDebugData

 @Description

 This functions is used to process debug data from firmware.

 @Input     hVxdCtx                 : Handle to video device IO context.

 @Return    none

******************************************************************************/
extern IMG_VOID
VXDIO_ProcessDebugData(
    const IMG_HANDLE    hVxdCtx
);

/*!
******************************************************************************

 @Function              VXDIO_EnableDebugFifo

 @Description

 This functions is used to enable debug fifo.

 @Input     hVxdCtx                 : Handle to video device IO context.

 @Return    none

******************************************************************************/
extern IMG_VOID
VXDIO_EnableDebugFifo(
    const IMG_HANDLE    hVxdCtx
);

/*!
******************************************************************************

 @Function              VXDIO_DisableDebugFifo

 @Description

 This functions is used to disable debug fifo.

 @Input     hVxdCtx                 : Handle to video device IO context.

 @Return    none

******************************************************************************/
extern IMG_VOID
VXDIO_DisableDebugFifo(
    const IMG_HANDLE    hVxdCtx
);

/*!
******************************************************************************

 @Function              VXDIO_GetDebugFifoSize

 @Description

 This functions is used to get debug fifo size

 @Input     hVxdCtx                 : Handle to video device IO context.

 @Return    Debug fifo size.

******************************************************************************/
extern IMG_UINT32
VXDIO_GetDebugFifoSize(
    const IMG_HANDLE    hVxdCtx
);

#endif /* !defined(SECURE_MEDIA_SUPPORT) && defined(IMG_DEBUG_FLAG) */

#if defined(__cplusplus)
}
#endif

#endif /* __VXDIO_H__ */



