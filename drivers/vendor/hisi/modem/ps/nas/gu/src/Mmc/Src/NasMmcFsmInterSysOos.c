/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmInterSysOos.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年07月27日
  最近修改   :
  功能描述   : 接入层重选时动作表
  函数列表   :
  修改历史   :
  1.日    期   : 2011年07月27日
    作    者   : w00176964
    修改内容   : 创建文件

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
#include "NasMmcFsmInterSysOos.h"
#include "NasMmcFsmInterSysOosTbl.h"
#include "NasMmcFsmInterSysOos.h"
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

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_OOS_C
/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSuspendInd_InterSysOos_Init
 功能描述  : 在intersysoos的INIT状态,收到was的RRMM_SUSPEND_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_SUSPEND_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysOos_Init(
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
    NAS_MMC_SetSuspendRspFlag_InterSysOos(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysOos(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_SUSPEND_RSP);

    /* 启动等待MM回复定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmSuspendRsp_InterSysOos_WaitMmSuspendRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_InterSysOos_RSP状态
              收到MMCGMM_Suspend_RSP消息的处理
 输入参数  :ulEventType:消息类型
            pstmsg:MMCMM_Suspend_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年04月24日
    作    者   : j00174725
    修改内容   : DSDS(接入层修改定时器长度) DTS2015042702414
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysOos_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* 标记已收到GMM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysOos( NAS_MMC_GMM_SUSPEND_RSP_FLG );

    /* 未收齐GMM,MM的SUSPNED_RSP,返回继续等待 */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysOos() )
    {
        return VOS_TRUE;
    }

    /* 停止定时器MMC_WAIT_NAS_SUSPEND_RSP_TIMER */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* 向接入层发送挂起成功 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* 将MMC的状态置成SUSPEND:NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsOosResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmSuspendRsp_InterSysOos_WaitMmSuspendRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_InterSysOos_RSP状态
              收到MMCMM_Suspend_RSP消息的处理
 输入参数  :ulEventType:消息类型
            pstmsg:MMCMM_Suspend_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年04月24日
    作    者   : j00174725
    修改内容   : DSDS(接入层修改定时器长度) DTS2015042702414
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysOos_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* 标记已收到MM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysOos( NAS_MMC_MM_SUSPEND_RSP_FLG );

    /* 未收齐GMM,MM的SUSPNED_RSP，返回继续等待 */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysOos() )
    {
        return VOS_TRUE;
    }

    /* 停止定时器MMC_WAIT_NAS_SUSPEND_RSP_TIMER */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* 向接入层发送挂起成功 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* 将MMC的状态置成SUSPEND:NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsOosResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysOos_WaitMmSuspendRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_InterSysOos_RSP状态
              收到TI_NAS_MMC_WAIT_MM_Suspend_RSP_TIMER消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_MM_Suspend_RSP_TIMER消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysOos_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysOos_WaitMmSuspendRsp:ENTERED");

    /* 向接入层回复挂起失败 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 向MM/GMM进行恢复 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出状态机*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasResumeInd_InterSysOos_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND状态
              收到WAS:RRMM_RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2012年9月11日
    作    者   : z40661
    修改内容   : DTS2012090505066:异系统回退信号门限上报不正确
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysOos_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* 停止MMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* 清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);


    /* 生成RESUME消息 */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysOos_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND状态
              收到TI_NAS_MMC_WAIT_AS_RESUME_IND_TIMER消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_AS_RESUME_IND_TIMER消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                  以供MM层调用，进行软复位。
  3.日    期   : 2014年2月18日
    作    者  :  w00242748
    修改内容  :  DTS2014021803515:复位时明确是收到哪个接入技术的异常消息导致的。

  4.日    期   : 2015年3月11日
    作    者   : wx270776
    修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysOos_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysOos_WaitAsResumeInd:ENTERED");

    /* 调用om接口,上电复位 */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_WAS_WAIT_RESUME_IND_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_GAS_WAIT_RESUME_IND_EXPIRED);
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
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitAsResumeInd
 功能描述  : 在NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND时,收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMMC_ABORT_FSM_REQ消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止TI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    /* 向当前AS发送 RRMM_SUSPEND_REL_REQ */
    if ( NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndAsSuspendRelReq(WUEPS_PID_WRR);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitAsResumeInd:could not support current rat!");

        return VOS_FALSE;
    }

    /* 迁移状态到等待SUSPEND_REL_CNF */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SUSPEND_REL_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitAsResumeInd
 功能描述  : 在NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND时,收到RRMM_REL_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月29日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年03月23日
    作    者   : l00130025
    修改内容   : DTS2012031604090,收到WRR的Rel_ind时没有设置RAT，导致恢复ResumeRsp错误
  3.日    期   : 2012年6月18日
    作    者   : l00171473
    修改内容   : DTS2012051104124, 无需判断原因值，收到rel ind，认为流程结束，
                 代表WAS恢复，即等同WAS发送了resume ind
  4.日    期   : 2012年6月20日
    作    者   : l00171473
    修改内容   : DTS2012062002706, OOS状态机收到REL IND时需停止保护定时器

  5.日    期   : 2012年9月11日
    作    者   : z40661
    修改内容   : DTS2012090505066:异系统回退信号门限上报不正确
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 无需判断原因值 */


    /* 停止TI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* 清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* 生成RESUME消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_GMM_RESUME_RSP_FLG);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf
 功能描述  : NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SUSPEND_REL_CNF状态下处理收到WAS发送的suspend_rel_cnf消息
 输入参数  : ulEventType:消息类型
             pstMsg:收到WAS发送的suspend_rel_cnf消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年04月07日
    作    者   : l00130025
    修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
  3.日    期   : 2013年07月23日
    作    者   : l65478
    修改内容   : 问题单号:DTS2013071809030,收到此消息后没有立刻处理SYSCFG,导致SYSCFG设置时间较长
  4.日    期   : 2014年5月31日
    作    者   : y00245242
    修改内容   : 修改服务状态上报
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);

    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 向MM/GMM进行恢复 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, begin */
    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, end */

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    /* 根据接口约定,当WRR发送RRMM_SUSPEND_REL_CNF时,已经进入了IDLE,但是WRR不会向MM/GMM发送连接释放指示,
       所以MMC需要本地清除连接标志 */
    NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf
 功能描述  : NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SUSPEND_REL_CNF状态下处理收到WAS发送的suspend_rel_cnf超时消息
 输入参数  : ulEventType:消息类型
             pstMsg:收到WAS发送的suspend_rel_cnf超时消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年04月07日
    作    者   : l00130025
    修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
  3.日    期   : 2014年5月31日
    作    者   : y00245242
    修改内容   : 修改服务状态上报
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf:ENTERED");

    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 向MM/GMM进行恢复 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, begin */
    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, end */

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasResumeInd_InterSysOos_WaitWasSuspendRelCnf
 功能描述  : MMC在NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SUSPEND_REL_CNF状态
              收到WAS:RRMM_RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月16日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 对冲场景的处理：刚给接入层发过RRMM_SUSPEND_REL_REQ就收到接入层的RRMM_RESUME_IND
       按照收到RRMM_RESUME_IND消息处理，后续收到RRMM_SUSPEND_REL_CNF丢弃 */

    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* 停止MMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* 清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);


    /* 生成RESUME消息 */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmResumeRsp_InterSysOos_WaitMmResumeRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP状态
              收到MMCGMM_RESUME_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCGMM_RESUME_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年7月15日
    作    者   : z00161729
    修改内容   : DTS2013062406563:WAS连接态OOS,T305运行期间只会在本系统下搜等效plmn，
                 不会驻留到本系统其他网络，也不会异系统下进行搜网，导致无法很快在软银网络注册，nas配合修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysOos_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_ClearResumeRspFlag_InterSysOos( NAS_MMC_GMM_RESUME_RSP_FLG );

    /* 未收齐GMM的MMCGMM_RESUME_RSP和 MM的MMCMM_RESUEM_RSP,返回继续等待 */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysOos() )
    {
        return VOS_TRUE;
    }

    /* 如果已经收齐,停止MMC_WAIT_MM_RESUME_RSP_TIMER */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */

    /* 发送suspend状态机完成消息 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmResumeRsp_InterSysOos_WaitMmResumeRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP状态
              收到MMCMM_RESUME_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:MMCMM_RESUME_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年11月21日
    作    者   : z00161729
    修改内容   : 支持cerssi和nmr
  3.日    期   : 2013年7月15日
    作    者   : z00161729
    修改内容   : DTS2013062406563:WAS连接态OOS,T305运行期间只会在本系统下搜等效plmn，
                 不会驻留到本系统其他网络，也不会异系统下进行搜网，导致无法很快在软银网络注册，nas配合修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysOos_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_ClearResumeRspFlag_InterSysOos( NAS_MMC_MM_RESUME_RSP_FLG );

    /* 未收齐GMM的MMCGMM_RESUME_RSP和 MM的MMCMM_RESUEM_RSP,返回继续等待 */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysOos() )
    {
        return VOS_TRUE;
    }

    /* 如果已经收齐,停止MMC_WAIT_MM_RESUME_RSP_TIMER */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */

    /* 发送suspend状态机完成消息 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysOos_WaitMmResumeRsp
 功能描述  : MMC在NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP状态
              收到TI_NAS_MMC_WAIT_MM_RESUME_RSP_TIMER消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:TI_NAS_MMC_WAIT_MM_RESUME_RSP_TIMER消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月27日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年7月15日
    作    者   : z00161729
    修改内容   : DTS2013062406563:WAS连接态OOS,T305运行期间只会在本系统下搜等效plmn，
                 不会驻留到本系统其他网络，也不会异系统下进行搜网，导致无法很快在软银网络注册，nas配合修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysOos_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysOos_WaitMmResumeRsp:ENTERED");

    /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */

    /* 发送suspend状态机完成消息 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/* oos状态机不再有等系统消息状态，删除g_astNasInterSysOosWaitWSysInfoIndActTbl，
   收到resume ind消息就退状态机 */

/* NAS_MMC_UpdateSearchedPlmnListInfo_Oos由于list、bg、搜网状态机都需要使用移至NasMmcCommFunc.c */

/* oos状态机不再有等系统消息状态，删除NAS_MMC_RcvWasSuspendInd_InterSysOos_WaitWasSysInfoInd/
   NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitWasSysInfoInd收到resume ind消息就退状态机 */


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitWasSysInfoInd
 功能描述  : 在NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SYSINFO_IND时,收到RRMM_REL_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:RRMM_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月05日
    作    者   : w00166186
    修改内容   : 新生成函数
  2.日    期   : 2012年6月18日
    作    者   : l00171473
    修改内容   : DTS2012051104124, 无需判断原因值，收到rel ind，认为流程结束，
                 代表WAS恢复，即等同WAS发送了SUSPEND REL CNF.
  3.日    期   : 2012年6月20日
    作    者   : l00171473
    修改内容   : DTS2012062002706, OOS状态机收到REL IND时需停止保护定时器
  4.日    期   : 2014年5月31日
    作    者   : y00245242
    修改内容   : 修改服务状态上报
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 无需判断原因值 */


    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);
    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 向MM/GMM进行恢复 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, begin */
    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-5-31, end */

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

