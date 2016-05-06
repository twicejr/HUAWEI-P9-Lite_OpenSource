/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmInterSysHo.c
  版 本 号   : 初稿
  作    者   : W00176964
  生成日期   : 2011年06月29日
  最近修改   :
  功能描述   : INTER SYS Ho时状态处理
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
#include "NasMmlCtx.h"
#include "NasComm.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmlMsgProc.h"
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
#include "NasMmcSndGuAs.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcProcSuspend.h"
#include "NasMmcFsmInterSysHoTbl.h"
#include "NasMmcFsmInterSysHo.h"
#include "NasUtranCtrlInterface.h"

#include "NasMmcComFunc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_HO_C
/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSuspendInd_InterSysHo_Init
 功能描述  : 在Ho的INIT状态,收到was的RRMM_SUSPEND_IND消息后的处理
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
VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysHo_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstHoSuspendMsg;

    pstHoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMC只在以下三个场景中用原语MMC_LMM_EPLMN_NOTIFY_REQ通知LMM:3异系统变换中，GU发生挂起，目标系统为LTE时 */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstHoSuspendMsg->ucSuspendDestination )
    {
        /* 通知LTE等效PLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(pstHoSuspendMsg);

    /* 设置MM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(pstHoSuspendMsg);

    /* 设置GMM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移到NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP);

    /* 启动等待MM回复定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasSuspendInd_InterSysHo_Init
 功能描述  : 在Ho的INIT状态,收到Gas的RRMM_SUSPEND_IND消息后的处理
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
VOS_UINT32  NAS_MMC_RcvGasSuspendInd_InterSysHo_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstHoSuspendMsg;

    pstHoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMC只在以下三个场景中用原语MMC_LMM_EPLMN_NOTIFY_REQ通知LMM:3异系统变换中，GU发生挂起，目标系统为LTE时 */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstHoSuspendMsg->ucSuspendDestination )
    {
        /* 通知LTE等效PLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(pstHoSuspendMsg);

    /* 设置MM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(pstHoSuspendMsg);

    /* 设置GMM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移到NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP);

    /* 启动等待MM回复定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_InterSysHo_Init
 功能描述  : 在Ho的INIT状态,收到LMM的ID_LMM_MMC_SUSPEND_IND消息后的处理
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
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_InterSysHo_Init(
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

    /* 向MM发起挂起指示 */
    NAS_MMC_SndMmSuspendInd(&stSndSuspendMsg);

    /* 设置MM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* 向GMM发起挂起指示 */
    NAS_MMC_SndGmmSuspendInd(&stSndSuspendMsg);

    /* 设置GMM挂起回复标记 */
    NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* 状态迁移到NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP);

    /* 启动等待MM回复定时器 */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmResumeInd_InterSysHo_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_InterSysHo_STA_WAIT_AS_RESUME_IND状态
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
VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysHo_WaitAsResumeInd(
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
    NAS_MMC_SndGmmResumeInd_Handover(&stResumeIndMsg, VOS_FALSE);
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_GMM_RESUME_RSP_FLG);
    NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_FALSE);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送:NAS_MMC_SndMmResumeInd */
    NAS_MMC_SndMmResumeInd_Handover(&stResumeIndMsg, VOS_FALSE);
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_MM_RESUME_RSP_FLG);
    NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_FALSE);

    /* 迁入到NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP);

    /* 启动定时器TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;

}

#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmSuspendRsp_InterSysHo_WaitMmSuspendRsp
 功能描述  : MMC在NAS_MMC_InterSysHo_STA_WAIT_MM_SUSPEND_RSP状态
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
VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysHo_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;
    /* 标记已收到MM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysHo( NAS_MMC_MM_SUSPEND_RSP_FLG );

    /* 未收齐GMM,MM的SUSPNED_RSP，返回继续等待 */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysHo() )
    {
        return VOS_TRUE;
    }

    /* 停止定时器TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* 向接入层发送挂起成功 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* 将MMC的状态置成SUSPEND:NAS_MMC_INTER_SYS_HO_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_HO_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmSuspendRsp_InterSysHo_WaitMmSuspendRsp
 功能描述  : MMC在NAS_MMC_InterSysHo_STA_WAIT_GMM_SUSPEND_RSP状态
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
VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysHo_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* 标记已收到GMM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysHo( NAS_MMC_GMM_SUSPEND_RSP_FLG );

    /* 未收齐GMM,MM的SUSPNED_RSP，返回继续等待 */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysHo() )
    {
        return VOS_TRUE;
    }

    /* 停止定时器TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* 向接入层发送挂起成功 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* 将MMC的状态置成SUSPEND:NAS_MMC_INTER_SYS_HO_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_HO_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysHo_WaitMmSuspendRsp
 功能描述  : MMC在NAS_MMC_InterSysHo_STA_WAIT_MM_SUSPEND_RSP状态
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
VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysHo_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysHo_WaitMmSuspendRsp:ENTERED");

    /* 向接入层发送挂起失败 */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    /* 根据挂起的发起方，构造一条恢复消息 */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* 向MM/GMM进行恢复 */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_HANDOVER, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出状态机*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasResumeInd_InterSysHo_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_InterSysHo_STA_WAIT_AS_RESUME_IND状态
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
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysHo_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enOldNtType;

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

    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* GU之间的切换,CS信令连接存在 */
    if (NAS_MML_NET_RAT_TYPE_GSM == enOldNtType)
    {
        NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_TRUE);
    }

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndMmResumeInd_Handover(pstResumeIndMsg, NAS_MMC_GetCsSigExistFlag_InterSysHo());
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_GMM_RESUME_RSP_FLG);
    NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_FALSE);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndGmmResumeInd_Handover(pstResumeIndMsg, NAS_MMC_GetPsSigExistFlag_InterSysHo());
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_MM_RESUME_RSP_FLG);
    NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_FALSE);

    /* 迁入到NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasResumeInd_InterSysHo_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_InterSysHo_STA_WAIT_AS_RESUME_IND状态
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
VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysHo_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enOldNtType;

    /* 停止MMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* 清除小区信息以及信号量 */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }


    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);


    /* 生成RESUME消息 */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* GU之间的切换,CS信令连接存在 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == enOldNtType)
    {
        NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_TRUE);
    }

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    NAS_MMC_SndMmResumeInd_Handover(pstResumeIndMsg, NAS_MMC_GetCsSigExistFlag_InterSysHo());
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_GMM_RESUME_RSP_FLG);
    NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_FALSE);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndGmmResumeInd_Handover(pstResumeIndMsg, NAS_MMC_GetPsSigExistFlag_InterSysHo());
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_MM_RESUME_RSP_FLG);
    NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_FALSE);

    /* 迁入到NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysHo_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_InterSysHo_STA_WAIT_AS_RESUME_IND状态
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
   修改内容   : DTS2015011212939:增加复位场景

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysHo_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysHo_WaitAsResumeInd:ENTERED");

    /* 调用om接口,上电复位: */

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
 函 数 名  : NAS_MMC_RcvRrMmRelInd_InterSysHo_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_InterSysHo_STA_WAIT_AS_RESUME_IND状态
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
VOS_UINT32 NAS_MMC_RcvRrMmRelInd_InterSysHo_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRelInd = VOS_NULL_PTR;
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    pstRelInd      = (RRMM_REL_IND_STRU*)pstMsg;


    /* 释放原因为Utran release时，需要继续HO流程，继续等待resume ind，
       其它认为流程结束，代表WAS恢复，即等同WAS发送了resume ind，但连接已不存在 */
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

    /* 停止MMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    /* 将resume 的结果包含在GMM_MMC_RESUME_INd 消息中，并向GMM发送 */
    PS_MEM_SET(&stResumeIndMsg, 0x0, sizeof(stResumeIndMsg));
    NAS_MMC_SndMmResumeInd_Handover(&stResumeIndMsg, NAS_MMC_GetCsSigExistFlag_InterSysHo());
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_GMM_RESUME_RSP_FLG);
    NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_FALSE);

    /* 将resume 的结果包含在MM_MMC_RESUME_IND消息中，并向MM发送 */
    NAS_MMC_SndGmmResumeInd_Handover(&stResumeIndMsg, NAS_MMC_GetPsSigExistFlag_InterSysHo());
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_MM_RESUME_RSP_FLG);
    NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_FALSE);

    /* 迁入到NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP状态 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmHandoverInd_InterSysHo_WaitAsResumeInd
 功能描述  : MMC在NAS_MMC_InterSysHo_STA_WAIT_AS_RESUME_IND状态
              收到RRMM_HANDOVER_INFO_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstmsg:RRMM_HANDOVER_INFO_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年11月26s日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmHandoverInd_InterSysHo_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_HANDOVER_INFO_IND_STRU        *pstHoInfoInd = VOS_NULL_PTR;

    pstHoInfoInd      = (RRMM_HANDOVER_INFO_IND_STRU*)pstMsg;

    /* 当前切换是SRVCC流程 */
    if (VOS_TRUE == pstHoInfoInd->ucSrvccFlag)
    {
        NAS_MMC_SndMmSrvccInfoNotify();
    }

    switch (pstHoInfoInd->enSignalInfo)
    {
        case RRC_NAS_SIG_CS:

             NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_TRUE);
             break;

        case RRC_NAS_SIG_PS:

            NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_TRUE);
            break;

        case RRC_NAS_SIG_CSANDPS:

             NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_TRUE);
             NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_TRUE);
             break;

        default:

            break;
    }

    return VOS_TRUE;
}




/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmResumeRsp_InterSysHo_WaitMmResumeRsp
 功能描述  : MMC在NAS_MMC_InterSysHo_STA_WAIT_MM_RESUME_RSP状态
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
 2.日    期   : 2012年11月21日
   作    者   : z00161729
   修改内容   : 支持cerssi和nmr
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysHo_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 状态机上下文标记已收到MMCGMM_RESUME_RSP */
    NAS_MMC_ClearResumeRspFlag_InterSysHo(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* 未收齐GMM的MMCGMM_RESUME_RSP和 MM的MMCMM_RESUEM_RSP,返回继续等待 */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysHo() )
    {
        return VOS_TRUE;
    }

    /* 如果已经收齐,停止TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

       /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */


    /* 发送状态机成功的结果 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_HANDOVER, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机: */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmResumeRsp_InterSysHo_WaitMmResumeRsp
 功能描述  : MMC在NAS_MMC_InterSysHo_STA_WAIT_MM_RESUME_RSP状态
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
 2.日    期   : 2012年11月21日
   作    者   : z00161729
   修改内容   : 支持cerssi和nmr

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysHo_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 状态机上下文标记已收到MMCMM_RESUME_RSP */
    NAS_MMC_ClearResumeRspFlag_InterSysHo(NAS_MMC_MM_RESUME_RSP_FLG);

    /* 未收齐GMM的MMCGMM_RESUME_RSP和 MM的MMCMM_RESUEM_RSP，返回继续等待 */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysHo() )
    {
        return VOS_TRUE;
    }

    /* 如果已经收齐,停止TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

     /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */

    /* 发送状态机成功的结果 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_HANDOVER, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机: */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysHo_WaitMmResumeRsp
 功能描述  : MMC在NAS_MMC_InterSysHo_STA_WAIT_MM_RESUME_RSP状态
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
 2.日    期   : 2012年11月21日
   作    者   : z00161729
   修改内容   : 支持cerssi和nmr
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysHo_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysHo_WaitMmResumeRsp:ENTERED");

    /* 向接入发送恢复回复 */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* 模式切换时不再通知接入层NAS_MMC_SndInfoReportReq，接入层从模时收到主动上报请求后自行保存 */


    /* 发送状态机成功的结果 */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_HANDOVER, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机: */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndGmmResumeInd_Handover
 功能描述  : 切换时NAS向MM发送ResumeInd的指示
 输入参数  : RRMM_RESUME_IND_ST                 *pstMsg
             ucPsSigExistFlg                    :PS信令连接存在标记
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月26日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_SndGmmResumeInd_Handover(
    RRMM_RESUME_IND_ST                 *pstMsg,
    VOS_UINT8                           ucPsSigExistFlg
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

    pstSndMsg->ucPsSigExistFlg       = ucPsSigExistFlg;

    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMmResumeInd_Handover
 功能描述  : handover时NAS向MM发送ResumeInd的指示
 输入参数  : RRMM_RESUME_IND_ST                 *pstMsg
             ucCsSigExistFlg                    :CS信令连接存在标记
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月26日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_MMC_SndMmResumeInd_Handover(
    RRMM_RESUME_IND_ST                 *pstMsg,
    VOS_UINT8                           ucCsSigExistFlg
)
{
    /*向MM发送恢复指示,定义原语类型指针 */
    MMCMM_RESUME_IND_STRU              *pstSndMsg = VOS_NULL_PTR;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    pstSndMsg  = (MMCMM_RESUME_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_RESUME_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstSndMsg->MsgHeader.ulLength          = sizeof(MMCMM_RESUME_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息名称 */
    pstSndMsg->MsgHeader.ulMsgName   = MMCMM_RESUME_IND;

    pstSndMsg->ucCsResumeResult      = pstMsg->ucCsResumeResult;
    pstSndMsg->ucPsResumeResult      = pstMsg->ucPsResumeResult;
    pstSndMsg->ucResumeOrigen        = pstMsg->ucResumeOrigen;

    pstSndMsg->ucCsSigExistFlg       = ucCsSigExistFlg;

    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


