

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "TafLog.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "xcc_aps_pif.h"
#include "TafApsProcEpdszid.h"

#include "TafApsComFunc.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_XCC_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


VOS_VOID TAF_APS_SndXccDataCallSuspendRsp(
    VOS_UINT8                           ucConnectId
)
{
    APS_XCC_DATA_CALL_SUSPEND_RSP_STRU *pstSuspendRsp = VOS_NULL_PTR;

    pstSuspendRsp = (APS_XCC_DATA_CALL_SUSPEND_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_XCC_DATA_CALL_SUSPEND_RSP_STRU));

    if (VOS_NULL_PTR == pstSuspendRsp)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndXccDataCallSuspendRsp: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstSuspendRsp + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_XCC_DATA_CALL_SUSPEND_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSuspendRsp->ulReceiverPid        = UEPS_PID_XCC;
    pstSuspendRsp->enMsgId              = ID_APS_XCC_DATA_CALL_SUSPEND_RSP;

    pstSuspendRsp->ucConnectId          = ucConnectId;

    PS_SEND_MSG(WUEPS_PID_TAF, pstSuspendRsp);

    return;
}


VOS_VOID TAF_APS_SndXccHangUpDataCallReq(
    VOS_UINT8                           ucCallId,
    TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
)
{
    APS_XCC_HANGUP_DATA_CALL_REQ_STRU  *pstHangUpReq = VOS_NULL_PTR;

    pstHangUpReq = (APS_XCC_HANGUP_DATA_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_XCC_HANGUP_DATA_CALL_REQ_STRU));

    if (VOS_NULL_PTR == pstHangUpReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndXccHangUpDataCallReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstHangUpReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_XCC_HANGUP_DATA_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstHangUpReq->ulReceiverPid   = UEPS_PID_XCC;
    pstHangUpReq->enMsgId         = ID_APS_XCC_HANGUP_DATA_CALL_REQ;
    pstHangUpReq->ucCallId        = ucCallId;
    pstHangUpReq->enEndReason     = enEndReason;

    PS_SEND_MSG(WUEPS_PID_TAF, pstHangUpReq);

    return;
}


VOS_VOID TAF_APS_SndXccOrigDataCallReq(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucHrpdHandOff1xFlg
)
{
    APS_XCC_ORIG_DATA_CALL_REQ_STRU        *pstOrigReq     = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity   = VOS_NULL_PTR;
    TAF_APS_CDATA_HRPD_EPDSZID_CTX_STRU    *pstHrpdActInfo = VOS_NULL_PTR;

    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstOrigReq = (APS_XCC_ORIG_DATA_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_XCC_ORIG_DATA_CALL_REQ_STRU));

    if (VOS_NULL_PTR == pstOrigReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndXccOrigDataCallReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstOrigReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_XCC_ORIG_DATA_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstOrigReq->ulReceiverPid           = UEPS_PID_XCC;
    pstOrigReq->enMsgId                 = ID_APS_XCC_ORIG_DATA_CALL_REQ;
    pstOrigReq->enSo                    = pstPdpEntity->stCdataInfo.enSo;
    pstOrigReq->ucCallId                = pstPdpEntity->stCdataInfo.ucCallId;
    pstOrigReq->ucDrsFlg                = pstPdpEntity->stCdataInfo.ucDrsFlg;
    pstOrigReq->ucIsDormDataCall        = pstPdpEntity->stCdataInfo.ucIsDormDataCall;
    pstOrigReq->ucReOrigCount           = pstPdpEntity->stCdataInfo.ucReOrigCount;
    pstOrigReq->ucIsL2ErrReOrig         = pstPdpEntity->stCdataInfo.ucIsL2ErrReOrig;
    pstOrigReq->ucSrId                  = pstPdpEntity->stCdataInfo.ucSrId;

    /* TODO:QOS */

    /* num filed默认值为DTMF编码格式的: #777 */
    pstOrigReq->stDialNumInfo.enDigitMode   = XCC_APS_DIGIT_MODE_DTMF;
    pstOrigReq->stDialNumInfo.ucDigitNum    = 4;
    pstOrigReq->stDialNumInfo.aucDigit[0]   = 0x0c;
    pstOrigReq->stDialNumInfo.aucDigit[1]   = 0x07;
    pstOrigReq->stDialNumInfo.aucDigit[2]   = 0x07;
    pstOrigReq->stDialNumInfo.aucDigit[3]   = 0x07;

    if (VOS_TRUE == ucHrpdHandOff1xFlg)
    {
        pstHrpdActInfo = TAF_APS_GetHrpdEpdszidInfo();

        pstOrigReq->ulIsPrevHrpdMode         = VOS_TRUE;
        pstOrigReq->stPrevHrpdActInfo.usSid  = pstHrpdActInfo->usSid;
        pstOrigReq->stPrevHrpdActInfo.usNid  = pstHrpdActInfo->usNid;
        pstOrigReq->stPrevHrpdActInfo.usPzid = pstHrpdActInfo->ucPzid;
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstOrigReq);

    return;
}


VOS_VOID TAF_APS_SndXccIncomingCallRsp(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConnectId,
    XCC_APS_RESULT_ENUM_UINT32          enRslt
)
{
    APS_XCC_INCOMING_CALL_RSP_STRU     *pstIncomingRsp = VOS_NULL_PTR;

    pstIncomingRsp  = (APS_XCC_INCOMING_CALL_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_XCC_INCOMING_CALL_RSP_STRU));

    if (VOS_NULL_PTR == pstIncomingRsp)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndXccIncomingCallRsp: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstIncomingRsp + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_XCC_INCOMING_CALL_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstIncomingRsp->ulReceiverPid       = UEPS_PID_XCC;
    pstIncomingRsp->enMsgId             = ID_APS_XCC_INCOMING_CALL_RSP;
    pstIncomingRsp->ucCallId            = ucCallId;
    pstIncomingRsp->ucConnectId         = ucConnectId;
    pstIncomingRsp->enRslt              = enRslt;

    PS_SEND_MSG(WUEPS_PID_TAF, pstIncomingRsp);

    return;
}


VOS_VOID TAF_APS_SndXccAnswerDataCallReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_XCC_ANSWER_DATA_CALL_REQ_STRU  *pstAnswerReq = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstAnswerReq    = (APS_XCC_ANSWER_DATA_CALL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_XCC_ANSWER_DATA_CALL_REQ_STRU));

    if (VOS_NULL_PTR == pstAnswerReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndXccAnswerDataCallReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstAnswerReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_XCC_ANSWER_DATA_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstAnswerReq->ulReceiverPid         = UEPS_PID_XCC;
    pstAnswerReq->enMsgId               = ID_APS_XCC_ANSWER_DATA_CALL_REQ;
    pstAnswerReq->ucCallId              = pstPdpEntity->stCdataInfo.ucCallId;

    PS_SEND_MSG(WUEPS_PID_TAF, pstAnswerReq);

    return;
}


VOS_VOID TAF_APS_SndXccPzidInfoNtf(
    XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
)
{
    APS_XCC_PZID_INFO_NTF_STRU         *pstPzidInfoNtf = VOS_NULL_PTR;
    TAF_APS_CDATA_EPDSZID_STRU         *pstCurrEpdszid = VOS_NULL_PTR;
    TAF_APS_CDATA_EPDSZID_CTX_STRU     *pstEpdszidCtx  = VOS_NULL_PTR;

    VOS_UINT8                           ucIndex;

    pstPzidInfoNtf = (APS_XCC_PZID_INFO_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                     sizeof(APS_XCC_PZID_INFO_NTF_STRU));

    if (VOS_NULL_PTR == pstPzidInfoNtf)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndXccPzidInfoNtf: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPzidInfoNtf + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_XCC_PZID_INFO_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* Head info */
    pstPzidInfoNtf->ulReceiverPid         = UEPS_PID_XCC;
    pstPzidInfoNtf->enMsgId               = ID_APS_XCC_PZID_INFO_NTF;

    /* Add Msg Info */
    if (VOS_TRUE == TAF_APS_GetHysEnableFlg())
    {
        pstCurrEpdszid = TAF_APS_GetCurrEpdszidInfo();

        pstPzidInfoNtf->ucPzidReportLen = TAF_APS_CDMA_EPDSZID_DEFAULT_MIN_LEN;
        pstPzidInfoNtf->aucPzid[0]      = pstCurrEpdszid->ucPzid;
    }
    else
    {
        pstEpdszidCtx = TAF_APS_GetEpdszidCtx();

        pstPzidInfoNtf->ucPzidReportLen = TAF_APS_GetCurrPacketZoneListLen();

        if (pstPzidInfoNtf->ucPzidReportLen < TAF_APS_CDMA_EPDSZID_LIST_MAX_LEN - 1)
        {
            for (ucIndex = 0; ucIndex < pstPzidInfoNtf->ucPzidReportLen; ucIndex++)
            {
                pstPzidInfoNtf->aucPzid[ucIndex] = pstEpdszidCtx->astEpdszidList[ucIndex].ucPzid;
            }
        }
    }

    pstPzidInfoNtf->ucConnectId = pstSoCtrlMsgInd->ucConnectId;
    pstPzidInfoNtf->usSo        = pstSoCtrlMsgInd->enSo;


    PS_SEND_MSG(WUEPS_PID_TAF, pstPzidInfoNtf);

    return;
}



VOS_VOID TAF_APS_SndXccReserveSrIdNtf(
    VOS_UINT8                           ucSrId,
    VOS_UINT8                           ucCallId,
    VOS_UINT16                          usSo
)
{
    APS_XCC_RESERVE_SR_ID_NTF_STRU     *pstSrIdNtf = VOS_NULL_PTR;

    pstSrIdNtf = (APS_XCC_RESERVE_SR_ID_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                     sizeof(APS_XCC_RESERVE_SR_ID_NTF_STRU));

    if (VOS_NULL_PTR == pstSrIdNtf)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndXccReserveSrIdNtf: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstSrIdNtf + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_XCC_RESERVE_SR_ID_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* Head info */
    pstSrIdNtf->ulReceiverPid       = UEPS_PID_XCC;
    pstSrIdNtf->enMsgId             = ID_APS_XCC_RESERVE_SR_ID_NTF;

    /* Add Msg Info */
    pstSrIdNtf->ucSrId              = ucSrId;
    pstSrIdNtf->ucCallId            = ucCallId;
    pstSrIdNtf->enSo                = usSo;


    PS_SEND_MSG(WUEPS_PID_TAF, pstSrIdNtf);

    return;
}


VOS_UINT32 TAF_APS_IsExist1xDataOperation(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enSo
)
{
    VOS_UINT8                           ucPdpId;

    /* 当前数据业务不在1X上，返回FALSE */
    if (TAF_APS_RAT_TYPE_1X != TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        return VOS_FALSE;
    }

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        if (enSo != TAF_APS_GetPdpEntSo(ucPdpId))
        {
            continue;
        }

        if (TAF_APS_CDATA_PS_STATE_ACTIVE == TAF_APS_GetPdpEntCdataPsState(ucPdpId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}




#endif


/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

