


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_DEBUG_C
/*lint +e767*/


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AdsDebug.h"
#include "AdsCtx.h"


/*****************************************************************************
  2 外部函数声明
*****************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
******************************************************************************/

ADS_STATS_INFO_STRU                     g_stAdsStats;
ADS_LOG_LEVEL_ENUM_UINT32               g_enAdsLogLevel = ADS_LOG_LEVEL_ERROR;


/******************************************************************************
   5 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : ADS_SetWakeTxTmrLen
 功能描述  : 设置数据发送持锁时长
 输入参数  : VOS_UINT32 ulValue
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_SetTxWakeLockTmrLen(VOS_UINT32 ulValue)
{
    g_stAdsCtx.stAdsIpfCtx.ulTxWakeLockTmrLen = ulValue;
    return;
}

/*****************************************************************************
 函 数 名  : ADS_SetWakeRxTmrLen
 功能描述  : 设置数据接收持锁时长
 输入参数  : VOS_UINT32 ulValue
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月22日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_SetRxWakeLockTmrLen(VOS_UINT32 ulValue)
{
    g_stAdsCtx.stAdsIpfCtx.ulRxWakeLockTmrLen = ulValue;
    return;
}

/*****************************************************************************
 函 数 名  : ADS_SetMaxQueueLength
 功能描述  : 为了调试需要，支持动态调整上行队列长度
 输入参数  : VOS_UINT32                          ulLength,
             VOS_UINT8                           ucInstanceIndex
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月3日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_SetMaxQueueLength(
    VOS_UINT32                          ulLength,
    VOS_UINT8                           ucInstanceIndex
)
{
    g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.ulUlMaxQueueLength = ulLength;
}

/*****************************************************************************
 函 数 名  : ADS_ShowEntityStats
 功能描述  : 显示ADS实体状态
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年04月12日
      作    者   : A00165503
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_ShowEntityStats(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;

    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        PS_PRINTF("ADS Modem ID %d\n", i);

        for (j = ADS_RAB_ID_MIN; j <= ADS_RAB_ID_MAX; j++)
        {
            if (VOS_NULL_PTR != g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].pstAdsUlLink)
            {
                PS_PRINTF("ADS Queue length is %d\n", IMM_ZcQueueLen(g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].pstAdsUlLink));
            }

            PS_PRINTF("ADS DL RabId is %d\r\n", g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx.astAdsDlRabInfo[j - ADS_RAB_ID_OFFSET].ucRabId);
            PS_PRINTF("ADS DL Rcv Func is 0x%x\r\n", g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx.astAdsDlRabInfo[j - ADS_RAB_ID_OFFSET].pRcvDlDataFunc);
        }
    }

    PS_PRINTF("ADS上行正在发送标识              %d\n",g_stAdsCtx.stAdsIpfCtx.ucSendingFlg);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : ADS_ShowEventProcStats
 功能描述  : 显示事件处理统计
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_ShowEventProcStats(VOS_VOID)
{
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS EVENT PROC STATS                         \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ULQueNonEmptyTrigEvent           %10u\n", g_stAdsStats.stUlComStatsInfo.ulULQueNonEmptyTrigEvent);
    PS_PRINTF("ULQueFullTrigEvent               %10u\n", g_stAdsStats.stUlComStatsInfo.ulULQueFullTrigEvent);
    PS_PRINTF("ULQueHitThresTrigEvent           %10u\n", g_stAdsStats.stUlComStatsInfo.ulULQueHitThresTrigEvent);
    PS_PRINTF("ULTmrHitThresTrigEvent           %10u\n", g_stAdsStats.stUlComStatsInfo.ulULTmrHitThresTrigEvent);
    PS_PRINTF("UL10MsTmrTrigEvent               %10u\n", g_stAdsStats.stUlComStatsInfo.ulUL10MsTmrTrigEvent);
    PS_PRINTF("ULSpeIntTrigEvent                %10u\n", g_stAdsStats.stUlComStatsInfo.ulULSpeIntTrigEvent);
    PS_PRINTF("ULProcEventNum                   %10u\n", g_stAdsStats.stUlComStatsInfo.ulULProcEventNum);
    PS_PRINTF("DLRcvIpfRdIntNum                 %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRcvIpfRdIntNum);
    PS_PRINTF("DLProcIpfRdEventNum              %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLProcIpfRdEventNum);
    PS_PRINTF("DLRcvIpfAdqEmptyIntNum           %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRcvIpfAdqEmptyIntNum);
    PS_PRINTF("DLProcIpfAdqEmptyEventNum        %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLProcIpfAdqEmptyEventNum);
    PS_PRINTF("DLCCoreResetTrigEvent            %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLCCoreResetTrigEvent);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : ADS_ShowULPktProcStats
 功能描述  : 显示上行数据处理统计
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_ShowULPktProcStats(VOS_VOID)
{
    VOS_UINT8                           ucInstance;

    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS UL PTK PROC STATS                        \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ULRmnetRxPktNum                  %10u\n", g_stAdsStats.stUlComStatsInfo.ulULRmnetRxPktNum);
    PS_PRINTF("ULRmnetEnQueSuccNum              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULRmnetEnQueSuccNum);
    PS_PRINTF("ULRmnetEnQueFailNum              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULRmnetEnQueFailNum);
    PS_PRINTF("ULPktEnQueSuccNum                %10u\n", g_stAdsStats.stUlComStatsInfo.ulULPktEnQueSuccNum);
    PS_PRINTF("ULPktEnQueFailNum                %10u\n", g_stAdsStats.stUlComStatsInfo.ulULPktEnQueFailNum);

    for (ucInstance = 0; ucInstance < ADS_INSTANCE_MAX_NUM; ucInstance++)
    {
        PS_PRINTF("ULBuffPktNum[MDOEM:%d]            %10u\n", ucInstance, ADS_UL_GetInstanceAllQueueDataNum(ucInstance));
    }

    PS_PRINTF("ULBuffThresholdCurrent           %10u\n", g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum);
    PS_PRINTF("ULBuffThreshold1                 %10u\n", g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold1);
    PS_PRINTF("ULBuffThreshold2                 %10u\n", g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold1);
    PS_PRINTF("ULBuffThreshold3                 %10u\n", g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold1);
    PS_PRINTF("ULBuffThreshold4                 %10u\n", g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold1);
    PS_PRINTF("ULWaterLevel1HitNum              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULWmLevel1HitNum);
    PS_PRINTF("ULWaterLevel2HitNum              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULWmLevel2HitNum);
    PS_PRINTF("ULWaterLevel3HitNum              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULWmLevel3HitNum);
    PS_PRINTF("ULWaterLevel4HitNum              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULWmLevel4HitNum);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : ADS_ShowULBdProcStats
 功能描述  : 显示上行BD处理统计
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_ShowULBdProcStats(VOS_VOID)
{
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS UL BD PROC STATS                         \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ULBdqCfgIpfHaveNoBd              %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqCfgIpfHaveNoBd);
    PS_PRINTF("ULBdqCfgBdSuccNum                %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqCfgBdSuccNum);
    PS_PRINTF("ULBdqCfgBdFailNum                %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqCfgBdFailNum);
    PS_PRINTF("ULBdqCfgIpfSuccNum               %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqCfgIpfSuccNum);
    PS_PRINTF("ULBdqCfgIpfFailNum               %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqCfgIpfFailNum);
    PS_PRINTF("ULBdqSaveSrcMemNum               %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqSaveSrcMemNum);
    PS_PRINTF("ULBdqFreeSrcMemNum               %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqFreeSrcMemNum);
    PS_PRINTF("ULBdqFreeSrcMemErr               %10u\n", g_stAdsStats.stUlComStatsInfo.ulULBdqFreeSrcMemErr);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : ADS_ShowDLPktProcStats
 功能描述  : 显示下行数据处理统计
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月26日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_ShowDLPktProcStats(VOS_VOID)
{
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS DL PKT PROC STATS                        \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("DLRmnetTxPktNum                  %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRmnetTxPktNum);
    PS_PRINTF("DLRmnetModemIdErrNum             %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRmnetModemIdErrNum);
    PS_PRINTF("DLRmnetRabIdErrNum               %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRmnetRabIdErrNum);
    PS_PRINTF("DLRmnetNoFuncFreePktNum          %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRmnetNoFuncFreePktNum);
    PS_PRINTF("\r\n");

    return;
 }

/*****************************************************************************
 函 数 名  : ADS_ShowDLRdProcStats
 功能描述  : 显示下行RD处理统计
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_ShowDLRdProcStats(VOS_VOID)
{
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS DL RD PROC STATS                         \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("DLRdqRxRdNum                     %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqRxRdNum);
    PS_PRINTF("DLRdqGetRd0Num                   %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqGetRd0Num);
    PS_PRINTF("DLRdqTransMemFailNum             %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqTransMemFailNum);
    PS_PRINTF("DLRdqRxNormPktNum                %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqRxNormPktNum);
    PS_PRINTF("DLRdqRxNdPktNum                  %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqRxNdPktNum);
    PS_PRINTF("DLRdqRxDhcpPktNum                %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqRxDhcpPktNum);
    PS_PRINTF("DLRdqRxErrPktNum                 %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqRxErrPktNum);
    PS_PRINTF("DLRdqFilterErrNum                %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLRdqFilterErrNum);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : ADS_ShowDLAdProcStats
 功能描述  : 显示下行AD处理统计
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_ShowDLAdProcStats(VOS_VOID)
{
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS DL ADQ PROC STATS                        \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("DLAdqAllocSysMemSuccNum          %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqAllocSysMemSuccNum);
    PS_PRINTF("DLAdqAllocSysMemFailNum          %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqAllocSysMemFailNum);
    PS_PRINTF("DLAdqAllocMemSuccNum             %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqAllocMemSuccNum);
    PS_PRINTF("DLAdqAllocMemFailNum             %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqAllocMemFailNum);
    PS_PRINTF("DLAdqFreeMemNum                  %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqFreeMemNum);
    PS_PRINTF("DLAdqRecycleMemSuccNum           %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqRecycleMemSuccNum);
    PS_PRINTF("DLAdqRecycleMemFailNum           %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqRecycleMemFailNum);
    PS_PRINTF("DLAdqGetFreeAdSuccNum            %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqGetFreeAdSuccNum);
    PS_PRINTF("DLAdqGetFreeAdFailNum            %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqGetFreeAdFailNum);
    PS_PRINTF("DLAdqCfgAdNum                    %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgAdNum);
    PS_PRINTF("DLAdqCfgAd0Num                   %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgAd0Num);
    PS_PRINTF("DLAdqCfgAd1Num                   %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgAd1Num);
    PS_PRINTF("DLAdqCfgIpfSuccNum               %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgIpfSuccNum);
    PS_PRINTF("DLAdqCfgIpfFailNum               %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqCfgIpfFailNum);
    PS_PRINTF("DLAdqStartEmptyTmrNum            %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqStartEmptyTmrNum);
    PS_PRINTF("DLAdqEmptyTmrTimeoutNum          %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqEmptyTmrTimeoutNum);
    PS_PRINTF("DLAdqRcvAd0EmptyIntNum           %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqRcvAd0EmptyIntNum);
    PS_PRINTF("DLAdqRcvAd1EmptyIntNum           %10u\n", g_stAdsStats.stDlComStatsInfo.ulDLAdqRcvAd1EmptyIntNum);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : ADS_ShowResetProcStats
 功能描述  : 显示C核复位处理统计
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_ShowResetProcStats(VOS_VOID)
{
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ADS RESET PROC STATS                         \n");
    PS_PRINTF("=============================================\n");
    PS_PRINTF("ULResetSem                       %p\n",   g_stAdsCtx.hULResetSem);
    PS_PRINTF("ULResetCreateSemFailNum          %10u\n", g_stAdsStats.stResetStatsInfo.ulULResetCreateSemFailNum);
    PS_PRINTF("ULResetLockFailNum               %10u\n", g_stAdsStats.stResetStatsInfo.ulULResetLockFailNum);
    PS_PRINTF("ULResetSuccNum                   %10u\n", g_stAdsStats.stResetStatsInfo.ulULResetSuccNum);
    PS_PRINTF("DLResetSem                       %p\n",   g_stAdsCtx.hDLResetSem);
    PS_PRINTF("DLResetCreateSemFailNum          %10u\n", g_stAdsStats.stResetStatsInfo.ulDLResetCreateSemFailNum);
    PS_PRINTF("DLResetLockFailNum               %10u\n", g_stAdsStats.stResetStatsInfo.ulDLResetLockFailNum);
    PS_PRINTF("DLResetSuccNum                   %10u\n", g_stAdsStats.stResetStatsInfo.ulDLResetSuccNum);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : ADS_Help
 功能描述  : ADS软调信息入口
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月12日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_Help(VOS_VOID)
{
    PS_PRINTF("=================================================\n");
    PS_PRINTF("ADS DEBUG ENTRY                                  \n");
    PS_PRINTF("=================================================\n");
    PS_PRINTF("ADS_ShowEntityStats          显示实体信息\n");
    PS_PRINTF("ADS_ShowEventProcStats       显示事件统计信息\n");
    PS_PRINTF("ADS_ShowULPktProcStats       显示上行数据统计信息\n");
    PS_PRINTF("ADS_ShowULBdProcStats        显示上行BD统计信息\n");
    PS_PRINTF("ADS_ShowDLPktProcStats       显示下行数据统计信息\n");
    PS_PRINTF("ADS_ShowDLRdProcStats        显示下行RD统计信息\n");
    PS_PRINTF("ADS_ShowDLAdProcStats        显示下行AD统计信息\n");
    PS_PRINTF("ADS_ShowResetProcStats       显示C核复位统计信息\n");
    PS_PRINTF("ADS_ResetDebugInfo           重置统计信息\n");
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : ADS_ResetDebugInfo
 功能描述  : 复位ADS的可维可测信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月13日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_ResetDebugInfo(VOS_VOID)
{
    PS_MEM_SET(&g_stAdsStats.stUlComStatsInfo, 0x00, sizeof(ADS_UL_COM_STATS_INFO_STRU));
    PS_MEM_SET(&g_stAdsStats.stDlComStatsInfo, 0x00, sizeof(ADS_DL_COM_STATS_INFO_STRU));
    return;
}

/*****************************************************************************
 函 数 名  : ADS_SetFlowDebugFlag
 功能描述  : 设置Flow Debug开关

 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年6月9日
      作    者   : c00199705
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_SetFlowDebugFlag(VOS_UINT32  ulFlowDebugFlag)
{
    switch (ulFlowDebugFlag)
    {
        case ADS_FLOW_DEBUG_DL_ON:
            g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag     = PS_TRUE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag     = PS_FALSE;
            g_stAdsStats.stDlComStatsInfo.ulDLFlowRptThreshold  = ADS_FLOW_DL_DEFAULT_RPT_THRESHOLD;
            break;

        case ADS_FLOW_DEBUG_UL_ON:
            g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag     = PS_FALSE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag     = PS_TRUE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowRptThreshold  = ADS_FLOW_UL_DEFAULT_RPT_THRESHOLD;
            break;

        case ADS_FLOW_DEBUG_ALL_ON:
            g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag     = PS_TRUE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag     = PS_TRUE;
            g_stAdsStats.stDlComStatsInfo.ulDLFlowRptThreshold  = ADS_FLOW_DL_DEFAULT_RPT_THRESHOLD;
            g_stAdsStats.stUlComStatsInfo.ulULFlowRptThreshold  = ADS_FLOW_UL_DEFAULT_RPT_THRESHOLD;
            break;

        default:
            g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag     = PS_FALSE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag     = PS_FALSE;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_SetFlowDLRptThreshold
 功能描述  : 设置下行流量上报门限

 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年6月9日
      作    者   : c00199705
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_SetFlowDLRptThreshold(VOS_UINT32  ulFlowDLRptThreshold)
{
    g_stAdsStats.stDlComStatsInfo.ulDLFlowRptThreshold  = ulFlowDLRptThreshold;
    return;
}

/*****************************************************************************
 函 数 名  : ADS_SetFlowUlRptThreshold
 功能描述  : 设置上行流量上报门限

 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年6月9日
      作    者   : c00199705
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_SetFlowULRptThreshold(VOS_UINT32  ulFlowULRptThreshold)
{
    g_stAdsStats.stUlComStatsInfo.ulULFlowRptThreshold  = ulFlowULRptThreshold;
    return;
}

/*****************************************************************************
 函 数 名  : ADS_DLFlowAdd
 功能描述  : ADS下行流量统计

 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年6月9日
      作    者   : c00199705
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_DLFlowAdd(VOS_UINT32 ulSduLen)
{
    if (PS_TRUE == g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag)
    {
        /* 流量统计 */
        g_stAdsStats.stDlComStatsInfo.ulDLFlowInfo += ulSduLen;

        /* 流量统计上报 */
        if (g_stAdsStats.stDlComStatsInfo.ulDLFlowInfo >= g_stAdsStats.stDlComStatsInfo.ulDLFlowRptThreshold)
        {
            g_stAdsStats.stDlComStatsInfo.ulDLEndSlice   = VOS_GetSlice();

            PS_PRINTF("ADS DL Flow Info = %10d, Pkt Num = %10d, Slice = %10d, Time = %10d\n",
                g_stAdsStats.stDlComStatsInfo.ulDLFlowInfo,
                g_stAdsStats.stDlComStatsInfo.ulDLRmnetTxPktNum, g_stAdsStats.stDlComStatsInfo.ulDLEndSlice,
                (g_stAdsStats.stDlComStatsInfo.ulDLEndSlice - g_stAdsStats.stDlComStatsInfo.ulDLStartSlice));

            g_stAdsStats.stDlComStatsInfo.ulDLStartSlice = g_stAdsStats.stDlComStatsInfo.ulDLEndSlice;
            g_stAdsStats.stDlComStatsInfo.ulDLFlowInfo   = 0;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_ULFlowAdd
 功能描述  : ADS上行流量统计

 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2014年6月9日
      作    者   : c00199705
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_ULFlowAdd(VOS_UINT32 ulSduLen)
{
    if (PS_TRUE == g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag)
    {
        /* 流量统计 */
        g_stAdsStats.stUlComStatsInfo.ulULFlowInfo += ulSduLen;

        /* 流量统计上报 */
        if (g_stAdsStats.stUlComStatsInfo.ulULFlowInfo >= g_stAdsStats.stUlComStatsInfo.ulULFlowRptThreshold)
        {
            g_stAdsStats.stUlComStatsInfo.ulULEndSlice   = VOS_GetSlice();

            PS_PRINTF("ADS UL Flow Info = %10d, Pkt Num = %10d, Slice = %10d, Time = %10d\n",
                g_stAdsStats.stUlComStatsInfo.ulULFlowInfo,
                g_stAdsStats.stUlComStatsInfo.ulULRmnetRxPktNum, g_stAdsStats.stUlComStatsInfo.ulULEndSlice,
                (g_stAdsStats.stUlComStatsInfo.ulULEndSlice - g_stAdsStats.stUlComStatsInfo.ulULStartSlice));

            g_stAdsStats.stUlComStatsInfo.ulULStartSlice = g_stAdsStats.stUlComStatsInfo.ulULEndSlice;
            g_stAdsStats.stUlComStatsInfo.ulULFlowInfo   = 0;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_LogPrintf
 功能描述  : LOG打印
 输入参数  : enLevel --- 打印级别
             pcFmt   --- 变参
             ...
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -esym(960,69)*/
VOS_VOID ADS_LogPrintf(ADS_LOG_LEVEL_ENUM_UINT32 enLevel, VOS_CHAR *pcFmt, ...)
{
    VOS_CHAR                            acBuff[ADS_LOG_BUFF_LEN] = {0};
    va_list                             pArgList;
    VOS_UINT32                          ulPrintLength = 0;

    /* 打印级别过滤 */
    if (enLevel < g_enAdsLogLevel)
    {
        return;
    }

    /*lint -e586*/
    va_start(pArgList, pcFmt);
    ulPrintLength += VOS_nvsprintf(acBuff, ADS_LOG_BUFF_LEN, pcFmt, pArgList);
    va_end(pArgList);
    /*lint +e586*/

    if (ulPrintLength > (ADS_LOG_BUFF_LEN - 1))
    {
        ulPrintLength = ADS_LOG_BUFF_LEN - 1;
    }

    acBuff[ulPrintLength] = '\0';

#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "%s", acBuff);
#else
    PS_PRINTF("%s", acBuff);
#endif

    return ;
}
/*lint +esym(960,69)*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


