/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmServiceDomainSelProc.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2013年7月11日
  最近修改   :
  功能描述   : TafSpmServiceDomainSelProc.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月11日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "VosPidDef.h"
#include "v_msg.h"
#include "TafLog.h"
#include "TafSpmServiceDomainSelProc.h"
#include "MnMsgApi.h"
#include "AtMnInterface.h"
#if (FEATURE_IMS == FEATURE_ON)
#include "SpmImsaInterface.h"
#endif
#include "TafSpmSndImsa.h"
#include "TafFsm.h"
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
#include "MnCallSendApp.h"
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */
#include "MnCall.h"
#include "TafSdcLib.h"
#include "TafSdcCtx.h"
#include "MnCallReqProc.h"
#include "TafSpmSndInternalMsg.h"
#include "MnErrorCode.h"
#include "Ssa_Define.h"
#include "TafSpmMntn.h"
#include "TafMmaCtx.h"

#include "TafSpmRedial.h"
#include "TafSpmComFunc.h"

#include "TafInternalInterface.h"

#include "TafSpmCtx.h"
#include "TafXCallSndApp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_SERVICE_DOMAIN_SEL_PROC_C

/*lint -save -e958 */

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    TAF_SPM_GET_IMS_DOMAIN_SEL_MSG_TAB_SIZE  (sizeof(g_astTafSpmImsDomainSelMsgTbl)/sizeof(TAF_SPM_PROC_MSG_STRU))

/*****************************************************************************
  3 类型定义
*****************************************************************************/
typedef VOS_UINT32 (*TAF_SPM_PROC_MSG_FUNC)(struct MsgCB *pstMsg);

typedef struct
{
    VOS_UINT32                          ulMsgEvtType;
    TAF_SPM_PROC_MSG_FUNC               pfMsgFun;
} TAF_SPM_PROC_MSG_STRU;
/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/
TAF_SPM_PROC_MSG_STRU g_astTafSpmImsDomainSelMsgTbl[]=
{
    /* AT CALL message */
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  MN_CALL_APP_ORIG_REQ,               TAF_SPM_RcvAppOrigReqBasedOnCsOverIp),
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  MN_CALL_APP_SUPS_CMD_REQ,           TAF_SPM_RcvAppSupsCmdReqBasedOnCsOverIp),
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  MN_CALL_APP_GET_INFO_REQ,           TAF_SPM_RcvAppGetInfoReqBasedOnCsOverIp),
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  MN_CALL_APP_START_DTMF_REQ,         TAF_SPM_RcvAppStartDtmfReqBasedOnCsOverIp),
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  MN_CALL_APP_STOP_DTMF_REQ,          TAF_SPM_RcvAppStopDtmfReqBasedOnCsOverIp),
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  MN_CALL_APP_GET_CDUR_REQ,           TAF_SPM_RcvAppGetCdurReqBasedOnCsOverIp),
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, begin */
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  ID_TAFAGENT_MN_GET_CALL_INFO_REQ,   TAF_SPM_RcvAppGetCallInfoReqBasedOnCsOverIp),
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, end */
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  MN_CALL_APP_CLPR_GET_REQ,           TAF_SPM_RcvAppGetClprReqBasedOnCsOverIp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  MN_CALL_APP_CALL_MODIFY_REQ,        TAF_SPM_RcvAppCallModifyReqBasedOnCsOverIp),
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  MN_CALL_APP_CALL_ANSWER_REMOTE_MODIFY_REQ,  TAF_SPM_RcvAppCallAnswerRemoteModifyReqBasedOnCsOverIp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  TAF_CALL_APP_ECONF_DIAL_REQ,   TAF_SPM_RcvAppEconfDialReqBasedOnCsOverIp),
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  TAF_CALL_APP_GET_ECONF_CALLED_INFO_REQ,      TAF_SPM_RcvAppGetEconfInfoReqBasedOnCsOverIp),

    /*  AT SS message */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, end */
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  TAF_MSG_PROCESS_USS_MSG,            TAF_SPM_RcvProcUssSsReqBasedOnCsOverIp),
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  TAF_MSG_RLEASE_MSG,                 TAF_SPM_RcvRleaseSsReqBasedOnCsOverIp),

    /* AT SMS message */
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT,  TAF_SPM_RcvSendRpdataDirectBasedOnCsOverIp),
    TAF_ACT_TBL_ITEM(WUEPS_PID_AT,  MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM, TAF_SPM_RcvSendRpdataFromMemBasedOnCsOverIp),

    /* STK CALL message */
    TAF_ACT_TBL_ITEM(MAPS_STK_PID,  STK_CALL_CALLORIG_REQ,              TAF_SPM_RcvStkOrigReqBasedOnCsOverIp),
    TAF_ACT_TBL_ITEM(MAPS_STK_PID,  STK_CALL_SUPS_CMD_REQ,              TAF_SPM_RcvStkSupsCmdReqBasedOnCsOverIp),
    TAF_ACT_TBL_ITEM(MAPS_STK_PID,  STK_CALL_START_DTMF_REQ,            TAF_SPM_RcvStkStartDtmfReqBasedOnCsOverIp),
    TAF_ACT_TBL_ITEM(MAPS_STK_PID,  STK_CALL_STOP_DTMF_REQ,             TAF_SPM_RcvStkStopDtmfReqBasedOnCsOverIp),

    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-17, end */
    /* STK SS message */
    TAF_ACT_TBL_ITEM(MAPS_STK_PID,  STK_SS_USSD_REQ,                    TAF_SPM_RcvProcUssSsReqBasedOnCsOverIp),
    TAF_ACT_TBL_ITEM(MAPS_STK_PID,  STK_SS_REGISTERSS_REQ,              TAF_SPM_RcvRegisterSsReqBasedOnCsOverIp),

    /* STK SMS message */
    TAF_ACT_TBL_ITEM(MAPS_STK_PID,  STK_MSG_SEND_REQ,                   TAF_SPM_RcvSendRpdataDirectBasedOnCsOverIp),
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_SPM_GetImsDomainSelMsgTabAddr
 功能描述  : 获取消息处理table的首地址

 输入参数  : 无

 输出参数  : 无
 返 回 值  : 返回Table表的首地址

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月11日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_PROC_MSG_STRU *TAF_SPM_GetImsDomainSelMsgTabAddr(VOS_VOID)
{
    return (&g_astTafSpmImsDomainSelMsgTbl[0]);
}

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/* TAF_SPM_GetCallType删除 */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */



#if ( FEATURE_ON == FEATURE_LTE )
/*****************************************************************************
 函 数 名  : TAF_SPM_ProcEmergencyCallDomainSelectionInCsVoicePreferredOnEutran
 功能描述  : 语音优先域为CS voice preferred下，emergency call在EUTRAN下的域选择
             流程。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月24日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 移IMS注册状态到SDC中
  3.日    期   : 2015年10月10日
    作    者   : c00318887
    修改内容   : DTS2015090705019
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcEmergencyCallDomainSelectionInCsVoicePreferredOnEutran(VOS_VOID)
{
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstLteNwCapInfo = VOS_NULL_PTR;

    pstLteNwCapInfo = TAF_SDC_GetLteNwCapInfo();

    /* select nas signalling if UE support CSFB and LTE network support CSFB preferred */
    if ((TAF_SDC_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == TAF_SDC_GetLteCsSeviceCap())
     && (TAF_SDC_LTE_CS_CAPBILITY_NO_ADDITION_INFO == pstLteNwCapInfo->enLteCsCap))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /*  network support IMS voice */
    if (TAF_SDC_NW_IMS_VOICE_SUPPORTED == pstLteNwCapInfo->enNwImsVoCap)
    {
        /*  IMS is in registered status, select CS over IP */
        if (TAF_SDC_IMS_NORMAL_REG_STATUS_REG == TAF_SDC_GetImsNormalRegStatus())
        {
            return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
        }
        /* select buffer message if IMS is registering */
        else if (TAF_SDC_IMS_NORMAL_REG_STATUS_REGING == TAF_SDC_GetImsNormalRegStatus())
        {
            return TAF_SPM_ProcCcDomainSelectionByProtectTimerLen();
        }
        else
        {
            /* nothing to do */
        }
    }

    return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcEmergencyCallDomainSelectionInImsPsVoicePreferredOnEutran
 功能描述  : 语音优先域为IMS PS voice preferred下，Emergency call在EUTRAN下的域
             选择流程。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月24日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 移IMS注册状态到SDC中
  3.日    期   : 2015年10月10日
    作    者   : c00318887
    修改内容   : DTS2015090705019
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcEmergencyCallDomainSelectionInImsPsVoicePreferredOnEutran(VOS_VOID)
{
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstLteNwCapInfo = VOS_NULL_PTR;

    pstLteNwCapInfo = TAF_SDC_GetLteNwCapInfo();

    /*  IMS is in registered status and network support IMS voice, select
     *  CS over IP
     */
    if ((TAF_SDC_IMS_NORMAL_REG_STATUS_REG     == TAF_SDC_GetImsNormalRegStatus())
     && (TAF_SDC_NW_IMS_VOICE_SUPPORTED == pstLteNwCapInfo->enNwImsVoCap))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
    }

    /* select nas signalling if UE support CSFB and LTE network support CSFB preferred */
    if ((TAF_SDC_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == TAF_SDC_GetLteCsSeviceCap())
     && (TAF_SDC_LTE_CS_CAPBILITY_NO_ADDITION_INFO == pstLteNwCapInfo->enLteCsCap))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /*  network support IMS voice */
    if (TAF_SDC_NW_IMS_VOICE_SUPPORTED == pstLteNwCapInfo->enNwImsVoCap)
    {
         /* select buffer message if IMS is registering */
         if (TAF_SDC_IMS_NORMAL_REG_STATUS_REGING == TAF_SDC_GetImsNormalRegStatus())
         {
             return TAF_SPM_ProcCcDomainSelectionByProtectTimerLen();
         }
    }

    return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_ProcEmergencyCallDomainSelectionInImsPsVoiceOnlyOnEutran
 功能描述  : 语音优先域为IMS PS voice only下，emergency call在EUTRAN下的域选择
             流程。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月24日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 移IMS注册状态到SDC中
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcEmergencyCallDomainSelectionInImsPsVoiceOnlyOnEutran(VOS_VOID)
{
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstLteNwCapInfo = VOS_NULL_PTR;

    pstLteNwCapInfo = TAF_SDC_GetLteNwCapInfo();

    /* network supports IMS vocie */
    if (TAF_SDC_NW_IMS_VOICE_SUPPORTED == pstLteNwCapInfo->enNwImsVoCap)
    {
        /* select CS over IP if IMS is in registered status */
        if (TAF_SDC_IMS_NORMAL_REG_STATUS_REG == TAF_SDC_GetImsNormalRegStatus())
        {
            return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
        }

        /* select buffer message if IMS is registering */
        if (TAF_SDC_IMS_NORMAL_REG_STATUS_REGING == TAF_SDC_GetImsNormalRegStatus())
        {
            return TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE;
        }
    }

    /* service request is failure if IMS voice is not supported by network or IMS is in
     * deregistering or deregistered status.
     */
    return TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcNormalCallDomainSelectionInCsVoicePreferredOnEutran
 功能描述  : 语音优先域为CS voice preferred下，normal call在EUTRAN下的域选择流程。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月09日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月14日
    作    者   : y00245242
    修改内容   : 新生成函数
  3.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 移IMS注册状态到SDC中
  4.日    期   : 2015年10月10日
    作    者   : c00318887
    修改内容   : DTS2015090705019
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcNormalCallDomainSelectionInCsVoicePreferredOnEutran(VOS_VOID)
{
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstLteNwCapInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucRoamSupport;

    pstLteNwCapInfo = TAF_SDC_GetLteNwCapInfo();

    /* PS service is not in normal status, return buffer message */
    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != TAF_SDC_GetPsServiceStatus())
    {
        return TAF_SPM_ProcCcDomainSelectionByProtectTimerLen();
    }

    ucRoamSupport = TAF_SDC_GetRoamingSupportFlag();
    if ((VOS_TRUE  == TAF_SDC_GetRoamFlag())
     && (VOS_FALSE == ucRoamSupport))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* select nas signalling if UE support CSFB and LTE network support CSFB preferred */
    if ((TAF_SDC_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == TAF_SDC_GetLteCsSeviceCap())
     && (TAF_SDC_LTE_CS_CAPBILITY_NO_ADDITION_INFO == pstLteNwCapInfo->enLteCsCap))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /*  network support IMS voice */
    if (TAF_SDC_NW_IMS_VOICE_SUPPORTED == pstLteNwCapInfo->enNwImsVoCap)
    {
        /*  IMS is in registered status, select CS over IP */
        if (TAF_SDC_IMS_NORMAL_REG_STATUS_REG == TAF_SDC_GetImsNormalRegStatus())
        {
            return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
        }
        /* select buffer message if IMS is registering */
        else if (TAF_SDC_IMS_NORMAL_REG_STATUS_REGING == TAF_SDC_GetImsNormalRegStatus())
        {
            return TAF_SPM_ProcCcDomainSelectionByProtectTimerLen();
        }
        else
        {
            /* nothing to do */
        }
    }

    /* check UE's usage setting if IMS voice is not supported by network or IMS is in
     * deregistering or deregistered status. If it is data centric, select nas signalling.
     * Or buffer message is selected.
     */
    if (TAF_SDC_UE_USAGE_DATA_CENTRIC == TAF_SDC_GetUeUsageSetting())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }


    /* 网络CS能力不支持时，需要等注册结果，时间比较长，所以直接走NAS信令提升用户体验 */
    if (TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED == pstLteNwCapInfo->enLteCsCap)
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    return TAF_SPM_ProcCcDomainSelectionByProtectTimerLen();
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcNormalCallDomainSelectionInImsPsVoicePreferredOnEutran
 功能描述  : 语音优先域为IMS PS voice preferred下，normal call在EUTRAN下的域选择流程。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月09日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月14日
    作    者   : y00245242
    修改内容   : 新生成函数
  3.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 移IMS注册状态到SDC中
  4.日    期   : 2015年10月10日
    作    者   : c00318887
    修改内容   : DTS2015090705019
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcNormalCallDomainSelectionInImsPsVoicePreferredOnEutran(VOS_VOID)
{
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstLteNwCapInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucRoamSupport;

    pstLteNwCapInfo = TAF_SDC_GetLteNwCapInfo();

    /* PS service is not in normal status, return buffer message */
    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != TAF_SDC_GetPsServiceStatus())
    {
        return TAF_SPM_ProcCcDomainSelectionByProtectTimerLen();
    }

    ucRoamSupport = TAF_SDC_GetRoamingSupportFlag();
    if ((VOS_TRUE  == TAF_SDC_GetRoamFlag())
     && (VOS_FALSE == ucRoamSupport))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /*  IMS is in registered status and network support IMS voice, select
     *  CS over IP
     */
    if ((TAF_SDC_IMS_NORMAL_REG_STATUS_REG     == TAF_SDC_GetImsNormalRegStatus())
     && (TAF_SDC_NW_IMS_VOICE_SUPPORTED == pstLteNwCapInfo->enNwImsVoCap))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
    }

    /* select nas signalling if UE support CSFB and LTE network support CSFB preferred */
    if ((TAF_SDC_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == TAF_SDC_GetLteCsSeviceCap())
     && (TAF_SDC_LTE_CS_CAPBILITY_NO_ADDITION_INFO == pstLteNwCapInfo->enLteCsCap))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /*  network support IMS voice */
    if (TAF_SDC_NW_IMS_VOICE_SUPPORTED == pstLteNwCapInfo->enNwImsVoCap)
    {
         /* select buffer message if IMS is registering */
         if (TAF_SDC_IMS_NORMAL_REG_STATUS_REGING == TAF_SDC_GetImsNormalRegStatus())
         {
             return TAF_SPM_ProcCcDomainSelectionByProtectTimerLen();
         }
    }

    /* check UE's usage setting if IMS voice is not supported by network or IMS is in
     * deregistering or deregistered status. If it is data centric, select nas signalling.
     * Or buffer message is selected.
     */
    if (TAF_SDC_UE_USAGE_DATA_CENTRIC == TAF_SDC_GetUeUsageSetting())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }


    /* 网络CS能力不支持时，需要等注册结果，时间比较长，所以直接走NAS信令提升用户体验 */
    if (TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED == pstLteNwCapInfo->enLteCsCap)
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    return TAF_SPM_ProcCcDomainSelectionByProtectTimerLen();
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcNormalCallDomainSelectionInImsPsVoiceOnlyOnEutran
 功能描述  : 语音优先域为IMS PS voice only下，normal call在EUTRAN下的域选择流程。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月09日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月14日
    作    者   : y00245242
    修改内容   : 新生成函数
  3.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 移IMS注册状态到SDC中
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcNormalCallDomainSelectionInImsPsVoiceOnlyOnEutran(VOS_VOID)
{
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstLteNwCapInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucRoamSupport;

    pstLteNwCapInfo = TAF_SDC_GetLteNwCapInfo();

    /* PS service is not in normal status, return buffer message */
    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != TAF_SDC_GetPsServiceStatus())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE;
    }

    ucRoamSupport = TAF_SDC_GetRoamingSupportFlag();
    if ((VOS_TRUE  == TAF_SDC_GetRoamFlag())
     && (VOS_FALSE == ucRoamSupport))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;
    }

    /* network supports IMS vocie */
    if (TAF_SDC_NW_IMS_VOICE_SUPPORTED == pstLteNwCapInfo->enNwImsVoCap)
    {
        /* select CS over IP if IMS is in registered status */
        if (TAF_SDC_IMS_NORMAL_REG_STATUS_REG == TAF_SDC_GetImsNormalRegStatus())
        {
            return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
        }

        /* select buffer message if IMS is registering */
        if (TAF_SDC_IMS_NORMAL_REG_STATUS_REGING == TAF_SDC_GetImsNormalRegStatus())
        {
            return TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE;
        }
    }

    /* service request is failure if IMS voice is not supported by network or IMS is in
     * deregistering or deregistered status.
     */
    return TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcNormalCallDomainSelectionOnEutran
 功能描述  : normal call在EUTRAN下的域选择流程。根据语音优先域的不同，做域选择
             流程

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcNormalCallDomainSelectionOnEutran(VOS_VOID)
{
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32                        enVoicePerferred;

    enDomainSelRslt  = TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;

    enVoicePerferred = TAF_SDC_GetVoiceDomain();
    switch (enVoicePerferred)
    {
        /* domain selection in CS voice preferred */
        case TAF_SDC_VOICE_DOMAIN_CS_PREFERRED:
            enDomainSelRslt = TAF_SPM_ProcNormalCallDomainSelectionInCsVoicePreferredOnEutran();
            break;

        /* domain selection in IMS PS voice preferred */
        case TAF_SDC_VOICE_DOMAIN_IMS_PS_PREFERRED:
            enDomainSelRslt = TAF_SPM_ProcNormalCallDomainSelectionInImsPsVoicePreferredOnEutran();
            break;

        /* domain selection in IMS PS voice only */
        case TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY:
            enDomainSelRslt = TAF_SPM_ProcNormalCallDomainSelectionInImsPsVoiceOnlyOnEutran();
            break;

        /* domain selection in CS voice only */
        case TAF_SDC_VOICE_DOMAIN_CS_ONLY:
        default:
            break;
    }

    return (enDomainSelRslt);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcEmergencyCallDomainSelectionOnEutran
 功能描述  : 紧急呼叫在EUTRAN下的域选择流程。当PS业务状态为非normal service或
             UE不支持EMS，或当前网络不支持EMS，选择NAS signalling，否则根据语
             音优先域进行紧急呼叫域选择流程

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月24日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcEmergencyCallDomainSelectionOnEutran(VOS_VOID)
{
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;
    TAF_SDC_NETWORK_CAP_INFO_STRU                          *pstNwCapInfo = VOS_NULL_PTR;
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32                        enVoicePerferred;

    enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;

    pstNwCapInfo = TAF_SDC_GetLteNwCapInfo();

    /* nas signalling is selected if PS service status is not nomal service */
    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != TAF_SDC_GetPsServiceStatus())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* nas signalling is selected if UE or network don't support EMS */
    if ((VOS_FALSE                       == TAF_SDC_GetLteEmsSupportFlag())
     || (TAF_SDC_NW_EMC_BS_NOT_SUPPORTED == pstNwCapInfo->enNwEmcBsCap))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    enVoicePerferred = TAF_SDC_GetVoiceDomain();
    switch (enVoicePerferred)
    {
        /* domain selection in CS voice preferred */
        case TAF_SDC_VOICE_DOMAIN_CS_PREFERRED:
            enDomainSelRslt = TAF_SPM_ProcEmergencyCallDomainSelectionInCsVoicePreferredOnEutran();
            break;

        /* domain selection in IMS PS voice preferred */
        case TAF_SDC_VOICE_DOMAIN_IMS_PS_PREFERRED:
            enDomainSelRslt = TAF_SPM_ProcEmergencyCallDomainSelectionInImsPsVoicePreferredOnEutran();
            break;

        /* domain selection in IMS PS voice only */
        case TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY:
            enDomainSelRslt = TAF_SPM_ProcEmergencyCallDomainSelectionInImsPsVoiceOnlyOnEutran();
            break;

        /* domain selection in CS voice only */
        case TAF_SDC_VOICE_DOMAIN_CS_ONLY:
        default:
            break;
    }

    /* select CS call */
    return (enDomainSelRslt);
}

 #if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : TAF_SPM_ProcEConfDomainSelectionOnEutran
 功能描述  : ECONF在EUTRAN下的域选择流程。根据语音优先域的不同，做域选择
             流程

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcEConfDomainSelectionOnEutran(VOS_VOID)
{
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32                        enVoicePerferred;

    enDomainSelRslt  = TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;

    enVoicePerferred = TAF_SDC_GetVoiceDomain();
    switch (enVoicePerferred)
    {
        /* 只有IMS域的ECONF，如果用户设置了CS域优先，也不选择NAS SIGNALING，按照PS ONLY处理 */
        /* domain selection in CS voice preferred */
        case TAF_SDC_VOICE_DOMAIN_CS_PREFERRED:
        /* domain selection in IMS PS voice preferred */
        case TAF_SDC_VOICE_DOMAIN_IMS_PS_PREFERRED:
        /* domain selection in IMS PS voice only */
        case TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY:
            enDomainSelRslt = TAF_SPM_ProcNormalCallDomainSelectionInImsPsVoiceOnlyOnEutran();
            break;

        /* domain selection in CS voice only */
        case TAF_SDC_VOICE_DOMAIN_CS_ONLY:
        default:
            break;
    }

    return (enDomainSelRslt);
}
#endif

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcCcDomainSelectionOnEutran
 功能描述  : call在EUTRAN下的域选择流程。
             如果UE不支持LTE下IMS功能，返回NAS SIGNALLING, 走CS call，否则check
             本次call的呼叫类型:
                1. 如果是紧急呼，选择EUTRAN下的紧急呼域选择流程；
                2. 如果是video call，且IMS栈支持video call，选择EUTRAN下normal
                   call域选择流程
                3. 其他呼叫类型，暂选择normal call域选择流程


 输入参数  : pstMsg -- 业务请求消息指针
 输出参数  :
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2014年12月24日
    作    者   : f00179208
    修改内容   : 增强型多方通话
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcCcDomainSelectionOnEutran(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain
)
{
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;

    enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;

    if (VOS_FALSE == TAF_SDC_GetLteImsSupportFlag())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    switch (enCallType)
    {
        /* emergency call */
        case MN_CALL_TYPE_EMERGENCY:
            enDomainSelRslt = TAF_SPM_ProcEmergencyCallDomainSelectionOnEutran();
            break;

        /* video call */
        case MN_CALL_TYPE_VIDEO:
        case MN_CALL_TYPE_VIDEO_TX:
        case MN_CALL_TYPE_VIDEO_RX:
            if (TAF_CALL_VOICE_DOMAIN_IMS == enVoiceDomain)
            {
                enDomainSelRslt = TAF_SPM_ProcNormalCallDomainSelectionOnEutran();
            }
            break;

        /* voice call */
        case MN_CALL_TYPE_VOICE:
            /* 如果是增强型会议的发起 */
#if (FEATURE_ON == FEATURE_IMS)
           if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
            {
                enDomainSelRslt = TAF_SPM_ProcEConfDomainSelectionOnEutran();
            }
            else
#endif
            {
                enDomainSelRslt = TAF_SPM_ProcNormalCallDomainSelectionOnEutran();
            }
            break;

        /* if call type is butt, return request fail */
        case MN_CALL_TYPE_BUTT:
            enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;
            break;

        /* other */
        case MN_CALL_TYPE_FAX:
        case MN_CALL_TYPE_CS_DATA:
        default:
            break;
    }

    return enDomainSelRslt;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSsDomainSelectionInCsVoicePreferredOnEutran
 功能描述  : 语音优先域为CS voice preferred下，补充业务在EUTRAN下的域选择流程。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月09日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月14日
    作    者   : y00245242
    修改内容   : 新生成函数
  3.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 移IMS注册状态到SDC中
  4.日    期   : 2015年10月10日
    作    者   : c00318887
    修改内容   : DTS2015090705019
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSsDomainSelectionInCsVoicePreferredOnEutran(VOS_VOID)
{
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstLteNwCapInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucRoamSupport;

    pstLteNwCapInfo = TAF_SDC_GetLteNwCapInfo();

    /* PS service is not in normal status, return buffer message */
    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != TAF_SDC_GetPsServiceStatus())
    {
        return TAF_SPM_ProcSsDomainSelectionByProtectTimerLen();
    }

    ucRoamSupport = TAF_SDC_GetRoamingSupportFlag();
    if ((VOS_TRUE  == TAF_SDC_GetRoamFlag())
     && (VOS_FALSE == ucRoamSupport))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* select nas signalling if UE support CSFB and LTE network support CSFB preferred */
    if ((TAF_SDC_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == TAF_SDC_GetLteCsSeviceCap())
     && (TAF_SDC_LTE_CS_CAPBILITY_NO_ADDITION_INFO == pstLteNwCapInfo->enLteCsCap))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /*  IMS is in registered status, select CS over IP */
    if (TAF_SDC_IMS_NORMAL_REG_STATUS_REG == TAF_SDC_GetImsNormalRegStatus())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
    }

    /* select buffer message if IMS is registering */
    if (TAF_SDC_IMS_NORMAL_REG_STATUS_REGING == TAF_SDC_GetImsNormalRegStatus())
    {
        return TAF_SPM_ProcSsDomainSelectionByProtectTimerLen();
    }

    /* check UE's usage setting if IMS is in deregistering or deregistered status.
     * If it is data centric, select nas signalling. Or buffer message is selected.
     */
    if (TAF_SDC_UE_USAGE_DATA_CENTRIC == TAF_SDC_GetUeUsageSetting())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }


    /* 网络CS能力不支持时，需要等注册结果，时间比较长，所以直接走NAS信令提升用户体验 */
    if (TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED == pstLteNwCapInfo->enLteCsCap)
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    return TAF_SPM_ProcSsDomainSelectionByProtectTimerLen();
}


/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSsDomainSelectionInImsPsVoicePreferredOnEutran
 功能描述  : 语音优先域为IMS PS voice preferred下，补充在EUTRAN下的域选择流程。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月09日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月14日
    作    者   : y00245242
    修改内容   : 新生成函数
  3.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 移IMS注册状态到SDC中
  4.日    期   : 2015年10月10日
    作    者   : c00318887
    修改内容   : DTS2015090705019
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSsDomainSelectionInImsPsVoicePreferredOnEutran(VOS_VOID)
{
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstLteNwCapInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucRoamSupport;

    pstLteNwCapInfo = TAF_SDC_GetLteNwCapInfo();

    /* PS service is not in normal status, return buffer message */
    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != TAF_SDC_GetPsServiceStatus())
    {
        return TAF_SPM_ProcSsDomainSelectionByProtectTimerLen();
    }

    ucRoamSupport = TAF_SDC_GetRoamingSupportFlag();
    if ((VOS_TRUE  == TAF_SDC_GetRoamFlag())
     && (VOS_FALSE == ucRoamSupport))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /*  IMS is in registered status, select CS over IP */
    if (TAF_SDC_IMS_NORMAL_REG_STATUS_REG == TAF_SDC_GetImsNormalRegStatus())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
    }

    /* select nas signalling if UE support CSFB and LTE network support CSFB preferred */
    if ((TAF_SDC_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == TAF_SDC_GetLteCsSeviceCap())
     && (TAF_SDC_LTE_CS_CAPBILITY_NO_ADDITION_INFO == pstLteNwCapInfo->enLteCsCap))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* select buffer message if IMS is registering */
    if (TAF_SDC_IMS_NORMAL_REG_STATUS_REGING == TAF_SDC_GetImsNormalRegStatus())
    {
        return TAF_SPM_ProcSsDomainSelectionByProtectTimerLen();
    }

    /* check UE's usage setting if IMS is in deregistering or deregistered status.
     * If it is data centric, select nas signalling. Or buffer message is selected.
     */
    if (TAF_SDC_UE_USAGE_DATA_CENTRIC == TAF_SDC_GetUeUsageSetting())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }


    /* 网络CS能力不支持时，需要等注册结果，时间比较长，所以直接走NAS信令提升用户体验 */
    if (TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED == pstLteNwCapInfo->enLteCsCap)
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    return TAF_SPM_ProcSsDomainSelectionByProtectTimerLen();
}


/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSsDomainSelectionInImsPsVoiceOnlyOnEutran
 功能描述  : 语音优先域为IMS PS voice only下，补充在EUTRAN下的域选择流程。

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月09日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月14日
    作    者   : y00245242
    修改内容   : 新生成函数
  3.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 移IMS注册状态到SDC中
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSsDomainSelectionInImsPsVoiceOnlyOnEutran(VOS_VOID)
{
    VOS_UINT8                           ucRoamSupport;

    /* PS service is not in normal status, return buffer message */
    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != TAF_SDC_GetPsServiceStatus())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE;
    }

    ucRoamSupport = TAF_SDC_GetRoamingSupportFlag();
    if ((VOS_TRUE  == TAF_SDC_GetRoamFlag())
     && (VOS_FALSE == ucRoamSupport))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;
    }

    /* select CS over IP if IMS is in registered status */
    if (TAF_SDC_IMS_NORMAL_REG_STATUS_REG == TAF_SDC_GetImsNormalRegStatus())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
    }

    /* select buffer message if IMS is registering */
    if (TAF_SDC_IMS_NORMAL_REG_STATUS_REGING == TAF_SDC_GetImsNormalRegStatus())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE;
    }

    /* service request is failure if IMS is in deregistering or deregistered status. */
    return TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSsDomainSelectionOnEutran
 功能描述  : SS请求在EUTRAN下的域选择流程。根据语音优先域不同，做不同的SS业务
             域选择流程

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSsDomainSelectionOnEutran(VOS_VOID)
{
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32                        enVoicePerferred;

    if (VOS_FALSE == TAF_SDC_GetLteImsSupportFlag())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    enVoicePerferred = TAF_SDC_GetVoiceDomain();

    switch (enVoicePerferred)
    {
        /* domain selection in CS voice preferred */
        case TAF_SDC_VOICE_DOMAIN_CS_PREFERRED:
            enDomainSelRslt = TAF_SPM_ProcSsDomainSelectionInCsVoicePreferredOnEutran();
            break;

        /* domain selection in IMS PS voice preferred */
        case TAF_SDC_VOICE_DOMAIN_IMS_PS_PREFERRED:
            enDomainSelRslt = TAF_SPM_ProcSsDomainSelectionInImsPsVoicePreferredOnEutran();
            break;

        /* domain selection in IMS PS voice only */
        case TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY:
            enDomainSelRslt = TAF_SPM_ProcSsDomainSelectionInImsPsVoiceOnlyOnEutran();
            break;

        /* domain selection in CS voice only */
        case TAF_SDC_VOICE_DOMAIN_CS_ONLY:
        default:
            enDomainSelRslt  = TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
            break;
    }

    return (enDomainSelRslt);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSmsDomainSelectionOnEutran
 功能描述  : 驻留在EUTRAN下的SMS域选择流程

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 移IMS注册状态到SDC中
  3.日    期   : 2015年3月9日
    作    者   : s00217060
    修改内容   : DTS2015020209437修改域选顺序
  4.日    期   : 2015年10月10日
    作    者   : c00318887
    修改内容   : DTS2015090705019
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSmsDomainSelectionOnEutran(VOS_VOID)
{
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enImsaRegStatus;
    TAF_SDC_LTE_CS_CAPBILITY_ENUM_UINT8 enLteCsCap;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsServiceStatus;
    VOS_UINT8                           ucRoamSupport;

    enLteCsCap = TAF_SDC_GetLteNwCapInfo()->enLteCsCap;

    /*
       1.驻留在LTE下时，但不支持IMS短信，发送CS/PS短信
       2.驻留在LTE下，支持IMS短信，SMS OVER IP不优先，发送CS/PS短信
       3.驻留在LTE下，支持IMS短信，SMS OVER IP优先，PS不正常服务服务，缓存消息
       4.驻留在LTE下，支持IMS短信，SMS OVER IP优先，IMSA主动上报的消息中ext_info指示IMS不可以使用SMS，发送CS/PS短信
       5.驻留在LTE下，支持IMS短信，SMS OVER IP优先，IMS注册成功，发送IMS短信
       6.驻留在LTE下，支持IMS短信，SMS OVER IP优先，sms over sgs支持，发送CS/PS短信
       7.驻留在LTE下，支持IMS短信，SMS OVER IP优先，IMS正在注册，缓存消息
       8.其他，发送CS/PS短信
    */

    /* LTE下的IMS不支持 */
    if (VOS_FALSE == TAF_SDC_GetLteImsSupportFlag())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* 不支持IMS短信 */
    if (VOS_FALSE == TAF_SDC_GetSmsOnImsSupportFlag())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    enPsServiceStatus = TAF_SDC_GetPsServiceStatus();

    /* SMS OVER IP不优先 */
    if (TAF_SDC_SMS_DOMAIN_PREFER_TO_USE_SMS_OVER_IP != TAF_SDC_GetSmsDomain())
    {
        /* 判断CS业务能力之前，首先确认PS服务状态，否则仅仅判定CS业务能力参数不准确 */
        if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE  == enPsServiceStatus)
         && (TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED == enLteCsCap))
        {
            return TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;
        }

        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* PS域非正常服务 */
    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enPsServiceStatus)
    {

        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcSmsDomainSelectionOnEutran: PS NON NORMAL SERVICE.");

        return TAF_SPM_ProcSmsDomainSelectionByProtectTimerLen();
    }

    ucRoamSupport = TAF_SDC_GetRoamingSupportFlag();
    if ((VOS_TRUE  == TAF_SDC_GetRoamFlag())
     && (VOS_FALSE == ucRoamSupport))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    enImsaRegStatus = TAF_SDC_GetImsNormalRegStatus();

    /* IMSA主动上报的消息中ext_info指示IMS是否可以使用SMS */
    /* 目前没有主动上报，接口先保留，上下文中初始化为支持 */
    if (VOS_FALSE == TAF_SPM_GetImsSmsSupportedOnImsServer())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* if ims reg succ */
    if (TAF_SDC_IMS_NORMAL_REG_STATUS_REG == enImsaRegStatus)
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
    }

    /* if nv config sms over sgs available and nw support sgs sms */
    if (TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED != enLteCsCap)
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* IMS正在注册 */
    if (TAF_SDC_IMS_NORMAL_REG_STATUS_REGING == enImsaRegStatus)
    {
        return TAF_SPM_ProcSmsDomainSelectionByProtectTimerLen();
    }

    /* ims reg fail */
    if (TAF_SDC_IMS_NORMAL_REG_STATUS_DEREG == enImsaRegStatus)
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;
    }

    return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;

}
#endif

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcCcDomainSelectionOnNoRat
 功能描述  : 在无RAT下的SMS域选择流程
             在无RAT下，如果UE不支持任何RAT下的IMS，选择NAS signalling, 目的是
             遵守在IMS不支持下不改变原有的消息流程；

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2015年10月10日
    作    者   : c00318887
    修改内容   : DTS2015090705019
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcCcDomainSelectionOnNoRat(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    if ((VOS_TRUE == TAF_SDC_GetImsSupportFlag())
     && (MN_CALL_TYPE_EMERGENCY != enCallType))
    {
        return TAF_SPM_ProcCcDomainSelectionByProtectTimerLen();
    }

    /* select NAS signalling if UE don't supported IMS on any RAT or call type is emergency */
    return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSmsDomainSelectionOnNoRat
 功能描述  : 在无RAT下的SMS域选择流程。
             在无RAT下，如果UE不支持任何RAT下的IMS，选择NAS signalling, 目的是
             遵守在IMS不支持下不改变原有的消息流程；

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2015年10月10日
    作    者   : c00318887
    修改内容   : DTS2015090705019
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSmsDomainSelectionOnNoRat(VOS_VOID)
{
    if (VOS_TRUE == TAF_SDC_GetImsSupportFlag())
    {
        return TAF_SPM_ProcSmsDomainSelectionByProtectTimerLen();
    }

    /* select NAS signalling if UE don't supported IMS on any RAT */
    return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSsDomainSelectionOnNoRat
 功能描述  : 在无RAT下的SS域选择流程。
             在无RAT下，如果UE不支持任何RAT下的IMS，选择NAS signalling, 目的是
             遵守在IMS不支持下不改变原有的消息流程；

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月23日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2015年10月10日
    作    者   : c00318887
    修改内容   : DTS2015090705019
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSsDomainSelectionOnNoRat(VOS_VOID)
{
    if (VOS_TRUE == TAF_SDC_GetImsSupportFlag())
    {
        return TAF_SPM_ProcSsDomainSelectionByProtectTimerLen();
    }

    /* select NAS signalling if UE don't supported IMS on any RAT */
    return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcCcDomainSelectionByProtectTimerLen
 功能描述  : 根据保护定时器时长，判断是否需要缓存CC服务消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcCcDomainSelectionByProtectTimerLen(VOS_VOID)
{
    if (0 == TAF_Spm_GetBufferCcProtectTimerLen())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    return TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSmsDomainSelectionByProtectTimerLen
 功能描述  : 根据保护定时器时长，判断是否需要缓存SMS服务消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSmsDomainSelectionByProtectTimerLen(VOS_VOID)
{
    if (0 == TAF_SPM_GetBufferSmsProtectTimerLen())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    return TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE;
}
/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSmsDomainSelectionByProtectTimerLen
 功能描述  : 根据保护定时器时长，判断是否需要缓存SS服务消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSsDomainSelectionByProtectTimerLen(VOS_VOID)
{
    if (0 == TAF_SPM_GetBufferSsProtectTimerLen())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    return TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE;
}



/*****************************************************************************
 函 数 名  : TAF_SPM_IsServiceExistedInCcDomainSelection
 功能描述  : 判断在cc域选择处理中，是否存在业务

 输入参数  : ulEventType
 输出参数  : 无
 返 回 值  : VOS_TRUE   存在业务
             VOS_FALSE  不存在业务
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-11-28
    作    者   : n00269697
    修改内容   : 新生成函数for enhanced conference
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsServiceExistedInCcDomainSelection(
    VOS_UINT32                          ulEventType
)
{
    if (ulEventType  != TAF_BuildEventType(WUEPS_PID_AT, MN_CALL_APP_ORIG_REQ)
     && ulEventType  != TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ)
     && ulEventType  != TAF_BuildEventType(MAPS_STK_PID, STK_CALL_CALLORIG_REQ))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcGULCcDomainSelection
 功能描述  : GU CC业务的域选择流程

 输入参数  : ulEventType －－ 请求消息事件类型
             pstMsg －－ 消息指针

 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月14日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
  3.日    期   : 2014年2月17日
    作    者   : y00245242
    修改内容   : DTS2014031105153: 增加IMS域MPTY域选择流程
  4.日    期   : 2014年6月4日
    作    者   : y00245242
    修改内容   : 为eCall特性增加修改
  5.日    期   : 2014年7月2日
    作    者   : s00217060
    修改内容   : DTS2014062805899:CS域SS业务存在时，电话不选择IMS域
  6.日    期   : 2014年11月28日
    作    者   : f00179208
    修改内容   : 增强型多方通话
  7.日    期   : 2015年03月04日
    作    者   : j00174725
    修改内容   : DTS2015021104607
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcGULCcDomainSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;
    MN_CALL_TYPE_ENUM_U8                                    enCallType;
    VOS_UINT8                                               ucImsInvitePtptFlag;
    MN_CALL_APP_REQ_MSG_STRU                               *pstAppMsg       = VOS_NULL_PTR;
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2014-01-03, begin */
    MN_APP_CALL_CALLORIG_REQ_STRU                          *pstStkOrigReq   = VOS_NULL_PTR;

    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8                        enVoiceDomain;

    pstAppMsg       = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;
    pstStkOrigReq   = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstMsg;

    enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;

    ucImsInvitePtptFlag = VOS_FALSE;

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-6-4, begin */
    /* eCall呼叫仅在GU下支持，域选择为NAS信令 */
#if (FEATURE_ON == FEATURE_ECALL)
    enCallType      = pstAppMsg->unParm.stOrig.enCallType;

    if (VOS_TRUE == TAF_SPM_IsEcallAllowedSelNasSignalling(enCallType))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-6-4, end */

    enVoiceDomain   = TAF_CALL_VOICE_DOMAIN_3GPP;

    if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, MN_CALL_APP_ORIG_REQ))
    {
        enCallType          = pstAppMsg->unParm.stOrig.enCallType;

        ucImsInvitePtptFlag = pstAppMsg->unParm.stOrig.ucImsInvitePtptFlag;

        enVoiceDomain       = pstAppMsg->unParm.stOrig.enVoiceDomain;
    }
#if (FEATURE_ON == FEATURE_IMS)
    else if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
    {
        enCallType          = pstAppMsg->unParm.stEconfDial.enCallType;
        ucImsInvitePtptFlag = pstAppMsg->unParm.stEconfDial.ucImsInvitePtptFlag;

        enVoiceDomain       = pstAppMsg->unParm.stEconfDial.enVoiceDomain;
    }
#endif
    else
    {
        enCallType      = pstStkOrigReq->enCallType;
    }
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2014-01-03, end */

    /* 这是IMS邀请第三方加入电话会议呼叫，直接选择IMS域发送
       如果是IMS的增强型会议添加与会者，直接选择IMS域发送 */
    if (VOS_TRUE == ucImsInvitePtptFlag)
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
    }

    /* select NAS signalling if call is running on CS domain*/
    if (VOS_TRUE == TAF_SDC_GetCsCallExistFlg())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* 目前UT布署在A核, AT或STK发起的非USSD的SS业务统一走CS域;
       STK或AT发起的USSD业务需要根据支持IMS USSD NV项是否打开，如果打开，
       经过正常SPM进行域选择，否则走CS域；
       IMS电话或短信业务存在时,收到AT或STK发起的非USSD的SS业务直接回复失败; */

    /* SS业务有可能不用判断IMS域和PS域是否正常服务这些条件，直接选了CS域，
       如果当前有CS域的SS业务存在，语音直接走CS域 */

    if (VOS_TRUE == TAF_SDC_GetCsSsSrvExistFlg())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* call is running on IMS domain and select OVER IP */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        /* 异常保护，如果处于IMS CALL过程中，不允许上层下发视频呼叫 */
        if (TAF_SPM_IS_VIDEO_CALL(enCallType))
        {
            return TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;
        }
        else
        {
            return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
        }
    }

    /* In this case, NAS SIGNALLING is selected */
    /* 异常场景:如MN_CALL_APP_SUPS_CMD_REQ等一般在有业务存在时才下发；如果业务不存在，默认走nas信令 */
    if (VOS_FALSE == TAF_SPM_IsServiceExistedInCcDomainSelection(ulEventType))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, begin */
    /* 呼叫类型和卡状态的判断放到预处理里面来做 */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, end */


    /* check whether voice call on IMS is supported or not */
    if (VOS_FALSE == TAF_SDC_GetVoiceCallOnImsSupportFlag())
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* 取当前驻留的RAT */
    switch (TAF_SDC_GetCampSysMode())
    {
#if (FEATURE_ON == FEATURE_LTE)
        case TAF_SDC_SYS_MODE_LTE:
            enDomainSelRslt = TAF_SPM_ProcCcDomainSelectionOnEutran(ulEventType, pstMsg, enCallType, enVoiceDomain);
            break;
#endif
        /* select NAS signalling in GEARN or UTRAN currently */
        case TAF_SDC_SYS_MODE_WCDMA:
        case TAF_SDC_SYS_MODE_GSM:
            enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
            break;

        /* process no RAT case */
        default:
            enDomainSelRslt = TAF_SPM_ProcCcDomainSelectionOnNoRat(enCallType);
            break;
    }

    return (enDomainSelRslt);
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : TAF_SPM_ProcCLCcDomainSelection
 功能描述  : 1x Call业务的域选择流程
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月3日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2015年8月4日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcCLCcDomainSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_CDMA_1X))
    {
        /* TO DO: 目前CL还不支持IMS，所以暂定都是NAS信令 */
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    return TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcCcDomainSelection
 功能描述  : CS CALL业务的域选择流程
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月3日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcCcDomainSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* CDMA inside，并且当前是CL模式 */
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        return TAF_SPM_ProcCLCcDomainSelection(ulEventType, pstMsg);
    }
#endif

    return TAF_SPM_ProcGULCcDomainSelection(ulEventType, pstMsg);
}


/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSsDomainSelection
 功能描述  : SS业务请求的域选择流程。如果当前有SS业务或CC业务在运行，选择当前
             业务运行域，否则如果RAT是LTE，选择EUTRAN下SS域选择流程。如果RAT为
             GU(目前不支持GU下IMS)，域选择结果为NAS signnalling。
             注: 如果当前消息为TAF_MSG_RLEASE_MSG，理论上来说，当前应该有SS业务
             在运行，如果无SS业务在运行，选择NAS SIGNALLING，交由SSA模块处理

 输入参数  : ulEventType －－ 消息事件类型
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:              消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:          消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:          缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL: 拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月14日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
  3.日    期   : 2014年04月01日
    作    者   : y00245242
    修改内容   : 为DTS2014040203732修改，增加NV控制USSD业务域选择；USSD业务NV打开，
                 进行正常域选择，否则选择CS域
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSsDomainSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, begin */
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;
    VOS_UINT8                                               ucCsCallExistFlg;
    VOS_UINT8                                               ucImsCallExistFlg;
    VOS_UINT8                                               ucImsSmsExistFlg;
    VOS_UINT8                                               ucImsSsExistFlg;
    VOS_UINT8                                               ucUssdOnImsSupportFlag;

    ucImsCallExistFlg       = TAF_SDC_GetImsCallExistFlg();
    ucImsSmsExistFlg        = TAF_SDC_GetImsSmsSrvExistFlg();
    ucImsSsExistFlg         = TAF_SDC_GetImsSsSrvExistFlg();

    /* 目前UT布署在A核, AT或STK发起的非USSD的SS业务统一走CS域;
       STK或AT发起的USSD业务需要根据支持IMS USSD NV项是否打开，如果打开，
       经过正常SPM进行域选择，否则走CS域；
       IMS电话或短信业务存在时,收到AT或STK发起的非USSD的SS业务直接回复失败; */

    ucUssdOnImsSupportFlag = TAF_SDC_GetUssdOnImsSupportFlag();

    if ((VOS_FALSE == TAF_SPM_IsUssdServiceType(ulEventType))
     || (VOS_FALSE == ucUssdOnImsSupportFlag))
    {
        if ((VOS_TRUE   ==  ucImsCallExistFlg)
         || (VOS_TRUE   ==  ucImsSmsExistFlg)
         || (VOS_TRUE   ==  ucImsSsExistFlg))
        {
            return TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;
        }

        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-25, end */

    ucCsCallExistFlg = TAF_SDC_GetCsCallExistFlg();
    if ((VOS_TRUE == TAF_SDC_GetCsSsSrvExistFlg())
     || (VOS_TRUE == ucCsCallExistFlg))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    if ((VOS_TRUE == ucImsSsExistFlg)
     || (VOS_TRUE == ucImsCallExistFlg))
    {
        return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
    }

    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, begin */
    /* release消息域选择，CUSD不带ussd string的场景，卡状态的判断放到预处理里面来做 */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, end */


    switch (TAF_SDC_GetCampSysMode())
    {
#if ( FEATURE_ON == FEATURE_LTE )
        case TAF_SDC_SYS_MODE_LTE:
            enDomainSelRslt = TAF_SPM_ProcSsDomainSelectionOnEutran();
            break;
#endif

        /* currently, select NAS signalling in GEARN or UTRAN */
        case TAF_SDC_SYS_MODE_WCDMA:
        case TAF_SDC_SYS_MODE_GSM:
            enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
            break;

        /* no network */
        default:
            enDomainSelRslt = TAF_SPM_ProcSsDomainSelectionOnNoRat();
            break;
    }

    return (enDomainSelRslt);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSmsDomainSelection
 功能描述  : SMS域选择流程

 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:               消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:           消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:           缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL:  拒绝到来的请求消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月14日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
  3.日    期   : 2013年1月2日
    作    者   : y00245242
    修改内容   : 增加换域重拨功能
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSmsDomainSelection(VOS_VOID)
{
    VOS_UINT8                                                   ucCsSmsExistFlg;
    VOS_UINT8                                                   ucPsSmsExistFlg;
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                        enDomainSelRslt;

    /*
       有CS短信业务存在时，选择当前域;
       如果有IMS短信业务存在时，且无MO IMS短信在发送时，选择当前域；
       如果有IMS短信业务存在时，且MO IMS短信在发送时，选择缓存
       无短信业务存在时，进行如下判断:
       1.驻留在LTE下时，调用EUTRAN下的短信域选择函数
       2.驻留在GU下时，发送CS/PS短信
       3.不驻留在GUL下，缓存消息
    */
    ucCsSmsExistFlg = TAF_SDC_GetCsSmsSrvExistFlg();
    ucPsSmsExistFlg = TAF_SDC_GetPsSmsSrvExistFlg();

    /* 如果有CS/PS域SMS业务正在运行，发送CS/PS短信 */
    if ( (VOS_TRUE == ucCsSmsExistFlg)
      || (VOS_TRUE == ucPsSmsExistFlg) )
    {

        return TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
    }

    /* 如果有IMS短信正在发送，需放消息进入域选择缓存中 */
    if (VOS_TRUE == TAF_SPM_GetImsSmsSendingFlg())
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcSmsDomainSelection: ImsSmsSendingFlg IS TRUE,BUFFER.");

        return TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE;
    }

    /* 如果有MT IMS域SMS业务正在运行，选择当前域 */
    if (VOS_TRUE == TAF_SDC_GetImsSmsSrvExistFlg())
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcSmsDomainSelection: ImsSmsSrvExistFlg IS TRUE.");

        return TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP;
    }

    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, begin */
    /* 卡状态的判断放到预处理里面来做 */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-14, end */


    switch (TAF_SDC_GetCampSysMode())
    {
        /* 驻留在LTE下时，调用EUTRAN下的短信域选择函数 */
#if ( FEATURE_ON == FEATURE_LTE )
        case TAF_SDC_SYS_MODE_LTE:
            enDomainSelRslt = TAF_SPM_ProcSmsDomainSelectionOnEutran();
            break;
#endif

        /* 2.驻留在GU下 */
        case TAF_SDC_SYS_MODE_GSM:
        case TAF_SDC_SYS_MODE_WCDMA:
            enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
            break;

        /* 3.无网络下 */
        default:
            enDomainSelRslt = TAF_SPM_ProcSmsDomainSelectionOnNoRat();;
            break;

    }

    return enDomainSelRslt;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcServiceRequestDomainSelection
 功能描述  : 域选择流程，将根据当前请求的消息业务类型(CC/SS/SMS)，选择对应的域
             选择流程

 输入参数  : ulEventType -- 消息事件类型
             pstMsg －－ 消息指针

 输出参数  : 无
 返 回 值  : TAF_SPM_MSG_CS_OVER_IP:               消息允许发送给IMS，基于IP发送
             TAF_SPM_MSG_NAS_SIGNALLING:           消息走NAS signalling
             TAF_SPM_MSG_BUFFER_MESSAGE:           缓存消息
             TAF_SPM_DOMAIN_SEL_TYPE_SELECT_FAIL:  拒绝到来的请求消息

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcServiceRequestDomainSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8                         enSrvReqType;
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU                           stSrvAcqRatList;

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));

    enSrvReqType    = TAF_SPM_GetServiceRequestType(pstMsg);

    enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_BUTT;

    if (VOS_FALSE == TAF_SPM_GetRfAvailInfo(enSrvReqType, &stSrvAcqRatList))
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if ( (VOS_FALSE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_CDMA_1X))
          && (TAF_MMA_SRV_ACQ_RAT_TYPE_1X == stSrvAcqRatList.aenRatType[0])
          && (1 == stSrvAcqRatList.ucRatNum) )
        {
            return TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;
        }
#endif

        /* no rf时缓存业务请求消息，等收到搜网结果再处理,缓存成功再发资源申请 */
        return TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE;
    }

#if (FEATURE_IMS == FEATURE_ON)
    switch (enSrvReqType)
    {
        case TAF_SPM_SRV_REQ_TYPE_CALL:
            enDomainSelRslt = TAF_SPM_ProcCcDomainSelection(ulEventType, pstMsg);

            if ((ulEventType                              == TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ))
             && (TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING == enDomainSelRslt))
            {
                enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL;
            }
            break;

        case TAF_SPM_SRV_REQ_TYPE_SS:
            enDomainSelRslt = TAF_SPM_ProcSsDomainSelection(ulEventType, pstMsg);
            break;

        case TAF_SPM_SRV_REQ_TYPE_SMS:
            enDomainSelRslt = TAF_SPM_ProcSmsDomainSelection();
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcServiceRequestDomainSelection: unknow message is received!");
            break;
    }

    /* log service domain selection pre-condition infomation */
    TAF_SPM_LogSrvDomainSelPreconditionInfo();

    TAF_SPM_LogSrvDomainSelRedialInfo();

    TAF_NORMAL_LOG1(WUEPS_PID_TAF, "TAF_SPM_ProcServiceRequestDomainSelection %d.", enDomainSelRslt);
#else
    enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;
#endif

    return (enDomainSelRslt);
}

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_SPM_ProcBufferedDomainSelectionResult
 功能描述  : 分发缓存的消息到IMSA或TAF其他模块。对于结果为发送失败的消息，通知
             发送业务请求失败
             注: 在域选择结果为CS OVER IP时，需要有个特殊处理，即在ulRst结果为
                 VOS_FALSE时，需要把缓存消息勾出来，由后续模块继续处理，主要是
                 针对SMS，因为SMS不是直接发送给IMSA的，而是转交给MSG模块处理

 输入参数  : enDomainSelType -- 业务域选择类型
             pstMsgEntry －－ 消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE -- 消息处理完毕
             VOS_FALSE -- 消息未处理完成，待进一步处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcBufferedDomainSelectionResult(
    TAF_SPM_ENTRY_MSG_STRU                                     *pstMsgEntry,
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                        enDomainSelRslt
)
{
    VOS_UINT32                          ulRst;

    /* tranfer message to call module if the result is nas signalling */
    if (TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING == enDomainSelRslt)
    {
        (VOS_VOID)TAF_SPM_ProcReqMsgBasedOnNasSignalling(pstMsgEntry->ulEventType,
                                               (struct MsgCB*)&(pstMsgEntry->aucEntryMsgBuffer[0]));

        TAF_SPM_UpdateServiceCtrlEntryMsg(pstMsgEntry->ulEventType,
                                          (struct MsgCB*)&(pstMsgEntry->aucEntryMsgBuffer[0]));

        TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

        /* message need to be processed further by call module, so return VOS_FALSE */
        ulRst = VOS_FALSE;
    }
    /* tranfer message to call module if the result is nas signalling */
    else if (TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP == enDomainSelRslt)
    {
        ulRst = TAF_SPM_ProcReqMsgBasedOnCsOverIp(pstMsgEntry->ulEventType,
                                                     (struct MsgCB*)&(pstMsgEntry->aucEntryMsgBuffer[0]));

        /* for SMS message, message need to be processed by MSG module, not IMSA. */
        if (VOS_FALSE == ulRst)
        {
            TAF_SPM_UpdateServiceCtrlEntryMsg(pstMsgEntry->ulEventType,
                                              (struct MsgCB*)&(pstMsgEntry->aucEntryMsgBuffer[0]));

            TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);
        }
    }
    /* send fail to sender of service request if the result is select fail */
    else
    {
        ulRst = TAF_SPM_ProcServiceRequestFail(pstMsgEntry->ulEventType,
                                          (struct MsgCB*)&(pstMsgEntry->aucEntryMsgBuffer[0]));
    }

    return ulRst;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsSmmaMsgExistedInSericeSelectionBuffer
 功能描述  : 检查SMMA中是否已经缓存了SMMA消息

 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 已有消息在域选择存在中
             VOS_FALSE -- 无SMMA消息在缓存中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月15日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsSmmaMsgExistedInSericeSelectionBuffer(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNumOfMsg;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCacheMsg = VOS_NULL_PTR;

    ucNumOfMsg = TAF_SPM_GetSmsMsgQueueNum();

    for(i = 0; (i < ucNumOfMsg) && (i < TAF_SPM_MAX_SMS_MSG_QUEUE_NUM); i++)
    {
        pstCacheMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(i);

        if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_SPM_SMMA_IND) == pstCacheMsg->stMsgEntry.ulEventType)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSmmaIndDomainSelectionResult
 功能描述  : 根据域选择结果处理SMMA IND的消息

 输入参数  : enDomainSelRslt -- 域选择结果类型

 输出参数  : 无
 返 回 值  : VOS_TRUE -- 消息处理完毕
             VOS_FALSE -- 消息未处理完成，待进一步处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2015年4月13日
    作    者   : s00217060
    修改内容   : DTS2015041007878:ID_TAF_SPM_MSG_REPORT_IND中的client id不对
                 ，重拨缓存未清除
*****************************************************************************/
VOS_VOID TAF_SPM_ProcSmmaIndDomainSelectionResult(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg,
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt
)
{
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32                     enMsgSignallingType;
    MN_APP_REQ_MSG_STRU                                    *pstSmsMsg = VOS_NULL_PTR;

    if (TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP == enDomainSelRslt)
    {
        enMsgSignallingType = TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP;
    }
    else if (TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING == enDomainSelRslt)
    {
        enMsgSignallingType = TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING;
    }
    else if (TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE == enDomainSelRslt)
    {
        if (VOS_FALSE == TAF_SPM_IsSmmaMsgExistedInSericeSelectionBuffer())
        {
            /* 缓存SMMA消息后，不care缓存是否失败，返回 */
            (VOS_VOID)TAF_SPM_BufferAppRequestMessage(ulEventType, pstMsg);
        }

        return;
    }
    else
    {
        /* 忽略该SMMA消息 */
        return;
    }

    /* 短信换域重拨功能打开，保存消息到缓存 */
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == enMsgSignallingType)
    {

        /* 设置IMS短信发送标志为TRUE */
        TAF_SPM_SetImsSmsSendingFlg(VOS_TRUE);

        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_ProcSmmaIndDomainSelectionResult: ImsSmsSendingFlg IS TRUE.");
        TAF_SPM_LogSrvDomainSelRedialInfo();

        if (VOS_TRUE == TAF_SDC_GetSmsRedailFromImsToCsSupportFlag())
        {
            pstSmsMsg   = (MN_APP_REQ_MSG_STRU *)pstMsg;
            ulEventType = TAF_BuildEventType(pstSmsMsg->ulSenderPid, pstSmsMsg->usMsgName);

            if (VOS_FALSE == TAF_SPM_StoreMsgIntoSmsRedialBuffer(ulEventType, pstMsg))
            {
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                          "TAF_SPM_ProcSmmaIndDomainSelectionResult: TAF_SPM_StoreMsgIntoSmsRedialBuffer error!");
            }
        }
    }

    /* 发送消息到MSG模块 */
    TAF_SPM_SendMsgSmmaRsp(enMsgSignallingType, pstMsg);
}


/* IMS无关函数放到IMS宏外面用于扩展使用 */

/*****************************************************************************
 函 数 名  : TAF_SPM_FreeMessagesInMessageQueue
 功能描述  : 收到power off指示后，SPM需要根据队列中缓存的消息，发送失败指示给
             对应的消息发送方，并清除缓存队列中的业务请求

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月10日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月31日
    作    者   : y00245242
    修改内容   : 增加换域重拨功能
  3.日    期   : 2014年2月19日
    作    者   : s00217060
    修改内容   : coverity清理
*****************************************************************************/
VOS_VOID TAF_SPM_FreeMessagesInMessageQueue(VOS_VOID)
{
    VOS_UINT8                           ucIndex;
    /* Added by s00217060 for coverity清理, 2014-02-17, begin */
    VOS_UINT8                           ucMsgQueueNum;
    /* Added by s00217060 for coverity清理, 2014-02-17, end */
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsg = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg    = VOS_NULL_PTR;

    /*
     * Note: At present, we just cache not more than one message. Or here need
     * to process all messages in queue.
     */

     /* free CC service request message in queue */
    /* Modified by s00217060 for coverity清理, 2014-02-19, begin */
    ucMsgQueueNum = TAF_SPM_GetCcMsgQueueNum();
    ucMsgQueueNum = TAF_SDC_MIN(ucMsgQueueNum, TAF_SPM_MAX_CC_MSG_QUEUE_NUM);
    for (ucIndex = 0; ucIndex < ucMsgQueueNum; ucIndex++)
    {
        /* get the first cached message in queue */
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(ucIndex);

        /* stop CC service protect timer */
        pstAppMsg    = (MN_APP_REQ_MSG_STRU *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]);
        TAF_SPM_StopTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

        /* notify user that service request is failure */
        TAF_SPM_SendCcServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_CS_CAUSE_POWER_OFF);

        /* clear the first cached message in queue */
        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(ucIndex);

    }

    /* free SMS service request message in queue */
    ucMsgQueueNum = TAF_SPM_GetSmsMsgQueueNum();
    ucMsgQueueNum = TAF_SDC_MIN(ucMsgQueueNum, TAF_SPM_MAX_SMS_MSG_QUEUE_NUM);
    for (ucIndex = 0; ucIndex < ucMsgQueueNum; ucIndex++)
    {
        /* get the first cached message in queue */
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(ucIndex);

        /* stop SMS service protect timer */
        pstAppMsg    = (MN_APP_REQ_MSG_STRU *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]);

        /* notify user that service request is failure */
        if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_SPM_SMMA_IND) != pstCachedMsg->stMsgEntry.ulEventType)
        {
            /* 停止域选择缓存定时器 */
            TAF_SPM_StopTimer(TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

            /* 通知应用层消息发送失败 */
            TAF_SPM_SendSmsServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                             (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                             MN_ERR_CLASS_SMS_POWER_OFF);
        }

        /* clear the first cached message in queue */
        TAF_SPM_FreeSpecificedIndexMessageInSmsQueue(ucIndex);
    }

    /* free SS service request message in queue */
    ucMsgQueueNum = TAF_SPM_GetSsMsgQueueNum();
    ucMsgQueueNum = TAF_SDC_MIN(ucMsgQueueNum, TAF_SPM_MAX_SS_MSG_QUEUE_NUM);
    for (ucIndex = 0; ucIndex < ucMsgQueueNum; ucIndex++)
    /* Modified by s00217060 for coverity清理, 2014-02-19, end */
    {
        /* get the first cached message in queue */
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(ucIndex);

        /* stop SS service protect timer */
        pstAppMsg    = (MN_APP_REQ_MSG_STRU *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]);
        TAF_SPM_StopTimer(TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

        /* notify user that service request is failure */
        TAF_SPM_SendSsServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_ERR_SS_POWER_OFF);

        /* clear the first cached message in queue */
        TAF_SPM_FreeSpecificedIndexMessageInSsQueue(ucIndex);
    }

    /* log service domain selection information */
    TAF_SPM_LogSrvDomainSelQueueInfo();
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcMmaPowerOffInd
 功能描述  : 处理来自MMA的关机指示，收到该消息，需要free所有缓存消息，并清除IMS
             注册

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 移IMS注册状态到SDC中
*****************************************************************************/
VOS_VOID TAF_SPM_ProcMmaPowerOffInd(VOS_VOID)
{
    /* free all buffered message */
    TAF_SPM_FreeMessagesInMessageQueue();

    /* reset IMS normal register status */
    TAF_SDC_SetImsNormalRegStatus(TAF_SDC_IMS_NORMAL_REG_STATUS_DEREG);
}


/*****************************************************************************
 函 数 名  : TAF_SPM_ProcImsaNormalRegStatusNotify
 功能描述  : 处理IMS注册状态，收到该消息后，更新IMS注册状态，同时触发缓存消息
             处理

 输入参数  : pstMsg -- 消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 消息处理完毕
             VOS_FALSE -- 消息未处理完成，待进一步处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月17日
    作    者   : y00245242
    修改内容   : 移IMS注册状态到SDC中
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcImsaNormalRegStatusNotify(
    struct MsgCB                       *pstMsg
)
{
    IMSA_NORMAL_REG_STATUS_NOTIFY_STRU *pstImsaNormalRegNotify = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    ulRst = VOS_TRUE;

    pstImsaNormalRegNotify = (IMSA_NORMAL_REG_STATUS_NOTIFY_STRU *)pstMsg;

    /* update IMS register status */
    TAF_SDC_SetImsNormalRegStatus((TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8)pstImsaNormalRegNotify->enNormalRegStatus);

    /* process the cached message in queue */
    ulRst = TAF_SPM_ProcBufferedMsgInQueue();

    return ulRst;
}
#endif

/* IMS无关函数放到IMS宏开关外面,用于扩展使用 */

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcInitialDomainSelectionResult
 功能描述  : 该函数根据APP请求消息的初始域选择结果，选择对应的消息处理:
             1. 域选择结果为NAS signalling，消息分发给TAF各业务适配模块
                (CALL, MSG, SSA);
             2. 域选择结果为CS OVER IP,选择消息发送给IMSA;
             3. 域选择结果为buffer message，放消息到缓存队列中；
             4. 域选择结果为select fail，通知APP消息发送失败；

 输入参数  : ulEventType -- 消息事件类型
             pstMsg      -- 消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE -- 消息处理完毕
             VOS_FALSE -- 消息处理未完成，待后续进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2014年6月23日
    作    者   : z00161729
    修改内容   : DSDS III新增
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcInitialDomainSelectionResult(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg,
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt
)
{
    VOS_UINT32                                              ulRet;

    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8                         enSpmSrvReqType;
    TAF_MMA_SRV_TYPE_ENUM_UINT8                             enMmaSrvType;
    MN_CALL_APP_REQ_MSG_STRU                               *pstMnCallAppReqMsg = VOS_NULL_PTR;
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU                           stSrvAcqRatList;


    ulRet = VOS_FALSE;

    switch (enDomainSelRslt)
    {
        case TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING:
            ulRet = TAF_SPM_ProcReqMsgBasedOnNasSignalling(ulEventType, pstMsg);
            break;

#if (FEATURE_IMS == FEATURE_ON)
        case TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP:
            ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
            break;
#endif

        case TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE:
            ulRet = TAF_SPM_BufferAppRequestMessage(ulEventType, pstMsg);

            /* if buffer message is failure, send service fail to message sender */
            if (VOS_FALSE == ulRet)
            {
                ulRet = TAF_SPM_ProcServiceRequestFail(ulEventType, pstMsg);
            }
            else
            {
                /* no rf场景缓存成功，发送srv acq req消息 */
                enSpmSrvReqType = TAF_SPM_GetServiceRequestType(pstMsg);

                PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));

                if (VOS_FALSE == TAF_SPM_GetRfAvailInfo(enSpmSrvReqType, &stSrvAcqRatList))
                {
                    TAF_SPM_ConvertSrvTypeToMma(enSpmSrvReqType, &enMmaSrvType);

                    if (TAF_SPM_SRV_REQ_TYPE_CALL == enSpmSrvReqType)
                    {
                        pstMnCallAppReqMsg = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;
                        if (MN_CALL_TYPE_EMERGENCY == pstMnCallAppReqMsg->unParm.stOrig.enCallType)
                        {
                            enMmaSrvType =  TAF_MMA_SRV_TYPE_CS_MO_EMERGENCY_CALL;
                        }
                    }

                    TAF_MMA_SrvAcqReq(enMmaSrvType, &stSrvAcqRatList);
                }
            }
            break;

        case TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL:

            ulRet = TAF_SPM_ProcServiceRequestFail(ulEventType, pstMsg);
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF,
                          "TAF_SPM_ProcInitDomainSelectionResult: domain selection type is error!");
            break;
    }

    return (ulRet);
}

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_SPM_ProcReqMsgBasedOnCsOverIp
 功能描述  : 处理基于SIP信令承载的请求消息，通过消息跳转表，选择对应的消息处理
             函数

 输入参数  : ulEventType -- 由PID与message name组成
             pstMsg      -- 消息地址

 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息已经处理
             VOS_FALSE: 消息未处理完
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcReqMsgBasedOnCsOverIp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRetFlg;
    TAF_SPM_PROC_MSG_STRU              *pstTabHeader = VOS_NULL_PTR;

    MN_CALL_APP_REQ_MSG_STRU           *pstCallMsg   = VOS_NULL_PTR;
    MN_CALL_ORIG_PARAM_STRU            *pstOrigReq   = VOS_NULL_PTR;

    /* Get tab first address */
    pstTabHeader = TAF_SPM_GetImsDomainSelMsgTabAddr();

    if (ulEventType == TAF_BuildEventType(WUEPS_PID_AT, MN_CALL_APP_ORIG_REQ))
    {
        pstCallMsg   = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;
        pstOrigReq   = (MN_CALL_ORIG_PARAM_STRU *)(&pstCallMsg->unParm);

        /* IMS视频在域选择完后如果VIDEO能力不支持需要转成IMS语音呼叫 */
        if ((VOS_FALSE == TAF_SDC_GetVideoCallOnImsSupportFlag())
         && (TAF_SPM_IS_VIDEO_CALL(pstOrigReq->enCallType)))
        {
            pstOrigReq->enCallType = MN_CALL_TYPE_VOICE;
        }
    }

    /* look up the matched message event type */
    for (i = 0; i < TAF_SPM_GET_IMS_DOMAIN_SEL_MSG_TAB_SIZE; i++)
    {
        if (ulEventType == pstTabHeader->ulMsgEvtType)
        {
            ulRetFlg = pstTabHeader->pfMsgFun(pstMsg);

            return ulRetFlg;
        }

        pstTabHeader++;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvRegisterSsReqBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的register SS请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2013年09月23日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目，更新IMS域SS业务标志
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvRegisterSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SendImsaRegisterSsReq(pstMsg);

    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
    TAF_SDC_SetImsSsSrvExistFlg(VOS_TRUE);
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvEraseSsReqBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的SS erase请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2013年09月23日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目，更新IMS域SS业务标志
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvEraseSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SendImsaEraseSsReq(pstMsg);

    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
    TAF_SDC_SetImsSsSrvExistFlg(VOS_TRUE);
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvActivateSsReqBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的SS activate请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2013年09月23日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目，更新IMS域SS业务标志
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvActivateSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SendImsaActivateSsReq(pstMsg);

    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
    TAF_SDC_SetImsSsSrvExistFlg(VOS_TRUE);
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvDeactivateSsReqBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的SS deactivate请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2013年09月23日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目，更新IMS域SS业务标志
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvDeactivateSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SendImsaDeactivateSsReq(pstMsg);

    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
    TAF_SDC_SetImsSsSrvExistFlg(VOS_TRUE);
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvInterrogateSsReqBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的SS interrogate请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2013年09月23日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目，更新IMS域SS业务标志
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvInterrogateSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SendImsaInterrogateSsReq(pstMsg);

    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
    TAF_SDC_SetImsSsSrvExistFlg(VOS_TRUE);
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvProcUssSsReqBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的SS process Ussd请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2013年09月23日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseII项目，更新IMS域SS业务标志
 3.日    期   : 2013年12月23日
   作    者   : s00217060
   修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvProcUssSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstRcvMsg   = VOS_NULL_PTR;
    TAF_SS_PROCESS_USS_REQ_STRU        *pstSsReqMsg = VOS_NULL_PTR;

    pstRcvMsg   = (MN_APP_REQ_MSG_STRU *)pstMsg;
    pstSsReqMsg = (TAF_SS_PROCESS_USS_REQ_STRU *)&(pstRcvMsg->aucContent[0]);

    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-23, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-23, end */

    /* check whether or not USSD string exists */
    if (0 != pstSsReqMsg->UssdStr.usCnt)
    {
        TAF_SPM_SendImsaProcessUssSsReq(pstMsg);

        /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
        TAF_SDC_SetImsSsSrvExistFlg(VOS_TRUE);
        /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvRleaseSsReqBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的SS release请求消息
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月23日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvRleaseSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SendImsaReleaseSsReq(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppOrigReqBasedOnCsOverIp
 功能描述  : SPM收到MN_CALL_APP_ORIG_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年12月13日
    作    者   : y00245242
    修改内容   : 增加IMS域到CS域的换域重拨功能
  3.日    期   : 2013年12月16日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
  4.日    期   : 2014年2月17日
    作    者   : y00245242
    修改内容   : DTS2014031105153: 增加IMS域MPTY域选择流程
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppOrigReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoicePerferred;
    VOS_UINT32                          ulEventType;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg       = VOS_NULL_PTR;

    pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    if (VOS_TRUE == pstAppMsg->unParm.stOrig.ucImsInvitePtptFlag)
    {
        TAF_SPM_SendImsaCallInviteNewPtptReq(pstAppMsg);

        return VOS_TRUE;
    }

    /* 重拨功能打开且语音优先域为CS preferred 或VOIP preferred时，保存消息到缓存 */
    enVoicePerferred = TAF_SDC_GetVoiceDomain();
    if ((VOS_TRUE                         == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
     && (TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY != enVoicePerferred))
    {
        ulEventType = TAF_BuildEventType(pstAppMsg->ulSenderPid, pstAppMsg->enReq);
        if (VOS_FALSE == TAF_SPM_StoreMsgIntoCallRedialBuffer(ulEventType, pstMsg))
        {
            /* 存储消息失败，应该有一个call正在发起，拒绝当前call */
            TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_NOT_ALLOW);

            return VOS_TRUE;
        }
    }

    TAF_SPM_SendImsaCallOrigReq(pstAppMsg);
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppSupsCmdReqBasedOnCsOverIp
 功能描述  : SPM收到MN_CALL_APP_SUPS_CMD_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年12月13日
    作    者   : y00245242
    修改内容   : 增加IMS域到CS域的换域重拨功能
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppSupsCmdReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_APP_REQ_MSG_STRU            *pstAppMsg = VOS_NULL_PTR;

    pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* 发送给IMSA处理 */
    TAF_SPM_SendImsaSupsCmdReq((MN_CALL_APP_REQ_MSG_STRU *)pstMsg);

    /* 用户挂机，如果有对应的重拨缓存存在，清除它 */
    switch (pstAppMsg->unParm.stCallMgmtCmd.enCallSupsCmd)
    {
        case MN_CALL_SUPS_CMD_REL_CALL_X:
            TAF_SPM_FreeCallRedialBufferWithCallId(pstAppMsg->callId);
            break;

        case MN_CALL_SUPS_CMD_REL_ALL_CALL:
        case MN_CALL_SUPS_CMD_REL_ALL_EXCEPT_WAITING_CALL:
            TAF_SPM_FreeCallRedialBufferWithClientId(pstAppMsg->clientId);
            break;

        default:
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppGetInfoReqBasedOnCsOverIp
 功能描述  : SPM收到MN_CALL_APP_GET_INFO_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年09月18日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目，添加消息来源模块标识
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetInfoReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, begin */
    /* 发送给IMSA处理 */
    TAF_SPM_SendImsaGetCallInfoReq((MN_CALL_APP_REQ_MSG_STRU *)pstMsg, CALL_IMSA_GET_CALL_INFO_REQ_TYPE_CLCC);
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppGetEconfInfoReqBasedOnCsOverIp
 功能描述  : SPM收到TAF_CALL_APP_GET_ECONF_CALLED_INFO_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetEconfInfoReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    /* 发送给IMSA处理 */
    TAF_SPM_SendImsaGetEconfInfoReq((MN_CALL_APP_REQ_MSG_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppStartDtmfReqBasedOnCsOverIp
 功能描述  : SPM收到MN_CALL_APP_START_DTMF_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppStartDtmfReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    /* 发送给IMSA处理 */
    TAF_SPM_SendImsaStartDtmfReq((MN_CALL_APP_REQ_MSG_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppStopDtmfReqBasedOnCsOverIp
 功能描述  : SPM收到MN_CALL_APP_STOP_DTMF_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppStopDtmfReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    /* 发送给IMSA处理 */
    TAF_SPM_SendImsaStopDtmfReq((MN_CALL_APP_REQ_MSG_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppGetCdurReqBasedOnCsOverIp
 功能描述  : SPM收到MN_CALL_APP_GET_CDUR_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetCdurReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    /* 发送给IMSA处理 */
    TAF_SPM_SendImsaGetCdurReq((MN_CALL_APP_REQ_MSG_STRU *)pstMsg);

    return VOS_TRUE;
}

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppGetCallInfoReqBasedOnCsOverIp
 功能描述  : SPM收到ID_TAFAGENT_MN_GET_CALL_INFO_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月18日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetCallInfoReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    /* 发送给IMSA处理 */
    TAF_SPM_SendImsaGetCallInfoReq((MN_CALL_APP_REQ_MSG_STRU *)pstMsg, CALL_IMSA_GET_CALL_INFO_REQ_TYPE_ATA);

    return VOS_TRUE;
}

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, end */

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppGetClprReqBasedOnCsOverIp
 功能描述  : SPM收到MN_CALL_APP_CLPR_GET_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月08日
    作    者   : Y00213812
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetClprReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    /* 发送给IMSA处理 */
    TAF_SPM_SendImsaGetClprReq((MN_CALL_APP_REQ_MSG_STRU *)pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_RcvStkOrigReqBasedOnCsOverIp
 功能描述  : SPM收到STK_CALL_CALLORIG_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年12月13日
    作    者   : y00245242
    修改内容   : 增加IMS域到CS域的换域重拨功能
  3.日    期   : 2013年12月16日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseIII项目
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvStkOrigReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstOrigParam       = VOS_NULL_PTR;
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
    MN_CALL_APP_REQ_MSG_STRU            stAppMsg;
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoicePerferred;
    VOS_UINT32                          ulEventType;

    pstOrigParam           = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstMsg;

    /* 重拨功能打开且语音优先域为CS preferred 或VOIP preferred时，保存消息到缓存 */
    enVoicePerferred = TAF_SDC_GetVoiceDomain();
    if ((VOS_TRUE == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
     && (TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY != enVoicePerferred))
    {
        ulEventType = TAF_BuildEventType(pstOrigParam->ulSenderPid, pstOrigParam->ulMsgId);
        if (VOS_FALSE == TAF_SPM_StoreMsgIntoCallRedialBuffer(ulEventType, pstMsg))
        {
            /* 存储消息失败，应该有一个call正在发起，拒绝当前call */
            TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_NOT_ALLOW);
            return VOS_TRUE;
        }
    }

    PS_MEM_SET(&stAppMsg, 0, sizeof(stAppMsg));
    stAppMsg.clientId                   = pstOrigParam->usClientId;
    stAppMsg.opId                       = pstOrigParam->opID;
    stAppMsg.callId                     = pstOrigParam->callID;
    stAppMsg.unParm.stOrig.enCallType   = pstOrigParam->enCallType;

    /* enClirCfg等参数按默认值填写 */
    stAppMsg.unParm.stOrig.enClirCfg                = MN_CALL_CLIR_AS_SUBS;
    stAppMsg.unParm.stOrig.enCallMode               = MN_CALL_MODE_SINGLE;
    stAppMsg.unParm.stOrig.stCugCfg.bEnable         = VOS_FALSE;
    stAppMsg.unParm.stOrig.stDataCfg.enSpeed        = MN_CALL_CSD_SPD_64K_MULTI;
    stAppMsg.unParm.stOrig.stDataCfg.enName         = MN_CALL_CSD_NAME_SYNC_UDI;
    stAppMsg.unParm.stOrig.stDataCfg.enConnElem     = MN_CALL_CSD_CE_T;

    if (0 != pstOrigParam->stSubAddr.ucLen)
    {
        stAppMsg.unParm.stOrig.stSubaddr.IsExist        = VOS_TRUE;
        stAppMsg.unParm.stOrig.stSubaddr.LastOctOffset  = 0;

        PS_MEM_CPY(stAppMsg.unParm.stOrig.stSubaddr.SubAddrInfo,
                    pstOrigParam->stSubAddr.aucSubAddr,
                    MN_CALL_MAX_SUBADDR_INFO_LEN);
    }

    stAppMsg.unParm.stOrig.stDialNumber.enNumType = pstOrigParam->stCalledAddr.ucAddrType;

    stAppMsg.unParm.stOrig.stDialNumber.ucNumLen  = pstOrigParam->stCalledAddr.ucLen;
    if (MN_CALL_MAX_CALLED_BCD_NUM_LEN < pstOrigParam->stCalledAddr.ucLen)
    {
        stAppMsg.unParm.stOrig.stDialNumber.ucNumLen = MN_CALL_MAX_CALLED_BCD_NUM_LEN;
    }

    PS_MEM_CPY(&(stAppMsg.unParm.stOrig.stDialNumber.aucBcdNum[0]),
               &(pstOrigParam->stCalledAddr.aucAddr[0]),
               stAppMsg.unParm.stOrig.stDialNumber.ucNumLen);

    PS_MEM_CPY(&(stAppMsg.unParm.stOrig.stEmergencyCat),
                (MN_CALL_EMERGENCY_CAT_STRU *)&pstOrigParam->stEmergencyCat,
                sizeof(MN_CALL_EMERGENCY_CAT_STRU));

    TAF_SPM_SendImsaCallOrigReq(&stAppMsg);
    /* Modified by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvStkSupsCmdReqBasedOnCsOverIp
 功能描述  : SPM收到STK_CALL_SUPS_CMD_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年12月13日
    作    者   : y00245242
    修改内容   : 增加IMS域到CS域的换域重拨功能
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvStkSupsCmdReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    MN_APP_CALL_SUPS_REQ_STRU          *pstCallSups    = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU            stAppMsg;

    pstCallSups = (MN_APP_CALL_SUPS_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stAppMsg, 0, sizeof(stAppMsg));
    stAppMsg.clientId                   = pstCallSups->usClientId;
    stAppMsg.opId                       = pstCallSups->opID;
    stAppMsg.callId                     = pstCallSups->stSupsPara.callId;
    stAppMsg.unParm.stCallMgmtCmd       = pstCallSups->stSupsPara;

    /* 发送给IMSA处理 */
    TAF_SPM_SendImsaSupsCmdReq(&stAppMsg);

    /* 用户挂机，如果有对应的重拨缓存存在，清除它 */
    switch (pstCallSups->stSupsPara.enCallSupsCmd)
    {
        case MN_CALL_SUPS_CMD_REL_CALL_X:
            TAF_SPM_FreeCallRedialBufferWithCallId(pstCallSups->stSupsPara.callId);
            break;

        case MN_CALL_SUPS_CMD_REL_ALL_CALL:
        case MN_CALL_SUPS_CMD_REL_ALL_EXCEPT_WAITING_CALL:
            TAF_SPM_FreeCallRedialBufferWithClientId(pstCallSups->usClientId);
            break;

        default:
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_RcvStkStartDtmfReqBasedOnCsOverIp
 功能描述  : SPM收到MN_CALL_APP_START_DTMF_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvStkStartDtmfReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    MN_APP_CALL_START_DTMF_REQ_STRU    *pstStartDtmf   = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU            stAppMsg;


    pstStartDtmf = (MN_APP_CALL_START_DTMF_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stAppMsg, 0, sizeof(stAppMsg));
    stAppMsg.clientId                   = pstStartDtmf->usClientId;
    stAppMsg.opId                       = pstStartDtmf->opID;
    stAppMsg.callId                     = pstStartDtmf->callID;
    stAppMsg.unParm.stDtmf              = pstStartDtmf->stTafStartDtmfPara;

    /* 发送给IMSA处理 */
    TAF_SPM_SendImsaStartDtmfReq(&stAppMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvStkStopDtmfReqBasedOnCsOverIp
 功能描述  : SPM收到STK_CALL_STOP_DTMF_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvStkStopDtmfReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    MN_APP_CALL_STOP_DTMF_REQ_STRU     *pstStopDtmf     = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU            stAppMsg;

    pstStopDtmf = (MN_APP_CALL_STOP_DTMF_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stAppMsg, 0, sizeof(stAppMsg));
    stAppMsg.clientId                   = pstStopDtmf->usClientId;
    stAppMsg.opId                       = pstStopDtmf->opID;
    stAppMsg.callId                     = pstStopDtmf->callID;

    /* 发送给IMSA处理 */
    TAF_SPM_SendImsaStopDtmfReq(&stAppMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvSendRpdataDirectBasedOnCsOverIp
 功能描述  : 处理来自AT或STK的SMS RP DATA消息，设置消息路由类型为IMS
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_FALSE  消息未处理完成

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月11日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2013年12月13日
   作    者   : y00245242
   修改内容   : 增加IMS域到CS域的换域重拨功能
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvSendRpdataDirectBasedOnCsOverIp(
    struct MsgCB                       *pstRcvMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstSmsMsg = VOS_NULL_PTR;
    MN_MSG_SEND_PARM_STRU              *pstMsgSnd = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

    pstSmsMsg = (MN_APP_REQ_MSG_STRU *)pstRcvMsg;

    pstMsgSnd = (MN_MSG_SEND_PARM_STRU *)(pstSmsMsg->aucContent);

    pstMsgSnd->enMsgSignallingType = TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP;

    /* 短信换域重拨功能打开，保存消息到缓存 */
    if (VOS_TRUE == TAF_SDC_GetSmsRedailFromImsToCsSupportFlag())
    {
        ulEventType = TAF_BuildEventType(pstRcvMsg->ulSenderPid, pstSmsMsg->usMsgName);

        if (VOS_FALSE == TAF_SPM_StoreMsgIntoSmsRedialBuffer(ulEventType, pstRcvMsg))
        {
            /* 存储消息失败，缓存队列满，拒绝当前SMS */
            TAF_SPM_SendSmsServiceRequetFail(ulEventType, pstRcvMsg, MN_ERR_CLASS_SMS_REDIAL_BUFFER_FULL);
            return VOS_TRUE;
        }
    }

    /* 设置IMS短信发送标志 */
    TAF_SPM_SetImsSmsSendingFlg(VOS_TRUE);

    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvSendRpdataDirectBasedOnCsOverIp: ImsSmsSendingFlg IS TRUE.");
    TAF_SPM_LogSrvDomainSelRedialInfo();

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_RcvSendRpdataFromMemBasedOnCsOverIp
 功能描述  : 处理从memory中发送的SMS的消息，设置消息路由类型为IMS
 输入参数  : pstRcvMsg  消息指针

 输出参数  : 无
 返 回 值  : VOS_FALSE  消息未处理完成

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月11日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2013年12月13日
   作    者   : y00245242
   修改内容   : 增加IMS域到CS域的换域重拨功能
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvSendRpdataFromMemBasedOnCsOverIp(
    struct MsgCB                       *pstRcvMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstSmsMsg    = VOS_NULL_PTR;
    MN_MSG_SEND_FROMMEM_PARM_STRU      *pstSndMemMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

    pstSmsMsg    = (MN_APP_REQ_MSG_STRU *)pstRcvMsg;

    pstSndMemMsg = (MN_MSG_SEND_FROMMEM_PARM_STRU *)(pstSmsMsg->aucContent);

    /* set SMS sending flag to IMS stack */
    pstSndMemMsg->enMsgSignallingType = TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP;

    /* 短信换域重拨功能打开，保存消息到缓存 */
    if (VOS_TRUE == TAF_SDC_GetSmsRedailFromImsToCsSupportFlag())
    {
        ulEventType = TAF_BuildEventType(pstRcvMsg->ulSenderPid, pstSmsMsg->usMsgName);

        if (VOS_FALSE == TAF_SPM_StoreMsgIntoSmsRedialBuffer(ulEventType, pstRcvMsg))
        {
            /* 存储消息失败，缓存队列满，拒绝当前SMS */
            TAF_SPM_SendSmsServiceRequetFail(ulEventType, pstRcvMsg, MN_ERR_CLASS_SMS_REDIAL_BUFFER_FULL);
            return VOS_TRUE;
        }
    }

    /* 设置IMS短信发送标志 */
    TAF_SPM_SetImsSmsSendingFlg(VOS_TRUE);

    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvSendRpdataFromMemBasedOnCsOverIp: ImsSmsSendingFlg IS TRUE.");
    TAF_SPM_LogSrvDomainSelRedialInfo();


    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsNeedtoWaitImsRegStatus
 功能描述  : 根据之前的业务状态以及网路能力参数与当前的服务状态与能力参数决定
             是否立即做域选择还是继续等待IMS新的注册状态

 输入参数  : enLastPsStatus -- 上次PS服务状态

 输出参数  : 无
 返 回 值  : VOS_TRUE -- 需要等待新IMS注册状态
             VOS_FALSE -- 不需要等待IMS注册状态

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月2日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsNeedtoWaitImsRegStatus(
    TAF_SPM_SERVICE_STATUS_ENUM_UINT8   enLastPsStatus
)
{
    TAF_SPM_SERVICE_STATUS_ENUM_UINT8   enCurrPsStatus;
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoicePerferred;
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstNwCapInfo = VOS_NULL_PTR;

    /* 获取当前网络能力 */
    pstNwCapInfo = TAF_SDC_GetLteNwCapInfo();

    /* 获取当前的PS服务状态 */
    enCurrPsStatus = (TAF_SPM_SERVICE_STATUS_ENUM_UINT8)TAF_SDC_GetPsServiceStatus();

    /* 获取语音优先域设置 */
    enVoicePerferred = TAF_SDC_GetVoiceDomain();

    if ((TAF_SPM_SERVICE_STATUS_NORMAL_SERVICE == enCurrPsStatus)
     && (enCurrPsStatus                        != enLastPsStatus)
     && (TAF_SDC_NW_IMS_VOICE_SUPPORTED        == pstNwCapInfo->enNwImsVoCap)
     && (TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY      == enVoicePerferred))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppCallModifyReqBasedOnCsOverIp
 功能描述  : SPM收到MN_CALL_APP_CALL_MODIFY_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppCallModifyReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    /* 发送ID_SPM_IMSA_CALL_MODIFY_REQ给IMSA处理 */
    TAF_SPM_SendImsaCallModifyReq((MN_CALL_APP_REQ_MSG_STRU *)pstMsg);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppCallAnswerRemoteModifyReqBasedOnCsOverIp
 功能描述  : SPM收到MN_CALL_APP_CALL_ANSWER_REMOTE_MODIFY_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月16日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppCallAnswerRemoteModifyReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    /* 发送ID_SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ给IMSA处理 */
    TAF_SPM_SendImsaCallAnswerRemoteModifyReq((MN_CALL_APP_REQ_MSG_STRU *)pstMsg);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppEconfDialReqBasedOnCsOverIp
 功能描述  : SPM收到TAF_CALL_APP_ECONF_DIAL_REQ的处理
 输入参数  : pstMsg       :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月28日
    作    者   : f00179208
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppEconfDialReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg  = VOS_NULL_PTR;

    pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    if (VOS_TRUE == pstAppMsg->unParm.stEconfDial.ucImsInvitePtptFlag)
    {
        /* 发送ID_SPM_IMSA_CALL_ECONF_ADD_USERS_REQ给IMSA处理 */
        TAF_SPM_SendImsaEconfAddUsersReq((MN_CALL_APP_REQ_MSG_STRU *)pstMsg);
        return VOS_TRUE;
    }

    /* 发送ID_SPM_IMSA_CALL_ECONF_DIAL_REQ给IMSA处理 */
    TAF_SPM_SendImsaEconfDialReq((MN_CALL_APP_REQ_MSG_STRU *)pstMsg);
    return VOS_TRUE;
}

#endif

/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_ProcCcSrvReqProtectTimerExpired
 功能描述  : CC业务保护定时器超时处理，收到该消息后，发送失败给业务请求发送方，
             随后释放缓存消息

 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 消息已处理
             VOS_FALSE-- 消息未处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月24日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2015年8月3日
    作    者   : n00269697
    修改内容   : DTS2015072802941，CC业务保护定时器超时，如果非PS ONLY，尝试域
                 选择到NAS信令进行处理
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcCcSrvReqProtectTimerExpired(VOS_VOID)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsg = VOS_NULL_PTR;
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain;
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSpmSrvReqType;
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;

    enVoiceDomain = TAF_SDC_GetVoiceDomain();

    if (TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY == enVoiceDomain)
    {
        /* get first index message address */
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);

        /* indicate sender that CC service request is failure */
        TAF_SPM_SendCcServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_CS_CAUSE_DOMAIN_SELECTION_TIMER_EXPIRED);

        /* clear the first cached message in queue */
        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);

        /* log service domain selection infomation */
        TAF_SPM_LogSrvDomainSelQueueInfo();

#if (FEATURE_IMS == FEATURE_ON)
        TAF_SPM_SetEcallHangUpImsFlag(VOS_FALSE);
#endif

        return VOS_TRUE;
    }

    /* 非PS ONLY，尝试域选择到NAS信令进行处理*/

    /* get first index message address */
    pstCachedMsg          = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);

    /* 如果当前RF available标志为FALSE, 释放缓存中的消息 */
    enSpmSrvReqType = TAF_SPM_GetServiceRequestType((struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]));

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));

    if (VOS_FALSE == TAF_SPM_GetRfAvailInfo(enSpmSrvReqType, &stSrvAcqRatList))
    {
        TAF_SPM_SendCcServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_CS_CAUSE_DOMAIN_SELECTION_TIMER_EXPIRED);

        /* clear the first cached message in queue */
        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);

        /* log service domain selection infomation */
        TAF_SPM_LogSrvDomainSelQueueInfo();

        return VOS_TRUE;
    }

    (VOS_VOID)TAF_SPM_ProcReqMsgBasedOnNasSignalling(pstCachedMsg->stMsgEntry.ulEventType,
                                           (struct MsgCB*)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]));

    TAF_SPM_UpdateServiceCtrlEntryMsg(pstCachedMsg->stMsgEntry.ulEventType,
                                      (struct MsgCB*)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]));

    TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

    /* clear the first cached message in queue */
    TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);

    TAF_SPM_LogSrvDomainSelQueueInfo();

    /* message need to be processed further by call module, so return VOS_FALSE
       需要替换入口消息
    */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSmsSrvReqProtectTimerExpired
 功能描述  : SMS业务保护定时器超时处理，收到该消息后，发送失败给业务请求发送方，
             随后释放缓存消息

 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 消息已处理
             VOS_FALSE-- 消息未处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月24日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年12月31日
    作    者   : y00245242
    修改内容   : 增加换域重拨功能
  3.日    期   : 2015年8月3日
    作    者   : n00269697
    修改内容   : DTS2015072802941，SMS业务保护定时器超时，如果非SMMA
                 消息，尝试域选择到NAS信令进行处理
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcSmsSrvReqProtectTimerExpired(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           i;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsg = VOS_NULL_PTR;
    MN_APP_MSG_SEND_REQ_STRU           *pstAppMsg  = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pstRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    VOS_UINT32                          ulEventType;
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSpmSrvReqType;
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;
    usClientId     = (VOS_UINT16)pstRcvTimerMsg->ulPara;


    /* 如果当前RF available标志为FALSE, 释放缓存中的消息 */
    pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(0);

    pstAppMsg    = (MN_APP_MSG_SEND_REQ_STRU *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]);

    enSpmSrvReqType = TAF_SPM_GetServiceRequestType((struct MsgCB *)pstAppMsg);

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));

    if (VOS_FALSE == TAF_SPM_GetRfAvailInfo(enSpmSrvReqType, &stSrvAcqRatList))
    {
        for (i = 0; i < TAF_SPM_GetSmsMsgQueueNum(); i++)
        {
            pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(i);

            pstAppMsg    = (MN_APP_MSG_SEND_REQ_STRU *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]);

            if ((pstAppMsg->usClientId                                   == usClientId)
             && (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_SPM_SMMA_IND) != pstCachedMsg->stMsgEntry.ulEventType))
             {
                TAF_SPM_SendSmsServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                                 (struct MsgCB *)pstAppMsg,
                                                 MN_ERR_CLASS_SMS_DOMAIN_SELECTION_TIMER_EXPIRED);

                TAF_SPM_FreeSpecificedIndexMessageInSmsQueue(i);
             }
        }

        TAF_SPM_LogSrvDomainSelQueueInfo();

        return VOS_TRUE;
    }

    /* 查找起动保护定时器消息 */
    for (i = 0; i < TAF_SPM_GetSmsMsgQueueNum(); i++)
    {
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(i);

        pstAppMsg    = (MN_APP_MSG_SEND_REQ_STRU *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]);

        ulEventType  = pstCachedMsg->stMsgEntry.ulEventType;

        /* 根据client ID查找缓存消息, SMMA消息不起域选择定时器，因此不care */
        if ((pstAppMsg->usClientId == usClientId)
         && (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_SPM_SMMA_IND) != ulEventType))
        {
            (VOS_VOID)TAF_SPM_ProcReqMsgBasedOnNasSignalling(pstCachedMsg->stMsgEntry.ulEventType,
                                           (struct MsgCB*)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]));

            TAF_SPM_UpdateServiceCtrlEntryMsg(pstCachedMsg->stMsgEntry.ulEventType,
                                      (struct MsgCB*)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]));

            TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

            TAF_SPM_FreeSpecificedIndexMessageInSmsQueue(i);

            break;
        }
    }

    TAF_SPM_LogSrvDomainSelQueueInfo();

    /* message need to be processed further by call module, so return VOS_FALSE */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSsSrvReqProtectTimerExpired
 功能描述  : SS业务保护定时器超时处理，收到该消息后，发送失败给业务请求发送方，
             随后释放缓存消息

 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 消息已处理
             VOS_FALSE-- 消息未处理完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月24日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2015年8月3日
    作    者   : n00269697
    修改内容   : DTS2015072802941，SS业务保护定时器超时，如果非PS ONLY，尝试域
                 选择到NAS信令进行处理
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcSsSrvReqProtectTimerExpired(VOS_VOID)
{
    TAF_SPM_CACHE_MSG_INFO_STRU                            *pstCachedMsg = VOS_NULL_PTR;
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32                        enVoiceDomain;
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8                         enSpmSrvReqType;
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU                           stSrvAcqRatList;

    enVoiceDomain = TAF_SDC_GetVoiceDomain();

    if (TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY == enVoiceDomain)
    {
        /* get the first cached message in queue */
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(0);

        TAF_SPM_SendSsServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_ERR_SS_DOMAIN_SELECTION_TIMER_EXPIRED);

        /* clear the first cached message in queue */
        TAF_SPM_FreeSpecificedIndexMessageInSsQueue(0);

        /* log service domain selection infomation */
        TAF_SPM_LogSrvDomainSelQueueInfo();

        return VOS_TRUE;
    }

    /* 非PS ONLY，尝试域选择到NAS信令进行处理*/

    /* get the first cached message in queue */
    pstCachedMsg      = TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(0);

    /* 如果当前RF available标志为FALSE, 释放缓存中的消息 */
    enSpmSrvReqType = TAF_SPM_GetServiceRequestType((struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]));

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));

    if (VOS_FALSE == TAF_SPM_GetRfAvailInfo(enSpmSrvReqType, &stSrvAcqRatList))
    {
        TAF_SPM_SendSsServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_ERR_SS_DOMAIN_SELECTION_TIMER_EXPIRED);

        /* clear the first cached message in queue */
        TAF_SPM_FreeSpecificedIndexMessageInSsQueue(0);

        /* log service domain selection infomation */
        TAF_SPM_LogSrvDomainSelQueueInfo();

        return VOS_TRUE;
    }

    (VOS_VOID)TAF_SPM_ProcReqMsgBasedOnNasSignalling(pstCachedMsg->stMsgEntry.ulEventType,
                                           (struct MsgCB*)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]));

    TAF_SPM_UpdateServiceCtrlEntryMsg(pstCachedMsg->stMsgEntry.ulEventType,
                                      (struct MsgCB*)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]));

    TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

    /* clear the first cached message in queue */
    TAF_SPM_FreeSpecificedIndexMessageInSsQueue(0);

    TAF_SPM_LogSrvDomainSelQueueInfo();

    /* message need to be processed further by call module, so return VOS_FALSE */
    return VOS_FALSE;
}
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */

/*****************************************************************************
 函 数 名  : TAF_SPM_SendCcServiceRequetFail
 功能描述  : 指示用户CC业务请求失败

 输入参数  : ulEventType －－消息事件类型
             pstMsg －－ 消息地址
             enCause -- 业务请求失败原因值

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月10日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2014年11月28日
    作    者   : f00179208
    修改内容   : enhanced conference项目
*****************************************************************************/
VOS_VOID TAF_SPM_SendCcServiceRequetFail(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstAtMsg  = VOS_NULL_PTR;
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstStkMsg = VOS_NULL_PTR;

    /* Notify sender that CC service request is failure */
    if (TAF_BuildEventType(WUEPS_PID_AT, MN_CALL_APP_ORIG_REQ) == ulEventType)
    {
        pstAtMsg = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
        {
            TAF_XCALL_SndCallOrigCnf(enCause,
                                     pstAtMsg->ulSenderPid,
                                     pstAtMsg->clientId,
                                     pstAtMsg->unParm.stOrig.enCallType);

            return;
        }
#endif

        TAF_CALL_SendCallOrigCnf(pstAtMsg->clientId, pstAtMsg->opId, pstAtMsg->callId, enCause);

#if (FEATURE_ON == FEATURE_PTM)
        /* 记录CS呼叫异常log */
        MN_CALL_CsCallErrRecord(0, enCause);
#endif
    }
    else if (TAF_BuildEventType(MAPS_STK_PID, STK_CALL_CALLORIG_REQ) == ulEventType)
    {
        pstStkMsg = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstMsg;
        TAF_CALL_SendCallOrigCnf(pstStkMsg->usClientId, pstStkMsg->opID, pstStkMsg->callID, enCause);

#if (FEATURE_ON == FEATURE_PTM)
        /* 记录CS呼叫异常log */
        MN_CALL_CsCallErrRecord(0, enCause);
#endif
    }
#if (FEATURE_ON == FEATURE_IMS)
    else if (TAF_BuildEventType(WUEPS_PID_AT, TAF_CALL_APP_ECONF_DIAL_REQ) == ulEventType)
    {
        pstAtMsg = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;
        TAF_SPM_SendAtEconfDialCnf(pstAtMsg->clientId, pstAtMsg->opId, pstAtMsg->callId, enCause);

#if (FEATURE_ON == FEATURE_PTM)
        /* 记录CS呼叫异常log */
        MN_CALL_CsCallErrRecord(0, enCause);
#endif
    }
#endif
    else
    {
        /* nothing to do */
    }
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SendSmsServiceRequetFail
 功能描述  : 指示用户SMS业务请求失败

 输入参数  : ulEventType －－消息事件类型
             pstMsg －－ 消息地址
             ulCause -- 业务请求失败原因值

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月10日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SendSmsServiceRequetFail(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    VOS_UINT32                          ulCause
)
{
    MN_APP_MSG_SEND_REQ_STRU           *pstAppMsg = VOS_NULL_PTR;

    pstAppMsg = (MN_APP_MSG_SEND_REQ_STRU *)pstMsg;

    switch (ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_AT, MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM):
        case TAF_BuildEventType(WUEPS_PID_AT, MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT):
        case TAF_BuildEventType(MAPS_STK_PID, STK_MSG_SEND_REQ):
            /* Notify sender that SMS service request is failure */
            MN_SendClientResponse(pstAppMsg->usClientId, pstAppMsg->opID, ulCause);
            break;

         default:
            break;
    }

}

/*****************************************************************************
 函 数 名  : TAF_SPM_SendSsServiceRequetFail
 功能描述  : 指示用户SS业务请求失败

 输入参数  : ulEventType －－消息事件类型
             pstMsg －－ 消息地址
             errorCode －－ 业务请求原因值

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月10日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SendSsServiceRequetFail(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_SS_ERROR                        errorCode
)
{
    MN_APP_MSG_SEND_REQ_STRU           *pstAppMsg  = VOS_NULL_PTR;

    pstAppMsg  = (MN_APP_MSG_SEND_REQ_STRU *)pstMsg;

    switch (ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_AT,  TAF_MSG_REGISTERSS_MSG):
        case TAF_BuildEventType(WUEPS_PID_AT,  TAF_MSG_ERASESS_MSG):
        case TAF_BuildEventType(WUEPS_PID_AT,  TAF_MSG_ACTIVATESS_MSG):
        case TAF_BuildEventType(WUEPS_PID_AT,  TAF_MSG_DEACTIVATESS_MSG):
        case TAF_BuildEventType(WUEPS_PID_AT,  TAF_MSG_INTERROGATESS_MSG):
        case TAF_BuildEventType(WUEPS_PID_AT,  TAF_MSG_PROCESS_USS_MSG):
        case TAF_BuildEventType(WUEPS_PID_AT,  TAF_MSG_REGPWD_MSG):
        case TAF_BuildEventType(WUEPS_PID_AT,  TAF_MSG_ERASECCENTRY_MSG):
        case TAF_BuildEventType(MAPS_STK_PID,  STK_SS_REGISTERSS_REQ):
        case TAF_BuildEventType(MAPS_STK_PID,  STK_SS_ERASESS_REQ):
        case TAF_BuildEventType(MAPS_STK_PID,  STK_SS_ACTIVATESS_REQ):
        case TAF_BuildEventType(MAPS_STK_PID,  STK_SS_DEACTIVATESS_REQ):
        case TAF_BuildEventType(MAPS_STK_PID,  STK_SS_INTERROGATESS_REQ):
        case TAF_BuildEventType(MAPS_STK_PID,  STK_SS_USSD_REQ):

            /* 向AT或STK发送失败结果,携带cause  */
            MN_SendClientResponse(pstAppMsg->usClientId, pstAppMsg->opID, errorCode);
            break;

        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcReqMsgBasedOnNasSignalling
 功能描述  : 处理基于NAS信令发送的APP的请求消息,仅需要对SMS的请求消息做处理，
             设置消息发送的信令类型为NAS SIGNALLING
 输入参数  : ulEventType -- 由PID与message name组成
             pstRcvMsg   -- 消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE   消息息已处理完成
             VOS_FALSE  消息未处理完成

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月31日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2014年06月16日
   作    者   : f00179208
   修改内容   : VTLTE项目
 3.日    期   : 2014年6月23日
   作    者   : z00161729
   修改内容   : DSDS III新增
 4.日    期   : 2014年11月28日
   作    者   : f00179208
   修改内容   : 增强型多方通话
 5.日    期   : 2015年6月27日
   作    者   : w00242748
   修改内容   : DTS2015062606295:1X no rf,syscfg设置1x不支持，atd117;会触发1X搜网
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcReqMsgBasedOnNasSignalling(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstRcvMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstSmsMsg    = VOS_NULL_PTR;
    MN_MSG_SEND_PARM_STRU              *pstMsgSnd    = VOS_NULL_PTR;
    MN_MSG_SEND_FROMMEM_PARM_STRU      *pstSndMemMsg = VOS_NULL_PTR;

    MN_CALL_APP_REQ_MSG_STRU           *pstCallMsg   = VOS_NULL_PTR;
    MN_CALL_ORIG_PARAM_STRU            *pstOrigReq   = VOS_NULL_PTR;
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU *pstServiceCtrlCfgInfo = VOS_NULL_PTR;


    /* only care SMS request messages from APP */
    switch (ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_AT, MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT):
        case TAF_BuildEventType(MAPS_STK_PID, STK_MSG_SEND_REQ):
            pstSmsMsg = (MN_APP_REQ_MSG_STRU *)pstRcvMsg;
            pstMsgSnd = (MN_MSG_SEND_PARM_STRU *)(pstSmsMsg->aucContent);

            /* set SMS sending flag to GUL stack */
            pstMsgSnd->enMsgSignallingType = TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING;
            break;

        case TAF_BuildEventType(WUEPS_PID_AT, MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM):
            pstSmsMsg    = (MN_APP_REQ_MSG_STRU *)pstRcvMsg;
            pstSndMemMsg = (MN_MSG_SEND_FROMMEM_PARM_STRU *)(pstSmsMsg->aucContent);

            /* set SMS sending flag to GUL stack */
            pstSndMemMsg->enMsgSignallingType = TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING;
            break;

        case TAF_BuildEventType(WUEPS_PID_AT, MN_CALL_APP_ORIG_REQ):
            pstServiceCtrlCfgInfo   = TAF_SPM_GetServiceCtrlCfgInfoAddr();
            pstCallMsg              = (MN_CALL_APP_REQ_MSG_STRU *)pstRcvMsg;
            pstOrigReq              = (MN_CALL_ORIG_PARAM_STRU *)(&pstCallMsg->unParm);

            /* PS域的视频在域选择完后需要转成普通的语音呼叫 */
            if (TAF_SPM_IS_PS_VIDEO(pstOrigReq->enCallType,
                                    pstServiceCtrlCfgInfo->enVpCfgState,
                                    pstOrigReq->enVoiceDomain))
            {
                pstOrigReq->enCallType = MN_CALL_TYPE_VOICE;
            }
            break;

        default:
            break;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcCcMsgQueue
 功能描述  : 处理缓存CC消息的队列中的消息。当队列中有消息存在时，运行域选择，
             除域选择结果为继续buffer message外，其他结果都停止定时器，清除
             队列中缓存的消息；

 输入参数  : 无
 输出参数  : pEnDomainSelType -- 指针，返回域选择结果类型
 返 回 值  : VOS_TRUE -- 消息处理完毕
             VOS_FALSE -- 消息未处理完成，待进一步处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月25日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2014年7月8日
    作    者   : w00176964
    修改内容   : 函数位置调整以及放开IMS宏控制
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcCcMsgQueue(TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 *pEnDomainSelRslt)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstMsgInfo = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    /* get first index message address */
    pstMsgInfo          = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);
    *pEnDomainSelRslt   = TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;

#if (FEATURE_ON == FEATURE_IMS)
    /* execute doman selection for cached message */
    *pEnDomainSelRslt = TAF_SPM_ProcCcDomainSelection(pstMsgInfo->stMsgEntry.ulEventType,
                                                      (struct MsgCB*)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]));

    /* if the result is buffer message, nothing to do */
    if (TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE == *pEnDomainSelRslt)
    {
        return VOS_TRUE;
    }

    /* process domain selection result */
    ulRst = TAF_SPM_ProcBufferedDomainSelectionResult(&(pstMsgInfo->stMsgEntry), *pEnDomainSelRslt);

#else

    (VOS_VOID)TAF_SPM_ProcReqMsgBasedOnNasSignalling(pstMsgInfo->stMsgEntry.ulEventType,
                                           (struct MsgCB*)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]));

    TAF_SPM_UpdateServiceCtrlEntryMsg(pstMsgInfo->stMsgEntry.ulEventType,
                                      (struct MsgCB*)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]));

    TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

    /* message need to be processed further by call module, so return VOS_FALSE */
    ulRst = VOS_FALSE;
#endif

    pstAppMsg = (MN_APP_REQ_MSG_STRU *)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]);

    /* stop CC service protect timer with client ID */
    TAF_SPM_StopTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

    /* clear the first cached message in queue */
    TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);

    return ulRst;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSmsMsgQueue
 功能描述  : 处理缓存SMS消息的队列中的消息。当队列中有消息存在时，运行域选择，
             除域选择结果为继续buffer message外，其他结果都停止定时器，清除
             队列中缓存的消息;

 输入参数  : 无
 输出参数  : pEnDomainSelType -- 指针，返回域选择结果类型
 返 回 值  : VOS_TRUE -- 消息处理完毕
             VOS_FALSE -- 消息未处理完成，待进一步处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月25日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年1月2日
    作    者   : y00245242
    修改内容   : 增加域选择换域重拨功能
  3.日    期   : 2014年7月8日
    作    者   : w00176964
    修改内容   : 函数位置调整以及放开IMS宏控制
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcSmsMsgQueue(TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 *pEnDomainSelRslt)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstMsgInfo = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    *pEnDomainSelRslt   = TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING;

#if (FEATURE_ON == FEATURE_IMS)
    /* run SMS domain selection */
    *pEnDomainSelRslt = TAF_SPM_ProcSmsDomainSelection();

    /* if the result is buffer message, nothing to do */
    if (TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE == *pEnDomainSelRslt)
    {
        return VOS_TRUE;
    }
#endif

    /* get the first cached message in queue */
    pstMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(0);

#if (FEATURE_ON == FEATURE_IMS)
    /* SMMA消息需要特殊处理: 不需要停止定时器且是发送外部消息给MSG模块 */
    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_SPM_SMMA_IND) == pstMsgInfo->stMsgEntry.ulEventType)
    {
        TAF_SPM_ProcSmmaIndDomainSelectionResult(pstMsgInfo->stMsgEntry.ulEventType,
                                                 (struct MsgCB *)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]),
                                                 *pEnDomainSelRslt);

        ulRst = VOS_TRUE;
    }
    else
#endif
    {
#if (FEATURE_ON == FEATURE_IMS)
        /* process domain selection result */
        ulRst = TAF_SPM_ProcBufferedDomainSelectionResult(&(pstMsgInfo->stMsgEntry), *pEnDomainSelRslt);
#else
        (VOS_VOID)TAF_SPM_ProcReqMsgBasedOnNasSignalling(pstMsgInfo->stMsgEntry.ulEventType,
                                               (struct MsgCB*)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]));

        TAF_SPM_UpdateServiceCtrlEntryMsg(pstMsgInfo->stMsgEntry.ulEventType,
                                          (struct MsgCB*)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]));

        TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

        /* message need to be processed further by call module, so return VOS_FALSE */
        ulRst = VOS_FALSE;
#endif

        /* stop SMS service protect timer */
        pstAppMsg = (MN_APP_REQ_MSG_STRU *)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]);
        TAF_SPM_StopTimer(TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

    }

    /* clear the first cached message in queue */
    TAF_SPM_FreeSpecificedIndexMessageInSmsQueue(0);

    return ulRst;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcSsMsgQueue
 功能描述  : 处理缓存SS消息的队列中的消息。当队列中有消息存在时，运行域选择，
             除域选择结果为继续buffer message外，其他结果都停止定时器，清除
             队列中缓存的消息；

 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 消息处理完毕
             VOS_FALSE -- 消息未处理完成，待进一步处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月25日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2014年7月8日
    作    者   : w00176964
    修改内容   : 函数位置调整以及放开IMS宏控制
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcSsMsgQueue(VOS_VOID)
{
    TAF_SPM_CACHE_MSG_INFO_STRU                            *pstMsgInfo = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                                    *pstAppMsg  = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_IMS)
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;
#endif
    VOS_UINT32                                              ulRst;

    /* get the first cached message in queue */
    pstMsgInfo      = TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(0);

#if (FEATURE_ON == FEATURE_IMS)
    /* run SS domain selection */
    enDomainSelRslt = TAF_SPM_ProcSsDomainSelection(pstMsgInfo->stMsgEntry.ulEventType,
                                                    (struct MsgCB*)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]));

    /* if the result is buffer message, nothing to do */
    if (TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE == enDomainSelRslt)
    {
        return VOS_TRUE;
    }

    /* process domain selection result */
    ulRst = TAF_SPM_ProcBufferedDomainSelectionResult(&(pstMsgInfo->stMsgEntry), enDomainSelRslt);

#else

    (VOS_VOID)TAF_SPM_ProcReqMsgBasedOnNasSignalling(pstMsgInfo->stMsgEntry.ulEventType,
                                           (struct MsgCB*)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]));

    TAF_SPM_UpdateServiceCtrlEntryMsg(pstMsgInfo->stMsgEntry.ulEventType,
                                      (struct MsgCB*)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]));

    TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

    /* message need to be processed further by call module, so return VOS_FALSE */
    ulRst = VOS_FALSE;

#endif

    /* stop SS service protect timer */
    pstAppMsg = (MN_APP_REQ_MSG_STRU *)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]);
    TAF_SPM_StopTimer(TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

    /* clear the first cached message in queue */
    TAF_SPM_FreeSpecificedIndexMessageInSsQueue(0);

    return ulRst;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcBufferedMsgInQueue
 功能描述  : 处理缓存在队列中的消息，确认CC/SMS/SS缓存对列中是否有消息，如果有
             运行对应的消息队列处理函数。
             如果CC缓存消息域选择结果不为缓存消息，且有缓存的SMS或SS请求消息，
             发送内部域选择指示消息给自己，否则继续处理SMS缓存消息，同样，如果
             SMS缓存消息域选择结果不为缓存，且有SS请求消息缓存，发送域选择指示
             给自己，否则返回

 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE -- 消息处理完毕
             VOS_FALSE -- 消息未处理完成，待进一步处理

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月24日
    作    者   : y00245242
    修改内容   : 新生成函数
  2.日    期   : 2013年1月2日
    作    者   : y00245242
    修改内容   : 增加换域重拨功能
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcBufferedMsgInQueue(VOS_VOID)
{
    VOS_UINT32                                              ulRst;
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;
    VOS_UINT8                                               ucSmsMsgQueueNum;
    VOS_UINT8                                               ucSsMsgQueueNum;

    ulRst = VOS_TRUE;

    if (0 != TAF_SPM_GetCcMsgQueueNum())
    {
        enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_BUTT;

        ulRst = TAF_SPM_ProcCcMsgQueue(&enDomainSelRslt);

        /* check if domain selection type is buffer message */
        if (TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE != enDomainSelRslt)
        {
            /* if SS or SMS message queue is not null, send domain selection indication message to self */
            ucSmsMsgQueueNum = TAF_SPM_GetSmsMsgQueueNum();
            ucSsMsgQueueNum  = TAF_SPM_GetSsMsgQueueNum();
            if ((0 != ucSmsMsgQueueNum) || (0 != ucSsMsgQueueNum))
            {
                TAF_SPM_SndInternalDomainSelectionInd();
            }

            /* log service domain selection infomation */
            TAF_SPM_LogSrvDomainSelQueueInfo();

            return ulRst;
        }
    }

    /* continue to process SMS message queue */
    if (0 != TAF_SPM_GetSmsMsgQueueNum())
    {
        enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_BUTT;

        ulRst = TAF_SPM_ProcSmsMsgQueue(&enDomainSelRslt);

        /* check if domain selection type is buffer message */
        if (TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE != enDomainSelRslt)
        {
            /* if SS or SMS message queue is not null, send domain selection indication message to self */
            ucSmsMsgQueueNum = TAF_SPM_GetSmsMsgQueueNum();
            ucSsMsgQueueNum  = TAF_SPM_GetSsMsgQueueNum();
            if ((0 != ucSmsMsgQueueNum)
             || (0 != ucSsMsgQueueNum))
            {
                TAF_SPM_SndInternalDomainSelectionInd();
            }

            /* log service domain selection infomation */
            TAF_SPM_LogSrvDomainSelQueueInfo();

            return ulRst;
        }
    }

    /* continue to process SS message queue */
    if (0 != TAF_SPM_GetSsMsgQueueNum())
    {
        ulRst = TAF_SPM_ProcSsMsgQueue();
    }

    /* log service domain selection infomation */
    TAF_SPM_LogSrvDomainSelQueueInfo();

    return ulRst;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_ProcServiceRequestFail
 功能描述  : 域选择结果为失败或已有缓存消息时，给AT/STK回复失败

 输入参数  : ulEventType -- 消息事件类型
             pstMsg -- 消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE -- 消息已处理
             VOS_FALSE -- 消息未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcServiceRequestFail(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType;

    enSrvReqType = TAF_SPM_GetServiceRequestType(pstMsg);

    switch (enSrvReqType)
    {
        case TAF_SPM_SRV_REQ_TYPE_CALL:
            TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_DOMAIN_SELECTION_FAILURE);
            break;

        case TAF_SPM_SRV_REQ_TYPE_SMS:
            TAF_SPM_SendSmsServiceRequetFail(ulEventType, pstMsg, MN_ERR_CLASS_SMS_DOMAIN_SELECTION_FAILURE);
            break;

        case TAF_SPM_SRV_REQ_TYPE_SS:
            TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, TAF_ERR_SS_DOMAIN_SELECTION_FAILURE);
            break;

        default:
            break;

    }
    return (VOS_TRUE);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_StartCcServiceReqProtectTimer
 功能描述  : 启动cc服务保护定时器
 输入参数  : ulRfAvailable -- RF
             enVoicePerferred -- VOICE优先域
             usClientId -- 定时器关联的client ID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_StartCcServiceReqProtectTimer(
    VOS_UINT32                          ulRfAvailable,
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoicePerferred,
    VOS_UINT16                          usClientId
)
{
    VOS_UINT32                          ucProtectTimerLen;

    ucProtectTimerLen                   = TAF_Spm_GetBufferCcProtectTimerLen();

    if ( (VOS_FALSE                         == ulRfAvailable)
      || (TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY  == enVoicePerferred) )
    {
        ucProtectTimerLen = TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER_VAL;
    }

    /* 异常保护: 如果ucProtectTimerLen在nv中配置为0，应该走nas信令 */
    if (0 == ucProtectTimerLen)
    {
        ucProtectTimerLen = TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL;
    }

    TAF_SPM_StartTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER,
                       ucProtectTimerLen,
                       usClientId);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_StartSmsServiceReqProtectTimer
 功能描述  : 启动sms服务保护定时器
 输入参数  : ulRfAvailable -- RF
             enVoicePerferred -- VOICE优先域
             usClientId -- 定时器关联的client ID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_StartSmsServiceReqProtectTimer(
    VOS_UINT32                          ulRfAvailable,
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoicePerferred,
    VOS_UINT16                          usClientId
)
{
    VOS_UINT32                          ucProtectTimerLen = TAF_SPM_GetBufferSmsProtectTimerLen();

#if (FEATURE_IMS == FEATURE_ON)
    VOS_UINT8                           ucImsSmsSndFlg = TAF_SPM_GetImsSmsSendingFlg();
#endif


    if ( (VOS_FALSE                         == ulRfAvailable)
#if (FEATURE_IMS == FEATURE_ON)
      || (VOS_TRUE                          == ucImsSmsSndFlg)
#endif
      || (TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY  == enVoicePerferred))
    {
        ucProtectTimerLen = TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER_VAL;
    }

    /* 异常保护: 如果ucProtectTimerLen在nv中配置为0，应该走nas信令 */
    if (0 == ucProtectTimerLen)
    {
        ucProtectTimerLen = TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL;
    }

    TAF_SPM_StartTimer(TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER,
                       ucProtectTimerLen,
                       usClientId);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_StartCcServiceReqProtectTimer
 功能描述  : 启动SS服务保护定时器
 输入参数  : ulRfAvailable -- RF
             enVoicePerferred -- VOICE优先域
             usClientId -- 定时器关联的client ID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_StartSsServiceReqProtectTimer(
    VOS_UINT32                          ulRfAvailable,
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoicePerferred,
    VOS_UINT16                          usClientId
)
{
    VOS_UINT32                          ucProtectTimerLen;

    ucProtectTimerLen                   = TAF_SPM_GetBufferSsProtectTimerLen();

    if ( (VOS_FALSE                         == ulRfAvailable)
      || (TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY  == enVoicePerferred) )
    {
        ucProtectTimerLen = TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER_VAL;
    }

    /* 异常保护: 如果ucProtectTimerLen在nv中配置为0，应该走nas信令 */
    if (0 == ucProtectTimerLen)
    {
        ucProtectTimerLen = TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL;
    }

    TAF_SPM_StartTimer(TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER,
                       ucProtectTimerLen,
                       usClientId);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_BufferAppRequestMessage
 功能描述  : 根据业务请求类型，保存消息到对应的缓存消息queue中，并启动对应的业务
             保护定时器。如果queue已满，退出保存

 输入参数  : ulEventType -- 消息事件类型
             pstMsg -- 消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE -- 保存成功
             VOS_FALSE -- queue中已经有消息存在，返回失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_BufferAppRequestMessage(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType;
    VOS_UINT32                          ulRst;
    MN_APP_REQ_MSG_STRU                *pstAppMsg = VOS_NULL_PTR;

    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;
    VOS_UINT32                          ulRfAvailable;
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoicePerferred;

    ulRst        = VOS_FALSE;

    /* get service request type */
    enSrvReqType = TAF_SPM_GetServiceRequestType(pstMsg);

    pstAppMsg    = (MN_APP_REQ_MSG_STRU *)pstMsg;

    PS_MEM_SET(&stSrvAcqRatList, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
    ulRfAvailable                       = TAF_SPM_GetRfAvailInfo(enSrvReqType, &stSrvAcqRatList);
    enVoicePerferred                    = TAF_SDC_GetVoiceDomain();

    switch (enSrvReqType)
    {
        case TAF_SPM_SRV_REQ_TYPE_CALL:
            /* queue is full? */
            if (VOS_FALSE == TAF_SPM_IsCcMsgQueueFull())
            {
                /* put message in queue */
                ulRst = TAF_SPM_PutMessageToCcQueue(ulEventType, pstMsg);

                /* message is cached successfully, start timer */
                if (VOS_TRUE == ulRst)
                {
                    TAF_SPM_StartCcServiceReqProtectTimer(ulRfAvailable, enVoicePerferred, pstAppMsg->clientId);
                }
            }
            break;

        case TAF_SPM_SRV_REQ_TYPE_SMS:
            if (VOS_FALSE == TAF_SPM_IsSmsMsgQueueFull())
            {
                ulRst = TAF_SPM_PutMessageToSmsQueue(ulEventType, pstMsg);

                /* message is cached successfully, start timer */
                if (VOS_TRUE == ulRst)
                {
                    TAF_SPM_StartSmsServiceReqProtectTimer(ulRfAvailable, enVoicePerferred, pstAppMsg->clientId);

                }
            }
            break;

        case TAF_SPM_SRV_REQ_TYPE_SS:
            if (VOS_FALSE == TAF_SPM_IsSsMsgQueueFull())
            {
                ulRst = TAF_SPM_PutMessageToSsQueue(ulEventType, pstMsg);

                /* message is cached successfully, start timer */
                if (VOS_TRUE == ulRst)
                {
                    TAF_SPM_StartSsServiceReqProtectTimer(ulRfAvailable, enVoicePerferred, pstAppMsg->clientId);

                }
            }
            break;

        default:
            break;
    }

    /* log service domain selection infomation */
    TAF_SPM_LogSrvDomainSelQueueInfo();

    return (ulRst);
}

#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : TAF_SPM_IsEcallAllowedSelNasSignalling
 功能描述  : 当前ecall是否允许在走nas signalling
 输入参数  : enCallType -- 呼叫类型

 输出参数  : 无
 返 回 值  : VOS_FALSE － 呼叫不允许发起
             VOS_TRUE  － 呼叫允许发起
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年03月02日
   作    者   : j00174725
   修改内容   :
*****************************************************************************/
VOS_UINT32 TAF_SPM_IsEcallAllowedSelNasSignalling(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    TAF_SDC_CALL_MODE_ENUM_UINT8        enEcallMode;

    enEcallMode = TAF_SDC_GetCurCallMode();

    if (TAF_SDC_ECALL_ONLY == enEcallMode)
    {
        return VOS_TRUE;
    }
    else
    {
        if ( (TAF_SDC_ECALL_AND_NORMAL_CALL == enEcallMode)
          && ( (MN_CALL_TYPE_MIEC           == enCallType)
            || (MN_CALL_TYPE_AIEC           == enCallType)
            || (MN_CALL_TYPE_TEST           == enCallType)
            || (MN_CALL_TYPE_RECFGURATION   == enCallType)))
        {
             return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

