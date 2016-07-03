

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "CnasXccSndInternalMsg.h"
#include  "CnasXccCtx.h"
#include  "PsCommonDef.h"
#include  "CnasMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_SND_INTERNAL_MSG_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 -e429 -e830 */

VOS_VOID CNAS_XCC_SndMoCallingRslt(
    VOS_UINT8                                               ucConnId,
    CNAS_XCC_MO_CALLING_RESULT_ENUM_UINT32                  enRslt,
    CNAS_XCC_MO_CALLING_END_REASON_ENUM_UINT8               enEndReason
)
{
    CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg  = PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XCC;
    pstMsg->enMsgId                     = ID_CNAS_XCC_XCC_MO_CALLING_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enRslt                      = enRslt;
    pstMsg->ucConnectId                 = ucConnId;
    pstMsg->enEndReason                 = enEndReason;


    /* 放消息进内部队列 */
    CNAS_XCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}



VOS_VOID CNAS_XCC_SndMtCallingRslt(
    VOS_UINT8                                               ucConnId,
    CNAS_XCC_MT_CALLING_RESULT_ENUM_UINT32                  enRslt,
    CNAS_XCC_MT_CALLING_END_REASON_ENUM_UINT8               enEndReason
)
{
    CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg  = PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XCC;
    pstMsg->enMsgId                     = ID_CNAS_XCC_XCC_MT_CALLING_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucConnectId                 = ucConnId;
    pstMsg->enRslt                      = enRslt;
    pstMsg->enEndReason                 = enEndReason;

    /* 放消息进内部队列 */
    CNAS_XCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}


VOS_VOID CNAS_XCC_SndXccAbortReq(
    VOS_UINT8                           ucConnId,
    VOS_UINT32                          ulEventType,
    TAF_XCC_CAUSE_ENUM_UINT32           enAbortCause
)
{
    CNAS_XCC_XCC_ABORT_REQ_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg  = PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_XCC_ABORT_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XCC;
    pstMsg->enMsgId                     = ID_CNAS_XCC_XCC_ABORT_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XCC_XCC_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucConnectId                 = ucConnId;
    pstMsg->ulEventType                 = ulEventType;

    pstMsg->enAbortCause                = enAbortCause;

    /* 放消息进内部队列 */
    CNAS_XCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}


VOS_VOID CNAS_XCC_SndXccPowerDownInd(
    VOS_UINT8                           ucConnId
)
{
    CNAS_XCC_XCC_POWER_DOWN_IND_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_XCC_XCC_POWER_DOWN_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC,
                                                               sizeof(CNAS_XCC_XCC_POWER_DOWN_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XCC;
    pstMsg->enMsgId                     = ID_CNAS_XCC_XCC_POWER_DOWN_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XCC_XCC_POWER_DOWN_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucConnectId                 = ucConnId;

    /* 放消息进内部队列 */
    CNAS_XCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}


VOS_VOID CNAS_XCC_SndXccNdssRedialInd(
    VOS_UINT8                           ucConnId
)
{
    CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC,
                                                               sizeof(CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XCC;
    pstMsg->ulLength                    = sizeof(CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_CNAS_XCC_XCC_NDSS_REDIAL_IND;
    pstMsg->usOpId                      = 0;

    pstMsg->ucConnectId                 = ucConnId;
    pstMsg->aucReserved[0]              = 0;
    pstMsg->aucReserved[1]              = 0;
    pstMsg->aucReserved[2]              = 0;


    /* 放消息进内部队列 */
    CNAS_XCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}


VOS_VOID CNAS_XCC_SndXcc1xCallStateUpdateInd(
    VOS_VOID
)
{
    CNAS_XCC_XCC_CALL_STATE_IND_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_XCC_XCC_CALL_STATE_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC,
                                                               sizeof(CNAS_XCC_XCC_CALL_STATE_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* 填充消息 */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XCC;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XCC;
    pstMsg->ulLength                    = sizeof(CNAS_XCC_XCC_CALL_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId                     = ID_CNAS_XCC_XCC_CALL_STATE_IND;
    pstMsg->usOpId                      = 0;

    /* 放消息进内部队列 */
    CNAS_XCC_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}

/*lint -restore*/

#endif









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
