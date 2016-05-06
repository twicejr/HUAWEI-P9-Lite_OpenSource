/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXsdMntn.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2014年08月18日
  功能描述   : CNAS的可维可测
  函数列表   :
  修改历史   :
  1.日    期   : 2014年08月18日
    作    者   : w00176964
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasMntn.h"
#include "CnasXsdMntn.h"
#include "NasNvInterface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_MNTN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XSD_LogScanChannelList
 功能描述  : 将频点扫描列表导出到SDT LOG中
 输入参数  : ulMsgName----消息名
             pstScanChanList--频点扫描列表
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2014年12月10日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modified

*****************************************************************************/
VOS_VOID CNAS_XSD_LogScanChannelList(
    VOS_UINT32                          ulMsgName,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU                 *pstMsg               = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                          (sizeof(CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogScanChannelList:Alloc Memory Failed");

        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->enMsgId         = ulMsgName;

    pstMsg->usChanNum       = pstScanChanList->usTotalNum;
    pstMsg->usCurScanIndex  = pstScanChanList->usCurScanIndex;

    for (i = 0; i < pstScanChanList->usTotalNum; i++)
    {
        if (i >= CNAS_XSD_MAX_LOG_CHANNEL_NUM_IN_SCAN_LIST)
        {
            break;
        }

        pstMsg->astScanChanList[i] = pstScanChanList->pstScanChanInfo[i];
    }

    pstMsg->ulLength        = sizeof(pstMsg->enMsgId)
                              + sizeof(pstMsg->usChanNum)
                              + sizeof(pstMsg->usCurScanIndex)
                              + (pstMsg->usChanNum * sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_LogAcqSystemList
 功能描述  : 将系统捕获列表导出到SDT LOG中
 输入参数  : pstAcqSysList
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogAcqSystemList(
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU                  *pstMsg               = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                          (sizeof(CNAS_XSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogAcqSystemList:Alloc Memory Failed");

        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_ACQ_SYS_LIST_IND;

    pstMsg->usSysNum   = pstGeoSysRecSrchList->usTotalNum;

    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++)
    {
        if (i >= CNAS_XSD_MAX_LOG_SYSTEM_NUM_IN_ACQ_LIST)
        {
            break;
        }

        pstMsg->astAcqSysList[i] = pstGeoSysRecSrchList->pstAcqSysInfo[i];
    }

    pstMsg->ulLength        = sizeof(pstMsg->enMsgId)
                              + sizeof(pstMsg->usSysNum)
                              + sizeof(pstMsg->aucRsv[0])*2
                              + (pstMsg->usSysNum* sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_LogAvailSystemList
 功能描述  : 将avail系统列表导出到SDT LOG中
 输入参数  : pstAvailSysList
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : w00176964
    修改内容   : 新生成函数

  2.日    期   : 2015年7月9日
    作    者   : y00245242
    修改内容   : iteration 17开发

*****************************************************************************/
VOS_VOID CNAS_XSD_LogAvailSystemList(
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_LOG_AVAIL_SYSTEM_LIST_MSG_STRU                *pstMsg               = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_AVAIL_SYSTEM_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                          (sizeof(CNAS_XSD_LOG_AVAIL_SYSTEM_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogAvailSystemList:Alloc Memory Failed");

        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_AVAIL_SYS_LIST_IND;

    pstMsg->ucAvailSysNum = pstAvailSysList->ucAvailSysNum;

    pstMsg->ucNextSrchIndex = pstAvailSysList->ucNextSrchIndex;

    for (i = 0; i < (VOS_UINT32)CNAS_MIN(pstAvailSysList->ucAvailSysNum, CNAS_XSD_MAX_AVAILABLE_SYS_NUM); i++)
    {
        pstMsg->astAvailSystem[i] = pstAvailSysList->astAvailSystem[i];
    }

    pstMsg->ulLength = sizeof(pstMsg->enMsgId)
                       + sizeof(pstMsg->ucAvailSysNum)
                       + sizeof(pstMsg->ucNextSrchIndex)
                       + sizeof(pstMsg->aucRsved[0])*2
                       + (pstMsg->ucAvailSysNum* sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_AVAIL_SYSTEM_LIST_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}



/*****************************************************************************
 函 数 名  : CNAS_XSD_LogMruList
 功能描述  : 将MRU列表导出到SDT LOG中
 输入参数  : pstMruList
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年8月18日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogMruList(
    CNAS_XSD_MRU_LIST_STRU             *pstMruList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_LOG_MRU_LIST_MSG_STRU                         *pstMsg               = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_MRU_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                          (sizeof(CNAS_XSD_LOG_MRU_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogMruList:Alloc Memory Failed");

        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_MRU_LIST_IND;

    pstMsg->ucSysNum    = pstMruList->ucSysNum;

    for (i = 0; i < (VOS_UINT32)CNAS_MIN(pstMruList->ucSysNum, CNAS_XSD_MAX_MRU_SYS_NUM); i++)
    {
        pstMsg->astSystem[i] = pstMruList->astSystem[i];
    }

    pstMsg->ulLength        = sizeof(pstMsg->enMsgId)
                              + sizeof(pstMsg->ucSysNum)
                              + sizeof(pstMsg->aucReserve[0])*3
                              + (pstMsg->ucSysNum* sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_MRU_LIST_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}


VOS_VOID CNAS_XSD_LogUeSupportedBandClass(
    VOS_UINT32                          ulBandClass
)
{
    CNAS_XSD_LOG_BANDCLASS_LIST_MSG_STRU                   *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_BANDCLASS_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                          (sizeof(CNAS_XSD_LOG_BANDCLASS_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogUeSupportedBandClass:Alloc Memory Failed");

        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_BANDClASS_LIST_IND;

    pstMsg->ulLength        = sizeof(pstMsg->enMsgId) + sizeof(VOS_UINT32);

    pstMsg->ulBandClass = ulBandClass;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_BANDCLASS_LIST_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_LogHomeSidNidList
 功能描述  : 将HOME_SID_NID列表导出到SDT LOG中
 输入参数  : pstHomeSidNidList
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogHomeSidNidList(
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU          *pstHomeSidNidList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU                 *pstMsg               = VOS_NULL_PTR;
    pstMsg = (CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                     sizeof(CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogHomeSidNidList:Alloc Memory Failed");

        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU), 0, sizeof(CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_HOME_SID_NID_LIST_IND;
    pstMsg->ucSysNum        = CNAS_MIN(pstHomeSidNidList->ucSysNum, CNAS_CCB_MAX_HOME_SID_NID_LIST);

    for (i = 0; i < pstMsg->ucSysNum; i++)
    {
        NAS_MEM_CPY_S(&pstMsg->astHomeSidNid[i],
                      sizeof(CNAS_CCB_1X_HOME_SID_NID_STRU),
                      &pstHomeSidNidList->astHomeSidNid[i],
                      sizeof(CNAS_CCB_1X_HOME_SID_NID_STRU));
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_LogOocScheduleInfo
 功能描述  : 将OOC timer调度信息导出到SDT LOG中
 输入参数  : pstOocTimerScheduleInfo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogOocScheduleInfo(
    CNAS_NVIM_OOC_TIMER_SCHEDULE_INFO_STRU                 *pstOocTimerScheduleInfo
)
{
    VOS_UINT8                                               i;
    CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU          *pstMsg               = VOS_NULL_PTR;
    pstMsg = (CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                          sizeof(CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogOocScheduleInfo:Alloc Memory Failed");

        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU), 0, sizeof(CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_OOC_TIMER_SCHEDULE_IND;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucMru0SearchTimerLen        = pstOocTimerScheduleInfo->ucMru0SearchTimerLen;
    pstMsg->ucPhaseNum                  = pstOocTimerScheduleInfo->ucPhaseNum;
    pstMsg->uc1xOocDoTchPhase1TimerLen  = pstOocTimerScheduleInfo->uc1xOocDoTchPhase1TimerLen;
    pstMsg->uc1xOocDoTchPhase2TimerLen  = pstOocTimerScheduleInfo->uc1xOocDoTchPhase2TimerLen;

    for (i = 0; i < pstOocTimerScheduleInfo->ucPhaseNum; i++)
    {
        pstMsg->astOocTimerInfo[i].usTimes    = pstOocTimerScheduleInfo->astOocTimerInfo[i].usTimes;
        pstMsg->astOocTimerInfo[i].usTimerLen = pstOocTimerScheduleInfo->astOocTimerInfo[i].usTimerLen;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_LogAvoidFreqList
 功能描述  : 将avoid 频点列表导出到SDT LOG中
 输入参数  : pstAvoidFreqList
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月22日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogAvoidFreqList(
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList
)
{
    VOS_UINT8                                               i;
    VOS_UINT8                                               j;
    CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                   sizeof(CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogAvoidFreqList: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU), 0, sizeof(CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_AVOID_FREQ_LIST_IND;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucAvoidFreqNum              = pstAvoidFreqList->ucAvoidFreqNum;

    for (i = 0; i < CNAS_MIN(pstAvoidFreqList->ucAvoidFreqNum, CNAS_XSD_MAX_AVOID_FREQ_NUM); i++)
    {
        pstMsg->astAvoidFreqInfo[i].ucAvoidFlag       = pstAvoidFreqList->astAvoidFreqInfo[i].ucAvoidFlag;
        pstMsg->astAvoidFreqInfo[i].stAvoidFreq       = pstAvoidFreqList->astAvoidFreqInfo[i].stAvoidFreq;
        pstMsg->astAvoidFreqInfo[i].ulStartSlice      = pstAvoidFreqList->astAvoidFreqInfo[i].ulStartSlice;
        pstMsg->astAvoidFreqInfo[i].ulExpiredSliceNum = pstAvoidFreqList->astAvoidFreqInfo[i].ulExpiredSliceNum;

        for (j = 0; j < CNAS_XSD_AVOID_REASON_MAX; j++)
        {
            pstMsg->astAvoidFreqInfo[i].aucAvoidTimes[j] = pstAvoidFreqList->astAvoidFreqInfo[i].aucAvoidTimes[j];
        }

    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_LogPrlSourceType
 功能描述  : 将avoid 频点列表导出到SDT LOG中
 输入参数  : enPrlSrcType -- PRL源类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月22日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogPrlSourceType(
    CNAS_XSD_PRL_SOURCE_TYPE_ENUM_UINT8 enPrlSrcType
)
{
    CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                   sizeof(CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogPrlSourceType: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU), 0, sizeof(CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_PRL_SOURCE_TYPE_IND;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enPrlSrcType                = enPrlSrcType;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_LogBufferQueueMsg
 功能描述  : 导出缓存的消息
 输入参数  : ulFullFlg:缓存是否已经满的标志位
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月5日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_XSD_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
)
{
    CNAS_XSD_LOG_BUffER_MSG_INFO_STRU  *pstBufferMsg = VOS_NULL_PTR;
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue  = VOS_NULL_PTR;

    pstBufferMsg = (CNAS_XSD_LOG_BUffER_MSG_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_XSD,
                             sizeof(CNAS_XSD_LOG_BUffER_MSG_INFO_STRU));

    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogBufferQueueMsg: Alloc Memory Failed!");
        return;
    }

    NAS_MEM_SET_S(pstBufferMsg, sizeof(CNAS_XSD_LOG_BUffER_MSG_INFO_STRU), 0, sizeof(CNAS_XSD_LOG_BUffER_MSG_INFO_STRU));

    pstMsgQueue                               = CNAS_XSD_GetCacheMsgAddr();
    pstBufferMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBufferMsg->ulSenderPid     = UEPS_PID_XSD;
    pstBufferMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstBufferMsg->ulLength        = sizeof(CNAS_XSD_LOG_BUffER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBufferMsg->enMsgId       = ID_CNAS_XSD_MNTN_LOG_BUFFER_MSG_INFO_IND;
    pstBufferMsg->ulFullFlg                   = ulFullFlg;
    NAS_MEM_CPY_S(&(pstBufferMsg->stMsgQueue), sizeof(pstBufferMsg->stMsgQueue), pstMsgQueue, sizeof(pstBufferMsg->stMsgQueue));

    DIAG_TraceReport(pstBufferMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstBufferMsg);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_LogOocCtxInfo
 功能描述  : log OOC上下文信息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月22日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogOocCtxInfo(
    CNAS_XSD_OOC_CTX_INFO_STRU         *pstOocCtxInfo
)
{
    CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                sizeof(CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogOocCtxInfo: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU), 0, sizeof(CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU));

    /* 更新消息头信息 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_OOC_CTX_INFO_IND;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 设置消息体内容 */
    pstMsg->ucAttemptTimesInDoTraffic   = pstOocCtxInfo->ucAttemptTimesInDoTraffic;
    pstMsg->ucCurrentPhase              = pstOocCtxInfo->ucCurrentPhase;
    pstMsg->ucDoTrafficFlag             = pstOocCtxInfo->ucDoTrafficFlag;
    pstMsg->ucFirstFourAcqArrivedFlag   = pstOocCtxInfo->ucFirstFourAcqArrivedFlag;
    pstMsg->ucSceneSetFlag              = pstOocCtxInfo->ucSceneSetFlag;
    pstMsg->ucWaitSearchFlag            = pstOocCtxInfo->ucWaitSearchFlag;
    pstMsg->usCurrentTimes              = pstOocCtxInfo->usCurrentTimes;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_LogHomeSidNidMostPriFlg
 功能描述  : 勾取home sid/nid是否是最优选的标记
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogHomeSidNidDependOnPrlFlg(
    VOS_UINT8                           ucFlg
)
{
    CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                sizeof(CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogHomeSidNidMostPriCfg: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU), 0, sizeof(CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU));

    /* 更新消息头信息 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_HOME_SID_NID_PRI_FLG;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 设置消息体内容 */
    pstMsg->ucHomeSidNidMostPriFlg      = ucFlg;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_LogOperLockWhiteSidList
 功能描述  : 勾取OPER LOCK WHITE SID列表
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogOperLockSysWhiteList(
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstMsg
)
{
    CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU             *pstOperLockSysWhiteList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstOperLockSysWhiteList = (CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                sizeof(CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU));
    if (VOS_NULL_PTR == pstOperLockSysWhiteList)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogOperLockSysWhiteList: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstOperLockSysWhiteList, sizeof(CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU), 0, sizeof(CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU));

    /* 更新消息头信息 */
    pstOperLockSysWhiteList->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstOperLockSysWhiteList->ulSenderPid     = UEPS_PID_XSD;
    pstOperLockSysWhiteList->ulReceiverPid   = UEPS_PID_XSD;
    pstOperLockSysWhiteList->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstOperLockSysWhiteList->enMsgId         = ID_CNAS_XSD_MNTN_LOG_OPER_LOCK_WHITE_SID_LIST_IND;
    pstOperLockSysWhiteList->ulLength        = sizeof(CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 设置消息体内容 */
    pstOperLockSysWhiteList->ucEnable      = pstMsg->ucEnable;

    pstOperLockSysWhiteList->usWhiteSysNum = CNAS_MIN(pstMsg->usWhiteSysNum, CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM);

    for (i = 0; i < pstOperLockSysWhiteList->usWhiteSysNum;i++)
    {
        pstOperLockSysWhiteList->astSysInfo[i].usStartSid = pstMsg->astSysInfo[i].usStartSid;
        pstOperLockSysWhiteList->astSysInfo[i].usEndSid   = pstMsg->astSysInfo[i].usEndSid;
        pstOperLockSysWhiteList->astSysInfo[i].ulMcc      = pstMsg->astSysInfo[i].ulMcc;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU), (VOS_VOID *)pstOperLockSysWhiteList);

    PS_MEM_FREE(UEPS_PID_XSD, pstOperLockSysWhiteList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_LogCTCCCustomizeFreqList
 功能描述  : 勾取中国电信自定义频点列表
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogCTCCCustomizeFreqList(
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstMsg
)
{
    CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU             *pstCustFreqList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstCustFreqList = (CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                sizeof(CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU));
    if (VOS_NULL_PTR == pstCustFreqList)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogCTCCCustomizeFreqList: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstCustFreqList, sizeof(CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU), 0, sizeof(CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU));

    /* 更新消息头信息 */
    pstCustFreqList->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCustFreqList->ulSenderPid     = UEPS_PID_XSD;
    pstCustFreqList->ulReceiverPid   = UEPS_PID_XSD;
    pstCustFreqList->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCustFreqList->enMsgId         = ID_CNAS_XSD_MNTN_LOG_CTCC_CUSTOMIZE_FREQ_LIST_IND;
    pstCustFreqList->ulLength        = sizeof(CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 设置消息体内容 */
    pstCustFreqList->ucEnableFlg = pstMsg->ucEnableFlg;
    pstCustFreqList->usFreqNum   = CNAS_MIN(pstMsg->usFreqNum, CNAS_CCB_MAX_FREQ_NUM);

    for (i = 0; i < pstCustFreqList->usFreqNum;i++)
    {
        pstCustFreqList->astFreqList[i].usChannel   = pstMsg->astFreqList[i].usChannel;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU), (VOS_VOID *)pstCustFreqList);

    PS_MEM_FREE(UEPS_PID_XSD, pstCustFreqList);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XSD_LogGeoSrchStatusList
 功能描述  : GEO搜索状态list
 输入参数  : pstGeoSrchStatus -- GEO搜索状态列表信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogGeoListSrchStatus(
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU    *pstGeoSrchStatus
)
{
    CNAS_XSD_LOG_GEO_LIST_SRCH_STATUS_STRU                 *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLen;
    VOS_UINT16                                              usGeoNum;

    usGeoNum = (VOS_UINT16)CNAS_MIN(pstGeoSrchStatus->usGeoNum, CNAS_XSD_MAX_LOG_SYSTEM_NUM_IN_ACQ_LIST);

    ulMsgLen = sizeof(MSG_HEADER_STRU) + sizeof(VOS_UINT16) + sizeof(VOS_UINT16) +\
               sizeof(CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU) * usGeoNum;

    pstMsg = (CNAS_XSD_LOG_GEO_LIST_SRCH_STATUS_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, ulMsgLen, 0, ulMsgLen);

    /* 更新消息头信息 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_GEO_LIST_SRCH_STATUS_IND;
    pstMsg->ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;

    pstMsg->usGeoNum                    = usGeoNum;

    if (0 != usGeoNum)
    {
        NAS_MEM_CPY_S(&pstMsg->astGeoSrchInfo[0],
                      sizeof(CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU) * pstMsg->usGeoNum,
                      pstGeoSrchStatus->pstGeoSrchInfo,
                      sizeof(CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU) * pstMsg->usGeoNum);
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, ulMsgLen, (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU
 功能描述  : LOG CDMA标准频段
 输入参数  : pstCdmaStandardChan -- CDMA标准频段信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogCdmaStandardChannels(
    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                   *pstCdmaStandardChan
)
{
    CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU               *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                      sizeof(CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU), 0, sizeof(CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU));

    /* 更新消息头信息 */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_CDMA_STANDARD_CHANNELS_IND;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stCdmaStandardChan.usPrimaryA   = pstCdmaStandardChan->usPrimaryA;

    pstMsg->stCdmaStandardChan.usPrimaryB   = pstCdmaStandardChan->usPrimaryB;

    pstMsg->stCdmaStandardChan.usSecondaryA = pstCdmaStandardChan->usSecondaryA;

    pstMsg->stCdmaStandardChan.usSecondaryB = pstCdmaStandardChan->usSecondaryB;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_LogCallBackConfig
 功能描述  : LOG CallBack模式Nv配置
 输入参数  : pstCdmaStandardChan -- CDMA标准频段信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogCallBackConfig(
    CNAS_XSD_CALLBACK_CFG_STRU                             *pstCallBackCfg
)
{
    CNAS_XSD_LOG_CALLBACK_CFG_STRU                          *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_CALLBACK_CFG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_LOG_CALLBACK_CFG_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_CALLBACK_CFG_STRU), 0, sizeof(CNAS_XSD_LOG_CALLBACK_CFG_STRU));

    /* 更新消息头信息 */
    pstMsg->ulReceiverCpuId                         = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                             = UEPS_PID_XSD;
    pstMsg->ulReceiverPid                           = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId                           = VOS_LOCAL_CPUID;
    pstMsg->enMsgId                                 = ID_CNAS_XSD_MNTN_LOG_CALLBACK_CFG_IND;
    pstMsg->ulLength                                = sizeof(CNAS_XSD_LOG_CALLBACK_CFG_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stCallBackCfg.ulCallBackEnableFlg       = pstCallBackCfg->ulCallBackEnableFlg;
    pstMsg->stCallBackCfg.ulCallBackModeTimerLen    = pstCallBackCfg->ulCallBackModeTimerLen;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_CALLBACK_CFG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_LogCallBackStatusInd
 功能描述  : LOG CallBack模式Nv配置
 输入参数  : pstCdmaStandardChan -- CDMA标准频段信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogCallBackStatusInd(
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32                        enMsgId
)
{
    CNAS_XSD_LOG_CALLBACK_STATUS_STRU                        *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_CALLBACK_STATUS_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                               sizeof(CNAS_XSD_LOG_CALLBACK_STATUS_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_CALLBACK_STATUS_STRU), 0, sizeof(CNAS_XSD_LOG_CALLBACK_STATUS_STRU));

    /* 更新消息头信息 */
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->enMsgId                     = enMsgId;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_LOG_CALLBACK_STATUS_STRU) - VOS_MSG_HEAD_LENGTH;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_CALLBACK_STATUS_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);
}

/*****************************************************************************
 函 数 名  : CNAS_XSD_LogCdma1XPrefChannels
 功能描述  : LOG Cdma 1X优选频点信息
 输入参数  : pstCdma1XPrefChannels -- CDMA 1X 优选频点信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XSD_LogCdma1XCustomPrefChannels(
    CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU             *pstCdma1XPrefChannels
)
{
    CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU), 0x00, sizeof(CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU));

    /* 更新消息头信息 */
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->enMsgId                     = ID_CNAS_XSD_MNTN_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_IND;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU) - VOS_MSG_HEAD_LENGTH;
    NAS_MEM_CPY_S(&(pstMsg->stCdma1XPrefChannels),
                  sizeof(pstMsg->stCdma1XPrefChannels),
                  pstCdma1XPrefChannels,
                  sizeof(CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);
}


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




