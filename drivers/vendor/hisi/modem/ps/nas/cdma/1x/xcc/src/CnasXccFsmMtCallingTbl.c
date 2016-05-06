/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccFsmMtCallingTbl.c
  版 本 号   : 初稿
  作    者   : w00242748
  生成日期   : 2014年9月4日
  功能描述   : MT CALLING L2状态机table表
  函数列表   :
  修改历史   :
  1.日    期   : 2014年9月4日
    作    者   : w00242748
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "xsd_xcc_pif.h"
#include "CnasXccFsmMtCalling.h"
#include "CnasXccFsmMtCallingTbl.h"
#include "cas_1x_control_main_nas_pif.h"
#include "cas_1x_trchctrl_proc_nas_pif.h"
#include "xcc_xcall_pif.h"
#include "xcc_aps_pif.h"
#include "CnasXccTimer.h"
#include "CnasXccSndInternalMsg.h"
#include "xcc_sms_pif.h"
#include  "xcc_xpds_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_FSM_MT_CALLING_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* CNAS XCC 主状态机 */
NAS_FSM_DESC_STRU                       g_stCnasXccMtCallingFsmDesc;

/* 本次迭代不涉及 */

/* MT CALLING INIT状态下事件处理表 */
NAS_ACT_STRU g_stCnasXccMtCallingInitActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_PAGING_IND,
                     CNAS_XCC_RcvAsPagingInd_MtCalling_Init),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_IND,
                     CNAS_XCC_RcvAsDschDataInd_MtCalling_Init),
};

/* MT CALLING WAIT APS SUSPEND RSP状态下事件处理表 */
NAS_ACT_STRU g_stCnasXccMtCallingWaitApsSuspendRspActTbl[] =
{
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_DATA_CALL_SUSPEND_RSP,
                     CNAS_XCC_RcvApsDataCallSuspendRsp_MtCalling_WaitApsSuspendRsp),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_ABORT_REQ,
                     CNAS_XCC_RcvXccAbortReq_MtCalling_WaitApsSuspendRsp),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP,
                     CNAS_XCC_RcvTiWaitApsSuspendRspExpired_MtCalling_WaitApsSuspendRsp),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitApsSuspendRsp),
};

/* MT CALLING WAIT AS EST CNF状态下事件处理表 */
NAS_ACT_STRU g_stCnasXccMtCallingWaitAsEstCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_EST_CNF,
                     CNAS_XCC_RcvAsEstCnf_MtCalling_WaitAsEstCnf),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_AS_EST_CNF,
                     CNAS_XCC_RcvTiWaitAsEstCnfExpired_MtCalling_WaitAsEstCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_ABORT_REQ,
                     CNAS_XCC_RcvXccAbortReq_MtCalling_WaitAsEstCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitAsEstCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitAsEstCnf),
};

/* MT CALLING WAIT AS CALL INIT状态下事件处理表 */
NAS_ACT_STRU g_stCnasXccMtCallingWaitAsCallInitActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_INIT_IND,
                     CNAS_XCC_RcvAsCallInitInd_MtCalling_WaitAsCallInitInd),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_ABORT_REQ,
                     CNAS_XCC_RcvXccAbortReq_MtCalling_WaitAsCallInit),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitAsCallInitInd),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND,
                     CNAS_XCC_RcvTiWaitAsCallInitIndExpired_MtCalling_WaitAsCallInit),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitAsCallInit),
};

/* MT CALLING WAIT FOR ORDER状态下事件处理表 */
NAS_ACT_STRU g_stCnasXccMtCallingWaitForOrderActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND,
                     CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForOrder),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_RESET_WFO_SUBSTATE_TIMER_IND,
                     CNAS_XCC_RcvAsResetWfoSubstateTimerInd_MtCalling_WaitForOrder),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_IND,
                     CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForOrder),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_ABORT_REQ,
                     CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForOrder),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForOrder),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_REL_IND,
                     CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForOrder),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_T52M,
                     CNAS_XCC_RcvTiT52MExpired_MtCalling_WaitForOrder),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForOrder),
};

/* MT CALLING WAIT FOR INCOMING RSP状态下事件处理表 */
NAS_ACT_STRU g_stCnasXccMtCallingWaitForIncomingRspActTbl[] =
{
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_INCOMING_CALL_RSP,
                     CNAS_XCC_RcvXcallIncomingCallRsp_MtCalling_WaitForIncomingRsp),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_INCOMING_CALL_RSP,
                     CNAS_XCC_RcvApsIncomingCallRsp_MtCalling_WaitForIncomingRsp),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_INCOMING_CALL_RSP,
                     CNAS_XCC_RcvSmsIncomingCallRsp_MtCalling_WaitForIncomingRsp),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_INCOMING_CALL_RSP,
                     CNAS_XCC_RcvXpdsIncomingCallRsp_MtCalling_WaitForIncomingRsp),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_ABORT_REQ,
                     CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForIncomingRsp),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_REL_IND,
                     CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForIncomingRsp),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForIncomingRsp),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP,
                     CNAS_XCC_RcvTiWaitForXcallIncomingRsp_MtCalling_WaitForIncomingRsp),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForIncomingRsp),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND,
                     CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForIncomingRsp),

};

/* MT CALLING WAIT FOR ANSWER状态下事件处理表 */
NAS_ACT_STRU g_stCnasXccMtCallingWaitForAnswerActTbl[] =
{
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_ANSWER_CALL_REQ,
                     CNAS_XCC_RcvXcallAnsCallReq_MtCalling_WaitForAnswer),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_ANSWER_DATA_CALL_REQ,
                     CNAS_XCC_RcvApsAnswerDataCallReq_MtCalling_WaitForAnswer),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_ANSWER_CALL_REQ,
                     CNAS_XCC_RcvCsmsAnswerCallReq_MtCalling_WaitForAnswer),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_ANSWER_CALL_REQ,
                     CNAS_XCC_RcvXpdsAnswerCallReq_MtCalling_WaitForAnswer),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitForAnswer),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_REL_IND,
                     CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitForAnswer),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_HANGUP_CALL_REQ,
                     CNAS_XCC_RcvXcallHangupCallReq_MtCalling_WaitForAnswer),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_END_SMS_CALL_REQ,
                     CNAS_XCC_RcvSmsEndSmsCallReq_MtCalling_WaitForAnswer),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_END_AGPS_CALL_REQ,
                     CNAS_XCC_RcvXpdsEndAgpsCallReq_MtCalling_WaitForAnswer),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_T53M,
                     CNAS_XCC_RcvTiT53MExpired_MtCalling_WaitForAnswer),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitForAnswer),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_IND,
                     CNAS_XCC_RcvAsDschDataInd_MtCalling_WaitForAnswer),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_ABORT_REQ,
                     CNAS_XCC_RcvXccAbortReq_MtCalling_WaitForAnswer),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND,
                     CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitForAnswer),

};

/* MT CALLING WAIT CONNECT L2 ACK状态下事件处理表 */
NAS_ACT_STRU g_stCnasXccMtCallingWaitConnectL2AckActTbl[] =
{
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_RcvAsCallTerminateInd_MtCalling_WaitConnL2Ack),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                     CNAS_XCC_RcvAsDschDataCnf_MtCalling_WaitConnL2Ack),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_REL_IND,
                     CNAS_XCC_RcvAsCallRelInd_MtCalling_WaitConnL2Ack),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_HANGUP_CALL_REQ,
                     CNAS_XCC_RcvXcallHangupCallReq_MtCalling_WaitConnL2Ack),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_HANGUP_DATA_CALL_REQ,
                     CNAS_XCC_RcvApsHangupDataCallReq_MtCalling_WaitConnL2Ack),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_END_SMS_CALL_REQ,
                     CNAS_XCC_RcvSmsHangupCallReq_MtCalling_WaitConnL2Ack),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_END_AGPS_CALL_REQ,
                     CNAS_XCC_RcvXpdsHangupCallReq_MtCalling_WaitConnL2Ack),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_CONN_L2_ACK,
                     CNAS_XCC_RcvTiWaitL2AckExpired_MtCalling_WaitConnL2Ack),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_ABORT_REQ,
                     CNAS_XCC_RcvXccAbortReq_MtCalling_WaitConnL2Ack),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_RcvXccPowerDownInd_MtCalling_WaitConnL2Ack),

    
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND,
                     CNAS_XCC_RcvAsUpdateCallInfoInd_MtCalling_WaitConnL2Ack),

};


/* XCC MT CALLING L2 状态机状态处理表 */
NAS_STA_STRU g_astCnasXccMtCallingStaTbl[] =
{
    NAS_STA_TBL_ITEM( CNAS_XCC_MT_CALLING_STA_INIT,
                      g_stCnasXccMtCallingInitActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_MT_CALLING_STA_WAIT_APS_SUSPEND_RSP,
                      g_stCnasXccMtCallingWaitApsSuspendRspActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_MT_CALLING_STA_WAIT_AS_EST_CNF,
                      g_stCnasXccMtCallingWaitAsEstCnfActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_MT_CALLING_STA_WAIT_AS_CALL_INIT,
                      g_stCnasXccMtCallingWaitAsCallInitActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ORDER,
                      g_stCnasXccMtCallingWaitForOrderActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER,
                      g_stCnasXccMtCallingWaitForAnswerActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_MT_CALLING_STA_WAIT_CONNECT_L2_ACK,
                      g_stCnasXccMtCallingWaitConnectL2AckActTbl ),

    NAS_STA_TBL_ITEM( CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP,
                      g_stCnasXccMtCallingWaitForIncomingRspActTbl ),

};


/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/


/*****************************************************************************
 函 数 名  : CNAS_XCC_GetMtCallingStaTblSize
 功能描述  : 获取MT CALLING L2状态机状态表大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回MT CALLING L2状态机状态表size
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年09月4日
   作    者   : w00242748
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_GetMtCallingStaTblSize(VOS_VOID)
{
    return (sizeof(g_astCnasXccMtCallingStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_GetMtCallingFsmDescAddr
 功能描述  : 获取MT CALLING状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : NAS_FSM_DESC_STRU:指向MT CALLING状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月4日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
NAS_FSM_DESC_STRU * CNAS_XCC_GetMtCallingFsmDescAddr(VOS_VOID)
{
    return (&g_stCnasXccMtCallingFsmDesc);
}

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




