/******************************************************************************

                  版权所有 (C), 2006, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsDebug.c
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2011年12月12日
  最近修改   :
  功能描述   : CDS软调信息
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月12日
    作    者   : l00164359
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CdsDebug.h"
#include "CDS.h"
#include "CdsIpfCtrl.h"
#include "CdsIpFragmentProc.h"

#define CDS_FLOW_DL_DEFAULT_RPT_THRESHOLD   (5000000)
#define CDS_FLOW_UL_DEFAULT_RPT_THRESHOLD   (500000)

CDS_STATS_INFO_STRU    g_stCdsStats = {0};

VOS_UINT32   g_ulCdsOmSwitch = 0;

/*****************************************************************************
  2 外部函数声明
*****************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
******************************************************************************/


/******************************************************************************
   5 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : CDS_SetDbgRptBearerId
 功能描述  : 设置Debug信息上报承载的ID

 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月8日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_SetDbgRptBearerId(VOS_UINT8  ucEpsbId)
{
    /*LTE默认放在Modem0*/
    g_astCdsEntity[MODEM_ID_0].ucDbgBearerId = ucEpsbId;
    return;
}

/*****************************************************************************
 函 数 名  : CDS_SetMbmsBearerId
 功能描述  : 设置MBMS承载的ID

 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月8日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_SetMbmsBearerId(VOS_UINT8  ucEpsbId)
{
    /*LTE默认放在Modem0*/
    g_astCdsEntity[MODEM_ID_0].ucMbmsBearerId = ucEpsbId;
    return;
}

/*****************************************************************************
 函 数 名  : CDS_SetPktDiscardFlg
 功能描述  : 设置CDS上下行丢包开关. 测试需求用于IDLE态功能测试和性能测试
 输入参数  : ulDir - 数传的方向，0代表上行，1代表下行
             ulFlg - 是否打开数据丢弃功能。
                      PS_TRUE代表数据包全部丢弃，PS_FALSE代表关闭丢包功能。

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年03月26日
      作    者   : y00151394
      修改内容   : 新增函数。
    2.日    期   : 2013年1月4日
      作    者   : y00151394
      修改内容   : 增加入参ModemId.

*****************************************************************************/
VOS_VOID CDS_SetPktDiscardFlg(MODEM_ID_ENUM_UINT16 enModemId,VOS_UINT32  ulDir, VOS_UINT32 ulFlg)
{
    CDS_ENTITY_STRU         *pstCdsEntity;

    pstCdsEntity = CDS_GetCdsEntity(enModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        return;
    }

    if (0 == ulDir)
    {
        pstCdsEntity->ulULPktDiscardFlg = ulFlg;
    }
    else
    {
        pstCdsEntity->ulDLPktDiscardFlg = ulFlg;
    }

    return ;
}

/*****************************************************************************
 函 数 名  : CDS_SetFlowDebugFlag
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
VOS_VOID CDS_SetFlowDebugFlag(VOS_UINT32  ulFlowDebugFlag)
{
    switch (ulFlowDebugFlag)
    {
        case CDS_FLOW_DEBUG_DL_ON:
            g_stCdsStats.ulDLFlowDebugFlag      = PS_TRUE;
            g_stCdsStats.ulULFlowDebugFlag      = PS_FALSE;
            g_stCdsStats.ulDLFlowRptThreshold   = CDS_FLOW_DL_DEFAULT_RPT_THRESHOLD;
            break;

        case CDS_FLOW_DEBUG_UL_ON:
            g_stCdsStats.ulDLFlowDebugFlag      = PS_FALSE;
            g_stCdsStats.ulULFlowDebugFlag      = PS_TRUE;
            g_stCdsStats.ulULFlowRptThreshold   = CDS_FLOW_UL_DEFAULT_RPT_THRESHOLD;
            break;

        case CDS_FLOW_DEBUG_ALL_ON:
            g_stCdsStats.ulDLFlowDebugFlag      = PS_TRUE;
            g_stCdsStats.ulULFlowDebugFlag      = PS_TRUE;
            g_stCdsStats.ulDLFlowRptThreshold   = CDS_FLOW_DL_DEFAULT_RPT_THRESHOLD;
            g_stCdsStats.ulULFlowRptThreshold   = CDS_FLOW_UL_DEFAULT_RPT_THRESHOLD;
            break;

        default:
            g_stCdsStats.ulDLFlowDebugFlag      = PS_FALSE;
            g_stCdsStats.ulULFlowDebugFlag      = PS_FALSE;
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_SetFlowDLRptThreshold
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
VOS_VOID CDS_SetFlowDLRptThreshold(VOS_UINT32  ulFlowDLRptThreshold)
{
    g_stCdsStats.ulDLFlowRptThreshold   = ulFlowDLRptThreshold;
    return;
}

/*****************************************************************************
 函 数 名  : CDS_SetFlowULRptThreshold
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
VOS_VOID CDS_SetFlowULRptThreshold(VOS_UINT32  ulFlowULRptThreshold)
{
    g_stCdsStats.ulULFlowRptThreshold   = ulFlowULRptThreshold;
    return;
}

/*****************************************************************************
 函 数 名  : CDS_DLFlowAdd
 功能描述  : 下行流量统计

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
VOS_VOID CDS_DLFlowAdd(VOS_UINT32  ulSduLen)
{
    if (PS_TRUE == g_stCdsStats.ulDLFlowDebugFlag)
    {
        /* 流量统计 */
        g_stCdsStats.ulDLFlowInfo += ulSduLen;

        /* 流量统计上报 */
        if (g_stCdsStats.ulDLFlowInfo >= g_stCdsStats.ulDLFlowRptThreshold)
        {
            g_stCdsStats.ulDLEndSlice   = VOS_GetSlice();

            PS_PRINTF("CDS DL Flow Info = %10d, Pkt Num = %10d, Slice = %10d, Time = %10d\n",
                g_stCdsStats.ulDLFlowInfo, g_stCdsStats.ulDLEnSduQueSucc, g_stCdsStats.ulDLEndSlice,
                (g_stCdsStats.ulDLEndSlice - g_stCdsStats.ulDLStartSlice));

            g_stCdsStats.ulDLStartSlice = g_stCdsStats.ulDLEndSlice;
            g_stCdsStats.ulDLFlowInfo   = 0;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ULFlowAdd
 功能描述  : 上行流量统计

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
VOS_VOID CDS_ULFlowAdd(VOS_UINT32  ulSduLen)
{
    if (PS_TRUE == g_stCdsStats.ulULFlowDebugFlag)
    {
        /* 流量统计 */
        g_stCdsStats.ulULFlowInfo += ulSduLen;

        /* 流量统计上报 */
        if (g_stCdsStats.ulULFlowInfo >= g_stCdsStats.ulULFlowRptThreshold)
        {
            g_stCdsStats.ulULEndSlice   = VOS_GetSlice();

            PS_PRINTF("CDS UL Flow Info = %10d, Pkt Num = %10d, Slice = %10d, Time = %10d\n",
                g_stCdsStats.ulULFlowInfo, g_stCdsStats.ulULASRxIpPktNum, g_stCdsStats.ulULEndSlice,
                (g_stCdsStats.ulULEndSlice - g_stCdsStats.ulULStartSlice));

            g_stCdsStats.ulULStartSlice = g_stCdsStats.ulULEndSlice;
            g_stCdsStats.ulULFlowInfo   = 0;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ShowEventStats
 功能描述  : 显示CDS事件处理统计量
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowEventStats(VOS_VOID)
{

    PS_PRINTF("上行收到IPF中断次数                          %d\n",g_stCdsStats.ulIpfULIntNum);
    PS_PRINTF("上行处理IPF中断次数                          %d\n",g_stCdsStats.ulULProcIpfIntNum);
    PS_PRINTF("上行收到ADQ空中断次数                        %d\n",g_stCdsStats.ulUlAdqEmtypIntNum);
    PS_PRINTF("上行处理ADQ空中断次数                        %d\n",g_stCdsStats.ulUlProcAdqEmptyIntNum);
    PS_PRINTF("下行IPF调用内存释放函数回调次数              %d\n",g_stCdsStats.ulIpfDlCallMemFreeNum);
    PS_PRINTF("下行IPF调用内存函数释放内存个数              %d\n",g_stCdsStats.ulIpfDlFreeMemNum);
    PS_PRINTF("下行10ms周期性定时器触发下行处理事件次数     %d\n",g_stCdsStats.ulDL10msTmrTrigEvent);
    PS_PRINTF("下行1ms子帧中断触发下行处理事件次数          %d\n",g_stCdsStats.ulDL1msIntTrigEvent);
    PS_PRINTF("下行UMTS DSP中断触发下行处理事件次数         %d\n",g_stCdsStats.ulDLUmtsIntTrigEvent);
    PS_PRINTF("下行处理下行处理事件次数                     %d\n",g_stCdsStats.ulDLProcEventNum);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ShowUlRdProcStats
 功能描述  : 显示CDS上行IPF RD处理统计
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowUlRdProcStats(VOS_VOID)
{
    PS_PRINTF("上行IPF收到RD个数                            %d\n",g_stCdsStats.ulULIpfRxRDNum);
    PS_PRINTF("上行RD内存转换失败个数                       %d\n",g_stCdsStats.ulULIpfTransMemFailNum);
    PS_PRINTF("上行IPF RD ModemID错误个数                   %d\n",g_stCdsStats.ulULIpfModemIdErrNum);
    PS_PRINTF("上行环回模式释放RD个数                       %d\n",g_stCdsStats.ulULIpfFreePktInLB);
    PS_PRINTF("上行收到IP包个数                             %d\n",g_stCdsStats.ulULIpfRxIpPktNum);
    PS_PRINTF("上行收到IP分片包个数                         %d\n",g_stCdsStats.ulULIpfRxIpSegNum);
    PS_PRINTF("上行收到NDIS包个数                           %d\n",g_stCdsStats.ulULIpfRxNdisPktNum);
    PS_PRINTF("上行IPF过滤错误个数                          %d\n",g_stCdsStats.ulULIpfFilterErrNum);

    PS_PRINTF("\r\n");
    return;
}

/*****************************************************************************
 函 数 名  : CDS_ShowUlAdqProcStats
 功能描述  : 显示CDS上行IPF ADQ处理统计
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowUlAdqProcStats(VOS_VOID)
{

    PS_PRINTF("上行ADQ分配内存个数                          %d\n",g_stCdsStats.ulULADQAllocMemNum);
    PS_PRINTF("上行ADQ配置失败释放内存个数                  %d\n",g_stCdsStats.ulULADQFreeMemNum);
    PS_PRINTF("上行配置AD 0内存个数                         %d\n",g_stCdsStats.ulULADQCfgAd0Num);
    PS_PRINTF("上行配置AD 1内存个数                         %d\n",g_stCdsStats.ulULADQCfgAd1Num);
    PS_PRINTF("上行配置AD内存总数(AD0+AD1)                  %d\n",g_stCdsStats.ulULADQCfgAdNum);
    PS_PRINTF("上行配置ADQ成功次数                          %d\n",g_stCdsStats.ulULADQCfgAdSucc);
    PS_PRINTF("上行配置ADQ失败次数                          %d\n",g_stCdsStats.ulULADQCfgAdFail);
    PS_PRINTF("上行启动ADQ空保护定时器次数                  %d\n",g_stCdsStats.ulULADQStartEmptyTmrNum);
    PS_PRINTF("上行停止ADQ空保护定时器次数                  %d\n",g_stCdsStats.ulULADQStopEmptyTmrNum);
    PS_PRINTF("上行ADQ空保护定时器超时次数                  %d\n",g_stCdsStats.ulULADQEmptyTmrTimeoutNum);
    PS_PRINTF("上行IPF ADQ空中断个数                        %d\n",g_stCdsStats.ulUlAdqEmtypIntNum);
    PS_PRINTF("上行IPF AD 0引起空中断个数                   %d\n",g_stCdsStats.ulULADQAd0EmptyIntNum);
    PS_PRINTF("上行IPF AD 1引起空中断个数                   %d\n",g_stCdsStats.ulULADQAd1EmptyIntNum);

    PS_PRINTF("\r\n");
    return;
}


/*****************************************************************************
 函 数 名  : CDS_ShowUlIpPktProcStats
 功能描述  : 显示CDS上行IP包处理统计
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowUlIpPktProcStats(VOS_VOID)
{

    PS_PRINTF("上行接入层收到的IP包总和                     %d\n",g_stCdsStats.ulULASRxIpPktNum);
    PS_PRINTF("上行打桩释放的IP包个数                       %d\n",g_stCdsStats.ulULDirectFreePktNum);
    PS_PRINTF("上行LTE模接收的IP包个数                      %d\n",g_stCdsStats.ulULLTERxPktNum);
    PS_PRINTF("上行GU模接收的IP包个数                       %d\n",g_stCdsStats.ulULGURxPktNum);
    PS_PRINTF("上行NULL模缓存IP包个数                       %d\n",g_stCdsStats.ulULNULLRxPktNum);
    PS_PRINTF("上行接入模式错误释放的IP包个数               %d\n",g_stCdsStats.ulULRanModeErrFreeNum);
    PS_PRINTF("\r\n");

    PS_PRINTF("LTE上行流控释放的IP包个数                    %d\n",g_stCdsStats.ulULLTEFcFreePktNum);
    PS_PRINTF("LTE上行处理IP分片失败IP包个数                %d\n",g_stCdsStats.ulULLTEProcIpSegFail);
    PS_PRINTF("LTE上行发送到LPDCP的IP包个数                 %d\n",g_stCdsStats.ulULLTESendToLPdcpNum);
    PS_PRINTF("LTE上行缓存IP包个数                          %d\n",g_stCdsStats.ulULLTESavePktNum);
    PS_PRINTF("LTE上行ERABM状态错误释放的IP包个数           %d\n",g_stCdsStats.ulULLTEERabmStateErr);
    PS_PRINTF("\r\n");

    PS_PRINTF("GU上行流控释放的IP包个数                     %d\n",g_stCdsStats.ulULGUFcFreePktNum);
    PS_PRINTF("GU上行发送到RABM的IP包个数                   %d\n",g_stCdsStats.ulULGUSendToRabmNum);
    PS_PRINTF("GU上行缓存IP包个数                           %d\n",g_stCdsStats.ulULGUSavePktNum);
    PS_PRINTF("GU上行RABM状态错误释放的IP包个数             %d\n",g_stCdsStats.ulULGURabmStateErr);
    PS_PRINTF("\r\n");

    PS_PRINTF("1x上行发送到RLP的IP包个数                    %d\n",g_stCdsStats.ulUL1xSendToRlpNum);
    PS_PRINTF("1x上行发送到PPP的IP包个数                    %d\n",g_stCdsStats.ulUL1xSendToPppNum);
    PS_PRINTF("1x上行缓存IP包个数                           %d\n",g_stCdsStats.ulUL1xSavePktNum);
    PS_PRINTF("1x上行RAB状态INACTIVE时释放的IP包个数        %d\n",g_stCdsStats.ulUL1xRabStateIna);
    PS_PRINTF("1x上行RAB状态错误释放的IP包个数              %d\n",g_stCdsStats.ulUL1xRabStateErr);
    PS_PRINTF("\r\n");

    PS_PRINTF("HRPD上行发送到PPP的IP包个数                  %d\n",g_stCdsStats.ulULHRPDSendToPppNum);
    PS_PRINTF("HRPD上行缓存IP包个数                         %d\n",g_stCdsStats.ulULHRPDSavePktNum);
    PS_PRINTF("HRPD上行RAB状态INACTIVE时释放的IP包个数      %d\n",g_stCdsStats.ulULHRPDRabStateIna);
    PS_PRINTF("HRPD上行RAB状态错误释放的IP包个数            %d\n",g_stCdsStats.ulULHRPDRabStateErr);
    PS_PRINTF("\r\n");

    PS_PRINTF("上行缓存入队成功个数                         %d\n",g_stCdsStats.ulULBuffEnQueSucc);
    PS_PRINTF("上行缓存入队失败个数                         %d\n",g_stCdsStats.ulULBuffEnQueFail);
    PS_PRINTF("上行缓存软过滤失败个数                       %d\n",g_stCdsStats.ulULBuffSoftFilterFail);
    PS_PRINTF("上行缓存发送IP包成功个数                     %d\n",g_stCdsStats.ulULBuffSendPktSuccNum);
    PS_PRINTF("上行缓存释放IP包个数                         %d\n",g_stCdsStats.ulULBuffFreePktNum);
    PS_PRINTF("\r\n");

    PS_PRINTF("上行IP包分类统计总和\n");
    PS_PRINTF("上行收到NDCLIENT包个数                       %d\n",g_stCdsStats.ulULRecvNdPktNum);
    PS_PRINTF("上行收到DHCP包个数                           %d\n",g_stCdsStats.ulULRecvDhcpPktNum);
    PS_PRINTF("上行收到环回数据包个数                       %d\n",g_stCdsStats.ulLBUlSendPktNum);
    PS_PRINTF("上行收到RD数据包总数                         %d\n",g_stCdsStats.ulULIpfRxIpPktNum + g_stCdsStats.ulULIpfRxIpSegNum);
    PS_PRINTF("上行缓存数据重新发送个数                     %d\n",g_stCdsStats.ulULBuffSendPktSuccNum);
    PS_PRINTF("上行按模式分发的数据包总和(ND+DHCP+LB+IP+BUFF)    %d\n",g_stCdsStats.ulULASRxIpPktNum);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ShowDlSduProcStats
 功能描述  : 显示下行SDU数传统计量
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowDlSduProcStats(VOS_VOID)
{

    PS_PRINTF("下行SDU数传统计\n\n");

    PS_PRINTF("下行GSM模接收SDU个数                         %d\n",g_stCdsStats.ulDLGSMRxSduNum);
    PS_PRINTF("下行GSM模接收IMS数据包个数                   %d\n",g_stCdsStats.ulDLGSMRxImsNum);
    PS_PRINTF("下行GSM模流控丢弃SDU个数                     %d\n",g_stCdsStats.ulDLGSMFcFreeSduNum);
    PS_PRINTF("下行GSM模环回模式下接收SDU个数               %d\n",g_stCdsStats.ulLBDLRxSduInGSM);
    PS_PRINTF("下行GSM获取缺省RABID失败个数                 %d\n",g_stCdsStats.ulDLGSMGetDeftRabIdFail);
    PS_PRINTF("下行GSM模入队成功个数                        %d\n",g_stCdsStats.ulDLGSMEnQueSucc);
    PS_PRINTF("下行GSM模入队失败个数                        %d\n",g_stCdsStats.ulDLGSMEnQueFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("下行UMTS模接收SDU个数                        %d\n",g_stCdsStats.ulDLUMTSRxSduNum);
    PS_PRINTF("下行UMTS模接收IMS数据包个数                  %d\n",g_stCdsStats.ulDLUMTSRxImsNum);
    PS_PRINTF("下行UMTS模流控丢弃SDU个数                    %d\n",g_stCdsStats.ulDLUMTSFcFreeSduNum);
    PS_PRINTF("下行UMTS模环回模式下接收SDU个数              %d\n",g_stCdsStats.ulLBDLRxSduInUMTS);
    PS_PRINTF("下行UMTS模打桩直接释放SDU个数                %d\n",g_stCdsStats.ulDLUMTSDirectFreeSduNum);
    PS_PRINTF("下行UMTS获取缺省RABID失败个数                %d\n",g_stCdsStats.ulDLUMTSGetDeftRabIdFail);
    PS_PRINTF("下行UMTS模入队成功个数                       %d\n",g_stCdsStats.ulDLUMTSEnQueSucc);
    PS_PRINTF("下行UMTS模入队失败个数                       %d\n",g_stCdsStats.ulDLUMTSEnQueFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("下行1x模接收SDU个数                          %d\n",g_stCdsStats.ulDL1xRxSduNum);
    PS_PRINTF("下行1x模打桩直接释放SDU个数                  %d\n",g_stCdsStats.ulDL1xDirectFreeSduNum);
    PS_PRINTF("下行1x获取DRB对应的RABID失败个数             %d\n",g_stCdsStats.ulDL1xGetRabIDFail);
    PS_PRINTF("下行1x获取DRB对应的默认RABID失败个数         %d\n",g_stCdsStats.ulDL1xGetDeftRabIDFail);
    PS_PRINTF("下行1x模入队成功个数                         %d\n",g_stCdsStats.ulDL1xEnQueSucc);
    PS_PRINTF("下行1x模入队失败个数                         %d\n",g_stCdsStats.ulDL1xEnQueFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("下行HRPD模接收SDU个数                        %d\n",g_stCdsStats.ulDLHRPDRxSduNum);
    PS_PRINTF("下行HRPD模打桩直接释放SDU个数                %d\n",g_stCdsStats.ulDLHRPDDirectFreeSduNum);
    PS_PRINTF("下行HRPD获取DRB对应的RABID失败个数           %d\n",g_stCdsStats.ulDLHRPDGetRabIDFail);
    PS_PRINTF("下行HRPD获取DRB对应的默认RABID失败个数       %d\n",g_stCdsStats.ulDLHRPDGetDeftRabIDFail);
    PS_PRINTF("下行HRPD模入队成功个数                       %d\n",g_stCdsStats.ulDLHRPDEnQueSucc);
    PS_PRINTF("下行HRPD模入队失败个数                       %d\n",g_stCdsStats.ulDLHRPDEnQueFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("下行LTE模接收SDU个数                         %d\n",g_stCdsStats.ulDLLteRxSduNum);
    PS_PRINTF("下行LTE模接收SDU长度错误个数                 %d\n",g_stCdsStats.ulDLLteRxSduLenErrNum);
    PS_PRINTF("下行LTE模接收IMS数据包个数                   %d\n",g_stCdsStats.ulDLLteRxImsNum);
    PS_PRINTF("下行LTE模流控丢弃SDU个数                     %d\n",g_stCdsStats.ulDLLteFcFreeSduNum);
    PS_PRINTF("下行LTE模打桩直接释放SDU个数                 %d\n",g_stCdsStats.ulDLLteDirectFreeSduNum);
    PS_PRINTF("下行LTE模环回模式下接收SDU个数               %d\n",g_stCdsStats.ulLBDLRxSduInLte);
    PS_PRINTF("下行LTE获取对应EPSBID失败个数                %d\n",g_stCdsStats.ulDLLteGetEpsbIDFail);
    PS_PRINTF("下行LTE获取缺省EPSBID失败个数                %d\n",g_stCdsStats.ulDLLteGetDeftEpsbIDFail);
    PS_PRINTF("下行LTE接收L2 Debug数据包个数                %d\n",g_stCdsStats.ulDLLteRxDbgPkt);
    PS_PRINTF("下行LTE接收MBMS数据包个数                    %d\n",g_stCdsStats.ulDLLteRxMbmsSdu);
    PS_PRINTF("下行LTE模入队成功个数                        %d\n",g_stCdsStats.ulDLLteEnQueSucc);
    PS_PRINTF("下行LTE模入队失败个数                        %d\n",g_stCdsStats.ulDLLteEnQueFail);


    PS_PRINTF("\r\n");

    PS_PRINTF("下行SDU队列当前缓存数据包个数               %d\n",LUP_QueCnt(CDS_GET_IPF_DL_SDU_QUE()));
    PS_PRINTF("下行SDU入队成功总数                          %d\n",g_stCdsStats.ulDLEnSduQueSucc);
    PS_PRINTF("下行SDU入队失败总数                          %d\n",g_stCdsStats.ulDLEnSduQueFail);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ShowDlIpfStats
 功能描述  : 显示下行IPF统计量
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowDlIpfProcStats(VOS_VOID)
{
    PS_PRINTF("下行IPF处理统计\n\n");

    PS_PRINTF("下行配置IPF没有BD次数                       %d\n",g_stCdsStats.ulDLIpfCfgHaveNoBD);
    PS_PRINTF("下行配置IPF没有CD次数                       %d\n",g_stCdsStats.ulDLIpfCfgHaveNoCD);
    PS_PRINTF("下行配置IPF CD不够次数                      %d\n",g_stCdsStats.ulDLIpfCfgCDNotEnough);
    PS_PRINTF("下行配置BD成功个数                          %d\n",g_stCdsStats.ulDLIpfCfgBDSucc);
    PS_PRINTF("下行配置BD失败个数                          %d\n",g_stCdsStats.ulDLIpfCfgBDFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("下行桥接模式保存源内存成功个数              %d\n",g_stCdsStats.ulDLIpfSaveSrcMemSucc);
    PS_PRINTF("下行桥接模式保存源内存失败个数              %d\n",g_stCdsStats.ulDLIpfSaveSrcMemFail);
    PS_PRINTF("下行桥接模式源内存释放队列当前个数          %d\n",LUP_QueCnt(CDS_IPF_DL_SRCMEM_FREE_QUE()));
    PS_PRINTF("下行桥接模式释放源内存成功个数              %d\n",g_stCdsStats.ulDLIpfFreeSrcMemNum);
    PS_PRINTF("下行桥接模式释放源内存失败个数              %d\n",g_stCdsStats.ulDLIpfFreeSrcMemErr);
    PS_PRINTF("\r\n");

    PS_PRINTF("下行非桥接模式IPF分配内存失败次数           %d\n",g_stCdsStats.ulDLIpfCfgBDAllocMemFail);
    PS_PRINTF("下行非桥接模式SDU长度错误个数               %d\n",g_stCdsStats.ulDLIpfCfgBDSduLenErr);
    PS_PRINTF("下行非桥接模式IPF调用内存释放函数回调次数   %d\n",g_stCdsStats.ulIpfDlCallMemFreeNum);
    PS_PRINTF("下行非桥接模式释放内存个数                  %d\n",g_stCdsStats.ulIpfDlFreeMemNum);

    PS_PRINTF("\r\n");

    return;
}


/*****************************************************************************
 函 数 名  : CDS_ShowLBProcStats
 功能描述  : 显示环回模式数传统计信息
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowLBProcStats(VOS_VOID)
{
    PS_PRINTF("环回模式处理统计\n\n");
    PS_PRINTF("环回下行从GSM接收的SDU个数                  %d\n",g_stCdsStats.ulLBDLRxSduInGSM);
    PS_PRINTF("环回下行从UMTS接收的SDU个数                 %d\n",g_stCdsStats.ulLBDLRxSduInUMTS);
    PS_PRINTF("环回下行从LTE接收的SDU个数                  %d\n",g_stCdsStats.ulLBDLRxSduInLte);
    PS_PRINTF("环回下行从CDMA接收的SDU个数                 %d\n",g_stCdsStats.ulLBDLRxSduInCDMA);
    PS_PRINTF("环回下行申请内存失败的个数                  %d\n",g_stCdsStats.ulLBDLAllocMemFail);
    PS_PRINTF("环回下行入队成功个数                        %d\n",g_stCdsStats.ulLBDDLEnQueSucc);
    PS_PRINTF("环回下行入队失败个数                        %d\n",g_stCdsStats.ulLBDLEnQueFail);
    PS_PRINTF("环回上行软过滤失败个数                      %d\n",g_stCdsStats.ulLBULSoftFilterFail);
    PS_PRINTF("环回上行发送到数据包个数                    %d\n",g_stCdsStats.ulLBUlSendPktNum);
    PS_PRINTF("环回上行清空队列释放数据包个数              %d\n",g_stCdsStats.ulLBUlClearPktNum);

    PS_PRINTF("\r\n");

    return;
}


/*****************************************************************************
 函 数 名  : CDS_ShowModemGUProcStats
 功能描述  : 显示不同Modem上GU的处理统计
 输入参数  : VOS_UINT16 usModemId
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年1月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowModemGUProcStats(VOS_UINT16 usModemId)
{

    if (usModemId >= MODEM_ID_BUTT)
    {
        PS_PRINTF("ModemId非法。输入ModemId=%d\n",usModemId);
        return;
    }

    PS_PRINTF("Modem %d上的GU数传统计信息\n",usModemId);
    PS_PRINTF("上行GU模接收的IP包个数                       %d\n",g_stCdsStats.astModemStats[usModemId].ulULGURxPktNum);
    PS_PRINTF("上行GU流控释放的IP包个数                     %d\n",g_stCdsStats.astModemStats[usModemId].ulULGUFcFreePktNum);
    PS_PRINTF("上行GU发送到RABM的IP包个数                   %d\n",g_stCdsStats.astModemStats[usModemId].ulULGUSendToRabmNum);
    PS_PRINTF("上行GU缓存IP包个数                           %d\n",g_stCdsStats.astModemStats[usModemId].ulULGUSavePktNum);
    PS_PRINTF("上行GU RABM状态错误释放的IP包个数            %d\n",g_stCdsStats.astModemStats[usModemId].ulULGURabmStateErr);
    PS_PRINTF("\r\n");

    PS_PRINTF("下行GSM模接收SDU个数                         %d\n",g_stCdsStats.astModemStats[usModemId].ulDLGSMRxSduNum);
    PS_PRINTF("下行GSM模接收IMS数据包个数                   %d\n",g_stCdsStats.astModemStats[usModemId].ulDLGSMRxImsNum);
    PS_PRINTF("下行GSM模流控丢弃SDU个数                     %d\n",g_stCdsStats.astModemStats[usModemId].ulDLGSMFcFreeSduNum);
    PS_PRINTF("下行GSM模环回模式下接收SDU个数               %d\n",g_stCdsStats.astModemStats[usModemId].ulLBDLRxSduInGSM);
    PS_PRINTF("下行GSM模入队成功个数                        %d\n",g_stCdsStats.astModemStats[usModemId].ulDLGSMEnQueSucc);
    PS_PRINTF("下行GSM模入队失败个数                        %d\n",g_stCdsStats.astModemStats[usModemId].ulDLGSMEnQueFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("下行UMTS模接收SDU个数                        %d\n",g_stCdsStats.astModemStats[usModemId].ulDLUMTSRxSduNum);
    PS_PRINTF("下行UMTS模接收IMS数据包个数                  %d\n",g_stCdsStats.astModemStats[usModemId].ulDLUMTSRxImsNum);
    PS_PRINTF("下行UMTS模流控丢弃SDU个数                    %d\n",g_stCdsStats.astModemStats[usModemId].ulDLUMTSFcFreeSduNum);
    PS_PRINTF("下行UMTS模环回模式下接收SDU个数              %d\n",g_stCdsStats.astModemStats[usModemId].ulLBDLRxSduInUMTS);
    PS_PRINTF("下行UMTS模打桩直接释放SDU个数                %d\n",g_stCdsStats.astModemStats[usModemId].ulDLUMTSDirectFreeSduNum);
    PS_PRINTF("下行UMTS模入队成功个数                       %d\n",g_stCdsStats.astModemStats[usModemId].ulDLUMTSEnQueSucc);
    PS_PRINTF("下行UMTS模入队失败个数                       %d\n",g_stCdsStats.astModemStats[usModemId].ulDLUMTSEnQueFail);
    PS_PRINTF("\r\n");

    PS_PRINTF("\r\n");

    return;
}


/*****************************************************************************
 函 数 名  : CDS_ShowUlLTEProcStats
 功能描述  : 显示CDS上行LTE处理统计
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowCdsEntityInfo(VOS_UINT16 usModemId)
{
    char    strRanMode[][20]  = {"NULL","LTE","GU","无效接入模式"};
    char    strLBState[][20]  = {"正常模式","环回模式"};


    CDS_ENTITY_STRU         *pstCdsEntity;
    VOS_UINT32               ulCnt;

    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        PS_PRINTF("ModemId非法。输入ModemId=%d\n",usModemId);
        return;
    }

    PS_PRINTF("显示Modem%d的CDS实体状态  \r\n",usModemId);
    PS_PRINTF("当前接入模式              : %s\r\n",strRanMode[pstCdsEntity->enRanMode]);
    PS_PRINTF("上行SR触发标志            : %d\r\n",pstCdsEntity->ulServiceReqFlg);
    PS_PRINTF("上行缓存队列缓存个数      : %d\r\n",LUP_QueCnt(pstCdsEntity->pstUlDataQue));
    PS_PRINTF("上行缓存数据保护定时器    : 0x%x\r\n",pstCdsEntity->astTimer[CDS_TMR_ID_UL_DATA_PROCTECT].pstTmrHdr);
    PS_PRINTF("下行10ms周期性定时器      : 0x%x\r\n",pstCdsEntity->astTimer[CDS_TMR_ID_DL_10MS_PERIODIC_TMR].pstTmrHdr);
    PS_PRINTF("环回模式状态              : %s\r\n",strLBState[pstCdsEntity->ulTestModeFlg]);
    PS_PRINTF("环回模式类型              : %d\r\n",pstCdsEntity->ulLoopBackMode);
    PS_PRINTF("环回模式B定时器时长       : %d\r\n",pstCdsEntity->astTimer[CDS_TMR_ID_LB_MODE_B_TMR].ulTmrLen);
    PS_PRINTF("环回队列当前缓存SDU       : %d\r\n",LUP_QueCnt(pstCdsEntity->pstLBModeBQue));

    PS_PRINTF("上行数据包直接丢弃开关    : %d\r\n",pstCdsEntity->ulULPktDiscardFlg);
    PS_PRINTF("下行数据包直接丢弃开关    : %d\r\n",pstCdsEntity->ulDLPktDiscardFlg);

    PS_PRINTF("\r\n");

    PS_PRINTF("显示Modem%d的IMS承载信息  \r\n",usModemId);

    PS_PRINTF("IMS端口号范围             :%d - %d\r\n",pstCdsEntity->stImsPortInfo.usMinImsPort,
                                                pstCdsEntity->stImsPortInfo.usMaxImsPort);

    PS_PRINTF("IMS承载总数               : %d\r\n",pstCdsEntity->ulImsBearerNum);
    for (ulCnt = 0; ulCnt < pstCdsEntity->ulImsBearerNum; ulCnt ++)
    {
        PS_PRINTF("IMS承载ID                 : %d\r\n",pstCdsEntity->astImsBearerInfo[ulCnt].ucEpsbId);
        PS_PRINTF("IMS承载类型               : %d\r\n",pstCdsEntity->astImsBearerInfo[ulCnt].enBearerType);
    }

    PS_PRINTF("\r\n");
    return;
}

/*****************************************************************************
 函 数 名  : CDS_PrintIpv4Addr
 功能描述  : 打印IPV4 地址
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_PrintIpv4Addr(const IPV4_ADDR_UN  *pstIpv4Addr)
{
    CDS_ASSERT(VOS_NULL_PTR != pstIpv4Addr);

    PS_PRINTF("%d.%d.%d.%d\r\n", pstIpv4Addr->aucIPAddr[0],
                           pstIpv4Addr->aucIPAddr[1],
                           pstIpv4Addr->aucIPAddr[2],
                           pstIpv4Addr->aucIPAddr[3]);
    return;
}

/*****************************************************************************
 函 数 名  : CDS_PrintIpv4Addr
 功能描述  : 打印IPV6 地址
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_PrintIpv6Addr(const IPV6_ADDR_UN  *pstIpv6Addr)
{

    VOS_UINT32       ulCnt;

    CDS_ASSERT(VOS_NULL_PTR != pstIpv6Addr);

    for (ulCnt = 0; ulCnt < IPV6_ADDR_LEN - 1; ulCnt ++)
    {
        PS_PRINTF("%.2x:",pstIpv6Addr->aucIPAddr[ulCnt]);
    }

    PS_PRINTF("%.2x\r\n",pstIpv6Addr->aucIPAddr[ulCnt]);

    return;
}
/*****************************************************************************
 函 数 名  : CDS_ShowSoftFilterIPv4Info
 功能描述  : 显示软过滤器信息IPv4相关的信息
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年08月07日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowSoftFilterIPv4Info(const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{
    /*Service Type*/
    if (PS_TRUE == pstSoftFilter->bitOpTypeOfService)
    {
        PS_PRINTF("TFT Service Type          : %d\r\n",pstSoftFilter->ucTypeOfService);
        PS_PRINTF("TFT Service Type Mask     : %d\r\n",pstSoftFilter->ucTypeOfServiceMask);
    }

    /*协议ID*/
    if (PS_TRUE == pstSoftFilter->bitOpProtocolId)
    {
        PS_PRINTF("TFT Protocol ID           : %d\r\n",pstSoftFilter->ucTypeOfService);
    }

    /*源IP地址信息*/
    if (PS_TRUE == pstSoftFilter->bitOpLcIpv4AddrAndMask)
    {
        PS_PRINTF("TFT IPv4 Src Address      : ");
        CDS_PrintIpv4Addr(&(pstSoftFilter->unLocalIpv4Addr));
        PS_PRINTF("TFT IPv4 Src Address Mask : ");
        CDS_PrintIpv4Addr(&(pstSoftFilter->unLocalIpv4Mask));
    }

    /*目的IP地址信息*/
    if (PS_TRUE == pstSoftFilter->bitOpRmtIpv4AddrAndMask)
    {
        PS_PRINTF("TFT IPv4 Dest Address     : ");
        CDS_PrintIpv4Addr(&(pstSoftFilter->unRmtIpv4Addr));
        PS_PRINTF("TFT IPv4 Dest Address Mask: ");
        CDS_PrintIpv4Addr(&(pstSoftFilter->unRmtIpv4Mask));
    }

    return;
}


/*****************************************************************************
 函 数 名  : CDS_ShowSoftFilterIPv6Info
 功能描述  : 显示软过滤器信息IPv6相关的信息
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年08月07日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowSoftFilterIPv6Info(const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{

    /*Service Type*/
    if (PS_TRUE == pstSoftFilter->bitOpTypeOfService)
    {
        PS_PRINTF("TFT Service Type          : %d\r\n",pstSoftFilter->ucTypeOfService);
        PS_PRINTF("TFT Service Type Mask     : %d\r\n",pstSoftFilter->ucTypeOfServiceMask);
    }

    /*协议ID*/
    if (PS_TRUE == pstSoftFilter->bitOpProtocolId)
    {
        PS_PRINTF("TFT Protocol ID           : %d\r\n",pstSoftFilter->ucTypeOfService);
    }

    /*FlowLable*/
    if (PS_TRUE == pstSoftFilter->bitOpFlowLabelType)
    {
        PS_PRINTF("TFT FlowLable Type        : 0x%.8x\r\n",pstSoftFilter->ulFlowLabelType);
    }

    /*源IPv6地址*/
    if (PS_TRUE == pstSoftFilter->bitOpLcIpv6AddrAndMask)
    {
        PS_PRINTF("TFT IPv6 Source Address    \r\n");
        CDS_PrintIpv6Addr(&(pstSoftFilter->unLocalIpv6Addr));
        PS_PRINTF("TFT IPv6 Source Address Mask \r\n");
        CDS_PrintIpv6Addr(&(pstSoftFilter->unLocalIpv6Mask));
    }

    /*目的IPv6地址*/
    if (PS_TRUE == pstSoftFilter->bitOpRmtIpv6AddrAndMask)
    {
        PS_PRINTF("TFT IPv6 Dest Address    \r\n");
        CDS_PrintIpv6Addr(&(pstSoftFilter->unRmtIpv6Addr));
        PS_PRINTF("TFT IPv6 Dest Address Mask \r\n");
        CDS_PrintIpv6Addr(&(pstSoftFilter->unRmtIpv6Mask));
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ShowSoftFilterTransportLayerInfo
 功能描述  : 显示IPv4类型软过滤器信息
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年08月07日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowSoftFilterTransportLayerInfo(const CDS_SOFTFILTER_INFO_STRU *pstSoftFilter)
{

    /*SPI*/
    if (PS_TRUE == pstSoftFilter->bitOpSecuParaIndex)
    {
        PS_PRINTF("TFT IPSec SPI             : 0x%.8x\r\n",pstSoftFilter->ulSecuParaIndex);
    }

    /*源端口信息*/
    if (PS_TRUE == pstSoftFilter->bitOpSingleLocalPort)
    {
        PS_PRINTF("TFT Source Port           : %d\r\n",pstSoftFilter->usSingleLcPort);
    }

    if (PS_TRUE == pstSoftFilter->bitOpLocalPortRange)
    {
        PS_PRINTF("TFT Source Port Range     : [%d,%d]\r\n",pstSoftFilter->usLcPortLowLimit,pstSoftFilter->usLcPortHighLimit);
    }

    /*目的端口信息*/
    if (PS_TRUE == pstSoftFilter->bitOpSingleRemotePort)
    {
        PS_PRINTF("TFT Dest Port             : %d\r\n",pstSoftFilter->usSingleRmtPort);
    }

    if (PS_TRUE == pstSoftFilter->bitOpRemotePortRange)
    {
        PS_PRINTF("TFT Dest Port Range       : [%d,%d]\r\n",pstSoftFilter->usRmtPortLowLimit,pstSoftFilter->usRmtPortHighLimit);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ShowUlSoftFilterInfo
 功能描述  : 显示CDS上行软过滤器
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年08月07日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowUlSoftFilter(VOS_UINT16 usModemId)
{

    CDS_ENTITY_STRU             *pstCdsEntity;
    CDS_SOFTFILTER_INFO_STRU    *pstSoftFilter;
    VOS_UINT32                   ulCnt;

    pstCdsEntity = CDS_GetCdsEntity(usModemId);
    if (VOS_NULL_PTR == pstCdsEntity)
    {
        PS_PRINTF("ModemId非法。输入ModemId=%d\n",usModemId);
        return;
    }

    PS_PRINTF("显示Modem%d的上行软过滤器，总数为%d  \r\n",usModemId,pstCdsEntity->ulUlSoftFilterNum);

    for (ulCnt = 0; ulCnt < pstCdsEntity->ulUlSoftFilterNum; ulCnt ++)
    {
        pstSoftFilter = &(pstCdsEntity->astUlSoftFilter[ulCnt]);
        PS_PRINTF("上行软过滤器%d详细信息\r\n",ulCnt);
        PS_PRINTF("上行软过滤器ID            : %d\r\n",pstSoftFilter->ulPacketFilterId);
        PS_PRINTF("上行软过滤器方向          : %d\r\n",pstSoftFilter->enDirection);
        PS_PRINTF("上行软过滤器类型          : %d\r\n",pstSoftFilter->enFilterType);
        PS_PRINTF("上行软过滤器优先级        : %d\r\n",pstSoftFilter->usPrecedence);
        PS_PRINTF("上行软过滤器对应的承载ID  : %d\r\n",pstSoftFilter->ucRabId);

        if (CDS_SOFTFILTER_TYPE_IPV4 == pstSoftFilter->enFilterType)
        {
            CDS_ShowSoftFilterIPv4Info(pstSoftFilter);
        }
        else
        {
            CDS_ShowSoftFilterIPv6Info(pstSoftFilter);
        }

        CDS_ShowSoftFilterTransportLayerInfo(pstSoftFilter);

        PS_PRINTF("\r\n");

    }


    PS_PRINTF("\r\n");
    return;
}


/*****************************************************************************
 函 数 名  : CDS_ShowUlSoftFilterStats
 功能描述  : 显示CDS上行软过滤处理统计
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年08月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowUlSoftFilterStats(VOS_VOID)
{

    PS_PRINTF("上行软过滤数据包个数                         %d\n",g_stCdsStats.ulULSoftFilterPktNum);
    PS_PRINTF("上行软过滤IPV4数据包个数                     %d\n",g_stCdsStats.ulULSoftFilterIPv4Num);
    PS_PRINTF("上行软过滤IPV6数据包个数                     %d\n",g_stCdsStats.ulULSoftFilterIPv6Num);
    PS_PRINTF("上行软过滤失败个数                           %d\n",g_stCdsStats.ulULSoftFilterFailNum);
    PS_PRINTF("上行软过滤IP分片个数                         %d\n",g_stCdsStats.ulULSoftFilterIPSegNum);
    PS_PRINTF("上行软过滤IP分片处理成功个数                 %d\n",g_stCdsStats.ulULSoftFilterIPSegSucc);
    PS_PRINTF("上行软过滤IP分片处理失败个数                 %d\n",g_stCdsStats.ulULSoftFilterIPSegFail);

    PS_PRINTF("\r\n");
    return;
}


/*****************************************************************************
 函 数 名  : CDS_ShowIMSStats
 功能描述  : 显示CDS IMS处理统计量
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2013年08月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowIMSStats(VOS_VOID)
{
    PS_PRINTF("IMS上行收包函数调用次数                      %d\n",g_stCdsStats.ulImsULRxFunCallNum);
    PS_PRINTF("IMS上行收包函数入参非法次数                  %d\n",g_stCdsStats.ulImsULRxFunParaErr);

    PS_PRINTF("IMS上行接收IMS NIC数据包个数                 %d\n",g_stCdsStats.ulImsULRxNicPktNum);
    PS_PRINTF("IMS上行申请内存失败个数                      %d\n",g_stCdsStats.ulImsULAllocMemFail);
    PS_PRINTF("IMS上行入队失败个数                          %d\n",g_stCdsStats.ulImsULEnQueFail);
    PS_PRINTF("IMS上行入队成功个数                          %d\n",g_stCdsStats.ulImsULEnQueSucc);
    PS_PRINTF("IMS上行触发IMS_PROC事件次数                  %d\n",g_stCdsStats.ulImsULTrigImsEvent);
    PS_PRINTF("IMS上行处理IMS_PROC事件次数                  %d\n",g_stCdsStats.ulImsULProcImsEvent);
    PS_PRINTF("IMS上行软过滤失败次数                        %d\n",g_stCdsStats.ulImsULSoftFilterFail);
    PS_PRINTF("IMS上行数据包发送到空口个数                  %d\n",g_stCdsStats.ulImsULSendToRan);

    PS_PRINTF("IMS下行接收IMS数据包个数                     %d\n",g_stCdsStats.ulImsDLRxImsPkt);
    PS_PRINTF("IMS下行接收到NDCLIENT数据包个数              %d\n",g_stCdsStats.ulImsDLNdPktNum);
    PS_PRINTF("IMS下行申请内存失败个数                      %d\n",g_stCdsStats.ulImsDLAllocMemFail);
    PS_PRINTF("IMS下行获取目的端口号失败个数                %d\n",g_stCdsStats.ulImsDLGetDestPortFail);
    PS_PRINTF("IMS下行发送到IMS NIC数据包失败个数           %d\n",g_stCdsStats.ulImsDLSendToNicFail);
    PS_PRINTF("IMS下行发送到IMS NIC数据包成功个数           %d\n",g_stCdsStats.ulImsDLSendToNicSucc);

    PS_PRINTF("IMS下行接收Ut数据包个数                     %d\n",g_stCdsStats.ulImsDLRxUtPkt);
    PS_PRINTF("IMS下行Ut数据包处理成功个数                 %d\n",g_stCdsStats.ulImsDLUtPktProcSuccNum);
    PS_PRINTF("IMS下行Ut数据包处理失败个数                 %d\n",g_stCdsStats.ulImsDLUtPktProcErrNum);

    PS_PRINTF("\r\n");
    return;
}

/*****************************************************************************
 函 数 名  : CDS_ShowIpV4FragmentBuffInfo
 功能描述  : 显示IPV4分片缓存信息
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowIpV4FragmentBuffInfo(VOS_VOID)
{

    VOS_UINT32                         ulCnt;
    CDS_IPV4_FRAGMENT_BUFF_STRU       *pstIpv4FragBuff;
    CDS_IPV4_FRAGMENT_INFO_STRU       *pstIpv4FragInfo;

    pstIpv4FragBuff = CDS_GET_IPV4_FRAGMENT_BUFF();
    for (ulCnt = 0; ulCnt < CDS_IPV4_FRAGMENT_BUFF_SIZE; ulCnt ++)
    {
        pstIpv4FragInfo = &(pstIpv4FragBuff->astSegBuff[ulCnt]);
        PS_PRINTF("\n IPV4 Fragment Buffer Index : %d\n",ulCnt);
        PS_PRINTF("EPS Bearer  ID:                 %d\n", pstIpv4FragInfo->ucEpsbID);
        PS_PRINTF("Source IP Addr:                 ");
        CDS_PrintIpv4Addr(&(pstIpv4FragInfo->unSrcAddr));
        PS_PRINTF("Dest   IP Addr:                 ");
        CDS_PrintIpv4Addr(&(pstIpv4FragInfo->unDstAddr));
        PS_PRINTF("IP Fragment ID:                 %d\n", pstIpv4FragInfo->usIpIdentity);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CDS_ShowIpV6FragmentBuffInfo
 功能描述  : 显示IPV6分片缓存信息
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowIpV6FragmentBuffInfo(VOS_VOID)
{

    VOS_UINT32                         ulCnt;
    CDS_IPV6_FRAGMENT_BUFF_STRU       *pstIpv6FragBuff;
    CDS_IPV6_FRAGMENT_INFO_STRU       *pstIpv6FragInfo;

    pstIpv6FragBuff = CDS_GET_IPV6_FRAGMENT_BUFF();
    for (ulCnt = 0; ulCnt < CDS_IPV6_FRAGMENT_BUFF_SIZE; ulCnt ++)
    {
        pstIpv6FragInfo = &(pstIpv6FragBuff->astSegBuff[ulCnt]);
        PS_PRINTF("\n IPV6 Fragment Buffer Index : %d\n",ulCnt);
        PS_PRINTF("EPS Bearer  ID:    %d\n", pstIpv6FragInfo->ucEpsbID);
        PS_PRINTF("IP Fragment ID:    %d\n", pstIpv6FragInfo->ulIdentity);
        PS_PRINTF("Src IPV6 Addr :    ");
        CDS_PrintIpv6Addr(&(pstIpv6FragInfo->unSrcAddr));
        PS_PRINTF("Dst IPV6 Addr :    ");
        CDS_PrintIpv6Addr(&(pstIpv6FragInfo->unDstAddr));
    }

    return;
}


/*****************************************************************************
 函 数 名  : CDS_ShowIpFragStats
 功能描述  : 显示IP分片
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ShowIpFragStats(VOS_VOID)
{

    PS_PRINTF("接收IPV4 分片的个数               %d\n",g_stCdsIpFragBuff.stStats.ulRxIpv4Frag);
    PS_PRINTF("接收IPV4 IPF过滤成功的个数        %d\n",g_stCdsIpFragBuff.stStats.ulRxIpv4IpfSucc);
    PS_PRINTF("接收IPV4 IPF过滤失败的个数        %d\n",g_stCdsIpFragBuff.stStats.ulRxIpv4IpfFail);
    PS_PRINTF("接收IPV6 分片的个数               %d\n",g_stCdsIpFragBuff.stStats.ulRxIpv6Frag);
    PS_PRINTF("接收IPV6 IPF过滤成功的个数        %d\n",g_stCdsIpFragBuff.stStats.ulRxIpv6IpfSucc);
    PS_PRINTF("接收IPV6 IPF过滤失败的个数        %d\n",g_stCdsIpFragBuff.stStats.ulRxIpv6IpfFail);
    PS_PRINTF("接收本地处理成功的个数            %d\n",g_stCdsIpFragBuff.stStats.ulLocalProcSucc);
    PS_PRINTF("接收本地处理失败的个数            %d\n",g_stCdsIpFragBuff.stStats.ulLocalProcFail);

    return;
}

/*****************************************************************************
 函 数 名  : CDS_IpFrag_Help
 功能描述  : 显示IP分片处理处理信息
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_IpFrag_Help(VOS_VOID)
{
    PS_PRINTF("CDS_ShowIpV4FragmentBuffInfo             显示IPV4分片缓存信息\n");
    PS_PRINTF("CDS_ShowIpV6FragmentBuffInfo             显示IPV6分片缓存信息\n");
    PS_PRINTF("CDS_ShowIpFragStats                      显示IP分片统计信息\n");
    PS_PRINTF("CDS_ClearIpFragBuff                      清空IP分片缓存");

    return;
}

/*****************************************************************************
 函 数 名  : CDS_Help
 功能描述  : CDS软调信息入口
 输入参数  :
 输出参数  : 无
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2011年12月12日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_Help(VOS_VOID)
{

    PS_PRINTF("********************CDS软调信息************************\n");
    PS_PRINTF("CDS_ShowCdsEntityInfo(ModemId)          显示对应Modem的CDS实体状态\n");
    PS_PRINTF("CDS_ShowEventStats                      显示CDS事件处理统计信息\n");
    PS_PRINTF("CDS_ShowUlRdProcStats                   显示CDS上行RD处理统计信息\n");
    PS_PRINTF("CDS_ShowUlAdqProcStats                  显示CDS上行ADQ统计信息\n");
    PS_PRINTF("CDS_ShowUlIpPktProcStats                显示CDS上行IP包处理统计信息\n");
    PS_PRINTF("CDS_ShowDlSduProcStats                  显示CDS下行SDU数传统计信息\n");
    PS_PRINTF("CDS_ShowDlIpfProcStats                  显示CDS下行IPF数传统计信息\n");

    PS_PRINTF("CDS_ShowModemGUProcStats(ModemId)       显示GU上行数传统计信息\n");
    PS_PRINTF("CDS_ShowLBProcStats                     显示环回模式数传统计信息\n");
    PS_PRINTF("CDS_IpFrag_Help                         显示IP分片软调信息\n");
    PS_PRINTF("QosFc_ShowStats                         显示流量控制数传统计信息\n");

    PS_PRINTF("CDS_ShowUlSoftFilter(ModemId)           显示上行过滤器组信息\n");
    PS_PRINTF("CDS_ShowUlSoftFilterStats               显示上行软过滤处理统计信息\n");
    PS_PRINTF("CDS_ShowIMSStats                        显示IMS处理统计信息\n");

    return;
}
/*****************************************************************************
 函 数 名  : LUP_CdsLomTraceRcvUlData
 功能描述  : 用户面时延Trace，用于记录CDS接收上行数据时间戳
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月23日
    作    者   : hujianbo 42180
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Cds_LomTraceRcvUlData(VOS_VOID)
{
    if (1 == g_ulCdsOmSwitch)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS, "User plane latency trace: CDS rcv ul data\n");
        CDS_PRINT_ERROR(Cds_LomTraceRcvUlData_ENUM, LL2_CDS_RECV_UL_DATA);
    }

    return;
}

/*****************************************************************************
 函 数 名  : Cds_LomTraceSendDlData
 功能描述  : 用户面时延Trace，用于记录CDS发送下行数据时间戳
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月23日
    作    者   : hujianbo 42180
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Cds_LomTraceSendDlData(VOS_VOID)
{
    if (1 == g_ulCdsOmSwitch)
    {
        CDS_ERROR_LOG(UEPS_PID_CDS, "User plane latency trace: CDS send dl data\n");
        CDS_PRINT_ERROR(Cds_LomTraceSendDlData_ENUM, LL2_CDS_SEND_DL_DATA);
    }

    return;
}





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



