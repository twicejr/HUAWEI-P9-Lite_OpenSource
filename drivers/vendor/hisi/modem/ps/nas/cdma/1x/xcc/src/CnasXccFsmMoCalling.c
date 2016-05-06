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
#include "CnasXccFsmMoCalling.h"
#include "CnasXccFsmMoCallingTbl.h"
#include "xcc_xcall_pif.h"
#include "cas_1x_access_ctrl_proc_nas_pif.h"
#include "CnasXccCtx.h"
#include "CnasXccComFunc.h"
#include "CnasXccSndAps.h"
#include "CnasXccSndCas.h"
#include "CnasXccSndXcall.h"
#include "CnasXccSndInternalMsg.h"
#include "cas_1x_control_main_nas_pif.h"
#include "CnasMntn.h"
#include "xcc_aps_pif.h"
#include "xcc_sms_pif.h"
#include "CnasXccSndCsms.h"
#include "CnasCcb.h"
#include "CnasXccSndXpds.h"
#include  "xcc_xpds_pif.h"
#include "Nas_Mem.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_FSM_MO_CALLING_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXcallOrigReq_MoCalling_Init
 功能描述  : XCC接收到主动呼叫XCALL_XCC_ORIG_CALL_REQ的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月6日
    作    者   : c00294324
    修改内容   : 新生成函数

  2.日    期   : 2015年12月24日
    作    者   : y00245242
    修改内容   : privacy mode特性开发
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallOrigReq_MoCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstOrigCallReq = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo    = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    VOS_UINT8                           ucSrId;
    VOS_UINT32                          ulRslt;

    pstOrigCallReq = (XCALL_XCC_ORIG_CALL_REQ_STRU*)pstMsg;

    /* 保存入口消息 */
    CNAS_XCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 存储呼叫相关的信息到全局变量中，设置当前呼叫为主叫 */
    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstCallInfo->enCurrentSo                    =   pstOrigCallReq->stSoInfo.enSo;
    pstCallInfo->ucCallId                       =   pstOrigCallReq->ucCallId;
    pstCallInfo->enInitSo                       =   pstOrigCallReq->stSoInfo.enSo;
    pstCallInfo->ucIsMoCall                     =   VOS_TRUE;

    /* 此处增加 privacy mode，ucIsL2ErrReOrig，ucReOrigCount  */
    pstCallInfo->ucReOrigCount                  =   pstOrigCallReq->ucReOrigCount;
    pstCallInfo->ucIsL2ErrReOrig                =   pstOrigCallReq->ucIsL2ErrReOrig;
    pstCallInfo->ucIsEmergencyCall              =   pstOrigCallReq->ucIsEmergencyCall;

    pstCallInfo->enReqPrivacyMode               =   (XCALL_XCC_PRIVACY_MODE_ENUM_UINT8)(CNAS_XCC_GetCtxAddr()->stCallNvimCfg.ucPrivacyMode);

    /* 记录拨号 */
    pstCallInfo->stCalledPartyNum.enDigitMode   = pstOrigCallReq->enDigitMode;
    pstCallInfo->stCalledPartyNum.enNumPlan     = (CAS_CNAS_1X_NUMBER_PLAN_ENUM_UINT8)pstOrigCallReq->stCalledPartyNum.enNumPlan;
    pstCallInfo->stCalledPartyNum.enNumType     = (CAS_CNAS_1X_NUMBER_TYPE_ENUM_UINT8)pstOrigCallReq->stCalledPartyNum.enNumType;
    pstCallInfo->stCalledPartyNum.ucDigitNum    = pstOrigCallReq->stCalledPartyNum.ucDigitNum;
    NAS_MEM_CPY_S(pstCallInfo->stCalledPartyNum.aucDigit,
                  sizeof(pstCallInfo->stCalledPartyNum.aucDigit),
                  pstOrigCallReq->stCalledPartyNum.aucDigit,
                  sizeof(pstCallInfo->stCalledPartyNum.aucDigit));

    if (VOS_TRUE   ==  pstOrigCallReq->bitOpCalledPartySubAddr)
    {
        pstCallInfo->stCalledPartySubAddr       =   pstOrigCallReq->stCalledPartySubAddr;
        pstCallInfo->bitOpCalledPartySubAddr    =   VOS_TRUE;
    }

    if (VOS_TRUE   ==  pstOrigCallReq->bitOpCallingPartyNum)
    {
        pstCallInfo->stCallingPartyNum          =   pstOrigCallReq->stCallingPartyNum;
        pstCallInfo->bitOpCallingPartyNum       =   VOS_TRUE;
    }

    if (VOS_TRUE   ==  pstOrigCallReq->bitOpCallingPartySubAddr)
    {
        pstCallInfo->stCallingPartySubAddr      =   pstOrigCallReq->stCallingPartySubAddr;
        pstCallInfo->bitOpCallingPartySubAddr   =   VOS_TRUE;
    }

    /* 语音呼叫必然是重新分配一个SR_ID */
    /* 如果SR_ID分配失败，则认为本次呼叫异常，直接做呼叫失败处理 */
    if (CNAS_CCB_GetPRevInUse() >= P_REV_IN_USE_6)
    {
        ulRslt = CNAS_XCC_AllocSrId(pstCallInfo->enInitSo,
                                    &ucSrId,
                                    pstCallInfo->ucConnectId);
        if (VOS_FALSE == ulRslt)
        {
            CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                              TAF_XCC_CAUSE_ALLOC_SRID_FAIL,
                                              TAF_XCC_FAIL_LAYER_L3,
                                              VOS_FALSE,
                                              0);

            /* 通知层1，状态机结果 CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
            CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                                      CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                                      CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

            CNAS_XCC_QuitFsmL2();

            return VOS_TRUE;
        }
        pstCallInfo->ucSrId = ucSrId;
    }
    else
    {
        pstCallInfo->ucSrId = 1;
    }

    /* 将SO转换成SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType))
    {
        /* 发送挂起APS消息ID_XCC_APS_DATA_CALL_SUSPEND_IND */
        CNAS_XCC_SndApsDataCallSuspendInd(pstCallInfo->ucConnectId, enServiceType);

        /* 迁入 CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP);

        /* 启动保护定时器TI_CNAS_XSD_WAIT_APS_SUSPEND_RSP，时长TI_CNAS_XSD_WAIT_APS_SUSPEND_RSP_LEN */
        CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN);

    }
    else
    {
        /* 发送ID_CNAS_CAS_1X_EST_REQ给接入层 */
        CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_ORIGINATION, pstCallInfo);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_ORIG_CALL,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();

        /* 迁入CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF层2子状态*/
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF);

        /* 开启保护定时器TI_CNAS_XCC_WAIT_AS_EST_CNF，时长TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN */
        CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvOrigDataCallReq_MoCalling_Init
 功能描述  : XCC接收到APS发起的DATA CALL请求
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigDataCallReq_MoCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_XCC_ORIG_DATA_CALL_REQ_STRU    *pstOrigCallReq = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo    = VOS_NULL_PTR;
    VOS_UINT8                           ucSrId;
    VOS_UINT32                          ulRslt;

    pstOrigCallReq = (APS_XCC_ORIG_DATA_CALL_REQ_STRU*)pstMsg;

    /* 保存入口消息 */
    CNAS_XCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 保存APS发送过来的数据信息 */
    pstCallInfo                   = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstCallInfo->enCurrentSo      = pstOrigCallReq->enSo;
    pstCallInfo->enInitSo         = pstOrigCallReq->enSo;
    pstCallInfo->ucCallId         = pstOrigCallReq->ucCallId;
    pstCallInfo->ucIsDormDataCall = pstOrigCallReq->ucIsDormDataCall;
    pstCallInfo->ucIsDataReady    = pstOrigCallReq->ucDrsFlg;
    pstCallInfo->ucIsL2ErrReOrig  = pstOrigCallReq->ucIsL2ErrReOrig;
    pstCallInfo->ucReOrigCount    = pstOrigCallReq->ucReOrigCount;
    pstCallInfo->ucIsMoCall       = VOS_TRUE;

    pstCallInfo->stCalledPartyNum.enDigitMode = pstOrigCallReq->stDialNumInfo.enDigitMode;
    pstCallInfo->stCalledPartyNum.ucDigitNum  = pstOrigCallReq->stDialNumInfo.ucDigitNum;
    NAS_MEM_CPY_S(pstCallInfo->stCalledPartyNum.aucDigit, sizeof(pstCallInfo->stCalledPartyNum.aucDigit),
                  pstOrigCallReq->stDialNumInfo.aucDigit, sizeof(pstCallInfo->stCalledPartyNum.aucDigit));

    if (0 != pstOrigCallReq->stQosInfo.ucQosParaLength)
    {
        pstCallInfo->bitOpQosInfo     = VOS_TRUE;
        pstCallInfo->ucQosInfoLen     = pstOrigCallReq->stQosInfo.ucQosParaLength;
        NAS_MEM_CPY_S(pstCallInfo->aucQosInfo, sizeof(pstCallInfo->aucQosInfo),
                      pstOrigCallReq->stQosInfo.aucQosPara, sizeof(pstCallInfo->aucQosInfo));
    }

    if (VOS_TRUE == pstOrigCallReq->ulIsPrevHrpdMode)
    {
        pstCallInfo->ulIsPrevHrpdFlg             = VOS_TRUE;
        pstCallInfo->stPrevHrpdActNetInfo.usSid  = pstOrigCallReq->stPrevHrpdActInfo.usSid;
        pstCallInfo->stPrevHrpdActNetInfo.usNid  = pstOrigCallReq->stPrevHrpdActInfo.usNid;
        pstCallInfo->stPrevHrpdActNetInfo.usPzid = pstOrigCallReq->stPrevHrpdActInfo.usPzid;
    }
    else
    {
        pstCallInfo->ulIsPrevHrpdFlg             = VOS_FALSE;
    }

    /* 如果APS携带的是无效的SR_ID，则直接进行分配，否则使用APS携带的SR_ID */
    /* 如果SR_ID分配失败，则认为本次呼叫异常，直接做呼叫失败处理 */
    if (CNAS_XCC_INVALID_SR_ID == pstOrigCallReq->ucSrId)
    {
        ulRslt = CNAS_XCC_AllocSrId(pstCallInfo->enInitSo,
                                    &ucSrId,
                                    pstCallInfo->ucConnectId);
        if (VOS_FALSE == ulRslt)
        {
            CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                              TAF_XCC_CAUSE_ALLOC_SRID_FAIL,
                                              TAF_XCC_FAIL_LAYER_L3,
                                              VOS_FALSE,
                                              0);

            /* 通知层1，状态机结果 CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
            CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                                      CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                                      CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

            CNAS_XCC_QuitFsmL2();

            return VOS_TRUE;
        }

        pstCallInfo->ucSrId = ucSrId;
    }
    else
    {
        pstCallInfo->ucSrId = pstOrigCallReq->ucSrId;
        CNAS_XCC_UpdateSrIdUsed(pstCallInfo->enInitSo,
                                pstOrigCallReq->ucSrId,
                                pstCallInfo->ucConnectId);

    }


    /* 给CAS发送建链请求 */
    CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_ORIGINATION, pstCallInfo);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_ORIG_CALL,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    /* 迁入CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF层2子状态*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF);

    /* 开启保护定时器TI_CNAS_XCC_WAIT_AS_EST_CNF，时长TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvOrigSmsCallReq_MoCalling_Init
 功能描述  : XCC接收到SMS发起的SMS CALL请求
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigSmsCallReq_MoCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CSMS_XCC_ORIG_SMS_CALL_REQ_STRU    *pstOrigCallReq = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo    = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    VOS_UINT8                           ucSrId;
    VOS_UINT32                          ulRslt;

    pstOrigCallReq = (CSMS_XCC_ORIG_SMS_CALL_REQ_STRU *)pstMsg;

    /* 保存入口消息 */
    CNAS_XCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 保存SMS发送过来的数据信息 */
    pstCallInfo                  = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstCallInfo->enCurrentSo     = pstOrigCallReq->enSo;
    pstCallInfo->enInitSo        = pstOrigCallReq->enSo;
    pstCallInfo->ucCallId        = pstOrigCallReq->ucCallId;
    pstCallInfo->ucIsL2ErrReOrig = pstOrigCallReq->ucIsL2ErrReOrig;
    pstCallInfo->ucReOrigCount   = pstOrigCallReq->ucL2ErrReOrigCount;

    /* 短信呼叫必然是重新分配一个SR_ID */
    /* 如果SR_ID分配失败，则认为本次呼叫异常，直接做呼叫失败处理 */
    if (CNAS_CCB_GetPRevInUse() >= P_REV_IN_USE_6)
    {
        ulRslt = CNAS_XCC_AllocSrId(pstCallInfo->enInitSo,
                                    &ucSrId,
                                    pstCallInfo->ucConnectId);
        if (VOS_FALSE == ulRslt)
        {
            CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                              TAF_XCC_CAUSE_ALLOC_SRID_FAIL,
                                              TAF_XCC_FAIL_LAYER_L3,
                                              VOS_FALSE,
                                              0);

            /* 通知层1，状态机结果 CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
            CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                                      CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                                      CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

            CNAS_XCC_QuitFsmL2();

            return VOS_TRUE;
        }
        pstCallInfo->ucSrId = ucSrId;
    }
    else
    {
        pstCallInfo->ucSrId = 1;
    }

    /* 将SO转换成SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstOrigCallReq->enSo, &enServiceType);

    /* 发送挂起APS消息ID_XCC_APS_DATA_CALL_SUSPEND_IND */
    CNAS_XCC_SndApsDataCallSuspendInd(pstCallInfo->ucConnectId, enServiceType);

    /* 迁入 CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP);

    /* 启动保护定时器TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP，时长TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvOrigAgpsCallReq_MoCalling_Init
 功能描述  : XCC接收到AGPS发起的AGPS CALL请求
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月31日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigAgpsCallReq_MoCalling_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU   *pstOrigCallReq = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo    = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    VOS_UINT8                           ucSrId;
    VOS_UINT32                          ulRslt;

    pstOrigCallReq = (XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU *)pstMsg;

    /* 保存入口消息 */
    CNAS_XCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 保存XPDS发送过来的数据信息 */
    pstCallInfo                  = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstCallInfo->enCurrentSo     = pstOrigCallReq->enSo;
    pstCallInfo->enInitSo        = pstOrigCallReq->enSo;
    pstCallInfo->ucCallId        = pstOrigCallReq->ucCallId;
    pstCallInfo->ucIsL2ErrReOrig = pstOrigCallReq->ucIsL2ErrReOrig;
    pstCallInfo->ucReOrigCount   = pstOrigCallReq->ucL2ErrReOrigCount;

    /* AGPS呼叫必然是重新分配一个SR_ID */
    /* 如果SR_ID分配失败，则认为本次呼叫异常，直接做呼叫失败处理 */
    if (CNAS_CCB_GetPRevInUse() >= P_REV_IN_USE_6)
    {
        ulRslt = CNAS_XCC_AllocSrId(pstCallInfo->enInitSo,
                                    &ucSrId,
                                    pstCallInfo->ucConnectId);
        if (VOS_FALSE == ulRslt)
        {
            CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                              TAF_XCC_CAUSE_ALLOC_SRID_FAIL,
                                              TAF_XCC_FAIL_LAYER_L3,
                                              VOS_FALSE,
                                              0);

            /* 通知层1，状态机结果 CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
            CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                                      CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                                      CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

            CNAS_XCC_QuitFsmL2();

            return VOS_TRUE;
        }
        pstCallInfo->ucSrId = ucSrId;
    }
    else
    {
        pstCallInfo->ucSrId = 1;
    }

    /* 将SO转换成SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstOrigCallReq->enSo, &enServiceType);

    /* 发送挂起APS消息ID_XCC_APS_DATA_CALL_SUSPEND_IND */
    CNAS_XCC_SndApsDataCallSuspendInd(pstCallInfo->ucConnectId, enServiceType);

    /* 迁入 CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP);

    /* 启动保护定时器TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP，时长TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvApsSuspendRsp_MoCalling_WaitApsSuspendRsp
 功能描述  : XCC处于等待APS挂起回复状态时，接收到APS发送的ID_APS_XCC_DATA_CALL_SUSPEND_RSP
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月6日
    作    者   : c00294324
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsSuspendRsp_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* 发送ID_CNAS_CAS_1X_EST_REQ给接入层 */
    CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_ORIGINATION, pstCallInfo);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_ORIG_CALL,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    /* 迁入CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF层2子状态*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF);

    /* 开启保护定时器TI_CNAS_XCC_WAIT_AS_EST_CNF，时长TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXcallHangUpReq_MoCalling_WaitApsSuspendRsp
 功能描述  : XCC处于等待APS挂起回复状态时，接收到XCALL发送的ID_XCALL_XCC_HANGUP_CALL_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月6日
    作    者   : c00294324
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallHangupReq_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护计时器TI_CNAS_XSD_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* 给XCALL模块发送ID_XCC_XCALL_HANGUP_CALL_CNF */
    CNAS_XCC_SndXcallHangUpCallCnf(pstCallInfo->ucCallId);

    /* 通知APS 取消挂起APS，发送ID_XCC_APS_DATA_CALL_RESUME_IND */
    CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_VOICE_CALL);

    /* 通知层1，状态机结果为CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitApsSuspendRsp
 功能描述  : XCC处于等待APS挂起回复状态时，接收到SMS发送的ID_CSMS_XCC_END_SMS_CALL_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护计时器TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* 给CSMS模块发送ID_XCC_CSMS_END_SMS_CALL_CNF */
    CNAS_XCC_SndCsmsHangupCallCnf(pstCallInfo->ucCallId);

    /* 通知APS 取消挂起APS，发送ID_XCC_APS_DATA_CALL_RESUME_IND */
    CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_SMS);

    /* 通知层1，状态机结果为CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId, CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED, CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXpdsEndCallReq_MoCalling_WaitApsSuspendRsp
 功能描述  : XCC处于等待APS挂起回复状态时，接收到XPDS发送的ID_XPDS_XCC_END_AGPS_CALL_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月01日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsEndCallReq_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护计时器TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* 给XPDS模块发送ID_XCC_XPDS_END_AGPS_CALL_CNF */
    CNAS_XCC_SndXpdsEndCallCnf(pstCallInfo->ucCallId);

    /* 通知APS 取消挂起APS，发送ID_XCC_APS_DATA_CALL_RESUME_IND */
    CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_AGPS_CALL);

    /* 通知层1，状态机结果为CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId, CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED, CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccAbortReq_MoCalling_WaitApsSuspendRsp
 功能描述  : XCC处于等待APS挂起回复状态时，接收到SMS发送的ID_CNAS_XCC_XCC_ABORT_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2014年12月15日
    作    者   : y00245242
    修改内容   : 修改原因值上报

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护计时器TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* 根据呼叫类型，通知TAF，呼叫结束 */
    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo, pstAbortReq->enAbortCause, TAF_XCC_FAIL_LAYER_L3, VOS_TRUE, 0);

    /* 通知层1，状态机结果为CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId, CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED, CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MoCalling_WaitApsSuspendRsp
 功能描述  : XCC处于等待APS挂起回复状态时，保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MoCalling_WaitApsSuspendRsp:time out");

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 发送ID_CNAS_CAS_1X_EST_REQ给接入层 */
    CNAS_XCC_SndCasEstReq(CAS_CNAS_1X_EST_TYPE_ORIGINATION, pstCallInfo);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_ORIG_CALL,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    /* 迁入CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF层2子状态*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_AS_EST_CNF);

    /* 开启保护定时器TI_CNAS_XCC_WAIT_AS_EST_CNF，时长TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF, TI_CNAS_XCC_WAIT_AS_EST_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitApsSuspendRsp
 功能描述  : XCC处于等待挂起回复状态，收到关机指令
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : c00294324
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitApsSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        当前关机的时候，链路释放是在main control里面处理的，因此不需要与接入层交互，只需要状态迁移，
        同时TAF对应消息的处理
     */
    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP);

    /* 向XCALL发送 ID_XCALL_XCC_ORIG_CALL_CNF (FAIL) */
    CNAS_XCC_SndXcallOrigCallCnf(pstCallInfo->ucCallId, TAF_XCC_FAIL_LAYER_L3, TAF_XCC_CAUSE_POWER_DOWN_IND, TAF_XCC_CALLID_NULL, 0);

    /* 将SO转换成SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    /* 通知APS 取消挂起APS，发送ID_XCC_APS_DATA_CALL_RESUME_IND */
    if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType))
    {
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);
    }

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MO_CALLING_END_REASON_POWER_DOWN_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsEstCnf_MoCalling_WaitAsEstCnf
 功能描述  : XCC处于等待接入层建链回复状态，接收到 ID_CAS_CNAS_1X_EST_CNF
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月6日
    作    者   : c00294324
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsEstCnf_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_EST_CNF_STRU           *pstEstCnf = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstEstCnf   =   (CAS_CNAS_1X_EST_CNF_STRU*)pstMsg;
    pstCallInfo =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*停止保护定时器*/
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);


    if (CAS_CNAS_1X_EST_RSLT_SUCCESS == pstEstCnf->enEstRslt)
    {
        /* 迁入CNAS_XCC_MO_CALLING_STA_WAIT_AS_CALL_INIT状态机 */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_MO_CALLING_STA_WAIT_AS_CALL_INIT);

        /* 开启保护定时器*/
        CNAS_XCC_StartTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND_LEN);
        return VOS_TRUE;
    }

    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                      CNAS_XCC_ConvertEstReasonToTafCause(pstEstCnf->enEstRslt),
                                      pstEstCnf->enFailLayer,
                                      VOS_TRUE,
                                      pstEstCnf->sCdmaRssi);

    /* 通知层1，状态机结果为CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXcallHandUpReq_MoCalling_WaitAsEstCnf
 功能描述  : XCC处于等待接入层建链回复状态，收到XCALL发送的ID_XCALL_XCC_HANGUP_CALL_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月6日
    作    者   : c00294324
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallHangupReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    /* 停止保护计时器 */
    pstCallInfo =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)pstMsg;

    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* 通知AS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 给XCALL模块发送ID_XCC_XCALL_HANGUP_CALL_CNF */
    CNAS_XCC_SndXcallHangUpCallCnf(pstCallInfo->ucCallId);

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitAsEstCnf
 功能描述  : XCC处于等待接入层建链回复状态，接收到ID_CSMS_XCC_END_SMS_CALL_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    CSMS_XCC_END_SMS_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstHangupCallReq = (CSMS_XCC_END_SMS_CALL_REQ_STRU *)pstMsg;
    pstCallInfo      =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* 通知AS REL_REQ*/
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId, pstCallInfo->ucConRef, enRelReason, VOS_FALSE);

    /* 给SMS模块发送ID_XCC_CSMS_END_SMS_CALL_CNF */
    CNAS_XCC_SndCsmsHangupCallCnf(pstCallInfo->ucCallId);

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXpdsEndAgpsCallReq_MoCalling_WaitAsEstCnf
 功能描述  : XCC处于等待接入层建链回复状态，接收到ID_XPDS_XCC_END_AGPS_CALL_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月31日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsEndAgpsCallReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    XPDS_XCC_END_AGPS_CALL_REQ_STRU    *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstHangupCallReq = (XPDS_XCC_END_AGPS_CALL_REQ_STRU *)pstMsg;
    pstCallInfo      =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* 通知AS REL_REQ*/
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId, pstCallInfo->ucConRef, enRelReason, VOS_FALSE);

    /* 给XPDS模块发送ID_XCC_XPDS_END_AGPS_CALL_CNF */
    CNAS_XCC_SndXpdsEndCallCnf(pstCallInfo->ucCallId);

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvApsHangupDataCallReq_MoCalling_WaitAsEstCnf
 功能描述  : XCC处于等待接入层建链回复状态，接收到ID_APS_XCC_HANGUP_DATA_CALL_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsHangupDataCallReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    APS_XCC_HANGUP_DATA_CALL_REQ_STRU  *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstHangupCallReq = (APS_XCC_HANGUP_DATA_CALL_REQ_STRU *)pstMsg;
    pstCallInfo      =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* 通知AS REL_REQ*/
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId, pstCallInfo->ucConRef, enRelReason, VOS_FALSE);

    /* 给APS模块发送ID_XCC_APS_HANGUP_DATA_CALL_CNF */
    CNAS_XCC_SndApsHangupDataCallCnf(pstCallInfo->ucCallId);

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccAbortReq_MoCalling_WaitAsEstCnf
 功能描述  : XCC处于等待接入层建链回复状态，接收到ID_CNAS_XCC_XCC_ABORT_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2014年12月15日
    作    者   : y00245242
    修改内容   : 修改原因值上报

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfo =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* 根据呼叫类型，通知TAF呼叫结束 */
    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo, pstAbortReq->enAbortCause, TAF_XCC_FAIL_LAYER_L3, VOS_FALSE, 0);

    /* 通知AS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId, pstCallInfo->ucConRef, CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE, VOS_FALSE);

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}




/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiWaitAsEstCnfExpired_MoCalling_WaitAsEstCnf
 功能描述  : XCC处于等待接入层建链回复状态，保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitAsEstCnfExpired_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_RcvTiWaitAsEstCnfExpired_MoCalling_WaitAsEstCnf:time out");

    /* 通知AS REL_REQ*/
    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                         TAF_XCC_CAUSE_ACCESS_CNF_TIMEOUT,
                                         TAF_XCC_FAIL_LAYER_L3,
                                         VOS_FALSE,
                                         0);

    /* 通知层1，状态机结果 CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallTerminateInd_MoCalling_WaitAsEstCnf
 功能描述  : XCC处于等待接入层建链回复状态，收到接入层的TERMINATE消息
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : h00246512
    修改内容   : 新生成函数
  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1x项目迭代5修改

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                             *pstCallInfo        =   VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU                     *pstTerminateInd    =   VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32                               enCause;

    pstCallInfo =   CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstTerminateInd =   (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU*)pstMsg;

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* 与AS的liuyin确认:等待建链回复时,AS异常时会上报terminate ind指示MS END,此时NAS需要进行重拨,转换原因值为abort */
    if (CAS_CNAS_1X_TERMINATE_REASON_MS_END == pstTerminateInd->enTerminateReason)
    {
        enCause = TAF_XCC_CAUSE_ABORT;
    }
    else
    {
        /* 不同消息类型的映射 */
        enCause = CNAS_XCC_ConvertTerminateReasonToTafCause(pstTerminateInd->enTerminateReason);
    }

    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                      enCause,
                                      TAF_XCC_FAIL_LAYER_L3,
                                      VOS_TRUE,
                                      pstTerminateInd->sCdmaRssi);

    /* 向层1报告结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    /* 退出层2状态机 */
    CNAS_XCC_QuitFsmL2();
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitAsEstCnf
 功能描述  : XCC处于等待接入层建链回复状态，收到关机指令
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : c00294324
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitAsEstCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        当前关机的时候，链路释放是在main control里面处理的，因此不需要与接入层交互，只需要状态迁移，
        同时TAF对应消息的处理
     */

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_EST_CNF);

    /* 向XCALL发送 ID_XCALL_XCC_ORIG_CALL_CNF (FAIL) */
    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo, TAF_XCC_CAUSE_POWER_DOWN_IND, TAF_XCC_FAIL_LAYER_L3, VOS_FALSE, 0);

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_POWER_DOWN_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallInitInd_MoCalling_WaitAsCallInit
 功能描述  : 接收到AS层INIT_IND消息，迁入CONVERASTION
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月6日
    作    者   : c00294324
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallInitInd_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_INIT_IND_STRU     *pstCallInd  = VOS_NULL_PTR;

    /* bypass，isnull，qos参数记录到全局变量 */
    pstCallInd  =   (CAS_CNAS_1X_CALL_INIT_IND_STRU*)pstMsg;


    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstCallInfo->ucConRef               =   pstCallInd->ucConRef;
    pstCallInfo->ucIsByPassAlertAns     =   (VOS_UINT8)pstCallInd->enBypassAlertAns;
    pstCallInfo->ucQosInfoLen           =   pstCallInd->ucQosInfoLen;
    pstCallInfo->ucIsNullCc             =   pstCallInd->enIsNullCcFlag;


    NAS_MEM_CPY_S(pstCallInfo->aucQosInfo, sizeof(pstCallInfo->aucQosInfo), pstCallInd->aucQosInfo, sizeof(pstCallInd->aucQosInfo));

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* 通知层1，状态机结果为CNAS_XCC_MO_CALLING_RESULT_SUCCESS */
    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo, TAF_XCC_CAUSE_SUCCESS, TAF_XCC_FAIL_LAYER_L3, VOS_FALSE, 0);

    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_SUCCESS,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallTerminateInd_MoCalling_WaitAsCallInit
 功能描述  : 收到 ID_CAS_CNAS_1X_CALL_TERMINATE_IND
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月6日
    作    者   : c00294324
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfo        = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU                    *pstTerminateInd    = VOS_NULL_PTR;

    pstTerminateInd     =   (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU*)pstMsg;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                         CNAS_XCC_ConvertTerminateReasonToTafCause(pstTerminateInd->enTerminateReason),
                                         TAF_XCC_FAIL_LAYER_L3,
                                         VOS_TRUE,
                                         pstTerminateInd->sCdmaRssi);

    /* 通知层1，状态机结果为CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXcallHandUpReq_MoCalling_WaitAsCallInit
 功能描述  : 收到XCALL发送的ID_XCALL_XCC_HANGUP_CALL_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月6日
    作    者   : c00294324
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallHandupReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)pstMsg;

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* 通知AS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 给XCALL模块发送ID_XCC_XCALL_HANGUP_CALL_CNF */
    CNAS_XCC_SndXcallHangUpCallCnf(pstCallInfo->ucCallId);

    /* 通知层1，带退状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitAsCallInit
 功能描述  : XCC处于等待CALL INIT状态，接收到ID_CSMS_XCC_END_SMS_CALL_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvSmsEndCallReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    CSMS_XCC_END_SMS_CALL_REQ_STRU     *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstHangupCallReq = (CSMS_XCC_END_SMS_CALL_REQ_STRU *)pstMsg;
    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* 通知AS REL_REQ*/
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 给SMS模块发送ID_XCC_CSMS_END_SMS_CALL_CNF */
    CNAS_XCC_SndCsmsHangupCallCnf(pstCallInfo->ucCallId);

    /* 通知层1，带退状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvApsHangupDataCallReq_MoCalling_WaitAsCallInit
 功能描述  : XCC处于等待CALL INIT状态，接收到ID_APS_XCC_HANGUP_DATA_CALL_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsHangupDataCallReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    APS_XCC_HANGUP_DATA_CALL_REQ_STRU  *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstHangupCallReq = (APS_XCC_HANGUP_DATA_CALL_REQ_STRU *)pstMsg;
    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* 通知AS REL_REQ*/
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 给APS模块发送ID_XCC_APS_HANGUP_DATA_CALL_CNF */
    CNAS_XCC_SndApsHangupDataCallCnf(pstCallInfo->ucCallId);

    /* 通知层1，带退状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXpdsEndCallReq_MoCalling_WaitAsCallInit
 功能描述  : XCC处于等待CALL INIT状态，接收到ID_XPDS_XCC_END_AGPS_CALL_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsEndCallReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    XPDS_XCC_END_AGPS_CALL_REQ_STRU    *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8   enRelReason;

    pstHangupCallReq = (XPDS_XCC_END_AGPS_CALL_REQ_STRU *)pstMsg;
    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* 通知AS REL_REQ*/
    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 给XPDS模块发送ID_XCC_XPDS_END_AGPS_CALL_CNF */
    CNAS_XCC_SndXpdsEndCallCnf(pstCallInfo->ucCallId);

    /* 通知层1，带退状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccAbortReq_MoCalling_WaitAsCallInit
 功能描述  : XCC处于等待CALL INIT状态，接收到ID_CNAS_XCC_XCC_ABORT_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月11日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2014年12月15日
    作    者   : y00245242
    修改内容   : 修改原因值上报
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo      = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* 根据呼叫类型，通知TAF呼叫结束 */
    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo, pstAbortReq->enAbortCause, TAF_XCC_FAIL_LAYER_L3, VOS_FALSE, 0);

    /* 通知AS REL_REQ*/
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* 通知层1，带退状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiWaitAsCallInitIndExpired_MoCalling_WaitAsCallInit
 功能描述  : XCC处于等待接入层建链回复状态，保护定时器超时
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月9日
    作    者   : h00246512
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitAsCallInitIndExpired_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 通知AS REL_REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo,
                                      TAF_XCC_CAUSE_ACCESS_TCH_TIMEOUT,
                                      TAF_XCC_FAIL_LAYER_L3,
                                      VOS_FALSE,
                                      0);

    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_NORMAL_END);
    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitAsCallInit
 功能描述  : XCC处于等待接入层INIT回复状态，收到关机指令
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : c00294324
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_MoCalling_WaitAsCallInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        当前关机的时候，链路释放是在main control里面处理的，因此不需要与接入层交互，只需要状态迁移，
        同时TAF对应消息的处理
     */

    /* 停止保护计时器 */
    CNAS_XCC_StopTimer(pstCallInfo->ucConnectId, TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND);

    /* 根据不同SO，回复不同ORIG CNF */
    CNAS_XCC_SndOrigCallCnf_MoCalling(pstCallInfo, TAF_XCC_CAUSE_POWER_DOWN_IND, TAF_XCC_FAIL_LAYER_L3, VOS_FALSE, 0);

    /* 通知层1，状态机结果CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SndMoCallingRslt(pstCallInfo->ucConnectId,
                              CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING,
                              CNAS_XCC_MO_CALLING_END_REASON_POWER_DOWN_END);

    CNAS_XCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndOrigCallCnf_MoCalling
 功能描述  : XCC处于收到TERMINATE 或者REL_IND之后向APS或者XCALL发送消息的处理流程
 输入参数  : VOS_UINT32 isNeedToResumeAps 为 VOS_TRUE 时，需要挂起APS

 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月15日
    作    者   : c00294324
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_XCC_SndOrigCallCnf_MoCalling(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    VOS_BOOL                            isNeedToResumeAps,
    VOS_INT16                           sRssi
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32      enServiceType;
    CNAS_XCC_ConvertSoToServiceType((CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16)pstCallInfo->enCurrentSo, &enServiceType);

    switch (enServiceType)
    {
       case CNAS_XCC_SERVICE_TYPE_VOICE_CALL:
            /* 语音业务 */
            if (VOS_TRUE == isNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);
            }
            CNAS_XCC_SndXcallOrigCallCnf(pstCallInfo->ucCallId, enFailLayer, enCause, TAF_XCC_CALLID_NULL, sRssi);
            break;

       case CNAS_XCC_SERVICE_TYPE_SMS:
           if (VOS_TRUE   ==  isNeedToResumeAps)
           {
               CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);
           }

           /* SMS 呼叫业务 */
           CNAS_XCC_SndCsmsOrigCallCnf(pstCallInfo->ucCallId, enFailLayer, enCause);
           break;

       case CNAS_XCC_SERVICE_TYPE_DATA_CALL:
            /* 数据呼叫业务 */
            CNAS_XCC_SndApsOrigDataCallCnf(pstCallInfo->ucCallId, enFailLayer, enCause, pstCallInfo->ucConRef, pstCallInfo->ucConnectId, sRssi);
            break;

       case CNAS_XCC_SERVICE_TYPE_AGPS_CALL:
           if (VOS_TRUE   ==  isNeedToResumeAps)
           {
               CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);
           }

           /* AGPS 呼叫业务 */
           CNAS_XCC_SndXpdsOrigCallCnf(pstCallInfo->ucCallId, enFailLayer, enCause);
            break;

       default:
            CNAS_XCC_SndXcallOrigCallCnf(pstCallInfo->ucCallId, enFailLayer, enCause, TAF_XCC_CALLID_NULL, 0);

            CNAS_WARNING_LOG1(UEPS_PID_XCC,
                          "CNAS_XCC_NotifyTafCallDisc_MoCalling: enServiceType is not found!",
                          enServiceType);
            break;
    }

}




/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





