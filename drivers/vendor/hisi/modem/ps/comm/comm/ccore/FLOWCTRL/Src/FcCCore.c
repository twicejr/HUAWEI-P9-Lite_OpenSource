/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : FcCCORE.c
  版 本 号   : 初稿
  作    者   : g45205
  生成日期   : 2011年12月21日
  最近修改   :
  功能描述   : CCORE流控功能
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月21日
    作    者   : g45205
    修改内容   : 创建文件

******************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "Fc.h"
#include "FcInterface.h"
#include "FcIntraMsg.h"
#include "PsCommonDef.h"
#include "PsLib.h"
#include "OmApi.h"
#include "R_ITF_FlowCtrl.h"
#include "FcMacInterface.h"
#include "RabmInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e534*/
#define    THIS_FILE_ID        PS_FILE_ID_CCORE_FLOW_CTRL_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
VOS_UINT32                              g_ulFcUlRateCpu = FC_HSUPA_RATE_MAX_KBPS;
VOS_UINT32                              g_ulFcUlRateTmp = FC_HSUPA_RATE_MAX_KBPS;

FC_CPU_CTRL_STRU                        g_stFcCpuCCtrl;

FC_TRACE_CPULOAD_STRU                   g_stFcTraceCpuLoad  =
{
    FC_CCPU_TRACE_CPULOAD_TIMELEN,
    0,
    VOS_NULL_PTR
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : FC_UL_GetRate
 功能描述  : 控制HSUPA上行发送速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 流控限制
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_UL_GetRate( VOS_VOID )
{
    /* 返回上行发送速率限制 = MIN(CPU速率，温保速率) */
    return PS_MIN(g_ulFcUlRateCpu*1024, g_ulFcUlRateTmp*1024);
}


/*****************************************************************************
 函 数 名  : FC_UL_UpRateLimit
 功能描述  : 加强HSUPA上行发送速率限制，降低发送速率
 输入参数  : ulSndRate    --  发送速率百分比
             ulPolicyMask --  流控策略掩码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_UL_UpRateLimit( VOS_UINT32 ulUlRate, VOS_UINT32 ulPolicyId )
{
    VOS_UINT32                          ulRateLimit;


    /* 前16位记录当前档位的流控百分比，用于启流控 */
    ulRateLimit = ulUlRate >> 16;

    if ( FC_POLICY_MASK_CPU_C == FC_POLICY_MASK(ulPolicyId))
    {
        g_ulFcUlRateCpu = ulRateLimit;
    }
    else if ( FC_POLICY_MASK_TMP == FC_POLICY_MASK(ulPolicyId))
    {
        g_ulFcUlRateTmp = ulRateLimit;
    }
    else
    {
        FC_LOG1(PS_PRINT_WARNING,
                "FC_UL_UpRateLimit, ERROR, Invalid ulPolicyId %d\n",
                (VOS_INT32)ulPolicyId);
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_UL_DownRateLimit
 功能描述  : 减弱HSUPA上行发送速率限制，提高发送速率
 输入参数  : ulSndRate    --  发送速率百分比
             ulPolicyMask --  流控策略掩码
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_UL_DownRateLimit( VOS_UINT32 ulUlRate, VOS_UINT32 ulPolicyId )
{
    VOS_UINT32                          ulRateLimit;


    /* 后16位记录下一个更低先级档位的流控百分比，用于解流控 */
    ulRateLimit = ulUlRate & FC_DOWN_RATE_LIMIT_MASK;

    if ( FC_POLICY_MASK_CPU_C == FC_POLICY_MASK(ulPolicyId))
    {
        g_ulFcUlRateCpu = ulRateLimit;
    }
    else if ( FC_POLICY_MASK_TMP == FC_POLICY_MASK(ulPolicyId))
    {
        g_ulFcUlRateTmp = ulRateLimit;
    }
    else
    {
        FC_LOG1(PS_PRINT_WARNING,
                "FC_UL_DownRateLimit, ERROR, Invalid ulPolicyId %d\n",
                (VOS_INT32)ulPolicyId);
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_UL_InitFcPoints
 功能描述  : 控制HSUPA上行发送速率
 输入参数  : ucPolicyId --  策略ID
             pstUlFcCfg --  策略流控配置
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_UL_InitFcPoints
(
    FC_POLICY_ID_ENUM_UINT8             enPolicyId,
    FC_CFG_UM_UL_RATE_STRU             *pstUlFcCfg
)
{
    FC_REG_POINT_STRU                   stFcRegPoint;
    VOS_UINT32                          ulRateLoop;
    VOS_UINT16                          usCurrRate;
    VOS_UINT16                          usPrevRate = FC_HSUPA_RATE_MAX_KBPS;
    FC_ID_ENUM_UINT8                    enFcId;
    FC_PRI_ENUM_UINT8                   enPri = FC_PRI_LOWEST;

    if (FC_POLICY_ID_CPU_C == enPolicyId)
    {
        enFcId = FC_ID_UL_RATE_1_FOR_CPU;
    }
    else if (FC_POLICY_ID_TMP == enPolicyId)
    {
        enFcId = FC_ID_UL_RATE_1_FOR_TMP;
    }
    /* 目前，只针对CCPU和TMP提供了按档位控速率功能，其他函数不能使用 */
    else
    {
        FC_LOG1(PS_PRINT_WARNING,
                "FC_UL_InitFcPoints, ERROR, wrong ulPolicyId %d\n",
                (VOS_INT32)enPolicyId);

        return VOS_ERR;
    }

    /* NV项中CCPU和TMP的档位预留了最大11档，但是优先级最高为FC_PRI_9，所以使用档位时只有前9档生效 */
    for ( ulRateLoop = 0 ; ulRateLoop < pstUlFcCfg->ucRateCnt ; ulRateLoop++ )
    {
        usCurrRate = pstUlFcCfg->ausRate[ulRateLoop];

        stFcRegPoint.enPolicyId = enPolicyId;
        stFcRegPoint.enFcPri    = enPri;
        stFcRegPoint.enFcId     = enFcId;
        stFcRegPoint.enModemId  = MODEM_ID_0;

        /* 解流控时将数率限制设为上一档 */
        stFcRegPoint.ulParam1   = (((VOS_UINT32)usCurrRate) << 16) | (((VOS_UINT32)usPrevRate) & FC_DOWN_RATE_LIMIT_MASK);
        stFcRegPoint.ulParam2   = enPolicyId;
        stFcRegPoint.pSetFunc   = (FC_SET_FUNC)FC_UL_UpRateLimit;
        stFcRegPoint.pClrFunc   = (FC_CLR_FUNC)FC_UL_DownRateLimit;
        stFcRegPoint.pRstFunc   = VOS_NULL_PTR;

        FC_POINT_Reg(&stFcRegPoint);

        enFcId++;

        if ( FC_PRI_HIGHEST == enPri )
        {
            break;
        }

        enPri++;
        usPrevRate = usCurrRate;

    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CPUC_UpJudge
 功能描述  : 两核共用CPU负载处理接口
 输入参数  : ulCpuIdleValue  --  当前CPU空闲量0~100
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_CPUC_UpJudge
(
    VOS_UINT32       ulCpuLoad,
    FC_CFG_CPU_STRU *pstFcCfgCpu,
    FC_POLICY_STRU  *pstFcPolicy
)
{
    if ( ulCpuLoad < pstFcCfgCpu->ulCpuOverLoadVal )
    {
        g_stFcCpuCCtrl.ulSmoothTimerLen =0;
        return VOS_FALSE;
    }

    if (pstFcPolicy->enHighestPri <= pstFcPolicy->enDonePri)
    {
        return VOS_FALSE;
    }

    if ( FC_PRI_NULL != pstFcPolicy->enDonePri )
    {
        return VOS_TRUE;
    }


    /*================================*//* 当第一次起流控时，做平滑处理  */
    g_stFcCpuCCtrl.ulSmoothTimerLen++;

    if (g_stFcCpuCCtrl.ulSmoothTimerLen < pstFcCfgCpu->ulSmoothTimerLen)
    {
        return VOS_FALSE;
    }

    g_stFcCpuCCtrl.ulSmoothTimerLen  = 0;

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : FC_CPUC_DownJudge
 功能描述  : 两核共用CPU负载处理接口
 输入参数  : ulCpuIdleValue  --  当前CPU空闲量0~100
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_CPUC_DownJudge
(
    VOS_UINT32       ulCpuLoad,
    FC_CFG_CPU_STRU *pstFcCfgCpu,
    FC_POLICY_STRU  *pstFcPolicy
)
{

    if ( (ulCpuLoad < pstFcCfgCpu->ulCpuUnderLoadVal)
         && (FC_PRI_NULL < pstFcPolicy->enDonePri) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_CpuCUpProcess
 功能描述  : CST流控策略
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CPUC_UpProcess( VOS_VOID )
{
    FC_POLICY_STRU                     *pFcPolicy;


    /*================================*//* 获取CPU流控策略实体，并调用通用流控策略 */
    pFcPolicy   = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CPU_C_MODEM_0);
    FC_POLICY_Up(pFcPolicy);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_CpuCDownProcess
 功能描述  : CST流控策略
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CPUC_DownProcess( VOS_VOID )
{
    FC_POLICY_STRU                     *pPolicy;


    /*================================*//* 获取CPU流控策略实体，并调用通用流控策略 */
    pPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CPU_C_MODEM_0);
    FC_POLICY_Down(pPolicy);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_FcNotifyProcess
 功能描述  : 收到流控启停消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月10日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_FcNotifyProcess(VOS_RATMODE_ENUM_UINT32 enRateMode)
{
    /* 根据当前最新流控状态启停流控 */
    if (R_ITF_FLOW_CTRL_START == g_stRItfFlowCtrl.ulCtrlFlag)
    {
        R_ITF_StartFlowCtrl(enRateMode);
    }
    else
    {
        R_ITF_StopFlowCtrl(enRateMode);
    }
}


/*****************************************************************************
 函 数 名  : FC_CPUC_Init
 功能描述  : CPU负载流控初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月23日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CPUC_Init( VOS_VOID )
{
    VOS_UINT32                          ulResult;


    ulResult = FC_UL_InitFcPoints(FC_POLICY_ID_CPU_C, &(g_stFcCfg.stFcCfgUmUlRateForCpu));

    if ( VOS_OK != ulResult )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_Init, ERROR, Fail to init FC Points for CPU!\n");
        return VOS_ERR;
    }

    VOS_MemSet(&g_stFcCpuCCtrl, 0, sizeof(g_stFcCpuCCtrl));

    ulResult = VOS_StartRelTimer(&g_stFcTraceCpuLoad.pstTraceCpuLoadTHandle, UEPS_PID_FLOWCTRL_C,
                                  g_stFcTraceCpuLoad.ulTraceCpuLoadTimerLen,
                                  TIMER_FC_CCPU_TRACE_CPULOAD, 0,
                                  VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
    if (VOS_OK != ulResult)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_Init, ERROR, Fail to Start Timer!\n");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CPU_Process
 功能描述  : C核流控模块提供的CPU负载处理接口，该函数目前在中断中调用，不能有阻塞性操作
 输入参数  : ulCpuLoad  --  当前CPU占用率0~100
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_CPU_Process( VOS_UINT32 ulCpuLoad )
{
    FC_CFG_CPU_STRU                    *pstFcCfgCpu;
    FC_POLICY_STRU                     *pstFcPolicy;
    VOS_UINT32                          ulStartCtrl;


    /*====================================*//* 使能检查 */
    if ( FC_POLICY_MASK_CPU_C != (FC_POLICY_MASK_CPU_C & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* CPU流控未使能，在中断中被调用，故使用LogPrint */
        (VOS_VOID)LogPrint1("FC_CPU_Process, INFO, CPU FlowCtrl is disabled %d.\r\n", (VOS_INT32)g_stFcCfg.ulFcEnbaleMask );
        return 0;
    }

    /*================================*//* 参数检查 */
    if ( 100 < ulCpuLoad )
    {
        /* 参数非法，在中断中被调用，故使用LogPrint */
        (VOS_VOID)LogPrint1("FC_CPU_Process, WARNING, Invalid Cpu Load %d.\r\n", (VOS_INT32)ulCpuLoad);
        return 0;
    }

    /* 记录CPU负载数据到全局变量中 */
    g_stFcTraceCpuLoad.ulCpuLoadRecord   = ulCpuLoad;

    pstFcPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CPU_C_MODEM_0);
    pstFcCfgCpu = &(g_stFcCfg.stFcCfgCpuC);

    /*================================*//* 是否要进行CPU流控 */
    ulStartCtrl = FC_CPUC_UpJudge(ulCpuLoad, pstFcCfgCpu, pstFcPolicy);
    if (VOS_TRUE == ulStartCtrl)
    {
        FC_SndCpuMsg(ID_FC_CPU_C_OVERLOAD_IND, ulCpuLoad, 0, 0);

        /* 环回模式下，启动丢包流控 */
        NAS_RABM_SetTcFlowCtrl();

        return 0;
    }

    /*================================*//* 进行CPU解流控判决 */
    ulStartCtrl = FC_CPUC_DownJudge(ulCpuLoad, pstFcCfgCpu, pstFcPolicy);
    if ( VOS_TRUE ==  ulStartCtrl )
    {
        FC_SndCpuMsg(ID_FC_CPU_C_UNDERLOAD_IND, ulCpuLoad, 0, 0);

        /* 环回模式下，停止丢包流控 */
        NAS_RABM_ClearTcFlowCtrl();

        return 0;
    }

    if ( ulCpuLoad <= pstFcCfgCpu->ulCpuOverLoadVal )
    {
        /* 环回模式下，停止丢包流控 */
        NAS_RABM_ClearTcFlowCtrl();
    }

    return 0;
}


/*****************************************************************************
 函 数 名  : FC_TEMPERATURE_UpProcess
 功能描述  : 温保流控策略，温度升高处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_TEMPERATURE_UpProcess( VOS_VOID )
{
    FC_POLICY_STRU                     *pstFcPolicy;


    /*================================*//* 获取CPU流控策略实体，并调用通用流控策略 */
    pstFcPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_TMP_MODEM_0);
    FC_POLICY_Up(pstFcPolicy);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_TEMPERATURE_DownProcess
 功能描述  : 温保流控策略，温度降低处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_TEMPERATURE_DownProcess( VOS_VOID )
{
    FC_POLICY_STRU                     *pPolicy;


    /*================================*//* 获取CPU流控策略实体，并调用通用流控策略 */
    pPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_TMP_MODEM_0);
    FC_POLICY_Down(pPolicy);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_TEMPERATURE_RecoverProcess
 功能描述  : 温保流控策略，温度降低处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_TEMPERATURE_RecoverProcess( VOS_VOID )
{
    FC_POLICY_STRU                     *pPolicy;


    /*================================*//* 获取CPU流控策略实体，并调用通用流控策略 */
    pPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_TMP_MODEM_0);
    FC_POLICY_DownToTargetPri(pPolicy, FC_PRI_NULL);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_SndTemperatureMsg
 功能描述  : 发送温保流控消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_TEMPERATURE_SndCtrlMsg
(
    FC_MSG_TYPE_ENUM_UINT16 usMsgName
)
{
    VOS_UINT32                          ulResult;
    FC_TEMPERATURE_IND_STRU            *pstMsg;


    pstMsg = (FC_TEMPERATURE_IND_STRU *)VOS_AllocMsg(UEPS_PID_FLOWCTRL, \
                                        sizeof(FC_TEMPERATURE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_SndIntraTemperatureMsg, Alloc Msg Fail\n");
        return VOS_ERR;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL;
    pstMsg->usMsgName       = usMsgName;

    ulResult = VOS_SendMsg(UEPS_PID_FLOWCTRL, pstMsg);

    if (VOS_OK != ulResult)
    {
        FC_LOG(PS_PRINT_ERROR,"FC_SndIntraTemperatureMsg, Send Msg Fail\n");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_TEMPERATURE_Init
 功能描述  : 温保流控初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月23日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_TEMPERATURE_Init( VOS_VOID )
{
    VOS_UINT32                          ulResult;


    /* 创建温保流控点实例 */
    ulResult = FC_UL_InitFcPoints(FC_POLICY_ID_TMP, &(g_stFcCfg.stFcCfgUmUlRateForTmp));

    return ulResult;
}


/*****************************************************************************
 函 数 名  : FC_DownUlGradeProcess
 功能描述  : OM温控模块检测到温度过高需要降速时，调用注册的过温降速处理API，降速减功耗。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OM_DATA_DOWMGRADE_CONTINUE --  可以继续控
             OM_DATA_DOWNGRADE_FINISH   --  不能继续控
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
SPY_DATA_DOWNGRADE_RESULT_ENUM_UINT32 FC_DownUlGradeProcess(VOS_VOID)
{
    FC_POLICY_STRU                     *pstFcPolicy;

    if ( FC_POLICY_MASK_TMP != (FC_POLICY_MASK_TMP & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 温控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_DownUlGradeProcess, INFO, TMP FlowCtrl is disabled %d\n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return SPY_DATA_DOWNGRADE_FINISH;
    }

    pstFcPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_TMP_MODEM_0);

    if ( pstFcPolicy->enHighestPri <= pstFcPolicy->enDonePri )
    {
        /* 已经达到流控最高级别，无法继续执行流控 */
        return SPY_DATA_DOWNGRADE_FINISH;
    }

    (VOS_VOID)FC_TEMPERATURE_SndCtrlMsg(ID_FC_TEMPERATURE_OVERLOAD_IND);

    return SPY_DATA_DOWNGRADE_CONTINUE;
}


/*****************************************************************************
 函 数 名  : FC_UpUlGradeProcess
 功能描述  : OM温控模块检测到温度恢复可以升速时，调用注册的升速处理API
 输入参数  : 无
 输出参数  : 无
 返 回 值  : OM_DATA_DOWMGRADE_CONTINUE --  可以继续控
             OM_DATA_DOWNGRADE_FINISH   --  不能继续控
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
SPY_DATA_UPGRADE_RESULT_ENUM_UINT32 FC_UpUlGradeProcess(VOS_VOID)
{
    FC_POLICY_STRU                     *pstFcPolicy;

    if ( FC_POLICY_MASK_TMP != (FC_POLICY_MASK_TMP & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 温控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_UpUlGradeProcess, INFO, TMP FlowCtrl is disabled %d\n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return SPY_DATA_UPGRADE_FINISH;
    }

    pstFcPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_TMP_MODEM_0);

    if ( FC_PRI_NULL == pstFcPolicy->enDonePri )
    {
        /* 已经达到流控最低级别，无法继续解流控 */
        return SPY_DATA_UPGRADE_FINISH;
    }

    (VOS_VOID)FC_TEMPERATURE_SndCtrlMsg(ID_FC_TEMPERATURE_UNDERLOAD_IND);

    return SPY_DATA_UPGRADE_CONTINUE;
}


/*****************************************************************************
 函 数 名  : FC_RecoverUlGradeProcess
 功能描述  : 恢复上行速率，不做限制
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月18日
    作    者   : FC_RecoverUlGradeProcess
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_RecoverUlGradeProcess( VOS_VOID )
{
    FC_POLICY_STRU                     *pstFcPolicy;


    if ( FC_POLICY_MASK_TMP != (FC_POLICY_MASK_TMP & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 温控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_RecoverUlGradeProcess, INFO, TMP FlowCtrl is disabled %d\n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return;
    }

    pstFcPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_TMP_MODEM_0);

    if ( FC_PRI_NULL == pstFcPolicy->enDonePri )
    {
        /* 已经恢复，无须再处理 */
        return;
    }

    (VOS_VOID)FC_TEMPERATURE_SndCtrlMsg(ID_FC_TEMPERATURE_RECOVER_IND);

    return;
}


/*****************************************************************************
 函 数 名  : FC_IntraMsgProc
 功能描述  : 流控流控消息处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CCORE_RcvIntraMsg( MsgBlock * pMsg )
{
    switch( FC_GET_MSG_NAME16(pMsg) )
    {
        case ID_FC_REG_POINT_IND:
            FC_POINT_Reg( &(((FC_REG_POINT_IND_STRU *)pMsg)->stFcPoint) );
            break;

        case ID_FC_DEREG_POINT_IND:
            FC_POINT_DeReg( ((FC_DEREG_POINT_IND_STRU *)pMsg)->enFcId,
                            ((FC_DEREG_POINT_IND_STRU *)pMsg)->enModemId );
            break;

        case ID_FC_CHANGE_POINT_IND:
            /* add by wangrong */
            FC_POINT_Change( ((FC_CHANGE_POINT_IND_STRU *)pMsg)->enFcId,
                             ((FC_CHANGE_POINT_IND_STRU *)pMsg)->enPolicyId,
                             ((FC_CHANGE_POINT_IND_STRU *)pMsg)->enPri,
                             ((FC_CHANGE_POINT_IND_STRU *)pMsg)->enModemId);
            /* add by wangrong */
            break;

        case ID_FC_TEMPERATURE_OVERLOAD_IND:
            FC_TEMPERATURE_UpProcess();
            break;

        case ID_FC_TEMPERATURE_UNDERLOAD_IND:
            FC_TEMPERATURE_DownProcess();
            break;

        case ID_FC_TEMPERATURE_RECOVER_IND:
            FC_TEMPERATURE_RecoverProcess();
            break;

        case ID_FC_CPU_C_OVERLOAD_IND:
            FC_CPUC_UpProcess();
            break;

        case ID_FC_CPU_C_UNDERLOAD_IND:
            FC_CPUC_DownProcess();
            break;

        case ID_FC_C_FLOWCTRL_NOTIFY:
            FC_FcNotifyProcess(((FC_FLOWCTRL_NOTIFY_STRU *)pMsg)->enRateMode);
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_CCORE_RcvTimerExpireMsg
 功能描述  : 接收定时器消息的分发处理
 输入参数  : REL_TIMER_MSG *pTimerMsg
 输出参数  : 无
 返 回 值  : 无
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月21日
    作    者   : caikai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_CCORE_RcvTimerExpireMsg(REL_TIMER_MSG *pTimerMsg)
{
    VOS_UINT32                          ulResult;


    switch (pTimerMsg->ulName)
    {
        case TIMER_FC_CCPU_TRACE_CPULOAD:
            /*====================================*//* 输出可维可测 */
            FC_MNTN_TraceCpuLoad(ID_FC_MNTN_CPU_C_CPULOAD, g_stFcTraceCpuLoad.ulCpuLoadRecord);

            /* 重启定时器 */
            ulResult = VOS_StartRelTimer(&g_stFcTraceCpuLoad.pstTraceCpuLoadTHandle, UEPS_PID_FLOWCTRL_C,
                                          g_stFcTraceCpuLoad.ulTraceCpuLoadTimerLen,
                                          TIMER_FC_CCPU_TRACE_CPULOAD, 0,
                                          VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
            if (VOS_OK != ulResult)
            {
                FC_LOG2(PS_PRINT_ERROR, "FC_Init, ERROR, Fail to Start Timer! ulResult = %d, ulTraceCpuLoadTimerLen = %d\n", (VOS_INT32)ulResult, (VOS_INT32)g_stFcTraceCpuLoad.ulTraceCpuLoadTimerLen);
                return;
            }

            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : FC_MsgProc
 功能描述  : 流控消息处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CCORE_MsgProc( MsgBlock * pMsg )
{
    switch (pMsg->ulSenderPid)
    {
        case UEPS_PID_FLOWCTRL_C:
            FC_CCORE_RcvIntraMsg(pMsg);
            break;

        case VOS_PID_TIMER:
            FC_CCORE_RcvTimerExpireMsg( (REL_TIMER_MSG *)pMsg );
            break;

        default:
            break;
    }

    return VOS_OK;
} /* FC_MsgProc */


/*****************************************************************************
 函 数 名  : FC_Init
 功能描述  : 流控模块初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CCORE_Init( VOS_VOID )
{
    VOS_UINT32                          ulResult;


    ulResult = FC_CommInit();

    if ( VOS_OK != ulResult )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_Init, ERROR, FC_CommInit return error!\n");
        return VOS_ERR;
    }

    ulResult    = FC_CPUC_Init();
    if ( VOS_OK != ulResult )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_Init, ERROR, FC_CPUC_Init error!\n");
        return VOS_ERR;
    }

    ulResult    = FC_TEMPERATURE_Init();
    if ( VOS_OK != ulResult )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_Init, ERROR, FC_TEMPERATURE_Init error!\n");
        return VOS_ERR;
    }

    /* 挂接 UL_DATA_POOL 内存池的监测函数 */
    R_ITF_InitFlowCtrl();

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_FidInit
 功能描述  : 流控FID初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE enPhase
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月14日
    作    者   :
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 FC_CCORE_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    VOS_UINT32  ulResult = VOS_ERR;

    switch (enPhase)
    {
        case   VOS_IP_LOAD_CONFIG:

            ulResult = VOS_RegisterPIDInfo(UEPS_PID_FLOWCTRL,
                                           (Init_Fun_Type)VOS_NULL_PTR,
                                           (Msg_Fun_Type)FC_CCORE_MsgProc);
            if (VOS_OK != ulResult)
            {
                FC_LOG(PS_PRINT_ERROR, "FC_FidInit, VOS_RegisterPIDInfo Fail\n");
                return VOS_ERR;
            }

            ulResult = VOS_RegisterTaskPrio(UEPS_FID_FLOWCTRL, TTF_FLOW_CTRL_TASK_PRIO);

            if (VOS_OK != ulResult)
            {
                FC_LOG(PS_PRINT_ERROR, "FC_FidInit, OS_RegisterTaskPrio Fail\n");
                return VOS_ERR;
            }

            ulResult = FC_CCORE_Init();

            if (VOS_OK != ulResult)
            {
                FC_LOG(PS_PRINT_ERROR, "FC_FidInit, Call FC_Init return error!\n");
                return VOS_ERR;
            }

            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
            break;
        default:
            break;
    }

    return VOS_OK;
}
/*lint -restore */
/*lint +e534*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

