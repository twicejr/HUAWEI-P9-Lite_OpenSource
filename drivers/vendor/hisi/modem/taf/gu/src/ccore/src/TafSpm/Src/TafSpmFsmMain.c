

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "AtMnInterface.h"
#include "TafTypeDef.h"
#include "TafSpmCtx.h"
#include "TafSpmFsmMain.h"
#include "TafSpmFsmMainTbl.h"
#include "SsInclude.h"
#include "TafSpmFsmServiceCtrlTbl.h"
#include "TafSpmSndInternalMsg.h"
#include "MnErrorCode.h"
#include "TafLog.h"
#include "AtMnInterface.h"

#include "NasStkInterface.h"
#include "MnCallMnccProc.h"
#include "TafSpmServiceDomainSelProc.h"
#include "TafSdcLib.h"
#include "MnCallApi.h"

#include "TafAgentInterface.h"

#include "TafSpmRedial.h"
#include "TafSpmComFunc.h"
#include "TafSpmServiceDomainSelProc.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_FSM_MAIN_C

/*lint -save -e958 */


VOS_UINT32 TAF_SPM_RcvAppReqMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucIdleFsmIndex;

    (VOS_VOID)TAF_SPM_GetClientIdWithAppMsg(pstMsg, &usClientId);
    TAF_SPM_GetOpIdWithAppMsg(pstMsg, &ucOpId);

    /* 判断是否有存在空闲状态机 */
    ucIdleFsmIndex = TAF_SPM_GetIdleEntityFsmIndex();

    if (TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX == ucIdleFsmIndex)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvAppReqMsg_Main():WARNING: No Idle Entiy Fsm Exist!");
        /* 临时响应改为正式响应 */
        TAF_SPM_SendServiceRequetFail_Main(ulEventType, pstMsg, MN_ERR_CLASS_SPM_BEYOND_CONCURRENCY_CAPABILITY);

#if (FEATURE_ON == FEATURE_IMS)
        TAF_SPM_SetEconfPreRslt(TAF_CS_CAUSE_UNKNOWN);

        TAF_SPM_ReportEconfCheckRslt();
#endif
    }
    else
    {
        /* 设置当前状态机的索引 */
        TAF_SPM_SetCurrEntityFsmAddr(ucIdleFsmIndex);

        /* 设置当前client ID实体状态机的client ID */
        TAF_SPM_SetCurrEntityFsmClientId(usClientId);

        /* 启动service ctrl状态机,进行fdn&CALL control检查 */
        TAF_SPM_FSM_InitEntityFsm(TAF_SPM_FSM_SERVICE_CTRL,
                                      TAF_SPM_GetServiceCtrlFsmDescAddr(),
                                      TAF_SPM_SERVICE_CTRL_STA_INIT);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_SPM_RcvSpmServiceCtrlResultInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SERVICE_CTRL_RSLT_STRU                         *pstServiceCtrlRslt = VOS_NULL_PTR;
    VOS_UINT8                                               ucOpId;
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulAppEventType;
    struct MsgCB                                           *pstAppMsg          = VOS_NULL_PTR;
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;

    ulRet   = VOS_TRUE;

    pstServiceCtrlRslt = (TAF_SPM_SERVICE_CTRL_RSLT_STRU*)pstMsg;

    TAF_SPM_GetOpIdWithAppMsg((struct MsgCB*)pstServiceCtrlRslt->stEntryMsg.aucEntryMsgBuffer, &ucOpId);

    pstAppMsg      = (struct MsgCB*)&(pstServiceCtrlRslt->stEntryMsg.aucEntryMsgBuffer[0]);
    ulAppEventType = pstServiceCtrlRslt->stEntryMsg.ulEventType;

    /* 检查结果为失败 */
    if (TAF_SPM_SERVICE_CTRL_FAIL == pstServiceCtrlRslt->enResult)
    {
        /* 向AT或STK发送失败结果,携带cause,临时响应修改为正式响应 */
        TAF_SPM_SendServiceRequetFail_Main(ulAppEventType, pstAppMsg, pstServiceCtrlRslt->ulCause);

        return VOS_TRUE;
    }

    enDomainSelRslt = TAF_SPM_ProcServiceRequestDomainSelection(ulAppEventType, pstAppMsg);

    ulRet           = TAF_SPM_ProcInitialDomainSelectionResult(ulAppEventType, pstAppMsg, enDomainSelRslt);

    if (VOS_TRUE == ulRet)
    {
        return VOS_TRUE;
    }

    /* 检查结果为成功设置更新入口消息标记并保存修改后的入口消息到全局变量中 */
    TAF_SPM_UpdateServiceCtrlEntryMsg(ulAppEventType, pstAppMsg);

    TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

    return VOS_FALSE;
}

/* 删除 */


/* 对IMSA消息的处理放到预处理中实现 */



VOS_VOID TAF_SPM_SendServiceRequetFail_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    VOS_UINT32                          ulCause
)
{
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType;

    enSrvReqType = TAF_SPM_GetServiceRequestType(pstMsg);

    switch (enSrvReqType)
    {
        case TAF_SPM_SRV_REQ_TYPE_CALL:
            TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, ulCause);
            break;

        case TAF_SPM_SRV_REQ_TYPE_SMS:
            TAF_SPM_SendSmsServiceRequetFail(ulEventType, pstMsg, ulCause);
            break;

        case TAF_SPM_SRV_REQ_TYPE_SS:
            TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)ulCause);
            break;

        default:
            break;

    }

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

