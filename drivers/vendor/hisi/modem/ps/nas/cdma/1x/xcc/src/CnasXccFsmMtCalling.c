/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccFsmMoCalling.c
  版 本 号   : 初稿
  作    者   : w00242748
  生成日期   : 2014年9月4日
  功能描述   : MO CALLING L2状态机
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : w00242748
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasXccFsmMtCalling.h"
#include "CnasXccFsmMtCallingTbl.h"
#include "CnasXccSndAps.h"
#include "cas_1x_control_main_nas_pif.h"
#include "CnasXccComFunc.h"
#include "CnasXccCtx.h"
#include "CnasXccSndCas.h"
#include "CnasXccSndCas.h"
#include "CnasXccSndXcall.h"
#include "CnasXccSndInternalMsg.h"
#include "CnasMntn.h"
#include "cas_1x_trchctrl_proc_nas_pif.h"
#include "CnasXccSndCsms.h"
#include "CnasCcb.h"
#include "xcc_aps_pif.h"
#include "xcc_sms_pif.h"
#include "CnasXccSndXpds.h"
#include  "xcc_xpds_pif.h"
#include "Nas_Mem.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_FSM_MT_CALLING_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsPagingInd_MtCalling_Init
 功能描述  : 收到ID_CAS_CNAS_1X_PAGING_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数

 2.日    期   : 2015年12月24日
   作    者   : y00245242
   修改内容   : privacy mode特性开发
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsPagingInd_MtCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_PAGING_IND_STRU        *pstAsPagingInd = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    /* 保存消息入口 */
    CNAS_XCC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstAsPagingInd = (CAS_CNAS_1X_PAGING_IND_STRU *)pstMsg;
    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 保存被叫SO */
    CNAS_XCC_SetInitSo(pstAsPagingInd->enSo);

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    CNAS_XCC_CovertVoiceCallPagingIndSo(&pstAsPagingInd->enSo);
#endif

    CNAS_XCC_SetCurrentSo(pstAsPagingInd->enSo);

    CNAS_XCC_ConvertSoToServiceType(pstAsPagingInd->enSo, &enServiceType);

    if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
    {
        pstCallInfoCtx->enReqPrivacyMode = (XCALL_XCC_PRIVACY_MODE_ENUM_UINT8)(CNAS_XCC_GetCtxAddr()->stCallNvimCfg.ucPrivacyMode);
    }

    /* 短信或者语音呼叫 */
    if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType) )
    {
        /* 通知APS挂起 */
        CNAS_XCC_SndApsDataCallSuspendInd(pstCallInfoCtx->ucConnectId, enServiceType);

        /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_APS_SUSPEND_RSP */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_APS_SUSPEND_RSP);

        /* 启动TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN);
    }
    else
    {
        /* 给AS发送EST REQ */
        CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_PAGING_RSP, pstCallInfoCtx);

        /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF);

        /* 启动TI_CNAS_XCC_WAIT_AS_EST_CNF */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsDschDataInd_MtCalling_Init
 功能描述  : 收到ID_CAS_CNAS_1X_DSCH_DATA_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期   : 2014年11月12日
   作    者   : L00256032
   修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_MtCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd;
    CNAS_XCC_AWIM_STRU                 *pstAWIM;
    CNAS_XCC_EAWIM_STRU                *pstEAWIM;

    /* 保存消息入口 */
    CNAS_XCC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;
    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* 该消息函数处理只有收到AWI或者EAWI或者MAINTANCE ORDER时才会进入 */
    if (CNAS_XCC_SERVICE_TYPE_LOOPBACK == enServiceType)
    {
        CNAS_XCC_AutoAnswerLoopBackService_MtCalling(pstCallInfoCtx);
        return VOS_TRUE;
    }

    /* 给XCALL发送INCOMING CALL IND */
    if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
    {
        /* 给XCALL发送INCOMING CALL IND */
        CNAS_XCC_SndXcallIncomingCallInd(pstCallInfoCtx);
    }


    /* SEND DATA CALL OR SMS incoming call ind */
    if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
    {
        /* 给CSMS发送INCOMING CALL IND */
        CNAS_XCC_SndCsmsIncomingCallInd(pstCallInfoCtx);
    }

    if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType)
    {
        CNAS_XCC_SndXpdsIncomingCallInd(pstCallInfoCtx);
    }

    /* 可维可测，上报1x call state*/
    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

#if 0
    if (CNAS_XCC_SERVICE_TYPE_DATA_CALL == enServiceType)
    {
        /* 给APS发送INCOMING CALL IND */
        CNAS_XCC_SndApsIncomingCallInd(pstCallInfoCtx);
    }
#endif




    /*
        如果是无效的call id，此时认为是一个新的呼叫的到来，走新来电的流程，否则走的是迁回到wait for
        answer状态
     */
    if ( CNAS_XCC_INVAILD_CALL_ID == pstCallInfoCtx->ucCallId )
    {
        /* 完成AWI/EAWI的解码并缓存 */
        CNAS_XCC_BufferAWIOrEAWIInfoReco((CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg, pstCallInfoCtx);

        /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP);

        /* 启动TI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP_LEN);
    }
    else
    {
        /* 解码AWI或EAWI，并完成上报 */
        if (CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG == pstDschDataInd->enDschMsgType)
        {
            pstAWIM = (CNAS_XCC_AWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_AWIM_STRU));
            if (VOS_NULL_PTR == pstAWIM)
            {
                return VOS_ERR;
            }

            if (VOS_OK != CNAS_XCC_DecodeAlertWithInformationMsg(pstDschDataInd, pstAWIM))
            {
                PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);
                return VOS_ERR;
            }

            CNAS_XCC_SndXcallInfoRecInd(pstCallInfoCtx->ucCallId,
                                        CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG,
                                        (VOS_UINT8 *)pstAWIM);

            PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);
        }
        else if (CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG == pstDschDataInd->enDschMsgType)
        {
            pstEAWIM = (CNAS_XCC_EAWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EAWIM_STRU));
            if (VOS_NULL_PTR == pstEAWIM)
            {
                return VOS_ERR;
            }

            if (VOS_OK != CNAS_XCC_DecodeExtendedAlertWithInformationMsg(pstDschDataInd, pstEAWIM))
            {
                PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);
                return VOS_ERR;
            }

            CNAS_XCC_SndXcallInfoRecInd(pstCallInfoCtx->ucCallId,
                                        CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG,
                                        (VOS_UINT8 *)pstEAWIM);

            PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);
        }
        else
        {

        }

        /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ANSWER,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));

        /* 启动TI_CNAS_XCC_T53M */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvApsDataCallSuspendRsp_MtCalling_WaitApsSuspendRsp
 功能描述  : 收到ID_APS_XCC_DATA_CALL_SUSPEND_RSP消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsDataCallSuspendRsp_MtCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* 给AS发送EST REQ */
    CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_PAGING_RSP, pstCallInfo);

    /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF);

    /* 启动TI_CNAS_XCC_WAIT_AS_EST_CNF */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitApsSuspendRsp
 功能描述  : 处理ID_CNAS_XCC_XCC_ABORT_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护定时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* 通知APS 取消挂起APS，发送ID_XCC_APS_DATA_CALL_RESUME_IND */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);

    /* 通知层1，状态机结果为CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId, CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED, CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MtCalling_WaitApsSuspendRsp
 功能描述  : XCC处于等待APS挂起回复状态时，保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MtCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 给AS发送EST REQ */
    CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_PAGING_RSP, pstCallInfo);

    /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF);

    /* 启动TI_CNAS_XCC_WAIT_AS_EST_CNF */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitApsSuspendRsp
 功能描述  : XCC处于等待APS挂起回复状态时，收到关机请求
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        当前关机的时候，链路释放是在main control里面处理的，因此不需要与接入层交互，只需要状态迁移，
        同时TAF对应消息的处理
     */

    /* 停止TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* 将SO转换成SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    /* 通知APS 取消挂起APS，发送ID_XCC_APS_DATA_CALL_RESUME_IND */
    if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType))
    {
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);
    }

    /* 通知层1，状态机结果为CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsEstCnf_MtCalling_WaitAsEstCnf
 功能描述  : 收到ID_CAS_CNAS_1X_EST_CNF消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsEstCnf_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CAS_CNAS_1X_EST_CNF_STRU           *pstEstCnfMsg   = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstEstCnfMsg   = (CAS_CNAS_1X_EST_CNF_STRU *)pstMsg;
    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* 停止TI_CNAS_XCC_WAIT_AS_EST_CNF */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    if ( CAS_CNAS_1X_EST_RSLT_SUCCESS == pstEstCnfMsg->enEstRslt )
    {
        /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_AS_CALL_INIT */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_AS_CALL_INIT);

        /* 启动TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND_LEN);
    }
    else
    {
        if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
          || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
          || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType) )
        {
            /* 通知APS RESUME IND */
            CNAS_XCC_SndApsDataCallResumeInd(pstCallInfoCtx->ucConnectId, enServiceType);
        }

        /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
        CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                                  CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

        /* 退出层2状态机 */
        CNAS_XCC_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitAsEstCnf
 功能描述  : 收到ID_CNAS_XCC_XCC_ABORT_REQ的处理
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;

    pstCallInfo =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护定时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* 通知AS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId, pstCallInfo->ucConRef, CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE, VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiWaitAsEstCnfExpired_MtCalling_WaitAsEstCnf
 功能描述  : XCC处于等待接入层建链回复状态，保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitAsEstCnfExpired_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 通知AS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitAsEstCnf
 功能描述  : XCC处于等待接入层建链回复状态，收到接入层terminate ind
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_WAIT_AS_EST_CNF */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* SO转换成service type */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* VOICE CALL OR SMS恢复APS */
    if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType) )
    {
        /* 通知APS resume */
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfoCtx->ucConnectId, enServiceType);
    }

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitAsEstCnf
 功能描述  : XCC处于等待接入层建链回复状态，收到关机请求
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        当前关机的时候，链路释放是在main control里面处理的，因此不需要与接入层交互，只需要状态迁移，
        同时TAF对应消息的处理
     */

    /* 停止TI_CNAS_XCC_WAIT_AS_EST_CNF */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallInitInd_MtCalling_WaitAsCallInitInd
 功能描述  : 收到ID_CAS_CNAS_1X_CALL_INIT_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallInitInd_MtCalling_WaitAsCallInitInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_INIT_IND_STRU     *pstCallInitInd = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstCallInitInd = (CAS_CNAS_1X_CALL_INIT_IND_STRU *)pstMsg;
    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* bypass，isnull，qos参数记录到全局变量 */
    /* 呼叫信息中的connect id和CALL INIT中的connect id是相同的 */
    pstCallInfoCtx->ucConRef           = pstCallInitInd->ucConRef;
    pstCallInfoCtx->ucIsByPassAlertAns = (VOS_UINT8)pstCallInitInd->enBypassAlertAns;
    pstCallInfoCtx->ucIsNullCc         = pstCallInitInd->enIsNullCcFlag;
    pstCallInfoCtx->ucQosInfoLen       = pstCallInitInd->ucQosInfoLen;

    NAS_MEM_CPY_S(pstCallInfoCtx->aucQosInfo, sizeof(pstCallInfoCtx->aucQosInfo), pstCallInitInd->aucQosInfo, sizeof(pstCallInfoCtx->aucQosInfo));

    if ( VOS_TRUE == pstCallInfoCtx->ucIsByPassAlertAns )
    {
        /* 如果是环回模式，直接进conversation状态，退状态机 */
        if (CNAS_XCC_SERVICE_TYPE_LOOPBACK == enServiceType)
        {
            /* 退状态机，进conversation状态 */
            CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                                      CNAS_XCC_MT_CALLING_RESULT_SUCCESS,
                                      CNAS_XCC_MT_CALLING_END_REASON_BUTT);

            CNAS_XCC_QuitFsmL2();
            return VOS_TRUE;
        }


        if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
        {
            /* 给XCALL发送INCOMING CALL IND */
            CNAS_XCC_SndXcallIncomingCallInd(pstCallInfoCtx);
        }

        /* SEND DATA CALL OR SMS incoming call ind */
        if (CNAS_XCC_SERVICE_TYPE_DATA_CALL == enServiceType)
        {
            CNAS_XCC_SndApsIncomingCallInd(pstCallInfoCtx);
        }

        if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
        {
            CNAS_XCC_SndCsmsIncomingCallInd(pstCallInfoCtx);
        }

        if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType)
        {
            CNAS_XCC_SndXpdsIncomingCallInd(pstCallInfoCtx);
        }

        /* 可维可测，上报1x call state*/
        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();

        /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP);

        /* 启动TI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP_LEN);
    }
    else
    {
        /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ORDER */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ORDER);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ORDER,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));

        /* 启动TI_CNAS_XCC_T52M */
        CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M, TI_CNAS_XCC_T52M_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitAsCallInit
 功能描述  : 收到ID_CNAS_XCC_XCC_ABORT_REQ的处理
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;

    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护定时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* 通知AS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                                  VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitAsCallInitInd
 功能描述  : 收到ID_CAS_CNAS_1X_CALL_INIT_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitAsCallInitInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* SO转换成service type */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* VOICE CALL OR SMS恢复APS */
    if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType) )
    {
        /* 通知APS resume */
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfoCtx->ucConnectId, enServiceType);
    }

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiWaitAsCallInitIndExpired_MtCalling_WaitAsCallInit
 功能描述  : XCC处于等待接入层call init ind状态，保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitAsCallInitIndExpired_MtCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 通知AS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitAsCallInit
 功能描述  : XCC处于等待接入层call init ind状态，收到关机请求
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        当前关机的时候，链路释放是在main control里面处理的，因此不需要与接入层交互，只需要状态迁移，
        同时TAF对应消息的处理
     */

    /* 停止TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForOrder
 功能描述  : 收到ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
 2.日    期   : 2015年9月1日
   作    者   : c00299063
   修改内容   : 函数封装
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_UpdateMtCallInfoInd(ulEventType, pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_UpdateMtCallInfoInd
 功能描述  : 更新被叫call info ind
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月1日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_UpdateMtCallInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfoCtx       = VOS_NULL_PTR;
    CAS_CNAS_1X_UPDATE_CALL_INFO_IND_STRU                  *pstUpdateCallInfoInd = VOS_NULL_PTR;

    pstUpdateCallInfoInd            = (CAS_CNAS_1X_UPDATE_CALL_INFO_IND_STRU *)pstMsg;
    pstCallInfoCtx                  = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 更新CALL信息 */
    pstCallInfoCtx->ucConRef        = pstUpdateCallInfoInd->ucConRef;
    pstCallInfoCtx->ucIsNullCc      = pstUpdateCallInfoInd->enIsNullCcFlag;
    pstCallInfoCtx->enCurrentSo     = pstUpdateCallInfoInd->enSo;

    CNAS_XCC_UpdateSrIdUsed(pstUpdateCallInfoInd->enSo,
                            pstUpdateCallInfoInd->ucSrId,
                            pstUpdateCallInfoInd->ucConnectId);
    pstCallInfoCtx->ucSrId          = pstUpdateCallInfoInd->ucSrId;


    /* 当前认为接入层上报ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND的时候，接入层已经SO协商完成，因此
        此时SO的协商完成标记置成VOS_TRUE */
    pstCallInfoCtx->ucIsSoNegCmplt  = VOS_TRUE;

    if ( VOS_TRUE == pstUpdateCallInfoInd->ucQosParaFlag )
    {
        pstCallInfoCtx->bitOpQosInfo       = VOS_TRUE;
        pstCallInfoCtx->ucQosInfoLen       = pstUpdateCallInfoInd->ucQosInfoLen;
        NAS_MEM_CPY_S(pstCallInfoCtx->aucQosInfo, sizeof(pstCallInfoCtx->aucQosInfo), pstUpdateCallInfoInd->aucQosInfo, sizeof(pstCallInfoCtx->aucQosInfo));
    }

    return ;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForAnswer
 功能描述  : 收到ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月1日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_UpdateMtCallInfoInd(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForIncomingRsp
 功能描述  : 收到ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月1日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_UpdateMtCallInfoInd(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitConnL2Ack
 功能描述  : 收到ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年9月1日
   作    者   : c00299063
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_UpdateMtCallInfoInd(ulEventType, pstMsg);

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsResetWfoSubstateTimerInd_MtCalling_WaitForOrder
 功能描述  : 收到ID_CAS_CNAS_1X_RESET_WFO_SUBSTATE_TIMER_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsResetWfoSubstateTimerInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx       = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 重新启动定时器 */
    CNAS_XCC_RestartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M, TI_CNAS_XCC_T52M_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForOrder
 功能描述  : 收到ID_CAS_CNAS_1X_DSCH_DATA_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd = VOS_NULL_PTR;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;

    pstDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;
    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));


    /*
    If the Call Control instance receives a message from the layer 3Layer 3 which is
    included in the following list and every message field value is within its permissible
    range, the Call Control instance shall process the message as described below and
    in accordance with the message action time (see 2.6.4.1.5).
        1. Alert With Information Message: If the message contains a Signal information
        record, the mobile station should alert the user in accordance with the Signal
        information record; otherwise, the mobile station should use standard alert as
        defined in 3.7.5.5. The Call Control instance shall enter the Waiting for Mobile
        Station Answer Substate (see 2.6.10.1.2).
        2. Extended Alert with Information Message: If the message contains a Signal
        information record, the mobile station should alert the user in accordance with
        the Signal information record; otherwise, the mobile station should use
        standard alert as defined in 3.7.5.5. The Call Control instance shall enter the
        Waiting for Mobile Station Answer Substate (see 2.6.10.1.2).
        3. Maintenance Order: The Call Control instance shall enter the Waiting for Mobile
        Station Answer Substate.
    If the Call Control instance receives a message that is not included in the above list,
    cannot be processed, or requires a capability which is not supported, the Call
    Control instance shall discard the message and send a message rejected indicationto the layer 3Layer 3, with the reject reason indicated.
    */
    switch (pstDschDataInd->enDschMsgType)
    {
        case CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG:
        case CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG:
            /* 完成AWI/EAWI的解码并缓存 */
            CNAS_XCC_BufferAWIOrEAWIInfoReco(pstDschDataInd, pstCallInfoCtx);

            /* 停T52M */
            CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M);

            /* 如果是环回模式，则自动接听 */
            if ( CNAS_XCC_SERVICE_TYPE_LOOPBACK == enServiceType)
            {
                CNAS_XCC_AutoAnswerLoopBackService_MtCalling(pstCallInfoCtx);
                return VOS_TRUE;
            }

            /* 给XCALL发送INCOMING CALL IND */
            if ( CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
            {
                /* 给XCALL发送INCOMING CALL IND */
                CNAS_XCC_SndXcallIncomingCallInd(pstCallInfoCtx);
            }

            /* SEND DATA CALL OR SMS incoming call ind */
            if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
            {
                /* 给CSMS发送INCOMING CALL IND */
                CNAS_XCC_SndCsmsIncomingCallInd(pstCallInfoCtx);
            }

            if (CNAS_XCC_SERVICE_TYPE_DATA_CALL == enServiceType)
            {
                /* 给APS发送INCOMING CALL IND */
                CNAS_XCC_SndApsIncomingCallInd(pstCallInfoCtx);
            }

            if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType)
            {
                CNAS_XCC_SndXpdsIncomingCallInd(pstCallInfoCtx);
            }

            /* 可维可测，上报1x call state*/
            CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL,
                                    CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
            CNAS_XCC_SndXcc1xCallStateUpdateInd();

            /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP */
            CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP);

            /* 启动TI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP */
            CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP_LEN);
            break;

        case CAS_CNAS_1X_RX_TCH_ORDER_MSG:
            CNAS_XCC_ProcOrderMsg_MtCalling_WaitForOrder(pstDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG:
        case CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG:
        case CAS_CNAS_1X_RX_TCH_SEND_BURST_DTMF_MSG:
            /* 编码REJ ORDER */
            pstCallInfoCtx              = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
            stRejInfo.ucConRef          = pstCallInfoCtx->ucConRef;
            stRejInfo.enRejRxTchMsgType = pstDschDataInd->enDschMsgType;
            stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
            stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_STATE;
            stRejInfo.ulL3PduBitLen     = 0;
            stRejInfo.pucPdudata        = aucPduData;
            CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

            /* 发送ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER)给AS */
            CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                       0, (VOS_UINT16)stRejInfo.ulL3PduBitLen, aucPduData);
            break;

        default:
            CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForOrder: Wrong MSG", pstDschDataInd->enDschMsgType);
            break;

    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForOrder
 功能描述  : 收到ID_CNAS_XCC_XCC_ABORT_REQ的处理
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;

    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护定时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_T52M);

    /* 通知AS REL_REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForOrder
 功能描述  : 收到ID_CAS_CNAS_1X_CALL_TERMINATE_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停T52M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M);

    /* SO转换成service type */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* VOICE CALL OR SMS恢复APS */
    if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType) )
    {
        /* 通知APS resume */
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfoCtx->ucConnectId, enServiceType);
    }

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForOrder
 功能描述  : 收到ID_CAS_CNAS_1X_CALL_REL_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月9日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停T52M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiT52MExpired_MtCalling_WaitForOrder
 功能描述  : TI_CNAS_XCC_T52M保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiT52MExpired_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 给AS发送Rel Req */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_SUB_STATE_TIMER_EXPIRED,
                              VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForOrder
 功能描述  : WAIT FOR ORDER状态，收到关机请求
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForOrder(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        当前关机的时候，链路释放是在main control里面处理的，因此不需要与接入层交互，只需要状态迁移，
        同时TAF对应消息的处理
     */

    /* 停止定时器 */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXcallIncomingCallRsp_MtCalling_WaitForIncomingRsp
 功能描述  : 收到ID_XCALL_XCC_INCOMING_CALL_RSP消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallIncomingCallRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCALL_XCC_INCOMING_CALL_RSP_STRU   *pstIncomingCallRsp = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstIncomingCallRsp = (XCALL_XCC_INCOMING_CALL_RSP_STRU *)pstMsg;
    pstCallInfo        = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* INCOMING RSP结果失败，通知CAS，退状态机 */
    if ( XCC_XCALL_RESULT_FAIL == pstIncomingCallRsp->enRslt )
    {
        /* 通知接入层REL REQ */
        CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                                  VOS_FALSE);

        /* 清除AWI/EAWI的info record缓存 */
        CNAS_XCC_ClearAWIOrEAWIInfoRecoBuffer();

        /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId, CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING, CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

        /* 退出层2状态机 */
        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 同步call id */
    pstCallInfo->ucCallId = pstIncomingCallRsp->ucCallId;

    if ( VOS_TRUE == pstCallInfo->ucIsByPassAlertAns )
    {
        /* 给XCALL模块发送XCC_XCALL_CALL_CONNECT_IND */
        CNAS_XCC_SndXcallCallConnectInd(pstCallInfo);

        /* 退状态机，进conversation状态 */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_SUCCESS,
                                  CNAS_XCC_MT_CALLING_END_REASON_BUTT);

        CNAS_XCC_QuitFsmL2();
    }
    else
    {
        /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ANSWER,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));

        /* 启动TI_CNAS_XCC_T53M */
        CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);
    }

    /* 如果AWI/EAWI有信息记录，通知XCALL */
    if (VOS_TRUE == pstCallInfo->stAWIorEAWIInfoRecoBuffer.ucIsBufferValid)
    {
        if (CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG == pstCallInfo->stAWIorEAWIInfoRecoBuffer.enMsgType)
        {
            CNAS_XCC_SndXcallInfoRecInd(pstCallInfo->ucCallId,
                                        CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG,
                                        (VOS_UINT8 *)&(pstCallInfo->stAWIorEAWIInfoRecoBuffer.u.stAWIM));
        }
        else
        {
            CNAS_XCC_SndXcallInfoRecInd(pstCallInfo->ucCallId,
                                        CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG,
                                        (VOS_UINT8 *)&(pstCallInfo->stAWIorEAWIInfoRecoBuffer.u.stEAWIM));
        }

        /* 清除AWI/EAWI的info record缓存 */
        CNAS_XCC_ClearAWIOrEAWIInfoRecoBuffer();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvApsIncomingCallRsp_MtCalling_WaitForIncomingRsp
 功能描述  : 收到ID_APS_XCC_INCOMING_CALL_RSP消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月13日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsIncomingCallRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_XCC_INCOMING_CALL_RSP_STRU     *pstIncomingCallRsp = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstIncomingCallRsp = (APS_XCC_INCOMING_CALL_RSP_STRU *)pstMsg;
    pstCallInfo        = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* INCOMING RSP结果失败，通知CAS，退状态机 */
    if (XCC_APS_RESULT_FAIL == pstIncomingCallRsp->enRslt)
    {
        /* 通知接入层REL REQ */
        CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_SERVICE_INACTIVE,
                                  VOS_FALSE);

        /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                                  CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

        /* 退出层2状态机 */
        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 同步call id */
    pstCallInfo->ucCallId = pstIncomingCallRsp->ucCallId;

    /* 如果BYPASS为TRUE，直接进CONVERSATION状态 */
    if (VOS_TRUE == pstCallInfo->ucIsByPassAlertAns)
    {
        /* 给APS模块发送ID_XCC_APS_DATA_CALL_CONN_IND */
        CNAS_XCC_SndApsDataCallConnectInd(pstCallInfo);

        /* 退状态机，进conversation状态 */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_SUCCESS,
                                  CNAS_XCC_MT_CALLING_END_REASON_BUTT);

        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ANSWER,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));

    /* 启动TI_CNAS_XCC_T53M */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);

    /* 待确认:TO DO: 如果AWI/EAWI有信息记录，通知APS */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvSmsIncomingCallRsp_MtCalling_WaitForIncomingRsp
 功能描述  : 收到ID_CSMS_XCC_INCOMING_CALL_RSP消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月13日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvSmsIncomingCallRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CSMS_XCC_INCOMING_CALL_RSP_STRU    *pstIncomingCallRsp = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstIncomingCallRsp = (CSMS_XCC_INCOMING_CALL_RSP_STRU *)pstMsg;
    pstCallInfo        = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* INCOMING RSP结果失败，通知CAS，退状态机 */
    if (XCC_CSMS_RESULT_FAIL == pstIncomingCallRsp->enRslt)
    {
        /* 通知接入层REL REQ */
        CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                                  VOS_FALSE);

        /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                                  CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

        /* 退出层2状态机 */
        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 同步call id */
    pstCallInfo->ucCallId = pstIncomingCallRsp->ucCallId;

    /* 如果BYPASS为TRUE，直接进CONVERSATION状态 */
    if (VOS_TRUE == pstCallInfo->ucIsByPassAlertAns)
    {
        /* 给SMS模块发送CONN_IND */
        CNAS_XCC_SndCsmsCallConnectInd(pstCallInfo);

        /* 退状态机，进conversation状态 */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_SUCCESS,
                                  CNAS_XCC_MT_CALLING_END_REASON_BUTT);

        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ANSWER,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));

    /* 启动TI_CNAS_XCC_T53M */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);

    /* 待确认:TO DO: 如果AWI/EAWI有信息记录，通知SMS */

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXpdsIncomingCallRsp_MtCalling_WaitForIncomingRsp
 功能描述  : 收到ID_XPDS_XCC_INCOMING_CALL_RSP消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月01日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsIncomingCallRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XPDS_XCC_INCOMING_CALL_RSP_STRU    *pstIncomingCallRsp = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo        = VOS_NULL_PTR;

    pstIncomingCallRsp = (XPDS_XCC_INCOMING_CALL_RSP_STRU *)pstMsg;
    pstCallInfo        = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* INCOMING RSP结果失败，通知CAS，退状态机 */
    if (XCC_CSMS_RESULT_FAIL == pstIncomingCallRsp->enRslt)
    {
        /* 通知接入层REL REQ */
        CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                                  VOS_FALSE);

        /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                                  CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

        /* 退出层2状态机 */
        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 同步call id */
    pstCallInfo->ucCallId = pstIncomingCallRsp->ucCallId;

    /* 如果BYPASS为TRUE，直接进CONVERSATION状态 */
    if (VOS_TRUE == pstCallInfo->ucIsByPassAlertAns)
    {
        /* 给XPDS模块发送CONN_IND */
        CNAS_XCC_SndXpdsCallConnectInd(pstCallInfo);

        /* 退状态机，进conversation状态 */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_SUCCESS,
                                  CNAS_XCC_MT_CALLING_END_REASON_BUTT);

        CNAS_XCC_QuitFsmL2();

        return VOS_TRUE;
    }

    /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER);


    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_WAIT_FOR_ANSWER,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));

    /* 启动TI_CNAS_XCC_T53M */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForIncomingRsp
 功能描述  : ID_CNAS_XCC_XCC_ABORT_REQ保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2014年12月15日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfo        = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护定时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* 通过DISC IND，通知XCALL/APS/SMS电话不存在 */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfo, pstAbortReq->enAbortCause, VOS_FALSE);

    /* 通知接入层 REL REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForIncomingRsp
 功能描述  : 收到ID_CAS_CNAS_1X_CALL_TERMINATE_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfoCtx      = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU                    *pstCallTerminateInd = VOS_NULL_PTR;

    pstCallTerminateInd = (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU *)pstMsg;
    pstCallInfoCtx      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* 通知TAF呼叫结束 */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfoCtx,
                                         CNAS_XCC_ConvertTerminateReasonToTafCause(pstCallTerminateInd->enTerminateReason),
                                         VOS_TRUE);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId, \
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForIncomingRsp
 功能描述  : 收到ID_CAS_CNAS_1X_CALL_REL_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月9日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* 通知TAF的模块，呼叫结束 */
    /* TO DO:接入层的rel ind，还没有增加原因值 */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfo, TAF_XCC_CAUSE_MS_NORMAL_RELEASE, VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiWaitForXcallIncomingRsp_MtCalling_WaitForIncomingRsp
 功能描述  : TI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitForXcallIncomingRsp_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 通知TAF的模块，呼叫结束 */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfo, TAF_XCC_CAUSE_INCOMING_RSP_TIME_OUT, VOS_FALSE);

    /* 通知接入层 REL REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* 清除AWI/EAWI的info record缓存 */
    CNAS_XCC_ClearAWIOrEAWIInfoRecoBuffer();

    /* 通知层1，状态机结果为CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForIncomingRsp
 功能描述  : TI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForIncomingRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        当前关机的时候，链路释放是在main control里面处理的，因此不需要与接入层交互，只需要状态迁移，
        同时TAF对应消息的处理
     */

    /* 停止TI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP);

    /* 通知TAF的模块，呼叫结束 */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfo, TAF_XCC_CAUSE_POWER_DOWN_IND, VOS_FALSE);

    /* 通知层1，状态机结果为CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXcallAnsCallReq_MtCalling_WaitForAnswer
 功能描述  : 收到ID_XCALL_XCC_ANSWER_CALL_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallAnsCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_ProcAnswerReq_MtCalling_WaitForAnswer();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvApsAnswerDataCallReq_MtCalling_WaitForAnswer
 功能描述  : 收到ID_APS_XCC_ANSWER_DATA_CALL_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月13日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsAnswerDataCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_ProcAnswerReq_MtCalling_WaitForAnswer();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvCsmsAnswerCallReq_MtCalling_WaitForAnswer
 功能描述  : 收到ID_CSMS_XCC_ANSWER_CALL_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月13日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvCsmsAnswerCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_ProcAnswerReq_MtCalling_WaitForAnswer();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXpdsAnswerCallReq_MtCalling_WaitForAnswer
 功能描述  : 收到ID_XPDS_XCC_ANSWER_CALL_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月01日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsAnswerCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_ProcAnswerReq_MtCalling_WaitForAnswer();

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForAnswer
 功能描述  : 收到ID_CAS_CNAS_1X_CALL_TERMINATE_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfoCtx = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU                    *pstCallTerminateInd = VOS_NULL_PTR;

    pstCallTerminateInd = (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU *)pstMsg;
    pstCallInfoCtx      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    /* 通知TAF呼叫结束 */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfoCtx,
                                         CNAS_XCC_ConvertTerminateReasonToTafCause(pstCallTerminateInd->enTerminateReason),
                                         VOS_TRUE);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForAnswer
 功能描述  : 收到ID_CAS_CNAS_1X_CALL_REL_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月9日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    /* TO DO:接入层的rel ind，还没有增加原因值 */
    /* 通知TAF呼叫结束，REL IND场景原因值均为TAF_XCC_CAUSE_NORMAL_RELEASE */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfoCtx, TAF_XCC_CAUSE_MS_NORMAL_RELEASE, VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXcallHangupCallReq_MtCalling_WaitForAnswer
 功能描述  : 收到ID_XCALL_XCC_HANGUP_CALL_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月9日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallHangupCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)pstMsg;

    /* 停止TI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* 通知接入层REL REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 通知XCALL关声码器 */
    if (VOS_TRUE == pstCallInfoCtx->ucIsCodecOpen)
    {
        CNAS_XCC_SndXcallCodecCloseInd();

        pstCallInfoCtx->ucIsCodecOpen = VOS_FALSE;
    }

    /* 给XCALL模块发送ID_XCC_XCALL_HANGUP_CALL_CNF */
    CNAS_XCC_SndXcallHangUpCallCnf(pstCallInfoCtx->ucCallId);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvSmsEndSmsCallReq_MtCalling_WaitForAnswer
 功能描述  : 收到ID_CSMS_XCC_END_SMS_CALL_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月13日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvSmsEndSmsCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CSMS_XCC_END_SMS_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (CSMS_XCC_END_SMS_CALL_REQ_STRU *)pstMsg;

    /* 停止TI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    /* 通知接入层REL REQ */
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 给APS模块发送ID_XCC_CSMS_END_SMS_CALL_CNF */
    CNAS_XCC_SndCsmsHangupCallCnf(pstCallInfoCtx->ucCallId);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXpdsEndAgpsCallReq_MtCalling_WaitForAnswer
 功能描述  : 收到ID_XPDS_XCC_END_AGPS_CALL_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月06日
   作    者   : y00314741
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsEndAgpsCallReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    XPDS_XCC_END_AGPS_CALL_REQ_STRU    *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XPDS_XCC_END_AGPS_CALL_REQ_STRU *)pstMsg;

    /* 停止TI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    /* 通知接入层REL REQ */
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 给XPDS模块发送ID_XCC_XPDS_END_AGPS_CALL_CNF */
    CNAS_XCC_SndXpdsEndCallCnf(pstCallInfoCtx->ucCallId);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForAnswer
 功能描述  : 收到ID_CAS_CNAS_1X_DSCH_DATA_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd = VOS_NULL_PTR;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;
    CNAS_XCC_AWIM_STRU                 *pstAWIM = VOS_NULL_PTR;
    CNAS_XCC_EAWIM_STRU                *pstEAWIM = VOS_NULL_PTR;

    pstDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;
    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);


    /*
       If the Call Control instance receives a message from layer 3Layer 3 which is
        included in the following list and every message field value is within its permissible
        range, the Call Control instance shall process the message as described below and
        in accordance with the message action time (see 2.6.4.1.5).
            1. Alert With Information Message: The Call Control instance shall reset the
            substate timer for T53m seconds. If this message does not contain a Signal
            information record, the mobile station should use standard alert as defined in
            3.7.5.5.
            2. Extended Alert With Information Message: The Call Control instance shall reset
            the substate timer for T53m seconds. If this message does not contain a Signal
            information record, the mobile station should use standard alert as defined in
            3.7.5.5.
            3. Maintenance Order: The mobile station shall reset the substate timer for T53m
            seconds.
         If the Call Control instance receives a message that is not included in the above list,
        cannot be processed, or requires a capability which is not supported, the Call
        Control instance shall discard the message and send a message rejected indication
        to the layer 3Layer 3, with the reject reason indicated.
    */

    switch (pstDschDataInd->enDschMsgType)
    {
        case CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG:
            /* 完成AWI或EAWI的解码 */
            pstAWIM = (CNAS_XCC_AWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_AWIM_STRU));
            if (VOS_NULL_PTR == pstAWIM)
            {
                return VOS_FALSE;
            }

            if (VOS_OK != CNAS_XCC_DecodeAlertWithInformationMsg(pstDschDataInd, pstAWIM))
            {
                PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);
                return VOS_FALSE;
            }

            /* 重置T53M */
            CNAS_XCC_RestartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);

            /* 给XCALL发送ID_XCC_XCALL_INFO_REC_IND*/
            if ( CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
            {
                CNAS_XCC_SndXcallInfoRecInd(pstCallInfoCtx->ucCallId,
                                            CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG,
                                            (VOS_UINT8 *)pstAWIM);
            }

            /* 待确认 TO DO: 给SMS/DATA CALL发送ID_XCC_XCALL_INFO_REC_IND */

            PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG:
            /* 完成AWI或EAWI的解码 */
            pstEAWIM = (CNAS_XCC_EAWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EAWIM_STRU));
            if (VOS_NULL_PTR == pstEAWIM)
            {
                return VOS_FALSE;
            }

            if (VOS_OK != CNAS_XCC_DecodeExtendedAlertWithInformationMsg(pstDschDataInd, pstEAWIM))
            {
                PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);
                return VOS_FALSE;
            }

            /* 重置T53M */
            CNAS_XCC_RestartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);

            /* 给XCALL发送ID_XCC_XCALL_INFO_REC_IND*/
            if ( CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
            {
                CNAS_XCC_SndXcallInfoRecInd(pstCallInfoCtx->ucCallId,
                                            CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG,
                                            (VOS_UINT8 *)pstEAWIM);
            }

            /* 待确认 TO DO: 给SMS/DATA CALL发送ID_XCC_XCALL_INFO_REC_IND */

            PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);
            break;

        case CAS_CNAS_1X_RX_TCH_ORDER_MSG:
            CNAS_XCC_ProcOrderMsg_MtCalling_WaitForAnswer(pstDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG:
        case CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG:
        case CAS_CNAS_1X_RX_TCH_SEND_BURST_DTMF_MSG:
            /* 编码REJ ORDER */
            NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

            pstCallInfoCtx              = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
            stRejInfo.ucConRef          = pstCallInfoCtx->ucConRef;
            stRejInfo.enRejRxTchMsgType = pstDschDataInd->enDschMsgType;
            stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
            stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_STATE;
            stRejInfo.ulL3PduBitLen     = 0;
            stRejInfo.pucPdudata        = aucPduData;
            CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

            /* 发送ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER)给AS */
            CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                       0, (VOS_UINT16)stRejInfo.ulL3PduBitLen, aucPduData);
            break;

        default:
            CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForAnswer Wrong Msg type", pstDschDataInd->enDschMsgType);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiT53MExpired_MtCalling_WaitForAnswer
 功能描述  : TI_CNAS_XCC_T53M保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiT53MExpired_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 给AS发送CAS_CNAS_1X_REL_REASON_SUB_STATE_TIMER_EXPIRED */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_SUB_STATE_TIMER_EXPIRED,
                              VOS_FALSE);

    /* 通知TAF呼叫结束，REL IND场景原因值均为TAF_XCC_CAUSE_NORMAL_RELEASE */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfoCtx, TAF_XCC_CAUSE_T53M_TIME_OUT, VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForAnswer
 功能描述  : 等待接听时，收到关机请求
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        当前关机的时候，链路释放是在main control里面处理的，因此不需要与接入层交互，只需要状态迁移，
        同时TAF对应消息的处理
     */

    /* 停止TI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    /* 通知TAF呼叫结束 */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfoCtx, TAF_XCC_CAUSE_POWER_DOWN_IND, VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForAnswer
 功能描述  : ID_CNAS_XCC_XCC_ABORT_REQ保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2014年12月15日
    作    者   : y00245242
    修改内容   : 修改原因值上报
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForAnswer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护定时器 */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M);

    /* 根据service type 给TAF发送业务终止指示 */
    CNAS_XCC_NotifyTafCallDisc_MtCalling(pstCallInfoCtx, pstAbortReq->enAbortCause, VOS_FALSE);

    /* 通知AS REL_REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitConnL2Ack
 功能描述  : 收到ID_CAS_CNAS_1X_CALL_TERMINATE_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfoCtx = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU                    *pstCallTerminateInd = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                       enServiceType;

    pstCallTerminateInd = (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU *)pstMsg;
    pstCallInfoCtx      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);


    /* 通知TAF呼叫结束 */
    CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfoCtx,
                                              CNAS_XCC_ConvertTerminateReasonToTafCause(pstCallTerminateInd->enTerminateReason),
                                              TAF_XCC_FAIL_LAYER_L3);

    /* 如果是VOICE CALL或者SMS，则需要将APS给恢复 */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
      || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType) )
    {
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfoCtx->ucConnectId, enServiceType);
    }


    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsDschDataCnf_MtCalling_WaitConnL2Ack
 功能描述  : 收到ID_CAS_CNAS_1X_DSCH_DATA_CNF消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsDschDataCnf_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pstDataCnf;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    pstDataCnf = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU *)pstMsg;
    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 本地保存的segnum与AS上报上来的不一致，需扔掉该条消息 */
    if ( pstCallInfo->ucMsgSeqNum != pstDataCnf->ucMsgSeqNum )
    {
        return VOS_TRUE;
    }

    /* 停止TI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);

    if (CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pstDataCnf->enRslt)
    {

        CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

        /* 根据SO类型判断，给相应模块回复ANSWER CNF */
        CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfo, TAF_XCC_CAUSE_SUCCESS, TAF_XCC_FAIL_LAYER_BUTT);

        if (VOS_TRUE == pstCallInfo->ucIsSoNegCmplt)
        {
            /* 通知XCALL打开CODEC */
            if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
              && (VOS_FALSE == pstCallInfo->ucIsCodecOpen) )
            {
                CNAS_XCC_SndXcallCodecOpenInd(pstCallInfo);
                pstCallInfo->ucIsCodecOpen = VOS_TRUE;
            }

            if (CNAS_XCC_SERVICE_TYPE_DATA_CALL == enServiceType)
            {
                CNAS_XCC_SndApsDataServiceConnectInd(pstCallInfo);
            }

            if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
            {
                CNAS_XCC_SndCsmsServiceConnectInd(pstCallInfo);
            }

            if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType)
            {
                CNAS_XCC_SndXpdsServiceConnectInd(pstCallInfo);
            }
        }

        /* 退状态机，L1状态机迁到CONVERSATION状态 */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_SUCCESS,
                                  CNAS_XCC_MT_CALLING_END_REASON_BUTT);

        /* 退出层2状态机 */
        CNAS_XCC_QuitFsmL2();
    }
    else
    {
        /* ERROR LOG */
        CNAS_WARNING_LOG1(UEPS_PID_XCC,
                          "CNAS_XCC_RcvAsDschDataCnf_MtCalling_WaitConnL2Ack: unexpected result !",
                          pstDataCnf->enRslt);

        /* 通知接入层REL REQ */
        CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                                  VOS_FALSE);

        /* 通知TAF的模块，呼叫结束 */
        CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfo, TAF_XCC_CAUSE_CONNECT_ORDER_ACK_FAILURE, TAF_XCC_FAIL_LAYER_L3);

        /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
        CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                                  CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                                  CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

        /* 退出层2状态机 */
        CNAS_XCC_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitConnL2Ack
 功能描述  : 收到ID_CAS_CNAS_1X_CALL_REL_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月9日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);


    /* 通知TAF的模块，呼叫结束 */
    /* TO DO:接入层的rel ind，还没有增加原因值 */
    CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfo, TAF_XCC_CAUSE_MS_NORMAL_RELEASE, TAF_XCC_FAIL_LAYER_L3);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXcallHangupCallReq_MtCalling_WaitConnL2Ack
 功能描述  : 收到ID_XCALL_XCC_HANGUP_CALL_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月9日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallHangupCallReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)pstMsg;

    /* 停止TI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* 通知接入层REL REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 通知XCALL关声码器 */
    if (VOS_TRUE == pstCallInfo->ucIsCodecOpen)
    {
        CNAS_XCC_SndXcallCodecCloseInd();

        pstCallInfo->ucIsCodecOpen = VOS_FALSE;
    }

    /* 给XCALL模块发送ID_XCC_XCALL_HANGUP_CALL_CNF */
    CNAS_XCC_SndXcallHangUpCallCnf(pstCallInfo->ucCallId);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvApsHangupDataCallReq_MtCalling_WaitConnL2Ack
 功能描述  : 收到ID_APS_XCC_HANGUP_DATA_CALL_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月13日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsHangupDataCallReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    APS_XCC_HANGUP_DATA_CALL_REQ_STRU  *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (APS_XCC_HANGUP_DATA_CALL_REQ_STRU *)pstMsg;

    /* 停止TI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 给APS模块发送ID_XCC_APS_HANGUP_DATA_CALL_CNF */
    CNAS_XCC_SndApsHangupDataCallCnf(pstCallInfoCtx->ucCallId);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvSmsHangupCallReq_MtCalling_WaitConnL2Ack
 功能描述  : 收到ID_CSMS_XCC_END_SMS_CALL_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年10月13日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvSmsHangupCallReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CSMS_XCC_END_SMS_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (CSMS_XCC_END_SMS_CALL_REQ_STRU *)pstMsg;

    /* 停止TI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 给SMS模块发送ID_XCC_CSMS_END_SMS_CALL_CNF */
    CNAS_XCC_SndCsmsHangupCallCnf(pstCallInfoCtx->ucCallId);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXpdsHangupCallReq_MtCalling_WaitConnL2Ack
 功能描述  : 收到ID_XPDS_XCC_END_AGPS_CALL_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月06日
   作    者   : y00314741
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsHangupCallReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    XPDS_XCC_END_AGPS_CALL_REQ_STRU    *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XPDS_XCC_END_AGPS_CALL_REQ_STRU *)pstMsg;

    /* 停止TI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 给XPDS模块发送ID_XCC_XPDS_END_AGPS_CALL_CNF */
    CNAS_XCC_SndXpdsEndCallCnf(pstCallInfoCtx->ucCallId);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_RcvTiWaitL2AckExpired_MtCalling_WaitConnL2Ack
 功能描述  : TI_CNAS_XCC_WAIT_CONN_L2_ACK保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitL2AckExpired_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();


    /* 通知TAF的模块，呼叫结束 */
    CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfo, TAF_XCC_CAUSE_L2_ACK_TIME_OUT, TAF_XCC_FAIL_LAYER_L3);

    /* 通知AS REL REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccAbortReq_MtCalling_WaitConnL2Ack
 功能描述  : ID_CNAS_XCC_XCC_ABORT_REQ保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2014年12月15日
    作    者   : y00245242
    修改内容   : 修改原因值上报
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护定时器 */
    CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);

    CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfoCtx, pstAbortReq->enAbortCause, VOS_FALSE);

    /* 通知AS REL_REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfoCtx->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitConnL2Ack
 功能描述  : 等待L2 ACK时，收到关机请求
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月10日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitConnL2Ack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        当前关机的时候，链路释放是在main control里面处理的，因此不需要与接入层交互，只需要状态迁移，
        同时TAF对应消息的处理
     */

    /* 停止TI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK);


    /* 通知TAF的模块，呼叫结束 */
    CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(pstCallInfo, TAF_XCC_CAUSE_POWER_DOWN_IND, TAF_XCC_FAIL_LAYER_L3);

    /* 通知层1，状态机结果CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMtCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}




/*****************************************************************************
 函 数 名  : CNAS_XCC_NotifyTafCallDisc_MtCalling
 功能描述  : 通知TAF的模块，呼叫结束
 输入参数  : pstCallInfo -- 状态机的呼叫信息
             enCause     -- 结束原因致
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月15日
   作    者   : h00246512
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_NotifyTafCallDisc_MtCalling(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    VOS_BOOL                            isNeedToResumeAps
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    /* 将SO转换成SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    switch(enServiceType)
    {
        case CNAS_XCC_SERVICE_TYPE_VOICE_CALL:
            /* 通知XCALL关声码器 */
            if (VOS_TRUE == pstCallInfo->ucIsCodecOpen)
            {
                CNAS_XCC_SndXcallCodecCloseInd();

                pstCallInfo->ucIsCodecOpen = VOS_FALSE;
            }

            /* 通知XCALL呼叫结束 */
            CNAS_XCC_SndXcallCallDiscInd(pstCallInfo->ucCallId,pstCallInfo->ucConnectId, enCause);

            if (VOS_TRUE == isNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_VOICE_CALL);
            }
            break;

        case CNAS_XCC_SERVICE_TYPE_DATA_CALL:
            /* 通知APS呼叫结束 */
            CNAS_XCC_SndApsDataCallDiscInd(pstCallInfo, enCause);
            break;

        case CNAS_XCC_SERVICE_TYPE_SMS:
            /* 这个地方貌似缺与SMS接口 */
            if (VOS_TRUE == isNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_SMS);
            }
            break;

        case CNAS_XCC_SERVICE_TYPE_AGPS_CALL:
            if (VOS_TRUE == isNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_AGPS_CALL);
            }
            break;

        case CNAS_XCC_SERVICE_TYPE_LOOPBACK:
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_NotifyTafCallDisc_MtCalling: Wrong Service Type");
            break;
    }

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling
 功能描述  : 通知TAF的模块，呼叫的应答结果
 输入参数  : pstCallInfo -- 状态机的呼叫信息
             enCause     -- 结束原因值
             enFailLayer -- 异常的层级
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月15日
   作    者   : h00246512
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32        enServiceType;

    /* 将SO转换成SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    switch(enServiceType)
    {
        case CNAS_XCC_SERVICE_TYPE_VOICE_CALL:
            CNAS_XCC_SndXcallAnswerCallCnf(pstCallInfo->ucCallId,
                                           pstCallInfo->ucConRef,
                                           pstCallInfo->enCurrentSo,
                                           enFailLayer,
                                           enCause);
            break;

        case CNAS_XCC_SERVICE_TYPE_DATA_CALL:
            /* 通知APS呼叫结束 */
            CNAS_XCC_SndApsAnswerDataCallCnf(pstCallInfo->ucCallId,
                                             enCause);
            break;

        case CNAS_XCC_SERVICE_TYPE_SMS:
            /* 通知sms呼叫结束 */
            CNAS_XCC_SndCsmsAnswerCallCnf(pstCallInfo->ucCallId,
                                          enCause);
            break;

        case CNAS_XCC_SERVICE_TYPE_AGPS_CALL:
            /* 通知XPDS呼叫结束 */
            CNAS_XCC_SndXpdsAnswerCallCnf(pstCallInfo->ucCallId,
                                          enCause);
            break;

        case CNAS_XCC_SERVICE_TYPE_LOOPBACK:
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_NotifyTafAnswerCallCnf_MtCalling: Wrong Service Type");
            break;
    }

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcOrderMsg_L1Main_WaitForOrder
 功能描述  : 处理空口的Order消息
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月25日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcOrderMsg_MtCalling_WaitForOrder(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_ORDRM_STRU                 stOrdrm;
    VOS_UINT32                          ulRslt;
    CNAS_XCC_ORDER_TYPE_ENUM_UINT8      enOrderType;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    if (VOS_OK != CNAS_XCC_DecodeOrderMsg(pstDschDataInd, &stOrdrm))
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation: Decode FAIL ");
        return;
    }

    /* 获取具体的order消息类型 */
    ulRslt = CNAS_XCC_GetOrderSpecificMsgType(&(stOrdrm.stOrder), &enOrderType);
    if (VOS_OK != ulRslt)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation: CAS_1X_MAIN_GetOrderSpecificMsgType FAIL ", ulRslt);

        return ;
    }

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    switch(enOrderType)
    {
        case CNAS_XCC_ORDER_TYPE_MAINTENANCE:
            /* 停T52M */
            CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T52M);

            /* 如果是环回模式，则自动接听 */
            if ( CNAS_XCC_SERVICE_TYPE_LOOPBACK == enServiceType)
            {
                CNAS_XCC_AutoAnswerLoopBackService_MtCalling(pstCallInfoCtx);
                return ;
            }

            /* 给XCALL发送INCOMING CALL IND */
            if ( CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
            {
                /* 给XCALL发送INCOMING CALL IND */
                CNAS_XCC_SndXcallIncomingCallInd(pstCallInfoCtx);
            }

            /* SEND DATA CALL OR SMS incoming call ind */
            if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
            {
                /* 给CSMS发送INCOMING CALL IND */
                CNAS_XCC_SndCsmsIncomingCallInd(pstCallInfoCtx);
            }

            if (CNAS_XCC_SERVICE_TYPE_DATA_CALL == enServiceType)
            {
                /* 给APS发送INCOMING CALL IND */
                CNAS_XCC_SndApsIncomingCallInd(pstCallInfoCtx);
            }

            if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType)
            {
                CNAS_XCC_SndXpdsIncomingCallInd(pstCallInfoCtx);
            }

            /* 可维可测，上报1x call state*/
            CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL,
                                    CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
            CNAS_XCC_SndXcc1xCallStateUpdateInd();

            /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP */
            CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP);

            /* 启动TI_CNAS_XCC_WAIT_FOR_XCALL_INCOMING_RSP */
            CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP, TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP_LEN);
            break;

        default:
            CNAS_ERROR_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation Wrong enOrderType", enOrderType);
            break;
    }

    return;

}


/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcOrderMsg_L1Main_WaitForAnswer
 功能描述  : 处理空口的Order消息
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月25日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcOrderMsg_MtCalling_WaitForAnswer(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_ORDRM_STRU                 stOrdrm;
    VOS_UINT32                          ulRslt;
    CNAS_XCC_ORDER_TYPE_ENUM_UINT8      enOrderType;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    if (VOS_OK != CNAS_XCC_DecodeOrderMsg(pstDschDataInd, &stOrdrm))
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation: Decode FAIL ");
        return;
    }

    /* 获取具体的order消息类型 */
    ulRslt = CNAS_XCC_GetOrderSpecificMsgType(&(stOrdrm.stOrder), &enOrderType);
    if (VOS_OK != ulRslt)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation: CAS_1X_MAIN_GetOrderSpecificMsgType FAIL ", ulRslt);

        return ;
    }

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    switch(enOrderType)
    {
        case CNAS_XCC_ORDER_TYPE_MAINTENANCE:
            /* 重置T53M */
            CNAS_XCC_RestartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_T53M, TI_CNAS_XCC_T53M_LEN);
            break;

        case CNAS_XCC_ORDER_TYPE_SERVICE_OPTION_CONTROL:
            break;

        default:
            CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_WaitForAnswer Ordertype", enOrderType);
            break;
    }

    return;

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcAnswerReq_MtCalling_WaitForAnswer
 功能描述  : 处理XCALL/APS/CSMS接听的接听请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月25日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcAnswerReq_MtCalling_WaitForAnswer(VOS_VOID)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;
    VOS_UINT8                           ucMsgSeqNum;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止TI_CNAS_XCC_T53M */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_T53M);

    /* 分配SEQ NUM */
    pstCallInfo->ucMsgSeqNum = CNAS_XCC_AllocSeqNum();
    ucMsgSeqNum              = pstCallInfo->ucMsgSeqNum;

    /* 给AS发送ID_CNAS_CAS_1X_DSCH_DATA_REQ(connect order) */
    ulPduDataLen = 0;
    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

    CNAS_XCC_EncodeTxTchConnectOrderMsg(pstCallInfo->ucConRef, aucPduData, &ulPduDataLen);

    CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_CONNECT_ORDER,
                               ucMsgSeqNum, (VOS_UINT16)ulPduDataLen, aucPduData);

    /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_CONNECT_L2_ACK */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_CONNECT_L2_ACK);

    /* 启动TI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK, TI_CNAS_XCC_WAIT_CONN_L2_ACK_LEN);
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_AutoAnswerLoopBackService_MtCalling
 功能描述  : 环回业务的自动应答处理
 输入参数  : pstCallInfoCtx - 呼叫上下文
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月20日
   作    者   : h00246512
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_AutoAnswerLoopBackService_MtCalling(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx
)
{
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;
    VOS_UINT8                           ucMsgSeqNum;

    /* 分配SEQ NUM */
    pstCallInfoCtx->ucMsgSeqNum = CNAS_XCC_AllocSeqNum();
    ucMsgSeqNum                 = pstCallInfoCtx->ucMsgSeqNum;

    /* 给AS发送ID_CNAS_CAS_1X_DSCH_DATA_REQ(connect order) */
    ulPduDataLen = 0;
    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

    CNAS_XCC_EncodeTxTchConnectOrderMsg(pstCallInfoCtx->ucConRef, aucPduData, &ulPduDataLen);

    CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_CONNECT_ORDER,
                               ucMsgSeqNum, (VOS_UINT16)ulPduDataLen, aucPduData);

    /* 状态迁移到CNAS_XCC_MT_CALLING_STA_WAIT_CONNECT_L2_ACK */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MT_CALLING_STA_WAIT_CONNECT_L2_ACK);

    /* 启动TI_CNAS_XCC_WAIT_CONN_L2_ACK */
    CNAS_XCC_StartTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_WAIT_CONN_L2_ACK, TI_CNAS_XCC_WAIT_CONN_L2_ACK_LEN);
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 函 数 名  : CNAS_XCC_CovertVoiceCallPagingIndSo
 功能描述  : 加密能力开启时，强制将语音呼叫类型的SO 转换为CAS_CNAS_1X_SO_3_EVRC
 输入参数  : struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月11日
    作    者   : l00359089
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_CovertVoiceCallPagingIndSo(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                 *enSo
)
{
    CNAS_XCC_CALL_NVIM_CFG_STRU        *pstCallNvimCfg   = VOS_NULL_PTR;

    pstCallNvimCfg      = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

    /*电信协议中要求"加密终端应关闭所有语音通话（包括普通通话和加密通话）的EVRC-B 功能"，所以强制转换SO */
    if ((VOS_TRUE == pstCallNvimCfg->ucEccSrvCap)
     && (VOS_TRUE == pstCallNvimCfg->ucEccSrvStatus))
    {
        if ((CAS_CNAS_1X_SO_3_EVRC       == (*enSo))
         || (CAS_CNAS_1X_SO_17_VOICE_13K == (*enSo))
         || (CAS_CNAS_1X_SO_68_EVRC_B    == (*enSo))
         || (CAS_CNAS_1X_SO_73_EVRC_NW   == (*enSo))
         || (CAS_CNAS_1X_SO_18_OTASP     == (*enSo)))
        {
            *enSo = CAS_CNAS_1X_SO_3_EVRC;
        }
    }
}
#endif


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





