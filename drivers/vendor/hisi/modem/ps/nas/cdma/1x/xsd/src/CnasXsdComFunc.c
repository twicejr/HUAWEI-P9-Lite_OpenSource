/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdComFunc.c
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年7月14日
  最近修改   :
  功能描述   : XSD模块公用函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月14日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "CnasTimerMgmt.h"
#include  "CnasXsdComFunc.h"
#include  "CnasMntn.h"
#include  "CnasPrlApi.h"
#include  "CnasXsdCtx.h"
#include  "CnasXsdMntn.h"

#include "cas_1x_idlectrl_proc_nas_pif.h"
#include "xsd_mscc_pif.h"
#include "xsd_xreg_pif.h"
#include "CnasPrlParse.h"
#include "CnasXsdSndXreg.h"
#include "CnasXsdSndMscc.h"
#include "CnasXsdSysAcqStrategy.h"

#include  "CnasXsdSndInternalMsg.h"
#include  "CnasXsdFsmMain.h"
#include  "CnasXsdFsmMainTbl.h"

#include "CnasXsdSndCas.h"
#include "Nas_Mem.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_COM_FUNC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

CNAS_XSD_CHANNEL_SUPPORTED_IN_BANDCLASS_TBL_STRU            g_aucChannelSupportedInBandClassTbl[CNAS_PRL_BAND_CLASS_TYPE_MAX] =
{
    {CNAS_PRL_BAND_CLASS_TYPE_0,                            CNAS_XSD_IsUeSupportedChannel_BandClass_0},
    {CNAS_PRL_BAND_CLASS_TYPE_1,                            CNAS_XSD_IsUeSupportedChannel_BandClass_1},
    {CNAS_PRL_BAND_CLASS_TYPE_2,                            CNAS_XSD_IsUeSupportedChannel_BandClass_2},
    {CNAS_PRL_BAND_CLASS_TYPE_3,                            CNAS_XSD_IsUeSupportedChannel_BandClass_3},
    {CNAS_PRL_BAND_CLASS_TYPE_4,                            CNAS_XSD_IsUeSupportedChannel_BandClass_4},
    {CNAS_PRL_BAND_CLASS_TYPE_5,                            CNAS_XSD_IsUeSupportedChannel_BandClass_5},
    {CNAS_PRL_BAND_CLASS_TYPE_6,                            CNAS_XSD_IsUeSupportedChannel_BandClass_6},
    {CNAS_PRL_BAND_CLASS_TYPE_7,                            CNAS_XSD_IsUeSupportedChannel_BandClass_7},
    {CNAS_PRL_BAND_CLASS_TYPE_8,                            CNAS_XSD_IsUeSupportedChannel_BandClass_8},
    {CNAS_PRL_BAND_CLASS_TYPE_9,                            CNAS_XSD_IsUeSupportedChannel_BandClass_9},
    {CNAS_PRL_BAND_CLASS_TYPE_10,                           CNAS_XSD_IsUeSupportedChannel_BandClass_10},
    {CNAS_PRL_BAND_CLASS_TYPE_11,                           CNAS_XSD_IsUeSupportedChannel_BandClass_11},
    {CNAS_PRL_BAND_CLASS_TYPE_12,                           CNAS_XSD_IsUeSupportedChannel_BandClass_12},
    {CNAS_PRL_BAND_CLASS_TYPE_13,                           CNAS_XSD_IsUeSupportedChannel_BandClass_13},
    {CNAS_PRL_BAND_CLASS_TYPE_14,                           CNAS_XSD_IsUeSupportedChannel_BandClass_14},
    {CNAS_PRL_BAND_CLASS_TYPE_15,                           CNAS_XSD_IsUeSupportedChannel_BandClass_15}
};


#ifdef DMT
VOS_UINT32                              g_ulCurSlice = 0;
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_StartTimer
 功能描述  : XSD模块封装的启动定时器函数
 输入参数  : CNAS_XSD_TIMER_ID_ENUM_UINT32       enTimerId,
             VOS_UINT32                          ulTimerLen
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_StartTimer(
    CNAS_XSD_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulTimerLen
)
{
    CNAS_TIMER_INFO_STRU                stTimerInfo;

    if (0 == ulTimerLen)
    {
        CNAS_WARNING_LOG1(UEPS_PID_XSD, "CNAS_XSD_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return ;
    }

    /* 当前XSD的定时器，ulParam暂时用不到，取值为0，ulTimerPrecision均是
       VOS_TIMER_NO_PRECISION，后续如果需要根据TimerId来做不同设定时，再
       增加相关的封装函数 */
    NAS_MEM_SET_S(&stTimerInfo, sizeof(stTimerInfo), 0, sizeof(CNAS_TIMER_INFO_STRU));
    stTimerInfo.ulTimerId               = enTimerId;
    stTimerInfo.ulTimerLen              = ulTimerLen;
    stTimerInfo.ulParam                 = 0;
    stTimerInfo.ulTimerPrecision        = VOS_TIMER_PRECISION_0;

    CNAS_StartTimer(UEPS_PID_XSD, &stTimerInfo);


}

/*****************************************************************************
 函 数 名  : CNAS_XSD_StopTimer
 功能描述  : XSD模块封装的停止定时器函数
 输入参数  : CNAS_XSD_TIMER_ID_ENUM_UINT32       enTimerId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月14日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_StopTimer(
    CNAS_XSD_TIMER_ID_ENUM_UINT32       enTimerId
)
{
    /* XSD模块不要ulParam，因此在调用CNAS_StopTimer的时候，ulParam值为0*/
    CNAS_StopTimer(UEPS_PID_XSD, enTimerId, 0);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetAvoidTimerLen
 功能描述  : 获取avoid timer时长
 输入参数  : enReason -- avoid原因值
             VOS_UINT8                           ucAvoidTimes
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2015年11月12日
    作    者   : c00299063
    修改内容   : avoid timer时长可变
*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetAvoidTimerLen(
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enReason,
    VOS_UINT16                          usAvoidTimes
)
{

    CNAS_XSD_AVOID_SCHEDULE_INFO_STRU  *pstAvoidScheduleInfo = VOS_NULL_PTR;

    if (enReason < CNAS_XSD_AVOID_REASON_MAX)
    {
        pstAvoidScheduleInfo = CNAS_XSD_GetAvoidScheduInfoAddr();

        if (usAvoidTimes < CNAS_XSD_AVOID_MAX_PHASE_NUM)
        {
           return pstAvoidScheduleInfo->aucAvoidTimerLen[enReason][usAvoidTimes];
        }

        /*次数超过存储定时器时长数组的最大长度，取数组中最后一个数据*/
        return pstAvoidScheduleInfo->aucAvoidTimerLen[enReason][CNAS_XSD_AVOID_MAX_PHASE_NUM - 1];


    }

    return 0;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdataAvoidListInfo
 功能描述  : 添加频点信息进avoid频点列表
 输入参数  : pstFreq        -- avoid频点
             ulExpiredSlice -- 到期slice

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月14日
    作    者   : y00245242
    修改内容   : 新生成函数
 修改历史      :
  2.日    期   : 2015年11月12日
    作    者   : c00299063
    修改内容   : 增加记录加入avoid频点的次数
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdataAvoidListInfo(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;
    CNAS_XSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucAvoidTimes;
    VOS_UINT16                          usTimerLen;

    ucAvoidTimes = CNAS_XSD_GetAvoidTimesOfAvoidFreq(pstFreq, enAvoidReason);

    /* 获取定时器时长 */
    usTimerLen  = CNAS_XSD_GetAvoidTimerLen(enAvoidReason, ucAvoidTimes);

    if (0 == usTimerLen)
    {
        return;
    }

    pstAvoidFreqList = CNAS_XSD_GetAvoidFreqListAddr();

    ucIndex = 0;

    if (VOS_TRUE == CNAS_XSD_GetAvoidFreqIndexOfAvoidlist(pstFreq, &ucIndex))
    {
        pstAvoidFreqInfo = &(pstAvoidFreqList->astAvoidFreqInfo[ucIndex]);
    }
    else
    {
        if (pstAvoidFreqList->ucAvoidFreqNum < CNAS_XSD_MAX_AVOID_FREQ_NUM)
        {
            pstAvoidFreqInfo = &(pstAvoidFreqList->astAvoidFreqInfo[pstAvoidFreqList->ucAvoidFreqNum]);

            pstAvoidFreqList->ucAvoidFreqNum++;
        }
    }

    if (VOS_NULL_PTR == pstAvoidFreqInfo)
    {
        return;
    }

    /* 更新频点与到期slice进avoid频点列表 */
    pstAvoidFreqInfo->stAvoidFreq.enBandClass = pstFreq->enBandClass;
    pstAvoidFreqInfo->stAvoidFreq.usChannel   = pstFreq->usChannel;
    pstAvoidFreqInfo->ulStartSlice            = CNAS_XSD_GetSystemSlice();
    pstAvoidFreqInfo->ulExpiredSliceNum       = CNAS_XSD_GetSystemSliceNumOfOneSecond() * usTimerLen;
    pstAvoidFreqInfo->ucAvoidFlag             = VOS_TRUE;


    if (pstAvoidFreqInfo->aucAvoidTimes[enAvoidReason] < CNAS_XSD_AVOID_MAX_PHASE_NUM)
    {
        pstAvoidFreqInfo->aucAvoidTimes[enAvoidReason]++;
    }

    return;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_DeleteAcqSuccFreqOfAvoidList
 功能描述  : 从avoid列表中删除频点信息
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月16日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_DeleteAcqSuccFreqOfAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
)
{

    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstLastSyncedFreq = VOS_NULL_PTR;

    pstLastSyncedFreq = CNAS_XSD_GetLastSyncedFreq();

    CNAS_XSD_DeleteUsableFreqFormAvoidList(pstFreq);

    /*如果系统消息和上次同步成功的频点不相同，hash或者切换场景 */
    if ((pstLastSyncedFreq->enBandClass != pstFreq->enBandClass)
     || (pstLastSyncedFreq->usChannel   != pstFreq->usChannel))
    {
        CNAS_XSD_DeleteUsableFreqFormAvoidList(pstLastSyncedFreq);
    }

    return;

}


/*****************************************************************************
 函 数 名  : IsExistAvoidFlagInAvoidlist
 功能描述  : avoid list 中是否有的频点还未解禁
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月16日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsExistAvoidFlagInAvoidlist()
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstAvoidFreqList    = CNAS_XSD_GetAvoidFreqListAddr();

    for (i = 0; i < CNAS_MIN(pstAvoidFreqList->ucAvoidFreqNum, CNAS_XSD_MAX_AVOID_FREQ_NUM); i++)
    {
        if (VOS_TRUE == pstAvoidFreqList->astAvoidFreqInfo[i].ucAvoidFlag)
        {
           return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ClearAccessSuccessFreqFormAvoidList
 功能描述  : 从avoid列表中删除频点信息
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月16日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_ClearAccessSuccessFreqFormAvoidList()
{
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCampedSysInfo = VOS_NULL_PTR;
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAvoidFreqList    = CNAS_XSD_GetAvoidFreqListAddr();

    ucIndex             = 0;

    pstCampedSysInfo = CNAS_XSD_GetCurCampedSysInfo();

    if (VOS_TRUE == CNAS_XSD_GetAvoidFreqIndexOfAvoidlist(&(pstCampedSysInfo->stSystem.stFreq), &ucIndex))
    {
        /*如果avoid列表中不存在禁用标记，表示没有被禁用的频点，停止定时器 */

        CNAS_XSD_ClearAvoidFreqInfoOfAvoidList(ucIndex);

        if (VOS_FALSE == CNAS_XSD_IsExistAvoidFlagInAvoidlist())
        {
            CNAS_XSD_StopTimer(TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER);
        }

        CNAS_XSD_LogAvoidFreqList(pstAvoidFreqList);
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_DeleteAvoidFreqInfoOfAvoidList
 功能描述  : 从avoid列表中删除频点信息
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月16日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ClearAvoidFreqInfoOfAvoidList(
    VOS_UINT8                           ucAvoidListIndex
)
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList    = VOS_NULL_PTR;

    pstAvoidFreqList = CNAS_XSD_GetAvoidFreqListAddr();

    if ((CNAS_XSD_MAX_AVOID_FREQ_NUM - 1) == ucAvoidListIndex)
    {
        NAS_MEM_SET_S(&(pstAvoidFreqList->astAvoidFreqInfo[ucAvoidListIndex]),
                      sizeof(CNAS_XSD_AVOID_FREQ_INFO_STRU),
                      0,
                      sizeof(CNAS_XSD_AVOID_FREQ_INFO_STRU));
    }
    else if (ucAvoidListIndex < (CNAS_XSD_MAX_AVOID_FREQ_NUM - 1))
    {
        if ((pstAvoidFreqList->ucAvoidFreqNum - 1) > ucAvoidListIndex)
        {
            NAS_MEM_MOVE_S(&(pstAvoidFreqList->astAvoidFreqInfo[ucAvoidListIndex]),
                            (pstAvoidFreqList->ucAvoidFreqNum - ucAvoidListIndex) * sizeof(CNAS_XSD_AVOID_FREQ_INFO_STRU),
                           &(pstAvoidFreqList->astAvoidFreqInfo[ucAvoidListIndex + 1]),
                            (pstAvoidFreqList->ucAvoidFreqNum - ucAvoidListIndex - 1) * sizeof(CNAS_XSD_AVOID_FREQ_INFO_STRU));
        }

        NAS_MEM_SET_S(&(pstAvoidFreqList->astAvoidFreqInfo[pstAvoidFreqList->ucAvoidFreqNum - 1]),
                      sizeof(CNAS_XSD_AVOID_FREQ_INFO_STRU),
                      0,
                      sizeof(CNAS_XSD_AVOID_FREQ_INFO_STRU));
    }
    else
    {
        return;
    }

    pstAvoidFreqList->ucAvoidFreqNum--;

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsAddSyncFailFreqInAvoidList
 功能描述  : 如果频点同步失败的时刻到加入avoid列表的时刻已经超过了解禁的时间，则不加入
 输入参数  :     CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstSyncFailFreq,
                 VOS_UINT32                          ulSyncFailSlice,
                 CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsAddSyncFailFreqInAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstSyncFailFreq,
    VOS_UINT32                          ulSyncFailSlice,
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    VOS_UINT32                          ulExpiredSliceNum;
    VOS_UINT16                          usTimerLen;
    VOS_UINT32                          ulCurrSlice;
    VOS_UINT32                          ulRunSliceNum;
    VOS_UINT8                           ucAvoidTimes;

    ucAvoidTimes = CNAS_XSD_GetAvoidTimesOfAvoidFreq(pstSyncFailFreq, enAvoidReason);

    usTimerLen  = CNAS_XSD_GetAvoidTimerLen(enAvoidReason, ucAvoidTimes);

    if (0 != usTimerLen)
    {
        /* 计算需要多少个slice到期 */
        ulExpiredSliceNum = usTimerLen * CNAS_XSD_GetSystemSliceNumOfOneSecond();

        ulCurrSlice       = CNAS_XSD_GetSystemSlice();

        ulRunSliceNum     = (ulCurrSlice - ulSyncFailSlice);

        ulRunSliceNum     = ulRunSliceNum % CNAS_XSD_MAX_SLICE_VALUE;

        if (ulRunSliceNum < ulExpiredSliceNum)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetAvoidTimesOfAvoidFreq
 功能描述  : 获取频点列表被禁止的次数
 输入参数  : CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstAvoidFreq,
             CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetAvoidTimesOfAvoidFreq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstAvoidFreq,
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCount;

    ucIndex          = 0;

    pstAvoidFreqList = CNAS_XSD_GetAvoidFreqListAddr();

    if (VOS_TRUE == CNAS_XSD_GetAvoidFreqIndexOfAvoidlist(pstAvoidFreq, &ucIndex))
    {
        ucCount = pstAvoidFreqList->astAvoidFreqInfo[ucIndex].aucAvoidTimes[enAvoidReason];

        return ucCount;
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_ClearAvoidCountFromAvoidList
 功能描述  : 清除avoid计数从avoid列表中
 输入参数  : VOS_UINT8                           ucAvoidListIndex,
             CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_ClearAvoidCountFromAvoidList(
    VOS_UINT8                           ucAvoidListIndex,
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList    = VOS_NULL_PTR;

    pstAvoidFreqList    = CNAS_XSD_GetAvoidFreqListAddr();

    pstAvoidFreqList->astAvoidFreqInfo[ucAvoidListIndex].aucAvoidTimes[enAvoidReason] = 0;

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsClearFreqInfoOfAvoidList
 功能描述  : 清除avoid计数从avoid列表中
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsClearFreqInfoOfAvoidList(
    VOS_UINT8                           ucAvoidListIndex
)
{
    VOS_UINT32                          i;
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList    = VOS_NULL_PTR;

    pstAvoidFreqList    = CNAS_XSD_GetAvoidFreqListAddr();

    for (i = 0; i < CNAS_XSD_AVOID_REASON_MAX; i++)
    {
        if (0 != pstAvoidFreqList->astAvoidFreqInfo[ucAvoidListIndex].aucAvoidTimes[i])
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason
 功能描述  : process required avoid frequency according to avoid reason
 输入参数  : enAvoidReason----avoid reason
             pstAvoidFreq ----avoid frequency
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2014年12月26日
    作    者   : w00176964
    修改内容   : CDMA Iteration 6 Modified

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstAvoidFreq
)
{
    CNAS_XSD_UpdataAvoidListInfo(pstAvoidFreq, enAvoidReason);

    /*如果avoid列表中存在禁用标记，表示存在被禁用的频点，启动定时器 */
    if (VOS_TRUE == CNAS_XSD_IsExistAvoidFlagInAvoidlist())
    {

        /* 如果avoid timer未启动，启动avoid timer定时器 */
        if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_XSD,
                                                                      TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER,
                                                                      0))
        {
            CNAS_XSD_StartTimer(TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER,
                                TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
        }
    }

    CNAS_XSD_LogAvoidFreqList(CNAS_XSD_GetAvoidFreqListAddr());
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetSystemSlice
 功能描述  : 获取系统slice
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetSystemSlice(VOS_VOID)
{
#ifdef DMT
    return g_ulCurSlice;
#else
    return VOS_GetSlice();
#endif

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetSystemSliceNumOfEverySecond
 功能描述  : 获取1秒slice的个数
 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月20日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetSystemSliceNumOfOneSecond(VOS_VOID)
{
    return VOS_GetSliceUnit();
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_TransferMsccCallTypeToXsdFormat
 功能描述  : 收到测试配置消息处理函数
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月2日
    作    者   : W00176964
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_XSD_CALL_EXIST_FLAG_ENUM_UINT8 CNAS_XSD_TransferMsccCallTypeToXsdFormat(
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8          enMsccCallType
)
{
    CNAS_XSD_CALL_EXIST_FLAG_ENUM_UINT8 enCallExistFlg;

    switch (enMsccCallType)
    {
        case NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL:
            enCallExistFlg = CNAS_XSD_EMC_VOICE_CALL_EXIST_FLAG;
            break;

        case NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_VOICE_CALL:
            enCallExistFlg = CNAS_XSD_NORMAL_VOICE_CALL_EXIST_FLAG;
            break;

        case NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_DATA_CALL:
            enCallExistFlg = CNAS_XSD_NORMAL_DATA_CALL_EXIST_FLAG;
            break;

        default:
            enCallExistFlg = CNAS_XSD_CALL_EXIST_NULL_FLAG;
            break;
    }

   return enCallExistFlg;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedFreq
 功能描述  : check the band class and chenne are supported by UE or not
 输入参数  : CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreqChan
 输出参数  : NONE
 返 回 值  : VOS_TRUE----UE support
             VOS_FALSE---UE could not support
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 26/12/2014
    作    者   : w00176964
    修改内容   : Create
  1.日    期   : 19/1/2015
    作    者   : y00307564
    修改内容   : 清PCLINT
  3.日    期   : 3/8/2015
    作    者   : c00299063
    修改内容   : 增加频点过滤
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedFreq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreqChan
)
{
    VOS_UINT32                          ulSupportedBand;
    VOS_UINT32                          i;
    pCNasXsdBandSupportChanBuildFunc    pfunBandSupportChanBuild = VOS_NULL_PTR;

    ulSupportedBand = CNAS_XSD_GetUeSupportedBandClass();

    if (0 == (ulSupportedBand & ((VOS_UINT32)1 << stFreqChan.enBandClass)))
    {
        return VOS_FALSE;
    }

    for (i = 0; i < (sizeof(g_aucChannelSupportedInBandClassTbl)/sizeof(CNAS_XSD_CHANNEL_SUPPORTED_IN_BANDCLASS_TBL_STRU)); i++)
    {
        if ((VOS_UINT32)stFreqChan.enBandClass == g_aucChannelSupportedInBandClassTbl[i].ulBandClass)
        {
            pfunBandSupportChanBuild = g_aucChannelSupportedInBandClassTbl[i].pfunBandSupportChanBuild;
            break;
        }
    }

    if (VOS_NULL_PTR == pfunBandSupportChanBuild)
    {
        return VOS_FALSE;
    }
    else
    {
        return pfunBandSupportChanBuild(stFreqChan.usChannel);
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_0
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_0(
    VOS_UINT16                          usChannel
)
{
    if (((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_799))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_991) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1323)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_1
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_1(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1199)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_2
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_2(
    VOS_UINT16                          usChannel
)
{
    if ((usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1000)
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1329) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_2047)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_3
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_3(
    VOS_UINT16                          usChannel
)
{
    if (((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_799))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_801) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1039))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1041) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1199))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1201) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1600)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_4
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_4(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_599)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_5
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_5(
    VOS_UINT16                          usChannel
)
{
    if (((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_400))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_539) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_871))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1039) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1473))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1536) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1715))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1792) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_2016)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_6
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_6(
    VOS_UINT16                          usChannel
)
{
    return CNAS_XSD_IsUeSupportedChannel_BandClass_1(usChannel);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_7
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_7(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_359)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_8
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_8(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1499)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_9
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_9(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_699)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_10
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_10(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_919)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_11
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_11(
    VOS_UINT16                          usChannel
)
{
    return CNAS_XSD_IsUeSupportedChannel_BandClass_5(usChannel);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_12
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_12(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_239)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_13
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_13(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1399)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_14
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_14(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1299)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsUeSupportedChannel_BandClass_15
 功能描述  : 判断该频点是否在移动终端所支持的传输列表当中
 输入参数  : VOS_UINT16                          usChannel
 输出参数  : 无

 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_15(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_899)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_SaveRedirectionInfo
 功能描述  : Save the redirection info from CAS
 输入参数  : pstCasRedirInfo-----the redirection info from CAS
 输出参数  : NONE
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 26/12/2014
    作    者   : w00176964
    修改内容   : Create

*****************************************************************************/
VOS_VOID CNAS_XSD_SaveRedirectionInfo(
    CNAS_CAS_1X_REDIRECTION_INFO_STRU  *pstCasRedirInfo
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstXsdRedirInfo = VOS_NULL_PTR;
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampedSys = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_ID_STRU          stSysId;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stSrcFreqInfo;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stDstFreqInfo;
    VOS_UINT8                           i;

    pstXsdRedirInfo     = CNAS_XSD_GetRedirectionInfoAddr();

    NAS_MEM_SET_S(&stSysId, sizeof(stSysId), 0x0, sizeof(stSysId));
    NAS_MEM_SET_S(&stSrcFreqInfo, sizeof(stSrcFreqInfo), 0x0, sizeof(stSrcFreqInfo));
    NAS_MEM_SET_S(&stDstFreqInfo, sizeof(stDstFreqInfo), 0x0, sizeof(stDstFreqInfo));

    stSysId.usSid = pstCasRedirInfo->usExpectedSid;
    stSysId.usNid = pstCasRedirInfo->usExpectedNid;

    for (i = 0; i < pstCasRedirInfo->ucChannelNum; i++)
    {
        stSrcFreqInfo.astFreqInfo[i].enBandClass = pstCasRedirInfo->usBandClass;
        stSrcFreqInfo.astFreqInfo[i].usChannel   = pstCasRedirInfo->ausChannelList[i];
    }
    stSrcFreqInfo.ulNum = pstCasRedirInfo->ucChannelNum;

    /* filter out negative freqs */
    CNAS_XSD_RemoveNegativeFreqs(&stSysId, &stSrcFreqInfo, &stDstFreqInfo);



    pstXsdRedirInfo->ucReturnIfFail = pstCasRedirInfo->ucReturnIfFail;
    pstXsdRedirInfo->usExpectSid    = pstCasRedirInfo->usExpectedSid;
    pstXsdRedirInfo->usExpectNid    = pstCasRedirInfo->usExpectedNid;
    pstXsdRedirInfo->ucChanNum      = pstCasRedirInfo->ucChannelNum;

    pstCurCampedSys     = CNAS_XSD_GetCurCampedSysInfo();

    CNAS_XSD_SaveRedirectionOrignalSys(&pstCurCampedSys->stSystem);

    for (i = 0; i < stDstFreqInfo.ulNum; i++)
    {
        pstXsdRedirInfo->astChanInfo[i].stFreqChan      = stDstFreqInfo.astFreqInfo[i];
        pstXsdRedirInfo->astChanInfo[i].enChanStatus    = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;
    }

    pstXsdRedirInfo->ucChanNum = (VOS_UINT8)stDstFreqInfo.ulNum;

    pstXsdRedirInfo->usCurScanIndex = 0;

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_TransformMccToBcd
 功能描述  : 转换十进制的MCC为BCD格式
 输入参数  : VOS_UINT16                          usMcc
 输出参数  : 无
 返 回 值  : VOS_UINT32

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月14日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XSD_TransformMccToBcd(
    VOS_UINT16                          usMcc
)
{
    /*转换原则:个位、十位和百位，每一位加1，如果该位值是9，加1为10，则取个位0    最后转换为BCD码*/
    /*359--> 460 -->0x00000604            */
    VOS_UINT32                          ulBcdMcc;

    if (usMcc > CNAS_XSD_MAX_MCC)
    {
        /*无效值 */
        ulBcdMcc = 0xffffffff;
    }
    else
    {
        ulBcdMcc  = 0;

        do
        {
            ulBcdMcc  = (ulBcdMcc << 8)|((usMcc % 10 + 1) % 10);
            usMcc    /= 10;
        }
        while(0 != usMcc);
    }

    return ulBcdMcc;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_TransformImsiToBcd
 功能描述  : 转换十进制的Imsi为BCD格式
 输入参数  : VOS_UINT8                           ucImsi
 输出参数  : 无
 返 回 值  : VOS_UINT16

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月14日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16 CNAS_XSD_TransformImsiToBcd(
    VOS_UINT8                           ucImsi
)
{
    /*转换原则:个位、十位，每一位加1，如果该位值是9，加1为10，则取个位0    最后转换为BCD码*/
    /*92--> 03 -->0x3000            */
    VOS_UINT16                          usBcdImsi;

    if (ucImsi > CNAS_XSD_MAX_IMSI11_12)
    {
        usBcdImsi = 0xffff;
    }
    else
    {
        usBcdImsi  = 0;

        do
        {
            usBcdImsi  = (VOS_UINT16)((usBcdImsi << 8)|((ucImsi % 10 + 1) % 10));
            ucImsi    /= 10;
        }
        while(0 != ucImsi);
    }

    return usBcdImsi;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_DeleteUsableFreqFormAvoidList
 功能描述  : 从avoid频点列表中删除可用的频点
 输入参数  : CNAS_PRL_FREQENCY_CHANNEL_STRU                          stFreq
 输出参数  : 无
 返 回 值  : VOS_VOID

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月27日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_DeleteUsableFreqFormAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
)
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList    = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAvoidFreqList    = CNAS_XSD_GetAvoidFreqListAddr();

    ucIndex             = 0;

    if (VOS_TRUE == CNAS_XSD_GetAvoidFreqIndexOfAvoidlist(pstFreq, &ucIndex))
    {

        /*删除搜网场景下的加入avoid列表的累加计数 */
        CNAS_XSD_ClearAvoidCountFromAvoidList(ucIndex, CNAS_XSD_AVOID_P_REV_MISMATCH);
        CNAS_XSD_ClearAvoidCountFromAvoidList(ucIndex, CNAS_XSD_AVOID_SID_NID_IS_REJ_BY_PRL);
        CNAS_XSD_ClearAvoidCountFromAvoidList(ucIndex, CNAS_XSD_AVOID_REDIRECTION_FAIL);
        CNAS_XSD_ClearAvoidCountFromAvoidList(ucIndex, CNAS_XSD_AVOID_REDIRECTION_WITH_INVALID_GSRDM);

        if (VOS_TRUE == CNAS_XSD_IsClearFreqInfoOfAvoidList(ucIndex))
        {

            CNAS_XSD_ClearAvoidFreqInfoOfAvoidList(ucIndex);

            /*如果avoid列表中不存在禁用标记，表示没有被禁用的频点，停止定时器 */
            if (VOS_FALSE == CNAS_XSD_IsExistAvoidFlagInAvoidlist())
            {
                CNAS_XSD_StopTimer(TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER);
            }
        }

        CNAS_XSD_LogAvoidFreqList(pstAvoidFreqList);
    }
}


/*****************************************************************************
Function Name   :   CNAS_XSD_ProcCasOhmInd
Description     :   Process the OHM Indication message received from CAS.
                    Send Notification to XREG And MMA, about the current camped system details.
Input parameters:
                    pstMsg       - pointer to OHM Indication message structure.
Outout parameters:  None
Return Value    :   VOS_TRUE

Modify History:
    1)  Date    :   2014-12-27
        Author  :   a00295761
        Modify content :    Create

    2)日    期   : 2015年1月3日
      作    者   : y00245242
      修改内容   : home SID/NID功能开发

    3).日    期   : 2015年7月9日
      作    者   : y00245242
      修改内容   : iteration 17开发
   4).日    期   :  2015年12月15日
      作    者   :  l00324781
      修改内容   :  CL_MUTIMODE_OPTIMIZE 修改
*****************************************************************************/

VOS_VOID CNAS_XSD_ProcCasOhmInd(
    CAS_CNAS_1X_OHM_IND_STRU           *pstMsg,
    VOS_UINT32                          ulIsNegSys
)
{
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU   stSysInfo;
    XSD_XREG_SYS_INFO_STRU              stXsdXregSysInfo;
    CNAS_PRL_1X_SYSTEM_STRU             stCurSysInfo;
    VOS_UINT32                          ulIsAvailSys;
    XSD_XREG_SERVICE_STATUS_ENUM_UINT32 enXsdXregSrvSta;
    CNAX_XSD_CAMPED_SYS_INFO_STRU       stCurCampedSysInfo;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8 enRoamingInd;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCardStatus;
    VOS_UINT8                           ucNoCardModeCfgFlg;

    NAS_MEM_SET_S(&stSysInfo, sizeof(stSysInfo), 0, sizeof(NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU));
    NAS_MEM_SET_S(&stXsdXregSysInfo, sizeof(stXsdXregSysInfo), 0, sizeof(XSD_XREG_SYS_INFO_STRU));
    NAS_MEM_SET_S(&stCurCampedSysInfo, sizeof(stCurCampedSysInfo), 0, sizeof(CNAX_XSD_CAMPED_SYS_INFO_STRU));

    stCurSysInfo.usSid              = pstMsg->usSid;
    stCurSysInfo.usNid              = pstMsg->usNid;
    stCurSysInfo.stFreq.enBandClass = pstMsg->usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstMsg->usFreq;

    CNAS_CCB_Set1xSysInfo(pstMsg->usSid,
                          pstMsg->usNid,
                          pstMsg->usBandClass,
                          pstMsg->usFreq);

    NAS_MEM_CPY_S(&(stCurCampedSysInfo.stSystem), sizeof(stCurCampedSysInfo.stSystem), &stCurSysInfo, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    stCurCampedSysInfo.enSysType = CNAS_XSD_SYS_TYPE_PREFERRED;

    ulIsAvailSys = CNAS_XSD_IsCurSystemInAvailSysList(&stCurSysInfo);

    CNAS_XSD_BuildXregSysInfoInd(pstMsg, &stXsdXregSysInfo);

    CNAS_XSD_BuildMsccSysInfoInd(pstMsg, &stSysInfo);

    enCardStatus       = CNAS_CCB_GetCsimCardStatus();
    ucNoCardModeCfgFlg = CNAS_XSD_GetNoCardModeCfgFlg();

    if ((VOS_TRUE                     == ulIsNegSys)
     || ((CNAS_CCB_CARD_STATUS_ABSENT == enCardStatus)
      && (VOS_FALSE                   == ucNoCardModeCfgFlg)))
    {
        enXsdXregSrvSta                 = XSD_XREG_SERVICE_STATUS_LIMITED_SERVICE;
        stSysInfo.enServiceStatus       = NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE;
        stCurCampedSysInfo.enSysType    = CNAS_XSD_SYS_TYPE_NEGATIVE;
        stCurCampedSysInfo.enSrvStatus  = CNAS_XSD_SERVICE_STATUS_LIMITED_SERVICE;
        CNAS_CCB_SetCur1XSrvStatus(CNAS_CCB_SERVICE_STATUS_LIMITED_SERVICE);
    }
    else
    {
        enXsdXregSrvSta                 = XSD_XREG_SERVICE_STATUS_NORMAL_SERVICE;
        stSysInfo.enServiceStatus       = NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE;

        enRoamingInd = CNAS_XSD_GetCurrentSystemRoamingInd(&stCurSysInfo);
        stSysInfo.ucRoamingInd          = enRoamingInd;
        stCurCampedSysInfo.ucRoamingInd = enRoamingInd;
        stCurCampedSysInfo.enSrvStatus  = CNAS_XSD_SERVICE_STATUS_NORMAL_SERVICE;
        CNAS_CCB_SetCur1XSrvStatus(CNAS_CCB_SERVICE_STATUS_NORMAL_SERVICE);
    }

    if (VOS_TRUE == ulIsAvailSys)
    {
        stCurCampedSysInfo.enSysType    = CNAS_XSD_SYS_TYPE_AVAILABLE;
    }

    if (VOS_TRUE == pstMsg->enServiceInfoIncl)
    {
        stCurCampedSysInfo.ulMcc                  = CNAS_XSD_TransformMccToBcd(pstMsg->stServiceInfo.usMcc);
        stCurCampedSysInfo.usImsi11_12            = CNAS_XSD_TransformImsiToBcd(pstMsg->stServiceInfo.ucImsi11_12);
        stSysInfo.stServiceInfo.ulMcc             = CNAS_XSD_TransformMccToBcd(pstMsg->stServiceInfo.usMcc);
        stSysInfo.stServiceInfo.usImsi11_12       = CNAS_XSD_TransformImsiToBcd(pstMsg->stServiceInfo.ucImsi11_12);

        CNAS_CCB_SetConcurrentSupportedFlag(pstMsg->stServiceInfo.ucConcurrentSupported);
    }

    stSysInfo.en1xPriClass = CNAS_XSD_GetCurrentSystemPriClass(&stCurCampedSysInfo.stSystem, MSCC_XSD_SYS_TYPE_CDMA2000_1X);
    stSysInfo.enAIPriClass = CNAS_XSD_GetCurrentSystemPriClass(&stCurCampedSysInfo.stSystem, MSCC_XSD_SYS_TYPE_CDMA2000_AI);

    stCurCampedSysInfo.ucCampOnFlag = VOS_TRUE;

    /* 给XREG模块转发ID_XSD_XREG_SYS_INFO_IND消息 */
    CNAS_XSD_SndXregSysInfoInd(enXsdXregSrvSta, &stXsdXregSysInfo);

    /* 给MSCC发送System srv Info信息 */
    CNAS_XSD_SndMsccSysSrvInfoInd(&stSysInfo);

    CNAS_XSD_SndMsccSidNidInd(stCurSysInfo.usSid, stCurSysInfo.usNid);

    CNAS_XSD_UpdateCurCampedSysInfo(&stCurCampedSysInfo);

    /* 更新协议使用版本 */
    CNAS_CCB_SetPRevInUse(pstMsg->ucPRevInUse);

    /* 如果不是negative系统，则更新MRU以及版本号 */
    if (VOS_FALSE == ulIsNegSys)
    {
        /* 如果是非negative系统，更新MRU[0] */
        CNAS_XSD_UpdateMru0(&stCurSysInfo);

        CNAS_XSD_DeleteAcqSuccFreqOfAvoidList(&(stCurSysInfo.stFreq));
    }

    /* 刷新紧急呼初始系统 */
    if (VOS_TRUE == CNAS_XSD_IsEmcCallOriginalSysExist())
    {
        CNAS_XSD_SaveEmcCallOriginalSys(&stCurSysInfo);
    }

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_UpdateReturnCauseValue
 功能描述  : 更新returnCause
 输入参数  : usSyncFailChanNum ------------------同步失败的频点个数
             pstSyncFailChanList ------------ 同步失败的频点列表
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年07月13日
   作    者   : m00312079
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateReturnCauseValue(
    VOS_UINT16                          usSyncFailChanNum,
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU    *pstSyncFailChanList
)
{
    CNAS_CAS_1X_SYS_SRCH_FAIL_REASON_ENUM_UINT16            enFailReason;
    VOS_UINT16                                              i;

    for (i = 0; i < usSyncFailChanNum; i++)
    {
        enFailReason          = pstSyncFailChanList[i].enFailReason;

        if (CNAS_CAS_1X_SYS_SRCH_SYNC_FAIL_FREQ_SRCH_FAIL == enFailReason)
        {
            CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_SYSTEM_NOT_ACQ);
        }
        else if (CNAS_CAS_1X_SYS_SRCH_SYNC_FAIL_PROTO_MISMATCH == enFailReason)
        {
            CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_PROTOCOL_MISMATCH);
        }
        else
        {
            /* Do noting */
        }
    }

    return;

}



/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCurrentSystemRoamingInd
 功能描述  : 获取当前系统的漫游指示值
 输入参数  : CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
 输出参数  : 无
 返 回 值  : CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8 -- 漫游指示值
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2015年7月2日
    作    者   : w00242748
    修改内容   : CDMA 1X Iteration 17 modified

*****************************************************************************/
CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8 CNAS_XSD_GetCurrentSystemRoamingInd(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enRoamingInd;
    VOS_UINT8                                               ucHomeSidNidFlg;

    ucHomeSidNidFlg = CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSysInfo);

    if ( (VOS_FALSE == CNAS_CCB_GetHomeSidNidDependOnPrlFlg())
      && (VOS_TRUE == ucHomeSidNidFlg) )
    {
        return (VOS_UINT8)CNAS_PRL_SYS_ROAMING_STATUS_OFF;
    }

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));
    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stGeoListInfo);

    if (0 == stGeoListInfo.ucGeoNum)
    {
        /* 无GEO，这是一个available系统，返回PRL头信息中的漫游指示 */
        return CNAS_PRL_GetPrlHeaderInfoAddr()->enDefRoamInd;
    }

    enRoamingInd = CNAS_PRL_GetRoamingIndInMatchedGeolist(pstCurSysInfo, &stGeoListInfo);

    if (VOS_TRUE == ucHomeSidNidFlg)
    {
        enRoamingInd = (VOS_UINT8)CNAS_PRL_SYS_ROAMING_STATUS_OFF;
    }

    return enRoamingInd;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RemoveNegativeFreqs
 功能描述  : 根据当前传入的系统以及频点列表,过滤negative的频点
 输入参数  : pstSysId -- 传入的系统ID
             pstSrcFreqInfo----原始的频点信息
 输出参数  : pstDstFreqInfo----过滤negative后的频点信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月15日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年7月2日
    作    者   : w00242748
    修改内容   : CDMA 1X Iteration 17 modified

*****************************************************************************/
VOS_VOID CNAS_XSD_RemoveNegativeFreqs(
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstSysId,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU    *pstSrcFreqInfo,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU    *pstDstFreqInfo
)
{
    CNAS_PRL_1X_SYSTEM_STRU             stSysInfo;
    VOS_UINT32                          i;
    VOS_UINT32                          ulIsNegSys;

    NAS_MEM_SET_S(&stSysInfo, sizeof(stSysInfo), 0x0, sizeof(stSysInfo));
    stSysInfo.usSid = pstSysId->usSid;
    stSysInfo.usNid = pstSysId->usNid;

    /* SID+NID为通配符或当前系统在home sid/nid list里则不需要考虑negative频点 */
    if ((CNAS_PRL_WILDCARD_SID == pstSysId->usSid)
     && (CNAS_PRL_WILDCARD_NID == pstSysId->usNid))
    {
        NAS_MEM_CPY_S(pstDstFreqInfo, sizeof(CNAS_PRL_ACQ_REC_FREQ_INFO_STRU), pstSrcFreqInfo, sizeof(CNAS_PRL_ACQ_REC_FREQ_INFO_STRU));

        return;
    }

    for (i = 0; i < pstSrcFreqInfo->ulNum; i++)
    {
        stSysInfo.stFreq = pstSrcFreqInfo->astFreqInfo[i];
        stSysInfo.usSid  = pstSysId->usSid;
        stSysInfo.usNid  = pstSysId->usNid;

        ulIsNegSys = CNAS_XSD_Is1xSysNegative(&stSysInfo, VOS_FALSE, 0);

        if ((VOS_TRUE  == CNAS_XSD_GetRedirectionInfoAddr()->ucIsEmcRedir)
         || (VOS_FALSE == ulIsNegSys))
        {
            pstDstFreqInfo->astFreqInfo[pstDstFreqInfo->ulNum] = pstSrcFreqInfo->astFreqInfo[i];

            (pstDstFreqInfo->ulNum)++;
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2k1xSysType
 功能描述  : 查看当前的1x系统在GEO中的匹配优先级,当前sys type为cdma2K_1X
 输入参数  : pstCurSysInfo -- 当前搜到的系统信息
             对于CDMA2000_1x的sys type,pri class是1x系统所在的优先级,即
             1X系统记录之间出现HRPD的系统,以1X系统的相对优先级为准;
             对于CDMA2000_AI的sys type,pri class是1x系统所在的绝对优先级,即
             1X系统记录之间出现更高优先级的HRPD的系统,1X系统的优先级也要递减;
 输出参数  : penMatchPrio        -----匹配的优先级
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月8日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2k1xSysType(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_1X_MATCH_PRIO_LVL_ENUM_UINT8                  *penMatchPrio
)
{
    VOS_UINT16                                              i;
    VOS_UINT8                                               ucSysPrioLvl;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;
    VOS_UINT16                                              ucMostMatchIndex;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enSysMatchLvl;
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMostMatchGeoInfo = VOS_NULL_PTR;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;

    *penMatchPrio   = CNAS_PRL_1X_MATCH_PRIO_LEVLE_NULL;
    ucSysPrioLvl    = 0;

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));
    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stGeoListInfo);

    if (0 == stGeoListInfo.ucGeoNum)
    {
        return;
    }

    /* 从GEO list中找出最匹配的GEO */
    pstMostMatchGeoInfo = CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList(pstCurSysInfo, &stGeoListInfo);

    /* 从最匹配的GEO中获取PRL表中最匹配的系统记录索引 */
    enSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstCurSysInfo, pstMostMatchGeoInfo, &ucMostMatchIndex);

    /* 不匹配 */
    if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH == enSysMatchLvl)
    {
        return;
    }

    /* 最高优先级记录直接返回 */
    if (ucMostMatchIndex == pstMostMatchGeoInfo->usGeoFirstSysRecIndex)
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_0;

        return;
    }

    for (i = (pstMostMatchGeoInfo->usGeoFirstSysRecIndex); i <= ucMostMatchIndex; i++)
    {
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(i);

        if ((VOS_NULL_PTR   == pstSysRecord)
         || (VOS_FALSE      == pstSysRecord->ucSysRecValid))
         {
            continue;
        }

        if (CNAS_PRL_RELATIVE_PRI_MORE == pstSysRecord->enPriInd)
        {
            ucSysPrioLvl++;

            /* 遇到more优先级的系统记录,PRIO递增,如果当前即为more的或HRPD的系统,优先级递减一次 */
            if ((i                              == ucMostMatchIndex)
             || (CNAS_PRL_SYS_RECORD_TYPE_HRPD  == pstSysRecord->enRecordType))
            {
                ucSysPrioLvl--;
            }
        }
    }

    if (0 == ucSysPrioLvl)
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_0;
    }
    else if (1 == ucSysPrioLvl)
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_1;
    }
    else
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_OTHER;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2kAISysType
 功能描述  : 查看当前的1x系统在GEO中的匹配优先级,当前sys type为CDMA2K_ai
 输入参数  : pstCurSysInfo -- 当前搜到的系统信息
             对于CDMA2000_1x的sys type,pri class是1x系统所在的优先级,即
             1X系统记录之间出现HRPD的系统,以1X系统的相对优先级为准;
             对于CDMA2000_AI的sys type,pri class是1x系统所在的绝对优先级,即
             1X系统记录之间出现更高优先级的HRPD的系统,1X系统的优先级也要递减;
 输出参数  : penMatchPrio        -----匹配的优先级
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月8日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2kAISysType(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_1X_MATCH_PRIO_LVL_ENUM_UINT8                  *penMatchPrio
)
{
    VOS_UINT16                                              i;
    VOS_UINT8                                               ucSysPrioLvl;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;
    VOS_UINT16                                              usMostMatchIndex;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enSysMatchLvl;
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMostMatchGeoInfo = VOS_NULL_PTR;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;

    *penMatchPrio   = CNAS_PRL_1X_MATCH_PRIO_LEVLE_NULL;
    ucSysPrioLvl    = 0;

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));
    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stGeoListInfo);

    if (0 == stGeoListInfo.ucGeoNum)
    {
        return;
    }

    /* 从GEO list中找出最匹配的GEO */
    pstMostMatchGeoInfo = CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList(pstCurSysInfo, &stGeoListInfo);

    /* 从最匹配的GEO中获取PRL表中最匹配的系统记录索引 */
    enSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstCurSysInfo, pstMostMatchGeoInfo, &usMostMatchIndex);

    /* 不匹配 */
    if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH == enSysMatchLvl)
    {
        return;
    }

    /* 最高优先级记录直接返回 */
    if (usMostMatchIndex == pstMostMatchGeoInfo->usGeoFirstSysRecIndex)
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_0;

        return;
    }

    for (i = (pstMostMatchGeoInfo->usGeoFirstSysRecIndex); i <= usMostMatchIndex; i++)
    {
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(i);

        if ((VOS_NULL_PTR   == pstSysRecord)
         || (VOS_FALSE      == pstSysRecord->ucSysRecValid))
        {
            continue;
        }

        if (CNAS_PRL_RELATIVE_PRI_MORE == pstSysRecord->enPriInd)
        {
            ucSysPrioLvl++;

            /* 遇到more优先级的系统记录,PRIO递增,如果当前即为more的系统,优先级递减一次 */
            if (i == usMostMatchIndex)
            {
                ucSysPrioLvl--;
            }
        }
    }

    if (0 == ucSysPrioLvl)
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_0;
    }
    else if (1 == ucSysPrioLvl)
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_1;
    }
    else
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_OTHER;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetCurrentSystemPriClass
 功能描述  : 获取当前系统的PRI CLASS
 输入参数  : enSysType
 输出参数  : 无
 返 回 值  : NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8 -- PRI CLASS
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 7/4/2015
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8 CNAS_XSD_GetCurrentSystemPriClass(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    MSCC_XSD_SYS_TYPE_ENUM_UINT8        enSysType
)
{
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8                           enPriClass;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                         stGeoListInfo;
    CNAS_PRL_1X_MATCH_PRIO_LVL_ENUM_UINT8                       enMatchPrio;

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    enMatchPrio   = CNAS_PRL_1X_MATCH_PRIO_LEVLE_NULL;

    if (MSCC_XSD_SYS_TYPE_CDMA2000_AI == enSysType)
    {
        CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2kAISysType(pstCurSysInfo, &enMatchPrio);
    }
    else
    {
        CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2k1xSysType(pstCurSysInfo, &enMatchPrio);
    }

    if (CNAS_PRL_1X_MATCH_PRIO_LEVLE_0 == enMatchPrio)
    {
        enPriClass = NAS_MSCC_PIF_PRI_CLASS_HOME;
    }
    else if (CNAS_PRL_1X_MATCH_PRIO_LEVLE_1 == enMatchPrio)
    {
        enPriClass = NAS_MSCC_PIF_PRI_CLASS_PREF;
    }
    else
    {
        enPriClass = NAS_MSCC_PIF_PRI_CLASS_ANY;
    }

    return enPriClass;
}




VOS_VOID CNAS_XSD_StopAllTimerExceptSpecifiedTimerId(
    VOS_UINT32                          ulTimerId
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    VOS_UINT8                           i;
    CNAS_MNTN_TIMER_INFO_STRU           stMntnTimerInfo;

    pstTimerCtx = CNAS_GetTimerCtxAddr();

    for (i = 0; i < CNAS_MAX_TIMER_RUNNING_NUM; i++)
    {
        if ((CNAS_TIMER_STATUS_RUNNING   == pstTimerCtx->enTimerStatus)
         && (UEPS_PID_XSD                == pstTimerCtx->ulPid)
         && (ulTimerId                   != pstTimerCtx->ulTimerId))
        {
            /* 当定时器的句柄为空的时候, 说明其已经停止或者超时 */
            if (VOS_NULL_PTR != pstTimerCtx->pTimerHandle)
            {
                /* 当前timer还在运行，先停止它 */
                if (VOS_OK != VOS_StopRelTimer(&(pstTimerCtx->pTimerHandle)))
                {
                    /* 停止定时器失败，打印错误信息 */
                    CNAS_ERROR_LOG1(UEPS_PID_XSD, "CNAS_StopTimer: start timer is failure!", pstTimerCtx->ulTimerId);

                    pstTimerCtx++;

                    continue;
                }

                /* 输出timer停止信息 */
                stMntnTimerInfo.ulParam    = pstTimerCtx->ulParam;
                stMntnTimerInfo.ulTimerId  = pstTimerCtx->ulTimerId;
                stMntnTimerInfo.ulTimerLen = 0;
                stMntnTimerInfo.enTimerAct = CNAS_MNTN_TIMER_ACTION_STOP;
                CNAS_MNTN_TraceTimerMsg(UEPS_PID_XSD, &stMntnTimerInfo);
            }

            /* 清除timer表中的CTX信息 */
            pstTimerCtx->pTimerHandle  = VOS_NULL_PTR;
            pstTimerCtx->ulParam       = 0;
            pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_STOP;
            pstTimerCtx->ulTimerId     = 0;
            pstTimerCtx->ulPid         = 0;
        }

        pstTimerCtx++;
    }

}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsAddNegSysInAvoidList
 功能描述  : 获取是否添加neg sys到avoid频点列表
 输入参数  :

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月5日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsAddInAvoidList(
    CNAS_XSD_AVOID_REASON_ENUM_UINT8                        enReason
)
{
    switch(enReason)
    {
        case CNAS_XSD_AVOID_SID_NID_IS_REJ_BY_PRL:
            return (CNAS_XSD_Get1xSysAcqNvimConfig()->stAddAvoidListCfg.ucIsNegSysAdd);

        default:
            return VOS_FALSE;
    }

}


/*****************************************************************************
 函 数 名  : CNAS_XSD_RegisterRrmResourceNtf
 功能描述  : 处理向RRM发送注册信息，RF恢复提醒
 输入参数  : RRM_PS_TASK_TYPE_ENUM_UINT16
             enRrmTaskType : 注册的任务类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_RegisterRrmResourceNtf(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
)
{
    /* 发送注册消息 */
    CNAS_XSD_SndRrmRegisterInd(enRrmTaskType);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_DeRegisterRrmResourceNtf
 功能描述  : 处理向RRM发送去注册信息，取消RF恢复提醒
 输入参数  : RRM_PS_TASK_TYPE_ENUM_UINT16
             enRrmTaskType : 注册的任务类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_DeRegisterRrmResourceNtf(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
)
{
    /* 发送去注册消息 */
    CNAS_XSD_SndRrmDeRegisterInd(enRrmTaskType);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_ConvertSrvTypeToSessionType
 功能描述  : 将服务类型转换成相应的Session类型
 输入参数  : 业务类型
 输出参数  : 无
 返 回 值  : 相应的Session类型
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : w00242748时
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16 CNAS_XSD_ConvertSrvTypeToSessionType(
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType
)
{
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType;

    enSessionType = NAS_MSCC_PIF_SRV_TYPE_BUTT;

    switch (enSrvType)
    {
        case NAS_MSCC_PIF_SRV_TYPE_CS_MO_NORMAL_CALL :
        case NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL :
            enSessionType = CNAS_CAS_1X_SESSION_TYPE_CS_CALL;
            break;

        case NAS_MSCC_PIF_SRV_TYPE_PS_CONVERSAT_CALL :
        case NAS_MSCC_PIF_SRV_TYPE_PS_STREAM_CALL :
        case NAS_MSCC_PIF_SRV_TYPE_PS_INTERACT_CALL :
        case NAS_MSCC_PIF_SRV_TYPE_PS_BACKGROUND_CALL :
        case NAS_MSCC_PIF_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL :
            enSessionType = CNAS_CAS_1X_SESSION_TYPE_PS_CALL;
            break;

        case NAS_MSCC_PIF_SRV_TYPE_CS_MO_SMS :
            enSessionType = CNAS_CAS_1X_SESSION_TYPE_SMS;
            break;

        default:
            enSessionType = NAS_MSCC_PIF_SRV_TYPE_BUTT;
            break;
    }

    return enSessionType;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_IsSidInOperLockWhiteSidList
 功能描述  : 判断SID是否在白名单中
 输入参数  : usSid
 输出参数  : 无
 返 回 值  : VOS_TRUE   表示在白名单中
             VOS_FALSE  表示不在白名单中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsSidInOperLockSysWhiteList(
    VOS_UINT16                          usSid
)
{
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstOperLockSysWhiteList = VOS_NULL_PTR;
    CNAS_CCB_SYS_INFO_STRU                                 *pstSysInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulWhiteSysNum;

    pstOperLockSysWhiteList = CNAS_CCB_GetOperLockSysWhiteList();

    /* 如果白名单被disable，默认系统在白名单中 */
    if (VOS_FALSE == pstOperLockSysWhiteList->ucEnable)
    {
        return VOS_TRUE;
    }

    ulWhiteSysNum = (VOS_UINT32)CNAS_MIN(pstOperLockSysWhiteList->usWhiteSysNum, CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM);

    for (i = 0; i < ulWhiteSysNum; i++)
    {
        pstSysInfo = &(pstOperLockSysWhiteList->astSysInfo[i]);

        if ( (pstSysInfo->usStartSid <= usSid)
          && (usSid <= pstSysInfo->usEndSid) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsMccInOperLockWhiteSidList
 功能描述  : 判断MCC是否在白名单中
 输入参数  : usSid
 输出参数  : 无
 返 回 值  : VOS_TRUE   表示在白名单中
             VOS_FALSE  表示不在白名单中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsMccInOperLockSysWhiteList(
    VOS_UINT32                          ulMcc
)
{
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstOperLockSysWhiteList = VOS_NULL_PTR;
    CNAS_CCB_SYS_INFO_STRU                                 *pstSysInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstOperLockSysWhiteList = CNAS_CCB_GetOperLockSysWhiteList();

    /* 如果白名单被disable，默认系统在白名单中 */
    if (VOS_FALSE == pstOperLockSysWhiteList->ucEnable)
    {
        return VOS_TRUE;
    }

    for (i = 0; i < CNAS_MIN(pstOperLockSysWhiteList->usWhiteSysNum, CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM); i++)
    {
        pstSysInfo = &(pstOperLockSysWhiteList->astSysInfo[i]);

        if ( pstSysInfo->ulMcc == ulMcc )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsCurSysInSysWhiteList
 功能描述  : 判断当前系统是否在系统白名单中
 输入参数  : pstCurSysInfo -- 当前系统信息
             ulMccValidFlg -- 是否需要check MCC
             usMcc         -- MCC
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  表示在白名单中
             VOS_FALSE --  表示不在白名单中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月1日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurSysInSysWhiteList
(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    VOS_UINT32                          ulMccValidFlg,
    VOS_UINT16                          usMcc
)
{
    /* 如果当前系统SID在SID白名单中，则认为系统在白名单中 */
    if (VOS_TRUE == CNAS_XSD_IsSidInOperLockSysWhiteList(pstCurSysInfo->usSid))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == ulMccValidFlg)
    {
        /* 如果MCC在白名单中，则认为是一个适合驻留的系统 */
        if (VOS_TRUE == CNAS_XSD_IsMccInOperLockSysWhiteList(CNAS_XSD_TransformMccToBcd(usMcc)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_RefreshPriLvlInSysRecord
 功能描述  : 刷新系统表中的优先级等级
 输入参数  : usTmpSysRecNum - 系统表记录个数
             pstSysRecord - 系统表记录
             usDistance - 需要增加的值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_ReducePriLvlInSysRecordList(
    VOS_UINT16                          usTmpSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord,
    VOS_UINT16                          usReducePriLvl
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstTmpSysRecord = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstTmpSysRecord = pstSysRecord;

    for (i = 0; i < (VOS_UINT32)usTmpSysRecNum; i++)
    {
        pstTmpSysRecord->usPriLvl += usReducePriLvl;

        pstTmpSysRecord++;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildSysRecordListBasedOnGeo
 功能描述  : 根据GEO的信息来构建系统记录表(调用者需保证，
             pstSysRecord申请的内存个数是该GEO中，系统记录表的个数)
 输入参数  : pstMatchedGeo - GEO信息
 输出参数  : pstSysRecord - 系统记录表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildSysRecordListBasedOnGeo(
    CNAS_PRL_MATCHED_GEO_INFO_STRU     *pstMatchedGeo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstPrlSysInfo         = VOS_NULL_PTR;
    VOS_UINT16                          usGeoFirstSysRecIndex;
    VOS_UINT16                          usSysRecNum;

    pstPrlSysInfo         = CNAS_PRL_GetPrlSysInfoAddr();
    usSysRecNum           = pstMatchedGeo->usGeoSysRecNum;
    usGeoFirstSysRecIndex = pstMatchedGeo->usGeoFirstSysRecIndex;

    NAS_MEM_CPY_S(pstSysRecord, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*usSysRecNum, pstPrlSysInfo->pstSysRecord + usGeoFirstSysRecIndex, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*usSysRecNum);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_AddGeoIntoCompsiteGeo
 功能描述  : 将某个GEO加入到拼接的GEO中，拼接GEO以系统记录个数、以及相应的系统记录表示
            (内存在该函数内申请，但释放由调用者释放)
 输入参数  : pstMatchedGeo - 需要拼接的GEO
 输出参数  : pusSysRecNum - 系统记录个数
             ppstSysRecord - 系统记录列表
             pusPriLvl - 拼接后，最匹配系统对应的优先级等级
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2015年08月26日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_UINT32 CNAS_XSD_AddGeoIntoCompsiteGeo(
    CNAS_PRL_MATCHED_GEO_INFO_STRU     *pstMatchedGeo,
    VOS_UINT16                         *pusSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecordList,
    VOS_UINT16                         *pusPriLvl
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstNewSysRecordList = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstCurSysRecordList = VOS_NULL_PTR;
    VOS_UINT16                          usNewSysRecNum;
    VOS_UINT16                          usMostMatchedIndex;
    VOS_UINT16                          usNewSysRecPriLvl;
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT32                          k;

    usMostMatchedIndex    = pstMatchedGeo->usMostMatchedIndex;
    usNewSysRecPriLvl     = (CNAS_PRL_GetPrlSysInfoAddr()->pstSysRecord + usMostMatchedIndex)->usPriLvl;
    usNewSysRecNum        = pstMatchedGeo->usGeoSysRecNum;

    /* 将GEO列表中的系统记录表具体化，以每条记录的列表形式表示 */
    pstNewSysRecordList   = (CNAS_PRL_EXT_SYS_RECORD_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*usNewSysRecNum);
    if (VOS_NULL_PTR == pstNewSysRecordList)
    {
        return VOS_FALSE;
    }

    CNAS_XSD_BuildSysRecordListBasedOnGeo(pstMatchedGeo, pstNewSysRecordList);

    /* 将已拼接成的GEO列表拷贝一份 */
    pstCurSysRecordList   = (CNAS_PRL_EXT_SYS_RECORD_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*(*pusSysRecNum));
    if (VOS_NULL_PTR == pstCurSysRecordList)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstNewSysRecordList);
        return VOS_FALSE;
    }

    NAS_MEM_CPY_S(pstCurSysRecordList,
                  sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*(*pusSysRecNum),
                  pstSysRecordList,
                  sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*(*pusSysRecNum));

    if (usNewSysRecPriLvl > *pusPriLvl)
    {
        CNAS_XSD_ReducePriLvlInSysRecordList(*pusSysRecNum, pstCurSysRecordList, usNewSysRecPriLvl - *pusPriLvl);

        *pusPriLvl = usNewSysRecPriLvl;
    }
    else
    {
        CNAS_XSD_ReducePriLvlInSysRecordList(usNewSysRecNum, pstNewSysRecordList, *pusPriLvl - usNewSysRecPriLvl);
    }

    /* 合并两个GEO列表 */
    for (i = 0, j = 0, k = 0; (i < (VOS_UINT32)*pusSysRecNum) && (j < (VOS_UINT32)usNewSysRecNum); )
    {
        /* 判断新GEO中系统优先级与当前已拼接GEO中系统的优先级进行比较，按优先级数值从小到大的顺序排列 */
        if ( (pstCurSysRecordList+i)->usPriLvl > (pstNewSysRecordList+j)->usPriLvl )
        {
            NAS_MEM_CPY_S((pstSysRecordList + k), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU), (pstNewSysRecordList + j), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));
            k++;
            j++;
        }
        else
        {
            NAS_MEM_CPY_S((pstSysRecordList + k), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU), (pstCurSysRecordList + i), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));
            k++;
            i++;
        }
    }

    /* 将列表中剩余未插入的系统记录继续插入 */
    while (i != (VOS_UINT32)*pusSysRecNum)
    {
        NAS_MEM_CPY_S((pstSysRecordList + k), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU), (pstCurSysRecordList + i), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));
        k++;
        i++;
    }

    while (j != (VOS_UINT32)usNewSysRecNum)
    {
        NAS_MEM_CPY_S((pstSysRecordList + k), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU), (pstNewSysRecordList + j), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));
        k++;
        j++;
    }

    PS_MEM_FREE(UEPS_PID_XSD, pstNewSysRecordList);
    PS_MEM_FREE(UEPS_PID_XSD, pstCurSysRecordList);



    *pusSysRecNum   = *pusSysRecNum + usNewSysRecNum;

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildCompsiteGeoFromMostMatchedGeoList
 功能描述  : 将几个最匹配的GEO拼接，(内存在该函数内申请，但释放由调用者释放)
 输入参数  : pstMatchedGeoList - 需要拼接的GEO的集合
 输出参数  : pusSysRecNum - 系统记录个数
             ppstSysRecord - 系统记录列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildCompsiteGeoFromMostMatchedGeoList(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMatchedGeoList,
    VOS_UINT16                                             *pusSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecordList,
    VOS_UINT16                                             *pusMorePrefSysNum
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          j;
    VOS_UINT16                          usPriLvl;

    if (0 == pstMatchedGeoList->ucGeoNum)
    {
        return;
    }

    usPriLvl = 0;

    *pusSysRecNum        = pstMatchedGeoList->astGeoInfoList[0].usGeoSysRecNum;

    usPriLvl             = (CNAS_PRL_GetPrlSysInfoAddr()->pstSysRecord + pstMatchedGeoList->astGeoInfoList[0].usMostMatchedIndex)->usPriLvl;

    CNAS_XSD_BuildSysRecordListBasedOnGeo(&(pstMatchedGeoList->astGeoInfoList[0]), pstSysRecordList);

    for (i = 1; i < pstMatchedGeoList->ucGeoNum;i++)
    {
        CNAS_XSD_AddGeoIntoCompsiteGeo(&(pstMatchedGeoList->astGeoInfoList[i]), pusSysRecNum, pstSysRecordList, &usPriLvl);
    }

    for (j = 0; j < *pusSysRecNum; j++)
    {
        if ((pstSysRecordList + j)->usPriLvl < usPriLvl)
        {
            (*pusMorePrefSysNum)++;
        }
        else
        {
            break;
        }
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_BuildGeoListBasedOnSysRecord
 功能描述  : 根据系统记录信息获取相应的GEO
 输入参数  : pstPrlSysInfo - PRL表中系统表记录
 输出参数  : pstGeoList - GEO列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : w00242748
    修改内容   : 新生成函数
  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildGeoListBasedOnSysRecord(
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstPrlSysInfo,
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoList
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord = VOS_NULL_PTR;
    VOS_UINT16                          i;
    VOS_UINT16                          j;
    VOS_UINT16                          usGeoNum;

    /* 该函数仅供内部调用，调用者保证pstPrlSysInfo不为VOS_NULL_PTR */
    pstSysRecord   = pstPrlSysInfo->pstSysRecord;
    usGeoNum       = 0;

    /* 统计GEO的个数，为了后续申请内存 */
    for (i = 0; i < pstPrlSysInfo->usSysRecordNum;i++)
    {
        if ( (CNAS_PRL_GEO_REGION_IND_NEW == (pstSysRecord+i)->enGeoInd)
          || (0 == i) )
        {
            usGeoNum++;
        }
    }

    pstGeoList->usGeoNum       = usGeoNum;
    pstGeoList->pstGeoSrchInfo = (CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU)*usGeoNum);

    if (VOS_NULL_PTR == pstGeoList->pstGeoSrchInfo)
    {
        pstGeoList->usGeoNum       = 0;
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_BuildGeoListBasedOnSysRecord: mem alloc fail");

        return;
    }

    /* 在已经申请的内存中，存放GEO的首地址 */
    for (i = 0, j = 0; i < pstPrlSysInfo->usSysRecordNum;i++)
    {
        if ( (CNAS_PRL_GEO_REGION_IND_NEW == (pstSysRecord+i)->enGeoInd)
          || (0 == i) )
        {
            pstGeoList->pstGeoSrchInfo[j].usGeoBeginIndex = i;
            pstGeoList->pstGeoSrchInfo[j].usGeoSrchStatus = VOS_FALSE;
            j++;
        }
    }
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_GetGeoListFromPrlSysRecordInfo
 功能描述  : 根据系统记录信息获取相应的GEO
 输入参数  : 无
 输出参数  : pstGeoList - GEO列表
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_GetGeoListFromPrlSysRecordInfo(
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoList
)
{
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstPrlSysInfo   = VOS_NULL_PTR;

    pstPrlSysInfo         = CNAS_PRL_GetPrlSysInfoAddr();

    CNAS_XSD_BuildGeoListBasedOnSysRecord(pstPrlSysInfo, pstGeoList);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_CalcPrlSysRecListTotalFreqNum
 功能描述  : 计算PRL系统记录列表的总的频点个数，(MCC-MNC记录的话，得分成多条记录处理)
 输入参数  : usSysRecNum-----------系统记录总个数
             pstSysRecord----------系统记录列表
 输出参数  : 无

 返 回 值  : 获取表中总的频点个数
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 CNAS_XSD_CalcPrlSysRecListTotalFreqNum(
    VOS_UINT16                          usSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usTotalNum;
    VOS_UINT16                          usAcqIndex;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stFreqInfo;
    VOS_UINT8                           ucSidNum;

    usTotalNum  = 0;
    usAcqIndex  = 0;
    ucSidNum    = 0;

    /* 当前计算的频点可能有重复，目前先允许有这样的重复，暂时认为这个重复不会是特别的多 */
    for (i = 0; i < usSysRecNum; i++)
    {

        if (VOS_FALSE == pstSysRecord[i].ucSysRecValid)
        {
            continue;
        }

        if (CNAS_PRL_SYS_RECORD_TYPE_1X_IS95 == pstSysRecord[i].enRecordType)
        {
            usAcqIndex = pstSysRecord[i].usAcqIndex;
            pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(usAcqIndex);

            /* 空指针进行保护 */
            if (VOS_NULL_PTR == pstPrlAcqRec)
            {
                continue;
            }

            CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stFreqInfo);

            usTotalNum += (VOS_UINT16)stFreqInfo.ulNum;
        }

        if (CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord[i].enRecordType)
        {
            usAcqIndex = pstSysRecord[i].usAcqIndex;
            pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(usAcqIndex);

            /* 空指针进行保护 */
            if (VOS_NULL_PTR == pstPrlAcqRec)
            {
                continue;
            }

            CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stFreqInfo);

            if ( (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID     == pstSysRecord[i].u.stMccMncId.enMccMncSubType)
              || (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID_NID == pstSysRecord[i].u.stMccMncId.enMccMncSubType) )
            {
                ucSidNum    = pstSysRecord[i].u.stMccMncId.u.stSidNid.ucSidNidNum;
                usTotalNum += (VOS_UINT16)(stFreqInfo.ulNum * ucSidNum);
            }
        }
    }

    return usTotalNum;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_IsCurSysHomeSystemIndependenceOnPrl
 功能描述  : check当前不在PRL表中的系统是否是home SID/NID系统
 输入参数  : pstCurSysInfo -- 当前系统信息
 输出参数  : 无
 返 回 值  : VOS_TRUE   表示是home系统
             VOS_FALSE  表示不是home系统
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurSysHomeSystemIndependenceOnPrl(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
)
{
    /* 如果非PRL表中的系统不能当作home系统 */
    if (VOS_TRUE == CNAS_CCB_GetHomeSidNidDependOnPrlFlg())
    {
        return VOS_FALSE;
    }

    /* 如果系统不在home SID/NID list中，则认为是非home系统 */
    if (VOS_FALSE == CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSysInfo))
    {
        return VOS_FALSE;
    }

    /* 如果当前home SID不在白名单中，则认为不是home SID/NID系统 */
    if (VOS_FALSE == CNAS_XSD_IsSidInOperLockSysWhiteList(pstCurSysInfo->usSid))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsCurSystemInAvailSysList
 功能描述  : 判断一个system是否在available system list中
 输入参数  : CNAS_PRL_1X_SYSTEM_STRU            *pstCurSys
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月6日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2014年12月25日
    作    者   : w00176964
    修改内容   : CDMA Iteration 6:Move the avail system list to the global variables
  3.日    期   : 2015年7月17日
    作    者   : y00245242
    修改内容   : iteration 17开发
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurSystemInAvailSysList(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSys
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;
    VOS_UINT32                                              ulHomeSidNidFlg;

    /* 获取所有匹配的GEO list */
    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_PRL_Get1xSysGeoList(pstCurSys, &stGeoListInfo);

    /* PRL中能找到对应的GEO，则认为是非avail系统 */
    if (0 != stGeoListInfo.ucGeoNum)
    {
        return VOS_FALSE;
    }

    /* 当前系统不在白名单中，则认为是NEG系统，也不是avail系统 */
    if (VOS_FALSE == CNAS_XSD_IsSidInOperLockSysWhiteList(pstCurSys->usSid))
    {
        return VOS_FALSE;
    }

    ulHomeSidNidFlg = CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSys);

    /* 如果home sid/nid独立于PRL，且是home sid/nid系统的话，则认为是非avail系统 */
    if ( (VOS_FALSE == CNAS_CCB_GetHomeSidNidDependOnPrlFlg())
      && (VOS_TRUE == ulHomeSidNidFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_QuitCallBackMode
 功能描述  : 紧急呼退出CallBack模式函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月02日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XSD_QuitCallBackMode( VOS_VOID )
{
    /* 上报退出CALLBACK模式NTF */
    CNAS_XSD_SndMsccEmcCallBackInd(NAS_MSCC_PIF_EMC_CALLBACK_MODE_DISABLE);

    /* 清空紧急呼建立成功的系统 */
    CNAS_XSD_ClearEmcCallOriginalSys();

    /* 清除异频临区频点信息 */
    CNAS_XSD_ClearEmcCallBackCandidateFreq();

    /* 清空CALLBACK状态 */
    CNAS_XSD_SetEmcState(CNAS_XSD_EMC_STATE_NULL);

    CNAS_XSD_LogCallBackStatusInd(ID_CNAS_XSD_MNTN_LOG_QUIT_CALLBACK_IND);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_IsCurSysNotSuitableSys
 功能描述  : 判断当前系统是否能驻留
 输入参数  : pstCurSysInfo -- 当前系统信息
 输出参数  : 无
 返 回 值  : VOS_TRUE   表示是not suitable系统，即认为是neg系统
             VOS_FALSE  表示是suitable系统，不是negative系统
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurSysNotSuitableSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    VOS_UINT32                          ulMccValidFlg,
    VOS_UINT16                          usMcc
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stGeoListInfo;
    VOS_UINT32                          ulIsNegSys;

    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stGeoListInfo);

    if (0 == stGeoListInfo.ucGeoNum)
    {
        if (VOS_FALSE == CNAS_PRL_GetPrefOnlyFlg())
        {
            /* 如果prefer only为FALSE，需要检查白名单 */
            return (!CNAS_XSD_IsCurSysInSysWhiteList(pstCurSysInfo, ulMccValidFlg, usMcc));
        }

        /* 如果prefer only为TRUE，且home SID/NID系统需要依赖PRL，则不在PRL表中系统都是不适合驻留的系统 */
        if (VOS_TRUE == CNAS_CCB_GetHomeSidNidDependOnPrlFlg())
        {
            return VOS_TRUE;
        }

        /* 如果prefer only为TRUE，且home SID/NID系统不依赖PRL，则需要继续home SID/NID检查 */
    }
    else
    {
        /* home sid/nid的优先指示标识不管是enable还是disable，都会将该系统指示成非NEG */
        ulIsNegSys = CNAS_PRL_Is1xSysNegativeInPrl(pstCurSysInfo, &stGeoListInfo);

        /* 如果不是negative系统，check当前系统是否在白名单中 */
        if (VOS_FALSE == ulIsNegSys)
        {
            return (!CNAS_XSD_IsCurSysInSysWhiteList(pstCurSysInfo, ulMccValidFlg, usMcc));
        }

        /* 如果是negative系统，则需要继续home SID/NID检查 */
    }

    /* 如果系统不在白名单中，则认为该系统不适合驻留 */
    if (VOS_FALSE == CNAS_XSD_IsCurSysInSysWhiteList(pstCurSysInfo, ulMccValidFlg, usMcc))
    {
        return VOS_TRUE;
    }

    /* 如果当前系统不在home SID/NID list中，则认为该系统不适合驻留 */
    if (VOS_FALSE == CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSysInfo))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_Is1xSysAllowedCampOn
 功能描述  : 判断当前系统是否是neg系统
 输入参数  : pstCurSysInfo -- 当前系统信息
 输出参数  : 无
 返 回 值  : VOS_TRUE   表示是neg系统
             VOS_FALSE  表示不是neg系统
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XSD_Is1xSysNegative(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    VOS_UINT32                          ulMccValidFlg,
    VOS_UINT16                          usMcc
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stGeoListInfo;
    VOS_UINT32                          ulIsNegSys;
    VOS_UINT8                           ucHomeSidNidFlg;

    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stGeoListInfo);

    if (0 == stGeoListInfo.ucGeoNum)
    {
        ulIsNegSys = VOS_FALSE;
    }
    else
    {
        /* home sid/nid的优先指示标识不管是enable还是disable，都会将该系统指示成非NEG */
        ulIsNegSys      = CNAS_PRL_Is1xSysNegativeInPrl(pstCurSysInfo, &stGeoListInfo);
        ucHomeSidNidFlg = CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSysInfo);

        ulIsNegSys = (VOS_UINT32)((VOS_TRUE == ucHomeSidNidFlg) ? VOS_FALSE : ulIsNegSys);
    }

    if (VOS_FALSE == ulIsNegSys)
    {
        /* 如果不在白名单中，则认为是negative系统 */
        if (VOS_FALSE == CNAS_XSD_IsCurSysInSysWhiteList(pstCurSysInfo, ulMccValidFlg, usMcc))
        {
            ulIsNegSys = VOS_TRUE;
        }
    }

    return ulIsNegSys;
}



/*lint -restore */


#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

