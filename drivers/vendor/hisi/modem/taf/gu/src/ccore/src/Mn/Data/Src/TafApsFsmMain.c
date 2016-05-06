/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmMain.c
  版 本 号   : 初稿
  作    者   : h44270
  生成日期   : 2011年12月16日
  最近修改   :
  功能描述   : 主状态机处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月16日
    作    者   : h44270
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafTypeDef.h"
#include "TafApsApi.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "MmcApsInterface.h"
#include "TafLog.h"
#include "TafApsCtx.h"
#include "TafApsFsmMain.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsFsmMsActivatingTbl.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "TafApsFsmMsModifyingTbl.h"
#include "TafApsFsmNwActivatingTbl.h"
#include "TafApsFsmMsDeactivating.h"
#include "TafApsProcIpFilter.h"
#include "TafApsSndAt.h"
#include "TafApsSndInternalMsg.h"
#include "TafApsSndRabm.h"
#include "TafApsSndSm.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#include "MnApsMultiMode.h"
#include "ApsL4aInterface.h"
#include "TafApsSndL4a.h"
#endif
#include "ApsNdInterface.h"
#include "TafApsSndNd.h"
#include "TafApsComFunc.h"

#include "TafApsFsmCdataEstingTbl.h"
#include "TafApsFsmCdataDiscingTbl.h"
#include "TafMmaInterface.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "xcc_aps_pif.h"
#include "hsm_aps_pif.h"
#include "TafApsFsmCdataHandOff.h"
#endif
#include "TafApsSndCds.h"
#include "TafApsSndPpp.h"
#include "taf_aps_ppp_pif.h"
#include "TafApsSndXcc.h"
#include "TafApsFsmCdataHandOffTbl.h"
#include "TafApsSndNd.h"
#include "TafApsSndEhsm.h"
#include "TafApsSndDhcp.h"
#include "cnas_cttf_hrpd_pa_pif.h"

#include "TafApsProcEpdszid.h"
#include "TafSdcLib.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MAIN_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_Inactive
 功能描述  : 收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg            = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* PDP激活操作处理 */
    if (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState)
    {
        /*-------------------------------------------------------
           加载TAF_APS_STA_MS_ACTIVATING状态机
           加载后子状态切换为TAF_APS_MS_ACTIVATING_SUBSTA_INIT

           在TAF_APS_MS_ACTIVATING_SUBSTA_INIT子状态中处理
           ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
        -------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_ACTIVATING,
                           TAF_APS_GetMsActivatingFsmDescAddr(),
                           TAF_APS_MS_ACTIVATING_SUBSTA_INIT);
    }
    else
    {
        /* 指定去激活的CID处于未激活状态, 在预处理中已经处理, 这里不再处理 */
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvAtSetPdpContextStateReq_Inactive: Wrong operation");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_Inactive
 功能描述  : INACTIVE主状态下收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /*-------------------------------------------------------
       平台能力支持CDMA，且当前驻留模式如果为3GPP2或NULL,
       则选择3GPP2流程，否则选择3GPP流程

       NULL状态下收到MMA上报的服务状态消息，
       如果为LTE模式则退出TAF_APS_FSM_CDATA_ESTING状态机，
       重新加载TAF_APS_STA_MS_ACTIVATING状态机

       加载TAF_APS_FSM_CDATA_ESTING状态机
       加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
    -------------------------------------------------------*/

    if (VOS_TRUE == TAF_APS_IsEnterCdataEsting())
    {
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                           TAF_APS_GetCdataEstingFsmDescAddr(),
                           TAF_APS_CDATA_ESTING_SUBSTA_INIT);
    }
    else
#endif
        /*-------------------------------------------------------
           加载TAF_APS_STA_MS_ACTIVATING状态机
           加载后子状态切换为TAF_APS_MS_ACTIVATING_SUBSTA_INIT

           在TAF_APS_MS_ACTIVATING_SUBSTA_INIT子状态中处理
           ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
        -------------------------------------------------------*/
    {
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_ACTIVATING,
                           TAF_APS_GetMsActivatingFsmDescAddr(),
                           TAF_APS_MS_ACTIVATING_SUBSTA_INIT);
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_Inactive
 功能描述  : INACTIVE主状态下收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /*-------------------------------------------------------
       平台能力支持CDMA，且当前驻留模式如果为3GPP2或NULL,
       则选择3GPP2流程，否则选择3GPP流程

       NULL状态下收到MMA上报的服务状态消息，
       如果为LTE模式则退出TAF_APS_FSM_CDATA_ESTING状态机，
       重新加载TAF_APS_STA_MS_ACTIVATING状态机

       加载TAF_APS_FSM_CDATA_ESTING状态机
       加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
    -------------------------------------------------------*/

    if (VOS_TRUE == TAF_APS_IsEnterCdataEsting())
    {
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                           TAF_APS_GetCdataEstingFsmDescAddr(),
                           TAF_APS_CDATA_ESTING_SUBSTA_INIT);
    }
    else
#endif
    /*-------------------------------------------------------
       加载TAF_APS_STA_MS_ACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_ACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_ACTIVATING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
    -------------------------------------------------------*/
    {
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_ACTIVATING,
                           TAF_APS_GetMsActivatingFsmDescAddr(),
                           TAF_APS_MS_ACTIVATING_SUBSTA_INIT);
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpActivateInd_Inactive
 功能描述  : INACTIVE主状态下收到D_PMC_SMREG_PDP_ACT_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpActivateInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    /* 获取当前网络模式*/
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    /* 检查当前模是否为GU, 如果不是, 丢弃该消息 */
    if ( (TAF_APS_RAT_TYPE_GSM   != enCurrRatType)
      && (TAF_APS_RAT_TYPE_WCDMA != enCurrRatType) )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSmPdpActivateInd_Inactive: Current RAT is not GSM/WCDMA!");
        return VOS_TRUE;
    }

     /* 迁移到子状态TAF_APS_NW_ACTIVATING_SUBSTA_INIT,在子状态
        TAF_APS_NW_ACTIVATING_SUBSTA_INIT中处理 ID_SMREG_PDP_ACTIVATE_IND
        消息
     */
    TAF_APS_InitSubFsm(TAF_APS_FSM_NW_ACTIVATING,
                       TAF_APS_GetNwActivatingFsmDescAddr(),
                       TAF_APS_NW_ACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmPdpManageInd_Inactive
 功能描述  : INACTIVE主状态下收到ID_APP_ESM_PDP_MANAGER_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpManageInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    /* 获取当前网络模式*/
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    /* 检查当前模是否为LTE, 如果不是, 丢弃该消息 */
    if (TAF_APS_RAT_TYPE_LTE != enCurrRatType)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvEsmPdpManageInd_Inactive: Current RAT is not LTE!");
        return VOS_TRUE;
    }

    /* 迁移到子状态TAF_APS_NW_ACTIVATING_SUBSTA_INIT,在子状态
       TAF_APS_NW_ACTIVATING_SUBSTA_INIT中处理 ID_APP_ESM_PDP_MANAGER_IND
       消息
    */
    TAF_APS_InitSubFsm(TAF_APS_FSM_NW_ACTIVATING,
                       TAF_APS_GetNwActivatingFsmDescAddr(),
                       TAF_APS_NW_ACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive
 功能描述  : INACTIVE主状态下收到ID_ESM_SM_EPS_BEARER_INFO_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月07日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2013年01月21日
    作    者   : A00165503
    修改内容   : DTS2013011803709: 激活ND Client增加接入技术判断, 防止在NULL
                 状态下激活ND Client导致RS包被丢弃

  3.日    期   : 2013年4月23日
    作    者   : A00165503
    修改内容   : DTS2013041204937: 专用承载激活时不需要激活ND Client

  4.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目新增IMS专有承载的处理

  5.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: PS域呼叫建立流程优化
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataSerMode;
#endif
    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;

    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 根据EPS承载的操作类型(Activate, Deactivate, Modify),
       调用相应的处理函数 */
    if (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptActivate(pstPdpEntity, pstBearerInfo);

        if (TAF_APS_DEFAULT_CID == TAF_APS_GetCidFromLteBitCid(pstBearerInfo->ulBitCid))
        {
            TAF_APS_SndInterAttachBearerActivateInd();
        }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

        enDataSerMode = TAF_APS_GetCurrPdpEntityDataServiceMode();

        if ((TAF_APS_RAT_TYPE_1X   != enDataSerMode)
         && (TAF_APS_RAT_TYPE_HRPD != enDataSerMode))
        {
            /* 记录当前的PS服务所在的模式 */
            TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);

            /* 通知外部模块当前的PS服务所在的模式 */
            TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_LTE);
        }

#endif
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive: Wrong option.");
    }

    /* 主状态迁移至TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    return VOS_TRUE;
}
#endif


/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_Active
 功能描述  : 收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : S62952
    修改内容   : 新生成函数

  2.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  3.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: PS域呼叫建立流程优化

  4.日    期   : 2014年12月8日
    作    者   : A00165503
    修改内容   : DTS2014111302668: 匹配缺省PDN流程中, CID对应的剩余时长未清
                 除, 导致使用相同CID再次拨号后, 在匹配缺省PDN场景下未上报响
                 应事件, 拨号流程异常
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;
#if (FEATURE_ON == FEATURE_IPV6)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif
    VOS_UINT32                          ulBearerActivateFlg;
    VOS_UINT8                           ucCidValue;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxStateReq                = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 设置激活标记 */
    ulBearerActivateFlg = (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState) ? VOS_TRUE : VOS_FALSE;

    /* 当前先不支持一次性激活多个PDP的场景，一次激活一个，因此找第一个要激活的 CID */
    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstSetPdpCtxStateReq->stCidListStateInfo.aucCid);

    /* PDP激活操作处理 */
    if (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState)
    {
        /* 如果CID对应的剩余定时器时长为0, 需要上报响应事件 */
        if (0 == TAF_APS_GetCallRemainTmrLen(ucCidValue))
        {
            TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpCtxStateReq->stCtrl),
                                         TAF_PS_CAUSE_SUCCESS);
        }

        TAF_APS_SetCallRemainTmrLen(ucCidValue, 0);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF事件 */
        TAF_APS_SndPdpActivateCnf(ucPdpId, ucCidValue);

#if (FEATURE_ON == FEATURE_IPV6)
        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
        if (VOS_TRUE == pstPdpEntity->bitOpIpv6RaInfo)
        {
            /* 上报ID_EVT_TAF_PS_IPV6_INFO_IND事件 */
            TAF_APS_SndIpv6RaInfoNotifyInd(&(pstSetPdpCtxStateReq->stCtrl),
                                           ucCidValue,
                                           pstPdpEntity->ucNsapi,
                                           (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
        }
#endif

        /* 激活成功，启动流量统计 */
        TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
    else
    {
        /*------------------------------------------------------------------
           主状态迁移至TAF_APS_STA_MS_DEACTIVATING
           子状态迁移至TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_Active
 功能描述  : ACTIVE主状态下收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  3.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: PS域呼叫建立流程优化

  4.日    期   : 2014年12月8日
    作    者   : A00165503
    修改内容   : DTS2014111302668: 匹配缺省PDN流程中, CID对应的剩余时长未清
                 除, 导致使用相同CID再次拨号后, 在匹配缺省PDN场景下未上报响
                 应事件, 拨号流程异常
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
#if (FEATURE_ON == FEATURE_IPV6)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 如果CID对应的剩余定时器时长为0, 需要上报响应事件 */
    if (0 == TAF_APS_GetCallRemainTmrLen(pstPppDialOrigReq->stPppDialParaInfo.ucCid))
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                  TAF_PS_CAUSE_SUCCESS);
    }

    TAF_APS_SetCallRemainTmrLen(pstPppDialOrigReq->stPppDialParaInfo.ucCid, 0);

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF事件 */
    TAF_APS_SndPdpActivateCnf(ucPdpId, pstPppDialOrigReq->stPppDialParaInfo.ucCid);

#if (FEATURE_ON == FEATURE_IPV6)
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    if (VOS_TRUE == pstPdpEntity->bitOpIpv6RaInfo)
    {
        /* 上报ID_EVT_TAF_PS_IPV6_INFO_IND事件 */
        TAF_APS_SndIpv6RaInfoNotifyInd(&(pstPppDialOrigReq->stCtrl),
                                       pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                       pstPdpEntity->ucNsapi,
                                       (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
    }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_APS_RAT_TYPE_LTE != TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);
    }
#endif
    /* 激活成功，启动流量统计 */
    TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_Active
 功能描述  : INACTIVE主状态下收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年6月28日
    作    者   : A00165503
    修改内容   : DTS2012062802394: 上报IPv6的RA信息时, 没有检查用户请求的拨
                 号类型是否为IPv6

  3.日    期   : 2012年6月30日
    作    者   : A00165503
    修改内容   : DTS2012062900707: IPv6拨号成功, 应用获取IPv6地址前缀异常

  4.日    期   : 2014年5月22日
    作    者   : A00165503
    修改内容   : DTS2013022201185: 呼叫建立流程优化

  5.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: IP类型从拨号参数中获取

  6.日    期   : 2014年12月8日
    作    者   : A00165503
    修改内容   : DTS2014111302668: 匹配缺省PDN流程中, CID对应的剩余时长未清
                 除, 导致使用相同CID再次拨号后, 在匹配缺省PDN场景下未上报响
                 应事件, 拨号流程异常
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#if (FEATURE_ON == FEATURE_IPV6)
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
#endif


    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 如果CID对应的剩余定时器时长为0, 需要上报响应事件 */
    if (0 == TAF_APS_GetCallRemainTmrLen(pstCallOrigReq->stDialParaInfo.ucCid))
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                               pstCallOrigReq->stDialParaInfo.ucCid,
                               TAF_PS_CAUSE_SUCCESS);
    }

    TAF_APS_SetCallRemainTmrLen(pstCallOrigReq->stDialParaInfo.ucCid, 0);

    /* 在ehrpd下，当前已经完成initial attach，存在默认承载cid=0，
        但是dhcp协商可能还没有协商完成,暂时不上报，协商结束上报 */
    if (VOS_FALSE == pstPdpEntity->ucNeedGetDnsFlg)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF事件 */
        TAF_APS_SndPdpActivateCnf(ucPdpId, pstCallOrigReq->stDialParaInfo.ucCid);
    }

#if (FEATURE_ON == FEATURE_IPV6)
    enPdpType    = pstCallOrigReq->stDialParaInfo.enPdpType;

    if ( ((TAF_PDP_IPV6 == enPdpType) || (TAF_PDP_IPV4V6 == enPdpType))
      && (VOS_TRUE == pstPdpEntity->bitOpIpv6RaInfo) )
    {
        /* 上报ID_EVT_TAF_PS_IPV6_INFO_IND事件 */
        TAF_APS_SndIpv6RaInfoNotifyInd(&(pstCallOrigReq->stCtrl),
                                       pstCallOrigReq->stDialParaInfo.ucCid,
                                       pstPdpEntity->ucNsapi,
                                       (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
    }
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_APS_RAT_TYPE_LTE != TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);
    }
#endif
    /* 激活成功，启动流量统计 */
    TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_Active
 功能描述  : 收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE  :处理消息失败
             VOS_TRUE   :处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /*-------------------------------------------------------
       平台能力支持CDMA，且当前驻留模式如果为3GPP2,
       则选择3GPP2流程，否则选择3GPP流程

       主状态迁移至TAF_APS_FSM_CDATA_DISCING
       子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

       在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_CALL_END_REQ消息
    -------------------------------------------------------*/
    if (VOS_TRUE == TAF_APS_IsEnterCdataDiscing())
    {
	    /* 上报PS呼叫挂断响应事件 */
        TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

        /* 加载TAF_APS_FSM_CDATA_DISCING状态机 */
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);
    }
    else
#endif
    {
        /*------------------------------------------------------------------
           主状态迁移至TAF_APS_STA_MS_DEACTIVATING
           子状态迁移至TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_CALL_END_REQ消息
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_Active
 功能描述  : 收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE :处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*------------------------------------------------------------------
       加载TAF_APS_STA_MS_MODIFYING状态机
       加载后子状态切换为TAF_APS_MS_MODIFYING_SUBSTA_INIT

       在TAF_APS_MS_MODIFYING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_MODIFYING,
                       TAF_APS_GetMsModifyingFsmDescAddr(),
                       TAF_APS_MS_MODIFYING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallAnswerReq_Active
 功能描述  : ACTIVE主状态下收到ID_MSG_TAF_PS_CALL_ANSWER_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq                    = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS域MT呼叫流程, 方案未确定, 目前直接返回ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallHangupReq_Active
 功能描述  : ACTIVE主状态下收到ID_MSG_TAF_PS_CALL_HANGUP_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS域MT呼叫流程, 方案未确定, 目前直接返回ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl),
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpModifyInd_Active
 功能描述  : 收到ID_PMC_SMREG_PDP_MODIFY_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_PMC_SMREG_PDP_MODIFY_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE  :处理消息失败
             VOS_TRUE   :处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpModifyInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    APS_MDFIND_PARA_ST                  stParam;
    SMREG_PDP_MODIFY_IND_STRU          *pstSmPdpModifyInd;
#if (FEATURE_ON == FEATURE_LTE)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif

    /* 获取消息内容 */
    pstSmPdpModifyInd = (SMREG_PDP_MODIFY_IND_STRU *)pstMsg;
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType     = TAF_APS_GetCurrPdpEntityRatType();
#if (FEATURE_ON == FEATURE_LTE)
    pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
#endif

    ulResult = Aps_PdpMdfIndParaCheck(pstSmPdpModifyInd, &stParam);
    if (APS_PARA_INVALID  == ulResult)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSmPdpModifyInd_Active: Check para failed! ");

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* 发送内部消息, 触发PDP去激活流程 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /* 检查QOS是否满足MIN */
    if (APS_PARA_VALID == Aps_CheckQosSatisify(ucPdpId, &stParam.NewQos))
    {
        /* 满足MINQOS */
        Aps_PdpMdfIndQosSatisfy(ucPdpId, &stParam, pstSmPdpModifyInd);

#if (FEATURE_ON == FEATURE_LTE)
        /* 同步PDP信息至ESM */
        MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_MODIFY);
#endif

        /* 如果当前模为GSM, 迁移状态 */
        if (TAF_APS_RAT_TYPE_GSM == enCurrRatType)
        {
            /*------------------------------------------------------------------
               加载TAF_APS_STA_MS_MODIFYING状态机
               加载后子状态切换为TAF_APS_MS_MODIFYING_SUBSTA_INIT

               在TAF_APS_MS_MODIFYING_SUBSTA_INIT子状态中
               处理D_PMC_SMREG_PDP_MODIFY_IND消息
            ------------------------------------------------------------------*/
            TAF_APS_InitSubFsm(TAF_APS_FSM_MS_MODIFYING,
                               TAF_APS_GetMsModifyingFsmDescAddr(),
                               TAF_APS_MS_MODIFYING_SUBSTA_INIT);
        }
    }
    else
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

        /* 发送内部消息, 触发PDP去激活流程 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_QOS_NOT_ACCEPTED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpDeactivateInd_Active
 功能描述  : 收到 ID_PMC_SMREG_PDP_DEACTIV_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_PMC_SMREG_PDP_DEACTIV_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE  :处理消息失败
             VOS_TRUE   :处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 初始化, 获取消息内容 */
    pstSmPdpDeactivateInd               = (SMREG_PDP_DEACTIVATE_IND_STRU*)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

    /* 同步PDP状态和信息至ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果是缺省承载且地址类型是IPv6, 需要同步给ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* 如果SNDCP已经激活, 释放SNDCP资源 */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤器 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmPdpModifyInd_Active
 功能描述  : 收到 ID_APP_ESM_PDP_MODIFY_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_APP_ESM_PDP_MODIFY_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE  :处理消息失败
             VOS_TRUE   :处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，记录LTE上报的EPSQOS
  3.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpModifyInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APP_ESM_PDP_MODIFY_IND_STRU        *pstPdpModify;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    pstPdpModify = (APP_ESM_PDP_MODIFY_IND_STRU*)pstMsg;

    /* 初始化, 获取PDP ID */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 如果不是默认承载，则上报，默认承载不上报 */
    if (TAF_APS_DEFAULT_CID != pstPdpModify->ulCid)
    {
        if (VOS_TRUE == pstPdpModify->bitOpSdfQos)
        {
            pstPdpEntity->bitOpEpsQos   = VOS_TRUE;
            PS_MEM_CPY((VOS_UINT8 *)&pstPdpEntity->stEpsQos,
                       (VOS_UINT8 *)&pstPdpModify->stSdfQosInfo,
                       sizeof(TAF_EPS_QOS_STRU));
        }

        /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFIED_IND事件 */
        TAF_APS_SndPdpModifyInd(ucPdpId);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmPdpDeactivateInd_Active
 功能描述  : 收到 ID_L4A_APS_PDP_DEACTIVATE_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_L4A_APS_STA_DEACTIVATE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE  :处理消息失败
             VOS_TRUE   :处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2014年8月21日
    作    者   : A00165503
    修改内容   : DTS2014081803666: 增加SNDCP激活状态判断, 如果SNDCP处于激活
                 状态, 需将其去激活

  3.日    期  : 2015年5月29日
    作    者  : a00165503
    修改内容  :  MODIFY for DTS2015051204781

  4.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    APP_ESM_PDP_RELEASE_IND_STRU       *pstEsmPdpDeactivateInd;

    /* 获取消息内容 */
    pstEsmPdpDeactivateInd = (APP_ESM_PDP_RELEASE_IND_STRU*)pstMsg;

    /* 获取当前状态机的APS索引 */
    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取该索引的APS实体内容地址 */
    pstPdpEntity           = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

    /* 如果不是默认承载，则上报，默认承载不上报 */
    if (TAF_APS_DEFAULT_CID != pstPdpEntity->stClientInfo.ucCid)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件上报 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapEsmCause(pstEsmPdpDeactivateInd->ulRslt));
    }
    else
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_DISCONNECTED);
#endif
    }

    /* 如果SNDCP已经激活, 释放SNDCP资源 */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmPdpSetupInd_Active
 功能描述  : 收到ID_APP_ESM_PDP_SETUP_IND消息的处理
 输入参数  : ulEventType: 消息类型
             pstMsg     : ID_APP_ESM_PDP_SETUP_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE  : 处理消息失败
             VOS_TRUE   : 处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月19日
    作    者   : w00316404
    修改内容   : 新生成函数

  2.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project

  3.日    期   : 2015年01月28日
    作    者   : w00316404
    修改内容   : send pdp activate inf to ND Client

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpSetupInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_IMS) || (FEATURE_ON == FEATURE_IPV6)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
#endif

#if (FEATURE_ON == FEATURE_IMS)
    /* 处理IMS专有承载 */
    TAF_APS_ProcImsDedicateBearer(pstPdpEntity);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果地址类型是IPv6, 需要同步给ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                               pstPdpEntity->PdpAddr.aucIpV6Addr);
    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmSmEpsBearerInfoInd_Active
 功能描述  : ACTIVE主状态下收到ID_ESM_SM_EPS_BEARER_INFO_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月07日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;

    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);


    /* 根据EPS承载的操作类型(Activate, Deactivate, Modify),
       调用相应的处理函数 */
    if (SM_ESM_PDP_OPT_MODIFY == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptModify(pstPdpEntity, pstBearerInfo);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            /* 发送内部消息，所有正在激活过程中的状态机都需要处理该消息 */
            TAF_APS_SndInterAttachBearerActivateInd();
            /* 记录当前的PS服务所在的模式 */
            TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);
            /* 通知外部模块当前的PS服务所在的模式 */
            TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_LTE);

            TAF_APS_SET_CDATA_MTU(0);
        }

        /* 上报给AP */
        TAF_APS_SndCgmtuValueChangeInd(0);

#endif
    }
    else if (SM_ESM_PDP_OPT_DEACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptDeactivate(pstPdpEntity, pstBearerInfo);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive: Wrong option.");
    }

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSndcpActivateRsp_Active
 功能描述  : TAF_APS_STA_ACTIVE状态下收到APS_SN_DEACT_RSP_MSG_TYPE消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月6日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    APS_SNDCP_ACTIVATE_RSP_ST          *pstSnActivateRsp;

    /* 初始化, 获取消息内容 */
    ulResult         = VOS_OK;
    pstSnActivateRsp = &((APS_SNDCP_ACTIVATE_RSP_MSG*)pstMsg)->ApsSnActRsp;
    ucPdpId          = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity     = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 检查消息参数 */
    ulResult = Aps_SnMsgModSnActRspParaCheck(pstSnActivateRsp);
    if (APS_PARA_VALID != ulResult)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSndcpActivateRsp_Active: Check para failed!");

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* 发送内部消息, 触发PDP去激活流程 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /* 收到SN_ACT_RSP后修改APS实体参数, 包括XID参数, TRANSMODE */
    Aps_SnActRspChngEntity(pstSnActivateRsp, ucPdpId);

    /* 设置RABM的传输模式 */
    TAF_APS_SndRabmSetTransModeMsg(pstSnActivateRsp->ucNsapi,
                                   pstPdpEntity->GprsPara.TransMode);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSndcpDeactivateRsp_Active
 功能描述  : TAF_APS_STA_ACTIVE状态下收到APS_SN_DEACT_RSP_MSG_TYPE消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月6日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpDeactivateRsp_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 在TAF_APS_STA_ACTIVE状态下, 目前不需要处理APS_SN_DEACT_RSP_MSG_TYPE */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSndcpDeactivateRsp_Active
 功能描述  : TAF_APS_STA_ACTIVE状态下收到APS_SN_STATUS_REQ_MSG_TYPE消息的处理
 输入参数  : ulEventType    - 消息ID
             pstMsg         - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE       - 消息处理成功
             VOS_FALSE      - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年6月20日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq;

    pstSnStatusReq = &((APS_SNDCP_STATUS_REQ_MSG*)pstMsg)->ApsSnStatusReq;
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();

    ulRslt = TAF_APS_ValidatePdpForSnStatusReq(ucPdpId, pstSnStatusReq);
    if (VOS_TRUE == ulRslt)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* 发送内部消息, 触发PDP去激活流程 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvRabmSysChgToGprs_Active
 功能描述  : 收到 ID_RABM_APS_SYS_CHG_TO_GPRS消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_RABM_MN_SYS_LTE_CHG_TO_GPRS消息
 输出参数  : 无
 返 回 值  : VOS_FALSE  :处理消息失败
             VOS_TRUE   :处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvRabmSysChgToGprs_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取当前状态机的APS实体索引 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 检查SNDCP激活标识, 激活SNDCP */
    if (APS_SNDCP_INACT == TAF_APS_GetPdpEntSndcpActFlg(ucPdpId))
    {
        Aps_RabmMsgActSndcp(ucPdpId);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvRabmLocalPdpDeactivateReq_Active
 功能描述  : 收到 RABM_APS_LOCAL_PDP_DEACT_REQ_MSG消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_RABM_APS_LOCAL_PDP_DEACT_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE  :处理消息失败
             VOS_TRUE   :处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvRabmLocalPdpDeactivateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    /* 获取当前状态机的接入技术 */
    enCurrRatType = TAF_APS_GetCurrPdpEntityRatType();

    /* 获取当前状态机的APS实体索引 */
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* 在GU模下处理该消息, LTE模直接丢弃 */
    if (TAF_APS_RAT_TYPE_WCDMA == enCurrRatType)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_RAB_SETUP_FAILURE);

        /* 发送内部消息, 去激活PDP */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsInternalPdpDeactivateReq_Active
 功能描述  : ACTIVE主状态下收到ID_APS_APS_INTER_PDP_DEACTIVATE_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsInternalPdpDeactivateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /*-------------------------------------------------------
       平台能力支持CDMA，且当前驻留模式如果为3GPP2,
       则选择3GPP2流程，否则选择3GPP流程

       主状态迁移至TAF_APS_FSM_CDATA_DISCING
       子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

       在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_CALL_END_REQ消息
    -------------------------------------------------------*/
    if (VOS_TRUE == TAF_APS_IsEnterCdataDiscing())
    {
        /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_INTER_DEACTIVE,
                                       TAF_APS_INTER_END_CALL_REASON_USER_END,
                                       TAF_APS_GetCurrFsmEntityPdpId(),
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }
    else
#endif
    {
        /*------------------------------------------------------------------
           加载TAF_APS_STA_MS_DEACTIVATING状态机
           加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中处理
           ID_APS_APS_INTER_PDP_DEACTIVATE_REQ消息
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsLocalPdpDeactivateReq_Active
 功能描述  : 收到 TAF_APS_RcvApsLocalPdpDeactivateInd_Active消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE  :处理消息失败
             VOS_TRUE   :处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月05日
    作    者   : f00179208
    修改内容   : 新生成函数

  2.日    期   : 2014年12月2日
    作    者   : A00165503
    修改内容   : DTS2014111805277: 缺省承载本地去激活时, 需要去激活与其关联
                 的专用承载
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                               ucPdpId;
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;

    /* 初始化, 获取消息内容 */
    pstLocalMsg                         = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;
    ucPdpId                             = pstLocalMsg->ucPdpId;
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

    /* 同步PDP状态和信息至ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* 通知EHSM清除LTE同步的PDN信息 */
        TAF_APS_SndEhsmLocDeactNtf(ucPdpId);
    }

#endif

    /* 向SM发送本地去激活请求 */
    if (VOS_TRUE == pstPdpEntity->bitOpTransId)
    {
        TAF_APS_SndSmPdpLocalDeactivateReq(ucPdpId);
    }

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果是缺省承载且地址类型是IPv6, 需要同步给ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* 如果SNDCP已经激活, 释放SNDCP资源 */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstLocalMsg->enCause));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤器 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterServiceStatusChangeInd_Active
 功能描述  : 收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE :处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2013年01月21日
    作    者   : A00165503
    修改内容   : DTS2013011803709: 激活ND Client增加接入技术判断, 防止在NULL
                 状态下激活ND Client导致RS包被丢弃

  3.日    期   : 2013年4月23日
    作    者   : A00165503
    修改内容   : DTS2013041204937: 专用承载激活时不需要激活ND Client

  4.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 修改入口消息

  5.日    期   : 2015年7月22日
    作    者   : Y00213812
    修改内容   : 修改函数名，增加L->1X的切换操作
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterServiceStatusChangeInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    /* 获取消息内容 */
    pstServStaChangeInd  = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* 获取当前状态机的APS实体索引 */
    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();

    switch (pstServStaChangeInd->enRatType)
    {
        /* 当前模为GSM时, 不依靠该消息激活SNDCP */
        case TAF_APS_RAT_TYPE_GSM:
            break;

        /* 当前模为WCDMA/LTE时, 需要去激活SNDCP */
        case TAF_APS_RAT_TYPE_WCDMA:
        case TAF_APS_RAT_TYPE_LTE:
            if (APS_SNDCP_ACT == TAF_APS_GetPdpEntSndcpActFlg(ucPdpId))
            {
                Aps_RabmMsgDeActSndcp(ucPdpId);
            }

        /* 如果之前承载建立在1X上的，由AP来去激活 */

            break;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TAF_APS_RAT_TYPE_1X:
            /* TO DO: 原来是LTE该如何修改 */
            /* 同步PDP信息至ESM */
#if (FEATURE_ON == FEATURE_LTE)
            if (TAF_APS_RAT_TYPE_LTE == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId), SM_ESM_PDP_OPT_DEACTIVATE);

                /* 通知EHSM清除LTE同步的PDN信息 */
                TAF_APS_SndEhsmLocDeactNtf(ucPdpId);


                /* 停止流量统计 */
                TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

                /* 上报去激活的事件 */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);
                /* 本地去激活 */
                TAF_APS_LocalReleaseProc(ucPdpId);
            }
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {

                /* 停止流量统计 */
                TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

                /* 上报去激活的事件 */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

                /* 本地去激活 */
                TAF_APS_LocalReleaseProc(ucPdpId);
            }
#endif
            break;
#endif
        case TAF_APS_RAT_TYPE_NULL:
        default:
            break;
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDiscInd_Active
 功能描述  : ACTIVE主状态下收到ID_XCC_APS_DATA_CALL_DISC_IND消息的处理
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

  2.日    期   : 2015年1月7日
    作    者   : g00261581
    修改内容   : 判断进入Dormant后是否启动Dormant TI
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDiscInd   = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    /* 更新实体保存的原因值 */
    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    if (TAF_PS_CAUSE_XCC_AS_SO_REJ == pstPdpEntity->enCause)
    {
        /******************************************************************************/
        /*               SO Rej 原因值需要特殊处理，本地去激活                        */
        /******************************************************************************/

        if (TAF_APS_CDATA_PPP_STATE_INACTIVE != TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* 收到网侧的SO_REJ，上报去激活的事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, pstPdpEntity->enCause);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        return VOS_TRUE;
    }
    else
    {
        TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_NO_LINK);

        /* 通知PPP当前链路不存在 */
        TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_NOT_EXISTED);

        /* 断链的原因值不为So rej, TAF APS进入Dormant状态 */
        TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_TRUE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEnterDormantInd_Active
 功能描述  : ACTIVE主状态下收到ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvPsCallEnterDormantInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataServiceMode;

    enDataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();

    if (TAF_APS_RAT_TYPE_EHRPD == enDataServiceMode)
    {
        /* EHRPD模式下只通知EHSM进入DORMANT状态，APS的状态不改变 */
        TAF_APS_SndEhsmDiscNtf();
    }
    else if ((TAF_APS_RAT_TYPE_1X   == enDataServiceMode)
          || (TAF_APS_RAT_TYPE_HRPD == enDataServiceMode))
    {
        /*------------------------------------------------------------------
           主状态迁移至TAF_APS_FSM_CDATA_DISCING
           子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

           在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND消息
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);
    }
    else
    {
        /* Do nothing */
        TAF_WARNING_LOG1(WUEPS_PID_TAF,"TAF_APS_RcvPsCallEnterDormantInd_Active not cdma mode", enDataServiceMode);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallInterEpdszidReOrig_Active
 功能描述  : In Active State, After Rcv Epdszid ReOrig Req, Only add Current EPDSZID into zone List
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallInterEpdszidReOrig_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_CDATA_EPDSZID_STRU         *pstCurrEpdszid;

    pstCurrEpdszid = TAF_APS_GetCurrEpdszidInfo();

    /* Add EPDSZID into Packet Zone List */
    TAF_APS_AddEpdszidToZoneList(pstCurrEpdszid);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccUpdateDataCallInfoInd_Active
 功能描述  : Processing message:ID_XCC_APS_UPDATE_DATA_CALL_INFO_IND, This Message is only
             processed in Active, other state is discarded.
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
VOS_UINT32 TAF_APS_RcvXccUpdateDataCallInfoInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU     *pstDataCallInof = VOS_NULL_PTR;
    VOS_UINT8                                   ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDataCallInof = (XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU *)pstMsg;

    /* Only Update SR_ID Now */
    if (pstDataCallInof->ucSrId != TAF_APS_GetPdpEntSrId(ucPdpId))
    {
        TAF_APS_SetPdpEntSrId(ucPdpId, pstDataCallInof->ucSrId);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvCdsServiceInd_Active
 功能描述  : ACTIVE主状态下收到ID_CDS_APS_SERVICE_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvCdsServiceInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode;

    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrCdataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();

    if (TAF_APS_RAT_TYPE_EHRPD == enCurrCdataServiceMode)
    {
        TAF_APS_SndEhsmReconnReq(ucPdpId);
    }
    else
    {
        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmDiscInd_Active
 功能描述  : ACTIVE主状态下收到ID_HSM_APS_DISC_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月6日
    作    者   : Y00213812
    修改内容   : 新生成函数

  2.日    期   : 2015年11月9日
    作    者   : g00261581
    修改内容   : 等待PPP协商的过程从Active状态中挪出去，此状态下可以直接迁移-
                 Dormant

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    HSM_APS_DISC_IND_STRU              *pstDiscInd = VOS_NULL_PTR;

    /* 初始化, 获取消息内容 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd      = (HSM_APS_DISC_IND_STRU *)pstMsg;

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_NO_LINK);

    /* 通知PPP当前链路不存在 */
    TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_NOT_EXISTED);

    TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    if (HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X == pstDiscInd->enCause)
    {
        TAF_APS_SetIsHrpdDisabledFlag(VOS_TRUE);
        TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_1X);

        /* 发送内部HRPD到1X切换请求消息 */
        TAF_APS_SndInterHrpdTo1XHandOffReq(ucPdpId);
    }
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactInd_Active
 功能描述  : ACTIVE主状态下收到ID_PPP_APS_DEACT_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvPppDeactInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 更新原因值 */
    pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_NW_DISC;

    /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_ACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /*------------------------------------------------------------------
       主状态迁移至TAF_APS_FSM_CDATA_DISCING
       子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

       在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
       处理ID_PPP_APS_DEACT_IND消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppModifyInd_Active
 功能描述  : ACTIVE主状态下收到ID_PPP_APS_MODIFY_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvPppModifyInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    PPP_APS_MODIFY_IND_STRU            *pstModifyInd;
    TAF_PDP_TYPE_ENUM_UINT8             enPdnType;
    VOS_INT32                           lCmpRst;

    /* 初始化, 获取消息内容 */
    lCmpRst        = VOS_ERROR;
    pstModifyInd   = (PPP_APS_MODIFY_IND_STRU*)pstMsg;
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    enPdnType      = TAF_APS_MapPppPdnTypeToAps(pstModifyInd->enPdnType);

    if (APS_ADDR_INVALID == enPdnType)
    {
        return VOS_TRUE;
    }

    if (pstPdpEntity->PdpAddr.ucPdpTypeNum != enPdnType)
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY,
                                       TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_MODE_CHANGE;

        return VOS_TRUE;
    }

    /* 判断PPP的类型 */
    switch (pstModifyInd->enPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:

            lCmpRst = PS_MEM_CMP(pstPdpEntity->PdpAddr.aucIpAddr,
                                 pstModifyInd->aucIpv4Addr,
                                 TAF_APS_PPP_IPV4_ADDR_LEN);
            break;

        case TAF_APS_PPP_ADDR_TYPE_IPV6:

            lCmpRst =  PS_MEM_CMP(pstPdpEntity->PdpAddr.aucIpV6Addr,
                                  pstModifyInd->aucIpv6Addr,
                                  TAF_APS_PPP_IPV6_ADDR_LEN);

            break;

        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:

            lCmpRst = PS_MEM_CMP(pstPdpEntity->PdpAddr.aucIpV6Addr,
                                 pstModifyInd->aucIpv6Addr,
                                 TAF_APS_PPP_IPV6_ADDR_LEN);

            if ((0 != PS_MEM_CMP(pstPdpEntity->PdpAddr.aucIpAddr,
                                 pstModifyInd->aucIpv4Addr,
                                 TAF_APS_PPP_IPV4_ADDR_LEN))
             || (0 != lCmpRst))
            {
                lCmpRst = VOS_ERROR;

            }

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvPppModifyInd_Active:Wrong Msg Entry");
            break;
    }

    if (0 != lCmpRst)
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY,
                                       TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_MODE_CHANGE;
        return VOS_TRUE;
    }

    if (pstModifyInd->usMtu != TAF_APS_GET_CDATA_MTU())
    {
        TAF_APS_SET_CDATA_MTU(pstModifyInd->usMtu);

        TAF_APS_SndCgmtuValueChangeInd(pstModifyInd->usMtu);
    }
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmPdnInfoChgInd_Active
 功能描述  : 处理ehsm的pdn变化消息
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
VOS_UINT32 TAF_APS_RcvEhsmPdnInfoChgInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_INFO_CHANGE_IND_STRU  *pstPdnChgInd;
    VOS_UINT8                           ucPdpId;
    VOS_INT32                           lCmpIpv4AddrRst;
    VOS_INT32                           lCmpIpv6AddrRst;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpType;

    /* 初始化, 获取消息内容 */
    pstPdnChgInd    = (EHSM_APS_PDN_INFO_CHANGE_IND_STRU*)pstMsg;
    ucPdpId         = TAF_APS_GetPdpIdByCid(pstPdnChgInd->ucCid);
    lCmpIpv4AddrRst = 0;
    lCmpIpv6AddrRst = 0;
    ucPdpType       = TAF_APS_MapEhsmPdnTypeToAps(pstPdnChgInd->stPdnChgInfo.stPdnAddr.enPdnType);

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (APS_ADDR_INVALID == ucPdpType)
    {
        return VOS_TRUE;
    }

    if (pstPdpEntity->PdpAddr.ucPdpTypeNum != ucPdpType)
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY,
                                       TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_MODE_CHANGE;

        return VOS_TRUE;
    }

    switch (pstPdnChgInd->stPdnChgInfo.stPdnAddr.enPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:
            lCmpIpv4AddrRst                     = PS_MEM_CMP(pstPdnChgInd->stPdnChgInfo.stPdnAddr.aucIpv4Addr,
                                                             pstPdpEntity->PdpAddr.aucIpAddr,
                                                             TAF_IPV4_ADDR_LEN);
            break;

        case TAF_APS_PPP_ADDR_TYPE_IPV6:
            lCmpIpv6AddrRst                     = PS_MEM_CMP(pstPdnChgInd->stPdnChgInfo.stPdnAddr.aucIpv6Addr,
                                                             pstPdpEntity->PdpAddr.aucIpV6Addr,
                                                             TAF_IPV6_PREFIX_LEN);

            break;

        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:
            lCmpIpv4AddrRst                     = PS_MEM_CMP(pstPdnChgInd->stPdnChgInfo.stPdnAddr.aucIpv4Addr,
                                                             pstPdpEntity->PdpAddr.aucIpAddr,
                                                             TAF_IPV4_ADDR_LEN);

            lCmpIpv6AddrRst                     = PS_MEM_CMP(pstPdnChgInd->stPdnChgInfo.stPdnAddr.aucIpv6Addr,
                                                             pstPdpEntity->PdpAddr.aucIpV6Addr,
                                                             TAF_IPV6_PREFIX_LEN);

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnInfoChgInd_Active:Wrong Msg Entry");
            break;
    }

    /* 给EHSM发送去激活消息 */
    if ((0 != lCmpIpv4AddrRst)
     || (0 != lCmpIpv6AddrRst))
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY,
                                       TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_MODE_CHANGE;
        return VOS_TRUE;
    }

    if (pstPdnChgInd->stPdnChgInfo.usMtu != TAF_APS_GET_CDATA_MTU())
    {
        TAF_APS_SET_CDATA_MTU(pstPdnChgInd->stPdnChgInfo.usMtu);

        TAF_APS_SndCgmtuValueChangeInd(pstPdnChgInd->stPdnChgInfo.usMtu);
    }
    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterEndCdmaCallReq_Active
 功能描述  : 主状态下收到ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ消息的处理
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

  2.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : ACTIVE状态下收到内部去激活，直接加载去激活状态机
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
   /*------------------------------------------------------------------
       主状态迁移至TAF_APS_FSM_CDATA_DISCING
       子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

       在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_INTERNAL_DISC_SO_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}




/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterServiceStatusChangeReq_Dormant
 功能描述  : DORMANT状态下收到TAF的服务状态信息
             ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND通知的处理
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
  2.日    期   : 2015年03月24日
    作    者   : y00314741
    修改内容   : Iteration 11
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterServiceStatusChangeReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                     ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32                  enCurrCdataServiceMode;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU *pstServStaChange = VOS_NULL_PTR;

    /* 获取PDP ID */
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取消息内容 */
    pstServStaChange  = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /*获取当前建立数据服务的模式*/
    enCurrCdataServiceMode  = TAF_APS_GetCurrPdpEntityDataServiceMode();

    /* 根据传入接入技术分别处理 */
    if (TAF_APS_RAT_TYPE_HRPD == pstServStaChange->enRatType)
    {
         /* 从1X切换到HRPD */
        if (TAF_APS_RAT_TYPE_1X == enCurrCdataServiceMode)
        {
            TAF_APS_Proc1xToHrpdHandOff(ucPdpId, pstServStaChange->ucIsNewSession);
        }
    }
    else if (TAF_APS_RAT_TYPE_1X == pstServStaChange->enRatType)
    {
        /* 从HRPD切换到1X */
        if (TAF_APS_RAT_TYPE_HRPD == enCurrCdataServiceMode)
        {
            /* 发送内部HRPD到1X切换请求消息 */
            TAF_APS_SndInterHrpdTo1XHandOffReq(ucPdpId);
        }
    }
    else if (TAF_APS_RAT_TYPE_LTE   == pstServStaChange->enRatType)
    {
        if (TAF_APS_RAT_TYPE_1X == enCurrCdataServiceMode)
        {
            /* 发起1X dormant态去激活 */
            TAF_APS_SndInterEnd1xServiceInDormantInd(ucPdpId);
        }

        if (TAF_APS_RAT_TYPE_HRPD == enCurrCdataServiceMode)
        {
            /* 上报去激活的事件 */
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);
            /* 本地去激活 */
            TAF_APS_LocalReleaseProc(ucPdpId);

            /* 通知外部模块PS模式切换 */
            TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);
        }
    }
    else if (TAF_APS_RAT_TYPE_EHRPD == pstServStaChange->enRatType)
    {
        /* 上报去激活的事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);
        /* 本地去激活 */
        TAF_APS_LocalReleaseProc(ucPdpId);
        /* 通知外部模块PS模式切换 */
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);
    }
    else
    {
        ;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvCdsServiceInd_Dormant
 功能描述  : DORMANT主状态下收到ID_CDS_APS_SERVICE_IND消息的处理
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

VOS_UINT32 TAF_APS_RcvCdsServiceInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if ((TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
     || (TAF_APS_CDMA_TC_SUSPENDED == TAF_APS_GET_CDATA_SUSPEND_STATUS()))
    {
        /* 给CDS发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息 */
        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

        return VOS_TRUE;
    }

    /*-------------------------------------------------------
       加载TAF_APS_FSM_CDATA_ESTING状态机
       加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppReConnInd_Dormant
 功能描述  : Dormant状态下收到消息ID_PPP_APS_RECONN_IND的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppReConnInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if ((TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
     || (TAF_APS_CDMA_TC_SUSPENDED == TAF_APS_GET_CDATA_SUSPEND_STATUS()))
    {
        TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_NOT_EXISTED);

        return VOS_TRUE;
    }

    /*-------------------------------------------------------
       加载TAF_APS_FSM_CDATA_ESTING状态机
       加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactInd_Dormant
 功能描述  : Dormant状态下收到消息ID_PPP_APS_DEACT_NTF的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报网侧去激活事件 */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_PPP_NW_DISC);

    /* 停止Dormant 定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccIncomingCallInd_Dormant
 功能描述  : DORMANT主状态下收到ID_XCC_APS_INCOMING_CALL_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        /* 停止Dormant 定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);
    }

    /*-------------------------------------------------------
       加载TAF_APS_FSM_CDATA_ESTING状态机
       加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallOrigReq_Dormant
 功能描述  : DORMANT主状态下收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvPsCallOrigReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 上报激活成功 */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                           pstCallOrigReq->stDialParaInfo.ucCid,
                           TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsPppDialOrigReq_Dormant
 功能描述  : DORMANT主状态下收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月06日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsPppDialOrigReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 上报激活成功 */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                              TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_Dormant
 功能描述  : DORMANT主状态下收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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

  2.日    期   : 2015年11月11日
    作    者   : g00261581
    修改内容   : 重构Dormant状态下的去激活流程
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallEndReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* 初始化, 获取PDP ID */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取PPP状态 */
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /****************************************************************************************************/
    /*             1. Dormant timer运行期间，不再发起建链请求，不需要加载去激活状态机                   */
    /*             2. PPP状态为Inactive(中继模式), 不需要去激活协商，不需要建链，故不加载去激活状态机   */
    /****************************************************************************************************/
    if ((TAF_APS_TIMER_STATUS_RUNING      == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
     || (TAF_APS_CDATA_PPP_STATE_INACTIVE == enPppState))
    {
        /* 停止Dormant 定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

        /* 如果当前的PPP状态是激活的 */
        if (TAF_APS_CDATA_PPP_STATE_ACTIVE == enPppState)
        {
            /* 向PPP发送deact ind */
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* 上报去激活的事件 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        return VOS_TRUE;
    }

    /*----------------------------------------------------------------------------
       DORMANT状态下去激活，加载去激活状态机，先建链，再做PPP去激活协商，再断链
    ----------------------------------------------------------------------------*/
    /* 加载TAF_APS_FSM_CDATA_DISCING状态机 */
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallInterEpdszidReOrig_Dormant
 功能描述  : When In Dormant State,Rcv Epdszid Re-Orig Req Msg
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallInterEpdszidReOrig_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* Get PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* If Dormant Timer is running ,Set Epdszid ReOrig Flag */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        /* Don't start Re-Orig right now , Only Set the Epdszid Re-Orig scene After Dormant Ti expired */
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_REORIG_AFTER_DORMANT_TI_EXPIRED);
    }
    else
    {
        /* Start Re-Orig */
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                           TAF_APS_GetCdataEstingFsmDescAddr(),
                           TAF_APS_CDATA_ESTING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiDormantTimerExpired_Dormant
 功能描述  : In Dormant State, Dormant Timer is Expried ,Process Re-Orig
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月31日
    作    者   : g00261581
    修改内容   : 新生成函数
 修改历史      :
  2.日    期   : 2015年03月27日
    作    者   : y00314741
    修改内容   : Iteration 11

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiDormantTimerExpired_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* If Re-Orig Pending Status is TRUE, After Dormant Timer Expired, Start Re-Orig Again */
    if (TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG != TAF_APS_GetEpdszidChgReOrigScene())
    {
        /* Snd Inter Msg To Re-Orig */
        TAF_APS_SndInterEpdszidReOrigReq();

        /* Esting Fsm is started, Set Re-Orig Secne BuTT */
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
    }
    else
    {
        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccResumeInd_Dormant
 功能描述  : When in Dormant state, rcv Resume Ind msg ,start re_orig
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月4日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccResumeInd_Dormant(

    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* Get PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        return VOS_TRUE;
    }

    /* If Re-Orig Pending Status is TRUE, After Traffic channel exist Expired, Start Re-Orig Again */
    if (TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG != TAF_APS_GetEpdszidChgReOrigScene())
    {
        /* Snd Inter Msg to Re-Orig */
        TAF_APS_SndInterEpdszidReOrigReq();

        /* Esting Fsm is started, Set Re-Orig Secne BuTT */
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
    }
    else
    {
        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmCalConnectInd_Dormant
 功能描述  : In Dormant State, Receive CONNECT_IND,
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
VOS_UINT32 TAF_APS_RcvHsmCalConnectInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTED);

    /* 启动流量上报定时器 */
    TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    /* 主状态迁移至TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);


    /* 通知外部模块当前的PS服务所在的模式 */
    TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_HRPD);

    TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallInter1XToHrpdHandOff_Dormant
 功能描述  : 收到内部1X到HRPD切换消息消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月01日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallInter1XToHrpdHandOff_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*-------------------------------------------------------
     加载TAF_APS_FSM_CDATA_HANDOFF状态机
     加载后子状态切换为TAF_APS_CDATA_HANDOFF_SUBSTA_INIT

     在TAF_APS_CDATA_HANDOFF_SUBSTA_INIT子状态中处理
     ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ消息
     -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_HANDOFF,
                       TAF_APS_GetCdataHandOffFsmDescAddr(),
                       TAF_APS_CDATA_HANDOFF_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallInterHrpdTo1XHandOff_Dormant
 功能描述  : 收到内部HRPD到1X切换消息消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月01日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallInterHrpdTo1XHandOff_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*-------------------------------------------------------
     加载TAF_APS_FSM_CDATA_ESTING状态机
     加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

     在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
     ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ消息
     -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEHsmPdnDeactInd_Active
 功能描述  : ACTIVE主状态下收到ID_EHSM_APS_PDN_DEACTIVATE_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEHsmPdnDeactInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    EHSM_APS_PDN_DEACTIVATE_IND_STRU   *pstEhsmPdnDeactInd;

    /* 获取消息内容 */
    pstEhsmPdnDeactInd    = (EHSM_APS_PDN_DEACTIVATE_IND_STRU *)pstMsg;
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();
    ucCid                 = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    pstPdpEntity          = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 记录失败原因值 */
    pstPdpEntity->enCause = TAF_APS_MapEhsmCause(pstEhsmPdnDeactInd->enCause);

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    /* 如果不是默认承载，则上报，默认承载不上报 */
    if (TAF_APS_DEFAULT_CID != ucCid)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件上报 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, pstPdpEntity->enCause);
    }
    else
    {
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_DISCONNECTED);
    }

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmLteHandoverToEhrpdInd_Active
 功能描述  : ACTIVE主状态下收到ID_EHSM_APS_PDN_MODIFY_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月19日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmLteHandoverToEhrpdInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU                *pstLteHandoverInd;
    VOS_UINT8                                               ucPdpId;

    VOS_UINT32                                              ulIsNeedDeactPdn;
    VOS_UINT8                                               aucIpv6Prefix[TAF_IPV6_PREFIX_LEN];
    APS_PDP_CONTEXT_ENTITY_ST                              *pstPdpEntity;

    pstLteHandoverInd = (EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU *)pstMsg;
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    ulIsNeedDeactPdn  = VOS_FALSE;

    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    if (EHSM_APS_PDN_OPTION_MODIFIED == pstLteHandoverInd->enPdnOption)
    {
        TAF_APS_ProcPdnInfoChg_LteHandoverToEhrpdScene(ucPdpId, pstLteHandoverInd, &ulIsNeedDeactPdn);

        if (VOS_TRUE == ulIsNeedDeactPdn)
        {
            TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY,
                                           TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED,
                                           ucPdpId,
                                           TI_TAF_APS_CDATA_DISCING_LEN);
            return VOS_TRUE;
        }

        PS_MEM_SET(aucIpv6Prefix, 0, TAF_IPV6_PREFIX_LEN);

        if ((EHSM_APS_PDN_TYPE_IPV6   == pstLteHandoverInd->stPdnAddr.enPdnType)
         || (EHSM_APS_PDN_TYPE_IPV4V6 == pstLteHandoverInd->stPdnAddr.enPdnType))
        {
            if (0 != PS_MEM_CMP(pstLteHandoverInd->stPdnAddr.aucIpv6Addr, aucIpv6Prefix, TAF_IPV6_PREFIX_LEN))
#if 0
             && (VOS_TRUE != pstPdpEntity->ulNdClientActiveFlg))
#endif
            {
                TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                       pstPdpEntity->PdpAddr.aucIpV6Addr);

#if 0
                pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;
#endif

                /* 在不做dhcp协商，但是IPV6的地址必然需要协商，在IPV6地址协商成功后，需要上报，故刷新次变量 */
                pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_TRUE;

            }
        }

        TAF_APS_ProcModifyReq_LteHandoverToEhrpdScene(ucPdpId, pstLteHandoverInd);

        if (pstLteHandoverInd->usMtu != TAF_APS_GET_CDATA_MTU())
        {
            TAF_APS_SET_CDATA_MTU(pstLteHandoverInd->usMtu);

            /* MTU变化后需要上报给AP */
            TAF_APS_SndCgmtuValueChangeInd(pstLteHandoverInd->usMtu);
        }

         /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

    }
    else if (EHSM_APS_PDN_OPTION_DEACTIVED == pstLteHandoverInd->enPdnOption)
    {
        TAF_APS_ProcLocDeactBear_MsDeactivating_LteMode();
    }
    else
    {
        ;
    }

    /* 通知外部模块当前的PS服务所在的模式 */
    TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_EHRPD);

    /* 发送内部消息，其它正在激活过程中的状态机需要处理此消息 */
    TAF_APS_SndInterAttachBearerActivateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmPdnActInd_Inactive
 功能描述  : ACTIVE主状态下收到ID_EHSM_APS_PDN_ACTIVATE_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月19日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnActInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_IND_STRU     *pstPdnActInd;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;
    MN_APS_PDP_IPV6_DNS_STRU           *pstPdpIpv6Dns;

    pstPdnActInd = (EHSM_APS_PDN_ACTIVATE_IND_STRU *)pstMsg;

    /* 获取该PDPID的PDP实体内容地址 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 更新PdnId, APN, PdnAdrr */
    pstPdpEntity->ucNsapi       = pstPdnActInd->ucRabId;
    pstPdpEntity->PdpNsapiFlag  = VOS_TRUE;
    pstPdpEntity->ActType       = APS_PDP_ACT_PRI;

    TAF_APS_SetPdpEntCdataPdnId(ucPdpId, pstPdnActInd->ucPdnId);

    TAF_APS_UpdateCdataEhsmPdnInfo(  pstPdpEntity,
                                   &(pstPdnActInd->stPdnAddr),
                                   &(pstPdnActInd->stApn),
                                   &(pstPdnActInd->stIpv4Dns));

    if (TAF_APS_DEFAULT_CID == pstPdnActInd->ucCid)
    {
        TAF_APS_SndInterAttachBearerActivateInd();
    }

    /* 记录当前的PS服务所在的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    /* 通知外部模块当前的PS服务所在的模式 */
    TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_EHRPD);

    TAF_APS_SET_CDATA_MTU(pstPdnActInd->usMtu);

    TAF_APS_SndCgmtuValueChangeInd(pstPdnActInd->usMtu);

    /* 主状态迁移至TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    TAF_APS_IpfConfigUlFilter(ucPdpId);


    /* 不需要获取Ipv4 DNS */
    if (((VOS_TRUE == pstPdnActInd->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE == pstPdnActInd->stIpv4Dns.bitOpIpv4SecDNS))
      && (EHSM_APS_PDN_TYPE_IPV4   == pstPdnActInd->stPdnAddr.enPdnType))
    {

        return VOS_TRUE;
    }
    else if (((VOS_TRUE == pstPdnActInd->stIpv6Dns.bitOpIpv6PrimDNS) || (VOS_TRUE == pstPdnActInd->stIpv6Dns.bitOpIpv6SecDNS))
            && (EHSM_APS_PDN_TYPE_IPV6 == pstPdnActInd->stPdnAddr.enPdnType))
    {
        TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

        pstPdpIpv6Dns = (MN_APS_PDP_IPV6_DNS_STRU *)&pstPdnActInd->stIpv6Dns;

        TAF_APS_UpdateCdataIpv6Dns(pstPdpEntity, pstPdpIpv6Dns);

        pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_TRUE;

        return VOS_TRUE;
    }
    else if (((VOS_TRUE == pstPdnActInd->stIpv6Dns.bitOpIpv6PrimDNS) || (VOS_TRUE == pstPdnActInd->stIpv6Dns.bitOpIpv6SecDNS))
           && ((VOS_TRUE == pstPdnActInd->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE == pstPdnActInd->stIpv4Dns.bitOpIpv4SecDNS))
           && (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActInd->stPdnAddr.enPdnType))
    {
        TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

        pstPdpIpv6Dns = (MN_APS_PDP_IPV6_DNS_STRU *)&pstPdnActInd->stIpv6Dns;

        TAF_APS_UpdateCdataIpv6Dns(pstPdpEntity, pstPdpIpv6Dns);

        pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_TRUE;

        return VOS_TRUE;
    }
    else
    {
        /* 需要获取Ipv4 DNS */
        if (((EHSM_APS_PDN_TYPE_IPV4   == pstPdnActInd->stPdnAddr.enPdnType) || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActInd->stPdnAddr.enPdnType))
         && (((VOS_TRUE != pstPdnActInd->stIpv4Dns.bitOpIpv4PrimDNS) && (VOS_TRUE != pstPdnActInd->stIpv4Dns.bitOpIpv4SecDNS))))
        {
            TAF_APS_SndDhcpDnsIpv4Req(ucPdpId);
            pstPdpEntity->ucNeedGetDnsFlg = VOS_TRUE;
        }

        /* 需要获取Ipv6 DNS，Ipv4,Ipv4v6类型 */
        if (((EHSM_APS_PDN_TYPE_IPV6   == pstPdnActInd->stPdnAddr.enPdnType) || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActInd->stPdnAddr.enPdnType))
         && ((VOS_TRUE != pstPdnActInd->stIpv6Dns.bitOpIpv6PrimDNS) && (VOS_TRUE != pstPdnActInd->stIpv6Dns.bitOpIpv6SecDNS)))
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            TAF_APS_SndDhcpDnsIpv6Req(ucPdpId);
            pstPdpEntity->ucNeedGetDnsFlg = VOS_TRUE;
        }
    }

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterEnd1xService_Dormant
 功能描述  : DORMANT主状态下收到ID_MSG_TAF_PS_INTER_END_1X_SERVICE_IN_DORMANT_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月04日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterEnd1xService_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* 初始化, 获取PDP ID */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* 如果Dormant Timer在运行或者PPP状态为Inactive, 不需要再建链，本地去激活 */
    if ((TAF_APS_TIMER_STATUS_RUNING      == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
     || (TAF_APS_CDATA_PPP_STATE_INACTIVE == enPppState))
    {
        /* 停止Dormant 定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

        /* 上报去激活的事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* 本地去激活 */
        TAF_APS_LocalReleaseProc(ucPdpId);

        /* 通知外部模块PS模式切换 */
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

        return VOS_TRUE;
    }

    /*-------------------------------------------------------
       DORMANT状态下，需要先重新建立链接，然后再断开。

       加载TAF_APS_FSM_CDATA_ESTING状态机
       加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}



#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

