/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsDsFlowStats.c
  版 本 号   : 初稿
  作    者   : o00132663
  生成日期   : 2011年12月14日
  最近修改   :
  功能描述   : APS流量统计处理文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月14日
    作    者   : o00132663
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafApsDsFlowStats.h"
#include "TafApsProcNvim.h"
#include "TafApsCtx.h"
#include "PsCommonDef.h"
#include "TafLog.h"
#include "ApsCdsInterface.h"
#include "TafApsSndAt.h"
#include "TafSdcLib.h"
#include "TafApsSndInternalMsg.h"

#include "NasUtranCtrlInterface.h"
#include "apminterface.h"

#include "TafApsComFunc.h"

#include "TafApsFsmMainTbl.h"

#include "TafApsMntn.h"
#include "TafApsProcEpdszid.h"

#include "TafApsCtx.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "cnas_cttf_hrpd_pa_pif.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define THIS_FILE_ID PS_FILE_ID_TAF_APS_DSFLOWSTATS_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/



/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_APS_StartDsFlowStats
 功能描述  : PDP激活时启动相关RAB承载流量统计
 输入参数  : ucRabId - RAB承载ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年5月30日
    作    者   : zhangyizhan 60575
    修改内容   : DTS2012052907939, 保存到NV的时间由NV 9036配置
  3.日    期   : 2012年11月09日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目激活PDP后开启流量上报定时器
  4.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目CDS接口修改
  5.日    期   : 2013年11月21日
    作    者   : j00174725
    修改内容   : ROTS 修改
*****************************************************************************/
VOS_VOID  TAF_APS_StartDsFlowStats(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulIndex;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;
    VOS_UINT16                          usModemid;

    /* 判断RAB ID是否有效 */
    if ((ucRabId < TAF_APS_RAB_ID_MIN)
     || (ucRabId > TAF_APS_RAB_ID_MAX))
    {
        return;
    }

    /* 初始化 */
    ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* 检查RAB是否已经激活 */
    if (VOS_TRUE == pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag)
    {
        TAF_NORMAL_LOG1(WUEPS_PID_TAF, "TAF_APS_StartDsFlowStats:NORMAL:RABM is already active! RABID:", ucRabId);
        return;
    }

    /*置该RABID激活标志:*/
    pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag = VOS_TRUE;

    /* 调用CDS API 清除该RABID的历史流量 */
    usModemid = VOS_GetModemIDFromPid(WUEPS_PID_TAF);
    CDS_ClearBearerDataFlowInfo(ucRabId, usModemid);


    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 初始化APS当前连接流量信息为0 */
    PS_MEM_SET(&pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo,
                0,
                sizeof(TAF_DSFLOW_INFO_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
    /* 记录当前连接开始时间 */
    pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ulStartLinkTime = VOS_GetTick() / PRE_SECOND_TO_TICK;

    /* 启动流量上报定时器 */
    TAF_APS_StartDsFlowRpt();

    /* 如果需要保存到NV项中，启动周期性保存流量到NV定时器 */
    if (VOS_TRUE == pstApsDsFlowCtx->ucDsFlowSave2NvFlg)
    {
        TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                           (pstApsDsFlowCtx->ucDsFlowSavePeriod * 60 * TIMER_S_TO_MS_1000),
                           TAF_APS_INVALID_PDPID);
    }
    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_StopDsFlowStats
 功能描述  : PDP去激活时停止相关RAB承载流量统计
 输入参数  : ucRabId - RAB承载ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年5月15日
    作    者   : A00165503
    修改内容   : DTS2012051402688: G模下清空流量信息后拨号数传, 时间小于10分
                 钟, 重启单板时没有将流量信息写入NV
  3.日    期   : 2012年5月18日
    作    者   : A00165503
    修改内容   : DTS2012041107552: G模数传时正常断开拨号, 流量统计异常
  4.日    期   : 2012年6月15日
    作    者   : f00179208
    修改内容   : DTS2012061407364, 流量统计低位当超出范围需要进位
  5.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目CDS接口修改
*****************************************************************************/
VOS_VOID  TAF_APS_StopDsFlowStats(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulIndex;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
    VOS_UINT16                          usModemid;

    /* 判断RAB ID是否有效 */
    if ((ucRabId < TAF_APS_RAB_ID_MIN) || (ucRabId > TAF_APS_RAB_ID_MAX))
    {
        return;
    }

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 初始化 */
    PS_MEM_SET(&stCurrentFlowInfo, 0, sizeof(TAF_DSFLOW_INFO_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();
    ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;

    if (VOS_TRUE == pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag)
    {
        /* 刷新流量上下文当前连接流量信息 */
        TAF_APS_GetCurrentFlowInfo(ucRabId, &stCurrentFlowInfo);
        pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo = stCurrentFlowInfo;

        /* 刷新流量上下文累积连接流量信息 */
        pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSLinkTime
                        += pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSLinkTime;

        /* 接收字节累加 */
        TAF_APS_BIT64_ADD(pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSReceiveFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSReceiveFluxLow,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSReceiveFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSReceiveFluxLow,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSReceiveFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSReceiveFluxLow);

        /* 发送字节累加 */
        TAF_APS_BIT64_ADD(pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSSendFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSSendFluxLow,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSSendFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSSendFluxLow,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSSendFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSSendFluxLow);

        /* 设置该RAB ID为去激活标志 */
        pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag = VOS_FALSE;

    }

    /* 如果当前所有RAB均已去激活，则停止流量上报定时器和周期性保存流量定时器 */
    if (VOS_FALSE == TAF_APS_CheckIfActiveRabIdExist())
    {
        /* 如果保存历史流量到NV特性使能，写NV */
        TAF_APS_SaveDsFlowInfoToNv();

        TAF_APS_ReleaseDfs();

        TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_REPORT,
                          TAF_APS_INVALID_PDPID);


        TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                          TAF_APS_INVALID_PDPID);
    }

    /* 调用CDS API 清除该RABID的流量信息 */
    usModemid = VOS_GetModemIDFromPid(WUEPS_PID_TAF);
    CDS_ClearBearerDataFlowInfo(ucRabId, usModemid);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_QryDsFlowStats
 功能描述  : 查询指定RAB承载的流量信息
 输入参数  : ucRabId          - RAB承载ID
 输出参数  : pstDsFlowQryInfo - 流量查询信息指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
*****************************************************************************/
/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
VOS_VOID  TAF_APS_QryDsFlowStats(
    TAF_DSFLOW_QUERY_INFO_STRU         *pstDsFlowQryInfo,
    VOS_UINT8                           ucRabId
)
/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
{
    VOS_UINT32                          ulIndex;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;

    /* 获取流量统计上下文 */
    ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* 刷新该RAB ID当前流量信息 */
    TAF_APS_GetCurrentFlowInfo(ucRabId, &pstDsFlowQryInfo->stCurrentFlowInfo);

    /* 刷新该RAB ID的历史流量信息 */
    if (VOS_TRUE == pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag)
    {
        /* 如果激活 */
        /* RABID历史流量     = APS流量统计上下文保存的历史流量 + RABID当前流量 */
        /* RABID历史连接时间 = APS流量统计上下文保存的历史连接时间 + RABID当前连接时间 */

        TAF_APS_BIT64_ADD(pstDsFlowQryInfo->stTotalFlowInfo.ulDSReceiveFluxHigh,
                          pstDsFlowQryInfo->stTotalFlowInfo.ulDSReceiveFluxLow,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSReceiveFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSReceiveFluxLow,
                          pstDsFlowQryInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh,
                          pstDsFlowQryInfo->stCurrentFlowInfo.ulDSReceiveFluxLow);

        TAF_APS_BIT64_ADD(pstDsFlowQryInfo->stTotalFlowInfo.ulDSSendFluxHigh,
                          pstDsFlowQryInfo->stTotalFlowInfo.ulDSSendFluxLow,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSSendFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSSendFluxLow,
                          pstDsFlowQryInfo->stCurrentFlowInfo.ulDSSendFluxHigh,
                          pstDsFlowQryInfo->stCurrentFlowInfo.ulDSSendFluxLow);

        pstDsFlowQryInfo->stTotalFlowInfo.ulDSLinkTime = pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSLinkTime
                          + pstDsFlowQryInfo->stCurrentFlowInfo.ulDSLinkTime;

    }
    else
    {
        /* 如果未激活 */
        /* RABID历史流量 = APS流量统计上下文保存的历史流量 */

        pstDsFlowQryInfo->stTotalFlowInfo = pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_QryAllRabDsFlowStats
 功能描述  : 查询所有RAB承载的流量信息
 输入参数  : 无
 输出参数  : pstDsFlowQryInfo - 流量查询信息结构指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数

  2.日    期   : 2012年3月26日
    作    者   : l60609
    修改内容   : DTS2012032202846：IPV4V6的情况，连接时间为最大值而不是累加值
*****************************************************************************/
/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
VOS_VOID  TAF_APS_QryAllRabDsFlowStats(
    TAF_DSFLOW_QUERY_INFO_STRU          *pstTotalDsFlowQryInfo
)
/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
{
    VOS_UINT8                           ucRabId;
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    TAF_DSFLOW_QUERY_INFO_STRU      stDsFlowQryInfo;

    /* 依次轮询所有RABID，获取流量信息并累加 */
    for ( ucRabId = TAF_APS_RAB_ID_MIN; ucRabId <=  TAF_APS_RAB_ID_MAX; ucRabId++ )
    {
        PS_MEM_SET(&stDsFlowQryInfo, 0, sizeof(TAF_DSFLOW_QUERY_INFO_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
        TAF_APS_QryDsFlowStats(&stDsFlowQryInfo, ucRabId);

        /* 当前连接时间: 取各RAB中最大值 */
        if (pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSLinkTime < stDsFlowQryInfo.stCurrentFlowInfo.ulDSLinkTime)
        {
            pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSLinkTime = stDsFlowQryInfo.stCurrentFlowInfo.ulDSLinkTime;
        }

        /* 当前连接接收字节累加 */
        TAF_APS_BIT64_ADD(pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh,
                          pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSReceiveFluxLow,
                          pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh,
                          pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSReceiveFluxLow,
                          stDsFlowQryInfo.stCurrentFlowInfo.ulDSReceiveFluxHigh,
                          stDsFlowQryInfo.stCurrentFlowInfo.ulDSReceiveFluxLow);

        /* 当前连接发送字节累加 */
        TAF_APS_BIT64_ADD(pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSSendFluxHigh,
                          pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSSendFluxLow,
                          pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSSendFluxHigh,
                          pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSSendFluxLow,
                          stDsFlowQryInfo.stCurrentFlowInfo.ulDSSendFluxHigh,
                          stDsFlowQryInfo.stCurrentFlowInfo.ulDSSendFluxLow);

        /* 总连接时间累加: 取各RAB中最大值 */
        if (pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSLinkTime < stDsFlowQryInfo.stTotalFlowInfo.ulDSLinkTime)
        {
            pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSLinkTime = stDsFlowQryInfo.stTotalFlowInfo.ulDSLinkTime;
        }

        /* 总连接接收字节累加 */
        TAF_APS_BIT64_ADD(pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSReceiveFluxHigh,
                          pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSReceiveFluxLow,
                          pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSReceiveFluxHigh,
                          pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSReceiveFluxLow,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSReceiveFluxHigh,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSReceiveFluxLow);

        /* 总连接发送字节累加 */
        TAF_APS_BIT64_ADD(pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSSendFluxHigh,
                          pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSSendFluxLow,
                          pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSSendFluxHigh,
                          pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSSendFluxLow,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSSendFluxHigh,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSSendFluxLow);

    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_ClearDsFlowStats
 功能描述  : 清除指定RAB承载的流量信息
 输入参数  : ucRabId          - RAB承载ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目CDS接口修改
  3.日    期   : 2013年11月21日
    作    者   : j00174725
    修改内容   : ROTS 修改
*****************************************************************************/
VOS_VOID  TAF_APS_ClearDsFlowStats(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucRabActiveFlag;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;
    VOS_UINT16                          usModemid;


    /* 初始化 */
    ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* 先保存该RABID激活标志 */
    ucRabActiveFlag = pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag;

    /* 流量统计上下文指定RABID流量信息清零 */
    PS_MEM_SET(&pstApsDsFlowCtx->astApsDsFlowStats[ulIndex],
                0,
                sizeof(TAF_APS_DSFLOW_STATS_STRU));

    /* 恢复该RABID激活标志信息 */
    pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag = ucRabActiveFlag;

    /* 如果RAB已激活，将当前连接时间置为当前时间，同时通知CDS清除流量信息 */
    if (VOS_TRUE == ucRabActiveFlag)
    {
        /* 调用CDS API 清除该RABID的流量信息 */
        usModemid = VOS_GetModemIDFromPid(WUEPS_PID_TAF);
        CDS_ClearBearerDataFlowInfo(ucRabId, usModemid);

        /* 记录当前连接开始时间 */
        pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ulStartLinkTime = VOS_GetTick() / PRE_SECOND_TO_TICK;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ClearAllRabDsFlowStats
 功能描述  : 清除所有RAB承载的流量信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_APS_ClearAllRabDsFlowStats( VOS_VOID )
{
    VOS_UINT8                           ucRabId;

    /* 依次轮询所有RABID，清除流量信息 */
    for ( ucRabId = TAF_APS_RAB_ID_MIN; ucRabId <=  TAF_APS_RAB_ID_MAX; ucRabId++ )
    {
        TAF_APS_ClearDsFlowStats(ucRabId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_StartDsFlowRpt
 功能描述  : 启动APS流量上报
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数

  2.日    期   : 2012年11月09日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目取消修改流量上报标志位
*****************************************************************************/
VOS_VOID  TAF_APS_StartDsFlowRpt( VOS_VOID )
{
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    /* 如果当前流量上报定时器正在运行，先停止定时器 */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_DSFLOW_REPORT,
                                           TAF_APS_INVALID_PDPID);
    if (TAF_APS_TIMER_STATUS_RUNING == enTimerStatus)
    {
        TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_REPORT, TAF_APS_INVALID_PDPID);
    }

    /* 判断当前是否有RAB激活 */
    if (VOS_TRUE == TAF_APS_CheckIfActiveRabIdExist())
    {
        /* 依次轮询所有RABID，刷新已激活RAB的当前连接流量信息 */
        TAF_APS_UpdateAllRabCurrentFlowInfo();

        /* 启动流量上报定时器 */
        TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_REPORT,
                           TI_TAF_APS_DSFLOW_REPORT_LEN,
                           TAF_APS_INVALID_PDPID);
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_StopDsFlowRpt
 功能描述  : 停止APS流量上报
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数

  2.日    期   : 2012年11月09日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目取消修改流量上报标志位
*****************************************************************************/
VOS_VOID  TAF_APS_StopDsFlowRpt( VOS_VOID )
{
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    /* 如果当前流量上报定时器正在运行，停止定时器 */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_DSFLOW_REPORT,
                                           TAF_APS_INVALID_PDPID);
    if (TAF_APS_TIMER_STATUS_RUNING == enTimerStatus)
    {
        TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_REPORT, TAF_APS_INVALID_PDPID);
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_QryDsFlowReportInfo
 功能描述  : 查询指定RAB承载的流量上报信息
 输入参数  : ucRabId            - RAB承载ID
 输出参数  : pstDsFlowRptInfo   - 流量上报结构指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_APS_QryDsFlowReportInfo(
    VOS_UINT8                           ucRabId,
    TAF_DSFLOW_REPORT_STRU             *pstDsFlowRptInfo
)
{
    VOS_UINT32                          ulIndex;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    /* 判断RAB ID是否有效 */
    if ((ucRabId < TAF_APS_RAB_ID_MIN) || (ucRabId > TAF_APS_RAB_ID_MAX))
    {
        return;
    }

    /* 初始化 */
    ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    PS_MEM_SET(&stCurrentFlowInfo, 0, sizeof(TAF_DSFLOW_INFO_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    /* 获取流量统计上下文 */
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* 获取当前连接流量信息 */
    TAF_APS_GetCurrentFlowInfo(ucRabId, &stCurrentFlowInfo);
    pstDsFlowRptInfo->stCurrentFlowInfo = stCurrentFlowInfo;

    /* 接收速率：(定时器超时时的当前连接接收流量 - 定时器启动时的当前连接接收流量 )/定时器周期 */
    TAF_APS_CalcDsflowRate(pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSReceiveFluxHigh,
                           pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSReceiveFluxLow,
                           pstDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh,
                           pstDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxLow,
                           (TI_TAF_APS_DSFLOW_REPORT_LEN/TIMER_S_TO_MS_1000),
                          &pstDsFlowRptInfo->ulCurrentReceiveRate);

    /* 发送速率：(定时器超时时的当前连接发送流量 - 定时器启动时的当前连接发送流量 )/定时器周期 */
    TAF_APS_CalcDsflowRate(pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSSendFluxHigh,
                           pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSSendFluxLow,
                           pstDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxHigh,
                           pstDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxLow,
                           (TI_TAF_APS_DSFLOW_REPORT_LEN/TIMER_S_TO_MS_1000),
                          &pstDsFlowRptInfo->ulCurrentSendRate);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_QryAllRabDsFlowReportInfo
 功能描述  : 查询所有RAB承载的流量上报信息
 输入参数  : 无
 输出参数  : pstTotalDsFlowRptInfo   - 流量上报结构指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_APS_QryAllRabDsFlowReportInfo(
    TAF_DSFLOW_REPORT_STRU             *pstTotalDsFlowRptInfo
)
{
    VOS_UINT8                           ucRabId;
    VOS_UINT32                          ulIndex;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;
    TAF_DSFLOW_REPORT_STRU              stDsFlowRptInfo;

    /* 获取流量统计上下文 */
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* 对所有激活的RAB承载，依次查询流量上报信息 */
    for ( ucRabId = TAF_APS_RAB_ID_MIN; ucRabId <=  TAF_APS_RAB_ID_MAX; ucRabId++ )
    {
        ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;

        if (VOS_TRUE == pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag)
        {
            /* 查询前先初始化为0 */
            PS_MEM_SET(&stDsFlowRptInfo, 0, sizeof(TAF_DSFLOW_REPORT_STRU));

            /* 获取指定RAB的流量上报信息 */
            TAF_APS_QryDsFlowReportInfo(ucRabId, &stDsFlowRptInfo);

            /* 当前连接时间: 取各RAB中最大值 */
            if (pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSLinkTime < stDsFlowRptInfo.stCurrentFlowInfo.ulDSLinkTime)
            {
                pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSLinkTime = stDsFlowRptInfo.stCurrentFlowInfo.ulDSLinkTime;
            }

            /* 当前发送速率，当前接收速率，当前连接发送流量，当前连接接收流量 :累加 */
            pstTotalDsFlowRptInfo->ulCurrentReceiveRate += stDsFlowRptInfo.ulCurrentReceiveRate;
            pstTotalDsFlowRptInfo->ulCurrentSendRate    += stDsFlowRptInfo.ulCurrentSendRate;

            TAF_APS_BIT64_ADD(pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh,
                              pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxLow,
                              pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh,
                              pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxLow,
                              stDsFlowRptInfo.stCurrentFlowInfo.ulDSReceiveFluxHigh,
                              stDsFlowRptInfo.stCurrentFlowInfo.ulDSReceiveFluxLow);

            TAF_APS_BIT64_ADD(pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxHigh,
                              pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxLow,
                              pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxHigh,
                              pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxLow,
                              stDsFlowRptInfo.stCurrentFlowInfo.ulDSSendFluxHigh,
                              stDsFlowRptInfo.stCurrentFlowInfo.ulDSSendFluxLow);

        }


    }

    /* 根据产品线要求，保持与Q的实现一致，QOS协商发送速率，QOS协商接收速率: 取0 */
    pstTotalDsFlowRptInfo->ulQosReceiveRate = 0;
    pstTotalDsFlowRptInfo->ulQosSendRate    = 0;

    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_GetCurrentFlowInfo
 功能描述  : 获取指定RABID的当前连接流量信息
 输入参数  : ucRabId          - RAB承载ID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目CDS接口修改(CDS_GetBearerDataFlowInfo添加modemid)
  3.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理Coverity
  4.日    期   : 2013年11月21日
    作    者   : j00174725
    修改内容   : ROTS 修改
*****************************************************************************/
/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
VOS_VOID  TAF_APS_GetCurrentFlowInfo(
    VOS_UINT8                           ucRabId,
    TAF_DSFLOW_INFO_STRU               *pstCurrentFlowInfo
)
/* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
{
    CDS_BEARER_DATA_FLOW_STRU           stDataFlowInfo;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCurSysTime;
    VOS_UINT16                          usModemid;

    if (ucRabId < TAF_APS_RAB_ID_OFFSET)
    {
        ucRabId = TAF_APS_RAB_ID_OFFSET;
    }

    /* 初始化 */
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();
    ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;

    /* 如果激活 */
    /* 调用CDS API CDS_GetBearerDataFlowInfo获取当前连接流量 */
    /* RABID当前流量 = CDS返回的当前连接流量 */

    /* 如果未激活 */
    /* RABID当前流量 = APS流量统计上下文保存的当前连接流量 */

    if (ulIndex >= TAF_APS_MAX_RAB_NUM)
    {
        ulIndex = TAF_APS_MAX_RAB_NUM - 1;
    }

    /* 获取指定RABID的当前连接流量信息 */
    if (VOS_TRUE == pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag)
    {
        /* 流量信息初始化 */
        PS_MEM_SET(&stDataFlowInfo, 0, sizeof(CDS_BEARER_DATA_FLOW_STRU));

        usModemid = VOS_GetModemIDFromPid(WUEPS_PID_TAF);
        CDS_GetBearerDataFlowInfo(ucRabId, &stDataFlowInfo, usModemid);

        /* 刷新流量上下文当前连接流量信息 */
        pstCurrentFlowInfo->ulDSReceiveFluxHigh
                                    = stDataFlowInfo.ulTotalReceiveFluxHigh;

        pstCurrentFlowInfo->ulDSReceiveFluxLow
                                    = stDataFlowInfo.ulTotalReceiveFluxLow;

        pstCurrentFlowInfo->ulDSSendFluxHigh
                                    = stDataFlowInfo.ulTotalSendFluxHigh;

        pstCurrentFlowInfo->ulDSSendFluxLow
                                    = stDataFlowInfo.ulTotalSendFluxLow;

        /* 当前连接时间：当前时间-PDP激活时间 */
        ulCurSysTime = VOS_GetTick() / PRE_SECOND_TO_TICK;

        /*与结构体中开始连接时间运算，得到本次连接总时间:*/
        if ( VOS_OK != TAF_CalcTime(pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ulStartLinkTime,
                                    ulCurSysTime,
                                    &pstCurrentFlowInfo->ulDSLinkTime) )
        {
            /*打印警告信息---计算最后一次DS从开始连接到现在所经历的时间(秒数)时出错:*/
            TAF_WARNING_LOG1( WUEPS_PID_TAF,
                              "TAF_APS_UpdateCurrentFlowInfo:WARNING:TAF_CalcTime FAIL! RabId:",
                              ucRabId );
        }

    }
    else
    {
        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
        PS_MEM_CPY(pstCurrentFlowInfo,
                  &pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo,
                   sizeof(TAF_DSFLOW_INFO_STRU) );
        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_UpdateAllRabCurrentFlowInfo
 功能描述  : 刷新所有已激活的RABID的当前连接流量信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_APS_UpdateAllRabCurrentFlowInfo( VOS_VOID )
{
    VOS_UINT8                           ucRabId;
    VOS_UINT32                          ulIndex;
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;

    /* 获取流量统计上下文指针 */
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* 依次轮询所有RABID，刷新当前连接流量信息 */
    for ( ucRabId = TAF_APS_RAB_ID_MIN; ucRabId <=  TAF_APS_RAB_ID_MAX; ucRabId++ )
    {
        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
        /* 初始化 */
        PS_MEM_SET(&stCurrentFlowInfo, 0, sizeof(TAF_DSFLOW_INFO_STRU));
        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

        /* 获取当前连接流量信息 */
        TAF_APS_GetCurrentFlowInfo(ucRabId, &stCurrentFlowInfo);

        /* 刷新流量统计上下文当前连接信息 */
        ulIndex                         = ucRabId - TAF_APS_RAB_ID_OFFSET;
        pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo
                                        = stCurrentFlowInfo;
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_UpdateAllRabCurrentFlowInfo
 功能描述  : 检查当前是否有RABID处于激活态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_APS_CheckIfActiveRabIdExist( VOS_VOID )
{
    VOS_UINT8                           ucRabId;
    VOS_UINT32                          ulIndex;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;

    /* 初始化 */
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* 依次轮询所有RABID，刷新当前连接流量信息 */
    for ( ucRabId = TAF_APS_RAB_ID_MIN; ucRabId <=  TAF_APS_RAB_ID_MAX; ucRabId++ )
    {
        ulIndex     = ucRabId - TAF_APS_RAB_ID_OFFSET;

        if (VOS_TRUE == pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_CalcDsflowRate
 功能描述  : 计算数传速率实现函数
 输入参数  : ulStartHigh - 流量计算起始值高字节
             ulStartLow  - 流量计算起始值低字节
             ulEndHigh   - 流量计算终止值高字节
             ulEndLow    - 流量计算终止值低字节
 输出参数  : pulRate     - 返回速率指针
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_APS_CalcDsflowRate(
    VOS_UINT32                          ulStartHigh,
    VOS_UINT32                          ulStartLow,
    VOS_UINT32                          ulEndHigh,
    VOS_UINT32                          ulEndLow,
    VOS_UINT32                          ulPeriod,
    VOS_UINT32                         *pulRate
)
{
    VOS_UINT32                          ulSubRstHigh;       /* 减法结果高字节 */
    VOS_UINT32                          ulSubRstLow;        /* 减法结果低字节 */
    VOS_UINT32                          ulQuotientHigh;     /* 整除结果高字节 */
    VOS_UINT32                          ulQuotientLow;      /* 整除结果低字节 */
    VOS_UINT32                          ulRemainder;        /* 整除结果余数 */
    VOS_UINT32                          ulResult;


    /* 计算流量值 */
    TAF_APS_BIT64_SUB(ulSubRstHigh,
                      ulSubRstLow,
                      ulEndHigh,
                      ulEndLow,
                      ulStartHigh,
                      ulStartLow);

    /* 计算速率 */
    ulResult = VOS_64Div32(ulSubRstHigh,
                           ulSubRstLow,
                           ulPeriod,
                          &ulQuotientHigh,
                          &ulQuotientLow,
                          &ulRemainder);

    if ( VOS_OK != ulResult )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_APS_CalcDsflowRate: VOS_64Div32 return error.");

        *pulRate = 0;
        return;
    }

    /*目前的传输速度不会大于4GB/s，故ulQuotientHigh为0，
      只返回商的低32位ulQuotientLow就行了: */
    *pulRate = ulQuotientLow;

    return;

}

/*****************************************************************************
 函 数 名  : TAF_APS_ClearApDsFlowStats
 功能描述  : 清除流量阈值统计信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_APS_ClearApDsFlowStats( VOS_VOID )
{
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstDsFlowCtx = VOS_NULL_PTR;

    pstDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    pstDsFlowCtx->ulTotalFluxHigh = 0;
    pstDsFlowCtx->ulTotalFluxLow  = 0;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcApDsFlowRpt
 功能描述  : 处理流量阈值上报
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2015年4月2日
    作    者   : w00316404
    修改内容   : clean coverity
*****************************************************************************/
VOS_VOID TAF_APS_ProcApDsFlowRpt(VOS_VOID)
{
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstDsflowCtx = VOS_NULL_PTR;
    TAF_APDSFLOW_REPORT_STRU            stApDsFlowRptInfo;
    TAF_DSFLOW_REPORT_STRU              stTotalDsFlowRptInfo;
    TAF_DSFLOW_QUERY_INFO_STRU          stDsFlowQryInfo;
    TAF_CTRL_STRU                       stCtrlHdr;
    VOS_UINT32                          ulTotalFluxThresHigh;
    VOS_UINT32                          ulTotalFluxThresLow;
    VOS_UINT32                          ulTotalFluxHigh;
    VOS_UINT32                          ulTotalFluxLow;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stApDsFlowRptInfo, 0x00, sizeof(TAF_APDSFLOW_REPORT_STRU));
    PS_MEM_SET(&stTotalDsFlowRptInfo, 0x00, sizeof(TAF_DSFLOW_REPORT_STRU));
    PS_MEM_SET(&stDsFlowQryInfo, 0x00, sizeof(TAF_DSFLOW_QUERY_INFO_STRU));
    PS_MEM_SET(&stCtrlHdr, 0x00, sizeof(TAF_CTRL_STRU));

    pstDsflowCtx = TAF_APS_GetDsFlowCtxAddr();

    if (VOS_TRUE == pstDsflowCtx->ulFluxThresRptFlg)
    {
        /* 查询所有激活RAB承载的上报流量信息 */
        TAF_APS_QryAllRabDsFlowReportInfo(&stTotalDsFlowRptInfo);

        /* 查询所有RAB承载的流量信息 */
        TAF_APS_QryAllRabDsFlowStats(&stDsFlowQryInfo);

        /* 累计上下行流量 */
        TAF_APS_BIT64_ADD(ulTotalFluxHigh,
                          ulTotalFluxLow,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSReceiveFluxHigh,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSReceiveFluxLow,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSSendFluxHigh,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSSendFluxLow);

        /* 计算累计流量上报阈值 */
        TAF_APS_BIT64_ADD(ulTotalFluxThresHigh,
                          ulTotalFluxThresLow,
                          pstDsflowCtx->ulTotalFluxHigh,
                          pstDsflowCtx->ulTotalFluxLow,
                          pstDsflowCtx->ulFluxThresHigh,
                          pstDsflowCtx->ulFluxThresLow);

        /* 检查是否达到流量上报阈值 */
        TAF_APS_BIT64_COMPARE(ulTotalFluxHigh,
                              ulTotalFluxLow,
                              ulTotalFluxThresHigh,
                              ulTotalFluxThresLow,
                              ulResult);

        if ((TAF_APS_BIT64_GREAT == ulResult) || (TAF_APS_BIT64_EQUAL == ulResult))
        {
            /* 更新累计流量 */
            pstDsflowCtx->ulTotalFluxHigh       = ulTotalFluxHigh;
            pstDsflowCtx->ulTotalFluxLow        = ulTotalFluxLow;

            /* 填写控制头 */
            TAF_APS_CFG_AT_EVT_CTRL_HDR(&stCtrlHdr, MN_CLIENT_ID_BROADCAST, 0);

            /* 填写事件内容 */
            stApDsFlowRptInfo.ulCurrentTxRate   = stTotalDsFlowRptInfo.ulCurrentSendRate;
            stApDsFlowRptInfo.ulCurrentRxRate   = stTotalDsFlowRptInfo.ulCurrentReceiveRate;
            stApDsFlowRptInfo.stCurrentFlowInfo = stTotalDsFlowRptInfo.stCurrentFlowInfo;
            stApDsFlowRptInfo.stTotalFlowInfo   = stDsFlowQryInfo.stTotalFlowInfo;

            /* 流量阈值上报 */
            TAF_APS_SndApDsFlowRptInd(&stCtrlHdr, &stApDsFlowRptInfo);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ShowDdrInfo
 功能描述  : 打印DDR调频信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月05日
    作    者   : 范晶 00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_APS_ShowDdrInfo(VOS_VOID)
{
    VOS_UINT32                              i;
    VOS_UINT32                              j;
    TAF_APS_SWITCH_DDR_RATE_INFO_STRU      *pstSwitchDdrInfo;

    pstSwitchDdrInfo = TAF_APS_GetSwitchDdrRateInfoAddr();

    /*vos_printf("request id                 %d\n", pstSwitchDdrInfo->iDfsReqId);*/
    (VOS_VOID)vos_printf("request id                 %d\n", pstSwitchDdrInfo->iDfsReqId);
    (VOS_VOID)vos_printf("request value              %d\n", pstSwitchDdrInfo->ulReqValue);
    (VOS_VOID)vos_printf("multi dfs flag             %d\n", pstSwitchDdrInfo->ulMultiDfsFlg);

    for (i = 0; i < TAF_NVIM_DIFF_DFS_NUM; i++)
    {
        for (j = 0; j < pstSwitchDdrInfo->astDfsConfig[i].ulProfileNum; j++)
        {
            (VOS_VOID)vos_printf("rat[%d] profile[%d] ulDlRate           %d\n", i, j, pstSwitchDdrInfo->astDfsConfig[i].astProfile[j].ulDlRate);
            (VOS_VOID)vos_printf("rat[%d] profile[%d] ulUlRate           %d\n", i, j, pstSwitchDdrInfo->astDfsConfig[i].astProfile[j].ulUlRate);
            (VOS_VOID)vos_printf("rat[%d] profile[%d] ulDdrBand          %d\n", i, j, pstSwitchDdrInfo->astDfsConfig[i].astProfile[j].ulDdrBand);
        }
    }

    (VOS_VOID)vos_printf("request Suc Count          %d\n", pstSwitchDdrInfo->stDfsDebugInfo.ulRequestSucCnt);
    (VOS_VOID)vos_printf("request fail Count         %d\n", pstSwitchDdrInfo->stDfsDebugInfo.ulRequestFailCnt);
    (VOS_VOID)vos_printf("update Suc Count           %d\n", pstSwitchDdrInfo->stDfsDebugInfo.ulUpdateSucCnt);
    (VOS_VOID)vos_printf("update fail count          %d\n", pstSwitchDdrInfo->stDfsDebugInfo.ulUpdateFailCnt);

    (VOS_VOID)vos_printf("min band                   %d\n", pstSwitchDdrInfo->ulMinBand);
    (VOS_VOID)vos_printf("max band                   %d\n", pstSwitchDdrInfo->ulMaxBand);

}

/*****************************************************************************
 函 数 名  : TAF_APS_ReleaseDfs
 功能描述  : 释放DDR调频的投票
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月05日
    作    者   : 范晶 00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_APS_ReleaseDfs(VOS_VOID)
{
#if defined(INSTANCE_1) || defined(INSTANCE_2)

#else
    TAF_APS_SWITCH_DDR_RATE_INFO_STRU      *pstSwitchDdrInfo;

    pstSwitchDdrInfo = TAF_APS_GetSwitchDdrRateInfoAddr();

    if (0 != TAF_APS_GET_DFS_PROFILE_NUM())
    {
        if (MDRV_OK != mdrv_pm_dfs_qos_update(DFS_QOS_ID_DDR_MINFREQ_E,
                                              pstSwitchDdrInfo->iDfsReqId,
                                              TAF_APS_GET_DSFLOW_RELEASE_DFS()))
        {
            TAF_APS_DFS_UPDATE_FAIL_CNT(1);
            TAF_APS_SndOmDfsInfo(pstSwitchDdrInfo);
            return;
        }

        pstSwitchDdrInfo->ulReqValue   = TAF_APS_GET_DSFLOW_RELEASE_DFS();
        pstSwitchDdrInfo->ulSetMaxFlag = VOS_FALSE;
        TAF_APS_DFS_UPDATE_SUCC_CNT(1);
        TAF_APS_SndOmDfsInfo(pstSwitchDdrInfo);

        (VOS_VOID)mdrv_pm_wake_unlock(PWRCTRL_SLEEP_DSFLOW);

    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetCurrRatMode
 功能描述  : 获取当前的接入技术模式，区分td和w
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_APS_RAT_TYPE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年05月26日
    作    者   : m00217266
    修改内容   : 新生成函数
*****************************************************************************/
TAF_APS_DFS_TYPE_ENUM_UINT32 TAF_APS_GetCurrDfsMode(VOS_VOID)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enMmcApsRat;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    enMmcApsRat = TAF_APS_GetCurrPdpEntityRatType();

    if (TAF_APS_RAT_TYPE_GSM == enMmcApsRat)
    {
        return TAF_APS_DFS_TYPE_GSM;
    }

    if (TAF_APS_RAT_TYPE_LTE == enMmcApsRat)
    {
        return TAF_APS_DFS_TYPE_LTE;
    }

    if (TAF_APS_RAT_TYPE_WCDMA == enMmcApsRat)
    {
        enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

        if (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranMode)
        {
            return TAF_APS_DFS_TYPE_WCDMA;
        }

        if (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode)
        {
            return TAF_APS_DFS_TYPE_TD_WCDMA;
        }
    }

    if ((TAF_APS_RAT_TYPE_1X == enMmcApsRat)
     || (TAF_APS_RAT_TYPE_HRPD == enMmcApsRat)
     || (TAF_APS_RAT_TYPE_EHRPD == enMmcApsRat))
    {
        return TAF_APS_DFS_TYPE_CDMA;
    }

    return TAF_APS_DFS_TYPE_BASE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_FindDfsReqValueByRat
 功能描述  : 根据接入技术查找DDR调频请求值
 输入参数  : VOS_UINT32                          ulDLRate
             VOS_UINT32                          ulULRate
 输出参数  : VOS_UINT32                         *pulReqValue
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年05月26日
    作    者   : m00217266
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_FindDfsReqValueByRat(
    VOS_UINT32                         *pulReqValue,
    VOS_UINT32                          ulDLRate,
    VOS_UINT32                          ulULRate
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulDLReqValue;
    VOS_UINT32                          ulULReqValue;
    TAF_APS_DFS_TYPE_ENUM_UINT32        enDfsType;

    ulDLReqValue = TAF_APS_GET_DSFLOW_MIN_DDR_BAND();
    ulULReqValue = TAF_APS_GET_DSFLOW_MIN_DDR_BAND();
    enDfsType    = TAF_APS_GetCurrDfsMode();

    if (0 == TAF_APS_GET_MULTI_DFS_PROFILE_NUM(enDfsType))
    {
        ulRet = TAF_APS_FindDfsReqValue(pulReqValue, ulDLRate, ulULRate);
        return ulRet;
    }

    /* 查找下行流速对应的DDR调频值 */
    for (i = 0; i < (TAF_APS_GET_MULTI_DFS_PROFILE_NUM(enDfsType)); i++)
    {
        if (i == (TAF_APS_GET_MULTI_DFS_PROFILE_NUM(enDfsType) - 1))
        {
            ulDLReqValue = TAF_APS_GET_MULTI_DFS_PROFILE_DDR_BAND(enDfsType, i);
            break;
        }

        if ((ulDLRate >= TAF_APS_GET_MULTI_DFS_PROFILE_DL_RATE(enDfsType, i))
         && (ulDLRate < TAF_APS_GET_MULTI_DFS_PROFILE_DL_RATE(enDfsType, i + 1)))
        {
            ulDLReqValue = TAF_APS_GET_MULTI_DFS_PROFILE_DDR_BAND(enDfsType, i);
            break;
        }
    }

    /* 查找上行流速对应的DDR调频值 */
    for (i = 0; i < (TAF_APS_GET_MULTI_DFS_PROFILE_NUM(enDfsType)); i++)
    {
        if (i == (TAF_APS_GET_MULTI_DFS_PROFILE_NUM(enDfsType) - 1))
        {
            ulULReqValue = TAF_APS_GET_MULTI_DFS_PROFILE_DDR_BAND(enDfsType, i);
            break;
        }

        if ((ulULRate >= TAF_APS_GET_MULTI_DFS_PROFILE_UL_RATE(enDfsType, i))
         && (ulULRate < TAF_APS_GET_MULTI_DFS_PROFILE_UL_RATE(enDfsType, i + 1)))
        {
            ulULReqValue = TAF_APS_GET_MULTI_DFS_PROFILE_DDR_BAND(enDfsType, i);
            break;
        }
    }

    *pulReqValue = PS_MAX(ulDLReqValue, ulULReqValue);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_APS_FindDfsReqValue
 功能描述  : 查找DDR调频请求值
 输入参数  : VOS_UINT32                          ulDLRate
             VOS_UINT32                          ulULRate
 输出参数  : VOS_UINT32                         *pulReqValue
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月05日
    作    者   : 范晶 00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_FindDfsReqValue(
    VOS_UINT32                         *pulReqValue,
    VOS_UINT32                          ulDLRate,
    VOS_UINT32                          ulULRate
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulDLReqValue;
    VOS_UINT32                          ulULReqValue;

    ulDLReqValue = TAF_APS_GET_DSFLOW_MIN_DDR_BAND();
    ulULReqValue = TAF_APS_GET_DSFLOW_MIN_DDR_BAND();

    if (0 == TAF_APS_GET_DFS_PROFILE_NUM())
    {
        return VOS_ERR;
    }

    /* 查找下行流速对应的DDR调频值 */
    for (i = 0; i < (TAF_APS_GET_DFS_PROFILE_NUM()); i++)
    {
        if (i == (TAF_APS_GET_DFS_PROFILE_NUM() - 1))
        {
            ulDLReqValue = TAF_APS_GET_DFS_PROFILE_DDR_BAND(i);
            break;
        }

        if ((ulDLRate >= TAF_APS_GET_DFS_PROFILE_DL_RATE(i))
         && (ulDLRate < TAF_APS_GET_DFS_PROFILE_DL_RATE(i + 1)))
        {
            ulDLReqValue = TAF_APS_GET_DFS_PROFILE_DDR_BAND(i);
            break;
        }
    }

    /* 查找上行流速对应的DDR调频值 */
    for (i = 0; i < (TAF_APS_GET_DFS_PROFILE_NUM()); i++)
    {
        if (i == (TAF_APS_GET_DFS_PROFILE_NUM() - 1))
        {
            ulULReqValue = TAF_APS_GET_DFS_PROFILE_DDR_BAND(i);
            break;
        }

        if ((ulULRate >= TAF_APS_GET_DFS_PROFILE_UL_RATE(i))
         && (ulULRate < TAF_APS_GET_DFS_PROFILE_UL_RATE(i + 1)))
        {
            ulULReqValue = TAF_APS_GET_DFS_PROFILE_DDR_BAND(i);
            break;
        }
    }

    *pulReqValue = PS_MAX(ulDLReqValue, ulULReqValue);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SwitchDdrRateByCurrentRate
 功能描述  : 根据当前的数据速率来调节DDR的频率
 输入参数  : VOS_UINT32 ulDlRate
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月05日
    作    者   : 范晶 00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_APS_SwitchDdrRateByCurrentRate(
    VOS_UINT32                          ulDlRate,
    VOS_UINT32                          ulUlRate
)
{
#if defined(INSTANCE_1) || defined(INSTANCE_2)

#else
    TAF_APS_SWITCH_DDR_RATE_INFO_STRU  *pstSwitchDdrInfo;
    VOS_UINT32                          ulReqValue;
    VOS_UINT32                          ulMinDdrFlg;

    ulReqValue       = TAF_APS_GET_DSFLOW_MIN_DDR_BAND();
    pstSwitchDdrInfo = TAF_APS_GetSwitchDdrRateInfoAddr();
    ulMinDdrFlg      = VOS_FALSE;

    /* 如果有设置过最大频率这本次的调频不再处理 */
    if (VOS_TRUE == pstSwitchDdrInfo->ulSetMaxFlag)
    {
        pstSwitchDdrInfo->ulSetMaxFlag = VOS_FALSE;
        return;
    }

    /* 目前的DDR调频策略:
       下行大于72M,                                 DDR调到533Mhz;
       下行小于72M大于36M, 或者上行大于36M,         DDR调到360Mhz;
       下行小于36M大于2M,  或者上行小于36M大于2M,   DDR调到266Mhz;
       下行小于2M大于300K, 或者上行小于2M大于300K,  DDR调到150Mhz;
       上下行都小于300K,                            DDR调到75Mhz.
    */

    /* 根据当前的上下行速率查找DDR投票请求值 */
    if (VOS_TRUE == TAF_APS_GET_MULTI_DFS_SUPPORT_FLG())
    {
        if (VOS_OK != TAF_APS_FindDfsReqValueByRat(&ulReqValue, ulDlRate, ulUlRate))
        {
            return;
        }
    }

    if (VOS_FALSE == TAF_APS_GET_MULTI_DFS_SUPPORT_FLG())
    {
        if (VOS_OK != TAF_APS_FindDfsReqValue(&ulReqValue, ulDlRate, ulUlRate))
        {
            return;
        }
    }


    /* 防止重复投票 */
    if (ulReqValue == pstSwitchDdrInfo->ulReqValue)
    {
        return;
    }

    if (MDRV_OK != mdrv_pm_dfs_qos_update(DFS_QOS_ID_DDR_MINFREQ_E,
                                          pstSwitchDdrInfo->iDfsReqId,
                                          ulReqValue))
    {
        TAF_APS_DFS_UPDATE_FAIL_CNT(1);
        TAF_APS_SndOmDfsInfo(pstSwitchDdrInfo);
        return;
    }

    pstSwitchDdrInfo->ulReqValue = ulReqValue;
    TAF_APS_DFS_UPDATE_SUCC_CNT(1);

    TAF_APS_SndOmDfsInfo(pstSwitchDdrInfo);

    ulMinDdrFlg = TAF_APS_CheckIfMinDdrBand(ulReqValue);

    /* 目前流量统计的时间是1秒，当突然没有流量时，连接态立即进入到IDLE态后，CCPU
       进入睡眠后，流量统计定时器不再超时时，DDR之前投票到高频后就无法降到低频，
       故增加对CCPU睡眠的投票 */
    /* 流速小于300K时释放CCPU睡眠投票，大于300K时阻止CCPU睡眠 */
    if (VOS_TRUE == ulMinDdrFlg)
    {
        (VOS_VOID)mdrv_pm_wake_unlock(PWRCTRL_SLEEP_DSFLOW);
    }
    else
    {
        (VOS_VOID)mdrv_pm_wake_lock(PWRCTRL_SLEEP_DSFLOW);
    }

#endif

    return;

}


/*****************************************************************************
 函 数 名  : TAF_APS_SetDfsMax
 功能描述  : 将DFS调到最大
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月17日
    作    者   : 范晶 00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_APS_SetDfsMax(VOS_VOID)
{
    TAF_APS_SWITCH_DDR_RATE_INFO_STRU  *pstSwitchDdrInfo;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    pstSwitchDdrInfo = TAF_APS_GetSwitchDdrRateInfoAddr();

    /* 调频功能不支持，则什么都不处理 */
    if (0 == TAF_APS_GET_DFS_PROFILE_NUM())
    {
        return;
    }
    /* 当前流量定时器没有启动，什么都不处理 */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_DSFLOW_REPORT,
                                           TAF_APS_INVALID_PDPID);
    if (TAF_APS_TIMER_STATUS_RUNING != enTimerStatus)
    {
        return;
    }

    /* 已经是最高档位，不再调节 */
    if (TAF_APS_GET_DSFLOW_MAX_DDR_BAND() == pstSwitchDdrInfo->ulReqValue)
    {
        return;
    }

    /* 直接将DDR调到最高一档 */
    if (MDRV_OK != mdrv_pm_dfs_qos_update(DFS_QOS_ID_DDR_MINFREQ_E,
                                          pstSwitchDdrInfo->iDfsReqId,
                                          TAF_APS_GET_DSFLOW_MAX_DDR_BAND()))

    {
        TAF_APS_DFS_UPDATE_FAIL_CNT(1);
        TAF_APS_SndOmDfsInfo(pstSwitchDdrInfo);
        return;
    }

    pstSwitchDdrInfo->ulReqValue   = TAF_APS_GET_DSFLOW_MAX_DDR_BAND();
    pstSwitchDdrInfo->ulSetMaxFlag = VOS_TRUE;
    TAF_APS_DFS_UPDATE_SUCC_CNT(1);
    (VOS_VOID)mdrv_pm_wake_lock(PWRCTRL_SLEEP_DSFLOW);
    TAF_APS_SndOmDfsInfo(pstSwitchDdrInfo);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_APS_CheckIfMinDdrBand
 功能描述  : 确认当前的ddr频率是否为当前的接入技术对应ddr频率的最小值
 输入参数  : VOS_UINT32 ulReqValue
 输出参数  : 无
 返 回 值  : VOS_TRUE、VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月18日
    作    者   : 马仁坤 m00217266
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_CheckIfMinDdrBand(
    VOS_UINT32                          ulReqValue
)
{
    VOS_UINT32                          ulMinDdrBand;
    TAF_APS_DFS_TYPE_ENUM_UINT32        enDfsType;

    enDfsType    = TAF_APS_GetCurrDfsMode();

    if (0 == TAF_APS_GET_MULTI_DFS_PROFILE_NUM(enDfsType))
    {
        ulMinDdrBand = TAF_APS_GET_DSFLOW_MIN_DDR_BAND();
    }
    else
    {
        ulMinDdrBand = TAF_APS_GET_MULTI_DFS_PROFILE_DDR_BAND(enDfsType, 0);
    }

    if (ulMinDdrBand == ulReqValue)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_APS_ProcRlpDataStatus
 功能描述  : APS提供给RLP的回调函数，RLP每20毫秒调用一次
 输入参数  : pstRlpDataStat : RLP参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年10月27日
   作    者   : h00246512
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcRlpDataStatusCb(
    const RLPITF_1X_RLP_DATA_STAT_STRU *const pstRlpDataStat
)
{
    VOS_UINT32                          i;
    static VOS_UINT32                   aulNoDataTimes[CTTF_1X_RLP_MAX_SRV_CONN_REC_NUM] = {0};
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           uc1xPktDataInactivityTimerLen;
    VOS_UINT8                           ucPreSetPktDataInactTimerLenInNv;

    ucPreSetPktDataInactTimerLenInNv = 5;

    if (0 == pstRlpDataStat->ucActiveConnsCnt)
    {
        return;
    }

    for (i = 0; i < TAF_APS_MIN(pstRlpDataStat->ucActiveConnsCnt, CTTF_1X_RLP_MAX_SRV_CONN_REC_NUM); i++)
    {
        /* 如果找不到有效的PDP ID，说明是无效的Con_Ref，则直接跳过 */
        ucPdpId = TAF_APS_GetPdpIdByConRef(pstRlpDataStat->astRlpBoValidFrame[i].ucConnReference);

        if (TAF_APS_INVALID_PDPID == ucPdpId)
        {
            continue;
        }

        /* TODO:这里需要判断当前是否在1X模式下 */
        /* 如果ucPdpId对应的状态机不在TAF_APS_STA_ACTIVE，清空进入dormant的计数  */
        if (TAF_APS_STA_ACTIVE != TAF_APS_GetPdpIdMainFsmState(ucPdpId))
        {
            aulNoDataTimes[i] = 0;
            TAF_INFO_LOG1(WUEPS_PID_TAF, "TAF_APS_ProcRlpDataStatusCb: clear 1x aulNoDataTimes of CTTF_1X_RLP_SRV_CONN_REC", i);
            continue;
        }

        if (PS_TRUE == pstRlpDataStat->astRlpBoValidFrame[i].enNonIdleNonFillFrameSentOrRcvd)
        {
            if (VOS_FALSE == TAF_APS_GetHysActivationInd())
            {
                TAF_APS_SetHysActivationInd(VOS_TRUE);

                TAF_APS_SndHaiChangeInd(ucPdpId);
            }
        }


        /* The mobile station shall maintain a packet data inactivity timer.  The value of this timer
             shall not be less than 5 seconds.  The timer should be reset whenever a RLP
             data frame is sent or received.  If the packet data inactivity timer expires, the mobile
             station should disconnect the packet data service option.  */
        uc1xPktDataInactivityTimerLen = TAF_APS_GetPktCdataInactivityTimerLen();

        if ((PS_TRUE == pstRlpDataStat->astRlpBoValidFrame[i].enNonIdleNonFillFrameSentOrRcvd)
          ||(0 == uc1xPktDataInactivityTimerLen))

        {
            aulNoDataTimes[i] = 0;

            if (ucPreSetPktDataInactTimerLenInNv != uc1xPktDataInactivityTimerLen)
            {
                TAF_INFO_LOG2(WUEPS_PID_TAF,
                             "TAF_APS_GetPktCdataInactivityTimerLen and aulNoDataTimes ",
                             uc1xPktDataInactivityTimerLen,
                             aulNoDataTimes[i]);
            }
        }
        else
        {
            aulNoDataTimes[i]++;

            if (aulNoDataTimes[i] > (VOS_UINT32)((uc1xPktDataInactivityTimerLen * 1000) / TAF_APS_CDATA_NO_DATA_TIME_LEN_PER_TIMES))
            {
                TAF_APS_SndEnterDormantInd(ucPdpId);
                aulNoDataTimes[i] = 0;
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcEvdoRlpDataStatusCb
 功能描述  : APS提供给RLP的回调函数，RLP每80毫秒调用一次
 输入参数  : enFlowActivity : RLP参数
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月02日
   作    者   : y00314741
   修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID TAF_APS_ProcEvdoRlpDataStatusCb(
    PS_BOOL_ENUM_UINT8                  enFlowActivity
)
{
    VOS_UINT8                           ucPdpId;
    static VOS_UINT32                   ulNoDataTime = 0;
    VOS_UINT8                           ucDoPktDataInactivityTimerLen;
    VOS_UINT8                           ucPreSetPktDataInactTimerLenInNv;

    ucPreSetPktDataInactTimerLenInNv = 5;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        /* 如果ucPdpId对应的状态机不在TAF_APS_STA_ACTIVE，清空进入dormant的计数 */
        if (TAF_APS_STA_ACTIVE != TAF_APS_GetPdpIdMainFsmState(ucPdpId))
        {
            ulNoDataTime = 0;
            TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_APS_ProcEvdoRlpDataStatusCb: clear DO ulNoDataTime");
            continue;
        }

        if (TAF_APS_RAT_TYPE_LTE == TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            ulNoDataTime = 0;

            return;
        }

        if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            if (TAF_PS_CDATA_BEAR_STATUS_ACTIVE != TAF_APS_GetCdataEhrpdSvcSta(ucPdpId))
            {
                ulNoDataTime = 0;

                return;
            }
        }

        ucDoPktDataInactivityTimerLen = TAF_APS_GetPktCdataInactivityTimerLen();

        if ((PS_TRUE == enFlowActivity)
          ||(0 == ucDoPktDataInactivityTimerLen))
        {
            ulNoDataTime = 0;

            if (ucPreSetPktDataInactTimerLenInNv != ucDoPktDataInactivityTimerLen)
            {
                TAF_INFO_LOG2(WUEPS_PID_TAF,
                             "TAF_APS_GetPktCdataInactivityTimerLen and ulNoDataTime ",
                              ucDoPktDataInactivityTimerLen,
                              ulNoDataTime);
            }
        }
        else
        {
            ulNoDataTime++;

            if (ulNoDataTime > (VOS_UINT32)((ucDoPktDataInactivityTimerLen * 1000) / TAF_APS_CDATA_EVDO_NO_DATA_TIME_LEN_PER_TIMES))
            {
                TAF_APS_SndEnterDormantInd(ucPdpId);


                ulNoDataTime = 0;

                break;
            }

        }
    }

    return;
}
#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
