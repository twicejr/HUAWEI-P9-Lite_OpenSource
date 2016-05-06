
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmMsActivating.c
  版 本 号   : 初稿
  作    者   : S62952
  生成日期   : 2011年12月14日
  最近修改   :
  功能描述   : MsActivating状态机处理函数
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月14日
    作    者   : S62952
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
#include "TafApsTimerMgmt.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsFsmMsActivating.h"
#include "TafApsFsmMsActivatingTbl.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "TafApsFsmMsModifyingTbl.h"
#include "TafApsProcIpFilter.h"
#include "TafApsSndSm.h"
#include "TafApsSndRabm.h"
#include "TafApsSndInternalMsg.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#include "MnApsMultiMode.h"
#include "ApsL4aInterface.h"
#include "TafApsSndL4a.h"
#include "TafApsSndEsm.h"
#endif
#include "TafApsComFunc.h"
#include "ApsNdInterface.h"
#include "TafApsSndNd.h"
#include "TafSdcCtx.h"
#include "TafAppMma.h"

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
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MSACTIVATING_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_Init
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_INIT子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
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

  2.日    期   : 2012年5月3日
    作    者   : A00165503
    修改内容   : DTS2012042604902: GCF 8.2.2.35 用例失败

  3.日    期   : 2012年12月22日
    作    者   : z60575
    修改内容   : DTS2012121900427: 记录PDP类型

  4.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: PS域呼叫建立流程优化

  5.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 增加NO RF丢网场景时, 触发搜网流程
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;
    TAF_PDP_TABLE_STRU                 *pstCidCtx;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
#endif

    /* 初始化, 获取PDP ID和当前接入技术 */
    pstAppMsg            = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType        = TAF_APS_GetCurrPdpEntityRatType();
    ucCid                = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    pstCidCtx            = TAF_APS_GetTafCidInfoAddr(ucCid);

    /* 检查PS域卡状态, 如果无效, 直接返回ERROR */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        /* 上报PDP操作结果 */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpCtxStateReq->stCtrl),
                                    TAF_PS_CAUSE_SIM_INVALID);

        /* 清除资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;
    }
    else
    {
        /* 如果CID对应的剩余定时器时长为0, 需要上报响应事件 */
        if (0 == TAF_APS_GetCallRemainTmrLen(ucCid))
        {
            TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpCtxStateReq->stCtrl),
                                         TAF_PS_CAUSE_SUCCESS);
        }
    }

#if (FEATURE_ON == FEATURE_DSDS)
    /* area lost no RF场景, 触发搜网*/
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        stSrvAcqRatList.ucRatNum      = 1;
        stSrvAcqRatList.aenRatType[0] = TAF_MMA_SRV_ACQ_RAT_TYPE_GUL;

        TAF_MMA_SrvAcqReq(TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, &stSrvAcqRatList);
    }
#endif


    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    if (VOS_TRUE == pstCidCtx->ucPriCidFlag)
    {
        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(pstCidCtx->ucPriCid));
    }
    else
    {
        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(ucCid));
    }

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_GuMode();
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_LteMode();
            break;
#endif

        case TAF_APS_RAT_TYPE_NULL:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);

            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_Init: Wrong RAT type!");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_Init
 功能描述  : ACTIVATEING主状态下收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
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

  2.日    期   : 2012年5月3日
    作    者   : A00165503
    修改内容   : DTS2012042604902: GCF 8.2.2.35 用例失败

  3.日    期   : 2012年12月22日
    作    者   : z60575
    修改内容   : DTS2012121900427: 记录PDP类型

  4.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: PS域呼叫建立流程优化

  5.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 增加NO RF丢网场景时, 触发搜网流程
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
#endif

    /* 初始化, 获取PDP ID和当前接入技术 */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType     = TAF_APS_GetCurrPdpEntityRatType();
    ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* 检查PS域卡状态, 如果无效, 直接返回ERROR */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        /* 上报PDP操作结果 */
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                 TAF_PS_CAUSE_SIM_INVALID);

        /* 清除资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;
    }
    else
    {
        /* 如果CID对应的剩余定时器时长为0, 需要上报响应事件 */
        if (0 == TAF_APS_GetCallRemainTmrLen(ucCid))
        {
            TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                      TAF_PS_CAUSE_SUCCESS);
        }
    }

#if (FEATURE_ON == FEATURE_DSDS)
    /* area lost no RF场景, 触发搜网*/
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        stSrvAcqRatList.ucRatNum      = 1;
        stSrvAcqRatList.aenRatType[0] = TAF_MMA_SRV_ACQ_RAT_TYPE_GUL;

        TAF_MMA_SrvAcqReq(TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, &stSrvAcqRatList);
    }
#endif

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType,pstMsg);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(ucCid));

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_GuMode();
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_LteMode();
            break;
#endif

        case TAF_APS_RAT_TYPE_NULL:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);

            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_Init: Wrong RAT type!");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsActivating_Init
 功能描述  : ACTIVATEING主状态下收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
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

  2.日    期   : 2012年8月2日
    作    者   : A00165503
    修改内容   : DTS2012080200981: APS在挂起状态下收到IPv4v6类型拨号请求,
                 在解挂前又收到断开拨号请求, 上报的断开拨号响应事件中承载类
                 型填写错误, 导致再次拨号失败

  3.日    期   : 2012年12月22日
    作    者   : z60575
    修改内容   : DTS2012121900427: 记录PDP类型

  4.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: PS域呼叫建立流程优化

  5.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 增加NO RF丢网场景时, 触发搜网流程

  6.日    期   : 2015年3月24日
    作    者   : A00165503
    修改内容   : DTS2015032403636: PDN连接建立过程中, 断开拨号连接, 上报的拨
                 号类型错误, 导致AT对应类型的拨号连接状态异常. 后续拨号失败
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32                          ucT3402State;
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
#endif

    /* 初始化, 获取PDP ID和当前接入技术 */
    pstAppMsg      = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType  = TAF_APS_GetCurrPdpEntityRatType();
    ucCid          = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* 检查PS域卡状态, 如果无效, 直接返回ERROR */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        /* 上报PDP操作结果 */
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                              pstCallOrigReq->stDialParaInfo.ucCid,
                              TAF_PS_CAUSE_SIM_INVALID);

        /* 清除资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;
    }
    else
    {
        /* 如果CID对应的剩余定时器时长为0, 需要上报响应事件 */
        if (0 == TAF_APS_GetCallRemainTmrLen(ucCid))
        {
            TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                                   pstCallOrigReq->stDialParaInfo.ucCid,
                                   TAF_PS_CAUSE_SUCCESS);
        }
    }

#if (FEATURE_ON == FEATURE_DSDS)
    /* area lost no RF场景, 触发搜网*/
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        stSrvAcqRatList.ucRatNum      = 1;
        stSrvAcqRatList.aenRatType[0] = TAF_MMA_SRV_ACQ_RAT_TYPE_GUL;

        TAF_MMA_SrvAcqReq(TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, &stSrvAcqRatList);
    }
#endif

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                 pstCallOrigReq->stDialParaInfo.ucCid,
                                 pstCallOrigReq->stDialParaInfo.enPdpType);

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_RcvAtPsCallOrigReq_MsActivating_GuMode();
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            TAF_APS_SetPdpEntAddrType(ucPdpId, pstCallOrigReq->stDialParaInfo.enPdpType);
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_RcvAtPsCallOrigReq_MsActivating_LteMode();
            break;
#endif

        case TAF_APS_RAT_TYPE_NULL:
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
            if (VOS_TRUE == TAF_SDC_IsConfigCLInterWorkCOutside())
            {
                ucT3402State   = TAF_APS_IsT3402Running();

                if ((VOS_FALSE == TAF_APS_IsAnyBearerExist())
                 && (VOS_TRUE  == ucT3402State))
                {
                    /* 停止激活流程定时器 */
                    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                                      ucPdpId);

                    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_GMM_DETACH_NOT_REATTACH);

                    /* 释放APS资源 */
                    Aps_ReleaseApsResource(ucPdpId);

                    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
                    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
                    TAF_APS_QuitCurrSubFsm();
                    return VOS_TRUE;
                }
            }
#endif
            TAF_APS_SetPdpEntAddrType(ucPdpId, pstCallOrigReq->stDialParaInfo.enPdpType);

            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_ACTIVATING);
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);

            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvAtPsCallOrigReq_MsActivating_Init: Wrong RAT type!");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_Suspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_MsActivating_Suspend子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2012年5月22日
    作    者   : A00165503
    修改内容   : DTS2012032005030: 丢网状态下, +CGACT命令发起的激活承载请求
                 在APS缓存的时间超过40s

  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg             = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();

    /* 正在激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* 上报PDP操作结果, ERROR */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* 上报PDP操作结果, NO_ERROR */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_SUCCESS);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_Suspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_MsActivating_Suspend子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsActivating_Suspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_MsActivating_Suspend子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg      = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsActivating_Suspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_MsActivating_Suspend子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2012年5月22日
    作    者   : A00165503
    修改内容   : DTS2012032005030: 丢网状态下, +CGACT命令发起的激活承载请求
                 在APS缓存的时间超过40s
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstPsCallEndReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstPsCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 上报PDP操作结果, NO_ERROR */
    TAF_APS_SndCallEndCnf(&(pstPsCallEndReq->stCtrl),
                         pstPsCallEndReq->ucCid,
                         TAF_PS_CAUSE_SUCCESS);

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsActivating_Suspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_MsActivating_Suspend子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在激活该APS实体, 修改该APS实体, 返回ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_Suspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2012年5月22日
    作    者   : A00165503
    修改内容   : DTS2012032005030: 丢网状态下, +CGACT命令发起的激活承载请求
                 在APS缓存的时间超过40s

  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

  4.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 修改入口消息
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg         = VOS_NULL_PTR;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
    VOS_UINT8                                               ucPdpId;

    /* 初始化, 获取消息内容 */
    pstEntryMsg            = TAF_APS_GetCurrSubFsmMsgAddr();
    pstServStaChangeInd    = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;
    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();

    /* 此时如果卡状态为无效，需要终止流程 */
    if (VOS_FALSE == pstServStaChangeInd->ulPsSimRegStatus)
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* 上报错误事件 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SIM_INVALID);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;
    }

    if ( (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
      || (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType))
    {
        switch (TAF_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
        {
            case ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ:
                TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_GuMode();
                break;

            case ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ:
                TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_GuMode();
                break;

            case ID_MSG_TAF_PS_CALL_ORIG_REQ:
                TAF_APS_RcvAtPsCallOrigReq_MsActivating_GuMode();
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_Suspend: Unknown message!");
                break;
        }
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        switch (TAF_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
        {
            case ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ:
                TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_LteMode();
                break;

            case ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ:
                TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_LteMode();
                break;

            case ID_MSG_TAF_PS_CALL_ORIG_REQ:
                TAF_APS_RcvAtPsCallOrigReq_MsActivating_LteMode();
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_Suspend: Unknown message!");
                break;
        }
    }
#endif
    else
    {
        TAF_NORMAL_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_Suspend: RAT type is NULL!");
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_Suspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND子状态下
             收到ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND消息的处理
 输入参数  : ulEventType --- 消息类型
             pstMsg      --- ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND消息
 输出参数  : 无
 返 回 值  : VOS_TRUE    --- 处理消息成功
             VOS_FALSE   --- 处理消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT32                          ulRemainTimeLen;
    VOS_UINT8                           ucPdpId;

    ulRemainTimeLen = 0;
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取定时器剩余时长 */
    TAF_APS_GetRemainTimerLen(TI_TAF_APS_MS_ACTIVATING, ucPdpId, &ulRemainTimeLen);

    /* 如果剩余时长非0, 停止当前流程, 重新处理当前的状态机入口消息 */
    if (0 != ulRemainTimeLen)
    {
        /* 记录剩余时长 */
        TAF_APS_SetCallRemainTmrLen(TAF_APS_GetPdpEntCurrCid(ucPdpId), ulRemainTimeLen);

        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 发送状态机入口消息至内部消息队列 */
        TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiMsActivatingExpired_MsActivating_Suspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND子状态下
             收到TI_TAF_APS_MS_ACTIVATING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月25日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq   = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    /* 正在去激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* 上报PDP激活错误事件 */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 向SM发送ABORT请求, 取消当前激活操作 */
        TAF_APS_SndSmPdpAbortReq(ucPdpId);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年05月02日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012050203426,PDP激活过程中进行PDP去激活，需要上报
                 PDP操作结果给AT.
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* Added by f00179208 for DTS2012050203426，2012-05-02 Begin */
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstPsCallEndReq;
    /* Added by f00179208 for DTS2012050203426，2012-05-02 End */

    /* 获取当前状态机的APS实体索引 */
    /* Added by f00179208 for DTS2012050203426，2012-05-02 Begin */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstPsCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);
    /* Added by f00179208 for DTS2012050203426，2012-05-02 End */

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* Added by f00179208 for DTS2012050203426，2012-05-02 Begin */
    /* 上报PDP操作结果, NO_ERROR */
    TAF_APS_SndCallEndCnf(&(pstPsCallEndReq->stCtrl),
                         pstPsCallEndReq->ucCid,
                         TAF_PS_CAUSE_SUCCESS);
    /* Added by f00179208 for DTS2012050203426，2012-05-02 End */

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 向SM发送ABORT请求, 取消当前激活操作 */
    TAF_APS_SndSmPdpAbortReq(ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在激活该APS实体, 修改该APS实体, 返回ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_PMC_SMREG_PDP_DEACTIV_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_PMC_SMREG_PDP_DEACTIV_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    /* ID_PMC_SMREG_PDP_DEACTIV_IND消息处理说明,在状态机中不需要对TEARDOWN
       再进行判断处理,APS在收到ID_PMC_SMREG_PDP_DEACTIV_IND消息适?先进行预处
       理,如果消息中带有TEARDOWN,预处理中找出都有哪些PDP待去激活,然后,将
       ID_PMC_SMREG_PDP_DEACTIV_IND分发到相应的实体状态中,所以,在状态机中不再
       对ID_PMC_SMREG_PDP_DEACTIV_IND中的TEARDOWN再作处理 */

    /* 初始化, 获取消息内容 */
    pstSmPdpDeactivateInd = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 本状态下收到ID_PMC_SMREG_PDP_DEACTIV_IND为异常消息,上报错误事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpActRej_MsActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_PMC_SMREG_PDP_ACT_REJ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_PMC_SMREG_PDP_ACT_REJ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpActRej_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_ACTIVATE_REJ_STRU        *pstSmPdpActivateRej;

    /* 初始化, 获取消息内容 */
    pstSmPdpActivateRej = (SMREG_PDP_ACTIVATE_REJ_STRU *)pstMsg;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 处理PDP去激活指示消息 ,上报给AT在Aps_PdpActRej内部实现 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmPdpActivateRej->enCause));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpActSecRej_MsActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_PMC_SMREG_PDP_ACT_SEC_REJ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_PMC_SMREG_PDP_ACT_SEC_REJ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpActSecRej_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_ACTIVATE_SEC_REJ_STRU    *pstSmSecPdpActivateRej;

    /* 初始化, 获取消息内容 */
    pstSmSecPdpActivateRej  = (SMREG_PDP_ACTIVATE_SEC_REJ_STRU *)pstMsg;
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 处理PDP去激活指示消息 ,上报给AT在Aps_PdpActRej内部实现 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmSecPdpActivateRej->enCause));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_PMC_SMREG_PDP_ACT_CNF消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_PMC_SMREG_PDP_ACT_CNF消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2011年12月26日
    作    者   : o00132663
    修改内容   : PS融合项目，增加启动流量统计调用
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理

  4.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

  5.日    期   : 2013年01月21日
    作    者   : A00165503
    修改内容   : DTS2013011803709: 激活ND Client增加接入技术判断, 防止在NULL
                 状态下激活ND Client导致RS包被丢弃
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    APS_ACTCNF_PARA_ST                  stParam;
    #if ((FEATURE_ON == FEATURE_LTE)||(FEATURE_ON == FEATURE_IPV6))
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    #endif
    SMREG_PDP_ACTIVATE_CNF_STRU        *pstSmPdpActivateCnf;


    PS_MEM_SET(&stParam, 0x00, sizeof(stParam));


    /* 初始化, 获取消息内容 */
    pstSmPdpActivateCnf = (SMREG_PDP_ACTIVATE_CNF_STRU *)pstMsg;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType       = TAF_APS_GetCurrPdpEntityRatType();
    #if ((FEATURE_ON == FEATURE_LTE)||(FEATURE_ON == FEATURE_IPV6))
    pstPdpEntity        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    #endif

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 检查输入的参数 */
    ulRet = Aps_PdpActCnfParaCheck(pstSmPdpActivateCnf, &stParam);
    if (APS_PARA_VALID != ulRet)
    {
        if (APS_PDPTYPE_INVALID == ulRet)
        {
            /* 上报激活失败 */
            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);

            /* 发送内部消息, 去激活PDP */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);
        }
        else
        {
            /* 上报激活失败 */
            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

            /* 发送内部消息, 去激活PDP */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
        }

        return VOS_TRUE;
    }

    /* 检查QOS是否满足MIN要求 */
    if (APS_PARA_VALID  == Aps_CheckQosSatisify(ucPdpId, &stParam.PdpQos))
    {
        /* 满足MINQOS */
        Aps_PdpActCnfQosSatisfy(ucPdpId, &stParam, pstSmPdpActivateCnf);

#if (FEATURE_ON == FEATURE_LTE)
        /* 同步PDP信息至ESM */
        MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_ACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
        /* 如果地址类型是IPv6, 需要同步给ND Client */
        if (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId))
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);
        }
#endif

        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_GSM:
                /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP */
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP);
                break;

            case TAF_APS_RAT_TYPE_WCDMA:
                /* 激活成功，启动流量统计 */
                TAF_APS_StartDsFlowStats(pstSmPdpActivateCnf->ucNsapi);

                /* 如果当前APS实体的PDP类型为IPv4, 需要配置IPF */
                if (TAF_APS_CheckPdpAddrTypeIpv4(ucPdpId))
                {
                    /* 配置IP过滤器 */
                    TAF_APS_IpfConfigUlFilter(ucPdpId);
                }

                /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
                TAF_APS_QuitCurrSubFsm();
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnf: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* 不满足MINQOS */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

        /* 发送内部消息, 去激活PDP */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_QOS_NOT_ACCEPTED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpActSecCnf_MsActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_PMC_SMREG_PDP_ACT_SEC_CNF消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_PMC_SMREG_PDP_ACT_SEC_CNF消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2012年6月19日
    作    者   : A00165503
    修改内容   : DTS2012061504908: GCF 45.2.5.1.2.2 FAIL

  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpActSecCnf_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    APS_ACTSECCNF_PARA_ST               stParam;
    SMREG_PDP_ACTIVATE_SEC_CNF_STRU    *pstSmSecPdpActivateCnf;

    /* 初始化, 获取消息内容 */
    pstSmSecPdpActivateCnf  = (SMREG_PDP_ACTIVATE_SEC_CNF_STRU *)pstMsg;
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType           = TAF_APS_GetCurrPdpEntityRatType();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 检查输入的参数 */
    ulRet = Aps_PdpActSecCnfParaCheck(pstSmSecPdpActivateCnf, &stParam);
    if (APS_PARA_VALID != ulRet)
    {
        /* 上报激活失败 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER );

        /* 发送内部消息, 去激活PDP */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);

        return VOS_TRUE;
    }

    /* 检查QOS是否满足MIN要求 */
    if (APS_PARA_VALID == Aps_CheckQosSatisify(ucPdpId, &stParam.PdpQos))
    {
        /* 满足MINQOS */
        Aps_PdpActSecCnfQosSatisfy(ucPdpId, &stParam, pstSmSecPdpActivateCnf);

#if (FEATURE_ON == FEATURE_LTE)
        /* 同步PDP信息至ESM */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId), SM_ESM_PDP_OPT_ACTIVATE);
#endif

        /* 根据当前模做状态迁移 */
        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_GSM:

                /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP */
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP);
                break;

            case TAF_APS_RAT_TYPE_WCDMA:

                /* 如果当前APS实体的PDP类型为IPv4, 需要配置IPF, 目前不支持Secondary PDP */

                /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
                TAF_APS_QuitCurrSubFsm();
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvSmPdpActSecCnf_MsActivating_WaitSmActivateCnf: Wrong RAT type!");
                break;
        }

    }
    else
    {
        /* 不满足MINQOS */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

        /* 发送内部消息, 去激活PDP */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_QOS_NOT_ACCEPTED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSmActivateCnf
 功能描述  : ACTIVATING主状态下收到ID_APS_APS_INTER_PDP_DEACTIVATE_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*---------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
       处理ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ消息
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月07日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalMsg;

    /* 初始化, 获取消息内容 */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstLocalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 本状态下收到ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND为异常消息,上报错误事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstLocalMsg->enCause));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 入口消息修改

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* 此时到L模应该是一条异常消息 */
    if (TAF_APS_RAT_TYPE_NULL != pstServStaChangeInd->enRatType)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnf: Wrong RAT Type!");

        return VOS_TRUE;
    }

    /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到TI_TAF_APS_MS_ACTIVATING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月25日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 释放SM资源 */
    TAF_APS_SndSmPdpAbortReq(ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq   = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    /* 正在去激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if ( TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState )
    {
        /* 上报PDP激活错误事件*/
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 向SM发送ABORT请求, 取消当前激活操作 */
        TAF_APS_SndSmPdpAbortReq(ucPdpId);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年05月02日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012050203426,PDP激活过程中进行PDP去激活，需要上报
                 PDP操作结果给AT.
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* Added by f00179208 for DTS2012050203426，2012-05-02 Begin */
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstPsCallEndReq;
    /* Added by f00179208 for DTS2012050203426，2012-05-02 End */

    /* 初始化, 获取消息内容 */
    /* Added by f00179208 for DTS2012050203426，2012-05-02 Begin */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstPsCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);
    /* Added by f00179208 for DTS2012050203426，2012-05-02 End */

    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* Added by f00179208 for DTS2012050203426，2012-05-02 Begin */
    /* 上报PDP操作结果, NO_ERROR */
    TAF_APS_SndCallEndCnf(&(pstPsCallEndReq->stCtrl),
                         pstPsCallEndReq->ucCid,
                         TAF_PS_CAUSE_SUCCESS);
    /* Added by f00179208 for DTS2012050203426，2012-05-02 End */

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 向SM发送ABORT请求, 取消当前激活操作 */
    TAF_APS_SndSmPdpAbortReq(ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在激活该APS实体, 修改该APS实体, 返回ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_PMC_SMREG_PDP_DEACTIV_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_PMC_SMREG_PDP_DEACTIV_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    pstSmPdpDeactivateInd = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* ID_PMC_SMREG_PDP_DEACTIV_IND消息处理说明,在状态机中不需要对TEARDOWN
       再进行判断处理,APS在收到ID_PMC_SMREG_PDP_DEACTIV_IND消息首先进行预处
       理,如果消息中带有TEARDOWN,预处理中找出都有哪些PDP待去激活,然后,将
       ID_PMC_SMREG_PDP_DEACTIV_IND分发到相应的实体状态中,所以,在状态机中不再
       对ID_PMC_SMREG_PDP_DEACTIV_IND中的TEARDOWN再作处理 */

   /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 本状态下收到ID_PMC_SMREG_PDP_DEACTIV_IND为异常消息,上报错误事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* 清除资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE*/
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月07日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalMsg;

    /* 初始化, 获取消息内容 */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstLocalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 本状态下收到ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND为异常消息,上报错误事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstLocalMsg->enCause));

    /* 清除资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE*/
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpActRej_MsActivating_WaitSmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_PMC_SMREG_PDP_ACT_REJ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_PMC_SMREG_PDP_ACT_REJ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月7日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpActRej_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_ACTIVATE_REJ_STRU        *pstSmPdpActivateRej;

    /* 初始化, 获取消息内容 */
    pstSmPdpActivateRej = (SMREG_PDP_ACTIVATE_REJ_STRU *)pstMsg;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 处理PDP去激活指示消息 ,上报给AT在Aps_PdpActRej内部实现 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmPdpActivateRej->enCause));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 入口消息修改

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                                               ucPdpId;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;
#endif
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd;

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd    = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;
#if (FEATURE_ON == FEATURE_LTE)
    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg            = TAF_APS_GetCurrSubFsmMsgAddr();
#endif

    if ( (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
      || (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType) )
    {
        /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF);
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        /* LTE模需要向GU模发送abort消息,再向L模发送PDP激活请求 */
        TAF_APS_SndSmPdpAbortReq(ucPdpId);

        switch (TAF_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
        {
            case ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ:
                TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_LteMode();
                break;

            case ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ:
                TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_LteMode();
                break;

            case ID_MSG_TAF_PS_CALL_ORIG_REQ:
                TAF_APS_RcvAtPsCallOrigReq_MsActivating_LteMode();
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnfSuspend: Unknown message!");
                break;
        }
    }
#endif
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSmActivateCnfSuspend: Wrong RAT type!");
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_WaitSmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND消息的处理
 输入参数  : ulEventType --- 消息类型
             pstMsg      --- ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND消息
 输出参数  : 无
 返 回 值  : VOS_TRUE    --- 处理消息成功
             VOS_FALSE   --- 处理消息失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT32                          ulRemainTimeLen;
    VOS_UINT8                           ucPdpId;

    ulRemainTimeLen = 0;
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取定时器剩余时长 */
    TAF_APS_GetRemainTimerLen(TI_TAF_APS_MS_ACTIVATING, ucPdpId, &ulRemainTimeLen);

    /* 如果剩余时长非0, 停止当前流程, 重新处理当前的状态机入口消息 */
    if (0 != ulRemainTimeLen)
    {
        /* 记录剩余时长 */
        TAF_APS_SetCallRemainTmrLen(TAF_APS_GetPdpEntCurrCid(ucPdpId), ulRemainTimeLen);

        /* 向GU模发送ABORT消息 */
        TAF_APS_SndSmPdpAbortReq(ucPdpId);

        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 发送状态机入口消息至内部消息队列 */
        TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND子状态下
             收到TI_TAF_APS_MS_ACTIVATING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月25日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 向SM发送ABORT请求 */
    TAF_APS_SndSmPdpAbortReq(ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_SMREG_PDP_ACTIVATE_CNF消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月30日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatTypeSuspend;
    APS_ACTCNF_PARA_ST                  stParam;
    #if ((FEATURE_ON == FEATURE_LTE)||(FEATURE_ON == FEATURE_IPV6))
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    #endif
    SMREG_PDP_ACTIVATE_CNF_STRU        *pstSmPdpActivateCnf;

    PS_MEM_SET(&stParam, 0x00, sizeof(stParam));

    /* 初始化, 获取消息内容 */
    pstSmPdpActivateCnf         = (SMREG_PDP_ACTIVATE_CNF_STRU *)pstMsg;
    ucPdpId                     = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatTypeSuspend        = TAF_APS_GET_RAT_TYPE_IN_SUSPEND();
    #if ((FEATURE_ON == FEATURE_LTE)||(FEATURE_ON == FEATURE_IPV6))
    pstPdpEntity        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    #endif

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 检查输入的参数 */
    ulRet = Aps_PdpActCnfParaCheck(pstSmPdpActivateCnf, &stParam);
    if (APS_PARA_VALID != ulRet)
    {
        if (APS_PDPTYPE_INVALID == ulRet)
        {
            /* 上报激活失败 */
            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);

            /* 发送内部消息, 去激活PDP */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);
        }
        else
        {
            /* 上报激活失败 */
            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

            /* 发送内部消息, 去激活PDP */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
        }

        return VOS_TRUE;
    }

    /* 检查QOS是否满足MIN要求 */
    if (APS_PARA_VALID  == Aps_CheckQosSatisify(ucPdpId, &stParam.PdpQos))
    {
        /* 满足MINQOS */
        Aps_PdpActCnfQosSatisfy(ucPdpId, &stParam, pstSmPdpActivateCnf);

#if (FEATURE_ON == FEATURE_LTE)
        /* 同步PDP信息至ESM */
        MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_ACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
        /* 如果地址类型是IPv6, 需要同步给ND Client */
        if (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId))
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);
        }
#endif

        switch (enCurrRatTypeSuspend)
        {
            case TAF_APS_RAT_TYPE_GSM:
                /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND */
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND);
                break;

            case TAF_APS_RAT_TYPE_WCDMA:
                /* 激活成功，启动流量统计 */
                TAF_APS_StartDsFlowStats(pstSmPdpActivateCnf->ucNsapi);

                /* 如果当前APS实体的PDP类型为IPv4, 需要配置IPF */
                if (TAF_APS_CheckPdpAddrTypeIpv4(ucPdpId))
                {
                    /* 配置IP过滤器 */
                    TAF_APS_IpfConfigUlFilter(ucPdpId);
                }

                /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
                TAF_APS_QuitCurrSubFsm();
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvSmPdpActCnf_MsActivating_WaitSmActivateCnf: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* 不满足MINQOS */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

        /* 发送内部消息, 去激活PDP */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_QOS_NOT_ACCEPTED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSmActivateCnfSuspend
 功能描述  : MsActivating_WaitSmActivateCnfSuspend状态下收到ID_APS_APS_INTER_PDP_DEACTIVATE_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月30日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*---------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
       处理ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ消息
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq               = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 正在去激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* 上报PDP激活错误事件*/
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /*---------------------------------------------------------
           加载TAF_APS_STA_MS_DEACTIVATING状态机
           加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
        ---------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;


    /* 初始化, 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /*---------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_CALL_END_REQ消息
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在去激活该APS实体, 修改该APS实体, 返回ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_PMC_SMREG_PDP_DEACTIV_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_PMC_SMREG_PDP_DEACTIV_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivInd_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstSmPdpDeactivateInd = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* ID_PMC_SMREG_PDP_DEACTIV_IND消息处理说明,在状态机中不需要对TEARDOWN
       再进行判断处理,APS在收到ID_PMC_SMREG_PDP_DEACTIV_IND消息进行预处理,
       如果消息中带有TEARDOWN,预处理中找出都有哪些PDP待去激活,然后,将
       ID_PMC_SMREG_PDP_DEACTIV_IND分发到相应的实体状态中,所以,在状态机中不再
       对ID_PMC_SMREG_PDP_DEACTIV_IND中的TEARDOWN再作处理 */

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

#if (FEATURE_ON == FEATURE_LTE)
    /* 同步PDP信息至ESM */
    MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));


    /* 释放SNDCP资源 */
    Aps_ReleaseSndcpResource(ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到APS_SN_ACT_RSP_MSG_TYPE消息的处理
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

  2.日    期   : 2011年12月27日
    作    者   : o00132663
    修改内容   : PS融合项目，增加流量统计调用
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    APS_SNDCP_ACTIVATE_RSP_ST          *pstSnActivateRsp;

    /* 初始化, 获取消息内容 */
    ulResult                            = VOS_OK;
    pstSnActivateRsp                    = &((APS_SNDCP_ACTIVATE_RSP_MSG*)pstMsg)->ApsSnActRsp;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 检查消息参数 */
    ulResult = Aps_SnMsgModSnActRspParaCheck(pstSnActivateRsp);
    if (APS_PARA_VALID != ulResult)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRsp: Check para failed!");

        /* 上报激活失败 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* 发送内部消息, 触发PDP去激活流程 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /* 收到SN_ACT_RSP后修改APS实体参数, 包括XID参数, TRANSMODE */
    Aps_SnActRspChngEntity(pstSnActivateRsp, ucPdpId);

    /* 设置RABM的传输模式 */
    TAF_APS_SndRabmSetTransModeMsg(pstSnActivateRsp->ucNsapi,
                                   pstPdpEntity->GprsPara.TransMode);

    /* 如果当前APS实体的PDP类型为IPv4, 需要配置IPF, 目前只支持Primary PDP */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv4(ucPdpId)) )
    {
        /* 配置IP过滤器 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);
    }

    /* 激活成功，启动流量统计 */
    TAF_APS_StartDsFlowStats(pstSnActivateRsp->ucNsapi);

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF事件 */
    TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSndcpStatusReqMsgType_MsActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND子状态下
             收到APS_SN_STATUS_REQ_MSG_TYPE消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : APS_SN_STATUS_REQ_MSG_TYPE消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq;

    pstSnStatusReq                      = &((APS_SNDCP_STATUS_REQ_MSG*)pstMsg)->ApsSnStatusReq;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    ulRet = TAF_APS_ValidatePdpForSnStatusReq(ucPdpId, pstSnStatusReq);
    if (VOS_TRUE == ulRet)
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /*上报激活失败并清资源*/
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* 发送内部消息, 触发PDP去激活流程 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSndcpActivateRsp
 功能描述  : ACTIVATING主状态下收到ID_APS_APS_INTER_PDP_DEACTIVATE_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*---------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
       处理ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ消息
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
 修改历史      :
  1.日    期   : 2012年06月07日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                               ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;

    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalMsg;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstLocalMsg  = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

#if (FEATURE_ON == FEATURE_LTE)
    /* 同步PDP信息至ESM */
    MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstLocalMsg->enCause));

    /* 释放SNDCP资源 */
    Aps_ReleaseSndcpResource(ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 入口消息修改
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* 此时到NULL模应该是一条异常消息 */
    if (TAF_APS_RAT_TYPE_NULL != pstServStaChangeInd->enRatType)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRsp: Wrong RAT Type:", pstServStaChangeInd->enRatType);

        return VOS_TRUE;
    }

    /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到TI_TAF_APS_MS_ACTIVATING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月25日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, SM_TAF_CAUSE_SM_MAX_TIME_OUT);

    /* 发送内部消息, 触发PDP去激活流程 */
    TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSndcpActivateRspSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq               = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 正在激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* 上报PDP激活错误事件*/
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /*---------------------------------------------------------
           加载TAF_APS_STA_MS_DEACTIVATING状态机
           加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
        ---------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSndcpActivateRspSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSndcpActivateRspSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSndcpActivateRspSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /*---------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_CALL_END_REQ消息
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSndcpActivateRspSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在去激活该APS实体, 修改该APS实体, 返回ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpDeactivateInd_MsActivating_WaitSndcpActivateRspSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND子状态下
             收到ID_PMC_SMREG_PDP_DEACTIV_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : D_PMC_SMREG_PDP_DEACTIV_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    /* ID_PMC_SMREG_PDP_DEACTIV_IND消息处理说明,在状态机中不需要对TEARDOWN
       再进行判断处理,APS在收到ID_PMC_SMREG_PDP_DEACTIV_IND消息适?先进行预处
       理,如果消息中带有TEARDOWN,预处理中找出都有哪些PDP待去激活,然后,将
       ID_PMC_SMREG_PDP_DEACTIV_IND分发到相应的实体状态中,所以,在状态机中不再
       对ID_PMC_SMREG_PDP_DEACTIV_IND中的TEARDOWN再作处理 */

    /* 初始化, 获取消息内容 */
    pstSmPdpDeactivateInd = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* 获取当前状态机的APS索引 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

#if (FEATURE_ON == FEATURE_LTE)
    /* 同步PDP信息至ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId), SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* 释放SNDCP资源 */
    Aps_ReleaseSndcpResource(ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSndcpStatusReqMsgType_MsActivating_WaitSndcpActivateRspSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF子状态下
             收到APS_SN_STATUS_REQ_MSG_TYPE消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : APS_SN_STATUS_REQ_MSG_TYPE消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpStatusReqMsgType_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq;

    /* 获取消息内容 */
    pstSnStatusReq = &((APS_SNDCP_STATUS_REQ_MSG*)pstMsg)->ApsSnStatusReq;

    /* 获取当前状态机的APS索引 */
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();

    /* 检查SNDCP指定的SAPI与APS实体的SAPI是否匹配 */
    ulRet = TAF_APS_ValidatePdpForSnStatusReq(ucPdpId, pstSnStatusReq);
    if (VOS_TRUE == ulRet)
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* 发送内部消息, 触发PDP去激活流程 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSndcpActivateRspSuspend
 功能描述  : ACTIVATING主状态下收到ID_APS_APS_INTER_PDP_DEACTIVATE_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*---------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
       处理ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ消息
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSndcpActivateRspSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND子状态下
             收到ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月07日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalMsg;

    /* 获取当前状态机的APS索引 */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstLocalMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstLocalMsg->enCause));

#if (FEATURE_ON == FEATURE_LTE)
    /* 同步PDP信息至ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId), SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* 释放SNDCP资源 */
    Aps_ReleaseSndcpResource(ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRspSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 入口消息修改
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucPdpId;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd;
    APS_PDP_CONTEXT_ENTITY_ST                              *pstPdpEntity;

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd     = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity            = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    switch (pstServStaChangeInd->enRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
            /* GU模下 ,不需要处理,继续等SM的回复,状态回到
               TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP);
            break;

        case TAF_APS_RAT_TYPE_WCDMA:
#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
#endif
            /* 停止激活流程定时器 */
            TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                              ucPdpId);

            /* 释放SNDCP资源 */
            Aps_ReleaseSndcpResource(ucPdpId);

            /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF事件 */
            TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

            /* 激活成功，启动流量统计 */
            TAF_APS_StartDsFlowStats(pstPdpEntity->ucNsapi);

            /* 主状态迁移至TAF_APS_STA_ACTIVE_SUSPEND, 退出子状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();
            break;

        default:
            TAF_WARNING_LOG1(WUEPS_PID_TAF,
                "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitSndcpActivateRspSuspend: Wrong RAT Type:", pstServStaChangeInd->enRatType);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSndcpActivateRspSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到TI_TAF_APS_MS_ACTIVATING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月25日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 发送内部消息, 触发PDP去激活流程 */
    TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_MAX_TIME_OUT);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRspSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到sndcp的激活rsp消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月30日
    作    者   : m00217266
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    APS_SNDCP_ACTIVATE_RSP_ST          *pstSnActivateRsp;

    /* 初始化, 获取消息内容 */
    ulResult                            = VOS_OK;
    pstSnActivateRsp                    = &((APS_SNDCP_ACTIVATE_RSP_MSG*)pstMsg)->ApsSnActRsp;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 检查消息参数 */
    ulResult = Aps_SnMsgModSnActRspParaCheck(pstSnActivateRsp);
    if (APS_PARA_VALID != ulResult)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSndcpActivateRsp_MsActivating_WaitSndcpActivateRsp: Check para failed!");

        /* 上报激活失败 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* 发送内部消息, 触发PDP去激活流程 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /* 收到SN_ACT_RSP后修改APS实体参数, 包括XID参数, TRANSMODE */
    Aps_SnActRspChngEntity(pstSnActivateRsp, ucPdpId);

    /* 设置RABM的传输模式 */
    TAF_APS_SndRabmSetTransModeMsg(pstSnActivateRsp->ucNsapi,
                                   pstPdpEntity->GprsPara.TransMode);

    /* 如果当前APS实体的PDP类型为IPv4, 需要配置IPF, 目前只支持Primary PDP */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv4(ucPdpId)) )
    {
        /* 配置IP过滤器 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);
    }

    /* 激活成功，启动流量统计 */
    TAF_APS_StartDsFlowStats(pstSnActivateRsp->ucNsapi);

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF事件 */
    TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitEsmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq               = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 正在去激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* 上报PDP激活错误事件*/
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 向SM发送ABORT请求, 取消当前激活操作 */
        TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitEsmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在去激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitEsmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在去激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitEsmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /*---------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_CALL_END_REQ消息
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitEsmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在去激活该APS实体, 修改该APS实体, 返回ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmPdpSetupCnf_MsActivate_WaitEsmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF子状态下
             收到ID_APP_ESM_PDP_SETUP_CNF消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_APP_ESM_PDP_SETUP_CNF消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpSetupCnf_MsActivate_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_SETUP_CNF_STRU         *pstEsmPdpSetupCnf;

    /* 初始化, 获取消息内容 */
    pstEsmPdpSetupCnf = (APP_ESM_PDP_SETUP_CNF_STRU *)pstMsg;

    /* 当结果值不为SUCC且bitOpRabId不为TRUE时，发送ACTIVATE_REJ，其他场景发送ACTIVATE_CNF */
    if((APP_SUCCESS != pstEsmPdpSetupCnf->ulRslt) && (0 == pstEsmPdpSetupCnf->bitOpRabId))
    {
        return TAF_APS_RcvEsmPdpActivateRej_MsActivate_WaitEsmActivateCnf(ulEventType, pstEsmPdpSetupCnf);     /*激活失败，上报REJ*/
    }
    else
    {
        return TAF_APS_RcvEsmPdpActivateCnf_MsActivate_WaitEsmActivateCnf(ulEventType, pstEsmPdpSetupCnf);     /*激活成功，上报CNF*/
    }
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmNdisconnCnf_MsActivate_WaitEsmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF子状态下
             收到ID_APP_ESM_NDISCONN_CNF消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_APP_ESM_NDISCONN_CNF消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmNdisconnCnf_MsActivate_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_NDISCONN_CNF_STRU          *pstEsmNdisconnCnf;
    APP_ESM_PDP_SETUP_CNF_STRU          stEsmPdpSetupCnf;

    /* 初始化, 获取消息内容 */
    pstEsmNdisconnCnf = (APP_ESM_NDISCONN_CNF_STRU *)pstMsg;
    PS_MEM_SET(&stEsmPdpSetupCnf, 0x00, sizeof(APP_ESM_PDP_SETUP_CNF_STRU));

    stEsmPdpSetupCnf.ulCid               = pstEsmNdisconnCnf->ulCid;
    stEsmPdpSetupCnf.ulRslt              = pstEsmNdisconnCnf->ulRslt;
    stEsmPdpSetupCnf.enBearerState       = pstEsmNdisconnCnf->enBearerState;
    stEsmPdpSetupCnf.enBearerType        = pstEsmNdisconnCnf->enBearerType;
    stEsmPdpSetupCnf.ulRabId             = pstEsmNdisconnCnf->ulRabId;
    stEsmPdpSetupCnf.bitOpBearerState    = pstEsmNdisconnCnf->bitOpBearerState;
    stEsmPdpSetupCnf.bitOpBearerType     = pstEsmNdisconnCnf->bitOpBearerType;
    stEsmPdpSetupCnf.bitOpPdnAddr        = pstEsmNdisconnCnf->bitOpPdnAddr;
    stEsmPdpSetupCnf.bitOpRabId          = pstEsmNdisconnCnf->bitOpRabId;
    stEsmPdpSetupCnf.bitOpApn            = pstEsmNdisconnCnf->bitOpApn;
    stEsmPdpSetupCnf.bitOpSdfQos         = pstEsmNdisconnCnf->bitOpSdfQos;
    stEsmPdpSetupCnf.bitOpDnsPrim        = pstEsmNdisconnCnf->bitOpDnsPrim;
    stEsmPdpSetupCnf.bitOpDnsSec         = pstEsmNdisconnCnf->bitOpDnsSec;
    stEsmPdpSetupCnf.bitOpPCscfPrim      = pstEsmNdisconnCnf->bitOpPCscfPrim;
    stEsmPdpSetupCnf.bitOpPCscfSec       = pstEsmNdisconnCnf->bitOpPCscfSec;
    stEsmPdpSetupCnf.bitOpGateWayAddrInfo= pstEsmNdisconnCnf->bitOpGateWayAddrInfo;

    PS_MEM_CPY(&stEsmPdpSetupCnf.stPDNAddrInfo        ,&pstEsmNdisconnCnf->stPDNAddrInfo,      sizeof(APP_ESM_IP_ADDR_STRU));
    PS_MEM_CPY(&stEsmPdpSetupCnf.stSubnetMask         ,&pstEsmNdisconnCnf->stSubnetMask,       sizeof(APP_ESM_IP_ADDR_STRU));
    PS_MEM_CPY(&stEsmPdpSetupCnf.stGateWayAddrInfo    ,&pstEsmNdisconnCnf->stGateWayAddrInfo,  sizeof(APP_ESM_IP_ADDR_STRU));
    PS_MEM_CPY(&stEsmPdpSetupCnf.stDnsPrimAddrInfo    ,&pstEsmNdisconnCnf->stDnsPrimAddrInfo,  sizeof(APP_ESM_IP_ADDR_STRU));
    PS_MEM_CPY(&stEsmPdpSetupCnf.stDnsSecAddrInfo     ,&pstEsmNdisconnCnf->stDnsSecAddrInfo,   sizeof(APP_ESM_IP_ADDR_STRU));
    PS_MEM_CPY(&stEsmPdpSetupCnf.stPCscfPrimAddrInfo  ,&pstEsmNdisconnCnf->stPCscfPrimAddrInfo,sizeof(APP_ESM_IP_ADDR_STRU));
    PS_MEM_CPY(&stEsmPdpSetupCnf.stPCscfSecAddrInfo   ,&pstEsmNdisconnCnf->stPCscfSecAddrInfo, sizeof(APP_ESM_IP_ADDR_STRU));

    PS_MEM_CPY(&stEsmPdpSetupCnf.stApnInfo            ,&pstEsmNdisconnCnf->stApnInfo,          sizeof(APP_ESM_APN_INFO_STRU));
    PS_MEM_CPY(&stEsmPdpSetupCnf.stSdfQosInfo         ,&pstEsmNdisconnCnf->stSdfQosInfo,       sizeof(APP_ESM_EPS_QOS_INFO_STRU));

    /* 当结果值不为SUCC且bitOpRabId不为TRUE时，发送ACTIVATE_REJ，其他场景发送ACTIVATE_CNF */
    if((APP_SUCCESS != pstEsmNdisconnCnf->ulRslt) && (0 == pstEsmNdisconnCnf->bitOpRabId))
    {
        return TAF_APS_RcvEsmPdpActivateRej_MsActivate_WaitEsmActivateCnf(ulEventType, &stEsmPdpSetupCnf);     /*激活失败，上报REJ*/
    }
    else
    {
        return TAF_APS_RcvEsmPdpActivateCnf_MsActivate_WaitEsmActivateCnf(ulEventType, &stEsmPdpSetupCnf);     /*激活成功，上报CNF*/
    }
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmPdpActivateCnf_MsActivate_WaitEsmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF子状态下
             收到ID_APP_ESM_PDP_SETUP_CNF消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_APP_ESM_PDP_SETUP_CNF消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数

  2.日    期   : 2015年01月28日
    作    者   : w00316404
    修改内容   : send pdp activate inf to ND Client
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpActivateCnf_MsActivate_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    APP_ESM_PDP_SETUP_CNF_STRU         *pstEsmPdpSetupCnf
)
{
    VOS_UINT8                           ucPdpId;
#if (FEATURE_ON == FEATURE_IPV6)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif
    VOS_UINT32                          ulRet;

    /* 初始化, 获取消息内容 */
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();
#if (FEATURE_ON == FEATURE_IPV6)
    pstPdpEntity         = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
#endif

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

#endif

    /* 缺省承载激活成功后, 需要检查PDP类型是否匹配 */
    if (VOS_FALSE == pstEsmPdpSetupCnf->bitOpLinkCid)
    {
        ulRet = TAF_APS_ValidatePdpType(TAF_APS_GetPdpEntDialPdpType(ucPdpId, (VOS_UINT8)pstEsmPdpSetupCnf->ulCid),
                                        pstEsmPdpSetupCnf->stPDNAddrInfo.ucIpType);
        if (ulRet != VOS_OK)
        {
            /* 上报激活失败 */
            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);

            /* 发送内部消息, 去激活PDP */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER);

            return VOS_TRUE;
        }
    }

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果地址类型是IPv6, 需要同步给ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                               pstPdpEntity->PdpAddr.aucIpV6Addr);
    }

    /* 更新错误码 */
    if ( APP_SUCCESS != pstEsmPdpSetupCnf->ulRslt )
    {
        pstPdpEntity->bitOpCause    = VOS_TRUE;
        pstPdpEntity->enCause       = TAF_APS_MapEsmCause(pstEsmPdpSetupCnf->ulRslt);
    }
#endif

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF事件 */
    TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /*------------------------------------------------------------------
       如果地址类型是IPv6, 需要同步给ND Client, 目前架构需要在收到ESM
       的EPS承载同步消息后通知ND Client
    ------------------------------------------------------------------*/

    /* 激活成功，启动流量统计 */
    TAF_APS_StartDsFlowStats((VOS_UINT8)pstEsmPdpSetupCnf->ulRabId);

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmPdpActivateRej_MsActivate_WaitEsmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF子状态下
             收到ID_APP_ESM_PDP_SETUP_CNF消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_APP_ESM_PDP_SETUP_CNF消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpActivateRej_MsActivate_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    APP_ESM_PDP_SETUP_CNF_STRU         *pstEsmPdpActivateRej
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapEsmCause(pstEsmPdpActivateRej->ulRslt));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitEsmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if (TAF_APS_RAT_TYPE_NULL != pstServStaChangeInd->enRatType)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitEsmActivateCnf: Wrong RAT type:", pstServStaChangeInd->enRatType);
        return VOS_TRUE;
    }

    /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmSmEpsBearerInfoInd_MsActivating_WaitEsmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF主状态下收到ID_ESM_SM_EPS_BEARER_INFO_IND消息的处理
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
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsActivating_WaitEsmActivateCnf(
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
    if (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptActivate(pstPdpEntity, pstBearerInfo);

#if (FEATURE_ON == FEATURE_IPV6)
        /* 如果地址类型是IPv6, 需要同步给ND Client */
        if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
          && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);
        }
#endif
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive: Wrong option.");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitEsmActivateCnf
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF子状态下
             收到TI_TAF_APS_MS_ACTIVATING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月25日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 向SM发送ABORT请求, 取消当前激活操作 */
    TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitEsmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq               = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 正在去激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* 上报PDP激活错误事件*/
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitEsmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在去激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitEsmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在去激活该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitEsmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年05月02日
    作    者   : f00179208
    修改内容   : 问题单号:DTS2012050203426,PDP激活过程中进行PDP去激活，需要上报
                 PDP操作结果给AT.
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* Added by f00179208 for DTS2012050203426，2012-05-02 Begin */
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstPsCallEndReq;
    /* Added by f00179208 for DTS2012050203426，2012-05-02 End */

    /* 初始化, 获取消息内容 */
    /* Added by f00179208 for DTS2012050203426，2012-05-02 Begin */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstPsCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);
    /* Added by f00179208 for DTS2012050203426，2012-05-02 End */

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);


    /* Added by f00179208 for DTS2012050203426，2012-05-02 Begin */
    /* 上报PDP操作结果, NO_ERROR */
    TAF_APS_SndCallEndCnf(&(pstPsCallEndReq->stCtrl),
                         pstPsCallEndReq->ucCid,
                         TAF_PS_CAUSE_SUCCESS);
    /* Added by f00179208 for DTS2012050203426，2012-05-02 End */

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitEsmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在去激活该APS实体, 修改该APS实体, 返回ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmPdpSetupCnfRej_MsActivate_WaitEsmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_APP_ESM_PDP_SETUP_CNF消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_APP_ESM_PDP_SETUP_CNF消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpSetupCnfRej_MsActivate_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APP_ESM_PDP_SETUP_CNF_STRU         *pstEsmPdpActivateRej;

    /* 初始化, 获取消息内容 */
    pstEsmPdpActivateRej                = (APP_ESM_PDP_SETUP_CNF_STRU*)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    if((APP_SUCCESS == pstEsmPdpActivateRej->ulRslt) || (0 != pstEsmPdpActivateRej->bitOpRabId))
    {
        return VOS_TRUE;
    }

    /* 如果错误码不是异系统, 则该激活流程终止 */
    if (APP_ERR_SM_SUSPENDED != pstEsmPdpActivateRej->ulRslt)
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapEsmCause(pstEsmPdpActivateRej->ulRslt));

        /* 释放资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmNdisconnCnfRej_MsActivate_WaitEsmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND子状态下
             收到ID_APP_ESM_NDISCONN_CNF消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_APP_ESM_NDISCONN_CNF消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmNdisconnCnfRej_MsActivate_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APP_ESM_NDISCONN_CNF_STRU          *pstEsmNdisconnCnfRej;

    /* 初始化, 获取消息内容 */
    pstEsmNdisconnCnfRej                = (APP_ESM_NDISCONN_CNF_STRU*)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    if((APP_SUCCESS == pstEsmNdisconnCnfRej->ulRslt) || (0 != pstEsmNdisconnCnfRej->bitOpRabId))
    {
        return VOS_TRUE;
    }

    /* 如果错误码不是异系统, 则该激活流程终止 */
    if (APP_ERR_SM_SUSPENDED != pstEsmNdisconnCnfRej->ulRslt)
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                          ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapEsmCause(pstEsmNdisconnCnfRej->ulRslt));

        /* 释放资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);
    }

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitEsmActivateCnfSuspend
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND子状态下
             收到TI_TAF_APS_MS_ACTIVATING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月25日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiMsActivatingExpired_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                      ucPdpId);

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 向SM发送ABORT请求, 取消当前激活操作 */
    TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmSmEpsBearerInfoInd_MsActivating_WaitEsmActivateCnfSuspend(
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND主状态下收到ID_ESM_SM_EPS_BEARER_INFO_IND消息的处理
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
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsActivating_WaitEsmActivateCnfSuspend(
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
    if (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptActivate(pstPdpEntity, pstBearerInfo);

#if (FEATURE_ON == FEATURE_IPV6)
        /* 如果地址类型是IPv6, 需要同步给ND Client */
        if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
          && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);
        }
#endif
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive: Wrong option.");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitEsmActivateCnfSuspend(
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF_SUSPEND主状态下收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
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

  2.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : L丢网后，如果此时上报1X or Hrpd网络，需要先上报L下激活失败。由上层来触发重新激活

  3.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT8                                               ucPdpId;
#endif

    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if (TAF_APS_RAT_TYPE_LTE != pstServStaChangeInd->enRatType)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsActivating_WaitL4aActivateCnfSuspend: Wrong RAT type:", pstServStaChangeInd->enRatType);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if ((TAF_APS_RAT_TYPE_1X   == pstServStaChangeInd->enRatType)
         || (TAF_APS_RAT_TYPE_HRPD == pstServStaChangeInd->enRatType))
        {

            /* 初始化, 获取消息内容 */
            ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

            /* 停止激活流程定时器 */
            TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                              ucPdpId);

            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

            TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));

            /* 释放APS资源 */
            Aps_ReleaseApsResource(ucPdpId);

            /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            TAF_APS_QuitCurrSubFsm();
        }
#endif
        return VOS_TRUE;
    }

    /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_WaitEsmActivateCnfSuspend
 功能描述  : Wait ESM Activate Cnf Suspend State, Rcv Ehsm Pdn Irat Hrpd
             Ind Msg
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterAttachBearerActivateInd_MsActivating_WaitEsmActivateCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT32                          ulRemainTimeLen;
    VOS_UINT8                           ucPdpId;

    ulRemainTimeLen = 0;
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取定时器剩余时长 */
    TAF_APS_GetRemainTimerLen(TI_TAF_APS_MS_ACTIVATING, ucPdpId, &ulRemainTimeLen);

    /* 如果剩余时长非0, 停止当前流程, 重新处理当前的状态机入口消息 */
    if (0 != ulRemainTimeLen)
    {
        /* 记录剩余时长 */
        TAF_APS_SetCallRemainTmrLen(TAF_APS_GetPdpEntCurrCid(ucPdpId), ulRemainTimeLen);

        /* 向L模发送ABORT消息 */
        TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 发送状态机入口消息至内部消息队列 */
        TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

#endif

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitEsmActivateCnf
 功能描述  : ACTIVATING主状态下收到ID_APS_APS_INTER_PDP_DEACTIVATE_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_MsActivating_WaitEsmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*---------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
       处理ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ消息
    ---------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_GuMode
 功能描述  : ACTIVATEING主状态下收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年11月13日
    作    者   : A00165503
    修改内容   : DTS2012111205973: LTE默认缺省承载IP类型IPv4v6, 用户拨号IP类
                 型IPv4 only或IPv6 only, 缺省承载IP类型被错误的修改为用户拨
                 号IP类型

  3.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: PS域呼叫建立流程优化

  4.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: 修改部分函数调用
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_GuMode(VOS_VOID)
{
    TAF_PDP_TABLE_STRU                 *pstTafCidInfo;
    TAF_PS_CAUSE_ENUM_UINT32            enRet;
    VOS_UINT32                          ulTimerLen;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;

    /* 初始化 */
    enRet   = TAF_PS_CAUSE_SUCCESS;

    /* 获取APS实体索引 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取CID */
    ucCid   = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    pstTafCidInfo = TAF_APS_GetTafCidInfoAddr(ucCid);
    if (VOS_TRUE == pstTafCidInfo->ucPriCidFlag)
    {
        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(pstTafCidInfo->ucPriCid));
    }
    else
    {
        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(ucCid));
    }

    /* 发起PDP激活请求 */
    enRet = TAF_APS_PsCallOrig(ucPdpId);
    if (TAF_PS_CAUSE_SUCCESS != enRet)
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
        TAF_APS_SndPdpActivateRej(ucPdpId, enRet);

        /* 清除APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF);

        /* 检查定时器是否正在运行, 如果正在运行, 则不需要重新启动 */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_GuMode
 功能描述  : ACTIVATEING主状态下收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年11月13日
    作    者   : A00165503
    修改内容   : DTS2012111205973: LTE默认缺省承载IP类型IPv4v6, 用户拨号IP类
                 型IPv4 only或IPv6 only, 缺省承载IP类型被错误的修改为用户拨
                 号IP类型

  3.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: PS域呼叫建立流程优化

  4.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: 修改部分函数调用
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_GuMode(VOS_VOID)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    TAF_PS_CAUSE_ENUM_UINT32            enRet;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;

    /* 初始化 */
    enRet             = TAF_PS_CAUSE_SUCCESS;

    /* 获取消息内容 */
    pstEntryMsg       = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg         = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 获取APS实体索引 */
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取CID */
    ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(ucCid));

    /* 发起PDP激活请求 */
    enRet = MN_APS_RcvPppDialOrigReq(ucPdpId,
                                     &(pstPppDialOrigReq->stPppDialParaInfo));
    if (TAF_PS_CAUSE_SUCCESS != enRet)
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
        TAF_APS_SndPdpActivateRej(ucPdpId, enRet);

        /* 清除APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF);

        /* 检查定时器是否正在运行, 如果正在运行, 则不需要重新启动 */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsActivating_GuMode
 功能描述  : ACTIVATEING主状态下收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年11月13日
    作    者   : A00165503
    修改内容   : DTS2012111205973: LTE默认缺省承载IP类型IPv4v6, 用户拨号IP类
                 型IPv4 only或IPv6 only, 缺省承载IP类型被错误的修改为用户拨
                 号IP类型

  3.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: PS域呼叫建立流程优化

  4.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: 修改部分函数调用
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallOrigReq_MsActivating_GuMode(VOS_VOID)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    TAF_PS_CAUSE_ENUM_UINT32            enRet;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;

    /* 初始化错误码 */
    enRet          = TAF_PS_CAUSE_SUCCESS;

    /* 获取消息内容 */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg      = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstCallOrigReq = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 获取APS实体索引 */
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取CID */
    ucCid          = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* 设置呼叫IP类型 */
    TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, pstCallOrigReq->stDialParaInfo.enPdpType);

    /* 发起PDP激活请求 */
    enRet = MN_APS_RcvCallOrigReq(ucPdpId, &(pstCallOrigReq->stDialParaInfo));
    if (TAF_PS_CAUSE_SUCCESS != enRet)
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
        TAF_APS_SndPdpActivateRej(ucPdpId, enRet);

        /* 清除APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF);

        /* 检查定时器是否正在运行, 如果正在运行, 则不需要重新启动 */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
        }
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_LteMode
 功能描述  : ACTIVATEING主状态下收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: PS域呼叫建立流程优化

  3.日    期   : 2014年3月20日
    作    者   : A00165503
    修改内容   : DTS2014032005866: 修改挂起呼叫请求的条件, 只要任意承载存在
                 就需要建立新的PDN连接

  4.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtSetPdpContextStateReq_MsActivating_LteMode(VOS_VOID)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;
    TAF_PDP_TABLE_STRU                 *pstCidCtx;
    VOS_UINT32                          ulTimerLen;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucAttachAllowFlg;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;

    /* 获取消息内容 */
    pstEntryMsg          = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg            = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstSetPdpCtxStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* 获取APS实体索引 */
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取CID */
    ucCid                = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* 如果注册承载不存在且注册允许标识为TRUE, 则缓存该呼叫建立请求 */
    ucAttachAllowFlg = TAF_APS_GetAttachAllowFlg();
    if ( (VOS_FALSE == TAF_APS_IsAnyBearerExist())
      && (VOS_TRUE == ucAttachAllowFlg) )
    {
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
        }
        return;
    }

    /* 保存该次激活请求的PDP类型，如果是二次PDP激活，则需要找到主PDP所对应的CID */
    pstCidCtx = TAF_APS_GetTafCidInfoAddr(ucCid);
    if (VOS_TRUE == pstCidCtx->ucPriCidFlag)
    {
        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(pstCidCtx->ucPriCid));
    }
    else
    {
        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_GetTafCidInfoPdpType(ucCid));
    }

    /* 向ESM发送EPS承载激活请求 */
    TAF_APS_SndEsmSetCgactMsgDistr(ucPdpId, pstSetPdpCtxStateReq);

    /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF);

    /* 检查定时器是否正在运行, 如果正在运行, 则不需要重新启动 */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                     TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
        TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
        TAF_APS_SetCallRemainTmrLen(ucCid, 0);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_LteMode
 功能描述  : ACTIVATEING主状态下收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: PS域呼叫建立流程优化

  3.日    期   : 2014年3月20日
    作    者   : A00165503
    修改内容   : DTS2014032005866: 修改挂起呼叫请求的条件, 只要任意承载存在
                 就需要建立新的PDN连接

  4.日    期   : 2015年4月20日
    作    者   : Y00213812
    修改内容   : LTE不支持PPP类型的PPP拨号，支持所有IP类型的拨号

  5.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsPppDialOrigReq_MsActivating_LteMode(VOS_VOID)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_AUTH_INFO_STRU              stAuthInfo;
    TAF_APS_IPCP_INFO_STRU              stIpcpInfo;
    VOS_UINT32                          ulDecAuthRst;
    VOS_UINT32                          ulDecIpcpRst;
    VOS_UINT32                          ulTimerLen;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucAttachAllowFlg;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;

    /* 初始化 */
    PS_MEM_SET(&stAuthInfo, 0, sizeof(TAF_APS_AUTH_INFO_STRU));
    PS_MEM_SET(&stIpcpInfo, 0, sizeof(TAF_APS_IPCP_INFO_STRU));

    /* 获取消息内容 */
    pstEntryMsg       = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg         = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 获取APS实体索引 */
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取CID */
    ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* 如果注册承载不存在且注册允许标识为TRUE, 则缓存该呼叫建立请求 */
    ucAttachAllowFlg = TAF_APS_GetAttachAllowFlg();
    if ( (VOS_FALSE == TAF_APS_IsAnyBearerExist())
      && (VOS_TRUE == ucAttachAllowFlg) )
    {
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
        }
        return;
    }

    /* 解码PPP DIAL REQ中AUTH和IPCP信元 */
    ulDecAuthRst = TAF_APS_DecodeAuthInfo(&stAuthInfo,
                                             &(pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth));
    ulDecIpcpRst = TAF_APS_DecodeIpcpPkt(&stIpcpInfo,
                                         pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stIPCP.aucIpcp,
                                         pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stIPCP.usIpcpLen);
    if ((VOS_OK != ulDecAuthRst)
     || (VOS_OK != ulDecIpcpRst))
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_UNKNOWN);

        /* 清除APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return;
    }

    if (TAF_PDP_PPP == TAF_APS_GetPdpEntDialPdpType(ucPdpId, ucCid))
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING, ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_UNKNOWN);

        /* 清除APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return;
    }

    /* 向ESM发送PPP激活请求 */
    TAF_APS_SndEsmPppDialSetupReq(pstPppDialOrigReq,
                                  &stAuthInfo,
                                  &stIpcpInfo);

    /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF);

    /* 检查定时器是否正在运行, 如果正在运行, 则不需要重新启动 */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                     TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
        TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
        TAF_APS_SetCallRemainTmrLen(ucCid, 0);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsActivating_LteMode
 功能描述  : ACTIVATEING主状态下收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2014年2月20日
    作    者   : A00165503
    修改内容   : DTS2013022201185: PS域呼叫建立流程优化

  3.日    期   : 2014年3月20日
    作    者   : A00165503
    修改内容   : DTS2014032005866: 修改挂起呼叫请求的条件, 只要任意承载存在
                 就需要建立新的PDN连接

  4.日    期   : 2014年5月16日
    作    者   : A00165503
    修改内容   : DTS2014050703206: 根据呼叫参数设置当前IP类型

  5.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallOrigReq_MsActivating_LteMode(VOS_VOID)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    VOS_UINT32                          ulTimerLen;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucAttachAllowFlg;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32                          ucT3402State;
#endif

    /* 获取消息内容 */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg      = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstCallOrigReq = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 获取APS实体索引 */
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取CID */
    ucCid          = TAF_APS_GetPdpEntCurrCid(ucPdpId);

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    if (VOS_TRUE == TAF_SDC_IsConfigCLInterWorkCOutside())
    {
        ucT3402State   = TAF_APS_IsT3402Running();

        if ((VOS_FALSE == TAF_APS_IsAnyBearerExist())
         && (VOS_TRUE  == ucT3402State))
        {
            /* 停止激活流程定时器 */
            TAF_APS_StopTimer(TI_TAF_APS_MS_ACTIVATING,
                              ucPdpId);

            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_GMM_DETACH_NOT_REATTACH);

            /* 释放APS资源 */
            Aps_ReleaseApsResource(ucPdpId);

            /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
            TAF_APS_QuitCurrSubFsm();
            return;
        }
    }
#endif

    /* 如果注册承载不存在且注册允许标识为TRUE, 则缓存该呼叫建立请求 */
    ucAttachAllowFlg = TAF_APS_GetAttachAllowFlg();
    if ( (VOS_FALSE == TAF_APS_IsAnyBearerExist())
      && (VOS_TRUE == ucAttachAllowFlg) )
    {
        TAF_APS_SetPdpEntAddrType(ucPdpId, pstCallOrigReq->stDialParaInfo.enPdpType);
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_SUSPEND);
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                         TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
            TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
        }
        return;
    }

    /* 设置呼叫IP类型 */
    TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                 ucCid,
                                 pstCallOrigReq->stDialParaInfo.enPdpType);

    /* 向ESM发送EPS承载激活请求 */
    (VOS_VOID)TAF_APS_SndEsmNdisconnReq(pstCallOrigReq);

    /* 子状态迁移至TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_ESM_ACTIVATE_CNF);

    /* 检查定时器是否正在运行, 如果正在运行, 则不需要重新启动 */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_ACTIVATING, ucPdpId);
    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        ulTimerLen = (0 != TAF_APS_GetCallRemainTmrLen(ucCid)) ?
                     TAF_APS_GetCallRemainTmrLen(ucCid) : TI_TAF_APS_MS_ACTIVATING_LEN;
        TAF_APS_StartTimer(TI_TAF_APS_MS_ACTIVATING, ulTimerLen, ucPdpId);
        TAF_APS_SetCallRemainTmrLen(ucCid, 0);
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

