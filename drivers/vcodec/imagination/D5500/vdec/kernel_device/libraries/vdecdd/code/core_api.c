/*!
 *****************************************************************************
 *
 * @File       core_api.c
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

#include "vdec_api.h"
#include "core_api.h"
#include "rman_api.h"
#include "page_alloc_km.h"
#include "dman_api_km.h"
#include "vdec_int.h"
#include "vdecdd_utils.h"
#include "talmmu_api.h"
#include "plant.h"
#include "scheduler.h"
#include "decoder.h"
#include "vdecdd_int.h"
#include "vdecdd_mmu.h"
#include "lst.h"
#include "report_api.h"
#include "dbgopt_api_km.h"

#ifdef SYSBRG_BRIDGING
    #include "bspp_km.h"
#endif

#define CORE_NO_STREAM_ID   0
#define INIT_HM_MSG_LIST_SIZE 64

/*!
******************************************************************************
 This type defines the core message Ids.
 @brief  Core Message Ids
******************************************************************************/
typedef enum
{
    CORE_MSGID_INVALID = 0,                     /*!< Invalid message id.                     */
    CORE_MSGID_CONNECTION_CREATE,               /*!< see CORE_ConnectionCreate().            */
    CORE_MSGID_CONNECTION_DESTROY,              /*!< see CORE_ConnectionDestroy().           */
    CORE_MSGID_STREAM_CREATE,                   /*!< see CORE_StreamCreate().                */
    CORE_MSGID_STREAM_DESTROY,                  /*!< see CORE_StreamDestroy().               */
    CORE_MSGID_STREAM_PLAY,                     /*!< see CORE_StreamPlay().                  */
    CORE_MSGID_STREAM_STOP,                     /*!< see CORE_StreamStop().                  */
    CORE_MSGID_STREAM_GET_STOP_FLAGS,           /*!< see CORE_StreamGetStopFlags().          */
    CORE_MSGID_STREAM_MAP_BUF,                  /*!< see CORE_StreamMapBuf().                */
    CORE_MSGID_STREAM_UNMAP_BUF,                /*!< see CORE_StreamUnmapBuf().              */
    CORE_MSGID_STREAM_SUBMIT_UNIT,              /*!< see CORE_StreamSubmitUnit().            */
    CORE_MSGID_STREAM_SET_OUTPUT_CONFIG,        /*!< see CORE_StreamSetOutputConfig().       */
    CORE_MSGID_STREAM_FILL_PICT_BUF,            /*!< see CORE_StreamFillPictBuf().           */
    CORE_MSGID_STREAM_FLUSH,                    /*!< see CORE_StreamFlush().                 */
    CORE_MSGID_STREAM_RELEASE_BUFS,             /*!< see CORE_StreamReleaseBufs().           */
    CORE_MSGID_STREAM_SET_BEHAVIOUR_ON_ERRORS,  /*!< see CORE_StreamGetStatus().             */
    CORE_MSGID_STREAM_GET_STATUS,               /*!< see CORE_StreamGetStatus().             */
    CORE_MSGID_DEV_SCHEDULE,                    /*!< see CORE_DevSchedule().                 */
    CORE_MSGID_DEV_HW_INTERRUPT,                /*!< see CORE_DevHwInterrupt().              */
    CORE_MSGID_DEV_POWER_PRE_S5,                /*!< see CORE_DevPowerPreS5().               */
    CORE_MSGID_DEV_POWER_POST_S0,               /*!< see CORE_DevPowerPostS0().              */
    CORE_MSGID_DEV_SW_INTERRUPT,                /*!< see CORE_DevSwInterrupt().              */
    CORE_MSGID_DEV_SERVICE_TIME_EXPIRY,         /*!< see CORE_DevServiceTimeExpiry().        */
    CORE_MSGID_DEV_RESET,                       /*!< see CORE_DevReset().                    */
    CORE_MSGID_DEV_REPLAY,                      /*!< see CORE_DevServiceTimeExpiry().        */
    CORE_MSGID_DEV_SW_INTERRUPT_PIC_DISCARDED,  /*!< see CORE_DevSwInterruptPicDiscarded().  */

    CORE_MSGID_MAX,                             /*!< Max. message id.                        */

} CORE_eMsgId;


/*!
******************************************************************************
 This structure contains CORE_ConnectionCreate() message.
 @brief  CORE_ConnectionCreate() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/

    /* Outputs...*/
    VDECDD_sDdConnContext    ** ppsDdConnContext;    /* Connection context (managed by caller).    */

} CORE_sCreateConnectionMsg;


/*!
******************************************************************************
 This structure contains CORE_ConnectionDestroy() message.
 @brief  CORE_ConnectionDestroy() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_UINT32                  ui32ConnId;        /* Connection ID.     */

    /* Outputs...*/

} CORE_sDestroyConnectionMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamCreate() message.
 @brief  CORE_StreamCreate() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_UINT32               ui32ConnId;       /*!< Connection ID.                       */
    VDEC_sStrConfigData      sStrConfigData;   /*!< Config data.                         */
    IMG_VOID *               pvStrCbParam;     /*!< Callback client defined stream data  */

    /* Outputs...*/
    IMG_UINT32             * pui32StrId;       /*!< Stream id.                           */

} CORE_sStreamCreateMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamDestroy() message.
 @brief  CORE_StreamDestroy() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_HANDLE              hDestroyedEvent;    /* Object to signal destroyed event. */

    /* Outputs...*/
    IMG_UINT32            * pui32ConnId;        /* Connection ID.     */

} CORE_sStreamDestroyMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamPlay() message.
 @brief  CORE_StreamPlay() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    VDEC_ePlayMode          ePlayMode;          /*!< Play mode.             */
    VDEC_eStopPoint         eStopPoint;         /*!< Stop point.            */
    IMG_UINT32              ui32StopPointQual;  /*!< Stop point qualifier.  */

    /* Outputs...*/

} CORE_sStreamPlayMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamStop() message.
 @brief  CORE_StreamStop() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    VDEC_eStopPoint         eStopPoint;         /*!< Stop point.            */
    IMG_UINT32              ui32StopPointQual;  /*!< Stop point qualifier.  */

    /* Outputs...*/

} CORE_sStreamStopMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamGetStopFlags() message.
 @brief  CORE_StreamGetStopFlags() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_UINT32  ui32TBD;    /*!< x*/

    /* Outputs...*/

} CORE_sStreamGetStopFlagsMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamMapBuf() message.
 @brief  CORE_StreamMapBuf() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_VOID *              pvBufCbParam;    /*!< A pointer to client specific data.  */
    VDEC_eBufType           eBufType;        /*!< Buffer type.                        */
    VDEC_sBufInfo           sBufInfo;        /*!< Buffer info.                        */

    /* Outputs...*/
    IMG_UINT32            * pui32BufMapId;    /*!< Buffer map id.                      */

} CORE_sStreamMapBufMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamUnmapBuf() message.
 @brief  CORE_StreamUnmapBuf() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_UINT32              ui32BufMapId;  /*!< Buffer map ID.            */

    /* Outputs...*/

} CORE_sStreamUnmapBufMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamSubmitUnit() message.
 @brief  CORE_StreamSubmitUnit() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    VDECDD_sStrUnit      * psStrUnit;       /*!< Stream unit.     */

    /* Outputs...*/

} CORE_sStreamSubmitUnitMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamSetOutputConfig() message.
 @brief  CORE_StreamSetOutputConfig() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    VDEC_sStrOutputConfig *  psStrOutputConfig;  /*!< Stream output configuration.  */
    VDEC_sPictBufConfig   *  psPictBufConfig;    /*!< Picture buffer configuration.         */

    /* Outputs...*/

} CORE_sStreamSetOutputConfigMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamFillPictBuf() message.
 @brief  CORE_StreamFillPictBuf() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_UINT32              ui32BufMapId;  /*!< Buffer map ID.            */

    /* Outputs...*/

} CORE_sStreamFillPictBufMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamFlush() message.
 @brief  CORE_StreamFlush() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_BOOL               bDiscardRefs;        /*!< Discard reference pictures.    */

    /* Outputs...*/

} CORE_sStreamFlushMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamReleaseBufs() message.
 @brief  CORE_StreamReleaseBufs() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    VDEC_eBufType           eBufType;           /*!< Buffer type to release.    */

    /* Outputs...*/

} CORE_sStreamReleaseBufsMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamSetBehaviourOnErrors() message.
 @brief  CORE_StreamSetBehaviourOnErrors() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    VDEC_eErrorHandling     eErrorHandling;     /*!< Error handling approach.   */

    /* Outputs...*/

} CORE_sStreamSetBehaviourOnErrorsMsg;


/*!
******************************************************************************
 This structure contains CORE_StreamGetStatus() message.
 @brief  CORE_StreamGetStatus() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    VDECDD_sStrStatus *     psStrStatus;        /*!< Stream status to populate. */

    /* Outputs...*/

} CORE_sStreamGetStatusMsg;


/*!
******************************************************************************
 This structure contains CORE_DevSchedule() message.
 @brief  CORE_DevSchedule() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_UINT32  ui32TBD;    /*!< x*/

    /* Outputs...*/

} CORE_sDevScheduleMsg;


/*!
******************************************************************************
 This structure contains CORE_DevHwInterrupt() message.
 @brief  CORE_DevHwInterrupt() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_HANDLE              hDecServiceInt;     /* Decoder interrupt servicing handle.  */

    /* Outputs...*/

} CORE_sDevHwInterruptMsg;


/*!
******************************************************************************
 This structure contains CORE_DevSwInterrupt() message.
 @brief  CORE_DevSwInterrupt() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_HANDLE              hDecServiceInt;     /* Decoder interrupt servicing handle.  */

    /* Outputs...*/

} CORE_sDevSwInterruptMsg;


/*!
******************************************************************************
 This structure contains CORE_DevSwInterruptPicDiscarded() message.
 @brief  CORE_DevSwInterruptPicDiscarded() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_HANDLE              hDecServiceInt;     /* Decoder interrupt servicing handle.  */

    /* Outputs...*/

} CORE_sDevSwInterruptPicDiscardedMsg;

/*!
******************************************************************************
 This structure contains CORE_DevServiceTimeExpiry() message.
 @brief  CORE_DevServiceTimeExpiry() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_UINT32              ui32CoreNum;

    /* Outputs...*/

} CORE_sDevServiceTimeExpiryMsg;

/*!
******************************************************************************
 This structure contains CORE_DevReset() message.
 @brief  CORE_DevReset() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    VDECDD_eResetReason     eReason;
    IMG_UINT32              ui32CoreNum;

    /* Outputs...*/

} CORE_sDevReset;

/*!
******************************************************************************
 This structure contains CORE_DevReplay() message.
 @brief  CORE_DevReplay() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_UINT32              ui32CoreNum;

    /* Outputs...*/

} CORE_sDevReplayMsg;


/*!
******************************************************************************
 This structure contains CORE_DevPowerPreS5() message.
 @brief  CORE_DevPowerPreS5() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_UINT32  ui32TBD;    /*!< x*/

    /* Outputs...*/

} CORE_sDevPowerPreS5Msg;


/*!
******************************************************************************
 This structure contains CORE_DevPowerPostS0() message.
 @brief  CORE_DevPowerPostS0() Message
******************************************************************************/
typedef struct
{
    /* Inputs...*/
    IMG_UINT32  ui32TBD;    /*!< x*/

    /* Outputs...*/

} CORE_sDevPowerPostS0Msg;


/*!
******************************************************************************
 This structure contains the event message information.
 @brief  Event Message Information
******************************************************************************/
typedef struct
{
    LST_LINK;            /*!< List link (allows the structure to be part of a MeOS list).*/

    CORE_eMsgId             eMsgId;             /*!< Message id.                                    */
    IMG_HANDLE              hEventHandle;       /*!< Event object for synchronous message.          */
    IMG_UINT32              ui32Result;         /*!< Result if message is handled synchronously     */
    IMG_UINT32              ui32StrId;          /*!< Stream context.                                */

    union
    {
        CORE_sCreateConnectionMsg            sCreateConnectionMsg;            /*!< CORE_ConnectionCreate() message.            */
        CORE_sDestroyConnectionMsg           sDestroyConnectionMsg;           /*!< CORE_ConnectionDestroy() message.           */
        CORE_sStreamCreateMsg                sStreamCreateMsg;                /*!< CORE_StreamCreate() message.                */
        CORE_sStreamDestroyMsg               sStreamDestroyMsg;               /*!< CORE_StreamDestroy() message.               */
        CORE_sStreamPlayMsg                  sStreamPlayMsg;                  /*!< CORE_StreamPlay() message.                  */
        CORE_sStreamStopMsg                  sStreamStopMsg;                  /*!< CORE_StreamStop() message.                  */
        CORE_sStreamGetStopFlagsMsg          sStreamGetStopFlagsMsg;          /*!< CORE_StreamGetStopFlags() message.          */
        CORE_sStreamMapBufMsg                sStreamMapBufMsg;                /*!< CORE_StreamMapBuf() message.                */
        CORE_sStreamUnmapBufMsg              sStreamUnmapBufMsg;              /*!< CORE_StreamUnmapBuf() message.              */
        CORE_sStreamSubmitUnitMsg            sStreamSubmitUnitMsg;            /*!< CORE_StreamSubmitUnit() message.            */
        CORE_sStreamSetOutputConfigMsg       sStreamSetOutputConfigMsg;       /*!< CORE_StreamSetOutputConfig() message.       */
        CORE_sStreamFillPictBufMsg           sStreamFillPictBufMsg;           /*!< CORE_StreamFillPictBuf() message.           */
        CORE_sStreamFlushMsg                 sStreamFlushMsg;                 /*!< CORE_StreamFlush() message.                 */
        CORE_sStreamReleaseBufsMsg           sStreamReleaseBufsMsg;           /*!< CORE_StreamReleaseBufs() message.           */
        CORE_sStreamSetBehaviourOnErrorsMsg  sStreamSetBehaviourOnErrorsMsg;  /*!< CORE_StreamSetBehaviourOnErrors() message.  */
        CORE_sStreamGetStatusMsg             sStreamGetStatusMsg;             /*!< CORE_StreamGetStatus() message.             */
        CORE_sDevScheduleMsg                 sDevScheduleMsg;                 /*!< CORE_DevSchedule() message.                 */
        CORE_sDevHwInterruptMsg              sDevHwInterruptMsg;              /*!< CORE_DevHwInterrupt() message.              */
        CORE_sDevPowerPreS5Msg               sDevPowerPreS5Msg;               /*!< CORE_DevPowerPreS5() message.               */
        CORE_sDevPowerPostS0Msg              sDevPowerPostS0Msg;              /*!< CORE_DevPowerPostS0() message.              */
        CORE_sDevSwInterruptMsg              sDevSwInterruptMsg;              /*!< CORE_DevSwInterrupt() message.              */
        CORE_sDevServiceTimeExpiryMsg        sDevServiceTimeExpiryMsg;        /*!< CORE_DevSericeTimeExpiry() message.         */
        CORE_sDevReset                       sDevReset;                       /*!< CORE_DevReset() message.                    */
        CORE_sDevReplayMsg                   sDevReplayMsg;                   /*!< CORE_DevReplay() message.                   */
        CORE_sDevSwInterruptPicDiscardedMsg  sDevSwInterruptPicDiscardedMsg;  /*!< CORE_DevSwInterruptPicDiscarded() message.  */
    };

} CORE_sCoreMsg;


static IMG_RESULT core_StreamStop(
    VDECDD_sDdStrContext *  psDdStrContext,
    VDEC_eStopPoint         eStopPoint,
    IMG_UINT32              ui32StopPointQual,
    IMG_UINT32              ui32Error
);

#ifdef __RELEASE_RELEASE__
static IMG_BOOL bDevConfigLogged = IMG_FALSE;
#endif

/*!
******************************************************************************
 This array defines names of the VDEC standards.
 Shall be in sync with #VDEC_eVidStd
 @brief  Names of the VDEC standards
******************************************************************************/
static char* gapszVideoStandard[VDEC_STD_MAX] =
{
    "VDEC_STD_UNDEFINED",
    "VDEC_STD_MPEG2",
    "VDEC_STD_MPEG4",
    "VDEC_STD_H263",
    "VDEC_STD_H264",
    "VDEC_STD_VC1",
    "VDEC_STD_AVS",
    "VDEC_STD_REAL",
    "VDEC_STD_JPEG",
    "VDEC_STD_VP6",
    "VDEC_STD_VP8",
    "VDEC_STD_SORENSON",
    "VDEC_STD_HEVC"
};


/*!
******************************************************************************
 @Function              status_open_callback
 Callback for writing information in the stream status debug file
******************************************************************************/
static void status_open_callback(void *data, debug_printf_t p_printf, void *print_data)
{
    VDECDD_sStrStatus *psStrStatus;
    VDECDD_sDdStrContext *psDdStrContext = data;
    unsigned result, i;

    /* VDECDD_sStrStatus is quite a big structure */
    VDEC_MALLOC(psStrStatus);
    if (!psStrStatus) {
        p_printf(print_data, "Cannot allocate VDECDD_sStrStatus (%zu bytes)\n",
                 sizeof(*psStrStatus));
        goto errStatAlloc;
    }

    /* Ask status to the core */
    result = CORE_StreamGetStatus(psDdStrContext->ui32StrId, psStrStatus);
    IMG_ASSERT(result == IMG_SUCCESS);
    if (result != IMG_SUCCESS)
    {
        p_printf(print_data, "Cannot print status. Context %p\n", psDdStrContext);
        goto errGetStatus;
    }


    p_printf(print_data, "===================\n");
    p_printf(print_data, "-------------------\n");

    p_printf(print_data, "User stream id: 0x%08X\n",
             psDdStrContext->sStrConfigData.ui32UserStrId);
    p_printf(print_data, "Low latency?: %s\n",
             psDdStrContext->sStrConfigData.bLowLatencyMode == IMG_TRUE ? "Yes" :"No");
    p_printf(print_data, "Secure?: %s\n",
             psDdStrContext->sStrConfigData.bSecureStream == IMG_TRUE ? "Yes" :"No");

    p_printf(print_data, "=========\n");
    p_printf(print_data, "---------\n");

    p_printf(print_data, "Mode: %d\n", psStrStatus->sSchStatus.ePlayMode);

    p_printf(print_data, "Stop Point: %d\n", psStrStatus->sSchStatus.eCurrentStopPoint);

    p_printf(print_data, "Configured?: %s\n",
             psStrStatus->sSchStatus.bConfigured == IMG_TRUE ? "Yes" : "No");

    p_printf(print_data, "Stopped?: %s, flags: 0x%08X\t\n",
             psStrStatus->sSchStatus.bStopped == IMG_TRUE ? "Yes" : "No",
             psStrStatus->sSchStatus.ui32StopFlags);

    p_printf(print_data, "Last Stream Unit: %d\n",
             psStrStatus->sSchStatus.eLastStrUnitType);

    if (psStrStatus->sSchStatus.eNextStrUnitType < VDECDD_STRUNIT_MAX) {
        p_printf(print_data, "Next Stream Unit: %d\n",
                 psStrStatus->sSchStatus.eNextStrUnitType);
    }

    p_printf(print_data, "Can schedule?: %s\n",
             psStrStatus->sSchStatus.bCanSchedule == IMG_TRUE ? "Yes" : "No");
    p_printf(print_data, "Resource Availability: 0x%08X\n",
             psStrStatus->sSchStatus.ui32Avail);
    p_printf(print_data, "Features (head of stream unit queue): 0x%08X\n",
            psStrStatus->sSchStatus.ui32Features);
    p_printf(print_data, "Load(avail/min): %d/%u\n",
             psStrStatus->sSchStatus.ui32MinAvailLoad,
             psStrStatus->sSchStatus.ui32MinLoad);

    p_printf(print_data, "Image Buffers: %u/%u\n",
             psStrStatus->sSchStatus.ui32NumAvailImageBuffers,
             psStrStatus->sSchStatus.ui32NumImageBuffers);
    p_printf(print_data, "Internal Resources: %u/%u\n",
             psStrStatus->sSchStatus.ui32NumAvailInternalResources,
             psStrStatus->sSchStatus.ui32NumInternalResources);

    p_printf(print_data, "Pictures: %u\n", psStrStatus->sSchStatus.ui32NumPict);
    p_printf(print_data, "Total pictures scheduled: %u\n",
             psStrStatus->sSchStatus.ui32TotalPictScheduled);

    p_printf(print_data, "=======\n");
    p_printf(print_data, "DECODER\n");
    p_printf(print_data, "-------\n");

    p_printf(print_data, "Pictures decoding: %u\n",
             psStrStatus->sDecStatus.ui32NumPictDecoding);
    for (i = 0; i < psStrStatus->sDecStatus.ui32NumPictDecoding; i++)
    {
        p_printf(print_data, "\t(%u) 0x%08X [FW:%+d | FEHW:%+d (%+4d,%+4d) | "
                 "BEHW:%+d (%+4d,%+4d)] [DMAC COUNT DMA_CHANNEL_SR1 (% 9d)]\n",
                 i,
                 psStrStatus->sDecStatus.asDecPictStatus[i].ui32TransactionId,
                 psStrStatus->sDecStatus.asDecPictStatus[i].eFwCheckPoint,
                 psStrStatus->sDecStatus.asDecPictStatus[i].eFeHwCheckPoint,
                 psStrStatus->sDecStatus.asDecPictStatus[i].ui32FeMbX,
                 psStrStatus->sDecStatus.asDecPictStatus[i].ui32FeMbY,
                 psStrStatus->sDecStatus.asDecPictStatus[i].eBeHwCheckPoint,
                 psStrStatus->sDecStatus.asDecPictStatus[i].ui32BeMbX,
                 psStrStatus->sDecStatus.asDecPictStatus[i].ui32BeMbY,
                 psStrStatus->sDecStatus.asDecPictStatus[i].ui32DMACStatus);
    }

    p_printf(print_data, "Pictures decoded : %u\n",
             psStrStatus->sDecStatus.ui32NumPictDecoded);
    for (i = 0; i < psStrStatus->sDecStatus.ui32NumPictDecoded; i++)
    {
        p_printf(print_data, "\t(%u) 0x%08X\n", i,
                 psStrStatus->sDecStatus.aui32DecodedPicts[i]);
    }

    p_printf(print_data, "Last Messages Processed:\n");
    p_printf(print_data, "\t[CONTROL    - FIRMWARE_INIT         = FW:0x%02X HOST:0x%02X]\n",
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8FWControlMsg[VDECFW_MSGID_FIRMWARE_INIT-VDECFW_MSGID_BASE_PADDING],
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8HostControlMsg[VDECFW_MSGID_FIRMWARE_INIT-VDECFW_MSGID_BASE_PADDING]);
    p_printf(print_data, "\t[CONTROL    - FIRMWARE_CONFIG       = FW:0x%02X HOST:0x%02X]\n",
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8FWControlMsg[VDECFW_MSGID_FIRMWARE_CONFIG-VDECFW_MSGID_BASE_PADDING],
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8HostControlMsg[VDECFW_MSGID_FIRMWARE_CONFIG-VDECFW_MSGID_BASE_PADDING]);
    p_printf(print_data, "\t[CONTROL    - FIRMWARE_CONTROL      = FW:0x%02X HOST:0x%02X]\n",
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8FWControlMsg[VDECFW_MSGID_FIRMWARE_CONTROL-VDECFW_MSGID_BASE_PADDING],
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8HostControlMsg[VDECFW_MSGID_FIRMWARE_CONTROL-VDECFW_MSGID_BASE_PADDING]);

    p_printf(print_data, "\t[DECODE     - DECODE_PICTURE        = FW:0x%02X HOST:0x%02X]\n",
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8FWDecodeMsg[VDECFW_MSGID_DECODE_PICTURE-VDECFW_MSGID_PSR_PADDING],
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8HostDecodeMsg[VDECFW_MSGID_DECODE_PICTURE-VDECFW_MSGID_PSR_PADDING]);
    p_printf(print_data, "\t[DECODE     - BITSTREAM_BUFFER      = FW:0x%02X HOST:0x%02X]\n",
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8FWDecodeMsg[VDECFW_MSGID_BITSTREAM_BUFFER-VDECFW_MSGID_PSR_PADDING],
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8HostDecodeMsg[VDECFW_MSGID_BITSTREAM_BUFFER-VDECFW_MSGID_PSR_PADDING]);
    p_printf(print_data, "\t[DECODE     - FENCE                 = FW:0x%02X HOST:0x%02X]\n",
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8FWDecodeMsg[VDECFW_MSGID_FENCE-VDECFW_MSGID_PSR_PADDING],
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8HostDecodeMsg[VDECFW_MSGID_FENCE-VDECFW_MSGID_PSR_PADDING]);
    p_printf(print_data, "\t[DECODE     - BATCH                 = FW:0x%02X HOST:0x%02X]\n",
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8FWDecodeMsg[VDECFW_MSGID_BATCH-VDECFW_MSGID_PSR_PADDING],
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8HostDecodeMsg[VDECFW_MSGID_BATCH-VDECFW_MSGID_PSR_PADDING]);

    p_printf(print_data, "\t[COMPLETION - PIC_DECODED           = FW:0x%02X HOST:0x%02X]\n",
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8FWCompletionMsg[VDECFW_MSGID_PIC_CRCS-VDECFW_MSGID_BE_PADDING],
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8HostCompletionMsg[VDECFW_MSGID_PIC_CRCS-VDECFW_MSGID_BE_PADDING]);
    p_printf(print_data, "\t[COMPLETION - PIC_CRCS              = FW:0x%02X HOST:0x%02X]\n",
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8FWCompletionMsg[VDECFW_MSGID_PIC_DECODED-VDECFW_MSGID_BE_PADDING],
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8HostCompletionMsg[VDECFW_MSGID_PIC_DECODED-VDECFW_MSGID_BE_PADDING]);
    p_printf(print_data, "\t[COMPLETION - PIC_PERFORMANCE       = FW:0x%02X HOST:0x%02X]\n",
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8FWCompletionMsg[VDECFW_MSGID_PIC_PERFORMANCE-VDECFW_MSGID_BE_PADDING],
        psStrStatus->sDecStatus.asDecPictStatus[0].aui8HostCompletionMsg[VDECFW_MSGID_PIC_PERFORMANCE-VDECFW_MSGID_BE_PADDING]);

    p_printf(print_data, "Next DISPLAY:\n");
    for (i = 0; i < psStrStatus->sDecStatus.ui32DisplayPics; i++)
    {
        p_printf(print_data, "\t(%u) 0x%08X [0x%08X]\n", i,
                 psStrStatus->sDecStatus.aui32NextDisplayItems[i],
                 psStrStatus->sDecStatus.aui32NextDisplayItemParent[i]);
    }

    p_printf(print_data, "Next RELEASE:\n");
    for (i = 0; i < psStrStatus->sDecStatus.ui32ReleasePics; i++)
    {
        p_printf(print_data, "\t(%u) 0x%08X [0x%08X]\n", i,
                 psStrStatus->sDecStatus.aui32NextReleaseItems[i],
                 psStrStatus->sDecStatus.aui32NextReleaseItemParent[i]);
    }

    p_printf(print_data, "Total pictures decoded: %u\n",
             psStrStatus->sDecStatus.ui32TotalPictDecoded);
    p_printf(print_data, "Total pictures displayed: %u\n",
             psStrStatus->sDecStatus.ui32TotalPictDisplayed);
    p_printf(print_data, "Total pictures finished: %u\n",
             psStrStatus->sDecStatus.ui32TotalPictFinished);

    p_printf(print_data, "-----------------\n");
    p_printf(print_data, "STREAM STATUS END\n");
    p_printf(print_data, "=================\n");


    p_printf(print_data, "CORE STATUS\n");
    p_printf(print_data, "==========\n");

    for(i=0;i<VDECDD_MSVDX_CORE_MAX;i++)
    {

        p_printf(print_data, "CORE %d STATUS\n",i);
        p_printf(print_data, "==========\n");
        p_printf(print_data, "MTX PC:  0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32MTX_PC);
        p_printf(print_data, "MTX PCX: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32MTX_PCX);
        p_printf(print_data, "MTX Stack Pointer: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32MTX_A0StP);
        p_printf(print_data, "MTX Frame Pointer: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32MTX_A0FrP);
        p_printf(print_data, "MTX STATUS BITS: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32MTX_STATUS_BITS);
        p_printf(print_data, "MTX FAULT0: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32MTX_FAULT0);
        p_printf(print_data, "MTX ENABLE: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32MTX_ENABLE);

        p_printf(print_data, "MTX STATUS END\n");
        p_printf(print_data, "==============\n");

        p_printf(print_data, "DMAC STATUS\n");
        p_printf(print_data, "===========\n");

        p_printf(print_data, "DMAC SETUP[0]: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32DMA_SETUP[0]);
        p_printf(print_data, "DMAC SETUP[1]: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32DMA_SETUP[1]);
        p_printf(print_data, "DMAC SETUP[2]: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32DMA_SETUP[2]);
        p_printf(print_data, "DMAC COUNT[0]: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32DMA_COUNT[0]);
        p_printf(print_data, "DMAC COUNT[1]: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32DMA_COUNT[1]);
        p_printf(print_data, "DMAC COUNT[2]: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32DMA_COUNT[2]);
        p_printf(print_data, "DMAC PERIPHERAL ADDR[0]: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32DMA_PERIPHERAL_ADDR[0]);
        p_printf(print_data, "DMAC PERIPHERAL ADDR[1]: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32DMA_PERIPHERAL_ADDR[1]);
        p_printf(print_data, "DMAC PERIPHERAL ADDR[2]: 0x%08X\n",
                 psStrStatus->sDecStatus.asCoreStatus[i].ui32DMA_PERIPHERAL_ADDR[2]);

        p_printf(print_data, "DMAC STATUS END\n");
        p_printf(print_data, "===============\n");
    }

errGetStatus:
    IMG_FREE(psStrStatus);
errStatAlloc:
    ;
}



/*!
******************************************************************************
 This array defines the names for each decode level.
 NOTE: these should be kept in sync with values in #VDECDD_eDecodeLevel.
******************************************************************************/
static IMG_CHAR * apszDecodeLevels[] =
{
    "scheduler [parse only]",
    "decoder [fake hw]",
    "firmware",
    "front-end hardware",

    "all",
};


/*!
******************************************************************************

 @Function                core_SendEvent

******************************************************************************/
static IMG_RESULT core_SendEvent(
    VDECDD_sDdStrContext *  psDdStrContext,
    VDECDD_eEvent           eEvent,
    IMG_VOID              * pvStrCbParam,
    IMG_VOID              * pvBufCbParam,
    const IMG_VOID        * pvParam
)
{
    VDECDD_sCallBackInfo *  psCallBackInfo;

    /* Allocate a device context structure...*/
    psCallBackInfo = IMG_MALLOC(sizeof(*psCallBackInfo));
    IMG_ASSERT(psCallBackInfo != IMG_NULL);
    if (psCallBackInfo == IMG_NULL)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
               "[SID=0x%08X] Failed to allocate memory for VDECDD event",
               psDdStrContext->ui32StrId);
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psCallBackInfo);

    /* Setup callback info. */
    psCallBackInfo->eEvent       = eEvent;
    psCallBackInfo->pvStrCbParam = pvStrCbParam;
    psCallBackInfo->pvBufCbParam = pvBufCbParam;

    /* Copy pvParam data to callback structure (if required). */
    switch (eEvent)
    {

    case VDECDD_EVENT_BSTRBUF_EMPTY:
        IMG_ASSERT(pvParam == IMG_NULL);
        break;

    case VDECDD_EVENT_BSTRINTERNAL_EMPTY:
        IMG_ASSERT(pvParam == IMG_NULL);
        break;

    case VDECDD_EVENT_PICTBUF_FULL:
        {
            const VDEC_sDecPictInfo *  psDecPictInfo = pvParam;

            /* Copy decoded picture info into message. */
            IMG_ASSERT(psDecPictInfo != IMG_NULL);
            if (psDecPictInfo)
            {
                psCallBackInfo->sDecPictInfo = *psDecPictInfo;
            }
        }
        break;

    case VDECDD_EVENT_PICTURE_DECODED:
        {
            const VDEC_sDecPictAuxInfo *  psDecPictAuxInfo = pvParam;

            /* Copy decoded picture info into message. */
            IMG_ASSERT(psDecPictAuxInfo != IMG_NULL);
            if (psDecPictAuxInfo)
            {
                psCallBackInfo->sDecPictAuxInfo = *psDecPictAuxInfo;
            }
        }
        break;

    case VDECDD_EVENT_STREAM_STOPPED:
        /* Copy tag into message. */
        //IMG_ASSERT(pvParam != IMG_NULL);
        psCallBackInfo->pvTag = (IMG_VOID *)pvParam;
        break;

    case VDECDD_EVENT_STREAM_FLUSHED:
        IMG_ASSERT(pvParam == IMG_NULL);
        IMG_ASSERT(pvBufCbParam == IMG_NULL);
        break;

    default:
        IMG_ASSERT(IMG_FALSE);
    }

    /* Queue event */
    SYSOSKM_DisableInt();
    LST_add(&psDdStrContext->sEventCbList, psCallBackInfo);
    SYSOSKM_EnableInt();

    SYSOSKM_SignalEventObject(psDdStrContext->hEventHandle);

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              core_SendSyncMsg

 @Description:
 Send a message to the HISR workqueue, and wait for a response.
 The wait is uninterruptible, so this function cannot be used if waiting for
 an event that might not happen (e.g. a hardware event).

******************************************************************************/
static IMG_RESULT core_SendSyncMsg(
    CORE_eMsgId             eMsgId,
    IMG_UINT32              ui32StrId,
    VDECDD_sDdDevContext *  psDdDevContext,
    CORE_sCoreMsg *         psCoreMsg
)
{
    IMG_RESULT  ui32Result;

    if (psDdDevContext == IMG_NULL)
    {
        VDECDD_sDdStrContext * psDdStrContext;

        // Stream based messages without a device context must have a stream ID.
        IMG_ASSERT(ui32StrId);

        /* Get access to stream context...*/
        ui32Result = RMAN_GetResource(ui32StrId, VDECDD_STREAM_TYPE_ID, (IMG_VOID **)&psDdStrContext, IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        psDdDevContext = psDdStrContext->psDdConnContext->psDdDevContext;
    }

    IMG_ASSERT(psDdDevContext);

    psCoreMsg->eMsgId = eMsgId;
    psCoreMsg->ui32StrId = ui32StrId;
    psCoreMsg->ui32Result = IMG_SUCCESS;

    /* Create event object. */
    ui32Result = SYSOSKM_CreateEventObject(&psCoreMsg->hEventHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Disable interrupts.  */
    SYSOSKM_DisableInt();

    /* Add message to queue. */
    LST_add(&psDdDevContext->sCoreMsgList, psCoreMsg);

    /* Enable interrupts.  */
    SYSOSKM_EnableInt();

    /* Activate the HISR which will call CORE_ProcessEvent(). */
    DMANKM_ActivateKmHisr(psDdDevContext->hDevHandle);

    /* Wait for the message to be processed */
    ui32Result = SYSOSKM_WaitEventObject(psCoreMsg->hEventHandle, IMG_TRUE);
    /* Destroy the event object. */
    SYSOSKM_DestroyEventObject(psCoreMsg->hEventHandle);

    IMG_ASSERT(ui32Result != IMG_ERROR_INTERRUPTED);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              core_SendAsyncMsg

******************************************************************************/
static IMG_RESULT core_SendAsyncMsg(
    CORE_eMsgId             eMsgId,
    IMG_UINT32              ui32StrId,
    VDECDD_sDdDevContext *  psDdDevContext,
    CORE_sCoreMsg *         psCoreMsg
)
{
    if (psDdDevContext == IMG_NULL)
    {
        VDECDD_sDdStrContext  * psDdStrContext;
        IMG_RESULT              ui32Result;

        // Stream based messages without a device context must have a stream ID.
        IMG_ASSERT(ui32StrId);

        /* Get access to stream context...*/
        ui32Result = RMAN_GetResource(ui32StrId, VDECDD_STREAM_TYPE_ID, (IMG_VOID **)&psDdStrContext, IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        psDdDevContext = psDdStrContext->psDdConnContext->psDdDevContext;
    }

    IMG_ASSERT(psDdDevContext);

    psCoreMsg->eMsgId = eMsgId;
    psCoreMsg->ui32StrId = ui32StrId;
    psCoreMsg->ui32Result = IMG_SUCCESS;

    /* Disable interrupts.  */
    SYSOSKM_DisableInt();

    /* Add message to queue. */
    LST_add(&psDdDevContext->sCoreMsgList, psCoreMsg);

    /* Enable interrupts.  */
    SYSOSKM_EnableInt();

    /* Activate the HISR which will call CORE_ProcessEvent(). */
    DMANKM_ActivateKmHisr(psDdDevContext->hDevHandle);

    /* Return success...*/
    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              core_GetConnContext

 @Description

 Get connection context from connection ID.

 @Input     ui32ConnId : Connection ID.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
static IMG_RESULT
core_GetConnContext(
    IMG_UINT32                  ui32ConnId,
    VDECDD_sDdConnContext    ** ppsDdConnContext
)
{
    IMG_HANDLE  hConnHandle;
    IMG_RESULT  ui32Result;

    /* Get the connection handle from it's ID...*/
    ui32Result = DMANKM_GetConnHandleFromId(ui32ConnId, &hConnHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Get access to the device connection context...*/
    *ppsDdConnContext = (VDECDD_sDdConnContext *)DMANKM_GetDevConnectionData(hConnHandle);
    IMG_ASSERT(*ppsDdConnContext != IMG_NULL);

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              core_StreamSignalStopStatus

 @Description

 Update the Scheduler stop flags to include the reason provided in ui32StopFlags.


 @Input     ui32StopFlags : New status to update within stop flags.

******************************************************************************/
static IMG_RESULT
core_StreamSignalStopStatus(
    VDECDD_sDdStrContext *   psDdStrContext,
    IMG_UINT32               ui32StopFlags
)
{
    IMG_UINT32 * pui32StopFlags = IMG_NULL;
    IMG_RESULT   ui32Result;

    if (psDdStrContext->eDdStrState == VDECDD_STRSTATE_STOPPED)
    {
        pui32StopFlags = &psDdStrContext->sStopInfo.ui32StopFlags;
    }

    ui32Result = SCHEDULER_StreamSignalStopStatus(psDdStrContext->hSchedulerContext,
                                                  ui32StopFlags,
                                                  pui32StopFlags);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function                core_HandleProcessedUnit

******************************************************************************/
static IMG_RESULT core_HandleProcessedUnit(
    VDECDD_sDdStrContext *  psDdStrContext,
    VDECDD_sStrUnit *       psStrUnit
)
{
    BSPP_sBitStrSeg * psBitStrSeg;
    IMG_RESULT          ui32Result;

    /* Loop over bit stream segments...*/
    psBitStrSeg = (BSPP_sBitStrSeg *)LST_removeHead(&psStrUnit->sBitStrSegList);
    while (psBitStrSeg != IMG_NULL)
    {
        /* If this is the last segment in the buffer...*/
        if (psBitStrSeg->ui32BitStrSegFlag & VDECDD_BSSEG_LASTINBUFF)
        {
            //Determining i fit is a defragmented buffer for VP8
            //which does not belong to the MMF but to vdec_api
            if(psDdStrContext->sStrConfigData.eVidStd == VDEC_STD_VP8 &&
                psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_START &&
                psStrUnit->psPictHdrInfo->bFragmentedData &&
                psBitStrSeg->ui32DataSize == psStrUnit->psPictHdrInfo->ui32PicDataSize)
            {
                VDECDD_sDdBufMapInfo *  psDdBufMapInfo;
                /* Get access to map info context...*/
                ui32Result = RMAN_GetResource(psBitStrSeg->ui32BufMapId, VDECDD_BUFMAP_TYPE_ID, (IMG_VOID **)&psDdBufMapInfo, IMG_NULL);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }
                /* The defragmented internal buffer is free now. */
                core_SendEvent(psDdStrContext,
                    VDECDD_EVENT_BSTRINTERNAL_EMPTY,
                    psDdStrContext->pvStrCbParam,
                    psDdBufMapInfo->pvBufCbParam,
                    IMG_NULL);
            }
            else
            {
                if (psDdStrContext->eDdStrState != VDECDD_STRSTATE_STOPPED)
                {
                    VDECDD_sDdBufMapInfo *  psDdBufMapInfo;
                    /* Get access to map info context...*/
                    ui32Result = RMAN_GetResource(psBitStrSeg->ui32BufMapId, VDECDD_BUFMAP_TYPE_ID, (IMG_VOID **)&psDdBufMapInfo, IMG_NULL);
                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        return ui32Result;
                    }

                    /* Bit stream buffer now empty. */
                    core_SendEvent(psDdStrContext,
                                   VDECDD_EVENT_BSTRBUF_EMPTY,
                                   psDdStrContext->pvStrCbParam,
                                   psDdBufMapInfo->pvBufCbParam,
                                   IMG_NULL);
                }
            }
        }

        /* Free segment. */
        IMG_FREE(psBitStrSeg);

        /* Get next segment. */
        psBitStrSeg = (BSPP_sBitStrSeg *)LST_removeHead(&psStrUnit->sBitStrSegList);
    }

    if (psStrUnit->eStrUnitType == VDECDD_STRUNIT_STOP)
    {
        /* Signal that the stream has been stopped in the device driver. */
        psDdStrContext->eDdStrState = VDECDD_STRSTATE_STOPPED;

        // Take a copy of the stop information and then clear the pointer
        // so that the data doesn't become inconsistent in the two different places.
        psDdStrContext->sStopInfo = *((VDEC_sStopInfo*)psStrUnit->pvDdData);
        IMG_FREE(psStrUnit->pvDdData);
        psStrUnit->pvDdData = IMG_NULL;

        //Enabling Android StoreMetaDataInBuffers Index requires that Buffers be mapped Dynamically.
        //Removing the check for number of buffers mapped and compatible size with previously mapped buffers.

        /*if (psDdStrContext->sComSequHdrInfo.sMaxFrameSize.ui32Width != 0)
        {
            IMG_UINT32 ui32ReqNumPictBufs = 0;

            // Report number of mapped buffers if more are needed to decode.
            ui32Result = VDECDDUTILS_GetMinRequiredNumPicts(
                &psDdStrContext->sStrConfigData,
                &psDdStrContext->sComSequHdrInfo,
                &psDdStrContext->sOutputConfig,
                &ui32ReqNumPictBufs);
            if(ui32Result != IMG_SUCCESS)
            {
                REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                    "[SID=0x%08X] Failed to calculate number of pictures needed for decode while processing STOP stream unit",
                    psDdStrContext->ui32StrId);
            }
            if (psDdStrContext->sMapBufInfo.ui32NumBufs < ui32ReqNumPictBufs)
            {
                IMG_UINT32 ui32TempResult;

                // Number of mapped image buffers is not sufficient for sequence.
                ui32TempResult = core_StreamSignalStopStatus(psDdStrContext, VDEC_STOPSTATUS_PICTBUF_NUM_MAPPED_INVALID);
                IMG_ASSERT(ui32TempResult == IMG_SUCCESS);
            }
        }*/
        if ((psDdStrContext->sStopInfo.ui32StopFlags & VDEC_STOPSTATUS_RECONFIGURE) ||
            (psDdStrContext->sStopInfo.ui32StopFlags & VDEC_STOPSTATUS_DISPLAY_RESOLUTION_CHANGED))
        {
            if ((psDdStrContext->sStopInfo.ui32StopFlags & VDEC_STOPSTATUS_CLOSED_GOP) == 0)
            {
                // Warn about output reconfiguration when needing to change buffers within a closed GOP, except when at a fence.
                if ((psDdStrContext->sStopInfo.ui32StopFlags & VDEC_STOPSTATUS_PICTBUF_CONFIG_INVALID) &&
                    (psDdStrContext->sStopInfo.ui32StopFlags & VDEC_STOPSTATUS_FENCE) == 0)
                {
                    /*REPORT(REPORT_MODULE_CORE, REPORT_WARNING,
                        "[SID=0x%08X] Stream output requires reconfiguration but closed GOP not signalled. "
                        "Subsequent picture pictures may refer to incompatible references",
                        psDdStrContext->ui32StrId);*/
                }
            }
            else
            {
                // Automatically flush all display and reference pictures.
                // If the output buffers need to be reconfigured then the reference
                // pictures are assumed to be unsuitable for any pictures that follow.
                if (!psDdStrContext->sComSequHdrInfo.bNotDpbFlush)
                {
                    ui32Result = DECODER_StreamFlush(psDdStrContext->hDecoderContext, IMG_TRUE);
                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        return ui32Result;
                    }
                }
            }

            if (psDdStrContext->sStopInfo.ui32StopFlags & VDEC_STOPSTATUS_RECONFIGURE)
            {
                psDdStrContext->bStrOutputConfigured = IMG_FALSE;
            }
            else
            {
                /* Only resolution has changed, but there is no need for reconf. */
                psDdStrContext->bStrOutputConfigured = IMG_TRUE;
            }
        }

        ui32Result = core_SendEvent(psDdStrContext,
            VDECDD_EVENT_STREAM_STOPPED,
            psDdStrContext->pvStrCbParam,
            IMG_NULL,
            psStrUnit->pvStrUnitTag);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }
#if 0
    else if (psStrUnit->eStrUnitType == VDECDD_STRUNIT_SEQUENCE_END)
    {
        // Automatically flush all display and reference pictures.
        // If the sequence has ended future sequences either have different frame
        // properties (references are no longer suitable) or don't use previous reference pictures
        ui32Result = DECODER_StreamFlush(psDdStrContext->hDecoderContext, IMG_TRUE);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }
#endif

    DEBUG_REPORT(REPORT_MODULE_CORE,
        "[SID=0x%08X] [UTYPE=0x%08X] PROCESSED",
        psDdStrContext->ui32StrId,
        psStrUnit->eStrUnitType);

    /* Return success...*/
    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              core_IsUnsupported

******************************************************************************/
static IMG_BOOL
core_IsUnsupported(
    VDEC_sUnSupportedFlags  * psUnSupportedFlags
)
{
    IMG_BOOL bUnsupported = IMG_FALSE;

    if (psUnSupportedFlags->ui32StrConfig ||
        psUnSupportedFlags->ui32SequHdr ||
        psUnSupportedFlags->ui32PictHdr ||
        psUnSupportedFlags->ui32StrOutputConfig ||
        psUnSupportedFlags->ui32OutputBufConfig)
    {
        bUnsupported = IMG_TRUE;
    }

    return bUnsupported;
}



/*!
******************************************************************************

 @Function              core_ReconfigureReconPictBuf

 @Description

 This function determines whether output reconfiguration is required.

 @Input    psDdStrContext : The current stream context.

 @Input    bReferencesUnused : Indicates whether references are used by
                               subsequent pictures.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
static IMG_RESULT
core_ReconfigureReconPictBuf(
    VDECDD_sDdStrContext *  psDdStrContext,
    IMG_BOOL                bReferencesUnused
)
{
    IMG_RESULT  ui32Result;
    VXDIO_sMemPool sMemPool;

    sMemPool.eMemPoolId = psDdStrContext->sStrConfigData.bSecureStream ?
        psDdStrContext->psDdConnContext->psDdDevContext->eSecurePool : psDdStrContext->psDdConnContext->psDdDevContext->eInsecurePool;
    sMemPool.eMemPoolType = psDdStrContext->sStrConfigData.bSecureStream ? VXDIO_MEMPOOL_SECURE : VXDIO_MEMPOOL_INSECURE;

    // Output configuration must be set before reconstructed picture
    // buffer source can be determined.
    IMG_ASSERT(psDdStrContext->bStrOutputConfigured);

    // Obtain the necessary internal resources including deciding whether
    // display picture buffers can be used instead of internal auxiliary buffers.
    // Picture buffers will be removed from internal resources when display buffers
    // are used for reference.
    ui32Result = PLANT_StreamResourceCreate(
        psDdStrContext->hPlantContext,
        bReferencesUnused,
        sMemPool,
        &psDdStrContext->sComSequHdrInfo,
        &psDdStrContext->sOutputConfig,
        &psDdStrContext->sDispPictBuf);
    IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              core_ActivePowerDownDecoder

 @Description

 This function powers down the cores if in active.

******************************************************************************/
static IMG_RESULT
core_ActivePowerDownDecoder(
    const IMG_HANDLE hDecCtx
)
{
    IMG_UINT32 ui32Result;

    // Power off the cores not scheduled on.
    ui32Result = DECODER_PowerOff(
        hDecCtx,
        IMG_FALSE);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              core_CheckDecoderSupport

 @Description

 This function determines whether Decoder supports bitstream and configuration.

******************************************************************************/
static IMG_RESULT
core_CheckDecoderSupport(
    const VDECDD_sDdDevContext *  psDdDevContext,
    const VDEC_sStrConfigData  *  psStrConfigData,
    const VDEC_sComSequHdrInfo *  psPrevSequHdrInfo,
    const BSPP_sPictHdrInfo    *  psPrevPictHdrInfo,
    const VDECDD_sMapBufInfo   *  psMapBufInfo,
    VDECDD_sSuppCheck          *  psSupportedCheck
)
{
    IMG_RESULT ui32Result;

    psSupportedCheck->ui32StopFlags = 0;

    if (psDdDevContext->eDecodeLevel > VDECDD_DECODELEVEL_SCHEDULER)
    {
        VDEC_sUnSupportedFlags  sUnSupported;
        VDEC_sPictRendInfo      sDispPictRendInfo;

        VDEC_BZERO(&sDispPictRendInfo);

        // If output picture buffer information is provided create another
        // with properties required by bitstream so that it can be compared.
        if (psSupportedCheck->psDispPictBuf)
        {
            VDEC_sPictRendConfig    sPictRendConfig;

            // Cannot validate the display picture buffer layout without knowing
            // the pixel format required for the output and the sequence information.
            if (psSupportedCheck->psComSequHdrInfo &&
                psSupportedCheck->psOutputConfig)
            {
                if (psMapBufInfo->ui32NumBufs)
                {
                    IMG_ASSERT(psMapBufInfo->eTileScheme == psSupportedCheck->psDispPictBuf->sBufConfig.eTileScheme);
                }
                // Prepare picture render configuration.
                if(psSupportedCheck->psOutputConfig->bScale) {
                	//Set ScaledPictSize for Scaling
                	sPictRendConfig.sCodedPictSize      = psSupportedCheck->psOutputConfig->sScaledPictSize;
            		/*sCodedPictSize.ui32Width, sCodedPictSize.ui32Height need to be a multiple of 16 */
            		if(psSupportedCheck->psOutputConfig->sScaledPictSize.ui32Width & 0x0000000F)
            		{
            			sPictRendConfig.sCodedPictSize.ui32Width = (psSupportedCheck->psOutputConfig->sScaledPictSize.ui32Width & 0xFFFFFFF0) + 0x00000010 ;
            		}
            		if(psSupportedCheck->psOutputConfig->sScaledPictSize.ui32Height & 0x0000000F)
            		{
            			sPictRendConfig.sCodedPictSize.ui32Height = (psSupportedCheck->psOutputConfig->sScaledPictSize.ui32Height & 0xFFFFFFF0) + 0x00000010 ;
            		}
                }
                else {
                	sPictRendConfig.sCodedPictSize = psSupportedCheck->psComSequHdrInfo->sMaxFrameSize;
                }


                sPictRendConfig.eTileScheme = psSupportedCheck->psDispPictBuf->sBufConfig.eTileScheme;
                sPictRendConfig.bPacked = psSupportedCheck->psDispPictBuf->sBufConfig.bPacked;
                DECODER_IsSupportedFeature(psDdDevContext->hDecoderContext,
                                           VDEC_FEATURE_EXTENDED_STRIDES,
                                           &sPictRendConfig.bUseExtendedStrides);

                // Recalculate render picture layout based upon sequence and output config.
                VDECDDUTILS_PictBufGetInfo(psStrConfigData,
                                           &sPictRendConfig,
                                           psSupportedCheck->psOutputConfig,
                                           &sDispPictRendInfo);
            }

            // Mapped buffers are not even large enough for new layout.
            //For Dynamic buffer mapping for android, psMapBufInfo->ui32BufSize may not be available before the buffers are supplied.
            /*if (psMapBufInfo->ui32BufSize < sDispPictRendInfo.ui32RenderedSize)
            {
                psSupportedCheck->ui32StopFlags |= VDEC_STOPSTATUS_PICTBUF_SIZE_INVALID;
                psSupportedCheck->ui32StopFlags |= VDEC_STOPSTATUS_RECONFIGURE;
            }*/
        }
        else
        {
            psSupportedCheck->ui32StopFlags |= VDEC_STOPSTATUS_PICTBUF_CONFIG_INVALID;
        }

        if (psSupportedCheck->psOutputConfig == IMG_NULL)
        {
            psSupportedCheck->ui32StopFlags |= VDEC_STOPSTATUS_OUTPUT_CONFIG_INVALID;
        }

        // Check that the decoder supports the picture.
        ui32Result = DECODER_CheckSupport(
                        psDdDevContext->hDecoderContext,
                        psStrConfigData,
                        psSupportedCheck->psOutputConfig,
                        psSupportedCheck->psDispPictBuf,
                        (sDispPictRendInfo.ui32RenderedSize) ? &sDispPictRendInfo : IMG_NULL,
                        psSupportedCheck->psComSequHdrInfo,
                        psSupportedCheck->psPictHdrInfo,
                        psPrevSequHdrInfo,
                        psPrevPictHdrInfo,
                        &sUnSupported,
                        &psSupportedCheck->ui32Features);
        IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);

        if (sUnSupported.ui32SequHdr)
        {
            psSupportedCheck->ui32StopFlags |= VDEC_STOPSTATUS_UNSUPPORTED;
        }

        if (ui32Result != IMG_SUCCESS)
        {
            if (ui32Result == IMG_ERROR_NOT_SUPPORTED)
            {
                psSupportedCheck->sUnSupportedFlags = sUnSupported;

                if (sUnSupported.ui32StrOutputConfig)
                {
                    psSupportedCheck->ui32StopFlags |= VDEC_STOPSTATUS_OUTPUT_CONFIG_INVALID;
                }

                if(sUnSupported.ui32OutputBufConfig)
                {
                    psSupportedCheck->ui32StopFlags |= VDEC_STOPSTATUS_PICTBUF_CONFIG_INVALID;

                    IMG_ASSERT(psSupportedCheck->psDispPictBuf);
                    IMG_ASSERT(psSupportedCheck->psOutputConfig);

                    DEBUG_REPORT(REPORT_MODULE_PLANT, "======================================================");
                    DEBUG_REPORT(REPORT_MODULE_PLANT, "User stream id: 0x%08X", psStrConfigData->ui32UserStrId);
                    DEBUG_REPORT(REPORT_MODULE_PLANT, "Required Buffer Configuration");
                    DEBUG_REPORT(REPORT_MODULE_PLANT, "-----------------------------");

                    VDECDDUTILS_PrintBufferProperties(psSupportedCheck->psOutputConfig,
                                                      &sDispPictRendInfo,
                                                      IMG_NULL);

                    DEBUG_REPORT(REPORT_MODULE_PLANT, "======================================================");

                    DEBUG_REPORT(REPORT_MODULE_PLANT, "Actual Buffer Configuration");
                    DEBUG_REPORT(REPORT_MODULE_PLANT, "---------------------------");

                    VDECDDUTILS_PrintBufferProperties(psSupportedCheck->psOutputConfig,
                                                      &psSupportedCheck->psDispPictBuf->sRendInfo,
                                                      &psSupportedCheck->psDispPictBuf->sBufConfig);

                    DEBUG_REPORT(REPORT_MODULE_PLANT, "======================================================");
                }

                //If it is unsupported only because we need to reconfigure, do NOT mark as unsupported
                if(!sUnSupported.ui32OutputBufConfig)
                {
                    psSupportedCheck->ui32StopFlags |= VDEC_STOPSTATUS_UNSUPPORTED;

                }
            }
            else
            {
                return ui32Result;
            }
        }
        //Enabling Android StoreMetaDataInBuffers Index requires that Buffers be mapped Dynamically.
        //Removing the check for number of buffers mapped and compatible size with previously mapped buffers.
        /*if (psStrConfigData &&
            psSupportedCheck->psComSequHdrInfo &&
            psSupportedCheck->psOutputConfig &&
            psMapBufInfo)
        {
            IMG_UINT32 ui32ReqNumPictBufs;

            // Report number of mapped buffers if more are needed to decode.
            ui32Result = VDECDDUTILS_GetMinRequiredNumPicts(
                                                psStrConfigData,
                                                psSupportedCheck->psComSequHdrInfo,
                                                psSupportedCheck->psOutputConfig,
                                                &ui32ReqNumPictBufs);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
            if (psMapBufInfo->ui32NumBufs < ui32ReqNumPictBufs)
            {
                psSupportedCheck->ui32StopFlags |= VDEC_STOPSTATUS_PICTBUF_NUM_MAPPED_INVALID;
            }
        }*/

        if ((psSupportedCheck->ui32StopFlags & VDEC_STOPSTATUS_OUTPUT_CONFIG_INVALID) ||
            (psSupportedCheck->ui32StopFlags & VDEC_STOPSTATUS_PICTBUF_CONFIG_INVALID) ||
            (psSupportedCheck->ui32StopFlags & VDEC_STOPSTATUS_PICTBUF_SIZE_INVALID))
        {
            psSupportedCheck->ui32StopFlags |= VDEC_STOPSTATUS_RECONFIGURE;
        }
    }

    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              core_CompCallback

******************************************************************************/
static IMG_RESULT core_CompCallback(
    IMG_INT32   i32Reason,
    IMG_VOID *  pvInitUserData,
    IMG_VOID *  pvCoreUserData,
    IMG_VOID *  pvStrUserData,
    IMG_VOID *  pvData
)
{
//    VDECDD_sDdDevContext *  psDdDevContext = (VDECDD_sDdDevContext*)pvInitUserData;
    VDECDD_sDdStrContext *  psDdStrContext = (VDECDD_sDdStrContext*)pvStrUserData;
    VDECDD_eStrUnitType  eStrUnitType;
    VDECDD_sStrUnit *  psStrUnit;
    IMG_RESULT  ui32Result = IMG_SUCCESS;

    switch (i32Reason)
    {
    case PLANT_CB_PICTURE_RESOURCE_ADD:
        /* Submit picture resources to the scheduler. */
        SCHEDULER_StreamAddPictureResource(
            psDdStrContext->hSchedulerContext,
            (VDECDD_sPictResInt*)pvData);
        break;

    case PLANT_CB_PICTURE_RESOURCE_REMOVE:
        SCHEDULER_StreamRemovePictureResource(
            psDdStrContext->hSchedulerContext,
            (VDECDD_sPictResInt*)pvData);
        break;

    case SCHEDULER_CB_PROCESS_UNIT:
        psStrUnit = pvData;

        DEBUG_REPORT(REPORT_MODULE_CORE,
            "[SID=0x%08X] [UTYPE=0x%08X] PROCESS",
            psDdStrContext->ui32StrId,
            psStrUnit->eStrUnitType);

        // Since the stop is now to be passed to the decoder signal that we're stopping.
        if (psStrUnit->eStrUnitType == VDECDD_STRUNIT_STOP)
        {
            psDdStrContext->eDdStrState = VDECDD_STRSTATE_STOPPING;
        }

        // Store the sequence/picture information for use in error handling.
        if (psStrUnit->eStrUnitType == VDECDD_STRUNIT_SEQUENCE_START)
        {
            psDdStrContext->sPrevComSequHdrInfo = psDdStrContext->sComSequHdrInfo;
            psDdStrContext->sComSequHdrInfo = psStrUnit->psSequHdrInfo->sComSequHdrInfo;

            DEBUG_REPORT(REPORT_MODULE_CORE,
                "[SID=0x%08X] VSH: Maximum Frame Resolution [%dx%d]",
                psDdStrContext->ui32StrId,
                psDdStrContext->sComSequHdrInfo.sMaxFrameSize.ui32Width,
                psDdStrContext->sComSequHdrInfo.sMaxFrameSize.ui32Height);
        }
        else if (psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_START)
        {
            psDdStrContext->sPrevPictHdrInfo = *psStrUnit->psPictHdrInfo;
        }

        /* Submit stream unit to the decoder for processing. */
        ui32Result = DECODER_StreamProcessUnit(psDdStrContext->hDecoderContext, psStrUnit);
        if(ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
        break;

    case SCHEDULER_CB_STREAM_RECONFIGRE_RECON_PICTBUFS:

        ui32Result = core_ReconfigureReconPictBuf(psDdStrContext, *((IMG_BOOL*)pvData));
        IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
        break;

    case SCHEDULER_CB_STREAM_CHECK_LOAD:
        {
            VDECDD_sLoadCheck * psLoadCheck = pvData;

            ui32Result = DECODER_GetLoad(
                            psDdStrContext->psDdConnContext->psDdDevContext->hDecoderContext,
                            psLoadCheck->ui32Features,
                            &psLoadCheck->ui32AvailLoad,
                            &psLoadCheck->ui32MinLoad);
            IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }
        break;

    case SCHEDULER_CB_STREAM_CHECK_SUPPORTED:
        {
            VDECDD_sSuppCheck * psSuppCheck = pvData;
            VDECDD_sMapBufInfo  sMapBufInfo = psDdStrContext->sMapBufInfo;

            // Check the compatibility of the bitstream data and configuration.
            ui32Result = core_CheckDecoderSupport(
                psDdStrContext->psDdConnContext->psDdDevContext,
                &psDdStrContext->sStrConfigData,
                &psDdStrContext->sPrevComSequHdrInfo,
                &psDdStrContext->sPrevPictHdrInfo,
                &sMapBufInfo,
                psSuppCheck);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            // If stop flags were requested, set them in the Scheduler.
            if (psSuppCheck->ui32StopFlags)
            {
                IMG_UINT32 ui32TempResult;

                ui32TempResult = core_StreamSignalStopStatus(psDdStrContext, psSuppCheck->ui32StopFlags);
                IMG_ASSERT(ui32TempResult == IMG_SUCCESS);
            }
        }
        break;

    case DECODER_CB_UNIT_PROCESSED:
        psStrUnit = (VDECDD_sStrUnit *)pvData;

        ui32Result = core_HandleProcessedUnit(psDdStrContext, psStrUnit);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        if (psStrUnit->eStrUnitType == VDECDD_STRUNIT_PICTURE_START &&
            !psStrUnit->bDecode)
        {
            // If the picture has not been decoded make sure that the
            // BSPP resource reference counts have been updated.

            VDEC_sDecPictAuxInfo  sDecPictAuxInfo;

            sDecPictAuxInfo.ui32SequenceHdrId =
                psStrUnit->psSequHdrInfo != IMG_NULL ?
                    psStrUnit->psSequHdrInfo->ui32SequHdrId : BSPP_INVALID;

            sDecPictAuxInfo.ui32PPSId =
                psStrUnit->psPictHdrInfo->sPictAuxData.ui32Id;
            sDecPictAuxInfo.ui32SecondPPSId =
                psStrUnit->psPictHdrInfo->sSecondPictAuxData.ui32Id;

            // If the picture has not been decoded make sure that the
            // BSPP resource reference counts have been updated.
            ui32Result = core_SendEvent(
                psDdStrContext,
                VDECDD_EVENT_PICTURE_DECODED,
                psDdStrContext->pvStrCbParam,
                IMG_NULL,
                &sDecPictAuxInfo);

            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }

        eStrUnitType = psStrUnit->eStrUnitType;
        ui32Result = VDECDDUTILS_FreeStrUnit(psStrUnit);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        DEBUG_REPORT(REPORT_MODULE_CORE,
            "[SID=0x%08X] [UTYPE=0x%08X] DESTROYED",
            psDdStrContext->ui32StrId,
            eStrUnitType);

        // Provide an opportunity to schedule another picture
        // when any picture has been decoded.
        if (eStrUnitType == VDECDD_STRUNIT_PICTURE_START)
        {
            CORE_DevSchedule(psDdStrContext->psDdConnContext->psDdDevContext);
        }
        break;

    case DECODER_CB_PICTURE_DISPLAY:
        /* Picture buffer is now ready for display. */
        ui32Result = core_SendEvent(
            psDdStrContext,
            VDECDD_EVENT_PICTBUF_FULL,
            psDdStrContext->pvStrCbParam,
            ((VDECDD_sPicture *)pvData)->sDisplayPictBuf.psPictBuf->pvBufCbParam,
            ((VDECDD_sPicture *)pvData)->psDecPictInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
        break;

    case DECODER_CB_PICTURE_DECODED:
        /* Picture has been decoded. */
        ui32Result = core_SendEvent(
            psDdStrContext,
            VDECDD_EVENT_PICTURE_DECODED,
            psDdStrContext->pvStrCbParam,
            IMG_NULL,
            &(((VDECDD_sPicture *)pvData)->sDecPictAuxInfo));

        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
        break;

    case SCHEDULER_CB_ACTIVE_POWER_DOWN:
        {
            /* Power Down the cores which do not have anything in their queues */
            VDECDD_sDdDevContext *  psDdDevContext = (VDECDD_sDdDevContext*)pvInitUserData;
            ui32Result = core_ActivePowerDownDecoder(
                psDdDevContext->hDecoderContext);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            break;
        }

    case DECODER_CB_GET_PICT_BUF_NUMBER:
        /* Get the number of registered image buffers from the Scheduler component. */
        ui32Result = SCHEDULER_StreamGetNumImageBuffers(
                                psDdStrContext->hSchedulerContext,
                                (IMG_UINT32*)pvData);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
        break;

    default:
        IMG_ASSERT(IMG_FALSE);
        break;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              CORE_Initialise

******************************************************************************/
IMG_RESULT CORE_Initialise(
    IMG_HANDLE               hDevHandle,
    SYS_eMemPool             eMemPool,
    SYS_eMemPool             eSecureMemPool,
    VDECDD_sDdDevContext **  ppsDdDevContext
)
{
    VDECDD_sDdDevContext *  psDdDevContext;
    VDECDD_sDdDevConfig     sDevConfig;
    IMG_UINT32              ui32NumCores;
    IMG_UINT32              ui32NumPipes;
    IMG_RESULT              ui32Result;

    /* Allocate a device context structure...*/
    VDEC_MALLOC(psDdDevContext);
    if (psDdDevContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
            "Failed to allocate memory for DD Device context");

        ui32Result = IMG_ERROR_OUT_OF_MEMORY;
        goto error;
    }
    VDEC_BZERO(psDdDevContext);

    /* Initialise device context. */
    psDdDevContext->hDevHandle = hDevHandle;
    LST_init(&psDdDevContext->sConnList);
    LST_init(&psDdDevContext->sCoreMsgList);

    /* Preallocate a list for the HW messages so that we don't need to allocate resources during HW interrupts. */
    {
        IMG_UINT32 i;
        CORE_sCoreMsg *psCoreMsg;
        LST_init(&psDdDevContext->sHwMsgList);
        for (i = 0; i < INIT_HM_MSG_LIST_SIZE; i++)
        {
            VDEC_MALLOC(psCoreMsg);
            IMG_ASSERT(psCoreMsg != IMG_NULL);
            if (psCoreMsg == IMG_NULL)
            {
                REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                    "Failed to allocate memory for core message");

                ui32Result = IMG_ERROR_OUT_OF_MEMORY;
                goto error;
            }
            LST_add(&psDdDevContext->sHwMsgList, psCoreMsg);
        }
    }

    /* Initialise the Decoder... */
    ui32Result = DECODER_Initialise(psDdDevContext,
                                    core_CompCallback,
                                    eMemPool,
                                    eSecureMemPool,
                                    &sDevConfig,
                                    &ui32NumCores,
                                    &ui32NumPipes,
                                    &psDdDevContext->hDecoderContext);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    psDdDevContext->eInsecurePool = eMemPool;
    psDdDevContext->eSecurePool =
        sDevConfig.bSecureMemoryAvailable ? eSecureMemPool : eMemPool;

#ifdef __RELEASE_RELEASE__
    if (!bDevConfigLogged)
    {
        REPORT(REPORT_MODULE_CORE,
               REPORT_INFO,
               "[%s] APM:%s, Cores:%u, Slots:%u, Level:%s, DWR:%ums, FakeMTX:%s, FEWDT:%u, BEWDT:%u, PSRWDT:%u, Rendec:%u bytes, Lockstep:%s, PerfLog:%s, Optimised:%s, MemStallMin:%u, MemStallMax:%u, MemStallRatio:%u, Tiling:%s",
               "Device Configuration",
               (sDevConfig.bAPM) ? "y" : "n",
               ui32NumCores,
               sDevConfig.ui32NumSlotsPerPipe,
               apszDecodeLevels[sDevConfig.eDecodeLevel],
               sDevConfig.ui32DwrPeriod,
               (sDevConfig.bFakeMtx) ? "y" : "n",
               sDevConfig.ui32FeWdtPeriod,
               sDevConfig.ui32BeWdtPeriod,
               sDevConfig.ui32PSRWdtPeriod,
               sDevConfig.ui32RendecSize,
               (sDevConfig.bLockStepDecode) ? "y" : "n",
               (sDevConfig.bPerformanceLog) ? "y" : "n",
               (sDevConfig.bOptimisedPerformance) ? "y" : "n",
               sDevConfig.ui32MemoryStallingMin * 32,
               sDevConfig.ui32MemoryStallingMax * 32,
               sDevConfig.ui32MemoryStallingRatio * 10,
               (sDevConfig.eTileScheme == VDEC_TS0_256x16) ? "0" : (sDevConfig.eTileScheme == VDEC_TS1_512x8) ? "1" : "None");

        bDevConfigLogged = IMG_TRUE;
    }

#else

    // Dump all the options in the KM log.
    DEBUG_REPORT(REPORT_MODULE_CORE, "======================================================");
    DEBUG_REPORT(REPORT_MODULE_CORE, "Device Configuration");
    DEBUG_REPORT(REPORT_MODULE_CORE, "--------------------");
    DEBUG_REPORT(REPORT_MODULE_CORE, "APM:                     %s", (sDevConfig.bAPM) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_CORE, "Decode cores:            %d", ui32NumCores);
    DEBUG_REPORT(REPORT_MODULE_CORE, "Decode slots/core:       %d", sDevConfig.ui32NumSlotsPerPipe);
    DEBUG_REPORT(REPORT_MODULE_CORE, "Decode Level:            %s", apszDecodeLevels[sDevConfig.eDecodeLevel]);
    DEBUG_REPORT(REPORT_MODULE_CORE, "DWR Period:              %d (ms)", sDevConfig.ui32DwrPeriod);
    DEBUG_REPORT(REPORT_MODULE_CORE, "Fake MTX:                %s", (sDevConfig.bFakeMtx) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_CORE, "FE HW WDT Period:        %d", sDevConfig.ui32FeWdtPeriod);
    DEBUG_REPORT(REPORT_MODULE_CORE, "BE HW WDT Period:        %d", sDevConfig.ui32BeWdtPeriod);
    DEBUG_REPORT(REPORT_MODULE_CORE, "PSR HW WDT Period:       %d", sDevConfig.ui32PSRWdtPeriod);
    DEBUG_REPORT(REPORT_MODULE_CORE, "Rendec Size:             %d (bytes)", sDevConfig.ui32RendecSize);
    DEBUG_REPORT(REPORT_MODULE_CORE, "Lockstep Decode:         %s", (sDevConfig.bLockStepDecode) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_CORE, "Performance Log:         %s", (sDevConfig.bPerformanceLog) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_CORE, "Optimised Performance:   %s", (sDevConfig.bOptimisedPerformance) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_CORE, "Memory Stalling:         %d - %d for %d%% of transactions",
                                                               sDevConfig.ui32MemoryStallingMin * 32,
                                                               sDevConfig.ui32MemoryStallingMax * 32,
                                                               sDevConfig.ui32MemoryStallingRatio * 10);
    DEBUG_REPORT(REPORT_MODULE_CORE, "Tiling scheme:           %s", (sDevConfig.eTileScheme == VDEC_TS0_256x16) ? "0" :
                                                              (sDevConfig.eTileScheme == VDEC_TS1_512x8) ? "1" : "None");
    DEBUG_REPORT(REPORT_MODULE_CORE, "======================================================");

#endif


    /* Initialise the Plant... */
    ui32Result = PLANT_Initialise(psDdDevContext,
                                  core_CompCallback,
                                  sDevConfig,
                                  ui32NumCores,
                                  ui32NumPipes);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    /* Initialise the Scheduler... */
    ui32Result = SCHEDULER_Initialise(psDdDevContext,
                                      core_CompCallback,
                                      sDevConfig.eDecodeLevel,
                                      sDevConfig.bAPM,
                                      psDdDevContext->hDecoderContext,
                                      &psDdDevContext->hSchedulerContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    psDdDevContext->eDecodeLevel = sDevConfig.eDecodeLevel;

    /* Return address of device context */
    *ppsDdDevContext = psDdDevContext;

    /* Return success...*/
    return IMG_SUCCESS;

error:
    if (psDdDevContext)
    {
        IMG_UINT32 ui32DeinitResult;

        /* Undo the initialisation. */
        ui32DeinitResult = CORE_Deinitialise(psDdDevContext);
        if (ui32DeinitResult != IMG_SUCCESS)
        {
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                "CORE_Deinitialise() failed to tidy-up after error");
        }
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              CORE_Deinitialise

******************************************************************************/
IMG_RESULT CORE_Deinitialise(
    VDECDD_sDdDevContext *  psDdDevContext
)
{
    IMG_RESULT  ui32Result;

    if (psDdDevContext)
    {
        CORE_sCoreMsg *psCoreMsg;

        // Ensure that there are no connections outstanding.
        IMG_ASSERT(LST_empty(&psDdDevContext->sConnList));

#ifdef STACK_USAGE_TEST
        if (psDdDevContext->hDecoderContext)
        {
            /* call the entry point to Stack Usage Test */
            ui32Result = DECODER_StackTest(psDdDevContext->hDecoderContext);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }
#endif

        /* Deinitialise the Plant...*/
        ui32Result = PLANT_Deinitialise();
        IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        if (psDdDevContext->hSchedulerContext)
        {
            /* Deinitialise the Scheduler...*/
            ui32Result = SCHEDULER_Deinitialise(psDdDevContext->hSchedulerContext);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }

        if (psDdDevContext->hDecoderContext)
        {
            /* Deinitialise the Decoder...*/
            ui32Result = DECODER_Deinitialise(psDdDevContext->hDecoderContext);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }

        // Free the sHwMsgList to avoid memory leak
        while ( !LST_empty(&psDdDevContext->sHwMsgList) )
        {
            psCoreMsg = (CORE_sCoreMsg *)LST_removeHead(&psDdDevContext->sHwMsgList);
            IMG_ASSERT(psCoreMsg != IMG_NULL);
            if (psCoreMsg != IMG_NULL)
            {
                /* Free the message structure. */
                IMG_FREE(psCoreMsg);
            }
        }

        IMG_FREE(psDdDevContext);
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              CORE_ConnectionCreate

******************************************************************************/
IMG_RESULT CORE_ConnectionCreate(
    VDECDD_sDdDevContext      * psDdDevContext,
    VDECDD_sDdConnContext    ** ppsDdConnContext
)
{
    IMG_RESULT     ui32Result;
    CORE_sCoreMsg  sCoreMsg;

    /* Create the core message. */
    VDEC_BZERO(&sCoreMsg);
    sCoreMsg.sCreateConnectionMsg.ppsDdConnContext = ppsDdConnContext;

    /* Send and wait for response. */
    ui32Result = core_SendSyncMsg(CORE_MSGID_CONNECTION_CREATE,
                                  CORE_NO_STREAM_ID,
                                  psDdDevContext,
                                  &sCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    IMG_ASSERT(sCoreMsg.ui32Result == IMG_SUCCESS);
    if (sCoreMsg.ui32Result != IMG_SUCCESS)
    {
        return sCoreMsg.ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              CORE_ConnectionDestroy

******************************************************************************/
IMG_RESULT CORE_ConnectionDestroy(
    IMG_UINT32      ui32ConnId
)
{
    IMG_RESULT     ui32Result;
    CORE_sCoreMsg  sCoreMsg;

    if (ui32ConnId)
    {
        VDECDD_sDdConnContext * psDdConnContext;

        ui32Result = core_GetConnContext(ui32ConnId, &psDdConnContext);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        /* Create the core message. */
        VDEC_BZERO(&sCoreMsg);
        sCoreMsg.sDestroyConnectionMsg.ui32ConnId = ui32ConnId;

        /* Send and wait for response. */
        ui32Result = core_SendSyncMsg(CORE_MSGID_CONNECTION_DESTROY,
                                      CORE_NO_STREAM_ID,
                                      psDdConnContext->psDdDevContext,
                                      &sCoreMsg);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        IMG_ASSERT(sCoreMsg.ui32Result == IMG_SUCCESS);
        if (sCoreMsg.ui32Result != IMG_SUCCESS)
        {
            return sCoreMsg.ui32Result;
        }
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              CORE_StreamCreate

******************************************************************************/
IMG_RESULT CORE_StreamCreate(
    IMG_UINT32              ui32ConnId,
    VDEC_sStrConfigData   * psStrConfigData,
    IMG_VOID              * pvStrCbParam,
    IMG_UINT32            * pui32StrId
)
{
    IMG_RESULT     ui32Result = IMG_SUCCESS;
    CORE_sCoreMsg  sCoreMsg;

    if (ui32ConnId)
    {
        VDECDD_sDdConnContext * psDdConnContext;

        ui32Result = core_GetConnContext(ui32ConnId, &psDdConnContext);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        /* Create the core message. */
        VDEC_BZERO(&sCoreMsg);
        sCoreMsg.sStreamCreateMsg.ui32ConnId = ui32ConnId;
        sCoreMsg.sStreamCreateMsg.sStrConfigData = *psStrConfigData;
        sCoreMsg.sStreamCreateMsg.pvStrCbParam = pvStrCbParam;
        sCoreMsg.sStreamCreateMsg.pui32StrId = pui32StrId;

        /* Send and wait for response. */
        ui32Result = core_SendSyncMsg(CORE_MSGID_STREAM_CREATE,
                                      CORE_NO_STREAM_ID,
                                      psDdConnContext->psDdDevContext,
                                      &sCoreMsg);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        IMG_ASSERT((sCoreMsg.ui32Result == IMG_SUCCESS) ||
                   (sCoreMsg.ui32Result == IMG_ERROR_NOT_SUPPORTED));
        if (sCoreMsg.ui32Result != IMG_SUCCESS)
        {
            return sCoreMsg.ui32Result;
        }
    }

    /* Return success...*/
    return ui32Result;
}


/*!
******************************************************************************

 @Function              CORE_StreamDestroy

******************************************************************************/
IMG_RESULT CORE_StreamDestroy(
    IMG_UINT32      ui32StrId,
    IMG_HANDLE      hDestroyedEvent,
    IMG_UINT32    * pui32ConnId
)
{
    IMG_RESULT     ui32Result;
    CORE_sCoreMsg  sCoreMsg;

    /* Create the core message. */
    VDEC_BZERO(&sCoreMsg);
    sCoreMsg.sStreamDestroyMsg.hDestroyedEvent = hDestroyedEvent;
    sCoreMsg.sStreamDestroyMsg.pui32ConnId = pui32ConnId;

    /* Send and wait for response. */
    ui32Result = core_SendSyncMsg(CORE_MSGID_STREAM_DESTROY,
                                  ui32StrId,
                                  IMG_NULL,
                                  &sCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    IMG_ASSERT(sCoreMsg.ui32Result == IMG_SUCCESS);
    if (sCoreMsg.ui32Result != IMG_SUCCESS)
    {
        return sCoreMsg.ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              CORE_StreamPlay

******************************************************************************/
IMG_RESULT CORE_StreamPlay(
    IMG_UINT32              ui32StrId,
    VDEC_ePlayMode          ePlayMode,
    VDEC_eStopPoint         eStopPoint,
    IMG_UINT32              ui32StopPointQual
)
{
    IMG_RESULT              ui32Result;
    CORE_sCoreMsg         * psCoreMsg;

    /* Allocate a core message...*/
    VDEC_MALLOC(psCoreMsg);
    IMG_ASSERT(psCoreMsg != IMG_NULL);
    if (psCoreMsg == IMG_NULL)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
            "[SID=0x%08X] Failed to allocate memory for core message",
            ui32StrId);
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    /* Create the core message. */
    VDEC_BZERO(psCoreMsg);
    psCoreMsg->sStreamPlayMsg.ePlayMode = ePlayMode;
    psCoreMsg->sStreamPlayMsg.eStopPoint = eStopPoint;
    psCoreMsg->sStreamPlayMsg.ui32StopPointQual = ui32StopPointQual;

    /* Send message. */
    ui32Result = core_SendAsyncMsg(CORE_MSGID_STREAM_PLAY,
                                   ui32StrId,
                                   IMG_NULL,
                                   psCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        IMG_FREE(psCoreMsg);
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              CORE_StreamStop

******************************************************************************/
IMG_RESULT CORE_StreamStop(
    IMG_UINT32              ui32StrId,
    VDEC_eStopPoint         eStopPoint,
    IMG_UINT32              ui32StopPointQual
)
{
    IMG_RESULT              ui32Result;
    CORE_sCoreMsg         * psCoreMsg;

    /* Allocate a core message...*/
    VDEC_MALLOC(psCoreMsg);
    IMG_ASSERT(psCoreMsg != IMG_NULL);
    if (psCoreMsg == IMG_NULL)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
            "[SID=0x%08X] Failed to allocate memory for core message",
            ui32StrId);
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    /* Create the core message. */
    VDEC_BZERO(psCoreMsg);
    psCoreMsg->sStreamStopMsg.eStopPoint = eStopPoint;
    psCoreMsg->sStreamStopMsg.ui32StopPointQual = ui32StopPointQual;

    /* Send message. */
    ui32Result = core_SendAsyncMsg(CORE_MSGID_STREAM_STOP,
                                   ui32StrId,
                                   IMG_NULL,
                                   psCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        IMG_FREE(psCoreMsg);
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              CORE_StreamGetStopFlags

******************************************************************************/
IMG_RESULT CORE_StreamGetStopFlags(
    IMG_UINT32              ui32StrId,
    IMG_UINT32 *            pui32StopFlags
)
{
    IMG_ASSERT(0);

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              CORE_StreamMapBuf

******************************************************************************/
IMG_RESULT CORE_StreamMapBuf(
    IMG_UINT32              ui32StrId,
    IMG_VOID *              pvBufCbParam,
    VDEC_eBufType           eBufType,
    VDEC_sBufInfo         * psBufInfo,
    IMG_UINT32            * pui32BufMapId
)
{
    IMG_RESULT              ui32Result;
    CORE_sCoreMsg           sCoreMsg;

    /* Create the core message. */
    VDEC_BZERO(&sCoreMsg);
    sCoreMsg.sStreamMapBufMsg.pvBufCbParam = pvBufCbParam;
    sCoreMsg.sStreamMapBufMsg.eBufType = eBufType;
    sCoreMsg.sStreamMapBufMsg.sBufInfo = *psBufInfo;
    sCoreMsg.sStreamMapBufMsg.pui32BufMapId = pui32BufMapId;

    /* Send and wait for response. */
    ui32Result = core_SendSyncMsg(CORE_MSGID_STREAM_MAP_BUF,
                                  ui32StrId,
                                  IMG_NULL,
                                  &sCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    IMG_ASSERT_TESTED(sCoreMsg.ui32Result == IMG_SUCCESS);
    if (sCoreMsg.ui32Result != IMG_SUCCESS)
    {
        return sCoreMsg.ui32Result;
    }

    DEBUG_REPORT(REPORT_MODULE_CORE,
        "[SID=0x%08X] Buffer mapped (buffer map id: %u)",
        ui32StrId,
        *pui32BufMapId);

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              CORE_StreamUnmapBuf

******************************************************************************/
IMG_RESULT CORE_StreamUnmapBuf(
    IMG_UINT32              ui32BufMapId
)
{
    IMG_RESULT              ui32Result;
    VDECDD_sDdBufMapInfo *  psDdBufMapInfo;
    CORE_sCoreMsg           sCoreMsg;

    /* Get access to map info context...*/
    ui32Result = RMAN_GetResource(ui32BufMapId, VDECDD_BUFMAP_TYPE_ID, (IMG_VOID **)&psDdBufMapInfo, IMG_NULL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Create the core message. */
    VDEC_BZERO(&sCoreMsg);
    sCoreMsg.sStreamUnmapBufMsg.ui32BufMapId = ui32BufMapId;

    /* Send message. */
    ui32Result = core_SendSyncMsg(CORE_MSGID_STREAM_UNMAP_BUF,
                                  psDdBufMapInfo->psDdStrContext->ui32StrId,
                                  IMG_NULL,
                                  &sCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    if (sCoreMsg.ui32Result != IMG_SUCCESS)
    {
        return sCoreMsg.ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                CORE_StreamSubmitUnit

******************************************************************************/
IMG_RESULT CORE_StreamSubmitUnit(
    IMG_UINT32              ui32StrId,
    VDECDD_sStrUnit       * psStrUnit
)
{
    IMG_RESULT              ui32Result;
    CORE_sCoreMsg *         psCoreMsg;

    /* Allocate a core message...*/
    VDEC_MALLOC(psCoreMsg);
    IMG_ASSERT(psCoreMsg != IMG_NULL);
    if (psCoreMsg == IMG_NULL)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
            "[SID=0x%08X] Failed to allocate memory for core message",
            ui32StrId);
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    /* Create the core message. */
    VDEC_BZERO(psCoreMsg);
    psCoreMsg->sStreamSubmitUnitMsg.psStrUnit = psStrUnit;

    /* Send message. */
    ui32Result = core_SendAsyncMsg(CORE_MSGID_STREAM_SUBMIT_UNIT,
                                   ui32StrId,
                                   IMG_NULL,
                                   psCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        IMG_FREE(psCoreMsg);
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              CORE_StreamSetOutputConfig

******************************************************************************/
IMG_RESULT CORE_StreamSetOutputConfig(
    IMG_UINT32              ui32StrId,
    VDEC_sStrOutputConfig * psStrOutputConfig,
    VDEC_sPictBufConfig   * psPictBufConfig
)
{
    IMG_RESULT     ui32Result;
    CORE_sCoreMsg  sCoreMsg;

    /* Create the core message. */
    VDEC_BZERO(&sCoreMsg);
    sCoreMsg.sStreamSetOutputConfigMsg.psStrOutputConfig = psStrOutputConfig;
    sCoreMsg.sStreamSetOutputConfigMsg.psPictBufConfig = psPictBufConfig;

    /* Send and wait for response. */
    ui32Result = core_SendSyncMsg(CORE_MSGID_STREAM_SET_OUTPUT_CONFIG,
                                  ui32StrId,
                                  IMG_NULL,
                                  &sCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    if (sCoreMsg.ui32Result != IMG_SUCCESS)
    {
        return sCoreMsg.ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              CORE_StreamFillPictBuf

******************************************************************************/
IMG_RESULT CORE_StreamFillPictBuf(
    IMG_UINT32              ui32BufMapId
)
{
    IMG_RESULT              ui32Result;
    VDECDD_sDdBufMapInfo  * psDdBufMapInfo;
    CORE_sCoreMsg         * psCoreMsg;

    /* Get access to map info context...*/
    ui32Result = RMAN_GetResource(ui32BufMapId, VDECDD_BUFMAP_TYPE_ID, (IMG_VOID **)&psDdBufMapInfo, IMG_NULL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Allocate a core message...*/
    VDEC_MALLOC(psCoreMsg);
    IMG_ASSERT(IMG_NULL != psCoreMsg);
    if (IMG_NULL == psCoreMsg)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
            "[SID=0x%08X] Failed to allocate memory for core message",
            psDdBufMapInfo->psDdStrContext->ui32StrId);

        return IMG_ERROR_OUT_OF_MEMORY;
    }

    /* Create the core message. */
    VDEC_BZERO(psCoreMsg);
    psCoreMsg->sStreamFillPictBufMsg.ui32BufMapId = ui32BufMapId;

    /* Send message. */
    ui32Result = core_SendAsyncMsg(CORE_MSGID_STREAM_FILL_PICT_BUF,
                                   psDdBufMapInfo->psDdStrContext->ui32StrId,
                                   IMG_NULL,
                                   psCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        IMG_FREE(psCoreMsg);
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                CORE_StreamFlush

******************************************************************************/
IMG_RESULT CORE_StreamFlush(
    IMG_UINT32              ui32StrId,
    IMG_BOOL                bDiscardRefs
)
{
    IMG_RESULT              ui32Result;
    CORE_sCoreMsg           sCoreMsg;

    /* Create the core message. */
    VDEC_BZERO(&sCoreMsg);
    sCoreMsg.sStreamFlushMsg.bDiscardRefs = bDiscardRefs;

    /* Send and wait for response. */
    ui32Result = core_SendSyncMsg(CORE_MSGID_STREAM_FLUSH,
                                  ui32StrId,
                                  IMG_NULL,
                                  &sCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    IMG_ASSERT(sCoreMsg.ui32Result == IMG_SUCCESS);
    if (sCoreMsg.ui32Result != IMG_SUCCESS)
    {
        return sCoreMsg.ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              CORE_StreamReleaseBufs

******************************************************************************/
IMG_RESULT CORE_StreamReleaseBufs(
    IMG_UINT32              ui32StrId,
    VDEC_eBufType           eBufType
)
{
    IMG_RESULT     ui32Result;
    CORE_sCoreMsg  sCoreMsg;

    /* Create the core message. */
    VDEC_BZERO(&sCoreMsg);
    sCoreMsg.sStreamReleaseBufsMsg.eBufType = eBufType;

    /* Send and wait for response. */
    ui32Result = core_SendSyncMsg(CORE_MSGID_STREAM_RELEASE_BUFS,
                                  ui32StrId,
                                  IMG_NULL,
                                  &sCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    IMG_ASSERT(sCoreMsg.ui32Result == IMG_SUCCESS);
    if (sCoreMsg.ui32Result != IMG_SUCCESS)
    {
        return sCoreMsg.ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              CORE_StreamSetBehaviourOnErrors

******************************************************************************/
IMG_RESULT CORE_StreamSetBehaviourOnErrors(
    IMG_UINT32              ui32StrId,
    VDEC_eErrorHandling     eErrorHandling
)
{
    IMG_RESULT     ui32Result;
    CORE_sCoreMsg  sCoreMsg;

    /* Create the core message. */
    VDEC_BZERO(&sCoreMsg);
    sCoreMsg.sStreamSetBehaviourOnErrorsMsg.eErrorHandling = eErrorHandling;

    /* Send and wait for response. */
    ui32Result = core_SendSyncMsg(CORE_MSGID_STREAM_SET_BEHAVIOUR_ON_ERRORS,
                                  ui32StrId,
                                  IMG_NULL,
                                  &sCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    IMG_ASSERT(sCoreMsg.ui32Result == IMG_SUCCESS);
    if (sCoreMsg.ui32Result != IMG_SUCCESS)
    {
        return sCoreMsg.ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              CORE_StreamGetStatus

******************************************************************************/
IMG_RESULT CORE_StreamGetStatus(
    IMG_UINT32              ui32StrId,
    VDECDD_sStrStatus *     psStrStatus
)
{
    IMG_RESULT           ui32Result;
    CORE_sCoreMsg        sCoreMsg;

    /* Create the core message. */
    VDEC_BZERO(&sCoreMsg);
    sCoreMsg.sStreamGetStatusMsg.psStrStatus = psStrStatus;

    /* Send and wait for response. */
    ui32Result = core_SendSyncMsg(CORE_MSGID_STREAM_GET_STATUS,
                                  ui32StrId,
                                  IMG_NULL,
                                  &sCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    IMG_ASSERT(sCoreMsg.ui32Result == IMG_SUCCESS);
    if (sCoreMsg.ui32Result != IMG_SUCCESS)
    {
        return sCoreMsg.ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                CORE_DevSchedule

******************************************************************************/
IMG_RESULT CORE_DevSchedule(
    VDECDD_sDdDevContext *  psDdDevContext
)
{
    IMG_RESULT              ui32Result;
    CORE_sCoreMsg *         psCoreMsg;

    /* Allocate a core message...*/
    VDEC_MALLOC(psCoreMsg);
    IMG_ASSERT(psCoreMsg != IMG_NULL);
    if (psCoreMsg == IMG_NULL)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
            "Failed to allocate memory for core message");

        return IMG_ERROR_OUT_OF_MEMORY;
    }

    /* Create the core message. */
    VDEC_BZERO(psCoreMsg);

    /* Send message. */
    ui32Result = core_SendAsyncMsg(CORE_MSGID_DEV_SCHEDULE,
                                   CORE_NO_STREAM_ID,
                                   psDdDevContext,
                                   psCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        IMG_FREE(psCoreMsg);
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              CORE_DevServiceTimeExpiry

******************************************************************************/
IMG_RESULT CORE_DevServiceTimeExpiry(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_UINT32              ui32CoreNum
)
{
    IMG_RESULT       ui32Result;
    CORE_sCoreMsg *  psCoreMsg;

    SYSOSKM_DisableInt();
    if ( LST_empty(&psDdDevContext->sHwMsgList) ) // we have used all our resources in the sHwMsgList
    {
        SYSOSKM_EnableInt();

        /* Allocate a core message...*/
        VDEC_MALLOC(psCoreMsg);
        IMG_ASSERT(psCoreMsg != IMG_NULL);
        if (psCoreMsg == IMG_NULL)
        {
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                "Failed to allocate memory for core message");

            return IMG_ERROR_OUT_OF_MEMORY;
        }
    }
    else
    {
        psCoreMsg = (CORE_sCoreMsg *)LST_removeHead(&psDdDevContext->sHwMsgList);
        SYSOSKM_EnableInt();

        IMG_ASSERT(psCoreMsg != IMG_NULL);
        if (psCoreMsg == IMG_NULL)
        {
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                "NULL Pointer extracted from the HW message list");

            return IMG_ERROR_OUT_OF_MEMORY;
        }
    }

    /* Create the core message. */
    VDEC_BZERO(psCoreMsg);
    psCoreMsg->sDevServiceTimeExpiryMsg.ui32CoreNum = ui32CoreNum;

    /* Send message. */
    ui32Result = core_SendAsyncMsg(CORE_MSGID_DEV_SERVICE_TIME_EXPIRY,
                                   CORE_NO_STREAM_ID,
                                   psDdDevContext,
                                   psCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        SYSOSKM_DisableInt();
        LST_add(&psDdDevContext->sHwMsgList, psCoreMsg);
        SYSOSKM_EnableInt();
        return ui32Result;
    }

    return ui32Result;
}

/*!
******************************************************************************

 @Function              CORE_DevReset

******************************************************************************/
IMG_RESULT CORE_DevReset(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_UINT32              ui32CoreNum,
    VDECDD_eResetReason     eResetReason
)
{
    IMG_RESULT       ui32Result;
    CORE_sCoreMsg *  psCoreMsg;

    SYSOSKM_DisableInt();
    if ( LST_empty(&psDdDevContext->sHwMsgList) ) // we have used all our resources in the sHwMsgList
    {
        SYSOSKM_EnableInt();

        IMG_ASSERT(!"Unable to find free HW message");
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    else
    {
        psCoreMsg = (CORE_sCoreMsg *)LST_removeHead(&psDdDevContext->sHwMsgList);
        SYSOSKM_EnableInt();

        IMG_ASSERT(psCoreMsg != IMG_NULL);
        if (psCoreMsg == IMG_NULL)
        {
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                "NULL Pointer extracted from the HW message list");

            return IMG_ERROR_OUT_OF_MEMORY;
        }
    }

    /* Create the core message. */
    VDEC_BZERO(psCoreMsg);
    psCoreMsg->sDevReset.eReason = eResetReason;
    psCoreMsg->sDevReset.ui32CoreNum = ui32CoreNum;

    /* Send message. */
    ui32Result = core_SendAsyncMsg(CORE_MSGID_DEV_RESET,
                                   CORE_NO_STREAM_ID,
                                   psDdDevContext,
                                   psCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        SYSOSKM_DisableInt();
        LST_add(&psDdDevContext->sHwMsgList, psCoreMsg);
        SYSOSKM_EnableInt();
    }

    return ui32Result;
}

/*!
******************************************************************************

 @Function              CORE_DevPostReplay

******************************************************************************/
IMG_RESULT CORE_DevReplay(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_UINT32              ui32CoreNum
)
{
    IMG_RESULT       ui32Result;
    CORE_sCoreMsg *  psCoreMsg;

    /* Allocate a core message...*/
    VDEC_MALLOC(psCoreMsg);
    IMG_ASSERT(psCoreMsg != IMG_NULL);
    if (psCoreMsg == IMG_NULL)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
            "Failed to allocate memory for core message");

        return IMG_ERROR_OUT_OF_MEMORY;
    }

    /* Create the core message. */
    VDEC_BZERO(psCoreMsg);
    psCoreMsg->sDevReplayMsg.ui32CoreNum = ui32CoreNum;

    /* Send message. */
    ui32Result = core_SendAsyncMsg(CORE_MSGID_DEV_REPLAY,
                                   CORE_NO_STREAM_ID,
                                   psDdDevContext,
                                   psCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        IMG_FREE(psCoreMsg);
        return ui32Result;
    }

    return ui32Result;
}

/*!
******************************************************************************

 @Function              CORE_DevSwInterrupt

******************************************************************************/
IMG_RESULT CORE_DevSwInterrupt(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_HANDLE              hDecServiceInt
)
{
    IMG_RESULT       ui32Result;
    CORE_sCoreMsg *  psCoreMsg;

    /* Allocate a core message...*/
    VDEC_MALLOC(psCoreMsg);
    IMG_ASSERT(psCoreMsg != IMG_NULL);
    if (psCoreMsg == IMG_NULL)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
            "Failed to allocate memory for core message");

        return IMG_ERROR_OUT_OF_MEMORY;
    }

    /* Create the core message. */
    VDEC_BZERO(psCoreMsg);
    psCoreMsg->sDevSwInterruptMsg.hDecServiceInt = hDecServiceInt;

    /* Send message. */
    ui32Result = core_SendAsyncMsg(CORE_MSGID_DEV_SW_INTERRUPT,
                                   CORE_NO_STREAM_ID,
                                   psDdDevContext,
                                   psCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        IMG_FREE(psCoreMsg);
        return ui32Result;
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              CORE_DevHwInterrupt

******************************************************************************/
IMG_RESULT CORE_DevHwInterrupt(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_HANDLE              hDecServiceInt
)
{
    IMG_RESULT       ui32Result;
    CORE_sCoreMsg *  psCoreMsg;

    SYSOSKM_DisableInt();
    if ( LST_empty(&psDdDevContext->sHwMsgList) ) // we have used all our resources in the sHwMsgList
    {
        SYSOSKM_EnableInt();

        /* Allocate a core message...*/
        VDEC_MALLOC(psCoreMsg);
        IMG_ASSERT(psCoreMsg != IMG_NULL);
        if (psCoreMsg == IMG_NULL)
        {
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                "Failed to allocate memory for core message");

            return IMG_ERROR_OUT_OF_MEMORY;
        }
    }
    else
    {
        psCoreMsg = (CORE_sCoreMsg *)LST_removeHead(&psDdDevContext->sHwMsgList);
        SYSOSKM_EnableInt();
        IMG_ASSERT(psCoreMsg != IMG_NULL);
        if (psCoreMsg == IMG_NULL)
        {
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                "NULL Pointer extracted from the HW message list");

            return IMG_ERROR_OUT_OF_MEMORY;
        }
    }

    /* Create the core message. */
    VDEC_BZERO(psCoreMsg);
    psCoreMsg->sDevHwInterruptMsg.hDecServiceInt = hDecServiceInt;

    /* Send message. */
    ui32Result = core_SendAsyncMsg(CORE_MSGID_DEV_HW_INTERRUPT,
                                   CORE_NO_STREAM_ID,
                                   psDdDevContext,
                                   psCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        SYSOSKM_DisableInt();
        LST_add(&psDdDevContext->sHwMsgList, psCoreMsg);
        SYSOSKM_EnableInt();
        return ui32Result;
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              CORE_DevSwInterruptPicDiscarded

******************************************************************************/
IMG_RESULT CORE_DevSwInterruptPicDiscarded(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_HANDLE              hDecServiceInt
)
{
    IMG_RESULT       ui32Result;
    CORE_sCoreMsg *  psCoreMsg;

    SYSOSKM_DisableInt();
    if ( LST_empty(&psDdDevContext->sHwMsgList) ) // we have used all our resources in the sHwMsgList
    {
        SYSOSKM_EnableInt();
        /* Allocate a core message...*/
        VDEC_MALLOC(psCoreMsg);
        IMG_ASSERT(psCoreMsg != IMG_NULL);
        if (psCoreMsg == IMG_NULL)
        {
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                "Failed to allocate memory for core message");

            return IMG_ERROR_OUT_OF_MEMORY;
        }
    }
    else
    {
        psCoreMsg = (CORE_sCoreMsg *)LST_removeHead(&psDdDevContext->sHwMsgList);
        SYSOSKM_EnableInt();
        IMG_ASSERT(psCoreMsg != IMG_NULL);
        if (psCoreMsg == IMG_NULL)
        {
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                "NULL Pointer extracted from the HW message list");

            return IMG_ERROR_OUT_OF_MEMORY;
        }
    }

    /* Create the core message. */
    VDEC_BZERO(psCoreMsg);
    psCoreMsg->sDevSwInterruptPicDiscardedMsg.hDecServiceInt = hDecServiceInt;

    /* Send message. */
    ui32Result = core_SendAsyncMsg(CORE_MSGID_DEV_SW_INTERRUPT_PIC_DISCARDED,
                                   CORE_NO_STREAM_ID,
                                   psDdDevContext,
                                   psCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        SYSOSKM_DisableInt();
        LST_add(&psDdDevContext->sHwMsgList, psCoreMsg);
        SYSOSKM_EnableInt();
        return ui32Result;
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              CORE_DevPowerPreS5

******************************************************************************/
IMG_VOID CORE_DevPowerPreS5(
    VDECDD_sDdDevContext *  psDdDevContext
)
{
    IMG_RESULT     ui32Result;
    CORE_sCoreMsg  sCoreMsg;

    /* Create the core message. */
    VDEC_BZERO(&sCoreMsg);

    /* Send and wait for response. */
    ui32Result = core_SendSyncMsg(CORE_MSGID_DEV_POWER_PRE_S5,
                                  CORE_NO_STREAM_ID,
                                  psDdDevContext,
                                  &sCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    IMG_ASSERT(sCoreMsg.ui32Result == IMG_SUCCESS);
}


/*!
******************************************************************************

 @Function              CORE_DevPowerPostS0

******************************************************************************/
IMG_VOID CORE_DevPowerPostS0(
    VDECDD_sDdDevContext *  psDdDevContext
)
{
    IMG_RESULT     ui32Result;
    CORE_sCoreMsg  sCoreMsg;

    /* Create the core message. */
    VDEC_BZERO(&sCoreMsg);

    /* Send and wait for response. */
    ui32Result = core_SendSyncMsg(CORE_MSGID_DEV_POWER_POST_S0,
                                  CORE_NO_STREAM_ID,
                                  psDdDevContext,
                                  &sCoreMsg);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    IMG_ASSERT(sCoreMsg.ui32Result == IMG_SUCCESS);
}


/*!
******************************************************************************

 @Function              core_ConnectionCreate

******************************************************************************/
static IMG_RESULT core_ConnectionCreate(
    VDECDD_sDdDevContext      * psDdDevContext,
    VDECDD_sDdConnContext    ** ppsDdConnContext
)
{
    IMG_RESULT               ui32Result;
    VDECDD_sDdConnContext *  psDdConnContext;

    /* Allocate a device connection context structure...*/
    VDEC_MALLOC(psDdConnContext);
    IMG_ASSERT(psDdConnContext != IMG_NULL);
    if (psDdConnContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
            "Failed to allocate memory for DD connection context");
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psDdConnContext);

    /* Initialise connection context. */
    LST_init(&psDdConnContext->sStreamList);
    psDdConnContext->psDdDevContext = psDdDevContext;

    /* Create connection resource bucket...*/
    ui32Result = RMAN_CreateBucket(&psDdConnContext->hResBHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    /* Add to list of connections...*/
    LST_add(&psDdDevContext->sConnList, psDdConnContext);

    /* Return address of connection context */
    *ppsDdConnContext = psDdConnContext;

    /* Return success...*/
    return IMG_SUCCESS;

error:
    if (psDdConnContext)
    {
        if (psDdConnContext->hResBHandle)
        {
            RMAN_DestroyBucket(psDdConnContext->hResBHandle);
        }
        IMG_FREE(psDdConnContext);
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              core_ConnectionDestroy

******************************************************************************/
static IMG_RESULT core_ConnectionDestroy(
    IMG_UINT32      ui32ConnId
)
{
    /* If we have a connection ID...*/
    if (ui32ConnId)
    {
        VDECDD_sDdConnContext * psDdConnContext;
        IMG_RESULT              ui32Result;

        ui32Result = core_GetConnContext(ui32ConnId, &psDdConnContext);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        // If there are active streams on this connection.
        if (!LST_empty(&psDdConnContext->sStreamList))
        {
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                   "Connection destroyed with streams still active");

            // Stop the device so that events for this process are not received by host
            // and, as importantly,
            //DECODER_ResetCores(psDdConnContext->psDdDevContext->hDecoderContext);
        }

        /* Remove from list of connections...*/
        LST_remove(&psDdConnContext->psDdDevContext->sConnList, psDdConnContext);

        /* Free context resources...*/
        RMAN_DestroyBucket(psDdConnContext->hResBHandle);

        // Replay the pending items on each core.
        //DECODER_Replay(psDdConnContext->psDdDevContext->hDecoderContext);

        IMG_FREE(psDdConnContext);
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              core_fnFreeStream

******************************************************************************/
static IMG_VOID core_RemoveStreamMessages(
    LST_T   * psCoreMsgList,
    IMG_UINT32 ui32StrId
)
{
    LST_T               sCurrentStrMsgList;
    CORE_sCoreMsg     * psCoreMsg, * psNextCoreMsg;

    /* Initialise list of core messages for current stream*/
    LST_init(&sCurrentStrMsgList);

    /* Fill it, protecting the core message list*/
    SYSOSKM_DisableInt();
    psCoreMsg = LST_first(psCoreMsgList);
    while (psCoreMsg)
    {
        if (psCoreMsg->ui32StrId == ui32StrId)
        {
            LST_remove(psCoreMsgList, psCoreMsg);
            LST_addHead(&sCurrentStrMsgList,psCoreMsg);
        }

        psCoreMsg = LST_next(psCoreMsg);
    }
    SYSOSKM_EnableInt();

    /* Fill it, protecting the core message list*/
    psCoreMsg = LST_first(&sCurrentStrMsgList);
    while (psCoreMsg)
    {
        psNextCoreMsg = LST_next(psCoreMsg);

        if(psCoreMsg->hEventHandle != IMG_NULL)
        {
            /* Signal completion. */
            SYSOSKM_SignalEventObject(psCoreMsg->hEventHandle);
        }
        else
        {
            /* Free the message structure. */
            IMG_FREE(psCoreMsg);
        }

        psCoreMsg = psNextCoreMsg;
    }
}

/*!
******************************************************************************

 @Function              core_fnFreeStream

******************************************************************************/
static IMG_VOID core_fnFreeStream (
    IMG_VOID *  pvParam
)
{
    IMG_RESULT              ui32Result;
    VDECDD_sDdStrContext  * psDdStrContext;
    VDECDD_sDdDevContext  * psDdDevContext;

    // Validate input arguments.
    IMG_ASSERT(pvParam);

    psDdStrContext = (VDECDD_sDdStrContext *)pvParam;
    IMG_ASSERT(psDdStrContext);
    if (IMG_NULL != psDdStrContext)
    {
        if (IMG_NULL != psDdStrContext->psDdConnContext)
        {
            VDECDD_sCallBackInfo  * psCallBackInfo;

            psDdDevContext = psDdStrContext->psDdConnContext->psDdDevContext;
            IMG_ASSERT(psDdDevContext);

            /* Remove status file in debug file system */
            if (psDdStrContext->hStatusDgFile)
            {
                SYSOSKM_RemoveDebugFile(psDdStrContext->hStatusDgFile);
                psDdStrContext->hStatusDgFile = IMG_NULL;
            }

            /* Destroy stream in the Scheduler. */
            if (psDdStrContext->hSchedulerContext)
            {
                ui32Result = SCHEDULER_StreamDestroy(psDdStrContext->hSchedulerContext);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                psDdStrContext->hSchedulerContext = IMG_NULL;
            }

            /* Destroy stream in the Decoder. */
            if (psDdStrContext->hDecoderContext)
            {
                ui32Result = DECODER_StreamDestroy(psDdStrContext->hDecoderContext);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                psDdStrContext->hDecoderContext = IMG_NULL;
            }

            /* Destroy stream in the Plant. */
            if (psDdStrContext->hPlantContext)
            {
                ui32Result = PLANT_StreamDestroy(psDdStrContext->hPlantContext);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                psDdStrContext->hPlantContext = IMG_NULL;
            }

            /* Destroy the MMU context for this stream. */
            if (psDdStrContext->hMmuStrHandle)
            {
                ui32Result = MMU_StreamDestroy(psDdStrContext->hMmuStrHandle);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                psDdStrContext->hMmuStrHandle = IMG_NULL;
            }

            /* Destroy the sync object...*/
            if (psDdStrContext->hEventHandle)
            {
                SYSOSKM_DestroyEventObject(psDdStrContext->hEventHandle);
                psDdStrContext->hEventHandle = IMG_NULL;
            }

            /* Destroy the stream resources. */
            if (psDdStrContext->hResBHandle)
            {
                RMAN_DestroyBucket(psDdStrContext->hResBHandle);
                psDdStrContext->hResBHandle = IMG_NULL;
            }

            /* Remove all messages for this stream from the core message list.
               and signal to all waiting threads. */
            core_RemoveStreamMessages(&psDdDevContext->sCoreMsgList, psDdStrContext->ui32StrId);

            /* Clear the event callback list. */
            psCallBackInfo = LST_removeHead(&psDdStrContext->sEventCbList);
            while (psCallBackInfo != IMG_NULL)
            {
                IMG_FREE(psCallBackInfo);
                psCallBackInfo = LST_removeHead(&psDdStrContext->sEventCbList);
            }

            // Remove stream context from connection.
            LST_remove(&psDdStrContext->psDdConnContext->sStreamList, psDdStrContext);
        }

        // Free stream context.
        IMG_FREE(psDdStrContext);
    }
}


/*!
******************************************************************************

 @Function              core_StreamCreate

******************************************************************************/
static IMG_RESULT core_StreamCreate(
    IMG_UINT32              ui32ConnId,
    VDEC_sStrConfigData *   psStrConfigData,
    IMG_VOID *              pvStrCbParam,
    IMG_UINT32 *            pui32StrId
)
{
    IMG_RESULT                  ui32Result;
    VDECDD_sDdStrContext      * psDdStrContext;
    VDECDD_sDdConnContext     * psDdConnContext;
    VDECDD_sSuppCheck           sSuppCheck;
    IMG_CHAR                    acDebugFileName[24];

    // Validate input arguments.
    IMG_ASSERT(ui32ConnId);
    IMG_ASSERT(psStrConfigData);
    IMG_ASSERT(pvStrCbParam);
    IMG_ASSERT(pui32StrId);

    /* Allocate a stream context...*/
    VDEC_MALLOC(psDdStrContext);
    IMG_ASSERT(psDdStrContext != IMG_NULL);
    if (psDdStrContext == IMG_NULL)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
            "Failed to allocate memory for DD stream context");
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psDdStrContext);

    /* Setup stream context. We need at least the Connection context, because
       if the stream is not supported it will try to destroy the context using it. */
    ui32Result = core_GetConnContext(ui32ConnId, &psDdStrContext->psDdConnContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    psDdConnContext = psDdStrContext->psDdConnContext;

    // Check stream configuration.
    VDEC_BZERO(&sSuppCheck);
    ui32Result = core_CheckDecoderSupport(psDdConnContext->psDdDevContext,
                                          psStrConfigData,
                                          IMG_NULL, IMG_NULL,
                                          IMG_NULL, &sSuppCheck);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    if (core_IsUnsupported(&sSuppCheck.sUnSupportedFlags))
    {
        ui32Result = IMG_ERROR_NOT_SUPPORTED;
        goto error;
    }

    /* Ensure the resource manager is initialised...*/
    ui32Result = RMAN_Initialise();
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    /* Create a bucket for the resources...*/
    ui32Result = RMAN_CreateBucket(&psDdStrContext->hResBHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    /* Register the stream as a connection resource...*/
    ui32Result = RMAN_RegisterResource(psDdConnContext->hResBHandle, VDECDD_STREAM_TYPE_ID,
                                        core_fnFreeStream, psDdStrContext,
                                        &psDdStrContext->hResHandle, &psDdStrContext->ui32StrId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    IMG_ASSERT(psStrConfigData->eVidStd < VDEC_STD_MAX);
    REPORT(REPORT_MODULE_CORE,
           REPORT_INFO,
           "[SID=0x%08X]: VidStd:%d [%s], BstrFmt:%d, UsrId:%u, UpdateYUV:%s, LowLatency:%s, BwEff:%s, Secure:%s, DisableMvc:%s, FullScan:%s",
           psDdStrContext->ui32StrId,
           psStrConfigData->eVidStd,
           gapszVideoStandard[psStrConfigData->eVidStd],
           psStrConfigData->eBstrFormat,
           psStrConfigData->ui32UserStrId,
           (psStrConfigData->bUpdateYUV) ? "y" : "n",
           (psStrConfigData->bLowLatencyMode) ? "y" : "n",
           (psStrConfigData->bBandwidthEfficient) ? "y" : "n",
           (psStrConfigData->bSecureStream) ? "y" : "n",
           (psStrConfigData->bDisableMvc) ? "y" : "n",
           (psStrConfigData->bFullScan) ? "y" : "n");

    /* Create stream in the Decoder. */
    /* NOTE: this must take place first since it creates the MMU context. */
    ui32Result = DECODER_StreamCreate(psDdConnContext->psDdDevContext->hDecoderContext,
                                     *psStrConfigData,
                                      &psDdStrContext->hMmuStrHandle,
                                      psDdStrContext/*pvStrCbParam*/,
                                      psDdStrContext,
                                      &psDdStrContext->hDecoderContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    /* Create stream in the Plant. */
    ui32Result = PLANT_StreamCreate(psStrConfigData,
                                    psDdStrContext->hMmuStrHandle,
                                    psDdStrContext,
                                    &psDdStrContext->hPlantContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    /* Create stream in the Scheduler. */
    ui32Result = SCHEDULER_StreamCreate(psDdConnContext->psDdDevContext->hSchedulerContext,
                                        psDdStrContext->ui32StrId,
                                        psStrConfigData,
                                        psDdStrContext,
                                        &psDdStrContext->hSchedulerContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    /* Setup stream context...*/
    psDdStrContext->sStrConfigData  = *psStrConfigData;
    psDdStrContext->pvStrCbParam    = pvStrCbParam;
    LST_init(&psDdStrContext->sEventCbList);

    /* Create sync object...*/
    ui32Result = SYSOSKM_CreateEventObject(&psDdStrContext->hEventHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    sprintf(acDebugFileName, "status_%08X", psDdStrContext->ui32StrId);
    psDdStrContext->hStatusDgFile =
        SYSOSKM_CreateDebugFile(acDebugFileName,
                               psDdStrContext,
                               status_open_callback);

    /* Add to list of streams...*/
    LST_add(&psDdConnContext->sStreamList, psDdStrContext);

    DEBUG_REPORT(REPORT_MODULE_CORE,
           "[SID=0x%08X] New stream created [USERSID=0x%08X] ",
           psDdStrContext->ui32StrId,
           psStrConfigData->ui32UserStrId);

    *pui32StrId = psDdStrContext->ui32StrId;

    /* Return success...*/
    return IMG_SUCCESS;

error:
    if (psDdStrContext->hResHandle)
    {
        /* Free the stream context via RMAN (if registered) */
        RMAN_FreeResource(psDdStrContext->hResHandle);
    }
    else
    {
        // Not registered with RMAN so just call the free function directly.
        core_fnFreeStream(psDdStrContext);
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              core_StreamDestroy

******************************************************************************/
static IMG_RESULT core_StreamDestroy(
    VDECDD_sDdStrContext  * psDdStrContext,
    IMG_HANDLE              hDestroyedEvent,
    IMG_UINT32            * pui32ConnId
)
{
    IMG_RESULT  ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdStrContext);
    IMG_ASSERT(hDestroyedEvent);

    if (pui32ConnId)
    {
        *pui32ConnId = psDdStrContext->psDdConnContext->ui32ConnId;
    }

    // Stop the stream from Scheduler to prevent any more units from being processed.
    ui32Result = core_StreamStop(psDdStrContext,
                                 VDEC_STOPPOINT_NOW,
                                 0, 0);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    // Destroy stream if idle otherwise wait and do it later.
    if (DECODER_StreamIsIdle(psDdStrContext->hDecoderContext))
    {
        /* Free the stream context...*/
        RMAN_FreeResource(psDdStrContext->hResHandle);

        // Signal (to any UM thread waiting) that stream is now destroyed.
        IMG_ASSERT(hDestroyedEvent);
        SYSOSKM_SignalEventObject(hDestroyedEvent);
    }
    else
    {
        psDdStrContext->hDestroyedEvent = hDestroyedEvent;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              core_StreamPlay

******************************************************************************/
static IMG_RESULT core_StreamPlay(
    VDECDD_sDdStrContext *  psDdStrContext,
    VDEC_ePlayMode          ePlayMode,
    VDEC_eStopPoint         eStopPoint,
    IMG_UINT32              ui32StopPointQual
)
{
    IMG_RESULT  ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdStrContext);
    IMG_ASSERT(ePlayMode < VDEC_PLAYMODE_MAX);
    IMG_ASSERT(eStopPoint < VDEC_STOPPOINT_MAX);

    /* Ensure we are stopped. */
    IMG_ASSERT(psDdStrContext->eDdStrState == VDECDD_STRSTATE_STOPPED);

    /* Set play mode etc. */
    psDdStrContext->ePlayMode = ePlayMode;
    psDdStrContext->eStopPoint = eStopPoint;
    psDdStrContext->ui32StopPointQual = ui32StopPointQual;

    /* Check play mode. */
    switch (ePlayMode)
    {
    case VDEC_PLAYMODE_PARSE_ONLY:
    case VDEC_PLAYMODE_NORMAL_DECODE:
        break;

    default:
        IMG_ASSERT(IMG_FALSE);
    }

    if (psDdStrContext->psDdConnContext->psDdDevContext->eDecodeLevel == VDECDD_DECODELEVEL_SCHEDULER)
    {
        ePlayMode = VDEC_PLAYMODE_PARSE_ONLY;
    }

    /* Set "playing". */
    psDdStrContext->eDdStrState = VDECDD_STRSTATE_PLAYING;

    ui32Result = SCHEDULER_StreamPlay(psDdStrContext->hSchedulerContext,
                                      ePlayMode,
                                      eStopPoint,
                                      (psDdStrContext->sDispPictBuf.sRendInfo.ui32RenderedSize) ?
                                           &psDdStrContext->sDispPictBuf : IMG_NULL,
                                      (psDdStrContext->bStrOutputConfigured) ? &psDdStrContext->sOutputConfig : IMG_NULL);
    IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              core_StreamStop

******************************************************************************/
static IMG_RESULT core_StreamStop(
    VDECDD_sDdStrContext *  psDdStrContext,
    VDEC_eStopPoint         eStopPoint,
    IMG_UINT32              ui32StopPointQual,
    IMG_UINT32              ui32Error
)
{
    IMG_RESULT  ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdStrContext);
    IMG_ASSERT(eStopPoint < VDEC_STOPPOINT_MAX);

    // Disregard this stop request if the stream is currently stopped or being stopped.
    if (psDdStrContext->eDdStrState == VDECDD_STRSTATE_PLAYING)
    {
        ui32Result = SCHEDULER_StreamStop(psDdStrContext->hSchedulerContext, eStopPoint, ui32Error);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              core_fnFreeMapped

******************************************************************************/
static IMG_VOID core_fnFreeMapped (
    IMG_VOID *  pvParam
)
{
    VDECDD_sDdBufMapInfo *  psDdBufMapInfo = (VDECDD_sDdBufMapInfo *)pvParam;

    // Validate input arguments.
    IMG_ASSERT(pvParam);

    /* Do not free the MMU mapping. It is handled by talmmu code. */
    IMG_FREE(psDdBufMapInfo);
}


/*!
******************************************************************************

 @Function              core_StreamSetPictBufConfig

******************************************************************************/
static IMG_RESULT core_StreamSetPictBufConfig(
    VDECDD_sDdStrContext  * psDdStrContext,
    VDEC_sPictBufConfig   * psPictBufConfig
)
{
    IMG_RESULT  ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdStrContext);
    IMG_ASSERT(psPictBufConfig);

    // If there are no buffers mapped or the configuration is not set (only done
    // when reconfiguring output) then calculate the output picture buffer layout.
    if (psDdStrContext->sMapBufInfo.ui32NumBufs == 0 ||
        psDdStrContext->sDispPictBuf.sBufConfig.ui32BufSize == 0)
    {
        VDECDD_sSuppCheck   sSuppCheck;
        VDECDD_sDdPictBuf   sDispPictBuf;

        VDEC_BZERO(&sDispPictBuf);

        sDispPictBuf.sBufConfig = *psPictBufConfig;

        // Ensure that the external picture buffer information is compatible with
        // the hardware and convert to internal driver representation.
        ui32Result = VDECDDUTILS_ConvertBufferConfig(&psDdStrContext->sStrConfigData,
                                                     &sDispPictBuf.sBufConfig,
                                                     &psDdStrContext->sComSequHdrInfo,
                                                     &sDispPictBuf.sRendInfo);
        IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        // Provide the current state for validation against the new buffer configuration.
        VDEC_BZERO(&sSuppCheck);
        sSuppCheck.psDispPictBuf = &sDispPictBuf;
        if (psDdStrContext->sComSequHdrInfo.sMaxFrameSize.ui32Width)
        {
            sSuppCheck.psComSequHdrInfo = &psDdStrContext->sComSequHdrInfo;
        }
        if (psDdStrContext->bStrOutputConfigured)
        {
            sSuppCheck.psOutputConfig = &psDdStrContext->sOutputConfig;
        }

        ui32Result = core_CheckDecoderSupport(
            psDdStrContext->psDdConnContext->psDdDevContext,
            &psDdStrContext->sStrConfigData,
            &psDdStrContext->sPrevComSequHdrInfo,
            &psDdStrContext->sPrevPictHdrInfo,
            &psDdStrContext->sMapBufInfo,
            &sSuppCheck);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        // If stop flags were requested, set them in the Scheduler.
        if (sSuppCheck.ui32StopFlags)
        {
            IMG_UINT32 ui32TempResult;

            ui32TempResult = core_StreamSignalStopStatus(psDdStrContext, sSuppCheck.ui32StopFlags);
            IMG_ASSERT(ui32TempResult == IMG_SUCCESS);
        }

        if (core_IsUnsupported(&sSuppCheck.sUnSupportedFlags))
        {
            ui32Result = IMG_ERROR_NOT_SUPPORTED;
            goto error;
        }

        psDdStrContext->sDispPictBuf = sDispPictBuf;
    }
    else
    {
        // Check configuration of buffer matches that for stream
        // including any picture buffers that are already mapped.
        if (IMG_MEMCMP(psPictBufConfig, &psDdStrContext->sDispPictBuf.sBufConfig, sizeof(*psPictBufConfig)))
        {
            // Configuration of output buffer doesn't match the rest.
            REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                    "[SID=0x%08X] All output buffers must have the same properties.",
                    psDdStrContext->ui32StrId);
            // ui32Result = IMG_ERROR_INVALID_PARAMETERS;
            // goto error;
        }
    }

    /* Return success...*/
    return IMG_SUCCESS;

error:
    return ui32Result;
}


/*!
******************************************************************************

 @Function              core_StreamMapBuf

******************************************************************************/
static IMG_RESULT core_StreamMapBuf(
    VDECDD_sDdStrContext *  psDdStrContext,
    IMG_VOID *              pvBufCbParam,
    VDEC_eBufType           eBufType,
    VDEC_sBufInfo *         psBufInfo,
    IMG_UINT32 *            pui32BufMapId
)
{
    IMG_RESULT              ui32Result;
    VDECDD_sDdBufMapInfo *  psDdBufMapInfo = IMG_NULL;

    // Validate input arguments.
    IMG_ASSERT(psDdStrContext);
    IMG_ASSERT(eBufType < VDEC_BUFTYPE_MAX);
    IMG_ASSERT(psBufInfo);
    IMG_ASSERT(pui32BufMapId);

    /* Allocate an active stream unit...*/
    VDEC_MALLOC(psDdBufMapInfo);
    IMG_ASSERT(psDdBufMapInfo != IMG_NULL);
    if (psDdBufMapInfo == IMG_NULL)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
            "[SID=0x%08X] Failed to allocate memory for DD buffer map information",
            psDdStrContext->ui32StrId);

        return IMG_ERROR_OUT_OF_MEMORY;
    }
    VDEC_BZERO(psDdBufMapInfo);

    /* Save the stream context etc. */
    psDdBufMapInfo->psDdStrContext    = psDdStrContext;
    psDdBufMapInfo->pvBufCbParam      = pvBufCbParam;
    psDdBufMapInfo->eBufType          = eBufType;

    ui32Result = PALLOCKM_GetPagesHandle(psBufInfo->ui32ExtImportId, &psDdBufMapInfo->hExtImportHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
        goto error;

    /* Register the allocation as a stream resource...*/
    ui32Result = RMAN_RegisterResource(psDdStrContext->hResBHandle, VDECDD_BUFMAP_TYPE_ID,
                                       core_fnFreeMapped, psDdBufMapInfo,
                                       &psDdBufMapInfo->hResHandle, pui32BufMapId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    if (eBufType == VDEC_BUFTYPE_PICTURE)
    {
        if (psDdStrContext->sMapBufInfo.ui32NumBufs == 0)
        {
            psDdStrContext->sMapBufInfo.ui32BufSize = psBufInfo->ui32BufSize;
            psDdStrContext->sMapBufInfo.eTileScheme = psBufInfo->sPictBufConfig.eTileScheme;
            psDdStrContext->sMapBufInfo.bByteInterleave = psBufInfo->sPictBufConfig.bByteInterleave;

            DEBUG_REPORT(REPORT_MODULE_CORE,
                         "[SID=0x%08X] Mapped Buffer size: %d (bytes)",
                         psDdStrContext->ui32StrId,
                         psBufInfo->ui32BufSize);
        }
        else
        {
            //Enabling Android StoreMetaDataInBuffers Index requires that Buffers be mapped Dynamically.
            //Removing the check for number of buffers mapped and compatible size with previously mapped buffers.

            /* Check that the buffer is compatible with those already mapped for stream. */
            /*if (psBufInfo->ui32BufSize != psDdStrContext->sMapBufInfo.ui32BufSize)
            {
                REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                    "[SID=0x%08X] Buffer cannot be mapped since its size (%d bytes) is not the same as buffers already mapped (%d bytes)",
                    psDdStrContext->ui32StrId,
                    psBufInfo->ui32BufSize,
                    psDdStrContext->sMapBufInfo.ui32BufSize);
                ui32Result = IMG_ERROR_INVALID_PARAMETERS;
                goto error;
            }*/

            // Same tile scheme should be used.
            if (psBufInfo->sPictBufConfig.eTileScheme != psDdStrContext->sMapBufInfo.eTileScheme)
            {
                REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                    "[SID=0x%08X] Buffer cannot be mapped since its tile scheme is not the same as buffers already mapped",
                    psDdStrContext->ui32StrId);
                ui32Result = IMG_ERROR_INVALID_PARAMETERS;
                goto error;
            }

            // Same byte interleaved setting should be used.
            // Convert to actual bools by comparing with zero.
            if ((psBufInfo->sPictBufConfig.bByteInterleave > 0) != (psDdStrContext->sMapBufInfo.bByteInterleave > 0))
            {
                REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                    "[SID=0x%08X] Buffer cannot be mapped since its byte interleave value (%s) is not the same as buffers already mapped (%s)",
                    psDdStrContext->ui32StrId,
                    (psBufInfo->sPictBufConfig.bByteInterleave) ? "ON" : "OFF",
                    (psDdStrContext->sMapBufInfo.bByteInterleave) ? "ON" : "OFF");
                ui32Result = IMG_ERROR_INVALID_PARAMETERS;
                goto error;
            }
        }

        /* Configure the buffer...*/
        ui32Result = core_StreamSetPictBufConfig(psDdStrContext, &psBufInfo->sPictBufConfig);
        IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }
    }

    /* Map heap from VDEC to MMU. */
    switch (eBufType)
    {
    case VDEC_BUFTYPE_BITSTREAM:
        psDdBufMapInfo->eMmuHeapId = MMU_HEAP_BITSTREAM_BUFFERS;
        break;

    case VDEC_BUFTYPE_PICTURE:
        MMU_GetHeap(psBufInfo->sPictBufConfig.eTileScheme,
                    psBufInfo->sPictBufConfig.aui32Stride[VDEC_PLANE_VIDEO_Y],
                    &psDdBufMapInfo->eMmuHeapId);
        break;

    default:
        IMG_ASSERT(IMG_FALSE);
    }

    /* Ensure the address of the buffer is at least page aligned. */
    IMG_ASSERT(((IMG_UINTPTR)psBufInfo->pvCpuLinearAddr & (DEV_MMU_PAGE_SIZE-1)) == 0);

    /* Map this buffer into the MMU. */
    ui32Result = MMU_StreamMapExt(psDdStrContext->hMmuStrHandle,
                                  (MMU_eHeapId)psDdBufMapInfo->eMmuHeapId,
                                  psBufInfo->ui32BufSize,
                                  DEV_MMU_PAGE_SIZE,
                                  psBufInfo->pvCpuLinearAddr,
                                  psDdBufMapInfo->hExtImportHandle,
                                  &psDdBufMapInfo->sDdBufInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error;
    }

    if (eBufType == VDEC_BUFTYPE_PICTURE)
    {
        psDdStrContext->sMapBufInfo.ui32NumBufs++;
    }

    psDdBufMapInfo->sDdBufInfo.eMemPool =
        (psDdBufMapInfo->sDdBufInfo.eMemAttrib & SYS_MEMATTRIB_SECURE) ?
        psDdStrContext->psDdConnContext->psDdDevContext->eSecurePool :
        psDdStrContext->psDdConnContext->psDdDevContext->eInsecurePool;

    // Initialise the reference count to indicate that the client still holds the buffer.
    psDdBufMapInfo->sDdBufInfo.ui32RefCount = 1;

    /* Return success...*/
    return IMG_SUCCESS;

error:
    if (psDdBufMapInfo)
    {
        if (IMG_NULL != psDdBufMapInfo->hResHandle)
        {
            RMAN_FreeResource(psDdBufMapInfo->hResHandle);
        }
        else
        {
            IMG_FREE(psDdBufMapInfo);
        }
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              core_StreamUnmapBuf

******************************************************************************/
static IMG_RESULT core_StreamUnmapBuf(
    VDECDD_sDdStrContext *  psDdStrContext,
    VDECDD_sDdBufMapInfo *  psDdBufMapInfo
)
{
    IMG_RESULT ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdStrContext);
    IMG_ASSERT(psDdBufMapInfo);


    DEBUG_REPORT(REPORT_MODULE_CORE,
        "UNMAP: PM [0x%p] --> VM [0x%08X - 0x%08X] (%d bytes)",
        psDdBufMapInfo->sDdBufInfo.pvCpuVirt,
        psDdBufMapInfo->sDdBufInfo.ui32DevVirt,
        psDdBufMapInfo->sDdBufInfo.ui32DevVirt + psDdBufMapInfo->sDdBufInfo.ui32BufSize,
        psDdBufMapInfo->sDdBufInfo.ui32BufSize);

    /* Buffer should only be held by the client. */
    IMG_ASSERT(psDdBufMapInfo->sDdBufInfo.ui32RefCount == 1);
    if (psDdBufMapInfo->sDdBufInfo.ui32RefCount != 1)
    {
        return IMG_ERROR_MEMORY_IN_USE;
    }
    else
    {
        psDdBufMapInfo->sDdBufInfo.ui32RefCount = 0;

        if (psDdBufMapInfo->eBufType == VDEC_BUFTYPE_PICTURE)
        {
            // Remove this picture buffer from the Scheduler.
            ui32Result = SCHEDULER_StreamRemovePictureBuffer(psDdStrContext->hSchedulerContext,
                                                            psDdBufMapInfo);
            IMG_ASSERT(ui32Result == IMG_SUCCESS || ui32Result == IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE );
            if (IMG_SUCCESS != ui32Result && IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE != ui32Result )
            {
                return ui32Result;
            }

            psDdBufMapInfo->psDdStrContext->sMapBufInfo.ui32NumBufs--;

            // Clear some state if there are no more mapped buffers.
            if (psDdStrContext->sMapBufInfo.ui32NumBufs == 0)
            {
                psDdStrContext->sMapBufInfo.ui32BufSize = 0;
                psDdStrContext->sMapBufInfo.eTileScheme = VDEC_TS_NONE;
                psDdStrContext->sMapBufInfo.bByteInterleave = IMG_FALSE;
            }
        }

        /*Unmap this buffer from the MMU. */
        ui32Result = MMU_FreeMem(&psDdBufMapInfo->sDdBufInfo);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (IMG_SUCCESS != ui32Result)
        {
            return ui32Result;
        }

        /* Free buffer map info. */
        RMAN_FreeResource(psDdBufMapInfo->hResHandle);
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                core_StreamSubmitUnit

******************************************************************************/
static IMG_RESULT core_StreamSubmitUnit(
    VDECDD_sDdStrContext *  psDdStrContext,
    VDECDD_sStrUnit *       psStrUnit
)
{
    IMG_RESULT              ui32Result;
    BSPP_sBitStrSeg       * psBitStrSeg;
    VDECDD_sDdBufMapInfo  * psDdBufMapInfo;
    VDECDD_eStrUnitType     eStrUnitType;

    /* Validate input arguments. */
    IMG_ASSERT(psDdStrContext);
    IMG_ASSERT(psStrUnit);

    /* Store stream unit type for reports. */
    eStrUnitType = psStrUnit->eStrUnitType;

    DEBUG_REPORT(REPORT_MODULE_CORE,
        "[SID=0x%08X] [UTYPE=0x%08X] SUBMIT",
        psDdStrContext->ui32StrId,
        eStrUnitType);

    /* Set the buffer map information for each segment. */
    psBitStrSeg = LST_first(&psStrUnit->sBitStrSegList);
    while (psBitStrSeg != IMG_NULL)
    {
        /* Get access to map info context...*/
        ui32Result = RMAN_GetResource(psBitStrSeg->ui32BufMapId, VDECDD_BUFMAP_TYPE_ID, (IMG_VOID **)&psDdBufMapInfo, IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        //psBitStrSeg->psDdBufMapInfo = psDdBufMapInfo;

        /* Get next segment. */
        psBitStrSeg = LST_next(psBitStrSeg);
    }


    ui32Result = SCHEDULER_StreamAddUnit(psDdStrContext->hSchedulerContext, psStrUnit);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    DEBUG_REPORT(REPORT_MODULE_CORE,
                 "[SID=0x%08X] [UTYPE=0x%08X] SUBMITTED",
                 psDdStrContext->ui32StrId,
                 eStrUnitType);

    /* Return success...*/
    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              core_StreamSetOutputConfig

******************************************************************************/
static IMG_RESULT core_StreamSetOutputConfig(
    VDECDD_sDdStrContext *   psDdStrContext,
    VDEC_sStrOutputConfig *  psStrOutputConfig,
    VDEC_sPictBufConfig   *  psPictBufConfig
)
{
    VDECDD_sSuppCheck       sSuppCheck;
    VDEC_sPictBufConfig     sPictBufConfig;
    VDEC_sPictRendInfo      sDispPictRendInfo;
    IMG_RESULT              ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdStrContext);
    IMG_ASSERT(psStrOutputConfig);

    VDEC_BZERO(&sSuppCheck);
    sSuppCheck.psComSequHdrInfo = &psDdStrContext->sComSequHdrInfo;
    sSuppCheck.psOutputConfig = psStrOutputConfig;

    // Validate stream output configuration against display buffer properties
    // if no new picture buffer configuration is provided.
    if (psPictBufConfig == IMG_NULL)
    {
        IMG_ASSERT(psDdStrContext->sDispPictBuf.sRendInfo.ui32RenderedSize);
        sSuppCheck.psDispPictBuf = &psDdStrContext->sDispPictBuf;
    }

    // Validate output configuration.
    ui32Result = core_CheckDecoderSupport(
        psDdStrContext->psDdConnContext->psDdDevContext,
        &psDdStrContext->sStrConfigData,
        &psDdStrContext->sPrevComSequHdrInfo,
        &psDdStrContext->sPrevPictHdrInfo,
        &psDdStrContext->sMapBufInfo,
        &sSuppCheck);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return IMG_SUCCESS;
    }

    // Clear warnings about unconfigured output picture buffer.
    // It is deliberately not passed-in here since it needs to be
    // recalculated once the output configuration has been validated.
    sSuppCheck.ui32StopFlags &= ~VDEC_STOPSTATUS_PICTBUF_CONFIG_INVALID;
    sSuppCheck.ui32StopFlags &= ~VDEC_STOPSTATUS_RECONFIGURE;
    if (sSuppCheck.ui32StopFlags & (VDEC_STOPSTATUS_OUTPUT_CONFIG_INVALID | VDEC_STOPSTATUS_PICTBUF_SIZE_INVALID))
    {
        sSuppCheck.ui32StopFlags |= VDEC_STOPSTATUS_RECONFIGURE;
    }

    // If stop flags were requested, set them in the Scheduler.
    if (sSuppCheck.ui32StopFlags)
    {
        IMG_UINT32 ui32TempResult;

        ui32TempResult = core_StreamSignalStopStatus(psDdStrContext, sSuppCheck.ui32StopFlags);
        IMG_ASSERT(ui32TempResult == IMG_SUCCESS);
    }

    if (core_IsUnsupported(&sSuppCheck.sUnSupportedFlags))
    {
        return IMG_ERROR_NOT_SUPPORTED;
    }

    /* Update the stream output configuration. */
    psDdStrContext->sOutputConfig = *psStrOutputConfig;

    /* Mark output as configured. */
    psDdStrContext->bStrOutputConfigured = IMG_TRUE;


    if (psPictBufConfig)
    {
        // Clear/invalidate the latest picture buffer configuration since it is easier to reuse
        // the set function to calculate for this new output configuration than to determine compatibility.
        // Keep a copy beforehand just in case the new configuration is invalid.
        if (psDdStrContext->sDispPictBuf.sRendInfo.ui32RenderedSize != 0)
        {
            sPictBufConfig = psDdStrContext->sDispPictBuf.sBufConfig;
            sDispPictRendInfo = psDdStrContext->sDispPictBuf.sRendInfo;

            VDEC_BZERO(&psDdStrContext->sDispPictBuf.sBufConfig);
            VDEC_BZERO(&psDdStrContext->sDispPictBuf.sRendInfo);
        }

        // Recalculate the picture buffer internal layout from the external configuration.
        // These settings provided by the allocator should be adhered to since the display process
        // will expect the decoder to use them.
        // If the configuration is invalid we need to leave the decoder state as it was before.
        ui32Result = core_StreamSetPictBufConfig(psDdStrContext, psPictBufConfig);
        IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            if (psDdStrContext->sDispPictBuf.sRendInfo.ui32RenderedSize != 0)
            {
                // Restore old picture buffer configuration.
                psDdStrContext->sDispPictBuf.sBufConfig = sPictBufConfig;
                psDdStrContext->sDispPictBuf.sRendInfo = sDispPictRendInfo;
            }

            return ui32Result;
        }
    }
    else if (core_IsUnsupported(&sSuppCheck.sUnSupportedFlags))
    {
        return IMG_ERROR_NOT_SUPPORTED;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              core_StreamFillPictBuf

******************************************************************************/
static IMG_RESULT core_StreamFillPictBuf(
    VDECDD_sDdStrContext *  psDdStrContext,
    VDECDD_sDdBufMapInfo *  psDdBufMapInfo
)
{
    IMG_RESULT      ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdStrContext);
    IMG_ASSERT(psDdBufMapInfo);

    /* Check buffer type. */
    IMG_ASSERT(psDdBufMapInfo->eBufType == VDEC_BUFTYPE_PICTURE);

    ui32Result = SCHEDULER_StreamAddPictureBuffer(psDdStrContext->hSchedulerContext,
                                                  psDdBufMapInfo);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              core_StreamFlush

******************************************************************************/
static IMG_RESULT core_StreamFlush(
    VDECDD_sDdStrContext *  psDdStrContext,
    IMG_BOOL                bDiscardRefs
)
{
    IMG_RESULT  ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdStrContext);
    IMG_ASSERT(psDdStrContext->eDdStrState == VDECDD_STRSTATE_STOPPED);

    ui32Result = DECODER_StreamFlush(psDdStrContext->hDecoderContext, bDiscardRefs);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    if (bDiscardRefs)
    {
        ui32Result = core_StreamSignalStopStatus(psDdStrContext, VDEC_STOPSTATUS_NO_REFERENCE_IMAGES);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }

    /* Flush now complete. */
    ui32Result = core_SendEvent(psDdStrContext,
                                VDECDD_EVENT_STREAM_FLUSHED,
                                psDdStrContext->pvStrCbParam,
                                IMG_NULL,
                                IMG_NULL);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              core_StreamReleaseBufs

******************************************************************************/
static IMG_RESULT core_StreamReleaseBufs(
    VDECDD_sDdStrContext *  psDdStrContext,
    VDEC_eBufType           eBufType
)
{
    IMG_RESULT  ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdStrContext);
    IMG_ASSERT(eBufType < VDEC_BUFTYPE_MAX);

    ui32Result = SCHEDULER_StreamReleaseBuffers(psDdStrContext->hSchedulerContext, eBufType);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    if (eBufType == VDEC_BUFTYPE_PICTURE || eBufType == VDEC_BUFTYPE_ALL)
    {
        ui32Result = DECODER_StreamReleaseBuffers(psDdStrContext->hDecoderContext);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }

        ui32Result = core_StreamSignalStopStatus(psDdStrContext, VDEC_STOPSTATUS_NO_REFERENCE_IMAGES);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              core_StreamSetBehaviourOnErrors

******************************************************************************/
static IMG_RESULT core_StreamSetBehaviourOnErrors(
    VDECDD_sDdStrContext *  psDdStrContext,
    VDEC_eErrorHandling     eErrorHandling
)
{
    IMG_RESULT  ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdStrContext);

    ui32Result = SCHEDULER_StreamSetBehaviourOnErrors(psDdStrContext->hSchedulerContext,
                                                      eErrorHandling);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);

    return ui32Result;
}


/*!
******************************************************************************

 @Function              core_StreamGetStatus

******************************************************************************/
static IMG_RESULT core_StreamGetStatus(
    VDECDD_sDdStrContext *  psDdStrContext,
    VDECDD_sStrStatus *     psStrStatus
)
{
    IMG_RESULT  ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdStrContext);
    IMG_ASSERT(psStrStatus);

    ui32Result = SCHEDULER_StreamGetStatus(psDdStrContext->hSchedulerContext, &psStrStatus->sSchStatus);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    ui32Result = DECODER_StreamGetStatus(psDdStrContext->hDecoderContext, &psStrStatus->sDecStatus);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                core_DevSchedule

******************************************************************************/
static IMG_RESULT core_DevSchedule(
    VDECDD_sDdDevContext  * psDdDevContext,
    VDECDD_sDdStrContext ** ppsDdStrContext
)
{
    IMG_RESULT  ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdDevContext);
    IMG_ASSERT(ppsDdStrContext);

    ui32Result = SCHEDULER_Run(psDdDevContext->hSchedulerContext, (IMG_VOID**)ppsDdStrContext);
    IMG_ASSERT_TESTED(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_CORE, REPORT_ERR,
            "Attempt to schedule unsuccessful");
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                core_DevHwInterrupt

******************************************************************************/
static IMG_RESULT core_DevHwInterrupt(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_HANDLE              hDecServiceInt,
    VDECDD_sDdStrContext ** ppsDdStrContext
)
{
    IMG_RESULT              ui32Result;
    VDECDD_sDdStrContext *  psDdStrContext = IMG_NULL;

    // Validate input arguments.
    IMG_ASSERT(psDdDevContext);
    IMG_ASSERT(hDecServiceInt);
    IMG_ASSERT(ppsDdStrContext);

    // Service the hardware interrupt to signal picture done and obtain the
    // stream context of the stream to which that picture belongs.
    ui32Result = DECODER_CoreServiceInterrupt(hDecServiceInt, (IMG_VOID**)&psDdStrContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    // If the stream is pending destruction and is now idle, add a message to destroy
    if (psDdStrContext && psDdStrContext->hDestroyedEvent)
    {
        if (DECODER_StreamIsIdle(psDdStrContext->hDecoderContext))
        {
            ui32Result = core_StreamDestroy(psDdStrContext,
                                            psDdStrContext->hDestroyedEvent,
                                            IMG_NULL);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }
    }

    *ppsDdStrContext = psDdStrContext;

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                core_DevSwInterrupt

******************************************************************************/
static IMG_RESULT core_DevSwInterrupt(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_HANDLE              hDecServiceInt,
    VDECDD_sDdStrContext ** ppsDdStrContext
)
{
    IMG_RESULT              ui32Result;
    VDECDD_sDdStrContext  * psDdStrContext;

    // Validate input arguments.
    IMG_ASSERT(psDdDevContext);
    IMG_ASSERT(hDecServiceInt);
    IMG_ASSERT(ppsDdStrContext);

    ui32Result = DECODER_StreamFlushInput(hDecServiceInt, (IMG_VOID**)&psDdStrContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    // If the stream is pending destruction and is now idle, add a message to destroy
    if (psDdStrContext->hDestroyedEvent)
    {
        if (DECODER_StreamIsIdle(psDdStrContext->hDecoderContext))
        {
            ui32Result = core_StreamDestroy(psDdStrContext,
                                            psDdStrContext->hDestroyedEvent,
                                            IMG_NULL);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }
    }

    *ppsDdStrContext = psDdStrContext;

    /* Return success...*/
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                core_DevSwInterruptPicDiscarded

******************************************************************************/
static IMG_RESULT core_DevSwInterruptPicDiscarded(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_HANDLE              hDecServiceInt,
    VDECDD_sDdStrContext ** ppsDdStrContext
)
{
    IMG_RESULT              ui32Result;
    VDECDD_sDdStrContext *  psDdStrContext = IMG_NULL;

    // Validate input arguments.
    IMG_ASSERT(psDdDevContext);
    IMG_ASSERT(hDecServiceInt);
    IMG_ASSERT(ppsDdStrContext);

    // Service the software interrupt to signal a pic has been discarded by the driver.
    ui32Result = DECODER_CoreServiceInterrupt(hDecServiceInt, (IMG_VOID**)&psDdStrContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    // If the stream is pending destruction and is now idle, add a message to destroy
    if (psDdStrContext && psDdStrContext->hDestroyedEvent)
    {
        if (DECODER_StreamIsIdle(psDdStrContext->hDecoderContext))
        {
            ui32Result = core_StreamDestroy(psDdStrContext,
                                            psDdStrContext->hDestroyedEvent,
                                            IMG_NULL);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }
    }

    *ppsDdStrContext = psDdStrContext;

    /* Return success...*/
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                core_DevReset

******************************************************************************/
static IMG_RESULT core_DevReset(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_UINT32              ui32CoreNum,
    VDECDD_eResetReason     eReason
)
{
#ifndef __FAKE_MTX_INTERFACE__
    IMG_RESULT  ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdDevContext);

    ui32Result = DECODER_CoreReset(psDdDevContext->hDecoderContext, ui32CoreNum, eReason);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
#endif // __FAKE_MTX_INTERFACE__
    /* Return success...*/
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                core_DevPowerPostS0

******************************************************************************/
static IMG_RESULT core_DevServiceTimeExpiry(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_UINT32              ui32CoreNum
)
{
#ifndef __FAKE_MTX_INTERFACE__
    IMG_RESULT  ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdDevContext);

    ui32Result = DECODER_CoreServiceTimerExpiry(psDdDevContext->hDecoderContext,ui32CoreNum);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
#endif // __FAKE_MTX_INTERFACE__
    /* Return success...*/
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                core_DevReplay

******************************************************************************/
static IMG_RESULT core_DevReplay(
    VDECDD_sDdDevContext *  psDdDevContext,
    IMG_UINT32              ui32CoreNum
)
{
    IMG_RESULT  ui32Result = IMG_SUCCESS;

    // Validate input arguments.
    IMG_ASSERT(psDdDevContext);
#ifndef __FAKE_MTX_INTERFACE__
    ui32Result = DECODER_CoreReplay(psDdDevContext->hDecoderContext,ui32CoreNum);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }
#endif //__FAKE_MTX_INTERFACE__

    /* Return success...*/
    return ui32Result;
}

/*!
******************************************************************************

 @Function                core_DevPowerPreS5

******************************************************************************/
static IMG_RESULT core_DevPowerPreS5(
    VDECDD_sDdDevContext *  psDdDevContext
)
{
    IMG_RESULT  ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdDevContext);

    ui32Result = DECODER_PrePowerOff(psDdDevContext->hDecoderContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                core_DevPowerPostS0

******************************************************************************/
static IMG_RESULT core_DevPowerPostS0(
    VDECDD_sDdDevContext *  psDdDevContext
)
{
    IMG_RESULT  ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdDevContext);

    ui32Result = DECODER_PostPowerOn(psDdDevContext->hDecoderContext);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        return ui32Result;
    }

    /* Return success...*/
    return IMG_SUCCESS;
}



/*!
******************************************************************************

 @Function              CORE_ProcessEvent

******************************************************************************/
IMG_RESULT CORE_ProcessEvent(
    VDECDD_sDdDevContext *  psDdDevContext
)
{
    CORE_sCoreMsg         * psCoreMsg;
    VDECDD_sDdStrContext  * psDdStrContext;
    IMG_RESULT              ui32Result;

    // Validate input arguments.
    IMG_ASSERT(psDdDevContext);

    /* Disable interrupts.  */
    SYSOSKM_DisableInt();

    /* Get the next message. */
    psCoreMsg = (CORE_sCoreMsg *)LST_removeHead(&psDdDevContext->sCoreMsgList);

    /* Enable interrupts.  */
    SYSOSKM_EnableInt();

    if (psCoreMsg == IMG_NULL)
    {
        return IMG_ERROR_STORAGE_TYPE_EMPTY;
    }

    // Process stream/device message. Only stream messages should have a stream ID.
    if (psCoreMsg->ui32StrId)
    {
        /* Get access to stream context...*/
        ui32Result = RMAN_GetResource(psCoreMsg->ui32StrId, VDECDD_STREAM_TYPE_ID, (IMG_VOID **)&psDdStrContext, IMG_NULL);
        IMG_ASSERT(ui32Result == IMG_SUCCESS && psDdStrContext);
        if (ui32Result != IMG_SUCCESS || psDdStrContext == IMG_NULL)
        {
            if (ui32Result == IMG_ERROR_INVALID_ID)
            {
                psCoreMsg->ui32Result = IMG_ERROR_GENERIC_FAILURE;
            }
            else if (psDdStrContext == IMG_NULL)
            {
                psCoreMsg->ui32Result = IMG_ERROR_INVALID_PARAMETERS;
            }

            goto error;
        }

        /* Branch of message id... */
        switch (psCoreMsg->eMsgId)
        {
        case CORE_MSGID_STREAM_DESTROY:
            IMG_ASSERT(psCoreMsg->sStreamDestroyMsg.hDestroyedEvent);
            IMG_ASSERT(psCoreMsg->sStreamDestroyMsg.pui32ConnId);
            psCoreMsg->ui32Result = core_StreamDestroy(psDdStrContext,
                                                       psCoreMsg->sStreamDestroyMsg.hDestroyedEvent,
                                                       psCoreMsg->sStreamDestroyMsg.pui32ConnId);
            IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_STREAM_PLAY:
            psCoreMsg->ui32Result = core_StreamPlay(psDdStrContext,
                                                    psCoreMsg->sStreamPlayMsg.ePlayMode,
                                                    psCoreMsg->sStreamPlayMsg.eStopPoint,
                                                    psCoreMsg->sStreamPlayMsg.ui32StopPointQual);
            IMG_ASSERT_TESTED(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_STREAM_STOP:
            psCoreMsg->ui32Result = core_StreamStop(psDdStrContext,
                                                    psCoreMsg->sStreamStopMsg.eStopPoint,
                                                    psCoreMsg->sStreamStopMsg.ui32StopPointQual,
                                                    0);
            IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_STREAM_GET_STOP_FLAGS:
            IMG_ASSERT(IMG_FALSE);
            break;

        case CORE_MSGID_STREAM_MAP_BUF:
            psCoreMsg->ui32Result = core_StreamMapBuf(psDdStrContext,
                                                      psCoreMsg->sStreamMapBufMsg.pvBufCbParam,
                                                      psCoreMsg->sStreamMapBufMsg.eBufType,
                                                      &psCoreMsg->sStreamMapBufMsg.sBufInfo,
                                                      psCoreMsg->sStreamMapBufMsg.pui32BufMapId);
            IMG_ASSERT_TESTED(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_STREAM_UNMAP_BUF:
            {
                VDECDD_sDdBufMapInfo *  psDdBufMapInfo;

                /* Get access to map info context...*/
                ui32Result = RMAN_GetResource(psCoreMsg->sStreamUnmapBufMsg.ui32BufMapId,
                                              VDECDD_BUFMAP_TYPE_ID, (IMG_VOID **)&psDdBufMapInfo, IMG_NULL);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }

                psCoreMsg->ui32Result = core_StreamUnmapBuf(psDdStrContext, psDdBufMapInfo);
                IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            }
            break;

        case CORE_MSGID_STREAM_SUBMIT_UNIT:
            psCoreMsg->ui32Result = core_StreamSubmitUnit(psDdStrContext,
                                                          psCoreMsg->sStreamSubmitUnitMsg.psStrUnit);
            if(psCoreMsg->ui32Result != IMG_SUCCESS)
            {
                REPORT(REPORT_MODULE_CORE, REPORT_ERR,
                    "[SID=0x%08X] Failed to submit unit",
                    psDdStrContext->ui32StrId);
            }
            break;

        case CORE_MSGID_STREAM_SET_OUTPUT_CONFIG:
            psCoreMsg->ui32Result = core_StreamSetOutputConfig(psDdStrContext,
                                                               psCoreMsg->sStreamSetOutputConfigMsg.psStrOutputConfig,
                                                               psCoreMsg->sStreamSetOutputConfigMsg.psPictBufConfig);
            IMG_ASSERT_TESTED(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_STREAM_FILL_PICT_BUF:
            {
                VDECDD_sDdBufMapInfo *  psDdBufMapInfo;

                /* Get access to map info context...*/
                ui32Result = RMAN_GetResource(psCoreMsg->sStreamFillPictBufMsg.ui32BufMapId,
                                              VDECDD_BUFMAP_TYPE_ID, (IMG_VOID **)&psDdBufMapInfo, IMG_NULL);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }

                psCoreMsg->ui32Result = core_StreamFillPictBuf(psDdStrContext, psDdBufMapInfo);
                IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            }
            break;

        case CORE_MSGID_STREAM_FLUSH:
            psCoreMsg->ui32Result = core_StreamFlush(psDdStrContext,
                                                     psCoreMsg->sStreamFlushMsg.bDiscardRefs);
            IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_STREAM_RELEASE_BUFS:
            psCoreMsg->ui32Result = core_StreamReleaseBufs(psDdStrContext,
                                                           psCoreMsg->sStreamReleaseBufsMsg.eBufType);
            IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_STREAM_SET_BEHAVIOUR_ON_ERRORS:
            psCoreMsg->ui32Result = core_StreamSetBehaviourOnErrors(psDdStrContext,
                                                                    psCoreMsg->sStreamSetBehaviourOnErrorsMsg.eErrorHandling);
            IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_STREAM_GET_STATUS:
            psCoreMsg->ui32Result = core_StreamGetStatus(psDdStrContext,
                                                         psCoreMsg->sStreamGetStatusMsg.psStrStatus);
            IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        default:
            IMG_ASSERT(IMG_FALSE);
        }
    }
    else
    {
        /* Branch of message id... */
        switch (psCoreMsg->eMsgId)
        {
        case CORE_MSGID_CONNECTION_CREATE:
            psCoreMsg->ui32Result = core_ConnectionCreate(psDdDevContext,
                                                          psCoreMsg->sCreateConnectionMsg.ppsDdConnContext);
            IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_CONNECTION_DESTROY:
            psCoreMsg->ui32Result = core_ConnectionDestroy(psCoreMsg->sDestroyConnectionMsg.ui32ConnId);
            IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_STREAM_CREATE:
            psCoreMsg->ui32Result = core_StreamCreate(psCoreMsg->sStreamCreateMsg.ui32ConnId,
                                                      &psCoreMsg->sStreamCreateMsg.sStrConfigData,
                                                      psCoreMsg->sStreamCreateMsg.pvStrCbParam,
                                                      psCoreMsg->sStreamCreateMsg.pui32StrId);
            IMG_ASSERT_TESTED(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_DEV_SCHEDULE:
            psCoreMsg->ui32Result = core_DevSchedule(psDdDevContext,
                                                     &psDdStrContext);
            IMG_ASSERT_TESTED(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_DEV_HW_INTERRUPT:
            psCoreMsg->ui32Result = core_DevHwInterrupt(psDdDevContext,
                                                        psCoreMsg->sDevHwInterruptMsg.hDecServiceInt,
                                                        &psDdStrContext);
            IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_DEV_SW_INTERRUPT:
            psCoreMsg->ui32Result = core_DevSwInterrupt(psDdDevContext,
                                                        psCoreMsg->sDevSwInterruptMsg.hDecServiceInt,
                                                        &psDdStrContext);
            IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_DEV_SW_INTERRUPT_PIC_DISCARDED:
            psCoreMsg->ui32Result = core_DevSwInterruptPicDiscarded(psDdDevContext,
                                                                    psCoreMsg->sDevSwInterruptPicDiscardedMsg.hDecServiceInt,
                                                                    &psDdStrContext);
            IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_DEV_POWER_PRE_S5:
            psCoreMsg->ui32Result = core_DevPowerPreS5(psDdDevContext);
            IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_DEV_POWER_POST_S0:
            psCoreMsg->ui32Result = core_DevPowerPostS0(psDdDevContext);
            IMG_ASSERT(psCoreMsg->ui32Result == IMG_SUCCESS);
            break;

        case CORE_MSGID_DEV_RESET:
            psCoreMsg->ui32Result = core_DevReset(psDdDevContext,
            psCoreMsg->sDevReset.ui32CoreNum,
            psCoreMsg->sDevReset.eReason);
            break;

        case CORE_MSGID_DEV_SERVICE_TIME_EXPIRY:
            psCoreMsg->ui32Result = core_DevServiceTimeExpiry(psDdDevContext,
                                                              psCoreMsg->sDevServiceTimeExpiryMsg.ui32CoreNum);
            break;

        case CORE_MSGID_DEV_REPLAY:
            psCoreMsg->ui32Result = core_DevReplay(psDdDevContext,
                                                   psCoreMsg->sDevReplayMsg.ui32CoreNum);
            break;

        default:
            IMG_ASSERT(IMG_FALSE);
        }
    }

error:

    /* If synchronous call. */
    if (psCoreMsg->hEventHandle != IMG_NULL)
    {
        /* Signal completion. */
        SYSOSKM_SignalEventObject(psCoreMsg->hEventHandle);
    }
    else
    {
        if (psCoreMsg->ui32Result != IMG_SUCCESS)
        {
            // Stop the stream and report the error result with the stop status.
            IMG_ASSERT(psDdStrContext);
            if (psDdStrContext)
            {
            core_StreamStop(psDdStrContext,
                            VDEC_STOPPOINT_NOW,
                            0,
                            psCoreMsg->ui32Result);
        }
        }

        // HW interrupt message buffers are allocated preemptively unless the HW message list runs out,
        // so no matter what happened, return them to the HW message list
        if (psCoreMsg->eMsgId == CORE_MSGID_DEV_HW_INTERRUPT ||
            psCoreMsg->eMsgId == CORE_MSGID_DEV_SERVICE_TIME_EXPIRY ||
            psCoreMsg->eMsgId == CORE_MSGID_DEV_SW_INTERRUPT_PIC_DISCARDED )
        {
            SYSOSKM_DisableInt();
            LST_add(&psDdDevContext->sHwMsgList, psCoreMsg);
            SYSOSKM_EnableInt();
        }
        // Non-HW interrupt message buffers are allocated normally when needed, so just free them
        else
        {
            /* Free the message structure. */
            IMG_FREE(psCoreMsg);
        }
    }

    /* Return success...*/
    return IMG_SUCCESS;
}
