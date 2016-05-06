
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmNwActivating.c
  版 本 号   : 初稿
  作    者   : S62952
  生成日期   : 2011年12月14日
  最近修改   :
  功能描述   : NwActivating状态机处理函数
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月14日
    作    者   : S62952
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
#include "TafTypeDef.h"
#include "TafApsApi.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "MmcApsInterface.h"
#include "TafLog.h"
#include "Taf_Aps.h"
#include "TafApsCtx.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsFsmNwActivating.h"
#include "TafApsFsmNwActivatingTbl.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "TafApsProcIpFilter.h"
#include "TafApsSndRabm.h"
#include "TafApsSndSm.h"
#include "TafApsSndAt.h"
#include "TafApsSndInternalMsg.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#include "MnApsMultiMode.h"
#include "ApsL4aInterface.h"
#include "TafApsSndL4a.h"
#include "TafApsSndEsm.h"
#include "TafSmInterface.h"
#endif

#include "TafApsComFunc.h"
#include "ApsNdInterface.h"
#include "TafApsSndNd.h"

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_NWACTIVATING_C

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
*****************************************************************************/


/******************************************************************************
   5 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpActivateInd_NwActivating_Init
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_INIT子状态下
             收到D_PMC_SMREG_PDP_ACT_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpActivateInd_NwActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /*--------------------------------------------------------------------------
       当前模为G/W:  子状态迁移至TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER
    --------------------------------------------------------------------------*/

    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_NW_ACTIVATING);
    TAF_APS_RcvSmPdpActivateInd_NwActivating_GuMode();

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmPdpManageInd_NwActivating_Init
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_INIT子状态下
             收到ID_APP_ESM_PDP_MANAGER_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpManageInd_NwActivating_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /*--------------------------------------------------------------------------
       当前模为LTE:  子状态迁移至TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER
    --------------------------------------------------------------------------*/

    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_NW_ACTIVATING);
    TAF_APS_RcvEsmPdpManageInd_NwActivating_LteMode();

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSetPdpContextStateReq_NwActivating_WaitAppAnswer
 功能描述  : 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态下
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
VOS_UINT32 TAF_APS_RcvSetPdpContextStateReq_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq   = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* 等待用户应答的时候，上报PDP激活/去激活错误事件 */
    TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitAppAnswer
 功能描述  : 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态下
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
    作    者   : S62952
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    /* 初始化, 获取消息内容 */
    enCurrRatType     = TAF_APS_GetCurrPdpEntityRatType();
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* IP类型的网络激活应答，AT^CGANS只支持GU模 */
    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitAppAnswer_GuMode(pstMsg);
            break;

        default:
            TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                     TAF_PS_CAUSE_UNKNOWN);
            break;
    }



    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitAppAnswer
 功能描述  : 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态下
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
    作    者   : S62952
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitAppAnswer(
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
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitAppAnswer
 功能描述  : 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态下
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
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
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
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitAppAnswer
 功能描述  : 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态下
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
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitAppAnswer(
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
 函 数 名  : TAF_APS_RcvAtPsCallAnswerReq_NwActivating_WaitAppAnswer
 功能描述  : 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态下
             收到ID_MSG_TAF_PS_CALL_ANSWER_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_ANSWER_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月12日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32            enCurrRatType;

    /* 初始化, 获取消息内容 */
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_RcvAtPsCallAnswerReq_NwActivating_GuMode(pstMsg);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            TAF_APS_RcvAtPsCallAnswerReq_NwActivating_LteMode(pstMsg);

            break;
#endif

        default:
            TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvAtPsCallAnswerReq_NwActivating_WaitAppAnswer,enCurrRatType", enCurrRatType);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallHangupReq_NwActivating_WaitAppAnswer
 功能描述  : 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态下
             收到ID_MSG_TAF_PS_CALL_HANGUP_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_HANGUP_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : S62952
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    /* 初始化, 获取消息内容 */
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在等待应答，此时有挂断操作, 直接返回TAF_ERR_NO_ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl), TAF_ERR_NO_ERROR);

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_RcvAtPsCallHangUpReq_NwActivating_GuMode(pstMsg);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            TAF_APS_RcvAtPsCallHangUpReq_NwActivating_LteMode(pstMsg);

            break;
#endif

        default:
            TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvAtPsCallHangupReq_NwActivating_WaitAppAnswer,enCurrRatType", enCurrRatType);
            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitAppAnswer
 功能描述  : 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态下
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
    修改内容   : 修改入口消息
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd;
    VOS_UINT8                                               ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32                            enLastRatType;                              /* 查询返回的当前参数 */

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd                 = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 记录前一次的网络类型 */
    enLastRatType = pstServStaChangeInd->enLastRatType;

    /* 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态
       如果enRatType为TAF_APS_RAT_TYPE_NULL，说明丢网或者异系统，此时流程终止 */
    if (TAF_APS_RAT_TYPE_NULL == pstServStaChangeInd->enRatType)
    {
        /* 给应用回挂断指示 */
        TAF_APS_SndPdpDisconnectInd(ucPdpId);

        /* 向SM发送Abort */
        if ((TAF_APS_RAT_TYPE_GSM == enLastRatType)
         || (TAF_APS_RAT_TYPE_WCDMA == enLastRatType))
        {
            TAF_APS_SndSmPdpAbortReq(ucPdpId);
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* 向ESM发送Abort */
        if (TAF_APS_RAT_TYPE_LTE == enLastRatType)
        {
            TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
#endif

        /* 停保护定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING, ucPdpId);

        /* 释放资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitAppAnswer: Wrong Rat Type");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitAppAnswer
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER子状态下
             收到TI_TAF_APS_NET_ACTIVATING消息的处理
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

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 给应用回挂断指示 */
    TAF_APS_SndPdpDisconnectInd(ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpDeactivateInd_NwActivating_WaitAppAnswer
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER子状态下
             收到ID_SMREG_PDP_DEACTIVATE_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月15日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_NwActivating_WaitAppAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* stop保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING, ucPdpId);

    /* 给应用回挂断指示 */
    TAF_APS_SndPdpDisconnectInd(ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitSmActivateCnf(
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

    /* 正在激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
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
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
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
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitSmActivateCnf(
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
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitSmActivateCnf(
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
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
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
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitSmActivateCnf(
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
 函 数 名  : TAF_APS_RcvSmPdpDeactivInd_NwActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到D_PMC_SMREG_PDP_DEACTIV_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : D_PMC_SMREG_PDP_DEACTIV_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivInd_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;


    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();
    pstSmPdpDeactivateInd = (SMREG_PDP_DEACTIVATE_IND_STRU*)pstMsg;

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
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
 函 数 名  : TAF_APS_RcvSmPdpActRej_NwActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到D_PMC_SMREG_PDP_ACT_REJ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : D_PMC_SMREG_PDP_ACT_REJ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpActRej_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    SMREG_PDP_ACTIVATE_REJ_STRU        *pstSmPdpActivateRej;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();
    pstSmPdpActivateRej = (SMREG_PDP_ACTIVATE_REJ_STRU *)pstMsg;

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                      ucPdpId);

    /* 本状态下收到D_PMC_SMREG_PDP_ACT_REJ为异常消息,上报错误事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmPdpActivateRej->enCause));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpActSecRej_NwActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到D_PMC_SMREG_PDP_ACT_SEC_REJ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : D_PMC_SMREG_PDP_ACT_SEC_REJ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpActSecRej_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    VOS_UINT8                           ucPdpId;
    SMREG_PDP_ACTIVATE_SEC_REJ_STRU    *pstSmSecPdpActivateRej;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();
    pstSmSecPdpActivateRej = (SMREG_PDP_ACTIVATE_SEC_REJ_STRU*)pstMsg;


    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                      ucPdpId);

    /* 本状态下收到D_PMC_SMREG_PDP_ACT_REJ为异常消息,上报错误事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_MapSmCause(pstSmSecPdpActivateRej->enCause));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpActSecCnf_NwActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到D_PMC_SMREG_PDP_ACT_SEC_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : D_PMC_SMREG_PDP_ACT_SEC_CNF消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

  3.日    期   : 2013年01月21日
    作    者   : A00165503
    修改内容   : DTS2013011803709: 激活ND Client增加接入技术判断, 防止在NULL
                 状态下激活ND Client导致RS包被丢弃

  4.日    期   : 2013年5月15日
    作    者   : w00167002
    修改内容   : DTS2013051408623:V3R2 lint不过修改
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpActSecCnf_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    APS_ACTSECCNF_PARA_ST               stParam;

#if (FEATURE_ON == FEATURE_LTE)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif

    SMREG_PDP_ACTIVATE_SEC_CNF_STRU    *pstSmSecPdpActivateCnf;

    /* 初始化, 获取消息内容 */
    pstSmSecPdpActivateCnf = (SMREG_PDP_ACTIVATE_SEC_CNF_STRU *)pstMsg;
    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType          = TAF_APS_GetCurrPdpEntityRatType();

#if (FEATURE_ON == FEATURE_LTE)
    pstPdpEntity        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
#endif

    /* 停止网络激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                          ucPdpId);

    /* 检查输入的参数 */
    ulRet = Aps_PdpActSecCnfParaCheck(pstSmSecPdpActivateCnf, &stParam);
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
            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_INSUFFICIENT_RESOURCES);

            /* 发送内部消息, 去激活PDP */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES);
        }

        return VOS_TRUE;
    }

    /* 检查QOS是否满足MIN要求 */
    if (APS_PARA_VALID  == Aps_CheckQosSatisify(ucPdpId, &stParam.PdpQos))
    {
        /* 满足MINQOS */
        Aps_PdpActSecCnfQosSatisfy(ucPdpId, &stParam, pstSmSecPdpActivateCnf);

#if (FEATURE_ON == FEATURE_LTE)
        /* 同步PDP信息至ESM */
        MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_ACTIVATE);
#endif

        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_GSM:
                /* 子状态迁移至TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP */
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP);
                break;

            case TAF_APS_RAT_TYPE_WCDMA:
                /* 激活成功，启动流量统计 */
                TAF_APS_StartDsFlowStats(pstSmSecPdpActivateCnf->ucNsapi);

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
                    "TAF_APS_RcvSmPdpActCnf_NwActivating_WaitSmActivateCnf: Wrong RAT type!");
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
 函 数 名  : TAF_APS_RcvSmPdpActCnf_NwActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_PMC_SMREG_PDP_ACT_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_PMC_SMREG_PDP_ACT_CNF消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月12日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理

  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

  4.日    期   : 2013年01月21日
    作    者   : A00165503
    修改内容   : DTS2013011803709: 激活ND Client增加接入技术判断, 防止在NULL
                 状态下激活ND Client导致RS包被丢弃
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpActCnf_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    APS_ACTCNF_PARA_ST                  stParam;
#if ((FEATURE_ON == FEATURE_LTE) || (FEATURE_ON == FEATURE_IPV6))
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif
    SMREG_PDP_ACTIVATE_CNF_STRU        *pstSmPdpActivateCnf;

    /* 初始化, 获取消息内容 */
    pstSmPdpActivateCnf = (SMREG_PDP_ACTIVATE_CNF_STRU *)pstMsg;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType       = TAF_APS_GetCurrPdpEntityRatType();
#if ((FEATURE_ON == FEATURE_LTE) || (FEATURE_ON == FEATURE_IPV6))
    pstPdpEntity        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
#endif


    PS_MEM_SET(&stParam, 0x00, sizeof(stParam));


    /* 停止网络激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
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
            TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_INSUFFICIENT_RESOURCES);

            /* 发送内部消息, 去激活PDP */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES);
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

                /* 子状态迁移至TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP */
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP);
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
                    "TAF_APS_RcvSmPdpActCnf_NwActivating_WaitSmActivateCnf: Wrong RAT type!");
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
 函 数 名  : TAF_APS_RcvApsInterPdpDeactivateReq_NwActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到ID_APS_APS_INTER_PDP_DEACTIVATE_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_NwActivating_WaitSmActivateCnf(
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
 函 数 名  : TAF_APS_RcvApsLocalPdpDeactivateInd_NwActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
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
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_NwActivating_WaitSmActivateCnf(
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
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
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
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitSmActivateCnf
 功能描述  : 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月12日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 修改入口消息
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitSmActivateCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd;
    VOS_UINT8                                               ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32                            enLastRatType;                              /* 查询返回的当前参数 */

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd                 = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 记录前一次的网络类型 */
    enLastRatType = pstServStaChangeInd->enLastRatType;

    /* 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态
       如果enRatType为MMC_APS_RAT_TYPE_NULL，
       说明丢网或者切换，认为是异常情况 */
    if (TAF_APS_RAT_TYPE_NULL == pstServStaChangeInd->enRatType)
    {
        /* 给应用回挂断指示 */
        TAF_APS_SndPdpDisconnectInd(ucPdpId);

        /* 向SM发送Abort */
        if ((TAF_APS_RAT_TYPE_GSM   == enLastRatType)
         || (TAF_APS_RAT_TYPE_WCDMA == enLastRatType))
        {
            TAF_APS_SndSmPdpAbortReq(ucPdpId);
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* 向ESM发送Abort */
        if (TAF_APS_RAT_TYPE_LTE == enLastRatType)
        {
            TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
#endif

        /* 停保护定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING, ucPdpId);

        /* 释放资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitSmActivateCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF子状态下
             收到TI_TAF_APS_NET_ACTIVATING消息的处理
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
VOS_UINT32 TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitSmActivateCnf(
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

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitEsmCgansCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitEsmCgansCnf(
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

    /* 正在激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
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
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
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
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitEsmCgansCnf
 功能描述  : 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitEsmCgansCnf(
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
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitEsmCgansCnf
 功能描述  : 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitEsmCgansCnf(
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
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitEsmCgansCnf
 功能描述  : 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitEsmCgansCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
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
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitEsmCgansCnf
 功能描述  : 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitEsmCgansCnf(
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
 函 数 名  : TAF_APS_RcvL4aSetCgansCnf_NwActivating_WaitEsmCgansCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF子状态下
             收到ID_L4A_APS_SET_CGANS_CNF消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_L4A_APS_SET_CGANS_CNF消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgansCnf_NwActivating_WaitEsmCgansCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 初始化, 获取消息内容 */
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 停止网络激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                      ucPdpId);

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果地址类型是IPv6, 需要同步给ND Client */
    if (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId))
    {
        TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                               pstPdpEntity->PdpAddr.aucIpV6Addr);
    }
#endif

#if (FEATURE_ON == FEATURE_IMS)
    /* 处理IMS专有承载 */
    TAF_APS_ProcImsDedicateBearer(pstPdpEntity);
#endif

    /* 激活成功，启动流量统计 */
    TAF_APS_StartDsFlowStats(pstPdpEntity->ucNsapi);

    /* 如果当前APS实体的PDP类型为IPv4, 需要配置IPF */
    if (TAF_APS_CheckPdpAddrTypeIpv4(ucPdpId))
    {
        /* 配置IP过滤器 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);
    }

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitEsmCgansCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 修改入口消息
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitEsmCgansCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd;
    VOS_UINT8                                               ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32                            enLastRatType;                              /* 查询返回的当前参数 */

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd                 = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 记录前一次的网络类型 */
    enLastRatType = pstServStaChangeInd->enLastRatType;

    /* 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_L4A_CGANS_CNF状态
       如果enRatType为TAF_APS_RAT_TYPE_NULL，说明丢网或者异系统，当前流程终止 */
    if (TAF_APS_RAT_TYPE_NULL == pstServStaChangeInd->enRatType)
    {
        /* 给应用回挂断指示 */
        TAF_APS_SndPdpDisconnectInd(ucPdpId);

        /* 向SM发送Abort */
        if ((TAF_APS_RAT_TYPE_GSM   == enLastRatType)
         || (TAF_APS_RAT_TYPE_WCDMA == enLastRatType))
        {
            TAF_APS_SndSmPdpAbortReq(ucPdpId);
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* 向ESM发送Abort */
        if (TAF_APS_RAT_TYPE_LTE == enLastRatType)
        {
            TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
#endif

        /* 停保护定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING, ucPdpId);

        /* 释放资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmSmEpsBearerInfoInd_NwActivating_WaitEsmCgansCnf(
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF主状态下收到ID_ESM_SM_EPS_BEARER_INFO_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年01月13日
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

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_NwActivating_WaitEsmCgansCnf(
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
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_NwActivating_WaitEsmCgansCnf: Wrong option.");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitEsmCgansCnf
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF子状态下
             收到TI_TAF_APS_NET_ACTIVATING消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : TI_TAF_APS_NET_ACTIVATING消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitEsmCgansCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 向ESM发送Abort */
    TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
#endif
/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitSndcpActivateRsp(
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
        /* 停止网侧激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
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
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitSndcpActivateRsp(
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
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : s62952
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitSndcpActivateRsp(
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
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止网侧激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
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
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitSndcpActivateRsp(
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
 函 数 名  : TAF_APS_RcvSmPdpDeactivInd_NwActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到ID_PMC_SMREG_PDP_DEACTIV_IND消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_PMC_SMREG_PDP_DEACTIV_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivInd_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    /* 初始化, 获取消息内容 */
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity            = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstSmPdpDeactivateInd   = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* ID_PMC_SMREG_PDP_DEACTIV_IND消息处理说明,在状态机中不需要对TEARDOWN
       再进行判断处理,APS在收到ID_PMC_SMREG_PDP_DEACTIV_IND消息进行预处理,
       如果消息中带有TEARDOWN,预处理中找出都有哪些PDP待去激活,然后,将
       ID_PMC_SMREG_PDP_DEACTIV_IND分发到相应的实体状态中,所以,在状态机中不再
       对ID_PMC_SMREG_PDP_DEACTIV_IND中的TEARDOWN再作处理 */

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
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
 函 数 名  : TAF_APS_RcvSndcpActivateRsp_NwActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到APS_SN_ACT_RSP_MSG_TYPE消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_NwActivating_WaitSndcpActivateRsp(
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
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                      ucPdpId);

    /* 检查消息参数 */
    ulResult = Aps_SnMsgModSnActRspParaCheck(pstSnActivateRsp);
    if (APS_PARA_VALID != ulResult)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSndcpActivateRsp_NwActivating_WaitSndcpActivateRsp: Check para failed!");

        /* 上报激活失败 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

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
 函 数 名  : TAF_APS_RcvSndcpStatusReq_NwActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到APS_SN_STATUS_REQ_MSG_TYPE消息的处理
 输入参数  : ulEventType:消息类型
              pstMsg     : APS_SN_STATUS_REQ_MSG_TYPE消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
              VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_NwActivating_WaitSndcpActivateRsp(
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
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                          ucPdpId);

        /*上报激活失败并清资源*/
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* 发送内部消息, 触发PDP去激活流程 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsInterPdpDeactivateReq_NwActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月13日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsInterPdpDeactivateReq_NwActivating_WaitSndcpActivateRsp(
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
 函 数 名  : TAF_APS_RcvApsLocalPdpDeactivateInd_NwActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
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
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalMsg;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstLocalMsg  = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
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
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitSndcpActivateRsp
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
    修改内容   : 修改入口消息
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitSndcpActivateRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd;
    VOS_UINT8                                               ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32                            enLastRatType;                              /* 查询返回的当前参数 */

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd                 = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 记录前一次的网络类型 */
    enLastRatType = pstServStaChangeInd->enLastRatType;

    /* 在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态
       如果enRatType为TAF_APS_RAT_TYPE_NULL，
       说明丢网或者切换，认为是异常情况 */
    if (TAF_APS_RAT_TYPE_NULL == pstServStaChangeInd->enRatType)
    {
        /* 给应用回挂断指示 */
        TAF_APS_SndPdpDisconnectInd(ucPdpId);

        /* 向SM发送Abort */
        if ((TAF_APS_RAT_TYPE_GSM   == enLastRatType)
         || (TAF_APS_RAT_TYPE_WCDMA == enLastRatType))
        {
            TAF_APS_SndSmPdpAbortReq(ucPdpId);
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* 向ESM发送Abort */
        if (TAF_APS_RAT_TYPE_LTE == enLastRatType)
        {
            TAF_APS_SndL4aAbortReq(TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
#endif

        /* 停保护定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING, ucPdpId);

        /* 释放资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitSndcpActivateRsp
 功能描述  : TAF_APS_MS_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP子状态下
             收到TI_TAF_APS_NET_ACTIVATING消息的处理
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
VOS_UINT32 TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitSndcpActivateRsp(
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
    TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpActivateInd_NwActivating_GuMode_ManualAns
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_INIT子状态，手动应答下
             收到D_PMC_SMREG_PDP_ACT_IND消息的处理
 输入参数  : VOS_UINT8                           ucPdpId
             SMREG_PDP_ACTIVATE_IND_STRU        *pstSmPdpActivateInd
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月10日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_RcvSmPdpActivateInd_NwActivating_GuMode_ManualAns(
    VOS_UINT8                           ucPdpId,
    SMREG_PDP_ACTIVATE_IND_STRU        *pstSmPdpActivateInd
)
{
    VOS_UINT32                          ulRet;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    ulRet = TAF_APS_SndPdpManageInd(ucPdpId, pstSmPdpActivateInd);

    if (TAF_APS_SUCC == ulRet)
    {
        /* 迁移子状态机到TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER);

        /* 检查定时器是否正在运行, 如果正在运行, 则不需要重新启动 */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_NET_ACTIVATING,
                                               ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            /* 起保护定时器 */
            TAF_APS_StartTimer(TI_TAF_APS_NET_ACTIVATING,
                               TI_TAF_APS_NET_ACTIVATING_LEN,
                               ucPdpId);
        }
    }
    else
    {
        /*手动应答拒绝激活*/
        Aps_ActIndRejRsp(ucPdpId);

        /* 停保护定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING, ucPdpId);

        /* 释放资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpActivateInd_NwActivating_GuMode_AutoAns
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_INIT子状态，自动应答下
 输入参数  : VOS_UINT8                           ucAnswerType
             VOS_UINT8                           ucPdpId
             SMREG_PDP_ACTIVATE_IND_STRU        *pstSmPdpActivateInd
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月10日
    作    者   : 鲁琳/l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_RcvSmPdpActivateInd_NwActivating_GuMode_AutoAns(
    VOS_UINT8                           ucAnswerType,
    VOS_UINT8                           ucPdpId,
    SMREG_PDP_ACTIVATE_IND_STRU        *pstSmPdpActivateInd
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulActReqRslt;
    APS_PDP_ACT_REQ_ST                  stApsPdpActReq;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    PS_MEM_SET(&stApsPdpActReq, 0x00, sizeof(stApsPdpActReq));

    ulRet = Aps_ActIndAutoAns(ucAnswerType, ucPdpId, pstSmPdpActivateInd, &stApsPdpActReq);

    if (TAF_APS_SUCC == ulRet)
    {
        /* 发起激活请求 */
        ulActReqRslt = Aps_PdpActReq(&stApsPdpActReq);

        if (TAF_APS_SUCC == ulActReqRslt)
        {
            /* 迁移子状态机到TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF);

            /* 检查定时器是否正在运行, 如果正在运行, 则不需要重新启动 */
            enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_NET_ACTIVATING,
                                                   ucPdpId);
            if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
            {
                /* 起保护定时器 */
                TAF_APS_StartTimer(TI_TAF_APS_NET_ACTIVATING,
                                   TI_TAF_APS_NET_ACTIVATING_LEN,
                                   ucPdpId);
            }

            return;
        }
    }

    /* 自动应答拒绝激活 */
    Aps_ActIndRejRsp(ucPdpId);

    /* 停保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING, ucPdpId);

    /* 释放资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* 退出子状态机 */
    TAF_APS_QuitCurrSubFsm();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpActivateInd_NwActivating_GuMode
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_INIT子状态下
             收到D_PMC_SMREG_PDP_ACT_IND消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2015年4月2日
    作    者   : w00316404
    修改内容   : clean coverity
*****************************************************************************/
VOS_VOID TAF_APS_RcvSmPdpActivateInd_NwActivating_GuMode(VOS_VOID)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    SMREG_PDP_ACTIVATE_IND_STRU        *pstSmPdpActivateInd;
    TAF_PDP_ANSWER_MODE_ENUM_UINT8      ucAnswerMode;                           /*是自动应答, 还是手动应答*/
    TAF_PDP_ANSWER_TYPE_ENUM_UINT8      ucAnswerType;                           /*自动应答是接受,还是拒绝*/

    ucAnswerType                        = TAF_PDP_ANSWER_TYPE_BUTT;
    ucAnswerMode                        = TAF_PDP_ANSWER_MODE_BUTT;

    /* 初始化, 获取消息内容 */
    pstEntryMsg                         = TAF_APS_GetCurrSubFsmMsgAddr();
    pstSmPdpActivateInd                 = (SMREG_PDP_ACTIVATE_IND_STRU *)(pstEntryMsg->aucEntryMsgBuffer);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /*查询是自动应答还是手动应答, 以及自动应答的话, 是自动接受还是拒绝 */
    Aps_GetPsAnswerMode(&ucAnswerMode, &ucAnswerType);

    if (TAF_PDP_ANSWER_MODE_MANUAL == ucAnswerMode)
    {
        TAF_APS_RcvSmPdpActivateInd_NwActivating_GuMode_ManualAns(ucPdpId,
                                                                  pstSmPdpActivateInd);
    }
    else
    {
        TAF_APS_RcvSmPdpActivateInd_NwActivating_GuMode_AutoAns(ucAnswerType,
                                                                ucPdpId,
                                                                pstSmPdpActivateInd);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallAnswerReq_NwActivating_GuMode
 功能描述  : GU模，TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER子状态下
             收到ID_MSG_TAF_PS_CALL_ANSWER_REQ消息的处理
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallAnswerReq_NwActivating_GuMode(struct MsgCB *pstMsg)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;
    APS_PDP_ACT_REQ_ST                  stApsActReq;
    VOS_UINT32                          ulRet;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;


    PS_MEM_SET(&stApsActReq, 0x00, sizeof(stApsActReq));


    /* 初始化, 获取消息内容 */
    pstAppMsg            = (TAF_PS_MSG_STRU*)(pstMsg);
    pstCallAnswerReq     = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /*获取PDP ID*/
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();

    /* 检查PS域卡状态, 如果无效, 直接返回ERROR */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                          ucPdpId);
        /* 上报PDP操作结果 */
        TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                pstCallAnswerReq->stAnsInfo.ucCid,
                                TAF_PS_CAUSE_SIM_INVALID);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return;
    }

    Aps_MakeAnsActReq(pstCallAnswerReq->stAnsInfo.ucCid, ucPdpId, &stApsActReq);

    /*发起PDP激活*/
    ulRet = Aps_PdpActReq(&stApsActReq);

    if (TAF_APS_FAIL == ulRet)
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                          ucPdpId);

        /* 返回PDP操作结果 */
        TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                pstCallAnswerReq->stAnsInfo.ucCid,
                                TAF_ERR_UNSPECIFIED_ERROR);

        /* 清除APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* 返回PDP操作结果 */
        TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                pstCallAnswerReq->stAnsInfo.ucCid,
                                TAF_ERR_NO_ERROR);

        /* 子状态迁移至TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF);

        /* 检查定时器是否正在运行, 如果正在运行, 则不需要重新启动 */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_NET_ACTIVATING,
                                               ucPdpId);

        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            /* 起保护定时器 */
            TAF_APS_StartTimer(TI_TAF_APS_NET_ACTIVATING,
                               TI_TAF_APS_NET_ACTIVATING_LEN,
                               ucPdpId);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallHangUpReq_NwActivating_GuMode
 功能描述  : GU模，TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态下
             收到ID_MSG_TAF_PS_CALL_HANGUP_REQ消息的处理
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月29日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallHangUpReq_NwActivating_GuMode(struct MsgCB *pstMsg)
{
    VOS_UINT8                           ucPdpId;

    /*获取PDP ID*/
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 网络激活手动应答中, 则该消息实际为: APP拒绝网络发起的激活 */
    Aps_ActIndRejRsp(ucPdpId);

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                      ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aPdpActivateInd_NwActivating_LteMode
 功能描述  : TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER子状态下
             收到ID_APP_ESM_PDP_MANAGER_IND消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2013年07月08日
    作    者   : Y00213812
    修改内容   : VoLTE_PhaseI 项目，EVENT结构替换
  3.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project

*****************************************************************************/
VOS_VOID TAF_APS_RcvEsmPdpManageInd_NwActivating_LteMode(VOS_VOID)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    APP_ESM_PDP_MANAGER_IND_STRU       *pstEsmPdpManageInd;
    TAF_PS_CALL_PDP_MANAGE_IND_STRU     stPdpActIndEvt;
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT8                           ucPdpId;
    TAF_PS_CALL_ANSWER_REQ_STRU         stCallAnswerReq;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
#endif
    /*---------------------------------------------------------
       LTE下，网络发起的激活，无论是自动应答还是手动应答都在
       ESM中实现，APS只进行透传，当aps收到ID_L4A_APS_PDP_ACTIVATE_IND
       时，APS将ACTIVATE IND事件上报给AT，AT上报应用RING或CRING
       进行响铃，APS不需要保存PDP上下文。
    ---------------------------------------------------------*/

    /* 初始化, 获取消息内容 */
    pstEntryMsg                         = TAF_APS_GetCurrSubFsmMsgAddr();
    pstEsmPdpManageInd                  = (APP_ESM_PDP_MANAGER_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

#if (FEATURE_ON == FEATURE_IMS)
    /* 判断当前是否存在IMS专有承载，判断PDP上下文信息中的ucLinkedRabid是否与IMS专有承载相同 */
    if (VOS_TRUE == pstEsmPdpManageInd->bitOpLinkCid)
    {
        if (VOS_TRUE == TAF_APS_CheckImsBearerByCid((VOS_UINT8)pstEsmPdpManageInd->ulLinkCid))
        {
            /*获取PDP ID*/
            ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

            /* 发送ID_APP_ESM_PDP_MANAGER_RSP给ESM */
            PS_MEM_SET(&stCallAnswerReq, 0, sizeof(TAF_PS_CALL_ANSWER_REQ_STRU));
            stCallAnswerReq.stCtrl.ucOpId       = (VOS_UINT8)pstEsmPdpManageInd->ulOpId;
            stCallAnswerReq.stAnsInfo.ucCid     = (VOS_UINT8)pstEsmPdpManageInd->ulCid;

            /*向L模发送应答请求，L模本地不会拒绝*/
            TAF_APS_SndEsmPdpManagerRsp(APS_ESM_BEARER_ACT_ACCEPT, stCallAnswerReq.stAnsInfo.ucCid);

            /* 迁移子状态机到TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF);


            /* 检查定时器是否正在运行, 如果正在运行, 则不需要重新启动 */
            enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_NET_ACTIVATING,
                                                   ucPdpId);

            if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
            {
                /* 起保护定时器 */
                TAF_APS_StartTimer(TI_TAF_APS_NET_ACTIVATING,
                                   TI_TAF_APS_NET_ACTIVATING_LEN,
                                   ucPdpId);
            }

            return;
        }
    }
#endif

    /* 否则上报ID_EVT_TAF_PS_CALL_PDP_ACTIVE_IND事件 */
    TAF_APS_FillCallEvtPdpAvtivateIndFromEsm(&stPdpActIndEvt,
                                             pstEsmPdpManageInd);

    /* 上报事件 */
    /*调用TAFM提供的事件上报函数 */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_MANAGE_IND,
                     &stPdpActIndEvt,
                     sizeof(TAF_PS_CALL_PDP_MANAGE_IND_STRU));

    /* 迁移子状态机到TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallAnswerReq_NwActivating_LteMode
 功能描述  : L模，TAF_APS_MS_ACTIVATING_SUBSTA_INIT子状态下
             收到ID_MSG_TAF_PS_CALL_ANSWER_REQ消息的处理
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年1月12日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报

  3.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallAnswerReq_NwActivating_LteMode(struct MsgCB *pstMsg)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    /* 初始化, 获取消息内容 */
    pstAppMsg            = (TAF_PS_MSG_STRU*)(pstMsg);
    pstCallAnswerReq     = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /*获取PDP ID*/
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();

    /* 检查PS域卡状态, 如果无效, 直接返回ERROR */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                          ucPdpId);

        /* 上报PDP操作结果 */
        TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                pstCallAnswerReq->stAnsInfo.ucCid,
                                TAF_PS_CAUSE_SIM_INVALID);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return;
    }

    /* 用户发起的CID不一定是LTE目前所使用的CID，因此这里刷新一下CID，
       L模仍然使用上报时所使用的CID值 */
    pstCallAnswerReq->stAnsInfo.ucCid = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /*向L模发送应答请求，L模本地不会拒绝*/
    TAF_APS_SndEsmPdpManagerRsp(APS_ESM_BEARER_ACT_ACCEPT, pstCallAnswerReq->stAnsInfo.ucCid);

    /* 迁移子状态机到TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF);

    /* 检查定时器是否正在运行, 如果正在运行, 则不需要重新启动 */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_NET_ACTIVATING,
                                           ucPdpId);

    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        /* 起保护定时器 */
        TAF_APS_StartTimer(TI_TAF_APS_NET_ACTIVATING,
                           TI_TAF_APS_NET_ACTIVATING_LEN,
                           ucPdpId);
    }

    return;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallHangUpReq_NwActivating_LteMode
 功能描述  : L模，TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态下
             收到ID_MSG_TAF_PS_CALL_HANGUP_REQ消息的处理
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月29日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project

*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallHangUpReq_NwActivating_LteMode(struct MsgCB *pstMsg)
{
    VOS_UINT8                           ucPdpId;

    /*获取PDP ID*/
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /*向LTE发送挂断请求，L模保证挂断不会失败*/
    TAF_APS_SndEsmPdpManagerRsp(APS_ESM_BEARER_ACT_REJ, 0);

    /* 停保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING, ucPdpId);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* 退出子状态机 */
    TAF_APS_QuitCurrSubFsm();

    return;
}

#endif

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitAppAnswer_GuMode
 功能描述  : GU模，在TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月7日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitAppAnswer_GuMode(struct MsgCB *pstMsg)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    APS_PDP_ACT_REQ_ST                  stApsActReq;
    VOS_UINT32                          ulRet;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    PS_MEM_SET(&stApsActReq, 0x00, sizeof(stApsActReq));

    /* 初始化, 获取消息内容 */
    pstAppMsg            = (TAF_PS_MSG_STRU*)(pstMsg);
    pstPppDialOrigReq    = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /*获取PDP ID*/
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();

    /* 检查PS域卡状态, 如果无效, 直接返回ERROR */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                          ucPdpId);

        /* 上报PDP操作结果 */
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                 TAF_PS_CAUSE_SIM_INVALID);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return;
    }

    TAF_APS_MakeIpTypeAnsExtActReq(ucPdpId, pstPppDialOrigReq, &stApsActReq);

    /*发起PDP激活*/
    ulRet = Aps_PdpActReq(&stApsActReq);

    if (TAF_APS_FAIL == ulRet)
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_NET_ACTIVATING,
                          ucPdpId);

        /* 返回PDP操作结果 */
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                 TAF_PS_CAUSE_UNKNOWN);

        /* 清除APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* 返回PDP操作结果 */
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                 TAF_PS_CAUSE_SUCCESS);

        /* 子状态迁移至TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF);

        /* 检查定时器是否正在运行, 如果正在运行, 则不需要重新启动 */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_NET_ACTIVATING,
                                               ucPdpId);

        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            /* 起保护定时器 */
            TAF_APS_StartTimer(TI_TAF_APS_NET_ACTIVATING,
                               TI_TAF_APS_NET_ACTIVATING_LEN,
                               ucPdpId);
        }
    }

    return;
}

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif










