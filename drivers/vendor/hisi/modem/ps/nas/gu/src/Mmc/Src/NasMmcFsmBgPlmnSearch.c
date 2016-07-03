

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "NasMmcFsmBgPlmnSearchTbl.h"
#include "NasMmcCtx.h"
#include "NasMmcFsmBgPlmnSearch.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcProcRegRslt.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcTimerMgmt.h"
#include "NasComm.h"
#include "NasMmlLib.h"
#include "NasMmlMsgProc.h"
#include "NasMmcSndMscc.h"
#include "NasMmcProcUsim.h"
#include "NasMmcProcSuspend.h"
#include "NasMmcSndOm.h"
#include "NasMmcProcNvim.h"
/* 删除ExtAppMmcInterface.h*/
#include "MmcMmInterface.h"
#include "MmcGmmInterface.h"
#include "NasMmcComFunc.h"
#include "NasUtranCtrlInterface.h"

#include "MsccMmcInterface.h"
#include "NasUtranCtrlInterface.h"
#include "NasMmcSndCss.h"

#include "NasUsimmApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_BG_PLMN_SEARCH_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_UINT32    NAS_MMC_RcvTiHPlmnTimerExpired_BgPlmnSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo           = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrCampPlmnId        = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stHighPrioPlmnInfo;


    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 获取当前驻留网络的PLMNID */
    pstCurrCampPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* 获取MML中保存的当前EQU PLMN信息 */
    pstEquPlmnInfo = NAS_MML_GetEquPlmnList();

    /* 保存状态机入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 保存当前驻留网络到状态机上下文 */
    NAS_MMC_SetPreCampPlmn_BgPlmnSearch(pstCurrCampPlmnId, NAS_MML_GetCurrNetRatType());

    /* 保存当前驻留网络的EPLMN到状态机上下文 */
    NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(pstCurrCampPlmnId, pstEquPlmnInfo);

#if (FEATURE_ON == FEATURE_LTE)
    /* 保存当前L disable状态到状态机上下文 */
    NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch(NAS_MML_GetLteCapabilityStatus());
    /* 设置是否需要enable LTE标志,在快速指定搜中调用 */
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLTE_FastSpecSearch())
    {
        NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch(VOS_TRUE);
    }
#endif

    /* 如果获取高优先级网络失败退出状态机 */
    if (VOS_FALSE == NAS_MMC_GetNextSearchHighPrioPlmn(pstPlmnSelectionListInfo,
                                                       &stHighPrioPlmnInfo,
                                                       NAS_MMC_GetPreCampPlmn_BgPlmnSearch(),
                                                       NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch()))
    {
        /* 发送状态机结果为成功,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_SUCC, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 保存需要搜索的网络到状态机上下文 */
    NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(&(stHighPrioPlmnInfo.stPlmnId),
                                            stHighPrioPlmnInfo.astPlmnRatInfo[0].enRatType);

    /* 向接入层发送BG搜网,启动保护定时器,迁移状态 */
    NAS_MMC_SndBgPlmnSearchReq_BgPlmnSearch(&(stHighPrioPlmnInfo.stPlmnId),
                                            stHighPrioPlmnInfo.astPlmnRatInfo[0].enRatType);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiHighPrioRatHPlmnTimerExpired_BgPlmnSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo           = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrCampPlmnId        = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stHighPrioPlmnInfo;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
#endif

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 获取当前驻留网络的PLMNID */
    pstCurrCampPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* 获取MML中保存的当前EQU PLMN信息 */
    pstEquPlmnInfo = NAS_MML_GetEquPlmnList();

    /* 保存状态机入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 保存当前驻留网络到状态机上下文 */
    NAS_MMC_SetPreCampPlmn_BgPlmnSearch(pstCurrCampPlmnId, NAS_MML_GetCurrNetRatType());

    /* 保存当前驻留网络的EPLMN到状态机上下文 */
    NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(pstCurrCampPlmnId, pstEquPlmnInfo);

#if (FEATURE_ON == FEATURE_LTE)
    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

    /* 保存当前L disable状态到状态机上下文 */
    if (NAS_MML_LTE_CAPABILITY_STATUS_BUTT != enLteCapabilityStatus)
    {
        NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch(enLteCapabilityStatus);
    }
    /* 设置是否需要enable LTE标志,在快速指定搜中调用 */
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLTE_FastSpecSearch())
    {
        NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch(VOS_TRUE);
    }
#endif

    /* 如果获取高优先级网络失败退出状态机 */
    if (VOS_FALSE == NAS_MMC_GetNextSearchHighPrioPlmn(pstPlmnSelectionListInfo,
                                                       &stHighPrioPlmnInfo,
                                                       NAS_MMC_GetPreCampPlmn_BgPlmnSearch(),
                                                       NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch()))
    {
        /* 发送状态机结果为成功,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_SUCC, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 保存需要搜索的网络到状态机上下文 */
    NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(&(stHighPrioPlmnInfo.stPlmnId),
                                            stHighPrioPlmnInfo.astPlmnRatInfo[0].enRatType);

    /* 向接入层发送BG搜网,启动保护定时器,迁移状态 */
    NAS_MMC_SndBgPlmnSearchReq_BgPlmnSearch(&(stHighPrioPlmnInfo.stPlmnId),
                                            stHighPrioPlmnInfo.astPlmnRatInfo[0].enRatType);

    return VOS_TRUE;
}




VOS_UINT32    NAS_MMC_RcvTiPeriodHighPrioPlmnSearchExpired_BgPlmnSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo           = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrCampPlmnId        = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stHighPrioPlmnInfo;

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 获取当前驻留网络的PLMNID */
    pstCurrCampPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* 获取MML中保存的当前EQU PLMN信息 */
    pstEquPlmnInfo = NAS_MML_GetEquPlmnList();

    /* 保存状态机入口消息 */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 保存当前驻留网络到状态机上下文 */
    NAS_MMC_SetPreCampPlmn_BgPlmnSearch(pstCurrCampPlmnId, NAS_MML_GetCurrNetRatType());

    /* 保存当前驻留网络的EPLMN到状态机上下文 */
    NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(pstCurrCampPlmnId, pstEquPlmnInfo);

    /* 保存当前L disable状态到状态机上下文 */
#if (FEATURE_ON == FEATURE_LTE)
    /* 保存当前L disable状态到状态机上下文 */
    NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch(NAS_MML_GetLteCapabilityStatus());
    /* 设置是否需要enable LTE标志,在快速指定搜中调用 */
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLTE_FastSpecSearch())
    {
        NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch(VOS_TRUE);
    }
#endif

    /* 如果获取高优先级网络失败退出状态机 */
    if (VOS_FALSE == NAS_MMC_GetNextSearchHighPrioPlmn(pstPlmnSelectionListInfo,
                                                       &stHighPrioPlmnInfo,
                                                       NAS_MMC_GetPreCampPlmn_BgPlmnSearch(),
                                                       NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch()))
    {
        /* 发送状态机结果为成功,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_SUCC, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 保存需要搜索的网络到状态机上下文 */
    NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(&(stHighPrioPlmnInfo.stPlmnId),
                                            stHighPrioPlmnInfo.astPlmnRatInfo[0].enRatType);

    /* 向接入层发送BG搜网,启动保护定时器,迁移状态 */
    NAS_MMC_SndBgPlmnSearchReq_BgPlmnSearch(&(stHighPrioPlmnInfo.stPlmnId),
                                            stHighPrioPlmnInfo.astPlmnRatInfo[0].enRatType);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;

    /* 停止等BG搜网结果回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_BG_PLMN_SEARCH_CNF);


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    /* 通知AS停止BG搜网,迁移状态NAS_MMC_BG_PLMN_SELECTION_STA_WAIT_WAS_BG_PLMN_STOP_CNF，启动保护定时器 */
    NAS_MMC_SndAsBgStopPlmnSearchReq(WUEPS_PID_WRR);
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_STOP_CNF);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
#if (FEATURE_ON == FEATURE_LTE)

    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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

    /* CBS上报 */
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /* 转发系统消息通知 给 MM/GMM */
    NAS_MMC_SndMmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 无需判断原因值 */

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf: ENTERED");

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_BG_PLMN_SEARCH_CNF);

    /* 发送状态机结果为失败,不需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitWasBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_BG_PLMN_SEARCH_CNF_ST                             *pstBgSearchCnf           = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn       = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnRatValue          = VOS_NULL_PTR;

    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stSearchedPlmnListInfo;
    VOS_UINT8                                               ucHighRatBgProc;

    ucHighRatBgProc = VOS_FALSE;

    pstBgSearchCnf      = (RRMM_BG_PLMN_SEARCH_CNF_ST*)pstMsg;

    if (pstBgSearchCnf->ucPlmnNum > NAS_RRC_MAX_BG_SRCH_PLMN_NUM)
    {
        pstBgSearchCnf->ucPlmnNum = NAS_RRC_MAX_BG_SRCH_PLMN_NUM;
    }

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_BG_PLMN_SEARCH_CNF);

    switch ( pstBgSearchCnf->enSearchRlt )
    {
        case RRC_BG_PLMN_SEARCH_RLT_ABORT :

            /* 发送状态机结果为失败,不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);

            /* 退出当前状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            break;

        case RRC_BG_PLMN_SEARCH_RLT_SUCCESS :

            /* 更新BG搜索的网络状态为已搜索存在 */
            NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstCurHighPrioPlmn,
                                                    NAS_MMC_NET_STATUS_SEARCHED_EXIST,
                                                    pstPlmnSelectionListInfo);

            ucHighRatBgProc = NAS_MMC_IsHighPrioRatHplmnSearch_BgPlmnSearch();

            /* 当前BG搜和VPLMN的PLMN一样，但是RAT不同，不发起快速指定搜，退出状态机*/
            pstPlmnRatValue = NAS_MMC_GetPreCampPlmn_BgPlmnSearch();

            if ((VOS_TRUE  == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnRatValue->stPlmnId), &(pstCurHighPrioPlmn->stPlmnId)))
             && (VOS_FALSE == ucHighRatBgProc))
            {
                /* 发送状态机结果为成功,不需要搜网 */
                NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_SUCC, VOS_FALSE, VOS_NULL_PTR);

                /* 退出当前状态机 */
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;
            }

            /* 如果信令连接存在(WAS接入层在P态),先释放信令连接 */
            if (VOS_TRUE == NAS_MML_IsRrcConnExist())
            {
                NAS_MMC_SndRrMmRelReq(RRC_NAS_PS_DOMAIN);
                NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);
            }
            else
            {

                /* 向MM、GMM发送搜网指示 */
                NAS_MMC_SndGmmPlmnSchInit();
                NAS_MMC_SndMmPlmnSchInit();

                NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

                NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                         NAS_MML_GetSimPsRegStatus());

                /* 进行快速指定搜网 */
                NAS_MMC_PerformFastSpecSearch_BgPlmnSearch(&(pstCurHighPrioPlmn->stPlmnId),
                                                           pstCurHighPrioPlmn->enRat);
            }

            break;

        case RRC_BG_PLMN_SEARCH_RLT_FAIL :


            PS_MEM_SET(&stSearchedPlmnListInfo, 0x00, sizeof(stSearchedPlmnListInfo));

            /* 将BG搜索结果转换为内部搜网信息 */
            NAS_MMC_ConvertRrcBgPlmnSearchRslt2SearchedPlmnListInfo(pstCurHighPrioPlmn->enRat,
                                                                    pstBgSearchCnf,
                                                                    &stSearchedPlmnListInfo);
            /* 处理BG搜网的失败结果 */
            NAS_MMC_ProcBgPlmnSearchRlstFail_BgPlmnSearch(&stSearchedPlmnListInfo);

            break;

        default:

            /* 打印异常 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitWasBgPlmnSearchCnf: Unexpected Bg search result.");
            break;
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitWasBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchList = VOS_NULL_PTR;

    /* 获取高优先级搜网列表信息 */
    pstHighPrioPlmnSearchList = NAS_MMC_GetHighPrioPlmnList();

    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitWasBgPlmnSearchCnf: ENTERED");

    if (VOS_TRUE == NAS_MMC_IsHighPrioRatHplmnSearch_BgPlmnSearch())
    {
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_RAT_HPLMN_SEARCH,
                                      VOS_NULL_PTR,
                                      pstHighPrioPlmnSearchList);
    }
    else
    {
        /* 重新初始化选网列表 */
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                      VOS_NULL_PTR,
                                      pstHighPrioPlmnSearchList);
    }

    /* 通知AS停止BG搜网,迁移状态NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_STOP_CNF，启动保护定时器 */
    NAS_MMC_SndAsBgStopPlmnSearchReq(WUEPS_PID_WRR);
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_STOP_CNF);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;

    /* 停止等BG搜网结果回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_BG_PLMN_SEARCH_CNF);


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    /* 通知AS停止BG搜网,迁移状态NAS_MMC_BG_PLMN_SELECTION_STA_WAIT_GAS_BG_PLMN_STOP_CNF，启动保护定时器 */
    NAS_MMC_SndAsBgStopPlmnSearchReq(UEPS_PID_GAS);
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_STOP_CNF);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_BG_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_BG_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                           *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            stOldCampInfo;
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

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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
    NAS_MMC_SndMmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitGasBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_BG_PLMN_SEARCH_CNF_ST                             *pstBgSearchCnf           = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn       = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnRatValue          = VOS_NULL_PTR;

    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stSearchedPlmnListInfo;
    VOS_UINT8                                               ucHighRatBgProc;

    ucHighRatBgProc = VOS_FALSE;

    pstBgSearchCnf = (RRMM_BG_PLMN_SEARCH_CNF_ST*)pstMsg;

    if (pstBgSearchCnf->ucPlmnNum > NAS_RRC_MAX_BG_SRCH_PLMN_NUM)
    {
        pstBgSearchCnf->ucPlmnNum = NAS_RRC_MAX_BG_SRCH_PLMN_NUM;
    }

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_BG_PLMN_SEARCH_CNF);


    switch ( pstBgSearchCnf->enSearchRlt )
    {
        case RRC_BG_PLMN_SEARCH_RLT_ABORT :

            /* 发送状态机结果为失败,不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);

            /* 退出当前状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            break;

        case RRC_BG_PLMN_SEARCH_RLT_SUCCESS :

            /* 更新BG搜索的网络状态为已搜索存在 */
            NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstCurHighPrioPlmn,
                                                    NAS_MMC_NET_STATUS_SEARCHED_EXIST,
                                                    pstPlmnSelectionListInfo);

            ucHighRatBgProc = NAS_MMC_IsHighPrioRatHplmnSearch_BgPlmnSearch();

            /* 当前BG搜和VPLMN的PLMN一样，但是RAT不同，不发起快速指定搜，退出状态机*/
            pstPlmnRatValue = NAS_MMC_GetPreCampPlmn_BgPlmnSearch();

            if ((VOS_TRUE  == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnRatValue->stPlmnId), &(pstCurHighPrioPlmn->stPlmnId)))
             && (VOS_FALSE == ucHighRatBgProc))
            {
                /* 发送状态机结果为成功,不需要搜网 */
                NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_SUCC, VOS_FALSE, VOS_NULL_PTR);

                /* 退出当前状态机 */
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;
            }


            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());

            /* 进行快速指定搜网 */
            NAS_MMC_PerformFastSpecSearch_BgPlmnSearch(&(pstCurHighPrioPlmn->stPlmnId),
                                                       pstCurHighPrioPlmn->enRat);
            break;

        case RRC_BG_PLMN_SEARCH_RLT_FAIL :


            PS_MEM_SET(&stSearchedPlmnListInfo, 0x00, sizeof(stSearchedPlmnListInfo));

            /* 将BG搜索结果转换为内部搜网信息 */
            NAS_MMC_ConvertRrcBgPlmnSearchRslt2SearchedPlmnListInfo(pstCurHighPrioPlmn->enRat,
                                                                    pstBgSearchCnf,
                                                                    &stSearchedPlmnListInfo);
            /* 处理BG搜网的失败结果 */
            NAS_MMC_ProcBgPlmnSearchRlstFail_BgPlmnSearch(&stSearchedPlmnListInfo);

            break;

        default:

            /* 打印异常 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitGasBgPlmnSearchCnf: Unexpected Bg search result.");
            break;
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitGasBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchList = VOS_NULL_PTR;

    /* 获取高优先级搜网列表信息 */
    pstHighPrioPlmnSearchList = NAS_MMC_GetHighPrioPlmnList();

    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitGasBgPlmnSearchCnf: ENTERED");

    if (VOS_TRUE == NAS_MMC_IsHighPrioRatHplmnSearch_BgPlmnSearch())
    {
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_RAT_HPLMN_SEARCH,
                                      VOS_NULL_PTR,
                                      pstHighPrioPlmnSearchList);
    }
    else
    {
        /* 重新初始化选网列表 */
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                      VOS_NULL_PTR,
                                      pstHighPrioPlmnSearchList);
    }


    /* 通知AS停止BG搜网,迁移状态NAS_MMC_BG_PLMN_SELECTION_STA_WAIT_GAS_BG_PLMN_STOP_CNF，启动保护定时器 */
    NAS_MMC_SndAsBgStopPlmnSearchReq(UEPS_PID_GAS);
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_STOP_CNF);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_BG_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_BG_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf      = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstCurHighPrioPlmn = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* 打印异常 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitWasSuspendCnf: Suspend fail");

        /* 不可恢复错误,调用底软接口RESET */

        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return VOS_TRUE;
    }

    /* 设置当前接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 进行快速指定搜网 */
    NAS_MMC_PerformFastSpecSearch_BgPlmnSearch(&(pstCurHighPrioPlmn->stPlmnId),
                                               pstCurHighPrioPlmn->enRat);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnf: ENTERED");

    /* 不可恢复故障，复位 */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat)
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}



VOS_UINT32    NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf      = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstCurHighPrioPlmn = VOS_NULL_PTR;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* 打印异常 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitGasSuspendCnf: Suspend fail");

        /* 不可恢复错误,调用底软接口RESET */

        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    /* 设置当前接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 进行快速指定搜网 */
    NAS_MMC_PerformFastSpecSearch_BgPlmnSearch(&(pstCurHighPrioPlmn->stPlmnId),
                                               pstCurHighPrioPlmn->enRat);

    return VOS_TRUE;
}



VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
#if (FEATURE_ON == FEATURE_LTE)

    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);


    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */

        NAS_MMC_SndMsccSysInfo();
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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

    /* CBS上报 */
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /* 转发系统消息通知 给 MM/GMM */
    NAS_MMC_SndMmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 无需判断原因值 */

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasBgStopCnf: ENTERED");

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF);

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为失败,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvBgPlmnStopCnf_BgPlmnSearch_WaitWasBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF);

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为失败,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32    NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitAsBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_BG_PLMN_SEARCH_CNF_ST                             *pstBgSearchCnf;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stSearchedPlmnListInfo;

    pstBgSearchCnf      = (RRMM_BG_PLMN_SEARCH_CNF_ST*)pstMsg;

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    if (RRC_BG_PLMN_SEARCH_RLT_FAIL == pstBgSearchCnf->enSearchRlt)
    {
        NAS_MMC_ConvertRrcBgPlmnSearchRslt2SearchedPlmnListInfo(pstCurHighPrioPlmn->enRat,
                                                                pstBgSearchCnf,
                                                                &stSearchedPlmnListInfo);

        /* 根据搜索列表更新网络状态 */
        NAS_MMC_UpdatePlmnListInPlmnSelectionList(&stSearchedPlmnListInfo,
                                                  pstPlmnSelectionListInfo,
                                                  VOS_FALSE,
                                                  VOS_TRUE);
    }

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF);

    /*GU都调用此函数，两个定时器都要停*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_BG_PLMN_STOP_CNF);


    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为失败,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitWasBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitWasBgStopCnf: ENTERED");

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为失败,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasBgPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                           *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            stOldCampInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

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

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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
    NAS_MMC_SndMmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvBgPlmnStopCnf_BgPlmnSearch_WaitGasBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_BG_PLMN_STOP_CNF);

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为失败,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32    NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitGasBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitGasBgStopCnf: ENTERED");

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为失败,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasFastPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasFastPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 无需判断原因值 */

    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasFastPlmnStopCnf: ENTERED");

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        /* 对NO RF进行处理 */
        NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmPlmnSrchStopCnf_BgPlmnSearch_WaitWasFastPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitWasStopCnfExpired_BgPlmnSearch_WaitWasFastPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStopCnfExpired_BgPlmnSearch_WaitWasFastPlmnStopCnf: ENTERED");

    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
;

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }


    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasFastPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmPlmnSearchStopCnf_BgPlmnSearch_WaitGasFastPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitAsFastPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg            = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn       = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /*GU都调用此函数，定时器都要停*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 对NO RF进行处理 */
        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MMC_GetPreCampPlmn_BgPlmnSearch()->enRat);
        }
        else
        {
            NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_GetCurrNetRatType());
        }

        return VOS_TRUE;
    }

    if (RRC_PLMN_SEARCH_RLT_SPEC_FAIL == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 更新当前搜索网络状态为已搜索不存在 */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstCurHighPrioPlmn,
                                                       NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,
                                                       pstPlmnSelectionListInfo);
    }



    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}



VOS_UINT32    NAS_MMC_RcvTiWaitGasStopCnfExpired_BgPlmnSearch_WaitGasFastPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStopCnfExpired_BgPlmnSearch_WaitGasFastPlmnStopCnf: ENTERED");

    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
;

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }


    return VOS_TRUE;
}



VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasPlmnFastSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;

    /* 停止等BG搜网结果回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    /* 通知AS停止快速指定搜网,迁移状态,启动保护定时器 */
    NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_FAST_PLMN_STOP_CNF);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitWasPlmnFastSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg            = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn       = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 停止等快速搜网结果回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    if (RRC_PLMN_SEARCH_RLT_SPEC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 根据不同的搜网模式，迁移到不同的L2状态，启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
    }
    else if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 对NO RF进行处理 */
        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MMC_GetPreCampPlmn_BgPlmnSearch()->enRat);
        }
        else
        {
            NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }

        return VOS_TRUE;
    }
    else
    {
        /* 更新当前搜索网络状态为已搜索不存在 */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstCurHighPrioPlmn,
                                                NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,
                                                pstPlmnSelectionListInfo);

        /* 搜索下一个高优先级网络 */
        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
        }
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnFastSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn       = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    /* 无需判断原因值 */

    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnFastSearchCnf: ENTERED");

    /* 停止等快速搜网结果回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* 更新当前搜索网络状态为已搜索不存在 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstCurHighPrioPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,
                                            pstPlmnSelectionListInfo);

    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        /* 对NO RF进行处理 */
        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MMC_GetPreCampPlmn_BgPlmnSearch()->enRat);
        }
        else
        {
            NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }

        return VOS_TRUE;
    }

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_BgPlmnSearch_WaitWasPlmnFastSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn       = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_BgPlmnSearch_WaitWasPlmnFastSearchCnf: ENTERED");

    /* 更新当前搜索网络状态为已搜索不存在 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstCurHighPrioPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,
                                            pstPlmnSelectionListInfo);

    /* 通知AS停止快速指定搜网,迁移状态,启动保护定时器 */
    NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_FAST_PLMN_STOP_CNF);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasPlmnFastSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;

    /* 停止等BG搜网结果回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    /* 通知AS停止快速指定搜网,迁移状态,启动保护定时器 */
    NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_FAST_PLMN_STOP_CNF);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitGasPlmnFastSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg            = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn       = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 停止等快速搜网结果回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    if (RRC_PLMN_SEARCH_RLT_SPEC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 根据不同的搜网模式，迁移到不同的L2状态，启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);
    }
    else if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 对NO RF进行处理 */
        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MMC_GetPreCampPlmn_BgPlmnSearch()->enRat);
        }
        else
        {
            NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }


        return VOS_TRUE;
    }
    else
    {
        /* 更新当前搜索网络状态为已搜索不存在 */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstCurHighPrioPlmn,
                                                NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,
                                                pstPlmnSelectionListInfo);

        /* 搜索下一个高优先级网络 */
        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_BgPlmnSearch_WaitGasPlmnFastSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn       = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_BgPlmnSearch_WaitGasPlmnFastSearchCnf: ENTERED");

    /* 更新当前搜索网络状态为已搜索不存在 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstCurHighPrioPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,
                                            pstPlmnSelectionListInfo);

    /* 通知AS停止快速指定搜网,迁移状态,启动保护定时器 */
    NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_FAST_PLMN_STOP_CNF);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif

    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 正常服务状态，等本次注册完成再上报系统消息 */
        if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch(VOS_TRUE);
        }
        else
        {
            /* 主动上报 */
            NAS_MMC_SndMsccSysInfo();
        }
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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

    /* CBS上报 */
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /* 转发系统消息通知 给 MM/GMM */
    NAS_MMC_SndMmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    /* 更新当前等待CSPS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();
    NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 更新CSPS的AdditionalAction */
    NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* 收到系统消息后迁移到等待CS+PS域的注册结果并启动定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitWasSysInfoExpired_BgPlmnSearch_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSysInfoExpired_BgPlmnSearch_WaitWasSysInfoInd: ENTERED");

    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSysInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif

    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
            /* 正常服务状态，等本次注册完成再上报系统消息 */
        if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch(VOS_TRUE);
        }
        else
        {
            /* 主动上报 */
            NAS_MMC_SndMsccSysInfo();
        }
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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
    NAS_MMC_SndMmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    /* 更新当前等待CSPS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();
    NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 更新CSPS的AdditionalAction */
    NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* 收到系统消息后迁移到等待CS+PS域的注册结果并启动定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitGasSysInfoExpired_BgPlmnSearch_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasSysInfoExpired_BgPlmnSearch_WaitGasSysInfoInd: ENTERED");

    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }


    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU                *pstAbortMsg = VOS_NULL_PTR;
    NAS_MMC_WAIT_REG_RSLT_IND_ENUM_UINT8   enRegRslt;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;
    /* 提取函数 */
    NAS_MMC_SndMsccSysInfo_BgPlmnSearch();


    /* 若打断类型是用户请求的关机，则直接退出等注册结果状态机 */
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* 发送状态机结果为ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch( NAS_MMC_BG_PLMN_SEARCH_ABORTED,
                                      VOS_FALSE, VOS_NULL_PTR );

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    /* 如果当前存在立即打断标志，则主动释放 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == pstAbortMsg->enAbortFsmType)
    {
        /* 停止等待注册结果定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);


        /* 在注册过程中收到立即打断，意味着注册尚未完成，更新未完成的域的服务
           状态为LIMIT SERVICE，否则当前的服务状态可能为NORMAL_SERVICE,这样若被用户
           指定搜打断，且网络接入技术都相同的情况下，就不会进行搜网注册了 */
        enRegRslt = NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch();
        if ( enRegRslt>= NAS_MMC_WAIT_REG_RESULT_IND_BUTT )
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch:NAS_MMC_WAIT_REG_RESULT_IND_BUTT");
        }
        NAS_MMC_UpdateDomainServiceStatus(enRegRslt,
                                          NAS_MMC_LIMITED_SERVICE);


        /* 如果当前不存在链接，则退出状态机 */
        if (VOS_FALSE == NAS_MML_IsRrcConnExist())
        {
            /* 发送状态机结果为ABORT,不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch( NAS_MMC_BG_PLMN_SEARCH_ABORTED,
                                                VOS_FALSE, VOS_NULL_PTR );

            /* 直接退出当前状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }

        /* 如果当前存在链接,设置主动释放标志 */
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_TRUE);

        /* 向MM、GMM发送主动释放请求 */
        NAS_MMC_SndMmRelReq();
        NAS_MMC_SndGmmRelReq();

        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

        /* 状态迁移到等待连接释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND);

        /* 启动等待连接释放定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvGmmPsRegResultInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* 针对CCO失败回退过程中收到的异系统的注册结果，不需要处理 */
    if (pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 清除PS域的等待标志 */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    if(GMM_MMC_ACTION_RESULT_SUCCESS == pstPsRegRslt->enActionResult)
    {
        /*注册结果为SUCCESS，需先报系统消息，再报注册结果*/
        NAS_MMC_SndMsccSysInfo_BgPlmnSearch();
    }
    else
    {
        /*注册结果为failure，如果注册结果收齐，需先报系统消息*/
        if (NAS_MMC_WAIT_REG_RESULT_IND_NULL == NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch())
        {
            NAS_MMC_SndMsccSysInfo_BgPlmnSearch();
        }
    }

    /* 处理PS注册结果 */
    NAS_MMC_ProcPsRegRslt_BgPlmnSearch(pstPsRegRslt);

    /* 如果注册结果还未收齐，退出函数, 继续等待 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch())
    {
        return VOS_TRUE;
    }

    /* 如果需要Abort */
    if (NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        NAS_MMC_PerformAbortRegFinished_BgPlmnSearch();
    }
    else
    {
        /* 如果不需要Abort，根据CS和PS的dditional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionRegFinished_BgPlmnSearch();
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmCsRegResultInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* 针对CCO失败回退过程中收到的异系统的注册结果，不需要处理 */
    if (pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 清除CS域的等待标志 */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_CS);

    /*注册结果为 successful 需先上系统消息再报状态，无需等收齐*/
    if (MM_MMC_LU_RESULT_SUCCESS == pstCsRegRslt->enLuResult)
    {
        NAS_MMC_SndMsccSysInfo_BgPlmnSearch();
    }
    else
    {
        /*注册结果为failure，等收齐后再上报系统消息*/
        if (NAS_MMC_WAIT_REG_RESULT_IND_NULL == NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch())
        {
            NAS_MMC_SndMsccSysInfo_BgPlmnSearch();
        }
    }

    /* 处理CS注册结果 */
    NAS_MMC_ProcCsRegRslt_BgPlmnSearch(pstCsRegRslt);

    /* 如果注册结果还未收齐，退出函数, 继续等待 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch())
    {
        return VOS_TRUE;
    }

    /* 如果需要Abort */
    if (NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        NAS_MMC_PerformAbortRegFinished_BgPlmnSearch();
    }
    else
    {
        /* 如果不需要Abort，根据CS和PS的dditional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionRegFinished_BgPlmnSearch();
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmAbortInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_ABORT_IND_STRU               *pstMmAbortInd   = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;
#endif

    pstMmAbortInd = (MMMMC_ABORT_IND_STRU*)pstMsg;

    /* 如果原因值不为#6，且不为#17，直接返回 */
    if ((NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME != pstMmAbortInd->enAbortCause)
     && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != pstMmAbortInd->enAbortCause))
    {
        return VOS_TRUE;
    }

    /* 如果原因值#6，设置CS Addition为Anycell驻留 */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstMmAbortInd->enAbortCause)
    {
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* 给LMM发送ID_MMC_LMM_ACTION_RESULT_REQ */
    /* 构造ActionRslt消息，结果为CN_Rej,类型填为新增NAS_MML_PROC_MM_ABORT类型
       请求和结果域都是CS，原因值为Abort带的原因值 */
    stActionRslt.enProcType     = NAS_MML_PROC_MM_ABORT;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_CN_REJ;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = pstMmAbortInd->enAbortCause;
    stActionRslt.ulAttemptCount = 0x0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    return VOS_TRUE;
}





VOS_UINT32    NAS_MMC_RcvGmmNetworkDetachInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_NETWORK_DETACH_IND_STRU                         *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstDetachMsg = (MMCGMM_NETWORK_DETACH_IND_STRU*)pstMsg;

    /* 清除PS域的等待标志 */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 注册结果收齐了，需先报系统消息 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL == NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch())
    {
        NAS_MMC_SndMsccSysInfo_BgPlmnSearch();
    }

    /* 处理Detach结果 */
    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction有效，更新PS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(enAdditionalAction);
    }

    /* 需要继续注册时，不需要执行后续的动作 */
    if (NAS_MMC_GMM_NT_DETACH_REATTACH == pstDetachMsg->ulDetachType)
    {
        return VOS_TRUE;
    }

#if   (FEATURE_ON == FEATURE_LTE)
    /* 给LMM发送detach结果消息 */
    NAS_MMC_SndLmmMtDetachIndActionResultReq(pstDetachMsg->ulDetachType,
        (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);
#endif

    /* 如果注册结果还未收齐，退出函数, 继续等待 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch())
    {
        return VOS_TRUE;
    }


    /* 如果需要Abort */
    if (NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        NAS_MMC_PerformAbortRegFinished_BgPlmnSearch();
    }
    else
    {
        /* 如果不需要Abort，根据CS和PS的dditional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionRegFinished_BgPlmnSearch();
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvGmmServiceRequestResultInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
#endif

    pstServiceRsltInd = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pstMsg;

    /*清除PS等待注册结果标示*/
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstServiceRsltInd->ulServiceSts)
    {
        /*注册结果为 successful 需先上系统消息再报状态，无需等收齐*/
        NAS_MMC_SndMsccSysInfo_BgPlmnSearch();

        /* 更新PS的AdditionalAction */
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
        /* 给LMM发送Service requestResult结果消息处理*/
        stActionRslt.enProcType     = NAS_MML_PROC_SER;
        stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
        stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
        stActionRslt.ulAttemptCount = 0;

        NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);

#endif
    }
    else
    {
        /*注册结果收齐了，需先报系统消息*/
        if (NAS_MMC_WAIT_REG_RESULT_IND_NULL == NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch())
        {
            NAS_MMC_SndMsccSysInfo_BgPlmnSearch();
        }
        /* 如果服务失败，处理不同拒绝原因值，返回PS additional Action */
        enAdditionalAction = NAS_MMC_ProcPsServiceRegFail(pstServiceRsltInd);

        /* AdditionalAction有效，更新PS的下一步的动作类型 */
        if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
        {
            NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(enAdditionalAction);
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* 给LMM发送Service requestResult结果消息处理 */
        stActionRslt.enProcType     = NAS_MML_PROC_SER;
        stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
        stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enCnCause      = pstServiceRsltInd->enRegFailCause;
        stActionRslt.ulAttemptCount = 0;

        NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);

#endif


    }

    /* 如果注册结果还未收齐，退出函数, 继续等待 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch())
    {
        return VOS_TRUE;
    }

    /* 如果需要Abort */
    if (NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        NAS_MMC_PerformAbortRegFinished_BgPlmnSearch();
    }
    else
    {
        /* 如果不需要Abort，根据CS和PS的dditional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionRegFinished_BgPlmnSearch();
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvCmServiceRejectInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_CM_SERVICE_REJECT_IND_STRU   *pstCmServiceRejMsg = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;
#endif

    pstCmServiceRejMsg = (MMCMM_CM_SERVICE_REJECT_IND_STRU*)pstMsg;

#if (FEATURE_ON == FEATURE_LTE)
    stActionRslt.enProcType     = NAS_MML_PROC_CM_SER;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstCmServiceRejMsg->ulCause;
    stActionRslt.ulAttemptCount = 0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);

#endif

    /* 如果拒绝原因为NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstCmServiceRejMsg->ulCause)
    {
        /* 清除CS域的等待标志 */
        NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_CS);

        /* 设置CS additional Action为限制驻留 */
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

    /* 如果注册结果还未收齐，退出函数, 继续等待 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch())
    {
        return VOS_TRUE;
    }

    /* 系统消息在预处理中发送 */

    /* 如果需要Abort */
    if (NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        NAS_MMC_PerformAbortRegFinished_BgPlmnSearch();
    }
    else
    {
        /* 如果不需要Abort，根据CS和PS的dditional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionRegFinished_BgPlmnSearch();
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvWasSuspendInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstSuspendMsg = VOS_NULL_PTR;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    if ((MMC_SUSPEND_CAUSE_PLMNSEARCH == pstSuspendMsg->ucSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= pstSuspendMsg->ucSuspendCause))
    {
        /* 如果是OOS场景，返回挂起失败 */
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, WUEPS_PID_WRR);
    }
    else
    {
        /* 否则根据挂起原因值，启动不同的状态机 */
        NAS_MMC_LoadInterSysFsm_BgPlmnSearch(pstSuspendMsg->ucSuspendCause);
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvGasSuspendInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstSuspendMsg = VOS_NULL_PTR;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    if ((MMC_SUSPEND_CAUSE_PLMNSEARCH == pstSuspendMsg->ucSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= pstSuspendMsg->ucSuspendCause))
    {
        /* 如果是OOS场景，返回挂起失败 */
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, UEPS_PID_GAS);
    }
    else
    {
        /* 否则根据挂起原因值，启动不同的状态机 */
        NAS_MMC_LoadInterSysFsm_BgPlmnSearch(pstSuspendMsg->ucSuspendCause);
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcMmcSuspendRslt_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRsltMsg = VOS_NULL_PTR;

    pstSuspendRsltMsg = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    /* 如果重选结果为失败,原因为出服务区,则当作注册过程中出服务区处理 */
    if ((NAS_MMC_SUSPEND_FAIL == pstSuspendRsltMsg->enRslt)
     && (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST == pstSuspendRsltMsg->enFailCause))
    {
        /* 停止等待注册结果定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
        {
            /* 向上层状态机发送背景搜索失败，不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);

            /* 退出当前状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }

        /* 如果当前有ABORT标志，则回VPLMN */
        if ( NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch() )
        {
            /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
               disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

            if (VOS_TRUE == NAS_MMC_IsVplmnValid())
            {
                /* 向MM、GMM发送搜网指示 */
                NAS_MMC_SndGmmPlmnSchInit();
                NAS_MMC_SndMmPlmnSchInit();

                NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

                NAS_MMC_ReCampVPlmn_BgPlmnSearch();
                return VOS_TRUE;
            }

            /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }
        else
        {
            /* 搜索下一个高优先级网络 */
            if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
            {
                /* 向上层状态机发送高优先级搜索失败，需要搜网 */
                NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

                /* 退出状态机 */
                NAS_MMC_FSM_QuitFsmL2();
                return VOS_TRUE;
            }

            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        }

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 迁移到不同的接入技术时，需要迁移到不同的处理注册结果状态 */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* 停止当前等待CS/PS注册结果的状态 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* 更新当前等待EPS的注册结果 */
        NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();
        NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

#if (FEATURE_ON == FEATURE_IMS)
        /* 增加等待IMS是否可用结果FLG,MMA保证收到PS注册结果上报IMS是否可用指示到MMC */
        NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

        /* 更新CS的注册Cause和AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* 迁移到等待注册结果子状态:NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

        return VOS_TRUE;
    }
#endif

    return VOS_TRUE;
}

 
VOS_UINT32    NAS_MMC_RcvAreaLostInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    /* 停止等待注册结果定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);

    NAS_MMC_SndMsccSysInfo_BgPlmnSearch();

    /* 获取当前驻留的网络信息 */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    /* 更新当前网络的搜索状态为已注册过，在此轮高优先级搜网中，不会再搜此网络 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                            NAS_MMC_GetHighPrioPlmnList());

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());


    /* 通知MM/GMM进入丢网,MM会释放CS业务 */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();


    /* 如果当前存在NO RF，退状态机，发送失败消息后迁移到OOC状态 */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 向上层状态机发送高优先级搜索失败，不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
    /* 如果当前有ABORT标志，则回VPLMN */
    if ( NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch() )
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 清空等待注册结果标志 */
    NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;

    }

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

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
        /* 背景搜收到系统消息时，当前限制服务，已经给MMA发了系统消息，此处可以给MMA发。
           否则要等到收到注册结果后再给MMA发送系统消息 */
        if (VOS_FALSE == NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch())
        {
            /* 主动上报 */
            NAS_MMC_SndMsccSysInfo();

        }
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

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /* 重新设置等待CS、PS注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();
    NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
    NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                               VOS_FALSE,
                               pstMsg);

    NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                               VOS_FALSE,
                               pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
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
        /* 背景搜收到系统消息时，当前限制服务，已经给MSCC发了系统消息，此处可以给MSCC发。
           否则要等到收到注册结果后再给MSCC发送系统消息 */
        if (VOS_FALSE == NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch())
        {
            /* 主动上报 */
            NAS_MMC_SndMsccSysInfo();
        }
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

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /* 重新设置等待CS、PS注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();
    NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
    NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                               VOS_FALSE,
                               pstMsg);

    NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                               VOS_FALSE,
                               pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果VPLMN接入技术当前不支持，不需将VPLMN接入技术更新为SYSCFG设置的最高优先接入技术，
       等获取下一个网络时再判断vplmn接入技术是否有效，vplmn无效时需要退状态机结果为需要搜网，
       重新驻留后再进行背景搜，该函数现不做处理，留作后续扩展使用 */
    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_BgPlmnSearch_WaitCsPsRegRsltInd: ENTERED");

    NAS_MMC_SndMsccSysInfo_BgPlmnSearch();

    /* 如果存在信令连接 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 状态迁移到等待连接释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND);

        /* 启动等待连接释放定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    if (NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 如果需要Abort，进行回VPLMN操作 */
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }
    else
    {
        /* 清空等待注册结果标志 */
        NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();

        /* 否则获取下一个高优先级网络进行搜索 */
        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;

        }

        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucRelRequestFlg;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 若打断类型是用户请求的关机，则直接退出等链接释放结果状态机 */
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)

    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        /* 发送状态机结果为ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch( NAS_MMC_BG_PLMN_SEARCH_ABORTED,
                                      VOS_FALSE, VOS_NULL_PTR );

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    ucRelRequestFlg = NAS_MMC_GetRelRequestFlag_BgPlmnSearch();

    /* 如果当前存在立即打断标志而且不是主动释放，则主动释放 */
    if ((NAS_MMC_ABORT_FSM_IMMEDIATELY == pstAbortMsg->enAbortFsmType)
     && (VOS_FALSE == ucRelRequestFlg))
    {
        /* 设置主动释放标志 */
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_TRUE);

        /* 向MM、GMM发送主动释放请求 */
        NAS_MMC_SndMmRelReq();
        NAS_MMC_SndGmmRelReq();

        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvGmmSignalingStatusInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果仍然存在信令连接，继续等待 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    /* 停止等待信令连接释放保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 如果Abor类型为立即退出，则退出状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果Abort类型是延迟退出，进行回VPLMN操作 */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 如果是主动释放(例如等待连接释放超时),搜索下一个网络 */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_BgPlmnSearch())
    {
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_FALSE);

        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;

        }


        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    }
    else
    {
        /* 当前为被动释放，根据CS和PS的additional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();
    }


    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvGmmNetworkDetachInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_NETWORK_DETACH_IND_STRU                         *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstDetachMsg = (MMCGMM_NETWORK_DETACH_IND_STRU *)pstMsg;

    /* 处理Detach结果 */
    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction有效，更新PS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(enAdditionalAction);
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvGmmTbfRelInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果仍然存在信令连接，继续等待 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    /* 停止等待信令连接释放保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 如果Abor类型为立即退出，则退出状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果Abort类型是延迟退出，进行回VPLMN操作 */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 如果是主动释放(例如等待连接释放超时),搜索下一个网络 */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_BgPlmnSearch())
    {
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_FALSE);

        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;

        }

        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    }
    else
    {
        /* 当前为被动释放，根据CS和PS的additional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvGmmServiceRequestResultInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
#endif

    pstServiceRsltInd = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pstMsg;

    /* 如果服务成功 */
    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstServiceRsltInd->ulServiceSts)
    {
        /* 更新PS的AdditionalAction */
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
#if (FEATURE_ON == FEATURE_LTE)
        /* 给LMM发送Service requestResult结果消息处理 */
        stActionRslt.enProcType     = NAS_MML_PROC_SER;
        stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
        stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
        stActionRslt.ulAttemptCount = 0;

        NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif
    }
    else
    {
        /* 如果服务失败，处理不同拒绝原因值，返回PS additional Action */
        enAdditionalAction = NAS_MMC_ProcPsServiceRegFail(pstServiceRsltInd);

        /* AdditionalAction有效，更新PS的下一步的动作类型 */
        if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
        {
            NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(enAdditionalAction);
        }


#if (FEATURE_ON == FEATURE_LTE)
        /* 给LMM发送Service requestResult结果消息处理 */
        stActionRslt.enProcType     = NAS_MML_PROC_SER;
        stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
        stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enCnCause      = pstServiceRsltInd->enRegFailCause;
        stActionRslt.ulAttemptCount = 0;

        NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmConnInfoInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果仍然存在信令连接，继续等待 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    /* 停止等待信令连接释放保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 如果Abor类型为立即退出，则退出状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果Abort类型是延迟退出，进行回VPLMN操作 */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 如果是主动释放(例如等待连接释放超时),搜索下一个网络 */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_BgPlmnSearch())
    {
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_FALSE);

        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }

        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    }
    else
    {
        /* 当前为被动释放，根据CS和PS的additional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmRrRelInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果仍然存在信令连接，继续等待 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    /* 停止等待信令连接释放保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 如果Abor类型为立即退出，则退出状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果Abort类型是延迟退出，进行回VPLMN操作 */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 如果是主动释放(例如等待连接释放超时),搜索下一个网络 */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_BgPlmnSearch())
    {
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_FALSE);

        /* 搜索下一个高优先级网络 */
        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }

        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    }
    else
    {
        /* 当前为被动释放，根据CS和PS的additional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();
    }
    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvCmServiceRejectInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_CM_SERVICE_REJECT_IND_STRU   *pstCmServiceRejMsg = VOS_NULL_PTR;

    pstCmServiceRejMsg = (MMCMM_CM_SERVICE_REJECT_IND_STRU*)pstMsg;

    /* 如果拒绝原因为NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstCmServiceRejMsg->ulCause)
    {
        /* 设置CS additional Action为限制驻留 */
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvGmmPsRegResultInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* 针对CCO失败回退过程中收到的异系统的注册结果，不需要处理 */
    if (pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理PS注册结果 */
    NAS_MMC_ProcPsRegRslt_BgPlmnSearch(pstPsRegRslt);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmCsRegResultInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* 针对CCO失败回退过程中收到的异系统的注册结果，不需要处理 */
    if (pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* 处理CS注册结果 */
    NAS_MMC_ProcCsRegRslt_BgPlmnSearch(pstCsRegRslt);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmAbortInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_ABORT_IND_STRU               *pstMmAbortInd   = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;
#endif

    pstMmAbortInd = (MMMMC_ABORT_IND_STRU*)pstMsg;

    /* 如果原因值不为#6，且不为#17，直接返回 */
    if ((NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME != pstMmAbortInd->enAbortCause)
     && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != pstMmAbortInd->enAbortCause))
    {
        return VOS_TRUE;
    }

    /* 如果原因值#6，设置CS Addition为Anycell驻留 */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstMmAbortInd->enAbortCause)
    {
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* 给LMM发送ID_MMC_LMM_ACTION_RESULT_REQ */
    /* 构造ActionRslt消息，结果为CN_Rej,类型填为新增NAS_MML_PROC_MM_ABORT类型
       请求和结果域都是CS，原因值为Abort带的原因值 */
    stActionRslt.enProcType     = NAS_MML_PROC_MM_ABORT;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_CN_REJ;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = pstMmAbortInd->enAbortCause;
    stActionRslt.ulAttemptCount = 0x0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    return VOS_TRUE;
}




VOS_UINT32    NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU         *pstVplmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;
    VOS_UINT32                          ulIsVplmnNetRatValid;

    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    pstVplmn             = NAS_MMC_GetPreCampPlmn_BgPlmnSearch();

    enRatType            = NAS_MML_GetCurrNetRatType();

    /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
       disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

    ulIsVplmnNetRatValid = NAS_MMC_IsVplmnValid();


    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        /* 停止等待信令连接释放保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        /* 向上层状态机发送高优先级搜索失败，不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果仍然存在信令连接，继续等待 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    /* 停止等待信令连接释放保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 如果Abor类型为立即退出，则退出状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果Abort类型是延迟退出，进行回VPLMN操作 */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* W下P态可以发起背景搜，快速指定搜前如果有rrc连接会迁到等连接释放，
           此时收到list搜网请求延迟打断时，无需回vplmn，可直接退出状态机 */
        if (((VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(NAS_MML_GetCurrCampPlmnId(), &pstVplmn->stPlmnId))
           || (enRatType != pstVplmn->enRat))
         && (VOS_TRUE == ulIsVplmnNetRatValid))
        {
            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 如果是主动释放(例如等待连接释放超时),搜索下一个网络 */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_BgPlmnSearch())
    {
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_FALSE);

        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }


        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    }
    else
    {
        /* 当前为被动释放，根据CS和PS的additional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmSuspendInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstSuspendMsg = VOS_NULL_PTR;
    VOS_UINT32                          ucRelRequestFlg;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    ucRelRequestFlg = NAS_MMC_GetRelRequestFlag_BgPlmnSearch();

    /* 如果主动释放或者存在Abort标志或是OOS场景，返回挂起失败 */
    if ((NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
     || (VOS_TRUE == ucRelRequestFlg)
     || (MMC_SUSPEND_CAUSE_PLMNSEARCH == pstSuspendMsg->ucSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= pstSuspendMsg->ucSuspendCause))
    {
        /* 返回挂起失败 */
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, pstSuspendMsg->MsgHeader.ulSenderPid);

        return VOS_TRUE;
    }

    /* 否则根据挂起原因值，启动不同的状态机 */
    NAS_MMC_LoadInterSysFsm_BgPlmnSearch(pstSuspendMsg->ucSuspendCause);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcSuspendRslt_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRsltMsg = VOS_NULL_PTR;

    pstSuspendRsltMsg = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    /* 如果重选结果为失败,原因为出服务区,则当作连接已释放处理 */
    if ((NAS_MMC_SUSPEND_FAIL == pstSuspendRsltMsg->enRslt)
     && (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST == pstSuspendRsltMsg->enFailCause))
    {
        /* 停止等待信令连接释放保护定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
        {
            /* 向上层状态机发送背景搜索失败，不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);

            /* 退出当前状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }

        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }

        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 迁移到不同的接入技术时，需要迁移到不同的处理注册结果状态 */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* 停止当前等待CS/PS连接释放的状态 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        /* 更新当前等待EPS的注册结果 */
        NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();
        NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

#if (FEATURE_ON == FEATURE_IMS)
        /* 增加等待IMS是否可用结果FLG,MSCC保证收到PS注册结果上报IMS是否可用指示到MMC */
        NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

        /* 更新CS的AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* 迁移到等待注册结果子状态PLMN_SRCH:NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

        return VOS_TRUE;
    }
#endif

    /*  如果存在信令连接，则继续等待  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* 在重选之前已经判断,此时不可能存在Abort或者主动释放,如果信令连接不存在可能发起搜网 */
    NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();


    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 如果是主动请求释放,由于需要立即进行搜网,系统消息不处理 */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_BgPlmnSearch())
    {
        return VOS_TRUE;
    }

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
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

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /*转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
    NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* 如果是主动请求释放,由于需要立即进行搜网,系统消息不处理 */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_BgPlmnSearch())
    {
        return VOS_TRUE;
    }

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

     pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
     pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

     PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
     PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
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

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /*转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
    NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果VPLMN接入技术当前不支持，不需将VPLMN接入技术更新为SYSCFG设置的最高优先接入技术，
       等获取下一个网络时再判断vplmn接入技术是否有效，vplmn无效时需要退状态机结果为需要搜网，
       重新驻留后再进行背景搜，该函数现不做处理，留作后续扩展使用 */
    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitRrcConnRelExpired_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucRelRequestFlg;
    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortType;
    VOS_UINT32                          ulCsServiceExist;
    VOS_UINT32                          ulPsServiceExist;

    enAbortType = NAS_MMC_GetAbortType_BgPlmnSearch();

    ucRelRequestFlg = NAS_MMC_GetRelRequestFlag_BgPlmnSearch();

    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitRrcConnRelExpired_BgPlmnSearch_WaitRrcConnRelInd: ENTERED");

    /* 如果Abort类型为立即退,则退出状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == enAbortType)
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果Abort类型为延迟退,根据是否主动释放分别处理 */
    if (NAS_MMC_ABORT_FSM_DELAY == enAbortType)
    {
        if (VOS_TRUE == ucRelRequestFlg)
        {
            /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
               disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

            if (VOS_TRUE == NAS_MMC_IsVplmnValid())
            {
                /* 向MM、GMM发送搜网指示 */
                NAS_MMC_SndGmmPlmnSchInit();
                NAS_MMC_SndMmPlmnSchInit();

                NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

                NAS_MMC_ReCampVPlmn_BgPlmnSearch();
                return VOS_TRUE;
            }

            /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }
        else
        {
            /* 发送主动释放请求到MM、GMM，重新启动等待连接释放定时器 */
            NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_TRUE);
            NAS_MMC_SndMmRelReq();
            NAS_MMC_SndGmmRelReq();

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);
        }

        return VOS_TRUE;
    }

    /* 如果是主动释放且不需要Abort，搜索下一个高优先级网络 */
    if (VOS_TRUE == ucRelRequestFlg)
    {
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_FALSE);

        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }


        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

        return VOS_TRUE;
    }

    ulCsServiceExist         = NAS_MML_GetCsServiceExistFlg();
    ulPsServiceExist         = NAS_MML_GetPsServiceExistFlg();

    /* 如果不是主动释放但存在业务，退出状态机 */
    if ((VOS_TRUE == ulCsServiceExist)
     || (VOS_TRUE == ulPsServiceExist))
    {
        /* 注册过程中注册失败需要搜网,等待RRC连接时如果发起CS/PS业务,退出需要等待业务结束后搜网 */
        if (VOS_TRUE == NAS_MMC_IsAdditionalTriggerPlmnSearch_BgPlmnSearch())
        {
            /* 发送状态机结果为失败,需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
        }
        else
        {
            /* W下P态时主动释放RRC连接超时,发送状态机结果为成功,不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_SUCC, VOS_FALSE, VOS_NULL_PTR);
        }

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }
    else
    {
        /* 发送主动释放请求到MM、GMM，重新启动等待连接释放定时器 */
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_TRUE);
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
        NAS_MMC_SndMmRelReq();
        NAS_MMC_SndGmmRelReq();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSuspendCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitWasSuspendCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 如果挂起失败，复位单板 */
    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* 打印异常 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitWasSuspendCnfReCampVPlmn: Suspend fail");

        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return VOS_TRUE;
    }

    /* 停止等待挂起回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    /* 设置当前接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 如果Abort类型为立即退,退出状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
       disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

    if (VOS_TRUE == NAS_MMC_IsVplmnValid())
    {
        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

        NAS_MMC_ReCampVPlmn_BgPlmnSearch();
        return VOS_TRUE;
    }

    /* 如果Abort类型为延迟退,退出状态机,不用搜网 */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }
    else
    {
        /* 无打断标记,向上层状态机发送FAIL,需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();
    return VOS_TRUE;

}


VOS_UINT32    NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnfReCampVPlmn: ENTERED");

    /* 挂起超时，复位单板 */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSuspendCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitGasSuspendCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* 如果挂起失败，复位单板 */
    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitGasSuspendCnfReCampVPlmn: Suspend fail");

        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    /* 停止等待挂起回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    /* 设置当前接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 如果Abort类型为立即退,退出状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
       disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

    if (VOS_TRUE == NAS_MMC_IsVplmnValid())
    {
        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

        NAS_MMC_ReCampVPlmn_BgPlmnSearch();
        return VOS_TRUE;
    }

    /* 如果Abort类型为延迟退,退出状态机,不用搜网 */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }
    else
    {
        /* 无打断标记,向上层状态机发送FAIL,需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();
    return VOS_TRUE;

}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    /* 如果Abort类型是立即退 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == pstAbortMsg->enAbortFsmType)
    {
        /* 停止等待搜网回复定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

        /* 向当前接入技术发送停止搜网请求 */
        NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

        /* 状态迁移到回VPlmn时等待停止搜网回复状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF_RECAMP_VPLMN);

        /* 启动等待停止搜网回复定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);
    }

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;

    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stSearchedPlmnListInfo;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 停止等待搜网回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 对NO RF进行处理 */
        NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    /* 如果搜网成功 */
    if (RRC_PLMN_SEARCH_RLT_SPEC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 状态迁移到回VPlmn时等待WAS系统消息状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND_RECAMP_VPLMN);

        /* 启动等待系统消息定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);

        return VOS_TRUE;
    }

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
        NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                        &pstSrchCnfMsg->PlmnIdList,
                                                        &stSearchedPlmnListInfo);

        NAS_MMC_ConvertRrcCoverTypeToNasFormat(pstSrchCnfMsg->enCoverageType, &(stSearchedPlmnListInfo.enCoverType));

        stSearchedPlmnListInfo.stSearchedType.ucHistorySearchedFlg  = VOS_TRUE;
        stSearchedPlmnListInfo.stSearchedType.ucPrefBandSearchedFlg = VOS_TRUE;
        stSearchedPlmnListInfo.stSearchedType.ucSpecSearchedFlg     = VOS_TRUE;
        stSearchedPlmnListInfo.stSearchedType.ucReserve             = 0;

        /* 向上层状态机发送BG搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, &stSearchedPlmnListInfo);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 无需判断原因值 */

    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn: ENTERED");

    /* 停止等待搜网回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        /* 对NO RF进行处理 */
        NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 向上层状态机发送BG搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitWasPlmnSearchCnf_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasPlmnSearchCnf_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn: ENTERED");

    /* 通知AS停止指定搜网,迁移状态,启动保护定时器 */
    NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF_RECAMP_VPLMN);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasPlmnSearchCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    /* 如果Abort类型是立即退 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == pstAbortMsg->enAbortFsmType)
    {
        /* 停止等待搜网回复定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

        /* 向当前接入技术发送停止搜网请求 */
        NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

        /* 状态迁移到回VPlmn时等待停止搜网回复状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF_RECAMP_VPLMN);

        /* 启动等待停止搜网回复定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);
    }

    return VOS_TRUE;
}



VOS_UINT32    NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitGasPlmnSearchCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stSearchedPlmnListInfo;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 停止等待搜网回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 对NO RF进行处理 */
        NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return VOS_TRUE;
    }

    /* 如果搜网成功 */
    if (RRC_PLMN_SEARCH_RLT_SPEC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 状态迁移到回VPlmn时等待GAS系统消息状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND_RECAMP_VPLMN);

        /* 启动等待系统消息定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

        return VOS_TRUE;
    }

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
        NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_GSM,
                                                        &pstSrchCnfMsg->PlmnIdList,
                                                        &stSearchedPlmnListInfo);

        NAS_MMC_ConvertRrcCoverTypeToNasFormat(pstSrchCnfMsg->enCoverageType, &(stSearchedPlmnListInfo.enCoverType));

        stSearchedPlmnListInfo.stSearchedType.ucHistorySearchedFlg  = VOS_TRUE;
        stSearchedPlmnListInfo.stSearchedType.ucPrefBandSearchedFlg = VOS_TRUE;
        stSearchedPlmnListInfo.stSearchedType.ucSpecSearchedFlg     = VOS_TRUE;
        stSearchedPlmnListInfo.stSearchedType.ucReserve             = 0;

        /* 向上层状态机发送BG搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, &stSearchedPlmnListInfo);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32    NAS_MMC_RcvTiWaitGasPlmnSearchCnf_BgPlmnSearch_WaitGasPlmnSearchCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasPlmnSearchCnf_BgPlmnSearch_WaitGasPlmnSearchCnfReCampVPlmn: ENTERED");

    /* 通知AS停止指定搜网,迁移状态,启动保护定时器 */
    NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF_RECAMP_VPLMN);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}



VOS_UINT32    NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 无需判断原因值 */

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn: ENTERED");

    /* 停止等待搜网回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 向上层状态机发送BG搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmPlmnSrchStopCnf_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待搜网回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 向上层状态机发送BG搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmPlmnSearchCnf_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 停止等待搜网回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 对NO RF进行处理 */
        NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 向上层状态机发送BG搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitWasStopCnfExpired_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStopCnfExpired_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn: ENTERED");

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 向上层状态机发送BG搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmPlmnSearchStopCnf_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待搜网回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 向上层状态机发送BG搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmPlmnSearchCnf_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* 停止等待搜网回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* 若搜网no rf失败，则退状态机 */
    if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* 对NO RF进行处理 */
        NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return VOS_TRUE;
    }

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 向上层状态机发送BG搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitGasStopCnfExpired_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStopCnfExpired_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn: ENTERED");

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 向上层状态机发送BG搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_ABORT_FSM_TYPE_UINT8                            enAbortType;
    NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM_UINT32                 enSearchRslt;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 获取BG PLMN SEARCH状态机上下文中的ABORT标志 */
    enAbortType = NAS_MMC_GetAbortType_BgPlmnSearch();

    /* 停止等待系统消息定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif

    /* 如果Abort类型为立即退 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == enAbortType)
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果Abort类型为延迟退 */
    if (NAS_MMC_ABORT_FSM_DELAY == enAbortType)
    {
        enSearchRslt = NAS_MMC_BG_PLMN_SEARCH_ABORTED;
    }
    else
    {
        enSearchRslt = NAS_MMC_BG_PLMN_SEARCH_SUCC;
    }

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
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

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /*转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
    NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    /* 发送状态机结果,不需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(enSearchRslt, VOS_FALSE, VOS_NULL_PTR);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvTiWaitWasSysInfoExpired_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSysInfoExpired_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn: ENTERED");

    /* 如果需要Abort */
    if (NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }
    else
    {
        /* 向上层状态机发送BG搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSysInfoReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}



VOS_UINT32    NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasSysInfoIndReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_ABORT_FSM_TYPE_UINT8                            enAbortType;
    NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM_UINT32                 enSearchRslt;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 获取BG PLMN SEARCH状态机上下文中的ABORT标志 */
    enAbortType = NAS_MMC_GetAbortType_BgPlmnSearch();

    /* 停止等待系统消息定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif

    /* 如果Abort类型为立即退 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == enAbortType)
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果Abort类型为延迟退 */
    if (NAS_MMC_ABORT_FSM_DELAY == enAbortType)
    {
        enSearchRslt = NAS_MMC_BG_PLMN_SEARCH_ABORTED;
    }
    else
    {
        enSearchRslt = NAS_MMC_BG_PLMN_SEARCH_SUCC;
    }


    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

     pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
     pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

     PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
     PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
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

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /*转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
    NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    /* 发送状态机结果,不需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(enSearchRslt, VOS_FALSE, VOS_NULL_PTR);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32    NAS_MMC_RcvTiWaitGasSysInfoExpired_BgPlmnSearch_WaitGasSysInfoIndReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasSysInfoExpired_BgPlmnSearch_WaitGasSysInfoIndReCampVPlmn: ENTERED");

    /* 如果需要Abort */
    if ( NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch() )
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }
    else
    {
        /* 向上层状态机发送BG搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}




VOS_VOID NAS_MMC_ProcPsRegRslt_BgPlmnSearch(
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRsltInd
)
{
    NAS_MML_LAI_STRU                                       *pstLai         = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
    NAS_MML_PROC_TYPE_ENUM_U32                              enProcType;

    /* 转换发送给L的proctype */
    enProcType = NAS_MML_PROC_BUTT;

    NAS_MMC_ConverGmmActionTypeToMml(pstPsRegRsltInd->enGmmActionType, &enProcType);


	NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enReqDomain, &stActionRslt.enReqDomain);

	NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enRsltDomain, &stActionRslt.enRstDomain);



#endif

    pstLai              = NAS_MML_GetCurrCampLai();

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));



    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstPsRegRsltInd->enActionResult)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* 保存注册结果消息 */
        NAS_MMC_SaveRegRsltCtx(GMM_MMC_PS_REG_RESULT_IND, pstPsRegRsltInd);

        /* 根据注册结果更新注册信息表 */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS, NAS_MML_REG_FAIL_CAUSE_NULL);
        NAS_MMC_ClearHplmnRejDomainInfo(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS);

        if (VOS_TRUE == NAS_MML_GetKeepCsForbInfoCfg())
        {
            /* 只删除Forb GPRS PLMN信息，CS相关FORB信息依然保留 */
            NAS_MML_DelForbGprsPlmn(&(pstLai->stPlmnId));
        }
        else
        {  
            /* 注册成功时，需要删除ForbPlmn,ForbLa,ForbGprs等信息 */
            NAS_MMC_DelForbInfo_GuRegRsltSucc(NAS_MMC_REG_DOMAIN_PS);
        }


        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());


        NAS_MMC_UpdatePsRegStatePsRegSucc();

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

#if   (FEATURE_ON == FEATURE_LTE)

        /* 假流程不通知给LMM */
        if ( VOS_TRUE == NAS_MML_IsRegFailCauseNotifyLmm(pstPsRegRsltInd->enRegFailCause) )
        {
            stActionRslt.enProcType     = enProcType;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
            stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
            stActionRslt.ulAttemptCount = 0;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif

        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, pstPsRegRsltInd->enRegFailCause);

    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcPsRegFail(GMM_MMC_PS_REG_RESULT_IND,
                                                   pstPsRegRsltInd);

        if ( VOS_TRUE == NAS_MML_IsNetworkRegFailCause(pstPsRegRsltInd->enRegFailCause) )
        {
            /* 根据注册结果更新注册信息表 */
            NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS, pstPsRegRsltInd->enRegFailCause);
        }
#if   (FEATURE_ON == FEATURE_LTE)

        /* 小于 NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE的拒绝原因是UE尝试发起注册的原因值，需要通知LMM */
        if ( VOS_TRUE == NAS_MML_IsRegFailCauseNotifyLmm(pstPsRegRsltInd->enRegFailCause) )
        {
            stActionRslt.enProcType     = enProcType;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
            stActionRslt.enCnCause      = pstPsRegRsltInd->enRegFailCause;
            stActionRslt.ulAttemptCount = pstPsRegRsltInd->ulRegCounter;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif
    }

    /* AdditionalAction有效，更新PS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));

        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);

        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}


VOS_VOID NAS_MMC_ProcCsRegRslt_BgPlmnSearch(
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRsltInd
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
#endif

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();



    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    if (MM_MMC_LU_RESULT_SUCCESS == pstCsRegRsltInd->enLuResult)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* 根据注册结果更新注册信息表 */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /* 更新DPLMN NPLMN列表 */
        if (VOS_TRUE == NAS_MMC_IsRoam())
        {
            NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
            NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);

            NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

            NAS_MMC_LogDplmnNplmnList();
        }

        /* 对Hplmn的Rej Lai信息的清除 */
        NAS_MMC_ClearHplmnRejDomainInfo(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS);

        /* 注册成功时，需要删除ForbPlmn,ForbLa,ForbGprs等信息 */
        NAS_MMC_DelForbInfo_GuRegRsltSucc(NAS_MMC_REG_DOMAIN_CS);

        NAS_MMC_UpdateCsRegStateCsRegSucc();

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_NORMAL_SERVICE);

#if   (FEATURE_ON == FEATURE_LTE)
        /* 非联合注册时并且为真流程才通知LMM此时LU的结果 */
        if ((VOS_TRUE  == NAS_MML_IsRegFailCauseNotifyLmm(pstCsRegRsltInd->enRegFailCause))
         && (VOS_FALSE == pstCsRegRsltInd->ucIsComBined))
        {
            stActionRslt.enProcType     = NAS_MML_PROC_LAU;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
            stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
            stActionRslt.ulAttemptCount = 0;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif

        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS, VOS_TRUE, pstCsRegRsltInd->enRegFailCause);

    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcCsRegFail(MM_MMC_CS_REG_RESULT_IND,
                                                   pstCsRegRsltInd);

        if ( VOS_TRUE == NAS_MML_IsNetworkRegFailCause(pstCsRegRsltInd->enRegFailCause) )
        {
            /* 根据注册结果更新注册信息表 */
            NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, pstCsRegRsltInd->enRegFailCause);

            /* 更新DPLMN NPLMN列表 */
            if (VOS_TRUE == NAS_MMC_IsRoam())
            {
                NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_NPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usNplmnListNum,pstDPlmnNPlmnCfgInfo->astNPlmnList);
                NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
                NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

                NAS_MMC_LogDplmnNplmnList();
            }
        }
#if   (FEATURE_ON == FEATURE_LTE)
        /* 小于 NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE的拒绝原因是UE尝试发起注册的原因值，需要通知LMM */
        /* 联合注册时不通知LMM此时LU的结果 */
        if ((VOS_TRUE  == NAS_MML_IsRegFailCauseNotifyLmm(pstCsRegRsltInd->enRegFailCause))
         && (VOS_FALSE == pstCsRegRsltInd->ucIsComBined))
        {
            stActionRslt.enProcType     = NAS_MML_PROC_LAU;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
            stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enCnCause      = pstCsRegRsltInd->enRegFailCause;
            stActionRslt.ulAttemptCount = pstCsRegRsltInd->ulLuAttemptCnt;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif
    }


    /* AdditionalAction有效，更新CS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}


VOS_VOID NAS_MMC_SndSpecSearchReq_BgPlmnSearch(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                         stDestPlmnList;
    VOS_UINT32                                              ulWaitWasPlmnSrchCnfTimerLen;

    ulWaitWasPlmnSrchCnfTimerLen = NAS_MMC_GetWaitWasPlmnSrchCnfTimerLen();

    /* 非用户指定搜网，从全局变量中获取FORBIDEN ROAMING LAS信息 */
    pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();
    stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
    PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                pstForbPlmnInfo->astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList) );
    NAS_MML_AddCustomizedForbLaToDestLaList(&(stForbRoamLaInfo.ucForbRoamLaNum),
                                                   stForbRoamLaInfo.astForbRomLaList);

    /* 状态更新为当前未驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    PS_MEM_SET(&stDestPlmnList, 0x0, sizeof(stDestPlmnList));

    stDestPlmnList.ulPlmnNum = 1;
    PS_MEM_CPY(&stDestPlmnList.astPlmnId[0], pstDestPlmn, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 根据不同的接入技术发送搜网请求 */
    switch (pstDestPlmn->enRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSpecPlmnSearchReq(&stDestPlmnList, &stForbRoamLaInfo);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF_RECAMP_VPLMN);


            /* 当前为关机类型的打断，为了快速响应关机，故启动等回复比较短的定时器 */
            if ( NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) ==
                                NAS_MMC_GetAbortEventType_BgPlmnSearch() )
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF,
                                   TI_NAS_MMC_FAST_RECAMP_VPLMN_WAIT_WAS_PLMN_SEARCH_CNF_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF,
                                   ulWaitWasPlmnSrchCnfTimerLen);
            }

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSpecPlmnSearchReq(&stDestPlmnList, &stForbRoamLaInfo);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF_RECAMP_VPLMN);


            /* 当前为关机类型的打断，为了快速响应关机，故启动等回复比较短的定时器 */
            if ( NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) ==
                                NAS_MMC_GetAbortEventType_BgPlmnSearch() )
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF,
                                   TI_NAS_MMC_FAST_RECAMP_VPLMN_WAIT_GAS_PLMN_SEARCH_CNF_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF,
                                   NAS_MMC_GetWaitGasPlmnSearchCnfTimerLen(VOS_FALSE));
            }

            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSpecPlmnSearchReq(&stDestPlmnList, VOS_FALSE, NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF_RECAMP_VPLMN);

            /* 当前存在关机类型的打断，为了快速响应关机，故启动等回复比较短的定时器 */
            if ( NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) ==
                                NAS_MMC_GetAbortEventType_BgPlmnSearch() )
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                                   TI_NAS_MMC_FAST_RECAMP_VPLMN_WAIT_LMM_PLMN_SEARCH_CNF_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                                   TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);
            }

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecSearchReq_BgPlmnSearch: Rat not support.");
            break;
    }


    return;
}


VOS_UINT32 NAS_MMC_IsVplmnValid(VOS_VOID)
{
	NAS_MML_PLMN_WITH_RAT_STRU                             *pstPreCampPlmn = VOS_NULL_PTR;
	NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                                               ucSimPsRegStatus;
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();
    ucSimPsRegStatus      = NAS_MML_GetSimPsRegStatus();
#endif

    pstPreCampPlmn        = NAS_MMC_GetPreCampPlmn_BgPlmnSearch();

     /* 如果VPLMN接入技术当前不支持,返回vplmn接入技术无效 */
    if (VOS_FALSE == NAS_MML_IsNetRatSupported(pstPreCampPlmn->enRat))
    {
        return VOS_FALSE;
    }

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* 禁止网络，在forbid plmn列表中 */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstPreCampPlmn->stPlmnId),
                                          pstForbidPlmnInfo->ucForbPlmnNum,
                                          pstForbidPlmnInfo->astForbPlmnIdList))
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE  == pstPreCampPlmn->enRat)
    {
        /* 当前LTE的能力状态为disable */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapabilityStatus)
          || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
        {
            if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
            {
                return VOS_FALSE;
            }
        }

        /* 在forbid plmn for gprs列表中 */
        if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstPreCampPlmn->stPlmnId),
                                          pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                          pstForbidPlmnInfo->astForbGprsPlmnList))
        {
            return VOS_FALSE;
        }

        /* PS域卡无效 */
        if (VOS_FALSE == ucSimPsRegStatus)
        {
            return VOS_FALSE;
        }
    }

#endif

    return VOS_TRUE;
}


VOS_VOID NAS_MMC_ReCampVPlmn_BgPlmnSearch()
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPreCampPlmn = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32              ulDisablteRoamFlg;

    NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8 enLteForbiddenStatus;

    enLteForbiddenStatus = NAS_MML_GetLteForbiddenStatusFlg();

    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();
#endif

    enNetRatType = NAS_MML_GetCurrNetRatType();

    pstPreCampPlmn = NAS_MMC_GetPreCampPlmn_BgPlmnSearch();

    /* 如果Vplmn是LTE网络,后续搜索高优先级的LTE网络时,在高优先级的LTE网络上Disable Lte,
       再回Vplmn时，需要先Enable Lte */
#if (FEATURE_ON == FEATURE_LTE)
    if ((NAS_MML_NET_RAT_TYPE_LTE == pstPreCampPlmn->enRat)
     && (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE != enLteForbiddenStatus))
    {
        /* Enable Lte */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* 更新disable LTE能力标记 */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&(pstPreCampPlmn->stPlmnId)))
    {
        NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_ReCampVPlmn_BgPlmnSearch:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                             pstPreCampPlmn->stPlmnId.ulMcc, pstPreCampPlmn->stPlmnId.ulMnc);

        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return;
    }
#endif
    /* 如果需要搜索的网络与当前接入技术相同,或者当前接入技术为Butt,对应的场景是
       接入层回复SUSPNED CNF后会将当前接入模式设置为Butt,表示可以向任何接入技术直接发起搜网 */
    if ((enNetRatType == pstPreCampPlmn->enRat)
     || (NAS_MML_NET_RAT_TYPE_BUTT == enNetRatType))
    {
        NAS_MML_SetCurrNetRatType(pstPreCampPlmn->enRat);

        /* 发送指定搜网,启保护定时器并迁移状态 */
        NAS_MMC_SndSpecSearchReq_BgPlmnSearch(pstPreCampPlmn);
    }
    else
    {
        /* 发送挂起请求,启保护定时器并迁移状态 */
        NAS_MMC_SndSuspendReqReCampVPlmn_BgPlmnSearch(enNetRatType);
    }

    return;
}



VOS_UINT32 NAS_MMC_IsAdditionalTriggerPlmnSearch_BgPlmnSearch()
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* 附加操作为驻留当前网络或继续等待注册结果时不需要搜网 */
    if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON   == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION   == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON  == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED    == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_BUTT             == enAdditionalAction))
    {
        return VOS_FALSE;
    }

    /* 其它情况需要搜网 */
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch()
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stHighPrioPlmnInfo;

    VOS_UINT32                                              ulIsVplmnNetRatValid;

    /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
       disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

    ulIsVplmnNetRatValid     = NAS_MMC_IsVplmnValid();


    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 如果vplmn由于syscfg设置或L disable变成无效，无需获取下一个高优先级网络，
       直接退出状态机搜网，重新驻留后再根据条件判断是否进行背景搜*/
    if (VOS_FALSE == ulIsVplmnNetRatValid)
    {
        return VOS_FALSE;
    }

    /* 如果获取高优先级网络失败回VPLMN */
    if (VOS_FALSE == NAS_MMC_GetNextSearchHighPrioPlmn(pstPlmnSelectionListInfo,
                                                       &stHighPrioPlmnInfo,
                                                       NAS_MMC_GetPreCampPlmn_BgPlmnSearch(),
                                                       NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch()))
    {
        NAS_MMC_ReCampVPlmn_BgPlmnSearch();
        return VOS_TRUE;
    }

    /* 网络状态为未搜索回VPLMN继续BG搜 */
    if (NAS_MMC_NET_STATUS_NO_SEARCHED == stHighPrioPlmnInfo.astPlmnRatInfo[0].enNetStatus)
    {
        NAS_MMC_ReCampVPlmn_BgPlmnSearch();
        return VOS_TRUE;
    }
    else
    {
        /* 保存需要搜索的网络到状态机上下文 */
        NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(&(stHighPrioPlmnInfo.stPlmnId),
                                                stHighPrioPlmnInfo.astPlmnRatInfo[0].enRatType);

        /* 进行快速指定搜网 */
        NAS_MMC_PerformFastSpecSearch_BgPlmnSearch(&(stHighPrioPlmnInfo.stPlmnId),
                                                   stHighPrioPlmnInfo.astPlmnRatInfo[0].enRatType);
    }

    return VOS_TRUE;
}


VOS_VOID NAS_MMC_PerformAbortRegFinished_BgPlmnSearch()
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    /* 获取当前驻留的网络信息 */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    /* 更新当前网络的搜索状态为已注册过，在此轮高优先级搜网中，不会再搜此网络 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                            NAS_MMC_GetHighPrioPlmnList());

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* 由于L和GU的注册结果处理均会调用此函数，故两个定时器都停一下 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* 如果不需要回VPLMN则直接退出状态机 */
    if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON        == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION        == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON       == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED         == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL          == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL == enAdditionalAction))
    {
        /* 保存当前驻留网络及其EPLMN到状态机上下文 */
        NAS_MMC_SetPreCampPlmn_BgPlmnSearch( NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetCurrNetRatType() );
        NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch( NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetEquPlmnList() );

        /* 发送状态机退出成功,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 如果信令连接存在 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
            {
                NAS_MMC_SndLmmRelReq();

                NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_TRUE);
            }

            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
        }
        else
#endif
        {
            /* 状态迁移到等待连接释放 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND);

            /* 启动等待连接释放定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);
        }

    }
    else
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return;
    }

    return;
}


VOS_VOID NAS_MMC_PerformAdditionalActionRegFinished_BgPlmnSearch()
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    /* 获取当前驻留的网络信息 */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    NAS_MMC_UpdateRegFinishedPlmnNetStatusInPlmnSelectionList(
                                            &stCurPlmn,
                                            NAS_MMC_GetHighPrioPlmnList());

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return;
    }

    /* 由于L和GU的注册结果处理均会调用此函数，故两个定时器都停一下 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* 附加操作为驻留当前网络 */
    if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enAdditionalAction))
    {
        /* 注册完成后,不需要发起搜网时,保存当前驻留网络和等效网络到状态机上下文 */
        NAS_MMC_SetPreCampPlmn_BgPlmnSearch(NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetCurrNetRatType());

        NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetEquPlmnList());

        /* 发送状态机退出成功,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_SUCC, VOS_FALSE, VOS_NULL_PTR);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 信令链接存在，且当前需要搜网，则迁移到等待连接释放的状态 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
            {
                NAS_MMC_SndLmmRelReq();

                NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_TRUE);
            }

            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
        }
        else
#endif
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);
        }

        return;
    }

    if ((NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL == enAdditionalAction))
    {
        /* 向上层状态机指示选网失败,需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return;

    }

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

    return;
}


VOS_VOID NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch()
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAdditionalAction;

    /* 调用优先级比较表格得出CS/PS的处理优先级，并转换为状态机下一步行为 */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);
        }
        else
#endif
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);
        }
        return;
    }

    /* 注册过程结束，停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* 附加操作为驻留当前网络 */
    if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enAdditionalAction))
    {
        /* 注册完成后,不需要发起搜网时,保存当前驻留网络和等效网络到状态机上下文 */
        NAS_MMC_SetPreCampPlmn_BgPlmnSearch(NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetCurrNetRatType());

        NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(NAS_MML_GetCurrCampPlmnId(), NAS_MML_GetEquPlmnList());

        /* 发送状态机退出成功,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_SUCC, VOS_FALSE, VOS_NULL_PTR);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    if ((NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL == enAdditionalAction))
    {
        /* 向上层状态机指示选网失败,需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return;

    }

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();


    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

    return;
}


VOS_VOID NAS_MMC_SndRslt_BgPlmnSearch(
    NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM_UINT32                 enRslt,
    VOS_UINT32                                              ulNeedPlmnSearchFlg,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                                              ulBgSearchFinishedFlg;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stSearchedPlmnListInfo;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stHighPrioPlmnInfo;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    NAS_MMC_BG_PLMN_SEARCH_SCENE_ENUM_UINT8                 enBgPlmnSearchScene;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    enLteCapStatus      = NAS_MML_GetLteCapabilityStatus();
#endif

    enBgPlmnSearchScene = NAS_MMC_BG_PLMN_SEARCH_SCENE_BUTT;

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 如果获取下一个高优先级网络失败表明BG搜索已完成 */
    if (VOS_FALSE == NAS_MMC_GetNextSearchHighPrioPlmn(pstPlmnSelectionListInfo,
                                                       &stHighPrioPlmnInfo,
                                                       NAS_MMC_GetPreCampPlmn_BgPlmnSearch(),
                                                       NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch()))
    {
        ulBgSearchFinishedFlg = VOS_TRUE;
    }
    else
    {
        ulBgSearchFinishedFlg = VOS_FALSE;
    }

    /* 将接入层搜索到的网络转换为内部搜网列表信息 */
    if (VOS_NULL_PTR == pstSearchedPlmnListInfo)
    {
        PS_MEM_SET(&stSearchedPlmnListInfo, 0, sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU));

        stSearchedPlmnListInfo.enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
    }
    else
    {
        PS_MEM_CPY(&stSearchedPlmnListInfo, pstSearchedPlmnListInfo, sizeof(stSearchedPlmnListInfo));
    }

    /* 如果需要搜网，则需要构造搜网场景，目前只有丢网和disable lte两种搜网场景 */
    if (VOS_TRUE == ulNeedPlmnSearchFlg)
    {
        /* BG搜之前Lte 没有disable，在背景搜状态机里发生disable lte，如注册被拒#7,搜网场景需为disable lte */
#if (FEATURE_ON == FEATURE_LTE)
        if ((VOS_FALSE == NAS_MMC_GetPreLteDisableFlg_BgPlmnSearch())
         && ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
          || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus)))
        {
            enBgPlmnSearchScene = NAS_MMC_BG_PLMN_SEARCH_SCENE_DISABLE_LTE;
        }
        else
#endif
        {
            enBgPlmnSearchScene = NAS_MMC_BG_PLMN_SEARCH_SCENE_AREA_LOST;
        }
    }

    /* 发送BG搜网结果 */
    NAS_MMC_SndBgPlmnSearchRslt(enRslt, ulNeedPlmnSearchFlg, enBgPlmnSearchScene,
                                ulBgSearchFinishedFlg, &stSearchedPlmnListInfo);

    return;
}


VOS_VOID NAS_MMC_SndBgPlmnSearchReq_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    stDestPlmn.stPlmnId = *pstPlmnId;
    stDestPlmn.enRat    = enRat;

    /* 根据不同的接入技术发送BG搜网请求 */
    switch (NAS_MML_GetCurrNetRatType())
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsBgPlmnSearchReq(WUEPS_PID_WRR, &stDestPlmn);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_BG_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_WAS_BG_PLMN_SEARCH_CNF_LEN);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsBgPlmnSearchReq(UEPS_PID_GAS, &stDestPlmn);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_BG_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_GAS_BG_PLMN_SEARCH_CNF_LEN);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmBgPlmnSearchReq(&stDestPlmn);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF_LEN);
            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndBgPlmnSearchReq_BgPlmnSearch: Rat not support.");
            break;
    }

    return;
}


VOS_VOID NAS_MMC_SndSuspendReq_BgPlmnSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 状态更新为当前未驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* 按接入技术发送挂起请求,启动保护定时器并迁移状态 */
    switch (enRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSuspendReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN);
            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendReq_BgPlmnSearch: Rat not support.");
            break;
    }

    return;
}



VOS_VOID NAS_MMC_SndSuspendReqReCampVPlmn_BgPlmnSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 状态更新为当前未驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* 按接入技术发送挂起请求,启动保护定时器并迁移状态 */
    switch (enRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF_RECAMP_VPLMN);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF_RECAMP_VPLMN);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSuspendReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF_RECAMP_VPLMN);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN);
            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendReqReCampVPlmn_BgPlmnSearch: Rat not support.");
            break;
    }

    return;
}


VOS_VOID NAS_MMC_SndAsSpecPlmnSearchReq_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                         stDestPlmnList;


    /* 非用户指定搜网，从全局变量中获取FORBIDEN ROAMING LAS信息 */
    pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();
    stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
    PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                pstForbPlmnInfo->astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList) );

    NAS_MML_AddCustomizedForbLaToDestLaList(&(stForbRoamLaInfo.ucForbRoamLaNum),
                                                   stForbRoamLaInfo.astForbRomLaList);

    PS_MEM_SET(&stDestPlmnList, 0x0, sizeof(stDestPlmnList));

    stDestPlmnList.ulPlmnNum            = 1;
    stDestPlmnList.astPlmnId[0].enRat   = enRat;
    PS_MEM_CPY(&stDestPlmnList.astPlmnId[0].stPlmnId, pstPlmnId, sizeof(NAS_MML_PLMN_ID_STRU));
    
    NAS_MMC_SndAsSpecPlmnSearchReq(&stDestPlmnList, &stForbRoamLaInfo);
}




VOS_VOID NAS_MMC_SndFastSpecSearchReq_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* 状态更新为当前未驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* 按接入技术发送快速指定搜网,启动保护定时器并迁移状态 */
    switch (enRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsFastPlmnSearchReq(WUEPS_PID_WRR, pstPlmnId);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_FAST_SEARCH_CNF);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_WAS_FAST_PLMN_SEARCH_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
            {
                NAS_MMC_SndAsSpecPlmnSearchReq_BgPlmnSearch(pstPlmnId, enRat);
            }
            else
            {
                NAS_MMC_SndAsFastPlmnSearchReq(UEPS_PID_GAS, pstPlmnId);
            }
            
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_FAST_SEARCH_CNF);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF, NAS_MMC_GetWaitGasPlmnSearchCnfTimerLen(VOS_FALSE));
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmFastPlmnSearchReq(pstPlmnId);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_FAST_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndFastSpecSearchReq_BgPlmnSearch: Rat not support.");
            break;
    }

    return;
}


VOS_VOID NAS_MMC_PerformFastSpecSearch_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;

    enNetRatType = NAS_MML_GetCurrNetRatType();

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_GetNeedEnableLteFlg_BgPlmnSearch())
    {
        NAS_MMC_SendEnableLTE_FastSpecSearch();
        NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch(VOS_FALSE);
    }
#endif

    /* 如果需要搜索的网络与当前接入技术相同,,或者当前接入技术为Butt,对应的场景是
       接入层回复SUSPNED CNF后会将当前接入模式设置为Butt,表示可以向任何接入技术直接发起搜网 */
    if ((enNetRatType == enRat)
     || (NAS_MML_NET_RAT_TYPE_BUTT == enNetRatType))
    {
        NAS_MML_SetCurrNetRatType(enRat);

        NAS_MMC_SndFastSpecSearchReq_BgPlmnSearch(pstPlmnId, enRat);
    }
    else
    {
        NAS_MMC_SndSuspendReq_BgPlmnSearch(enNetRatType);
    }

    return;
}


VOS_VOID NAS_MMC_LoadInterSysFsm_BgPlmnSearch(
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
)
{
    switch ( enSuspendCause )
    {
        /* 启动HANDOVER状态机 */
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            break;

        /* 启动 CCO状态机 */
        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            break;

        /* 启动 小区重选 状态机 */
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            break;

        /* 启动 系统出服务区搜网 状态机 */
        case MMC_SUSPEND_CAUSE_PLMNSEARCH:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_OOS);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_LoadInterSysFsm_BgPlmnSearch():Unexpected suspend cause.");
            break;
    }

    return;
}


VOS_VOID NAS_MMC_ProcBgPlmnSearchRlstFail_BgPlmnSearch(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stHighPrioPlmnInfo;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRatType;
    NAS_MML_CONN_STATUS_INFO_STRU                          *pstConnStatus = VOS_NULL_PTR;

    pstConnStatus = NAS_MML_GetConnStatus();

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 根据搜索列表更新网络状态 */

    NAS_MMC_UpdatePlmnListInPlmnSelectionList(pstSearchedPlmnListInfo,
                                              pstPlmnSelectionListInfo,
                                              VOS_FALSE,
                                              VOS_TRUE);

    /* 可维可测,将选网列表输出 */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);

    /* 如果获取高优先级网络失败退出状态机 */
    if (VOS_FALSE == NAS_MMC_GetNextSearchHighPrioPlmn(pstPlmnSelectionListInfo,
                                                       &stHighPrioPlmnInfo,
                                                       NAS_MMC_GetPreCampPlmn_BgPlmnSearch(),
                                                       NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch()))
    {
        /* 发送状态机结果为成功,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_SUCC, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* 保存需要搜索的网络到状态机上下文 */
    NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(&(stHighPrioPlmnInfo.stPlmnId),
                                            stHighPrioPlmnInfo.astPlmnRatInfo[0].enRatType);

    /* 网络状态为未搜索继续BG搜 */
    if (NAS_MMC_NET_STATUS_NO_SEARCHED == stHighPrioPlmnInfo.astPlmnRatInfo[0].enNetStatus)
    {
        /* 向接入层发送BG搜网,启动保护定时器,迁移状态 */
        NAS_MMC_SndBgPlmnSearchReq_BgPlmnSearch(&(stHighPrioPlmnInfo.stPlmnId),
                                                stHighPrioPlmnInfo.astPlmnRatInfo[0].enRatType);

        return;
    }

    /* 获取当前的网络类型 */
    enRatType = NAS_MML_GetCurrNetRatType();

    /* 如果RRC连接存在(WAS接入层在P态),先释放RRC连接,G和L不存在该场景*/
    if ((VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
     && (NAS_MML_NET_RAT_TYPE_WCDMA == enRatType))
    {
        NAS_MMC_SndRrMmRelReq(RRC_NAS_PS_DOMAIN);
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);
    }
    else
    {
        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

        NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                 NAS_MML_GetSimPsRegStatus());

        /* 进行快速指定搜网 */
        NAS_MMC_PerformFastSpecSearch_BgPlmnSearch(&(stHighPrioPlmnInfo.stPlmnId),
                                                   stHighPrioPlmnInfo.astPlmnRatInfo[0].enRatType);
    }
}



VOS_UINT32    NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];

    pstAreaLostInd = (RRMM_AREA_LOST_IND_STRU*)pstMsg;

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_BG_PLMN_SEARCH_CNF);

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

    /* 发送状态机结果为失败,需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitGasBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];

    pstAreaLostInd = (RRMM_AREA_LOST_IND_STRU*)pstMsg;

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_BG_PLMN_SEARCH_CNF);

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

    /* 发送状态机结果为失败,需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitWasBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];

    pstAreaLostInd = (RRMM_AREA_LOST_IND_STRU*)pstMsg;

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF);

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

    /* 发送状态机结果为失败,需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32    NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitGasBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];

    pstAreaLostInd = (RRMM_AREA_LOST_IND_STRU*)pstMsg;

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF);

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

    /* 发送状态机结果为失败,需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_BgPLmnSearch(ulEventType, pstMsg);
}


VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* GU下收到IMS VOICE是否可用目前暂不处理
       对于异系统过程中收到的IMS VOICE是否可用的场景由于可能是异系统导致的IMS VOICE
       不可用,此时用来决定disable L模不准确,暂不考虑该场景 */

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_BgPLmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_BgPLmnSearch(ulEventType, pstMsg);
}



VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_BgPLmnSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pastIntraPlmnSrchInfo = VOS_NULL_PTR;
    RRMM_LIMIT_SERVICE_CAMP_IND_STRU                       *pstRrmmLimitCampOnMsg;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stHighPrioPlmnInfo;
    VOS_UINT32                                              ulIndex;

    pstRrmmLimitCampOnMsg = (RRMM_LIMIT_SERVICE_CAMP_IND_STRU *)pstMsg;


    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();


    pastIntraPlmnSrchInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                             sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);
    /* 分配内存失败 */
    if (VOS_NULL_PTR == pastIntraPlmnSrchInfo)
    {
        return VOS_TRUE;
    }

    NAS_MMC_InitSearchedPlmnListInfo(pastIntraPlmnSrchInfo);

    /* 转换W下的网络格式 */
    NAS_MMC_UpdateSearchedPlmnListInfo(VOS_NULL_PTR, &(pstRrmmLimitCampOnMsg->stPlmnIdList), pastIntraPlmnSrchInfo);

    /* 删除列表中禁止的PLMN */
    NAS_MMC_DelForbPlmnFromAsSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* 手动搜网模式下删除非用户指定的PLMN */
    NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* 可维可测信息勾出 */
    NAS_MMC_LogAsPlmnList(pastIntraPlmnSrchInfo);

    /* 存在available PLMN时,退出当前状态机,发起搜网 */
    if (VOS_TRUE == NAS_MMC_IsExistAvailPlmnInSearchedPlmnList(pastIntraPlmnSrchInfo))
    {
        /* 根据搜索列表更新网络状态 */
        for (ulIndex = 0; ulIndex < NAS_MML_MAX_RAT_NUM; ulIndex++)
        {
            NAS_MMC_UpdatePlmnListInPlmnSelectionList(&(pastIntraPlmnSrchInfo[ulIndex]),
                                                        pstPlmnSelectionListInfo,
                                                        VOS_FALSE,
                                                        VOS_TRUE);
        }

        /* 可维可测,将选网列表输出 */
        NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);

        /* 信令链接存在，且当前需要搜网，则迁移到等待连接释放的状态 */
        if (VOS_TRUE == NAS_MMC_GetNextSearchHighPrioPlmn(pstPlmnSelectionListInfo,
                                                           &stHighPrioPlmnInfo,
                                                           NAS_MMC_GetPreCampPlmn_BgPlmnSearch(),
                                                           NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch()))
        {
            /* 保存需要搜索的网络到状态机上下文 */
            NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(&(stHighPrioPlmnInfo.stPlmnId),
                                                    stHighPrioPlmnInfo.astPlmnRatInfo[0].enRatType);

            /* 设置主动释放标志 */
            NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_TRUE);

            /* 根据前面的检查,当前应该存在连接 */
            NAS_MMC_SndMmRelReq();
            NAS_MMC_SndGmmRelReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);
        }

    }

    PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;

    /* 停止等BG搜网结果回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF);

    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    /* 通知AS停止BG搜网,迁移状态NAS_MMC_BG_PLMN_SELECTION_STA_WAIT_LMM_BG_PLMN_STOP_CNF，启动保护定时器 */
    NAS_MMC_SndLmmBgStopPlmnSearchReq();
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_STOP_CNF);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvLmmSysInfoInd_BgPlmnSearch_WaitLmmBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU         stOldCampInfo;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);

    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();
    }


    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /* 转发系统消息给GMM,供RABM使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitLmmBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_BG_PLMN_SEARCH_CNF_STRU                        *pstBgSearchCnf           = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn       = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stSearchedPlmnListInfo;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnRatValue          = VOS_NULL_PTR;
    VOS_UINT8                                               ucHighRatBgProc;

    ucHighRatBgProc = VOS_FALSE;

    pstBgSearchCnf = (LMM_MMC_BG_PLMN_SEARCH_CNF_STRU*)pstMsg;

    if (pstBgSearchCnf->ulPlmnNum > MMC_LMM_MAX_BG_SRCH_PLMN_NUM)
    {
        pstBgSearchCnf->ulPlmnNum = MMC_LMM_MAX_BG_SRCH_PLMN_NUM;
    }

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF);


    switch ( pstBgSearchCnf->enRlst)
    {
        case MMC_LMM_BG_SRCH_RLT_ABORT:

            /* 发送状态机结果为失败,不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);

            /* 退出当前状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            break;

        case MMC_LMM_BG_SRCH_RLT_SUCCESS :

            /* 更新BG搜索的网络状态为已搜索存在 */
            NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstCurHighPrioPlmn,
                                                    NAS_MMC_NET_STATUS_SEARCHED_EXIST,
                                                    pstPlmnSelectionListInfo);

            ucHighRatBgProc = NAS_MMC_IsHighPrioRatHplmnSearch_BgPlmnSearch();

            /* 当前BG搜和VPLMN的PLMN一样，但是RAT不同，不发起快速指定搜，退出状态机*/
            pstPlmnRatValue = NAS_MMC_GetPreCampPlmn_BgPlmnSearch();

            if ((VOS_TRUE  == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnRatValue->stPlmnId), &(pstCurHighPrioPlmn->stPlmnId)))
             && (VOS_FALSE == ucHighRatBgProc))
            {
                /* 发送状态机结果为成功,不需要搜网 */
                NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_SUCC, VOS_FALSE, VOS_NULL_PTR);

                /* 退出当前状态机 */
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;
            }

            {
                /* 向MM、GMM发送搜网指示 */
                NAS_MMC_SndGmmPlmnSchInit();
                NAS_MMC_SndMmPlmnSchInit();

                NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

                NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                         NAS_MML_GetSimPsRegStatus());

                /* 进行快速指定搜网 */
                NAS_MMC_PerformFastSpecSearch_BgPlmnSearch(&(pstCurHighPrioPlmn->stPlmnId),
                                                           pstCurHighPrioPlmn->enRat);
            }
            break;

        case MMC_LMM_BG_SRCH_RLT_FAIL:


            PS_MEM_SET(&stSearchedPlmnListInfo, 0x00, sizeof(stSearchedPlmnListInfo));

            NAS_MMC_ConvertLmmBgPlmnSearchRslt2SearchedPlmnListInfo(pstBgSearchCnf,
                                                    &stSearchedPlmnListInfo,
                                                     pstCurHighPrioPlmn->enRat);

            /* 处理BG搜网的失败结果 */
            NAS_MMC_ProcBgPlmnSearchRlstFail_BgPlmnSearch(&stSearchedPlmnListInfo);

            break;

        default:

            /* 打印异常 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitLmmBgPlmnSearchCnf: Unexpected Bg search result.");
            break;
    }
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitLmmBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchList = VOS_NULL_PTR;

    /* 获取高优先级搜网列表信息 */
    pstHighPrioPlmnSearchList = NAS_MMC_GetHighPrioPlmnList();

    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitLmmBgPlmnSearchCnf: ENTERED");

    if (VOS_TRUE == NAS_MMC_IsHighPrioRatHplmnSearch_BgPlmnSearch())
    {
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_RAT_HPLMN_SEARCH,
                                      VOS_NULL_PTR,
                                      pstHighPrioPlmnSearchList);
    }
    else
    {
        /* 重新初始化选网列表 */
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                      VOS_NULL_PTR,
                                      pstHighPrioPlmnSearchList);
    }


    /* 通知AS停止BG搜网,迁移状态NAS_MMC_BG_PLMN_SELECTION_STA_WAIT_LMM_BG_PLMN_STOP_CNF，启动保护定时器 */
    NAS_MMC_SndLmmBgStopPlmnSearchReq();
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_STOP_CNF);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmMmcAreaLostInd_BgPlmnSearch_WaitLmmBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_AREA_LOST_IND_STRU                             *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];

    pstAreaLostInd = (LMM_MMC_AREA_LOST_IND_STRU*)pstMsg;

    PS_MEM_SET(astPlmnListInfo, 0x00, sizeof(astPlmnListInfo));

     /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF);

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 上报无服务*/

    /* 通知TAF当前的服务状态*/

    /* 向TAF上报出服务区 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /* 发送状态机结果为失败,需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;

    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmSysInfoInd_BgPlmnSearch_WaitLmmBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU         stOldCampInfo;
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);


    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);


    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);


    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /* 转发系统消息给GMM,供RABM使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvBgPlmnStopCnf_BgPlmnSearch_WaitLmmBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat;

    pstPlmnWithRat = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();
    stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
    stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;
#endif
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF);

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        /* 如果当前plmn不允许搜索，退背景搜状态机，并进行搜网 */
        if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
        {
            NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvBgPlmnStopCnf_BgPlmnSearch_WaitLmmBgStopCnf:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                                 stPlmnId.ulMcc, stPlmnId.ulMnc);

            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
        }
        else
#endif
        {
            /* 发送状态机结果为失败,不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);
        }
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitLmmBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_BG_PLMN_SEARCH_CNF_STRU                        *pstBgSearchCnf           = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stSearchedPlmnListInfo;

    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn       = VOS_NULL_PTR;

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    pstBgSearchCnf = (LMM_MMC_BG_PLMN_SEARCH_CNF_STRU*)pstMsg;

    if (pstBgSearchCnf->ulPlmnNum > MMC_LMM_MAX_BG_SRCH_PLMN_NUM)
    {
        pstBgSearchCnf->ulPlmnNum = MMC_LMM_MAX_BG_SRCH_PLMN_NUM;
    }

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    if (MMC_LMM_BG_SRCH_RLT_FAIL == pstBgSearchCnf->enRlst)
    {
        NAS_MMC_ConvertLmmBgPlmnSearchRslt2SearchedPlmnListInfo(pstBgSearchCnf,
                                                               &stSearchedPlmnListInfo,
                                                               pstCurHighPrioPlmn->enRat);

        /* 根据搜索列表更新网络状态 */
        NAS_MMC_UpdatePlmnListInPlmnSelectionList(&stSearchedPlmnListInfo,
                                                  pstPlmnSelectionListInfo,
                                                  VOS_FALSE,
                                                  VOS_TRUE);
    }

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF);

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为失败,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitLmmBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitLmmBgStopCnf: ENTERED");

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为失败,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvLmmMmcAreaLostInd_BgPlmnSearch_WaitLmmBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_AREA_LOST_IND_STRU                             *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];

    pstAreaLostInd = (LMM_MMC_AREA_LOST_IND_STRU*)pstMsg;

    PS_MEM_SET(astPlmnListInfo, 0x00, sizeof(astPlmnListInfo));

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF);

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 上报无服务*/

    /* 通知TAF当前的服务状态*/

    /* 向TAF上报出服务区 */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /* 发送状态机结果为失败,需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmPlmnFastSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;

    /* 停止等快速指定搜网结果回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    /* 通知AS停止快速指定搜网,迁移状态,启动保护定时器 */
    NAS_MMC_SndLmmPlmnSrchStopReq();
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_FAST_PLMN_STOP_CNF);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmPlmnSrchCnf_BgPlmnSearch_WaitLmmPlmnFastSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstSrchCnfMsg            = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn       = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    pstSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU *)pstMsg;

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 停止等快速搜网结果回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC == pstSrchCnfMsg->enRlst)
    {
        /* 根据不同的搜网模式，迁移到不同的L2状态，启动保护定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);
    }
    else if (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->enRlst)
    {
        /* 对NO RF进行处理 */
        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MMC_GetPreCampPlmn_BgPlmnSearch()->enRat);
        }
        else
        {
            NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }

        return VOS_TRUE;
    }
    else
    {
        /* 更新当前搜索网络状态为已搜索不存在 */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstCurHighPrioPlmn,
                                                NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,
                                                pstPlmnSelectionListInfo);

        /* 搜索下一个高优先级网络 */
        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_BgPlmnSearch_WaitLmmPlmnFastSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn       = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_BgPlmnSearch_WaitLmmPlmnFastSearchCnf: ENTERED");

    /* 更新当前搜索网络状态为已搜索不存在 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstCurHighPrioPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,
                                            pstPlmnSelectionListInfo);

    /* 通知AS停止快速指定搜网,迁移状态,启动保护定时器 */
    NAS_MMC_SndLmmPlmnSrchStopReq();
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_FAST_PLMN_STOP_CNF);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmFastPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;

    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmPlmnSrchStopCnf_BgPlmnSearch_WaitLmmFastPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitLmmFastPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstSrchCnfMsg            = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurHighPrioPlmn       = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    pstSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU *)pstMsg;

    /* 获取当前正在尝试的高优先级网络的信息 */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 获取高优先级网络列表 */
    pstPlmnSelectionListInfo = NAS_MMC_GetHighPrioPlmnList();

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->enRlst)
    {
        /* 对NO RF进行处理 */
        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MMC_GetPreCampPlmn_BgPlmnSearch()->enRat);
        }
        else
        {
            NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }

        return VOS_TRUE;
    }

    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_FAIL == pstSrchCnfMsg->enRlst)
    {
        /* 更新当前搜索网络状态为已搜索不存在 */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstCurHighPrioPlmn,
                                                       NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,
                                                       pstPlmnSelectionListInfo);
    }


    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvTiWaitLmmStopCnfExpired_BgPlmnSearch_WaitLmmFastPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnfExpired_BgPlmnSearch_WaitLmmFastPlmnStopCnf: ENTERED");

    /* 如果当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果当前存在延迟打断标志，则回VPLMN */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmSuspendCnf_BgPlmnSearch_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_CNF_STRU           *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmn       = VOS_NULL_PTR;

    pstSuspendCnf = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    /* 停止定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF);

    if (MMC_LMM_FAIL == pstSuspendCnf->ulRst)
    {
        /* 异常打印 */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSuspendCnf_BgPlmnSearch_WaitLmmSuspendCnf: SUSPEND FAIL !");

        /* 不可恢复错误,调用底软接口RESET */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    /* 设置当前接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch( NAS_MMC_BG_PLMN_SEARCH_ABORTED,
                                      VOS_FALSE, VOS_NULL_PTR );

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 当前存在延迟打断标志，则回VPlmn */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }


    /* 获取当前正在尝试的高优先级网络的信息 */
    pstPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* 进行快速指定搜网 */
    NAS_MMC_PerformFastSpecSearch_BgPlmnSearch(&(pstPlmn->stPlmnId),
                                                 pstPlmn->enRat);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU         stOldCampInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 停止等待系统消息的定时器  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 如果当前需要退出状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY  == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch( NAS_MMC_BG_PLMN_SEARCH_ABORTED,
                                      VOS_FALSE, VOS_NULL_PTR );

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果Abort类型是延迟退出，进行回VPLMN操作 */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);


    /* 更新当前等待EPS的注册结果 */
    NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();
    NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

#if (FEATURE_ON == FEATURE_IMS)
    /* 增加等待IMS是否可用结果FLG,MSCC保证收到PS注册结果上报IMS是否可用指示到MMC */
    NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    /* 更新CS的AdditionalAction */
    NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch(VOS_TRUE);
        }
        else
        {
           /* 主动上报 */
           NAS_MMC_SndMsccSysInfo();
        }
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* 转发系统消息给GMM,供RABM使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    /* 迁移到等待注册结果子状态:NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}


/* 删除LTE上报服务状态和注册状态的接口   NAS_MMC_RcvLmmMmcRegStatusInd_BgPlmnSearch_WaitLSysInfoInd()处理函数 */



VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_BgPlmnSearch_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch( NAS_MMC_BG_PLMN_SEARCH_ABORTED,
                                      VOS_FALSE, VOS_NULL_PTR );

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 当前存在延迟打断标志，则回VPlmn */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 不存在打断标志，尝试搜下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat     = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
#endif

    pstLmmStatusIndMsg = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    if ( VOS_FALSE == pstLmmStatusIndMsg->bitOpConnState)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_BgPlmnSearch_WaitEpsRegRsltInd:bitOpConnState IS VOS_FALSE");
        return VOS_TRUE;
    }

    /* 更新LMM的链接状态 */
    NAS_MML_UpdateEpsConnectionStatus(pstLmmStatusIndMsg->ulConnState);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    pstPlmnWithRat      = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();
    stPlmnId.ulMcc      = pstPlmnWithRat->stPlmnId.ulMcc;
    stPlmnId.ulMnc      = pstPlmnWithRat->stPlmnId.ulMnc;

    /* 链接不存在，判断当前lte plmn是否允许搜 */
    if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
    {
        NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_BgPlmnSearch_WaitEpsRegRsltInd:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                             stPlmnId.ulMcc, stPlmnId.ulMnc);

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 向上层状态机发送高优先级搜索失败 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }
#endif

    return VOS_TRUE;
}


/* 删除LTE上报服务状态和注册状态的接口   NAS_MMC_RcvLmmMmcRegStatusInd_BgPlmnSearch_WaitEpsRegRsltInd()处理函数 */


VOS_UINT32 NAS_MMC_RcvLmmMmcAttachInd_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;

    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode;

    enUeOperationMode   =  NAS_MML_GetLteUeOperationMode();
    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* LMM在搜网未回复search cnf时收到用户detach ps请求后，后续不会做注册给mmc回复attach result
       为MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW，请求类型填的是MMC_LMM_ATT_TYPE_BUTT，
       MMC需要根据当前ue operation mode给请求类型重新赋值 */
    if ((MMC_LMM_ATT_TYPE_BUTT == pstLmmAttachIndMsg->ulReqType)
     && (MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW == pstLmmAttachIndMsg->ulAttachRslt))
    {
        pstLmmAttachIndMsg->ulReqType = NAS_MMC_ConvertLmmAttachReqType(enUeOperationMode);
    }

    /*注册成功需先报系统消息*/
    if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachIndMsg->ulAttachRslt)
    {
        NAS_MMC_SndMsccSysInfo_BgPlmnSearch();
    }
    else
    {
        /*注册非成功，需等收齐后再上报系统消息*/
        if (NAS_MMC_WAIT_REG_RESULT_IND_NULL == NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch())
        {
            NAS_MMC_SndMsccSysInfo_BgPlmnSearch();
        }
    }

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* 处理attach结果 */
    NAS_MMC_ProcLmmAttachInd_BgPlmnSearch(pstLmmAttachIndMsg);

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch())
    {
        return VOS_TRUE;
    }

    /* 如果需要Abort,此时的打断类型只可能为延迟打断 */
    if (NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 注册结果完成后收到ABORT的处理 */
        NAS_MMC_PerformAbortRegFinished_BgPlmnSearch();
    }
    else
    {
        /* 如果不需要Abort，根据CS和PS的dditional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionRegFinished_BgPlmnSearch();
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmMmcTauResultInd_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg = VOS_NULL_PTR;

    pstLmmTauIndMsg = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /*注册成功需先报系统消息*/
    if (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauIndMsg->ulTauRst)
    {
        NAS_MMC_SndMsccSysInfo_BgPlmnSearch();
    }
    else
    {
        /*注册非成功，需等收齐后再上报系统消息*/
        if (NAS_MMC_WAIT_REG_RESULT_IND_NULL == NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch())
        {
            NAS_MMC_SndMsccSysInfo_BgPlmnSearch();
        }
    }

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* 处理tau结果 */
    NAS_MMC_ProcLmmTauResultInd_BgPlmnSearch(pstLmmTauIndMsg);

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch())
    {
        return VOS_TRUE;
    }
    /* 如果需要Abort,此时的打断类型只可能为延迟打断 */
    if (NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 注册结果完成后收到ABORT的处理 */
        NAS_MMC_PerformAbortRegFinished_BgPlmnSearch();
    }
    else
    {
        /* 如果不需要Abort，根据CS和PS的dditional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionRegFinished_BgPlmnSearch();
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    /* 处理DETACH消息，返回下一步动作 */
    NAS_MMC_ProcLmmDetachInd(pstDetachMsg, &enCsAdditionalAction, &enPsAdditionalAction);

    /*更新EPS的下一步的动作类型*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(enPsAdditionalAction);
    }

    /*更新CS的下一步的动作类型*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(enCsAdditionalAction);
    }

    /* 如果需要Abort,此时的打断类型只可能为延迟打断 */
    if (NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 注册结果完成后收到ABORT的处理 */
        NAS_MMC_PerformAbortRegFinished_BgPlmnSearch();
    }
    else
    {
        /* 如果不需要Abort，根据CS和PS的dditional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionRegFinished_BgPlmnSearch();
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

        NAS_MMC_SndOmEquPlmn();
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmMmcServiceRsltInd_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU                        *pstSerRsltMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstSerRsltMsg     = (LMM_MMC_SERVICE_RESULT_IND_STRU*)pstMsg;

    /* 根据LMM的service result结果返回下一步处理动作 */
    enAdditionalAction = NAS_MMC_ProcLmmServiceRsltInd(pstSerRsltMsg);

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    /* 如果需要Abort,此时的打断类型只可能为延迟打断 */
    if (NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 注册结果完成后收到ABORT的处理 */
        NAS_MMC_PerformAbortRegFinished_BgPlmnSearch();
    }
    else
    {
        /* 如果不需要Abort，根据CS和PS的dditional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionRegFinished_BgPlmnSearch();
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg = VOS_NULL_PTR;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;

    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* L模下，挂起原因定义与GU下不同，转换一下挂起原因定义 */
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLSuspendMsg->ulSysChngType, &enSuspendCause);

    /* 如果为OOS或者参数不正确, 则不允许进行异系统变换 */
    if ((MMC_SUSPEND_CAUSE_PLMNSEARCH == enSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= enSuspendCause))
    {
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
    }
    else
    {
        /* 根据SUSPEND消息中的不同类型起相应的状态机 */
        NAS_MMC_LoadInterSysFsm_BgPlmnSearch(enSuspendCause);
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcMmcSuspendRslt_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRsltMsg = VOS_NULL_PTR;

    pstSuspendRsltMsg = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    /* 如果重选结果为失败,原因为出服务区,则当作注册过程中出服务区处理 */
    if ((NAS_MMC_SUSPEND_FAIL == pstSuspendRsltMsg->enRslt)
     && (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST == pstSuspendRsltMsg->enFailCause))
    {
        /* 停止等待注册结果定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
        {
            /* 向上层状态机发送背景搜索失败，不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);

            /* 退出当前状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }


        /* 如果当前有ABORT标志，则退出当前状态机 */
        if ( NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch() )
        {
            /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
               disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

            if (VOS_TRUE == NAS_MMC_IsVplmnValid())
            {
                /* 向MM、GMM发送搜网指示 */
                NAS_MMC_SndGmmPlmnSchInit();
                NAS_MMC_SndMmPlmnSchInit();

                NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

                NAS_MMC_ReCampVPlmn_BgPlmnSearch();
                return VOS_TRUE;
            }

            /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }

        /* 清空等待注册结果标志 */
        NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();

        /* 没有ABORT标志，搜索下一个高优先级网络 */
        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }

        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

        return VOS_TRUE;
    }

    /* 迁移到不同的接入技术时，需要迁移到不同的处理注册结果状态 */
    enRatType = NAS_MML_GetCurrNetRatType();
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
     || (NAS_MML_NET_RAT_TYPE_GSM   == enRatType))
    {
        /* 停止当前等待EPS注册结果的定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 更新当前等待CSPS的注册结果 */
        NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();
        NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_CS);
        NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* 更新CSPS的AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* 收到系统消息后迁移到等待CS+PS域的注册结果并启动定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    }

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* 重选到HRPD后,退出背景搜索状态机 */
    if ((NAS_MML_NET_RAT_TYPE_BUTT == enRatType)
     && (NAS_MMC_SUSPEND_SUCCESS == pstSuspendRsltMsg->enRslt))
    {
        /* 停止当前等待EPS注册结果的定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_INTER_SYS_HRPD, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
#endif

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SndMsccSysInfo_BgPlmnSearch();

    /* 如果存在信令连接 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 状态迁移到等待连接释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND);

        /* 启动等待连接释放定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    if (NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 如果需要Abort，进行回VPLMN操作 */
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
;

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }
    else
    {
        /* 清空等待注册结果标志 */
        NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();

        /* 否则获取下一个高优先级网络进行搜索 */
        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }

        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stCurPlmn;

    NAS_MMC_SndMsccSysInfo_BgPlmnSearch();


    /* 获取当前驻留的网络信息 */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    /* 更新当前网络的搜索状态为已注册过，在此轮高优先级搜网中，不会再搜此网络 */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                                    NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                    NAS_MMC_GetHighPrioPlmnList());

    /* 停止等待注册结果定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* 清除驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* 当前信号更新 */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());


    /* 如果当前存在NO RF，退状态机，发送失败消息后迁移到OOC状态 */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* 向上层状态机发送高优先级搜索失败，不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
    /* 更新服务状态 */

    /* 通知TAF当前的服务状态 */

    /* 如果当前有ABORT标志，则回VPLMN */
    if ( NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch() )
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 向上层状态机发送高优先级搜索被打断，不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 清空等待注册结果标志 */
    NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();

    /* 搜索下一个高优先级网络 */
    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;

    }

    /* 向MM、GMM发送搜网指示 */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();


    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo           = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU         stOldCampInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);

    /* 驻留小区变化时，上报系统消息 */


    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);


    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo,pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        if (VOS_FALSE == NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch())
        {
            NAS_MMC_SndMsccSysInfo();
        }
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* 转发系统消息给GMM,供RABM使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果VPLMN接入技术当前不支持，不需将VPLMN接入技术更新为SYSCFG设置的最高优先接入技术，
       等获取下一个网络时再判断vplmn接入技术是否有效，vplmn无效时需要退状态机结果为需要搜网，
       重新驻留后再进行背景搜，该函数现不做处理，留作后续扩展使用 */
    return VOS_TRUE;

}


VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU                         *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                                               ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* 如果在等待PS的注册结果则继续等待PS注册结果 */
    if (NAS_MMC_WAIT_REG_RESULT_IND_PS == (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_PS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS不可用时判断是否需要disable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }
    }

    NAS_MMC_SndMsccSysInfo_BgPlmnSearch();


    /* 如果需要Abort,此时的打断类型只可能为延迟打断 */
    if (NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 注册结果完成后收到ABORT的处理 */
        NAS_MMC_PerformAbortRegFinished_BgPlmnSearch();
    }
    else
    {
        /* 如果不需要Abort，根据CS和PS的dditional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionRegFinished_BgPlmnSearch();
    }

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU                *pstAbortMsg = VOS_NULL_PTR;
    NAS_MMC_WAIT_REG_RSLT_IND_ENUM_UINT8   enRegRslt;


    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    NAS_MMC_SndMsccSysInfo_BgPlmnSearch();



    /* 若打断类型是用户请求的关机，则直接退出等注册结果状态机 */
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* 发送状态机结果为ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch( NAS_MMC_BG_PLMN_SEARCH_ABORTED,
                                      VOS_FALSE, VOS_NULL_PTR );

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    /* 当前存在立即打断标志，则退状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == pstAbortMsg->enAbortFsmType)
    {
        /* 停止等待注册结果定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);


        /* 在注册过程中收到立即打断，意味着注册尚未完成，更新未完成的域的服务
           状态为LIMIT SERVICE，否则当前的服务状态可能为NORMAL_SERVICE,这样若被用户
           指定搜打断，且网络接入技术都相同的情况下，就不会进行搜网注册了 */
        enRegRslt = NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch();
        if ( enRegRslt>= NAS_MMC_WAIT_REG_RESULT_IND_BUTT )
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch:NAS_MMC_WAIT_REG_RESULT_IND_BUTT");
        }
        NAS_MMC_UpdateDomainServiceStatus(enRegRslt,
                                          NAS_MMC_LIMITED_SERVICE);


        if (VOS_TRUE == NAS_MML_IsRrcConnExist())
        {
            /* 设置主动释放标志 */
            NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_TRUE);

            /* 向LMM发送主动释放请求 */
            NAS_MMC_SndLmmRelReq();

            /* 状态迁移到等待连接释放 */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND);

            /* 启动等待连接释放定时器 */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
            return VOS_TRUE;
        }

        /* 发送状态机结果为ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch( NAS_MMC_BG_PLMN_SEARCH_ABORTED,
                                      VOS_FALSE, VOS_NULL_PTR );

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;

    pstLmmStatusIndMsg = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    if ( VOS_FALSE == pstLmmStatusIndMsg->bitOpConnState)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_BgPlmnSearch_WaitEpsConnRelInd:bitOpConnState IS VOS_FALSE");
        return VOS_TRUE;
    }

    /* 更新LMM的链接状态 */
    NAS_MML_UpdateEpsConnectionStatus(pstLmmStatusIndMsg->ulConnState);

    /* 如果仍然存在信令连接，继续等待 */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    /* 停止等待信令连接释放保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* 如果Abor类型为立即退出，则退出状态机 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果Abort类型是延迟退出，进行回VPLMN操作 */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
           disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

        if (VOS_TRUE == NAS_MMC_IsVplmnValid())
        {
            /* 向MM、GMM发送搜网指示 */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

            NAS_MMC_ReCampVPlmn_BgPlmnSearch();
            return VOS_TRUE;
        }

        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
;

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_BgPlmnSearch())
    {
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_FALSE);

        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }

        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    }
    else
    {
        /* 当前为被动释放，根据CS和PS的additional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitEpsConnRelIndExpired_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucRelRequestFlg;
    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortType;
    VOS_UINT32                          ulCsServiceExist;
    VOS_UINT32                          ulPsServiceExist;

    enAbortType     = NAS_MMC_GetAbortType_BgPlmnSearch();
    ucRelRequestFlg = NAS_MMC_GetRelRequestFlag_BgPlmnSearch();

    /* 打印异常 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitEpsConnRelIndExpired_BgPlmnSearch_WaitEpsConnRelInd: ENTERED");

    /* 如果Abort类型为立即退 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == enAbortType)
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 当前存在延迟打断标志，则回VPlmn */
    if (NAS_MMC_ABORT_FSM_DELAY == enAbortType)
    {
        if (VOS_TRUE == ucRelRequestFlg)
        {
            /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
               disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

            if (VOS_TRUE == NAS_MMC_IsVplmnValid())
            {
                /* 向MM、GMM发送搜网指示 */
                NAS_MMC_SndGmmPlmnSchInit();
                NAS_MMC_SndMmPlmnSchInit();

                NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

                NAS_MMC_ReCampVPlmn_BgPlmnSearch();
                return VOS_TRUE;
            }

            /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
;

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }
        else
        {
            /* 发送主动释放请求到LMM，重新启动等待连接释放定时器 */
            NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_TRUE);
            NAS_MMC_SndLmmRelReq();
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
        }

        return VOS_TRUE;
    }

    /* 如果是主动释放且不需要Abort，搜索下一个高优先级网络 */
    if (VOS_TRUE == ucRelRequestFlg)
    {
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_FALSE);

        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }

        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

        return VOS_TRUE;
    }

    ulCsServiceExist = NAS_MML_GetCsServiceExistFlg();
    ulPsServiceExist = NAS_MML_GetPsServiceExistFlg();

    /* 如果不是主动释放但存在业务，退出状态机 */
    if ((VOS_TRUE == ulCsServiceExist)
     || (VOS_TRUE == ulPsServiceExist))
    {
        /* 发送状态机结果为成功,需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_SUCC, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }
    else
    {
        /* 发送主动释放请求到LMM，重新启动等待连接释放定时器 */
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_TRUE);
        NAS_MMC_SndLmmRelReq();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU         stOldCampInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 如果是主动请求释放,由于需要立即进行搜网,系统消息不处理 */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_BgPlmnSearch())
    {
        return VOS_TRUE;
    }

    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);

    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        NAS_MMC_SndMsccSysInfo();

    }


    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /* 转发系统消息给GMM,供RABM使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg = VOS_NULL_PTR;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;
    VOS_UINT32                          ulRelRequestFlg;

    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    ulRelRequestFlg = NAS_MMC_GetRelRequestFlag_BgPlmnSearch();

    /* L模下，挂起原因定义与GU下不同，转换一下挂起原因定义 */
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLSuspendMsg->ulSysChngType, &enSuspendCause);

    /* 如果是主动释放或者已经接收到Abort消息,则不允许进行异系统重选 */
    if ((NAS_MMC_ABORT_BUTT != NAS_MMC_GetAbortType_BgPlmnSearch())
     || (VOS_TRUE == ulRelRequestFlg)
     || (MMC_SUSPEND_CAUSE_PLMNSEARCH == enSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= enSuspendCause))
    {
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
    }
    else
    {
        /* 根据SUSPEND消息中的不同类型起相应的状态机 */
        NAS_MMC_LoadInterSysFsm_BgPlmnSearch(enSuspendCause);
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcSuspendRslt_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRsltMsg = VOS_NULL_PTR;

    pstSuspendRsltMsg = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    /* 如果重选结果为失败,原因为出服务区,则当作连接已释放处理 */
    if ((NAS_MMC_SUSPEND_FAIL == pstSuspendRsltMsg->enRslt)
     && (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST == pstSuspendRsltMsg->enFailCause))
    {
        /* 停止当前等待eps连接释放定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
        {
            /* 向上层状态机发送背景搜索失败，不需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);

            /* 退出当前状态机 */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }

        /* 链接释放时收到SUSPEND CNF后肯定没有ABORT标志，搜索下一个高优先级网络 */
        if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
        {
            /* 向上层状态机发送高优先级搜索失败，需要搜网 */
            NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

            /* 退出状态机 */
            NAS_MMC_FSM_QuitFsmL2();
            return VOS_TRUE;
        }

        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

        return VOS_TRUE;
    }

    /* 迁移到不同的接入技术时，需要迁移到不同的处理注册结果状态 */
    enRatType = NAS_MML_GetCurrNetRatType();
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
     || (NAS_MML_NET_RAT_TYPE_GSM == enRatType))
    {
        /* 停止当前等待eps连接释放定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* 更新当前等待CSPS的注册结果 */
        NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch();

        /* 更新CSPS的AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* 收到系统消息后迁移到等待CS+PS域的注册结果并启动定时器 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* 重选到HRPD后,退出背景搜索状态机 */
    if ((NAS_MML_NET_RAT_TYPE_BUTT == enRatType)
        && (NAS_MMC_SUSPEND_SUCCESS == pstSuspendRsltMsg->enRslt))
    {
        /* 停止当前等待EPS连接释放的定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* 向上层状态机发送高优先级搜索失败，不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_INTER_SYS_HRPD, VOS_FALSE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
#endif

    /*  如果存在信令连接，则继续等待  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* 如果信令连接不存在可能发起搜网 */
    NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果VPLMN接入技术当前不支持，不需将VPLMN接入技术更新为SYSCFG设置的最高优先接入技术，
       等获取下一个网络时再判断vplmn接入技术是否有效，vplmn无效时需要退状态机结果为需要搜网，
       重新驻留后再进行背景搜，该函数现不做处理，留作后续扩展使用 */
    return VOS_TRUE;

}



VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    /* 处理DETACH消息，返回下一步动作 */
    NAS_MMC_ProcLmmDetachInd(pstDetachMsg, &enCsAdditionalAction, &enPsAdditionalAction);

    /*更新EPS的下一步的动作类型*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(enPsAdditionalAction);
    }

    /*更新CS的下一步的动作类型*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

        NAS_MMC_SndOmEquPlmn();
    }

    return VOS_TRUE;

}


VOS_UINT32 NAS_MMC_RcvLmmMmcDetachCnf_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_CNF_STRU            *pstDetachCnfMsg = VOS_NULL_PTR;

    pstDetachCnfMsg = (LMM_MMC_DETACH_CNF_STRU*)pstMsg;

    /* 不过detach结果不是鉴权被拒，不需要进状态机，预处理中就可以处理 */
    if ( MMC_LMM_DETACH_RSLT_AUTH_REJ != pstDetachCnfMsg->ulDetachRslt)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcDetachCnf_BgPlmnSearch_WaitEpsConnRelInd: Unexpected detach result!");

        return VOS_TRUE;
    }

    /*更新EPS的下一步的动作类型*/
    NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL);

    /*更新CS的下一步的动作类型*/
    NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucRelRequestFlg;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 若打断类型是用户请求的关机，则直接退出等链接释放结果状态机 */
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)

    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* 发送状态机结果为ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch( NAS_MMC_BG_PLMN_SEARCH_ABORTED,
                                      VOS_FALSE, VOS_NULL_PTR );

        /* 直接退出当前状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    ucRelRequestFlg = NAS_MMC_GetRelRequestFlag_BgPlmnSearch();

    /* 如果当前存在立即打断标志而且不是主动释放，则主动释放 */
    if ((NAS_MMC_ABORT_FSM_IMMEDIATELY == pstAbortMsg->enAbortFsmType)
     && (VOS_FALSE == ucRelRequestFlg))
    {
        /* 设置主动释放标志 */
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_TRUE);

        /* 向LMM发送主动释放请求 */
        NAS_MMC_SndLmmRelReq();
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmMmcTauResultInd_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg = VOS_NULL_PTR;

    pstLmmTauIndMsg = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* L高优先级网络注册过程中 ,用户设置syscfg需要搜网场景，MMC会主动释放连接，
      在等待连接释放状态，L可能会上注册结果，需要处理 */
    NAS_MMC_ProcLmmTauResultInd_BgPlmnSearch(pstLmmTauIndMsg);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmMmcAttachInd_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode;

    enUeOperationMode   =  NAS_MML_GetLteUeOperationMode();
    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* LMM在搜网未回复search cnf时收到用户detach ps请求后，后续不会做注册给mmc回复attach result
       为MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW，请求类型填的是MMC_LMM_ATT_TYPE_BUTT，
       MMC需要根据当前ue operation mode给请求类型重新赋值 */
    if ((MMC_LMM_ATT_TYPE_BUTT == pstLmmAttachIndMsg->ulReqType)
     && (MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW == pstLmmAttachIndMsg->ulAttachRslt))
    {
        pstLmmAttachIndMsg->ulReqType = NAS_MMC_ConvertLmmAttachReqType(enUeOperationMode);
    }

    /* 向GMM和MM转发注册结果消息 */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* L高优先级网络注册过程中 ,用户设置syscfg需要搜网场景，MMC会主动释放连接，
      在等待连接释放状态，L可能会上注册结果，需要处理 */
    NAS_MMC_ProcLmmAttachInd_BgPlmnSearch(pstLmmAttachIndMsg);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmPlmnSearchCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    /* 如果Abort类型是立即退 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == pstAbortMsg->enAbortFsmType)
    {
        /* 停止等待搜网回复定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

        /* 向当前接入技术发送停止搜网请求 */
        NAS_MMC_SndLmmPlmnSrchStopReq();

        /* 状态迁移到回VPlmn时等待停止搜网回复状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF_RECAMP_VPLMN);

        /* 启动等待停止搜网回复定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);
    }


    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmPlmnCnf_BgPlmnSearch_WaitLmmPlmnSearchCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stSearchedPlmnList;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU *)pstMsg;

    /* 停止等待搜网回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
       /* 对NO RF进行处理 */
        NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return VOS_TRUE;
    }

    /* 如果搜网成功 */
    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC == pstLmmSrchCnfMsg->enRlst)
    {
        /* 状态迁移到回VPlmn时等待L系统消息状态 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND_RECAMP_VPLMN);

        /* 启动等待系统消息定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

        return VOS_TRUE;
    }

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 将搜网消息中携带的网络信息转换为内部消息中网络信息 */
        NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo(&(pstLmmSrchCnfMsg->stPlmnIdList),
                                                         &stSearchedPlmnList);

        NAS_MMC_ConvertLmmCoverTypeToNasFormat(pstLmmSrchCnfMsg->enCoverageType, &(stSearchedPlmnList.enCoverType));

        stSearchedPlmnList.stSearchedType.ucHistorySearchedFlg  = VOS_TRUE;
        stSearchedPlmnList.stSearchedType.ucPrefBandSearchedFlg = VOS_TRUE;
        stSearchedPlmnList.stSearchedType.ucSpecSearchedFlg     = VOS_TRUE;
        stSearchedPlmnList.stSearchedType.ucReserve             = 0;

        /* 向上层状态机发送BG搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, &stSearchedPlmnList);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitLmmSrchCnf_BgPlmnSearch_WaitLmmPlmnSearchCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmSrchCnf_BgPlmnSearch_WaitLmmPlmnSearchCnfReCampVPlmn: Timer Expired");

    /* 向LMM发送停止搜网请求消息 */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /* 迁移到等待停止搜网回复状态,启动等待停止搜网回复状态定时器 */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF_RECAMP_VPLMN);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmSuspendCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmSuspendCnf_BgPlmnSearch_WaitLmmSuspendCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_CNF_STRU           *pstSuspendCnf = VOS_NULL_PTR;

    pstSuspendCnf = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    /* 停止等待挂起回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF);

    /* 如果挂起失败，复位单板 */
    if (MMC_LMM_FAIL == pstSuspendCnf->ulRst)
    {
        /* 异常打印 */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSuspendCnf_BgPlmnSearch_WaitLmmSuspendCnfReCampVPlmn: SUSPEND FAIL !");

        /* 不可恢复错误,调用底软接口RESET */

        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    /* 设置当前接入技术为BUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* 如果Abort类型为立即退 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 发送状态机结果为ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch( NAS_MMC_BG_PLMN_SEARCH_ABORTED,
                                      VOS_FALSE, VOS_NULL_PTR );

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* 回VPLMN时需要判断当前的VPLMN的接入技术时是否有效,因为有可能当前
       disable LTE或SYSCFG设置后VPLMN的接入技术变为无效 */

    if (VOS_TRUE == NAS_MMC_IsVplmnValid())
    {
        /* 向MM、GMM发送搜网指示 */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

        NAS_MMC_ReCampVPlmn_BgPlmnSearch();
        return VOS_TRUE;
    }

    /* 如果Abort类型为延迟退,退出状态机,不用搜网 */
    if (NAS_MMC_ABORT_FSM_DELAY == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 有打断标记,向上层状态机发送ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }
    else
    {
        /* 无打断标记,向上层状态机发送FAIL,需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();
    return VOS_TRUE;

}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU *)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 设置Abort类型 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmPlmnStopCnf_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 停止等待搜网回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmPlmnSearchCnf_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstSrchCnfMsg            = VOS_NULL_PTR;

    pstSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU *)pstMsg;

    /* 停止等待搜网回复定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

    /* 若搜网no rf,则退状态机 */
    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->enRlst)
    {
        /* 对NO RF进行处理 */
        NAS_MMC_ProcNoRf_BgPlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return VOS_TRUE;
    }

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitLmmStopCnf_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnf_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn: Timer Expired");

    if (NAS_MMC_ABORT_BUTT == NAS_MMC_GetAbortType_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);
    }
    else
    {
        /* 发送状态机结果为被中止,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_ABORTED, VOS_FALSE, VOS_NULL_PTR);
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitLSysInfoIndReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_ABORT_FSM_TYPE_UINT8                            enAbortType;
    NAS_MMC_HIGH_PRIO_PLMN_SEARCH_RSLT_ENUM_UINT32          enSearchRslt;
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 停止等待系统消息定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 获取HIGH_PRIO_PLMN_SEARCH状态机上下文中的ABORT标志 */
    enAbortType = NAS_MMC_GetAbortType_BgPlmnSearch();

    /* 如果Abort类型为立即退 */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == enAbortType)
    {
        /* 发送状态机结果为ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch( NAS_MMC_BG_PLMN_SEARCH_ABORTED,
                                      VOS_FALSE, VOS_NULL_PTR );

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 如果Abort类型为延迟退 */
    if (NAS_MMC_ABORT_FSM_DELAY == enAbortType)
    {
        /* 高优先级搜网状态机结果为中止 */
        enSearchRslt = NAS_MMC_BG_PLMN_SEARCH_ABORTED;
    }
    else
    {
        /* 高优先级搜网状态机结果为成功 */
        enSearchRslt = NAS_MMC_BG_PLMN_SEARCH_SUCC;
    }


    /* 保留老的驻留网络信息 */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);


    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();


    /*方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC*/
    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }


    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /* 转发系统消息给GMM,供RABM使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    /* 发送状态机结果,不需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(enSearchRslt, VOS_FALSE, VOS_NULL_PTR);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();


    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_BgPlmnSearch_WaitLSysInfoIndReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortType;

    /* 异常打印 */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLSysInfoExpired_BgPlmnSearch_WaitLSysInfoIndReCampVPlmn: Timer Expired");

    enAbortType = NAS_MMC_GetAbortType_BgPlmnSearch();

    /* 如果需要Abort */
    if ( NAS_MMC_ABORT_BUTT != enAbortType)
    {
        /* 发送状态机结果为ABORT,不需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch( NAS_MMC_BG_PLMN_SEARCH_ABORTED,
                                      VOS_FALSE, VOS_NULL_PTR );
    }
    else
    {
        /* 发送状态机结果为失败,需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch( NAS_MMC_BG_PLMN_SEARCH_FAIL,
                                      VOS_TRUE, VOS_NULL_PTR );
    }

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLSysInfoIndReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 记录状态机上下文中Abort事件类型 */
    NAS_MMC_SetAbortEventType_BgPlmnSearch(pstAbortMsg->ulEventType);

    /* 记录Abort标志 */
    NAS_MMC_SetAbortType_BgPlmnSearch(pstAbortMsg->enAbortFsmType);

    return VOS_TRUE;
}


VOS_VOID NAS_MMC_ProcLmmCombinedAttachInd_BgPlmnSearch(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause(pstLmmAttachIndMsg,&enPsRegRsltCause, &enCsRegRsltCause);

    switch (pstLmmAttachIndMsg->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_SUCCESS:
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc(pstLmmAttachIndMsg,
                       enCsRegRsltCause, &enCsAdditionalAction, &enPsAdditionalAction);

            break;

        case MMC_LMM_ATT_RSLT_FAILURE:
            if (VOS_FALSE == pstLmmAttachIndMsg->bitOpAtmpCnt)
            {
                enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
                enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;


                NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
            }
            else
            {
                /* EPS/CS 均注册失败 */
                NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND,
                                                    pstLmmAttachIndMsg,
                                                    &enPsAdditionalAction,
                                                    &enCsAdditionalAction);
            }
            break;

        case MMC_LMM_ATT_RSLT_ESM_FAILURE:
        case MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_T3402_RUNNING:
        case MMC_LMM_ATT_RSLT_TIMER_EXP:
        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_ATT_RSLT_AUTH_REJ:
        case MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW:
            /* EPS/CS 均注册失败 */
            NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND,
                                                pstLmmAttachIndMsg,
                                                &enPsAdditionalAction,
                                                &enCsAdditionalAction);
            break;

        case MMC_LMM_ATT_RSLT_CN_REJ:
            if ((VOS_TRUE == pstLmmAttachIndMsg->bitOpCnRslt)
             && (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == pstLmmAttachIndMsg->ulCnRslt))
            {
                /* 当ATTACH请求类型为联合，网侧相应的ATTACH结果类型为EPS ONLY，
                   且原因值不为协议24301 5.5.1.3.4.3章节所列或者没有携带原因值，
                   则LMM通过ATTACH结果中MMC_LMM_ATT_RSLT_CN_REJ通知MMC，
                   且携带相应的ATTACH请求类型、网侧响应的ATTCH结果类型、原因值，
                   并携带处理该原因后的attach attempt counter值 */
                NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc(pstLmmAttachIndMsg,enCsRegRsltCause,
                                  &enCsAdditionalAction, &enPsAdditionalAction);
            }
            else
            {
                /* EPS/CS 均注册失败 */
                NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND,
                                                    pstLmmAttachIndMsg,
                                                    &enPsAdditionalAction,
                                                    &enCsAdditionalAction);
            }
            break;

        default:
            /* 异常打印 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedAttachInd_BgPlmnSearch:Unexpected attach result!");
            enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch();
            enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch();
            break;

    }

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(enPsAdditionalAction);
    }

    /* AdditionalAction有效，更新CS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(enCsAdditionalAction);
    }


    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

        NAS_MMC_SndOmEquPlmn();

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}



VOS_VOID NAS_MMC_ProcLmmEpsOnlyAttachInd_BgPlmnSearch(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    VOS_UINT32                                              ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stLEplmnInfo;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    VOS_UINT8                                               ucSimCsRegStatus;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverLmmAttachRsltToMMLCause(pstLmmAttachIndMsg, &enRegRsltCause);

    if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachIndMsg->ulAttachRslt)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

        /* 根据注册结果更新注册信息表 */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /* 先处理EPLMN LIST，在处理注册状态的上报*/
        if ( VOS_TRUE == pstLmmAttachIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmAttachIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmAttachIndMsg->stEplmnList.astEplmnList;

            /* 将LMM的PLMN ID格式转换为GU的格式 */
            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));
            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnInfo.astEquPlmnAddr);

            NAS_MMC_WriteEplmnNvim();
        }

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

        /* EPS单域注册成功时，需要删除ForbPlmn,ForbGprs等信息 */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, NAS_MMC_IsEpsEmergencyAttachType(pstLmmAttachIndMsg->ulReqType));

        /* 如果CS允许注册而且CS卡有效则更改CS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }

        /*注意: 需要先更新EPLMN LIST，在处理注册状态的上报,因为NAS_MMC_UpdatePsRegStatePsRegSucc()函数中会根据EPLMN LIST上报注册状态 */

        NAS_MMC_UpdateGURegRlstRPlmnIdInNV();

        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                  NAS_MML_GetSimPsRegStatus());
    }
    else if ((MMC_LMM_ATT_RSLT_FAILURE == pstLmmAttachIndMsg->ulAttachRslt)
          && (VOS_FALSE == pstLmmAttachIndMsg->bitOpAtmpCnt))
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
    }
    else
    {
        enAdditionalAction= NAS_MMC_ProcEpsAttachRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);
    }

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

        NAS_MMC_SndOmEquPlmn();

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}



VOS_VOID NAS_MMC_ProcLmmAttachInd_BgPlmnSearch(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    switch (pstLmmAttachIndMsg->ulReqType)
    {
        case MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI:

            /* 处理lmm的联合attach结果 */
            NAS_MMC_ProcLmmCombinedAttachInd_BgPlmnSearch(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_ONLY:

            /* 处理lmm的非联合attach，EPS only注册的结果 */
            NAS_MMC_ProcLmmEpsOnlyAttachInd_BgPlmnSearch(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_EMERGENCY:

            /* 暂不支持未实现 */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_BgPlmnSearch:Unsupported attach req type!");
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_BgPlmnSearch:Unexpected attach req type!");
            break;

    }

    return;
}


VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_BgPlmnSearch(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    NAS_MMC_ConverLmmCombinedTauRsltToMMLCause(pstLmmTauIndMsg, &enPsRegRsltCause, &enCsRegRsltCause);

    NAS_MMC_ProcLmmCombinedTauResult(pstLmmTauIndMsg, enCsRegRsltCause,
                                        &enPsAdditionalAction, &enCsAdditionalAction);

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(enPsAdditionalAction);
    }

    /* AdditionalAction有效，更新CS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

        NAS_MMC_SndOmEquPlmn();

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}


VOS_VOID  NAS_MMC_ProcLmmEpsOnlyTauResultInd_BgPlmnSearch(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnAddr;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stSndEquPlmnInfo;
    VOS_UINT8                           ucSimCsRegStatus;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8          enCsRegAdditionalAction;
    
    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverTauResultToMMLCause(pstLmmTauIndMsg, &enRegRsltCause);

    if (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauIndMsg->ulTauRst)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* 保存注册结果消息 */
        NAS_MMC_SaveRegRsltCtx(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

        /* 根据注册结果更新注册信息表 */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /*注意: 需要先更新EPLMN LIST，在处理注册状态的上报,因为NAS_MMC_UpdatePsRegStatePsRegSucc()函数中会根据EPLMN LIST上报注册状态 */
        /* 更新EPLMN */
        if (VOS_TRUE == pstLmmTauIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmTauIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmTauIndMsg->stEplmnList.astEplmnList;

            /* 将LMM的PLMN ID格式转换为MMC的格式 */
            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnAddr.astEquPlmnAddr));

            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnAddr.astEquPlmnAddr);

            NAS_MMC_WriteEplmnNvim();
        }

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

        /* EPS单域注册成功时，需要删除ForbPlmn,ForbGprs等信息 */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, VOS_FALSE);

        /* 此处更新CS addition原因是联合TAU仅EPS成功时,LMM启动T3411再次尝试TAU过程中,
           用户Detach CS,LMM会直接报TAU成功,不再尝试联合TAU */
        NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON);

        /* 如果CS允许注册而且CS卡有效则更改CS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }

        /*注意: 需要先更新EPLMN LIST，在处理注册状态的上报,因为NAS_MMC_UpdatePsRegStatePsRegSucc()函数中会根据EPLMN LIST上报注册状态 */

        NAS_MMC_UpdateGURegRlstRPlmnIdInNV();

        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                  NAS_MML_GetSimPsRegStatus());
    }
    else if ((MMC_LMM_TAU_RSLT_FAILURE == pstLmmTauIndMsg->ulTauRst)
          && (VOS_FALSE == pstLmmTauIndMsg->bitOpAtmpCnt))
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;


        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
    }
    else if (MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC == pstLmmTauIndMsg->ulTauRst)
    {
        NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                          &enAdditionalAction, &enCsRegAdditionalAction);
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcEpsTauRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);
    }

    /* AdditionalAction有效，更新EPS的下一步的动作类型 */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

        NAS_MMC_SndOmEquPlmn();

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}


VOS_VOID  NAS_MMC_ProcLmmTauResultInd_BgPlmnSearch(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    switch (pstLmmTauIndMsg->ulReqType)
    {
        case MMC_LMM_COMBINED_TA_LA_UPDATING:
        case MMC_LMM_COMBINED_TA_LA_WITH_IMSI:
        case MMC_LMM_CS_PS_PERIODIC_UPDATING:

            /* 处理lmm的联合tau结果 */
            NAS_MMC_ProcLmmCombinedTauResultInd_BgPlmnSearch(pstLmmTauIndMsg);
            break;

        case MMC_LMM_TA_UPDATING:
        case MMC_LMM_PS_PERIODIC_UPDATING:

            /* 处理lmm的非联合tau，EPS only注册的结果 */
            NAS_MMC_ProcLmmEpsOnlyTauResultInd_BgPlmnSearch(pstLmmTauIndMsg);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmTauResultInd_BgPlmnSearch:Unexpected tau req type!");
            break;

    }

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 NAS_MMC_RcvMsccCLAssociatedInfoNtf_BgPlmnSearch_WaitLmmPlmnFastSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat;

    pstPlmnWithRat  = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();
    stPlmnId.ulMcc  = pstPlmnWithRat->stPlmnId.ulMcc;
    stPlmnId.ulMnc  = pstPlmnWithRat->stPlmnId.ulMnc;

    if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
    {
        NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvMsccCLAssociatedInfoNtf_BgPlmnSearch_WaitLmmPlmnFastSearchCnf:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                             stPlmnId.ulMcc, stPlmnId.ulMnc);

        /* 停止等 LMM PLMN SEARCH CNF的定时器 */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

        /* 向LTE发送停止快速指定搜网消息 */
        NAS_MMC_SndLmmPlmnSrchStopReq();

        /*迁移到等待停止搜网确认状态，启动保护定时器*/
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_FAST_PLMN_STOP_CNF);

        NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccCLAssociatedInfoNtf_BgPlmnSearch_WaitLmmBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat;

    pstPlmnWithRat = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();
    stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
    stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;

    if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
    {
        NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvMsccCLAssociatedInfoNtf_BgPlmnSearch_WaitLmmBgPlmnSearchCnf:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                             stPlmnId.ulMcc, stPlmnId.ulMnc);

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF);

        /* 向LTE发送停止背景搜网消息 */
        NAS_MMC_SndLmmBgStopPlmnSearchReq();

        /*迁移到等待停止搜网确认状态，启动保护定时器*/
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_STOP_CNF);

        NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF_LEN);
    }

    return  VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccCLAssociatedInfoNtf_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat;

    pstPlmnWithRat = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();
    stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
    stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;

    if (VOS_TRUE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
    {
        return VOS_TRUE;
    }

    NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvMsccCLAssociatedInfoNtf_BgPlmnSearch_WaitEpsRegRsltInd:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                         stPlmnId.ulMcc, stPlmnId.ulMnc);

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* 设置主动释放标志 */
        NAS_MMC_SetRelRequestFlag_BgPlmnSearch(VOS_TRUE);

        /* 向LMM发送主动释放请求 */
        NAS_MMC_SndLmmRelReq();

        /* 状态迁移到等待连接释放 */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND);

        /* 启动等待连接释放定时器 */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch())
    {
        /* 向上层状态机发送高优先级搜索失败，需要搜网 */
        NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, VOS_NULL_PTR);

        /* 退出状态机 */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return  VOS_TRUE;
}

#endif
#endif



VOS_UINT8  NAS_MMC_IsHighPrioRatHplmnSearch_BgPlmnSearch(VOS_VOID)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;

   /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg     = NAS_MMC_GetCurrFsmMsgAddr();

    if (TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_MMC_IsNeedEnableLTE_FastSpecSearch(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    VOS_UINT32                                              ulIsPlmnSupportDam;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrPlmn;
    VOS_UINT8                                               ucHighRatBgProc;

    ucHighRatBgProc = NAS_MMC_IsHighPrioRatHplmnSearch_BgPlmnSearch();

    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

    /* 如果是SIM卡，不需要Enable Lte */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_FALSE;
    }

    /* PS卡无效, 不需要重新 Enable L */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus() )
    {
        return VOS_FALSE;
    }

    /* PS卡不允许注册,不需要重新 Enable L */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_FALSE;
    }

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* nv已经设置不需要ENABLE LTE并且是高优先RAT背景搜时，不ENABLE LTE */
    if ( (NAS_MML_HIGH_PRIO_RAT_BG_SEARCH_PROC_LTE_NOT_ENABLE_LTE == NAS_MML_GetHighPrioRatBgEnableLteFlag())
      && (VOS_TRUE == ucHighRatBgProc))
    {
        return VOS_FALSE;
    }    

    /* 当前驻留VPLMN，enable LTE，否则不enable */
    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();
    if (VOS_TRUE ==  NAS_MML_ComparePlmnIdWithHplmn(pstCurrPlmn))
    {
        return VOS_FALSE;
    }

    /* 已经Disable L,需要重新 Enable L */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapabilityStatus))
    {
        /* 如果之前disable lte的网络是支持DAM的网络，且禁止接入技术网络列表特性9014 nv未开启，
           则无需enable lte,AT&T LTE-BTR-1-1840用例要求只禁止310410 lte网络，漫游lte网络可用，
           后该用例删除，如果后续有需要测试，可以DAM nv项进行测试 */
        ulIsPlmnSupportDam = NAS_MML_IsPlmnSupportDam(NAS_MMC_GetDisabledLtePlmnId());

        if ((VOS_FALSE == NAS_MML_GetAddDamPlmnInDisablePlmnWithRatListFlag())
          && (VOS_TRUE == ulIsPlmnSupportDam))
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID NAS_MMC_SendEnableLTE_FastSpecSearch(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

    if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
    {
        NAS_MMC_SndEnableLteNotify();
        NAS_MMC_ClearDisabledLtePlmnId();
        NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);

    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
    }

    /* 更新disable LTE能力标记 */
    NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);


    return;
}


#endif



VOS_VOID NAS_MMC_ProcNoRf_BgPlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat
)
{
    /* 记录NO RF */
    NAS_MML_SetCurrRatRfAvailFlg(enNasRat, VOS_FALSE);

    /* 向MSCC通知当前NO RF信息  */
    NAS_MMC_SndMsccRfAvailInd(VOS_FALSE);

    /* 向RRM发起注册 */
    NAS_MMC_RegisterRrmResourceNtf(enNasRat, RRM_PS_TASK_TYPE_NAS_SEARCH);

    /* 向上层状态机发送高优先级搜索失败，不需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_FALSE, VOS_NULL_PTR);

    /* 退出状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return;
}

/*lint -restore */


VOS_VOID  NAS_MMC_SndMsccSysInfo_BgPlmnSearch(VOS_VOID)
{
    /* 发送系统消息标志置上的时候通知MMA系统消息，并清除标志 */
    if (VOS_TRUE == NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch())
    {
        NAS_MMC_SndMsccSysInfo();

        NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch(VOS_FALSE);
    }

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
