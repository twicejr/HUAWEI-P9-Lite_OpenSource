

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmMntn.h"
#include "CnasMntn.h"
#include "CnasHsmCtx.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_MNTN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 Global variable
*****************************************************************************/

/*****************************************************************************
  3 Function Definitions
*****************************************************************************/

VOS_VOID CNAS_HSM_LogHwIdInfo(
    CNAS_HSM_HARDWARE_ID_INFO_STRU     *pstHwIdInfo
)
{
    CNAS_HSM_LOG_HWID_INFO_STRU        *pstMsg               = VOS_NULL_PTR;

    pstMsg = (CNAS_HSM_LOG_HWID_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_HSM,
                          (sizeof(CNAS_HSM_LOG_HWID_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_LogHwIdInfo:ERROR:Alloc Mem Fail!");

        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_HSM_LOG_HWID_INFO_STRU), 0, sizeof(CNAS_HSM_LOG_HWID_INFO_STRU));

    CNAS_CFG_MSG_HDR(pstMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_LOG_HARDWARE_ID_INFO,
                     (sizeof(CNAS_HSM_LOG_HWID_INFO_STRU) - VOS_MSG_HEAD_LENGTH));

    NAS_MEM_CPY_S(pstMsg->aucMeId, sizeof(pstMsg->aucMeId), pstHwIdInfo->aucMeId, CNAS_HSM_MEID_OCTET_NUM);
    pstMsg->ulEsn                       = pstHwIdInfo->ulEsn;
    pstMsg->enHwidType                  = pstHwIdInfo->enHwidType;
    pstMsg->enHwidSrcType               = pstHwIdInfo->enHwidSrcType;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_HWID_INFO_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstMsg);

    return;
}


VOS_VOID  CNAS_HSM_LogBufferMsgInfo(
    MSG_HEADER_STRU                                        *pstCurOperateMsgHead,
    VOS_UINT8                                               ucMsgBuffIndex,
    CNAS_HSM_BUFFER_MSG_OPERATE_TYPE_ENUM_UINT32            enOperateType
)
{
    VOS_UINT32                          i;
    MSG_HEADER_STRU                    *pstBuffMsgHead  = VOS_NULL_PTR;
    CNAS_HSM_LOG_BUFFER_MSG_INFO_STRU  *pstBufferMsg    = VOS_NULL_PTR;
    CNAS_HSM_CACHE_MSG_QUEUE_STRU      *pstMsgQueue     = VOS_NULL_PTR;

    pstBufferMsg = (CNAS_HSM_LOG_BUFFER_MSG_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_HSM,
                             sizeof(CNAS_HSM_LOG_BUFFER_MSG_INFO_STRU));

    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_LogBufferQueueMsg: Alloc Memory Failed!");
        return;
    }

    NAS_MEM_SET_S(pstBufferMsg, sizeof(CNAS_HSM_LOG_BUFFER_MSG_INFO_STRU), 0, sizeof(CNAS_HSM_LOG_BUFFER_MSG_INFO_STRU));

    CNAS_CFG_MSG_HDR(pstBufferMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_LOG_BUFFER_MSG_INFO_IND,
                     sizeof(CNAS_HSM_LOG_BUFFER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsgQueue                                 = CNAS_HSM_GetCacheMsgAddr();

    pstBufferMsg->ucCacheMsgNum                 = pstMsgQueue->ucCacheMsgNum;
    pstBufferMsg->enOperateType                 = enOperateType;
    pstBufferMsg->ucCurOperateMsgBuffIndex      = ucMsgBuffIndex;
    pstBufferMsg->ulCurOperateMsgId             = pstCurOperateMsgHead->ulMsgName;
    pstBufferMsg->ulCurOperateMsgSenderPid      = pstCurOperateMsgHead->ulSenderPid;

    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        pstBuffMsgHead = (MSG_HEADER_STRU *)pstMsgQueue->astCacheMsg[i].pucMsgBuffer;

        pstBufferMsg->astCacheMsg[i].enMsgPri   = pstMsgQueue->astCacheMsg[i].enMsgPri;

        if (VOS_NULL_PTR != pstMsgQueue->astCacheMsg[i].pucMsgBuffer)
        {
            NAS_MEM_CPY_S(pstBufferMsg->astCacheMsg[i].aucMsgBuffer,
                          sizeof(pstBufferMsg->astCacheMsg[i].aucMsgBuffer),
                          pstMsgQueue->astCacheMsg[i].pucMsgBuffer,
                          (pstBuffMsgHead->ulLength + VOS_MSG_HEAD_LENGTH));
        }
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_BUFFER_MSG_INFO_STRU), (VOS_VOID *)pstBufferMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstBufferMsg);

    return;
}



VOS_VOID  CNAS_HSM_LogFsmStateInfoInd(
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulOldState,
    VOS_UINT32                          ulNewState
)
{
    CNAS_HSM_LOG_FSM_STATE_INFO_IND_STRU                   *pstFsmStateInfoMsg = VOS_NULL_PTR;

    pstFsmStateInfoMsg = (CNAS_HSM_LOG_FSM_STATE_INFO_IND_STRU*)PS_MEM_ALLOC(UEPS_PID_HSM,
                             sizeof(CNAS_HSM_LOG_FSM_STATE_INFO_IND_STRU));

    if ( VOS_NULL_PTR == pstFsmStateInfoMsg )
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_LogFsmStateInfoInd: Alloc Memory Failed!");
        return;
    }

    NAS_MEM_SET_S(pstFsmStateInfoMsg, sizeof(CNAS_HSM_LOG_FSM_STATE_INFO_IND_STRU), 0, sizeof(CNAS_HSM_LOG_FSM_STATE_INFO_IND_STRU));

    CNAS_CFG_MSG_HDR(pstFsmStateInfoMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ulMsgId,
                     (sizeof(CNAS_HSM_LOG_FSM_STATE_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstFsmStateInfoMsg->ulOldState = ulOldState;
    pstFsmStateInfoMsg->ulNewState = ulNewState;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_FSM_STATE_INFO_IND_STRU), (VOS_VOID *)pstFsmStateInfoMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstFsmStateInfoMsg);

    return;
}


VOS_VOID  CNAS_HSM_LogCodecResultInd(
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulErrCode
)
{
    CNAS_HSM_LOG_CODEC_RESULT_IND_STRU *pstCodecRsltMsg = VOS_NULL_PTR;

    pstCodecRsltMsg = (CNAS_HSM_LOG_CODEC_RESULT_IND_STRU*)PS_MEM_ALLOC(UEPS_PID_HSM,
                             sizeof(CNAS_HSM_LOG_CODEC_RESULT_IND_STRU));

    if ( VOS_NULL_PTR == pstCodecRsltMsg )
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_LogCodecResultInd: Alloc Memory Failed!");
        return;
    }

    NAS_MEM_SET_S(pstCodecRsltMsg, sizeof(CNAS_HSM_LOG_CODEC_RESULT_IND_STRU), 0, sizeof(CNAS_HSM_LOG_CODEC_RESULT_IND_STRU));

    CNAS_CFG_MSG_HDR(pstCodecRsltMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ulMsgId,
                     (sizeof(CNAS_HSM_LOG_CODEC_RESULT_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstCodecRsltMsg->ulErrCode = ulErrCode;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_CODEC_RESULT_IND_STRU), (VOS_VOID *)pstCodecRsltMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstCodecRsltMsg);

    return;
}


VOS_VOID  CNAS_HSM_LogUatiReqMsg(
    CNAS_HSM_UATI_REQ_MSG_STRU                             *pstUatiReq
)
{
    CNAS_HSM_LOG_MNTN_UATI_REQ_STRU                        *pstLogUatiReq;

    pstLogUatiReq = (CNAS_HSM_LOG_MNTN_UATI_REQ_STRU *)
                   PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_MNTN_UATI_REQ_STRU));

    if (VOS_NULL_PTR == pstLogUatiReq)
    {
        return;
    }
    NAS_MEM_SET_S(pstLogUatiReq, sizeof(CNAS_HSM_LOG_MNTN_UATI_REQ_STRU), 0x00, sizeof(CNAS_HSM_LOG_MNTN_UATI_REQ_STRU));
    CNAS_CFG_MSG_HDR(pstLogUatiReq,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_MSG_TYPE_UATI_REQ,
                     (sizeof(CNAS_HSM_LOG_MNTN_UATI_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstLogUatiReq->stUatiReq.ucTransactionId = pstUatiReq->ucTransactionId;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_LOG_MNTN_UATI_REQ_STRU),
                          (VOS_VOID *)pstLogUatiReq);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogUatiReq);

}


VOS_VOID  CNAS_HSM_LogUatiCompMsg(
    CNAS_HSM_UATI_COMP_MSG_STRU                            *pstUatiCmp
)
{
    CNAS_HSM_LOG_MNTN_UATI_COMP_STRU                       *pstLogUatiCmp;

    pstLogUatiCmp = (CNAS_HSM_LOG_MNTN_UATI_COMP_STRU *)
                   PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_MNTN_UATI_COMP_STRU));
    if (VOS_NULL_PTR == pstLogUatiCmp)
    {
        return;
    }
    NAS_MEM_SET_S(pstLogUatiCmp, sizeof(CNAS_HSM_LOG_MNTN_UATI_COMP_STRU), 0x00, sizeof(CNAS_HSM_LOG_MNTN_UATI_COMP_STRU));
    CNAS_CFG_MSG_HDR(pstLogUatiCmp,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_MSG_TYPE_UATI_COMPLETE,
                     (sizeof(CNAS_HSM_LOG_MNTN_UATI_COMP_STRU) - VOS_MSG_HEAD_LENGTH));

    NAS_MEM_CPY_S(&pstLogUatiCmp->stUatiComp,
                  sizeof(pstLogUatiCmp->stUatiComp),
                  pstUatiCmp,
                  sizeof(CNAS_HSM_UATI_COMP_MSG_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_LOG_MNTN_UATI_COMP_STRU),
                          (VOS_VOID *)pstLogUatiCmp);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogUatiCmp);
}


VOS_VOID  CNAS_HSM_LogHardWareIdRespMsg(
    CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU                 *pstHardwareIdInfo
)
{
    CNAS_HSM_LOG_MNTN_HARDWARE_ID_RESP_STRU                *pstLogHardwareIdResp;

    pstLogHardwareIdResp = (CNAS_HSM_LOG_MNTN_HARDWARE_ID_RESP_STRU *)
                            PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_MNTN_HARDWARE_ID_RESP_STRU));
    if (VOS_NULL_PTR == pstLogHardwareIdResp)
    {
        return;
    }
    NAS_MEM_SET_S(pstLogHardwareIdResp, sizeof(CNAS_HSM_LOG_MNTN_HARDWARE_ID_RESP_STRU), 0x00, sizeof(CNAS_HSM_LOG_MNTN_HARDWARE_ID_RESP_STRU));

    CNAS_CFG_MSG_HDR(pstLogHardwareIdResp,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_MSG_TYPE_HARDWAREID_RESP,
                     (sizeof(CNAS_HSM_LOG_MNTN_HARDWARE_ID_RESP_STRU) - VOS_MSG_HEAD_LENGTH));

    NAS_MEM_CPY_S(&pstLogHardwareIdResp->stHardwareIdRsp,
                  sizeof(pstLogHardwareIdResp->stHardwareIdRsp),
                  pstHardwareIdInfo,
                  sizeof(CNAS_HSM_HARDWARE_ID_RESPONSE_MSG_STRU));


    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_LOG_MNTN_HARDWARE_ID_RESP_STRU),
                          (VOS_VOID *)pstLogHardwareIdResp);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogHardwareIdResp);
}


VOS_VOID  CNAS_HSM_LogSessionCloseMsg(
    CNAS_HSM_SESSION_CLOSE_MSG_STRU                        *pstSessionCloseInput
)
{
    CNAS_HSM_LOG_MNTN_SESSION_CLOSE_STRU                   *pstLogSessionCloseMsg;

    pstLogSessionCloseMsg = (CNAS_HSM_LOG_MNTN_SESSION_CLOSE_STRU *)
                            PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_MNTN_SESSION_CLOSE_STRU));
    if (VOS_NULL_PTR == pstLogSessionCloseMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstLogSessionCloseMsg, sizeof(CNAS_HSM_LOG_MNTN_SESSION_CLOSE_STRU), 0x00, sizeof(CNAS_HSM_LOG_MNTN_SESSION_CLOSE_STRU));
    CNAS_CFG_MSG_HDR(pstLogSessionCloseMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_MSG_TYPE_SESSION_CLOSE,
                     (sizeof(CNAS_HSM_LOG_MNTN_SESSION_CLOSE_STRU) - VOS_MSG_HEAD_LENGTH));

    NAS_MEM_CPY_S(&pstLogSessionCloseMsg->stSessionClose,
                  sizeof(pstLogSessionCloseMsg->stSessionClose),
                  pstSessionCloseInput,
                  sizeof(CNAS_HSM_SESSION_CLOSE_MSG_STRU));


    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_LOG_MNTN_SESSION_CLOSE_STRU),
                          (VOS_VOID *)pstLogSessionCloseMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogSessionCloseMsg);
}


VOS_VOID  CNAS_HSM_LogHardWareIdReqMsg(
    CNAS_HSM_HARDWARE_ID_REQ_MSG                              *pstHardWareIdReq
)
{
    CNAS_HSM_LOG_MNTN_HARDWARE_ID_REQ_STRU                    *pstLogHardWareIdreq;

    pstLogHardWareIdreq = (CNAS_HSM_LOG_MNTN_HARDWARE_ID_REQ_STRU *)
                            PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_MNTN_HARDWARE_ID_REQ_STRU));

    if (VOS_NULL_PTR == pstLogHardWareIdreq)
    {
        return;
    }

    NAS_MEM_SET_S(pstLogHardWareIdreq, sizeof(CNAS_HSM_LOG_MNTN_HARDWARE_ID_REQ_STRU), 0x00, sizeof(CNAS_HSM_LOG_MNTN_HARDWARE_ID_REQ_STRU));
    CNAS_CFG_MSG_HDR(pstLogHardWareIdreq,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_MSG_TYPE_HARDWAREID_REQ,
                     (sizeof(CNAS_HSM_LOG_MNTN_HARDWARE_ID_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstLogHardWareIdreq->stHardWareIdReq.ucTransactionId = pstHardWareIdReq->ucTransactionId;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_LOG_MNTN_HARDWARE_ID_REQ_STRU),
                          (VOS_VOID *)pstLogHardWareIdreq);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogHardWareIdreq);

}


VOS_VOID  CNAS_HSM_LogUatiAssignMsg(
    CNAS_HSM_UATI_ASSIGN_MSG_STRU                          *pstUatiAssign,
    CNAS_HSM_UATI_ASSIGN_CATE_ENUM_UINT32                   enUatiAssignCate
)
{
    CNAS_HSM_LOG_MNTN_UATI_ASSIGN_STRU                     *pstLogUatiAssign;

    pstLogUatiAssign = (CNAS_HSM_LOG_MNTN_UATI_ASSIGN_STRU *)
                            PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_MNTN_UATI_ASSIGN_STRU));

    if (VOS_NULL_PTR == pstLogUatiAssign)
    {
        return;
    }

    NAS_MEM_SET_S(pstLogUatiAssign, sizeof(CNAS_HSM_LOG_MNTN_UATI_ASSIGN_STRU), 0x00, sizeof(CNAS_HSM_LOG_MNTN_UATI_ASSIGN_STRU));
    CNAS_CFG_MSG_HDR(pstLogUatiAssign,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_MSG_TYPE_UATI_ASSIGN,
                     (sizeof(CNAS_HSM_LOG_MNTN_UATI_ASSIGN_STRU) - VOS_MSG_HEAD_LENGTH));

    pstLogUatiAssign->enUatiAssignCate = enUatiAssignCate;

    NAS_MEM_CPY_S(&pstLogUatiAssign->stUatiAssign,
                  sizeof(pstLogUatiAssign->stUatiAssign),
                  pstUatiAssign,
                  sizeof(CNAS_HSM_UATI_ASSIGN_MSG_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_LOG_MNTN_UATI_ASSIGN_STRU),
                          (VOS_VOID *)pstLogUatiAssign);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogUatiAssign);
}


VOS_VOID CNAS_HSM_LogAmpSmpNegAttribInfoInd(
    CNAS_HSM_AMP_NEG_ATTRIB_STRU                           *pstAmpNegAttrib,
    CNAS_HSM_SMP_NEG_ATTRIB_STRU                           *pstSmpNegAttrib
)
{
    CNAS_HSM_LOG_MNTN_AMP_SMP_NEG_ATTRIB_IND_STRU          *pstLogAmpSmpAttrib;

    pstLogAmpSmpAttrib = (CNAS_HSM_LOG_MNTN_AMP_SMP_NEG_ATTRIB_IND_STRU *)
                            PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_MNTN_AMP_SMP_NEG_ATTRIB_IND_STRU));

    if (VOS_NULL_PTR == pstLogAmpSmpAttrib)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_LogAmpSmpNegAttribInfoInd: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstLogAmpSmpAttrib, sizeof(CNAS_HSM_LOG_MNTN_AMP_SMP_NEG_ATTRIB_IND_STRU), 0x00, sizeof(CNAS_HSM_LOG_MNTN_AMP_SMP_NEG_ATTRIB_IND_STRU));

    CNAS_CFG_MSG_HDR(pstLogAmpSmpAttrib,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_LOG_AMP_SMP_NEG_ATTRS_INFO_IND,
                     (sizeof(CNAS_HSM_LOG_MNTN_AMP_SMP_NEG_ATTRIB_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    NAS_MEM_CPY_S(&(pstLogAmpSmpAttrib->stAmpNegAttrib),
                  sizeof(pstLogAmpSmpAttrib->stAmpNegAttrib),
                  pstAmpNegAttrib,
                  sizeof(CNAS_HSM_AMP_NEG_ATTRIB_STRU));

    NAS_MEM_CPY_S(&(pstLogAmpSmpAttrib->stSmpNegAttrib),
                  sizeof(pstLogAmpSmpAttrib->stSmpNegAttrib),
                  pstSmpNegAttrib,
                  sizeof(CNAS_HSM_SMP_NEG_ATTRIB_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_LOG_MNTN_AMP_SMP_NEG_ATTRIB_IND_STRU),
                          (VOS_VOID *)pstLogAmpSmpAttrib);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogAmpSmpAttrib);

    return;
}


VOS_VOID  CNAS_HSM_LogKeepAliveReq(
    CNAS_HSM_KEEP_ALIVE_REQ_MSG_STRU                       *pstKeepAliveReq
)
{
    CNAS_HSM_LOG_MNTN_KEEP_ALIVE_REQ_MSG_STRU              *pstLogMsg;

    pstLogMsg = (CNAS_HSM_LOG_MNTN_KEEP_ALIVE_REQ_MSG_STRU *)
                   PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_MNTN_KEEP_ALIVE_REQ_MSG_STRU));

    if (VOS_NULL_PTR == pstLogMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstLogMsg, sizeof(CNAS_HSM_LOG_MNTN_KEEP_ALIVE_REQ_MSG_STRU), 0, sizeof(CNAS_HSM_LOG_MNTN_KEEP_ALIVE_REQ_MSG_STRU));
    CNAS_CFG_MSG_HDR(pstLogMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_MSG_TYPE_KEEP_ALIVE_REQ,
                     (sizeof(CNAS_HSM_LOG_MNTN_KEEP_ALIVE_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    pstLogMsg->stKeepAliveReq.ucTransId = pstKeepAliveReq->ucTransId;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_LOG_MNTN_KEEP_ALIVE_REQ_MSG_STRU),
                          (VOS_VOID *)pstLogMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogMsg);

    return;
}




VOS_VOID  CNAS_HSM_LogKeepAliveResp(
    CNAS_HSM_KEEP_ALIVE_RESP_MSG_STRU                      *pstKeepAliveResp
)
{
    CNAS_HSM_LOG_MNTN_KEEP_ALIVE_RESP_MSG_STRU             *pstLogMsg;

    pstLogMsg = (CNAS_HSM_LOG_MNTN_KEEP_ALIVE_RESP_MSG_STRU *)
                   PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_MNTN_KEEP_ALIVE_RESP_MSG_STRU));

    if (VOS_NULL_PTR == pstLogMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstLogMsg, sizeof(CNAS_HSM_LOG_MNTN_KEEP_ALIVE_RESP_MSG_STRU), 0, sizeof(CNAS_HSM_LOG_MNTN_KEEP_ALIVE_RESP_MSG_STRU));
    CNAS_CFG_MSG_HDR(pstLogMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_MSG_TYPE_KEEP_ALIVE_RESP,
                     (sizeof(CNAS_HSM_LOG_MNTN_KEEP_ALIVE_RESP_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    pstLogMsg->stKeepAliveResp.ucTransId = pstKeepAliveResp->ucTransId;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_LOG_MNTN_KEEP_ALIVE_RESP_MSG_STRU),
                          (VOS_VOID *)pstLogMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogMsg);

    return;
}



VOS_VOID  CNAS_HSM_LogSessionDeactInfo(
    CNAS_HSM_SESSION_DEACT_INFO_STRU                       *pstSessionDeactInfo
)
{
    CNAS_HSM_MNTN_LOG_SESSION_DEACT_INFO_STRU              *pstLogMsg;

    pstLogMsg = (CNAS_HSM_MNTN_LOG_SESSION_DEACT_INFO_STRU *)
                   PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_MNTN_LOG_SESSION_DEACT_INFO_STRU));

    if (VOS_NULL_PTR == pstLogMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstLogMsg, sizeof(CNAS_HSM_MNTN_LOG_SESSION_DEACT_INFO_STRU), 0, sizeof(CNAS_HSM_MNTN_LOG_SESSION_DEACT_INFO_STRU));

    CNAS_CFG_MSG_HDR(pstLogMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_LOG_SESSION_DEACT_INFO_IND,
                     (sizeof(CNAS_HSM_MNTN_LOG_SESSION_DEACT_INFO_STRU) - VOS_MSG_HEAD_LENGTH));

    NAS_MEM_CPY_S(&(pstLogMsg->stSessionDeactInfo),
                  sizeof(pstLogMsg->stSessionDeactInfo),
                  pstSessionDeactInfo,
                  sizeof(CNAS_HSM_SESSION_DEACT_INFO_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_MNTN_LOG_SESSION_DEACT_INFO_STRU),
                          (VOS_VOID *)pstLogMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogMsg);
}


VOS_VOID  CNAS_HSM_LogReceiveATIListInfo(
    CNAS_HSM_ATI_LIST_INFO_STRU                            *pstCurrRcvATIList
)
{
    CNAS_HSM_LOG_MNTN_RCV_ATI_LIST_INFO_STRU               *pstLogCurrRcvATIList;

    pstLogCurrRcvATIList = (CNAS_HSM_LOG_MNTN_RCV_ATI_LIST_INFO_STRU *)
                            PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_LOG_MNTN_RCV_ATI_LIST_INFO_STRU));

    if (VOS_NULL_PTR == pstLogCurrRcvATIList)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_LogReceiveATIListInfo: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstLogCurrRcvATIList, sizeof(CNAS_HSM_LOG_MNTN_RCV_ATI_LIST_INFO_STRU), 0x00, sizeof(CNAS_HSM_LOG_MNTN_RCV_ATI_LIST_INFO_STRU));

    CNAS_CFG_MSG_HDR(pstLogCurrRcvATIList,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_LOG_RCV_ATI_LIST_INFO_IND,
                     (sizeof(CNAS_HSM_LOG_MNTN_RCV_ATI_LIST_INFO_STRU) - VOS_MSG_HEAD_LENGTH));

    pstLogCurrRcvATIList->ulATIRecordNum = pstCurrRcvATIList->ulATIRecordNum;

    NAS_MEM_CPY_S(pstLogCurrRcvATIList->astATIEntry,
                  sizeof(pstLogCurrRcvATIList->astATIEntry),
                  pstCurrRcvATIList->astATIEntry,
                  sizeof(pstCurrRcvATIList->astATIEntry));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_LOG_MNTN_RCV_ATI_LIST_INFO_STRU),
                          (VOS_VOID *)pstLogCurrRcvATIList);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogCurrRcvATIList);

    return;
}



VOS_VOID  CNAS_HSM_LogSessionKeepAliveInfo(
    CNAS_HSM_KEEP_ALIVE_TIMER_SCENE_ENUM_UINT32             enKeepAliveTimerScene,
    VOS_UINT32                                              ulIsKeepAliveAfterProc,
    CNAS_HSM_KEEP_ALIVE_CTRL_CTX_STRU                      *pstKeepAliveCtrlCtxInfo
)
{
    CNAS_HSM_MNTN_LOG_SESSION_KEEP_ALIVE_INFO_IND_STRU     *pstLogMsg = VOS_NULL_PTR;

    pstLogMsg = (CNAS_HSM_MNTN_LOG_SESSION_KEEP_ALIVE_INFO_IND_STRU *)
                   PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_MNTN_LOG_SESSION_KEEP_ALIVE_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstLogMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstLogMsg, sizeof(CNAS_HSM_MNTN_LOG_SESSION_KEEP_ALIVE_INFO_IND_STRU), 0, sizeof(CNAS_HSM_MNTN_LOG_SESSION_KEEP_ALIVE_INFO_IND_STRU));

    CNAS_CFG_MSG_HDR(pstLogMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_LOG_SESSION_KEEP_ALIVE_INFO_IND,
                     (sizeof(CNAS_HSM_MNTN_LOG_SESSION_KEEP_ALIVE_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstLogMsg->ulIsKeepAliveAfterProc   = ulIsKeepAliveAfterProc;
    pstLogMsg->enKeepAliveTimerScene    = enKeepAliveTimerScene;
    pstLogMsg->ulSysTickFwdTrafChan     = pstKeepAliveCtrlCtxInfo->stKeepAliveTimerInfo.ulSysTickFwdTrafChan;
    pstLogMsg->ulOldSysTickFwdTrafChan  = pstKeepAliveCtrlCtxInfo->stKeepAliveTimerInfo.ulOldSysTickFwdTrafChan;
    pstLogMsg->ulKeepAliveTimerLen      = pstKeepAliveCtrlCtxInfo->stKeepAliveTimerInfo.ulKeepAliveTimerLen;
    pstLogMsg->ulTotalTimerRunCount     = pstKeepAliveCtrlCtxInfo->stKeepAliveTimerInfo.ulTotalTimerRunCount;
    pstLogMsg->ulTimerExpiredCount      = pstKeepAliveCtrlCtxInfo->stKeepAliveTimerInfo.ulTimerExpiredCount;
    pstLogMsg->ulReferenceSysTick       = pstKeepAliveCtrlCtxInfo->ulReferenceSysTick;
    pstLogMsg->ucKeepAliveReqSndCount   = pstKeepAliveCtrlCtxInfo->stKeepAliveTimerInfo.ucKeepAliveReqSndCount;
    pstLogMsg->ucIsKeepAliveInfoValid   = pstKeepAliveCtrlCtxInfo->stSessionKeepAliveInfo.ucIsKeepAliveInfoValid;
    pstLogMsg->usTsmpClose              = pstKeepAliveCtrlCtxInfo->stSessionKeepAliveInfo.usTsmpClose;
    pstLogMsg->ulTsmpCloseRemainTime    = pstKeepAliveCtrlCtxInfo->stSessionKeepAliveInfo.ulTsmpCloseRemainTime;
    pstLogMsg->ucKeepAliveReqTransId    = pstKeepAliveCtrlCtxInfo->ucKeepAliveReqTransId;


    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_MNTN_LOG_SESSION_KEEP_ALIVE_INFO_IND_STRU),
                          (VOS_VOID *)pstLogMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogMsg);

}


VOS_VOID CNAS_HSM_LogReadCardInfo(
    VOS_UINT32                          ulWaitCardReadCnfFlag
)
{
    CNAS_HSM_MNTN_LOG_READ_CARD_INFO_IND_STRU              *pstLogMsg = VOS_NULL_PTR;

    pstLogMsg = (CNAS_HSM_MNTN_LOG_READ_CARD_INFO_IND_STRU *)
                    PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_MNTN_LOG_READ_CARD_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstLogMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_LogWaitReadCardInfo: Mem Alloc Fail!");

        return;
    }

    NAS_MEM_SET_S(pstLogMsg, sizeof(CNAS_HSM_MNTN_LOG_READ_CARD_INFO_IND_STRU), 0x00, sizeof(CNAS_HSM_MNTN_LOG_READ_CARD_INFO_IND_STRU));

    CNAS_CFG_MSG_HDR(pstLogMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_LOG_READ_CARD_INFO_IND,
                     (sizeof(CNAS_HSM_MNTN_LOG_READ_CARD_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstLogMsg->ulWaitReadCardCnfFlag   = ulWaitCardReadCnfFlag;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_MNTN_LOG_READ_CARD_INFO_IND_STRU),
                          (VOS_VOID *)pstLogMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogMsg);
}


VOS_VOID CNAS_HSM_LogQuitSlaveStateInfo(
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8  enCurSessionStatus,
    VOS_UINT8                           ucIsFirstSysAcq
)
{
    CNAS_HSM_MNTN_LOG_QUIT_SLAVE_STATE_INFO_IND_STRU       *pstLogMsg = VOS_NULL_PTR;

    pstLogMsg = (CNAS_HSM_MNTN_LOG_QUIT_SLAVE_STATE_INFO_IND_STRU *)
                    PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_MNTN_LOG_QUIT_SLAVE_STATE_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstLogMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_LogQuitSlaveStateInfo: Mem Alloc Fail!");

        return;
    }

    NAS_MEM_SET_S(pstLogMsg, sizeof(CNAS_HSM_MNTN_LOG_QUIT_SLAVE_STATE_INFO_IND_STRU), 0x00, sizeof(CNAS_HSM_MNTN_LOG_QUIT_SLAVE_STATE_INFO_IND_STRU));

    CNAS_CFG_MSG_HDR(pstLogMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_LOG_QUIT_SLAVE_STATE_INFO_IND,
                     (sizeof(CNAS_HSM_MNTN_LOG_QUIT_SLAVE_STATE_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstLogMsg->enCurSessionStatus   = enCurSessionStatus;
    pstLogMsg->ucIsFirstSysAcq      = ucIsFirstSysAcq;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_MNTN_LOG_QUIT_SLAVE_STATE_INFO_IND_STRU),
                          (VOS_VOID *)pstLogMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogMsg);
}

/*****************************************************************************
Function Name   :   CNAS_HSM_LogSessionRecoveryJudgeInfo
Description     :   Log session recovery judge related info
Input parameters:   ucCardChangedFlg   ------- is card changed
                    ucIsSessionExpired ------- is Session expired
Output parameters:  None
Return Value    :   VOS_VOID

Modify History  :
1)  Date           : 2015-09-22
    Author         : t00323010
    Modify content : HSM MNTN(DTS2015092201636): Create
2)  Date           : 2015-10-10
    Author         : w00351686
    Modification   : HSM MNTN(DTS2015092201636): Modified the structure name
3. Date            : 2015-10-13
   Author          : y00307564
   Modification    : DTS2015082403731: 增加换卡逻辑新增的ESN_MEID_ME和ppp an鉴权信息
4. Date            : 2015-12-22
   Author          : m00312079
   Modification    : DTS2015120208895: 增加UE的版本信息
*****************************************************************************/
VOS_VOID CNAS_HSM_LogSessionRecoveryJudgeInfo(
    VOS_UINT8                           ucCardChangedFlg,
    VOS_UINT32                          ulIsSessionExpired
)
{
    CNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND_STRU *pstLogMsg = VOS_NULL_PTR;

    pstLogMsg = (CNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND_STRU *)
                    PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstLogMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_LogRecoveryJudgeInfo: Mem Alloc Fail!");

        return;
    }

    NAS_MEM_SET_S(pstLogMsg, sizeof(CNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND_STRU), 0x00, sizeof(CNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND_STRU));

    CNAS_CFG_MSG_HDR(pstLogMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND,
                     (sizeof(CNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstLogMsg->enLastSessionStatus      = CNAS_HSM_GetLastHrpdSessionStatus();
    pstLogMsg->ucIsKeepAliveInfoValid   = CNAS_HSM_GetKeepAliveInfoValidFlag();
    pstLogMsg->ucCardChangedFlg         = ucCardChangedFlg;
    pstLogMsg->enLastSessionType        = CNAS_HSM_GetLastSessionType();
    pstLogMsg->ulIsSupportEhrpd         = CNAS_HSM_IsCurrentCapSupportEhrpd();
    pstLogMsg->ulIsSessionExpired       = ulIsSessionExpired;
    pstLogMsg->ulTsmpCloseRemainTime    = CNAS_HSM_GetTsmpCloseRemainTime();

    NAS_MEM_CPY_S(pstLogMsg->aucLastIccid,
                  sizeof(pstLogMsg->aucLastIccid),
                  CNAS_HSM_GetLastIccIdAddr(),
                  CNAS_HSM_ICCID_OCTET_NUM);

    NAS_MEM_CPY_S(pstLogMsg->aucCurIccid,
                  sizeof(pstLogMsg->aucCurIccid),
                  CNAS_CCB_GetCardIccIdAddr(),
                  CNAS_HSM_ICCID_OCTET_NUM);

    NAS_MEM_CPY_S(&pstLogMsg->stLastHwid,
                  sizeof(pstLogMsg->stLastHwid),
                  CNAS_HSM_GetLastSessionHwidCtxAddr(),
                  sizeof(CNAS_HSM_HARDWARE_ID_INFO_STRU));

    NAS_MEM_CPY_S(&pstLogMsg->stCurHwid,
                  sizeof(pstLogMsg->stCurHwid),
                  CNAS_HSM_GetHardwareIdInfo(),
                  sizeof(CNAS_HSM_HARDWARE_ID_INFO_STRU));

    NAS_MEM_CPY_S(pstLogMsg->aulLastPowerOffSysTime,
                  sizeof(pstLogMsg->aulLastPowerOffSysTime),
                  CNAS_HSM_GetLastPowerOffSysTime(),
                  sizeof(pstLogMsg->aulLastPowerOffSysTime));

    NAS_MEM_CPY_S(pstLogMsg->aulReceivedSysTime,
                  sizeof(pstLogMsg->aulReceivedSysTime),
                  CNAS_HSM_GetLastReceivedSysTime(),
                  sizeof(pstLogMsg->aulReceivedSysTime));

    NAS_MEM_CPY_S(&(pstLogMsg->stCardStatus),
                  sizeof(pstLogMsg->stCardStatus),
                  CNAS_HSM_GetCardStatusChangeInfoAddr(),
                  sizeof(pstLogMsg->stCardStatus));

    NAS_MEM_CPY_S(&(pstLogMsg->stStoreEsnMeidRslt),
                  sizeof(pstLogMsg->stStoreEsnMeidRslt),
                  CNAS_HSM_GetStoreEsnMeidRsltAddr(),
                  sizeof(pstLogMsg->stStoreEsnMeidRslt));

    NAS_MEM_CPY_S(&(pstLogMsg->stCurEsnMeidMe),
                  sizeof(pstLogMsg->stCurEsnMeidMe),
                  CNAS_CCB_GetEsnMeidMeInfoAddr(),
                  sizeof(pstLogMsg->stCurEsnMeidMe));

    NAS_MEM_CPY_S(&(pstLogMsg->stCurAccessAuthInfo),
                  sizeof(pstLogMsg->stCurAccessAuthInfo),
                  CNAS_CCB_GetHrpdAccesAuthInfoAddr(),
                  sizeof(pstLogMsg->stCurAccessAuthInfo));

    NAS_MEM_CPY_S(&(pstLogMsg->stlastAccessAuthInfo),
                  sizeof(pstLogMsg->stlastAccessAuthInfo),
                  CNAS_HSM_GetLastHrpdAccessAuthInfoCtxAddr(),
                  sizeof(pstLogMsg->stlastAccessAuthInfo));

    NAS_MEM_CPY_S(&(pstLogMsg->stLastUERevInfo),
                  sizeof(pstLogMsg->stLastUERevInfo),
                  CNAS_HSM_GetLastHrpdUERevInfoCtxAddr(),
                  sizeof(CNAS_NVIM_HRPD_UE_REV_INFO_STRU));

    NAS_MEM_CPY_S(&(pstLogMsg->stCurUERevInfo),
                  sizeof(pstLogMsg->stCurUERevInfo),
                  CNAS_HSM_GetHrpdUERevInfoCtxAddr(),
                  sizeof(CNAS_NVIM_HRPD_UE_REV_INFO_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_MNTN_LOG_SESSION_RECOVERY_JUDGE_INFO_IND_STRU),
                          (VOS_VOID *)pstLogMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogMsg);
}


VOS_VOID CNAS_HSM_LogSessionOperateCtrlInfo(VOS_VOID)
{
    CNAS_HSM_MNTN_LOG_SESSION_OPERATE_CTRL_INFO_IND_STRU   *pstLogMsg = VOS_NULL_PTR;

    pstLogMsg = (CNAS_HSM_MNTN_LOG_SESSION_OPERATE_CTRL_INFO_IND_STRU *)
                    PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_MNTN_LOG_SESSION_OPERATE_CTRL_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstLogMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_LogSessionOperateCtrlInfo: Mem Alloc Fail!");

        return;
    }

    NAS_MEM_SET_S(pstLogMsg, sizeof(CNAS_HSM_MNTN_LOG_SESSION_OPERATE_CTRL_INFO_IND_STRU), 0x00, sizeof(CNAS_HSM_MNTN_LOG_SESSION_OPERATE_CTRL_INFO_IND_STRU));

    CNAS_CFG_MSG_HDR(pstLogMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_LOG_SESSION_OPERATE_CTRL_INFO_IND,
                     (sizeof(CNAS_HSM_MNTN_LOG_SESSION_OPERATE_CTRL_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    NAS_MEM_CPY_S(&pstLogMsg->stSessionCtrlInfo,
                  sizeof(pstLogMsg->stSessionCtrlInfo),
                  CNAS_HSM_GetSessionCtrlInfoAddr(),
                  sizeof(CNAS_HSM_SESSION_CTRL_STRU));

    NAS_MEM_CPY_S(&pstLogMsg->stHrpdAmpNegAttibInfo,
                  sizeof(pstLogMsg->stHrpdAmpNegAttibInfo),
                  CNAS_HSM_GetHrpdAmpNegAttribAddr(),
                  sizeof(CNAS_HSM_HRPD_AMP_NEG_ATTRIB_STRU));


    NAS_MEM_CPY_S(&pstLogMsg->stMultiModeCtrlInfo,
                  sizeof(pstLogMsg->stMultiModeCtrlInfo),
                  &CNAS_HSM_GetHsmCtxAddr()->stMultiModeCtrlInfo,
                  sizeof(CNAS_HSM_MULTI_MODE_CTRL_INFO_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_MNTN_LOG_SESSION_OPERATE_CTRL_INFO_IND_STRU),
                          (VOS_VOID *)pstLogMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogMsg);
}


VOS_VOID CNAS_HSM_LogConnMnmtStatusInfo(VOS_VOID)
{
    CNAS_HSM_MNTN_LOG_CONN_MNMT_STATUS_INFO_IND_STRU       *pstLogMsg = VOS_NULL_PTR;

    pstLogMsg = (CNAS_HSM_MNTN_LOG_CONN_MNMT_STATUS_INFO_IND_STRU *)
                    PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_MNTN_LOG_CONN_MNMT_STATUS_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstLogMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_LogConnMnmtStatusInfo: Mem Alloc Fail!");

        return;
    }

    NAS_MEM_SET_S(pstLogMsg, sizeof(CNAS_HSM_MNTN_LOG_CONN_MNMT_STATUS_INFO_IND_STRU), 0x00, sizeof(CNAS_HSM_MNTN_LOG_CONN_MNMT_STATUS_INFO_IND_STRU));

    CNAS_CFG_MSG_HDR(pstLogMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_LOG_CONN_MNMT_STATUS_INFO_IND,
                     (sizeof(CNAS_HSM_MNTN_LOG_CONN_MNMT_STATUS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstLogMsg->enSessionStatus          = CNAS_HSM_GetSessionStatus();
    pstLogMsg->enSessionType            = CNAS_HSM_GetNegoSessionType();
    pstLogMsg->enConnStatus             = CNAS_HSM_GetConnStatus();
    pstLogMsg->enMainState              = CNAS_HSM_GetCurrMainState();
    pstLogMsg->enSubState               = CNAS_HSM_GetCurrSubState();
    pstLogMsg->enCovertedCasStatus      = CNAS_HSM_GetHrpdConvertedCasStatus();
    pstLogMsg->enOriginalCasStatus      = CNAS_HSM_GetHrpdOriginalCasStatus();

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_MNTN_LOG_CONN_MNMT_STATUS_INFO_IND_STRU),
                          (VOS_VOID *)pstLogMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogMsg);
}


VOS_VOID CNAS_HSM_LogDiscardMsgInfo(
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_SCENE_ENUM_UINT8          enDiscardMsgScene,
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_REASON_UNION             *punDiscardMsgReason
)
{
    CNAS_HSM_MNTN_LOG_DISCARD_MSG_INFO_IND_STRU            *pstLogMsg = VOS_NULL_PTR;

    pstLogMsg = (CNAS_HSM_MNTN_LOG_DISCARD_MSG_INFO_IND_STRU *)
                    PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_MNTN_LOG_DISCARD_MSG_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstLogMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_LogDiscardMsgInfo: Mem Alloc Fail!");

        return;
    }

    NAS_MEM_SET_S(pstLogMsg, sizeof(CNAS_HSM_MNTN_LOG_DISCARD_MSG_INFO_IND_STRU), 0x00, sizeof(CNAS_HSM_MNTN_LOG_DISCARD_MSG_INFO_IND_STRU));

    CNAS_CFG_MSG_HDR(pstLogMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_LOG_DISCARD_MSG_INFO_IND,
                     (sizeof(CNAS_HSM_MNTN_LOG_DISCARD_MSG_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstLogMsg->enDiscardMsgScene    = enDiscardMsgScene;

    if (VOS_NULL_PTR != punDiscardMsgReason)
    {
        NAS_MEM_CPY_S(&pstLogMsg->unDiscardMsgReason,
                      sizeof(pstLogMsg->unDiscardMsgReason),
                      punDiscardMsgReason,
                      sizeof(CNAS_HSM_MNTN_LOG_DISCARD_MSG_REASON_UNION));
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_MNTN_LOG_DISCARD_MSG_INFO_IND_STRU),
                          (VOS_VOID *)pstLogMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogMsg);
}


VOS_VOID CNAS_HSM_LogBuffQueueFullInd(VOS_VOID)
{
    CNAS_HSM_MNTN_LOG_BUFF_MSG_QUEUE_FULL_IND_STRU         *pstLogMsg = VOS_NULL_PTR;

    pstLogMsg = (CNAS_HSM_MNTN_LOG_BUFF_MSG_QUEUE_FULL_IND_STRU *)
                    PS_MEM_ALLOC(UEPS_PID_HSM, sizeof(CNAS_HSM_MNTN_LOG_BUFF_MSG_QUEUE_FULL_IND_STRU));

    if (VOS_NULL_PTR == pstLogMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_LogBuffMsgQueueFullInd: Mem Alloc Fail!");

        return;
    }

    NAS_MEM_SET_S(pstLogMsg, sizeof(CNAS_HSM_MNTN_LOG_BUFF_MSG_QUEUE_FULL_IND_STRU), 0x00, sizeof(CNAS_HSM_MNTN_LOG_BUFF_MSG_QUEUE_FULL_IND_STRU));

    CNAS_CFG_MSG_HDR(pstLogMsg,
                     UEPS_PID_HSM,
                     UEPS_PID_HSM,
                     ID_CNAS_HSM_MNTN_LOG_BUFF_MSG_QUEUE_FULL_IND,
                     (sizeof(CNAS_HSM_MNTN_LOG_BUFF_MSG_QUEUE_FULL_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSM,
                          sizeof(CNAS_HSM_MNTN_LOG_BUFF_MSG_QUEUE_FULL_IND_STRU),
                          (VOS_VOID *)pstLogMsg);

    PS_MEM_FREE(UEPS_PID_HSM, pstLogMsg);
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





