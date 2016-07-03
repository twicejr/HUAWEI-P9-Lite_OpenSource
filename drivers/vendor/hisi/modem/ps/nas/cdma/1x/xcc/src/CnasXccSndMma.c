

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXccSndMma.h"
#include  "CnasCcb.h"
#include  "CnasMntn.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_SND_MMA_C


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/


VOS_VOID CNAS_XCC_SndMma1XCallState(
    XCC_MMA_1X_CALL_STATE_ENUM_UINT8    enCallState
)
{
    XCC_MMA_1X_CALL_STATE_IND_STRU     *pstCallStateInd = VOS_NULL_PTR;

    /* 分配消息 */
    pstCallStateInd  = (XCC_MMA_1X_CALL_STATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_MMA_1X_CALL_STATE_IND_STRU));

    if (VOS_NULL_PTR == pstCallStateInd)
    {
        return;
    }

    /* 清空消息内容 */
    NAS_MEM_SET_S((VOS_UINT8 *)pstCallStateInd + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_MMA_1X_CALL_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_MMA_1X_CALL_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    /* 填充消息 */
    pstCallStateInd->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstCallStateInd->ulSenderPid      = UEPS_PID_XCC;
    pstCallStateInd->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstCallStateInd->ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_MMA);
    pstCallStateInd->ulLength         = sizeof(XCC_MMA_1X_CALL_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCallStateInd->enMsgId          = ID_XCC_MMA_1X_CALL_STATE_IND;
    pstCallStateInd->enCallState      = enCallState;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCallStateInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstCallStateInd);
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




