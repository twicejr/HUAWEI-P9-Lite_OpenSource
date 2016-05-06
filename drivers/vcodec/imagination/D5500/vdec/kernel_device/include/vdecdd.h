/*!
 *****************************************************************************
 *
 * @File       vdecdd.h
 * @Title      VDEC Device Driver.
 * @Description    This file contains the header file information for the
 *  VDEC Device User Mode interface.
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

#if !defined (__VDECDD_H__)
#define __VDECDD_H__

#include <img_defs.h>

#include <vdec_api.h>
#include <vdec_int.h>
#include "vdecdd_defs.h"

#include "bspp.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*! Clears '__user' in user space but make it visible for doxygen */
#if !defined(IMG_KERNEL_MODULE) && !defined(__RPCCODEGEN__)
    #define __user
#endif

#ifdef  __RPCCODEGEN__
  #define rpc_prefix      VDECDD
  #define rpc_filename    vdecdd
#endif

/*! Macro to optionally not assert on return paths that have already been tested. */
#if 0
#define IMG_ASSERT_TESTED(test)   IMG_ASSERT(test)
#else
#define IMG_ASSERT_TESTED(test)
#endif



/*!
******************************************************************************
 This structure contains the event callback information.
 @brief   Event Callback Information
 ******************************************************************************/
typedef struct
{
    SYSBRG_POINTER(IMG_VOID, lst_padding);				//*!< Reserved space for LST_LINK link  (allows the structure to be part of a LST).*/

    VDECDD_eEvent  eEvent;        /*!< The #VDECDD_eEvent event.                           */
    SYSBRG_POINTER(IMG_VOID, pvStrCbParam);     /*!< A pointer to client defined stream
                                       data defined in the call to VDECDD_StreamCreate().  */
	SYSBRG_POINTER(VDEC_sBufMapInfo, pvBufCbParam);    /*!< A pointer to client defined buffer
                                       data defined in the call to VDECDD_StreamMapBuf().  */
    union
    {
        VDEC_sDecPictInfo       sDecPictInfo;
        VDEC_sDecPictAuxInfo    sDecPictAuxInfo;
        SYSBRG_POINTER(IMG_VOID, pvTag);
        IMG_RESULT              ui32Result;
    };

} VDECDD_sCallBackInfo;


/*!
******************************************************************************
 This structure contains the map info.
 @brief  VDECDD Map Info
 ******************************************************************************/
typedef struct VDECDD_tag_sDdBufMapInfo  VDECDD_sDdBufMapInfo;  /*! VDECDD internal buffer map structure.  */


/*!
******************************************************************************
 This structure contains a front end stream unit.
 @brief   Front End Stream Unit
 ******************************************************************************/
typedef struct
{
    SYSBRG_POINTER(IMG_VOID, lst_padding);				//*!< Reserved space for LST_LINK link  (allows the structure to be part of a LST).*/                                      */

    VDECDD_eStrUnitType  eStrUnitType;                  /*!< Stream unit type.                                                                  */
    SYSBRG_HANDLE(hStrUnitHandle);                      /*!< Client handle for the stream unit.                                                 */
    IMG_UINT32           ui32ErrorFlags;                /*!< Flags word to indicate error in parsing/decoding - see #VDEC_eErrorType.           */
    IMG_UINT32           ui32WarningFlags;              /*!< Flags word to indicate warning in parsing/decoding - see #VDEC_eWarningType.       */
    IMG_UINT32           ui32CorrectionFlags;           /*!< Flags word to indicate correction in parsing/decoding - see #VDEC_eCorrectionType. */
    SYSBRG_LST(sBitStrSegList);             /*!< List of bitstream segments (#VDECDD_sBitStrSeg) containing bit stream data.        */
    SYSBRG_POINTER(IMG_VOID, pvDdData);                 /*!< Pointer to opaque unit data [DD use only].                                         */

    SYSBRG_POINTER(BSPP_sSequHdrInfo, psSequHdrInfo);   /*!< Sequence header information [VDECDD_STRUNIT_SEQUENCE_START only].                  */
    IMG_UINT32           ui32SeqHdrId;                  /*!< Sequence header identifier.                                                        */
    IMG_BOOL             bClosedGOP;                    /*!< Sequence header also marks start of closed GOP.                                    */

    SYSBRG_POINTER(BSPP_sPictHdrInfo, psPictHdrInfo);   /*!< Picture header information [VDECDD_STRUNIT_PICTURE_START only].                    */
    SYSBRG_POINTER(IMG_VOID, pvDdPictData);             /*!< Pointer to opaque picture data [VDECDD_STRUNIT_PICTURE_START & DD use only].       */
    IMG_BOOL             bLastPictInSeq;                /*!< Last picture in a sequence [VDECDD_STRUNIT_PICTURE_START only].                    */

    SYSBRG_POINTER(IMG_VOID, pvStrUnitTag);             /*!< Client data associated with this stream unit.                                      */

    IMG_BOOL             bDecode;                       /*!< Stream unit should be prepared for decode.                                         */
    IMG_UINT32           ui32Features;                  /*!< Features of the stream as defined by #VDECDD_eCoreFeatureFlags.                    */

} VDECDD_sStrUnit;


/*!
******************************************************************************
 This structure contains the Scheduler component stream status.
 @brief   Scheduler Component Stream Status
 ******************************************************************************/
typedef struct
{
    // Dynamic
    IMG_BOOL             bConfigured;                    /*!< Stream is currently configured.                                       */
    IMG_BOOL             bStopped;                       /*!< Stream is stopped and no more units will be submitted
                                                              for decoding until VDEC_StreamPlay().                                 */
    IMG_UINT32           ui32StopFlags;                  /*!< Indicates any specific reason for the stop.                           */
    VDECDD_eStrUnitType  eLastStrUnitType;               /*!< Last Stream unit scheduled on Decoder.                                */
    VDECDD_eStrUnitType  eNextStrUnitType;               /*!< Stream unit at head of queue.                                         */
    IMG_BOOL             bCanSchedule;                   /*!< Indicates whether the next unit can be scheduled when playing.
                                                              NOTE: reconfiguration may be required.                                */
    IMG_UINT32           ui32NumPict;                    /*!< Number of pictures ready for scheduling.                              */
    IMG_UINT32           ui32NumAvailImageBuffers;       /*!< Number of available image buffers.                                    */
    IMG_UINT32           ui32NumImageBuffers;            /*!< Number of mapped image buffers.                                       */
    IMG_UINT32           ui32NumAvailInternalResources;  /*!< Number of available internal resources.                               */
    IMG_UINT32           ui32NumInternalResources;       /*!< Number of internal resources mapped.                                  */

    VDEC_ePlayMode       ePlayMode;                      /*!< Play mode.                                                            */
    VDEC_eStopPoint      eCurrentStopPoint;              /*!< Current stop point for this stream.                                   */

    IMG_UINT32           ui32Avail;                      /*!< Last known resource availability (see #SCHEDULER_eAvailablility).     */
    IMG_UINT32           ui32Features;                   /*!< Features of the stream (last picture decoded) as defined
                                                              by #VDECDD_eCoreFeatureFlags.                                         */
    IMG_UINT32           ui32MinAvailLoad;               /*!< Min load value of available cores.                                    */
    IMG_UINT32           ui32MinLoad;                    /*!< Min load value of suitable (meets features) cores.                    */

    /* Cumulative */
    IMG_UINT32           ui32TotalPictScheduled;         /*!< Total pictures scheduled for decode.                                  */

} VDECDD_sSchStrStatus;


/*!
******************************************************************************
 This structure contains the Decoder decoding picture status.
 @brief   Decoder Decoding Picture Status
 ******************************************************************************/
typedef struct
{
    IMG_UINT32                  ui32TransactionId;      /*!< Transaction Id of picture.                                             */

    // State.
    VDECFW_eProgressCheckPoint  eFwCheckPoint;          /*!< Furthest check-point reached by picture in firmware.                   */
    VDECFW_eProgressCheckPoint  eFeHwCheckPoint;        /*!< Furthest check-point reached by picture in front-end hardware.         */
    VDECFW_eProgressCheckPoint  eBeHwCheckPoint;        /*!< Furthest check-point reached by picture in back-end hardware.          */

    IMG_UINT32                  ui32DMACStatus;         /*!< DMAC CNT on channel DMA_CHANNEL_SR1 (channel 2)                        */
    IMG_UINT32                  ui32FeMbX;              /*!< Last processed MB X in front-end hardware.                             */
    IMG_UINT32                  ui32FeMbY;              /*!< Last processed MB Y in front-end hardware.                             */
    IMG_UINT32                  ui32BeMbX;              /*!< Last processed MB X in back-end hardware.                              */
    IMG_UINT32                  ui32BeMbY;              /*!< Last processed MB Y in back-end hardware.                              */

    IMG_UINT8                   aui8FWControlMsg[VDECFW_MSGID_CONTROL_TYPES];           /*!< Last Control Message Processed.            */
    IMG_UINT8                   aui8FWDecodeMsg[VDECFW_MSGID_DECODE_TYPES];             /*!< Last Decode Message Processed.             */
    IMG_UINT8                   aui8FWCompletionMsg[VDECFW_MSGID_COMPLETION_TYPES];     /*!< Last Completion Message Processed.         */

    IMG_UINT8                   aui8HostControlMsg[VDECFW_MSGID_CONTROL_TYPES];           /*!< Last Control Message Processed.            */
    IMG_UINT8                   aui8HostDecodeMsg[VDECFW_MSGID_DECODE_TYPES];             /*!< Last Decode Message Processed.             */
    IMG_UINT8                   aui8HostCompletionMsg[VDECFW_MSGID_COMPLETION_TYPES];     /*!< Last Completion Message Processed.         */

} VDECDD_sDecPictStatus;

/*!
******************************************************************************
 This type defines the decoder core numbers.
 @brief Core Numbers
******************************************************************************/
typedef enum
{
    VDECDD_MSVDX_CORE_MASTER = 0,
    VDECDD_MSVDX_CORE_SLAVE1,
    VDECDD_MSVDX_CORE_SLAVE2,

    VDECDD_MSVDX_CORE_MAX,

} VDECDD_eCoreNum;
/*!
******************************************************************************
 This structure contains the Decoder decoding picture status.
 @brief  Core Status
 ******************************************************************************/
typedef struct {

    IMG_UINT32  ui32MTX_PC;                  /*!< MTX Program Counter            */
    IMG_UINT32  ui32MTX_PCX;                 /*!< MTX Program Counter X          */
    IMG_UINT32  ui32MTX_ENABLE;              /*!< MTX Enable Register            */
    IMG_UINT32  ui32MTX_STATUS_BITS;         /*!< MTX Status Register            */
    IMG_UINT32  ui32MTX_FAULT0;              /*!< MTX Fault0 Register            */
    IMG_UINT32  ui32MTX_A0StP;               /*!< MTX Stack Pointer              */
    IMG_UINT32  ui32MTX_A0FrP;               /*!< MTX Frame Pointer              */

    IMG_UINT32  ui32DMA_SETUP[3];            /*!< DMAC Setup Registers           */
    IMG_UINT32  ui32DMA_COUNT[3];            /*!< DMAC Count Registers           */
    IMG_UINT32  ui32DMA_PERIPHERAL_ADDR[3];  /*!< DMAC Peripheral addr Registers */

} VDECDD_sCoreStatus;

/*!
******************************************************************************
 This structure contains the Decoder component stream status.
 @brief   Decoder Component Stream Status
 ******************************************************************************/
typedef struct
{
    /* Dynamic */
    IMG_UINT32              ui32NumPictDecoding;                                  /*!< Number of pictures pending decode.                                    */
    VDECDD_sDecPictStatus   asDecPictStatus[VDECFW_MAX_NUM_PICTURES];             /*!< List of currently decoding pictures status'.                          */

    IMG_UINT32              ui32NumPictDecoded;                                   /*!< Number of pictures decoded and held for reference/display.            */
    IMG_UINT32              aui32DecodedPicts[VDECFW_MAX_NUM_PICTURES];           /*!< list of retained decoded pictures.                                    */

    IMG_UINT32              ui32Features;                                         /*!< Features of the stream (last picture decoded) as defined
                                                                                       by #VDECDD_eCoreFeatureFlags.                                         */
    IMG_UINT32              ui32MinAvailLoad;                                     /*!< Min load value of available cores.                                    */
    IMG_UINT32              ui32MinLoad;                                          /*!< Min load value of suitable (meets features) cores.                    */
    VDECDD_sCoreStatus      asCoreStatus[VDECDD_MSVDX_CORE_MAX];                  /*!< Status for each core on the device.                                   */

    // Next item in decoded list to be processed
    IMG_UINT32              ui32DisplayPics;                                      /*!< Number of pictures pending display (up to VDECFW_MAX_NUM_PICTURES).   */
    IMG_UINT32              ui32ReleasePics;                                      /*!< Number of pictures pending release (up to VDECFW_MAX_NUM_PICTURES).   */
    IMG_UINT32              aui32NextDisplayItems[VDECFW_MAX_NUM_PICTURES];       /*!< List of picture transactions pending display.                         */
    IMG_UINT32              aui32NextDisplayItemParent[VDECFW_MAX_NUM_PICTURES];  /*!< List of picture transactions that indicate the corresponding display. */
    IMG_UINT32              aui32NextReleaseItems[VDECFW_MAX_NUM_PICTURES];       /*!< List of picture transactions pending release.                         */
    IMG_UINT32              aui32NextReleaseItemParent[VDECFW_MAX_NUM_PICTURES];  /*!< List of picture transactions that indicate the corresponding release. */

    /* Cumulative */
    IMG_UINT32              ui32FieldsAsFrameDecodes;                             /*!< Total number of images host thought frames while field pair           */
    IMG_UINT32              ui32TotalPictDecoded;                                 /*!< Total number of pictures decoded on stream.                           */
    IMG_UINT32              ui32TotalPictDisplayed;                               /*!< Total number of pictures displayed on stream.                         */
    IMG_UINT32              ui32TotalPictFinished;                                /*!< Total number of pictures finished on stream
                                                                                       (decoded and no longer used for reference or display).                */

} VDECDD_sDecStrStatus;


/*!
******************************************************************************
 This structure contains the Device Driver Stream Status.
 @brief   Device Driver Stream Status
 ******************************************************************************/
typedef struct
{
    VDECDD_sSchStrStatus  sSchStatus;  /*!< Scheduler stream status.  */
    VDECDD_sDecStrStatus  sDecStatus;  /*!< Decoder stream status.    */

} VDECDD_sStrStatus;






/*!
******************************************************************************

 @Function              VDECDD_IsSupportedFeature

 @Description

 This function reports whether the feature is supported by the driver.

 @Input    ui32ConnId  : The connection Id.

 @Input    eFeature    : Feature to support.

 @Output   pbSupported : Pointer to feature supported flag.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_IsSupportedFeature(
    IMG_UINT32         ui32ConnId,
    VDEC_eFeature      eFeature,
    SYSBRG_POINTER_ARG(IMG_BOOL)    pbSupported
);

/*!
******************************************************************************

 @Function              VDECDD_SupportedFeatures

 @Description

 This function reports the features being supported.

 @Input    ui32ConnId  : The connection Id.

 @Input    psFeature    : Feature supported.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_SupportedFeatures(
    IMG_UINT32         ui32ConnId,
    SYSBRG_POINTER_ARG(VDEC_sFeatures)  psFeature
);

/*!
******************************************************************************

 @Function              VDECDD_StreamCreate

 @Description

 This function is used to create a stream.

 @Input    psStrConfigData : A pointer to a #VDEC_sStrConfigData structure.

 @Input    pvStrCbParam    : A pointer to client defined stream data or IMG_NULL.

 @Output   pui32StrId      : A pointer used to return the stream id.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamCreate(
    SYSBRG_POINTER_ARG(VDEC_sStrConfigData) psStrConfigData,  
    SYSBRG_POINTER_ARG(IMG_VOID)            pvStrCbParam,
    SYSBRG_POINTER_ARG(IMG_UINT32)          pui32StrId
);



/*!
******************************************************************************

 @Function              VDECDD_StreamDestroy

 @Description

 This function is used to destroy a stream.

 NOTE: Should only be called when VDECDD is in the "stopped" state.

 @Input    ui32StrId : The stream Id.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamDestroy(
    IMG_UINT32  ui32StrId
);


/*!
******************************************************************************

 @Function              VDECDD_GetCallbackEvent

 @Description

 This function is used to wait for the next callback event.

 @Input    ui32StrId      : The stream Id.

 @Input    psCallBackInfo : A pointer used to return the callback
                            info #VDECDD_sCallBackInfo.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_GetCallbackEvent(
    IMG_UINT32                     ui32StrId,
    SYSBRG_POINTER_ARG(VDECDD_sCallBackInfo)    psCallBackInfo
);


/*!
******************************************************************************

 @Function              VDECDD_PreemptCallbackEvent

 @Description

 This function is used to preempt a pending VDECDD_GetCallbackEvent() call
 and cause the function to return with no data.

 @Input    ui32StrId : The stream Id.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_PreemptCallbackEvent(
    IMG_UINT32  ui32StrId
);


/*!
******************************************************************************

 @Function              VDECDD_StreamPlay

 @Description

 This function is used to start playing.

 @Input    ui32StrId         : The stream id.

 @Input    ePlayMode         : Sets the "play" mode.

 @Input    eStopPoint        : Sets the decode stop point.

 @Input    ui32StopPointQual : Use to qualify the stop point.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamPlay(
    IMG_UINT32       ui32StrId,
    VDEC_ePlayMode   ePlayMode,
    VDEC_eStopPoint  eStopPoint,
    IMG_UINT32       ui32StopPointQual
);


/*!
******************************************************************************

 @Function              VDECDD_StreamStop

 @Description

 This function is used to stop and allows any in-flight data to flow through
 the system and be decoded.

 A #VDEC_EVENT_STREAM_STOPPED event is used to signal when the decoding has
 stopped.

 eStopPoint set the point to stop.

 @Input    ui32StrId         : The stream Id.

 @Input    eStopPoint        : Sets the decode stop point.

 @Input    ui32StopPointQual : Use to qualify the stop point.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamStop(
    IMG_UINT32       ui32StrId,
    VDEC_eStopPoint  eStopPoint,
    IMG_UINT32       ui32StopPointQual
);


/*!
******************************************************************************

 @Function              VDECDD_StreamGetStopInfo

 @Description

 This function is used to obtained the stopped status flags.

 @Input    ui32StrId  : The stream Id.

 @Output   psStopInfo : A pointer used to return the stopped status flags
                        as defined in #VDEC_eStopFlags plus additional info.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamGetStopInfo(
    IMG_UINT32               ui32StrId,
    SYSBRG_POINTER_ARG(VDEC_sStopInfo)  psStopInfo
);


/*!
******************************************************************************

 @Function              VDECDD_StreamGetSequHdrInfo

 @Description

 This function is used to obtained the sequence header information.

 @Input    ui32StrId        : The stream Id.

 @Output   psComSequHdrInfo : A pointer used to return the sequence header
                              info as defined in #VDEC_sComSequHdrInfo.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamGetSequHdrInfo(
    IMG_UINT32                     ui32StrId,
    SYSBRG_POINTER_ARG(VDEC_sComSequHdrInfo)    psComSequHdrInfo
);


/*!
******************************************************************************

 @Function              VDECDD_StreamMapBuf

 @Description

 This function is used to map a buffer into the device MMU.

 NOTE: The buffer must have been allocated in a way that allows th memory to
 be mapped in the devices MMU.

 @Input     ui32StrId     : The stream id.

 @Input     pvBufCbParam  : A pointer to client defined buffer data or IMG_NULL.

 @Input     eBufType      : Type of buffer to be mapped.

 @Input     psBufInfo     : A pointer to a #VDEC_sBufInfo structure
                            containing the buffer information.

 @Output    pui32BufMapId : A pointer used to return the buffer mapping id.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamMapBuf(
    IMG_UINT32                          ui32StrId,
    SYSBRG_POINTER_ARG(IMG_VOID)        pvBufCbParam,
    VDEC_eBufType                       eBufType,
    SYSBRG_POINTER_ARG(VDEC_sBufInfo)   psBufInfo,
    SYSBRG_POINTER_ARG(IMG_UINT32)      pui32BufMapId
);


/*!
******************************************************************************

 @Function              VDECDD_StreamUnmapBuf

 @Description

 This function is used to unmap a buffer from the device MMU.

 NOTE: The buffers should not be unmapped of the buffers is currently "held"
 by VDECDD as an bit stream buffer being decoded or as a picture buffer queued
 for decoding into or as a reference frame.

 @Input    ui32BufMapId : The buffer mapping id.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamUnmapBuf(
    IMG_UINT32  ui32BufMapId
);


/*!
******************************************************************************

 @Function              VDECDD_StreamSetOutputConfig

 @Description

 This function is used to set the output configuration.

 @Input    ui32StrId         : The stream id.

 @Input    psStrOutputConfig : A pointer to a #VDEC_sStrOutputConfig
                               structure containing the changes to the
                               output configuration.

 @Input    psPictBufConfig   : A pointer to picture buffer configuration.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamSetOutputConfig(
    IMG_UINT32                     ui32StrId,
    SYSBRG_POINTER_ARG(VDEC_sStrOutputConfig)   psStrOutputConfig,
    SYSBRG_POINTER_ARG(VDEC_sPictBufConfig)     psPictBufConfig
);


/*!
******************************************************************************

 @Function              VDECDD_StreamFillPictBuf

 @Description

 This function is used to submit or return a picture buffer to allow it to
 be re-used.

 @Input    ui32BufMapId : The mapping id.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamFillPictBuf(
    IMG_UINT32  ui32BufMapId
);


/*!
******************************************************************************

 @Function                VDECDD_StreamFlush

 @Description

 This function flushes all decoded pictures (inc. references) for the stream and
 returns any outstanding display images via event #VDEC_EVENT_PICTBUF_FULL.

 NOTE: Should only be called when VDECDD is in the "stopped" state.

 @Input    ui32StrId    : The stream id.

 @Input    bDiscardRefs : Indicates that references should be dropped.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamFlush(
    IMG_UINT32  ui32StrId,
    IMG_BOOL    bDiscardRefs
);


/*!
******************************************************************************

 @Function              VDECDD_StreamReleaseBufs

 @Description

 This function is used to release any reference to buffers held by VDEC.
 Once called the client is free to discard or re-use the released buffers.

 NOTE: Should only be called when VDECDD is in the "stopped" state.

 @Input    ui32StrId : The stream id.

 @Input    eBufType  : Indicates the type of buffers to be returned/released.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamReleaseBufs(
    IMG_UINT32     ui32StrId,
    VDEC_eBufType  eBufType
);


/*!
******************************************************************************

 @Function              VDECDD_StreamSetBehaviourOnErrors

 @Description

 This function allows for defining how VDEC behaves on stream processing errors.

 @Input    ui32StrId      : The stream Id.

 @Input    eErrorHandling : Defines how to behave on errors.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamSetBehaviourOnErrors(
    IMG_UINT32           ui32StrId,
    VDEC_eErrorHandling  eErrorHandling
);


/*!
******************************************************************************

 @Function                VDECDD_StreamGetStatus

 @Description

 This function is used to obtain the device driver stream status.

 @Input    ui32StrId   : The stream id.

 @Output   psStrStatus : Pointer to device driver stream status structure.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT VDECDD_StreamGetStatus(
    IMG_UINT32                  ui32StrId,
    SYSBRG_POINTER_ARG(VDECDD_sStrStatus)   psStrStatus
);

/*!
******************************************************************************

 @Function                VDECDD_StreamSubmitUnit

******************************************************************************/
extern IMG_RESULT VDECDD_StreamSubmitUnit(
    IMG_UINT32                  ui32StrId,
    SYSBRG_POINTER_ARG(VDECDD_sStrUnit) psStrUnit
);

#if defined(__cplusplus)
}
#endif

#endif /* __VDECDD_H__    */

