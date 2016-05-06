/******************************************************************************

                   版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmCdataHandOff.c　
  版 本 号   : 初稿
  作    者   : y00314741
  生成日期   : 2015年04月07日
  最近修改   :
  功能描述   :
  函数列表   :

  修改历史   :
  1.日    期   : 2015年04月07日
    作    者   : y00314741
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafApsApi.h"
#include "Taf_Aps.h"
#include "TafSdcLib.h"
#include "TafApsCtx.h"
#include "TafMmaInterface.h"
#include "TafApsSndXcc.h"
#include "TafApsSndPpp.h"
#include "TafApsSndAds.h"
#include "TafApsSndCds.h"

#include "taf_aps_ppp_pif.h"
#include "TafApsComFunc.h"
#include "TafApsTimerMgmt.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsSndInternalMsg.h"
#include "TafApsComFunc.h"
#include "TafSdcCtx.h"
#include "MnApsComm.h"
#include "TafLog.h"
#include "TafApsDsFlowStats.h"

#include "TafApsFsmCdataEstingTbl.h"
#include "TafApsFsmCdataEsting.h"
#include "TafApsFsmCdataDiscingTbl.h"
#include "TafApsFsmCdataHandOff.h"
#include "TafApsFsmCdataHandOffTbl.h"
#include "TafApsSndRlp.h"
#include "TafApsSndCds.h"
#include "TafApsProcIpFilter.h"
#include "hsm_aps_pif.h"
#include "TafApsSndHsm.h"
#include "xcc_aps_pif.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_HANDOFF_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

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
 函 数 名  : TAF_APS_RcvPsInter1XHrpdHandOff_CdataHandOff_Init
 功能描述  : CDATA HANDOFF INIT子状态下收到ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvPsInter1XToHrpdHandOff_CdataHandOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId  = TAF_APS_GetCurrFsmEntityPdpId();

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 起保数据服务切换护定时器 */
    TAF_APS_StartTimer(TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER,
                       TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER_LEN,
                       ucPdpId);

    /* 发送模式切换请求给HSM */
    TAF_APS_SndHsm1XToHrpdHandOffReq(ucPdpId);

    /* 主状态TAF_APS_STA_CDATA_HANDOFF */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_HANDOFF);

    /* 迁移TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF子状态 */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmHandOffCnf_CdataHandOff_WaitHsmHandOffCnf
 功能描述  : TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF子状态下
             收到ID_HSM_APS_1X_TO_HRPD_HANDOFF_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月24日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmHandOffCnf_CdataHandOff_WaitHsmHandOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_1X_TO_HRPD_HANDOFF_CNF_STRU  *pstApsHandOffCnf;
    VOS_UINT8                             ucPdpId;

    /* 初始化 */
    pstApsHandOffCnf  = (HSM_APS_1X_TO_HRPD_HANDOFF_CNF_STRU *)pstMsg;
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止模式切换定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER, ucPdpId);

    /* 数据服务切换成功 */
    if (HSM_APS_CAUSE_SUCCESS == pstApsHandOffCnf->ulCause)
    {
        /* 更新建立数据服务的接入技术 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        /* 通知外部模块当前的PS服务所在的模式 */
        TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_HRPD);
    }

    /* 主状态迁移至TAF_APS_STA_DORMANT */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_DORMANT);

    /* 退出子状态状态机 */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTi1XToHrpdHandOffExpired_CdataHandOff_WaitHsmHandOffCnf
 功能描述  : TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF子状态下
             收到TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月24日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTi1XToHrpdHandOffExpired_CdataHandOff_WaitHsmHandOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 主状态迁移至TAF_APS_STA_DORMANT */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_DORMANT);

    /* 退出子状态状态机 */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataEHandOff_WaitHsmHandOffCnf
 功能描述  : TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataHandOff_WaitHsmHandOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;

    /* 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* 停止保数据服务切换保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER, ucPdpId);

    //To do:暂时按照此流程做，后面参考标杆来做

    /* 如果PPP已激活，通知PPP去激活 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        TAF_APS_SndPppDeactInd(ucPdpId);
    }


    /* 上报去激活的事件 */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SUCCESS);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* 退出子状态状态机 */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccIncomingCallInd_CdataEHandOff_WaitHsmHandOffCnf
 功能描述  : TAF_APS_RcvXccIncomingCallInd_CdataEHandOff_WaitHsmHandOffCnf子状态下
             收到ID_XCC_APS_INCOMING_CALL_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月21日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_CdataHandOff_WaitHsmHandOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止保数据服务切换保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER, ucPdpId);

    /*-------------------------------------------------------
    加载TAF_APS_FSM_CDATA_ESTING状态机
    加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

    在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
    ID_XCC_APS_INCOMING_CALL_IND消息
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : TAF_APS_Proc1xToHrpdHandOff
 功能描述  : TAF Aps Proc 1X to Hrpd Hand Off
 输入参数  : VOS_UINT8                           ucPdpId
             VOS_UINT8                           ucIsNewSession
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月26日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_Proc1xToHrpdHandOff(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucIsNewSession
)
{
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);
    }

    /* 从1X切换到HRPD */
    if (VOS_TRUE == ucIsNewSession)
    {
        /* 更新当前建立数据服务的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        /* 通知外部模块当前的PS服务所在的模式 */
        TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_HRPD);
    }
    else
    {
        /* 发送内部1X到HRPD切换请求消息 */
        TAF_APS_SndInter1XToHrpdHandOffReq(ucPdpId);
    }

    return;
}


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


