/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndGmm.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2010年5月9日
  最近修改   :
  功能描述   : MMC发给GMM的消息的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年05月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmStartReq
 功能描述  : 给GMM发送开机消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月10日
    作    者   : luokaihui /l00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
*****************************************************************************/
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



/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmPowerOffReq
 功能描述  : 向GMM模块发送关机原语MMCGMM_POWER_OFF_REQ的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整

*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmPlmnSchInit
 功能描述  : 向GMM发送plmnsrchinit
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年7月22日
    作    者   : l00130025
    修改内容   : PhaseII修改
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmSuspendInd
 功能描述  : NAS向GMM发起挂起指示
 输入参数  : RRMM_SUSPEND_IND_ST                *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月10日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整

  3.日    期   : 2011年10月27日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseIII 阶段调整:联合注册

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmResumeInd
 功能描述  : NAS向MM发送ResumeInd的指示
 输入参数  : RRMM_RESUME_IND_ST                 *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月10日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2013年11月26日
    作    者   : w00176964
    修改内容   : Volte PhaseII项目调整

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmCoverageLostInd
 功能描述  : NAS向GMM发送coverage lost的指示
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月11日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年7月22日
    作    者   : l00130025
    修改内容   : PhaseII修改
*****************************************************************************/

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

/*******************************************************************************
  函 数 名  : NAS_MMC_SndGmmAttachReq
  功能描述  : 发送原语MMCGMM_ATTACH_REQ的公共处理
  输入参数  : ulOpid          - Opid
               ulMmcAttachType - ATTACH类型
  输出参数  : 无
  返 回 值  :
  调用函数  :
  被调函数  :

  修改历史      :
  1.日    期   : 2011年7月11日
    作    者   : w00166186
    修改内容   : 新建，V7R1 PHASE II,ATTACH/DETACH调整

*******************************************************************************/
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

/*******************************************************************************
 函 数 名  : NAS_MMC_SndGmmDetachReq
 功能描述  : 发送原语MMCGMM_DETACH_REQ的公共处理
 输入参数  : ulOpid        - Opid
              ulDetachCause - Detach原因
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月11日
   作    者   : w00166186
   修改内容   : 新建，V7R1 PHASE II,ATTACH/DETACH调整
*******************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmRelReq
 功能描述  : 向GMM发送PS信令链接释放消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年07月11日
   作    者   : w00167002
   修改内容   : 新生成函数

*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmLteSysinfo
 功能描述  : NAS通知gmm的LTE 系统消息
 输入参数  : MMC_LMM_USIM_STATUS_ENUM_UINT32     ulUsimState
 输出参数  : 无
 返 回 值  : VOS_ERR: ID_MMC_LMM_USIM_STATUS_REQ消息发送失败
             VOS_OK : ID_MMC_LMM_USIM_STATUS_REQ消息发送成功
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年3月28日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月28日
   作    者   : W00166186
   修改内容   : DTS2012042602593,MM没有保存当前驻留的PLMN，导致后续判断出错

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmLmmAttachInd
 功能描述  : MMC向GMM通知当前LMM的attach结果
 输入参数  : LMM_MMC_ATTACH_IND_STRU        *pstActionResultInd
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月26日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmLmmTauResultInd
 功能描述  : MMC向GMM通知当前LMM的TAU注册结果
 输入参数  : LMM_MMC_ATTACH_IND_STRU        *pstActionResultInd
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月26日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmLmmMtDetachInd
 功能描述  : MMC向GMM通知当前LMM的网侧去注册结果
 输入参数  : LMM_MMC_DETACH_IND_STRU            *pstActionResultInd DETACH消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月26日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmLmmLocalDetachInd
 功能描述  : MMC向GMM通知当前LMM的本地去注册结果
 输入参数  : LMM_MMC_DETACH_IND_STRU            *pstActionResultInd DETACH消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月6日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmLmmMoDetachInd
 功能描述  : MMC向GMM通知当前LMM的UE去注册结果
 输入参数  : LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月5日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmLmmSerResultnd
 功能描述  : MMC向GMM通知当前LMM的service request结果
 输入参数  : LMM_MMC_DETACH_IND_STRU        *pstSerInd
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月26日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmLmmStatusInd
 功能描述  : MMC向GMM通知当前LMM的Status_IND
 输入参数  : LMM_MMC_STATUS_IND_STRU        *pstStatusInd
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期: 2012年03月02日
   作    者: l00130025
   修改内容: DTS2012022102014:L->G->L->G后，没有重新分配TLLI,导致G下RAU被网侧ImplicityDetached
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmLmmTimerStateNotify
 功能描述  : MMC向GMM通知当前LMM的定时器状态
 输入参数  : pstTimerStatusNotify - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年3月20日
   作    者   : z00161729
   修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmEmergencyNumList
 功能描述  : MMC向GMM通知EmergencyNumList
 输入参数  : pstEmergencyNumList - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年5月22日
   作    者   : b00269685
   修改内容   : DTS2014050604659新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmModeChangeReq
 功能描述  : 向GMM发送模式改变的消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年3月28日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年07月27日
   作    者   : w00167002
   修改内容   : V7R1_PHASEII调整

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmWasSysInfoInd
 功能描述  : 向GMM转发WAS系统消息
 输入参数  : VOS_UINT32                          ulForbiddenFlg
             VOS_UINT32                          ulUserSrchFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年12月24日
    作    者   : w00166186
    修改内容   : DTS2011122004483,指定搜网不停LAU问题统一修改
  3.日    期   : 2012年05月16日
    作    者   : l65478
    修改内容   : DTS2011122004483,E5在HPLMN上注册失败#14后没有再发起注册
  4.日    期   : 2012年11月29日
    作    者   : W00176964
    修改内容   : DTS2012112902395,BVT测试,hplmn被拒#11后后续需要继续注册
  5.日    期   : 2013年9月14日
    作    者   : w00167002
    修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 在NAS_MMC_SndGmmWasSysInfoInd函数中，如果是用户指定搜网，则将FORBFLG设置为null，
                 将此耦合去除；
                 在选网状态机识别出是否是用户指定搜网，并配置正确的ulForbiddenFlg标志；
  6.日    期   : 2015年11月16日
    作    者   : c00318887
    修改内容   : DTS2015061609864
  7.日    期   : 2016年1月27日
    作    者   : z00359541
    修改内容   : DTS2016012302336:周期RAU被用户指定搜打断，后续搜到同一网络要能发起注册
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmGsmSysInfoInd
 功能描述  : 向GMM转发GSM系统消息
 输入参数  : VOS_UINT32                          ulForbiddenFlg
             VOS_UINT32                          ulUserSrchFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月21日
    作    者   : l00130025
    修改内容   : 新生成函数
  2.日    期   : 2011年12月24日
    作    者   : w00166186
    修改内容   : DTS2011122004483,指定搜网不停LAU问题统一修改
  3.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 修改变量名
  4.日    期   : 2013年9月14日
    作    者   : w00167002
    修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 在NAS_MMC_SndGmmGsmSysInfoInd函数中，如果是用户指定搜网，则将FORBFLG设置为null，
                 将此耦合去除；
                 在选网状态机识别出是否是用户指定搜网，并配置正确的ulForbiddenFlg标志；
  5.日    期   : 2015年11月16日
    作    者   : c00318887
    修改内容   : DTS2015061609864
  6.日    期   : 2015年1月26日
    作    者   : z00359541
    修改内容   : DTS2016012302336:周期RAU被用户指定搜打断，后续搜到同一网络要能发起注册
*****************************************************************************/
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

    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    pstInternalMsg->unAcInfo.ucRestrictType               = pstGrrMmSysInfo->unAcInfo.ucRestrictType;

    /* 如果是GSM禁止接入，通知MM/GMM，防止发起注册 */
    if (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
    {
        pstInternalMsg->unAcInfo.ucRestrictType            = RRC_NAS_ACCESS_RESTRICTION_ALL_SERVICE;
    }
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    /* 从bar转为不bar的标志位 */
    pstInternalMsg->ucCsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetCsRegisterBarToUnBarFlg();
    pstInternalMsg->ucPsChanged2UnBarFlg    = (VOS_UINT8)NAS_MML_GetPsRegisterBarToUnBarFlg();

    NAS_MML_SndInternalMsg(pstInternalMsg);

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmWasAcInfoChangeInd
 功能描述  : NAS向GMM发送AC INFO CHANGE的指示
 输入参数  :
    VOS_UINT8                           ucCsResTrictionRegister,
    VOS_UINT8                           ucPsResTrictionRegister,
    VOS_UINT8                           ucOldCsResTrictionRegister,
    VOS_UINT8                           ucOldPsResTrictionRegister

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : W00166186
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmVoiceDomainChangeNotify
 功能描述  : NAS向GMM发送MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月10日
    作    者   : s00217060
    修改内容   : VOLTE SWITCH新生成函数
*****************************************************************************/
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

