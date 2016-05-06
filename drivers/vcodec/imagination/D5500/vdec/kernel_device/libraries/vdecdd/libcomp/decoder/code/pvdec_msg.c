/*!
 *****************************************************************************
 *
 * @File       pvdec_msg.c
 * @Title      Messages to PVDEC firmware.
 * @Description    This file contains functions for creating messages to PVDEC firmware.
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

#include "report_api.h"
#include "rman_api.h"
#include "sysos_api_km.h"
#include "dbgopt_api_km.h"
#include "vxd_ext.h"
#include "hwctrl_api.h"
#include "pvdec_msg.h"
#include "pvdec_int.h"
#include "pvdec_ctx.h"
#include "interface/deva_fw_msg.h"
#include "hwdefs/pvdec_core_regs.h"

#ifdef USE_REAL_FW
    #include "vdecfw_bin.h"
#endif

#ifndef SYSBRG_BRIDGING
    #include "talmmu_api.h"
#else
    //#include "msvdx_ext.h"
    #include "sysmem_utils.h"
#endif

/* Included from PVDEC firmware. */
#include "source/core/vdec_fw_interface.h"

/* Panic reason identifier. */
typedef enum
{
    PANIC_REASON_OTHER = 0,
    PANIC_REASON_WDT,
    PANIC_REASON_READ_TIMEOUT,
    PANIC_REASON_CMD_TIMEOUT,
    PANIC_REASON_MMU_FAULT,

    PANIC_REASON_MAX

} pvdec_ePanicReason;

/* Panic reason strings.
 * NOTE: Should match the pvdec_ePanicReason ids. */
static IMG_CHAR *  apszPanicReason[PANIC_REASON_MAX] =
{
    "Other, ",
    "Watch Dog Timeout, ",
    "Command Timeout, ",
    "Read Timeout, ",
    "MMU Page Fault, "
};

/* Maximum length of the panic reason string. */
#define PANIC_REASON_LEN  (PANIC_REASON_MAX * 24)

/*!
******************************************************************************

 @Function              PVDEC_GetInitMessage

******************************************************************************/
IMG_RESULT PVDEC_GetInitMessage(
    const IMG_HANDLE               hVxd,
    IMG_UINT8                   ** ppui8Msg,
    HWCTRL_sMsgStatus            * psHostMsgStatus,
    VDECDD_sDdDevConfig          * psDevConfig,
    VXDIO_sDdBufInfo             * psRendecBufInfo,
    const VDECFW_sCoreInitData   * psCoreInitData,
    const VXDIO_sDdBufInfo       * psDevPtdBufInfo
)
{
    /* Create a control picture message here from the config. */
    IMG_BOOL bHWCRCGen = IMG_FALSE;
    IMG_UINT8  * pui8Msg = IMG_MALLOC(FW_DEVA_INIT_SIZE);
    if (pui8Msg == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "Failed to allocate message buffer");
        return IMG_ERROR_MALLOC_FAILED;
    }
    IMG_MEMSET(pui8Msg, 0, FW_DEVA_INIT_SIZE);

    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_GENMSG_MSG_SIZE, FW_DEVA_INIT_SIZE/sizeof(IMG_UINT32));
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_GENMSG_MSG_TYPE, FW_DEVA_INIT);
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_GENMSG_BATCH_START, 0);


    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_INIT_HEVC_MIN_H_FOR_DUAL_PIPE, 0); /* no minimum height restriction */
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_INIT_HEVC_MAX_H_FOR_PIPE_WAIT, ~0); /* never wait */

    /* DEVA PVDEC FW uses only first (in message) rendec buffer currently and splits it itself. */
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_INIT_RENDEC_ADDR0, psRendecBufInfo[0].ui32DevVirt);
    /* DEVA PVDEC FW expects rendec buffer size to be given in pages */
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_INIT_RENDEC_SIZE0, psRendecBufInfo[0].ui32BufSize/(DEV_MMU_PAGE_SIZE));//psCoreInitData->sRendecConfig.ui32RegVecRendecBufferSize/(SYS_MMU_PAGE_SIZE));

    /* Check if CRC generation is required. */
    {
        DBGOPT_sValue  sVal;
        if (DBGOPTKM_GetSize("HardwareCRCGen", DBGOPT_TYPE_BOOL) &&
            DBGOPTKM_Get("HardwareCRCGen", IMG_NULL, &sVal))
        {
            bHWCRCGen = sVal.bVal;
        }
    }

    /* Request signatures (CRCs) for picture verification if required. */
    if(bHWCRCGen)
    {
        MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_INIT_HW_SIG_SELECT, (PVDEC_SIGNATURE_GROUP_20 | PVDEC_SIGNATURE_GROUP_24));
    }

    DEBUG_REPORT(REPORT_MODULE_VXDIO, "[MID=0x%02X] [CONTROL] [0x%02X]",
        psHostMsgStatus->aui8ControlFenceID[VDECFW_MSGID_FIRMWARE_INIT-VDECFW_MSGID_BASE_PADDING], VDECFW_MSGID_FIRMWARE_INIT);

    *ppui8Msg = pui8Msg;

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              PVDEC_GetBatchMessage

******************************************************************************/
IMG_RESULT PVDEC_GetBatchMessage(
    const IMG_HANDLE              hVxd,
    IMG_UINT8                  ** ppui8Msg,
    HWCTRL_sMsgStatus           * psHostMsgStatus,
    const VDECDD_sDdDevConfig   * psDevConfig,
    const IMG_UINT8               ui8BatchMessageID,
    LST_T                       * psDecPictSegList,
    HWCTRL_sBatchMsgData        * psBatchMsgData
)
{
    PVDEC_sContext  * psPvdecContext = (PVDEC_sContext *)hVxd;
    IMG_UINT16        ui16VdecFlags = 0;
    IMG_UINT16        ui16Flags = 0;

    VXDIO_sDdBufInfo  * psStrPtdBufInfo = psBatchMsgData->psStrPtdBufInfo;
    VXDIO_sDdBufInfo  * psBatchMsgBufInfo = psBatchMsgData->psBatchMsgBufInfo;

    IMG_UINT8            * pui8Msg = IMG_MALLOC(FW_DEVA_DECODE_SIZE);
    if (pui8Msg == IMG_NULL)
    {
        REPORT(REPORT_MODULE_VXDIO, REPORT_ERR,
               "Failed to allocate message buffer");
        return IMG_ERROR_MALLOC_FAILED;
    }
    IMG_MEMSET(pui8Msg, 0, FW_DEVA_DECODE_SIZE);
    if (psBatchMsgData->bFirstPicOfSequence)
    {
        ui16VdecFlags |= FW_VDEC_NEW_SEQUENCE;
    }
    if (psBatchMsgData->bSizeDelimitedMode)
    {
        ui16VdecFlags |= FW_VDEC_NAL_SIZE_DELIM;
    }
    ui16Flags |= FW_DEVA_RENDER_HOST_INT | FW_DEVA_IMMEDIATE_ABORT_FAULTED;

    /* Message type and stream ID */
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_GENMSG_MSG_TYPE, FW_DEVA_PARSE);

    /* Control allocation size and address */
    IMG_ASSERT(CTRL_ALLOC_MAX_SEGMENT_SIZE > psBatchMsgData->ui32CtrlAllocBytes);
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_DECODE_CTRL_ALLOC_ADDR, (IMG_UINT32)psBatchMsgBufInfo->ui32DevVirt);
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_DECODE_BUFFER_SIZE, psBatchMsgData->ui32CtrlAllocBytes/sizeof(IMG_UINT32));

    /* Operating mode and decode flags */
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_DECODE_OPERATING_MODE, psBatchMsgData->ui32OperatingMode);
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_DECODE_FLAGS, ui16Flags);
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_DECODE_VDEC_FLAGS, ui16VdecFlags);
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_DECODE_PIPE, psBatchMsgData->ui8Pipe);

    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_DECODE_STREAMID, GET_STREAM_ID(psBatchMsgData->ui32TransactionId));

    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_DECODE_EXT_STATE_BUFFER, (IMG_UINT32)psBatchMsgData->psPvdecFwCtx->ui32DevVirt);
    DEBUG_REPORT(REPORT_MODULE_VXDIO, "[TID=0x%08X] [PARSE] [0x%02X]", psBatchMsgData->ui32TransactionId, FW_DEVA_PARSE);
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_DECODE_MSG_ID, ++psPvdecContext->ui16CurrentMsgId) ;
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_DECODE_TRANS_ID, psBatchMsgData->ui32TransactionId) ;

    /* PTD. Host pointer has to be updated because the value was temporary stored in the device memory*/
    UPDATE_HOST(psStrPtdBufInfo, IMG_TRUE);
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_DECODE_MMUPTD, *((IMG_UINT32 *)psStrPtdBufInfo->pvCpuVirt));

    /* Size of message */
    MEMIO_WRITE_FIELD(pui8Msg, FW_DEVA_GENMSG_MSG_SIZE, FW_DEVA_DECODE_SIZE/sizeof(IMG_UINT32));

    *ppui8Msg = pui8Msg;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              PVDEC_ReturnMsg

******************************************************************************/
IMG_VOID PVDEC_ReturnMsg(
    const IMG_HANDLE    hVxd,
    IMG_UINT8         * pui8Msg
)
{
    IMG_FREE(pui8Msg);
}


/*!
******************************************************************************

 @Function              PVDEC_ProcessMessage

******************************************************************************/
IMG_RESULT PVDEC_ProcessMessage(
    const IMG_HANDLE     hVxd,
    IMG_UINT32         * pui32Msg,
    HWCTRL_sMsgStatus  * psHostMsgStatus,
    LST_T              * psPendPictList,
#ifndef IMG_KERNEL_MODULE
    IMG_BOOL             bPdumpAndRes,
#endif
    IMG_BOOL           * pbDecodedMsg
)
{
    PVDEC_sContext    * psPvdecCtx = (PVDEC_sContext *)hVxd;
    IMG_UINT8           ui8MsgType;
    IMG_UINT8           ui8MsgGroup;
    DECODER_sDecPict  * psDecPict;
    IMG_UINT32          ui32TransId = 0;
    VDEC_sPictHwCrc *   psPictHwCrc = IMG_NULL;

    #define MSG_GROUP_MASK  0xf0
    #define MSG_PIPE_MASK   0x0f

    ui32TransId = MEMIO_READ_FIELD(pui32Msg, FW_DEVA_GENMSG_TRANS_ID);
    ui8MsgType  = MEMIO_READ_FIELD(pui32Msg, FW_DEVA_GENMSG_MSG_TYPE);
    ui8MsgGroup = ui8MsgType & MSG_GROUP_MASK;

    switch (ui8MsgGroup)
    {
        case MSG_TYPE_START_PSR_MTXHOST_MSG:
        {
            switch (ui8MsgType)
            {
                case FW_DEVA_COMPLETED:
                {
                    VDEC_sPictDecoded *  psPictDecoded = IMG_NULL;
                    IMG_UINT16           ui16ErrorFlags = MEMIO_READ_FIELD(pui32Msg, FW_DEVA_COMPLETED_ERROR_FLAGS);

                    psDecPict = LST_first(psPendPictList);
                    while (psDecPict)
                    {
                        if (psDecPict->ui32TransactionId == ui32TransId)
                        {
                            break;
                        }
                        psDecPict = LST_next(psDecPict);
                    }

                    // We must have a picture in the list that matches the transaction id
                    if(psDecPict == IMG_NULL)
                    {
                        IMG_ASSERT(IMG_FALSE);

                        REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                            "Firmware decoded message received with no pending picture");
                        return IMG_ERROR_FATAL;
                    }

                    if(psDecPict->psFirstFieldFwMsg->sPictDecoded.bFirstFieldReceived)
                    {
                        psPictDecoded = &psDecPict->psSecondFieldFwMsg->sPictDecoded;
                    }
                    else
                    {
                        psPictDecoded = &psDecPict->psFirstFieldFwMsg->sPictDecoded;
                        psDecPict->psFirstFieldFwMsg->sPictDecoded.bFirstFieldReceived = IMG_TRUE;
                    }

                    psPictDecoded->ui32FEError = (IMG_UINT32)ui16ErrorFlags;

                    psDecPict->bDecoded = IMG_TRUE;

                    *pbDecodedMsg = IMG_TRUE;

                    //psDecPict->psFwMsg->ui32FEError = MEMIO_READ_FIELD(pui32Msg, V2_DECODEDMSG_FE_ERR);
                    //psDecPict->psFwMsg->ui32NoBEDWT = MEMIO_READ_FIELD(pui32Msg, V2_DECODEDMSG_BEWDT);

                    /*if(FLAG_IS_SET(MEMIO_READ_FIELD(pui32Msg,V2_DECODEDMSG_FLAGS),VDECFW_MSGFLAG_DECODED_SKIP_PICTURE))
                    {
                        psDecPict->psFwMsg->bSkipPict = IMG_TRUE;
                        psDecPict->psFwMsg->ui32TransIdToFillSkipPict = MEMIO_READ_FIELD(pui32Msg, V2_DECODEDMSG_FILLPICID);
                    }*/

                    //psHostMsgStatus->aui8CompletionFenceID[VDECFW_MSGID_PIC_DECODED-VDECFW_MSGID_BE_PADDING] = MEMIO_READ_FIELD(pui32Msg, V2_DECODEDMSG_FENCE_ID);

                    DEBUG_REPORT(REPORT_MODULE_HWCTRL, "[TID=0x%08X] [COMPLETION_DECODED]", ui32TransId);

            #ifndef IMG_KERNEL_MODULE
                    if(bPdumpAndRes)
                    {
                        if(psDecPict->psAltPict != IMG_NULL)
                        {
                            UPDATE_HOST((&psDecPict->psAltPict->psPictBuf->sDdBufInfo), IMG_TRUE);
                        }
                        else
                        {
                            UPDATE_HOST((&psDecPict->psReconPict->psPictBuf->sDdBufInfo), IMG_TRUE);
                        }
                    }
            #endif
                    break;
                }

                case FW_DEVA_PANIC:
                {
                    IMG_UINT32  ui32PanicInfo =  MEMIO_READ_FIELD(pui32Msg, FW_DEVA_PANIC_ERROR_INT);
                    IMG_CHAR    szPanicReason[PANIC_REASON_LEN] = "Reason(s): ";
                    IMG_BOOL    bPanicResonIdentified = IMG_FALSE;

                    *pbDecodedMsg = IMG_FALSE;
                    psPvdecCtx->bFWPanic = IMG_TRUE;

                    /* Create panic reason string. */
                    if (REGIO_READ_FIELD(ui32PanicInfo, PVDEC_CORE, CR_PVDEC_HOST_INTERRUPT_STATUS, CR_HOST_SYS_WDT))
                    {
                        strncat(szPanicReason, apszPanicReason[PANIC_REASON_WDT], PANIC_REASON_LEN - 1);
                        bPanicResonIdentified = IMG_TRUE;
                    }
                    if (REGIO_READ_FIELD(ui32PanicInfo, PVDEC_CORE, CR_PVDEC_HOST_INTERRUPT_STATUS, CR_HOST_READ_TIMEOUT_PROC_IRQ))
                    {
                        strncat(szPanicReason, apszPanicReason[PANIC_REASON_READ_TIMEOUT], PANIC_REASON_LEN - 1);
                        bPanicResonIdentified = IMG_TRUE;
                    }
                    if (REGIO_READ_FIELD(ui32PanicInfo, PVDEC_CORE, CR_PVDEC_HOST_INTERRUPT_STATUS, CR_HOST_COMMAND_TIMEOUT_PROC_IRQ))
                    {
                        strncat(szPanicReason, apszPanicReason[PANIC_REASON_CMD_TIMEOUT], PANIC_REASON_LEN - 1);
                        bPanicResonIdentified = IMG_TRUE;
                    }
                    if (REGIO_READ_FIELD(ui32PanicInfo, PVDEC_CORE, CR_PVDEC_HOST_INTERRUPT_STATUS, CR_HOST_MMU_FAULT_IRQ))
                    {
                        strncat(szPanicReason, apszPanicReason[PANIC_REASON_MMU_FAULT], PANIC_REASON_LEN - 1);
                        bPanicResonIdentified = IMG_TRUE;
                    }
                    if (!bPanicResonIdentified)
                    {
                        strncat(szPanicReason, apszPanicReason[PANIC_REASON_OTHER], PANIC_REASON_LEN - 1);
                    }
                    szPanicReason[IMG_STRLEN(szPanicReason) - 2] = 0;

                    if (0 != ui32TransId)
                    {
                        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "[TID=0x%08X] [!!!FIRMWARE PANIC!!! %s]", ui32TransId, szPanicReason);
                    }
                    else
                    {
                        DEBUG_REPORT(REPORT_MODULE_HWCTRL, "[TID=NULL] [!!!GENERAL FIRMWARE PANIC!!! %s]", szPanicReason);
                    }
                    break;
                }

                default:
                {
                    IMG_ASSERT(IMG_FALSE);
                    break;
                }
            }
            break;
        }

        case FW_DEVA_SIGNATURES_LEGACY:
        case FW_DEVA_SIGNATURES_HEVC:
        {
            IMG_UINT32  * pui32Signatures = pui32Msg + (FW_DEVA_SIGNATURES_SIGNATURES_OFFSET / sizeof(IMG_UINT32));

            psDecPict = LST_first(psPendPictList);
            while (psDecPict)
            {
                if (psDecPict->ui32TransactionId == ui32TransId)
                {
                    break;
                }
                psDecPict = LST_next(psDecPict);
            }

            // We must have a picture in the list that matches the tid
            if(psDecPict == IMG_NULL)
            {
                IMG_ASSERT(IMG_FALSE);

                REPORT(REPORT_MODULE_HWCTRL, REPORT_ERR,
                       "Firmware signatures message received with no pending picture");
                return IMG_ERROR_FATAL;
            }

            if(psDecPict->psFirstFieldFwMsg->sPictHwCrc.bFirstFieldReceived)
            {
                psPictHwCrc = &psDecPict->psSecondFieldFwMsg->sPictHwCrc;
            }
            else
            {
                psPictHwCrc = &psDecPict->psFirstFieldFwMsg->sPictHwCrc;
                psDecPict->psFirstFieldFwMsg->sPictHwCrc.bFirstFieldReceived = IMG_TRUE;
            }

            psPictHwCrc->ui32CrcVdmcPixRecon     = pui32Signatures[0];
            psPictHwCrc->ui32VdebSysMemWriteData = pui32Signatures[1];

            DEBUG_REPORT(REPORT_MODULE_HWCTRL, "[TID=0x%08X] [SIGNATURES]", ui32TransId);

            break;
        }

        default:
        {
            IMG_ASSERT(IMG_FALSE);
            break;
        }
    }

    return IMG_SUCCESS;
}

