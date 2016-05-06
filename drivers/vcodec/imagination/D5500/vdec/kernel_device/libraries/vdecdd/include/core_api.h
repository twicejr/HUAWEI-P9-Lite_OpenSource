/*!
 *****************************************************************************
 *
 * @File       core_api.h
 * @Title      VDECDD Core API.
 * @Description    This file contains the VDECDD Core API.
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

#ifndef __CORE_API_H__
#define __CORE_API_H__

#include "img_errors.h"
#include "img_defs.h"
#include "vdec_api.h"
#include "vdecdd.h"
#include "vdecdd_int.h"

#ifdef __cplusplus
extern "C" {
#endif


/*!
******************************************************************************

 @Function              CORE_Initialise

 @Description

 This function is used to initialised the core when the first process connects
 to the device.

 @Input    hDevHandle      : The device handle.

 @Input    eMemPool        : System memory pool (insecure)

 @Input    eSecureMemPool  : System secure memory pool

 @Output   ppsDdDevContext : A pointer used to return the #VDECDD_sDdDevContext
                             structure.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_Initialise(
    IMG_HANDLE               hDevHandle,
    SYS_eMemPool             eMemPool,
    SYS_eMemPool             eSecureMemPool,
    VDECDD_sDdDevContext **  ppsDdDevContext
);


/*!
******************************************************************************

 @Function              CORE_Deinitialise

 @Description

 This function is used to de-initialise the core and is called by portability
 framework when the last connection to the device is discontinued.

 @Input    psDdDevContext : A pointer to the #VDECDD_sDdDevContext structure.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_Deinitialise(
    VDECDD_sDdDevContext *  psDdDevContext
);


/*!
******************************************************************************

 @Function              CORE_ConnectionCreate

 @Description

 This function is used to create a connection to the core.

 @Input    psDdDevContext   : A pointer to the #VDECDD_sDdDevContext structure.

 @Output   ppsDdConnContext : Pointer to return pointer to connection context.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_ConnectionCreate(
    VDECDD_sDdDevContext      * psDdDevContext,
    VDECDD_sDdConnContext    ** ppsDdConnContext
);


/*!
******************************************************************************

 @Function              CORE_ConnectionDestroy

 @Description

 This function is used to create a connection to the core.

 @Input    ui32ConnId     : Connection ID.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_ConnectionDestroy(
    IMG_UINT32      ui32ConnId
);


/*!
******************************************************************************

 @Function              CORE_StreamCreate

 @Description

 This function is used to create a stream.

 @Input    ui32ConnId      : Connection ID.

 @Input    psStrConfigData : A pointer to a #VDEC_sStrConfigData structure.

 @Input    pvStrCbParam    : A pointer to client defined stream data or IMG_NULL.

 @Output   pui32StrId      : A pointer used to return the stream id.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamCreate(
    IMG_UINT32              ui32ConnId,
    VDEC_sStrConfigData   * psStrConfigData,
    IMG_VOID              * pvStrCbParam,
    IMG_UINT32            * pui32StrId
);


/*!
******************************************************************************

 @Function              CORE_StreamDestroy

 @Description

 This function is used to destroy a stream.

 @Input    ui32StrId        : Stream ID.

 @Input    hDestroyedEvent  : Handle to destroyed stream event object.

 @Output    pui32ConnId  : Pointer to store connection ID.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamDestroy(
    IMG_UINT32      ui32StrId,
    IMG_HANDLE      hDestroyedEvent,
    IMG_UINT32    * pui32ConnId
);


/*!
******************************************************************************

 @Function              CORE_StreamPlay

 @Description

 This function is used to start playing.

 @Input    ui32StrId         : Stream ID.

 @Input    ePlayMode         : Sets the "play" mode.

 @Input    eStopPoint        : Sets the decode stop point.

 @Input    ui32StopPointQual : Use to qualify the stop point.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamPlay(
    IMG_UINT32              ui32StrId,
    VDEC_ePlayMode          ePlayMode,
    VDEC_eStopPoint         eStopPoint,
    IMG_UINT32              ui32StopPointQual
);



/*!
******************************************************************************

 @Function              CORE_StreamStop

 @Description

 This function is used to stop and allows any in-flight data to flow through
 the system and be decoded.

 A #VDEC_EVENT_STREAM_STOPPED event is used to signal when the decoding has
 stopped.

 eStopPoint set the point to stop.

 @Input    ui32StrId         : Stream ID.

 @Input    eStopPoint        : Sets the decode stop point.

 @Input    ui32StopPointQual : Use to qualify the stop point.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamStop(
    IMG_UINT32              ui32StrId,
    VDEC_eStopPoint         eStopPoint,
    IMG_UINT32              ui32StopPointQual
);


/*!
******************************************************************************

 @Function              CORE_StreamGetStopFlags

 @Description

 This function is used to obtained the stopped status flags.

 @Input    ui32StrId      : Stream ID.

 @Output   pui32StopFlags : A pointer used to return the stopped status
                            flags as defined in #VDEC_eStopFlags.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamGetStopFlags(
    IMG_UINT32              ui32StrId,
    IMG_UINT32 *            pui32StopFlags
);


/*!
******************************************************************************

 @Function              CORE_StreamMapBuf

 @Description

 This function is used to map a buffer into the device MMU.

 NOTE: The buffer must have been allocated in a way that allows th memory to
 be mapped in the devices MMU.

 @Input    ui32StrId      : Stream ID.

 @Input    pvBufCbParam   : A pointer to client defined buffer data or IMG_NULL.

 @Input    eBufType       : Type of buffer to be mapped.

 @Input    psBufInfo      : A pointer to a #VDEC_sBufInfo structure
                            containing the buffer information.

 @Output   pui32BufMapId  : A pointer used to return the buffer mapping id.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamMapBuf(
    IMG_UINT32              ui32StrId,
    IMG_VOID *              pvBufCbParam,
    VDEC_eBufType           eBufType,
    VDEC_sBufInfo         * psBufInfo,
    IMG_UINT32            * pui32BufMapId
);


/*!
******************************************************************************

 @Function              CORE_StreamUnmapBuf

 @Description

 This function is used to unmap a buffer from the device MMU.

 NOTE: The buffers should not be unmapped if the buffers is currently "held"
 by VDECDD as an bit stream buffer being decoded or as a picture buffer queued
 for decoding into or as a reference frame.

 @Input    ui32BufMapId   : Buffer Map ID.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamUnmapBuf(
    IMG_UINT32              ui32BufMapId
);


/*!
******************************************************************************

 @Function                CORE_StreamSubmitUnit

 @Description

 This function is used to submit a stream unit at the front end.

 @Input    ui32StrId      : Stream ID.

 @Input    psStrUnit      : A pointer to a stream unit structure #VDECDD_sStrUnit.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamSubmitUnit(
    IMG_UINT32              ui32StrId,
    VDECDD_sStrUnit       * psStrUnit
);


/*!
******************************************************************************

 @Function              CORE_StreamSetOutputConfig

 @Description

 This function is used to set the output configuration.

 @Input    ui32StrId         : Stream ID.

 @Input    psStrOutputConfig : A pointer to a #VDEC_sStrOutputConfig
                               structure containing the changes to the
                               output configuration.

 @Input    psPictBufConfig   : A pointer to picture buffer configuration.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamSetOutputConfig(
    IMG_UINT32              ui32StrId,
    VDEC_sStrOutputConfig * psStrOutputConfig,
    VDEC_sPictBufConfig   * psPictBufConfig
);


/*!
******************************************************************************

 @Function              CORE_StreamFillPictBuf

 @Description

 This function is used to submit or return a picture buffer to allow it to
 be re-used.

 @Input    ui32BufMapId   : Buffer Map ID.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamFillPictBuf(
    IMG_UINT32              ui32BufMapId
);


/*!
******************************************************************************

 @Function                CORE_StreamFlush

 @Description

 This function synchronously flushes the Decoder and returns via callback
 any buffers required for display.

 @Input    ui32StrId      : Stream ID.

 @Input    bDiscardRefs   : Indicates that references should be dropped.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamFlush(
    IMG_UINT32              ui32StrId,
    IMG_BOOL                bDiscardRefs
);


/*!
******************************************************************************

 @Function              CORE_StreamReleaseBufs

 @Description

 This function is used to release any reference to buffers held by VDEC.
 Once called the client is free to discard or re-use the released buffers.

 @Input    ui32StrId      : Stream ID.

 @Input    eBufType       : Indicates the type of buffers to be returned/released.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamReleaseBufs(
    IMG_UINT32              ui32StrId,
    VDEC_eBufType           eBufType
);


/*!
******************************************************************************

 @Function              CORE_StreamSetBehaviourOnErrors

 @Description

 This function allows for defining how VDEC behaves on stream processing errors.

 @Input    ui32StrId      : Stream ID.

 @Input    eErrorHandling : Defines how to behave on errors.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamSetBehaviourOnErrors(
    IMG_UINT32              ui32StrId,
    VDEC_eErrorHandling     eErrorHandling
);


/*!
******************************************************************************

 @Function              CORE_StreamGetStatus

 @Description

 This function is used to obtain the stream status information from the device
 driver.

 @Input    ui32StrId      : Stream ID.

 @Output   psStrStatus    : Pointer to device driver stream status structure.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_StreamGetStatus(
    IMG_UINT32              ui32StrId,
    VDECDD_sStrStatus *     psStrStatus
);


/*!
******************************************************************************

 @Function              CORE_DevSchedule

 @Description 

 This function is used to run the scheduler.

 @Input    psDdDevContext : A pointer to the #VDECDD_sDdDevContext structure.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_DevSchedule(
    VDECDD_sDdDevContext *  psDdDevContext
);


/*!
******************************************************************************

 @Function              CORE_DevHwInterrupt

 @Description

 This function is used to process an interrupt for a particular core.
 
 @Input     psDdDevContext : A pointer to the #VDECDD_sDdDevContext structure.

 @Input     hDecServiceInt : Decoder interrupt servicing handle. 

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_DevHwInterrupt(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_HANDLE              hDecServiceInt
);


/*!
******************************************************************************

 @Function              CORE_DevSwInterrupt

 @Description

 This function is used to process an interrupt for a particular core.
 
 @Input     psDdDevContext : A pointer to the #VDECDD_sDdDevContext structure.

 @Input     hDecServiceInt : Decoder interrupt servicing handle. 

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_DevSwInterrupt(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_HANDLE              hDecServiceInt
);

/*!
******************************************************************************

 @Function              CORE_DevReset

 This function is used to invoke a vxd reset
 
 @Input     psDdDevContext : A pointer to the #VDECDD_sDdDevContext structure.

 @Input     ui32CoreNum    : Core Number 

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.
******************************************************************************/
extern IMG_RESULT CORE_DevReset(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_UINT32              ui32CoreNum,
    VDECDD_eResetReason     eReason
);

/*!
******************************************************************************

 @Function              CORE_DevServiceTimeExpiry

 This function is used to process a service time expiry for a particular core.

 @Input     psDdDevContext : A pointer to the #VDECDD_sDdDevContext structure.

 @Input     ui32CoreNum    : Core Number

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.
******************************************************************************/
extern IMG_RESULT CORE_DevServiceTimeExpiry(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_UINT32              ui32CoreNum
);

/*!
******************************************************************************

 @Function              CORE_DevReplay

 This function is used to post a replay for a particular core.

 Usage: After a service time expiry
 
 @Input     psDdDevContext : A pointer to the #VDECDD_sDdDevContext structure.

 @Input     ui32CoreNum    : Core Number 

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.
******************************************************************************/
extern IMG_RESULT CORE_DevReplay(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_UINT32              ui32CoreNum
);

/*!
******************************************************************************

 @Function              CORE_DevSwInterruptPicDiscarded

 @Description

 This function is used to post for dealing with discarded picture..
 
 @Input     psDdDevContext : A pointer to the #VDECDD_sDdDevContext structure.

 @Input     hDecServiceInt : Decoder interrupt servicing handle. 

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_DevSwInterruptPicDiscarded(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_HANDLE              hDecServiceInt
);



/*!
******************************************************************************

 @Function              CORE_DevPowerPreS5

 @Description

 This is the power management callback function for entering S5 (off).

 See definition of #DMANKM_pfnDevPowerPreS5.

 @Input    psDdDevContext : A pointer to the #VDECDD_sDdDevContext structure.

 @Return   None.

******************************************************************************/
extern IMG_VOID CORE_DevPowerPreS5(
    VDECDD_sDdDevContext *  psDdDevContext
);


/*!
******************************************************************************

 @Function              CORE_DevPowerPostS0

 @Description

 This is the power management callback function for entering S5 (off).

 See definition of #DMANKM_pfnDevPowerPostS0.

 @Input    psDdDevContext : A pointer to the #VDECDD_sDdDevContext structure.

 @Return   None.

******************************************************************************/
extern IMG_VOID CORE_DevPowerPostS0(
    VDECDD_sDdDevContext *  psDdDevContext
);


/*!
******************************************************************************

 @Function              CORE_ProcessEvent

 @Description

 This function is used to process one event.

 NOTE: Called from vdeckm_fnDevKmHisr.

 NOTE: Should NOT be called called directly.

 @Input    psDdDevContext : A pointer to the #VDECDD_sDdDevContext structure.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT CORE_ProcessEvent(
    VDECDD_sDdDevContext *  psDdDevContext
);


#ifdef __cplusplus
}
#endif

#endif /* __CORE_API_H__   */


