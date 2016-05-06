/******************************************************************************

                  版权所有 (C), 2014-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdSysAcqStrategy.c
  版 本 号   : 初稿
  作    者   : C00299064
  生成日期   : 2014年12月15日
  最近修改   :
  功能描述   : CNAS 层状态机系统捕获的搜网策略文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月15日
    作    者   : C00299064
    修改内容   : Added for HRPD
******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsCommonDef.h"
#include "stdlib.h"
#include "CnasHsdSysAcqStrategy.h"
#include "CnasHsdMntn.h"
#include "CnasCcb.h"
#include "CnasPrlApi.h"
#include "CnasHsdAvoidStrategy.h"
#include "CnasHsdFsmSysAcq.h"
#include "hsd_mscc_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_CNAS_HSD_SYS_ACQ_STRATEGY_C

/*lint -save -e958*/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/* 各种搜网场景对应的搜网列表初始化函数，在搜网状态机初始化时使用 */
CNAS_HSD_SCAN_CHANNEL_LIST_BUILD_TBL_STRU           g_astCnasHsdScanChanListBuildTbl[] =
{
    {CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON,              CNAS_HSD_BuildScanChanList_SwitchOn},
    {CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST,            CNAS_HSD_BuildScanChanList_SystemLost},
    {CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION,            CNAS_HSD_BuildScanChanList_Redirection},
    {CNAS_HSD_SYS_ACQ_SCENE_OOC_MRU0,               CNAS_HSD_BuildScanChanList_OocMru0},
    {CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK,        CNAS_HSD_BuildScanChanList_DataCallQuick},
    {CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH,           CNAS_HSD_BuildScanChanList_PilotSearch},
    {CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY,          CNAS_HSD_BuildScanChanList_HighPriority},
    {CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER,             CNAS_HSD_BuildScanChanList_SystemLost},
    {CNAS_HSD_SYS_ACQ_SCENE_CFREQ_LOCK,             CNAS_HSD_BuildScanChanList_CFreqLock},
    {CNAS_HSD_SYS_ACQ_SCENE_OOC_SWITCH_ON,          CNAS_HSD_BuildScanChanList_SwitchOn},
};

/* 在丢网场景下插入MRU0的序列号 */
VOS_UINT8                                           g_aucCnasHsdSystemLostMru0Pos[CNAS_HSD_MRU0_NUM_4_IN_SCAN_LIST] = {2,5,9,14};

/* 各种搜网场景下获取扫描频点对应函数Table */
CNAS_HSD_GET_SCAN_CHANNEL_LIST_TBL_STRU             g_astCnasHsdGetScanChanListTbl[] =
{
    {CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON,              CNAS_HSD_GetScanChanListFromHrpdList_SwitchOn},
    {CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST,            CNAS_HSD_GetScanChanListFromHrpdList_SystemLost},
    {CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION,            CNAS_HSD_GetScanChanListFromHrpdList_Redirection},
    {CNAS_HSD_SYS_ACQ_SCENE_OOC_MRU0,               CNAS_HSD_GetScanChanListFromMru0_Ooc},
    {CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK,        CNAS_HSD_GetScanChanListFromHrpdList_DataCallQuick},
    {CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH,           CNAS_HSD_GetScanChanListFromHrpdList_SwitchOn},
    {CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY,          CNAS_HSD_GetScanChanListFromHrpdList_HighPriority},
    {CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER,             CNAS_HSD_GetScanChanListFromHrpdList_SystemLost},
    {CNAS_HSD_SYS_ACQ_SCENE_OOC_SWITCH_ON,          CNAS_HSD_GetScanChanListFromHrpdList_SwitchOn},
};

/*****************************************************************************
 函 数 名  : CNAS_HSD_IsAcqedHrpdSysMatchTheSysRecs
 功能描述  : 判断CAS上传的SYS是不是和当前的SYS表匹配
 输入参数  : pstHrpdSys               - CAS上报系统
 输出参数  : pucPrio                  - 匹配到的系统的优先级
             pusHrpeSysListMatchIndex - 匹配到的系统在系统表里面的INDEX
 返 回 值  : VOS_TRUE/VOS_FALSE 表示匹配结果
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月10日
   作    者   : C00299064
   修改内容   : 新生成函数
 2.日    期   : 2015年12月30日
   作    者   : z00316370
   修改内容   : DTS2015122407681,修改匹配规则
*****************************************************************************/
VOS_UINT32 CNAS_HSD_IsAcqedHrpdSysMatchTheSysRecs
(
    CNAS_PRL_HRPD_SYSTEM_STRU                              *pstHrpdSys,
    VOS_UINT8                                              *pucPrio,
    VOS_UINT16                                             *pusHrpdSysListMatchIndex
)
{
    VOS_UINT16                                              i;
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstHrpdSysList;

    pstHrpdSysList                      = CNAS_HSD_GetSysRecListAddr();

    CNAS_HSD_GetAcqedHrpdSysMatchIndexList(pstHrpdSys);

    for (i = 0; i < pstHrpdSysList->usHrpdSysNum; i++)
    {
        if (VOS_TRUE == CNAS_HSD_IsAcqedHrpdSysInMatchIndexList(pstHrpdSysList->pstHrpdSysItem[i].usSysIndex))
        {
            *pucPrio                    = pstHrpdSysList->pstHrpdSysItem[i].ucPrioLevel;
            *pusHrpdSysListMatchIndex   = i;
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RefreshScanListByMatchLvl()
 功能描述  : 高LEVEL系统收到低LEVEL系统
 输入参数  : usScanlistPos  - 当前的band channel在scan list中的INDEX
             ucPrio         - 匹配到的SYS RECS里面的优先级
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月10日
   作    者   : C00299064
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RefreshScanListByMatchLvl
(
    VOS_UINT16                          usScanListPos,
    VOS_UINT8                           ucPrio
)
{

    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstScanList;
    CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU   stHsdChannelInfo;
    VOS_UINT16                          i;
    VOS_UINT16                          usIndex;

    usIndex                             = 0;
    pstScanList                         = CNAS_HSD_GetScanFreqListAddr();

    /* 如果当前的PRIO内已经有当前的band channel不需要修改scan list*/
    for (i = usScanListPos + 1; i < pstScanList->usAvailFreqNum; i++)
    {
        if (pstScanList->pstScanFreqItem[i].ucPrioLevel == ucPrio)
        {
            break;
        }
    }

    /* 当前level的最后一个频点匹配上下一个等级，则直接驻留 */
    if (i == (usScanListPos + 1))
    {
        return VOS_TRUE;
    }

    usIndex = i - 1;

    PS_MEM_SET(&stHsdChannelInfo, 0, sizeof(CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU));

    /* 将得到CNF的当前位置的band channel 保存下来 */
    PS_MEM_CPY(&stHsdChannelInfo,
               &pstScanList->pstScanFreqItem[usScanListPos],
               sizeof(CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU));

    stHsdChannelInfo.ucPrioLevel    = ucPrio;

    /* mem move */
    PS_MEM_MOVE(&pstScanList->pstScanFreqItem[usScanListPos],
                &pstScanList->pstScanFreqItem[usScanListPos + 1],
                (usIndex - usScanListPos) * (sizeof(CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU)));

    /* 赋值最后一个 */
    PS_MEM_CPY(&pstScanList->pstScanFreqItem[usIndex],
               &stHsdChannelInfo,
               sizeof(CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU));

    /* 当前的Index 减1 */
    pstScanList->usCurrIndex--;

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_IsCurrFreqStay
 功能描述  : 当前的系统是不是可以驻留
 输入参数  : pstHrpdSys - 当前系统
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 可以驻留
             VOS_FALSE - 不能驻留
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月10日
   作    者   : C00299064
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_IsCurrFreqStay
(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys
)
{
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstScanList;
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysList;
    VOS_UINT8                           ucMatchPrio;
    VOS_UINT8                           ucCurrPrio;
    VOS_UINT16                          usMatchedSysIndex;
    VOS_UINT16                          usCurrIndex;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stCFreqLock;
    CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU  *pstCFreqLockPara;
    CNAS_HSD_1X_SYSTEM_INFO_STRU       *pst1xSys;
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32 enModeType;

    enModeType                          = CNAS_HSD_GetModeType();
    pst1xSys                            = CNAS_HSD_Get1xSystemInfo();
    pstScanList                         = CNAS_HSD_GetScanFreqListAddr();
    pstHrpdSysList                      = CNAS_HSD_GetSysRecListAddr();
    usCurrIndex                         = pstScanList->usCurrIndex - 1;
    ucCurrPrio                          = pstScanList->pstScanFreqItem[usCurrIndex].ucPrioLevel;

    if (VOS_TRUE == CNAS_HSD_GetFreqLockMode())
    {
        pstCFreqLockPara                = CNAS_HSD_GetFreqLockAddr();

        stCFreqLock.enBandClass         = pstCFreqLockPara->usHrpdBandClass;
        stCFreqLock.usChannel           = pstCFreqLockPara->usHrpdFreq;

        if (VOS_TRUE == CNAS_PRL_CmpFreqValue(&pstHrpdSys->stFreq, &stCFreqLock))
        {
            return VOS_TRUE;
        }
        else
        {
            return VOS_FALSE;
        }
    }

    /* 系统中匹配上了 */
    if (VOS_TRUE == CNAS_HSD_IsAcqedHrpdSysMatchTheSysRecs(pstHrpdSys, &ucMatchPrio, &usMatchedSysIndex))
    {
        if (CNAS_PRL_PREF_NEG_SYS_NEG == pstHrpdSysList->pstHrpdSysItem[usMatchedSysIndex].enPrefNegSys)
        {
            return VOS_FALSE;
        }

        if (CNAS_HSD_FREQ_TYPE_REDIRECTION == pstScanList->pstScanFreqItem[usCurrIndex].enFreqType)
        {
            return VOS_TRUE;
        }

        /* 如果HYBRID而且当前1x不存在，直接驻留 */
        if ((CNAS_HSD_1X_SYSTEM_UNAVAILABLE == pst1xSys->enStatus)
        &&  (CNAS_HSD_SYS_MODE_HYBRID == enModeType))
        {
            return VOS_TRUE;
        }

        /* 如果匹配到的优先级比当前SCANList的高或者相等而且不是NEG，直接驻留；
            如果低于当前修改SCANLIST。 */
        if (ucCurrPrio >= ucMatchPrio)
        {
            return VOS_TRUE;
        }
        else
        {
            return CNAS_HSD_RefreshScanListByMatchLvl(usCurrIndex, ucMatchPrio);
        }
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_RefreshScanListIndex
 功能描述  : 更新SCAN LIST的 INDEX
 输入参数  : usFreqNumUsed - 新的current index
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月10日
   作    者   : C00299064
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_RefreshScanListIndex(VOS_UINT16 usFreqNumUsed)
{
    VOS_UINT16                          usCurIndex;

    usCurIndex = CNAS_HSD_GetCurScanFreqIndex();

    usCurIndex += usFreqNumUsed;

    CNAS_HSD_SetCurScanFreqIndex(usCurIndex);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_BuildHrpdScanList
 功能描述  : 根据不同的捕获场景，构造扫描列表
 输入参数  : enSysAcqScene - 捕获场景
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月12日
   作    者   : C00299064
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_BuildHrpdScanList(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
)
{
    VOS_UINT32                          i;
    pCNasHsdScanChanListBuildFunc       funSysScanListBuild    = VOS_NULL_PTR;

    /* 清空系统表和搜网表 */
    CNAS_HSD_InitSysRecList(CNAS_HSD_INIT_CTX_BUILD_FREQ, CNAS_HSD_GetSysRecListAddr());
    CNAS_HSD_InitScanChanList(CNAS_HSD_INIT_CTX_BUILD_FREQ, CNAS_HSD_GetScanFreqListAddr());

    /* 若启动锁频 */
    if (VOS_TRUE == CNAS_HSD_GetFreqLockMode())
    {
        enSysAcqScene = CNAS_HSD_SYS_ACQ_SCENE_CFREQ_LOCK;
    }

    /* 根据场景在g_astCnasHsdAcqSysListBuildTbl查找搜网列表构造函数 */
    /* 根据场景，频点信息，SYS RECS 生成SCAN LIST */
    for (i = 0; i < (sizeof(g_astCnasHsdScanChanListBuildTbl)/sizeof(CNAS_HSD_SCAN_CHANNEL_LIST_BUILD_TBL_STRU)); i++)
    {
        if (enSysAcqScene == g_astCnasHsdScanChanListBuildTbl[i].enSysAcqScene)
        {
            funSysScanListBuild = g_astCnasHsdScanChanListBuildTbl[i].pfunScanChanListBuild;
            break;
        }
    }

    /* 查找成功时调用初始化函数进行构造 */
    if (VOS_NULL_PTR != funSysScanListBuild)
    {
        funSysScanListBuild(enSysAcqScene);
    }

    /* 存储当前匹配的1X系统*/
    PS_MEM_CPY(CNAS_HSD_GetScanListMatched1xSystemInfo(),
               CNAS_HSD_Get1xSystemInfo(),
               sizeof(CNAS_HSD_1X_SYSTEM_INFO_STRU));


    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_BuildScanChanList_SwitchOn
 功能描述  : 开机扫描频点列表构造
 输入参数  : enSysAcqScene    - 捕获场景

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月12日
   作    者   : C00299064
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_BuildScanChanList_SwitchOn(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32                      enModeType;
    CNAS_HSD_1X_SYSTEM_INFO_STRU                           *pst1xSysInfo;
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstSysList;
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstScanList;

    pstScanList     = CNAS_HSD_GetScanFreqListAddr();
    pstSysList      = CNAS_HSD_GetSysRecListAddr();
    enModeType      = CNAS_HSD_GetModeType();
    pst1xSysInfo    = CNAS_HSD_Get1xSystemInfo();

    /* 生成EVDO LIST */
    if (VOS_FALSE == CNAS_HSD_CreateHrpdSysList(enModeType, pst1xSysInfo, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_SwitchOn: create hrpd list fail!");
        return;
    }

    CNAS_HSD_LogSysRecList(pstSysList, enSysAcqScene);

    /* 生成SWITCH ON SCAN LIST */
    if (VOS_FALSE == CNAS_HSD_CreateScanFreqList(enSysAcqScene, pstScanList, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_SwitchOn: create freq list fail!");
        return;
    }

    CNAS_HSD_LogScanFreqList(pstScanList, enSysAcqScene);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_BuildScanChanList_PilotSearch
 功能描述  : 开机扫描频点列表构造
 输入参数  : enSysAcqScene    - 捕获场景

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年01月15日
   作    者   : x00306642
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_BuildScanChanList_PilotSearch(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32                      enModeType;
    CNAS_HSD_1X_SYSTEM_INFO_STRU                           *pst1xSysInfo;
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstSysList;
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstScanList;

    pstScanList     = CNAS_HSD_GetScanFreqListAddr();
    pstSysList      = CNAS_HSD_GetSysRecListAddr();
    enModeType      = CNAS_HSD_GetModeType();
    pst1xSysInfo    = CNAS_HSD_Get1xSystemInfo();

    /* 生成EVDO LIST */
    if (VOS_FALSE == CNAS_HSD_CreateHrpdSysList(enModeType, pst1xSysInfo, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_PilotSearch: create hrpd list fail!");
        return;
    }

    CNAS_HSD_LogSysRecList(pstSysList, enSysAcqScene);

    /* 生成SWITCH ON SCAN LIST */
    if (VOS_FALSE == CNAS_HSD_CreateScanFreqList(enSysAcqScene, pstScanList, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_PilotSearch: create freq list fail!");
        return;
    }

    CNAS_HSD_LogScanFreqList(pstScanList, enSysAcqScene);

    return;
}
/*****************************************************************************
 函 数 名  : CNAS_HSD_CreateHrpdSysList
 功能描述  : 构造HRPD列表
 输入参数  : enModeType     - 当前的搜网场景类型 (混合、非混合)
             pst1xSysInfo   - 当前1X系统信息(包含 SID/NID Freq
             pstSysList     - 存放Hrpd系统信息地址

 输出参数  : pstSysList     - 获取到的Hrpd系统信息

 返 回 值  : VOS_UINT32     - 构造HRPD列表的结果是成功还是失败
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月18日
   作    者   : C00299064
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_CreateHrpdSysList(
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32                      enModeType,
    CNAS_HSD_1X_SYSTEM_INFO_STRU                           *pst1xSysInfo,
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstSysList
)
{
    VOS_UINT32                                              ulResult;
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU              *pstGeoListInfo = VOS_NULL_PTR;

    if (CNAS_HSD_SYS_MODE_HYBRID == enModeType)
    {
        if (CNAS_HSD_1X_SYSTEM_UNAVAILABLE == pst1xSysInfo->enStatus)
        {
            ulResult = CNAS_HSD_CreateAllHrpdSysRecs(CNAS_PRL_CHECK_ASSN_INCL, CNAS_PRL_SORT_NEEDED, pstSysList);
        }
        else
        {
                /* 根据当前的1X系统获取最匹配的GEO，现在由XSD提供接口 */
            pstGeoListInfo  = (CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU*)VOS_MemAlloc(UEPS_PID_HSD, DYNAMIC_MEM_PT, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU));

            if (VOS_NULL_PTR == pstGeoListInfo)
            {
                CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_CreateHrpdSysList: pstGeoListInfo NULL_PTR!");
                return VOS_FALSE;
            }

            PS_MEM_SET(pstGeoListInfo, 0, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU));

            ulResult = CNAS_HSD_Create1xMatchedHrpdSysRecs(&pst1xSysInfo->st1xSys, pstSysList,pstGeoListInfo);

            VOS_MemFree(UEPS_PID_HSD, pstGeoListInfo);

        }
    }
    else
    {
        ulResult = CNAS_HSD_CreateAllHrpdSysRecs(CNAS_PRL_NO_CHECK_ASSN_INCL, CNAS_PRL_SORT_NEEDED, pstSysList);
    }

    return ulResult;
}
/*****************************************************************************
 函 数 名  : CNAS_HSD_GetScanChanelList
 功能描述  : 根据不同的捕获场景，提取扫描频点列表
 输入参数  : enSysAcqScene       - 捕获场景
             pstHrpdSysRecList   -
             pstHrpdScanFreqList -
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月22日
   作    者   : d00212987
   修改内容   : 新增
*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetScanChanelList(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene,
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysRecList,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList
)
{
    pCNasHsdGetScanChanListFunc         funSysGetScanList    = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    ulResult                  = VOS_FALSE;

    for (i = 0; i < (sizeof(g_astCnasHsdGetScanChanListTbl) / sizeof(CNAS_HSD_GET_SCAN_CHANNEL_LIST_TBL_STRU)); i++)
    {
        if (enSysAcqScene     == g_astCnasHsdGetScanChanListTbl[i].enSysAcqScene)
        {
            funSysGetScanList = g_astCnasHsdGetScanChanListTbl[i].pfunGetScanChanList;
            break;
        }
    }

    /* 查找成功时调用初始化函数进行构造 */
    if (VOS_NULL_PTR != funSysGetScanList)
    {
        ulResult     = funSysGetScanList(pstHrpdSysRecList, pstHrpdScanFreqList);
    }

    return ulResult;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_BuildScanChanList_SwitchOn
 功能描述  : 构造捕获列表
 输入参数  : enModeType  - 当前的搜网场景
             pstScanList - 扫描频点列表地址
             pstSysList  - Hrpd系统信息

 输出参数  : pstScanList - 扫描频点列表

 返 回 值  : VOS_FALSE/VOS_TRUE - 获取扫描频点列表结果
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月18日
   作    者   : C00299064
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_CreateScanFreqList(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstScanList,
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstSysList
)
{
    VOS_UINT16                          usTotalFreqNum;

    usTotalFreqNum = CNAS_HSD_CalcFreqNumForScanList(enSysAcqScene, pstSysList);

    if (0 == usTotalFreqNum)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_CreateScanFreqList: calc total freq number fail!");
        return VOS_FALSE;
    }

    if (VOS_FALSE == CNAS_HSD_MallocMemForScanList(pstScanList, usTotalFreqNum))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_CreateScanFreqList: malloc memory fail!");
        return VOS_FALSE;
    }

    /* 通过HRPD LIST 生成SCAN LIST */
    return CNAS_HSD_GetScanChanelList(enSysAcqScene, pstSysList, pstScanList);
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_MallocMemForScanList
 功能描述  : 构建扫描频点列表时,估算频点个数用于申请内存
 输入参数  : enSysAcqScene - 捕获场景
             pstSysList    - Hrpd系统信息

 输出参数  : 无
 返 回 值  : VOS_UINT16 获取到频点数量
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月12日
   作    者   : C00299064
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 CNAS_HSD_CalcFreqNumForScanList(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene,
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstSysList
)
{
    VOS_UINT16                          usTotalFreqNum;

    usTotalFreqNum                      = 0;

    if (CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION == enSysAcqScene)
    {
        /* 获取REDIRECTION的频点数量:重定向只需把网侧发起的评点加入搜网列表中即可 */
        usTotalFreqNum = CNAS_HSD_GetRedirectionFreqNum();
        return usTotalFreqNum;
    }

    /* 高优先级搜网，只需计算高优先级的频点个数 */
    if (CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY == enSysAcqScene)
    {
        usTotalFreqNum = CNAS_HSD_GetHighPriorityFreqNum();
        return usTotalFreqNum;
    }

    if (CNAS_HSD_SYS_ACQ_SCENE_OOC_MRU0 == enSysAcqScene)
    {
        return CNAS_HSD_MRU0_NUM_1_IN_SCAN_LIST;
    }

    if ((CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST     == enSysAcqScene)
      ||(CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER      == enSysAcqScene))
    {
        usTotalFreqNum                  += CNAS_HSD_MRU0_NUM_4_IN_SCAN_LIST;
    }

    /* MRU 里面频点个数 */
    usTotalFreqNum                      += CNAS_HSD_GetMruListNum();

    /* Hrpd LIST里面频点个数 */
    usTotalFreqNum                      += CNAS_HSD_CalcMatchHrpdSystemFreqNum(pstSysList);

    return usTotalFreqNum;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_MallocMemForScanList
 功能描述  : 构建扫描频点列表时，申请内存
 输入参数  : usTotalFreqNum - 估算出的扫描频点总数
             pstScanList    - 申请内存地址

 输出参数  : pstScanList    - 存放扫描频点地址

 返 回 值  : VOS_TRUE - 申请内存成功
             VOS_FALSE - 申请内存失败
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月12日
   作    者   : C00299064
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_MallocMemForScanList(
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstScanList,
    VOS_UINT16                          usTotalFreqNum
)
{
    if (VOS_NULL_PTR != pstScanList->pstScanFreqItem)
    {
        PS_MEM_FREE(UEPS_PID_HSD, pstScanList->pstScanFreqItem);

        pstScanList->usTotalFreqNum  = 0;
        pstScanList->usAvailFreqNum  = 0;
        pstScanList->usCurrIndex     = 0;
        pstScanList->ucLowPrioLevel  = CNAS_PRL_PRIO_LEVEL_1;
    }

    /* 申请空间 */
    pstScanList->pstScanFreqItem = (CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU*)PS_MEM_ALLOC(UEPS_PID_HSD,
                                    usTotalFreqNum * sizeof(CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU));

    if (VOS_NULL_PTR == pstScanList->pstScanFreqItem)
    {
        return VOS_FALSE;
    }

    /* 清零 */
    PS_MEM_SET(pstScanList->pstScanFreqItem, 0, usTotalFreqNum * sizeof(CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU));

    pstScanList->usTotalFreqNum  = usTotalFreqNum;
    pstScanList->usAvailFreqNum  = 0;
    pstScanList->usCurrIndex     = 0;
    pstScanList->ucLowPrioLevel  = CNAS_PRL_PRIO_LEVEL_1;

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : CNAS_HSD_Create1xMatchedHrpdSysRecs
 功能描述  : 创建1X相关的HRPD系统表
 输入参数  : pst1xSys    - 1X系统信息(包含SID/NID Freq)
             pstSysList  - 存放Hrpd系统信息地址

 输出参数  : pstSysList  - Hrpd系统信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月12日
   作    者   : C00299064
   修改内容   : 新生成函数
 2.日    期   : 2015年07月16日
   作    者   : x00306642
   修改内容   : evdo pilot iteration 1
*****************************************************************************/
VOS_UINT32 CNAS_HSD_Create1xMatchedHrpdSysRecs(
    CNAS_PRL_1X_SYSTEM_STRU                                *pst1xSys,
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstSysList,
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU              *pstGeoListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT16                                              usHrpdSysNum;
    VOS_UINT16                                              usRecHrpdSysIndex;
    VOS_UINT16                                              usAvilHrpdSysNum;
    VOS_UINT8                                               aucPivotDeltPrio[CNAS_PRL_MAX_MATCHING_GEO_NUM] = {0};

    usRecHrpdSysIndex   = 0;

    /* 根据当前的1X系统获取最匹配的GEO，现在由XSD提供接口 */
    if (VOS_ERR == CNAS_HSD_Get1XMostMatchedGeoList(pst1xSys, pstGeoListInfo))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_Create1xMatchedHrpdSysRecs: CNAS_HSD_Get1XMostMatchedGeoListfail!");
        return VOS_FALSE;
    }

    if (0 == pstGeoListInfo->ucGeoNum)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_Create1xMatchedHrpdSysRecs: get 1x sys geo list fail!");
        return VOS_FALSE;
    }

    /* 如果存在多个GEO,需要获得每个最匹配的1x支点的优先级 */
    if (1 < pstGeoListInfo->ucGeoNum)
    {
        if (VOS_ERR == CNAS_HSD_GetPivot1xSysPriosInGeos(pstGeoListInfo, aucPivotDeltPrio))
        {
            CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_Create1xMatchedHrpdSysRecs: CNAS_HSD_GetPivot1xSysPriosInGeos fail!");

            return VOS_FALSE;
        }
    }

    usHrpdSysNum = 0;

    /* 得到HRPD SYS REC 的数量 */
    for (i  = 0; i < pstGeoListInfo->ucGeoNum; i++)
    {
        usHrpdSysNum += CNAS_HSD_GetHybridHrpdSysRecNum(&pstGeoListInfo->astGeoInfoList[i]);
    }

    if (0 == usHrpdSysNum)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_Create1xMatchedHrpdSysRecs: get hrpd sys rec num fail!");
        return VOS_FALSE;
    }

    /* 为SYS REC 申请空间 */
    if (VOS_FALSE == CNAS_HSD_MallocMemForSysRec(usHrpdSysNum, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_Create1xMatchedHrpdSysRecs: hrpd sys rec malloc memory fail!");
        return VOS_FALSE;
    }

    usAvilHrpdSysNum = usHrpdSysNum;

    /* 获取HRPD项信息 */
    /* 添加多个GEO的时候，每个GEO的起始优先级是 1 + 距离支点的差值 */
    for (i  = 0; i < pstGeoListInfo->ucGeoNum; i++)
    {
        /* 得到HRPD项列表个数 */
        usRecHrpdSysIndex    += CNAS_HSD_GetHybridHrpdSysRecList(&pstGeoListInfo->astGeoInfoList[i],
                                                                 &pstSysList->pstHrpdSysItem[usRecHrpdSysIndex],
                                                                 usAvilHrpdSysNum,
                                                                 aucPivotDeltPrio[i]);
        usAvilHrpdSysNum  = usHrpdSysNum - usRecHrpdSysIndex;

        if ((0 == usAvilHrpdSysNum) || (usHrpdSysNum <= usRecHrpdSysIndex))
        {
            CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_Create1xMatchedHrpdSysRecs: hrpd sys num full!");
            break;
        }
    }

    if (VOS_NULL == usRecHrpdSysIndex)
    {
        pstSysList->usHrpdSysNum = VOS_NULL;
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_Create1xMatchedHrpdSysRecs: get hrpd sys rec list fail!");
        return VOS_FALSE;
    }

    pstSysList->usHrpdSysNum = usRecHrpdSysIndex;

    /* 对Hrpd系统信息排序 */
    CNAS_HSD_SortHrpdSystem(pstSysList);

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : CNAS_HSD_MallocMemForSysRec
 功能描述  : HRPD系统表申请空间
 输入参数  : usSysRecNum  - 系统个数
 输出参数  : pstSysList   - 粗放HRPD系统信息地址

 返 回 值  : VOS_UINT32   - 内测申请结果
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月12日
   作    者   : C00299064
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_MallocMemForSysRec(
    VOS_UINT16                          usSysRecNum,
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstSysList
)
{
    if (VOS_NULL_PTR != pstSysList->pstHrpdSysItem)
    {
        pstSysList->usHrpdSysNum    = 0;
        PS_MEM_FREE(UEPS_PID_HSD, pstSysList->pstHrpdSysItem);
    }

    pstSysList->pstHrpdSysItem = (CNAS_HSD_HRPD_SYS_REC_ITEM_STRU*)PS_MEM_ALLOC(
                                    UEPS_PID_HSD, usSysRecNum * (sizeof(CNAS_HSD_HRPD_SYS_REC_ITEM_STRU)));

    if (VOS_NULL_PTR == pstSysList->pstHrpdSysItem)
    {
        return VOS_FALSE;
    }

    pstSysList->usHrpdSysNum = usSysRecNum;
    PS_MEM_SET(pstSysList->pstHrpdSysItem, 0, usSysRecNum * (sizeof(CNAS_HSD_HRPD_SYS_REC_ITEM_STRU)));

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : CNAS_HSD_CreateAllHrpdSysRecs
 功能描述  : 得到系统表
 输入参数  : enCheckAssnIncl  - 是不是需要判断ASSNINCL
             enIsSortNeeded   - 是不是需要排序
             pstSysList       - 获取到的Hrpd系统信息

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月11日
   作    者   : c00299064
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_CreateAllHrpdSysRecs(
    CNAS_PRL_CHECK_ASSN_INCL_ENUM_UINT16          enCheckAssnIncl,
    CNAS_PRL_SORT_ENUM_UINT16                     enIsSortNeeded,
    CNAS_HSD_HRPD_SYS_LIST_STRU                  *pstSysList
)
{
    VOS_UINT16                          usHrpdSysNum;

    /* 得到HRPD SYS REC 的数量 */
    usHrpdSysNum = CNAS_HSD_GetNonHybridHrpdSysRecNum(enCheckAssnIncl);

    if (0 == usHrpdSysNum)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_CreateAllHrpdSysRecs: get hypd sys rec number fail!");
        return VOS_FALSE;
    }

    /* 为HRPD SYS RECS 申请空间 */
    if (VOS_FALSE == CNAS_HSD_MallocMemForSysRec(usHrpdSysNum, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_CreateAllHrpdSysRecs: hypd sys rec malloc memory fail!");
        return VOS_FALSE;
    }

    if (VOS_FALSE == CNAS_HSD_GetNonHybridHrpdSysRecList(enCheckAssnIncl, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_CreateAllHrpdSysRecs: get hypd sys rec list fail!");
        return VOS_FALSE;
    }

    /* 对HRPD SYS RECS 进行排序 */
    if (CNAS_PRL_SORT_NEEDED == enIsSortNeeded)
    {
        CNAS_HSD_SortHrpdSystem(pstSysList);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_BuildScanChanList_SystemLost
 功能描述  : 丢网场景下扫描频点列表构造
 输入参数  : enSysAcqScene    - 系统捕获场景

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月12日
   作    者   : C00299064
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_BuildScanChanList_SystemLost(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32                      enModeType;
    CNAS_HSD_1X_SYSTEM_INFO_STRU                           *pst1xSysInfo;
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstSysList;
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstScanList;

    pstScanList     = CNAS_HSD_GetScanFreqListAddr();
    pstSysList      = CNAS_HSD_GetSysRecListAddr();

    enModeType      = CNAS_HSD_GetModeType();
    pst1xSysInfo    = CNAS_HSD_Get1xSystemInfo();

    /* 生成Hrpd LIST */
    if (VOS_FALSE == CNAS_HSD_CreateHrpdSysList(enModeType, pst1xSysInfo, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_SystemLost: create hrpd list fail!");
        return;
    }

    CNAS_HSD_LogSysRecList(pstSysList, enSysAcqScene);

    /* 生成SWITCH ON SCAN LIST */
    if (VOS_FALSE == CNAS_HSD_CreateScanFreqList(enSysAcqScene, pstScanList, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_SystemLost: create freq list fail!");
        return;
    }

    CNAS_HSD_LogScanFreqList(pstScanList, enSysAcqScene);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_BuildScanChanList_Redirection
 功能描述  : 重定向场景下扫描频点列表构造
 输入参数  : enSysAcqScene    - 系统捕获场景

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月6日
   作    者   : d00212987
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_BuildScanChanList_Redirection(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32  enModeType;
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstSysList;
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstScanList;
    VOS_UINT32                          ulResult;

    pstScanList     = CNAS_HSD_GetScanFreqListAddr();
    pstSysList      = CNAS_HSD_GetSysRecListAddr();
    enModeType      = CNAS_HSD_GetModeType();

    /* 按照协议，重定向频点可以和1x不关联 */
    if (CNAS_HSD_SYS_MODE_HYBRID == enModeType)
    {
        ulResult = CNAS_HSD_CreateAllHrpdSysRecs(CNAS_PRL_CHECK_ASSN_INCL, CNAS_PRL_SORT_NEEDED, pstSysList);
    }
    else
    {
        ulResult = CNAS_HSD_CreateAllHrpdSysRecs(CNAS_PRL_NO_CHECK_ASSN_INCL, CNAS_PRL_SORT_NEEDED, pstSysList);
    }

    if (VOS_FALSE == ulResult)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_Redirection: create hrpd list fail!");
        return;
    }

    CNAS_HSD_LogSysRecList(pstSysList, enSysAcqScene);

    /* 生成Redirction CAN LIST */
    if (VOS_FALSE == CNAS_HSD_CreateScanFreqList(enSysAcqScene, pstScanList, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_Redirection: create freq list fail!");
        return;
    }

    CNAS_HSD_LogScanFreqList(pstScanList, enSysAcqScene);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_BuildScanChanList_DataCallQuick
 功能描述  : Data Call场景下快速搜索扫描频点列表构造
 输入参数  : enSysAcqScene    - 系统捕获场景

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月6日
   作    者   : d00212987
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_BuildScanChanList_DataCallQuick(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32                      enModeType;
    CNAS_HSD_1X_SYSTEM_INFO_STRU                           *pst1xSysInfo;
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstSysList;
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstScanList;

    pstScanList     = CNAS_HSD_GetScanFreqListAddr();
    pstSysList      = CNAS_HSD_GetSysRecListAddr();

    enModeType      = CNAS_HSD_GetModeType();
    pst1xSysInfo    = CNAS_HSD_Get1xSystemInfo();

    /* 生成Hrpd LIST */
    if (VOS_FALSE == CNAS_HSD_CreateHrpdSysList(enModeType, pst1xSysInfo, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_SystemLost: create hrpd list fail!");
        return;
    }

    CNAS_HSD_LogSysRecList(pstSysList, enSysAcqScene);

    /* 生成DATA CALL SCAN LIST */
    if (VOS_FALSE == CNAS_HSD_CreateScanFreqList(enSysAcqScene, pstScanList, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_SystemLost: create freq list fail!");
        return;
    }

    CNAS_HSD_LogScanFreqList(pstScanList, enSysAcqScene);

    return;

}

/*****************************************************************************
 函 数 名  : CNAS_HSD_AddMRUToScanList_SwitchOn
 功能描述  : 开机场景把MRU中的频点添加到搜网列表中
 输入参数  : 无
 输出参数  : pstHrpdScanFreqList - 搜网列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月10日
    作    者   : j00304117
    修改内容   : 新生成函数
  1.日    期   : 2015年07月15日
    作    者   : x00306642
    修改内容   : 修改hybrid模式下的策略

*****************************************************************************/
void CNAS_HSD_AddMruToScanList_SwitchOn
(
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                       *pstHrpdScanFreqList
)
{
    VOS_UINT8                           i;
    VOS_UINT16                          usPos;
    VOS_UINT16                          usTotalNum;
    CNAS_HSD_HRPD_MRU_LIST_STRU        *pstMRUList;

    /* 获取MRU列表地址 */
    pstMRUList = CNAS_HSD_GetMruList();

    /* 获取已经添加的频点个数以及总数 */
    usPos       = pstHrpdScanFreqList->usAvailFreqNum;
    usTotalNum  = pstHrpdScanFreqList->usTotalFreqNum;

    /* 添加频点到Scan List */
    if (CNAS_HSD_SYS_MODE_HYBRID == CNAS_HSD_GetModeType())
    {
        if (0 == CNAS_HSD_GetMruListNum())
        {
            return;
        }

        if (VOS_FALSE == CNAS_HSD_FreqIsSupport(&pstMRUList->astHrpdSys[0].stFreq))
        {
            return;
        }

        if (VOS_FALSE == CNAS_HSD_GetMru0RelateFlg())
        {
            return;
        }

        pstHrpdScanFreqList->pstScanFreqItem[usPos].stFreq           = pstMRUList->astHrpdSys[0].stFreq;
        pstHrpdScanFreqList->pstScanFreqItem[usPos].enFreqType       = CNAS_HSD_FREQ_TYPE_MRU;
        pstHrpdScanFreqList->pstScanFreqItem[usPos++].ucPrioLevel    = CNAS_PRL_PRIO_LEVEL_1;
        pstHrpdScanFreqList->usAvailFreqNum = usPos;

    }
    else
    {
        for (i = 0; i < CNAS_HSD_GetMruListNum(); i++)
        {
            if (VOS_FALSE == CNAS_HSD_FreqIsSupport(&pstMRUList->astHrpdSys[i].stFreq))
            {
                continue;
            }

            if (VOS_TRUE == CNAS_HSD_IsRepeatFreq(pstHrpdScanFreqList, &pstMRUList->astHrpdSys[i].stFreq))
            {
                continue;
            }

            /* 判断是否越界 */
            if (usPos >= usTotalNum)
            {
                CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_AddMruToScanList_SwitchOn: scan list to small,cannot add Freq!");
                return;
            }

            pstHrpdScanFreqList->pstScanFreqItem[usPos].stFreq           = pstMRUList->astHrpdSys[i].stFreq;
            pstHrpdScanFreqList->pstScanFreqItem[usPos].enFreqType       = CNAS_HSD_FREQ_TYPE_MRU;
            pstHrpdScanFreqList->pstScanFreqItem[usPos++].ucPrioLevel    = CNAS_PRL_PRIO_LEVEL_1;
            pstHrpdScanFreqList->usAvailFreqNum = usPos;
        }
    }
    pstHrpdScanFreqList->ucLowPrioLevel = CNAS_PRL_PRIO_LEVEL_1;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_AddMRUToScanList_SystemLost
 功能描述  : System Lost场景把MRU中的频点添加到搜网列表中
 输入参数  : 无
 输出参数  : pstHrpdScanFreqList   - 搜网列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月10日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_AddMruToScanList_SystemLost
(
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                       *pstHrpdScanFreqList
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usPos;
    VOS_UINT16                          usMruNum;
    VOS_UINT16                          usTotalNum;
    CNAS_HSD_HRPD_MRU_LIST_STRU        *pstMRUList;

    /* 获取MRU列表地址 */
    pstMRUList = CNAS_HSD_GetMruList();

    /* 获取MRU个数总数 */

    usMruNum    = CNAS_HSD_GetMruListNum();

    /* 添加到Scan List的频点总数 */
    usTotalNum = pstHrpdScanFreqList->usTotalFreqNum;

    /* 已经添加的频点个数 */
    usPos      = pstHrpdScanFreqList->usAvailFreqNum;

    /* 添加频点到Scan List */
    for (i = 0; i < usMruNum; i++)
    {
        if (VOS_FALSE == CNAS_HSD_FreqIsSupport(&pstMRUList->astHrpdSys[i].stFreq))
        {
            continue;
        }

        /* 检查是否已有重复频点 */
        if (VOS_TRUE == CNAS_HSD_IsRepeatFreq(pstHrpdScanFreqList, &pstMRUList->astHrpdSys[i].stFreq))
        {
            continue;
        }

        /* 判断是否越界 */
        if(usPos >= usTotalNum)
        {
            CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_AddMruToScanList_SwitchOn: scan list to small,cannot add Freq!");
            return ;
        }

        /* 把频点放到Scan List中 */
        pstHrpdScanFreqList->pstScanFreqItem[usPos].stFreq         = pstMRUList->astHrpdSys[i].stFreq;
        pstHrpdScanFreqList->pstScanFreqItem[usPos].enFreqType     = CNAS_HSD_FREQ_TYPE_MRU;
        pstHrpdScanFreqList->pstScanFreqItem[usPos++].ucPrioLevel  = CNAS_PRL_PRIO_LEVEL_1;

        pstHrpdScanFreqList->usAvailFreqNum                        = usPos;

        /* 根据文档 CDG 130 5.2.3.3 System Lost Scan List描述
           按照Figure 5-3规则将MRU[0] */
        /* 判断是MRU0应该插入的位置 */
        if (VOS_TRUE == CNAS_HSD_FreqIsMru0Pos(usPos))
        {
            /* 判断是否越界 */
            if (usPos >= usTotalNum)
            {
                CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_AddMruToScanList_SwitchOn: scan list to small,cannot add Freq!");
                return ;
            }

            pstHrpdScanFreqList->pstScanFreqItem[usPos].stFreq         = pstMRUList->astHrpdSys[0].stFreq;
            pstHrpdScanFreqList->pstScanFreqItem[usPos].enFreqType     = CNAS_HSD_FREQ_TYPE_MRU;
            pstHrpdScanFreqList->pstScanFreqItem[usPos++].ucPrioLevel  = CNAS_PRL_PRIO_LEVEL_1;

            pstHrpdScanFreqList->usAvailFreqNum                        = usPos;
        }
    }

    pstHrpdScanFreqList->ucLowPrioLevel             = CNAS_PRL_PRIO_LEVEL_1;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_AddMatchedGEOFreqToScanFreqList
 功能描述  : 把EVDO系统的频点添加到搜网列表里(排除Negative系统)
 输入参数  : pstHrpdItemInfo            - EVDO系统表
             pstHrpdScanFreqList        - 搜网列表
 输出参数  : 无
 返 回 值  : VOS_TRUE               - 所有频点添加成功
             VOS_FALSE              - 有频点添加到搜网列表中失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月10日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SwitchOn
(
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstHrpdItemInfo,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstHrpdScanFreqList
)
{
    VOS_UINT16                          usSystemIndex;
    VOS_UINT16                          usFreqIndex;
    VOS_UINT16                          usPos  =  0;
    VOS_UINT16                          usTotalFreqNum;
    CNAS_PRL_ACQ_RECORD_STRU           *pstTmpExtAcqRecord     = VOS_NULL_PTR;
    CNAS_PRL_GENERIC_ACQ_FOR_HRPD_STRU *pstHrpdSys             = VOS_NULL_PTR;

    /* 将要把频点放到Scan List的起始地址 */
    usPos = pstHrpdScanFreqList->usAvailFreqNum;

    /* 预期的Scan List的频点总数 */
    usTotalFreqNum = pstHrpdScanFreqList->usTotalFreqNum;

    for (usSystemIndex = 0; usSystemIndex < pstHrpdItemInfo->usHrpdSysNum; usSystemIndex++)
    {
        /* 排除Negative系统 */
        if (CNAS_PRL_PREF_NEG_SYS_PREF != pstHrpdItemInfo->pstHrpdSysItem[usSystemIndex].enPrefNegSys)
        {
            continue;
        }

        /* 获取解析PRL后得到的Acq Table的地址 */
        pstTmpExtAcqRecord  = CNAS_PRL_GetSpecifiedPrlValidAcqRecord(pstHrpdItemInfo->pstHrpdSysItem[usSystemIndex].usAcqIndex);

        if (VOS_NULL_PTR == pstTmpExtAcqRecord)
        {
            CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SwitchOn: Get AcqRec fail!");
            continue;
        }

        /* 频点类型保护 */
        if (CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD != pstTmpExtAcqRecord->enAcqType)
        {
            continue;
        }

        /* 获取HRPD系统的首地址 */
        pstHrpdSys = &(pstTmpExtAcqRecord->u.stHrpdSys);

        for (usFreqIndex = 0 ; usFreqIndex < pstHrpdSys->ucNumOfChans; usFreqIndex++)
        {
            /* 判断硬件是否支持该频点 */
            if (VOS_FALSE == CNAS_HSD_FreqIsSupport(&pstHrpdSys->astFreq[usFreqIndex]))
            {
                continue;
            }

            /* 超出内存空间，判错 */
            if (usPos >= usTotalFreqNum)
            {
                pstHrpdScanFreqList->usAvailFreqNum  = 0;
                CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SwitchOn: scan list to small,cannot add Freq!");
                return VOS_FALSE;
            }

            /* 不重复的频点加入搜网表 */
            if (VOS_FALSE == CNAS_HSD_IsRepeatFreq(pstHrpdScanFreqList,
                                                  &pstHrpdSys->astFreq[usFreqIndex]))
            {
                pstHrpdScanFreqList->pstScanFreqItem[usPos].ucPrioLevel = pstHrpdItemInfo->pstHrpdSysItem[usSystemIndex].ucPrioLevel;
                pstHrpdScanFreqList->pstScanFreqItem[usPos].enFreqType  = CNAS_HSD_FREQ_TYPE_OTHER;
                pstHrpdScanFreqList->pstScanFreqItem[usPos++].stFreq    = pstHrpdSys->astFreq[usFreqIndex];
                pstHrpdScanFreqList->usAvailFreqNum  = usPos;
            }
        }

    }

    if (0 == usPos)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SwitchOn: no Freq added to scan list!");
        return VOS_FALSE;
    }

    /* 总优先级个数 */
    pstHrpdScanFreqList->ucLowPrioLevel  = pstHrpdScanFreqList->pstScanFreqItem[usPos - 1].ucPrioLevel;

    /* 搜网序号清零 */
    pstHrpdScanFreqList->usCurrIndex     = 0;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SystemLost
 功能描述  : 把EVDO系统的频点添加到搜网列表里(排除Negative系统)
 输入参数  : pstHrpdItemInfo            - EVDO系统表
             pstHrpdScanFreqList        - 搜网列表
 输出参数  : 无
 返 回 值  : VOS_TRUE               - 所有频点添加成功
             VOS_FALSE              - 有频点添加到搜网列表中失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月10日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SystemLost
(
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstHrpdItemInfo,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstHrpdScanFreqList
)
{
    VOS_UINT16                          usSystemIndex;
    VOS_UINT16                          usFreqIndexs;
    VOS_UINT16                          usPos  =  0;
    VOS_UINT16                          usTotalFreqNum;
    CNAS_PRL_ACQ_RECORD_STRU           *pstTmpExtAcqRecord     = VOS_NULL_PTR;
    CNAS_HSD_HRPD_MRU_LIST_STRU        *pstMRUList             = VOS_NULL_PTR;
    CNAS_PRL_GENERIC_ACQ_FOR_HRPD_STRU *pstHrpdSys             = VOS_NULL_PTR;

    /*获取MRU存储地址*/
    pstMRUList = CNAS_HSD_GetMruList();

    /* 将要把频点放到Scan List的起始地址 */
    usPos = pstHrpdScanFreqList->usAvailFreqNum;

    /* 预期的Scan List的频点总数 */
    usTotalFreqNum = pstHrpdScanFreqList->usTotalFreqNum;

    for (usSystemIndex = 0; usSystemIndex < pstHrpdItemInfo->usHrpdSysNum; usSystemIndex++)
    {

        /* 排除Negative系统 */
        if (CNAS_PRL_PREF_NEG_SYS_PREF != pstHrpdItemInfo->pstHrpdSysItem[usSystemIndex].enPrefNegSys)
        {
            continue;
        }

        /* 获取解析PRL后得到的Acq Table的地址 */
        pstTmpExtAcqRecord  = CNAS_PRL_GetSpecifiedPrlValidAcqRecord(pstHrpdItemInfo->pstHrpdSysItem[usSystemIndex].usAcqIndex);

        if (VOS_NULL_PTR == pstTmpExtAcqRecord)
        {
            CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SystemLost: Get AcqRec fail!");
            continue;
        }

        /* 频点类型保护 */
        if (CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD != pstTmpExtAcqRecord->enAcqType)
        {
            continue;
        }

        /* 获取HRPD系统的首地址 */
        pstHrpdSys = &(pstTmpExtAcqRecord->u.stHrpdSys);

        for (usFreqIndexs = 0 ;usFreqIndexs <pstHrpdSys->ucNumOfChans;usFreqIndexs++)
        {
            /* 判断硬件是否支持该频点 */
            if (VOS_FALSE == CNAS_HSD_FreqIsSupport(&(pstHrpdSys->astFreq[usFreqIndexs])))
            {
                continue;
            }

            /* 同一优先级不重复的频点加入搜网表 */
            if (VOS_TRUE == CNAS_HSD_IsRepeatFreq(pstHrpdScanFreqList,
                                                  &pstHrpdSys->astFreq[usFreqIndexs]))
            {
                continue;
            }

            /* 超出内存空间，判错 */
            if (usPos >= usTotalFreqNum)
            {
                pstHrpdScanFreqList->usAvailFreqNum  = 0;
                CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SystemLost: scan list to small,cannot add Freq!");
                return VOS_FALSE;
            }

            /* 添加非MRU频点到Scan List中 */
            pstHrpdScanFreqList->pstScanFreqItem[usPos].ucPrioLevel = pstHrpdItemInfo->pstHrpdSysItem[usSystemIndex].ucPrioLevel;
            pstHrpdScanFreqList->pstScanFreqItem[usPos].enFreqType  = CNAS_HSD_FREQ_TYPE_OTHER;
            pstHrpdScanFreqList->pstScanFreqItem[usPos++].stFreq    = pstTmpExtAcqRecord->u.stHrpdSys.astFreq[usFreqIndexs];
            pstHrpdScanFreqList->usAvailFreqNum                     = usPos;

            /* 根据文档 CDG 130 5.2.3.3 System Lost Scan List描述
               按照Figure 5-3规则将MRU[0] */
            if (VOS_TRUE == CNAS_HSD_FreqIsMru0Pos(usPos))
            {
                /* 超出内存空间，判错 */
                if(usPos >= usTotalFreqNum)
                {
                    pstHrpdScanFreqList->usAvailFreqNum  = 0;
                    CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SystemLost: scan list to small,cannot add Freq!");
                    return VOS_FALSE;
                }

                pstHrpdScanFreqList->pstScanFreqItem[usPos].stFreq        = pstMRUList->astHrpdSys[0].stFreq;
                pstHrpdScanFreqList->pstScanFreqItem[usPos].enFreqType    = CNAS_HSD_FREQ_TYPE_MRU;
                pstHrpdScanFreqList->pstScanFreqItem[usPos].ucPrioLevel = pstHrpdScanFreqList->pstScanFreqItem[usPos-1].ucPrioLevel;
                usPos++;
                pstHrpdScanFreqList->usAvailFreqNum                       = usPos;
            }
        }

    }

    if (0 == usPos)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SystemLost: no Freq added to scan list");
        return VOS_FALSE;
    }

    /* 总优先级个数 */
    pstHrpdScanFreqList->ucLowPrioLevel  = pstHrpdScanFreqList->pstScanFreqItem[usPos - 1].ucPrioLevel;

    /* 搜网序号清零 */
    pstHrpdScanFreqList->usCurrIndex     = 0;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_AddMatchedGeoFreqToScanFreqList_Redirection
 功能描述  : 把EVDO系统的频点添加到搜网列表里(排除Negative系统)
 输入参数  : pstHrpdItemInfo            - EVDO系统表
             pstHrpdScanFreqList        - 搜网列表

 输出参数  : 无

 返 回 值  : VOS_TRUE               - 所有频点添加成功
             VOS_FALSE              - 有频点添加到搜网列表中失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月7日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_AddMatchedGeoFreqToScanFreqList_Redirection
(
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstHrpdItemInfo,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstHrpdScanFreqList
)
{
    CNAS_HSD_REDIRECTION_STRU          *pstRedirection;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreq;
    VOS_UINT16                          usAvailFreqNum;
    VOS_UINT16                          i;

    usAvailFreqNum  =  0;
    pstRedirection  = CNAS_HSD_GetRedirectionFreqAddr();

    /* 获取空口上报频点,添加到Scan list中 */
    for (i=0; i< CNAS_HSD_GetRedirectionFreqNum(); i++)
    {
        stFreq.enBandClass = pstRedirection->aulChannel[i].ucBandClass;
        stFreq.usChannel   = pstRedirection->aulChannel[i].usChannel;

        /* 硬件是否支持 */
        if (VOS_FALSE == CNAS_HSD_FreqIsSupport(&stFreq))
        {
            continue;
        }

        /* 频点重复检查 */
        if (VOS_TRUE == CNAS_HSD_IsRepeatFreq(pstHrpdScanFreqList, &stFreq))
        {
            continue;
        }

        pstHrpdScanFreqList->pstScanFreqItem[usAvailFreqNum].ucPrioLevel = CNAS_PRL_PRIO_LEVEL_1; /* 默认填一个level */
        pstHrpdScanFreqList->pstScanFreqItem[usAvailFreqNum].enFreqType  = CNAS_HSD_FREQ_TYPE_REDIRECTION;
        pstHrpdScanFreqList->pstScanFreqItem[usAvailFreqNum].stFreq      = stFreq;

        usAvailFreqNum++;
        pstHrpdScanFreqList->usAvailFreqNum  = usAvailFreqNum;

        /* 防止越界 */
        if (usAvailFreqNum >= pstHrpdScanFreqList->usTotalFreqNum)
        {
            break;
        }
    }

    /* 总优先级个数 */
    pstHrpdScanFreqList->ucLowPrioLevel  = CNAS_PRL_PRIO_LEVEL_1;

    /* 搜网序号清零 */
    pstHrpdScanFreqList->usCurrIndex     = 0;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetScanChanListFromHrpdList_SwitchOn
 功能描述  : 非混合模式下开机场景创建搜网列表
 输入参数  : ulTotalMatchedGeoChanNum  - 总共的频点数
 输出参数  : 无
 返 回 值  : VOS_TRUE                  - 所有频点添加成功
             VOS_FALSE                 - 有频点添加到搜网列表中失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月10日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetScanChanListFromHrpdList_SwitchOn(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysRecList,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList
)
{
    /* 添加MRU表到Scan List里 */
    CNAS_HSD_AddMruToScanList_SwitchOn(pstHrpdScanFreqList);

    /* 添加要搜索的频点到Scan List里 */
    if (VOS_FALSE == CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SwitchOn(pstHrpdSysRecList,
                                                                       pstHrpdScanFreqList))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetScanChanListFromHrpdList_SystemLost
 功能描述  : System Lost场景把频点添加到搜网列表中
 输入参数  : ulTotalMatchedGeoChanNum  - 需要添加的频点总共数
 输出参数  : 无
 返 回 值  : VOS_TRUE                  - 有频点添加成功
             VOS_FALSE                 - 有频点添加到搜网列表中失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月10日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetScanChanListFromHrpdList_SystemLost
(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysRecList,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList
)
{
    if ((VOS_NULL_PTR   == pstHrpdSysRecList)
       || (VOS_NULL_PTR == pstHrpdScanFreqList))
    {
        return VOS_FALSE;
    }

    /* 添加MRU表到Scan List里 */
    CNAS_HSD_AddMruToScanList_SystemLost(pstHrpdScanFreqList);

    /* 添加要搜索的频点到Scan List里 */
    if (VOS_FALSE == CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SystemLost(pstHrpdSysRecList,
                                                                         pstHrpdScanFreqList))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetScanChanListFromHrpdList_Redirection
 功能描述  : Redirection场景把频点添加到搜网列表中
 输入参数  : ulTotalMatchedGeoChanNum  - 需要添加的频点总共数

 输出参数  : 无

 返 回 值  : VOS_TRUE                  - 有频点添加成功
             VOS_FALSE                 - 有频点添加到搜网列表中失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetScanChanListFromHrpdList_Redirection
(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysRecList,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList
)
{
    if ((VOS_NULL_PTR   == pstHrpdSysRecList)
       || (VOS_NULL_PTR == pstHrpdScanFreqList))
    {
        return VOS_FALSE;
    }

    /* 添加要搜索的频点到Scan List里 */
    if (VOS_FALSE == CNAS_HSD_AddMatchedGeoFreqToScanFreqList_Redirection(pstHrpdSysRecList,
                                                                          pstHrpdScanFreqList))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetScanChanListFromHrpdList_Redirection
 功能描述  : Redirection场景把频点添加到搜网列表中
 输入参数  : ulTotalMatchedGeoChanNum  - 需要添加的频点总共数
 输出参数  : 无
 返 回 值  : VOS_TRUE                  - 有频点添加成功
             VOS_FALSE                 - 有频点添加到搜网列表中失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetScanChanListFromHrpdList_DataCallQuick
(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysRecList,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList
)
{
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  stTempScanList;
    CNAS_HSD_HRPD_MRU_LIST_STRU       *pstMRUList;
    VOS_UINT16                         usFreqNum;
    VOS_UINT16                         usScanFreqIndex;
    VOS_UINT16                         i;
    VOS_UINT16                         j;
    VOS_UINT8                          ucMruNum = 0;

    if ((VOS_NULL_PTR   == pstHrpdSysRecList)
       || (VOS_NULL_PTR == pstHrpdScanFreqList))
    {
        return VOS_FALSE;
    }

    pstMRUList  = CNAS_HSD_GetMruList();

    /* 获取MRU个数总数 */
    ucMruNum    = CNAS_HSD_GetMruListNum();

    usFreqNum   = pstHrpdScanFreqList->usTotalFreqNum - ucMruNum;

    PS_MEM_SET(&stTempScanList, 0, sizeof(CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU));

    /* 申请临时存储空间 */
    stTempScanList.pstScanFreqItem = (CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU*)PS_MEM_ALLOC(UEPS_PID_HSD,
                                      usFreqNum * sizeof(CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU));

    if (VOS_NULL_PTR == stTempScanList.pstScanFreqItem)
    {
        return VOS_FALSE;
    }

    stTempScanList.usTotalFreqNum  = usFreqNum;

    /* 清零 */
    PS_MEM_SET(stTempScanList.pstScanFreqItem, 0, usFreqNum * sizeof(CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU));

    /* 添加要搜索的频点到非Mru所需的临时存储空间里 */
    if (VOS_FALSE == CNAS_HSD_AddMatchedGeoFreqToScanFreqList_SwitchOn(pstHrpdSysRecList,
                                                                       &stTempScanList))
    {
        PS_MEM_FREE(UEPS_PID_HSD, stTempScanList.pstScanFreqItem);

        return VOS_FALSE;
    }

    /* 获取avail freq下发给CAS捕获时，检查avoid list中到期的频点，到期的需要删掉 */
    CNAS_HSD_CheckExpiredFreqFromAvoidList();

    usScanFreqIndex = 0;

    /* 如果Mru频点在Scan list中，加入 */
    for (i=0; i< ucMruNum; i++)
    {
        for (j=0; j<stTempScanList.usAvailFreqNum; j++)
        {
            if (VOS_TRUE != CNAS_PRL_CmpFreqValue(&(pstMRUList->astHrpdSys[i].stFreq),
                                                  &(stTempScanList.pstScanFreqItem[j].stFreq)))
            {
                continue;
            }

            /* 检查当前频点是否被禁用 */
            if (VOS_TRUE == CNAS_HSD_IsCurFreqAvoided(&(pstMRUList->astHrpdSys[i].stFreq)))
            {
                continue;
            }

            /* 如果存在则加入到表头 */
            pstHrpdScanFreqList->pstScanFreqItem[usScanFreqIndex].ucPrioLevel = stTempScanList.ucLowPrioLevel; /* 设置当前的等级为最低 */
            pstHrpdScanFreqList->pstScanFreqItem[usScanFreqIndex].enFreqType  = CNAS_HSD_FREQ_TYPE_MRU;
            pstHrpdScanFreqList->pstScanFreqItem[usScanFreqIndex++].stFreq    = pstMRUList->astHrpdSys[i].stFreq;
            pstHrpdScanFreqList->usAvailFreqNum  = usScanFreqIndex;

            pstHrpdScanFreqList->usCurrIndex     = 0;

            PS_MEM_FREE(UEPS_PID_HSD, stTempScanList.pstScanFreqItem);

            /* 找到1个即退出当前循环 */
            return VOS_TRUE;
        }
    }

    CNAS_NORMAL_LOG(UEPS_PID_HSD, "CNAS_HSD_GetScanChanListFromHrpdList_DataCallQuick: MRU not existed!");

    /* 如果Mru不能满足，再查找第一个非Avoid频点加入Scan list表 */
    for (i=0; i<stTempScanList.usAvailFreqNum; i++)
    {
        /* 检查当前频点是否被禁用 */
        if (VOS_TRUE == CNAS_HSD_IsCurFreqAvoided(&(stTempScanList.pstScanFreqItem[i].stFreq)))
        {
            continue;
        }

        pstHrpdScanFreqList->pstScanFreqItem[usScanFreqIndex].ucPrioLevel = stTempScanList.ucLowPrioLevel; /* 设置当前的等级为最低 */
        pstHrpdScanFreqList->pstScanFreqItem[usScanFreqIndex].enFreqType  = CNAS_HSD_FREQ_TYPE_MRU;        /* 为驻留设置 */
        pstHrpdScanFreqList->pstScanFreqItem[usScanFreqIndex++].stFreq    = stTempScanList.pstScanFreqItem[i].stFreq;
        pstHrpdScanFreqList->usAvailFreqNum  = usScanFreqIndex;
        pstHrpdScanFreqList->usCurrIndex     = 0;

        /* 找到1个即退出 */
        break;
    }

    PS_MEM_FREE(UEPS_PID_HSD, stTempScanList.pstScanFreqItem);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_FreqIsMru0Pos
 功能描述  : 检查当前位置是否是MRU0插入的位置
 输入参数  : usPos            - 需要写入频点的位置
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : j00304117
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_FreqIsMru0Pos
(
    VOS_UINT16                          usPos
)
{
    VOS_UINT16                          i;
    CNAS_HSD_HRPD_MRU_LIST_STRU        *pstMRUList;

    /* 获取MRU列表地址 */
    pstMRUList = CNAS_HSD_GetMruList();

    if (0 == pstMRUList->ucCurrMruNum)
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == CNAS_HSD_FreqIsSupport(&pstMRUList->astHrpdSys[0].stFreq))
    {
        return VOS_FALSE;
    }

    /* 检查当前位置是否是MRU0插入的位置 */
    for (i = 0;i < CNAS_HSD_MRU0_NUM_4_IN_SCAN_LIST; i++)
    {
        if (usPos == g_aucCnasHsdSystemLostMru0Pos[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_FreqIsSupport
 功能描述  : 频点是否被设备支持
 输入参数  : stFreq         - 需要判断的频点
 输出参数  : 无
 返 回 值  : VOS_TRUE       - 频点被设备支持
             VOS_TRUE       - 频点不被设备支持
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : j00304117
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_FreqIsSupport
(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
#ifdef DMT
    /* 目前只支持BC0和BC10，后续通过NV项配置 */
    if ((CNAS_PRL_BAND_CLASS_TYPE_0 == pstFreq->enBandClass)
     || (CNAS_PRL_BAND_CLASS_TYPE_10 == pstFreq->enBandClass))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
#else
    VOS_UINT32                          ulSupportedBand;

    ulSupportedBand = CNAS_HSD_GetUeSupportedBandClass();

    if (0 == (ulSupportedBand & ((VOS_UINT32)1 << pstFreq->enBandClass)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
#endif
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_SortHrpdSystem_NoHybrid
 功能描述  : 把获取到的DRDP系统根据优先级和index排序
 输入参数  : pstHrpdList     - 需要排序的EVDO系统的记录
 输出参数  : pstHrpdList     - 排序完成的EVDO系统的记录

 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月10日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_SortHrpdSystem_NoHybrid
(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdList
)
{
    CNAS_HSD_HRPD_SYS_REC_ITEM_STRU    *pstHrpdItemInfo;
    CNAS_HSD_HRPD_SYS_REC_ITEM_STRU     stTmpItem;
    VOS_UINT16                          usNumOfSystem;
    VOS_UINT32                          ulCmpVal;
    VOS_UINT32                          ulCmpTmp;
    VOS_UINT16                          i;
    VOS_UINT16                          j;

    pstHrpdItemInfo = pstHrpdList->pstHrpdSysItem;
    usNumOfSystem   = pstHrpdList->usHrpdSysNum;

    /* 定义了优先级值越小优先级越高, */
    /* 排序规则为先对HRPD系统优先级高的放前面，当HRPD系统的系统相同时，按照AcqTbl中的index从小到大排列 */
    /* e.g. hrpd_1优先级为1、index为2，hrpd_2优先级为3，index为1，
       组合后的优先级为
            hrpd_1:0x00010002
            hrpd_2:0x00030001
       按照规则hrpd_1比hrpd_2优先级高
    */
    for (i = 0; i < usNumOfSystem - 1 ; i++)
    {
        for (j = i + 1 ;j < usNumOfSystem ; j++)
        {
            ulCmpVal = (VOS_UINT32) (pstHrpdItemInfo[i].ucPrioLevel << 16) | (pstHrpdItemInfo[i].usAcqIndex);
            ulCmpTmp = (VOS_UINT32) (pstHrpdItemInfo[j].ucPrioLevel << 16) | (pstHrpdItemInfo[j].usAcqIndex);

            if (ulCmpVal > ulCmpTmp)
            {
                stTmpItem           = pstHrpdItemInfo[j];
                pstHrpdItemInfo[j]  = pstHrpdItemInfo[i];
                pstHrpdItemInfo[i]  = stTmpItem;
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_CalcMatchHrpdSystemFreqNum
 功能描述  : 计算匹配的EVDO系统的频点总数(排除Negative系统)
 输入参数  : pstHrpdItemInfo   - 匹配的1X的EVDO系统表
 输出参数  : 无
 返 回 值  : 匹配1X的EVDO系统的频点总数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月10日
    作    者   : j00304117
    修改内容   : 新生成函数
  1.日    期   : 2015年07月16日
    作    者   : x00306642
    修改内容   : 增加MRU0关联性判断

*****************************************************************************/
VOS_UINT16 CNAS_HSD_CalcMatchHrpdSystemFreqNum(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdItemInfo
)
{
    VOS_UINT16                          usTotalMatchedGeoChanNum    = 0;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstPrlSysRecList            = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstPrlSysRec                = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec                = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stFreqInfo;
    VOS_UINT16                          i;

    pstPrlSysRecList  = CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo.pstSysRecord;

    CNAS_HSD_SetMru0RelateFlg(VOS_FALSE);

    /* 获取频点个数 */
    for (i = 0; i < pstHrpdItemInfo->usHrpdSysNum; i++)
    {
        /* 排除negative系统 */
        if (CNAS_PRL_PREF_NEG_SYS_PREF == pstHrpdItemInfo->pstHrpdSysItem[i].enPrefNegSys)
        {
            pstPrlSysRec = &pstPrlSysRecList[pstHrpdItemInfo->pstHrpdSysItem[i].usSysIndex];

            if (VOS_FALSE == pstPrlSysRec->ucSysRecValid)
            {
                continue;
            }

            pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstPrlSysRec->usAcqIndex);

            /* 空指针进行保护 */
            if (VOS_NULL_PTR == pstPrlAcqRec)
            {
                continue;
            }

            /* 频点类型保护 */
            if (CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD != pstPrlAcqRec->enAcqType)
            {
                continue;
            }

            CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stFreqInfo);

            usTotalMatchedGeoChanNum += (VOS_UINT16)stFreqInfo.ulNum;

            CNAS_HSD_ProcMru0Relate(&stFreqInfo);
        }
    }

    return usTotalMatchedGeoChanNum;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_IsRepeatFreqInSpecPrio
 功能描述  : 检查频点在搜网表指定优先级中是否重复
 输入参数  : pstHrpdScanFreqList    - 搜网列表
             stFreq                 - 需要检查的频点
             usPrio                 - 指定的优先级
 输出参数  : 无
 返 回 值  : VOS_TRUE               - 频点在搜网列表指定优先级中已存在
             VOS_FALSE              - 频点在搜网列表指定优先级中不存在
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月10日
    作    者   : j00304117
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_IsRepeatFreqInSpecPrio
(
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    VOS_UINT8                           usPrio
)
{
    VOS_UINT16                           i;

    /* 要求比较的等级为MRU的频点，则直接认为不重复 */
    if (0 == usPrio)
    {
        return VOS_FALSE;
    }

    /* 由于优先级值是从大到小排序的，倒叙找时一旦找到优先级比指定优先级小的优先级，
       表示指定优先级已经结束，可以结束循环比较了 */
    for (i = pstHrpdScanFreqList->usAvailFreqNum; i != 0; i--)
    {
        /* 优先级为相同 */
        if ((pstHrpdScanFreqList->pstScanFreqItem[i - 1].ucPrioLevel == usPrio)
            ||(CNAS_HSD_FREQ_TYPE_MRU != pstHrpdScanFreqList->pstScanFreqItem[i - 1].enFreqType))
        {
            /* 频点相同 */
            if (VOS_TRUE == CNAS_PRL_CmpFreqValue(pstFreq, &(pstHrpdScanFreqList->pstScanFreqItem[i-1].stFreq)))
            {
                return VOS_TRUE;
            }
        }

        if (usPrio > pstHrpdScanFreqList->pstScanFreqItem[i - 1].ucPrioLevel)
        {
            break;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_IsRepeatFreq
 功能描述  : 检查频点是否重复
 输入参数  : pstHrpdScanFreqList    - 搜网列表
             stFreq                 - 需要检查的频点
 输出参数  : 无
 返 回 值  : VOS_TRUE               - 频点在搜网列表指定优先级中已存在
             VOS_FALSE              - 频点在搜网列表指定优先级中不存在
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月28日
    作    者   : g00256031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_IsRepeatFreq
(
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    VOS_UINT16                           i;

    /* 循环比较 */
    for (i = 0; i < pstHrpdScanFreqList->usAvailFreqNum; i++)
    {
        /* 频点相同 */
        if (VOS_TRUE == CNAS_PRL_CmpFreqValue(pstFreq, &(pstHrpdScanFreqList->pstScanFreqItem[i].stFreq)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetScanListSameLevelFreq
 功能描述  : 从Scan List中获取相同Level的可用频点
 输入参数  : ulFreqNum    - 最大存放频点个数
             pstFreq      - 存放频点地址

 输出参数  : pstFreq      - 获取到的频点列表

 返 回 值  : 获取到频点个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月8日
    作    者   : d00212987
    修改内容   : EVDO HSD Phase0

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetScanListSameLevelFreq(
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstCnasHsdScanList;
    VOS_UINT32                          ulHrpdFreqNum  = 0;
    VOS_UINT32                          usAvailFreqNum = 0;
    VOS_UINT16                          usCurrIndex    = 0;
    VOS_UINT32                          i;

    if ((VOS_NULL_PTR == pstFreq) || (0 == ulFreqNum))
    {
        CNAS_ERROR_LOG1(UEPS_PID_HSD, "CNAS_HSD_GetScanListSameLevelFreq: Para is Err. FreqNum is", ulFreqNum);
        return 0;
    }

    /* 获取avail freq下发给CAS捕获时，检查avoid list中到期的频点，到期的需要删掉 */
    CNAS_HSD_CheckExpiredFreqFromAvoidList();

    pstCnasHsdScanList = CNAS_HSD_GetScanFreqListAddr();

    /* 当前索引 */
    usCurrIndex    = pstCnasHsdScanList->usCurrIndex;

    /* 总的可用频点个数 */
    usAvailFreqNum = pstCnasHsdScanList->usAvailFreqNum;

    /* 这里改成不判断level，不同的level可以一起发下去 */
    /* 从后一个频点开始，判断是否能添加到SCAN LIST中 */
    for (i = usCurrIndex; i < usAvailFreqNum; i++)
    {
        /* 检查当前频点是否被禁用 */
        if (VOS_TRUE == CNAS_HSD_IsCurFreqAvoided(&(pstCnasHsdScanList->pstScanFreqItem[i].stFreq)))
        {
            if (0 == ulHrpdFreqNum)
            {
                pstCnasHsdScanList->usCurrIndex++;

                continue;
            }
            else
            {
                break;
            }
        }

        /* 拷贝到可用列表中 */
        PS_MEM_CPY(&pstFreq[ulHrpdFreqNum],
                   &(pstCnasHsdScanList->pstScanFreqItem[i].stFreq),
                   sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));

        ulHrpdFreqNum++;

        if (ulFreqNum == ulHrpdFreqNum)
        {
            break;
        }
    }

    return ulHrpdFreqNum;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetNonHybridHrpdSysRecNum
 功能描述  : 非混合情况下获取Hrpd SYS RECORD个数
 输入参数  : bIsAssnIncl    - 是否需要判断Assn Incl在SYS RECORD中的状态

 输出参数  : NA

 返 回 值  : 获取到非混合情况下 Hrpd SYS RECORD个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月8日
    作    者   : d00212987
    修改内容   : EVDO HSD Phase0
  2.日    期   : 2015年04月07日
    作    者   : z00316370
    修改内容   : 高优先搜网时增加筛选判断

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetNonHybridHrpdSysRecNum(
    CNAS_PRL_CHECK_ASSN_INCL_ENUM_UINT16    enCheckAssnIncl
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord             = VOS_NULL_PTR;
    VOS_UINT16                          usSysRecordNum           = 0;
    VOS_UINT16                          usNonHybridHrpdSysRecNum = 0;
    VOS_UINT16                          i;

    /* 获取SYS RECORD个数*/
    usSysRecordNum = CNAS_PRL_GetPrlSysRecordNum();

    for (i = 0; i < usSysRecordNum; i++)
    {
         /* 获取SYS RECORD */
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlValidSysRecord(i);

        if (VOS_NULL_PTR == pstSysRecord)
        {
            CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_GetNonHybridHrpdSysRecNum: Get SysRecord is Null,i is", i);
            continue;
        }

        if (VOS_TRUE == CNAS_PRL_IsHrpdSysRec(pstSysRecord))
        {
            /* 高优先级搜网时，需判断当前HRPD是否需要添加到EVDO列表中 */
            if (VOS_FALSE == CNAS_HSD_IsCurHrpdSysNeedInHighPriScene(i, pstSysRecord))
            {
                continue;
            }

            if (CNAS_PRL_NO_CHECK_ASSN_INCL == enCheckAssnIncl)
            {
                /* 不需关注Assn Incl状态直接统计 */
                usNonHybridHrpdSysRecNum++;
            }
            else
            {
                /* 需关注Assn Incl状态:只有Assn Incl为YES时才统计 */
                if (VOS_YES == pstSysRecord->ucAssociationIncl)
                {
                    usNonHybridHrpdSysRecNum++;
                }
            }
        }
    }

    return usNonHybridHrpdSysRecNum;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetNonHybridHrpdSysRecList
 功能描述  : 非混合情况下获取Hrpd SYS RECORD ITEM LIST
 输入参数  : bIsAssnIncl     - 是否需要判断Assn Incl在SYS RECORD中的状态
             pstSysRecIList  - 分配好存放SYS RECORD ITEM的空间

 输出参数  : pstSysRecIList   - 返回实际SYS RECORD ITEM

 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月8日
    作    者   : d00212987
    修改内容   : EVDO HSD Phase0
  2.日    期   : 2015年04月07日
    作    者   : z00316370
    修改内容   : 高优先搜网时增加筛选判断

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetNonHybridHrpdSysRecList(
    CNAS_PRL_CHECK_ASSN_INCL_ENUM_UINT16    enCheckAssnIncl,
    CNAS_HSD_HRPD_SYS_LIST_STRU            *pstSysRecList
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord             = VOS_NULL_PTR;
    VOS_UINT16                          usSysRecordNum           = 0;
    VOS_UINT16                          usNonHybridHrpdSysRecNum = 0;
    VOS_UINT8                           ucPrioLevel              = CNAS_PRL_PRIO_LEVEL_1;
    VOS_UINT16                          i;
    VOS_UINT16                          ucPriorityMore           = VOS_FALSE;

    /* 获取SYS RECORD个数*/
    usSysRecordNum = CNAS_PRL_GetPrlSysRecordNum();

    for (i = 0; i < usSysRecordNum; i++)
    {
        /* 获取SYS RECORD */
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlValidSysRecord(i);

        if (VOS_NULL_PTR == pstSysRecord)
        {
            CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_GetNonHybridHrpdSysRecList: Get SysRecord is Null,i is", i);
            continue;
        }

        if (CNAS_PRL_GEO_REGION_IND_NEW == pstSysRecord->enGeoInd)
        {
            /* 新GEO需重新计算PrioLevel */
            ucPrioLevel     = CNAS_PRL_PRIO_LEVEL_1;
            ucPriorityMore  = VOS_FALSE;
        }

        /* 前一个GEO的PriInd是more */
        if (VOS_TRUE == ucPriorityMore)
        {
            ucPrioLevel++;
            ucPriorityMore = VOS_FALSE;
        }

        if (CNAS_PRL_RELATIVE_PRI_MORE == pstSysRecord->enPriInd)
        {
            /* PrioLevel为more */
            ucPriorityMore = VOS_TRUE;
        }

        /* 高优先级搜网时，需判断当前HRPD是否需要添加到EVDO列表中 */
        if (VOS_FALSE == CNAS_HSD_IsCurHrpdSysNeedInHighPriScene(i, pstSysRecord))
        {
            continue;
        }

        if (VOS_TRUE == CNAS_PRL_IsHrpdSysRec(pstSysRecord))
        {
            if (CNAS_PRL_NO_CHECK_ASSN_INCL == enCheckAssnIncl)
            {
                /* 不需关注Assn Incl状态 */
                pstSysRecList->pstHrpdSysItem[usNonHybridHrpdSysRecNum].ucPrioLevel  = ucPrioLevel;
                pstSysRecList->pstHrpdSysItem[usNonHybridHrpdSysRecNum].usAcqIndex   = pstSysRecord->usAcqIndex;
                pstSysRecList->pstHrpdSysItem[usNonHybridHrpdSysRecNum].usSysIndex   = i;
                pstSysRecList->pstHrpdSysItem[usNonHybridHrpdSysRecNum].enPrefNegSys = pstSysRecord->enPrefNegSys;

                usNonHybridHrpdSysRecNum++;

                /* 分配内存空间存满 */
                if (usNonHybridHrpdSysRecNum >= pstSysRecList->usHrpdSysNum)
                {
                    CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetNonHybridHrpdSysRecList:Assn Incl NO No Space left");
                    break;
                }
            }
            else
            {
                /* 需关注Assn Incl为YES状态 */
                if (VOS_YES == pstSysRecord->ucAssociationIncl)
                {
                    pstSysRecList->pstHrpdSysItem[usNonHybridHrpdSysRecNum].ucPrioLevel  = ucPrioLevel;
                    pstSysRecList->pstHrpdSysItem[usNonHybridHrpdSysRecNum].usAcqIndex   = pstSysRecord->usAcqIndex;
                    pstSysRecList->pstHrpdSysItem[usNonHybridHrpdSysRecNum].usSysIndex   = i;
                    pstSysRecList->pstHrpdSysItem[usNonHybridHrpdSysRecNum].enPrefNegSys = pstSysRecord->enPrefNegSys;

                    usNonHybridHrpdSysRecNum++;

                    /* 分配内存空间存满 */
                    if (usNonHybridHrpdSysRecNum >= pstSysRecList->usHrpdSysNum)
                    {
                        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetNonHybridHrpdSysRecList:Assn Incl YES No Space left");
                        break;
                    }
                }
            }

        }
    }

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : CNAS_HSD_GetHybridHrpdSysRecParaCheck
 功能描述  : 混合情况下获取Hrpd SYS RECORD ITEM LIST
 输入参数  : pstMatchGeoInfo     - 待获取Geo列表信息
             usSysRecordNum      -
             usGeoEndIndex       -

 输出参数  : NA

 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月8日
    作    者   : d00212987
    修改内容   : EVDO HSD Phase0

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetHybridHrpdSysRecParaCheck(
    CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU    *pstGeoInfoList,
    VOS_UINT16                               usSysRecordNum,
    VOS_UINT16                               usGeoEndIndex
)
{
    VOS_UINT8                                ucIndex = 0;
    CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16    enGeoMostMatchLvl;
    if (usGeoEndIndex > usSysRecordNum)
    {
        /* 超出SYS RECORD记录直接返回 */
        CNAS_ERROR_LOG1(UEPS_PID_HSD, "CNAS_HSD_GetHybridHrpdSysRecList: ulGeoEndIndex out of range", usGeoEndIndex);
        return VOS_FALSE;
    }

    enGeoMostMatchLvl = pstGeoInfoList->enGeoMostMatchLvl;
    /* 判断1X index是否在所给范围中 */
    for (ucIndex = 0; ucIndex < pstGeoInfoList->astIndexList[enGeoMostMatchLvl].usMatchedIndexNum; ucIndex++)
    {
        if ((pstGeoInfoList->astIndexList[enGeoMostMatchLvl].ausMostMatchedIndex[ucIndex] < pstGeoInfoList->usGeoFirstSysRecIndex)
         || (pstGeoInfoList->astIndexList[enGeoMostMatchLvl].ausMostMatchedIndex[ucIndex] >= usGeoEndIndex))
        {
            CNAS_ERROR_LOG1(UEPS_PID_HSD, "CNAS_HSD_GetHybridHrpdSysRecList: 1xSysIndex out of range", usGeoEndIndex);
            return VOS_FALSE;
        }
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetHybridHrpdSysRecNum
 功能描述  : 混合情况下获取Hrpd SYS RECORD个数
 输入参数  : pstMatchGeoInfo    - 待匹配Geo列表信息

 输出参数  : NA

 返 回 值  : 获取到混合情况下Geo列表数量
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月8日
    作    者   : d00212987
    修改内容   : EVDO HSD Phase0
  2.日    期   : 2015年04月07日
    作    者   : z00316370
    修改内容   : 高优先搜网时增加筛选判断
  3.日    期   : 2015年07月16日
    作    者   : x00306642
    修改内容   : evdo pilot iteration 1
  4.日    期   : 2015年12月07日
    作    者   : c00299064
    修改内容   : GEO结构体修改
*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetHybridHrpdSysRecNum(
    CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU     *pstGeoInfoList
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord          = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pst1xSysRecord[CNAS_PRL_MAX_MATCHED_SYSTEM_NUM]      = {0};
    VOS_UINT16                          usGeoEndIndex         = 0;
    VOS_UINT16                          usSysRecordNum        = 0;
    VOS_UINT16                          usHybridHrpdSysRecNum = 0;
    VOS_UINT16                          i;
    CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16                   enGeoMostMatchLvl;
    VOS_UINT8                           ucMatched1xSysNum     = 0;

    /* 获取SYS RECORD个数*/
    usSysRecordNum = CNAS_PRL_GetPrlSysRecordNum();

    usGeoEndIndex  = pstGeoInfoList->usGeoFirstSysRecIndex + pstGeoInfoList->usGeoSysRecNum;

    /* 参数合法性检查 */
    if (VOS_TRUE != CNAS_HSD_GetHybridHrpdSysRecParaCheck(pstGeoInfoList, usSysRecordNum, usGeoEndIndex))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_GetHybridHrpdSysRecList: para error");
        return VOS_NULL;
    }

    enGeoMostMatchLvl   = pstGeoInfoList->enGeoMostMatchLvl;
    ucMatched1xSysNum   = (VOS_UINT8)(pstGeoInfoList->astIndexList[enGeoMostMatchLvl].usMatchedIndexNum);

    /* 得到最匹配的1X系统 ，可能会有多个*/
    for (i = 0; i < ucMatched1xSysNum; i++)
    {
        pst1xSysRecord[i] = CNAS_PRL_GetSpecifiedPrlValidSysRecord(pstGeoInfoList->astIndexList[enGeoMostMatchLvl].ausMostMatchedIndex[i]);

        if (VOS_NULL_PTR == pst1xSysRecord[i])
        {
            CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetHybridHrpdSysRecNum: Get SysRecord null");
            return VOS_NULL;
        }
    }

    for (i = pstGeoInfoList->usGeoFirstSysRecIndex; i < usGeoEndIndex; i++)
    {
        /* 获取SYS RECORD */
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlValidSysRecord(i);

        if (VOS_NULL_PTR == pstSysRecord)
        {
            CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_GetHybridHrpdSysRecNum: Get SysRecord null, i", i);
            continue;
        }

        if (VOS_FALSE == CNAS_PRL_IsHrpdSysRec(pstSysRecord))
        {
            continue;
        }

        /* 高优先级搜网时，需判断当前HRPD是否需要添加到EVDO列表中 */
        if (VOS_FALSE == CNAS_HSD_IsCurHrpdSysNeedInHighPriScene(i, pstSysRecord))
        {
            continue;
        }

        /* Assn Incl为YES时才统计 */
        if (VOS_YES != pstSysRecord->ucAssociationIncl)
        {
            continue;
        }

        /* 如果和多个1X里面的一个相同就认为相同 */
        if (VOS_TRUE == CNAS_HSD_IsTheHrpdSysAsso1xSys(pstSysRecord,pst1xSysRecord,ucMatched1xSysNum))
        {
            usHybridHrpdSysRecNum++;
        }
    }

    return usHybridHrpdSysRecNum;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetHybridHrpdSysRecList
 功能描述  : 混合情况下获取Hrpd SYS RECORD ITEM LIST
 输入参数  : pstMatchGeoInfo     - 待获取Geo列表信息
             pstSysRecIList      - 分配好存放SYS RECORD ITEM空间
             usAviHrpdSysNum     - 可用空间数量

 输出参数  : pstSysRecIList      - 返回实际SYS RECORD ITEM

 返 回 值  : 返回获取到的HRPD SYS RECIRD ITEM数量
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月8日
    作    者   : d00212987
    修改内容   : EVDO HSD Phase0
  2.日    期   : 2015年04月07日
    作    者   : z00316370
    修改内容   : 高优先搜网时增加筛选判断
  3.日    期   : 2015年07月16日
    作    者   : x00306642
    修改内容   : evdo pilot iteration 1

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetHybridHrpdSysRecList(
    CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU    *pstGeoList,
    CNAS_HSD_HRPD_SYS_REC_ITEM_STRU         *pstHrpdSysItem,
    VOS_UINT16                               usAviHrpdSysNum,
    VOS_UINT16                               usPivotDeltLevel
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord          = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pst1xSysRecord[CNAS_PRL_MAX_MATCHED_SYSTEM_NUM]        = {VOS_NULL_PTR};
    VOS_UINT16                          usGeoEndIndex         = 0;
    VOS_UINT16                          usSysRecordNum        = 0;
    VOS_UINT16                          usHybridHrpdSysRecNum = 0;
    VOS_UINT8                           ucPrioLevel           = (VOS_UINT8)(CNAS_PRL_PRIO_LEVEL_1 + usPivotDeltLevel);
    VOS_UINT16                          i;
    VOS_UINT16                          ucPriorityMore        = VOS_FALSE;
    VOS_UINT8                           ucMatched1xSysNum     = 0;
    VOS_UINT8                           ucIsAll1xSysNoAss     = VOS_TRUE;
    CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16                   enGeoMostMatchLvl;

    /* 获取SYS RECORD个数*/
    usSysRecordNum = CNAS_PRL_GetPrlSysRecordNum();

    usGeoEndIndex = pstGeoList->usGeoFirstSysRecIndex + pstGeoList->usGeoSysRecNum;

    if (VOS_TRUE != CNAS_HSD_GetHybridHrpdSysRecParaCheck(pstGeoList, usSysRecordNum, usGeoEndIndex))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_GetHybridHrpdSysRecList: para error");
        return VOS_NULL;
    }

    enGeoMostMatchLvl   = pstGeoList->enGeoMostMatchLvl;
    ucMatched1xSysNum   = (VOS_UINT8)pstGeoList->astIndexList[enGeoMostMatchLvl].usMatchedIndexNum;

    /* 得到最匹配的1X系统 ，可能会有多个*/
    for (i = 0; i < ucMatched1xSysNum; i++)
    {
        pst1xSysRecord[i] = CNAS_PRL_GetSpecifiedPrlValidSysRecord(pstGeoList->astIndexList[enGeoMostMatchLvl].ausMostMatchedIndex[i]);

        if (VOS_NULL_PTR == pst1xSysRecord[i])
        {
            CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetHybridHrpdSysRecNum: Get SysRecord null");
            return VOS_NULL;
        }

        /* 判断1X Assn Inc是否为YES */
        if (VOS_NO != pst1xSysRecord[i]->ucAssociationIncl)
        {
            ucIsAll1xSysNoAss = VOS_FALSE;
        }
    }

    if (VOS_TRUE == ucIsAll1xSysNoAss)
    {
        return VOS_NULL;
    }

    for (i = pstGeoList->usGeoFirstSysRecIndex; i < usGeoEndIndex; i++)
    {
        /* 获取SYS RECORD */
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlValidSysRecord(i);

        if (VOS_NULL_PTR == pstSysRecord)
        {
            CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_GetHybridHrpdSysRecList: Get SysRecord null, i", i);
            continue;
        }

        if (CNAS_PRL_GEO_REGION_IND_NEW == pstSysRecord->enGeoInd)
        {
            /* 新GEO需重新计算PrioLevel */
            ucPrioLevel     = (VOS_UINT8)(CNAS_PRL_PRIO_LEVEL_1 + usPivotDeltLevel);
            ucPriorityMore  = VOS_FALSE;
        }

        /* 前一个GEO的PriInd是more */
        if (VOS_TRUE == ucPriorityMore)
        {
            ucPrioLevel++;
            ucPriorityMore = VOS_FALSE;
        }

        if (CNAS_PRL_RELATIVE_PRI_MORE == pstSysRecord->enPriInd)
        {
            /* PrioLevel为more */
            ucPriorityMore = VOS_TRUE;
        }

        if (VOS_FALSE == CNAS_PRL_IsHrpdSysRec(pstSysRecord))
        {
            continue;
        }

        /* 高优先级搜网时，需判断当前HRPD是否需要添加到EVDO列表中 */
        if (VOS_FALSE == CNAS_HSD_IsCurHrpdSysNeedInHighPriScene(i, pstSysRecord))
        {
            continue;
        }

        if (VOS_TRUE == CNAS_HSD_IsTheHrpdSysAsso1xSys(pstSysRecord, pst1xSysRecord, ucMatched1xSysNum))
        {
            pstHrpdSysItem[usHybridHrpdSysRecNum].ucPrioLevel  = ucPrioLevel;
            pstHrpdSysItem[usHybridHrpdSysRecNum].usAcqIndex   = pstSysRecord->usAcqIndex;
            pstHrpdSysItem[usHybridHrpdSysRecNum].usSysIndex   = i;
            pstHrpdSysItem[usHybridHrpdSysRecNum].enPrefNegSys = pstSysRecord->enPrefNegSys;
            usHybridHrpdSysRecNum++;

            /* 分配内存空间存满 */
            if (usHybridHrpdSysRecNum >= usAviHrpdSysNum)
            {
                CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_GetHybridHrpdSysRecList: usHybridHrpdSysRecNum No Space left",
                                  usHybridHrpdSysRecNum);
                break;
            }
        }
    }

    return usHybridHrpdSysRecNum;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_BuildScanChanList_MRU0
 功能描述  : MRU0频点搜索scan list构造
 输入参数  :

 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月14日
   作    者   : z00316370
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_BuildScanChanList_OocMru0(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32  enModeType;
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstScanList;
    CNAS_HSD_1X_SYSTEM_INFO_STRU       *pst1xSysInfo;
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstSysList;

    pstScanList     = CNAS_HSD_GetScanFreqListAddr();
    pstSysList      = CNAS_HSD_GetSysRecListAddr();
    pst1xSysInfo    = CNAS_HSD_Get1xSystemInfo();
    enModeType      = CNAS_HSD_GetModeType();

    /* 生成EVDO LIST */
    if (VOS_FALSE == CNAS_HSD_CreateHrpdSysList(enModeType, pst1xSysInfo, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_OocMru0: CNAS_HSD_CreateHrpdSysList fail!");

        return;
    }

    CNAS_HSD_LogSysRecList(pstSysList, enSysAcqScene);

    /* 生成SWITCH ON SCAN LIST */
    if (VOS_FALSE == CNAS_HSD_CreateScanFreqList(enSysAcqScene, pstScanList, pstSysList))
    {
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_OocMru0: CNAS_HSD_GetMru0SysId fail!");

        return;
    }

    CNAS_HSD_LogScanFreqList(pstScanList, enSysAcqScene);

    return ;

}


/*****************************************************************************
 函 数 名  : CNAS_HSD_CheckHrpdFreqAssnWith1X
 功能描述  : 判断当前HRPD频点和1X系统相关联性
 输入参数  : pstHrpdSys         HRPD系统信息
 输出参数  : VOS_VOID

 返 回 值  : VOS_TRUE           - 相关联
             VOS_FALSE          - 不相关联
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月22日
    作    者   : g00256031
    修改内容   : EVDO HSD Phase0
  2.日    期   : 2015年06月04日
    作    者   : z00316370
    修改内容   : 增加入参pstHrpdSys

*****************************************************************************/
CNAS_HSD_ASSN_RLST_ENUM_UINT32 CNAS_HSD_CheckHrpdFreqAssnWith1X(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys
)
{
    VOS_UINT8                           ucPrio;
    VOS_UINT16                          usMatchIndex;
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysList;

    /* 按照开机场景构造频点列表 */
    CNAS_HSD_BuildHrpdScanList(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON);

    /* 判断是否有关联的HRPD频点 */
    if (0 == CNAS_HSD_GetScanFreqNum())
    {
        return CNAS_HSD_NO_ASSN_FREQ;
    }

    /* 当前系统不相关联 */
    if (VOS_FALSE == CNAS_HSD_IsAcqedHrpdSysMatchTheSysRecs(pstHrpdSys,
                                                           &ucPrio,
                                                           &usMatchIndex))
    {
        return CNAS_HSD_NO_ASSN_WITH_HRPD;
    }

    pstHrpdSysList = CNAS_HSD_GetSysRecListAddr();

    /* 假如当前HRPD系统为negative则当不关联处理 */
    if (CNAS_PRL_PREF_NEG_SYS_NEG == pstHrpdSysList->pstHrpdSysItem[usMatchIndex].enPrefNegSys)
    {
        return CNAS_HSD_NO_ASSN_WITH_HRPD;
    }

    return CNAS_HSD_ASSN_SUCC;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetScanChanListFromMru0_Ooc
 功能描述  : OOC场景通过MRU0创建搜网列表
 输入参数  : pstHrpdSysRecList
             pstHrpdScanFreqList
 输出参数  : 无
 返 回 值  : VOS_TRUE                  - 所有频点添加成功
             VOS_FALSE                 - 有频点添加到搜网列表中失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月21日
    作    者   : z00316370
    修改内容   : 新生成函数
  2.日    期   : 2015年02月27日
    作    者   : z00316370
    修改内容   : 修改为添加第一个硬件支持的MRU频点到搜网列表

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetScanChanListFromMru0_Ooc(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysRecList,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usMruNum;
    CNAS_HSD_HRPD_MRU_LIST_STRU        *pstMRUList;
    /* make pclint happy */
    /* pstHrpdSysRecList = pstHrpdSysRecList; */

    /* 获取MRU列表地址 */
    pstMRUList = CNAS_HSD_GetMruList();

    /* 获取MRU个数总数 */
    usMruNum    = CNAS_HSD_GetMruListNum();

    /* 添加第一个支持的频点到Scan List */
    for (i = 0; i < usMruNum; i++)
    {
        /* 判断硬件是否支持该频点 */
        if (VOS_TRUE == CNAS_HSD_FreqIsSupport(&pstMRUList->astHrpdSys[i].stFreq))
        {
            /* 在头位置插入MRU0 */
            pstHrpdScanFreqList->pstScanFreqItem[0].stFreq            = pstMRUList->astHrpdSys[i].stFreq;
            pstHrpdScanFreqList->pstScanFreqItem[0].enFreqType        = CNAS_HSD_FREQ_TYPE_MRU;
            pstHrpdScanFreqList->pstScanFreqItem[0].ucPrioLevel       = CNAS_PRL_PRIO_LEVEL_1;
            pstHrpdScanFreqList->usAvailFreqNum                       = 1;
            pstHrpdScanFreqList->ucLowPrioLevel                       = CNAS_PRL_PRIO_LEVEL_1;

            /* 初始化当前需要搜索的频点索引为0 */
            pstHrpdScanFreqList->usCurrIndex                          = 0;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_BuildScanChanList_HighPriority
 功能描述  : 高优先级搜网扫描频点列表构造
 输入参数  : enSysAcqScene    - 捕获场景

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年04月07日
   作    者   : z00316370
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_BuildScanChanList_HighPriority(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32                      enModeType;
    CNAS_HSD_1X_SYSTEM_INFO_STRU                           *pst1xSysInfo;
    CNAS_HSD_HRPD_SYS_LIST_STRU                            *pstSysList;
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstScanList;

    pstScanList     = CNAS_HSD_GetScanFreqListAddr();
    pstSysList      = CNAS_HSD_GetSysRecListAddr();
    enModeType      = CNAS_HSD_GetModeType();
    pst1xSysInfo    = CNAS_HSD_Get1xSystemInfo();

    /* 生成EVDO LIST */
    if (VOS_FALSE == CNAS_HSD_CreateHrpdSysList(enModeType, pst1xSysInfo, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_HighPriority: create hrpd list fail!");
        return;
    }

    CNAS_HSD_LogSysRecList(pstSysList, enSysAcqScene);

    /* 生成SWITCH ON SCAN LIST */
    if (VOS_FALSE == CNAS_HSD_CreateScanFreqList(enSysAcqScene, pstScanList, pstSysList))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_HighPriority: create freq list fail!");
        return;
    }

    CNAS_HSD_LogScanFreqList(pstScanList, enSysAcqScene);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetScanChanListFromHrpdList_HighPriority
 功能描述  : 把高优先级系统的频点添加到搜网列表里，排除Negative系统
 输入参数  : ulTotalMatchedGeoChanNum  - 总共的频点数
 输出参数  : 无
 返 回 值  : VOS_TRUE                  - 所有频点添加成功
             VOS_FALSE                 - 有频点添加到搜网列表中失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月07日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetScanChanListFromHrpdList_HighPriority(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysRecList,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstHrpdScanFreqList
)
{
    VOS_UINT16                          usSystemIndex;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreq;
    VOS_UINT16                          usAvailFreqNum;
    VOS_UINT8                           ucPriFreqNum;
    VOS_UINT16                          i;
    CNAS_HSD_HIGHPRIORITY_STRU         *pstHighPri          = VOS_NULL_PTR;

    usAvailFreqNum  = 0;
    pstHighPri      = CNAS_HSD_GetHighPriorityFreqAddr();
    ucPriFreqNum    = CNAS_HSD_GetHighPriorityFreqNum();

    for (usSystemIndex = 0; usSystemIndex < pstHrpdSysRecList->usHrpdSysNum; usSystemIndex++)
    {
        /* 排除Negative系统 */
        if (CNAS_PRL_PREF_NEG_SYS_PREF != pstHrpdSysRecList->pstHrpdSysItem[usSystemIndex].enPrefNegSys)
        {
            continue;
        }

        /* 每个HRPD表项可能匹配高优先级中多个频点 */
        for (i = 0; i < ucPriFreqNum; i++)
        {
            /* 按照优先级顺序添加频点 */
            if (pstHrpdSysRecList->pstHrpdSysItem[usSystemIndex].usSysIndex != pstHighPri->astFreqInfo[i].stHrpdSysItem.usSysIndex)
            {
                continue;
            }

            stFreq.enBandClass = pstHighPri->astFreqInfo[i].astFreq.enBandClass;
            stFreq.usChannel   = pstHighPri->astFreqInfo[i].astFreq.usChannel;

            /* 硬件是否支持 */
            if (VOS_FALSE == CNAS_HSD_FreqIsSupport(&stFreq))
            {
                continue;
            }

            /* 频点重复检查 */
            if (VOS_TRUE == CNAS_HSD_IsRepeatFreq(pstHrpdScanFreqList, &stFreq))
            {
                continue;
            }

            pstHrpdScanFreqList->pstScanFreqItem[usAvailFreqNum].ucPrioLevel = pstHighPri->astFreqInfo[i].stHrpdSysItem.ucPrioLevel;
            pstHrpdScanFreqList->pstScanFreqItem[usAvailFreqNum].enFreqType  = CNAS_HSD_FREQ_TYPE_OTHER;
            pstHrpdScanFreqList->pstScanFreqItem[usAvailFreqNum].stFreq      = stFreq;

            usAvailFreqNum++;
            pstHrpdScanFreqList->usAvailFreqNum  = usAvailFreqNum;

            /* 防止越界 */
            if (usAvailFreqNum >= pstHrpdScanFreqList->usTotalFreqNum)
            {
                break;
            }
        }
    }

    /* 总优先级个数,需确认是否合适 */
    pstHrpdScanFreqList->ucLowPrioLevel  = pstHrpdSysRecList->pstHrpdSysItem[usAvailFreqNum-1].ucPrioLevel;

    /* 搜网序号清零 */
    pstHrpdScanFreqList->usCurrIndex     = 0;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_IsCurHrpdSysNeedInHighPriScene
 功能描述  : 高优先级搜网时，判断当前hrpd sys的是否需要添加计算
 输入参数  : usSysIndex               - 当前HRPD的SysIndex
             pstSysRecord             - 当前sys rec表项
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE 表示是否需要添加记录
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年04月21日
   作    者   : z00316370
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_HSD_IsCurHrpdSysNeedInHighPriScene(
    VOS_UINT16                          usSysIndex,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene;
    VOS_UINT8                           ucExist;

    enSysAcqScene = CNAS_HSD_GetCurSysAcqScene_SysAcq();

    if (CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY == enSysAcqScene)
    {
        /* 存在于高优先级网络中，则返回TURE */
        ucExist     = CNAS_HSD_IsCurHrpdSysInHighPriList(usSysIndex);
    }
    else
    {
        ucExist = VOS_TRUE;
    }

    return ucExist;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_IsCurHrpdSysInHighPriList
 功能描述  : 判断当前HRPD的Sys Index在下发的高优先级列表中
 输入参数  : usSysIndex               - 当前HRPD的SysIndex
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE 表示匹配结果
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年04月07日
   作    者   : z00316370
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_HSD_IsCurHrpdSysInHighPriList(
    VOS_UINT16                          usSysIndex
)
{
    VOS_UINT16                          i;
    VOS_UINT8                           ucExist;
    VOS_UINT8                           ucPriFreqNum;
    CNAS_HSD_HIGHPRIORITY_STRU         *pstHighPri;

    ucExist         = VOS_FALSE;
    ucPriFreqNum    = CNAS_HSD_GetHighPriorityFreqNum();
    pstHighPri      = CNAS_HSD_GetHighPriorityFreqAddr();

    for (i = 0; i < ucPriFreqNum; i++)
    {
        if (usSysIndex == pstHighPri->astFreqInfo[i].stHrpdSysItem.usSysIndex)
        {
            ucExist = VOS_TRUE;
            break;
        }
    }

    return ucExist;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_IsCurSysSubnetWildCard
 功能描述  : 判断当前sys rec的subnet为通配的
 输入参数  : pstSysRecord             - 当前sys rec表项
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE 表示是否通配
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年04月21日
   作    者   : z00316370
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_HSD_IsCurSysSubnetWildCard(
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucRslt;

    ucRslt = VOS_TRUE;

    /* 长度不为0，且不全为0时，为非通配 */
    for (i = 0; i < pstSysRecord->u.stIs856Id.ucSubnetBitLen; i++)
    {
        if (0 != pstSysRecord->u.stIs856Id.aucSubnet[i])
        {
            ucRslt = VOS_FALSE;
            break;
        }
    }


    return ucRslt;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_CheckHrpdSysAssnWith1X
 功能描述  : 判断当前HRPD频点和1X系统相关联性
 输入参数  : pstHrpdSys         HRPD系统信息
 输出参数  : VOS_VOID

 返 回 值  : VOS_TRUE           - 相关联
             VOS_FALSE          - 不相关联
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月12日
    作    者   : z00316370
    修改内容   : 新增函数

*****************************************************************************/
CNAS_HSD_ASSN_RLST_ENUM_UINT32 CNAS_HSD_CheckHrpdSysAssnWith1X(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys
)
{
    VOS_UINT8                           ucPrio;
    VOS_UINT16                          usMatchIndex;
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdSysList;

    /* 按照开机场景构造频点列表 */
    CNAS_HSD_BuildHrpdScanList(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON);

    /* 判断是否有关联的HRPD系统 */
    if (0 == CNAS_HSD_GetSysRecItemNum())
    {
        return CNAS_HSD_NO_ASSN_SYS;
    }

    /* 当前系统不相关联 */
    if (VOS_FALSE == CNAS_HSD_IsAcqedHrpdSysMatchTheSysRecs(pstHrpdSys,
                                                           &ucPrio,
                                                           &usMatchIndex))
    {
        return CNAS_HSD_NO_ASSN_WITH_HRPD;
    }

    pstHrpdSysList = CNAS_HSD_GetSysRecListAddr();

    /* 假如当前HRPD系统为negative则当不关联处理 */
    if (CNAS_PRL_PREF_NEG_SYS_NEG == pstHrpdSysList->pstHrpdSysItem[usMatchIndex].enPrefNegSys)
    {
        return CNAS_HSD_NO_ASSN_WITH_HRPD;
    }

    return CNAS_HSD_ASSN_SUCC;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_GetMostMatched1xGeoList
 功能描述  : 获取最match的GEO list
 输入参数  : pstCurSysInfo ----当前系统信息

 输出参数  : pstMostMatchGeoListInfo ----最match的GEO list信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月16日
    作    者   : x00306642
    修改内容   : evdo pilot iteration 1开发
*****************************************************************************/
VOS_VOID CNAS_HSD_GetMostMatched1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMostMatchGeoListInfo
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;

    PS_MEM_SET(&stGeoListInfo, 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    /* 获取所有匹配的GEO list */
    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stGeoListInfo);

    /* 从GEO list中获取最match的GEO list */
    CNAS_PRL_GetAllMostMatched1xGeoFrom1xGeoList(pstCurSysInfo, &stGeoListInfo, pstMostMatchGeoListInfo);

    pstMostMatchGeoListInfo->usSid = pstCurSysInfo->usSid;
    pstMostMatchGeoListInfo->usNid = pstCurSysInfo->usNid;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_BuildScanChanList_SwitchOn
 功能描述  : 锁频扫描频点列表构造
 输入参数  : enSysAcqScene    - 捕获场景

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月14日
   作    者   : x00306642
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_BuildScanChanList_CFreqLock(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU                      *pstScanList;
    CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU                      *pstCnasHsdCFreqLockValue;

    pstScanList                 = CNAS_HSD_GetScanFreqListAddr();
    pstCnasHsdCFreqLockValue    = CNAS_HSD_GetFreqLockAddr();

    if (VOS_FALSE == CNAS_HSD_MallocMemForScanList(pstScanList, CNAS_HSD_CFREQLOCK_FREQ_NUM))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_BuildScanChanList_CFreqLock: malloc memory fail!");
        return ;
    }

    pstScanList->usCurrIndex                             = 0;
    pstScanList->usTotalFreqNum                          = 1;
    pstScanList->usAvailFreqNum                          = 1;
    pstScanList->ucLowPrioLevel                          = 0;

    pstScanList->pstScanFreqItem[0].stFreq.enBandClass   = pstCnasHsdCFreqLockValue->usHrpdBandClass;
    pstScanList->pstScanFreqItem[0].stFreq.usChannel     = pstCnasHsdCFreqLockValue->usHrpdFreq;
    pstScanList->pstScanFreqItem[0].ucPrioLevel          = 0;
    pstScanList->pstScanFreqItem[0].enFreqType           = CNAS_HSD_FREQ_TYPE_OTHER;

    CNAS_HSD_LogScanFreqList(pstScanList, enSysAcqScene);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_Mru0IsRelate
 功能描述  : 判断Mru0是否属于关联DO系统对应的ACQ记录
 输入参数  : enSysAcqScene    - 捕获场景

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月14日
   作    者   : x00306642
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_ProcMru0Relate(
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU    *pstFreqInfo
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stMru0Freq;
    UINT16                              i;

    if (VOS_FALSE == CNAS_HSD_GetMru0RelateFlg())
    {
        stMru0Freq = CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stMruList.astHrpdSys[0].stFreq;

        for (i = 0; i < (VOS_UINT16)pstFreqInfo->ulNum; i++)
        {
            if (VOS_TRUE == CNAS_PRL_CmpFreqValue(&pstFreqInfo->astFreqInfo[i], &stMru0Freq))
            {
                CNAS_HSD_SetMru0RelateFlg(VOS_TRUE);
                break;
            }
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_PRL_SortHrpdSystem_Hybrid
 功能描述  : 把获取到的DRDP系统根据优先级和index排序
 输入参数  : pstHrpdList     - 需要排序的EVDO系统的记录
 输出参数  : pstHrpdList     - 排序完成的EVDO系统的记录

 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_PRL_SortHrpdSystem_Hybrid
(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdList
)
{
    CNAS_HSD_HRPD_SYS_REC_ITEM_STRU    *pstHrpdItemInfo;
    CNAS_HSD_HRPD_SYS_REC_ITEM_STRU     stTmpItem;
    VOS_UINT16                          usNumOfSystem;
    VOS_UINT32                          ulCmpVal;
    VOS_UINT32                          ulCmpTmp;
    VOS_UINT16                          i;
    VOS_UINT16                          j;
    CNAS_HSD_1X_SYSTEM_INFO_STRU        *pst1xSys;

    pst1xSys =  CNAS_HSD_Get1xSystemInfo();

    pstHrpdItemInfo = pstHrpdList->pstHrpdSysItem;
    usNumOfSystem   = pstHrpdList->usHrpdSysNum;

    /* 定义了优先级值越小优先级越高, */
    /* 排序规则: 即使匹配到不同的GEO 也是按照SYSTEM 从上到下来排序 */
    /* 定义了优先级值越小优先级越高, */
    /* 如果1x存在排序规则为先对HRPD系统优先级高的放前面，当HRPD系统的系统相同时，按照sustbl中的index从小到大排列 */
    /* e.g. hrpd_1优先级为1、index为2，hrpd_2优先级为3，index为1，
       组合后的优先级为
            hrpd_1:0x00010002
            hrpd_2:0x00030001
       按照规则hrpd_1比hrpd_2优先级高
    */
    /* 如果1X不存在，按照sys 顺序排列 */

    if (CNAS_HSD_1X_SYSTEM_AVAILABLE == pst1xSys->enStatus)
    {
        for (i = 0; i < usNumOfSystem - 1 ; i++)
        {
            for (j = i + 1 ;j < usNumOfSystem ; j++)
            {
                ulCmpVal = (VOS_UINT32) (pstHrpdItemInfo[i].ucPrioLevel << 16) | (pstHrpdItemInfo[i].usSysIndex);
                ulCmpTmp = (VOS_UINT32) (pstHrpdItemInfo[j].ucPrioLevel << 16) | (pstHrpdItemInfo[j].usSysIndex);

                if (ulCmpVal > ulCmpTmp)
                {
                    stTmpItem           = pstHrpdItemInfo[j];
                    pstHrpdItemInfo[j]  = pstHrpdItemInfo[i];
                    pstHrpdItemInfo[i]  = stTmpItem;
                }
            }
        }
    }
    else
    {
        for (i = 0; i < usNumOfSystem - 1 ; i++)
        {
            for (j = i + 1 ;j < usNumOfSystem ; j++)
            {
                ulCmpVal = (VOS_UINT32)(pstHrpdItemInfo[i].usSysIndex);
                ulCmpTmp = (VOS_UINT32)(pstHrpdItemInfo[j].usSysIndex);

                if (ulCmpVal > ulCmpTmp)
                {
                    stTmpItem           = pstHrpdItemInfo[j];
                    pstHrpdItemInfo[j]  = pstHrpdItemInfo[i];
                    pstHrpdItemInfo[i]  = stTmpItem;
                }
            }
        }
    }


    return;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_SortHrpdSystem
 功能描述  : 把获取到的DRDP系统根据优先级和index排序
 输入参数  : pstHrpdList     - 需要排序的EVDO系统的记录
 输出参数  : pstHrpdList     - 排序完成的EVDO系统的记录

 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月22日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_SortHrpdSystem
(
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstHrpdList
)
{
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32  enModeType;

    enModeType      = CNAS_HSD_GetModeType();

    if (CNAS_HSD_SYS_MODE_HYBRID == enModeType)
    {
        CNAS_PRL_SortHrpdSystem_Hybrid(pstHrpdList);
    }
    else
    {
        CNAS_HSD_SortHrpdSystem_NoHybrid(pstHrpdList);
    }
    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetPivot1xSysPriosInGeos
 功能描述  : 得到每个匹配的1X在GEO里面的优先级(支点INDEX)
 输入参数  : pstHrpdList     - 需要排序的EVDO系统的记录
 输出参数  : pstHrpdList     - 排序完成的EVDO系统的记录

 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetPivot1xSysPriosInGeos
(
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU              *pstGeoList,
    VOS_UINT8                                              *pucPivotDeltPrio
)
{
    VOS_UINT32                          ulIndex             = 0;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstPrlSysRec        = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstPrlGeoFirstSysRec= VOS_NULL_PTR;
    VOS_UINT16                          usLowestPrio        = 0;
    VOS_UINT8                           aucPivotPrio[CNAS_PRL_MAX_MATCHING_GEO_NUM]   = {0};
    CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16                   enGeoMostMatchLvl;

    for (ulIndex = 0; ulIndex < pstGeoList->ucGeoNum; ulIndex++)
    {
        /* 得到匹配等级和当前GEO相等的1X的prio */
        /* 为了得到最匹配的1X系统在当前GEO的优先级(CNAS的优先级GEO切换没有清)。
            用当用当前1X的优先级 减去GEO里面第一个系统的优先级 */

        enGeoMostMatchLvl       = pstGeoList->astGeoInfoList[ulIndex].enGeoMostMatchLvl;

        pstPrlSysRec            = CNAS_PRL_GetSpecifiedPrlSysRecord(pstGeoList->astGeoInfoList[ulIndex].astIndexList[enGeoMostMatchLvl].ausMostMatchedIndex[0]);

        pstPrlGeoFirstSysRec    = CNAS_PRL_GetSpecifiedPrlSysRecord(pstGeoList->astGeoInfoList[ulIndex].usGeoFirstSysRecIndex);

        if ((VOS_NULL_PTR == pstPrlSysRec)
         || (VOS_NULL_PTR == pstPrlGeoFirstSysRec))
        {

            CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_GetPivot1xSysPriosInGeos: pstPrlSysRec NULL_PTR");

            return VOS_ERR;
        }

        aucPivotPrio[ulIndex] = (VOS_UINT8)(pstPrlSysRec->usPriLvl - pstPrlGeoFirstSysRec->usPriLvl);

        if (usLowestPrio < aucPivotPrio[ulIndex])
        {
            usLowestPrio = aucPivotPrio[ulIndex];
        }
    }

    for (ulIndex = 0; ulIndex < pstGeoList->ucGeoNum; ulIndex++)
    {
        /* GEO 拼接需要增加的 PRIO */
        pucPivotDeltPrio[ulIndex] = (VOS_UINT8)(usLowestPrio - aucPivotPrio[ulIndex]);
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_Is1xSysStillMatchHrpdSearchList
 功能描述  : 判断最新的1X是不是和原来的HRPD搜网列表匹配
 输入参数  :    CNAS_PRL_1X_SYSTEM_STRU            *pstSrcSys,
                CNAS_PRL_1X_SYSTEM_STRU            *pstDstSys
 输出参数  :

 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月23日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_Is1xSysStillMatchHrpdSearchList
(
    CNAS_PRL_1X_SYSTEM_STRU            *pstHrpdSrcSys, /*  生成HRPD列表的1x系统 */
    CNAS_PRL_1X_SYSTEM_STRU            *pstDstSys
)
{
    /* 根据两个1X得到最匹配的GEO 然后比较得到的GEO和最匹配的1x位置是否一致 */
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU                    *pstSrcMostMatchGeoListInfo     = VOS_NULL_PTR;
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU                    *pstDestMostMatchGeoListInfo    = VOS_NULL_PTR;

    /* 如否当前的1x和之前的1X完全一样，不需要重新建表 */
    if ((pstHrpdSrcSys->usSid == pstDstSys->usSid)
     && (pstHrpdSrcSys->usNid== pstDstSys->usNid)
     && (pstHrpdSrcSys->stFreq.enBandClass == pstDstSys->stFreq.enBandClass)
     && (pstHrpdSrcSys->stFreq.usChannel == pstDstSys->stFreq.usChannel))
    {
        return VOS_TRUE;
    }

    pstSrcMostMatchGeoListInfo      = (CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU*)VOS_MemAlloc(UEPS_PID_HSD, DYNAMIC_MEM_PT, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU));
    pstDestMostMatchGeoListInfo     = (CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU*)VOS_MemAlloc(UEPS_PID_HSD, DYNAMIC_MEM_PT, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU));

    if ((VOS_NULL_PTR == pstSrcMostMatchGeoListInfo)
     || (VOS_NULL_PTR == pstDestMostMatchGeoListInfo))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_Is1xSysStillMatchHrpdSearchList : alloc err");
        return VOS_FALSE;
    }
    PS_MEM_SET(pstSrcMostMatchGeoListInfo, 0, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU));
    PS_MEM_SET(pstSrcMostMatchGeoListInfo, 0, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_HSD_Get1XMostMatchedGeoList(pstHrpdSrcSys, pstSrcMostMatchGeoListInfo);

    CNAS_HSD_Get1XMostMatchedGeoList(pstDstSys, pstDestMostMatchGeoListInfo);

    if (0 == PS_MEM_CMP(pstSrcMostMatchGeoListInfo, pstDestMostMatchGeoListInfo, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU)))
    {
        VOS_MemFree(UEPS_PID_HSD, pstSrcMostMatchGeoListInfo);
        VOS_MemFree(UEPS_PID_HSD, pstDestMostMatchGeoListInfo);
        return VOS_TRUE;
    }

    VOS_MemFree(UEPS_PID_HSD, pstSrcMostMatchGeoListInfo);
    VOS_MemFree(UEPS_PID_HSD, pstDestMostMatchGeoListInfo);

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_Get1XMostMatchedGeoList
 功能描述  : 通过驻留的1X系统获最匹配的GEO列表
 输入参数  :    CNAS_PRL_1X_SYSTEM_STRU                              *pstSrcSys,
                CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU            *pstMatchedGeoList,
 输出参数  :

 返 回 值  :   VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月04日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_Get1XMostMatchedGeoList
(
    CNAS_PRL_1X_SYSTEM_STRU                                *pst1xSrcSys,
    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU              *pstMostMatchedGeoList
)
{
    /* Step1 :通过1X得到所以matche的 GEO,如果得到的GEO NUM为0 返回VOS_ERR
       Step2 : 遍历所以匹配的得到最匹配的几个
       step3 : 将结果输出
    */

    CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU              *pstMatchedGeoList = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex             = 0;
    VOS_UINT8                                               ucMostMatchGeoNum   = 0;
    CNAS_PRL_CUSTOM_MATCH_LVL_ENUM_UINT16                   enGeoMostMatchLvl   = CNAS_PRL_CUSTOM_MATCH_LVL_WILDCARD_SID_EXCEPT_CHANNEL;
    VOS_UINT8                                               aucGeoIndex[CNAS_PRL_MAX_MATCHING_GEO_NUM]       = {0};
    CNAS_PRL_MULTI_MATCHED_GEO_INFO_STRU                   *pstMulTIMatchedGeo  = VOS_NULL_PTR;


    pstMatchedGeoList = (CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_HSD, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU));

    if (VOS_NULL_PTR == pstMatchedGeoList)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_Get1XMostMatchedGeoList: pstMatchedGeoList NULL_PTR");
        return VOS_ERR;
    }

    PS_MEM_SET(pstMatchedGeoList, 0, sizeof(CNAS_PRL_MULTI_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_PRL_GetMostMultiMatched1xGeoList(pst1xSrcSys, pstMatchedGeoList);

    /* Step1 :通过1X得到所以matched的 GEO */
    if (0 == pstMatchedGeoList->ucGeoNum)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_Get1XMostMatchedGeoList: no GEO matched");
        PS_MEM_FREE(UEPS_PID_HSD, pstMatchedGeoList);
        return VOS_ERR;
    }

    /* Step2 : 遍历所以匹配的得到最匹配的几个 */
    for (ucIndex = 0; ucIndex < pstMatchedGeoList->ucGeoNum; ucIndex++)
    {
        pstMulTIMatchedGeo = &(pstMatchedGeoList->astGeoInfoList[ucIndex]);

        if (CNAS_PRL_CUSTOM_MATCH_LVL_BUTT <= pstMulTIMatchedGeo->enGeoMostMatchLvl)
        {
            CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_Get1XMostMatchedGeoList: MATCH LVL >= CNAS_PRL_CUSTOM_MATCH_LVL_BUTT");
            PS_MEM_FREE(UEPS_PID_HSD, pstMatchedGeoList);
            return VOS_ERR;
        }

        /* 如果Match lvl大于临时最大Match lvl;需要将最匹配的数组清零，个数清零 */
        if (enGeoMostMatchLvl < pstMulTIMatchedGeo->enGeoMostMatchLvl)
        {
            enGeoMostMatchLvl = pstMulTIMatchedGeo->enGeoMostMatchLvl;

            ucMostMatchGeoNum = 0;
            PS_MEM_SET(aucGeoIndex, 0, CNAS_PRL_MAX_MATCHING_GEO_NUM);

            aucGeoIndex[0] = ucIndex;
            ucMostMatchGeoNum++;

        }
        else if  (enGeoMostMatchLvl == pstMulTIMatchedGeo->enGeoMostMatchLvl)
        {
            /* 如果Match lvl等于临时最大Match lvl，而且不是不匹配;需要将index放入最匹配的数组，个数++ */
            aucGeoIndex[ucMostMatchGeoNum] = ucIndex;
            ucMostMatchGeoNum++;
        }
        else
        {
            ;
        }
    }

    /* 输出当前的MOST MATCHED GEO LIST*/
    pstMostMatchedGeoList->ucGeoNum = ucMostMatchGeoNum;
    pstMostMatchedGeoList->usSid    = pst1xSrcSys->usSid;
    pstMostMatchedGeoList->usNid    = pst1xSrcSys->usNid;

    for (ucIndex = 0; ucIndex < ucMostMatchGeoNum; ucIndex++)
    {
        pstMostMatchedGeoList->astGeoInfoList[ucIndex] = pstMatchedGeoList->astGeoInfoList[(aucGeoIndex[ucIndex])];
    }

    PS_MEM_FREE(UEPS_PID_HSD, pstMatchedGeoList);
    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : CNAS_HSD_IsTheHrpdSysAsso1xSys
 功能描述  : 通过驻留的1X系统获最匹配的GEO列表
 输入参数  :
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSrcHrpdSys,
    CNAS_PRL_EXT_SYS_RECORD_STRU                          **ppst1xSys,
    VOS_UINT8                                               uc1xSysNum

 输出参数  :

 返 回 值  :   VOS_TURE/VOS_FALSE
 调用函数  :

 修改历史      :
  1.日    期   : 2015年12月07日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_IsTheHrpdSysAsso1xSys
(
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSrcHrpdSys,
    CNAS_PRL_EXT_SYS_RECORD_STRU                          **ppst1xSys,
    VOS_UINT8                                               uc1xSysNum
)
{
    VOS_UINT8                           ucIndex = 0;

    for (ucIndex = 0; ucIndex < uc1xSysNum; ucIndex++)
    {
        if ((VOS_YES == ppst1xSys[ucIndex]->ucAssociationIncl)
         && (pstSrcHrpdSys->ucAssociationTag == ppst1xSys[ucIndex]->ucAssociationTag))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : CNAS_HSD_GetAcqedHrpdSysMatchIndex
 功能描述  : 获取和CAS上传的SYS相匹配的系统表的索引集
 输入参数  : pstHrpdSys               - CAS上报系统
 输出参数  :
 返 回 值  : VOS_TRUE/VOS_FALSE 表示匹配结果
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年12月30日
   作    者   : z00316370
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_HSD_GetAcqedHrpdSysMatchIndexList(
    CNAS_PRL_HRPD_SYSTEM_STRU                              *pstHrpdSys
)
{
    VOS_UINT16                                              i;
    VOS_UINT16                                              usSysRecordNum;
    VOS_UINT16                                              usSysIndexNum;
    CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16                   enMatchLvl;
    CNAS_PRL_SUBNET_MATCH_LVL_ENUM_UINT16                   enMostMatchLvl;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord;
    CNAS_HSD_MATCHED_HRPD_SYS_INDEX_LIST_STRU              *pstMatchedSysIndex;

    usSysIndexNum       = 0;
    enMostMatchLvl      = CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH;
    usSysRecordNum      = CNAS_PRL_GetPrlSysRecordNum();
    pstMatchedSysIndex  = CNAS_HSD_GetMatchedHrpdSysIndexListAddr();

    /* 初始化匹配的系统索引列表 */
    CNAS_HSD_InitMatchedHrpdSysIndexList();

    for (i = 0; i < usSysRecordNum; i++)
    {
         /* 获取SYS RECORD */
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlValidSysRecord(i);

        if (VOS_NULL_PTR == pstSysRecord)
        {
            CNAS_WARNING_LOG1(UEPS_PID_HSD, "CNAS_HSD_GetAcqedHrpdSysMatchIndexList: Get SysRecord is Null,i is", i);
            continue;
        }

        /* 协议CDG 143 CHAPTER 2.10.2 */
        enMatchLvl = CNAS_PRL_GetHrpdSysRecMatchLvl(pstHrpdSys, pstSysRecord);

        if (CNAS_PRL_SUBNET_MATCH_LVL_NOT_MATCH == enMatchLvl)
        {
            continue;
        }

        /* 匹配等级有提高 */
        if (enMatchLvl > enMostMatchLvl)
        {
            enMostMatchLvl  = enMatchLvl;
            usSysIndexNum   = 0;
            pstMatchedSysIndex->ausMatchedHrpdSysIndexList[usSysIndexNum] = i;
            usSysIndexNum++;
        }
        else if (enMatchLvl == enMostMatchLvl)
        {
            pstMatchedSysIndex->ausMatchedHrpdSysIndexList[usSysIndexNum] = i;
            usSysIndexNum++;
        }
        else
        {}

        pstMatchedSysIndex->usIndexNum = usSysIndexNum;

        if (usSysIndexNum >= CNAS_PRL_MAX_MATCHED_HRPD_SYSTEM_NUM)
        {
            CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetAcqedHrpdSysMatchIndexList: Mactched HRPD sys index list is full");
            return;
        }

    }

    return;

}

/*****************************************************************************
 函 数 名  : CNAS_HSD_GetAcqedHrpdSysMatchIndex
 功能描述  : 判断指定的index是否在匹配的索引集中
 输入参数  : pstHrpdSys               - CAS上报系统
 输出参数  :
 返 回 值  : VOS_TRUE/VOS_FALSE 表示是否存在
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年12月30日
   作    者   : z00316370
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_HSD_IsAcqedHrpdSysInMatchIndexList(
    VOS_UINT16                                              usSysIndex
)
{
    VOS_UINT16                                              usIndexNum;
    CNAS_HSD_MATCHED_HRPD_SYS_INDEX_LIST_STRU              *pstMatchedSysIndex;

    pstMatchedSysIndex  = CNAS_HSD_GetMatchedHrpdSysIndexListAddr();

    for (usIndexNum = 0; usIndexNum < pstMatchedSysIndex->usIndexNum; usIndexNum++)
    {
        if ((VOS_UINT32)usSysIndex == pstMatchedSysIndex->ausMatchedHrpdSysIndexList[usIndexNum])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


#endif

/*lint -restore*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



