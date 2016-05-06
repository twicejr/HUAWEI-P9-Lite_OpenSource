/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHluSndFsig.c
  版 本 号   : 初稿
  作    者   : y00213812
  生成日期   : 2014年12月16日
  最近修改   :
  功能描述   : HLU发送给L2 FSIG的消息处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月16日
    作    者   : Y00213812
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasHluSndFsig.h"
#include "CnasHluComm.h"
#include "CnasHluMain.h"
#include "PsCommonDef.h"
#include "vos.h"
#include "NasOmInterface.h"
#include "Nas_Mem.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HLU_SND_FSIG_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/


VOS_VOID CNAS_HLU_SendLocNotification(
    CNAS_HLU_MSG_TX_OPTION_INFO        *pstMsgTxInfo,
    VOS_BOOL                            bIsHandOff,
    CNAS_HLU_LOC_VALUE_STRU            *pstHandOffLocVal

)
{
    CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU   *pstSnpDataReq;
    VOS_VOID                           *pvSnpData;
    VOS_UINT32                          ulSize;

    if (CNAS_HLU_IsCurrLocTypeValid() || (VOS_TRUE == bIsHandOff))
    {
        ulSize    = sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU) + 4;
        pvSnpData = (VOS_VOID *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HLU, ulSize);
        if (CNAS_HLU_IS_NULL_PTR(pvSnpData))
        {
            CNAS_ERROR_LOG(UEPS_PID_HLU, "CNAS_HLU_SendLocNotification:"
                                         "memory allocation failure.");
            return;
        }

        NAS_MEM_SET_S(pvSnpData, ulSize, 0, ulSize);

        pstSnpDataReq = (CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU *)pvSnpData;

        /* 1. Fill usMsgBitLen = [MessageID_bitLen + locationType_bitLen
                                 + locationLength_bitLen + locationValue_bitLen]
           2. Fill LocationNotification : MessageID = 0x04, locationType and
              locationLength.
           3. Fill the current stored LocationValue in netwotk BYTE order.
        */
        pstSnpDataReq->stMsgData.usMsgBitLen   = CNAS_HLU_LOC_NOTIF_MSG_BIT_LEN;
        pstSnpDataReq->stMsgData.aucMsgData[0] = CNAS_HLU_HRPD_LOC_NOTIFICATION;
        pstSnpDataReq->stMsgData.aucMsgData[1] = CNAS_HLU_CDMA2000_HRPD_LOC_TYPE;
        pstSnpDataReq->stMsgData.aucMsgData[2] = CNAS_HLU_CDMA2000_HRPD_LOC_LEN;

        if (VOS_TRUE == bIsHandOff)
        {
            CNAS_HLU_SetHandOffOpId();
            pstSnpDataReq->usOpId = CNAS_HLU_GetHandOffOpId();
        }

        CNAS_HLU_GetCurrLocValHToN(&(pstSnpDataReq->stMsgData.aucMsgData[3]),
                                    bIsHandOff,
                                    pstHandOffLocVal);

    }
    else
    {
        /* It means current stored value on AT is not valid. */
        /* Do not include LocationLength and LocationVAlue in message to be sent. */
        ulSize    = sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU);
        pvSnpData = (VOS_VOID *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HLU,
                                        ulSize);
        if (VOS_NULL_PTR == pvSnpData)
        {
            CNAS_ERROR_LOG(UEPS_PID_HLU, "CNAS_HLU_SendLocNotification:" \
                                         "memory allocation failure.");
            return;
        }

        NAS_MEM_SET_S(pvSnpData, ulSize, 0, ulSize);

        pstSnpDataReq = (CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU *)pvSnpData;

        pstSnpDataReq->stMsgData.usMsgBitLen   = CNAS_HLU_NO_LOC_NOTIF_MSG_BIT_LEN;
        pstSnpDataReq->stMsgData.aucMsgData[0] = CNAS_HLU_HRPD_LOC_NOTIFICATION;
        pstSnpDataReq->stMsgData.aucMsgData[1] = CNAS_HLU_CDMA2000_HRPD_LOC_TYPE_INV;

    }

    pstSnpDataReq->ulLength = ulSize - VOS_MSG_HEAD_LENGTH;

    CNAS_HLU_FILL_MSG_HDR(pstSnpDataReq, UEPS_PID_HLU, CTTF_PID_HRPD_SIG);

    CNAS_HLU_FILL_SNP_REQ_MSG(pstSnpDataReq, pstMsgTxInfo, CNAS_HLU_GetProtocolType());

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSnpDataReq);

    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_UP,
                          NAS_OTA_MSG_HLU_LOC_NOTIFICATION,
                          UEPS_PID_HLU,
                         (VOS_UINT32)pstSnpDataReq->stMsgData.usMsgBitLen,
                          pstSnpDataReq->stMsgData.aucMsgData);

    /* Send message to FSIG. */
    (VOS_VOID)PS_SEND_MSG(CTTF_PID_HRPD_SIG, pstSnpDataReq);

    return;
}


VOS_VOID CNAS_HLU_SendLocComplete(
    CNAS_HLU_MSG_TX_OPTION_INFO        *pstMsgTxInfo
)
{
    CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU   *pstSnpDataReq;

    pstSnpDataReq = (CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HLU,
                                                    sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU));
    if (VOS_NULL_PTR == pstSnpDataReq)
    {
        return;
    }

    NAS_MEM_SET_S(pstSnpDataReq, sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU), 0, sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU));

    /* MsgLen in bits. */
    pstSnpDataReq->stMsgData.usMsgBitLen   = CNAS_HLU_LOC_COMP_MSG_BIT_LEN;

    pstSnpDataReq->stMsgData.aucMsgData[0] = CNAS_HLU_HRPD_LOC_COMPLETE;
    pstSnpDataReq->stMsgData.aucMsgData[1] = CNAS_HLU_GetLocMsgTransId();

    pstSnpDataReq->ulLength = sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU)
                                        - VOS_MSG_HEAD_LENGTH;

    CNAS_HLU_FILL_MSG_HDR(pstSnpDataReq, UEPS_PID_HLU, CTTF_PID_HRPD_SIG);

    CNAS_HLU_FILL_SNP_REQ_MSG(pstSnpDataReq, pstMsgTxInfo, CNAS_HLU_GetProtocolType());

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSnpDataReq);

    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_UP,
                          NAS_OTA_MSG_HLU_LOC_COMPLETE_UP,
                          UEPS_PID_HLU,
                         (VOS_UINT32)pstSnpDataReq->stMsgData.usMsgBitLen,
                          pstSnpDataReq->stMsgData.aucMsgData);


    /* Send message to FSIG. */
    (VOS_VOID)PS_SEND_MSG(CTTF_PID_HRPD_SIG, pstSnpDataReq);

    return;
}


VOS_VOID CNAS_HLU_SendStrgBlobNotification(
    CNAS_HLU_MSG_TX_OPTION_INFO        *pstMsgTxInfo
)
{
    CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU   *pstSnpDataReq;
    VOS_UINT32                          ulSize;
    VOS_UINT8                           ucBLOBLen;

    if (CNAS_HLU_IsCurrBlobTypeValid())
    {
        ucBLOBLen     = CNAS_HLU_GetCurrBlobLen();

        ulSize        = sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU) + ucBLOBLen;
        pstSnpDataReq = (CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU *)
                        PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HLU, ulSize);
        if (VOS_NULL_PTR == pstSnpDataReq)
        {
            return;
        }

        NAS_MEM_SET_S(pstSnpDataReq, ulSize, 0, ulSize);

        /* 1. Fill usMsgBitLen
           2. Fill MessageID.
           3. Fill StorageBLOB in network BYTE order
        */
        pstSnpDataReq->stMsgData.usMsgBitLen   = CNAS_HLU_BLOB_NOTIF_MSG_BIT_LEN(ucBLOBLen);
        pstSnpDataReq->stMsgData.aucMsgData[0] = CNAS_HLU_HRPD_BLOB_NOTIFICATION;

        CNAS_HLU_GetCurrStrgBlobHToN(&(pstSnpDataReq->stMsgData.aucMsgData[1]));

    }
    else
    {
        /* It means current stored value of StorageBlob stored on AT is not
           valid, Do not include aucStorageBLOB in message to be sent.
        */
        ulSize = sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU);
        pstSnpDataReq = (CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU *)
                        PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HLU, ulSize);

        if (VOS_NULL_PTR == pstSnpDataReq)
        {
            return;
        }

        NAS_MEM_SET_S(pstSnpDataReq, ulSize, 0, ulSize);

        /* 1. Get the stored value of SID, NID.
           2. Fill usMsgBitLen = [MessageID_bitLen + StorageBLOBType_bitLen
                             + StorageBLOBLength_bitLen + StorageBLOBValue_bitLen]
           3. Fill MessageID, StorageBLOBType and StorageBLOBLength.
        */
        pstSnpDataReq->stMsgData.usMsgBitLen   = CNAS_HLU_NO_BLOB_NOTIF_MSG_BIT_LEN;
        pstSnpDataReq->stMsgData.aucMsgData[0] = CNAS_HLU_HRPD_BLOB_NOTIFICATION; /* MessageID */
        pstSnpDataReq->stMsgData.aucMsgData[1] = CNAS_HLU_BYTE_NULL; /* StorageBLOBType BYTE1 */
        pstSnpDataReq->stMsgData.aucMsgData[2] = CNAS_HLU_BYTE_NULL; /* StorageBLOBType BYTE2 */
        pstSnpDataReq->stMsgData.aucMsgData[3] = CNAS_HLU_BYTE_NULL; /* StorageBLOBLength */

    }

    pstSnpDataReq->ulLength             = ulSize - VOS_MSG_HEAD_LENGTH;

    CNAS_HLU_FILL_MSG_HDR(pstSnpDataReq, UEPS_PID_HLU, CTTF_PID_HRPD_SIG);

    CNAS_HLU_FILL_SNP_REQ_MSG(pstSnpDataReq, pstMsgTxInfo, CNAS_HLU_GetProtocolType());

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSnpDataReq);

    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_UP,
                          NAS_OTA_MSG_HLU_BLOB_NOTIFICATION,
                          UEPS_PID_HLU,
                         (VOS_UINT32)pstSnpDataReq->stMsgData.usMsgBitLen,
                          pstSnpDataReq->stMsgData.aucMsgData);

    /* Send message to FSIG. */
    (VOS_VOID)PS_SEND_MSG(CTTF_PID_HRPD_SIG, pstSnpDataReq);

    return;

}


VOS_VOID CNAS_HLU_SendStrgBlobComplete(
    CNAS_HLU_MSG_TX_OPTION_INFO        *pstMsgTxInfo
)
{
    CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU   *pstSnpDataReq;

    pstSnpDataReq = (CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU *)
                    PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HLU, sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU));

    if (VOS_NULL_PTR == pstSnpDataReq)
    {
        return;
    }

    NAS_MEM_SET_S(pstSnpDataReq, sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU), 0, sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU));

    /* 1. Fill MsgLen in bits, MsgId, TransactionId. */
    pstSnpDataReq->stMsgData.usMsgBitLen   = CNAS_HLU_BLOB_COMP_MSG_BIT_LEN;

    pstSnpDataReq->stMsgData.aucMsgData[0] = CNAS_HLU_HRPD_BLOB_COMPLETE;
    pstSnpDataReq->stMsgData.aucMsgData[1] = CNAS_HLU_GetBLobTransId();

    pstSnpDataReq->ulLength = sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU)
                                        - VOS_MSG_HEAD_LENGTH;

    CNAS_HLU_FILL_MSG_HDR(pstSnpDataReq, UEPS_PID_HLU, CTTF_PID_HRPD_SIG);

    CNAS_HLU_FILL_SNP_REQ_MSG(pstSnpDataReq, pstMsgTxInfo, CNAS_HLU_GetProtocolType());

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSnpDataReq);

    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_UP,
                          NAS_OTA_MSG_HLU_BLOB_COMPLETE_UP,
                          UEPS_PID_HLU,
                         (VOS_UINT32)pstSnpDataReq->stMsgData.usMsgBitLen,
                          pstSnpDataReq->stMsgData.aucMsgData);

    /* Send message to FSIG. */
    (VOS_VOID)PS_SEND_MSG(CTTF_PID_HRPD_SIG, pstSnpDataReq);

    return;

}


/*lint -restore*/

#endif







#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




