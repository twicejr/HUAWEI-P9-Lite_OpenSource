

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
/* 删除ExtAppMmcInterface.h*/
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

    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);

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

    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}


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

    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* 通知TAF当前的服务状态 */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);

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

