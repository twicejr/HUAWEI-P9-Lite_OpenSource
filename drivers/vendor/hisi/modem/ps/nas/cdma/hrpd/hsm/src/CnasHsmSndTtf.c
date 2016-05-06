

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmSndTtf.h"
#include "nas_cttf_hrpd_rmac_ctrl_pif.h"
#include "CnasHsmCtx.h"
#include "CnasMntn.h"
#include "CnasHsmComFunc.h"
#include "CnasCcb.h"
#include "CnasHsmMntn.h"
#include "CnasHsmFsmTbl.h"

#include "CnasHsmFsmUatiRequest.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_SND_TTF_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/

VOS_VOID CNAS_HSM_SndMacTransmitAtiNotify(
    CNAS_HSM_ATI_RECORD_STRU           *pstTransATI
)
{
    CNAS_CTTF_HRPD_TRANSMIT_ATI_NTF_STRU                   *pstTransAtiNtf;
    VOS_UINT32                                              ulLen;

    ulLen = sizeof(CNAS_CTTF_HRPD_TRANSMIT_ATI_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstTransAtiNtf = (CNAS_CTTF_HRPD_TRANSMIT_ATI_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);

    if (VOS_NULL_PTR == pstTransAtiNtf)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstTransAtiNtf + VOS_MSG_HEAD_LENGTH),
                  sizeof(CNAS_CTTF_HRPD_TRANSMIT_ATI_NTF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0x00,
                  sizeof(CNAS_CTTF_HRPD_TRANSMIT_ATI_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    CNAS_CFG_MSG_HDR(pstTransAtiNtf,
                     UEPS_PID_HSM,
                     CTTF_PID_HRPD_RMAC,
                     ID_CNAS_CTTF_HRPD_TRANSMIT_ATI_NTF,
                     ulLen);

    pstTransAtiNtf->usOpId = 0;

    pstTransAtiNtf->stTransmitAtiRecord.enATIType = CNAS_HSM_CovertHsmAtiTypeToTtfAtiType(
                                                        pstTransATI->enATIType);
    NAS_MEM_CPY_S(&(pstTransAtiNtf->stTransmitAtiRecord.aucATI[0]),
                  sizeof(pstTransAtiNtf->stTransmitAtiRecord.aucATI),
                  &(pstTransATI->aucATIValue[0]),
                  CTTF_HRPD_ATI_LENGTH_NUM);

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstTransAtiNtf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstTransAtiNtf);
}


VOS_VOID CNAS_HSM_SndMacReceiveAtiNotify(
    CNAS_HSM_ATI_LIST_INFO_STRU        *pstATIListInfo
)
{
    CNAS_CTTF_HRPD_RECEIVE_ATI_NTF_STRU                    *pstRcvAtiNtf;
    VOS_UINT8                                               i;
    VOS_UINT32                                              ulLen;

    /* 添加钩包ReceiveATIList */
    CNAS_HSM_LogReceiveATIListInfo(pstATIListInfo);

    ulLen  = sizeof(CNAS_CTTF_HRPD_RECEIVE_ATI_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstRcvAtiNtf = (CNAS_CTTF_HRPD_RECEIVE_ATI_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);

    if (VOS_NULL_PTR == pstRcvAtiNtf)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstRcvAtiNtf + VOS_MSG_HEAD_LENGTH),
                  sizeof(CNAS_CTTF_HRPD_RECEIVE_ATI_NTF_STRU) - VOS_MSG_HEAD_LENGTH,
                  0x00,
                  sizeof(CNAS_CTTF_HRPD_RECEIVE_ATI_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    CNAS_CFG_MSG_HDR(pstRcvAtiNtf,
                     UEPS_PID_HSM,
                     CTTF_PID_HRPD_RMAC,
                     ID_CNAS_CTTF_HRPD_RECEIVE_ATI_NTF,
                     ulLen);

    pstRcvAtiNtf->usOpId    = 0;

    pstRcvAtiNtf->ulAtiRecordNum = CNAS_MIN(pstATIListInfo->ulATIRecordNum, CNAS_HSM_MAX_UATI_REC_NUM);

    for (i = 0; i < CNAS_MIN(pstATIListInfo->ulATIRecordNum, CNAS_HSM_MAX_UATI_REC_NUM); i++)
    {
        pstRcvAtiNtf->astAtiRecord[i].enATIType = CNAS_HSM_CovertHsmAtiTypeToTtfAtiType(
                                                      pstATIListInfo->astATIEntry[i].enATIType);
        NAS_MEM_CPY_S(&(pstRcvAtiNtf->astAtiRecord[i].aucATI[0]),
                      sizeof(pstRcvAtiNtf->astAtiRecord[i].aucATI),
                      &(pstATIListInfo->astATIEntry[i].aucATIValue[0]),
                      CTTF_HRPD_ATI_LENGTH_NUM);
    }

    /* 初始化ATItype值 */
    for ( ; i < CNAS_HSM_MAX_UATI_REC_NUM; i++)
    {
        pstRcvAtiNtf->astAtiRecord[i].enATIType = CTTF_HRPD_INACTIVE_ATI;
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstRcvAtiNtf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstRcvAtiNtf);
}


VOS_VOID CNAS_HSM_SndTtfHrpdSnpDataReq(
    CNAS_CTTF_HRPD_SNP_DATA_REQ_HEADER_STRU                *pstSnpDataReqHeader,
    VOS_UINT16                                             *pusOpId,
    VOS_UINT16                                              usMsgBitLen,
    VOS_UINT8                                              *pucMsgBuf
)
{
    CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU   *pstSnpDataReq = VOS_NULL_PTR;
    VOS_UINT16                          usMsgByteLen;
    VOS_UINT32                          ulMsgDataLen;

    usMsgByteLen = CNAS_HSM_CovertBitLenToByteLen(usMsgBitLen);

    *pusOpId  = CNAS_HSM_GetSnpDataReqOpId();

    CNAS_HSM_IncreaseSnpDataReqOpId();

    /* SNPITF_MSG_DATA_STRU----should reduce the length of aucMsgData array */
    if (usMsgByteLen >= 4)
    {
        ulMsgDataLen = sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU) + usMsgByteLen - VOS_MSG_HEAD_LENGTH - 4;
    }
    else
    {
        ulMsgDataLen = sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    }

    /* Allocation memory for message */
    pstSnpDataReq = (CNAS_CTTF_HRPD_SNP_DATA_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulMsgDataLen);

    if (VOS_NULL_PTR == pstSnpDataReq)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstSnpDataReq) + VOS_MSG_HEAD_LENGTH, ulMsgDataLen, 0, ulMsgDataLen);

    CNAS_CFG_MSG_HDR(pstSnpDataReq,
                     UEPS_PID_HSM,
                     CTTF_PID_HRPD_SIG,
                     ID_CNAS_CTTF_HRPD_SNP_DATA_REQ,
                     ulMsgDataLen);

    pstSnpDataReq->usOpId                = *pusOpId;

    /* here we always use inuse instance in HSM module,config instance is used in AS layer */
    pstSnpDataReq->enInstanceType        = pstSnpDataReqHeader->enInstanceType;

    pstSnpDataReq->enDeliveryType        = pstSnpDataReqHeader->enDeliveryType;
    pstSnpDataReq->enChannelType         = pstSnpDataReqHeader->enChannelType;
    pstSnpDataReq->ucPriority            = pstSnpDataReqHeader->ucPriority;
    pstSnpDataReq->stMsgData.usMsgBitLen = usMsgBitLen;
    pstSnpDataReq->enProtocolType        = pstSnpDataReqHeader->enProtocolType;
    pstSnpDataReq->enAddressType         = pstSnpDataReqHeader->enAddressType;

    pstSnpDataReq->enNeedRslt            = CTTF_HRPD_BEST_EFFORT_NEED_RSLT;

    NAS_MEM_CPY_S(pstSnpDataReq->stMsgData.aucMsgData, usMsgByteLen, pucMsgBuf, usMsgByteLen);

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSnpDataReq);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstSnpDataReq);
}


VOS_VOID CNAS_HSM_SndKeepAliveReqMsg(VOS_VOID)
{
    VOS_UINT8                                              *pucKeepAliveReqMsgBuf = VOS_NULL_PTR;
    VOS_UINT16                                              usMsgBufBitLen;
    VOS_UINT16                                              usMsgBufByteLen;
    VOS_UINT8                                               ucTransId;
    VOS_UINT16                                              usOpId;
    CNAS_CTTF_HRPD_SNP_DATA_REQ_HEADER_STRU                 stSnpDataReqHeader;

    /* increase keep alive req TI while send new keep alive req to AN */
    CNAS_HSM_IncreaseKeepAliveReqTransId();

    ucTransId   = CNAS_HSM_GetKeepAliveReqTransId();

    usMsgBufByteLen = CNAS_HSM_KEEP_ALIVE_REQ_MSG_OCTET_LEN;

    /* first alloc UATI request message buffer */
    pucKeepAliveReqMsgBuf = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_HSM, usMsgBufByteLen);

    if (VOS_NULL_PTR == pucKeepAliveReqMsgBuf)
    {
        return;
    }

    NAS_MEM_SET_S(pucKeepAliveReqMsgBuf, usMsgBufByteLen, 0, usMsgBufByteLen);

    /* Encode keep alive message */
    usMsgBufBitLen   = 0;
    CNAS_HSM_EncodeKeepAliveReq((VOS_VOID *)&ucTransId,
                                &usMsgBufBitLen,
                                pucKeepAliveReqMsgBuf);

    if (0 == usMsgBufBitLen)
    {
        CNAS_HSM_LogCodecResultInd(ID_CNAS_HSM_MNTN_LOG_ENCODE_RESULT_IND, CNAS_HSM_ENCODE_FAILURE);

        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_SndKeepAliveReqMsg: After encode usMsgBitLen is 0");

        PS_MEM_FREE(UEPS_PID_HSM, pucKeepAliveReqMsgBuf);

        return;
    }

    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_UP,
                          NAS_OTA_MSG_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_REQ_UP,
                          UEPS_PID_HSM,
                         (VOS_UINT32)usMsgBufBitLen,
                         (VOS_UINT8 *)pucKeepAliveReqMsgBuf);

    NAS_MEM_SET_S(&stSnpDataReqHeader, sizeof(stSnpDataReqHeader), 0, sizeof(stSnpDataReqHeader));

    /* fill hrpd snp date request header */
    CNAS_CFG_CTTF_HRPD_SNP_DATA_REQ_HEADER(&stSnpDataReqHeader,
                                           CTTF_HRPD_SNP_SESSION_MANAGEMENT_PROTOCOL,
                                           CTTF_HRPD_ADDRESS_UNICAST,
                                           CTTF_HRPD_CHANNEL_AC_OR_RTC,
                                           CTTF_HRPD_DELIVERY_TYPE_BEST_EFFORT,
                                           CNAS_HSM_MSG_PRIORITY_KEEP_ALVIE_REQ,
                                           CTTF_HRPD_INSTANCE_INUSE);
    CNAS_HSM_SndTtfHrpdSnpDataReq(&stSnpDataReqHeader,
                                  &usOpId,
                                  usMsgBufBitLen,
                                  pucKeepAliveReqMsgBuf);

    CNAS_HSM_SaveKeepAliveReqSnpDataReqOpId(usOpId);

    PS_MEM_FREE(UEPS_PID_HSM, pucKeepAliveReqMsgBuf);
}


VOS_VOID CNAS_HSM_SndKeepAliveRspMsg(
    VOS_UINT8                           ucKeepAliveReqTransId
)
{
    VOS_UINT8                                              *pucKeepAliveRspMsgBuf = VOS_NULL_PTR;
    VOS_UINT16                                              usMsgBufBitLen;
    VOS_UINT16                                              usMsgBufByteLen;
    VOS_UINT16                                              usOpId;
    CNAS_CTTF_HRPD_SNP_DATA_REQ_HEADER_STRU                 stSnpDataReqHeader;

    usMsgBufByteLen = CNAS_HSM_KEEP_ALIVE_RESP_MSG_OCTET_LEN;

    /* first alloc UATI request message buffer */
    pucKeepAliveRspMsgBuf = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_HSM, usMsgBufByteLen);

    if (VOS_NULL_PTR == pucKeepAliveRspMsgBuf)
    {
        return;
    }

    NAS_MEM_SET_S(pucKeepAliveRspMsgBuf, usMsgBufByteLen, 0, usMsgBufByteLen);

    /* Encode keep alive message */
    usMsgBufBitLen   = 0;
    CNAS_HSM_EncodeKeepAliveResp((VOS_VOID *)&ucKeepAliveReqTransId,
                                &usMsgBufBitLen,
                                pucKeepAliveRspMsgBuf);

    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_UP,
                          NAS_OTA_MSG_HSM_SMP_MESSAGE_TYPE_KEEP_ALIVE_RESP_UP,
                          UEPS_PID_HSM,
                         (VOS_UINT32)usMsgBufBitLen,
                          pucKeepAliveRspMsgBuf);

    if (0 == usMsgBufBitLen)
    {
        CNAS_HSM_LogCodecResultInd(ID_CNAS_HSM_MNTN_LOG_ENCODE_RESULT_IND, CNAS_HSM_ENCODE_FAILURE);

        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_SndKeepAliveRspMsg: After encode usMsgBitLen is 0");

        PS_MEM_FREE(UEPS_PID_HSM, pucKeepAliveRspMsgBuf);

        return;
    }

    NAS_MEM_SET_S(&stSnpDataReqHeader, sizeof(stSnpDataReqHeader), 0, sizeof(stSnpDataReqHeader));

    /* fill hrpd snp date request header */
    CNAS_CFG_CTTF_HRPD_SNP_DATA_REQ_HEADER(&stSnpDataReqHeader,
                                           CTTF_HRPD_SNP_SESSION_MANAGEMENT_PROTOCOL,
                                           CTTF_HRPD_ADDRESS_UNICAST,
                                           CTTF_HRPD_CHANNEL_AC_OR_RTC,
                                           CTTF_HRPD_DELIVERY_TYPE_BEST_EFFORT,
                                           CNAS_HSM_MSG_PRIORITY_KEEP_ALVIE_RSP,
                                           CTTF_HRPD_INSTANCE_INUSE);

    CNAS_HSM_SndTtfHrpdSnpDataReq(&stSnpDataReqHeader,
                                  &usOpId,
                                  usMsgBufBitLen,
                                  pucKeepAliveRspMsgBuf);

    CNAS_HSM_SaveKeepAliveRspSnpDataReqOpId(usOpId);

    PS_MEM_FREE(UEPS_PID_HSM, pucKeepAliveRspMsgBuf);
}



VOS_VOID CNAS_HSM_SndHardWareIdRspMsg(
    CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU                 *pstHardWareIdRsp
)
{
    CNAS_CTTF_HRPD_SNP_DATA_REQ_HEADER_STRU                 stSnpDataReqHeader;
    VOS_UINT8                                               ucHardwareIdLen;
    VOS_UINT16                                              usMsgBitLen;
    VOS_UINT16                                              usMsgByteLen;
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                              *pucHwIdRspMsgBuf = VOS_NULL_PTR;

    /* first alloc message for hardare id response */
    ucHardwareIdLen = CNAS_HSM_GetHardwareIdLength(pstHardWareIdRsp);
    usMsgByteLen    = CNAS_HSM_GET_HARDWARE_ID_RESPONSE_MSG_OCTET_LEN(ucHardwareIdLen);

    pucHwIdRspMsgBuf = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_HSM, usMsgByteLen);

    if (VOS_NULL_PTR == pucHwIdRspMsgBuf)
    {
        return;
    }

    /* Encode HardWareId Resp message and send to SNP */
    CNAS_HSM_EncodeHardwareIdResponse((VOS_VOID*)pstHardWareIdRsp,
                                      &usMsgBitLen,
                                      pucHwIdRspMsgBuf);

    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_UP,
                          NAS_OTA_MSG_HSM_AMP_MSG_TYPE_HARDWAREID_RESP,
                          UEPS_PID_HSM,
                         (VOS_UINT32)usMsgBitLen,
                          pucHwIdRspMsgBuf);

    if (0 == usMsgBitLen)
    {
        CNAS_HSM_LogCodecResultInd(ID_CNAS_HSM_MNTN_LOG_ENCODE_RESULT_IND, CNAS_HSM_ENCODE_FAILURE);
        PS_MEM_FREE(UEPS_PID_HSM, pucHwIdRspMsgBuf);

        return;
    }

    NAS_MEM_SET_S(&stSnpDataReqHeader, sizeof(stSnpDataReqHeader), 0, sizeof(stSnpDataReqHeader));

    /* fill hrpd snp date request header */
    CNAS_CFG_CTTF_HRPD_SNP_DATA_REQ_HEADER(&stSnpDataReqHeader,
                                           CTTF_HRPD_SNP_ADDRESS_MANAGEMENT_PROTOCOL,
                                           CTTF_HRPD_ADDRESS_UNICAST,
                                           CTTF_HRPD_CHANNEL_AC_OR_RTC,
                                           CTTF_HRPD_DELIVERY_TYPE_RELIABLE,
                                           CNAS_HSM_MSG_PRIORITY_HARDWARE_ID_RESP,
                                           CTTF_HRPD_INSTANCE_INUSE);

    CNAS_HSM_SndTtfHrpdSnpDataReq(&stSnpDataReqHeader,
                                  &usOpId,
                                  usMsgBitLen,
                                  pucHwIdRspMsgBuf);

    CNAS_HSM_SaveHardWareIdRspSnpDataReqOpId(usOpId);

    PS_MEM_FREE(UEPS_PID_HSM, pucHwIdRspMsgBuf);
}



VOS_VOID CNAS_HSM_SndSessionCloseMsg(
    CNAS_HSM_SESSION_CLOSE_MSG_STRU                        *pstSessionClose
)
{
    VOS_UINT8                                              *pucSessionCloseMsgBuf;
    VOS_UINT16                                              usMsgBitLen;
    VOS_UINT16                                              usMsgByteLen;
    CNAS_CTTF_HRPD_SNP_DATA_REQ_HEADER_STRU                 stSnpDataReqHeader;

    VOS_UINT16                                              usOpId;

    usMsgByteLen  = CNAS_HSM_GetSessionCloseMsgEncodedBufLen(pstSessionClose);

    pucSessionCloseMsgBuf = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_HSM, usMsgByteLen);

    if (VOS_NULL_PTR == pucSessionCloseMsgBuf)
    {
        return;
    }

    /* Encode Session Close message and send to SNP */
    usMsgBitLen = 0;
    CNAS_HSM_EncodeSessionClose((VOS_VOID*)pstSessionClose,
                                 &usMsgBitLen,
                                 pucSessionCloseMsgBuf);

    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_UP,
                          NAS_OTA_MSG_HSM_SMP_MESSAGE_TYPE_SESSION_CLOSE_UP,
                          UEPS_PID_HSM,
                         (VOS_UINT32)usMsgBitLen,
                          pucSessionCloseMsgBuf);

    NAS_MEM_SET_S(&stSnpDataReqHeader, sizeof(stSnpDataReqHeader), 0, sizeof(CNAS_CTTF_HRPD_SNP_DATA_REQ_HEADER_STRU));

    /* fill hrpd snp date request header */
    CNAS_CFG_CTTF_HRPD_SNP_DATA_REQ_HEADER(&stSnpDataReqHeader,
                                           CNAS_HSM_SESSION_MANAGEMENT_PROTOCOL,
                                           CTTF_HRPD_ADDRESS_UNICAST,
                                           CTTF_HRPD_CHANNEL_AC_OR_RTC,
                                           CTTF_HRPD_DELIVERY_TYPE_BEST_EFFORT,
                                           CNAS_HSM_MSG_PRIORITY_SESSION_CLOSE,
                                           CTTF_HRPD_INSTANCE_INUSE);

    CNAS_HSM_SndTtfHrpdSnpDataReq(&stSnpDataReqHeader,
                                  &usOpId,
                                  usMsgBitLen,
                                  pucSessionCloseMsgBuf);

    /* 无论是AN发起还是AT发起同一时间只能存在一个Session Deactive流程，
       所以可以使用一个全局变量来保存AN和AT触发的两种场景发送的Session Close消息的OpId */
    CNAS_HSM_SaveSessionCloseSnpDataReqOpId(usOpId);

    PS_MEM_FREE(UEPS_PID_HSM, pucSessionCloseMsgBuf);
}


VOS_VOID CNAS_HSM_SndUatiCmplMsg(VOS_VOID)
{
    VOS_UINT8                                              *pucUATICmpMsgBuf = VOS_NULL_PTR;
    CNAS_HSM_UATI_INFO_STRU                                *pstGlobalUait    = VOS_NULL_PTR;
    VOS_UINT16                                              usMsgBufBitLen;
    VOS_UINT16                                              usMsgBufByteLen;
    CNAS_HSM_UATI_COMP_MSG_STRU                             stUaitCmpInput;
    CNAS_CTTF_HRPD_SNP_DATA_REQ_HEADER_STRU                 stSnpDataReqHeader;

    VOS_UINT16                                              usOpId;

    pstGlobalUait = &(CNAS_HSM_GetSessionCtrlInfoAddr()->stUATIInfo);

    /* first alloc uati complete message */
    usMsgBufByteLen = CNAS_HSM_GET_UATI_COMPLETE_MSG_OCTET_LEN(pstGlobalUait->ucOldUATILen);

    pucUATICmpMsgBuf = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_HSM, usMsgBufByteLen);

    if (VOS_NULL_PTR == pucUATICmpMsgBuf)
    {
        return;
    }

    NAS_MEM_SET_S(pucUATICmpMsgBuf, usMsgBufByteLen, 0, usMsgBufByteLen);

    NAS_MEM_SET_S(&stUaitCmpInput, sizeof(stUaitCmpInput), 0, sizeof(stUaitCmpInput));

    /* Fullfill UATIComplte input paramters, C.S0024 7.3.7.2.3 UAIComplete */
    stUaitCmpInput.ucMsgSeq        = CNAS_HSM_GetCurrUATIAssignMsgSeqNum();
    stUaitCmpInput.ucOldUATILen    = pstGlobalUait->ucOldUATILen;

    NAS_MEM_CPY_S(stUaitCmpInput.aucOldUATI, sizeof(stUaitCmpInput.aucOldUATI), pstGlobalUait->aucOldUATI, CNAS_HSM_UATI_OCTET_LENGTH);

    /* Encode UATIComplete message */
    usMsgBufBitLen = 0;
    CNAS_HSM_EncodeUATIComplete(&stUaitCmpInput,
                                &usMsgBufBitLen,
                                pucUATICmpMsgBuf);
    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_UP,
                          NAS_OTA_MSG_HSM_AMP_MSG_TYPE_UATI_COMPLETE,
                          UEPS_PID_HSM,
                         (VOS_UINT32)usMsgBufBitLen,
                          pucUATICmpMsgBuf);

    if (0 == usMsgBufBitLen)
    {
        CNAS_HSM_LogCodecResultInd(ID_CNAS_HSM_MNTN_LOG_ENCODE_RESULT_IND, CNAS_HSM_ENCODE_FAILURE);
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_SndUatiCmplMsg_UatiReq: After encode usMsgBitLen is 0");

        PS_MEM_FREE(UEPS_PID_HSM, pucUATICmpMsgBuf);

        return;
    }

    NAS_MEM_SET_S(&stSnpDataReqHeader, sizeof(stSnpDataReqHeader), 0, sizeof(stSnpDataReqHeader));

    /* fill hrpd snp date request header */
    CNAS_CFG_CTTF_HRPD_SNP_DATA_REQ_HEADER(&stSnpDataReqHeader,
                                           CTTF_HRPD_SNP_ADDRESS_MANAGEMENT_PROTOCOL,
                                           CTTF_HRPD_ADDRESS_UNICAST,
                                           CTTF_HRPD_CHANNEL_AC_OR_RTC,
                                           CTTF_HRPD_DELIVERY_TYPE_RELIABLE,
                                           CNAS_HSM_MSG_PRIORITY_UATI_COMP,
                                           CTTF_HRPD_INSTANCE_INUSE);

    CNAS_HSM_SndTtfHrpdSnpDataReq(&stSnpDataReqHeader,
                                  &usOpId,
                                  usMsgBufBitLen,
                                  pucUATICmpMsgBuf);

    CNAS_HSM_SaveUatiCmplSnpDataReqOpId(usOpId);

    PS_MEM_FREE(UEPS_PID_HSM, pucUATICmpMsgBuf);
}



VOS_VOID CNAS_HSM_SndTtfHrpdPASessionCloseInd(VOS_VOID)
{
    CNAS_CTTF_HRPD_PA_SESSION_CLOSED_IND_STRU              *pstSessionCloseInd;
    VOS_UINT32                                              ulLen;

    ulLen = sizeof(CNAS_CTTF_HRPD_PA_SESSION_CLOSED_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSessionCloseInd = (CNAS_CTTF_HRPD_PA_SESSION_CLOSED_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSM, ulLen);

    if (VOS_NULL_PTR == pstSessionCloseInd)
    {
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstSessionCloseInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               sizeof(CNAS_CTTF_HRPD_PA_SESSION_CLOSED_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    CNAS_CFG_MSG_HDR(pstSessionCloseInd,
                     UEPS_PID_HSM,
                     CTTF_PID_HRPD_RPA,
                     ID_CNAS_CTTF_HRPD_PA_SESSION_CLOSED_IND,
                     ulLen);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstSessionCloseInd);
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


