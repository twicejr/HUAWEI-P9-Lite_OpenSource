/*!
 *****************************************************************************
 *
 * @File       scheduler.h
 * @Title      VDECDD Scheduler Component
 * @Description    This file contains the structure and function prototypes
 *  for the VDECDD scheduler component.
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

#ifndef __VDECDD_SCHEDULER_H__
#define __VDECDD_SCHEDULER_H__

#include <img_defs.h>
#include <vdecdd.h>
#include <vdecdd_int.h>

#ifdef __cplusplus
extern "C" {
#endif


/*!
******************************************************************************
 This enum defines resource availability masks.
 @brief  Resource Availability
******************************************************************************/
typedef enum
{
    SCHEDULER_AVAIL_PICTBUF = (1 << 0),
    SCHEDULER_AVAIL_PICTRES = (1 << 1),
    SCHEDULER_AVAIL_CORE    = (1 << 2),

    SCHEDULER_AVAIL_MAX


} SCHEDULER_eAvailablility;

/*!
******************************************************************************
 This enumeration describes the scheduler callback types.
 @brief  Scheduler Callback Types
******************************************************************************/
typedef enum
{
    SCHEDULER_CB_PROCESS_UNIT = VDECDD_CBGRP_SCHEDULER, /*!< Request to submit stream unit for processing (pvData: #VDECDD_sStrUnit*) */
    SCHEDULER_CB_RESCHEDULE,                            /*!< Request to obtain another scheduling time-slice (pvData: IMG_NULL). */
    SCHEDULER_CB_STREAM_CHECK_LOAD,                       /*!< Return the new picture header. Core can decide whether this can be decoded (pvData: #BSPP_sPictHdrInfo*). */
    SCHEDULER_CB_STREAM_RECONFIGRE_RECON_PICTBUFS,      /*!< Reconfigure reconstructed picture buffers now that none are held for reference. */
    SCHEDULER_CB_STREAM_CHECK_SUPPORTED,
    SCHEDULER_CB_ACTIVE_POWER_DOWN,
    SCHEDULER_CB_MAX

} SCHEDULER_eCBType;


/*!
******************************************************************************

 @Function              SCHEDULER_Initialise

 @Description

 This function prepares the global state of the scheduler. There is a single
 instance of the scheduler within the device driver. A single callback is
 registered for the scheduler since it may not refer to a stream or core
 (see #SCHEDULER_eCBType). pvStrParam: pvStrUserData supplied by user in
 SCHEDULER_StreamCreate() and pvCoreParam = IMG_NULL.

 Usage: during driver initialisation in vdeckm_fnDevInit().

 @Input     pvInitUserData  : Pointer to component-wide user data.

 @Input     pfnCallback     : Pointer to component callback function.

 @Input     eDecodeLevel    : Level in system to which decoding should take place.

 @Input     bAPM            : Active power management turned off or on
 
 @Input     hDecCtx         : Handle to decoder context.

 @Output    phSchCtx        : Pointer to Scheduler context handle.

 @Return   IMG_RESULT       : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_Initialise(
    IMG_VOID *              pvInitUserData,
    VDECDD_pfnCompCallback  pfnCallback,
    VDECDD_eDecodeLevel     eDecodeLevel,
    IMG_BOOL                bAPM,
    IMG_HANDLE              hDecCtx,
    IMG_HANDLE           *  phSchCtx
);


/*!
******************************************************************************

 @Function              SCHEDULER_Deinitialise

 @Description

 This function shuts-down the scheduler.

 Usage: during driver deinitialisation in vdeckm_fnDevDeinit().

 @Input     hSchCtx : Scheduler context handle.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_Deinitialise(
    IMG_HANDLE  hSchCtx
);


/*!
******************************************************************************

 @Function              SCHEDULER_Run

 @Description

 This function runs the scheduling algorithm. This will be based upon
 core availability (resource) and stream resources/loading/priority. The decode
 resources are requested for a picture on a given stream and, if successful,
 the picture is submitted for decode. Note that any paused stream via
 SCHEDULER_StreamPause() will not be serviced until SCHEDULER_StreamResume().

 Usage: periodic scheduling of streams. Note this function should not be
 called during another components time-slice.

 @Input     hSchCtx             : Scheduler context handle.

 @Output    ppvStrUserIntData   : Pointer to stream user data pointer.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_Run(
    IMG_HANDLE      hSchCtx,
    IMG_VOID     ** ppvStrUserIntData
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamCreate

 @Description

 This function creates a scheduler stream context.

 @Input     hSchCtx : Scheduler context handle.
 
 @Input     ui32StrId : Kernel RMAN stream ID.

 @Input     psStrConfig : Pointer to configuration data structure.

 @Input     pvStrUserData : Pointer to stream-specific user data.

 @Output    phSchStrCtx : Pointer to scheduler stream context handle

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamCreate(
    IMG_HANDLE             hSchCtx,
    IMG_UINT32             ui32StrId,
    VDEC_sStrConfigData *  psStrConfig,
    IMG_VOID *             pvStrUserData,
    IMG_HANDLE *           phSchStrCtx
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamDestroy

 @Description

 This function destroys a scheduler stream context.

 Usage:

 @Input     hSchStrCtx : Scheduler stream context handle.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamDestroy(
    IMG_HANDLE  hSchStrCtx
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamPlay

 @Description

 This function allows pending pictures on this stream to be scheduled
 for decoding. The scheduling will continue until the stop point is reached.

 @Input    hSchStrCtx : Scheduler stream context handle.

 @Input    ePlayMode  : Sets the "play" mode.

 @Input    eStopPoint : Sets the decode stop point.

 @Input    psDispPictBuf : Pointer to display picture buffer template.

 @Input    psOutputConfig : Pointer to the output configuration information.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamPlay(
    IMG_HANDLE                    hSchStrCtx,
    VDEC_ePlayMode                ePlayMode,
    VDEC_eStopPoint               eStopPoint,
    const VDECDD_sDdPictBuf     * psDispPictBuf,
    const VDEC_sStrOutputConfig * psOutputConfig
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamStop

 @Description

 This function prevents a set of pending pictures of this stream from being
 submitted for decode. Which pending pictures will not be submitted is determined
 based on the eStopPoint value. Any calls to SCHEDULER_StreamAddUnit()
 will behave as normal.

 @Input    hSchStrCtx : Scheduler stream context handle.

 @Input    eStopPoint : Sets the decode stop point.

 @Input    ui32Error  : Error status (only used with eStopPoint = VDEC_STOPPOINT_NOW).

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamStop(
    IMG_HANDLE       hSchStrCtx,
    VDEC_eStopPoint  eStopPoint,
    IMG_UINT32       ui32Error
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamSignalStopStatus

 @Description

 This function signals new status flags to cause Scheduler to stop.

 @Input    hSchStrCtx : Scheduler stream context handle.

 @Input    ui32StopFlags : Stop flags to report.

 @Output   pui32StopFlags : Pointer to external flags that need updating.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamSignalStopStatus(
    IMG_HANDLE      hSchStrCtx,
    IMG_UINT32      ui32StopFlags,
    IMG_UINT32    * pui32StopFlags
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamSetLoadInfo

 @Description

 Sets the load information for least loaded available core (i.e. has slots for
 decoding) and least loaded core (regardless of availability) where the core
 supports all required features of the stream.

 @Input    hSchStrCtx : Scheduler stream context handle.

 @Input    ui32Features : Core features set for this picture.

 @Input    ui32AvailLoad : Load metric for available suitable core

 @Input    ui32MinLoad : Load metric for least loaded suitable core

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamSetLoadInfo(
    IMG_HANDLE  hSchStrCtx,
    IMG_UINT32  ui32Features,
    IMG_UINT32  ui32AvailLoad,
    IMG_UINT32  ui32MinLoad
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamAddUnit

 @Description

 This function is used to pass a stream unit to be scheduled for processing.
 All required resources will be associated with the unit before processing.
 The SCHEDULER_Run() function will then be called to execute the scheduling
 algorithm to submit the unit to the Decoder.

 @Input    hSchStrCtx : Scheduler stream context handle.

 @Input    psStrUnit  : Pointer to coded picture.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamAddUnit(
    IMG_HANDLE         hSchStrCtx,
    VDECDD_sStrUnit *  psStrUnit
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamAddPictureBuffer

 @Description

 This function is used to submit a picture buffer to decode a picture into.

 @Input    hSchStrCtx     : Scheduler stream context handle.

 @Input    psDdBufMapInfo : Pointer to picture buffer info structure.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamAddPictureBuffer(
    IMG_HANDLE              hSchStrCtx,
    VDECDD_sDdBufMapInfo *  psDdBufMapInfo
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamAddPictureResource

 @Description

 This function is used to add picture related resources.

 @Input    hSchStrCtx    : Scheduler stream context handle.

 @Input    psPictResInt  : Pointer to picture resource structure.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamAddPictureResource(
    IMG_HANDLE            hSchStrCtx,
    VDECDD_sPictResInt *  psPictResInt
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamRemovePictureBuffer

 @Description

 This function is used to remove a picture buffer from Scheduler resources and
 should be called when a picture buffer is unmapped.

 @Input    hSchStrCtx     : Scheduler stream context handle.

 @Input    psDdBufMapInfo : Pointer to picture buffer info structure.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamRemovePictureBuffer(
    IMG_HANDLE              hSchStrCtx,
    VDECDD_sDdBufMapInfo *  psDdBufMapInfo
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamRemovePictureResource

 @Description

 This function is used to remove a picture resource from Scheduler resources and
 should be called when a picture resource is no longer available.

 @Input    hSchStrCtx     : Scheduler stream context handle.

 @Input    psPictResInt  : Pointer to picture resource structure.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamRemovePictureResource(
    IMG_HANDLE            hSchStrCtx,
    VDECDD_sPictResInt *  psPictResInt
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamReleaseBuffers

 @Description

 This function is used to release any reference to buffers held by SCHEDULER.
 All the internal buffers bound to buffers being released will also be freed.

 NOTE: Should only be called in the "stopped" state.

 @Input    hSchStrCtx : Scheduler stream context handle.

 @Input    eBufType   : Indicates the type of buffers to be returned/released.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamReleaseBuffers(
    IMG_HANDLE     hSchStrCtx,
    VDEC_eBufType  eBufType
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamSetBehaviourOnErrors

 @Description

 This function allows for defining how to behave on stream processing errors.

 @Input    hSchStrCtx     : Scheduler stream context handle.

 @Input    eErrorHandling : Defines how to behave on errors.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamSetBehaviourOnErrors(
    IMG_HANDLE           hSchStrCtx,
    VDEC_eErrorHandling  eErrorHandling
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamGetStatus

 @Description

 This function is used to obtain the stream status information from the Scheduler
 component.

 @Input    hSchStrCtx     : Scheduler stream context handle.

 @Output   psSchStrStatus : Pointer to the Scheduler stream status structure.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
SCHEDULER_StreamGetStatus(
    IMG_HANDLE              hSchStrCtx,
    VDECDD_sSchStrStatus *  psSchStrStatus
);


/*!
******************************************************************************

 @Function              SCHEDULER_StreamGetPictBufNum

 @Description

 This function is used to obtain the number of image buffers registered
 from the Scheduler component.

 @Input    hSchStrCtx     : Scheduler stream context handle.

 @Output   pui32NumImageBuffers : Pointer to the variable in which the number
                                  of image buffers is to be returned.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
IMG_RESULT
SCHEDULER_StreamGetNumImageBuffers(
    IMG_HANDLE    hSchStrCtx,
    IMG_UINT32 *  pui32NumImageBuffers
);



#if defined(__cplusplus)
}
#endif

#endif /* __VDECDD_SCHEDULER_H__    */
