
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmMsModifying.c
  版 本 号   : 初稿
  作    者   : S62952
  生成日期   : 2011年12月14日
  最近修改   :
  功能描述   : Modifying状态机处理函数
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月14日
    作    者   : S62952
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "TafLog.h"
#include "TafApsCtx.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "TafApsFsmMsModifying.h"
#include "TafApsFsmMsModifyingTbl.h"
#include "TafApsProcIpFilter.h"
#include "MmcApsInterface.h"
#include "TafApsSndInternalMsg.h"
#include "TafApsFsmMsDeactivating.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#include "MnApsMultiMode.h"
#include "ApsL4aInterface.h"
#include "TafApsSndL4a.h"
#include "TafApsSndSm.h"
#include "TafApsSndEsm.h"
#endif
#include "TafApsComFunc.h"
#include "MnComm.h"
#include "TafSdcCtx.h"
#include "TafAppMma.h"

#include "TafApsSndEhsm.h"
#include "TafSdcLib.h"

#include "TafApsSndPpp.h"
#include "TafApsSndNd.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MSMODIFYING_C

/******************************************************************************
   2 全局变量定义
*****************************************************************************/


/******************************************************************************
   3 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_Init
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_INIT子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
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

  2.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 增加NO RF丢网场景时, 触发搜网流程
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;
#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
#endif

    /* 初始化, 获取消息内容 */
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    /* 获取PDPId */
    ucPdpId                             = (VOS_UINT8)TAF_APS_GetCurrFsmEntityPdpId();

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

    /*--------------------------------------------------------------------------
       当前模为G/W:  子状态迁移至TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF
       当前模为LTE:  子状态迁移至TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF
       当前模为NULL: 子状态迁移至TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND
    --------------------------------------------------------------------------*/
    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_MODIFYING);
            TAF_APS_RcvAtPsCallModifyReq_MsModifying_GuMode();
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_APS_RAT_TYPE_LTE:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_MODIFYING);
            TAF_APS_RcvAtPsCallModifyReq_MsModifying_LteMode();
            break;
#endif

        case TAF_APS_RAT_TYPE_NULL:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_MODIFYING);
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND);

            /* 起保护定时器 */
            TAF_APS_StartTimer(TI_TAF_APS_MS_MODIFYING,
                               TI_TAF_APS_MS_MODIFYING_LEN,
                               ucPdpId);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvAtPsCallModifyReq_MsModifying_Init: Wrong RAT type!");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpModifyInd_MsModifying_Init
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_INIT子状态下
             收到D_PMC_SMREG_PDP_MODIFY_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月4日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvSmPdpModifyInd_MsModifying_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    /* 获取PDPId */
    ucPdpId                             = (VOS_UINT8)TAF_APS_GetCurrFsmEntityPdpId();

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType,pstMsg);

    /* 只有GSM模式下才处理此消息，其他模式不会收到此消息 */
    if (TAF_APS_RAT_TYPE_GSM == enCurrRatType)
    {
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_MS_MODIFYING);

        /* 子状态迁移至TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP);

        /* 起保护定时器 */
        TAF_APS_StartTimer(TI_TAF_APS_MS_MODIFYING,
                           TI_TAF_APS_MS_MODIFYING_LEN,
                           ucPdpId);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvSmPdpModifyInd_MsModifying_Init: Wrong RAT type!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_Suspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MMC_APS_SERVICE_STATUS_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE:处理消息失败
             VOS_TRUE:处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32  TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* 获取当前处理的PDP ID */
    ucPdpId                 = TAF_APS_GetCurrFsmEntityPdpId();

    /* 初始化, 获取消息内容 */
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq   = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* 已经激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* 上报PDP激活错误事件 */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止全流程状态机保护定时器*/
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /*------------------------------------------------------------------
           加载TAF_APS_STA_MS_DEACTIVATING状态机
           加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT
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
 函 数 名  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_Suspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_FALSE  : 处理消息失败
             VOS_TRUE   : 处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32  TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_Suspend(
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
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsModifying_Suspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_ORIG_REQ消息
 输出参数  : 无
 返 回 值  : VOS_TRUE   : 消息处理成功
             VOS_FALSE  : 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在修改该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsModifying_Suepend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ消息
 输出参数  : 无
 返 回 值  : VOS_TRUE   : 消息处理成功
             VOS_FALSE  : 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取当前处理的PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_CALL_END_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_Suspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
 输出参数  : 无
 返 回 值  : VOS_TRUE   : 消息处理成功
             VOS_FALSE  : 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvAtPsCallModifyReq_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在修改该APS实体, 修改该APS实体, 返回ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_Suspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_ANSWER_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_ANSWER_REQ消息
 输出参数  : 无
 返 回 值  : VOS_TRUE   : 消息处理成功
             VOS_FALSE  : 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvAtPsCallAnswerReq_MsModifying_Suspend(
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
 函 数 名  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_Suspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_HANGUP_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_HANGUP_REQ消息
 输出参数  : 无
 返 回 值  : VOS_TRUE   : 消息处理成功
             VOS_FALSE  : 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvAtPsCallHangupReq_MsModifying_Suspend(
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
 函 数 名  : TAF_APS_RcvSmPdpDeactivateInd_MsModifying_Suspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND子状态下
             收到D_PMC_SMREG_PDP_DEACTIV_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月3日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2012年5月18日
    作    者   : A00165503
    修改内容   : DTS2012041107552: PDP去激活未配置IPF
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstSmPdpDeactivateInd               = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* 同步PDP状态&信息给ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* 如果已经激活SNDCP, 需要向SNDCP发送去激活指示, 并等待SNDCP的响应，
       如果SNDCP没有激活, 直接上报PDP去激活成功事件 */
    if ( (VOS_TRUE == pstPdpEntity->PdpProcTrackFlag)
      && (VOS_TRUE == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* 释放SNDCP资源 */
        Aps_ReleaseSndcpResource(ucPdpId);

        pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;
    }

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤器 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_Suspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND子状态下
             收到ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 修改历史      :
  1.日    期   : 2012年06月07日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2012年08月07日
    作    者   : f00179208
    修改内容   : 问题单:DTS2012080604402, 转换消息不正确
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                               ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;

    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalPdpDeactInd;

    /* 初始化, 获取消息内容 */
    ucPdpId                     = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstLocalPdpDeactInd         = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* 同步PDP状态&信息给ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* 通知EHSM清除LTE同步的PDN信息 */
        TAF_APS_SndEhsmLocDeactNtf(ucPdpId);
    }
#endif

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstLocalPdpDeactInd->enCause));

    /* 如果已经激活SNDCP, 需要向SNDCP发送去激活指示, 并等待SNDCP的响应，
       如果SNDCP没有激活, 直接上报PDP去激活成功事件 */
    if ( (VOS_TRUE == pstPdpEntity->PdpProcTrackFlag)
      && (VOS_TRUE == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* 释放SNDCP资源 */
        Aps_ReleaseSndcpResource(ucPdpId);

        pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;
    }

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤器 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_Suspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND子状态下
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改

  3.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 修改入口消息
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT8                                               ucPdpId;
#endif

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd    = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if ( (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
      || (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType))
    {
        /* GU模下发起PDP修改请求 */
        TAF_APS_RcvAtPsCallModifyReq_MsModifying_GuMode();
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        /* LTE模下发起EPS承载修改请求 */
        TAF_APS_RcvAtPsCallModifyReq_MsModifying_LteMode();
    }
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    else if (TAF_APS_RAT_TYPE_EHRPD == pstServStaChangeInd->enRatType)
    {
        ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        TAF_APS_QuitCurrSubFsm();
    }
    else if (TAF_APS_RAT_TYPE_1X == pstServStaChangeInd->enRatType)
    {
        /* 本地去激活，退状态机 */
        ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

        /* 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* 停止流量统计 */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        /* 同步PDP状态&信息给ESM */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                 SM_ESM_PDP_OPT_DEACTIVATE);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* 通知EHSM清除LTE同步的PDN信息 */
        TAF_APS_SndEhsmLocDeactNtf(ucPdpId);

#if (FEATURE_ON == FEATURE_IPV6)

        /* 如果是缺省承载且地址类型是IPv6, 需要同步给ND Client */
        if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
          && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
        {
            TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
        }
#endif

        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpTransId)
        {
            /* 向SM发送本地去激活请求 */
            TAF_APS_SndSmPdpLocalDeactivateReq(ucPdpId);
        }

        /* 本地去激活与当前缺省承载关联的专用承载 */
        TAF_APS_SndLocalAllSecPdpDeactivateInd(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

        /* 释放资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤器 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();
    }
#endif
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_Suspend:rev msg err!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_Suspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND子状态下
             收到TI_TAF_APS_WAIT_MS_MODIFYING_CNF消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnf(
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

    /* 获取当前处理的PDP ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 已经激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState)
    {
        /* 上报PDP激活错误事件 */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止全流程状态机保护定时器*/
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /*------------------------------------------------------------------
           加载TAF_APS_STA_MS_DEACTIVATING状态机
           加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

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
 函 数 名  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
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
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnf(
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
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
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
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在修改该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取当前处理的PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_CALL_END_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在修改该APS实体, 修改该APS实体, 返回ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_ANSWER_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnf(
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
 函 数 名  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_HANGUP_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnf(
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
 函 数 名  : TAF_APS_RcvSmPdpModifyCnf_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF子状态下
             收到D_PMC_SMREG_PDP_MODIFY_CNF消息的处理
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

  2.日    期   : 2013年7月22日
    作    者   : A00165503
    修改内容   : DTS2013071905717: MODIFY流程导致的内部去激活需要上报承载去
                 激活事件
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpModifyCnf_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_MODIFY_CNF_STRU          *pstPdpModifyCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    APS_MDFCNF_PARA_ST                  stParam;

    /* 初始化, 获取消息内容 */
    pstPdpModifyCnf                     = (SMREG_PDP_MODIFY_CNF_STRU *)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType,pstMsg);

    /* 检查输入的参数 */
    ulRet = Aps_PdpMdfCnfParaCheck(pstPdpModifyCnf, &stParam);
    if (APS_PARA_VALID != ulRet)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* 发送内部消息，进行去激活操作，状态机不迁移，直接在当前状态处理 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /*检查QOS是否满足MIN*/
    if (VOS_TRUE == pstPdpModifyCnf->bitOpNegotiatedQos)
    {
        /*MDF_CNF消息中有QOS,则与MIN_QOS进行比较 */
        if (APS_PARA_VALID == Aps_CheckQosSatisify(ucPdpId, &stParam.PdpQos))
        {
            /*满足MINQOS*/
            Aps_PdpMdfCnfQosSatisfy(ucPdpId, &stParam, pstPdpModifyCnf);

#if (FEATURE_ON == FEATURE_LTE)
            /* 同步PDP信息给ESM */
            MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                    SM_ESM_PDP_OPT_MODIFY);
#endif
        }
        else
        {
            /* 上报事件 */
            TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

            /* 发送内部消息，进行去激活操作，状态机不转换，直接在当前状态处理 */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

            /* 设置去激活事件上报标识, 内部去激活后, 根据该标识决定是否上报 */
            pstPdpEntity->ucInterDeactNotifyFlg = VOS_TRUE;

            return VOS_TRUE;
        }
    }
    else
    {
        /*若SM返回的MDF_CNF消息中无 QOS, 则表示UE申请的QOS被接受了,或者没有修改QOS*/
        Aps_PdpMdfCnfQosSatisfy(ucPdpId, &stParam, pstPdpModifyCnf);

#if (FEATURE_ON == FEATURE_LTE)

        /* 同步PDP信息给ESM */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                SM_ESM_PDP_OPT_MODIFY);
#endif
    }

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_GSM:

            /* 子状态迁移至TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP);
            break;

        case TAF_APS_RAT_TYPE_WCDMA:

            /* 停止全流程状态机保护定时器*/
            TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

            /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvSmPdpModifyCnf_MsModifying_WaitSmModifyCnf: Wrong RAT type!");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF子状态下
             收到D_PMC_SMREG_PDP_MODIFY_REJ消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_MODIFY_REJ_STRU          *pstSmMsg;

    /* 初始化, 获取消息内容 */
    pstSmMsg                            = (SMREG_PDP_MODIFY_REJ_STRU *)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_APS_MapSmCause(pstSmMsg->enCause));

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF子状态下
             收到D_PMC_SMREG_PDP_DEACTIV_IND消息的处理
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

  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改

  3.日    期   : 2012年5月18日
    作    者   : A00165503
    修改内容   : DTS2012041107552: PDP去激活未配置IPF

  4.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstSmPdpDeactivateInd               = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* 同步PDP状态&信息给ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* 如果已经激活SNDCP, 需要向SNDCP发送去激活指示, 并等待SNDCP的响应，
       如果SNDCP没有激活, 直接上报PDP去激活成功事件 */
    if ( (VOS_TRUE == pstPdpEntity->PdpProcTrackFlag)
      && (VOS_TRUE == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* 释放SNDCP资源 */
        Aps_ReleaseSndcpResource(ucPdpId);

        pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;
    }

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤器 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF子状态下
             收到ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
 修改历史      :
  1.日    期   : 2012年06月07日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2012年08月07日
    作    者   : f00179208
    修改内容   : 问题单:DTS2012080604402, 转换消息不正确

  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                               ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;

    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalPdpDeactInd;

    /* 初始化, 获取消息内容 */
    ucPdpId                     = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstLocalPdpDeactInd         = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* 同步PDP状态&信息给ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstLocalPdpDeactInd->enCause));

    /* 如果已经激活SNDCP, 需要向SNDCP发送去激活指示, 并等待SNDCP的响应，
       如果SNDCP没有激活, 直接上报PDP去激活成功事件 */
    if ( (VOS_TRUE == pstPdpEntity->PdpProcTrackFlag)
      && (VOS_TRUE == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot) )
    {
        /* 释放SNDCP资源 */
        Aps_ReleaseSndcpResource(ucPdpId);

        pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;
    }

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤器 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改

  3.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 修改入口消息
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* 处理挂起指示 */
    if (TAF_APS_RAT_TYPE_NULL == pstServStaChangeInd->enRatType)
    {
        /* 子状态迁移至TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND);
    }
    else
    {
        /* 此时到L模应该是一条异常消息 */
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnf: Wrong RAT Type!");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF状态下收到
             ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月30日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取Pdp ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvRabmLocalPdpDeactReq_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_HANGUP_REQ消息的处理
 输入参数  : ulEventType:消息类型
             pstMsg     : ID_MSG_TAF_PS_CALL_HANGUP_REQ消息
 输出参数  : 无
 返 回 值  : VOS_TRUE   : 消息处理成功
             VOS_FALSE  : 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月29日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32  TAF_APS_RcvRabmLocalPdpDeactReq_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取PDP ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_RAB_SETUP_FAILURE);

    /* 发送内部消息，进行去激活操作，状态机不迁移，直接在当前状态处理 */
    TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF子状态下
             收到TI_TAF_APS_WAIT_MS_MODIFYING_CNF消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* 获取PDP ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq               = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* 已经激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if ( TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState )
    {
        /* 上报PDP激活错误事件 */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止全流程状态机保护定时器*/
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /*------------------------------------------------------------------
           加载TAF_APS_STA_MS_DEACTIVATING状态机
           加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中处理
           ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
           子状态迁移至TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
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
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnfSuspend(
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
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
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
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSmModifyCnfSuspend(
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
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取当前处理的PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
       子状态迁移至TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

   return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在修改该APS实体, 修改该APS实体, 返回ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_ANSWER_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnfSuspend(
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
 函 数 名  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_HANGUP_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnfSuspend(
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
 函 数 名  : TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND子状态下
             收到D_PMC_SMREG_PDP_MODIFY_REJ消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_MODIFY_REJ_STRU          *pstSmMsg;

    /* 初始化, 获取消息内容 */
    pstSmMsg                            = (SMREG_PDP_MODIFY_REJ_STRU *)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_APS_MapSmCause(pstSmMsg->enCause));

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND子状态下
             收到D_PMC_SMREG_PDP_DEACTIV_IND消息的处理
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

  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改

  3.日    期   : 2012年5月18日
    作    者   : A00165503
    修改内容   : DTS2012041107552: PDP去激活未配置IPF

  4.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;

    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstSmPdpDeactivateInd               = (SMREG_PDP_DEACTIVATE_IND_STRU*)pstMsg;

    /* ID_PMC_SMREG_PDP_DEACTIV_IND消息处理说明,在状态机中不需要对TEARDOWN
       再进行判断处理,APS在收到ID_PMC_SMREG_PDP_DEACTIV_IND消息首先进行预处
       理,如果消息中带有TEARDOWN,预处理中找出都有哪些PDP待去激活,然后,将
       ID_PMC_SMREG_PDP_DEACTIV_IND分发到相应的实体状态中,所以,在状态机中不再
       对ID_PMC_SMREG_PDP_DEACTIV_IND中的TEARDOWN再作处理 */

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

#if (FEATURE_ON == FEATURE_LTE)

    /* 同步PDP状态&信息给ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* 如果SNDCP已经激活, 则去激活SNDCP */
    if ( (VOS_TRUE == pstPdpEntity->PdpProcTrackFlag)
      && (VOS_TRUE == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot))
    {
        /* 释放SNDCP资源 */
        Aps_ReleaseSndcpResource(ucPdpId);

        pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;
    }

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤器 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND子状态下
             收到ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月07日
    作    者   : f00179208
    修改内容   : 新生成函数
  2.日    期   : 2012年08月07日
    作    者   : f00179208
    修改内容   : 问题单:DTS2012080604402, 转换消息不正确
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                               ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;

    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalPdpDeactInd;

    ucPdpId                     = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstLocalPdpDeactInd         = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;

    /* 停止全流程状态机保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

#if (FEATURE_ON == FEATURE_LTE)

    /* 同步PDP状态&信息给ESM */
    MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                            SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* 如果SNDCP已经激活, 则去激活SNDCP */
    if ( (VOS_TRUE == pstPdpEntity->PdpProcTrackFlag)
      && (VOS_TRUE == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot))
    {
        /* 释放SNDCP资源 */
        Aps_ReleaseSndcpResource(ucPdpId);

        pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;
    }

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstLocalPdpDeactInd->enCause));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤器 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : 新生成函数

  3.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 修改入口消息
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                                               ucPdpId;
#endif

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if ( (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
      || (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType))
    {
        /*GU模下 ,不需要处理,继续等SM的回复,状态回到
          TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF
        */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF);
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

        /*向SM发送abort消息*/
        TAF_APS_SndSmPdpAbortReq(ucPdpId);

        /* LTE模下发起EPS承载修改请求 */
        TAF_APS_RcvAtPsCallModifyReq_MsModifying_LteMode();
    }
#endif
    else
    {
        ;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND子状态下
             收到TI_TAF_APS_WAIT_MS_MODIFYING_CNF消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRsp
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* 获取PDP ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq               = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* 已经激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState )
    {
        /* 上报PDP激活错误事件 */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止全流程状态机保护定时器*/
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /*------------------------------------------------------------------
           加载TAF_APS_STA_MS_DEACTIVATING状态机
           加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中处理
           ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRsp
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
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
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRsp(
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
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRsp
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
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
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRsp(
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
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRsp
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取当前处理的PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_CALL_END_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRsp
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在修改该APS实体, 修改该APS实体, 返回ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRsp
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP子状态下
             收到ID_MSG_TAF_PS_CALL_ANSWER_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS域MT呼叫流程, 方案未确定, 目前直接返回ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRsp
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP子状态下
             收到ID_MSG_TAF_PS_CALL_HANGUP_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRsp(
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
 函 数 名  : TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRsp
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP子状态下
             收到APS_SN_MDF_RSP_MSG_TYPE消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_MODIFY_RSP_ST            *pstSnModifyRsp;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;

    /* 初始化, 获取消息内容 */
    pstSnModifyRsp                      = &((APS_SNDCP_MODIFY_RSP_MSG*)pstMsg)->ApsSnMdfRsp;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg                         = TAF_APS_GetCurrSubFsmMsgAddr();

    /* 根据触发流程的入口消息判断回复消息类型 */
    switch (pstEntryMsg->ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_CNF):
            /* 如果是用户发起的MODIFY，上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF事件 */
            TAF_APS_SndPdpModifyCnf(ucPdpId);
            break;

        case TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_IND):

            /* 如果是网络发起的MODIFY，上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND事件 */
            TAF_APS_SndPdpModifyInd(ucPdpId);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRsp: invalid message!");
            return VOS_TRUE;
    }

    /* 设置RABM的传输模式 */
    Aps_SnMsgModSnMdfRsp(pstSnModifyRsp);

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* 主状态迁移至TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    /* 退出子状态机 */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRsp
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP子状态下
             收到APS_SN_STATUS_REQ_MSG_TYPE消息的处理
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

  2.日    期   : 2014年8月4日
    作    者   : A00165503
    修改内容   : DTS2014080401792: LLC确认模式下, 处理SN_STATUS_REQ消息优化
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq;

    /* 初始化, 获取消息内容 */
    pstSnStatusReq                      = &((APS_SNDCP_STATUS_REQ_MSG*)pstMsg)->ApsSnStatusReq;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 对SAPI进行检查 */
    ulRet = Aps_SnMsgModSnStatusReqParaCheck(pstSnStatusReq);
    if ( APS_PARA_VALID != ulRet )
    {
        MN_WARN_LOG("TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRsp:Aps_SnMsgModSnStatusReqParaCheck ERR ");
        return VOS_TRUE;
    }

    /* 检查当前APS实体中的SAPI是否满足SN STATUS消息中指定的SAPI，满足时转入去激活 */
    ulRet = TAF_APS_ValidatePdpForSnStatusReq(ucPdpId, pstSnStatusReq);
    if (VOS_TRUE == ulRet)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF事件 */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* 发送内部消息，进行去激活操作，状态机不迁移，直接在当前状态处理 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRsp
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP子状态下
             收到ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月2日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取Pdp ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRsp
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改

  3.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 修改入口消息
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* 处理挂起指示 */
    if (TAF_APS_RAT_TYPE_NULL == pstServStaChangeInd->enRatType)
    {
        /* 子状态迁移至TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND);
    }
    else
    {
        /* 此时到L模应该是一条异常消息 */
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRsp: Wrong RAT Type!");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRsp
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP子状态下
             收到TI_TAF_APS_WAIT_MS_MODIFYING_CNF消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSetPdpCtxStateReq_MsModifying_WaitSndcpModifyRspSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstPdpContextStateReq;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    pstAppMsg             = (TAF_PS_MSG_STRU*)pstMsg;
    pstPdpContextStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();

    /* 已经激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if ( TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState )
    {
        /* 上报PDP激活错误事件 */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止全流程状态机保护定时器*/
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /*------------------------------------------------------------------
           加载TAF_APS_STA_MS_DEACTIVATING状态机
           加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

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
 函 数 名  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRspSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
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
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRspSuspend(
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
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRspSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
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
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRspSuspend(
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
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl), pstCallOrigReq->stDialParaInfo.ucCid, TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRspSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取当前处理的PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRspSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 异常消息, 直接向用户返回OK */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRspSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_ANSWER_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRspSuspend(
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
 函 数 名  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRspSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_HANGUP_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRspSuspend(
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
 函 数 名  : TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRspSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND子状态下
             收到APS_SN_MDF_RSP_MSG_TYPE消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2014年10月28日
    作    者   : j00174725
    修改内容   : DTS2014102204179
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_MODIFY_RSP_ST            *pstSnModifyRsp;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;

    /* 初始化, 获取消息内容 */
    pstSnModifyRsp                      = &((APS_SNDCP_MODIFY_RSP_MSG*)pstMsg)->ApsSnMdfRsp;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg                         = TAF_APS_GetCurrSubFsmMsgAddr();

    /* 根据触发流程的入口消息判断回复消息类型 */
    switch (pstEntryMsg->ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_CNF):
            /* 如果是用户发起的MODIFY，上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF事件 */
            TAF_APS_SndPdpModifyCnf(ucPdpId);
            break;

        case TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_IND):

            /* 如果是网络发起的MODIFY，上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND事件 */
            TAF_APS_SndPdpModifyInd(ucPdpId);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRsp: invalid message!");
            return VOS_TRUE;
    }

    /* 设置RABM的传输模式 */
    Aps_SnMsgModSnMdfRsp(pstSnModifyRsp);

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* 主状态迁移至TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    /* 退出子状态机 */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRspSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND子状态下
             收到APS_SN_STATUS_REQ_MSG_TYPE消息的处理
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

  2.日    期   : 2014年8月4日
    作    者   : A00165503
    修改内容   : DTS2014080401792: LLC确认模式下, 处理SN_STATUS_REQ消息优化
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq;

    pstSnStatusReq                      = &((APS_SNDCP_STATUS_REQ_MSG*)pstMsg)->ApsSnStatusReq;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    ulRet = Aps_SnMsgModSnStatusReqParaCheck(pstSnStatusReq);
    if (APS_PARA_VALID != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRspSuspend: Check para failed! ");

        return VOS_TRUE;
    }

    ulRet = TAF_APS_ValidatePdpForSnStatusReq(ucPdpId, pstSnStatusReq);
    if (VOS_TRUE == ulRet)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF事件 */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* 发送内部消息，进行去激活操作，状态机不迁移，直接在当前状态处理 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRspSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改

  3.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 修改入口消息
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg         = VOS_NULL_PTR;
    VOS_UINT8                                               ucPdpId;

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg         = TAF_APS_GetCurrSubFsmMsgAddr();

    if (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
    {
        /* GU模下 ,不需要处理,继续等SNDCP的回复,状态回到
           TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP
        */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP);
    }
    else if ( (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType)
#if (FEATURE_ON == FEATURE_LTE)
           || (TAF_APS_RAT_TYPE_LTE   == pstServStaChangeInd->enRatType)
#endif
    )
    {
        /* 释放SNDCP资源 */
        Aps_ReleaseSndcpResource(ucPdpId);

        /* 根据触发流程的入口消息判断回复消息类型 */
        switch (pstEntryMsg->ulEventType)
        {
            case TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_CNF):

                /* 如果是用户发起的MODIFY，上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF事件 */
                TAF_APS_SndPdpModifyCnf(ucPdpId);
                break;

            case TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_IND):

                /* 如果是网络发起的MODIFY，上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND事件 */
                TAF_APS_SndPdpModifyInd(ucPdpId);
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRspSuspend: invalid message!");
                break;
        }

        /* 停止全流程状态机保护定时器*/
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /* 主状态迁移至TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvMmcServiceStatusInd_MsModifying_WaitSndcpModifyRspSuspend:rev msg err!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRspSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND状态下收到
             ID_APS_APS_INTERNAL_PDP_DEACTIVATE_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月30日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取Pdp ID */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRspSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND子状态下
             收到TI_TAF_APS_WAIT_MS_MODIFYING_CNF消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRspSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_GuMode
 功能描述  : MODIFYING主状态下收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallModifyReq_MsModifying_GuMode(VOS_VOID)
{
    VOS_UINT8                           ucErrCode;
    VOS_UINT8                           ucPdpId;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    ucErrCode                           = TAF_ERR_NO_ERROR;
    pstEntryMsg                         = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg                           = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 修改PS CALL参数: QOS等 */
    Aps_PsCallModify(pstCallModifyReq->stCtrl.usClientId,
                     pstCallModifyReq->stCtrl.ucOpId,
                     ucPdpId,
                     &ucErrCode);
    if (TAF_ERR_NO_ERROR != ucErrCode)
    {
        /* 返回PDP操作结果 */
        TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                                TAF_PS_CAUSE_UNKNOWN);

        /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* 返回PDP操作结果 */
        TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                                TAF_PS_CAUSE_SUCCESS);

        /* 子状态迁移至TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF);

        /* 由于可能GU和LTE间反复多次切换，因此有可能定时器之前已经启动，此处不能
           重启，因此只有定时器未启动时才启动 */
        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_MODIFYING,
                                               ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            /* 起保护定时器 */
            TAF_APS_StartTimer(TI_TAF_APS_MS_MODIFYING,
                               TI_TAF_APS_MS_MODIFYING_LEN,
                               ucPdpId);
        }
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitEsmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitEsmModifyCnf(
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

    /* 已经激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if (TAF_CGACT_ACT == pstPdpContextStateReq->stCidListStateInfo.ucState )
    {
        /* 上报PDP激活错误事件 */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstPdpContextStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING,
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
 函 数 名  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitEsmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
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
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在修改该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitEsmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
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
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在修改该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                          pstCallOrigReq->stDialParaInfo.ucCid,
                          TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitEsmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取当前处理的PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitEsmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 异常消息, 直接向用户返回ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitEsmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_ANSWER_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitEsmModifyCnf(
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
 函 数 名  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitEsmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_HANGUP_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitEsmModifyCnf(
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
 函 数 名  : TAF_APS_RcvEsmPdpModifyCnfRst_MsModifying_WaitEsmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF子状态下
             收到ID_APP_ESM_PDP_MODIFY_CNF消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpModifyCnf_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_MODIFY_CNF_STRU        *pstEsmPdpModifyCnf;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /* 初始化, 获取消息内容 */
    pstEsmPdpModifyCnf                  = (APP_ESM_PDP_MODIFY_CNF_STRU*)pstMsg;

    if (APP_SUCCESS == pstEsmPdpModifyCnf->ulRslt)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF事件 */
        TAF_APS_SndPdpModifyCnf(ucPdpId);
    }
    else
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_APS_MapEsmCause(pstEsmPdpModifyCnf->ulRslt));
    }

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改

  3.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 修改入口消息
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;

    /* 初始化, 获取消息内容 */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if (TAF_APS_RAT_TYPE_NULL == pstServStaChangeInd->enRatType)
    {
        /* 子状态迁移至TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnf: Wrong RAT Type!");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitEsmModifyCnf(
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF主状态下收到ID_ESM_SM_EPS_BEARER_INFO_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitEsmModifyCnf(
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
    if (SM_ESM_PDP_OPT_DEACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptDeactivate(pstPdpEntity, pstBearerInfo);
    }
    else if (SM_ESM_PDP_OPT_MODIFY == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptModify(pstPdpEntity, pstBearerInfo);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitL4aModifyCnf: Wrong option.");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitEsmModifyCnf
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF子状态下
             收到TI_TAF_APS_WAIT_MS_MODIFYING_CNF消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitEsmModifyCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitEsmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxStateReq                = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 已经激活该APS实体, 再激活该APS实体所用的CID,上报ERROR事件,
       否则,发起去激活状态进行迁移 */
    if (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState)
    {
        /* 上报PDP激活错误事件 */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpCtxStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
    }
    else
    {
        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING,
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
 函 数 名  : TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitEsmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
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
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在修改该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                             TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitEsmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
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
  2.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 正在修改该APS实体, 激活该APS实体所用的CID, 返回ERROR */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl), pstCallOrigReq->stDialParaInfo.ucCid, TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitEsmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取当前处理的PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    /*------------------------------------------------------------------
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_END_REQ消息
       子状态迁移至TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitEsmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 异常消息, 直接向用户返回ERROR */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl), TAF_PS_CAUSE_CID_INVALID);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitEsmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_ANSWER_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitEsmModifyCnfSuspend(
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
 函 数 名  : TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitEsmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_HANGUP_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitEsmModifyCnfSuspend(
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
 函 数 名  : TAF_APS_RcvEsmPdpModifyCnf_MsModifying_WaitEsmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND子状态下
             收到ID_APP_ESM_PDP_MODIFY_CNF消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpModifyCnf_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_MODIFY_CNF_STRU        *pstEsmPdpModifyCnf;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    pstEsmPdpModifyCnf                  = (APP_ESM_PDP_MODIFY_CNF_STRU*)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止全流程状态机保护定时器*/
    TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

    if (APP_SUCCESS == pstEsmPdpModifyCnf->ulRslt)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF事件 */
        TAF_APS_SndPdpModifyCnf(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* 如果错误码不是异系统, 则该修改流程终止 */
        if (APP_ERR_SM_SUSPENDED != pstEsmPdpModifyCnf->ulRslt)
        {
            /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
            TAF_APS_SndPdpModifyRej(ucPdpId, TAF_APS_MapEsmCause(pstEsmPdpModifyCnf->ulRslt));

            /* 停止全流程状态机保护定时器*/
            TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

            /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出层2状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();
        }
        else
        {
            /* 子状态迁移至TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE                   - 消息处理成功
             VOS_FALSE                  - 消息处理失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月2日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数

  2.日    期   : 2015年5月25日
    作    者   : g00261581
    修改内容   : 修改入口消息

  3.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project
*****************************************************************************/
VOS_UINT32  TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT8                                               ucPdpId;
#endif
    /* 初始化, 获取消息内容 */
    pstServStaChangeInd    = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    if ( (TAF_APS_RAT_TYPE_GSM   == pstServStaChangeInd->enRatType)
      || (TAF_APS_RAT_TYPE_WCDMA == pstServStaChangeInd->enRatType))
    {
        /* 在GU下重新发起MODIFY */
        TAF_APS_RcvAtPsCallModifyReq_MsModifying_GuMode();
    }
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        /*L模下 ,不需要处理,继续等L4A的回复,状态回到
          TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF
        */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF);
    }
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    else if (TAF_APS_RAT_TYPE_EHRPD == pstServStaChangeInd->enRatType)
    {
        ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

        TAF_APS_StopTimer(TI_TAF_APS_MS_MODIFYING, ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        TAF_APS_QuitCurrSubFsm();
    }
    else if (TAF_APS_RAT_TYPE_1X == pstServStaChangeInd->enRatType)
    {
        /* 1X模式下，本地去激活, hrpd下由EHSM进行本地去激活 */
        ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

        /* 停止定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_MS_DEACTIVATING, ucPdpId);

        /* 停止流量统计 */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        /* 同步PDP状态&信息给ESM */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                 SM_ESM_PDP_OPT_DEACTIVATE);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
        TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* 通知EHSM清除LTE同步的PDN信息 */
        TAF_APS_SndEhsmLocDeactNtf(ucPdpId);

#if (FEATURE_ON == FEATURE_IPV6)

        /* 如果是缺省承载且地址类型是IPv6, 需要同步给ND Client */
        if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
          && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
        {
            TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
        }
#endif

        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpTransId)
        {
            /* 向SM发送本地去激活请求 */
            TAF_APS_SndSmPdpLocalDeactivateReq(ucPdpId);
        }

        /* 本地去激活与当前缺省承载关联的专用承载 */
        TAF_APS_SndLocalAllSecPdpDeactivateInd(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);

        /* 释放资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤器 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();
    }
#endif
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitL4aModifyCnfSuspend:rev msg err!");
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitEsmModifyCnfSuspend(
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND主状态下收到ID_ESM_SM_EPS_BEARER_INFO_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitEsmModifyCnfSuspend(
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
    if (SM_ESM_PDP_OPT_DEACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptDeactivate(pstPdpEntity, pstBearerInfo);
    }
    else if (SM_ESM_PDP_OPT_MODIFY == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptModify(pstPdpEntity, pstBearerInfo);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitL4aModifyCnfSuspend: Wrong option.");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitEsmModifyCnfSuspend
 功能描述  : TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF_SUSPEND子状态下
             收到TI_TAF_APS_WAIT_MS_MODIFYING_CNF消息的处理
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
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2012年8月22日
    作    者   : Y00213812
    修改内容   : 修改PS域错误码上报
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitEsmModifyCnfSuspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ事件 */
    TAF_APS_SndPdpModifyRej(ucPdpId, TAF_PS_CAUSE_SM_MAX_TIME_OUT);

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallModifyReq_MsModifying_LteMode
 功能描述  : MODIFYING主状态下收到ID_MSG_TAF_PS_CALL_MODIFY_REQ消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月17日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2011年12月29日
    作    者   : z60575
    修改内容   : PS融合检视意见修改
  3.日    期   : 2015年12月7日
    作    者   : w00316404
    修改内容   : Split L4A Project
*****************************************************************************/
VOS_VOID TAF_APS_RcvAtPsCallModifyReq_MsModifying_LteMode(VOS_VOID)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;

    /* 初始化, 获取消息内容 */
    pstEntryMsg                         = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg                           = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 向ESM发送modify请求 */
    TAF_APS_SndEsmPdpModifyReq(pstCallModifyReq);

    /* 返回PDP操作结果 */
    TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                            TAF_PS_CAUSE_SUCCESS);

    /* 子状态迁移至TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_MS_MODIFYING_SUBSTA_WAIT_ESM_MODIFY_CNF);

    /* 由于可能GU和LTE间反复多次切换，因此有可能定时器之前已经启动，此处不能
       重启，因此只有定时器未启动时才启动 */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_MS_MODIFYING,
                                           ucPdpId);
    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        /* 起保护定时器 */
        TAF_APS_StartTimer(TI_TAF_APS_MS_MODIFYING,
                           TI_TAF_APS_MS_MODIFYING_LEN,
                           ucPdpId);
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

