
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMmcSndGmm.h"
#include "NasComm.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmlMsgProc.h"
#include "MmcMmInterface.h"
#include "MmcGmmInterface.h"
#include "NasMmcProcRegRslt.h"
#include "MM_Share.h"
#include "NasMmcComFunc.h"
#include "NVIM_Interface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_GMM_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/
/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */


VOS_VOID NAS_MMC_SndGmmStartReq(VOS_VOID)
{
    MMCGMM_START_REQ_STRU              *pstMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg  = (MMCGMM_START_REQ_STRU*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_START_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息名称 */
    pstMsg->MsgHeader.ulMsgName         = MMCGMM_START_REQ;

    NAS_MML_SndInternalMsg(pstMsg);
}




VOS_VOID NAS_MMC_SndGmmPowerOffReq(VOS_VOID)
{
    MMCGMM_POWER_OFF_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg  = (MMCGMM_POWER_OFF_REQ_STRU*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_POWER_OFF_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息类别  */
    pstMsg->MsgHeader.ulMsgName         = MMCGMM_POWER_OFF_REQ;              /* 填写消息名称                             */

    NAS_MML_SndInternalMsg(pstMsg);
}

VOS_VOID   NAS_MMC_SndGmmPlmnSchInit(VOS_VOID)
{
    MMCGMM_PLMN_SEARCH_INITIATED_STRU  *pstInternalMsg = VOS_NULL_PTR;

    pstInternalMsg  = (MMCGMM_PLMN_SEARCH_INITIATED_STRU*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_PLMN_SEARCH_INITIATED_STRU));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstInternalMsg->MsgHeader.ulLength
        = sizeof(MMCGMM_PLMN_SEARCH_INITIATED_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息类别                             */
    pstInternalMsg->MsgHeader.ulMsgName   = MMCGMM_PLMN_SEARCH_INITIATED;              /* 填写消息名称                             */

    NAS_MML_SndInternalMsg(pstInternalMsg);

}



VOS_VOID NAS_MMC_SndGmmSuspendInd(
    RRMM_SUSPEND_IND_ST                *pstMsg
)
{
    /*向GMM发送挂起指示,定义原语类型指针 */
    MMCGMM_SUSPEND_IND_ST              *pstSndMsg       = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstSndMsg  = (MMCGMM_SUSPEND_IND_ST*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_SUSPEND_IND_ST));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_GMM;

    /* 填写消息名称 */
    pstSndMsg->MsgHeader.ulMsgName       = MMCGMM_SUSPEND_IND;
    pstSndMsg->MsgHeader.ulLength        = sizeof(MMCGMM_SUSPEND_IND_ST) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->ucSuspendCause            = pstMsg->ucSuspendCause;
    pstSndMsg->ucSuspendOrigen           = pstMsg->ucSuspendOrigen;

    pstSndMsg->ucSuspendDestination      = pstMsg->ucSuspendDestination;

    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}


VOS_VOID NAS_MMC_SndGmmResumeInd(
    RRMM_RESUME_IND_ST                 *pstMsg
)
{
    /*向GMM发送恢复指示,定义原语类型指针 */
    MMCGMM_RESUME_IND_ST               *pstSndMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstSndMsg  = (MMCGMM_RESUME_IND_ST*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_RESUME_IND_ST));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;

    pstSndMsg->MsgHeader.ulLength
        = sizeof(RRMM_RESUME_IND_ST) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息名称 */
    pstSndMsg->MsgHeader.ulMsgName   = MMCGMM_RESUME_IND;

    pstSndMsg->ucCsResumeResult      = pstMsg->ucCsResumeResult;
    pstSndMsg->ucPsResumeResult      = pstMsg->ucPsResumeResult;
    pstSndMsg->ucResumeOrigen        = pstMsg->ucResumeOrigen;

    pstSndMsg->ucPsSigExistFlg       = VOS_FALSE;

    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}



VOS_VOID  NAS_MMC_SndGmmCoverageLostInd(VOS_VOID)
{
    MMCGMM_COVERAGE_LOST_IND_STRU      *pstInternalMsg;

    pstInternalMsg  = (MMCGMM_COVERAGE_LOST_IND_STRU*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_COVERAGE_LOST_IND_STRU));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstInternalMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;

    /* 填写消息类别  */
    pstInternalMsg->MsgHeader.ulMsgName   = MMCGMM_COVERAGE_LOST_IND;
    pstInternalMsg->MsgHeader.ulLength    = sizeof(MMCGMM_COVERAGE_LOST_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}


VOS_VOID NAS_MMC_SndGmmAttachReq(
    VOS_UINT32                          ulOpid,
    VOS_UINT32                          ulMmcAttachType
)
{
    MMCGMM_ATTACH_REQ_STRU             *pstMsg;

    /* 从内部消息队列中获取一个还没有使用的空间 */

    pstMsg          = (MMCGMM_ATTACH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_ATTACH_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCGMM_ATTACH_REQ;
    pstMsg->ulOpid                      = ulOpid;
    pstMsg->enAttachType                = ulMmcAttachType;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}


VOS_VOID NAS_MMC_SndGmmDetachReq(
    VOS_UINT32                          ulOpid,
    MMC_GMM_DETACH_TYPE_ENUM_UINT32     enDetachType,  /* detach类型 */
    MMC_GMM_DETACH_REASON_ENUM_UINT32   enDetachReason /* detach原因 */
)
{
    MMCGMM_DETACH_REQ_STRU             *pstMsg;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstMsg          = (MMCGMM_DETACH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_DETACH_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg )
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCGMM_DETACH_REQ;
    pstMsg->ulOpid                      = ulOpid;
    pstMsg->enDetachType                = enDetachType;
    pstMsg->enDetachReason              = enDetachReason;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}


VOS_VOID NAS_MMC_SndGmmRelReq(VOS_VOID)
{
    /* 向GMM发送PS信令链接释放消息 */
    MMCGMM_REL_REQ_STRU                *pstSndGmmRelMsg     = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstSndGmmRelMsg = (MMCGMM_REL_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_REL_REQ_STRU));
    if ( VOS_NULL_PTR == pstSndGmmRelMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGmmRelReq:ALLOC MEM ERROR!");
        return;
    }

    pstSndGmmRelMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndGmmRelMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndGmmRelMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndGmmRelMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;

    /* 填写消息类别 */
    pstSndGmmRelMsg->MsgHeader.ulMsgName         = MMCGMM_REL_REQ;
    pstSndGmmRelMsg->MsgHeader.ulLength          = sizeof(MMCGMM_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstSndGmmRelMsg);

    return;

}






#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_SndGmmLteSysinfoInd(
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg
)
{
    /* 定义原语类型指针 */
    MMC_GMM_LTE_SYS_INFO_IND_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg          = (MMC_GMM_LTE_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_GMM_LTE_SYS_INFO_IND_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_SndGmmLteSysinfoInd:Alloc Mem Failed");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstLmmSysInfoMsg, sizeof(MMC_GMM_LTE_SYS_INFO_IND_STRU));

    pstMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->ulMsgId           = MMCGMM_LTE_SYS_INFO_IND;
    pstMsg->ulLength          = sizeof(MMC_GMM_LTE_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return ;
}



VOS_VOID  NAS_MMC_SndGmmLmmAttachInd(
    LMM_MMC_ATTACH_IND_STRU        *pstAttachInd
)
{
    MMCGMM_LMM_ATTACH_IND_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCGMM_LMM_ATTACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_ATTACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGmmLmmAttachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstAttachInd, sizeof(MMCGMM_LMM_ATTACH_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_ATTACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_ATTACH_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}


VOS_VOID  NAS_MMC_SndGmmLmmTauResultInd(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstActionResultInd
)
{
    MMCGMM_LMM_TAU_RESULT_IND_STRU     *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCGMM_LMM_TAU_RESULT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_TAU_RESULT_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGmmLmmTauResultInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstActionResultInd, sizeof(MMCGMM_LMM_TAU_RESULT_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_TAU_RESULT_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_TAU_RESULT_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}


VOS_VOID  NAS_MMC_SndGmmLmmMtDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstActionResultInd
)
{
    MMCGMM_LMM_MT_DETACH_IND_STRU      *pstMsg = VOS_NULL_PTR;

    /* 申请消息内存分配 */
    pstMsg              = (MMCGMM_LMM_MT_DETACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_MT_DETACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndGmmLmmMtDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstActionResultInd, sizeof(MMCGMM_LMM_MT_DETACH_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_MT_DETACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_MT_DETACH_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}



VOS_VOID  NAS_MMC_SndGmmLmmLocalDetachInd(
    LMM_MMC_DETACH_IND_STRU            *pstActionResultInd
)
{
    MMCGMM_LMM_LOCAL_DETACH_IND_STRU   *pstMsg = VOS_NULL_PTR;

    /* 申请消息内存分配 */
    pstMsg              = (MMCGMM_LMM_LOCAL_DETACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_LOCAL_DETACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndGmmLmmLocalDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstActionResultInd, sizeof(MMCGMM_LMM_LOCAL_DETACH_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_LOCAL_DETACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_LOCAL_DETACH_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}


VOS_VOID  NAS_MMC_SndGmmLmmMoDetachInd(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
)
{
    MMCGMM_LMM_MO_DETACH_IND_STRU      *pstMsg = VOS_NULL_PTR;

    /* 申请消息内存分配 */
    pstMsg              = (MMCGMM_LMM_MO_DETACH_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_MO_DETACH_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndGmmLmmMoDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstLmmDetachCnf, sizeof(MMCGMM_LMM_MO_DETACH_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_MO_DETACH_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_MO_DETACH_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}



VOS_VOID  NAS_MMC_SndGmmLmmSerResultnd(
    LMM_MMC_SERVICE_RESULT_IND_STRU     *pstSerInd
)
{
    MMCGMM_LMM_SERVICE_RESULT_IND_STRU *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCGMM_LMM_SERVICE_RESULT_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_SERVICE_RESULT_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGmmLmmSerResultnd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstSerInd, sizeof(MMCGMM_LMM_SERVICE_RESULT_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_SERVICE_RESULT_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_SERVICE_RESULT_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}



VOS_VOID  NAS_MMC_SndGmmLmmStatusInd(
    LMM_MMC_STATUS_IND_STRU            *pstStatusInd
)
{
    MMCGMM_LMM_STATUS_IND_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg              = (MMCGMM_LMM_STATUS_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_STATUS_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGmmLmmStatusInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstStatusInd, sizeof(MMCGMM_LMM_STATUS_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_STATUS_IND_STRU)
                                       -VOS_MSG_HEAD_LENGTH;

    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_STATUS_IND;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}


VOS_VOID  NAS_MMC_SndGmmLmmTimerStateNotify(
    LMM_MMC_TIMER_STATE_NOTIFY_STRU    *pstTimerStatusNotify
)
{
    MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU *pstMsg = VOS_NULL_PTR;

    /* 申请消息内存分配 */
    pstMsg              = (MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMmLmmTimerStatusNotify,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstTimerStatusNotify, sizeof(MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU)
                                       -VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_LMM_TIMER_STATE_NOTIFY;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}



VOS_VOID  NAS_MMC_SndGmmEmergencyNumList(
    MMCGMM_EMERGENCY_NUM_LIST_IND_STRU                     *pstEmergencyNumList
)
{
    MMCGMM_EMERGENCY_NUM_LIST_IND_STRU                     *pstMsg = VOS_NULL_PTR;

    /* 申请消息内存分配 */
    pstMsg = (MMCGMM_EMERGENCY_NUM_LIST_IND_STRU *)
                  NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_EMERGENCY_NUM_LIST_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndGmmEmergencyNumList,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(MMCGMM_EMERGENCY_NUM_LIST_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 消息IE项赋值 */
    PS_MEM_CPY(pstMsg, pstEmergencyNumList, sizeof(MMCGMM_EMERGENCY_NUM_LIST_IND_STRU));

    /* 修改消息头 */
    pstMsg->ulLength        = sizeof(MMCGMM_EMERGENCY_NUM_LIST_IND_STRU)
                                       - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->ulMsgId         = MMCGMM_EMERGENCY_NUM_LIST_IND;


    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

#endif



VOS_VOID NAS_MMC_SndGmmModeChangeReq(
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode
)
{
    MMCGMM_MODE_CHANGE_REQ_STRU         *pstMsg;

    /* 从内部消息队列中获取一个临时发送的空间 */
    pstMsg          = (MMCGMM_MODE_CHANGE_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_MODE_CHANGE_REQ_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_SndGmmModeChangeReq:Alloc Mem Failed");
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_MODE_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCGMM_MODE_CHANGE_REQ;
    pstMsg->enMsMode                    = enMsMode;

    NAS_MML_SndInternalMsg(pstMsg);
}



VOS_VOID   NAS_MMC_SndGmmWasSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSrchFlg,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_SYS_INFO_IND_STRU           *pstInternalMsg    = VOS_NULL_PTR;
    RRMM_SYS_INFO_IND_STRU             *pstRrMmSysInfoInd = VOS_NULL_PTR;

    pstInternalMsg  = (MMCGMM_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_SYS_INFO_IND_STRU));

    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET(pstInternalMsg, 0x00, sizeof(MMCGMM_SYS_INFO_IND_STRU));

    pstRrMmSysInfoInd = (RRMM_SYS_INFO_IND_STRU *)pstMsg;

    /* 填充发送消息 */
    pstInternalMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstInternalMsg->MsgHeader.ulMsgName         = MMCGMM_SYS_INFO_IND;
    pstInternalMsg->MsgHeader.ulLength          = sizeof(MMCGMM_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstInternalMsg->ulCellId              = pstRrMmSysInfoInd->ulCellId;

    /* 根据系统消息的内容，填充Mask值 */
    pstInternalMsg->ulMask = NAS_MMC_GetOptMask_WasSysinfo(pstRrMmSysInfoInd);

    /* 拷贝Common信息 */
    pstInternalMsg->ulCnCommonSize  = (VOS_UINT32)pstRrMmSysInfoInd->ucCnCommonSize;

    PS_MEM_CPY(pstInternalMsg->aucCnCommonInfo,
               pstRrMmSysInfoInd->aucCnCommonInfo, RRC_NAS_MAX_SIZE_NAS_GSM_MAP);

    PS_MEM_CPY(pstInternalMsg->aulPsInfo,
               pstRrMmSysInfoInd->aucPsInfo, RRC_NAS_MAX_SIZE_NAS_GSM_MAP);

    pstInternalMsg->ulPsInfoSize           = (VOS_UINT32)pstRrMmSysInfoInd->ucPsInfoSize;
    pstInternalMsg->PlmnId.ulMcc           = pstRrMmSysInfoInd->PlmnId.ulMcc;
    pstInternalMsg->PlmnId.ulMnc           = pstRrMmSysInfoInd->PlmnId.ulMnc;

    pstInternalMsg->ulPsDrxLength          = pstRrMmSysInfoInd->ulPsDrxLength;

    pstInternalMsg->ulUserSrchFlg          = ulUserSrchFlg;

    pstInternalMsg->ulForbiddenMask    = ulForbiddenFlg;

    /* 在Hplmn上CS注册被拒后，非E5时，不在发起注册 ,E5时，HplmnRejlist不记录值 */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
    {
        pstInternalMsg->ulForbiddenMask = NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej(
                                                ulForbiddenFlg,
                                                ulUserSrchFlg,
                                                NAS_MML_NET_RAT_TYPE_WCDMA,
                                                NAS_MMC_REG_DOMAIN_PS);
    }


    /* 从bar转为不bar的标志位 */
    pstInternalMsg->ucCsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetCsRegisterBarToUnBarFlg();
    pstInternalMsg->ucPsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetPsRegisterBarToUnBarFlg();

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;
}


VOS_VOID   NAS_MMC_SndGmmGsmSysInfoInd(
    VOS_UINT32                          ulForbiddenFlg,
    VOS_UINT32                          ulUserSrchFlg,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pstInternalMsg  = VOS_NULL_PTR;
    GRRMM_SYS_INFO_IND_ST              *pstGrrMmSysInfo = VOS_NULL_PTR;

    pstInternalMsg  = (MMCGMM_GSM_SYS_INFO_IND_ST *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    pstGrrMmSysInfo = (GRRMM_SYS_INFO_IND_ST *)pstMsg;

    pstInternalMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstInternalMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;

    pstInternalMsg->MsgHeader.ulMsgName   = MMCGMM_GSM_SYS_INFO_IND;
    pstInternalMsg->MsgHeader.ulLength    = sizeof(MMCGMM_GSM_SYS_INFO_IND_ST) - VOS_MSG_HEAD_LENGTH;

    /* 填充CS信息 */
    pstInternalMsg->ucAttachDetach           = pstGrrMmSysInfo->ucAttachDetach;
    pstInternalMsg->ucLRTimerT3212           = pstGrrMmSysInfo->ucLRTimerT3212;
    pstInternalMsg->ucGprsSupportInd         = pstGrrMmSysInfo->ucGprsSupportInd;
    pstInternalMsg->usLac                    = pstGrrMmSysInfo->usLac;
    pstInternalMsg->ucSgsnRelease            = pstGrrMmSysInfo->ucSgsnRelease;

    /* 填充PS信息 */
    if ( GRRMM_NW_OP_MODE_III == pstGrrMmSysInfo->ucNetworkOperationMode)
    {
        pstInternalMsg->ucNetworkOperationMode   = GRRMM_NW_OP_MODE_II;
    }
    else
    {
        pstInternalMsg->ucNetworkOperationMode   = pstGrrMmSysInfo->ucNetworkOperationMode;
    }

    pstInternalMsg->ucRac                    = pstGrrMmSysInfo->ucRac;
    pstInternalMsg->usCellId                 = pstGrrMmSysInfo->usCellId;
    pstInternalMsg->stPlmnId.ulMcc           = pstGrrMmSysInfo->PlmnId.ulMcc;
    pstInternalMsg->stPlmnId.ulMnc           = pstGrrMmSysInfo->PlmnId.ulMnc;

    pstInternalMsg->ucDrxTimerMax            = pstGrrMmSysInfo->ucDrxTimerMax;

    pstInternalMsg->ulUserSrchFlg            = ulUserSrchFlg;

    pstInternalMsg->ulForbiddenFlg           = ulForbiddenFlg;

    /* 在Hplmn上CS注册被拒后，非E5时，不在发起注册 ,E5时，HplmnRejlist不记录值 */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
    {
        if ((VOS_FALSE == NAS_MMC_GetHPlmnSpecDomainAccessCapa(NAS_MMC_REG_DOMAIN_PS))
         && (MMCMM_NO_FORBIDDEN == ulForbiddenFlg))
        {
            pstInternalMsg->ulForbiddenFlg   = MMCMM_FORBIDDEN_PLMN;
        }
    }

    /* 在Hplmn上PS注册被拒后，非E5时，不在发起注册 ,E5时，HplmnRejlist不记录值 */
    if ((VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
     && (VOS_FALSE == ulUserSrchFlg))
    {
        pstInternalMsg->ulForbiddenFlg = NAS_MMC_ModifyForbiddenFlg_HplmnRegisterRej(
                                                ulForbiddenFlg,
                                                ulUserSrchFlg,
                                                NAS_MML_NET_RAT_TYPE_GSM,
                                                NAS_MMC_REG_DOMAIN_PS);
    }

    pstInternalMsg->unAcInfo.ucRestrictType               = pstGrrMmSysInfo->unAcInfo.ucRestrictType;

    /* 如果是GSM禁止接入，通知MM/GMM，防止发起注册 */
    if (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
    {
        pstInternalMsg->unAcInfo.ucRestrictType            = RRC_NAS_ACCESS_RESTRICTION_ALL_SERVICE;
    }

    /* 从bar转为不bar的标志位 */
    pstInternalMsg->ucCsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetCsRegisterBarToUnBarFlg();
    pstInternalMsg->ucPsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetPsRegisterBarToUnBarFlg();

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;

}


VOS_VOID  NAS_MMC_SndGmmWasAcInfoChangeInd(
    VOS_UINT8                           ucCsResTrictionRegister,
    VOS_UINT8                           ucPsResTrictionRegister,
    VOS_UINT8                           ucOldCsResTrictionRegister,
    VOS_UINT8                           ucOldPsResTrictionRegister
)
{
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstSndMsg           = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstSndMsg       = (MMCGMM_W_AC_INFO_CHANGE_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_W_AC_INFO_CHANGE_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_SndGmmWasAcInfoChangeInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstSndMsg->MsgHeader.ulLength
        = sizeof(MMCGMM_W_AC_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息类别 */
    pstSndMsg->MsgHeader.ulMsgName          = MMCGMM_W_AC_INFO_CHANGE_IND;

    pstSndMsg->enCsRestrictRegisterChange   = NAS_MML_RESTRICTION_NO_CHANGE;
    pstSndMsg->enPsRestrictRegisterChange   = NAS_MML_RESTRICTION_NO_CHANGE;

    /* CS注册从受限变为不受限 */
    if ((VOS_TRUE == ucOldCsResTrictionRegister)
     && (VOS_FALSE == ucCsResTrictionRegister))
    {
        pstSndMsg->enCsRestrictRegisterChange = NAS_MML_RESTRICTION_BAR_TO_UNBAR;
    }

    /* CS注册从不受限变为受限 */
    if ((VOS_FALSE == ucOldCsResTrictionRegister)
     && (VOS_TRUE == ucCsResTrictionRegister))
    {
        pstSndMsg->enCsRestrictRegisterChange = NAS_MML_RESTRICTION_UNBAR_TO_BAR;
    }

    /* PS注册从受限变为不受限 */
    if ((VOS_TRUE == ucOldPsResTrictionRegister)
     && (VOS_FALSE == ucPsResTrictionRegister))
    {
        pstSndMsg->enPsRestrictRegisterChange = NAS_MML_RESTRICTION_BAR_TO_UNBAR;
    }

    /* PS注册从不受限变为受限 */
    if ((VOS_FALSE == ucOldPsResTrictionRegister)
     && (VOS_TRUE == ucPsResTrictionRegister))
    {
        pstSndMsg->enPsRestrictRegisterChange = NAS_MML_RESTRICTION_UNBAR_TO_BAR;
    }


    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}


VOS_VOID  NAS_MMC_SndGmmVoiceDomainChangeNotify(VOS_VOID)
{
    MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY_STRU *pstSndMsg           = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstSndMsg       = (MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC,"NAS_MMC_SndGmmVoiceDomainChangeNotify:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstSndMsg->MsgHeader.ulLength
        = sizeof(MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息类别 */
    pstSndMsg->MsgHeader.ulMsgName         = MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY;

    /* 内部消息的发送 */
    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}



/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

