
 
#ifdef __cplusplus
#if __cplusplus
     extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "product_config.h"
#if(FEATURE_ON == FEATURE_ACPU_FC_POINT_REG)
#include "Fc.h"
#include "FcInterface.h"
#include "FcCdsInterface.h"
#include "FcCstInterface.h"
#include "AtFcInterface.h"
#include "AdsFcInterface.h"
#include "ACpuLoadInterface.h"
#include "ImmInterface.h"
#include "NFExtInterface.h"
#include "FcIntraMsg.h"
#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "PsLib.h"
#include "TTFTaskPriority.h"
#include "NVIM_Interface.h"
#include "FcACoreCReset.h"


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_ACORE_FLOW_CTRL_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 网桥速率统计使用的变量 */
FC_BRIDGE_RATE_STRU                     g_stFcBridgeRate;

/* CDS流控使用的全局变量，FC IdRAB映射关系 */

FC_RAB_MAPPING_INFO_SET_STRU            g_astFcRabMappingInfoSet[MODEM_ID_BUTT];

/* CPU流控使用，包括平滑次数，定时器 */
FC_CPU_CTRL_STRU                        g_stFcCpuACtrl;

FC_CPU_DRV_ASSEM_CONFIG_PARA_STRU       g_stCpuDriverAssePara =
{
    6,
    10,
    5,
    0,
    {
    /* cpuload, PC驱动组包时延，UE驱动TX组包个数, UE驱动TX时延，UE驱动RX组包个数，UE驱动RX组包时延，保留域 */
        {
            85,{20, 40, 10, 10, 10, 56, {0, 0}}
        },
        {
            70,{15, 20, 10, 10, 10, 20, {0, 0}}
        },
        {
            60,{10, 10, 10, 10, 10, 5, {0, 0}}
        },
        {
            40,{5,  5,  10, 10, 10, 1, {0, 0}}
        },
        {
            0, {0,  1,  1,  1,  1, 1, {0, 0}}
        }
    }
};

/* 驱动组包参数实体结构 */
FC_CPU_DRV_ASSEM_PARA_ENTITY_STRU  g_stDrvAssemParaEntity = {0, 0, 0, 0, 0, {0, 0, 0, 0}, {100, {0, 0, 0, 0, 0, 0, {0, 0}}}, VOS_NULL_PTR, VOS_NULL_PTR};

VOS_SPINLOCK                       g_stFcMemSpinLock;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
#if(FEATURE_ON == FEATURE_NFEXT)
/*****************************************************************************
 函 数 名  : FC_CalcBridgeRate
 功能描述  : 计算网桥上的速率,单位:bps
 输入参数  : ulPeriod -- 网桥速率统计周期，单位毫秒
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_BRIDGE_CalcRate( VOS_UINT32 ulPeriod )
{
    VOS_UINT32                          ulCurrentByteCnt;
    VOS_UINT32                          ulLastByteCnt;
    VOS_UINT32                          ulRate;
    VOS_UINT32                          ulDeltaPacketCnt;

    if (0 == ulPeriod)
    {
        g_stFcBridgeRate.ulRate = 0;
        return;
    }

    ulLastByteCnt       = g_stFcBridgeRate.ulLastByteCnt;
    ulCurrentByteCnt    = NFExt_GetBrBytesCnt();
    ulDeltaPacketCnt    = (ulCurrentByteCnt - ulLastByteCnt);

    /* 换算成bps,注意防止计算溢出 */
    if (ulDeltaPacketCnt < ulPeriod)
    {
        ulRate = (ulDeltaPacketCnt * 1000 * 8) / ulPeriod ;
    }
    else
    {
        ulRate = ((ulDeltaPacketCnt * 8) / ulPeriod) * 1000;
    }


    g_stFcBridgeRate.ulLastByteCnt      = ulCurrentByteCnt;
    g_stFcBridgeRate.ulRate             = ulRate;

    return;
}


/*****************************************************************************
 函 数 名  : FC_ResetBridgeRate
 功能描述  : 清除网桥速率统计
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_BRIDGE_ResetRate( VOS_VOID )
{
    g_stFcBridgeRate.ulLastByteCnt      = NFExt_GetBrBytesCnt();
    g_stFcBridgeRate.ulRate             = 0;
}


/*****************************************************************************
 函 数 名  : FC_GetBridgeRate
 功能描述  : 获取网桥速率统计值，单位:bps
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 网桥速率
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_BRIDGE_GetRate( VOS_VOID )
{
    return(g_stFcBridgeRate.ulRate);
}


/*****************************************************************************
 函 数 名  : FC_RmRateJudge
 功能描述  : Rm速率是否达到引发CPU流控的门限
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:达到门限，VOS_FALSE:没有达到门限
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_RmRateJudge( VOS_VOID )
{
    /* 如果网桥速率超过门限，则认为是速率高引起CPU高 */
    if (g_stFcBridgeRate.ulRate > g_stFcCfg.stFcCfgCpuA.ulRmRateThreshold)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#else
/*****************************************************************************
 函 数 名  : FC_CalcBridgeRate
 功能描述  : 计算网桥上的速率,单位:bps
 输入参数  : ulPeriod -- 网桥速率统计周期，单位毫秒
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_BRIDGE_CalcRate( VOS_UINT32 ulPeriod )
{
    return;
}


/*****************************************************************************
 函 数 名  : FC_ResetBridgeRate
 功能描述  : 清除网桥速率统计
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_BRIDGE_ResetRate( VOS_VOID )
{
    return;
}
#endif

/*****************************************************************************
 函 数 名  : FC_ACORE_RegDrvAssemFunc
 功能描述  : 注册驱动组包参数调整回调函数
 输入参数  : FC_ACORE_DRV_ASSEMBLE_PARA_FUNC pFcDrvSetAssemParaFuncUe  调整UE组包参数回调函数
             FC_ACORE_DRV_ASSEMBLE_PARA_FUNC pFcDrvSetAssemParaFuncPc  调整PC组包参数回调函数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_ACORE_RegDrvAssemFunc(FC_ACORE_DRV_ASSEMBLE_PARA_FUNC pFcDrvSetAssemParaFuncUe, FC_ACORE_DRV_ASSEMBLE_PARA_FUNC pFcDrvSetAssemParaFuncPc)
{
    FC_ADS_DRV_ASSEM_STRU stFcAdsAssemEntity;

    g_stDrvAssemParaEntity.pDrvSetAssemParaFuncUe = pFcDrvSetAssemParaFuncUe;
    g_stDrvAssemParaEntity.pDrvSetAssemParaFuncPc = pFcDrvSetAssemParaFuncPc;

    stFcAdsAssemEntity.ucEnableMask         = g_stCpuDriverAssePara.ucEnableMask;
    stFcAdsAssemEntity.ulDlRateUpLev        = FC_ADS_DL_RATE_UP_LEV;
    stFcAdsAssemEntity.ulDlRateDownLev      = FC_ADS_DL_RATE_DOWN_LEV;
    stFcAdsAssemEntity.ulExpireTmrLen       = FC_ADS_TIMER_LEN;
    stFcAdsAssemEntity.pDrvAssemFunc        = FC_JudgeDrvToMaxPara;

    ADS_DL_RegDrvAssemFunc(&stFcAdsAssemEntity);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_ShowDrvAssemPara
 功能描述  : 驱动可维可测打印信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月14日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_ShowDrvAssemPara(VOS_VOID)
{
    FC_CPU_DRV_ASSEM_PARA_STRU *pstCpuDrvAssemPara  = VOS_NULL_PTR;
    VOS_INT i = 0;

    (VOS_VOID)vos_printf("g_stCpuDriverAssePara.ucEnableMask = %d\n", g_stCpuDriverAssePara.ucEnableMask);
    (VOS_VOID)vos_printf("g_stDrvAssemParaEntity.stCurAssemLevPara.ulLev = %d\n", g_stDrvAssemParaEntity.ulCurLev);
    (VOS_VOID)vos_printf("g_stDrvAssemParaEntity.stCurAssemPara.ucEthTxMinNum = %d\n", g_stDrvAssemParaEntity.stCurAssemPara.stDrvAssemPara.ucEthTxMinNum);
    (VOS_VOID)vos_printf("g_stDrvAssemParaEntity.stCurAssemPara.ucCdsGuDlThres = %d\n", g_stDrvAssemParaEntity.stCurAssemPara.stDrvAssemPara.ucCdsGuDlThres);
    (VOS_VOID)vos_printf("g_stDrvAssemParaEntity.ucSmoothCntUp = %d\n", g_stDrvAssemParaEntity.ucSmoothCntUp);
    (VOS_VOID)vos_printf("g_stDrvAssemParaEntity.ucSmoothCntDown = %d\n", g_stDrvAssemParaEntity.ucSmoothCntDown);
    (VOS_VOID)vos_printf("g_stCpuDriverAssePara.ucSmoothCntUpLev = %d\n", g_stCpuDriverAssePara.ucSmoothCntUpLev);
    (VOS_VOID)vos_printf("g_stCpuDriverAssePara.ucSmoothCntDownLev = %d\n", g_stCpuDriverAssePara.ucSmoothCntDownLev);
    (VOS_VOID)vos_printf("g_stDrvAssemParaEntity.pDrvSetAssemParaFunc = %p\n", g_stDrvAssemParaEntity.pDrvSetAssemParaFuncUe);
    (VOS_VOID)vos_printf("g_stDrvAssemParaEntity.ucSetDrvFailCnt = 0x%x\n", g_stDrvAssemParaEntity.ucSetDrvFailCnt);

    for (i = 0; i < FC_ACPU_DRV_ASSEM_LEV_BUTT; i++)
    {
        pstCpuDrvAssemPara = &g_stCpuDriverAssePara.stCpuDrvAssemPara[i];

        (VOS_VOID)vos_printf("pstCpuDrvAssemPara->ulCpuLoad = %d\n", pstCpuDrvAssemPara->ulCpuLoad);
        (VOS_VOID)vos_printf("pstCpuDrvAssemPara->stDrvAssemPara.ucEthRxMinNum = %d\n", pstCpuDrvAssemPara->stDrvAssemPara.ucEthRxMinNum);
        (VOS_VOID)vos_printf("pstCpuDrvAssemPara->stDrvAssemPara.ucEthRxTimeout = %d\n", pstCpuDrvAssemPara->stDrvAssemPara.ucEthRxTimeout);
        (VOS_VOID)vos_printf("pstCpuDrvAssemPara->stDrvAssemPara.ucEthTxMinNum = %d\n", pstCpuDrvAssemPara->stDrvAssemPara.ucEthTxMinNum);
        (VOS_VOID)vos_printf("pstCpuDrvAssemPara->stDrvAssemPara.ucEthTxTimeout = %d\n", pstCpuDrvAssemPara->stDrvAssemPara.ucEthTxTimeout);
        (VOS_VOID)vos_printf("pstCpuDrvAssemPara->stDrvAssemPara.ucHostOutTimeout = %d\n", pstCpuDrvAssemPara->stDrvAssemPara.ucHostOutTimeout);
    }
}

/*****************************************************************************
 函 数 名  : FC_DrvAssemInit
 功能描述  : 驱动组包参数初始化，从NV项中读出值
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月14日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_DrvAssemInit(VOS_VOID)
{
    FC_CPU_DRV_ASSEM_PARA_NV_STRU   stCpuDrvAssemPara;
    VOS_UINT32                      ulRst;

    ulRst = NV_ReadEx(MODEM_ID_0, en_NV_Item_FC_ACPU_DRV_ASSEMBLE_PARA, &stCpuDrvAssemPara, sizeof(FC_CPU_DRV_ASSEM_PARA_NV_STRU));

    /* NV如果读取失败使用默认值 */
    if (NV_OK != ulRst)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_DrvAssemInit Read NV fail!\n");

        return;
    }

    g_stDrvAssemParaEntity.stCurAssemPara.ulCpuLoad = 100;
    g_stDrvAssemParaEntity.ulCurLev                 = FC_ACPU_DRV_ASSEM_LEV_1;
    g_stDrvAssemParaEntity.ucSetDrvFailCnt          = 0;

    /* NV的长度与结构体的长度定义不一样只拷NV的部分 */
    PS_MEM_CPY(&g_stCpuDriverAssePara, &stCpuDrvAssemPara, sizeof(FC_CPU_DRV_ASSEM_PARA_NV_STRU));
}

/*****************************************************************************
 函 数 名  : FC_JudgeAssemSmoothFactor
 功能描述  : 调整平滑系数
 输入参数  : FC_CPU_DRV_ASSEM_PARA_STRU pstDrvAssemPara 组包参数信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月14日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_JudgeAssemSmoothFactor(FC_CPU_DRV_ASSEM_PARA_STRU *pstDrvAssemPara)
{
    /* 平滑系数计算，连续多次超过才做出调整 */
    if (g_stDrvAssemParaEntity.stCurAssemPara.ulCpuLoad > pstDrvAssemPara->ulCpuLoad)
    {
        /* 下调档位平滑 */
        g_stDrvAssemParaEntity.ucSmoothCntDown++;
        g_stDrvAssemParaEntity.ucSmoothCntUp = 0;
    }
    else if (g_stDrvAssemParaEntity.stCurAssemPara.ulCpuLoad < pstDrvAssemPara->ulCpuLoad)
    {
        /* 上调档位平滑 */
        g_stDrvAssemParaEntity.ucSmoothCntUp++;
        g_stDrvAssemParaEntity.ucSmoothCntDown = 0;
    }
    else
    {
        /* 如果需要调整档已经与当前相同，平滑系数清零 */
        g_stDrvAssemParaEntity.ucSmoothCntUp    = 0;
        g_stDrvAssemParaEntity.ucSmoothCntDown  = 0;
    }
}


/*****************************************************************************
 函 数 名  : FC_GetCpuDrvAssemPara
 功能描述  : 根据当前档位获取参数
 输入参数  : VOS_UINT32 ulLev 档位值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月14日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
FC_CPU_DRV_ASSEM_PARA_STRU *FC_GetCpuDrvAssemPara(VOS_UINT32 ulLev)
{
    if (ulLev >= FC_ACPU_DRV_ASSEM_LEV_BUTT)
    {
        return VOS_NULL_PTR;
    }

    return &g_stCpuDriverAssePara.stCpuDrvAssemPara[ulLev];
}

/*****************************************************************************
 函 数 名  : FC_JudgeCdsDlThres
 功能描述  : 向CDS发送消息，内容为:CdsGuDlThres
 输入参数  : VOS_UINT8 ucThres
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月14日
    作    者   : t00148005
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 FC_JudgeCdsDlThres(VOS_UINT8 ucThres)
{
    FC_CDS_THRES_CHG_IND_STRU *pstFcCdsThresChgMsg = VOS_NULL_PTR;

    pstFcCdsThresChgMsg = (FC_CDS_THRES_CHG_IND_STRU *)PS_ALLOC_MSG_ALL_CHECK(UEPS_PID_FLOWCTRL, sizeof(FC_CDS_THRES_CHG_IND_STRU));

    if (VOS_NULL_PTR == pstFcCdsThresChgMsg)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_JudgeCdsDlThres, Send Msg Fail\n");

        return VOS_ERR;
    }

    pstFcCdsThresChgMsg->enMsgName  = ID_FC_CDS_DL_THRES_CHG_IND;
    pstFcCdsThresChgMsg->ucThres    = ucThres;
    pstFcCdsThresChgMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstFcCdsThresChgMsg->ulReceiverPid   = UEPS_PID_CDS;

    if (VOS_OK != PS_SEND_MSG(UEPS_PID_FLOWCTRL, pstFcCdsThresChgMsg))
    {
        FC_LOG(PS_PRINT_ERROR, "FC_JudgeCdsDlThres, Send Msg Fail\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_GetCurrentAssemPara
 功能描述  : 获取当前ASSEM参数
 输入参数  : VOS_UINT32 ulAssemLev 根据当前CPU选出的档位值
 输出参数  : pstDrvAssemPara
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月14日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
FC_CPU_DRV_ASSEM_PARA_STRU* FC_GetCurrentAssemPara(VOS_UINT32 ulAssemLev)
{
    FC_CPU_DRV_ASSEM_PARA_STRU *pstDrvAssemPara = VOS_NULL_PTR;

    /* 向上调整一步调到位 */
    if (g_stDrvAssemParaEntity.ucSmoothCntUp >= g_stCpuDriverAssePara.ucSmoothCntUpLev)
    {
        g_stDrvAssemParaEntity.ulCurLev = ulAssemLev;
    }
    /* 向下调整一个档位一个档位调整 */
    else if (g_stDrvAssemParaEntity.ucSmoothCntDown >= g_stCpuDriverAssePara.ucSmoothCntDownLev)
    {
        if (g_stDrvAssemParaEntity.ulCurLev < (FC_ACPU_DRV_ASSEM_LEV_BUTT - 1))
        {
             g_stDrvAssemParaEntity.ulCurLev++;
        }
    }
    else
    {
        return VOS_NULL_PTR;
    }

    pstDrvAssemPara = FC_GetCpuDrvAssemPara(g_stDrvAssemParaEntity.ulCurLev);

    return pstDrvAssemPara;
}

/*****************************************************************************
 函 数 名  : FC_DoJudgeDrvAssem
 功能描述  : 对驱动进行调整操作
 输入参数  : FC_CPU_DRV_ASSEM_PARA_STRU *pstDrvAssemPara 选出档位参数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月14日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_DoJudgeDrvAssem(FC_CPU_DRV_ASSEM_PARA_STRU *pstDrvAssemPara)
{
#if 0
    if (FC_ACPU_CDS_GU_ASSEM_ON_MASK == (FC_ACPU_CDS_GU_ASSEM_ON_MASK & g_stCpuDriverAssePara.ucEnableMask))
    {
        FC_JudgeCdsDlThres(pstDrvAssemPara->stDrvAssemPara.ucCdsGuDlThres);
    }

    /* 使能开关打开 */
    if (FC_ACPU_DRV_ASSEM_UE_ON_MASK == (FC_ACPU_DRV_ASSEM_UE_ON_MASK & g_stCpuDriverAssePara.ucEnableMask))
    {
        if (VOS_NULL_PTR != g_stDrvAssemParaEntity.pDrvSetAssemParaFuncUe)
        {
            /* 调用回调函数调整驱动组包参数,这个地方是调整UE侧组包方案 */
            if (VOS_OK != g_stDrvAssemParaEntity.pDrvSetAssemParaFuncUe(&(pstDrvAssemPara->stDrvAssemPara)))
            {
                FC_LOG(PS_PRINT_ERROR, "Set Driver Assemble parameter fail!\n");
                /* 设置失败计数 */
                g_stDrvAssemParaEntity.ucSetDrvFailCnt++;

                return;
            }
        }
    }
#endif

    /* 使能开关打开 */
    if (FC_ACPU_DRV_ASSEM_PC_ON_MASK == (FC_ACPU_DRV_ASSEM_PC_ON_MASK & g_stCpuDriverAssePara.ucEnableMask))
    {
        if (VOS_NULL_PTR != g_stDrvAssemParaEntity.pDrvSetAssemParaFuncPc)
        {
            /* 调用回调函数调整驱动组包参数，这里调整PC侧组包方案 */
            if (VOS_OK != g_stDrvAssemParaEntity.pDrvSetAssemParaFuncPc(&(pstDrvAssemPara->stDrvAssemPara)))
            {
                FC_LOG(PS_PRINT_ERROR, "Set Driver Assemble parameter fail!\n");
                /* 设置失败计数 */
                g_stDrvAssemParaEntity.ucSetDrvFailCnt++;

                return;
            }
        }
    }

    /* 组包系数清零 */
    g_stDrvAssemParaEntity.ucSmoothCntUp    = 0;
    g_stDrvAssemParaEntity.ucSmoothCntDown  = 0;

    /* 设置失败次数清零 */
    g_stDrvAssemParaEntity.ucSetDrvFailCnt  = 0;

    /* 保存当前档位信息 */
    PS_MEM_CPY(&g_stDrvAssemParaEntity.stCurAssemPara, pstDrvAssemPara, sizeof(FC_CPU_DRV_ASSEM_PARA_STRU));

    /* 可维可测 */
    FC_MNTN_TraceDrvAssemPara(&(pstDrvAssemPara->stDrvAssemPara));

}

/*****************************************************************************
 函 数 名  : FC_JudgeDrvAssemAction
 功能描述  : 对驱动进行调整
 输入参数  : VOS_UINT32 ulAssemLev 根据当前CPU选出的档位值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月14日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_JudgeDrvAssemAction(VOS_UINT32 ulAssemLev)
{

    FC_CPU_DRV_ASSEM_PARA_STRU *pstDrvAssemPara = VOS_NULL_PTR;

    pstDrvAssemPara = FC_GetCurrentAssemPara(ulAssemLev);

    /* 超过平滑系数的水线之后再做出调整 */
    if ( VOS_NULL_PTR != pstDrvAssemPara)
    {
        FC_DoJudgeDrvAssem(pstDrvAssemPara);
    }
}

/*****************************************************************************
 函 数 名  : FC_JudgeDrvToMaxPara
 功能描述  : 将驱动调整到最大档位
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月14日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_JudgeDrvToMaxPara(VOS_VOID)
{
    FC_CPU_DRV_ASSEM_PARA_STRU *pstDrvAssemPara = VOS_NULL_PTR;

    /* 直接调整到最大档位 */
    g_stDrvAssemParaEntity.ulCurLev = FC_ACPU_DRV_ASSEM_LEV_1;

    pstDrvAssemPara =  FC_GetCpuDrvAssemPara(FC_ACPU_DRV_ASSEM_LEV_1);

    FC_DoJudgeDrvAssem(pstDrvAssemPara);
}

/*****************************************************************************
 函 数 名  : FC_SelectDrvAssemParaRule
 功能描述  : 通过CPU LOAD的情况选择参数档位
 输入参数  : VOS_UINT32 ulCpuLoad 当前CPU LOAD情况
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月14日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
FC_CPU_DRV_ASSEM_PARA_STRU* FC_SelectDrvAssemParaRule(VOS_UINT32 ulCpuLoad, VOS_UINT32 *pulAssemLev)
{
    FC_CPU_DRV_ASSEM_PARA_STRU      *pstCpuDrvAssemParaRst  = VOS_NULL_PTR;
    FC_CPU_DRV_ASSEM_PARA_STRU      *pstCpuDrvAssemPara     = VOS_NULL_PTR;
    VOS_INT                          i                      = 0;

    /* 选出当前需要调整档位 */
    for (i = 0; i < FC_ACPU_DRV_ASSEM_LEV_BUTT; i++)
    {
        pstCpuDrvAssemPara = &g_stCpuDriverAssePara.stCpuDrvAssemPara[i];
        if (ulCpuLoad >= pstCpuDrvAssemPara->ulCpuLoad)
        {
            pstCpuDrvAssemParaRst   = pstCpuDrvAssemPara;
           *pulAssemLev             = (VOS_UINT32)i;

            break;
        }
    }

    return pstCpuDrvAssemParaRst;
}


/*****************************************************************************
 函 数 名  : FC_JudgeDrvAssemPara
 功能描述  : 通过CPU LOAD的情况调整驱动组包参数数
 输入参数  : VOS_UINT32 ulCpuLoad 当前CPU LOAD情况
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月14日
    作    者   : t00148005
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_JudgeDrvAssemPara(VOS_UINT32 ulCpuLoad)
{
    FC_CPU_DRV_ASSEM_PARA_STRU *pstDrvAssemPara  = VOS_NULL_PTR;
    /* 默认最高档 */
    VOS_UINT32                  ulAssemLev       = FC_ACPU_DRV_ASSEM_LEV_1;

    /* 使能开关未打开时，不再继续下面步骤 */
    if (0 == g_stCpuDriverAssePara.ucEnableMask)
    {
        return;
    }

    if (0 != (g_stDrvAssemParaEntity.ucSetDrvFailCnt % CPU_MAX_SET_DRV_FAIL_SMOOTH_CNT))
    {
        g_stDrvAssemParaEntity.ucSetDrvFailCnt++;

        return;
    }

    /* 根据CPU负载情况选择对应档位 */
    pstDrvAssemPara = FC_SelectDrvAssemParaRule(ulCpuLoad, &ulAssemLev);

    if (VOS_NULL_PTR == pstDrvAssemPara)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_JudgeDrvAssemPara pstDrvAssemPara is NULL!\n");

        return;
    }

    /* 根据当前档位计算平滑因子 */
    FC_JudgeAssemSmoothFactor(pstDrvAssemPara);

    /* 对驱动做出调整 */
    FC_JudgeDrvAssemAction(ulAssemLev);
}

/*****************************************************************************
 函 数 名  : FC_UmRateOverThreshold
 功能描述  : 空口速率是否达到引发CPU流控的门限
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:达到门限，VOS_FALSE:没有达到门限
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_UmRateOverThreshold( VOS_VOID )
{
    VOS_UINT32                          ulUlRate;
    VOS_UINT32                          ulDlRate;


    /* 获取UM口速率 */
    ADS_GetCurrentRate(&ulUlRate, &ulDlRate);


    /* 如果上行或下行速率超过门限，则认为是速率高引起CPU高 */
    if ( (ulUlRate > g_stFcCfg.stFcCfgCpuA.ulUmUlRateThreshold)
        || (ulDlRate > g_stFcCfg.stFcCfgCpuA.ulUmDlRateThreshold) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : FC_PsRateJudge
 功能描述  : 判断是否有数传
 输入参数  : 无
 输出参数  : 速率超标VOS_TRUE，不超标VOS_FALSE
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_PsRateJudge( VOS_VOID )
{
    /*
    STICK形态判断空口速率
    E5形态判断网桥速率
    */
#if(FEATURE_ON == FEATURE_NFEXT)
    return (FC_RmRateJudge());
#else
    return (FC_UmRateOverThreshold());
#endif
}


/*****************************************************************************
 函 数 名  : FC_GetPsRate
 功能描述  : 获取数传速率
 输入参数  : None
 输出参数  : pulUlRate -- 上行速率输出指针，bps
              pulDlRate -- 下行速率输出指针，bps
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_GetPsRate( VOS_UINT32 *pulUlRate, VOS_UINT32 *pulDlRate )
{
    /* E5形态下，获取网桥速率 */
#if(FEATURE_ON == FEATURE_NFEXT)
   /* 网桥上，上下行速率都赋值成网桥速率 */
   *pulUlRate   = FC_BRIDGE_GetRate();
   *pulDlRate   = *pulUlRate;
#else
    /* STICK形态下，获取网桥速率 */
    ADS_GetCurrentRate(pulUlRate, pulDlRate);
#endif
}


/*****************************************************************************
 函 数 名  : FC_CPUA_UpJudge
 功能描述  : 是否触发CPU流控，第一次会做平滑处理
 输入参数  : ulCpuLoad   -- 当前CPU空闲量0~100
              pstFcCfgCpu -- CPU流控配置项
              pstFcPolicy -- CPU流控策略实体
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要进行流控，VOS_FALSE:不需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_CPUA_UpJudge
(
    VOS_UINT32       ulCpuLoad,
    FC_CFG_CPU_STRU *pstFcCfgCpu,
    FC_POLICY_STRU  *pstFcPolicy
)
{
    VOS_UINT32                          ulResult;


    if ( ulCpuLoad < pstFcCfgCpu->ulCpuOverLoadVal )
    {
        g_stFcCpuACtrl.ulSmoothTimerLen = 0;
        return VOS_FALSE;
    }

    /* 已经达到CPU流控的最高级别，不用再进一步流控 */
    if (pstFcPolicy->enHighestPri <= pstFcPolicy->enDonePri)
    {
        return VOS_FALSE;
    }


    /* 是否进行平滑和速率判断  */
    /* 如果已经开始进行CPU流控，则继续进行流控，不再进行平滑和速率的判断 */
    if ( FC_PRI_NULL != pstFcPolicy->enDonePri )
    {
        return VOS_TRUE;
    }

    if ( 0 == g_stFcCpuACtrl.ulSmoothTimerLen )
    {
        FC_BRIDGE_ResetRate();
    }

    g_stFcCpuACtrl.ulSmoothTimerLen++;

    if (g_stFcCpuACtrl.ulSmoothTimerLen < pstFcCfgCpu->ulSmoothTimerLen)
    {
        return VOS_FALSE;
    }

#if(FEATURE_ON == FEATURE_ACPU_STAT)
    /* A核ulSmoothTimerLen >= 2，详见FC_CFG_CheckParam函数内注释 */
    FC_BRIDGE_CalcRate((pstFcCfgCpu->ulSmoothTimerLen - 1) * CPULOAD_GetRegularTimerLen());
#endif

    g_stFcCpuACtrl.ulSmoothTimerLen  = 0;


    /* 数传速率是否是CPU高的原因 */
    ulResult    = FC_PsRateJudge();
    if (VOS_FALSE == ulResult)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : FC_CPUA_DownJudge
 功能描述  : 是否触发CPU解除流控
 输入参数  : ulCpuLoad   -- 当前CPU空闲量0~100
              pstFcCfgCpu -- CPU流控配置项
              pstFcPolicy -- CPU流控策略实体
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要解除流控，VOS_FALSE:不需要
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_CPUA_DownJudge
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
 函 数 名  : FC_RcvCpuLoad
 功能描述  : A核流控模块提供的CPU负载处理接口
 输入参数  : ulCpuLoad  --  当前CPU负载0~100
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_CPUA_RcvCpuLoad(VOS_UINT32  ulCpuLoad)
{
    FC_CFG_CPU_STRU                    *pstFcCfgCpu;
    FC_POLICY_STRU                     *pstFcPolicy;
    VOS_UINT32                          ulStartCtrl;
    VOS_UINT32                          ulUlRate;
    VOS_UINT32                          ulDlRate;


    /* 通过CPU LOAD调整驱动组包参数，不受CPU流控开关控制 */
    FC_JudgeDrvAssemPara(ulCpuLoad);


    /* 参数检查 */
    if ( FC_POLICY_MASK_CPU_A != (FC_POLICY_MASK_CPU_A & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* CPU流控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_CPU_ProcessLoad, INFO, CPU FlowCtrl is disabled %d\n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return;
    }

    /* 输出可维可测 */
    FC_MNTN_TraceCpuLoad(ID_FC_MNTN_CPU_A_CPULOAD, ulCpuLoad);

    if ( 100 < ulCpuLoad )
    {
        /* 参数非法 */
        FC_LOG1(PS_PRINT_WARNING, "FC_CPU_ProcessLoad, WARNING, Invalid Cpu Load %d\n",
                (VOS_INT32)ulCpuLoad);
        return;
    }


    pstFcCfgCpu = &(g_stFcCfg.stFcCfgCpuA);
    pstFcPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CPU_A_MODEM_0);

    /* 是否要进行CPU流控 */
    ulStartCtrl = FC_CPUA_UpJudge(ulCpuLoad, pstFcCfgCpu, pstFcPolicy);
    if (VOS_TRUE == ulStartCtrl)
    {
        FC_GetPsRate(&ulUlRate, &ulDlRate);
        FC_SndCpuMsg(ID_FC_CPU_A_OVERLOAD_IND, ulCpuLoad, ulUlRate, ulDlRate);
        return;
    }


    /* 进行CPU解流控判决 */
    ulStartCtrl = FC_CPUA_DownJudge(ulCpuLoad, pstFcCfgCpu, pstFcPolicy);
    if ( VOS_TRUE ==  ulStartCtrl )
    {
        FC_GetPsRate(&ulUlRate, &ulDlRate);
        FC_SndCpuMsg(ID_FC_CPU_A_UNDERLOAD_IND, ulCpuLoad, ulUlRate, ulDlRate);
        return;
    }

    return;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_CpuStopFcAttempt
 功能描述  : 尝试解除CPU流控
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CPUA_StopFcAttempt( VOS_UINT32 ulParam1, VOS_UINT32 ulParam2 )
{
    FC_CFG_CPU_STRU                     *pstCfgCpu;


    pstCfgCpu   = &(g_stFcCfg.stFcCfgCpuA);
    if (0 == pstCfgCpu->ulStopAttemptTimerLen)
    {
        return VOS_OK;
    }

#if(FEATURE_ON == FEATURE_ACPU_STAT)
    CPULOAD_ResetUserDefLoad();
#endif

    /*如果定时器已经开启，则不需要再次启动*/
    if (VOS_NULL_PTR == g_stFcCpuACtrl.pstStopAttemptTHandle)
    {
        if ( VOS_OK != VOS_StartRelTimer(&g_stFcCpuACtrl.pstStopAttemptTHandle,
                                            UEPS_PID_FLOWCTRL,
                                            pstCfgCpu->ulStopAttemptTimerLen,
                                            FC_TIMER_STOP_CPU_ATTEMPT,
                                            0,
                                            VOS_RELTIMER_NOLOOP,
                                            VOS_TIMER_PRECISION_0))
        {
            FC_LOG(PS_PRINT_WARNING, "FC_CPUA_StopFcAttempt, VOS_StartRelTimer Fail!\n");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CPUA_UpProcess
 功能描述  : ACPU负载的流控处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功VOS_OK,失败VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CPUA_UpProcess( VOS_VOID )
{
    FC_POLICY_STRU                     *pFcPolicy;


    /* 获取CPU流控策略实体，并调用通用流控策略 */
    pFcPolicy   = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CPU_A_MODEM_0);
    FC_POLICY_Up(pFcPolicy);


    /* 已经是当前策略的最高级别了，执行回调函数 */
    if (pFcPolicy->enDonePri == pFcPolicy->enHighestPri)
    {
        if (VOS_NULL_PTR != pFcPolicy->pPostFunc)
        {
            (VOS_VOID)pFcPolicy->pPostFunc(FC_POLICY_ID_CPU_A, 0);
        }
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CPUA_DownProcess
 功能描述  : ACPU负载的解除流控处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功VOS_OK,失败VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CPUA_DownProcess( VOS_VOID )
{
    FC_POLICY_STRU                      *pPolicy;


    /* 获取CPU流控策略实体，并调用通用流控策略 */
    pPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CPU_A_MODEM_0);
    FC_POLICY_Down(pPolicy);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CPUA_StopFlowCtrl
 功能描述  : 根据CPU负载，判读是否可以提前解除CPU流控
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功VOS_OK,失败VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CPUA_StopFlowCtrl( VOS_VOID )
{
    FC_CFG_CPU_STRU                    *pstFcCfgCpu;
    FC_POLICY_STRU                     *pstFcPolicy;
    VOS_UINT32                          ulCpuLoad = 0;

    pstFcCfgCpu = &(g_stFcCfg.stFcCfgCpuA);
    pstFcPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CPU_A_MODEM_0);

#if (FEATURE_ON == FEATURE_ACPU_STAT)
    ulCpuLoad   = CPULOAD_GetUserDefLoad();
#endif

    /* 当前CPU小于解流控门限值,解流控 */
    if ( (ulCpuLoad <= pstFcCfgCpu->ulCpuUnderLoadVal)
         && (FC_PRI_NULL < pstFcPolicy->enDonePri) )
    {
        FC_CPUA_DownProcess();
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CPUA_Init
 功能描述  : ACPU负载流控的初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月22日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CPUA_Init( VOS_VOID )
{
    /* 增加使用宏开关判断是否注册回调函数 */
#if(FEATURE_ON == FEATURE_ACPU_STAT)
    /* 向CPU监测模块注册回调函数 */
    if ( VOS_OK != CPULOAD_RegRptHook((CPULOAD_RPT_HOOK_FUNC)FC_CPUA_RcvCpuLoad) )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_CPUA_Init, ERROR, CPULOAD_RegRptHook return error!\n");
        return VOS_ERR;
    }

    /* A核CPU流控策略初始化 */
    g_astFcPolicy[FC_POLICY_ID_CPU_A].pPostFunc   = FC_CPUA_StopFcAttempt;
#endif

    VOS_MemSet(&g_stFcBridgeRate, 0, sizeof(FC_BRIDGE_RATE_STRU));
    VOS_MemSet(&g_stFcCpuACtrl, 0, sizeof(g_stFcCpuACtrl));

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_CalcUpTargetFcPris
 功能描述  : 内存递增时，根据内存占用量，计算出内存流控的目标流控级别，
              内存策略只有一个优先级时，按照Lev3处理
 输入参数  : pPolicy    -- 内存流控策略
              ulMemValue -- 当前内存占用量
 输出参数  : 无
 返 回 值  : 目标流控级别
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
FC_PRI_ENUM_UINT8  FC_MEM_CalcUpTargetFcPri
(
    FC_POLICY_STRU                     *pPolicy,
    VOS_UINT32                          ulMemValue
)
{
    FC_PRI_ENUM_UINT8                  enTargetPri;
    FC_CFG_MEM_STRU                    *pstMemCfg;


    pstMemCfg   = &(g_stFcCfg.stFcCfgMem);
    enTargetPri = pPolicy->enDonePri;

    /* 内存策略只注册了一个优先级，按照Lev3处理 */
    if (1 == pPolicy->ucPriCnt)
    {
        /* 计算出目标流控优先级 */
        if (ulMemValue <= pstMemCfg->astThreshold[FC_MEM_THRESHOLD_LEV_3].ulSetThreshold)
        {
            enTargetPri     = pPolicy->enHighestPri;
        }
    }
    /* 内存策略只注册了多个优先级 */
    else
    {
        /* 计算出目标流控优先级 */
        if (ulMemValue <= pstMemCfg->astThreshold[FC_MEM_THRESHOLD_LEV_4].ulSetThreshold)
        {
            enTargetPri     = FC_PRI_FOR_MEM_LEV_4;
        }
        else if (ulMemValue <= pstMemCfg->astThreshold[FC_MEM_THRESHOLD_LEV_3].ulSetThreshold)
        {
            enTargetPri     = FC_PRI_FOR_MEM_LEV_3;
        }
        else if (ulMemValue <= pstMemCfg->astThreshold[FC_MEM_THRESHOLD_LEV_2].ulSetThreshold)
        {
            enTargetPri     = FC_PRI_FOR_MEM_LEV_2;
        }
        else if (ulMemValue <= pstMemCfg->astThreshold[FC_MEM_THRESHOLD_LEV_1].ulSetThreshold)
        {
            enTargetPri     = FC_PRI_FOR_MEM_LEV_1;
        }
        else
        {
            ;
        }
    }

    return enTargetPri;
} /* FC_MEM_CalcUpTargetFcPri */


/*****************************************************************************
 函 数 名  : FC_MEM_CalcDownTargetFcPri
 功能描述  : 内存递减时，根据内存占用量，计算出内存流控的目标解流控级别，
              内存策略只有一个优先级时，按照Lev3处理
 输入参数  : pPolicy    -- 内存流控策略
              ulMemValue -- 当前内存占用量
 输出参数  : 无
 返 回 值  : 目标解流控级别
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月9日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
FC_PRI_ENUM_UINT8  FC_MEM_CalcDownTargetFcPri
(
    FC_POLICY_STRU                     *pPolicy,
    VOS_UINT32                          ulMemValue
)
{
    FC_PRI_ENUM_UINT8                  enTargetPri;
    FC_CFG_MEM_STRU                    *pstMemCfg;

    pstMemCfg   = &(g_stFcCfg.stFcCfgMem);
    enTargetPri = pPolicy->enDonePri;

    /* 内存策略只注册了一个优先级 */
    if (1 == pPolicy->ucPriCnt)
    {
        /* 计算出目标流控优先级 */
        if (ulMemValue > pstMemCfg->astThreshold[FC_MEM_THRESHOLD_LEV_3].ulStopThreshold)
        {
            enTargetPri     = FC_PRI_NULL;
        }
    }
    /* 内存策略只注册了多个优先级 */
    else
    {
        /* 计算出目标流控优先级 */
        if (ulMemValue > pstMemCfg->astThreshold[FC_MEM_THRESHOLD_LEV_1].ulStopThreshold)
        {
            enTargetPri     = FC_PRI_NULL;
        }
        else if (ulMemValue > pstMemCfg->astThreshold[FC_MEM_THRESHOLD_LEV_2].ulStopThreshold)
        {
            enTargetPri     = FC_PRI_FOR_MEM_LEV_1;
        }
        else if (ulMemValue > pstMemCfg->astThreshold[FC_MEM_THRESHOLD_LEV_3].ulStopThreshold)
        {
            enTargetPri     = FC_PRI_FOR_MEM_LEV_2;
        }
        else if (ulMemValue > pstMemCfg->astThreshold[FC_MEM_THRESHOLD_LEV_4].ulStopThreshold)
        {
            enTargetPri     = FC_PRI_FOR_MEM_LEV_3;
        }
        else
        {
            ;
        }
    }

    return enTargetPri;
} /* FC_MEM_CalcUpTargetFcPri */


/*****************************************************************************
 函 数 名  : FC_MEM_AdjustPriForUp
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月14日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_MEM_AdjustPriForUp
(
    FC_PRI_ENUM_UINT8                  enPointPri,
    FC_ID_ENUM_UINT8                   enFcId
)
{
    FC_POLICY_STRU                     *pPolicy;
    FC_PRI_ENUM_UINT8                   enTargetPri;

    /* 获取内存流控策略和内存流控配置 */
    pPolicy         = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_MEM_MODEM_0);

    /* 根据内存情况，重新刷新内存流控目标优先级 */
    enTargetPri     = FC_MEM_CalcUpTargetFcPri(pPolicy, 0);

    /* 目标优先级调整后，进行流控处理调整，符合新的流控优先级 */
    if (pPolicy->enDonePri < enTargetPri)
    {
        FC_POLICY_UpToTargetPri(pPolicy, enTargetPri);
    }
    else if (pPolicy->enDonePri > enTargetPri)
    {
        FC_POLICY_DownToTargetPri(pPolicy, enTargetPri);
    }
    else
    {
        ;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_POLICY_AdjustMemPri
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月14日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_MEM_AdjustPriForDown
(
    FC_PRI_ENUM_UINT8                   enPointPri,
    FC_ID_ENUM_UINT8                    enFcId
)
{
    FC_POLICY_STRU                     *pPolicy;
    FC_PRI_ENUM_UINT8                   enTargetPri;

    /* 获取内存流控策略和内存流控配置 */
    pPolicy         = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_MEM_MODEM_0);

    /* 根据内存情况，重新刷新内存流控目标优先级 */
    enTargetPri     = FC_MEM_CalcDownTargetFcPri(pPolicy, 0);

    /* 目标优先级调整后，进行流控处理调整，符合新的流控优先级 */
    if (pPolicy->enDonePri < enTargetPri)
    {
        FC_POLICY_UpToTargetPri(pPolicy, enTargetPri);
    }
    else if (pPolicy->enDonePri > enTargetPri)
    {
        FC_POLICY_DownToTargetPri(pPolicy, enTargetPri);
    }
    else
    {
        ;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_SndMemUpToTargetPriIndMsg
 功能描述  : 发送内存流控到目标值的消息通知
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_MEM_SndUpToTargetPriIndMsg(FC_PRI_ENUM_UINT8 enTargetPri, VOS_UINT16 usMemFreeCnt)
{
    FC_MEM_UP_TO_TARGET_PRI_IND_STRU   *pstMsg;
    VOS_UINT32                          ulResult;


    pstMsg = (FC_MEM_UP_TO_TARGET_PRI_IND_STRU *)VOS_AllocMsg(UEPS_PID_FLOWCTRL, \
                                         sizeof(FC_MEM_UP_TO_TARGET_PRI_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_SndMemUpToTargetPriIndMsg, Alloc Msg Fail\n");
        return VOS_ERR;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL;
    pstMsg->usMsgName       = ID_FC_MEM_UP_TO_TARGET_PRI_IND;
    pstMsg->enTargetPri     = enTargetPri;
    pstMsg->usMemFreeCnt    = usMemFreeCnt;

    ulResult = VOS_SendMsg(UEPS_PID_FLOWCTRL, pstMsg);

    if (VOS_OK != ulResult)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_SndMemUpToTargetPriIndMsg, Send Msg Fail\n");
        return VOS_ERR;
    }

    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : FC_SndMemDownToTargetPriIndMsg
 功能描述  : 发送内存流控到目标值的消息通知
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_MEM_SndDownToTargetPriIndMsg( FC_PRI_ENUM_UINT8 enTargetPri, VOS_UINT16 usMemFreeCnt)
{
    FC_MEM_DOWN_TO_TARGET_PRI_IND_STRU *pstMsg;
    VOS_UINT32                          ulResult;


    pstMsg = (FC_MEM_DOWN_TO_TARGET_PRI_IND_STRU *)VOS_AllocMsg(UEPS_PID_FLOWCTRL, \
                                         sizeof(FC_MEM_DOWN_TO_TARGET_PRI_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_SndMemDownToTargetPriIndMsg, Alloc Msg Fail\n");
        return VOS_ERR;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL;
    pstMsg->usMsgName       = ID_FC_MEM_DOWN_TO_TARGET_PRI_IND;
    pstMsg->enTargetPri     = enTargetPri;
    pstMsg->usMemFreeCnt    = usMemFreeCnt;

    ulResult = VOS_SendMsg(UEPS_PID_FLOWCTRL, pstMsg);

    if (VOS_OK != ulResult)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_SndMemDownToTargetPriIndMsg, Send Msg Fail\n");
        return VOS_ERR;
    }

    return VOS_OK;

}


/*****************************************************************************
 函 数 名  : FC_MEM_UpProcess
 功能描述  : 内存流控策略入口函数
 输入参数  : ulMemValue:内存个数
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID FC_MEM_UpProcess( VOS_UINT32 ulMemValue  )
{
    FC_POLICY_STRU                     *pPolicy;
    FC_PRI_ENUM_UINT8                  enTargetPri;
    VOS_ULONG                           ulFlags = 0UL;

    /* 参数检查 */
    if ( FC_POLICY_MASK_MEM != (FC_POLICY_MASK_MEM & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 内存流控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_MEM_UpProcess, INFO, MEM FlowCtrl is disabled %d \n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return;
    }

    pPolicy         = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_MEM_MODEM_0);
    enTargetPri     = FC_MEM_CalcUpTargetFcPri(pPolicy, ulMemValue);

    if ((pPolicy->enDonePri < enTargetPri) && (pPolicy->enToPri < enTargetPri))
    {
        /* 如果在软中断这类不可打断的任务中，就不发流控消息 */
        /*lint -e506 -e774*/
        if (likely(preemptible()))
        /*lint +e506 +e774*/
        {
            VOS_SpinLockIntLock(&g_stFcMemSpinLock, ulFlags);
            pPolicy->enToPri = enTargetPri;
            VOS_SpinUnlockIntUnlock(&g_stFcMemSpinLock , ulFlags);

            /* 消息发送失败会单板复位，不再进行enToPri的恢复 */
            FC_MEM_SndUpToTargetPriIndMsg(enTargetPri, (VOS_UINT16)ulMemValue);

        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : FC_MEM_DownProcess
 功能描述  : 内存使用量减少，可能触发解除流控
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
VOS_VOID  FC_MEM_DownProcess( VOS_UINT32 ulMemValue )
{
    FC_POLICY_STRU                     *pPolicy;
    FC_PRI_ENUM_UINT8                  enTargetPri;
    VOS_ULONG                           ulFlags = 0UL;

    /* 参数检查 */
    if ( FC_POLICY_MASK_MEM != (FC_POLICY_MASK_MEM & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 内存流控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_MEM_UpProcess, INFO, MEM FlowCtrl is disabled %d \n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return;
    }

    pPolicy         = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_MEM_MODEM_0);
    enTargetPri     = FC_MEM_CalcDownTargetFcPri(pPolicy, ulMemValue);

    if ((pPolicy->enDonePri > enTargetPri) && (pPolicy->enToPri > enTargetPri))
    {
        /* 如果在软中断这类不可打断的任务中，就不发流控消息 */
        /*lint -e506 -e774*/
        if (likely(preemptible()))
        /*lint +e506 +e774*/
        {
            VOS_SpinLockIntLock(&g_stFcMemSpinLock, ulFlags);
            pPolicy->enToPri = enTargetPri;
            VOS_SpinUnlockIntUnlock(&g_stFcMemSpinLock, ulFlags);

            /* 消息发送失败会单板复位，不再进行enToPri的恢复 */
            FC_MEM_SndDownToTargetPriIndMsg(enTargetPri, (VOS_UINT16)ulMemValue);
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : FC_MEM_Init
 功能描述  : 内存流控初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月27日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_MEM_Init( VOS_VOID )
{
    VOS_SpinLockInit(&g_stFcMemSpinLock);

    /* V9R1项目中判断ACPU内存流控使能则注册回调函数，否则不注册 */
    /* 注册内存回调函数 */
    if ( (FC_POLICY_MASK(FC_POLICY_ID_MEM) == (FC_POLICY_MASK(FC_POLICY_ID_MEM) & g_stFcCfg.ulFcEnbaleMask) ))
    {
        /* A核内存流控策略初始化 */
        g_astFcPolicy[FC_POLICY_ID_MEM].pAdjustForUpFunc    = FC_MEM_AdjustPriForUp;
        g_astFcPolicy[FC_POLICY_ID_MEM].pAdjustForDownFunc  = FC_MEM_AdjustPriForDown;
    }
    else
    {
         /* A核内存流控策略初始化 */
        g_astFcPolicy[FC_POLICY_ID_MEM].pAdjustForUpFunc    = VOS_NULL_PTR;
        g_astFcPolicy[FC_POLICY_ID_MEM].pAdjustForDownFunc  = VOS_NULL_PTR;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CST_UpProcess
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
VOS_UINT32  FC_CST_UpProcess( VOS_UINT8 ucRabId )
{
    FC_POLICY_STRU                     *pPolicy;


    /*====================================*//* 使能检查 */
    if ( FC_POLICY_MASK_CST != (FC_POLICY_MASK_CST & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 内存流控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_CST_UpProcess, INFO, MEM FlowCtrl is disabled %d \n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return VOS_OK;
    }


    /* 获取CPU流控策略实体，并调用通用流控策略 */
    pPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CST_MODEM_0);
    FC_POLICY_UpToTargetPri(pPolicy, pPolicy->enHighestPri);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CST_DownProcess
 功能描述  : CST解除流控策略
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
VOS_UINT32  FC_CST_DownProcess( VOS_UINT8 ucRabId )
{
    FC_POLICY_STRU                     *pPolicy;


    /*====================================*//* 使能检查 */
    if ( FC_POLICY_MASK_CST != (FC_POLICY_MASK_CST & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 内存流控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_CST_DownProcess, INFO, MEM FlowCtrl is disabled %d \n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return VOS_OK;
    }


    /* 获取CPU流控策略实体，并调用通用流控策略 */
    pPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CST_MODEM_0);
    FC_POLICY_DownToTargetPri(pPolicy, FC_PRI_NULL);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CDS_GetFcInfo
 功能描述  : 获取Fc流控实体
 输入参数  : VOS_UINT8 ucRabId  需要查找的对应FC信息的Rab Id
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
FC_RAB_MAPPING_INFO_STRU  *FC_CDS_GetFcInfo( VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId )
{
    FC_RAB_MAPPING_INFO_SET_STRU       *pstFcRabMappingInfoSet;
    FC_RAB_MAPPING_INFO_STRU           *pstFcRabMappingInfo;
    FC_ID_ENUM_UINT8                    enFcId;
    VOS_UINT32                          ulRabMask;


    pstFcRabMappingInfoSet  = &g_astFcRabMappingInfoSet[enModemId];
    ulRabMask               = (VOS_UINT32)(1UL << ucRabId);

    /*====================================*//* 遍历所有映射关系，如果找到包含指定RAB_ID的映射关系，则退出 */
    for (enFcId = 0; enFcId < pstFcRabMappingInfoSet->enFcIdCnt; enFcId++)
    {
        pstFcRabMappingInfo = &(pstFcRabMappingInfoSet->astFcRabMappingInfo[enFcId]);
        if ( 0 != (ulRabMask & pstFcRabMappingInfo->ulIncludeRabMask) )
        {
            return pstFcRabMappingInfo;
        }
    }

    return VOS_NULL_PTR;
}


/*****************************************************************************
 函 数 名  : FC_CDS_DelFcId
 功能描述  : 删除FC Id对应的FC信息
 输入参数  : FC_ID_ENUM_UINT8 enFcId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CDS_DelFcId( FC_ID_ENUM_UINT8 enFcId, MODEM_ID_ENUM_UINT16 enModemId )
{
    FC_RAB_MAPPING_INFO_SET_STRU       *pstFcRabMappingInfoSet;
    FC_RAB_MAPPING_INFO_STRU           *pstFcRabMappingInfo;
    FC_ID_ENUM_UINT8                    enFcIdNum;
    FC_ID_ENUM_UINT8                    enShiftFcId;

    pstFcRabMappingInfoSet    = &g_astFcRabMappingInfoSet[enModemId];

    for (enFcIdNum = 0; enFcIdNum < pstFcRabMappingInfoSet->enFcIdCnt; enFcIdNum++)
    {
        if (enFcId == pstFcRabMappingInfoSet->astFcRabMappingInfo[enFcIdNum].enFcId)
        {
            break;
        }
    }

    if (enFcIdNum >= pstFcRabMappingInfoSet->enFcIdCnt)
    {
        FC_LOG1(PS_PRINT_WARNING, "FC_CDS_DelFcId, can not find the Fc Id <1>!\n",
            (VOS_INT32)enFcId);
        return VOS_ERR;
    }

    /* 将后面的映射关系拷贝过来，保持数组连续性 */
    for (enShiftFcId = (FC_PRI_ENUM_UINT8)(enFcIdNum + 1); enShiftFcId < pstFcRabMappingInfoSet->enFcIdCnt; enShiftFcId++)
    {
        pstFcRabMappingInfo   = &(pstFcRabMappingInfoSet->astFcRabMappingInfo[enShiftFcId]);
        PS_MEM_CPY((pstFcRabMappingInfo - 1), pstFcRabMappingInfo, sizeof(FC_RAB_MAPPING_INFO_STRU));
    }

    /* 最后一个映射关系无法被拷贝覆盖，所以需要手动清除 */
    PS_MEM_SET(&(pstFcRabMappingInfoSet->astFcRabMappingInfo[enShiftFcId - 1]), 0, sizeof(FC_RAB_MAPPING_INFO_STRU));
    pstFcRabMappingInfoSet->enFcIdCnt--;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CDS_AddRab
 功能描述  : 增加ClentId到RAB映射
 输入参数  : FC_ID_ENUM_UINT8 enFcId   对应业务所在设备的Fc Id
             VOS_UINT8 ucRabId          对应业务的RabId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CDS_AddRab(FC_ID_ENUM_UINT8 enFcId, VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId )
{
    FC_RAB_MAPPING_INFO_SET_STRU       *pstFcRabMappingInfoSet;
    FC_RAB_MAPPING_INFO_STRU           *pstFcRabMappingInfo;
    FC_ID_ENUM_UINT8                    enFcIdNum;
    VOS_UINT32                          ulRabMask;

    pstFcRabMappingInfoSet  = &g_astFcRabMappingInfoSet[enModemId];
    ulRabMask               = (VOS_UINT32)(1UL << ucRabId);

    if ( FC_MAX_NUM < pstFcRabMappingInfoSet->enFcIdCnt )
    {
        FC_LOG1(PS_PRINT_ERROR, "FC_CDS_AddRab, g_astFcRabMappingInfoSet is exceed the ranger!\n",
            (VOS_INT32)pstFcRabMappingInfoSet->enFcIdCnt);
        return VOS_ERR;
    }

    /*====================================*//* 遍历该FC的流控信息，如果找到包含指定RAB_ID的Fc Id，则退出 */
    for (enFcIdNum = 0; enFcIdNum < pstFcRabMappingInfoSet->enFcIdCnt; enFcIdNum++)
    {
        pstFcRabMappingInfo = &(pstFcRabMappingInfoSet->astFcRabMappingInfo[enFcIdNum]);
        if ( enFcId == pstFcRabMappingInfo->enFcId )
        {
            if ( 0 == (pstFcRabMappingInfo->ulIncludeRabMask & ulRabMask) )
            {
                pstFcRabMappingInfo->ulIncludeRabMask   |= ulRabMask;
                pstFcRabMappingInfo->ulNoFcRabMask      |= ulRabMask;
                (VOS_VOID)FC_POINT_ClrFc(FC_POLICY_MASK_CDS, enFcId);
            }

            return VOS_OK;
        }
    }

    if ( FC_MAX_NUM == pstFcRabMappingInfoSet->enFcIdCnt )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_CDS_AddRab, AtClientCnt reaches the max num!\n");
        return VOS_ERR;
    }

    /*====================================*//* 如果是新的FC Id，则添加该Fc Id和RAB ID */
    pstFcRabMappingInfo = &(pstFcRabMappingInfoSet->astFcRabMappingInfo[pstFcRabMappingInfoSet->enFcIdCnt]);
    pstFcRabMappingInfo->enFcId             = enFcId;
    pstFcRabMappingInfo->ulIncludeRabMask   = ulRabMask;
    pstFcRabMappingInfo->ulNoFcRabMask      = ulRabMask;

    pstFcRabMappingInfoSet->enFcIdCnt++;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CDS_DelRab
 功能描述  : 清除该RAB ID对应的流控信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CDS_DelRab( VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId )
{
    FC_RAB_MAPPING_INFO_STRU           *pstFcRabMappingInfo;
    VOS_UINT32                          ulRabMask;


    /*====================================*//* 通过Rab Id来查找该Rab Id所在的FC实体 */
    pstFcRabMappingInfo                 = FC_CDS_GetFcInfo(ucRabId, enModemId);
    if (VOS_NULL_PTR == pstFcRabMappingInfo)
    {
        return VOS_ERR;
    }

    /* 清除该RabId的信息，如果该Fc上已经不存在不需要流控的RabId，则进行流控 */
    ulRabMask       = (VOS_UINT32)(1UL << ucRabId);

    pstFcRabMappingInfo->ulIncludeRabMask  &= (~ulRabMask);

    if (0 != pstFcRabMappingInfo->ulNoFcRabMask)
    {
        pstFcRabMappingInfo->ulNoFcRabMask       &= (~ulRabMask);
        if ((0 == pstFcRabMappingInfo->ulNoFcRabMask) && (0 != pstFcRabMappingInfo->ulIncludeRabMask))
        {
            (VOS_VOID)FC_POINT_SetFc(FC_POLICY_MASK_CDS, pstFcRabMappingInfo->enFcId);
        }
    }

    /* 如果删除了RabId后，该FC上没有其它信息，则删除该FC ID对应的信息 */
    if (0 == pstFcRabMappingInfo->ulIncludeRabMask)
    {
        FC_CDS_DelFcId(pstFcRabMappingInfo->enFcId, enModemId);
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CDS_Init
 功能描述  : AT Client流控初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CDS_Init( VOS_VOID )
{
    VOS_MemSet(g_astFcRabMappingInfoSet, 0, sizeof(g_astFcRabMappingInfoSet));

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CDS_UpProcess
 功能描述  : CDS流控策略
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
VOS_UINT32  FC_CDS_UpProcess( VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId )
{
    FC_RAB_MAPPING_INFO_STRU               *pstFcRabMappingInfo;


    /*====================================*//* 使能检查 */
    if ( FC_POLICY_MASK_CDS != (FC_POLICY_MASK_CDS & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 内存流控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_CST_UpProcess, INFO, MEM FlowCtrl is disabled %d \n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return VOS_OK;
    }

    if ( MODEM_ID_BUTT <= enModemId )
    {
        FC_LOG1(PS_PRINT_WARNING, "FC_CDS_UpProcess ModemId Is Invalid %d\n", enModemId);
        return VOS_ERR;
    }

    /*====================================*//* 通过RAB id来查找 Client流控实体 */
    pstFcRabMappingInfo         = FC_CDS_GetFcInfo(ucRabId, enModemId);
    if (VOS_NULL_PTR == pstFcRabMappingInfo)
    {
        return VOS_ERR;
    }


    /*====================================*//* 如果该Fc流控实体已经流控，则无需处理，直接返回 */
    if (0 == pstFcRabMappingInfo->ulNoFcRabMask)
    {
        return VOS_OK;
    }


    /*====================================*/
    /* 去除该FC对应的没有流控的RAB掩码，如果为0，表明所有RAB都要求流控，该FC进行流控 */
    pstFcRabMappingInfo->ulNoFcRabMask   &= (~((VOS_UINT32)1 << ucRabId));
    if (0 == pstFcRabMappingInfo->ulNoFcRabMask)
    {
        (VOS_VOID)FC_POINT_SetFc(FC_POLICY_MASK_CDS, pstFcRabMappingInfo->enFcId);
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_CDS_DownProcess
 功能描述  : CDS解除流控策略
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
VOS_UINT32  FC_CDS_DownProcess( VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId )
{
    FC_RAB_MAPPING_INFO_STRU                  *pstFcRabMappingInfo;


    /*====================================*//* 使能检查 */
    if ( FC_POLICY_MASK_CDS != (FC_POLICY_MASK_CDS & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 内存流控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_CDS_DownProcess, INFO, MEM FlowCtrl is disabled %d \n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return VOS_OK;
    }

    /* add by wangrong */
    if ( MODEM_ID_BUTT <= enModemId )
    {
        FC_LOG1(PS_PRINT_WARNING, "FC_CDS_DownProcess ModemId Is Invalid %d\n", enModemId);
        return VOS_ERR;
    }

    /*====================================*//* 通过RAB id来查找 FC实体 */
    pstFcRabMappingInfo                 = FC_CDS_GetFcInfo(ucRabId, enModemId);
    if (VOS_NULL_PTR == pstFcRabMappingInfo)
    {
        return VOS_ERR;
    }


    /*====================================*/
    /* 如果该FC实体已经解除流控，则无需处理，直接返回 */
    if (0 != pstFcRabMappingInfo->ulNoFcRabMask)
    {
        pstFcRabMappingInfo->ulNoFcRabMask   |= ((VOS_UINT32)1 << ucRabId);
        return VOS_OK;
    }


    /*====================================*/
    /* 增加v对应的没有流控的RAB掩码，如果为0，则该FC实体s需要进行解流控 */
    pstFcRabMappingInfo->ulNoFcRabMask   |= ((VOS_UINT32)1 << ucRabId);
    (VOS_VOID)FC_POINT_ClrFc(FC_POLICY_MASK_CDS, pstFcRabMappingInfo->enFcId);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_UpProcess
 功能描述  : 处理流控请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月11日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_UpProcess(VOS_RATMODE_ENUM_UINT32 enRateMode)
{

    switch (enRateMode)
    {
        case VOS_RATMODE_GSM:

            FC_GPRS_UpProcess();

            break;

        case VOS_RATMODE_1X:
        case VOS_RATMODE_HRPD:

            FC_CDMA_UpProcess();

            break;

        default:

            FC_LOG1(PS_PRINT_WARNING, "FC_UpProcess RateMode Is Invalid %d\n", enRateMode);

            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : FC_GPRS_UpProcess
 功能描述  : 处理GPRS流控请求
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
VOS_UINT32  FC_GPRS_UpProcess( VOS_VOID )
{
    FC_POLICY_STRU                      *pPolicy;


    /*====================================*//* 使能检查 */
    if ( FC_POLICY_MASK_GPRS != (FC_POLICY_MASK_GPRS & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 内存流控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_GPRS_UpProcess, INFO, MEM FlowCtrl is disabled %d \n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return VOS_OK;
    }


    /* 获取CPU流控策略实体，并调用通用流控策略 */
    pPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_GPRS_MODEM_0);
    FC_POLICY_UpToTargetPri(pPolicy, pPolicy->enHighestPri);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_CDMA_UpProcess
 功能描述  : 处理CDMA流控请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CDMA_UpProcess( VOS_VOID )
{
    FC_POLICY_STRU                      *pPolicy;


    /*====================================*//* 使能检查 */
    if ( FC_POLICY_MASK_CDMA != (FC_POLICY_MASK_CDMA & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 内存流控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_CDMA_UpProcess, INFO, MEM FlowCtrl is disabled %d \n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return VOS_OK;
    }


    /* 获取CPU流控策略实体，并调用通用流控策略 */
    pPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CDMA_MODEM_0);
    FC_POLICY_UpToTargetPri(pPolicy, pPolicy->enHighestPri);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_DownProcess
 功能描述  : 处理流控请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月11日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_DownProcess(VOS_RATMODE_ENUM_UINT32 enRateMode)
{

    switch (enRateMode)
    {
        case VOS_RATMODE_GSM:

            FC_GPRS_DownProcess();

            break;

        case VOS_RATMODE_1X:
        case VOS_RATMODE_HRPD:

            FC_CDMA_DownProcess();

            break;

        default:

            FC_LOG1(PS_PRINT_WARNING, "FC_DownProcess RateMode Is Invalid %d\n", enRateMode);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : FC_GPRS_DownProcess
 功能描述  : 处理GPRS解除流控请求
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
VOS_UINT32  FC_GPRS_DownProcess( VOS_VOID )
{
    FC_POLICY_STRU                      *pPolicy;


    /*====================================*//* 使能检查 */
    if ( FC_POLICY_MASK_GPRS != (FC_POLICY_MASK_GPRS & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 内存流控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_GPRS_UpProcess, INFO, MEM FlowCtrl is disabled %d \n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return VOS_OK;
    }

    /* 获取CPU流控策略实体，并调用通用流控策略 */
    pPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_GPRS_MODEM_0);
    FC_POLICY_DownToTargetPri(pPolicy, FC_PRI_NULL);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_CDMA_DownProcess
 功能描述  : 处理CDMA解除流控请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月11日
    作    者   : c00184031
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_CDMA_DownProcess( VOS_VOID )
{
    FC_POLICY_STRU                      *pPolicy;


    /*====================================*//* 使能检查 */
    if ( FC_POLICY_MASK_CDMA != (FC_POLICY_MASK_CDMA & g_stFcCfg.ulFcEnbaleMask) )
    {
        /* 内存流控未使能 */
        FC_LOG1(PS_PRINT_INFO, "FC_CDMA_UpProcess, INFO, MEM FlowCtrl is disabled %d \n",
                (VOS_INT32)g_stFcCfg.ulFcEnbaleMask);
        return VOS_OK;
    }

    /* 获取CPU流控策略实体，并调用通用流控策略 */
    pPolicy = FC_POLICY_Get(FC_PRIVATE_POLICY_ID_CDMA_MODEM_0);
    FC_POLICY_DownToTargetPri(pPolicy, FC_PRI_NULL);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_ChannelMapCreate
 功能描述  : A核流控模块提供接口给AT配置通道与RABID映射关系
 输入参数  : FC_ID_ENUM_UINT8 enFcId   通道对应的FC ID
             VOS_UINT8 ucRabId          流控对应的RabId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_ChannelMapCreate(FC_ID_ENUM_UINT8 enFcId, VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16  enModemId)
{
    FC_ADD_RAB_FCID_MAP_IND_STRU       *pstMsg;
    VOS_UINT32                          ulResult;


    /* 参数检查，RabId范围为[5,15] */
    if ( (FC_UE_MIN_RAB_ID > ucRabId) || (FC_UE_MAX_RAB_ID < ucRabId) )
    {
        FC_LOG1(PS_PRINT_WARNING, "FC_ChannelMapCreate RabId Is Invalid %d\n", ucRabId);
        return;
    }

    if ( MODEM_ID_BUTT <= enModemId )
    {
        FC_LOG1(PS_PRINT_WARNING, "FC_ChannelMapCreate ModemId Is Invalid %d\n", enModemId);
        return;
    }

    /* 发送消息 */
    pstMsg = (FC_ADD_RAB_FCID_MAP_IND_STRU *)VOS_AllocMsg(UEPS_PID_FLOWCTRL_A, \
                                    sizeof(FC_ADD_RAB_FCID_MAP_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        FC_LOG(PS_PRINT_ERROR,"FC_ChannelMapCreate, Alloc Msg Fail\n");
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL_A;
    pstMsg->usMsgName       = ID_FC_ADD_RAB_FCID_MAP_IND;
    pstMsg->enFcId          = enFcId;
    pstMsg->ucRabId         = ucRabId;
    pstMsg->enModemId       = enModemId;

    ulResult = VOS_SendMsg(UEPS_PID_FLOWCTRL_A, pstMsg);

    if (VOS_OK != ulResult)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_ChannelMapCreate, Send Msg Fail\n");
        return;
    }
}


/*****************************************************************************
 函 数 名  : FC_ChannelMapDelete
 功能描述  : 当有一个RABID释放时，AT通过该接口删除流控模块映射关系
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_ChannelMapDelete( VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16  enModemId )
{
    FC_DEL_RAB_FCID_MAP_IND_STRU       *pstMsg;
    VOS_UINT32                          ulResult;


    /* 参数检查，RabId范围为[5,15] */
    if ( (FC_UE_MIN_RAB_ID > ucRabId) || (FC_UE_MAX_RAB_ID < ucRabId) )
    {
        FC_LOG1(PS_PRINT_WARNING, "FC_ChannelMapDelete RabId Is Invalid %d\n", ucRabId);
        return;
    }

    if ( MODEM_ID_BUTT <= enModemId )
    {
        FC_LOG1(PS_PRINT_WARNING, "FC_ChannelMapDelete ModemId Is Invalid %d\n", enModemId);
        return;
    }

    /* 发送消息 */
    pstMsg = (FC_DEL_RAB_FCID_MAP_IND_STRU *)VOS_AllocMsg(UEPS_PID_FLOWCTRL_A, \
                                    sizeof(FC_DEL_RAB_FCID_MAP_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstMsg)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_ChannelMapDelete, Alloc Msg Fail\n");
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL_A;
    pstMsg->usMsgName       = ID_FC_DEL_RAB_FCID_MAP_IND;
    pstMsg->ucRabId         = ucRabId;
    pstMsg->enModemId       = enModemId;

    ulResult = VOS_SendMsg(UEPS_PID_FLOWCTRL_A, pstMsg);

    if (VOS_OK != ulResult)
    {
        FC_LOG(PS_PRINT_ERROR, "FC_ChannelMapDelete, Send Msg Fail\n");
        return;
    }
}


/*****************************************************************************
 函 数 名  : FC_RcvCstMsg
 功能描述  : 接收CST消息
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
VOS_UINT32  FC_RcvCstMsg( MsgBlock * pMsg )
{
    switch ( FC_GET_MSG_NAME32(pMsg) )
    {
        case ID_CST_FC_SET_FLOWCTRL_REQ:
            FC_CST_UpProcess( ((CST_FC_SET_FLOWCTRL_REQ_STRU *)pMsg)->ucRabId );
            break;

        case ID_CST_FC_STOP_FLOWCTRL_REQ:
            FC_CST_DownProcess( ((CST_FC_STOP_FLOWCTRL_REQ_STRU *)pMsg)->ucRabId );
            break;

        default:
            break;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_RcvCdsMsg
 功能描述  : 接收处理CDS消息
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
VOS_UINT32  FC_RcvCdsMsg( MsgBlock * pMsg )
{
    switch ( FC_GET_MSG_NAME32(pMsg) )
    {
        case ID_CDS_FC_STOP_CHANNEL_IND:
            FC_CDS_UpProcess( ((CDS_FC_STOP_CHANNEL_IND_STRU *)pMsg)->ucRabId,
                               ((CDS_FC_STOP_CHANNEL_IND_STRU *)pMsg)->enModemId );
            break;

        case ID_CDS_FC_START_CHANNEL_IND:
            FC_CDS_DownProcess( ((CDS_FC_START_CHANNEL_IND_STRU *)pMsg)->ucRabId,
                                 ((CDS_FC_START_CHANNEL_IND_STRU *)pMsg)->enModemId );
            break;

        default:
            break;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_ACORE_PointReg
 功能描述  : 初始化时，注册一些固定的流控点
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月22日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_ACORE_RegPoint( VOS_VOID )
{
#if(FEATURE_OFF == FEATURE_UE_MODE_CDMA)
/* V9R1项目中增加使用宏开关判断FC模块是否需要进行流控点注册 */
#if(FEATURE_ON == FEATURE_NFEXT)
    FC_REG_POINT_STRU                   stFcRegPoint;

    PS_MEM_SET(&stFcRegPoint, 0, sizeof(FC_REG_POINT_STRU));

    /* CPU负载流控点注册 */
    stFcRegPoint.enPolicyId = FC_POLICY_ID_CPU_A;
    stFcRegPoint.enFcPri    = FC_PRI_FOR_BRIDGE_FORWARD_DISCARD;
    stFcRegPoint.enFcId     = FC_ID_BRIDGE_FORWARD_DISACRD;
    stFcRegPoint.ulParam1   = 0;
    stFcRegPoint.ulParam2   = 0;
    stFcRegPoint.pSetFunc   = (FC_SET_FUNC)NFExt_BrSetFlowCtrl;
    stFcRegPoint.pClrFunc   = (FC_SET_FUNC)NFExt_BrStopFlowCtrl;
    stFcRegPoint.pRstFunc   = VOS_NULL_PTR;
    FC_POINT_Reg(&stFcRegPoint);

    stFcRegPoint.enPolicyId = FC_POLICY_ID_CPU_A;
    stFcRegPoint.enFcPri    = FC_PRI_HIGHEST;
    stFcRegPoint.enFcId     = FC_ID_WIFI_ETH;
    stFcRegPoint.ulParam1   = 0;
    stFcRegPoint.ulParam2   = 0;
    stFcRegPoint.pSetFunc   = (FC_SET_FUNC)DRV_WIFI_SET_RX_FCTL;
    stFcRegPoint.pClrFunc   = (FC_SET_FUNC)DRV_WIFI_CLR_RX_FCTL;
    stFcRegPoint.pRstFunc   = VOS_NULL_PTR;
    FC_POINT_Reg(&stFcRegPoint);

    /* 内存流控点注册 */
    stFcRegPoint.enPolicyId = FC_POLICY_ID_MEM;
    stFcRegPoint.enFcPri    = FC_PRI_FOR_BRIDGE_FORWARD_DISCARD;
    stFcRegPoint.enFcId     = FC_ID_BRIDGE_FORWARD_DISACRD;
    stFcRegPoint.ulParam1   = 0;
    stFcRegPoint.ulParam2   = 0;
    stFcRegPoint.pSetFunc   = (FC_SET_FUNC)NFExt_BrSetFlowCtrl;
    stFcRegPoint.pClrFunc   = (FC_SET_FUNC)NFExt_BrStopFlowCtrl;
    stFcRegPoint.pRstFunc   = VOS_NULL_PTR;
    FC_POINT_Reg(&stFcRegPoint);

    stFcRegPoint.enPolicyId = FC_POLICY_ID_MEM;
    stFcRegPoint.enFcPri    = FC_PRI_FOR_MEM_LEV_4;
    stFcRegPoint.enFcId     = FC_ID_WIFI_ETH;
    stFcRegPoint.ulParam1   = 0;
    stFcRegPoint.ulParam2   = 0;
    stFcRegPoint.pSetFunc   = (FC_SET_FUNC)DRV_WIFI_SET_RX_FCTL;
    stFcRegPoint.pClrFunc   = (FC_SET_FUNC)DRV_WIFI_CLR_RX_FCTL;
    stFcRegPoint.pRstFunc   = VOS_NULL_PTR;
    FC_POINT_Reg(&stFcRegPoint);

#endif
#endif

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : FC_ACORE_RcvTimerMsg
 功能描述  : 接收处理定时器消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  FC_ACORE_RcvTimerMsg(REL_TIMER_MSG *pTimerMsg)
{
    switch (pTimerMsg->ulName)
    {
        case FC_TIMER_STOP_CPU_ATTEMPT:
            FC_CPUA_StopFlowCtrl();
            break;

        default:
            break;
    }

    return VOS_OK;

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
VOS_UINT32  FC_ACORE_RcvIntraMsg( MsgBlock * pMsg )
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
            FC_POINT_Change( ((FC_CHANGE_POINT_IND_STRU *)pMsg)->enFcId,
                             ((FC_CHANGE_POINT_IND_STRU *)pMsg)->enPolicyId,
                             ((FC_CHANGE_POINT_IND_STRU *)pMsg)->enPri,
                             ((FC_CHANGE_POINT_IND_STRU *)pMsg)->enModemId);
            break;

        case ID_FC_CPU_A_OVERLOAD_IND:
            FC_CPUA_UpProcess();
            break;

        case ID_FC_CPU_A_UNDERLOAD_IND:
            FC_CPUA_DownProcess();
            break;

        case ID_FC_SET_FLOWCTRL_IND:
            FC_UpProcess(((FC_SET_FLOWCTRL_IND_STRU *)pMsg)->enRateMode);
            break;

        case ID_FC_STOP_FLOWCTRL_IND:
            FC_DownProcess(((FC_SET_FLOWCTRL_IND_STRU *)pMsg)->enRateMode);
            break;

        case ID_FC_ADD_RAB_FCID_MAP_IND:
            FC_CDS_AddRab(((FC_ADD_RAB_FCID_MAP_IND_STRU *)pMsg)->enFcId,
                ((FC_ADD_RAB_FCID_MAP_IND_STRU *)pMsg)->ucRabId,
                ((FC_ADD_RAB_FCID_MAP_IND_STRU *)pMsg)->enModemId);
            break;

        case ID_FC_DEL_RAB_FCID_MAP_IND:
            FC_CDS_DelRab(( (FC_DEL_RAB_FCID_MAP_IND_STRU *)pMsg)->ucRabId,
                          ( (FC_DEL_RAB_FCID_MAP_IND_STRU *)pMsg)->enModemId);
            break;

        case ID_FC_MEM_UP_TO_TARGET_PRI_IND:
            FC_POLICY_UpToTargetPri( &(g_astFcPolicy[FC_POLICY_ID_MEM]),
                ((FC_MEM_UP_TO_TARGET_PRI_IND_STRU *)pMsg)->enTargetPri );
            break;

        case ID_FC_MEM_DOWN_TO_TARGET_PRI_IND:
            FC_POLICY_DownToTargetPri( &(g_astFcPolicy[FC_POLICY_ID_MEM]),
                ((FC_MEM_DOWN_TO_TARGET_PRI_IND_STRU *)pMsg)->enTargetPri );
            break;

        case ID_FC_ACORE_CRESET_START_IND:
            FC_ACORE_CResetProc(FC_ACORE_CRESET_BEFORE_RESET);
            break;

        case ID_FC_ACORE_CRESET_END_IND:
            FC_ACORE_CResetProc(FC_ACORE_CRESET_AFTER_RESET);
            break;

        case ID_FC_ACORE_CRESET_START_RSP:
            FC_ACORE_CResetRcvStartRsp();
            break;

        default:
            break;
    }

    return VOS_OK;
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
VOS_UINT32  FC_ACORE_MsgProc( MsgBlock * pMsg )
{
    switch (pMsg->ulSenderPid)
    {
        case UEPS_PID_FLOWCTRL_A:
        case UEPS_PID_FLOWCTRL_C:
            FC_ACORE_RcvIntraMsg(pMsg);
            break;

        case UEPS_PID_CST:
            FC_RcvCstMsg(pMsg);
            break;

        case UEPS_PID_CDS:
            FC_RcvCdsMsg(pMsg);
            break;

        case VOS_PID_TIMER:
            FC_ACORE_RcvTimerMsg( (REL_TIMER_MSG *)pMsg );
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
VOS_UINT32  FC_ACORE_Init( VOS_VOID )
{
    VOS_UINT32                          ulResult;
    VOS_INT                             iRet;
    VOS_CHAR                            ucSmName[] = "FcACoreCResetDoneSem";

    ulResult = FC_CommInit();

    if ( VOS_OK != ulResult )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_Init, ERROR, FC_CommInit return error!\n");
        return VOS_ERR;
    }

    ulResult    = FC_CPUA_Init();
    if ( VOS_OK != ulResult )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_ACORE_Init, ERROR, FC_CPUA_Init return error!\n");
        return VOS_ERR;
    }

    FC_CDS_Init();

    FC_MEM_Init();

    FC_ACORE_RegPoint();

    FC_DrvAssemInit();

    /* 创建信号量，用于C核单独复位时，通知底软FcACore的回调事务已完成 */
    if ( VOS_OK != VOS_SmBCreate(ucSmName, 0, VOS_SEMA4_FIFO, (VOS_SEM *)&g_ulFcACoreCResetDoneSem) )
    {
        FC_LOG(PS_PRINT_ERROR,"FC_ACORE_Init, Create Sem Fail\n");
        return VOS_ERR;
    }

    /* 注册回调函数到底软C核复位接口中 */
    iRet    = mdrv_sysboot_register_reset_notify ("TTF_FcACore", FC_ACORE_CResetCallback, 0, FC_ACORE_CRESET_CALLBACK_PRIOR);

    if ( VOS_OK != iRet )
    {
        FC_LOG(PS_PRINT_ERROR, "FC_ACORE_Init, ERROR, DRV_CCORERESET_REGCBFUNC fail!\n");
        return VOS_ERR;
    }

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
VOS_UINT32 FC_ACORE_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    VOS_UINT32  ulResult = VOS_ERR;


    switch (enPhase)
    {
        case   VOS_IP_LOAD_CONFIG:
#ifndef DMT
            ulResult = VOS_RegisterPIDInfo(UEPS_PID_FLOWCTRL,
                                           (Init_Fun_Type)VOS_NULL_PTR,
                                           (Msg_Fun_Type)FC_ACORE_MsgProc);
#else

            ulResult = VOS_RegisterPIDInfo(UEPS_PID_FLOWCTRL_A,
                                           (Init_Fun_Type)VOS_NULL_PTR,
                                           (Msg_Fun_Type)FC_ACORE_MsgProc);
#endif
            if (VOS_OK != ulResult)
            {
                FC_LOG(PS_PRINT_ERROR, "FC_FidInit, VOS_RegisterPIDInfo Fail\n");
                return VOS_ERR;
            }
#ifndef DMT
            ulResult = VOS_RegisterTaskPrio(UEPS_FID_FLOWCTRL, TTF_FLOW_CTRL_TASK_PRIO);
#else

            ulResult = VOS_RegisterTaskPrio(UEPS_FID_FLOWCTRL_A, TTF_FLOW_CTRL_TASK_PRIO);
#endif
            if (VOS_OK != ulResult)
            {
                FC_LOG(PS_PRINT_ERROR, "FC_FidInit, OS_RegisterTaskPrio Fail\n");
                return VOS_ERR;
            }

            ulResult = FC_ACORE_Init();

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

#else

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "FcInterface.h"

/*****************************************************************************
  2 函数实现
*****************************************************************************/
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
VOS_UINT32 FC_ACORE_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : FC_ChannelMapCreate
 功能描述  : A核流控模块提供接口给AT配置通道与RABID映射关系
 输入参数  : FC_ID_ENUM_UINT8 enFcId   通道对应的FC ID
             VOS_UINT8 ucRabId          流控对应的RabId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_ChannelMapCreate(FC_ID_ENUM_UINT8 enFcId, VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16  enModemId)
{
    return;
}

/*****************************************************************************
 函 数 名  : FC_ChannelMapDelete
 功能描述  : 当有一个RABID释放时，AT通过该接口删除流控模块映射关系
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  FC_ChannelMapDelete( VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16  enModemId )
{
    return;
}

/*****************************************************************************
 函 数 名  : FC_ACORE_RegDrvAssemFunc
 功能描述  : 注册驱动组包参数调整回调函数
 输入参数  : FC_ACORE_DRV_ASSEMBLE_PARA_FUNC pFcDrvSetAssemParaFuncUe  调整UE组包参数回调函数
             FC_ACORE_DRV_ASSEMBLE_PARA_FUNC pFcDrvSetAssemParaFuncPc  调整PC组包参数回调函数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : g45205
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_ACORE_RegDrvAssemFunc(FC_ACORE_DRV_ASSEMBLE_PARA_FUNC pFcDrvSetAssemParaFuncUe, FC_ACORE_DRV_ASSEMBLE_PARA_FUNC pFcDrvSetAssemParaFuncPc)
{
    return VOS_OK;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif



