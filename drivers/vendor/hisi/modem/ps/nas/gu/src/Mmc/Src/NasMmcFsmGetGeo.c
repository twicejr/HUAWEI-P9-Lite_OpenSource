

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasComm.h"
#include "NasMmlLib.h"
#include "NasMmcFsmGetGeo.h"
#include "NasMmcFsmGetGeoTbl.h"
#include "NasMmcComFunc.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndMscc.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "NasMmcSndLmm.h"
#endif



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_GET_GEO_C

/* 状态机函数起始位置 */

VOS_UINT32 NAS_MMC_RcvMsccGetGeoReq_GetGeo_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatListInfo = VOS_NULL_PTR;

    pstGetGeoRatListInfo                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_GET_GEO_REQ ");

    /*Get_Geo状态机初始化，就表示开始了FFT，作为开始的时间点 */
    NAS_MML_SetFftSrchStartTime(VOS_GetSlice());

    /* 保存入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 初始化可以考虑获取地理信息的接入技术 */
    NAS_MMC_InitFsmGetGeoRatPrioListCtx_GetGeo();

    /* 如果初始化之后发现可以GET GEO接入技术列表为空，直接返回失败，退出状态机 */
    if (0 == pstGetGeoRatListInfo->ucRatNum)
    {
        NAS_TRACE_HIGH("rat num is 0, GetGeo fail. ");

        /* 状态机返回获取地理信息结果失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 存在需要CSS扫频的接入技术，设置进入扫频阶段 */
    NAS_MMC_SetFsmTaskPhase_GetGeo(NAS_MMC_GET_GEO_FSM_TASK_PHASE_BAND_SCAN);

    /* 执行扫频 */
    NAS_MMC_PerformBandScan_GetGeo();

    return VOS_TRUE;

}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitCssBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ");

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF);

    /* 将abort标志置为true */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 向CSS发送停止扫频，转到等待停止扫频状态，启动定时器 */
    NAS_MMC_SndCssStopBandScanReq();

    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF,
                                 TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF");

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitCssBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ");

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF);

    /* 将abort标志置为true */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    /* 向CSS发送停止扫频，转到等待停止扫频状态，启动定时器 */
    NAS_MMC_SndCssStopBandScanReq();

    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF,
                                 TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF");

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvCssBandScanCnf_GetGeo_WaitCssBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;
    CSS_MULTI_BAND_SCAN_CNF_STRU       *pstBandScanCnf   = VOS_NULL_PTR;

    pstBandScanCnf = (CSS_MULTI_BAND_SCAN_CNF_STRU*)pstMsg;

    /* 扫频结果打印 */
    NAS_TRACE_HIGH("enResult = %d, coverageType is, GSM %u, WCDMA %u, LTE %u ",
                    pstBandScanCnf->enResult,
                    pstBandScanCnf->enGsmCoverageType,
                    pstBandScanCnf->enUmtsFddCoverageType,
                    pstBandScanCnf->enLteCoverageType);

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF);

    /* 收到扫频结果事件ID_CSS_MULTI_BAND_SCAN_CNF
    Get_Geo状态机都在此函数中处理扫频结果. 记录 Band Scan的结果 */
    NAS_MML_SaveFftSrchBandScanResultAndFinishTime(pstBandScanCnf);

    /* 如果有中止标识 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 状态机返回扫频结果abort */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 无射频资源 */
    if (CSS_MULTI_BAND_SCAN_RESULT_NO_RF == pstBandScanCnf->enResult)
    {
        /* 状态机返回扫频结果NO RF */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 其他原因的失败 */
    if (CSS_MULTI_BAND_SCAN_RESULT_SUCC != pstBandScanCnf->enResult)
    {
        /* 状态机返回扫频结果失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 扫频结果成功 */
    NAS_TRACE_HIGH("BandScan succ, coverageType is, GSM %u, WCDMA %u, LTE %u ",
                    pstBandScanCnf->enGsmCoverageType,
                    pstBandScanCnf->enUmtsFddCoverageType,
                    pstBandScanCnf->enLteCoverageType);

    /* 根据扫频结果刷新GET GEO接入技术优先级列表 */
    NAS_MMC_UpdateGetGeoRatPrioListCtx_GetGeo(pstBandScanCnf);

    /* 可维可测，输出刷新完的获取地理信息使用的接入技术优先级列表 */
    NAS_MMC_LOG_FsmCtxGetGeoRatListState_GetGeo();

    /* 进入PLMN搜索阶段 */
    NAS_MMC_SetFsmTaskPhase_GetGeo(NAS_MMC_GET_GEO_FSM_TASK_PHASE_PLMN_SEARCH);

    /* 取下一个要获取地理信息的接入技术 */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取成功，到下一个接入技术获取地理信息 */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitCssBandScanCnfExp_GetGeo_WaitCssBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF");

    /* 向CSS发送停止扫频，转到等待停止扫频状态，启动定时器 */
    NAS_MMC_SndCssStopBandScanReq();

    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF,
                                 TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF");

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvCssStopBandScanCnf_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_CSS_STOP_BAND_SCAN_CNF");

    /* 收到扫频结果事件ID_CSS_STOP_BAND_SCAN_CNF,扫频已经停止,记录 Band Scan的结果 */
    NAS_MML_SaveFftSrchBandScanResultAndFinishTime(VOS_NULL_PTR);

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF);

    /* 如果有中止标识 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 状态机返回获取地理信息结果为被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);
    }
    else
    {
        /* 否则返回扫频结果异常 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABNORMAL, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvCssBandScanCnf_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF);

    return NAS_MMC_RcvCssBandScanCnf_GetGeo_WaitCssBandScanCnf(ulEventType, pstMsg);
}


VOS_UINT32 NAS_MMC_RcvTiWaitCssStopBandScanCnfExp_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF");

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 状态机返回获取地理信息结果为被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);
    }
    else
    {
        /* 状态机返回获取地理信息结果为异常 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABNORMAL, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* 设置打断标识 */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 获取地理信息被打断，认为获取失败，通知当前接入技术停止获取地理信息 */

    /* 给GAS发送停止获取地理信息请求 */
    NAS_MMC_SndAsStopGetGeoPlmnSearchReq(UEPS_PID_GAS);

    /* 迁移到等待停止获取地理信息状态，启动定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;

}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* 设置打断标识 */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    /* 获取地理信息被打断，认为获取失败，通知当前接入技术停止获取地理信息 */

    /* 给GAS发送停止获取地理信息请求 */
    NAS_MMC_SndAsStopGetGeoPlmnSearchReq(UEPS_PID_GAS);

    /* 迁移到等待停止获取地理信息状态，启动定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;

}



VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stGeoPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    PS_MEM_SET((VOS_INT8 *)&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("Rcv Msg: RRMM_PLMN_SEARCH_CNF, enResult = %d", pstSrchCnfMsg->ulSearchRlt);

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* 获取地理信息成功，结束状态机，返回状态机结果 */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 从搜网结果中获取地理信息PLMN */
        NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(NAS_MML_NET_RAT_TYPE_GSM, pstMsg, &stGeoPlmn);

        /* 状态机返回获取地理信息结果成功 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_SUCCESS, &stGeoPlmn);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取地理信息失败 */

    /* 如果是NO RF，则放弃获取地理信息，直接认为失败 */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 取下一个要获取地理信息的接入技术 */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取成功，到下一个接入技术获取地理信息 */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvTiWaitGasGetGeoCnfExp_GetGeo_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF.");

    /* 获取地理信息超时，认为获取失败，通知当前接入技术停止获取地理信息 */

    /* 给GAS发送停止获取地理信息请求 */
    NAS_MMC_SndAsStopGetGeoPlmnSearchReq(UEPS_PID_GAS);

    /* 迁移到等待停止获取地理信息状态，启动定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* 设置打断标识 */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 获取地理信息被打断，认为获取失败，通知当前接入技术停止获取地理信息 */

    /* 给WAS发送停止获取地理信息请求 */
    NAS_MMC_SndAsStopGetGeoPlmnSearchReq(WUEPS_PID_WRR);

    /* 迁移到等待停止获取地理信息状态，启动定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;

}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* 设置打断标识 */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    /* 获取地理信息被打断，认为获取失败，通知当前接入技术停止获取地理信息 */

    /* 给WAS发送停止获取地理信息请求 */
    NAS_MMC_SndAsStopGetGeoPlmnSearchReq(WUEPS_PID_WRR);

    /* 迁移到等待停止获取地理信息状态，启动定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;

}



VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stGeoPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat     = NAS_MML_NET_RAT_TYPE_BUTT;
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    PS_MEM_SET((VOS_INT8 *)&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    pstSrchCnfMsg                       = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("Rcv Msg: RRMM_PLMN_SEARCH_CNF, enResult = %d", pstSrchCnfMsg->ulSearchRlt);

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* 获取地理信息成功，结束状态机，返回状态机结果 */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 从搜网结果中获取地理信息PLMN */
        NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(NAS_MML_NET_RAT_TYPE_WCDMA, pstMsg, &stGeoPlmn);

        /* 状态机返回获取地理信息结果成功 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_SUCCESS, &stGeoPlmn);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取地理信息失败 */

    /* 如果是NO RF，则放弃获取地理信息，直接认为失败 */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 取下一个要获取地理信息的接入技术 */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取成功，到下一个接入技术获取地理信息 */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitWasGetGeoExp_GetGeo_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF ");

    /* 获取地理信息超时，认为获取失败，通知当前接入技术停止获取地理信息 */

    /* 给WAS发送停止获取地理信息请求 */
    NAS_MMC_SndAsStopGetGeoPlmnSearchReq(WUEPS_PID_WRR);

    /* 迁移到等待停止获取地理信息状态，启动定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}




VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;

    NAS_TRACE_HIGH("Rcv Msg: RRMM_PLMN_SEARCH_STOP_CNF ");

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* 存在ABORT标识，直接退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 状态机返回获取地理信息结果被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 取下一个要获取地理信息的接入技术 */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取成功，到下一个接入技术获取地理信息 */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stGeoPlmn;
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    PS_MEM_SET((VOS_INT8 *)&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    NAS_TRACE_HIGH("Rcv Msg: RRMM_PLMN_SEARCH_CNF ");

    pstSrchCnfMsg                       = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    /* 获取地理信息成功，结束状态机，返回状态机结果 */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 停止等待定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

        /* 从搜网结果中获取地理信息PLMN */
        NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(NAS_MML_NET_RAT_TYPE_GSM, pstMsg, &stGeoPlmn);

        /* 状态机返回获取地理信息结果成功 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_SUCCESS, &stGeoPlmn);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 存在ABORT标识，直接退出状态机，不用再等STOP回复 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 停止等待定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

        /* 状态机返回获取地理信息结果为被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 如果是NO RF，则放弃获取地理信息，直接认为失败 */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 停止等待定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取地理信息其他原因的失败，不停定时器继续等STOP CNF，然后再执行下一步的处理 */

    return VOS_TRUE;

}



VOS_UINT32  NAS_MMC_RcvTiWaitGasStopGetGeoExp_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;

    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF ");

    /* 存在ABORT标识，直接退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 状态机返回获取地理信息结果为被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 取下一个要获取地理信息的接入技术 */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取成功，到下一个接入技术获取地理信息 */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;

    NAS_TRACE_HIGH("Rcv Msg: RRMM_PLMN_SEARCH_STOP_CNF ");

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* 存在ABORT标识，直接退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 状态机返回获取地理信息结果为被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 取下一个要获取地理信息的接入技术 */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取成功，到下一个接入技术获取地理信息 */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stGeoPlmn;
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    PS_MEM_SET((VOS_INT8 *)&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    NAS_TRACE_HIGH("Rcv Msg: RRMM_PLMN_SEARCH_CNF ");

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    /* 获取地理信息成功，结束状态机，返回状态机结果 */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 停止等待定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

        /* 从搜网结果中获取地理信息PLMN */
        NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(NAS_MML_NET_RAT_TYPE_WCDMA, pstMsg, &stGeoPlmn);

        /* 状态机返回获取地理信息结果成功 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_SUCCESS, &stGeoPlmn);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 存在ABORT标识，直接退出状态机，不用再等STOP CNF */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 停止等待定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

        /* 状态机返回获取地理信息结果为被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 如果是NO RF，则放弃获取地理信息，直接认为失败 */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 停止等待定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取地理信息其他原因的失败，不停定时器继续等STOP CNF，然后再执行下一步的处理 */

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvTiWaitWasStopGetGeoExp_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;

    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF ");

    /* 存在ABORT标识，直接退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 状态机返回获取地理信息结果为被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 取下一个要获取地理信息的接入技术 */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取成功，到下一个接入技术获取地理信息 */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_GetGeo_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;

    pstSuspendCnf                       = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    NAS_TRACE_HIGH("Rcv Msg: RRMM_SUSPEND_CNF ");

    /* 挂起失败，直接复位 */
    if (MMC_AS_SUSPEND_SUCCESS != pstSuspendCnf->ucResult)
    {
        NAS_TRACE_HIGH("suspend fail: NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE");

        /* 调用底软接口RESET */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    /* 当前接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 存在ABORT标识，直接退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 状态机返回获取地理信息结果为被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 如果状态机任务是扫频阶段，执行扫频流程 */
    if (NAS_MMC_GET_GEO_FSM_TASK_PHASE_BAND_SCAN == NAS_MMC_GetFsmTaskPhase_GetGeo())
    {
        NAS_MMC_PerformBandScan_GetGeo();
        return VOS_TRUE;
    }

    /* 否则一定是PLMN搜索阶段 */

    /* 取下一个要获取地理信息的接入技术 */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取成功，到下一个接入技术获取地理信息 */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitGasSuspendCnfExp_GetGeo_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF. suspend fail: NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE");

    /* 挂起超时，直接复位，调用底软接口RESET */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_GetGeo_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;

    pstSuspendCnf                       = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    NAS_TRACE_HIGH("Rcv Msg: RRMM_SUSPEND_CNF ");

    /* 挂起失败，直接复位 */
    if (MMC_AS_SUSPEND_SUCCESS != pstSuspendCnf->ucResult)
    {
        NAS_TRACE_HIGH("suspend fail: NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE");

        /* 调用底软接口RESET */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* 挂起成功 */

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    /* 当前接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 存在ABORT标识，直接退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 状态机返回获取地理信息结果为被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 如果状态机任务是扫频阶段，执行扫频流程 */
    if (NAS_MMC_GET_GEO_FSM_TASK_PHASE_BAND_SCAN == NAS_MMC_GetFsmTaskPhase_GetGeo())
    {
        NAS_MMC_PerformBandScan_GetGeo();
        return VOS_TRUE;
    }

    /* 否则一定是PLMN搜索阶段 */

    /* 取下一个要获取地理信息的接入技术 */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取成功，到下一个接入技术获取地理信息 */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendCnfExp_GetGeo_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF. suspend fail: NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE");

    /* 挂起超时，直接复位，调用底软接口RESET */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 设置打断标识 */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 获取地理信息被打断，认为获取失败，通知当前接入技术停止获取地理信息 */

    /* 给LMM发送停止获取地理信息请求 */
    NAS_MMC_SndLmmStopGetGeoPlmnSearchReq();

    /* 迁移到等待停止获取地理信息状态，启动定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;

}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 设置打断标识 */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    /* 获取地理信息被打断，认为获取失败，通知当前接入技术停止获取地理信息 */

    /* 给LMM发送停止获取地理信息请求 */
    NAS_MMC_SndLmmStopGetGeoPlmnSearchReq();

    /* 迁移到等待停止获取地理信息状态，启动定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;

}



VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_GetGeo_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stGeoPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstSrchCnfMsg = VOS_NULL_PTR;

    PS_MEM_SET((VOS_INT8 *)&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    pstSrchCnfMsg                       = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("Rcv Msg: ID_LMM_MMC_PLMN_SRCH_CNF, enResult = %d", pstSrchCnfMsg->enRlst);

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 获取地理信息成功，结束状态机，返回状态机结果 */
    if (MMC_LMM_PLMN_SRCH_RLT_GET_GEO_SUCC == pstSrchCnfMsg->enRlst)
    {
        /* 从搜网结果中获取地理信息PLMN */
        NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(NAS_MML_NET_RAT_TYPE_LTE, pstMsg, &stGeoPlmn);

        /* 状态机返回获取地理信息结果成功 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_SUCCESS, &stGeoPlmn);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取地理信息失败 */

    /* 如果是NO RF，则放弃获取地理信息，直接认为失败 */
    if (MMC_LMM_PLMN_SRCH_RLT_GET_GEO_NO_RF == pstSrchCnfMsg->enRlst)
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 取下一个要获取地理信息的接入技术 */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取成功，到下一个接入技术获取地理信息 */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitLmmGetGeoCnfExp_GetGeo_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF ");

    /* 获取地理信息超时，认为获取失败，通知当前接入技术停止获取地理信息 */

    /* 给LMM发送停止获取地理信息请求 */
    NAS_MMC_SndLmmStopGetGeoPlmnSearchReq();

    /* 迁移到等待停止获取地理信息状态，启动定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmStopPlmnSrchCnf_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;

    NAS_TRACE_HIGH("Rcv Msg: ID_LMM_MMC_STOP_PLMN_SRCH_CNF ");

    /* 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

    /* 存在ABORT标识，直接退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 状态机返回获取地理信息结果为被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 取下一个要获取地理信息的接入技术 */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取成功，到下一个接入技术获取地理信息 */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stGeoPlmn;
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstSrchCnfMsg = VOS_NULL_PTR;

    PS_MEM_SET((VOS_INT8 *)&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    NAS_TRACE_HIGH("Rcv Msg: ID_LMM_MMC_PLMN_SRCH_CNF ");

    pstSrchCnfMsg                       = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* 获取地理信息成功，结束状态机，返回状态机结果 */
    if (MMC_LMM_PLMN_SRCH_RLT_GET_GEO_SUCC == pstSrchCnfMsg->enRlst)
    {
        /* 停止等待定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        /* 从搜网结果中获取地理信息PLMN */
        NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(NAS_MML_NET_RAT_TYPE_LTE, pstMsg, &stGeoPlmn);

        /* 状态机返回获取地理信息结果成功 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_SUCCESS, &stGeoPlmn);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 存在ABORT标识，直接退出状态机，接入层已经回复了CNF，不用再STOP */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 停止等待定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        /* 状态机返回获取地理信息结果为被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 如果是NO RF，则放弃获取地理信息，直接认为失败 */
    if (MMC_LMM_PLMN_SRCH_RLT_GET_GEO_NO_RF == pstSrchCnfMsg->enRlst)
    {
        /* 停止等待定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取地理信息其他原因的失败，不停定时器继续等STOP CNF，然后再执行下一步的处理 */

    return VOS_TRUE;

}



VOS_UINT32  NAS_MMC_RcvTiWaitLmmStopGetGeoCnfExp_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;

    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF ");

    /* 存在ABORT标识，直接退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 状态机返回获取地理信息结果为被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 取下一个要获取地理信息的接入技术 */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取成功，到下一个接入技术获取地理信息 */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* 设置通知MSCC回复标记 */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvLmmSuspendCnf_GetGeo_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;
    LMM_MMC_SUSPEND_CNF_STRU           *pstSuspendCnf = VOS_NULL_PTR;

    pstSuspendCnf                       = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("Rcv Msg: ID_LMM_MMC_SUSPEND_CNF ");

    /* 挂起失败，直接复位 */
    if (MMC_LMM_SUCC != pstSuspendCnf->ulRst)
    {
        NAS_TRACE_HIGH("suspend fail: NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE");

        /* 调用底软接口RESET */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* 挂起成功, 停止等待定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF);

    /* 当前接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 存在ABORT标识，直接退出状态机 */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* 状态机返回获取地理信息结果为被中止 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 如果状态机任务是扫频阶段，执行扫频流程 */
    if (NAS_MMC_GET_GEO_FSM_TASK_PHASE_BAND_SCAN == NAS_MMC_GetFsmTaskPhase_GetGeo())
    {
        NAS_MMC_PerformBandScan_GetGeo();
        return VOS_TRUE;
    }

    /* 否则一定是PLMN搜索阶段，取下一个要获取地理信息的接入技术 */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* 获取失败，状态机返回结果获取地理信息失败 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取成功，到下一个接入技术获取地理信息 */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvTiWaitLmmSuspendCnfExp_GetGeo_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF. suspend fail: NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE");

    /* 挂起超时，直接复位，调用底软接口RESET */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);
    return VOS_TRUE;
}

#endif

/* 状态机函数结束位置 */

/* 状态机函数调用的其他函数起始定义位置 */


VOS_VOID NAS_MMC_LOG_FsmCtxGetGeoRatListState_GetGeo(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatInfoList = VOS_NULL_PTR;

    pstGetGeoRatInfoList                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    /* 循环输出列表中的每个单元的状态 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        NAS_TRACE_HIGH("prio %u, enRatType %u, coveragetype %u, IsSrchedFlag %u",
                    i,
                    pstGetGeoRatInfoList->astGetGeoRatInfo[i].enRatType,
                    pstGetGeoRatInfoList->astGetGeoRatInfo[i].enCoverageType,
                    pstGetGeoRatInfoList->astGetGeoRatInfo[i].ucIsSrchedFlag);
    }

    return;

}


VOS_VOID NAS_MMC_LogSndCssBandScanReq_GetGeo(
    NAS_MMC_CSS_MULTI_BAND_SCAN_INFO_STRU         *pstCssScanInfo
)
{
    NAS_TRACE_HIGH("bitOpMcc = %u, bitOpHighRssi = %u, enBandScanType = %u, aucMcc[0] = %u, aucMcc[1] = %u",
                pstCssScanInfo->bitOpMcc,
                pstCssScanInfo->bitOpHighRssi,
                pstCssScanInfo->enBandScanType,
                pstCssScanInfo->aucMcc[0],
                pstCssScanInfo->aucMcc[1]);

    NAS_TRACE_HIGH("enRatType = %u, %u, %u",
                pstCssScanInfo->stRatList.aucRatList[0],
                pstCssScanInfo->stRatList.aucRatList[1],
                pstCssScanInfo->stRatList.aucRatList[2]);

    return;

}


VOS_VOID NAS_MMC_LOG_PrioRatList_GetGeo(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstMsPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstGetGeoPrioList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /* 获取当前支持的接入技术及其优先级 */
    pstMsPrioRatList                    = NAS_MML_GetMsPrioRatList();
    /* 可维可测，循环输出SYSCFG配置的支持的接入技术优先级 */
    for (i = 0; i < pstMsPrioRatList->ucRatNum; i++)
    {
        NAS_TRACE_HIGH("SYSCFG MsPrioRatList: prio %u, enRatType %u ", i, pstMsPrioRatList->aucRatPrio[i]);
    }

    /* 获取NV设置的获取地理位置信息接入技术优先级列表 */
    pstGetGeoPrioList                   = NAS_MML_GetGeoPrioRatList();
    /* 可维可测，循环输出NV配置的支持的接入技术优先级 */
    for (i = 0; i < pstGetGeoPrioList->ucRatNum; i++)
    {
        NAS_TRACE_HIGH("NV GetGeoPrioList: prio %u, enRatType %u ", i, pstGetGeoPrioList->aucRatPrio[i]);
    }

    return;
}


VOS_VOID NAS_MMC_BuildCommBandScanInfo_GetGeo(
    NAS_MMC_CSS_MULTI_BAND_SCAN_INFO_STRU        *pstCssScanInfo
)
{
    pstCssScanInfo->bitOpMcc         = VOS_FALSE;
    pstCssScanInfo->bitOpHighRssi    = VOS_FALSE;
    pstCssScanInfo->enBandScanType   = CSS_BAND_SCAN_COMM;
    NAS_MMC_ConvertNasRatTypeToCssRatType_GetGeo(&pstCssScanInfo->stRatList);
    return;
}


VOS_VOID NAS_MMC_InitFsmGetGeoRatPrioListCtx_GetGeo(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstGetGeoPrioList    = VOS_NULL_PTR;
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatInfoList = VOS_NULL_PTR;

    pstGetGeoRatInfoList                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    /* 可维可测，分别输出SYSCFG和NV配置的支持的接入技术优先级 */
    NAS_MMC_LOG_PrioRatList_GetGeo();

    /* 获取NV设置的获取地理位置信息接入技术优先级列表 */
    pstGetGeoPrioList                   = NAS_MML_GetGeoPrioRatList();

    /* 按获取地理信息接入技术优先级顺序，到当前支持的接入技术列表中查找 */
    for (i = 0; i < pstGetGeoPrioList->ucRatNum; i++)
    {
        enRatType                       = pstGetGeoPrioList->aucRatPrio[i];

        /* 如果此接入技术在SYSCFG支持的接入技术列表中，则按序添加到目标列表中 */
        if (VOS_TRUE == NAS_MML_IsNetRatSupported(enRatType))
        {
            pstGetGeoRatInfoList->astGetGeoRatInfo[pstGetGeoRatInfoList->ucRatNum].enRatType      = enRatType;
            pstGetGeoRatInfoList->astGetGeoRatInfo[pstGetGeoRatInfoList->ucRatNum].enCoverageType = NAS_MMC_COVERAGE_TYPE_BUTT;
            pstGetGeoRatInfoList->astGetGeoRatInfo[pstGetGeoRatInfoList->ucRatNum].ucIsSrchedFlag = VOS_FALSE;
            pstGetGeoRatInfoList->ucRatNum ++;
        }
    }

    return;
}


VOS_VOID NAS_MMC_ConvertNasRatTypeToCssRatType_GetGeo(
    CSS_RAT_LIST                       *pstCssBandScanRatList
)
{
    VOS_UINT32                          i;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSrcRat;
    CSS_RAT_TYPE_ENUM_UINT8             enDstRat;
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatInfoList = VOS_NULL_PTR;

    pstGetGeoRatInfoList                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    pstCssBandScanRatList->ucRatNum     = pstGetGeoRatInfoList->ucRatNum;

    /* 从状态机上下文中逐个取要扫频的接入技术进行转换 */
    for (i = 0; i < pstGetGeoRatInfoList->ucRatNum; i++)
    {
        enSrcRat = pstGetGeoRatInfoList->astGetGeoRatInfo[i].enRatType;

        switch (enSrcRat)
        {
            case NAS_MML_NET_RAT_TYPE_GSM:
                enDstRat                = CSS_RAT_GSM;
                break;

            case NAS_MML_NET_RAT_TYPE_WCDMA:
                enDstRat                = CSS_RAT_UMTS_FDD;
                break;

#if (FEATURE_ON == FEATURE_LTE)
            case NAS_MML_NET_RAT_TYPE_LTE:
                enDstRat                = CSS_RAT_LTE;
                break;
#endif
            default:
                enDstRat                = CSS_RAT_TYPE_BUTT;
                break;
        }

        pstCssBandScanRatList->aucRatList[i] = enDstRat;
    }

    return;

}


NAS_MMC_COVERAGE_TYPE_ENUM_UINT8 NAS_MMC_ConvertCoverageType_GetGeo(
    CSS_COVERAGE_TYPE_ENUM_UINT8        enSrcCoverageType
)
{
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8    enDestCoverageType;

    switch (enSrcCoverageType)
    {
        case CSS_COVERAGE_TYPE_NONE:

            enDestCoverageType = NAS_MMC_COVERAGE_TYPE_NONE;
            break;

        case CSS_COVERAGE_TYPE_LOW:

            enDestCoverageType = NAS_MMC_COVERAGE_TYPE_LOW;
            break;

        case CSS_COVERAGE_TYPE_HIGH:

            enDestCoverageType = NAS_MMC_COVERAGE_TYPE_HIGH;
            break;

        default:

            enDestCoverageType = NAS_MMC_COVERAGE_TYPE_BUTT;
            break;
    }

    return enDestCoverageType;

}


VOS_VOID NAS_MMC_UpdateGetGeoRatCoverageType_GetGeo(
    CSS_MULTI_BAND_SCAN_CNF_STRU       *pstBandScanCnf,
    NAS_MMC_GET_GEO_RAT_INFO_STRU      *pstDestRatInfo
)
{
    /* 根据此接入技术是否存在覆盖，如果是返回TRUE，不是则返回FALSE */
    switch (pstDestRatInfo->enRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:

            pstDestRatInfo->enCoverageType = NAS_MMC_ConvertCoverageType_GetGeo(pstBandScanCnf->enGsmCoverageType);
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            pstDestRatInfo->enCoverageType = NAS_MMC_ConvertCoverageType_GetGeo(pstBandScanCnf->enUmtsFddCoverageType);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:

            pstDestRatInfo->enCoverageType = NAS_MMC_ConvertCoverageType_GetGeo(pstBandScanCnf->enLteCoverageType);
            break;
#endif
        default:

            NAS_TRACE_HIGH("enRat ERR.");
            break;
    }

    return;

}



VOS_VOID NAS_MMC_UpdateGetGeoRatPrioListCtx_GetGeo(
    CSS_MULTI_BAND_SCAN_CNF_STRU       *pstBandScanCnf
)
{
    VOS_UINT32                          i;
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatInfoList = VOS_NULL_PTR;

    pstGetGeoRatInfoList                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    /* 按获取地理信息接入技术优先级列表保存的优先级顺序，到扫频结果中查找 */
    for (i = 0; i < pstGetGeoRatInfoList->ucRatNum; i++)
    {
        /* 更新当前接入技术的覆盖类型 */
        NAS_MMC_UpdateGetGeoRatCoverageType_GetGeo(pstBandScanCnf, &pstGetGeoRatInfoList->astGetGeoRatInfo[i]);
    }

    return;
}



VOS_UINT32 NAS_MMC_GetNextGetGeoRat_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penDestRat
)
{
    VOS_UINT32                          i;
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatInfoList = VOS_NULL_PTR;

    pstGetGeoRatInfoList                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    /* 扫描整个获取地理信息接入技术优先级列表 */
    for (i = 0; i < pstGetGeoRatInfoList->ucRatNum; i++)
    {
        if (((NAS_MMC_COVERAGE_TYPE_LOW == pstGetGeoRatInfoList->astGetGeoRatInfo[i].enCoverageType)
          || (NAS_MMC_COVERAGE_TYPE_HIGH == pstGetGeoRatInfoList->astGetGeoRatInfo[i].enCoverageType))
         && (VOS_FALSE == pstGetGeoRatInfoList->astGetGeoRatInfo[i].ucIsSrchedFlag))
        {
            /* 找到未曾发起过获取地理信息且存在覆盖的接入技术，返回成功 */
            *penDestRat = pstGetGeoRatInfoList->astGetGeoRatInfo[i].enRatType;

            NAS_TRACE_HIGH("enDestRat is %u", *penDestRat);
            return VOS_TRUE;
        }
    }

    /* 循环结束也未找到，返回获取失败 */
    NAS_TRACE_HIGH("GetNextRat fail");
    return VOS_FALSE;

}


VOS_VOID NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType,
    struct MsgCB                       *pstMsg,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU stPlmnSearchInfo;
    RRMM_PLMN_SEARCH_CNF_STRU          *pstGuAsSrchCnfMsg = VOS_NULL_PTR;
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmSrchCnfMsg  = VOS_NULL_PTR;


    PS_MEM_SET(&stPlmnSearchInfo, 0, sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU));

    switch (enRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
        case NAS_MML_NET_RAT_TYPE_WCDMA:

            pstGuAsSrchCnfMsg           = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

            if (0 < pstGuAsSrchCnfMsg->PlmnIdList.ulHighPlmnNum)
            {
                pstPlmnId->ulMcc        = pstGuAsSrchCnfMsg->PlmnIdList.aHighPlmnList[0].stPlmnId.ulMcc;
                pstPlmnId->ulMnc        = pstGuAsSrchCnfMsg->PlmnIdList.aHighPlmnList[0].stPlmnId.ulMnc;
            }
            else if (0 < pstGuAsSrchCnfMsg->PlmnIdList.ulLowPlmnNum)
            {
                pstPlmnId->ulMcc        = pstGuAsSrchCnfMsg->PlmnIdList.aLowPlmnList[0].PlmnId.stPlmnId.ulMcc;
                pstPlmnId->ulMnc        = pstGuAsSrchCnfMsg->PlmnIdList.aLowPlmnList[0].PlmnId.stPlmnId.ulMnc;
            }
            else
            {
                pstPlmnId->ulMcc        = NAS_MML_INVALID_MCC;
                pstPlmnId->ulMnc        = NAS_MML_INVALID_MNC;
            }

            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:

            pstLmmSrchCnfMsg            = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

            /* 将L模上报的PLMN转换成MMC使用的格式 */
            NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo(&pstLmmSrchCnfMsg->stPlmnIdList,
                                                            &stPlmnSearchInfo);

            if (0 < stPlmnSearchInfo.ulHighPlmnNum)
            {
                pstPlmnId->ulMcc        = stPlmnSearchInfo.astHighPlmnList[0].ulMcc;
                pstPlmnId->ulMnc        = stPlmnSearchInfo.astHighPlmnList[0].ulMnc;
            }
            else if (0 < stPlmnSearchInfo.ulLowPlmnNum)
            {
                pstPlmnId->ulMcc        = stPlmnSearchInfo.astLowPlmnList[0].stPlmnId.ulMcc;
                pstPlmnId->ulMnc        = stPlmnSearchInfo.astLowPlmnList[0].stPlmnId.ulMnc;
            }
            else
            {
                pstPlmnId->ulMcc        = NAS_MML_INVALID_MCC;
                pstPlmnId->ulMnc        = NAS_MML_INVALID_MNC;
            }

            break;
#endif
        default:
            break;
    }

    return;

}



VOS_VOID NAS_MMC_SetRatIsSearchedInGetGeoRatPrioList_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat
)
{
    VOS_UINT32                          i;
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatInfoList = VOS_NULL_PTR;

    pstGetGeoRatInfoList                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    /* 扫描整个获取地理信息的接入技术列表 */
    for (i = 0; i < pstGetGeoRatInfoList->ucRatNum; i++)
    {
        if (enDestRat == pstGetGeoRatInfoList->astGetGeoRatInfo[i].enRatType)
        {
            /* 找到目标接入技术，设置为已搜索 */
            pstGetGeoRatInfoList->astGetGeoRatInfo[i].ucIsSrchedFlag = VOS_TRUE;
            break;
        }
    }

    /* 未找到，打印异常 */
    if (i >= pstGetGeoRatInfoList->ucRatNum)
    {
        NAS_TRACE_HIGH("ERR, can't find enDestRat.");
    }

    return;

}


VOS_VOID NAS_MMC_SuspendCurrentRat_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    /* 如果存在当前接入技术，则需要挂起当前接入技术才能开始扫频 */
    switch (enRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_GAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                                         TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);

            NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_GAS_SUSPEND_CNF. ");
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_WAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                                         TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);

            NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_WAS_SUSPEND_CNF. ");
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSuspendReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_LMM_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF,
                                         TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN);

            NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_LMM_SUSPEND_CNF. ");
            break;
#endif
        default:
            break;
    }

    return;
}



VOS_VOID NAS_MMC_SndAsGetGeoReq_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat
)
{
    /* 根据不同的接入技术发送搜网请求 */
    switch (enDestRat)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:

            NAS_MMC_SndAsGetGeoPlmnSearchReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_GAS_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF,
                                         TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF_LEN);

            NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_GAS_PLMN_SEARCH_CNF. ");
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsGetGeoPlmnSearchReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_WAS_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF,
                                         TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF_LEN);

            NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_WAS_PLMN_SEARCH_CNF. ");
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmGetGeoPlmnSearchReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_LMM_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                                         TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);

            NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_LMM_PLMN_SEARCH_CNF. ");
            break;
#endif

        default:
            NAS_TRACE_HIGH("enDestRat is ERR. ");
            break;
    }

    return;
}


VOS_VOID NAS_MMC_PerformBandScan_GetGeo(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8               enCurrRat;
    NAS_MMC_CSS_MULTI_BAND_SCAN_INFO_STRU         stCssScanInfo;

    /* 当前接入技术不是BUTT，保护处理，挂起当前接入技术再扫频，否则可以立即扫频 */
    enCurrRat                           = NAS_MML_GetCurrNetRatType();

    if (NAS_MML_NET_RAT_TYPE_BUTT > enCurrRat)
    {
        /* 挂起当前接入技术 */
        NAS_MMC_SuspendCurrentRat_GetGeo(enCurrRat);
    }
    else
    {
        PS_MEM_SET((VOS_INT8 *)&stCssScanInfo, 0, sizeof(NAS_MMC_CSS_MULTI_BAND_SCAN_INFO_STRU));

        /* 设置CSS请求参数，包括初始化需要CSS扫频的接入技术列表 */
        NAS_MMC_BuildCommBandScanInfo_GetGeo(&stCssScanInfo);

        /* 可维可测，打印给CSS发送扫频的相关信息 */
        NAS_MMC_LogSndCssBandScanReq_GetGeo(&stCssScanInfo);

        /* 给CSS发送扫频请求 */
        NAS_MMC_SndCssMultiBandScanReq(&stCssScanInfo);

        /* 已发送Multi-Band Scan请求，记录扫频开始时间 */
        NAS_MML_SetFftSrchBandScanStartTime(VOS_GetSlice());

        /* 转到等CSS扫频结果态，启动定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_CSS_BAND_SCAN_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF,
                                     TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF_LEN);

        NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_CSS_BAND_SCAN_CNF. ");
    }

    return;

}



VOS_VOID NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;

    /* 当前接入技术不是BUTT且与获取地理信息目标接入技术不同，保护处理，
    挂起当前接入技术再获取，否则可以立即直接获取 */
    enCurrRat                           = NAS_MML_GetCurrNetRatType();

    NAS_TRACE_HIGH("CurrNetRat %u, enDestRat %u", enCurrRat, enDestRat);

    if ((NAS_MML_NET_RAT_TYPE_BUTT > enCurrRat)
     && (enDestRat != enCurrRat))
    {
        /* 挂起当前接入技术 */
        NAS_MMC_SuspendCurrentRat_GetGeo(enCurrRat);
    }
    else
    {
        /* 设置目标接入技术为当前接入技术 */
        NAS_MML_SetCurrNetRatType(enDestRat);

        /*记录当前的PLMN Search的接入技术制式*/
        NAS_MML_SetFftSrchPlmnSrchRatType(enDestRat);

        /* 将获取地理信息接入技术优先级列表中的目标接入技术设置为已搜索 */
        NAS_MMC_SetRatIsSearchedInGetGeoRatPrioList_GetGeo(enDestRat);

        /* 可维可测，输出更新后的高质量接入技术优先级列表 */
        NAS_MMC_LOG_FsmCtxGetGeoRatListState_GetGeo();

        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        /* 向目标接入技术发送获取地理信息请求 */
        NAS_MMC_SndAsGetGeoReq_GetGeo(enDestRat);
    }

    return;

}


VOS_UINT32  NAS_MMC_IsMsccGetGeo_GetGeo(VOS_VOID)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;

   /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg     = NAS_MMC_GetCurrFsmMsgAddr();

    if (ID_MSCC_MMC_GET_GEO_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MMC_ProcGetGeoRslt_GetGeo(
    NAS_MMC_GET_GEO_RSLT_ENUM_UINT32    enGetGeoRslt,
    NAS_MML_PLMN_ID_STRU               *pstGeoPlmn
)
{
    if ((VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_GetGeo())
     && (NAS_MMC_GET_GEO_ABORTED == enGetGeoRslt))
    {
        NAS_MMC_SndMsccStopGetGeoCnf();
    }
    else if (VOS_TRUE == NAS_MMC_IsMsccGetGeo_GetGeo())
    {
        NAS_MMC_SndMsccGetGeoCnf(pstGeoPlmn);
    }
    else
    {
    }

    /* 状态机返回获取地理信息结果 */
    NAS_MMC_SndGetGeoRsltMsg(enGetGeoRslt, pstGeoPlmn);

    /* Get_Geo状态已得到搜索结果，在此处上报CHR结果 */
    NAS_MML_SaveFftSrchResultAndFinishTime((VOS_UINT8)enGetGeoRslt);
#if (FEATURE_ON == FEATURE_PTM)
    NAS_MMC_RecordFftSrchMccInfo();
#endif
    return;
}

/* 状态机函数调用的其他函数结束定义位置 */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

