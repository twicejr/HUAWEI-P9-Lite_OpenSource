/******************************************************************************

                  版权所有 (C), 2014-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdSysAcqStrategy.c
  版 本 号   : 初稿
  作    者   : wenlutao /00176964
  生成日期   : 2014年08月05日
  最近修改   :
  功能描述   : CNAS 层状态机系统捕获的搜网策略文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年08月05日
    作    者   : wenlutao /00176964
    修改内容   : Added for CDMA 1X IT&1上
******************************************************************************/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsCommonDef.h"
#include "stdlib.h"
#include "CnasXsdSysAcqStrategy.h"
#include "cas_1x_control_initialstate_nas_pif.h"
#include "CnasXsdMntn.h"
#include "CnasPrlApi.h"
#include "CnasCcb.h"
#include "CnasXsdComFunc.h"
#include "CnasXsdPreProcAct.h"
#include "NasMntn.h"
#include "CnasXsdFsmSysAcq.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_CNAS_XSD_SYS_ACQ_STRATEGY_C

/*lint -save -e958*/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/* 各种搜网场景对应的搜网列表初始化函数，在搜网状态机初始化时使用 */
CNAS_XSD_SCAN_CHANNEL_LIST_BUILD_TBL_STRU                   g_astCnasXsdScanChanListBuildTbl[] =
{
    {CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON,                      CNAS_XSD_BuildScanChanList_SwitchOn},
    {CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST,                    CNAS_XSD_BuildScanChanList_SystemLost},
    {CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED,                  CNAS_XSD_BuildScanChanList_CallReleased},
    {CNAS_XSD_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED,        CNAS_XSD_BuildScanChanList_AvailableTimerExpired},

    {CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL,             CNAS_XSD_BuildScanChanList_CallRedial},

    {CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED_WITH_REDIR,       CNAS_XSD_BuildScanChanList_CallReleasedWithRedir},
    {CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_FAIL,               CNAS_XSD_BuildScanChanList_RedirectionFail},
    {CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM, CNAS_XSD_BuildScanChanList_RedirectionWithInvalidGSRDM},

    {CNAS_XSD_SYS_ACQ_SCENE_RESCAN,                         CNAS_XSD_BuildScanChanList_Rescan},
    {CNAS_XSD_SYS_ACQ_SCENE_PROTO_MISMATCH,                 CNAS_XSD_BuildScanChanList_ProtoMismatch},
    {CNAS_XSD_SYS_ACQ_SCENE_ACCESS_DENINED,                 CNAS_XSD_BuildScanChanList_AccessDenied},
    {CNAS_XSD_SYS_ACQ_SCENE_ACCT_BLOCKED,                   CNAS_XSD_BuildScanChanList_AcctBlocked},
    {CNAS_XSD_SYS_ACQ_SCENE_NDSS_OFF,                       CNAS_XSD_BuildScanChanList_NdssOff},
    {CNAS_XSD_SYS_ACQ_SCENE_ERR,                            CNAS_XSD_BuildScanChanList_Error},
    {CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF,   CNAS_XSD_BuildScanChanList_RegisRejWithRedirAndRtf},
    {CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ,                      CNAS_XSD_BuildScanChanList_RegisRej},
    {CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF,      CNAS_XSD_BuildScanChanList_SysReselWithPrefPrl},
    {CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG,    CNAS_XSD_BuildScanChanList_SysReselNotInPrlOrNeg},
    {CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL,      CNAS_XSD_BuildScanChanList_MaxAccessFailureInPrl},
    {CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL,  CNAS_XSD_BuildScanChanList_MaxAccessFailureNotInPrl},
    {CNAS_XSD_SYS_ACQ_SCENE_ABNORMAL,                       CNAS_XSD_BuildScanChanList_Abnormal},

    {CNAS_XSD_SYS_ACQ_SCENE_CALL_MRU0,                      CNAS_XSD_BuildScanChanList_MRU0},

    {CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL,                 CNAS_XSD_BuildScanChanList_EMC},
    {CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST,       CNAS_XSD_BuildScanChanList_CALLBACK},
    {CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED,              CNAS_XSD_BuildScanChanList_EmcCallReleased},
    {CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0,          CNAS_XSD_BuildScanChanList_SystemLostSkipMru0},
    {CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF_EMC,   CNAS_XSD_BuildScanChanList_RegisRejWithRedirAndRtf},
    {CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF_EMC,      CNAS_XSD_BuildScanChanList_SysReselWithPrefPrl},
    {CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG_EMC,    CNAS_XSD_BuildScanChanList_SysReselNotInPrlOrNeg},
    {CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0_EMC,          CNAS_XSD_BuildScanChanList_SystemLostSkipMru0},
    {CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM_EMC, CNAS_XSD_BuildScanChanList_RedirectionWithInvalidGSRDM},
    {CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL_EMC,      CNAS_XSD_BuildScanChanList_MaxAccessFailureInPrl},
    {CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL_EMC,  CNAS_XSD_BuildScanChanList_MaxAccessFailureNotInPrl},

    {CNAS_XSD_SYS_ACQ_SCENE_POWER_ON_INIT_SEARCH,           CNAS_XSD_BuildScanChanList_PowerOnInitSearch},

    {CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASE_SYSTEM_LOST,           CNAS_XSD_BuildScanChanList_CallReleaseSystemLost},
};


/* 该变量临时控制call release场景下的列表构造, 后续会被删除 */

VOS_UINT32                              g_CtrlCallRelScanList = VOS_TRUE;

/*****************************************************************************
 函 数 名  : CNAS_XSD_RemoveSpecialFreqFromScanList
 功能描述  : 从搜网列表中删除指定频点
 输入参数  : pstSpecialFreq  ---------- 指定频点
             pstScanChanList ---------- 同步列表
 输出参数  : pstScanChanList ---------- 同步列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年12月21日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_RemoveSpecialFreqFromScanList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstSpecialFreq,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          usIndex;

    if ( (VOS_NULL_PTR == pstSpecialFreq)
      || (VOS_NULL_PTR == pstScanChanList) )
    {
        return;
    }

    for ( usIndex = 0; usIndex < pstScanChanList->usTotalNum; usIndex++ )
    {
        if ((pstSpecialFreq->enBandClass == pstScanChanList->pstScanChanInfo[usIndex].stFreqChan.enBandClass)
         && (pstSpecialFreq->usChannel   == pstScanChanList->pstScanChanInfo[usIndex].stFreqChan.usChannel))
        {
            if (usIndex != pstScanChanList->usTotalNum - 1)
            {
                NAS_MEM_MOVE_S(&(pstScanChanList->pstScanChanInfo[usIndex]),
                                (pstScanChanList->usTotalNum - usIndex) * sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU),
                               &(pstScanChanList->pstScanChanInfo[usIndex+1]),
                                (pstScanChanList->usTotalNum - usIndex - 1) * sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));
            }

            pstScanChanList->usTotalNum--;

            return;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList
 功能描述  : 系统捕获状态机启动时,频点扫描表初始化
 输入参数  : enSysAcqScene ------------   捕获场景
             usPreSrchChanNum ------------当前需要优先搜索的频点个数,构造时需要增加到扫描频点列表中
             pstPreSrchChanArray ----------当前需要优先搜索的频点数组头指针,构造时需要增加到扫描频点列表中
 输出参数  : pstScanChanListInfo -----------构造好的扫描频点列表指针
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年08月05日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32 enSysAcqScene,
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    VOS_UINT32                          i;
    pCNasXsdScanChanListBuildFunc       pfunScanChanListBuild;
    CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU  *pstCnasXsdCFreqLockValue;

    pstCnasXsdCFreqLockValue = CNAS_XSD_GetFreqLockAddr();

    pfunScanChanListBuild = VOS_NULL_PTR;

    if (VOS_TRUE == CNAS_XSD_GetTestConfig()->ucIsMod1xAvailTimerLen)
    {        
        CNAS_XSD_GetCdma1XCustomPrefChannels()->ucEnableFlg = VOS_FALSE;
    }

    /* 若启动锁频 */
    if (VOS_TRUE == pstCnasXsdCFreqLockValue->ucFreqLockMode)
    {
        CNAS_XSD_AllocMemoryForScanChanList_FreqLock(pstScanChanList);
        if (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo)
        {
            CNAS_XSD_BuildScanChanList_FreqLock(pstScanChanList);
            CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_CFREQLOCK_SCAN_CHAN_LIST_IND, pstScanChanList);
        }

        return;
    }

    /* 根据场景在g_astCnasXsdScanChanListBuildTbl查找搜网列表构造函数 */
    for (i = 0; i < (sizeof(g_astCnasXsdScanChanListBuildTbl)/sizeof(CNAS_XSD_SCAN_CHANNEL_LIST_BUILD_TBL_STRU)); i++)
    {
        if (enSysAcqScene == g_astCnasXsdScanChanListBuildTbl[i].enSysAcqScene)
        {
            pfunScanChanListBuild = g_astCnasXsdScanChanListBuildTbl[i].pfunScanChanListBuild;
            break;
        }
    }

    /* 由于scan list比较大,需要先分配内存,待关机时释放内存 */
    /* 增加搜网场景*/
    CNAS_XSD_AllocMemoryForScanChanList(pstScanChanList, enSysAcqScene);


    /* 查找成功时调用初始化函数进行构造 */
    if ((VOS_NULL_PTR != pfunScanChanListBuild)
     && (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo))
    {
        pfunScanChanListBuild(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

        CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_SCAN_CHAN_LIST_IND, pstScanChanList);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildGeoSysRecordSrchList
 功能描述  : 频点同步完成,需要捕获系统时,捕获列表的构造
 输入参数  : usMatchedSysRecNum--------------同步成功的系统ID:呼叫释放等场景下直接使用同步成功的SID+NID构造列表
             pusMatchedSysRecNum-----------系统GEO列表中匹配的系统表记录总个数,如果无匹配的,个数填写为0
             pstMatchedSysRecord ----------系统GEO列表中匹配的系统表记录指针,在GEO查找中已经分配了内存
 输出参数  : pstSysAcqList ---------------构造好的捕获系统列表信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年08月05日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2015年7月9日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildGeoSysRecordSrchList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSyncSuccSysId,
    VOS_UINT16                                              usMatchedSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstMatchedSysRecord,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList,
    VOS_UINT16                                              usMostMatchedIndex
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          j;
    VOS_UINT16                          usAcqIndex;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stAcqRecFreqInfo;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec = VOS_NULL_PTR;
    VOS_UINT16                          usLevel;
    VOS_UINT16                          usTotalNum;

    /* 内存分配时，仅分配GEO中高优先级的系统频点+当前同步到的系统频点 */
    CNAS_XSD_AllocMemoryForGeoSysRecordSrchList(usMostMatchedIndex,
                                                pstMatchedSysRecord,
                                                pstGeoSysRecSrchList);

    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        return;
    }

    /* 获取GEO中最match的level */
    usLevel = (pstMatchedSysRecord + usMostMatchedIndex)->usPriLvl;

    for (i = 0; i < usMatchedSysRecNum; i++)
    {
        if (VOS_FALSE == pstMatchedSysRecord[i].ucSysRecValid)
        {
            continue;
        }

        usAcqIndex = pstMatchedSysRecord[i].usAcqIndex;

        /* 获取PRL中获取表指针 */
        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(usAcqIndex);

        /* 空指针进行保护 */
        if (VOS_NULL_PTR == pstPrlAcqRec)
        {
            continue;
        }

        /*******************************************************************************************
         * 只取高优先级的系统以及当前同步到的系统
         * 注: 必须先提前判断level，否则如果当前系统中在GEO中level是最高级别的，但在它之前仍然有同级
         *     别的系统，会被加进去
         ******************************************************************************************/
        if (usLevel == pstMatchedSysRecord[i].usPriLvl)
        {
            usTotalNum = pstGeoSysRecSrchList->usTotalNum;

            /* 这里默认更新当前系统为优先系统，同步状态为未同步后，后续如果当前系统为negative系统，则被刷新为同步不存在，
               否则会被刷新为同步存在 */
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].enPrefNegSys                = CNAS_PRL_PREF_NEG_SYS_PREF;
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].enSysStatus                 = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].stAcqSys.stFreq.enBandClass = pstSyncSuccSysId->stFreq.enBandClass;
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].stAcqSys.stFreq.usChannel   = pstSyncSuccSysId->stFreq.usChannel;
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].stAcqSys.usNid              = pstSyncSuccSysId->usNid;
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].stAcqSys.usSid              = pstSyncSuccSysId->usSid;
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].usLevel                     = usLevel;

            pstGeoSysRecSrchList->usTotalNum++;

            return;
        }

        /*******************************************************************************************
         * 只统计IS_95的系统以及MCC/MNC且子类型为SID或SID/NID的系统
         ******************************************************************************************/
        /*  */
        if ((CNAS_PRL_SYS_RECORD_TYPE_1X_IS95           == pstMatchedSysRecord[i].enRecordType)
        || ((CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED     == pstMatchedSysRecord[i].enRecordType)
         && ((CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID     == pstMatchedSysRecord[i].u.stMccMncId.enMccMncSubType)
          || (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID_NID == pstMatchedSysRecord[i].u.stMccMncId.enMccMncSubType))))
        {
            NAS_MEM_SET_S(&stAcqRecFreqInfo, sizeof(stAcqRecFreqInfo), 0x0, sizeof(CNAS_PRL_ACQ_REC_FREQ_INFO_STRU));
            CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stAcqRecFreqInfo);

            for (j = 0; j < CNAS_MIN(stAcqRecFreqInfo.ulNum, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); j++)
            {
                CNAS_XSD_AddSysRecordIntoSysList(&(stAcqRecFreqInfo.astFreqInfo[j]), &(pstMatchedSysRecord[i]), pstGeoSysRecSrchList);
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_SwitchOn
 功能描述  : 开机扫描频点列表构造
 输入参数  : usPreSrchChanNum ------------ 当前需要优先搜索的频点个数,构造时需要增加到扫描频点列表中
             pstPreSrchChanArray---------- 当前需要优先搜索的频点数组头指针,构造时需要增加到扫描频点列表中
 输出参数  : pstScanChanList---------------构造好的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月05日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_SwitchOn(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    /* 列表组成: (MRU + 电信常用频点 + PRL Acquire table)
         Reference to
         CDG130:
         5.2.3.1  Normal Scan List
         such as the deletion of:
           Duplicate entries
           Channels caused by suitable identification in the preferences (see section 5.1.1)
           Channels that can be specifically identified as negative systems

         CDG143:
         4.1 Power-up
         4.1.1 This requirement does not exclude multiple acquisition attempts on channels, like MRU[0], before completing a pass through the MRU and PRL
    */
    /* 先将MRU中的频点信息增加到pstScanChanListInfo中 */
    CNAS_XSD_AddMruListInScanChanList(pstScanChanList);

    /* 将电信常用1X 频点加入到pstScanChanListInfo中 */
    CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

    /* 然后将PRL中获取表的频点信息增加到pstScanChanListInfo中 */
    CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);

    /* 初始化当前需要搜索的频点索引为0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildChanScanList_SystemLost
 功能描述  : 丢网场景下扫描频点列表构造
 输入参数  : usPreSrchChanNum ------------ 当前需要优先搜索的频点个数,构造时需要增加到扫描频点列表中
             pstPreSrchChanArray---------- 当前需要优先搜索的频点数组头指针,构造时需要增加到扫描频点列表中
 输出参数  : pstScanChanList---------------构造好的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月05日
   作    者   : w00176964
   修改内容   : 新生成函数
  修改历史     :
 2.日    期   : 2015年1月5日
   作    者   : c00299063
   修改内容   : 封装原函数，增加重复搜索策略
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_SystemLost(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{

    CNAS_XSD_OOC_SCAN_STRATEGY_ENUM_UINT8                   enOocScanStrategy;
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                        *pstOocScheduleInfo = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstOrigFreq        = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru0SysId;

    pstOocScheduleInfo = CNAS_XSD_GetOocScheduleInfo();

    /*不增加重复频点的条件构建频点列表 */
    CNAS_XSD_BuildNormalSystemLostScanChanlist(pstScanChanList);

    enOocScanStrategy = pstOocScheduleInfo->stConfigInfo.enOocScanStrategy;

    NAS_MEM_SET_S(&stMru0SysId, sizeof(stMru0SysId), 0, sizeof(stMru0SysId));

    if (VOS_FALSE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        return;
    }

    pstOrigFreq       = &(stMru0SysId.stFreq);

    switch (enOocScanStrategy)
    {
        case CNAS_XSD_OOC_SCAN_REACQ_0_1_2_3_4S:
            CNAS_XSD_AddOrigChanToScanChanlist_REACQ_0_1_2_3_4s(pstScanChanList, pstOrigFreq);
            break;

        case CNAS_XSD_OOC_SCAN_PING_5:
            CNAS_XSD_AddOrigChanToScanChanlist_PING_5(pstScanChanList, pstOrigFreq);
            break;

        case CNAS_XSD_OOC_SCAN_2_7:
            CNAS_XSD_AddOrigChanToScanChanlist_2_7(pstScanChanList, pstOrigFreq);
            break;

        case CNAS_XSD_OOC_SCAN_NORMAL:

            break;
        default:

            break;

    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_AvailableTimerExpired
 功能描述  : 选网定时器超时场景下扫描频点列表初始化
 输入参数  : usPreSrchChanNum ------------ 当前需要优先搜索的频点个数,构造时需要增加到扫描频点列表中
             pstPreSrchChanArray---------- 当前需要优先搜索的频点数组头指针,构造时需要增加到扫描频点列表中
 输出参数  : pstScanChanList---------------构造好的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月05日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年11月28日
   作    者   : c00299063
   修改内容   : 记录当前搜网场景
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_AvailableTimerExpired(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    /* 目前来看,该场景与system lost场景构造列表逻辑一致 */
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_CallReleased
 功能描述  : 呼叫释放场景下扫描频点列表构造
 输入参数  : usPreSrchChanNum ------------ 当前需要优先搜索的频点个数,构造时需要增加到扫描频点列表中
             pstPreSrchChanArray---------- 当前需要优先搜索的频点数组头指针,构造时需要增加到扫描频点列表中
 输出参数  : pstScanChanList---------------构造好的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月05日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2015年7月9日
   作    者   : y00245242
   修改内容   : iteration 17开发
 3.日    期   : 2015年12月21日
   作    者   : w00242748
   修改内容   : DTS2015121511023:call release申请的资源优先级需提高

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_CallReleased(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    CNAS_XSD_CALL_REL_ANY_CAMP_ON_FREQ_STRU                *pstCallRelAnyCampOnFreq = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stTmpScanChanInfo;
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru0SysId;
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru1SysId;
    VOS_UINT16                                              i;

    /***********************************************************************************************
     * cdg143 4.6:
     * If MS fails to acquire the last channel being used in Traffic state, it shall try to acquire
     * the channel that is listed in MRU[0].
     * If MS fails to acquire MRU[0], it shall perform system lost algorithm based on MRU[0].
     * 根据cdg143的协议，call release频点构造按照"呼叫释放时的频点+MRU0", 以上两个频点捕获失败，则
     * 按照system lost场景基于MRU[0]构造，因此这里scan list列表我们一次构造完成, 列表按如下构造:
     * 历史频点 + MRU[0] + GEO LIST(ORDER BY MRU LIST) + MRU LIST + 电信常用频点 + PRL ACQ RECORD LIST
     **********************************************************************************************/

    /***********************************************************************************************
     * 1. 添加呼叫释放时的频点
     **********************************************************************************************/
    /* 先将pstPreSrchChanArray中的频点信息增加到pstScanChanListInfo中 */
    for (i = 0; i < usPreSrchChanNum; i++)
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[i];
        stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    /***********************************************************************************************
     * 2. 添加MRU[0]频点
     **********************************************************************************************/
    /* 再将MRU[0]中的频点信息增加到pstScanChanListInfo中 */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan   = stMru0SysId.stFreq;
        stTmpScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* 添加到频点扫描列表 */
        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    if (VOS_TRUE == g_CtrlCallRelScanList)
    {
        /***********************************************************************************************
         * 3. 更新call release首次需要同步的频点
         **********************************************************************************************/
        pstCallRelAnyCampOnFreq = CNAS_XSD_GetCallRelAnyCampOnFreqListAddr();
        pstCallRelAnyCampOnFreq->usChanNum = pstScanChanList->usTotalNum;
        for (i = 0; i < CNAS_MIN(pstCallRelAnyCampOnFreq->usChanNum, CNAS_XSD_CALL_REL_SYNC_MAX_FREQ_NUM); i++)
        {
            pstCallRelAnyCampOnFreq->astFreq[i].enBandClass = pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass;
            pstCallRelAnyCampOnFreq->astFreq[i].usChannel   = pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel;
        }
    }

    if (VOS_TRUE == CNAS_XSD_GetMru1SysId(&stMru1SysId))
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan   = stMru1SysId.stFreq;
        stTmpScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* 添加到频点扫描列表 */
        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    /* 初始化当前需要搜索的频点索引为0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_EmcCallReleased
 功能描述  : 紧急呼叫释放场景下扫描频点列表构造
 输入参数  : usPreSrchChanNum ------------ 当前需要优先搜索的频点个数,构造时需要增加到扫描频点列表中
             pstPreSrchChanArray---------- 当前需要优先搜索的频点数组头指针,构造时需要增加到扫描频点列表中
 输出参数  : pstScanChanList---------------构造好的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年7月9日
   作    者   : h00313353
   修改内容   : iteration 17开发

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_EmcCallReleased(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stTmpScanChanInfo;
    VOS_UINT16                                              i;

    /***********************************************************************************************
     * 1. 添加呼叫释放时的频点
     **********************************************************************************************/
    /* 先将pstPreSrchChanArray中的频点信息增加到pstScanChanListInfo中 */
    for (i = 0; i < usPreSrchChanNum; i++)
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[i];
        stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    /* 初始化当前需要搜索的频点索引为0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_SystemLostSkipMru0
 功能描述  : 同丢网场景构造列表，只是将MRU0从scanList中清除
 输入参数  : usPreSrchChanNum ------------ 当前需要优先搜索的频点个数,构造时需要增加到扫描频点列表中
             pstPreSrchChanArray---------- 当前需要优先搜索的频点数组头指针,构造时需要增加到扫描频点列表中
 输出参数  : pstScanChanList---------------构造好的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年08月26日
   作    者   : m00312079
   修改内容   : DTS2015070400587:同丢网场景构造列表，只是将MRU0从scanList中清除

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_SystemLostSkipMru0(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    VOS_UINT32                              ulLoop;

    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum,
                                          pstPreSrchChanArray,
                                          pstScanChanList);

    if (pstScanChanList->usTotalNum > 1)
    {
        /* 将MRU0删除 */
        for (ulLoop = 0; ulLoop < (VOS_UINT32)pstScanChanList->usTotalNum - 1; ulLoop++)
        {
            NAS_MEM_MOVE_S(&pstScanChanList->pstScanChanInfo[ulLoop],
                           sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU),
                           &pstScanChanList->pstScanChanInfo[ulLoop + 1],
                           sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));
        }

        NAS_MEM_SET_S(&pstScanChanList->pstScanChanInfo[ulLoop],
                      sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU),
                      0x00,
                      sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        pstScanChanList->usTotalNum--;
    }

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_PowerOnInitSearch
 功能描述  : 上电开机，第一次无卡开机，发起X模初搜，只为了获取X模位置信息，只构造电信常用频点
 输入参数  : usPreSrchChanNum ------------ 当前需要优先搜索的频点个数,构造时需要增加到扫描频点列表中
             pstPreSrchChanArray---------- 当前需要优先搜索的频点数组头指针,构造时需要增加到扫描频点列表中
 输出参数  : pstScanChanList---------------构造好的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年12月10日
   作    者   : l00324781
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_PowerOnInitSearch(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    /* 将电信常用1X 频点加入到pstScanChanListInfo中 */
    CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

    /* 初始化当前需要搜索的频点索引为0 */
    pstScanChanList->usCurScanIndex    = 0;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_OrderScanListByMruList
 功能描述  : scan list is ordered according MRU list,
 输入参数  : pstScanChanList -- scan list
             pstMruList      -- MRU list
 输出参数  : none
 返 回 值  : none
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2/12/2014
   作    者   : y00245242
   修改内容   : create
*****************************************************************************/
VOS_VOID CNAS_XSD_OrderScanListByMruList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList,
    CNAS_XSD_MRU_LIST_STRU             *pstMruList
)
{
    VOS_UINT8                           i;
    VOS_UINT16                          j;

    for (i = CNAS_MIN(pstMruList->ucSysNum, CNAS_XSD_MAX_MRU_SYS_NUM); i > 0; i--)
    {
        for (j = 0; j < pstScanChanList->usTotalNum; j++)
        {
            /* 找到频点则将对应的频点删除,将找到频点插入到数组头部 */
            if ((pstMruList->astSystem[i-1].stFreq.enBandClass == pstScanChanList->pstScanChanInfo[j].stFreqChan.enBandClass)
             && (pstMruList->astSystem[i-1].stFreq.usChannel   == pstScanChanList->pstScanChanInfo[j].stFreqChan.usChannel))
            {
                if (0 != j)
                {
                    NAS_MEM_MOVE_S(&(pstScanChanList->pstScanChanInfo[1]),
                                   sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * (pstScanChanList->usTotalNum - 1),
                                   &(pstScanChanList->pstScanChanInfo[0]),
                                   sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * j);
                }

                pstScanChanList->pstScanChanInfo[0].stFreqChan = pstMruList->astSystem[i-1].stFreq;

                break;
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetLastIndexOfSameOrMorePreferredThanSpecifiedSystemInGeo
 功能描述  : get the last index of system that is same or more preferred than the
             specified system in GEO.

 输入参数  : pstGeoListInfo -- orignal system GEO information

 输出参数  : pstScanChanList -- return silent normal call scan list

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2/12/2014
   作    者   : y00245242
   修改内容   : create
 2.日    期   : 1/17/2015
   作    者   : y00307564
   修改内容   : 清TQE
 3.日    期   : 4/17/2015
   作    者   : c00299063
   修改内容   : DTS2015032505314
*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetSystemIndexOfSameOrMorePreferredThanSpecifiedSystemInGeo(
    VOS_UINT16                                              usSysMatchedIndex,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMatchedGeoInfo
)
{
    VOS_UINT16                          usGeoEndIndex;
    VOS_UINT16                          i;

    /* get end index in GEO */
    usGeoEndIndex = pstMatchedGeoInfo->usGeoFirstSysRecIndex + pstMatchedGeoInfo->usGeoSysRecNum - 1;

    for (i = usSysMatchedIndex; i <= usGeoEndIndex; i++)
    {
        if (VOS_NULL_PTR == CNAS_PRL_GetSpecifiedPrlSysRecord(i))
        {
            continue;
        }

        if (CNAS_PRL_RELATIVE_PRI_MORE == CNAS_PRL_GetSpecifiedPrlSysRecord(i)->enPriInd)
        {
            return i;
        }
    }

    return usGeoEndIndex;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildCallRedialScanChanListUponOrigSystemInGeo
 功能描述  : construct scan list when orignal system is in GEO.
 输入参数  : pstGeoListInfo -- orignal system GEO information

 输出参数  : pstScanChanList -- return silent normal call scan list

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2/12/2014
   作    者   : y00245242
   修改内容   : create
 2.日    期   : 1/17/2015
   作    者   : y00307564
   修改内容   : 清TQE
 3.日    期   : 17/1/2015
   作    者   : y00245242
   修改内容   : home SID/NID list开发
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildCallRedialScanChanListUponOrigSystemInGeo(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstOrigSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    VOS_UINT16                                              usIndex;
    VOS_UINT8                                               i;
    VOS_UINT16                                              j;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMatchLvl;
    VOS_UINT16                                              usSameOrHighIndex;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT16                                              usGeoEndIndex;
    VOS_UINT8                                               ucIsHomeSidNid;
    CNAS_PRL_1X_SYSTEM_STRU                                 stCurSysInfo;

    /* reference from section 4.7.3 in cdg143:
    If the original system is listed in the PRL system table, only channels that
    are associated with system table entries that are within the current GEO and
    comply with one of the following criteria shall be placed into the list:

    - System table entries that are same or more preferred than the original system

    - System table entries that have a home roaming indicator (as defined in Req. 2.6.2).
    */

    for (i = 0; i < pstGeoListInfo->ucGeoNum; i++)
    {
        enMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstOrigSysInfo,
                                                               &(pstGeoListInfo->astGeoInfoList[i]),
                                                               &usIndex);

        /* Actually, it should not happen. Or somewhere is error! */
        if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH == enMatchLvl)
        {
            continue;
        }

        /* add freqs in scan list that System table entries are same or more preferred than the original system */
        usSameOrHighIndex = CNAS_XSD_GetSystemIndexOfSameOrMorePreferredThanSpecifiedSystemInGeo(usIndex,
                                                                                                 &(pstGeoListInfo->astGeoInfoList[i]));
        for (j = pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex; j <= usSameOrHighIndex; j++)
        {
            pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(j);

            if (VOS_NULL_PTR == pstSysRecord)
            {
                continue;
            }

            NAS_MEM_SET_S(&stCurSysInfo, sizeof(stCurSysInfo), 0, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

            stCurSysInfo.usNid = pstSysRecord->u.st1xAndIs95Id.usNid;
            stCurSysInfo.usSid = pstSysRecord->u.st1xAndIs95Id.usSid;

            ucIsHomeSidNid = CNAS_PRL_IsCurrentSystemInHomeSidNidList(&stCurSysInfo);

            if ((CNAS_PRL_PREF_NEG_SYS_PREF == pstSysRecord->enPrefNegSys)
            ||  (VOS_TRUE                   == ucIsHomeSidNid))
            {
                pstAcqRecord = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord->usAcqIndex);
                if (VOS_NULL_PTR == pstAcqRecord)
                {
                    continue;
                }

                CNAS_XSD_AddSpecPrlAcqRecInScanChanList(pstAcqRecord, pstScanChanList);
            }
        }

        /* Add freqs in scan list that System table entries have a home roaming indicator */
        usGeoEndIndex = pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex + pstGeoListInfo->astGeoInfoList[i].usGeoSysRecNum - 1;
        for (j = usSameOrHighIndex + 1; j <= usGeoEndIndex; j++)
        {
            pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(j);

            if (VOS_NULL_PTR == pstSysRecord)
            {
                continue;
            }

            /* home roaming indicator */
            if (CNAS_PRL_SYS_ROAMING_STATUS_OFF == pstSysRecord->enRoamingInd)
            {
                pstAcqRecord = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord->usAcqIndex);
                if (VOS_NULL_PTR == pstAcqRecord)
                {
                    continue;
                }

                CNAS_XSD_AddSpecPrlAcqRecInScanChanList(pstAcqRecord, pstScanChanList);
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildCallRedialScanChanList
 功能描述  : 呼叫开始时构造呼叫重拨搜网频点列表
 输入参数  : pstOrigSysInfo---------------呼叫发起的系统,如果未驻留,指针为空
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月18日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildCallRedialScanChanList(
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampSysInfo
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU                                 stOrigSysInfo;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;

    pstScanChanList = CNAS_XSD_GetCallRedialScanChanListAddr();

    CNAS_XSD_AllocMemoryForScanChanList(pstScanChanList, CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL);

    if (VOS_NULL_PTR == pstScanChanList->pstScanChanInfo)
    {
        return;
    }

    /* check current camp on system exist or not */
    if (VOS_TRUE == pstCurCampSysInfo->ucCampOnFlag)
    {
        NAS_MEM_SET_S(&stOrigSysInfo, sizeof(stOrigSysInfo), 0, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

        NAS_MEM_CPY_S(&stOrigSysInfo, sizeof(stOrigSysInfo), &(pstCurCampSysInfo->stSystem), sizeof(CNAS_PRL_1X_SYSTEM_STRU));

        NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

        CNAS_XSD_GetMostMatched1xGeoList(&stOrigSysInfo, &stGeoListInfo);

        /* check whether or not orignal system is in PRL */
        if (0 != stGeoListInfo.ucGeoNum)
        {
            CNAS_XSD_BuildCallRedialScanChanListUponOrigSystemInGeo(&stOrigSysInfo,
                                                                    &stGeoListInfo,
                                                                    pstScanChanList);
        }
        /* orignal system is not in GEO */
        else
        {
            /* 将电信常用1X 频点加入到pstScanChanListInfo中 */
            CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

            /* reference from section 4.7.3 in cdg143:
            - If the original system is not listed in the PRL system table, all channels from
              the PRL acquisition table shall be placed into the list.
            */
            CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);
        }

        /* reference from section 4.7.3 in cdg143:
        - The list should be ordered according to the MRU, then system table entries in the current GEO.

        - The channel over which origination failed shall be placed last in the channels list.
        */

        /* The list should be ordered according to the MRU */
        CNAS_XSD_OrderScanListByMruList(pstScanChanList, CNAS_XSD_GetMruList());

        /* place the failed freq last in the channels list */
        CNAS_XSD_MoveFreqChantoEndOfChanList(&stOrigSysInfo, pstScanChanList);
    }
    else
    {
        /* 先将MRU中的频点信息增加到pstScanChanList中 */
        CNAS_XSD_AddMruListInScanChanList(pstScanChanList);

        /* 将电信常用1X 频点加入到pstScanChanListInfo中 */
        CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

        /* 然后将PRL中获取表的频点信息增加到pstScanChanList中 */
        CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);
    }

    /* 初始化当前需要搜索的频点索引为0 */
    pstScanChanList->usCurScanIndex = 0;

    CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_CALL_REDIAL_SCAN_CHAN_LIST_IND, pstScanChanList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildEmcCallRedialScanChanList
 功能描述  : 呼叫开始时构造紧急呼叫重拨搜网频点列表
 输入参数  : pstOrigSysInfo---------------呼叫发起的系统,如果未驻留,指针为空
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月07日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildEmcCallRedialScanChanList( VOS_VOID )
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList = VOS_NULL_PTR;

    pstScanChanList = CNAS_XSD_GetEmcCallRedialScanChanListAddr();

    CNAS_XSD_AllocMemoryForScanChanList(pstScanChanList, CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL);

    if (VOS_NULL_PTR == pstScanChanList->pstScanChanInfo)
    {
        return;
    }

    /* 插入同步成功后的频点 */
    CNAS_XSD_AddHistorySyncedSuccFreqListInScanChanlist(pstScanChanList);

    /* 将MRU中的频点信息增加到pstScanChanListInfo中 */
    CNAS_XSD_AddMruListInScanChanList(pstScanChanList);

    /* 将电信常用1X 频点加入到pstScanChanListInfo中 */
    CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

    /* 将PRL中获取表的频点信息增加到pstScanChanListInfo中 */
    CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);

    /* 将当前支持的Pref频点信息增加到pstScanChanListInfo中 */
    CNAS_XSD_AddUePreferredListInScanChanList(pstScanChanList);

    /* 初始化当前需要搜索的频点索引为0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_AddOrigChanToScanChanlist_REACQ_0_1_2_3_4s
 功能描述  : 重复搜索策略REACQ_0_1_2_3_4s
 输入参数  : CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
             CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstPreCampFreq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月5日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_AddOrigChanToScanChanlist_REACQ_0_1_2_3_4s(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstPreCampFreq
)
{
    VOS_UINT16                                              i;
    VOS_UINT16                                              usTotalChanNum;
    VOS_UINT16                                              usOrigChanInsertCount;
    VOS_UINT16                                              usChanIntervalCount;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                        *pstScanChanInfo    = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                        *pstSrcScanChanInfo = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stPreCampChanInfo;
    VOS_UINT16                                              usSrcTotalChanNum;

    usSrcTotalChanNum  = pstScanChanList->usTotalNum;
    pstScanChanInfo    = pstScanChanList->pstScanChanInfo;

    /*先前驻留频点信息 */
    NAS_MEM_SET_S(&stPreCampChanInfo, sizeof(stPreCampChanInfo), 0, sizeof(stPreCampChanInfo));
    stPreCampChanInfo.stFreqChan.enBandClass = pstPreCampFreq->enBandClass;
    stPreCampChanInfo.stFreqChan.usChannel   = pstPreCampFreq->usChannel;
    stPreCampChanInfo.enChanStatus           = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    /*申请空间保存原频点信息 */
    pstSrcScanChanInfo = PS_MEM_ALLOC(UEPS_PID_XSD, (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    if (VOS_NULL_PTR == pstSrcScanChanInfo)
    {
        return;
    }

    NAS_MEM_SET_S(pstSrcScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum),
                  0,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    NAS_MEM_CPY_S(pstSrcScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum),
                  pstScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    /*重写频点列表*/

    usTotalChanNum        = 0;
    usChanIntervalCount   = 0;
    usOrigChanInsertCount = 0;

    /*在频点列表头部插入先前驻留频点 */
    *pstScanChanInfo      = stPreCampChanInfo;

    /*频点总数加1 */
    usTotalChanNum++;

    /*频点间隔计数清零，插入次数加1 */
    usOrigChanInsertCount++;

    /*原频点列表的第一个也为先前驻留频点，目前的处理跳过 */
    for (i = 1; i < usSrcTotalChanNum; i++)
    {
        if (usChanIntervalCount == usOrigChanInsertCount)
        {
            /*间隔次数等于已经插入的次数，插入先前驻留频点 */
            *(pstScanChanInfo + usTotalChanNum)  = stPreCampChanInfo;

            /*频点间隔计数清零，插入次数加1 */
            usChanIntervalCount = 0;
            usOrigChanInsertCount++;

            /*频点总数加1 */
            usTotalChanNum++;
        }

        /*继续插入其他频点 */
        *(pstScanChanInfo + usTotalChanNum)  = *(pstSrcScanChanInfo + i);

        /*间隔计数加1 */
        usChanIntervalCount++;

        /*频点总数加1 */
        usTotalChanNum++;

    }

    PS_MEM_FREE(UEPS_PID_XSD, pstSrcScanChanInfo);

    pstScanChanList->usTotalNum = usTotalChanNum;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_AddOrigChanToScanChanlist_PING_5
 功能描述  : 重复搜索策略PING_5
 输入参数  : CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
             CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstPreCampFreq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月5日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_AddOrigChanToScanChanlist_PING_5(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstPreCampFreq
)
{
    VOS_UINT16                                              i;
    VOS_UINT16                                              usTotalChanNum;
    VOS_UINT16                                              usChanIntervalCount;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                        *pstScanChanInfo    = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                        *pstSrcScanChanInfo = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stPreCampChanInfo;
    VOS_UINT16                                              usSrcTotalChanNum;

    usSrcTotalChanNum  = pstScanChanList->usTotalNum;
    pstScanChanInfo    = pstScanChanList->pstScanChanInfo;

    /*先前驻留频点信息 */
    NAS_MEM_SET_S(&stPreCampChanInfo, sizeof(stPreCampChanInfo), 0, sizeof(stPreCampChanInfo));
    stPreCampChanInfo.stFreqChan.enBandClass = pstPreCampFreq->enBandClass;
    stPreCampChanInfo.stFreqChan.usChannel   = pstPreCampFreq->usChannel;
    stPreCampChanInfo.enChanStatus           = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    /*申请空间保存原频点信息 */
    pstSrcScanChanInfo = PS_MEM_ALLOC(UEPS_PID_XSD, (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    if (VOS_NULL_PTR == pstSrcScanChanInfo)
    {
        return;
    }

    NAS_MEM_SET_S(pstSrcScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum),
                  0,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    NAS_MEM_CPY_S(pstSrcScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum),
                  pstScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    /*重写频点列表*/

    usTotalChanNum      = 0;
    usChanIntervalCount = 0;

    /*在频点列表头部插入先前驻留频点 */
    *pstScanChanInfo      = stPreCampChanInfo;

    usTotalChanNum++;

    /*原频点列表的第一个也为先前驻留频点，目前的处理跳过 */
    for (i = 1; i < usSrcTotalChanNum; i++)
    {
        if (CNAS_XSD_CHANNEL_REPEAT_INTERVAL == usChanIntervalCount)
        {
            /*插入先前驻留频点 */
            *(pstScanChanInfo + usTotalChanNum)  = stPreCampChanInfo;

            /*频点间隔计数清零*/
            usChanIntervalCount = 0;

            /*频点总数加1 */
            usTotalChanNum++;
        }

        /*继续插入其他频点 */
        *(pstScanChanInfo + usTotalChanNum)  = *(pstSrcScanChanInfo + i);

        /*间隔计数加1 */
        usChanIntervalCount++;

        /*频点总数加1 */
        usTotalChanNum++;

    }

    PS_MEM_FREE(UEPS_PID_XSD, pstSrcScanChanInfo);

    pstScanChanList->usTotalNum = usTotalChanNum;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_AddOrigChanToScanChanlist_PING_5
 功能描述  : 重复搜索策略2_7
 输入参数  : CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
             CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstPreCampFreq
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月5日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_AddOrigChanToScanChanlist_2_7(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstPreCampFreq
)
{
    VOS_UINT16                                              i;
    VOS_UINT16                                              usTotalChanNum;
    VOS_UINT16                                              usChanIntervalCount;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                        *pstScanChanInfo    = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                        *pstSrcScanChanInfo = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stPreCampChanInfo;
    VOS_UINT16                                              usSrcTotalChanNum;

    usSrcTotalChanNum  = pstScanChanList->usTotalNum;
    pstScanChanInfo    = pstScanChanList->pstScanChanInfo;

    /*先前驻留频点信息 */
    NAS_MEM_SET_S(&stPreCampChanInfo, sizeof(stPreCampChanInfo), 0, sizeof(stPreCampChanInfo));
    stPreCampChanInfo.stFreqChan.enBandClass = pstPreCampFreq->enBandClass;
    stPreCampChanInfo.stFreqChan.usChannel   = pstPreCampFreq->usChannel;
    stPreCampChanInfo.enChanStatus           = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    /*申请空间保存原频点信息 */
    pstSrcScanChanInfo = PS_MEM_ALLOC(UEPS_PID_XSD, (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    if (VOS_NULL_PTR == pstSrcScanChanInfo)
    {
        return;
    }

    NAS_MEM_SET_S(pstSrcScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum),
                  0,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    NAS_MEM_CPY_S(pstSrcScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum),
                  pstScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    /*重写频点列表*/

    usTotalChanNum      = 0;
    usChanIntervalCount = 0;

    /*在频点列表头部插入先前驻留频点2次 */
    *pstScanChanInfo      = stPreCampChanInfo;

    usTotalChanNum++;

    *(pstScanChanInfo + usTotalChanNum)  = stPreCampChanInfo;

    usTotalChanNum++;

    /*原频点列表的第一个也为先前驻留频点，目前的处理跳过 */
    for (i = 1; i < usSrcTotalChanNum; i++)
    {
        if (CNAS_XSD_CHANNEL_REPEAT_INTERVAL == usChanIntervalCount)
        {
            /*插入先前驻留频点，2次 */
            *(pstScanChanInfo + usTotalChanNum)  = stPreCampChanInfo;

            /*频点总数加1 */
            usTotalChanNum++;

            *(pstScanChanInfo + usTotalChanNum)  = stPreCampChanInfo;

            /*频点总数加1 */
            usTotalChanNum++;

            /*频点间隔计数清零*/
            usChanIntervalCount = 0;
        }

        /*继续插入其他频点 */
        *(pstScanChanInfo + usTotalChanNum)  = *(pstSrcScanChanInfo + i);

        /*间隔计数加1 */
        usChanIntervalCount++;

        /*频点总数加1 */
        usTotalChanNum++;

    }

    PS_MEM_FREE(UEPS_PID_XSD, pstSrcScanChanInfo);

    pstScanChanList->usTotalNum = usTotalChanNum;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildCallRedialScanChanList
 功能描述  : 系统丢网后构造重新搜网频点列表
 输入参数  : CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月18日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildNormalSystemLostScanChanlist(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru0SysId;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stScanChanInfo;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stMatchedGeoList;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstGeoChanList  = VOS_NULL_PTR;
    VOS_UINT16                                              usGeoChanNum;
    VOS_UINT32                                              ulRet;
    VOS_UINT16                                              usMaxGeoChanNum;

    CNAS_XSD_AllocMemoryForScanChanList(pstScanChanList, CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST);

    if (VOS_NULL_PTR == pstScanChanList->pstScanChanInfo)
    {
        return;
    }

    /* 列表组成:MRU[0] + GEO LIST(ORDER BY MRU LIST) + MRU LIST + 电信常用频点 + PRL ACQ RECORD LIST */

    NAS_MEM_SET_S(&stMatchedGeoList, sizeof(stMatchedGeoList), 0x0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    /* 先将MRU[0]中的频点信息增加到pstScanChanListInfo中 */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan   = stMru0SysId.stFreq;
        stScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* 添加到频点扫描列表 */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);

        /* 从PRL系统表中查找MRU[0]中SID NID所在的GEO LIST */
        CNAS_PRL_Get1xSysGeoList(&stMru0SysId, &stMatchedGeoList);
    }

    if (0 < stMatchedGeoList.ucGeoNum)
    {
        /* calculate the max size of the geo list channel and then alloc memory */
        usMaxGeoChanNum = CNAS_PRL_CalcMatchedGeoListTotalFreqNum(&stMru0SysId, &stMatchedGeoList);

        pstGeoChanList = (CNAS_PRL_FREQENCY_CHANNEL_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * usMaxGeoChanNum);

        if (VOS_NULL_PTR == pstGeoChanList)
        {
            return;
        }

        /* 将GEO列表中每条记录的频点解析成频点列表 */
        usGeoChanNum = 0;
        ulRet        = CNAS_XSD_PraseChannelInMatchedGeoList(&stMru0SysId, &stMatchedGeoList, usMaxGeoChanNum, &usGeoChanNum, pstGeoChanList);

        /* 解析成功 */
        if (VOS_TRUE == ulRet)
        {
            /* 将查找到的GEO中对应的频点列表按照MRU的顺序进行排序 */
            CNAS_XSD_SortChanListByMruList(usGeoChanNum,pstGeoChanList,CNAS_XSD_GetMruList());

            /* 将排序好的频点列表增加pstScanChanListInfo中 */
            CNAS_XSD_AddFreqChanListInScanChanList(usGeoChanNum, pstGeoChanList,pstScanChanList);
        }

        PS_MEM_FREE(UEPS_PID_XSD, pstGeoChanList);
    }

    /* 先将除MRU[0]之外中其他MRU中的频点信息增加到pstScanChanListInfo中 */
    CNAS_XSD_AddMruListExcludeMru0InScanChanList(pstScanChanList);

    /* 将电信常用1X 频点加入到pstScanChanListInfo中 */
    CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

    /* 然后将PRL中获取表的频点信息增加到pstScanChanListInfo中 */
    CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);


    /* 初始化当前需要搜索的频点索引为0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;

}


/*****************************************************************************
 函 数 名  : CNAS_XSD_ClearCallRedialScanChanList
 功能描述  : 呼叫开始时清除呼叫重拨搜网频点列表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月18日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_ClearCallRedialScanChanList(VOS_VOID)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList = VOS_NULL_PTR;

    pstScanChanList = CNAS_XSD_GetCallRedialScanChanListAddr();

    if (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstScanChanList->pstScanChanInfo);

        pstScanChanList->pstScanChanInfo = VOS_NULL_PTR;
    }

    pstScanChanList->usTotalNum     = 0;
    pstScanChanList->usCurScanIndex = 0;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateScanChanList
 功能描述  : 更新频点扫描列表
 输入参数  : pstSrcScanChanList------------更新前的频点扫描列表
 输出参数  : pstDestScanChanList-----------更新后的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月5日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstDestScanChanList,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstSrcScanChanList
)
{
    VOS_UINT16                          i;

    if ((VOS_NULL_PTR == pstSrcScanChanList->pstScanChanInfo)
     || (VOS_NULL_PTR == pstDestScanChanList->pstScanChanInfo))
    {
        return;
    }

    for (i = 0; i < pstSrcScanChanList->usTotalNum; i++)
    {
        pstDestScanChanList->usTotalNum     = pstSrcScanChanList->usTotalNum;
        pstDestScanChanList->usCurScanIndex = pstSrcScanChanList->usCurScanIndex;

        NAS_MEM_CPY_S(&(pstDestScanChanList->pstScanChanInfo[i]),
                      sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU),
                      &(pstSrcScanChanList->pstScanChanInfo[i]),
                      sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));
    }

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_CallRedial
 功能描述  : 开机扫描频点列表构造
 输入参数  : usPreSrchChanNum ------------ 当前需要优先搜索的频点个数,构造时需要增加到扫描频点列表中
             pstPreSrchChanArray---------- 当前需要优先搜索的频点数组头指针,构造时需要增加到扫描频点列表中
 输出参数  : pstScanChanList---------------构造好的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月18日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_CallRedial(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstCallRedialScanChanList = VOS_NULL_PTR;
    VOS_UINT16                          i;

    pstCallRedialScanChanList = CNAS_XSD_GetCallRedialScanChanListAddr();

    CNAS_XSD_UpdateScanChanList(pstScanChanList, pstCallRedialScanChanList);

    /* if the call redial channel list has been synced finished,we should reset
       the index and the channle status. */
    if (pstScanChanList->usCurScanIndex >= pstScanChanList->usTotalNum - 1)
    {
        for (i = 0; i < pstScanChanList->usTotalNum; i++)
        {
            pstScanChanList->pstScanChanInfo[i].enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;
        }

        pstScanChanList->usCurScanIndex = 0;
    }

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateChanStatusInScanChanList
 功能描述  : 更新指定频点在扫描频点列表中的频点搜索状态
 输入参数  : usBeginScanListIndex --------------- 开始的index
             pstChannel--------------- 指定频点
             enChanStatus--------------------频点状态
             pstScanChanList -----------------当前的频点扫描列表
 输出参数  : pstScanChanList-------------------当前的频点扫描列表
 返 回 值  : VOS_UINT16 -- 返回当前刷新的频点在scan list中的索引
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月05日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2015年9月8日
   作    者   : y00245242
   修改内容   : DTS2015090601618
*****************************************************************************/
VOS_UINT16 CNAS_XSD_UpdateChanStatusInScanChanList(
    VOS_UINT16                                              usBeginScanListIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstChannel,
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enChanStatus,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    VOS_UINT16                          i;

    for (i = usBeginScanListIndex; i < pstScanChanList->usTotalNum; i++)
    {
        if ((pstChannel->enBandClass == pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass)
         && (pstChannel->usChannel   == pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel))
        {
            pstScanChanList->pstScanChanInfo[i].enChanStatus = enChanStatus;

            return i;
        }
    }

    /* 如果没有找到，仍然返回当前的索引 */
    return usBeginScanListIndex;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateSysFreqStatusBySysInGeoSysRecordSrchList
 功能描述  : 更新指定系统在捕获系统列表中的状态
 输入参数  : pstSysInfo--------------- 指定系统
             enSysStatus----------------系统状态
             pstSysAcqList ---------------系统捕获列表
 输出参数  : pstSysAcqList------------------系统捕获列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月16日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateSysFreqStatusBySysInGeoSysRecordSrchList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enSysStatus,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                          i;

    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++)
    {
        if (VOS_TRUE == CNAS_PRL_Is1xSysMatched(pstSysInfo, &(pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys)))
        {
            /* 不重复刷新捕获过的系统状态 */
            if (CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED == pstGeoSysRecSrchList->pstAcqSysInfo[i].enSysStatus)
            {
                pstGeoSysRecSrchList->pstAcqSysInfo[i].enSysStatus = enSysStatus;
                break;
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateSysFreqStatusByFreqChanInGeoSysRecordSrchList
 功能描述  : 根据指定的频点在系统捕获列表中查找对应的系统列表并更新状态
 输入参数  : pstFreqChan--------------- 指定频点
             enSysStatus----------------系统状态
             pstSysAcqList ---------------系统捕获列表
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月28日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2015年7月27日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/

VOS_VOID CNAS_XSD_UpdateSysFreqStatusByFreqChanInGeoSysRecordSrchList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqChan,
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enSysStatus,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstSysAcqList
)
{
    VOS_UINT16                          i;

    for (i = 0; i < pstSysAcqList->usTotalNum; i++)
    {
        if ((pstFreqChan->enBandClass == pstSysAcqList->pstAcqSysInfo[i].stAcqSys.stFreq.enBandClass)
         && (pstFreqChan->usChannel   == pstSysAcqList->pstAcqSysInfo[i].stAcqSys.stFreq.usChannel))
        {
             /* 刷新频点状态 */
            pstSysAcqList->pstAcqSysInfo[i].enSysStatus = enSysStatus;
        }
    }


    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RemoveExpiredFreqFromAvoidList
 功能描述  : 检查到期的频点，如果有频点到期，从avoid列表中剔除该频点
 输入参数  : 无

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月14日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_RemoveExpiredFreqFromAvoidList(VOS_VOID)
{
    VOS_UINT32                                              ulCurSlice;
    VOS_UINT32                                              ulRunSliceNum;
    VOS_UINT8                                               i;
    CNAS_XSD_AVOID_FREQ_INFO_STRU                          *pstAvoidFreqInfo = VOS_NULL_PTR;


    /* 获取当前系统的slice */
    ulCurSlice = CNAS_XSD_GetSystemSlice();

    /* 遍历avoid列表中所有的频点的到期slice */
    for (i = 0; i < CNAS_MIN(CNAS_XSD_GetAvoidFreqListNum(), CNAS_XSD_MAX_AVOID_FREQ_NUM); i++)
    {
        pstAvoidFreqInfo = CNAS_XSD_GetAvoidFreqFromAvoidList(i);

        if (VOS_NULL_PTR == pstAvoidFreqInfo)
        {
            /* 空指针保护 */
            continue;
        }

        if (VOS_FALSE == pstAvoidFreqInfo->ucAvoidFlag)
        {
            continue;
        }

        if (ulCurSlice < pstAvoidFreqInfo->ulStartSlice)
        {
            /* 考虑反转问题 */
            ulRunSliceNum = CNAS_XSD_MAX_SLICE_VALUE- pstAvoidFreqInfo->ulStartSlice + ulCurSlice + 1;
        }
        else
        {
            ulRunSliceNum = ulCurSlice - pstAvoidFreqInfo->ulStartSlice;
        }

        /* 如果已经运行的slice数目大于等于到期的slice数目，从avoid频点列表中剔除该频点 */
        if (ulRunSliceNum >= pstAvoidFreqInfo->ulExpiredSliceNum)
        {
            CNAS_XSD_DeleteAvoidFlagFromAvoidList(i);

            /* 对于解禁的频点，这里刷新scan list频点为未搜索，确保后续能搜索到 */
            (VOS_VOID)CNAS_XSD_UpdateChanStatusInScanChanList(0,
                                                              &(pstAvoidFreqInfo->stAvoidFreq),
                                                              CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED,
                                                              CNAS_XSD_GetScanChanListAddr());


        }
    }

    /*如果avoid列表中不存在禁用标记，表示没有被禁用的频点，停止定时器 */
    if (VOS_FALSE == CNAS_XSD_IsExistAvoidFlagInAvoidlist())
    {
        CNAS_XSD_StopTimer(TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER);
    }

    CNAS_XSD_LogAvoidFreqList(CNAS_XSD_GetAvoidFreqListAddr());
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsCurFreqAvoided
 功能描述  : 检查当前频点是否在avoid列表中被禁
 输入参数  : pstFreqChan -- 频点信息指针

 输出参数  : 无

 返 回 值  : VOS_TRUE  -- 当前频点被禁
             VOS_FALSE -- 当前频点不被禁
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月14日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsCurFreqAvoided(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqChan
)
{
    VOS_UINT8                           i;
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;

    /* 遍历avoid列表中所有的频点，当前频点在avoid列表中, 返回VOS_TRUE */
    pstAvoidFreqList = CNAS_XSD_GetAvoidFreqListAddr();

    for (i = 0; i < CNAS_MIN(pstAvoidFreqList->ucAvoidFreqNum, CNAS_XSD_MAX_AVOID_FREQ_NUM); i++)
    {
        if (VOS_FALSE == pstAvoidFreqList->astAvoidFreqInfo[i].ucAvoidFlag)
        {
            continue;
        }

        if ((pstAvoidFreqList->astAvoidFreqInfo[i].stAvoidFreq.enBandClass == pstFreqChan->enBandClass)
         && (pstAvoidFreqList->astAvoidFreqInfo[i].stAvoidFreq.usChannel   == pstFreqChan->usChannel))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetNextScanChanList
 功能描述  : 获取下个未扫描过的频点列表
 输入参数  : ucInsertMru0Freq  ----------插入MRU0频点
             usCurScanChanIndex----------当前扫描到的频点索引
             pstScanChanList------当前的扫描频点列表
 输出参数  : pusDstChanNum-----------获取到的频点个数
             pstDstChan--------------获取到的频点列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月05日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2015年1月05日
   作    者   : y00245242
   修改内容   : 增加OOC搜索策略

 3.日    期   : 2015年7月21日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_GetNextScanChanList(
    VOS_UINT16                          usCurScanChanIndex,
    VOS_UINT16                         *pusDstChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstChan,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList,
    VOS_UINT32                          ulIsAvoidListEnable
)
{
    VOS_UINT16                          usChanScanNum;
    VOS_UINT16                          i;
    VOS_UINT16                          j;

    /* 当前还未扫描的频点总个数 */
    usChanScanNum   = pstScanChanList->usTotalNum - usCurScanChanIndex;

    *pusDstChanNum = 0;

    /* scan list个数为0，直接退出 */
    if (0 == usChanScanNum)
    {
        return;
    }

    /* 检查avoid列表中到期的频点，从表中剔除 */
    CNAS_XSD_RemoveExpiredFreqFromAvoidList();

    /* 最多一次取32个频点发给AS进行同步 */
    if (CNAS_CAS_1X_MAX_FREQ_NUM <= usChanScanNum)
    {
        usChanScanNum = CNAS_CAS_1X_MAX_FREQ_NUM;
    }

    j = 0;

    for (i = usCurScanChanIndex; i < pstScanChanList->usTotalNum; i++)
    {
        /* 同步存在的频点的也允许被搜索 */
        if ((CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED    == pstScanChanList->pstScanChanInfo[i].enChanStatus)
         || (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_EXIST == pstScanChanList->pstScanChanInfo[i].enChanStatus))
        {
            /* 如果当前频点在avoid列表中，进行下一个检查 */
            if ((VOS_TRUE   == CNAS_XSD_IsCurFreqAvoided(&pstScanChanList->pstScanChanInfo[i].stFreqChan))
             && (VOS_TRUE   == ulIsAvoidListEnable))
            {
                /* 下面处理原则:
                 *  从频点扫描列表中取未同步的且非avoid的频点，遇到avoid的频点处理如下:
                 *  1) 如果pstDstChan中的频点个数为0，继续获取未同步的且非avoid的频点；
                 *  2) 如果pstDstChan中的频点个数不为0，跳出循环；
                 *  原因: 因为AS同步一个频点时，时间可能会很长，当下一次频点同步时，很可能被禁的
                 *        的频点已经解禁，这会给avoid频点更多搜索机会。
                 */
                if (0 == j)
                {
                    /* 如果pstDstChan中频点个数为0，继续下一个频点检查 */
                    continue;
                }
                else
                {
                    /* 如果pstDstChan中频点个数不为0，跳出循环， */
                    break;
                }
            }

            pstDstChan[j].enBandClass = pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass;
            pstDstChan[j].usChannel   = pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel;

            j++;

            if (j >= usChanScanNum)
            {
                break;
            }
        }
    }

    (*pusDstChanNum) = j;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsSpecifiedFreqSrchedInGeoSysRecordSrchList
 功能描述  : GEO系统记录搜索列表是否搜索过
 输入参数  : pstFreq       -- 指定的频点
             pstAcqSysInfo -- 捕获的系统信息
 输出参数  :

 返 回 值  : VOS_TRUE  -- 已经搜索过
             VOS_FALSE -- 未搜索过
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年7月6日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsSpecifiedFreqSrchedInGeoSysRecordSrchList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU  *pstAcqSysInfo
)
{
    /* 未捕获过的系统且非NEG的系统,相同频点则允许捕获 */
    if ((pstFreq->enBandClass                    == pstAcqSysInfo->stAcqSys.stFreq.enBandClass)
     && (pstFreq->usChannel                      == pstAcqSysInfo->stAcqSys.stFreq.usChannel)
     && ((CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED    == pstAcqSysInfo->enSysStatus)
      || (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_EXIST == pstAcqSysInfo->enSysStatus)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_GetNextSysSyncListFromGeoSysRecordSrchList
 功能描述  : 获取下个未捕获过的系统列表
 输入参数  : pstSysAcqList  -- 当前的系统捕获列表
 输出参数  : pusScanChanNum -- 返回下次同步的搜索频点数目
             pstScanList    -- 获取到下发发给AS的scan list
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月15日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2015年7月4日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_GetNextSysSyncListFromGeoSysRecordSrchList(
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList,
    VOS_UINT16                                             *pusScanChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstScanList
)
{
    VOS_UINT16                                              i;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stTmpChannel;

    *pusScanChanNum = 0;

    /* 解禁avoid列表中到期的频点 */
    CNAS_XSD_RemoveExpiredFreqFromAvoidList();

    CNAS_XSD_UpdateGeoSysRecordListInfoAccordingToScanChanList(pstGeoSysRecSrchList);

    for (i = 0; ((i < pstGeoSysRecSrchList->usTotalNum) && (*pusScanChanNum < CNAS_CAS_1X_MAX_FREQ_NUM)); i++)
    {
        stTmpChannel = pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.stFreq;

        /*******************************************************************************************
         *  1. 如果当前level已经全部取完，停止加scan list列表；注: 如果当前level的频点没有需要搜索的，
         *     跳到下一个level系统记录进行搜索
         ******************************************************************************************/
        if (pstGeoSysRecSrchList->usCurSrchLevel != pstGeoSysRecSrchList->pstAcqSysInfo[i].usLevel)
        {
            if (0 != *pusScanChanNum)
            {
                /* 相同level优先级的系统已经全部取完 */
                return;
            }
            else
            {
                /* 当前GEO中没有需要搜索的频点，取GEO中下一个level的系统表频点去搜索 */
                pstGeoSysRecSrchList->usCurSrchLevel = pstGeoSysRecSrchList->pstAcqSysInfo[i].usLevel;
            }
        }

        /*******************************************************************************************
         *  2. 检查当前频点是否被禁，如果被禁，跳过该频点
         ******************************************************************************************/
        if (VOS_TRUE == CNAS_XSD_IsCurFreqAvoided(&stTmpChannel))
        {
            continue;
        }

        /*******************************************************************************************
         *  3. 当前频点在scan list中，同步不存在的，跳过；
         ******************************************************************************************/
        if (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST == CNAS_XSD_GetScanChanStatusInScanChanList(&stTmpChannel,
                                                                                                  CNAS_XSD_GetScanChanListAddr()))
        {
            continue;
        }

        /*******************************************************************************************
         *  4. 跳过发送给AS的同步list中已经存在的频点
         ******************************************************************************************/
        if (VOS_TRUE == CNAS_XSD_IsChannelInSndCasSyncList(&stTmpChannel, pstScanList, *pusScanChanNum))
        {
            continue;
        }

        /*******************************************************************************************
         *  5. 跳过表中搜索不存在的系统
         ******************************************************************************************/
        if (VOS_FALSE == CNAS_XSD_IsSpecifiedFreqSrchedInGeoSysRecordSrchList(&stTmpChannel,
                                                                              &pstGeoSysRecSrchList->pstAcqSysInfo[i]))
        {
            continue;
        }

        /*******************************************************************************************
         *  6. 添加scan list列表
         ******************************************************************************************/
        pstScanList[*pusScanChanNum].enBandClass = pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.stFreq.enBandClass;
        pstScanList[*pusScanChanNum].usChannel   = pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.stFreq.usChannel;

        (*pusScanChanNum)++;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_PraseChannelInMatchedGeoList
 功能描述  : 根据匹配的GEO列表解析出对应的频点
 输入参数  : pstMatchedGeoList------匹配的GEO列表
             usMaxGeoChanNum--------最大的GEO频点个数
 输出参数  : pusGeoChanNum-------解析GEO后的频点个数
             pstGeoChanList------解析GEO后的频点列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月5日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 3/1/2015
   作    者   : w00176964
   修改内容   : place the alloc memory logic outside of this function
 3.日    期   : 2015年08月27日
   作    者   : t00323010
   修改内容   : DTS2015081904804 clear pc-lint warning
*****************************************************************************/
VOS_UINT32 CNAS_XSD_PraseChannelInMatchedGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMatchedGeoList,
    VOS_UINT16                                              usMaxGeoChanNum,
    VOS_UINT16                                             *pusGeoChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstGeoChanList
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          j;
    VOS_UINT16                          usIndex;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec  = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord  = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stAcqRecFreqInfo;
    VOS_UINT16                          usSysRecNum;
    VOS_UINT16                          usTotalSysRecNum;

    usSysRecNum         = 0;
    usTotalSysRecNum    = 0;

    /* 消除PCLINT 429告警 */
    pstGeoChanList = pstGeoChanList;

    /* 计算当前可能的最大系统记录数 */
    for (i = 0; i < (VOS_UINT8)CNAS_MIN(pstMatchedGeoList->ucGeoNum, CNAS_PRL_MAX_MATCHING_GEO_NUM); i++)
    {
        usTotalSysRecNum += pstMatchedGeoList->astGeoInfoList[i].usGeoSysRecNum;
    }

    pstSysRecord = PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU) * usTotalSysRecNum);

    /* 如果是空指针，直接返回 */
    if (VOS_NULL_PTR == pstSysRecord)
    {
        return VOS_FALSE;
    }

    CNAS_PRL_BuildGeoSysRecList(pstSysInfo, pstMatchedGeoList, VOS_TRUE, &usSysRecNum, pstSysRecord);

    *pusGeoChanNum = 0;
    usIndex        = 0;

    for (i = 0; i < usSysRecNum; i++)
    {
        /* 获取PRL中获取表指针 */
        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord[i].usAcqIndex);

        /* 空指针进行保护 */
        if (VOS_NULL_PTR == pstPrlAcqRec)
        {
            continue;
        }

        /* 类型判断，HRPD频点不添加 */
        if (CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD == pstPrlAcqRec->enAcqType)
        {
            continue;
        }

        CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stAcqRecFreqInfo);

        for (j = 0; (j < CNAS_MIN(stAcqRecFreqInfo.ulNum, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM)) && (*pusGeoChanNum < usMaxGeoChanNum); j++)
        {
            if (VOS_FALSE == CNAS_XSD_IsChannelInChannelList(&(stAcqRecFreqInfo.astFreqInfo[j]), *pusGeoChanNum, pstGeoChanList))
            {
                pstGeoChanList[usIndex++] = stAcqRecFreqInfo.astFreqInfo[j];

                (*pusGeoChanNum)++;
            }
        }
    }

    /* 释放内存pstSysRecord */
    PS_MEM_FREE(UEPS_PID_XSD, pstSysRecord);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_SortChanListByMruList
 功能描述  : 根据MRU列表对已知的频点列表进行排序
 输入参数  : usChanNum------原始的频点列表个数
             pstChanList----原始的频点列表
             pstMruList----MRU列表
 输出参数  : usChanNum------排好序的频点列表个数
             pstChanList----排好序的频点列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月85日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
/*lint -e429*/
VOS_VOID CNAS_XSD_SortChanListByMruList(
    VOS_UINT16                          usChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChanList,
    CNAS_XSD_MRU_LIST_STRU             *pstMruList
)
{
    VOS_UINT8                           i;
    VOS_UINT16                          j;

    for (i = CNAS_MIN(pstMruList->ucSysNum, CNAS_XSD_MAX_MRU_SYS_NUM); i > 0; i--)
    {
        for (j = 0; j < usChanNum; j++)
        {
            /* 找到频点则将对应的频点删除,将找到频点插入到数组头部 */
            if ((pstMruList->astSystem[i-1].stFreq.enBandClass == pstChanList[j].enBandClass)
             && (pstMruList->astSystem[i-1].stFreq.usChannel   == pstChanList[j].usChannel))
            {
                if (0 != j)
                {
                    NAS_MEM_MOVE_S(&(pstChanList[1]),
                                   sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (usChanNum - 1),
                                   &(pstChanList[0]),
                                   sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * j);
                }

                pstChanList[0] = pstMruList->astSystem[i-1].stFreq;
                break;
            }
        }
    }

    return;
}
/*lint +e429*/

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetScanChanStatusInScanChanList
 功能描述  : 判断指定的频点在扫描频点列表中的扫描状态
 输入参数  : pstFreq-------------指定的频点
             pstScanChanList-------频点扫描列表
 输出参数  : 无
 返 回 值  : 频点扫描状态
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月21日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/

CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8 CNAS_XSD_GetScanChanStatusInScanChanList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                              i;
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8    enChanSta;

    enChanSta       = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    for (i = 0; i < pstScanChanList->usTotalNum; i++)
    {
        if ((pstFreq->enBandClass == pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass)
         && (pstFreq->usChannel   == pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel))
        {
            enChanSta       = pstScanChanList->pstScanChanInfo[i].enChanStatus;

            break;
        }
    }

    return enChanSta;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_AddFreqChanListInScanChanList
 功能描述  : 向频点扫描列表中增加频点扫描列表
 输入参数  : usChanNum---------频点列表个数
             pstChanList------频点列表
 输出参数  : pstScanChanList-------------增加PRL中获取记录列表后的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月12日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
/*lint -e429*/
VOS_VOID CNAS_XSD_AddFreqChanListInScanChanList(
    VOS_UINT16                          usChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChanList,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          i;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stScanChanInfo;

    for (i = 0; i < usChanNum; i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan    = pstChanList[i];
        stScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* 添加到频点扫描列表 */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}
/*lint +e429*/


/*****************************************************************************
 函 数 名  : NAS_MMC_AddMruListInScanChanList
 功能描述  : 向频点扫描列表中增加MRU列表
 输入参数  : 无
 输出参数  : pstScanChanList-------------增加MRU列表后的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月12日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_AddMruListInScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          i;
    CNAS_XSD_MRU_LIST_STRU             *pstMruList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stScanChanInfo;

    pstMruList = CNAS_XSD_GetMruList();

    for (i = 0; i < CNAS_MIN(pstMruList->ucSysNum, CNAS_XSD_MAX_MRU_SYS_NUM); i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan   = pstMruList->astSystem[i].stFreq;
        stScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* 添加到频点扫描列表 */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_AddUePreferredListInScanChanList
 功能描述  : 向频点扫描列表中增加Band0和Band10中Preferred频点
 输入参数  : 无
 输出参数  : pstScanChanList
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月07日
   作    者   : h00313353
   修改内容   : 新生成函数

 2.日    期   : 2015年9月23日
   作    者   : y00245242
   修改内容   : DTS2015091901326
*****************************************************************************/
VOS_VOID CNAS_XSD_AddUePreferredListInScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT32                                              i;
    CNAS_PRL_BANDCLASS0_SUBCLASS_CHAN_STRU  const          *pstBand0Tab     = VOS_NULL_PTR;
    CNAS_PRL_BANDCLASS10_SUBCLASS_CHAN_STRU const          *pstBand10Tab    = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stScanChanInfo;
    VOS_UINT32                                              ulBand0TabSize;
    VOS_UINT32                                              ulBand10TabSize;
    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                   *pstCdmaStandardChan = VOS_NULL_PTR;

    ulBand0TabSize  = CNAS_PRL_GetBand0PrefChanTabSize();
    ulBand10TabSize = CNAS_PRL_GetBand10PrefChanTabSize();
    pstBand0Tab     = CNAS_PRL_GetBand0PrefChanTab();
    pstBand10Tab    = CNAS_PRL_GetBand10PrefChanTab();

    /* 添加BC0中SUBCLASS类型0的频点 */
    pstCdmaStandardChan = CNAS_CCB_GetCdmaStandardChannels();

    stScanChanInfo.stFreqChan.enBandClass   = CNAS_PRL_BAND_CLASS_TYPE_0;
    stScanChanInfo.enChanStatus             = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    stScanChanInfo.stFreqChan.usChannel     = pstCdmaStandardChan->usPrimaryA;
    CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);

    stScanChanInfo.stFreqChan.usChannel     = pstCdmaStandardChan->usPrimaryB;
    CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);

    stScanChanInfo.stFreqChan.usChannel     = pstCdmaStandardChan->usSecondaryA;
    CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);

    stScanChanInfo.stFreqChan.usChannel     = pstCdmaStandardChan->usSecondaryB;
    CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);

    for (i = 0; i < ulBand0TabSize; i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x00, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan.usChannel     = pstBand0Tab[i].usChan;
        stScanChanInfo.stFreqChan.enBandClass   = CNAS_PRL_BAND_CLASS_TYPE_0;
        stScanChanInfo.enChanStatus             = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* 添加到频点扫描列表 */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    for (i = 0; i < ulBand10TabSize; i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x00, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan.usChannel     = pstBand10Tab[i].usChan;
        stScanChanInfo.stFreqChan.enBandClass   = CNAS_PRL_BAND_CLASS_TYPE_10;
        stScanChanInfo.enChanStatus             = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* 添加到频点扫描列表 */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_AddSyncedSuccFreqListinScanChanlist
 功能描述  : 向频点扫描列表中增加开机后同步成功过的频点
 输入参数  : 无
 输出参数  : pstScanChanList
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月07日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_AddHistorySyncedSuccFreqListInScanChanlist(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stScanChanInfo;
    CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU             *pstSyncedSuccFreqList   = VOS_NULL_PTR;

    pstSyncedSuccFreqList               = CNAS_XSD_GetHistorySyncedSysFreqList();

    for (i = 0; i < CNAS_MIN(pstSyncedSuccFreqList->ulCurNum, CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM); i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x00, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan.usChannel     = pstSyncedSuccFreqList->astFreq[i].usChannel;
        stScanChanInfo.stFreqChan.enBandClass   = pstSyncedSuccFreqList->astFreq[i].enBandClass;
        stScanChanInfo.enChanStatus             = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* 添加到频点扫描列表 */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_AddCdma1XPrefChannelsInScanChanlist
 功能描述  : 向频点扫描列表中增加CDMA 1X 优选频点
 输入参数  : 无
 输出参数  : pstScanChanList
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月07日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stScanChanInfo;
    CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU             *pstCdma1XCustomPrefChan    = VOS_NULL_PTR;

    pstCdma1XCustomPrefChan                                 = CNAS_XSD_GetCdma1XCustomPrefChannels();

    if (VOS_FALSE == pstCdma1XCustomPrefChan->ucEnableFlg)
    {
        return;
    }

    for (i = 0; i < pstCdma1XCustomPrefChan->usFreqNum; i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x00, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan.usChannel     = pstCdma1XCustomPrefChan->astFreqList[i].usChannel;
        stScanChanInfo.stFreqChan.enBandClass   = pstCdma1XCustomPrefChan->astFreqList[i].enBandClass;
        stScanChanInfo.enChanStatus             = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* 添加到频点扫描列表 */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_AddMruListExcludeMru0InScanChanList
 功能描述  : 向频点扫描列表中增加除MRU0以外的MRU列表
 输入参数  : 无
 输出参数  : pstScanChanList-------------增加MRU0以外的MRU列表后的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月12日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_AddMruListExcludeMru0InScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          i;
    CNAS_XSD_MRU_LIST_STRU             *pstMruList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stScanChanInfo;

    pstMruList = CNAS_XSD_GetMruList();

    for (i = 1; i < CNAS_MIN(pstMruList->ucSysNum, CNAS_XSD_MAX_MRU_SYS_NUM); i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan   = pstMruList->astSystem[i].stFreq;
        stScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* 添加到频点扫描列表 */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_AddSpecPrlAcqRecInScanChanList
 功能描述  : 向频点扫描列表中增加PRL中指定获取记录频点信息
 输入参数  : pstPrlAcqRec---------------指定的PRL中的系统表记录
 输出参数  : pstScanChanList-------------增加PRL中获取记录列表后的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月12日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_AddSpecPrlAcqRecInScanChanList(
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          i;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stAcqRecFreqInfo;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stScanChanInfo;

    /* 类型判断，HRPD频点不添加 */
    if (CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD == pstPrlAcqRec->enAcqType)
    {
        return;
    }

    CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stAcqRecFreqInfo);

    for (i = 0; i < CNAS_MIN(stAcqRecFreqInfo.ulNum, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan.enBandClass = stAcqRecFreqInfo.astFreqInfo[i].enBandClass;
        stScanChanInfo.stFreqChan.usChannel   = stAcqRecFreqInfo.astFreqInfo[i].usChannel;
        stScanChanInfo.enChanStatus           = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* 添加到频点扫描列表 */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_AddPrlAcqRecListInScanChanList
 功能描述  : 向频点扫描列表中增加PRL中的获取记录列表
 输入参数  : 无
 输出参数  : pstScanChanList-------------增加PRL中获取记录列表后的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月12日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_AddPrlAcqRecListInScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          i;
    CNAS_PRL_ACQ_RECORD_INFO_STRU      *pstAcqRecInfo = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec  = VOS_NULL_PTR;

    pstAcqRecInfo = CNAS_PRL_GetPrlAcqInfoAddr();

    for (i = 0; i < CNAS_MIN(pstAcqRecInfo->usAcqRecordNum, CNAS_PRL_ACQ_RECORD_MAX_NUM); i++)
    {
        /* 获取PRL中获取表指针 */
        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(i);

        /* 空指针进行保护 */
        if ((VOS_NULL_PTR == pstPrlAcqRec)
         || (VOS_FALSE    == pstPrlAcqRec->ucAcqValid))
        {
            continue;
        }

        CNAS_XSD_AddSpecPrlAcqRecInScanChanList(pstPrlAcqRec, pstScanChanList);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_AppendFreqChanInScanChanList
 功能描述  : 向频点扫描列表中加入指定频点
 输入参数  : pstScanChanInfo-----指定的扫描频点信息
 输出参数  : pstScanChanList----------频点扫描列表信息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月12日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年12月26日
   作    者   : w00176964
   修改内容   : CDMA 1X Iteration Modifed:Remove the band class that are not supported BY MS
*****************************************************************************/
VOS_VOID CNAS_XSD_AppendFreqChanInScanChanList(
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU    *pstScanChanInfo,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usIndex;
    /* could not add the band class or channel which is not supported by UE */
    if (VOS_FALSE == CNAS_XSD_IsUeSupportedFreq(pstScanChanInfo->stFreqChan))
    {
        return;
    }

    /* the totoal num is larger than the max channel list size, should not add chan to the list */
    if (pstScanChanList->usTotalNum >= pstScanChanList->usMaxScanChanSize)
    {
        return;
    }

    for (i = 0; i < pstScanChanList->usTotalNum; i++)
    {
        /* 不添加重复频点 */
        if ((pstScanChanInfo->stFreqChan.enBandClass == pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass)
         && (pstScanChanInfo->stFreqChan.usChannel   == pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel))
        {
            return;
        }
    }

    usIndex = pstScanChanList->usTotalNum;

    NAS_MEM_SET_S(&(pstScanChanList->pstScanChanInfo[usIndex]), sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

    pstScanChanList->pstScanChanInfo[usIndex].stFreqChan   = pstScanChanInfo->stFreqChan;
    pstScanChanList->pstScanChanInfo[usIndex].enChanStatus = pstScanChanInfo->enChanStatus;
    pstScanChanList->usTotalNum++;

    return;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_IsChannelInSndCasSyncList
 功能描述  : check当前发送给CAS中的频点列表中是否有需要同步的频点
 输入参数  : pstFreqChan -- 需要同步的频点
             pstScanList -- 发送给AS的同步列表
             usScanNum   -- 当前同步列表中数目
 输出参数  : 无
 返 回 值  : VOS_TRUE:当前频点在里面
             VOS_FALSE:当前频点不在里面
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月12日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2015年7月4日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsChannelInSndCasSyncList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqChan,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstScanList,
    VOS_UINT16                                              usScanNum
)
{
    VOS_UINT16                          i;

    /* 禁止添加重复频点的系统 */
    for (i = 0; i < CNAS_MIN(usScanNum, CNAS_CAS_1X_MAX_FREQ_NUM); i++)
    {
        if ((pstScanList[i].enBandClass == pstFreqChan->enBandClass)
         && (pstScanList[i].usChannel   == pstFreqChan->usChannel))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_AppendAcqSysInfoInAcqSysList
 功能描述  : 向捕获系统列表中增加捕获系统信息
 输入参数  : pstAcqSysInfo-----指定的捕获系统信息
 输出参数  : pstScanChanList----------捕获系统列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月12日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年7月6日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_AppendAcqSysInfoInAcqSysList(
    CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU                      *pstAcqSysInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usIndex;

    if (VOS_FALSE == CNAS_XSD_IsUeSupportedFreq(pstAcqSysInfo->stAcqSys.stFreq))
    {
        return;
    }

    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++)
    {
        /* 不添加重复系统 */
        if (VOS_TRUE == CNAS_PRL_Is1xSysMatched(&(pstAcqSysInfo->stAcqSys), &(pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys)))
        {
            return;
        }
    }

    /* the totoal num is larger than the max acq sys list size, should not add sys to the list */
    if (pstGeoSysRecSrchList->usTotalNum >= pstGeoSysRecSrchList->usMaxAcqSysSize)
    {
        return;
    }

    usIndex = pstGeoSysRecSrchList->usTotalNum;

    NAS_MEM_SET_S(&(pstGeoSysRecSrchList->pstAcqSysInfo[usIndex]), sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU), 0x0, sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU));

    pstGeoSysRecSrchList->pstAcqSysInfo[usIndex].stAcqSys.stFreq = pstAcqSysInfo->stAcqSys.stFreq;
    pstGeoSysRecSrchList->pstAcqSysInfo[usIndex].stAcqSys.usNid  = pstAcqSysInfo->stAcqSys.usNid;
    pstGeoSysRecSrchList->pstAcqSysInfo[usIndex].stAcqSys.usSid  = pstAcqSysInfo->stAcqSys.usSid;
    pstGeoSysRecSrchList->pstAcqSysInfo[usIndex].enPrefNegSys    = pstAcqSysInfo->enPrefNegSys;
    pstGeoSysRecSrchList->pstAcqSysInfo[usIndex].enSysStatus     = pstAcqSysInfo->enSysStatus;
    pstGeoSysRecSrchList->pstAcqSysInfo[usIndex].usLevel         = pstAcqSysInfo->usLevel;

    pstGeoSysRecSrchList->usTotalNum++;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_AddSysRecordIntoSysList
 功能描述  : 向捕获系统列表中增加捕获系统信息
 输入参数  : pstFreq             -----频点信息
             pstSysRecord        -----系统记录
 输出参数  : pstGeoSysRecSrchList-----GEO系统记录搜索列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月12日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年7月6日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_AddSysRecordIntoSysList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU   stTmpAcqSysInfo;
    VOS_UINT32                          k;

    if (CNAS_PRL_SYS_RECORD_TYPE_1X_IS95 == pstSysRecord->enRecordType)
    {
        NAS_MEM_SET_S(&stTmpAcqSysInfo, sizeof(stTmpAcqSysInfo), 0x0, sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU));

        stTmpAcqSysInfo.stAcqSys.stFreq = *pstFreq;
        stTmpAcqSysInfo.stAcqSys.usNid  = pstSysRecord->u.st1xAndIs95Id.usNid;
        stTmpAcqSysInfo.stAcqSys.usSid  = pstSysRecord->u.st1xAndIs95Id.usSid;
        stTmpAcqSysInfo.enSysStatus     = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;
        stTmpAcqSysInfo.enPrefNegSys    = pstSysRecord->enPrefNegSys;
        stTmpAcqSysInfo.usLevel         = pstSysRecord->usPriLvl;

        CNAS_XSD_AppendAcqSysInfoInAcqSysList(&stTmpAcqSysInfo, pstGeoSysRecSrchList);
    }

    if ( (CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord->enRecordType)
      && ( (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID     == pstSysRecord->u.stMccMncId.enMccMncSubType)
        || (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID_NID == pstSysRecord->u.stMccMncId.enMccMncSubType) ) )
    {
        for (k = 0; k < pstSysRecord->u.stMccMncId.u.stSidNid.ucSidNidNum;k++)
        {
            NAS_MEM_SET_S(&stTmpAcqSysInfo, sizeof(stTmpAcqSysInfo), 0x0, sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU));

            stTmpAcqSysInfo.stAcqSys.stFreq = *pstFreq;

            if (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID == pstSysRecord->u.stMccMncId.enMccMncSubType)
            {
                stTmpAcqSysInfo.stAcqSys.usNid  = CNAS_PRL_WILDCARD_NID;
            }
            else
            {
                stTmpAcqSysInfo.stAcqSys.usNid  = pstSysRecord->u.stMccMncId.u.stSidNid.asNid[k];
            }

            stTmpAcqSysInfo.stAcqSys.usSid  = pstSysRecord->u.stMccMncId.u.stSidNid.asSid[k];
            stTmpAcqSysInfo.enSysStatus     = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;
            stTmpAcqSysInfo.enPrefNegSys    = pstSysRecord->enPrefNegSys;
            stTmpAcqSysInfo.usLevel         = pstSysRecord->usPriLvl;

            CNAS_XSD_AppendAcqSysInfoInAcqSysList(&stTmpAcqSysInfo, pstGeoSysRecSrchList);
        }

    }

    return;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_IsChannelInChannelList
 功能描述  : 判定指定频点是否在频点列表止呕能够
 输入参数  : pstChannel-----指定的扫描频点信息
             usChanListNum---频点列表个数
             pstChanList----------频点扫描列表信表
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_TRUE :在频点列表里
                        VOS_FALSE:不在频点列表
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月18日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
/*lint -e429*/
VOS_UINT32 CNAS_XSD_IsChannelInChannelList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChannel,
    VOS_UINT16                          usChanListNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChanList
)
{
    VOS_UINT16                          i;

    for (i = 0; i < usChanListNum; i++)
    {
        /* 不添加重复频点 */
        if ((pstChannel->enBandClass == pstChanList[i].enBandClass)
         && (pstChannel->usChannel   == pstChanList[i].usChannel))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*lint +e429*/

/*****************************************************************************
 函 数 名  : CNAS_XSD_MoveFreqChantoEndOfChanList
 功能描述  : The channel over which origination failed shall be placed last in
             the channels list.

 输入参数  : pstSysInfo      -- system information
             pstScanChanList -- scan list
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月21日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_MoveFreqChantoEndOfChanList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    VOS_UINT16                          i;

    for (i = 0; i < pstScanChanList->usTotalNum; i++)
    {
        if ((pstSysInfo->stFreq.usChannel   == pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel)
         && (pstSysInfo->stFreq.enBandClass == pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass))
        {
            /* if last freq is failed freq  */
            if (i == pstScanChanList->usTotalNum - 1)
            {
                return;
            }

            /* if fail freq is not last in scan list */
            if (i != pstScanChanList->usTotalNum - 1)
            {
                NAS_MEM_MOVE_S(&pstScanChanList->pstScanChanInfo[i],
                               (pstScanChanList->usTotalNum - i) * sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU),
                               &pstScanChanList->pstScanChanInfo[i+1],
                               (pstScanChanList->usTotalNum - i - 1) * sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

                pstScanChanList->pstScanChanInfo[pstScanChanList->usTotalNum - 1].stFreqChan = pstSysInfo->stFreq;

                return;
            }
        }
    }

    /* the fail req is not found */
    pstScanChanList->pstScanChanInfo[pstScanChanList->usTotalNum].stFreqChan = pstSysInfo->stFreq;

    pstScanChanList->pstScanChanInfo[pstScanChanList->usTotalNum].enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    pstScanChanList->usTotalNum++;

    return;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_CalculateSystemLostMaxScanChanListSize
 功能描述  : 计算丢网场景下重复搜索策略时最大的频点数
 输入参数  : VOS_UINT16                         *pstMaxScanListSize
 输出参数  : VOS_UINT16                         *pstMaxScanListSize
 返 回 值  : 无
 调用函数  :
 被调函数  :

  1.日    期   : 2015年1月5日
    作    者   : c00299063
    修改内容   : 新建

*****************************************************************************/
VOS_VOID CNAS_XSD_CalculateSystemLostMaxScanChanListSize(
    VOS_UINT16                         *pusMaxScanListSize
)
{
    VOS_UINT16                                              usMaxScanListSize;
    CNAS_XSD_OOC_SCAN_STRATEGY_ENUM_UINT8                   enOocScanStrategy;
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                        *pstOocScheduleInfo = VOS_NULL_PTR;

    usMaxScanListSize         = *pusMaxScanListSize;
    pstOocScheduleInfo        = CNAS_XSD_GetOocScheduleInfo();
    enOocScanStrategy         = pstOocScheduleInfo->stConfigInfo.enOocScanStrategy;

    switch (enOocScanStrategy)
    {
        case CNAS_XSD_OOC_SCAN_REACQ_0_1_2_3_4S:
            usMaxScanListSize *= 2;
            break;

        case CNAS_XSD_OOC_SCAN_PING_5:
            usMaxScanListSize  = (VOS_UINT16)((usMaxScanListSize / 5) * 6 + 1 + usMaxScanListSize % 5);
            break;

        case CNAS_XSD_OOC_SCAN_2_7:
            usMaxScanListSize  = (VOS_UINT16)((usMaxScanListSize / 5) * 7 + 2 + usMaxScanListSize % 5);
            break;

        case CNAS_XSD_OOC_SCAN_NORMAL:
        default:
            break;

    }

    *pusMaxScanListSize      = usMaxScanListSize;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_AllocMemoryForScanChanList
 功能描述  : 为扫描频点列表分配内存
 输入参数  : 无
 输出参数  : pstScanChanList-----频点扫描列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月21日
    作    者   : w00176964
    修改内容   : 新生成函数
 修改历史      :
  2.日    期   : 2015年1月5日
    作    者   : c00299063
    修改内容   : 增加入参，搜网场景

  3.日    期   : 2015年7月20日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
VOS_VOID CNAS_XSD_AllocMemoryForScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    VOS_UINT16                          usMaxScanListSize;

    /* 如果多轮搜网,先释放之前分配给SCAN LIST的内存 */
    if (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstScanChanList->pstScanChanInfo);

        pstScanChanList->pstScanChanInfo = VOS_NULL_PTR;
    }

    /* 按照MRU+PRL ACQ表中的记录,计算大致的频点个数 */
    usMaxScanListSize = CNAS_PRL_CalcPrlAcqRecTotalFreqNum();

    if (0 != CNAS_XSD_GetMruListNum())
    {
        usMaxScanListSize += CNAS_XSD_MAX_MRU_SYS_NUM;
    }

    /* 加上将电信常用1X 频点数量 */
    if (VOS_TRUE == CNAS_XSD_GetCdma1XCustomPrefChannels()->ucEnableFlg)
    {
        usMaxScanListSize += CNAS_XSD_GetCdma1XCustomPrefChannels()->usFreqNum;
    }

    if (CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST == enSysAcqScene)
    {
        /* 计算丢网场景下重复搜索策略时最大的频点数 */
        CNAS_XSD_CalculateSystemLostMaxScanChanListSize(&usMaxScanListSize);
    }

    /* 加上紧急呼同步成功的频点数量 */
    if (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL == enSysAcqScene)
    {
        /* 加入当前同步成功的频点数量 */
        usMaxScanListSize += (VOS_UINT16)CNAS_XSD_GetHistorySyncedSysFreqList()->ulCurNum;

        /* 加入Band0和Band10 Pref的频点数量 */
        usMaxScanListSize += CNAS_XSD_BAND0_BAND10_PREFERRED_SYSTEM_NUM;
    }

    /* PRL不可用时,出现重定向或重选场景,AS携带频点最大个数为40,此时进行保护 */
    if (usMaxScanListSize < CNAS_XSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM)
    {
        usMaxScanListSize = CNAS_XSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM;
    }

    /* 由于scan list比较大,需要先分配内存,待关机时释放内存 */
    pstScanChanList->pstScanChanInfo = (CNAS_XSD_SCAN_CHANNEL_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usMaxScanListSize);

    if (VOS_NULL_PTR == pstScanChanList->pstScanChanInfo)
    {
        return;
    }

    pstScanChanList->usCurScanIndex  = 0;
    pstScanChanList->usTotalNum      = 0;

    NAS_MEM_SET_S(pstScanChanList->pstScanChanInfo, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usMaxScanListSize, 0x0, (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usMaxScanListSize));

    pstScanChanList->usMaxScanChanSize = usMaxScanListSize;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_AllocMemoryForGeoSysRecordSrchList
 功能描述  : 为捕获系统列表分配内存
 输入参数  : usMatchedSysRecNum----------选中的GEO列表中的系统记录条数
             pstMatchedSysRecord---------选中的GEO列表中的系统记录
 输出参数  : pstAcqSysList---------------捕获系统列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月21日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2015年7月20日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_AllocMemoryForGeoSysRecordSrchList(
    VOS_UINT16                                              usMatchedSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstMatchedSysRecord,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                          usMaxAcqSysIdNum;

    /* 如果多轮搜网,先释放之前分配给acq sys LIST的内存 */
    if (VOS_NULL_PTR != pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstGeoSysRecSrchList->pstAcqSysInfo);

        pstGeoSysRecSrchList->pstAcqSysInfo = VOS_NULL_PTR;
    }

    /* 计算匹配的GEO列表中最大频点个数 */
    usMaxAcqSysIdNum = CNAS_XSD_CalcPrlSysRecListTotalFreqNum(usMatchedSysRecNum, pstMatchedSysRecord);

    /* 为当前同步到的系统频点预留一个空间 */
    usMaxAcqSysIdNum++;

    /* 根据个数分配内存 */
    pstGeoSysRecSrchList->pstAcqSysInfo = (CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU)*(usMaxAcqSysIdNum));

    /* 分配内存失败 */
    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        return;
    }

    pstGeoSysRecSrchList->usTotalNum     = 0;
    NAS_MEM_SET_S(pstGeoSysRecSrchList->pstAcqSysInfo, sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU) * (usMaxAcqSysIdNum), 0x0, sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU) * usMaxAcqSysIdNum);

    pstGeoSysRecSrchList->usMaxAcqSysSize = usMaxAcqSysIdNum;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_AllocMemoryForScanChanList_FreqLock
 功能描述  : 为扫描频点列表分配内存
 输入参数  : 无
 输出参数  : pstScanChanList-----频点扫描列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_AllocMemoryForScanChanList_FreqLock(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    /* 如果多轮搜网,先释放之前分配给SCAN LIST的内存 */
    if (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstScanChanList->pstScanChanInfo);

        pstScanChanList->pstScanChanInfo = VOS_NULL_PTR;
    }

    /* 锁频时频点只有1个 */
    pstScanChanList->pstScanChanInfo = (CNAS_XSD_SCAN_CHANNEL_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) );

    if (VOS_NULL_PTR == pstScanChanList->pstScanChanInfo)
    {
        return;
    }

    pstScanChanList->usCurScanIndex  = 0;
    pstScanChanList->usTotalNum      = 0;

    NAS_MEM_SET_S(pstScanChanList->pstScanChanInfo, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_CallReleasedWithRedir
 功能描述  : build scan channel list with SD ind with release while redirection flag is true
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create

 2.日    期   : 2015年7月20日
   作    者   : y00245242
   修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_CallReleasedWithRedir(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;
    VOS_UINT16                          i;

    /* 列表组成:历史频点 + MRU[0] */

    /* 先将pstPreSrchChanArray中的频点信息增加到pstScanChanListInfo中 */
    for (i = 0; i < usPreSrchChanNum; i++)
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[i];
        stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    /* 再将MRU[0]中的频点信息增加到pstScanChanListInfo中 */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan   = stMru0SysId.stFreq;
        stTmpScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* 添加到频点扫描列表 */
        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    /* 初始化当前需要搜索的频点索引为0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_RedirectionFail
 功能描述  : build scan channel list while redirection failed
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_RedirectionFail(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    /* according to CDG143, the list is compose of:GEO(ordered by mru) + MRU + 电信常用频点 + PRL */
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stMatchedGeoList;
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstGeoChanList = VOS_NULL_PTR;
    VOS_UINT16                          usGeoChanNum;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usMaxGeoChanNum;

    NAS_MEM_SET_S(&stMatchedGeoList, sizeof(stMatchedGeoList), 0x0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    /* 先将MRU[0]中的频点信息增加到pstScanChanListInfo中 */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        /* 从PRL系统表中查找MRU[0]中SID NID所在的GEO LIST */
        CNAS_PRL_Get1xSysGeoList(&stMru0SysId, &stMatchedGeoList);
    }

    if (0 < stMatchedGeoList.ucGeoNum)
    {
        /* calculate the max size of the geo list channel and then alloc memory */
        usMaxGeoChanNum = CNAS_PRL_CalcMatchedGeoListTotalFreqNum(&stMru0SysId, &stMatchedGeoList);

        pstGeoChanList = (CNAS_PRL_FREQENCY_CHANNEL_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * usMaxGeoChanNum);

        if (VOS_NULL_PTR == pstGeoChanList)
        {
            return;
        }

        /* 将GEO列表中每条记录的频点解析成频点列表 */
        usGeoChanNum = 0;
        ulRet = CNAS_XSD_PraseChannelInMatchedGeoList(&stMru0SysId, &stMatchedGeoList, usMaxGeoChanNum, &usGeoChanNum, pstGeoChanList);

        /* 解析成功 */
        if (VOS_TRUE == ulRet)
        {
            /* 将查找到的GEO中对应的频点列表按照MRU的顺序进行排序 */
            CNAS_XSD_SortChanListByMruList(usGeoChanNum,pstGeoChanList,CNAS_XSD_GetMruList());

            /* 将排序好的频点列表增加pstScanChanListInfo中 */
            CNAS_XSD_AddFreqChanListInScanChanList(usGeoChanNum, pstGeoChanList, pstScanChanList);
        }

        PS_MEM_FREE(UEPS_PID_XSD, pstGeoChanList);
    }

    /* 先将除MRU[0]之外中其他MRU中的频点信息增加到pstScanChanListInfo中 */
    CNAS_XSD_AddMruListExcludeMru0InScanChanList(pstScanChanList);

    /* 将电信常用1X 频点加入到pstScanChanListInfo中 */
    CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

    /* 然后将PRL中获取表的频点信息增加到pstScanChanListInfo中 */
    CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);

    /* 初始化当前需要搜索的频点索引为0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_RedirectionWithInvalidGSRDM
 功能描述  : build scan channel list while redirection failed
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_RedirectionWithInvalidGSRDM(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    /* according to CDG143, the list is compose of:GEO(ordered by mur) + MRU + PRL */

    CNAS_XSD_BuildScanChanList_RedirectionFail(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_Rescan
 功能描述  : build scan channel list with SD ind with reason reason
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_Rescan(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_ProtoMismatch
 功能描述  : build scan channel list with SD ind with protocol mismatch reason
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_ProtoMismatch(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_AccessDenied
 功能描述  : build scan channel list with SD ind with access denied reason
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_AccessDenied(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_AcctBlocked
 功能描述  : build scan channel list with SD ind with acct blocked reason
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_AcctBlocked(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_NdssOff
 功能描述  : build scan channel list with SD ind with ndss off reason
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_NdssOff(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    /* NDSS OFF scan list按照开机场景构造 */
    CNAS_XSD_BuildScanChanList_SwitchOn(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_Error
 功能描述  : build scan channel list with SD ind with error ind reason
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_Error(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_RegisRej
 功能描述  : build scan channel list with SD ind with register reject ind reason
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_RegisRej(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_RegisRejWithRedirAndRtf
 功能描述  : build scan channel list with SD ind with register reject ind reason while rediection flag is true and return_if_fail is true
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_RegisRejWithRedirAndRtf(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;

    /* add the redirection orignal system only */

    NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

    stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[0];
    stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);

    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_SysReselWithPrefPrl
 功能描述  : build scan channel list with SD ind with system reselection ind reason while the current system is in PRL and is prefered system
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_SysReselWithPrefPrl(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    /* the scan list is built like this:reslection list(delete the frequency not in PRL) + idle geo list */
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;
    VOS_UINT16                          i;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usGeoChanNum;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stMatchedGeoList;
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstGeoChanList = VOS_NULL_PTR;
    VOS_UINT16                          usMaxGeoChanNum;

    NAS_MEM_SET_S(&stMatchedGeoList, sizeof(stMatchedGeoList), 0x0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    /* first add reslection list */
    for (i = 0; i < usPreSrchChanNum; i++)
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[i];
        stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* if the channel is not in PRL acquistion table,we should not add to the scan list */
        if (VOS_TRUE == CNAS_XSD_IsChannelInPrlAcqTbl(&stTmpScanChanInfo.stFreqChan))
        {
            CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
        }
    }

    /* Second add idle geo list */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        /* 从PRL系统表中查找MRU[0]中SID NID所在的GEO LIST */
        CNAS_PRL_Get1xSysGeoList(&stMru0SysId, &stMatchedGeoList);
    }

    if (0 < stMatchedGeoList.ucGeoNum)
    {
        /* calculate the max size of the geo list channel and then alloc memory */
        usMaxGeoChanNum = CNAS_PRL_CalcMatchedGeoListTotalFreqNum(&stMru0SysId, &stMatchedGeoList);

        pstGeoChanList = (CNAS_PRL_FREQENCY_CHANNEL_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * usMaxGeoChanNum);

        if (VOS_NULL_PTR == pstGeoChanList)
        {
            return;
        }

        /* prase the channle list from the GEO list */
        usGeoChanNum = 0;
        ulRet = CNAS_XSD_PraseChannelInMatchedGeoList(&stMru0SysId, &stMatchedGeoList, usMaxGeoChanNum, &usGeoChanNum, pstGeoChanList);

        /* prase success */
        if (VOS_TRUE == ulRet)
        {
            CNAS_XSD_AddFreqChanListInScanChanList(usGeoChanNum, pstGeoChanList, pstScanChanList);
        }

        PS_MEM_FREE(UEPS_PID_XSD, pstGeoChanList);
    }

    /* initial the index */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_SysReselNotInPrlOrNeg
 功能描述  : build scan channel list with SD ind with system reselection ind reason while the current system is not in PRL or negative in PRL
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_SysReselNotInPrlOrNeg(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    /* the scan list is built like this:reslection list(delete the frequency not in PRL) */
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;
    VOS_UINT16                          i;

    for (i = 0; i < usPreSrchChanNum; i++)
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[i];
        stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* if the channel is not in PRL acquistion table,we should not add to the scan list */
        if (VOS_TRUE == CNAS_XSD_IsChannelInPrlAcqTbl(&stTmpScanChanInfo.stFreqChan))
        {
            CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_MaxAccessFailureInPrl
 功能描述  : build scan channel list with SD ind with max access failure reason while the current system is in PRL
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create

 2.日    期   : 2015年3月21日
   作    者   : c00299063
   修改内容   : DTS2015031106822

 3.日    期   : 27/1/2016
   作    者   : w00176964
   修改内容   : DTS2015120204031:SD指示max access failure,balong回原始频点时间比较慢
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_MaxAccessFailureInPrl(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{

    /* the scan list is built like this:IDLE GEO LIST + MRU + 电信常用频点 + PRL(MRU0 should be placed to the end)*/
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stMatchedGeoList;
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstGeoChanList = VOS_NULL_PTR;
    VOS_UINT16                          usGeoChanNum;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usMaxGeoChanNum;
    CNAS_PRL_1X_SYSTEM_STRU             stTmpSysId;

    PS_MEM_SET(&stTmpSysId, 0x0, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    NAS_MEM_SET_S(&stMatchedGeoList, sizeof(stMatchedGeoList), 0x0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    /* 先将MRU[0]中的频点信息增加到pstScanChanListInfo中 */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        /* 从PRL系统表中查找MRU[0]中SID NID所在的GEO LIST */
        CNAS_PRL_Get1xSysGeoList(&stMru0SysId, &stMatchedGeoList);
    }

    if (0 < stMatchedGeoList.ucGeoNum)
    {
        /* calculate the max size of the geo list channel and then alloc memory */
        usMaxGeoChanNum = CNAS_PRL_CalcMatchedGeoListTotalFreqNum(&stMru0SysId, &stMatchedGeoList);

        pstGeoChanList = (CNAS_PRL_FREQENCY_CHANNEL_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * usMaxGeoChanNum);
        if (VOS_NULL_PTR == pstGeoChanList)
        {
            return;
        }

        /* 将GEO列表中每条记录的频点解析成频点列表 */
        usGeoChanNum = 0;
        ulRet        = CNAS_XSD_PraseChannelInMatchedGeoList(&stMru0SysId, &stMatchedGeoList, usMaxGeoChanNum, &usGeoChanNum, pstGeoChanList);

        /* 解析成功 */
        if (VOS_TRUE == ulRet)
        {
            CNAS_XSD_AddFreqChanListInScanChanList(usGeoChanNum, pstGeoChanList, pstScanChanList);

            /* 将MRU中的频点信息增加到pstScanChanListInfo中 */
            CNAS_XSD_AddMruListInScanChanList(pstScanChanList);

            /* 将电信常用1X 频点加入到pstScanChanListInfo中 */
            CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

            /* 然后将PRL中获取表的频点信息增加到pstScanChanListInfo中 */
            CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);

            /* place the mru0 freq last in the channels list */
            CNAS_XSD_MoveFreqChantoEndOfChanList(&stMru0SysId, pstScanChanList);

            if (VOS_NULL_PTR != pstPreSrchChanArray)
            {
                stTmpSysId.stFreq = pstPreSrchChanArray[0];

                /* 将SD携带的MAP频点放在列表最后面 */
                CNAS_XSD_MoveFreqChantoEndOfChanList(&stTmpSysId, pstScanChanList);
            }
        }

        PS_MEM_FREE(UEPS_PID_XSD, pstGeoChanList);
    }

    /* 初始化当前需要搜索的频点索引为0 */
    pstScanChanList->usCurScanIndex = 0;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_MaxAccessFailureNotInPrl
 功能描述  : build scan channel list with SD ind with max access failure reason while the current system is not in PRL
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create

 2.日    期   : 27/1/2016
   作    者   : w00176964
   修改内容   : DTS2015120204031:SD指示max access failure,balong回原始频点时间比较慢
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_MaxAccessFailureNotInPrl(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          usAcqChanNum;
    VOS_UINT16                          i;
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstAcqChanList = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;
    CNAS_PRL_1X_SYSTEM_STRU             stTmpSysId;

    PS_MEM_SET(&stTmpSysId, 0x0, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    /* the scan list is built like this: 电信常用频点 + prl acquisition table(ordered by mru) + del mru0 from list + mru0 */
    /* 将电信常用1X 频点加入到pstScanChanListInfo中 */
    CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

    CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);

    pstAcqChanList = (CNAS_PRL_FREQENCY_CHANNEL_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * pstScanChanList->usTotalNum);

    if (VOS_NULL_PTR == pstAcqChanList)
    {
        return;
    }

    usAcqChanNum = pstScanChanList->usTotalNum;
    for (i = 0; i < pstScanChanList->usTotalNum; i++)
    {
        pstAcqChanList[i] = pstScanChanList->pstScanChanInfo[i].stFreqChan;
    }

    /* clear the scan channel list */
    pstScanChanList->usTotalNum     = 0;
    pstScanChanList->usCurScanIndex = 0;

    CNAS_XSD_SortChanListByMruList(usAcqChanNum, pstAcqChanList, CNAS_XSD_GetMruList());

    CNAS_XSD_AddFreqChanListInScanChanList(usAcqChanNum, pstAcqChanList,pstScanChanList);

    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        /* place the mru0 freq last in the channels list */
        CNAS_XSD_MoveFreqChantoEndOfChanList(&stMru0SysId, pstScanChanList);
    }

    if (VOS_NULL_PTR != pstPreSrchChanArray)
    {
        stTmpSysId.stFreq = pstPreSrchChanArray[0];

        /* 将SD携带的MAP频点放在列表最后面 */
        CNAS_XSD_MoveFreqChantoEndOfChanList(&stTmpSysId, pstScanChanList);
    }

    PS_MEM_FREE(UEPS_PID_XSD, pstAcqChanList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_Abnormal
 功能描述  : build scan channel list with SD ind with abnormal ind reason
 输入参数  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 输出参数  : pstScanChanList---------------The scan channel list which has been built
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年12月25日
   作    者   : w00176964
   修改内容   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_Abnormal(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}



CNAS_XSD_SYSTEM_ACQUIRE_MODE_ENUM_UINT8 CNAS_XSD_GetSysAcqModeOfSpecialAcqScene(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enScanScene
)
{
    CNAS_XSD_SYSTEM_ACQUIRE_MODE_ENUM_UINT8                 enSysAcqMode;

    enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_BEST_PREF;

    if (VOS_TRUE == CNAS_XSD_GetFreqLockMode())
    {
        return CNAS_XSD_SYSTEM_ACQUIRE_MODE_SPECIFIC;
    }

    switch (enScanScene)
    {
        case CNAS_XSD_SYS_ACQ_SCENE_NDSS_OFF:
        case CNAS_XSD_SYS_ACQ_SCENE_RESCAN:
        case CNAS_XSD_SYS_ACQ_SCENE_PROTO_MISMATCH:
        case CNAS_XSD_SYS_ACQ_SCENE_ACCESS_DENINED:
        case CNAS_XSD_SYS_ACQ_SCENE_ACCT_BLOCKED:
        case CNAS_XSD_SYS_ACQ_SCENE_ERR:
        case CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON:
        case CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST:
        case CNAS_XSD_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED:
        case CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ:
        case CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_FAIL:
        case CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM:
        case CNAS_XSD_SYS_ACQ_SCENE_ABNORMAL:
        case CNAS_XSD_SYS_ACQ_SCENE_CALL_MRU0:
            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_BEST_PREF;
            break;

        case CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL:
        case CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF:

            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_ALLOWED;
            break;

        case CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF:
        case CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL:

            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_PREFERED;
            break;

        case CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG:
        case CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED_WITH_REDIR:
        case CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED:
        case CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL:
        case CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST:
        case CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED:
        case CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_POWER_ON_INIT_SEARCH:

            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_ANY;
            break;

        case CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL:

            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_NOT_LESS_PREF;
            break;

        case CNAS_XSD_SYS_ACQ_SCENE_CFREQ_LOCK:

            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_SPECIFIC;
            break;

        default:
            break;
    }

    return enSysAcqMode;
}


/*****************************************************************************
Function Name   :   CNAS_XSD_BuildScanChanList_Redirection
Description     :   Build the channel scan list with SD ind reason is redirecton
Input parameters:   pstRedirectionInfo
                    pstScanList

Output parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2014-12-26
        Author  :   m00270891
        Modify content :    Create
    2)  Date    :   2015-6-09
        Author  :   W00176964
        Modify content : DTS2015053003202:重定向过滤AS携带过来的重复频点
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_Redirection(
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirectionInfo,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList
)
{
    VOS_UINT8                           i;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;

    /* Allocate memory for the scan list */
    pstScanList->pstScanChanInfo = (CNAS_XSD_SCAN_CHANNEL_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                                   (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * pstRedirectionInfo->ucChanNum));

    if (VOS_NULL_PTR == pstScanList->pstScanChanInfo)
    {
        return;
    }

    pstScanList->usTotalNum         = 0;
    pstScanList->usCurScanIndex     = 0;
    pstScanList->usMaxScanChanSize  = pstRedirectionInfo->ucChanNum;

    NAS_MEM_SET_S(pstScanList->pstScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * pstRedirectionInfo->ucChanNum),
                  0,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * pstRedirectionInfo->ucChanNum));

    for (i = 0; i < pstRedirectionInfo->ucChanNum; i++)
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstRedirectionInfo->astChanInfo[i].stFreqChan;
        stTmpScanChanInfo.enChanStatus  = pstRedirectionInfo->astChanInfo[i].enChanStatus;

        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanList);
    }

    pstScanList->usCurScanIndex = pstRedirectionInfo->usCurScanIndex;

    CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_REDIR_SCAN_CHAN_LIST_IND, pstScanList);
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_FreqLock
 功能描述  : 构建扫描列表
 输入参数  : 无
 输出参数  : pstScanChanList-----频点扫描列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月29日
    作    者   : y00307564
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_FreqLock(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU  *pstCnasXsdCFreqLockValue;

    pstCnasXsdCFreqLockValue = CNAS_XSD_GetFreqLockAddr();

    pstScanChanList->usCurScanIndex                         = 0;
    pstScanChanList->usTotalNum                             = 1;

    pstScanChanList->pstScanChanInfo->stFreqChan.enBandClass = pstCnasXsdCFreqLockValue->usCdmaBandClass;
    pstScanChanList->pstScanChanInfo->stFreqChan.usChannel   = pstCnasXsdCFreqLockValue->usCdmaFreq;
    pstScanChanList->pstScanChanInfo->enChanStatus           = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    return;
}
/*****************************************************************************
 函 数 名  : CNAS_XSD_IsChannelInPrlAcqTbl
 功能描述  : 判定指定频点是否在PRL中
 输入参数  : pstChannel-----指定的扫描频点信息
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_TRUE :在PRL中
                        VOS_FALSE:不在PRL中
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月9日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsChannelInPrlAcqTbl(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChannel
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usAcqRecNum;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stAcqRecFreqInfo;

    usAcqRecNum = CNAS_PRL_GetPrlAcqRecordNum();

    for (i = 0; i < usAcqRecNum; i++)
    {
        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(i);

        /* 空指针进行保护，直接跳过 */
        if (VOS_NULL_PTR == pstPrlAcqRec)
        {
            continue;
        }

        /* 类型判断，HRPD频点不添加 */
        if (CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD == pstPrlAcqRec->enAcqType)
        {
            continue;
        }

        /* 如果是无效的Acq Rec， 直接跳过 */
        if (VOS_FALSE == pstPrlAcqRec->ucAcqValid)
        {
            continue;
        }

        CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stAcqRecFreqInfo);

        if (VOS_TRUE == CNAS_XSD_IsChannelInChannelList(pstChannel, (VOS_UINT16)stAcqRecFreqInfo.ulNum, &(stAcqRecFreqInfo.astFreqInfo[0])))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsAvailableSys
 功能描述  : 判定当前系统是否为available system
 输入参数  : pstCurSys-----当前系统
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_TRUE :是available system
                        VOS_FALSE:不是available system
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月9日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsAvailableSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSys
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stGeoListInfo;

    if (VOS_FALSE == CNAS_XSD_IsUeSupportedFreq(pstCurSys->stFreq))
    {
        return VOS_FALSE;
    }


    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_PRL_Get1xSysGeoList(pstCurSys, &stGeoListInfo);

    /* SID and NID is not In PRL */
    if ((VOS_FALSE == CNAS_PRL_GetPrefOnlyFlg())
     && (0         == stGeoListInfo.ucGeoNum))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_IsAcquireAvaialSysNeeded
 功能描述  : 判定是否需要捕获available system
 输入参数  : pstCurSys-----当前系统
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_TRUE :是available system
                        VOS_FALSE:不是available system
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月9日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsAcquireAvaialSysNeeded(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enScanScene
)
{
    VOS_UINT8                                               ucAvailSysNum;
    VOS_UINT8                                               ucPrefOnlyFlg;
    CNAS_XSD_SYSTEM_ACQUIRE_MODE_ENUM_UINT8                 enSysAcqMode;

    ucAvailSysNum = CNAS_XSD_GetAvailSysFreqNum();
    ucPrefOnlyFlg = CNAS_PRL_GetPrefOnlyFlg();

    enSysAcqMode = CNAS_XSD_GetSysAcqModeOfSpecialAcqScene(enScanScene);

    /* PERF_ONLY is false and available system exist,for the following acq scene,
       we have to select the avaialble system to provide service */
    if ((VOS_FALSE                                        == ucPrefOnlyFlg)
     && (0                                                != ucAvailSysNum)
     && ((CNAS_XSD_SYSTEM_ACQUIRE_MODE_BEST_PREF           == enSysAcqMode)
      || (CNAS_XSD_SYSTEM_ACQUIRE_MODE_NOT_LESS_PREF       == enSysAcqMode)
      || ((CNAS_XSD_SYSTEM_ACQUIRE_MODE_PREFERED           == enSysAcqMode)
       && (CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL == enScanScene))))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_MRU0
 功能描述  : MRU0频点搜索scan list构造
 输入参数  : usPreSrchChanNum ------------ 当前需要优先搜索的频点个数,构造时需要增加到扫描频点列表中
             pstPreSrchChanArray---------- 当前需要优先搜索的频点数组头指针,构造时需要增加到扫描频点列表中
 输出参数  : pstScanChanList---------------构造好的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年1月5日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_MRU0(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;

    /* 再将MRU[0]中的频点信息增加到pstScanChanListInfo中 */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan   = stMru0SysId.stFreq;
        stTmpScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* 添加到频点扫描列表 */
        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }


    /* 初始化当前需要搜索的频点索引为0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_EMC
 功能描述  : 紧急呼频点搜索scan list构造
 输入参数  : VOS_UINT16                          usPreSrchChanNum
             CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray
 输出参数  : pstScanChanList---------------构造好的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月07日
   作    者   : h00313353
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_EMC(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstEmcCallRedialScanChanList = VOS_NULL_PTR;
    VOS_UINT16                          i;

    pstEmcCallRedialScanChanList = CNAS_XSD_GetEmcCallRedialScanChanListAddr();

    CNAS_XSD_UpdateScanChanList(pstScanChanList, pstEmcCallRedialScanChanList);

    /* if the call redial channel list has been synced finished,we should reset
       the index and the channle status. */
    if (pstScanChanList->usCurScanIndex >= pstScanChanList->usTotalNum - 1)
    {
        for (i = 0; i < pstScanChanList->usTotalNum; i++)
        {
            pstScanChanList->pstScanChanInfo[i].enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;
        }

        pstScanChanList->usCurScanIndex = 0;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_CALLBACK
 功能描述  : 紧急呼频点搜索scan list构造
 输入参数  : VOS_UINT16                          usPreSrchChanNum
             CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray
 输出参数  : pstScanChanList---------------构造好的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月07日
   作    者   : h00313353
   修改内容   : 新生成函数

 2.日    期   : 2016年1月27日
   作    者   : h00313353
   修改内容   : DTS2015091603440
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_CALLBACK(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;
    CNAS_PRL_1X_SYSTEM_STRU            *pstCallBackSysId    = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /***********************************************************************************************
     * 1. 添加紧急呼叫建立的系统频点
     **********************************************************************************************/

    pstCallBackSysId                    = CNAS_XSD_GetEmcCallOriginalSys();
    NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x00, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

    stTmpScanChanInfo.stFreqChan   = pstCallBackSysId->stFreq;
    stTmpScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    /* 添加到频点扫描列表 */
    CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);

    /***********************************************************************************************
     * 2. 添加异频临区的频点
     **********************************************************************************************/
    /* 先将pstPreSrchChanArray中的频点信息增加到pstScanChanListInfo中 */
    for (i = 0; i < usPreSrchChanNum; i++)
    {
        PS_MEM_SET(&stTmpScanChanInfo, 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[i];
        stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    /* 初始化当前需要搜索的频点索引为0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateSyncSuccChanStatus
 功能描述  : 更新扫描成功的频点状态
 输入参数  : VOS_UINT16                          usBeginScanListIndex
             CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChannel
             CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
 输出参数  : 无
 返 回 值  : VOS_UINT16 -- 返回当前刷新的频点在scan list中的索引
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月14日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年9月8日
    作    者   : y00245242
    修改内容   : DTS2015090601618
*****************************************************************************/
VOS_UINT16 CNAS_XSD_UpdateSyncSuccChanStatus(
    VOS_UINT16                          usBeginScanListIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChannel,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    return CNAS_XSD_UpdateChanStatusInScanChanList(usBeginScanListIndex,
                                                   pstChannel,
                                                   CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_EXIST,
                                                   pstScanChanList);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateSyncFailChanStatus
 功能描述  : 更新扫描失败的频点状态
 输入参数  : usBeginScanListIndex ------------ 开始搜索频点的index
             usSyncFailChanNum ------------------同步失败的频点个数
             pstSyncFailChanList ------------ 同步失败的频点列表
             pstScanChanList -----------------当前的频点扫描列表
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年8月14日
   作    者   : w00176964
   修改内容   : 新生成函数

 2.日    期   : 2015年7月9日
   作    者   : y00245242
   修改内容   : iteration 17开发

 3.日    期   : 2015年9月8日
   作    者   : y00245242
   修改内容   : DTS2015090601618
*****************************************************************************/
VOS_UINT16 CNAS_XSD_UpdateSyncFailChanStatus(
    VOS_UINT16                          usBeginScanListIndex,
    VOS_UINT16                          usSyncFailChanNum,
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU    *pstSyncFailChanList,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stTmpChan;
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enChanStatus;
    VOS_UINT16                                              i;
    VOS_UINT16                                              usCurFreqIndex;

    usCurFreqIndex = usBeginScanListIndex;

    for (i = 0; i < usSyncFailChanNum; i++)
    {
        stTmpChan.enBandClass = pstSyncFailChanList[i].stFreq.usBandClass;
        stTmpChan.usChannel   = pstSyncFailChanList[i].stFreq.usChannel;

        enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST;

        usCurFreqIndex = CNAS_XSD_UpdateChanStatusInScanChanList(usBeginScanListIndex,
                                                                 &stTmpChan,
                                                                 enChanStatus,
                                                                 pstScanChanList);
    }

    /* 返回最后一个刷新的频点在scan list中的索引 */
    return usCurFreqIndex;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateGeoListSrchStatus
 功能描述  : 更新GEO list搜索状态
 输入参数  : pstGeoListInfo -- match的GEO list信息

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateGeoListSrchStatus(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    VOS_UINT16                                              usGeoSrchStatus
)
{
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoListSrchInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    pstGeoListSrchInfo = CNAS_XSD_GetGeoSrchListInfoAddr();

    if (VOS_NULL_PTR == pstGeoListSrchInfo->pstGeoSrchInfo)
    {
        NAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_UpdateGeoListSrchStatus: GEO LIST search information is NULL!");
        return;
    }

    /* 在GEO搜索列表中查找当前GEO，并设置对应的GEO状态为已搜索 */
    for (i = 0; i < pstGeoListInfo->ucGeoNum; i++)
    {
        for (j = 0; j < pstGeoListSrchInfo->usGeoNum; j++)
        {
            if (pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex == pstGeoListSrchInfo->pstGeoSrchInfo[j].usGeoBeginIndex)
            {
                pstGeoListSrchInfo->pstGeoSrchInfo[j].usGeoSrchStatus = usGeoSrchStatus;

                break;
            }
        }
    }

    /* log GEO list搜索状态 */
    CNAS_XSD_LogGeoListSrchStatus(pstGeoListSrchInfo);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateGeoSysRecordListInfoAccordingToScanChanList
 功能描述  : 根据scan chan list更新GEO系统记录搜索
 输入参数  : pstGeoSysRecSrchList -- GEO系统记录搜索列表

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateGeoSysRecordListInfoAccordingToScanChanList(
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enSysStatus;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        return;
    }

    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++)
    {
        if (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST == pstGeoSysRecSrchList->pstAcqSysInfo[i].enSysStatus)
        {
            continue;
        }

        pstFreq = &pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.stFreq;

        /* check当前GEO系统记录搜索列表中的频点在scan list中的状态 */
        enSysStatus = CNAS_XSD_GetScanChanStatusInScanChanList(pstFreq, CNAS_XSD_GetScanChanListAddr());

        if (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST != enSysStatus)
        {
            /* 刷新当前搜索level */
            pstGeoSysRecSrchList->usCurSrchLevel = pstGeoSysRecSrchList->pstAcqSysInfo[i].usLevel;

            return;
        }

        /* 否则，更新系统记录搜索列表中的状态为同步不存在 */
        pstGeoSysRecSrchList->pstAcqSysInfo[i].enSysStatus = CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST;

        if ((pstGeoSysRecSrchList->usTotalNum - 1) != i)
        {
            /* 更新GEO中当前搜索level为下一个系统记录的level */
            pstGeoSysRecSrchList->usCurSrchLevel = pstGeoSysRecSrchList->pstAcqSysInfo[i+1].usLevel;
        }
        else
        {
            /* 更新GEO中当前搜索level为当前的level */
            pstGeoSysRecSrchList->usCurSrchLevel = pstGeoSysRecSrchList->pstAcqSysInfo[i].usLevel;
        }
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateRedirectionFreqStatusAccordingToScanChanList
 功能描述  : 根据scan chan list更新重定向频点状态
 输入参数  : pstScanChanList -- scan chan list地址

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月2日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateRedirectionFreqStatusAccordingToScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU                         *pstRedirInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;

    /* 如果重定向标志不存在的话，不需要刷新重定向频点状态 */
    if (VOS_FALSE == CNAS_XSD_GetRedirectionFlag())
    {
        return;
    }

    pstRedirInfo = CNAS_XSD_GetRedirectionInfoAddr();

    for (i = 0; i < (VOS_UINT32)CNAS_MIN(pstScanChanList->usTotalNum, CNAS_XSD_CALL_REL_SYNC_MAX_FREQ_NUM); i++)
    {
        for (j = 0; j < pstRedirInfo->ucChanNum; j++)
        {
            if ((pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass == pstRedirInfo->astChanInfo[j].stFreqChan.enBandClass)
             && (pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel   == pstRedirInfo->astChanInfo[j].stFreqChan.usChannel))
            {
                pstRedirInfo->astChanInfo[j].enChanStatus = pstScanChanList->pstScanChanInfo[i].enChanStatus;
            }
        }
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsOocSceneAndRepeatMru0FreqSrchExist
 功能描述  : check当前是否是OOC场景且重复MRU0频点搜索存在
 输入参数  : pstMru0SysId -- MRU0频点信息

 输出参数  : 无

 返 回 值  : VOS_TRUE  -- 当前是OOC场景且MRU0频点存在
             VOS_FALSE -- 不是OOC场景且MRU0频点存在
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月07日
   作    者   : y00245242
   修改内容   : DTS2015090601618
*****************************************************************************/
VOS_UINT32  CNAS_XSD_IsOocSceneAndRepeatMru0FreqSrchExist(
    CNAS_PRL_1X_SYSTEM_STRU            *pstMru0SysId
)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;

    pstOocScheduleInfo = CNAS_XSD_GetOocScheduleInfo();

    /* 如果不是OOC场景，直接返回FALSE */
    if (CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST != CNAS_XSD_GetCurSysAcqScene_SysAcq())
    {
        return VOS_FALSE;
    }

    /* 如果当前没有启动MRU0重复频点插入策略，则返回FAALSE */
    if ((CNAS_XSD_OOC_SCAN_NORMAL == pstOocScheduleInfo->stConfigInfo.enOocScanStrategy)
     || (CNAS_XSD_OOC_SCAN_BUTT   == pstOocScheduleInfo->stConfigInfo.enOocScanStrategy))
    {
        return VOS_FALSE;
    }

    /* 如果无MRU0频点，返回VOS_FALSE */
    if (VOS_FALSE == CNAS_XSD_GetMru0SysId(pstMru0SysId))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_IsMru0FreqInOocScene
 功能描述  : 检查当前频点是否是MRU0频点
 输入参数  : pstFreqChan -- 频点信息指针

 输出参数  : 无

 返 回 值  : VOS_TRUE  -- 是MRU0频点
             VOS_FALSE -- 不是MRU0频点
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月07日
   作    者   : y00245242
   修改内容   : DTS2015090601618
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsMru0FreqInOocScene(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqChan
)
{
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;

    if (VOS_FALSE == CNAS_XSD_IsOocSceneAndRepeatMru0FreqSrchExist(&stMru0SysId))
    {
        return VOS_FALSE;
    }

    if ((stMru0SysId.stFreq.enBandClass == pstFreqChan->enBandClass)
     && (stMru0SysId.stFreq.usChannel   == pstFreqChan->usChannel))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList
 功能描述  : 更新scan list中从开始到当前索引指定的频点状态
 输入参数  : enChanStatus       -- 频点状态
             usCurScanChanIndex -- 当前频点索引
             pstFreqChan        -- 频点信息地址
             pstScanChanList    -- scan chan list信息地址

 输出参数  : 无

 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月07日
   作    者   : y00245242
   修改内容   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList(
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enChanStatus,
    VOS_UINT16                                              usCurScanChanIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqChan,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    VOS_UINT32                          i;

    for (i = 0; i < usCurScanChanIndex; i++)
    {
        if ((pstFreqChan->enBandClass == pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass)
         && (pstFreqChan->usChannel   == pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel))
        {
            pstScanChanList->pstScanChanInfo[i].enChanStatus = enChanStatus;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateNoSyncedOrSyncSuccScanChanInScanChanList
 功能描述  : 更新scan list中未同步的或同步成功的频点状态
 输入参数  : enChanStatus       -- 频点状态
             usCurScanChanIndex -- 当前频点索引
             pstFreqChan        -- 频点信息地址
             pstScanChanList    -- scan chan list信息地址

 输出参数  : 无

 返 回 值  : VOS_UINT16 -- 当前刷新的频点索引

 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月07日
   作    者   : y00245242
   修改内容   : DTS2015090601618
*****************************************************************************/
VOS_UINT16 CNAS_XSD_UpdateNoSyncedOrSyncSuccScanChanInScanChanList(
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enChanStatus,
    VOS_UINT16                                              usCurScanIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqChan,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    VOS_UINT16                          i;

    for (i = usCurScanIndex; i < pstScanChanList->usTotalNum; i++)
    {
        /* 跳过频点状态为搜索不存在的频点状态 */
        if (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST == pstScanChanList->pstScanChanInfo[i].enChanStatus)
        {
            continue;
        }

        if ((pstFreqChan->enBandClass == pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass)
         && (pstFreqChan->usChannel   == pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel))
        {
            pstScanChanList->pstScanChanInfo[i].enChanStatus = enChanStatus;

            return i;
        }
    }

    /* 如果没有找到，返回当前搜索索引 */

    return usCurScanIndex;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildEmcRedialMruList
 功能描述  : 记录当前MRU LIST，用于紧急呼叫重拨计数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildEmcRedialMruList()
{
    CNAS_XSD_MRU_LIST_STRU                                 *pstMruList            = VOS_NULL_PTR;
    CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU                   *pstEmcRedialSysAcqCfg = VOS_NULL_PTR;

    pstMruList            = CNAS_XSD_GetMruList();
    pstEmcRedialSysAcqCfg = CNAS_XSD_GetEmcRedialSysAcqCfgInfo();

    NAS_MEM_CPY_S(&(pstEmcRedialSysAcqCfg->stEmcRedialMruList),
                  sizeof(pstEmcRedialSysAcqCfg->stEmcRedialMruList),
                  pstMruList,
                  sizeof(CNAS_XSD_MRU_LIST_STRU));

    return;

}
/*****************************************************************************
 函 数 名  : CNAS_XSD_ClearEmcRedialSysAcqCount
 功能描述  : 清空紧急呼重拨搜网计数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_ClearEmcRedialSysAcqCfgInfo()
{
    CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU                   *pstEmcRedialSysAcqCfg = VOS_NULL_PTR;

    pstEmcRedialSysAcqCfg = CNAS_XSD_GetEmcRedialSysAcqCfgInfo();

    pstEmcRedialSysAcqCfg->ucRedialCount     = 0;

    NAS_MEM_SET_S(&(pstEmcRedialSysAcqCfg->stLastCampedSys), sizeof(pstEmcRedialSysAcqCfg->stLastCampedSys), 0, sizeof(CNAS_PRL_1X_SYSTEM_STRU));
    NAS_MEM_SET_S(&(pstEmcRedialSysAcqCfg->stEmcRedialMruList), sizeof(pstEmcRedialSysAcqCfg->stEmcRedialMruList), 0, sizeof(CNAS_XSD_MRU_LIST_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCurSysIndexOfEmcRedialMruList
 功能描述  : 保存当前系统在mru列表中的索引
 输入参数  : CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo
 输出参数  : VOS_UINT8                                              *pucindex
 返 回 值  : VOS_TRUE      获取索引成功
             VOS_FALSE     获取索引失败，系统不在MruList表中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetCurSysIndexOfEmcRedialMruList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    VOS_UINT32                                             *pulIndex
)
{
    CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU                   *pstEmcRedialSysAcqCfg = VOS_NULL_PTR;
    VOS_UINT32                                              i;

   *pulIndex = 0;

    pstEmcRedialSysAcqCfg = CNAS_XSD_GetEmcRedialSysAcqCfgInfo();

    for (i = 0; i < pstEmcRedialSysAcqCfg->stEmcRedialMruList.ucSysNum; i++)
    {
        if ((pstSysInfo->usSid              == pstEmcRedialSysAcqCfg->stEmcRedialMruList.astSystem[i].usSid)
         && (pstSysInfo->usNid              == pstEmcRedialSysAcqCfg->stEmcRedialMruList.astSystem[i].usNid)
         && (pstSysInfo->stFreq.enBandClass == pstEmcRedialSysAcqCfg->stEmcRedialMruList.astSystem[i].stFreq.enBandClass)
         && (pstSysInfo->stFreq.usChannel   == pstEmcRedialSysAcqCfg->stEmcRedialMruList.astSystem[i].stFreq.usChannel))
        {
           *pulIndex = i;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildScanChanList_CallReleaseSystemLost
 功能描述  : 丢网场景下扫描频点列表构造
 输入参数  : usPreSrchChanNum ------------ 当前需要优先搜索的频点个数,构造时需要增加到扫描频点列表中
             pstPreSrchChanArray---------- 当前需要优先搜索的频点数组头指针,构造时需要增加到扫描频点列表中
 输出参数  : pstScanChanList---------------构造好的频点扫描列表
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年12月21日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_CallReleaseSystemLost(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru0SysId;
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru1SysId;

    /*不增加重复频点的条件构建频点列表 */
    CNAS_XSD_BuildNormalSystemLostScanChanlist(pstScanChanList);

    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        CNAS_XSD_RemoveSpecialFreqFromScanList(&(stMru0SysId.stFreq), pstScanChanList);
    }

    if (VOS_TRUE == CNAS_XSD_GetMru1SysId(&stMru1SysId))
    {
        CNAS_XSD_RemoveSpecialFreqFromScanList(&(stMru1SysId.stFreq), pstScanChanList);
    }

    return;
}


#endif

/*lint -restore*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



