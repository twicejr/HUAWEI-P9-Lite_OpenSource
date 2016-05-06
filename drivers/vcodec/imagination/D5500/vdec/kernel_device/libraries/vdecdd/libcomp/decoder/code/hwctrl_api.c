/*!
 *****************************************************************************
 *
 * @File       hwctrl_api.c
 * @Title      VDECDD Hardware control API.
 * @Description    This file contains the VDECDD Hardware control API.
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

#include "hwctrl_api.h"
#include "hwctrl_int.h"
#include "core_api.h"
#include "report_api.h"
#include "rman_api.h"
#include "sysos_api_km.h"
#include "vxd_ext.h"
#include "secure_defs.h"

#ifdef VDEC_USE_PVDEC
#include "pvdec_int.h"
#include "hwdefs/pvdec_core_regs.h"
#else /* ndef VDEC_USE_PVDEC */
#include "msvdx_int.h"
#include "vdecfw_msg_mem_io.h"
#endif /* ndef VDEC_USE_PVDEC */

#ifndef SYSBRG_BRIDGING
    #include "talmmu_api.h"
#else /* def SYSBRG_BRIDGING */
    #include "sysmem_utils.h"
#endif /* def SYSBRG_BRIDGING */

#ifdef __FAKE_MTX_INTERFACE__
    #include "vdecfw_fakemtx.h"
#endif /* __FAKE_MTX_INTERFACE__ */

#ifdef USE_REAL_FW
    #include "vdecfw_bin.h"
#endif /* USE_REAL_FW */

#ifndef VDEC_MSVDX_HARDWARE
    //#define HWCTRL_REPLACEMENT_HW_THREAD
#endif /* ndef VDEC_MSVDX_HARDWARE */

extern int is_hi6250;

#ifdef HWCTRL_REPLACEMENT_HW_THREAD
/*!
******************************************************************************
 Contains task control information
******************************************************************************/
typedef struct
{
    IMG_BOOL    bExit;              /*!< Used to signal the task to exit.  */
    LST_T       sMsgList;           /*!< List of messages.                 */
    IMG_HANDLE  hMsgListMutex;      /*!< Sync list of messages.            */
    IMG_HANDLE  hNewMsgSent;        /*!< New message sent event.           */

    // book-keeping info
    IMG_HANDLE  hTask;              /*!< Task handle.                      */
    IMG_HANDLE  hActivatedEvent;    /*!< Indicates task was activated.     */
    IMG_HANDLE  hDeactivatedEvent;  /*!< Indicates task was deactivated.   */
} HWCTRL_sTaskInfo;

#endif /* HWCTRL_REPLACEMENT_HW_THREAD */


/*!
******************************************************************************
 This structure contains the hwctrl context.
 @brief  Hardware Control Context
******************************************************************************/
typedef struct
{
    IMG_BOOL                bInitialised;           /*!< Indicates whether the core has been enumerated.                            */
    volatile IMG_BOOL       bPower;                 /*!< Indicating whether the core is powered up.                                 */

    IMG_UINT32              ui32CoreNum;
    IMG_UINT32              ui32NumPipes;
    VDECDD_sDdDevConfig     sDevConfig;             /*!< Device configuration.                                                      */

    IMG_HANDLE              hVxd;                   /*!< Handle to video decoder context.                                           */
    HWCTRL_sFunctions       sVxdFuncs;              /*!< Low level video decoder routines.                                          */

    IMG_VOID *              pvDecCore;
    IMG_VOID *              pvCompInitUserData;

    VXDIO_sDdBufInfo        aui32RendecBufInfo[VDEC_NUM_RENDEC_BUFFERS];  /*!< Device virtual address of rendec buffers.            */
    VXDIO_sDdBufInfo        sDevPtdBufInfo;                               /*!< Buffer to hold device Page Table directory address.  */
    VXDIO_sDdBufInfo        sPsrModInfo;

    // State
    LST_T                   sPendPictList;          /*!< List of pictures that are being decoded on this core.                      */
    IMG_UINT32              ui32NumFreeSlots[VDEC_MAX_PIXEL_PIPES];       /*!< Number of front-end decoding slots (in pictures).                          */
    IMG_UINT32              ui32Load[VDEC_MAX_PIXEL_PIPES];               /*!< Metric to indicate the fullness of the core.                               */
    HWCTRL_sMsgStatus       sHostMsgStatus;         /*!< Video decoder  message status.                                             */

    IMG_HANDLE              hTimerHandle;
    IMG_BOOL                bMonitorBusy;

    HWCTRL_sState           sState;                 /*!< Current HWCTRL state. In core context because it is too big for stack.     */
    HWCTRL_sState           sPrevState;
    IMG_BOOL                bPrevHwStateSet;

    IMG_HANDLE              hFWPrintTimerHandle;
    IMG_BOOL                bPrintTaskBusy;
    IMG_BOOL                bPrintTaskRequestedActive;

    // Firmware message.
    VXD_sMsgQueue           sMsgQueue;              /*!< The queue of firmware messages.                                            */
    VXD_sIntStatus          sIntStatus;
    VXDIO_sHISRMsg          asHISRMsg[MSVDX_MAX_LISR_HISR_MSG]; /*!< Messages passed between LISR and HISR.                         */

#ifdef HWCTRL_REPLACEMENT_HW_THREAD
    HWCTRL_sTaskInfo      * psTaskInfo;             /*!< Pointer to task data.                                                      */
#endif

} HWCTRL_sHwCtx;


/*****************************************************************************
 Local function prototypes.
******************************************************************************/
static IMG_VOID hwctrl_SetupDWR(
    HWCTRL_sHwCtx     * psHwCtx,
    SYSOSKM_pfnTimer    pfnTimer);
static IMG_RESULT hwctrl_PowerOn(
    IMG_HANDLE  hHwCtx);
static IMG_VOID hwctrl_DumpState(
    VXDIO_sState    * psPrevState,
    VXDIO_sState    * psCurState,
    VXD_sIntStatus  * psIntStatus,
    IMG_UINT8         ui8PipeMinus1);
static IMG_BOOL hwctrl_HwStateIsLockUp(
    HWCTRL_sHwCtx  * psHwCtx);
static IS_NOT_USED IMG_BOOL hwctrl_MonitorHwState(
    IMG_VOID  * pvParam);
static IMG_UINT32 hwctrl_CalcMbLoad(
    IMG_UINT32  ui32NumMbs,
    IMG_BOOL    bIntraCoded);
static IMG_UINT32 hwctrl_CalculateLoad(
    BSPP_sPictHdrInfo  * psPictHdrInfo);
static IMG_RESULT hwctrl_SendInitMessage(
    HWCTRL_sHwCtx               * psHwCtx,
    const VDECFW_sCoreInitData  * psCoreInitData,
    const VXDIO_sDdBufInfo      * psDevPtdBufInfo);
static IMG_RESULT hwctrl_SendDecodeMessage(
    HWCTRL_sHwCtx       * psHwCtx,
    VXDIO_sDdBufInfo    * psTransactionBufInfo,
    VXDIO_sDdBufInfo    * psStrPtdBufInfo);
static IMG_RESULT hwctrl_SendBatchMessage(
    HWCTRL_sHwCtx     * psHwCtx,
    DECODER_sDecPict  * psDecPict);
static IMG_RESULT hwctrl_PictureReplay(
    IMG_HANDLE          hHwCtx,
    DECODER_sDecPict  * psDecPict);
static IMG_RESULT hwctrl_ProcessMTXMsgs(
    HWCTRL_sHwCtx  * psHwCtx,
    VXD_sMsgQueue  * psMsgQueue,
    IMG_VOID       * pvUserData);
static IMG_RESULT hwctrl_PowerOn(
    IMG_HANDLE  hHwCtx);


#ifdef HWCTRL_REPLACEMENT_HW_THREAD

/*!
******************************************************************************
 This type defines the HWCTRL task events.
 @brief  HWCTRL Internal Events
******************************************************************************/
typedef enum
{
    HWCTRL_EVENT_DECODE_PICTURE,  /*!< Decode a picture.     */

    HWCTRL_EVENT_MAX,             /*!< Max. "normal" event.  */

} HWCTRL_eEvent;


/*!
******************************************************************************
 Contains event information posted to HWCTRL task
******************************************************************************/
typedef struct
{
    LST_LINK;        /*!< List link (allows the structure to be part of a MeOS list).*/

    HWCTRL_eEvent    eEvent;   /*!< HWCTRL event.    */
    HWCTRL_sHwCtx *  psHwCtx;  /*!< HWCTRL context.  */

} HWCTRL_sEventInfo;

/*!
******************************************************************************

 @Function              hwctrl_SendEvent

******************************************************************************/
static IMG_VOID
hwctrl_SendEvent(
    HWCTRL_sTaskInfo   * psTaskInfo,
    HWCTRL_eEvent        eEvent,
    HWCTRL_sEventInfo  * psEventInfo
)
{
    psEventInfo->eEvent = eEvent;
    SYSOSKM_LockMutex(psTaskInfo->hMsgListMutex);
    LST_add(&psTaskInfo->sMsgList, psEventInfo);
    SYSOSKM_UnlockMutex(psTaskInfo->hMsgListMutex);

    /* Kick the task...*/
    SYSOSKM_SignalEventObject(psTaskInfo->hNewMsgSent);
}


/*!
******************************************************************************

 @Function              hwctrl_Task

 @Description

 This task mimics the hardware operation when none is present.

 @Input     pvTaskParam : Pointer to task parameter.

******************************************************************************/
static IMG_BOOL
hwctrl_Task(
    IMG_VOID  *pvParams
)
{
    HWCTRL_sTaskInfo *   psTaskInfo;
    HWCTRL_sEventInfo *  psEventInfo;
    IMG_RESULT           ui32Result;

    psTaskInfo = (HWCTRL_sTaskInfo *)pvParams;
    IMG_ASSERT(psTaskInfo);

    SYSOSKM_SignalEventObject(hActivatedEvent);

    while (!psTaskInfo->bExit)
    {
        SYSOSKM_WaitEventObject(psTaskInfo->hNewMsgSent);

        if (!psTaskInfo->bExit)
        {
            /* Get the event...*/
            SYSOSKM_LockMutex(psTaskInfo->hMsgListMutex);
            psEventInfo = (HWCTRL_sEventInfo *)LST_removeHead(&psTaskInfo->sMsgList);
            SYSOSKM_UnlockMutex(psTaskInfo->hMsgListMutex);

            while (psEventInfo != IMG_NULL)
            {
                switch (psEventInfo->eEvent)
                {
                case HWCTRL_EVENT_DECODE_PICTURE:

                    // Fake hardware processing.
                    KRN_hibernate(&hibernateQ, 1);

                    /* Generate a Dev HW Interrupt and not submit the picture */
                    ui32Result = CORE_DevHwInterrupt(psEventInfo->psHwCtx->pvCompInitUserData, psEventInfo->psHwCtx->pvDecCore);
                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        //return ui32Result;
                    }
                    break;

                default:
                    IMG_ASSERT(IMG_FALSE);
                    break;
                }

                IMG_FREE(psEventInfo);

                /* Get next event */
                SYSOSKM_LockMutex(psTaskInfo->hMsgListMutex);
                psEventInfo = (HWCTRL_sEventInfo *)LST_removeHead(&psTaskInfo->sMsgList);
                SYSOSKM_UnlockMutex(psTaskInfo->hMsgListMutex);
            }
        }
    }

    SYSOSKM_SignalEventObject(hDeactivatedEvent);

    return IMG_FALSE;
}

#endif

static IMG_VOID
hwctrl_SetupDWR(
    HWCTRL_sHwCtx     * psHwCtx,
    SYSOSKM_pfnTimer    pfnTimer
)
{
    if (psHwCtx->hTimerHandle == IMG_NULL)
    {
        if (psHwCtx->sDevConfig.ui32DwrPeriod)
        {
            SYSOSKM_CreateTimer(pfnTimer, psHwCtx, psHwCtx->sDevConfig.ui32DwrPeriod, &psHwCtx->hTimerHandle);
        }
    }

    psHwCtx->bMonitorBusy = IMG_FALSE;
    psHwCtx->bPrevHwStateSet = IMG_FALSE;
    psHwCtx->sPrevState.ui32DWRRetry = 0;
}


#ifdef FW_PRINT

// Important, verify the base address of the debug words in VDECFW_sFirmwareState
#define READ_REQUEST(psHwCtx, pui32Register)                                    \
do                                                                              \
{                                                                               \
    IMG_ASSERT(psHwCtx->sVxdFuncs.pfnReadVLR != IMG_NULL);                      \
    if (psHwCtx->sVxdFuncs.pfnReadVLR)                                          \
    {                                                                           \
        psHwCtx->sVxdFuncs.pfnReadVLR(                                          \
            psHwCtx->hVxd,                                                      \
            VLR_FIRMWARE_STATE_AREA_BASE_ADDR+sizeof(VDECFW_sFirmwareState)-12, \
            (IMG_UINT32*)pui32Register,                                         \
            1);                                                                 \
    }                                                                           \
} while (0);


#define WRITE_ACKNOWLEDGE(psHwCtx, pui32Register)                               \
do                                                                              \
{                                                                               \
    IMG_ASSERT(psHwCtx->sVxdFuncs.pfnWriteVLR != IMG_NULL);                     \
    if (psHwCtx->sVxdFuncs.pfnWriteVLR)                                         \
    {                                                                           \
        psHwCtx->sVxdFuncs.pfnWriteVLR(                                         \
            psHwCtx->hVxd,                                                      \
            VLR_FIRMWARE_STATE_AREA_BASE_ADDR+sizeof(VDECFW_sFirmwareState)-8,  \
            (IMG_UINT32*)pui32Register,                                         \
            1);                                                                 \
    }                                                                           \
} while (0);


#define READ_DATA32(psHwCtx, pui32Register)                                     \
do                                                                              \
{                                                                               \
    IMG_ASSERT(psHwCtx->sVxdFuncs.pfnReadVLR != IMG_NULL);                      \
    if (psHwCtx->sVxdFuncs.pfnReadVLR)                                          \
    {                                                                           \
        psHwCtx->sVxdFuncs.pfnReadVLR(                                          \
            psHwCtx->hVxd,                                                      \
            VLR_FIRMWARE_STATE_AREA_BASE_ADDR+sizeof(VDECFW_sFirmwareState)-4 , \
            (IMG_UINT32*)pui32Register,                                         \
            1);                                                                 \
    }                                                                           \
} while (0);

#ifdef SYSBRG_BRIDGING
#define MODE_PRINT printk
#else
#define MODE_PRINT printf
#endif

#define MAX_STATIC_STRING_SIZE  1024

static IMG_BOOL
hwctrl_MTXPrintTask(
    IMG_VOID  * pvParam
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *)pvParam;
    IMG_UINT32  ui32Word, ui32SavedWord;
    IMG_UINT32  ui32StringSize;
    IMG_BOOL    bContainsValue;
    IMG_UINT8   pui8String[MAX_STATIC_STRING_SIZE];
    IMG_UINT32  i;

    if (psHwCtx->bPrintTaskRequestedActive == IMG_FALSE)
    {
        return IMG_FALSE;   // we don't want the task to be kicked again by the timer
    }
    if (psHwCtx->bPrintTaskBusy == IMG_TRUE)
    {
        return IMG_TRUE;   // we want the task to be kicked again by the timer
    }

    psHwCtx->bPrintTaskBusy = IMG_TRUE;

    ui32Word = 0;
    WRITE_ACKNOWLEDGE(psHwCtx, &ui32Word); // Always zero Acknowledge at start to eliminate any possible miscommunications

    READ_REQUEST(psHwCtx, &ui32Word);   // Check if FW has requested any transfer
    ui32SavedWord = ui32Word;

    if (ui32Word == 0)
    {
        psHwCtx->bPrintTaskBusy = IMG_FALSE;
        return IMG_TRUE;    // we want the task to be kicked again by the timer
    }

    MODE_PRINT("FIRMWARE MESSAGE: ");   // Acknowledge the request

    WRITE_ACKNOWLEDGE(psHwCtx, &ui32Word);

    ui32StringSize = (ui32Word & 0x7FFF);   // 1024 bytes is the maximum string size allowed dispite this value
    bContainsValue = (ui32Word > 0x7fff);   // Contains also a numerical value

    // if string length is >0
    if (ui32StringSize > 0)
    {
        if (ui32StringSize > MAX_STATIC_STRING_SIZE)
        {
            MODE_PRINT("Not enough memory for firmware printing, something may be wrong with the printing function\n");
            ui32Word = 0;
            WRITE_ACKNOWLEDGE(psHwCtx, &ui32Word);
            psHwCtx->bPrintTaskBusy = IMG_FALSE;
            return IMG_TRUE;    // we want the task to be kicked again by the timer
        }

        for (i=4; i<=ui32StringSize; i+=4)        // read in 4-byte words
        {
            do
            {
                READ_REQUEST(psHwCtx, &ui32Word);
            }while (ui32Word == ui32SavedWord);    // wait for request value change
            ui32SavedWord = ui32Word;

            if (i != ui32Word)    // error, send 0 and reinitialize
            {
                MODE_PRINT("FW print lost synchronisation while string reading, reinitialize\n");
                ui32Word = 0;
                WRITE_ACKNOWLEDGE(psHwCtx, &ui32Word);
                psHwCtx->bPrintTaskBusy = IMG_FALSE;
                return IMG_TRUE;    // we want the task to be kicked again by the timer
            }

            READ_DATA32(psHwCtx, &ui32Word);
            pui8String[i-4] =  ui32Word      & 0xFF;
            pui8String[i-3] = (ui32Word>>8)  & 0xFF;
            pui8String[i-2] = (ui32Word>>16) & 0xFF;
            pui8String[i-1] = (ui32Word>>24) & 0xFF;

            WRITE_ACKNOWLEDGE(psHwCtx, &i);
        }

        if (i-4 < ui32StringSize)    // read the last 1, 2 or 3 bytes if they remain (cannot be 4+ and for 0 do nothing)
        {
            do
            {
                READ_REQUEST(psHwCtx, &ui32Word);
            }while (ui32Word == ui32SavedWord);    // wait for request value change
            ui32SavedWord = ui32Word;

            if (ui32StringSize != ui32Word)    // error, send 0 and reinitialize
            {
                MODE_PRINT("FW print lost synchronisation while string ending reading, reinitialize\n");
                ui32Word = 0;
                WRITE_ACKNOWLEDGE(psHwCtx, &ui32Word);
                psHwCtx->bPrintTaskBusy = IMG_FALSE;
                return IMG_TRUE;    // we want the task to be kicked again by the timer
            }

            READ_DATA32(psHwCtx, &ui32Word);
            switch (ui32StringSize-(i-4))
            {
            case 3:     pui8String[i-2] = (ui32Word>>16) & 0xFF;
            case 2:     pui8String[i-3] = (ui32Word>>8)  & 0xFF;
            case 1:     pui8String[i-4] =  ui32Word      & 0xFF;
            default:    break;
            }

            WRITE_ACKNOWLEDGE(psHwCtx, &ui32StringSize);
        }

        MODE_PRINT("%s", pui8String);
    }

    if (bContainsValue)
    {
        do
        {
            READ_REQUEST(psHwCtx, &ui32Word);
        }while (ui32Word == ui32SavedWord);    // wait for request value change
        ui32SavedWord = ui32Word;

        if (0x8001 != ui32Word)    // error, send 0 and reinitialize
        {
            MODE_PRINT("FW print lost synchronisation while value reading, reinitialize\n");
            ui32Word = 0;
            WRITE_ACKNOWLEDGE(psHwCtx, &ui32Word);
            psHwCtx->bPrintTaskBusy = IMG_FALSE;
            return IMG_TRUE;    // we want the task to be kicked again by the timer
        }

        READ_DATA32(psHwCtx, &ui32Word);

        MODE_PRINT("\t--> 0x%08lx", ui32Word);

        WRITE_ACKNOWLEDGE(psHwCtx, &ui32SavedWord);
    }

    MODE_PRINT("\n");

    do
    {
        READ_REQUEST(psHwCtx, &ui32Word);
    }while (ui32Word == ui32SavedWord);    // wait for request value change

    if (0 != ui32Word)    // error, send 0 and reinitialize
    {
        MODE_PRINT("FW print lost synchronisation while finishing, reinitialize\n");
        ui32Word = 0;
        WRITE_ACKNOWLEDGE(psHwCtx, &ui32Word);
        psHwCtx->bPrintTaskBusy = IMG_FALSE;
        return IMG_TRUE;    // we want the task to be kicked again by the timer
    }

    WRITE_ACKNOWLEDGE(psHwCtx, &ui32Word); // Always zero Acknowledge at start to eliminate any possible miscommunications

    psHwCtx->bPrintTaskBusy = IMG_FALSE;
    return IMG_TRUE;    // we want the task to be kicked again by the timer
}
#endif //FW_PRINT

static IMG_VOID
hwctrl_DumpState(
    VXDIO_sState    * psPrevState,
    VXDIO_sState    * psCurState,
    VXD_sIntStatus  * psIntStatus,
    IMG_UINT8         ui8PipeMinus1
)
{
    if(!is_hi6250)
    {
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "Back-End MbX                          [% 10d]", psPrevState->sFwState.asPipeState[ui8PipeMinus1].sBeMb.ui32X);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "Back-End MbY                          [% 10d]", psPrevState->sFwState.asPipeState[ui8PipeMinus1].sBeMb.ui32Y);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "Front-End MbX                         [% 10d]", psPrevState->sFwState.asPipeState[ui8PipeMinus1].sFeMb.ui32X);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "Front-End MbY                         [% 10d]", psPrevState->sFwState.asPipeState[ui8PipeMinus1].sFeMb.ui32Y);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "VDECFW_CHECKPOINT_BE_PICTURE_COMPLETE [0x%08X]", psCurState->sFwState.asPipeState[ui8PipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_BE_PICTURE_COMPLETE]);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "VDECFW_CHECKPOINT_BE_1SLICE_DONE      [0x%08X]", psCurState->sFwState.asPipeState[ui8PipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_BE_1SLICE_DONE]);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "VDECFW_CHECKPOINT_BE_PICTURE_STARTED  [0x%08X]", psCurState->sFwState.asPipeState[ui8PipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_BE_PICTURE_STARTED]);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "VDECFW_CHECKPOINT_FE_PICTURE_COMPLETE [0x%08X]", psCurState->sFwState.asPipeState[ui8PipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_FE_PICTURE_COMPLETE]);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "VDECFW_CHECKPOINT_FE_PARSE_DONE       [0x%08X]", psCurState->sFwState.asPipeState[ui8PipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_FE_PARSE_DONE]);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "VDECFW_CHECKPOINT_FE_1SLICE_DONE      [0x%08X]", psCurState->sFwState.asPipeState[ui8PipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_FE_1SLICE_DONE]);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "VDECFW_CHECKPOINT_ENTDEC_STARTED      [0x%08X]", psCurState->sFwState.asPipeState[ui8PipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_ENTDEC_STARTED]);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "VDECFW_CHECKPOINT_FIRMWARE_SAVED      [0x%08X]", psCurState->sFwState.asPipeState[ui8PipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_FIRMWARE_SAVED]);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "VDECFW_CHECKPOINT_PICMAN_COMPLETE     [0x%08X]", psCurState->sFwState.asPipeState[ui8PipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_PICMAN_COMPLETE]);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "VDECFW_CHECKPOINT_SYNC_COMPLETE       [0x%08X]", psCurState->sFwState.asPipeState[ui8PipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_SYNC_COMPLETE]);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "VDECFW_CHECKPOINT_FIRMWARE_READY      [0x%08X]", psCurState->sFwState.asPipeState[ui8PipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_FIRMWARE_READY]);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "VDECFW_CHECKPOINT_PICTURE_STARTED     [0x%08X]", psCurState->sFwState.asPipeState[ui8PipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_PICTURE_STARTED]);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "eFirmwareAction                       [0x%08X]", psCurState->sFwState.asPipeState[ui8PipeMinus1].eFirmwareAction);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "DMACStatus                            [0x%08X]", psPrevState->sFwState.asPipeState[ui8PipeMinus1].aui32DMACStatus[0]);
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "Interrupt Status                      [0x%08X]", psIntStatus->ui32Pending);
    }
}

static IMG_BOOL
hwctrl_HwStateIsLockUp(
    HWCTRL_sHwCtx  * psHwCtx
)
{
    IMG_BOOL bReturnVal = IMG_FALSE;

    // Check if the HW State indicates a LockUp
    if (!LST_empty(&psHwCtx->sPendPictList))
    {
        IMG_UINT32 aui32NumFreeSlots[VDEC_MAX_PIXEL_PIPES];
        IMG_UINT32 aui32PipeLoad[VDEC_MAX_PIXEL_PIPES];

        HWCTRL_GetCoreStatus(psHwCtx, aui32NumFreeSlots, aui32PipeLoad, &psHwCtx->sState);

        /* Check for firmware PANIC. */
        if (psHwCtx->sState.sCoreState.sFwState.bPanic)
        {
            return IMG_TRUE;
        }

        // Make sure we actually have set the Previous State once at least before checking if it has been remained unmodified
        // Without this we may compare the first state to uninitialised state
        if (psHwCtx->bPrevHwStateSet)
        {
            VXDIO_sState * psCurState = &psHwCtx->sState.sCoreState;
            VXDIO_sState * psPrevState = &psHwCtx->sPrevState.sCoreState;
            IMG_UINT8      uiPipeMinus1 = 0;

            for(uiPipeMinus1 = 0; uiPipeMinus1 < psHwCtx->ui32NumPipes; uiPipeMinus1++)
            {
                bReturnVal = IMG_FALSE;
                // If HW state has not been modified for this core since the last time and there
                // is no progress of data transfer to SR
                if ( (psPrevState->sFwState.asPipeState[uiPipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_PICTURE_STARTED] ==
                      psCurState->sFwState.asPipeState[uiPipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_PICTURE_STARTED]) &&
                     (psPrevState->sFwState.asPipeState[uiPipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_BE_PICTURE_COMPLETE] ==
                      psCurState->sFwState.asPipeState[uiPipeMinus1].aui32CheckPoint[VDECFW_CHECKPOINT_BE_PICTURE_COMPLETE]) &&
                     (psCurState->sFwState.asPipeState[uiPipeMinus1].aui32DMACStatus[0] == psPrevState->sFwState.asPipeState[uiPipeMinus1].aui32DMACStatus[0])
                   )
               {
                    VDECFW_eCodecType eCodec = (VDECFW_eCodecType) psCurState->sFwState.asPipeState[uiPipeMinus1].ui8CurCodec;
                    /* We support large JPEGs, which can be encoded in one slice. There is no way to determine if
                       HW is locked up in this case (latest MBs are not updated in ENTDEC_INFORMATION register
                       for JPEG), so retry timer <psHwCtx->sDevConfig.ui32DwrJPEGRetry> times. */
                    if (eCodec == VDECFW_CODEC_JPEG)
                    {
                        if (psHwCtx->sPrevState.ui32DWRRetry < psHwCtx->sDevConfig.ui32DwrJPEGRetry)
                        {
                            psHwCtx->sState.ui32DWRRetry++;
                        }
                        else
                        {
                            bReturnVal = IMG_TRUE;
                        }
                    }
                    // Now test for backend macroblock number
                    else if ( (psCurState->sFwState.asPipeState[uiPipeMinus1].sBeMb.ui32X == psPrevState->sFwState.asPipeState[uiPipeMinus1].sBeMb.ui32X) &&
                              (psCurState->sFwState.asPipeState[uiPipeMinus1].sBeMb.ui32Y == psPrevState->sFwState.asPipeState[uiPipeMinus1].sBeMb.ui32Y) &&
                              (psCurState->sFwState.asPipeState[uiPipeMinus1].sFeMb.ui32X == psPrevState->sFwState.asPipeState[uiPipeMinus1].sFeMb.ui32X) &&
                              (psCurState->sFwState.asPipeState[uiPipeMinus1].sFeMb.ui32Y == psPrevState->sFwState.asPipeState[uiPipeMinus1].sFeMb.ui32Y)
                            )
                    {
                        IMG_UINT32 i;
                        bReturnVal = IMG_TRUE;

                        // Check that we haven't received any messages since last time
                        for (i = 0; i < VDECFW_MSGID_COMPLETION_TYPES; i++)
                        {
                            if ((psHwCtx->sState.sFwMsgStatus.aui8CompletionFenceID[i] !=
                                psHwCtx->sPrevState.sFwMsgStatus.aui8CompletionFenceID[i]) ||
                                (psHwCtx->sState.sHostMsgStatus.aui8CompletionFenceID[i] !=
                                psHwCtx->sPrevState.sHostMsgStatus.aui8CompletionFenceID[i]))
                            {
                                bReturnVal = IMG_FALSE;
                                break;
                            }
                        }
                        if ((psPrevState->sFwState.asPipeState[uiPipeMinus1].ui32BeSlices != psCurState->sFwState.asPipeState[uiPipeMinus1].ui32BeSlices) ||
                            (psPrevState->sFwState.asPipeState[uiPipeMinus1].ui32FeSlices != psCurState->sFwState.asPipeState[uiPipeMinus1].ui32FeSlices))
                        {
                            bReturnVal = IMG_FALSE;
                        }
                    }

                }

                //there was some action on current pipe, not need to check others
                if(bReturnVal == IMG_FALSE)
                {
                    break;
                }
            }

            if (bReturnVal)
            {
                VXD_sIntStatus  sIntStatus;
                IMG_UINT32      ui32Result;
                IMG_UINT8       uiPipeMinus1 = 0;

                IMG_MEMSET(&sIntStatus, 0, sizeof(sIntStatus));

                /* Lets dump some useful debug information from the Hardware */
                IMG_ASSERT(psHwCtx->sVxdFuncs.pfnGetIntStatus != IMG_NULL);
                if (psHwCtx->sVxdFuncs.pfnGetIntStatus)
                {
                    ui32Result = psHwCtx->sVxdFuncs.pfnGetIntStatus(psHwCtx->hVxd, &sIntStatus);
                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        return bReturnVal;
                    }
                }

                REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "====================================================");
                REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "There might be a core lock-up.");

                for(uiPipeMinus1 = 0; uiPipeMinus1 < psHwCtx->ui32NumPipes; uiPipeMinus1++)
                {
                    if (psCurState->sFwState.asPipeState[0].ui32IntStatus & MSVDX_CORE_CR_MSVDX_INTERRUPT_STATUS_CR_MTX_COMMAND_TIMEOUT_IRQ_MASK)
                    {
                        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "Possibly due to MTX command timeout on pipe %d", uiPipeMinus1 + 1);
                    }
                }

                if (psHwCtx->sVxdFuncs.pfnGetIntStatus)
                {
                    for(uiPipeMinus1 = 0; uiPipeMinus1 < psHwCtx->ui32NumPipes; uiPipeMinus1++)
                    {
                        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "Dumping debug info for pipe %d:", uiPipeMinus1 + 1);
                        hwctrl_DumpState(psPrevState, psCurState, &sIntStatus, uiPipeMinus1);
                    }
                }
                REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "====================================================");

                /* Now lets dump The complete Register spaces for CORE, MTX, VEC, VDMC, VDEB, DMAC and VLR. Also Dump RTM register for HW Debug. */
                if (psHwCtx->sDevConfig.bCoreDump)
                {
                    IMG_ASSERT(psHwCtx->sVxdFuncs.pfnDumpRegisters != IMG_NULL);
                    if (psHwCtx->sVxdFuncs.pfnDumpRegisters)
                    {
                        ui32Result = psHwCtx->sVxdFuncs.pfnDumpRegisters(psHwCtx->hVxd);
                        IMG_ASSERT(ui32Result == IMG_SUCCESS);
                        if (ui32Result != IMG_SUCCESS)
                        {
                            return bReturnVal;
                        }
                    }
                }
            }
        }
        else
        {
            psHwCtx->bPrevHwStateSet = IMG_TRUE;
        }

        IMG_MEMCPY( &psHwCtx->sPrevState, &psHwCtx->sState, sizeof(HWCTRL_sState) );
    }

    return bReturnVal;
}


IMG_BOOL HWCTRL_HwStateIsLockUp(
    IMG_VOID  * pvParam
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *)pvParam;

    if(hwctrl_HwStateIsLockUp(psHwCtx))
    {
        return IMG_TRUE;
    }
    else
    {
        psHwCtx->bMonitorBusy = IMG_FALSE;
        return IMG_FALSE;
    }
}

static IS_NOT_USED IMG_BOOL
hwctrl_MonitorHwState(
    IMG_VOID  * pvParam
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *)pvParam;
    IMG_UINT32 ui32Result;

    // bMonitorBusy is used to detect if we are already in a process of resetting the core
    if (psHwCtx->bMonitorBusy)
    {
        // ALWAYS return true if you want the timer to keep running
        return IMG_TRUE;
    }

    // Check for state and reset if needed
    if (hwctrl_HwStateIsLockUp(psHwCtx))
    {
        psHwCtx->bMonitorBusy = IMG_TRUE;

        // Do the Device Reset
        // ...
        ui32Result = CORE_DevServiceTimeExpiry(psHwCtx->pvCompInitUserData, psHwCtx->ui32CoreNum);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            //return ui32Result;
        }
    }

    // ALWAYS return true if you want the timer to keep running
    return IMG_TRUE;
}


#ifdef VDEC_MSVDX_HARDWARE

/*!
******************************************************************************

 @Function              hwctrl_CalcMbLoad

******************************************************************************/
static IMG_UINT32
hwctrl_CalcMbLoad(
    IMG_UINT32  ui32NumMbs,
    IMG_BOOL    bIntraCoded
)
{
    IMG_UINT32 ui32Load = 0;

    ui32Load = ui32NumMbs;
    if (bIntraCoded)
    {
        //ui32Load = (ui32Load*3)/2;
    }

    return ui32Load;
}


/*!
******************************************************************************

 @Function              hwctrl_CalculateLoad

******************************************************************************/
static IMG_UINT32
hwctrl_CalculateLoad(
    BSPP_sPictHdrInfo  * psPictHdrInfo
)
{
    IMG_UINT32 ui32NumMbs;

    ui32NumMbs = ((psPictHdrInfo->sCodedFrameSize.ui32Width+15)/16) * ((psPictHdrInfo->sCodedFrameSize.ui32Height+15)/16);

    return hwctrl_CalcMbLoad(ui32NumMbs, psPictHdrInfo->bIntraCoded);
}


#ifdef POST_TEST
/*!
******************************************************************************

 @Function              hwctrl_SendPOSTMessage

 @Description

 This function sends the POST message to the firmware.

******************************************************************************/
static IMG_RESULT hwctrl_SendPOSTMessage(
    HWCTRL_sHwCtx                 * psHwCtx,
    const VDECFW_ePOSTCommand       ePOSTCommand,
    const VXDIO_sDdBufInfo        * psDevPtdBufInfo
)
{
    IMG_RESULT ui32Result;
    /* Create a control picture message here from the config. */
    IMG_UINT8 aui8Msg[V2_CONTROLMSG_SIZE];
    IMG_UINT8 * pui8Msg = &aui8Msg[0];

    VDEC_BZERO(&aui8Msg);
    MEMIO_WRITE_FIELD(pui8Msg,V2_CONTROLMSG_SIZE, sizeof(aui8Msg));
    MEMIO_WRITE_FIELD(pui8Msg,V2_CONTROLMSG_MID, VDECFW_MSGID_FIRMWARE_CONTROL);
    /* prepare message type field */
    MEMIO_WRITE_FIELD(pui8Msg, V2_CONTROLMSG_TYPE, VDECFW_CONTROL_POST);
    /* prepare POST command field */
    MEMIO_WRITE_FIELD(pui8Msg, V2_CONTROLMSG_VALUE0, ePOSTCommand);
    /* prepare other data fields according to command */
    switch(ePOSTCommand)
    {
    case VDECFW_POST_FIRST_MSG:
        /* set value 1 to 0: not used */
        MEMIO_WRITE_FIELD(pui8Msg, V2_CONTROLMSG_VALUE1, 0);
        break;

    case VDECFW_POST_START_CALC:
        /* calculation data */
        MEMIO_WRITE_FIELD(pui8Msg, V2_CONTROLMSG_VALUE1, 0x45678912);
        break;

    case VDECFW_POST_GET_INIT_RES:
        /* set value 1 to 0: not used */
        MEMIO_WRITE_FIELD(pui8Msg, V2_CONTROLMSG_VALUE1, 0);
        break;

    default:
        break;
    }

    /* Updating the host pointer because the value was temporary stored in the device memory */
    UPDATE_HOST(psDevPtdBufInfo, IMG_TRUE);

    /* Prepare last message fields */
    MEMIO_WRITE_FIELD(pui8Msg, V2_CONTROLMSG_FENCE_ID, ((++(psHwCtx->sHostMsgStatus.aui8ControlFenceID[VDECFW_MSGID_FIRMWARE_CONTROL-VDECFW_MSGID_BASE_PADDING]))&0xFF));

    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "[MID=0x%02X] [CONTROL] [0x%02X]",
        psHwCtx->sHostMsgStatus.aui8ControlFenceID[VDECFW_MSGID_FIRMWARE_CONTROL-VDECFW_MSGID_BASE_PADDING], VDECFW_MSGID_FIRMWARE_CONTROL);

    /* Send the message to the firmware. MSVDX ONLY! */
    ui32Result = MSVDX_SendFirmwareMessage(psHwCtx->hVxd, MTXIO_AREA_CONTROL, aui8Msg);

    return ui32Result;
}
#endif


/*!
******************************************************************************

 @Function              hwctrl_SendInitMessage

 @Description

 This function sends the init message to the firmware.

******************************************************************************/
static IMG_RESULT
hwctrl_SendInitMessage(
    HWCTRL_sHwCtx               * psHwCtx,
    const VDECFW_sCoreInitData  * psCoreInitData,
    const VXDIO_sDdBufInfo      * psDevPtdBufInfo
)
{
    IMG_RESULT ui32Result;

    /* Create a control picture message here from the config. */
    IMG_UINT8 * pui8Msg = IMG_NULL;

    IMG_ASSERT(psHwCtx->sVxdFuncs.pfnGetInitMessage != IMG_NULL);
    if (psHwCtx->sVxdFuncs.pfnGetInitMessage)
    {
        ui32Result = psHwCtx->sVxdFuncs.pfnGetInitMessage(psHwCtx->hVxd,
                                                          &pui8Msg,
                                                          &psHwCtx->sHostMsgStatus,
                                                          &psHwCtx->sDevConfig,
                                                          psHwCtx->aui32RendecBufInfo,
                                                          psCoreInitData,
                                                          psDevPtdBufInfo);

        if (ui32Result != IMG_SUCCESS)
        {
            REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                   "Failed to get init message");
            return ui32Result;
        }
        IMG_ASSERT(pui8Msg != IMG_NULL);

        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "[MID=0x%02X] [CONTROL] [0x%02X]",
            psHwCtx->sHostMsgStatus.aui8ControlFenceID[VDECFW_MSGID_FIRMWARE_INIT-VDECFW_MSGID_BASE_PADDING], VDECFW_MSGID_FIRMWARE_INIT);

        IMG_ASSERT(psHwCtx->sVxdFuncs.pfnSendFirmwareMessage != IMG_NULL);
        if (psHwCtx->sVxdFuncs.pfnSendFirmwareMessage)
        {
            ui32Result = psHwCtx->sVxdFuncs.pfnSendFirmwareMessage(psHwCtx->hVxd, MTXIO_AREA_CONTROL, pui8Msg);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }

        IMG_ASSERT(psHwCtx->sVxdFuncs.pfnReturnMsg != IMG_NULL);
        if (psHwCtx->sVxdFuncs.pfnReturnMsg)
        {
            psHwCtx->sVxdFuncs.pfnReturnMsg(psHwCtx->hVxd, pui8Msg);
        }
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              hwctrl_SendDecodeMessage

 @Description

 This function sends the decode message to the firmware.

******************************************************************************/
static IMG_RESULT
hwctrl_SendDecodeMessage(
    HWCTRL_sHwCtx       * psHwCtx,
    VXDIO_sDdBufInfo    * psTransactionBufInfo,
    VXDIO_sDdBufInfo    * psStrPtdBufInfo
)
{
    IMG_RESULT ui32Result;

    IMG_UINT8 * pui8Msg = IMG_NULL;

    IMG_ASSERT(psHwCtx->sVxdFuncs.pfnGetDecodeMessage != IMG_NULL);
    if (psHwCtx->sVxdFuncs.pfnGetDecodeMessage)
    {
        ui32Result = psHwCtx->sVxdFuncs.pfnGetDecodeMessage(psHwCtx->hVxd,
                                                            &pui8Msg,
                                                            &psHwCtx->sHostMsgStatus,
                                                            &psHwCtx->sDevConfig,
                                                            psStrPtdBufInfo,
                                                            &psHwCtx->sPsrModInfo,
                                                            psTransactionBufInfo);
        if (ui32Result != IMG_SUCCESS)
        {
            REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                   "Failed to get decode message");
            return ui32Result;
        }
        IMG_ASSERT(pui8Msg != IMG_NULL);

        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "[MID=0x%02X] [DECODE] [0x%02X]",
            psHwCtx->sHostMsgStatus.aui8DecodeFenceID[VDECFW_MSGID_DECODE_PICTURE-VDECFW_MSGID_PSR_PADDING], VDECFW_MSGID_DECODE_PICTURE);

        IMG_ASSERT(psHwCtx->sVxdFuncs.pfnSendFirmwareMessage != IMG_NULL);
        if (psHwCtx->sVxdFuncs.pfnSendFirmwareMessage)
        {
            ui32Result = psHwCtx->sVxdFuncs.pfnSendFirmwareMessage(psHwCtx->hVxd, MTXIO_AREA_DECODE, pui8Msg);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }

        IMG_ASSERT(psHwCtx->sVxdFuncs.pfnReturnMsg != IMG_NULL);
        if (psHwCtx->sVxdFuncs.pfnReturnMsg)
        {
            psHwCtx->sVxdFuncs.pfnReturnMsg(psHwCtx->hVxd, pui8Msg);
        }
    }

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              hwctrl_SendBatchMessage

 @Description

 This function sends a batch message that contains a decode message,
 a number of bitstream buffer messages and the end bytes.

******************************************************************************/
static IMG_RESULT
hwctrl_SendBatchMessage(
    HWCTRL_sHwCtx     * psHwCtx,
    DECODER_sDecPict  * psDecPict
)
{
    HWCTRL_sBatchMsgData    sBatchMsgData;
    IMG_RESULT              ui32Result;
    IMG_UINT8               ui8BatchMessageID = 0;
    IMG_UINT8             * pui8Msg = IMG_NULL;
    VXDIO_sDdBufInfo      * psTransactionBufInfo = psDecPict->psTransactionInfo->psDdBufInfo;
    VXDIO_sDdBufInfo      * psStrPtdBufInfo = psDecPict->psStrPtdBufInfo;
    VXDIO_sDdBufInfo      * psBatchMsgBufInfo = psDecPict->psBatchMsgInfo->psDdBufInfo;
    VXDIO_sDdBufInfo      * psStartCodeBufInfo = psDecPict->psStartCodeBufInfo;
    LST_T                 * psDecPictSegList = &psDecPict->sDecPictSegList;

    ui8BatchMessageID = ((++(psHwCtx->sHostMsgStatus.aui8DecodeFenceID[VDECFW_MSGID_BATCH-VDECFW_MSGID_PSR_PADDING]))&0xFF);

    sBatchMsgData.psTransactionBufInfo = psTransactionBufInfo;
    sBatchMsgData.psStartCodeBufInfo = psStartCodeBufInfo;
    sBatchMsgData.psBatchMsgBufInfo = psBatchMsgBufInfo;
    sBatchMsgData.psPsrModInfo = &psHwCtx->sPsrModInfo;
    sBatchMsgData.psStrPtdBufInfo = psStrPtdBufInfo;
#ifdef VDEC_USE_PVDEC
    sBatchMsgData.ui32TransactionId = psDecPict->ui32TransactionId;
    sBatchMsgData.psPvdecFwCtx = psDecPict->psStrPvdecFwCtxBuf;
    sBatchMsgData.ui32CtrlAllocBytes = psDecPict->ui32CtrlAllocBytes;
    sBatchMsgData.ui32OperatingMode = psDecPict->ui32OperatingMode;
    sBatchMsgData.ui8Pipe = psDecPict->ui8Pipe;
    sBatchMsgData.bFirstPicOfSequence = psDecPict->psPictHdrInfo->bFirstPicOfSequence;
    sBatchMsgData.bSizeDelimitedMode =  (psDecPict->psPictHdrInfo->eParserMode != VDECFW_SCP_ONLY) ? (IMG_TRUE) : (IMG_FALSE) ;
#endif /* VDEC_USE_PVDEC */


    IMG_ASSERT(psHwCtx->sVxdFuncs.pfnGetBatchMessage != IMG_NULL);
    if (psHwCtx->sVxdFuncs.pfnGetBatchMessage)
    {
        ui32Result = psHwCtx->sVxdFuncs.pfnGetBatchMessage(psHwCtx->hVxd,
                                                           &pui8Msg,
                                                           &psHwCtx->sHostMsgStatus,
                                                           &psHwCtx->sDevConfig,
                                                           ui8BatchMessageID,
                                                           psDecPictSegList,
                                                           &sBatchMsgData);
        if (ui32Result != IMG_SUCCESS)
        {
            REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                   "Failed to get decode message");
            return ui32Result;
        }
        IMG_ASSERT(pui8Msg != IMG_NULL);

        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "[MID=0x%02X] [DECODE] [0x%02X]",
            ui8BatchMessageID, VDECFW_MSGID_BATCH);

        IMG_ASSERT(psHwCtx->sVxdFuncs.pfnSendFirmwareMessage != IMG_NULL);
        if (psHwCtx->sVxdFuncs.pfnSendFirmwareMessage)
        {
            ui32Result = psHwCtx->sVxdFuncs.pfnSendFirmwareMessage(psHwCtx->hVxd, MTXIO_AREA_DECODE, pui8Msg);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }

        IMG_ASSERT(psHwCtx->sVxdFuncs.pfnReturnMsg != IMG_NULL);
        if (psHwCtx->sVxdFuncs.pfnReturnMsg)
        {
            psHwCtx->sVxdFuncs.pfnReturnMsg(psHwCtx->hVxd, pui8Msg);
        }
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              hwctrl_PictureReplay

******************************************************************************/
static IMG_RESULT
hwctrl_PictureReplay(
    IMG_HANDLE          hHwCtx,
    DECODER_sDecPict  * psDecPict
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;

    if (psHwCtx->bInitialised)
    {
#ifdef VDEC_MSVDX_HARDWARE
        if (psHwCtx->sDevConfig.eDecodeLevel > VDECDD_DECODELEVEL_DECODER)
        {
            IMG_RESULT ui32Result;

            ui32Result = hwctrl_PowerOn(psHwCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            ui32Result = hwctrl_SendBatchMessage(psHwCtx, psDecPict);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            ui32Result = HWCTRL_CoreSendEndBytes(hHwCtx, psDecPict->psEndBytesBufInfo);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }
#endif
    }

    return IMG_SUCCESS;
}


/*
******************************************************************************

 @Function              decoder_ProcessMTXMsgs

 @Description

 This function is used for now to read through firmware messages and send Dev HW Interrupt.

 @Input     psDdDevContext  : Pointer to hwctrl context.

 @Input     pvUserData      : Pointer to component wide user data.

 @Return    IMG_RESULT      : This function returns either IMG_SUCCESS or an
                              error code.

******************************************************************************/
static IMG_RESULT
hwctrl_ProcessMTXMsgs(
    HWCTRL_sHwCtx     * psHwCtx,
    VXD_sMsgQueue     * psMsgQueue,
    IMG_VOID          * pvUserData
)
{
    IMG_RESULT eResult;

    VXDIO_sHISRMsg *  psHISRMsg;
    VXDIO_sHISRMsg    sHISRMsg;

    IMG_BOOL  bDecodedMsg;

    /* Process all pending HISR messages. */
    psHISRMsg = LST_first(&psMsgQueue->sNewMsgList);
    while (psHISRMsg != IMG_NULL)
    {
        // Make a local copy of the message.
        sHISRMsg = *psHISRMsg;

        /* Remove the message from the queue...*/
        psHISRMsg = LST_removeHead(&psMsgQueue->sNewMsgList);
        if (psHISRMsg != IMG_NULL)
        {
            /* Process the fw message and populate the Pic */
            bDecodedMsg = IMG_FALSE;
            IMG_ASSERT(psHwCtx->sVxdFuncs.pfnProcessMessage != IMG_NULL);
            if (psHwCtx->sVxdFuncs.pfnProcessMessage)
            {
                eResult = psHwCtx->sVxdFuncs.pfnProcessMessage(psHwCtx->hVxd,
                                                               &psMsgQueue->aui32MsgBuf[sHISRMsg.ui32MsgIndex],
                                                               &psHwCtx->sHostMsgStatus,
                                                               &psHwCtx->sPendPictList,
#ifndef IMG_KERNEL_MODULE
                                                               psHwCtx->sDevConfig.bPdumpAndRes,
#endif
                                                               &bDecodedMsg);
                IMG_ASSERT(eResult == IMG_SUCCESS);
                if (eResult != IMG_SUCCESS)
                {
                    /* Free the message */
                    LST_add(&psMsgQueue->sFreeMsgList, psHISRMsg);
                    return eResult;
                }

                if (sHISRMsg.ui32MsgIndex < psMsgQueue->ui32ReadIdx)
                {
                    // We assume here that the buffer wrapped around and this is why the ui32MsgIndex < ui32ReadIdx
                    // so the message should start at the beggining of the buffer. Otherwise the ReadIdx should be set
                    // at the value of ui32MsgIndex;
                    IMG_ASSERT(sHISRMsg.ui32MsgIndex == 0);
                    // When the message didn't fit in the last portion of message buffer
                    // move the read index to the start of the message.
                    psMsgQueue->ui32ReadIdx = 0;
                }

                psMsgQueue->ui32ReadIdx += sHISRMsg.ui32MsgSize;

                /* Free the message */
                LST_add(&psMsgQueue->sFreeMsgList, psHISRMsg);

                if (bDecodedMsg)
                {
#ifndef IMG_KERNEL_MODULE
                    IMG_ASSERT(psHwCtx->sVxdFuncs.pfnPDUMPUnlock != IMG_NULL);
                    if (psHwCtx->sVxdFuncs.pfnPDUMPUnlock)
                    {
                        eResult = psHwCtx->sVxdFuncs.pfnPDUMPUnlock(psHwCtx->hVxd);
                        IMG_ASSERT(eResult == IMG_SUCCESS);
                        if (eResult != IMG_SUCCESS)
                        {
                            return eResult;
                        }
                    }
#endif
                    CORE_DevHwInterrupt(pvUserData, psHwCtx->pvDecCore);
                }
            }
        }

        /* Get the next message...*/
        psHISRMsg = LST_first(&psMsgQueue->sNewMsgList);
    }

    return IMG_SUCCESS;
}

#endif // VDEC_MSVDX_HARDWARE

#ifndef IMG_KERNEL_MODULE
/*!
******************************************************************************

 @Function              HWCTRL_SyncPDumpContexts

 @Description

 Sync pdump contexts

******************************************************************************/
IMG_RESULT
HWCTRL_SyncPDumpContexts(
    IMG_HANDLE          hHwCtx
)
{
    HWCTRL_sHwCtx         * psHwCtx;
    IMG_UINT32              ui32Result = IMG_SUCCESS;

    IMG_ASSERT(hHwCtx != IMG_NULL);
    if(hHwCtx == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    psHwCtx = (HWCTRL_sHwCtx *)hHwCtx;

#ifdef VDEC_MSVDX_HARDWARE
    IMG_ASSERT(psHwCtx->sVxdFuncs.pfnPDUMPSync);
    if (psHwCtx->sVxdFuncs.pfnPDUMPSync)
    {
        ui32Result = psHwCtx->sVxdFuncs.pfnPDUMPSync(psHwCtx->hVxd);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }
#endif

    return ui32Result;
}
#endif

/*!
******************************************************************************

 @Function              HWCTRL_GetCoreStatus

******************************************************************************/
IMG_UINT32
HWCTRL_GetCoreStatus(
    IMG_HANDLE          hHwCtx,
    IMG_UINT32          aui32FreeSlots[VDEC_MAX_PIXEL_PIPES],
    IMG_UINT32          aui32Load[VDEC_MAX_PIXEL_PIPES],
    HWCTRL_sState     * psState
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;
    IMG_UINT32      ui32Result = IMG_SUCCESS;

    IMG_MEMCPY(aui32FreeSlots,
               psHwCtx->ui32NumFreeSlots,
               VDEC_MAX_PIXEL_PIPES*sizeof(aui32FreeSlots[0]));

    IMG_MEMSET(aui32Load, 0, VDEC_MAX_PIXEL_PIPES*sizeof(aui32Load[0]));


#ifdef VDEC_MSVDX_HARDWARE
    if (psHwCtx->sDevConfig.eDecodeLevel > VDECDD_DECODELEVEL_DECODER &&
        psHwCtx->bPower &&
        psHwCtx->sVxdFuncs.pfnGetCoreState != IMG_NULL)
    {
        DECODER_sDecPict  *  psDecPict;
        IMG_UINT32           ui32PictLoadDone = 0;
        VXDIO_sState         sCoreState;
        VXDIO_sState *       psCoreState = IMG_NULL;

        if (IMG_NULL == psState)
        {
            psCoreState = &sCoreState;
        }
        else
        {
            psCoreState  = &psState->sCoreState;
        }

        VDEC_BZERO(psCoreState);
        ui32Result = psHwCtx->sVxdFuncs.pfnGetCoreState(psHwCtx->hVxd, psCoreState);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }

        if (IMG_NULL != psState)
        {
            IMG_MEMCPY(psState->sFwMsgStatus.aui8ControlFenceID,
                       psState->sCoreState.sFwState.aui8ControlFenceID,
                       sizeof(psState->sFwMsgStatus.aui8ControlFenceID));
            IMG_MEMCPY(psState->sFwMsgStatus.aui8DecodeFenceID,
                       psState->sCoreState.sFwState.aui8DecodeFenceID,
                       sizeof(psState->sFwMsgStatus.aui8DecodeFenceID));
            IMG_MEMCPY(psState->sFwMsgStatus.aui8CompletionFenceID,
                       psState->sCoreState.sFwState.aui8CompletionFenceID,
                       sizeof(psState->sFwMsgStatus.aui8CompletionFenceID));

            IMG_MEMCPY(psState->sHostMsgStatus.aui8ControlFenceID,
                       psHwCtx->sHostMsgStatus.aui8ControlFenceID,
                       sizeof(psState->sHostMsgStatus.aui8ControlFenceID));
            IMG_MEMCPY(psState->sHostMsgStatus.aui8DecodeFenceID,
                       psHwCtx->sHostMsgStatus.aui8DecodeFenceID,
                       sizeof(psState->sHostMsgStatus.aui8DecodeFenceID));
            IMG_MEMCPY(psState->sHostMsgStatus.aui8CompletionFenceID,
                       psHwCtx->sHostMsgStatus.aui8CompletionFenceID,
                       sizeof(psState->sHostMsgStatus.aui8CompletionFenceID));

            psState->ui32DWRRetry = psHwCtx->sPrevState.ui32DWRRetry;
        }

        // Obtain up-to-date load based upon the progress of the current picture(s) on the back-end.
        {
            IMG_BOOL abPipeFound[VDEC_MAX_PIXEL_PIPES] = {0};
        psDecPict = LST_first(&psHwCtx->sPendPictList);
            while (psDecPict)
        {
                if(abPipeFound[psDecPict->ui8Pipe-1] == IMG_FALSE)
        {
            IMG_UINT32 ui32NumMbProcessed;
            IMG_UINT32 ui32WidthInMb = (psDecPict->psPictHdrInfo->sCodedFrameSize.ui32Width + (VDEC_MB_DIMENSION - 1)) / VDEC_MB_DIMENSION;

                    ui32NumMbProcessed = (sCoreState.sFwState.asPipeState[psDecPict->ui8Pipe-1].sBeMb.ui32Y * ui32WidthInMb) +
                                                                            sCoreState.sFwState.asPipeState[psDecPict->ui8Pipe-1].sBeMb.ui32X;
            ui32PictLoadDone = hwctrl_CalcMbLoad(ui32NumMbProcessed, psDecPict->psPictHdrInfo->bIntraCoded);
                    aui32Load[psDecPict->ui8Pipe-1] = psHwCtx->ui32Load[psDecPict->ui8Pipe-1] - ui32PictLoadDone;
                    abPipeFound[psDecPict->ui8Pipe-1] = IMG_TRUE;
        }

                psDecPict = LST_next(psDecPict);
        }

            IMG_MEMCPY(aui32Load, psHwCtx->ui32Load, VDEC_MAX_PIXEL_PIPES*sizeof(aui32Load[0]));
    }
    }

error:
#endif
    return ui32Result;
}


/*!
******************************************************************************

 @Function              HWCTRL_CoreFlushMmuCache

******************************************************************************/
IMG_RESULT
HWCTRL_CoreFlushMmuCache(
    IMG_HANDLE  hHwCtx
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;
    IMG_UINT32      ui32Result;

    if (psHwCtx->bInitialised)
    {
        if (psHwCtx->sDevConfig.eDecodeLevel > VDECDD_DECODELEVEL_DECODER && psHwCtx->bPower)
        {
            IMG_ASSERT(psHwCtx->sVxdFuncs.pfnFlushMmuCache != IMG_NULL);
            if (psHwCtx->sVxdFuncs.pfnFlushMmuCache)
            {
                ui32Result = psHwCtx->sVxdFuncs.pfnFlushMmuCache(psHwCtx->hVxd);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    goto error;
                }
            }
        }
    }

    return IMG_SUCCESS;

error:
    return ui32Result;
}


/*!
******************************************************************************

 @Function              HWCTRL_HandleInterrupt

 @Description

 This function handles the device interrupts and makes a request for the decoder
 to later service the core interrupt.

******************************************************************************/
IMG_RESULT
HWCTRL_HandleInterrupt(
    IMG_HANDLE  hHwCtx,
    IMG_VOID *  pvUserData
)
{
    IMG_UINT32          ui32Result = IMG_SUCCESS;

#ifdef VDEC_MSVDX_HARDWARE
    HWCTRL_sHwCtx     * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;
    IMG_BOOL            bMtxIrq;

    IMG_ASSERT(hHwCtx);

    // We want to make sure Power has not been turned off and this interrupt needs to be ignored.
    // Also need to make sure we are configured to handle this.
    if (psHwCtx->bPower)
    {
        VXD_sIntStatus* psIntStatus = &psHwCtx->sIntStatus;

        IMG_ASSERT(psHwCtx->sVxdFuncs.pfnHandleInt != IMG_NULL);
        if (psHwCtx->sVxdFuncs.pfnHandleInt)
        {
            ui32Result = psHwCtx->sVxdFuncs.pfnHandleInt(psHwCtx->hVxd, psIntStatus);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);

            if (psIntStatus->ui32Pending & MSVDX_CORE_CR_MSVDX_INTERRUPT_STATUS_CR_MMU_FAULT_IRQ_MASK)
            {
            IMG_UINT32 aui32NumFreeSlots[VDEC_MAX_PIXEL_PIPES];
            IMG_UINT32 aui32PipeLoad[VDEC_MAX_PIXEL_PIPES];
                HWCTRL_sState   sState;
                IMG_UINT8       uiPipeMinus1 = 0;

                // Report the fault.
                REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE,
                       "MMU %s fault from %s %s @ 0x%08X",
                       (psIntStatus->MMU_PF_N_RW) ? "PAGE" : "PROTECTION",
                           (psIntStatus->ui32Requestor & (1<<0)) ? "DMAC" :
                           (psIntStatus->ui32Requestor & (1<<1)) ? "VEC"  :
                           (psIntStatus->ui32Requestor & (1<<2)) ? "VDMC" :
                           (psIntStatus->ui32Requestor & (1<<3)) ? "VDEB" :
                                                                   "INVALID",
                       (psIntStatus->MMU_FAULT_RNW) ? "READING" : "WRITING",
                       psIntStatus->MMU_FAULT_ADDR);

            HWCTRL_GetCoreStatus(psHwCtx, aui32NumFreeSlots, aui32PipeLoad, &sState);
                for(uiPipeMinus1 = 0; uiPipeMinus1 < psHwCtx->ui32NumPipes; uiPipeMinus1++)
                {
                    REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE, "Dumping debug info for pipe %d:", uiPipeMinus1 + 1);
                    hwctrl_DumpState(&sState.sCoreState, &sState.sCoreState, psIntStatus, uiPipeMinus1);
                }

                /* Now lets dump The complete Register spaces for CORE, MTX, VEC, VDMC, VDEB, DMAC and VLR. Also Dump RTM register for HW Debug. */
                if (psHwCtx->sDevConfig.bCoreDump)
                {
                    IMG_ASSERT(psHwCtx->sVxdFuncs.pfnDumpRegisters != IMG_NULL);
                    if (psHwCtx->sVxdFuncs.pfnDumpRegisters)
                    {
                        ui32Result = psHwCtx->sVxdFuncs.pfnDumpRegisters(psHwCtx->hVxd);
                        IMG_ASSERT(ui32Result == IMG_SUCCESS);
                        if (ui32Result != IMG_SUCCESS)
                        {
                            goto error;
                        }
                    }
                }

                // Do the Device Reset
                // ...
                ui32Result = CORE_DevReset(psHwCtx->pvCompInitUserData, psHwCtx->ui32CoreNum, RESET_MMUPF);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    goto error;
                }
            }

#ifdef VDEC_USE_PVDEC
            bMtxIrq = psIntStatus->ui32Pending & PVDEC_CORE_CR_PVDEC_HOST_INTERRUPT_STATUS_CR_HOST_PROC_IRQ_MASK;
#else /* ndef VDEC_USE_PVDEC */
            bMtxIrq = psIntStatus->ui32Pending & MSVDX_CORE_CR_MSVDX_INTERRUPT_STATUS_CR_MTX_IRQ_MASK;
#endif /* ndef VDEC_USE_PVDEC */

            if (bMtxIrq && (IMG_NULL != psIntStatus->psMsgQueue))
            {
#ifdef IMG_KERNEL_MODULE
#ifdef VDEC_USE_PVDEC
                // Checking the consistency of the message queue: either the queue is not empty and it's signalled as not empty
                // or the queue is empty and it's not signalled as not empty. The second case is acceptable as messages for this
                // interrupt may have been handled with messages signalled by the previous interrupt due to latencies.
                IMG_ASSERT((psIntStatus->psMsgQueue->bQueued && !LST_empty(&psIntStatus->psMsgQueue->sNewMsgList)) ||
                           (!psIntStatus->psMsgQueue->bQueued && LST_empty(&psIntStatus->psMsgQueue->sNewMsgList)));
                // Process messages only if there are any.
                if(psIntStatus->psMsgQueue->bQueued && !LST_empty(&psIntStatus->psMsgQueue->sNewMsgList))
                {
#else /* ndef VDEC_USE_PVDEC */
                // This checks that we don't get any spurious interrupts.
                // When run in no-bridging because of the interrupt latency and
                // the way we process messages (we process all the messages we find
                // in the VLR buffer not only the ones that each interrupt is 'associated')
                // we may end up here with an interrupt but no new messages and this will
                // be valid.
                IMG_ASSERT(psIntStatus->psMsgQueue->bQueued && !LST_empty(&psIntStatus->psMsgQueue->sNewMsgList));
#endif /* ndef VDEC_USE_PVDEC */
#else /* ndef IMG_KERNEL_MODULE */
                // In no-bridging if there are no messages just continue. We must have
                // processed them
                if(psIntStatus->psMsgQueue->bQueued)
                {
#endif /* ndef IMG_KERNEL_MODULE */
                    do
                    {
                        /* Deal with MTX messages. */
                        hwctrl_ProcessMTXMsgs(psHwCtx, psIntStatus->psMsgQueue, pvUserData);

                        if (!psIntStatus->psMsgQueue->bEmpty)
                        {
                            REPORT(REPORT_MODULE_HWCTRL, REPORT_WARNING, "Must service message buffer again...");

                            IMG_ASSERT(psHwCtx->sVxdFuncs.pfnHandleInt != IMG_NULL);
                            if (psHwCtx->sVxdFuncs.pfnHandleInt)
                            {
                                ui32Result = psHwCtx->sVxdFuncs.pfnHandleInt(psHwCtx->hVxd, psIntStatus);
                                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                                if (ui32Result != IMG_SUCCESS)
                                {
                                    goto error;
                                }
                            }
                        }

                    }
                    while (!psIntStatus->psMsgQueue->bEmpty && psIntStatus->psMsgQueue->bQueued);
#if !defined(IMG_KERNEL_MODULE) || defined(VDEC_USE_PVDEC)
                }
#endif /* !defined(IMG_KERNEL_MODULE) || defined(VDEC_USE_PVDEC) */
            }
        }
    }

    return IMG_SUCCESS;

error:
#endif /* VDEC_MSVDX_HARDWARE */

	return ui32Result;

}


/*!
******************************************************************************

 @Function              HWCTRL_PowerOff

 @Description

 This function handles when the device is going off.

******************************************************************************/
IMG_RESULT
HWCTRL_PowerOff(
    IMG_HANDLE  hHwCtx
)
{
    IMG_UINT32  ui32Result = IMG_SUCCESS;

#ifdef VDEC_MSVDX_HARDWARE
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;

    if (psHwCtx->bPower && psHwCtx->sDevConfig.eDecodeLevel > VDECDD_DECODELEVEL_DECODER)
    {
        /* Disable and clear all core interrupts before going further with reset.
         * This guards against getting core interrupts in the middle of the reset procedure,
         * which can end up in interrupt storm. */
        if (psHwCtx->sVxdFuncs.pfnDisableCoreInterrupts)
        {
            ui32Result = psHwCtx->sVxdFuncs.pfnDisableCoreInterrupts(psHwCtx->hVxd);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }
        }

        // XXX: Danish Reset and Resume doesn't work with FAKE mtx. Stop and Start MTX needs to be fixed
        // XXX: to get it to work.
        // Turn the power flag off. Any subsequent interrupts from the hardware will be ignored.
        // We need to disable interrupts. There is a Service Time Expiry task running, which when
        // check the status of the hardware in interrupt context, that might read from hardware while
        // we have disabled the clocks. This will lockup the hardware.
        SYSOSKM_DisableInt();
        psHwCtx->bPower = IMG_FALSE;
        SYSOSKM_EnableInt();

#ifdef FW_PRINT
        psHwCtx->bPrintTaskRequestedActive = IMG_FALSE;
        if(psHwCtx->hFWPrintTimerHandle)
        {
            SYSOSKM_DestroyTimer( psHwCtx->hFWPrintTimerHandle );
            psHwCtx->hFWPrintTimerHandle = IMG_NULL;
        }
#endif //FW_PRINT

        // Destroy the service timer expiry off.
        if(psHwCtx->hTimerHandle)
        {
            SYSOSKM_DestroyTimer(psHwCtx->hTimerHandle);
            psHwCtx->hTimerHandle = IMG_NULL;
        }

#ifndef IMG_KERNEL_MODULE
        // Sync all pdump scripts before deinitializing. This makes sure
        // that teardown will not happen while the backend context is waiting
        // for pictures to come up
        IMG_ASSERT(psHwCtx->sVxdFuncs.pfnPDUMPSync != IMG_NULL);
        if (psHwCtx->sVxdFuncs.pfnPDUMPSync)
        {
            ui32Result = psHwCtx->sVxdFuncs.pfnPDUMPSync(psHwCtx->hVxd);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }
        }
#endif
        IMG_ASSERT(psHwCtx->sVxdFuncs.pfnDeInitialise != IMG_NULL);
        if (psHwCtx->sVxdFuncs.pfnDeInitialise)
        {
            ui32Result = psHwCtx->sVxdFuncs.pfnDeInitialise(psHwCtx->hVxd);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }
        }

        DEBUG_REPORT(REPORT_MODULE_HWCTRL,
            "HWCTRL has performed Power off operations on Core %d",
            psHwCtx->ui32CoreNum);
    }

error:

#endif // VDEC_MSVDX_HARDWARE

    return ui32Result;
}


#ifdef STACK_USAGE_TEST
/*!
******************************************************************************

 @Function              HWCTRL_checkStackUsage

 @Description

 This function check the stack usage.

******************************************************************************/
IMG_RESULT
HWCTRL_checkStackUsage(IMG_HANDLE hHwCtx)
{
    IMG_RESULT rResult;
    IMG_UINT32 aui32StackInfo[6];
    HWCTRL_sHwCtx * psStackCtx = (HWCTRL_sHwCtx *) hHwCtx;

    rResult = IMG_SUCCESS;

    /* support only MSVDX at the moment. Do the check here */
#ifdef VDEC_MSVDX_HARDWARE

    /* report the start of stack usage check */
    REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE,
        "***** STACK USAGE TEST - Getting maximum stack usage info...");

    /* call MSVDX function to get stack usage */
    rResult = MSVDX_GetStackUsage(psStackCtx->hVxd,
                                  &aui32StackInfo[0]);
    if(IMG_SUCCESS != rResult)
    {
        /* error during checking stack usage */
        REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
            "***** STACK USAGE TEST - Maximum Stack Usage: NONE - AN UNEXPECTED ERROR OCCURRED");
    }
    else
    {
        /* stack info are valid */
        REPORT(REPORT_MODULE_HWCTRL, REPORT_NOTICE,
            "***** STACK USAGE TEST - STACK RESULTS:\n-- Stack space: %d 32-bit words\n-- Maximum stack track: %d 32-bit words (%d bytes) [%d %%]\n-- Stack usage of the maximum track: %d 32-bit words (%d bytes) [%d %% of maximum stack usage]\n-- Effective stack usage: %d %% of entire stack",
            aui32StackInfo[5], aui32StackInfo[0], aui32StackInfo[0]*4, aui32StackInfo[1], aui32StackInfo[2], aui32StackInfo[2]*4, aui32StackInfo[3], aui32StackInfo[4]);
    }

#else

    /* report the start of stack usage check */
    REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
        "***** STACK USAGE TEST - ATTENTION: Stack usage test is not implemented for this platform");

#endif

    return rResult;
}
#endif
/*!
******************************************************************************

 @Function              hwctrl_PowerOn

 @Description

 This function handles when the device is turning on.

******************************************************************************/
static IMG_RESULT
hwctrl_PowerOn(
    IMG_HANDLE                  hHwCtx
)
{
    IMG_UINT32  ui32Result = IMG_SUCCESS;

#ifdef VDEC_MSVDX_HARDWARE
#ifdef POST_TEST
    IMG_UINT32  aui32CheckPoints[NUM_OF_FW_INIT_CHECKPOINTS];
    IMG_UINT32  ui32TimeoutCnt = 1000;
#endif
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;

    if (!psHwCtx->bPower  && psHwCtx->sDevConfig.eDecodeLevel > VDECDD_DECODELEVEL_DECODER)
    {
        VDECFW_sCoreInitData    sInitConfig;

        IMG_ASSERT(psHwCtx->sVxdFuncs.pfnInitialise != IMG_NULL);
        if (psHwCtx->sVxdFuncs.pfnInitialise)
        {
            ui32Result = psHwCtx->sVxdFuncs.pfnInitialise(psHwCtx->hVxd, &sInitConfig);
            if (ui32Result != IMG_SUCCESS)
            {
                REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                        "ERROR: Failed initialising core %d!",
                        psHwCtx->ui32CoreNum);
                goto error;
            }

#ifdef POST_TEST
#ifdef SEC_USE_REAL_FW
            /* if POST required from command line */
            if (IMG_TRUE == psHwCtx->sDevConfig.bPost)
            {
                /* Wait first and second check-points from firmware until timeout */
                do
                {
                    /* read first and second VLR check-points */
                    MSVDX_ReadVLR(psHwCtx->hVxd,
                                 (VLR_FIRMWARE_STATE_AREA_BASE_ADDR + (VDECFW_CHECKPOINT_FI_START * 4)),
                                 &aui32CheckPoints[0],
                                 (NUM_OF_FW_INIT_CHECKPOINTS - 1));

                    /* decrement timeout counter */
                    ui32TimeoutCnt--;
                }
                /* check second check-point only at the moment */
                while(((aui32CheckPoints[0] != CHKPNT_FW_VALUE) || (aui32CheckPoints[1] != CHKPNT_FW_VALUE))
                   && (ui32TimeoutCnt > 0));
                /* check timeout */
                if (0 == ui32TimeoutCnt)
                {
                    /* Initialisation end checkpoint FAILED */

                    REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                        "***** POST: Firmware initialisation check-points for core %d FAILED",
                           psHwCtx->ui32CoreNum);

                    ui32Result = IMG_ERROR_DEVICE_UNAVAILABLE;
                    goto error;
                }
                else
                {
                    /* The second check-point has been reached from the firmware */

                    REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                        "***** POST: Firmware initialisation check-points for core %d PASSED",
                           psHwCtx->ui32CoreNum);
                }

                /* re-init timeout counter */
                ui32TimeoutCnt = 1000;
            }
            else
            {
                /* do nothing */
            }
#endif
#endif
            /* Send init message to the firmware. */
            ui32Result = hwctrl_SendInitMessage(psHwCtx,
                                                &sInitConfig,
                                                &psHwCtx->sDevPtdBufInfo);
            if (ui32Result != IMG_SUCCESS)
            {
                REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                       "ERROR: Failed sending init message to firmware for core %d!",
                       psHwCtx->ui32CoreNum);
            }

            hwctrl_SetupDWR(psHwCtx, (SYSOSKM_pfnTimer)hwctrl_MonitorHwState);

#ifdef POST_TEST
            /* if POST required from command line */
            if (IMG_TRUE == psHwCtx->sDevConfig.bPost)
            {
                /* Send first POST message to the firmware. */
                ui32Result = hwctrl_SendPOSTMessage(psHwCtx, VDECFW_POST_FIRST_MSG, &psHwCtx->sDevPtdBufInfo);
                if (IMG_SUCCESS != ui32Result)
                {
                    /* failure to send a POST message from HOST to firmware */

                    REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                           "***** POST: Sending check-point POST message to firmware for core %d FAILED",
                           psHwCtx->ui32CoreNum);
                    goto error;
                }

                /* Wait third check-point (first message) from firmware until timeout. */
                do
                {
                    /* read third VLR check-point only */
                    MSVDX_ReadVLR(psHwCtx->hVxd,
                                 (VLR_FIRMWARE_STATE_AREA_BASE_ADDR + (VDECFW_CHECKPOINT_FI_START * 4)),
                                 &aui32CheckPoints[0],
                                 NUM_OF_FW_INIT_CHECKPOINTS);

                    /* decrement timeout counter */
                    ui32TimeoutCnt--;
                }
                /* check third check-point only that is in the first array position */
                while((aui32CheckPoints[2] != CHKPNT_FW_VALUE)
                   && (ui32TimeoutCnt > 0));
                /* check timeout */
                if (0 == ui32TimeoutCnt)
                {
                    /* Message interrupt checkpoint FAILED */

                    REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                           "***** POST: Firmware first message check-point for core %d FAILED",
                           psHwCtx->ui32CoreNum);

                    ui32Result = IMG_ERROR_DEVICE_UNAVAILABLE;
                    goto error;
                }
                else
                {
                    /* The third check-point has been reached from the firmware */

                    REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                        "***** POST: Firmware first message check-point for core %d PASSED",
                           psHwCtx->ui32CoreNum);
                }

                /* Send memory test result request message to the firmware. */
                ui32Result = hwctrl_SendPOSTMessage(psHwCtx, VDECFW_POST_GET_INIT_RES, &psHwCtx->sDevPtdBufInfo);
                if (IMG_SUCCESS != ui32Result)
                {
                    /* failure to send a POST message from HOST to firmware */

                    REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                           "***** POST: Sending POST memory test message to firmware for core %d FAILED",
                           psHwCtx->ui32CoreNum);
                    goto error;
                }

                /* Send calculation test request message to the firmware. */
                ui32Result = hwctrl_SendPOSTMessage(psHwCtx, VDECFW_POST_START_CALC, &psHwCtx->sDevPtdBufInfo);
                if (IMG_SUCCESS != ui32Result)
                {
                    /* failure to send a POST message from HOST to firmware */

                    REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                           "***** POST: Sending POST calculation test message to firmware for core %d FAILED",
                           psHwCtx->ui32CoreNum);
                    goto error;
                }
            }
            else
            {
                /* do nothing */
            }
#endif

#ifdef FW_PRINT
            psHwCtx->bPrintTaskRequestedActive = IMG_TRUE;
            SYSOSKM_CreateTimer( (SYSOSKM_pfnTimer)hwctrl_MTXPrintTask, psHwCtx, 1, &psHwCtx->hFWPrintTimerHandle );
#endif //FW_PRINT

            SYSOSKM_DisableInt();
            psHwCtx->bPower = IMG_TRUE;
            SYSOSKM_EnableInt();

#ifndef IMG_KERNEL_MODULE
            {
                // Unlock pdump context that many times as the decode slots per core we have minus 1
                // (we lock after we submit a picture).
                // This will allow that many pictures in the pipeline
                IMG_UINT32  ui32I = 0;
                IMG_ASSERT(psHwCtx->sVxdFuncs.pfnPDUMPUnlock != IMG_NULL);
                if (psHwCtx->sVxdFuncs.pfnPDUMPUnlock)
                {
                for(ui32I = 0; ui32I < psHwCtx->ui32NumPipes * psHwCtx->sDevConfig.ui32NumSlotsPerPipe - 1; ui32I++)
                    {
                        ui32Result = psHwCtx->sVxdFuncs.pfnPDUMPUnlock(psHwCtx->hVxd);
                        if(ui32Result != IMG_SUCCESS)
                        {
                            REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                               "ERROR: Failed unlock pdump context");
                            goto error;
                        }
                    }
                }

                // Add a sync across all pdump scripts. This will prevent backend pdump
                // from trying to poll for pictures before driver submitted any.
                IMG_ASSERT(psHwCtx->sVxdFuncs.pfnPDUMPSync != IMG_NULL);
                if (psHwCtx->sVxdFuncs.pfnPDUMPSync)
                {
                    ui32Result = psHwCtx->sVxdFuncs.pfnPDUMPSync(psHwCtx->hVxd);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                           "ERROR: Failed sync pdump contexts");
                        goto error;
                    }
                }
            }
#endif

            DEBUG_REPORT(REPORT_MODULE_HWCTRL,
                "HWCTRL has performed Power on operations on Core %d",
                psHwCtx->ui32CoreNum);
        }
    }

error:

#endif // VDEC_MSVDX_HARDWARE

    return ui32Result;
}





/*!
******************************************************************************

 @Function              HWCTRL_PictureSubmit

******************************************************************************/
IMG_RESULT
HWCTRL_PictureSubmit(
    IMG_HANDLE          hHwCtx,
    DECODER_sDecPict *  psDecPict
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;

    if (psHwCtx->bInitialised)
    {
#ifdef VDEC_MSVDX_HARDWARE
        if (psHwCtx->sDevConfig.eDecodeLevel > VDECDD_DECODELEVEL_DECODER)
        {
            IMG_RESULT ui32Result;

            ui32Result = hwctrl_PowerOn(psHwCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            // Add picture to core decode list
            LST_add(&psHwCtx->sPendPictList, psDecPict);

            ui32Result = hwctrl_SendDecodeMessage(psHwCtx,
                                                  psDecPict->psTransactionInfo->psDdBufInfo,
                                                  psDecPict->psStrPtdBufInfo);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            psHwCtx->ui32Load[psDecPict->ui8Pipe - 1] += hwctrl_CalculateLoad(psDecPict->psPictHdrInfo);
        }
        else
#endif // VDEC_MSVDX_HARDWARE
        {
            // Add picture to core decode list
            LST_add(&psHwCtx->sPendPictList, psDecPict);
        }

        psHwCtx->ui32NumFreeSlots[psDecPict->ui8Pipe - 1]--;
    }

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              HWCTRL_DiscardHeadPicList

******************************************************************************/
IMG_RESULT
HWCTRL_DiscardHeadPicList(
    IMG_HANDLE          hHwCtx
)
{
    DECODER_sDecPict    *   psDecPict;
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;
    IMG_UINT32  ui32Result;

    if(psHwCtx->bInitialised)
    {
        // Remove the head of the list
        psDecPict = LST_first(&psHwCtx->sPendPictList);
        if(psDecPict)
        {
            // Mark the picture
            psDecPict->psFirstFieldFwMsg->sPictDecoded.bDWRFired = IMG_TRUE;
            // Send async message for this discarded picture
            ui32Result = CORE_DevSwInterruptPicDiscarded(psHwCtx->pvCompInitUserData, psHwCtx->pvDecCore);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;

            }
            DEBUG_REPORT(REPORT_MODULE_HWCTRL,
                "HWCTRL has discarded the picture at the head on Core %d",
                psHwCtx->ui32CoreNum);
        }
    }

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              HWCTRL_PostCoreReplay

******************************************************************************/
IMG_RESULT
HWCTRL_PostCoreReplay(
    IMG_HANDLE          hHwCtx
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;
    IMG_UINT32  ui32Result = IMG_SUCCESS;

    if (psHwCtx->bInitialised)
    {
#ifdef VDEC_MSVDX_HARDWARE
        ui32Result = CORE_DevReplay(psHwCtx->pvCompInitUserData, psHwCtx->ui32CoreNum);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            goto error;
        }
        DEBUG_REPORT(REPORT_MODULE_HWCTRL,
                     "HWCTRL has posted a AsynMessage for Replay for core %d",
                     psHwCtx->ui32CoreNum);
#endif
    }

#ifdef VDEC_MSVDX_HARDWARE
error:
#endif
    return ui32Result;
}

/*!
******************************************************************************

@Function              HWCTRL_CoreReplay

******************************************************************************/
IMG_RESULT
HWCTRL_CoreReplay(
    IMG_HANDLE          hHwCtx
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;
    IMG_UINT32  ui32Result = IMG_SUCCESS;

    if (psHwCtx->bInitialised)
    {
#ifdef VDEC_MSVDX_HARDWARE
        DECODER_sDecPict  * psDecPict = LST_first(&psHwCtx->sPendPictList);

        /* Replay the contents of the pending list. */
        while (psDecPict)
        {
            /* Reschedule the picture. */
            ui32Result = hwctrl_PictureReplay(hHwCtx, psDecPict);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }

            psDecPict = LST_next(psDecPict);
        }

        DEBUG_REPORT(REPORT_MODULE_HWCTRL,
                     "HWCTRL has performed Replay operation on Core %d",
                     psHwCtx->ui32CoreNum);
#endif
    }

#ifdef VDEC_MSVDX_HARDWARE
error:
#endif
    return ui32Result;
}

/*!
******************************************************************************

 @Function              HWCTRL_PictureSubmitBatch

******************************************************************************/
IMG_RESULT
HWCTRL_PictureSubmitBatch(
    IMG_HANDLE          hHwCtx,
    DECODER_sDecPict  * psDecPict,
    IMG_HANDLE          hResources,
    VXDIO_sPtdInfo    * psPtdInfo
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;

    if (psHwCtx->bInitialised)
    {
#ifdef VDEC_MSVDX_HARDWARE
        if (psHwCtx->sDevConfig.eDecodeLevel > VDECDD_DECODELEVEL_DECODER)
        {
            IMG_RESULT ui32Result;

            ui32Result = hwctrl_PowerOn(psHwCtx);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            // Add picture to core decode list
            LST_add(&psHwCtx->sPendPictList, psDecPict);

            ui32Result = hwctrl_SendBatchMessage(psHwCtx,
                                                 psDecPict);

            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }

            psHwCtx->ui32Load[psDecPict->ui8Pipe - 1] += hwctrl_CalculateLoad(psDecPict->psPictHdrInfo);
        }
        else
#endif
        {
            // Add picture to core decode list
            LST_add(&psHwCtx->sPendPictList, psDecPict);
        }

        psHwCtx->ui32NumFreeSlots[psDecPict->ui8Pipe - 1]--;
    }

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              HWCTRL_PictureSubmitFragment

******************************************************************************/
IMG_RESULT
HWCTRL_PictureSubmitFragment(
    IMG_HANDLE    hHwCtx,
    LST_T       * psDecPictSegList
)
{
#ifdef VDEC_MSVDX_HARDWARE
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;

    if (psHwCtx->bInitialised &&
        (psHwCtx->sDevConfig.eDecodeLevel > VDECDD_DECODELEVEL_DECODER))
    {
        /* Load the Base component if needed */

        /* Create a message here for bitstream dma buffer for the fragment */
        VDECDD_sDdBufMapInfo *  psDdBufMapInfo;
        DECODER_sDecPictSeg * psDecPictSeg = IMG_NULL;
        IMG_UINT32 ui32Result;

        psDecPictSeg = (DECODER_sDecPictSeg *) LST_first(psDecPictSegList);
        while(psDecPictSeg != IMG_NULL)
        {
            IMG_UINT8 * pui8Msg;

            /* Get access to map info context...*/
            ui32Result = RMAN_GetResource(psDecPictSeg->psBitStrSeg->ui32BufMapId, VDECDD_BUFMAP_TYPE_ID, (IMG_VOID **)&psDdBufMapInfo, IMG_NULL);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
            IMG_ASSERT(psHwCtx->sVxdFuncs.pfnGetFragmentMessage != IMG_NULL);
            if (psHwCtx->sVxdFuncs.pfnGetFragmentMessage)
            {
                ui32Result = psHwCtx->sVxdFuncs.pfnGetFragmentMessage(psHwCtx->hVxd,
                                                                      &pui8Msg,
                                                                      &psHwCtx->sHostMsgStatus,
                                                                      psDdBufMapInfo,
                                                                      psDecPictSeg);
                if (ui32Result != IMG_SUCCESS)
                {
                    REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                            "Failed to get fragment message");
                    return ui32Result;
                }
                IMG_ASSERT(pui8Msg != IMG_NULL);

                DEBUG_REPORT(REPORT_MODULE_HWCTRL, "[MID=0x%02X] [DECODE] [0x%02X]",
                    psHwCtx->sHostMsgStatus.aui8DecodeFenceID[VDECFW_MSGID_BITSTREAM_BUFFER-VDECFW_MSGID_PSR_PADDING], VDECFW_MSGID_BITSTREAM_BUFFER);

                IMG_ASSERT(psHwCtx->sVxdFuncs.pfnSendFirmwareMessage != IMG_NULL);
                if (psHwCtx->sVxdFuncs.pfnSendFirmwareMessage)
                {
                    ui32Result = psHwCtx->sVxdFuncs.pfnSendFirmwareMessage(psHwCtx->hVxd, MTXIO_AREA_DECODE, pui8Msg);
                    IMG_ASSERT(ui32Result == IMG_SUCCESS);
                    if (ui32Result != IMG_SUCCESS)
                    {
                        return ui32Result;
                    }
                }

                IMG_ASSERT(psHwCtx->sVxdFuncs.pfnReturnMsg != IMG_NULL);
                if (psHwCtx->sVxdFuncs.pfnReturnMsg)
                {
                    psHwCtx->sVxdFuncs.pfnReturnMsg(psHwCtx->hVxd, pui8Msg);
                }
            }

            psDecPictSeg = LST_next(psDecPictSeg);
        }
    }
#endif

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              HWCTRL_KickSwInterrupt

******************************************************************************/
IMG_RESULT
HWCTRL_KickSwInterrupt(
    IMG_HANDLE  hHwCtx,
    IMG_HANDLE  hDecServiceInt
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *)     hHwCtx;

    {
        IMG_RESULT ui32Result;

        /* Generate a Dev SW Interrupt */
        ui32Result = CORE_DevSwInterrupt(psHwCtx->pvCompInitUserData, hDecServiceInt);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            //return ui32Result;
        }
    }

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              HWCTRL_CoreSendEndBytes

******************************************************************************/
IMG_RESULT
HWCTRL_CoreSendEndBytes(
    IMG_HANDLE            hHwCtx,
    VXDIO_sDdBufInfo    * psEndBytesBufInfo
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *)hHwCtx;
    IMG_RESULT ui32Result;

#ifdef VDEC_MSVDX_HARDWARE
    if (psHwCtx->sDevConfig.eDecodeLevel > VDECDD_DECODELEVEL_DECODER)
    {
        if (psHwCtx->bInitialised && psHwCtx->sVxdFuncs.pfnGetEndBytesMessage != IMG_NULL)
        {
            IMG_UINT8 * pui8Msg;
            ui32Result = psHwCtx->sVxdFuncs.pfnGetEndBytesMessage(psHwCtx->hVxd,
                                                                  &pui8Msg,
                                                                  &psHwCtx->sHostMsgStatus,
                                                                  psEndBytesBufInfo);
            if (ui32Result != IMG_SUCCESS)
            {
                REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                        "Failed to get end bytes message");
                return ui32Result;
            }
            IMG_ASSERT(pui8Msg != IMG_NULL);

            DEBUG_REPORT(REPORT_MODULE_HWCTRL, "[MID=0x%02X] [DECODE] [0x%02X]",
                psHwCtx->sHostMsgStatus.aui8DecodeFenceID[VDECFW_MSGID_BITSTREAM_BUFFER-VDECFW_MSGID_PSR_PADDING], VDECFW_MSGID_BITSTREAM_BUFFER);

            IMG_ASSERT(psHwCtx->sVxdFuncs.pfnSendFirmwareMessage != IMG_NULL);
            if (psHwCtx->sVxdFuncs.pfnSendFirmwareMessage)
            {
                ui32Result = psHwCtx->sVxdFuncs.pfnSendFirmwareMessage(psHwCtx->hVxd, MTXIO_AREA_DECODE, pui8Msg);
                IMG_ASSERT(ui32Result == IMG_SUCCESS);
                if (ui32Result != IMG_SUCCESS)
                {
                    return ui32Result;
                }
            }

            IMG_ASSERT(psHwCtx->sVxdFuncs.pfnReturnMsg != IMG_NULL);
            if (psHwCtx->sVxdFuncs.pfnReturnMsg)
            {
                psHwCtx->sVxdFuncs.pfnReturnMsg(psHwCtx->hVxd, pui8Msg);
            }
        }
#ifndef IMG_KERNEL_MODULE
            IMG_ASSERT(psHwCtx->sVxdFuncs.pfnPDUMPLock != IMG_NULL);
            if (psHwCtx->sVxdFuncs.pfnPDUMPLock)
            {
                ui32Result = psHwCtx->sVxdFuncs.pfnPDUMPLock(psHwCtx->hVxd);
                if (ui32Result != IMG_SUCCESS)
                {
                    REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                           "Failed to get PDUMP Lock");
                    return ui32Result;
                }
            }
#endif
    }
    else
#endif
    {
#ifdef HWCTRL_REPLACEMENT_HW_THREAD
        HWCTRL_sEventInfo   * psEventInfo;

        VDEC_MALLOC(psEventInfo);
        IMG_ASSERT(psEventInfo != IMG_NULL);
        VDEC_BZERO(psEventInfo);

        psEventInfo->psHwCtx = psHwCtx;

        // Fake the hardware processing.
        hwctrl_SendEvent(psHwCtx->psTaskInfo,
                         HWCTRL_EVENT_DECODE_PICTURE,
                         psEventInfo);
#else
        /* Generate a Dev HW Interrupt and not submit the picture */
        ui32Result = CORE_DevHwInterrupt(psHwCtx->pvCompInitUserData, psHwCtx->pvDecCore);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            //return ui32Result;
        }
    }
#endif

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              HWCTRL_GetPicPendPictList

******************************************************************************/
IMG_RESULT
HWCTRL_GetPicPendPictList(
    IMG_HANDLE           hHwCtx,
    IMG_UINT32           ui32TransactionId,
    DECODER_sDecPict  ** ppsDecPict
)
{
    HWCTRL_sHwCtx     * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;
    DECODER_sDecPict  * psDecPic;

    psDecPic = LST_first(&psHwCtx->sPendPictList);
    while(psDecPic)
    {
        if(psDecPic->ui32TransactionId == ui32TransactionId)
        {
            *ppsDecPict = psDecPic;
            break;
        }
        psDecPic = LST_next(psDecPic);
    }

    if(psDecPic == IMG_NULL)
    {
        REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
            "Failed to find pending picture from transaction ID");
        return IMG_ERROR_INVALID_ID;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              HWCTRL_PeekHeadPicList

******************************************************************************/
IMG_RESULT
HWCTRL_PeekHeadPicList(
    IMG_HANDLE           hHwCtx,
    DECODER_sDecPict  ** ppsDecPict
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;

    if (psHwCtx)
    {
        *ppsDecPict = LST_first(&psHwCtx->sPendPictList);
    }

    if (*ppsDecPict)
    {
        return IMG_SUCCESS;
    }
    else
    {
        return IMG_ERROR_GENERIC_FAILURE;
    }
}
/*!
******************************************************************************

 @Function              HWCTRL_RemoveHeadPicList

******************************************************************************/
IMG_RESULT
HWCTRL_RemoveHeadPicList(
    IMG_HANDLE           hHwCtx,
    DECODER_sDecPict  ** ppsDecPict
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;

    if(psHwCtx)
    {
        *ppsDecPict = LST_removeHead(&psHwCtx->sPendPictList);

        if (*ppsDecPict)
        {
            // Indicate that a decode slot is now free.
            psHwCtx->ui32NumFreeSlots[(*ppsDecPict)->ui8Pipe - 1]++;

#ifdef VDEC_MSVDX_HARDWARE
            if (psHwCtx->sDevConfig.eDecodeLevel > VDECDD_DECODELEVEL_DECODER)
            {
                psHwCtx->ui32Load[(*ppsDecPict)->ui8Pipe - 1] -= hwctrl_CalculateLoad((*ppsDecPict)->psPictHdrInfo);
            }
#endif
        }
    }
    return IMG_SUCCESS;
}

#ifdef VDEC_USE_PVDEC
/*!
******************************************************************************

 @Function              HWCTRL_GetDecodedPicture

******************************************************************************/
IMG_RESULT
HWCTRL_GetDecodedPicture(
    IMG_HANDLE           hHwCtx,
    DECODER_sDecPict  ** ppsDecPict
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;

    if (psHwCtx)
    {
        DECODER_sDecPict *  psCurDecPict;

        // Ensure that this picture is in the list.
        psCurDecPict = LST_first(&psHwCtx->sPendPictList);
        while (psCurDecPict)
        {
            if (psCurDecPict->bDecoded)
            {
                *ppsDecPict = psCurDecPict;
                return IMG_SUCCESS;
            }

            psCurDecPict = LST_next(psCurDecPict);
        }
    }

    return IMG_ERROR_VALUE_OUT_OF_RANGE;
}
#endif /* VDEC_USE_PVDEC */


/*!
******************************************************************************

 @Function              HWCTRL_RemoveFromPicList

******************************************************************************/
IMG_RESULT
HWCTRL_RemoveFromPicList(
    IMG_HANDLE          hHwCtx,
    DECODER_sDecPict  * psDecPict
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;

    if (psHwCtx)
    {
        DECODER_sDecPict *  psCurDecPict;

        // Ensure that this picture is in the list.
        psCurDecPict = LST_first(&psHwCtx->sPendPictList);
        while (psCurDecPict)
        {
            if (psCurDecPict == psDecPict)
            {
                LST_remove(&psHwCtx->sPendPictList, psDecPict);

                // Indicate that a decode slot is now free.
                psHwCtx->ui32NumFreeSlots[psDecPict->ui8Pipe - 1]++;

                break;
            }

            psCurDecPict = LST_next(psCurDecPict);
        }
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              HWCTRL_Configure

******************************************************************************/
IMG_RESULT
HWCTRL_Configure(
    IMG_HANDLE                  hHwCtx,
    const MSVDXIO_sFw         * psFw,
    const VXDIO_sDdBufInfo      aui32RendecBufinfo[],
    const VXDIO_sDdBufInfo    * psDevPtdBufInfo,
    const VXDIO_sPtdInfo      * psPtdInfo
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;
    IMG_UINT32  ui32Result = IMG_SUCCESS;

#ifdef VDEC_MSVDX_HARDWARE
    if (psHwCtx->sDevConfig.eDecodeLevel > VDECDD_DECODELEVEL_DECODER)
    {
        IMG_ASSERT(psHwCtx->sVxdFuncs.pfnPrepareFirmware != IMG_NULL);
        if (psHwCtx->sVxdFuncs.pfnPrepareFirmware)
        {
            ui32Result = psHwCtx->sVxdFuncs.pfnPrepareFirmware(psHwCtx->hVxd, psFw, psPtdInfo);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                goto error;
            }
        }

        psHwCtx->aui32RendecBufInfo[0] = aui32RendecBufinfo[0];
        psHwCtx->aui32RendecBufInfo[1] = aui32RendecBufinfo[1];
        psHwCtx->sDevPtdBufInfo = *psDevPtdBufInfo;
        psHwCtx->sPsrModInfo = psFw->sPsrModInfo;
    }

error:
#endif
    return ui32Result;
}


/*!
******************************************************************************

 @Function              HWCTRL_Initialise

******************************************************************************/
IMG_RESULT
HWCTRL_Initialise(
    IMG_VOID                   * pvDecCore,
    IMG_VOID                   * pvCompInitUserData,
    IMG_UINT32                   ui32CoreNum,
    const VDECDD_sDdDevConfig  * psDdDevConfig,
    VXD_sCoreProps             * psCoreProps,
    HWCTRL_sRendec             * psRendec,
    IMG_HANDLE                 * phHwCtx
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) *phHwCtx;
    IMG_RESULT ui32Result;

    if (psHwCtx == IMG_NULL)
    {
        VDEC_MALLOC(psHwCtx);
        IMG_ASSERT(psHwCtx);
        if(psHwCtx == IMG_NULL)
        {
            REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                   "Failed to allocate memory for HWCTRL context");
            return IMG_ERROR_OUT_OF_MEMORY;
        }
        VDEC_BZERO(psHwCtx);
        *phHwCtx = psHwCtx;
    }

    if (!psHwCtx->bInitialised)
    {
        IMG_UINT32  ui32Msg;
        IMG_UINT32  ui32I;

        psHwCtx->sIntStatus.psMsgQueue = &psHwCtx->sMsgQueue;

#ifdef VDEC_USE_PVDEC
        ui32Result = PVDEC_Create(psDdDevConfig,
                                  ui32CoreNum,
                                  psCoreProps,
                                  psRendec,
                                  &psHwCtx->hVxd,
                                  &psHwCtx->sVxdFuncs);
#else /* ndef VDEC_USE_PVDEC */
        ui32Result = MSVDX_Create(psDdDevConfig,
                                  ui32CoreNum,
                                  psCoreProps,
                                  psRendec,
                                  &psHwCtx->hVxd,
                                  &psHwCtx->sVxdFuncs);
#endif /* ndef VDEC_USE_PVDEC */

        if (ui32Result != IMG_SUCCESS)
        {
            REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                   "Failed to create decoder (%d)", ui32Result);
            goto error;
        }

        IMG_ASSERT(psHwCtx->hVxd);

        /* Initialise message info...*/
        LST_init(&psHwCtx->sMsgQueue.sFreeMsgList);
        LST_init(&psHwCtx->sMsgQueue.sNewMsgList);
        for (ui32Msg = 0; ui32Msg < MSVDX_MAX_LISR_HISR_MSG; ui32Msg++)
        {
            LST_add(&psHwCtx->sMsgQueue.sFreeMsgList, &psHwCtx->asHISRMsg[ui32Msg]);
        }

#ifdef HWCTRL_REPLACEMENT_HW_THREAD
        /* Start HW task...*/
        VDEC_MALLOC(psHwCtx->psTaskInfo);
        IMG_ASSERT(psHwCtx->psTaskInfo != IMG_NULL);
        VDEC_BZERO(psHwCtx->psTaskInfo);
        LST_init(&psHwCtx->psTaskInfo->sMsgList);

        DQ_init(&psHwCtx->psTaskInfo->hibernateQ);

        SYSOSKM_CreateMutex(&psHwCtx->psTaskInfo->hMsgListMutex);
        SYSOSKM_CreateEventObject(&psHwCtx->psTaskInfo->hNewMsgSent);

        SYSOSKM_CreateEventObject(&hActivatedEvent);
        SYSOSKM_CreateEventObject(&hDeactivatedEvent);

        SYSOSKM_CreateTimer(hwctrl_Task, psHwCtx->psTaskInfo, 0, &psHwCtx->psTaskInfo->hTask);

        SYSOSKM_WaitEventObject(hActivatedEvent);
#endif /* #ifdef HWCTRL_REPLACEMENT_HW_THREAD */

        LST_init(&psHwCtx->sPendPictList);

        psHwCtx->sDevConfig         = *psDdDevConfig;
        for(ui32I = 0; ui32I < psCoreProps->ui32NumPixelPipes; ui32I++)
        {
            psHwCtx->ui32NumFreeSlots[ui32I]   = psDdDevConfig->ui32NumSlotsPerPipe;
        }

        psHwCtx->ui32CoreNum        = ui32CoreNum;
        psHwCtx->ui32NumPipes       = psCoreProps->ui32NumPixelPipes;
        psHwCtx->pvCompInitUserData = pvCompInitUserData;
        psHwCtx->pvDecCore          = pvDecCore;
        psHwCtx->bInitialised       = IMG_TRUE;
        psHwCtx->hTimerHandle       = IMG_NULL;
    }

    return IMG_SUCCESS;

error:
    if (psHwCtx->bInitialised)
    {
        if (IMG_SUCCESS != HWCTRL_Deinitialise(*phHwCtx))
        {
            REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                   "HWCTRL_Deinitialise() failed to tidy-up after error");
        }
    }
    else
    {
        IMG_FREE(*phHwCtx);
    }

    return ui32Result;
}


/*!
******************************************************************************

 @Function              HWCTRL_Deinitialise

******************************************************************************/
IMG_RESULT
HWCTRL_Deinitialise(
    IMG_HANDLE  hHwCtx
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;
    IMG_UINT32      ui32Result;

    if (psHwCtx->bInitialised)
    {
#ifdef FW_PRINT
        psHwCtx->bPrintTaskRequestedActive = IMG_FALSE;
        if(psHwCtx->hFWPrintTimerHandle)
        {
            SYSOSKM_DestroyTimer( psHwCtx->hFWPrintTimerHandle );
            psHwCtx->hFWPrintTimerHandle = IMG_NULL;
        }
#endif //FW_PRINT
        if(psHwCtx->hTimerHandle)
        {
            SYSOSKM_DestroyTimer( psHwCtx->hTimerHandle );
            psHwCtx->hTimerHandle = IMG_NULL;
        }

        IMG_ASSERT(psHwCtx->sVxdFuncs.pfnDestroy != IMG_NULL);
        if (psHwCtx->sVxdFuncs.pfnDestroy)
        {
            ui32Result = psHwCtx->sVxdFuncs.pfnDestroy(psHwCtx->hVxd);
            IMG_ASSERT(ui32Result == IMG_SUCCESS);
            if (ui32Result != IMG_SUCCESS)
            {
                return ui32Result;
            }
        }

#ifdef HWCTRL_REPLACEMENT_HW_THREAD
        /* Stop the task...*/
        psHwCtx->psTaskInfo->bExit = IMG_TRUE;
        SYSOSKM_SignalEventObject(psHwCtx->psTaskInfo->hNewMsgSent);

        SYSOSKM_WaitEventObject(hDeactivatedEvent);

        SYSOSKM_DestroyTimer(psHwCtx->psTaskInfo->hTask);

        SYSOSKM_DestroyEventObject(hActivatedEvent);
        SYSOSKM_DestroyEventObject(hDeactivatedEvent);

        SYSOSKM_DestroyEventObject(psHwCtx->psTaskInfo->hNewMsgSent);
        SYSOSKM_DestroyMutex(psHwCtx->psTaskInfo->hMsgListMutex);

        if (psHwCtx->psTaskInfo)
        {
            IMG_FREE(psHwCtx->psTaskInfo);
            psHwCtx->psTaskInfo = IMG_NULL;
        }
#endif

        IMG_FREE(psHwCtx);
        psHwCtx = IMG_NULL;
    }

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              HWCTRL_PrintMSVDXProps

******************************************************************************/
IMG_VOID
HWCTRL_PrintMSVDXProps(
    VXD_sCoreProps    * psCoreProps,
    IMG_UINT32          ui32CoreNum
)
{
    IMG_UINT8    ui8PipeMinus1;
#ifdef __RELEASE_RELEASE__
    REPORT(REPORT_MODULE_HWCTRL,
           REPORT_INFO,
           "[%s:%u, %s] "
           "clock{auto:%s, ext:%s}, "
           "Stride.{Fixed64B:%s, Ext:%s}, "
           "MMU:%s, "
           "Samples{ChromaUp:%s}, "
           "Error{Handle:%s, Conceal:%s, Impr.:%s}, "
           "MemLat:%u, CmdBuf:%ubytes, NewCacheSet:%s, AuxLine:%s, Lossless:%s, NewTestReg:%s",
           "Core Configuration",
           ui32CoreNum,
           psCoreProps->acVersion,
           (psCoreProps->bAutoClockGatingSupport) ? "y" : "n",
           (psCoreProps->bExtClockGating) ? "y" : "n",
           (psCoreProps->b64ByteFixedStrides) ? "y" : "n",
           (psCoreProps->bExtendedStrides) ? "y" : "n",
           acMmuTypeNames[psCoreProps->eMmuType],
           (psCoreProps->bChromaUpsample) ? "y" : "n",
           (psCoreProps->bErrorHandling) ? "y" : "n",
           (psCoreProps->bErrorConcealment) ? "y" : "n",
           (psCoreProps->bImprovedErrorConcealment) ? "y" : "n",
           psCoreProps->ui32Latency,
           psCoreProps->ui32CmdBufferSize,
           (psCoreProps->bNewCacheSettings) ? "y" : "n",
           (psCoreProps->bAuxLineBufSupported) ? "y" : "n",
           (psCoreProps->bLossless) ? "y" : "n",
           (psCoreProps->bNewTestRegSpace) ? "y" : "n");

    for(ui8PipeMinus1 = 0; ui8PipeMinus1 < psCoreProps->ui32NumPixelPipes; ui8PipeMinus1++)
    {
        REPORT(REPORT_MODULE_HWCTRL,
               REPORT_INFO,
               "Std_pipe_%d{avs:%s, h264:%s, jpeg:%s, mpeg2:%s, mpeg4:%s, real:%s, vc1:%s, vp6:%s, vp8:%s, hevc:%s}, "
               "SR_pipe_%d{streams:%u, DMABurst:%u}, "
               "Rot_pipe_%d:%s, "
               "Scale_pipe_%d{%s, %u-bit, 4k coeff:%s, 8k coeff:%s, OOLD:%s}",
               ui8PipeMinus1,
               (psCoreProps->abAvs[ui8PipeMinus1])   ? "y" : "n",
               (psCoreProps->abH264[ui8PipeMinus1])  ? "y" : "n",
               (psCoreProps->abJpeg[ui8PipeMinus1])  ? "y" : "n",
               (psCoreProps->abMpeg2[ui8PipeMinus1]) ? "y" : "n",
               (psCoreProps->abMpeg4[ui8PipeMinus1]) ? "y" : "n",
               (psCoreProps->abReal[ui8PipeMinus1])  ? "y" : "n",
               (psCoreProps->abVc1[ui8PipeMinus1])   ? "y" : "n",
               (psCoreProps->abVp6[ui8PipeMinus1])   ? "y" : "n",
               (psCoreProps->abVp8[ui8PipeMinus1])   ? "y" : "n",
               (psCoreProps->abHEVC[ui8PipeMinus1])  ? "y" : "n",
               ui8PipeMinus1,
               psCoreProps->aui32NumStreams[ui8PipeMinus1],
               psCoreProps->ui32SrDmaBurstSize,
               ui8PipeMinus1,
               (psCoreProps->abRotationSupport[ui8PipeMinus1]) ? "y" : "n",
               ui8PipeMinus1,
               (psCoreProps->abScalingSupport[ui8PipeMinus1]) ? "y" : "n",
                psCoreProps->ui32ScalingPrecision,
               (psCoreProps->b4kScalingCoeffs) ? "y" : "n",
               (psCoreProps->b8kScalingCoeffs) ? "y" : "n",
               (psCoreProps->bScalingWithOold) ? "y" : "n");
    }
#else
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "======================================================");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "Core (%d) Configuration [%s]", ui32CoreNum, psCoreProps->acVersion);


    for(ui8PipeMinus1 = 0; ui8PipeMinus1 < psCoreProps->ui32NumPixelPipes; ui8PipeMinus1++)
    {
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "----------------------");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "Pipe (%d) ", ui8PipeMinus1);
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "----------------------");
        // Video standards.
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "Video Standards >>>>>>>>>>>>>");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    AVS:                               %s", (psCoreProps->abAvs[ui8PipeMinus1])   ? "yes" : "no");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    H.264:                             %s", (psCoreProps->abH264[ui8PipeMinus1])  ? "yes" : "no");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    HEVC:                              %s", (psCoreProps->abHEVC[ui8PipeMinus1])  ? "yes" : "no");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    JPEG:                              %s", (psCoreProps->abJpeg[ui8PipeMinus1])  ? "yes" : "no");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    MPEG2:                             %s", (psCoreProps->abMpeg2[ui8PipeMinus1]) ? "yes" : "no");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    MPEG4:                             %s", (psCoreProps->abMpeg4[ui8PipeMinus1]) ? "yes" : "no");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    REAL:                              %s", (psCoreProps->abReal[ui8PipeMinus1])  ? "yes" : "no");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    VC-1:                              %s", (psCoreProps->abVc1[ui8PipeMinus1])   ? "yes" : "no");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    VP6:                               %s", (psCoreProps->abVp6[ui8PipeMinus1])   ? "yes" : "no");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    VP8:                               %s", (psCoreProps->abVp8[ui8PipeMinus1])   ? "yes" : "no");

        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "Transformations >>>>>>>>>>>>>");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Rotation:                          %s", (psCoreProps->abRotationSupport[ui8PipeMinus1]) ? "yes" : "no");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Scaling:                           %s", (psCoreProps->abScalingSupport[ui8PipeMinus1]) ? "yes" : "no");
        if (psCoreProps->abScalingSupport[ui8PipeMinus1])
        {
            DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Scaling precision:                 %d", psCoreProps->ui32ScalingPrecision);
            DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    4k Scaling coeffs:                 %s", (psCoreProps->b4kScalingCoeffs) ? "yes" : "no");
            DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    8k Scaling coeffs:                 %s", (psCoreProps->b8kScalingCoeffs) ? "yes" : "no");
            DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Scaling (+OOLD):                   %s", (psCoreProps->bScalingWithOold) ? "yes" : "no");
        }

        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "Shift register >>>>>>>>>>>>>>");
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Quantity:                          %d", psCoreProps->aui32NumStreams[ui8PipeMinus1]);
        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    DMA burst size:                    %d", psCoreProps->ui32SrDmaBurstSize);
    }
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "----------------------");

    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "Clocks >>>>>>>>>>>>>>>>>>>>>>");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Auto clock-gating:                 %s", (psCoreProps->bAutoClockGatingSupport) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Extended clock-gating:             %s", (psCoreProps->bExtClockGating) ? "yes" : "no");

    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "Stride Support >>>>>>>>>>");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Fixed Strides (64 byte multiples): %s", (psCoreProps->b64ByteFixedStrides) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Extended Strides (64 byte):        %s", (psCoreProps->bExtendedStrides) ? "yes" : "no");

    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "MMU >>>>>>>>>>>>>>>>>>>>>>>>>");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Type:                              %s", acMmuTypeNames[psCoreProps->eMmuType]);

    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "Samples >>>>>>>>>>>>>>>>>>>>>");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Chroma upsampling:                 %s",    (psCoreProps->bChromaUpsample) ? "yes" : "no");

    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "Error >>>>>>>>>>>>>>>>>>>>>");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Error Handling:                    %s",    (psCoreProps->bErrorHandling) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Error Concealment:                 %s",    (psCoreProps->bErrorConcealment) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Improved Concealment:              %s",    (psCoreProps->bImprovedErrorConcealment) ? "yes" : "no");

    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "Other >>>>>>>>>>>>>>>>>>>>>>>");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Memory Latency:                    %d", psCoreProps->ui32Latency);
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Command buffer size:               %d", psCoreProps->ui32CmdBufferSize);
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    New cache settings:                %s", (psCoreProps->bNewCacheSettings) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Aux line buffer:                   %s", (psCoreProps->bAuxLineBufSupported) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    Lossless:                          %s", (psCoreProps->bLossless) ? "yes" : "no");
    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "    New test register space:           %s", (psCoreProps->bNewTestRegSpace) ? "yes" : "no");

    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "======================================================");
#endif
}

/*!
******************************************************************************

 @Function              HWCTRL_GetRegsOffsets

******************************************************************************/
IMG_RESULT
HWCTRL_GetRegsOffsets(
    IMG_HANDLE              hHwCtx,
    DECODER_sRegsOffsets  * psRegsOffsets
)
{
    HWCTRL_sHwCtx * psHwCtx = (HWCTRL_sHwCtx *) hHwCtx;
    IMG_UINT32      ui32Result = IMG_SUCCESS;

    IMG_ASSERT(psHwCtx->sVxdFuncs.pfnGetRegsOffsets != IMG_NULL);
    if (psHwCtx->sVxdFuncs.pfnGetRegsOffsets)
    {
        ui32Result = psHwCtx->sVxdFuncs.pfnGetRegsOffsets(psHwCtx->hVxd, psRegsOffsets);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            return ui32Result;
        }
    }

    return ui32Result;
}
