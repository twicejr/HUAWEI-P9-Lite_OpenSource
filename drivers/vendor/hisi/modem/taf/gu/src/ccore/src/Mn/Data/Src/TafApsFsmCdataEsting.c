/******************************************************************************

                   版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsFsmCdataEsting.c　
  版 本 号   : 初稿
  作    者   : y00213812
  生成日期   : 2014年10月14日
  最近修改   :
  功能描述   : DORMANT状态下的处理
  函数列表   :

  修改历史   :
  1.日    期   : 2014年10月14日
    作    者   : y00213812
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
#include "TafApsSndRlp.h"
#include "TafApsSndCds.h"
#include "TafApsProcIpFilter.h"
#include "hsm_aps_pif.h"
#include "TafApsSndHsm.h"
#include "xcc_aps_pif.h"
#include "TafApsProcEpdszid.h"
#include "ehsm_aps_pif.h"
#include "TafApsSndEhsm.h"
#include "TafApsSndNd.h"
#include "TafApsSndDhcp.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_ESTING_C

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
 函 数 名  : TAF_APS_RcvPsCallOrigReq_CdataEsting_Init
 功能描述  : CDATA ESTING INIT子状态下收到ID_MSG_TAF_PS_CALL_ORIG_REQ消息的处理
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

  2.日    期   : 2015年08月24日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallOrigReq_CdataEsting_Init(
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

    /* 初始化, 获取PDP ID和当前接入技术 */
    pstAppMsg      = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType  = TAF_APS_GetCurrPdpEntityRatType();
    ucCid          = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* 检查PS域卡状态, 如果无效, 直接返回ERROR */
    if (TAF_SDC_USIM_STATUS_VALID != TAF_SDC_GetCsimStatus())
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

    if (0 == TAF_APS_GetCallRemainTmrLen(ucCid))
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                                 pstCallOrigReq->stDialParaInfo.ucCid,
                                 TAF_PS_CAUSE_SUCCESS);
    }

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                 pstCallOrigReq->stDialParaInfo.ucCid,
                                 pstCallOrigReq->stDialParaInfo.enPdpType);

    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVATING);

    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTING);

    /* 如果支持HYBRID模式，首先在HPRD模式下进行尝试建链 */
    if (VOS_TRUE == TAF_APS_IsHybridMode())
    {
        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_HRPD:
                /* DO强信号去HRPD建链；DO弱信号去1X建链 */
                if (VOS_FALSE == TAF_APS_GetIsHrpdDisabledFlag())
                {
                    TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(ucPdpId, VOS_FALSE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
                }
                break;

            case TAF_APS_RAT_TYPE_EHRPD:
                TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode(ucPdpId, TAF_APS_ORIG_TYPE_PS_CALL);

                break;

            case TAF_APS_RAT_TYPE_1X:
                /* DO强信号去HRPD建链；DO弱信号去1X建链 */
                if (VOS_FALSE == TAF_APS_GetIsHrpdDisabledFlag())
                {
                    TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(ucPdpId, VOS_TRUE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
                }
                break;

            case TAF_APS_RAT_TYPE_NULL:
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND);

                ulTimerLen = TAF_APS_GetCallRemainTmrLen(ucCid);

                if (0 == ulTimerLen)
                {
                    ulTimerLen = TI_TAF_APS_CDATA_ESTING_LEN;
                }

                TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, ulTimerLen, ucPdpId);
                TAF_APS_SetCallRemainTmrLen(ucCid, 0);

                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvPsCallOrigReq_CdataEsting_Init: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* 如果不支持Hybrid，即只支持1X，则在1X下尝试建链 */
        TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppDialOrigReq_CdataEsting_Init
 功能描述  : CDATA ESTING INIT子状态下收到ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息的处理
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

  2.日    期   : 2015年08月24日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDialOrigReq_CdataEsting_Init(
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
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    /* 初始化, 获取PDP ID和当前接入技术 */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType       = TAF_APS_GetCurrPdpEntityRatType();
    ucCid               = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* 检查PS域卡状态, 如果无效, 直接返回ERROR */
    if (TAF_SDC_USIM_STATUS_VALID != TAF_SDC_GetCsimStatus())
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

    if (0 == TAF_APS_GetCallRemainTmrLen(ucCid))
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                  TAF_PS_CAUSE_SUCCESS);
    }

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                 pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                 TAF_APS_GetTafCidInfoPdpType(ucCid));



    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVATING);

    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTING);

    /* 如果支持HYBRID模式，首先在HPRD模式下进行尝试建链 */
    if (VOS_TRUE == TAF_APS_IsHybridMode())
    {
        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_HRPD:
                /* DO强信号去HRPD建链；DO弱信号去1X建链 */
                if (VOS_FALSE == TAF_APS_GetIsHrpdDisabledFlag())
                {
                    TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(ucPdpId, VOS_FALSE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
                }
                break;

            case TAF_APS_RAT_TYPE_EHRPD:
                enPdpType = TAF_APS_GetTafCidInfoPdpType(pstPppDialOrigReq->stPppDialParaInfo.ucCid);

                if ((TAF_PS_CDATA_DIAL_MODE_RELAY == TAF_APS_GetFsmCtxCdataDialMode())
                 || (TAF_PDP_PPP == enPdpType))
                {
                    /* 中继模式或者地址类型设置为PPP，则上报拨号失败 */
                    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_INVALID_PARAMETER);

                    /* 释放APS资源 */
                    Aps_ReleaseApsResource(ucPdpId);

                    /* 主状态迁移至TAF_APS_STA_INACTIVE */
                    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

                    /* 退出子状态状态机 */
                    TAF_APS_QuitCurrSubFsm();
                }
                else
                {
                    TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode(ucPdpId, TAF_APS_ORIG_TYPE_PPP_DIAL);
                }

                break;

            case TAF_APS_RAT_TYPE_1X:
                /* DO强信号去HRPD建链；DO弱信号去1X建链 */
                if (VOS_FALSE == TAF_APS_GetIsHrpdDisabledFlag())
                {
                    TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(ucPdpId, VOS_TRUE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
                }
                break;

            case TAF_APS_RAT_TYPE_NULL:
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND);

                ulTimerLen = TAF_APS_GetCallRemainTmrLen(ucCid);
                if (0 == ulTimerLen)
                {
                    ulTimerLen = TI_TAF_APS_CDATA_ESTING_LEN;
                }

                TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, ulTimerLen, ucPdpId);
                TAF_APS_SetCallRemainTmrLen(ucCid, 0);

                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvPsCallOrigReq_CdataEsting_Init: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* 如果不支持Hybrid，即只支持1X，则在1X下尝试建链 */
        TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccIncomingCallInd_CdataEsting_Init
 功能描述  : CDATA ESTING INIT子状态下收到ID_XCC_APS_INCOMING_CALL_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_INCOMING_CALL_IND_STRU     *pstIncomingCall;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstIncomingCall = (XCC_APS_INCOMING_CALL_IND_STRU *)pstMsg;

    /* 起激活定时器 */
    TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, TI_TAF_APS_CDATA_ESTING_LEN, ucPdpId);
    /* TAF_APS_SetCallRemainTmrLen(TAF_APS_GetPdpEntCurrCid(ucPdpId), 0); */

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 设置主状态 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTING);

    /* 记录当前建立数据服务的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);



    /* 根据ByePass值进行处理 */
    if (VOS_TRUE == pstIncomingCall->ucIsAlertAnsByPass)
    {
        /* 迁TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND子状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND);
    }
    else
    {
        /* 发送ID_APS_XCC_ANSWER_DATA_CALL_REQ */
        TAF_APS_SndXccAnswerDataCallReq(ucPdpId);

        /* 迁TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF子状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF);
    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvCdsServiceInd_CdataEsting_Init
 功能描述  : CDATA ESTING INIT子状态下收到ID_CDS_APS_SERVICE_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvCdsServiceInd_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType   = TAF_APS_GetCurrPdpEntityRatType();

    /* area lost no RF场景, 触发搜网*/
/* TODO:
#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_FALSE == TAF_SDC_GetRfAvailFlag())
    {
        TAF_MMA_SrvAcqReq(TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL);
    }
#endif
*/

    /* 用户上行数据触发的数据服务链接重建 */
    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);
    /* TODO:需要综合考虑进DORMANT前数据服务所在的模式 */

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTING);

    /* 如果支持HYBRID模式，首先在HPRD模式下进行尝试建链 */
    if (VOS_TRUE == TAF_APS_IsHybridMode())
    {
        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_HRPD:
                /* DO强信号去HRPD建链；DO弱信号去1X建链 */
                if (VOS_FALSE == TAF_APS_GetIsHrpdDisabledFlag())
                {
                    TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(ucPdpId, VOS_FALSE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_TRUE, VOS_TRUE, VOS_FALSE);
                }
                break;

            case TAF_APS_RAT_TYPE_EHRPD:
                break;

            case TAF_APS_RAT_TYPE_1X:
            case TAF_APS_RAT_TYPE_NULL:
                /* DO强信号去HRPD建链；DO弱信号去1X建链 */
                if (VOS_FALSE == TAF_APS_GetIsHrpdDisabledFlag())
                {
                    TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(ucPdpId, VOS_TRUE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_TRUE, VOS_TRUE, VOS_FALSE);
                }
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvCdsServiceInd_CdataEsting_Init: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* 如果不支持Hybrid，即只支持1X，则在1X下尝试建链 */
        TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_TRUE, VOS_TRUE, VOS_FALSE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppReConnInd_CdataEsting_Init
 功能描述  : CDATA ESTING INIT子状态下收到ID_PPP_APS_RECONN_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvPppReConnInd_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType   = TAF_APS_GetCurrPdpEntityRatType();

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

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
                    TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(ucPdpId, VOS_FALSE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_TRUE, VOS_TRUE, VOS_FALSE);
                }
                break;

            case TAF_APS_RAT_TYPE_1X:
            case TAF_APS_RAT_TYPE_NULL:
                /* DO强信号去HRPD建链；DO弱信号去1X建链 */
                if (VOS_FALSE == TAF_APS_GetIsHrpdDisabledFlag())
                {
                    TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(ucPdpId, VOS_TRUE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_TRUE, VOS_TRUE, VOS_FALSE);
                }
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvPppReConnInd_CdataEsting_Init: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* 如果不支持Hybrid，即只支持1X，则在1X下尝试建链 */
        TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_TRUE, VOS_TRUE, VOS_FALSE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterEpdszidReOrigReq_CdataEsting_Init
 功能描述  : During CDATA ESTING INIT state, Rcv ID_MSG_TAF_PS_EPDSZID_REORIG_REQ msg
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月04日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterEpdszidReOrigReq_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId  = TAF_APS_GetCurrFsmEntityPdpId();

    /* Save Sub Fsm Entry Msg */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* Get curr RatType */
    enCurrRatType  = TAF_APS_GetCurrPdpEntityRatType();

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_1X:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

            TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTING);

            TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_TRUE, VOS_FALSE, VOS_FALSE);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvPsEpdszidReOrigReq_CdataEsting_Init: Wrong RAT type!");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterHrpdTo1XHandOff_CdataEsting_Init
 功能描述  : CDATA ESTING INIT子状态下收到ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月25日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterHrpdTo1XHandOff_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId  = TAF_APS_GetCurrFsmEntityPdpId();

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 设置匹配1X的SrId */
    TAF_APS_SetPdpEntSrId(ucPdpId, TAF_APS_HRPD_DEFAULT_SR_ID);

    /* 主状态TAF_APS_STA_CDATA_ESTING */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTING);

    /* 在1X下建链 */
    TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_TRUE, VOS_FALSE, VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterHrpdTo1XHandOff_CdataEsting_Init
 功能描述  : CDATA ESTING INIT子状态下收到ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvPsInterDormantEnd1xSvc_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId  = TAF_APS_GetCurrFsmEntityPdpId();

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* DORMANT状态下，需要先重新建立链接 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTING);

    TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_TRUE, VOS_TRUE, VOS_FALSE);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccOrigDataCallCnf_CdataEsting_WaitXccOrigCallCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF子状态下
             收到ID_XCC_APS_ORIG_DATA_CALL_CNF消息的处理
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
VOS_UINT32 TAF_APS_RcvXccOrigDataCallCnf_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_ORIG_DATA_CALL_CNF_STRU    *pstOirgCallCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataServiceMode;

    /* 初始化 */
    pstOirgCallCnf  = (XCC_APS_ORIG_DATA_CALL_CNF_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    ucCid           = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    usClientId      = TAF_APS_GetPdpEntClientId(ucPdpId, ucCid);
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();

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

        /* 迁移TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED);

        TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_1X_NORMAL_DATA_CALL);

        enDataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();
        if (TAF_APS_RAT_TYPE_BUTT == enDataServiceMode)
        {
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                            "TAF_APS_RcvXccOrigDataCallCnf_CdataEsting_WaitXccOrigCallCnf: RAT type is Butt!");
        }

        /* 设置流控 */
        R_ITF_SetFlowLev(TAF_APS_MapRatType2VosRatMode(enDataServiceMode));

        TAF_APS_ProcEpdszidAfterRcvXccOrigDataCallCnf();

        /* Clear ReOrig Scene */
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
    }
    else
    {
        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_APS_MapXccCause(pstOirgCallCnf->enRslt);
        pstPdpEntity->sRssi   = pstOirgCallCnf->sRssi;

        if ((TAF_XCC_CAUSE_CCS_NOT_SUPPORT == pstOirgCallCnf->enRslt)
         || (TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MO_CALL == pstOirgCallCnf->enRslt)
         || (TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MT_CALL == pstOirgCallCnf->enRslt))
        {
            if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ) == pstEntryMsg->ulEventType)
            {
                TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_REORIG_AFTER_TC_RELEASE);
            }
        }

        /* 判断是否需要发起Silent Redial */
        if (VOS_TRUE == TAF_APS_IsNeedSilentRedial(pstPdpEntity->enCause, TAF_APS_RAT_TYPE_1X))
        {
            TAF_APS_CdataOrigRedialCount(ucPdpId, pstOirgCallCnf->enFailLayer);


            if (VOS_TRUE == TAF_APS_IsNeedRedial1xSystemAcquire(pstPdpEntity->enCause, pstPdpEntity->sRssi))
            {
                TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                                         usClientId,
                                                         TAF_MMA_1X_NORMAL_DATA_CALL,
                                                         pstPdpEntity->enCause);
            }

            /* 起SILENT_REDIAL_WAIT 4s定时器，如果此定时器超时，会尝试重拨 */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                               TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                               ucPdpId);

            /* 迁移TAF_APS_CDATA_ESTING_SUBSTA_WAIT_REDIAL子状态 */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL);
        }
        else
        {
            if ((pstOirgCallCnf->enRslt == TAF_XCC_CAUSE_NW_NORMAL_RELEASE)
            || ((pstOirgCallCnf->enRslt != TAF_XCC_CAUSE_NW_NORMAL_RELEASE) && (TAF_XCC_FAIL_LAYER_L3 == pstOirgCallCnf->enFailLayer)))
            {
                TAF_APS_ProcEpdszidAfterRcvXccOrigDataCallCnf();

            }

            if (pstOirgCallCnf->enRslt == TAF_XCC_CAUSE_NW_NORMAL_RELEASE)
            {
                TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);
            }

            /* 停止流程定时器 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

            /* 如果重拨周期定时器在运行，需要停止 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_1X_NORMAL_DATA_CALL);

            /* 不需要重拨时，建链失败的处理 */
            TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId, pstPdpEntity->enCause);
        }

    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccOrigCallCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccOrigCallCnf(
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

    /* 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* PPP状态ACTIVE, 由于PPP需要等链路建好之后再去做PPP去激活协商，只缓存入口消息, 继续建链流程 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 更换状态机入口消息，激活流程触发条件变为用户去激活触发建链 */
        TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

        /* 启动定时器TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF */
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                           TAF_APS_GetCdataPppDeactTimerLen(),
                           ucPdpId);
    }
    else
    {
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

        /* 停止激活定时器/重拨周期定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            TAF_APS_SndPppDeactInd(ucPdpId);

            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);
        }

        /* 更新之前发起建链的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

        /*------------------------------------------------------------------
           主状态迁移至TAF_APS_FSM_CDATA_DISCING
           子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

           在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_CALL_END_REQ消息
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccOrigCallCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF子状态下，
             收到TI_TAF_APS_CDATA_ESTING消息的处理
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
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 不需要重拨时，建链失败的处理 */
    TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                         TAF_PS_CAUSE_XCC_TIME_OUT);


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDataServiceConnInd_CdataEsting_WaitXccSoConnected
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态下，
             收到ID_XCC_APS_DATA_SERVICE_CONNECT_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvXccDataServiceConnInd_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_SERVICE_CONNECT_IND_STRU  *pstSoInd;
    VOS_UINT8                               ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstSoInd        = (XCC_APS_DATA_SERVICE_CONNECT_IND_STRU *)pstMsg;

    /* 停止流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* 更新SO、CONREF和PPP ID信息 */
    TAF_APS_SetPdpEntSo(ucPdpId, pstSoInd->enSo);
    TAF_APS_SetPdpEntConRef(ucPdpId, pstSoInd->ucConRef);

    /* 更新SR ID信息 */
    TAF_APS_SetPdpEntSrId(ucPdpId, pstSoInd->ucSrId);


    /* 通知外部模块当前的PS服务所在的模式 */
    TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_1X);

    /* 数据服务建链完成的处理 */
    TAF_APS_ProcCdataEstSucc_CdataEsting(ucPdpId);


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccSoConnected
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccSoConnected(
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

    /* 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* PPP状态ACTIVE, 由于PPP需要等链路建好之后再去做PPP去激活协商，只缓存入口消息, 继续建链流程 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 更换状态机入口消息，激活流程触发条件变为用户去激活触发建链 */
        TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

        /* 启动定时器TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF */
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                           TAF_APS_GetCdataPppDeactTimerLen(),
                           ucPdpId);
    }
    else
    {
        /* 停止激活定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            TAF_APS_SndPppDeactInd(ucPdpId);

            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);
        }

        /*------------------------------------------------------------------
           主状态迁移至TAF_APS_FSM_CDATA_DISCING
           子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

           在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_CALL_END_REQ消息
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitXccSoConnected
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态下
             收到ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitXccSoConnected(
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
 函 数 名  : TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccSoConnected
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态下
             收到ID_XCC_APS_DATA_CALL_DISC_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32


 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd      = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 停止流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* 保存原因值 */
    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* 不需重拨，处理建链失败的原因 */
    TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId, pstPdpEntity->enCause);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccSoConnected
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态下，
             收到TI_TAF_APS_CDATA_ESTING消息的处理
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
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 保存原因值 */
    pstPdpEntity->enCause = TAF_PS_CAUSE_XCC_TIME_OUT;

    /* 获取当前的状态机入口消息和EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();

    /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ消息 */
    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType)
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_USER_END,
                                       TAF_APS_INTER_END_CALL_REASON_USER_END,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);

        if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            /* 向PPP发送消息ID_APS_PPP_DEACT_IND */
            TAF_APS_SndPppDeactInd(ucPdpId);

            /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
        }
    }
    else if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ) == pstEntryMsg->ulEventType)
          || (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ) == pstEntryMsg->ulEventType))
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL,
                                       TAF_APS_INTER_END_CALL_REASON_SO_NEGOTIATE_TIME_OUT,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }
    else if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND) == pstEntryMsg->ulEventType)
    {
        /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_HANDOFF,
                                       TAF_APS_INTER_END_CALL_REASON_HANDOFF,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);

        if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            /* 向PPP发送消息ID_APS_PPP_DEACT_REQ */
            TAF_APS_SndPppDeactInd(ucPdpId);

            /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
        }
    }
    else
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_REEST_FAIL,
                                       TAF_APS_INTER_END_CALL_REASON_SO_NEGOTIATE_TIME_OUT,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccAnsCallCnf_CdataEsting_WaitXccAnsCallCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF子状态下,
             收到ID_XCC_APS_ANSWER_DATA_CALL_CNF消息的处理
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
VOS_UINT32 TAF_APS_RcvXccAnsCallCnf_CdataEsting_WaitXccAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_ANSWER_DATA_CALL_CNF_STRU  *pstAnsCallCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstAnsCallCnf   = (XCC_APS_ANSWER_DATA_CALL_CNF_STRU *)pstMsg;

    if (TAF_XCC_CAUSE_SUCCESS == pstAnsCallCnf->enRslt)
    {
        /* 迁移TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED);
    }
    else
    {
        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_APS_MapXccCause(pstAnsCallCnf->enRslt);

        /* 停止流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 建链失败的处理 */
        TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                             pstPdpEntity->enCause);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccAnsCallCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /*获取PDP ID */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* 更换状态机入口消息，激活流程触发条件变为用户去激活触发建链 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccAnsCallCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF子状态下,
             收到ID_XCC_APS_DATA_CALL_DISC_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 此为冲突场景，数据被叫时，用户拨打电话,否则XCC应该回复ANS_CALL_CNF消息 */

    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd      = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity    = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDiscInd   = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* 停止流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* 不需要重拨时，建链失败的处理 */
    TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                         pstPdpEntity->enCause);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccAnsCallCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF子状态下,
             收到TI_TAF_APS_CDATA_ESTING消息的处理
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
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 不需要重拨时，建链失败的处理 */
    TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                                TAF_PS_CAUSE_XCC_TIME_OUT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccCallConnectedInd_CdataEsting_WaitXccCallConnectedInd
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND子状态下，
             收到ID_XCC_APS_DATA_CALL_CONN_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvXccCallConnectedInd_CdataEsting_WaitXccCallConnectedInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_CONN_IND_STRU    *pstCallConnInd;
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    pstCallConnInd  = (XCC_APS_DATA_CALL_CONN_IND_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 更新CONREF信息 */
    TAF_APS_SetPdpEntConRef(ucPdpId, pstCallConnInd->ucConRef);

    /* 迁移TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态 */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccCallConnectedInd
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccCallConnectedInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* 更换状态机入口消息，激活流程触发条件变为用户去激活触发建链 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccCallConnectedInd
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND子状态下
             收到ID_XCC_APS_DATA_CALL_CONN_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月17日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccCallConnectedInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 此为冲突场景，数据被叫时，用户拨打电话 */

    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd      = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity    = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDiscInd   = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* 停止流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* 不需要重拨时，建链失败的处理 */
    TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                         pstPdpEntity->enCause);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiRedialIntervalExpired_CdataEsting_WaitRedial
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL子状态下,
             收到TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL消息,发起重拨
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiRedialIntervalExpired_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT32                          ulRemainTimeLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucIsDormDataCall;
    VOS_UINT8                           ucDrsFlag;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enSdcServiceStatus;
    VOS_UINT8                           ucDoQuickAcqProtect;


    ucDrsFlag           = VOS_TRUE;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg         = TAF_APS_GetCurrSubFsmMsgAddr();
    enSdcServiceStatus  = TAF_APS_GetHrpdServiceStatus();
    ucDoQuickAcqProtect = TAF_APS_GetDoQuickAcqProtectFlag(ucPdpId);

    if (((VOS_FALSE == TAF_APS_GetClDelaySearch()) && (VOS_FALSE == ucDoQuickAcqProtect))
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

            /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF);

            return VOS_TRUE;
        }

        /* 判断是否可以发起1X建链 */
        if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_1X))
        {
            if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ) == pstEntryMsg->ulEventType)
            {
                /* Esting Fsm is started, Set Re-Orig Secne BuTT */
                TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
            }

            ucDrsFlag                   = TAF_APS_GetDrsValueByScene(pstEntryMsg->ulEventType);
            ucIsDormDataCall            = TAF_APS_IsRedialCallFromDormantState(ucPdpId);

            TAF_APS_ProcCdataRedialReOrig_CdataEsting_1XMode(ucIsDormDataCall, ucDrsFlag);

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

        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL);
    }
    else
    {
        /* 停止流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 如果重拨周期定时器在运行，需要停止 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* 通知搜网模块结束搜网 */
        if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

            TAF_APS_SetPdpEntCdataEstFailCause(ucPdpId, TAF_APS_RAT_TYPE_1X);
        }
        else
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

            TAF_APS_SetPdpEntCdataEstFailCause(ucPdpId, TAF_APS_RAT_TYPE_HRPD);
        }

        pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        /* 不需要重拨时，建链失败的处理 */
        TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                             pstPdpEntity->enCause);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataEsting_WaitRedial
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL子状态下,
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : g00261581
    修改内容   : 新生成函数

  2.日    期   : 2015年11月18日
    作    者   : g00261581
    修改内容   : 重拨过程中收到去激活，此时由于没有链路，直接通知PPP本地去激
                 活，上报去激活成功

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();
    pstAppMsg     = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* 停止激活总定时器/重拨周期/重拨间隔定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
    {
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
    }

    if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
    {
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
    }

    /* 如果PPP已激活或PPP在激活协商过程中 */
    if (TAF_APS_CDATA_PPP_STATE_INACTIVE != TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        TAF_APS_SndPppDeactInd(ucPdpId);

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId))
        {
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);
        }
    }

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    /* 给用户返回DEACTIVE_CNF事件 */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* 退出子状态状态机 */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterSrvStaChangeReq_CdataEsting_WaitRedial
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL子状态下,
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月24日
    作    者   : c00299063
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterSrvStaChangeReq_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST                              *pstPdpEntity = VOS_NULL_PTR;
    VOS_UINT8                                               ucPdpId;
    VOS_UINT8                                               ucIsDormDataCall;
    VOS_UINT8                                               ucDrsFlag;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstSvcStaChangeReq = VOS_NULL_PTR;
    VOS_UINT8                                               ucDoQuickAcqProtect;
    VOS_UINT8                                               ucCid;

    ucDrsFlag    = VOS_TRUE;
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg  = TAF_APS_GetCurrSubFsmMsgAddr();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 获取消息内容 */
    pstSvcStaChangeReq = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;


    /*判断是否需要立即重拨 */
    if ((VOS_FALSE == TAF_APS_IsNeedRedialImmediately(pstPdpEntity->enCause, pstPdpEntity->sRssi))
     && ((TAF_APS_RAT_TYPE_HRPD == pstSvcStaChangeReq->enRatType)
      || (TAF_APS_RAT_TYPE_1X  == pstSvcStaChangeReq->enRatType)))
    {
        return VOS_TRUE;
    }

    switch(pstSvcStaChangeReq->enRatType)
    {
        /* 判断HRPD有服务 */
        case TAF_APS_RAT_TYPE_HRPD:
            /* 判断是否可以发起HRPD建链 */
            if(VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_HRPD))
            {
                /* 停止定时器 */
                TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

                TAF_APS_SetDoQuickAcqProtectFlag(ucPdpId, VOS_FALSE);

                /* Send Orig Data Call Req To HSM */
                TAF_APS_SndHsmOrigReq(ucPdpId);

                if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
                {
                    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
                    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
                }

                TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_HRPD);

                /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF */
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF);
            }

            break;

        /* 判断1X服务 */
        case TAF_APS_RAT_TYPE_1X:
            ucDoQuickAcqProtect = TAF_APS_GetDoQuickAcqProtectFlag(ucPdpId);

            if ((VOS_TRUE == ucDoQuickAcqProtect)
             && (TAF_APS_INTER_SERVICE_RESULT_CL == pstSvcStaChangeReq->ucServiceType))
            {
                ucCid = TAF_APS_GetPdpEntCurrCid(ucPdpId);

                TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                                         TAF_APS_GetPdpEntClientId(ucPdpId, ucCid),
                                                         TAF_MMA_DO_NORMAL_DATA_CALL,
                                                         TAF_PS_CAUSE_HRPD_NO_SERVICE);

                return VOS_TRUE;
            }

            if ((VOS_FALSE == TAF_APS_GetClDelaySearch())
             && (VOS_FALSE == ucDoQuickAcqProtect))
            {
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

                    TAF_APS_ProcCdataRedialReOrig_CdataEsting_1XMode(ucIsDormDataCall, ucDrsFlag);
                }
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

            /* 不需要重拨时，建链失败的处理 */
            TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                                 TAF_PS_CAUSE_RAT_TYPE_CHANGE);
            /* 通知外部模块PS模式切换 */
            TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

            break;

        default:
            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvMmaHrpdDataCallSysAcqInd_CdataEsting_WaitRedial
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL子状态下,
             收到ID_MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月24日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMmaHrpdDataCallSysAcqInd_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;
    VOS_UINT8                                               ucPdpId;
    VOS_UINT8                                               ucIsDormDataCall;
    VOS_UINT8                                               ucDrsFlag;
    MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU                *pstHrpdSysAcqInd = VOS_NULL_PTR;

    ucDrsFlag    = VOS_TRUE;
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg  = TAF_APS_GetCurrSubFsmMsgAddr();
    pstHrpdSysAcqInd = (MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU *)pstMsg;

    TAF_APS_SetDoQuickAcqProtectFlag(ucPdpId, VOS_FALSE);

    if (MMA_TAF_HRPD_ACQUIRED_RESULT_SUCC == pstHrpdSysAcqInd->enHrpdSysAcqRst)
    {
        if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_ConvertMmaRatType(pstHrpdSysAcqInd->enRatType))
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
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF);

        }
        else
        {
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

            /* 不需要重拨时，建链失败的处理 */
            TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                                 TAF_PS_CAUSE_RAT_TYPE_CHANGE);
            /* 通知外部模块PS模式切换 */
            TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

        }

        return VOS_TRUE;
    }
    else if (MMA_TAF_HRPD_ACQUIRED_RESULT_NO_RF == pstHrpdSysAcqInd->enHrpdSysAcqRst)
    {
        return VOS_TRUE;
    }
    else
    {
        if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_1X))
        {
            /* 停止定时器 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

            if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ) == pstEntryMsg->ulEventType)
            {
                /* Esting Fsm is started, Set Re-Orig Secne BuTT */
                TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
            }

            ucDrsFlag                   = TAF_APS_GetDrsValueByScene(pstEntryMsg->ulEventType);
            ucIsDormDataCall            = TAF_APS_IsRedialCallFromDormantState(ucPdpId);

            TAF_APS_ProcCdataRedialReOrig_CdataEsting_1XMode(ucIsDormDataCall, ucDrsFlag);
        }

        return VOS_TRUE;

    }

}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccIncomingCallInd_CdataEsting_WaitRedial
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL子状态下,
             收到ID_XCC_APS_INCOMING_CALL_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_INCOMING_CALL_IND_STRU     *pstIncomingCall;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstIncomingCall = (XCC_APS_INCOMING_CALL_IND_STRU *)pstMsg;

    /* 此场景下，不能保存入口消息 */

    /* 记录当前建立数据服务的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

    /* 总的激活定时器TAF_APS_STA_CDATA_ESTING此时在运行，需要先关闭再重新运行 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING, ucPdpId))
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, TI_TAF_APS_CDATA_ESTING_LEN, ucPdpId);
    }

    /* 停止重拨定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

    /* 根据ByePass值进行处理 */
    if (VOS_TRUE == pstIncomingCall->ucIsAlertAnsByPass)
    {
        /* 迁TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND子状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND);
    }
    else
    {
        /* 发送ID_APS_XCC_ANSWER_DATA_CALL_REQ */
        TAF_APS_SndXccAnswerDataCallReq(ucPdpId);

        /* 迁TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF子状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmConnectInd_CdataEsting_WaitRedial
 功能描述  : 等待Redial阶段收到HSM发送的ID_HSM_APS_CONNECT_IND消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月7日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmConnectInd_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止重拨间隔定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

    /* 记录当前建立数据服务的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

    /* 通知PPPC当前的PS服务所在的模式 */
    TAF_APS_SndPppModeChangeNotify(ucPdpId);

    /* 通知CDS当前建立的数据服务模式 */
    TAF_APS_SndCdsModeChangeInd(TAF_APS_RAT_TYPE_HRPD);

    /* 数据服务建链完成的处理 */
    TAF_APS_ProcCdataEstSucc_CdataEsting(ucPdpId);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode
 功能描述  : 处理用户激活/上行数传/去激活请求时的，拨号处理
 输入参数  : VOS_UINT8                           ucIsDormDataCall
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月21日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(
    VOS_UINT8                           ucIsDormDataCall,
    VOS_UINT8                           ucDrsFlg,
    VOS_UINT8                           ucHrpdHandOff1xFlg
)
{
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucCid;
    VOS_UINT16                          usClientId;

    /* Get Pdp Fsm Entity */
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->stCdataInfo.ucCallId              = ucPdpId + 1;
    pstPdpEntity->stCdataInfo.enSo                  = TAF_APS_GetFsmCtxCdataSoInitType();
    pstPdpEntity->stCdataInfo.ucDrsFlg              = ucDrsFlg;
    pstPdpEntity->stCdataInfo.ucIsDormDataCall      = ucIsDormDataCall;
    pstPdpEntity->stCdataInfo.ucIsL2ErrReOrig       = VOS_FALSE;
    pstPdpEntity->stCdataInfo.ucReOrigCount         = 0;

    ucCid      = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    usClientId = TAF_APS_GetPdpEntClientId(ucPdpId, ucCid);

    /* Send start Ntf to MMA */
    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_1X_NORMAL_DATA_CALL);

    TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_1X);

    /* Start Timer TI_TAF_APS_CDATA_ESTING */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING, ucPdpId);
    if (TAF_APS_TIMER_STATUS_RUNING != enTimerStatus)
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, TI_TAF_APS_CDATA_ESTING_LEN, ucPdpId);
    }

    /* Start Timer TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
    if (TAF_APS_TIMER_STATUS_RUNING != enTimerStatus)
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD_LEN, ucPdpId);
    }

    /* 判断是否可以发起1X建链 */
    if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_1X))
    {
        /* Send Orig Data Call Req To Xcc */
        TAF_APS_SndXccOrigDataCallReq(ucPdpId, ucHrpdHandOff1xFlg);

        /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF);
    }
    else
    {


        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                           ucPdpId);

        /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcCdataRedialReOrig_CdataEsting_1XMode
 功能描述  : 处理用户激活/上行数传/去激活请求时的，拨号处理
 输入参数  : VOS_UINT8                           ucIsDormDataCall
             VOS_UINT8                           ucDrsFlg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月25日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_ProcCdataRedialReOrig_CdataEsting_1XMode(
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

    /* 子状态迁移至TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF);

    return VOS_TRUE;


}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcCdataEstSucc_CdataEsting
 功能描述  : CDATA数据服务建链成功的处理
 输入参数  : VOS_UINT8                           ucPdpId
             TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月15日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcCdataEstSucc_CdataEsting(
    VOS_UINT8                           ucPdpId
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 初始化 */
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();

    /* 如果重拨周期定时器在运行，需要关闭重拨周期定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTED);

    switch(pstEntryMsg->ulEventType)
    {
        /* INACTIVE状态下用户发生激活触发的数据服务建立 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ):
            /* CDMA HRPD模式下目前只支持一个承载，默认rabId为5 */
            pstPdpEntity->ucNsapi       = TAF_APS_DEFAULT_CDATA_RAB_ID;
            pstPdpEntity->PdpNsapiFlag  = VOS_TRUE;
            pstPdpEntity->ActType       = APS_PDP_ACT_PRI;
            TAF_APS_SetPdpEntCdataPdnId(ucPdpId, TAF_APS_DEFAULT_CDATA_PDN_ID);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 通知RLP做初始化 */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            if (TAF_PS_CDATA_DIAL_MODE_RELAY == TAF_APS_GetFsmCtxCdataDialMode())
            {
                /**********************************************************************/
                /* 中继模式，不需要再做PPP协商，APS状态机直接迁移至TAF_APS_STA_ACTIVE */
                /**********************************************************************/
                /* 给用户上报ACTIVATE_CNF事件 */
                TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

                /* 设置CDATA PS域服务状态为ACTIVE状态 */
                TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVE);

                /* 配置IP过滤 */
                TAF_APS_IpfConfigUlFilter(ucPdpId);

                /* 启动流量上报定时器 */
                TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

                /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

                TAF_APS_QuitCurrSubFsm();

            }
            else
            {
                if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
                {
                    /* 链路重建是由PPPC模块触发，之前的PPP激活协商还未结束,通知PPPC链路已重建成功 */
                    TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_CONNECTED);
                }
                else
                {
                    /* 发送ID_APS_PPP_ACT_REG消息给PPP模块 */
                    TAF_APS_SndPppActReq(ucPdpId);

                    /* 起激活定时器 */
                    TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF,
                                       TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF_LEN,
                                       ucPdpId);

                    /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_ACTIVATING */
                    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_ACTIVATING);
                }

                /* 迁移TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF子状态 */
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF);
            }

            break;

        /* DORMANT状态下用户去激活触发的数据服务重建，走断开流程 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ):
            /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
            TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_USER_END,
                                           TAF_APS_INTER_END_CALL_REASON_USER_END,
                                           ucPdpId,
                                           TI_TAF_APS_CDATA_DISCING_LEN);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 通知RLP做初始化 */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            /* 启动流量上报定时器 */
            TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

            /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();

            break;
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND):
            /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
            TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_HANDOFF,
                                           TAF_APS_INTER_END_CALL_REASON_HANDOFF,
                                           ucPdpId,
                                           TI_TAF_APS_CDATA_DISCING_LEN);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 通知RLP做初始化 */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            /* 启动流量上报定时器 */
            TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

            /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT状态下用户上行数传触发的数据服务重建，直接迁ACTIVE状态 */
        case TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ):
        /* DORMANT状态下，HRPD丢网 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ):
        case TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_RECONN_IND):
            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 通知RLP做初始化 */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }



            /* 启动流量上报定时器 */
            TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

            /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* Notify ppp link reBuild succ */
            TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_CONNECTED);

            /* 给CDS发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息 */
            TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT状态下网侧触发的数据服务重建，直接迁ACTIVE状态 */
        case TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_INCOMING_CALL_IND):

            /* TODO:给用户上报出DORMANT状态 */

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 通知RLP做初始化 */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            /* 启动流量上报定时器 */
            TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));


            /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* 给CDS发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息 */
            TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

            TAF_APS_QuitCurrSubFsm();

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_ProcCdataEstSucc_CdataEsting:Wrong Msg Entry");
            break;
    }

}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcEhrpdPdnActSucc_CdataEsting
 功能描述  : EHRPD下单个PDN激活成功的处理
 输入参数  : VOS_UINT8                           ucPdpId
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月27日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcEhrpdPdnActSucc_CdataEsting(
    VOS_UINT8                           ucPdpId,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_CNF_STRU     *pstPdnActCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucCid;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataServiceMode;
    MN_APS_PDP_IPV6_DNS_STRU           *pstPdpIpv6Dns;

    /* 初始化 */
    pstPdnActCnf    = (EHSM_APS_PDN_ACTIVATE_CNF_STRU *)pstMsg;
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    ucCid           = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* CDMA EHRPD模式下承载 */
    pstPdpEntity->ucNsapi       = pstPdnActCnf->ucRabId;
    pstPdpEntity->PdpNsapiFlag  = VOS_TRUE;
    pstPdpEntity->ActType       = APS_PDP_ACT_PRI;

    /* 记录当前建立数据服务的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    /* 通知外部模块当前的PS服务所在的模式 */
    TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_EHRPD);

    /* 记录PDNID Pdnadrr Apn Dns */
    TAF_APS_SetPdpEntCdataPdnId(ucPdpId, pstPdnActCnf->ucPdnId);
    TAF_APS_UpdateCdataEhsmPdnInfo(pstPdpEntity,
                                   &(pstPdnActCnf->stPdnAddr),
                                   &(pstPdnActCnf->stApn),
                                   &(pstPdnActCnf->stIpv4Dns));


    /* 不需要获取Ipv4 DNS */
    if (((VOS_TRUE == pstPdnActCnf->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE == pstPdnActCnf->stIpv4Dns.bitOpIpv4SecDNS))
      && (EHSM_APS_PDN_TYPE_IPV4   == pstPdnActCnf->stPdnAddr.enPdnType))
    {
        /* 给用户上报ACTIVATE_CNF事件 */
        TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
    }
    else if (((VOS_TRUE == pstPdnActCnf->stIpv6Dns.bitOpIpv6PrimDNS) || (VOS_TRUE == pstPdnActCnf->stIpv6Dns.bitOpIpv6SecDNS))
            && (EHSM_APS_PDN_TYPE_IPV6 == pstPdnActCnf->stPdnAddr.enPdnType))
    {
        TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

        pstPdpIpv6Dns = (MN_APS_PDP_IPV6_DNS_STRU *)&pstPdnActCnf->stIpv6Dns;

        TAF_APS_UpdateCdataIpv6Dns(pstPdpEntity, pstPdpIpv6Dns);

        /* 在不做dhcp协商，但是IPV6的地址必然需要协商，在IPV6地址协商成功后，需要上报，故刷新次变量 */
        pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_TRUE;

        /* 给用户上报ACTIVATE_CNF事件 */
        TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
    }
    else if (((VOS_TRUE == pstPdnActCnf->stIpv6Dns.bitOpIpv6PrimDNS) || (VOS_TRUE == pstPdnActCnf->stIpv6Dns.bitOpIpv6SecDNS))
           && ((VOS_TRUE == pstPdnActCnf->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE == pstPdnActCnf->stIpv4Dns.bitOpIpv4SecDNS))
           && (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActCnf->stPdnAddr.enPdnType))
    {
        TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

        pstPdpIpv6Dns = (MN_APS_PDP_IPV6_DNS_STRU *)&pstPdnActCnf->stIpv6Dns;

        TAF_APS_UpdateCdataIpv6Dns(pstPdpEntity, pstPdpIpv6Dns);

        /* 在不做dhcp协商，但是IPV6的地址必然需要协商，在IPV6地址协商成功后，需要上报，故刷新次变量 */
        pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_TRUE;

        /* 给用户上报ACTIVATE_CNF事件 */
        TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
    }
    else
    {
        /* 需要获取Ipv4 DNS */
        if (((EHSM_APS_PDN_TYPE_IPV4   == pstPdnActCnf->stPdnAddr.enPdnType) || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActCnf->stPdnAddr.enPdnType))
         && ((VOS_TRUE != pstPdnActCnf->stIpv4Dns.bitOpIpv4PrimDNS) && (VOS_TRUE != pstPdnActCnf->stIpv4Dns.bitOpIpv4SecDNS)))
        {
            /* 给DHCP发送GET_DNS_IPV4消息  */
            TAF_APS_SndDhcpDnsIpv4Req(ucPdpId);

            pstPdpEntity->ucNeedGetDnsFlg = VOS_TRUE;
        }

        /* 需要获取Ipv6 DNS，Ipv4,Ipv4v6类型 */
        if (((EHSM_APS_PDN_TYPE_IPV6   == pstPdnActCnf->stPdnAddr.enPdnType) || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActCnf->stPdnAddr.enPdnType))
         && ((VOS_TRUE != pstPdnActCnf->stIpv6Dns.bitOpIpv6PrimDNS) && (VOS_TRUE != pstPdnActCnf->stIpv6Dns.bitOpIpv6SecDNS)))
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            TAF_APS_SndDhcpDnsIpv6Req(ucPdpId);

            pstPdpEntity->ucNeedGetDnsFlg = VOS_TRUE;
        }
    }

    /* 配置IP过滤 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    enDataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();
    if (TAF_APS_RAT_TYPE_BUTT == enDataServiceMode)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
                        "TAF_APS_ProcEhrpdPdnActSucc_CdataEsting: RAT type is Butt!");
    }

    /* 设置流控 */
    R_ITF_SetFlowLev(TAF_APS_MapRatType2VosRatMode(enDataServiceMode));

    /* 启动流量上报定时器 */
    TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcCdataEstFail_CdataEsting
 功能描述  : CDATA数据服务建链时失败或超时的处理
 输入参数  : VOS_UINT8                               ucPdpId
             TAF_PS_CAUSE_ENUM_UINT32                enCause
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月23日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_ProcCdataEstFail_CdataEsting(
    VOS_UINT8                               ucPdpId,
    TAF_PS_CAUSE_ENUM_UINT32                enCause
)
{
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8      enCdataPppState;

    /* 获取当前的状态机入口消息和EVENTTYPE */
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    enCdataPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_NO_LINK);

    switch(pstEntryMsg->ulEventType)
    {
        /* INACTIVE状态下用户去激活触发的数据服务，走断开流程 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ):
            /* 给用户返回ACTIVE_REJ事件 */
            TAF_APS_SndPdpActivateRej(ucPdpId, enCause);

            /* 如果PPP已经在激活协商过程中，通知PPP去激活 */
            if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == enCdataPppState)
            {
                TAF_APS_SndPppDeactInd(ucPdpId);

                TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);
            }

            /* 释放APS资源 */
            Aps_ReleaseApsResource(ucPdpId);

            /* 主状态迁移至TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* 退出子状态状态机 */
            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT状态下由于其他消息(例如CDS数传)触发重建，重建过程中收到用户去激活，
           保存用户去激活的入口消息 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ):
            /* 给用户返回DEACTIVE_CNF事件 */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

            TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF, ucPdpId);

            /* 如果PPP已激活或PPP在激活协商过程中 */
            if (TAF_APS_CDATA_PPP_STATE_INACTIVE != enCdataPppState)
            {
                TAF_APS_SndPppDeactInd(ucPdpId);

                if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId))
                {
                    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);
                }
            }

            /* 释放APS资源 */
            Aps_ReleaseApsResource(ucPdpId);

            /* 配置IP过滤 */
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            /* 主状态迁移至TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* 退出子状态状态机 */
            TAF_APS_QuitCurrSubFsm();
            break;

        /* DORMANT状态下发生数据服务模式切换，建链失败 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND):

            /* 上报去激活的事件 */
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

            /* 设置当前数据服务模式 */
            TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

            /* 本地去激活 */
            TAF_APS_LocalReleaseProc(ucPdpId);

            /* 退出子状态状态机 */
            TAF_APS_QuitCurrSubFsm();

            break;

        case TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ):
        case TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_RECONN_IND):
            if (VOS_TRUE == TAF_APS_IsCdataLocalReleaseCause(enCause))
            {
                /* 停止流量统计 */
                /* TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi); */

                /* 上报去激活的事件 */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, enCause);

                if (TAF_APS_CDATA_PPP_STATE_INACTIVE != TAF_APS_GetPdpEntPppState(ucPdpId))
                {
                    TAF_APS_SndPppDeactInd(ucPdpId);

                    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
                }

                /* 本地去激活 */
                TAF_APS_LocalReleaseProc(ucPdpId);
            }
            else
            {
                /* 主状态迁移至TAF_APS_STA_DORMANT */
                TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);

                if (TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND) == pstEntryMsg->ulEventType)
                {
                    /* 给CDS发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息 */
                    TAF_APS_SndCdsFreeBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
                }
            }

            /* 退出子状态状态机 */
            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT状态下网络发起的数据服务重建，直接迁DORMANT状态 */
        case TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_INCOMING_CALL_IND):

            if (TAF_PS_CAUSE_XCC_AS_SO_REJ == enCause)
            {
                /* 停止流量统计 */
                /* TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi); */

                /* 上报去激活的事件 */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, enCause);

                /* 释放APS资源 */
                Aps_ReleaseApsResource(ucPdpId);

                /* 配置IP过滤 */
                TAF_APS_IpfConfigUlFilter(ucPdpId);

                /* 主状态迁移至TAF_APS_STA_INACTIVE */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
            }
            else
            {
                /* 主状态迁移至TAF_APS_STA_DORMANT */
                TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);

                /* 给CDS发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息 */
                TAF_APS_SndCdsFreeBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
            }

            /* 退出子状态状态机 */
            TAF_APS_QuitCurrSubFsm();

            break;
        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_ProcCdataEstFail_CdataEsting:Wrong Msg Entry");
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode
 功能描述  : HRPD模式下的拨号
 输入参数  : VOS_UINT8                           ucPdpId
             VOS_UINT32                          ulNeedSearchSys
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月5日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(
    VOS_UINT8                           ucPdpId,
    VOS_UINT32                          ulDoQuickAcq
)
{
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucCid;
    VOS_UINT16                          usClientId;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enSdcServiceStatus;
    VOS_UINT32                          ulClDelaySearch;

    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    ucCid           = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    usClientId      = TAF_APS_GetPdpEntClientId(ucPdpId, ucCid);

    /* 拨号参数 */
    pstPdpEntity->stCdataInfo.ucCallId = ucPdpId + 1;

    /* Send start Ntf to MMA */
    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_DO_NORMAL_DATA_CALL);

    TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_HRPD);

    /* Start Timer TI_TAF_APS_CDATA_ESTING */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING, ucPdpId);
    if (TAF_APS_TIMER_STATUS_RUNING != enTimerStatus)
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, TI_TAF_APS_CDATA_ESTING_LEN, ucPdpId);
    }

    /* Start Timer TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
    if (TAF_APS_TIMER_STATUS_RUNING != enTimerStatus)
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD_LEN,
                           ucPdpId);
    }

    /* 判断是否可以发起HRPD建链 */
    if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_HRPD))
    {
        /* Send Orig Data Call Req To HSM */
        TAF_APS_SndHsmOrigReq(ucPdpId);

        /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF);
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
                                                     usClientId,
                                                     TAF_MMA_DO_NORMAL_DATA_CALL,
                                                     TAF_PS_CAUSE_HRPD_NO_SERVICE);

        }

        TAF_APS_SetDoQuickAcqProtectFlag(ucPdpId, VOS_TRUE);

        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                           ucPdpId);

        /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL);
    }
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode
 功能描述  : EHRPD模式下的拨号
 输入参数  : VOS_UINT8                           ucPdpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月14日
    作    者   : y00314741
    修改内容   : 新生成函数

  2.日    期   : 2015年08月24日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode(
    VOS_UINT8                           ucPdpId,
    TAF_APS_ORIG_TYPE_ENUM_UINT8        enDailType

)
{
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucCid;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataServiceType;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT32                          ulRemainTimerLen;

    /* 获取APS，Cid, ClientId */
    ucCid = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    ulRemainTimerLen    = TAF_APS_GetCallRemainTmrLen(ucCid);

    if (0 != ulRemainTimerLen)
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode: Remain TimerLen !=0");
    }

    /* 如果Auto Attach开关打开，需要等待EHRPD自动Attach的结果 */
    if (VOS_TRUE == TAF_APS_GetEhrpdAutoAttachFlag())
    {
        /* 如果没有承载，或者由L切到C，则缓存该呼叫建立请求 */
        enDataServiceType = TAF_APS_GetCurrPdpEntityDataServiceMode();
        if ((VOS_FALSE == TAF_APS_IsAnyBearerExist())
         || (TAF_APS_RAT_TYPE_EHRPD != enDataServiceType))
        {
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND);

            enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING, ucPdpId);
            if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
            {
                ulTimerLen = (0 != ulRemainTimerLen) ?
                             ulRemainTimerLen : TI_TAF_APS_CDATA_ESTING_LEN;

                TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, ulTimerLen, ucPdpId);
                TAF_APS_SetCallRemainTmrLen(ucCid, 0);
            }

            return;
        }
    }
    else
    {
        /* 如果EHRPD AUTO ATTACH开关关闭，且当前无承载，需要发起Initial Attach */
        if (VOS_FALSE == TAF_APS_IsAnyBearerExist())
        {
            TAF_APS_SndEhsmPdnAttachReq(ucPdpId, enDailType);

            /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ATTACH_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ATTACH_CNF);

            enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING, ucPdpId);
            if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
            {
                ulTimerLen = (0 != ulRemainTimerLen) ?
                             ulRemainTimerLen : TI_TAF_APS_CDATA_ESTING_LEN;

                TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, ulTimerLen, ucPdpId);
                TAF_APS_SetCallRemainTmrLen(ucCid, 0);
            }

            return;
        }
    }

    /* Send pdn activate Call Req To EHSM */
    TAF_APS_SndEhsmPdnActReq(ucPdpId, enDailType);

    /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF);

    /* Start Timer TI_TAF_APS_CDATA_ESTING */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING, ucPdpId);
    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        ulTimerLen = (0 != ulRemainTimerLen) ?
                     ulRemainTimerLen : TI_TAF_APS_CDATA_ESTING_LEN;

        TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, ulTimerLen, ucPdpId);
        TAF_APS_SetCallRemainTmrLen(ucCid, 0);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmOrigCnf_CdataEsting_WaitHsmOrigCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF子状态下
             收到ID_HSM_APS_ORIG_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月3日
    作    者   : Y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmOrigCnf_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_ORIG_CNF_STRU              *pstOirgCallCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataServiceMode;

    /* 初始化 */
    pstOirgCallCnf  = (HSM_APS_ORIG_CNF_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    ucCid           = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    usClientId      = TAF_APS_GetPdpEntClientId(ucPdpId, ucCid);

    if (HSM_APS_CAUSE_SUCCESS == pstOirgCallCnf->enResult)
    {
        /* 记录当前建立数据服务的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);


        TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_DO_NORMAL_DATA_CALL);

        /* 通知外部模块当前的PS服务所在的模式 */
        TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_HRPD);

        /* 数据服务建链完成的处理 */
        TAF_APS_ProcCdataEstSucc_CdataEsting(ucPdpId);


        enDataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();
        if (TAF_APS_RAT_TYPE_BUTT == enDataServiceMode)
        {
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                            "TAF_APS_RcvHsmOrigCnf_CdataEsting_WaitHsmOrigCnf: RAT type is Butt!");
        }

        /* 设置流控 */
        R_ITF_SetFlowLev(TAF_APS_MapRatType2VosRatMode(enDataServiceMode));
    }
    else
    {
        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_APS_MapHsmCause(pstOirgCallCnf->enResult);

        /* 判断是否需要发起Silent Redial */
        if (VOS_TRUE == TAF_APS_IsNeedSilentRedial(pstPdpEntity->enCause, TAF_APS_RAT_TYPE_HRPD))
        {
#if 0
            if (VOS_TRUE == TAF_APS_IsNeedRedialHrpdSystemAcquire(pstPdpEntity->enCause))
            {
                /* 建链过程中失败，暂不通知MMA搜网 */
                TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                                       usClientId,
                                                       TAF_MMA_DO_NORMAL_DATA_CALL,
                                                       pstPdpEntity->enCause);

                 /* 需要等待系统重新搜网后再重播 */
                 TAF_APS_SET_CDATA_WAIT_SYS_REQUIRE(VOS_TRUE);
            }
#endif
            /* 起SILENT_REDIAL_WAIT 4s定时器，如果此定时器超时，会尝试重拨 */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                               TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                               ucPdpId);

            /* 迁移TAF_APS_CDATA_ESTING_SUBSTA_WAIT_REDIAL子状态 */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL);
        }
        else
        {
            /* 停止流程定时器 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

            /* 如果重拨周期定时器在运行，需要停止 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_DO_NORMAL_DATA_CALL);

            /* 不需要重拨时，建链失败的处理 */
            TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId, pstPdpEntity->enCause);
        }

    }
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataEsting_WaitHsmOrigCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF子状态下
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
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitHsmOrigCnf(
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

    /* 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* PPP状态ACTIVE, 由于PPP需要等链路建好之后再去做PPP去激活协商，只缓存入口消息, 继续建链流程 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 更换状态机入口消息，激活流程触发条件变为用户去激活触发建链 */
        TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

        /* 启动定时器TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF */
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_DISCING_WAIT_PPP_DEACT_CNF,
                           TAF_APS_GetCdataPppDeactTimerLen(),
                           ucPdpId);
    }
    else
    {
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

        /* 停止激活定时器/重拨周期定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            TAF_APS_SndPppDeactInd(ucPdpId);

            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);
        }

        /* 更新之前发起建链的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        /*------------------------------------------------------------------
           主状态迁移至TAF_APS_FSM_CDATA_DISCING
           子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

           在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_CALL_END_REQ消息
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataEsting_WaitHsmOrigCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF子状态下
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
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 建链失败的处理 */
    TAF_APS_ProcCdataEstFail_CdataEsting(TAF_APS_GetCurrFsmEntityPdpId(),
                                         TAF_PS_CAUSE_HSM_TIME_OUT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterEndCdmaCallReq_WaitHsmOrigCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF子状态下
             收到ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月16日
    作    者   : y00218312
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_WaitHsmOrigCnf(
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
 函 数 名  : TAF_APS_RcvEhsmPdnActCnf_CdataEsting_WaitEhsmPdnActCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF子状态下
             收到ID_EHSM_APS_PDN_ACTIVATE_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月14日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnActCnf_CdataEsting_WaitEhsmPdnActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_CNF_STRU     *pstPdnActCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    pstPdnActCnf    = (EHSM_APS_PDN_ACTIVATE_CNF_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (EHSM_APS_CAUSE_SUCCESS == pstPdnActCnf->enCause)
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 数据建立成功处理 */
        TAF_APS_ProcEhrpdPdnActSucc_CdataEsting(ucPdpId, pstMsg);
    }
    else if (EHSM_APS_CAUSE_EHRPD_SUSPEND == pstPdnActCnf->enCause)
    {
        /* 迁激活Suspend状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND);
    }
    else
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_APS_MapEhsmCause(pstPdnActCnf->enCause);



        /* 不需要重拨时，建链失败的处理 */
        TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId, pstPdpEntity->enCause);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataEsting_WaitEhsmPdnActCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月14日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitEhsmPdnActCnf(
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

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /*------------------------------------------------------------------
    主状态迁移至TAF_APS_FSM_CDATA_DISCING
    子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

    在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
    处理ID_MSG_TAF_PS_CALL_END_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitEhsmPdnActCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF子状态下
             收到TI_TAF_APS_CDATA_ESTING消息的处理
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
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitEhsmPdnActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取实体信息 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 通知ehsm本地去激活 */
    TAF_APS_SndEhsmLocDeactNtf(ucPdpId);

    /* 建链失败的处理 */
    TAF_APS_ProcCdataEstFail_CdataEsting(TAF_APS_GetCurrFsmEntityPdpId(),
                                         TAF_PS_CAUSE_EHSM_PPP_ERROR_TIME_OUT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcEhprdPdnAttachSucc_CdataEsting
 功能描述  : 用户发起激活，APS处理Attach成功的处理
 输入参数  : VOS_UINT8                           ucPdpId
             EHSM_APS_PDN_ATTACH_CNF_STRU       *pstPdnAttachCnf
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcEhprdPdnAttachSucc_CdataEsting(
    VOS_UINT8                           ucPdpId,
    EHSM_APS_PDN_ATTACH_CNF_STRU       *pstPdnAttachCnf
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataServiceMode;
    VOS_UINT8                           ucCid;
    MN_APS_PDP_IPV6_DNS_STRU           *pstPdpIpv6Dns;

    ucCid        = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 更新PdnId, APN, PdnAdrr */
    pstPdpEntity->ucNsapi       = pstPdnAttachCnf->ucRabId;
    pstPdpEntity->PdpNsapiFlag  = VOS_TRUE;
    pstPdpEntity->ActType       = APS_PDP_ACT_PRI;

    TAF_APS_SetPdpEntCdataPdnId(ucPdpId, pstPdnAttachCnf->ucPdnId);

    TAF_APS_UpdateCdataEhsmPdnInfo(  pstPdpEntity,
                                   &(pstPdnAttachCnf->stPdnAddr),
                                   &(pstPdnAttachCnf->stApn),
                                   &(pstPdnAttachCnf->stIpv4Dns));

    /* 记录当前的PS服务所在的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    /* 通知外部模块当前的PS服务所在的模式 */
    TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_EHRPD);

    TAF_APS_SET_CDATA_MTU(pstPdnAttachCnf->usMtu);

    TAF_APS_SndCgmtuValueChangeInd(pstPdnAttachCnf->usMtu);

    /* 不需要获取Ipv4 DNS */
    if (((VOS_TRUE == pstPdnAttachCnf->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE == pstPdnAttachCnf->stIpv4Dns.bitOpIpv4SecDNS))
      && (EHSM_APS_PDN_TYPE_IPV4   == pstPdnAttachCnf->stPdnAddr.enPdnType))
    {


        /* 给用户上报激活结果 */
        TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
    }
    else if (((VOS_TRUE == pstPdnAttachCnf->stIpv6Dns.bitOpIpv6PrimDNS) || (VOS_TRUE == pstPdnAttachCnf->stIpv6Dns.bitOpIpv6SecDNS))
            && (EHSM_APS_PDN_TYPE_IPV6 == pstPdnAttachCnf->stPdnAddr.enPdnType))
    {
        TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

        pstPdpIpv6Dns = (MN_APS_PDP_IPV6_DNS_STRU *)&pstPdnAttachCnf->stIpv6Dns;

        TAF_APS_UpdateCdataIpv6Dns(pstPdpEntity, pstPdpIpv6Dns);

        /* 在不做dhcp协商，但是IPV6的地址必然需要协商，在IPV6地址协商成功后，需要上报，故刷新次变量 */
        pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_TRUE;

        /* 给用户上报ACTIVATE_CNF事件 */
        TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
    }
    else if (((VOS_TRUE == pstPdnAttachCnf->stIpv6Dns.bitOpIpv6PrimDNS) || (VOS_TRUE == pstPdnAttachCnf->stIpv6Dns.bitOpIpv6SecDNS))
           && ((VOS_TRUE == pstPdnAttachCnf->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE == pstPdnAttachCnf->stIpv4Dns.bitOpIpv4SecDNS))
           && (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnAttachCnf->stPdnAddr.enPdnType))
    {
        TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

        pstPdpIpv6Dns = (MN_APS_PDP_IPV6_DNS_STRU *)&pstPdnAttachCnf->stIpv6Dns;

        TAF_APS_UpdateCdataIpv6Dns(pstPdpEntity, pstPdpIpv6Dns);

        /* 在不做dhcp协商，但是IPV6的地址必然需要协商，在IPV6地址协商成功后，需要上报，故刷新次变量 */
        pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_TRUE;

        /* 给用户上报ACTIVATE_CNF事件 */
        TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
    }
    else
    {
        /* 需要获取Ipv4 DNS */
        if (((EHSM_APS_PDN_TYPE_IPV4 == pstPdnAttachCnf->stPdnAddr.enPdnType) || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnAttachCnf->stPdnAddr.enPdnType))
         && (((VOS_TRUE != pstPdnAttachCnf->stIpv4Dns.bitOpIpv4PrimDNS) && (VOS_TRUE != pstPdnAttachCnf->stIpv4Dns.bitOpIpv4SecDNS))))
        {
            TAF_APS_SndDhcpDnsIpv4Req(ucPdpId);
            pstPdpEntity->ucNeedGetDnsFlg = VOS_TRUE;
        }

        /* 需要获取Ipv6 DNS，Ipv4,Ipv4v6类型 */
        if (((EHSM_APS_PDN_TYPE_IPV6   == pstPdnAttachCnf->stPdnAddr.enPdnType) || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnAttachCnf->stPdnAddr.enPdnType))
         && ((VOS_TRUE != pstPdnAttachCnf->stIpv6Dns.bitOpIpv6PrimDNS) && (VOS_TRUE != pstPdnAttachCnf->stIpv6Dns.bitOpIpv6SecDNS)))
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            TAF_APS_SndDhcpDnsIpv6Req(ucPdpId);
            pstPdpEntity->ucNeedGetDnsFlg = VOS_TRUE;
        }
    }

    enDataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();
    if (TAF_APS_RAT_TYPE_BUTT == enDataServiceMode)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_ProcEhprdPdnAttachSucc_CdataEsting: RAT type is Butt!");
    }

    /* 设置流控 */
    R_ITF_SetFlowLev(TAF_APS_MapRatType2VosRatMode(enDataServiceMode));

    /* 启动流量上报定时器 */
    TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    TAF_APS_QuitCurrSubFsm();

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmPdnAttachCnf_CdataEsting_WaitEhsmAttachCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ATTACH_CNF子状态下收
             到消息ID_EHSM_APS_PDN_ATTACH_CNF的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnAttachCnf_CdataEsting_WaitEhsmAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ATTACH_CNF_STRU       *pstPdnAttachCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 获取该PDPID */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstPdnAttachCnf = (EHSM_APS_PDN_ATTACH_CNF_STRU *)pstMsg;

    /* 停止激活总定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* Initial Attach成功 */
    if (EHSM_APS_CAUSE_SUCCESS == pstPdnAttachCnf->enCause)
    {
        TAF_APS_ProcEhprdPdnAttachSucc_CdataEsting(ucPdpId, pstPdnAttachCnf);
    }
    else if (EHSM_APS_CAUSE_EHRPD_SUSPEND == pstPdnAttachCnf->enCause)
    {
        /* 迁激活Suspend状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND);
    }
    else
    {
        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_APS_MapEhsmCause(pstPdnAttachCnf->enCause);

        /* 上报激活被拒 */
        TAF_APS_SndPdpActivateRej(ucPdpId, pstPdpEntity->enCause);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态状态机 */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataEsting_WaitEhsmAttachCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ATTACH_CNF子状态下收
             到消息ID_MSG_TAF_PS_CALL_END_REQ的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitEhsmAttachCnf(
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

    /* 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 停止激活定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* 更新Data Service Mode为EHRPD */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    /*------------------------------------------------------------------
    主状态迁移至TAF_APS_FSM_CDATA_DISCING
    子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

    在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
    处理ID_MSG_TAF_PS_CALL_END_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitEhsmAttachCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ATTACH_CNF子状态下收
             到定时器TI_TAF_APS_CDATA_ESTING超时消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitEhsmAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 给用户返回ACTIVE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_EHSM_PPP_ERROR_TIME_OUT);

    TAF_APS_SndEhsmLocDetachNotify();

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* 退出子状态状态机 */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterAttachBearerActivateInd_CdataEsting_Suspend
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND子状态下
             收到ID_EHSM_APS_PDN_ACTIVATE_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月21日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterAttachBearerActivateInd_CdataEsting_Suspend(
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
    TAF_APS_GetRemainTimerLen(TI_TAF_APS_CDATA_ESTING, ucPdpId, &ulRemainTimeLen);

    /* 如果剩余时长非0, 停止当前流程, 重新处理当前的状态机入口消息 */
    if (0 != ulRemainTimeLen)
    {
        /* 记录剩余时长 */
        TAF_APS_SetCallRemainTmrLen(TAF_APS_GetPdpEntCurrCid(ucPdpId), ulRemainTimeLen);

        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

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

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataEstingExpired_CdataEsting_Suspend
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND子状态下
             收到TI_TAF_APS_CDATA_ESTING消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月21日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_APS_TIME_OUT);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_CdataEsting_Suspend
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月21日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_CdataEsting_Suspend(
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
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING,
                      ucPdpId);

    /* 上报PDP操作结果, NO_ERROR */
    TAF_APS_SndCallEndCnf(&(pstPsCallEndReq->stCtrl),
                          pstPsCallEndReq->ucCid,
                          TAF_PS_CAUSE_SUCCESS);

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
 函 数 名  : TAF_APS_RcvPsInterSrvStaChangeReq_CdataEsting_Suspend
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND子状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月22日
    作    者   : y00314741
    修改内容   : 新生成函数

  2.日    期   : 2015年8月19日
    作    者   : Y00213812
    修改内容   : 有服务模式后，modem侧只关注是否可以拨号，不关注是否需要切换
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterSrvStaChangeReq_CdataEsting_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID和当前接入技术 */
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType  = TAF_APS_GetCurrPdpEntityRatType();
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();

    /* 如果支持HYBRID模式，首先在HPRD模式下进行尝试建链 */
    if (VOS_TRUE == TAF_APS_IsHybridMode())
    {
        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_HRPD:
                TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(ucPdpId, VOS_FALSE);

                break;

            case TAF_APS_RAT_TYPE_EHRPD:
                if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ) == pstEntryMsg->ulEventType)
                {
                    TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode(ucPdpId, TAF_APS_ORIG_TYPE_PS_CALL);
                }

                if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ) == pstEntryMsg->ulEventType)
                {
                    TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode(ucPdpId, TAF_APS_ORIG_TYPE_PPP_DIAL);
                }
                break;

            case TAF_APS_RAT_TYPE_1X:
                TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(ucPdpId, VOS_TRUE);

                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                     "TAF_APS_RcvPsInterSvcStaChangeReq_CdataEsting_Suspend: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* 如果不支持Hybrid，即只支持1X，则在1X下尝试建链 */
        TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
    }

    return VOS_TRUE;

}



/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppActCnf_CdataEsting_WaitPppActCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF子状态下收到
             ID_PPP_APS_ACT_CNF消息的处理
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
VOS_UINT32 TAF_APS_RcvPppActCnf_CdataEsting_WaitPppActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_ACT_CNF_STRU               *pstPppActCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataServiceMode;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPppActCnf = (PPP_APS_ACT_CNF_STRU *)pstMsg;

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 停止流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

    enDataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();
    if (TAF_APS_RAT_TYPE_BUTT == enDataServiceMode)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
                        "TAF_APS_RcvPppActCnf_CdataEsting_WaitPppActCnf: RAT type is Butt!");
    }

    if (VOS_OK == pstPppActCnf->ulResult)
    {
        pstPdpEntity->PdpAddrFlag           = VOS_TRUE;

        if (TAF_APS_PPP_ADDR_TYPE_IPV4 == pstPppActCnf->enPdnType)
        {
            pstPdpEntity->PdpAddr.ucPdpTypeNum  = APS_ADDR_STATIC_IPV4;

            TAF_APS_UpdataCdataIpv4Addr(pstPdpEntity, pstPppActCnf);

            if ((VOS_TRUE == pstPppActCnf->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE == pstPppActCnf->stIpv4Dns.bitOpIpv4SecDNS))
            {
                /* 给用户上报ACTIVATE_CNF事件 */
                TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
            }
            else
            {
                TAF_APS_SndDhcpDnsIpv4Req(ucPdpId);
            }
        }
        else if (TAF_APS_PPP_ADDR_TYPE_IPV6 == pstPppActCnf->enPdnType)
        {
            TAF_APS_SndCdsModeChangeInd(enDataServiceMode);

            pstPdpEntity->PdpAddr.ucPdpTypeNum  = MN_APS_ADDR_IPV6;

            TAF_APS_UpdataCdataIpv6Addr(pstPdpEntity, pstPppActCnf);

            /* IPV6 RA INFO */
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            TAF_APS_SndDhcpDnsIpv6Req(ucPdpId);
        }
        else if (TAF_APS_PPP_ADDR_TYPE_IPV4V6 == pstPppActCnf->enPdnType)
        {
            TAF_APS_SndCdsModeChangeInd(enDataServiceMode);

            pstPdpEntity->PdpAddr.ucPdpTypeNum  = MN_APS_ADDR_IPV4V6;

            TAF_APS_UpdataCdataIpv4Addr(pstPdpEntity, pstPppActCnf);
            TAF_APS_UpdataCdataIpv6Addr(pstPdpEntity, pstPppActCnf);

            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            if ((VOS_TRUE != pstPppActCnf->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE != pstPppActCnf->stIpv4Dns.bitOpIpv4SecDNS))
            {
                TAF_APS_SndDhcpDnsIpv4Req(ucPdpId);
            }

            TAF_APS_SndDhcpDnsIpv6Req(ucPdpId);
        }
        else
        {
            /* TODO:检查IP类型错误，需要内部去激活? */
        }

        TAF_APS_SET_CDATA_MTU(pstPppActCnf->usMtu);

        /* 设置CDATA PS域服务状态为ACTIVE状态 */
        TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVE);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_ACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_ACTIVE);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 启动流量上报定时器 */
        TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

        /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_NEGOTIATE_FAIL;

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        if (TAF_APS_CDATA_AIR_LINK_CONNECTED == TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
        {
            /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ消息 */
            TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL,
                                           TAF_APS_INTER_END_CALL_REASON_PPP_ACT_FAIL,
                                           ucPdpId,
                                           TI_TAF_APS_CDATA_DISCING_LEN);
        }
        else
        {
            TAF_APS_SndPdpActivateRej(ucPdpId, pstPdpEntity->enCause);

            /* 释放APS资源 */
            Aps_ReleaseApsResource(ucPdpId);

            /* 配置IP过滤 */
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            /* 退出子状态机 */
            TAF_APS_QuitCurrSubFsm();

            /* 主状态迁移至TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppReConnInd_CdataEsting_WaitPppActCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF子状态下收到
             ID_PPP_APS_RECONN_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvPppReConnInd_CdataEsting_WaitPppActCnf(
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
                    TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(ucPdpId, VOS_FALSE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
                }
                break;

            case TAF_APS_RAT_TYPE_1X:
            case TAF_APS_RAT_TYPE_NULL:
                /* DO强信号去HRPD建链；DO弱信号去1X建链 */
                if (VOS_FALSE == TAF_APS_GetIsHrpdDisabledFlag())
                {
                    TAF_APS_ProcHrpdOirgDataCall_CdataEsting_HybridMode(ucPdpId, VOS_TRUE);
                }
                else
                {
                    TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
                }
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvPppReConnInd_CdataEsting_WaitPppActCnf: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* 如果不支持Hybrid，即只支持1X，则在1X下尝试建链 */
        TAF_APS_Proc1xOrigDataCall_CdataEsting_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitPppActCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF子状态下收到
             ID_XCC_APS_DATA_CALL_DISC_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitPppActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity          = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDiscInd            = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* SO Rej 需要特殊处理，本地去激活 */
    if (TAF_PS_CAUSE_XCC_AS_SO_REJ == pstPdpEntity->enCause)
    {
        /* 之前的激活流程尚未结束，PPP激活协商尚未完成，此时上报激活失败 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

        TAF_APS_SndPdpActivateRej(ucPdpId, pstPdpEntity->enCause);

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
 函 数 名  : TAF_APS_RcvHsmDiscInd_CdataEsting_WaitPppActCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF子状态下收到
             ID_HSM_APS_DISC_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvHsmDiscInd_CdataEsting_WaitPppActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    HSM_APS_DISC_IND_STRU              *pstDiscInd = VOS_NULL_PTR;

    /* 初始化, 获取消息内容 */
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
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataEsting_WaitPppActCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF子状态下收到
             ID_MSG_TAF_PS_CALL_END_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitPppActCnf(
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

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    if (TAF_APS_CDATA_AIR_LINK_CONNECTED == TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
    {
        /* 当前空口链路存在，等待PPP激活协商的过程中，收到用户发起去激活, 加载去激活的状态机 */
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);
    }
    else
    {
        /* 上报去激活成功 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        TAF_APS_SndPppDeactInd(ucPdpId);

        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

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
 函 数 名  : TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitPppActCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF子状态下收到
             ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ消息的处理
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
VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitPppActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 加载去激活的状态机 */
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitPppActCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_PPP_ACT_CNF子状态下收到
             PPP激活协商超时消息的处理
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
VOS_UINT32 TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitPppActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_TIME_OUT;

    /* 通知PPP去激活 */
    TAF_APS_SndPppDeactInd(ucPdpId);

    /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    if (TAF_APS_CDATA_AIR_LINK_CONNECTED == TAF_APS_GetCdmaAirLinkStatus(ucPdpId))
    {
        /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ消息 */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL,
                                       TAF_APS_INTER_END_CALL_REASON_PPP_ACT_TIME_OUT,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }
    else
    {
        TAF_APS_SndPdpActivateRej(ucPdpId, pstPdpEntity->enCause);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppActCnf_CdataEsting_WaitXccOrigCallCnf
 功能描述  : 子状态TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF下收到
             消息ID_PPP_APS_ACT_CNF的处理
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
VOS_UINT32 TAF_APS_RcvPppActCnf_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 初始化PdpId */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 如果之前的PPP激活流程还在进行，此次重建是由PPPC触发的，激活过程中, PPP协商结果均为失败 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 保存原因值,上报激活失败的时候使用 */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_NEGOTIATE_FAIL;

        /* 停止上一轮的PPP激活协商定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

        /* 停止本次建链流程中起的定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* 之前发起建链的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

        /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL,
                                       TAF_APS_INTER_END_CALL_REASON_PPP_ACT_FAIL,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitXccOrigCallCnf
 功能描述  : 子状态TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF下收到
             消息定时器TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF超时的处理
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
VOS_UINT32 TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 如果之前的PPP激活流程还在进行，此次重建是由PPPC触发的，激活过程中, PPP协商结果均为失败 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_TIME_OUT;

        /* 停止本次建链流程中起的定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 通知PPP去激活 */
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

        /* 之前发起建链的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

        /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL,
                                       TAF_APS_INTER_END_CALL_REASON_PPP_ACT_TIME_OUT,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiPppDeactCnfExpired_CdataEsting_WaitXccOrigCallCnf
 功能描述  : 等待XCC Orig Cnf的时候收到PPP去激活协商定时器超时消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月19日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止本次建链流程中起的定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* PPP状态为active,通知PPP去激活 */
    TAF_APS_SndPppDeactInd(ucPdpId);

    /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

    /* 之前发起建链的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

    /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
    TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_USER_END,
                                   TAF_APS_INTER_END_CALL_REASON_USER_END,
                                   ucPdpId,
                                   TI_TAF_APS_CDATA_DISCING_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitXccOrigCallCnf
 功能描述  : 等待XCC ORIG CNF的子状态收到内部去激活的消息
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
VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitXccOrigCallCnf(
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
 函 数 名  : TAF_APS_RcvPppActCnf_CdataEsting_WaitXccSoConnected
 功能描述  : 子状态TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED下收到消
             息ID_PPP_APS_ACT_CNF的处理
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
VOS_UINT32 TAF_APS_RcvPppActCnf_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 初始化PdpId */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 如果之前的PPP激活流程还在进行，此次重建是由PPPC触发的，激活过程中, PPP协商结果均为失败 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 保存原因值,上报激活失败的时候使用 */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_NEGOTIATE_FAIL;

        /* 停止上一轮的PPP激活协商定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

        /* 停止本次建链流程中起的定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL,
                                       TAF_APS_INTER_END_CALL_REASON_PPP_ACT_FAIL,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitXccSoConnected
 功能描述  : 子状态TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED下收到定时器
             TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF超时消息的处理
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
VOS_UINT32 TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 初始化PdpId */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 如果之前的PPP激活流程还在进行，此次重建是由PPPC触发的，激活过程中, PPP协商结果均为失败 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_TIME_OUT;

        /* 停止本次建链流程中起的定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 通知PPP去激活 */
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL,
                                       TAF_APS_INTER_END_CALL_REASON_PPP_ACT_TIME_OUT,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiPppDeactCnfExpired_CdataEsting_WaitXccSoConnected
 功能描述  : 等待SO Connect消息时候收到PPP去激活定时器超时
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月19日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止本次建链流程中起的定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* PPP状态为active,通知PPP去激活 */
    TAF_APS_SndPppDeactInd(ucPdpId);

    /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
    TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_USER_END,
                                   TAF_APS_INTER_END_CALL_REASON_USER_END,
                                   ucPdpId,
                                   TI_TAF_APS_CDATA_DISCING_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppActCnf_CdataEsting_WaitRedial
 功能描述  : 子状态TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL下收到消
             息ID_PPP_APS_ACT_CNF的处理
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
VOS_UINT32 TAF_APS_RcvPppActCnf_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化PdpId */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 如果之前的PPP激活流程还在进行，此次重建是由PPPC触发的，激活过程中, PPP协商结果均为失败 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 停止上一轮的PPP激活协商定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

        /* 停止建链流程中起的定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
        }

        if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
        }

        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_PPP_NEGOTIATE_FAIL);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitRedial
 功能描述  : 子状态TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL下收到定时器
             TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF超时消息的处理
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
VOS_UINT32 TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化PdpId */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 如果之前的PPP激活流程还在进行，此次重建是由PPPC触发的，激活过程中, PPP协商结果均为失败 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 停止建链流程中起的定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
        }

        if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
        }

        /* 再次通知PPP本地去激活 */
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_PPP_TIME_OUT);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppActCnf_CdataEsting_WaitHsmOrigCnf
 功能描述  : 子状态TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF下收到消
             息ID_PPP_APS_ACT_CNF的处理
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
VOS_UINT32 TAF_APS_RcvPppActCnf_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 初始化PdpId */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 如果之前的PPP激活流程还在进行，此次重建是由PPPC触发的，激活过程中, PPP协商结果均为失败 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 保存原因值,上报激活失败的时候使用 */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_NEGOTIATE_FAIL;

        /* 停止上一轮的PPP激活协商定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

        /* 停止本次建链流程中起的定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* 之前发起建链的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL,
                                       TAF_APS_INTER_END_CALL_REASON_PPP_ACT_FAIL,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitHsmOrigCnf
 功能描述  : 子状态TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF下收到定时器
             TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF超时消息的处理
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
VOS_UINT32 TAF_APS_RcvTiPppActCnfExpired_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 初始化PdpId */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 如果之前的PPP激活流程还在进行，此次重建是由PPPC触发的，激活过程中, PPP协商结果均为失败 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_TIME_OUT;

        /* 停止本次建链流程中起的定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 通知PPP去激活 */
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

        /* 之前发起建链的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL,
                                       TAF_APS_INTER_END_CALL_REASON_PPP_ACT_TIME_OUT,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiPppDeactCnfExpired_CdataEsting_WaitHsmOrigCnf
 功能描述  : 等待TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF时候收到PPP去激活协商定时器超时消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月19日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiPppDeactCnfExpired_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止本次建链流程中起的定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* PPP状态为active,通知PPP去激活 */
    TAF_APS_SndPppDeactInd(ucPdpId);

    /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

    /* 之前发起建链的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

    /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
    TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_USER_END,
                                   TAF_APS_INTER_END_CALL_REASON_USER_END,
                                   ucPdpId,
                                   TI_TAF_APS_CDATA_DISCING_LEN);

    return VOS_TRUE;
}

#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


