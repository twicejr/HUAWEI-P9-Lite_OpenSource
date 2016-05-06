/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasHsdMntn.c
  版 本 号   : 初稿
  作    者   : d00212987
  生成日期   : 2014年12月16日
  功能描述   : CNAS的可维可测
  函数列表   :
  修改历史   :
  1.日    期   : 2014年12月16日
    作    者   : d00212987
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasMntn.h"
#include "CnasHsdMntn.h"
#include "PsLib.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_MNTN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e545 -e413 */
/*****************************************************************************
 函 数 名  : CNAS_HSD_LogScanFreqList
 功能描述  : 将频点扫描列表导出到SDT LOG中
 输入参数  : pstScanFreqList - 待导出Scan list
             enMsgLogType    - Scan list产生场景

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_LogScanFreqList(
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU           *pstScanFreqList,
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32           enMsgLogType
)
{
    VOS_UINT32                                   i;
    CNAS_HSD_LOG_SCAN_FREQ_LIST_MSG_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_HSD_LOG_SCAN_FREQ_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                          (sizeof(CNAS_HSD_LOG_SCAN_FREQ_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogScanFreqList:Alloc Memory Failed");

        return;
    }
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_SCAN_FREQ_LIST_IND;

    pstMsg->enMsgLogType                = enMsgLogType;
    pstMsg->usTotalItemNum              = pstScanFreqList->usAvailFreqNum;
    pstMsg->usCurScanIndex              = pstScanFreqList->usCurrIndex;
    pstMsg->ucLowPrioLevel              = pstScanFreqList->ucLowPrioLevel;

    for (i = 0; i < pstScanFreqList->usAvailFreqNum; i++)
    {
        if (i >= CNAS_HSD_MAX_LOG_FREQ_NUM_IN_SCAN_LIST)
        {
            break;
        }

        pstMsg->astScanFreqList[i] = pstScanFreqList->pstScanFreqItem[i];
    }

    pstMsg->stMsgHeader.ulLength        = PS_OFFSET_OF(CNAS_HSD_LOG_SCAN_FREQ_LIST_MSG_STRU, astScanFreqList)
                                          - VOS_MSG_HEAD_LENGTH
                                          + (pstMsg->usTotalItemNum * sizeof(CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_SCAN_FREQ_LIST_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_LogSysRecList
 功能描述  : 将系统捕获列表导出到SDT LOG中
 输入参数  : pstSysRecList - SYS RECORD 列表
             enMsgLogType  - SYS RECORD产生场景

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_LogSysRecList(
    CNAS_HSD_HRPD_SYS_LIST_STRU                  *pstSysRecList,
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32            enMsgLogType
)
{
    VOS_UINT32                                    i;
    CNAS_HSD_LOG_HRPD_SYS_LIST_MSG_STRU          *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_HSD_LOG_HRPD_SYS_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                          (sizeof(CNAS_HSD_LOG_HRPD_SYS_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogSysRecList:Alloc Memory Failed");

        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_HRPD_SYS_LIST_IND;

    pstMsg->enMsgLogType                = enMsgLogType;

    pstMsg->usSysNum   = pstSysRecList->usHrpdSysNum;

    for (i = 0; i < pstSysRecList->usHrpdSysNum; i++)
    {
        if (i >= CNAS_HSD_MAX_LOG_HRPD_SYS_NUM)
        {
            break;
        }

        pstMsg->astSysRecList[i] = pstSysRecList->pstHrpdSysItem[i];
    }

    pstMsg->stMsgHeader.ulLength        = PS_OFFSET_OF(CNAS_HSD_LOG_HRPD_SYS_LIST_MSG_STRU, astSysRecList)
                                          - VOS_MSG_HEAD_LENGTH
                                          + (pstMsg->usSysNum* sizeof(CNAS_HSD_HRPD_SYS_REC_ITEM_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_HRPD_SYS_LIST_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_LogMruList
 功能描述  : 将MRU列表导出到SDT LOG中
 输入参数  : pstMruList   - 待导出MRU列表
             enMruLogType - MRU 列表更新场景

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月16日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_LogMruList(
    CNAS_HSD_HRPD_MRU_LIST_STRU                  *pstMruList,
    CNAS_HSD_MNTN_MRU_LOG_TYPE_ENUM_UINT8         enMruLogType
)
{
    VOS_UINT32                                    i;
    CNAS_HSD_LOG_MRU_LIST_MSG_STRU               *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_HSD_LOG_MRU_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                          (sizeof(CNAS_HSD_LOG_MRU_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogMruList:Alloc Memory Failed");

        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_MRU_LIST_IND;

    pstMsg->enMruLogType                = enMruLogType;

    pstMsg->ucSysNum    = pstMruList->ucCurrMruNum;

    for (i = 0; i < CNAS_MIN(pstMruList->ucCurrMruNum, CNAS_HSD_MAX_MRU_SYS_NUM); i++)
    {
        pstMsg->astSystem[i] = pstMruList->astHrpdSys[i];
    }

    pstMsg->stMsgHeader.ulLength        = PS_OFFSET_OF(CNAS_HSD_LOG_MRU_LIST_MSG_STRU, astSystem)
                                          - VOS_MSG_HEAD_LENGTH
                                          + (pstMsg->ucSysNum * sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_MRU_LIST_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_LogOocScheduleInfo
 功能描述  : 将OOC timer调度信息导出到SDT LOG中
 输入参数  : pstOocTimerScheduleInfo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月13日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_LogOocScheduleInfo(
    CNAS_NVIM_HRPD_OOC_TIMER_SCHEDULE_INFO_STRU            *pstOocTimerScheduleInfo
)
{
    VOS_UINT8                                               i;
    CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU          *pstMsg               = VOS_NULL_PTR;
    pstMsg = (CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                          sizeof(CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogOocScheduleInfo:Alloc Memory Failed");

        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_OOC_TIMER_SCHEDULE_IND;
    pstMsg->stMsgHeader.ulLength        = sizeof(CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucMru0SearchTimerLen        = pstOocTimerScheduleInfo->ucMru0SearchTimerLen;
    pstMsg->ucPhaseNum                  = pstOocTimerScheduleInfo->ucPhaseNum;

    for (i = 0; i < pstOocTimerScheduleInfo->ucPhaseNum; i++)
    {
        pstMsg->astOocTimerInfo[i].usTimes    = pstOocTimerScheduleInfo->astOocTimerInfo[i].usTimes;
        pstMsg->astOocTimerInfo[i].usTimerLen = pstOocTimerScheduleInfo->astOocTimerInfo[i].usTimerLen;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_LogOocCtxInfo
 功能描述  : log OOC上下文信息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : Z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_LogOocCtxInfo(
    CNAS_HSD_OOC_CTX_INFO_STRU         *pstOocCtxInfo
)
{
    CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                                                                sizeof(CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogOocCtxInfo: Alloc Memory Failed!");

        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU));

    /* 更新消息头信息 */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_OOC_CTX_INFO_IND;
    pstMsg->stMsgHeader.ulLength        = sizeof(CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 设置消息体内容 */
    pstMsg->ucWaitSearchFlag            = pstOocCtxInfo->ucWaitSearchFlag;
    pstMsg->ucCurrentPhase              = pstOocCtxInfo->ucCurrentPhase;
    pstMsg->usCurrentTimes              = pstOocCtxInfo->usCurrentTimes;
    pstMsg->ucSceneSetFlag              = pstOocCtxInfo->ucSceneSetFlag;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_HSD_LogAvoidFreqList
 功能描述  : 将avoid 频点列表导出到SDT LOG中
 输入参数  : pstAvoidFreqList
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月07日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_LogAvoidFreqList(
    CNAS_HSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList
)
{
    VOS_UINT8                                               i;
    CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                                                                   sizeof(CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogAvoidFreqList: Alloc Memory Failed!");

        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_AVOID_FREQ_LIST_IND;
    pstMsg->stMsgHeader.ulLength        = sizeof(CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucAvoidItemUsedNum          = pstAvoidFreqList->ucAvoidItemUsedNum;

    for (i  = 0; i < CNAS_HSD_AVOID_REASON_MAX; i++)
    {
        pstMsg->aucCounter[i]           = pstAvoidFreqList->aucCounter[i];
    }

    for (i = 0; i < CNAS_HSD_MAX_AVOID_FREQ_NUM; i++)
    {
        pstMsg->astAvoidFreqInfo[i].enUsedFlag        = pstAvoidFreqList->astAvoidFreqInfo[i].enUsedFlag;
        pstMsg->astAvoidFreqInfo[i].stAvoidFreq       = pstAvoidFreqList->astAvoidFreqInfo[i].stAvoidFreq;
        pstMsg->astAvoidFreqInfo[i].ulStartSlice      = pstAvoidFreqList->astAvoidFreqInfo[i].ulStartSlice;
        pstMsg->astAvoidFreqInfo[i].ulExpiredSliceNum = pstAvoidFreqList->astAvoidFreqInfo[i].ulExpiredSliceNum;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_LogRedirectionFreqList
 功能描述  : 将收到的重定向频点法向LOG工具中
 输入参数  : pstRedirection   - 收到的重定向列表频点

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月20日
    作    者   : d00212987
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_LogRedirectionFreqList(
    CNAS_HSD_REDIRECTION_STRU           *pstRedirection
)
{
    CNAS_HSD_LOG_REDIRCT_MSG_STRU      *pstMsg;

    pstMsg = (CNAS_HSD_LOG_REDIRCT_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                          (sizeof(CNAS_HSD_LOG_REDIRCT_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogRedirectionFreqList:Alloc Memory Failed");

        return;
    }

    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_HSD;
    pstMsg->ulReceiverPid           = UEPS_PID_HSD;
    pstMsg->enMsgId                 = ID_CNAS_HSD_MNTN_LOG_REDIRECT_FREQ_LIST_IND;

    pstMsg->enNetworkLostReason     = CAS_CNAS_HRPD_NETWORK_LOST_REDIRECT;

    pstMsg->ucChanNum               = pstRedirection->ucChanNum;

    PS_MEM_CPY( pstMsg->aulChannel,
                pstRedirection->aulChannel,
                (sizeof(CAS_CNAS_HRPD_DERECTION_CHANNEL_STRU) * pstMsg->ucChanNum) );

    pstMsg->ulLength        = PS_OFFSET_OF(CNAS_HSD_LOG_REDIRCT_MSG_STRU, aulChannel)
                                           - VOS_MSG_HEAD_LENGTH
                                           + (pstMsg->ucChanNum * sizeof(CAS_CNAS_HRPD_DERECTION_CHANNEL_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_REDIRCT_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_LogOperLockWhiteSidList
 功能描述  : 勾取OPER LOCK WHITE SID列表
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月1日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_LogOperLockSysWhiteList(
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstMsg
)
{
    CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU             *pstOperLockSysWhiteList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstOperLockSysWhiteList = (CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                                                                sizeof(CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU));
    if (VOS_NULL_PTR == pstOperLockSysWhiteList)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogOperLockSysWhiteList: Alloc Memory Failed!");

        return;
    }

    PS_MEM_SET(pstOperLockSysWhiteList, 0, sizeof(CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU));

    /* 更新消息头信息 */
    pstOperLockSysWhiteList->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstOperLockSysWhiteList->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstOperLockSysWhiteList->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstOperLockSysWhiteList->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstOperLockSysWhiteList->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_OPER_LOCK_WHITE_SID_LIST_IND;
    pstOperLockSysWhiteList->stMsgHeader.ulLength        = sizeof(CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 设置消息体内容 */
    pstOperLockSysWhiteList->ucEnable      = pstMsg->ucEnable;

    pstOperLockSysWhiteList->usWhiteSysNum = CNAS_MIN(pstMsg->usWhiteSysNum, CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM);

    for (i = 0; i < pstOperLockSysWhiteList->usWhiteSysNum;i++)
    {
        pstOperLockSysWhiteList->astSysInfo[i].usStartSid = pstMsg->astSysInfo[i].usStartSid;
        pstOperLockSysWhiteList->astSysInfo[i].usEndSid   = pstMsg->astSysInfo[i].usEndSid;
        pstOperLockSysWhiteList->astSysInfo[i].ulMcc      = pstMsg->astSysInfo[i].ulMcc;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU), (VOS_VOID *)pstOperLockSysWhiteList);

    PS_MEM_FREE(UEPS_PID_HSD, pstOperLockSysWhiteList);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_HSD_LogCTCCCustomizeFreqList
 功能描述  : 勾取中国电信自定义频点列表
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月1日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_LogCTCCCustomizeFreqList(
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstMsg
)
{
    CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU             *pstCustFreqList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstCustFreqList = (CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                                                                sizeof(CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU));
    if (VOS_NULL_PTR == pstCustFreqList)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogCTCCCustomizeFreqList: Alloc Memory Failed!");

        return;
    }

    PS_MEM_SET(pstCustFreqList, 0, sizeof(CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU));

    /* 更新消息头信息 */
    pstCustFreqList->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCustFreqList->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstCustFreqList->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstCustFreqList->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCustFreqList->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_CTCC_CUSTOMIZE_FREQ_LIST_IND;
    pstCustFreqList->stMsgHeader.ulLength        = sizeof(CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 设置消息体内容 */
    pstCustFreqList->ucEnableFlg = pstMsg->ucEnableFlg;
    pstCustFreqList->usFreqNum   = CNAS_MIN(pstMsg->usFreqNum, CNAS_CCB_MAX_FREQ_NUM);

    for (i = 0; i < pstCustFreqList->usFreqNum;i++)
    {
        pstCustFreqList->astFreqList[i].usChannel   = pstMsg->astFreqList[i].usChannel;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU), (VOS_VOID *)pstCustFreqList);

    PS_MEM_FREE(UEPS_PID_HSD, pstCustFreqList);

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
  1.日    期   : 2015年08月18日
    作    者   : x00306642
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSD_LogPrlSourceType(
    CNAS_HSD_PRL_SOURCE_TYPE_ENUM_UINT8 enPrlSrcType
)
{
    CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                                                                   sizeof(CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogPrlSourceType: Alloc Memory Failed!");

        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_PRL_SOURCE_TYPE_IND;
    pstMsg->stMsgHeader.ulLength        = sizeof(CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enPrlSrcType                = enPrlSrcType;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




