

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "CnasHluSndAs.h"
#include "PsCommonDef.h"
#include "CnasMntn.h"
#include "Nas_Mem.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HLU_SND_AS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_VOID CNAS_HLU_SndCasBeginSessionNotify(
    CNAS_CAS_HRPD_SESSION_TYPE_ENUM_UINT16                  enSessionType
)
{
    CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU                   *pstBeginSessionNotify   = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength                                             = sizeof(CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstBeginSessionNotify = (CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HLU, ulMsgLength);

    if (VOS_NULL_PTR == pstBeginSessionNotify)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstBeginSessionNotify->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulSenderPid      = UEPS_PID_HLU;
    pstBeginSessionNotify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulReceiverPid    = UEPS_PID_HALMP;
    pstBeginSessionNotify->ulLength         = ulMsgLength;
    pstBeginSessionNotify->enMsgId          = ID_CNAS_CAS_HRPD_SESSION_BEGIN_NTF;
    pstBeginSessionNotify->usOpId           = 0x00;
    pstBeginSessionNotify->enSessionType    = enSessionType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstBeginSessionNotify);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HLU, pstBeginSessionNotify);

    return;
}


VOS_VOID CNAS_HLU_SndCasEndSessionNotify(
    CNAS_CAS_HRPD_SESSION_TYPE_ENUM_UINT16                  enSessionType
)
{
    CNAS_CAS_HRPD_SESSION_END_NTF_STRU                     *pstEndSessionNotify = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength                                             = sizeof(CNAS_CAS_HRPD_SESSION_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstEndSessionNotify = (CNAS_CAS_HRPD_SESSION_END_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HLU, ulMsgLength);

    if (VOS_NULL_PTR == pstEndSessionNotify)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8 *)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstEndSessionNotify->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulSenderPid       = UEPS_PID_HLU;
    pstEndSessionNotify->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulReceiverPid     = UEPS_PID_HALMP;
    pstEndSessionNotify->ulLength          = ulMsgLength;
    pstEndSessionNotify->enMsgId           = ID_CNAS_CAS_HRPD_SESSION_END_NTF;
    pstEndSessionNotify->usOpId            = 0x00;
    pstEndSessionNotify->enSessionType     = enSessionType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstEndSessionNotify);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HLU, pstEndSessionNotify);

    return;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



