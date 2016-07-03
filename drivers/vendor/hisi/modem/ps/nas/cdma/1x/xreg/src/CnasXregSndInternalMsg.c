

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXregSndInternalMsg.h"
#include  "CnasXregProcess.h"
#include  "CnasMain.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_SND_INTERNAL_MSG_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/


VOS_VOID CNAS_XREG_SndRegReqMsg(CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8 enRegType)
{
    CNAS_XREG_XREG_REG_REQ_STRU        *pstInternalMsg = VOS_NULL_PTR;

    pstInternalMsg  = (CNAS_XREG_XREG_REG_REQ_STRU*)CNAS_GetIntMsgSendBuf(UEPS_PID_XREG,
                                                        sizeof(CNAS_XREG_XREG_REG_REQ_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = UEPS_PID_XREG;

    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = UEPS_PID_XREG;

    pstInternalMsg->ulLength
        = sizeof(CNAS_XREG_XREG_REG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->enMsgId         = ID_CNAS_XREG_XREG_REG_REQ;
    pstInternalMsg->usOpId          = 0;
    pstInternalMsg->enRegType       = enRegType;

    CNAS_SndInternalMsg(pstInternalMsg);

    return;
}


VOS_VOID CNAS_XREG_SndRegCnfMsg(CNAS_XREG_REG_RESULT_ENUM_UINT32 enRegResult,
                                            CNAS_XREG_REGING_STA_ENUM_UINT32 enRegingSta,
                                            CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8 enRegType)
{
    CNAS_XREG_XREG_REG_CNF_STRU        *pstInternalMsg = VOS_NULL_PTR;

    pstInternalMsg  = (CNAS_XREG_XREG_REG_CNF_STRU*)CNAS_GetIntMsgSendBuf(UEPS_PID_XREG,
                                                        sizeof(CNAS_XREG_XREG_REG_CNF_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = UEPS_PID_XREG;

    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = UEPS_PID_XREG;

    pstInternalMsg->ulLength
        = sizeof(CNAS_XREG_XREG_REG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->enMsgId         = ID_CNAS_XREG_XREG_REG_CNF;
    pstInternalMsg->usOpId          = 0;

    pstInternalMsg->enRegResult     = enRegResult;
    pstInternalMsg->enRegingSta     = enRegingSta;
    pstInternalMsg->enRegType       = enRegType;

    CNAS_SndInternalMsg(pstInternalMsg);

    return;
}


VOS_VOID CNAS_XREG_SndAbortFsmMsg(VOS_VOID)
{
    CNAS_XREG_XREG_ABORT_FSM_STRU      *pstInternalMsg = VOS_NULL_PTR;

    pstInternalMsg  = (CNAS_XREG_XREG_ABORT_FSM_STRU*)CNAS_GetIntMsgSendBuf(UEPS_PID_XREG,
                                                        sizeof(CNAS_XREG_XREG_ABORT_FSM_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = UEPS_PID_XREG;

    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = UEPS_PID_XREG;

    pstInternalMsg->ulLength
        = sizeof(CNAS_XREG_XREG_ABORT_FSM_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->enMsgId         = ID_CNAS_XREG_ABORT_FSM_REQ;
    pstInternalMsg->usOpId          = 0;

    CNAS_SndInternalMsg(pstInternalMsg);

    return;
}


VOS_VOID CNAS_XREG_SndSwitchOnRlst(
    VOS_UINT32                          ulResult
)
{
    CNAS_XREG_XREG_SWITCH_ON_RSLT_CNF_STRU     *pstInternalMsg = VOS_NULL_PTR;

    pstInternalMsg  = (CNAS_XREG_XREG_SWITCH_ON_RSLT_CNF_STRU*)CNAS_GetIntMsgSendBuf(UEPS_PID_XREG,
                                                        sizeof(CNAS_XREG_XREG_SWITCH_ON_RSLT_CNF_STRU));

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid                 = UEPS_PID_XREG;
    pstInternalMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid               = UEPS_PID_XREG;
    pstInternalMsg->enMsgId                     = ID_CNAS_XREG_XREG_SWITCH_ON_RSLT_CNF;
    pstInternalMsg->usOpId                      = 0;
    pstInternalMsg->ulLength                    = sizeof(CNAS_XREG_XREG_SWITCH_ON_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->enRslt                      = ulResult;

    CNAS_SndInternalMsg((VOS_UINT8 *)pstInternalMsg);

    return;
}

/*lint -restore*/
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
