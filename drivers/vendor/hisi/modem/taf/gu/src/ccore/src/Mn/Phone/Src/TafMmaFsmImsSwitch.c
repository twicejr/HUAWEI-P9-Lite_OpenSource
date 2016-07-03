

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "TafMmaCtx.h"
#include "TafMmaSndApp.h"
#include "TafMmaTimerMgmt.h"
#include "TafMmaComFunc.h"
#include "TafLog.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaSndMtc.h"

#if (FEATURE_IMS == FEATURE_ON)
#include "TafMmaFsmImsSwitch.h"
#include "TafMmaFsmImsSwitchTbl.h"
#include "TafMmaSndMscc.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_IMS_SWITCH_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*****************************************************************************
  6 函数实现
*****************************************************************************/

#if (FEATURE_IMS == FEATURE_ON)

VOS_UINT32 TAF_MMA_RcvTafImsSwitchSet_ImsSwitch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU    *pstImsSwitchSet = VOS_NULL_PTR;

    pstImsSwitchSet = (TAF_MMA_IMS_SWITCH_SET_REQ_STRU*)pstMsg;

    /* 保存的入口消息 */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    /* 打开IMS业务功能的流程 */
    if (TAF_MMA_IMS_SWITCH_SET_POWER_ON == pstImsSwitchSet->enImsSwitch)
    {
        /* 发送IMS开启请求给MSCC */
        TAF_MMA_SndMsccImsStartReq();

        /* 迁移状态到等待IMSA的开机回复 */
        TAF_MMA_FSM_SetCurrState(TAF_MMA_IMS_SWITCH_STA_WAIT_MSCC_START_CNF);

        /* 启动保护定时器 */
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_IMS_START_CNF, TI_TAF_MMA_WAIT_MSCC_IMS_START_CNF_LEN);
    }
    else    /* 否则走关闭IMS业务功能的流程 */
    {
        /* 发送IMS关闭请求给MSCC */
        TAF_MMA_SndMsccImsStopReq();

        /* 迁移状态到等待IMSA的关机回复 */
        TAF_MMA_FSM_SetCurrState(TAF_MMA_IMS_SWITCH_STA_WAIT_MSCC_STOP_CNF);

        /* 启动保护定时器 */
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_IMS_STOP_CNF, TI_TAF_MMA_WAIT_MSCC_IMS_STOP_CNF_LEN);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvMsccImsStartCnf_ImsSwitch_WaitMsccImsStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_IMS_START_CNF_STRU         *pstStartCnf = VOS_NULL_PTR;
    TAF_ERROR_CODE_ENUM_UINT32           enErrorCode;

    pstStartCnf = (MSCC_MMA_IMS_START_CNF_STRU *)pstMsg;

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_IMS_START_CNF);

    /* 转换错误码 */
    TAF_MMA_TransMsccImsStartResultToTafErrorCode(pstStartCnf->enResult, &enErrorCode);

    if (TAF_ERR_NO_ERROR == enErrorCode)
    {
        /* 置IMS为已开机 */
        TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_ON);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* 通知MTC IMSA的开关机状态 */
        TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_ON);
#endif

        /* 给上层回复成功 */
        TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                                enErrorCode);

        TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_ON_SUCC);
    }
    else
    {
        /* 置IMS为已关机 */
        TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_OFF);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* 通知MTC IMSA的开关机状态 */
        TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_OFF);
#endif

        /* 回退NV为不支持IMS业务，否则AP查询出来的结果和MODEM维护的不一致 */
        if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportFlag(VOS_FALSE))
        {
            /* warning打印 */
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateLteImsSupportFlag fail!");
        }

        /* 给上层回复失败 */
        TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_FAILURE,
                                                enErrorCode);

        TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_ON_FAIL);
    }

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_RcvTiWaitMsccImsStartCnfExpired_ImsSwitch_WaitMsccImsStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        (VOS_VOID)vos_printf("\n*TAF_MMA_RcvTiWaitMsccImsStartCnfExpired_ImsSwitch_WaitMsccImsStartCnf\n");
    }

    /* warning打印 */
    TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTiWaitMsccImsStartCnfExpired_ImsSwitch_WaitMsccImsStartCnf:time expired!");

    /* 置IMS为已关机 */
    TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_OFF);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* 通知MTC IMSA的开关机状态 */
    TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_OFF);
#endif

    /* 回退NV为不支持IMS业务，否则AP查询出来的结果和MODEM维护的不一致 */
    if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportFlag(VOS_FALSE))
    {
        /* warning打印 */
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateLteImsSupportFlag fail!");
    }

    /* 给上层回复失败 */
    TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_FAILURE,
                                            TAF_ERR_IMS_STACK_TIMEOUT);

    TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_ON_FAIL);

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvMsccImsStopCnf_ImsSwitch_WaitMsccImsStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_IMS_STOP_CNF_STRU          *pstStopCnf = VOS_NULL_PTR;
    TAF_ERROR_CODE_ENUM_UINT32           enErrorCode;

    pstStopCnf = (MSCC_MMA_IMS_STOP_CNF_STRU *)pstMsg;

    /* 停止保护定时器 */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_IMS_STOP_CNF);

    /* 置IMS为已关机 */
    TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_OFF);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* 通知MTC IMSA的开关机状态 */
    TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_OFF);
#endif

    /* 转换错误码 */
    TAF_MMA_TransMsccImsStopResultToTafErrorCode(pstStopCnf->enResult, &enErrorCode);

    if (TAF_ERR_NO_ERROR == enErrorCode)
    {
        /* 给上层回复成功 */
        TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                                enErrorCode);

        TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_OFF_SUCC);
    }
    else
    {
        /* 给上层回复失败 */
        TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_FAILURE,
                                                enErrorCode);

        TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_OFF_FAIL);
    }

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvTiWaitMsccImsStopCnfExpired_ImsSwitch_WaitMsccImsStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        (VOS_VOID)vos_printf("\n*TAF_MMA_RcvTiWaitMsccImsStopCnfExpired_ImsSwitch_WaitMsccImsStopCnf\n");
    }

    /* warning打印 */
    TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTiWaitMsccImsStopCnfExpired_ImsSwitch_WaitMsccImsStopCnf:time expired!");

    /* 置IMS为已关机 */
    TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_OFF);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* 通知MTC IMSA的开机状态 */
    TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_OFF);
#endif

    /* 给上层回复失败 */
    TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_FAILURE,
                                            TAF_ERR_IMS_STACK_TIMEOUT);

    TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_OFF_FAIL);

    /* 退出状态机 */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}


VOS_VOID TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enResult,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    VOS_UINT32                          ulEventType;
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU    *pstImsSwitchSet = VOS_NULL_PTR;

    /* 根据FSM ID获取该FSM 入口消息 */
    pstEntryMsg = TAF_MMA_GetCurrFsmMsgAddr();
    ulEventType = pstEntryMsg->ulEventType;

    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ) == ulEventType)
    {
        pstImsSwitchSet = (TAF_MMA_IMS_SWITCH_SET_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer);

        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   enResult, enErrorCause);

    }

    return;

}

#endif /* FEATURE_IMS */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



