/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsPreproc.c
  版 本 号   : 初稿
  作    者   : o00132663
  生成日期   : 2011年12月28日
  最近修改   :
  功能描述   : TAF APS模块状态机预处理函数实现文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月28日
    作    者   : o00132663
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsCommonDef.h"
#include "Taf_Tafm_Remote.h"
#include "MnApsComm.h"
#include "MmaAppLocal.h"
#include "TafLog.h"
#include "TafApsCtx.h"
#include "TafApsProcNvim.h"
#include "TafAgentInterface.h"
#include "TafApsPreproc.h"
#include "TafApsComFunc.h"
#include "TafApsSndAt.h"
#include "ApsNdInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "TafApsSndL4a.h"
#include "MnApsMultiMode.h"
#endif
#include "TafSdcLib.h"
#include "TafApsProcIpFilter.h"
#include "TafApsApi.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "xcc_aps_pif.h"
#include "TafApsSndXcc.h"
#include "taf_aps_ppp_pif.h"
#include "xreg_aps_pif.h"
#include "hsm_aps_pif.h"
#include "TafApsSndHsm.h"
#endif

#include "TafMmaInterface.h"
#include "TafApsMntn.h"


#include "NasUsimmApi.h"
#include "NasComm.h"

#include "ehsm_aps_pif.h"
#include "taf_aps_dhcp_pif.h"
#include "TafApsSndCds.h"
#include "TafApsSndDhcp.h"
#include "TafApsSndEhsm.h"
#include "TafApsSndPpp.h"
#include "cnas_cttf_hrpd_pa_pif.h"

#include "TafApsProcUsim.h"

#include "TafApsProcEpdszid.h"
#include "TafApsSndInternalMsg.h"
#include "ApsCdsInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_PREPROC_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetDsFlowInfoReq_PreProc
 功能描述  : AT消息ID_MSG_TAF_PS_GET_DSFLOW_INFO_REQ预处理函数
 输入参数  : ulEventType - 事件名
             pstMsg      - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE    - 消息处理完毕
             VOS_FALSE   - 消息未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetDsFlowInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstMsgHeader;
    TAF_PS_GET_DSFLOW_INFO_REQ_STRU    *pstGetDsFlowInfoReq;
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    TAF_DSFLOW_QUERY_INFO_STRU          stDsFlowQryInfo;

    /* 初始化 */
    pstMsgHeader        = (TAF_PS_MSG_STRU *)pstMsg;
    pstGetDsFlowInfoReq = (TAF_PS_GET_DSFLOW_INFO_REQ_STRU *)(pstMsgHeader->aucContent);

    /* 流量上报信息初始化 */
    PS_MEM_SET(&stDsFlowQryInfo, 0, sizeof(TAF_DSFLOW_QUERY_INFO_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    /* 查询所有RAB承载的流量信息 */
    TAF_APS_QryAllRabDsFlowStats(&stDsFlowQryInfo);

    /* 给AT回复查询到的流量信息 */
    TAF_APS_SndGetDsFlowInfoCnf(&(pstGetDsFlowInfoReq->stCtrl),
                                TAF_ERR_NO_ERROR,
                               &stDsFlowQryInfo);


    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtClearDsFlowReq_PreProc
 功能描述  : AT消息ID_MSG_TAF_PS_CLEAR_DSFLOW_REQ预处理函数
 输入参数  : ulEventType - 事件名
             pstMsg      - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32  - 函数执行结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数

  2.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : DTS2015021010050: 清除流量阈值相关统计
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtClearDsFlowReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstMsgHeader;
    TAF_PS_CLEAR_DSFLOW_REQ_STRU       *pstClearDsFlowReq;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsflowCtx;


    /* 初始化 */
    pstMsgHeader        = (TAF_PS_MSG_STRU*)pstMsg;
    pstClearDsFlowReq   = (TAF_PS_CLEAR_DSFLOW_REQ_STRU*)(pstMsgHeader->aucContent);

    /* 清除所有RAB承载的流量信息 */
    TAF_APS_ClearAllRabDsFlowStats();

    /* 清除AP相关流量统计 */
    TAF_APS_ClearApDsFlowStats();

    /* 如果流量保存NV功能使能，清除NV项中历史信息 */
    pstApsDsflowCtx = TAF_APS_GetDsFlowCtxAddr();
    if (VOS_TRUE == pstApsDsflowCtx->ucDsFlowSave2NvFlg)
    {
        TAF_APS_ClearDsFlowInfoInNv();
    }

    /* 给AT回复结果 */
    TAF_APS_SndClearDsFlowCnf(&(pstClearDsFlowReq->stCtrl),
                               TAF_ERR_NO_ERROR);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvConfigDsFlowRptReq_PreProc
 功能描述  : AT消息ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ预处理函数
 输入参数  : ulEventType - 事件名
             pstMsg      - 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32  - 函数执行结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数

  2.日    期   : 2012年11月09日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目修改AT端口流量上报标志位
  3.日    期   : 2013年4月8日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtConfigDsFlowRptReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstMsgHeader;
    TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU  *pstConfigDsFlowRptReq;
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, begin */
    VOS_UINT32                          ulRptCmdStatus;

    /* 初始化 */
    pstMsgHeader            = (TAF_PS_MSG_STRU*)pstMsg;
    pstConfigDsFlowRptReq   = (TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU*)(pstMsgHeader->aucContent);

    /* 更新单个命令设置主动上报的全局变量 */
    if ( VOS_TRUE == pstConfigDsFlowRptReq->stReportConfigInfo.ulRptEnabled )
    {
        /* 启动AT端口流量上报 */
        ulRptCmdStatus = VOS_TRUE;
    }
    else
    {
        /* 停止AT端口流量上报 */
        ulRptCmdStatus = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_DSFLOWRPT, ulRptCmdStatus);
    /* Modified by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, end */

    /* 给AT回复清除结果 */
    TAF_APS_SndConfigDsFlowRptCnf(&(pstConfigDsFlowRptReq->stCtrl),
                                  TAF_ERR_NO_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSetApDsFlowRptCfgReq_PreProc
 功能描述  : 消息ID_MSG_TAF_PS_SET_APDSFLOW_RPT_CFG_REQ预处理函数
 输入参数  : ulEventType --- 事件名
             pstMsg      --- 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE    --- 消息处理完毕
             VOS_FALSE   --- 消息未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSetApDsFlowRptCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU   *pstSetRptCfgReq = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU          *pstDsFlowCtx    = VOS_NULL_PTR;
    TAF_PS_CAUSE_ENUM_UINT32                enCause;
    VOS_UINT32                              ulResult;

    pstSetRptCfgReq = (TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    pstDsFlowCtx    = TAF_APS_GetDsFlowCtxAddr();

    if (VOS_TRUE == pstSetRptCfgReq->stRptCfg.ulRptEnabled)
    {
        /* 阈值换算: KBYTE ---> BYTE */
        ulResult = VOS_64Multi32(0,                                             /* ulMultiplicandHigh */
                                 pstSetRptCfgReq->stRptCfg.ulFluxThreshold,     /* ulMultiplicandLow */
                                 TAF_APS_1_KBYTE_1024_BYTE,                     /* ulMultiplicator */
                                 &(pstDsFlowCtx->ulFluxThresHigh),              /* pulProductHigh */
                                 &(pstDsFlowCtx->ulFluxThresLow));              /* pulProductLow */
        if (VOS_OK == ulResult)
        {
            /* 更新流量阈值上报参数 */
            pstDsFlowCtx->ulFluxThresRptFlg = VOS_TRUE;
            pstDsFlowCtx->ulFluxThresKByte  = pstSetRptCfgReq->stRptCfg.ulFluxThreshold;

            enCause                         = TAF_PS_CAUSE_SUCCESS;
        }
        else
        {
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvSetApDsFlowRptCfgReq_PreProc: VOS_64Multi32 failed.");

            enCause                         = TAF_PS_CAUSE_INVALID_PARAMETER;
        }
    }
    else
    {
        /* 更新流量阈值上报参数 */
        pstDsFlowCtx->ulFluxThresRptFlg     = VOS_FALSE;
        pstDsFlowCtx->ulFluxThresKByte      = 0;
        pstDsFlowCtx->ulFluxThresHigh       = 0;
        pstDsFlowCtx->ulFluxThresLow        = 0;
        pstDsFlowCtx->ulTotalFluxHigh       = 0;
        pstDsFlowCtx->ulTotalFluxLow        = 0;

        enCause                             = TAF_PS_CAUSE_SUCCESS;
    }

    TAF_APS_SndSetApDsFlowRptCfgCnf(&(pstSetRptCfgReq->stCtrl), enCause);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvGetApDsFlowRptCfgReq_PreProc
 功能描述  : 消息ID_MSG_TAF_PS_GET_APDSFLOW_RPT_CFG_REQ预处理函数
 输入参数  : ulEventType --- 事件名
             pstMsg      --- 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE    --- 消息处理完毕
             VOS_FALSE   --- 消息未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月4日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvGetApDsFlowRptCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU   *pstGetRptCfgReq = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU          *pstDsFlowCtx    = VOS_NULL_PTR;
    TAF_APDSFLOW_RPT_CFG_STRU               stRptCfg;

    pstGetRptCfgReq = (TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    pstDsFlowCtx    = TAF_APS_GetDsFlowCtxAddr();

    /* 获取APDSFLOW配置参数 */
    stRptCfg.ulRptEnabled    = pstDsFlowCtx->ulFluxThresRptFlg;
    stRptCfg.ulFluxThreshold = pstDsFlowCtx->ulFluxThresKByte;

    TAF_APS_SndGetApDsFlowRptCfgCnf(&(pstGetRptCfgReq->stCtrl),
                                    TAF_PS_CAUSE_SUCCESS,
                                    &stRptCfg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSetDsFlowNvWriteCfgReq_PreProc
 功能描述  : 消息ID_MSG_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ预处理函数
 输入参数  : ulEventType --- 事件名
             pstMsg      --- 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE    --- 消息处理完毕
             VOS_FALSE   --- 消息未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月12日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSetDsFlowNvWriteCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU    *pstSetNvWriteCfgReq = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU              *pstDsFlowCtx        = VOS_NULL_PTR;

    pstSetNvWriteCfgReq = (TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    pstDsFlowCtx        = TAF_APS_GetDsFlowCtxAddr();

    /* 开启流量写NV功能 */
    if (VOS_TRUE == pstSetNvWriteCfgReq->stNvWriteCfg.ucEnabled)
    {
        /* 流量写NV功能已开启, 根据当前流量写NV功能是否开启做不同处理 */
        if (VOS_TRUE == pstDsFlowCtx->ucDsFlowSave2NvFlg)
        {
            /* 如果流量写NV周期变化, 刷新当前流量到NV, 重启定时器 */
            if (pstDsFlowCtx->ucDsFlowSavePeriod != pstSetNvWriteCfgReq->stNvWriteCfg.ucInterval)
            {
                pstDsFlowCtx->ucDsFlowSavePeriod = pstSetNvWriteCfgReq->stNvWriteCfg.ucInterval;

                TAF_APS_SaveDsFlowInfoToNv();

                TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                                  TAF_APS_INVALID_PDPID);

                TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                                   (pstDsFlowCtx->ucDsFlowSavePeriod * 60 * TIMER_S_TO_MS_1000),
                                   TAF_APS_INVALID_PDPID);
            }
        }
        /* 流量写NV功能未开启, 使能流量写NV功能, 启动定时器 */
        else
        {
            pstDsFlowCtx->ucDsFlowSave2NvFlg = VOS_TRUE;
            pstDsFlowCtx->ucDsFlowSavePeriod = pstSetNvWriteCfgReq->stNvWriteCfg.ucInterval;

            TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                               (pstDsFlowCtx->ucDsFlowSavePeriod * 60 * TIMER_S_TO_MS_1000),
                               TAF_APS_INVALID_PDPID);
        }
    }
    /* 关闭流量写NV功能 */
    else
    {
        /* 流量写NV功能已开启, 刷新当前流量到NV, 停止定时器 */
        if (VOS_TRUE == pstDsFlowCtx->ucDsFlowSave2NvFlg)
        {
            pstDsFlowCtx->ucDsFlowSave2NvFlg = VOS_FALSE;
            pstDsFlowCtx->ucDsFlowSavePeriod = pstSetNvWriteCfgReq->stNvWriteCfg.ucInterval;

            TAF_APS_SaveDsFlowInfoToNv();

            TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                              TAF_APS_INVALID_PDPID);
        }
    }

    TAF_APS_SndSetDsFlowNvWriteCfgCnf(&(pstSetNvWriteCfgReq->stCtrl),
                                      TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvGetDsFlowNvWriteCfgReq_PreProc
 功能描述  : 消息ID_MSG_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ预处理函数
 输入参数  : ulEventType --- 事件名
             pstMsg      --- 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE    --- 消息处理完毕
             VOS_FALSE   --- 消息未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月12日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvGetDsFlowNvWriteCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU    *pstGetNvWriteCfgReq = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU              *pstDsFlowCtx        = VOS_NULL_PTR;
    TAF_DSFLOW_NV_WRITE_CFG_STRU                stNvWriteCfg;

    pstGetNvWriteCfgReq = (TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    pstDsFlowCtx        = TAF_APS_GetDsFlowCtxAddr();

    /* 获取DSFLOW写NV配置参数 */
    PS_MEM_SET(&stNvWriteCfg, 0x00, sizeof(TAF_DSFLOW_NV_WRITE_CFG_STRU));
    stNvWriteCfg.ucEnabled  = pstDsFlowCtx->ucDsFlowSave2NvFlg;
    stNvWriteCfg.ucInterval = pstDsFlowCtx->ucDsFlowSavePeriod;

    TAF_APS_SndGetDsFlowNvWriteCfgCnf(&(pstGetNvWriteCfgReq->stCtrl),
                                      TAF_PS_CAUSE_SUCCESS,
                                      &stNvWriteCfg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiDsFlowReportExpired_PreProc
 功能描述  : 处理流量上报定时器超时消息
 输入参数  : ulEventType - 事件名
             pstMsg      - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 消息处理结束
             VOS_FALSE - 消息未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月15日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数

  2.日    期   : 2012年11月09日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目增加OM流量上报

  3.日    期   : 2013年4月7日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整

  4.日    期   : 2015年2月2日
    作    者   : A00165503
    修改内容   : DTS2015021010050: 增加流量阈值上报处理

  5.日    期   : 2016年01月21日
    作    者   : w00316404
    修改内容   : DTS2016012006718: add cds state report for nonlte
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiDsFlowReportExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsflowCtx = VOS_NULL_PTR;
    TAF_CTRL_STRU                       stCtrl;
    TAF_DSFLOW_REPORT_STRU              stTotalDsFlowRptInfo;

    PS_MEM_SET(&stCtrl, 0x00, sizeof(TAF_CTRL_STRU));

    /* 获取DSFLOW上下文 */
    pstApsDsflowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* 如果当前无PDP激活，返回 */
    if (VOS_FALSE == TAF_APS_CheckIfActiveRabIdExist())
    {
        return VOS_TRUE;
    }

    /* 初始化流量查询信息变量 */
    PS_MEM_SET(&stTotalDsFlowRptInfo, 0, sizeof(TAF_DSFLOW_REPORT_STRU));

    /* 查询所有激活RAB承载的上报流量信息 */
    TAF_APS_QryAllRabDsFlowReportInfo(&stTotalDsFlowRptInfo);

    pstApsDsflowCtx->ucDsFlowATRptTmrExpCnt = (pstApsDsflowCtx->ucDsFlowATRptTmrExpCnt + 1)
                                              % pstApsDsflowCtx->ucDsFlowATRptPeriod;

    if (0 == pstApsDsflowCtx->ucDsFlowATRptTmrExpCnt)
    {
        /* 给AT上报流量信息 */
        stCtrl.ulModuleId    = WUEPS_PID_AT;
        stCtrl.usClientId    = MN_CLIENT_ID_BROADCAST;
        stCtrl.ucOpId        = 0;

        TAF_APS_SndDsFlowRptInd(&stCtrl, TAF_ERR_NO_ERROR, &stTotalDsFlowRptInfo);
    }

    if (VOS_TRUE == pstApsDsflowCtx->ucDsFlowOMReportFlg)
    {
        if (0 == pstApsDsflowCtx->ucDsFlowOMRptTmrExpCnt)
        {
            /* 给OM上报流量信息 */
            TAF_APS_SndDsFlowOMRptInd(&stTotalDsFlowRptInfo);
        }

        pstApsDsflowCtx->ucDsFlowOMRptTmrExpCnt = (pstApsDsflowCtx->ucDsFlowOMRptTmrExpCnt + 1)
                                                  % pstApsDsflowCtx->ucDsFlowOMRptPeriod;
    }

    /* 流量阈值上报处理 */
    TAF_APS_ProcApDsFlowRpt();

    /* 保存当前流量信息到流量统计上下文全局变量，方便下次定时器超时计算速率 */
    TAF_APS_UpdateAllRabCurrentFlowInfo();

    /* APS统计的流量是MB为单位的，故需要转换为Mb处理 */
    TAF_APS_SwitchDdrRateByCurrentRate((stTotalDsFlowRptInfo.ulCurrentReceiveRate * 8),
                                       (stTotalDsFlowRptInfo.ulCurrentSendRate * 8));

    CDS_APS_CdsOmReport();

    /* 启动流量上报定时器*/
    TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_REPORT,
                       TI_TAF_APS_DSFLOW_REPORT_LEN,
                       TAF_APS_INVALID_PDPID);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiDsFlowReportExpired_PreProc
 功能描述  : 处理保存流量到NV定时器超时消息
 输入参数  : ulEventType - 事件名
             pstMsg      - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 消息处理结束
             VOS_FALSE - 消息未处理
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
  3.日    期   : 2012年5月30日
    作    者   : zhangyizhan 60575
    修改内容   : DTS2012052907939, 保存到NV的时间由NV 9036配置
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiDsFlowWriteNvExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsflowCtx;

    /* 初始化 */
    pstApsDsflowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* 保存历史流量到NV使能，将历史流量信息保存到NV中 */
    TAF_APS_SaveDsFlowInfoToNv();

    /* 判断保存历史流量到NV是否使能 */
    if (VOS_TRUE == pstApsDsflowCtx->ucDsFlowSave2NvFlg)
    {
        /* 重新启动定时器 */
        TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                           (pstApsDsflowCtx->ucDsFlowSavePeriod * 60 * TIMER_S_TO_MS_1000),
                           TAF_APS_INVALID_PDPID);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetPrimPdpCtxInfoReq_PreProc
 功能描述  : 查询主PDP上下文预处理函数
             (ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetPrimPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 去消息头, 调用原处理函数处理并回复AT */
    (VOS_VOID)MN_APS_RcvGetPrimPdpCtxInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetPdpInfoReq_PreProc
 功能描述  : 查询主从PDP上下文预处理函数
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月5日
    作    者   : c00173809
    修改内容   : DTS2012010604900
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetPdpInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                            *pstPsMsg;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulPdpCtxInfoLen;
    VOS_UINT32                                  ulCidNum;
    TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU       *pstGetPdpCtxInfoReq;
    TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU       *pstGetPdpCtxInfoCnf;

    /* 初始化消息 */
    pstPsMsg            = (TAF_PS_MSG_STRU*)pstMsg;

    ulPdpCtxInfoLen     = 0;
    ulCidNum            = 0;
    pstGetPdpCtxInfoReq = (TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU*)pstPsMsg->aucContent;
    pstGetPdpCtxInfoCnf = VOS_NULL_PTR;

    /* 计算事件内容长度 */
    ulPdpCtxInfoLen     = sizeof(TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU);

    /* 申请内存 */
    pstGetPdpCtxInfoCnf = (TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                WUEPS_PID_TAF,
                                ulPdpCtxInfoLen);

    /* 申请消息失败 */
    if ( VOS_NULL_PTR == pstGetPdpCtxInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetPdpCtxInfoReq:  ERROR : PS_MEM_ALLOC Error!");
        return VOS_TRUE;
    }

    /* 填写事件内容 */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        /*该PDP没有定义*/
        if (TAF_FREE == g_TafCidTab[ucIndex].ucUsed)
        {
            continue;
        }

        /* 不区分主从PDP,只要是定义的就返回 */
        pstGetPdpCtxInfoCnf->ulCid[ulCidNum]    = ucIndex;
        ulCidNum++;
    }

    /* 填写事件控制头 */
    pstGetPdpCtxInfoCnf->stCtrl     = pstGetPdpCtxInfoReq->stCtrl;
    pstGetPdpCtxInfoCnf->ulCidNum   = ulCidNum;
    pstGetPdpCtxInfoCnf->enCause    = TAF_PS_CAUSE_SUCCESS;

    /* 返回处理结果 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_PDP_CONTEXT_INFO_CNF,
                    pstGetPdpCtxInfoCnf,
                    ulPdpCtxInfoLen);

    /* 释放用于存放PDP上下文参数的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetPdpCtxInfoCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetSecPdpCtxInfoReq_PreProc
 功能描述  : 查询从PDP上下文预处理函数
             (ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetSecPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvGetSecPdpCtxInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetTftInfoReq_PreProc
 功能描述  : 查询TFT参数预处理函数
             (ID_MSG_TAF_PS_GET_PDP_TFT_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetTftInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 去消息头, 调用原处理函数处理并回复AT */
    (VOS_VOID)MN_APS_RcvGetTftInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetPdpIpAddrInfoReq_PreProc
 功能描述  : 查询已激活承载的IP地址设置命令预处理函数
             (ID_MSG_TAF_PS_GET_PDP_IP_ADDR_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetPdpIpAddrInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 去消息头, 调用原处理函数处理并回复AT */
    (VOS_VOID)MN_APS_RcvGetPdpIpAddrInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetAnsModeInfoReq_PreProc
 功能描述  : 查询PS域的自动应答状态预处理函数
             (ID_MSG_TAF_PS_GET_ANSWER_MODE_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetAnsModeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvGetAnsModeInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetPdpContextStateReq_PreProc
 功能描述  : 查询当前PDP的激活状态

 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月06日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetPdpContextStateReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 去消息头, 调用原处理函数处理并回复AT */
    (VOS_VOID)MN_APS_RcvGetPdpCtxStateReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}




#if ( FEATURE_ON == FEATURE_LTE )

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetDynamicPrimPdpCtxInfoReq_PreProc
 功能描述  : 读取主PDP上下文动态参数预处理函数
             (ID_MSG_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetDynamicPrimPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 发送消息给L4A */
    TAF_APS_SndL4aSetCgcontrdpReq(pstPsMsg->aucContent);

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* 启动L4A消息回复保护定时器 */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* 添加消息进等待队列 */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetDynamicSecPdpCtxInfoReq_PreProc
 功能描述  : 读取从PDP上下文动态参数预处理函数
             (ID_MSG_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetDynamicSecPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 发送消息给L4A */
    TAF_APS_SndL4aSetCgscontrdpReq(pstPsMsg->aucContent);

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* 启动L4A消息回复保护定时器 */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* 添加消息进等待队列 */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetDynamicTftInfoReq_PreProc
 功能描述  : 读取TFT的动态参数预处理函数
             (ID_MSG_TAF_PS_GET_DYNAMIC_TFT_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetDynamicTftInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 发送消息给L4A */
    TAF_APS_SndL4aSetCgtftrdpReq(pstPsMsg->aucContent);

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
    /* 启动L4A消息回复保护定时器 */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* 添加消息进等待队列 */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetEpsQosInfoReq_PreProc
 功能描述  : 查询EPS服务质量预处理函数
             (ID_MSG_TAF_PS_GET_EPS_QOS_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetEpsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulErrCode;
    VOS_UINT32                          ulEqosInfoLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_MSG_STRU                    *pstPsMsg;
    TAF_PS_GET_EPS_QOS_INFO_REQ_STRU   *pstGetEqosInfoReq;
    TAF_PS_GET_EPS_QOS_INFO_CNF_STRU   *pstGetEqosInfoCnf;

    /* 初始化消息 */
    pstPsMsg                = (TAF_PS_MSG_STRU*)pstMsg;
    ulErrCode               = TAF_PARA_OK;
    ulEqosInfoLen           = 0;
    ulCidNum                = 0;
    pstGetEqosInfoReq       = (TAF_PS_GET_EPS_QOS_INFO_REQ_STRU*)pstPsMsg->aucContent;
    pstGetEqosInfoCnf       = VOS_NULL_PTR;

    /* 计算事件内容长度 */
    ulEqosInfoLen     = sizeof(TAF_PS_GET_EPS_QOS_INFO_CNF_STRU)
                            + ((TAF_MAX_CID + 1) * sizeof(TAF_EPS_QOS_EXT_STRU));

    /* 申请内存 */
    pstGetEqosInfoCnf = (TAF_PS_GET_EPS_QOS_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                WUEPS_PID_TAF,
                                ulEqosInfoLen);

    /* 申请消息失败 */
    if ( VOS_NULL_PTR == pstGetEqosInfoCnf )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvAtGetEpsQosInfoReq_PreProc:  ERROR : PS_MEM_ALLOC Error!");
        return VOS_TRUE;
    }

    /* 填写事件内容 */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetEqosInfoCnf->astEpsQosInfo[ulCidNum]),
                   0x00,
                   sizeof(TAF_EPS_QOS_EXT_STRU));

        /* 获取EPS QOS信息 */
        TAF_APS_QueEpsQosInfo(ucIndex, &(pstGetEqosInfoCnf->astEpsQosInfo[ulCidNum]), &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* 填写事件控制头 */
    pstGetEqosInfoCnf->stCtrl           = pstGetEqosInfoReq->stCtrl;
    pstGetEqosInfoCnf->ulCidNum         = ulCidNum;
    pstGetEqosInfoCnf->enCause          = TAF_PS_CAUSE_SUCCESS;

    /* 返回处理结果 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_EPS_QOS_INFO_CNF,
                     pstGetEqosInfoCnf,
                     ulEqosInfoLen);

    /* 释放用于存放PDP上下文参数的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetEqosInfoCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetDynamicEpsQosInfoReq_PreProc
 功能描述  : 查询EPS服务质量动态参数预处理函数
             (ID_MSG_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetDynamicEpsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 发送消息给L4A */
    TAF_APS_SndL4aSetCgeqosrdpReq(pstPsMsg->aucContent);

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
    /* 启动L4A消息回复保护定时器 */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* 添加消息进等待队列 */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetLteCsInfoReq_PreProc
 功能描述  :
             (ID_MSG_TAF_PS_GET_LTE_CS_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月24日
    作    者   : h00135900
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetLteCsInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_PS_MSG_STRU                 *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* 发送消息给L4A */
    TAF_APS_SndL4aGetLteCsReq(pstPsMsg->aucContent);

    /* 启动L4A消息回复保护定时器 */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* 添加消息进等待队列 */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                                     (VOS_UINT32*)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_LTECS_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aGetLteCsCnf_PreProc
 功能描述  :
             (ID_L4A_APS_GET_LTE_CS_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月24日
    作    者   : h00135900
    修改内容   : 新生成函数
  2.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，从缓冲队列中获取消息

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aGetLteCsCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_GET_LTE_CS_CNF_STRU        *pstPsMsg = VOS_NULL_PTR;
    TAF_PS_LTECS_CNF_STRU              *pstApsAtLteCsInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulPara;

    /* 初始化消息 */
    pstPsMsg = (APS_L4A_GET_LTE_CS_CNF_STRU*)pstMsg;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* 判断保护定时器是否已超时 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                                                              ulPara))
    {
        /* 保护定时器没有超时, 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_GET_LTE_CS_CNF, ulPara);

        /* 返回AT处理结果 */
        pstApsAtLteCsInfo =  (TAF_PS_LTECS_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_PS_LTECS_CNF_STRU));

        if ( VOS_NULL_PTR == pstApsAtLteCsInfo )
        {
            /* 系统异常打印, 直接返回 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aGetLteCsCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        PS_MEM_SET(pstApsAtLteCsInfo, 0x00,  sizeof( TAF_PS_LTECS_CNF_STRU));

        /* L4A错误参数转换 */
        pstApsAtLteCsInfo->enCause = TAF_APS_TransL4aErrorCode(pstPsMsg->ulErrorCode);

        /* 从缓冲队列中获取消息 */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstApsAtLteCsInfo->stCtrl,
                                                              TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                                                              ulPara))
        {
            /* 消息获取失败, 打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aGetLteCsCnf_PreProc: Get message info failed!");

            /* 释放内存 */
            PS_MEM_FREE(WUEPS_PID_TAF, pstApsAtLteCsInfo);

            return VOS_TRUE;
        }

        if(pstApsAtLteCsInfo->enCause == TAF_PS_CAUSE_SUCCESS )
        {
            pstApsAtLteCsInfo->stLteCs.ucSG     = pstPsMsg->ucSmsOverSGs;
            pstApsAtLteCsInfo->stLteCs.ucIMS    = pstPsMsg->ucSmsOverIMS;
            pstApsAtLteCsInfo->stLteCs.ucCSFB   = pstPsMsg->ucCSFB;
            pstApsAtLteCsInfo->stLteCs.ucVCC    = pstPsMsg->ucSrVcc;
            pstApsAtLteCsInfo->stLteCs.ucVoLGA  = pstPsMsg->ucVoLGA;
        }

        /* 将消息返回 */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_LTECS_INFO_CNF,
                         pstApsAtLteCsInfo,
                         sizeof(TAF_PS_LTECS_CNF_STRU));

        /* 释放内存 */
        PS_MEM_FREE(WUEPS_PID_TAF, pstApsAtLteCsInfo);

        /* 从消息等待队列中删除该消息 */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_LTE_CS_CNF, ulPara);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetCemodeInfoReq_PreProc
 功能描述  :
             (ID_MSG_TAF_PS_GET_CEMODE_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
   1.日    期   : 2012年03月20日
    作    者   : w00182550
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetCemodeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* 发送消息给L4A */
    TAF_APS_SndL4aGetCemodeReq(pstPsMsg->aucContent);

    /* 启动L4A消息回复保护定时器 */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* 添加消息进等待队列 */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                                     (VOS_UINT32*)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_CEMODE_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aGetCemodeCnf_PreProc
 功能描述  :
             (ID_L4A_APS_GET_CEMODE_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年03月20日
    作    者   : w00182550
    修改内容   : 新生成函数
  2.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，从缓冲队列中获取消息
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aGetCemodeCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_GET_CEMODE_CNF_STRU        *pstPsMsg;
    TAF_PS_CEMODE_CNF_STRU             *pstApsAtCemodeInfo = NULL;
    VOS_UINT32                          i;
    VOS_UINT32                          ulPara;

    /* 初始化消息 */
    pstPsMsg                = (APS_L4A_GET_CEMODE_CNF_STRU*)pstMsg;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* 判断保护定时器是否已超时 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                                                              ulPara))
    {
        /* 保护定时器没有超时, 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_GET_CEMODE_CNF, ulPara);

        /* 返回AT处理结果 */
        pstApsAtCemodeInfo =  (TAF_PS_CEMODE_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_PS_CEMODE_CNF_STRU));

        if ( VOS_NULL_PTR == pstApsAtCemodeInfo )
        {
            /* 系统异常打印, 直接返回 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aGetCemodeCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        PS_MEM_SET(pstApsAtCemodeInfo, 0x00,  sizeof( TAF_PS_CEMODE_CNF_STRU));

        /* L4A错误参数转换 */
        pstApsAtCemodeInfo->enCause = TAF_APS_TransL4aErrorCode(pstPsMsg->ulErrorCode);;

        /* 从缓冲队列中获取消息 */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstApsAtCemodeInfo->stCtrl,
                                                              TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                                                              ulPara))
        {
            /* 消息获取失败, 打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aGetCemodeCnf_PreProc: Get message info failed!");

            /* 释放内存 */
            PS_MEM_FREE(WUEPS_PID_TAF, pstApsAtCemodeInfo);

            return VOS_TRUE;
        }

        if (pstApsAtCemodeInfo->enCause == TAF_PS_CAUSE_SUCCESS )
        {
            pstApsAtCemodeInfo->stCemode.enCurrentUeMode    = pstPsMsg->ulCurrentUeMode;
            pstApsAtCemodeInfo->stCemode.ulSupportModeCnt   = pstPsMsg->ulSupportModeCnt;

            for (i = 0; i < 4; i++)
            {
                pstApsAtCemodeInfo->stCemode.aenSupportModeList[i] = pstPsMsg->aulSupportModeList[i];
            }
        }

            /* 将消息返回AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CEMODE_INFO_CNF,
                         pstApsAtCemodeInfo,
                         sizeof( TAF_PS_CEMODE_CNF_STRU));

        /* 释放内存 */
        PS_MEM_FREE(WUEPS_PID_TAF, pstApsAtCemodeInfo);

        /* 从消息等待队列中删除该消息 */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_CEMODE_CNF, ulPara);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdprofInfoReq_PreProc
 功能描述  : 设置APN, 用户名和密码鉴权信息预处理函数
             (ID_MSG_TAF_PS_SET_PDPROFMOD_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月12日
    作    者   : x00126983
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdprofInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
    /* 发送消息给L4A */
    TAF_APS_SndL4aSetPdprofReq(pstPsMsg->aucContent);

    /* 启动L4A消息回复保护定时器 */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_PDPROF_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* 添加消息进等待队列 */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_PDPROF_CNF,
                                     (VOS_UINT32*)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_SET_PROFILE_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aSetPdprofInfoCnf_PreProc
 功能描述  : CNF消息预处理函数
             (ID_L4A_APS_SET_PDPROFMOD_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年03月15日
    作    者   : x00126983
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetPdprofInfoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_PDPROFMOD_CNF_STRU     *pstPsMsg;
    TAF_CTRL_STRU                       stCtrl = {0};
    VOS_UINT32                          ulErrCode;
    TAF_APS_CMD_BUFFER_STRU            *pstMsgInfo;
    TAF_PS_SET_PROFILE_INFO_REQ_STRU   *pstSetPdprofInfoReq;
    VOS_UINT32                          ulPara;

    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    /* 初始化消息 */
    pstPsMsg                = (APS_L4A_SET_PDPROFMOD_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetPdprofInfoReq     = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* 判断保护定时器是否已超时 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_PDPROF_CNF,
                                                              ulPara))
    {
        /* 保护定时器没有超时, 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_PDPROF_CNF, ulPara);

        /* L4A错误参数转换 */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* 从缓冲队列中获取消息 */
        pstMsgInfo  = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_PDPROF_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* 消息获取失败, 打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetPdprofInfoCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* 消息获取成功, 更新APS本地全局变量, 写NV操作 */
        pstSetPdprofInfoReq = (TAF_PS_SET_PROFILE_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;

        stCtrl = pstSetPdprofInfoReq->stCtrl;

        /* 如果L4A全局变量更新成功, 更新APS本地全局变量, 写NV操作 */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* 设置Primary PDP上下文和AUTHDATA参数(NDIS)  */
            Aps_DefPsPdprofmod(pstSetPdprofInfoReq->stCtrl.usClientId,
                               pstSetPdprofInfoReq->stCtrl.ucOpId,
                               &(pstSetPdprofInfoReq->stPdpProfInfo),
                               &ulErrCode);
        }

        /* 从消息等待队列中删除该消息 */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_PDPROF_CNF, ulPara);

        /* 返回AT处理结果 */
        TAF_APS_SndSetPdprofInfoCnf(&stCtrl, ulErrCode);
    }
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    return VOS_TRUE;
}

/* Add by w00199382 for V7代码同步, 2012-04-07, End   */

#endif

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetAuthDataInfoReq_PreProc
 功能描述  : 查询用户名和密码鉴权信息预处理函数
             (ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetAuthDataInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvGetAuthDataInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetUmtsQosInfoReq_PreProc
 功能描述  : 查询PDP上下文的Qos参数的预处理函数
             (ID_MSG_TAF_PS_GET_UMTS_QOS_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetUmtsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvGetUmtsQosInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetUmtsQosMinInfoReq_PreProc
 功能描述  : 查询PDP上下文的最小可接受服务质量预处理函数
             (ID_MSG_TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetUmtsQosMinInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvGetUmtsQosMinInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetDynamicUmtsQosInfoReq_PreProc
 功能描述  : 查询PDP上下文激活后经过与网络协商后而实际使用的QoS预处理函数
             (ID_MSG_TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetDynamicUmtsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvGetDynamicUmtsQosInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetPdpDnsInfoReq_PreProc
 功能描述  : 查询PDP上下文使用的DNS信息预处理函数
             (ID_MSG_TAF_PS_GET_PDP_DNS_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetPdpDnsInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 去消息头, 调用原处理函数处理并回复AT */
    (VOS_VOID)MN_APS_RcvGetPdpDnsInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPrimPdpCtxInfoReq_PreProc
 功能描述  : 设置主PDP上下文预处理函数
             (ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目接口修改(添加系统能力判断)
  3.日    期   : 2014年02月14日
    作    者   : m00217266
    修改内容   : L-C互操作项目(添加请求有效性判断)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPrimPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                             *pstPsMsg;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU   *pstSetPdpCtxInfoReq;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* 初始化消息 */
    pstPsMsg            = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxInfoReq = (TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU *)pstPsMsg->aucContent;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* Added by m00217266 for L-C互操作项目, 2014-1-24, begin */
    /* L-C互操作模式，对请求消息有效性做判断 */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstSetPdpCtxInfoReq->stCtrl)))
    {
        TAF_APS_SndSetPrimPdpCtxInfoCnf(&(pstSetPdpCtxInfoReq->stCtrl), TAF_PARA_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }
    /* Added by m00217266 for L-C互操作项目, 2014-1-24, end */
#endif
#if ( FEATURE_ON == FEATURE_LTE )
    /* 根据LTE能力分别执行 */
    /* 目前ESM不支持PPP类型的拨号 */
    if ((VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
     && (TAF_PDP_PPP != pstSetPdpCtxInfoReq->stPdpContextInfo.enPdpType))
    {
        /* 发送消息给L4A */
        TAF_APS_SndL4aSetCgdcontReq(pstSetPdpCtxInfoReq);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstSetPdpCtxInfoReq),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstSetPdpCtxInfoReq));

        /* 启动L4A消息回复保护定时器 */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGDCONT_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* 添加消息进等待队列 */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDCONT_CNF,
                                         (VOS_UINT32*)pstSetPdpCtxInfoReq,
                                         sizeof(TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU),
                                         ulPara);

       return VOS_TRUE;
    }

#endif

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvSetPrimPdpCtxInfoReq(pstSetPdpCtxInfoReq);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetSecPdpCtxInfoReq_PreProc
 功能描述  : 设置从PDP上下文预处理函数
             (ID_MSG_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目接口修改(添加系统能力判断)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetSecPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

#if ( FEATURE_ON == FEATURE_LTE )
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        /* 发送消息给L4A */
        TAF_APS_SndL4aSetCgdscontReq(pstPsMsg->aucContent);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
        /* 启动L4A消息回复保护定时器 */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* 添加消息进等待队列 */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF,
                                         (VOS_UINT32*)pstPsMsg->aucContent,
                                         sizeof(TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU),
                                         ulPara);

	    return VOS_TRUE;
    }
#endif

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvSetSecPdpCtxInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetTftInfoReq_PreProc
 功能描述  : 设置TFT参数预处理函数
             (ID_MSG_TAF_PS_SET_TFT_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目接口修改(添加系统能力判断)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetTftInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
#if ( FEATURE_ON == FEATURE_LTE )
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        /* 发送消息给L4A */
        TAF_APS_SndL4aSetCgtftReq(pstPsMsg->aucContent);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

        /* 启动L4A消息回复保护定时器 */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGTFT_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* 添加消息进等待队列 */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFT_CNF,
                                         (VOS_UINT32*)pstPsMsg->aucContent,
                                         sizeof(TAF_PS_SET_TFT_INFO_REQ_STRU),
                                         ulPara);

        return VOS_TRUE;
    }

#endif

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvSetTftInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetAnsModeInfoReq_PreProc
 功能描述  : PS域的自动应答状态设置预处理函数
             (ID_MSG_TAF_PS_SET_ANSWER_MODE_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目接口修改(添加系统能力判断)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetAnsModeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

#if ( FEATURE_ON == FEATURE_LTE )
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        /* 发送消息给L4A */
        TAF_APS_SndL4aSetCgautoReq(pstPsMsg->aucContent);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
        /* 启动L4A消息回复保护定时器 */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGAUTO_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* 添加消息进等待队列 */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGAUTO_CNF,
                                         (VOS_UINT32*)pstPsMsg->aucContent,
                                         sizeof(TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU),
                                         ulPara);

        return VOS_TRUE;
    }
#endif

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvSetAnsModeInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetAuthDataInfoReq_PreProc
 功能描述  : 设置用户名和密码鉴权信息预处理函数
             (ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2012年12月26日
    作    者   : m00217266
    修改内容   : DSDA C核项目接口修改(添加系统能力判断)
  3.日    期   : 2014年02月14日
    作    者   : m00217266
    修改内容   : L-C互操作项目(添加请求有效性判断)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetAuthDataInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                     *pstPsMsg;
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU   *pstAuthdata;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstAuthdata     = (TAF_PS_SET_AUTHDATA_INFO_REQ_STRU *)pstPsMsg->aucContent;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* Added by m00217266 for L-C互操作项目, 2014-1-24, begin */
    /* L-C互操作模式，对请求消息有效性做判断 */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstAuthdata->stCtrl)))
    {
        (VOS_VOID)TAF_APS_SndSetAuthDataInfoCnf(&(pstAuthdata->stCtrl), TAF_PARA_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }
    /* Added by m00217266 for L-C互操作项目, 2014-1-24, end */
#endif

#if ( FEATURE_ON == FEATURE_LTE )
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        /* 发送消息给L4A */
        TAF_APS_SndL4aSetAuthdataReq(pstAuthdata);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstAuthdata),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstAuthdata));

        /* 启动L4A消息回复保护定时器 */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* 添加消息进等待队列 */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF,
                                         (VOS_UINT32*)pstAuthdata,
                                         sizeof(TAF_PS_SET_AUTHDATA_INFO_REQ_STRU),
                                         ulPara);

        return VOS_TRUE;
    }
#endif

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvSetAuthDataInfoReq(pstAuthdata);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetUmtsQosInfoReq_PreProc
 功能描述  : 设置PDP上下文的Qos参数的预处理函数
             (ID_MSG_TAF_PS_SET_UMTS_QOS_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2014年02月14日
    作    者   : m00217266
    修改内容   : L-C互操作项目(添加请求有效性判断)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetUmtsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                     *pstPsMsg;
    TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU   *pstSetQosReq;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetQosReq    = (TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU *)pstPsMsg->aucContent;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* Added by m00217266 for L-C互操作项目, 2014-1-24, begin */
    /* L-C互操作模式，对请求消息有效性做判断 */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstSetQosReq->stCtrl)))
    {
        TAF_APS_SndSetUmtsQosInfoCnf(&(pstSetQosReq->stCtrl), TAF_PARA_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }
    /* Added by m00217266 for L-C互操作项目, 2014-1-24, end */
#endif

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvSetUmtsQosInfoReq(pstSetQosReq);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetUmtsQosMinInfoReq_PreProc
 功能描述  : 设置PDP上下文的最小可接受服务质量预处理函数
             (ID_MSG_TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2014年02月14日
    作    者   : m00217266
    修改内容   : L-C互操作项目(添加请求有效性判断)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetUmtsQosMinInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                         *pstPsMsg;
    TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU   *pstSetQosMinReq;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetQosMinReq = (TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU *)pstPsMsg->aucContent;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* Added by m00217266 for L-C互操作项目, 2014-1-24, begin */
    /* L-C互操作模式，对请求消息有效性做判断 */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstSetQosMinReq->stCtrl)))
    {
        TAF_APS_SndSetUmtsQosMinInfoCnf(&(pstSetQosMinReq->stCtrl), TAF_PARA_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }
    /* Added by m00217266 for L-C互操作项目, 2014-1-24, end */
#endif

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvSetUmtsQosMinInfoReq(pstSetQosMinReq);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpDnsInfoReq_PreProc
 功能描述  : 设置PDP上下文使用的DNS信息预处理函数
             (ID_MSG_TAF_PS_SET_PDP_DNS_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpDnsInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 去消息头, 调用原处理函数处理并回复AT */
    (VOS_VOID)MN_APS_RcvSetPdpDnsInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtTrigGprsDataReq_PreProc
 功能描述  : 消息预处理函数
             (ID_MSG_TAF_PS_TRIG_GPRS_DATA_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtTrigGprsDataReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_TRIG_GPRS_DATA_REQ_STRU     *pstTrigReq = VOS_NULL_PTR;

    pstTrigReq  = (TAF_PS_TRIG_GPRS_DATA_REQ_STRU*)TAF_PS_GET_MSG_CONTENT(pstMsg);

    TAF_APS_GprsDataReq(pstTrigReq->stGprsDataInfo.ucMode,
                        pstTrigReq->stGprsDataInfo.ucNsapi,
                        pstTrigReq->stGprsDataInfo.ulLength,
                        pstTrigReq->stGprsDataInfo.ucTimes,
                        pstTrigReq->stGprsDataInfo.ulMillisecond);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtConfigNbnsFunctionReq_PreProc
 功能描述  : 消息预处理函数
             (ID_MSG_TAF_PS_CONFIG_NBNS_FUNCTION_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtConfigNbnsFunctionReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* 去消息头, 调用原处理函数处理并回复AT */
    MN_APS_RcvConfigNbnsFunctionReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvFindCidForDialReq_PreProc
 功能描述  : 查询CID请求。
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : c00173809
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtFindCidForDialReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU  *pCnf;
    VOS_UINT8                                 ucCid;

    pCnf = (TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                                   sizeof(TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    /* 需找可用于拨号的CID */
    ucCid = TAF_APS_FindCidForDial(WUEPS_PID_AT);
    if ( TAF_INVALID_CID == ucCid )
    {
        pCnf->ulRet       = VOS_ERR;
    }

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF;
    pCnf->ulRet                         = VOS_OK;
    pCnf->ucCid                         = ucCid;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetCidParaReq_PreProc
 功能描述  : 获取CID的参数
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : c00173809
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetCidParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_GET_CID_PARA_CNF_STRU         *pCnf;
    TAFAGENT_APS_GET_CID_PARA_REQ_STRU         *pMsgReq;
    VOS_UINT32                                  ulResult;

    pCnf = (TAFAGENT_APS_GET_CID_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                              sizeof(TAFAGENT_APS_GET_CID_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    pMsgReq                             = (TAFAGENT_APS_GET_CID_PARA_REQ_STRU*)pstMsg;

    ulResult                            = MN_APS_GetPdpCidPara(&(pCnf->stCidInfo),pMsgReq->ucCid);

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_GET_CID_PARA_CNF;
    pCnf->ulRet                         = (VOS_UINT8)ulResult;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_SetCidParaReq_PreProc
 功能描述  : 设置CID的参数
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : c00173809
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetCidParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_SET_CID_PARA_REQ_STRU                         *pMsgReq;
    TAFAGENT_APS_SET_CID_PARA_CNF_STRU                         *pCnf;
    VOS_UINT32                                                  ulResult;

    pCnf = (TAFAGENT_APS_SET_CID_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                sizeof(TAFAGENT_APS_SET_CID_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    pMsgReq                  = (TAFAGENT_APS_SET_CID_PARA_REQ_STRU*)(pstMsg);
    ulResult                 = MN_APS_SetPdpCidPara((VOS_UINT16)pMsgReq->ulClientID,&(pMsgReq->stPdpPrimContextExt));

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_SET_CID_PARA_CNF;
    pCnf->ulRet                         = (VOS_UINT8)ulResult;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetCidQosParaReq_PreProc
 功能描述  : 获取CID的QOS参数
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月29日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2015年01月20日
    作    者   : z00301431
    修改内容   : DTS2015012000798, 消息申请后未初始化导致min qos配置错误
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetCidQosParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU         *pCnf;
    TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU         *pMsgReq;
    VOS_UINT32                                      ulResult;

    pCnf = (TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                              sizeof(TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_GetCidQosParaReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    PS_MEM_SET((VOS_CHAR*)pCnf + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pMsgReq                             = (TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU*)pstMsg;

    ulResult                            = TAF_APS_GetPdpCidQosPara(&(pCnf->stQosPara), pMsgReq->ucCid);

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_GET_CID_QOS_PARA_CNF;
    pCnf->ulRet                         = (VOS_UINT8)ulResult;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvAtGetCidQosParaReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetCidQosParaReq_PreProc
 功能描述  : 设置CID的Qos参数
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月29日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetCidQosParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU                         *pMsgReq;
    TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU                         *pCnf;
    VOS_UINT32                                                      ulResult;

    pCnf = (TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                sizeof(TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_RcvAtSetCidQosParaReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    pMsgReq                  = (TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU*)(pstMsg);

    ulResult                 = TAF_APS_SetPdpCidQosPara(&(pMsgReq->stQosPara));

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_SET_CID_QOS_PARA_CNF;
    pCnf->ulRet                         = (VOS_UINT8)ulResult;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvAtSetCidQosParaReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_PreProc
 功能描述  : 激活去激活上下文的时候，需要进行预处理，判定当前是否能进入状态机
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
  1.日    期  : 2011年12月22日
    作    者  : h44270
    修改内容  : 新生成函数

  2.日    期   : 2012年4月16日
    作    者   : A00165503
    修改内容   : DTS2012040100697: 自动应答模式下, 网侧建立的ESP承载, 用户不
                 能修改和去激活

  3.日    期   : 2012年11月13日
    作    者   : A00165503
    修改内容   : DTS2012111205973: LTE默认缺省承载IP类型IPv4v6, 用户拨号IP类
                 型IPv4 only或IPv6 only, 缺省承载IP类型被错误的修改为用户拨
                 号IP类型

  4.日    期   : 2014年02月14日
    作    者   : m00217266
    修改内容   : L-C互操作项目(添加请求有效性判断)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq;
    VOS_UINT8                           ucCidValue;
    VOS_UINT32                          ulBearerActivateFlg;
    VOS_UINT32                          ulRslt;

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpStateReq                   = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* Added by m00217266 for L-C互操作项目, 2014-1-24, begin */
    /* L-C互操作模式，对请求消息有效性做判断 */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstSetPdpStateReq->stCtrl)))
    {
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl), TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }
    /* Added by m00217266 for L-C互操作项目, 2014-1-24, end */
#endif

    /* 设置激活标记 */
    ulBearerActivateFlg = (TAF_CGACT_ACT == pstSetPdpStateReq->stCidListStateInfo.ucState) ? VOS_TRUE : VOS_FALSE;

    /*
       当前先不支持一次性激活多个PDP的场景，一次激活一个，因此找第一个要激活的
       CID
    */
    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstSetPdpStateReq->stCidListStateInfo.aucCid);

    /* 如果返回的CID为0，表明是无效CID，直接返回ERROR */
    if (0 == ucCidValue)
    {
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;
    }

    if (ulBearerActivateFlg == VOS_TRUE)
    {
        ulRslt = TAF_APS_ProcActivatePdpContext_PreProc(ucCidValue, pstSetPdpStateReq);
    }
    else
    {
        ulRslt = TAF_APS_ProcDeactivatePdpContext_PreProc(ucCidValue, pstSetPdpStateReq);
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcActivatePdpContext_PreProc
 功能描述  : 预处理状态机中处理PDP激活
 输入参数  :    ucCidValue
                pstSetPdpStateReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月17日
    作    者   : m00217266
    修改内容   : 新生成函数

  2.日    期   : 2014年02月25日
    作    者   : Y00213812
    修改内容   : DTS2014022504539:只支持IMSA与其它端口共用APN

  3.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: 调整承载匹配处理
*****************************************************************************/
VOS_UINT32 TAF_APS_ProcActivatePdpContext_PreProc(
    VOS_UINT8                           ucCidValue,
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq
)
{
    TAF_APS_MATCH_PARAM_STRU            stMatchParam;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucPdpId;
    TAF_PH_MODE                         ucPhMode;

    PS_MEM_SET(&stMatchParam, 0x00, sizeof(TAF_APS_MATCH_PARAM_STRU));

    ucPhMode = MMA_GetCurrPhMode();

    /* 如果系统为开机,则直接返回VOS_TRUE */
    if ( TAF_PH_MODE_FULL != ucPhMode )
    {
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

    /* CID对应的上下文没有定义，则直接返回ERROR */
    if (VOS_FALSE == TAF_APS_GetTafCidInfoUsedFlg(ucCidValue))
    {
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;
    }

    /* 生成匹配参数信息 */
    TAF_APS_GenMatchParamByCidInfo(TAF_APS_GetTafCidInfoAddr(ucCidValue),
                                   &stMatchParam);

#if (FEATURE_ON == FEATURE_LTE)
    /* 找到默认承载的情况下，直接刷新CID  */
    if (VOS_TRUE == TAF_APS_MatchCallWithAttachBearer(
                                &pstSetPdpStateReq->stCtrl,
                                &stMatchParam))
    {
        /* 除了刷新CID，还同时刷新了ClientId和OP ID */
        ucPdpId = TAF_APS_GetPdpIdByDefaultCid();

        /* 清除cid 0 的信息,记录PDP 信息 */
        TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                    ucCidValue,
                                    pstSetPdpStateReq->stCtrl.ulModuleId,
                                    pstSetPdpStateReq->stCtrl.usClientId,
                                    pstSetPdpStateReq->stCtrl.ucOpId);

        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCidValue, TAF_APS_GetTafCidInfoPdpType(ucCidValue));

        /* 通知ESM当前的Cid刷新 */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                SM_ESM_PDP_OPT_MODIFY);

        return VOS_FALSE;
    }
#endif

    /* 获取PdpId，如果获取不到，说明当前是激活一个新的CID */
    ucPdpId = TAF_APS_GetPdpIdByCid(ucCidValue);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* 相同APN
           如果已激活相同APN，PDP类型相容，共用PDP实体
           如果已激活相同APN，PDP类型不同，重新分配PDP实体
           未激活: ACTIVATING,MODIFING,DEACTIVATING
           返回特殊原因值TAF_PS_CAUSE_SAME_APN_OPERATING

           无相同APN，执行原有流程
        */

        /* 激活则分配一个新的PDP ID */
        if (VOS_TRUE == TAF_APS_MatchCallWithAllBearer(
                                    &pstSetPdpStateReq->stCtrl,
                                    &stMatchParam,
                                    &ucPdpId))
        {
            /* 未激活: ACTIVATING,MODIFING,DEACTIVATING
               返回特殊原因值TAF_PS_CAUSE_SAME_APN_OPERATING */
            if (TAF_APS_STA_ACTIVE != TAF_APS_GetPdpIdMainFsmState(ucPdpId))
            {
                TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                             TAF_PS_CAUSE_OPERATION_CONFLICT);
                return VOS_TRUE;
            }
            else
            {
                /* 记录PDP信息 */
                TAF_APS_AddPdpEntClientInfo(ucPdpId,
                                            ucCidValue,
                                            &(pstSetPdpStateReq->stCtrl));

                TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                             ucCidValue,
                                             TAF_APS_GetTafCidInfoPdpType(ucCidValue));
            }
        }
        else
        {
            /* 分配TI(PdP Id) */
            if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&pstSetPdpStateReq->stCtrl,
                                                               ucCidValue,
                                                               &ucPdpId))
            {
                /* 分配不到实体，则直接返回ERROR */
                TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                            TAF_PS_CAUSE_UNKNOWN);
                return VOS_TRUE;
            }
        }
    }
    else
    {
        if (TAF_APS_GetPdpEntClientId(ucPdpId, ucCidValue) != pstSetPdpStateReq->stCtrl.usClientId)
        {
            /* ClientId不匹配, 则直接返回ERROR */
            TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                        TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
    }

    ulRslt = TAF_APS_RcvAtSetPdpContextStateReq_PdpActLimit_PreProc(pstSetPdpStateReq);

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcDeactivatePdpContext_PreProc
 功能描述  : 预处理状态机处理PDP去激活
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月17日
    作    者   : m00217266
    修改内容   : 新生成函数

  2.日    期   : 2013年12月17日
    作    者   : Y00213812
    修改内容   : 增加多用户共用APN的处理
*****************************************************************************/
VOS_UINT32 TAF_APS_ProcDeactivatePdpContext_PreProc(
    VOS_UINT8                           ucCidValue,
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_BITCID_INFO_STRU            stCid;

    PS_MEM_SET(&stCid, 0, sizeof(TAF_APS_BITCID_INFO_STRU));

    /* 获取PdpId，如果获取不到，说明当前是去激活一个新的CID */
    ucPdpId = TAF_APS_GetPdpIdByCid(ucCidValue);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /*
           去激活操作，如果是去激活一个新的CID,说明当前对应的CID还没有激活
           或者尝试激活，直接返回OK
        */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_SUCCESS);

        /* 没有找到匹配的PDP, 则此PDP没有激活, 上报去激活成功事件 */
        TAF_APS_SndCidInactiveEvt(&(pstSetPdpStateReq->stCtrl),
                                  ucCidValue);

        return VOS_TRUE;
    }
    else
    {
        if (TAF_APS_INVALID_CLIENTID == TAF_APS_GetPdpEntClientId(ucPdpId, ucCidValue))
        {
            TAF_APS_SetPdpEntClientId(ucPdpId, ucCidValue, pstSetPdpStateReq->stCtrl.usClientId);
        }
        else if (TAF_APS_GetPdpEntClientId(ucPdpId, ucCidValue) != pstSetPdpStateReq->stCtrl.usClientId)
        {
            /* ClientId不匹配, 则直接返回ERROR */
            TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                         TAF_PS_CAUSE_UNKNOWN);

            return VOS_TRUE;
        }
        else
        {
            /* 检查PDP实体中是否存在多个cid */
            TAF_APS_GetPdpEntBitCidInfo(ucPdpId, &stCid);

            if (stCid.ulNum > 1)
            {
                /* 返回该cid去激活成功 */
                TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                             TAF_PS_CAUSE_SUCCESS);

                TAF_APS_SndPdpDeActivateCnf(ucPdpId, ucCidValue);

                /* 清除PDP实体中该CID信息 */
                TAF_APS_RmvPdpEntClientInfo(ucPdpId, ucCidValue, &stCid);

                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_PreProc
 功能描述  : 收到modify消息的时候，需要进行预处理，判定当前是否能进入状态机
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月22日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年03月05日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012022405416，G下正常驻留，发起PDP MOD REQ,
                 PDP修改完成异系统到W下，PS被BAR，AT无响应

  3.日    期   : 2012年4月16日
    作    者   : A00165503
    修改内容   : DTS2012040100697: 自动应答模式下, 网侧建立的ESP承载, 用户不
                 能修改和去激活
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCidValue;
    VOS_UINT32                          ulBearerActivateFlg;
    TAF_APS_BITCID_INFO_STRU                     stCid;

    PS_MEM_SET(&stCid, 0, sizeof(TAF_APS_BITCID_INFO_STRU));

    /* 当前先不支持一次性Modify多个PDP的场景，一次Modify一个 */
    ulBearerActivateFlg                 = VOS_FALSE;
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstCallModifyReq->stCidListInfo.aucCid);

    /* 如果返回的CID为0，表明是无效CID，直接返回ERROR */
    if ( 0 == ucCidValue )
    {
        /* 上报ERROR */
        TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                                TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;

    }

    /* 获取PdpId，如果获取不到，说明当前没有可以修改的PDP ID */
    ucPdpId = TAF_APS_GetPdpIdByCid(ucCidValue);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* 直接返回ERROR */
        TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                                TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;
    }

    /* 检查PDP实体中是否存在多个cid */
    TAF_APS_GetPdpEntBitCidInfo(ucPdpId, &stCid);
    if (stCid.ulNum > 1)
    {
        /* 存在APN共用时，不允许用户主动MODIFY */
        TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                                 TAF_PS_CAUSE_OPERATION_CONFLICT);
        return VOS_TRUE;
    }

    TAF_APS_SetPdpEntModDialInfo(ucPdpId, &(pstCallModifyReq->stCtrl));

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_PreProc
 功能描述  : 收到激活消息的时候，需要进行预处理，判定当前是否能进入状态机
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月22日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年11月13日
    作    者   : A00165503
    修改内容   : DTS2012111205973: LTE默认缺省承载IP类型IPv4v6, 用户拨号IP类
                 型IPv4 only或IPv6 only, 缺省承载IP类型被错误的修改为用户拨
                 号IP类型

  3.日    期   : 2014年02月25日
    作    者   : Y00213812
    修改内容   : DTS2014022504539:只支持IMSA与其它端口共用APN

  4.日    期   : 2014年02月14日
    作    者   : m00217266
    修改内容   : L-C互操作项目(添加请求有效性判断)

  5.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: 调整承载匹配处理
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    TAF_APS_MATCH_PARAM_STRU            stMatchParam;
    VOS_UINT8                           ucPdpId;
    TAF_PH_MODE                         ucPhMode;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo = VOS_NULL_PTR;
#endif

    PS_MEM_SET(&stMatchParam, 0x00, sizeof(TAF_APS_MATCH_PARAM_STRU));

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPhMode                            = MMA_GetCurrPhMode();
    ucPdpId                             = TAF_APS_INVALID_PDPID;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* Added by m00217266 for L-C互操作项目, 2014-1-24, begin */
    /* L-C互操作模式，对请求消息有效性做判断 */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstCallOrigReq->stCtrl)))
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                      pstCallOrigReq->stDialParaInfo.ucCid,
                      TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }
    /* Added by m00217266 for L-C互操作项目, 2014-1-24, end */
#endif

    /* 如果系统为开机，则直接返回VOS_TRUE */
    if (TAF_PH_MODE_FULL != ucPhMode)
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                              pstCallOrigReq->stDialParaInfo.ucCid,
                              TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    pstSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

    /* CallBack状态，不能进行拨号 */
    if (VOS_TRUE == pstSdc1xSysInfo->ucIsEmcCallExistFlg)
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                              pstCallOrigReq->stDialParaInfo.ucCid,
                              TAF_PS_CAUSE_UNKNOWN);

        return VOS_TRUE;
    }
#endif

    /* 生成匹配参数信息 */
    TAF_APS_GenMatchParamByDailInfo(&pstCallOrigReq->stDialParaInfo,
                                    &stMatchParam);

    /* 找到默认承载的情况下，直接刷新CID  */
    if (VOS_TRUE == TAF_APS_MatchCallWithAttachBearer(
                                &pstCallOrigReq->stCtrl,
                                &stMatchParam))
    {
        /* 除了刷新CID，还同时刷新了ClientId和OP ID */
        ucPdpId = TAF_APS_GetPdpIdByDefaultCid();

        /* 清除CID 0 的信息,记录PDP 信息 */
        TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                    pstCallOrigReq->stDialParaInfo.ucCid,
                                    pstCallOrigReq->stCtrl.ulModuleId,
                                    pstCallOrigReq->stCtrl.usClientId,
                                    pstCallOrigReq->stCtrl.ucOpId);

        TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                     pstCallOrigReq->stDialParaInfo.ucCid,
                                     pstCallOrigReq->stDialParaInfo.enPdpType);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

        /* 通知EHSM当前的Cid刷新 */
        TAF_APS_SndEhsmPdnCtxInfoNotify(ucPdpId, EHSM_APS_PDN_OPTION_MODIFIED);

#endif

#if (FEATURE_ON == FEATURE_LTE)
        /* 通知ESM当前的Cid刷新 */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                SM_ESM_PDP_OPT_MODIFY);
#endif

        return VOS_FALSE;
    }

    /* 获取PdpId，如果获取不到，说明当前是激活或者去激活一个新的CID */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstCallOrigReq->stDialParaInfo.ucCid);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* 相同APN
             如果已激活相同APN，PDP类型相容，共用PDP实体
             如果已激活相同APN，PDP类型不同，重新分配PDP实体
             未激活: ACTIVATING,MODIFING,DEACTIVATING
             返回特殊原因值TAF_PS_CAUSE_SAME_APN_OPERATING

           无相同APN，执行原有流程  */
        if (VOS_TRUE == TAF_APS_MatchCallWithAllBearer(
                                    &pstCallOrigReq->stCtrl,
                                    &stMatchParam,
                                    &ucPdpId))
        {
            /* 未激活: ACTIVATING,MODIFING,DEACTIVATING
               返回特殊原因值TAF_PS_CAUSE_SAME_APN_OPERATING */
            if (TAF_APS_STA_ACTIVE != TAF_APS_GetPdpIdMainFsmState(ucPdpId))
            {
                TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                                       pstCallOrigReq->stDialParaInfo.ucCid,
                                       TAF_PS_CAUSE_OPERATION_CONFLICT);
                return VOS_TRUE;
            }
            else
            {
                /* 记录PDP信息 */
                TAF_APS_AddPdpEntClientInfo(ucPdpId,
                                            pstCallOrigReq->stDialParaInfo.ucCid,
                                            &(pstCallOrigReq->stCtrl));

                TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                             pstCallOrigReq->stDialParaInfo.ucCid,
                                             pstCallOrigReq->stDialParaInfo.enPdpType);
            }
        }
        else
        {
            /* 分配实体 */
            if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&pstCallOrigReq->stCtrl,
                                                               pstCallOrigReq->stDialParaInfo.ucCid,
                                                               &ucPdpId))
            {
                /* 分配不到实体，则直接返回ERROR */
                TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                                      pstCallOrigReq->stDialParaInfo.ucCid,
                                      TAF_PS_CAUSE_UNKNOWN);
                return VOS_TRUE;
            }
        }
    }
    else
    {
        if (TAF_APS_GetPdpEntClientId(ucPdpId, pstCallOrigReq->stDialParaInfo.ucCid) != pstCallOrigReq->stCtrl.usClientId)
        {
            /* ClientId不匹配, 则直接返回ERROR */
            TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                                  pstCallOrigReq->stDialParaInfo.ucCid,
                                  TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
    }

    if (VOS_TRUE == TAF_APS_IsPdpActLimit_PreProc())
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                              pstCallOrigReq->stDialParaInfo.ucCid,
                              TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_IsStaNwActivatingSubStaWaitAppAnswer
 功能描述  : 判断当前处于网络激活等待应用发起应答状态
 输出参数  : TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月7日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_IsStaNwActivatingSubStaWaitAppAnswer(
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq
)
{
    VOS_UINT8                           ucPdpId;

    /* 根据CID获取PDP ID */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstPppDialOrigReq->stPppDialParaInfo.ucCid);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* 如果获取不到，说明不是应答网络激活 */
        return VOS_FALSE;
    }

    /* 找到PDP ID后获取对应的状态机，如果不是网络激活等待用户应答状态，说明不是应答网络激活 */
    if (TAF_APS_STA_NW_ACTIVATING != TAF_APS_GetPdpIdMainFsmState(ucPdpId))
    {
        return VOS_FALSE;
    }

    if (TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER != TAF_APS_GetPdpIdSubFsmState(ucPdpId))
    {
        return VOS_FALSE;
    }

    /* 判断端口是否一致 */
    if (pstPppDialOrigReq->stCtrl.usClientId != TAF_APS_GetPdpEntClientId(ucPdpId, pstPppDialOrigReq->stPppDialParaInfo.ucCid))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPppDialOrigReq_PreProc
 功能描述  : 收到PPP拨号激活消息的时候，需要进行预处理，判定当前是否能进入状态机
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
  1.日    期   : 2011年12月22日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年11月13日
    作    者   : A00165503
    修改内容   : DTS2012111205973: LTE默认缺省承载IP类型IPv4v6, 用户拨号IP类
                 型IPv4 only或IPv6 only, 缺省承载IP类型被错误的修改为用户拨
                 号IP类型
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPppDialOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg = VOS_NULL_PTR;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;
    TAF_PH_MODE                         ucPhMode;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulErrCode;
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo = VOS_NULL_PTR;
#endif

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPhMode                            = MMA_GetCurrPhMode();

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    pstSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

    /* CallBack状态，不能进行拨号 */
    if (VOS_TRUE == pstSdc1xSysInfo->ucIsEmcCallExistFlg)
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                TAF_PS_CAUSE_UNKNOWN);

        return VOS_TRUE;
    }
#endif

    /* 判断当前处于网络激活等待用户应答状态，直接进入状态机 */
    if (VOS_TRUE == TAF_APS_IsStaNwActivatingSubStaWaitAppAnswer(pstPppDialOrigReq))
    {
        return VOS_FALSE;
    }

    /* 如果系统未开机或如果CID对应的上下文没有定义，则直接返回ERROR */
    if ( (TAF_PH_MODE_FULL != ucPhMode)
      || (VOS_FALSE == TAF_APS_GetTafCidInfoUsedFlg(pstPppDialOrigReq->stPppDialParaInfo.ucCid)) )
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                 TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        ulErrCode = TAF_ERR_NO_ERROR;

        ulResult = TAF_APS_FindSutiablePdpForPppDial_LteMode(&pstPppDialOrigReq->stPppDialParaInfo,
                                                             &ulErrCode);
        if (TAF_ERR_ERROR == ulErrCode)
        {
            TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                     TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }

        /* 找到默认承载的情况下，直接刷新CID */
        if (VOS_TRUE == ulResult)
        {
            /* 除了刷新CID，还同时刷新了ClientId和OP ID */
            ucPdpId = TAF_APS_GetPdpIdByDefaultCid();

            /* 清除cid 0 的信息,记录PDP 信息 */
            TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                        pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                        pstPppDialOrigReq->stCtrl.ulModuleId,
                                        pstPppDialOrigReq->stCtrl.usClientId,
                                        pstPppDialOrigReq->stCtrl.ucOpId);

            TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                         pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                         TAF_APS_GetTafCidInfoPdpType(pstPppDialOrigReq->stPppDialParaInfo.ucCid));

            /* 通知ESM当前的Cid刷新 */
            MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                    SM_ESM_PDP_OPT_MODIFY);

            return VOS_FALSE;
        }
    }

#endif

    /* 获取PdpId，如果获取不到，说明当前是激活或者去激活一个新的CID */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstPppDialOrigReq->stPppDialParaInfo.ucCid);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* 分配实体 */
        if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&pstPppDialOrigReq->stCtrl,
                                                           pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                                           &ucPdpId))
        {
            /* 分配不到实体，则直接返回ERROR */
            TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                     TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
    }
    else
    {
        if (TAF_APS_GetPdpEntClientId(ucPdpId, pstPppDialOrigReq->stPppDialParaInfo.ucCid) != pstPppDialOrigReq->stCtrl.usClientId)
        {
            /* ClientId不匹配, 则直接返回ERROR */
            TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                     TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
    }

    if (VOS_TRUE == TAF_APS_IsPdpActLimit_PreProc())
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                 TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_PreProc
 功能描述  : 收到ID_MSG_TAF_PS_CALL_END_REQ消息的时候，需要进行预处理，判定当前是否能进入状态机
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数
  2.日    期   : 2012年3月6日
    作    者   : c00173809
    修改内容   : PPP和NDIS拨相同CID的PDP上下文出错.

  3.日    期   : 2013年9月23日
    作    者   : A00165503
    修改内容   : UART-MODEM: PDPID获取失败时返回ERROR, 防止用户挂死
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;
    TAF_APS_BITCID_INFO_STRU            stCid;

    PS_MEM_SET(&stCid, 0, sizeof(TAF_APS_BITCID_INFO_STRU));
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq                       = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* 获取PdpId，如果获取不到，直接返回，不进状态机 */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstCallEndReq->ucCid);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* 该场景下返回ERROR, 防止使用者挂死 */
        TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                              pstCallEndReq->ucCid,
                              TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;

    }
    else
    {
        if (TAF_APS_GetPdpEntClientId(ucPdpId, pstCallEndReq->ucCid) != pstCallEndReq->stCtrl.usClientId)
        {
            TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                                  pstCallEndReq->ucCid,
                                  TAF_PS_CAUSE_CID_INVALID);

            return VOS_TRUE;
        }
        else
        {
            /* 更新用户信息--IMSA会使用不同的opid */
            TAF_APS_SetPdpEntOpId(ucPdpId,
                                  pstCallEndReq->ucCid,
                                  pstCallEndReq->stCtrl.ucOpId);

            /* 检查PDP实体中是否存在多个cid */
            TAF_APS_GetPdpEntBitCidInfo(ucPdpId, &stCid);

            if (stCid.ulNum > 1)
            {
                /* 返回该cid去激活成功 */
                TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                                      pstCallEndReq->ucCid,
                                      TAF_PS_CAUSE_SUCCESS);

                TAF_APS_SndPdpDeActivateCnf(ucPdpId, pstCallEndReq->ucCid);

                /* 清除PDP实体中该CID信息 */
                TAF_APS_RmvPdpEntClientInfo(ucPdpId, pstCallEndReq->ucCid, &stCid);

                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallAnswerReq_PreProc
 功能描述  : 收到ANSWER消息的时候，需要进行预处理，判定当前是否能进入状态机
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
  1.日    期  : 2011年12月22日
    作    者  : h44270
    修改内容  : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
  3.日    期   : 2013年05月22日
    作    者   : f00179208
    修改内容   : V3R3 PPP PROJECT
  4.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，数据结构变更，增加PID记录到实体

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;
    TAF_PRI_PDP_QUERY_INFO_STRU         stPdpPriPara;
    VOS_UINT32                          ulErrCode;
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstNwActFsm;
    VOS_UINT8                           ucPdpId;

    VOS_UINT8                           ucCid;

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq                    = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);
    ucCid                               = pstCallAnswerReq->stAnsInfo.ucCid;

    pstNwActFsm = TAF_APS_GetPdpEntityFsm(TAF_APS_STA_NW_ACTIVATING,
                                          TAF_APS_FSM_NW_ACTIVATING,
                                          TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER);

    /* 判断当前是否处于网络激活等待用户应答状态 */
    if (VOS_NULL_PTR == pstNwActFsm)
    {
        TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                 pstCallAnswerReq->stAnsInfo.ucCid,
                                 TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

    ucPdpId = pstNwActFsm->ucPdpId;

    /* 不支持IPV4/IPV4V6类型，直接回ERROR */
#if (FEATURE_ON == FEATURE_IPV6)
    if ((MN_APS_ADDR_IPV6 == g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum)
     || (MN_APS_ADDR_IPV4V6 == g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum))
    {
        TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                 pstCallAnswerReq->stAnsInfo.ucCid,
                                 TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }
#endif

    /* 用户指定了CID，需要匹配PDP TYPE和ADDR。否则使用网络指定的PDP TYPE和ADDR */
    if (0 != ucCid)
    {
        /* 获取Primary PDP上下文信息 */
        PS_MEM_SET(&stPdpPriPara, 0x00, sizeof(TAF_PRI_PDP_QUERY_INFO_STRU));
        Aps_QuePri(pstCallAnswerReq->stAnsInfo.ucCid, &stPdpPriPara, &ulErrCode);
        if (TAF_PARA_OK != ulErrCode)
        {
            TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                     pstCallAnswerReq->stAnsInfo.ucCid,
                                     TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
        else
        {
            /* 用户设置的类型和网络下发的类型不一致 */
            if (TAF_APS_ConvertPdpType(g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum) != stPdpPriPara.stPriPdpInfo.stPdpAddr.enPdpType)
            {
                TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                         pstCallAnswerReq->stAnsInfo.ucCid,
                                         TAF_PS_CAUSE_UNKNOWN);
                return VOS_TRUE;
            }

            /* 网络发起的PPP类型的拨号，需要进行匹配拨号类型 */
            /* 网络发起的IPV4类型的拨号，需要进行匹配拨号类型和IP地址 */
            if (APS_ADDR_PPP != g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum)
            {
                /* 用户设置了PDP ADDR */
                if ('\0' != stPdpPriPara.stPriPdpInfo.stPdpAddr.aucIpv4Addr[0])
                {
                    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
                    if (0 != PS_MEM_CMP(stPdpPriPara.stPriPdpInfo.stPdpAddr.aucIpv4Addr,
                                        g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr,
                                        TAF_IPV4_ADDR_LEN))
                    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
                    {
                        TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                                 pstCallAnswerReq->stAnsInfo.ucCid,
                                                 TAF_PS_CAUSE_UNKNOWN);
                        return VOS_TRUE;
                    }
                }
            }
        }
    }

    ucCid = ((0 != ucCid) ? ucCid : TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 记录PDP 信息 */
    TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                ucCid,
                                pstCallAnswerReq->stCtrl.ulModuleId,
                                pstCallAnswerReq->stCtrl.usClientId,
                                pstCallAnswerReq->stCtrl.ucOpId);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_ConvertPdpType(g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum));

    /* 如果AT^ANSWER发起的IP类型的网络激活响应，直接上报CONNECT给AT，等待PPP发起拨号请求 */
    if (VOS_TRUE == pstCallAnswerReq->stAnsInfo.ucAnsExtFlg)
    {
        if (TAF_PDP_IPV4 == TAF_APS_ConvertPdpType(g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum))
        {
            /* 前面操作成功，记录下应答的客户端和呼叫标识和Cid */
            g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct
                                                = APS_APP_MANUL_ACT;

            TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                     TAF_APS_GetPdpEntCurrCid(ucPdpId),
                                     TAF_ERR_AT_CONNECT);

            return VOS_TRUE;
        }
    }


    /* 预处理结束，需要进入状态机 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallHangupReq_PreProc
 功能描述  : 收到HAANUP消息的时候，需要进行预处理，判定当前是否能进入状态机
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstNwActFsm;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    pstNwActFsm = TAF_APS_GetPdpEntityFsm(TAF_APS_STA_NW_ACTIVATING,
                                          TAF_APS_FSM_NW_ACTIVATING,
                                          TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER);

    /* 判断当前是否处于网络激活等待用户应答状态 */
    if (VOS_NULL_PTR == pstNwActFsm)
    {
        TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl), TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmRegPdpActCnf_PreProc
 功能描述  : 收到SM D_PMC_SMREG_PDP_ACT_CNF消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

 2.日    期  : 2011年12月22日
   作    者  : M00217266
   修改内容  : 清零PDP激活失败计数器（AT&T&DCM定制 PDP激活受限）
 3.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpActCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_CNF_STRU        *pstSmMsg;
    SM_TAF_TRANS_ID_STRU                stTi;
    TAF_APS_PDP_ACT_LIMIT_INFO_STRU    *pstPdpActLimitInfo;


    PS_MEM_SET(&stTi, 0x00, sizeof(stTi));


    pstSmMsg = (SMREG_PDP_ACTIVATE_CNF_STRU *)pstMsg;

    /* 根据CR获取不到相应的PDP ID，则打印异常，直接返回，不进状态机 */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    pstPdpActLimitInfo = TAF_APS_GetPdpActLimitInfoAddr();

    if (VOS_TRUE == pstPdpActLimitInfo->ucPdpActLimitFlg)
    {
        pstPdpActLimitInfo->ucPdpActFailCount = 0;

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
        {
            TAF_APS_StopTimer(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID);
        }
    }


    /* mo场景，直接在此处刷新实体中Ti的值 */
    stTi.ucTiValue = pstSmMsg->stTransId.ucTiValue;
    stTi.ucTiFlag  = pstSmMsg->stTransId.ucTiFlag;

    TAF_APS_SetPdpEntityTi(pstSmMsg->ucConnectId, &stTi);

    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmRegPdpActRej_PreProc
 功能描述  : 收到SM D_PMC_SMREG_PDP_ACT_REJ消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

 2.日    期  : 2012年6月15日
   作    者  : m00217266
   修改内容  : 添加PDP激活受限处理

  3.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : SM/APS原语接口中的CAUSE成员类型修改
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpActRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_REJ_STRU        *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_REJ_STRU *)pstMsg;

    /* 根据CR获取不到相应的PDP ID，则打印异常，直接返回，不进状态机 */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    /* PDP激活受限处理:PDP激活的次数为SM实际尝试的PDP激活次数 */
    if (SM_TAF_CAUSE_SM_MAX_TIME_OUT == pstSmMsg->enCause)
    {
        TAF_APS_ProcPdpActLimit_PreProc(pstSmMsg->ucExpiredCount);
    }
    else
    {
        TAF_APS_ProcPdpActLimit_PreProc(pstSmMsg->ucExpiredCount + 1);
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmRegPdpActInd_PreProc
 功能描述  : 收到SM D_PMC_SMREG_PDP_ACT_Ind消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数
 2.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理
 3.日    期   : 2013年06月05日
   作    者   : f00179208
   修改内容   : V3R3 PPP PROJECT
 4.日    期   : 2013年07月08日
   作    者   : Y00213812
   修改内容   : VoLTE_PhaseI 项目，增加PID记录到实体
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpActInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_IND_STRU        *pstSmMsg;
    APS_PDP_CONTEXT_ENTITY_ST          *pstCurrEntity;
    SM_TAF_TRANS_ID_STRU                stTi;


    PS_MEM_SET(&stTi, 0x00, sizeof(stTi));


    pstSmMsg = (SMREG_PDP_ACTIVATE_IND_STRU *)pstMsg;


    /* 网络发起的PDP激活，在预处理处分配PDP ID,这里的CR 等同于PDP ID */
    pstCurrEntity = TAF_APS_GetPdpEntInfoAddr(pstSmMsg->ucConnectId);
    pstCurrEntity->stClientInfo.ucCid   = TAF_APS_FindCidForAns();
    pstCurrEntity->ulUsedFlg            = VOS_TRUE;
    pstCurrEntity->ucPdpId              = pstSmMsg->ucConnectId;

    /* 刷新PDP信息 */
    TAF_APS_SetPdpEntClientInfo(pstCurrEntity->ucPdpId,
                                pstCurrEntity->stClientInfo.ucCid,
                                TAF_APS_INVALID_MODULEID,
                                TAF_APS_INVALID_CLIENTID,
                                TAF_APS_INVALID_OPID);

    /* mt场景，直接在此处刷新实体中Ti的值 */
    stTi.ucTiValue = pstSmMsg->stTransId.ucTiValue;
    stTi.ucTiFlag  = pstSmMsg->stTransId.ucTiFlag;

    TAF_APS_SetPdpEntityTi(pstSmMsg->ucConnectId, &stTi);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmRegPdpModifyInd_PreProc
 功能描述  : 收到SM SMREG_PDP_MODIFY_IND_STRU消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_MODIFY_IND_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_IND_STRU *)pstMsg;

    /* 根据CR获取不到相应的PDP ID，则打印异常，直接返回，不进状态机 */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;


}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmRegPdpModifyCnf_PreProc
 功能描述  : 收到SM D_PMC_SMREG_PDP_MODIFY_IND消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_MODIFY_CNF_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_CNF_STRU *)pstMsg;

    /* 根据CR获取不到相应的PDP ID，则打印异常，直接返回，不进状态机 */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmRegPdpModifyRej_PreProc
 功能描述  : 收到SM D_PMC_SMREG_PDP_MODIFY_IND消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpModifyRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_MODIFY_REJ_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_REJ_STRU *)pstMsg;

    /* 根据CR获取不到相应的PDP ID，则打印异常，直接返回，不进状态机 */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;


}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmRegPdpDeactivInd_PreProc
 功能描述  : 收到SM D_PMC_SMREG_PDP_DEACTIV_IND消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

2.日    期  : 2012年6月15日
   作    者  : m00217266
   修改内容  : 添加PDP激活受限处理

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpDeactivInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmMsg;

    pstSmMsg = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* 根据TI获取不到相应的PDP ID，则打印异常，直接返回，不进状态机 */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    /* PDP激活受限处理: 网侧主动发起的PDP去激活，认为发起PDP激活的次数为1 */
    TAF_APS_ProcPdpActLimit_PreProc(1);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmRegPdpDeactivCnf_PreProc
 功能描述  : 收到SM D_PMC_SMREG_PDP_DEACTIV_CNF消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpDeactivCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_DEACTIVATE_CNF_STRU      *pstSmMsg;

    pstSmMsg = (SMREG_PDP_DEACTIVATE_CNF_STRU *)pstMsg;

    /* 根据CR获取不到相应的PDP ID，则打印异常，直接返回，不进状态机 */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;


}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmRegPdpActSecCnf_PreProc
 功能描述  : 收到SM D_PMC_SMREG_PDP_ACT_SEC_CNF消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数
 2.日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpActSecCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_SEC_CNF_STRU    *pstSmMsg;
    SM_TAF_TRANS_ID_STRU                stTi;


    PS_MEM_SET(&stTi, 0x00, sizeof(stTi));


    pstSmMsg = (SMREG_PDP_ACTIVATE_SEC_CNF_STRU *)pstMsg;

    /* 根据CR获取不到相应的PDP ID，则打印异常，直接返回，不进状态机 */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    /* mo场景，直接在此处刷新实体中Ti的值 */
    stTi.ucTiValue = pstSmMsg->stTransId.ucTiValue;
    stTi.ucTiFlag  = pstSmMsg->stTransId.ucTiFlag;

    TAF_APS_SetPdpEntityTi(pstSmMsg->ucConnectId, &stTi);

    return VOS_FALSE;


}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmRegPdpActSecRej_PreProc
 功能描述  : 收到SM D_PMC_SMREG_PDP_ACT_SEC_REJ消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpActSecRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_SEC_REJ_STRU    *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_SEC_REJ_STRU *)pstMsg;

    /* 根据CR获取不到相应的PDP ID，则打印异常，直接返回，不进状态机 */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;


}

#if ( FEATURE_ON == FEATURE_LTE )
/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetEpsQosInfoReq_PreProc
 功能描述  : 设置EPS服务质量预处理函数
             (ID_MSG_TAF_PS_SET_EPS_QOS_INFO_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月16日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetEpsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* 初始化消息 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                           TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* 发送消息给L4A */
    TAF_APS_SndL4aSetCgeqosReq(pstPsMsg->aucContent);

    /* 启动L4A消息回复保护定时器 */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGEQOS_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* 添加消息进等待队列 */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOS_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_SET_EPS_QOS_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aSetCgdcontCnf_PreProc
 功能描述  : CNF消息预处理函数
             (ID_L4A_APS_SET_CGDCONT_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数

  2.日    期   : 2012年6月15日
    作    者   : m00217266
    修改内容   : 停止暂停PDP激活定时器(AT&T定制，PDP激活限制)

  3.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，数据结构变更

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgdcontCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGDCONT_CNF_STRU               *pstPsMsg;
    TAF_CTRL_STRU                               stCtrl = {0};
    VOS_UINT32                                  ulErrCode;
    TAF_APS_CMD_BUFFER_STRU                    *pstMsgInfo;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU  *pstSetPdpCtxInfoReq;
    VOS_UINT32                                  ulPara;

    /* 初始化消息 */
    pstPsMsg                = (APS_L4A_SET_CGDCONT_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetPdpCtxInfoReq     = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* 判断保护定时器是否已超时 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGDCONT_CNF,
                                                              ulPara))
    {
        /* 保护定时器没有超时, 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGDCONT_CNF, ulPara);

        /* 从缓冲队列中获取消息 */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDCONT_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* 消息获取失败, 打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgdcontCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }
        /* 消息获取成功, 更新APS本地全局变量, 写NV操作 */
        pstSetPdpCtxInfoReq = (TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetPdpCtxInfoReq->stCtrl;

        /* L4A错误参数转换 */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* 如果L4A全局变量更新成功, 更新APS本地全局变量, 写NV操作 */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {

            /* PDP激活受限特性打开，暂停激活定时器正在运行 */
            if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
            {
                TAF_APS_RcvSetPrimPdpCtxInfoReq_PdpActLimit(pstSetPdpCtxInfoReq);
            }


            /* 设置Primary PDP上下文 */
            Aps_DefPsPdpContext(pstSetPdpCtxInfoReq->stCtrl.usClientId,
                                pstSetPdpCtxInfoReq->stCtrl.ucOpId,
                                &(pstSetPdpCtxInfoReq->stPdpContextInfo),
                                &ulErrCode);
        }

        /* 从消息等待队列中删除该消息 */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDCONT_CNF, ulPara);

        /* 返回AT处理结果 */
        TAF_APS_SndSetPrimPdpCtxInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aSetCgdscontCnf_PreProc
 功能描述  : CNF消息预处理函数
             (ID_L4A_APS_SET_CGDSCONT_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，数据结构变更

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgdscontCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGDSCONT_CNF_STRU              *pstPsMsg;
    TAF_CTRL_STRU                               stCtrl = {0};
    VOS_UINT32                                  ulErrCode;
    TAF_APS_CMD_BUFFER_STRU                    *pstMsgInfo;
    TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU   *pstSetPdpCtxInfoReq;
    VOS_UINT32                                  ulPara;

    /* 初始化消息 */
    pstPsMsg                = (APS_L4A_SET_CGDSCONT_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetPdpCtxInfoReq     = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* 判断保护定时器是否已超时 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF,
                                                              ulPara))
    {
        /* 保护定时器没有超时, 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF, ulPara);

        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
        /* 从缓冲队列中获取消息 */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* 消息获取失败, 打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgdscontCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* 消息获取成功, 更新APS本地全局变量, 写NV操作 */
        pstSetPdpCtxInfoReq = (TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetPdpCtxInfoReq->stCtrl;

        /* L4A错误参数转换 */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* 如果L4A全局变量更新成功, 更新APS本地全局变量, 写NV操作 */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* 设置Primary PDP上下文 */
            Aps_DefPsSecPdpContext(pstSetPdpCtxInfoReq->stCtrl.usClientId,
                                   pstSetPdpCtxInfoReq->stCtrl.ucOpId,
                                   &(pstSetPdpCtxInfoReq->stPdpContextInfo),
                                   &ulErrCode);
        }
        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

        /* 从消息等待队列中删除该消息 */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF, ulPara);

        /* 返回AT处理结果 */
        TAF_APS_SndSetSecPdpCtxInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aSetCgtftCnf_PreProc
 功能描述  : CNF消息预处理函数
             (ID_L4A_APS_SET_CGTFT_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，数据结构变更

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgtftCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGTFT_CNF_STRU         *pstPsMsg;
    TAF_CTRL_STRU                       stCtrl = {0};
    VOS_UINT32                          ulErrCode;
    TAF_APS_CMD_BUFFER_STRU            *pstMsgInfo;
    TAF_PS_SET_TFT_INFO_REQ_STRU       *pstSetTftInfoReq;
    VOS_UINT32                          ulPara;

    /* 初始化消息 */
    pstPsMsg                = (APS_L4A_SET_CGTFT_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetTftInfoReq        = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* 判断保护定时器是否已超时 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGTFT_CNF,
                                                              ulPara))
    {
        /* 保护定时器没有超时, 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGTFT_CNF, ulPara);

        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
        /* 从缓冲队列中获取消息 */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFT_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* 消息获取失败, 打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgtftCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* 消息获取成功, 更新APS本地全局变量, 写NV操作 */
        pstSetTftInfoReq = (TAF_PS_SET_TFT_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetTftInfoReq->stCtrl;

        /* L4A错误参数转换 */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* 如果L4A全局变量更新成功, 更新APS本地全局变量, 写NV操作 */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* 设置TFT参数 */
            TAF_APS_SetTftInfo(&(pstSetTftInfoReq->stTftInfo), &ulErrCode);
        }
        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

        /* 从消息等待队列中删除该消息 */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFT_CNF, ulPara);

        /* 返回AT处理结果 */
        TAF_APS_SndSetTftInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aSetCgautoCnf_PreProc
 功能描述  : CNF消息预处理函数
             (ID_L4A_APS_SET_CGAUTO_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgautoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGAUTO_CNF_STRU            *pstPsMsg;
    TAF_CTRL_STRU                           stCtrl = {0};
    VOS_UINT32                              ulErrCode;
    TAF_APS_CMD_BUFFER_STRU                *pstMsgInfo;
    TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU   *pstSetAnsModeInfoReq;
    VOS_UINT32                              ulPara;

    /* 初始化消息 */
    pstPsMsg                = (APS_L4A_SET_CGAUTO_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetAnsModeInfoReq    = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);


    /* 判断保护定时器是否已超时 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGAUTO_CNF,
                                                              ulPara))
    {
        /* 保护定时器没有超时, 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGAUTO_CNF, ulPara);

        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
        /* 从缓冲队列中获取消息 */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGAUTO_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* 消息获取失败, 打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgautoCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* 消息获取成功, 更新APS本地全局变量, 写NV操作 */
        pstSetAnsModeInfoReq = (TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetAnsModeInfoReq->stCtrl;

        /* L4A错误参数转换 */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* 如果L4A全局变量更新成功, 更新APS本地全局变量, 写NV操作 */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* 检查应答模式是否合法 */
            if ( (TAF_PDP_ANSWER_MODE_MANUAL == pstSetAnsModeInfoReq->ulAnsMode)
              || (TAF_PDP_ANSWER_MODE_AUTO   == pstSetAnsModeInfoReq->ulAnsMode) )
            {
                /* 设置应答模式 */
                Aps_SetPsAnsMode(pstSetAnsModeInfoReq->stCtrl.usClientId,
                                 pstSetAnsModeInfoReq->stCtrl.ucOpId,
                                 (TAF_PDP_ANSWER_MODE_ENUM_UINT8)pstSetAnsModeInfoReq->ulAnsMode,
                                 &ulErrCode);
            }
            else
            {
                ulErrCode = TAF_PARA_SET_ERROR;
            }
        }
        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

        /* 从消息等待队列中删除该消息 */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGAUTO_CNF, ulPara);

        /* 返回AT处理结果 */
        TAF_APS_SndSetAnsModeInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aSetCgansCnf_PreProc
 功能描述  : CNF消息预处理函数
             (ID_L4A_APS_SET_CGANS_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgansCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 处理L4A发来的消息 */

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aSetCgeqosCnf_PreProc
 功能描述  : CNF消息预处理函数
             (ID_L4A_APS_SET_CGEQOS_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgeqosCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGEQOS_CNF_STRU        *pstPsMsg;
    TAF_CTRL_STRU                       stCtrl = {0};
    VOS_UINT32                          ulErrCode;
    TAF_APS_CMD_BUFFER_STRU            *pstMsgInfo;
    TAF_PS_SET_EPS_QOS_INFO_REQ_STRU   *pstSetEpsQosInfoReq;
    VOS_UINT32                          ulPara;

    /* 初始化消息 */
    pstPsMsg                = (APS_L4A_SET_CGEQOS_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetEpsQosInfoReq     = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* 判断保护定时器是否已超时 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGEQOS_CNF,
                                                              ulPara))
    {
        /* 保护定时器没有超时, 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGEQOS_CNF, ulPara);

        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
        /* 从缓冲队列中获取消息 */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOS_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* 消息获取失败, 打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgeqosCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* 消息获取成功, 更新APS本地全局变量, 写NV操作 */
        pstSetEpsQosInfoReq = (TAF_PS_SET_EPS_QOS_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetEpsQosInfoReq->stCtrl;

        /* L4A错误参数转换 */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* 如果L4A全局变量更新成功, 更新APS本地全局变量, 写NV操作 */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* 设置应答模式 */
            TAF_APS_SetEpsQosInfo(&pstSetEpsQosInfoReq->stEpsQosInfo,
                                  &ulErrCode);
        }
        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

        /* 从消息等待队列中删除该消息 */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOS_CNF, ulPara);

        /* 返回AT处理结果 */
        TAF_APS_SndSetCgeqosCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aSetAuthdataCnf_PreProc
 功能描述  : CNF消息预处理函数
             (ID_L4A_APS_SET_AUTHDATA_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetAuthdataCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_AUTHDATA_CNF_STRU      *pstPsMsg;
    TAF_CTRL_STRU                       stCtrl = {0};
    VOS_UINT32                          ulErrCode;
    TAF_APS_CMD_BUFFER_STRU            *pstMsgInfo;
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU  *pstAuthDataReq;
    VOS_UINT32                          ulPara;

    /* 初始化消息 */
    pstPsMsg                = (APS_L4A_SET_AUTHDATA_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstAuthDataReq          = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* 判断保护定时器是否已超时 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF,
                                                              ulPara))
    {
        /* 保护定时器没有超时, 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF, ulPara);

        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
        /* 从缓冲队列中获取消息 */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* 消息获取失败, 打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetAuthdataCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* 消息获取成功, 更新APS本地全局变量, 写NV操作 */
        pstAuthDataReq = (TAF_PS_SET_AUTHDATA_INFO_REQ_STRU *)pstMsgInfo->pulMsgInfo;
        stCtrl = pstAuthDataReq->stCtrl;

        /* L4A错误参数转换 */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* 如果L4A全局变量更新成功, 更新APS本地全局变量, 写NV操作 */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* 设置AUTHDATA参数(NDIS) */
            Aps_DefNdisAuthdata(pstAuthDataReq->stCtrl.usClientId,
                                pstAuthDataReq->stCtrl.ucOpId,
                                &(pstAuthDataReq->stAuthDataInfo),
                                &ulErrCode);
        }
        /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

        /* 从消息等待队列中删除该消息 */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF, ulPara);

        /* 返回AT处理结果 */
        (VOS_VOID)TAF_APS_SndSetAuthDataInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aSetCgcontrdpCnf_PreProc
 功能描述  : CNF消息预处理函数
             (ID_L4A_APS_SET_CGCONTRDP_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgcontrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGCONTRDP_CNF_STRU                     *pstPsMsg;
    VOS_UINT32                                          ulErrCode;
    VOS_UINT32                                          ulCidNum;                   /* CID数量  */
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU  *pstGetDynamicPdpCtxInfoCnf;
    VOS_UINT32                                          ulGetDynamicPdpCtxInfoCnfLen;
    VOS_UINT32                                          ulPara;

    /* 初始化消息 */
    pstPsMsg                            = (APS_L4A_SET_CGCONTRDP_CNF_STRU*)pstMsg;
    ulErrCode                           = pstPsMsg->ulErrorCode;
    ulCidNum                            = pstPsMsg->ulCidNum;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* 判断保护定时器是否已超时 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                                                              ulPara))
    {
        /* 保护定时器没有超时, 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF, ulPara);

        /* L4A错误参数转换 */
        ulErrCode   = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* 如果L4A查询动态参数失败，CID设置为0 */
        if ( TAF_PS_CAUSE_SUCCESS != ulErrCode )
        {
            ulCidNum = 0;
        }

        /* 计算回复事件消息内容长度 */
        ulGetDynamicPdpCtxInfoCnfLen    = sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU)
                                            + (ulCidNum * sizeof(TAF_PDP_DYNAMIC_PRIM_EXT_STRU));

        /* 申请内存 */
        pstGetDynamicPdpCtxInfoCnf      = (TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                                                           ulGetDynamicPdpCtxInfoCnfLen);

        /* 申请消息失败 */
        if ( VOS_NULL_PTR == pstGetDynamicPdpCtxInfoCnf )
        {
            /* 系统异常打印, 直接返回 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgcontrdpCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        /* 填写事件内容 */
        PS_MEM_SET(pstGetDynamicPdpCtxInfoCnf,
                   0x00,
                   ulGetDynamicPdpCtxInfoCnfLen);


        /* 从缓冲队列中获取消息 */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstGetDynamicPdpCtxInfoCnf->stCtrl,
                                                              TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                                                              ulPara))
        {
            /* 消息获取失败, 打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgcontrdpCnf_PreProc: Get message info failed!");

            /* 释放内存 */
            PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);

            return VOS_TRUE;
        }

        pstGetDynamicPdpCtxInfoCnf->enCause         = ulErrCode;
        pstGetDynamicPdpCtxInfoCnf->ulCidNum        = ulCidNum;

        if (0 != ulCidNum)
        {
            PS_MEM_CPY(pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo,
                       pstPsMsg->astPrimParaInfo,
                       (ulCidNum * sizeof(TAF_PDP_DYNAMIC_PRIM_EXT_STRU)));
        }

        /* 将消息返回AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF,
                        pstGetDynamicPdpCtxInfoCnf,
                        ulGetDynamicPdpCtxInfoCnfLen);

        /* 释放内存 */
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);

        /* 从消息等待队列中删除该消息 */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF, ulPara);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aSetCgscontrdpCnf_PreProc
 功能描述  : CNF消息预处理函数
             (ID_L4A_APS_SET_CGSCONTRDP_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，从缓冲队列中获取消息

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgscontrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGSCONTRDP_CNF_STRU                    *pstPsMsg;
    VOS_UINT32                                          ulErrCode;
    VOS_UINT32                                          ulCidNum;                   /* CID数量  */
    TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU   *pstGetDynamicPdpCtxInfoCnf;
    VOS_UINT32                                          ulGetDynamicPdpCtxInfoCnfLen;
    VOS_UINT32                                          ulPara;

    /* 初始化消息 */
    pstPsMsg                            = (APS_L4A_SET_CGSCONTRDP_CNF_STRU*)pstMsg;
    ulErrCode                           = pstPsMsg->ulErrorCode;
    ulCidNum                            = pstPsMsg->ulCidNum;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* 判断保护定时器是否已超时 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                                                              ulPara))
    {
        /* 保护定时器没有超时, 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF, ulPara);

        /* L4A错误参数转换 */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* 如果L4A查询动态参数失败，CID设置为0 */
        if ( TAF_PS_CAUSE_SUCCESS != ulErrCode )
        {
            ulCidNum = 0;
        }

        /* 计算事件内容长度 */
        ulGetDynamicPdpCtxInfoCnfLen    = sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU)
                                            + (ulCidNum * sizeof(TAF_PDP_DYNAMIC_SEC_EXT_STRU));

        /* 申请内存 */
        pstGetDynamicPdpCtxInfoCnf      = (TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                                                          ulGetDynamicPdpCtxInfoCnfLen);

        /* 申请消息失败 */
        if ( VOS_NULL_PTR == pstGetDynamicPdpCtxInfoCnf )
        {
            /* 系统异常打印, 直接返回 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgscontrdpCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        /* 填写事件内容 */
        PS_MEM_SET(pstGetDynamicPdpCtxInfoCnf,
                   0x00,
                   ulGetDynamicPdpCtxInfoCnfLen);

        /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
        /* 从缓冲队列中获取消息 */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstGetDynamicPdpCtxInfoCnf->stCtrl,
                                                              TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                                                              ulPara))
        {
            /* 消息获取失败, 打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgscontrdpCnf_PreProc: Get message info failed!");

            /* 释放内存 */
            PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);

            return VOS_TRUE;
        }
        /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

        pstGetDynamicPdpCtxInfoCnf->enCause          = ulErrCode;
        pstGetDynamicPdpCtxInfoCnf->ulCidNum         = ulCidNum;

        if (0 != ulCidNum)
        {
            PS_MEM_CPY(pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo,
                       pstPsMsg->astSecParaInfo,
                       (ulCidNum * sizeof(TAF_PDP_DYNAMIC_SEC_EXT_STRU)));
        }

        /* 将消息返回AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF,
                         pstGetDynamicPdpCtxInfoCnf,
                         ulGetDynamicPdpCtxInfoCnfLen);

        /* 释放内存 */
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);

        /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
        /* 从消息等待队列中删除该消息 */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF, ulPara);
        /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_FillPfTftInfo
 功能描述  : 将L4a回复的TFT参数填充到回复给AT的CNF消息中
 输入参数  : APS_L4A_SDF_PF_TFT_STRU   *pstL4aPfTftInfo - L4A回复的TFT参数
             VOS_UINT32                 ulCidNum        - CID个数
  输出参数  : TAF_PF_TFT_STRU           *pstPfTftInfo    - 给AT回复的TFT参数
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月12日
    作    者   : l00198894
    修改内容   : 新生成函数

  2.日    期   : 2015年9月28日
    作    者   : W00316404
    修改内容   : R11 TFT 协议升级

*****************************************************************************/
VOS_VOID TAF_APS_FillPfTftInfo(
    TAF_PF_TFT_STRU                    *pstPfTftInfo,
    APS_L4A_SDF_PF_TFT_STRU            *pstL4aPfTftInfo,
    VOS_UINT32                          ulCidNum
)
{
    VOS_UINT32                          ulIndex1;
    VOS_UINT32                          ulIndex2;

    /* 初始化参数 */
    ulIndex1        = VOS_NULL;
    ulIndex2        = VOS_NULL;

    /* 循环遍历填充TFT参数 */
    for (ulIndex1 = 0; ulIndex1 < ulCidNum; ulIndex1++)
    {
        pstPfTftInfo[ulIndex1].ulCid    = pstL4aPfTftInfo[ulIndex1].ulCid;
        pstPfTftInfo[ulIndex1].ulPFNum  = pstL4aPfTftInfo[ulIndex1].ulPfNum;

        for (ulIndex2 = 0; ulIndex2 < pstL4aPfTftInfo[ulIndex1].ulPfNum; ulIndex2++)
        {
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpPktFilterId    = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpPktFilterId;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpPrecedence     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpPrecedence;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSrcIp          = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSrcIp;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpProtocolId     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpProtocolId;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpDestPortRange  = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpDestPortRange;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSrcPortRange   = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSrcPortRange;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSpi            = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSpi;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpTosMask        = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpTosMask;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpFlowLable      = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpFlowLable;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpDirection      = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpDirection;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpNwPktFilterId  = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpNwPktFilterId;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpLocalIpv4AddrAndMask  = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpLocalIpv4AddrAndMask;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpLocalIpv6AddrAndMask  = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpLocalIpv6AddrAndMask;

            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucCid               = (VOS_UINT8)pstL4aPfTftInfo[ulIndex1].ulCid;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucDefined           = VOS_TRUE;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucPacketFilterId    = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucPacketFilterId;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucPrecedence        = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucPrecedence;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucProtocolId        = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucProtocolId;

            PS_MEM_CPY(&(pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].stSourceIpaddr),
                       &(pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].stSourceIpaddr),
                       sizeof(TAF_PDP_ADDR_STRU));
            PS_MEM_CPY(&(pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].stSourceIpMask),
                       &(pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].stSourceIpMask),
                       sizeof(TAF_PDP_ADDR_STRU));
            PS_MEM_CPY(pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].aucLocalIpv4Addr,
                       pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].aucLocalIpv4Addr,
                       APS_L4A_MAX_IPV4_ADDR_LEN);
            PS_MEM_CPY(pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].aucLocalIpv4Mask,
                       pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].aucLocalIpv4Mask,
                       APS_L4A_MAX_IPV4_ADDR_LEN);
            PS_MEM_CPY(pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].aucLocalIpv6Addr,
                       pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].aucLocalIpv6Addr,
                       APS_L4A_MAX_IPV6_ADDR_LEN);
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucLocalIpv6Prefix   = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucLocalIpv6Prefix;

            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usLowSourcePort     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usLowSourcePort;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usHighSourcePort    = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usHighSourcePort;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usLowDestPort       = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usLowDestPort;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usHighDestPort      = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usHighDestPort;

            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ulSecuParaIndex     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ulSecuParaIndex;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ulFlowLable         = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ulFlowLable;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucTypeOfServiceMask = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucTypeOfServiceMask;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucTypeOfService     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucTypeOfService;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucDirection         = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].enTftFilterDirection;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucNwPktFilterId     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucNwPktFilterId;
        }

    }
    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc
 功能描述  : CNF消息预处理函数
             (ID_L4A_APS_SET_CGTFTRDP_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，从缓冲队列中获取消息

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGTFTRDP_CNF_STRU          *pstPsMsg;
    VOS_UINT32                              ulErrCode;
    VOS_UINT32                              ulCidNum;                   /* CID数量  */
    TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU   *pstGetDynamicTftInfoCnf;
    VOS_UINT32                              ulGetDynamicTftInfoCnfLen;
    VOS_UINT32                              ulPara;

    /* 初始化消息 */
    pstPsMsg                            = (APS_L4A_SET_CGTFTRDP_CNF_STRU*)pstMsg;
    ulErrCode                           = pstPsMsg->ulErrorCode;
    ulCidNum                            = pstPsMsg->ulCidNum;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* 判断保护定时器是否已超时 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                                                              ulPara))
    {
        /* 保护定时器没有超时, 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF, ulPara);

        /* L4A错误参数转换 */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* 如果L4A查询动态参数失败，CIDNum设置为0 */
        if ( TAF_PS_CAUSE_SUCCESS != ulErrCode )
        {
            ulCidNum = 0;
        }

        /* 计算事件内容长度 */
        ulGetDynamicTftInfoCnfLen   = sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU)
                                        + (ulCidNum * sizeof(TAF_PF_TFT_STRU));

        /* 申请内存 */
        pstGetDynamicTftInfoCnf = (TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                                WUEPS_PID_TAF,
                                                ulGetDynamicTftInfoCnfLen);

        /* 申请消息失败 */
        if ( VOS_NULL_PTR == pstGetDynamicTftInfoCnf )
        {
            /* 系统异常打印, 直接返回 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        /* 填写事件内容 */
        PS_MEM_SET(pstGetDynamicTftInfoCnf,
                   0x00,
                   ulGetDynamicTftInfoCnfLen);

        /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
        /* 从缓冲队列中获取消息 */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstGetDynamicTftInfoCnf->stCtrl,
                                                              TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                                                              ulPara))
        {
            /* 消息获取失败, 打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc: Get message info failed!");

            /* 释放内存 */
            PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicTftInfoCnf);

            return VOS_TRUE;
        }
        /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

        pstGetDynamicTftInfoCnf->enCause          = ulErrCode;
        pstGetDynamicTftInfoCnf->ulCidNum         = ulCidNum;

        TAF_APS_FillPfTftInfo(pstGetDynamicTftInfoCnf->astPfTftInfo, pstPsMsg->astPfTftInfo, ulCidNum);

        /* 将消息返回AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_TFT_INFO_CNF,
                         pstGetDynamicTftInfoCnf,
                         ulGetDynamicTftInfoCnfLen);

        /* 释放内存 */
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicTftInfoCnf);

        /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
        /* 从消息等待队列中删除该消息 */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF, ulPara);
        /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aSetCgeqosrdpCnf_PreProc
 功能描述  : CNF消息预处理函数
             (ID_L4A_APS_SET_CGEQOSRDP_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月18日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgeqosrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGEQOSRDP_CNF_STRU                     *pstPsMsg;
    VOS_UINT32                                          ulErrCode;
    VOS_UINT32                                          ulCidNum;                   /* CID数量  */
    TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU           *pstGetDynamicEpsQosInfoCnf;
    VOS_UINT32                                          ulGetDynamicEpsQosInfoCnfLen;
    VOS_UINT32                                          ulPara;

    /* 初始化消息 */
    pstPsMsg                            = (APS_L4A_SET_CGEQOSRDP_CNF_STRU*)pstMsg;
    ulErrCode                           = pstPsMsg->ulErrorCode;
    ulCidNum                            = pstPsMsg->ulCidNum;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* 判断保护定时器是否已超时 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                                                              ulPara))
    {
        /* 保护定时器没有超时, 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF, ulPara);

        /* L4A错误参数转换 */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* 如果L4A查询动态参数失败，CIDNum设置为0 */
        if ( TAF_PS_CAUSE_SUCCESS != ulErrCode )
        {
            ulCidNum = 0;
        }

        /* 计算事件内容长度 */
        ulGetDynamicEpsQosInfoCnfLen    = sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU)
                                            + (ulCidNum * sizeof(TAF_EPS_QOS_EXT_STRU));

        /* 申请内存 */
        pstGetDynamicEpsQosInfoCnf      = (TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                                                  ulGetDynamicEpsQosInfoCnfLen);

        /* 申请消息失败 */
        if ( VOS_NULL_PTR == pstGetDynamicEpsQosInfoCnf )
        {
            /* 系统异常打印, 直接返回 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        /* 填写事件内容 */
        PS_MEM_SET(pstGetDynamicEpsQosInfoCnf,
                   0x00,
                   ulGetDynamicEpsQosInfoCnfLen);

        /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-08-28, begin */
        /* 从缓冲队列中获取消息 */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstGetDynamicEpsQosInfoCnf->stCtrl,
                                                              TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                                                              ulPara))
        {
            /* 消息获取失败, 打印错误信息 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgeqosrdpCnf_PreProc: Get message info failed!");

            /* 释放内存 */
            PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicEpsQosInfoCnf);

            return VOS_TRUE;
        }
        /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-08-28, end */

        pstGetDynamicEpsQosInfoCnf->enCause           = ulErrCode;
        pstGetDynamicEpsQosInfoCnf->ulCidNum          = ulCidNum;

        if (0 != ulCidNum)
        {
            PS_MEM_CPY(pstGetDynamicEpsQosInfoCnf->astEpsQosInfo,
                       pstPsMsg->astEpsQosInfo,
                       (ulCidNum * sizeof(TAF_EPS_QOS_EXT_STRU)));
        }

        /* 将消息返回AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF,
                         pstGetDynamicEpsQosInfoCnf,
                         ulGetDynamicEpsQosInfoCnfLen);

        /* 释放内存 */
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicEpsQosInfoCnf);

        /* 从消息等待队列中删除该消息 */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF, ulPara);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiSetCgdcontCnfExpired_PreProc
 功能描述  : 发往L4A消息保护定时器超时预处理函数
             (TI_TAF_APS_WAIT_SET_CGDCONT_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgdcontCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGDCONT_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgdcontCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* 将失败消息返回给AT */
    TAF_APS_SndSetPrimPdpCtxInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* 从消息等待队列中删除该消息 */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDCONT_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiSetCgdscontCnfExpired_PreProc
 功能描述  : 发往L4A消息保护定时器超时预处理函数
             (TI_TAF_APS_WAIT_SET_CGDSCONT_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgdscontCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                         TI_TAF_APS_WAIT_SET_CGDSCONT_CNF,
                                                         pstRcvTimerMsg->ulPara))
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgdscontCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* 将失败消息返回给AT */
    TAF_APS_SndSetSecPdpCtxInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* 从消息等待队列中删除该消息 */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiSetCgtftCnfExpired_PreProc
 功能描述  : 发往L4A消息保护定时器超时预处理函数
             (TI_TAF_APS_WAIT_SET_CGTFT_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgtftCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGTFT_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgtftCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* 将失败消息返回给AT */
    TAF_APS_SndSetTftInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* 从消息等待队列中删除该消息 */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFT_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiSetCgautoCnfExpired_PreProc
 功能描述  : 发往L4A消息保护定时器超时预处理函数
             (TI_TAF_APS_WAIT_SET_CGAUTO_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgautoCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGAUTO_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgautoCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* 将失败消息返回给AT */
    TAF_APS_SndSetAnsModeInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* 从消息等待队列中删除该消息 */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGAUTO_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiSetCgeqosCnfExpired_PreProc
 功能描述  : 发往L4A消息保护定时器超时预处理函数
             (TI_TAF_APS_WAIT_SET_CGEQOS_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgeqosCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGEQOS_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgeqosCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* 将失败消息返回给AT */
    TAF_APS_SndSetCgeqosCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* 从消息等待队列中删除该消息 */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOS_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiSetAuthdataCnfExpired_PreProc
 功能描述  : 发往L4A消息保护定时器超时预处理函数
             (TI_TAF_APS_WAIT_SET_AUTHDATA_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetAuthdataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_AUTHDATA_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetAuthdataCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* 将失败消息返回给AT */
    (VOS_VOID)TAF_APS_SndSetAuthDataInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* 从消息等待队列中删除该消息 */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/* Add by w00199382 for V7代码同步, 2012-04-07, Begin   */
/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiGetLtecsCnfExpired_PreProc
 功能描述  : 发往L4A消息保护定时器超时预处理函数
             (TI_TAF_APS_WAIT_GET_LTE_CS_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : w00182550
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiGetLtecsCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiGetLtecsCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* 将失败消息返回给AT */
    TAF_APS_SndGetLtecsInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* 从消息等待队列中删除该消息 */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_LTE_CS_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiGetCemodeCnfExpired_PreProc
 功能描述  : 发往L4A消息保护定时器超时预处理函数
             (TI_TAF_APS_WAIT_GET_CEMODE_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiGetCemodeCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiGetCemodeCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* 将失败消息返回给AT */
    TAF_APS_SndGetCemodeInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* 从消息等待队列中删除该消息 */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_CEMODE_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiSetPdprofInfoExpired_PreProc
 功能描述  : 发往L4A消息保护定时器超时预处理函数
             (TI_TAF_APS_WAIT_SET_PDPROF_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年03月22日
    作    者   : x00126983
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetPdprofInfoExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_PDPROF_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetPdprofInfoExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* 将失败消息返回给AT */
    TAF_APS_SndSetPdprofInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* 从消息等待队列中删除该消息 */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_PDPROF_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}


/* Add by w00199382 for V7代码同步, 2012-04-07, End   */

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiSetCgcontrdpCnfExpired_PreProc
 功能描述  : 发往L4A消息保护定时器超时预处理函数
             (TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgcontrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl = {0};
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgcontrdpCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* 将失败消息返回给AT */
    (VOS_VOID)TAF_APS_SndGetDynamicPrimPdpCtxInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT, 0);

    /* 从消息等待队列中删除该消息 */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiSetCgscontrdpCnfExpired_PreProc
 功能描述  : 发往L4A消息保护定时器超时预处理函数
             (TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，从缓冲队列中获取消息

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgscontrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl = {0};
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgscontrdpCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* 将失败消息返回给AT */
    TAF_APS_SndGetDynamicSecPdpCtxInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT, 0);

    /* 从消息等待队列中删除该消息 */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiSetCgtftrdpCnfExpired_PreProc
 功能描述  : 发往L4A消息保护定时器超时预处理函数
             (TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgtftrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl = {0};
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgtftrdpCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* 将失败消息返回给AT */
    (VOS_VOID)TAF_APS_SndGetDynamicTftInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT, 0);

    /* 从消息等待队列中删除该消息 */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiSetCgeqosrdpCnfExpired_PreProc
 功能描述  : 发往L4A消息保护定时器超时预处理函数
             (TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : l00198894
    修改内容   : 新生成函数
  2.日    期 : 2013年07月08日
    作    者 : Y00213812
    修改内容 : VoLTE_PhaseI 项目，从缓冲队列中获取消息

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgeqosrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* 消息获取失败, 打印错误信息 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgeqosrdpCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* 将失败消息返回给AT */
    TAF_APS_SndGetCgeqosrdpCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* 从消息等待队列中删除该消息 */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_TransL4aErrorCode
 功能描述  : 转换L4A返回的错误码
 输入参数  : VOS_UINT32         ulL4aErrCode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月19日
    作    者   : l00198894
    修改内容   : 新生成函数

*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_TransL4aErrorCode(
    VOS_UINT32                          ulL4aErrCode
)
{
    /* 所有非成功的错误码均返回参数设置错误 */
    if (0 == ulL4aErrCode)
    {
        return TAF_PS_CAUSE_SUCCESS;
    }
    else
    {
        return TAF_PS_CAUSE_INVALID_PARAMETER;
    }
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmPdpSetupCnf_PreProc
 功能描述  : 收到ESM ID_APP_ESM_PDP_SETUP_CNF消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2015年12月7日
   作    者  : w00316404
   修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpSetupCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_SETUP_CNF_STRU         *pstCnf;

    pstCnf = (APP_ESM_PDP_SETUP_CNF_STRU*)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid((VOS_UINT8)pstCnf->ulCid))
    {
        /* 丢弃该消息 */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmNdisconnCnf_PreProc
 功能描述  : 收到ESM ID_APP_ESM_NDISCONN_CNF消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2015年12月7日
   作    者  : w00316404
   修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmNdisconnCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_NDISCONN_CNF_STRU          *pstCnf;

    pstCnf = (APP_ESM_NDISCONN_CNF_STRU*)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid((VOS_UINT8)pstCnf->ulCid))
    {
        /* 丢弃该消息 */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmApsPdpNanageInd_PreProc
 功能描述  : 收到ESM ID_APP_ESM_PDP_MANAGER_IND消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

 2.日    期   : 2013年07月08日
   作    者   : Y00213812
   修改内容   : VoLTE_PhaseI 项目，增加MODULE ID

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmApsPdpNanageInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_MANAGER_IND_STRU       *pstPdpManageInd;
    VOS_UINT8                           ucPdpId;
    TAF_CTRL_STRU                       stCtrl;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));
    /* MODULE ID默认设置为AT, 如果需要上报给IMSA的话，在网络侧上报
       SM_ESM_EPS_BEARER_INFO_IND_STRU消息后重新刷新 */
    stCtrl.ulModuleId   = WUEPS_PID_AT;
    stCtrl.usClientId   = TAF_APS_INVALID_CLIENTID;
    stCtrl.ucOpId       = TAF_APS_INVALID_OPID;

    pstPdpManageInd = (APP_ESM_PDP_MANAGER_IND_STRU*)pstMsg;

    /* 分配(PdP Id) */
    if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&stCtrl,
                                                       (VOS_UINT8)pstPdpManageInd->ulCid,
                                                       &ucPdpId))
    {
        /* 分配不到实体，打印异常，此时不应该分配不到实体 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmApsPdpNanageInd_PreProc, alloc pdp id fail");
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmApsPdpModifyCnf_PreProc
 功能描述  : 收到L4a ID_APP_ESM_PDP_MODIFY_CNF消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2015年12月7日
   作    者  : w00316404
   修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmApsPdpModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_MODIFY_CNF_STRU      *pstPdpModifyCnf;

    pstPdpModifyCnf = (APP_ESM_PDP_MODIFY_CNF_STRU*)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid((VOS_UINT8)pstPdpModifyCnf->ulCid))
    {
        /* 丢弃该消息 */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmApsPdpModifyInd_PreProc
 功能描述  : 收到ESM ID_APP_ESM_PDP_MODIFY_IND消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2015年12月7日
   作    者  : w00316404
   修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmApsPdpModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_MODIFY_IND_STRU      *pstPdpModifyInd;

    pstPdpModifyInd = (APP_ESM_PDP_MODIFY_IND_STRU*)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid((VOS_UINT8)pstPdpModifyInd->ulCid))
    {
        /* 丢弃该消息 */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmApsPdpReleaseCnf_PreProc
 功能描述  : 收到ESM ID_APP_ESM_PDP_RELEASE_CNF消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2015年12月7日
   作    者  : w00316404
   修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmApsPdpReleaseCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_RELEASE_CNF_STRU       *pstPdpReleaseCnf;

    pstPdpReleaseCnf = (APP_ESM_PDP_RELEASE_CNF_STRU*)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid((VOS_UINT8)pstPdpReleaseCnf->ulCid))
    {
        /* 丢弃该消息 */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmApsPdpDeactivateInd_PreProc
 功能描述  : 收到ESM ID_APP_ESM_PDP_RELEASE_IND消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

 2.日    期  : 2015年5月29日
   作    者  : a00165503
   修改内容  :  MODIFY for DTS2015051204781

 3.日    期   : 2015年12月7日
   作    者   : w00316404
   修改内容   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmApsPdpDeactivateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_RELEASE_IND_STRU       *pstPdpDeactInd;
    VOS_UINT8                           ucPdpId;

    pstPdpDeactInd = (APP_ESM_PDP_RELEASE_IND_STRU*)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (VOS_TRUE == pstPdpDeactInd->bitOpLinkCid)
    {
        ucPdpId = TAF_APS_GetPdpIdByCid((VOS_UINT8)pstPdpDeactInd->ulCid);
    }
    else
    {
        ucPdpId = TAF_APS_GetPdpIdByEpsbId(pstPdpDeactInd->ulEpsbId);
    }

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* 丢弃该消息 */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmApsPdpSetupInd_PreProc
 功能描述  : 收到ID_APP_ESM_PDP_SETUP_IND消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月19日
    作    者   : w00316404
    修改内容   : 新生成函数

  2.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmApsPdpSetupInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_SETUP_IND_STRU         *pstPdpSetupInd;
    VOS_UINT8                           ucPdpId;

    pstPdpSetupInd = (APP_ESM_PDP_SETUP_IND_STRU*)pstMsg;

    if (VOS_TRUE == pstPdpSetupInd->bitOpLinkCid)
    {
        /* 从消息中所带的Cid来查找对应的PDP ID */
        ucPdpId = TAF_APS_GetPdpIdByCid((VOS_UINT8)(pstPdpSetupInd->ulCid));
    }
    else
    {
        /* 从消息中所带的RabId来查找对应的PDP ID */
        ucPdpId = TAF_APS_GetPdpIdByEpsbId(pstPdpSetupInd->ulRabId);
    }

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* 丢弃该消息 */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmEpsBearInfoInd_PreProc
 功能描述  : 收到Esm SM_ESM_EPS_BEARER_INFO_IND_STRU相关消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
  1.日    期  : 2011年12月22日
    作    者  : h44270
    修改内容  : 新生成函数

  2.日    期   : 2012年4月16日
    作    者   : A00165503
    修改内容   : DTS2012040100697: 自动应答模式下, 网侧建立的ESP承载, 用户不
                 能修改和去激活

  3.日    期  : 2015年5月29日
    作    者  : a00165503
    修改内容  :  MODIFY for DTS2015051204781
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmEpsBearInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    TAF_CTRL_STRU                       stCtrl;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));
    /* MODULE ID默认设置为AT, 如果需要上报给IMSA的话，在网络侧上报
       SM_ESM_EPS_BEARER_INFO_IND_STRU消息后重新刷新 */
    stCtrl.ulModuleId   = WUEPS_PID_AT;
    stCtrl.usClientId   = TAF_APS_INVALID_CLIENTID;
    stCtrl.ucOpId       = TAF_APS_INVALID_OPID;
    /* Modified by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    pstBearerInfo = (SM_ESM_EPS_BEARER_INFO_IND_STRU*)pstMsg;


    ucCid = TAF_APS_GetCidFromLteBitCid(pstBearerInfo->ulBitCid);

    /* Cid的值无效，则直接返回 */
    if ( TAF_INVALID_CID == ucCid )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, invalid Cid");
        return VOS_TRUE;
    }

    /* 正常情况下，按照CID来查找Pdp Id */
    if (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption)
    {
        ucPdpId = TAF_APS_GetPdpIdByCid(ucCid);
    }
    else
    {
        ucPdpId = TAF_APS_GetPdpIdByEpsbId(pstBearerInfo->ulEpsbId);
    }

    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, invalid Cid");
        return VOS_FALSE;
    }
    else
    {
        /* 自动应答模式下, 需要分配新的APS实体来存储承载信息 */
        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, Get PDP ID fail.");
    }


    /* cid为0时，表示是默认承载，此时如果是激活，则分配一个新的PDP ID
       client id和op id此时认为是无效值，后面真正激活时，再进行刷新
    */
    if ( ((TAF_APS_DEFAULT_CID == ucCid) || (ucCid > APS_PDP_MAX_CID))
      && (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption) )
    {
        /* 分配(PdP Id) */
        if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&stCtrl,
                                                           ucCid,
                                                           &ucPdpId))
        {
            /* 分配不到实体，打印异常，此时不应该分配不到实体 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, alloc pdp id fail");
            return VOS_TRUE;
        }

        /* 记录默认承载的标志 */
        if (TAF_APS_DEFAULT_CID == ucCid)
        {
           TAF_APS_SetPdpEntAttachBearerFlag(ucPdpId, VOS_TRUE);
        }
    }
    else
    {
        /* 异常消息, 丢弃 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, Abnormal EPS Bearer.");
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmNotificationInd_PreProc
 功能描述  : ID_EMS_APS_NOTIFICATION_IND处理函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmNotificationInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    ESM_APS_NOTIFICATION_IND_STRU      *pstEsmNotiInd;

    pstEsmNotiInd = (ESM_APS_NOTIFICATION_IND_STRU*)pstMsg;

    /* 发送消息 */
    TAF_APS_SndImsaSrvccCancelNotify(pstEsmNotiInd->enNotificationIndicator);

    return VOS_TRUE;
}

#endif

#endif

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSndcpActivateRsp_PreProc
 功能描述  : 收到Sndcp APS_SN_ACT_RSP_MSG_TYPE消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_SNDCP_ACTIVATE_RSP_MSG         *pstSnActRsp;

    pstSnActRsp = (APS_SNDCP_ACTIVATE_RSP_MSG*)pstMsg;

    /* 从SNDCP的消息中获取NSAPI,如果获取不到则丢弃 */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByNsapi(pstSnActRsp->ApsSnActRsp.ucNsapi))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSndcpModifyRsp_PreProc
 功能描述  : 收到Sndcp APS_SN_MDF_RSP_MSG_TYPE消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpModifyRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_SNDCP_MODIFY_RSP_MSG           *pstSnModifyRsp;

    pstSnModifyRsp = (APS_SNDCP_MODIFY_RSP_MSG*)pstMsg;

    /* 从SNDCP的消息中获取NSAPI,如果获取不到则丢弃 */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByNsapi(pstSnModifyRsp->ApsSnMdfRsp.ucNsapi))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvSndcpDeactRsp_PreProc
 功能描述  : 收到Sndcp APS_SN_DEACT_RSP_MSG_TYPE消息的预处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
 1.日    期  : 2011年12月22日
   作    者  : h44270
   修改内容  : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpDeactRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_SNDCP_DEACTIVATE_RSP_MSG           *pstSnDeactRsp;

    pstSnDeactRsp = (APS_SNDCP_DEACTIVATE_RSP_MSG*)pstMsg;

    /* 从SNDCP的消息中获取NSAPI,如果获取不到则丢弃 */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByNsapi(pstSnDeactRsp->ApsSnDeActRsp.ucNsapi))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : TAF_APS_RcvNdIpv6ParaInfoNotifyInd_PreProc
 功能描述  : 收到NDCLINET的ID_NDCLIENT_APS_PARA_INFO_NOTIFY消息的预处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月2日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常
  3.日    期   : 2012年12月11日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，增加PID记录到实体
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvNdIpv6ParaInfoNotifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_CTRL_STRU                       stCtrl;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;
    NDCLIENT_APS_PARA_INFO_NOTIFY_STRU *pstNdIpv6ParaInfoNotifyInd;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;


    PS_MEM_SET(&stCtrl, 0x00, sizeof(stCtrl));

    /* 初始化, 获取消息内容 */
    pstNdIpv6ParaInfoNotifyInd = (NDCLIENT_APS_PARA_INFO_NOTIFY_STRU*)pstMsg;

    /* 获取NSAPI对应的APS实体索引 */
    ucPdpId = TAF_APS_GetPdpIdByNsapi(pstNdIpv6ParaInfoNotifyInd->ucRabId);
    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        /* 获取该PDPID的PDP实体内容地址 */
        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        /* 更新APS实体的RA参数信息 */
        pstPdpEntity->bitOpIpv6RaInfo = VOS_TRUE;
        PS_MEM_CPY((VOS_CHAR*)&pstPdpEntity->stIpv6RaInfo,
                   (VOS_CHAR*)&pstNdIpv6ParaInfoNotifyInd->stIpv6Info,
                   sizeof(NDCLIENT_APS_IPV6_INFO_STRU));

#if (FEATURE_ON == FEATURE_LTE)
        /* 同步RA信息给ESM */
        (VOS_VOID)TAF_APS_SndL4aIpv6InfoNotifyInd(pstPdpEntity->ucNsapi,
                                        &pstPdpEntity->stIpv6RaInfo);
#endif

        /* 检查当前接入技术, 如果是GU模, 需要配置IPF */
        enRatType = TAF_APS_GetCurrPdpEntityRatType();

        if ( (TAF_APS_RAT_TYPE_GSM   == enRatType)
          || (TAF_APS_RAT_TYPE_WCDMA == enRatType) )
        {
            TAF_APS_IpfConfigUlFilter(ucPdpId);
        }

        /* 如果已经收到DHCP的回复消息，可以上报，否则设置NDCLIENT标志位 */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if ((TAF_APS_RAT_TYPE_1X    == enRatType)
         || (TAF_APS_RAT_TYPE_HRPD  == enRatType)
         || (TAF_APS_RAT_TYPE_EHRPD == enRatType))
        {
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            if (TAF_APS_RAT_TYPE_EHRPD == enRatType)
            {
                /* 通知EHSM刷新IPV6地址 */
                TAF_APS_SndEhsmPdnCtxInfoNotify(ucPdpId, EHSM_APS_PDN_OPTION_MODIFIED);
            }

            if (VOS_TRUE == pstPdpEntity->ucRcvDhcpDnsFlgIpv6)
            {

                /* 如果已经上报清标志位 */
                pstPdpEntity->ucRcvNdClientNtyFlg = VOS_FALSE;
                pstPdpEntity->ucRcvDhcpDnsFlgIpv4 = VOS_FALSE;
                pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_FALSE;
            }
            else
            {
                pstPdpEntity->ucRcvNdClientNtyFlg = VOS_TRUE;

                return VOS_TRUE;
            }

        }
#endif

        /* 检查当前APS是否有用户使用, 如果有用户使用, 上报RA信息事件 */
        if ((TAF_APS_INVALID_CLIENTID != TAF_APS_GetPdpEntClientId(ucPdpId, pstPdpEntity->stClientInfo.ucCid))
         && (VOS_TRUE == pstPdpEntity->ulUsedFlg))
        {
            /* 填写APP控制头 */
            TAF_APS_SetPsCallEvtCtrl(ucPdpId, pstPdpEntity->stClientInfo.ucCid, &stCtrl);

            /* 上报ID_EVT_TAF_PS_IPV6_INFO_IND事件 */
            TAF_APS_SndIpv6RaInfoNotifyInd(&stCtrl,
                                           pstPdpEntity->stClientInfo.ucCid,
                                           pstPdpEntity->ucNsapi,
                                           (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
        }
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvNdIpv6ParaInfoNotifyInd_PreProc: Can't find PDP ID form RAB ID!");
    }

    return VOS_TRUE;
}

#endif

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGetGprsActiveTypeReq_PreProc
 功能描述  : 获取PPP拨号CID对应的PDP类型
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史    :
   1.日    期  : 2011年12月22日
     作    者  : A00165503
     修改内容  : 新生成函数

  2.日    期   : 2014年1月13日
    作    者   : A00165503
    修改内容   : DTS2013122609183: L2P参数处理优化, 直接根据CID上下文中定义
                 的PDP类型决定
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetGprsActiveTypeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                              ulErrCode;
    TAF_PDP_TYPE_ENUM_UINT8                 enPdpType;
    TAF_CID_GPRS_ACTIVE_TYPE_STRU           stCidGprsActiveType;
    TAF_PS_MSG_STRU                        *pstAppMsg;
    TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU *pstGetGprsActiveTypeReq;

    /* 初始化 */
    ulErrCode               = TAF_PARA_OK;
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstGetGprsActiveTypeReq = (TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU*)(pstAppMsg->aucContent);

    /* 获取GPRS激活类型 */
    PS_MEM_SET(&stCidGprsActiveType, 0x00, sizeof(TAF_CID_GPRS_ACTIVE_TYPE_STRU));
    stCidGprsActiveType.ucCid = pstGetGprsActiveTypeReq->stAtdPara.ucCid;

    enPdpType = Taf_GetCidType(pstGetGprsActiveTypeReq->stAtdPara.ucCid);

    /* 删除L2P协议类型的判断处理 */

    /* 直接根据CID上下文的PDP类型决定创建PPP实体类型 */
    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            /* IP类型,进行IP激活，TE中启动了PPP，MT中启动PPP */
            stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
        case TAF_PDP_IPV4V6:
            /* IP类型,进行IP激活，TE中启动了PPP，MT中启动PPP */
            stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
            break;
#endif

        case TAF_PDP_PPP:
            /* PPP类型,进行PPP激活，TE中启动了PPP，MT中不启动PPP */
            stCidGprsActiveType.enActiveType = TAF_PPP_ACTIVE_TE_PPP_MT_NOT_PPP_TYPE;
            break;

        default:
            ulErrCode = TAF_PS_CAUSE_INVALID_PARAMETER;
            break;
    }

    (VOS_VOID)TAF_APS_SndGetGprsActiveTypeCnf(&(pstGetGprsActiveTypeReq->stCtrl),
                                   ulErrCode,
                                   &stCidGprsActiveType);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetDnsQueryReq_PreProc
 功能描述  : 查询指定的PDP激活后，与网侧协商的主DNS、辅DNS信息的预处理函数
             (ID_MSG_TAF_PS_GET_NEGOTIATION_DNS_REQ)
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月20日
    作    者   : l00198894
    修改内容   : 新生成函数

  2.日    期   : 2012年10月17日
    作    者   : l00198894
    修改内容   : DTS2012101606439, 增加DNS默认值回复
  3.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，结构替换

  4.日    期   : 2015年4月20日
    作    者   : Y00213812
    修改内容   : 增加CDMA模式后需要考虑dormant状态和discing状态
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetDnsQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                        *pstPsMsg        = VOS_NULL_PTR;
    TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU    *pstNegoDnsReq   = VOS_NULL_PTR;
    TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU     stNegoDnsCnf;
    VOS_UINT8                               ucPdpId         = TAF_APS_INVALID_PDPID;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity    = VOS_NULL_PTR;
    TAF_APS_STA_ENUM_UINT32                 enStaState      = TAF_APS_STA_BUTT;
    TAF_APS_CDATA_PS_STATE_ENUM_UINT8       enCdataPsState;

    /* 初始化 */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstNegoDnsReq   = (TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU *)pstPsMsg->aucContent;
    ucPdpId         = TAF_APS_GetPdpIdByCid(pstNegoDnsReq->ucCid);
    PS_MEM_SET(&stNegoDnsCnf, 0, sizeof(stNegoDnsCnf));

    /* 填写消息内容 */
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    stNegoDnsCnf.stCtrl                 = pstNegoDnsReq->stCtrl;
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

    stNegoDnsCnf.enCause                = TAF_PS_CAUSE_UNKNOWN;

    /* 获取CID对应的PdpId */
    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        enCdataPsState = TAF_APS_GetPdpEntCdataPsState(ucPdpId);

        /* 检查该CID对应PDP是否激活 */
        enStaState  = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
        if ( (TAF_APS_STA_ACTIVE            == enStaState)
          || (TAF_APS_STA_MS_MODIFYING      == enStaState)
          || (TAF_APS_STA_MS_DEACTIVATING   == enStaState)
          || (TAF_APS_STA_CDATA_DISCING     == enStaState)
          || (TAF_APS_CDATA_PS_STATE_ACTIVE == enCdataPsState) )
        {
            /* 获取该PDPID的PDP实体内容地址 */
            pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

            /* 获取该激活PDP对应的主DNS, 辅DNS信息 */
            stNegoDnsCnf.stNegotiationDns.ucCid = pstNegoDnsReq->ucCid;
            stNegoDnsCnf.enCause = TAF_PS_CAUSE_SUCCESS;
            stNegoDnsCnf.stNegotiationDns.stDnsInfo.bitOpPrimDnsAddr = VOS_TRUE;
            stNegoDnsCnf.stNegotiationDns.stDnsInfo.bitOpSecDnsAddr  = VOS_TRUE;

            if (VOS_TRUE == pstPdpEntity->PdpDnsFlag)
            {
                if (VOS_TRUE == pstPdpEntity->PdpDns.OP_PriDns)
                {
                    PS_MEM_CPY(stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucPrimDnsAddr,
                               pstPdpEntity->PdpDns.aucPriDns,
                               TAF_IPV4_ADDR_LEN);
                }

                if (VOS_TRUE == pstPdpEntity->PdpDns.OP_SecDns)
                {
                    PS_MEM_CPY(stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucSecDnsAddr,
                               pstPdpEntity->PdpDns.aucSecDns,
                               TAF_IPV4_ADDR_LEN);
                }
            }
        }
    }

    /* 将处理结果返回AT模块 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_NEGOTIATION_DNS_CNF,
                     &stNegoDnsCnf,
                     sizeof(TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU));

    return VOS_TRUE;
}





/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiApsLimitPdpActExpired_PreProc
 功能描述  : 暂停PDP激活定时器超时预处理函数(AT&T DCM定制，PDP激活受限
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月16日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiApsLimitPdpActExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiApsMsActvaingExpired_PreProc
 功能描述  : APS发起的PDP激活超时预处理函数(AT&T DCM定制，PDP激活受限
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月16日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiApsMsActvaingExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* PDP激活受限处理:此定时器超时认为异常,PDP激活次数按一次处理 */
    TAF_APS_ProcPdpActLimit_PreProc(1);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetActPdpLimitTimerLen
 功能描述  : 产生暂停PDP激活定时器的时长(AT&T DCM定制，PDP激活受限
 输入参数  : VOS_UINT8 ucFailCount
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月16日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_GetActPdpLimitTimerLen(
    VOS_UINT8                           ucFailCount
)
{
    VOS_UINT32                          ulTimeLen;

    ulTimeLen = 0;

    /* 暂停PDP激活定时器时长随着激活失败的次数来确定，小于等于10次直接返回时长0.
    11-18次按照10s步长递增时长，大于18次的统一使用90s时长 */
    if (ucFailCount <= TAF_APS_PDP_ACT_LIMIT_NO_DELAY_COUNT_THRESHOLD)
    {
        return 0;
    }

    /* PDP激活被拒11-19次之内，按照10s步长递增启动定时器 */
    if (ucFailCount < TAF_APS_PDP_ACT_LIMIT_STEP_DELAY_COUNT_THRESHOLD)
    {
        ulTimeLen = (ucFailCount - TAF_APS_PDP_ACT_LIMIT_NO_DELAY_COUNT_THRESHOLD)
                        * TAF_APS_PDP_ACT_LIMIT_STEP_TIME;
    }
    else
    {   /* PDP激活被拒19次(包括19次)以上，按照90s时长启动定时器 */
        /* 当失败次数是10的整数倍时，PDP暂停激活定时器使用随机时长 */
        if (0 == (ucFailCount % TAF_APS_PDP_ACT_LIMIT_RANDOM_TIME_FAILCOUNT))
        {
            ulTimeLen = TAF_APS_PDP_ACT_LIMIT_AVERAGE_DELAY_TIME
                        + VOS_Rand(TAF_APS_PDP_ACT_LIMIT_RANDOM_TIME_THRESHOLD);
        }
        else
        {
            ulTimeLen = TAF_APS_PDP_ACT_LIMIT_AVERAGE_DELAY_TIME;
        }
    }

    /* 定时器时长单位为ms */
    return (ulTimeLen * TIMER_S_TO_MS_1000);
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcPdpActLimit_PreProc
 功能描述  : 收到激活被拒、主动去激活或者激活超时，处理激活受限
 输入参数  : VOS_UINT8 ucTryingCount
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月15日
    作    者   : M00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcPdpActLimit_PreProc(VOS_UINT8 ucTryingCount)
{
    TAF_APS_PDP_ACT_LIMIT_INFO_STRU    *pstPdpActLimitInfo;

    pstPdpActLimitInfo = TAF_APS_GetPdpActLimitInfoAddr();

    /* 判断PDP激活受限功能是否打开 */
    if (VOS_TRUE == pstPdpActLimitInfo->ucPdpActLimitFlg)
    {
        pstPdpActLimitInfo->ucPdpActFailCount = pstPdpActLimitInfo->ucPdpActFailCount + ucTryingCount;

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
        {
            return;
        }

        if (pstPdpActLimitInfo->ucPdpActFailCount > TAF_APS_PDP_ACT_LIMIT_NO_DELAY_COUNT_THRESHOLD)
        {
            TAF_APS_StartTimer(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_GetActPdpLimitTimerLen(pstPdpActLimitInfo->ucPdpActFailCount), TAF_APS_PDP_ACT_LIMIT_PDP_ID);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_IsPdpActLimit_PreProc
 功能描述  : 判断是不是PDP激活受限
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月30日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_IsPdpActLimit_PreProc(VOS_VOID)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    enCurrRatType        = TAF_APS_GetCurrPdpEntityRatType();

    /* PS域无效，到状态机中处理 */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        return VOS_FALSE;
    }

    /* 目前PDP激活受限的功能只适用于GU模 */
    if ((TAF_APS_RAT_TYPE_GSM == enCurrRatType)
     || (TAF_APS_RAT_TYPE_WCDMA == enCurrRatType))
    {
        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_PdpActLimit_PreProc
 功能描述  : 收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ，PDP激活受限的预处
             理
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月4日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_PdpActLimit_PreProc(
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq
)
{
    if (VOS_TRUE == TAF_APS_IsPdpActLimit_PreProc())
    {
        /* 不处理去激活 */
        if (TAF_CGACT_ACT != pstSetPdpStateReq->stCidListStateInfo.ucState)
        {
            return VOS_FALSE;
        }

        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvOmSetDsflowRptReq_PreProc
 功能描述  : 收到ID_NAS_OM_SET_DSFLOW_RPT_REQ，设置OM流量上报信息
 输入参数  : ulEventType        -- 事件类型
             pstMsg             -- 消息信息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月09日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目新增函数

  2.日    期   : 2015年7月09日
    作    者   : wx270776
    修改内容   : OM融合

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvOmSetDsflowRptReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by wx270776 for OM融合, 2015-7-1, begin */
    NAS_OM_SET_DSFLOW_RPT_REQ_STRU     *pstDsflowRptReq = VOS_NULL_PTR;
    NAS_OM_SET_DSFLOW_RPT_CNF_STRU     *pstDsflowRptCnf = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx = VOS_NULL_PTR;//global
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulRet;

    /* 申请消息 */
    ulMsgLen        = sizeof(NAS_OM_SET_DSFLOW_RPT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstDsflowRptCnf = (NAS_OM_SET_DSFLOW_RPT_CNF_STRU*)PS_ALLOC_MSG(WUEPS_PID_TAF, ulMsgLen);
    if (VOS_NULL_PTR == pstDsflowRptCnf)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvOmSetDsflowRptReq_PreProc: PS_MEM_ALLOC Failed!");

        return VOS_FALSE;
    }

    /* 初始化 */
    PS_MEM_SET((VOS_UINT8*)pstDsflowRptCnf + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

    pstDsflowRptReq = (NAS_OM_SET_DSFLOW_RPT_REQ_STRU*)pstMsg;

    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* 更新OM流量上报标志位 */
    switch(pstDsflowRptReq->enRptAction)
    {
        case NAS_OM_REPORT_START:
            if ( (pstDsflowRptReq->usRptPeriod >= TI_TAF_APS_DSFLOW_REPORT_LEN)
              && (0 == (pstDsflowRptReq->usRptPeriod % TI_TAF_APS_DSFLOW_REPORT_LEN)) )
            {
                pstApsDsFlowCtx->ucDsFlowOMReportFlg    = VOS_TRUE;
                pstApsDsFlowCtx->ucDsFlowOMRptPeriod    = (VOS_UINT8)(pstDsflowRptReq->usRptPeriod / TI_TAF_APS_DSFLOW_REPORT_LEN);
                pstDsflowRptCnf->enResult                 = NAS_OM_RESULT_NO_ERROR;
            }
            else
            {
                pstDsflowRptCnf->enResult                 = NAS_OM_RESULT_INCORRECT_PARAMETERS;
            }
            break;
        case NAS_OM_REPORT_STOP:
            pstApsDsFlowCtx->ucDsFlowOMReportFlg        = VOS_FALSE;
            pstApsDsFlowCtx->ucDsFlowOMRptPeriod        = 0;
            break;
        default:
            pstDsflowRptCnf->enResult                     = NAS_OM_RESULT_INCORRECT_PARAMETERS;
            break;
    }

    /* 填充消息内容 */
    pstDsflowRptCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstDsflowRptCnf->ulMsgId          = ID_NAS_OM_SET_DSFLOW_RPT_CNF;
    pstDsflowRptCnf->usOriginalId     = pstDsflowRptReq->usOriginalId;
    pstDsflowRptCnf->usTerminalId     = pstDsflowRptReq->usTerminalId;
    pstDsflowRptCnf->ulTimeStamp      = pstDsflowRptReq->ulTimeStamp;
    pstDsflowRptCnf->ulSN             = pstDsflowRptReq->ulSN;


    /* 发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstDsflowRptCnf);
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("NAS_MMC_SndOmOtaCnf:WARNING: Send msg fail.");

        return VOS_FALSE;
    }



    return VOS_TRUE;
    /* Modified by wx270776 for OM融合, 2015-7-1, end */

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvMmcServiceStatusInd_PreProc
 功能描述  : 收到ID_MMC_APS_SERVICE_STATUS_IND，预处理
 输入参数  : ulEventType        -- 事件类型
             pstMsg             -- 消息信息
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月30日
    作    者   : m00217266
    修改内容   : 新增，主要用于记录ID_MMC_APS_SERVICE_STATUS_IND消息处理之前pdp实体的接入技术
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMmcServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*
        1）CDMA编译宏打开时，MMC不再给CDS发消息通知接入技术切换，只通知给APS
        2）GUL模式下，由APS通知CDS接入技术变更，同时APS 3GPP状态机对模式变更处理的逻辑不变；
        3）CL模式下，MMC上报NULL给APS，APS根据当前数据业务所在的模式决定是否通知CDS
            1.LTE下，APS通知CDS接入技术为NULL，APS内部的处理与GUL保持一致；
            2.DO下，APS通知CDS接入技术为NULL，只在预处理处理本消息；
            3.1X下，APS忽略该消息，不通知CDS；
        4）CL模式下，MMC上报LTE给APS，APS根据当前数据业务所在的模式决定如何处理
            1.LTE下，APS通知CDS接入技术为LTE，APS内部的处理与GUL保持一致；
            2.DO下，APS忽略该消息，继续等待MMA的服务状态通知，然后再通知CDS；
            3.1X下，APS忽略该消息，继续等待MMA的服务状态通知，DORMANT态直接通知CDS，
              ACTIVE状态不通知，等去激活完成后无条件通知CDS当前的接入技术；
    */

    MMC_APS_SERVICE_STATUS_IND_STRU    *pstSerStaInd;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enLastRatType;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrDataServiceMode;
#endif

    /* 初始化, 获取消息内容 */
    pstSerStaInd  = (MMC_APS_SERVICE_STATUS_IND_STRU*)pstMsg;
    enRatType     = TAF_APS_ConvertMmcRatType(pstSerStaInd->enRatType);
    enLastRatType = TAF_APS_GetCurrPdpEntityRatType();

    /* 更新的PS域卡状态 */
    TAF_APS_SetCurrPdpEntitySimRegStatus(pstSerStaInd->ulPsSimRegStatus);

    if (TAF_APS_RAT_TYPE_NULL != enRatType)
    {
         /* 记录可用的PS域状态，在挂起时使用 */
        TAF_APS_SET_RAT_TYPE_IN_SUSPEND(enRatType);

    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    enCurrDataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();

    if (TAF_APS_RAT_TYPE_NULL != enRatType)
    {

        if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
        {
            /* 设置接入技术 */
            if (TAF_APS_RAT_TYPE_LTE == enCurrDataServiceMode)
            {
                TAF_APS_SetCurrPdpEntityRatType(enRatType);
            }

            /* 通知CDS当前接入技术改变 */
            if (VOS_TRUE == TAF_APS_IsNeedNotifyCdsModeChange(enRatType, enCurrDataServiceMode))
            {
                TAF_APS_SndCdsModeChangeInd(enRatType);
            }
        }
        else
        {
            TAF_APS_SetCurrPdpEntityRatType(enRatType);
            TAF_APS_SndCdsModeChangeInd(enRatType);
        }
    }
    else
    {
        if (TAF_APS_RAT_TYPE_1X == enCurrDataServiceMode)
        {
            /* 如果原来是1X模式，不处理MMC上报的NULL的通知 */
            return VOS_TRUE;
        }
        else if ((TAF_APS_RAT_TYPE_HRPD  == enCurrDataServiceMode)
              || (TAF_APS_RAT_TYPE_EHRPD == enCurrDataServiceMode))
        {
            /* 通知CDS当前接入技术改变,不进状态机处理 */
            TAF_APS_SndCdsModeChangeInd(enRatType);

            return VOS_TRUE;
        }
        else
        {
            TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_NULL);
        }
    }

    TAF_APS_LogOldNewPdpRatType(TAF_APS_GetCurrPdpEntityRatType(), enLastRatType);

    /* CL模式下，数据业务非LTE模式，不进状态机处理 */
    if ((VOS_TRUE == TAF_SDC_IsConfigCLMode())
     && (TAF_APS_RAT_TYPE_LTE != enCurrDataServiceMode))
    {
        return VOS_TRUE;
    }

#else

    /* 上报当前的接入技术模式 */
    TAF_APS_LogOldNewPdpRatType(enRatType, enLastRatType);

    TAF_APS_SetCurrPdpEntityRatType(enRatType);

#endif

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* 如果当前PDP实体不为INACTIVE状态，则发送内部消息进状态机处理 */
        if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucPdpId))
        {
            /* 内部消息中携带的是MMC上报的服务状态，不能用上下文中的
               状态机处理此内部消息时，使用消息中携带的信息
            */
            (VOS_VOID)TAF_APS_SndInterServiceStatusChangeInd(ucPdpId,
                                                   enRatType,
                                                   enLastRatType,
                                                   pstSerStaInd->ulPsSimRegStatus,
                                                   VOS_FALSE,
                                                   TAF_APS_INTER_SERVICE_RESULT_LTE);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_Aps_RcvGetCidSdfReq
 功能描述  : 用于获取所有NV项中的SDF配置信息预处理
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月09日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsGetCidSdfReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucNum;
    TAF_PS_SDF_INFO_REQ_STRU           *pstSdfInfoReq;
    TAF_PS_SDF_INFO_CNF_STRU           *pstSdfInfoCnf;

    pstSdfInfoReq = (TAF_PS_SDF_INFO_REQ_STRU *)pstMsg;

    /* 申请消息内存 */
    pstSdfInfoCnf = (TAF_PS_SDF_INFO_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                            sizeof(TAF_PS_SDF_INFO_CNF_STRU));

    /* 申请消息失败 */
    if ( VOS_NULL_PTR == pstSdfInfoCnf )
    {
        MN_ERR_LOG("TAF_APS_RcvPsGetCidSdfReq_PreProc:  ERROR : PS_MEM_ALLOC Error!");
        return VOS_TRUE;
    }

    PS_MEM_SET(pstSdfInfoCnf, 0, sizeof(TAF_PS_SDF_INFO_CNF_STRU));

    /* 填写消息头 */
    pstSdfInfoCnf->stCtrl = pstSdfInfoReq->stCtrl;

    for (ucNum = 1; ucNum <= TAF_MAX_CID_NV; ucNum++)
    {
        if (VOS_OK == TAF_APS_GetSdfParaInfo(ucNum,
                              &(pstSdfInfoCnf->stSdfInfo.astSdfPara[pstSdfInfoCnf->stSdfInfo.ulSdfNum])))
        {
            pstSdfInfoCnf->stSdfInfo.ulSdfNum ++;
        }
    }

    /* 发送ID_MSG_TAF_GET_CID_SDF_CNF消息 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_CID_SDF_CNF,
                     (VOS_VOID *) pstSdfInfoCnf,
                     sizeof(TAF_PS_SDF_INFO_CNF_STRU));

    /* 释放用于存放SDF参数的内存 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstSdfInfoCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSetImsPdpCfgReq_PreProc
 功能描述  : 设置PDP是否支持IMS
 输入参数  : VOS_VOID                           *pMsgData
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月29日
    作    者   : z00301431
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSetImsPdpCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_CID_IMS_CFG_TBL_STRU       *pstCidImsCfgTbl;
    TAF_PS_SET_IMS_PDP_CFG_REQ_STRU    *pstSetImsPdpCfgReq;
    TAF_PS_SET_IMS_PDP_CFG_CNF_STRU     stSetImsPdpCfgCnf;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucImsFlag;

    enCause             = TAF_PS_CAUSE_SUCCESS;
    pstSetImsPdpCfgReq  = (TAF_PS_SET_IMS_PDP_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    ucCid       = pstSetImsPdpCfgReq->stImsPdpCfg.ucCid;
    ucImsFlag   = pstSetImsPdpCfgReq->stImsPdpCfg.ucImsFlag;

    /* 判断CID有效性 */
    if (!(TAF_PS_PDP_CONTEXT_CID_VALID(ucCid)))
    {
        enCause = TAF_PS_CAUSE_CID_INVALID;
    }
    else
    {
        /* 设置CID的IMS配置 */
        pstCidImsCfgTbl = TAF_APS_GetCidImsCfgTable();
        pstCidImsCfgTbl->aucImsFlag[ucCid] = ucImsFlag;
    }

    PS_MEM_SET(&stSetImsPdpCfgCnf, 0, sizeof(TAF_PS_SET_IMS_PDP_CFG_CNF_STRU));

    /* 填写消息头 */
    stSetImsPdpCfgCnf.stCtrl  = pstSetImsPdpCfgReq->stCtrl;
    stSetImsPdpCfgCnf.enCause = enCause;

    /* 发送ID_EVT_TAF_PS_SET_IMS_PDP_CFG_CNF消息 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_IMS_PDP_CFG_CNF,
                               &stSetImsPdpCfgCnf,
                               sizeof(TAF_PS_SET_IMS_PDP_CFG_CNF_STRU));

    return VOS_TRUE;
}

/* Added by m00217266 for L-C互操作项目, 2014-2-12, begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 函 数 名  : TAF_APS_LC_Check_Req_Valid
 功能描述  : 在LC互操作模式下，检查请求的有效性
 输入参数  : TAF_CTRL_STRU
 输出参数  : 无
 返 回 值  : VOS_UINT8,
             0:无效请求
             1:有效请求
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_APS_LCCheckReqValid(
    TAF_CTRL_STRU                       *pstCtrlInfo
)
{
    TAF_PH_MODE                         ucPhMode;

    ucPhMode                            = MMA_GetCurrPhMode();

    /* 非开机状态，不做限制 */
    if (TAF_PH_MODE_FULL != ucPhMode)
    {
        return VOS_TRUE;
    }
    /* 在L+C互操作场景下，非CMMCA下发请求不做处理 */
    if ((VOS_TRUE        == TAF_SDC_IsConfigCLInterWorkCOutside())
     && (WUEPS_PID_CMMCA != pstCtrlInfo->ulModuleId))
    {
        return VOS_FALSE;
    }

    /* 在非L+C互操作场景下，CMMCA下发请求不做处理 */
    if ((VOS_FALSE       == TAF_SDC_IsConfigCLInterWorkCOutside())
     && (WUEPS_PID_CMMCA == pstCtrlInfo->ulModuleId))
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}
#endif
/* Added by m00217266 for L-C互操作项目, 2014-2-12, end */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDataCallSuspendInd_PreProc
 功能描述  : 收到ID_XCC_APS_DATA_CALL_SUSPEND_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataCallSuspendInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_SUSPEND_IND_STRU *pstSuspendInd = VOS_NULL_PTR;

    pstSuspendInd = (XCC_APS_DATA_CALL_SUSPEND_IND_STRU *)pstMsg;

    TAF_APS_SET_CDATA_SUSPEND_STATUS(TAF_APS_CDMA_TC_SUSPENDED);


    /* TO DO:需在状态机中处理该消息 */

    /* DMT测试时，如果g_ulApsTestStub为TRUE，则不回复SUSPEND_RSP消息 */
    if (VOS_FALSE == g_ulApsTestStub)
    {
        TAF_APS_SndXccDataCallSuspendRsp(pstSuspendInd->ucConnectId);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDataCallResumeInd_PreProc
 功能描述  : 收到ID_XCC_APS_DATA_CALL_RESUME_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataCallResumeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_RESUME_IND_STRU  *pstResumeInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    VOS_UINT32                          ulExist1XService;
    VOS_UINT8                           ucPdpId;



    /* 获取消息内容 */
    pstResumeInd            = (XCC_APS_DATA_CALL_RESUME_IND_STRU *)pstMsg;
    ulExist1XService        = TAF_APS_Get1XPsServiceStatus();

    TAF_APS_SET_CDATA_SUSPEND_STATUS(TAF_APS_CDMA_TC_RESUMED);


    if ((TAF_APS_RAT_TYPE_NULL == TAF_APS_GetCurrPdpEntityRatType())
     && (VOS_TRUE == ulExist1XService))
    {
        if (VOS_FALSE == TAF_APS_GetClDelaySearch())
        {
            TAF_APS_LogOldNewPdpRatType(TAF_APS_RAT_TYPE_1X, TAF_APS_RAT_TYPE_NULL);

            TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_1X);
        }
    }

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.ucConnectId == pstResumeInd->ucConnectId)
        {
            /* 当前只支持一路呼叫，ConnectId匹配成功后，进入状态机处理 */
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccOrigDataCallCnf_PreProc
 功能描述  : 收到ID_XCC_APS_ORIG_DATA_CALL_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccOrigDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_ORIG_DATA_CALL_CNF_STRU    *pstOrigCallCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstOrigCallCnf = (XCC_APS_ORIG_DATA_CALL_CNF_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstOrigCallCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccOrigDataCallCnf_PreProc:Wrong CallId", pstOrigCallCnf->ucCallId);
        return VOS_TRUE;
    }

    /* 否则进状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccHangupDataCallCnf_PreProc
 功能描述  : 收到ID_XCC_APS_HANGUP_DATA_CALL_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccHangupDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_HANGUP_DATA_CALL_CNF_STRU  *pstHangUpCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstHangUpCnf = (XCC_APS_HANGUP_DATA_CALL_CNF_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstHangUpCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccHangupDataCallCnf_PreProc:Wrong CallId", pstHangUpCnf->ucCallId);
        return VOS_TRUE;
    }

    /* 否则进状态机处理 */
    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDataCallDiscInd_PreProc
 功能描述  : 收到ID_XCC_APS_DATA_CALL_DISC_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataCallDiscInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscCallInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstDiscCallInd = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.ucConnectId == pstDiscCallInd->ucConnectId)
        {
            /* 进状态机处理 */
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccIncomintCallInd_PreProc
 功能描述  : 收到ID_XCC_APS_INCOMING_CALL_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_INCOMING_CALL_IND_STRU     *pstIncomingCallInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstIncomingCallInd = (XCC_APS_INCOMING_CALL_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* 当前只支持dormant状态下，网络发起的寻呼，因此无效的PDP ID，直接跳过 */
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }



        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.enSo == pstIncomingCallInd->enSo)
        {
            /* 更新ConnectId到APS实体中 */
            TAF_APS_SetPdpEntConnectId(ucPdpId, pstIncomingCallInd->ucConnectId);

            TAF_APS_SndXccIncomingCallRsp(pstPdpEntity->stCdataInfo.ucCallId,
                                          pstIncomingCallInd->ucConnectId,
                                          XCC_APS_RESULT_SUCC);

            /* 进状态机处理 */
            return VOS_FALSE;
        }
    }

    TAF_APS_SndXccIncomingCallRsp(pstIncomingCallInd->ucCallId,
                                  pstIncomingCallInd->ucConnectId,
                                  XCC_APS_RESULT_FAIL);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDataCallConnInd_PreProc
 功能描述  : 收到ID_XCC_APS_DATA_CALL_CONN_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataCallConnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_CONN_IND_STRU    *pstConnCallInd = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstConnCallInd = (XCC_APS_DATA_CALL_CONN_IND_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstConnCallInd->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccDataCallConnInd_PreProc:Wrong CallId", pstConnCallInd->ucCallId);
        return VOS_TRUE;
    }

    /* 否则进状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDataServiceConnInd_PreProc
 功能描述  : 收到ID_XCC_APS_DATA_SERVICE_CONNECT_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataServiceConnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_SERVICE_CONNECT_IND_STRU        *pstServiceConnInd = VOS_NULL_PTR;
    VOS_UINT8                                     ucPdpId;

    pstServiceConnInd = (XCC_APS_DATA_SERVICE_CONNECT_IND_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstServiceConnInd->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccDataServiceConnInd_PreProc:Wrong CallId", pstServiceConnInd->ucCallId);
        return VOS_TRUE;
    }

    /* 否则进状态机处理 */
    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccAnswerDataCallCnf_PreProc
 功能描述  : 收到ID_XCC_APS_ANSWER_DATA_CALL_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccAnswerDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_ANSWER_DATA_CALL_CNF_STRU  *pstAnswerCallCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstAnswerCallCnf = (XCC_APS_ANSWER_DATA_CALL_CNF_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstAnswerCallCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccAnswerDataCallCnf_PreProc:Wrong CallId", pstAnswerCallCnf->ucCallId);
        return VOS_TRUE;
    }

    /* 否则进状态机处理 */
    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccSetPdpEntDormantTimer_PreProc
 功能描述  : SOCM消息配置Dormant Timer
 输入参数  : XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月1日
    作    者   : g00261581
    修改内容   : 新生成函数

  2.日    期   : 2015年1月7日
    作    者   : g00261581
    修改内容   : 设置Dormant TI时跟具体的PdpId实体无关
*****************************************************************************/
VOS_VOID TAF_APS_RcvXccSetPdpEntDormantTimer_PreProc(
    XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
)
{
    VOS_UINT8                           ucPdpId;

    switch (pstSoCtrlMsgInd->ucDormCntl)
    {
        case XCC_APS_SOCM_DORMANT_TIMER_CTRL_DISABLE:
            TAF_APS_SetSocmDormantTiLen(0);
            TAF_APS_SetUserCfgDormTiVal(0);
            break;

        case XCC_APS_SOCM_DORMANT_TIMER_CTRL_SET_MIN_VALUE:
        case XCC_APS_SOCM_DORMANT_TIMER_CTRL_SET_MIN_AND_CUR_VALUE:
            if (TAF_APS_GetSocmDormantTiLen() < (pstSoCtrlMsgInd->ucDormTimer * 100))
            {
                TAF_APS_SetSocmDormantTiLen(pstSoCtrlMsgInd->ucDormTimer * 100);
            }

            for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
            {
                if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
                {
                    continue;
                }

                if (pstSoCtrlMsgInd->enSo != TAF_APS_GetPdpEntSo(ucPdpId))
                {
                    continue;
                }

                if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
                {
                    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

                    if (TAF_APS_GetUserCfgDormTiVal() > TAF_APS_GetSocmDormantTiLen())
                    {
                        TAF_APS_StartTimer(TI_TAF_APS_CDATA_DORMANT, TAF_APS_GetUserCfgDormTiVal(), ucPdpId);
                    }
                    else
                    {
                        TAF_APS_StartTimer(TI_TAF_APS_CDATA_DORMANT, TAF_APS_GetSocmDormantTiLen(), ucPdpId);
                    }
                }
            }

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvXccSetPdpEntDormantTimer_PreProc, Invalid DormCntl Field");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccSetPacketZoneReconnFeature_PreProc
 功能描述  : SOCM Msg used to config Packet Zone Reconnect Feature and Packet Zone Hysteresis Feature
             Parse SOCM Msg
 输入参数  : XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月23日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_RcvXccSetPacketZoneReconnFeature_PreProc(
    XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
)
{
    /* Parse Socm msg according to Pkt_Conect_Cntl Field */
    switch (pstSoCtrlMsgInd->ucPktConCntl)
    {
        case XCC_APS_SOCM_PACKET_ZONE_RECONNECT_CTRL_DISABLE:
            TAF_APS_EpdszidSocmDisableReconn();
            break;

        case XCC_APS_SOCM_PACKET_ZONE_RECONNECT_CTRL_ENABLE:
            TAF_APS_EpdszidSocmEnableReconn(pstSoCtrlMsgInd->ucPktZoneListLen);
            break;

        case XCC_APS_SOCM_PACKET_ZONE_RECONNECT_CTRL_CLEAR:
            TAF_APS_EpdszidSocmClearPacketZoneList(pstSoCtrlMsgInd->ucPktZoneListLen);
            break;

        case XCC_APS_SOCM_PACKET_ZONE_RECONNECT_CTRL_TRANSFER:
            TAF_APS_EpdszidScomTransferPzid(pstSoCtrlMsgInd);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccSoCntrlMsg_PreProc
 功能描述  : 收到ID_XCC_APS_SERVICE_OPTION_CONTROL_MESSAGE消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

  2.日    期   : 2015年1月7日
    作    者   : g00261581
    修改内容   : 增加Packet zone特性功能的配置
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccSoCtrlMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_SO_CTRL_MSG_IND_STRU       *pSoCtrlMsg;

    pSoCtrlMsg = (XCC_APS_SO_CTRL_MSG_IND_STRU *)pstMsg;

    switch (pSoCtrlMsg->enFieldType)
    {
        case XCC_APS_SO_CTRL_FIELD_DORMANT_TIMER_CTRL:
            TAF_APS_RcvXccSetPdpEntDormantTimer_PreProc(pSoCtrlMsg);
            break;

        case XCC_APS_SO_CTRL_FIELD_PACKET_ZONE_RECONN_CTRL:
            TAF_APS_RcvXccSetPacketZoneReconnFeature_PreProc(pSoCtrlMsg);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvXccSoCtrlMsg_PreProc, Error Socm msg");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppActCnf_PreProc
 功能描述  : 收到ID_PPP_APS_PDP_ACT_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppActCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_ACT_CNF_STRU               *pstPppActCnf = VOS_NULL_PTR;

    pstPppActCnf = (PPP_APS_ACT_CNF_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppActCnf->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* 否则不进状态机处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactInd_PreProc
 功能描述  : 收到ID_PPP_APS_PDP_DEACT_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_CNF_STRU             *pstPppDeactCnf  = VOS_NULL_PTR;

    pstPppDeactCnf = (PPP_APS_DEACT_CNF_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppDeactCnf->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* 否则不进状态机处理 */
    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactNtf_PreProc
 功能描述  : 收到ID_PPP_APS_PDP_DEACT_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_NTF_STRU             *pstPppDeactNtf = VOS_NULL_PTR;

    pstPppDeactNtf = (PPP_APS_DEACT_NTF_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppDeactNtf->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* 否则不进状态机处理 */
    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppModifyInd_PreProc
 功能描述  : 收到ID_PPP_APS_MODIFY_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月27日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_MODIFY_IND_STRU            *pstPppModifyInd = VOS_NULL_PTR;

    pstPppModifyInd = (PPP_APS_MODIFY_IND_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppModifyInd->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* 否则不进状态机处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmPdnInfoChgInd_PreProc
 功能描述  : aps收到ehsm的pdn信息变化消息的预处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnInfoChgInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_INFO_CHANGE_IND_STRU  *pstEhsmPdnChgInd = VOS_NULL_PTR;

    pstEhsmPdnChgInd = (EHSM_APS_PDN_INFO_CHANGE_IND_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByCid(pstEhsmPdnChgInd->ucCid))
    {
        return VOS_FALSE;
    }

    /* 否则不进状态机处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppReconnInd_PreProc
 功能描述  : 收到ID_PPP_APS_RECONN_IND消息的预处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月9日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppReconnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_RECONN_IND_STRU            *pstPppReconnInd = VOS_NULL_PTR;

    pstPppReconnInd = (PPP_APS_RECONN_IND_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppReconnInd->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* 否则不进状态机处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvCdsServiceInd_PreProc
 功能描述  : 收到ID_CDS_APS_SERVICE_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月18日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvCdsServiceInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CDS_APS_CDATA_SERVICE_IND_STRU     *pstCdsServiceInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstCdsServiceInd = (CDS_APS_CDATA_SERVICE_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpEntity     = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        /* 如果可以找到对应的实体，记录当前的触发场景 */
        if (pstPdpEntity->ucNsapi == pstCdsServiceInd->ucRabId)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SetCqosPriReq_PreProc
 功能描述  : 处理ID_MSG_TAF_PS_SET_CQOS_PRI_REQ消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月16日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_SetCqosPriReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    TAF_PS_SET_1X_CQOS_PRI_REQ_STRU    *pstSetCqosPriReq;

    pstPsMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetCqosPriReq                   = (TAF_PS_SET_1X_CQOS_PRI_REQ_STRU*)(pstPsMsg->aucContent);

    /* 把用户设置记录到NV项中 */

    /* NV未定义，To Do */

    /* 返回设置结果 */

    /* 返回处理结果 */
    TAF_APS_SndSetCqosPriCnf(&(pstSetCqosPriReq->stCtrl),
                              TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEnterDormantInd_PreProc
 功能描述  : 收到ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND消息的预处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月28日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallEnterDormantInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_CALL_ENTER_DORMANT_IND_STRU *pstDormantInd;

    /* 初始化, 获取消息内容 */
    pstDormantInd = (TAF_PS_CALL_ENTER_DORMANT_IND_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstDormantInd->ucPdpId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvPsCallEnterDormantInd_PreProc:Wrong PdpId", pstDormantInd->ucPdpId);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiHatExpired_PreProc
 功能描述  : APS PreProc when HAT Expired
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiHatExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ProcEpdszidHatExpired();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiHtExpired_PreProc
 功能描述  : APS PreProc when HT Expired
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiHtExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ProcEpdszidHtExpired();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvMmaEpdszidInfo_PreProc
 功能描述  : APS Rcv EPDSZID Info from MMA，Update Current EPDSZID，
             Start Reconnect If current EPDSZID is not in the List
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMmaEpdszidInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_APS_EPDSZID_INFO_IND_STRU      *pEpdszidInfoInd = VOS_NULL_PTR;
    TAF_APS_CDATA_EPDSZID_STRU          stCdataEpdszid;
    VOS_UINT8                           ucPdpId;

    pEpdszidInfoInd = (MMA_APS_EPDSZID_INFO_IND_STRU *)pstMsg;

    PS_MEM_SET(&stCdataEpdszid, 0, sizeof(TAF_APS_CDATA_EPDSZID_STRU));
    stCdataEpdszid.usSid  = pEpdszidInfoInd->usSid;
    stCdataEpdszid.usNid  = pEpdszidInfoInd->usNid;
    stCdataEpdszid.ucPzid = pEpdszidInfoInd->ucPzid;

    /* 可维可测 */
    TAF_APS_TraceEpdszidInfo();

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        /* 当前如果状态机实体处于Inactive状态，不需要处理EPDSZID改变而触发的重建 */
        if (TAF_APS_STA_INACTIVE == TAF_APS_GetPdpIdMainFsmState(ucPdpId))
        {
            continue;
        }

        /* 遗留问题 */
        /* 是不是检测到一个有效的PDPID即可发送函数，还是跟主业务绑定 */
        TAF_APS_ProcMmaEpdszidInfo(pEpdszidInfoInd->usSid,
                                   pEpdszidInfoInd->usNid,
                                   pEpdszidInfoInd->ucPzid,
                                   ucPdpId);
        return VOS_TRUE;
    }

    /* If Don't Snd Internal Msg Only Update Epdszid */
    TAF_APS_SetCurrEpdszidInfo(&stCdataEpdszid);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXregRegBeginInd_PreProc
 功能描述  : XREG send Reg Begin Ind Msg to APS,The msg contains sid/nid/pzid info
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXregRegBeginInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XREG_APS_REG_BEGIN_IND_STRU        *pRegBeginInd = VOS_NULL_PTR;

    pRegBeginInd = (XREG_APS_REG_BEGIN_IND_STRU *)pstMsg;

    TAF_APS_ProcXregEpdszidRegBeginInd(pRegBeginInd->usSid,
                                       pRegBeginInd->usNid,
                                       pRegBeginInd->ucPzid);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterEpdszidReOrig_PreProc
 功能描述  : PreProc Epdszis Re-Orig Req
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月7日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterEpdszidReOrig_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*TO Do: 后续会增加多模融合后的处理 */

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsHaiChangeInd_PreProc
 功能描述  : 收到ID_MSG_TAF_PS_HAI_CHANGE_IND消息的预处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsHaiChangeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_HAI_CHANGE_IND_STRU         *pstHaiChangeInd;

    /* 初始化, 获取消息内容 */
    pstHaiChangeInd = (TAF_PS_HAI_CHANGE_IND_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstHaiChangeInd->ucPdpId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvPsHaiChangeInd_PreProc:Wrong PdpId", pstHaiChangeInd->ucPdpId);
        return VOS_TRUE;
    }

    TAF_APS_ProcEpdszidHaiChangeInd();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccUpdateDataCallInfoInd_PreProc
 功能描述  : The Process for receiving ID_XCC_APS_ANSWER_DATA_CALL_CNF
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccUpdateDataCallInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU     *pstDataCallInfo = VOS_NULL_PTR;
    VOS_UINT8                                   ucPdpId;

    pstDataCallInfo = (XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU *)pstMsg;

    /* If can not find corresponding PDP ID, discard this message */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstDataCallInfo->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccUpdateDataCallInfoInd_PreProc:Wrong CallId", pstDataCallInfo->ucCallId);
        return VOS_TRUE;
    }

    /* Enter FSM to process */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmOrigCnf_PreProc
 功能描述  : 收到ID_HSM_APS_ORIG_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmOrigCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_ORIG_CNF_STRU              *pstOrigCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstOrigCnf = (HSM_APS_ORIG_CNF_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstOrigCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return VOS_TRUE;
    }

    /* 否则进状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmConnectInd_PreProc
 功能描述  : 收到ID_HSM_APS_CONNECT_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmConnectInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    TAF_APS_STA_ENUM_UINT32             enStatus;
    VOS_UINT8                           ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* 当前只支持dormant状态下，网络发起的寻呼，因此无效的PDP ID，直接跳过 */
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        /* 网络激活只处理DORMANT和TAF_APS_STA_CDATA_ESTING状态下的流程 */
        enStatus = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
        if ((TAF_APS_STA_DORMANT == enStatus)
          ||(TAF_APS_STA_CDATA_ESTING == enStatus))
        {
            pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

            TAF_APS_SndHsmConnectRsp(pstPdpEntity->stCdataInfo.ucCallId);

            /* 进状态机处理 */
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmDiscCnf_PreProc
 功能描述  : 收到ID_HSM_APS_DISC_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmDiscCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_DISC_CNF_STRU              *pstDiscCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstDiscCnf = (HSM_APS_DISC_CNF_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstDiscCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return VOS_TRUE;
    }

    /* 否则进状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmDiscInd_PreProc
 功能描述  : 收到ID_HSM_APS_DISC_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmDiscInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_DISC_IND_STRU              *pstDiscInd     = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstDiscInd = (HSM_APS_DISC_IND_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstDiscInd->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return VOS_TRUE;
    }

    /* 否则进状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmLocChangedInd_PreProc
 功能描述  : 收到ID_HSM_APS_LOC_CHANGED_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmLocChangedInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_LOC_CHANGED_IND_STRU       *pstLocChangedInd = VOS_NULL_PTR;
    TAF_APS_CDATA_EPDSZID_STRU          stCdataEpdszid;

    pstLocChangedInd = (HSM_APS_LOC_CHANGED_IND_STRU *)pstMsg;

    PS_MEM_SET(&stCdataEpdszid, 0, sizeof(TAF_APS_CDATA_EPDSZID_STRU));
    stCdataEpdszid.usSid  = pstLocChangedInd->usSid;
    stCdataEpdszid.usNid  = pstLocChangedInd->usNid;
    stCdataEpdszid.ucPzid = pstLocChangedInd->ucPktZoneId;


    /* 更新hrpd最新的Sid/Nid信息 */
    TAF_APS_SetHrpdEpdszidInfo(pstLocChangedInd->usSid,
                               pstLocChangedInd->usNid,
                               pstLocChangedInd->ucPktZoneId);

    /* 可维可测 */
    TAF_APS_TraceEpdszidInfo();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsm1XToHrpdHandOff_PreProc
 功能描述  : 收到ID_HSM_APS_1X_TO_HRPD_HANDOFF_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsm1XToHrpdHandOff_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                     ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmHrpdAvailableIndPreProc
 功能描述  : 收到ID_HSM_APS_HRPD_AVAILABLE_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月07日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmHrpdAvailableIndPreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_SetIsHrpdDisabledFlag(VOS_FALSE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsSetPktCdataInactivityTimeLenReq_PreProc
 功能描述  : 消息ID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQ预处理函数
 输入参数  : ulEventType --- 事件名
             pstMsg      --- 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE    --- 消息处理完毕
             VOS_FALSE   --- 消息未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月21日
    作    者   : c00299063
    修改内容   : 新生成函数
  2.日    期   : 2016年1月25日
    作    者   : y00322978
    修改内容   : DTS2016012503506 at+cta设置1x和do的进入dormant态的时长
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsSetPktCdataInactivityTimeLenReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_SET_CTA_INFO_REQ_STRU       *pstSetPktCdataInactivityTimeLenReq = VOS_NULL_PTR;

    pstSetPktCdataInactivityTimeLenReq = (TAF_PS_SET_CTA_INFO_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    TAF_APS_SetPktCdataInactivityTimerLen(pstSetPktCdataInactivityTimeLenReq->ucPktCdataInactivityTmrLen);

    TAF_APS_SndSetPktCdataInactivityTimerLenCnf(&(pstSetPktCdataInactivityTimeLenReq->stCtrl), TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsGetPktCdataInactivityTimerLenReq_PreProc
 功能描述  : 消息ID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQ预处理函数
 输入参数  : ulEventType --- 事件名
             pstMsg      --- 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE    --- 消息处理完毕
             VOS_FALSE   --- 消息未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月21日
    作    者   : c00299063
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsGetPktCdataInactivityTimerLenReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_CTA_INFO_REQ_STRU       *pstGetPktCdataInactivityTmrlenReq = VOS_NULL_PTR;
    VOS_UINT8                                               ucTimeLen;

    pstGetPktCdataInactivityTmrlenReq  = (TAF_PS_GET_CTA_INFO_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    ucTimeLen = TAF_APS_GetPktCdataInactivityTimerLen();

    if (0 == ucTimeLen)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvPsGetPktCdataInactivityTimerLenReq_PreProc:Time Len = 0!");
    }

    TAF_APS_SndGetPktCdataInactivityTimerLenCnf(&(pstGetPktCdataInactivityTmrlenReq->stCtrl), ucTimeLen, TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvPowerOnInd_Preproc
 功能描述  : 从卡中读取数据业务时最大无数据收发时间请求
 输入参数  : ulEventType --- 事件名
             pstMsg      --- 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE    --- 消息处理完毕
             VOS_FALSE   --- 消息未处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月21日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPowerOnInd_Preproc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 给RLP注册上行数据状态的回调函数*/
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        CTTF_HRPD_RPA_RegDormancyMonitor(TAF_APS_ProcEvdoRlpDataStatusCb);

        CTTF_1X_RLP_RegUserDataUpdateCB(WUEPS_PID_TAF,TAF_APS_ProcRlpDataStatusCb);
    }

    if (VOS_TRUE != TAF_SDC_Is1xOnlyMode())
    {
        TAF_APS_SetClDelaySearch(VOS_TRUE);
    }
    else
    {
        TAF_APS_SetClDelaySearch(VOS_FALSE);
    }

    if (VOS_TRUE == TAF_APS_GetPppAuthInfoGetFromCardFlag())
    {
        TAF_APS_SetRead3GpdFileDoneFlag(VOS_FALSE);
        TAF_APS_Read3GdpFile();
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetDialModeReq_PreProc
 功能描述  :
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月02日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsSetDialModeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_CDATA_DIAL_MODE_REQ_STRU    *pstDialModeReq = VOS_NULL_PTR;
    TAF_PS_MSG_STRU                    *pstPsMsg       = VOS_NULL_PTR;

    /* 初始化 */
    pstDialModeReq    = (TAF_PS_CDATA_DIAL_MODE_REQ_STRU *)pstMsg;

    /* 去消息头, 回复AT */
    pstPsMsg          = (TAF_PS_MSG_STRU *)pstMsg;
    pstDialModeReq    = (TAF_PS_CDATA_DIAL_MODE_REQ_STRU *)pstPsMsg->aucContent;

    TAF_APS_SetFsmCtxCdataDialMode(pstDialModeReq->enDialMode);

    TAF_APS_SndPppDialModeNotify(pstDialModeReq->stCtrl.usClientId);

    TAF_APS_SndSetDialModeCnf(&(pstDialModeReq->stCtrl), TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvGetCgmtuValue_PreProc
 功能描述  : TAF APS Pre Proc CDMA Mtu Value Qry Req
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月29日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvGetCgmtuValue_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_CGMTU_VALUE_REQ_STRU    *pstCgmtuValueReq = VOS_NULL_PTR;
    VOS_UINT32                          ulMtuValue;

    pstCgmtuValueReq = (TAF_PS_GET_CGMTU_VALUE_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    ulMtuValue       = TAF_APS_GET_CDATA_MTU();

    TAF_APS_SndGetCgmtuValueCnf(&(pstCgmtuValueReq->stCtrl), ulMtuValue);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvMma1XServiceStatusInd_PreProc
 功能描述  : 收到ID_MMA_TAF_1X_SERVICE_STATUS_IND消息的处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月08日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMma1XServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_TAF_1X_SERVICE_STATUS_IND_STRU *pstMmaServiceStatusInd = VOS_NULL_PTR;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enOldRatType;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enNewRatType;
    VOS_UINT8                           ucPdpId;

    /* 获取消息内容 */
    pstMmaServiceStatusInd = (MMA_TAF_1X_SERVICE_STATUS_IND_STRU*)pstMsg;

    /* 更新1X的PS域服务状态信息 */
    TAF_APS_Set1XPsServiceStatus(pstMmaServiceStatusInd->ulExist1XService);

    enOldRatType = TAF_APS_GetCurrPdpEntityRatType();

    /* 判断syscfg配置，如果不支持CDMA，直接退出 */
    if (VOS_TRUE != TAF_SDC_IsConfigCLMode())
    {
        return VOS_TRUE;
    }

    /* 如果只支持1X，则直接取1X的服务状态 */
    if (VOS_TRUE == TAF_SDC_Is1xOnlyMode())
    {
        /* 1X的PS域服务可用时，取1X的服务 */
        enNewRatType = (pstMmaServiceStatusInd->ulExist1XService ? TAF_APS_RAT_TYPE_1X:TAF_APS_RAT_TYPE_NULL);

    }
    else
    {
        if ((VOS_FALSE == TAF_APS_GetClDelaySearch())
         && (TAF_APS_RAT_TYPE_NULL == enOldRatType)
         && (VOS_TRUE  == pstMmaServiceStatusInd->ulExist1XService))
         {
            /* 之前无任何PS域服务，1X的PS域服务可用时，取1X的服务 */
            enNewRatType = TAF_APS_RAT_TYPE_1X;
         }
         else if((TAF_APS_RAT_TYPE_1X == enOldRatType)
              && (VOS_FALSE == pstMmaServiceStatusInd->ulExist1XService))
         {
            /* 之前为1X的PS域服务，1X的PS域服务不可用时，取NULL */
            enNewRatType = TAF_APS_RAT_TYPE_NULL;
         }
         else
         {
            /* 其它情况下取原记录:NULL false,1x true */
            enNewRatType = TAF_APS_GetCurrPdpEntityRatType();
         }
    }

    TAF_APS_LogOldNewPdpRatType(enNewRatType, enOldRatType);

    /* 更新状态机实体接入技术 */
    TAF_APS_SetCurrPdpEntityRatType(enNewRatType);


    if ((TAF_APS_RAT_TYPE_NULL == enNewRatType)
     && (enOldRatType == enNewRatType))
    {
        return VOS_TRUE;
    }

    /* TO DO:预处理里向Ehsm发送Loc Detach Ind消息 */

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* 如果当前PDP实体不为INACTIVE状态，则发送内部消息进状态机处理 */
        if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucPdpId))
        {
            (VOS_VOID)TAF_APS_SndInterServiceStatusChangeInd(ucPdpId,
                                                   TAF_APS_GetCurrPdpEntityRatType(),
                                                   enOldRatType,
                                                   TAF_APS_GetCurrPdpEntitySimRegStatus(),
                                                   VOS_FALSE,
                                                   TAF_APS_INTER_SERVICE_RESULT_1X);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvMmaCLServiceStatusInd_PreProc
 功能描述  : 收到ID_MMA_TAF_SERVICE_STATUS_IND消息的处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月08日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMmaCLServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_APS_CL_SERVICE_STATUS_IND_STRU *pstMmaServiceStatusInd = VOS_NULL_PTR;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enOldRatType;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enNewRatType;
    VOS_UINT32                          ulExist1XService;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrDataServiceMode;
    VOS_UINT8                           ucPdpId;


    /* 获取消息内容 */
    pstMmaServiceStatusInd  = (MMA_APS_CL_SERVICE_STATUS_IND_STRU*)pstMsg;
    ulExist1XService        = TAF_APS_Get1XPsServiceStatus();
    enOldRatType            = TAF_APS_GetCurrPdpEntityRatType();
    enNewRatType            = enOldRatType;

    /* 判断syscfg配置，如果不支持CDMA，直接退出 */
    if (VOS_TRUE != TAF_SDC_IsConfigCLMode())
    {
        return VOS_TRUE;
    }


    /* DO/LTE由有服务到无服务时的处理 */
    if ((MMA_TAF_CL_STATUS_DO_LTE_NO_SERVICE == pstMmaServiceStatusInd->enClStatus)
     || (MMA_TAF_CL_STATUS_DO_NO_SERVICE     == pstMmaServiceStatusInd->enClStatus)
     || (MMA_TAF_CL_STATUS_LTE_NO_SERVICE    == pstMmaServiceStatusInd->enClStatus))
    {
        /* 当前1X有服务，收到DO或LTE无服务，不更新接入技术模式 */
        if (VOS_TRUE == ulExist1XService)
        {
            if (TAF_APS_CDMA_TC_SUSPENDED != TAF_APS_GET_CDATA_SUSPEND_STATUS())
            {
                enNewRatType = TAF_APS_RAT_TYPE_1X;
            }
            else
            {
                enNewRatType = TAF_APS_RAT_TYPE_NULL;
            }
        }
        else
        {
            enNewRatType = TAF_APS_RAT_TYPE_NULL;
        }
    }
    else
    {
        enNewRatType = TAF_APS_ConvertMmaClServiceToApsRatType(pstMmaServiceStatusInd->enClStatus);
    }

    TAF_APS_LogOldNewPdpRatType(enNewRatType, enOldRatType);

    /* 更新状态机实体接入技术 */
    TAF_APS_SetCurrPdpEntityRatType(enNewRatType);

    if ((TAF_APS_RAT_TYPE_HRPD  == enNewRatType)
     || (TAF_APS_RAT_TYPE_EHRPD == enNewRatType)
     || (TAF_APS_RAT_TYPE_LTE   == enNewRatType))
    {
        TAF_APS_SetClDelaySearch(VOS_TRUE);
    }
    else
    {
        TAF_APS_SetClDelaySearch(VOS_FALSE);
    }

    /* 通知CDS当前接入技术改变 */
    enCurrDataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();
    if (VOS_TRUE == TAF_APS_IsNeedNotifyCdsModeChange(enNewRatType, enCurrDataServiceMode))
    {
        TAF_APS_SndCdsModeChangeInd(enNewRatType);
    }

    /* 模式没有改变则不再次进入状态机处理，避免重复处理或者冗余消息 */
    if ((enOldRatType          == enNewRatType)
     && (TAF_APS_RAT_TYPE_NULL == enNewRatType))
    {
        return VOS_TRUE;
    }

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* 如果当前PDP实体不为INACTIVE状态，则发送内部消息进状态机处理 */
        if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucPdpId))
        {
            (VOS_VOID)TAF_APS_SndInterServiceStatusChangeInd(ucPdpId,
                                                   TAF_APS_GetCurrPdpEntityRatType(),
                                                   enOldRatType,
                                                   TAF_APS_GetCurrPdpEntitySimRegStatus(),
                                                   pstMmaServiceStatusInd->ucIsNewSession,
                                                   TAF_APS_INTER_SERVICE_RESULT_CL);
        }
    }

    return VOS_TRUE;
}


#if 0
/*****************************************************************************
 函 数 名  : TAF_APS_RcvMmaHrpdDataCallSysAcqInd_PreProc
 功能描述  : 收到ID_MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND消息的处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月16日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMmaHrpdDataCallSysAcqInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU                *pstHrpdSysAcqInd = VOS_NULL_PTR;

    pstHrpdSysAcqInd = (MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU *)pstMsg;

    if (MMA_TAF_HRPD_ACQUIRED_RESULT_SUCC == pstHrpdSysAcqInd->enHrpdSysAcqRst)
    {
        /* 目前消息中携带的rattype不可用 */
        if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_ConvertMmaRatType(pstHrpdSysAcqInd->enRatType))
        {
            TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_HRPD);
        }
        else
        {
            TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_EHRPD);
        }

    }

    return VOS_FALSE;
}

#endif

/*****************************************************************************
 函 数 名  : TAF_APS_RcvMmaSysCfgInfoInd_PreProc
 功能描述  : 收到ID_MMA_APS_SYS_CFG_INFO_IND消息的处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月29日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMmaSysCfgInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_TAF_SYS_CFG_INFO_IND_STRU      *pstSysCfgInfoInd = VOS_NULL_PTR;
    VOS_UINT8                           i;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;

    pstSysCfgInfoInd = (MMA_TAF_SYS_CFG_INFO_IND_STRU *)pstMsg;


    /* 系统模式切换GUL<->CL切换后，APS本地清除承载信息，退出状态机，并通知底层模块，处理等同于POWER_OFF
       1.GUL->CL 本地去激活后APS通知SM，ESM，ADS，CDS等模块；
       2.CL->GUL 本地去激活后APS通知EHSM，ESM，ADS，CDS，PPP等模块；
       注意以上的CL是广义的意义，包括如下模式，1X only，DO only，hybrid，1X+LTE，hybrid+LTE(SVLTE)。
    */

    if (VOS_TRUE == TAF_APS_IsSyscfgCdmaModeChange(&pstSysCfgInfoInd->stOldRatOrder,
                                                   &pstSysCfgInfoInd->stNewRatOrder))
    {
        TAF_APS_LocalReleaseAll();
    }

    /* 非单1X时，迟滞标记为VOS_FALSE */
    for (i = 0; i < pstSysCfgInfoInd->stNewRatOrder.ucRatOrderNum; i++)
    {
        enRatType = TAF_APS_ConvertMmaRatTypeToApsRatType(pstSysCfgInfoInd->stNewRatOrder.aenRatOrder[i]);

        if ((TAF_APS_RAT_TYPE_HRPD == enRatType)
         || (TAF_APS_RAT_TYPE_LTE  == enRatType))
        {
            TAF_APS_SetClDelaySearch(VOS_TRUE);

            return VOS_TRUE;
        }
    }

    /* 单1X时，迟滞标记为VOS_FALSE */
    enRatType = TAF_APS_ConvertMmaRatTypeToApsRatType(pstSysCfgInfoInd->stNewRatOrder.aenRatOrder[0]);
    if ((1                   == pstSysCfgInfoInd->stNewRatOrder.ucRatOrderNum)
     && (TAF_APS_RAT_TYPE_1X == enRatType))
    {
        TAF_APS_SetClDelaySearch(VOS_FALSE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmPdnActiveInd_PreProc
 功能描述  : 收到ID_EHSM_APS_PDN_ACTIVATE_IND消息的处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnActInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_IND_STRU     *pstEhsmPdnInd;
    VOS_UINT8                           ucPdpId;
    TAF_CTRL_STRU                       stCtrl;

    pstEhsmPdnInd = (EHSM_APS_PDN_ACTIVATE_IND_STRU *)pstMsg;
    /* MODULE ID默认设置为AT */
    stCtrl.ulModuleId   = WUEPS_PID_AT;
    stCtrl.usClientId   = TAF_APS_INVALID_CLIENTID;
    stCtrl.ucOpId       = TAF_APS_INVALID_OPID;

    /* Cid的值无效，则直接返回 */
    if ( TAF_INVALID_CID == pstEhsmPdnInd->ucCid )
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnActInd_PreProc:invalid Cid", pstEhsmPdnInd->ucCid);
        return VOS_TRUE;
    }

#if 0
    /* 正常情况下，按照CID来查找Pdp Id */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstEhsmPdnInd->ucCid);
    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        return VOS_FALSE;
    }
    else
    {
        /* 自动应答模式下, 需要分配新的APS实体来存储承载信息 */
        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnActInd_PreProc, Get PDP ID fail.");
    }
#endif

    /* cid为0时，表示是默认承载，则分配一个新的PDP ID
       client id和op id此时认为是无效值，后面真正激活时，再进行刷新 */
    if (TAF_APS_DEFAULT_CID == pstEhsmPdnInd->ucCid)
    {
        /* 分配(PdP Id) */
        if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&stCtrl,
                                                           pstEhsmPdnInd->ucCid,
                                                           &ucPdpId))
        {
            /* 分配不到实体，打印异常，此时不应该分配不到实体 */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnActInd_PreProc, alloc pdp id fail");
            return VOS_TRUE;
        }
    }
    else
    {
        /* 异常消息, 丢弃 */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnActInd_PreProc, Abnormal Ehsm CID.");
        return VOS_TRUE;
    }

    /* 否则进状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmPdnDeactiveInd_PreProc
 功能描述  : 收到ID_EHSM_APS_PDN_DEACTIVATE_IND消息的处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnDeactInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_DEACTIVATE_IND_STRU   *pstPdnDeactInd;

    pstPdnDeactInd = (EHSM_APS_PDN_DEACTIVATE_IND_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByPndId(pstPdnDeactInd->ucPdnId))
    {
        /* 丢弃该消息 */
        return VOS_TRUE;
    }

    /* 否则进状态机处理 */
    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmLteHandoverToEhrpdInd_PreProc
 功能描述  : 收到ID_MMA_TAF_SERVICE_STATUS_IND消息的处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月11日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmLteHandoverToEhrpdInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU       *pstPdnIratHrpdInd;

    pstPdnIratHrpdInd = (EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByNsapi(pstPdnIratHrpdInd->ucRabId))
    {
        /* 丢弃该消息 */
        return VOS_TRUE;
    }

    /* 记录当前的PS服务所在的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    /* 否则进状态机处理 */
    return VOS_FALSE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmPdnActCnf_PreProc
 功能描述  : 收到ID_EHSM_APS_PDN_ACTIVATE_CNF消息的处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月19日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnActCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_CNF_STRU     *pstPdnActCnf;

    pstPdnActCnf = (EHSM_APS_PDN_ACTIVATE_CNF_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdnActCnf->ucCid))
    {
        /* 丢弃该消息 */
        return VOS_TRUE;
    }

    /* 否则进状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmPdnAttachCnf_PreProc
 功能描述  : ID_EHSM_APS_PDN_ATTACH_CNF消息的预处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnAttachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ATTACH_CNF_STRU       *pstPdnAttachCnf;

    pstPdnAttachCnf = (EHSM_APS_PDN_ATTACH_CNF_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdnAttachCnf->ucCid))
    {
        /* 丢弃该消息 */
        return VOS_TRUE;
    }

    /* 否则进状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmPdnDeactCnf_PreProc
 功能描述  : 收到ID_EHSM_APS_PDN_DEACTIVATE_CNF消息的处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnDeactCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_DEACTIVATE_CNF_STRU   *pstPdnDeactCnf;

    pstPdnDeactCnf = (EHSM_APS_PDN_DEACTIVATE_CNF_STRU *)pstMsg;

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdnDeactCnf->ucCid))
    {
        /* 丢弃该消息 */
        return VOS_TRUE;
    }

    /* 否则进状态机处理 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmReconnCnf_PreProc
 功能描述  : 收到ID_EHSM_APS_RECONN_CNF消息的处理
 输入参数  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmReconnCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_RECONN_CNF_STRU           *pstReconnCnf;
    VOS_UINT8                           ucPdpId;

    pstReconnCnf = (EHSM_APS_RECONN_CNF_STRU *)pstMsg;
    ucPdpId      = TAF_APS_GetPdpIdByCid(pstReconnCnf->ucCid);

    /* 如果找不到对应的PDP ID，则丢弃该消息 */
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* 丢弃该消息 */
        return VOS_TRUE;
    }


    /* 给CDS发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息 */
    TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvDhcpDnsGetCnf_PreProc
 功能描述  : 收到DHCP的ID_DHCP_APS_GET_DNS_IPV4_CNF消息的预处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月24日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvDhcpDnsIpv4Cnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    DHCP_APS_DNS_IPV4_CNF_STRU         *pstDhcpDnsIpv4Cnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 初始化, 获取消息内容 */
    pstDhcpDnsIpv4Cnf = (DHCP_APS_DNS_IPV4_CNF_STRU *)pstMsg;

    /* 获取NSAPI对应的APS实体 */
    ucPdpId           = TAF_APS_GetPdpIdByNsapi(pstDhcpDnsIpv4Cnf->ucRabId);

    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);
        pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);


        if (VOS_OK             == pstDhcpDnsIpv4Cnf->ulResult)
        {
            /* 更新PDP实体的DNS */
            TAF_APS_UpdateCdataIpv4Dns(pstPdpEntity, pstDhcpDnsIpv4Cnf);
        }
        else
        {
            /* 协商失败处理 */
            TAF_APS_ProcCdataDhcpNegotiateFail(ucPdpId,
                                               TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV4_FAIL);

            return VOS_TRUE;
        }

        TAF_APS_IpfConfigUlFilter(ucPdpId);

        if (APS_ADDR_STATIC_IPV4 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
        {
            /* 协商结束 */
            pstPdpEntity->ucNeedGetDnsFlg = VOS_FALSE;

            if (TAF_APS_DEFAULT_CID != ucCid)
            {
                /* 给用户上报ACTIVATE_CNF事件 */
                TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
            }

            return VOS_TRUE;
        }
        else
        {
            /* 如果是Ipv4Ipv6, 先设置标IPV4的标志位 */
            pstPdpEntity->ucRcvDhcpDnsFlgIpv4 = VOS_TRUE;
        }

         /* 当前为Ipv4v6, 先 RaInfo*/
        TAF_APS_RcvSequenceProcessDhcpNdclient(ucPdpId, ucCid);


    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvDhcpDnsIpv4Cnf_PreProc: Can't find PDP ID form RAB ID!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvDhcpDnsIpv6Cnf_PreProc
 功能描述  : 收到DHCP的ID_DHCP_APS_GET_DNS_IPV6_CNF消息的预处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月24日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvDhcpDnsIpv6Cnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    DHCP_APS_DNS_IPV6_CNF_STRU         *pstDhcpDnsIpv6Cnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    MN_APS_PDP_IPV6_DNS_STRU           *pstPdpIpv6Dns;

    /* 初始化, 获取消息内容 */
    pstDhcpDnsIpv6Cnf = (DHCP_APS_DNS_IPV6_CNF_STRU *)pstMsg;

    /* 获取NSAPI对应的APS实体 */
    ucPdpId           = TAF_APS_GetPdpIdByNsapi(pstDhcpDnsIpv6Cnf->ucRabId);

    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);
        pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);


        if (VOS_OK             == pstDhcpDnsIpv6Cnf->ulResult)
        {
            /* 更新PDP实体的DNS */
            pstPdpIpv6Dns = (MN_APS_PDP_IPV6_DNS_STRU *)&pstDhcpDnsIpv6Cnf->stIpv6Dns;

            TAF_APS_UpdateCdataIpv6Dns(pstPdpEntity, pstPdpIpv6Dns);
        }
        else
        {
            pstPdpIpv6Dns = (MN_APS_PDP_IPV6_DNS_STRU *)&pstDhcpDnsIpv6Cnf->stIpv6Dns;
            PS_MEM_SET(pstPdpIpv6Dns, 0, sizeof(MN_APS_PDP_IPV6_DNS_STRU));

            TAF_APS_UpdateCdataIpv6Dns(pstPdpEntity, pstPdpIpv6Dns);

            /* 协商失败处理 */
#if 0
            TAF_APS_ProcCdataDhcpNegotiateFail(ucPdpId,
                                               TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV6_FAIL);

            return VOS_TRUE;
#endif
        }

        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* Ipv4Ipv6, 先设置标IPV6的标志位
            或只做IPV6的协商   */
        pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_TRUE;

        /* 当前为Ipv4 v6, 需要判断标志位，决定由哪个处理消息上报 ipv4Cnf ipv6Cnf ndclientInd */
        TAF_APS_RcvSequenceProcessDhcpNdclient(ucPdpId, ucCid);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvDhcpDnsIpv6Cnf_PreProc: Can't find PDP ID form RAB ID!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterPsServiceModeModifyInd_PreProc
 功能描述  : 收到ID_MSG_TAF_PS_INTER_PS_SERVICE_MODE_MODIFY_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月4日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterPsServiceModeModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU   *pstInterMsg = VOS_NULL_PTR;
    TAF_APS_RAT_TYPE_ENUM_UINT32                         enPsRatType;
    TAF_APS_RAT_TYPE_ENUM_UINT32                         enPsDataSerMode;
    VOS_UINT8                                            ucPdpId;

    pstInterMsg     = (TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU *)pstMsg;

    enPsRatType     = TAF_APS_GetCurrPdpEntityRatType();
    enPsDataSerMode = TAF_APS_GetCurrPdpEntityDataServiceMode();

    switch (pstInterMsg->enPsOptionType)
    {
        case TAF_APS_INTER_PS_OPTION_DISCONNECTED:
            for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
            {
                if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucPdpId))
                {
                    /* 去激活后，如果还存在承载，保持PS模式与rattype一致 */
                    if ((enPsRatType != enPsDataSerMode)
                     && (  (TAF_APS_RAT_TYPE_HRPD == enPsDataSerMode)
                         ||(TAF_APS_RAT_TYPE_1X   == enPsDataSerMode)))
                    {
                        break;
                    }
                    else
                    {
                        return VOS_TRUE;
                    }
                }
            }

            /* 当前无PS业务 */
            enPsRatType = TAF_APS_RAT_TYPE_NULL;
            break;

        case TAF_APS_INTER_PS_OPTION_SWITCH:

            break;

        default:
            return VOS_TRUE;
    }

    /* 设置当前PS业务所在的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(enPsRatType);

    /* 通知外部模块当前PS业务所在的模式 */
    TAF_APS_SndExternalModulePsRatTypeNtf(enPsRatType);

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : TAF_APS_RcvSet1xDormantTimer_PreProc
 功能描述  : 消息ID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQ预处理函数
 输入参数  : ulEventType --- 事件名
             pstMsg      --- 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE    --- 消息处理完毕
             VOS_FALSE   --- 消息未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : y00314741
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSet1xDormantTimer_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_SET_1X_DORM_TIMER_REQ_STRU  *pstSet1xDormTimerReq = VOS_NULL_PTR;
    VOS_UINT32                          ulSocmDormTimer;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_PS_SET_1X_DORM_TIMER_CNF_STRU   stSet1xDormTimerCnf;

    enCause              = TAF_PS_CAUSE_SUCCESS;
    pstSet1xDormTimerReq = (TAF_PS_SET_1X_DORM_TIMER_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    ulSocmDormTimer      = TAF_APS_GetSocmDormantTiLen();

    /* Dormant timer feature is enable, and user cfg value shall not less than SOCM setting  */
    if ((ulSocmDormTimer > 0) && ((pstSet1xDormTimerReq->ucDormantTimer * 100) >= ulSocmDormTimer))
    {
        TAF_APS_SetUserCfgDormTiVal(pstSet1xDormTimerReq->ucDormantTimer * 100);
    }
    else
    {
        enCause       = TAF_PS_CAUSE_INVALID_PARAMETER;
    }

    PS_MEM_SET(&stSet1xDormTimerCnf, 0, sizeof(TAF_PS_SET_1X_DORM_TIMER_CNF_STRU));

    /* 填写消息头 */
    stSet1xDormTimerCnf.stCtrl  = pstSet1xDormTimerReq->stCtrl;
    stSet1xDormTimerCnf.enCause = enCause;

    /* 发送ID_EVT_TAF_PS_SET_1X_DORM_TIMER_CNF消息 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_1X_DORM_TIMER_CNF,
                               &stSet1xDormTimerCnf,
                               sizeof(TAF_PS_SET_1X_DORM_TIMER_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtGet1xDormantTimer_PreProc
 功能描述  : 消息ID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQ预处理函数
 输入参数  : ulEventType --- 事件名
             pstMsg      --- 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE    --- 消息处理完毕
             VOS_FALSE   --- 消息未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月13日
    作    者   : y00314741
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGet1xDormantTimer_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_1X_DORM_TIMER_REQ_STRU  *pstGet1xDormTimerReq = VOS_NULL_PTR;
    TAF_PS_GET_1X_DORM_TIMER_CNF_STRU   stGet1xDormTimerCnf;

    pstGet1xDormTimerReq = (TAF_PS_GET_1X_DORM_TIMER_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    PS_MEM_SET(&stGet1xDormTimerCnf, 0, sizeof(TAF_PS_GET_1X_DORM_TIMER_CNF_STRU));

    /* 填写消息头 */
    stGet1xDormTimerCnf.stCtrl             = pstGet1xDormTimerReq->stCtrl;
    stGet1xDormTimerCnf.ucSocmDormTiVal    = (VOS_UINT8)(TAF_APS_GetSocmDormantTiLen()/100);
    stGet1xDormTimerCnf.ucUserCfgDormTival = (VOS_UINT8)(TAF_APS_GetUserCfgDormTiVal()/100);

    /* 发送ID_EVT_TAF_PS_SET_1X_DORM_TIMER_CNF消息 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_1X_DORM_TIMER_CNF,
                               &stGet1xDormTimerCnf,
                               sizeof(TAF_PS_GET_1X_DORM_TIMER_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_UsimGetFileRspPreProc
 功能描述  : aps 收到卡文件读取cnf消息的处理
 输入参数  : USIMM_READFILE_CNF_STRU* pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月27日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_UsimGetFileRspPreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg  = VOS_NULL_PTR;
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID;

    pUsimTafMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;
    if (VOS_OK != USIMM_ChangePathToDefFileID(pUsimTafMsg->stCmdResult.enApptype, pUsimTafMsg->stFilePath.ulPathLen, pUsimTafMsg->stFilePath.acPath, &enFileID))
    {
        return VOS_FALSE;
    }

    /* 清除等待标记 */
    TAF_APS_ClearWaitSimFilesCnfFlg(enFileID);

    if (TAF_APS_READ_USIM_FILE_FLG_NULL == TAF_APS_GetWaitSimFilesCnfFlg())
    {
        TAF_APS_SetRead3GpdFileDoneFlag(VOS_TRUE);
    }


    switch (enFileID)
    {
        case USIMM_CDMA_EFSIPCAP_ID:
        case USIMM_CSIM_EFSIPCAP_ID:
            TAF_APS_Read3GpdSipCapaFileCnf(pUsimTafMsg);
            break;
        case USIMM_CDMA_EFSIPUPP_ID:
        case USIMM_CSIM_EFSIPUPP_ID:
            TAF_APS_Read3GpdSipUppFileCnf(pUsimTafMsg);
            break;
        case USIMM_CDMA_EFSIPSP_ID:
        case USIMM_CSIM_EFSIPSP_ID:
            TAF_APS_Read3GpdSipStatusFileCnf(pUsimTafMsg);
            break;
        case USIMM_CDMA_EFSIPPAPSS_ID:
        case USIMM_CSIM_EFSIPPAPSS_ID:
            TAF_APS_Read3GpdSipPapSsFileCnf(pUsimTafMsg);
            break;
        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_UsimGetFileRspPreProc():WARNING:UNKNOW EFID RECEIVE! ");
    }

    return VOS_TRUE;
}


#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
