

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXsmsSndCas.h"
#include "TafXsmsMsgProc.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_SND_CAS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/


VOS_UINT32 TAF_XSMS_SndCasCschDataReq(VOS_UINT8 ucMsgSeqNum, VOS_UINT8 *paucData, TAF_XSMS_DATA_BURST_MSG_STRU *pstDbm)
{
    CNAS_CAS_1X_CSCH_DATA_REQ_STRU     *pstCschDataReq;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec       = TAF_XSMS_MtGetRecAddr();

    pstCschDataReq = (CNAS_CAS_1X_CSCH_DATA_REQ_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                                    ((sizeof(CNAS_CAS_1X_CSCH_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH)
                                                                    + pstDbm->ucNumFields));

    if (VOS_NULL_PTR == pstCschDataReq)
    {
        return VOS_ERR;
    }

    VOS_MemSet(pstCschDataReq, 0, sizeof(CNAS_CAS_1X_CSCH_DATA_REQ_STRU) + pstDbm->ucNumFields);

    /* 将Dbm转换成发给CAS的BIT流 */
    if (VOS_OK != TAF_XSMS_TransDbmToCSCHData(pstDbm, pstCschDataReq))
    {
        VOS_FreeMsg(UEPS_PID_XSMS, pstCschDataReq);

        return VOS_ERR;
    }

    pstCschDataReq->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstCschDataReq->ulSenderPid         = UEPS_PID_XSMS;
    pstCschDataReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstCschDataReq->ulReceiverPid       = UEPS_PID_1XCASM;
    pstCschDataReq->ulLength            = sizeof(CNAS_CAS_1X_CSCH_DATA_REQ_STRU) + pstDbm->ucNumFields - VOS_MSG_HEAD_LENGTH;


    pstCschDataReq->enMsgId             = ID_CNAS_CAS_1X_CSCH_DATA_REQ;
    pstCschDataReq->usOpId              = 0;
    pstCschDataReq->ucMsgSeqNum         = ucMsgSeqNum;
    pstCschDataReq->enTxCschMsgType     = CAS_CNAS_1X_TX_COMMON_DATA_BURST_MSG;
    pstCschDataReq->enAckReqFlag        = pstMtRec->enIsCasAckFlag;
    pstCschDataReq->enDataBurstType     = CNAS_1X_SMS_DATA_BURST_TYPE;

    /* 根据是不是需要給网侧回复，判断是REQ还是RESPONSE */
    if (VOS_TRUE == pstMtRec->enIsCasAckFlag)
    {
        pstCschDataReq->enMsgDataType   = CAS_CNAS_1X_DATA_TYPE_RESPONSE;
    }
    else
    {
        pstCschDataReq->enMsgDataType   = CAS_CNAS_1X_DATA_TYPE_REQUEST;
    }

    pstMtRec->enIsCasAckFlag            = VOS_FALSE;

    PS_MEM_CPY(pstCschDataReq->aucAckPara, pstMtRec->aucCasAckData, 2);

    PS_MEM_CPY(pstCschDataReq->aucAuthDigit, paucData, 3);

    return VOS_SendMsg(UEPS_PID_XSMS, pstCschDataReq);
}



VOS_UINT32 TAF_XSMS_SndCasCschOrderMsg
(
    VOS_UINT8                           ucMsgSeqNum,
    PS_BOOL_ENUM_UINT8                  enIsCasAckFlag,
    VOS_UINT8                          *paucCasAckData
)
{
    CNAS_CAS_1X_CSCH_DATA_REQ_STRU     *pstCschDataReq;

    pstCschDataReq = (CNAS_CAS_1X_CSCH_DATA_REQ_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                                    (sizeof(CNAS_CAS_1X_CSCH_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstCschDataReq)
    {
        return VOS_ERR;
    }

    VOS_MemSet(pstCschDataReq, 0, sizeof(CNAS_CAS_1X_CSCH_DATA_REQ_STRU));

    if (VOS_ERR == TAF_XSMS_EncodeCschOrderMsg(pstCschDataReq))
    {

        TAF_XSMS_INFO_LOG("TAF_XSMS_SndCasCschOrderMsg: Encode Order msg error");

        VOS_FreeMsg(UEPS_PID_XSMS, pstCschDataReq);

        return VOS_ERR;
    }

    pstCschDataReq->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstCschDataReq->ulSenderPid         = UEPS_PID_XSMS;
    pstCschDataReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstCschDataReq->ulReceiverPid       = UEPS_PID_1XCASM;
    pstCschDataReq->ulLength            = sizeof(CNAS_CAS_1X_CSCH_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;


    pstCschDataReq->enMsgId             = ID_CNAS_CAS_1X_CSCH_DATA_REQ;
    pstCschDataReq->usOpId              = 0;
    pstCschDataReq->ucMsgSeqNum         = ucMsgSeqNum;
    pstCschDataReq->enTxCschMsgType     = CAS_CNAS_1X_TX_COMMON_ORDER_MSG;
    pstCschDataReq->enAckReqFlag        = enIsCasAckFlag;
    pstCschDataReq->enMsgDataType       = CAS_CNAS_1X_DATA_TYPE_RESPONSE;

    PS_MEM_CPY(pstCschDataReq->aucAckPara, paucCasAckData, 2);

    return VOS_SendMsg(UEPS_PID_XSMS, pstCschDataReq);
}

VOS_UINT32 TAF_XSMS_SndCasDschDataReq(VOS_UINT8 ucMsgSeqNum, TAF_XSMS_DATA_BURST_MSG_STRU *pstDbm)
{
    CNAS_CAS_1X_DSCH_DATA_REQ_STRU     *pstDschDataReq;
    VOS_UINT32                          MsgLength;

    pstDschDataReq = (CNAS_CAS_1X_DSCH_DATA_REQ_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                                    ((sizeof(CNAS_CAS_1X_DSCH_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH)
                                                                    + pstDbm->ucNumFields ));

    if (VOS_NULL_PTR == pstDschDataReq)
    {
        return VOS_ERR;
    }

    MsgLength = pstDschDataReq->ulLength;

    VOS_MemSet(pstDschDataReq, 0, sizeof(CNAS_CAS_1X_DSCH_DATA_REQ_STRU) + pstDbm->ucNumFields);

    /* 将Dbm转换成发给CAS的BIT流 */
    if (VOS_OK != TAF_XSMS_TransDbmToDSCHData(pstDbm, pstDschDataReq))
    {
        VOS_FreeMsg(UEPS_PID_XSMS, pstDschDataReq);

        return VOS_ERR;
    }

    pstDschDataReq->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstDschDataReq->ulSenderPid         = UEPS_PID_XSMS;
    pstDschDataReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDschDataReq->ulReceiverPid       = UEPS_PID_1XCASM;
    pstDschDataReq->ulLength            = MsgLength;



    pstDschDataReq->enMsgId             = ID_CNAS_CAS_1X_DSCH_DATA_REQ;
    pstDschDataReq->usOpId              = 0;
    pstDschDataReq->ucMsgSeqNum         = ucMsgSeqNum;
    pstDschDataReq->enTxDschMsgType     = CAS_CNAS_1X_TX_TCH_DATA_BURST_MSG;
    pstDschDataReq->enIsAmDataReq       = VOS_TRUE;

    return VOS_SendMsg(UEPS_PID_XSMS, pstDschDataReq);
}



VOS_VOID TAF_XSMS_SndCasBeginSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                        enSessionType
)
{
    CNAS_CAS_1X_SESSION_BEGIN_NTF_STRU                         *pstBeginSessionNotify = VOS_NULL_PTR;
    VOS_UINT32                                                  ulMsgLength;

    ulMsgLength                                                 = sizeof(CNAS_CAS_1X_SESSION_BEGIN_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstBeginSessionNotify = (CNAS_CAS_1X_SESSION_BEGIN_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_XSMS, ulMsgLength);

    if (VOS_NULL_PTR == pstBeginSessionNotify)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    pstBeginSessionNotify->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulSenderPid      = UEPS_PID_XSMS;
    pstBeginSessionNotify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulReceiverPid    = UEPS_PID_1XCASM;
    pstBeginSessionNotify->ulLength         = ulMsgLength;
    pstBeginSessionNotify->enMsgId          = ID_CNAS_CAS_1X_SESSION_BEGIN_NTF;
    pstBeginSessionNotify->usOpId           = 0x00;
    pstBeginSessionNotify->enSessionType    = enSessionType;

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstBeginSessionNotify);

    return;
}


VOS_VOID TAF_XSMS_SndCasEndSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType
)
{
    CNAS_CAS_1X_SESSION_END_NTF_STRU                       *pstEndSessionNotify = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength                                             = sizeof(CNAS_CAS_1X_SESSION_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstEndSessionNotify = (CNAS_CAS_1X_SESSION_END_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_XSMS, ulMsgLength);

    if (VOS_NULL_PTR == pstEndSessionNotify)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    pstEndSessionNotify->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulSenderPid        = UEPS_PID_XSMS;
    pstEndSessionNotify->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulReceiverPid      = UEPS_PID_1XCASM;
    pstEndSessionNotify->ulLength           = ulMsgLength;
    pstEndSessionNotify->enMsgId            = ID_CNAS_CAS_1X_SESSION_END_NTF;
    pstEndSessionNotify->usOpId             = 0x00;
    pstEndSessionNotify->enSessionType      = enSessionType;

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstEndSessionNotify);

    return;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



