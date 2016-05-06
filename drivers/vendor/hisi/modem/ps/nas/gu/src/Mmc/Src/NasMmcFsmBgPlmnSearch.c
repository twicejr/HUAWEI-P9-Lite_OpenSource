/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcFsmBgPlmnSearch.c
  版 本 号   : 初稿
  作    者   : s46746
  生成日期   : 2011年9月10日
  最近修改   :
  功能描述   : NAS BG搜网状态机内的动作处理
  函数列表   :
  修改历史   :
  1.日    期   : 2011年9月10日
    作    者   : s46746
    修改内容   : 创建文件

******************************************************************************/

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
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "MmcMmInterface.h"
#include "MmcGmmInterface.h"
#include "NasMmcComFunc.h"
#include "NasUtranCtrlInterface.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
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
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiHplmnTimerExpired_BgPlmnSearch_Init
 功能描述  : BG搜网状态机初始状态接收到HPLMN定时器超时消息的处理
 输入参数  : pstMsg        - HPLMN 定时器超时消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年5月8日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年06月02日
   作    者   : s00217060
   修改内容   : for CS/PS mode 1, 如果已经Disable L，PS卡有效且允许注册，Enable L
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiHighPrioRatHPlmnTimerExpired_BgPlmnSearch_Init
 功能描述  : BG搜网状态机初始状态接收到High_Prio_rat_HPLMN定时器超时消息的处理
 输入参数  : pstMsg        - HPLMN 定时器超时消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月19日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvTiHighPrioRatHPlmnTimerExpired_BgPlmnSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo           = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrCampPlmnId        = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stHighPrioPlmnInfo;
    /* Added by w00176964 for coverity清理, 2014-3-10, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
#endif
    /* Added by w00176964 for coverity清理, 2014-3-10, end */

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
    /* Modified by w00176964 for coverity清理, 2014-3-10, begin */
    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

    /* 保存当前L disable状态到状态机上下文 */
    if (NAS_MML_LTE_CAPABILITY_STATUS_BUTT != enLteCapabilityStatus)
    {
        NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch(enLteCapabilityStatus);
    }
    /* Modified by w00176964 for coverity清理, 2014-3-10, end */
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



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiPeriodHighPrioPlmnSearchExpired_BgPlmnSearch_Init
 功能描述  : BG搜网状态机初始状态接收到周期性高优先级搜网定时器超时消息的处理
 输入参数  : pstMsg        - 周期性尝试高优先级搜网定时器超时消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年5月8日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasBgPlmnSearchCnf
 功能描述  : 等待BG搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf
 功能描述  : 等待BG搜网回复状态收到RRMM_SYS_INFO_IND消息的处理
 输入参数  : pstMsg        - RRMM_SYS_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 3.日    期   : 2012年8月21日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 4.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 5.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核

 6.日    期   : 2014年1月18日
   作    者   : z00234330
   修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
                 此处判断并没有判断plmnid是否有效

  7.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)

    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

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
    /* 驻留小区变化或重新搜网时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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

    /* CBS上报 */
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /* 转发系统消息通知 给 MM/GMM */
    NAS_MMC_SndMmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf
 功能描述  : 等待BG搜网回复状态收到RRMM_REL_IND消息的处理
 输入参数  : pstMsg        - RRMM_REL_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年6月18日
   作    者   : l00171473
   修改内容   : DTS2012051104124, 如果不判原因值，流程不会有问题(但WAS后面还会上报RRMM_BG_PLMN_SEARCH_CNF)，
                因为接入层发送RRMM_REL_IND后，都会进行重新驻留，此时接入层是不会进行bg搜索，也不会缓存BG搜索的
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitWasBgPlmnSearchCnf
 功能描述  : 等待BG搜网回复状态收到RRMM_BG_PLMN_SEARCH_CNF消息的处理
 输入参数  : pstMsg        - RRMM_BG_PLMN_SEARCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月20日
   作    者   : h44270
   修改内容   : BG搜网状态机开始快速指定搜网时，认为当前无网络，通知APS挂起
 3.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年10月29日
   作    者   : t00212959
   修改内容   : DTS2012080305980，相同PLMN，不同RAT，不再发起快速指定搜
 5.日    期   : 2012年12月13日
   作    者   : L00171473
   修改内容   : DTS2012121802573, TQE清理
 6.日    期   : 2014年2月22日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search调整:不比较驻留PLMN与BG搜的PLMN同时BG搜成功enable LTE
*****************************************************************************/
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

                /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
                NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
                /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitWasBgPlmnSearchCnf
 功能描述  : 等待BG搜网回复状态收到TI_NAS_MMC_WAIT_BG_PLMN_SEARCH_CNF消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_BG_PLMN_SEARCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
 3.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search特性调整
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasBgPlmnSearchCnf
 功能描述  : 等待BG搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasBgPlmnSearchCnf
 功能描述  : 等待BG搜网回复状态收到GRRMM_SYS_INFO_IND消息的处理
 输入参数  : pstMsg        - GRRMM_SYS_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 3.日    期   : 2012年8月21日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 4.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 5.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 6.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 7.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasBgPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                           *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)

    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

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
    /* 驻留小区变化或重新搜网时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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
	/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /*转发系统消息通知 给 MM/GMM */
    NAS_MMC_SndMmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitGasBgPlmnSearchCnf
 功能描述  : 等待BG搜网回复状态收到RRMM_BG_PLMN_SEARCH_CNF消息的处理
 输入参数  : pstMsg        - RRMM_BG_PLMN_SEARCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月20日
   作    者   : h44270
   修改内容   : BG搜网状态机开始快速指定搜网时，认为当前无网络，通知APS挂起
 3.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年9月3日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseII:如果在BG搜时候发生了同系统重选到TD国家网络,则在TDD模式下，
                 需要退出BG状态机。
 5.日    期   : 2012年10月29日
   作    者   : t00212959
   修改内容   : DTS2012080305980，相同PLMN，不同RAT，不再发起快速指定搜
 6.日    期   : 2012年12月13日
   作    者   : L00171473
   修改内容   : DTS2012121802573, TQE清理
 7.日    期   : 2013年12月20日
   作    者   : w00167002
   修改内容   : DTS2013112917981:guNAS删除在TD模式下不能进行bg搜的限制
 8.日    期   : 2014年2月22日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search调整:不比较驻留PLMN与BG搜的PLMN同时BG搜成功enable LTE
*****************************************************************************/
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

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitGasBgPlmnSearchCnf
 功能描述  : 等待BG搜网回复状态收到TI_NAS_MMC_WAIT_BG_PLMN_SEARCH_CNF消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_BG_PLMN_SEARCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
 3.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search特性调整
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSuspendCnf
 功能描述  : 等待接入挂起回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitWasSuspendCnf
 功能描述  : 等待接入挂起回复状态收到RRMM_SUSPEND_CNF消息的处理
 输入参数  : pstMsg        - RRMM_SUSPEND_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年12月15日
   作    者   : w00167002
   修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                 以供MM层调用，进行软复位。
 3.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年4月30日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 5.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 6.日    期   : 2014年2月18日
   作    者  :  w00242748
   修改内容  :  DTS2014021803515:复位时明确是收到哪个接入技术的异常消息导致的。
 7.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : 增加复位场景
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnf
 功能描述  : 等待接入挂起回复状态收到TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSuspendCnf
 功能描述  : 等待接入挂起回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitGasSuspendCnf
 功能描述  : 等待接入挂起回复状态收到RRMM_SUSPEND_CNF消息的处理
 输入参数  : pstMsg        - RRMM_SUSPEND_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年12月15日
   作    者   : w00167002
   修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                 以供MM层调用，进行软复位。
 3.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 5.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 6.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasBgStopCnf
 功能描述  : 等待停止背景搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasBgStopCnf
 功能描述  : 等待停止背景搜网回复状态收到RRMM_SYS_INFO_IND消息的处理
 输入参数  : pstMsg        - RRMM_SYS_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 3.日    期   : 2012年8月21日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 4.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA

 5.日    期   : 2014年1月18日
   作    者   : z00234330
   修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
                 此处判断并没有判断plmnid是否有效
 6.日    期   : 2014年1月23日
   作    者   : z00161729
   修改内容   : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息

 7.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)

    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);


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
    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */

        NAS_MMC_SndMsccSysInfo();
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报 */
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /* 转发系统消息通知 给 MM/GMM */
    NAS_MMC_SndMmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasBgStopCnf
 功能描述  : 等待停止背景搜网回复状态收到RRMM_REL_IND消息的处理
 输入参数  : pstMsg        - RRMM_REL_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年6月18日
   作    者   : l00171473
   修改内容   : DTS2012051104124, 如果不判原因值，流程不会有问题，
                因为接入层发送RRMM_REL_IND后，bg搜索肯定已经停止，也不会有缓存BG搜索
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvBgPlmnStopCnf_BgPlmnSearch_WaitWasBgStopCnf
 功能描述  : 等待停止背景搜网回复状态收到RRMM_BG_PLMN_STOP_CNF消息的处理
 输入参数  : pstMsg        - RRMM_BG_PLMN_STOP_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitAsBgStopCnf
 功能描述  : 等待停止背景搜网回复状态收到RRMM_BG_PLMN_SEARCH_CNF消息的处理
 输入参数  : pstMsg        - RRMM_BG_PLMN_SEARCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月4日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年6月14日
   作    者   : t00212959
   修改内容   : GU都调用此函数，需要停两个定时器
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitWasBgStopCnf
 功能描述  : 等待停止背景搜网回复状态收到TI_NAS_MMC_WAIT_BG_STOP_CNF消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_BG_STOP_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasBgPlmnStopCnf
 功能描述  : 等待停止背景搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasBgStopCnf
 功能描述  : 等待停止背景搜网回复状态收到GRRMM_SYS_INFO_IND消息的处理
 输入参数  : pstMsg        - GRRMM_SYS_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 3.日    期   : 2012年8月21日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 4.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 5.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 6.日    期   : 2014年1月23日
   作    者   : z00161729
   修改内容   : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息
 7.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasBgStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                           *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)

    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

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
    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        NAS_MMC_SndMsccSysInfo();

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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
    NAS_MMC_SndMmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvBgPlmnStopCnf_BgPlmnSearch_WaitGasBgStopCnf
 功能描述  : 等待停止背景搜网回复状态收到RRMM_BG_PLMN_STOP_CNF消息的处理
 输入参数  : pstMsg        - RRMM_BG_PLMN_STOP_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitGasBgStopCnf
 功能描述  : 等待停止背景搜网回复状态收到TI_NAS_MMC_WAIT_BG_STOP_CNF消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_BG_STOP_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasFastPlmnStopCnf
 功能描述  : 等待停止快速指定搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasFastPlmnStopCnf
 功能描述  : 等待停止快速指定搜网回复状态收到 RRMM_REL_IND 消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2012年6月18日
   作    者   : l00171473
   修改内容   : DTS2012051104124, WAS:接收到RRMM_PLMN_SEARCH_STOP_REQ时，
                可能发送有异常原因的rel ind或者RRMM_PLMN_SEARCH_STOP_CNF.
                收到rel ind时认为停止快速搜网结束
 3.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 5.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 6.日    期   : 2014年6月12日
   作    者   : w00167002
   修改内容   : WAS异常且NO RF,直接进ooc进行处理
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchStopCnf_BgPlmnSearch_WaitWasFastPlmnStopCnf
 功能描述  : 等待停止快速指定搜网回复状态收到RRMM_PLMN_SEARCH_STOP_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasStopCnfExpired_BgPlmnSearch_WaitWasFastPlmnStopCnf
 功能描述  : 等待停止快速指定搜网回复状态收到TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasFastPlmnStopCnf
 功能描述  : 等待停止快速指定搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSearchStopCnf_BgPlmnSearch_WaitGasFastPlmnStopCnf
 功能描述  : 等待停止快速指定搜网回复状态收到RRMM_PLMN_SEARCH_STOP_CNF消息的处理
 输入参数  : pstMsg        - RRMM_PLMN_SEARCH_STOP_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 5.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitAsFastPlmnStopCnf
 功能描述  : 等待停止快速指定搜网回复状态收到RRMM_PLMN_SEARCH_STOP_CNF消息的处理
 输入参数  : pstMsg        - RRMM_PLMN_SEARCH_STOP_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月4日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年6月14日
   作    者   : t00212959
   修改内容   : GU都调用此函数，需要停两个定时器
 3.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 4.日    期   : 2014年6月25日
   作    者   : b00269685
   修改内容   : DSDS III项目
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasStopCnfExpired_BgPlmnSearch_WaitGasFastPlmnStopCnf
 功能描述  : 等待停止快速指定搜网回复状态收到TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasPlmnFastSearchCnf
 功能描述  : 等待快速指定搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitWasPlmnFastSearchCnf
 功能描述  : 等待快速指定搜网回复状态收到RRMM_PLMN_SEARCH_CNF消息的处理
 输入参数  : pstMsg        - RRMM_PLMN_SEARCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2013年4月9日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败迁移到ooc
 4.日    期   : 2014年6月27日
   作    者   : b00269685
   修改内容   : DSDS III修改
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnFastSearchCnf
 功能描述  : 等待快速指定搜网回复状态收到RRMM_REL_IND消息的处理
 输入参数  : pstMsg        - RRMM_REL_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年6月18日
   作    者   : l00171473
   修改内容   : DTS2012051104124, WAS:接收到RRMM_PLMN_SEARCH_REQ时，
                不会上报正常原因的rel ind，只有异常原因的rel ind.
                收到rel ind时认为快速指定搜结束
 3.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2014年6月17日
   作    者   : w00167002
   修改内容   : DSDS III项目
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_BgPlmnSearch_WaitWasPlmnFastSearchCnf
 功能描述  : 等待快速指定搜网回复状态收到TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasPlmnFastSearchCnf
 功能描述  : 等待快速指定搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitGasPlmnFastSearchCnf
 功能描述  : 等待快速指定搜网回复状态收到RRMM_PLMN_SEARCH_CNF消息的处理
 输入参数  : pstMsg        - RRMM_PLMN_SEARCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2013年4月9日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败迁移到ooc时
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_BgPlmnSearch_WaitGasPlmnFastSearchCnf
 功能描述  : 等待快速指定搜网回复状态收到TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSysInfoInd
 功能描述  : 等待系统消息状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasSysInfoInd
 功能描述  : 等待系统消息状态收到RRMM_SYS_INFO_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:正常服务状态，等注册状态后再发系统消息，否则立即发
                系统消息
 5.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 6.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 7.日    期   : 2012年8月14日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题,禁止LTE漫游
 8.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 9.日    期   : 2014年1月18日
   作    者   : z00234330
   修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
                 此处判断并没有判断plmnid是否有效
 10.日    期   : 2014年1月23日
   作    者   : z00161729
   修改内容   : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息
 11.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求

*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
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

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

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

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
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

    /* CBS上报 */
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasSysInfoExpired_BgPlmnSearch_WaitWasSysInfoInd
 功能描述  : 等待系统消息状态收到TI_NAS_MMC_WAIT_WAS_SYS_INFO消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_WAS_SYS_INFO消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSysInfo
 功能描述  : 等待系统消息状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasSysInfoInd
 功能描述  : 等待系统消息状态收到GRRMM_SYS_INFO_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:正常服务状态，等注册状态后再发系统消息，否则立即发
                系统消息
 5.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 6.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 7.日    期   : 2012年8月14日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题,禁止LTE漫游
 8.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 9.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 10.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容   : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息
 11.日    期   : 2014年5月4日
    作    者   : t00173447
    修改内容   : DTS2014042105390,软银定制需求

*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

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

    /* 停止保护定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* 更新驻留状态 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

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

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasSysInfoExpired_BgPlmnSearch_WaitGasSysInfoInd
 功能描述  : 等待系统消息状态收到TI_NAS_MMC_WAIT_GAS_SYS_INFO消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_GAS_SYS_INFO消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月3日
   作    者   : w00167002
   修改内容   : 在注册过程中收到立即打断，意味着注册尚未完成，更新未完成的域的服务
                 状态为LIMIT SERVICE，否则当前的服务状态可能为NORMAL_SERVICE,这样若被用户
                 指定搜打断，且网络接入技术都相同的情况下，就不会进行搜网注册了
 3.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:增加打断事件ID，状态机可以知道是什么事件
                打断自己的。
                修改原因:用户下发关机命令后，当前可能在等注册结果或者在等连接
                释放，可能需要比较久的时间才能处理关机命令，通过增加打断事件，
                如归当前在等注册结果或者等链接释放状态，若收到关机命令，则直接
                退出当前状态机，处理用户的关机命令。
 4.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 5.日    期   : 2012年12月11日
   作    者   : l00167671
   修改内容   : DTS2012121802573, TQE清理
 6.日    期   : 2015年1月7日
   作    者   : s00217060
   修改内容   : Service_State_Optimize_PhaseI修改
*****************************************************************************/
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
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
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
     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmPsRegResultInd_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到GMMMMC_PS_REG_RESULT_IND消息的处理
 输入参数  : pstMsg        - GMMMMC_PS_REG_RESULT_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 3.日    期   : 2014年11月28日
   作    者   : w00281933
   修改内容   : 服务状态优化Phase I
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCsRegResultInd_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到MMMMC_CS_REG_RESULT_IND消息的处理
 输入参数  : pstMsg        - MMMMC_CS_REG_RESULT_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 3.日    期   : 2014年11月28日
   作    者   : w00281933
   修改内容   : 服务状态优化Phase I
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmAbortInd_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待CS PS注册结果过程中收到MM Abort消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年7月12日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
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




/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmNetworkDetachInd_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到MMCGMM_NETWORK_DETACH_IND消息的处理
 输入参数  : pstMsg        - MMCGMM_NETWORK_DETACH_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月15日
   作    者   : w00176964
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
 3.日    期   : 2012年2月13日
   作    者   : w00167002
   修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
 4.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 5.日    期   : 2014年11月28日
   作    者   : w00281933
   修改内容   : 服务状态优化Phase I
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmServiceRequestResultInd_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到GMMMMC_SERVICE_REQUEST_RESULT_IND消息的处理
 输入参数  : pstMsg        - GMMMMC_SERVICE_REQUEST_RESULT_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月15日
   作    者   : w00176964
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
 3.日    期   : 2012年2月13日
   作    者   : w00167002
   修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
 4.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 5.日    期   : 2014年11月28日
   作    者   : w00281933
   修改内容   : 服务状态优化Phase I
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvCmServiceRejectInd_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到MMCMM_CM_SERVICE_REJECT_IND消息的处理
 输入参数  : pstMsg        - MMCMM_CM_SERVICE_REJECT_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月15日
   作    者   : w00176964
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
 3.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 4.日    期   : 2015年1月7日
   作    者   : s00217060
   修改内容   : Service_State_Optimize_PhaseI修改

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvWasSuspendInd_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到RRMM_SUSPEND_IND消息的处理
 输入参数  : pstMsg        - RRMM_SUSPEND_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGasSuspendInd_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到RRMM_SUSPEND_IND消息的处理
 输入参数  : pstMsg        - RRMM_SUSPEND_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcMmcSuspendRslt_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到MMCMMC_SUSPEND_RSLT_CNF消息的处理
 输入参数  : pstMsg        - MMCMMC_SUSPEND_RSLT_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 5.日    期   : 2013年2月7日
   作    者   : W00176964
   修改内容   : Volte_phase3项目调整:增加IMS不可用时disable L模的逻辑修改
 6.日    期   : 2013年4月9日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败迁移到ooc

*****************************************************************************/
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

                /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
                NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
                /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */
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

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
#if (FEATURE_ON == FEATURE_IMS)
        /* 增加等待IMS是否可用结果FLG,MMA保证收到PS注册结果上报IMS是否可用指示到MMC */
        NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */

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

 /*****************************************************************************
 函 数 名  : NAS_MMC_RcvAreaLostInd_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到RRMM_AREA_LOST_IND消息的处理
 输入参数  : pstMsg        - RRMM_AREA_LOST_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 5.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 6.日    期   : 2013年4月4日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败消息后迁移到ooc
 7.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
 8.日    期   : 2014年4月30日
   作    者   : s00261364
   修改内容   : ecall项目修改服务状态上报
 9.日    期   : 2014年6月17日
   作    者   : w00167002
   修改内容   : DSDS III项目
 10.日    期   : 2014年10月13日
    作    者   : w00167002
    修改内容   : DTS2014102005694:G下，CS注册成功后，PS还未注册成功时候，则
               发起电话业务，在电话业务建联时候丢网，MM没有释放信令，MMC没有发起ANY
               CELL搜网。
 11.日    期   : 2015年1月7日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI修改
*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvAreaLostInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    /* 停止等待注册结果定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for 预置频点搜网优化, 2015-9-9, end */

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

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, begin */

    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-30, end */
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

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到RRMM_SYS_INFO_IND消息的处理
 输入参数  : pstMsg        - RRMM_SYS_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月28日
   作    者   : w00167002
   修改内容   : DTS2011112406707:删除将当前的Additional Action进行初始化的代码.
                修改原因:在ROAMING BROKER时候，设置1次失败,注册失败1次后，
                MMC需要搜网，但是MMC可能要等两个域的结果(如在选网状态机)，
                当收到系统消息的时候，假流程会更改MMC的AdditionalAction的值,
                导致ROMING BROKER特性失效。
 3.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 4.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 5.日    期   : 2012年8月21日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 6.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA

 7.日    期   : 2014年1月18日
   作    者   : z00234330
   修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
               此处判断并没有判断plmnid是否有效
 8.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求

*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

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

    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 背景搜收到系统消息时，当前限制服务，已经给MMA发了系统消息，此处可以给MMA发。
           否则要等到收到注册结果后再给MMA发送系统消息 */
        if (VOS_FALSE == NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch())
        {
            /* 主动上报 */
           /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
            NAS_MMC_SndMsccSysInfo();
           /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

        }
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

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到GRRMM_SYS_INFO_IND消息的处理
 输入参数  : pstMsg        - GRRMM_SYS_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月28日
   作    者   : w00167002
   修改内容   : DTS2011112406707:删除将当前的Additional Action进行初始化的代码.
                修改原因:在ROAMING BROKER时候，设置1次失败,注册失败1次后，
                MMC需要搜网，但是MMC可能要等两个域的结果(如在选网状态机)，
                当收到系统消息的时候，假流程会更改MMC的AdditionalAction的值,
                导致ROMING BROKER特性失效。
 3.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 4.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 5.日    期   : 2012年8月21日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 6.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 7.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式

 8.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

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

    /* 驻留小区变化时，上报系统消息 */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* 背景搜收到系统消息时，当前限制服务，已经给MSCC发了系统消息，此处可以给MSCC发。
           否则要等到收到注册结果后再给MSCC发送系统消息 */
        if (VOS_FALSE == NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch())
        {
            /* 主动上报 */
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
            NAS_MMC_SndMsccSysInfo();
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
        }
    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MSCC模块当前接入受限信息 */
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

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到ID_MSCC_MMC_SYS_CFG_SET_REQ消息的处理
 输入参数  : pstMsg        - ID_MSCC_MMC_SYS_CFG_SET_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到MMCMMC_SYSCFG_RSLT_CNF消息的处理
 输入参数  : pstMsg        - MMCMMC_SYSCFG_RSLT_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月26日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 等待注册结果状态收到TI_NAS_MMC_WAIT_CSPS_REG_IND消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_CSPS_REG_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 5.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
  6.日    期   : 2015年1月7日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI修改
*****************************************************************************/
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

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:增加打断事件ID，状态机可以知道是什么事件
                打断自己的。
                修改原因:用户下发关机命令后，当前可能在等注册结果或者在等连接
                释放，可能需要比较久的时间才能处理关机命令，通过增加打断事件，
                如归当前在等注册结果或者等链接释放状态，若收到关机命令，则直接
                退出当前状态机，处理用户的关机命令。

*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucRelRequestFlg;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 若打断类型是用户请求的关机，则直接退出等链接释放结果状态机 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmSignalingStatusInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到MMCGMM_SIGNALING_STATUS_IND消息的处理
 输入参数  : pstMsg      - MMCGMM_SIGNALING_STATUS_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 5.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search特性调整:P态下BG搜成功后快速指定搜网时enable LTE
*****************************************************************************/
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

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */
    }
    else
    {
        /* 当前为被动释放，根据CS和PS的additional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmNetworkDetachInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到MMCGMM_NETWORK_DETACH_IND消息的处理
 输入参数  : pstMsg        - MMCGMM_NETWORK_DETACH_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年2月13日
   作    者   : w00167002
   修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmTbfRelInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到MMCGMM_TBF_REL_IND消息的处理
 输入参数  : pstMsg        - MMCGMM_TBF_REL_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */
    }
    else
    {
        /* 当前为被动释放，根据CS和PS的additional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmServiceRequestResultInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到GMMMMC_SERVICE_REQUEST_RESULT_IND消息的处理
 输入参数  : pstMsg        - GMMMMC_SERVICE_REQUEST_RESULT_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
 3.日    期   : 2012年2月13日
   作    者   : w00167002
   修改内容   : DTS2011122704039:additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmConnInfoInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到MMCMM_RR_CONN_INFO_IND消息的处理
 输入参数  : pstMsg        - MMCMM_RR_CONN_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */
    }
    else
    {
        /* 当前为被动释放，根据CS和PS的additional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmRrRelInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到MMCMM_RR_REL_IND消息的处理
 输入参数  : pstMsg        - MMCMM_RR_REL_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */
    }
    else
    {
        /* 当前为被动释放，根据CS和PS的additional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvCmServiceRejectInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到MMCMM_CM_SERVICE_REJECT_IND消息的处理
 输入参数  : pstMsg        - MMCMM_CM_SERVICE_REJECT_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGmmPsRegResultInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到GMMMMC_PS_REG_RESULT_IND消息的处理
 输入参数  : pstMsg        - GMMMMC_PS_REG_RESULT_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmCsRegResultInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到MMMMC_CS_REG_RESULT_IND消息的处理
 输入参数  : pstMsg        - MMMMC_CS_REG_RESULT_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmAbortInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待RRC连接释放过程中收到MM Abort消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年7月12日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
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



/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到RRMM_REL_IND消息的处理
 输入参数  : pstMsg        - RRMM_REL_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 5.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search特性调整

 6.日    期   : 2014年6月17日
   作    者   : w00167002
   修改内容   : DSDS III:异常且NO RF，则进入OOC进行处理
*****************************************************************************/
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

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */
    }
    else
    {
        /* 当前为被动释放，根据CS和PS的additional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到RRMM_SUSPEND_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSuspendRslt_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到MMCMMC_SUSPEND_RSLT_CNF消息的处理
 输入参数  : pstMsg        - MMCMMC_SUSPEND_RSLT_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月26日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2013年2月7日
   作    者   : W00176964
   修改内容   : Volte_phase3项目调整:增加IMS不可用时disable L模的逻辑修改
 4.日    期   : 2013年4月9日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败迁移到ooc

*****************************************************************************/
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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
#if (FEATURE_ON == FEATURE_IMS)
        /* 增加等待IMS是否可用结果FLG,MSCC保证收到PS注册结果上报IMS是否可用指示到MMC */
        NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到RRMM_SYS_INFO_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 3.日    期   : 2012年8月21日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题
 4.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA

 5.日    期   : 2014年1月18日
   作    者   : z00234330
   修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
                 此处判断并没有判断plmnid是否有效
 6.日    期   : 2014年1月23日
   作    者   : z00161729
   修改内容   : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息

 7.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

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

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

/* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-24, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif
/* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-24, end */

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MSCC模块当前接入受限信息 */
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

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /*转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
    NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到GRRMM_SYS_INFO_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 3.日    期   : 2012年8月21日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 4.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MMA
 5.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 6.日    期   : 2014年1月23日
   作    者   : z00161729
   修改内容   : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息

 7.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* 获取LTE能力状态 */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

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

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
     pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
     pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

     PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
     PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
     /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-24, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-24, end */

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccSysInfo();
	    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MSCC模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
       /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /*转发系统消息通知 给 MM/GMM,并将当前系统消息的 Forbidden 类型携带过去 */
    NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到ID_MSCC_MMC_SYS_CFG_SET_REQ消息的处理
 输入参数  : pstMsg        - ID_MSCC_MMC_SYS_CFG_SET_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到MMCMMC_SYSCFG_RSLT_CNF消息的处理
 输入参数  : pstMsg        - MMCMMC_SYSCFG_RSLT_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月26日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitRrcConnRelExpired_BgPlmnSearch_WaitRrcConnRelInd
 功能描述  : 等待连接释放状态收到TI_NAS_MMC_WAIT_RRC_CONN_REL消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_RRC_CONN_REL消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年12月3日
   作    者   : w00167002
   修改内容   : DTS2011120300667:在背景搜时，可能有紧急呼业务，同时注册结果
                需要导致搜网，在等链接释放超时时，需要启动AVAILABLE 定时器，
                等此定时器超时后，发起搜网。
 3.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 5.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 6.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search特性调整:BG搜成功快速指定搜时enable LTE
*****************************************************************************/
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

                /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
                NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
                /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSuspendCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitWasSuspendCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到RRMM_SUSPEND_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2011年12月15日
   作    者   : w00167002
   修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                 以供MM层调用，进行软复位。
 3.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 5.日    期   : 2012年6月14日
   作    者   : t00212959
   修改内容   : V7R1C50 GUL BG搜网修改,回VPLMN失败，区分是否打断
 6.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 7.日    期   : 2014年2月18日
   作    者  :  w00242748
   修改内容  :  DTS2014021803515:复位时明确是收到哪个接入技术的异常消息导致的。
 8.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF
             TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSuspendCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitGasSuspendCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到RRMM_SUSPEND_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2011年12月15日
   作    者   : w00167002
   修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                 以供MM层调用，进行软复位。
 3.日    期   : 2012年4月30日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 5.日    期   : 2012年6月14日
   作    者   : t00212959
   修改内容   : V7R1C50 GUL BG搜网修改,回VPLMN失败，区分是否打断
 6.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 7.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到RRMM_PLMN_SEARCH_CNF消息的处理
 输入参数  : pstMsg        - RRMM_PLMN_SEARCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
 3.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:更新网络覆盖类型
 4.日    期   : 2014年6月24日
   作    者   : w00167002
   修改内容   : DSDS III：搜网NO RF则进入OOC状态
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到RRMM_REL_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2012年6月18日
   作    者   : l00171473
   修改内容   : DTS2012051104124, WAS:接收到RRMM_PLMN_SEARCH_REQ时，
                不会上报正常原因的rel ind，只有异常原因的rel ind
 3.日    期   : 2014年6月12日
   作    者   : w00167002
   修改内容   : WAS异常且NO RF,直接进OOC处理
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasPlmnSearchCnf_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasPlmnSearchCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitGasPlmnSearchCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到RRMM_PLMN_SEARCH_CNF消息的处理
 输入参数  : pstMsg        - RRMM_PLMN_SEARCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月26日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
 3.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:更新网络覆盖类型

 4.日    期   : 2014年6月24日
   作    者   : w00167002
   修改内容   : DSDS III:搜网NO RF后进入OOC
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasPlmnSearchCnf_BgPlmnSearch_WaitGasPlmnSearchCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF消息的处理
 输入参数  : pstMsg        - TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到RRMM_REL_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2012年6月18日
   作    者   : l00171473
   修改内容   : DTS2012051104124, WAS:接收到RRMM_PLMN_SEARCH_STOP_REQ时，
                可能发送有异常原因的rel ind或者RRMM_PLMN_SEARCH_STOP_CNF，
                收到rel ind时认为停止搜网结束
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSrchStopCnf_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到RRMM_PLMN_SEARCH_STOP_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSearchCnf_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn
 功能描述  : 回VPLMN等待停止指定搜网回复状态收到RRMM_PLMN_SEARCH_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月25日
   作    者   : b00269685
   修改内容   : DSDS III新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasStopCnfExpired_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSearchStopCnf_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到RRMM_PLMN_SEARCH_STOP_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmPlmnSearchCnf_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到RRMM_PLMN_SEARCH_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年6月28日
   作    者   : b00269685
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasStopCnfExpired_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn
 功能描述  : 回VPLMN等待指定搜网回复状态收到TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn
 功能描述  : 回VPLMN等待系统消息状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn
 功能描述  : 回VPLMN等待系统消息状态收到RRMM_SYS_INFO_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2012年6月16日
   作    者   : l00171473
   修改内容   : DTS2012061409086, 收到W或G的系统消息时通知L模
 3.日    期   : 2012年8月14日
   作    者   : t00212959
   修改内容   : DCM定制需求和遗留问题，禁止LTE漫游
 4.日    期   : 2012年12月11日
   作    者   : w00176964
   修改内容   : 收到系统消息接入禁止信息变化则通知MSCC
 5.日    期   : 2014年1月18日
   作    者   : z00234330
   修改内容   : dts2014011801513,接入层上报的系统消息里面有可能没有携带plmnid,
               此处判断并没有判断plmnid是否有效
 6.日    期   : 2014年1月23日
   作    者   : z00161729
   修改内容   : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息

 7.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_ABORT_FSM_TYPE_UINT8                            enAbortType;
    NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM_UINT32                 enSearchRslt;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
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

    /* 获取BG PLMN SEARCH状态机上下文中的ABORT标志 */
    enAbortType = NAS_MMC_GetAbortType_BgPlmnSearch();

    /* 停止等待系统消息定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

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

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
       /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccSysInfo();
       /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MSCC模块当前接入受限信息 */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitWasSysInfoExpired_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn
 功能描述  : 回VPLMN等待系统消息状态收到TI_NAS_MMC_WAIT_WAS_SYS_INFO消息
             的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSysInfoReCampVPlmn
 功能描述  : 回VPLMN等待系统消息状态收到MMCMMC_ABORT_FSM_REQ消息
             的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasSysInfoIndReCampVPlmn
 功能描述  : 回VPLMN等待系统消息状态收到GRRMM_SYS_INFO_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
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
 5.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 6.日    期   : 2014年1月23日
   作    者   : z00161729
   修改内容   : DTS2014012305088:svlte特性tds或l上系统消息后pstransfer:1，注册随机接入失败，ps迁移
                到modem1后tds或l再次驻留mmc收到系统消息判断驻留信息未改变不会给mma发送系统消息导致
                mtc无法上报pstransfer:1,需要在搜网状态机退出后给mma再发次系统消息
 7.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求

*****************************************************************************/
VOS_UINT32    NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasSysInfoIndReCampVPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_ABORT_FSM_TYPE_UINT8                            enAbortType;
    NAS_MMC_BG_PLMN_SEARCH_RSLT_ENUM_UINT32                 enSearchRslt;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
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

    /* 获取BG PLMN SEARCH状态机上下文中的ABORT标志 */
    enAbortType = NAS_MMC_GetAbortType_BgPlmnSearch();

    /* 停止等待系统消息定时器 */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* 状态更新为当前已经驻留 */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* 如果收到GAS的系统消息，且目前Utran被Enable，则重新Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-15, end */

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

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, begin */
     pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
     pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

     PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
     PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
     /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-12, end */

    /* 根据系统消息，更新MML的全部变量 */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* 驻留小区变化或重新搜网时，上报系统消息 */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* 主动上报 */
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    }

    /* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    /* 驻留小区的接入受限信息变化时,通知MSCC模块当前接入受限信息 */
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

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitGasSysInfoExpired_BgPlmnSearch_WaitGasSysInfoIndReCampVPlmn
 功能描述  : 回VPLMN等待系统消息状态收到TI_NAS_MMC_WAIT_GAS_SYS_INFO消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月19日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
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



/*****************************************************************************
 函 数 名  : NAS_MMC_ProcPsRegRslt_BgPlmnSearch
 功能描述  : 对Ps注册结果的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月20日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月28日
   作    者   : w00167002
   修改内容   : DTS2011112406707:若当前为假流程且当前的AdditionalAction不为
                初始无效值，则不更新当前的AdditionalAction的值，否则若当前为
                真流程或当前为假流程且AdditionalAction为初始无效值，则更新
                当前的AdditionalAction的值.
                修改原因:在ROAMING BROKER时候，设置1次失败,注册失败1次后，
                MMC需要搜网，但是MMC可能要等两个域的结果(如在选网状态机)，
                当收到系统消息的时候，假流程会更改MMC的AdditionalAction的值,
                导致ROMING BROKER特性失效。
 3.日    期   : 2011年12月5日
   作    者   : z00161729
   修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
 4.日    期   : 2011年12月15日
   作    者   : w00176964
   修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
 5.日    期   : 2012年1月3日
   作    者   : w00167002
   修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网
                统一调整注册ADDITIONAL ACTION的值，若是用户自定义的原因值(>=256)，则
                不保存注册结果。
                若当前支持L模，则注册原因值小于260时通知LMM当前的注册结果.
 6.日    期   : 2012年3月1日
   作    者   : w00176964
   修改内容   : DTS2012022407450:增加GMM的联合RAU/ATTACH类型，MMC转发给LMM
 7.日    期   : 2012年03月30日
   作    者   : l00130025
   修改内容   : DTS2012032307791,发给LMM注册结果,CombineReg时需要区分结果域
 8.日    期   : 2012年6月8日
   作    者   : l00130025
   修改内容   : DTS2012060702423:Anycell驻留后，注册成功时，没有通知通知APS/CDS消息，无法数传
 9.日    期   : 2012年12月6日
   作    者   : s00217060
   修改内容   : DTS2012120410842:注册成功时，需要删除ForbPlmn,ForbLa,ForbGprs等信息
10.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
11.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
12.日    期   : 2014年01月10日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目
13.日    期   : 2014年05月4日
   作    者   : w00176964
   修改内容   : V3R3C60_eCall项目调整
*****************************************************************************/
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

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstPsRegRsltInd->enActionResult)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-10, begin */
        /* 保存注册结果消息 */
        NAS_MMC_SaveRegRsltCtx(GMM_MMC_PS_REG_RESULT_IND, pstPsRegRsltInd);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-10, end */

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

        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

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

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, pstPsRegRsltInd->enRegFailCause);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcCsRegRslt_BgPlmnSearch
 功能描述  : 对Cs注册结果的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月20日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年11月28日
   作    者   : w00167002
   修改内容   : DTS2011112406707:若当前为假流程且当前的AdditionalAction不为
                初始无效值，则不更新当前的AdditionalAction的值，否则若当前为
                真流程或当前为假流程且AdditionalAction为初始无效值，则更新
                当前的AdditionalAction的值.
                修改原因:在ROAMING BROKER时候，设置1次失败,注册失败1次后，
                MMC需要搜网，但是MMC可能要等两个域的结果(如在选网状态机)，
                当收到系统消息的时候，假流程会更改MMC的AdditionalAction的值,
                导致ROMING BROKER特性失效。
  3.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU

  4.日    期   : 2011年12月15日
    作    者   : w00176964
    修改内容   : V7R1 Phase IV调整,当前SYSCFG中L不在时，也需要向LMM通知ID_MMC_LMM_ACTION_RESULT_REQ
  5.日    期   : 2012年1月3日
    作    者   : w00167002
    修改内容   : DTS2011122006209:g下PS ONLY注册成功_更改为CS后注册失败4次后未发起搜网
                  统一调整注册ADDITIONAL ACTION的值，若是用户自定义的原因值(>=256)，则
                  不保存注册结果。若当前支持L模，则注册原因值小于260时通知LMM.

  6.日    期   : 2012年1月20日
    作    者   : w00167002
    修改内容   : DTS2011122006209:将注册失败的消息通知给处理注册结果函数，
                  能进行更好的扩展.
  7.日    期   : 2012年3月1日
    作    者   : w00176964
    修改内容   : DTS2012022407450:联合ATTACH时,MM不能通知LMM此时CS的注册结果，否则导致TAU的类型不正确
  8.日    期   : 2012年12月6日
    作    者   : s00217060
    修改内容   : DTS2012120410842:注册成功时，需要删除ForbPlmn,ForbLa,ForbGprs等信息
  9.日    期   : 2013年05月08日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 10.日    期   : 2013年12月24日
    作    者   : z00161729
    修改内容   : SVLTE支持NCELL搜网
 11.日    期   : 2014年01月10日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseIII项目
 12.日    期   : 2014年05月4日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整
 13.日    期   : 2014年11月3日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
*****************************************************************************/
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

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

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

        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_NORMAL_SERVICE);
        /* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

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

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS, VOS_TRUE, pstCsRegRsltInd->enRegFailCause);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSpecSearchReq_BgPlmnSearch
 功能描述  : 向接入层发送搜网请求消息
 输入参数  : stDestPlmn
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月23日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年11月11日
   作    者   : w00167002
   修改内容   : DTS2011110907180:将禁止漫游位置区信息作为参数传递进来，向
                接入层发送此FORB ROAM LAS即可

 3.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:当前为关机类型的打断，为了快速响应关机，
                故启动等回复比较短的定时器
 4.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 5.日    期   : 2013年1月15日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:等待WAS的搜网回复定时器长度封装成函数
 6.日    期   : 2014年3月19日
   作    者   : w00242748
   修改内容   : DTS2014031200137:当NV特性打开时，自动开机或者搜网时，如果首次搜索RPLMN的话，
                需要将HPLMN/EHPLMN带给接入层。
7.日    期   : 2015年02月11日
   作    者   : w00167002
   修改内容   : DTS2015021000324:当前在DSDS双卡中，GSM下搜网可能不回NAS 搜网NO RF,那么
                NAS搜网定时器超时，则上报无服务了。修改为延长NAS定时器时长
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_IsVplmnValid
 功能描述  : 回vplmn时，判断vplmn接入技术是否有效
             1) 如果vplmn是L的网络且当前ps卡无效
                或此时L已disable或syscfg设置L不支持时认为vplmn接入技术无效，无需回vplmn直接退状态机;
             2) 如果vplmn是GU的网络，syscfg设置不支持GU，此时认为vplmn接入技术无效，无需回vplmn直接退状态机
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - vplmn接入技术有效
             VOS_FALSE - vplmn接入技术无效
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月30日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2012年8月27日
    作    者   : l00167671
    修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网
  3.日    期   : 2012年10月20日
    作    者   : s00217060
    修改内容   : 问题单: DTS2012082306472,背景搜没能找到可以注册的网络回退到V时，
                 如果Vplmn是Lte网络,并且PS卡有效且允许注册,需要Enable Lte,重回Vplmn
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_ReCampVPlmn_BgPlmnSearch
 功能描述  : 回VPLMN的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2012年10月20日
    作    者   : s00217060
    修改内容   : 问题单: DTS2012082306472,背景搜没能找到可以注册的网络回退到V时，
                 如果Vplmn是Lte网络,并且PS卡有效且允许注册,需要Enable Lte,重回Vplmn
  3.日    期   : 2013年01月23日
    作    者   : s00217060
    修改内容   : 问题单: DTS2013012106172,Enable Lte时停止定时器TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  4.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
  5.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_IsAdditionalTriggerPlmnSearch_BgPlmnSearch
 功能描述  : 根据当前注册导致的addition值,判断是否需要导致搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月1日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SearchNextHighPrioPlmn_BgPlmnSearch
 功能描述  : 搜索下一个高优先级网络的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 获取下一个高优先级网络成功
             VOS_FALSE - 获取下一个高优先级网络失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2012年4月30日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL BG搜网修改
  3.日    期   : 2012年8月27日
    作    者   : l00167671
    修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_PerformAbortRegFinished_BgPlmnSearch
 功能描述  : CS、PS注册结果接收到后存在Abort标志处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2012年4月24日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL BG搜网修改
  3.日    期   : 2012年5月18日
    作    者   : w00176964
    修改内容   : V7R1C50 GUL BG搜网修改
  4.日    期   : 2012年8月27日
    作    者   : l00167671
    修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 6.日    期   : 2012年11月22日
   作    者   : t00212959
   修改内容   : DTS2012112006974:#18造成disable LTE，主动释放链接
*****************************************************************************/
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

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_PerformAdditionalActionRegFinished_BgPlmnSearch
 功能描述  : CS、PS注册结果接收到后的附加处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2012年4月24日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL BG搜网修改
  3.日    期   : 2012年11月22日
    作    者   : t00212959
    修改内容   : DTS2012112006974
  4.日    期   : 2013年2月7日
    作    者   : W00176964
    修改内容   : Volte_phase3项目调整:增加IMS不可用时disable L模的逻辑修改
  5.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : User_Exp_Improve修改
*****************************************************************************/
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

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch
 功能描述  : 连接释放后的附加处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2012年4月24日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
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


    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SndRslt_BgPlmnSearch
 功能描述  : 发送BgPlmnSearch状态机退出结果消息
 输入参数  : enRslt,状态机结果
             ulNeedPlmnSearchFlg,是否需要搜网
             pstSearchPlmnList,接入层搜索到的列表
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月22日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2012年4月24日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL BG搜网修改
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndBgPlmnSearchReq_BgPlmnSearch
 功能描述  : 向接入层发送BG搜网请求消息
 输入参数  : *pstPlmnId,需要搜索的网络
              enRat,需要搜索的接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月22日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月28日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndSuspendReq_BgPlmnSearch
 功能描述  : 向接入层发送挂起请求
 输入参数  : enRat,需要挂起的接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月22日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_SndSuspendReqReCampVPlmn_BgPlmnSearch
 功能描述  : 向接入层发送挂起请求
 输入参数  : enRat,需要挂起的接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月22日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndAsSpecPlmnSearchReq_BgPlmnSearch
 功能描述  : BG search 成功后，向接入层发送指定搜请求
 输入参数  : pstPlmnId  -  需要指定搜的 plmn
             enRat      -  需要指定搜的接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年12月19日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
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



/*****************************************************************************
 函 数 名  : NAS_MMC_SndFastSpecSearchReq_BgPlmnSearch
 功能描述  : 向接入层发送快速指定搜网
 输入参数  : *pstPlmnId,需要搜索的网络
              enRat,需要搜索的接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月22日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改

 3.日    期   : 2012年9月4日
   作    者   : w00167002
   修改内容   : V7R1C50_GUTL_PhaseII:等W快速指定搜网时，不需要到TD下搜网，故修改
                定时器的时长只用于保护在W下搜网。
 4.日    期   : 2015年02月11日
   作    者   : w00167002
   修改内容   : DTS2015021000324:当前在DSDS双卡中，GSM下搜网可能不回NAS 搜网NO RF,那么
                NAS搜网定时器超时，则上报无服务了。修改为延长NAS定时器时长。
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_PerformFastSpecSearch_BgPlmnSearch
 功能描述  : BG搜索完成后进行快速指定搜网
 输入参数  : *pstPlmnId,需要搜索的网络
              enRat,需要搜索的接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月22日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_LoadInterSysFsm_BgPlmnSearch
 功能描述  : 根据SUSPEND的原因值起不同的状态机
 输入参数  : MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月23日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcBgPlmnSearchRlstFail_BgPlmnSearch
 功能描述  : 处理BG搜网的失败结果
 输入参数  : pstSearchedPlmnListInfo -- BG搜网的结果消息转换来的内部搜网信息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月6日
   作    者   : L00171473
   修改内容   : 新生成函数
 2.日    期   : 2011年12月20日
   作    者   : h44270
   修改内容   : BG搜网状态机开始快速指定搜网时，认为当前无网络，通知APS挂起
 3.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数入参
 4.日    期   : 2012年5月7日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网项目调整
*****************************************************************************/
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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

        NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                 NAS_MML_GetSimPsRegStatus());

        /* 进行快速指定搜网 */
        NAS_MMC_PerformFastSpecSearch_BgPlmnSearch(&(stHighPrioPlmnInfo.stPlmnId),
                                                   stHighPrioPlmnInfo.astPlmnRatInfo[0].enRatType);
    }
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf
 功能描述  : 等待BG搜网回复状态收到RRMM_AREA_LOST_IND消息的处理
 输入参数  : pstMsg        - RRMM_AREA_LOST_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年11月14日
   作    者   : z40661
   修改内容   : 新生成函数

 2.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
 3.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更

*****************************************************************************/
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

    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /* 发送状态机结果为失败,需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitGasBgPlmnSearchCnf
 功能描述  : 等待BG搜网回复状态收到RRMM_AREA_LOST_IND消息的处理
 输入参数  : pstMsg        - RRMM_AREA_LOST_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年11月14日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
 3.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更

*****************************************************************************/
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

    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /* 发送状态机结果为失败,需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitWasBgStopCnf
 功能描述  : 等待停止背景搜网回复状态收到RRMM_AREA_LOST_IND消息的处理
 输入参数  : pstMsg        - RRMM_REL_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年11月14日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
 3.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更

*****************************************************************************/
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

    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /* 发送状态机结果为失败,需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitGasBgStopCnf
 功能描述  : 等待停止背景搜网回复状态收到RRMM_AREA_LOST_IND消息的处理
 输入参数  : pstMsg        - RRMM_REL_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年11月14日
   作    者   : z40661
   修改内容   : 新生成函数
 2.日    期   : 2014年5月4日
   作    者   : t00173447
   修改内容   : DTS2014042105390,软银定制需求
 3.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更

*****************************************************************************/
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

    /* 向MM/GMM/TAF报出服务区流程 */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* 更新服务状态 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
     /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /* 发送状态机结果为失败,需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrmmLimitServiceCampInd_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 高优先级搜网等注册结果时，对OOS消息RRMM_LIMIT_SERVICE_CAMP_IND的处理
 输入参数  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月15日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_BgPlmnSearch_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_BgPLmnSearch(ulEventType, pstMsg);
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccImsVoiceCapInd_BgPlmnSearch_WaitCsPsRegRsltInd
 功能描述  : 处理MSCC的IMS VOICE不可用的消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年2月8日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
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

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-8, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrmmLimitServiceCampInd_BgPLmnSearch_WaitRrcConnRelInd
 功能描述  : 高优先级搜网等连接释放时，对OOS消息RRMM_LIMIT_SERVICE_CAMP_IND的处理
 输入参数  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月15日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_BgPLmnSearch_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_BgPLmnSearch(ulEventType, pstMsg);
}


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvRrmmLimitServiceCampInd_BgPLmnSearch
 功能描述  : 高优先级搜网时，对OOS消息的处理
 输入参数  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月27日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2014年6月17日
    作    者   : s00217060
    修改内容   : DTS2014061003286:RRMM_LIMITED_CAMP_IND需要搜网，主动释放链接时设置标志
  3.日    期   : 2015年10月21日
    作    者   : s00217060
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0修改
*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmBgPlmnSearchCnf
 功能描述  : 等待背景搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType   - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年4月25
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSysInfoInd_BgPlmnSearch_WaitLmmBgPlmnSearchCnf
 功能描述  : 等待背景搜网回复状态收到ID_LMM_MMC_SYS_INFO_IND消息的处理
 输入参数  : pstMsg        - ID_LMM_MMC_SYS_INFO_IND消息
             ulEventType   - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年4月25
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年4月18日
   作    者   : l00130025
   修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
 3.日    期   : 2012年11月29日
   作    者   : w00176964
   修改内容   : DTS2012042804167:通知CBA模块当前接入模式为LTE
 4.日    期   : 2012年12月20日
   作    者   : w00176964
   修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
 5.日    期   : 2012年12月20日
   作    者   : w00176964
   修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
 6.日    期   : 2013年1月19日
    作    者   : t00212959
    修改内容   : DTS2012122900189:EPS注册状态完全由L上报
 7.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
*****************************************************************************/
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

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /* 转发系统消息给GMM,供RABM使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
函 数 名  : NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitLmmBgPlmnSearchCnf
功能描述  : 等待背景搜网回复状态收到ID_LMM_MMC_BG_PLMN_SEARCH_CNF消息的处理
输入参数  : pstMsg        - ID_LMM_MMC_BG_PLMN_SEARCH_CNF消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年4月25
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2012年5月17
  作    者   : w00176964
  修改内容   : GUL BG项目调整
3.日    期   : 2012年6月25
  作    者   : z00161729
  修改内容   : DTS2012061908820:L上报bg搜网失败没有带任何网络时未更新接入技术
4.日    期   : 2012年9月3日
  作    者   : w00167002
  修改内容   : V7R1C50_GUTL_PhaseII:如果在BG搜时候发生了同系统重选到TD国家网络,则在TDD模式下，
               需要退出BG状态机。
5.日    期   : 2012年10月29日
  作    者   : t00212959
  修改内容   : DTS2012080305980，相同PLMN，不同RAT，不再发起快速指定搜
6.日    期   : 2012年12月13日
  作    者   : L00171473
  修改内容   : DTS2012121802573, TQE清理
7.日    期   : 2013年12月20日
   作    者   : w00167002
   修改内容   : DTS2013112917981:guNAS删除在TD模式下不能进行bg搜的限制
 8.日    期   : 2014年2月22日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search调整:不比较驻留PLMN与BG搜的PLMN同时BG搜成功进行快速指定搜网时enable LTE
*****************************************************************************/
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

                /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
                NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
                /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

/*****************************************************************************
函 数 名  : NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitLmmBgPlmnSearchCnf
功能描述  : 等待背景搜网回复状态收到TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF消息的处理
输入参数  : pstMsg        - TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年4月25
 作    者   : z00161729
 修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
函 数 名  : NAS_MMC_RcvLmmMmcAreaLostInd_BgPlmnSearch_WaitLmmBgPlmnSearchCnf
功能描述  : 等待背景搜网回复状态收到ID_LMM_MMC_AREA_LOST_IND消息的处理
输入参数  : pstMsg        - ID_LMM_MMC_AREA_LOST_IND消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年4月25
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
3.日    期   : 2015年10月22日
  作    者   : s00217060
  修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更
*****************************************************************************/
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
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /* 发送状态机结果为失败,需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();
    return VOS_TRUE;
}

/*****************************************************************************
函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmBgStopCnf
功能描述  : 等待停止背景搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年4月25
  作    者   : z00161729
  修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
函 数 名  : NAS_MMC_RcvLmmSysInfoInd_BgPlmnSearch_WaitLmmBgStopCnf
功能描述  : 等待停止背景搜网回复状态收到ID_LMM_MMC_SYS_INFO_IND消息的处理
输入参数  : pstMsg        - ID_LMM_MMC_SYS_INFO_IND消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年4月25
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2012年4月18日
  作    者   : l00130025
  修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
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

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /* 转发系统消息给GMM,供RABM使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
函 数 名  : NAS_MMC_RcvBgPlmnStopCnf_BgPlmnSearch_WaitLmmBgStopCnf
功能描述  : 等待停止背景搜网回复状态收到ID_LMM_MMC_STOP_BG_PLMN_SEARCH_CNF消息的处理
输入参数  : pstMsg        - ID_LMM_MMC_STOP_BG_PLMN_SEARCH_CNF消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年4月25
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2015年9月30
  作    者   : y00346957
  修改内容   : DTS2015070910885 modify
*****************************************************************************/
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


/*****************************************************************************
函 数 名  : NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitLmmBgStopCnf
功能描述  : 等待停止背景搜网回复状态收到ID_LMM_MMC_BG_PLMN_SEARCH_CNF消息的处理
输入参数  : pstMsg        - ID_LMM_MMC_STOP_BG_PLMN_SEARCH_CNF消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年6月4
  作    者   : w00176964
  修改内容   : 新生成函数
2.日    期   : 2012年6月25
  作    者   : z00161729
  修改内容   : DTS2012061908820:L上报bg搜网失败没有带任何网络时未更新接入技术

*****************************************************************************/
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

/*****************************************************************************
函 数 名  : NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitLmmBgStopCnf
功能描述  : 等待停止背景搜网回复状态收到TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF消息的处理
输入参数  : pstMsg        - TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年4月25
  作    者   : z00161729
  修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
函 数 名  : NAS_MMC_RcvLmmMmcAreaLostInd_BgPlmnSearch_WaitLmmBgStopCnf
功能描述  : 等待停止背景搜网回复状态收到ID_LMM_MMC_AREA_LOST_IND消息的处理
输入参数  : pstMsg        - ID_LMM_MMC_AREA_LOST_IND消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年4月25
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2014年5月5日
  作    者   : w00242748
  修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
               注册状态的上报。
3.日    期   : 2015年10月22日
  作    者   : s00217060
  修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更
*****************************************************************************/
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
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /* 发送状态机结果为失败,需要搜网 */
    NAS_MMC_SndRslt_BgPlmnSearch(NAS_MMC_BG_PLMN_SEARCH_FAIL, VOS_TRUE, astPlmnListInfo);

    /* 退出当前状态机 */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmPlmnFastSearchCnf
功能描述  : 等待快速指定搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年4月25
  作    者   : z00161729
  修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
函 数 名  : NAS_MMC_RcvLmmPlmnSrchCnf_BgPlmnSearch_WaitLmmPlmnFastSearchCnf
功能描述  : 等待快速指定搜网回复状态收到ID_LMM_MMC_PLMN_SRCH_CNF消息的处理
输入参数  : pstMsg        - ID_LMM_MMC_PLMN_SRCH_CNF消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年4月25
  作    者   : z00161729
  修改内容   : 新生成函数

2.日    期   : 2014年6月12日
  作    者   : w00167002
  修改内容   : DSDS III:搜网NO RF后的处理
*****************************************************************************/
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

/*****************************************************************************
函 数 名  : NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_BgPlmnSearch_WaitLmmPlmnFastSearchCnf
功能描述  : 等待快速指定搜网回复状态收到TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF消息的处理
输入参数  : pstMsg        - TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年4月25
  作    者   : z00161729
  修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmFastPlmnStopCnf
功能描述  : 等待停止快速指定搜网回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
输入参数  : pstMsg        - MMCMMC_ABORT_FSM_REQ消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年4月25
  作    者   : z00161729
  修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
函 数 名  : NAS_MMC_RcvLmmPlmnSrchStopCnf_BgPlmnSearch_WaitLmmFastPlmnStopCnf
功能描述  : 等待停止快速指定搜网回复状态收到ID_LMM_MMC_STOP_PLMN_SRCH_CNF消息的处理
输入参数  : pstMsg        - ID_LMM_MMC_STOP_PLMN_SRCH_CNF消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
1.日    期   : 2012年4月25
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2012年5月5
  作    者   : w00176964
  修改内容   : GUL BG项目调整
  修改内容   : 新生成函数
3.日    期   : 2012年5月18
  作    者   : w00176964
  修改内容   : GUL BG项目调整
5.日    期   : 2012年8月27日
  作    者   : l00167671
  修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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


/*****************************************************************************
函 数 名  : NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitLmmFastPlmnStopCnf
功能描述  : 等待停止快速指定搜网回复状态收到ID_LMM_MMC_PLMN_SRCH_CNF消息的处理
输入参数  : pstMsg        - ID_LMM_MMC_PLMN_SRCH_CNF消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
 1.日    期   : 2012年6月4
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 3.日    期   : 2014年6月25日
   作    者   : b00269685
   修改内容   : DSDS III项目
*****************************************************************************/
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
/*****************************************************************************
函 数 名  : NAS_MMC_RcvTiWaitLmmStopCnfExpired_BgPlmnSearch_WaitLmmFastPlmnStopCnf
功能描述  : 等待停止快速指定搜网回复状态收到TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF消息的处理
输入参数  : pstMsg        - TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF消息
            ulEventType   - 消息类型
输出参数  : 无
返 回 值  : VOS_FALSE:处理消息失败
            VOS_TRUE:处理消息成功
调用函数  :
被调函数  :

修改历史     :
 1.日    期   : 2012年4月25
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年5月2日
   作    者   : w00176964
   修改内容   : GUL BG项目调整
 3.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmSuspendCnf
 功能描述  : 等待挂起回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型到状态机上下文中
 3.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendCnf_BgPlmnSearch_WaitLmmSuspendCnf
 功能描述  : 等待挂起回复状态收到ID_LMM_MMC_SUSPEND_CNF消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_SUSPEND_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 2.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 4.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitLSysInfoInd
 功能描述  : 等待系统消息状态收到ID_LMM_MMC_SYS_INFO_IND消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_SYS_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数

 2.日    期   : 2011年11月3日
   作    者   : w00167002
   修改内容   : 如果当前为PS ONLY或者当前仅仅支持L模，则更新CS的AdditionalAction为
                 NAS_MMC_ADDITIONAL_ACTION_BUTT，即后续的搜网动作完全由PS域结果来确定
 3.日    期   : 2011年12月30日
   作    者   : l65478
   修改内容   : 在迁到L模时,不立刻把CS设置成可选搜网,而是等待PS注册结果时
                根据具体的原因值再设置
 4.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名和替换函数
 5.日    期   : 2012年4月18日
   作    者   : l00130025
   修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
 6.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网调整
 7.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:正常服务状态，等注册状态后再发系统消息，否则立即发
                系统消息
 8.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 9.日    期   : 2012年11月29日
   作    者   : w00176964
   修改内容   : DTS2012042804167:通知CBA模块当前接入模式为LTE
10.日    期   : 2012年12月20日
   作    者   : w00176964
   修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
11.日    期   : 2013年1月19日
   作    者   : t00212959
   修改内容   : DTS2012122900189:EPS注册状态完全由L上报
12.日    期   : 2013年2月7日
   作    者   : W00176964
   修改内容   : Volte_phase3项目调整:增加IMS不可用时disable L模的逻辑修改
13.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
*****************************************************************************/
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

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
#if (FEATURE_ON == FEATURE_IMS)
    /* 增加等待IMS是否可用结果FLG,MSCC保证收到PS注册结果上报IMS是否可用指示到MMC */
    NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */

    /* 更新CS的AdditionalAction */
    NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* CBS上报*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLSysInfoExpired_BgPlmnSearch_WaitLSysInfoInd
 功能描述  : 等待系统消息状态收到TI_NAS_MMC_WAIT_LMM_SYS_INFO消息的处理
 输入参数  : pMsg        - TI_NAS_MMC_WAIT_LMM_SYS_INFO消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 2.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLSysInfoInd
 功能描述  : 等待系统消息状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数

 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型
 3.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcStatusInd_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待注册结果状态收到ID_LMM_MMC_STATUS_IND消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_STATUS_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
 3.日    期   : 2015年9月17日
   作    者   : y00346957
   修改内容   : DTS2015070910885，增加对当前搜索lte的plmn是否可以搜的判断

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcAttachInd_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待注册结果状态收到ID_LMM_MMC_ATTACH_IND消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_ATTACH_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年10月25日
   作    者   : z00161729
   修改内容   : V7R1 phase III 联合注册修改
 3.日    期   : 2012年1月8日
   作    者   : z00161729
   修改内容   : V7R1 Phase IV调整
 4.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
 5.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 6.日    期   : 2014年11月28日
   作    者   : w00281933
   修改内容   : 服务状态优化Phase I
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcTauResultInd_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待注册结果状态收到ID_LMM_MMC_TAU_RESULT_IND消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_TAU_RESULT_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年10月26日
   作    者   : w00176964
   修改内容   : V7R1 Phase III调整:联合注册修改
 3.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
 4.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 5.日    期   : 2014年11月28日
   作    者   : w00281933
   修改内容   : 服务状态优化Phase I
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcDetachInd_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待注册结果状态收到ID_LMM_MMC_DETACH_IND消息的处理
 输入参数  : pMsg        - LMM_MMC_DETACH_IND_STRU消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月19日
   作    者   : s46746
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

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
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcServiceRsltInd_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待注册结果状态收到ID_LMM_MMC_SERVICE_RESULT_IND消息的处理
 输入参数  : pMsg        - LMM_MMC_SERVICE_RESULT_IND_STRU消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月19日
   作    者   : s46746
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待注册结果状态收到ID_LMM_MMC_SUSPEND_IND消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_SUSPEND_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcMmcSuspendRslt_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待注册结果状态收到MMCMMC_SUSPEND_RSLT_CNF消息的处理
 输入参数  : pMsg        - MMCMMC_SUSPEND_RSLT_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 2.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
4.日    期   : 2013年4月9日
  作    者   : y00176023
  修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败迁移到ooc
 5.日    期   : 2014年1月27日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
*****************************************************************************/
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

                /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
                NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
                /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
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
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待注册结果状态收到TI_NAS_MMC_WAIT_EPS_REG_IND消息的处理
 输入参数  : pMsg        - TI_NAS_MMC_WAIT_EPS_REG_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 2.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
  5.日    期   : 2015年1月7日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI修改
*****************************************************************************/
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

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmAreaLostInd_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待注册结果状态收到ID_LMM_MMC_AREA_LOST_IND消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_AREA_LOST_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年11月9日
   作    者   : w00167002
   修改内容   : 在注册过程中收到丢网指示，则更新当前的网络的注册状态为
                 NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,否则查找下一个网络依然为
                 已经丢网的网络。
 3.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年6月16日
   作    者   : t00212959
   修改内容   : V7R1C50 GUL BG搜网修改
 5.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 6.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 7.日    期   : 2014年5月5日
   作    者   : w00242748
   修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                注册状态的上报。
 8.日    期   : 2014年6月12日
   作    者   : w00167002
   修改内容   : DSDS III:在NO RF丢网后进OOC状态
 9.日    期   : 2015年1月7日
   作    者   : s00217060
   修改内容   : Service_State_Optimize_PhaseI修改
10.日    期   : 2015年10月22日
   作    者   : s00217060
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND消息接口变更
*****************************************************************************/
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

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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


    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待注册结果状态收到ID_LMM_MMC_SYS_INFO_IND消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_SYS_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
 3.日    期   : 2012年4月18日
   作    者   : l00130025
   修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
 4.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
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

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待注册结果状态收到ID_MSCC_MMC_SYS_CFG_SET_REQ消息的处理
 输入参数  : pMsg        - ID_MSCC_MMC_SYS_CFG_SET_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待注册结果状态收到MMCMMC_SYSCFG_RSLT_CNF消息的处理
 输入参数  : pMsg        - MMCMMC_SYSCFG_RSLT_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改

*****************************************************************************/
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

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccImsVoiceCapInd_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 处理MSCC的IMS VOICE是否可用消息
 输入参数  : ulEventType:消息类型
             pstMsg:消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
             VOS_FALSE:处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年2月7日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年1月7日
   作    者   : s00217060
   修改内容   : Service_State_Optimize_PhaseI修改

*****************************************************************************/
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

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-2-7, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待注册结果状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数

 2.日    期   : 2011年11月3日
   作    者   : w00167002
   修改内容   : 在注册过程中收到立即打断，意味着注册尚未完成，更新未完成的域的服务
                 状态为LIMIT SERVICE，否则当前的服务状态可能为NORMAL_SERVICE,这样若被用户
                 指定搜打断，且网络接入技术都相同的情况下，就不会进行搜网注册了
 3.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:增加打断事件ID，状态机可以知道是什么事件
                打断自己的。
                修改原因:用户下发关机命令后，当前可能在等注册结果或者在等连接
                释放，可能需要比较久的时间才能处理关机命令，通过增加打断事件，
                如归当前在等注册结果或者等链接释放状态，若收到关机命令，则直接
                退出当前状态机，处理用户的关机命令。
 4.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
 5.日    期   : 2012年6月25日
   作    者   : l60609
   修改内容   : AT&T&DCM:判断是否需要发送系统消息
 6.日    期   : 2012年12月11日
   作    者   : l00167671
   修改内容   : DTS2012121802573, TQE清理
 7.日    期   : 2015年1月7日
   作    者   : s00217060
   修改内容   : Service_State_Optimize_PhaseI修改
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcStatusInd_BgPlmnSearch_WaitEpsConnRelInd
 功能描述  : 等待连接释放状态收到ID_LMM_MMC_STATUS_IND消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_STATUS_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月26日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网修改
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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

            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */
    }
    else
    {
        /* 当前为被动释放，根据CS和PS的additional Action进一步处理 */
        NAS_MMC_PerformAdditionalActionConnRel_BgPlmnSearch();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitEpsConnRelIndExpired_BgPlmnSearch_WaitEpsConnRelInd
 功能描述  : 等待连接释放状态收到TI_NAS_MMC_WAIT_EPS_CONN_REL_IND消息的处理
 输入参数  : pMsg        - TI_NAS_MMC_WAIT_EPS_CONN_REL_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
 3.日    期   : 2012年5月18日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网调整
 4.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
*****************************************************************************/
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

                /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
                NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
                /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitEpsConnRelInd
 功能描述  : 等待连接释放状态收到ID_LMM_MMC_SYS_INFO_IND消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_SYS_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
 3.日    期   : 2012年4月18日
   作    者   : l00130025
   修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
 4.日    期   : 2012年11月29日
   作    者   : w00176964
   修改内容   : DTS2012042804167:通知CBA模块当前接入模式为LTE
 5.日    期   : 2012年12月20日
   作    者   : w00176964
   修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
 6.日    期   : 2013年1月19日
    作    者   : t00212959
    修改内容   : DTS2012122900189:EPS注册状态完全由L上报
 7.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
*****************************************************************************/
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

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

    /* 转发系统消息给GMM,供RABM使用 */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendInd_BgPlmnSearch_WaitEpsConnRelInd
 功能描述  : 等待连接释放状态收到ID_LMM_MMC_SUSPEND_IND消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_SUSPEND_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSuspendRslt_BgPlmnSearch_WaitEpsConnRelInd
 功能描述  : 等待连接释放状态收到MMCMMC_SUSPEND_RSLT_CNF消息的处理
 输入参数  : pMsg        - MMCMMC_SUSPEND_RSLT_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
 3.日    期   : 2013年4月9日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:收到NO RF 退状态机，发送失败迁移到ooc
 4.日    期   : 2014年1月27日
   作    者   : s00246516
   修改内容   : L-C互操作项目:增加异系统到HRPD的处理
*****************************************************************************/
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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
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
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitEpsConnRelInd
 功能描述  : 等待连接释放状态收到ID_MSCC_MMC_SYS_CFG_SET_REQ消息的处理
 输入参数  : pMsg        - ID_MSCC_MMC_SYS_CFG_SET_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 直接调起syscfg层二状态机 */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitEpsConnRelInd
 功能描述  : 等待连接释放状态收到MMCMMC_SYSCFG_RSLT_CNF消息的处理
 输入参数  : pMsg        - MMCMMC_SYSCFG_RSLT_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcDetachInd_BgPlmnSearch_WaitEpsConnRelInd
 功能描述  : 等待注册结果状态收到ID_LMM_MMC_DETACH_IND消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_DETACH_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月01日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

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
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcDetachCnf_BgPlmnSearch_WaitEpsConnRelInd
 功能描述  : 在等待EPS链路释放的时候用户detach CNF的的处理
 输入参数  : ulEventType:消息类型
             pstMsg: ID_LMM_MMC_DETACH_CNF消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2012年4月24日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitEpsConnRelInd
 功能描述  : 等待连接释放状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:增加打断事件ID，状态机可以知道是什么事件
                打断自己的。
                修改原因:用户下发关机命令后，当前可能在等注册结果或者在等连接
                释放，可能需要比较久的时间才能处理关机命令，通过增加打断事件，
                如归当前在等注册结果或者等链接释放状态，若收到关机命令，则直接
                退出当前状态机，处理用户的关机命令。
 3.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucRelRequestFlg;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* 若打断类型是用户请求的关机，则直接退出等链接释放结果状态机 */
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcTauResultInd_BgPlmnSearch_WaitEpsConnRelInd
 功能描述  : 在等待EPS链路释放的时候用户ID_LMM_MMC_TAU_RESULT_IND的的处理,
             在主动释放连接场景可能会收到注册结果
 输入参数  : ulEventType:消息类型
             pstMsg: ID_LMM_MMC_TAU_RESULT_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理成功
             VOS_FALSE:处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月12日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmMmcAttachInd_BgPlmnSearch_WaitEpsConnRelInd
 功能描述  : 在等待EPS链路释放的时候用户ID_LMM_MMC_ATTACH_IND的的处理,
             在主动释放连接场景可能会收到注册结果
 输入参数  : ulEventType:消息类型
             pstMsg: ID_LMM_MMC_ATTACH_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:处理成功
             VOS_FALSE:处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月12日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmPlmnSearchCnfReCampVPlmn
 功能描述  : 回VPlmn等待搜网结果回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型
 3.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnCnf_BgPlmnSearch_WaitLmmPlmnSearchCnfReCampVPlmn
 功能描述  : 回VPlmn等待搜网结果回复状态收到ID_LMM_MMC_PLMN_SRCH_CNF消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_PLMN_SRCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
 3.日    期   : 2012年11月05日
   作    者   : w00176964
   修改内容   : DTS2011082405001:根据搜网列表信息更新网络覆盖类型

 4.日    期   : 2014年6月24日
   作    者   : w00167002
   修改内容   : DSDS III:在RECAMP LTE时候，如果NO RF，则进入OOC
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmSrchCnf_BgPlmnSearch_WaitLmmPlmnSearchCnfReCampVPlmn
 功能描述  : 回VPlmn等待搜网结果回复状态收到TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF消息的处理
 输入参数  : pMsg        - TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmSuspendCnfReCampVPlmn
 功能描述  : 回VPlmn等待挂起回复状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型
 3.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmSuspendCnf_BgPlmnSearch_WaitLmmSuspendCnfReCampVPlmn
 功能描述  : 回VPlmn等待挂起回复状态收到ID_LMM_MMC_SUSPEND_CNF消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_SUSPEND_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数

 2.日    期   : 2011年12月15日
   作    者   : w00167002
   修改内容   : DTS2011120702166:MMC复位后无复位信息,在MML模块封装复位信息，
                 以供MM层调用，进行软复位。
 3.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
 4.日    期   : 2012年5月14日
   作    者   : w00176964
   修改内容   : V7R1C50 GUL BG搜网调整
  5.日    期   : 2012年6月14日
   作    者   : t00212959
   修改内容   : V7R1C50 GUL BG搜网修改,回VPLMN失败，区分是否打断
 6.日    期   : 2012年8月27日
   作    者   : l00167671
   修改内容   : 问题单: DTS2012080605217,背景搜没能找到可以注册的网络回退到V时，
                 V在禁止列表中或者forbid plmn for gprs列表中时进入限制服务并不再
                 发起搜网,将原函数NAS_MMC_IsVplmnNetRatValid改名成NAS_MMC_IsVplmnValid
                 并在该函数中增加了判断V是否在禁止列表中或者forbid plmn for gprs列表中，
                 若在两个列表中的任意一个列表中则认为Vplmn已经无效
 7.日    期   : 2015年3月11日
   作    者   : wx270776
   修改内容   : DTS2015011212939:增加复位场景
*****************************************************************************/
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

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn
 功能描述  : 等待接入层停止搜网状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型
 3.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnStopCnf_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn
 功能描述  : 回VPlmn等待停止搜网回复状态收到ID_LMM_MMC_STOP_PLMN_SRCH_CNF消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_STOP_PLMN_SRCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLmmPlmnSearchCnf_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn
 功能描述  : 回VPlmn等待停止搜网回复状态收到ID_LMM_MMC_PLMN_SRCH_CNF消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_PLMN_SRCH_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年6月25日
   作    者   : b00269685
   修改内容   : DSDS III新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLmmStopCnf_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn
 功能描述  : 回VPlmn等待停止搜网回复状态收到TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF消息的处理
 输入参数  : pMsg        - TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitLSysInfoIndReCampVPlmn
 功能描述  : 回VPlmn等待系统消息状态收到ID_LMM_MMC_SYS_INFO_IND消息的处理
 输入参数  : pMsg        - ID_LMM_MMC_SYS_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
 3.日    期   : 2012年4月18日
   作    者   : l00130025
   修改内容   : DTS2012040200480,单独维护EPS注册状态,供L模下CEREG/CGREG查询和上报使用
 4.日    期   : 2012年11月29日
   作    者   : w00176964
   修改内容   : DTS2012042804167:通知CBA模块当前接入模式为LTE
 5.日    期   : 2012年12月20日
   作    者   : w00176964
   修改内容   : DTS2012121906946:收到L的系统消息转发给LMM
 6.日    期   : 2013年1月19日
    作    者   : t00212959
    修改内容   : DTS2012122900189:EPS注册状态完全由L上报
 7.日    期   : 2015年02月11日
   作    者   : l00305157
   修改内容   : Service_State_Optimize_PhaseII 项目修改
                 方案优化后，LTE下的小区发生变化，LMM会通过系统消息通知MMC
*****************************************************************************/
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

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-18, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvTiWaitLSysInfoExpired_BgPlmnSearch_WaitLSysInfoIndReCampVPlmn
 功能描述  : 回VPlmn等待系统消息状态收到TI_NAS_MMC_WAIT_LMM_SYS_INFO消息的处理
 输入参数  : pMsg        - TI_NAS_MMC_WAIT_LMM_SYS_INFO消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLSysInfoIndReCampVPlmn
 功能描述  : 回VPlmn等待系统消息状态收到MMCMMC_ABORT_FSM_REQ消息的处理
 输入参数  : pMsg        - MMCMMC_ABORT_FSM_REQ消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2011年11月29日
   作    者   : w00167002
   修改内容   : DTS2011112301233:保存打断事件类型
 3.日    期   : 2012年4月24日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改函数名
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedAttachInd_BgPlmnSearch
 功能描述  : 高优先级搜网时，对Eps联合注册结果的处理
 输入参数  : pstLmmAttachIndMsg - combine attach消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2011年12月8日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整
  3.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  4.日    期   : 2011年12月13日
    作    者   : z00161729
    修改内容   : DTS2011121302231:attach被拒#9/#10按协议应该按other cause处理
  5.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                    additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  6.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  7.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改,DTS2012090401249
  8.日    期   : 2014年5月5日
    作    者   : w00242748
    修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                 注册状态的上报。
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmCombinedAttachInd_BgPlmnSearch(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

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


                /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
                NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
                /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
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
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmEpsOnlyAttachInd_BgPlmnSearch
 功能描述  : 高优先级搜网时，对Eps注册结果的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年10月30日
    作    者   : z00161729
    修改内容   : V7R1 phaseIII修改函数名
  3.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  4.日    期   : 2011年12月14日
    作    者   : w00176964
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  5.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                  ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。
                  将函数名由NAS_MMC_ProcEpsRegFail更改为NAS_MMC_ProcEpsAttachRegFail
                  调用ATTACH的注册原因值表进行处理。
  6.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  7.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                  additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  8.日    期   : 2012年4月24日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL BG搜网修改函数名
  9.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  10.日    期   : 2012年9月4日
     作    者   : z00161729
     修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
  11.日    期   : 2012年09月12日
     作    者   : z00161729
     修改内容   : DTS2012082904888：cs ps mode1，on plmn、plmn list、bg plmn search状态机在eps only注册成功未调用NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc判断是否需要disable lte
  12.日    期   : 2012年12月6日
     作    者   : s00217060
     修改内容   : DTS2012120410842:注册成功时，需要删除ForbPlmn,ForbGprs等信息
  13.日    期   : 2013年05月08日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  14.日    期   : 2013年12月10日
     作    者   : w00176964
     修改内容   : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
  15.日    期   : 2014年5月6日
     作    者   : z00161729
     修改内容   : DTS2014050602850:l下联合注册eps成功，cs注册被#18拒绝，disable lte到gu下搜网注册成功，后指定搜l cs注册被#18拒绝的网络，l发起eps单域注册成功，mmc没有disable lte
  16.日    期   : 2014年5月5日
     作    者   : w00242748
     修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                  注册状态的上报。
  17.日    期   : 2015年4月18日
     作    者   : z00161729
     修改内容   : 24301 R11 CR升级项目修改
  18.日    期   : 2015年02月11日
     作    者   : l00305157
     修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果ATTACH (EPS ONLY)成功，上报注册状态
  19.日    期   : 2015年06月09日
     作    者   : l00305157
     修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果，需先更新EPLMN LIST，在处理注册状态的上报
  20.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmEpsOnlyAttachInd_BgPlmnSearch(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    VOS_UINT32                                              ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stLEplmnInfo;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */
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

        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        /* 如果CS允许注册而且CS卡有效则更改CS注册状态为NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

        /*注意: 需要先更新EPLMN LIST，在处理注册状态的上报,因为NAS_MMC_UpdatePsRegStatePsRegSucc()函数中会根据EPLMN LIST上报注册状态 */

        NAS_MMC_UpdateGURegRlstRPlmnIdInNV();

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
        /* Added by w00176964 for APS服务状态通知清理, 2014-4-7, begin */
        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                  NAS_MML_GetSimPsRegStatus());
        /* Added by w00176964 for APS服务状态通知清理, 2014-4-7, end */
    }
    else if ((MMC_LMM_ATT_RSLT_FAILURE == pstLmmAttachIndMsg->ulAttachRslt)
          && (VOS_FALSE == pstLmmAttachIndMsg->bitOpAtmpCnt))
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
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
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmAttachInd_BgPlmnSearch
 功能描述  : 高优先级搜网时，对Eps注册结果的处理
 输入参数  : pstLmmAttachIndMsg - lmm attach消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月25日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmCombinedTauResultInd_BgPlmnSearch
 功能描述  : 高优先级搜网时，对Eps 联合TAU结果的处理
 输入参数  : pstLmmTauIndMsg - combined tau消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月27日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月8日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整
  3.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  4.日    期   : 2011年12月13日
    作    者   : z00161729
    修改内容   : DTS2011121302231:attach被拒#9/#10按协议应该按other cause处理
  4.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                  additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  5.日    期   : 2012年4月24日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL BG搜网修改
  6.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  7.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_BgPlmnSearch(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

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
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmEpsOnlyTauResultInd_BgPlmnSearch
 功能描述  : 高优先级搜网时，对Eps TAU结果的处理
 输入参数  : pstLmmTauIndMsg - lmm tau消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月20日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年12月5日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改合并原NAS_MMC_HPLMN_REG_REJ_STRU和NAS_MMC_PLMN_REG_INFO_STRU
  3.日    期   : 2011年12月15日
    作    者   : w00167002
    修改内容   : DTS2011121307570: MMC没有维护LMM的EPLMN信息，现在统一调整
                ATTACH/TAU/DETACH/SERVICE中被拒时EPLMN的维护。
                将函数名由NAS_MMC_ProcEpsRegFail更改为NAS_MMC_ProcEpsTauRegFail
                调用TAU的注册原因值表进行处理。
  4.日    期   : 2011年12月20日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整:UT修改NAS_MMC_SetUserSpecPlmnRegisterStatus
                 只在搜网状态机和ON PLMN下进行设置
  5.日    期   : 2012年1月8日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV调整:EPS单域注册假流程调整
  6.日    期   : 2012年2月4日
    作    者   : w00167002
    修改内容   : DTS2011122704039:将注册结果类型以及注册消息传递给处理注册结果
                  函数，扩展注册结果函数的处理能力。
                  additional action值若为无效值NAS_MMC_ADDITIONAL_ACTION_BUTT
                 则不更新当前的additional action
  7.日    期   : 2012年4月24日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL BG搜网修改函数名
  8.日    期   : 2012年06月01日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 C50 CS/PS mode 1
  9.日    期   : 2012年8月21日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改DTS2012090401249
  10.日    期   : 2012年09月12日
     作    者   : z00161729
     修改内容   : DTS2012082904888：cs ps mode1，on plmn、plmn list、bg plmn search状态机在eps only注册成功未调用NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc判断是否需要disable lte
  11.日    期   : 2012年12月6日
     作    者   : s00217060
     修改内容   : DTS2012120410842:注册成功时，需要删除ForbPlmn,ForbGprs等信息
  12.日    期   : 2013年05月08日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  13.日    期   : 2013年12月10日
     作    者   : w00176964
     修改内容   : VoLTE_PhaseIII 项目:修改Disable L模的逻辑
  14.日    期   : 2014年5月6日
     作    者   : z00161729
     修改内容   : DTS2014050602850:l下联合注册eps成功，cs注册被#18拒绝，disable lte到gu下搜网注册成功，后指定搜l cs注册被#18拒绝的网络，l发起eps单域注册成功，mmc没有disable lte
  15.日    期   : 2014年5月5日
     作    者   : w00242748
     修改内容   : DTS2014043000311:注册状态服务状态不一致，将MMC中报服务状态的场景，都加
                  注册状态的上报。
  16.日    期   : 2014年5月14日
     作    者   : w00242748
     修改内容   : DTS2014051206381:枚举值使用不对
  17.日    期   : 2015年4月18日
     作    者   : z00161729
     修改内容   : 24301 R11 CR升级项目修改
  18.日    期   : 2015年02月11日
     作    者   : l00305157
     修改内容   : Service_State_Optimize_PhaseII 项目修改
  19.日    期   : 2015年06月09日
     作    者   : l00305157
     修改内容   : Service_State_Optimize_PhaseII 项目修改
                    MMC接收到LMM模块注册结果，先更新EPLMN LIST，在处理注册状态的上报
 20.日    期   : 2015年10月14日
    作    者   : c00318887
    修改内容   : DTS2015082002854: 漫游标记不准  
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmEpsOnlyTauResultInd_BgPlmnSearch(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnAddr;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */
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

        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
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
        /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

        /*注意: 需要先更新EPLMN LIST，在处理注册状态的上报,因为NAS_MMC_UpdatePsRegStatePsRegSucc()函数中会根据EPLMN LIST上报注册状态 */

        NAS_MMC_UpdateGURegRlstRPlmnIdInNV();

        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
        /* Added by w00176964 for APS服务状态通知清理, 2014-4-7, begin */
        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                  NAS_MML_GetSimPsRegStatus());
        /* Added by w00176964 for APS服务状态通知清理, 2014-4-7, end */
    }
    else if ((MMC_LMM_TAU_RSLT_FAILURE == pstLmmTauIndMsg->ulTauRst)
          && (VOS_FALSE == pstLmmTauIndMsg->bitOpAtmpCnt))
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;


        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
        /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */
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
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* 通知CSS GEO信息 */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ProcLmmTauResultInd_BgPlmnSearch
 功能描述  : 高优先级搜网时，对Eps TAU结果的处理
 输入参数  : pstLmmTauIndMsg - lmm tau消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月30日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2011年12月28日
    作    者   : z00161729
    修改内容   : V7R1 phaseIV修改周期性tau处理
  3.日    期   : 2012年4月24日
    作    者   : z00161729
    修改内容   : V7R1C50 GUL BG搜网修改
*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccCLAssociatedInfoNtf_BgPlmnSearch_WaitLmmPlmnFastSearchCnf
 功能描述  : 等待L模上报快速指定搜网结果收到ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF消息的处理
 输入参数  : pstMsg      - ID_MSCC_MMC_MSPL_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功

 修改历史     :
 1.日    期   : 2015年9月12日
   作    者   : y00346957
   修改内容   : 新建

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccMsplInfoInd_BgPlmnSearch_WaitLmmBgPlmnSearchCnf
 功能描述  : 等待L模上报BG搜网结果收到ID_MSCC_MMC_MSPL_INFO_IND消息的处理
 输入参数  : pstMsg      - ID_MSCC_MMC_MSPL_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功

 修改历史     :
 1.日    期   : 2015年9月12日
   作    者   : y00346957
   修改内容   : 新建

*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_RcvMsccLteSysPriClassInfoInd_BgPlmnSearch_WaitEpsRegRsltInd
 功能描述  : 等待L模上报BG搜网结果收到ID_MSCC_MMC_MSPL_INFO_IND消息的处理
 输入参数  : pstMsg      - ID_MSCC_MMC_MSPL_INFO_IND消息
             ulEventType - 消息类型
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功

 修改历史     :
 1.日    期   : 2015年9月12日
   作    者   : y00346957
   修改内容   : 新建

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_IsHighPrioRatHplmnSearch_BgPlmnSearch
 功能描述  : 判断是否为高优先级RAT的HPLMN搜索
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  高优先级RAT的HPLMN搜索
             VOS_FALSE 非高优先级RAT的HPLMN搜索
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月22日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
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
/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedEnableLTE_FastSpecSearch
 功能描述  : 判断是否需要 Enable L
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_FALSE:不需要 Enable L
             VOS_TRUE: 需要 Enable L
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年02月14日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
 3.日    期   : 2015年1月5日
   作    者   : h00285180
   修改内容   : LTE #14拒绝优化:DTS2015010401946
 4.日    期   : 2015年11月23日
   作    者   : z00359541
   修改内容   : DTS2015111706562:TAU被网络#17拒绝5次DISABLE LTE，后续背景搜
                又ENABLE LTE导致又会发起TAU被网络#17拒绝。TAU期间收不到网络寻呼
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLTE_FastSpecSearch(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    VOS_UINT32                                              ulIsPlmnSupportDam;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrPlmn;
    /* Added by c00318887 for 移植T3402 , 2015-6-23, begin */
    VOS_UINT8                                               ucHighRatBgProc;

    ucHighRatBgProc = NAS_MMC_IsHighPrioRatHplmnSearch_BgPlmnSearch();
    /* Added by c00318887 for 移植T3402 , 2015-6-23, end*/

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

    /* Added by c00318887 for 移植T3402 , 2015-6-23, begin */
    /* nv已经设置不需要ENABLE LTE并且是高优先RAT背景搜时，不ENABLE LTE */
    if ( (NAS_MML_HIGH_PRIO_RAT_BG_SEARCH_PROC_LTE_NOT_ENABLE_LTE == NAS_MML_GetHighPrioRatBgEnableLteFlag())
      && (VOS_TRUE == ucHighRatBgProc))
    {
        return VOS_FALSE;
    }    
    /* Added by c00318887 for 移植T3402 , 2015-6-23, end */

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

/*****************************************************************************
 函 数 名  : NAS_MMC_SendEnableLTE_FastSpecSearch
 功能描述  : 通知GU AS进行enable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年02月14日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年06月12日
   作    者   : b00269685
   修改内容   : 若是因为禁止LTE漫游而没有enable LTE，也需要停止定时器，并且更新disable LTE能力标记
 3.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改

*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : NAS_MMC_ProcNoRf_BgPlmnSelection
 功能描述  : 背景搜状态机中有no rf处理
 输入参数  : 接入技术
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年06月27日
   作    者   : b00269685
   修改内容   : DSDS III新增函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccSysInfo_BgPlmnSearch
 功能描述  : BG搜状态机中给MMA发送系统消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  高优先级RAT的HPLMN搜索
             VOS_FALSE 非高优先级RAT的HPLMN搜索
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月7日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI 新增

*****************************************************************************/
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
