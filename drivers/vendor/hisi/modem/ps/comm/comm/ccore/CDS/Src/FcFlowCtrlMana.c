/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : FcFlowCtrlMana.c
  版 本 号   : 初稿
  作    者   : w00145177
  生成日期   : 2011年12月23日
  最近修改   :
  功能描述   : C核流控管理模块
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月23日
    作    者   : w00145177
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

#include "CDS.h"
#include "QosFcCommon.h"
#include "OmApi.h"
#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
#include "LPsNvInterface.h"
#endif
#include "FcFlowCtrlMana.h"
#include "TtfNvInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_FC_FLOWCTRL_MANA_C
/*lint +e767*/




/*****************************************************************************
  2 外部函数声明
*****************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/

/******************************************************************************
   4 全局变量定义
******************************************************************************/
#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
FLOWCTRL_LTE_CONFIG_STRU        g_stFcLteConfig = \
                                {{4,0,{0,0},\
                                   {50000,40000,35000,30000,\
                                   25000,20000,15000,10000,\
                                   5000,2000,0,0}, 200},\
                                   {5,20,10,2000,10,5,60,98,90,0}};
#endif

FLOWCTRL_CDS_CONFIG_STRU        g_stFcCdsConfig = {0, {80,50,20,95,100,200,300,400}, {50,80}};

FC_LTE_CPU_CONTROL_STRU         g_stFcLteCpuCtrl;

FC_LTE_TEMPERATURE_CONTROL_STRU g_stFcLteTemperatureCtrl;

FC_CDS_DL_CONTROL_STRU          g_stFcCdsDlCtrl;

/* CPU流控BSR乘数 */
VOS_DOUBLE                      g_dBsrCpuModu = 1.0;
VOS_DOUBLE                      g_dBsrCpuLimit = 0.02;

/* HARQ丢包率 */
VOS_UINT32  g_ulHarqKeepRate = 100;

VOS_UINT32  g_ulUlFcThroughputStat = 0;
VOS_UINT32  g_ulUlDowngradeFlag = PS_FALSE ;
VOS_UINT32  g_ulUlThroughputMax = FC_UL_ENTRY_THROUGHPUT_INIT;

FC_CL_STATS_INFO_STRU    g_stFcCLStats = {0};

#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
extern VOS_UINT32 LUP_GetCurrentTime(VOS_VOID);
/* extern VOS_VOID   LUP_RelDataReq(VOS_VOID); */
#endif

/*extern VOS_VOID BSP_PWRCTRL_GetCcpuLoadCB(PWRCTRLFUNCPTR pFunc);*/

/******************************************************************************
   5 函数实现
******************************************************************************/
#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
/*****************************************************************************
 函 数 名  : Fc_LteConfig2Default
 功能描述  : NV读失败时流控初始化为默认值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月7日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_LteConfig2Default(VOS_VOID)
{
    g_stFcLteConfig.stFcCpuConfig.usFirstDelay = 5;
    g_stFcLteConfig.stFcCpuConfig.usUlDownRate = 20;
    g_stFcLteConfig.stFcCpuConfig.usUlUpRate = 10;
    g_stFcLteConfig.stFcCpuConfig.usUlMinThr = 2000;
    g_stFcLteConfig.stFcCpuConfig.usHqDownRate = 10;
    g_stFcLteConfig.stFcCpuConfig.usHqUpRate = 5;
    g_stFcLteConfig.stFcCpuConfig.usHqMaxDiscardRate = 60;
    g_stFcLteConfig.stFcCpuConfig.usDowngradeThres = 98;
    g_stFcLteConfig.stFcCpuConfig.usUpgradeThres = 90;

    g_stFcLteConfig.stFcTemperatureConfig.ucInitialPos = 4;
    g_stFcLteConfig.stFcTemperatureConfig.ucZeroSupport = 0;
    g_stFcLteConfig.stFcTemperatureConfig.ulMinBsrThr = 200;
    g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[0] = 50000;
    g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[1] = 40000;
    g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[2] = 35000;
    g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[3] = 30000;
    g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[4] = 25000;
    g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[5] = 20000;
    g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[6] = 15000;
    g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[7] = 10000;
    g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[8] = 5000;
    g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[9] = 2000;
    g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[10] = 0;
    g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[11] = 0;

    return;
}

/*****************************************************************************
 函 数 名  : FC_LteConfigcheck
 功能描述  : 流控参数检查
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月22日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_LteConfigcheck(VOS_VOID)
{
    VOS_UINT32 i = 0;

    if(g_stFcLteConfig.stFcCpuConfig.usUlDownRate >= 100)
    {
        PS_PRINTF("FC_LteConfigcheck Error config stFcCpuConfig.usUlDownRate over 100:%d\n", g_stFcLteConfig.stFcCpuConfig.usUlDownRate);
        return PS_FAIL;
    }
    if(g_stFcLteConfig.stFcCpuConfig.usUlUpRate >= 100)
    {
        PS_PRINTF("FC_LteConfigcheck Error config stFcCpuConfig.usUlUpRate over 100:%d\n", g_stFcLteConfig.stFcCpuConfig.usUlUpRate);
        return PS_FAIL;
    }
    if(g_stFcLteConfig.stFcCpuConfig.usHqDownRate >= 100)
    {
        PS_PRINTF("FC_LteConfigcheck Error config stFcCpuConfig.usHqDownRate over 100:%d\n", g_stFcLteConfig.stFcCpuConfig.usHqDownRate);
        return PS_FAIL;
    }
    if(g_stFcLteConfig.stFcCpuConfig.usHqUpRate >= 100)
    {
        PS_PRINTF("FC_LteConfigcheck Error config stFcCpuConfig.usHqUpRate over 100:%d\n", g_stFcLteConfig.stFcCpuConfig.usHqUpRate);
        return PS_FAIL;
    }
    if(g_stFcLteConfig.stFcCpuConfig.usDowngradeThres >= 100)
    {
        PS_PRINTF("FC_LteConfigcheck Error config stFcCpuConfig.usDowngradeThres over 100:%d\n", g_stFcLteConfig.stFcCpuConfig.usDowngradeThres);
        return PS_FAIL;
    }
    if(g_stFcLteConfig.stFcCpuConfig.usUpgradeThres >= g_stFcLteConfig.stFcCpuConfig.usDowngradeThres)
    {
        PS_PRINTF("FC_LteConfigcheck Error config stFcCpuConfig.usUpgradeThres greater than stFcCpuConfig.usDowngradeThres:%d,%d\n",
                                    g_stFcLteConfig.stFcCpuConfig.usUpgradeThres,
                                    g_stFcLteConfig.stFcCpuConfig.usDowngradeThres);
        return PS_FAIL;
    }

    if(g_stFcLteConfig.stFcTemperatureConfig.ucInitialPos >= FC_UL_THROUGHPUT_THRES_CNT_NV)
    {
        PS_PRINTF("FC_LteConfigcheck Error config stFcTemperatureConfig.ucInitialPos beyond :%d,%d\n", g_stFcLteConfig.stFcTemperatureConfig.ucInitialPos, FC_UL_THROUGHPUT_THRES_CNT_NV);
        return PS_FAIL;
    }
    if(g_stFcLteConfig.stFcTemperatureConfig.ucZeroSupport > 1)
    {
        PS_PRINTF("FC_LteConfigcheck Error config stFcTemperatureConfig.ucZeroSupport over 1:%d\n", g_stFcLteConfig.stFcTemperatureConfig.ucZeroSupport);
        return PS_FAIL;
    }

    for(i = 0; i < FC_UL_THROUGHPUT_THRES_CNT_NV-1; i++)
    {
        if(0 == g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[i])
        {
            break;
        }

        if(g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[i] < g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[i+1])
        {
            PS_PRINTF("FC_LteConfigcheck: g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps must be descending order!");
            return PS_FAIL;
        }
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Fc_KbpsToBsr
 功能描述  : 将NV配置kbps转换为BSR上报门限
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月7日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_KbpsToBsr(VOS_VOID)
{
    VOS_UINT32                  i;

    g_stFcLteCpuCtrl.ulUlMinBsr = g_stFcLteConfig.stFcCpuConfig.usUlMinThr*g_stFcLteTemperatureCtrl.ulBsrTimerLen/8;
    g_dBsrCpuLimit = g_stFcLteCpuCtrl.ulUlMinBsr / 150000.0;

    for(i = 0; i < g_stFcLteTemperatureCtrl.ucBsrThresCnt; i++)
    {
        g_stFcLteTemperatureCtrl.ulTemperSteps[i] = g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[i]*g_stFcLteTemperatureCtrl.ulBsrTimerLen/8;
    }
}

/*****************************************************************************
 函 数 名  : Fc_BsrTimerSetting
 功能描述  : 设置BSR周期
 输入参数  : VOS_UINT32 ulBsrTimer
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月6日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_BsrTimerSetting( VOS_UINT32 ulBsrTimer )
{
    if(g_stFcLteTemperatureCtrl.ulBsrTimerLen != ulBsrTimer)
    {
        g_stFcLteTemperatureCtrl.ulBsrTimerLen = ulBsrTimer;
        /* BSR周期改变，重新计算 */
        Fc_KbpsToBsr();

    }
}


#endif

/*****************************************************************************
 函 数 名  : Fc_CdsConfig2Default
 功能描述  : NV读失败时流控初始化为默认值
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月7日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_CdsConfig2Default(VOS_VOID)
{
    g_stFcCdsConfig.ulFcEnableMask = 0;

    g_stFcCdsConfig.stQosFcConfig.ulPktCntLimit = 80;
    g_stFcCdsConfig.stQosFcConfig.ulTimerLen = 50;

    g_stFcCdsConfig.stQosFcConfig.ulRandomDiscardRate = 20;
    g_stFcCdsConfig.stQosFcConfig.ulDiscardRate = 95;

    g_stFcCdsConfig.stQosFcConfig.ulWarningThres = 100;
    g_stFcCdsConfig.stQosFcConfig.ulDiscardThres = 200;
    g_stFcCdsConfig.stQosFcConfig.ulRandomDiscardThres = 300;
    g_stFcCdsConfig.stQosFcConfig.ulRestoreThres = 400;

    g_stFcCdsConfig.stFcCdsDlConfig.ulDiscardThres = 50;
    g_stFcCdsConfig.stFcCdsDlConfig.ulDiscardRate = 80;
    return;
}

/*****************************************************************************
 函 数 名  : FC_CdsConfigcheck
 功能描述  : 流控参数检查
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月22日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_CdsConfigcheck(VOS_VOID)
{
    if(g_stFcCdsConfig.stFcCdsDlConfig.ulDiscardRate >= 100)
    {
        PS_PRINTF("FC_CdsConfigcheck Error config stFcCdsDlConfig.ulDiscardRate over 100:%d\n", g_stFcCdsConfig.stFcCdsDlConfig.ulDiscardRate);
        return PS_FAIL;
    }
    if(g_stFcCdsConfig.stQosFcConfig.ulDiscardRate >= 100)
    {
        PS_PRINTF("FC_CdsConfigcheck Error config stQosFcConfig.ulDiscardRate over 100:%d\n", g_stFcCdsConfig.stQosFcConfig.ulDiscardRate);
        return PS_FAIL;
    }
    if(g_stFcCdsConfig.stQosFcConfig.ulRandomDiscardRate >= g_stFcCdsConfig.stQosFcConfig.ulDiscardRate)
    {
        PS_PRINTF("FC_CdsConfigcheck Error config stQosFcConfig.ulRandomDiscardRate greater than stQosFcConfig.ulDiscardRate:%d,%d\n", g_stFcCdsConfig.stQosFcConfig.ulRandomDiscardRate, g_stFcCdsConfig.stQosFcConfig.ulDiscardRate);
        return PS_FAIL;
    }
    if(g_stFcCdsConfig.stQosFcConfig.ulWarningThres >= g_stFcCdsConfig.stQosFcConfig.ulDiscardThres)
    {
        PS_PRINTF("FC_CdsConfigcheck Error config stQosFcConfig.ulWarningThres greater than stQosFcConfig.ulDiscardThres:%d,%d\n", g_stFcCdsConfig.stQosFcConfig.ulWarningThres, g_stFcCdsConfig.stQosFcConfig.ulDiscardThres);
        return PS_FAIL;
    }

    if(g_stFcCdsConfig.stQosFcConfig.ulDiscardThres >= g_stFcCdsConfig.stQosFcConfig.ulRandomDiscardThres)
    {
        PS_PRINTF("FC_CdsConfigcheck Error config stQosFcConfig.ulDiscardThres greater than stQosFcConfig.ulRandomDiscardThres:%d,%d\n", g_stFcCdsConfig.stQosFcConfig.ulDiscardThres, g_stFcCdsConfig.stQosFcConfig.ulRandomDiscardThres);
        return PS_FAIL;
    }
    if(g_stFcCdsConfig.stQosFcConfig.ulRandomDiscardThres >= g_stFcCdsConfig.stQosFcConfig.ulRestoreThres)
    {
        PS_PRINTF("FC_CdsConfigcheck Error config stQosFcConfig.ulRandomDiscardThres greater than stQosFcConfig.ulRestoreThres:%d,%d\n", g_stFcCdsConfig.stQosFcConfig.ulRandomDiscardThres, g_stFcCdsConfig.stQosFcConfig.ulRestoreThres);
        return PS_FAIL;
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : Fc_LteStatusInit
 功能描述  : LTE流控状态初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月9日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_LteStatusInit(VOS_VOID)
{
    /* 复位流控状态 */
    g_dBsrCpuModu = 1.0;
    g_ulHarqKeepRate = 100;

    g_ulUlDowngradeFlag = PS_FALSE;
    g_ulUlThroughputMax = FC_UL_ENTRY_THROUGHPUT_INIT;
    g_stFcLteTemperatureCtrl.ucCurrPos = FC_UL_THROUGHPUT_THRES_CNT;
}

/*****************************************************************************
 函 数 名  : Fc_LteInit
 功能描述  : LTE流控初始化
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_LteInit(VOS_VOID)
{
    VOS_UINT32                  ulReturnCode;

#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
    VOS_UINT32                  i;

    /* 从NV读取流控配置信息 */
    /*lint -e718*/
    /*lint -e746*/
    /*lint -e732*/
    /*lint -e830*/
    ulReturnCode = LPs_NvimItem_Read(EN_NV_ID_FLOWCTRL_CONFIG,\
                                    (VOS_VOID *)(&g_stFcLteConfig),\
                                    sizeof(FLOWCTRL_LTE_CONFIG_STRU));
    /*lint +e830*/
    /*lint +e732*/
    /*lint +e746*/
    /*lint +e718*/
    if (PS_SUCC != ulReturnCode)
    {
        PS_PRINTF("Fc_LteInit,LPs_NvimItem_Read FLOWCTRL_LTE_CONFIG fail:%d\n", ulReturnCode);
        /* 初始化为默认值 */
        Fc_LteConfig2Default();
    }

    if(PS_SUCC != FC_LteConfigcheck())
    {
        /* 初始化为默认值 */
        Fc_LteConfig2Default();
    }

    g_stFcLteCpuCtrl.ulFirstDelay = g_stFcLteConfig.stFcCpuConfig.usFirstDelay;
    g_stFcLteCpuCtrl.ulUlDownRate = g_stFcLteConfig.stFcCpuConfig.usUlDownRate;
    g_stFcLteCpuCtrl.ulUlUpRate = g_stFcLteConfig.stFcCpuConfig.usUlUpRate;
    g_stFcLteCpuCtrl.ulHqDownRate = g_stFcLteConfig.stFcCpuConfig.usHqDownRate;
    g_stFcLteCpuCtrl.ulHqUpRate = g_stFcLteConfig.stFcCpuConfig.usHqUpRate;
    g_stFcLteCpuCtrl.ulHqMaxDiscardRate = g_stFcLteConfig.stFcCpuConfig.usHqMaxDiscardRate;
    g_stFcLteCpuCtrl.ulDowngradeThres = g_stFcLteConfig.stFcCpuConfig.usDowngradeThres;
    g_stFcLteCpuCtrl.ulUpgradeThres = g_stFcLteConfig.stFcCpuConfig.usUpgradeThres;

    g_stFcLteTemperatureCtrl.ucInitialPos = g_stFcLteConfig.stFcTemperatureConfig.ucInitialPos;
    g_stFcLteTemperatureCtrl.ulBsrTimerLen = 10;    /* 默认BSR周期10ms */
    g_stFcLteTemperatureCtrl.ucAvailCnt = 0;
    g_stFcLteTemperatureCtrl.ucBsrThresCnt = 0;
    g_stFcLteTemperatureCtrl.ucCurrPos = FC_UL_THROUGHPUT_THRES_CNT;

    for(i = 0; i < FC_UL_THROUGHPUT_THRES_CNT_NV; i++)
    {
        if(0 == g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[i])
        {
            break;
        }

        if(g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[i] < g_stFcLteConfig.stFcTemperatureConfig.ulMinBsrThr)
        {
            g_stFcLteTemperatureCtrl.ucAvailCnt++;
            /* 周期折算，NV设置为kbps，入口流控基于100ms字节数 */
            g_stFcLteTemperatureCtrl.ulTemperSteps[i] = g_stFcLteConfig.stFcTemperatureConfig.ulTemperSteps[i]*100 / 8;
        }
        else
        {
            g_stFcLteTemperatureCtrl.ucBsrThresCnt++;
        }
    }
    /* 入口流控紧随BSR流控 */
    g_stFcLteTemperatureCtrl.ucAvailCnt += g_stFcLteTemperatureCtrl.ucBsrThresCnt;

    for(; i < FC_UL_THROUGHPUT_THRES_CNT; i++)
    {
        g_stFcLteTemperatureCtrl.ulTemperSteps[i] = 0;
    }

    if(g_stFcLteConfig.stFcTemperatureConfig.ucZeroSupport > 0)
    {
        g_stFcLteTemperatureCtrl.ucAvailCnt++;
    }

    g_ulUlDowngradeFlag = PS_FALSE;

    Fc_KbpsToBsr();
#endif


    /* 从GU NV读取流控配置信息 */
    /*lint -e718*/
    /*lint -e746*/
    /*lint -e732*/
    ulReturnCode = NV_ReadEx(MODEM_ID_0,EN_NV_ITEM_CDS_FC_CONFIG,\
                                    (&g_stFcCdsConfig),\
                                    sizeof(FLOWCTRL_CDS_CONFIG_STRU));
    /*lint +e732*/
    /*lint +e746*/
    /*lint +e718*/

    if (PS_SUCC != ulReturnCode)
    {
        PS_PRINTF("Fc_LteInit,NV_Read FLOWCTRL_CDS_CONFIG fail:%d\n", ulReturnCode);
        /* 初始化为默认值 */
        Fc_CdsConfig2Default();
    }

    if(PS_SUCC != FC_CdsConfigcheck())
    {
        /* 初始化为默认值 */
        Fc_CdsConfig2Default();
    }

    /* 基于NV填充控制结构 */
    if(0 == (FC_CDS_DL_ENABLED_MASK & g_stFcCdsConfig.ulFcEnableMask))
    {
        g_stFcCdsDlCtrl.bDlCdsFcEnable = VOS_FALSE;
    }
    else
    {
        g_stFcCdsDlCtrl.bDlCdsFcEnable = VOS_TRUE;
    }

    g_stFcCdsDlCtrl.ulDiscardThres = g_stFcCdsConfig.stFcCdsDlConfig.ulDiscardThres;
    g_stFcCdsDlCtrl.ulDiscardRate = g_stFcCdsConfig.stFcCdsDlConfig.ulDiscardRate;

    return;
}

/*****************************************************************************
 函 数 名  : NULL_CPUFcProcess
 功能描述  : NULL模式 CPU流控回调处理
 输入参数  : unsigned int arg
 输出参数  : 无
 返 回 值  : unsigned int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int NULL_CPUFcProcess( unsigned int arg )
{
    if(arg > g_stFcLteCpuCtrl.ulDowngradeThres)
    {
        /*CDS_WARNING_LOG1(UEPS_PID_CDS,"NULL_CPUFcProcess : NULL CPU overload:", arg);*/
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : NULL_DownGradeUlProcess
 功能描述  : NULL模式温保降速回调函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : SPY_DATA_UPGRADE_RESULT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
SPY_DATA_DOWNGRADE_RESULT_ENUM_UINT32 NULL_DownGradeUlProcess (VOS_VOID)
{
    CDS_WARNING_LOG(UEPS_PID_CDS,"NULL_DownGradeUlProcess : NULL Speed Downgrade");
    CDS_PRINT_WARNING(NULL_DownGradeUlProcess_ENUM, CDS_FC_NULL_SPEED_DOWN_GRADE);
    /* 开机高温场景 */
    return SPY_DATA_DOWNGRADE_CONTINUE;
}

/*****************************************************************************
 函 数 名  : NULL_UpGradeUlProcess
 功能描述  : NULL模式温保升速回调函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : SPY_DATA_UPGRADE_RESULT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
SPY_DATA_UPGRADE_RESULT_ENUM_UINT32 NULL_UpGradeUlProcess (VOS_VOID)
{
    CDS_WARNING_LOG(UEPS_PID_CDS,"NULL_UpGradeUlProcess : NULL Speed Upgrade");
    CDS_PRINT_WARNING(NULL_UpGradeUlProcess_ENUM, CDS_FC_NULL_SPEED_UP_GRADE);

    return SPY_DATA_UPGRADE_FINISH;
}

/*****************************************************************************
 函 数 名  : NULL_RecoverUlGradeProcess
 功能描述  : NULL温保直接恢复回调函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月29日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NULL_RecoverUlGradeProcess (VOS_VOID)
{
    CDS_WARNING_LOG(UEPS_PID_CDS, "NULL_RecoverUlGradeProcess : NULL Speed Recover");
    CDS_PRINT_WARNING(NULL_UpGradeUlProcess_ENUM, CDS_FC_NULL_SPEED_RECOVER);

    return;
}

/*****************************************************************************
 函 数 名  : FC_HarqDown
 功能描述  : HARQ降速
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月7日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_HarqDown (VOS_VOID)
{
    if(g_stFcLteCpuCtrl.ulHqMaxDiscardRate > (100 - g_ulHarqKeepRate))
    {
        FC_CL_HQ_DOWN_STAT(1);
        g_ulHarqKeepRate = g_ulHarqKeepRate * (100 - g_stFcLteCpuCtrl.ulHqDownRate) / 100;
        if(g_stFcLteCpuCtrl.ulHqMaxDiscardRate < (100 - g_ulHarqKeepRate))
        {
            FC_CL_HQ_TO_DOWN_STAT(1);
            g_ulHarqKeepRate = 100 - g_stFcLteCpuCtrl.ulHqMaxDiscardRate;
            /*CDS_WARNING_LOG(UEPS_PID_CDS,"FC_HarqDown : HARQ DOWNGRADE finish");*/
        }
        /*CDS_WARNING_LOG1(UEPS_PID_CDS,"FC_HarqDown : HARQ DiscardRate:", (100 - g_ulHarqKeepRate));*/

        /* 写给DSP */
    }

    return;
}

/*****************************************************************************
 函 数 名  : FC_HarqUp
 功能描述  : HARQ升速
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月7日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_HarqUp (VOS_VOID)
{
    FC_CL_HQ_UP_STAT(1);

    g_ulHarqKeepRate = g_ulHarqKeepRate * (100 + g_stFcLteCpuCtrl.ulHqUpRate) / 100;
    /*CDS_WARNING_LOG1(UEPS_PID_CDS,"FC_HarqUp : HARQ DiscardRate:", (100 - g_ulHarqKeepRate));*/

    if(g_ulHarqKeepRate > 100)
    {
        g_ulHarqKeepRate = 100;
        /*CDS_WARNING_LOG(UEPS_PID_CDS,"FC_HarqUp : HARQ UPGRADE finish");*/
        FC_CL_HQ_TO_NORMAL_STAT(1);
    }

    /* 写给DSP */

    return;
}

/*****************************************************************************
 函 数 名  : FC_LCPU_Process
 功能描述  : LTE CPU流控回调处理
 输入参数  : unsigned int arg
 输出参数  : 无
 返 回 值  : unsigned int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int FC_LCPU_Process( unsigned int arg )
{
    static VOS_UINT32 ulFirstDelay = 0;

    if(arg > g_stFcLteCpuCtrl.ulDowngradeThres)
    {
        /* 0.9999浮点逼近 1 */
        if(0.9999 <  g_dBsrCpuModu)
        {
            /* 延迟进入流控状态 */
            ulFirstDelay++;
            if(g_stFcLteCpuCtrl.ulFirstDelay <= ulFirstDelay)
            {
                FC_CL_CPU_DOWN_STAT(3);
                FC_CL_CPU_TO_DOWN_STAT(1);
                /*  首次快降 */
                g_dBsrCpuModu = (100.0 - g_stFcLteCpuCtrl.ulUlDownRate) * g_dBsrCpuModu / 100.0;
                g_dBsrCpuModu = (100.0 - g_stFcLteCpuCtrl.ulUlDownRate) * g_dBsrCpuModu / 100.0;
                g_dBsrCpuModu = (100.0 - g_stFcLteCpuCtrl.ulUlDownRate) * g_dBsrCpuModu / 100.0;
                ulFirstDelay = 0;
            }
            /*CDS_WARNING_LOG2(UEPS_PID_CDS, "FC_LCPU_Process : Modulus: CPU: ", (VOS_UINT32)(g_dBsrCpuModu * 10000.0), arg);*/
        }
        else
        {
            /* Limit = 0.02*150000 */
            if(g_dBsrCpuLimit < g_dBsrCpuModu)
            {
                FC_CL_CPU_DOWN_STAT(1);
                g_dBsrCpuModu = (100.0 - g_stFcLteCpuCtrl.ulUlDownRate) * g_dBsrCpuModu / 100.0;
                /*CDS_WARNING_LOG2(UEPS_PID_CDS, "FC_LCPU_Process : Modulus: CPU: ", (VOS_UINT32)(g_dBsrCpuModu * 10000.0), arg);*/
            }
            else if(g_stFcLteCpuCtrl.ulHqMaxDiscardRate > (100 - g_ulHarqKeepRate))
            {
                /* HARQ降速 */
                FC_HarqDown();
            }
            else
            {
            }
        }
    }
    else if(arg < g_stFcLteCpuCtrl.ulUpgradeThres)
    {
        ulFirstDelay = 0;
        if(g_ulHarqKeepRate < 100)
        {
            /* HARQ升速 */
            FC_HarqUp();
        }
        else if(0.9999 >  g_dBsrCpuModu)
        {
            FC_CL_CPU_UP_STAT(1);
            g_dBsrCpuModu = (100.0 + g_stFcLteCpuCtrl.ulUlUpRate) * g_dBsrCpuModu / 100.0;

            if(1 <  g_dBsrCpuModu)
            {
                g_dBsrCpuModu = 1.0;
                FC_CL_CPU_TO_NORMAL_STAT(1);
            }
            /*CDS_WARNING_LOG1(UEPS_PID_CDS,"FC_LCPU_Process : Modulus: ", (VOS_UINT32)(g_dBsrCpuModu * 10000.0));*/
        }
        else
        {
            ;
        }
     }
    else
    {
        ulFirstDelay = 0;
        /* 不处理 */
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : FC_LDownUlGrade_Process
 功能描述  : LTE温保降速回调函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : SPY_DATA_UPGRADE_RESULT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
SPY_DATA_DOWNGRADE_RESULT_ENUM_UINT32 FC_LDownUlGrade_Process (VOS_VOID)
{
    if(g_stFcLteTemperatureCtrl.ucCurrPos >=  FC_UL_THROUGHPUT_THRES_CNT)
    {
        /*  首次快降 */
        g_stFcLteTemperatureCtrl.ucCurrPos = g_stFcLteTemperatureCtrl.ucInitialPos;

        FC_CL_TEMPERATURE_DOWN_STAT(g_stFcLteTemperatureCtrl.ucInitialPos+1);
    }
    else
    {
        g_stFcLteTemperatureCtrl.ucCurrPos++;

        FC_CL_TEMPERATURE_DOWN_STAT(1);
    }

    if(g_stFcLteTemperatureCtrl.ucCurrPos >= g_stFcLteTemperatureCtrl.ucBsrThresCnt)
    {
        /* 是否启动了入口流控 */
        if(g_stFcLteTemperatureCtrl.ucAvailCnt > g_stFcLteTemperatureCtrl.ucBsrThresCnt)
        {
            g_ulUlDowngradeFlag = PS_TRUE;
        }
        if(g_stFcLteTemperatureCtrl.ucCurrPos >= g_stFcLteTemperatureCtrl.ucAvailCnt)
        {
            /* 校正到最后一个有效位置 */
            g_stFcLteTemperatureCtrl.ucCurrPos = g_stFcLteTemperatureCtrl.ucAvailCnt - 1;
        }
        if(PS_TRUE == g_ulUlDowngradeFlag)
        {
            CDS_WARNING_LOG2(UEPS_PID_CDS,"FC_LDownUlGrade_Process: Downgrade Entry : ->:", g_ulUlThroughputMax, g_stFcLteTemperatureCtrl.ulTemperSteps[g_stFcLteTemperatureCtrl.ucCurrPos]);
            CDS_PRINT_WARNING2(FC_LDownUlGrade_Process_ENUM, CDS_FC_LTE_SPEED_DOWN_GRADE,g_ulUlThroughputMax, g_stFcLteTemperatureCtrl.ulTemperSteps[g_stFcLteTemperatureCtrl.ucCurrPos]);
            g_ulUlThroughputMax = g_stFcLteTemperatureCtrl.ulTemperSteps[g_stFcLteTemperatureCtrl.ucCurrPos];
        }
    }

    if(g_stFcLteTemperatureCtrl.ucCurrPos >= g_stFcLteTemperatureCtrl.ucAvailCnt -1)
    {
        FC_CL_TEMPERATURE_TO_LIMIT_STAT(1);

        CDS_WARNING_LOG1(UEPS_PID_CDS,"FC_LDownUlGrade_Process: Finish : ThresPos:", g_stFcLteTemperatureCtrl.ucCurrPos);
        CDS_PRINT_WARNING1(FC_LDownUlGrade_Process_ENUM, CDS_FC_LTE_SPEED_DOWN_FINISH_POS,g_stFcLteTemperatureCtrl.ucCurrPos);
        return SPY_DATA_DOWNGRADE_FINISH;
    }

    CDS_WARNING_LOG1(UEPS_PID_CDS, "FC_LDownUlGrade_Process : ThresPos: ", g_stFcLteTemperatureCtrl.ucCurrPos);
    CDS_PRINT_WARNING1(FC_LDownUlGrade_Process_ENUM, CDS_FC_LTE_SPEED_DOWN_POS,g_stFcLteTemperatureCtrl.ucCurrPos);

    return SPY_DATA_DOWNGRADE_CONTINUE;
}

/*****************************************************************************
 函 数 名  : FC_LUpUlGrade_Process
 功能描述  : LTE温保升速回调函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : SPY_DATA_UPGRADE_RESULT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
SPY_DATA_UPGRADE_RESULT_ENUM_UINT32 FC_LUpUlGrade_Process (VOS_VOID)
{
    FC_CL_TEMPERATURE_UP_STAT(1);

    if(PS_TRUE == g_ulUlDowngradeFlag)
    {
        if(g_stFcLteTemperatureCtrl.ucBsrThresCnt < g_stFcLteTemperatureCtrl.ucCurrPos)
        {
            CDS_WARNING_LOG2(UEPS_PID_CDS,"FC_LUpUlGrade_Process: Upgrade Entry : ->:", g_ulUlThroughputMax, g_stFcLteTemperatureCtrl.ulTemperSteps[g_stFcLteTemperatureCtrl.ucCurrPos-1]);
            CDS_PRINT_WARNING2(FC_LUpUlGrade_Process_ENUM, CDS_FC_LTE_SPEED_UP_GRADE,g_ulUlThroughputMax, g_stFcLteTemperatureCtrl.ulTemperSteps[g_stFcLteTemperatureCtrl.ucCurrPos-1]);
            g_ulUlThroughputMax = g_stFcLteTemperatureCtrl.ulTemperSteps[g_stFcLteTemperatureCtrl.ucCurrPos-1];
        }
        else
        {   /* 退出入口流控 */
            g_ulUlDowngradeFlag = PS_FALSE;
            g_ulUlThroughputMax = FC_UL_ENTRY_THROUGHPUT_INIT;
            /*g_stFcLteTemperatureCtrl.ucCurrPos = g_stFcLteTemperatureCtrl.ucBsrThresCnt-1;*/
        }
    }

    if(PS_FALSE == g_ulUlDowngradeFlag)
    {
        if((g_stFcLteTemperatureCtrl.ucCurrPos == 0)
            || (g_stFcLteTemperatureCtrl.ucCurrPos >= FC_UL_THROUGHPUT_THRES_CNT))
        {
            g_stFcLteTemperatureCtrl.ucCurrPos = FC_UL_THROUGHPUT_THRES_CNT;
            CDS_WARNING_LOG(UEPS_PID_CDS, "FC_LUpUlGrade_Process: Finish !");
            CDS_PRINT_WARNING(FC_LUpUlGrade_Process_ENUM, CDS_FC_LTE_SPEED_UP_FINISH);
            FC_CL_TEMPERATURE_TO_NORMAL_STAT(1);

            return SPY_DATA_UPGRADE_FINISH;
        }
    }

    g_stFcLteTemperatureCtrl.ucCurrPos--;

    CDS_WARNING_LOG1(UEPS_PID_CDS, "FC_LUpUlGrade_Process : ThresPos: ", g_stFcLteTemperatureCtrl.ucCurrPos);
    CDS_PRINT_WARNING1(FC_LUpUlGrade_Process_ENUM, CDS_FC_LTE_SPEED_UP_POS,g_stFcLteTemperatureCtrl.ucCurrPos);

    return SPY_DATA_UPGRADE_CONTINUE;
}

/*****************************************************************************
 函 数 名  : FC_LRecoverUlGrade_Process
 功能描述  : LTE温保直接恢复回调函数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月29日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_LRecoverUlGrade_Process (VOS_VOID)
{
    FC_CL_TEMPERATURE_RECOVER_STAT(1);

    g_ulUlDowngradeFlag = PS_FALSE;
    g_ulUlThroughputMax = FC_UL_ENTRY_THROUGHPUT_INIT;
    g_stFcLteTemperatureCtrl.ucCurrPos = FC_UL_THROUGHPUT_THRES_CNT;

    CDS_WARNING_LOG1(UEPS_PID_CDS, "FC_LRecoverUlGrade_Process : ThresPos: ", g_stFcLteTemperatureCtrl.ucCurrPos);
    CDS_PRINT_WARNING1(FC_LRecoverUlGrade_Process_ENUM, CDS_FC_LTE_SPEED_RECOVER,g_stFcLteTemperatureCtrl.ucCurrPos);
    return;
}

#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
/*****************************************************************************
 函 数 名  : FC_UlDowngradeInput
 功能描述  : LTE温保用户名入口流控控制
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月8日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_UlDowngradeInput(VOS_VOID)
{
    static VOS_UINT32   ulIPStatTick = 0;
    VOS_UINT32          ulTTI;

    if(PS_FALSE == g_ulUlDowngradeFlag)
    {
        return PS_FALSE;
    }

    ulTTI = LUP_GetCurrentTime()/FC_UL_DOWNGRADE_GAP;

    if((ulTTI != ulIPStatTick))
    {
        ulIPStatTick = ulTTI;
        g_ulUlFcThroughputStat = 1;
    }

    if(g_ulUlFcThroughputStat > g_ulUlThroughputMax)
    {
    	return PS_TRUE;
    }

    return PS_FALSE;
}
#endif

/*****************************************************************************
 函 数 名  : Fc_SwitchToGu
 功能描述  : 流控信息接收模块切换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_SwitchToGu(VOS_VOID)
{
    FC_CL_TO_GU_STAT(1);
#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
    /*释放上行SDU*/
    LUP_RelDataReq();
#endif
    /* 新进入GU，恢复温保流控状态 */
    FC_RecoverUlGradeProcess();

    LDRV_PM_REG_CCPULOAD_CB(FC_CPU_Process);
    Spy_DownGradeRegister(FC_DownUlGradeProcess);
    Spy_UpGradeRegister(FC_UpUlGradeProcess);
    Spy_RestoreRegister(FC_RecoverUlGradeProcess);
    return;
}

/*****************************************************************************
 函 数 名  : Fc_SwitchToLte
 功能描述  : 流控信息接收模块切换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_SwitchToLte(VOS_VOID)
{
    /* 新进入LTE，恢复流控状态 */
    Fc_LteStatusInit();

    FC_CL_TO_LTE_STAT(1);

    LDRV_PM_REG_CCPULOAD_CB(FC_LCPU_Process);
    Spy_DownGradeRegister(FC_LDownUlGrade_Process);
    Spy_UpGradeRegister(FC_LUpUlGrade_Process);
    Spy_RestoreRegister(FC_LRecoverUlGrade_Process);
    return;
}

/*****************************************************************************
 函 数 名  : Fc_SwitchToNull
 功能描述  : 流控信息接收模块切换, 环回或NULL模式
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月24日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_SwitchToNull(VOS_VOID)
{
    FC_CL_TO_NULL_STAT(1);

#if (CDS_FEATURE_ON == CDS_FEATURE_LTE)
    /*释放上行SDU*/
    LUP_RelDataReq();
#endif
    Fc_LteStatusInit();

    LDRV_PM_REG_CCPULOAD_CB(NULL_CPUFcProcess);
    Spy_DownGradeRegister(NULL_DownGradeUlProcess);
    Spy_UpGradeRegister(NULL_UpGradeUlProcess);
    Spy_RestoreRegister(NULL_RecoverUlGradeProcess);
    return;
}

/*****************************************************************************
 函 数 名  : Fc_BufferReportDiscount
 功能描述  : 通过Buffer上报降速
 输入参数  : VOS_UINT32 ulBufferSize
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 g_BsrCheck = 0;
VOS_UINT32 Fc_BufferReportDiscount( VOS_UINT32 ulBufferSize )
{
    VOS_UINT8 ulTmpCurrPos;

    if(PS_FALSE == g_ulUlDowngradeFlag)
    {
        ulTmpCurrPos = g_stFcLteTemperatureCtrl.ucCurrPos;
    }
    else
    {
        if (g_stFcLteTemperatureCtrl.ucBsrThresCnt > 0)
        {
            ulTmpCurrPos = g_stFcLteTemperatureCtrl.ucBsrThresCnt - 1;
        }
        else
        {
            ulTmpCurrPos = FC_UL_THROUGHPUT_THRES_CNT;
        }
    }

    if(ulTmpCurrPos < FC_UL_THROUGHPUT_THRES_CNT)
    {
        if(ulBufferSize > g_stFcLteTemperatureCtrl.ulTemperSteps[ulTmpCurrPos])
        {
            ulBufferSize = g_stFcLteTemperatureCtrl.ulTemperSteps[ulTmpCurrPos];
        }
    }

    /* CPU或温控减速 */
    /* 0.9999浮点逼近 1 */
    if((g_dBsrCpuModu < 0.9999) && (g_stFcLteCpuCtrl.ulUlMinBsr < ulBufferSize))
    {
        ulBufferSize = (VOS_UINT32)(ulBufferSize * g_dBsrCpuModu);
        if(g_stFcLteCpuCtrl.ulUlMinBsr > ulBufferSize)
        {
            FC_CL_BSR_BELOW_MIN_STAT(1);
            ulBufferSize = g_stFcLteCpuCtrl.ulUlMinBsr;
        }
    }
    if(g_BsrCheck)
    {
        if(977 == PS_RAND(3000))
        {
            PS_PRINTF("BSR value:  %d\r\n", ulBufferSize);
        }
    }

    return ulBufferSize;
}

/*****************************************************************************
 函 数 名  : Fc_CdsDlPktDiscard
 功能描述  : 下行共享内存不足流控处理
 输入参数  : VOS_UINT8 ucRabId
 输出参数  : 无
 返 回 值  : VOS_BOOL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月28日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_BOOL Fc_CdsDlPktDiscard(VOS_UINT8 ucRabId)
{
    VOS_UINT32 ulRandValue;

    /* 规避PC-LINT问题，后面扩展下行流控时将用到 */
    (VOS_VOID)ucRabId;
    /*lint -e960*/
    if((g_stFcCdsDlCtrl.bDlCdsFcEnable)
        && (g_stFcCdsDlCtrl.ulDiscardThres > TTF_GetDlIpFreeMemCnt()))

    {
        /* 丢包 */
        ulRandValue = PS_RAND(101);
        if(ulRandValue > g_stFcCdsDlCtrl.ulDiscardRate)
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
    /*lint +e960*/
}

/*****************************************************************************
 函 数 名  : Fc_ShowLtePara
 功能描述  : 显示LTE流控参数
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_ShowLtePara(VOS_VOID)
{
    PS_PRINTF("LTE流控参数 :\r\n");
    PS_PRINTF("\r\n");
    PS_PRINTF("下行CDS流控是否使能   %s\r\n", g_stFcCdsDlCtrl.bDlCdsFcEnable?"Yes":"No");
    PS_PRINTF("下行CDS丢包门限       %d\r\n", g_stFcCdsDlCtrl.ulDiscardThres);
    PS_PRINTF("下行CDS丢包率         %d\r\n", g_stFcCdsDlCtrl.ulDiscardRate);
    PS_PRINTF("\r\n");

    PS_PRINTF("CPU过载流控延迟进入   %d\r\n", g_stFcLteCpuCtrl.ulFirstDelay);
    PS_PRINTF("CPU升速步长百分比     %d\r\n", g_stFcLteCpuCtrl.ulUlUpRate);
    PS_PRINTF("CPU降速步长百分比     %d\r\n", g_stFcLteCpuCtrl.ulUlDownRate);
    PS_PRINTF("CPU降速下限 BSR       %d\r\n", g_stFcLteCpuCtrl.ulUlMinBsr);
    PS_PRINTF("HARQ升速步长百分比    %d\r\n", g_stFcLteCpuCtrl.ulHqUpRate);
    PS_PRINTF("HARQ降速步长百分比    %d\r\n", g_stFcLteCpuCtrl.ulHqDownRate);
    PS_PRINTF("HARQ丢包降速上限      %d\r\n", g_stFcLteCpuCtrl.ulHqMaxDiscardRate);
    PS_PRINTF("CPU降速阈值           %d\r\n", g_stFcLteCpuCtrl.ulDowngradeThres);
    PS_PRINTF("CPU升速阈值           %d\r\n", g_stFcLteCpuCtrl.ulUpgradeThres);
    PS_PRINTF("\r\n");

    PS_PRINTF("降速起始位置          %d\r\n", g_stFcLteTemperatureCtrl.ucInitialPos);
    PS_PRINTF("温保总流控阶数          %d\r\n", g_stFcLteTemperatureCtrl.ucAvailCnt);
    PS_PRINTF("BSR降速阶数           %d\r\n", g_stFcLteTemperatureCtrl.ucBsrThresCnt);
    PS_PRINTF("温保入口控制参数      %d %d %d %d\r\n", g_stFcLteTemperatureCtrl.ulTemperSteps[0],
                                                          g_stFcLteTemperatureCtrl.ulTemperSteps[1],
                                                          g_stFcLteTemperatureCtrl.ulTemperSteps[2],
                                                          g_stFcLteTemperatureCtrl.ulTemperSteps[3]);
    PS_PRINTF("                      %d %d %d %d\r\n",
                                                          g_stFcLteTemperatureCtrl.ulTemperSteps[4],
                                                          g_stFcLteTemperatureCtrl.ulTemperSteps[5],
                                                          g_stFcLteTemperatureCtrl.ulTemperSteps[6],
                                                          g_stFcLteTemperatureCtrl.ulTemperSteps[7]);
    PS_PRINTF("                      %d %d %d %d\r\n",
                                                          g_stFcLteTemperatureCtrl.ulTemperSteps[8],
                                                          g_stFcLteTemperatureCtrl.ulTemperSteps[9],
                                                          g_stFcLteTemperatureCtrl.ulTemperSteps[10],
                                                          g_stFcLteTemperatureCtrl.ulTemperSteps[11]);
    PS_PRINTF("                      %d\r\n", g_stFcLteTemperatureCtrl.ulTemperSteps[12]);

    PS_PRINTF("BSR周期               %d\r\n", g_stFcLteTemperatureCtrl.ulBsrTimerLen);

    PS_PRINTF("\r\n");
    return;
}

/*****************************************************************************
 函 数 名  : Fc_ShowLteStats
 功能描述  : 显示C核LTE流控统计量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_ShowLteStats(VOS_VOID)
{
    PS_PRINTF("C核LTE流控统计 :\r\n");
    PS_PRINTF("\r\n");
    PS_PRINTF("切为LTE模次数               %d\r\n", g_stFcCLStats.ulToLteNum);
    PS_PRINTF("切为GU模次数                %d\r\n", g_stFcCLStats.ulToGUNum);
    PS_PRINTF("进入NULL模式次数            %d\r\n", g_stFcCLStats.ulToNullNum);
    PS_PRINTF("进入LOOPBACK次数            %d\r\n", g_stFcCLStats.ulToLBNum);
    PS_PRINTF("LTE温控降速次数             %d\r\n", g_stFcCLStats.ulTemperatureDownNum);
    PS_PRINTF("LTE温控升速次数             %d\r\n", g_stFcCLStats.ulTemperatureUpNum);
    PS_PRINTF("LTE温控直接恢复次数         %d\r\n", g_stFcCLStats.ulTemperatureRecoverNum);
    PS_PRINTF("LTE温控降速到下限次数       %d\r\n", g_stFcCLStats.ulTemperatureToLimitNum);
    PS_PRINTF("LTE温控恢复到正常次数       %d\r\n", g_stFcCLStats.ulTemperatureToNormalNum);
    PS_PRINTF("LTE CPU过载降速次数         %d\r\n", g_stFcCLStats.ulCpuDownNum);
    PS_PRINTF("LTE CPU恢复升速次数         %d\r\n", g_stFcCLStats.ulCpuUpNum);
    PS_PRINTF("LTE CPU进入降速状态数       %d\r\n", g_stFcCLStats.ulCpuToDownNum);
    PS_PRINTF("LTE CPU恢复到正常次数       %d\r\n", g_stFcCLStats.ulCpuToNormalNum);
    PS_PRINTF("LTE HARQ过载降速次数        %d\r\n", g_stFcCLStats.ulHqDownNum);
    PS_PRINTF("LTE HARQ恢复升速次数        %d\r\n", g_stFcCLStats.ulHqUpNum);
    PS_PRINTF("LTE HARQ降到底次数          %d\r\n", g_stFcCLStats.ulHqToDownNum);
    PS_PRINTF("LTE HARQ恢复到正常次数      %d\r\n", g_stFcCLStats.ulHqToNormalNum);
    PS_PRINTF("LTE上报缓存低于下限         %d\r\n", g_stFcCLStats.ulBelowMinBsr);

    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 函 数 名  : Fc_ShowLteResult
 功能描述  : 显示C核LTE流控结果
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_ShowLteResult(VOS_VOID)
{
    PS_PRINTF("C核LTE流控结果 :\r\n");
    /*lint -e960*/
    PS_PRINTF("\r\n");
    PS_PRINTF("CPU乘数  (*10000)      %05d\r\n", (VOS_UINT32)(g_dBsrCpuModu * 10000));
    PS_PRINTF("HARQ丢包率             %d\r\n", (100 - g_ulHarqKeepRate));
    PS_PRINTF("温保流控当前位置       %d\r\n", g_stFcLteTemperatureCtrl.ucCurrPos);
    PS_PRINTF("温保入口控制状态       %d\r\n", g_ulUlDowngradeFlag);

    PS_PRINTF("\r\n");
    /*lint +e960*/

    return;
}

/*****************************************************************************
 函 数 名  : Fc_ResetLteStats
 功能描述  : 清除LTE流控统计量
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_ResetLteStats(VOS_VOID)
{
    PS_MEM_SET(&g_stFcCLStats, 0, sizeof(FC_CL_STATS_INFO_STRU));
    return;

}

/*****************************************************************************
 函 数 名  : Fc_LteHelp
 功能描述  : LTE流控软调命令
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : w00145177
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Fc_LteHelp(VOS_VOID)
{
    PS_PRINTF("LTE流控软调命令 :\r\n");
    PS_PRINTF("\r\n");
    PS_PRINTF("Fc_ShowLtePara       :显示LTE流控参数\r\n");
    PS_PRINTF("Fc_ShowLteStats      :显示LTE流控统计量\r\n");
    PS_PRINTF("Fc_ResetLteStats     :复位LTE流控统计量\r\n");
    PS_PRINTF("Fc_ShowLteResult     :显示C核LTE流控结果\r\n");

    PS_PRINTF("QosFc_ShowPara       :显示QoS流控参数\r\n");
    PS_PRINTF("QosFc_ShowStats      :显示QoS流控统计量\r\n");
    PS_PRINTF("QosFc_ResetStats     :复位QoS流控统计量\r\n");
    PS_PRINTF("QosFc_ShowState      :显示QoS流控状态\r\n");
    PS_PRINTF("QosFc_ShowRabState   :显示QoS流控承载状态\r\n");
    PS_PRINTF("QosFc_ShowEntity     :显示Qos流控实体状态\r\n");
    PS_PRINTF("QosFc_ShowChannel    :显示Qos流控通道状态\r\n");

    PS_PRINTF("\r\n");
    return;

}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



