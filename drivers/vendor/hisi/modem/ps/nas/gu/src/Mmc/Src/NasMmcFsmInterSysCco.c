

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcCtx.h"
#include "NasMmcTimerMgmt.h"
#include "Nasrrcinterface.h"

#include "MsccMmcInterface.h"

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
/* 删除ExtAppMmcInterface.h*/
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
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 获取旧的网络类型 */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* 停止保护定时器  TI_NAS_MMC_WAIT_WAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

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
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());



    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );







    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



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
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 获取旧的网络类型 */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* 停止保护定时器  TI_NAS_MMC_WAIT_GAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif

    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

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

    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());




    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );





    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());




    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();


    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );




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


VOS_UINT32 NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());




    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );




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




VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitWSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulParentEventType;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 停止保护定时器  TI_NAS_MMC_WAIT_WAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);


    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    /* 驻留小区的接入受限信息变化时,通知MMA模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

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

    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());




    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );




    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitGSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulParentEventType;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 停止保护定时器  TI_NAS_MMC_WAIT_GAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif

    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    /* 驻留小区的接入受限信息变化时,通知MSCC模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

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

    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());




    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );




    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());




    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );




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


VOS_UINT32 NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());




    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );




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



    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 通知TAF当前的服务状态 */

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



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


    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 通知TAF当前的服务状态 */



    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



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

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);


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




VOS_UINT32 NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitAsSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 更新服务状态 */

    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 通知TAF当前的服务状态 */


    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_LNAS_SYS_INFO_EXP);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



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

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);


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




VOS_UINT32 NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitAsSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 更新服务状态 */



    /* 向TAF报出服务区流程 */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* 通知TAF当前的服务状态 */


    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_LNAS_SYS_INFO_EXP);

    /*发送状态机失败结果*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



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



