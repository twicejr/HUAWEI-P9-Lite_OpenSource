/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmInterSysCellResel.c
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2011年03月14日
  最近修改   :
  功能描述   : 接入层重选时动作表
  函数列表   :
  修改历史   :
  1.日    期   : 2011年03月14日
    作    者   : zhoujun /40661
    修改内容   : 创建文件
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "Nasrrcinterface.h"
#include "MM_Share.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmlMsgProc.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndMm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndMscc.h"
#include "NasMmcFsmInterSysCellResel.h"
#include "NasMmcFsmInterSysCellReselTbl.h"
#include "NasMmcProcRegRslt.h"
#include "NasMmcProcSuspend.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "NasMmcComFunc.h"
#include "NasUtranCtrlInterface.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_CELLRESEL_C
/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/


/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSuspendInd_InterSysCellResel_Init
 功能描述  : 在SUSPEND的INIT状态,收到was异系统重选指示消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:收到WAS的异系统重选指示消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2012年05月28日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysCellResel_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstGUSuspendMsg = VOS_NULL_PTR;

    pstGUSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMC只在以下三个场景中用原语MMC_LMM_EPLMN_NOTIFY_REQ通知LMM:3异系统变换中，GU发生挂起，目标系统为LTE时 */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstGUSuspendMsg->ucSuspendDestination )
    {
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP);

    /* 启动等待MM回复定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasSuspendInd_InterSysCellResel_Init
 功能描述  : 在SUSPEND的INIT状态,收到Gas异系统重选指示消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:收到GAS的异系统重选指示消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGasSuspendInd_InterSysCellResel_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstGUSuspendMsg = VOS_NULL_PTR;

    pstGUSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMC只在以下三个场景中用原语MMC_LMM_EPLMN_NOTIFY_REQ通知LMM:3异系统变换中，GU发生挂起，目标系统为LTE时 */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstGUSuspendMsg->ucSuspendDestination )
    {
        /* 通知LTE等效PLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP);

    /* 启动等待MM回复定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_InterSysCellResel_RSP状态
             收到MMCGMM_Suspend_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMM_Suspend_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月14日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2012年11月17日
    作    者   : s00217060
    修改内容   : DTS2012082007133:如果有打断，并且挂起原因是重定向，给不同的接入层发送SUSPEND_REL_REQ

  4.日    期   : 2014年2月26日
    作    者   : w00167002
    修改内容   : L-C互操作项目:UT修改

  5.日    期   : 2015年04月24日
    作    者   : j00174725
    修改内容   : DSDS(接入层修改定时器长度) DTS2015042702414

  6.日    期   : 2015年05月30日
    作    者   : l00324781
    修改内容   : CDMA Iteration 12: 增加 CL模式下，L2C重选或重定向功能。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* 标记已收到GMM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCellResel( NAS_MMC_GMM_SUSPEND_RSP_FLG );

    /* 未收齐GMM,MM的SUSPNED_RSP，返回继续等待 */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCellResel() )
    {
        return VOS_TRUE;
    }

    /* 停止定时器MMC_WAIT_NAS_SUSPEND_RSP_TIMER */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* 向接入层发送挂起成功 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* 如果有打断，并且挂起原因是重定向，给不同的接入层发送SUSPEND_REL_REQ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
        if ( MMC_SUSPEND_CAUSE_REDIRECTION == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
        {
            NAS_MMC_SndSuspendRelReq_InterSysCellResel(NAS_MML_GetCurrNetRatType());

            return VOS_TRUE;
        }
    }

    /* 将MMC的状态置成SUSPEND:NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND );

    /* 拼片或CL模式下，启动不同时长定时器 */
    if (VOS_TRUE == NAS_MMC_StartResumeTimer_InterSysCellResel())
    {
        return VOS_TRUE;
    }

    /* 如果是GU重定向,定时器时间为90S;如果是GL WL之间的重定向,定时器时间为200S */
    if ( MMC_SUSPEND_CAUSE_CELLRESELECT == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
    {
        ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

         return VOS_TRUE;
    }

    /* 获取挂起目的方的网络类型 */
#if (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetSuspendDestinationRatType(NAS_MMC_GetCurrEntryMsg()))
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, TI_NAS_MMC_INTER_SYS_GUL_REDIR_WAIT_AS_RESUME_IND_LEN);
    }
    else
#endif
    {
        ulResumeIndTiLen = NAS_MMC_GetWaitGUTAsRedirResumeIndTimerLen();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);
    }

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_InterSysCellResel_RSP状态
             收到MMCMM_Suspend_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMM_Suspend_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月14日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2012年11月17日
    作    者   : s00217060
    修改内容   : DTS2012082007133:如果有打断，并且挂起原因是重定向，给不同的接入层发送SUSPEND_REL_REQ
  4.日    期   : 2015年04月24日
    作    者   : j00174725
    修改内容   : DSDS(接入层修改定时器长度) DTS2015042702414
  5.日    期   : 2015年05月30日
    作    者   : l00324781
    修改内容   : CDMA Iteration 12: 增加 CL模式下，L2C重选或重定向功能。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* 标记已收到MM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCellResel( NAS_MMC_MM_SUSPEND_RSP_FLG );

    /* 未收齐GMM,MM的SUSPNED_RSP,返回继续等待 */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCellResel() )
    {
        return VOS_TRUE;
    }

    /* 停止定时器MMC_WAIT_NAS_SUSPEND_RSP_TIMER */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* 向接入层发送挂起成功 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* 如果有打断，并且挂起原因是重定向，给不同的接入层发送SUSPEND_REL_REQ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
        if (MMC_SUSPEND_CAUSE_REDIRECTION == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
        {
            NAS_MMC_SndSuspendRelReq_InterSysCellResel(NAS_MML_GetCurrNetRatType());

            return VOS_TRUE;
        }
    }

    /* 将MMC的状态置成SUSPEND:NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND );

    /* 拼片或CL模式下，启动不同时长定时器 */
    if (VOS_TRUE == NAS_MMC_StartResumeTimer_InterSysCellResel())
    {
        return VOS_TRUE;
    }

    /* 如果是GU重定向,定时器时间为90S;如果是GL WL之间的重定向,定时器时间为200S */
    if ( MMC_SUSPEND_CAUSE_CELLRESELECT == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
    {
        ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

         return VOS_TRUE;
    }

    /* 获取挂起目的方的网络类型 */
#if (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetSuspendDestinationRatType(NAS_MMC_GetCurrEntryMsg()))
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, TI_NAS_MMC_INTER_SYS_GUL_REDIR_WAIT_AS_RESUME_IND_LEN);
    }
    else
#endif
    {
        ulResumeIndTiLen = NAS_MMC_GetWaitGUTAsRedirResumeIndTimerLen();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);
    }

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCellResel_WaitMmSuspendRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_InterSysCellResel_RSP状态
              收到TI_NAS_MMC_WAIT_MM_Suspend_RSP_TIMER消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_MM_Suspend_RSP_TIMER消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月12日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCellResel_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCellResel_WaitMmSuspendRsp:ENTERED");

    /* 向接入层发送挂起失败 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 向MM/GMM进行恢复 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出状态机*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmSuspendRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_InterSysCellResel_RSP状态
             收到MMCMMC_ABORT_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录打断标志 */
    NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_TRUE);

    /* 等收齐了MM/GMM的SUSPEND_RSP后，再给接入层发RRMM_SUSPEND_REL_REQ */

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND状态
              收到WAS:RRMM_RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月12日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2011年12月1日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseIV 阶段调整

  4.日    期   : 2012年9月11日
    作    者   : z40661
    修改内容   : DTS2012090505066:异系统回退信号门限上报不正确
  5.日    期   : 2012年10月22日
    作    者   : t00212959
    修改内容   : DTS2012101907218:限制服务的上报时机不正确
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;


    /* 停止MMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /*  异系统到其他模式后清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_WCDMA);
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */


    /* 生成RESUME消息 */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND状态
              收到GAS:RRMM_RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月12日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整

 3.日    期   : 2012年9月11日
   作    者   : z40661
   修改内容   : DTS2012090505066:异系统回退信号门限上报不正确
 4.日    期   : 2012年10月22日
   作    者   : t00212959
   修改内容   : DTS2012101907218:限制服务的上报时机不正确
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;


    /* 停止MMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* 清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_GSM);
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */


    /* 生成RESUME消息 */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcWaitAsResumeIndTimerOutInSuspendWaitAsResumeInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND状态
              收到TI_NAS_MMC_WAIT_AS_RESUME_IND_TIMER消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_AS_RESUME_IND_TIMER消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月12日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整

  3.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                  以供MM层调用，进行软复位。
  4.日    期   : 2014年2月18日
    作    者  :  w00242748
    修改内容  :  DTS2014021803515:复位时明确是收到哪个接入技术的异常消息导致的。

  5.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCellResel_WaitAsResumeInd:ENTERED");

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_WAS_WAIT_RESUME_IND_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_WAS_WAIT_RESUME_IND_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_LMM_WAIT_RESUME_IND_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_TD_WAIT_RESUME_IND_EXPIRED);
    }

   return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND状态
              收到MMCMMC_ABORT_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
    VOS_UINT32                          ulIsSysChgToHrpd;

    ulIsSysChgToHrpd = NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg());
#endif

    /* 记录打断标志 */
    NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_TRUE);

    /* 如果是GU重定向,给GU接入层发RRMM_SUSPEND_REL_REQ
       如果是L模重定向到GU，给LMM发送LMM_SUSPEND_REL_REQ */
    if (( MMC_SUSPEND_CAUSE_REDIRECTION == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
      || (VOS_TRUE == ulIsSysChgToHrpd)
#endif
      )
    {
        /* 停止TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF);

        /* 停止MMC_WAIT_AS_RESUME_IND_TIMER */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

        NAS_MMC_SndSuspendRelReq_InterSysCellResel(NAS_MML_GetCurrNetRatType());
    }

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_InterSysCellResel_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND状态
             收到RRMM_REL_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月28日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年03月23日
    作    者   : l00130025
    修改内容   : DTS2012031604090,收到WRR的Rel_ind时没有设置RAT，导致恢复ResumeRsp错误
  3.日    期   : 2012年5月24日
    作    者   : l00171473
    修改内容   : DTS2012051104124, relind处理修改
  4.日    期   : 2012年9月11日
    作    者   : z40661
    修改内容   : DTS2012090505066:异系统回退信号门限上报不正确
  5.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : DTS2012082007133:有打断标志时，退出状态机，处理打断消息
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmRelInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRelInd = VOS_NULL_PTR;
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    pstRelInd = (RRMM_REL_IND_STRU*)pstMsg;


    /* 释放原因为Utran release时, 需要继续重选流程, 继续等待resume ind,
       其它认为流程结束, 代表WAS恢复, 即等同WAS发送了resume ind */
    if (RRC_REL_CAUSE_UTRAN_RELEASE == pstRelInd->ulRelCause)
    {
        return VOS_TRUE;
    }

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* 清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* 停止TI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);


    /* 构造resume消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 如果前面有打断标志，退出当前状态机，处理打断消息 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
        /* 回复InterSysCellResel执行结果 */
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmResumeRsp_InterSysCellResel_WaitMmResumeRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态
              收到MMCGMM_RESUME_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCGMM_RESUME_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月12日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2011年12月12日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseIV 阶段调整:调整等待WAS系统消息时长
  4.日    期   : 2012年6月1日
    作    者   : l00130025
    修改内容   : DTS2012053003593:FACH态出服务区，W重入服务区，数传不能恢复
  5.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : DTS2012082007133:有打断标志时，退出状态机，处理打断消息
  6.日    期   : 2012年11月21日
    作    者   : z00161729
    修改内容   : 支持cerssi和nmr
  7.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容  : L-C互操作项目，增加重选到HRPD的处理
  8.日    期   : 2015年05月30日
    作    者   : l00324781
    修改内容   : CDMA Iteration 12: 增加 CL模式下，L2C重选或重定向功能。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysCellResel_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;
#if (FEATURE_ON == FEATURE_LTE)
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
    VOS_UINT32                          ulIsSysChgToHrpd;
#endif
    enSuspendCause                      = NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg());
#endif
    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    NAS_MMC_ClearResumeRspFlag_InterSysCellResel( NAS_MMC_GMM_RESUME_RSP_FLG );

    /* 未否收齐GMM的MMCGMM_RESUME_RSP和 MM的MMCMM_RESUEM_RSP,返回继续等待 */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCellResel() )
    {
        return VOS_TRUE;
    }

    /* 如果已经收齐,停止MMC_WAIT_MM_RESUME_RSP_TIMER */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    if(VOS_TRUE == NAS_MMC_ProcResumeRspFromLteToHrpd_InterSysCellResel())
    {
        return VOS_TRUE;
    }

    /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */

    /* 如果前面有打断标志，并且当前接入技术不是LTE，退出当前状态机，处理打断消息
       如果当前接入技术是LTE,需要继续等LTE的系统消息 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
#if (FEATURE_ON == FEATURE_LTE)
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
        ulIsSysChgToHrpd = NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg());
#endif
        if ((NAS_MML_NET_RAT_TYPE_LTE != enCurNetType)
           || ((MMC_SUSPEND_CAUSE_CELLRESELECT == enSuspendCause)
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
          &&(VOS_FALSE == ulIsSysChgToHrpd)
#endif
          ))
#endif
        {
            /* 回复InterSysCellResel执行结果 */
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }
    }

    /* 根据不同的网络类型迁移到不同的状态 */
    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:


            /* W下Cell Reselect 重选回退到 W下，可能进入FACH态出服务区流程，需要提前退出，系统消息有后续状态机处理 */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                /* 发送状态机成功的结果 */
                NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

                /* 退出当前状态机: */
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;

            }
            else
            {
                /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND状态 */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND);

                /* WAS的回退流程中，上报系统消息时间较长，调整等待系统消息时长 */
                if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
                }
                else
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
                }
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvGmmResumeRsp_InterSysCellResel_WaitMmResumeRsp:Unexpected Rat Type!");
            break;
    }

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcMmResumeRspInSuspendWaitMmResumeRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态
              收到MMCMM_RESUME_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMM_RESUME_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月12日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2011年12月12日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseIV 阶段调整:调整等待WAS系统消息时长
  4.日    期   : 2012年6月1日
    作    者   : l00130025
    修改内容   : DTS2012053003593:FACH态出服务区，W重入服务区，数传不能恢复
  5.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : DTS2012082007133:有打断标志时，退出状态机，处理打断消息
  6.日    期   : 2012年11月21日
    作    者   : z00161729
    修改内容  : 支持cerssi和nmr
  7.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容  : L-C互操作项目，增加重选到HRPD的处理
  8.日    期   : 2015年05月30日
    作    者   : l00324781
    修改内容   : CDMA Iteration 12: 增加 CL模式下，L2C重选或重定向功能。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysCellResel_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;
#if (FEATURE_ON == FEATURE_LTE)
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
    VOS_UINT32                          ulIsSysChgToHrpd;
#endif
    enSuspendCause                      = NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg());
#endif
    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    NAS_MMC_ClearResumeRspFlag_InterSysCellResel( NAS_MMC_MM_RESUME_RSP_FLG );

    /* 未收齐GMM的MMCGMM_RESUME_RSP和 MM的MMCMM_RESUEM_RSP,返回继续等待 */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCellResel() )
    {
        return VOS_TRUE;
    }

    /* 如果已经收齐,停止MMC_WAIT_MM_RESUME_RSP_TIMER */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* 如果重选到HRPD，通知LMM恢复，退出状态机 */
    if (VOS_TRUE == NAS_MMC_ProcResumeRspFromLteToHrpd_InterSysCellResel())
    {
        return VOS_TRUE;
    }

    /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */

    /* 如果前面有打断标志，退出当前状态机，处理打断消息 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
#if   (FEATURE_ON == FEATURE_LTE)
#if   ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
        ulIsSysChgToHrpd = NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg());
#endif
        if ( (NAS_MML_NET_RAT_TYPE_LTE != enCurNetType)
          || ((MMC_SUSPEND_CAUSE_CELLRESELECT == enSuspendCause)
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
          &&(VOS_FALSE == ulIsSysChgToHrpd)
#endif
          ))
#endif
        {
            /* 回复InterSysCellResel执行结果 */
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }
    }

    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* W下Cell Reselect 重选回退到 W下，可能进入FACH态出服务区流程，需要提前退出，系统消息有后续状态机处理 */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                /* 发送状态机成功的结果 */
                NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

                /* 退出当前状态机: */
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;

            }
            else
            {
                /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND状态 */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND);

                /* WAS的回退流程中，上报系统消息时间较长，调整等待系统消息时长 */
                if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
                }
                else
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
                }
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmResumeRsp_InterSysCellResel_WaitMmResumeRsp:Unexpected Rat Type!");
            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcWaitMmResumeRspTimerOutInSuspendWaitMmResumeRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态
              收到TI_NAS_MMC_WAIT_MM_RESUME_RSP_TIMER消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_MM_RESUME_RSP_TIMER消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月12日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2011年12月12日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseIV 阶段调整:调整等待WAS系统消息时长
  4.日    期   : 2012年6月1日
    作    者   : l00130025
    修改内容   : DTS2012053003593:FACH态出服务区，W重入服务区，数传不能恢复
  5.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : DTS2012082007133:有打断标志时，并且挂起原因是重选，退出状态机，处理打断消息
  6.日    期   : 2012年11月21日
    作    者   : z00161729
    修改内容   : 支持cerssi和nmr
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCellResel_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;
#if (FEATURE_ON == FEATURE_LTE)
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;

    enSuspendCause                      = NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg());
#endif
    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCellResel_WaitMmResumeRsp:ENTERED");

    /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */

    /* 如果前面有打断标志，并且挂起原因是重选，退出当前状态机，处理打断消息 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
#if   (FEATURE_ON == FEATURE_LTE)
        if ( (NAS_MML_NET_RAT_TYPE_LTE != enCurNetType)
          || (MMC_SUSPEND_CAUSE_CELLRESELECT == enSuspendCause) )
#endif
        {
            /* 回复InterSysCellResel执行结果 */
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }
    }

    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:


            /* W下Cell Reselect 重选回退到 W下，可能进入FACH态出服务区流程，需要提前退出，系统消息有后续状态机处理 */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                /* 发送状态机成功的结果 */
                NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

                /* 退出当前状态机: */
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;

            }
            else
            {
                /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND状态 */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND);

                /* WAS的回退流程中，上报系统消息时间较长，调整等待系统消息时长 */
                if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
                }
                else
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
                }
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCellResel_WaitMmResumeRsp:Unexpected Rat Type!");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmResumeRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态
              收到MMCMMC_ABORT_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 记录打断标志 */
    NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF状态
              收到WAS的SUSPEND_REL_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_SUSPEND_REL_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 停等待WAS的SUSPEND_REL_CNF消息的定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /*  异系统到其他模式后清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* 回复InterSysCellResel执行结果 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitWasSuspendRelCnf
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF状态
              收到WAS的RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 对冲场景，刚向接入层发完RRMM_SUSPEND_REL_REQ,就收到接入层的RRMM_RESUME_IND
       先处理RRMM_RESUME_IND,后面再收到RRMM_SUSPEND_REL_CNF丢弃 */

    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    /* 停等待SUSPEND_REL_CNF消息的定时器 */
    NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(enRatType);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != enRatType)
    {
        /*  异系统到其他模式后清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);


    /* 生成RESUME消息 */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF状态
              等待WAS的SUSPEND_REL_CNF消息超时的处理
 输入参数  : ulEventType:消息类型
             pstMsg:等待RRMM_SUSPEND_REL_CNF超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /*  异系统到其他模式后清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* 回复InterSysCellResel执行结果 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrmmRelInd_InterSysCellResel_WaitWasSuspendRelCnf
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF状态
              收到WAS的RRMM_REL_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrmmRelInd_InterSysCellResel_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 停等待WAS的SUSPEND_REL_CNF消息的定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /*  异系统到其他模式后清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* 回复InterSysCellResel执行结果 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF状态
              收到WAS的SUSPEND_REL_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_SUSPEND_REL_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 停等待GAS的SUSPEND_REL_CNF消息的定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF);

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* 清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);

    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* 回复InterSysCellResel执行结果 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitGasSuspendRelCnf
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SUSPEND_REL_CNF状态
              收到GAS的RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 对冲场景，刚向接入层发完RRMM_SUSPEND_REL_REQ,就收到接入层的RRMM_RESUME_IND
       先处理RRMM_RESUME_IND,后面再收到RRMM_SUSPEND_REL_CNF丢弃 */

    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    /* 停等待SUSPEND_REL_CNF消息的定时器 */
    NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(enRatType);

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* 清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);


    /* 生成RESUME消息 */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);


    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF状态
              等待GAS的SUSPEND_REL_CNF消息超时的处理
 输入参数  : ulEventType:消息类型
             pstMsg:等待RRMM_SUSPEND_REL_CNF超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* 清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);

    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* 回复InterSysCellResel执行结果 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}





/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitWasSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND状态
              收到rrmm_sysinfo_ind消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_SYS_INFO_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 3.日    期   : 2012年8月14日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题,禁止LTE漫游
 4.日    期   : 2012年10月22日
   作    者   : t00212959
   修改内容   : DTS2012101907218:限制服务的上报时机不正确
 4.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 5.日    期   : 2013年4月10日
   作    者   : w00176964
   修改内容   : DTS2013032507710:增加NV控制,重选到GU下H3G时收到GU的系统消息场景,是否设置CS/PS的服务状态
 6.日    期   : 2013年9月14日
    作    者   : w00167002
    修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 在NAS_MMC_SndMmGsmSysInfoInd函数中，如果是用户指定搜网，则将FORBFLG设置为null，
                 将此耦合去除；
                 在选网状态机识别出是否是用户指定搜网，并配置正确的ulForbiddenFlg标志；

 7.日    期   : 2014年1月18日
   作    者   : z00234330
   修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
               此处判断并没有判断plmnid是否有效
 8.日    期   : 2014年4月28日
   作    者   : w00242748
   修改内容   : DTS2014042808114:针对H3G漫游场景，L下同样需要增加NV控制。
 9.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
 10.日    期   : 2014年5月31日
    作    者   : y00245242
    修改内容   : 修改服务状态上报
 11.日    期   : 2014年12月19日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI 服务状态上报调整到系统消息上报后面
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulParentEventType;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    VOS_UINT8                                               ucH3gCtrlFlg;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 停止保护定时器  TI_NAS_MMC_WAIT_WAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    /* 获取旧的网络类型 */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* 异系统重选时，需要针对H3G漫游场景做特殊处理，即当前网络如果不是HPLMN，
       则服务状态需要先更新为受限服务 */
    ucH3gCtrlFlg = NAS_MML_GetH3gCtrlFlg();


    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    }

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /* 服务状态和注册状态上报放在系统消息上报后面 */
    if ((VOS_TRUE != NAS_MML_ComparePlmnIdWithHplmn(&(stOldCampInfo.stLai.stPlmnId)))
     && (NAS_MML_NET_RAT_TYPE_WCDMA != enOldNtType)
     && (VOS_TRUE == ucH3gCtrlFlg))
    {
        /* 小区重选后，在成功注册前，先上报limit service */
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, end */
    }


    /*转发系统消息通知 给 MM/GMM */
    enParentFsmId     = NAS_MMC_GetParentFsmId();
    ulParentEventType = NAS_MMC_GetParentFsmEventType();

    if ( VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enParentFsmId,ulParentEventType) )
    {
        /* 转发系统消息通知 给 MM/GMM */
        NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        /* 转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
        NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

    }


#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    /* 发送suspend状态机完成消息 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitWasSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND状态
              收到RRMM_AREA_LOST_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_AREA_LOST_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
 4.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
 5.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];

    pstAreaLostInd = (RRMM_AREA_LOST_IND_STRU*)pstMsg;

    /* 停止保护定时器  TI_NAS_MMC_WAIT_WAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
	NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND状态
              收到TI_NAS_MMC_WAIT_WAS_SYS_INFO消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_WAS_SYS_INFO消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd:ENTERED");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_WAS_SYS_INFO_EXP);
    }
    else
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_TAS_SYS_INFO_EXP);
    }

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitWasSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND状态
              收到MMCMMC_ABORT_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*停止保护定时器 TI_NAS_MMC_WAIT_WAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitGasSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND状态
              收到GRRMM_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:GRRMM_SYS_INFO_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 3.日    期   : 2012年8月14日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题,禁止LTE漫游
 4.日    期   : 2012年10月22日
   作    者   : t00212959
   修改内容   : DTS2012101907218,限制服务的上报时机
 5.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 6.日    期   : 2013年4月10日
   作    者   : w00176964
   修改内容   : DTS2013032507710:增加NV控制,重选到GU下H3G时收到GU的系统消息场景,是否设置CS/PS的服务状态
 7.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式

 8.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
 9.日    期   : 2014年5月31日
   作    者   : y00245242
   修改内容   : 修改服务状态上报
10.日    期   : 2014年12月19日
   作    者   : s00217060
   修改内容   : Service_State_Optimize_PhaseI 服务状态上报调整到系统消息上报后面
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulParentEventType;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;
    VOS_UINT8                                               ucH3gCtrlFlg;

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 停止保护定时器  TI_NAS_MMC_WAIT_GAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* 获取旧的网络类型 */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* 异系统重选时,NV进行定制,针对H3G漫游场景做特殊处理，即当前网络如果不是HPLMN，
       则服务状态需要先更新为受限服务 */
    ucH3gCtrlFlg = NAS_MML_GetH3gCtrlFlg();

    /* 服务状态上报调整到系统消息上报后面 */

    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /* 服务状态和注册状态上报放在系统消息上报后面 */
    if ((VOS_TRUE != NAS_MML_ComparePlmnIdWithHplmn(&(stOldCampInfo.stLai.stPlmnId)))
     && (NAS_MML_NET_RAT_TYPE_GSM != enOldNtType)
     && (VOS_TRUE == ucH3gCtrlFlg))
    {
        /* 小区重选后，在成功注册前，先上报limit service */
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, end */
    }

    /*转发系统消息通知 给 MM/GMM */
    enParentFsmId     = NAS_MMC_GetParentFsmId();
    ulParentEventType = NAS_MMC_GetParentFsmEventType();


    if ( VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enParentFsmId,ulParentEventType) )
    {
        /* 转发系统消息通知 给 MM/GMM */
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        /* 转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

    }

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    /* 发送suspend状态机完成消息 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitGasSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND状态
              收到RRMM_AREA_LOST_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_AREA_LOST_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
 4.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
 5.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];

    pstAreaLostInd = (RRMM_AREA_LOST_IND_STRU*)pstMsg;

    /* 停止保护定时器  TI_NAS_MMC_WAIT_GAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
	NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitGasSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND状态
              收到TI_NAS_MMC_WAIT_GAS_SYS_INFO消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_GAS_SYS_INFO消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd:ENTERED");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_GAS_SYS_INFO_EXP);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitGasSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND状态
              收到MMCMMC_ABORT_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*停止保护定时器 TI_NAS_MMC_WAIT_GAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLSysInfoInd_InterSysCellResel_WaitLSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND状态
              收到ID_LMM_MMC_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:ID_LMM_MMC_SYS_INFO_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年4月18日
   作    者   : l00130025
   修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
 3.日    期   : 2012年4月28日
   作    者   : W00166186
   修改内容   : DTS2012042602593,MM没有保存当前驻留的PLMN，导致后续判断出错
 4.日    期   : 2012年11月20日
   作    者   : s00217060
   修改内容   : DTS2012082007133:收到L的系统消息或丢网消息时，判断是不是L重定向到GU失败，回退到L
                如果是，等收到LMM的suspend_rel_cnf，再退出状态机，处理打断消息
 5.日    期   : 2012年11月29日
   作    者   : w00176964
   修改内容   : DTS2012042804167:通知CBA模块当前接入模式为LTE
 6.日    期   : 2012年12月20日
   作    者   : w00176964
   修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
 7.日    期   : 2013年1月19日
    作    者   : t00212959
    修改内容   : DTS2012122900189:EPS注册状态完全由L上报
 8.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    LMM_MMC_SYS_INFO_IND_STRU                              *pstLmmSysInfoMsg    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmPlmnId        = VOS_NULL_PTR;
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    /* 获取旧的网络类型 */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /*停止保护定时器 TI_NAS_MMC_WAIT_LMM_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    PS_MEM_SET(&stPlmnId, 0x00, sizeof(NAS_MML_PLMN_ID_STRU));

    pstLmmSysInfoMsg = (LMM_MMC_SYS_INFO_IND_STRU*)pstMsg;

    pstLmmPlmnId = &(pstLmmSysInfoMsg->stLteSysInfo.stSpecPlmnIdList.astSuitPlmnList[0]);

    NAS_MMC_ConvertLmmPlmnToGUNasFormat(pstLmmPlmnId, &stPlmnId);

    /* C2L 切换到lte plmn不符合lte plmn 优先级 大于等于 1x 的要求 */
    if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
    {
         /*发送状态机失败结果*/
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
#endif

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);



    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }
    /* 转发GMM系统消息,供rabm使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    /* L重定向到GU，如果停止GURRC成功，或者重定向失败回退到L时，
       消息发送的顺序为：LMM上报RESUME_IND,再上报LMM_SYS_INFO_IND或AREA_LOST_IND
       最后再上报SUSPEND_REL_CNF,之后才能退出状态机，处理打断消息，
       所以此处迁到等LMM的SUSPEND_REL_CNF状态 */
    if ( (VOS_TRUE == NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel())
      && (NAS_MML_NET_RAT_TYPE_LTE == enOldNtType) )
    {
        /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN);

        return VOS_TRUE;
    }

    /* 发送suspend状态机完成消息 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitLSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND状态
              收到ID_LMM_MMC_AREA_LOST_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:ID_LMM_MMC_AREA_LOST_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2012年11月20日
   作    者   : s00217060
   修改内容   : DTS2012082007133:收到L的系统消息或丢网消息时，判断是不是L重定向到GU失败，回退到L
               如果是，等收到LMM的suspend_rel_cnf，再退出状态机，处理打断消息
 4.日    期   : 2014年5月5日
   作    者   : w00242748
   修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                注册状态的上报。
 5.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_AREA_LOST_IND_STRU                             *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;

    pstAreaLostInd = (LMM_MMC_AREA_LOST_IND_STRU*)pstMsg;

    /* 获取旧的网络类型 */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* 停止保护定时器  TI_NAS_MMC_WAIT_LMM_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 更新服务状态 */


    /* 向TAF报出服务区 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* 通知TAF当前的服务状态 */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /* L重定向到GU，如果停止GURRC成功，或者重定向失败回退到L时，
       消息发送的顺序为：LMM上报RESUME_IND,再上报LMM_SYS_INFO_IND或AREA_LOST_IND
       最后再上报SUSPEND_REL_CNF,之后才能退出状态机，处理打断消息，
       所以此处迁到等LMM的SUSPEND_REL_CNF状态 */
    if ( (VOS_TRUE == NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel())
      && (NAS_MML_NET_RAT_TYPE_LTE == enOldNtType) )
    {
        /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN);

        return VOS_TRUE;
    }

    NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLSysInfoExpired_InterSysCellResel_WaitLSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND状态
              收到TI_NAS_MMC_WAIT_LMM_SYS_INFO消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_LMM_SYS_INFO消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月28日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2012年11月20日
   作    者   : s00217060
   修改内容   : DTS2012082007133:收到L的系统消息或丢网消息时，判断是不是L重定向到GU失败，回退到L
              如果是，等收到LMM的suspend_rel_cnf，再退出状态机，处理打断消息
 4.日    期   : 2014年5月5日
   作    者   : w00242748
   修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                注册状态的上报。
 5.日    期   : 2015年11月16日
   作    者   : l00324781
   修改内容   : DTS2015111004607: 删除语句：当前接入结束设置为BUTT
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;

    /* 获取旧的网络类型 */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLSysInfoExpired_InterSysCellResel_WaitLSysInfoInd:ENTERED");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 更新服务状态 */
    


    /* 向TAF报出服务区 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* 通知TAF当前的服务状态 */

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /* L重定向到GU，如果停止GURRC成功，或者重定向失败回退到L时，
       消息发送的顺序为：LMM上报RESUME_IND,再上报LMM_SYS_INFO_IND或AREA_LOST_IND
       最后再上报SUSPEND_REL_CNF,之后才能退出状态机，处理打断消息，
       所以此处迁到等LMM的SUSPEND_REL_CNF状态 */
    if ( (VOS_TRUE == NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel())
      && (NAS_MML_NET_RAT_TYPE_LTE == enOldNtType) )
    {
        /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN);

        return VOS_TRUE;
    }

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_LNAS_SYS_INFO_EXP);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_InterSysCellResel_Init
 功能描述  : 在SUSPEND的INIT状态,收到LMM的异系统重选指示消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:收到LTE的异系统重选指示消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2015年11月05日
    作    者   : w00176964
    修改内容   : DTS2015070910837:通知MSCC CL异系统开始指示
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_InterSysCellResel_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                 stSndSuspendMsg;
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg  = VOS_NULL_PTR;

    pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 转换L的挂起消息为GU格式的 */
    NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stSndSuspendMsg);

    if (MMC_SUSPEND_DESTINATION_HRPD == stSndSuspendMsg.ucSuspendDestination)
    {
        /* 给mscc发送异系统开始指示 */
        NAS_MMC_SndMsccInterSysStartInd(NAS_MMC_ConvertMmcInterSysCauseToMsccFormat(stSndSuspendMsg.ucSuspendCause),
                                        VOS_RATMODE_LTE,
                                        VOS_RATMODE_HRPD);
    }

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(&stSndSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(&stSndSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 将状态迁移*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP);

    /* 启动等待MM回复定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND状态
              收到ID_LMM_MMC_RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月12日
    作    者   : W00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年07月13日
    作    者   : w00176964
    修改内容   : GUNAS V7R1 PhaseII 阶段调整
  3.日    期   : 2014年4月28日
    作    者   : w00242748
    修改内容   : DTS2014042808114:针对H3G漫游场景，L下同样需要增加NV控制。
  4.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。

  5.日    期   : 2014年7月18日
    作    者   : w00167002
    修改内容   : DTS2014071701762:在L->C失败从L恢复时候，没有停止CMMCA RESUME IND
                 的定时器，后续定时器超时导致复位。
  5.日    期   : 2015年8月22日
    作    者   : m00312079
    修改内容   : DTS2015081908397:在L->C失败从L恢复时候，停止TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF定时器
  6.日    期   : 2015年11月05日
    作    者   : w00176964
    修改内容   : DTS2015070910837:通知MSCC异系统结束
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;


    /* 停止MMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))

    /* 停止TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF);
#endif

#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
    if (VOS_TRUE == NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg()))
    {
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CMMCA_RESUME_IND);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        NAS_MMC_SndMsccInterSysEndInd(VOS_RATMODE_LTE);
#endif
    }
#endif

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_LTE);
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

    /* 由于L的RESUME_IND消息不包含CS,PSresume结果，此时按照恢复成功生成RESUME消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_NET_RAT_TYPE_LTE ,&stResumeIndMsg);

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF状态
              收到LMM的SUSPEND_REL_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCLMM_SUSPEND_REL_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2014年3月14日
    作    者   : s00246516
    修改内容   : L-C互操作项目，需要通知MM/GMM恢复消息
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, Begin */
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 停等待LMM的SUSPEND_REL_CNF消息的定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    /* Modified by s00246516 for L-C互操作项目, 2014-02-14, End */

    /* 回复InterSysCellResel执行结果 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitLmmSuspendRelCnf
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_Lmm_SUSPEND_REL_CNF状态
              收到LMM的RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2014年4月28日
    作    者   : w00242748
    修改内容   : DTS2014042808114:针对H3G漫游场景，L下同样需要增加NV控制。
  3.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 对冲场景，刚向接入层发完RRMM_SUSPEND_REL_REQ,就收到接入层的RRMM_RESUME_IND
       先处理RRMM_RESUME_IND,后面再收到RRMM_SUSPEND_REL_CNF丢弃 */

    RRMM_RESUME_IND_ST                  stResumeIndMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    /* 获取旧的网络类型 */

    /* 停等待SUSPEND_REL_CNF消息的定时器 */
    NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(enRatType);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);


    /* 由于L的RESUME_IND消息不包含CS,PSresume结果，此时按照恢复成功生成RESUME消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_NET_RAT_TYPE_LTE ,&stResumeIndMsg);

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF状态
              等待LMM的SUSPEND_REL_CNF消息超时的处理
 输入参数  : ulEventType:消息类型
             pstMsg:等待LMM_MMC_SUSPEND_REL_CNF超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 回复InterSysCellResel执行结果 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitLSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND状态
              收到MMCMMC_ABORT_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月15日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*停止保护定时器 TI_NAS_MMC_WAIT_LMM_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    /* 回复InterSysCellResel执行结果 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInfoChangeNotify_InterSysCellResel_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND状态
              收到LMM发送的替换入口消息的接口
 输入参数  : ulEventType:消息类型
             pstMsg:ID_LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月26日
    作    者   : z00234330
    修改内容   : 新生成函数
  2.日    期   : 2013年3月31日
    作    者   : y00176023
    修改内容   : DSDS GUNAS II项目:发送RAT变化给MM
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmSuspendInfoChangeNotify_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU *pstSuspendInfoChangeNotifyMsg;
    NAS_MMC_ENTRY_MSG_STRU                  *pstEntryMsg;
    LMM_MMC_SUSPEND_IND_STRU                *pstSuspendIndMsg;

    pstSuspendInfoChangeNotifyMsg   = (LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU*)pstMsg;


    if ( LMM_MMC_SUSPEND_RAT_INFO_CHANGE != pstSuspendInfoChangeNotifyMsg->ulInfoType)
    {
        return VOS_TRUE;
    }

    pstEntryMsg     = NAS_MMC_GetCurrEntryMsg();

    pstSuspendIndMsg = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

    if ( LMM_MMC_RAT_CHANGE_G2W == pstSuspendInfoChangeNotifyMsg->ulRatChangeType )
    {
        pstSuspendIndMsg->ulSysChngDir = MMC_LMM_SYS_CHNG_DIR_L2W;

        /*发送变化消息给mm*/
        NAS_MMC_SndMmRatChangeInd(NAS_MML_NET_RAT_TYPE_WCDMA);
    }
    else if ( LMM_MMC_RAT_CHANGE_W2G == pstSuspendInfoChangeNotifyMsg->ulRatChangeType )
    {
        pstSuspendIndMsg->ulSysChngDir = MMC_LMM_SYS_CHNG_DIR_L2G;

        /*发送变化消息给mm*/
        NAS_MMC_SndMmRatChangeInd(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        ;
    }
    return VOS_TRUE;
}


#endif

/* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if   (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvCmmcaResumeInd_InterSysCellResel_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND状态
              收到CMMCA的RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_CMMCA_MMC_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvCmmcaResumeInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 停止MMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CMMCA_RESUME_IND);

    /* 重选到CDMA，设置当前的3GPP的接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 重选到CDMA，设置当前未驻留 */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_HRPD);

    /* 给MM/GMM发送的resume ind消息中指示恢复方为HRPD */
    stResumeIndMsg.ucCsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucPsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucResumeOrigen   = MMC_RESUME_ORIGEN_HRPD;

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitCmmcaResumeIndExpired_InterSysCellResel_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND状态
              收到TI_NAS_MMC_WAIT_CMMCA_RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_CMMCA_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月19日
    作    者   : s00246516
    修改内容   : 新生成函数
  2.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitCmmcaResumeIndExpired_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitCmmcaResumeIndExpired_InterSysCellResel_WaitAsResumeInd:ENTERED");

    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_CMMCA_RESUME_IND_EXPIRED);

    return VOS_TRUE;
}
#endif
/* Added by s00246516 for L-C互操作项目, 2014-01-27, End */


/*****************************************************************************
 函 数 名  : NAS_MMC_SndSuspendRelReq_InterSysCellResel
 功能描述  : 根据不同的接入技术，给接入层或LMM发送SUSPEND_REL_REQ
 输入参数  : enRat
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月21日
    作    者   : s00217060
    修改内容   : 新生成函数

  1.日    期   : 2014年3月13日
    作    者   : s00261364
    修改内容   : 异系统重选过程中收到detach req,通知LTE suspend时,状态迁移错误
*****************************************************************************/
VOS_VOID NAS_MMC_SndSuspendRelReq_InterSysCellResel(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel(VOS_TRUE);

    switch (enRat)
    {
       case NAS_MML_NET_RAT_TYPE_WCDMA :
            /* 给WRR发送RRMM_SUSPEND_REL_REQ */
            NAS_MMC_SndAsSuspendRelReq(WUEPS_PID_WRR);

            /* 迁移状态到等待WAS的SUSPEND_REL_CNF */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF);

            /* 启相应的保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM :
            /* 给GAS发送RRMM_SUSPEND_REL_REQ */
            NAS_MMC_SndAsSuspendRelReq(UEPS_PID_GAS);

            /* 迁移状态到等待GAS的SUSPEND_REL_CNF */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SUSPEND_REL_CNF);

            /* 启相应的保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF_LEN);

            break;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE :
            /* 给LMM发送RRMM_SUSPEND_REL_REQ */
            NAS_MMC_SndLmmSuspendRelReq();

            /* Modified by s00261364 for L-C互操作项目, 2014-3-13, begin */
            /* 迁移状态到等待LMM的SUSPEND_REL_CNF */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF);

            /* 启相应的保护定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN);
            /* Modified by s00261364 for L-C互操作项目, 2014-3-13, end */

            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendRelReq_InterSysCellResel: Rat not support.");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel
 功能描述  : 根据不同的接入技术，给接入层或LMM发送SUSPEND_REL_REQ
 输入参数  : enRat
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月21日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2014年5月20日
    作    者   : z00161729
    修改内容   : DTS201405090133:给lnas suspend rel req和gu resume ind消息对冲时mmc未处理缓存导致后续退状态机处理缓存主动复位
*****************************************************************************/
VOS_VOID NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
       case NAS_MML_NET_RAT_TYPE_WCDMA :

            /* 停WAS的保护定时器 */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM :

            /* 停GAS的保护定时器 */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF);

            break;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE :
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel: Rat not support.");
            break;
    }

    return;
}


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))


VOS_UINT32 NAS_MMC_RcvMsccInterSysHrpdNtf_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 停止TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF);

    /* 重选或重定向到CDMA，设置当前的3GPP的接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 重选或重定向到CDMA，设置当前未驻留 */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_HRPD);

    /* 给MM/GMM发送的resume ind消息中指示恢复方为HRPD */
    stResumeIndMsg.ucCsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucPsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucResumeOrigen   = MMC_RESUME_ORIGEN_HRPD;

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvTiWaitMsccInterSysHrpdNtfExpired_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMsccInterSysHrpdNtfExpired_InterSysCellResel_WaitAsResumeInd:ENTERED");

    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_EXPIRED);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccInterSysHrpdNtf_InterSysCellResel_WaitAsSuspendRelCnf
 功能描述  : MMC在NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF状态
              收到MSCC的异系统变换到HRPD消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:ID_MSCC_MMC_INTERSYS_HRPD_NTF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月5日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccInterSysHrpdNtf_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 对冲场景，刚向接入层发完MMC_LMM_SUSPEND_REL_REQ,就收到MSCC的异系统变换到HRPD的指示,
       此时LTE变为从模,无suspend rel确认回复,到了HRPD后当成HRPD的恢复流程处理 */

    RRMM_RESUME_IND_ST                  stResumeIndMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    /* 停等待SUSPEND_REL_CNF消息的定时器 */
    NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(enRatType);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 重选或重定向到CDMA，设置当前未驻留 */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_HRPD);

    /* 给MM/GMM发送的resume ind消息中指示恢复方为HRPD */
    stResumeIndMsg.ucCsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucPsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucResumeOrigen   = MMC_RESUME_ORIGEN_HRPD;

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


#endif

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
Function Name   :   NAS_MMC_RcvLmmResumeInd_InterSysCellResel_Init
Description     :   CL mode,HRPD Reselct LTE, MMC Recive LMM_MMC_RESUME_IND，wait LMM_MMC_SYSINFO_INF_IND
Input parameters:   ulEventType: the Event type
                :   pstMsg     : the LMM_MMC_RESUME_IND message
Outout parameters:  None
Return Value    :
Modify History:
    1)  Date    :   2015-06-06
        Author  :   l00324781
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCellResel_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

    /* 向LMM返回响应消息 */
    NAS_MMC_SndLmmResumeNotify();

    /* 将状态迁移*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND);

    /* 启动等待MM回复定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

    return VOS_TRUE;
}
#endif


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


