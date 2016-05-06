/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccMainCtrl.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年09月13日
  功能描述   : 1X CC(call control)主控处理函数
  函数列表   :
  修改历史   :
  1.日    期   : 2014年09月13日
    作    者   : y00245242
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "PsCommonDef.h"
#include  "CnasXccMainCtrl.h"
#include  "CnasXccInstanceMgmt.h"
#include  "NasFsm.h"
#include  "xsd_xcc_pif.h"
#include  "CnasXccSndXsd.h"
#include  "CnasXccSndInternalMsg.h"
#include  "CnasXccComFunc.h"
#include  "CnasXccCtx.h"
#include  "CnasCcb.h"
#include  "CnasXccSndXcall.h"
#include  "CnasXccFsmMainTbl.h"
#include  "CnasXccFsmMoCallingTbl.h"
#include  "CnasXccFsmMtCallingTbl.h"
#include  "CnasXccSndCas.h"
#include  "CnasMntn.h"
#include  "xcc_aps_pif.h"
#include  "xcc_sms_pif.h"
#include  "CnasXccSndAps.h"
#include  "CnasXccSndCsms.h"
#include  "CnasXccSndXcall.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "xcc_mma_pif.h"
#include  "CnasXccSndMma.h"
#include "CnasXccSndXpds.h"
#include  "xcc_xpds_pif.h"
#include "CnasXccProcNvim.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_MAIN_CTRL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/* 目前X模的仓是单独编译的，编译机在编译时不下载TAF仓的代码 */
extern VOS_UINT8   TAF_SDC_GetCsCallExistFlg(VOS_VOID);

/*****************************************************************************
  2 类型定义
*****************************************************************************/
typedef VOS_UINT32 (*CNAS_XCC_MAIN_CTRL_PROC_FUNC)(VOS_UINT32                    ulEventType,
                                                   struct MsgCB                 *pstMsg);

typedef struct
{
    VOS_UINT32                          ulMsgEvtType;
    CNAS_XCC_MAIN_CTRL_PROC_FUNC        pfMainCtrlProcFun;
} CNAS_XCC_MAIN_CTRL_PROC_STRU;

/*****************************************************************************
  3 全局变量定义
*****************************************************************************/
CNAS_XCC_MAIN_CTRL_PROC_STRU g_astCnasXccMainCtrlProcTab[] = {
    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_XSD_XCC_START_REQ,
                     CNAS_XCC_ProcessXsdStartReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_XSD_XCC_POWER_OFF_REQ,
                     CNAS_XCC_ProcessXsdPowerDownReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_ORIG_CALL_REQ,
                     CNAS_XCC_ProcessXcallOrigCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_ORIG_DATA_CALL_REQ,
                     CNAS_XCC_ProcessApsOrigDataCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_ORIG_SMS_CALL_REQ,
                     CNAS_XCC_ProcessSmsOrigCallReq_MainCtrl),
    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_ORIG_AGPS_CALL_REQ,
                     CNAS_XCC_ProcessXpdsOrigCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_HANGUP_CALL_REQ,
                     CNAS_XCC_ProcessXcallHangupCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_HANGUP_DATA_CALL_REQ,
                     CNAS_XCC_ProcessApsHangupDataCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_END_SMS_CALL_REQ,
                     CNAS_XCC_ProcessSmsHangupCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_END_AGPS_CALL_REQ,
                     CNAS_XCC_ProcessXpdsHangupCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_ANSWER_CALL_REQ,
                     CNAS_XCC_ProcessXcallAnswerCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_ANSWER_DATA_CALL_REQ,
                     CNAS_XCC_ProcessApsAnswerDataCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_ANSWER_CALL_REQ,
                     CNAS_XCC_ProcessSmsAnswerCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_ANSWER_CALL_REQ,
                     CNAS_XCC_ProcessXpdsAnswerCallReq_MainCtrl),
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_PAGING_IND,
                     CNAS_XCC_ProcessCas1xPagingInd_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_IND,
                     CNAS_XCC_ProcessCas1xDschDataInd_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_POWEROFF_REL_ORDER_SND_NTF,
                     CNAS_XCC_ProcessCas1xReleaseOrderInd_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_SEND_FLASH_REQ,
                     CNAS_XCC_ProcessXcallSendFlashReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                     CNAS_XCC_ProcessCas1xDschDataCnf_MainCtrl),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK,
                     CNAS_XCC_RcvTiProtectFlashCnfL2Ack_MainCtrl),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK,
                     CNAS_XCC_RcvTiProtectBurstDTMFCnfL2Ack_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_SEND_BURST_DTMF_REQ,
                     CNAS_XCC_ProcessXcallSendBurstDTMFReq_MainCtrl),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK,
                     CNAS_XCC_RcvTiWaitEmergencyCallFlashCnfL2Ack_MainCtrl),


    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_ProcessCas1xCallTerminateInd_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_REL_IND,
                     CNAS_XCC_ProcessCas1xCallRelInd_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_ProcessXccPowerDownInd_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CSCH_DATA_IND,
                     CNAS_XCC_ProcessCas1xCschDataInd_MainCtrl),


    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_NDSS_RECORD_DAILED_DIGITS_IND,
                     CNAS_XCC_ProcessCas1xNdssRecordDialedDigitsInd_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_XSD_XCC_NDSS_RESULT_IND,
                     CNAS_XCC_ProcessXsdNdssResultInd_MainCtrl),


    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_PZID_INFO_NTF,
                     CNAS_XCC_ProcessApsPzidInfoNtf_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_CALL_STATE_IND,
                     CNAS_XCC_ProcessXCallStateInd_MainCtrl),

#if 0
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_RESERVE_SR_ID_NTF,
                     CNAS_XCC_ProcessReserveSrIdNtf_MainCtrl),
#endif

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_SEND_CONT_DTMF_REQ,
                     CNAS_XCC_ProcessXcallSendContDTMFReq_MainCtrl),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK,
                     CNAS_XCC_RcvTiProtectContDTMFCnfL2Ack_MainCtrl),

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_ECC_SERVICE_REQ,
                     CNAS_XCC_ProcessXcallEccServiceReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_ECC_SERVICE_CNF,
                     CNAS_XCC_ProcessCas1xEccServiceCnf_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_TCH_ASSIGN_CMPL_IND,
                     CNAS_XCC_ProcessCas1xTchAssignCmplInd_MainCtrl),
#endif

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_PRIVACY_MODE_SET_REQ,
                     CNAS_XCC_ProcessXcallPrivacyModeSetReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_PRIVACY_MODE_QRY_REQ,
                     CNAS_XCC_ProcessXcallPrivacyModeQryReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_LONG_CODE_TRANSITION_IND,
                     CNAS_XCC_ProcessXcallLongCodeTransitionInd_MainCtrl),
};

/*****************************************************************************
  4 函数定义
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 函 数 名  : CNAS_XCC_IsSending1xCallRelReqAllowed
 功能描述  : check当前call instance实体当前状态机ID及状态, 确认是否需要发送
             1X call release请求
 输入参数  : pstFsmCtx -- FSM上下文
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 允许发送
             VOS_FALSE -- 不允许发送

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月13日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XCC_IsSending1xCallRelReqAllowed(
    CNAS_XCC_FSM_CTX_STRU               *pstFsmCtx
)
{
    VOS_UINT8                           ulRslt;

    ulRslt = VOS_TRUE;

    switch (pstFsmCtx->enFsmId)
    {
        case CNAS_XCC_FSM_L1_MAIN:
            if (CNAS_XCC_L1_STA_ENDING == pstFsmCtx->ulState)
            {
                /* 在ending状态，不需要发送release request */
                ulRslt = VOS_FALSE;
            }
            break;

        case CNAS_XCC_FSM_MO_CALLING:
            if (CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP == pstFsmCtx->ulState)
            {
                /* 此时链路未建立，不需要发送release request */
                ulRslt = VOS_FALSE;
            }
            break;

        case CNAS_XCC_FSM_MT_CALLING:
            if (CNAS_XCC_MT_CALLING_STA_WAIT_APS_SUSPEND_RSP == pstFsmCtx->ulState)
            {
                /* 此时链路未建立，不需要发送release request */
                ulRslt = VOS_FALSE;
            }
            break;

        default:
            ulRslt = VOS_FALSE;
            break;
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ReturnPaginMsgActionType
 功能描述  : 检查寻呼消息是否允许处理
 输入参数  : pstFsmCtx -- FSM上下文
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 允许发送
             VOS_FALSE -- 不允许发送

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月13日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XCC_IsPaginMsgAllowed(
    CAS_CNAS_1X_PAGING_IND_STRU        *pstMsg,
    VOS_UINT8                          *pucAbortIndex,
    VOS_UINT8                          *pucAbortFlag
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                       enServiceType;

    /* 支持并发的话，指示不需要打断，允许发送 */
    *pucAbortFlag  = VOS_FALSE;
    *pucAbortIndex = 0;

    CNAS_XCC_ConvertSoToServiceType(pstMsg->enSo, &enServiceType);

    /* paging消息，根据SO, 检查是否有同类型的呼叫在发起，如果存在，忽略paging */
    if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(enServiceType, pucAbortIndex))
    {

        return VOS_FALSE;
    }

    if (VOS_FALSE == CNAS_XCC_IsConcurrentSupported())
    {
        return CNAS_XCC_ProcessPagingCollision(enServiceType, pucAbortIndex, pucAbortFlag);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_IsXcallOrigCallReqAllowed
 功能描述  : 检查呼叫请求消息是否允许，如果允许，通过pucAbortFlag返回是否终止
             当前其他呼叫，还是无需终止其他呼叫
 输入参数  : pstMsg -- XCALL ORIG CALL REQ消息地址
 输出参数  : pucAbortIndex -- 返回终止其他呼叫call instance索引
             pucAbortFlag  -- 返回是否需要终止其他呼叫

 返 回 值  : VOS_TRUE  -- 允许发送
             VOS_FALSE -- 不允许发送

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月13日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1x项目迭代5修改
*****************************************************************************/
TAF_XCC_CAUSE_ENUM_UINT32 CNAS_XCC_IsXcallOrigCallReqAllowed(
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstMsg,
    VOS_UINT8                          *pucAbortIndex,
    VOS_UINT8                          *pucAbortFlag
)
{
    /* 支持并发的话，指示不需要打断，允许发送 */
    *pucAbortFlag  = VOS_FALSE;
    *pucAbortIndex = 0;

    if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, pucAbortIndex))
    {
        if (VOS_FALSE == pstMsg->ucIsEmergencyCall)
        {
            return TAF_XCC_CAUSE_ABORT;
        }

        /* if mt voice call instance exist (mo vocice call exist,uplayer will reject the emergency call request af first),
           check if we could send a emc flash message or not.
           if not, send orig cnf fail with one special cause so that the uplayer could retry this call
        */
        if (VOS_FALSE == CNAS_XCC_IsSendingEmcFlashMsgAllowed_MainCtrl(*pucAbortIndex))
        {
            return TAF_XCC_CAUSE_EMERGENCY_CALL_ABORT;
        }

        return TAF_XCC_CAUSE_SUCCESS;
    }

    if (VOS_FALSE == CNAS_XCC_IsConcurrentSupported())
    {
        /* 当前的设计认为，在环回测试的时候，不能触发语音 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_LOOPBACK, pucAbortIndex))
        {
            return TAF_XCC_CAUSE_CALL_NOT_ALLOWED;
        }

        /* 存在数据呼过程中，收到主叫语音呼，打断 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, pucAbortIndex))
        {
            *pucAbortFlag = VOS_TRUE;

            return TAF_XCC_CAUSE_SUCCESS;
        }

        /* 存在SMS呼过程中，收到主叫语音呼，打断 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, pucAbortIndex))
        {
            *pucAbortFlag = VOS_TRUE;

            return TAF_XCC_CAUSE_SUCCESS;
        }

        /* 在AGPS呼过程中，收到主叫语音呼，打断 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, pucAbortIndex))
        {
            *pucAbortFlag = VOS_TRUE;

            return TAF_XCC_CAUSE_SUCCESS;
        }
    }

    return TAF_XCC_CAUSE_SUCCESS;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_IsApsOrigDataCallReqAllowed
 功能描述  : 检查数据呼叫请求消息是否允许，如果允许，通过pucAbortFlag返回是否终止
             当前其他呼叫，还是无需终止其他呼叫
 输入参数  : pstMsg -- XCALL ORIG CALL REQ消息地址
 输出参数  : pucAbortIndex -- 返回终止其他呼叫call instance索引
             pucAbortFlag  -- 返回是否需要终止其他呼叫

 返 回 值  : TAF_XCC_CAUSE_SUCCESS   -- 允许发送
             非TAF_XCC_CAUSE_SUCCESS -- 不允许发送
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
TAF_XCC_CAUSE_ENUM_UINT32 CNAS_XCC_IsApsOrigDataCallReqAllowed(VOS_VOID)
{
    VOS_UINT8                           ucIndex;

    if (CNAS_CCB_GetPRevInUse() < P_REV_IN_USE_6)
    {
        return TAF_XCC_CAUSE_PROTOTAL_REV_NOT_SUPPORT;
    }

    /* 同种类型呼叫冲突处理，主叫/被叫冲突 */
    if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, &ucIndex))
    {
        /* 优先被叫，由该函数调用者回复结果 */
        return TAF_XCC_CAUSE_ABORT;
    }

    if (VOS_FALSE == CNAS_XCC_IsConcurrentSupported())
    {
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_LOOPBACK, &ucIndex))
        {
            return TAF_XCC_CAUSE_CALL_NOT_ALLOWED;
        }

        /* 语音被叫过程中，收到主叫数据呼，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
        {
            return TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }

        /* 短信被叫过程中，收到主叫数据呼，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, &ucIndex))
        {
            return TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }

        /* 在AGPS呼过程中，收到主叫语音呼，打断 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, &ucIndex))
        {
            return TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }
    }

    return TAF_XCC_CAUSE_SUCCESS;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_IsCsmsOrigCallReqAllowed
 功能描述  : 检查短信呼叫请求消息是否允许，如果允许，通过pucAbortFlag返回是否终止
             当前其他呼叫，还是无需终止其他呼叫
 输入参数  : pstMsg -- XCALL ORIG CALL REQ消息地址
 输出参数  : pucAbortIndex -- 返回终止其他呼叫call instance索引
             pucAbortFlag  -- 返回是否需要终止其他呼叫

 返 回 值  : TAF_XCC_CAUSE_SUCCESS   -- 允许发送
             非TAF_XCC_CAUSE_SUCCESS -- 不允许发送

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
TAF_XCC_CAUSE_ENUM_UINT32 CNAS_XCC_IsCsmsOrigCallReqAllowed(
    CSMS_XCC_ORIG_SMS_CALL_REQ_STRU    *pstOrigDataCallReq,
    VOS_UINT8                          *pucAbortIndex,
    VOS_UINT8                          *pucAbortFlag
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtx = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;

    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    /* 支持并发的话，指示不需要打断，允许发送 */
    *pucAbortFlag  = VOS_FALSE;
    *pucAbortIndex = 0;

    pstXccCtx = CNAS_XCC_GetCtxAddr();
    enCause   = TAF_XCC_CAUSE_SUCCESS;

    /* 同种类型呼叫冲突处理 */
    if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, pucAbortIndex))
    {
        /* 优先被叫，由该函数调用者回复结果 */
        enCause = TAF_XCC_CAUSE_ABORT;
    }

    if (VOS_FALSE == CNAS_XCC_IsConcurrentSupported())
    {
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_LOOPBACK, pucAbortIndex))
        {
            return TAF_XCC_CAUSE_CALL_NOT_ALLOWED;
        }

        /* 语音被叫过程中，收到主叫短信，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, pucAbortIndex))
        {
            enCause = TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }

        /* 数据业务被叫过程中，收到主叫短信，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, pucAbortIndex))
        {
            enCause = TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }

        /* 在AGPS呼过程中，收到主叫语音呼，打断 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, pucAbortIndex))
        {
            enCause = TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }
    }

    /*如果当前SO已经协商完成，更新原因值 */
    if (TAF_XCC_CAUSE_SUCCESS != enCause)
    {
        if (VOS_TRUE == pstXccCtx->astFsmEntity[*pucAbortIndex].stCallInfoCtx.ucIsSoNegCmplt)
        {
            CNAS_XCC_ConvertSoToServiceType(pstXccCtx->astFsmEntity[*pucAbortIndex].stCallInfoCtx.enCurrentSo, &enServiceType);

            if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
            {
                enCause = TAF_XCC_CAUSE_MT_SMS_IN_TCH;
            }
            else
            {
                enCause = TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH;
            }
        }
    }

    return enCause;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_IsXpdsOrigCallReqAllowed
 功能描述  : 检查AGPS呼叫请求消息是否允许，如果允许，通过pucAbortFlag返回是否终止
             当前其他呼叫，还是无需终止其他呼叫
 输入参数  : pstMsg -- XPDS_XCC_ORIG_AGPS_CALL_REQ消息地址
 输出参数  : pucAbortIndex -- 返回终止其他呼叫call instance索引
             pucAbortFlag  -- 返回是否需要终止其他呼叫

 返 回 值  : TAF_XCC_CAUSE_SUCCESS   -- 允许发送
             非TAF_XCC_CAUSE_SUCCESS -- 不允许发送

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月02日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
TAF_XCC_CAUSE_ENUM_UINT32 CNAS_XCC_IsXpdsOrigCallReqAllowed(
    XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU   *pstOrigDataCallReq,
    VOS_UINT8                          *pucAbortIndex,
    VOS_UINT8                          *pucAbortFlag
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtx = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;

    /* 支持并发的话，指示不需要打断，允许发送 */
    *pucAbortFlag  = VOS_FALSE;
    *pucAbortIndex = 0;

    pstXccCtx = CNAS_XCC_GetCtxAddr();
    enCause   = TAF_XCC_CAUSE_SUCCESS;

    /* 同种类型呼叫冲突处理 */
    if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, pucAbortIndex))
    {
        /* 优先被叫，由该函数调用者回复结果 */
        enCause = TAF_XCC_CAUSE_ABORT;
    }

    if (VOS_FALSE == CNAS_XCC_IsConcurrentSupported())
    {
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_LOOPBACK, pucAbortIndex))
        {
            return TAF_XCC_CAUSE_CALL_NOT_ALLOWED;
        }

        /* 语音被叫过程中，收到AGPS主叫，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, pucAbortIndex))
        {
            enCause = TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }

        /* 数据业务被叫过程中，收到AGPS主叫，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, pucAbortIndex))
        {
            enCause = TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }

        /* 在短信呼过程中，收到AGPS主叫，打断 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, pucAbortIndex))
        {
            enCause = TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }
    }

    if (TAF_XCC_CAUSE_SUCCESS != enCause)
    {
        if (VOS_TRUE == pstXccCtx->astFsmEntity[*pucAbortIndex].stCallInfoCtx.ucIsSoNegCmplt)
        {
            enCause = TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH;
        }
    }

    return enCause;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_IsPrivacyModeAllowedToSend_MainCtrl
 功能描述  : 是否允许发送privacy mode给CAS

 输入参数  : enPrivacyMode -- 用户设置privacy mode

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 允许发送
             VOS_FALSE -- 不允许发送

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_IsPrivacyModeAllowedToSend_MainCtrl(
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8                       enPrivacyMode
)
{
    CNAS_XCC_CTX_STRU                                      *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;

    /* 检查当前是否有激活语音呼叫 */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_FALSE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* 如果当前状态机不在L1 MAIN状态或不在conversation状态，不要发送privacy mode */
    if ((CNAS_XCC_FSM_L1_MAIN         != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
     || (CNAS_XCC_L1_STA_CONVERSATION != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        return VOS_FALSE;
    }

    /* 根据CAS约定，只有在SO协商完成后，才可发送 */
    if (VOS_FALSE == pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSoNegCmplt)
    {
        return VOS_FALSE;
    }

    /* 如果当前的用户请求的privacy mode等于协商后的privacy mode, 不需要发送 */
    if (enPrivacyMode == pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.enNegPrivacyMode)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq
 功能描述  : 在Send Flash Req流程中等待L2 ACK状态下，处理电话挂断(主动挂断或网络挂断)
 输入参数  : ucIndex
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : L00256032
    修改内容   : 1X SS Project修改

*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait)
    {
        return;
    }

    /* 清除等待ACK的标记 */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait = VOS_FALSE;

    /* 停止TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK);

    CNAS_XCC_SndXcallSendFlashCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                  TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq
 功能描述  : 在Send Burst DTMF流程中等待L2 ACK状态下，处理电话挂断(主动挂断或网络挂断)
 输入参数  : ucIndex
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月12日
    作    者   : L00256032
    修改内容   : 1X SS Project修改

*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait)
    {
        return;
    }

    /* 清除等待ACK的标记 */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait = VOS_FALSE;

    /* 停止TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK);

    CNAS_XCC_SndXcallSendBurstDTMFCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                      TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE);

    return;
}



/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcBufferedMsgWithPowerDown
 功能描述  : 清除缓存的用户请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月13日
    作    者   : y00245242
    修改内容   : 新生成函数
   2.日    期   : 2015年9月8日
     作    者   : w00176964
     修改内容   : CNAS内存裁剪调整
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcBufferedMsgUponPowerDown(VOS_VOID)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstXcallOrigReq = VOS_NULL_PTR;
    APS_XCC_ORIG_DATA_CALL_REQ_STRU    *pstApsOrigReq   = VOS_NULL_PTR;
    CSMS_XCC_ORIG_SMS_CALL_REQ_STRU    *pstCsmsOrigReq  = VOS_NULL_PTR;
    XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU   *pstXpdsOrigReq  = VOS_NULL_PTR;
    VOS_UINT8                           i;
    VOS_UINT8                           ucMsgNum;

    ucMsgNum = CNAS_XCC_GetBufferedMsgNum();

    for (i = 0; i < CNAS_MIN(ucMsgNum, CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM); i++)
    {
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
        pstBufferMsgHdr         = (MSG_HEADER_STRU *)CNAS_XCC_GetSpecifiedIndexBufferMsg(i);

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_XCALL_XCC_ORIG_CALL_REQ) == ulBufferMsgEventType)
        {
            pstXcallOrigReq = (XCALL_XCC_ORIG_CALL_REQ_STRU *)pstBufferMsgHdr;
            CNAS_XCC_SndXcallOrigCallCnf(pstXcallOrigReq->ucCallId,
                                         TAF_XCC_FAIL_LAYER_L3,
                                         TAF_XCC_CAUSE_POWER_DOWN_IND,
                                         TAF_XCC_CALLID_NULL,
                                         0);
        }

        /* 该缓存依赖于XCC冲突机制，到时修改 */
        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_XCC_ORIG_DATA_CALL_REQ) == ulBufferMsgEventType)
        {
            pstApsOrigReq = (APS_XCC_ORIG_DATA_CALL_REQ_STRU *)pstBufferMsgHdr;

            CNAS_XCC_SndApsOrigDataCallCnf(pstApsOrigReq->ucCallId,
                                           TAF_XCC_FAIL_LAYER_L3,
                                           TAF_XCC_CAUSE_POWER_DOWN_IND,
                                           CNAS_XCC_INVALID_CON_REF,
                                           CNAS_XCC_INVAILD_CON_ID,
                                           0);
        }

        if (CNAS_BuildEventType(UEPS_PID_XSMS, ID_CSMS_XCC_ORIG_SMS_CALL_REQ) == ulBufferMsgEventType)
        {
            pstCsmsOrigReq = (CSMS_XCC_ORIG_SMS_CALL_REQ_STRU *)pstBufferMsgHdr;

            CNAS_XCC_SndCsmsOrigCallCnf(pstCsmsOrigReq->ucCallId,
                                        TAF_XCC_FAIL_LAYER_L3,
                                        TAF_XCC_CAUSE_POWER_DOWN_IND);
        }
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */

        if (CNAS_BuildEventType(UEPS_PID_XPDS, ID_XPDS_XCC_ORIG_AGPS_CALL_REQ) == ulBufferMsgEventType)
        {
            pstXpdsOrigReq = (XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU *)pstBufferMsgHdr;

            CNAS_XCC_SndXpdsOrigCallCnf(pstXpdsOrigReq->ucCallId,
                                        TAF_XCC_FAIL_LAYER_L3,
                                        TAF_XCC_CAUSE_POWER_DOWN_IND);
        }
    }

    /* 清除所有缓存 */
    CNAS_XCC_FreeAllBufferMsgInQueue();
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXsdStartReq_MainCtrl
 功能描述  : 处理Xsd start req
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月13日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXsdStartReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_InitCtx(CNAS_XCC_INIT_TYPE_POWER_ON);

    /* 开机请求不需要进call control instance各状态机，直接返回开机成功 */
    CNAS_XCC_SndXsdStartCnf(XCC_XSD_START_RESULT_SUCC);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXsdPowerDownReq_MainCtrl
 功能描述  : 处理power down request
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月06日
    作    者   : y00245242
    修改内容   : 新生成函数

  2.日    期   : 2015年1月8日
    作    者   : y00245242
    修改内容   : 增加NDSS ORIG功能
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXsdPowerDownReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INSTANCE_LIST_STRU    stCallInstanceList;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucRelReqFlag;
    XSD_XCC_POWER_OFF_REQ_STRU         *pstPowerOffReq = VOS_NULL_PTR;

    NAS_MEM_SET_S(&stCallInstanceList, sizeof(CNAS_XCC_CALL_INSTANCE_LIST_STRU), 0, sizeof(CNAS_XCC_CALL_INSTANCE_LIST_STRU));

    CNAS_XCC_GetAllActiveCallInstanceIndex(&stCallInstanceList);

    pstXccCtxAddr       = CNAS_XCC_GetCtxAddr();

    ucRelReqFlag        = VOS_FALSE;

    pstPowerOffReq = (XSD_XCC_POWER_OFF_REQ_STRU*)pstMsg;

    if (0 == stCallInstanceList.ucInstanceNum)
    {
        /* 如果无call control instance激活，回复关机确认 */
        CNAS_XCC_SndXsdPowerOffCnf(XCC_XSD_POWER_OFF_RESULT_SUCC);

        /* 初始化XCC上下文 */
        if (XCC_XSD_POWER_OFF_REASON_POWER_OFF == pstPowerOffReq->enPowerOffReason)
        {
            CNAS_XCC_InitCtx(CNAS_XCC_INIT_TYPE_POWER_DOWN);
        }
        else
        {
            CNAS_XCC_InitCtx(CNAS_XCC_INIT_TYPE_POWER_SAVE);
        }

        return VOS_TRUE;
    }

    /* 如果有激活call instance，转换成内部关机事件，存放消息进内部队列中 */
    for (i = 0; i < CNAS_MIN(stCallInstanceList.ucInstanceNum, CNAS_XCC_MAX_FSM_ENTITY_NUM); i++)
    {
        ucIndex = stCallInstanceList.aucInstance[i];

        CNAS_XCC_SndXccPowerDownInd(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId);

        if (VOS_FALSE == ucRelReqFlag)
        {
            ucRelReqFlag =
                CNAS_XCC_IsSending1xCallRelReqAllowed(&(pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm));
        }

    }

    if (VOS_TRUE == ucRelReqFlag)
    {
        if (XCC_XSD_POWER_OFF_REASON_POWER_OFF == pstPowerOffReq->enPowerOffReason)
        {
            /* 发送释放请求 */
            CNAS_XCC_SndCasCallRelReq(CNAS_XCC_INVAILD_CON_ID,
                                      CNAS_XCC_INVALID_CON_REF,
                                      CAS_CNAS_1X_REL_REASON_POWER_DOWN_RELEASE,
                                      VOS_TRUE);
        }
        else
        {
            /* 发送释放请求 */
            CNAS_XCC_SndCasCallRelReq(CNAS_XCC_INVAILD_CON_ID,
                                      CNAS_XCC_INVALID_CON_REF,
                                      CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                                      VOS_TRUE);
        }
    }

    /* 清除可能缓存的所有用户请求消息 */
    CNAS_XCC_ProcBufferedMsgUponPowerDown();

    /* 缓存关机请求消息 */
    CNAS_XCC_BufferMsgInQueue(ulEventType, pstMsg);

    CNAS_XCC_ClearAllOrigCallOrderIndex();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXcallOrigCallReq_MainCtrl
 功能描述  : 处理ID_XCALL_XCC_ORIG_CALL_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月06日
    作    者   : y00245242
    修改内容   : 新生成函数

  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1X项目迭代5修改
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallOrigCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucAbortIndex;
    VOS_UINT8                           ucAbortFlag;
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstXcallOrigReq = VOS_NULL_PTR;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;

    pstXcallOrigReq = (XCALL_XCC_ORIG_CALL_REQ_STRU *)pstMsg;

    if (VOS_FALSE == CNAS_CCB_Get1XRfAvailFlg())
    {
        /* NO RF时，拒绝呼叫请求 */
        /* NO RF状态，XSD正在搜网时收到业务请求下发SessionBegin消息会导致X模内部抢资源的情况，
           这里在NO RF状态直接回复XCALL,让XCALL发起重播，保证当前驻留在网上后再处理呼叫业务 */
        CNAS_XCC_SndXcallOrigCallCnf(pstXcallOrigReq->ucCallId,
                                     TAF_XCC_FAIL_LAYER_L3,
                                     TAF_XCC_CAUSE_NO_RF,
                                     TAF_XCC_CALLID_NULL,
                                     0);

        return VOS_TRUE;
    }

    /* check是否有关机缓存 */
    if (VOS_TRUE == CNAS_XCC_IsBufferedPowerDownMsgExist_MainCtrl())
    {
        /* 如果有关机消息缓存，拒绝呼叫请求 */
        CNAS_XCC_SndXcallOrigCallCnf(pstXcallOrigReq->ucCallId,
                                     TAF_XCC_FAIL_LAYER_L3,
                                     TAF_XCC_CAUSE_POWER_DOWN_IND,
                                     TAF_XCC_CALLID_NULL,
                                     0);

        return VOS_TRUE;
    }

    ucAbortIndex = 0;
    ucAbortFlag  = VOS_FALSE;
    enCause = CNAS_XCC_IsXcallOrigCallReqAllowed(pstXcallOrigReq, &ucAbortIndex, &ucAbortFlag);
    if(TAF_XCC_CAUSE_SUCCESS != enCause)
    {
        /* 拒绝呼叫请求 */
        CNAS_XCC_SndXcallOrigCallCnf(pstXcallOrigReq->ucCallId,
                                     TAF_XCC_FAIL_LAYER_L3,
                                     enCause,
                                     TAF_XCC_CALLID_NULL,
                                     0);

        return VOS_TRUE;
    }

    if (VOS_TRUE == ucAbortFlag)
    {
        pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

        /* 如果需要终止其他呼叫类型，转呼叫事件为abort事件，并存放到内部队列中 */
        CNAS_XCC_SndXccAbortReq(pstXccCtxAddr->astFsmEntity[ucAbortIndex].stCallInfoCtx.ucConnectId,
                                ulEventType,
                                TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MO_CALL);

        /* 缓存用户请求消息 */
        CNAS_XCC_BufferMsgInQueue(ulEventType, pstMsg);

        return VOS_TRUE;
    }

    /* for emergency call,we should process in advance according the state machine state  */
    if (VOS_TRUE == pstXcallOrigReq->ucIsEmergencyCall)
    {
        if (VOS_TRUE == CNAS_XCC_ProcessXcallEmergencyCallReq_MainCtrl(ulEventType, pstMsg))
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXcallOrigCallReq_MainCtrl
 功能描述  : 处理ID_APS_XCC_ORIG_DATA_CALL_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessApsOrigDataCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_XCC_ORIG_DATA_CALL_REQ_STRU                        *pstDataCallReq = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32                               enCause;

    pstDataCallReq = (APS_XCC_ORIG_DATA_CALL_REQ_STRU *)pstMsg;

    /* check是否有关机缓存 */
    if (VOS_TRUE == CNAS_XCC_IsBufferedPowerDownMsgExist_MainCtrl())
    {
        /* 如果有关机消息缓存，通知APS呼叫失败 */
        CNAS_XCC_SndApsOrigDataCallCnf(pstDataCallReq->ucCallId,
                                       TAF_XCC_FAIL_LAYER_L3,
                                       TAF_XCC_CAUSE_POWER_DOWN_IND,
                                       CNAS_XCC_INVALID_CON_REF,
                                       CNAS_XCC_INVAILD_CON_ID,
                                       0);

        return VOS_TRUE;
    }



    enCause = CNAS_XCC_IsApsOrigDataCallReqAllowed();

    if(TAF_XCC_CAUSE_SUCCESS != enCause)
    {
        /* 通知APS呼叫失败 */
        CNAS_XCC_SndApsOrigDataCallCnf(pstDataCallReq->ucCallId, TAF_XCC_FAIL_LAYER_L3, enCause, CNAS_XCC_INVALID_CON_REF, CNAS_XCC_INVAILD_CON_ID, 0);

        return VOS_TRUE;
    }

#if 0
    if (VOS_TRUE == ucAbortFlg)
    {
        pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

        /* 如果需要终止其他呼叫类型，转呼叫事件为abort事件，并存放到内部队列中 */
        CNAS_XCC_SndXccAbortReq(pstXccCtxAddr->astFsmEntity[ucAbortIndex].stCallInfoCtx.ucConnectId, ulEventType);

        /* 缓存用户请求消息 */
        CNAS_XCC_BufferMsgInQueue(ulEventType, pstMsg);

        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessSmsOrigCallReq_MainCtrl
 功能描述  : 处理ID_CSMS_XCC_ORIG_SMS_CALL_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessSmsOrigCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CSMS_XCC_ORIG_SMS_CALL_REQ_STRU                        *pstOrigCallReq = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32                               enCause;
    VOS_UINT8                                               ucAbortIndex;
    VOS_UINT8                                               ucAbortFlag;

    pstOrigCallReq = (CSMS_XCC_ORIG_SMS_CALL_REQ_STRU *)pstMsg;

    /* check是否有关机缓存 */
    if (VOS_TRUE == CNAS_XCC_IsBufferedPowerDownMsgExist_MainCtrl())
    {
        /* 如果有关机消息缓存，通知SMS呼叫失败 */
        CNAS_XCC_SndCsmsOrigCallCnf(pstOrigCallReq->ucCallId,
                                    TAF_XCC_FAIL_LAYER_L3,
                                    TAF_XCC_CAUSE_POWER_DOWN_IND);

        return VOS_TRUE;
    }

    ucAbortIndex = 0;
    ucAbortFlag  = 0;

    enCause = CNAS_XCC_IsCsmsOrigCallReqAllowed(pstOrigCallReq, &ucAbortIndex, &ucAbortFlag);

    if (TAF_XCC_CAUSE_SUCCESS != enCause)
    {
        /* 通知SMS呼叫失败 */
        CNAS_XCC_SndCsmsOrigCallCnf(pstOrigCallReq->ucCallId, TAF_XCC_FAIL_LAYER_L3, enCause);

        return VOS_TRUE;
    }

#if 0
    if (VOS_TRUE == ucAbortFlag)
    {
        pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

        /* 如果需要终止其他呼叫类型，转呼叫事件为abort事件，并存放到内部队列中 */
        CNAS_XCC_SndXccAbortReq(pstXccCtxAddr->astFsmEntity[ucAbortIndex].stCallInfoCtx.ucConnectId, ulEventType);

        /* 缓存用户请求消息 */
        CNAS_XCC_BufferMsgInQueue(ulEventType, pstMsg);

        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXpdsOrigCallReq_MainCtrl
 功能描述  : 处理ID_XPDS_XCC_ORIG_AGPS_CALL_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月31日
    作    者   : y00314741
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXpdsOrigCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU   *pstOrigCallReq = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;
    VOS_UINT8                           ucAbortIndex;
    VOS_UINT8                           ucAbortFlag;


    pstOrigCallReq = (XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU *)pstMsg;

    /* check是否有关机缓存 */
    if (VOS_TRUE == CNAS_XCC_IsBufferedPowerDownMsgExist_MainCtrl())
    {
        /* 如果有关机消息缓存，通知XPDS呼叫失败 */
        CNAS_XCC_SndXpdsOrigCallCnf(pstOrigCallReq->ucCallId,
                                    TAF_XCC_FAIL_LAYER_L3,
                                    TAF_XCC_CAUSE_POWER_DOWN_IND);

        return VOS_TRUE;
    }

    ucAbortIndex = 0;
    ucAbortFlag  = 0;

    enCause = CNAS_XCC_IsXpdsOrigCallReqAllowed(pstOrigCallReq, &ucAbortIndex, &ucAbortFlag);

    if (TAF_XCC_CAUSE_SUCCESS != enCause)
    {
        /* 通知XPDS呼叫失败 */
        CNAS_XCC_SndXpdsOrigCallCnf(pstOrigCallReq->ucCallId, TAF_XCC_FAIL_LAYER_L3, enCause);

        return VOS_TRUE;
    }

#if 0
    if (VOS_TRUE == ucAbortFlag)
    {
        pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

        /* 如果需要终止其他呼叫类型，转呼叫事件为abort事件，并存放到内部队列中 */
        CNAS_XCC_SndXccAbortReq(pstXccCtxAddr->astFsmEntity[ucAbortIndex].stCallInfoCtx.ucConnectId, ulEventType);

        /* 缓存用户请求消息 */
        CNAS_XCC_BufferMsgInQueue(ulEventType, pstMsg);

        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}




/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXcallAnswerCallReq_MainCtrl
 功能描述  : 处理ID_XCALL_XCC_ANSWER_CALL_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月06日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallAnswerCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCALL_XCC_ANSWER_CALL_REQ_STRU     *pstXcallAnswerReq = VOS_NULL_PTR;

    if (VOS_FALSE == CNAS_XCC_IsVoiceCallInstanceActive())
    {
        pstXcallAnswerReq = (XCALL_XCC_ANSWER_CALL_REQ_STRU *)pstMsg;

        /* 回复接听失败 */
        CNAS_XCC_SndXcallAnswerCallCnf(pstXcallAnswerReq->ucCallId,
                                       0,
                                       TAF_CDMA_SO_BUTT,
                                       TAF_XCC_FAIL_LAYER_L3,
                                       TAF_XCC_CAUSE_CONNID_NOT_FOUND);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessApsAnswerDataCallReq_MainCtrl
 功能描述  : 处理ID_APS_XCC_ANSWER_DATA_CALL_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessApsAnswerDataCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_XCC_ANSWER_DATA_CALL_REQ_STRU  *pstAnsCallReq = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAnsCallReq = (APS_XCC_ANSWER_DATA_CALL_REQ_STRU *)pstMsg;

    ucIndex = 0;

    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, &ucIndex))
    {
        /* 给APS发送接听失败 */
        CNAS_XCC_SndApsAnswerDataCallCnf(pstAnsCallReq->ucCallId, TAF_XCC_CAUSE_CONNID_NOT_FOUND);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessSmsAnswerCallReq_MainCtrl
 功能描述  : 处理ID_CSMS_XCC_ANSWER_CALL_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessSmsAnswerCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CSMS_XCC_ANSWER_CALL_REQ_STRU      *pstAnsCallReq = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAnsCallReq = (CSMS_XCC_ANSWER_CALL_REQ_STRU *)pstMsg;

    ucIndex = 0;

    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, &ucIndex))
    {
        /* 给SMS发送接听失败 */
        CNAS_XCC_SndCsmsAnswerCallCnf(pstAnsCallReq->ucCallId, TAF_XCC_CAUSE_CONNID_NOT_FOUND);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXpdsAnswerCallReq_MainCtrl
 功能描述  : 处理ID_CSMS_XCC_ANSWER_CALL_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXpdsAnswerCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XPDS_XCC_ANSWER_CALL_REQ_STRU      *pstAnsCallReq = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAnsCallReq = (XPDS_XCC_ANSWER_CALL_REQ_STRU *)pstMsg;

    ucIndex = 0;

    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, &ucIndex))
    {
        /* 给XPDS发送接听失败 */
        CNAS_XCC_SndXpdsAnswerCallCnf(pstAnsCallReq->ucCallId, TAF_XCC_CAUSE_CONNID_NOT_FOUND);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXcallHangupCallReq_MainCtrl
 功能描述  : 处理ID_XCALL_XCC_HANGUP_CALL_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月06日
    作    者   : y00245242
    修改内容   : 新生成函数

  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1X项目迭代5修改

  3.日    期   : 2015年1月8日
    作    者   : y00245242
    修改内容   : 增加NDSS ORIG功能
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallHangupCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           i;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstOrigReq   = VOS_NULL_PTR;
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangupReq = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    ucMsgNum     = CNAS_XCC_GetBufferedMsgNum();

    pstHangupReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)pstMsg;

    for (i = 0; i < CNAS_MIN(ucMsgNum, CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM); i++)
    {
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
        pstBufferMsgHdr         = (MSG_HEADER_STRU *)CNAS_XCC_GetSpecifiedIndexBufferMsg(i);

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_XCALL_XCC_ORIG_CALL_REQ) == ulBufferMsgEventType)
        {
            pstOrigReq   = (XCALL_XCC_ORIG_CALL_REQ_STRU *)pstBufferMsgHdr;

            if (pstHangupReq->ucCallId == pstOrigReq->ucCallId)
            {
                /* 清除呼叫请求 */
                CNAS_XCC_SndXcallHangUpCallCnf(pstHangupReq->ucCallId);
                CNAS_XCC_FreeSpecifiedIndexBufferMsg(i);
                return VOS_TRUE;
            }
        }
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
    }

    /* 如果无voice call instance激活，直接回复挂机确认 */
    if (VOS_FALSE == CNAS_XCC_IsVoiceCallInstanceActive())
    {
        CNAS_XCC_SndXcallHangUpCallCnf(pstHangupReq->ucCallId);
        return VOS_TRUE;
    }

    /* Get call control instance of hangUp CallId, if fail,
       hangup the emergency call other than mt call.
    */
    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByCallId(pstHangupReq->ucCallId, &ucIndex))
    {
        /* if fail, ucIndex points to mt call instance,
           but hangup callId points to emergency call.So don't execute the following function.
        */
        /* 判断实例是否在等待FLASH REQ的L2 ACK */
        CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq(ucIndex);

        /* 判断实例是否在等待Send Burst DTMF的L2 ACK */
        CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq(ucIndex);

        /* 判断实例是否在等待Cont DTMF Tone Order的L2 ACK */
        CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder(ucIndex);
    }
    else
    {
        /* if wait emergency FWI/EFWI flag exist,the uplayer may hangup the emergency call while mt
          voice call exist, the we could not match the hangup call ID with the current mt voice call ID
          then we should continue match the hangup call ID with the emergency call ID. */
        if (VOS_FALSE == CNAS_XCC_GetWaitEmcFlashMsgRspFlg())
        {
            return VOS_TRUE;
        }

        /* continue get the instance index using the mt voice call id. */
        if (VOS_FALSE == CNAS_XCC_GetCallInstanceIndexByCallId(CNAS_XCC_GetMtVoiceCallId(), &ucIndex))
        {
            return VOS_TRUE;
        }
    }

    if (VOS_TRUE == CNAS_XCC_ProcessHangupCallReqWhenWaitEmcFlashMsgRsp(ucIndex, pstHangupReq))
    {
        return VOS_TRUE;
    }

    CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessApsHangupDataCallReq_MainCtrl
 功能描述  : 处理ID_APS_XCC_HANGUP_DATA_CALL_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2015年1月8日
    作    者   : y00245242
    修改内容   : 增加NDSS ORIG功能
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessApsHangupDataCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
    APS_XCC_ORIG_DATA_CALL_REQ_STRU    *pstOrigReq   = VOS_NULL_PTR;
    APS_XCC_HANGUP_DATA_CALL_REQ_STRU  *pstHangupReq = VOS_NULL_PTR;
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex;

    ucMsgNum     = CNAS_XCC_GetBufferedMsgNum();

    pstHangupReq = (APS_XCC_HANGUP_DATA_CALL_REQ_STRU *)pstMsg;

    for (i = 0; i < CNAS_MIN(ucMsgNum, CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM); i++)
    {
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
        pstBufferMsgHdr         = (MSG_HEADER_STRU *)CNAS_XCC_GetSpecifiedIndexBufferMsg(i);

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_XCC_ORIG_DATA_CALL_REQ) == ulBufferMsgEventType)
        {
            pstOrigReq   = (APS_XCC_ORIG_DATA_CALL_REQ_STRU *)pstBufferMsgHdr;

            if (pstHangupReq->ucCallId == pstOrigReq->ucCallId)
            {
                /* 给APS发送挂断回复 */
                CNAS_XCC_SndApsHangupDataCallCnf(pstHangupReq->ucCallId);

                /* 清除缓存 */
                CNAS_XCC_FreeSpecifiedIndexBufferMsg(i);

                return VOS_TRUE;
            }
        }
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
    }

    /* 如果无data call instance激活，直接回复挂机确认 */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, &ucIndex))
    {
        /* 给APS发送挂断回复 */
        CNAS_XCC_SndApsHangupDataCallCnf(pstHangupReq->ucCallId);

        return VOS_TRUE;
    }

    CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessSmsHangupCallReq_MainCtrl
 功能描述  : 处理ID_CSMS_XCC_END_SMS_CALL_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : w00242748
    修改内容   : 新生成函数

  2.日    期   : 2015年1月8日
    作    者   : y00245242
    修改内容   : 增加NDSS ORIG功能
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessSmsHangupCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
    CSMS_XCC_ORIG_SMS_CALL_REQ_STRU    *pstOrigReq   = VOS_NULL_PTR;
    CSMS_XCC_END_SMS_CALL_REQ_STRU     *pstHangupReq = VOS_NULL_PTR;
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex;

    ucMsgNum     = CNAS_XCC_GetBufferedMsgNum();

    pstHangupReq = (CSMS_XCC_END_SMS_CALL_REQ_STRU *)pstMsg;

    for (i = 0; i < CNAS_MIN(ucMsgNum, CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM); i++)
    {
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
        pstBufferMsgHdr         = (MSG_HEADER_STRU *)CNAS_XCC_GetSpecifiedIndexBufferMsg(i);

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(UEPS_PID_XSMS, ID_CSMS_XCC_ORIG_SMS_CALL_REQ) == ulBufferMsgEventType)
        {
            pstOrigReq   = (CSMS_XCC_ORIG_SMS_CALL_REQ_STRU *)pstBufferMsgHdr;

            if (pstHangupReq->ucCallId == pstOrigReq->ucCallId)
            {
                /* 给SMS发送挂断回复 */
                CNAS_XCC_SndCsmsHangupCallCnf(pstHangupReq->ucCallId);

                /* 清除缓存 */
                CNAS_XCC_FreeSpecifiedIndexBufferMsg(i);

                return VOS_TRUE;
            }
        }
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
    }

    /* 如果无SMS call instance激活，直接回复挂机确认 */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, &ucIndex))
    {
        /* 给SMS发送挂断回复 */
        CNAS_XCC_SndCsmsHangupCallCnf(pstHangupReq->ucCallId);

        return VOS_TRUE;
    }

    CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXpdsHangupCallReq_MainCtrl
 功能描述  : 处理ID_XPDS_XCC_END_AGPS_CALL_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月31日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXpdsHangupCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
    XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU   *pstOrigReq   = VOS_NULL_PTR;
    XPDS_XCC_END_AGPS_CALL_REQ_STRU    *pstHangupReq = VOS_NULL_PTR;
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex;

    ucMsgNum     = CNAS_XCC_GetBufferedMsgNum();

    pstHangupReq = (XPDS_XCC_END_AGPS_CALL_REQ_STRU *)pstMsg;

    for (i = 0; i < CNAS_MIN(ucMsgNum, CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM); i++)
    {
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
        pstBufferMsgHdr         = (MSG_HEADER_STRU *)CNAS_XCC_GetSpecifiedIndexBufferMsg(i);

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(UEPS_PID_XPDS, ID_XPDS_XCC_ORIG_AGPS_CALL_REQ) == ulBufferMsgEventType)
        {
            pstOrigReq   = (XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU *)pstBufferMsgHdr;

            if (pstHangupReq->ucCallId == pstOrigReq->ucCallId)
            {
                /* 给Xpds发送挂断回复 */
                CNAS_XCC_SndXpdsEndCallCnf(pstHangupReq->ucCallId);

                /* 清除缓存 */
                CNAS_XCC_FreeSpecifiedIndexBufferMsg(i);

                return VOS_TRUE;
            }
        }
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
    }

    /* 如果无AGPS call instance激活，直接回复挂机确认 */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, &ucIndex))
    {
        /* 给XPDS发送挂断回复 */
        CNAS_XCC_SndXpdsEndCallCnf(pstHangupReq->ucCallId);

        return VOS_TRUE;
    }

    CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessCas1xPagingInd_MainCtrl
 功能描述  : 处理ID_CAS_CNAS_1X_PAGING_IND
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月06日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xPagingInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucAbortIndex;
    VOS_UINT8                           ucAbortFlag;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulCurrFsmId;
    VOS_UINT32                          ulCurrFsmState;
    VOS_UINT32                          i;
    CNAS_XCC_FSM_ENTITY_STRU           *pstFsmEntity = VOS_NULL_PTR;

    for ( i = 0 ; i < CNAS_XCC_MAX_FSM_ENTITY_NUM ; i++ )
    {
        /* 获取每个状态机 */
        pstFsmEntity = &(CNAS_XCC_GetCtxAddr()->astFsmEntity[i]);

        ulCurrFsmId    = pstFsmEntity->stCurFsm.enFsmId;
        ulCurrFsmState = pstFsmEntity->stCurFsm.ulState;

        /* 当前已在关机状态，忽略寻呼 */
        if ((CNAS_XCC_FSM_L1_MAIN == ulCurrFsmId)
         && (CNAS_XCC_L1_STA_POWER_OFF == ulCurrFsmState))
        {
            /* 忽略寻呼 */
            CNAS_WARNING_LOG(UEPS_PID_XCC,
                             "CNAS_XCC_ProcessCas1xPagingInd_MainCtrl: power off，ignore the page information!");

            return VOS_TRUE;

        }
    }

    if (VOS_TRUE == CNAS_XCC_IsBufferedPowerDownMsgExist_MainCtrl())
    {
        /* 忽略寻呼 */
        CNAS_WARNING_LOG(UEPS_PID_XCC,
                         "CNAS_XCC_ProcessCas1xPagingInd_MainCtrl: ignore the page information!");

        return VOS_TRUE;

    }

    ucAbortIndex = 0;
    ucAbortFlag  = VOS_FALSE;
    if (VOS_FALSE == CNAS_XCC_IsPaginMsgAllowed((CAS_CNAS_1X_PAGING_IND_STRU *)pstMsg, &ucAbortIndex, &ucAbortFlag))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == ucAbortFlag)
    {
        pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

        /* 如果需要终止其他呼叫类型，转呼叫事件为abort事件，并存放到内部队列中 */
        CNAS_XCC_SndXccAbortReq(pstXccCtxAddr->astFsmEntity[ucAbortIndex].stCallInfoCtx.ucConnectId,
                                ulEventType,
                                TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MT_CALL);

        /* 缓存用户请求消息 */
        CNAS_XCC_BufferMsgInQueue(ulEventType, pstMsg);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessMsgWaitingWithinAWI_MainCtrl
 功能描述  : 若AWI消息中存在MsgWaiting Info record，则向XSMS发送指示
 输入参数  : pst1xDschDataInd --- 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : L00256032
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinAWI_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
)
{
    CNAS_XCC_AWIM_STRU                 *pstAWIM = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 完成AWI的解码 */
    pstAWIM = (CNAS_XCC_AWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_AWIM_STRU));
    if (VOS_NULL_PTR == pstAWIM)
    {
        return;
    }

    NAS_MEM_SET_S(pstAWIM, sizeof(CNAS_XCC_AWIM_STRU), 0, sizeof(CNAS_XCC_AWIM_STRU));

    if (VOS_OK != CNAS_XCC_DecodeAlertWithInformationMsg(pst1xDschDataInd, pstAWIM))
    {
        PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);
        return;
    }

    /* 查找解码后的结果中是否有message waiting这个info record */
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_MESSAGE_WAITING,
                                                           pstAWIM->ucNumInfoRecs,
                                                           pstAWIM->astInfoRecsData,
                                                           &ucIndex);

    if (VOS_TRUE == ulResult)
    {
        CNAS_XCC_SndCsmsMsgWaitingInd(pstAWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stMsgWaiting.ucMsgCnt);
    }

    PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessMsgWaitingWithinFWI_MainCtrl
 功能描述  : 若FWI消息中存在MsgWaiting Info record，则向XSMS发送指示
 输入参数  : pst1xDschDataInd --- 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : L00256032
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinFWI_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
)
{
    CNAS_XCC_FWIM_STRU                 *pstFWIM = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 完成FWI的解码 */
    pstFWIM = (CNAS_XCC_FWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_FWIM_STRU));
    if (VOS_NULL_PTR == pstFWIM)
    {
        return;
    }

    NAS_MEM_SET_S(pstFWIM, sizeof(CNAS_XCC_FWIM_STRU), 0, sizeof(CNAS_XCC_FWIM_STRU));

    if (VOS_OK != CNAS_XCC_DecodeFlashWithInformationMsg(pst1xDschDataInd, pstFWIM))
    {
        PS_MEM_FREE(UEPS_PID_XCC, pstFWIM);
        return;
    }

    /* 查找解码后的结果中是否有message waiting这个info record */
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_MESSAGE_WAITING,
                                                           pstFWIM->ucNumInfoRecs,
                                                           pstFWIM->astInfoRecsData,
                                                           &ucIndex);

    if (VOS_TRUE == ulResult)
    {
        CNAS_XCC_SndCsmsMsgWaitingInd(pstFWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stMsgWaiting.ucMsgCnt);
    }

    PS_MEM_FREE(UEPS_PID_XCC, pstFWIM);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessMsgWaitingWithinEAWI_MainCtrl
 功能描述  : 若EAWI消息中存在MsgWaiting Info record，则向XSMS发送指示
 输入参数  : pst1xDschDataInd --- 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : L00256032
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinEAWI_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
)
{
    CNAS_XCC_EAWIM_STRU                *pstEAWIM = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 完成EAWI的解码 */
    pstEAWIM = (CNAS_XCC_EAWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EAWIM_STRU));
    if (VOS_NULL_PTR == pstEAWIM)
    {
        return;
    }

    NAS_MEM_SET_S(pstEAWIM, sizeof(CNAS_XCC_EAWIM_STRU), 0, sizeof(CNAS_XCC_EAWIM_STRU));

    if (VOS_OK != CNAS_XCC_DecodeExtendedAlertWithInformationMsg(pst1xDschDataInd, pstEAWIM))
    {
        PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);
        return;
    }

    /* 查找解码后的结果中是否有message waiting这个info record */
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_MESSAGE_WAITING,
                                                           pstEAWIM->ucNumInfoRecs,
                                                           pstEAWIM->astInfoRecsData,
                                                           &ucIndex);

    if (VOS_TRUE == ulResult)
    {
        CNAS_XCC_SndCsmsMsgWaitingInd(pstEAWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stMsgWaiting.ucMsgCnt);
    }

    PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessMsgWaitingWithinEFWI_MainCtrl
 功能描述  : 若EFWI消息中存在MsgWaiting Info record，则向XSMS发送指示
 输入参数  : pst1xDschDataInd --- 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : L00256032
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinEFWI_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
)
{
    CNAS_XCC_EFWIM_STRU                *pstEFWIM  = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* 完成EFWI的解码 */
    pstEFWIM = (CNAS_XCC_EFWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EFWIM_STRU));
    if (VOS_NULL_PTR == pstEFWIM)
    {
        return;
    }

    NAS_MEM_SET_S(pstEFWIM, sizeof(CNAS_XCC_EFWIM_STRU), 0, sizeof(CNAS_XCC_EFWIM_STRU));

    if (VOS_OK != CNAS_XCC_DecodeExtendedFlashWithInformationMsg(pst1xDschDataInd, pstEFWIM))
    {
        PS_MEM_FREE(UEPS_PID_XCC, pstEFWIM);
        return;
    }

    /* 查找解码后的结果中是否有message waiting这个info record */
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_MESSAGE_WAITING,
                                                           pstEFWIM->ucNumInfoRecs,
                                                           pstEFWIM->astInfoRecsData,
                                                           &ucIndex);

    if (VOS_TRUE == ulResult)
    {
        CNAS_XCC_SndCsmsMsgWaitingInd(pstEFWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stMsgWaiting.ucMsgCnt);
    }

    PS_MEM_FREE(UEPS_PID_XCC, pstEFWIM);

    return;
}

VOS_UINT32 CNAS_XCC_ProcessOrderMsg_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
)
{
    CNAS_XCC_ORDRM_STRU                 stOrdrm;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucConRef;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucDigit;
    VOS_UINT8                           ucSwitch;
    CNAS_XCC_ORDER_TYPE_ENUM_UINT8      enOrderType;


    NAS_MEM_SET_S(&stOrdrm, sizeof(CNAS_XCC_ORDRM_STRU), 0x00, sizeof(CNAS_XCC_ORDRM_STRU));

    if (VOS_OK != CNAS_XCC_DecodeOrderMsg(pst1xDschDataInd, &stOrdrm))
    {
        /* message structure not acceptable */
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stOrdrm.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_STRUCT);
        return VOS_TRUE;
    }

    ulRslt = CNAS_XCC_GetOrderSpecificMsgType(&(stOrdrm.stOrder), &enOrderType);
    if (VOS_OK != ulRslt)
    {
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stOrdrm.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_CODE);
        CNAS_ERROR_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcessOrderMsg_MainCtrl: CNAS_XCC_GetOrderSpecificMsgType FAIL ", ulRslt);
        return VOS_TRUE;
    }

    if (CNAS_XCC_ORDER_TYPE_CONTINUOUS_DTMF_TONE != enOrderType)
    {
        /* Returning VOS_FALSE to process this order in FSM */
        return VOS_FALSE;
    }

    /* if the Protocol Revision is equal to or greater than 7, then the CON_REF must be extracted from the encoded
    ORDM message to get the correct call ID corresponding to this message */
    if (P_REV_IN_USE_7 <= CNAS_CCB_GetPRevInUse())
    {
        /* Get the CON_REF_INCL and CON_REF from the Encoded bit stream */
        CNAS_XCC_DecodeConRefFromFDschOrdmMsg(pst1xDschDataInd->aucMsgData,
                                              pst1xDschDataInd->usMsgDataLen,
                                              &stOrdrm.ucConRefPresent,
                                              &stOrdrm.ucConRef);
    }

    ucConRef = (VOS_TRUE == stOrdrm.ucConRefPresent) ? stOrdrm.ucConRef : CNAS_XCC_INVALID_CON_REF;
    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByCallRef(ucConRef, &ucIndex))
    {
        /* no call control instance present with the specified identifier */
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stOrdrm.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_NO_CC_INST);
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if ((CNAS_XCC_FSM_L1_MAIN != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
     || (CNAS_XCC_L1_STA_CONVERSATION != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        /* message not accepted in this state  */
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stOrdrm.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_STATE);
        return VOS_TRUE;
    }

    ucDigit  = CNAS_XCC_INVALID_DTMF_DIGIT;
    ucSwitch = CNAS_XCC_INVALID_DTMF_SWITCH;

    /* Check the permissible ORDQ */
    ulRslt = CNAS_XCC_GetDigitAndSwitchFromORDQ(stOrdrm.stOrder.ucOrdq, &ucDigit, &ucSwitch);
    if (VOS_OK != ulRslt)
    {
        /* message field not in valid range */
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stOrdrm.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_FIELD);
        return VOS_TRUE;
    }

    /* Send ID_XCC_XCALL_CONT_DTMF_IND message to XCALL */
    ucCallId = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId;
    CNAS_XCC_SndXcallContDTMFInd(ucCallId, ucDigit, ucSwitch);

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessMsgWaitingWithinDschDataInd_MainCtrl
 功能描述  : 处理ID_CAS_CNAS_1X_DSCH_DATA_IND，如果为FWI/EFWI/AWI/EAWI，若消息中存在
             MsgWaiting Info record，则向XSMS发送指示
 输入参数  : pst1xDschDataInd --- 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : L00256032
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinDschDataInd_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
)
{
    switch (pst1xDschDataInd->enDschMsgType)
    {
        case CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG:
            CNAS_XCC_ProcessMsgWaitingWithinAWI_MainCtrl(pst1xDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG:
            CNAS_XCC_ProcessMsgWaitingWithinFWI_MainCtrl(pst1xDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG:
            CNAS_XCC_ProcessMsgWaitingWithinEAWI_MainCtrl(pst1xDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG:
            CNAS_XCC_ProcessMsgWaitingWithinEFWI_MainCtrl(pst1xDschDataInd);
            break;

        default:
            break;
    }

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessCas1xDschDataInd_MainCtrl
 功能描述  : 处理ID_CAS_CNAS_1X_DSCH_DATA_IND
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月06日
    作    者   : y00245242
    修改内容   : 新生成函数

  2.日    期   : 2015-07-24
    作    者   : K00902809
    修改内容   : Added process to handle receiving Continuous DTMF order.

  3.日    期   : 2015-07-24
    作    者   : a00295761
    修改内容   : Added process to handle receiving Burst DTMF Message.
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xDschDataInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd = VOS_NULL_PTR;
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    CNAS_XCC_ORDRM_STRU                 stOrdrm;
    VOS_UINT8                           ucConRef;

    /* 如果是CAS_CNAS_1X_RX_TCH_SERVICE_OPTION_CONTROL_MSG消息，不进状态机 */
    pst1xDschDataInd =(CAS_CNAS_1X_DSCH_DATA_IND_STRU*)pstMsg;
    if (CAS_CNAS_1X_RX_TCH_SERVICE_OPTION_CONTROL_MSG == pst1xDschDataInd->enDschMsgType)
    {
        CNAS_XCC_ProcessCas1xTchServiceOptionControlMsgInd_MainCtrl(pstMsg);
        return VOS_TRUE;
    }

    if (CAS_CNAS_1X_RX_TCH_ORDER_MSG == pst1xDschDataInd->enDschMsgType)
    {
        /*
        Returns VOS_FALSE: If the received ORDER TYPE is not Continuous DTMF order to process pstMsg is FSM.
        Other wise returns VOS_TRUE because the message is processed in the below function and no need to process in FSM.
        */
        return CNAS_XCC_ProcessOrderMsg_MainCtrl(pst1xDschDataInd);
    }

    if (CAS_CNAS_1X_RX_TCH_SEND_BURST_DTMF_MSG == pst1xDschDataInd->enDschMsgType)
    {
        CNAS_XCC_ProcessCas1xTchSndBurstDtmfMsgInd_MainCtrl(ulEventType, pstMsg);
        return VOS_TRUE;
    }

    pst1xDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;

    CNAS_XCC_GetConRefFromDschDataInd(pst1xDschDataInd, &ucConRef);

    if (VOS_FALSE == CNAS_XCC_IsCallConRefExist(ucConRef))
    {
        /* 如果ConRef不存在，发送reject order，消息不进状态机处理 */
        NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

        /* 编码REJ ORDER */
        stRejInfo.ucConRef          = ucConRef;
        stRejInfo.enRejRxTchMsgType = pst1xDschDataInd->enDschMsgType;
        stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
        stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_NO_CC_INST;
        stRejInfo.ulL3PduBitLen     = 0;
        stRejInfo.pucPdudata        = aucPduData;

        if (CAS_CNAS_1X_RX_TCH_ORDER_MSG == pst1xDschDataInd->enDschMsgType)
        {
            NAS_MEM_SET_S(&stOrdrm, sizeof(stOrdrm), 0, sizeof(stOrdrm));

            CNAS_XCC_DecodeOrderMsg(pst1xDschDataInd, &stOrdrm);
            stRejInfo.ucRejOrderCode    = stOrdrm.stOrder.ucOrder;
            stRejInfo.ucRejOrdq         = stOrdrm.stOrder.ucOrdq;
        }

        CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

        /* 发送ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER)给AS */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG,
                                   CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                   0,
                                   (VOS_UINT16)stRejInfo.ulL3PduBitLen,
                                   stRejInfo.pucPdudata);

        return VOS_TRUE;
    }

    CNAS_XCC_ProcessMsgWaitingWithinDschDataInd_MainCtrl(pst1xDschDataInd);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessCas1xReleaseOrderInd_MainCtrl
 功能描述  : 处理ID_CAS_CNAS_1X_RELEASE_ORDER_IND
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月13日
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xReleaseOrderInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 参考Q的实现,as发送release order指示给NW后,终端不需要再进行关机去注册,通知XSD模块关机不需要去注册 */
    CNAS_XCC_SndXsdDeregisterInd(XSD_XCC_DEREGISTER_REASON_POWEROFF);

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessMsgInMainCtrl
 功能描述  : 主控模块中处理入口消息
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月13日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessMsgInMainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           i;

    ulRslt = VOS_FALSE;

    for (i = 0; i < (sizeof(g_astCnasXccMainCtrlProcTab)/sizeof(CNAS_XCC_MAIN_CTRL_PROC_STRU)); i++)
    {
        if (ulEventType == g_astCnasXccMainCtrlProcTab[i].ulMsgEvtType)
        {
            ulRslt = g_astCnasXccMainCtrlProcTab[i].pfMainCtrlProcFun(ulEventType, pstMsg);
            break;
        }
    }

    return ulRslt;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessPagingCollision
 功能描述  : 处理被叫冲突
 输入参数  : enPagingService -- 被叫服务类型
 输出参数  : pucAbortIndex -- 打断索引
             pucAbortFlag -- 打断标记
 返 回 值  : VOS_TRUE  -- 允许发送
             VOS_FALSE -- 不允许发送

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月13日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 CNAS_XCC_ProcessPagingCollision(
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enPagingService,
    VOS_UINT8                          *pucAbortIndex,
    VOS_UINT8                          *pucAbortFlag
)
{
    VOS_UINT8                           ucRslt;
    CNAS_XCC_CALL_INSTANCE_LIST_STRU    stCallInstanceList;

    ucRslt = VOS_TRUE;

    NAS_MEM_SET_S(&stCallInstanceList, sizeof(stCallInstanceList), 0x0, sizeof(stCallInstanceList));

    /* 当前存在环回的被叫，则打断当前的呼叫 */
    if (CNAS_XCC_SERVICE_TYPE_LOOPBACK == enPagingService)
    {
        /* 当前只有不支持并发的情况下，才会需要打断当前的呼叫，因此只可能有一路呼叫 */
        CNAS_XCC_GetAllActiveCallInstanceIndex(&stCallInstanceList);
        if (0 != stCallInstanceList.ucInstanceNum)
        {
            *pucAbortIndex = stCallInstanceList.aucInstance[0];
            *pucAbortFlag = VOS_TRUE;
            ucRslt = VOS_TRUE;
        }
    }
    else if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enPagingService)
    {
        /* 存在数据呼过程中，收到被叫语音呼，打断 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, pucAbortIndex))
        {
            *pucAbortFlag = VOS_TRUE;

            ucRslt = VOS_TRUE;
        }

        /* 存在SMS呼过程中，收到被叫语音呼，打断 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, pucAbortIndex))
        {
            *pucAbortFlag = VOS_TRUE;

            ucRslt = VOS_TRUE;
        }

        /* 存在AGPS呼过程中，收到被叫语音呼，打断 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, pucAbortIndex))
        {
            *pucAbortFlag = VOS_TRUE;

            ucRslt = VOS_TRUE;
        }
    }
    else if (CNAS_XCC_SERVICE_TYPE_DATA_CALL == enPagingService)
    {
        /* 语音被叫过程中，收到被叫数据呼，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }

        /* 短信被叫过程中，收到被叫数据呼，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }


        /* 有语音重拨存在丢弃数据被叫 */
        if (VOS_TRUE == TAF_SDC_GetCsCallExistFlg())
        {
            ucRslt = VOS_FALSE;
        }
        /* 存在AGPS呼过程中，收到被叫数据呼，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }
    }
    else if (CNAS_XCC_SERVICE_TYPE_SMS == enPagingService)
    {
        /* 语音被叫过程中，收到被叫短信，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }

        /* 数据业务被叫过程中，收到被叫短信，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }

        /* 存在AGPS呼过程中，收到被叫短信，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }
    }
    else if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enPagingService)
    {
        /* 语音呼过程中，收到AGPS被叫，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }

        /* 数据呼过程中，收到AGPS被叫，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }

         /* 短信呼过程中，收到AGPS被叫，直接返回 */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }
    }
    else
    {
       ucRslt = VOS_TRUE;
    }

    return ucRslt;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_IsBufferedPowerDownMsgExist
 功能描述  : 处理被叫冲突
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 允许发送
             VOS_FALSE -- 不允许发送

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月28日
    作    者   : w00242748
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_IsBufferedPowerDownMsgExist_MainCtrl(VOS_VOID)
{
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */

    /* check是否有关机缓存 */
    if (0 != CNAS_XCC_GetBufferedMsgNum())
    {
        /* 关机请求是否存在 */
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, begin */
        pstBufferMsgHdr         = (MSG_HEADER_STRU *)CNAS_XCC_GetSpecifiedIndexBufferMsg(0);

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            return VOS_FALSE;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(UEPS_PID_XSD, ID_XSD_XCC_POWER_OFF_REQ) == ulBufferMsgEventType)
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-9, end */
        {
            /* 存在缓存关机，则返回VOS_TRUE */
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndFWIorEFWIWithFlashReq_MainCtrl
 功能描述  : XCC发送FWI或EFWI
 输入参数  : ucIndex           -- voice call实例索引
             *pstXcallFlashReq
 输出参数  : 无
 返 回 值  : VOS_OK    --  消息发送成功
             VOS_ERR   --  消息发送失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
  2.日    期   : 2014年12月1日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modified
*****************************************************************************/
VOS_UINT32 CNAS_XCC_SndFWIorEFWIWithFlashReq_MainCtrl(
    VOS_UINT8                           ucIndex,
    XCALL_XCC_SEND_FLASH_REQ_STRU      *pstXcallFlashReq
)
{
    VOS_UINT8                           ucPRevInUse;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucMsgSeqNum;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    ulPduDataLen = 0;
    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

    /* 分配SEQ NUM */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucSendFlashSeqNum = CNAS_XCC_AllocSeqNum();
    ucMsgSeqNum = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucSendFlashSeqNum;

    /*
        If P_REV_IN_USEs is less than seven, the mobile station shall send a Flash With Information Message .
        If P_REV_IN_USEs is equal to or greater than seven, the mobile station shall perform the following:
          if this Call Control instance is identified by NULL, the mobile station shall send either a Flash
          With Information Message or an Extended Flash With Information Message (with either the CON_REF_INCL
          field of the message set to '0' or the CON_REF_INCL field set to '1' and the CON_REF field set to
          the connection reference of the service option connection corresponding to this call);
          otherwise, the mobile station shall send an  Extended Flash With Information Message, with the
          CON_REF_INCL field of the message set to '1' and the CON_REF field of the message set to the
          connection reference of the service option connection corresponding to this call.
    */

    ucPRevInUse = CNAS_CCB_GetPRevInUse();

    if ( (ucPRevInUse < P_REV_IN_USE_7)
       ||(VOS_TRUE == pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsNullCc))
    {
        /* 需要发送FWI，先完成FWI的编码 */
        if (VOS_OK != CNAS_XCC_EncodeFlashWithInformationMsgWithFlashReq(pstXcallFlashReq->ucDigitNum,
                                                             pstXcallFlashReq->aucDigit,
                                                             aucPduData,
                                                             &ulPduDataLen))
        {
            return VOS_ERR;
        }

        /* 发送FWI */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_FLASH_WITH_INFORMATION_MSG,
                                   CNAS_XCC_TX_ORDER_TYPE_BUTT,
                                   ucMsgSeqNum,
                                   (VOS_UINT16)ulPduDataLen,
                                   aucPduData);

    }
    else
    {
        /* 需要发送EFWI，先完成EFWI的编码 */
        if (VOS_OK != CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithFlashReq(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConRef,
                                                                     pstXcallFlashReq->ucDigitNum,
                                                                     pstXcallFlashReq->aucDigit,
                                                                     aucPduData,
                                                                     &ulPduDataLen))
        {
            return VOS_ERR;
        }

        /* 发送EFWI */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_EXT_FLASH_WITH_INFORMATION_MSG,
                                   CNAS_XCC_TX_ORDER_TYPE_BUTT,
                                   ucMsgSeqNum,
                                   (VOS_UINT16)ulPduDataLen,
                                   aucPduData);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXcallSendFlashReq_MainCtrl
 功能描述  : 处理ID_XCALL_XCC_SEND_FLASH_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallSendFlashReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    XCALL_XCC_SEND_FLASH_REQ_STRU      *pstXcallFlashReq = VOS_NULL_PTR;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucIsEmcCall;
    XCALL_XCC_ORIG_CALL_REQ_STRU        stXcallOrigReq;
    VOS_UINT8                           ucMsgSeqNum;

    pstXcallFlashReq = (XCALL_XCC_SEND_FLASH_REQ_STRU *)pstMsg;

    /* 获取voice call的实例index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        CNAS_XCC_SndXcallSendFlashCnf(pstXcallFlashReq->ucCallId, TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE);

        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* 判断voice call的实例状态是否为Conversation，目前只支持在conversation态处理FLASH请求 */
    if (  (CNAS_XCC_FSM_L1_MAIN != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
       || (CNAS_XCC_L1_STA_CONVERSATION != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        CNAS_XCC_SndXcallSendFlashCnf(pstXcallFlashReq->ucCallId, TAF_XCC_CAUSE_ABNORMAL_STATE);

        return VOS_TRUE;
    }

    ucIsEmcCall = pstXcallFlashReq->ucIsEmcCall;

    if (VOS_TRUE == ucIsEmcCall)
    {
        NAS_MEM_SET_S(&stXcallOrigReq, sizeof(XCALL_XCC_ORIG_CALL_REQ_STRU), 0x00, sizeof(XCALL_XCC_ORIG_CALL_REQ_STRU));

        NAS_MEM_CPY_S(stXcallOrigReq.stCalledPartyNum.aucDigit,
                      XCC_XCALL_MAX_CALLED_NUMBER_CHARI_OCTET_NUM,
                      pstXcallFlashReq->aucDigit,
                      pstXcallFlashReq->ucDigitNum);

        stXcallOrigReq.stCalledPartyNum.ucDigitNum = pstXcallFlashReq->ucDigitNum;

        ucMsgSeqNum = CNAS_XCC_AllocSeqNum();
        pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucSendFlashSeqNum = ucMsgSeqNum;

        stXcallOrigReq.enDigitMode = XCC_XCALL_DIGIT_MODE_ASCII;

        /* 给AS发送ID_CNAS_CAS_1X_DSCH_DATA_REQ(FWI/EFWI) */
        if (VOS_FALSE == CNAS_XCC_SndFWIorEFWIWithEmergencyCallReq_MainCtrl(ucIndex, ucMsgSeqNum, &stXcallOrigReq))
        {
           CNAS_XCC_SndXcallSendFlashCnf(pstXcallFlashReq->ucCallId, TAF_XCC_CAUSE_ENCODE_FAIL);

           return VOS_TRUE;
        }
    }
    else
    {
        /* 给AS发送ID_CNAS_CAS_1X_DSCH_DATA_REQ(FWI/EFWI) */
        if (VOS_OK != CNAS_XCC_SndFWIorEFWIWithFlashReq_MainCtrl(ucIndex, pstXcallFlashReq))
        {
            CNAS_XCC_SndXcallSendFlashCnf(pstXcallFlashReq->ucCallId, TAF_XCC_CAUSE_ENCODE_FAIL);

            return VOS_TRUE;
        }
    }

    /* 置位等待ACK的标记 */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait = VOS_TRUE;

    /* 启动TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK */
    CNAS_XCC_StartTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                        TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK,
                        TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessFlashL2Ack_MainCtrl
 功能描述  : 处理FLASH的L2 ACK
 输入参数  : ucIndex           -- 消息类型+PID
             pst1xDschDataCnf  -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  对应FLASH的L2 ACK
             VOS_FALSE --  非FLASH的L2 ACK，或当前并不在等待FLASH L2 ACK的状态

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月11日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessFlashL2Ack_MainCtrl(
    VOS_UINT8                           ucIndex,
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* 判断voice call的实例是否在等待FLASH REQ的L2 ACK */
    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait)
    {
        return VOS_FALSE;
    }

    /* 判断seqNum是否一致 */
    if (pst1xDschDataCnf->ucMsgSeqNum != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucSendFlashSeqNum)
    {
        return VOS_FALSE;
    }

    /* 清除等待ACK的标记 */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait = VOS_FALSE;

    /* 停止TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK);

    if(CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pst1xDschDataCnf->enRslt)
    {
        enCause = TAF_XCC_CAUSE_SUCCESS;
    }
    else
    {
        enCause = TAF_XCC_CAUSE_L2_ACK_FAIL;
    }
    CNAS_XCC_SndXcallSendFlashCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                  enCause);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessCas1xDschDataCnf_MainCtrl
 功能描述  : 处理ID_CAS_CNAS_1X_DSCH_DATA_CNF
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : L00256032
    修改内容   : 1X SS Project修改

  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1X项目迭代5修改
  3.日    期   : 2015年7月25日
    作    者   : l00324781
    修改内容   : 迭代16修改
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xDschDataCnf_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf = VOS_NULL_PTR;

    pst1xDschDataCnf = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU *)pstMsg;

    /* 获取voice call的实例index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_FALSE;
    }

    /* 判断是否为FWI/EFWI的L2 ACK */
    if (VOS_TRUE == CNAS_XCC_ProcessFlashL2Ack_MainCtrl(ucIndex, pst1xDschDataCnf))
    {
        /* 为FWI/EFWI的L2 ACK，处理完成后直接退出，不需要进入状态机处理 */
        return VOS_TRUE;
    }

    /* 判断是否为Send Burst DTMF的L2 ACK */
    if (VOS_TRUE == CNAS_XCC_ProcessBurstDTMFL2Ack_MainCtrl(ucIndex, pst1xDschDataCnf))
    {
        /* 为Send Burst DTMF的L2 ACK，处理完成后直接退出，不需要进入状态机处理 */
        return VOS_TRUE;
    }

    /* 判断是否为Cont DTMF Tone Order的L2 ACK */
    if (VOS_TRUE == CNAS_XCC_ProcessContDTMFToneOrderL2Ack_MainCtrl(ucIndex, pst1xDschDataCnf))
    {
        /* 为Cont DTMF Tone Order的L2 ACK，处理完成后直接退出，不需要进入状态机处理 */
        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_XCC_ProcessEmergencyCallFlashMsgRsp_MainCtrl(ucIndex, pst1xDschDataCnf))
    {
        return VOS_TRUE;
    }


    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiProtectFlashCnfL2Ack_MainCtrl
 功能描述  : 处理TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK定时器超时
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE --  消息都不需要进状态机处理，故该函数返回值都为VOS_TRUE

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiProtectFlashCnfL2Ack_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    /* 获取voice call的实例index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
    /* 判断voice call的实例是否在等待FLASH REQ的L2 ACK */
    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait)
    {
        return VOS_TRUE;
    }

    /* 清除等待ACK的标记 */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait = VOS_FALSE;

    CNAS_XCC_SndXcallSendFlashCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                  TAF_XCC_CAUSE_L2_ACK_TIME_OUT);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiProtectBurstDTMFCnfL2Ack_MainCtrl
 功能描述  : 处理TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK定时器超时
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE --  消息都不需要进状态机处理，故该函数返回值都为VOS_TRUE

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiProtectBurstDTMFCnfL2Ack_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;


    /* 获取voice call的实例index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
    /* 判断voice call的实例是否在等待Send Burst DTMF的L2 ACK */
    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait)
    {
        return VOS_TRUE;
    }

    /* 清除等待ACK的标记 */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait = VOS_FALSE;

    CNAS_XCC_SndXcallSendBurstDTMFCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                      TAF_XCC_CAUSE_L2_ACK_TIME_OUT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXcallSendBurstDTMFReq_MainCtrl
 功能描述  : 处理ID_XCALL_XCC_BURST_DTMF_REQ
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallSendBurstDTMFReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    XCALL_XCC_BURST_DTMF_REQ_STRU      *pstXcallBurstDTMFReq = VOS_NULL_PTR;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXcallBurstDTMFReq = (XCALL_XCC_BURST_DTMF_REQ_STRU *)pstMsg;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByCallId(pstXcallBurstDTMFReq->ucCallId, &ucIndex))
    {
        CNAS_XCC_SndXcallSendBurstDTMFCnf(pstXcallBurstDTMFReq->ucCallId, TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE);

        return VOS_TRUE;
    }

    /* 判断voice call的实例状态是否为Conversation，目前只支持在conversation态处理Burst DTMF请求 */
    if (  (CNAS_XCC_FSM_L1_MAIN != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
       || (CNAS_XCC_L1_STA_CONVERSATION != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        CNAS_XCC_SndXcallSendBurstDTMFCnf(pstXcallBurstDTMFReq->ucCallId, TAF_XCC_CAUSE_ABNORMAL_STATE);

        return VOS_TRUE;
    }

    /* 给CAS发送ID_CNAS_CAS_1X_DSCH_DATA_REQ(Send Burst DTMF) */
    if (VOS_OK != CNAS_XCC_SndBurstDTMF_MainCtrl(ucIndex, pstXcallBurstDTMFReq))
    {
        CNAS_XCC_SndXcallSendBurstDTMFCnf(pstXcallBurstDTMFReq->ucCallId, TAF_XCC_CAUSE_ENCODE_FAIL);

        return VOS_TRUE;
    }

    /* 置位等待ACK的标记 */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait = VOS_TRUE;

    /* 启动TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK */
    CNAS_XCC_StartTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                        TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK,
                        TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndBurstDTMF_MainCtrl
 功能描述  : XCC发送Send Burst DTMF
 输入参数  : ucIndex               -- voice call实例索引
             pstXcallBurstDTMFReq  -- Burst DTMF请求消息指针
 输出参数  : 无
 返 回 值  : VOS_OK                --  消息发送成功
             VOS_ERR               --  消息发送失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_SndBurstDTMF_MainCtrl(
    VOS_UINT8                           ucIndex,
    XCALL_XCC_BURST_DTMF_REQ_STRU      *pstXcallBurstDTMFReq
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucMsgSeqNum;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    ulPduDataLen = 0;
    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

    /* 分配SEQ NUM */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucBurstDtmfSeqNum = CNAS_XCC_AllocSeqNum();
    ucMsgSeqNum = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucBurstDtmfSeqNum;

    /* 需要发送Send Burst DTMF，先完成编码 */
    if (VOS_OK != CNAS_XCC_EncodeSendBurstDTMFMsg(pstXcallBurstDTMFReq,
                                                  aucPduData,
                                                 &ulPduDataLen))
    {
        return VOS_ERR;
    }

    /* 发送Send Burst DTMF */
    CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_SEND_BURST_DTMF_MSG,
                               CNAS_XCC_TX_ORDER_TYPE_BUTT,
                               ucMsgSeqNum,
                               (VOS_UINT16)ulPduDataLen,
                               aucPduData);
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessBurstDTMFL2Ack_MainCtrl
 功能描述  : 处理Send Burst DTMF的L2 ACK
 输入参数  : ucIndex           -- 消息类型+PID
             pst1xDschDataCnf  -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  对应Send Burst DTMF的L2 ACK
             VOS_FALSE --  非Send Burst DTMF的L2 ACK，或当前并不在等待Send Burst DTMFL2 ACK的状态

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessBurstDTMFL2Ack_MainCtrl(
    VOS_UINT8                           ucIndex,
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* 判断voice call的实例是否在等待Send Burst DTMF的L2 ACK */
    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait)
    {
        return VOS_FALSE;
    }

    /* 判断seqNum是否一致 */
    if (pst1xDschDataCnf->ucMsgSeqNum != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucBurstDtmfSeqNum)
    {
        return VOS_FALSE;
    }

    /* 清除等待ACK的标记 */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait = VOS_FALSE;

    /* 停止TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK);

    if(CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pst1xDschDataCnf->enRslt)
    {
        enCause = TAF_XCC_CAUSE_SUCCESS;
    }
    else
    {
        enCause = TAF_XCC_CAUSE_L2_ACK_FAIL;
    }

    CNAS_XCC_SndXcallSendBurstDTMFCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId, enCause);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessCas1xCallTerminateInd_MainCtrl
 功能描述  : 处理ID_CAS_CNAS_1X_CALL_TERMINATE_IND
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月13日
    作    者   : L00256032
    修改内容   : 1X SS Project修改

  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1X项目迭代5修改

  3.日    期   : 2015年1月8日
    作    者   : y00245242
    修改内容   : 增加NDSS ORIG功能
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xCallTerminateInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU                    *pstCallTerminateInd;
    VOS_UINT8                                               ucIndex;

    pstCallTerminateInd = (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU *)pstMsg;

    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByConnId(pstCallTerminateInd->ucConnectId, &ucIndex))
    {
        return VOS_FALSE;
    }

    /* 判断实例是否在等待FLASH REQ的L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq(ucIndex);

    /* 判断实例是否在等待Send Burst DTMF的L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq(ucIndex);

    /* 判断实例是否在等待Cont DTMF Tone Order的L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder(ucIndex);

    CNAS_XCC_ProcessReleaseWhenWaitEmcFlashMsgRsp(ucIndex);

    CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessCas1xCallRelInd_MainCtrl
 功能描述  : 处理ID_CAS_CNAS_1X_CALL_REL_IND
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月13日
    作    者   : L00256032
    修改内容   : 1X SS Project修改

  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1X项目迭代5修改

  3.日    期   : 2015年1月8日
    作    者   : y00245242
    修改内容   : 增加NDSS ORIG功能
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xCallRelInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_CALL_REL_IND_STRU                          *pstCallRelInd;
    VOS_UINT8                                               ucIndex;

    pstCallRelInd = (CAS_CNAS_1X_CALL_REL_IND_STRU *)pstMsg;

    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByConnId(pstCallRelInd->ucConnectId, &ucIndex))
    {
        return VOS_TRUE;
    }

    /* 判断实例是否在等待FLASH REQ的L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq(ucIndex);

    /* 判断实例是否在等待Send Burst DTMF的L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq(ucIndex);

    /* 判断实例是否在等待Cont DTMF Tone Order的L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder(ucIndex);

    CNAS_XCC_ProcessReleaseWhenWaitEmcFlashMsgRsp(ucIndex);

    CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXccPowerDownInd_MainCtrl
 功能描述  : 处理ID_CNAS_XCC_XCC_POWER_DOWN_IND
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月13日
    作    者   : L00256032
    修改内容   : 1X SS Project修改

  2.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1X项目迭代5修改
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXccPowerDownInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_XCC_POWER_DOWN_IND_STRU                       *pstPowerDownInd;
    VOS_UINT8                                               ucIndex;

    pstPowerDownInd = (CNAS_XCC_XCC_POWER_DOWN_IND_STRU *)pstMsg;

    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByConnId(pstPowerDownInd->ucConnectId, &ucIndex))
    {
        return VOS_TRUE;
    }

    /* 判断实例是否在等待FLASH REQ的L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq(ucIndex);

    /* 判断实例是否在等待Send Burst DTMF的L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq(ucIndex);

    /* 判断实例是否在等待Cont DTMF Tone Order的L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder(ucIndex);

    CNAS_XCC_ProcessReleaseWhenWaitEmcFlashMsgRsp(ucIndex);

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessCas1xCschFeatureNotificationMsgInd_MainCtrl
 功能描述  : 处理CAS_CNAS_1X_RX_COMMON_FEATURE_NOTIFICATION_MSG
 输入参数  : pstCschDataInd -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xCschFeatureNotificationMsgInd_MainCtrl(
    CAS_CNAS_1X_CSCH_DATA_IND_STRU     *pstCschDataInd
)
{
    CNAS_XCC_FNM_STRU                  *pstFNM = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;


    /* 完成FNM的解码 */
    pstFNM = (CNAS_XCC_FNM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_FNM_STRU));
    if (VOS_NULL_PTR == pstFNM)
    {
        return VOS_TRUE;
    }

    if (VOS_OK != CNAS_XCC_DecodeFeatureNotificationMsg(pstCschDataInd, pstFNM))
    {
        PS_MEM_FREE(UEPS_PID_XCC, pstFNM);
        return VOS_TRUE;
    }

    /* 新增发送MS ACK的处理，目前的处理是短信和XCC需要判断公共信道上的消息是否需要确认，如果需要
    　　确认，则发送MS ACK给网络 */
    if ( VOS_TRUE == pstCschDataInd->enAckReqFlag )
    {
        if (VOS_OK == CNAS_XCC_EncodeCschMsAckOrderMsg(aucPduData, &ulPduDataLen))
        {
            CNAS_XCC_SndCasCschDataReq(CAS_CNAS_1X_TX_COMMON_ORDER_MSG,
                                       pstCschDataInd->enAckReqFlag,
                                       pstCschDataInd->aucAckPara,
                                       (VOS_UINT16)ulPduDataLen,
                                       aucPduData);
        }
    }


    if (VOS_TRUE == pstFNM->ucIsRelease)
    {
        /* 通知接入层电话释放，发送REL REQ给CAS */
        CNAS_XCC_SndCasCallRelReq(0, 0, CAS_CNAS_1X_REL_REASON_FNM_RELEASE,VOS_TRUE);
    }


    /* 查找解码后的结果中是否有Message Waiting项，有的话，通知XSMS*/
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_MESSAGE_WAITING,
                                                           pstFNM->ucNumInfoRecs,
                                                           pstFNM->astInfoRecsData,
                                                           &ucIndex);
    if (VOS_TRUE == ulResult)
    {
        CNAS_XCC_SndCsmsMsgWaitingInd(pstFNM->astInfoRecsData[ucIndex].stInfoRecs.u.stMsgWaiting.ucMsgCnt);
    }


    /* 消息通过ID_XCC_XCALL_INFO_REC_IND上报给XCALL */
    CNAS_XCC_SndXcallCschInfoRecInd(CNAS_XCC_INVAILD_CALL_ID,
                                    CAS_CNAS_1X_RX_COMMON_FEATURE_NOTIFICATION_MSG,
                                    (VOS_UINT8*)pstFNM);


    PS_MEM_FREE(UEPS_PID_XCC, pstFNM);
    return VOS_TRUE;

}



/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessCas1xCschDataInd_L1Main_MainCtrl
 功能描述  : 处理ID_CAS_CNAS_1X_CSCH_DATA_IND
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xCschDataInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_CSCH_DATA_IND_STRU     *pstCschDataInd  = VOS_NULL_PTR;


    pstCschDataInd  = (CAS_CNAS_1X_CSCH_DATA_IND_STRU*)pstMsg;


    switch(pstCschDataInd->enCschMsgType)
    {
        case CAS_CNAS_1X_RX_COMMON_FEATURE_NOTIFICATION_MSG:
            CNAS_XCC_ProcessCas1xCschFeatureNotificationMsgInd_MainCtrl(pstCschDataInd);

            CNAS_MNTN_Log1xCschDataIndMsg(UEPS_PID_XCC,
                                          pstCschDataInd->usMsgDataLen,
                                          pstCschDataInd->enCschMsgType,
                                          pstCschDataInd->aucMsgData);
            break;

        default:
            CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcessCas1xCschDataInd_MainCtrl wrong Msg Type", pstCschDataInd->enCschMsgType);
            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessCas1xTchServiceOptionControlMsgInd_L1Main_MainCtrl
 功能描述  : 处理CAS_CNAS_1X_RX_TCH_SERVICE_OPTION_CONTROL_MSG
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xTchServiceOptionControlMsgInd_MainCtrl(
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd  = VOS_NULL_PTR;
    CNAS_XCC_SOCM_STRU                  stSOCM;

    pstDschDataInd  = (CAS_CNAS_1X_DSCH_DATA_IND_STRU*)pstMsg;
    if (VOS_OK != CNAS_XCC_DecodeServiceOptionControlMsg(pstDschDataInd, &stSOCM))
    {
        return VOS_TRUE;
    }

    switch (stSOCM.usSo)
    {
        case CAS_CNAS_1X_SO_3_EVRC:
        case CAS_CNAS_1X_SO_68_EVRC_B:
            CNAS_XCC_ProcessVoiceSoCtrlMsg_MainCtrl(&stSOCM);
            break;

        case CAS_CNAS_1X_SO_33_PPP_PKT_DATA_CDMA2K:
            CNAS_XCC_ProcessDataSoCtrlMsg_MainCtrl(&stSOCM);
            break;

        /* only support data service and voice service */
        default:
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessVoiceSoCtrlMsg_MainCtrl
 功能描述  : 处理处理语音业务的Service Option Control消息
 输入参数  : pstSOCM   -- 解码消息内容
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessVoiceSoCtrlMsg_MainCtrl(
    CNAS_XCC_SOCM_STRU                 *pstSOCM
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo;
    VOS_UINT8                           ucOctetLen;

    /* get the voice call entity，if can not find，return */
    if (VOS_FALSE == CNAS_XCC_GetCallInstanceIndexByCallRef(pstSOCM->ucConRef, &ucIndex))
    {
        return;
    }

    /* if para is invalid, return */
    if (VOS_FALSE == CNAS_XCC_VoiceSoCtrlMsgParaCheck(pstSOCM))
    {
        return;
    }

    /* 当前语音的SOCM消息长度是8bit整数倍，因此这里直接取整数 */
    ucOctetLen = (VOS_UINT8)(pstSOCM->usBitLen / CNAS_XCC_OCTET_BIT_LEN);

    /*  the USE_TIME field is set to '1', the base station shall set this field
         to the System Time, in units of 80 ms (modulo 64), at which the message
         is to take effect.  If the USE_TIME field set to '0' the base station shall
         set this field to '00000' */
    if (0 == pstSOCM->ucUseTime)
    {
        pstSOCM->ucActionTime = 0;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
    pstCallInfo = (CNAS_XCC_CALL_INFO_CTX_STRU*)(&(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx));

    /* Send Mesaage to XCALL */
    CNAS_XCC_SndXcallSoCtrlMsgInd(pstCallInfo,
                                  pstSOCM->aucData,
                                  ucOctetLen,
                                  pstSOCM->ucActionTime);

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessDataSoCtrlMsg_MainCtrl
 功能描述  : 处理处理数据业务的Service Option Control消息
 输入参数  : pstSOCM   -- 解码消息内容
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月18日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessDataSoCtrlMsg_MainCtrl(
    CNAS_XCC_SOCM_STRU                 *pstSOCM
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo;

    /* 获取数据业务的呼叫实体，如果找不到，直接返回 */
    if (VOS_FALSE == CNAS_XCC_GetCallInstanceIndexByCallRef(pstSOCM->ucConRef, &ucIndex))
    {
        return;
    }


    if (VOS_FALSE == CNAS_XCC_DataSoCtrlMsgParaCheck(pstSOCM))
    {
        return;
    }

    /*  the USE_TIME field is set to '1', the base station shall set this field
         to the System Time, in units of 80 ms (modulo 64), at which the message
         is to take effect.  If the USE_TIME field set to '0' the base station shall
         set this field to '00000' */
    if (0 == pstSOCM->ucUseTime)
    {
        pstSOCM->ucActionTime = 0;
    }


    /* 其他情况下，发送ID_XCC_APS_SO_CTRL_MSG_IND给APS */
    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
    pstCallInfo = (CNAS_XCC_CALL_INFO_CTX_STRU*)(&(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx));
    CNAS_XCC_SndApsSoCtrlMsgInd(pstCallInfo, pstSOCM);

}



/*****************************************************************************
 函 数 名  : CNAS_XCC_IsSendingEmcFlashMsgAllowed_MainCtrl
 功能描述  : check sending emergency call FWI/EFWI message allowed or not
 输入参数  : ucCurInstanceIndex----current call instance index
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- need send flash msg
             VOS_FALSE -- need not send flash msg

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_IsSendingEmcFlashMsgAllowed_MainCtrl(
    VOS_UINT8                           ucCurInstanceIndex
)
{
    CNAS_XCC_FSM_ID_ENUM_UINT32         enFsmId;
    VOS_UINT32                          ulState;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
    ulState       = pstXccCtxAddr->astFsmEntity[ucCurInstanceIndex].stCurFsm.ulState;
    enFsmId       = pstXccCtxAddr->astFsmEntity[ucCurInstanceIndex].stCurFsm.enFsmId;

    /* follow C.S0005 protocol, converstation sate,wait for answer state, wait or order state should
       send a flash with info message while receive a emergency call.But follow Q logic,while in wait
       for order state,the ui did not show "ring",so here easy to process :return orig fail with one
       special cause to uplayer the redial in the next state. */
    if ((CNAS_XCC_FSM_L1_MAIN           == enFsmId)
     && (CNAS_XCC_L1_STA_CONVERSATION   == ulState))
    {
        return VOS_TRUE;
    }

    if (CNAS_XCC_FSM_MT_CALLING == enFsmId)
    {
        switch(ulState)
        {
            case CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER:
            case CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP:

                if (CNAS_CCB_GetPRevInUse() >= P_REV_IN_USE_7)
                {
                    return VOS_TRUE;
                }
                else
                {
                    return VOS_FALSE;
                }

            default:

                return VOS_FALSE;
        }
    }

    /* else for wait for order state, also send back one speical cause to the uplayer
       and wait the uplayer to retry later. */

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXcallEmgencyCallReq_MainCtrl
 功能描述  : process emergency call reqest message
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modified
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallEmergencyCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucSeqNum;
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstXcallOrigReq = VOS_NULL_PTR;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;

    pstXcallOrigReq = (XCALL_XCC_ORIG_CALL_REQ_STRU *)pstMsg;

    /* if voice call instance does not exist,continue process in the state machine. */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_FALSE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
    ucCallId      = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId;

    /* send emergency call flash with info message following the C.S0005 protocol */
    /* If the Call Control instance receives an indication that the user has originated
       an  emergency call (see 2.6.4.3), the mobile station shall send a Flash With Information
       Message or an Extended Flash With Information Message in assured mode with a  Global
       Emergency Call Information Record */

    /* allocate new sequence number and save it */
    ucSeqNum = CNAS_XCC_AllocSeqNum();

    if (VOS_FALSE == CNAS_XCC_SndFWIorEFWIWithEmergencyCallReq_MainCtrl(ucIndex, ucSeqNum, pstXcallOrigReq))
    {
        CNAS_XCC_SndXcallOrigCallCnf(pstXcallOrigReq->ucCallId, TAF_XCC_FAIL_LAYER_L3, TAF_XCC_CAUSE_ENCODE_FAIL, TAF_XCC_CALLID_NULL, 0);

        return VOS_TRUE;
    }

    CNAS_XCC_SetWaitEmcFlashMsgRspFlg(VOS_TRUE);

    CNAS_XCC_SaveEmcFlashMsgSeqNum(ucSeqNum);

    CNAS_XCC_SaveEmcCallId(pstXcallOrigReq->ucCallId);
    CNAS_XCC_SaveMtVoiceCallId(ucCallId);

    CNAS_XCC_StartTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                        TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK,
                        TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_SndFWIorEFWIWithEmergencyCallReq_MainCtrl
 功能描述  : XCC send emergency call flash message
 输入参数  : ucIndex           -- voice call实例索引
             *pstXcallFlashReq
 输出参数  : 无
 返 回 值  : VOS_OK    --  消息发送成功
             VOS_ERR   --  消息发送失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modified
*****************************************************************************/
VOS_UINT32 CNAS_XCC_SndFWIorEFWIWithEmergencyCallReq_MainCtrl(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucMsgSeqNum,
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstOrigReq
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    ulPduDataLen = 0;
    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

    /*
        If this Call Control instance is identified by NULL, the mobile station shall send  either
        a Flash With Information Message or an Extended Flash With Information Message (with either
        the CON_REF_INCL field of the message set to '0' or the CON_REF_INCL field set to '1' and
        the CON_REF field set to the connection reference of the service option connection corresponding
        to this call); otherwise,the mobile station shall send an Extended Flash With Information Message,
        with the CON_REF_INCL field of the message set to '1' and the CON_REF field of the  message set to
        the connection reference of the service option connection  corresponding to this call.
    */

    if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsNullCc)
    {
        /* ucIsNullCc = 1时，需根据协议版本发送不同Type的FWI消息 */
        if (P_REV_IN_USE_7 > CNAS_CCB_GetPRevInUse())
        {
            /* 需要发送FWI，先完成FWI的编码 Type = KEYPAD_FACILITY */
            if (VOS_OK != CNAS_XCC_EncodeFlashWithInformationMsgWithFlashReq(pstOrigReq->stCalledPartyNum.ucDigitNum,
                                                                         pstOrigReq->stCalledPartyNum.aucDigit,
                                                                         aucPduData,
                                                                         &ulPduDataLen))
            {
                return VOS_FALSE;
            }
        }
        else
        {
            /* 需要发送FWI，先完成FWI的编码，Type = EMERGENCY_CALL */
            if (VOS_OK != CNAS_XCC_EncodeFlashWithInformationMsgWithEmergencyCallReq(pstOrigReq->enDigitMode,
                                                                               &(pstOrigReq->stCalledPartyNum),
                                                                               aucPduData,
                                                                               &ulPduDataLen))
            {
                return VOS_FALSE;
            }
        }

        /* 发送FWI */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_FLASH_WITH_INFORMATION_MSG,
                                   CNAS_XCC_TX_ORDER_TYPE_BUTT,
                                   ucMsgSeqNum,
                                   (VOS_UINT16)ulPduDataLen,
                                   aucPduData);

    }
    else
    {
        /* 需要发送EFWI，先完成EFWI的编码 */
        if (VOS_OK != CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithEmergencyCallReq(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConRef,
                                                                                   pstOrigReq->enDigitMode,
                                                                                   &(pstOrigReq->stCalledPartyNum),
                                                                                   aucPduData,
                                                                                   &ulPduDataLen))
        {
            return VOS_FALSE;
        }

        /* 发送EFWI */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_EXT_FLASH_WITH_INFORMATION_MSG,
                                   CNAS_XCC_TX_ORDER_TYPE_BUTT,
                                   ucMsgSeqNum,
                                   (VOS_UINT16)ulPduDataLen,
                                   aucPduData);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessHangupCallReqWhenWaitEmcFlashMsgRsp
 功能描述  : process the hang up call request when waiting for the respnose of the emc FWI/EFWI msg
 输入参数  : ucIndex-------------------current call instance index
             pstHangupReq -------------hangup call request message
 输出参数  : VOS_VOID
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modified

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessHangupCallReqWhenWaitEmcFlashMsgRsp(
    VOS_UINT8                           ucIndex,
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangupReq
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucEmcCallId;
    VOS_UINT8                           ucMtVoiceCallId;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_FALSE == CNAS_XCC_GetWaitEmcFlashMsgRspFlg())
    {
        return VOS_FALSE;
    }

    /* no matter hangup the mt voice call or the emergency call, we should stop the timer and
       clear the emc ctrl info. */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK);

    ucEmcCallId     = CNAS_XCC_GetEmcCallId();
    ucMtVoiceCallId = CNAS_XCC_GetMtVoiceCallId();

    CNAS_XCC_InitEmergencyCallCtrlCtx(&(pstXccCtxAddr->stMainCtrlCtx.stEmcCallCtrl));

    /* if hangup emergency call, we response the hangup cnf to uplayer and this message
       need not process any more. */
    if (ucEmcCallId == pstHangupReq->ucCallId)
    {
        CNAS_XCC_SndXcallHangUpCallCnf(ucEmcCallId);

        return VOS_TRUE;
    }

    /* if hangup mt voice call,we should disconnect the emergency call and this meesage
       should be continue processed in the state machine. */
    if (ucMtVoiceCallId == pstHangupReq->ucCallId)
    {
        CNAS_XCC_SndXcallOrigCallCnf(ucEmcCallId, TAF_XCC_FAIL_LAYER_L3, TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE, TAF_XCC_CALLID_NULL, 0);

        return VOS_FALSE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessEmergencyCallFlashMsgRsp_MainCtrl
 功能描述  : process the respnose of the emc FWI/EFWI msg
 输入参数  : ucIndex-------------------current call instance index
             pst1xDschDataCnf ---------the response of the emc FWI/EFWI msg
 输出参数  : VOS_VOID
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modified

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessEmergencyCallFlashMsgRsp_MainCtrl(
    VOS_UINT8                           ucIndex,
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucEmcSeqNum;
    VOS_UINT8                           ucOrigCallId;

    ucOrigCallId                        = TAF_XCC_CALLID_NULL;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_FALSE == CNAS_XCC_GetWaitEmcFlashMsgRspFlg())
    {
        return VOS_FALSE;
    }

    /* compare the sequence number,if not match, return */
    ucEmcSeqNum = CNAS_XCC_GetEmcFlashMsgSeqNum();

    if (ucEmcSeqNum != pst1xDschDataCnf->ucMsgSeqNum)
    {
        return VOS_FALSE;
    }

    if (CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pst1xDschDataCnf->enRslt)
    {
        ucOrigCallId                    = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId;
    }

    /* stop the timer and clear the emc ctrl info. */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK);

    CNAS_XCC_SndXcallOrigCallCnf(CNAS_XCC_GetEmcCallId(),
                                 TAF_XCC_FAIL_LAYER_L3,
                                 TAF_XCC_CAUSE_EMERGENCY_CALL_FLASHED,
                                 ucOrigCallId,
                                 0);

    CNAS_XCC_InitEmergencyCallCtrlCtx(&(pstXccCtxAddr->stMainCtrlCtx.stEmcCallCtrl));

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiWaitEmergencyCallFlashCnfL2Ack_MainCtrl
 功能描述  : process the expired of the timer:TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE --  消息都不需要进状态机处理，故该函数返回值都为VOS_TRUE

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration Modifed
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitEmergencyCallFlashCnfL2Ack_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_MAIN_CTRL_CTX_STRU        *pstMainCtrlCtx = VOS_NULL_PTR;

    /* 获取voice call的实例index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_TRUE;
    }

    if (VOS_FALSE == CNAS_XCC_GetWaitEmcFlashMsgRspFlg())
    {
        return VOS_TRUE;
    }

    pstMainCtrlCtx = CNAS_XCC_GetMainCtrlCtx();

    CNAS_XCC_SndXcallOrigCallCnf(CNAS_XCC_GetEmcCallId(), TAF_XCC_FAIL_LAYER_L3, TAF_XCC_CAUSE_L2_ACK_TIME_OUT, TAF_XCC_CALLID_NULL, 0);

    CNAS_XCC_InitEmergencyCallCtrlCtx(&(pstMainCtrlCtx->stEmcCallCtrl));

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessReleaseWhenWaitEmcFlashMsgRsp
 功能描述  : process the release when waiting for the respnose of the emc FWI/EFWI msg
 输入参数  : ucIndex-------------------current call instance index
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月26日
    作    者   : w00176964
    修改内容   : CDMA 1X Iteration 5 Modified

*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessReleaseWhenWaitEmcFlashMsgRsp(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_FALSE == CNAS_XCC_GetWaitEmcFlashMsgRspFlg())
    {
        return;
    }

    ucCallId = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId;

    /* check the mt voice call id matahed or not */
    if (ucCallId != CNAS_XCC_GetMtVoiceCallId())
    {
        return;
    }

    /* stop the timer and clear the emc ctrl info. */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK);

    CNAS_XCC_SndXcallOrigCallCnf(CNAS_XCC_GetEmcCallId(), TAF_XCC_FAIL_LAYER_L3, TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE, TAF_XCC_CALLID_NULL, 0);

    CNAS_XCC_InitEmergencyCallCtrlCtx(&(pstXccCtxAddr->stMainCtrlCtx.stEmcCallCtrl));

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessCas1xNdssRecordDialedDigitsInd_MainCtrl
 功能描述  : 处理在呼叫过程中，包括呼叫建立过程中或呼叫在TCH态下，发生业务重定向
             呼叫处理
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年09月06日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xNdssRecordDialedDigitsInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;

    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    CNAS_XCC_FSM_ENTITY_STRU           *pstFsmEntity = VOS_NULL_PTR;

    ucIndex = CNAS_XCC_GetLastCallIndex();

    if (CNAS_XCC_INVAILD_CALL_INDEX == ucIndex)
    {
        return VOS_TRUE;
    }

    pstFsmEntity = &(CNAS_XCC_GetCtxAddr()->astFsmEntity[ucIndex]);

    /* 呼叫实体已经去激活，退出处理 */
    if (VOS_FALSE == pstFsmEntity->stCallInfoCtx.ucIsEntityActive)
    {
        return VOS_TRUE;
    }

    /* 现有设计仅实现在TCH状态下的最后一路呼叫如果是语音呼叫， 可以采用协议定义的NDSS方案重拨，
       其他都采用原有的重拨机制.
       */
    /* 将SO转换成SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstFsmEntity->stCallInfoCtx.enCurrentSo, &enServiceType);

    if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
    {
        /* 判断实例是否在等待FLASH REQ的L2 ACK */
        CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq(ucIndex);

        /* 判断实例是否在等待Send Burst DTMF的L2 ACK */
        CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq(ucIndex);

        /* 判断实例是否在等待Cont DTMF Tone Order的L2 ACK */
        CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder(ucIndex);

        CNAS_XCC_ProcessReleaseWhenWaitEmcFlashMsgRsp(ucIndex);

        /* 发送XCC内部消息，通知NDSS redial indication */
        CNAS_XCC_SndXccNdssRedialInd(pstFsmEntity->stCallInfoCtx.ucConnectId);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXsdNdssResultInd_MainCtrl
 功能描述  : 处理XSD呼叫过程中重定向结果。这里直接透传给TAF
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月08日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXsdNdssResultInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_XCC_NDSS_RESULT_IND_STRU       *pstNdssResultInd = VOS_NULL_PTR;

    pstNdssResultInd = (XSD_XCC_NDSS_RESULT_IND_STRU *)pstMsg;

    CNAS_XCC_SndXcallNdssResultInd((XCC_XCALL_NDSS_RESULT_ENUM_UINT8)pstNdssResultInd->enNsddResult);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessApsPzidInfoNtf_MainCtrl
 功能描述  : 处理Aps的Pzid信息，发送给网络
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月10日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessApsPzidInfoNtf_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_XCC_PZID_INFO_NTF_STRU         *pstPzidInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;
    VOS_UINT8                           ucConRef;

    pstPzidInfo = (APS_XCC_PZID_INFO_NTF_STRU*)pstMsg;

    ulRslt = CNAS_XCC_GetCallInstanceIndexByConnId(pstPzidInfo->ucConnectId,&ucIndex);

    if (VOS_TRUE == ulRslt)
    {
        pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
        ucConRef = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConRef;
        ulPduDataLen= 0;
        NAS_MEM_SET_S(aucPduData, sizeof(aucPduData), 0, sizeof(aucPduData));
        if (VOS_OK != CNAS_XCC_EncodeServiceOptionCtrlMsg(pstPzidInfo, ucConRef,aucPduData,&ulPduDataLen))
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_ProcessApsPzidInfoNtf_MainCtrl: Encode fail");
            return VOS_TRUE;
        }

        /* 发送SERVICE OPTION CONTROL MESSAG */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_SERVICE_OPTION_CONTROL_MSG,
                                   CNAS_XCC_TX_ORDER_TYPE_BUTT,
                                   0,
                                   (VOS_UINT16)ulPduDataLen,
                                   aucPduData);


    }


    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessReserveSrIdNtf_MainCtrl
 功能描述  : 处理APS通知刷新SR_ID
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月15日
    作    者   : h00246512
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessReserveSrIdNtf_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_XCC_RESERVE_SR_ID_NTF_STRU     *pstSrIdNtf = VOS_NULL_PTR;

    pstSrIdNtf = (APS_XCC_RESERVE_SR_ID_NTF_STRU*)pstMsg;

    CNAS_XCC_UpdateSrIdUsed(pstSrIdNtf->enSo,
                            pstSrIdNtf->ucSrId,
                            CNAS_XCC_INVAILD_CON_ID);


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXCallStateInd_MainCtrl
 功能描述  : call state  状态信息改变时候上报
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月22日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXCallStateInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucVoicceCallState;
    VOS_UINT8                           ucPsCallState;
    VOS_UINT8                           ucSmsCallState;
    VOS_UINT8                           ucCurrCallState;

    ucVoicceCallState = CNAS_CCB_Get1xVoiceCallState();
    ucPsCallState     = CNAS_CCB_Get1xPsCallState();
    ucSmsCallState    = CNAS_CCB_Get1xSmsCallState();

    if ((CNAS_CCB_1X_CALL_STATE_BUTT != ucVoicceCallState)
    && (CNAS_CCB_1X_CALL_STATE_IDLE!= ucVoicceCallState))
    {
        ucCurrCallState = CNAS_XCC_Convert1XcallState(ucVoicceCallState);
    }
    else if ((CNAS_CCB_1X_CALL_STATE_ORIG_CALL == ucPsCallState)
          || (CNAS_CCB_1X_CALL_STATE_ORIG_CALL == ucSmsCallState))
    {
        ucCurrCallState = XCC_MMA_1X_CALL_STATE_ORIG_CALL;
    }
    else if ((CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL == ucPsCallState)
          || (CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL == ucSmsCallState))
    {
        ucCurrCallState = XCC_MMA_1X_CALL_STATE_INCOMMING_CALL;
    }
    else if ((CNAS_CCB_1X_CALL_STATE_CONVERSATION == ucPsCallState)
          || (CNAS_CCB_1X_CALL_STATE_CONVERSATION == ucSmsCallState))
    {
        ucCurrCallState = XCC_MMA_1X_CALL_STATE_CONVERSATION;
    }
    else
    {
        ucCurrCallState = XCC_MMA_1X_CALL_STATE_IDLE;
    }
    CNAS_XCC_SndMma1XCallState(ucCurrCallState);

    return VOS_TRUE;
}




VOS_VOID CNAS_XCC_ProcessCas1xTchSndBurstDtmfMsgInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU                         *pst1xDschDataInd = VOS_NULL_PTR;
    CNAS_XCC_SEND_BURST_DTMF_STRU                           stSndBurstDtmfMsg;
    CNAS_XCC_CTX_STRU                                      *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;
    VOS_UINT8                                               ucCallId;
    CNAS_XCC_DECODE_RESULT_ENUM_UINT8                       enDecodeRslt;
    CNAS_XCC_REV_MS_REJECT_ORDQ_ENUM_UINT8                  enRejOrdq;

    pst1xDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU*)pstMsg;

    NAS_MEM_SET_S(&stSndBurstDtmfMsg, sizeof(CNAS_XCC_SEND_BURST_DTMF_STRU), 0x00, sizeof(CNAS_XCC_SEND_BURST_DTMF_STRU));

    /* Decode the CAS DSCH Data Ind message */
    enDecodeRslt = CNAS_XCC_DecodeSndBurstDtmfMsg(pst1xDschDataInd, &stSndBurstDtmfMsg);

    if (CNAS_XCC_DECODE_RSLT_SUCCESS != enDecodeRslt)
    {
        /* If the decode process is not success, then XCC sends Message Reject Order to CAS */
        if (CNAS_XCC_DECODE_RSLT_INVALID_FIELD == enDecodeRslt)
        {
            enRejOrdq = CNAS_XCC_REV_ORDER_MS_REJECT_FIELD;
        }
        else
        {
            enRejOrdq = CNAS_XCC_REV_ORDER_MS_REJECT_STRUCT;
        }

        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stSndBurstDtmfMsg.ucConRef, enRejOrdq);

        return;
    }

    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByCallRef(stSndBurstDtmfMsg.ucConRef, &ucIndex))
    {
        /* If the Call Instance cannot be found from the input Con_Ref, XCC will send Message Reject Order to CAS */
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stSndBurstDtmfMsg.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_NO_CC_INST);

        return;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if ((CNAS_XCC_FSM_L1_MAIN != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
     || (CNAS_XCC_L1_STA_CONVERSATION != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        /* If the Current FSM is not L1 Main Or the current FSM state is not Conversation, then XCC sends Message Reject Order
        to CAS */
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stSndBurstDtmfMsg.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_STATE);

        return;
    }

    ucCallId = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId;

    /* XCC sends BURST DTMF Request to XCALL */
    CNAS_XCC_SndXcallBurstDtmfInd(ucCallId, &stSndBurstDtmfMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXcallSendContDTMFReq_MainCtrl
 功能描述  : 处理ID_XCALL_XCC_SEND_CONT_DTMF_REQ消息，或返回失败，或向CAS发送消息
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月25日
    作    者   : l00324781
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallSendContDTMFReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    XCALL_XCC_SEND_CONT_DTMF_REQ_STRU  *pstXcallContDTMFReq = VOS_NULL_PTR;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXcallContDTMFReq = (XCALL_XCC_SEND_CONT_DTMF_REQ_STRU *)pstMsg;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* 获取实例，获取失败表示异常，向XCALL响应失败 */
    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByCallId(pstXcallContDTMFReq->ucCallId, &ucIndex))
    {
        CNAS_XCC_SndXcallSendContDTMFCnf(pstXcallContDTMFReq->ucCallId, TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE);

        return VOS_TRUE;
    }

    /* 判断voice call的实例状态是否为Conversation，目前只支持在conversation态处理Cont DTMF Tone Order */
    if ((CNAS_XCC_FSM_L1_MAIN != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
       || (CNAS_XCC_L1_STA_CONVERSATION != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        CNAS_XCC_SndXcallSendContDTMFCnf(pstXcallContDTMFReq->ucCallId, TAF_XCC_CAUSE_ABNORMAL_STATE);

        return VOS_TRUE;
    }

    /* 给CAS发送ID_CNAS_CAS_1X_DSCH_DATA_REQ(CONT DTMF Tone Order) */
    if (VOS_OK != CNAS_XCC_SndContDTMFToneOrder_MainCtrl(ucIndex, pstXcallContDTMFReq))
    {
        CNAS_XCC_SndXcallSendContDTMFCnf(pstXcallContDTMFReq->ucCallId, TAF_XCC_CAUSE_ENCODE_FAIL);

        return VOS_TRUE;
    }

    /* 置位等待ACK的标记 */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait = VOS_TRUE;

    /* 启动TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK */
    CNAS_XCC_StartTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                        TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK,
                        TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_SndContDTMFToneOrder_MainCtrl
 功能描述  : XCC发送Send Cont DTMF Tone Order
 输入参数  : ucIndex               -- voice call实例索引
             pstXcallContDTMFReq  --  Cont DTMF请求消息指针
 输出参数  : 无
 返 回 值  : VOS_OK                --  消息发送成功
             VOS_ERR               --  消息发送失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月24日
    作    者   : l00324781
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_SndContDTMFToneOrder_MainCtrl(
    VOS_UINT8                           ucIndex,
    XCALL_XCC_SEND_CONT_DTMF_REQ_STRU  *pstXcallContDTMFReq
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucContDtmfSeqNum;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;
    CNAS_XCC_TX_ORDER_TYPE_ENUM_UINT8   enOrderType;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    ulPduDataLen = 0;
    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

    /* 需要发送Send Cont DTMF Tone Order，先完成编码 */
    if (VOS_OK != CNAS_XCC_EncodeSendContDTMFToneOrder(pstXcallContDTMFReq,
                                                       aucPduData,
                                                       &ulPduDataLen,
                                                       ucIndex))
    {
        return VOS_ERR;
    }

    /* 分配SEQ NUM */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucContDtmfSeqNum = CNAS_XCC_AllocSeqNum();
    ucContDtmfSeqNum = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucContDtmfSeqNum;

    /* Cont DTMF Tone Order 分为Start 和 Stop */
    if (XCALL_XCC_CONT_DTMF_STOP == pstXcallContDTMFReq->enSwitch)
    {
        enOrderType = CNAS_XCC_TX_ORDER_TYPE_CONTINUOUS_DTMF_TONE_STOP_ORDER;
    }
    else
    {
        enOrderType = CNAS_XCC_TX_ORDER_TYPE_CONTINUOUS_DTMF_TONE_START_ORDER;
    }

    /* 发送Send Cont DTMF Tone Order */
    CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, enOrderType,
                               ucContDtmfSeqNum, (VOS_UINT16)ulPduDataLen, aucPduData);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessContDTMFToneOrderL2Ack_MainCtrl
 功能描述  : 处理Cont DTMF Tone Order的L2 ACK
 输入参数  : ucIndex           -- 消息类型+PID
             pst1xDschDataCnf  -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  对应Cont DTMF Tone Order的L2 ACK
             VOS_FALSE --  非Cont DTMF Tone Order的L2 ACK，或当前并不在等待Cont DTMF Tone Order的状态

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月25日
    作    者   : l00324781
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessContDTMFToneOrderL2Ack_MainCtrl(
    VOS_UINT8                           ucIndex,
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* 判断voice call的实例是否在等待Cont DTMF Tone Order的L2 ACK */
    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait)
    {
        return VOS_FALSE;
    }

    /* 判断seqNum是否一致 */
    if (pst1xDschDataCnf->ucMsgSeqNum != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucContDtmfSeqNum)
    {
        return VOS_FALSE;
    }

    /* 清除等待ACK的标记 */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait = VOS_FALSE;

    /* 停止TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK);

    /* 检查L2 Ack返回结果 */
    if(CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pst1xDschDataCnf->enRslt)
    {
        enCause = TAF_XCC_CAUSE_SUCCESS;
    }
    else
    {
        enCause = TAF_XCC_CAUSE_L2_ACK_FAIL;
    }

    CNAS_XCC_SndXcallSendContDTMFCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId, enCause);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiProtectContDTMFCnfL2Ack_MainCtrl
 功能描述  : 处理TI_CNAS_XCC_WAIT_Cont_DTMF_CNF_L2_ACK定时器超时
 输入参数  : ulEventType -- 消息类型+PID
             pMsg        -- 消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE --  消息都不需要进状态机处理，故该函数返回值都为VOS_TRUE

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月25日
    作    者   : l00324781
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiProtectContDTMFCnfL2Ack_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    /* 获取voice call的实例index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* 判断voice call的实例是否在等待Cont DTMF Tone Order的L2 ACK */
    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait)
    {
        return VOS_TRUE;
    }

    /* 清除等待ACK的标记 */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait = VOS_FALSE;

    CNAS_XCC_SndXcallSendContDTMFCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                      TAF_XCC_CAUSE_L2_ACK_TIME_OUT);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder
 功能描述  : 在Send Cont DTMF Tone Order流程中等待L2 ACK状态下，处理电话挂断(主动挂断或网络挂断)
 输入参数  : ucIndex
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月27日
    作    者   : L00324781
    修改内容   : Iter 16 增加

*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait)
    {
        return;
    }

    /* 清除等待ACK的标记 */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait = VOS_FALSE;

    /* 停止TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK);

    CNAS_XCC_SndXcallSendContDTMFCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                      TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE);

    return;
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXcallEccServiceReq_MainCtrl
 功能描述  : 预处理ID_XCALL_XCC_ECC_SERVICE_REQ
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : l00359089
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallEccServiceReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    /* 获取voice call的实例index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        CNAS_XCC_SndXcallEccServiceCnf(XCC_XCALL_ECC_SERVICE_RESULT_FAIL);
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* 判断voice call的实例状态 ,如果处在 CNAS_XCC_L1_STA_ENDING状态, 直接给XCALL 回复失败*/
    if ((CNAS_XCC_FSM_L1_MAIN == pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
     && (CNAS_XCC_L1_STA_ENDING == pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        CNAS_XCC_SndXcallEccServiceCnf(XCC_XCALL_ECC_SERVICE_RESULT_FAIL);
        return VOS_TRUE;
    }

    /*其它状态，给CAS 下发业务请求*/
    CNAS_XCC_SndCasEccServiceReq();
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessCas1xEccServiceCnf_MainCtrl
 功能描述  : 预处理ID_CAS_CNAS_1X_ECC_SERVICE_CNF
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : l00359089
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xEccServiceCnf_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    CNAS_XCC_CTX_STRU                                      *pstXccCtxAddr = VOS_NULL_PTR;
    CAS_CNAS_1X_ECC_SERVICE_CNF_STRU                       *pstEccServiceCnf = VOS_NULL_PTR;
    XCC_XCALL_ECC_SERVICE_RESULT_ENUM_UINT8                 enRslt;

    pstEccServiceCnf = (CAS_CNAS_1X_ECC_SERVICE_CNF_STRU *)pstMsg;
    enRslt = XCC_XCALL_ECC_SERVICE_RESULT_SUCC;

    /* 获取voice call的实例index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* 判断voice call的实例状态 ,如果处在 CNAS_XCC_L1_STA_ENDING状态, 不予处理*/
    if ((CNAS_XCC_FSM_L1_MAIN == pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
     && (CNAS_XCC_L1_STA_ENDING == pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        return VOS_TRUE;
    }

    /*其它状态，给XCALL回复*/
    if (CAS_CNAS_1X_ECC_SERVICE_RESULT_SUCC != pstEccServiceCnf->enRslt)
    {
        enRslt = XCC_XCALL_ECC_SERVICE_RESULT_FAIL;
    }

    CNAS_XCC_SndXcallEccServiceCnf(enRslt);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessCas1xTchAssignCmplInd_MainCtrl
 功能描述  : 预处理ID_CAS_CNAS_1X_TCH_ASSIGN_CMPL_IND
 输入参数  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_TRUE  --  消息不需要进一步处理
             VOS_FALSE --  消息需要后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月23日
    作    者   : l00359089
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xTchAssignCmplInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    /* 获取voice call的实例index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* 判断voice call的实例状态 ,如果处在 CNAS_XCC_L1_STA_ENDING状态, 不予处理*/
    if ((CNAS_XCC_FSM_L1_MAIN == pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
     && (CNAS_XCC_L1_STA_ENDING == pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        return VOS_TRUE;
    }

    /*其它状态，给XCALL上报TCH 建立消息*/
    CNAS_XCC_SndXcallTchAssignCmplInd();
    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXcallPrivacyModeQryReq_MainCtrl
 功能描述  : 查询当前privacy mode设置

 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 允许发送
             VOS_FALSE -- 不允许发送

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallPrivacyModeSetReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCALL_XCC_PRIVACY_MODE_SET_REQ_STRU                    *pstPrivacyModeSetReq = VOS_NULL_PTR;
    CNAS_XCC_CALL_NVIM_CFG_STRU                            *pstCallNvimCfg       = VOS_NULL_PTR;
    XCC_XCALL_RESULT_ENUM_UINT32                            enResult;

    enResult             = XCC_XCALL_RESULT_SUCC;

    pstPrivacyModeSetReq = (XCALL_XCC_PRIVACY_MODE_SET_REQ_STRU *)pstMsg;

    pstCallNvimCfg = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

    /* 如果privacy mode发送变更，需要写NV */
    if (pstCallNvimCfg->ucPrivacyMode != (VOS_UINT8)pstPrivacyModeSetReq->enPrivacyMode)
    {
        if (VOS_FALSE == CNAS_XCC_WritePrivacyModeNvim((VOS_UINT8)pstPrivacyModeSetReq->enPrivacyMode))
        {
            /* 如果写失败，返回操作失败，不更新本地的全局变量 */
            enResult = XCC_XCALL_RESULT_FAIL;
        }
    }

    /* 如果写NV成功，对当前的voice呼叫进行处理，检查是否需要更改privacy mode */
    if (XCC_XCALL_RESULT_SUCC == enResult)
    {
        pstCallNvimCfg->ucPrivacyMode = (VOS_UINT8)pstPrivacyModeSetReq->enPrivacyMode;

        /* 检查是否需要通知接入层，变更当前语音呼叫的privacy mode */
        if (VOS_TRUE == CNAS_XCC_IsPrivacyModeAllowedToSend_MainCtrl(pstPrivacyModeSetReq->enPrivacyMode))
        {
            /* 通知CAS privacy mode发生变更 */
            CNAS_XCC_SndCasLongCodeTransitionNtf(pstCallNvimCfg->ucPrivacyMode);
        }
    }

    CNAS_XCC_SndXcallPrivacyModeSetCnf(enResult,
                                       pstPrivacyModeSetReq->ulModuleId,
                                       pstPrivacyModeSetReq->usClientId,
                                       pstPrivacyModeSetReq->usOpId);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXcallPrivacyModeQryReq_MainCtrl
 功能描述  : 查询当前privacy mode设置

 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 允许发送
             VOS_FALSE -- 不允许发送

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallPrivacyModeQryReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCALL_XCC_PRIVACY_MODE_QRY_REQ_STRU                    *pstPrivacyModeQryReq = VOS_NULL_PTR;
    CNAS_XCC_CALL_NVIM_CFG_STRU                            *pstCallNvimCfg       = VOS_NULL_PTR;

    pstPrivacyModeQryReq = (XCALL_XCC_PRIVACY_MODE_QRY_REQ_STRU *)pstMsg;

    pstCallNvimCfg      = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

    CNAS_XCC_SndXcallPrivacyModeQryCnf((XCALL_XCC_PRIVACY_MODE_ENUM_UINT8)pstCallNvimCfg->ucPrivacyMode,
                                       pstPrivacyModeQryReq->ulModuleId,
                                       pstPrivacyModeQryReq->usClientId,
                                       pstPrivacyModeQryReq->usOpId);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcessXcallLongCodeTransitionInd_MainCtrl
 功能描述  : 收到CAS上报的privacy mode指示

 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 允许发送
             VOS_FALSE -- 不允许发送

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月23日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallLongCodeTransitionInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_LONG_CODE_TRANSITION_IND_STRU              *pstLongCodeTransInd = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfoCtx      = VOS_NULL_PTR;
    CNAS_XCC_CALL_NVIM_CFG_STRU                            *pstCallNvimCfg       = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                       enServiceType;
    VOS_UINT8                                               ucIndex;

    pstLongCodeTransInd = (CAS_CNAS_1X_LONG_CODE_TRANSITION_IND_STRU *)pstMsg;

    /* 如果CONNECT ID无效，则不处理该消息 */
    if (VOS_FALSE == CNAS_XCC_GetCallInstanceIndexByConnId(pstLongCodeTransInd->ucConnectId, &ucIndex))
    {
        return VOS_TRUE;
    }

    pstCallInfoCtx = &(CNAS_XCC_GetCtxAddr()->astFsmEntity[ucIndex].stCallInfoCtx);

    enServiceType = CNAS_XCC_SERVICE_TYPE_BUTT;
    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* 如果不是语音呼叫，不处理该消息 */
    if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL != enServiceType)
    {
        return VOS_TRUE;
    }

    /* 如果privacy mode发生了变更，则更新呼叫信息中协商的privacy mode，同时通知XCALL模块 */
    if (pstLongCodeTransInd->enUsePrivateLongCodeFlag != pstCallInfoCtx->enNegPrivacyMode)
    {
        pstCallNvimCfg                   = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

        /* 更新协商后的privacy mode */
        pstCallInfoCtx->enNegPrivacyMode = pstLongCodeTransInd->enUsePrivateLongCodeFlag;

        CNAS_XCC_SndXcallPrivacyModeInd(pstCallNvimCfg->ucPrivacyMode,
                                        pstCallInfoCtx->enNegPrivacyMode,
                                        pstCallInfoCtx->ucCallId);
    }

    return VOS_TRUE;
}

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


