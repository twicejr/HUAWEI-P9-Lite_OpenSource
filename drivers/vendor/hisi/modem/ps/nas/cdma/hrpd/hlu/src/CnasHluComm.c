/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHluComm.c
  版 本 号   : 初稿
  作    者   : y00213812
  生成日期   : 2014年12月16日
  最近修改   :
  功能描述   : HLU encode & decode process
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月16日
    作    者   : Y00213812
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "CnasHluCtx.h"
#include "CnasMntn.h"
#include "CnasHluComm.h"
#include "CnasHluSndFsig.h"
#include "CnasHluSndHsm.h"
#include "CnasHluProcNvim.h"

#include "CnasHluSndAs.h"
#include "NasOmInterface.h"

#include "CnasTimerMgmt.h"
#include "Nas_Mem.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HLU_COMM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 Global variable
*****************************************************************************/


/*****************************************************************************
  3 Function Definitions
*****************************************************************************/
/*lint -save -e958*/


VOS_UINT32 CNAS_HLU_DecodeLoc(
    VOS_UINT8                          *pucData
)
{
    CNAS_HLU_LOC_STRU                   stLocCtx;

    NAS_MEM_SET_S(&stLocCtx, sizeof(stLocCtx), 0, sizeof(CNAS_HLU_LOC_STRU));

    if ((CNAS_HLU_CDMA2000_HRPD_LOC_TYPE == *(pucData + 2))
     && (CNAS_HLU_CDMA2000_HRPD_LOC_LEN == *(pucData + 3)))
    {
        stLocCtx.ucTransID          = *(pucData + 1);
        stLocCtx.ucLocType          = CNAS_HLU_CDMA2000_HRPD_LOC_TYPE;
        stLocCtx.ucLocLen           = CNAS_HLU_CDMA2000_HRPD_LOC_LEN;

        /*** C.S0024-A_v3.0_060912.pdf [Section:4.6.4.2.3] ***/
        /* LocationValue : The access network shall set this field to the
           Location of type  specified by LocationType. If LocationType
           is set to 0x01, the access  network shall set this field as
           shown in Table 4.6.4.2-2, where SID, NID, and PACKET_ZONE_ID
           correspond to the current access network.

           Subfields of LocationValue when LocationType = 0x01
           Sub-fields of LocationValue     # of bits
           SID                               15
           Reserved                          1
           NID                               16
           PACKET_ZONE_ID                    8

             --------------- - ---------------- --------
            |      SID      |R|       NID      |  PZID  |
             --------------- - ---------------- --------
                    15       1         16           8
        */
        CNAS_HLU_STORE_SID_NTOH_S(&stLocCtx.stLocVal.usSID, pucData);
        CNAS_HLU_STORE_NID_NTOH_S(&stLocCtx.stLocVal.usNID, pucData);

        /* Ignore the reserve bit in SID. */
        CNAS_HLU_ClearBitInDByte(&stLocCtx.stLocVal.usSID, 16);

        stLocCtx.stLocVal.ucPacketZoneID = *(pucData + 8);
    }
    else if (CNAS_HLU_CDMA2000_HRPD_LOC_TYPE_INV == *(pucData + 2))
    {
        /* No location information contained. HLU must reset the previous
           location information stored.
           HLU must send location complete when AN sends LocAssignment with
           locType = 0.
        */
        stLocCtx.ucTransID               = *(pucData + 1);
        stLocCtx.ucLocType               = CNAS_HLU_CDMA2000_HRPD_LOC_TYPE_INV;
        stLocCtx.ucLocLen                = CNAS_HLU_CDMA2000_HRPD_LOC_LEN_INV;
        stLocCtx.stLocVal.usSID          = 0;
        stLocCtx.stLocVal.usNID          = 0;
        stLocCtx.stLocVal.ucPacketZoneID = 0;
    }
    else
    {
        /* location value is NULL */
        CNAS_INFO_LOG2(UEPS_PID_HLU, "CNAS_HLU_DecodeLoc:Invalid LocationType "
                                        "or LocationLength received in "
                                        "LocationAssignment Msg.",
                                        *(pucData + 2),
                                        *(pucData + 3));
        return VOS_ERR;
    }

    /* Store value in global variable */
    NAS_MEM_CPY_S(&((CNAS_HLU_GetLocCtxAddr())->stLocCtx),
                  sizeof(CNAS_HLU_LOC_STRU),
                  &stLocCtx,
                  sizeof(CNAS_HLU_LOC_STRU));

    return VOS_OK;
}


VOS_UINT32 CNAS_HLU_DecodeBLOB(
    VOS_UINT8                          *pucData
)
{
    CNAS_HLU_BLOB_STRU                  stBLOBCtx;
    VOS_UINT16                          usBlobType;
    VOS_UINT8                           ucBlobLen;

    usBlobType = *((VOS_UINT16 *)(pucData + 2));
    usBlobType = CNAS_HLU_NTOHS(usBlobType);
    ucBlobLen  = *(pucData + 4);

    NAS_MEM_SET_S(&stBLOBCtx, sizeof(stBLOBCtx), 0, sizeof(CNAS_HLU_BLOB_STRU));

    if ((CNAS_HLU_CDMA2000_HRPD_BLOB_TYPE_INV != usBlobType)
     && (CNAS_HLU_CDMA2000_HRPD_BLOB_LEN_INV != ucBlobLen))
    {
        /* StorageBLOB value is NOT NULL */
        stBLOBCtx.ucTransID       = *(pucData + 1);
        stBLOBCtx.usStrgBLOBtype  = usBlobType;
        stBLOBCtx.ucStrgBLOBLen   = ucBlobLen;

        NAS_MEM_CPY_S(stBLOBCtx.aucStorageBLOB, sizeof(stBLOBCtx.aucStorageBLOB), (pucData + 5), stBLOBCtx.ucStrgBLOBLen);

        /* Store value in global variable */
        NAS_MEM_CPY_S(&((CNAS_HLU_GetLocCtxAddr())->stBLOBCtx),
                      sizeof(CNAS_HLU_BLOB_STRU),
                      &stBLOBCtx,
                      sizeof(CNAS_HLU_BLOB_STRU));

    }
    else
    {

        /* StorageBLOB value is NULL */
        stBLOBCtx.ucTransID       = *(pucData + 1);
        stBLOBCtx.usStrgBLOBtype  = usBlobType;
        stBLOBCtx.ucStrgBLOBLen   = 0;

        /* Clear value in global variable */
        NAS_MEM_CPY_S(&((CNAS_HLU_GetLocCtxAddr())->stBLOBCtx),
                      sizeof(CNAS_HLU_BLOB_STRU),
                      &stBLOBCtx,
                      sizeof(CNAS_HLU_BLOB_STRU));


    }

    return VOS_OK;
}


VOS_VOID CNAS_HLU_ProcSnpDataInd(
    SNPITF_MSG_DATA_STRU               *pstMsgData
)
{
    VOS_UINT8                           ucMsgId;
    VOS_UINT32                          ulRetVal;
    VOS_UINT8                           ucBlobLen;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT16                          usMsgByteLen;

    if (pstMsgData->usMsgBitLen % CNAS_HLU_BYTE_LEN == 0)
    {
        usMsgByteLen = pstMsgData->usMsgBitLen / CNAS_HLU_BYTE_LEN;
    }
    else
    {
        usMsgByteLen = pstMsgData->usMsgBitLen / CNAS_HLU_BYTE_LEN + 1;
    }

    pucData = PS_MEM_ALLOC(UEPS_PID_HLU, usMsgByteLen);
    if (VOS_NULL_PTR == pucData)
    {
        CNAS_ERROR_LOG(UEPS_PID_HLU,
                       "CNAS_HLU_ProcSnpDataInd: mem alloc "
                       "mem alloc fail.");
        return;
    }

    NAS_MEM_CPY_S(pucData, usMsgByteLen, pstMsgData->aucMsgData, usMsgByteLen);


    ucMsgId = pstMsgData->aucMsgData[0];

    switch (ucMsgId)
    {
        case CNAS_HLU_HRPD_LOC_REQUEST:
        {
            CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_DOWN,
                                  NAS_OTA_MSG_HLU_LOC_REQUEST,
                                  UEPS_PID_HLU,
                                  (VOS_UINT32)(pstMsgData->usMsgBitLen),
                                  pstMsgData->aucMsgData);

            /* location request */
            /* send a location notification to FSIG */
            CNAS_HLU_SndFsig(CNAS_HLU_HRPD_LOC_NOTIFICATION);

            break;
        }
        case CNAS_HLU_HRPD_LOC_ASSIGNMENT:
        {
            /* location assignment */
            if (pstMsgData->usMsgBitLen >= CNAS_HLU_LOC_ASSIGN_MSG_MIN_BIT_LEN)
            {
                /* 1. Decode the message and store the info */
                /* 2. Send locationComplete message to FSIG */
                ulRetVal = CNAS_HLU_DecodeLoc(pucData);

                CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_DOWN,
                                      NAS_OTA_MSG_HLU_LOC_ASSIGNMENT,
                                      UEPS_PID_HLU,
                                     (VOS_UINT32)pstMsgData->usMsgBitLen,
                                      pstMsgData->aucMsgData);

                if (VOS_OK == ulRetVal)
                {
                    CNAS_HLU_SndFsig(CNAS_HLU_HRPD_LOC_COMPLETE);

                    /* ***  Here, update PZID in APS. *** */
                    CNAS_HLU_UpdateHsmLocValue(CNAS_HLU_GetLocCtxAddr());

                    /* Write assigned StorageBLOB to NV*/
                    CNAS_HLU_WriteLocInfoNvim();
                }
            }
            else
            {
                CNAS_ERROR_LOG(UEPS_PID_HLU,
                               "CNAS_HLU_ProcSnpDataInd: LOCAssignment message "
                               "received with invalid msg bit length.");
            }

            break;
        }
        case CNAS_HLU_HRPD_BLOB_REQUEST:
        {
            CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_DOWN,
                                  NAS_OTA_MSG_HLU_BLOB_REQUEST,
                                  UEPS_PID_HLU,
                                 (VOS_UINT32)pstMsgData->usMsgBitLen,
                                  pstMsgData->aucMsgData);

            /* StorageBLOB request */
            /* send StorageBLOB notification to FSIG, invoke CNAS_HLU_SndFsig */
            CNAS_HLU_SndFsig(CNAS_HLU_HRPD_BLOB_NOTIFICATION);

            break;
        }
        case CNAS_HLU_HRPD_BLOB_ASSIGNMENT:
        {
            ucBlobLen = *(pucData + 4);

            if ((CNAS_HLU_BLOB_ASSG_MSG_BIT_LEN(ucBlobLen)) == pstMsgData->usMsgBitLen)
            {
                /* StorageBLOB assignment */
                /* decode the message and store the info */
                ulRetVal = CNAS_HLU_DecodeBLOB(pucData);

                CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_DOWN,
                                      NAS_OTA_MSG_HLU_BLOB_ASSIGNMENT,
                                      UEPS_PID_HSM,
                                     (VOS_UINT32)pstMsgData->usMsgBitLen,
                                      pstMsgData->aucMsgData);


                if (VOS_OK == ulRetVal)
                {
                    /* send storageBlobComplete message to FSIG */
                    CNAS_HLU_SndFsig(CNAS_HLU_HRPD_BLOB_COMPLETE);

                    /* Write assigned StorageBLOB to NV*/
                    CNAS_HLU_WriteStrgBlobNvim();
                }
            }
            else
            {
                CNAS_ERROR_LOG(UEPS_PID_HLU,
                               "CNAS_HLU_ProcSnpDataInd: BLOBAssignment message "
                               "received with invalid msg bit length.");
            }
            break;
        }
        default:
        {
            CNAS_WARNING_LOG(UEPS_PID_HLU, "CNAS_HLU_ProcSnpDataInd: Incorrect "
                                            "HRPD_MSG_TYPE received.");
            break;
        }
    }

    PS_MEM_FREE(UEPS_PID_HLU, pucData);

    return;
}



VOS_VOID CNAS_HLU_SndFsig(
    VOS_UINT8                           ucMsgId
)
{
    CNAS_HLU_MSG_TX_OPTION_INFO         stMsgTxInfo;

    /* Fill the value in transmission info. */
    stMsgTxInfo.enChannelType  = CTTF_HRPD_CHANNEL_AC_OR_RTC;
    stMsgTxInfo.enDeliveryType = CTTF_HRPD_DELIVERY_TYPE_BEST_EFFORT;
    stMsgTxInfo.enAddressType  = CTTF_HRPD_ADDRESS_UNICAST;
    stMsgTxInfo.ucPriority     = CNAS_HLU_LOC_MSG_PRIORITY;

    switch(ucMsgId)
    {
        case CNAS_HLU_HRPD_LOC_NOTIFICATION:
        {
            /* 向接入层发送保护请求 */
            CNAS_HLU_SndCasBeginSessionNotify(CNAS_CAS_HRPD_SESSION_TYPE_LU);

            /* send a location notification to AN */
            CNAS_HLU_SendLocNotification(&stMsgTxInfo, VOS_FALSE, VOS_NULL_PTR);

            CNAS_HLU_StartTimer(TI_CNAS_HLU_WAIT_SIG_DATA_CNF, TI_CNAS_HLU_WAIT_SIG_DATA_CNF_LEN);


            break;
        }
        case CNAS_HLU_HRPD_LOC_COMPLETE:
        {

            /* 向接入层发送保护请求 */
            CNAS_HLU_SndCasBeginSessionNotify(CNAS_CAS_HRPD_SESSION_TYPE_LU);

            /* send a location complete to AN */
            CNAS_HLU_SendLocComplete(&stMsgTxInfo);

            CNAS_HLU_StartTimer(TI_CNAS_HLU_WAIT_SIG_DATA_CNF, TI_CNAS_HLU_WAIT_SIG_DATA_CNF_LEN);

            break;
        }
        case CNAS_HLU_HRPD_BLOB_NOTIFICATION:
        {
            /* 向接入层发送保护请求 */
            CNAS_HLU_SndCasBeginSessionNotify(CNAS_CAS_HRPD_SESSION_TYPE_LU);

            /* send StorageBLOB notification to AN */
            CNAS_HLU_SendStrgBlobNotification(&stMsgTxInfo);

            CNAS_HLU_StartTimer(TI_CNAS_HLU_WAIT_SIG_DATA_CNF, TI_CNAS_HLU_WAIT_SIG_DATA_CNF_LEN);


            break;
        }
        case CNAS_HLU_HRPD_BLOB_COMPLETE:
        {
            /* 向接入层发送保护请求 */
            CNAS_HLU_SndCasBeginSessionNotify(CNAS_CAS_HRPD_SESSION_TYPE_LU);

            /* send StorageBLOB Complete to AN */
            CNAS_HLU_SendStrgBlobComplete(&stMsgTxInfo);

            CNAS_HLU_StartTimer(TI_CNAS_HLU_WAIT_SIG_DATA_CNF, TI_CNAS_HLU_WAIT_SIG_DATA_CNF_LEN);

            break;
        }
        default:
        {
            CNAS_ERROR_LOG1(UEPS_PID_HLU, "CNAS_HLU_SndFsig:"
                                         "Invalid HRPD_MSG_TYPE received.",
                                         ucMsgId)
            break;
        }
    }

    return;
}


VOS_VOID CNAS_HLU_ClearBitInDByte(
    VOS_UINT16                         *usByte,
    VOS_UINT8                           ucBitNo
)
{
    VOS_UINT8                           ucActualBitNo;
    VOS_UINT16                          usTmp;

    if ((ucBitNo < 1) || (ucBitNo > 16))
    {
        return;
    }

    ucActualBitNo = ucBitNo - 1;
    usTmp         = 1;
    /*lint -e502*/
    *usByte      &= ~(usTmp << (ucActualBitNo & 0x0f));
    /*lint +e502*/

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HLU_StartTimer
 功能描述  : 启动HLU的保护定时器
 输入参数  : CNAS_HLU_TIMER_ID_ENUM_UINT32       enTimerId
             VOS_UINT32                          ulTimerLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月8日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HLU_StartTimer(
    CNAS_HLU_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulTimerLen
)
{
    CNAS_TIMER_INFO_STRU                stTimerInfo;

    if (0 == ulTimerLen)
    {
        CNAS_WARNING_LOG1(UEPS_PID_HLU, "CNAS_HLU_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return ;
    }

    NAS_MEM_SET_S(&stTimerInfo, sizeof(stTimerInfo), 0, sizeof(CNAS_TIMER_INFO_STRU));
    stTimerInfo.ulTimerId               = enTimerId;
    stTimerInfo.ulTimerLen              = ulTimerLen;
    stTimerInfo.ulParam                 = 0;
    stTimerInfo.ulTimerPrecision        = VOS_TIMER_PRECISION_0;

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HLU, enTimerId, 0))
    {
        /* 重新启动定时器 */
        CNAS_RestartTimer(UEPS_PID_HLU, &stTimerInfo);
    }

    /* 启动定时器 */
    CNAS_StartTimer(UEPS_PID_HLU, &stTimerInfo);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HLU_StopTimer
 功能描述  : 停止HLU的保护定时器
 输入参数  : CNAS_HLU_TIMER_ID_ENUM_UINT32       enTimerId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月8日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HLU_StopTimer(
    CNAS_HLU_TIMER_ID_ENUM_UINT32       enTimerId
)
{
    /* 停止定时器 */
    CNAS_StopTimer(UEPS_PID_HLU, enTimerId, 0);

    return;
}

/*lint -restore*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif





