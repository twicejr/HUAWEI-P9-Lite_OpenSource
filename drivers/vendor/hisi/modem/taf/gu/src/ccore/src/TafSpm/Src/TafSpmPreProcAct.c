/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmPreProcAct.c
  版 本 号   : 初稿
  作    者   : s00217060
  生成日期   : 2013年12月14日
  最近修改   :
  功能描述   :预处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年12月14日
    作    者   : s00217060
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "MnCallApi.h"
#include "MnCallReqProc.h"
#include "TafLog.h"
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, begin */
#include "MnCallSendApp.h"
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-18, end */
#include "MnCallMnccProc.h"
#include "TafSpmServiceDomainSelProc.h"
#include "TafMmaCtx.h"
#include "TafSdcLib.h"
#include "TafSpmSndInternalMsg.h"
#include "SpmImsaInterface.h"
#include "TafSpmPreProcTbl.h"
#include "TafSpmPreProcAct.h"
#include "TafAgentInterface.h"
#include "TafSpmComFunc.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "CallImsaInterface.h"
#endif

#include "TafSpmRedial.h"
#include "TafSpmCtx.h"
#include "NasSms.h"
#include "TafSpmMntn.h"
#include "MnMsgApi.h"

#include "MnCall.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_PREPROC_ACT_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-22, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_IsCallAllowedInCurrentPhoneMode
 功能描述  : 根据呼叫类型以及当前的状态，确定是否允许发起该呼叫
 输入参数  : pstMsg -- 呼叫请求消息地址

 输出参数  : 无
 返 回 值  : VOS_FALSE － 呼叫不允许发起
             VOS_TRUE  － 呼叫允许发起
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年04月22日
   作    者   : y00245242
   修改内容   : 为eCall特性增加
*****************************************************************************/
VOS_UINT32 TAF_SPM_IsCallAllowedInCurrentPhoneMode(MN_CALL_APP_REQ_MSG_STRU *pstMsg)
{
#if (FEATURE_ON == FEATURE_ECALL)
    MN_CALL_TYPE_ENUM_U8                enCallType;
#endif
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhMode;

    enPhMode   = TAF_SDC_GetCurPhoneMode();

    if (TAF_PH_MODE_FULL == enPhMode)
    {
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_ECALL)
    /* 对于温保模式，MIEC或AIEC需要触发开机 */
    if (TAF_PH_MODE_LOWPOWER == enPhMode)
    {
        enCallType = pstMsg->unParm.stOrig.enCallType;

        if ((MN_CALL_TYPE_MIEC == enCallType)
         || (MN_CALL_TYPE_AIEC == enCallType))
        {
            return VOS_TRUE;
        }
    }
#endif

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : TAF_SPM_ProcMiecAndAiecReqInLowPower
 功能描述  : 在低功耗状态下，处理MIEC与AIEC Ecall呼叫请求。在低功耗时，缓存消息，
             触发开机。

 输入参数  : ulEventType   - 事件类型
             pstMsg        - 消息地址

 输出参数  :
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月22日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_SPM_ProcMiecAndAiecReqInLowPower(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;
    TAF_MMA_PHONE_MODE_PARA_STRU        stPhoneModePara;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq = VOS_NULL_PTR;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* 缓存eCall请求，并启动保护定时器TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER */
    ulRst = TAF_SPM_PutMessageToCcQueue(ulEventType, pstMsg);
    if (VOS_TRUE != ulRst)
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_ECALL_CACHE_MSG_FAIL);
        return;
    }

    /* 调用API接口TAF_MMA_PhoneModeSetReq(full mode)发送开机消息到MMA */
    PS_MEM_SET(&stPhoneModePara, 0x00, sizeof(TAF_MMA_PHONE_MODE_PARA_STRU));
    stPhoneModePara.PhMode  = TAF_PH_MODE_FULL;
    stPhoneModePara.PhReset = TAF_PH_OP_MODE_UNRESET;
    if (VOS_TRUE != TAF_MMA_PhoneModeSetReq(WUEPS_PID_TAF, INTERNAL_CLIENT_ID_SPM, 0, &stPhoneModePara))
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_ECALL_LOWERPOWER_POWER_ON_FAIL);

        /* 因为仅缓存一条消息，这儿释放队列中首个消息 */
        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);
        return;
    }

    TAF_SPM_StartTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER,
                       TI_TAF_SPM_CC_ECALL_REQ_PROTECT_TIMER_VAL,
                       pstAppReq->clientId);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcMiecAndAiecReqInOtherCallRunning
 功能描述  : 在有呼叫存在场景下，处理MIEC与AIEC Ecall呼叫请求
 输入参数  : ulEventType   - 事件类型
             pstMsg        - 消息地址

 输出参数  :
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月22日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_SPM_ProcMiecAndAiecReqInOtherCallRunning(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq    = VOS_NULL_PTR;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* 如果缓存有消息，清除缓存，确保eCall呼叫的发起 */
    if (TAF_SPM_GetCcMsgQueueNum() > 0)
    {
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);

        /* 清除缓存时，先通知应用，缓存的呼叫发起失败 */
        TAF_SPM_SendCcServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_CS_CAUSE_DOMAIN_SELECTION_TIMER_EXPIRED);

        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);
    }

    /* 缓存当前eCall请求消息 */
    (VOS_VOID)TAF_SPM_PutMessageToCcQueue(ulEventType, pstMsg);

    /* 启动呼叫业务请求保护定时器，如果定时超时，清除缓存，通知APP呼叫失败 */
    TAF_SPM_StartTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER,
                       TI_TAF_SPM_CC_ECALL_REQ_PROTECT_TIMER_VAL,
                       pstAppReq->clientId);

    /* 释放所有非紧急呼叫，确保后续eCall呼叫能正常发起, 收到TAF_CALL_TAF_REL_CALL_CNF后，发送缓存的
     * 呼叫请求
     */
    TAF_SPM_SndTafRelCallReq(pstAppReq->clientId, pstAppReq->opId, TAF_CALL_REL_CALL_ALL_NORMAL);
}

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_SPM_ProcMiecAndAiecReqInImsCallRunning
 功能描述  : 在有IMS呼叫存在场景下，处理MIEC与AIEC Ecall呼叫请求
 输入参数  : ulEventType   - 事件类型
             pstMsg        - 消息地址

 输出参数  :
 返 回 值  : VOS_VOID

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月04日
    作    者   : j00174725
    修改内容   : DTS2015021000591
*****************************************************************************/
VOS_VOID  TAF_SPM_ProcMiecAndAiecReqInImsCallRunning(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq    = VOS_NULL_PTR;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* 如果缓存有消息，清除缓存，确保eCall呼叫的发起 */
    if (TAF_SPM_GetCcMsgQueueNum() > 0)
    {
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);

        /* 清除缓存时，先通知应用，缓存的呼叫发起失败 */
        TAF_SPM_SendCcServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_CS_CAUSE_DOMAIN_SELECTION_TIMER_EXPIRED);

        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);
    }

    /* 判断当前IMS电话中是否有紧急呼 */
    if (VOS_TRUE == TAF_SPM_IsImsCallTypeEmgencyCall())
    {
        /* 当前有紧急呼存在，直接回复失败 */
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_NOT_ALLOW);
        return;
    }

    /* 缓存当前eCall请求消息 */
    (VOS_VOID)TAF_SPM_PutMessageToCcQueue(ulEventType, pstMsg);

    /* 启动呼叫业务请求保护定时器，如果定时超时，清除缓存，通知APP呼叫失败 */
    TAF_SPM_StartTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER,
                       TI_TAF_SPM_CC_ECALL_REQ_PROTECT_TIMER_VAL,
                       pstAppReq->clientId);

    /* 释放所有IMS下的非紧急呼叫 */
    TAF_SPM_SndImsRelAllCall(pstAppReq->clientId, pstAppReq->opId);

    /* 记录标记 */
    TAF_SPM_SetEcallHangUpImsFlag(VOS_TRUE);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcMiecAndAiecReq_PreProc
 功能描述  : 处理MIEC与AIEC Ecall呼叫请求
 输入参数  : ulEventType   - 事件类型
             pstMsg        - 消息地址

 输出参数  :
 返 回 值  : VOS_TRUE --  消息处理完毕
             VOS_FALSE -- 消息需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月22日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcMiecAndAiecReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq = VOS_NULL_PTR;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    pstAppReq->unParm.stOrig.stEmergencyCat.bExist = VOS_TRUE;

    /* 填写category类型 */
    if (MN_CALL_TYPE_MIEC == pstAppReq->unParm.stOrig.enCallType)
    {
        pstAppReq->unParm.stOrig.stEmergencyCat.ucEmergencyCat = MN_CALL_EMER_CATEGORG_MAN_INIT_ECALL;
    }
    else
    {
        pstAppReq->unParm.stOrig.stEmergencyCat.ucEmergencyCat = MN_CALL_EMER_CATEGORG_AUTO_INIT_ECALL;
    }

    if (TAF_PH_MODE_LOWPOWER == TAF_SDC_GetCurPhoneMode())
    {
        /* 如果处于温保关机状态, eCall紧急呼需要触发开机 */
        TAF_SPM_ProcMiecAndAiecReqInLowPower(ulEventType, pstMsg);

        return VOS_TRUE;
    }

    /* 如果未来考虑IMS也有呼叫存在，此处增加IMS call呼叫释放处理 */
    if (VOS_TRUE == TAF_SDC_GetCsCallExistFlg())
    {
        TAF_SPM_ProcMiecAndAiecReqInOtherCallRunning(ulEventType, pstMsg);

        return VOS_TRUE;
    }

#if (FEATURE_IMS == FEATURE_ON)
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        TAF_SPM_ProcMiecAndAiecReqInImsCallRunning(ulEventType, pstMsg);

        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcTestAndRecfgReq_PreProc
 功能描述  : 处理test与reconfiguration eCall呼叫
 输入参数  : ulEventType -- 事件类型
             pstMsg -- 呼叫请求消息地址

 输出参数  : 无
 返 回 值  : VOS_TRUE --  消息处理完毕
             VOS_FALSE -- 消息需要继续处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年04月22日
   作    者   : y00245242
   修改内容   : 为eCall特性增加
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcTestAndRecfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SDC_ECALL_NUM_STRU             *pstEcallNum = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq = VOS_NULL_PTR;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    if (0 != pstAppReq->unParm.stOrig.stDialNumber.ucNumLen)
    {
        return VOS_FALSE;
    }

    if (MN_CALL_TYPE_TEST == pstAppReq->unParm.stOrig.enCallType)
    {
        /* 获取test number */
        pstEcallNum = TAF_SDC_GetEcallTestNumber();
    }
    else
    {
        /* 获取reconfiguration number */
        pstEcallNum = TAF_SDC_GetEcallRecfgNumber();
    }

    /* 号码不存在，异常处理 */
    if (0 == pstEcallNum->ucLength)
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_CALL_NUMBER_NOT_EXIST);
        return VOS_TRUE;
    }

    if (TAF_SDC_ECALL_BCD_NUM_MAX_LEN < pstEcallNum->ucLength)
    {
        pstAppReq->unParm.stOrig.stDialNumber.ucNumLen = TAF_SDC_ECALL_BCD_NUM_MAX_LEN;
    }
    else
    {
        pstAppReq->unParm.stOrig.stDialNumber.ucNumLen = pstEcallNum->ucLength;
    }

    pstAppReq->unParm.stOrig.stDialNumber.enNumType = pstEcallNum->ucNumType;

    PS_MEM_CPY(&(pstAppReq->unParm.stOrig.stDialNumber.aucBcdNum[0]),
               &(pstEcallNum->aucCallNumber[0]),
               pstAppReq->unParm.stOrig.stDialNumber.ucNumLen);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_ProcEcallReq_PreProc
 功能描述  : 处理eCall呼叫
 输入参数  : ulEventType -- 事件类型
             pstMsg      -- 呼叫请求消息地址

 输出参数  : 无
 返 回 值  : VOS_FALSE － 消息处理未完成
             VOS_TRUE  － 消息处理已完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年04月22日
   作    者   : y00245242
   修改内容   : 为eCall特性增加
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcEcallReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    switch (pstAppReq->unParm.stOrig.enCallType)
    {
        case MN_CALL_TYPE_MIEC:
        case MN_CALL_TYPE_AIEC:
            ulRst = TAF_SPM_ProcMiecAndAiecReq_PreProc(ulEventType, pstMsg);
            break;

        case MN_CALL_TYPE_TEST:
        case MN_CALL_TYPE_RECFGURATION:
            ulRst = TAF_SPM_ProcTestAndRecfgReq_PreProc(ulEventType, pstMsg);
            break;

        default:
            ulRst = VOS_FALSE;
            break;
    }

    return ulRst;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsEcallAllowedInCurrentSysMode
 功能描述  : 根据当前系统模式，决定eCall呼叫是否被允许
 输入参数  : enCallType -- 呼叫类型

 输出参数  : 无
 返 回 值  : VOS_FALSE － 呼叫不允许发起
             VOS_TRUE  － 呼叫允许发起
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年04月22日
   作    者   : y00245242
   修改内容   : 为eCall特性增加
*****************************************************************************/
VOS_UINT32 TAF_SPM_IsEcallAllowedInCurrentSysMode(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    TAF_SDC_RAT_PRIO_STRU              *pstRatPrio = VOS_NULL_PTR;

    pstRatPrio = TAF_SDC_GetMsPrioRatList();

    if ((VOS_TRUE          == TAF_SDC_IsLteOnlyMode(pstRatPrio))
     && ((MN_CALL_TYPE_MIEC         == enCallType)
      || (MN_CALL_TYPE_AIEC         == enCallType)
      || (MN_CALL_TYPE_TEST         == enCallType)
      || (MN_CALL_TYPE_RECFGURATION == enCallType)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsEcallAllowedInCurrentCallMode
 功能描述  : 根据呼叫模式，是否允许发起eall
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
VOS_UINT32 TAF_SPM_IsEcallAllowedInCurrentCallMode(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    TAF_SDC_CALL_MODE_ENUM_UINT8        enEcallMode;

    enEcallMode = TAF_SDC_GetCurCallMode();

    if ((TAF_SDC_CALL_MODE_BUTT     == enEcallMode)
     && ((MN_CALL_TYPE_MIEC         == enCallType)
      || (MN_CALL_TYPE_AIEC         == enCallType)
      || (MN_CALL_TYPE_TEST         == enCallType)
      || (MN_CALL_TYPE_RECFGURATION == enCallType)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#endif
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-22, end */

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppOrigReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的呼叫请求的消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2014年04月22日
   作    者   : y00245242
   修改内容   : 为eCall特性修改
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg     = VOS_NULL_PTR;
    MN_CALL_EMERGENCY_CAT_STRU          stEmergencyCat;

    pstAppMsg                 = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    PS_MEM_SET(&stEmergencyCat, 0, sizeof(MN_CALL_EMERGENCY_CAT_STRU));

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-22, begin */
    /* call is allowed if phone mode is power on */
    if (VOS_TRUE != TAF_SPM_IsCallAllowedInCurrentPhoneMode(pstAppMsg))
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-22, end */
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_POWER_OFF);

        return VOS_TRUE;
    }

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_FALSE == TAF_SPM_IsEcallAllowedInCurrentSysMode(pstAppMsg->unParm.stOrig.enCallType))
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_NOT_ALLOW);

        return VOS_TRUE;
    }

    if (VOS_FALSE == TAF_SPM_IsEcallAllowedInCurrentCallMode(pstAppMsg->unParm.stOrig.enCallType))
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_NOT_ALLOW);

        return VOS_TRUE;
    }

    if (VOS_TRUE == TAF_SPM_ProcEcallReq_PreProc(ulEventType, pstMsg))
    {
        /* 消息处理完毕，返回 */
        return VOS_TRUE;
    }

    /* 如果是ecal紧急呼，不需要进行下一步检查 */
    if ((MN_CALL_TYPE_MIEC == pstAppMsg->unParm.stOrig.enCallType)
     || (MN_CALL_TYPE_AIEC == pstAppMsg->unParm.stOrig.enCallType))
    {
        return VOS_FALSE;
    }
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-22, end */

    /* VIDEO call当做普通呼叫处理不做紧急呼叫号码检查 */
    if ((MN_CALL_TYPE_VIDEO    != pstAppMsg->unParm.stOrig.enCallType)
     && (MN_CALL_TYPE_VIDEO_RX != pstAppMsg->unParm.stOrig.enCallType)
     && (MN_CALL_TYPE_VIDEO_TX != pstAppMsg->unParm.stOrig.enCallType))
    {
        /* 判断是紧急呼更新紧急呼叫的CAT信息 */
        if (VOS_TRUE  == TAF_SPM_IsEmergencyNum(&pstAppMsg->unParm.stOrig.stDialNumber,
                                                VOS_TRUE,
                                                &stEmergencyCat))
        {
            pstAppMsg->unParm.stOrig.enCallType  = MN_CALL_TYPE_EMERGENCY;

            PS_MEM_CPY(&(pstAppMsg->unParm.stOrig.stEmergencyCat),
                        &stEmergencyCat,
                        sizeof(MN_CALL_EMERGENCY_CAT_STRU));

            return VOS_FALSE;
        }
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* CDMA inside，并且当前是CL模式 */
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* 如果卡无效，拒绝普通呼 */
        if (VOS_FALSE == TAF_SPM_IsCsimServiceAvailable())
        {
            TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_SIM_NOT_EXIST);
            return VOS_TRUE;
        }
    }
    else
#endif
    {
        /* forbid normal call when USIM service is not available */
        if (VOS_FALSE == TAF_SPM_IsUsimServiceAvailable())
        {
            TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_SIM_NOT_EXIST);
            return VOS_TRUE;
        }

        /* 需要判断两个域卡无效,因为单域卡无效的情况能会disable LTE到GU下,需要到GU下继续尝试 */
        if (VOS_FALSE == TAF_SDC_IsUsimStausValid())
        {
            TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_SIM_INVALID);
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppSupsCmdReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的MN_CALL_APP_SUPS_CMD_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppSupsCmdReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
#if (FEATURE_ON == FEATURE_IMS)
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg = VOS_NULL_PTR;
#endif

    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* 如果已经IMS域呼叫存在，直接选择IMS域，其他情况返回VOS_FALSE，到CALL模块处理 */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
    else
    {
        /* 该场景解决由于SRVCC刚切换成功，如果此时用户发起挂断相应的call时，需要
         * 清除重拨缓存中保存的call请求信息，避免在GU下又发起重拨
         */
        pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

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
    }
#endif

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppGetInfoReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的MN_CALL_APP_GET_INFO_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRet;
    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* 如果已经IMS域呼叫存在，直接选择IMS域，其他情况返回VOS_FALSE，到CALL模块处理 */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppStartDtmfReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的MN_CALL_APP_START_DTMF_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppStartDtmfReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRet;
    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* 如果已经IMS域呼叫存在，直接选择IMS域，其他情况返回VOS_FALSE，到CALL模块处理 */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppStopDtmfReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的MN_CALL_APP_STOP_DTMF_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppStopDtmfReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRet;
    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* 如果已经IMS域呼叫存在，直接选择IMS域，其他情况返回VOS_FALSE，到CALL模块处理 */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppGetCdurReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的MN_CALL_APP_GET_CDUR_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetCdurReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRet;
    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* 如果已经IMS域呼叫存在，直接选择IMS域，其他情况返回VOS_FALSE，到CALL模块处理 */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppGetCallInfoReq_PreProc
 功能描述  : 预处理状态机初始化状态收到TAFAGENT的ID_TAFAGENT_MN_GET_CALL_INFO_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetCallInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRet;
    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* 如果已经IMS域呼叫存在，直接选择IMS域，其他情况返回VOS_FALSE，到CALL模块处理 */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppGetClprReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的MN_CALL_APP_CLPR_GET_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetClprReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRet;
    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* 如果已经IMS域呼叫存在，直接选择IMS域，其他情况返回VOS_FALSE，到CALL模块处理 */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

#if (FEATURE_ON == FEATURE_ECALL)
/* Added by s00261364 for V3R360_eCall项目, 2014-4-1, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_RcvMmaPhoneModeSetCnf_PreProc
 功能描述  : 预处理状态机初始化状态收到MMA的ID_TAF_MMA_PHONE_MODE_SET_CNF消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年4月1日
   作    者   : s00261364
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaPhoneModeSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstMsgInfo = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg  = VOS_NULL_PTR;
    TAF_MMA_PHONE_MODE_SET_CNF_STRU    *pstCnfMsg  = VOS_NULL_PTR;

    pstMsgInfo      = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);
    pstAppMsg       = (MN_CALL_APP_REQ_MSG_STRU *)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]);
    pstCnfMsg       = (TAF_MMA_PHONE_MODE_SET_CNF_STRU *)pstMsg;

    /* 检查client id */
    if (INTERNAL_CLIENT_ID_SPM != pstCnfMsg->usClientId)
    {
        return VOS_TRUE;
    }

    /* 如果缓存为空，缓存定时器已经超时，退出消息处理 */
    if (0 == TAF_SPM_GetCcMsgQueueNum())
    {
        return VOS_TRUE;
    }

    /* 1. 检查缓存消息类型是否是ecall呼叫，如果不是，则返回
     * 2. 检查是否是开机响应消息，即ucPhMode是否是TAF_PH_MODE_FULL，如果不是，则返回
     */
    if (((MN_CALL_TYPE_MIEC != pstAppMsg->unParm.stOrig.enCallType)
      && (MN_CALL_TYPE_AIEC != pstAppMsg->unParm.stOrig.enCallType))
     || (TAF_PH_MODE_FULL  != pstCnfMsg->ucPhMode))
    {
        return VOS_TRUE;
    }

    /* 停止保护定时器TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER */
    TAF_SPM_StopTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

    /* 开机失败，通知AT eCall呼叫失败  */
    if ( TAF_MMA_APP_OPER_RESULT_SUCCESS != pstCnfMsg->enRslt )
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType,
                                        (struct MsgCB *)pstAppMsg,
                                        TAF_CS_CAUSE_ECALL_LOWERPOWER_POWER_ON_FAIL);

        /* 清除缓存 */
        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);

        return VOS_TRUE;
    }

    /* 检查结果为成功设置更新入口消息标记并保存修改后的入口消息到全局变量中 */
    TAF_SPM_UpdateServiceCtrlEntryMsg(pstMsgInfo->stMsgEntry.ulEventType, (struct MsgCB *)pstAppMsg);

    TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

    /* 清除缓存 */
    TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);

    return VOS_FALSE;
}
/* Added by s00261364 for V3R360_eCall项目, 2014-4-1, end */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_RcvTafRelCallCnf_PreProc
 功能描述  : 处理内部normal呼叫释放确认消息

 输入参数  : pstMsg      -- 呼叫请求消息地址
             ulEventType － 事件类型

 输出参数  : 无
 返 回 值  : VOS_FALSE － 呼叫未处理完成
             VOS_TRUE  － 呼叫处理完成
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年04月22日
   作    者   : y00245242
   修改内容   : 为eCall特性增加
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvTafRelCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CALL_TAF_REL_CALL_CNF_STRU     *pstCnfMsg  = VOS_NULL_PTR;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstMsgInfo = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    /* 如果缓存为空，缓存定时器已经超时，退出消息处理 */
    if (0 == TAF_SPM_GetCcMsgQueueNum())
    {
        return VOS_TRUE;
    }

    pstMsgInfo      = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);
    pstAppMsg       = (MN_CALL_APP_REQ_MSG_STRU *)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]);

    /* 停止保护定时器TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER */
    TAF_SPM_StopTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

    pstCnfMsg = (TAF_CALL_TAF_REL_CALL_CNF_STRU *)pstMsg;
    if (TAF_CS_CAUSE_SUCCESS == pstCnfMsg->enCause)
    {
        /* 检查结果为成功设置更新入口消息标记并保存修改后的入口消息到全局变量中 */
        TAF_SPM_UpdateServiceCtrlEntryMsg(pstMsgInfo->stMsgEntry.ulEventType, (struct MsgCB *)pstAppMsg);

        TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

        ulRst = VOS_FALSE;
    }
    else
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType,
                                        (struct MsgCB *)pstAppMsg,
                                        pstCnfMsg->enCause);
        ulRst = VOS_TRUE;
    }

    /* 清除缓存 */
    TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);

    return ulRst;
}
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, end */

/* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_RcvPbECallInitInd_PreProc
 功能描述  : 收到PB初始化完成指示
 输入参数  : ulEventType
             pstMsg

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月23日
    作    者   : w00176964
    修改内容   : eCall项目新增
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvPbECallInitInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucFdnRecordNum;
    VOS_UINT8                           ucSdnRecordNum;
    SI_PB_ECALLINIT_IND_STRU           *pstECallInitInd = VOS_NULL_PTR;

    pstECallInitInd = (SI_PB_ECALLINIT_IND_STRU *)pstMsg;

    ucFdnRecordNum = (VOS_UINT8)pstECallInitInd->usFdnRecordNum;
    ucSdnRecordNum = (VOS_UINT8)pstECallInitInd->usSdnRecordNum;;

    /* 清除ecall number */
    TAF_SDC_InitECallNumber(TAF_SDC_GetEcallRecfgNumber());
    TAF_SDC_InitECallNumber(TAF_SDC_GetEcallTestNumber());

    TAF_SPM_ReadEcallNumber(ucFdnRecordNum, ucSdnRecordNum);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_ProcPbQryFdnECallNumCnf_PreProc
 功能描述  : 收到PB模块读取FDN中ecall相关号码的处理
 输入参数  : pstPbMsg-----PB的查询消息

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月26日
    作    者   : w00176964
    修改内容   : eCall项目新增
*****************************************************************************/
VOS_VOID TAF_SPM_ProcPbQryFdnECallNumCnf_PreProc(
    SI_PB_ECALLQRY_CNF_STRU            *pstPbMsg
)
{
    TAF_SDC_ECALL_NUM_STRU             *pstTestNum  = VOS_NULL_PTR;
    TAF_SDC_ECALL_NUM_STRU             *pstRecfgNum = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstTestNum  = TAF_SDC_GetEcallTestNumber();
    pstRecfgNum = TAF_SDC_GetEcallRecfgNumber();

    for (ucIndex = 0; ucIndex < (VOS_UINT8)pstPbMsg->ulRecordNum; ucIndex++)
    {
        /* 第一条索引为test number */
        if ((TAF_SPM_USIM_FILE_FIRST_RECORD == pstPbMsg->astECallNumber[ucIndex].ucIndex)
         && (0                              < pstPbMsg->astECallNumber[ucIndex].ucLength))
        {
            pstTestNum->ucNumType = pstPbMsg->astECallNumber[ucIndex].ucTon;

            if (PB_NUMBER_TYPE_INTERNATIONAL != pstTestNum->ucNumType)
            {
                pstTestNum->ucNumType = PB_NUMBER_TYPE_NORMAL;
            }

            pstTestNum->ucLength  = pstPbMsg->astECallNumber[ucIndex].ucLength;

            if (TAF_SDC_ECALL_BCD_NUM_MAX_LEN < pstTestNum->ucLength)
            {
                pstTestNum->ucLength = TAF_SDC_ECALL_BCD_NUM_MAX_LEN;
            }

            PS_MEM_CPY(pstTestNum->aucCallNumber, pstPbMsg->astECallNumber[ucIndex].aucCallNumber, pstTestNum->ucLength);
        }

        /* 第二条索引为recfg number */
        if ((TAF_SPM_USIM_FILE_SECOND_RECORD == pstPbMsg->astECallNumber[ucIndex].ucIndex)
         && (0                               < pstPbMsg->astECallNumber[ucIndex].ucLength))
        {
            pstRecfgNum->ucNumType = pstPbMsg->astECallNumber[ucIndex].ucTon;

            if (PB_NUMBER_TYPE_INTERNATIONAL != pstRecfgNum->ucNumType)
            {
                pstRecfgNum->ucNumType = PB_NUMBER_TYPE_NORMAL;
            }

            pstRecfgNum->ucLength  = pstPbMsg->astECallNumber[ucIndex].ucLength;

            if (TAF_SDC_ECALL_BCD_NUM_MAX_LEN < pstRecfgNum->ucLength)
            {
                pstRecfgNum->ucLength = TAF_SDC_ECALL_BCD_NUM_MAX_LEN;
            }

            PS_MEM_CPY(pstRecfgNum->aucCallNumber, pstPbMsg->astECallNumber[ucIndex].aucCallNumber, pstRecfgNum->ucLength);

            break;
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_ProcPbQrySdnECallNumCnf_PreProc
 功能描述  : 收到PB模块读取SDN中ecall相关号码的处理
 输入参数  : pstPbMsg-----PB的查询消息

 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月26日
    作    者   : w00176964
    修改内容   : eCall项目新增
*****************************************************************************/
VOS_VOID TAF_SPM_ProcPbQrySdnECallNumCnf_PreProc(
    SI_PB_ECALLQRY_CNF_STRU            *pstPbMsg
)
{
    TAF_SDC_ECALL_NUM_STRU             *pstTestNum  = VOS_NULL_PTR;
    TAF_SDC_ECALL_NUM_STRU             *pstRecfgNum = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucTmpIndex;

    pstTestNum  = TAF_SDC_GetEcallTestNumber();
    pstRecfgNum = TAF_SDC_GetEcallRecfgNumber();

    for (ucIndex = (VOS_UINT8)pstPbMsg->ulRecordNum; ucIndex > 0; ucIndex--)
    {
        ucTmpIndex = (VOS_UINT8)pstPbMsg->ulRecordNum;

        /* 最后条索引为recfg number */
        if ((ucTmpIndex == pstPbMsg->astECallNumber[ucIndex].ucIndex)
         && (0          < pstPbMsg->astECallNumber[ucIndex].ucLength))
        {
            pstRecfgNum->ucNumType = pstPbMsg->astECallNumber[ucIndex].ucTon;

            if (PB_NUMBER_TYPE_INTERNATIONAL != pstRecfgNum->ucNumType)
            {
                pstRecfgNum->ucNumType = PB_NUMBER_TYPE_NORMAL;
            }

            pstRecfgNum->ucLength  = pstPbMsg->astECallNumber[ucIndex].ucLength;

            if (TAF_SDC_ECALL_BCD_NUM_MAX_LEN < pstRecfgNum->ucLength)
            {
                pstRecfgNum->ucLength = TAF_SDC_ECALL_BCD_NUM_MAX_LEN;
            }

            PS_MEM_CPY(pstRecfgNum->aucCallNumber, pstPbMsg->astECallNumber[ucIndex].aucCallNumber, pstRecfgNum->ucLength);
        }

        /* 倒数第二条索引为test number */
        ucTmpIndex = (VOS_UINT8)pstPbMsg->ulRecordNum - 1;

        if ((ucTmpIndex == pstPbMsg->astECallNumber[ucIndex].ucIndex)
         && (0          < pstPbMsg->astECallNumber[ucIndex].ucLength))
        {
            pstTestNum->ucNumType = pstPbMsg->astECallNumber[ucIndex].ucTon;

            if (PB_NUMBER_TYPE_INTERNATIONAL != pstTestNum->ucNumType)
            {
                pstTestNum->ucNumType = PB_NUMBER_TYPE_NORMAL;
            }

            pstTestNum->ucLength  = pstPbMsg->astECallNumber[ucIndex].ucLength;

            if (TAF_SDC_ECALL_BCD_NUM_MAX_LEN < pstTestNum->ucLength)
            {
                pstTestNum->ucLength = TAF_SDC_ECALL_BCD_NUM_MAX_LEN;
            }

            PS_MEM_CPY(pstTestNum->aucCallNumber, pstPbMsg->astECallNumber[ucIndex].aucCallNumber, pstTestNum->ucLength);

            break;
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_RcvPbQryECallNumCnf_PreProc
 功能描述  : 收到PB模块读取ecall相关号码的处理
 输入参数  : ulEventType
             pstMsg

 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月23日
    作    者   : w00176964
    修改内容   : eCall项目新增
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvPbQryECallNumCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SI_PB_ECALLQRY_CNF_STRU            *pstPbMsg    = VOS_NULL_PTR;

    pstPbMsg = (SI_PB_ECALLQRY_CNF_STRU *)pstMsg;

    if (VOS_OK != pstPbMsg->ulRslt)
    {
        return VOS_TRUE;
    }
    if (SI_PB_STORAGE_FD == pstPbMsg->enStorage)
    {
        TAF_SPM_ProcPbQryFdnECallNumCnf_PreProc(pstPbMsg);

        return VOS_TRUE;
    }
    if (SI_PB_STORAGE_SD == pstPbMsg->enStorage)
    {
        TAF_SPM_ProcPbQrySdnECallNumCnf_PreProc(pstPbMsg);
    }

    return VOS_TRUE;
}

/* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */


#endif





/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppSendRpdataDirect_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppSendRpdataDirect_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulCause;

    /* 检查当前卡状态及开关机状态是否允许发起SMS业务 */
    if (VOS_FALSE == TAF_SPM_IsSmsServiceReqAllowed_PreProc(ulEventType, pstMsg, &ulCause))
    {
        /* 如果不允许发起SMS业务，给AT回复失败，带相应的原因值 */
        TAF_SPM_SendSmsServiceRequetFail(ulEventType, pstMsg, ulCause);

        return VOS_TRUE;
    }

    /* 允许发起SMS业务时，要进行FDN&CALL CONTROL检查 */
    return VOS_FALSE;

}



/*****************************************************************************
 函 数 名  : TAF_SPM_RcvProcUssSsReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的TAF_MSG_PROCESS_USS_MSG消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvProcUssSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstRcvMsg   = VOS_NULL_PTR;
    TAF_SS_PROCESS_USS_REQ_STRU        *pstSsReqMsg = VOS_NULL_PTR;
    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    pstRcvMsg   = (MN_APP_REQ_MSG_STRU *)pstMsg;
    pstSsReqMsg = (TAF_SS_PROCESS_USS_REQ_STRU *)&(pstRcvMsg->aucContent[0]);

    /* configure CUSD setting */
    if (TAF_SS_CUSD_TYPE_ENABLE == pstSsReqMsg->enCusdType)
    {
        TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUSD, VOS_TRUE);
    }
    else
    {
        TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUSD, VOS_FALSE);
    }

    /* check whether or not USSD string exists */
    if (0 == pstSsReqMsg->UssdStr.usCnt)
    {
        /* 如果只带CUSD是否主动上报参数，AT口已经释放，不需要等待C核回复 */
        return VOS_TRUE;
    }

    /* 检查当前卡状态及开关机状态是否允许发起SS业务 */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* 如果不允许发起SS业务，给AT回复失败，带相应的原因值 */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* 允许发起SS业务时，要进行FDN&CALL CONTROL检查 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvRegisterSsReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的TAF_MSG_REGISTERSS_MSG消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvRegisterSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* 检查当前卡状态及开关机状态是否允许发起SS业务 */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* 如果不允许发起SS业务，给AT回复失败，带相应的原因值 */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* 允许发起SS业务时，要进行FDN&CALL CONTROL检查 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvEraseSsReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的TAF_MSG_ERASESS_MSG消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvEraseSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* 检查当前卡状态及开关机状态是否允许发起SS业务 */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* 如果不允许发起SS业务，给AT回复失败，带相应的原因值 */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* 允许发起SS业务时，要进行FDN&CALL CONTROL检查 */
    return VOS_FALSE;
}




/*****************************************************************************
 函 数 名  : TAF_SPM_RcvActivateSsReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的TAF_MSG_ACTIVATESS_MSG消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvActivateSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* 检查当前卡状态及开关机状态是否允许发起SS业务 */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* 如果不允许发起SS业务，给AT回复失败，带相应的原因值 */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* 允许发起SS业务时，要进行FDN&CALL CONTROL检查 */
    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : TAF_SPM_RcvDeactivateSsReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的TAF_MSG_DEACTIVATESS_MSG消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvDeactivateSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* 检查当前卡状态及开关机状态是否允许发起SS业务 */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* 如果不允许发起SS业务，给AT回复失败，带相应的原因值 */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* 允许发起SS业务时，要进行FDN&CALL CONTROL检查 */
    return VOS_FALSE;
}



/*****************************************************************************
 函 数 名  : TAF_SPM_RcvInterrogateSsReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的TAF_MSG_INTERROGATESS_MSG消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvInterrogateSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* 检查当前卡状态及开关机状态是否允许发起SS业务 */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* 如果不允许发起SS业务，给AT回复失败，带相应的原因值 */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* 允许发起SS业务时，要进行FDN&CALL CONTROL检查 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_RcvRegPwdSsReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的TAF_MSG_REGPWD_MSG消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年01月07日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvRegPwdSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* 检查当前卡状态及开关机状态是否允许发起SS业务 */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* 如果不允许发起SS业务，给AT回复失败，带相应的原因值 */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* 允许发起SS业务时，要进行FDN&CALL CONTROL检查 */
    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_RcvEraseCCentrySsReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的TAF_MSG_ERASECCENTRY_MSG消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年01月07日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvEraseCCentrySsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* 检查当前卡状态及开关机状态是否允许发起SS业务 */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* 如果不允许发起SS业务，给AT回复失败，带相应的原因值 */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* 允许发起SS业务时，要进行FDN&CALL CONTROL检查 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvRleaseSsReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的TAF_MSG_RLEASE_MSG消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvRleaseSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;

    ulRet               = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* 如果已经IMS域USSD业务存在，直接选择IMS域，其他情况返回VOS_FALSE，按NAS信令流程处理 */
    if (VOS_TRUE == TAF_SDC_GetImsSsSrvExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvStkOrigReq_PreProc
 功能描述  : 预处理状态机初始化状态收到STK的呼叫请求的消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : s00217060
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvStkOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    MN_CALL_EMERGENCY_CAT_STRU          stEmergencyCat;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT32                          ulExistBc;
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstOrigParam = VOS_NULL_PTR;

    pstOrigParam = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stEmergencyCat, 0, sizeof(MN_CALL_EMERGENCY_CAT_STRU));
    enCallType  = MN_CALL_TYPE_VOICE;
    ulExistBc   = VOS_TRUE;

    /* call is allowed if phone mode is power on */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_POWER_OFF);
        return VOS_TRUE;
    }

    if (0 == pstOrigParam->stBc.ucLen)
    {
        ulExistBc    = VOS_FALSE;
    }

    /* 根据BC参数获取呼叫类型 */
    ulRet = TAF_SPM_GetBcCallType(ulExistBc,
                                  pstOrigParam->stBc.ucLen,
                                  pstOrigParam->stBc.aucBc,
                                  &enCallType);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("MN_CALL_StkCallOrigReqProc: Fail to TAF_SPM_GetBcCallType.");

        TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                 pstOrigParam->opID,
                                 pstOrigParam->callID,
                                 TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY);

#if (FEATURE_ON == FEATURE_PTM)
        /* 记录CS呼叫异常log */
        MN_CALL_CsCallErrRecord(pstOrigParam->callID, TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY);
#endif

        return VOS_TRUE;
    }

    /* VIDEO call当做普通呼叫处理不做紧急呼叫号码检查 */
    pstOrigParam->enCallType = enCallType;
    if ((MN_CALL_TYPE_VIDEO    != pstOrigParam->enCallType)
     && (MN_CALL_TYPE_VIDEO_RX != pstOrigParam->enCallType)
     && (MN_CALL_TYPE_VIDEO_TX != pstOrigParam->enCallType))
    {
        /* 判断是紧急呼更新紧急呼叫的CAT信息 */
        if (VOS_TRUE  == TAF_SPM_IsEmergencyNum((MN_CALL_CALLED_NUM_STRU *)&pstOrigParam->stCalledAddr,
                                                  VOS_FALSE,
                                                  &stEmergencyCat))
        {
            pstOrigParam->enCallType        = MN_CALL_TYPE_EMERGENCY;

            PS_MEM_CPY(&(pstOrigParam->stEmergencyCat),
                        &stEmergencyCat,
                        sizeof(MN_CALL_EMERGENCY_CAT_STRU));

            return VOS_FALSE;
        }
        else
        {
            PS_MEM_SET(&(pstOrigParam->stEmergencyCat),
                       0,
                       sizeof(MN_CALL_EMERGENCY_CAT_STRU));

        }
    }

    /* forbid normal call when USIM service is not available */
    if (VOS_FALSE == TAF_SPM_IsUsimServiceAvailable())
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_SIM_NOT_EXIST);
        return VOS_TRUE;
    }

    /* 需要判断两个域卡无效,因为单域卡无效的情况能会disable LTE到GU下,需要到GU下继续尝试 */
    if (VOS_FALSE == TAF_SDC_IsUsimStausValid())
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_SIM_INVALID);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : TAF_SPM_RcvMsgSmmaInd_PreProc
 功能描述  : MAIN状态机初始化状态收到ID_TAF_SPM_SMMA_IND的消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月24日
   作    者   : s00217060
   修改内容   : 新生成函数
 2.日    期   : 2013年12月31日
   作    者   : y00245242
   修改内容   : 增加IMS-->CS换域重拨功能
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMsgSmmaInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;

    /* 进行域选择 */
    enDomainSelRslt = TAF_SPM_ProcSmsDomainSelection();

    TAF_SPM_ProcSmmaIndDomainSelectionResult(ulEventType, pstMsg, enDomainSelRslt);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvMsgReportInd_PreProc
 功能描述  : MAIN状态机初始化状态收到ID_TAF_SPM_MSG_REPORT_IND的消息处理.
             该消息通知SPM短信发送结果
             收到该消息，check消息中携带的cause值:
             1) cause值属于重拨cause值，SPM将复制重拨缓存消息，转发给MSG模块；
             2) cause值不属于重拨cause值，通知上层短信发送失败
             完成上述操作后，清除重拨缓存


 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE :消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月10日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2015年4月13日
   作    者   : s00217060
   修改内容   : DTS2015041007878:ID_TAF_SPM_MSG_REPORT_IND中的client id不对，重拨缓存未清除
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMsgReportInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_MSG_REPORT_IND_STRU                            *pstMsgReportInd = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU                                 *pstCacheMsg     = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;
    VOS_UINT32                                              ulRst;
    VOS_UINT8                                               ucImsSmsSndFlg;

    pstMsgReportInd = (TAF_SPM_MSG_REPORT_IND_STRU *)pstMsg;

    /* 清除IMS短信正在发送标志 */
    TAF_SPM_SetImsSmsSendingFlg(VOS_FALSE);

    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvMsgReportInd_PreProc: ImsSmsSendingFlg IS FALSE.");

    if (VOS_TRUE == TAF_SDC_GetSmsRedailFromImsToCsSupportFlag())
    {
        /* 从短信重拨缓存中取出缓存消息 */
        pstCacheMsg = TAF_SPM_GetSmsRedialBufferWithClientId(&ucIndex, pstMsgReportInd->usClientId);

        if (VOS_NULL_PTR != pstCacheMsg)
        {
            if (VOS_TRUE == TAF_MSG_IsSmsRedialCauseValueFromImsDomain(pstMsgReportInd->stRptEvtInfo.enErrorCode))
            {
                if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_SPM_SMMA_IND) == pstCacheMsg->ulEventType)
                {
                    /* SMMA消息，需要发送外部消息给MSG模块 */
                    TAF_SPM_SendMsgSmmaRsp(TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING,
                                           (struct MsgCB*)&(pstCacheMsg->aucEntryMsgBuffer[0]));

                    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvMsgReportInd_PreProc: SendMsgSmmaRsp.");
                }
                else
                {
                    /* 修改消息中的信令类型 */
                    (VOS_VOID)TAF_SPM_ProcReqMsgBasedOnNasSignalling(pstCacheMsg->ulEventType,
                                                           (struct MsgCB*)&(pstCacheMsg->aucEntryMsgBuffer[0]));

                    /* 更新入口消息 */
                    TAF_SPM_UpdateServiceCtrlEntryMsg(pstCacheMsg->ulEventType,
                                                      (struct MsgCB*)&(pstCacheMsg->aucEntryMsgBuffer[0]));

                    TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);
                }

                /* 清除重拨缓存 */
                TAF_SPM_FreeSpecificedIndexSmsRedialBuffer(ucIndex);

                /* 如果此时域选择缓存有消息存在，需要把消息转发给MSG模块 */
                if (0 != TAF_SPM_GetSmsMsgQueueNum())
                {
                    /* 发送内部域选择给SPM */
                    TAF_SPM_SndInternalDomainSelectionInd();
                }

                TAF_SPM_LogSrvDomainSelRedialInfo();

                return VOS_FALSE;
            }

            /* 清除重拨缓存 */
            TAF_SPM_FreeSpecificedIndexSmsRedialBuffer(ucIndex);

            TAF_SPM_LogSrvDomainSelRedialInfo();
        }

        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvMsgReportInd_PreProc: VOS_NULL_PTR == pstCacheMsg.");
    }

    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvMsgReportInd_PreProc: Redail not support.");

    /* 不支持换域重拨，这儿上报短信发送报告 */
    TAF_SPM_ProcSmsRptEvent(pstMsgReportInd);

    /* 继续处理短信域选择queue */
    if (0 != TAF_SPM_GetSmsMsgQueueNum())
    {
        enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_BUTT;

        ulRst = TAF_SPM_ProcSmsMsgQueue(&enDomainSelRslt);

        /* check if domain selection type is buffer message */
        if (TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE != enDomainSelRslt)
        {
            /* 如果短信域选择缓存不为空，且当前无IMS短信在发送，继续处理短信域选择缓存 */
            ucImsSmsSndFlg = TAF_SPM_GetImsSmsSendingFlg();
            if ((0         != TAF_SPM_GetSmsMsgQueueNum())
             && (VOS_FALSE == ucImsSmsSndFlg))
            {
                TAF_SPM_SndInternalDomainSelectionInd();
            }

            /* log service domain selection infomation */
            TAF_SPM_LogSrvDomainSelQueueInfo();

            return ulRst;
        }
    }

    TAF_SPM_LogSrvDomainSelRedialInfo();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvMsgCheckRsltInd_PreProc
 功能描述  : MAIN状态机初始化状态收到ID_TAF_SPM_MSG_CHECK_RESULT_IND的消息处理.
             该消息通知SPM短信FDN or CONTROL检查结果,收到该消息清除缓存
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE :消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月14日
   作    者   : j00174725
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMsgCheckRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_MSG_CHECK_RESULT_IND_STRU                      *pstMsgCheckRsltInd  = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU                                 *pstCacheMsg         = VOS_NULL_PTR;
    VOS_UINT32                                              ulRst;
    VOS_UINT8                                               ucIndex;
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;

    pstMsgCheckRsltInd = (TAF_SPM_MSG_CHECK_RESULT_IND_STRU *)pstMsg;

    if ( (pstMsgCheckRsltInd->enRslt != TAF_MSG_ERROR_FDN_CHECK_FAIL)
      && (pstMsgCheckRsltInd->enRslt != TAF_MSG_ERROR_FDN_CHECK_TIMEROUT)
      && (pstMsgCheckRsltInd->enRslt != TAF_MSG_ERROR_CTRL_CHECK_FAIL)
      && (pstMsgCheckRsltInd->enRslt != TAF_MSG_ERROR_CTRL_CHECK_TIMEOUT) )
    {
        return VOS_TRUE;
    }

#if (FEATURE_IMS == FEATURE_ON)
    /* 清除IMS短信正在发送标志 */
    TAF_SPM_SetImsSmsSendingFlg(VOS_FALSE);

    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvMsgCheckRsltInd_PreProc: ImsSmsSendingFlg FDN Or SMS CONTROL fail.");

    if (VOS_TRUE == TAF_SDC_GetSmsRedailFromImsToCsSupportFlag())
    {
        /* 从短信重拨缓存中取出缓存消息 */
        pstCacheMsg = TAF_SPM_GetSmsRedialBufferWithClientId(&ucIndex, pstMsgCheckRsltInd->usClientId);

        if (VOS_NULL_PTR != pstCacheMsg)
        {
            /* 清除重拨缓存 */
            TAF_SPM_FreeSpecificedIndexSmsRedialBuffer(ucIndex);
        }
    }
#endif

    /* 继续处理短信域选择queue */
    if (0 != TAF_SPM_GetSmsMsgQueueNum())
    {
        enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_BUTT;

        ulRst = TAF_SPM_ProcSmsMsgQueue(&enDomainSelRslt);

        /* check if domain selection type is buffer message */
        if (TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE != enDomainSelRslt)
        {
            if (0 != TAF_SPM_GetSmsMsgQueueNum())
            {
                /* 继续处理短信域选择缓存 */
                TAF_SPM_SndInternalDomainSelectionInd();
            }

            /* log service domain selection infomation */
            TAF_SPM_LogSrvDomainSelQueueInfo();
        }

        return ulRst;
    }

    TAF_SPM_LogSrvDomainSelRedialInfo();
    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvMsgCheckRsltInd_PreProc");

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallOrigCnf_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_CALL_ORIG_CNF事件的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月30日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年09月23日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目,更新IMS域业务标识
  3.日    期   : 2013年12月12日
    作    者   : y00245242
    修改内容   : 增加IMS域到CS域的换域重拨功能
  4.日    期   : 2014年11月06日
    作    者   : s00217060
    修改内容   : DTS2014110608091:IMS电话时不处理cs域的paging ind
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallOrigCnf_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheInfo             = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
    /* 只要MO成功时，才设置IMS域呼叫存在标识 */
    if (TAF_CS_CAUSE_SUCCESS == stCallInfo.enCause)
    {
        TAF_SDC_SetImsCallExistFlg(VOS_TRUE);
        TAF_SndMmaImsSrvInfoNotify(VOS_TRUE);

        /* 更新重拨缓存消息的call ID，方便消息在释放时查找 */
        TAF_SPM_UpdateCallRedialBufferMsgWithCallId(stCallInfo.clientId, stCallInfo.callId);
    }
    /* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, begin */
    else
    {
        /* IMSA不填写呼叫方向，本地修改一下该项，为后续重拨判断使用 */
        stCallInfo.enCallDir = MN_CALL_DIR_MO;

        if (VOS_TRUE == TAF_SPM_IsCsCallRedialAllowed(&stCallInfo))
        {
            /* 获取呼叫重拨缓存消息 */
            pstCacheInfo = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(0);

            /* 更新入口消息 */
            TAF_SPM_UpdateServiceCtrlEntryMsg(pstCacheInfo->ulEventType,
                                              (struct MsgCB*)&(pstCacheInfo->aucEntryMsgBuffer[0]));

            TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

            /* 清除重拨缓存 */
            TAF_SPM_FreeSpecificedIndexCallRedialBuffer(0);

            return VOS_FALSE;
        }

        /* 清除重拨缓存 */
        TAF_SPM_FreeSpecificedIndexCallRedialBuffer(0);
    }
    /* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, end */
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* 构造一条MN_CALL_EVT_CALL_ORIG_CNF消息，给相应的cliendId回复 */
    MN_SendClientEvent(stCallInfo.clientId,
                        MN_CALLBACK_CS_CALL,
                        MN_CALL_EVT_CALL_ORIG_CNF,
                        &stCallInfo);

#if (FEATURE_ON == FEATURE_PTM)
    /* 记录CS呼叫异常log */
    MN_CALL_CsCallErrRecord(0, stCallInfo.enCause);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallOrig_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_ORIG事件的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月30日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年12月13日
    作    者   : y00245242
    修改内容   : 增加IMS域到CS域的换域重拨功能
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallOrig_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* 构造一条MN_CALL_EVT_ORIG消息，给相应的cliendId回复 */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_ORIG,
                       &stCallInfo);

    /* 更新重拨缓存消息的call ID，方便消息在释放时查找 */
    TAF_SPM_UpdateCallRedialBufferMsgWithCallId(stCallInfo.clientId, stCallInfo.callId);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallProc_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_CALL_PROC事件的处理
             注: call proceeding事件是IMS内部产生，非网络发送过来的事件，因此
                 收到该事件时，并不清除call 模块的重拨缓存

 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月30日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallProc_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* 构造一条MN_CALL_EVT_CALL_PROC消息，给相应的cliendId回复 */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_CALL_PROC,
                       &stCallInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallAlerting_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_ALERTING事件的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月30日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年12月13日
    作    者   : y00245242
    修改内容   : 增加换域重拨功能
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallAlerting_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* 构造一条MN_CALL_EVT_ALERTING消息，给相应的cliendId回复 */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_ALERTING,
                       &stCallInfo);

    /* 清除重拨缓存 */
    TAF_SPM_FreeCallRedialBufferWithCallId(pstImsaCallMsg->stCallInfo.callId);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallConnect_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_CONNECT事件的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月30日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallConnect_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* 构造一条MN_CALL_EVT_CONNECT消息，给相应的cliendId回复 */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_CONNECT,
                       &stCallInfo);

    /* 清除重拨缓存 */
    TAF_SPM_FreeCallRedialBufferWithCallId(pstImsaCallMsg->stCallInfo.callId);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallSupsCmdCnf_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_SUPS_CMD_CNF事件的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月30日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallSupsCmdCnf_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* 构造一条MN_CALL_EVT_SUPS_CMD_CNF消息，给相应的cliendId回复 */
    MN_SendClientEvent(stCallInfo.clientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_SUPS_CMD_CNF,
                       &stCallInfo);


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallRelease_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_RELEASED事件的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月30日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年12月12日
    作    者   : y00245242
    修改内容   : 增加IMS域到CS域的换域重拨功能
  3.日    期   :2014年9月28日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallRelease_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheInfo             = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, begin */
    if (VOS_TRUE == TAF_SPM_IsCsCallRedialAllowed(&stCallInfo))
    {
        /* 获取呼叫重拨缓存消息 */
        pstCacheInfo = TAF_SPM_GetCallRedialBufferWithCallId(stCallInfo.callId);
        if (VOS_NULL_PTR != pstCacheInfo)
        {
            /* 更新入口消息 */
            TAF_SPM_UpdateServiceCtrlEntryMsg(pstCacheInfo->ulEventType,
                                              (struct MsgCB*)&(pstCacheInfo->aucEntryMsgBuffer[0]));

            TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

            /* 清除重拨缓存 */
            TAF_SPM_FreeCallRedialBufferWithCallId(stCallInfo.callId);

            return VOS_FALSE;
        }
    }

    /* 清除重拨缓存 */
    TAF_SPM_FreeCallRedialBufferWithCallId(stCallInfo.callId);
    /* Added by y00245242 for VoLTE_PhaseIII 项目, 2013-12-12, end */

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* 构造一条MN_CALL_EVT_RELEASED消息，给相应的cliendId回复 */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_RELEASED,
                       &stCallInfo);

#if (FEATURE_ON == FEATURE_PTM)
    /* 记录CS呼叫异常log */
    MN_CALL_CsCallErrRecord(0, stCallInfo.enCause);
#endif

    /* 电话挂断时勾出相应的事件，第三个参数不能是空指针，第四个参数不能是0，否则事件报不上去 */
    if(MN_CALL_DIR_MO == stCallInfo.enCallDir)
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_DISCONNECT,
                        &(stCallInfo.enCause),
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MT_DISCONNECT,
                        &(stCallInfo.enCause),
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallIncoming_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_INCOMING事件的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月30日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年09月23日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目,更新IMS域业务标识
  3.日    期   : 2014年11月06日
    作    者   : s00217060
    修改内容   : DTS2014110608091:IMS电话时不处理cs域的paging ind
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallIncoming_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
    /* 设置IMS域呼叫存在标识 */
    TAF_SDC_SetImsCallExistFlg(VOS_TRUE);
    TAF_SndMmaImsSrvInfoNotify(VOS_TRUE);
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* 构造一条MN_CALL_EVT_INCOMING消息，给相应的cliendId回复 */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_INCOMING,
                       &stCallInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallStartDtmfCnf_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_START_DTMF_CNF事件的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月30日
    作    者   : s00217060
    修改内容   : 新生成函数
  1.日    期   : 2013年10月25日
    作    者   : y00245242
    修改内容   : 适配新的DTMF接口
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallStartDtmfCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_START_DTMF_CNF_STRU  *pstStartDtmfCnfMsg       = VOS_NULL_PTR;
    TAF_CALL_EVT_DTMF_CNF_STRU          stDtmfCnf;

    pstStartDtmfCnfMsg      = (IMSA_SPM_CALL_START_DTMF_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stDtmfCnf, 0, sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    stDtmfCnf.callId        = pstStartDtmfCnfMsg->ucCallId;
    stDtmfCnf.usClientId    = pstStartDtmfCnfMsg->usClientId;
    stDtmfCnf.opId          = pstStartDtmfCnfMsg->ucOpId;
    stDtmfCnf.enCause       = pstStartDtmfCnfMsg->enCause;
    stDtmfCnf.enDtmfState   = pstStartDtmfCnfMsg->enDtmfState;
    stDtmfCnf.ucDtmfCnt     = pstStartDtmfCnfMsg->ucDtmfCnt;


    TAF_CALL_SendMsg(pstStartDtmfCnfMsg->usClientId,
                     MN_CALL_EVT_START_DTMF_CNF,
                     &stDtmfCnf,
                     sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallStartDtmfRsltInd_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_START_DTMF_RSLT_IND事件的处理
 输入参数  : ulEventType:事件类型
             pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月25日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallStartDtmfRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_START_DTMF_RSLT_IND_STRU                 *pstDtmfRsltIndMsg       = VOS_NULL_PTR;
    TAF_CALL_EVT_DTMF_CNF_STRU                              stDtmfCnf;

    pstDtmfRsltIndMsg      = (IMSA_SPM_CALL_START_DTMF_RSLT_IND_STRU *)pstMsg;

    PS_MEM_SET(&stDtmfCnf, 0, sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    stDtmfCnf.callId        = pstDtmfRsltIndMsg->ucCallId;
    stDtmfCnf.usClientId    = pstDtmfRsltIndMsg->usClientId;
    stDtmfCnf.opId          = pstDtmfRsltIndMsg->ucOpId;
    stDtmfCnf.enCause       = pstDtmfRsltIndMsg->enCause;
    stDtmfCnf.enDtmfState   = pstDtmfRsltIndMsg->enDtmfState;
    stDtmfCnf.ucDtmfCnt     = pstDtmfRsltIndMsg->ucDtmfCnt;


    TAF_CALL_SendMsg(pstDtmfRsltIndMsg->usClientId,
                     MN_CALL_EVT_START_DTMF_RSLT,
                     &stDtmfCnf,
                     sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallStopDtmfCnf_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_STOP_DTMF_CNF事件的处理
 输入参数  : ulEventType:事件类型
             pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月30日
    作    者   : s00217060
    修改内容   : 新生成函数
  1.日    期   : 2013年10月25日
    作    者   : y00245242
    修改内容   : 适配新的DTMF接口
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallStopDtmfCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_STOP_DTMF_CNF_STRU   *pstStopDtmfCnfMsg       = VOS_NULL_PTR;
    TAF_CALL_EVT_DTMF_CNF_STRU          stDtmfCnf;

    pstStopDtmfCnfMsg      = (IMSA_SPM_CALL_STOP_DTMF_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stDtmfCnf, 0, sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    stDtmfCnf.callId       = pstStopDtmfCnfMsg->ucCallId;
    stDtmfCnf.usClientId   = pstStopDtmfCnfMsg->usClientId;
    stDtmfCnf.opId         = pstStopDtmfCnfMsg->ucOpId;
    stDtmfCnf.enCause      = pstStopDtmfCnfMsg->enCause;
    stDtmfCnf.enDtmfState  = pstStopDtmfCnfMsg->enDtmfState;
    stDtmfCnf.ucDtmfCnt    = pstStopDtmfCnfMsg->ucDtmfCnt;


    TAF_CALL_SendMsg(pstStopDtmfCnfMsg->usClientId,
                     MN_CALL_EVT_STOP_DTMF_CNF,
                     &stDtmfCnf,
                     sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallStopDtmfRsltInd_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_STOP_DTMF_RSLT_IND消息处理
 输入参数  : ulEventType:事件类型
             pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月25日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallStopDtmfRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_STOP_DTMF_RSLT_IND_STRU                  *pstDtmfRsltIndMsg       = VOS_NULL_PTR;
    TAF_CALL_EVT_DTMF_CNF_STRU                              stDtmfCnf;

    pstDtmfRsltIndMsg      = (IMSA_SPM_CALL_STOP_DTMF_RSLT_IND_STRU *)pstMsg;

    PS_MEM_SET(&stDtmfCnf, 0, sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    stDtmfCnf.callId        = pstDtmfRsltIndMsg->ucCallId;
    stDtmfCnf.usClientId    = pstDtmfRsltIndMsg->usClientId;
    stDtmfCnf.opId          = pstDtmfRsltIndMsg->ucOpId;
    stDtmfCnf.enCause       = pstDtmfRsltIndMsg->enCause;
    stDtmfCnf.enDtmfState   = pstDtmfRsltIndMsg->enDtmfState;
    stDtmfCnf.ucDtmfCnt     = pstDtmfRsltIndMsg->ucDtmfCnt;


    TAF_CALL_SendMsg(pstDtmfRsltIndMsg->usClientId,
                     MN_CALL_EVT_STOP_DTMF_RSLT,
                     &stDtmfCnf,
                     sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallSsCmdRslt_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_SS_CMD_RSLT事件的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月30日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallSsCmdRslt_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg      = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

#if ( (FEATURE_ON == FEATURE_ECALL)&& (FEATURE_ON == FEATURE_IMS) )
    if (VOS_TRUE == TAF_SPM_GetEcallHangUpImsFlag())
    {
        return VOS_TRUE;
    }
#endif

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* 构造一条MN_CALL_EVT_SS_CMD_RSLT消息，给相应的cliendId回复 */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_SS_CMD_RSLT,
                       &stCallInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallSsNotify_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_SS_NOTIFY事件的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月30日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallSsNotify_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* 构造一条MN_CALL_EVT_SS_NOTIFY消息，给相应的cliendId回复 */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_SS_NOTIFY,
                       &stCallInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallAllRelease_PreProc
 功能描述  : SPM收到IMSA的MN_CALL_EVT_ALL_RELEASED事件的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月30日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年09月23日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目,更新IMS域业务标识
  3.日    期   : 2014年01月24日
    作    者   : y00245242
    修改内容   : 为呼叫换域重拨功能修改
  4.日    期   : 2014年11月06日
    作    者   : s00217060
    修改内容   : DTS2014110608091:IMS电话时不处理cs域的paging ind
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallAllRelease_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg          = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_ECALL)
#if (FEATURE_IMS == FEATURE_ON)
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstMsgInfo              = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg               = VOS_NULL_PTR;
#endif
#endif
    MN_CALL_INFO_STRU                   stCallInfo;

    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, begin */
    /* 设置IMS域呼叫存在标识 */
    TAF_SDC_SetImsCallExistFlg(VOS_FALSE);
    TAF_SndMmaImsSrvInfoNotify(VOS_FALSE);
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-23, end */

    /* 如果无重拨在GU下发起，需要上报call all release事件给应用 */
    if (VOS_FALSE == TAF_SDC_GetCsCallExistFlg())
    {
        pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

        pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
        pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

        PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

        PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

        /* 增加主动上报相关全局变量的值 */
        PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                    pstCurcRptCtrl->aucRptCfg,
                    MN_CALL_RPT_CFG_MAX_SIZE);

        PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                    pstUnsolicitedRptCtrl->aucRptCfg,
                    MN_CALL_RPT_CFG_MAX_SIZE);

        /* 构造一条MN_CALL_EVT_ALL_RELEASED消息，给相应的cliendId回复 */
        MN_SendClientEvent(pstImsaCallMsg->usClientId,
                           MN_CALLBACK_CS_CALL,
                           MN_CALL_EVT_ALL_RELEASED,
                           &stCallInfo);
    }

#if (FEATURE_ON == FEATURE_ECALL)
#if (FEATURE_IMS == FEATURE_ON)
    if (VOS_TRUE == TAF_SPM_GetEcallHangUpImsFlag())
    {
        TAF_SPM_SetEcallHangUpImsFlag(VOS_FALSE);

        /* 如果缓存为空，缓存定时器已经超时，退出消息处理 */
        if (0 == TAF_SPM_GetCcMsgQueueNum())
        {
            return VOS_TRUE;
        }

        pstMsgInfo      = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);
        pstAppMsg       = (MN_CALL_APP_REQ_MSG_STRU *)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]);

        /* 停止保护定时器TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER */
        TAF_SPM_StopTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

        /* 检查结果为成功设置更新入口消息标记并保存修改后的入口消息到全局变量中 */
        TAF_SPM_UpdateServiceCtrlEntryMsg(pstMsgInfo->stMsgEntry.ulEventType, (struct MsgCB *)pstAppMsg);

        TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

        /* 清除缓存 */
        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);
        return VOS_FALSE;
    }
#endif
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallMsg_PreProc
 功能描述  : SPM收到ID_IMSA_SPM_CALL_MSG的处理
 输入参数  : ulEventType:事件类型
             pstMsg     :消息内容
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
VOS_UINT32 TAF_SPM_RcvImsaCallMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRetFlg;
    TAF_SPM_PROC_IMSA_CALL_MSG_STRU    *pstTabHeader    = VOS_NULL_PTR;
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulTabSize;

    pstImsaCallMsg      = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    /* 获取处理函数的表的首地址 */
    pstTabHeader = TAF_SPM_GetImsaCallMsgTabAddr();

    ulRetFlg     = VOS_TRUE;
    ulTabSize    = TAF_SPM_GetImsaCallMsgTabSize();

    /* 根据EventType查表 */
    for (i = 0; i < ulTabSize; i++)
    {
        if (pstImsaCallMsg->enEventType == pstTabHeader->ulMsgEvtType)
        {
            ulRetFlg = pstTabHeader->pfMsgFun(pstMsg);

            break;
        }

        pstTabHeader++;
    }

    return ulRetFlg;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaGetCallInfoCnf_PreProc
 功能描述  : SPM收到ID_IMSA_SPM_CALL_GET_CALL_INFO_CNF的处理
 输入参数  : ulEventType:事件类型
             pstMsg     :消息内容
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
    修改内容   : VoLTE_PhaseII项目，服务状态改变时通知SPM
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaGetCallInfoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU                   *pstImsaMsg  = VOS_NULL_PTR;

    pstImsaMsg = (IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU *)pstMsg;

    if (MN_CALL_MAX_NUM < pstImsaMsg->ucNumOfCalls)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvImsaGetCallInfoCnf_PreProc: call numbers is abnormal!");

        return VOS_TRUE;
    }

    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, begin */
    if (CALL_IMSA_GET_CALL_INFO_REQ_TYPE_ATA == pstImsaMsg->enReqType)
    {
        /* 请求类型是ATA时调用TAFAGENT API查询呼叫信息,给TAFAGENT回复 */
        TAF_SPM_SendTafAgentGetCallInfoCnf(pstImsaMsg);
    }
    else
    {
        /* 请求类型是CLCC查询呼叫信息,给AT回复 */
        TAF_SPM_SendAtGetCallInfoCnf(pstImsaMsg);
    }
    /* Modified by s00217060 for VoLTE_PhaseII  项目, 2013-09-18, end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaChannelInfoInd_PreProc
 功能描述  : SPM收到ID_IMSA_SPM_CHANNEL_INFO_IND的处理
 输入参数  : ulEventType:事件类型
             pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : s00217060
    修改内容   : 新生成函数

  2.日    期   : 2014年3月29日
    作    者   : W00176964
    修改内容   : DTS2014032901140:接口优化调整
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaChannelInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CHANNEL_INFO_IND_STRU     *pstImsaMsg  = VOS_NULL_PTR;
    MN_CALL_EVT_CHANNEL_INFO_STRU       stChannelEvt;

    pstImsaMsg  = (IMSA_SPM_CHANNEL_INFO_IND_STRU *)pstMsg;

    /* 构造一条消息，给AT回复 */
    PS_MEM_SET(&stChannelEvt, 0x00, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));

    stChannelEvt.enEvent                = MN_CALL_EVT_CHANNEL_INFO_IND;
    stChannelEvt.usClientId             = MN_GetRealClientId(pstImsaMsg->usClientId, WUEPS_PID_TAF);
    stChannelEvt.ucIsLocalAlertingFlag  = pstImsaMsg->ucIsLocalAlertingFlag;
    stChannelEvt.enVoiceDomain          = TAF_CALL_VOICE_DOMAIN_IMS;
    stChannelEvt.enCodecType            = pstImsaMsg->enCodecType;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stChannelEvt, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaGetClprCnf_PreProc
 功能描述  : ID_IMSA_SPM_CALL_GET_CLPR_CNF处理函数
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年09月18日
    作    者   : Y00213812
    修改内容   : 新增函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaGetClprCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_GET_CLPR_CNF_STRU    *pstImsaMsg  = VOS_NULL_PTR;
    MN_CALL_CLPR_GET_CNF_STRU           stClprCnf;

    pstImsaMsg  = (IMSA_SPM_CALL_GET_CLPR_CNF_STRU *)pstMsg;

    /* 构造一条消息，给AT回复 */
    PS_MEM_SET(&stClprCnf, 0x00, sizeof(MN_CALL_CLPR_GET_CNF_STRU));

    stClprCnf.enEvent                   = MN_CALL_EVT_CLPR_SET_CNF;
    stClprCnf.stAppCtrl.usClientId      = pstImsaMsg->usClientId;
    stClprCnf.ulRet                     = pstImsaMsg->ulRet;
    stClprCnf.stRedirectInfo            = pstImsaMsg->stRedirectInfo;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stClprCnf, sizeof(MN_CALL_CLPR_GET_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallHold_PreProc
 功能描述  : SPM收到ID_IMSA_SPM_CALL_HOLD的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年10月31日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallHold_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaMsg              = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    MN_CALL_EVT_HOLD_STRU               stEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();


    pstImsaMsg  = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    PS_MEM_SET(&stEvent, 0, sizeof(MN_CALL_EVT_HOLD_STRU));
    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stEvent.enEvent         = MN_CALL_EVT_HOLD;
    stEvent.usClientId      = MN_GetRealClientId(pstImsaMsg->usClientId, WUEPS_PID_TAF);
    stEvent.ucCallNum       = 1;
    stEvent.aucCallId[0]    = pstImsaMsg->stCallInfo.callId;
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-31, begin */
    stEvent.enVoiceDomain   = pstImsaMsg->stCallInfo.enVoiceDomain;
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-31, end */

    PS_MEM_CPY(stEvent.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                sizeof(stEvent.aucCurcRptCfg));
    PS_MEM_CPY(stEvent.aucUnsolicitedRptCfg,
            pstUnsolicitedRptCtrl->aucRptCfg,
            sizeof(stEvent.aucUnsolicitedRptCfg));

    /* 将HOLD事件发送到AT */
    if (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE))
    {
        MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stEvent, sizeof(MN_CALL_EVT_HOLD_STRU));
    }

    /* 将HOLD事件发送到OAM */
    PS_MEM_CPY(&stCallInfo, &(pstImsaMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    MN_CS_SendMsgToOam(MN_CLIENT_ALL,
                       MN_CALL_EVT_HOLD,
                       MAPS_STK_PID,
                       &stCallInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallRetrieve_PreProc
 功能描述  : SPM收到ID_IMSA_SPM_CALL_RETRIEVE的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2013年10月31日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallRetrieve_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaMsg              = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    MN_CALL_EVT_RETRIEVE_STRU           stEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    pstImsaMsg  = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    PS_MEM_SET(&stEvent, 0, sizeof(MN_CALL_EVT_RETRIEVE_STRU));
    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stEvent.enEvent         = MN_CALL_EVT_RETRIEVE;
    stEvent.usClientId      = MN_GetRealClientId(pstImsaMsg->usClientId, WUEPS_PID_TAF);
    stEvent.ucCallNum       = 1;
    stEvent.aucCallId[0]    = pstImsaMsg->stCallInfo.callId;
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-31, begin */
    stEvent.enVoiceDomain   = pstImsaMsg->stCallInfo.enVoiceDomain;
    /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-31, end */

    PS_MEM_CPY(stEvent.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                sizeof(stEvent.aucCurcRptCfg));
    PS_MEM_CPY(stEvent.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                sizeof(stEvent.aucUnsolicitedRptCfg));

    /* 将RETRIEVE事件发送到AT */
    if (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE))
    {
        MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stEvent, sizeof(MN_CALL_EVT_RETRIEVE_STRU));
    }

    /* 将RETRIEVE事件发送到OAM */
    PS_MEM_CPY(&stCallInfo, &(pstImsaMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    MN_CS_SendMsgToOam(MN_CLIENT_ALL,
                       MN_CALL_EVT_RETRIEVE,
                       MAPS_STK_PID,
                       &stCallInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaSsMsg_PreProc
 功能描述  : 处理IMSA过来的message: ID_IMSA_SPM_SS_MSG
 输入参数  : ulEventType  消息事件类型
             pstRcvMsg    消息指针

 输出参数  : 无
 返 回 值  : VOS_FALSE  消息未处理
             VOS_FALSE  消息已处理

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月11日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaSsMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstRcvMsg
)
{
    IMSA_SPM_SS_MSG_STRU               *pstImsaMsg = VOS_NULL_PTR;


    pstImsaMsg = (IMSA_SPM_SS_MSG_STRU *)pstRcvMsg;

    MN_SendClientEvent(pstImsaMsg->usClientId,
                       MN_CALLBACK_SS,
                       (VOS_UINT32)(pstImsaMsg->stSsEventInfo.SsEvent),
                       (VOS_VOID *)&(pstImsaMsg->stSsEventInfo));

    switch(pstImsaMsg->stSsEventInfo.SsEvent)
    {
        /* 网络主动发起的SS业务需要置上标志 */
        case TAF_SS_EVT_REGISTERSS_CNF:
        case TAF_SS_EVT_USS_NOTIFY_IND:

            TAF_SDC_SetImsSsSrvExistFlg(VOS_TRUE);

            break;

        /* 以下事件需要清除标志 */
        case TAF_SS_EVT_ERROR:
        case TAF_SS_EVT_ERASESS_CNF:
        case TAF_SS_EVT_ACTIVATESS_CNF:
        case TAF_SS_EVT_DEACTIVATESS_CNF:
        case TAF_SS_EVT_INTERROGATESS_CNF:
        case TAF_SS_EVT_PROCESS_USS_REQ_CNF:
        case TAF_SS_EVT_USS_RELEASE_COMPLETE_IND:
        case TAF_SS_EVT_ERASE_CC_ENTRY_CNF:
        case TAF_SS_EVT_PROBLEM:

            TAF_SDC_SetImsSsSrvExistFlg(VOS_FALSE);

            break;

        /* 其他事件时不需要设置/清除标志 */
        default:

            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaNormalRegStatusNotify_PreProc
 功能描述  : 收到ID_IMSA_NORMAL_REG_STATUS_NOTIFY消息的处理, 该消息通知SPM当前
             IMS注册状态，在收到该消息时，SPM本地保存IMS注册状态，并check本地
             缓存队列，如果队列中有缓存消息，将运行域选择，处理缓存消息，并
             相应的停止相关定时器

 输入参数  : ulEventType  消息事件类型
             pstRcvMsg    消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaNormalRegStatusNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;

    /* 处理缓存的消息 */
    ulRst = TAF_SPM_ProcImsaNormalRegStatusNotify(pstMsg);

    return ulRst;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvInternalDomainSelInd_PreProc
 功能描述  : 收到ID_SPM_SPM_INTERNAL_DOMAIN_SEL_IND的处理，收到该消息时，处理缓存的消息

 输入参数  : ulEventType  消息事件类型
             pstRcvMsg    消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvInternalDomainSelInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;

    /* 处理缓存的消息 */
    ulRst = TAF_SPM_ProcBufferedMsgInQueue();

    return ulRst;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvMmaServiceStatusChangeNotify_PreProc
 功能描述  : 收到MMA ID_MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY消息的处理
 输入参数  : ulEventType  消息事件类型
             pstRcvMsg    消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月18日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2014年1月2日
    作    者   : y00245242
    修改内容   : 增加对IMS注册特殊处理功能
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaServiceStatusChangeNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRlst;
    TAF_SPM_SERVICE_STATUS_ENUM_UINT8   enLastPsStatus;
    TAF_SPM_SERVICE_STATUS_ENUM_UINT8   enCurrPsStatus;

    /* 获取上次PS服务状态 */
    enLastPsStatus = TAF_SPM_GetLastPsServiceStatus();

    /* 更新当前的PS服务状态到SPM CONTEXT中 */
    enCurrPsStatus = (TAF_SPM_SERVICE_STATUS_ENUM_UINT8)TAF_SDC_GetPsServiceStatus();
    if (TAF_SPM_SERVICE_STATUS_BUTT < enCurrPsStatus)
    {
        return  VOS_FALSE;
    }
    TAF_SPM_SetLastPsServiceStatus(enCurrPsStatus);

    if (VOS_TRUE == TAF_SPM_IsNeedtoWaitImsRegStatus(enLastPsStatus))
    {
        /* 等待新IMS注册结果 */
        return VOS_TRUE;
    }

    /* 处理缓存的消息 */
    ulRlst = TAF_SPM_ProcBufferedMsgInQueue();

    return ulRlst;

}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvMmaNetworkCapabilityChangeNotify_PreProc
 功能描述  : 收到MMA ID_MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY消息的处理
 输入参数  : ulEventType  消息事件类型
             pstRcvMsg    消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月18日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaNetworkCapabilityChangeNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRlst;

    /* 处理缓存的消息 */
    ulRlst = TAF_SPM_ProcBufferedMsgInQueue();

    return ulRlst;

}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvMmaRatChangeNotify_PreProc
 功能描述  : 收到MMA ID_MMA_TAF_RAT_CHANGE_NOTIFY消息的处理
 输入参数  : ulEventType  消息事件类型
             pstRcvMsg    消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月18日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaRatChangeNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRlst;

    /* 处理缓存的消息，和网络能力变化时的处理一致 */
    ulRlst = TAF_SPM_ProcBufferedMsgInQueue();

    return ulRlst;
}

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, begin */

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvMmaImsVoiceCapInd_PreProc
 功能描述  : 收到MMA ID_MMA_TAF_IMS_VOICE_CAP_IND消息的处理
 输入参数  : ulEventType  消息事件类型
             pstRcvMsg    消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月31日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaImsVoiceCapInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRlst;

    /* 处理缓存的消息，和网络能力变化时的处理一致 */
    ulRlst = TAF_SPM_ProcBufferedMsgInQueue();

    return ulRlst;
}
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, end */


/*****************************************************************************
  函 数 名  : TAF_SPM_RcvImsaCallMsgSyncInd_PreProc
  功能描述  : 收到IMSA的呼叫信息同步指示消息，收到该消息后，清除重拨缓存

  输入参数  : ulEventType -- 消息事件类型
              pstMsg      -- 消息指针

  输出参数  : 无
  返 回 值  : VOS_TRUE  -- 消息处理完成
              VOS_FALSE -- 消息未处理完成

  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2013年12月18日
     作    者   : y00245242
     修改内容   : 新生成函数
 *****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallMsgSyncInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucNum;
    VOS_UINT8                           i;

    /* 呼叫重拨未打开，直接返回 */
    if (VOS_TRUE == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
    {
        /* 由于SRVCC过程前的呼叫请求，走换域重拨流程，IMSA保证在该消息前先发给SPM,
         * 因此，如果收到该消息时，重拨缓存中仍然有消息，它一定是在SRVCC过程中收到，
         * 可以清除呼叫重拨缓存，呼叫请求消息由call模块负责发起
         */
        ucNum = TAF_SPM_GetNumberOfCallRedialBuffer();

        for (i = 0; i < ucNum; i++)
        {
            TAF_SPM_FreeSpecificedIndexCallRedialBuffer(i);
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
  函 数 名  : TAF_SPM_RcvImsaCallInviteNewPtptCnf_PreProc
  功能描述  : 处理邀请第三方通话请求的确认消息

  输入参数  : ulEventType -- 消息事件类型
              pstMsg      -- 消息指针

  输出参数  : 无
  返 回 值  : VOS_TRUE  -- 消息处理完成
              VOS_FALSE -- 消息未处理完成

  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2014年2月13日
     作    者   : y00245242
     修改内容   : 新生成函数
 *****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallInviteNewPtptCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF_STRU                 *pstNewPtptCnf         = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU                             *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU                      *pstUnsolicitedRptCtrl = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                                       stCallInfo;

    pstNewPtptCnf = (IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId = pstNewPtptCnf->usClientId;
    stCallInfo.opId     = pstNewPtptCnf->ucOpId;
    stCallInfo.enCause  = pstNewPtptCnf->enCause;

    /* 增加主动上报相关全局变量的值 */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* 构造一条MN_CALL_EVT_CALL_ORIG_CNF消息，给相应的cliendId回复 */
    MN_SendClientEvent(stCallInfo.clientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_CALL_ORIG_CNF,
                       &stCallInfo);

#if (FEATURE_ON == FEATURE_PTM)
    /* 记录CS呼叫异常log */
    MN_CALL_CsCallErrRecord(0, stCallInfo.enCause);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallTypeChangeInfoInd_PreProc
 功能描述  : SPM收到IMSA的ID_IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND事件的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月17日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallTypeChangeInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND_STRU                 *pstImsaCallMsg           = VOS_NULL_PTR;

    pstImsaCallMsg  = (IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND_STRU *)pstMsg;

    /* 网络下发的紧急呼列表中没有带110，拨打110时，按普通呼叫发出去，IMS指示需要建立紧急承载，以紧急呼重新发起，并携带原因值#380
       IMSA建立紧急承载，以紧急呼发起域内重拨，此时上报ID_IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND，指示呼叫类型变更 */

    /* Modified by s00217060 for 中移动VoLTE需求, 2014-10-17, begin */
    /* 更新重拨缓存消息的call type，在换域重拨时，以紧急呼发CS域重拨 */
    TAF_SPM_UpdateCallRedialBufferMsgWithCallType(pstImsaCallMsg->usClientId,
                                                  pstImsaCallMsg->enDestCallType,
                                                  &(pstImsaCallMsg->stEmergencyCat));
    /* Modified by s00217060 for 中移动VoLTE需求, 2014-10-17, End */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppCallModifyReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的MN_CALL_APP_CALL_MODIFY_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年06月16日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppCallModifyReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    MN_CALL_MODIFY_CNF_STRU             stModifyCnf;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg;

    /* 该消息不进入到状态机处理 */
    ulRet     = VOS_TRUE;
    pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* 构造一条消息，给AT回复 */
    PS_MEM_SET(&stModifyCnf, 0x00, sizeof(MN_CALL_MODIFY_CNF_STRU));

    /* 如果已经IMS域呼叫存在，直接选择IMS域，其他情况返回VOS_FALSE当失败处理 */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
    else
    {
        /* 如果域选择为CS域则直接给AT回复失败 */
        stModifyCnf.enEvent                 = MN_CALL_EVT_CALL_MODIFY_CNF;
        stModifyCnf.usClientId              = pstAppMsg->clientId;
        stModifyCnf.ucOpId                  = pstAppMsg->opId;
        stModifyCnf.ucCallId                = pstAppMsg->callId;
        stModifyCnf.enCause                 = TAF_CS_CAUSE_DOMAIN_SELECTION_FAILURE;

        MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stModifyCnf, sizeof(MN_CALL_MODIFY_CNF_STRU));
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppCallAnswerRemoteModifyReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的MN_CALL_APP_CALL_ANSWER_REMOTE_MODIFY_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年06月16日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppCallAnswerRemoteModifyReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    MN_CALL_MODIFY_CNF_STRU             stModifyCnf;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg;

    /* 该消息不进入到状态机处理 */
    ulRet     = VOS_TRUE;
    pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* 构造一条消息，给AT回复 */
    PS_MEM_SET(&stModifyCnf, 0x00, sizeof(MN_CALL_MODIFY_CNF_STRU));

    /* 如果已经IMS域呼叫存在，直接选择IMS域，其他情况返回VOS_FALSE当失败处理 */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
    else
    {
        /* 如果域选择为CS域则直接给AT回复失败 */
        stModifyCnf.enEvent                 = MN_CALL_EVT_CALL_ANSWER_REMOTE_MODIFY_CNF;
        stModifyCnf.usClientId              = pstAppMsg->clientId;
        stModifyCnf.ucOpId                  = pstAppMsg->opId;
        stModifyCnf.ucCallId                = pstAppMsg->callId;
        stModifyCnf.enCause                 = TAF_CS_CAUSE_DOMAIN_SELECTION_FAILURE;

        MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stModifyCnf, sizeof(MN_CALL_MODIFY_CNF_STRU));
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallModifyCnf_PreProc
 功能描述  : SPM收到ID_IMSA_SPM_CALL_MODIFY_CNF的处理
 输入参数  : ulEventType:事件类型
             pstMsg     :消息内容
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
VOS_UINT32 TAF_SPM_RcvImsaCallModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MODIFY_CNF_STRU      *pstImsaMsg  = VOS_NULL_PTR;
    MN_CALL_MODIFY_CNF_STRU             stModifyCnf;

    pstImsaMsg  = (IMSA_SPM_CALL_MODIFY_CNF_STRU *)pstMsg;

    /* 构造一条消息，给AT回复 */
    PS_MEM_SET(&stModifyCnf, 0x00, sizeof(MN_CALL_MODIFY_CNF_STRU));

    stModifyCnf.enEvent                 = MN_CALL_EVT_CALL_MODIFY_CNF;
    stModifyCnf.usClientId              = pstImsaMsg->usClientId;
    stModifyCnf.ucOpId                  = pstImsaMsg->ucOpId;
    stModifyCnf.ucCallId                = pstImsaMsg->callId;
    stModifyCnf.enCause                 = pstImsaMsg->enCause;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stModifyCnf, sizeof(MN_CALL_MODIFY_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallAnswerRemoteModifyCnf_PreProc
 功能描述  : SPM收到ID_IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF的处理
 输入参数  : ulEventType:事件类型
             pstMsg     :消息内容
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
VOS_UINT32 TAF_SPM_RcvImsaCallAnswerRemoteModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF_STRU    *pstImsaMsg  = VOS_NULL_PTR;
    MN_CALL_MODIFY_CNF_STRU                         stModifyCnf;

    pstImsaMsg  = (IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF_STRU *)pstMsg;

    /* 构造一条消息，给AT回复 */
    PS_MEM_SET(&stModifyCnf, 0x00, sizeof(MN_CALL_MODIFY_CNF_STRU));

    stModifyCnf.enEvent                 = MN_CALL_EVT_CALL_ANSWER_REMOTE_MODIFY_CNF;
    stModifyCnf.usClientId              = pstImsaMsg->usClientId;
    stModifyCnf.ucOpId                  = pstImsaMsg->ucOpId;
    stModifyCnf.ucCallId                = pstImsaMsg->callId;
    stModifyCnf.enCause                 = pstImsaMsg->enCause;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stModifyCnf, sizeof(MN_CALL_MODIFY_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaCallModifyStatusInd_PreProc
 功能描述  : SPM收到ID_IMSA_SPM_CALL_MODIFY_STATUS_IND的处理
 输入参数  : ulEventType:事件类型
             pstMsg     :消息内容
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
VOS_UINT32 TAF_SPM_RcvImsaCallModifyStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU   *pstImsaMsg  = VOS_NULL_PTR;
    MN_CALL_EVT_MODIFY_STATUS_IND_STRU      stModifyInd;

    pstImsaMsg  = (IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU *)pstMsg;

    /* 构造一条消息，给AT回复 */
    PS_MEM_SET(&stModifyInd, 0x00, sizeof(MN_CALL_EVT_MODIFY_STATUS_IND_STRU));

    stModifyInd.enEvent                 = MN_CALL_EVT_CALL_MODIFY_STATUS_IND;
    stModifyInd.usClientId              = MN_GetRealClientId(pstImsaMsg->usClientId, WUEPS_PID_TAF);
    stModifyInd.ucOpId                  = pstImsaMsg->ucOpId;
    stModifyInd.ucCallId                = pstImsaMsg->callId;
    stModifyInd.enModifyStatus          = (MN_CALL_MODIFY_STATUS_ENUM_UINT8)pstImsaMsg->enModifyStatus;
    stModifyInd.enVoiceDomain           = pstImsaMsg->enVoiceDomain;
    stModifyInd.enCurrCallType          = pstImsaMsg->enCurrCallType;
    stModifyInd.enExpectCallType        = pstImsaMsg->enExpectCallType;
    stModifyInd.enCause                 = pstImsaMsg->enCause;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stModifyInd, sizeof(MN_CALL_EVT_MODIFY_STATUS_IND_STRU));

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppEconfDialReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的TAF_CALL_APP_ECONF_DIAL_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月28日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppEconfDialReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg;

    pstAppMsg   = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* 初始化Econf的信息 */
    TAF_SPM_InitEconfInfo();

    /* 解析电话号码相关信息 */
    TAF_SPM_ParseEconfDailInfoFromMsg(pstMsg);

    /* call is allowed if phone mode is power on */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        TAF_SPM_SendAtEconfDialCnf(pstAppMsg->clientId,
                                   pstAppMsg->opId,
                                   pstAppMsg->callId,
                                   TAF_CS_CAUSE_POWER_OFF);
        /* 记录状态 */
        TAF_SPM_SetEconfPreRslt(TAF_CS_CAUSE_POWER_OFF);

        /* 上报Notify Ind */
        TAF_SPM_ReportEconfCheckRslt();

        return VOS_TRUE;
    }

    /* 增强型多方通话只有MN_CALL_TYPE_VOICE类型 */
    if (MN_CALL_TYPE_VOICE != pstAppMsg->unParm.stEconfDial.enCallType)
    {
        TAF_SPM_SendAtEconfDialCnf(pstAppMsg->clientId,
                                   pstAppMsg->opId,
                                   pstAppMsg->callId,
                                   TAF_CS_CAUSE_NOT_ALLOW);
        /* 记录状态 */
        TAF_SPM_SetEconfPreRslt(TAF_CS_CAUSE_NOT_ALLOW);

        /* 上报Notify Ind */
        TAF_SPM_ReportEconfCheckRslt();

        return VOS_TRUE;
    }

    /* forbid normal call when USIM service is not available */
    if (VOS_FALSE == TAF_SPM_IsUsimServiceAvailable())
    {
        TAF_SPM_SendAtEconfDialCnf(pstAppMsg->clientId,
                                   pstAppMsg->opId,
                                   pstAppMsg->callId,
                                   TAF_CS_CAUSE_SIM_NOT_EXIST);
        /* 记录状态 */
        TAF_SPM_SetEconfPreRslt(TAF_CS_CAUSE_SIM_NOT_EXIST);

        /* 上报Notify Ind */
        TAF_SPM_ReportEconfCheckRslt();

        return VOS_TRUE;
    }

    /* 需要判断两个域卡无效,因为单域卡无效的情况能会disable LTE到GU下 */
    if (VOS_FALSE == TAF_SDC_IsUsimStausValid())
    {
        TAF_SPM_SendAtEconfDialCnf(pstAppMsg->clientId,
                                   pstAppMsg->opId,
                                   pstAppMsg->callId,
                                   TAF_CS_CAUSE_SIM_INVALID);

        /* 记录状态 */
        TAF_SPM_SetEconfPreRslt(TAF_CS_CAUSE_SIM_INVALID);

        /* 上报Notify Ind */
        TAF_SPM_ReportEconfCheckRslt();

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaEconfDialCnf_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的ID_IMSA_SPM_CALL_ECONF_DIAL_CNF消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月28日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaEconfDialCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_ECONF_DIAL_CNF_STRU     *pstImsaMsg  = VOS_NULL_PTR;

    pstImsaMsg  = (IMSA_SPM_CALL_ECONF_DIAL_CNF_STRU *)pstMsg;

    /* 只要MO成功时，才设置IMS域呼叫存在标识 */
    if (TAF_CS_CAUSE_SUCCESS == pstImsaMsg->enCause)
    {
        TAF_SDC_SetImsCallExistFlg(VOS_TRUE);
        TAF_SndMmaImsSrvInfoNotify(VOS_TRUE);
    }

    /* 构造一条消息，给AT回复 */
    TAF_SPM_SendAtEconfDialCnf(pstImsaMsg->usClientId,
                               pstImsaMsg->ucOpId,
                               pstImsaMsg->ucCallId,
                               pstImsaMsg->enCause);

#if (FEATURE_ON == FEATURE_PTM)
    /* 记录CS呼叫异常log */
    MN_CALL_CsCallErrRecord(0, pstImsaMsg->enCause);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaEconfAddUsersCnf_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的ID_IMSA_SPM_CALL_ECONF_ADD_USERS_CNF消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月28日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaEconfAddUsersCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_ECONF_ADD_USERS_CNF_STRU     *pstImsaMsg  = VOS_NULL_PTR;

    pstImsaMsg  = (IMSA_SPM_CALL_ECONF_ADD_USERS_CNF_STRU *)pstMsg;

    /* 构造一条消息，给AT回复 */
    TAF_SPM_SendAtEconfDialCnf(pstImsaMsg->usClientId,
                               pstImsaMsg->ucOpId,
                               pstImsaMsg->ucOpId,
                               pstImsaMsg->enCause);

#if (FEATURE_ON == FEATURE_PTM)
    /* 记录CS呼叫异常log */
    MN_CALL_CsCallErrRecord(0, pstImsaMsg->enCause);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaEconfNotifyInd_PreProc
 功能描述  : SPM收到IMSA的ID_IMSA_SPM_CALL_ECONF_NOTIFY_IND事件的处理
 输入参数  : pstMsg     :消息内容
 输出参数  : 无
 返 回 值  : VOS_TRUE:  消息处理完成
             VOS_FALSE: 消息未处理完成，还需要继续处理
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月28日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaEconfNotifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_ECONF_NOTIFY_IND_STRU    *pstImsaMsg      = VOS_NULL_PTR;
    TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU     *pstNotifyInd    = VOS_NULL_PTR;

    pstNotifyInd = (TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU));
    if (VOS_NULL_PTR == pstNotifyInd)
    {
        return VOS_TRUE;
    }

    pstImsaMsg  = (IMSA_SPM_CALL_ECONF_NOTIFY_IND_STRU *)pstMsg;

    /* 构造一条消息，给AT回复 */
    PS_MEM_SET(pstNotifyInd, 0x00, sizeof(TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU));

    pstNotifyInd->enEvent          = TAF_CALL_EVT_ECONF_NOTIFY_IND;
    pstNotifyInd->usClientId       = MN_GetRealClientId(pstImsaMsg->usClientId, WUEPS_PID_TAF);
    pstNotifyInd->ucOpId           = pstImsaMsg->ucOpId;

    if (pstImsaMsg->ucNumOfCalls > TAF_CALL_MAX_ECONF_CALLED_NUM)
    {
        pstNotifyInd->ucNumOfCalls = TAF_CALL_MAX_ECONF_CALLED_NUM;
    }
    else
    {
        pstNotifyInd->ucNumOfCalls = pstImsaMsg->ucNumOfCalls;
    }

    PS_MEM_CPY(pstNotifyInd->astCallInfo,
               pstImsaMsg->astCallInfo,
               sizeof(TAF_CALL_ECONF_INFO_PARAM_STRU) * pstImsaMsg->ucNumOfCalls);

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)pstNotifyInd, sizeof(TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU));

    PS_MEM_FREE(WUEPS_PID_TAF, pstNotifyInd);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvAppGetEconfInfoReq_PreProc
 功能描述  : 预处理状态机初始化状态收到AT的MN_CALL_APP_GET_ECONF_CALLED_INFO_REQ消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : j00174725
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetEconfInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 上层如果来查询会议状态，都发到IMSA去查询 */
    (VOS_VOID)TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvImsaGetEconfInfoCnf_PreProc
 功能描述  : SPM收到ID_IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF的处理
 输入参数  : ulEventType:事件类型
             pstMsg     :消息内容
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
VOS_UINT32 TAF_SPM_RcvImsaGetEconfInfoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU   *pstImsaMsg  = VOS_NULL_PTR;

    pstImsaMsg = (IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU *)pstMsg;

    /* 与会者最多为5个 */
    if (pstImsaMsg->ucNumOfCalls > TAF_CALL_MAX_ECONF_CALLED_NUM)
    {
        pstImsaMsg->ucNumOfCalls = TAF_CALL_MAX_ECONF_CALLED_NUM;
    }

    if (CALL_IMSA_GET_CALL_INFO_REQ_TYPE_CLCC == pstImsaMsg->enReqType)
    {
        /* 请求类型是CLCC查询呼叫信息,给AT回复 */
        TAF_SPM_SendAtGetEconfCallInfoCnf(pstImsaMsg);
    }

    return VOS_TRUE;
}

#endif

/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_RcvCcSrvReqProtectTimerExpired_PreProc
 功能描述  : 收到CC业务保护定时器超时事件的处理, 收到该消息时，根据CC缓存队列中
             的消息，发送业务请求失败给对应的应用,并清除CC缓存队列中的消息

 输入参数  : ulEventType  消息事件类型
             pstRcvMsg    消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvCcSrvReqProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;

    /* 处理缓存的消息 */
    ulRst = TAF_SPM_ProcCcSrvReqProtectTimerExpired();

    return ulRst;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvSmsSrvReqProtectTimerExpired_PreProc
 功能描述  : 收到SMS业务保护定时器超时事件的处理, 收到该消息时，根据CC缓存队列中
             的消息，发送业务请求失败给对应的应用,并清除SMS缓存队列中的消息

 输入参数  : ulEventType  消息事件类型
             pstRcvMsg    消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvSmsSrvReqProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;

    /* 处理缓存的消息 */
    ulRst = TAF_SPM_ProcSmsSrvReqProtectTimerExpired(pstMsg);

    return ulRst;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvSsSrvReqProtectTimerExpired_PreProc
 功能描述  : 收到SS业务保护定时器超时事件的处理, 收到该消息时，根据CC缓存队列中
             的消息，发送业务请求失败给对应的应用,并清除SS缓存队列中的消息

 输入参数  : ulEventType  消息事件类型
             pstRcvMsg    消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月23日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvSsSrvReqProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;

    /* 处理缓存的消息 */
    ulRst = TAF_SPM_ProcSsSrvReqProtectTimerExpired();

    return ulRst;
}
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvMmaPowerOffInd_PreProc
 功能描述  : 收到power off指示的消息处理

 输入参数  : ulEventType -- 消息事件类型
             pstMsg -- 消息指针

 输出参数  : 无
 返 回 值  : VOS_TRUE -- 消息处理完成
             VOS_FALSE -- 消息未处理完成

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月10日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaPowerOffInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

#if (FEATURE_ON == FEATURE_IMS)
    TAF_SPM_ProcMmaPowerOffInd();
#endif

    /* return VOS_FASLE， APS also need this message */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_RcvMmaSrvAcqCnf_PreProc
 功能描述  : 收到mma srv cnf消息时，处理缓存的消息
 输入参数  : ulEventType  消息事件类型
             pstRcvMsg    消息指针
 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月19日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaSrvAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;
    TAF_MMA_SRV_ACQ_CNF_STRU           *pstSrvAcqCnf = VOS_NULL_PTR;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsg = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg    = VOS_NULL_PTR;
    MN_APP_MSG_SEND_REQ_STRU           *pstAppMsgSndReqMsg      = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstSrvAcqCnf = (TAF_MMA_SRV_ACQ_CNF_STRU *)pstMsg;

    /* 业务触发搜网成功，处理缓存 */
    if (TAF_MMA_SRV_ACQ_RESULT_SUCCESS == pstSrvAcqCnf->enResult)
    {
        /* 处理缓存的消息 */
        ulRst = TAF_SPM_ProcBufferedMsgInQueue();

        return ulRst;
    }

    /* 如果搜网失败，缓存有cc的业务回复失败，停止CC缓存定时器 */
    if (0 != TAF_SPM_GetCcMsgQueueNum())
    {
        /* get first index message address */
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);
        pstAppMsg    = (MN_APP_REQ_MSG_STRU *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]);

        /* indicate sender that CC service request is failure */
        TAF_SPM_SendCcServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_CS_CAUSE_NO_RF);


        TAF_SPM_StopTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

        /* clear the first cached message in queue */
        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);

        /* log service domain selection infomation */
        TAF_SPM_LogSrvDomainSelQueueInfo();
    }

    /* 如果搜网失败，缓存有ss的业务回复失败，停止ss缓存定时器 */
    if (0 != TAF_SPM_GetSsMsgQueueNum())
    {
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(0);
        pstAppMsg    = (MN_APP_REQ_MSG_STRU *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]);

        TAF_SPM_SendSsServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_CS_CAUSE_NO_RF);

        TAF_SPM_StopTimer(TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

        /* clear the first cached message in queue */
        TAF_SPM_FreeSpecificedIndexMessageInSsQueue(0);

        /* log service domain selection infomation */
        TAF_SPM_LogSrvDomainSelQueueInfo();
    }

    /* 如果搜网失败，缓存有sms的业务回复失败，停止sms缓存定时器 */
    for (i = 0; i < TAF_SPM_GetSmsMsgQueueNum(); i++)
    {
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(i);

        pstAppMsgSndReqMsg   = (MN_APP_MSG_SEND_REQ_STRU *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[i]);
        ulEventType = pstCachedMsg->stMsgEntry.ulEventType;

        /* 根据client ID查找缓存消息, SMMA消息不起域选择定时器，因此不care */
        if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_SPM_SMMA_IND) != ulEventType)
        {
            /* send fail indication to user */
            TAF_SPM_SendSmsServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                             (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[i]),
                                             TAF_CS_CAUSE_NO_RF);

            TAF_SPM_StopTimer(TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER, pstAppMsgSndReqMsg->usClientId);

            /* clear the first cached message in queue */
            TAF_SPM_FreeSpecificedIndexMessageInSmsQueue(i);

            /* log service domain selection infomation */
            TAF_SPM_LogSrvDomainSelQueueInfo();
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsSsServiceReqAllowed_PreProc
 功能描述  : 判断SS业务是否允许发起

 输入参数  : ulEventType -- 消息事件类型
             pstMsg -- 消息指针

 输出参数  : penCause -- 业务发起失败原因值
 返 回 值  : VOS_TRUE -- 允许发起SS业务
             VOS_FALSE-- 不允许发起SS业务

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月30日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_IsSsServiceReqAllowed_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_ERROR_CODE_ENUM_UINT32         *penCause
)
{
    VOS_UINT32                          ulIsUsimValid;

    *penCause   = TAF_ERR_NO_ERROR;

    ulIsUsimValid   = TAF_SDC_IsUsimStausValid();

    /* SS is allowed if phone mode is power on */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        *penCause   = TAF_ERR_SS_POWER_OFF;
        return VOS_FALSE;
    }

    /* forbid SS when USIM service is not available */
    /* 需要判断两个域卡无效,因为单域卡无效的情况能会disable LTE到GU下,需要到GU下继续尝试 */
    if ( (VOS_FALSE == TAF_SPM_IsUsimServiceAvailable())
      || (VOS_FALSE == ulIsUsimValid) )
    {
        *penCause   = TAF_ERR_USIM_SIM_INVALIDATION;
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsSmsServiceReqAllowed_PreProc
 功能描述  : 判断SMS业务是否允许发起

 输入参数  : ulEventType -- 消息事件类型
             pstMsg -- 消息指针

 输出参数  : penCause -- 业务发起失败原因值
 返 回 值  : VOS_TRUE -- 允许发起SMS业务
             VOS_FALSE-- 不允许发起SMS业务

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月30日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_IsSmsServiceReqAllowed_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    VOS_UINT32                         *pulCause
)
{
    *pulCause   = MN_ERR_NO_ERROR;

    /* SMS is allowed if phone mode is power on */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        *pulCause    = MN_ERR_CLASS_SMS_POWER_OFF;
        return VOS_FALSE;
    }

    /* forbid SMS when USIM service is not available */
    if (VOS_FALSE == TAF_SPM_IsUsimServiceAvailable())
    {
        *pulCause    = MN_ERR_CLASS_SMS_NOUSIM;
        return VOS_FALSE;
    }

    /* 判断两个域卡无效时，直接给AT回复失败 */
    if (VOS_FALSE == TAF_SDC_IsUsimStausValid())
    {
        *pulCause    = MN_ERR_CLASS_SMS_UNAVAILABLE;
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*lint -restore */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


