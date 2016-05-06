/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmPreProcTbl.c
  版 本 号   : 初稿
  作    者   : s00217060
  生成日期   : 2013年12月14日
  最近修改   :
  功能描述   : SPM模块预处理状态表
  函数列表   :
  修改历史   :
  1.日    期   : 2013年12月14日
    作    者   : s00217060
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "TafFsm.h"
#include "MnCallApi.h"
#include "TafSpmPreProcTbl.h"
#include "TafSpmPreProcAct.h"
#include "NasStkInterface.h"
#include "MnComm.h"
#include "TafSpmTimerMgmt.h"
#include "TafSpmSndInternalMsg.h"
#include "TafSpmFsmMainTbl.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "CallImsaInterface.h"
#include "SpmImsaInterface.h"
#include "ImsaInterface.h"
#endif

#include "TafMmaInterface.h"
#include "TafInternalInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_PREPROC_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 预处理状态机 */
TAF_FSM_DESC_STRU                       g_stTafSpmPreFsmDesc;

/*****************************************************************************
  3 类型定义
*****************************************************************************/


/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_IMS)
TAF_SPM_PROC_IMSA_CALL_MSG_STRU g_astTafSpmProcImsaCallMsgTbl[]=
{
    /* ID_IMSA_SPM_CALL_MSG消息中不同的EventType对应的处理函数 */
    {MN_CALL_EVT_CALL_ORIG_CNF,         TAF_SPM_RcvImsaCallOrigCnf_PreProc     },
    {MN_CALL_EVT_ORIG,                  TAF_SPM_RcvImsaCallOrig_PreProc        },
    {MN_CALL_EVT_CALL_PROC,             TAF_SPM_RcvImsaCallProc_PreProc        },
    {MN_CALL_EVT_ALERTING,              TAF_SPM_RcvImsaCallAlerting_PreProc    },
    {MN_CALL_EVT_CONNECT,               TAF_SPM_RcvImsaCallConnect_PreProc     },
    {MN_CALL_EVT_SUPS_CMD_CNF,          TAF_SPM_RcvImsaCallSupsCmdCnf_PreProc  },
    {MN_CALL_EVT_RELEASED,              TAF_SPM_RcvImsaCallRelease_PreProc     },
    {MN_CALL_EVT_INCOMING,              TAF_SPM_RcvImsaCallIncoming_PreProc    },
    {MN_CALL_EVT_SS_CMD_RSLT,           TAF_SPM_RcvImsaCallSsCmdRslt_PreProc   },
    {MN_CALL_EVT_SS_NOTIFY,             TAF_SPM_RcvImsaCallSsNotify_PreProc    },
    {MN_CALL_EVT_ALL_RELEASED,          TAF_SPM_RcvImsaCallAllRelease_PreProc  },
    {MN_CALL_EVT_HOLD,                  TAF_SPM_RcvImsaCallHold_PreProc        },
    {MN_CALL_EVT_RETRIEVE,              TAF_SPM_RcvImsaCallRetrieve_PreProc    },
};

#endif


/*新增状态动作处理表 */

/* 不进状态机处理的消息 动作表 */
TAF_ACT_STRU        g_astTafSpmPreProcessActTbl[]   =
{

    /* AT CALL message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_ORIG_REQ,
                      TAF_SPM_RcvAppOrigReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_SUPS_CMD_REQ,
                      TAF_SPM_RcvAppSupsCmdReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_GET_INFO_REQ,
                      TAF_SPM_RcvAppGetInfoReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_START_DTMF_REQ,
                      TAF_SPM_RcvAppStartDtmfReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_STOP_DTMF_REQ,
                      TAF_SPM_RcvAppStopDtmfReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_GET_CDUR_REQ,
                      TAF_SPM_RcvAppGetCdurReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      ID_TAFAGENT_MN_GET_CALL_INFO_REQ,
                      TAF_SPM_RcvAppGetCallInfoReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_CLPR_GET_REQ,
                      TAF_SPM_RcvAppGetClprReq_PreProc ),

    /* AT SMS message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT,
                      TAF_SPM_RcvAppSendRpdataDirect_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM,
                      TAF_SPM_RcvAppSendRpdataDirect_PreProc ),

    /* AT SS message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_PROCESS_USS_MSG,
                      TAF_SPM_RcvProcUssSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_REGISTERSS_MSG,
                      TAF_SPM_RcvRegisterSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ERASESS_MSG,
                      TAF_SPM_RcvEraseSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ACTIVATESS_MSG,
                      TAF_SPM_RcvActivateSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_DEACTIVATESS_MSG,
                      TAF_SPM_RcvDeactivateSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_INTERROGATESS_MSG,
                      TAF_SPM_RcvInterrogateSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_REGPWD_MSG,
                      TAF_SPM_RcvRegPwdSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_ERASECCENTRY_MSG,
                      TAF_SPM_RcvEraseCCentrySsReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_RLEASE_MSG,
                      TAF_SPM_RcvRleaseSsReq_PreProc ),

    /* STK CALL message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_CALL_CALLORIG_REQ,
                      TAF_SPM_RcvStkOrigReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_CALL_SUPS_CMD_REQ,
                      TAF_SPM_RcvAppSupsCmdReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_CALL_START_DTMF_REQ,
                      TAF_SPM_RcvAppStartDtmfReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_CALL_STOP_DTMF_REQ,
                      TAF_SPM_RcvAppStopDtmfReq_PreProc ),

    /* STK SS message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_REGISTERSS_REQ,
                      TAF_SPM_RcvRegisterSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_ERASESS_REQ,
                      TAF_SPM_RcvEraseSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_ACTIVATESS_REQ,
                      TAF_SPM_RcvActivateSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_DEACTIVATESS_REQ,
                      TAF_SPM_RcvDeactivateSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_INTERROGATESS_REQ,
                      TAF_SPM_RcvInterrogateSsReq_PreProc ),

    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_SS_USSD_REQ,
                      TAF_SPM_RcvProcUssSsReq_PreProc ),


    /* STK SMS message */
    TAF_ACT_TBL_ITEM( MAPS_STK_PID,
                      STK_MSG_SEND_REQ,
                      TAF_SPM_RcvAppSendRpdataDirect_PreProc ),

#if (FEATURE_ON == FEATURE_IMS)
    /* IMSA CALL message */
    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_MSG,
                      TAF_SPM_RcvImsaCallMsg_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_GET_CALL_INFO_CNF,
                      TAF_SPM_RcvImsaGetCallInfoCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CHANNEL_INFO_IND,
                      TAF_SPM_RcvImsaChannelInfoInd_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_GET_CLPR_CNF,
                      TAF_SPM_RcvImsaGetClprCnf_PreProc ),


    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_START_DTMF_CNF,
                      TAF_SPM_RcvImsaCallStartDtmfCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_START_DTMF_RSLT_IND,
                      TAF_SPM_RcvImsaCallStartDtmfRsltInd_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_STOP_DTMF_CNF,
                      TAF_SPM_RcvImsaCallStopDtmfCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_STOP_DTMF_RSLT_IND,
                      TAF_SPM_RcvImsaCallStopDtmfRsltInd_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_CALL_MSG_SYNC_IND,
                      TAF_SPM_RcvImsaCallMsgSyncInd_PreProc ),


    /* IMSA SS message */
    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_SS_MSG,
                      TAF_SPM_RcvImsaSsMsg_PreProc ),


    /* IMS register status notify message */
    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_NORMAL_REG_STATUS_NOTIFY,
                      TAF_SPM_RcvImsaNormalRegStatusNotify_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF,
                      TAF_SPM_RcvImsaCallInviteNewPtptCnf_PreProc ),


    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND,
                      TAF_SPM_RcvImsaCallTypeChangeInfoInd_PreProc ),

    /* TAF INTERNAL message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      TAF_SPM_INTERNAL_DOMAIN_SEL_IND,
                      TAF_SPM_RcvInternalDomainSelInd_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_SPM_SMMA_IND,
                      TAF_SPM_RcvMsgSmmaInd_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_SPM_MSG_REPORT_IND,
                      TAF_SPM_RcvMsgReportInd_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_SPM_MSG_CHECK_RESULT_IND,
                      TAF_SPM_RcvMsgCheckRsltInd_PreProc ),

    /* MMA message */
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY,
                      TAF_SPM_RcvMmaServiceStatusChangeNotify_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY,
                      TAF_SPM_RcvMmaNetworkCapabilityChangeNotify_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_TAF_RAT_CHANGE_NOTIFY,
                      TAF_SPM_RcvMmaRatChangeNotify_PreProc ),

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_TAF_IMS_VOICE_CAP_IND,
                      TAF_SPM_RcvMmaImsVoiceCapInd_PreProc ),
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, end */

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_CALL_MODIFY_REQ,
                      TAF_SPM_RcvAppCallModifyReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      MN_CALL_APP_CALL_ANSWER_REMOTE_MODIFY_REQ,
                      TAF_SPM_RcvAppCallAnswerRemoteModifyReq_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_MODIFY_CNF,
                      TAF_SPM_RcvImsaCallModifyCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF,
                      TAF_SPM_RcvImsaCallAnswerRemoteModifyCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_MODIFY_STATUS_IND,
                      TAF_SPM_RcvImsaCallModifyStatusInd_PreProc ),


    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_CALL_APP_ECONF_DIAL_REQ,
                      TAF_SPM_RcvAppEconfDialReq_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_CALL_APP_GET_ECONF_CALLED_INFO_REQ,
                      TAF_SPM_RcvAppGetEconfInfoReq_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_ECONF_DIAL_CNF,
                      TAF_SPM_RcvImsaEconfDialCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_ECONF_ADD_USERS_CNF,
                      TAF_SPM_RcvImsaEconfAddUsersCnf_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_ECONF_NOTIFY_IND,
                      TAF_SPM_RcvImsaEconfNotifyInd_PreProc ),

    TAF_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF,
                      TAF_SPM_RcvImsaGetEconfInfoCnf_PreProc ),

#endif

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER,
                      TAF_SPM_RcvCcSrvReqProtectTimerExpired_PreProc ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER,
                      TAF_SPM_RcvSmsSrvReqProtectTimerExpired_PreProc ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER,
                      TAF_SPM_RcvSsSrvReqProtectTimerExpired_PreProc ),
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */

#if (FEATURE_ON == FEATURE_ECALL)
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-1, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_TAF_MMA_PHONE_MODE_SET_CNF,
                      TAF_SPM_RcvMmaPhoneModeSetCnf_PreProc ),
    /* Added by s00261364 for V3R360_eCall项目, 2014-4-1, end */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      TAF_CALL_TAF_REL_CALL_CNF,
                      TAF_SPM_RcvTafRelCallCnf_PreProc ),
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, end */


    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-23, begin */
    TAF_ACT_TBL_ITEM( MAPS_PB_PID,
                      SI_PB_EVENT_ECALLQUERY_CNF,
                      TAF_SPM_RcvPbQryECallNumCnf_PreProc),

    TAF_ACT_TBL_ITEM( MAPS_PB_PID,
                      SI_PB_EVENT_ECALLINIT_IND,
                      TAF_SPM_RcvPbECallInitInd_PreProc),

    /* Added by w00176964 for V3R3C60_eCall项目, 2014-4-23, end */

#endif
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_TAF_MMA_SRV_ACQ_CNF,
                      TAF_SPM_RcvMmaSrvAcqCnf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_TAF_POWER_OFF_IND,
                      TAF_SPM_RcvMmaPowerOffInd_PreProc )

};

/* 不进状态机处理的消息 状态表 */
TAF_STA_STRU        g_astTafSpmPreProcessFsmTbl[]   =
{
    TAF_STA_TBL_ITEM( TAF_SPM_MAIN_STA_PREPROC,
                      g_astTafSpmPreProcessActTbl )
};

/*****************************************************************************
 函 数 名  : TAF_SPM_GetPreProcessStaTblSize
 功能描述  : 获取预处理状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:预处理状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月14日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_GetPreProcessStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astTafSpmPreProcessFsmTbl)/sizeof(TAF_STA_STRU));
}


/*****************************************************************************
 函 数 名  : TAF_SPM_GetPreFsmDescAddr
 功能描述  : 获取预处理状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_FSM_DESC_STRU:指向预处理状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月14日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
TAF_FSM_DESC_STRU * TAF_SPM_GetPreFsmDescAddr(VOS_VOID)
{
    return (&g_stTafSpmPreFsmDesc);
}

#if (FEATURE_ON == FEATURE_IMS)

/*****************************************************************************
 函 数 名  : TAF_SPM_GetImsDomainSelMsgTabAddr
 功能描述  : 获取处理ID_IMSA_SPM_CALL_MSG消息的table的首地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回Table表的首地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月30日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_PROC_IMSA_CALL_MSG_STRU *TAF_SPM_GetImsaCallMsgTabAddr(VOS_VOID)
{
    return (&g_astTafSpmProcImsaCallMsgTbl[0]);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetImsaCallMsgTabSize
 功能描述  : 获取SPM处理IMSA消息状态机的大小
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32:预处理状态机的大小
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月14日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 TAF_SPM_GetImsaCallMsgTabSize( VOS_VOID )
{
    return sizeof(g_astTafSpmProcImsaCallMsgTbl)/sizeof(TAF_SPM_PROC_IMSA_CALL_MSG_STRU);
}
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

