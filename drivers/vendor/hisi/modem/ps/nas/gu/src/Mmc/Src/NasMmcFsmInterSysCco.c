/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmInterSysCco.c
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2011年06月29日
  最近修改   :
  功能描述   : InterSysCco时状态处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年06月29日
    作    者   : W00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcCtx.h"
#include "NasMmcTimerMgmt.h"
#include "Nasrrcinterface.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndLmm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcFsmInterSysCco.h"
#include "NasMmcFsmInterSysCcoTbl.h"
#include "NasMmcProcSuspend.h"
#include "NasComm.h"
#include "NasMmlLib.h"
#include "NasMmcProcRegRslt.h"
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

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_CCO_C
/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/


/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSuspendInd_InterSysCco_Init
 功能描述  : 在InterSysCco的INIT状态,收到RRMM_SUSPEND_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstmsg:收到WAS的RRMM_SUSPEND_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年06月01日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysCco_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstCcoSuspendMsg;

    pstCcoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMC只在以下三个场景中用原语MMC_LMM_EPLMN_NOTIFY_REQ通知LMM:3异系统变换中，GU发生挂起，目标系统为LTE时 */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstCcoSuspendMsg->ucSuspendDestination )
    {
        /* 通知LTE等效PLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(pstCcoSuspendMsg);

    /* 设置MM挂起回复标记:*/
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(pstCcoSuspendMsg);

    /* 设置GMM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP);

    /* 启动等待MM回复定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasSuspendInd_InterSysCco_Init
 功能描述  : 在InterSysCco的INIT状态,收到Gas的RRMM_SUSPEND_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstmsg:收到GAS的RRMM_SUSPEND_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年06月01日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGasSuspendInd_InterSysCco_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstCcoSuspendMsg;

    pstCcoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMC只在以下三个场景中用原语MMC_LMM_EPLMN_NOTIFY_REQ通知LMM:3异系统变换中，GU发生挂起，目标系统为LTE时 */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstCcoSuspendMsg->ucSuspendDestination )
    {
        /* 通知LTE等效PLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(pstCcoSuspendMsg);

    /* 设置MM挂起回复标记:*/
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(pstCcoSuspendMsg);

    /* 设置GMM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP);

    /* 启动等待MM回复定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmSuspendRsp_InterSysCco_WaitMmSuspendRsp
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_MM_SUSPEND_RSP状态
              收到MMCMM_SUSPEND_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCMM_SUSPEND_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年04月24日
   作    者   : j00174725
   修改内容   : DSDS(接入层修改定时器长度) DTS2015042702414
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysCco_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* 标记已收到MM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCco( NAS_MMC_MM_SUSPEND_RSP_FLG );

    /* 未收齐GMM,MM的SUSPNED_RSP，返回继续等待 */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCco() )
    {
        return VOS_TRUE;
    }

    /* 停止定时器TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* 向接入层发送挂起成功 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* 将MMC的状态置成SUSPEND:NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmSuspendRsp_InterSysCco_WaitMmSuspendRsp
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_MM_SUSPEND_RSP状态
              收到MMCGMM_SUSPEND_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCGMM_SUSPEND_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年04月24日
   作    者   : j00174725
   修改内容   : DSDS(接入层修改定时器长度) DTS2015042702414
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysCco_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* 标记已收到GMM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCco( NAS_MMC_GMM_SUSPEND_RSP_FLG );

    /* 未收齐GMM,MM的SUSPNED_RSP,返回继续等待 */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCco() )
    {
        return VOS_TRUE;
    }

    /* 停止定时器TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* 向接入层发送挂起成功 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* 将MMC的状态置成SUSPEND:NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRsp
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_MM_SUSPEND_RSP状态
              收到TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_TIMER消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_TIMER消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRsp:ENTERED");

    /* 向接入层发送挂起失败 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 向MM/GMM进行恢复 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出状态机*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasResumeInd_InterSysCco_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_AS_RESUME_IND状态
              收到WAS:RRMM_RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月1日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整

 3.日    期   : 2012年9月11日
   作    者   : z40661
   修改内容   : DTS2012090505066:异系统回退信号门限上报不正确
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* 停止MMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* 异系统到其他模式需要清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* 生成RESUME消息 */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasResumeInd_InterSysCco_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_AS_RESUME_IND状态
              收到GAS:RRMM_RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月1日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整

 3.日    期   : 2012年9月11日
   作    者   : z40661
   修改内容   : DTS2012090505066:异系统回退信号门限上报不正确
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* 停止MMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* 异系统到其他模式清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);

    /* 生成RESUME消息 */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_AS_RESUME_IND状态
              收到TI_NAS_MMC_WAIT_AS_RESUME_IND_TIMER消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_AS_RESUME_IND_TIMER消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
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
   修改内容   : DTS2015011212939: 复位时增加复位场景

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeInd:ENTERED");

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
 函 数 名  : NAS_MMC_RcvRrMmRelInd_InterSysCco_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_AS_RESUME_IND状态
              收到RRMM_REL_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_REL_IND消息的首地址
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
 3.日    期   : 2012年5月24日
   作    者   : l00171473
   修改内容   : DTS2012051104124, relind处理修改

 4.日    期   : 2012年9月11日
   作    者   : z40661
   修改内容   : DTS2012090505066:异系统回退信号门限上报不正确
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmRelInd_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRelInd = VOS_NULL_PTR;
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    pstRelInd      = (RRMM_REL_IND_STRU*)pstMsg;


    /* 释放原因为Utran release时, 需要继续重选流程, 继续等待resume ind,
       其它认为流程结束, 代表WAS恢复, 即等同WAS发送了resume ind */
    if (RRC_REL_CAUSE_UTRAN_RELEASE == pstRelInd->ulRelCause)
    {
        return VOS_TRUE;
    }

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* 异系统到其他模式,清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);


    /* 停止TI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    /* 构造resume消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* 设置GMM等待标识 */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* 设置MM等待标识 */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP);

    /* 启动定时器TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRsp
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_MM_RESUME_RSP状态
              收到MMCGMM_RESUME_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCGMM_RESUME_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月12日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整:调整等待WAS系统消息时长
 3.日    期   : 2012年11月21日
   作    者   : z00161729
   修改内容   : 支持cerssi和nmr

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;

    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    /* 状态机上下文标记已收到MMCGMM_RESUME_RSP */
    NAS_MMC_ClearResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 判断是否收齐GMM的MMCGMM_RESUME_RSP和 MM的MMCMM_RESUEM_RSP */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCco() )
    {
        return VOS_TRUE;
    }

    /* 如果已经收齐,停止TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */

    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND);

            /* WAS的回退流程中，上报系统消息时间较长，调整等待系统消息时长 */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:

            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRsp:Unexpected rat type!");
            break;
    }

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRsp
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_MM_RESUME_RSP状态
              收到MMCMM_RESUME_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCMM_RESUME_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W001176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月12日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整:调整等待WAS系统消息时长
 3.日    期   : 2012年11月21日
   作    者   : z00161729
   修改内容   : 支持cerssi和nmr
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;

    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    /* 状态机上下文标记已收到MMCMM_RESUME_RSP */
    NAS_MMC_ClearResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 未收齐GMM的MMCGMM_RESUME_RSP和 MM的MMCMM_RESUEM_RSP,返回继续等待 */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCco() )
    {
        return VOS_TRUE;
    }

    /* 如果已经收齐,停止TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */

    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND);

            /* WAS的回退流程中，上报系统消息时间较长，调整等待系统消息时长 */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRsp:Unexpected rat type!");
            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRsp
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_MM_RESUME_RSP状态
              收到TI_NAS_MMC_WAIT_MM_RESUME_RSP_TIMER消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_MM_RESUME_RSP_TIMER消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月12日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整:调整等待WAS系统消息时长
 3.日    期   : 2012年11月21日
   作    者   : z00161729
   修改内容   : 支持cerssi和nmr

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;

    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRsp:ENTERED");

    /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */

    /* 清除MM/GMM的等待恢复标记 */
    NAS_MMC_ClearAllResumeRspFlag_InterSysCco();

    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND);

            /* WAS的回退流程中，上报系统消息时间较长，调整等待系统消息时长 */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRsp:Unexpected Rat type!");
            break;
    }

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysInfoInd_InterSysCco_WaitWSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND状态
              收到RRMM_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_SYS_INFO_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 3.日    期   : 2012年8月14日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题,禁止LTE漫游
 4.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 5.日    期   : 2013年9月14日
   作    者   : w00167002
   修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 在NAS_MMC_SndMmGsmSysInfoInd函数中，如果是用户指定搜网，则将FORBFLG设置为null，
                 将此耦合去除；
                 在选网状态机识别出是否是用户指定搜网，并配置正确的ulForbiddenFlg标志；

 6.日    期   : 2014年1月18日
   作    者   : z00234330
   修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
               此处判断并没有判断plmnid是否有效
 7.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitWSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulParentEventType;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */
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

    /* 获取旧的网络类型 */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

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

     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /*转发系统消息通知 给 MM/GMM ,非指定搜网过程*/
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

    /* 如果挂起模式与当前模式一样,直接退出当前状态机 */
    if ( enOldNtType == NAS_MML_GetCurrNetRatType())
    {
        /*发送状态机失败结果*/
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 将MMC的状态置成NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND);

    /* 启动保护定时器TI_NAS_MMC_WAIT_EST_IND */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EST_IND, TI_NAS_MMC_WAIT_EST_IND_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAreaLostInd_InterSysCco_WaitWSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND状态
              收到RRMM_AREA_LOST_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_AREA_LOST_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月20日
   作    者   : W00176964
   修改内容   : 新生成函数

 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep

 3.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求

 4.日    期   : 2014年4月30日
   作    者   : s00261364
   修改内容   : ecall项目修改服务状态上报
 5.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCco_WaitWSysInfoInd(
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

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, end */

    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );


    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, end */

     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */



    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysInfoInd_InterSysCco_WaitGSysInfoInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_GAS_SYS_INFO_IND状态
              收到GRRMM_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:GRRMM_SYS_INFO_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 3.日    期   : 2012年8月14日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题,禁止LTE漫游
 4.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 5.日    期   : 2013年9月14日
   作    者   : w00167002
   修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 在NAS_MMC_SndMmGsmSysInfoInd函数中，如果是用户指定搜网，则将FORBFLG设置为null，
                 将此耦合去除；
                 在选网状态机识别出是否是用户指定搜网，并配置正确的ulForbiddenFlg标志；
 6.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式

 7.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitGSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulParentEventType;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

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

    /* 获取旧的网络类型 */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

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

     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

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

    /* 如果挂起模式与当前模式一样,直接退出当前状态机 */
    if ( enOldNtType == NAS_MML_GetCurrNetRatType())
    {
        /*发送状态机失败结果*/
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 将MMC的状态置成NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND);

    /* 启动保护定时器TI_NAS_MMC_WAIT_EST_IND */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EST_IND, TI_NAS_MMC_WAIT_EST_IND_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAreaLostInd_InterSysCco_WaitGSysInfoInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND状态
              收到RRMM_AREA_LOST_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_AREA_LOST_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月20日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep

 3.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
 4.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCco_WaitGSysInfoInd(
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

     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_GAS_SYS_INFO_IND状态
              收到TI_NAS_MMC_WAIT_GAS_SYS_INFO消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_GAS_SYS_INFO消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_GAS_SYS_INFO_EXP);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_WAS_SYS_INFO_IND状态
              收到TI_NAS_MMC_WAIT_WAS_SYS_INFO消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_WAS_SYS_INFO消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_WAS_SYS_INFO_EXP);
    }
    else
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_TAS_SYS_INFO_EXP);
    }


    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmRrConnInfoInd_InterSysCco_WaitEstInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_Est_Ind状态
             收到MMCMM_RR_CONN_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCMM_RR_CONN_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmRrConnInfoInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_RR_CONN_INFO_IND_STRU        *pstRrconnInfo;

    pstRrconnInfo = (MMCMM_RR_CONN_INFO_IND_STRU*)pstMsg;

    switch(pstRrconnInfo->ulRrConnFlg)
    {
        case MMC_MM_RR_CONN_ESTING:

            /* 正在建链，继续等待 */
            NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvMmRrConnInfoInd_InterSysCco_WaitEstInd:establishing the cs connection!");
            break;
        case MMC_MM_RR_CONN_ESTED:

            /* 停止保护定时器  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /*发送状态机成功结果*/
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* 建连接成功，CCO流程结束，退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            break;
        case MMC_MM_RR_CONN_ABSENT:

            /* 停止保护定时器  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /* 建链失败,回退,将MMC的状态置成NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND, TI_NAS_MMC_WAIT_AS_SUSPEND_IND_LEN);

            break;
        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvMmRrConnInfoInd_InterSysCco_WaitEstInd:Unexpected RR conn status!");
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmSignalingStatusInd_InterSysCco_WaitEstInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_Est_Ind状态
              收到MMCGMM_SIGNALING_STATUS_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCGMM_SIGNALING_STATUS_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年5月19日
   作    者   : b00269685
   修改内容   : G下回退修改

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvGmmSignalingStatusInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_SIGNALING_STATUS_IND_STRU    *pstSignalStatusInfo;

    pstSignalStatusInfo = (MMCGMM_SIGNALING_STATUS_IND_STRU*)pstMsg;


    switch(pstSignalStatusInfo->ulSignalingSts)
    {
        case MMC_GMM_SIGNALING_STATUS_ESTING:

             /* PS正在建链,等待*/
             NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvGmmSignalingStatusInd_InterSysCco_WaitEstInd:establishing the ps connection!");

             break;
        case MMC_GMM_SIGNALING_STATUS_PRESENT:

            /* 停止保护定时器  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /*发送状态机成功结果*/
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* 建连接成功，CCO流程结束，退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            break;

        case MMC_GMM_SIGNALING_STATUS_ABSENT:

            /* 停止保护定时器  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /* 建链失败,回退,将MMC的状态置成NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND, TI_NAS_MMC_WAIT_AS_SUSPEND_IND_LEN);

            break;
        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvGmmSignalingStatusInd_InterSysCco_WaitEstInd:Unexpected signaling status!");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitEstCnfExpired_InterSysCco_WaitEstInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_Est_Ind状态
              收到TI_NAS_MMC_WAIT_Est_Ind消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_Est_Ind消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitEstIndExpired_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitEstIndExpired_InterSysCco_WaitEstInd:Entered");

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmTbfRelInd_InterSysCco_WaitEstInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_Est_Ind状态
              收到MMCGMM_TBF_REL_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCGMM_TBF_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmTbfRelInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器  TI_NAS_MMC_WAIT_EST_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

    /* 将MMC的状态置成NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK);

    /* 启动保护定时器 TI_NAS_MMC_WAIT_AS_SUSPEND_IND*/
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND, TI_NAS_MMC_WAIT_AS_SUSPEND_IND_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSuspendInd_InterSysCco_WaitEstInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_Est_Ind状态
              收到RRMM_SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_SUSPEND_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年06月01日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasSuspendInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstCcoSuspendMsg;

    pstCcoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* 停止保护定时器  TI_NAS_MMC_WAIT_EST_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMC只在以下三个场景中用原语MMC_LMM_EPLMN_NOTIFY_REQ通知LMM:3异系统变换中，GU发生挂起，目标系统为LTE时 */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstCcoSuspendMsg->ucSuspendDestination )
    {
        /* 通知LTE等效PLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(pstCcoSuspendMsg);

    /* 设置MM挂起回复标记:*/
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(pstCcoSuspendMsg);

    /* 设置GMM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK);

    /* 启动等待MM回复定时器TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasSuspendInd_InterSysCco_WaitEstInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_Est_Ind状态
              收到RRMM_SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCGMM_TBF_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年06月01日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasSuspendInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstCcoSuspendMsg;

    pstCcoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* 停止保护定时器  TI_NAS_MMC_WAIT_EST_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMC只在以下三个场景中用原语MMC_LMM_EPLMN_NOTIFY_REQ通知LMM:3异系统变换中，GU发生挂起，目标系统为LTE时 */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstCcoSuspendMsg->ucSuspendDestination )
    {
        /* 通知LTE等效PLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(pstCcoSuspendMsg);

    /* 设置MM挂起回复标记:*/
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(pstCcoSuspendMsg);

    /* 设置GMM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK);

    /* 启动等待MM回复定时器TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSuspendInd_InterSysCco_WaitAsSuspendIndFallBack
 功能描述  : 在InterSysCco的NAS_MMC_InterSysCco_STA_WAIT_AS_SUSPEND_IND_FALLBACK状态,收到was的RRMM_SUSPEND_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstmsg:收到WAS的RRMM_SUSPEND_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年06月01日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysCco_WaitAsSuspendIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstCcoSuspendMsg;

    pstCcoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* 停止保护定时器  TI_NAS_MMC_WAIT_AS_SUSPEND_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND);

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMC只在以下三个场景中用原语MMC_LMM_EPLMN_NOTIFY_REQ通知LMM:3异系统变换中，GU发生挂起，目标系统为LTE时 */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstCcoSuspendMsg->ucSuspendDestination )
    {
        /* 通知LTE等效PLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(pstCcoSuspendMsg);

    /* 设置等待标识 */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(pstCcoSuspendMsg);

     /* 设置等待标识 */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK);

    /* 启动等待MM回复定时器TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasSuspendInd_InterSysCco_WaitAsSuspendIndFallBack
 功能描述  : 在InterSysCco的NAS_MMC_InterSysCco_STA_WAIT_AS_SUSPEND_IND_FALLBACK状态,收到GAS的RRMM_SUSPEND_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstmsg:收到GAS的RRMM_SUSPEND_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年06月01日
   作    者   : sunxibo /46746
   修改内容   : Added for V7R1 C50 CS/PS mode 1

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGasSuspendInd_InterSysCco_WaitAsSuspendIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstCcoSuspendMsg;

    pstCcoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* 停止保护定时器  TI_NAS_MMC_WAIT_AS_SUSPEND_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND);

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMC只在以下三个场景中用原语MMC_LMM_EPLMN_NOTIFY_REQ通知LMM:3异系统变换中，GU发生挂起，目标系统为LTE时 */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstCcoSuspendMsg->ucSuspendDestination )
    {
        /* 通知LTE等效PLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(pstCcoSuspendMsg);

    /* 设置MM挂起回复标记:*/
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(pstCcoSuspendMsg);

    /* 设置GMM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK);

    /* 启动等待MM回复定时器TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitAsSuspendIndExpired_InterSysCco_WaitAsSuspendIndFallBack
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_AS_SUSPEND_IND_FALLBACK状态
              收到TI_NAS_MMC_WAIT_As_Suspend_Ind_Expired消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_AS_SUSPEND_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendIndExpired_InterSysCco_WaitAsSuspendIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitAsSuspendIndExpired_InterSysCco_WaitAsSuspendIndFallBack:Entered");

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE,NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmSuspendRsp_InterSysCco_WaitMmSuspendRspFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK状态
              收到MMCMM_SUSPEND_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCMM_SUSPEND_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年04月24日
   作    者   : j00174725
   修改内容   : DSDS(接入层修改定时器长度) DTS2015042702414
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysCco_WaitMmSuspendRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* 状态机上下文标记已收到MMCMM_SUSPEND_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCco( NAS_MMC_MM_SUSPEND_RSP_FLG );

    /* 未收齐GMM,MM的SUSPNED_RSP，返回继续等待 */
    if (  NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCco()  )
    {
        return VOS_TRUE;
    }

    /* 停止定时器TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_StopTimer (TI_NAS_MMC_WAIT_MM_SUSPEND_RSP);

    /* 向接入层发送挂起成功 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* 将MMC的状态置成NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();

    /* 启动定时器TI_NAS_MMC_WAIT_AS_RESUME_IND */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmSuspendRsp_InterSysCco_WaitMmSuspendRspFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK状态
              收到MMCGMM_SUSPEND_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCGMM_SUSPEND_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年04月24日
   作    者   : j00174725
   修改内容   : DSDS(接入层修改定时器长度) DTS2015042702414
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysCco_WaitMmSuspendRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* 状态机上下文标记已收到MMCGMM_SUSPEND_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCco( NAS_MMC_GMM_SUSPEND_RSP_FLG );

    /* 未收齐GMM,MM的SUSPNED_RSP，返回继续等待 */
    if (  NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCco()  )
    {
        return VOS_TRUE;
    }

    /* 停止定时器TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* 向接入层发送挂起成功 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* 将MMC的状态置成NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();

    /* 启动定时器TI_NAS_MMC_WAIT_AS_RESUME_IND */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRspFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK状态
              收到TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_TIMER消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_TIMER消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRspFallBack:ENTERED");

    /* 向接入层发送挂起失败 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 向MM/GMM进行恢复 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE,NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出状态机*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasResumeInd_InterSysCco_WaitAsResumeIndFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK状态
              收到WAS:RRMM_RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月1日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCco_WaitAsResumeIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* 停止MMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* 清除小区信息以及信号量 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* 生成RESUME消息 */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK);

    /* 启动定时器TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasResumeInd_InterSysCco_WaitAsResumeIndFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK状态
              收到GAS:RRMM_RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月1日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCco_WaitAsResumeIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* 停止MMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);

    /* 清除小区信息以及信号量 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* 生成RESUME消息 */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK);

    /* 启动定时器TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeIndFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK状态
              收到TI_NAS_MMC_WAIT_AS_RESUME_IND_TIMER消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_AS_RESUME_IND_TIMER消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
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
   修改内容   : DTS2015011212939:复位时增加复位场景
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 异常打印 */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeIndFallBack:ENTERED");

    /* 调用om接口,上电复位 */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurRat) )
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
 函 数 名  : NAS_MMC_RcvRrMmRelInd_InterSysCco_WaitAsResumeIndFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK状态
             收到RRMM_REL_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_REL_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月05日
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
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmRelInd_InterSysCco_WaitAsResumeIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRelInd = VOS_NULL_PTR;
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    pstRelInd      = (RRMM_REL_IND_STRU*)pstMsg;


    /* 释放原因为Utran release时, 需要继续重选流程, 继续等待resume ind,
       其它认为流程结束, 代表WAS恢复, 即等同WAS发送了resume ind */
    if (RRC_REL_CAUSE_UTRAN_RELEASE == pstRelInd->ulRelCause)
    {
        return VOS_TRUE;
    }

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* 到异系统后清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }


    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* 停止TI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);


    /* 构造resume消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* 设置GMM等待标识 */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* 设置MM等待标识 */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK);

    /* 启动定时器TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRspFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK状态
              收到MMCGMM_RESUME_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCGMM_RESUME_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月12日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整:调整等待WAS系统消息时长
 3.日    期   : 2012年11月21日
   作    者   : z00161729
   修改内容   : 支持cerssi和nmr

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 状态机上下文标记已收到MMCGMM_RESUME_RSP */
    NAS_MMC_ClearResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 未收齐GMM的MMCGMM_RESUME_RSP和 MM的MMCMM_RESUEM_RSP，返回继续等待 */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCco() )
    {
        return VOS_TRUE;
    }

    /* 如果已经收齐,停止TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */

    /* 根据不同的网络类型迁移到不同的状态 */
    switch(NAS_MML_GetCurrNetRatType())
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRspFallBack:Unexpected Rat Type!");
            break;
    }

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRspFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK状态
              收到MMCMM_RESUME_RSP消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCMM_RESUME_RSP消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W001176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月12日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整:调整等待WAS系统消息时长
 3.日    期   : 2012年11月21日
   作    者   : z00161729
   修改内容   : 支持cerssi和nmr
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 状态机上下文标记已收到MMCMM_RESUME_RSP */
    NAS_MMC_ClearResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 未收齐GMM的MMCGMM_RESUME_RSP和 MM的MMCMM_RESUEM_RSP,返回继续等待 */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCco() )
    {
        return VOS_TRUE;
    }

    /* 如果已经收齐,停止TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */

    /* 根据不同的网络类型迁移到不同的状态 */
    switch(NAS_MML_GetCurrNetRatType())
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRspFallBack:Unexpected Rat Type!");
            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRspFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK状态
              收到TI_NAS_MMC_WAIT_MM_RESUME_RSP_TIMER消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_MM_RESUME_RSP_TIMER消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月12日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整:调整等待WAS系统消息时长
 3.日    期   : 2012年11月21日
   作    者   : z00161729
   修改内容   : 支持cerssi和nmr
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRspFallBack:ENTERED");

    /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */

    switch(NAS_MML_GetCurrNetRatType())
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK状态 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRspFallBack:Unexpected Rat Type!");
            break;
    }


    return VOS_TRUE;

}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysInfoInd_InterSysCco_WaitWSysInfoIndFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK状态
              收到RRMM_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_SYS_INFO_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 3.日    期   : 2012年8月14日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题,禁止LTE漫游
 4.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 5.日    期   : 2013年9月14日
   作    者   : w00167002
   修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 在NAS_MMC_SndMmGsmSysInfoInd函数中，如果是用户指定搜网，则将FORBFLG设置为null，
                 将此耦合去除；
                 在选网状态机识别出是否是用户指定搜网，并配置正确的ulForbiddenFlg标志；

 6.日    期   : 2014年1月18日
   作    者   : z00234330
   修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
               此处判断并没有判断plmnid是否有效

 7.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitWSysInfoIndFallBack(
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

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */

    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /*转发系统消息通知 给 MM/GMM ,非指定搜网过程*/
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

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAreaLostInd_InterSysCco_WaitWSysInfoIndFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK状态
              收到RRMM_AREA_LOST_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_AREA_LOST_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月24日
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
VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCco_WaitWSysInfoIndFallBack(
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

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysInfoInd_InterSysCco_WaitGSysInfoIndFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK状态
              收到GRRMM_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:GRRMM_SYS_INFO_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 3.日    期   : 2012年8月14日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题,禁止LTE漫游
 4.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 5.日    期   : 2013年9月14日
   作    者   : w00167002
   修改内容   : DTS2013090908249:开机用户指定搜网24003，CS注册被拒15，MM在LIMIT
                 状态，在选网状态机收到同一小区的SYSINFO后，通知MM当前没有FORB FLG,
                 导致MM发起循环注册；
                 在NAS_MMC_SndMmGsmSysInfoInd函数中，如果是用户指定搜网，则将FORBFLG设置为null，
                 将此耦合去除；
                 在选网状态机识别出是否是用户指定搜网，并配置正确的ulForbiddenFlg标志；
 6.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式

 7.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitGSysInfoIndFallBack(
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

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MSCC模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

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

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvAreaLostInd_InterSysCco_WaitGSysInfoIndFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK状态
              收到RRMM_AREA_LOST_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_AREA_LOST_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月24日
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
VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCco_WaitGSysInfoIndFallBack(
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
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoIndFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK状态
              收到TI_NAS_MMC_WAIT_GAS_SYS_INFO消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_GAS_SYS_INFO消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, bein */
    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_GAS_SYS_INFO_EXP);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoIndFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK状态
              收到TI_NAS_MMC_WAIT_WAS_SYS_INFO消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_WAS_SYS_INFO消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2014年04月4日
   作    者   : s00261364
   修改内容   : V3R360_eCall项目:服务状态上报到mmc
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_WAS_SYS_INFO_EXP);
    }
    else
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_TAS_SYS_INFO_EXP);
    }

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_InterSysCco_Init
 功能描述  : 在InterSysCco的INIT状态,收到LMM的ID_LMM_MMC_SUSPEND_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstmsg:收到LMM的ID_LMM_MMC_SUSPEND_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_InterSysCco_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg;
    RRMM_SUSPEND_IND_ST                 stSndSuspendMsg;

    pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 转换L的挂起消息为GU格式的 */
    NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stSndSuspendMsg);

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(&stSndSuspendMsg);

    /* 设置MM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(&stSndSuspendMsg);

    /* 设置GMM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP);

    /* 启动等待MM回复定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmResumeInd_InterSysCco_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_AS_RESUME_IND状态
              收到ID_LMM_MMC_RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:ID_LMM_MMC_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月1日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 停止TI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    /* 设置当前网络为LTE */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

    /* 由于L的RESUME_IND消息不包含CS,PSresume结果，此时按照恢复成功生成RESUME消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_NET_RAT_TYPE_LTE ,&stResumeIndMsg);

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* 设置GMM等待标识 */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送:NAS_MMC_SndMmResumeInd */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* 设置MM等待标识 */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP);

    /* 启动定时器TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAreaLostInd_InterSysCco_WaitAsSysInfoInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_LMM_SYS_INFO_IND状态
              收到ID_LMMM_MMC_AREA_LOST_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:ID_LMM_MMC_AREA_LOST_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2014年5月5日
   作    者   : w00242748
   修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                注册状态的上报。
 4.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_InterSysCco_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_AREA_LOST_IND_STRU                             *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];

    pstAreaLostInd = (LMM_MMC_AREA_LOST_IND_STRU*)pstMsg;

    /* 停止定时器*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 更新服务状态 */


     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */

    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 通知TAF当前的服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAreaLostInd_InterSysCco_WaitLSysInfoIndFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK状态
              收到ID_LMMM_MMC_AREA_LOST_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:ID_LMM_MMC_AREA_LOST_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年8月24日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2014年5月5日
   作    者   : w00242748
   修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                注册状态的上报。
 4.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_InterSysCco_WaitLSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_AREA_LOST_IND_STRU                             *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];

    pstAreaLostInd = (LMM_MMC_AREA_LOST_IND_STRU*)pstMsg;

    /* 停止定时器*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 更新服务状态 */


    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 通知TAF当前的服务状态 */
	/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */



    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysInfoInd_InterSysCco_WaitLSysInfoInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_LMM_SYS_INFO_IND状态
              收到ID_LMMM_MMC_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:ID_LMM_MMC_SYS_INFO_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月5日
   作    者   : W00176964
   修改内容   : V7R1 phase IV修改
 3.日    期   : 2012年4月18日
   作    者   : l00130025
   修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
 4.日    期   : 2012年4月28日
   作    者   : W00166186
   修改内容   : DTS2012042602593,MM没有保存当前驻留的PLMN，导致后续判断出错
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
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    /* 获取旧的网络类型 */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /*停止保护定时器 TI_NAS_MMC_WAIT_LMM_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

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

    /* 如果挂起模式与当前模式一样,直接退出当前状态机 */
    if ( enOldNtType == NAS_MML_GetCurrNetRatType())
    {
        /*发送状态机失败结果*/
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

        /* 退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 将MMC的状态置成NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND);

    /*启动保护定时器 TI_NAS_MMC_WAIT_EST_IND*/
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EST_IND, TI_NAS_MMC_WAIT_EST_IND_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_LMM_SYS_INFO_IND状态
              收到TI_NAS_MMC_WAIT_LMM_SYS_INFO消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_LMM_SYS_INFO消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2014年5月5日
   作    者   : w00242748
   修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                注册状态的上报。
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitAsSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 更新服务状态 */

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 通知TAF当前的服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_LNAS_SYS_INFO_EXP);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvSysInfoInd_InterSysCco_WaitLSysInfoIndFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK状态
              收到ID_LMMM_MMC_SYS_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:ID_LMM_MMC_SYS_INFO_IND消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年4月18日
   作    者   : l00130025
   修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
 2.日    期   : 2012年4月28日
   作    者   : W00166186
   修改内容   : DTS2012042602593,MM没有保存当前驻留的PLMN，导致后续判断出错
 3.日    期   : 2012年11月29日
   作    者   : w00176964
   修改内容   : DTS2012042804167:通知CBA模块当前接入模式为LTE
 4.日    期   : 2012年12月20日
   作    者   : w00176964
   修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
 5.日    期   : 2013年1月19日
    作    者   : t00212959
    修改内容   : DTS2012122900189:EPS注册状态完全由L上报
 6.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitLSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    /*停止保护定时器 TI_NAS_MMC_WAIT_LMM_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

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

    /*发送状态机成功结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoIndFallBack
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK状态
              收到TI_NAS_MMC_WAIT_LMM_SYS_INFO消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:TI_NAS_MMC_WAIT_LMM_SYS_INFO消息首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : W00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年04月07日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2012040106098,调整CoverageLost和service的上报顺序，以更新MMA的状态到DeepSleep
 3.日    期   : 2014年5月5日
   作    者   : w00242748
   修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                注册状态的上报。
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitAsSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 更新服务状态 */


    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */

    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 通知TAF当前的服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_LNAS_SYS_INFO_EXP);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcStatusInd_InterSysCco_WaitEstInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_Est_Ind状态
              收到ID_LMM_MMC_STATUS_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCMM_RR_CONN_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数

  2.日    期   : 2012年4月17日
    作    者   : z40661
    修改内容   : 低功耗合入
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstStatus;

    pstStatus = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    if ( VOS_FALSE == pstStatus->bitOpConnState)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_InterSysCco_WaitEstInd:bitOpConnState IS VOS_FALSE");
        return VOS_TRUE;
    }

    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_InterSysCco_WaitEstInd:NetType is not Lte");
        return VOS_TRUE;
    }

    /* 根据当前连接建立情况，确定是CCO流程结束还是回退，同时更新LMM的链接状态 */
    switch (pstStatus->ulConnState)
    {
        case MMC_LMM_CONN_ESTING:

            /* 设置EPS的信令链接为存在 */
            NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);

            break;
        case MMC_LMM_CONNECTED_SIG:

            /* 停止保护定时器  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /* 设置EPS的信令链接为存在 */
            NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);

            /* 发送状态成功结果 */
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            break;

        case MMC_LMM_CONNECTED_DATA:

            /* 停止保护定时器  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /* 设置EPS的数据链接为存在 */
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_TRUE);

            /* 发送状态成功结果 */
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            break;

        case MMC_LMM_CONN_IDLE:

            /* 停止保护定时器  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /* 设置EPS的信令链接为不存在 */
            NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);

            /* 设置EPS的数据链接为不存在 */
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);

            /* 将MMC的状态置成NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND, TI_NAS_MMC_WAIT_AS_SUSPEND_IND_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_InterSysCco_WaitEstInd:Unexpected eps con status!");
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_InterSysCco_WaitEstInd
 功能描述  : MMC在NAS_MMC_InterSysCco_STA_WAIT_Est_Ind状态
              收到ID_LMM_MMC_SUSPEND_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:MMCMM_RR_CONN_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg;
    RRMM_SUSPEND_IND_ST                 stSndSuspendMsg;

    pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* 停止保护定时器  TI_NAS_MMC_WAIT_EST_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 转换L的挂起消息为GU格式的 */
    NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stSndSuspendMsg);

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(&stSndSuspendMsg);

    /* 设置MM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(&stSndSuspendMsg);

    /* 设置GMM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK);

    /* 启动等待MM回复定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_InterSysCco_WaitAsSuspendIndFallBack
 功能描述  : 在InterSysCco的NAS_MMC_InterSysCco_STA_WAIT_AS_SUSPEND_IND_FALLBACK状态,收到LMM的ID_LMM_MMC_SUSPEND_IND消息后的处理
 输入参数  : ulEventType:消息类型
             pstmsg:收到LMM的ID_LMM_MMC_SUSPEND_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_InterSysCco_WaitAsSuspendIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLmmSuspendMsg;
    RRMM_SUSPEND_IND_ST                 stSndSuspendMsg;

    pstLmmSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* 停止保护定时器  TI_NAS_MMC_WAIT_AS_SUSPEND_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND);

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 转换L的挂起消息为GU格式的 */
    NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLmmSuspendMsg, &stSndSuspendMsg);

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(&stSndSuspendMsg);

    /* 设置MM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(&stSndSuspendMsg);

    /* 设置GMM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK);

    /* 启动等待MM回复定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmResumeInd_InterSysCco_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK状态
              收到ID_LMM_MMC_RESUME_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:ID_LMM_MMC_RESUME_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月29日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2011年12月1日
   作    者   : w00176964
   修改内容   : GUNAS V7R1 PhaseIV 阶段调整

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCco_WaitAsResumeIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 停止TI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    /* 设置当前网络为LTE */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

    /* 由于L的RESUME_IND消息不包含CS,PSresume结果，此时按照恢复成功生成RESUME消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_NET_RAT_TYPE_LTE ,&stResumeIndMsg);

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* 设置GMM等待标识 */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送:NAS_MMC_SndMmResumeInd */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* 设置MM等待标识 */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 迁入到NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK);

    /* 启动定时器TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



