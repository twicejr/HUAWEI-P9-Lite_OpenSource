/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CnasXccFsmMain.c
  版 本 号   : 初稿
  作    者   : y00213812
  生成日期   : 2014年07月03日
  功能描述   : XCC L1主状态机
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月03日
    作    者   : y00213812
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CnasXccFsmMain.h"
#include "CnasXccFsmMainTbl.h"
#include "CnasXccSndInternalMsg.h"
#include "CnasMntn.h"
#include "cas_1x_control_main_nas_pif.h"
#include "cas_1x_trchctrl_proc_nas_pif.h"
#include "CnasXccComFunc.h"
#include "CnasXccCtx.h"
#include "CnasXccSndAps.h"
#include "CnasXccSndCas.h"
#include "CnasXccSndXcall.h"
#include "CnasTimerMgmt.h"
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

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_FSM_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvOrigCallReq_L1Main
 功能描述  : 收到ID_XCALL_XCC_ORIG_CALL_REQ消息的处理
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

 2.日    期   : 2015年10月22日
   作    者   : h00313353
   修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigCallReq_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstCallInfo->ucIsEntityActive = VOS_TRUE;

    /* 发送Session保护 */
    CNAS_XCC_SndSessionBeginNtf((CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16)(((XCALL_XCC_ORIG_CALL_REQ_STRU *)pstMsg)->stSoInfo.enSo));

    /* 状态迁移MO CALLING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MO_CALLING);

    /* 启动L2 MO CALLING状态机 */
    CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MO_CALLING);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvOrigDataCallReq_L1Main_Idle
 功能描述  : 收到ID_APS_XCC_ORIG_DATA_CALL_REQ消息的处理
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

  2.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigDataCallReq_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstCallInfo->ucIsEntityActive = VOS_TRUE;

    /* 发送Session保护 */
    CNAS_XCC_SndSessionBeginNtf((CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16)(((APS_XCC_ORIG_DATA_CALL_REQ_STRU *)pstMsg)->enSo));

    /* 状态迁移MO CALLING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MO_CALLING);

    /* 启动L2 MO CALLING状态机 */
    CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MO_CALLING);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvOrigCsmsCallReq_L1Main_Idle
 功能描述  : 收到ID_CSMS_XCC_ORIG_SMS_CALL_REQ消息的处理
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

  2.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigCsmsCallReq_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstCallInfo->ucIsEntityActive = VOS_TRUE;

    /* 发送Session保护 */
    CNAS_XCC_SndSessionBeginNtf((CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16)(((CSMS_XCC_ORIG_SMS_CALL_REQ_STRU *)pstMsg)->enSo));

    /* 状态迁移MO CALLING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MO_CALLING);

    /* 启动L2 MO CALLING状态机 */
    CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MO_CALLING);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvOrigAgpsCallReq_L1Main_Idle
 功能描述  : 收到ID_XPDS_XCC_ORIG_AGPS_CALL_REQ消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月31日
    作    者   : y00314741
    修改内容   : 新生成函数

  2.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigAgpsCallReq_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstCallInfo->ucIsEntityActive = VOS_TRUE;

    /* 发送Session保护 */
    CNAS_XCC_SndSessionBeginNtf((CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16)(((XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU *)pstMsg)->enSo));

    /* 状态迁移MO CALLING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MO_CALLING);

    /* 启动L2 MO CALLING状态机 */
    CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MO_CALLING);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvPagingInd_Idle
 功能描述  : 收到ID_XCALL_XCC_ORIG_CALL_REQ消息的处理
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

  2.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvPagingInd_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfo     = VOS_NULL_PTR;

    /* 发送Session Begin消息 */
    CNAS_XCC_SndSessionBeginNtf(((CAS_CNAS_1X_PAGING_IND_STRU *)pstMsg)->enSo);

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstCallInfo->ucIsEntityActive = VOS_TRUE;

    /* 状态迁移MT CALLING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

    /* 启动L2 MT CALLING状态机 */
    CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvMoCallingRsltCnf_L1Main_MoCalling
 功能描述  : 收到ID_CNAS_XCC_XCC_MO_CALLING_RSLT_CNF消息的处理
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

  2.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS

  3.日    期   : 2015年12月24日
    作    者   : y00245242
    修改内容   : privacy mode特性开发
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvMoCallingRsltCnf_L1Main_MoCalling(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU                  *pstMoCallingRsltCnf = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfo         = VOS_NULL_PTR;
    CNAS_XCC_CALL_NVIM_CFG_STRU                            *pstCallNvimCfg      = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                       enServiceType;

    pstCallInfo         = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstMoCallingRsltCnf = (CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU *)pstMsg;

    /*
     状态机返回为CNAS_XCC_MO_CALLING_RESULT_SUCCESS时，说明电话打通
     状态机返回为CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED时，说明电话已经结束
     状态机返回为CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING时，说明电话正在挂断的过程中
     */
    if ( CNAS_XCC_MO_CALLING_RESULT_SUCCESS == pstMoCallingRsltCnf->enRslt )
    {
        /* 状态迁移 */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_CONVERSATION);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_CONVERSATION,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();

        /* 将SO转换成SERVICE TYPE */
        CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

        /* privacy mode仅呼叫为voice call且当前so协商已经完成 */
        if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
         && (VOS_TRUE                         == pstCallInfo->ucIsSoNegCmplt))
        {
            pstCallNvimCfg = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

             /* 如果当前NV配置模式不等于呼叫请求的privacy mode，需要通知CAS privacy mode发生变更 */
            if (((VOS_UINT8)pstCallInfo->enReqPrivacyMode) != pstCallNvimCfg->ucPrivacyMode)
            {
                pstCallInfo->enReqPrivacyMode = pstCallNvimCfg->ucPrivacyMode;

                /* 通知CAS privacy mode发生变更 */
                CNAS_XCC_SndCasLongCodeTransitionNtf(pstCallNvimCfg->ucPrivacyMode);
            }
        }
    }
    else if ( CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED == pstMoCallingRsltCnf->enRslt )
    {
        pstCallInfo->ucIsEntityActive = VOS_FALSE;

        /* 去除Session保护 */
        CNAS_XCC_SndSessionEndNtf(pstCallInfo->enInitSo);

        CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfo->ucConnectId);

        CNAS_XCC_InitCallInfoCtx(pstCallInfo, CNAS_XCC_INIT_CALLINFO_SCENE_ENDED);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();

        /* 状态迁移 */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_IDLE);
    }
    else if ( CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING == pstMoCallingRsltCnf->enRslt )
    {
        CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfo->ucConnectId);

        CNAS_XCC_InitCallInfoCtx(pstCallInfo, CNAS_XCC_INIT_CALLINFO_SCENE_ENDING);

        /* 状态迁移 */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

        if (CNAS_XCC_MO_CALLING_END_REASON_POWER_DOWN_END == pstMoCallingRsltCnf->enEndReason)
        {
            CNAS_XCC_StartTimer(pstCallInfo->ucConnectId,
                                TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,
                                TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING_LEN);
        }
    }
    else
    {
        /* enRslt is wrong */
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_RcvMoCallingRsltCnf_L1Main_MoCalling: Wrong Rslt",
                          pstMoCallingRsltCnf->enRslt);
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvMtCallingRsltCnf_L1Main_MtCalling
 功能描述  : 收到ID_CNAS_XCC_XCC_MT_CALLING_RSLT_CNF消息的处理
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

  2.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS

  3.日    期   : 2015年12月24日
    作    者   : y00245242
    修改内容   : privacy mode特性开发
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvMtCallingRsltCnf_L1Main_MtCalling(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU                  *pstMtCallingRsltCnf = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfo         = VOS_NULL_PTR;
    CNAS_XCC_CALL_NVIM_CFG_STRU                            *pstCallNvimCfg      = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                       enServiceType;

    pstCallInfo         = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstMtCallingRsltCnf = (CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU *)pstMsg;

    if ( CNAS_XCC_MT_CALLING_RESULT_SUCCESS == pstMtCallingRsltCnf->enRslt )
    {
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_CONVERSATION);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_CONVERSATION,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();

        /* 将SO转换成SERVICE TYPE */
        CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

        /* privacy mode仅呼叫为voice call且当前so协商已经完成 */
        if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
         && (VOS_TRUE                         == pstCallInfo->ucIsSoNegCmplt))
        {
            pstCallNvimCfg = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

            /* 如果当前NV配置模式不等于呼叫请求的privacy mode，需要通知CAS privacy mode发生变更 */
            if (((VOS_UINT8)pstCallInfo->enReqPrivacyMode) != pstCallNvimCfg->ucPrivacyMode)
            {
                pstCallInfo->enReqPrivacyMode = pstCallNvimCfg->ucPrivacyMode;

                /* 通知CAS privacy mode发生变更 */
                CNAS_XCC_SndCasLongCodeTransitionNtf(pstCallNvimCfg->ucPrivacyMode);
            }
        }
    }
    else if ( CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED == pstMtCallingRsltCnf->enRslt )
    {
        pstCallInfo->ucIsEntityActive = VOS_FALSE;

        /* 去除Session保护 */
        CNAS_XCC_SndSessionEndNtf(pstCallInfo->enInitSo);

        CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfo->ucConnectId);

        CNAS_XCC_InitCallInfoCtx(pstCallInfo, CNAS_XCC_INIT_CALLINFO_SCENE_ENDED);

        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_IDLE);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();
    }
    else if ( CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING == pstMtCallingRsltCnf->enRslt )
    {
        CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfo->ucConnectId);

        CNAS_XCC_InitCallInfoCtx(pstCallInfo, CNAS_XCC_INIT_CALLINFO_SCENE_ENDING);

        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

        if (CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END == pstMtCallingRsltCnf->enEndReason)
        {
            CNAS_XCC_StartTimer(pstCallInfo->ucConnectId,
                                TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,
                                TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING_LEN);
        }

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();

    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_RcvMtCallingRsltCnf_L1Main_MtCalling: Wrong Rslt",
                          pstMtCallingRsltCnf->enRslt);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallTerminateInd_L1Main_Conversation
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

  2.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU        *pstCallTerminateInd = VOS_NULL_PTR;

    pstCallTerminateInd = (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU *)pstMsg;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* Session保护 */
    CNAS_XCC_SndSessionEndNtf(pstCallInfoCtx->enInitSo);

    CNAS_XCC_NotifyTafCallDisc_L1Main(pstCallInfoCtx,
                                      CNAS_XCC_ConvertTerminateReasonToTafCause(pstCallTerminateInd->enTerminateReason),
                                      VOS_TRUE);

    /* 将该标记置成VOS_FALSE，表明该实例已不存在 */
    pstCallInfoCtx->ucIsEntityActive = VOS_FALSE;

    CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfoCtx->ucConnectId);

    CNAS_XCC_InitCallInfoCtx(pstCallInfoCtx, CNAS_XCC_INIT_CALLINFO_SCENE_ENDED);

    /* 状态迁移到IDLE */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_IDLE);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallRelInd_L1Main_Conversation
 功能描述  : 收到ID_CAS_CNAS_1X_CALL_REL_IND消息的处理
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
VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32                   enCause;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* cause值暂设为TAF_XCC_CAUSE_NORMAL_RELEASE，待后续接口中增加cause值后，使用消息中的原因值 */
    enCause = TAF_XCC_CAUSE_MS_NORMAL_RELEASE;

    CNAS_XCC_NotifyTafCallDisc_L1Main(pstCallInfoCtx, enCause, VOS_FALSE);

    /* 状态迁移到ENDING*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXcallHandupCallReq_L1Main_Conversation
 功能描述  : 收到ID_XCALL_XCC_HANGUP_CALL_REQ消息的处理
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
VOS_UINT32 CNAS_XCC_RcvXcallHandupCallReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx = VOS_NULL_PTR;
    XCALL_XCC_HANGUP_CALL_REQ_STRU             *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8           enRelReason;

    pstCallInfoCtx   = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)pstMsg;

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* 给AS发送REL REQ，指示呼叫结束 */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 通知XCALL关声码器 */
    if ( VOS_TRUE == pstCallInfoCtx->ucIsCodecOpen )
    {
        CNAS_XCC_SndXcallCodecCloseInd();

        pstCallInfoCtx->ucIsCodecOpen = VOS_FALSE;
    }

    /* 给XCALL模块发送ID_XCC_XCALL_HANGUP_CALL_CNF */
    CNAS_XCC_SndXcallHangUpCallCnf(pstCallInfoCtx->ucCallId);


    /* 状态迁移到ENDING*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvApsHangupDataCallReq_L1Main_Conversation
 功能描述  : 收到ID_APS_XCC_HANGUP_DATA_CALL_REQ消息的处理
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
VOS_UINT32 CNAS_XCC_RcvApsHangupDataCallReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx = VOS_NULL_PTR;
    APS_XCC_HANGUP_DATA_CALL_REQ_STRU          *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8           enRelReason;

    pstCallInfoCtx   = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (APS_XCC_HANGUP_DATA_CALL_REQ_STRU *)pstMsg;

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* 给AS发送REL REQ，指示呼叫结束 */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 给XCALL模块发送ID_XCC_APS_HANGUP_DATA_CALL_CNF */
    CNAS_XCC_SndApsHangupDataCallCnf(pstCallInfoCtx->ucCallId);


    /* 状态迁移到ENDING*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvCsmsEndSmsCallReq_L1Main_Conversation
 功能描述  : 收到ID_CSMS_XCC_END_SMS_CALL_REQ消息的处理
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
VOS_UINT32 CNAS_XCC_RcvCsmsEndSmsCallReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx = VOS_NULL_PTR;
    CSMS_XCC_END_SMS_CALL_REQ_STRU             *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8           enRelReason;

    pstCallInfoCtx   = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (CSMS_XCC_END_SMS_CALL_REQ_STRU *)pstMsg;

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* 给AS发送REL REQ，指示呼叫结束 */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 给XCALL模块发送ID_XCC_APS_HANGUP_DATA_CALL_CNF */
    CNAS_XCC_SndCsmsHangupCallCnf(pstCallInfoCtx->ucCallId);


    /* 状态迁移到ENDING*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXpdsEndAgpsCallReq_L1Main_Conversation
 功能描述  : 收到ID_XPDS_XCC_END_AGPS_CALL_REQ消息的处理
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
VOS_UINT32 CNAS_XCC_RcvXpdsEndAgpsCallReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfo      = VOS_NULL_PTR;
    XPDS_XCC_END_AGPS_CALL_REQ_STRU            *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8           enRelReason;

    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XPDS_XCC_END_AGPS_CALL_REQ_STRU *)pstMsg;

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* 给AS发送REL REQ，指示呼叫结束 */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* 给XPDS模块发送ID_XCC_XPDS_END_AGPS_CALL_CNF */
    CNAS_XCC_SndXpdsEndCallCnf(pstCallInfo->ucCallId);

    /* 状态迁移到ENDING*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAWI_L1Main_Conversation
 功能描述  : 收到AWI消息的处理
 输入参数  : pstDschDataInd
 输出参数  : 无
 返 回 值  : VOS_TRUE   -- 处理成功
             VOS_FALSE  -- 处理失败
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2014年11月12日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAWI_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_AWIM_STRU                 *pstAWIM = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 完成AWI的解码 */
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

    /* 查找解码后的结果中是否有signal这个info record */
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_SIGNAL,
                                                           pstAWIM->ucNumInfoRecs,
                                                           pstAWIM->astInfoRecsData,
                                                           &ucIndex);


    /* 如果SIGNAL不存在，状态需要迁移到WAIT FOR ANSWER */
    if (VOS_TRUE != ulResult)
    {
        /* 状态迁移MT CALLING */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

        /* 启动L2 MT CALLING状态机 */
        CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);

        PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);

        return VOS_TRUE;
    }

    /* 如果 SIGNAL TYPE 为01 OR 10，状态需要迁移到WAIT FOR ANSWER */
    if ( (CNAS_XCC_SIGNAL_TYPE_ISDN_ALERTING == pstAWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stSignal.ucSignalType)
      || (CNAS_XCC_SIGNAL_TYPE_IS_54B_ALERTING == pstAWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stSignal.ucSignalType))
    {
        /* 状态迁移MT CALLING */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

        /* 启动L2 MT CALLING状态机 */
        CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);

        PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);

        return VOS_TRUE;
    }

    /* 消息通过rec ind上报 */
    CNAS_XCC_SndXcallInfoRecInd(pstCallInfo->ucCallId,
                                CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG,
                                (VOS_UINT8 *)pstAWIM);

    PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvEAWI_L1Main_Conversation
 功能描述  : 收到EAWI消息的处理
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2014年11月12日
    作    者   : L00256032
    修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvEAWI_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_EAWIM_STRU                *pstEAWIM = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 完成EAWI的解码 */
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

    /* 查找解码后的结果中是否有singal这个info record */
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_SIGNAL,
                                                           pstEAWIM->ucNumInfoRecs,
                                                           pstEAWIM->astInfoRecsData,
                                                           &ucIndex);


    /* 如果SIGNAL不存在，状态需要迁移到WAIT FOR ANSWER */
    if (VOS_TRUE != ulResult)
    {
        /* 状态迁移MT CALLING */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

        /* 启动L2 MT CALLING状态机 */
        CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);

        PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);

        return VOS_TRUE;
    }

    /* 如果 SIGNAL TYPE 为01 OR 10，状态需要迁移到WAIT FOR ANSWER */
    if ( (CNAS_XCC_SIGNAL_TYPE_ISDN_ALERTING == pstEAWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stSignal.ucSignalType)
      || (CNAS_XCC_SIGNAL_TYPE_IS_54B_ALERTING == pstEAWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stSignal.ucSignalType))
    {
        /* 状态迁移MT CALLING */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

        /* 启动L2 MT CALLING状态机 */
        CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);

        PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);

        return VOS_TRUE;
    }

    /* 消息通过rec ind上报 */
    CNAS_XCC_SndXcallInfoRecInd(pstCallInfo->ucCallId,
                                CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG,
                                (VOS_UINT8 *)pstEAWIM);

    PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsDschDataInd_L1Main_Conversation
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
 2.日    期   : 2014年11月10日
   作    者   : y00307564
   修改内容   : 1X SS Project修改
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd = VOS_NULL_PTR;


    pstDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;

    /*
    If the Call Control instance receives a message from the layer 3Layer 3 which is
    included in the following list and every message field value is within its permissible
    range, the Call Control instance shall process the message as described below and
    in accordance with the message action time (see 2.6.4.1.5).
        1. Alert With Information Message: If the message contains a Signal information
        record with the SIGNAL_TYPE field set to '01' or '10', or if the message does not
        contain a Signal information record, the Call Control instance shall enter the
        Waiting For Mobile Station Answer Substate. The mobile station should alert the
        user in accordance with the Signal information record. If this message does not
        contain a Signal information record, the mobile station should use standard
        alert as defined in 3.7.5.5.
        2. Continuous DTMF Tone Order
        3. Extended Alert With Information Message: If the message contains a Signal
        information record with the SIGNAL_TYPE field set to '01' or '10' or if the
        message does not contain a Signal information record, the Call Control instance
        shall enter the Waiting For Mobile Station Answer Substate. The mobile station
        should alert the user in accordance with the Signal information record. If this
        message does not contain a Signal information record, the mobile station should
        use standard alert as defined in 3.7.5.5.
        4. Flash With Information Message
        5. Extended Flash With Information Message
        6. Maintenance Order: The Call Control instance shall enter the Waiting for Mobile
        Station Answer Substate.
        7. Send Burst DTMF Message:
    If the Call Control instance receives a message that is not included in the above list,
    cannot be processed, or requires a capability which is not supported, the Call
    Control instance shall discard the message and send a message rejected indicationto the layer 3Layer 3, with the reject reason indicated.
    */
    switch (pstDschDataInd->enDschMsgType)
    {
        case CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG:
            CNAS_XCC_RcvAWI_L1Main_Conversation(pstDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG:
            CNAS_XCC_RcvEAWI_L1Main_Conversation(pstDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG:
            CNAS_XCC_RcvFWI_L1Main_Conversation(pstDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG:
            CNAS_XCC_RcvEFWI_L1Main_Conversation(pstDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_ORDER_MSG:
            CNAS_XCC_ProcOrderMsg_L1Main_Conversation(pstDschDataInd);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_RcvAsDschDataInd_L1Main_Conversation: Wrong order msg");
            break;

    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsUpdateCallInfoInd_L1Main_Conversation
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

 2.日    期   : 2015年12月24日
   作    者   : y00245242
   修改内容   : privacy mode特性开发
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx       = VOS_NULL_PTR;
    CAS_CNAS_1X_UPDATE_CALL_INFO_IND_STRU      *pstUpdateCallInfoInd = VOS_NULL_PTR;
    CNAS_XCC_CALL_NVIM_CFG_STRU                *pstCallNvimCfg       = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32           enServiceType;

    pstUpdateCallInfoInd = (CAS_CNAS_1X_UPDATE_CALL_INFO_IND_STRU *)pstMsg;
    pstCallInfoCtx       = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 更新CALL、CON_REF信息 */
    pstCallInfoCtx->ucConRef     = pstUpdateCallInfoInd->ucConRef;
    pstCallInfoCtx->ucIsNullCc   = pstUpdateCallInfoInd->enIsNullCcFlag;
    pstCallInfoCtx->enCurrentSo  = pstUpdateCallInfoInd->enSo;
    CNAS_XCC_UpdateSrIdUsed(pstUpdateCallInfoInd->enSo,
                            pstUpdateCallInfoInd->ucSrId,
                            pstUpdateCallInfoInd->ucConnectId);
    pstCallInfoCtx->ucSrId       = pstUpdateCallInfoInd->ucSrId;

    if ( VOS_TRUE == pstUpdateCallInfoInd->ucQosParaFlag )
    {
        pstCallInfoCtx->bitOpQosInfo       = VOS_TRUE;
        pstCallInfoCtx->ucQosInfoLen       = pstUpdateCallInfoInd->ucQosInfoLen;
        NAS_MEM_CPY_S(pstCallInfoCtx->aucQosInfo, sizeof(pstCallInfoCtx->aucQosInfo), pstUpdateCallInfoInd->aucQosInfo, sizeof(pstCallInfoCtx->aucQosInfo));
    }

    /* 将SO转换成SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* 根据不同SO，给不同模块发送SO协商完成 */
    if ( CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType )
    {
        /* 通知XCALL更新CALL信息 */
        if (VOS_FALSE == pstCallInfoCtx->ucIsCodecOpen)
        {
            CNAS_XCC_SndXcallCodecOpenInd(pstCallInfoCtx);
            pstCallInfoCtx->ucIsCodecOpen = VOS_TRUE;
        }
        else
        {
            CNAS_XCC_SndXcallCodecChangedInd(pstCallInfoCtx);
        }

        pstCallNvimCfg = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

        /* 如果当前NV配置模式不等于呼叫请求的privacy mode，需要通知CAS privacy mode发生变更 */
       if (((VOS_UINT8)pstCallInfoCtx->enReqPrivacyMode) != pstCallNvimCfg->ucPrivacyMode)
       {
           pstCallInfoCtx->enReqPrivacyMode = pstCallNvimCfg->ucPrivacyMode;

           /* 通知CAS privacy mode发生变更 */
           CNAS_XCC_SndCasLongCodeTransitionNtf(pstCallNvimCfg->ucPrivacyMode);
       }
    }

    if ( CNAS_XCC_SERVICE_TYPE_DATA_CALL == enServiceType )
    {
        /* 当前需要考虑SR_ID的维护，因此做成和语音呼叫类似，已经通知APS数据业务建立的情况
             下，后面增加一个刷新的通知 */
        if (VOS_FALSE == pstCallInfoCtx->ucIsDataSrvConn)
        {
            CNAS_XCC_SndApsDataServiceConnectInd(pstCallInfoCtx);
            pstCallInfoCtx->ucIsDataSrvConn= VOS_TRUE;
        }
        else
        {
            CNAS_XCC_SndApsUpdateDataCallInfoInd(pstCallInfoCtx);
        }
    }

    if ( CNAS_XCC_SERVICE_TYPE_SMS == enServiceType )
    {
        CNAS_XCC_SndCsmsServiceConnectInd(pstCallInfoCtx);
    }

    if ( CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType )
    {
        CNAS_XCC_SndXpdsServiceConnectInd(pstCallInfoCtx);
    }

    /* 当前认为接入层上报ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND的时候，接入层已经SO协商完成，因此
        此时SO的协商完成标记置成VOS_TRUE，这里无条件设置一下 */
    pstCallInfoCtx->ucIsSoNegCmplt = VOS_TRUE;

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccPowerDownInd_L1Main_Conversation
 功能描述  : 收到ID_CNAS_XCC_XCC_POWER_DOWN_IND消息的处理
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年9月16日
   作    者   : h00246512
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_L1Main_Conversation(
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

    /* 通知TAF通话结束 */
    CNAS_XCC_NotifyTafCallDisc_L1Main(pstCallInfo, TAF_XCC_CAUSE_POWER_DOWN_IND, VOS_FALSE);

    /* 状态迁移为CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();


    /* 启动关机的保护定时器 */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId,
                        TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,
                        TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccAbortReq_L1Main_Conversation
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
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 根据service type 给TAF发送业务终止指示 */
    CNAS_XCC_NotifyTafCallDisc_L1Main(pstCallInfoCtx, pstAbortReq->enAbortCause, VOS_FALSE);

    /* 通知AS REL_REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* 直接将状态机迁到CNAS_XCC_L1_STA_ENDING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvXccNdssRedialInd_L1Main_Conversation
 功能描述  : 在通话过程中，收到NDSS重拨指示处理
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

  2.日    期   : 2015年1月5日
    作    者   : y00245242
    修改内容   : 修改原因值上报

  3.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccNdssRedialInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 去除Session保护 */
    CNAS_XCC_SndSessionEndNtf(pstCallInfoCtx->enInitSo);

    /* 通知XCALL呼叫重拨指示, 清除呼叫 */
    CNAS_XCC_NotifyTafCallDisc_L1Main(pstCallInfoCtx, TAF_XCC_CAUSE_NDSS_REDIAL_IND, VOS_TRUE);

    /* 将该标记置成VOS_FALSE，表明该实例已不存在 */
    pstCallInfoCtx->ucIsEntityActive = VOS_FALSE;

    CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfoCtx->ucConnectId);

    CNAS_XCC_InitCallInfoCtx(pstCallInfoCtx, CNAS_XCC_INIT_CALLINFO_SCENE_ENDED);

    /* 状态迁移到IDLE */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_IDLE);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsCallTerminateInd_L1Main_Ending
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

  2.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_L1Main_Ending(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32           enServiceType;
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 去除Session保护 */
    CNAS_XCC_SndSessionEndNtf(pstCallInfoCtx->enInitSo);

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_XCC,
                                                                  TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,
                                                                  pstCallInfoCtx->ucConnectId))
    {
        CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING);
    }

    /* 如果是语音呼叫的话，则需要通知APS resume */
    enServiceType = CNAS_XCC_SERVICE_TYPE_BUTT;

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType))
    {
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfoCtx->ucConnectId, enServiceType);
    }

    pstCallInfoCtx->ucIsEntityActive = VOS_FALSE;

    CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfoCtx->ucConnectId);

    CNAS_XCC_InitCallInfoCtx(pstCallInfoCtx, CNAS_XCC_INIT_CALLINFO_SCENE_ENDED);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    /* 状态迁移到IDLE */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_IDLE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvAsDschDataInd_L1Main_Ending
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
VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_L1Main_Ending(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd = VOS_NULL_PTR;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;
    CNAS_XCC_ORDRM_STRU                 stOrdrm;

    pstCallInfo         = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;

    /*
        2.6.10.3 Call Release Substate
    In this substate, the Call Control instance waits for the call to be released.
    While in the Call Release Substate, the Call Control instance shall perform the following:
    If the Call Control instance receives a message from the layer 3Layer 3 which is
    included in the following list and every message field value is within its permissible
    range, the Call Control instance shall process the message as described below and
    in accordance with the message action time (see 2.6.4.1.5).
         1. Alert With Information Message: The Call Control instance shall send an enter
         traffic channel substate indication?to the layer 3Layer 3 and shall enter the
         Waiting for Mobile Station Answer Substate. If this message does not contain a
         Signal information record, the mobile station should use standard alert as
         defined in 3.7.5.5.
         2. Extended Alert With Information Message: The Call Control instance shall send a
         enter traffic channel substate indication?to layer 3Layer 3 and shall enter the
         Waiting for Mobile Station Answer Substate. If this message does not contain a
         Signal information record, the mobile station should use standard alert as
         defined in 3.7.5.5.
    If the Call Control instance receives a message that is not included in the above list,
    cannot be processed, or requires a capability which is not supported, the Call
    Control instance shall discard the message and send a message rejected indicationto the layer 3Layer 3, with the reject reason indicated.
    */

    /* 当前认为这个阶段不再处理空口消息，如果此时还有空口消息，则直接发送REL REQ给CAS */
    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_XCC,TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING, pstCallInfo->ucConnectId))
    {
        CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_POWER_DOWN_RELEASE,
                                  VOS_FALSE);

        return VOS_TRUE;
    }

    if ( (CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG == pstDschDataInd->enDschMsgType)
      || (CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG == pstDschDataInd->enDschMsgType) )
    {
        /* 发送给AS enter traffic channel substate indication */
        CNAS_XCC_NotifyCasEnterTchSubstate();

        /* 状态迁移MT CALLING */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

        /* 启动L2 MT CALLING状态机 */
        CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);
    }
    else if ((CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG == pstDschDataInd->enDschMsgType)
          || (CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG == pstDschDataInd->enDschMsgType)
          || (CAS_CNAS_1X_RX_TCH_ORDER_MSG == pstDschDataInd->enDschMsgType)
          || (CAS_CNAS_1X_RX_TCH_SEND_BURST_DTMF_MSG == pstDschDataInd->enDschMsgType))
    {
        NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

        /* 编码REJ ORDER */
        if (CAS_CNAS_1X_RX_TCH_ORDER_MSG == pstDschDataInd->enDschMsgType)
        {
            CNAS_XCC_DecodeOrderMsg(pstDschDataInd, &stOrdrm);
            stRejInfo.ucRejOrderCode    = stOrdrm.stOrder.ucOrder;
            stRejInfo.ucRejOrdq         = stOrdrm.stOrder.ucOrdq;
        }
        pstCallInfo                 = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
        stRejInfo.ucConRef          = pstCallInfo->ucConRef;
        stRejInfo.enRejRxTchMsgType = pstDschDataInd->enDschMsgType;
        stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
        stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_STATE;
        stRejInfo.ulL3PduBitLen     = 0;
        stRejInfo.pucPdudata        = aucPduData;
        CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

        /* 发送ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER)给AS */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                                0, (VOS_UINT16)stRejInfo.ulL3PduBitLen, aucPduData);
    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_RcvAsDschDataInd_L1Main_Ending: msgtype", pstDschDataInd->enDschMsgType);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiProtectPowerDown_L1Main_Ending
 功能描述  : 收到TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING超时消息的处理
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

  2.日    期   : 2015年10月22日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiProtectPowerDown_L1Main_Ending(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfo   = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                       enServiceType;

    pstCallInfo         = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 去除Session保护 */
    CNAS_XCC_SndSessionEndNtf(pstCallInfo->enInitSo);

    /* 如果是语音呼叫的话，则需要通知APS resume */
    enServiceType = CNAS_XCC_SERVICE_TYPE_BUTT;

    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType))
    {
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);
    }

    CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfo->ucConnectId);

    CNAS_XCC_InitCallInfoCtx(pstCallInfo, CNAS_XCC_INIT_CALLINFO_SCENE_ENDED);

    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_IDLE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvTiProtectPowerDown_L1Main_Ending
 功能描述  : 收到TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING超时消息的处理
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
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_L1Main_Ending(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo   = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* 启动关机的保护定时器 */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId,
                        TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,
                        TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_XCC_NotifyTafCallDisc_L1Main
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
VOS_VOID CNAS_XCC_NotifyTafCallDisc_L1Main(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    VOS_UINT32                          ulIsNeedToResumeAps
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    /* 将SO转换成SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    switch (enServiceType)
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

            if (VOS_TRUE == ulIsNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId,CNAS_XCC_SERVICE_TYPE_VOICE_CALL);
            }

            break;

        case CNAS_XCC_SERVICE_TYPE_DATA_CALL:
            /* 通知APS呼叫结束 */
            CNAS_XCC_SndApsDataCallDiscInd(pstCallInfo, enCause);
            break;

        case CNAS_XCC_SERVICE_TYPE_SMS:
            /* 这个地方貌似缺与SMS接口，接入层直接通知SMS电话挂了 */
            if (VOS_TRUE == ulIsNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId,CNAS_XCC_SERVICE_TYPE_SMS);
            }
            break;
        case CNAS_XCC_SERVICE_TYPE_AGPS_CALL:
            if (VOS_TRUE == ulIsNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_AGPS_CALL);
            }
            break;

        case CNAS_XCC_SERVICE_TYPE_LOOPBACK:
            if (VOS_TRUE == pstCallInfo->ucIsMoCall)
            {
                CNAS_XCC_SndXcallCallDiscInd(pstCallInfo->ucCallId,pstCallInfo->ucConnectId, enCause);
            }

            break;

        default:
            CNAS_XCC_SndXcallCallDiscInd(pstCallInfo->ucCallId,pstCallInfo->ucConnectId, enCause);

            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_NotifyTafCallDisc_L1Main: Wrong Service Type");
            break;
    }

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_ProcOrderMsg_L1Main_Conversation
 功能描述  : 处理空口的Order消息
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 消息指针

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年9月25日
   作    者   : h00246512
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcOrderMsg_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_ORDRM_STRU                 stOrdrm;
    VOS_UINT32                          ulRslt;
    CNAS_XCC_ORDER_TYPE_ENUM_UINT8      enOrderType;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

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

    switch(enOrderType)
    {
        case CNAS_XCC_ORDER_TYPE_MAINTENANCE:
            /* 迁状态到WAIT FOR ANSWER */
            /* 状态迁移MT CALLING */
            CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

            /* 启动L2 MT CALLING状态机 */
            CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);
            break;

        case CNAS_XCC_ORDER_TYPE_SERVICE_OPTION_CONTROL:
            pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
            CNAS_XCC_SndXcallSoCtrlOrderInd(pstCallInfo, (VOS_UINT8)stOrdrm.stOrder.ucOrdq);
            break;

        default:
            CNAS_ERROR_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation Wrong enOrderType", enOrderType);
            break;
    }

    return;

}

/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvFWI_L1Main_Conversation
 功能描述  : 收到FWI消息的处理
 输入参数  : CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月12日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvFWI_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_FWIM_STRU                 *pstFWIM  = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstFWIM = (CNAS_XCC_FWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_FWIM_STRU));
    if (VOS_NULL_PTR == pstFWIM)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "ALLOC FWIM Wrong");

        return VOS_FALSE;
    }
    NAS_MEM_SET_S(pstFWIM, sizeof(CNAS_XCC_FWIM_STRU), 0, sizeof(CNAS_XCC_FWIM_STRU));

    if ((VOS_OK == CNAS_XCC_DecodeFlashWithInformationMsg(pstDschDataInd, pstFWIM))
      && (1 <= pstFWIM->ucNumInfoRecs))
    {
         /* 给XCALL发送ID_XCC_XCALL_INFO_REC_IND */
         CNAS_XCC_SndXcallInfoRecInd(pstCallInfo->ucCallId,
                                     pstDschDataInd->enDschMsgType,
                                    (VOS_UINT8 *)pstFWIM);
    }
    else
    {
        NAS_MEM_SET_S(&stRejInfo, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU), 0x0, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU));

        /* 编码REJ ORDER */
        stRejInfo.ucConRef          = pstCallInfo->ucConRef;
        stRejInfo.enRejRxTchMsgType = pstDschDataInd->enDschMsgType;
        stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
        stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_STRUCT;
        stRejInfo.ulL3PduBitLen     = 0;
        stRejInfo.pucPdudata        = aucPduData;
        CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

        /* 发送ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER)给AS */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                   0, (VOS_UINT16)stRejInfo.ulL3PduBitLen, aucPduData);
    }

    PS_MEM_FREE(UEPS_PID_XCC, pstFWIM);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : CNAS_XCC_RcvEFWI_L1Main_Conversation
 功能描述  : 收到EFWI消息的处理
 输入参数  : CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月12日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvEFWI_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_EFWIM_STRU                *pstEFWIM  = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstEFWIM = (CNAS_XCC_EFWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EFWIM_STRU));
    if (VOS_NULL_PTR == pstEFWIM)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "ALLOC EFWIM Wrong");

        return VOS_FALSE;
    }
    NAS_MEM_SET_S(pstEFWIM, sizeof(CNAS_XCC_EFWIM_STRU), 0, sizeof(CNAS_XCC_EFWIM_STRU));

    if ((VOS_OK == CNAS_XCC_DecodeExtendedFlashWithInformationMsg(pstDschDataInd, pstEFWIM))
       && (pstEFWIM->ucRecNum == pstEFWIM->ucNumInfoRecs))
    {
        /* 给XCALL发送ID_XCC_XCALL_INFO_REC_IND */
        CNAS_XCC_SndXcallInfoRecInd(pstCallInfo->ucCallId,
                                    pstDschDataInd->enDschMsgType,
                                    (VOS_UINT8 *)pstEFWIM);
    }
    else
    {
        NAS_MEM_SET_S(&stRejInfo, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU), 0x0, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU));

        /* 编码REJ ORDER */
        stRejInfo.ucConRef          = pstCallInfo->ucConRef;
        stRejInfo.enRejRxTchMsgType = pstDschDataInd->enDschMsgType;
        stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
        stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_STRUCT;
        stRejInfo.ulL3PduBitLen     = 0;
        stRejInfo.pucPdudata        = aucPduData;
        CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

        /* 发送ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER)给AS */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                   0, (VOS_UINT16)stRejInfo.ulL3PduBitLen, aucPduData);
    }

    PS_MEM_FREE(UEPS_PID_XCC, pstEFWIM);

    return VOS_TRUE;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





