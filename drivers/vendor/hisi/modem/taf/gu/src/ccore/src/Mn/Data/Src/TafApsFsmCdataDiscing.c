/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmCdataDiscing.c
  版 本 号   : 初稿
  作    者   : h00246512
  生成日期   : 2014年10月14日
  最近修改   :
  功能描述   : CdataDiscing状态机处理函数，APS模块处理断开data call操作
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月14日
    作    者   : h00246512
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafApsFsmCdataDiscing.h"
#include  "TafApsFsmCdataDiscingTbl.h"
#include  "Taf_Aps.h"
#include  "TafLog.h"
#include  "TafApsCtx.h"
#include  "xcc_taf_pif.h"
#include  "MnApsComm.h"
#include  "TafApsSndInternalMsg.h"
#include  "TafApsSndXcc.h"
#include  "TafApsSndPpp.h"
#include  "xcc_aps_pif.h"
#include  "TafApsFsmMainTbl.h"
#include  "TafApsComFunc.h"
#include  "TafApsSndCds.h"
#include  "taf_aps_ppp_pif.h"
#include  "TafApsFsmCdataEstingTbl.h"
#include  "TafApsProcIpFilter.h"
#include  "TafApsSndHsm.h"
#include  "TafApsProcEpdszid.h"
#include  "TafApsSndEhsm.h"
#include  "TafApsSndNd.h"
#include  "TafApsSndDhcp.h"

#include "cnas_cttf_hrpd_pa_pif.h"

#include "TafSdcLib.h"
#include "TafApsSndRlp.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_DISCING_C


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_APS_ProcCdataDisc_CdataDiscing_Init
 功能描述  : CDMA相应模下去断空口链路
 输入参数  : TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月17日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_ProcCdataDisc_CdataDiscing_Init(
    TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 设置主状态 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_DISCING);

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_DISCONNECTING);

    switch (TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        case TAF_APS_RAT_TYPE_HRPD:
        

            /* 向HSM发送消息ID_APS_HSM_DISC_REQ */
            TAF_APS_SndHsmDiscReq(ucPdpId);

            /* 状态迁移到TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF);

            break;

        case TAF_APS_RAT_TYPE_1X:
            /* 向XCC发送消息ID_APS_XCC_HANGUP_DATA_CALL_REQ */
            TAF_APS_SndXccHangUpDataCallReq(pstPdpEntity->stCdataInfo.ucCallId,
                                            enEndReason);

            /* 状态迁移到TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF);

            break;

        case TAF_APS_RAT_TYPE_EHRPD:
            /* EHRPD模式下不主动去注册上行数据的回调函数 */

            /* 向EHSM发送消息ID_APS_EHSM_PDN_DEACTIVATE_REQ */
            TAF_APS_SndEhsmPdnDeactReq(ucPdpId);
            TAF_APS_SndDhcpDeactInd(ucPdpId);

#if (FEATURE_ON == FEATURE_IPV6)
            /* 如果是缺省承载且地址类型是IPv6, 需要同步给ND Client */
            if ((TAF_APS_CheckPrimaryPdp(ucPdpId))
             && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
            {
                TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
            }
#endif

            /* 状态迁移到TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF);

            break;

        default:
            /* 迁去激活Suspend状态 */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND);

            break;
    }

    /* 启动定时器TI_TAF_APS_CDATA_DISCING */
    TAF_APS_StartTimer(TI_TAF_APS_CDATA_DISCING,
                       TI_TAF_APS_CDATA_DISCING_LEN,
                       ucPdpId);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEnterDormantInd_CdataDiscing_Init
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_INIT状态下
             收到ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPsCallEnterDormantInd_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 如果当前是1X模式，需要原因值，如果是HRPD则不需要 */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_NORMAL_RELEASE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvApsInternEndCdmaCallReq_CdataDiscing_Init
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_INIT状态下
             收到ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvApsInternEndCdmaCallReq_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;
    VOS_UINT8                           ucPdpId;
    VOS_UINT32                          ulPppDeactTiLen;

    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    enPppState      = TAF_APS_GetPdpEntPppState(ucPdpId);
    ulPppDeactTiLen = TAF_APS_GetCdataPppDeactTimerLen();

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 设置主状态 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_DISCING);

    /* 网络模式，当前的PPP状态是激活的，或者在激活过程中则先断开PPP */
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == enPppState)
    {
        if (TAF_APS_CDATA_AIR_LINK_CONNECTED == TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
        {
            /* 更新PS状态 */
            TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_DEACTIVATING);

            /* 向PPP发送消息ID_APS_PPP_DEACT_REQ */
            TAF_APS_SndPppDeactReq(ucPdpId);

            /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_DEACTIVATING */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);

            /* 状态迁移到TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF);

            /* 启动定时器TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                               ulPppDeactTiLen,
                               ucPdpId);

            return VOS_TRUE;
        }
    }

    /* 如果当前是1X模式，需要原因值，如果是HRPD则不需要 */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataDiscing_Init
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_INIT状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理


 修改历史      :
  1.日    期   : 2014年10月21日
    作    者   : h00246512
    修改内容   : 新生成函数

  2.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : 修改用户去激活的入口消息处理逻辑
*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;
    VOS_UINT8                           ucPdpId;
    VOS_UINT32                          ulPppDeactTiLen;

    /* 获取消息内容 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    ulPppDeactTiLen = TAF_APS_GetCdataPppDeactTimerLen();

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_DEACTIVATING);

    /* Dormant状态下去激活，首先需要先将链路建成功 */
    if (TAF_APS_STA_DORMANT == TAF_APS_GetPdpIdMainFsmState(ucPdpId))
    {
        switch (TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            case TAF_APS_RAT_TYPE_HRPD:

                TAF_APS_ProcHrpdOrigDataCall_CdataDiscing_HybridMode(ucPdpId, VOS_FALSE);

                break;

            case TAF_APS_RAT_TYPE_1X:

                TAF_APS_Proc1xOrigDataCall_CdataDiscing_1XMode(VOS_TRUE, VOS_TRUE, VOS_FALSE);

                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvPsCallEndReq_CdataDiscing_Init: Wrong RAT type!");
                break;
        }

        /* Dormant状态下去激活，先尝试建链 */
        TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTING);

        /* 设置主状态 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_DISCING);

        /* Dormant状态下去激活需要先建链，建链的目的是做PPP去激活协商，启动PPP去激活协商的总定时器保护 */
        /* 启动定时器TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF */
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                           ulPppDeactTiLen,
                           ucPdpId);

        return VOS_TRUE;
    }

    /* 网络模式，当前的PPP状态是激活的，或者在激活过程中则先断开PPP */
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);
    if ((TAF_APS_CDATA_PPP_STATE_ACTIVE     == enPppState)
     || (TAF_APS_CDATA_PPP_STATE_ACTIVATING == enPppState))
    {
        if (TAF_APS_CDATA_AIR_LINK_CONNECTED == TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
        {
            if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId))
            {
                TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);
            }

            /* 设置主状态 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_DISCING);

            /* 向PPP发送消息ID_APS_PPP_DEACT_REQ */
            TAF_APS_SndPppDeactReq(ucPdpId);

            /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_DEACTIVATING */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);

            /* 状态迁移到TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF);

            /* 启动定时器TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                               ulPppDeactTiLen,
                               ucPdpId);

            return VOS_TRUE;
        }
    }

    /* 空口链路断链流程 */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactNtf_CdataDiscing_Init
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_INIT状态下
             收到ID_PPP_APS_DEACT_NOTIFY消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理


 修改历史      :
  1.日    期   : 2014年10月21日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPppDeactNtf_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_DEACTIVATING);

    /* 设置主状态 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_DISCING);

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 如果当前是1X模式，需要原因值，如果是HRPD则不需要 */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccHangUpDataCnf_CdataDiscing_WaitXccHangUpDataCallCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF状态下
             收到ID_XCC_APS_HANGUP_DATA_CALL_CNF消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvXccHangUpDataCnf_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取实体信息 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccHangUpDataCallCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF状态下
             收到ID_XCC_APS_DATA_CALL_DISC_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd      = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    /* 停止保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* 根据原因值和PPP状态判断是否需要通知PPP直接断开 */
    if ((TAF_XCC_CAUSE_SO_REJ == pstDiscInd->enCause)
      &&(TAF_APS_CDATA_PPP_STATE_ACTIVE == enPppState))
    {
        TAF_APS_SndPppDeactInd(ucPdpId);
    }

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_APS_MapXccCause(pstDiscInd->enCause));

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitXccHangUpDataCallCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2014年10月21日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitXccHangUpDataCallCnf(
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

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 更改子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 如果当前的PPP状态是激活的 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 需要通知PPP去激活 */
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
    }

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitXccHangUpDataCallCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF状态下
             收到TI_TAF_APS_CDATA_DISCING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterEpdszidReOrigReq_CdataDiscing_WaitXccHangUpDataCallCnf
 功能描述  : In TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF
             state, Rcv msg ID_MSG_TAF_PS_EPDSZID_REORIG_REQ
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterEpdszidReOrigReq_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;

    /* Get Pdp Entity */
    pstEntryMsg = TAF_APS_GetCurrSubFsmMsgAddr();

    /* If Discing is not caused by ID_MSG_TAF_PS_CALL_END_REQ and ID_PPP_APS_DEACT_NTF, Set  Epdszid Re-orig secne */
    if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) != pstEntryMsg->ulEventType)
     && (TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_DEACT_NTF)    != pstEntryMsg->ulEventType))
    {
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_REORIG_ENTER_DORMANT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcCdataDisc_CdataDiscing
 功能描述  : CDATA数据服务断开的处理
 输入参数  : TAF_PS_CAUSE_ENUM_UINT32                enCause
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月30日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_ProcCdataDisc_CdataDiscing(
    TAF_PS_CAUSE_ENUM_UINT32                enCause
)
{
    VOS_UINT8                               ucPdpId;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    TAF_APS_INTER_END_CDMA_CALL_REQ_STRU   *pstEndCdmaCall;
    VOS_UINT32                              ulNeedStartTimer;

    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    pstEndCdmaCall  = (TAF_APS_INTER_END_CDMA_CALL_REQ_STRU*)pstEntryMsg->aucEntryMsgBuffer;

    /* 判断是否启动Dormant TI */
    ulNeedStartTimer  = VOS_FALSE;

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_NO_LINK);

    /* 如果是用户发起的挂断，上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
    if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType)
     || ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) == pstEntryMsg->ulEventType)
      && (TAF_APS_INTER_END_CALL_SCENE_USER_END == pstEndCdmaCall->enEndScene)))
    {
        /* 设置当前数据服务模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_GetCurrPdpEntityRatType());

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    }
    else if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) == pstEntryMsg->ulEventType)
          && (TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL == pstEndCdmaCall->enEndScene))
    {
        /* 主叫时需要给用户上报REJ消息 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_GetPdpEntPdpCause(ucPdpId));
    }
    else if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) == pstEntryMsg->ulEventType)
          && (TAF_APS_INTER_END_CALL_SCENE_HANDOFF == pstEndCdmaCall->enEndScene))
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* 设置当前数据服务模式 */
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

    }
    else
    {
        if (TAF_APS_CDATA_PS_STATE_ACTIVE == TAF_APS_GetPdpEntCdataPsState(ucPdpId))
        {
            /* 如果之前是Active状态，20s没有数传而进入Dormant状态后，需要启动Dormant Timer */
            if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND) == pstEntryMsg->ulEventType)
            {
                if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
                {
                    ulNeedStartTimer = VOS_TRUE;
                }
                else
                {
                    ulNeedStartTimer = VOS_FALSE;
                }
            }

            TAF_APS_PdpEntityEnterDormant(ucPdpId, ulNeedStartTimer);

            /* 进入Dormant状态后，触发内部消息，发起重拨*/
            if (TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG != TAF_APS_GetEpdszidChgReOrigScene())
            {
                TAF_APS_SndInterEpdszidReOrigReq();

                TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
            }

            /* 退出子状态机 */
            TAF_APS_QuitCurrSubFsm();

            return VOS_TRUE;
        }
        else
        {
            /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_GetPdpEntPdpCause(ucPdpId));

        }
    }

    /* 释放资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* 退出子状态机 */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmDiscCnf_CdataDiscing_WaitHsmDiscCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF状态下
             收到ID_HSM_APS_DISC_CNF消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvHsmDiscCnf_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    HSM_APS_DISC_CNF_STRU              *pstDiscCnf = VOS_NULL_PTR;

    /* 获取实体信息 */
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscCnf            = (HSM_APS_DISC_CNF_STRU *)pstMsg;

    /* 停止保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    if (HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X == pstDiscCnf->enCause)
    {
        TAF_APS_SetIsHrpdDisabledFlag(VOS_TRUE);
        TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_1X);
    }

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_CdataDiscing_WaitHsmDiscCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitHsmDiscCnf(
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

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 更改子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 如果当前的PPP状态是激活的 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 需要通知PPP去激活 */
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitHsmDiscCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF状态下
             收到ID_HSM_APS_DISC_IND消息的处理
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

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    HSM_APS_DISC_IND_STRU              *pstDiscInd = VOS_NULL_PTR;

    /* 获取实体信息 */
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd            = (HSM_APS_DISC_IND_STRU *)pstMsg;

    /* 停止保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    if (HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X == pstDiscInd->enCause)
    {
        TAF_APS_SetIsHrpdDisabledFlag(VOS_TRUE);
        TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_1X);
    }

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitHsmDiscCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF状态下
             收到TI_TAF_APS_CDATA_DISCING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmPdnDeactCnf_CdataDiscing_WaitEhsmPdnDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF状态下
             收到ID_EHSM_APS_PDN_DEACTIVATE_CNF消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年05月15日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEhsmPdnDeactCnf_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    EHSM_APS_PDN_DEACTIVATE_CNF_STRU   *pstDeactCnf;

    /* 获取实体信息 */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf = (EHSM_APS_PDN_DEACTIVATE_CNF_STRU *)pstMsg;

    if (EHSM_APS_CAUSE_LAST_PDN == pstDeactCnf->enCause)
    {
        /* 停止保护定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        /* 停止流量统计 */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 如果是最后PDN去激活，EHSM会拒绝，根据此特定原因值进行特殊处理，此时
           该实体不会实际去激活，但是会刷新成默认承载，实体状态保持为激活状态 */

        /* 刷新成默认承载的CID */
        TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                    TAF_APS_DEFAULT_CID,
                                    TAF_APS_INVALID_MODULEID,
                                    TAF_APS_INVALID_CLIENTID,
                                    TAF_APS_INVALID_OPID);
        /* 通知EHSM当前的Cid刷新 */
        TAF_APS_SndEhsmPdnCtxInfoNotify(ucPdpId, EHSM_APS_PDN_OPTION_MODIFIED);

        /* 主状态迁移至TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;

    }
    else if(EHSM_APS_CAUSE_EHRPD_SUSPEND == pstDeactCnf->enCause)
    {
        /* 迁去激活Suspend状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND);

    }
    else
    {
        /* 停止保护定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        /* 数据链接断开处理 */
        TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmDeactInd_CdataDiscing_WaitEhsmPdnDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF状态下
             收到ID_EHSM_APS_PDN_DEACTIVATE_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年05月15日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEhsmPdnDeactInd_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF状态下
             收到TI_TAF_APS_CDATA_DISCING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年05月15日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 通知ehsm本地去激活 */
    TAF_APS_SndEhsmLocDeactNtf(ucPdpId);

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmSmEpsBearerInfoInd_CdataDiscing_WaitEhsmPdnDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF状态下
             收到ID_ESM_SM_EPS_BEARER_INFO_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年6月6日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEsmSmEpsBearerInfoInd_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucPdpId;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);

    /* 获取当前的状态机入口消息和EVENTTYPE */
    pstEntryMsg = TAF_APS_GetCurrSubFsmMsgAddr();

    /* 将入口消息切到3GPP状态机处理 */
    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType )
    {
        /* 主状态迁移至TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();

        /* 重新将去激活请求发送出来，后续进入3GPP状态机处理 */
        TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

    }

    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) ==pstEntryMsg->ulEventType)
    {
        /* 主状态迁移至TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();

        /* 重新将内部去激活请求发送出来，后续进入3GPP状态机处理 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_UNKNOWN);

    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmApsLteHandoverToEhrpdInd_CdataDiscing_Suspend
 功能描述  : 收到ID_EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月16日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEhsmApsLteHandoverToEhrpdInd_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    /* 向EHSM发送消息ID_APS_EHSM_PDN_DEACTIVATE_REQ */
    TAF_APS_SndEhsmPdnDeactReq(ucPdpId);
    TAF_APS_SndDhcpDeactInd(ucPdpId);

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果是缺省承载且地址类型是IPv6, 需要同步给ND Client */
    if ((TAF_APS_CheckPrimaryPdp(ucPdpId))
     && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* 状态迁移到TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND状态下
             收到TI_TAF_APS_CDATA_DISCING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年6月6日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取实体信息 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        TAF_APS_SndEhsmLocDeactNtf(ucPdpId);
    }

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_Suspend
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年06月08日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucPdpId;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;

    /* 获取消息内容 */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU *)pstMsg;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg         = TAF_APS_GetCurrSubFsmMsgAddr();

    if (TAF_APS_RAT_TYPE_EHRPD == pstServStaChangeInd->enRatType)
    {
        /* 向EHSM发送消息ID_APS_EHSM_PDN_DEACTIVATE_REQ */
        TAF_APS_SndEhsmPdnDeactReq(ucPdpId);

        /* 状态迁移到TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF);
    }
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        /* 停止保护定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);

        /* 将入口消息切到3GPP状态机处理 */
        if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType)
        {
            /* 主状态迁移至TAF_APS_STA_ACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* 退出子状态机 */
            TAF_APS_QuitCurrSubFsm();

            /* 重新将去激活请求发送出来，后续进入3GPP状态机处理 */
            TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

        }

        if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) ==pstEntryMsg->ulEventType)
        {
            /* 主状态迁移至TAF_APS_STA_ACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* 退出子状态机 */
            TAF_APS_QuitCurrSubFsm();

            /* 重新将内部去激活请求发送出来，后续进入3GPP状态机处理 */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_UNKNOWN);
        }
    }
    else
    {
        if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            TAF_APS_SndEhsmLocDeactNtf(ucPdpId);
        }

        /* 停止保护定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        /* 停止流量统计 */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态状态机 */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcPppDeactInd_CdataDiscing
 功能描述  : 建链过程中或者等待PPP去激活协商时收到PPP发送来的PPP Deact Ind消
             息
 输入参数  : VOS_UINT8                           ucPdpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcPppDeactInd_CdataDiscing(
    VOS_UINT8                           ucPdpId
)
{
    /* 停止流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

    /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /* PPP链路断开后，再去断开空口链路 */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitPppDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF状态下收到消息ID_PPP_APS_DEACT_CNF
             的处理
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
VOS_UINT32  TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_CNF_STRU             *pstDeactCnf;
    VOS_UINT8                           ucPdpId;

    /* 获取PdpId */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

    /* 如果PPP回复失败，则强制PPP去激活 */
    pstDeactCnf = (PPP_APS_DEACT_CNF_STRU*)pstMsg;
    if (VOS_OK != pstDeactCnf->ulResult)
    {
        TAF_APS_SndPppDeactInd(ucPdpId);
    }

    /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /* 如果当前链路不存在，或不在建链过程中，则不需要再去断空口链路 */
    if (TAF_APS_CDATA_AIR_LINK_NO_LINK == TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
    {
        /* 数据链接断开处理 */
        TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);
    }
    else
    {
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactInd_CdataDiscing_WaitPppDeactCnf
 功能描述  : 子状态TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF下收到消息ID_PPP_APS_DEACT_NTF
             的处理
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
VOS_UINT32  TAF_APS_RcvPppDeactInd_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取PdpId */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 如果当前链路不存在，或不在建链过程中，则不需要再去断空口链路 */
    if (TAF_APS_CDATA_AIR_LINK_NO_LINK == TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
    {
        /* 停止流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* 数据链接断开处理 */
        TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);
    }
    else
    {
        TAF_APS_ProcPppDeactInd_CdataDiscing(ucPdpId);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcHrpdOrigDataCall_CdataDiscing_HybridMode
 功能描述  : 去激活流程中需要先在HRPD网络上建链成功，链路存在才能做PPP去激活协商
 输入参数  : VOS_UINT8                           ucPdpId
             VOS_UINT32                          ulNeedSearchSys
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcHrpdOrigDataCall_CdataDiscing_HybridMode(
    VOS_UINT8                           ucPdpId,
    VOS_UINT32                          ulDoQuickAcq
)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enSdcServiceStatus;
    VOS_UINT32                          ulClDelaySearch;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 拨号参数 */
    pstPdpEntity->stCdataInfo.ucCallId = ucPdpId + 1;

    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

    TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_HRPD);

    /* 启动30s重拨周期定时器 */
    if (TAF_APS_TIMER_STATUS_RUNING != TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId))
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD_LEN,
                           ucPdpId);
    }

    if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_HRPD))
    {
        /* 发送激活请求 */
        TAF_APS_SndHsmOrigReq(ucPdpId);

        /* 子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF);
    }
    else
    {
        enSdcServiceStatus = TAF_APS_GetHrpdServiceStatus();
        ulClDelaySearch    = TAF_APS_GetClDelaySearch();

        /* Send Redial Ntf to MMA */
        if ((VOS_FALSE == ulClDelaySearch)
         && ((VOS_TRUE == ulDoQuickAcq) || (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enSdcServiceStatus)))
        {
            /* 触发HRPD下搜索MRU[0] */
            TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                                     0,
                                                     TAF_MMA_DO_NORMAL_DATA_CALL,
                                                     TAF_PS_CAUSE_HRPD_NO_SERVICE);
        }

        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                           ucPdpId);

        /* 子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_Proc1xOrigDataCall_CdataDiscing_1XMode
 功能描述  : 去激活流程中需要先在1X网络上建链成功，链路存在才能做PPP去激活协商
 输入参数  : VOS_UINT8                           ucIsDormDataCall
             VOS_UINT8                           ucDrsFlg
             VOS_UINT8                           ucHrpdHandOff1xFlg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_Proc1xOrigDataCall_CdataDiscing_1XMode(
    VOS_UINT8                           ucIsDormDataCall,
    VOS_UINT8                           ucDrsFlg,
    VOS_UINT8                           ucHrpdHandOff1xFlg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* Get Pdp Fsm Entity */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->stCdataInfo.ucCallId         = ucPdpId + 1;
    pstPdpEntity->stCdataInfo.enSo             = TAF_APS_GetFsmCtxCdataSoInitType();
    pstPdpEntity->stCdataInfo.ucDrsFlg         = ucDrsFlg;
    pstPdpEntity->stCdataInfo.ucIsDormDataCall = ucIsDormDataCall;
    pstPdpEntity->stCdataInfo.ucIsL2ErrReOrig  = VOS_FALSE;
    pstPdpEntity->stCdataInfo.ucReOrigCount    = 0;

    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

    TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_1X);

    if (TAF_APS_TIMER_STATUS_RUNING != TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId))
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD_LEN, ucPdpId);
    }

    /* 判断是否可以发起1X建链 */
    if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_1X))
    {
        /* 发送激活请求至XCC */
        TAF_APS_SndXccOrigDataCallReq(ucPdpId, ucHrpdHandOff1xFlg);

        /* 子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF);
    }
    else
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                           ucPdpId);

        /* 子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcCdataRedialReOrig_CdataDiscing_1XMode
 功能描述  : 1X网络下发起重拨
 输入参数  : VOS_UINT8                           ucIsDormDataCall
             VOS_UINT8                           ucDrsFlg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_ProcCdataRedialReOrig_CdataDiscing_1XMode(
    VOS_UINT8                           ucIsDormDataCall,
    VOS_UINT8                           ucDrsFlg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 获取APS实体索引 */
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->stCdataInfo.ucCallId              = ucPdpId + 1;
    pstPdpEntity->stCdataInfo.enSo                  = TAF_APS_GetFsmCtxCdataSoInitType();
    pstPdpEntity->stCdataInfo.ucDrsFlg              = ucDrsFlg;
    pstPdpEntity->stCdataInfo.ucIsDormDataCall      = ucIsDormDataCall;

    if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
    {
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
        TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
    }

    TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_1X);

    /* 向1X发送数据服务链接建立请求 */
    TAF_APS_SndXccOrigDataCallReq(ucPdpId, VOS_FALSE);

    /* 子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppReConnInd_CdataDiscing_WaitPppDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF状态下收到PPP通
             知建链的消息
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
VOS_UINT32  TAF_APS_RcvPppReConnInd_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType = TAF_APS_GetCurrPdpEntityRatType();

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTING);

    /* 如果支持HYBRID模式，首先在HPRD模式下进行尝试建链 */
    if (VOS_FALSE == TAF_SDC_Is1xOnlyMode())
    {
        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_HRPD:
                /* DO强信号去HRPD建链；DO弱信号去1X建链 */
                if (VOS_FALSE == TAF_APS_GetIsHrpdDisabledFlag())
                {
                    TAF_APS_ProcHrpdOrigDataCall_CdataDiscing_HybridMode(ucPdpId, VOS_FALSE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataDiscing_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
                }
                break;

            case TAF_APS_RAT_TYPE_1X:
            case TAF_APS_RAT_TYPE_NULL:
                /* DO强信号去HRPD建链；DO弱信号去1X建链 */
                if (VOS_FALSE == TAF_APS_GetIsHrpdDisabledFlag())
                {
                    TAF_APS_ProcHrpdOrigDataCall_CdataDiscing_HybridMode(ucPdpId, VOS_TRUE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataDiscing_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
                }
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvPppReConnInd_CdataDiscing_WaitPppDeactCnf: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* 如果不支持Hybrid，即只支持1X，则在1X下尝试建链 */
        TAF_APS_Proc1xOrigDataCall_CdataDiscing_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitPppDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF状态下收到消息ID_XCC_APS_DATA_CALL_DISC_IND
             的处理
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
VOS_UINT32 TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity         = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDiscInd           = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* SO Rej 需要特殊处理，本地去激活 */
    if (TAF_PS_CAUSE_XCC_AS_SO_REJ == pstPdpEntity->enCause)
    {
        /* 停止流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

        /* 停止流量统计 */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        /* 之前的去激活流程尚未结束，PPP去激活协商尚未完成，此时上报去激活事件 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        return VOS_TRUE;
    }
    else
    {
        TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_NO_LINK);

        /* 通知PPP当前链路不存在 */
        TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_NOT_EXISTED);

        /* 状态继续维持在TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF */
        return VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitPppDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF状态下收到消息ID_HSM_APS_DISC_IND的
             处理
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
VOS_UINT32 TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    HSM_APS_DISC_IND_STRU              *pstDiscInd = VOS_NULL_PTR;

    /* 初始化, 获取PDP ID */
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd            = (HSM_APS_DISC_IND_STRU *)pstMsg;

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_NO_LINK);

    /* 通知PPP当前链路不存在,APS子状态机的状态维持不变 */
    TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_NOT_EXISTED);

    if (HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X == pstDiscInd->enCause)
    {
        TAF_APS_SetIsHrpdDisabledFlag(VOS_TRUE);
        TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_1X);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitPppDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF状态下收到消息TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF超时
             的处理
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
VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitPppDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取PdpId */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 通知PPP直接断开 */
    TAF_APS_SndPppDeactInd(ucPdpId);

    /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /* 如果当前链路不存在，或不在建链过程中，则不需要再去断空口链路 */
    if (TAF_APS_CDATA_AIR_LINK_NO_LINK == TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
    {
        /* 数据链接断开处理 */
        TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);
    }
    else
    {
        /* PPP链路断开后，再去断开空口链路 */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccOrigDataCallCnf_CdataDiscing_WaitXccOrigCnf
 功能描述  : 子状态TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF下收到消息ID_XCC_APS_ORIG_DATA_CALL_CNF
             的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccOrigDataCallCnf_CdataDiscing_WaitXccOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_ORIG_DATA_CALL_CNF_STRU    *pstOirgCallCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    pstOirgCallCnf  = (XCC_APS_ORIG_DATA_CALL_CNF_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (TAF_XCC_CAUSE_SUCCESS == pstOirgCallCnf->enRslt)
    {
        TAF_APS_SetPdpEntConRef(ucPdpId, pstOirgCallCnf->ucConRef);
        TAF_APS_SetPdpEntConnectId(ucPdpId, pstOirgCallCnf->ucConnectId);

        /* 如果重拨周期定时器在运行，需要关闭重拨周期定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* 记录当前建立数据服务的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

        /* 通知外部模块当前的PS服务所在的模式 */
        TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_1X);

        /* 迁移TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED);

        TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
    }
    else
    {
        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_APS_MapXccCause(pstOirgCallCnf->enRslt);

        pstPdpEntity->sRssi   = pstOirgCallCnf->sRssi;

        /* 判断是否需要发起Silent Redial */
        if (VOS_TRUE == TAF_APS_IsNeedSilentRedial(pstPdpEntity->enCause, TAF_APS_RAT_TYPE_1X))
        {
            TAF_APS_CdataOrigRedialCount(ucPdpId, pstOirgCallCnf->enFailLayer);

            if (VOS_TRUE == TAF_APS_IsNeedRedial1xSystemAcquire(pstPdpEntity->enCause, pstPdpEntity->sRssi))
            {
                TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                                         0,
                                                         TAF_MMA_1X_NORMAL_DATA_CALL,
                                                         pstPdpEntity->enCause);
            }

            /* 起SILENT_REDIAL_WAIT 4s定时器，如果此定时器超时，会尝试重拨 */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                               TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                               ucPdpId);

            /* 迁移TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL子状态 */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL);
        }
        else
        {
            /* 如果重拨周期定时器在运行，需要停止 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

            if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId))
            {
                /* 停止PPP去激活协商流程定时器 */
                TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);
            }

            /* 停止流量统计 */
            TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

            /* Dormant状态下去激活触发的建链/PPP触发的重建，如果建链失败，需要通知PPP本地去激活*/
            TAF_APS_SndPppDeactInd(ucPdpId);

            /* 给用户返回DEACTIVE_CNF事件 */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

            /* 释放APS资源 */
            Aps_ReleaseApsResource(ucPdpId);

            /* 配置IP过滤 */
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            /* 主状态迁移至TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* 退出子状态状态机 */
            TAF_APS_QuitCurrSubFsm();
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitXccOrigCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF子状态下收到消息ID_PPP_APS_DEACT_CNF
             的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitXccOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_CNF_STRU             *pstDeactCnf;
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf = (PPP_APS_DEACT_CNF_STRU *)pstMsg;

    /* 如果之前并未发起过PPP去激活协商，则不处理，return */
    if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 停止PPP去激活协商流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

        /* 如果PPP回复失败，则强制PPP去激活 */
        pstDeactCnf = (PPP_APS_DEACT_CNF_STRU*)pstMsg;
        if (VOS_OK != pstDeactCnf->ulResult)
        {
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* 如果重拨周期定时器在运行，需要停止 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

        /* PPP链路断开后，再去断开空口链路 */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactInd_CdataDiscing_WaitXccOrigCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF子状态下收到消息
             ID_PPP_APS_DEACT_NTF的处理
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
VOS_UINT32  TAF_APS_RcvPppDeactInd_CdataDiscing_WaitXccOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取PdpId */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();

    /* 如果重拨周期定时器在运行，需要停止 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

    TAF_APS_ProcPppDeactInd_CdataDiscing(ucPdpId);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitXccOrigCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_ORIG_CNF子状态下收到定时器消息TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF超时
             的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitXccOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* 获取PdpId */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* 去激活的保护定时器超时，PPP的状态只可能是ACTIVE/DEACTIVATING */
    if ((TAF_APS_CDATA_PPP_STATE_DEACTIVATING == enPppState)
     || (TAF_APS_CDATA_PPP_STATE_ACTIVE       == enPppState))
    {
        /* 如果重拨周期定时器在运行，需要停止 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

        /* PPP链路断开后，再去断开空口链路 */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmOrigCnf_CdataDiscing_WaitHsmOrigCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF子状态下收到消息ID_HSM_APS_ORIG_CNF
             的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmOrigCnf_CdataDiscing_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_ORIG_CNF_STRU              *pstOirgCallCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    pstOirgCallCnf  = (HSM_APS_ORIG_CNF_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (HSM_APS_CAUSE_SUCCESS == pstOirgCallCnf->enResult)
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* 记录当前建立数据服务的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTED);

        TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

        if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            /* 链路重建是由PPPC模块触发，之前的PPP去激活协商还未结束,通知PPPC链路已重建成功 */
            TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_CONNECTED);
        }
        else
        {
            /***************************************************************************/
            /*   Dormant状态下去激活，需要等链路建立成功之后，再发送PPP去激活协商请求  */
            /***************************************************************************/

            /* 发送ID_APS_PPP_DEACT_REQ消息给PPP模块 */
            TAF_APS_SndPppDeactReq(ucPdpId);

            /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_DEACTIVATING */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);

            /* 不需要再启动TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF定时器，之前入口消息已经启动 */
        }

        /* 迁移TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF子状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF);
    }
    else
    {
        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_APS_MapHsmCause(pstOirgCallCnf->enResult);

        /* 判断是否需要发起Silent Redial */
        if (VOS_TRUE == TAF_APS_IsNeedSilentRedial(pstPdpEntity->enCause, TAF_APS_RAT_TYPE_HRPD))
        {
            /* 起SILENT_REDIAL_WAIT 4s定时器，如果此定时器超时，会尝试重拨 */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                               TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                               ucPdpId);

            /* 迁移TAF_APS_CDATA_ESTING_SUBSTA_WAIT_REDIAL子状态 */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL);
        }
        else
        {
            /* 如果重拨周期定时器在运行，需要停止 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

            if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId))
            {
                /* 停止PPP去激活协商流程定时器 */
                TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);
            }

            /* 停止流量统计 */
            TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

            /* Dormant状态下去激活触发的建链/PPP触发的重建，如果建链失败，需要通知PPP本地去激活*/
            TAF_APS_SndPppDeactInd(ucPdpId);

            /* 给用户返回DEACTIVE_CNF事件 */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

            /* 释放APS资源 */
            Aps_ReleaseApsResource(ucPdpId);

            /* 配置IP过滤 */
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            /* 主状态迁移至TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* 退出子状态状态机 */
            TAF_APS_QuitCurrSubFsm();
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitHsmOrigCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF子状态下收到消息ID_PPP_APS_DEACT_CNF
             的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_CNF_STRU             *pstDeactCnf;
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf = (PPP_APS_DEACT_CNF_STRU *)pstMsg;

    /* 如果之前并未发起过PPP去激活协商，则不处理，return */
    if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 停止PPP去激活协商流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

        /* 如果PPP回复失败，则强制PPP去激活 */
        pstDeactCnf = (PPP_APS_DEACT_CNF_STRU*)pstMsg;
        if (VOS_OK != pstDeactCnf->ulResult)
        {
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* 如果重拨周期定时器在运行，需要停止 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        /* PPP链路断开后，再去断开空口链路 */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactInd_CdataDiscing_WaitHsmOrigCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF子状态下收到消息-
             ID_PPP_APS_DEACT_NTF的处理
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
VOS_UINT32  TAF_APS_RcvPppDeactInd_CdataDiscing_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取PdpId */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 如果重拨周期定时器在运行，需要停止 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

    TAF_APS_ProcPppDeactInd_CdataDiscing(ucPdpId);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitHsmOrigCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF子状态下收到定时器TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF超时消息
             的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* 获取PdpId */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* 去激活的保护定时器超时，PPP的状态只可能是ACTIVE/DEACTIVATING */
    if ((TAF_APS_CDATA_PPP_STATE_DEACTIVATING == enPppState)
     || (TAF_APS_CDATA_PPP_STATE_ACTIVE       == enPppState))
    {
        /* 如果重拨周期定时器在运行，需要停止 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        /* PPP链路断开后，再去断开空口链路 */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDataServiceConnInd_CdataDiscing_WaitXccSoConnected
 功能描述  : 子状态TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED下收到
             消息ID_XCC_APS_DATA_SERVICE_CONNECT_IND的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataServiceConnInd_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_SERVICE_CONNECT_IND_STRU  *pstSoInd;
    VOS_UINT8                               ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId  = TAF_APS_GetCurrFsmEntityPdpId();
    pstSoInd = (XCC_APS_DATA_SERVICE_CONNECT_IND_STRU *)pstMsg;

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTED);

    /* 更新SO、CONREF和PPP ID信息 */
    TAF_APS_SetPdpEntSo(ucPdpId, pstSoInd->enSo);
    TAF_APS_SetPdpEntConRef(ucPdpId, pstSoInd->ucConRef);

    /* 更新SR ID信息 */
    TAF_APS_SetPdpEntSrId(ucPdpId, pstSoInd->ucSrId);

    /* 通知RLP做初始化 */
    TAF_APS_SndRlpInitReq(ucPdpId);

    if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 链路重建是由PPPC模块触发，之前的PPP去激活协商还未结束,通知PPPC链路已重建成功 */
        TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_CONNECTED);
    }
    else
    {
        /***************************************************************************/
        /*   Dormant状态下去激活，需要等链路建立成功之后，再发送PPP去激活协商请求  */
        /***************************************************************************/
        /* 发送ID_APS_PPP_DEACT_REQ消息给PPP模块 */
        TAF_APS_SndPppDeactReq(ucPdpId);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_DEACTIVATING */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);
    }

    /* 迁移TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF子状态 */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_PPP_DEACT_CNF);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccSoConnected
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态收到消
             息ID_XCC_APS_DATA_CALL_DISC_IND的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 给用户返回DEACTIVE_CNF事件 */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId))
    {
        /* 停止PPP去激活协商流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);
    }

    if (TAF_APS_CDATA_PPP_STATE_INACTIVE != TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* PPP的状态主要是TAF_APS_CDATA_PPP_STATE_ACTIVE / TAF_APS_CDATA_PPP_STATE_DEACTIVATING两种情况 */
        TAF_APS_SndPppDeactInd(ucPdpId);
    }

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 退出子状态状态机 */
    TAF_APS_QuitCurrSubFsm();

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitXccSoConnected
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态收到消
             息ID_PPP_APS_DEACT_CNF的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_CNF_STRU             *pstDeactCnf;
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf = (PPP_APS_DEACT_CNF_STRU *)pstMsg;

    /* 如果之前并未发起过PPP去激活协商，则不处理，return */
    if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 停止PPP去激活协商流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

        /* 如果PPP回复失败，则强制PPP去激活 */
        pstDeactCnf = (PPP_APS_DEACT_CNF_STRU*)pstMsg;
        if (VOS_OK != pstDeactCnf->ulResult)
        {
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* PPP链路断开后，再去断开空口链路 */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactInd_CdataDiscing_WaitXccSoConnected
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态收到消
             息ID_PPP_APS_DEACT_NTF的处理
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
VOS_UINT32 TAF_APS_RcvPppDeactInd_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    TAF_APS_ProcPppDeactInd_CdataDiscing(ucPdpId);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitXccSoConnected
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态收到TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF超时消
             息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月10日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* 获取PdpId */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* 去激活的保护定时器超时，PPP的状态只可能是ACTIVE/DEACTIVATING */
    if ((TAF_APS_CDATA_PPP_STATE_DEACTIVATING == enPppState)
     || (TAF_APS_CDATA_PPP_STATE_ACTIVE       == enPppState))
    {
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* PPP链路断开后，再去断开空口链路 */
        TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiRedialIntervalExpired_CdataDiscing_WaitRedial
 功能描述  : 子状态TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL下收到
             TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiRedialIntervalExpired_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT32                          ulRemainTimeLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucIsDormDataCall;
    VOS_UINT8                           ucDrsFlag;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enSdcServiceStatus;

    ucDrsFlag           = VOS_TRUE;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg         = TAF_APS_GetCurrSubFsmMsgAddr();
    enSdcServiceStatus  = TAF_APS_GetHrpdServiceStatus();

    if ((VOS_FALSE == TAF_APS_GetClDelaySearch())
     || (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enSdcServiceStatus))
    {
        /* 判断是否可以发起HRPD建链 */
        if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_HRPD))
        {
            /* Send Orig Data Call Req To HSM */
            TAF_APS_SndHsmOrigReq(ucPdpId);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
            {
                TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
                TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
            }
            TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_HRPD);

            /* Sub Fsm State transfer to TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF);

            return VOS_TRUE;
        }

        /* 判断是否可以发起1X建链 */
        if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_1X))
        {
            ucDrsFlag        = TAF_APS_GetDrsValueByScene(pstEntryMsg->ulEventType);
            ucIsDormDataCall = TAF_APS_IsRedialCallFromDormantState(ucPdpId);

            TAF_APS_ProcCdataRedialReOrig_CdataDiscing_1XMode(ucIsDormDataCall, ucDrsFlag);

            return VOS_TRUE;
        }
    }

    TAF_APS_GetRemainTimerLen(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD,
                              ucPdpId,
                              &ulRemainTimeLen);

    if (ulRemainTimeLen >= TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN)
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                           ucPdpId);

        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL);
    }
    else
    {
        /* 如果重拨周期定时器在运行，需要停止 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* 通知搜网模块结束搜网 */
        if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
        }

        if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
        }

        /* 停止流量统计 */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        /* 给用户返回DEACTIVE_CNF事件 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId))
        {
            /* 停止PPP去激活协商流程定时器 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);
        }

        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态状态机 */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitRedial
 功能描述  : 子状态TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL下收到消息ID_PPP_APS_DEACT_CNF的处
             理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    PPP_APS_DEACT_CNF_STRU             *pstDeactCnf;

    /* 初始化 */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf = (PPP_APS_DEACT_CNF_STRU *)pstMsg;

    /* 如果之前已经发送过PPP去激活协商，则继续处理，否则直接return */
    if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
        }

        if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
        }

        /* 停止流量统计 */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        /* 给用户返回DEACTIVE_CNF事件 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 停止PPP去激活协商流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

        /* 停止重拨周期定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* 停止重拨间隔定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

        /* 如果PPP回复失败，则强制PPP去激活 */
        pstDeactCnf = (PPP_APS_DEACT_CNF_STRU*)pstMsg;
        if (VOS_OK != pstDeactCnf->ulResult)
        {
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态状态机 */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDeactCnf_CdataDiscing_WaitRedial
 功能描述  : 子状态TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL下收到消息ID_PPP_APS_DEACT_NTF的处
             理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactInd_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
    {
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
    }

    if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
    {
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
    }

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    /* 给用户返回DEACTIVE_CNF事件 */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 停止PPP去激活协商流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

    /* 停止重拨周期定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

    /* 停止重拨间隔定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

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
 函 数 名  : TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitRedial
 功能描述  : 子状态TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL下收到
             TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* 获取PdpId */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* 去激活的保护定时器超时，PPP的状态只可能是ACTIVE/DEACTIVATING */
    if ((TAF_APS_CDATA_PPP_STATE_DEACTIVATING == enPppState)
     || (TAF_APS_CDATA_PPP_STATE_ACTIVE       == enPppState))
    {
        if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
        }

        if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
        }

        /* 停止流量统计 */
        TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        /* 给用户返回DEACTIVE_CNF事件 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 停止重拨周期定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* 停止重拨间隔定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态状态机 */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_WaitRedial
 功能描述  : 子状态TAF_APS_CDATA_DISCING_SUBSTA_WAIT_INTERVAL_REDIAL下收到
             ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月17日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;
    VOS_UINT8                                               ucPdpId;
    VOS_UINT8                                               ucIsDormDataCall;
    VOS_UINT8                                               ucDrsFlag;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstSvcStaChangeReq = VOS_NULL_PTR;

    ucDrsFlag    = VOS_TRUE;
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg  = TAF_APS_GetCurrSubFsmMsgAddr();

    /* 获取消息内容 */
    pstSvcStaChangeReq = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    switch(pstSvcStaChangeReq->enRatType)
    {
        /* 判断HRPD有服务 */
        case TAF_APS_RAT_TYPE_HRPD:
            /* 判断是否可以发起HRPD建链 */
            if(VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_HRPD))
            {
                /* 停止定时器 */
                TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

                /* Send Orig Data Call Req To HSM */
                TAF_APS_SndHsmOrigReq(ucPdpId);

                if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
                {
                    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
                    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
                }

                TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_HRPD);

                /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF */
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_ORIG_CNF);
            }

            break;

        /* 判断1X服务 */
        case TAF_APS_RAT_TYPE_1X:
            /* 判断是否可以发起1X建链 */
            if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_1X))
            {
                /* 停止定时器 */
                TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

                if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ) == pstEntryMsg->ulEventType)
                {
                    /* Esting Fsm is started, Set Re-Orig Secne BuTT */
                    TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
                }

                ucDrsFlag           = TAF_APS_GetDrsValueByScene(pstEntryMsg->ulEventType);
                ucIsDormDataCall    = TAF_APS_IsRedialCallFromDormantState(ucPdpId);

                TAF_APS_ProcCdataRedialReOrig_CdataDiscing_1XMode(ucIsDormDataCall, ucDrsFlag);
            }

            break;

        case TAF_APS_RAT_TYPE_EHRPD:
        case TAF_APS_RAT_TYPE_LTE:
            /* 停止流程定时器 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

            /* 如果重拨周期定时器在运行，需要停止 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
            {
                TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
            }
            else
            {
                TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
            }

            /* 数据链接断开处理 */
            TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_RAT_TYPE_CHANGE);

            /* 通知外部模块PS模式切换 */
            TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

            break;

        default:
            break;
    }

    return VOS_TRUE;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
