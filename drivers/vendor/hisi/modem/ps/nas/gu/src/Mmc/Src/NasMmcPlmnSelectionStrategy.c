/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcPlmnSelectionStrategy.c
  版 本 号   : 初稿
  作    者   : sunxibo /46746
  生成日期   : 2011年07月04日
  最近修改   :
  功能描述   : NAS 层状态机PlmnSelection的搜网策略文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年07月04日
    作    者   : sunxibo /46746
    修改内容   : Added for V7R1 phase II

******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "stdlib.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcFsmPlmnSelection.h"
#include "NasMmlLib.h"
#include "NasComm.h"
#include "NasMmcCtx.h"
#include "NasMmcSndOm.h"
#include "NasMmcComFunc.h"
#include "NasMmcProcNvim.h"
#include "NasMmcFsmBgPlmnSearchTbl.h"

#include "MmaAppLocal.h"
#include "TafMmaNetworkNameTbl.h"
#include "NasMmcSndLmm.h"

#include "NasMmcFsmMainTbl.h"
#include "NasUsimmApi.h"

#include "NasMmlCtx.h"
/* Added by c00318887 for 移植T3402 , 2015-6-24, begin */
#include "NasMmcFsmBgPlmnSearch.h"
/* Added by c00318887 for 移植T3402 , 2015-6-24, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_PLMN_SELECTION_STRATEGY_C

/* 各种搜网场景对应的搜网列表初始化函数，在搜网状态机初始化时使用 */
NAS_MMC_PLMN_SELECTION_LIST_INIT_TBL_STRU         g_astNasMmcPlmnSearchInitTbl[] =
{
    {NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON,                   NAS_MMC_InitPlmnSelectionList_SwitchOn},
    {NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST,                   NAS_MMC_InitPlmnSelectionList_AreaLost},
    {NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET,                  NAS_MMC_InitPlmnSelectionList_SyscfgSet},
    {NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED,     NAS_MMC_InitPlmnSelectionList_AvailTimerExpire},
    {NAS_MMC_PLMN_SEARCH_SCENE_USER_LIST,                   NAS_MMC_InitPlmnSelectionList_UserList},
    {NAS_MMC_PLMN_SEARCH_SCENE_REG_REJ_PLMN_SEARCH,         NAS_MMC_InitPlmnSelectionList_RegRejPlmnSearch},
    {NAS_MMC_PLMN_SEARCH_SCENE_REG_REJ_CURRENT_PLMN_SEARCH, NAS_MMC_InitPlmnSelectionList_RegRejCurPlmnSearch},
    {NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,       NAS_MMC_InitPlmnSelectionList_UserSpecPlmnSearch},
    {NAS_MMC_PLMN_SEARCH_SCENE_MANUAL_CHANGE_AUTO_MODE,     NAS_MMC_InitPlmnSelectionList_ManualChangeAutoMode},
    {NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,       NAS_MMC_InitPlmnSelectionList_HighPrioPlmnSearch},
    {NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE,                 NAS_MMC_InitPlmnSelectionList_DisableLte},
    {NAS_MMC_PLMN_SEARCH_SCENE_INTER_SYS_OOS,               NAS_MMC_InitPlmnSelectionList_InterSysOos},
#if (FEATURE_ON == FEATURE_LTE)
    {NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ,       NAS_MMC_InitPlmnSelectionListCsfbServiceRej},
#endif
    {NAS_MMC_PLMN_SEARCH_SCENE_USER_AUTO_RESEL,             NAS_MMC_InitPlmnSelectionList_UserAutoResel},

    {NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_NCELL_SEARCH, NAS_MMC_InitPlmnSelectionList_AvailTimerExpireNcellSearch},

    {NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE,                   NAS_MMC_InitPlmnSelectionListRfEnable},

    {NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_RAT_HPLMN_SEARCH,  NAS_MMC_InitPlmnSelectionList_HighPrioRatHplmnSearch},
    /* Added by s00246516 for L-C互操作项目, 2014-02-11, Begin */
    {NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL,                   NAS_MMC_InitPlmnSelectionList_RegNCell},
    {NAS_MMC_PLMN_SEARCH_SCENE_REG_HPLMN,                   NAS_MMC_InitPlmnSelectionList_RegHPlmn},
    {NAS_MMC_PLMN_SEARCH_SCENE_REG_PREF_PLMN,               NAS_MMC_InitPlmnSelectionList_RegPrefPlmn},
    {NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN,                NAS_MMC_InitPlmnSelectionList_AvailTimerExpire},
    /* Added by s00246516 for L-C互操作项目, 2014-02-11, End */


    {NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST_ROAMING_CFG,       NAS_MMC_InitPlmnSelectionList_Roaming_AreaLost},

    {NAS_MMC_PLMN_SEARCH_SCENE_SRV_TRIG_PLMN_SEARCH,        NAS_MMC_InitPlmnSelectionListRfEnable},

#if (FEATURE_ON == FEATURE_LTE)
    {NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH,      NAS_MMC_InitPlmnSelectionList_EnableLte},
    {NAS_MMC_PLMN_SEARCH_SCENE_CSFB_ABORT,                  NAS_MMC_InitPlmnSelectionList_CsfbAbort},
#endif

#if (FEATURE_ON == FEATURE_LTE)
    {NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_LTE_PLMN_SEARCH,      NAS_MMC_InitPlmnSelectionList_HighPrioLtePlmnSearch},
#endif

    {NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH,     NAS_MMC_InitPlmnSelectionList_AvailTimerExpire},

    {NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH,    NAS_MMC_InitPlmnSelectionList_AvailTimerExpire},

    {NAS_MMC_PLMN_SEARCH_SCENE_CSFB_END,   NAS_MMC_InitPlmnSelectionList_CsfbEnd},

    {NAS_MMC_PLMN_SEARCH_SCENE_DPLMN_SET,  NAS_MMC_InitPlmnSelectionList_DplmnSet},
};

/* 需要先进行history搜网的搜网场景 */
VOS_UINT32 g_aulNasMmcNeedHistorySearchSceneTbl[] =
{
    NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST,
    NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED,
    NAS_MMC_PLMN_SEARCH_SCENE_REG_REJ_PLMN_SEARCH,
    NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ,
    NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE,
    NAS_MMC_PLMN_SEARCH_SCENE_SRV_TRIG_PLMN_SEARCH,
    NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH,
    NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH,
    NAS_MMC_PLMN_SEARCH_SCENE_CSFB_END,
};


/* 需要先进行pref band搜网的搜网场景 */
VOS_UINT32 g_aulNasMmcNeedPrefBandSearchSceneTbl[] =
{
    NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST,
    NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH,
};


/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : NAS_MMC_GetNeedHistorySearchSceneTblSize
 功能描述  : 获取需要进行history搜网的搜网场景列表个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : g_astNasMmcNeedHistorySearchSceneTbl个数
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年8月11日
    作    者   : z00161729
    修改内容   : DTS2015061609419：L下被拒搜网场景优化，先history搜再全频搜
*****************************************************************************/
VOS_UINT16 NAS_MMC_GetNeedHistorySearchSceneTblSize(VOS_VOID)
{
    VOS_UINT16                          usTblSize;

    usTblSize = sizeof(g_aulNasMmcNeedHistorySearchSceneTbl) / sizeof(g_aulNasMmcNeedHistorySearchSceneTbl[0]);

    return usTblSize;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNeedHistorySearchSceneTblAddr
 功能描述  : 获取需要进行history搜网的搜网场景列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : g_astNasMmcNeedHistorySearchSceneTbl地址
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年8月11日
    作    者   : z00161729
    修改内容   : DTS2015061609419：L下被拒搜网场景优化，先history搜再全频搜
*****************************************************************************/
VOS_UINT32 *NAS_MMC_GetNeedHistorySearchSceneTblAddr(VOS_VOID)
{
    return g_aulNasMmcNeedHistorySearchSceneTbl;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsSpecSearchSceneInNeedHistorySearchSceneTbl
 功能描述  : 判断指定搜网场景是否需要先history搜
 输入参数  : enSearchScene - 搜网场景
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 指定的搜网场景在需要先history搜网场景列表中
             VOS_FALSE - 指定的搜网场景不在需要先history搜网场景列表中
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年8月11日
    作    者   : z00161729
    修改内容   : DTS2015061609419：L下被拒搜网场景优化，先history搜再全频搜
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsSpecSearchSceneInNeedHistorySearchSceneTbl(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enSearchScene
)
{
    VOS_UINT16                          usTblSize;
    VOS_UINT32                          ulIndex;

    usTblSize = NAS_MMC_GetNeedHistorySearchSceneTblSize();

    for (ulIndex = 0; ulIndex < usTblSize; ulIndex++)
    {
        if (enSearchScene == g_aulNasMmcNeedHistorySearchSceneTbl[ulIndex])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 函 数 名  : NAS_MMC_GetMsccTriggerPlmnSrchTypeInClMode_PlmnSelection
 功能描述  : 获取CL模式下的搜网类型
 输入参数  : VOS_VOID
 输出参数  : NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32---CL模式下的搜网类型
 返 回 值  : VOS_TRUE----获取成功
             VOS_FALSE---获取失败
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年12月29日
    作    者   : w00176964
    修改内容   : CL_MUTIMODE_OPTIMIZE调整
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetMsccTriggerPlmnSrchTypeInClMode_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                   *penSrchType
)
{
    NAS_MMC_ENTRY_MSG_STRU                                 *pstEntryMsg           = VOS_NULL_PTR;
    MSCC_MMC_PLMN_SEARCH_REQ_STRU                          *pstMsccPlmnSrchReq    = VOS_NULL_PTR;

    /* 获取状态机的入口消息信息 */
    pstEntryMsg  = NAS_MMC_GetCurrEntryMsg();

    *penSrchType = NAS_MMC_PLMN_SEARCH_TYPE_SPEC;

    if (VOS_FALSE == NAS_MML_IsGULModeConfigured())
    {
        if (pstEntryMsg->ulEventType == NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SEARCH_REQ))
        {
            pstMsccPlmnSrchReq = (MSCC_MMC_PLMN_SEARCH_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

            if (NAS_MSCC_PIF_PLMN_SEARCH_HISTORY == pstMsccPlmnSrchReq->enSrchType)
            {
                *penSrchType = NAS_MMC_PLMN_SEARCH_TYPE_HISTORY;
            }
            else if (NAS_MSCC_PIF_PLMN_SEARCH_PERF_BAND == pstMsccPlmnSrchReq->enSrchType)
            {
                *penSrchType = NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND;
            }
            else
            {
                *penSrchType = NAS_MMC_PLMN_SEARCH_TYPE_SPEC;
            }

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


#endif

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNeedPrefBandSearchSceneTblSize
 功能描述  : 获取需要进行pref band搜网的搜网场景列表个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : g_astNasMmcNeedPrefBandSearchSceneTbl个数
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年10月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 NAS_MMC_GetNeedPrefBandSearchSceneTblSize(VOS_VOID)
{
    VOS_UINT16                          usTblSize;

    usTblSize = sizeof(g_aulNasMmcNeedPrefBandSearchSceneTbl) / sizeof(g_aulNasMmcNeedPrefBandSearchSceneTbl[0]);

    return usTblSize;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNeedPrefBandSearchSceneTblAddr
 功能描述  : 获取需要进行pref band搜网的搜网场景列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : g_astNasMmcNeedPrefBandSearchSceneTbl地址
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年10月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 *NAS_MMC_GetNeedPrefBandSearchSceneTblAddr(VOS_VOID)
{
    return g_aulNasMmcNeedPrefBandSearchSceneTbl;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsSpecSearchSceneInNeedPrefBandSearchSceneTbl
 功能描述  : 判断指定搜网场景是否需要先pref band搜
 输入参数  : enSearchScene - 搜网场景
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 指定的搜网场景在需要先pref band搜网场景列表中
             VOS_FALSE - 指定的搜网场景不在需要先pref band搜网场景列表中
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年10月13日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsSpecSearchSceneInNeedPrefBandSearchSceneTbl(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enSearchScene
)
{
    VOS_UINT16                          usTblSize;
    VOS_UINT32                          ulIndex;

    usTblSize = NAS_MMC_GetNeedPrefBandSearchSceneTblSize();

    for (ulIndex = 0; ulIndex < usTblSize; ulIndex++)
    {
        if (enSearchScene == g_aulNasMmcNeedPrefBandSearchSceneTbl[ulIndex])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildRatPrioList_AreaLost
 功能描述  : 丢网之后的搜网根据搜网策略配置更新接入技术顺序
 输入参数  : NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
 输出参数  : 无
 返 回 值  : NAS_MML_PLMN_RAT_PRIO_STRU*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_BuildRatPrioList_AreaLost(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstDestRatRrioList
)
{
    VOS_UINT32                                              i;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCurRatType;                                                  /* 网络的接入技术 */
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU   *pstNonOosCfg  = VOS_NULL_PTR;

    pstNonOosCfg   = NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg();
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    enCurRatType   = NAS_MML_GetCurrNetRatType();

    PS_MEM_CPY(pstDestRatRrioList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 如果不带PlmnList信息，和原有的处理一致，把当前模放在最后搜 */
    if (VOS_NULL_PTR == pstSearchedPlmnListInfo)
    {
        NAS_MML_SortSpecRatPrioLowest(enCurRatType, pstDestRatRrioList);
        return;
    }

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (pstSearchedPlmnListInfo[i].enRatType != enCurRatType)
        {
            continue;
        }

        /* 如果接入层上报丢网时已经进行过spec搜或pref band搜，根据NV配置不搜当前模或把当前模放在最后搜 */
        if ((VOS_TRUE == pstSearchedPlmnListInfo[i].stSearchedType.ucPrefBandSearchedFlg)
         || (VOS_TRUE == pstSearchedPlmnListInfo[i].stSearchedType.ucSpecSearchedFlg))
        {
            /* NV配置跳过当前模的spec搜或pref band搜时，把当前模从列表中删除 */
            if (NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_NONE == pstNonOosCfg->enSearchTypeAfterHistoryInAreaLostScene)
            {
                NAS_MML_DelSpecRatInPrioRatList(enCurRatType, pstDestRatRrioList);
            }
            /* NV配置不跳过当前模的spec搜或pref band搜时，把当前模放在最后搜 */
            else
            {
                NAS_MML_SortSpecRatPrioLowest(enCurRatType, pstDestRatRrioList);
            }

            return;
        }

        /* 如果接入层未进行任何搜索立即上报丢网，要最先搜当前模；
           如果接入层上报丢网时只进行过history搜，当前模先放在最前面，另有标志记录当前模已进行过history，history搜时会跳过
        */
        NAS_MML_SortSpecRatPrioHighest(enCurRatType, pstDestRatRrioList);
        break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_PlmnSearchListInit
 功能描述  : 搜网状态机启动时，搜网列表初始化
 输入参数  : enPlmnSearchScene    搜网场景
 输出参数  : pstPlmnSelectionList 搜网列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月28日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
 3.日    期   : 2014年6月17日
    作    者   : z00234330
    修改内容   : PCINT清理
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                          i;
    pNasMmcPlmnSelectionListInitFunc    pfunPlmnSearchInit;

    pfunPlmnSearchInit = VOS_NULL_PTR;

    /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */
    /* 根据场景在g_astNasMmcPlmnSearchInitTbl查找搜网列表初始化函数 */
    for (i = 0; i < (sizeof(g_astNasMmcPlmnSearchInitTbl)/sizeof(NAS_MMC_PLMN_SELECTION_LIST_INIT_TBL_STRU)); i++)
    /* Modified by z00234330 for PCLINT清理, 2014-06-24, end */
    {
        if (enPlmnSearchScene == g_astNasMmcPlmnSearchInitTbl[i].enPlmnSearchScene)
        {
            pfunPlmnSearchInit = g_astNasMmcPlmnSearchInitTbl[i].pfunPlmnSearchInit;
            break;
        }
    }

    /* 查找成功时调用初始化函数进行初始化 */
    if (VOS_NULL_PTR != pfunPlmnSearchInit)
    {
        PS_MEM_SET(pstPlmnSelectionListInfo, 0x0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));

        pfunPlmnSearchInit(pstPlmnSelectionListInfo, pstSearchedPlmnListInfo);
    }

    /* 用户列表搜网时,初始化完毕后还需要根据已搜索列表进行更新,
       因此此处暂不Log信息,待更新完毕后Log */
    if (NAS_MMC_PLMN_SEARCH_SCENE_USER_LIST != enPlmnSearchScene)
    {
        /* 可维可测，输出选网列表信息 */
        NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_SwitchOn
 功能描述  : 开机搜网列表初始化
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月28日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络

 3.日    期   : 2012年5月17日
   作    者   : zhoujun 40661
   修改内容   : 泰国AIS特性

 4.日    期   : 2014年10月8日
   作    者   : w00167002
   修改内容   : DTS2014090401463:在换卡时候，开机会将8275nv中的LAST RPLMN RAT设置为
                BUTT，后续在开机时候，如果换卡了，则按照LAST RPLMN RAT不生效处理。
                在移动卡上4g注册成功，换联通卡(在4G上注册成功),由于当前没有6f7E
                文件，获取L的RPLMN失败，开机时候会取W的RPLMN.所以开机时候，按照W
                LG顺序搜网。修改后，在换卡后，会按照LWG顺序搜网。
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_SwitchOn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_HPLMN_CFG_INFO_STRU        *pstHPlmnCfg     = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg     = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstGeoPlmn      = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stRPlmn;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enNvimLastRplmnRat;             /* NVIM中保存的上次关机前RPLMN的接入技术 */

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    PS_MEM_SET(&stRPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    /* 获取当前支持的接入技术及其优先级 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 获取HPLMN的配置信息 */
    pstHPlmnCfg    = NAS_MML_GetHplmnCfg();

    /* 获取RPLMN的配置信息 */
    pstRPlmnCfg    = NAS_MML_GetRplmnCfg();

    enNvimLastRplmnRat = pstRPlmnCfg->enLastRplmnRat;
    NAS_MMC_ReadNvimLastRplmnRat(&enNvimLastRplmnRat);

    pstGeoPlmn  = NAS_MMC_GetGeoPlmn();

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* Modified by z40661 for 泰国AIS特性 2012-05-17, begin */
        if ( VOS_TRUE == NAS_MMC_IsAisRoamingEffect())
        {
            /* 向选网列表中增加最需要进行搜网的网络*/
            NAS_MMC_AddAisRoamPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }

        /* Modified by z40661 for 泰国AIS特性 2012-05-17, end */

        /* 支持运营商P4的开机搜索Hplmn或者支持优先搜索Hplmn */
        if ((VOS_TRUE == NAS_MMC_IsHPlmnPrioSearch())
         || (VOS_TRUE == pstHPlmnCfg->ucHplmnSearchPowerOn))
        {
            /* 向选网列表中增加HPLMN或EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* 向选网列表中增加RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加UPLMN和OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }

        else if ( (VOS_TRUE                     == pstRPlmnCfg->ucLastRplmnRatFlg)
               && (NAS_MML_NET_RAT_TYPE_BUTT    != enNvimLastRplmnRat) ) /* last Rplmn rat激活 */
        {
            /* 向选网列表中增加RPLMN,将last Rplmn rat排在最前面 */
            NAS_MML_SortSpecRatPrioHighest(pstRPlmnCfg->enLastRplmnRat, &stPrioRatList);
            NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加HPLMN或EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* 向选网列表中增加UPLMN和OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* 向选网列表中增加RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加HPLMN或EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* 向选网列表中增加UPLMN和OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
    }
    else
    {
        /* 获取用户指定网络 */
        pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

        /* last Rplmn rat激活,且没有换卡，在换卡时候，LastRplmnRat为BUTT值 */
        if ( (VOS_TRUE                  == pstRPlmnCfg->ucLastRplmnRatFlg)
          && (NAS_MML_NET_RAT_TYPE_BUTT != enNvimLastRplmnRat) )
        {
            /* 向选网列表中增加用户指定PLMN,只增加last Rplmn rat指示的接入技术 */
            stPrioRatList.ucRatNum      = 1;
            stPrioRatList.aucRatPrio[0] = pstRPlmnCfg->enLastRplmnRat;
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }

        /* 向选网列表中增加用户指定PLMN */
        NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        (VOS_VOID)NAS_MMC_GetRPlmn_PlmnSelectionStrategy(pstRPlmnCfg->enLastRplmnRat, &stRPlmn);

        /* 用户指定网络与RPLMN相同时需要将EPLMN添加到选网列表 */
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stRPlmn,
                                                           &(pstUserSpecPlmn->stPlmnId)))
        {
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);
        }

        /* 支持R7开机搜索Hplmn */
        if (VOS_TRUE == pstHPlmnCfg->ucManualSearchHplmnFlg)
        {
            /* 向选网列表中增加HPLMN或EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
    }

    /* 更新是否存在RPLMN或HPLMN标志 */
    NAS_MMC_UpdateExistRplmnOrHplmnFlag_InitPlmnSelectionList(pstGeoPlmn);

    /* 漫游排序 NV打开并且MCC与RPLMN/HPLMN不同时，把漫游网络排在列表的前面 */
    if (VOS_TRUE == NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON,
                                                                                  pstGeoPlmn))
    {
        /* 对选网列表进行排序 */
        NAS_MMC_SortRoamPlmnSelectionList_InitPlmnSelectionList(pstGeoPlmn, pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_AreaLost
 功能描述  : 出服务区搜网列表初始化
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月28日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
 3.日    期   : 2012年11月09日
   作    者   : l65478
   修改内容   : DTS2012103005174, PS成功,CS失败手动模式搜网时不能加RPLMN
 4.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : User_Exp_Improve修改
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_AreaLost(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;
    VOS_UINT32                          ulIsRoam;
    VOS_UINT32                          ulIsSortPlmnSearchList;
#endif

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* 获取当前支持的接入技术及其优先级 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

#if (FEATURE_ON == FEATURE_LTE)
    ulIsSortPlmnSearchList      = VOS_FALSE;
    enNetRatType                = NAS_MML_GetCurrNetRatType();
    ulIsRoam                    = NAS_MML_IsLastCampedPlmnIdRoam();

    if ((VOS_TRUE == NAS_MML_IsNeedSortRatPrioForLteOos2GPrefPlmnSel(&stPrioRatList))
     && (NAS_MML_NET_RAT_TYPE_LTE == enNetRatType)
     && (VOS_FALSE == ulIsRoam))
    {
        ulIsSortPlmnSearchList = VOS_TRUE;
    }
#endif

    /* 根据NV配置的搜网策略调整搜网的顺序 */
    NAS_MMC_BuildRatPrioList_AreaLost(pstSearchedPlmnListInfo, &stPrioRatList);

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 支持优先搜索Hplmn */
        if (VOS_TRUE == NAS_MMC_IsHPlmnPrioSearch())
        {
            /* 向选网列表中增加HPLMN或EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* 接入技术顺序的调整放在前面 */

            /* 向选网列表中增加RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);


        }
        else
        {
            /* 接入技术顺序的调整放在前面 */

            /* 向选网列表中增加RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加HPLMN或EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        if(VOS_TRUE == ulIsSortPlmnSearchList)
        {
            NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                    pstPlmnSelectionListInfo);
            NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE,
                                                    pstPlmnSelectionListInfo);
        }
        /* 向选网列表中增加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* 用户指定网络注册成功过,可以搜索RPLMN和EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {

            /* 接入技术顺序的调整放在前面 */

            /* 向选网列表中增加RPLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加用户指定网络 */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* 获取用户指定网络 */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* 接入技术顺序的调整放在前面 */

            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }
        if(VOS_TRUE == ulIsSortPlmnSearchList)
        {
            NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                    pstPlmnSelectionListInfo);
            NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE,
                                                    pstPlmnSelectionListInfo);
        }
    }

    /* 出服务区搜网时，如果当前存在CSFB业务标志，选网列表构造完成之后，需要将LTE所有网络优先级放在GSM和WCDMA之后 */
    if (VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE, pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_Roaming_AreaLost
 功能描述  : OOS出服务区后搜网列表初始化
 输入参数  : pstPlmnListSearched, 接入层上报的列表
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年02月18日
   作    者   : t00173447
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_Roaming_AreaLost(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;

    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* 获取当前支持的接入技术及其优先级 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /*仅搜当前接入技术*/
        PS_MEM_SET(&stPrioRatList, 0x0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
        stPrioRatList.ucRatNum = 1;
        stPrioRatList.aucRatPrio[0] = NAS_MML_GetCurrNetRatType();
        /* 向选网列表中增加RPLMN,仅搜当前接入技术 */
        NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

        /* 向选网列表中增加EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* 向选网列表中增加HPLMN或EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* 向选网列表中增加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* 用户指定网络注册成功过,可以搜索RPLMN和EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* 向选网列表中增加RPLMN,当前接入技术排在最后 */
            NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加用户指定网络 */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* 获取用户指定网络 */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* 向选网列表中增加用户指定PLMN,当前接入技术排在最后 */
            NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }

    }
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_OosAreaLost
 功能描述  : OOS出服务区后搜网列表初始化
 输入参数  : pstPlmnListSearched, 接入层上报的列表
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年11月26日
   作    者   : w00166186
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
 3.日    期   : 2012年11月09日
   作    者   : l65478
   修改内容   : DTS2012103005174, PS成功,CS失败手动模式搜网时不能加RPLMN
 4.日    期   : 2015年8月25日
   作    者   : l00289540
   修改内容   : User_Exp_Improve 修改
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_InterSysOos(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* 获取当前支持的接入技术及其优先级 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 将OOS流程结束后接入层上报的PLMN加入搜网列表 */
    NAS_MMC_AddSearchedPlmnListInfoInPlmnSelectionList(pstPlmnSelectionListInfo, pstSearchedPlmnListInfo);

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 向选网列表中增加RPLMN,当前接入技术排在最后 */
        NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);
        NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

        /* 向选网列表中增加EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* 向选网列表中增加HPLMN或EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* 向选网列表中增加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* 用户指定网络注册成功过,可以搜索RPLMN和EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* 向选网列表中增加RPLMN,当前接入技术排在最后 */
            NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加用户指定网络 */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* 获取用户指定网络 */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* 向选网列表中增加用户指定PLMN,当前接入技术排在最后 */
            NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }

    }


    /* 如果当前存在CSFB业务标志，选网列表构造完成之后，需要将LTE所有网络优先级放在GSM和WCDMA之后 */
    if (VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE, pstPlmnSelectionListInfo);
    }

    /* 可维可测，输出选网列表信息 */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_UserAutoResel
 功能描述  : 用户重选时,搜网列表初始化，按Ts23.122 ch4.4.3.2.1将当前Plmn放在最低位置
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2012年5月15日
    作    者   : l00130025
    修改内容   : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton功能支持

  2.日    期   : 2014年9月3日
    作    者   : w00167002
    修改内容   : DTS2014090204636:在HOME PLMN上驻留时，发起重选，把当前的HOMPE PLMN
                给删除了。在单模时，如仅有HPLMN,则可能触发搜FFFFF网络，增加搜网时间。
 *****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_UserAutoResel(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    /* 向选网列表中增加HPLMN或EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    /* 向选网列表中增加UPLMN和OPLMN */
    NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);


    /* 驻留在非EHPLMN时，则将当前网络排在最后 */
    if (VOS_TRUE == NAS_MMC_IsRoam())
    {
        /* 删除当前驻留的网络 */
        NAS_MMC_DelSpecPlmnWithRatInPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             pstPlmnSelectionListInfo);
    }

    /* 可维可测，输出选网列表信息 */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPrioRat_SyscfgSet
 功能描述  : Syscfg设置触发搜网时搜网列表初始化时，获取当前最高优先级的接入技术
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8 最高优先级的接入技术
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月11日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期   : 2014年7月17日
   作    者   : w00242748
   修改内容   : DTS2014063003419:SYSCFG触发高优先级接入技术搜网增加NV控制

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetPrioRat_SyscfgSet(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg     = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;

    enRatType        = NAS_MML_NET_RAT_TYPE_BUTT;
    pstRPlmnCfg      = NAS_MML_GetRplmnCfg();
    enCurrNetRatType = NAS_MML_GetCurrNetRatType();
    pstPrioRatList   = NAS_MML_GetMsPrioRatList();

    /* SVLTE特性开的话，当前驻留的接入技术优先 */
    if ( (VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
      && (NAS_MML_NET_RAT_TYPE_BUTT != enCurrNetRatType))
    {
        enRatType = enCurrNetRatType;
    }
    else
    {
        /* SVLTE特性关闭，按原有逻辑处理 */
        if ( VOS_TRUE == NAS_MML_GetSyscfgTriHighRatSrchFlg() )
        {
            enRatType = pstPrioRatList->aucRatPrio[0];
        }
        else if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
        {
            enRatType = pstRPlmnCfg->enLastRplmnRat;
        }
        else
        {
            ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

            if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
             && (VOS_TRUE == ulEplmnValidFlg))
            {
                enRatType = pstRPlmnCfg->enLastRplmnRat;
            }
            else
            {
                pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();
                enRatType       = pstUserSpecPlmn->enRat;
            }
        }
    }

    return enRatType;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_SyscfgSet
 功能描述  : Syscfg设置触发搜网时搜网列表初始化
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月28日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
 3.日    期   : 2012年11月09日
   作    者   : l65478
   修改内容   : DTS2012103005174, PS成功,CS失败手动模式搜网时不能加RPLMN
 4.日    期   : 2015年8月25日
   作    者   : l00289540
   修改内容   : User_Exp_Improve 修改
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_SyscfgSet(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr      = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstGeoPlmn      = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pstGeoPlmn  = NAS_MMC_GetGeoPlmn();

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));


    enRatType = NAS_MMC_GetPrioRat_SyscfgSet();

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 向选网列表中增加RPLMN,将last Rplmn rat排在最前面 */
        NAS_MML_SortSpecRatPrioHighest(enRatType, &stPrioRatList);
        NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

        /* 向选网列表中增加EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* 向选网列表中增加HPLMN或EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* 向选网列表中增加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* 用户指定网络注册成功过,可以搜索RPLMN和EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* 向选网列表中增加RPLMN,将last Rplmn rat排在最前面 */
            NAS_MML_SortSpecRatPrioHighest(enRatType, &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加用户指定网络 */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* 获取用户指定网络 */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* 向选网列表中增加用户指定PLMN,将用户指定的rat排在最前面 */
            NAS_MML_SortSpecRatPrioHighest(enRatType, &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }
    }


    /* 更新是否存在RPLMN或HPLMN标志 */
    NAS_MMC_UpdateExistRplmnOrHplmnFlag_InitPlmnSelectionList(pstGeoPlmn);

    /* 漫游排序 NV打开并且MCC与RPLMN/HPLMN不同时，把漫游网络排在列表的前面 */
    if (VOS_TRUE == NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET,
                                                                                  pstGeoPlmn))
    {
        /* 对选网列表进行排序 */
        NAS_MMC_SortRoamPlmnSelectionList_InitPlmnSelectionList(pstGeoPlmn, pstPlmnSelectionListInfo);
    }


    /* 如果当前存在CSFB业务标志，选网列表构造完成之后，需要将LTE所有网络优先级放在GSM和WCDMA之后 */
    if (VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE, pstPlmnSelectionListInfo);
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildNcellPlmnSelectionPlmnList
 功能描述  : 构造NCELL 选网列表
 输入参数  : enPlmnType:网络类型
             ucChangePrioRatOrder :是否按照PrioRat 顺序

 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年5月27日
   作    者   :  x00203213
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_BuildNcellPlmnSelectionPlmnList(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    VOS_UINT8                                               ucChangePrioRatOrder,
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT8                                               ucRatNum;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList = VOS_NULL_PTR;
    VOS_UINT32                                              ulRatCnt;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRatType;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;

    PS_MEM_CPY(&(stPlmnInfo.stPlmnId), pstPlmnId, sizeof(NAS_MML_PLMN_ID_STRU));
    stPlmnInfo.enPlmnType = enPlmnType;

    /* 获取优先级列表 */
    pstRatPrioList     = NAS_MML_GetMsPrioRatList();

    for (ulRatCnt =0; ulRatCnt< pstRatPrioList->ucRatNum; ulRatCnt++)
    {
        ucRatNum                = 0x0;
        /* 初始化上报的接入技术列表 */
        if (VOS_FALSE == ucChangePrioRatOrder)
        {
            enRatType        = pstRatPrioList->aucRatPrio[ulRatCnt];
        }

        /*反向构建搜网列表*/
        else
        {
            enRatType        = pstRatPrioList->aucRatPrio[pstRatPrioList->ucRatNum -1 - ulRatCnt];
        }


        if (NAS_MML_NET_RAT_TYPE_LTE == enRatType)
        {
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_LTE;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
            ucRatNum++;
        }

        if (NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
        {
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_WCDMA;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
            ucRatNum++;
        }
        stPlmnInfo.ucRatNum = ucRatNum;

        /* 数组剩余位置赋值为无效值 */
        for (; ucRatNum < NAS_MML_MAX_RAT_NUM; ucRatNum++)
        {
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_BUTT;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_BUTT;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_BUTT;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        }

        /* 添加到搜网列表 */
        NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);

    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_AvailTimerExpireNcellSearch
 功能描述  : Available Timer超时触发NCELL 搜网时搜网列表初始化
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月28日
    作    者   : x00203213
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_AvailTimerExpireNcellSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU        *pstEHPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          *pstUserSpecPlmn   = VOS_NULL_PTR;
    VOS_UINT8                            ucNeedChangeRatOrder;

    /* 判断是否需要更改顺序*/
    ucNeedChangeRatOrder = NAS_MMC_IsNeedChangeNcellSearchRatOrder();

    pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();
    pstEHPlmnInfo   = NAS_MML_GetSimEhplmnList();


    /* 自动搜网模式 添加 HPLMN 到列表中*/
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_MMC_BuildNcellPlmnSelectionPlmnList(NAS_MMC_PLMN_TYPE_HPLMN,
                                       ucNeedChangeRatOrder,
                                       &(pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId),
                                       pstPlmnSelectionListInfo);

    }

    else
    {
        NAS_MMC_BuildNcellPlmnSelectionPlmnList(NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                       ucNeedChangeRatOrder,
                                       &(pstUserSpecPlmn->stPlmnId),
                                       pstPlmnSelectionListInfo);
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_AvailTimerExpire
 功能描述  : Available Timer超时触发搜网时搜网列表初始化
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月28日
    作    者   : s46746
    修改内容   : 新生成函数
  2.日    期   : 2011年12月31日
    作    者   : w00166186
    修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
  3.日    期   : 2012年11月09日
    作    者   : l65478
    修改内容   : DTS2012103005174, PS成功,CS失败手动模式搜网时不能加RPLMN
  4.日    期   : 2015年8月25日
   作    者   : l00289540
   修改内容   : User_Exp_Improve 修改
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_AvailTimerExpire(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 支持优先搜索Hplmn */
        if (VOS_TRUE == NAS_MMC_IsHPlmnPrioSearch())
        {
            /* 向选网列表中增加HPLMN或EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* 向选网列表中增加RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(pstPrioRatList, pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加UPLMN和OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* 向选网列表中增加RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(pstPrioRatList, pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加HPLMN或EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* 向选网列表中增加UPLMN和OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
    }
    else
    {
        /* 用户指定网络注册成功过,可以搜索RPLMN和EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* 向选网列表中增加RPLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       pstPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加用户指定网络 */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* 向选网列表中增加用户指定网络 */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }

    }

    /* 如果当前存在CSFB业务标志，选网列表构造完成之后，需要将LTE所有网络优先级放在GSM和WCDMA之后 */
    if (VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE, pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_UserList
 功能描述  : 用户列表搜网结束后触发搜网时搜网列表初始化
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月28日
   作    者   : s46746
   修改内容   : 新生成函数

 2.日    期   : 2011年10月20日
   作    者   : w00167002
   修改内容   : 用户列表搜按照上一个RPlmn优先顺序进行搜索
 3.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
 4.日    期   : 2012年6月4日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL BG搜网修改
 5.日    期   : 2012年11月09日
   作    者   : l65478
   修改内容   : DTS2012103005174, PS成功,CS失败手动模式搜网时不能加RPLMN
 6.日    期   : 2014年2月20日
   作    者   : z00161729
   修改内容   : DTS2014022100125:单待驻留g的网络，切双待后tl无网络限制驻留g的网络，
               available超时做list搜网构造搜网列表把last rplmn rat排在最前面
               导致g排在第一个无法回l或tds的网络
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_UserList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;

    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg     = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;

    VOS_UINT8                           ucPsAttachAllowFlg;
    VOS_UINT8                           ucCsAttachAllowFlg;

    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pstRPlmnCfg    = NAS_MML_GetRplmnCfg();

    /* 向选网列表中增加RPLMN,将last Rplmn rat排在最前面 */
    NAS_MML_SortSpecRatPrioHighest(pstRPlmnCfg->enLastRplmnRat, &stPrioRatList);

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 支持优先搜索Hplmn */
        if (VOS_TRUE == NAS_MMC_IsHPlmnPrioSearch())
        {
            /* 向选网列表中增加HPLMN或EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* 向选网列表中增加RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(pstPrioRatList, pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加UPLMN和OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {

            /* 向选网列表中增加RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加HPLMN或EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* 向选网列表中增加UPLMN和OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
    }
    else
    {
        /* 用户指定网络注册成功过,可以搜索RPLMN和EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {

            /* 向选网列表中增加RPLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加用户指定网络 */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* 向选网列表中增加用户指定网络 */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }

    }

    /* 对搜网列表进行排序，svlte 双待模式把g的接入技术放到列表最后,否则存在找不回t或l网络的问题 */
    ucPsAttachAllowFlg = NAS_MML_GetPsAttachAllowFlg();
    ucCsAttachAllowFlg = NAS_MML_GetCsAttachAllowFlg();

    if ((VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
     && (VOS_FALSE == ucPsAttachAllowFlg)
     && (VOS_FALSE == ucCsAttachAllowFlg))
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_GSM,
                                                pstPlmnSelectionListInfo);
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_RegRejPlmnSearch
 功能描述  : 注册被拒触发搜网时搜网列表初始化
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月28日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : W00166186
   修改内容   : DTS2011082902017,ON PLMN注册被拒，搜网状态机重复搜网
 3.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : User_Exp_Improve修改
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_RegRejPlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU            stPrioRatList;
    VOS_UINT8                             ucKeepSrchHplmnFlg;

    ucKeepSrchHplmnFlg = NAS_MMC_IsNeedSrchCurrCampHpmnRejByCause13();

    if (VOS_TRUE == ucKeepSrchHplmnFlg)
    {
        PS_MEM_SET(&stPrioRatList, 0x00, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
        stPrioRatList.ucRatNum = 1;
        stPrioRatList.aucRatPrio[0] = NAS_MML_GetCurrNetRatType();

        NAS_MMC_AddSpecPlmnInPlmnSelectionList(NAS_MML_GetCurrCampPlmnId(),
                                            NAS_MMC_PLMN_TYPE_HPLMN,
                                            &stPrioRatList,
                                            pstPlmnSelectionListInfo);
    }

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 向选网列表中增加HPLMN或EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* 向选网列表中增加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        if (VOS_FALSE == ucKeepSrchHplmnFlg)
        {
            /* 删除当前注册被拒的网络 */
            NAS_MMC_DelSpecPlmnWithRatInPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                                 NAS_MML_GetCurrNetRatType(),
                                                 pstPlmnSelectionListInfo);
        }
    }
    else
    {
        /* 向选网列表中增加用户指定网络 */
        NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }

    /* 如果当前存在CSFB业务标志，选网列表构造完成之后，需要将LTE所有网络优先级放在GSM和WCDMA之后 */
    if (VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE, pstPlmnSelectionListInfo);
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_DisableLte
 功能描述  : Disable LTE触发搜网时搜网列表初始化
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年11月1日
   作    者   : w00176964
   修改内容   : 新生成函数
  2.日    期   : 2012年6月1日
    作    者   : l00171473
    修改内容   : DTS2012053003930, Disable Lte时需要搜RPLMN
  3.日    期   : 2012年11月09日
    作    者   : l65478
    修改内容   : DTS2012103005174, PS成功,CS失败手动模式搜网时不能加RPLMN
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_DisableLte(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;
    VOS_UINT32                                              ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU                              *pEplmnAddr  = VOS_NULL_PTR;

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {

        /* 向选网列表中增加 RPLMN */
        NAS_MMC_AddRPlmnInPlmnSelectionList(pstPrioRatList, pstPlmnSelectionListInfo);

        /* 向选网列表中增加 EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);


        /* 向选网列表中增加HPLMN或EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* 向选网列表中增加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {

        /* 用户指定网络注册成功过,可以搜索RPLMN和EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* 向选网列表中增加 RPLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       pstPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* 向选网列表中增加 EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);
        }


        /* 向选网列表中增加用户指定网络 */
        NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_RegRejCurPlmnSearch
 功能描述  : 注册被拒触发搜当前网络时搜网列表初始化
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月28日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:更改比较的先后顺序，认为当前驻留的网络类型
                为BCCH的。
 3.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
 4.日    期   : 2012年11月09日
   作    者   : l65478
   修改内容   : DTS2012103005174, PS成功,CS失败手动模式搜网时不能加RPLMN
 5.日    期   : 2015年8月25日
   作    者   : l00289540
   修改内容   : User_Exp_Improve 修改
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_RegRejCurPlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enPlmnType;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnList = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pstPlmnId      = NAS_MML_GetCurrCampPlmnId();
    pstEquPlmnList = NAS_MML_GetEquPlmnList();

    /* 添加的Plmn的类型默认为AvailPlmn */
    enPlmnType = NAS_MMC_PLMN_TYPE_AVAIL_PLMN;


    /* Rplmn与 EplmnList[0]相同时，添加为Rplmn类型 */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &(pstEquPlmnList->astEquPlmnAddr[0]) ))
    {
        enPlmnType = NAS_MMC_PLMN_TYPE_RPLMN;
    }


    /* 向选网列表中增加当前网络,当前接入技术放在最前面 */
    NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);

    NAS_MMC_AddSpecPlmnInPlmnSelectionList(pstPlmnId,
                                           enPlmnType,
                                           &stPrioRatList,
                                           pstPlmnSelectionListInfo);

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 向选网列表中增加EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* 向选网列表中增加HPLMN或EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* 向选网列表中增加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* 用户指定网络注册成功过,可以搜索RPLMN和EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);
        }

        /* 向选网列表中增加用户指定网络 */
        NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }

    /* 如果当前存在CSFB业务标志，选网列表构造完成之后，需要将LTE所有网络优先级放在GSM和WCDMA之后 */
    if (VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE, pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_UserSpecPlmnSearch
 功能描述  : 用户指定搜网时列表初始化
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月28日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_UserSpecPlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stRPlmn;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg     = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    PS_MEM_SET(&stRPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

    /* 获取RPLMN的配置信息 */
    pstRPlmnCfg    = NAS_MML_GetRplmnCfg();

    /* 向选网列表中增加用户指定网络,用户指定接入技术放在最前面 */
    NAS_MML_SortSpecRatPrioHighest(pstUserSpecPlmn->enRat, &stPrioRatList);
    NAS_MMC_AddSpecPlmnInPlmnSelectionList(&pstUserSpecPlmn->stPlmnId,
                                           NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                           &stPrioRatList,
                                           pstPlmnSelectionListInfo);

    (VOS_VOID)NAS_MMC_GetRPlmn_PlmnSelectionStrategy(pstRPlmnCfg->enLastRplmnRat, &stRPlmn);

    /* 用户指定网络与RPLMN相同时需要将EPLMN添加到选网列表 */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stRPlmn,
                                                       &(pstUserSpecPlmn->stPlmnId)))
    {
        NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_ManualChangeAutoMode
 功能描述  : 手动搜网模式修改为自动模式触发搜网时搜网列表初始化
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月28日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_ManualChangeAutoMode(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList   = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserReselPlmn = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 自动修改为手动时提供正常服务的网络 */
    pstUserReselPlmn = NAS_MMC_GetUserReselPlmnId();

    /* 自动修改为手动时保存的提供正常服务网络的接入技术放在最前面 */
    NAS_MML_SortSpecRatPrioHighest(pstUserReselPlmn->enRat, &stPrioRatList);
    NAS_MMC_AddSpecPlmnInPlmnSelectionList(&pstUserReselPlmn->stPlmnId,
                                           NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                           &stPrioRatList,
                                           pstPlmnSelectionListInfo);

    /* 向选网列表中增加EPLMN */
    NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

    /* 向选网列表中增加HPLMN或EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    /* 向选网列表中增加UPLMN和OPLMN */
    NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_CSFB_SERVICE_REJ
 功能描述  : CSFB服务后搜网列表初始化
 输入参数  : pstPlmnListSearched, 接入层上报的列表
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年2月15日
   作    者   : h00202780
   修改内容   : 新生成函数
 2.日    期   : 2012年11月09日
   作    者   : l65478
   修改内容   : DTS2012103005174, PS成功,CS失败手动模式搜网时不能加RPLMN
 3.日    期   : 2014年4月8日
   作    者   : z00161729
   修改内容   : DTS2014040809442:csfb失败lmm 回复service result ind指示需要搜网，由于tds语音不完善，如果utranmode为tdd，
                构造搜网列表时需要将tds网络放到g的后面，增加呼叫成功率
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionListCsfbServiceRej(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* 获取当前支持的接入技术及其优先级 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 向选网列表中增加RPLMN */
        NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

        /* 向选网列表中增加EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* 向选网列表中增加HPLMN或EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* 向选网列表中增加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* 用户指定网络注册成功过,可以搜索RPLMN和EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* 向选网列表中增加RPLMN  */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加用户指定网络 */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* 获取用户指定网络 */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* 向选网列表中增加RPLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }

    }

    if (VOS_TRUE == NAS_MMC_IsNetRatSupportedTdscdma())
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                pstPlmnSelectionListInfo);
    }

    /* 对搜网列表进行排序，将L接入技术放到列表最后*/
    NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE,
                                                pstPlmnSelectionListInfo);
    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_EnableLte
 功能描述  : enable lte搜网列表初始化
 输入参数  : pstPlmnSelectionListInfo, 接入层上报的列表
 输出参数  : pstSearchedPlmnListInfo,列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_EnableLte(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* 获取当前支持的接入技术及其优先级 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 向选网列表中增加RPLMN,LTE接入技术排在最前 */
        NAS_MML_SortSpecRatPrioHighest(NAS_MML_NET_RAT_TYPE_LTE, &stPrioRatList);

        NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

        /* 向选网列表中增加EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* 向选网列表中增加HPLMN或EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* 向选网列表中增加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    }
    else
    {
        /* 用户指定网络注册成功过,可以搜索RPLMN和EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* 向选网列表中增加RPLMN,LTE接入技术排在最前 */
            NAS_MML_SortSpecRatPrioHighest(NAS_MML_NET_RAT_TYPE_LTE, &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加用户指定网络 */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* 获取用户指定网络 */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* 向选网列表中增加用户指定PLMN,LTE接入技术排在最前 */
            NAS_MML_SortSpecRatPrioHighest(NAS_MML_NET_RAT_TYPE_LTE, &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }
    }
    return;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_CsfbAbort
 功能描述  : enable lte搜网列表初始化
 输入参数  : pstPlmnSelectionListInfo, 接入层上报的列表
 输出参数  : pstSearchedPlmnListInfo,列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年5月7日
    作    者   : b00269685
    修改内容   : csfb搜网过程中挂电话触发的搜网
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_CsfbAbort(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* 获取当前支持的接入技术及其优先级 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 向选网列表中增加RPLMN,LTE接入技术排在最前 */
        NAS_MML_SortSpecRatPrioHighest(NAS_MML_NET_RAT_TYPE_LTE, &stPrioRatList);

        NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

        /* 向选网列表中增加EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* 向选网列表中增加HPLMN或EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* 向选网列表中增加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    }
    else
    {
        /* 用户指定网络注册成功过,可以搜索RPLMN和EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* 向选网列表中增加RPLMN,LTE接入技术排在最前 */
            NAS_MML_SortSpecRatPrioHighest(NAS_MML_NET_RAT_TYPE_LTE, &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加用户指定网络 */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* 获取用户指定网络 */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* 向选网列表中增加用户指定PLMN,LTE接入技术排在最前 */
            NAS_MML_SortSpecRatPrioHighest(NAS_MML_NET_RAT_TYPE_LTE, &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_CsfbEnd
 功能描述  : CSFB过程中收到Area lost触发搜网过程后，收到挂断业务通知进而触发搜网
 输入参数  : pstPlmnSelectionListInfo, 接入层上报的列表
 输出参数  : pstSearchedPlmnListInfo,列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : 新建
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_CsfbEnd(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* 自动搜网模式 */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_MMC_AddRPlmnInPlmnSelectionList(NAS_MML_GetMsPrioRatList(), pstPlmnSelectionListInfo);

        /* 向选网列表中增加EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* 向选网列表中增加HPLMN或EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* 向选网列表中增加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    }
    else
    {
        /* 用户指定网络注册成功过,可以搜索RPLMN和EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* 向选网列表中增加RPLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       NAS_MML_GetMsPrioRatList(),
                                       pstPlmnSelectionListInfo);

            /* 向选网列表中增加EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* 向选网列表中增加用户指定网络 */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* 获取用户指定网络 */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* 向选网列表中增加用户指定PLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   NAS_MML_GetMsPrioRatList(),
                                                   pstPlmnSelectionListInfo);
        }
    }

    return;
}

#endif



/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionListRfEnable
 功能描述  : 通知RF可用时候，进行选网列表构造
 输入参数  : pstPlmnListSearched, 接入层上报的列表
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年1月22日
   作    者   : w00167002
   修改内容   : SVLTE共天线项目，
            在引入搜网失败NO RF场景后，MMC需要修改如下两种场景的搜网：
            【1】 MMC在收到RRM发送的ID_RRM_PS_STATUS_IND消息时候，如果当前存在NO RF标记信息，则需触发选网；
            【2】 MMC在收到Available定时器超时消息时候，如果当前存在NO RF标记信息，则需触发选网；

            MMC的选网列表构造规则为:
            规则1： NO RF搜网失败时的选网列表有效，则继续按照当时的选网列表继续搜网，否则按规则2进行选网列表构造。
            规则2：按周期搜网定时器超时场景构造选网列表，但将收到NO RF失败时的接入技术作为第一个PLMN的最优先级接入技术。
                   如在W下搜网失败，则在选网列表中第一位置增加搜W的网络接入技术。
 2.日    期   : 2013年4月4日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:更改NO RF 相关变量名称
 3.日    期   : 2013年6月30日
   作    者   : w00176964
   修改内容   : DSDS GUNAS III项目:NO RF场景下,重新初始化高优先级搜网列表
 4.日    期   : 2015年5月21日
   作    者   : l00305157
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionListRfEnable(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stDestFirstPlmnRatInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNoRfPlmnRat;
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT8                                               ucExistNoRFRat;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList      = VOS_NULL_PTR;
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstRatSearcchInfo   = VOS_NULL_PTR;

    pstRatSearcchInfo   = NAS_MMC_GetSearchRatInfo_PlmnSelection();

    /* 变量初始化 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    enNoRfPlmnRat  = NAS_MML_GetNoRfRatType();

    ucExistNoRFRat = VOS_FALSE;
    PS_MEM_SET(&stDestFirstPlmnRatInfo, 0X00, sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

    /* 如果当前MMC中备份了选网列表，则恢复导入备份的选网列表 */
    if ( NAS_MMC_BACKUP_PLMN_SELECTION_LIST == NAS_MMC_GetPlmnSelectionListType() )
    {
        PS_MEM_CPY(pstPlmnSelectionListInfo, NAS_MMC_GetHighPrioPlmnList(), sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));

        /* 恢复NO RF 资源可用后,进行相关资源的恢复 */
        NAS_MMC_RestoreNoRfHistorySearchedRatInfo_PlmnSelection(pstRatSearcchInfo);

        /* NO RF场景下,如果当前是备份选网列表信息，则重新初始化为高优先级列表信息 */
        if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
        {
            NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                          VOS_NULL_PTR,
                                          NAS_MMC_GetHighPrioPlmnList());
        }

        return;
    }

    /* 否则按照周期搜网定时器超时构造搜网列表，但将NO RF时候的接入技术调整为第一优先级 */
    NAS_MMC_InitPlmnSelectionList_AvailTimerExpire(pstPlmnSelectionListInfo, pstSearchedPlmnListInfo);

    /* 异常保护，如果当前目标接入技术为BUTT,则不进行调整 */
    if ( NAS_MML_NET_RAT_TYPE_BUTT == enNoRfPlmnRat )
    {
        return;
    }

    /* 异常保护，如果当前网络已满了，则不进行构造 */
    if ( NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST == pstPlmnSelectionListInfo->usSearchPlmnNum )
    {
        return;
    }

    /* 当前的接入技术个数为1个，则不需要调整搜网列表 */
    if ( 1 == pstPrioRatList->ucRatNum)
    {
        return;
    }

    /* 在整个选网列表中查找目标接入技术的网络信息 */
    for ( i = 0 ; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++ )
    {
        for (j = 0; j < pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum; j++)
        {
            /* 找到目标项接入技术，则填充在第一位，总个数不需要增加 */
            if ( enNoRfPlmnRat == pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType )
            {
                PS_MEM_CPY(&stDestFirstPlmnRatInfo,
                           &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                           sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

                /* 将目标网络的接入技术设置为仅且一个 */
                stDestFirstPlmnRatInfo.ucRatNum = 1;
                PS_MEM_CPY(&(stDestFirstPlmnRatInfo.astPlmnRatInfo[0]),
                           &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j]),
                           sizeof(NAS_MMC_PLMN_RAT_INFO_STRU) );

                ucExistNoRFRat = VOS_TRUE;

                break;
            }
        }

        /* 找到了目标接入技术，则直接跳出 */
        if ( VOS_TRUE == ucExistNoRFRat )
        {
            break;
        }
    }

    /* 没找到目标接入技术，则构造一个对应的接入技术 */
    if ( VOS_FALSE == ucExistNoRFRat )
    {
        /* 如果找不到对应的接入技术网络信息，则主动构造一个目标接入技术网络 */
        PS_MEM_CPY(&stDestFirstPlmnRatInfo,
                   &(pstPlmnSelectionListInfo->astPlmnSelectionList[0]),
                   sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

        stDestFirstPlmnRatInfo.ucRatNum = 1;
        stDestFirstPlmnRatInfo.astPlmnRatInfo[0].enRatType      = enNoRfPlmnRat;
        stDestFirstPlmnRatInfo.astPlmnRatInfo[0].enNetStatus    = NAS_MMC_NET_STATUS_BUTT;
        stDestFirstPlmnRatInfo.astPlmnRatInfo[0].enQuality      = NAS_MMC_NET_QUALITY_BUTT;
        stDestFirstPlmnRatInfo.astPlmnRatInfo[0].ucReserve      = 0;
        stDestFirstPlmnRatInfo.astPlmnRatInfo[0].lRscp          = NAS_MML_UTRA_RSCP_UNVALID;
    }

    /* 将当前选网列表后移一位后，将目标接入技术网络加入选网列表 */
    (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[1]),
                &(pstPlmnSelectionListInfo->astPlmnSelectionList[0]),
                (pstPlmnSelectionListInfo->usSearchPlmnNum) * sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));


    PS_MEM_CPY(&(pstPlmnSelectionListInfo->astPlmnSelectionList[0]),
               &stDestFirstPlmnRatInfo,
               sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

    pstPlmnSelectionListInfo->usSearchPlmnNum++;

    return;
}


/* Added by s00246516 for L-C互操作项目, 2014-02-11, Begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_RegNCell
 功能描述  : 进行NCell注册时搜网列表初始化
 输入参数  : pstSearchedPlmnListInfo,已搜索到的网络信息
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月11日
   作    者   : s00246516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_RegNCell(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MMC_NCELL_SEARCH_INFO_STRU     *pstMmcNcellSearchInfo = VOS_NULL_PTR;

    pstMmcNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();

    /* 目前NCELL仅支持LTE接入技术 */
    stPrioRatList.ucRatNum      = 1;
    stPrioRatList.aucRatPrio[0] = NAS_MML_NET_RAT_TYPE_LTE;

    /* 向选网列表中增加NCELL信息中的PLMN ID */
    for (i = 0; i < pstMmcNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum; i ++)
    {
        NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstMmcNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr[0]),
                                   NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                   &stPrioRatList,
                                   pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_RegHPlmn
 功能描述  : 进行Home Plmn注册时搜网列表初始化
 输入参数  : pstSearchedPlmnListInfo,已搜索到的网络信息
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月11日
   作    者   : s00246516
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_RegHPlmn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    /* 向选网列表中增加HPLMN或EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_RegPrefPlmn
 功能描述  : 进行优选PLMN注册时搜网列表初始化
 输入参数  : pstSearchedPlmnListInfo,已搜索到的网络信息
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月11日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   : 2014年6月13日
   作    者   : b00269685
   修改内容   : 根据3gpp2,Pref网络不包含UPLMN
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_RegPrefPlmn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    /* 向选网列表中增加HPLMN或EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    if (VOS_FALSE == NAS_MML_Get3GPP2UplmnNotPrefFlg())
    {
        /* 向选网列表中增加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* 向选网列表中增加OPLMN */
        NAS_MMC_AddOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }

    return;
}
/* Added by s00246516 for L-C互操作项目, 2014-02-11, End */

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_HighPrioLtePlmnSearch
 功能描述  : 高优先级的LTE的搜网列表初始化
 输入参数  : pstPlmnListSearched, MSCC下发后转换后的PLMN列表
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年4月3日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_HighPrioLtePlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_ID_STRU                stTmpPlmnId;

    VOS_UINT32                                              ulHighPlmnIndex;
    VOS_UINT32                                              ulLowPlmnIndex;
    VOS_UINT8                                               ucRatIndex;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stPrioRatList;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRatType;

    /* 向选网列表中增加HPLMN或EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    if (VOS_FALSE == NAS_MML_Get3GPP2UplmnNotPrefFlg())
    {
        /* 向选网列表中增加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* 向选网列表中增加OPLMN */
        NAS_MMC_AddOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }

    /* 由于优选的LTE的PLMN已经搜索过一遍，因此这里需要使用搜到的优选
       PLMN列表刷新下PLMN状态，对于不存在的PLMN在高优先级搜索时
       直接跳过，提高搜索效率; */

    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        stTmpPlmnId = pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId;

        if (VOS_FALSE == NAS_MMC_IsPlmnIdInSearchedPlmnList(&stTmpPlmnId, pstSearchedPlmnListInfo))
        {
            /* 未查找到相同的优选PLMN,对于相同接入技术的PLMN(目前看这个接入技术必然为LTE),网络状
               态需要更新为搜过不存在,保证搜索时不搜索该类PLMN */
            NAS_MMC_UpdateRatNetStatusInPlmnRatInfo(pstSearchedPlmnListInfo->enRatType,
                                                    NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,
                                                    &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]));
        }
    }



    /* 将bsr时hsd背景搜搜到的plmn追加到plmn选网列表中(重复的不加) */

    PS_MEM_SET(&stPlmnInfo, 0x00, sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    for (ucRatIndex = 0; ucRatIndex < NAS_MML_MAX_RAT_NUM; ucRatIndex++)
    {
        enRatType = pstSearchedPlmnListInfo[ucRatIndex].enRatType;

        if (NAS_MML_NET_RAT_TYPE_BUTT == enRatType)
        {
            continue;
        }

        /* 对高信号质量遍历 */
        for (ulHighPlmnIndex = 0; ulHighPlmnIndex < pstSearchedPlmnListInfo[ucRatIndex].ulHighPlmnNum; ulHighPlmnIndex++)
        {
            stPlmnInfo.stPlmnId.ulMcc = pstSearchedPlmnListInfo[ucRatIndex].astHighPlmnList[ulHighPlmnIndex].ulMcc;
            stPlmnInfo.stPlmnId.ulMnc = pstSearchedPlmnListInfo[ucRatIndex].astHighPlmnList[ulHighPlmnIndex].ulMnc;

            /* 搜到的plmn不在现有的构建的搜网列表中，要追加 */
            if (VOS_FALSE == NAS_MMC_IsPlmnInSearchList(stPlmnInfo, pstPlmnSelectionListInfo))
            {
                NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_InitPlmnSelectionList_HighPrioLtePlmnSearch, high srched plmn is not in plmn selectionlist:",
                                    stPlmnInfo.stPlmnId.ulMcc, stPlmnInfo.stPlmnId.ulMnc);

                stPrioRatList.ucRatNum      = 1;
                stPrioRatList.aucRatPrio[0] = pstSearchedPlmnListInfo[ucRatIndex].enRatType;

                NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(stPlmnInfo.stPlmnId),
                                                        NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                        &stPrioRatList,
                                                        pstPlmnSelectionListInfo);


            }
        }

        /* 对低信号质量遍历 */
        for (ulLowPlmnIndex = 0; ulLowPlmnIndex < pstSearchedPlmnListInfo[ucRatIndex].ulLowPlmnNum; ulLowPlmnIndex++)
        {
            stPlmnInfo.stPlmnId.ulMcc = pstSearchedPlmnListInfo[ucRatIndex].astLowPlmnList[ulLowPlmnIndex].stPlmnId.ulMcc;
            stPlmnInfo.stPlmnId.ulMnc = pstSearchedPlmnListInfo[ucRatIndex].astLowPlmnList[ulLowPlmnIndex].stPlmnId.ulMnc;

            /* 搜到的plmn不在现有的构建的搜网列表中，要追加 */
            if (VOS_FALSE == NAS_MMC_IsPlmnInSearchList(stPlmnInfo, pstPlmnSelectionListInfo))
            {
                NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_InitPlmnSelectionList_HighPrioLtePlmnSearch, low srched plmn is not in plmn selectionlist:",
                                    stPlmnInfo.stPlmnId.ulMcc, stPlmnInfo.stPlmnId.ulMnc);

                stPrioRatList.ucRatNum      = 1;
                stPrioRatList.aucRatPrio[0] = pstSearchedPlmnListInfo[ucRatIndex].enRatType;

                NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(stPlmnInfo.stPlmnId),
                                                        NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                        &stPrioRatList,
                                                        pstPlmnSelectionListInfo);
            }
        }
    }

    /* 可维可测，输出选网列表信息 */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_DplmnSet
 功能描述  : 搜网场景为NAS_MMC_PLMN_SEARCH_SCENE_DPLMN_SET时，初始化选网列表
 输入参数  : NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
             NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月21日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_DplmnSet(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    /* 同开机搜网，有GEO信息时，使用AP配置下来的新的DPLMN列表构造搜网列表
       对于无GEO信息，搜RPLMN/HPLMN时，接入层报PLMN_INFO_IND需要打断，这时收到DPLMN SET的场景
       需要从RPLMN/HPLMN开始搜，再收到PLMN_INFO_IND需要打断，此时再使用AP配置下来的新的DPLMN列表 */

    NAS_MMC_InitPlmnSelectionList_SwitchOn(pstPlmnSelectionListInfo, pstSearchedPlmnListInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildPlmnSelectionPlmnInfo
 功能描述  : 构造选网列表中单个PLMN信息
 输入参数  : enPlmnType:网络类型
             usSimRat:支持的接入技术,按SIM卡存储的格式
             pstPlmnId:PLMN ID
 输出参数  : pstPlmnInfo,支持的接入技术个数
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月27日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_BuildPlmnSelectionPlmnInfo(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    VOS_UINT16                                              usSimRat,
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo
)
{
    VOS_UINT8                           ucRatNum;

    ucRatNum                = 0x0;

    PS_MEM_CPY(&pstPlmnInfo->stPlmnId, pstPlmnId, sizeof(NAS_MML_PLMN_ID_STRU));
    pstPlmnInfo->enPlmnType = enPlmnType;

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_SIM_RAT_E_UTRN == (NAS_MML_SIM_RAT_E_UTRN & usSimRat))
    {
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_LTE;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        ucRatNum++;
    }
#endif

    if (NAS_MML_SIM_RAT_UTRN == (NAS_MML_SIM_RAT_UTRN & usSimRat))
    {
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_WCDMA;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        ucRatNum++;
    }

    if (NAS_MML_SIM_RAT_GSM == (NAS_MML_SIM_RAT_GSM & usSimRat))
    {
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_GSM;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        ucRatNum++;
    }

    pstPlmnInfo->ucRatNum = ucRatNum;

    /* 数组剩余位置赋值为无效值 */
    for (; ucRatNum < NAS_MML_MAX_RAT_NUM; ucRatNum++)
    {
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_BUTT;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_BUTT;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_BUTT;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_AddEHPlmnInPlmnSelectionList
 功能描述  : 向搜网列表中加入EHPLMN或HPLMN
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月29日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_AddEHPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;

    /* 获取EHPLMN */
    pstEHPlmnInfo = NAS_MML_GetSimEhplmnList();

    for (i = 0; i< pstEHPlmnInfo->ucEhPlmnNum; i++)
    {
        /* 根据SIM卡的接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
        NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_HPLMN,
                                           pstEHPlmnInfo->astEhPlmnInfo[i].usSimRat,
                                           &(pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId),
                                           &stPlmnInfo);

        /* 添加到搜网列表 */
        NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddEHPlmnInDestPlmn
 功能描述  : 向目的的搜网列表中加入EHPLMN或HPLMN
 输入参数  : pstEHPlmnInfo        EHPLMN 列表
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年3月19日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期   : 2014年6月17日
   作    者   : z00234330
   修改内容   : PCINT清理
 3.日    期   : 2015年9月30日
   作    者   : c00318887
   修改内容   : DTS2015091700173
*****************************************************************************/
VOS_VOID NAS_MMC_AddEHPlmnInDestPlmnList(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo
)
{
    VOS_UINT32                                              i;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndexOfPlmnList;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnIdWithRat;
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfg   = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stTempPlmn;

    if ( 0 == pstDestPlmnList->ulPlmnNum )
    {
        return;
    }

    /* 获取禁止接入技术的PLMN信息 */
    pstDisabledRatPlmnCfg = NAS_MML_GetDisabledRatPlmnInfo();

    /* 该列表的第0位为RPLMN */
    pstPlmnWithRat = &pstDestPlmnList->astPlmnId[0];


    PS_MEM_SET(&stTempPlmn, 0x00, sizeof(stTempPlmn));

    /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */
    for (i = 0, (ulIndexOfPlmnList = 1); i< NAS_MML_MIN(pstEHPlmnInfo->ucEhPlmnNum, NAS_MML_MAX_EHPLMN_NUM); i++)
    /* Modified by z00234330 for PCLINT清理, 2014-06-24, end */
    {
        /* 根据SIM卡的接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
        PS_MEM_SET(&stPlmnId, 0x00, sizeof(stPlmnId));
        PS_MEM_SET(&stPlmnIdWithRat, 0x00, sizeof(stPlmnIdWithRat));
        PS_MEM_CPY(&stPlmnId, &(pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId), sizeof(stPlmnId));
        PS_MEM_CPY(&stPlmnIdWithRat.stPlmnId, &stPlmnId, sizeof(stPlmnIdWithRat.stPlmnId));

        stPlmnIdWithRat.enRat = pstPlmnWithRat->enRat;

        if ( VOS_TRUE == NAS_MML_IsBcchPlmnIdWithRatInDestPlmnWithRatList(&stPlmnIdWithRat, pstDestPlmnList->ulPlmnNum, pstDestPlmnList->astPlmnId) )
        {
            continue;
        }

        /* 判断该PLMN是否在黑白名单中 */
        if ( VOS_TRUE == NAS_MML_IsPlmnIdForbiddenByWhiteBlackList(&stPlmnId) )
        {
            continue;
        }

        /* 组装stTempPlmn，用于判断是否被禁接入技术 */
        stTempPlmn.enPlmnType                  = NAS_MMC_PLMN_TYPE_HPLMN;
        stTempPlmn.ucRatNum                    = 1;
        stTempPlmn.astPlmnRatInfo[0].enRatType = pstPlmnWithRat->enRat;
        PS_MEM_CPY(&stTempPlmn.stPlmnId, &stPlmnId, sizeof(stTempPlmn.stPlmnId));

        /* 删除在禁止接入技术的网络的接入技术 */
        NAS_MMC_DelPlmnSelectionRatInfoInDisabledPlmnWithForbiddenPeriodList(&stTempPlmn,
                                                  pstDisabledRatPlmnCfg->ulDisabledRatPlmnNum,
                                                  pstDisabledRatPlmnCfg->astDisabledRatPlmnId);

        /* 删除在禁止接入技术列表中的接入技术 */
        NAS_MMC_DeleteForbiddenRatInPlmnSeleInfo(&stTempPlmn);

        /* 若添加网络的接入技术个数为零，则不添加 */
        if (0 == stTempPlmn.ucRatNum)
        {
            continue;
        }

        if ( NAS_MML_MAX_EHPLMN_NUM <= pstDestPlmnList->ulPlmnNum )
        {
            break;
        }

        pstDestPlmnList->astPlmnId[ulIndexOfPlmnList].enRat          = pstPlmnWithRat->enRat;

        PS_MEM_CPY(&(pstDestPlmnList->astPlmnId[ulIndexOfPlmnList].stPlmnId), &stPlmnId, sizeof(NAS_MML_PLMN_ID_STRU));
        pstDestPlmnList->ulPlmnNum++;
        ulIndexOfPlmnList++;
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_AddEPlmnInDestPlmnList
 功能描述  : 向目的的搜网列表中加入EPLMN
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月9日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_AddEPlmnInDestPlmnList(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulIndexOfPlmnList;
    VOS_UINT32                                              ulCurPlmnNum;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnIdWithRat;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    PS_MEM_SET(&stPlmnIdWithRat, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    ulCurPlmnNum = pstDestPlmnList->ulPlmnNum;

    if ( 0 == ulCurPlmnNum )
    {
        return;
    }

    pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
    PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
    NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);

    for (i = 0, (ulIndexOfPlmnList = ulCurPlmnNum); i< NAS_MML_MIN(stSndEquPlmnInfo.ucEquPlmnNum, NAS_MML_MAX_EHPLMN_NUM); i++)
    {
        stPlmnIdWithRat.stPlmnId.ulMcc = stSndEquPlmnInfo.astEquPlmnAddr[i].ulMcc;
        stPlmnIdWithRat.stPlmnId.ulMnc = stSndEquPlmnInfo.astEquPlmnAddr[i].ulMnc;
        stPlmnIdWithRat.enRat          = pstDestPlmnList->astPlmnId[0].enRat;

        /* 需要加入的eplmn已经在列表中则跳过 */
        if ( VOS_TRUE == NAS_MML_IsBcchPlmnIdWithRatInDestPlmnWithRatList(&stPlmnIdWithRat, pstDestPlmnList->ulPlmnNum, pstDestPlmnList->astPlmnId) )
        {
            continue;
        }

        pstDestPlmnList->astPlmnId[ulIndexOfPlmnList].enRat = stPlmnIdWithRat.enRat;
        PS_MEM_CPY(&(pstDestPlmnList->astPlmnId[ulIndexOfPlmnList].stPlmnId), &stPlmnIdWithRat.stPlmnId, sizeof(NAS_MML_PLMN_ID_STRU));
        pstDestPlmnList->ulPlmnNum++;
        ulIndexOfPlmnList++;

        if (ulIndexOfPlmnList >= NAS_MML_MAX_EHPLMN_NUM)
        {
            return;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddDplmnOfSameCountryInDestPlmnList
 功能描述  : 向目的的搜网列表中加入DPLMN
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月24日
   作    者   : l00289540
   修改内容   : 新生成函数
  2.日    期   : 2015年12月30日
    作    者   : c00318887
    修改内容   : DTS2015120807529：需要增加的dplmn在fplmn里，不应增加
*****************************************************************************/
VOS_VOID NAS_MMC_AddDplmnInDestPlmnList(
    NAS_MML_PLMN_WITH_RAT_STRU          *pstDestPlmn,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU     *pstDestPlmnList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulIsSameCountryAsDestPlmn;
    NAS_MML_MCC_DESC_STRU                                  *pstEquMccList           = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDplmnNplmnCfgInfo    = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList    = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo       = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stTempPlmn;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* 获取等效MCC列表 */
    pstEquMccList                       = NAS_MML_GetEquivalentMccList(pstDestPlmn->stPlmnId.ulMcc);

    /* 获取选网列表 */
    pstPlmnSelectionList                = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    pstForbidPlmnInfo                   = NAS_MML_GetForbidPlmnInfo();
    PS_MEM_SET(&stTempPlmn, 0x00, sizeof(stTempPlmn));

    if ((0 == pstDestPlmnList->ulPlmnNum)
     || (VOS_NULL_PTR == pstEquMccList))
    {
        return;
    }

    pstDplmnNplmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* 从DPLMN List获取属于相同国家的的DPLMN，将其加入到目标列表中 */
    for (i = 0; i < pstDplmnNplmnCfgInfo->usDplmnListNum; i++)
    {
        /* 当前DPLMN不支持当前接入技术 */
        if (VOS_FALSE == NAS_MMC_IsNetRatContainedInSimRat(pstDestPlmn->enRat, pstDplmnNplmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.usSimRat))
        {
            continue;
        }

        stPlmnWithRat.stPlmnId.ulMcc = pstDplmnNplmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMcc;
        stPlmnWithRat.stPlmnId.ulMnc = pstDplmnNplmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMnc;
        stPlmnWithRat.enRat = pstDestPlmn->enRat;

        ulIsSameCountryAsDestPlmn = NAS_MML_IsSpecMccInEquMccList(stPlmnWithRat.stPlmnId.ulMcc, pstEquMccList);
        enNetStatus = NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&stPlmnWithRat, pstPlmnSelectionList);

        if ((VOS_TRUE == ulIsSameCountryAsDestPlmn)
         && (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != enNetStatus))
        {
            /* 需要加入的Dplmn已经在列表中则跳过 */
            if ( VOS_TRUE == NAS_MML_IsBcchPlmnIdWithRatInDestPlmnWithRatList(&stPlmnWithRat, pstDestPlmnList->ulPlmnNum, pstDestPlmnList->astPlmnId) )
            {
                continue;
            }

            /* 需要加入的Dplmn在forbid plmn列表中则跳过 */
            if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(stPlmnWithRat.stPlmnId),
                                                  pstForbidPlmnInfo->ucForbPlmnNum,
                                                  pstForbidPlmnInfo->astForbPlmnIdList))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList: dplmn in forbPlmnIdList");
                continue;
            }   
            
            /* 判断该PLMN是否在黑白名单中 */
            if ( VOS_TRUE == NAS_MML_IsPlmnIdForbiddenByWhiteBlackList(&(stPlmnWithRat.stPlmnId)) )
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList: dplmn in WhiteBlackList");
                continue;
            }
            
            /* 该PLMN ID是否在锁网锁卡的PLMN 列表中 */
            if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInLockPlmnList(&(stPlmnWithRat.stPlmnId)))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList: dplmn in LockPlmnList");
                continue;
            }
            
            /* 不允许漫游时 */
            if (VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(&(stPlmnWithRat.stPlmnId)))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList: dplmn RoamingAllowed is false");
                continue;
            } 
            /* 当前plmn的MCC在禁止LTE国际漫游的MCC列表里,PLMN不允许发起注册 */
            if (VOS_TRUE == NAS_MMC_IsNeedDisableLteRoam(stPlmnWithRat.stPlmnId.ulMcc))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList:  dplmn IsNeedDisableLteRoam is true");
                continue;
            }            
            
            /* 判断当前PLMN是否在禁止RAT的PLMN列表中同时当前接入技术被禁止,则认为当前PLMN为禁止网络 */
            if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList: NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList return true");
                continue;
            }
            
            /* 判断PLMN的RAT在禁止接入技术列表中，则认为当前RAT对应网络为禁止网络 */
            if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(stPlmnWithRat.enRat))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList: NAS_MML_IsRatInForbiddenList return true");
                continue;
            }

            /* 目标列表已满，则退出此函数 */
            if ( NAS_MML_MAX_EHPLMN_NUM <= pstDestPlmnList->ulPlmnNum )
            {
                return;
            }

            pstDestPlmnList->astPlmnId[pstDestPlmnList->ulPlmnNum].enRat = stPlmnWithRat.enRat;
            PS_MEM_CPY(&(pstDestPlmnList->astPlmnId[pstDestPlmnList->ulPlmnNum].stPlmnId), &stPlmnWithRat.stPlmnId, sizeof(NAS_MML_PLMN_ID_STRU));
            pstDestPlmnList->ulPlmnNum++;
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddUOPlmnInPlmnSelectionList
 功能描述  : 向搜网列表中加入UPLMN、OPLMN,如果卡中不存在这两个文件,添加PlmnSel
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月29日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期    : 2013年11月26日
   作    者    : s00190137
   修改内容    : 将最大支持设置的OPLMN扩展到256个
 3.日    期   : 2014年6月13日
   作    者   : b00269685
   修改内容   : 根据3gpp2,Pref网络不包含UPLMN

*****************************************************************************/
VOS_VOID NAS_MMC_AddUOPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_SIM_USERPLMN_INFO_STRU                         *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU                         *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU                          *pstSelPlmnList  = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;
    VOS_UINT16                                              usSimRat;

    /* 获取UOPLMN */
    pstUserPlmnList = NAS_MML_GetSimUserPlmnList();

    pstOperPlmnList = NAS_MML_GetSimOperPlmnList();

    /* UPLMN个数不为0或者OPLMN个数不为0 */
    if ((pstUserPlmnList->ucUserPlmnNum > 0)
     || (pstOperPlmnList->usOperPlmnNum > 0))
    {
        for (i = 0; i< pstUserPlmnList->ucUserPlmnNum; i++)
        {

            /* UPLMN中若Plmn有效，但usSimRat为0时，默认都支持 */
            usSimRat = pstUserPlmnList->astUserPlmnInfo[i].usSimRat;

            if (0 == usSimRat)
            {
                usSimRat = NAS_MML_SIM_RAT_ALL_SUPPORT;
            }

            /* 根据SIM卡的接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_UPLMN,
                                               usSimRat,
                                               &(pstUserPlmnList->astUserPlmnInfo[i].stPlmnId),
                                               &stPlmnInfo);

            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
        }

        for (i = 0; i< pstOperPlmnList->usOperPlmnNum; i++)
        {
            /* OPLMN中若Plmn有效，但usSimRat为0时，默认都支持 */
            usSimRat = pstOperPlmnList->astOperPlmnInfo[i].usSimRat;

            if (0 == usSimRat)
            {
                usSimRat = NAS_MML_SIM_RAT_ALL_SUPPORT;
            }

            /* 根据SIM卡的接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_OPLMN,
                                               usSimRat,
                                               &(pstOperPlmnList->astOperPlmnInfo[i].stPlmnId),
                                               &stPlmnInfo);

            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
        }
    }
    else /* 表示(U)SIM卡中不存在UPLMN、OPLMN，则添加PLMN Sel文件 */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        for (i = 0; i< pstSelPlmnList->ucSelPlmnNum; i++)
        {
            /* 根据SIM卡的接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_OPLMN,
                                               NAS_MML_SIM_RAT_ALL_SUPPORT,
                                               &(pstSelPlmnList->astPlmnId[i]),
                                               &stPlmnInfo);

            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddOPlmnInPlmnSelectionList
 功能描述  : 向搜网列表中加入OPLMN,如果卡中不存在这两个文件,添加PlmnSel
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年5月15日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_AddOPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_SIM_USERPLMN_INFO_STRU                         *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU                         *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU                          *pstSelPlmnList  = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;
    VOS_UINT16                                              usSimRat;

    /* 获取UOPLMN */
    pstUserPlmnList = NAS_MML_GetSimUserPlmnList();

    pstOperPlmnList = NAS_MML_GetSimOperPlmnList();

    /* UPLMN个数不为0或者OPLMN个数不为0 */
    if ((pstUserPlmnList->ucUserPlmnNum > 0)
     || (pstOperPlmnList->usOperPlmnNum > 0))
    {
        for (i = 0; i< pstOperPlmnList->usOperPlmnNum; i++)
        {
            /* OPLMN中若Plmn有效，但usSimRat为0时，默认都支持 */
            usSimRat = pstOperPlmnList->astOperPlmnInfo[i].usSimRat;

            if (0 == usSimRat)
            {
                usSimRat = NAS_MML_SIM_RAT_ALL_SUPPORT;
            }

            /* 根据SIM卡的接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_OPLMN,
                                               usSimRat,
                                               &(pstOperPlmnList->astOperPlmnInfo[i].stPlmnId),
                                               &stPlmnInfo);

            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
        }
    }
    else /* 表示(U)SIM卡中不存在UPLMN、OPLMN，则添加PLMN Sel文件 */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        for (i = 0; i< pstSelPlmnList->ucSelPlmnNum; i++)
        {
            /* 根据SIM卡的接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_OPLMN,
                                               NAS_MML_SIM_RAT_ALL_SUPPORT,
                                               &(pstSelPlmnList->astPlmnId[i]),
                                               &stPlmnInfo);

            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode
 功能描述  : 手动搜网模式下向搜网列表中加入EPLMN
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月29日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:更改比较的先后顺序，认为当前驻留的网络类型
                为BCCH的。

*****************************************************************************/
VOS_VOID NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnList = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;

    /* 当前Rplmn不存在时，不添加Eplmn */
    if (VOS_FALSE == NAS_MML_GetRPlmn(NAS_MML_GetLastRplmnRat(), &stPlmnId))
    {
        return;
    }

    pstEquPlmnList = NAS_MML_GetEquPlmnList();


    /* Rplmn与 EplmnList[0]不相同时，不需要添加 */
    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId, &(pstEquPlmnList->astEquPlmnAddr[0])))
    {
        return;
    }

    for (i = 1; i < pstEquPlmnList->ucEquPlmnNum; i++)
    {
        /* 根据SIM卡的接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
        NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_EPLMN,
                                           NAS_MML_SIM_RAT_ALL_SUPPORT,
                                           &(pstEquPlmnList->astEquPlmnAddr[i]),
                                           &stPlmnInfo);

        NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode
 功能描述  : 向搜网列表中加入EPLMN
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月29日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:更改比较的先后顺序，认为当前驻留的网络类型
                为BCCH的。

*****************************************************************************/
VOS_VOID NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnList = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;


    pstEquPlmnList = NAS_MML_GetEquPlmnList();


    for (i = 1; i < pstEquPlmnList->ucEquPlmnNum; i++)
    {
        /* 根据SIM卡的接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
        NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_EPLMN,
                                           NAS_MML_SIM_RAT_ALL_SUPPORT,
                                           &(pstEquPlmnList->astEquPlmnAddr[i]),
                                           &stPlmnInfo);

        NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddRPlmnInPlmnSelectionList
 功能描述  : 向搜网列表中按特定接入技术优先顺序加入RPLMN
 输入参数  : pstPrioRatList
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月29日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_AddRPlmnInPlmnSelectionList(
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;
    NAS_MML_PLMN_ID_STRU                                    stRPlmn;
    NAS_MML_RPLMN_CFG_INFO_STRU                            *pstRPlmnCfg  = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRPlmnRat;

    /* 获取RPLMN配置信息 */
    pstRPlmnCfg = NAS_MML_GetRplmnCfg();

    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        enRPlmnRat = pstPrioRatList->aucRatPrio[i];

        /* 如果多RPLMN特性未激活,则使用最后注册成功的RPLMN作为所有接入技术的RPLMN
           或者当前为手动选网模式,也只有最后注册成功的RPLMN为指定网络的EPLMN,其它RPLMN不能搜索 */
        if ((NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
         || (VOS_FALSE == pstRPlmnCfg->ucMultiRATRplmnFlg))
        {
            enRPlmnRat = pstRPlmnCfg->enLastRplmnRat;
        }

        /* RPLMN获取失败 */
        if (VOS_FALSE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(enRPlmnRat,
                                                               &stRPlmn))
        {
            continue;
        }

        switch (pstPrioRatList->aucRatPrio[i])
        {
#if   (FEATURE_ON == FEATURE_LTE)
            case NAS_MML_NET_RAT_TYPE_LTE:

                /* 根据当前接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_RPLMN,
                                                   NAS_MML_SIM_RAT_E_UTRN,
                                                   &stRPlmn,
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
                break;
#endif

            case NAS_MML_NET_RAT_TYPE_WCDMA:

                /* 根据当前接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_RPLMN,
                                                   NAS_MML_SIM_RAT_UTRN,
                                                   &stRPlmn,
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
                break;

            case NAS_MML_NET_RAT_TYPE_GSM:

                /* 根据当前接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_RPLMN,
                                                   NAS_MML_SIM_RAT_GSM,
                                                   &stRPlmn,
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
                break;

            default:
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_AddRPlmnInPlmnSelectionList: Rat not support.");
                break;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList
 功能描述  : 向搜网列表中加入用户指定搜索PLMN
 输入参数  : 无
 输出参数  : pstPlmnSelectionListInfo,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月27日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;

    pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

    /* 根据接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
    NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                       NAS_MML_SIM_RAT_ALL_SUPPORT,
                                       &(pstUserSpecPlmn->stPlmnId),
                                       &stPlmnInfo);

    NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);

    return;
}

/* Modified by z40661 for 泰国AIS特性 2012-05-17, begin */

/*****************************************************************************
 函 数 名  : NAS_MMC_AddAisRoamPlmnInPlmnSelectionList
 功能描述  : 向搜网列表中加入AIS漫游搜索PLMN
 输入参数  : 无
 输出参数  : pstPlmnSelectionListInfo,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年5月17日
   作    者   : z40661
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_AddAisRoamPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_AIS_ROAMING_CFG_STRU           *pstRoamingCfg   = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU   stPlmnInfo;
    VOS_UINT16                              usSimRat;

    pstRoamingCfg  = NAS_MML_GetAisRoamingCfg();



#if (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == pstRoamingCfg->enHighPrioRatType )
    {
        usSimRat = NAS_MML_SIM_RAT_E_UTRN;
    }
#endif
    if ( NAS_MML_NET_RAT_TYPE_WCDMA == pstRoamingCfg->enHighPrioRatType )
    {
        usSimRat = NAS_MML_SIM_RAT_UTRN;
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == pstRoamingCfg->enHighPrioRatType )
    {
        usSimRat = NAS_MML_SIM_RAT_GSM;
    }
    else
    {
        usSimRat = NAS_MML_SIM_NO_RAT;
    }

    /* 根据接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
    NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_HPLMN,
                                       usSimRat,
                                       &(pstRoamingCfg->stHighPrioPlmnId),
                                       &stPlmnInfo);

    NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);

}


/* Modified by z40661 for 泰国AIS特性 2012-05-17, end */

/*****************************************************************************
 函 数 名  : NAS_MMC_AddSpecPlmnInPlmnSelectionList
 功能描述  : 向搜网列表中按特定接入技术优先顺序加入指定网络
 输入参数  : pstPlmn
             enPlmnType
             pstPrioRatList
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月29日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_AddSpecPlmnInPlmnSelectionList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmn,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;

    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        switch (pstPrioRatList->aucRatPrio[i])
        {
#if   (FEATURE_ON == FEATURE_LTE)
            case NAS_MML_NET_RAT_TYPE_LTE:

                /* 根据当前接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(enPlmnType,
                                                   NAS_MML_SIM_RAT_E_UTRN,
                                                   pstPlmn,
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
                break;
#endif

            case NAS_MML_NET_RAT_TYPE_WCDMA:

                /* 根据当前接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(enPlmnType,
                                                   NAS_MML_SIM_RAT_UTRN,
                                                   pstPlmn,
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
                break;

            case NAS_MML_NET_RAT_TYPE_GSM:

                /* 根据当前接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(enPlmnType,
                                                   NAS_MML_SIM_RAT_GSM,
                                                   pstPlmn,
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
                break;

            default:
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_AddSpecPlmnInPlmnSelectionList: Rat not support.");
                break;
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_AppendPlmnInPlmnSelectionList
 功能描述  : 向搜网列表中加入指定PLMN
 输入参数  : pstPlmn
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月29日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                更改为NAS_MML_IsSimPlmnIdInDestBcchPlmnList,明确网络的比较类型，
                否则可能导致比较出错。
 3.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : BalongV300R002 Build优化项目:删除NAS_FEATURE_BLACK_WHITE_PLMN宏
 4.日    期   : 2012年8月15日
   作    者   : w00176964
   修改内容   : V7R1C50_GUTL_PhaseII:将当前PLMN中的禁止接入技术删除

  5.日    期   : 2012年9月24日
    作    者   : w00167002
    修改内容   : DTS2012092405740:删除禁止网络接入技术时，不改变传递进来的数据信息。
                 原有的问题举例如下:用户下发列表搜，当前存在46001W,23001W,46001G,
                 设置46001W为禁止网络，列表只上报了46001G,没有上报23001W.
  6.日    期   : 2013年11月01日
    作    者   : l00208543
    修改内容   : 根据卡类型禁止网络制式
*****************************************************************************/
VOS_VOID NAS_MMC_AppendPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmn,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT16                                              usSearchPlmnNum;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stTempPlmn;

    NAS_MML_PLMN_LOCK_CFG_INFO_STRU                        *pstPlmnLockCfg          = VOS_NULL_PTR;
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfg   = VOS_NULL_PTR;

    PS_MEM_SET(&stTempPlmn, 0, sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

    /* 获取禁止接入技术的PLMN信息 */
    pstDisabledRatPlmnCfg = NAS_MML_GetDisabledRatPlmnInfo();

    /* 用于获取黑白名单 */
    pstPlmnLockCfg = NAS_MML_GetPlmnLockCfg();

    /* 拷贝传进的数据pstPlmn到临时局部变量中去，保证pstPlmn数据不会被当前函数修改 */
    PS_MEM_CPY(&stTempPlmn, pstPlmn, sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU) );

    /* 该PLMN无效 */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(&(stTempPlmn.stPlmnId)))
    {
        return;
    }

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    /* 判断当前的网络是否在黑名单列表中，若在则直接返回VOS_FALSE */
    if ( VOS_TRUE == NAS_MMC_IsSpecTypePlmnIdInDestPlmnList(&(stTempPlmn.stPlmnId),
                                           stTempPlmn.enPlmnType,
                                           pstPlmnLockCfg->ucBlackPlmnLockNum,
                                           pstPlmnLockCfg->astBlackPlmnId) )     /* 该PLMN在黑名单列表中 */
    {
        return;
    }

    if (pstPlmnLockCfg->ucWhitePlmnLockNum != 0)
    {
        /* 判断当前的网络是否在白名单列表中，若不在则直接返回VOS_FALSE */
        if (VOS_FALSE == NAS_MMC_IsSpecTypePlmnIdInDestPlmnList(&(stTempPlmn.stPlmnId),
                                               stTempPlmn.enPlmnType,
                                               pstPlmnLockCfg->ucWhitePlmnLockNum,
                                               pstPlmnLockCfg->astWhitePlmnId))     /* 该PLMN不在白名单列表中 */
        {
            return;
        }
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    if (VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(&(stTempPlmn.stPlmnId))) /* 该PLMN不在允许漫游列表中 */
    {
        return;
    }

    /* 删除在禁止接入技术的网络的接入技术 */
    NAS_MMC_DelPlmnSelectionRatInfoInDisabledPlmnWithForbiddenPeriodList(&stTempPlmn,
                                              pstDisabledRatPlmnCfg->ulDisabledRatPlmnNum,
                                              pstDisabledRatPlmnCfg->astDisabledRatPlmnId);

    /* 删除在禁止接入技术列表中的接入技术 */
    NAS_MMC_DeleteForbiddenRatInPlmnSeleInfo(&stTempPlmn);

    /* 若添加网络的接入技术个数为零，则不添加 */
    if (0 == stTempPlmn.ucRatNum)
    {
        return;
    }

    usSearchPlmnNum = pstPlmnSelectionListInfo->usSearchPlmnNum;

    if (usSearchPlmnNum >= NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_AppendPlmnInPlmnSelectionList: list full.");

        return;
    }

    /*将该PLMN存储在列表尾部,PLMN个数增1*/
    PS_MEM_CPY(&(pstPlmnSelectionListInfo->astPlmnSelectionList[usSearchPlmnNum]),
               &stTempPlmn, sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
    pstPlmnSelectionListInfo->usSearchPlmnNum++;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AppendPlmnInRoamPlmnSelectionList
 功能描述  : 向搜网列表中加入指定PLMN
 输入参数  : pstPlmn - 指定plmn信息
 输出参数  : pstSearchedPlmnListInfo - 列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月30日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改
 2.日    期   : 2016年1月4日
   作    者   : s00217060
   修改内容   : DTS2015120406613:搜到漫游的网络不排序

*****************************************************************************/
VOS_VOID NAS_MMC_AppendPlmnInRoamPlmnSelectionList(
    NAS_MMC_ROAM_PLMN_INFO_STRU                            *pstPlmn,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedPlmnListInfo
)
{
    VOS_UINT16                                              usSearchPlmnNum;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stTempPlmn;
    NAS_MML_LAI_STRU                                        stLai;
    VOS_UINT8                                               ucAllBandSearch;
    VOS_UINT32                                              i;

    PS_MEM_SET(&stTempPlmn, 0, sizeof(stTempPlmn));
    PS_MEM_SET(&stLai, 0, sizeof(stLai));
    i               = 0;
    usSearchPlmnNum = 0;

    /* 拷贝传进的数据pstPlmn到临时局部变量中去，保证pstPlmn数据不会被当前函数修改 */
    PS_MEM_CPY(&stTempPlmn, pstPlmn, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU) );

    /* plmn无效不插入roam搜网列表 */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(&stTempPlmn.stPlmnWithRat.stPlmnId))
    {
        return;
    }

    ucAllBandSearch = NAS_MMC_GetAllBandSearch_PlmnSelection(stTempPlmn.stPlmnWithRat.enRat);

    /* 如果该接入技术之前已经收到过searched plmn info ind且排过一次序,或已经进行过一轮全频段搜网，
       则不添加该接入技术plmn到roam搜网列表 */
    if (VOS_TRUE == NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(stTempPlmn.stPlmnWithRat.enRat))
    {
        return;
    }

    /* 如果某个模是从模，并且该模下已经进行过一轮全频段搜网，漫游排序时只排当前主模，不对这个从模进行排序 */
    if ((pstPlmn->stPlmnWithRat.enRat != NAS_MML_GetCurrNetRatType())
     && (VOS_TRUE == ucAllBandSearch))
    {
        return;
    }

    usSearchPlmnNum = pstSearchedPlmnListInfo->usSearchPlmnNum;

    if (usSearchPlmnNum >= NAS_MMC_MAX_ROAM_PLMN_NUM_IN_SELECTION_LIST)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_AppendPlmnInRoamPlmnSelectionList: list full.");

        return;
    }

    /* 如果已经在roam搜网列表中，则无需添加 */
    for (i = 0; i < pstSearchedPlmnListInfo->usSearchPlmnNum; i++)
    {
        if ((VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stTempPlmn.stPlmnWithRat.stPlmnId, &pstSearchedPlmnListInfo->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId))
         && (stTempPlmn.stPlmnWithRat.enRat == pstSearchedPlmnListInfo->astPlmnSelectionList[i].stPlmnWithRat.enRat))
        {
            return;
        }
    }

    stLai.stPlmnId         = stTempPlmn.stPlmnWithRat.stPlmnId;
    stLai.enCampPlmnNetRat = stTempPlmn.stPlmnWithRat.enRat;
    stLai.aucLac[0]        = stTempPlmn.aucLac[0];
    stLai.aucLac[1]        = stTempPlmn.aucLac[1];
    stLai.ucRac            = NAS_MML_RAC_INVALID;

    /* 获取网络禁止类型，如果是禁止网络则不加入roam搜网列表 */
    if (NAS_MML_PLMN_FORBID_NULL != NAS_MML_GetLaiForbType(&stLai))
    {
        return;
    }

    /*将该PLMN存储在列表尾部,PLMN个数增1*/
    PS_MEM_CPY(&(pstSearchedPlmnListInfo->astPlmnSelectionList[usSearchPlmnNum]),
               &stTempPlmn, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));

    pstSearchedPlmnListInfo->usSearchPlmnNum++;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InsertPlmnInPlmnSelectionList
 功能描述  : 向搜网列表中插入指定PLMN
 输入参数  : pstPlmn:需要插入的PLMN信息
             ulPos:需要插入的位置
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_UINT32 VOS_TRUE :插入成功
                        VOS_FALSE:插入失败
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月29日
   作    者   : s46746
   修改内容   : 新生成函数
2. 日    期   : 2013年8月26日
   作    者   : w00242748
   修改内容   : DTS2013071808373,编译告警清理
*****************************************************************************/
VOS_UINT32 NAS_MMC_InsertPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmn,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    VOS_UINT32                                              ulPos
)
{
    VOS_UINT16                          usSearchPlmnNum;

    usSearchPlmnNum = pstPlmnSelectionListInfo->usSearchPlmnNum;

    if ((usSearchPlmnNum >= NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST)
     || (ulPos >= NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_InsertPlmnInPlmnSelectionList: list full.");

        return VOS_FALSE;
    }

    if ((NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST - 1) != ulPos)
    {
        /* 将第ulPos位置空出 */
        /*lint -e961*/
        (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[ulPos+1]),
                    &(pstPlmnSelectionListInfo->astPlmnSelectionList[ulPos]),
                    (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST-ulPos-1)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
        /*lint +e961*/
    }

    /* 将该PLMN插入到搜网列表第ulPos位置 */
    PS_MEM_CPY(&(pstPlmnSelectionListInfo->astPlmnSelectionList[ulPos]),
               pstPlmn, sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
    pstPlmnSelectionListInfo->usSearchPlmnNum++;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InsertPlmnToPlmnSelectionListHead
 功能描述  : 在选网列表前面按接入技术优先顺序插入指定PLMN
 输入参数  : pstPlmn:需要插入的PLMN
             enPlmnType
             pstPrioRatList,插入的接入技术优先级顺序
             ulPos:需要插入的位置
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月29日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_InsertPlmnToPlmnSelectionListHead(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmn,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulPos;

    ulRet                               = VOS_FALSE;
    ulPos                               = 0;

    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        switch (pstPrioRatList->aucRatPrio[i])
        {
#if   (FEATURE_ON == FEATURE_LTE)
            case NAS_MML_NET_RAT_TYPE_LTE:

                /* 根据当前接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(enPlmnType,
                                                   NAS_MML_SIM_RAT_E_UTRN,
                                                   pstPlmn,
                                                   &stPlmnInfo);

                ulRet = NAS_MMC_InsertPlmnInPlmnSelectionList(&stPlmnInfo,
                                                              pstPlmnSelectionListInfo,
                                                              ulPos);
                break;
#endif

            case NAS_MML_NET_RAT_TYPE_WCDMA:

                /* 根据当前接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(enPlmnType,
                                                   NAS_MML_SIM_RAT_UTRN,
                                                   pstPlmn,
                                                   &stPlmnInfo);

                ulRet = NAS_MMC_InsertPlmnInPlmnSelectionList(&stPlmnInfo,
                                                              pstPlmnSelectionListInfo,
                                                              ulPos);
                break;

            case NAS_MML_NET_RAT_TYPE_GSM:

                /* 根据当前接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(enPlmnType,
                                                   NAS_MML_SIM_RAT_GSM,
                                                   pstPlmn,
                                                   &stPlmnInfo);

                ulRet = NAS_MMC_InsertPlmnInPlmnSelectionList(&stPlmnInfo,
                                                              pstPlmnSelectionListInfo,
                                                              ulPos);
                break;

            default:
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_InsertSpecPlmnInPlmnSelectionList: Rat not support.");
                break;
        }

        if (VOS_TRUE == ulRet)
        {
            ulPos++;
            ulRet = VOS_FALSE;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateRatNetStatusInPlmnRatInfo
 功能描述  : 更新指定PLMN的对应接入技术的网络状态信息
 输入参数  : pstSrcPlmn
 输出参数  : pstDstPlmn,
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月19日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateRatNetStatusInPlmnRatInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstDstPlmn
)
{
    VOS_UINT32                             i;

    /* 将原PLMN的每一个支持的接入技术与目标PLMN的每一个支持的接入技术进行比较 */
    for (i = 0; i < pstDstPlmn->ucRatNum; i++)
    {
        /* 如果相同，则更新目标PLMN信息中的状态信息 */
        if (pstDstPlmn->astPlmnRatInfo[i].enRatType == enRat)
        {
            pstDstPlmn->astPlmnRatInfo[i].enNetStatus = enNetStatus;

            return;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList
 功能描述  : 获取搜网列表中指定接入技术的漫游网络的类型
 输入参数  : pstPlmnWithRat
             pstPlmnSelectionList,列表信息
 输出参数  : 无
 返 回 值  : NAS_MMC_PLMN_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
NAS_MMC_PLMN_TYPE_ENUM_UINT8 NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;

    enPlmnType = NAS_MMC_GetPlmnTypeInPlmnSelectionList(pstPlmnWithRat, pstPlmnSelectionListInfo);

    if (NAS_MMC_PLMN_TYPE_BUTT == enPlmnType)
    {
        enPlmnType = NAS_MMC_PLMN_TYPE_AVAIL_PLMN;
    }

    /* 由于搜网列表中plmn有重复的且类型有可能即是rplmn又是uplmn，需要再判断网络是否是UPLMN */
    if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithUplmn(pstPlmnWithRat))
    {
        enPlmnType = NAS_MMC_PLMN_TYPE_UPLMN;
        return enPlmnType;
    }

    /* 由于搜网列表中plmn有重复的且类型有可能即是rplmn又是uplmn，需要再判断网络是否是OPLMN */
    if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithOplmn(pstPlmnWithRat))
    {
        enPlmnType = NAS_MMC_PLMN_TYPE_OPLMN;
        return enPlmnType;
    }

    return enPlmnType;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList
 功能描述  : 获取搜网列表中指定网络的单个接入技术的网络的状态
 输入参数  : pstPlmnWithRat
             pstPlmnSelectionList,列表信息
 输出参数  : 无
 返 回 值  : NAS_MMC_NET_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

 2.日    期   : 2015年10月6日
   作    者   : c00318887
   修改内容   : 修改函数名称
*****************************************************************************/
NAS_MMC_NET_STATUS_ENUM_UINT8 NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                              stPrioRatList;
    NAS_MMC_NET_STATUS_ENUM_UINT8                           aucNetStatus[NAS_MML_MAX_RAT_NUM];
    VOS_UINT8                                               i;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(stPrioRatList));

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        aucNetStatus[i] = NAS_MMC_NET_STATUS_BUTT;
    }

    stPrioRatList.ucRatNum      = 1;
    stPrioRatList.aucRatPrio[0] = pstPlmnWithRat->enRat;
    NAS_MMC_GetSpecPlmnNetStatusInPlmnSelectionList(&pstPlmnWithRat->stPlmnId,
                                                    &stPrioRatList,
                                                    aucNetStatus,
                                                    pstPlmnSelectionListInfo);

    return  aucNetStatus[0];
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddSearchedPlmnInRoamPlmnSelectionList
 功能描述  : 向漫游搜网列表中加入网络
 输入参数  : pstRoamPlmnInfo - 加入网络信息
 输出参数  : pstNewRoamPlmnSelectionList - 搜网列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月28日
   作    者   : z00161729
   修改内容   : 开机漫游搜网项目修改

*****************************************************************************/
VOS_VOID NAS_MMC_AddSearchedPlmnInRoamPlmnSelectionList(
    NAS_MMC_ROAM_PLMN_INFO_STRU                            *pstRoamPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stPrioRatList;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stRoamPlmnInfo;
    VOS_UINT16                                              usSimRat;

    /* 获取选网列表 */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    enPlmnType      = NAS_MMC_PLMN_TYPE_BUTT;
    i               = 0;

    PS_MEM_SET(&stPlmnInfo, 0, sizeof(stPlmnInfo));
    PS_MEM_SET(&stRoamPlmnInfo, 0, sizeof(stRoamPlmnInfo));
    PS_MEM_SET(&stPrioRatList, 0, sizeof(stPrioRatList));

    /* 获取存储DPLMN和NPLMN的指针 */
    pstDPlmnNPlmnCfgInfo = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* 获取当前支持的接入技术及其优先级 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 向选网列表中增加接入层报上来的网络，当前搜网接入技术优先 */
    NAS_MML_SortSpecRatPrioHighest(pstRoamPlmnInfo->stPlmnWithRat.enRat, &stPrioRatList);


    /* 如果加入的网络在NPLMN中，则不添加到roam搜网列表中,如果搜网列表中没有则插入搜网列表最后面 */
    if (VOS_TRUE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(&pstRoamPlmnInfo->stPlmnWithRat,
                    pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList))
    {
        if (VOS_FALSE == NAS_MMC_IsPlmnWithRatInPlmnList(&pstRoamPlmnInfo->stPlmnWithRat.stPlmnId,
                                                         pstRoamPlmnInfo->stPlmnWithRat.enRat,
                                                         pstPlmnSrchList,
                                                         pstPlmnSrchList->usSearchPlmnNum))
        {
            usSimRat = NAS_MMC_ConvertNetRatToSimRat(pstRoamPlmnInfo->stPlmnWithRat.enRat);

            NAS_MMC_BuildPlmnSelectionPlmnInfo(pstRoamPlmnInfo->enPlmnType,
                                               usSimRat,
                                               &(pstRoamPlmnInfo->stPlmnWithRat.stPlmnId),
                                               &stPlmnInfo);

            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSrchList);
        }
    }
    else
    {
        NAS_MMC_AppendPlmnInRoamPlmnSelectionList(pstRoamPlmnInfo, pstNewRoamPlmnSelectionList);
    }

    /* 加入其他接入技术plmn到roam搜网列表 */
    for (i = 1; i < stPrioRatList.ucRatNum; i++)
    {
        stRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = pstRoamPlmnInfo->stPlmnWithRat.stPlmnId.ulMcc;
        stRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = pstRoamPlmnInfo->stPlmnWithRat.stPlmnId.ulMnc;
        stRoamPlmnInfo.stPlmnWithRat.enRat = stPrioRatList.aucRatPrio[i];

        enPlmnType                 = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&stRoamPlmnInfo.stPlmnWithRat, pstPlmnSrchList);
        stRoamPlmnInfo.enPlmnType  = enPlmnType;
        stRoamPlmnInfo.enNetStatus = NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&stRoamPlmnInfo.stPlmnWithRat, pstPlmnSrchList);

        if (NAS_MMC_NET_STATUS_BUTT == stRoamPlmnInfo.enNetStatus)
        {
            stRoamPlmnInfo.enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
        }

        /* 如果该网络在NPLMN中则不添加该网络到roam搜网列表,如果搜网列表中不存在，则插入搜网列表最后面 */
        if (VOS_TRUE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(&stRoamPlmnInfo.stPlmnWithRat,
                        pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList))
        {
            if (VOS_FALSE == NAS_MMC_IsPlmnWithRatInPlmnList(&stRoamPlmnInfo.stPlmnWithRat.stPlmnId,
                                                         stRoamPlmnInfo.stPlmnWithRat.enRat,
                                                         pstPlmnSrchList,
                                                         pstPlmnSrchList->usSearchPlmnNum))
            {
                usSimRat = NAS_MMC_ConvertNetRatToSimRat(stRoamPlmnInfo.stPlmnWithRat.enRat);

                NAS_MMC_BuildPlmnSelectionPlmnInfo(stRoamPlmnInfo.enPlmnType,
                                                   usSimRat,
                                                   &(stRoamPlmnInfo.stPlmnWithRat.stPlmnId),
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSrchList);
            }

            continue;
        }

        NAS_MMC_AppendPlmnInRoamPlmnSelectionList(&stRoamPlmnInfo, pstNewRoamPlmnSelectionList);

    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetRoamPlmnType
 功能描述  : 获取漫游网络类型
 输入参数  : pstPlmnInfo - 网络信息
 输出参数  : 无
 返 回 值  : 网络类型
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月29日
   作    者   : z00161729
   修改内容   : 新生成函数

  2.日    期   : 2015年10月13日
    作    者   : l00289540
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
*****************************************************************************/
NAS_MMC_ROAM_PLMN_TYPE_ENUM_UINT8 NAS_MMC_GetRoamPlmnType(
    NAS_MMC_ROAM_PLMN_INFO_STRU        *pstPlmnInfo
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    NAS_MML_LAI_STRU                                        stLai;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));
    PS_MEM_SET(&stLai, 0, sizeof(stLai));

    /* 获取存储DPLMN和NPLMN的指针 */
    pstDPlmnNPlmnCfgInfo   = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    stLai.stPlmnId         = pstPlmnInfo->stPlmnWithRat.stPlmnId;
    stLai.enCampPlmnNetRat = pstPlmnInfo->stPlmnWithRat.enRat;
    stLai.aucLac[0]        = pstPlmnInfo->aucLac[0];
    stLai.aucLac[1]        = pstPlmnInfo->aucLac[1];
    stLai.ucRac            = NAS_MML_RAC_INVALID;

    /* 判断网络是否为禁止网络 */
    if (NAS_MML_PLMN_FORBID_NULL != NAS_MML_GetLaiForbType(&stLai))
    {
        return NAS_MMC_ROAM_PLMN_TYPE_FORBIDDEN;
    }

    /* 判断网络是否在NPLMN列表中 */
    if (VOS_TRUE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(&pstPlmnInfo->stPlmnWithRat,
                      pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList))
    {
        return NAS_MMC_ROAM_PLMN_TYPE_NPLMN;
    }

    if (VOS_TRUE == NAS_MMC_GetSrchUOplmnPriorToDplmnFlg())
    {
        /* 判断网络是否是UPLMN */
        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithUplmn(&pstPlmnInfo->stPlmnWithRat))
        {
            return NAS_MMC_ROAM_PLMN_TYPE_UPLMN;
        }

        /* 判断网络是否是OPLMN */
        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithOplmn(&pstPlmnInfo->stPlmnWithRat))
        {
            return NAS_MMC_ROAM_PLMN_TYPE_OPLMN;
        }

        /* 判断网络是否在DPLMN中 */
        if (VOS_TRUE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(&pstPlmnInfo->stPlmnWithRat,
                               pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList))
        {
            return NAS_MMC_ROAM_PLMN_TYPE_DPLMN;
        }
    }
    else
    {
        /* 判断网络是否在DPLMN中 */
        if (VOS_TRUE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(&pstPlmnInfo->stPlmnWithRat,
                               pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList))
        {
            return NAS_MMC_ROAM_PLMN_TYPE_DPLMN;
        }

        /* 判断网络是否是UPLMN */
        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithUplmn(&pstPlmnInfo->stPlmnWithRat))
        {
            return NAS_MMC_ROAM_PLMN_TYPE_UPLMN;
        }

        /* 判断网络是否是OPLMN */
        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithOplmn(&pstPlmnInfo->stPlmnWithRat))
        {
            return NAS_MMC_ROAM_PLMN_TYPE_OPLMN;
        }
    }

    return NAS_MMC_ROAM_PLMN_TYPE_AVAIL_PLMN;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_GetRoamPlmnPrio
 功能描述  : 获取漫游PLMN的优先级信息
 输入参数  : NAS_MMC_ROAM_PLMN_INFO_STRU        *pstRoamPlmnInfo，漫游PLMN
 输出参数  : 无
 返 回 值  : VOS_UINT32，优先级对应的数值，取值范围为[0,5]，值越大，优先级越高
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetRoamPlmnPrio(
    NAS_MMC_ROAM_PLMN_INFO_STRU        *pstRoamPlmnInfo
)
{
    NAS_MMC_ROAM_PLMN_TYPE_ENUM_UINT8             enRoamPlmnType;
    NAS_MMC_ROAM_PLMN_PRIO_ENUM_UINT8             enRoamPlmnPrio;

    enRoamPlmnType      = NAS_MMC_GetRoamPlmnType(pstRoamPlmnInfo);

    if (VOS_FALSE == NAS_MMC_GetSrchUOplmnPriorToDplmnFlg())
    {
        return enRoamPlmnType;
    }

    switch(enRoamPlmnType)
    {
        case NAS_MMC_ROAM_PLMN_TYPE_UPLMN:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_UPLMN;
            break;

        case NAS_MMC_ROAM_PLMN_TYPE_OPLMN:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_OPLMN;
            break;

        case NAS_MMC_ROAM_PLMN_TYPE_DPLMN:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_DPLMN;
            break;

        case NAS_MMC_ROAM_PLMN_TYPE_AVAIL_PLMN:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_AVAIL_PLMN;
            break;

        case NAS_MMC_ROAM_PLMN_TYPE_NPLMN:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_NPLMN;
            break;

        case NAS_MMC_ROAM_PLMN_TYPE_FORBIDDEN:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_FORBIDDEN;
            break;

        default:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_FORBIDDEN;
            break;
    }

    return enRoamPlmnPrio;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_CompareRoamPlmnPrio
 功能描述  : 比较两个plmn优先级
 输入参数  : pPlmn1Info - 第一个plmn信息
             pPlmn2Info - 第二个plmn信息
 输出参数  : 无
 返 回 值  : 1 - 第一个plmn优先级高于第二个plmn
             0 - 第一个plmn优先级等于第二个plmn
            -1 - 第一个plmn优先级低于第二个plmn
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月29日
   作    者   : z00161729
   修改内容   : 新生成函数

  2.日    期   : 2015年10月9日
    作    者   : l00289540
    修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
*****************************************************************************/
VOS_INT32  NAS_MMC_CompareRoamPlmnPrio(
    const VOS_VOID                  *pPlmn1Info,
    const VOS_VOID                  *pPlmn2Info,
    NAS_MML_PLMN_RAT_PRIO_STRU      *pstPrioRatList
)
{
    NAS_MMC_ROAM_PLMN_INFO_STRU                            *pstFirstPlmnInfo;
    NAS_MMC_ROAM_PLMN_INFO_STRU                            *pstSecondPlmnInfo;
    VOS_UINT8                                               ucFirstRoamPlmnPrio;
    VOS_UINT8                                               ucSecondRoamPlmnPrio;
    VOS_UINT8                                               i;
    VOS_UINT8                                               ucFirstPlmnRatIndex;
    VOS_UINT8                                               ucSecondPlmnRatIndex;

    pstFirstPlmnInfo         = (NAS_MMC_ROAM_PLMN_INFO_STRU *)pPlmn1Info;
    pstSecondPlmnInfo        = (NAS_MMC_ROAM_PLMN_INFO_STRU *)pPlmn2Info;
    ucFirstRoamPlmnPrio      = NAS_MMC_GetRoamPlmnPrio(pstFirstPlmnInfo);
    ucSecondRoamPlmnPrio     = NAS_MMC_GetRoamPlmnPrio(pstSecondPlmnInfo);
    ucFirstPlmnRatIndex      = 0;
    ucSecondPlmnRatIndex     = 0;

    /* 比较两个plmn的优先及，plmn type越大优先级越高 */
    if (ucFirstRoamPlmnPrio > ucSecondRoamPlmnPrio)
    {
        return 1;
    }

    if (ucFirstRoamPlmnPrio < ucSecondRoamPlmnPrio)
    {
        return -1;
    }

    /* 如果两个plmn优先级相同，再比较网络状态，存在的网络优先级高,
       其他网络状态不作为优先级比较条件 */
    if ((NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstFirstPlmnInfo->enNetStatus)
     && (NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstSecondPlmnInfo->enNetStatus))
    {
        return 0;
    }

    if (NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstFirstPlmnInfo->enNetStatus)
    {
        return 1;
    }

    if (NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstSecondPlmnInfo->enNetStatus)
    {
        return -1;
    }

    /* 第一个plmn和第二个plmn相同时才考虑接入技术优先级*/
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstFirstPlmnInfo->stPlmnWithRat.stPlmnId, &pstSecondPlmnInfo->stPlmnWithRat.stPlmnId))
    {
        for (i = 0; i < pstPrioRatList->ucRatNum; i++)
        {
            if (pstFirstPlmnInfo->stPlmnWithRat.enRat == pstPrioRatList->aucRatPrio[i])
            {
                ucFirstPlmnRatIndex = i;
            }

            if (pstSecondPlmnInfo->stPlmnWithRat.enRat == pstPrioRatList->aucRatPrio[i])
            {
                ucSecondPlmnRatIndex = i;
            }
        }

        /* 第一个plmn接入技术优先，返回优先级高 */
        if (ucFirstPlmnRatIndex < ucSecondPlmnRatIndex)
        {
            return 1;
        }

        if (ucSecondPlmnRatIndex < ucFirstPlmnRatIndex)
        {
            return -1;
        }
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList
 功能描述  : 将排序好的roam搜网列表插入搜网列表
 输入参数  : pstNewRoamPlmnSelectionList - 需要插入搜网列表信息
 输出参数  : pstPlmnSrchList - 搜网列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月29日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年7月9日
   作    者   : z00161729
   修改内容   : DTS2015071001632:开机漫游搜网如果报上来的漫游网络全部是禁止网络或全在nplmn中，
               则存在构造的漫游网络列表为0个，0减1会出现全F的大数导致死循环，单板复位

*****************************************************************************/
VOS_VOID NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stInsertPlmnInfo;
    VOS_UINT16                                              usSimRat;
    VOS_INT32                                               i;

    PS_MEM_SET(&stInsertPlmnInfo, 0, sizeof(stInsertPlmnInfo));
    i = 0;

    if (0 == pstNewRoamPlmnSelectionList->usSearchPlmnNum)
    {
        return;
    }

    /* 按优先顺序从低到高插入搜网列表头部 */
    for (i = pstNewRoamPlmnSelectionList->usSearchPlmnNum - 1; i >= 0 ; i--)
    {
        usSimRat = NAS_MMC_ConvertNetRatToSimRat(pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].stPlmnWithRat.enRat);

        NAS_MMC_BuildPlmnSelectionPlmnInfo(
              pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].enPlmnType,
              usSimRat,
              &pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId,
              &stInsertPlmnInfo);

        (VOS_VOID)NAS_MMC_InsertPlmnInPlmnSelectionList(&stInsertPlmnInfo,
                 pstPlmnSrchList, 0);

        /* 如果roam搜网列表中网络状态是不为no searched，需要根据漫游搜网列表中网络状态更新搜网列表对应网络状态，
           默认NAS_MMC_BuildPlmnSelectionPlmnInfo构造完网络状态是未搜索状态 */
        if (NAS_MMC_NET_STATUS_NO_SEARCHED != pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].enNetStatus)
        {
            NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].stPlmnWithRat,
                                               pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].enNetStatus,
                                               pstPlmnSrchList);
        }
    }

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail
 功能描述  : 从rrc search cnf失败消息中获取存在的漫游网络信息
 输入参数  : enRat         - 接入技术
             pstPlmnIdList - rrc search cnf失败消息中带上来的网络信息
 输出参数  : pstSearchedExistPlmnInfo - 漫游搜网列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月1日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnIdList,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo
)
{
    VOS_UINT32                                             i;
    VOS_UINT32                                             ulPlmnNum;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                           enPlmnType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                 *pstPlmnSrchList   = VOS_NULL_PTR;

     /* 获取选网列表 */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* 加入高质量网络*/
    for (i = 0; i < pstPlmnIdList->ulHighPlmnNum; i++)
    {
        ulPlmnNum = pstSearchedExistPlmnInfo->usSearchPlmnNum;

        if (ulPlmnNum >= NAS_MMC_MAX_ROAM_PLMN_NUM_IN_SELECTION_LIST)
        {
            return;
        }

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.stPlmnId = pstPlmnIdList->astHighPlmnList[i];
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.enRat    = enRat;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[0]              = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[1]              = NAS_MML_LAC_HIGH_BYTE_INVALID;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus            = NAS_MMC_NET_STATUS_SEARCHED_EXIST;

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus  =  NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus)
        {
            pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        }

        enPlmnType = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enPlmnType  = enPlmnType;
        pstSearchedExistPlmnInfo->usSearchPlmnNum++;
    }

    /* 加入把低质量网络*/
    for (i = 0; i < pstPlmnIdList->ulLowPlmnNum; i++)
    {
        ulPlmnNum = pstSearchedExistPlmnInfo->usSearchPlmnNum;

        if (ulPlmnNum >= NAS_MMC_MAX_ROAM_PLMN_NUM_IN_SELECTION_LIST)
        {
            return;
        }

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.stPlmnId = pstPlmnIdList->astLowPlmnList[i].stPlmnId;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.enRat    = enRat;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[0]              = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[1]              = NAS_MML_LAC_HIGH_BYTE_INVALID;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus            = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        enPlmnType = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enPlmnType  = enPlmnType;
        pstSearchedExistPlmnInfo->usSearchPlmnNum++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildSearchedPlmnInfoByLteSearchedPlmnInfoInd
 功能描述  : 根据lte的searched plmn info ind消息中带上来的网络提取
             NAS_MMC_ROAM_PLMN_LIST_INFO_STRU结构类型的漫游搜网列表
 输入参数  : pstLteSearchedPlmnInfo - lte的searched plmn info ind消息内容
 输出参数  : pstSearchedExistPlmnInfo - 搜网列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月1日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_BuildSearchedPlmnInfoByLteSearchedPlmnInfoInd(
    LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU                    *pstLteSearchedPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo
)
{
    VOS_UINT32                                             i;
    VOS_UINT32                                             ulPlmnNum;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                           enPlmnType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                 *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   stGuNasPlmn;

    /* 获取选网列表 */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulPlmnNum       = 0;
    i               = 0;
    enPlmnType      = NAS_MMC_PLMN_TYPE_BUTT;
    PS_MEM_SET(&stGuNasPlmn, 0, sizeof(stGuNasPlmn));


    /*  将存在的网络加入roam搜网列表 */
    for (i = 0; i < pstLteSearchedPlmnInfo->ulTaiNum; i++)
    {
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&pstLteSearchedPlmnInfo->stTaiList[i].stPlmnId,
                                            &stGuNasPlmn);

        ulPlmnNum = pstSearchedExistPlmnInfo->usSearchPlmnNum;

        if (ulPlmnNum >= NAS_MMC_MAX_ROAM_PLMN_NUM_IN_SELECTION_LIST)
        {
            return;
        }

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.stPlmnId = stGuNasPlmn;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[0]              = pstLteSearchedPlmnInfo->stTaiList[i].stTac.ucTac;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[1]              = pstLteSearchedPlmnInfo->stTaiList[i].stTac.ucTacCnt;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus  =  NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus)
        {
            pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        }

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.enRat    = NAS_MML_NET_RAT_TYPE_LTE;

        enPlmnType = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enPlmnType  = enPlmnType;
        pstSearchedExistPlmnInfo->usSearchPlmnNum++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildSearchedPlmnInfoByRrcSearchedPlmnInfoInd
 功能描述  : 将RRMM_SEARCHED_PLMN_INFO_IND消息中带上来的网络按
             NAS_MMC_ROAM_PLMN_INFO_STRU结构提取到NAS_MMC_ROAM_PLMN_LIST_INFO_STRU列表中
 输入参数  : pstSearchedPlmnInfoMsg   - rrmm searched plmn info ind消息内容
 输出参数  : pstSearchedExistPlmnInfo - 漫游网络搜网列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月1日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_BuildSearchedPlmnInfoByRrcSearchedPlmnInfoInd(
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU   *pstSearchedExistPlmnInfo
)
{
    VOS_UINT32                                             i;
    VOS_UINT32                                             ulPlmnNum;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                           enPlmnType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                 *pstPlmnSrchList   = VOS_NULL_PTR;
    RRC_NAS_RAT_TYPE_ENUM_UINT32                           enRrcRatType;
    NAS_MMC_NET_STATUS_ENUM_UINT8                          enNetStatus;

    enPlmnType   = NAS_MMC_PLMN_TYPE_BUTT;
    ulPlmnNum    = 0;
    enRrcRatType = RRC_NAS_RAT_TYPE_BUTT;
    i            = 0;

    /* 获取选网列表 */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    for (i = 0; i < pstSearchedPlmnInfoMsg->ulAvailPlmnNum; i++)
    {
        ulPlmnNum = pstSearchedExistPlmnInfo->usSearchPlmnNum;

        if (ulPlmnNum >= NAS_MMC_MAX_ROAM_PLMN_NUM_IN_SELECTION_LIST)
        {
            return;
        }

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.stPlmnId.ulMcc = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].stPlmnId.ulMcc;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.stPlmnId.ulMnc = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].stPlmnId.ulMnc;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[0]              = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].usLac & 0x00FF;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[1]              = (pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].usLac & 0xFF00) >> 8;

        enRrcRatType = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].ulRat;
        NAS_MMC_ConvertRrcRatToNasFormat(enRrcRatType, &pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.enRat);

        /* 该网络状态需要从总的搜网列表中先查询下，如果状态已经是register，
           重新插入时需要使用搜网列表中状态，不能默认更新为searched exist否则会导致多次搜索*/
        enNetStatus = NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED == enNetStatus)
        {
            pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_REGISTERED;
        }
        else
        {
            pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        }

        enPlmnType = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enPlmnType  = enPlmnType;
        pstSearchedExistPlmnInfo->usSearchPlmnNum++;
    }

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnExistInRoamPlmnList
 功能描述  : 判断plmn是否在漫游搜网列表中
 输入参数  : pstPlmnId            - 网络信息
             pstNewRoamPlmnSelectionList - 漫游搜网列表
 返 回 值  : 无
 调用函数  : VOS_TRUE  - 存在
             VOS_FALSE - 不存在
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月1日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnExistInRoamPlmnList(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnId,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU   *pstNewRoamPlmnSelectionList
)
{
    VOS_UINT32                          i;

    for (i = 0; i < pstNewRoamPlmnSelectionList->usSearchPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstPlmnId->stPlmnId,
                      &pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildRoamPlmnSelectionPlmnInfo
 功能描述  : 构造漫游选网列表中单个漫游PLMN信息
 输入参数  : pstPlmnWithRat - 网络信息
 输出参数  : pstRoamPlmnInfo - 漫游plmn信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_VOID NAS_MMC_BuildRoamPlmnSelectionPlmnInfo(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat,
    NAS_MMC_ROAM_PLMN_INFO_STRU        *pstPlmnInfo
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stRoamPlmnInfo;
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus;

    PS_MEM_SET(&stRoamPlmnInfo, 0, sizeof(stRoamPlmnInfo));

    pstPlmnSelectionList                        = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    stRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
    stRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;
    stRoamPlmnInfo.stPlmnWithRat.enRat          = pstPlmnWithRat->enRat;

    /* 该网络状态需要从总的搜网列表中先查询下，如果状态已经是searched no exist或register
       或exist，重新插入时需要使用搜网列表中状态，不能默认更新为no searched否则会导致多次搜索*/
    enNetStatus = NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&stRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);

    if (NAS_MMC_NET_STATUS_BUTT != enNetStatus)
    {
        stRoamPlmnInfo.enNetStatus = enNetStatus;
    }
    else
    {
        stRoamPlmnInfo.enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
    }

    stRoamPlmnInfo.enPlmnType = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&stRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);
    stRoamPlmnInfo.aucLac[0]  = NAS_MML_LAC_LOW_BYTE_INVALID;
    stRoamPlmnInfo.aucLac[1]  = NAS_MML_LAC_HIGH_BYTE_INVALID;

    PS_MEM_CPY(pstPlmnInfo, &stRoamPlmnInfo, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SortRoamPlmnSelectionList
 功能描述  : 对漫游搜网列表排序
 输入参数  : pstPrioRatList       - 接入优先级
             ulRoamPlmnListNum    - 漫游列表网络个数
 输出参数  : pstRoamPlmnList      - 漫游搜网列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月1日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2015年7月9日
   作    者   : z00161729
   修改内容   : DTS2015071001632:开机漫游搜网如果报上来的漫游网络全部是禁止网络或全在nplmn中，
                则存在构造的漫游网络列表为0个，0减1会出现全F的大数导致死循环，单板复位
*****************************************************************************/
VOS_VOID NAS_MMC_SortRoamPlmnSelectionList(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList,
    VOS_UINT32                          ulRoamPlmnListNum,
    NAS_MMC_ROAM_PLMN_INFO_STRU        *pstRoamPlmnList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT32                          ulHighPrioRoamPlmnIndex;
    NAS_MMC_ROAM_PLMN_INFO_STRU         stHighPrioRoamPlmnInfo;

    PS_MEM_SET(&stHighPrioRoamPlmnInfo, 0, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));

    if (0 == ulRoamPlmnListNum)
    {
        return;
    }

    for (i = 0; i < ulRoamPlmnListNum - 1; ++i)
    {
        ulHighPrioRoamPlmnIndex = i;

        for (j = i + 1; j < ulRoamPlmnListNum; ++j)
        {
            /* 修改函数名 */
            if (1 == NAS_MMC_CompareRoamPlmnPrio(&pstRoamPlmnList[j],&pstRoamPlmnList[ulHighPrioRoamPlmnIndex],pstPrioRatList))
            {
                ulHighPrioRoamPlmnIndex = j;
            }
        }

        PS_MEM_CPY(&stHighPrioRoamPlmnInfo, &pstRoamPlmnList[ulHighPrioRoamPlmnIndex],sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));
        PS_MEM_CPY(&pstRoamPlmnList[ulHighPrioRoamPlmnIndex], &pstRoamPlmnList[i],sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));
        PS_MEM_CPY(&pstRoamPlmnList[i], &stHighPrioRoamPlmnInfo, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddDplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo
 功能描述  : 根据接入层带上来的存在网络，将DPLMN List中与SearchedExistPlmn同属一个国家的PLMN加入到漫游搜网列表
 输入参数  : pstSearchedExistPlmnInfo    - 存在网络信息
 输出参数  : pstNewRoamPlmnSelectionList - 漫游搜网列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月10日
   作    者   : l00289540
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_AddDplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stRoamPlmnInfo;
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;

    pstDPlmnNPlmnCfgInfo     = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    i                        = 0;
    j                        = 0;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));
    PS_MEM_SET(&stRoamPlmnInfo, 0, sizeof(stRoamPlmnInfo));

    /* 如果TAF_MMA_GetNetworkNameTblAddr中信息不全，DPLMN中的网络不在
       TAF_MMA_GetNetworkNameTblAddr中，存在DPLMN没有加入漫游列表情况，优先加入DPLMN中网络*/
    for (i = 0; i < pstSearchedExistPlmnInfo->usSearchPlmnNum; i++)
    {
        for (j = 0; j < pstDPlmnNPlmnCfgInfo->usDplmnListNum; j++)
        {
            stPlmnWithRat.stPlmnId.ulMcc = pstDPlmnNPlmnCfgInfo->astDPlmnList[j].stSimPlmnWithRat.stPlmnId.ulMcc;
            stPlmnWithRat.stPlmnId.ulMnc = pstDPlmnNPlmnCfgInfo->astDPlmnList[j].stSimPlmnWithRat.stPlmnId.ulMnc;
            stPlmnWithRat.enRat = NAS_MMC_ConvertSimRatToNetRat(pstDPlmnNPlmnCfgInfo->astDPlmnList[j].stSimPlmnWithRat.usSimRat);

            if (VOS_TRUE == NAS_MML_IsPlmnMccBelongToTheSameCountry(stPlmnWithRat.stPlmnId.ulMcc,
                                                pstSearchedExistPlmnInfo->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId.ulMcc))
            {
                if (VOS_TRUE == NAS_MMC_IsPlmnExistInRoamPlmnList(&stPlmnWithRat, pstNewRoamPlmnSelectionList))
                {
                    continue;
                }

                if (NAS_MML_NET_RAT_TYPE_BUTT != stPlmnWithRat.enRat)
                {
                    NAS_MMC_BuildRoamPlmnSelectionPlmnInfo(&stPlmnWithRat, &stRoamPlmnInfo);
                    NAS_MMC_AddSearchedPlmnInRoamPlmnSelectionList(&stRoamPlmnInfo, pstNewRoamPlmnSelectionList);
                }
            }
        }
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddUOplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo
 功能描述  : 根据接入层带上来的存在网络，将UPLMN/OPLMN L List中与SearchedExistPlmn同属一个国家的PLMN加入到漫游搜网列表
 输入参数  : pstSearchedExistPlmnInfo    - 存在网络信息
 输出参数  : pstNewRoamPlmnSelectionList - 漫游搜网列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月10日
   作    者   : l00289540
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_AddUOplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stRoamPlmnInfo;
    VOS_UINT32                                              i = 0;
    VOS_UINT32                                              j = 0;
    VOS_UINT32                                              k = 0;

    pstPlmnSelectionList     = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));
    PS_MEM_SET(&stRoamPlmnInfo, 0, sizeof(stRoamPlmnInfo));

    /* 如果TAF_MMA_GetNetworkNameTblAddr中信息不全，UPLMN/OPLMN中的网络不在
     * TAF_MMA_GetNetworkNameTblAddr中，存在UPLMN/OPLMN没有加入漫游列表情况，优先加入UPLMN/OPLMN中网络*/
    for (i = 0; i < pstSearchedExistPlmnInfo->usSearchPlmnNum; i++)
    {
        for (j = 0; j < pstPlmnSelectionList->usSearchPlmnNum; j++)
        {
            if ((NAS_MMC_PLMN_TYPE_UPLMN == pstPlmnSelectionList->astPlmnSelectionList[j].enPlmnType)
             || (NAS_MMC_PLMN_TYPE_OPLMN == pstPlmnSelectionList->astPlmnSelectionList[j].enPlmnType))
            {
                stPlmnWithRat.stPlmnId.ulMcc = pstPlmnSelectionList->astPlmnSelectionList[j].stPlmnId.ulMcc;
                stPlmnWithRat.stPlmnId.ulMnc = pstPlmnSelectionList->astPlmnSelectionList[j].stPlmnId.ulMnc;

                if (VOS_TRUE == NAS_MML_IsPlmnMccBelongToTheSameCountry(stPlmnWithRat.stPlmnId.ulMcc,
                                                pstSearchedExistPlmnInfo->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId.ulMcc))
                {
                    if (VOS_TRUE == NAS_MMC_IsPlmnExistInRoamPlmnList(&stPlmnWithRat, pstNewRoamPlmnSelectionList))
                    {
                        continue;
                    }

                    for(k = 0; k< pstPlmnSelectionList->astPlmnSelectionList[j].ucRatNum; k++)
                    {
                        stPlmnWithRat.enRat          = pstPlmnSelectionList->astPlmnSelectionList[j].astPlmnRatInfo[k].enRatType;

                        if (NAS_MML_NET_RAT_TYPE_BUTT != stPlmnWithRat.enRat)
                        {
                            NAS_MMC_BuildRoamPlmnSelectionPlmnInfo(&stPlmnWithRat, &stRoamPlmnInfo);
                            NAS_MMC_AddSearchedPlmnInRoamPlmnSelectionList(&stRoamPlmnInfo, pstNewRoamPlmnSelectionList);
                        }
                    }
                }
            }
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddOtherPlmnToRoamPlmnSelectionListBySearchedExistPlmnInfo
 功能描述  : 根据接入层带上来的存在网络，将TAF_MMA_GetNetworkNameTblAddr中与SearchedExistPlmn
             同属一个国家且未在漫游搜网列表内的PLMN加入到列表中
 输入参数  : pstSearchedExistPlmnInfo    - 存在网络信息
 输出参数  : pstNewRoamPlmnSelectionList - 漫游搜网列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月10日
   作    者   : l00289540
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_AddOtherPlmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
)
{
    TAF_PH_OPERATOR_NAME_TBL_STRU                          *pstNetworkNameTbl = VOS_NULL_PTR;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stRoamPlmnInfo;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    VOS_UINT16                                              usTotalNtwkNum;
    VOS_UINT8                                               ucPlmnMncNum;
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;

    usTotalNtwkNum           = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl        = TAF_MMA_GetNetworkNameTblAddr();
    i                        = 0;
    j                        = 0;
    ucPlmnMncNum             = 0;
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));
    PS_MEM_SET(&stRoamPlmnInfo, 0, sizeof(stRoamPlmnInfo));

    /* 查找和存在网络相同国家码的所有plmn，加入roam搜网列表，排序后插入搜网列表 */
    for (i = 0; i < pstSearchedExistPlmnInfo->usSearchPlmnNum; i++)
    {
        for (j = 0; j < usTotalNtwkNum; j++)
        {
            stPlmnWithRat.stPlmnId.ulMcc = pstNetworkNameTbl[j].PlmnId.Mcc;
            stPlmnWithRat.stPlmnId.ulMnc = pstNetworkNameTbl[j].PlmnId.Mnc;
            stPlmnWithRat.enRat          = pstSearchedExistPlmnInfo->astPlmnSelectionList[i].stPlmnWithRat.enRat;

            ucPlmnMncNum = pstNetworkNameTbl[j].ucMncLength;
            NAS_MMC_ConvertPlmnId2NasFormat(&stPlmnWithRat.stPlmnId,ucPlmnMncNum);

            if (VOS_TRUE == NAS_MML_IsPlmnMccBelongToTheSameCountry(stPlmnWithRat.stPlmnId.ulMcc,
                                            pstSearchedExistPlmnInfo->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId.ulMcc))
            {
                if (VOS_TRUE == NAS_MMC_IsPlmnExistInRoamPlmnList(&stPlmnWithRat, pstNewRoamPlmnSelectionList))
                {
                    continue;
                }

                NAS_MMC_BuildRoamPlmnSelectionPlmnInfo(&stPlmnWithRat, &stRoamPlmnInfo);
                NAS_MMC_AddSearchedPlmnInRoamPlmnSelectionList(&stRoamPlmnInfo, pstNewRoamPlmnSelectionList);
            }
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo
 功能描述  : 根据接入层带上来的存在网络构造漫游搜网列表
 输入参数  : enRat                       - 接入技术
             pstSearchedExistPlmnInfo    - 存在网络信息
 输出参数  : pstNewRoamPlmnSelectionList - 漫游搜网列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月1日
   作    者   : z00161729
   修改内容   : 新生成函数

 2.日    期   : 2015年10月9日
   作    者   : l00289540
   修改内容   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 修改
 3.日    期   : 2016年1月5日
   作    者   : s00217060
   修改内容   : DTS2015120406613:漫游时只打断不排序

*****************************************************************************/
VOS_VOID NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                              stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    i                        = 0;
    PS_MEM_SET(&stPrioRatList, 0, sizeof(stPrioRatList));

    /*  将存在的网络加入roam搜网列表最前面 */
    for (i = 0; i < pstSearchedExistPlmnInfo->usSearchPlmnNum; i++)
    {
        NAS_MMC_AddSearchedPlmnInRoamPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[i], pstNewRoamPlmnSelectionList);
    }

    if (VOS_TRUE == NAS_MMC_GetSrchUOplmnPriorToDplmnFlg())
    {
        NAS_MMC_AddUOplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(pstSearchedExistPlmnInfo, pstNewRoamPlmnSelectionList);

        NAS_MMC_AddDplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(pstSearchedExistPlmnInfo, pstNewRoamPlmnSelectionList);

        NAS_MMC_AddOtherPlmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(pstSearchedExistPlmnInfo, pstNewRoamPlmnSelectionList);
    }
    else
    {
        NAS_MMC_AddDplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(pstSearchedExistPlmnInfo, pstNewRoamPlmnSelectionList);

        NAS_MMC_AddUOplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(pstSearchedExistPlmnInfo, pstNewRoamPlmnSelectionList);

        NAS_MMC_AddOtherPlmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(pstSearchedExistPlmnInfo, pstNewRoamPlmnSelectionList);
    }

    /* 对临时搜网列表进行排序，如果在搜DPLMN前优先搜UPLMN/OPLMN特性打开，则排序原则为:DPLMN->UPLMN->OPLMN->AVAILABLE
     * 否则，排序原则为:UPLMN->OPLMN->DPLMN->AVAILABLE
     */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 向选网列表中增加接入层报上来的网络，当前搜网接入技术优先 */
    NAS_MML_SortSpecRatPrioHighest(enRat, &stPrioRatList);

    NAS_MMC_SortRoamPlmnSelectionList(&stPrioRatList, pstNewRoamPlmnSelectionList->usSearchPlmnNum,
                  pstNewRoamPlmnSelectionList->astPlmnSelectionList);

    /* 排序之后个数为0时增加异常打印 */
    if (0 == pstNewRoamPlmnSelectionList->usSearchPlmnNum)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo: usSearchPlmnNum is 0");
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList
 功能描述  : 更新搜网列表中指定PLMN的网络状态信息
 输入参数  : pstPlmn
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月29日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmn,
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                             i;

    /* 将该PLMN及其接入技术与搜网列表中每个PLMN及其接入技术比较 */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        /* 比较pstPlmn->stPlmnId,与pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId */
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmn->stPlmnId),
                                                           &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId)))
        {
            /* 如果相同，更新搜网列表中PLMN对应接入技术的信息 */
            NAS_MMC_UpdateRatNetStatusInPlmnRatInfo(pstPlmn->enRat,
                                                    enNetStatus,
                                                    &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]));
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSpecQualAvailPlmnInPlmnSelectionList
 功能描述  : 获取搜网列表中类型为available的对应质量网络
 输入参数  : pstPlmnSelectionList,列表信息
             enPlmnQuality,要提取网络的质量
 输出参数  : pstPlmnSelectionList,列表信息
             pstAvailPlmnList,提取后存储的列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月19日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2014年8月28日
   作    者   : z00161729
   修改内容   : available网络个数申请内存不足，会导致拷贝越界单板复位
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetSpecQualAvailPlmnInPlmnSelectionList(
    VOS_UINT32                                              ulAvailPlmnListNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstAvailPlmnList,
    NAS_MMC_NET_QUALITY_ENUM_UINT8                          enPlmnQuality,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulPlmnNum;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnSelectionPlmnInfo = VOS_NULL_PTR;

    ulPlmnNum = 0x0;

    /* 将搜网列表中属性为AVAIL信号质量为enPlmnQuality的网络找出 */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        pstPlmnSelectionPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);

        if (NAS_MMC_PLMN_TYPE_AVAIL_PLMN == pstPlmnSelectionPlmnInfo->enPlmnType)
        {
            /* 循环查找所有的接入技术，找出对应接入技术质量为enPlmnQuality的网络 */
            for (j = 0; j < pstPlmnSelectionPlmnInfo->ucRatNum; j++)
            {
                if (enPlmnQuality == pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enQuality)
                {
                    /* 初始化选网信息 */
                    NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                       NAS_MML_INVALID_SIM_RAT,
                                                       &(pstPlmnSelectionPlmnInfo->stPlmnId),
                                                       &(pstAvailPlmnList[ulPlmnNum]));

                    /* 获取该PLMN相关信息 */
                    PS_MEM_CPY(&pstAvailPlmnList[ulPlmnNum].astPlmnRatInfo[0],
                               &(pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j]),
                               sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));

                    pstAvailPlmnList[ulPlmnNum].ucRatNum++;

                    ulPlmnNum ++;

                    if (ulPlmnNum >= ulAvailPlmnListNum)
                    {
                       return ulPlmnNum;
                    }
                }
            }
        }
    }

    return ulPlmnNum;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SortRatPrioSpecRat
 功能描述  : 将第一个参数指定接入技术调整在第二个之前
 输入参数  : enPrioRat
             enRat
 输出参数  : pstPrioRatList,接入技术优先顺序
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月19日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SortRatPrioSpecRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enPrioRat,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulPrioRatIndex;
    VOS_UINT32                          ulRatIndex;
    VOS_UINT32                          ulFoundPrioRatFlg;
    VOS_UINT32                          ulFoundRatFlg;

    ulPrioRatIndex    = 0x0;
    ulRatIndex        = 0x0;

    ulFoundPrioRatFlg = VOS_FALSE;
    ulFoundRatFlg     = VOS_FALSE;

    /* 找出优先接入技术和非优先接入技术的位置 */
    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        if (enPrioRat == pstPrioRatList->aucRatPrio[i])
        {
            ulPrioRatIndex    = i;
            ulFoundPrioRatFlg = VOS_TRUE;
        }

        if (enRat == pstPrioRatList->aucRatPrio[i])
        {
            ulRatIndex        = i;
            ulFoundRatFlg     = VOS_TRUE;
        }
    }

    /* 如果当前不支持优先接入技术,不需要排序 */
    if ((VOS_FALSE == ulFoundPrioRatFlg)
     || (VOS_FALSE == ulFoundRatFlg))
    {
        return;
    }

    /* 如果前者优先级低，需要调整，将优先的移到前面 */
    if (ulPrioRatIndex > ulRatIndex)
    {
        (VOS_VOID)PS_MEM_MOVE(&(pstPrioRatList->aucRatPrio[ulRatIndex+1]),
                    &(pstPrioRatList->aucRatPrio[ulRatIndex]),
                    (ulPrioRatIndex-ulRatIndex)*sizeof(NAS_MML_NET_RAT_TYPE_ENUM_UINT8));

        pstPrioRatList->aucRatPrio[ulRatIndex] = enPrioRat;
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MMC_SortPlmnListRandom
 功能描述  : 对搜网列表中PLMN进行随机排序
 输入参数  : pstPlmnSelectionList,列表信息
             ulPlmnNum,PLMN个数
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月19日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2013年5月20日
   作    者   : s00217060
   修改内容   : coverity和foritfy修改

*****************************************************************************/
VOS_VOID NAS_MMC_SortPlmnListRandom(
    VOS_UINT32                                              ulPlmnNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnList
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU  stTempPlmnInfo;
    VOS_UINT32                             ulPlmnListNum;
    VOS_UINT32                             ulRand;

    ulPlmnListNum = ulPlmnNum;

    /* Modified by s00217060 for coverity和foritfy修改 , 2013-05-20, begin */
    /* 随机种子 */
    VOS_SetSeed(VOS_GetTick());

    for (; ulPlmnListNum > 1; ulPlmnListNum--)
    {
        /* 获取随机数 */
        ulRand = VOS_Rand(ulPlmnListNum);
        if (ulRand >  (ulPlmnListNum - 1))
        {
            continue;
        }

        stTempPlmnInfo               = pstPlmnList[ulRand];
        pstPlmnList[ulRand]          = pstPlmnList[ulPlmnListNum-1];
        pstPlmnList[ulPlmnListNum-1] = stTempPlmnInfo;
    }
    /* Modified by s00217060 for coverity和foritfy修改 , 2013-05-20, end */

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SortPlmnListPrioRat
 功能描述  : 对搜网列表中PLMN按接入技术优先顺序排序
 输入参数  : pstPlmnSelectionList,列表信息
             *pulPlmnNum,PLMN个数
             pstPrioRatList,指定的接入技术优先顺序
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月19日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SortPlmnListPrioRat(
    VOS_UINT32                                             *pulPlmnNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnList,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulTmpPlmnNum;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstTmpPlmnList = VOS_NULL_PTR;

    /* PlmnNum个数为0时，无须排序 */
    if (0 == (*pulPlmnNum))
    {
        return;
    }

    pstTmpPlmnList = (NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   ((*pulPlmnNum)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU)));

    if (VOS_NULL_PTR == pstTmpPlmnList)
    {
        /* 打印异常 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SortPlmnListPrioRat: Mem alloc fail.");

        return;
    }

    ulTmpPlmnNum = 0x0;

    /*排序方法是,循环所有的接入技术,将最高优先级的接入技术网络放到最后，一轮外循环后保证最高优
      先级接入技术的网络都在最前面，接着对数组后面网络以相同方式排序 */
    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        for (j = 0; j < (*pulPlmnNum); j++)
        {
            if (pstPrioRatList->aucRatPrio[i] == pstPlmnList[j].astPlmnRatInfo[0].enRatType)
            {
                PS_MEM_CPY(&pstTmpPlmnList[ulTmpPlmnNum], &pstPlmnList[j], sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
                ulTmpPlmnNum++;
            }
        }
    }

    *pulPlmnNum = ulTmpPlmnNum;

    PS_MEM_CPY(pstPlmnList, pstTmpPlmnList, (ulTmpPlmnNum*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU)));

    PS_MEM_FREE(WUEPS_PID_MMC, pstTmpPlmnList);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SortPlmnListSignalDecrease
 功能描述  : 对搜网列表中PLMN按信号递减排序
 输入参数  : pstPlmnSelectionList,列表信息
             ulPlmnNum,PLMN个数
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月19日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SortPlmnListSignalDecrease(
    VOS_UINT32                                              ulPlmnNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnList
)
{
    /* 不同接入技术的质量标准不一致，暂未确定排序方法 */

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SortAvailPlmnInPlmnSelectionList
 功能描述  : 对搜网列表中高低质量的available plmn进行排序
 输入参数  : pstPlmnSelectionList,列表信息
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月29日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2012年03月03日
   作    者   : s62952
   修改内容   : BalongV300R002 Build优化项目:使用NV替换NAS_FEATURE_SUPPORT_H3G_REQ宏
 3.日    期   : 2013年12月13日
   作    者   : z00161729
   修改内容   : DTS2013121206933:非高优先级可用高低质量的网络按syscfg设置接入技术优先级排序，9055 nv项控制

*****************************************************************************/
VOS_VOID NAS_MMC_SortAvailPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstHighQualityAvailPlmnList  = VOS_NULL_PTR;
    VOS_UINT32                             ulHighQualityAvailPlmnNum;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstLowQualityAvailPlmnList   = VOS_NULL_PTR;
    VOS_UINT32                             ulLowQualityAvailPlmnNum;
    NAS_MML_PLMN_RAT_PRIO_STRU             stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU            *pstPrioRatList;

    VOS_UINT32                             ulAvailPlmnListNum;

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    ulAvailPlmnListNum = NAS_MML_MAX_RAT_NUM * RRC_MAX_HIGH_PLMN_NUM;

    pstHighQualityAvailPlmnList = (NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   (NAS_MML_MAX_RAT_NUM*RRC_MAX_HIGH_PLMN_NUM)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

    if (VOS_NULL_PTR == pstHighQualityAvailPlmnList)
    {
        /* 打印异常 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SortAvailPlmnInPlmnSelectionList: Mem alloc fail.");

        return;
    }

    pstLowQualityAvailPlmnList  = (NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   (NAS_MML_MAX_RAT_NUM*RRC_MAX_HIGH_PLMN_NUM)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

    if (VOS_NULL_PTR == pstLowQualityAvailPlmnList)
    {
        /* 打印异常 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SortAvailPlmnInPlmnSelectionList: Mem alloc fail.");

        PS_MEM_FREE(WUEPS_PID_MMC, pstHighQualityAvailPlmnList);

        return;
    }

    /* 将搜网列表中属性为Availabe质量为高的PLMN取出 */
    ulHighQualityAvailPlmnNum = NAS_MMC_GetSpecQualAvailPlmnInPlmnSelectionList(ulAvailPlmnListNum,
                                                                            pstHighQualityAvailPlmnList,
                                                                            NAS_MMC_NET_HIGH_QUALITY,
                                                                            pstPlmnSelectionListInfo);

    /* 将搜网列表中属性为Availabe质量为低的PLMN取出 */
    ulLowQualityAvailPlmnNum = NAS_MMC_GetSpecQualAvailPlmnInPlmnSelectionList(ulAvailPlmnListNum,
                                                                            pstLowQualityAvailPlmnList,
                                                                            NAS_MMC_NET_LOW_QUALITY,
                                                                            pstPlmnSelectionListInfo);


    /* 将搜网列表中属性为Availabe质量为高的PLMN删除 */
    NAS_MMC_DeleteSpecQualAvailPlmnInPlmnSelectionList(NAS_MMC_NET_HIGH_QUALITY, pstPlmnSelectionListInfo);

    /* 将搜网列表中属性为Availabe质量为低的PLMN删除 */
    NAS_MMC_DeleteSpecQualAvailPlmnInPlmnSelectionList(NAS_MMC_NET_LOW_QUALITY, pstPlmnSelectionListInfo);

    /* 对高质量PLMN进行随机排序 */
    NAS_MMC_SortPlmnListRandom(ulHighQualityAvailPlmnNum, pstHighQualityAvailPlmnList);

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if (NAS_MMC_NV_ITEM_ACTIVE == pstMiscellaneousCfgInfo->ucWcdmaPriorityGsmFlg)
    {
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        stPrioRatList  = *pstPrioRatList;

        /* 将 W的接入技术移动到 G的前面 */
        NAS_MMC_SortRatPrioSpecRat(NAS_MML_NET_RAT_TYPE_WCDMA,
                                   NAS_MML_NET_RAT_TYPE_GSM,
                                  &stPrioRatList);

        NAS_MMC_SortPlmnListPrioRat(&ulHighQualityAvailPlmnNum,
                                        pstHighQualityAvailPlmnList,
                                        &stPrioRatList);
    }
    else if (NAS_MMC_NV_ITEM_ACTIVE == pstMiscellaneousCfgInfo->ucSortAvailalePlmnListRatPrioFlg)
    {
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        stPrioRatList  = *pstPrioRatList;

        /* 高质量网络按syscfg设置优先级排序 */
        NAS_MMC_SortPlmnListPrioRat(&ulHighQualityAvailPlmnNum,
                                     pstHighQualityAvailPlmnList,
                                    &stPrioRatList);

        /* 低质量网络按syscfg设置优先级排序 */
        NAS_MMC_SortPlmnListPrioRat(&ulLowQualityAvailPlmnNum,
                                     pstLowQualityAvailPlmnList,
                                    &stPrioRatList);
    }
    else
    {
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* 对低质量PLMN进行按信号递减排序 */
    NAS_MMC_SortPlmnListSignalDecrease(ulLowQualityAvailPlmnNum, pstLowQualityAvailPlmnList);



    /* 将高质量PLMN再放回选网列表 */
    NAS_MMC_SaveAvailablePlmnInPlmnSelectionList(ulHighQualityAvailPlmnNum,
                                                 pstHighQualityAvailPlmnList,
                                                 pstPlmnSelectionListInfo);

    /* 将低质量PLMN在放回搜网列表 */
    NAS_MMC_SaveAvailablePlmnInPlmnSelectionList(ulLowQualityAvailPlmnNum,
                                                 pstLowQualityAvailPlmnList,
                                                 pstPlmnSelectionListInfo);

    PS_MEM_FREE(WUEPS_PID_MMC, pstHighQualityAvailPlmnList);

    PS_MEM_FREE(WUEPS_PID_MMC, pstLowQualityAvailPlmnList);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_DeleteEPlmnInPlmnSelectionList
 功能描述  : 将搜网列表中属性为enPlmnType的网络删除
 输入参数  : enPlmnType
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月29日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                             i;

    i = 0;

    /* 将搜网列表中属性为enPlmnType的网络删除 */
    while (i < pstPlmnSelectionListInfo->usSearchPlmnNum)
    {
        if (enPlmnType == pstPlmnSelectionListInfo->astPlmnSelectionList[i].enPlmnType)
        {
            pstPlmnSelectionListInfo->usSearchPlmnNum--;

            (VOS_VOID)PS_MEM_MOVE(&pstPlmnSelectionListInfo->astPlmnSelectionList[i],
                        &pstPlmnSelectionListInfo->astPlmnSelectionList[i+1],
                        (pstPlmnSelectionListInfo->usSearchPlmnNum-i)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

            continue;
        }

        i++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_DeleteSpecQualAvailPlmnInPlmnSelectionList
 功能描述  : 删除指定质量的Available网络
 输入参数  : enNetQuality
 输出参数  : pstPlmnSelectionListInfo,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月28日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2013年8月26日
   作    者   : w00242748
   修改内容   : DTS2013071808373编译告警清理
*****************************************************************************/
VOS_VOID NAS_MMC_DeleteSpecQualAvailPlmnInPlmnSelectionList(
    NAS_MMC_NET_QUALITY_ENUM_UINT8                          enNetQuality,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo = VOS_NULL_PTR;

    i = 0;

    /* 将搜网列表中属性为AVAIL信号质量为enNetQuality的网络找出 */
    while (i < pstPlmnSelectionListInfo->usSearchPlmnNum)
    {
        pstPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);
        if (NAS_MMC_PLMN_TYPE_AVAIL_PLMN == pstPlmnInfo->enPlmnType)
        {
            j = 0;

            /* 循环查找所有的接入技术，找出对应接入技术质量为enPlmnQuality的网络 */
            while (j < pstPlmnInfo->ucRatNum)
            {
                if (enNetQuality == pstPlmnInfo->astPlmnRatInfo[j].enQuality)
                {
                    /* 从搜网列表中将该PLMN对应的接入技术信息清除 */
                    pstPlmnInfo->ucRatNum --;

                    if (j < (NAS_MML_MAX_RAT_NUM - 1))
                    {
                        (VOS_VOID)PS_MEM_MOVE(&pstPlmnInfo->astPlmnRatInfo[j],
                                    &pstPlmnInfo->astPlmnRatInfo[j+1],
                                    (pstPlmnInfo->ucRatNum - j)*sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                    }

                    pstPlmnInfo->astPlmnRatInfo[pstPlmnInfo->ucRatNum].enRatType     = NAS_MML_NET_RAT_TYPE_BUTT;
                    pstPlmnInfo->astPlmnRatInfo[pstPlmnInfo->ucRatNum].enQuality     = NAS_MMC_NET_QUALITY_BUTT;
                    pstPlmnInfo->astPlmnRatInfo[pstPlmnInfo->ucRatNum].enNetStatus   = NAS_MMC_NET_STATUS_BUTT;

                    continue;
                }
                j++;
            }

            /* 删除该网络对应接入技术信息后，如果其不支持任何接入技术，则从列表中删除该网络 */
            if (0 == pstPlmnInfo->ucRatNum)
            {
                pstPlmnSelectionListInfo->usSearchPlmnNum--;

                if (i < (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST - 1))
                {
                    (VOS_VOID)PS_MEM_MOVE(&pstPlmnSelectionListInfo->astPlmnSelectionList[i],
                                &pstPlmnSelectionListInfo->astPlmnSelectionList[i+1],
                                (pstPlmnSelectionListInfo->usSearchPlmnNum - i)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
                }
                continue;
            }
        }

        i++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_DeleteSpecNetStatusAvailPlmnInPlmnSelectionList
 功能描述  : 删除指定网络状态的网络
 输入参数  : enNetStatus
 输出参数  : pstPlmnSelectionListInfo,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年5月22日
   作    者   : s00246516
   修改内容   : 新生成函数:开机搜索RPLMN:23002成功，注册失败CS被拒17达到4次后,在刷新EPLMN时候，把所有的
                RPLMN信息都清楚了，后面又搜到23002，又发起搜网。
*****************************************************************************/
VOS_VOID NAS_MMC_DeleteSpecNetStatusAvailPlmnInPlmnSelectionList(
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo = VOS_NULL_PTR;

    i = 0;

    /* 将搜网列表中属性为AVAIL,网络状态为NO SEARCHED的网络找出 */
    while (i < pstPlmnSelectionListInfo->usSearchPlmnNum)
    {
        pstPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);
        if (NAS_MMC_PLMN_TYPE_AVAIL_PLMN == pstPlmnInfo->enPlmnType)
        {
            j = 0;

            /* 循环查找所有的接入技术，找出网络状态为NO SEARCHED的网络找出 */
            while (j < pstPlmnInfo->ucRatNum)
            {
                if (enNetStatus == pstPlmnInfo->astPlmnRatInfo[j].enNetStatus)
                {
                    /* 从搜网列表中将该PLMN对应的接入技术信息清除 */
                    pstPlmnInfo->ucRatNum --;

                    if (j < (NAS_MML_MAX_RAT_NUM - 1))
                    {
                        (VOS_VOID)PS_MEM_MOVE(&pstPlmnInfo->astPlmnRatInfo[j],
                                    &pstPlmnInfo->astPlmnRatInfo[j+1],
                                    (pstPlmnInfo->ucRatNum - j)*sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                    }

                    pstPlmnInfo->astPlmnRatInfo[pstPlmnInfo->ucRatNum].enRatType     = NAS_MML_NET_RAT_TYPE_BUTT;
                    pstPlmnInfo->astPlmnRatInfo[pstPlmnInfo->ucRatNum].enQuality     = NAS_MMC_NET_QUALITY_BUTT;
                    pstPlmnInfo->astPlmnRatInfo[pstPlmnInfo->ucRatNum].enNetStatus   = NAS_MMC_NET_STATUS_BUTT;

                    continue;
                }
                j++;
            }

            /* 删除该网络对应接入技术信息后，如果其不支持任何接入技术，则从列表中删除该网络 */
            if (0 == pstPlmnInfo->ucRatNum)
            {
                pstPlmnSelectionListInfo->usSearchPlmnNum--;

                if (i < (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST - 1))
                {
                    (VOS_VOID)PS_MEM_MOVE(&pstPlmnSelectionListInfo->astPlmnSelectionList[i],
                                &pstPlmnSelectionListInfo->astPlmnSelectionList[i+1],
                                (pstPlmnSelectionListInfo->usSearchPlmnNum - i)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
                }

                continue;
            }
        }

        i++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_DelSpecNetStatusRat
 功能描述  : 从stPrioRatList中删除网络状态为enNetStatus的接入技术
 输入参数  : enNetStatus  : 指定要删除的网络状态类型
              pstNetStatus : PLMNID的网络状态
 输出参数  : stPrioRatList : 接入技术优先级列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月13日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_DelSpecNetStatusRat(
    NAS_MMC_NET_STATUS_ENUM_UINT8       enNetStatus,
    NAS_MMC_NET_STATUS_ENUM_UINT8      *pstNetStatus,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;

    i = 0;

    /* 异常保护 */
    if (0x0 == pstPrioRatList->ucRatNum)
    {
        return;

    }

    /* 如果网络状态为enNetStatus，把该状态的接入技术从stPrioRatList中删除 */
    while (i < (VOS_UINT32)(pstPrioRatList->ucRatNum-1))
    {
        if (enNetStatus == pstNetStatus[i])
        {
            pstPrioRatList->aucRatPrio[i] = NAS_MML_NET_RAT_TYPE_BUTT;
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPrioRatList->aucRatPrio[i]),
                        &(pstPrioRatList->aucRatPrio[i+1]),
                        (NAS_MML_MAX_RAT_NUM-i-1));

            (VOS_VOID)PS_MEM_MOVE(&(pstNetStatus[i]),
                        &(pstNetStatus[i+1]),
                        (NAS_MML_MAX_RAT_NUM-i-1));
            /*lint +e961*/
            (pstPrioRatList->ucRatNum)--;

            continue;
        }
        i++;
    }

    /* 最后一个的处理 */
    if ((pstPrioRatList->ucRatNum > 0)
     && (enNetStatus == pstNetStatus[i]))
    {
        pstPrioRatList->aucRatPrio[i] = NAS_MML_NET_RAT_TYPE_BUTT;

        (pstPrioRatList->ucRatNum)--;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_ModifyPlmnTypeInPlmnSelectionList
 功能描述  : 更新搜网列表中属性为enSrcPlmnType的网络，修改其属性为enDestPlmnType
 输入参数  : enSrcPlmnType
             enDestPlmnType
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年6月29日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enSrcPlmnType,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enDestPlmnType,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                             i;

    /* 将搜网列表中属性为enSrcPlmnType的网络,修改其属性为enDestPlmnType */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        if (enSrcPlmnType == pstPlmnSelectionListInfo->astPlmnSelectionList[i].enPlmnType)
        {
            pstPlmnSelectionListInfo->astPlmnSelectionList[i].enPlmnType = enDestPlmnType;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextSearchPlmn
 功能描述  : 获取搜网列表中排在最前面的可以搜索的网络
 输入参数  : pstPlmnSelectionList,列表信息
             pstPrioRatList,优先级顺序
             ulUserSpecPlmnSearch,是否用户指定搜网
 输出参数  : pstDestPlmn
 返 回 值  : VOS_UINT32 VOS_TRUE :获取成功
                        VOS_FALSE:获取失败

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextSearchPlmn(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstDestPlmn,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList,
    VOS_UINT32                                              ulUserSpecPlmnSearch,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;
    VOS_UINT32                                              ulIsPlmnSearchingAllowed;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnSelectionPlmnInfo = VOS_NULL_PTR;

    /* 依次查找搜网列表中的每一个网络 */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        pstPlmnSelectionPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);

        /* 按SYSCFG设置的接入技术优先级依次查找 */
        for (k = 0; k < pstPrioRatList->ucRatNum; k++)
        {
            /* 依次查找一个网络的所有支持的接入技术 */
            for (j = 0; j < pstPlmnSelectionPlmnInfo->ucRatNum; j++)
            {
                /* 如果优先的接入技术与当前查找的网络支持的接入技术相同 */
                if (pstPrioRatList->aucRatPrio[k] == pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType)
                {
                    ulIsPlmnSearchingAllowed = NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy(&(pstPlmnSelectionPlmnInfo->stPlmnId),
                                                                                         pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType,
                                                                                         pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enNetStatus,
                                                                                         ulUserSpecPlmnSearch);
                    if (VOS_FALSE == ulIsPlmnSearchingAllowed)
                    {
                        /* 存储的接入技术不会有重复 */
                        break;
                    }

                    pstDestPlmn->stPlmnId = pstPlmnSelectionPlmnInfo->stPlmnId;
                    pstDestPlmn->enRat    = pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType;

                    return VOS_TRUE;
                }
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdatePlmnIdWithBCCHMnc
 功能描述  : 根据 BCCH的Mnc确定Sim卡中对应Plmn的Mnc的长度 ，便于在list搜网上报时处理
             调用函数需要保证,ulBcchMnc对应网络 与pstDestPlmnInfo对应网络是相同的
 输入参数  : ulBcchMnc
 输出参数  : pstDestPlmnId
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年2月27日
    作    者   : l00130025
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdatePlmnIdWithBCCHMnc(
    VOS_UINT32                          ulBcchMnc,
    NAS_MML_PLMN_ID_STRU               *pstDestPlmnId
)
{
    VOS_UINT8                           ucBcchMnc3;

    ucBcchMnc3 = (VOS_UINT8)((ulBcchMnc & 0x00ff0000) >> 16);

    if (0x0F == ucBcchMnc3)
    {
        pstDestPlmnId->ulMnc |= 0x0F0000;
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdatePlmnRatInfoInSearchList
 功能描述  : 根据PLMN ID和接入技术,从搜索列表中更新网络状态质量信息
 输入参数  : pstPlmnSearchInfo    已搜索的列表信息
 输出参数  : pstPlmnSelectionInfo,选网列表中某个网络
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_UpdatePlmnRatInfoInSearchList(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnSelectionInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo,
    VOS_UINT8                                               ucIsAllBandSearch

)
{
    VOS_UINT32                               i;
    VOS_UINT32                               j;

    for (i = 0; i < pstPlmnSelectionInfo->ucRatNum; i++)
    {
        if (pstPlmnSearchInfo->enRatType == pstPlmnSelectionInfo->astPlmnRatInfo[i].enRatType)
        {
            break;
        }
    }

    if (i == pstPlmnSelectionInfo->ucRatNum)
    {
        return VOS_FALSE;
    }

    /* pstPlmnSelectionInfo->stPlmnId是否在高质量列表中 */
    for (j = 0; j < pstPlmnSearchInfo->ulHighPlmnNum; j++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnSearchInfo->astHighPlmnList[j]),
                                                           &(pstPlmnSelectionInfo->stPlmnId)))
        {
            /* 如果当前网络当前接入技术状态为initial、not exist，则更新状态为存在，质量为高质量 */
            if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != pstPlmnSelectionInfo->astPlmnRatInfo[i].enNetStatus)
            {
                pstPlmnSelectionInfo->astPlmnRatInfo[i].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
            }
            pstPlmnSelectionInfo->astPlmnRatInfo[i].enQuality   = NAS_MMC_NET_HIGH_QUALITY;
            pstPlmnSelectionInfo->astPlmnRatInfo[i].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;

            /* BCCH中上报的Mnc有可能长度和SIM卡中存储的Mnc不一样，统一改为BCCH中的Mnc */
            pstPlmnSelectionInfo->stPlmnId.ulMnc = pstPlmnSearchInfo->astHighPlmnList[j].ulMnc;
            return VOS_TRUE;
        }
    }

    for (j = 0; j < pstPlmnSearchInfo->ulLowPlmnNum; j++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn((NAS_MML_PLMN_ID_STRU*)&(pstPlmnSearchInfo->astLowPlmnList[j].stPlmnId),
                                                           &(pstPlmnSelectionInfo->stPlmnId)))
        {
            /* 如果当前网络当前接入技术状态为initial、not exist，则更新状态为存在，质量为低质量，记录具体质量值 */
            if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != pstPlmnSelectionInfo->astPlmnRatInfo[i].enNetStatus)
            {
                pstPlmnSelectionInfo->astPlmnRatInfo[i].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
            }
            pstPlmnSelectionInfo->astPlmnRatInfo[i].enQuality   = NAS_MMC_NET_LOW_QUALITY;
            pstPlmnSelectionInfo->astPlmnRatInfo[i].lRscp       = pstPlmnSearchInfo->astLowPlmnList[j].lRscp;

            /* BCCH中上报的Mnc有可能长度和SIM卡中存储的Mnc不一样，统一改为BCCH中的Mnc */
            pstPlmnSelectionInfo->stPlmnId.ulMnc = pstPlmnSearchInfo->astLowPlmnList[j].stPlmnId.ulMnc;
            return VOS_TRUE;
        }
    }


    /* 在全频段搜索时候，才能将未搜索到的更新为不存在，在历史频点搜，高质量搜等非全频段搜时候，只能更新存在的 */
    if (VOS_TRUE == ucIsAllBandSearch )
    {
        /* 如果当前网络当前接入技术状态为initial、exist、exist seached，则更新状态为不存在 */
        pstPlmnSelectionInfo->astPlmnRatInfo[i].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST;
        pstPlmnSelectionInfo->astPlmnRatInfo[i].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_DelPlmnInSearchList
 功能描述  : 从搜索列表中删除指定的网络
 输入参数  : pstPlmn    需要删除的网络
 输出参数  : pstPlmnSearchInfo,搜索列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_DelPlmnInSearchList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmn,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo
)
{
    VOS_UINT32                           i;

    /* 从高质量列表中删除此网络 */
    for (i = 0; i < pstPlmnSearchInfo->ulHighPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnSearchInfo->astHighPlmnList[i]),
                                                           pstPlmn))
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSearchInfo->astHighPlmnList[i]),
                        &(pstPlmnSearchInfo->astHighPlmnList[i+1]),
                        (pstPlmnSearchInfo->ulHighPlmnNum-i-1)*sizeof(NAS_MML_PLMN_ID_STRU));
            /*lint +e961*/
            (pstPlmnSearchInfo->ulHighPlmnNum)--;

            return;
        }
    }

    /* 从低质量列表中删除此网络 */
    for (i = 0; i < pstPlmnSearchInfo->ulLowPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn((NAS_MML_PLMN_ID_STRU*)&(pstPlmnSearchInfo->astLowPlmnList[i].stPlmnId),
                                                           pstPlmn))
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSearchInfo->astLowPlmnList[i]),
                        &(pstPlmnSearchInfo->astLowPlmnList[i+1]),
                        (pstPlmnSearchInfo->ulLowPlmnNum-i-1)*sizeof(NAS_MMC_LOW_PLMN_INFO_STRU));
            /*lint +e961*/
            (pstPlmnSearchInfo->ulLowPlmnNum)--;

            return;
        }
    }

    return;

}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetSpecPlmnTypeIndexInPlmnSelectionList
 功能描述  : 获取搜网列表中指定网络类型的索引值
 输入参数  : enSpecPlmnType      - 网络类型
             pstPlmnSelectionList- 列表信息
 输出参数  : 无
 返 回 值  : 索引值
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_UINT16 NAS_MMC_GetSpecPlmnTypeIndexInPlmnSelectionList(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enSpecPlmnType,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{

    VOS_UINT16                                              i;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo = VOS_NULL_PTR;

    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        pstPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);

        if (enSpecPlmnType == pstPlmnInfo->enPlmnType)
        {
            return i;
        }
    }

    /* 不存在指定类型的网络，返回无效值0xffff */
    return NAS_MMC_PLMN_SELECTION_LIST_INVALID_INDEX;
}
/*****************************************************************************
 函 数 名  : NAS_MMC_InsertRoamPlmnListInPlmnSelectionList
 功能描述  : 根据已搜索的列表信息更新或补充选网列表
 输入参数  : pastPlmnSearchInfo,搜索的列表信息
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月18日
   作    者   : c00188733
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_VOID NAS_MMC_InsertRoamPlmnListInPlmnSelectionList(
    VOS_UINT32                                              ulPlmnSearchNum,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnIdList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT16                                              usIndex;
    VOS_UINT16                                              usSimRat;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;

    /* 循环搜索带上来的每个网络,判断是否在搜网列表中已存在，如果不存在且国家码与rplmn和hplmn不同，
       则插入搜网列表的rplmn或hplmn前 */
    for (i = 0; i < ulPlmnSearchNum; i++)
    {
        if (VOS_TRUE == NAS_MMC_IsPlmnWithRatInPlmnList(&(pstPlmnIdList[i]),
                                                          enRat,
                                                          pstPlmnSelectionListInfo,
                                                          pstPlmnSelectionListInfo->usSearchPlmnNum))
        {
            continue;
        }


        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithRplmn(pstPlmnIdList[i].ulMcc))
        {
            continue;
        }

        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithHplmn(pstPlmnIdList[i].ulMcc))
        {
            continue;
        }

        usSimRat = NAS_MMC_ConvertNetRatToSimRat(enRat);

        /* 获取rplmn在搜网列表中的index，如果rplmn不存在，则获取hplmn在搜网列表中的index,插入搜网列表index位置 */
        usIndex = NAS_MMC_GetSpecPlmnTypeIndexInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN, pstPlmnSelectionListInfo);

        if (NAS_MMC_PLMN_SELECTION_LIST_INVALID_INDEX != usIndex)
        {

            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                               usSimRat,
                                               &pstPlmnIdList[i],
                                               &stPlmnInfo);

            (VOS_VOID)NAS_MMC_InsertPlmnInPlmnSelectionList(&stPlmnInfo,
                                                   pstPlmnSelectionListInfo,
                                                   usIndex);
        }
        else
        {
            usIndex = NAS_MMC_GetSpecPlmnTypeIndexInPlmnSelectionList(NAS_MMC_PLMN_TYPE_HPLMN, pstPlmnSelectionListInfo);

            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                               usSimRat,
                                               &pstPlmnIdList[i],
                                               &stPlmnInfo);

            (VOS_VOID)NAS_MMC_InsertPlmnInPlmnSelectionList(&stPlmnInfo,
                                                   pstPlmnSelectionListInfo,
                                                   usIndex);
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateRoamPlmnListInPlmnSelectionList
 功能描述  : 根据已搜索的列表信息更新或补充选网列表
 输入参数  : pastPlmnSearchInfo,搜索的列表信息
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月8日
   作    者   : z00161729
   修改内容   : 开机搜网优化项目修改

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateRoamPlmnListInPlmnSelectionList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    VOS_UINT32                                              ulAppendFlg,
    VOS_UINT8                                                ucIsAllBandSearch

)
{
    VOS_UINT32                                              i;
    NAS_MML_PLMN_ID_STRU                                    astLowPlmnInfo[NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM];

    /*插入高质量PLMN*/
    NAS_MMC_InsertRoamPlmnListInPlmnSelectionList(pstPlmnSearchInfo->ulHighPlmnNum,pstPlmnSearchInfo->enRatType,pstPlmnSearchInfo->astHighPlmnList,pstPlmnSelectionListInfo);

    /*插入低质量PLMN*/
    PS_MEM_SET(astLowPlmnInfo, 0xFF, sizeof(astLowPlmnInfo));
    for (i = 0; i < pstPlmnSearchInfo->ulLowPlmnNum; i++)
    {
        astLowPlmnInfo[i].ulMcc = pstPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMcc;
        astLowPlmnInfo[i].ulMnc = pstPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMnc;
    }
    NAS_MMC_InsertRoamPlmnListInPlmnSelectionList(pstPlmnSearchInfo->ulLowPlmnNum,pstPlmnSearchInfo->enRatType,astLowPlmnInfo,pstPlmnSelectionListInfo);

    /* 更新完毕将剩余网络补充到选网列表 */
    NAS_MMC_UpdatePlmnListInPlmnSelectionList(pstPlmnSearchInfo,
                                              pstPlmnSelectionListInfo,
                                              ulAppendFlg,
                                              ucIsAllBandSearch);

    return;
}





/*****************************************************************************
 函 数 名  : NAS_MMC_UpdatePlmnListInPlmnSelectionList
 功能描述  : 根据已搜索的列表信息更新或补充选网列表
 输入参数  : pastPlmnSearchInfo,搜索的列表信息
             ulAppendFlg,是否需要将更新后的列表信息保存到选网列表
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_UpdatePlmnListInPlmnSelectionList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    VOS_UINT32                                              ulAppendFlg,
    VOS_UINT8                                                ucIsAllBandSearch

)
{
    VOS_UINT32                                              i;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstTmpPlmnSearchInfo = VOS_NULL_PTR;


    pstTmpPlmnSearchInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU));

    if (VOS_NULL_PTR == pstTmpPlmnSearchInfo)
    {
        /* 打印异常 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePlmnListInPlmnSelectionList: Mem alloc fail.");

        return;
    }

    PS_MEM_CPY(pstTmpPlmnSearchInfo, pstPlmnSearchInfo, sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU));

    /* 循环选网列表中每一个网络 */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {

        /* 根据一个接入技术的搜索信息更新搜索列表中的一个网络，如果更新成功，需要将搜索信息中对应网络删除 */
        if (VOS_TRUE == NAS_MMC_UpdatePlmnRatInfoInSearchList(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                                               pstPlmnSearchInfo, ucIsAllBandSearch))
        {
            NAS_MMC_DelPlmnInSearchList(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId), pstTmpPlmnSearchInfo);
        }
    }

    /* 如果需要将已搜索的列表信息pastPlmnSearchInfo中的剩余网络补充到搜网列表中 */
    if (VOS_TRUE == ulAppendFlg)
    {
        NAS_MMC_SavePlmnListInPlmnSelectionList(pstTmpPlmnSearchInfo, pstPlmnSelectionListInfo);
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstTmpPlmnSearchInfo);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetPlmnTypeInPlmnSelectionList
 功能描述  : 获取搜网列表中指定接入技术的网络的类型
 输入参数  : pstPlmnWithRat
             pstPlmnSelectionList,列表信息
 输出参数  : 无
 返 回 值  : NAS_MMC_PLMN_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数

*****************************************************************************/
NAS_MMC_PLMN_TYPE_ENUM_UINT8 NAS_MMC_GetPlmnTypeInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{

    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo = VOS_NULL_PTR;

    /* 将该PLMN及其接入技术与搜网列表中每个PLMN及其接入技术比较 */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        pstPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);

        /* 比较pstPlmn->stPlmnId,与pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId */
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnWithRat->stPlmnId),
                                                           &(pstPlmnInfo->stPlmnId)))
        {
            /* 如果相同，比较接入技术 */
            for (j = 0; j < pstPlmnInfo->ucRatNum; j++)
            {
                if (pstPlmnWithRat->enRat == pstPlmnInfo->astPlmnRatInfo[j].enRatType)
                {
                    return pstPlmnInfo->enPlmnType;
                }
            }
        }
    }

    return NAS_MMC_PLMN_TYPE_BUTT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSpecPlmnNetStatusInPlmnSelectionList
 功能描述  : 获取搜网列表中指定网络的各接入技术的网络状态
 输入参数  : pstPlmnWithRat
             pstPrioRatList
             pstPlmnSelectionList,列表信息
 输出参数  : paucNetStatus
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_GetSpecPlmnNetStatusInPlmnSelectionList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmn,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList,
    NAS_MMC_NET_STATUS_ENUM_UINT8                          *paucNetStatus,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo = VOS_NULL_PTR;

    /* 将该PLMN及其接入技术与搜网列表中每个PLMN及其接入技术比较 */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        pstPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);

        /* 比较pstPlmn->stPlmnId,与pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId */
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmn,
                                                           &(pstPlmnInfo->stPlmnId)))
        {
            /* 如果相同，比较接入技术 */
            for (j = 0; j < pstPrioRatList->ucRatNum; j++)
            {
                for (k = 0; k < pstPlmnInfo->ucRatNum; k++)
                {
                    if (pstPrioRatList->aucRatPrio[j] == pstPlmnInfo->astPlmnRatInfo[k].enRatType)
                    {
                        paucNetStatus[j] = pstPlmnInfo->astPlmnRatInfo[k].enNetStatus;
                        break;
                    }
                }
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetRPlmn_PlmnSelectionStrategy
 功能描述  : 根据RPLMN定制特性获取RPLMN
 输入参数  : enRat
 输出参数  : pstPlmnId
 返 回 值  : VOS_TRUE,获取成功
             VOS_FALSE,获取失败
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetRPlmn_PlmnSelectionStrategy(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stRPlmn;

    /* 初始化为无效PLMN */
    pstPlmnId->ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnId->ulMnc = NAS_MML_INVALID_MNC;

    /* 获取RPLMN配置信息 */
    pstRPlmnCfg = NAS_MML_GetRplmnCfg();

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == enRat)
    {
        /* 获取LTE的RPLMN */
        return NAS_MML_GetLteRPlmn(pstPlmnId);
    }
#endif

    /* 获取GU的RPLMN */
    if (VOS_FALSE == NAS_MML_GetGURPlmn(pstPlmnId))
    {
        return VOS_FALSE;
    }

    /* 如果不支持多接入技术RPLMN,则不需要读取各自接入技术下保存在NV中的RPLMN */
    if (VOS_FALSE == pstRPlmnCfg->ucMultiRATRplmnFlg)
    {
        return VOS_TRUE;
    }

    if (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
    {
        stRPlmn = pstRPlmnCfg->stWRplmnInNV;
    }
    else
    {
        stRPlmn = pstRPlmnCfg->stGRplmnInNV;
    }

    /* 若NV中保存的RPLMN有效且不在禁止网络中，返回NV中存储的网络,否则返回之前从SIM卡中获取的网络 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stRPlmn))
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdInForbidPlmnList(&stRPlmn))
        {
           *pstPlmnId = stRPlmn;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy
 功能描述  : 判断PLMN ID是否在禁止列表中
 输入参数  : pstPlmnId:需要判断的PLMN ID
             enRat:网络接入技术
             enNetStatus:网络接入状态
             ulUserSpecPlmnSearch:是否用户指定搜索
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID可以搜索
             VOS_FALSE : PLMN ID不可以搜索
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年08月3日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年10月5日
   作    者   : z00161729
   修改内容   : V7R1 phaseII高优先级搜网LLD检视意见修改函数名和参数
 3.日    期   : 2011年10月26日
   作    者   : w00176964
   修改内容   : V7R1 Phase III调整:联合注册修改
 4.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
                更改为NAS_MML_IsSimPlmnIdInDestBcchPlmnList,明确网络的比较类型，
                否则可能导致比较出错。
 4.日    期   : 2011年10月26日
   作    者   : w00176964
   修改内容   : V7R1 Phase III调整:联合注册修改
 5.日    期   : 2012年3月17日
   作    者   : w00176964
   修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加LTE国家漫游功能定制

 6.日    期   : 2012年10月20日
   作    者   : w00167002
   修改内容   : DTS2012101903646:GUTL四模定制版本，UE在L下注册被拒后，更新搜
                网列表时，没有过滤禁止接入技术网络,导致尝试搜禁止接入技术的网络，
                与设计不符合。
 7.日    期   : 2012年12月27日
   作    者   : s00217060
   修改内容   : for DSDA GUNAS C CORE:如果USIM卡GSM禁止接入，则不选择GSM网络
 8.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式
 9.日    期   : 2015年1月15日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
 10.日    期   : 2015年4月23日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MMC_NET_STATUS_ENUM_UINT8       enNetStatus,
    VOS_UINT32                          ulUserSpecPlmnSearch
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulAllowed;
#endif
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRatId;


    /* 初始化PLMN WITH RAT信息 */
    stPlmnWithRatId.stPlmnId.ulMcc      = pstPlmnId->ulMcc;
    stPlmnWithRatId.stPlmnId.ulMnc      = pstPlmnId->ulMnc;
    stPlmnWithRatId.enRat               = enRat;

#if (FEATURE_ON == FEATURE_LTE)
    ulAllowed = VOS_TRUE;

    /* 当前网络为LTE时 */
    if (NAS_MML_NET_RAT_TYPE_LTE == enRat)
    {
        /* 判断是否允许LTE的网络进行搜索 */
        ulAllowed   = NAS_MMC_IsLtePlmnSearchingAllowed_PlmnSelectionStrategy(pstPlmnId);
    }

    if (VOS_FALSE == ulAllowed)
    {
        return VOS_FALSE;
    }

#endif

    /* 如果USIM卡GSM禁止接入，则不选择GSM网络 */
    if ( (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
      && (NAS_MML_NET_RAT_TYPE_GSM == enRat) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy GsmForbidFlg");        
        
        return VOS_FALSE;
    }

    /* 如果当前尝试搜网的网络在禁止接入技术网络列表里,则不准许搜索 */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRatId))
    {
       return VOS_FALSE;
    }

    /* 如果当前尝试的接入技术在禁止接入技术列表中，则不准许搜索 */
    if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(stPlmnWithRatId.enRat))
    {
        return VOS_FALSE;
    }


    /* 网络状态不为未搜索和已搜索存在,则不容许搜索该网络 */
    if ((NAS_MMC_NET_STATUS_NO_SEARCHED != enNetStatus)
     && (NAS_MMC_NET_STATUS_SEARCHED_EXIST != enNetStatus))
    {
        return VOS_FALSE;
    }

    /* 手动模式不需要再判断是否在禁止网络列表中 */
    if (VOS_TRUE == ulUserSpecPlmnSearch)
    {
        return VOS_TRUE;
    }

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();


    /* 禁止网络，认为肯定是BCCH类型网络，在forbid plmn列表中 */
    if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstPlmnId,
                                          pstForbidPlmnInfo->ucForbPlmnNum,
                                          pstForbidPlmnInfo->astForbPlmnIdList))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy auto in astForbPlmnIdList");        
        
        return VOS_FALSE;
    }

    /* 不在forbid plmn for gprs列表中 */
    if (VOS_FALSE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstPlmnId,
                                          pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                          pstForbidPlmnInfo->astForbGprsPlmnList))
    {
        return VOS_TRUE;
    }

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy auto in astForbGprsPlmnList");        

#if (FEATURE_ON == FEATURE_LTE)

    /* LTE仅支持EPS,因此如果PS被禁,表示该网络不能搜索 */
    if (NAS_MML_NET_RAT_TYPE_LTE == enRat)
    {
        return VOS_FALSE;
    }
#endif

    /* 配置为PS ONLY时,不搜索禁止GPRS列表中的网络 */
    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        return VOS_FALSE;
    }

    /* CS域卡无效时 */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetSimCsRegStatus is false");        
        
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SaveAvailablePlmnInPlmnSelectionList
 功能描述  : 将Available网络保存回选网列表
 输入参数  : ulAvailPlmnNum
             pstAvailPlmnList
 输出参数  : pstPlmnSelectionListInfo
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2011年08月3日
   作    者   : s46746
   修改内容   : 新生成函数
*****************************************************************************/
/*lint -e429*/
VOS_VOID NAS_MMC_SaveAvailablePlmnInPlmnSelectionList(
    VOS_UINT32                                              ulAvailPlmnNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstAvailPlmnList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    /* 判断新增网络后是否会导致选网列表溢出 */
    if ((pstPlmnSelectionListInfo->usSearchPlmnNum + ulAvailPlmnNum) < NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST)
    {
        PS_MEM_CPY(&pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum],
                   pstAvailPlmnList,
                   ulAvailPlmnNum*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
        pstPlmnSelectionListInfo->usSearchPlmnNum += (VOS_UINT16)ulAvailPlmnNum;
    }
    else
    {
        PS_MEM_CPY(&pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum],
                   pstAvailPlmnList,
                   (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST-pstPlmnSelectionListInfo->usSearchPlmnNum)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
        pstPlmnSelectionListInfo->usSearchPlmnNum = NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST;

        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveAvailablePlmnInPlmnSelectionList: Plmn selection list full.");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SavePlmnListInPlmnSelectionList
 功能描述  : 保存更新后剩余的搜索列表信息到选网列表
 输入参数  : pastPlmnSearchInfo,剩余的搜索列表信息
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SavePlmnListInPlmnSelectionList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{

    VOS_UINT32                                              i;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmn;

    /* 初始化选网信息 */
    NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_AVAIL_PLMN, NAS_MML_INVALID_SIM_RAT,
                                       &(stPlmn.stPlmnId), &stPlmn);

    stPlmn.ucRatNum++;
    stPlmn.astPlmnRatInfo[0].enRatType     = pstPlmnSearchInfo->enRatType;
    stPlmn.astPlmnRatInfo[0].enNetStatus   = NAS_MMC_NET_STATUS_SEARCHED_EXIST;

    /* 循环已搜网列表中还存在的高质量网络 */
    for (i = 0; i < pstPlmnSearchInfo->ulHighPlmnNum; i++)
    {
        stPlmn.stPlmnId                        = pstPlmnSearchInfo->astHighPlmnList[i];

        stPlmn.astPlmnRatInfo[0].enQuality     = NAS_MMC_NET_HIGH_QUALITY;

        /* 加入到选网列表中 */
        NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmn, pstPlmnSelectionListInfo);
    }

    /* 循环已搜网列表中还存在的低质量网络 */
    for (i = 0; i < pstPlmnSearchInfo->ulLowPlmnNum; i++)
    {
        stPlmn.stPlmnId.ulMcc                  = pstPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMcc;
        stPlmn.stPlmnId.ulMnc                  = pstPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMnc;

        stPlmn.astPlmnRatInfo[0].enQuality     = NAS_MMC_NET_LOW_QUALITY;
        stPlmn.astPlmnRatInfo[0].lRscp         = pstPlmnSearchInfo->astLowPlmnList[i].lRscp;

        /* 加入到选网列表中 */
        NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmn, pstPlmnSelectionListInfo);
    }

    return;
}
/*lint +e429*/
/*****************************************************************************
 函 数 名  : NAS_MMC_InitNetStatusInRatSearchInfo
 功能描述  : 根据接入技术是否进行过全频搜索，初始化网络的存在状态
 输入参数  : pstPrioRatList : 接入技术优先级列表
              pstSearchRatInfo ：不同接入技术的搜索信息列表
 输出参数  : paucNetStatus：接入技术对应的网络状态
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月22日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_InitNetStatusInRatSearchInfo(
    NAS_MMC_NET_STATUS_ENUM_UINT8      *paucNetStatus,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList,
    NAS_MMC_RAT_SEARCH_INFO_STRU       *pstSearchRatInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT8                           ucSearchAllBandFlg;

    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        ucSearchAllBandFlg = VOS_FALSE;

        for (j = 0; j < NAS_MML_MAX_RAT_NUM; j++)
        {
            if (pstPrioRatList->aucRatPrio[i] == pstSearchRatInfo[j].enRatType)
            {
                ucSearchAllBandFlg = pstSearchRatInfo[j].ucSearchAllBand;
                break;
            }
        }

        if (VOS_TRUE == ucSearchAllBandFlg)
        {
            paucNetStatus[i] = NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST;
        }
        else
        {
            paucNetStatus[i] = NAS_MMC_NET_STATUS_NO_SEARCHED;
        }
    }
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_RefreshPlmnSelectionList_DisableLte_CsPsMode1RegSuccess
 功能描述  : 刷新选网列表，保证当前网络的GU接入技术优先搜索
 输入参数  : 无
 输出参数  : pstPlmnSelectionList
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年6月1日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2012年10月10日
   作    者   : t00212959
   修改内容   : For DTS2012083005474，EPLMN的第一个是RPLMN,将原搜网列表的RPLMN 和 EPLMN去除
 3.日    期   : 2012年12月12日
   作    者   : t00212959
   修改内容   : For DTS2012121104779，不是因为CSPS mode 1导致的disable L,如被#7拒绝，不应该按照CSPS Mode1处理

 4.日    期   : 2014年5月28日
   作    者   : z00234330
   修改内容   : covertity修改
*****************************************************************************/
VOS_VOID NAS_MMC_RefreshPlmnSelectionList_DisableLte_CsPsMode1RegSuccess(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList,
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEPlmnList    = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MMC_NET_STATUS_ENUM_UINT8       aucNetStatus[NAS_MML_MAX_RAT_NUM];
    VOS_UINT32                          i;

    /* modified by z00234330 for coverity修改 2014-05-28 begin */
    PS_MEM_SET(aucNetStatus, 0x00, sizeof(aucNetStatus));
    PS_MEM_SET(&stPrioRatList, 0x00, sizeof(stPrioRatList));
    /* modified by z00234330 for coverity修改 2014-05-28 end */

    /* NAS_MML_GetEquPlmnList 获取当前网络的EPLMN */
    pstEPlmnList   = NAS_MML_GetEquPlmnList();
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* 将原来搜网列表的EPLMN去除*/
    /* 手动选网模式删除RPLMN和EPLMN,用户指定网络不删除,目的是在其它接入技术上继续尝试用户指定网络 */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 在选网列表中将用户指定PLMN修改为Avail plmn,保证后续获取下一个搜索网络时,
           如果其处于禁止列表中,不再搜索该网络 */
        NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                  NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                  pstPlmnSelectionList);

        /* 在选网列表中删除RPLMN */
        NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN,
                                                      pstPlmnSelectionList);

        /* 在选网列表中删除EPLMN */
        NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_EPLMN,
                                                      pstPlmnSelectionList);
    }
    else
    {
        /* 在选网列表中将RPLMN修改为Avail plmn */
        NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN,
                                                  NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                  pstPlmnSelectionList);

        /* 在选网列表中将EPLMN修改为Avail plmn */
        NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(NAS_MMC_PLMN_TYPE_EPLMN,
                                                  NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                  pstPlmnSelectionList);

        /* 在选网列表中删除质量为UNKNOW的Avail plmn */
        NAS_MMC_DeleteSpecQualAvailPlmnInPlmnSelectionList(NAS_MMC_NET_QUALITY_UNKNOWN,
                                                           pstPlmnSelectionList);

        /* 重新排序available plmn */
        NAS_MMC_SortAvailPlmnInPlmnSelectionList(pstPlmnSelectionList);
    }

    /* 将EPLMN从后往前添加到选网列表 */
    for ( i = pstEPlmnList->ucEquPlmnNum; i > 0; i-- )
    {
        NAS_MMC_InitNetStatusInRatSearchInfo(aucNetStatus, pstPrioRatList, pstSearchRatInfo);

        NAS_MMC_GetSpecPlmnNetStatusInPlmnSelectionList(&(pstEPlmnList->astEquPlmnAddr[i-1]),
                                                          pstPrioRatList,
                                                          aucNetStatus,
                                                          pstPlmnSelectionList);

        PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(stPrioRatList));

        /* 网络状态为NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,NAS_MMC_NET_STATUS_SEARCHED_REGISTERED的接入技术,
           表示后续没必要在进行搜索了,因此从stPrioRatList中删除 */
        NAS_MMC_DelSpecNetStatusRat(NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST, aucNetStatus, &stPrioRatList);

        NAS_MMC_DelSpecNetStatusRat(NAS_MMC_NET_STATUS_SEARCHED_REGISTERED, aucNetStatus, &stPrioRatList);

        if (i==1)
        {
            /* 将RPLMN网络插入到选网列表最前面 */
            NAS_MMC_InsertPlmnToPlmnSelectionListHead(&(pstEPlmnList->astEquPlmnAddr[i-1]),
                                                        NAS_MMC_PLMN_TYPE_RPLMN,
                                                       &stPrioRatList,
                                                        pstPlmnSelectionList);
        }
        else
        {
            /* 将EPLMN网络插入到选网列表最前面 */
            NAS_MMC_InsertPlmnToPlmnSelectionListHead(&(pstEPlmnList->astEquPlmnAddr[i-1]),
                                                        NAS_MMC_PLMN_TYPE_EPLMN,
                                                       &stPrioRatList,
                                                        pstPlmnSelectionList);
        }

    }

    return;
}

#endif


/*****************************************************************************
 函 数 名  : NAS_MMC_RefreshEPlmnInPlmnSelectionList
 功能描述  : 当注册失败需要进行PLMN SELECTION时对选网列表的调整
 输入参数  : 无
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数
 2. 日    期   : 2011年1月15日
    作    者  : l00171473
    修改内容   : For DTS2011111003965, 手动开机，用户指定网络被原因值13拒掉后，不应搜EPLMN
  3.日    期   : 2012年10月26日
    作    者   : W00176964
    修改内容   : DTS2012090303157:使用EPLMN有效标记来判断是否需要从选网列表中删除EPLMN
  4.日    期   : 2014年5月21日
    作    者   : w00167002
    修改内容   : DTS2014051602857:在SOR打开时候，如果CS注册失败达到4次，则等周期
                搜网定时器超时发起LIST搜网，如果当前仅有原有网络，则发起LAU,否则
                触发MM发起LAU;如果LIST搜后，发现有其他网络，则发起其他网络的搜网注册。
                删除EPLMN时候，不能将已经注册过的网络删除。
*****************************************************************************/
VOS_VOID NAS_MMC_RefreshEPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList
)
{
    /* EPLMN有效直接返回,只有在EPLMN无效的情况下才更新选网列表 */
    if (VOS_TRUE == NAS_MML_GetEplmnValidFlg())
    {
        return;
    }


    /* 手动选网模式删除RPLMN和EPLMN,用户指定网络不删除,目的是在其它接入技术上继续尝试用户指定网络 */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        /* 在选网列表中将用户指定PLMN修改为Avail plmn,保证后续获取下一个搜索网络时,
           如果其处于禁止列表中,不再搜索该网络 */
        NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                  NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                  pstPlmnSelectionList);


        if (VOS_TRUE == NAS_MML_GetDeleteRplmnWhenEplmnInvalidFlg())
        {
            /* 在选网列表中删除RPLMN */
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN,
                                                          pstPlmnSelectionList);
        }

        /* 在选网列表中删除EPLMN */
        NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_EPLMN,
                                                      pstPlmnSelectionList);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetDeleteRplmnWhenEplmnInvalidFlg())
    {
        /* 在选网列表中将RPLMN修改为Avail plmn */
        NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN,
                                                  NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                  pstPlmnSelectionList);
    }

    /* 在选网列表中将EPLMN修改为Avail plmn */
    NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(NAS_MMC_PLMN_TYPE_EPLMN,
                                              NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                              pstPlmnSelectionList);


    /* 在选网列表中删除网络状态为未搜索的网络 */
    NAS_MMC_DeleteSpecNetStatusAvailPlmnInPlmnSelectionList(NAS_MMC_NET_STATUS_NO_SEARCHED,
                                               pstPlmnSelectionList);


    /* 重新排序available plmn */
    NAS_MMC_SortAvailPlmnInPlmnSelectionList(pstPlmnSelectionList);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsR7SptSrchHplmn_AutoMode
 功能描述  : 自动模式是否支持R7开机搜索 Hplmn
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年8月12日
   作    者   : l00130025
   修改内容   : 新生成函数

 2.日    期   : 2011年11月12日
   作    者   : w00167002
   修改内容   : DTS2011111200182:记录是否支持协议要求的在自动模式开机
                 或丢网后搜索Hplmn的特性,VOS_FALSE:不支持,VOS_TRUE:支持
 3.日    期   : 2014年3月19日
   作    者   : w00242748
   修改内容   : DTS2014031200137:当NV特性打开时，自动开机或者搜网时，如果首次搜索RPLMN的话，
                需要将HPLMN/EHPLMN带给接入层。
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsHPlmnPrioSearch( VOS_VOID )
{
    NAS_MML_HPLMN_CFG_INFO_STRU        *pstHplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo   = VOS_NULL_PTR;

    /* 获取HPLMN的配置信息 */
    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    /* 获取Sim卡中Ehplmn相关的信息 */
    pstEHPlmnInfo  = NAS_MML_GetSimEhplmnList();

    /* 自动搜网模式 支持开机优先搜索Hplmn */
    if ((NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
     && ( ( (NAS_MML_AUTO_SRCH_FLG_TYPE_PLMN_SEL_IND == pstHplmnCfgInfo->enAutoSearchHplmnFlg)
       && (NAS_MML_LAST_RPLMN_SEL_IND_HPLMN == pstEHPlmnInfo->enPLMNSelInd))
     || (NAS_MML_AUTO_SRCH_FLG_TYPE_HPLMN_FIRST == pstHplmnCfgInfo->enAutoSearchHplmnFlg) ))
    {
        return VOS_TRUE;
    }
    else
    {
       return VOS_FALSE;
    }

}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsRPlmnFirstSearchWithHPlmn
 功能描述  : 搜索RPLMN时，是否需要带HPLMN的标识
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年3月19日
   作    者   : w00242748
   修改内容   : DTS2014031200137:当NV特性打开时，自动开机或者搜网时，如果首次搜索RPLMN的话，
                需要将HPLMN/EHPLMN带给接入层。
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsRPlmnFirstSearchWithHPlmn(VOS_VOID)
{
    NAS_MML_HPLMN_CFG_INFO_STRU        *pstHplmnCfgInfo = VOS_NULL_PTR;

    /* 获取HPLMN的配置信息 */
    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();


    /* 自动搜网模式 支持开机优先搜索Hplmn */
    if ((NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
     && (NAS_MML_AUTO_SRCH_FLG_TYPE_RPLMN_WITH_HPLMN_FIRST == pstHplmnCfgInfo->enAutoSearchHplmnFlg))
    {
        return VOS_TRUE;
    }
    else
    {
       return VOS_FALSE;
    }
}



/*****************************************************************************
 函 数 名  : NAS_MMC_RefreshCurPlmnInPlmnSelectionList
 功能描述  : 当注册失败需要进行当前网络搜索时对选网列表的调整
 输入参数  : enPlmnType
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数
 2.日    期   : 2012年7月1日
    作    者  : s00217060
    修改内容  : For V7R1 CS/PS mode 1, 调整函数，选网列表初始化
 3.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
 3.日    期   : 2013年8月26日
   作    者   : w00242748
   修改内容   : DTS2013071808373, 编译告警清理
*****************************************************************************/
VOS_VOID NAS_MMC_RefreshCurPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList,
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList       = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MMC_NET_STATUS_ENUM_UINT8       aucNetStatus[NAS_MML_MAX_RAT_NUM];
    VOS_UINT32                          i;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    PS_MEM_SET(aucNetStatus, 0x00, sizeof(aucNetStatus));

    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* 在选网列表中获取当前网络的网络状态 */
    NAS_MMC_InitNetStatusInRatSearchInfo(aucNetStatus, pstPrioRatList, pstSearchRatInfo);

    NAS_MMC_GetSpecPlmnNetStatusInPlmnSelectionList(NAS_MML_GetCurrCampPlmnId(),
                                                    pstPrioRatList,
                                                    aucNetStatus,
                                                    pstPlmnSelectionList);

    i = 0;

    /* 网络状态为NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,NAS_MMC_NET_STATUS_SEARCHED_REGISTERED的接入技术,
       表示后续没必要在进行搜索了,因此从stPrioRatList中删除 */
    while (i < stPrioRatList.ucRatNum)
    {
        if ((NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST == aucNetStatus[i])
         || (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED == aucNetStatus[i]))
        {
            stPrioRatList.aucRatPrio[i] = NAS_MML_NET_RAT_TYPE_BUTT;

            if (i < (NAS_MML_MAX_RAT_NUM - 1))
            {
                /*lint -e961*/
                (VOS_VOID)PS_MEM_MOVE(&(stPrioRatList.aucRatPrio[i]),
                            &(stPrioRatList.aucRatPrio[i+1]),
                            (NAS_MML_MAX_RAT_NUM-i-1));

                (VOS_VOID)PS_MEM_MOVE(&(aucNetStatus[i]),
                            &(aucNetStatus[i+1]),
                            (NAS_MML_MAX_RAT_NUM-i-1));
                /*lint +e961*/
            }
            stPrioRatList.ucRatNum--;

            continue;
        }
        i++;
    }

    /* 如果网络类型为Butt,表示选网列表中未找到此接入技术网络,该网络类型就为avail网络,
       此时只需要将当前接入技术排在最前面即可 */
    if (NAS_MMC_PLMN_TYPE_BUTT == enPlmnType)
    {
        enPlmnType = NAS_MMC_PLMN_TYPE_AVAIL_PLMN;
        NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);
    }
    else
    {
        /* 将当前接入技术插入到最前面 */
        (VOS_VOID)PS_MEM_MOVE(&(stPrioRatList.aucRatPrio[1]),
                    &(stPrioRatList.aucRatPrio[0]),
                    (stPrioRatList.ucRatNum*sizeof(NAS_MML_NET_RAT_TYPE_ENUM_UINT8)));

        stPrioRatList.aucRatPrio[0] = NAS_MML_GetCurrNetRatType();

        stPrioRatList.ucRatNum++;
    }

    /* 将当前网络插入到选网列表最前面 */
    NAS_MMC_InsertPlmnToPlmnSelectionListHead(NAS_MML_GetCurrCampPlmnId(),
                                              enPlmnType,
                                              &stPrioRatList,
                                              pstPlmnSelectionList);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_LogPlmnSelectionList
 功能描述  : 将选网列表发送到OM
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月29日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_LogPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* 将选网列表信息发送到OM输出 */
    NAS_MMC_SndOmPlmnSelectionList(pstPlmnSelectionList, pstPrioRatList);

    NAS_MMC_LogRplmnRelatedInfo();
    NAS_MMC_LogForbiddenPlmnRelatedInfo();


    /* 勾取选网状态机上下文信息，便于问题定位 */
    if (NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo(NAS_MMC_GetPlmnSelectionCtx_PlmnSelection());
    }


    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_LogAsPlmnList
 功能描述  : 将接入层上报搜网列表发送到OM
 输入参数  : pstSrchedPlmn - 接入层上报的搜网列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月9日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2014年12月29日
    作    者   : w00167002
    修改内容   : DTS2014122600652:长度不正确导致复位
*****************************************************************************/
VOS_VOID NAS_MMC_LogAsPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    *pstSrchedPlmn
)
{
    NAS_MMC_LOG_AS_PLMN_LIST_MSG_STRU                      *pstMsg  = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_LOG_AS_PLMN_LIST_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_AS_PLMN_LIST_MSG_STRU)));
    if (TAF_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogAsPlmnList:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_AS_PLMN_SELECTION_LIST;

    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_AS_PLMN_LIST_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_CPY(&pstMsg->stSrchedPlmn, pstSrchedPlmn,sizeof(pstMsg->stSrchedPlmn));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_LogDplmnNplmnList
 功能描述  : 将DPLMN, NPLMN发送到OM
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : b00269685
    修改内容   : 新生成函数
  2.日    期   : 2015年12月16日
    作    者   : s00217060
    修改内容   : DTS2015120701561:增加DPLMN对应版本号和EHPLMN列表的可维可测

*****************************************************************************/
VOS_VOID NAS_MMC_LogDplmnNplmnList(VOS_VOID)
{
    NAS_MMC_LOG_DPLMN_LIST_STRU                            *pstLogDplmnMsg       = VOS_NULL_PTR;
    NAS_MMC_LOG_NPLMN_LIST_STRU                            *pstLogNplmnMsg       = VOS_NULL_PTR;
    NAS_MMC_LOG_DPLMN_NPLMN_CFG_STRU                       *pstLogDplmnNplmnCfg  = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT16                                              i;

    pstDPlmnNPlmnCfgInfo     = NAS_MMC_GetDPlmnNPlmnCfgInfo();


    /* ========================== DPLMN-NPLMN-CFG开始 ========================== */
    pstLogDplmnNplmnCfg = (NAS_MMC_LOG_DPLMN_NPLMN_CFG_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_DPLMN_NPLMN_CFG_STRU)));

    if (VOS_NULL_PTR == pstLogDplmnNplmnCfg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogDplmnNplmnList:ERROR:Alloc Mem Fail.");
        return;
    }

    pstLogDplmnNplmnCfg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLogDplmnNplmnCfg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstLogDplmnNplmnCfg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstLogDplmnNplmnCfg->stMsgHeader.ulMsgName       = MMCOM_LOG_DPLMN_NPLMN_CFG;
    pstLogDplmnNplmnCfg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_DPLMN_NPLMN_CFG_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 版本号 */
    PS_MEM_CPY(pstLogDplmnNplmnCfg->aucVersionId, pstDPlmnNPlmnCfgInfo->aucVersionId, NAS_MCC_INFO_VERSION_LEN);

    /* EHPLMN个数 */
    pstLogDplmnNplmnCfg->ucEHplmnNum    = pstDPlmnNPlmnCfgInfo->ucEHplmnNum;

    /* EHPLMN列表 */
    PS_MEM_CPY(pstLogDplmnNplmnCfg->astEHplmnList, pstDPlmnNPlmnCfgInfo->astEHplmnList, sizeof(pstDPlmnNPlmnCfgInfo->astEHplmnList));

    DIAG_TraceReport(pstLogDplmnNplmnCfg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstLogDplmnNplmnCfg);

    /* ========================== DPLMN-NPLMN-CFG结束 ========================== */


    /* ========================== DPLMN LIST开始 ========================== */


    pstLogDplmnMsg = (NAS_MMC_LOG_DPLMN_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_DPLMN_LIST_STRU)));

    if (VOS_NULL_PTR == pstLogDplmnMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogDplmnNplmnList:ERROR:Alloc Mem Fail.");
        return;
    }

    pstLogDplmnMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLogDplmnMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstLogDplmnMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstLogDplmnMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_DPLMN_LIST;

    for (i = 0; i < pstDPlmnNPlmnCfgInfo->usDplmnListNum; i++)
    {
        PS_MEM_CPY(&pstLogDplmnMsg->astDPlmnList[i], &pstDPlmnNPlmnCfgInfo->astDPlmnList[i], sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));
    }

    pstLogDplmnMsg->usDplmnListNum = pstDPlmnNPlmnCfgInfo->usDplmnListNum;

    pstLogDplmnMsg->stMsgHeader.ulLength = sizeof(pstLogDplmnMsg->stMsgHeader.ulMsgName)
                                      + sizeof(pstLogDplmnMsg->usDplmnListNum)
                                      + (pstLogDplmnMsg->usDplmnListNum * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));

    DIAG_TraceReport(pstLogDplmnMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstLogDplmnMsg);

    /* ========================== DPLMN LIST结束 ========================== */



    /* ========================== NPLMN LIST开始 ========================== */

    pstLogNplmnMsg = (NAS_MMC_LOG_NPLMN_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_NPLMN_LIST_STRU)));

    if (VOS_NULL_PTR == pstLogNplmnMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogDplmnNplmnList:ERROR:Alloc Mem Fail.");
        return;
    }

    pstLogNplmnMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLogNplmnMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstLogNplmnMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstLogNplmnMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_NPLMN_LIST;

    for (i = 0; i < pstDPlmnNPlmnCfgInfo->usNplmnListNum; i++)
    {
        PS_MEM_CPY(&pstLogNplmnMsg->astNPlmnList[i], &pstDPlmnNPlmnCfgInfo->astNPlmnList[i], sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));
    }

    pstLogNplmnMsg->usNplmnListNum = pstDPlmnNPlmnCfgInfo->usNplmnListNum;

    pstLogNplmnMsg->stMsgHeader.ulLength = sizeof(pstLogNplmnMsg->stMsgHeader.ulMsgName)
                                      + sizeof(pstLogNplmnMsg->usNplmnListNum)
                                      + (pstLogNplmnMsg->usNplmnListNum * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));

    DIAG_TraceReport(pstLogNplmnMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstLogNplmnMsg);
    /* ========================== NPLMN LIST结束 ========================== */

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_HighPrioPlmnSearch
 功能描述  : 高优先级搜网状态机启动时，搜网列表初始化
 输入参数  : 无
 输出参数  : pstPlmnSelectionList - 高优先级搜网列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年9月9日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2011年12月31日
   作    者   : w00166186
   修改内容   : DTS2011082902017,ON PLMN下注册被拒,搜网状态机重复搜索该网络

 3.日    期   : 2012年5月17日
   作    者   : zhoujun 40661
   修改内容   : 泰国AIS特性

 4.日    期   : 2014年1月22日
   作    者   : w00167002
   修改内容   : SVLTE共天线:MMC上下文中的选网列表可以用于高优先级搜网使用，
                 也可以用于存储选网状态机中的搜网列表信息。
                如果初始化为高优先级搜网，则需要显示指示当前的选网类型。
 5.日    期   : 2014年6月13日
   作    者   : b00269685
   修改内容   : 根据3gpp2,优选网络不包括UPLMN
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_HighPrioPlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT8                           uc3GPPUplmnNotPrefFlg;

    uc3GPPUplmnNotPrefFlg = NAS_MML_Get3GPP2UplmnNotPrefFlg();

    NAS_MMC_SetPlmnSelectionListType(NAS_MMC_STORE_HIGH_PRIO_PLMN_SELECTION_LIST);

    /* Modified by z40661 for 泰国AIS特性 2012-05-17, begin */
    if ( VOS_TRUE == NAS_MMC_IsAisRoamingEffect())
    {
        /* 向选网列表中增加最需要进行搜网的网络*/
        NAS_MMC_AddAisRoamPlmnInPlmnSelectionList(pstHighPrioPlmnSearchListInfo);
    }
    /* Modified by z40661 for 泰国AIS特性 2012-05-17, end */

    /* 添加EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstHighPrioPlmnSearchListInfo);

    if ((NAS_MMC_REG_CONTROL_BY_3GPP_MMC == NAS_MMC_GetRegCtrl())
     || (VOS_FALSE == uc3GPPUplmnNotPrefFlg))
    {
        /* 添加UPLMN和OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstHighPrioPlmnSearchListInfo);
    }
    else
    {
        /* 添加OPLMN */
        NAS_MMC_AddOPlmnInPlmnSelectionList(pstHighPrioPlmnSearchListInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnRatSupported
 功能描述  : 判断PLMN的各接入技术当前是否支持(是否是syscfg设置支持的)
 输入参数  : NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU   *pstPlmnInfo
 输出参数  : 无
 返 回 值  : VOS_TRUE:不支持
             VOS_FALSE:支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月23日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnRatSupported(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo
)
{
    VOS_UINT32                         i;

    for (i = 0; i < pstPlmnInfo->ucRatNum; i++)
    {
        if (VOS_TRUE == NAS_MML_IsNetRatSupported(pstPlmnInfo->astPlmnRatInfo[i].enRatType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsHighPrioPlmnSameCountry
 功能描述  : 获取该高优先级网络是否允许搜索
 输入参数  : pstHighPrioPlmnInfo: 高优先级PLMN
             pstVPlmnId: VPLMN信息
 输出参数  : 无
 返 回 值  : VOS_TRUE:允许搜索
             VOS_FALSE:不允许搜索
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月9日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年6月11日
   作    者   : w00166186
   修改内容   : AT&T&DCM项目

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsHighPrioPlmnSameCountry(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstHighPrioPlmnInfo,
    NAS_MML_PLMN_ID_STRU                                   *pstVPlmnId
)
{
    VOS_UINT32                                      ulIsSameCountryFlg;
    NAS_MML_BG_SEARCH_CFG_INFO_STRU                 *pstBgSearchCfg = VOS_NULL_PTR;

    NAS_MMC_HPLMN_SEARCH_REGARDLESS_MCC_CTX_STRU    *pstBgSearchRegardlessMccCtx = VOS_NULL_PTR;

    pstBgSearchCfg              = NAS_MML_GetBgSearchCfg();

    pstBgSearchRegardlessMccCtx = NAS_MML_GetBgSearchRegardlessMccCtx();


    ulIsSameCountryFlg  = NAS_MML_ComparePlmnMcc(pstVPlmnId->ulMcc, pstHighPrioPlmnInfo->stPlmnId.ulMcc);

    /* ucSpecialRoamFlg关闭时,如果国家码不同,返回VOS_FALSE；
       或者ucSpecialRoamFlg打开时,plmn属性为plmn属性为UPLMN和OPLMN,如果国家码
       不同返回VOS_FALSE,EHPLMN无此限制*/

    if ((VOS_TRUE == pstBgSearchCfg->ucSpecialRoamFlg)
     && (NAS_MMC_PLMN_TYPE_HPLMN == pstHighPrioPlmnInfo->enPlmnType))
    {
        return VOS_TRUE;
    }

    /* 当前国家码在定制的BG搜不考虑国家码的列表中 */
    if (VOS_TRUE == NAS_MML_IsMccInDestMccList(pstVPlmnId->ulMcc, pstBgSearchRegardlessMccCtx->ucCustomMccNum, pstBgSearchRegardlessMccCtx->aulCostumMccList))
    {
        return VOS_TRUE;
    }

    return ulIsSameCountryFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_CompareVPlmnPrioWithHighPrioPlmn
 功能描述  : 比较VPLMN和高优先级搜索网络的优先级是否相同
 输入参数  : pstVPlmn:高优先级搜网之前驻留的VPLMN信息
             enRat:VPLMN的接入技术
             pstEplmnList:高优先级搜网之前驻留VPLMN的等效PLMN信息
             pstHighPrioPlmnInfo: 高优先级PLMN
 输出参数  : 无
 返 回 值  : VOS_TRUE:VPLMN和高优先级网络优先级相同
             VOS_FALSE:VPLMN和高优先级网络优先级不同
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月9日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2011年11月24日
   作    者   : w00167002
   修改内容   : DTS2011112405567:原有的函数名NAS_MML_IsPlmnIdInDestPlmnList
               更改为NAS_MML_IsSimPlmnIdInDestBcchPlmnList,明确网络的比较类型，
               否则可能导致比较出错。
  3.日    期   : 2012年5月24日
    作    者   : l00171473
    修改内容   : DTS2012052404408,驻留HPLMN时,不发起BG搜
 3.日    期   : 2012年5月26日
   作    者   : z00161729
   修改内容   : V7R1C50 GUL背景搜修改
 4.日    期   : 2014年6月17日
   作    者   : z00234330
   修改内容   : PCINT清理
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareVPlmnPrioWithHighPrioPlmn(
    NAS_MML_PLMN_ID_STRU                                   *pstVPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnList,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstHighPrioPlmnInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIsPlmnInEplmnList;
    VOS_UINT32                          ulIsPlmnRatSupported;
    VOS_UINT32                          ulIsEPlmnListValid;

    ulIsPlmnInEplmnList = VOS_FALSE;

    ulIsEPlmnListValid  = VOS_FALSE;

    /* 判断EPLMN列表是否为VPLMN的等效PLMN列表,例如之前注册成功,重选到接入禁止网络,此时EPLMN列表不为当前网络的EPLMN列表 */
    if (pstEplmnList->ucEquPlmnNum != 0)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstVPlmnId, &(pstEplmnList->astEquPlmnAddr[0])))
        {
            ulIsEPlmnListValid = VOS_TRUE;
        }
    }

    /* 判断高优先级网络的接入技术是否支持,如果高优先级网络在EPLMN中且接入技术
       当前支持，则返回VOS_TRUE,多模时EPLMN不分接入技术 */
    ulIsPlmnRatSupported = NAS_MMC_IsPlmnRatSupported(pstHighPrioPlmnInfo);

    /* 根据23.122 4.4.3.3:In the case
    that the mobile has a stored "Equivalent PLMNs" list the mobile shall
    only select a PLMN if it is of a higher priority than those of the same
    country as the current serving PLMN which are stored in the "Equivalent
    PLMNs" list,此时不需要搜索,最高优先级的网络已经在EPLMN列表中返回VOS_TRUE,
    EPLMN是从数组下标1开始存放的，数组下标0存放的是RPLMN */
    if (VOS_TRUE == ulIsEPlmnListValid)
    {
        ulIsPlmnInEplmnList = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstHighPrioPlmnInfo->stPlmnId),
                                                         pstEplmnList->ucEquPlmnNum - 1,
                                                         &pstEplmnList->astEquPlmnAddr[1]);
    }

    if ((VOS_TRUE == ulIsPlmnInEplmnList)
     && (VOS_TRUE == ulIsPlmnRatSupported))
    {
        return VOS_TRUE;
    }

    /* h) If the PLMN of the highest priority PLMN/access technology combination
    available is the current VPLMN,or one of the PLMNs in the ""Equivalent PLMNs""
    list,the MS shall remain on the current PLMN/access technology combination. */
    /* 当前驻留的网络PLMN ID和最高优先级的网络一致,
       且该高优先级网络支持的接入技术当前支持返回VOS_TRUE */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstVPlmnId, &(pstHighPrioPlmnInfo->stPlmnId)))
    {
        /* 如果VPLMN是HPLMN, 即使当前的接入技术和最高优先级不同也认为已在最高优先级 */
        if (VOS_TRUE == NAS_MMC_IsCampOnHPlmn())
        {
            return VOS_TRUE;
        }

        for (i = 0; i < pstHighPrioPlmnInfo->ucRatNum; i++)
        {
            if (pstHighPrioPlmnInfo->astPlmnRatInfo[i].enRatType == enRat)
            {
                return VOS_TRUE;
            }
        }

        /* If the PLMN of the highest priority PLMN/access technology combination
          available is the current VPLMN,or one of the PLMNs in the ""Equivalent PLMNs"" list,
          the MS shall remain on the current PLMN/access technology combination.
          与VPLMN相同国家码的最高优先级的网络的在当前网络环境中存在，且VPLMN和最高优先级的网络
          的PLMN相同。（例如：VPLMN为G的23002，USIM卡中最高优先级网络为W的23002且状态
          为SEARCHED_EXIST，则认为已驻留在最高优先级网络上*/
        for (i = 0; i < pstHighPrioPlmnInfo->ucRatNum; i++)
        {
            /* Modified by z00234330 for PCLINT清理, 2014-06-24, begin */
            if ((VOS_TRUE ==  NAS_MML_IsNetRatSupported(pstHighPrioPlmnInfo->astPlmnRatInfo[i].enRatType))
             && (NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstHighPrioPlmnInfo->astPlmnRatInfo[i].enNetStatus))
            /* Modified by z00234330 for PCLINT清理, 2014-06-24, end */
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetNextSearchHighPrioPlmn
 功能描述  : 获取下一个需要搜索的高优先级网络
 输入参数  : pstHighPrioPlmnSearchListInfo:需要搜索的高优先级列表
             pstVPlmn:高优先级搜网之前驻留的VPLMN信息
             pstEplmnList:高优先级搜网之前驻留VPLMN的等效PLMN信息
 输出参数  : pstHighPrioPlmnInfo: 高优先级PLMN
 返 回 值  : VOS_TRUE:获取成功
             VOS_FALSE:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月9日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2014年2月22日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search调整:驻留VPLMN为HPLMN时不比较优先级
 3.日    期   : 2014年4月10日
   作    者   : w00242748
   修改内容   : DTS2014040905679:接入技术顺序030201，当前驻留在GSM上，
                高优先级接入技术HPLMN搜索L失败，搜索W成功并成功注册后，再次
                启动高优先级接入技术HPLMN时，定时器时长不正确。
 4.日    期   : 2015年2月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
 5.日    期   : 2015年11月23日
   作    者   : z00359541
   修改内容   : DTS2015111706562:TAU被网络#17拒绝5次DISABLE LTE，后续背景搜
                又ENABLE LTE导致又会发起TAU被网络#17拒绝。TAU期间收不到网络寻呼
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextSearchHighPrioPlmn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchListInfo,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstHighPrioPlmnInfo,
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstVPlmn,
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsPlmnSearchingAllowed;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnSelectionPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulCampHplmnFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulIsPlmnSupportDam;
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    /* Added by c00318887 for 移植T3402 , 2015-6-23, begin */
    VOS_UINT8                                               ucHighRatBgProc;
    /* Added by c00318887 for 移植T3402 , 2015-6-23, end*/
    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();
#endif


    ulCampHplmnFlg              = NAS_MML_ComparePlmnIdWithHplmn(&pstVPlmn->stPlmnId);

    /* 获取当前接入技术优先级信息 */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    for ( i = 0 ; i < pstHighPrioPlmnSearchListInfo->usSearchPlmnNum; i++ )
    {
        pstPlmnSelectionPlmnInfo = &(pstHighPrioPlmnSearchListInfo->astPlmnSelectionList[i]);

        /* 该PLMN与VPLMN国家码是否相同,如果不相同,则不进行搜索 */
        if ( VOS_FALSE == NAS_MMC_IsHighPrioPlmnSameCountry(pstPlmnSelectionPlmnInfo,
                                                                 &pstVPlmn->stPlmnId))
        {
            continue;
        }

        /* 当前VPLMN是HPLMN,HPLMN的BG搜比较特殊,需要特殊处理 */
        if (VOS_TRUE == ulCampHplmnFlg)
        {
            /* 获取到的高优先级PLMN不是HPLMN则跳过 */
            if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(&pstPlmnSelectionPlmnInfo->stPlmnId))
            {
                continue;
            }
        }
        else
        {
            /* 非高优先级RAT的HPLMN搜索时,比较VPLMN和高优先级网络优先级是否相同，如果相同返回VOS_FALSE */
            if (VOS_TRUE == NAS_MMC_CompareVPlmnPrioWithHighPrioPlmn(&pstVPlmn->stPlmnId,
                                                                      pstVPlmn->enRat, pstEplmnList, pstPlmnSelectionPlmnInfo))
            {
                return VOS_FALSE;
            }
        }


        /* 按SYSCFG设置的接入技术优先级依次查找,当需要跳过的当前的高优先级PLMN时则退出 */
        for (k = 0; k < pstPrioRatList->ucRatNum; k++)
        {
            /* 根据SYSCFG设置和该Plmn支持的接入技术获取该plmn Id和接入技术以及存在状态 */
            for (j = 0; j < pstPlmnSelectionPlmnInfo->ucRatNum; j++)
            {
                /* 网络接入技术支持且状态需为未搜索或搜索已存在 */
                if (pstPrioRatList->aucRatPrio[k] == pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType)
                {
                    ulIsPlmnSearchingAllowed = NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy(&(pstPlmnSelectionPlmnInfo->stPlmnId),
                                                                                         pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType,
                                                                                         pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enNetStatus,
                                                                                         VOS_FALSE);
                    if (VOS_FALSE == ulIsPlmnSearchingAllowed)
                    {
                        /* 存储的接入技术不会有重复 */
                        break;
                    }

#if (FEATURE_ON == FEATURE_LTE)
                    /* 已经Disable L,且高优先级网络是lte的，且DAM特性生效则不bg搜lte的网络，不enable lte */
                    if (((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
                      || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapabilityStatus))
                      && (NAS_MML_NET_RAT_TYPE_LTE == pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType))
                    {
                        /* 如果之前disable lte的网络是支持DAM的网络，且禁止接入技术网络列表特性9014 nv未开启，
                          则无需enable lte,AT&T LTE-BTR-1-1840用例要求只禁止310410 lte网络，漫游lte网络可用，
                          后该用例删除，如果后续有需要测试，可以DAM nv项进行测试 */
                        ulIsPlmnSupportDam = NAS_MML_IsPlmnSupportDam(NAS_MMC_GetDisabledLtePlmnId());

                        if ((VOS_FALSE == NAS_MML_GetAddDamPlmnInDisablePlmnWithRatListFlag())
                          && (VOS_TRUE == ulIsPlmnSupportDam))
                        {
                            continue;
                        }
                        
                        /* Added by c00318887 for 移植T3402 , 2015-6-23, begin */
                        ucHighRatBgProc = NAS_MMC_IsHighPrioRatHplmnSearch_BgPlmnSearch();
                        /* 高优先级RAT不ENABLE LTE特性生效则不bg搜lte的网络，不enable lte */
                        if ( (NAS_MML_HIGH_PRIO_RAT_BG_SEARCH_PROC_LTE_NOT_ENABLE_LTE == NAS_MML_GetHighPrioRatBgEnableLteFlag())
                          && (VOS_TRUE == ucHighRatBgProc))
                        {
                            continue;
                        }    
                        /* Added by c00318887 for 移植T3402 , 2015-6-23, end */
                        if  (VOS_TRUE == ulCampHplmnFlg)
                        {
                            continue;
                        }
                    }
#endif

                    /* 驻留HPLMN上且获取到的高优先级RAT与VPLMN的RAT一致则跳过获取高优先级搜网列表中的下个索引的PLMN */
                    /* 直接在构造搜网列表时过滤 */

                    pstHighPrioPlmnInfo->stPlmnId                      = pstHighPrioPlmnSearchListInfo->astPlmnSelectionList[i].stPlmnId;
                    pstHighPrioPlmnInfo->ucRatNum                      = 1;
                    pstHighPrioPlmnInfo->astPlmnRatInfo[0].enRatType   = pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType;
                    pstHighPrioPlmnInfo->astPlmnRatInfo[0].enNetStatus = pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enNetStatus;

                    /* 获取成功返回VOS_TRUE */
                    return VOS_TRUE;

                }
            }
        }

    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetHighestPrioPlmnFromHighPrioPlmnList
 功能描述  : 从高优先级列表中得到最高优先级的网络
 输入参数  : pstPlmnSelectionListInfo:需要搜索的高优先级列表
 输出参数  : pstHighPrioPlmnInfo: 最高优先级PLMN
 返 回 值  : VOS_TRUE:获取成功
             VOS_FALSE:获取失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月24日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetHighestPrioPlmnInHighPrioPlmnList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstHighPrioPlmnInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId = VOS_NULL_PTR;

    /* 取得当前驻留的PLMN ID */
    pstCurrCampPlmnId = NAS_MML_GetCurrCampPlmnId();

    for ( i = 0 ; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++ )
    {
        /* 只取国家码相同的PLMN */
        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstCurrCampPlmnId->ulMcc, pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId.ulMcc))
        {
            continue;
        }

        /* 如果最高优先级网络接入技术不支持,继续取下一个 */
        if (VOS_FALSE == NAS_MMC_IsPlmnRatSupported(&pstPlmnSelectionListInfo->astPlmnSelectionList[i]))
        {
            continue;
        }

        PS_MEM_CPY(pstHighPrioPlmnInfo, &pstPlmnSelectionListInfo->astPlmnSelectionList[i], sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

        return VOS_TRUE;
    }

    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : NAS_MMC_DelSpecPlmnWithRatInPlmnList
 功能描述  : 在列表中删除指定的PLMN
 输入参数  :
             NAS_MML_PLMN_ID_STRU                   *pstPlmnId,
             NAS_MML_NET_RAT_TYPE_ENUM_UINT8         enRat,
             NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstPlmnSelectionListInfo
 输出参数  : pstPlmnSelectionListInfo
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月4日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_DelSpecPlmnWithRatInPlmnList (
    NAS_MML_PLMN_ID_STRU                   *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8         enRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* 删除重复的PLMN */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; )
    {
        for (j = 0; j < pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum; )
        {
            if ((VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId,
                                                               &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId)))
             && (enRat == pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType))
            {
                /*lint -e961*/
                /* 删除相应的RAT */
                (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j]),
                            &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j + 1]),
                            ((pstPlmnSelectionListInfo->astPlmnSelectionList[i]).ucRatNum - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                /*lint +e961*/
                pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum--;

            }
            else
            {
                j++;
            }
        }

        /* 接入技术个数为0时，删除相应的PLMN ID */
        if (0 == pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum)
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                        &(pstPlmnSelectionListInfo->astPlmnSelectionList[i + 1]),
                        (pstPlmnSelectionListInfo->usSearchPlmnNum - i - 1) * sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
            /*lint +e961*/
            pstPlmnSelectionListInfo->usSearchPlmnNum--;
        }
        else
        {
            i++;
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_MMC_AddEHPlmnInPlmnSelectionList
 功能描述  : 向搜网列表中加入EHPLMN或HPLMN
 输入参数  : pstSearchedPlmnListInfo,搜索到的列表
 输出参数  : pstPlmnSelectionList,列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年01月02日
   作    者   : w00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_AddSearchedPlmnListInfoInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stPrioRatList;

    if (VOS_NULL_PTR == pstSearchedPlmnListInfo)
    {
        return;
    }

    /* 将接入层在AREA_LOST消息中上报的其他模的网络加入选网列表 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (NAS_MML_NET_RAT_TYPE_BUTT == pstSearchedPlmnListInfo[i].enRatType)
        {
            continue;
        }

        stPrioRatList.ucRatNum      = 1;
        stPrioRatList.aucRatPrio[0] = pstSearchedPlmnListInfo[i].enRatType;

        /* 将高质量网络接入选网列表 */
        for (j = 0; j < pstSearchedPlmnListInfo[i].ulHighPlmnNum; j++)
        {
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstSearchedPlmnListInfo[i].astHighPlmnList[j]),
                                                   NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }

        /* 将低质量网络接入选网列表 */
        for (j = 0; j < pstSearchedPlmnListInfo[i].ulLowPlmnNum; j++)
        {
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstSearchedPlmnListInfo[i].astLowPlmnList[j].stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_GetSpecRatCoverageTypeInSearchedPlmnList
 功能描述  : 从搜网列表中获取指定RAT的覆盖类型
 输入参数  : pstSearchedPlmnListInfo,搜索到的列表
             enRatType;指定的接入技术类型
 输出参数  : penCoverType,接入技术覆盖类型
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年11月06日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_GetSpecRatCoverageTypeInSearchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRatType,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8                       *penCoverType
)
{
    VOS_UINT32                                              i;

    /* 将接入层在AREA_LOST消息中上报的其他模的网络加入选网列表 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRatType == pstSearchedPlmnListInfo[i].enRatType)
        {
            *penCoverType = pstSearchedPlmnListInfo[i].enCoverType;
            break;
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList
 功能描述  : 从搜网列表中获取指定RAT的覆盖类型
 输入参数  : pstSearchRatInfo,搜索到的RAT列表
             enRatType;指定的接入技术类型
 输出参数  : penCoverType,接入技术覆盖类型
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年11月06日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
NAS_MMC_COVERAGE_TYPE_ENUM_UINT8 NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRatType
)
{
    VOS_UINT32                                              i;

    /* 将接入层在AREA_LOST消息中上报的其他模的网络加入选网列表 */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRatType == pstSearchRatInfo[i].enRatType)
        {
            return pstSearchRatInfo[i].enCoverageType;
        }
    }

    return NAS_MMC_COVERAGE_TYPE_BUTT;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedNcellSearch
 功能描述  : 判断是否需要进行ncell搜网
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要进行ncell搜网；VOS_FALSE:不需要进行ncell搜网
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年12月24日
   作    者   : z00161729
   修改内容   : SVLTE支持NCELL搜网
 2.日    期   : 2014年1月26日
   作    者   : z00161729
   修改内容   : DTS2014012305088：支持增强NCELL搜网，如果Modem1传递过来的邻区信息不存在的情况下，通过历史频点支持NCELL搜索。
*****************************************************************************/
VOS_UINT8  NAS_MMC_IsNeedNcellSearch(VOS_VOID)
{
    VOS_UINT32                          ulCurNcellSearchTimerCount;
    VOS_UINT32                          ulTotalNcellSearchTimerCount;
    VOS_UINT8                           ucNcellSearchFlag;


    VOS_UINT8                           ucNcellSearchTimerLen;

    VOS_UINT8                           ucPsAttachAllowFlag;
    VOS_UINT8                           ucCsAttachAllowFlag;

    ulCurNcellSearchTimerCount   = NAS_MMC_GetCurNcellSearchTimerCount_OnPlmn();
    ucNcellSearchFlag            = NAS_MMC_GetNcellSearchFlag();
    ulTotalNcellSearchTimerCount = 0;
    ucPsAttachAllowFlag          = NAS_MML_GetPsAttachAllowFlg();
    ucCsAttachAllowFlag          = NAS_MML_GetCsAttachAllowFlg();

    /* 如果当前搜索的次数不超过available 定时器的第一次次数,使用第一次时长,否则使用第二次的 */
    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        ucNcellSearchTimerLen        = NAS_MMC_GetNcellSearchFirstTimerLen();

        if (0 != ucNcellSearchTimerLen)
        {
            ulTotalNcellSearchTimerCount = ((NAS_MMC_GetPhaseOnePeriodicSleepTimerLen()) / ucNcellSearchTimerLen);
        }
    }
    else
    {
        ucNcellSearchTimerLen        = NAS_MMC_GetNcellSearchSecondTimerLen();

        if (0 != ucNcellSearchTimerLen)
        {
            ulTotalNcellSearchTimerCount = ((NAS_MMC_GetPhaseTwoPeriodicSleepTimerLen()) / ucNcellSearchTimerLen);
        }
    }

    /* 1、svlte 特性开启
       2、支持ncell快速搜网nv开启
       3、modem1 gas上报存在t或l的邻区频点信息或邻区个数为0时也需启动ncell搜定时器
       4、当前为PS attach not allow/cs attach not allow,防止国外情况开启该功能
       5、ncell搜网次数未达到n(第M阶段的搜网间隔时间/ NcellQuickSearchTimer)次
          则available定时器时长启动为ncell搜网时长 */
    if ((VOS_TRUE == ucNcellSearchFlag)
     && (ulCurNcellSearchTimerCount < ulTotalNcellSearchTimerCount)
     && (VOS_FALSE == ucPsAttachAllowFlag)
     && (VOS_FALSE == ucCsAttachAllowFlag))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedChangeNcellSearchRatOrder
 功能描述  : 判断ncell搜网时候，是否需要T L艘网顺序反向，防止始终搜索同一个RAT；
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要反向；VOS_FALSE:不需要进行反向
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年5月28日
   作    者   : x00203213
   修改内容   : SVLTE支持NCELL搜网顺序反转
 *****************************************************************************/

VOS_UINT8 NAS_MMC_IsNeedChangeNcellSearchRatOrder(VOS_VOID)
{
    VOS_UINT8                                               ucCampOnHighRatFlag;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList        = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCampOnRatType;
    VOS_UINT8                                               ucSvlteSupportFlag;
    VOS_UINT8                                               ucPsTransferOffAreaModeFlag;
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8 enSpecPlmnSearchState;

    ucCampOnHighRatFlag             = VOS_FALSE;
    ucSvlteSupportFlag                  = NAS_MML_GetSvlteSupportFlag();
    ucPsTransferOffAreaModeFlag	= NAS_MML_GetPsTransferOffAreaModeFlag();
    enSpecPlmnSearchState          = NAS_MMC_GetSpecPlmnSearchState();

    /* 获取优先级列表 */
    pstRatPrioList     = NAS_MML_GetMsPrioRatList();

    /*当前支持一个RAT，不需要反转*/
    if (2 > pstRatPrioList->ucRatNum)
    {
         return VOS_FALSE;
    }


    /* 获取驻留RAT */
    enCampOnRatType = NAS_MML_GetCurrNetRatType();

    /*驻留在非最低优先级网络上才有需要反转*/
    if ((pstRatPrioList->aucRatPrio[pstRatPrioList->ucRatNum -1] != enCampOnRatType )
    &&  ( NAS_MML_NET_RAT_TYPE_BUTT != enCampOnRatType ))
    {
         ucCampOnHighRatFlag = VOS_TRUE;
    }

    /*满足如下条件需要反族:
          1、svlte 特性开启
          2、支持离网特性NV 开启
          3、当前在高优先级的RAT 上驻留
          4 、当前已经完成驻留
    */
    if ((VOS_TRUE == ucSvlteSupportFlag)
          && (VOS_TRUE == ucPsTransferOffAreaModeFlag)
          && (VOS_TRUE == ucCampOnHighRatFlag)
          && (NAS_MMC_SPEC_PLMN_SEARCH_STOP == enSpecPlmnSearchState))
    {
        return VOS_TRUE;
    }

   return VOS_FALSE;

}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MMC_IsLtePlmnSearchingAllowed_PlmnSelectionStrategy
 功能描述  : 判断LTE的PLMN ID是否运行搜索
 输入参数  : pstPlmnId:需要判断的PLMN ID
 输出参数  : 无
 返 回 值  : VOS_TRUE  : PLMN ID可以搜索
             VOS_FALSE : PLMN ID不可以搜索
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2012年03月8日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2012年11月8日
   作    者   : s00217060
   修改内容   : DTS2012102902559 调整：SIM卡时设置成LTE only，不去掉L模，但此时搜网时不搜L模
 3.日    期   : 2014年2月24日
   作    者   : w00176964
   修改内容   : High_Rat_Hplmn_Search特性调整:BG搜时对于disable L的情况不过滤L的网络
 4.日    期   : 2015年9月19日
   作    者   : y00346957
   修改内容   : add for DTS2015070910885
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsLtePlmnSearchingAllowed_PlmnSelectionStrategy(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;
    VOS_UINT32                                              ulEnableRoaming;
    VOS_UINT32                                              aulComparedMccList[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER];
    VOS_UINT32                                              ulState;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    enSimType = NAS_MML_GetSimType();

    ulEnableRoaming   = VOS_TRUE;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 判断当前选择的PLMN是否满足优先级要求 */
    if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(pstPlmnId))
    {
        NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_IsLtePlmnSearchingAllowed_PlmnSelectionStrategy:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                             pstPlmnId->ulMcc, pstPlmnId->ulMnc);
        return VOS_FALSE;
    }
#endif

    /* 禁止LTE国际漫游时 */
    if (VOS_FALSE == NAS_MML_GetLteRoamAllowedFlg())
    {
        NAS_MML_GetRoamEnabledMccList(aulComparedMccList);

        /* 判断该PLMN ID的MCC是否在允许驻留的MCC列表中 */
        ulEnableRoaming = NAS_MML_IsMccInDestMccList(pstPlmnId->ulMcc, NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER, aulComparedMccList);
    }

    /* 获取LTE能力状态 */
    enLCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

    /* 满足如下条件,则不需要搜索LTE的网络:
        1)当前网络的接入技术为L且当前PS域卡无效
        2)当前网络的接入技术为L且当前DISABLE LTE
        3)LTE禁止国际漫游
        4)卡类型为SIM卡:对应的场景为:SIM卡时设置成LTE only，不去掉L模，但此时搜网时不搜L模
    */
    if ((VOS_FALSE                             == NAS_MML_GetSimPsRegStatus())
     || (VOS_FALSE == ulEnableRoaming)
     || (NAS_MML_SIM_TYPE_SIM == enSimType))
    {
        NAS_NORMAL_LOG2(WUEPS_PID_MMC, "NAS_MMC_IsLtePlmnSearchingAllowed_PlmnSelectionStrategy ulEnableRoaming,enSimType",ulEnableRoaming,enSimType);        
        
        return VOS_FALSE;
    }

    ulState = NAS_MMC_GetFsmTopState();

    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLCapabilityStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLCapabilityStatus))
    {
        /* BG搜网流程中获取下个高优先级网络时不过滤disable L模的网络 */
        if ((NAS_MMC_FSM_BG_PLMN_SEARCH                             == NAS_MMC_GetCurrFsmId())
         && ((NAS_MMC_BG_PLMN_SEARCH_STA_INIT                        == ulState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF == ulState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF == ulState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF == ulState)))
        {
            /* PS卡不允许注册,不需要重新 Enable L */
            if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
            {
                return VOS_FALSE;
            }

            /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
            if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
            {
                return VOS_FALSE;
            }

            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#endif


/*****************************************************************************
 函 数 名  : NAS_MMC_InitPlmnSelectionList_HighPrioPlmnSearch
 功能描述  : 高优先级搜网状态机启动时，搜网列表初始化
 输入参数  : 无
 输出参数  : pstPlmnSelectionList - 高优先级搜网列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月20日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_HighPrioRatHplmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;

    NAS_MMC_SetPlmnSelectionListType(NAS_MMC_STORE_HIGH_PRIO_PLMN_SELECTION_LIST);

    /* Added by w00176964 for coverity清理, 2014-3-10, begin */
    PS_MEM_SET(&stPlmnInfo, 0x0, sizeof(stPlmnInfo));
    /* Added by w00176964 for coverity清理, 2014-3-10, end */

    /* 获取EHPLMN */
    pstEHPlmnInfo = NAS_MML_GetSimEhplmnList();


    for (i = 0; i< pstEHPlmnInfo->ucEhPlmnNum; i++)
    {
        /* 根据SIM卡的接入技术信息、网络ID、网络类型构造选网列表中PLMN ID信息 */
        NAS_MMC_BuildPlmnSelectionPlmnInfo_ForHighPrioRatHplmnSearch(NAS_MMC_PLMN_TYPE_HPLMN,
                                           &(pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId),
                                           &stPlmnInfo);

        /* 添加到搜网列表 */
        if (VOS_FALSE == NAS_MMC_IsPlmnInSearchList(stPlmnInfo, pstHighPrioPlmnSearchListInfo))
        {
            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstHighPrioPlmnSearchListInfo);
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnInSearchList
 功能描述  : 检查指定的Plmn是否在构造的搜网列表中
 输入参数  : stPlmnId:PLMN ID
            pstHighPrioPlmnSearchListInfo: 构造的搜网列表
 输出参数  : pstPlmnInfo,支持的接入技术个数
 返 回 值  : VOS_TRUE: 已经存在
            VOS_FALSE: 不存在
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月27日
   作    者   : f00261443
   修改内容   : 新生成函数
 2.日    期   : 2014年9月29日
   作    者   : b00269685
   修改内容   : DTS2014092900118修改

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnInSearchList(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchListInfo
)
{
    VOS_UINT32                          ulPlmnNum;
    NAS_MML_PLMN_ID_STRU                stPlmnId;

    PS_MEM_SET(&stPlmnId, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    for (ulPlmnNum = 0; ulPlmnNum < pstHighPrioPlmnSearchListInfo->usSearchPlmnNum; ulPlmnNum++)
    {
        PS_MEM_CPY(&stPlmnId, &(pstHighPrioPlmnSearchListInfo->astPlmnSelectionList[ulPlmnNum].stPlmnId), sizeof(stPlmnId));
        if ((stPlmnId.ulMcc == stPlmnInfo.stPlmnId.ulMcc)
         && (stPlmnId.ulMnc == stPlmnInfo.stPlmnId.ulMnc))
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_BuildPlmnSelectionPlmnInfo_ForHighPrioRatHplmnSearch
 功能描述  : 构造选网列表中单个PLMN信息
 输入参数  : enPlmnType:网络类型
            pstPlmnId:PLMN ID
 输出参数  : pstPlmnInfo,支持的接入技术个数
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年2月27日
   作    者   : f00261443
   修改内容   : 新生成函数
 2.日    期   : 2014年4月10日
   作    者   : w00242748
   修改内容   : DTS2014040905679:接入技术顺序030201，当前驻留在GSM上，
                高优先级接入技术HPLMN搜索L失败，搜索W成功并成功注册后，再次
                启动高优先级接入技术HPLMN时，定时器时长不正确。

*****************************************************************************/
VOS_VOID NAS_MMC_BuildPlmnSelectionPlmnInfo_ForHighPrioRatHplmnSearch(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo
)
{
    VOS_UINT8                           ucRatNum;
    VOS_UINT8                           i;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPlmnRatPrio = VOS_NULL_PTR;

    ucRatNum                = 0x0;
    pstPlmnRatPrio = NAS_MML_GetMsPrioRatList();

    PS_MEM_CPY(&pstPlmnInfo->stPlmnId, pstPlmnId, sizeof(NAS_MML_PLMN_ID_STRU));
    pstPlmnInfo->enPlmnType = enPlmnType;

    for (i = 0; i < pstPlmnRatPrio->ucRatNum; i++)
    {
        /* 构造高优先级接入技术HPLMN列表时，直接将优先级比当前接入技术低的接入技术过滤掉 */
        if ( pstPlmnRatPrio->aucRatPrio[i] == NAS_MML_GetCurrNetRatType() )
        {
            break;
        }

        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enRatType   = pstPlmnRatPrio->aucRatPrio[i];
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        ucRatNum++;

    }

    pstPlmnInfo->ucRatNum = ucRatNum;
    /* 数组剩余位置赋值为无效值 */
    for (; ucRatNum < NAS_MML_MAX_RAT_NUM; ucRatNum++)
    {
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_BUTT;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_BUTT;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_BUTT;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsPlmnIdInSearchedPlmnList
 功能描述  : 检查指定的Plmn是否在构造的搜网列表中
 输入参数  : stPlmnId:PLMN ID
             pstSearchedPlmnListInfo: 构造的搜网列表
 输出参数  : pstPlmnInfo,支持的接入技术个数
 返 回 值  :VOS_TRUE: 已经存在
            VOS_FALSE: 不存在
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年4月4日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnIdInSearchedPlmnList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                          ulHighPlmnIndex;
    VOS_UINT32                          ulLowPlmnIndex;
    VOS_UINT8                           ucRatIndex;

    if (VOS_NULL_PTR == pstSearchedPlmnListInfo)
    {
        return VOS_FALSE;
    }

    for (ucRatIndex = 0; ucRatIndex < NAS_MML_MAX_RAT_NUM; ucRatIndex++)
    {
        if (NAS_MML_NET_RAT_TYPE_BUTT == pstSearchedPlmnListInfo[ucRatIndex].enRatType)
        {
            continue;
        }

        for (ulHighPlmnIndex = 0; ulHighPlmnIndex < pstSearchedPlmnListInfo[ucRatIndex].ulHighPlmnNum; ulHighPlmnIndex++)
        {
            if ((pstPlmnId->ulMcc == pstSearchedPlmnListInfo[ucRatIndex].astHighPlmnList[ulHighPlmnIndex].ulMcc)
             && (pstPlmnId->ulMnc == pstSearchedPlmnListInfo[ucRatIndex].astHighPlmnList[ulHighPlmnIndex].ulMnc))
            {
                return VOS_TRUE;
            }
        }

        for (ulLowPlmnIndex = 0; ulLowPlmnIndex < pstSearchedPlmnListInfo[ucRatIndex].ulLowPlmnNum; ulLowPlmnIndex++)
        {
            if ((pstPlmnId->ulMcc == pstSearchedPlmnListInfo[ucRatIndex].astLowPlmnList[ulLowPlmnIndex].stPlmnId.ulMcc)
             && (pstPlmnId->ulMnc == pstSearchedPlmnListInfo[ucRatIndex].astLowPlmnList[ulLowPlmnIndex].stPlmnId.ulMnc))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}


/*lint -restore */


/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateExistRplmnOrHplmnFlag_InitPlmnSelectionList
 功能描述  : 初始化列表时更新是否存在RPLMN或HPLMN标志
 输入参数  : NAS_MML_PLMN_WITH_RAT_STRU                             *pstSearchedPlmn
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月22日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateExistRplmnOrHplmnFlag_InitPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSearchedPlmn
)
{
    /* PLMN无效时，不更新标志 */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(&(pstSearchedPlmn->stPlmnId)))
    {
        return;
    }

    /* 获取地理位置信息时的PLMN对应的国家码与rplmn相同 */
    if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithRplmn(pstSearchedPlmn->stPlmnId.ulMcc))
    {
        NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
        return;
    }

    /* 获取地理位置信息时的PLMN对应的国家码与hplmn相同 */
    if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithHplmn(pstSearchedPlmn->stPlmnId.ulMcc))
    {
        NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection
 功能描述  : 判断初始化选网列表时是否需要对搜网列表进行排序
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要重新排序
             VOS_FALSE - 不需要重新排序
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月11日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene,
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSearchedPlmn
)
{
    /* 测试卡 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* 漫游搜网优化排序定制关闭不处理 */
    if (VOS_FALSE == NAS_MMC_GetRoamPlmnSelectionSortActiveFlg())
    {
        return VOS_FALSE;
    }

    /* 手动搜网模式不处理该消息 */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return VOS_FALSE;
    }

    /* PLMN无效时，不对DPLMN/UPLMN/OPLMN/AVAILABLE PLMN 排序 */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(&(pstSearchedPlmn->stPlmnId)))
    {
        return VOS_FALSE;
    }

    /* 获取地理位置信息时的PLMN对应的国家码是否和rplmn或hplmn相同 */
    if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithRplmn(pstSearchedPlmn->stPlmnId.ulMcc))
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithHplmn(pstSearchedPlmn->stPlmnId.ulMcc))
    {
        return VOS_FALSE;
    }

    /* 漫游搜网定制开启，目前只有开机选网、SYSCFG触发的选网，才会在初始化列表时进行漫游排序
       后续如果有其他场景在初始化列表时需要排序再添加 */
    if ((NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON    != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET   != enPlmnSearchScene))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_SortRoamPlmnSelectionList_InitPlmnSelectionList
 功能描述  : 初始化列表时对漫游网络进行排序
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月11日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MMC_SortRoamPlmnSelectionList_InitPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSearchedPlmn,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList  = VOS_NULL_PTR;


    /* 开机漫游场景或syscfg触发的搜网对漫游搜网列表排序，原则如下:
     1、开机搜网MMA带下来的网络放在漫游搜网列表前面,在NPLMN中的网络不添加，
        支持的所有接入技术都添加，当前搜网的接入技术优先
     2、在gastNetworkNameTbl中找出跟当前存在网络相同国家码的plmn加入漫游搜网列表，
        在NPLMN中的网络不添加，支持的所有接入技术都添加，当前搜网的接入技术优先
     3、根据DPLMN->UPLMN->OPLMN->AVAILABLE PLMN顺序对漫游搜网列表进行排序
    */

    pstPrioRatList  = NAS_MML_GetMsPrioRatList();

    /* 根据pstSearchedPlmn构造stSearchedExistPlmnInfo */
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));

    enPlmnType  = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(pstSearchedPlmn, pstPlmnSelectionListInfo);

    enNetStatus = NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(pstSearchedPlmn, pstPlmnSelectionListInfo);

    if (NAS_MMC_NET_STATUS_BUTT == enNetStatus)
    {
        enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
    }

    stSearchedExistPlmnInfo.usSearchPlmnNum = 1;
    stSearchedExistPlmnInfo.astPlmnSelectionList[0].stPlmnWithRat.enRat             = pstPrioRatList->aucRatPrio[0];
    stSearchedExistPlmnInfo.astPlmnSelectionList[0].stPlmnWithRat.stPlmnId.ulMcc    = pstSearchedPlmn->stPlmnId.ulMcc;
    stSearchedExistPlmnInfo.astPlmnSelectionList[0].stPlmnWithRat.stPlmnId.ulMnc    = pstSearchedPlmn->stPlmnId.ulMnc;
    stSearchedExistPlmnInfo.astPlmnSelectionList[0].enPlmnType                      = enPlmnType;
    stSearchedExistPlmnInfo.astPlmnSelectionList[0].enNetStatus                     = enNetStatus;


    /* 从DPLMN/UPLMN/OPLMN/AVAILABLE PLMN中找出MCC相同的网络，构造漫游列表 */
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    /* 初始化列表排序时，用当前syscfg配置的最高优先级的接入技术，否则比如设置LTE优先级时，可能会优先搜WCDMA */
    NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(pstPrioRatList->aucRatPrio[0],
                                                              &stSearchedExistPlmnInfo,
                                                              &stNewRoamPlmnSelectionList);

    /* 把排过序的roam搜网列表插入搜网列表前面 */
    NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSelectionListInfo);

    /* 设置该接入技术进行过一轮排序 */
    NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[0], VOS_TRUE);

    /* 可维可测,将选网列表输出 */
    NAS_MMC_LogDplmnNplmnList();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_IsNeedSrchCurrCampHpmnRejByCause13
 功能描述  : HPLMN上注册被#13拒之后是否需要继续搜索当前PLMN WITH RAT
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要继续搜索当前注册被#13拒绝的HPLMN
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : 新生成函数
  2.日    期   : 2015年12月9日
    作    者   : s00217060
    修改内容   : DTS2015120709483:循环搜网导致MSCC消息队列满

*****************************************************************************/
VOS_UINT8  NAS_MMC_IsNeedSrchCurrCampHpmnRejByCause13(VOS_VOID)
{
    VOS_UINT8                           ucKeepSrchHplmnEvenRejByCause13Flg;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegRejCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegRejCause;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCurrLai      = VOS_NULL_PTR;

    /* 非用户指定搜网，从全局变量中获取FORBIDEN ROAMING LAS信息 */
    pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();

    enCsRegRejCause = NAS_MML_REG_FAIL_CAUSE_BUTT;
    enPsRegRejCause = NAS_MML_REG_FAIL_CAUSE_BUTT;

    ucKeepSrchHplmnEvenRejByCause13Flg  = NAS_MML_GetKeepSrchHplmnEvenRejByCause13Flg();

    /* 优化特性对测试卡不生效 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* 优化特性未打开时不继续搜当前HPLMN */
    if (VOS_FALSE   == ucKeepSrchHplmnEvenRejByCause13Flg)
    {
        return VOS_FALSE;
    }

    /* 未驻留HPLMN则不继续搜索当前PLMN */
    if (VOS_FALSE   == NAS_MMC_IsCampOnHPlmn())
    {
        return VOS_FALSE;
    }

    /* 获取在该PLMN上的注册被拒原因值 */
    NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                            NAS_MML_GetCurrNetRatType(),
                                            &enCsRegRejCause,
                                            &enPsRegRejCause);


    /* 有一个域被#11拒绝则不继续搜索当前HPLMN */
    if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == enCsRegRejCause)
     || (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == enPsRegRejCause))
    {
        return VOS_FALSE;
    }

    /* 获取当前驻留的LAI */
    pstCurrLai          = NAS_MML_GetCurrCampLai();

    /* 当前驻留的PLMN与forb LA是否相同，相同时意味着在伪基站被#13拒绝，需要继续搜HPLMN;否则不继续搜 */
    if ( VOS_TRUE == NAS_MML_IsLaiInDestLaiList(pstCurrLai, pstForbPlmnInfo->ucForbRoamLaNum, pstForbPlmnInfo->astForbRomLaList) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_MMC_UpdateRegFinishedPlmnNetStatusInPlmnSelectionList
 功能描述  : 注册结束之后，更新当前网络状态到搜网列表中
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_MMC_UpdateRegFinishedPlmnNetStatusInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                   *pstPlmnIdWithRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU        *pstPlmnSelectionListInfo
)
{

    /* 选网状态机下，HPLMN注册被#13拒绝如果需要再搜当前HPLMN，则不更新当前网络的搜索状态 */
    if (VOS_TRUE == NAS_MMC_IsNeedSrchCurrCampHpmnRejByCause13())
    {
        /* 更新当前网络的搜索状态为已搜索并且存在，在此轮高优先级搜网中，还会再搜此网络 */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstPlmnIdWithRat,
                                                NAS_MMC_NET_STATUS_SEARCHED_EXIST,
                                                pstPlmnSelectionListInfo);
    }
    else
    {
        /* 更新当前网络的搜索状态为已注册过，在此轮高优先级搜网中，不会再搜此网络 */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstPlmnIdWithRat,
                                                NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                pstPlmnSelectionListInfo);
    }

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


