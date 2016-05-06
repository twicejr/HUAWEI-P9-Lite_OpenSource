/*!
 *****************************************************************************
 *
 * @File       decoder.h
 * @Title      VDECDD Decoder Component
 * @Description    This file contains the structure and function prototypes
 *  for the VDECDD decoder component.
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

#ifndef __VDECDD_DECODER_H__
#define __VDECDD_DECODER_H__

#include "img_defs.h"
#include "vdecdd_int.h"

#ifdef __cplusplus
extern "C" {
#endif



/*!
******************************************************************************
 This enumeration describes the decoder callback types.
 @brief  Decoder Callback Types
******************************************************************************/
typedef enum
{
    DECODER_CB_POWEROFF_READY = VDECDD_CBGRP_DECODER,   /*!< Decoder has prepared all the cores for power off */
    DECODER_CB_CORE_IDLE,                               /*!< No pictures in-flight within component for this core */
    DECODER_CB_STREAM_IDLE,                             /*!< No pictures in-flight within component for this stream */
    DECODER_CB_UNIT_PROCESSED,                          /*!< Unit processed by Decoder. (pvData: #VDECDD_sStrUnit) */
    DECODER_CB_PICTURE_DISPLAY,                         /*!< Picture is output as display */
    DECODER_CB_PICTURE_DECODED,
    DECODER_CB_GET_PICT_BUF_NUMBER,
    DECODER_CB_MAX,

} DECODER_eCBType;


/*!
******************************************************************************

 @Function              DECODER_Initialise

 @Description

 This function prepares the global state of the decoder. There is a single
 instance of the decoder within the device driver. A single callback is
 registered for the decoder since it may not refer to a stream or core
 (see #DECODER_eCBType). pvStrParam: pvStrUserData supplied by user in
 DECODER_StreamCreate() and pvCoreParam: pvCoreUserData
 supplied by user in decoder_CoreEnumerate().

 @Input     pvInitUserData : Pointer to component-wide user data.

 @Input     pfnCallback : Pointer to component callback function.

 @Input     eInsecurePool : Insecure memory pool to be used.

 @Input     eSecureMemPool: Secure memory pool to be used

 @Output    psDdDevConfig : Pointer to device configuration.

 @Output    pui32NumCores : Pointer to number of cores.

 @Output    pui32NumPipes : Pointer to number of pipes per core.

 @Output    phDecCtx : Pointer to Decoder context handle.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_Initialise(
    IMG_VOID *              pvInitUserData,
    VDECDD_pfnCompCallback  pfnCallback,
    SYS_eMemPool            eInsecurePool,
    SYS_eMemPool            eSecureMemPool,
    VDECDD_sDdDevConfig   * psDdDevConfig,
    IMG_UINT32            * pui32NumCores,
    IMG_UINT32            * pui32NumPipes,
    IMG_HANDLE *            phDecCtx
);


#ifdef STACK_USAGE_TEST
/*!
******************************************************************************

 @Function              DECODER_StackTest

 @Description

 This function starts the stack usage check.

 Usage: during driver deinitialisation in vdeckm_fnDevDeinit().

 @Input     hDecCtx : Decoder context handle.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT 
DECODER_StackTest(
    IMG_HANDLE      hDecCtx
);
#endif


/*!
******************************************************************************

 @Function              DECODER_Deinitialise

 @Description

 This function shuts-down the decoder.

 Usage: during driver deinitialisation in vdeckm_fnDevDeinit().

 @Input     hDecCtx : Decoder context handle.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_Deinitialise(
    IMG_HANDLE  hDecCtx
);


/*!
******************************************************************************

 @Function              DECODER_IsSupportedFeature

 @Description

 This function is used to check whether a requested feature is supported.

 @Input     hDecCtx     : Decoder context handle.

 @Input     eFeature    : Feature of device (see #VDEC_eFeature).

 @Output    pbSupported : Pointer to feature supported flag.

 @Return    IMG_RESULT  : This function returns either IMG_SUCCESS or an
                          error code.

******************************************************************************/
extern IMG_RESULT
DECODER_IsSupportedFeature(
    IMG_HANDLE       hDecCtx,
    VDEC_eFeature    eFeature,
    IMG_BOOL       * pbSupported
);

/*!
******************************************************************************

 @Function              DECODER_SupportedFeatures

 @Description

 This function is used to check the supported features.

 @Input     hDecCtx     : Decoder context handle.

 @Output    psFeatures : Pointer to feature supported structure.

 @Return    IMG_RESULT  : This function returns either IMG_SUCCESS or an
                          error code.

******************************************************************************/
IMG_RESULT DECODER_SupportedFeatures(
    IMG_HANDLE          hDecCtx,
    VDEC_sFeatures    * psFeatures
);

/*!
******************************************************************************

 @Function              DECODER_GetLoad

 @Description

 Obtains the loading (available and min.) for cores which support the requested
 features.

 @Input     hDecCtx     : Decoder context handle.

 @Input     ui32CoreFeatures : Core features (see #VDECDD_eCoreFeatureFlags).

 @Input     pui32AvailLoad : Pointer to available core load metric.

 @Input     pui32MinLoad : Pointer to least-loaded-core load metric.

 @Return    IMG_RESULT  : This function returns either IMG_SUCCESS or an
                          error code.

******************************************************************************/
extern IMG_RESULT DECODER_GetLoad(
    IMG_HANDLE    hDecCtx,
    IMG_UINT32    ui32CoreFeatures,
    IMG_UINT32  * pui32AvailLoad,
    IMG_UINT32  * pui32MinLoad
);


/*!
******************************************************************************

 @Function              DECODER_CheckSupport

 @Description

 Checks whether configuration/state is valid for decoding.

 @Input     hDecCtx     : Decoder context handle.

 @Input     psStrConfigData : Pointer to stream configuration information.

 @Input     psOutputConfig : Pointer to output configuration information.

 @Input     psDispPictBuf : Pointer to display picture buffer.

 @Input     psReqPictRendInfo : Pointer to required display picture render information.

 @Input     psComSequHdrInfo : Pointer to common Sequence header information.

 @Input     psPictHdrInfo : Pointer to Picture header information.

 @Input     psPrevComSequHdrInfo : Pointer to previous common Sequence header information.

 @Input     psPrevPictHdrInfo : Pointer to previous Picture header information.

 @Output    psUnsupported : Pointer to unsupported flags structure to populate.

 @Output    pui32Features : Pointer to core feature flags (see #VDECDD_eCoreFeatureFlags).

 @Return    IMG_RESULT  : This function returns either IMG_SUCCESS or an
                          error code.

******************************************************************************/
extern IMG_RESULT
DECODER_CheckSupport(
    IMG_HANDLE                     hDecCtx,
    const VDEC_sStrConfigData    * psStrConfig,
    const VDEC_sStrOutputConfig  * psOutputConfig,
    const VDECDD_sDdPictBuf      * psDispPictBuf,
    const VDEC_sPictRendInfo     * psReqPictRendInfo,
    const VDEC_sComSequHdrInfo   * psComSequHdrInfo,
    const BSPP_sPictHdrInfo      * psPictHdrInfo,
    const VDEC_sComSequHdrInfo   * psPrevComSequHdrInfo,
    const BSPP_sPictHdrInfo      * psPrevPictHdrInfo,
    VDEC_sUnSupportedFlags       * psUnsupported,
    IMG_UINT32                   * pui32Features
);


/*!
******************************************************************************

 @Function              DECODER_Replay

 @Description

 This function replays all pending transactions on all cores.

 Usage: temporary as a simple fix for internally handing stream destruction
 whilst playing. It should follow DECODER_ResetCores().

 @Input     hDecCtx     : Decoder context handle.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT DECODER_Replay(
    IMG_HANDLE  hDecCtx
);


/*!
******************************************************************************

 @Function              DECODER_ResetCores

 @Description

 This function resets all cores in preparation for destroying one or more streams
 whilst they are still playing.

 Usage: temporary as a simple fix for internally handing stream destruction
 whilst playing.

 @Input     hDecCtx     : Decoder context handle.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT DECODER_ResetCores(
    IMG_HANDLE  hDecCtx
);


/*!
******************************************************************************

 @Function              DECODER_PowerOff

 @Description

 This function shuts off cores with nothing in the queue.

 Usage: Acitve Power Management

 @Input     hDecCtx     : Decoder context handle.

 @Input     bForceAll   : Force to switch off all cores

 @Return	IMG_RESULT : This function returns either IMG_SUCCESS or an
						 error code.

******************************************************************************/
extern IMG_RESULT
DECODER_PowerOff(
    IMG_HANDLE          hDecCtx,
    IMG_BOOL            bForceAll
);

/*!
******************************************************************************

 @Function              DECODER_PrePowerOff

 @Description

 This function prepares all decoder cores for imminent power-down. The completion
 of this is reported via callback #DECODER_CB_POWEROFF_READY.

 Usage: before cores are powered-down

 @Input     hDecCtx     : Decoder context handle.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_PrePowerOff(
    IMG_HANDLE  hDecCtx
);


/*!
******************************************************************************

 @Function              DECODER_PostPowerOn

 @Description

 This function prepares all decoder cores after recent power-up.

 Usage: after cores are powered-up

 @Input     hDecCtx     : Decoder context handle.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_PostPowerOn(
    IMG_HANDLE  hDecCtx
);


/*!
******************************************************************************

 @Function              DECODER_HandleInterrupt

 @Description

 This function handles the device interrupts and makes a request for the decoder
 to later service the core interrupt.

 Usage: when an interrupt has been received from the core.

 @Input     psDdDevContext : Pointer to device context.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_HandleInterrupt(
    VDECDD_sDdDevContext  * psDdDevContext
);


/*!
******************************************************************************

 @Function              DECODER_CoreServiceTimerExpiry

 @Description

 This function resets the core and replays pictures that were queued for
 processing.

 Usage: when the core has become unresponsive

 @Input     hDecCtx     : Decoder Context handle.
 
 @Input     ui32CoreNum : Decoder Core number of the core whose timer has expired.
 
 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_CoreServiceTimerExpiry(
    IMG_HANDLE  hDecCtx,
    IMG_UINT32  ui32CoreNum
);

/*!
******************************************************************************

 @Function              DECODER_CoreReset

 @Description

 This function resets the core and replays pictures that were queued for
 processing (according to eReason given)

 Usage: when the core has become unresponsive

 @Input     hDecCtx     : Decoder Context handle.

 @Input     eReason : Reason of the reset (DWR, MMUPF...)

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_CoreReset(
    IMG_HANDLE  hDecCtx,
    IMG_UINT32  ui32CoreNum,
    VDECDD_eResetReason eReason
);
/*!
******************************************************************************

 @Function              DECODER_CoreReplay

 @Description

 This function Replays on a particular core.

 Usage: In response to a Service timer expiry

 @Input     hDecCtx     : Decoder Context handle.
 
 @Input     ui32CoreNum : Decoder Core number of the core to replay.
 
 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_CoreReplay(
    IMG_HANDLE  hDecCtx,
    IMG_UINT32  ui32CoreNum
);



/*!
******************************************************************************

 @Function              DECODER_CoreServiceInterrupt

 @Description

 This function services any core interrupt.

 @Input     hDecServiceInt : Decoder interrupt servicing handle.

 @Output    ppvStrUserIntData  : Pointer to pointer to stream user interrupt
                                 data (registered with DECODER on #DECODER_StreamCreate).
                                 This will be IMG_NULL if no stream can be associated
                                 with the signalled interrupt.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_CoreServiceInterrupt(
    IMG_HANDLE     hDecServiceInt,
    IMG_VOID    ** ppvStrUserIntData
);


/*!
******************************************************************************

 @Function              DECODER_StreamCreate

 @Description

 This function creates a decoder stream context.

 Usage: Should be called before other DECODE_Core or DECODE_Stream functions.

 @Input     hDecCtx : Decoder context handle.

 @Input     sStrConfig : Configuration data structure.

 @Output    phMmuStrHandle : Pointer to VDECDD MMU stream context handle.

 @Input     pvStrUserData : Pointer to stream-specific user data.

 @Input     pvStrUserIntData : Pointer to stream-specific user data related to interrupts.

 @Output    phDecStrCtx : Pointer to decoder stream context handle

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_StreamCreate(
    IMG_HANDLE             hDecCtx,
    VDEC_sStrConfigData    sStrConfig,
    IMG_HANDLE           * phMmuStrHandle,
    IMG_VOID             * pvStrUserData,
    IMG_VOID             * pvStrUserIntData,
    IMG_HANDLE           * phDecStrCtx
);


/*!
******************************************************************************

 @Function              DECODER_StreamIsIdle

 @Description

 This function report whether the stream has no outstanding stream units to process.

 @Input     hDecStrCtx : Decoder stream context handle.

 @Return    IMG_BOOL   : Indicates whether stream is idle.

******************************************************************************/
extern IMG_BOOL
DECODER_StreamIsIdle(
    IMG_HANDLE  hDecStrCtx
);


/*!
******************************************************************************

 @Function              DECODER_StreamProcessUnit

 @Description

 This function submits a stream unit to the decoder for processing. This function
 should return an error if space was not available on the core.

 @Input     hDecStrCtx : Decoder stream context handle.

 @Input     psStrUnit  : Pointer to stream unit.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_StreamProcessUnit(
    IMG_HANDLE         hDecStrCtx,
    VDECDD_sStrUnit  * psStrUnit
);


/*!
******************************************************************************

 @Function              DECODER_StreamFlushInput

 @Description

 This function handles all stream units up until (but not including) the next 
 picture.

 @Input     hDecServiceInt    : Decoder interrupt servicing handle.

 @Output    ppvStrUserIntData : Pointer to pointer to stream user interrupt
                                data (registered with DECODER on #DECODER_StreamCreate).

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_StreamFlushInput(
    IMG_HANDLE     hDecServiceInt,
    IMG_VOID    ** ppvStrUserIntData
);


/*!
******************************************************************************

 @Function              DECODER_StreamFlush

 @Description

 This function flushes all decoded pictures (inc. references) for the stream and
 returns any outstanding display images via callback #DECODER_CB_PICTURE_DISPLAY.

 @Input     hDecStrCtx : Decoder stream context handle.

 @Input     bDiscardRefs : Indicates that references should be dropped.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_StreamFlush(
    IMG_HANDLE  hDecStrCtx,
    IMG_BOOL    bDiscardRefs
);


/*!
******************************************************************************

 @Function              DECODER_StreamReleaseBuffers

 @Description

 This function is used to release references to all decoded image buffers held
 by Decoder. Associated internal buffers will also be freed.

 NOTE: Should only be called in the "stopped" state.

 @Input     hDecStrCtx : Scheduler stream context handle.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS
                         or an error code.

******************************************************************************/
extern IMG_RESULT
DECODER_StreamReleaseBuffers(
    IMG_HANDLE  hDecStrCtx
);


/*!
******************************************************************************

 @Function              DECODER_StreamGetStatus

 @Description

 This function is used to obtain the stream status information from the Decoder
 component.

 @Input     hDecStrCtx     : Decoder stream context handle.

 @Output    psDecStrStatus : Pointer to Decoder stream status structure.

 @Return    IMG_RESULT    : This function returns either IMG_SUCCESS or an
                            error code.

******************************************************************************/
extern IMG_RESULT
DECODER_StreamGetStatus(
    IMG_HANDLE              hDecStrCtx,
    VDECDD_sDecStrStatus  * psDecStrStatus
);


/*!
******************************************************************************

 @Function              DECODER_StreamDestroy

 @Description

 This function destroys a decoder stream context.

 Usage: whilst destroying stream in VDECDD_StreamDestroy().

 @Input     hDecStrCtx : Decoder stream context handle.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an
                         error code.

******************************************************************************/
extern IMG_RESULT
DECODER_StreamDestroy(
    IMG_HANDLE  hDecStrCtx
);


#if defined(__cplusplus)
}
#endif

#endif /* __VDECDD_DECODER_H__    */
