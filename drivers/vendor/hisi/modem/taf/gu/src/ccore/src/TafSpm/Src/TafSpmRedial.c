

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "VosPidDef.h"
#include "v_msg.h"
#include "TafSdcCtx.h"
#include "TafSpmCtx.h"
#include "TafSpmRedial.h"
#include "NasSms.h"
#include "MnMsgApi.h"
#include "TafSpmMntn.h"
#if (FEATURE_IMS == FEATURE_ON)
#include "SpmImsaInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_REDIAL_C

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
  2 常量定义
*****************************************************************************/


/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 函数实现
*****************************************************************************/

VOS_UINT8 TAF_SPM_IsCallRedialCauseFromImsToCs(TAF_CS_CAUSE_ENUM_UINT32 enCause)
{

    VOS_UINT16                                               usIndex;
    TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU       *pstImsToCsRedialCauseCfg;
    pstImsToCsRedialCauseCfg  = TAF_SDC_GetImsToCsRedialCauseConfig();

    /* 检查原因值enCause是否在IMS重播原因值列表里面 */
    for (usIndex = 0; usIndex < pstImsToCsRedialCauseCfg->ucImsRedialCauseNum; usIndex++)
    {
        if (enCause == pstImsToCsRedialCauseCfg->ausImsRedialCause[usIndex] + TAF_CS_CAUSE_IMS_BEGIN )
        {
            return VOS_TRUE;
        }
    }

    /* 检查原因值enCause是否在IMSA重播原因值列表里面 */
    for (usIndex = 0; usIndex < pstImsToCsRedialCauseCfg->ucImsaRedialCauseNum; usIndex++)
    {
        if (enCause == pstImsToCsRedialCauseCfg->ausImsaRedialCause[usIndex] + TAF_CS_CAUSE_IMSA_BEGIN )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT8 TAF_SPM_IsCsCallRedialAllowed(MN_CALL_INFO_STRU *pstCallInfo)
{

    IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU                    stCallInfoInd;


    PS_MEM_SET(&stCallInfoInd, 0, sizeof(IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU));

    /* 呼叫换域重拨功能关闭，不需要尝试CS域 */
    if (VOS_FALSE == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
    {
        return VOS_FALSE;
    }

    /* 如果该呼叫不是MO，返回 */
    if (MN_CALL_DIR_MO != pstCallInfo->enCallDir)
    {
        return VOS_FALSE;
    }

    /* 调用IMSA提供的API查询当前各路通话的信息，如果已经有IMS域通话，
        第二路通话不管是普通呼叫还是紧急呼，都不换域重拨 */
    (VOS_VOID)IMSA_SpmGetCallInfo(&stCallInfoInd);

    TAF_SPM_LogRedialCallInfo(&stCallInfoInd);

    if (0 < stCallInfoInd.ucNumOfCalls)
    {
        return VOS_FALSE;
    }


    /* 避免冲突场景下呼叫重拨缓存已经被清除，重拨缓存为空，不需要尝试 */
    if (VOS_TRUE == TAF_SPM_IsCallRedialBufferEmpty())
    {
        return VOS_FALSE;
    }

    /* 如果是视频呼叫，不需要尝试CS域 */
    if (TAF_SPM_IS_VIDEO_CALL(pstCallInfo->enCallType))
    {
        return VOS_FALSE;
    }

    /* 如果是紧急呼，无条件发起重拨 */
    if (MN_CALL_TYPE_EMERGENCY == pstCallInfo->enCallType)
    {
        return VOS_TRUE;
    }

    /* 原因值不为重拨cause值，不需要尝试CS域 */
    if (VOS_FALSE == TAF_SPM_IsCallRedialCauseFromImsToCs(pstCallInfo->enCause))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetCallRedialBufferWithCallId(MN_CALL_ID_T ucCallId)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg   = VOS_NULL_PTR;

    ucNum = TAF_SPM_GetNumberOfCallRedialBuffer();

    for (i = 0; (i < ucNum) && (i < TAF_SPM_MAX_CC_MSG_QUEUE_NUM); i++)
    {
        pstCacheMsg = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(i);

        pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)(pstCacheMsg->aucEntryMsgBuffer);

        if (ucCallId == pstAppMsg->callId)
        {
            return pstCacheMsg;
        }
    }

    return VOS_NULL_PTR;
}


VOS_VOID TAF_SPM_FreeCallRedialBufferWithClientId(MN_CLIENT_ID_T usClientId)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg   = VOS_NULL_PTR;

    /* 呼叫重拨未打开，直接返回 */
    if (VOS_FALSE == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
    {
        return;
    }

    ucNum = TAF_SPM_GetNumberOfCallRedialBuffer();

    for (i = 0; (i < ucNum) && (i < TAF_SPM_MAX_CC_MSG_QUEUE_NUM); i++)
    {
        pstCacheMsg = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(i);

        pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)(pstCacheMsg->aucEntryMsgBuffer);

        if (usClientId == pstAppMsg->clientId)
        {
            TAF_SPM_FreeSpecificedIndexCallRedialBuffer(i);
            break;
        }
    }

    TAF_SPM_LogSrvDomainSelRedialInfo();
}


VOS_VOID TAF_SPM_FreeCallRedialBufferWithCallId(MN_CALL_ID_T ucCallId)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg   = VOS_NULL_PTR;

    /* 呼叫重拨未打开，直接返回 */
    if (VOS_FALSE == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
    {
        return;
    }

    ucNum = TAF_SPM_GetNumberOfCallRedialBuffer();

    for (i = 0; (i < ucNum) && (i < TAF_SPM_MAX_CC_MSG_QUEUE_NUM); i++)
    {
        pstCacheMsg = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(i);

        pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)(pstCacheMsg->aucEntryMsgBuffer);

        if (ucCallId == pstAppMsg->callId)
        {
            TAF_SPM_FreeSpecificedIndexCallRedialBuffer(i);
            break;
        }
    }

    TAF_SPM_LogSrvDomainSelRedialInfo();
}


VOS_VOID TAF_SPM_UpdateCallRedialBufferMsgWithCallId(
    MN_CLIENT_ID_T                      usClientId,
    MN_CALL_ID_T                        ucCallId
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAtMsg    = VOS_NULL_PTR;

    /* 呼叫重拨未打开，直接返回 */
    if (VOS_FALSE == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
    {
        return;
    }

    ucNum = TAF_SPM_GetNumberOfCallRedialBuffer();

    for (i = 0; (i < ucNum) && (i < TAF_SPM_MAX_CC_MSG_QUEUE_NUM); i++)
    {
        pstCacheMsg = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(i);

        pstAtMsg = (MN_CALL_APP_REQ_MSG_STRU *)(pstCacheMsg->aucEntryMsgBuffer);

        if (usClientId == pstAtMsg->clientId)
        {
            /* 更新call Id */
            pstAtMsg->callId = ucCallId;
            break;
        }
    }
}



VOS_VOID TAF_SPM_UpdateCallRedialBufferMsgWithCallType(
    MN_CLIENT_ID_T                      usClientId,
    MN_CALL_TYPE_ENUM_U8                enDestCallType,
    MN_CALL_EMERGENCY_CAT_STRU         *pstEmcCat
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAtMsg    = VOS_NULL_PTR;

    /* 呼叫重拨未打开，直接返回 */
    if (VOS_FALSE == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
    {
        return;
    }

    ucNum = TAF_SPM_GetNumberOfCallRedialBuffer();

    for (i = 0; (i < ucNum) && (i < TAF_SPM_MAX_CC_MSG_QUEUE_NUM); i++)
    {
        pstCacheMsg = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(i);

        pstAtMsg = (MN_CALL_APP_REQ_MSG_STRU *)(pstCacheMsg->aucEntryMsgBuffer);

        if (usClientId == pstAtMsg->clientId)
        {
            /* 更新call Id */
            pstAtMsg->unParm.stOrig.enCallType  = enDestCallType;

            /* 呼叫类型由普通呼叫变为紧急呼叫时，紧急呼的类型也要更新 */
            if (MN_CALL_TYPE_EMERGENCY == enDestCallType)
            {
                PS_MEM_CPY(&(pstAtMsg->unParm.stOrig.stEmergencyCat), pstEmcCat, sizeof(MN_CALL_EMERGENCY_CAT_STRU));
            }
            break;
        }
    }
}


VOS_UINT8 TAF_SPM_StoreMsgIntoCallRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucStoreRlst;

    ucStoreRlst = VOS_FALSE;

    if (VOS_FALSE == TAF_SPM_IsCallRedialBufferFull())
    {
        /* 放消息进缓存 */
        ucStoreRlst = (VOS_UINT8)TAF_SPM_PutMsgIntoCallRedialBuffer(ulEventType, pstMsg);
    }

    TAF_SPM_LogSrvDomainSelRedialInfo();

    return ucStoreRlst;
}


VOS_UINT8 TAF_MSG_IsSmsRedialCauseValueFromImsDomain(SMR_SMT_ERROR_ENUM_UINT32 enCause)
{
    MN_MSG_IMSA_CAUSE_ENUM_UINT8        enImsaCause;
#if (VOS_OS_VER == VOS_WIN32)
    VOS_UINT8                           ucRslt;
    MN_MSG_IMS_CAUSE_ENUM_UINT8         enImsCause;

    MN_MSG_RP_CAUSE_ENUM_U8             enRpCause;

    ucRslt = VOS_FALSE;

    if (SMR_SMT_ERROR_IMS_ERROR_BEGIN == (SMR_SMT_ERROR_IMS_ERROR_BEGIN & enCause))
    {
        enImsCause = (MN_MSG_IMS_CAUSE_ENUM_UINT8)(enCause & (~SMR_SMT_ERROR_IMS_ERROR_BEGIN));

        switch (enImsCause)
        {
            case MN_MSG_IMS_CAUSE_INNER_ERROR:
            case MN_MSG_IMS_CAUSE_SMS_INCAPABILITY:
            case MN_MSG_IMS_CAUSE_SMS_NO_SMSC:
            case MN_MSG_IMS_CAUSE_SMS_NO_IPSMGW:
                ucRslt = VOS_TRUE;
                break;

            default:
                break;
        }
    }
    else if (SMR_SMT_ERROR_IMSA_ERROR_BEGIN == (SMR_SMT_ERROR_IMSA_ERROR_BEGIN & enCause))
    {
        enImsaCause = (MN_MSG_IMSA_CAUSE_ENUM_UINT8) (enCause & (~SMR_SMT_ERROR_IMSA_ERROR_BEGIN));

        switch (enImsaCause)
        {
            case MN_MSG_IMSA_CAUSE_NO_SERVICE:
                ucRslt = VOS_TRUE;
                break;

            default:
                break;
        }
    }
    else if (SMR_SMT_ERROR_RP_ERROR_BEGIN == (SMR_SMT_ERROR_RP_ERROR_BEGIN & enCause))
    {
        enRpCause = (MN_MSG_RP_CAUSE_ENUM_U8) (enCause & (~SMR_SMT_ERROR_RP_ERROR_BEGIN));

        switch (enRpCause)
        {
            /* 处理RP cause下的重拨场景，由于需求不明确，目前仅处理如下cause */
            case MN_MSG_RP_CAUSE_NETWORK_OUT_OF_ORDER:                              /* 38 */
            case MN_MSG_RP_CAUSE_TEMPORARY_FAILURE:                                 /* 41 */
            case MN_MSG_RP_CAUSE_CONGESTION:                                        /* 42 */
            case MN_MSG_RP_CAUSE_RESOURCES_UNAVAILABLE_UNSPECIFIED:                 /* 47 */
            case MN_MSG_RP_CAUSE_REQUESTED_FACILITY_NOT_IMPLEMENTED:                /* 69 */
                ucRslt = VOS_TRUE;
                break;

            default:
                break;
        }
    }
    else
    {
        /* 内部错误需要重发的场景 */
        switch (enCause)
        {
            case SMR_SMT_ERROR_TR1M_TIMEOUT:
                ucRslt = VOS_TRUE;
                break;

            default:
                break;
        }
    }

    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_MSG_IsSmsRedialCauseValueFromImsDomain: VOS_OS_VER == VOS_WIN32.");

    return ucRslt;

#else
    /* SMR_SMT_ERROR_IMS_ERROR_BEGIN段内的原因值不仅是现在枚举中定义的值，需要修改成UINT32
       和刘继武确认在mate7上先不区分原因值全部换域重拨，在austin版本上再详细区分 */
    if (SMR_SMT_ERROR_NO_ERROR == enCause)
    {
        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_MSG_IsSmsRedialCauseValueFromImsDomain: no err no recall.");

        return VOS_FALSE;
    }

    if (SMR_SMT_ERROR_IMSA_ERROR_BEGIN == (SMR_SMT_ERROR_IMSA_ERROR_BEGIN & enCause))
    {
        enImsaCause = (MN_MSG_IMSA_CAUSE_ENUM_UINT8) (enCause & (~SMR_SMT_ERROR_IMSA_ERROR_BEGIN));

        if (MN_MSG_IMSA_CAUSE_NO_RF == enImsaCause)
        {
            TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_MSG_IsSmsRedialCauseValueFromImsDomain: no rf no recall.");

            return VOS_FALSE;
        }
    }

    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_MSG_IsSmsRedialCauseValueFromImsDomain: other recall.");

    return VOS_TRUE;

#endif
}


TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetSmsRedialBufferWithClientId(
    VOS_UINT8                          *pucIndex,
    MN_CLIENT_ID_T                      usClientId
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstRedialMsg = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg    = VOS_NULL_PTR;

    ucNum = TAF_SPM_GetNumberOfSmsRedialBuffer();

    for (i = 0; (i < ucNum) && (i < TAF_SPM_MAX_SMS_REDIAL_QUEUE_NUM); i++)
    {
        pstRedialMsg = TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer(i);

        pstAppMsg = (MN_APP_REQ_MSG_STRU *)(pstRedialMsg->aucEntryMsgBuffer);

        if (usClientId == pstAppMsg->clientId)
        {
            *pucIndex = i;

            return pstRedialMsg;
        }
    }

    return VOS_NULL_PTR;
}


VOS_UINT8 TAF_SPM_StoreMsgIntoSmsRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucStoreRlst;

    ucStoreRlst = VOS_FALSE;

    if (VOS_FALSE == TAF_SPM_IsSmsRedialBufferFull())
    {
        /* 放消息进缓存 */
        ucStoreRlst = (VOS_UINT8)TAF_SPM_PutMsgIntoSmsRedialBuffer(ulEventType, pstMsg);
    }

    TAF_SPM_LogSrvDomainSelRedialInfo();

    return ucStoreRlst;
}

/*lint -restore */


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

