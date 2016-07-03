

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "TafTypeDef.h"
#include "MnCallApi.h"
#include "MnCallSendCc.h"
#include "MnCallMgmt.h"
#include "MnComm.h"
#include "MnErrorCode.h"
#include "UsimPsInterface.h"
#include "MnCallBcProc.h"
#include "NasIeUtil.h"
#include "siapppb.h"
#include "NasOmInterface.h"
#include "MnCallMnccProc.h"
#include "MmaAppLocal.h"
#include "MnCall.h"
#include "MnCallMnccProc.h"
#include "MnCallTimer.h"
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"
#include "MnCallReqProc.h"

#include "NasStkInterface.h"

#include "TafSdcLib.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "NasUsimmApi.h"

#include "TafStdlib.h"

#include "MnCallSendApp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_REQ_PROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/* f_aucCallEmerNumsNoUsim、f_aucCallEmerNumsWithUsim、MN_CALL_MAX_ASCII_NUM_LEN
   f_stMmCallEmerNumList、g_stTafCallCustomEccNumCtx 移到SPM模块 */

#define MN_CALL_MODE_FULL               1   /* full functionality */


/*lint -save -e958 */

/*****************************************************************************
   2 函数实现
*****************************************************************************/

LOCAL VOS_VOID MN_CALL_ActCcbsReqPorc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        ucCallId
)
{
    MN_CALL_SendCcActCcbsReq(ucCallId);

    /* 关注CCBS激活成功事件, 后续操作为上报操作成功 */
    MN_CALL_RegSsKeyEvent(ucCallId,
                          MN_CALL_SS_PROG_EVT_ACT_CCBS_CNF,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

    /*关注CCBS激活失败事件，后续操作为上报操作失败*/
    MN_CALL_RegSsKeyEvent(ucCallId,
                          MN_CALL_SS_PROG_EVT_ACT_CCBS_REJ,
                          MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

    MN_CALL_BeginCallSupsCmdProgress(clientId, MN_CALL_SUPS_CMD_ACT_CCBS);

    MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_SUCCESS);

}


LOCAL VOS_VOID  MN_CALL_RecallCcbsReqPorc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        ucCallId
)
{
    VOS_UINT32                          ulRslt = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];


    /*查找是否有正在通话的呼叫，如果有，则不能发送SETUP消息*/
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    if (0 == ulNumOfCalls)
    {
        ulRslt = MN_CALL_SendCcbsSetupReq(ucCallId);
        /* 消息发送失败，进入错误处理，则清除实体 */
        if ( VOS_OK != ulRslt)
        {
            MN_CALL_FreeCallId(ucCallId);

            MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_UNKNOWN);

            return;
        }

        MN_CALL_UpdateClientId(ucCallId,clientId);
        MN_CALL_UpdateRecallSupsProgress(ucCallId,
                                         MN_CALL_ERR_SS_UNSPECIFIC,
                                         MN_CALL_SS_RES_SUCCESS);

        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_SUCCESS);

        MN_CALL_UpdateCcCallDir(ucCallId, MN_CALL_DIR_MO);
        MN_CALL_UpdateCallState(ucCallId, MN_CALL_S_DIALING);

        /* 如果支持呼叫重建功能，则启动MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD定时器 */
        if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(ucCallId))
        {
            TAF_CALL_StartRedialPeriodTimer(ucCallId);
        }

        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_ORIG);
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_ATTEMPT,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
     }
     else
     {
        /*如果用户选择接受CCBS回呼，则返回失败,当前存在呼叫不能进行回呼*/
        MN_CALL_UpdateClientId(ucCallId, clientId);


        /*挂断指定的呼叫*/
        (VOS_VOID)MN_CALL_SendCcDiscReq(ucCallId, MN_CALL_USER_BUSY);

        /* 记录主动挂断的原因值 */
        MN_CALL_UpdateCcCause(ucCallId, MN_CALL_USER_BUSY);

        /* 记录呼叫挂断的方向 */
        MN_CALL_UpdateDiscCallDir(ucCallId, VOS_TRUE);

        /* 关注该呼叫的挂断完成事件, 后续操作为上报操作成功 */
        MN_CALL_RegSsKeyEvent(ucCallId,
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);


        /*补充业务操作开始进行*/
        MN_CALL_BeginCallSupsCmdProgress(clientId, MN_CALL_SUPS_CMD_ACT_CCBS);

        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_STATE_ERROR);
     }

}


LOCAL VOS_VOID MN_CALL_SupsCmdCcbsReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    /*用户接受CCBS激活或接受CCBS回呼都认为是走AT命令:CHLD+5*/
    MN_CALL_GetCallsByState(MN_CALL_S_CCBS_WAITING_ACTIVE,&ulNumOfCalls,aCallIds);
    if (0 != ulNumOfCalls)
    {
        MN_CALL_ActCcbsReqPorc(clientId, opId, aCallIds[0]);
        return;
    }
    MN_CALL_GetCallsByState(MN_CALL_S_CCBS_WAITING_RECALL,&ulNumOfCalls,aCallIds);
    if (0 != ulNumOfCalls)
    {
        MN_CALL_RecallCcbsReqPorc(clientId, opId, aCallIds[0]);
        return;
    }

    MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_STATE_ERROR);
}

/* MN_CALL_IsValidEmerCategory上移到SPM模块并重命名 */


LOCAL VOS_BOOL MN_CALL_JudgeAllowToBuildMpty(VOS_VOID)
{
    VOS_UINT32                          ulNumOfMptyCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT32                          ulNumOfHoldCalls,ulNumOfActCalls;


    /* 获取处于active或者hold状态的呼叫 */
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfActCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfHoldCalls, aCallIds);


    /* 判定当前是否有呼叫属于MPTY */
    MN_CALL_GetCallsByMptyState(MN_CALL_IN_MPTY, &ulNumOfMptyCalls, aCallIds);
    if (5 <= ulNumOfMptyCalls)
    {
        /* MPTY已经到了上限 */
        MN_WARN_LOG("MN_CALL_JudgeAllowToBuildMpty: Beyond MPTY Capability.");
        return VOS_FALSE;
    }

    if (0 == ulNumOfMptyCalls)
    {
        /* 当前没有MPTY,但是有不止一个处于激活或者hold状态的呼叫 */
        if ((1 != ulNumOfActCalls) || (1 != ulNumOfHoldCalls))
        {
            MN_WARN_LOG("MN_CALL_JudgeAllowToBuildMpty: Not Only One Active or hold Call.");
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }
    else
    {
        if ((0 == ulNumOfActCalls) || (0 == ulNumOfHoldCalls))
        {
            MN_WARN_LOG("MN_CALL_JudgeAllowToBuildMpty: No Active or hold Call.");
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


LOCAL VOS_VOID MN_CALL_CallSupsCmdReqCommProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam,
    VOS_UINT32                          ulRslt
)
{
    /*补充业务操作开始进行*/
    MN_CALL_BeginCallSupsCmdProgress(clientId, pstCallSupsParam->enCallSupsCmd);

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, ulRslt);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              ulRslt);
}


VOS_VOID MN_CALL_CommRelAction(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    MN_CALL_UpdateClientId(callId, clientId);
    (VOS_VOID)MN_CALL_SendCcDiscReq(callId, MN_CALL_USER_BUSY);

    /* 记录主动挂断的原因值 */
    MN_CALL_UpdateCcCause(callId, MN_CALL_USER_BUSY);

    /* 记录呼叫挂断的方向 */
    MN_CALL_UpdateDiscCallDir(callId, VOS_TRUE);

    /* 关注该呼叫的挂断完成事件, 后续操作为上报操作成功 */
    MN_CALL_RegSsKeyEvent(callId,
                          MN_CALL_SS_PROG_EVT_REL,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

    MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);
}


VOS_VOID TAF_CALL_RelIncomingOrWaitingCall(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{
    (VOS_VOID)MN_CALL_SendCcDiscReq(ucCallId, MN_CALL_USER_BUSY);

    /* 记录主动挂断的原因值 */
    MN_CALL_UpdateCcCause(ucCallId, MN_CALL_USER_BUSY);

    /* 记录呼叫挂断的方向 */
    MN_CALL_UpdateDiscCallDir(ucCallId, VOS_TRUE);

    if ((MN_CALL_S_INCOMING == enCallState)
      ||(MN_CALL_S_WAITING == enCallState))
    {
        MN_CALL_StopTimer(MN_CALL_TID_RING);
    }
}


VOS_VOID TAF_CALL_RelRedialingCall(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU      *pstCallSupsParam
)
{
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;

    pstBufferdMsg = MN_CALL_GetBufferedMsg();

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_GetInternalHangUpFlag())
    {
        /* 是TAF内部挂机操作，发送确认消息给TAF */
        TAF_CALL_SetInternalHangUpFlag(VOS_FALSE);
        TAF_CALL_SendTafRelCallCnf(clientId, opId, TAF_CS_CAUSE_SUCCESS);
    }
    else
#endif
    {
        TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

        TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                  opId,
                                                  pstCallSupsParam->callId,
                                                  TAF_CS_CAUSE_SUCCESS);
    }

    if (VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
    {
#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstBufferdMsg->stBufferedSetupMsg.ucCallId))
        {
            /* 停止T9定时器 */
            MN_CALL_StopTimer(TAF_CALL_TID_T9);
        }
#endif
        TAF_CALL_StopAllRedialTimers(pstBufferdMsg->stBufferedSetupMsg.ucCallId);

        TAF_CALL_ProcBufferedRedialMessage(pstBufferdMsg, MN_CALL_NORMAL_CALL_CLEARING);
    }
}


VOS_VOID TAF_CALL_AtaReportOkAsync(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_SUPS_PARAM_STRU      *pstCallSupsParam
)
{
    /* 如果该呼叫的call sub state 为TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK则回复失败*/
    if (TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK == TAF_CALL_GetCallSubState(callId))
    {
        TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_NOT_ALLOW);

        TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                  opId,
                                                  pstCallSupsParam->callId,
                                                  TAF_CS_CAUSE_NOT_ALLOW);

        return;
    }

    /* 设置呼叫子状态为TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK */
    TAF_CALL_SetCallSubState(callId, TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK);

    /*接听该呼叫 */
    (VOS_VOID)MN_CALL_SendCcSetupRsp(callId);
    MN_CALL_StopTimer(MN_CALL_TID_RING);

    /*判断业务信道是否准备好，如果准备好就给VC发送打开声码器操作*/
    if(VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
        {
            /* 发送消息通知VC打开语音通道 */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);

            /* 发送消息通知AT语音通道状态 */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
        }
        MN_CALL_SetChannelOpenFlg(VOS_TRUE);
    }

    /* 更新该呼叫的Client信息 */
    MN_CALL_UpdateClientId(callId, clientId);

    TAF_CALL_SendSupsCmdCnf(clientId, opId, callId, TAF_CS_CAUSE_SUCCESS);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              callId,
                                              TAF_CS_CAUSE_SUCCESS);

    return;
}


LOCAL VOS_VOID MN_CALL_CallSupsCmdRelHoldOrUdubReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    /* 有正在等待的呼叫, 挂断该呼叫(原因为User busy) */
    MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        MN_CALL_CommRelAction(clientId,opId,aCallIds[0],pstCallSupsParam);
        MN_CALL_StopTimer(MN_CALL_TID_RING);
        return;
    }

    /* Incoming状态的也算等待的呼叫, 所以挂断该呼叫(原因为User busy) */
    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        MN_CALL_CommRelAction(clientId,opId,aCallIds[0],pstCallSupsParam);
        MN_CALL_StopTimer(MN_CALL_TID_RING);
        return;
    }

    /* 有被保持的呼叫,挂断所有被保持的呼叫 */
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
    if (0 < ulNumOfCalls)
    {
        /* 挂断所有被保持的呼叫 */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            /*需更新所有呼叫的ClientId*/
            MN_CALL_UpdateClientId(aCallIds[i], clientId);
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* 记录主动挂断的原因值 */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* 记录呼叫挂断的方向 */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* 清除"等待mt eCall呼叫标志位" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* 清除重拨缓存与重拨定时器 */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
        }

        /* 关注最后一个被挂断呼叫的挂断完成事件, 后续操作为上报操作成功 */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }
    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
    {
        /* 有正在等待CCBS激活的呼叫, 挂断该呼叫(原因为User busy) */
        MN_CALL_GetCallsByState(MN_CALL_S_CCBS_WAITING_ACTIVE, &ulNumOfCalls, aCallIds);
        if (0 != ulNumOfCalls)
        {
            MN_CALL_CommRelAction(clientId,opId,aCallIds[0],pstCallSupsParam);
            return;
        }

        /* 有正在等待CCBS回呼的呼叫, 挂断该呼叫(原因为User busy) */
        MN_CALL_GetCallsByState(MN_CALL_S_CCBS_WAITING_RECALL, &ulNumOfCalls, aCallIds);
        if (0 != ulNumOfCalls)
        {
            MN_CALL_CommRelAction(clientId,opId,aCallIds[0],pstCallSupsParam);
            return;
        }
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdRelHoldOrUdubReqProc: state err REL ACT ACPT OTH");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;

}

LOCAL VOS_VOID MN_CALL_CallSupsCmdRelActAcptOthReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    /* 有正在通话的呼叫,挂断所有正在通话的呼叫 */
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* 挂断所有正在通话的呼叫 */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_UpdateClientId(aCallIds[i], clientId);
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* 记录主动挂断的原因值 */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* 记录呼叫挂断的方向 */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* 清除"等待mt eCall呼叫标志位" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* 清除重拨缓存与重拨定时器 */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
        }

        /* 关注最后一个被挂断呼叫的挂断完成事件, 后续操作为接听另一个 */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_ACCPT_OTH);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    /* 有正在等待的呼叫 */
    MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /*接听该呼叫 */
        (VOS_VOID)MN_CALL_SendCcSetupRsp(aCallIds[0]);
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /* 停止MN_CALL_TID_RING定时器 */
        MN_CALL_StopTimer(MN_CALL_TID_RING);

        /* 关注该呼叫的连接建立完成事件, 后续操作为上报操作成功 */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_SETUP_COMPL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* 关注该呼叫的连接挂断完成事件, 后续操作为上报操作失败 */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    /* 有被保持的呼叫 */
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* 如果被保持的呼叫是MTPY,那么恢复MTPY，不然恢复该呼叫*/
        MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
        if (MN_CALL_IN_MPTY == enMptyState)
        {
            /*恢复MPTY*/
            MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                         MN_CALL_SS_RETRIEVEMPTY_OPERATION);
        }
        else
        {
            /*接听该呼叫 */
            MN_CALL_SendCcRetrieveReq(aCallIds[0]);
        }

        /* 更新当前的client */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);
        /* 关注该呼叫的恢复成功事件, 后续操作为上报操作成功 */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* 关注该呼叫的恢复被拒绝事件, 后续操作为上报操作失败 */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdRelActAcptOthReqProc: state err REL ACT ACPT OTH");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;

}


LOCAL VOS_VOID MN_CALL_CallSupsCmdRelCallXReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    /* 此处删除 */



    enCallState    = MN_CALL_S_BUTT;
    enMptyState    = MN_CALL_MPYT_STATE_BUTT;

    /*呼叫X的状态为unknown或idle, 进入错误处理*/
    MN_CALL_GetCallState(pstCallSupsParam->callId, &enCallState, &enMptyState);
    if ((MN_CALL_S_IDLE == enCallState) || (MN_CALL_S_UNKNOWN == enCallState))
    {
        MN_WARN_LOG("MN_CALL_CallSupsCmdRelCallXReqProc: state err REL CALL X");

        TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

        TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                  opId,
                                                  pstCallSupsParam->callId,
                                                  TAF_CS_CAUSE_STATE_ERROR);

        return;
    }

    MN_CALL_UpdateClientId(pstCallSupsParam->callId, clientId);

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstCallSupsParam->callId))
    {
        /* 清除"等待mt eCall呼叫标志位" */
        TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

        /* 清除重拨缓存与重拨定时器 */
        TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(pstCallSupsParam->callId);
    }
#endif

    if ((MN_CALL_S_INCOMING == enCallState)
     || (MN_CALL_S_WAITING == enCallState)
     || (MN_CALL_S_CCBS_WAITING_RECALL == enCallState))
    {
        TAF_CALL_RelIncomingOrWaitingCall(pstCallSupsParam->callId, enCallState);
    }
    /* 如果呼叫处于dialing状态并且呼叫重发间隔定时器在运行，cc处于U0状态，无需
       给cc发送disconnect消息，处理缓存的rej ind消息 */
    else if ((MN_CALL_TIMER_STATUS_RUNING == TAF_CALL_GetRedialIntervalTimerStatus(pstCallSupsParam->callId))
          && (MN_CALL_S_DIALING           == enCallState))
    {
        /* 关注该呼叫的挂断完成事件, 后续操作为上报操作成功 */
        MN_CALL_RegSsKeyEvent(pstCallSupsParam->callId,
            MN_CALL_SS_PROG_EVT_REL,
            MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /*补充业务操作开始进行*/
        MN_CALL_BeginCallSupsCmdProgress(clientId, pstCallSupsParam->enCallSupsCmd);

        /* 记录主动挂断的原因值 */
        MN_CALL_UpdateCcCause(pstCallSupsParam->callId, MN_CALL_NORMAL_CALL_CLEARING);

        /* 记录呼叫挂断的方向 */
        MN_CALL_UpdateDiscCallDir(pstCallSupsParam->callId, VOS_TRUE);

        TAF_CALL_RelRedialingCall(clientId, opId, pstCallSupsParam);
        return;
    }
    else
    {
        /*挂断指定的呼叫*/
        (VOS_VOID)MN_CALL_SendCcDiscReq(pstCallSupsParam->callId, MN_CALL_NORMAL_CALL_CLEARING);

        /* 记录主动挂断的原因值 */
        MN_CALL_UpdateCcCause(pstCallSupsParam->callId, MN_CALL_NORMAL_CALL_CLEARING);

        /* 记录呼叫挂断的方向 */
        MN_CALL_UpdateDiscCallDir(pstCallSupsParam->callId, VOS_TRUE);
    }

    /* 关注该呼叫的挂断完成事件, 后续操作为上报操作成功 */
    MN_CALL_RegSsKeyEvent(pstCallSupsParam->callId,
                          MN_CALL_SS_PROG_EVT_REL,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);


    MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

    MN_NORM_LOG("MN_CALL_CallSupsCmdRelCallXReqProc: send clint res succ.");
    return;
 }


VOS_VOID MN_CALL_CallSupsCmdRelAllCallReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);

    if (0 == ulNumOfCalls)
    {
        MN_WARN_LOG("MN_CALL_CallSupsCmdRelAllCallReqProc: state err REL ALL CALL");

#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_GetInternalHangUpFlag())
        {
            /* 该分支不会发生，异常保护 */
            TAF_CALL_SetInternalHangUpFlag(VOS_FALSE);
            TAF_CALL_SendTafRelCallCnf(clientId, opId, TAF_CS_CAUSE_SUCCESS);
        }
        else
#endif
        {
            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_SUCCESS);
        }

        return;
    }

    /* 挂断所有正在通话的呼叫 */
    for (i = 0; i < ulNumOfCalls; i++)
    {
        MN_CALL_GetCallState(aCallIds[i], &enCallState, &enMptyState);
        MN_CALL_UpdateClientId(aCallIds[i], clientId);
        if ((MN_CALL_S_INCOMING            == enCallState)
         || (MN_CALL_S_WAITING             == enCallState)
         || (MN_CALL_S_CCBS_WAITING_RECALL == enCallState))
        {
            TAF_CALL_RelIncomingOrWaitingCall(aCallIds[i], enCallState);
        }
        /* 如果呼叫处于dialing状态并且呼叫重发间隔定时器在运行，cc处于U0状态，无需
           给cc发送disconnect消息，处理缓存的rej ind消息 */
        else if ((MN_CALL_TIMER_STATUS_RUNING == TAF_CALL_GetRedialIntervalTimerStatus(aCallIds[i]))
              && (MN_CALL_S_DIALING           == enCallState))
        {
            TAF_CALL_RelRedialingCall(clientId, opId, pstCallSupsParam);
            return;
        }
        else
        {
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* 记录主动挂断的原因值 */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* 记录呼叫挂断的方向 */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* 清除"等待mt eCall呼叫标志位" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* 清除重拨缓存与重拨定时器 */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
        }

        MN_CALL_DeRegSsKeyEvent(aCallIds[i],MN_CALL_SS_PROG_EVT_SETUP_COMPL);
        MN_CALL_DeRegSsKeyEvent(aCallIds[i],MN_CALL_SS_PROG_EVT_REL);
    }

    /* 关注最后一个被挂断呼叫的挂断完成事件, 后续操作为接听另一个 */
    MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                          MN_CALL_SS_PROG_EVT_REL,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

    MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

    MN_NORM_LOG("MN_CALL_CallSupsCmdRelAllCallReqProc: send clint res succ.");
    return;
}


LOCAL VOS_VOID MN_CALL_CallSupsCmdHoldActAcptOthReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_ID_T                        ucCallId;
    VOS_UINT32                          ulHeldNumOfCalls;
    VOS_UINT32                          ulIncomingNumOfCalls;
    VOS_UINT32                          ulWaitingNumOfCalls;
    VOS_UINT32                          ulDialNumOfCalls;
    VOS_UINT32                          ulAlertingNumOfCalls;

    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulHeldNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulIncomingNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulWaitingNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_DIALING, &ulDialNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_ALERTING, &ulAlertingNumOfCalls, aCallIds);

    /* 标杆对CHLD=2,满足如下条件时,可以设置:
       if 存在一个激活的呼叫:
           a.当存在并且仅存在一个HOLD的呼叫,或者
           b.当存在并且仅存在一个MT的呼叫,或者
           c.不存在其它呼叫
       else if 存在一个HOLD的呼叫:
           a.当存在并且仅存在一个MT的呼叫,或者
           b.不存在其它呼叫
       else if 存在一个MT的呼叫
    */
    /* 当前有MO呼叫正在拨号或者正在响铃,拒绝用户设置 */
    if ((0 != ulDialNumOfCalls) || (0 != ulAlertingNumOfCalls))
    {
        TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

        TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                  opId,
                                                  pstCallSupsParam->callId,
                                                  TAF_CS_CAUSE_STATE_ERROR);

        return;
    }


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    /* 有正在通话的呼叫 */
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* 当前有一个激活的呼叫,还存在一个HOLD和MT呼叫时,拒绝CHLD=2的设置 */
        if ((0 != ulHeldNumOfCalls) && ((0 != ulIncomingNumOfCalls) || (0 != ulWaitingNumOfCalls)))
        {
            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;
        }

        /* 如果正在通话的呼叫是MTPY,那么保持MTPY*/
        MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
        if (MN_CALL_IN_MPTY == enMptyState)
        {
            /*保持MPTY*/
            MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                         MN_CALL_SS_HOLDMPTY_OPERATION);
        }
        else
        {
            /*保持该呼叫 */
            MN_CALL_SendCcHoldReq(aCallIds[0]);
        }
        /* 更新该呼叫的Client信息 */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /* 关注该呼叫的呼叫的保持被拒绝事件, 后续操作为上报操作失败 */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_HOLD_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        ucCallId = aCallIds[0];

        /*有正在等待的呼叫*/
        MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
        if (0 != ulNumOfCalls)
        {
            /* 更新该呼叫的Client信息 */
            MN_CALL_UpdateClientId(ucCallId, clientId);

            /*关注正在通话的呼叫的保持成功事件, 后续操作为接听另一个 */
            MN_CALL_RegSsKeyEvent(ucCallId,
                                  MN_CALL_SS_PROG_EVT_HOLD_CNF,
                                  MN_CALL_SS_SUBSEQ_OP_ACCPT_OTH);

            /* 关注正在通话的呼叫保持过程中被挂断释放时间，后续操作为接听另一个 */
            MN_CALL_RegSsKeyEvent(ucCallId,
                                  MN_CALL_SS_PROG_EVT_REL,
                                  MN_CALL_SS_SUBSEQ_OP_ACCPT_OTH);

            MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

            return;
        }

        /*有被保持的呼叫*/
        MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
        if (0 != ulNumOfCalls)
        {
            /* 如果被保持的呼叫是MTPY,那么恢复MTPY，不然恢复该呼叫*/
            MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
            if (MN_CALL_IN_MPTY == enMptyState)
            {
                /*恢复 MPTY*/
                MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                     MN_CALL_SS_RETRIEVEMPTY_OPERATION);
            }
            else
            {
                /*恢复该呼叫 */
                MN_CALL_SendCcRetrieveReq(aCallIds[0]);
            }

            /* 更新该呼叫的Client信息 */
            MN_CALL_UpdateClientId(aCallIds[0], clientId);

            /*关注该呼叫的恢复成功事件, 后续操作为上报操作成功*/
            MN_CALL_RegSsKeyEvent(aCallIds[0],
                                  MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

            /*关注该呼叫的恢复被拒绝事件, 后续操作为上报操作失败*/
            MN_CALL_RegSsKeyEvent(aCallIds[0],
                                  MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

            /* 依赖CC模块实现，HOLD CNF接收到就标志HOLD CNF和RETRIEVE CNF都会到达 */
            MN_CALL_RegSsKeyEvent(ucCallId,
                                  MN_CALL_SS_PROG_EVT_HOLD_CNF,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

            MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

            return;
        }

        /* 更新该呼叫的Client信息 */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /*关注正在通话的呼叫的保持成功事件, 后续操作为上报操作成功*/
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_HOLD_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    /*有正在等待的呼叫*/
    MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /*接听该呼叫 */
        (VOS_VOID)MN_CALL_SendCcSetupRsp(aCallIds[0]);
        MN_CALL_StopTimer(MN_CALL_TID_RING);

        /* 更新该呼叫的Client信息 */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /* 关注该呼叫的连接建立成功事件, 后续操作为上报操作成功 */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_SETUP_COMPL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* 关注该呼叫的挂断完成事件, 后续操作为上报操作失败 */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }
    /*有正在等待的呼叫,对应ATA*/
    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* 由于目前发送alert请求消息后，才会上报incoming事件，因此此处不用在下发alert事件 */

        if (VOS_TRUE == TAF_CALL_GetAtaReportOkAsyncFlag())
        {
            TAF_CALL_AtaReportOkAsync(clientId, opId, aCallIds[0], pstCallSupsParam);
            return;
        }

        /*接听该呼叫 */
        (VOS_VOID)MN_CALL_SendCcSetupRsp(aCallIds[0]);
        MN_CALL_StopTimer(MN_CALL_TID_RING);

        /*判断业务信道是否准备好，如果准备好就给VC发送打开声码器操作*/
        if(VOS_TRUE == MN_CALL_GetTchStatus())
        {
            if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
            {
                /* 发送消息通知VC打开语音通道 */
                MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
                /* 发送消息通知AT语音通道状态 */
                MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
            }
            MN_CALL_SetChannelOpenFlg(VOS_TRUE);
        }

        /* 更新该呼叫的Client信息 */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /* 关注该呼叫的连接建立成功事件, 后续操作为上报操作成功 */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_SETUP_COMPL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* 关注该呼叫的挂断完成事件, 后续操作为上报操作失败 */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    /*有被保持的呼叫*/
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* 如果被保持的呼叫是MTPY,那么恢复MTPY，不然恢复该呼叫*/
        MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
        if (MN_CALL_IN_MPTY == enMptyState)
        {
            /*恢复 MPTY*/
            MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                        MN_CALL_SS_RETRIEVEMPTY_OPERATION);
        }
        else
        {
            /*恢复该呼叫 */
            MN_CALL_SendCcRetrieveReq(aCallIds[0]);
        }

        /* 更新该呼叫的Client信息 */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /*关注该呼叫的恢复成功事件, 后续操作为上报操作成功*/
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /*关注该呼叫的恢复被拒绝事件, 后续操作为上报操作失败*/
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err HOLD ACT ACPT OTH");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}


LOCAL VOS_VOID MN_CALL_CallSupsCmdHoldAllExcptXReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstCallSupsParam->callId, &enCallState, &enMptyState);
    if (MN_CALL_IN_MPTY == enMptyState)
    {

        /* 更新该呼叫的Client信息 */
        MN_CALL_UpdateClientId(pstCallSupsParam->callId, clientId);

        /*将呼叫X从MPTY中分离*/
        MN_CALL_SendCcSimpleFacility(pstCallSupsParam->callId,
                                     MN_CALL_SS_SPLITMPTY_OPERATION);

        /*关注该呼叫的分离成功事件, 后续操作为上报操作成功*/
        MN_CALL_RegSsKeyEvent(pstCallSupsParam->callId,
                              MN_CALL_SS_PROG_EVT_SPLIT_MPTY_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /*关注该呼叫的分离被拒绝事件, 后续操作为上报操作失败*/
        MN_CALL_RegSsKeyEvent(pstCallSupsParam->callId,
                              MN_CALL_SS_PROG_EVT_SPLIT_MPTY_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err HOLD ALL EXCPT X");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}


LOCAL VOS_VOID MN_CALL_CallSupsCmdBuildMptyReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    if (VOS_TRUE == MN_CALL_JudgeAllowToBuildMpty())
    {
        /* 建立MPTY */
        MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);

        /* 更新该呼叫的Client信息 */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                     MN_CALL_SS_BUILDMPTY_OPERATION);


        /* 关注该呼叫的建立MPTY成功事件, 后续操作为上报操作成功 */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_BUILD_MPTY_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* 关注该呼叫的建立MPTY被拒绝事件, 后续操作为上报操作失败 */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_BUILD_MPTY_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }
    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err BUILD MPTY");


    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}


LOCAL VOS_VOID MN_CALL_CallSupsCmdDeflectCallReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];

    TAF_CALL_SUB_STATE_ENUM_UINT8       enCallSubState;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aCallIds);
    if (0 == ulNumOfCalls)
    {
        MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
        if (0 == ulNumOfCalls)
        {
            MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err DEFLECT CALL");

            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;
        }
        else
        {
            MN_CALL_StopTimer(MN_CALL_TID_RING);
        }
    }
    else
    {
        /* NV项开启判断incoming呼叫的呼叫子状态为
           TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK则直接上报ERROR */
        enCallSubState = TAF_CALL_GetCallSubState(pstCallSupsParam->callId);

        if ((VOS_TRUE == TAF_CALL_GetAtaReportOkAsyncFlag())
         && (TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK == enCallSubState))
        {
            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;
        }

        MN_CALL_StopTimer(MN_CALL_TID_RING);
    }

    MN_CALL_UpdateRedirNumber(aCallIds[0], &pstCallSupsParam->stRedirectNum);

    /*更新该呼叫的Client信息*/
    MN_CALL_UpdateClientId(aCallIds[0], clientId);

    /* 发出呼叫偏转的补充业务请求 */
    MN_CALL_SendCcDeflectFacility(aCallIds[0], &pstCallSupsParam->stRedirectNum);


    /* 关注该呼叫的偏转成功事件, 后续操作为上报操作成功 */
    MN_CALL_RegSsKeyEvent(aCallIds[0],
                          MN_CALL_SS_PROG_EVT_DEFLECT_CNF,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

    /* 关注该呼叫的偏转被拒绝事件, 后续操作为上报操作失败 */
    MN_CALL_RegSsKeyEvent(aCallIds[0],
                          MN_CALL_SS_PROG_EVT_DEFLECT_REJ,
                          MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

    MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

    MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
    return;

}


LOCAL VOS_VOID MN_CALL_CallSupsCmdEctReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT32                          ulNumOfCalls2;
    MN_CALL_ID_T                        aHeldCallIds[MN_CALL_MAX_NUM];
    MN_CALL_ID_T                        aOtherCallIds[MN_CALL_MAX_NUM];


    PS_MEM_SET(aHeldCallIds,  0x00, sizeof(aHeldCallIds));
    PS_MEM_SET(aOtherCallIds, 0x00, sizeof(aOtherCallIds));

    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aHeldCallIds);
    if ( 0 != ulNumOfCalls )
    {
        MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aOtherCallIds);
        ulNumOfCalls2 = ulNumOfCalls;
        MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aOtherCallIds);
        ulNumOfCalls2 += ulNumOfCalls;
        MN_CALL_GetCallsByState(MN_CALL_S_ALERTING, &ulNumOfCalls, aOtherCallIds);
        ulNumOfCalls2 += ulNumOfCalls;
        if( 0 == ulNumOfCalls2 )
        {
            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;
        }

        /*更新该呼叫的Client信息*/
        MN_CALL_UpdateClientId(aHeldCallIds[0], clientId);

        /* ECT操作 */
        MN_CALL_SendCcSimpleFacility(aHeldCallIds[0],
                                     MN_CALL_SS_ECT_OPERATION);
        /* 关注该呼叫的ECT成功事件, 后续操作为上报操作成功 */
        MN_CALL_RegSsKeyEvent(aHeldCallIds[0],
                              MN_CALL_SS_PROG_EVT_ECT_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* 关注该呼叫的ECT被拒绝事件, 后续操作为上报操作失败 */
        MN_CALL_RegSsKeyEvent(aHeldCallIds[0],
                              MN_CALL_SS_PROG_EVT_ECT_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);


        /*更新另一呼叫的Client信息*/
        MN_CALL_UpdateClientId(aOtherCallIds[0], clientId);


        /* 关注该呼叫的ECT成功事件, 后续操作为上报操作成功 */
        MN_CALL_RegSsKeyEvent(aOtherCallIds[0],
                              MN_CALL_SS_PROG_EVT_ECT_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* 关注该呼叫的ECT被拒绝事件, 后续操作为上报操作失败 */
        MN_CALL_RegSsKeyEvent(aOtherCallIds[0],
                              MN_CALL_SS_PROG_EVT_ECT_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}


LOCAL VOS_VOID MN_CALL_CallSupsCmdRelAllExceptWaitCallReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    VOS_UINT8                           i;

    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* 挂断所有正在通话的呼叫 */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_GetCallState(aCallIds[i], &enCallState, &enMptyState);
            if (( MN_CALL_S_INCOMING != enCallState)
             && ( MN_CALL_S_WAITING != enCallState))
            {
                /* 更新该呼叫的Client信息 */
                MN_CALL_UpdateClientId(aCallIds[i], clientId);
                (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* 记录主动挂断的原因值 */
                MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* 记录呼叫挂断的方向 */
                MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

#if (FEATURE_ON == FEATURE_ECALL)
                if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
                {
                    /* 清除"等待mt eCall呼叫标志位" */
                    TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                    /* 清除重拨缓存与重拨定时器 */
                    TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
                }
#endif
            }
        }

        /* 关注最后一个被挂断呼叫的挂断完成事件, 后续操作为接听另一个 */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err REL ALL CALL");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}


LOCAL VOS_VOID MN_CALL_CallSupsCmdRelHeldReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT8                           i;

    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* 挂断所有正在通话的呼叫 */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            /* 更新该呼叫的Client信息 */
            MN_CALL_UpdateClientId(aCallIds[i], clientId);
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* 记录主动挂断的原因值 */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* 记录呼叫挂断的方向 */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* 清除"等待mt eCall呼叫标志位" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* 清除重拨缓存与重拨定时器 */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
        }

        /* 关注最后一个被挂断呼叫的挂断完成事件, 后续操作为接听另一个 */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err REL ALL CALL");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}


LOCAL VOS_VOID MN_CALL_CallSupsCmdRelActiveReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT8                           i;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* 挂断所有正在通话的呼叫 */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            /* 更新该呼叫的Client信息 */
            MN_CALL_UpdateClientId(aCallIds[i], clientId);
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* 记录主动挂断的原因值 */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* 记录呼叫挂断的方向 */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* 清除"等待mt eCall呼叫标志位" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* 清除重拨缓存与重拨定时器 */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
        }

        /* 关注最后一个被挂断呼叫的挂断完成事件, 后续操作为接听另一个 */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err REL ALL CALL");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}




VOS_VOID  MN_CALL_SetMmEmerNumList(
    MNCC_EMERGENCY_LIST_IND_STRU       *pstMnccEmcListInd
)
{
    VOS_UINT8                           i;

    VOS_UINT32                          j;

    TAF_SDC_MM_EMERGENCY_LIST_STRU     *pstMmCallEmerNumList    = VOS_NULL_PTR;

    pstMmCallEmerNumList                    = TAF_SDC_GetMmCallEmerNumList();

    pstMmCallEmerNumList->ulMcc             = pstMnccEmcListInd->ulMcc;
    pstMmCallEmerNumList->ucEmergencyNumber = pstMnccEmcListInd->ucEmergencyNumber;

    /* 如果紧急呼号码条数超出最大值，则使用最大值 */
    if (pstMnccEmcListInd->ucEmergencyNumber > TAF_SDC_EMER_NUM_LISTS_MAX_NUMBER)
    {
        pstMmCallEmerNumList->ucEmergencyNumber = TAF_SDC_EMER_NUM_LISTS_MAX_NUMBER;
    }
    else
    {
        pstMmCallEmerNumList->ucEmergencyNumber = pstMnccEmcListInd->ucEmergencyNumber;
    }

    /* 将紧急呼号码保存在全局变量中 */
    for (i = 0; i < pstMmCallEmerNumList->ucEmergencyNumber; i++)
    {
        pstMmCallEmerNumList->astEmergencyLists[i].ucCategoryValue = pstMnccEmcListInd->astEmergencyLists[i].ucCategoryValue;
        pstMmCallEmerNumList->astEmergencyLists[i].ucEmcNumLen     = pstMnccEmcListInd->astEmergencyLists[i].ucEmcNumLen;


        /* BCD码中0X0F表示紧急呼叫号码结束，如果BCD码填写为99f947,则需要转换为99f9 */
        for ( j = 0; j < pstMnccEmcListInd->astEmergencyLists[i].ucEmcNumLen; j++ )
        {
            pstMmCallEmerNumList->astEmergencyLists[i].aucEmergencyList[j] = pstMnccEmcListInd->astEmergencyLists[i].aucEmergencyNum[j];

            /* 检测到结束符号0XF_ */
            if (MN_CALL_BCD_ODD_NUMBER_END == (pstMnccEmcListInd->astEmergencyLists[i].aucEmergencyNum[j] & MN_CALL_BCD_ODD_NUMBER_END) )
            {
                /* 需要对长度值重新赋值 */
                pstMmCallEmerNumList->astEmergencyLists[i].ucEmcNumLen = (VOS_UINT8)(j + 1);
                break;
            }

        }

    }
}

/* TAF_SPM_UsimEccNumCheck 、TAF_SPM_NetworkEccNumCheck、TAF_SPM_AppCustomEccNumCheck
    TAF_SPM_EccNumCheck上移到SPM,重命名为TAF_SPM_... */



VOS_UINT32 MN_CALL_GetMoCallBc(
    MN_CALL_ID_T                        CallId,
    NAS_CC_IE_BC_STRU                  *pstBc1,
    NAS_CC_IE_BC_STRU                  *pstBc2,
    MN_CALL_REP_IND_ENUM_U8            *penBcRepeatInd
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulNumOfBc;
    MN_CALL_MGMT_STRU                   stCallInfo;

    ulRet = MN_CALL_GetSpecificCallInfo(CallId, &stCallInfo);
    if (VOS_OK != ulRet)
    {
        return ulRet;
    }

    /* 根据呼叫类型, 呼叫模式和数据呼叫配置生成BC和Repeat Ind参数 */
    PS_MEM_SET(pstBc1, 0, sizeof(NAS_CC_IE_BC_STRU));
    PS_MEM_SET(pstBc2, 0, sizeof(NAS_CC_IE_BC_STRU));

    ulNumOfBc = MN_CALL_BuildBcOfSetup(stCallInfo.stCallInfo.enCallType,
                                       stCallInfo.stCallInfo.enCallMode,
                                       &stCallInfo.stCallInfo.stDataCfgInfo,
                                       pstBc1,
                                       pstBc2);
    if (0 == ulNumOfBc)
    {
        return VOS_ERR;
    }
    else if (TAF_CALL_MAX_BC_NUM == ulNumOfBc)
    {
        /* 有两个BC的情况下，repeat indicator设为alternate */
        *penBcRepeatInd = MN_CALL_REP_IND_ALTER;
    }
    else
    {
        /* 此处需要参考24.008 10.5.4.22 中的定义确认?? */
        *penBcRepeatInd = MN_CALL_REP_IND_NULL;
    }

    return VOS_OK;
}


VOS_UINT32  MN_CALL_BuildNormalCallReqProc(MN_CALL_ID_T callId)
{
    NAS_CC_IE_BC_STRU                   stBc1;
    NAS_CC_IE_BC_STRU                   stBc2;
    MN_CALL_REP_IND_ENUM_U8             enBcRepeatInd;
    VOS_UINT32                          ulRet;
    MN_CALL_MGMT_STRU                   stCallInfo;

    PS_MEM_SET(&stCallInfo, 0, sizeof(stCallInfo));

    ulRet = MN_CALL_GetSpecificCallInfo(callId, &stCallInfo);
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_CALL_BuildNormalCallReqProc: BUILD BC FAIL.");
        return TAF_CS_CAUSE_UNKNOWN;
    }

    ulRet = MN_CALL_GetMoCallBc(stCallInfo.stCallInfo.callId, &stBc1, &stBc2, &enBcRepeatInd);
    if (VOS_OK != ulRet)
    {
        /* 构造BC失败，释放呼叫 */
        MN_WARN_LOG("MN_CALL_BuildNormalCallReqProc: BUILD BC FAIL.");
        return TAF_CS_CAUSE_UNKNOWN;
    }

    /* 由于上报的speed的定义，和API中的定义不同，
       对speed进行转换，直接从BC中进行转换 */
    if ((MN_CALL_TYPE_CS_DATA == stCallInfo.stCallInfo.enCallType)
      ||(MN_CALL_TYPE_FAX == stCallInfo.stCallInfo.enCallType))
    {
        MN_CALL_GetDataCfgInfoFromBc(&stBc1, &stCallInfo.stCallInfo.stDataCfgInfo);
    }
    else
    {
        /* 传真和语音交替，则从BC2中获取 */
        if (( MN_CALL_MODE_AVF == stCallInfo.stCallInfo.enCallMode )
          &&( VOS_TRUE == NAS_IE_IS_PRESENT(&stBc2)))
        {
            MN_CALL_GetDataCfgInfoFromBc(&stBc2, &stCallInfo.stCallInfo.stDataCfgInfo);
        }
    }

    /* FDN检查应该在 MO CONTROL流程前执行，此处流程前移 */

    /* 发送正常呼叫的Setup消息给CC */

    if (VOS_OK != MN_CALL_SendCcSetupReq(enBcRepeatInd,
                                         &stBc1,
                                         &stBc2,
                                         &stCallInfo))
    {
        MN_WARN_LOG("MN_CALL_CallOrigReqProc: SEND MSG ERROR.");
        return TAF_CS_CAUSE_UNKNOWN;
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_ATTEMPT,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }

    return TAF_CS_CAUSE_SUCCESS;
}


VOS_BOOL MN_CALL_CheckNVAllowCallOrig(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    VOS_UINT8                           enVpNvCfgState;

    if (MN_CALL_TYPE_VOICE == enCallType)
    {
        /* VOICE类型的呼叫如果不允许的话，直接返回VOS_FALSE */
        if ( VOS_FALSE == TAF_CALL_GetCallStatusControl())
        {
            return VOS_FALSE;
        }
        return VOS_TRUE;
    }
    enVpNvCfgState = TAF_CALL_GetVpCfgState();
    if (MN_CALL_TYPE_VIDEO == enCallType)
    {
        /* 根据当前的NV项，双向和MO呼叫允许的，返回VOS_TRUE */
        if (( MN_CALL_VP_MO_MT_BOTH == enVpNvCfgState )
         || ( MN_CALL_VP_MO_ONLY == enVpNvCfgState ))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
    return VOS_TRUE;

}


VOS_VOID  MN_CALL_CallOrigReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    MN_CALL_ORIG_PARAM_STRU            *pstOrigParam
)
{
    VOS_UINT32                          ulRet;
    MN_CALL_ID_T                        NewcallId;

    NewcallId = 0;

    /* 紧急呼的判断放在SPM预处理中，这里删除 */

    /* 不允许呼叫，通知呼叫发起方呼叫异常结束 */
    ulRet = MN_CALL_MakeNewCall(pstOrigParam->enCallType,
                                &NewcallId);

    if (TAF_CS_CAUSE_SUCCESS != ulRet)
    {
        MN_NORM_LOG("MN_CALL_CallOrigReqProc: Fail to MN_CALL_MakeNewCall.");

        TAF_CALL_SendCallOrigCnf(clientId, opId, callId, ulRet);

#if (FEATURE_ON == FEATURE_PTM)
        /* 记录CS呼叫异常log */
        MN_CALL_CsCallErrRecord(NewcallId, ulRet);
#endif

        return;
    }
    callId = NewcallId;

    /* 如果是紧急呼叫，则直接发往CC,其他呼叫还需要进行一系列判定 */
    if ((MN_CALL_TYPE_EMERGENCY == pstOrigParam->enCallType)
#if (FEATURE_ON == FEATURE_ECALL)
     || (MN_CALL_TYPE_MIEC      == pstOrigParam->enCallType)
     || (MN_CALL_TYPE_AIEC      == pstOrigParam->enCallType)
#endif
       )
    {
        /*新建一个呼叫实体, ulCcTi并没有实际含义*/
        MN_CALL_CreateMoCallEntity(clientId, opId, callId, pstOrigParam);

        if (VOS_TRUE == pstOrigParam->stEmergencyCat.bExist)
        {
            ulRet = MN_CALL_SendCcEmergSetupReq(callId,
                                                &(pstOrigParam->stEmergencyCat.ucEmergencyCat));

        }
        else
        {
            ulRet = MN_CALL_SendCcEmergSetupReq(callId, VOS_NULL_PTR);
        }

        if (VOS_OK != ulRet)
        {
            MN_WARN_LOG("MN_CALL_CallOrigReqProc: SEND MSG ERROR: emerge.");

            TAF_CALL_SendCallOrigCnf(clientId, opId, callId, TAF_CS_CAUSE_UNKNOWN);

#if (FEATURE_ON == FEATURE_PTM)
            /* 记录CS呼叫异常log */
            MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_UNKNOWN);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }
    }
    else
    {
        /*新建一个呼叫实体, ulCcTi并没有实际含义*/
        MN_CALL_CreateMoCallEntity(clientId, opId, callId, pstOrigParam);

        /* FDN和CALL control的检查出来上移到SPM模块 */

        ulRet = MN_CALL_BuildNormalCallReqProc(callId);

        if (TAF_CS_CAUSE_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_CALL_CallOrigReqProc: MN_CALL_BuildNormalCallReqProc fail.");

            TAF_CALL_SendCallOrigCnf(clientId, opId, callId, ulRet);

#if (FEATURE_ON == FEATURE_PTM)
            /* 记录CS呼叫异常log */
            MN_CALL_CsCallErrRecord(callId, ulRet);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }
    }

    NAS_EventReport(WUEPS_PID_TAF,
                    NAS_OM_EVENT_CC_MO_ATTEMPT,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    MN_CALL_UpdateCallState(callId, MN_CALL_S_DIALING);

#if (FEATURE_ON == FEATURE_ECALL)
    /* 如果T9定时器在running, 停止T9定时器 */
    MN_CALL_StopTimer(TAF_CALL_TID_T9);

    TAF_CALL_ResetEcallPeriodRemainTimerLen();

    TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
#endif

    /* 如果支持呼叫重建功能，则启动MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD定时器 */
    if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(callId))
    {
        TAF_CALL_StartRedialPeriodTimer(callId);
    }

    TAF_CALL_SendCallOrigCnf(clientId, opId, callId, TAF_CS_CAUSE_SUCCESS);


    MN_CALL_ReportEvent(callId, MN_CALL_EVT_ORIG);

    MN_NORM_LOG("MN_CALL_CallOrigReqProc: send clint res normal and report event.");
}


TAF_CS_CAUSE_ENUM_UINT32 MN_CALL_GetEndCause(
    TAF_CS_CAUSE_ENUM_UINT32            enEndCause,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{
    /* 填写对应的挂断原因值 */
    /* enEndCause小于128时用enEndCause，incoming/waiting状态用USER_BUSY，大于127时填interwork unspecified */
    if ( (MN_CALL_INVALID_CAUSE            != enEndCause)
      && (MN_CALL_INTERWORKING_UNSPECIFIED >= enEndCause ) )
    {
        return enEndCause;
    }
    else if ((MN_CALL_S_INCOMING == enCallState)
          || (MN_CALL_S_WAITING == enCallState)
          || (MN_CALL_S_CCBS_WAITING_RECALL == enCallState))
    {
        return TAF_CS_CAUSE_CC_NW_USER_BUSY;
    }
    else if (MN_CALL_INTERWORKING_UNSPECIFIED < enEndCause)
    {
        return MN_CALL_INTERWORKING_UNSPECIFIED;
    }
    else
    {
        return TAF_CS_CAUSE_CC_NW_NORMAL_CALL_CLEARING;
    }

}


VOS_UINT32 MN_CALL_InternalCallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU       *pstEndParm
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_CC_CAUSE_ENUM_U8            enCause;

    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_CC_CAUSE_BUTT;

    /* 获取对应的呼叫状态，如果是Idle和Unknown状态，直接上报错误 */
    MN_CALL_GetCallState(callId, &enCallState, &enMptyState);
    if ((MN_CALL_S_IDLE == enCallState)
     || (MN_CALL_S_UNKNOWN == enCallState))
    {
        if ( MN_CLIENT_ALL != clientId )
        {
            MN_WARN_LOG1("MN_CALL_InternalCallEndReqProc: send clint res err.",TAF_CS_CAUSE_STATE_ERROR);
            return TAF_CS_CAUSE_STATE_ERROR;
        }

    }

    if ((MN_CALL_S_INCOMING == enCallState)
      ||(MN_CALL_S_WAITING == enCallState))
    {
        MN_CALL_StopTimer(MN_CALL_TID_RING);
    }

    /* enCause给CC发Disconnect时用，不能超过127
       pstEndParm->enEndCause需要更新到挂断原因值中，报CEND的时候用 */
    enCause = (MN_CALL_CC_CAUSE_ENUM_U8)MN_CALL_GetEndCause(pstEndParm->enEndCause, enCallState);

    /* 记录主动挂断的原因值 */
    MN_CALL_UpdateCcCause(callId, pstEndParm->enEndCause);

    /* 记录呼叫挂断的方向 */
    MN_CALL_UpdateDiscCallDir(callId, VOS_TRUE);

    /* 发送MNCC_DISC_REQ原语 */
    if (VOS_OK != MN_CALL_SendCcDiscReq(callId, enCause))
    {
        MN_WARN_LOG1("MN_CALL_InternalCallEndReqProc: send clint res err.",TAF_CS_CAUSE_UNKNOWN);
        return TAF_CS_CAUSE_UNKNOWN;
    }

    MN_NORM_LOG("MN_CALL_InternalCallEndReqProc: send clint res normal.");
    return TAF_CS_CAUSE_SUCCESS;

}


VOS_VOID  MN_CALL_CallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU        *pstEndParm
)
{
    VOS_UINT32                          ulRet;

    /* 呼叫处于呼叫相关补充业务过程中，不允许挂断电话 */
    if (VOS_FALSE == MN_CALL_AllowSupsOperation())
    {
        MN_WARN_LOG("MN_CALL_CallEndReqProc: state err ss cmd in progress ");

        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_STATE_ERROR);

        return;

    }

    /* 根据呼叫状态释放呼叫本地资源，并通知网络电话挂断 */
    ulRet = MN_CALL_InternalCallEndReqProc(clientId, opId, callId, pstEndParm);
    if (TAF_CS_CAUSE_SUCCESS != ulRet)
    {
        MN_SendClientResponse(clientId, opId, ulRet);
        return;
    }

    /* 向用户通知挂断请求正在处理 */
    MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_SUCCESS);

    /* 更新用户信息，等待挂断操作的结果 */
    MN_CALL_UpdateClientId(callId, clientId);

    return;

}



VOS_VOID  MN_CALL_CallAnswerReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_ANS_PARAM_STRU        *pstAnsParam
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    enCallState          = MN_CALL_S_BUTT;
    enMptyState          = MN_CALL_MPYT_STATE_BUTT;

    /* 获取对应的呼叫状态，如果不是Incoming或者Waiting状态，直接上报错误 */
    MN_CALL_GetCallState(callId, &enCallState, &enMptyState);
    if ((MN_CALL_S_INCOMING != enCallState) && (MN_CALL_S_WAITING != enCallState))
    {
        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_STATE_ERROR);

#if (FEATURE_ON == FEATURE_PTM)
        /* 记录CS呼叫异常log */
        MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_STATE_ERROR);
#endif

        MN_WARN_LOG1("MN_CALL_CallAnswerReqProc: call state err.state:",enCallState);
        return;
    }

    MN_CALL_StopTimer(MN_CALL_TID_RING);

    /* 由于目前发送alert请求消息后，才会上报incoming事件，因此此处不用在下发alert事件 */

    /*发送MN_SETUP_RES原语接听*/
    if (VOS_OK != MN_CALL_SendCcSetupRsp(callId))
    {
        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_UNKNOWN);

#if (FEATURE_ON == FEATURE_PTM)
        /* 记录CS呼叫异常log */
        MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_UNKNOWN);
#endif

        MN_ERR_LOG1("MN_CALL_CallAnswerReqProc: send clint res err.ulrslt:",TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /*判断业务信道是否准备好，如果准备好就给VC发送打开声码器操作*/
    if(VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
        {
            /* 发送消息通知VC打开语音通道 */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
            /* 发送消息通知AT语音通道状态 */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
        }
        MN_CALL_SetChannelOpenFlg(VOS_TRUE);
    }

    /* 上报应用请求确认 */
    MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_SUCCESS);


    /*更新该呼叫的Client信息*/
    MN_CALL_UpdateClientId(callId, clientId);

    MN_NORM_LOG("MN_CALL_CallEndReqProc: send clint res normal.");
}


VOS_VOID  MN_CALL_CallSupsCmdReqProc(struct MsgCB *pstCallSups)
{
    MN_CALL_CUSTOM_CFG_INFO_STRU       *pstCustomCfgAddr = VOS_NULL_PTR;
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;

    pstCallSupsParam = (MN_CALL_SUPS_PARAM_STRU *)(&((MN_APP_CALL_SUPS_REQ_STRU *)pstCallSups)->stSupsPara);
    clientId         = ((MN_APP_CALL_SUPS_REQ_STRU *)pstCallSups)->usClientId;
    opId             = ((MN_APP_CALL_SUPS_REQ_STRU *)pstCallSups)->opID;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();

    /*
    当前已有补充业务操作，
    如请求类型为挂断所有呼叫
    */
    if (VOS_FALSE == MN_CALL_AllowSupsOperation())
    {
        if ((MN_CALL_SUPS_CMD_REL_ALL_CALL != pstCallSupsParam->enCallSupsCmd)
#if (FEATURE_ON == FEATURE_ECALL)
         && (MN_CALL_SUPS_CMD_REL_ECALL    != pstCallSupsParam->enCallSupsCmd)
#endif
        )
        {
            MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err ss cmd in progress ");

            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;

        }

        TAF_CALL_PreProcRelAllCall();

    }

    switch(pstCallSupsParam->enCallSupsCmd)
    {
        case MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB:
            MN_CALL_CallSupsCmdRelHoldOrUdubReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH:
            MN_CALL_CallSupsCmdRelActAcptOthReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_CALL_X:
            MN_CALL_CallSupsCmdRelCallXReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_ALL_CALL:
            MN_CALL_CallSupsCmdRelAllCallReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH:
            MN_CALL_CallSupsCmdHoldActAcptOthReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X:
            MN_CALL_CallSupsCmdHoldAllExcptXReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_BUILD_MPTY:
            MN_CALL_CallSupsCmdBuildMptyReqProc(clientId, opId, pstCallSupsParam);
            break;
        case MN_CALL_SUPS_CMD_DEFLECT_CALL:
            if ( MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCallDeflectionSupportFlg)
            {
                MN_CALL_CallSupsCmdDeflectCallReqProc(clientId, opId, pstCallSupsParam);
            }
            else
            {
                TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

                TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                          opId,
                                                          pstCallSupsParam->callId,
                                                          TAF_CS_CAUSE_STATE_ERROR);
            }

            break;

        case MN_CALL_SUPS_CMD_ACT_CCBS:
            if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
            {
                MN_CALL_SupsCmdCcbsReqProc(clientId, opId, pstCallSupsParam);
            }
            else
            {
                TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

                TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                          opId,
                                                          pstCallSupsParam->callId,
                                                          TAF_CS_CAUSE_STATE_ERROR);
            }
            break;

        case MN_CALL_SUPS_CMD_ECT:
            MN_CALL_CallSupsCmdEctReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_ALL_EXCEPT_WAITING_CALL:
            MN_CALL_CallSupsCmdRelAllExceptWaitCallReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_HELD:
            MN_CALL_CallSupsCmdRelHeldReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_ACTIVE:
            MN_CALL_CallSupsCmdRelActiveReqProc(clientId, opId, pstCallSupsParam);
            break;

        #if (FEATURE_ON == FEATURE_ECALL)
        case MN_CALL_SUPS_CMD_REL_ECALL:
            TAF_CALL_EcallSupsCmdRelReqProc(clientId, opId, pstCallSupsParam);
            break;
        #endif

        default:
            break;
    }

}



VOS_VOID  MN_CALL_QryAls(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    MN_CALL_QRY_ALS_CNF_STRU       stQryAlsCnf;

    stQryAlsCnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stQryAlsCnf.OpId     = opId;
    stQryAlsCnf.ulRet    = TAF_ERR_NO_ERROR;
    stQryAlsCnf.enEvent  = MN_CALL_EVT_QRY_ALS_CNF;

    stQryAlsCnf.enAlsLine = MN_CALL_GetAlsLineInfo();

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,(VOS_UINT8*)&stQryAlsCnf,sizeof(stQryAlsCnf));

}

VOS_VOID  MN_CALL_QryUus1Info(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    TAF_PH_QRY_UUS1_INFO_CNF_STRU       stQryUus1Cnf;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulChkCuus1IFlg;
    VOS_UINT32                          ulChkCuus1UFlg;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkCuus1IFlg  = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                TAF_SDC_RPT_CMD_CUUS1I);

    ulChkCuus1UFlg  = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                TAF_SDC_RPT_CMD_CUUS1U);

    PS_MEM_SET(&stQryUus1Cnf, 0, sizeof(stQryUus1Cnf));
    stQryUus1Cnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stQryUus1Cnf.OpId     = opId;
    stQryUus1Cnf.ulRet    = TAF_ERR_NO_ERROR;
    stQryUus1Cnf.enEvent  = MN_CALL_EVT_QRY_UUS1_INFO_CNF;

    /* 查询结果里增加CUUS1I和CUUS1U是否需要主动上报的项 */
    stQryUus1Cnf.aenSetType[0] = ulChkCuus1IFlg;
    stQryUus1Cnf.aenSetType[1] = ulChkCuus1UFlg;

    ulRet = MN_CALL_GetCcUus1Info(&stQryUus1Cnf.ulActNum,stQryUus1Cnf.stUus1Info);

    if (VOS_OK != ulRet)
    {
        stQryUus1Cnf.ulRet = TAF_ERR_AT_ERROR;
    }

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,(VOS_UINT8*)&stQryUus1Cnf,sizeof(stQryUus1Cnf));
}


VOS_VOID  MN_CALL_SetAls(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_SET_ALS_PARAM_STRU         *pstAls
)
{
    MN_CALL_SET_ALS_CNF_STRU       stAlsCnf;
    VOS_UINT32                     ulRet;

    stAlsCnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stAlsCnf.OpId     = opId;
    stAlsCnf.ulRet    = TAF_ERR_NO_ERROR;
    stAlsCnf.enEvent  = MN_CALL_EVT_SET_ALS_CNF;

    ulRet = MN_CALL_UpdateAlsLineInfo(pstAls->enAlsLine,VOS_TRUE);

    if (VOS_OK != ulRet )
    {
        stAlsCnf.ulRet = TAF_ERR_UNSPECIFIED_ERROR;
    }

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,(VOS_UINT8*)&stAlsCnf,sizeof(stAlsCnf));

}

VOS_VOID  MN_CALL_SetUus1Info(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_UUS1_PARAM_STRU            *pstUus1Info
)
{
    VOS_UINT32                          i;
    TAF_PH_SET_UUS1_INFO_CNF_STRU       stUus1Cnf;

    /* 获取单个命令主动上报的全局变量 */
    VOS_UINT32                          ulCuus1URptCmdStatus;
    VOS_UINT32                          ulCuus1IRptCmdStatus;

    /* 更新CUUS1I和CUUS1U对应的SDC全局变量 */
    if (MN_CALL_CUUS1_ENABLE == pstUus1Info->enCuus1UFlg)
    {
        ulCuus1URptCmdStatus  = VOS_TRUE;
    }
    else
    {
        ulCuus1URptCmdStatus  = VOS_FALSE;
    }

    if (MN_CALL_CUUS1_ENABLE == pstUus1Info->enCuus1IFlg)
    {
        ulCuus1IRptCmdStatus  = VOS_TRUE;
    }
    else
    {
        ulCuus1IRptCmdStatus  = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUUS1U, ulCuus1URptCmdStatus);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUUS1I, ulCuus1IRptCmdStatus);

    stUus1Cnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stUus1Cnf.OpId     = opId;
    stUus1Cnf.ulRet    = TAF_ERR_NO_ERROR;
    stUus1Cnf.enEvent  = MN_CALL_EVT_SET_UUS1_INFO_CNF;

    for (i = 0; i < pstUus1Info->ulActNum; i++ )
    {
        /* 更新保存在CC中的相关消息的UUS1信息 */
        if (MN_ERR_NO_ERROR != MN_CALL_UpdateCcUus1Info(pstUus1Info->enSetType[i],
                                                       &(pstUus1Info->stUus1Info[i])) )
        {
            stUus1Cnf.ulRet = TAF_ERR_PARA_ERROR;
            break;
         }
    }

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,(VOS_UINT8*)&stUus1Cnf,sizeof(stUus1Cnf));

}


VOS_UINT32 MN_CALL_AddEmerNumsWithUsimToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    VOS_UINT8                           i;
    VOS_CHAR                          **pucEmcNumsWithUsim  = VOS_NULL_PTR;

    pucEmcNumsWithUsim  = TAF_SDC_GetCallEmerNumsWithUsimTblAddr();

    /* 将协议定义的紧急呼号码加入消息 */
    for (i = 0; i < TAF_SDC_NUMOF_EMER_NUMS_WITH_USIM; i++)
    {
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc                  = 0xffffffff;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory             = MN_CALL_ECC_NUM_INVALID_CATEGORY;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent      = MN_CALL_ECC_NUM_VALID_SIM_PRESENT;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg   = VOS_FALSE;

        if (MN_ERR_NO_ERROR != TAF_STD_ConvertAsciiNumberToBcd(pucEmcNumsWithUsim[i],
                            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                            &pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen))
        {
            MN_WARN_LOG("MN_CALL_AddEmerNumsWithUsimToReportList: TAF_STD_ConvertAsciiNumberToBcd Fail.");
        }

        pstEccNumInfo->ulEccNumCount++;

        /* 列表已满 */
        if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 MN_CALL_AddEmerNumsNoUsimToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    VOS_UINT8                           i;
    VOS_CHAR                          **pucEmcNumsNoUsim    = VOS_NULL_PTR;

    pucEmcNumsNoUsim    = TAF_SDC_GetCallEmerNumsNoUsimTblAddr();

    /* 将协议定义的无卡时紧急呼号码 */
    for (i = 0; i < TAF_SDC_NUMOF_EMER_NUMS_NO_USIM; i++)
    {
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc                  = 0xffffffff;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory             = MN_CALL_ECC_NUM_INVALID_CATEGORY;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent      = MN_CALL_ECC_NUM_VALID_SIM_ABSENT;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg   = VOS_FALSE;

        if (MN_ERR_NO_ERROR != TAF_STD_ConvertAsciiNumberToBcd(pucEmcNumsNoUsim[i],
                            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                            &pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen))
        {
            MN_WARN_LOG("MN_CALL_AddEmerNumsNoUsimToReportList: TAF_STD_ConvertAsciiNumberToBcd Fail.");
        }

        pstEccNumInfo->ulEccNumCount++;

        /* 列表已满 */
        if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 MN_CALL_AddEccNumsInUsimToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    SI_PB_ECC_DATA_STRU                *pstEccData;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           i;

    /* 将卡中的紧急呼号码加入消息 */
    pstEccData = (SI_PB_ECC_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(SI_PB_ECC_DATA_STRU));
    if (VOS_NULL_PTR == pstEccData)
    {
        MN_WARN_LOG("MN_CALL_AddEccNumsInUsimToReportList: Alloc Mem Fail.");
        return VOS_FALSE;
    }
    else
    {
        /* 获取USIM中的紧急呼叫号码 */
        PS_MEM_SET(pstEccData, 0, sizeof(SI_PB_ECC_DATA_STRU));
        NAS_PBAPI_GetEccNumber(pstEccData);

        for (i = 0; i < pstEccData->ulReocrdNum; i++)
        {
            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc                  = 0xffffffff;

            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory = 0;

            /* 判断值的有效性 */
            ulResult = TAF_STD_IsValidEmerCategory(pstEccData->astEccRecord[i].ucESC);

            if ( (VOS_TRUE == pstEccData->astEccRecord[i].bESC)
              && (VOS_TRUE == ulResult))
            {
                pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory         = (pstEccData->astEccRecord[i].ucESC & MN_CALL_EMER_CATEGORG_VAL_MAX);
            }

            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent      = MN_CALL_ECC_NUM_VALID_SIM_PRESENT;
            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg   = VOS_FALSE;
            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen            = USIM_ECC_LEN;
            (VOS_VOID)VOS_MemCpy(pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                       pstEccData->astEccRecord[i].aucEccCode,
                       USIM_ECC_LEN);

            pstEccNumInfo->ulEccNumCount++;

            /* 列表已满 */
            if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
            {
                /* 内存释放 */
                PS_MEM_FREE(WUEPS_PID_TAF,pstEccData);
                return VOS_TRUE;
            }
        }

        /* 内存释放 */
        PS_MEM_FREE(WUEPS_PID_TAF,pstEccData);
    }

    return VOS_FALSE;
}


VOS_UINT32 MN_CALL_AddMmEccNumsToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    VOS_UINT8                           i;
    TAF_SDC_MM_EMERGENCY_LIST_STRU     *pstMmCallEmerNumList    = VOS_NULL_PTR;

    pstMmCallEmerNumList    = TAF_SDC_GetMmCallEmerNumList();

    /* 将注册带上来的紧急呼号码加入消息 */
    for (i = 0; i < pstMmCallEmerNumList->ucEmergencyNumber; i++)
    {
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc                  = pstMmCallEmerNumList->ulMcc;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory             = pstMmCallEmerNumList->astEmergencyLists[i].ucCategoryValue;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent      = MN_CALL_ECC_NUM_VALID_SIM_PRESENT;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg   = VOS_FALSE;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen            = pstMmCallEmerNumList->astEmergencyLists[i].ucEmcNumLen;

        (VOS_VOID)VOS_MemCpy(pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                   pstMmCallEmerNumList->astEmergencyLists[i].aucEmergencyList,
                   pstMmCallEmerNumList->astEmergencyLists[i].ucEmcNumLen);

        pstEccNumInfo->ulEccNumCount++;

        /* 列表已满 */
        if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 MN_CALL_AddCustomEccNumsToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    VOS_UINT8                           i;
    TAF_SDC_CUSTOM_ECC_CTX_STRU        *pstCustomCallEmerNumCtx    = VOS_NULL_PTR;

    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    /* 将APP定制的紧急呼号码加入消息 */
    for (i = 0; i < pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount; i++)
    {
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ulMcc;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucCategory;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucAbnormalServiceFlg;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen;

        (VOS_VOID)VOS_MemCpy(pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                   pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                   pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen);

        pstEccNumInfo->ulEccNumCount++;

        /* 列表已满 */
        if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID MN_CALL_ReportEccNumList(VOS_VOID)
{
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo = VOS_NULL_PTR;
    VOS_UINT16                          usLen;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;

    pstCurcRptCtrl                  = TAF_SDC_GetCurcRptCtrl();



    /* 判断主动上报是否打开 */
    if (VOS_FALSE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_XLEMA))
    {
        return;
    }

    pstEccNumInfo = (MN_CALL_ECC_NUM_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_CALL_ECC_NUM_INFO_STRU));
    if (VOS_NULL_PTR == pstEccNumInfo)
    {
        MN_WARN_LOG("MN_CALL_ReportEccNumList: Alloc Mem Fail.");
        return;
    }

    /* 消息初始化 */
    PS_MEM_SET(pstEccNumInfo, 0, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    pstEccNumInfo->enEvent    = MN_CALL_EVT_ECC_NUM_IND;
    pstEccNumInfo->usClientId = MN_GetRealClientId(MN_CLIENT_ALL, WUEPS_PID_TAF);

    /* 获取紧急呼列表 */
    MN_CALL_GetEccNumList(pstEccNumInfo);

    usLen = (VOS_UINT16)sizeof(MN_CALL_ECC_NUM_INFO_STRU);

    /*  上报AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (TAF_UINT8 *)pstEccNumInfo, usLen);

    /* 内存释放 */
    PS_MEM_FREE(WUEPS_PID_TAF,pstEccNumInfo);

    return;
}


VOS_VOID MN_CALL_SaveCustomEccNum(
    MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU*    pstCustomEccNumReq
)
{
    VOS_UINT8                               ucIndex;
    TAF_SDC_CUSTOM_ECC_NUM_STRU            *pstCustomEccNum = VOS_NULL_PTR;

    TAF_SDC_CUSTOM_ECC_CTX_STRU            *pstCustomCallEmerNumCtx    = VOS_NULL_PTR;

    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    /* 当前PLMN不存在定制紧急呼号码，清除当前列表 */
    if ((1 == pstCustomEccNumReq->ucIndex)
     && (1 == pstCustomEccNumReq->ucTotal)
     && (MN_CALL_INVALID_CATEGORY == pstCustomEccNumReq->ucCategory))
    {
        PS_MEM_SET(&pstCustomCallEmerNumCtx->stCustomEccNumList, 0, sizeof(TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU));
    }
    else
    {
        /* 保存定制号码到全局变量 */
        ucIndex         = pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount;
        pstCustomEccNum = &(pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[ucIndex]);

        pstCustomEccNum->ucCategory             = pstCustomEccNumReq->ucCategory;
        pstCustomEccNum->ucValidSimPresent      = pstCustomEccNumReq->ucSimPresent;
        pstCustomEccNum->ulMcc                  = pstCustomEccNumReq->ulMcc;
        pstCustomEccNum->ucEccNumLen            = pstCustomEccNumReq->stEccNum.ucNumLen;
        pstCustomEccNum->ucAbnormalServiceFlg   = pstCustomEccNumReq->ucAbnormalServiceFlg;

        (VOS_VOID)VOS_MemCpy(pstCustomEccNum->aucEccNum,
                   pstCustomEccNumReq->stEccNum.aucBcdNum,
                   pstCustomEccNumReq->stEccNum.ucNumLen);

        (pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount)++;
    }

    return;
}



VOS_VOID MN_CALL_RcvTafEccNumReq(
    MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU*    pstCustomEccNumReq
)
{
    VOS_UINT32                              ulRst;
    MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU   stNvimCustomEccNumList;
    VOS_UINT8                               i;
    MN_CALL_CUSTOM_CFG_INFO_STRU           *pstCustomCfg       = VOS_NULL_PTR;
    TAF_SDC_CUSTOM_ECC_NUM_STRU            *pstCustomEccNum    = VOS_NULL_PTR;
    TAF_SDC_CUSTOM_ECC_CTX_STRU            *pstCustomCallEmerNumCtx    = VOS_NULL_PTR;

    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    pstCustomCfg      = MN_CALL_GetCustomCfgInfo();

    /* 如果index为1,清空定制列表, 标记定制开始 */
    if (1 == pstCustomEccNumReq->ucIndex)
    {
        PS_MEM_SET(&(pstCustomCallEmerNumCtx->stCustomEccNumList), 0, sizeof(TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU));

        pstCustomCallEmerNumCtx->ucCustomSetFlg = VOS_TRUE;
    }

    /* 当前不在定制过程 */
    if (VOS_FALSE == pstCustomCallEmerNumCtx->ucCustomSetFlg)
    {
        /* 丢弃不保存 */
        return;
    }

    /* 保存定制号码到全局变量 */
    MN_CALL_SaveCustomEccNum(pstCustomEccNumReq);

    /* 当INDEX = TOTAL或者定制号码条数达到最大认为本次定制结束 */
    if ((pstCustomEccNumReq->ucIndex == pstCustomEccNumReq->ucTotal)
     || (TAF_SDC_MAX_CUSTOM_ECC_NUM == pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount))
    {
        (VOS_VOID)VOS_MemSet(&stNvimCustomEccNumList, 0, sizeof(MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU));

        stNvimCustomEccNumList.ucEccNumCount = pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount;

        for (i = 0; i < pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount; i++)
        {
            pstCustomEccNum = &(pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i]);

            stNvimCustomEccNumList.astCustomEccNumList[i].ucCategory
                = pstCustomEccNum->ucCategory;
            stNvimCustomEccNumList.astCustomEccNumList[i].ulMcc
                = pstCustomEccNum->ulMcc;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent
                = pstCustomEccNum->ucValidSimPresent;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucAbnormalServiceFlg
                = pstCustomEccNum->ucAbnormalServiceFlg;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucEccNumLen
                = pstCustomEccNum->ucEccNumLen;
            (VOS_VOID)VOS_MemCpy(stNvimCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                       pstCustomEccNum->aucEccNum,
                       pstCustomEccNum->ucEccNumLen);
        }

        /* 标记定制结束 */
        pstCustomCallEmerNumCtx->ucCustomSetFlg = VOS_FALSE;

        /* 将全局变量保存的列表写入NV */
        ulRst = NV_Write(en_NV_Item_CUSTOM_ECC_NUM_LIST,(VOS_VOID*)&stNvimCustomEccNumList,sizeof(MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU));
        if (NV_OK != ulRst)
        {
            MN_ERR_LOG("MN_CALL_RcvTafEccNumReq:Write NVIM Error");
        }

        /* 紧急呼上报控制NV开关打开 */
        if (VOS_TRUE == pstCustomCfg->ucReportEccNumFlg)
        {
            /* 向AT上报当前所有的紧急呼号码 */
            MN_CALL_ReportEccNumList();
        }
    }

    return;
}


VOS_UINT32 MN_CALL_MakeNewCall(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_ID_T                       *pNewCallId
)
{
    MN_CALL_ID_T                        callId;


    /* 获取特性控制NV地址 */

    /* 在MN Call模块上分配CallId MN_CALL_AllocCallId */

    /* 检查NV配置项是否允许发起呼叫 MN_CALL_CheckNVAllowCallOrig */

    /* 检查是否可以发起/接听一个新的呼叫 MN_CALL_IsAllowToMakeNewCall */


    if (VOS_FALSE == MN_CALL_CheckNVAllowCallOrig(enCallType))
    {
        MN_NORM_LOG("MN_CALL_MakeNewCall: Fail to MN_CALL_CheckNVAllowCallOrig.");
        return TAF_CS_CAUSE_NOT_ALLOW;
    }




    /* 在MN Call模块上分配CallId */
    if (VOS_OK != MN_CALL_AllocCallId(&callId))
    {
        MN_WARN_LOG("MN_CALL_MakeNewCall: Null Point.");
        return TAF_CS_CAUSE_NO_CALL_ID;
    }

    *pNewCallId = callId;

    /* 存在其它呼叫实体且状态不是HELD或IDLE，则拒绝新呼叫 */
    if (VOS_TRUE != MN_CALL_IsAllowToMakeNewCall(callId, MN_CALL_DIR_MO))
    {
        MN_WARN_LOG("MN_CALL_MakeNewCall: ONLY SUPPORT ONE CALL.");
        MN_CALL_FreeCallId(callId);
        return TAF_CS_CAUSE_NOT_ALLOW;
    }

    return TAF_CS_CAUSE_SUCCESS;
}




VOS_VOID MN_CALL_RcvAtClprGetReq(MN_CALL_APP_REQ_MSG_STRU            *pstCallMsg)
{
    MN_CALL_CLPR_GET_CNF_STRU           stGetClprCnf;

    PS_MEM_SET(&stGetClprCnf, 0x00, sizeof(MN_CALL_CLPR_GET_CNF_STRU));

    /* 返回MN_CALL_EVT_CLPR_GET_CNF消息 */
    stGetClprCnf.stAppCtrl.usClientId = pstCallMsg->clientId;
    stGetClprCnf.stAppCtrl.ucOpId     = pstCallMsg->opId;
    stGetClprCnf.ulRet                = TAF_ERR_ERROR;
    stGetClprCnf.enEvent              = MN_CALL_EVT_CLPR_SET_CNF;

    /* 检查输入的CALLID是否存在,并且为被叫 */

    if (VOS_TRUE == MN_CALL_CheckCallEntityExist(pstCallMsg->callId))
    {
        MN_CALL_ReadCallEntityRedirectInfo(pstCallMsg->callId, &stGetClprCnf);
    }

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,
                    (VOS_UINT8*)&stGetClprCnf,
                    sizeof(MN_CALL_CLPR_GET_CNF_STRU));

}





VOS_VOID MN_CALL_StkCallOrigReqProc(struct MsgCB * pstMsg)
{
    VOS_UINT32                          ulRet;
    MN_CALL_ID_T                        NewcallId;
    MN_CALL_ID_T                        callId;

    VOS_BOOL                            bSupported;
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstOrigParam = VOS_NULL_PTR;

    pstOrigParam = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstMsg;

    NewcallId = 0;

    /* 获取特性控制NV地址 */

    /* 在MN Call模块上分配CallId MN_CALL_AllocCallId */

    /* 检查NV配置项是否允许发起呼叫 MN_CALL_CheckNVAllowCallOrig */

    /* 检查是否可以发起/接听一个新的呼叫 MN_CALL_IsAllowToMakeNewCall */

    /*
       是紧急呼叫号码，则直接发送EMERGENTCY SETUP CALL消息到CC，并返回:
       2.发送EMERGENTCY SETUP CALL消息到CC，
       3.状态迁移到MN_CALL_S_DIALING
       4.广播上报应用请求确认事件MN_CALL_EVT_NO_ERROR,
       5.广播主叫发起(ORIG)MN_CALL_EVT_ORIG
       6.给STK发送临时响应消息，原因值为MN_ERR_NO_ERROR
       7.退出函数
    */

     /*
       1.发送SETUP CALL消息到CC，
       2.状态迁移到MN_CALL_S_DIALING
       3.广播上报应用请求确认事件MN_CALL_EVT_NO_ERROR,
       4.广播主叫发起(ORIG)MN_CALL_EVT_ORIG
       5.给STK发送临时响应消息，原因值为MN_ERR_NO_ERROR
       6.退出函数

     */


    /* 不允许呼叫，通知呼叫发起方呼叫异常结束 */
    ulRet = MN_CALL_MakeNewCall(pstOrigParam->enCallType, &NewcallId);
    if (TAF_CS_CAUSE_SUCCESS != ulRet)
    {
        MN_NORM_LOG("MN_CALL_StkCallOrigReqProc: Fail to MN_CALL_MakeNewCall.");
        TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                 pstOrigParam->opID,
                                 pstOrigParam->callID,
                                 ulRet);

#if (FEATURE_ON == FEATURE_PTM)
        /* 记录CS呼叫异常log */
        MN_CALL_CsCallErrRecord(NewcallId, ulRet);
#endif

        return;
    }
    callId = NewcallId;

    /* 如果是紧急呼叫，则直接发往CC,其他呼叫还需要进行一系列判定 */
    if (MN_CALL_TYPE_EMERGENCY == pstOrigParam->enCallType)
    {
        MN_CALL_CreateStkMoCallEntity(callId, MN_CALL_TYPE_EMERGENCY, pstOrigParam);

        if (VOS_TRUE == pstOrigParam->stEmergencyCat.bExist)
        {
            ulRet = MN_CALL_SendCcEmergSetupReq(callId, &(pstOrigParam->stEmergencyCat.ucEmergencyCat));
        }
        else
        {
            ulRet = MN_CALL_SendCcEmergSetupReq(callId, VOS_NULL_PTR);
        }

        if (TAF_CS_CAUSE_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_CALL_StkCallOrigReqProc: SEND MSG ERROR: emerge.");
            TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                     pstOrigParam->opID,
                                     callId,
                                     TAF_CS_CAUSE_UNKNOWN);

#if (FEATURE_ON == FEATURE_PTM)
            /* 记录CS呼叫异常log */
            MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_UNKNOWN);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }
    }
    else
    {
        MN_CALL_SupportMoCallType(pstOrigParam->enCallType, &bSupported);
        if (VOS_TRUE != bSupported)
        {
            MN_WARN_LOG("MN_CALL_StkCallOrigReqProc: Fail to MN_CALL_SupportMoCallType.");
            TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                     pstOrigParam->opID,
                                     callId,
                                     TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY);

#if (FEATURE_ON == FEATURE_PTM)
            /* 记录CS呼叫异常log */
            MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }

        MN_CALL_CreateStkMoCallEntity(callId, pstOrigParam->enCallType, pstOrigParam);



        ulRet = MN_CALL_BuildNormalCallReqProc(callId);
        if (TAF_CS_CAUSE_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_CALL_StkCallOrigReqProc: MN_CALL_BuildNormalCallReqProc fail.");
            TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                     pstOrigParam->opID,
                                     callId,
                                     ulRet);

#if (FEATURE_ON == FEATURE_PTM)
            /* 记录CS呼叫异常log */
            MN_CALL_CsCallErrRecord(callId, ulRet);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }
    }

    NAS_EventReport(WUEPS_PID_TAF,
                    NAS_OM_EVENT_CC_MO_ATTEMPT,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    MN_CALL_UpdateCallState(callId, MN_CALL_S_DIALING);

    /* 如果支持呼叫重建功能，则启动MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD定时器 */
    if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(callId))
    {
        TAF_CALL_StartRedialPeriodTimer(callId);
    }

    TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                             pstOrigParam->opID,
                             callId,
                             TAF_CS_CAUSE_SUCCESS);


    MN_CALL_ReportEvent(callId, MN_CALL_EVT_ORIG);

    MN_NORM_LOG("MN_CALL_StkCallOrigReqProc: send clint res normal and report event.");

    return;
}



VOS_VOID  MN_CALL_RcvAtCssnSetReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_SET_CSSN_REQ_STRU          *pstSetCssnReq
)
{
    MN_CALL_SET_CSSN_CNF_STRU           stSetCssnCnf;
    VOS_UINT32                          ulCssiRptStatus;
    VOS_UINT32                          ulCssuRptStatus;

    /* 更新CSSI和CSSU对应的SDC全局变量 */
    if (MN_CALL_SET_CSSN_ACT == pstSetCssnReq->aenSetType[0])
    {
        ulCssiRptStatus = VOS_TRUE;
    }
    else
    {
        ulCssiRptStatus = VOS_FALSE;
    }


    if (MN_CALL_SET_CSSN_ACT == pstSetCssnReq->aenSetType[1])
    {
        ulCssuRptStatus = VOS_TRUE;
    }
    else
    {
        ulCssuRptStatus = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CSSI, ulCssiRptStatus);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CSSU, ulCssuRptStatus);

    PS_MEM_SET(&stSetCssnCnf, 0, sizeof(stSetCssnCnf));
    stSetCssnCnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stSetCssnCnf.OpId     = opId;
    stSetCssnCnf.ulRet    = TAF_ERR_NO_ERROR;
    stSetCssnCnf.enEvent  = MN_CALL_EVT_SET_CSSN_CNF;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8*)&stSetCssnCnf, sizeof(stSetCssnCnf));

}


VOS_VOID MN_CALL_GetEccNumList(MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo)
{
    VOS_UINT32                          ulListFulled;

    if (VOS_NULL_PTR == pstEccNumInfo)
    {
        MN_WARN_LOG("MN_CALL_GetEccNumList: pstEccNumInfo is NULL.");
        return;
    }

    /* 将所有紧急号码都添加入消息 */
    if (TAF_SDC_USIM_STATUS_NO_PRESENT != TAF_SDC_GetUsimStatus())
    {
        /* 将协议定义的有卡时紧急号码加入上报列表 */
        ulListFulled = MN_CALL_AddEmerNumsWithUsimToReportList(pstEccNumInfo);

        /* 列表未满，将卡中的紧急呼号码加入消息 */
        if (VOS_FALSE == ulListFulled)
        {
            ulListFulled = MN_CALL_AddEccNumsInUsimToReportList(pstEccNumInfo);
        }

        /* 列表未满，将MM层上报的紧急呼号码加入消息 */
        if (VOS_FALSE == ulListFulled)
        {
           ulListFulled = MN_CALL_AddMmEccNumsToReportList(pstEccNumInfo);
        }
    }
    else
    {
        /* 将协议定义的无卡时紧急呼号码 */
        ulListFulled = MN_CALL_AddEmerNumsNoUsimToReportList(pstEccNumInfo);
    }

    /* 列表未满,将APP定制的紧急呼号码加入消息 */
    if (VOS_FALSE == ulListFulled)
    {
       (VOS_VOID)MN_CALL_AddCustomEccNumsToReportList(pstEccNumInfo);
    }

    return;
}

VOS_VOID MN_CALL_RcvAtXlemaReq(MN_CALL_APP_REQ_MSG_STRU            *pstCallMsg)
{
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo = VOS_NULL_PTR;
    VOS_UINT16                          usLen;

    pstEccNumInfo = (MN_CALL_ECC_NUM_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_CALL_ECC_NUM_INFO_STRU));
    if (VOS_NULL_PTR == pstEccNumInfo)
    {
        MN_WARN_LOG("MN_CALL_RcvAtXlemaReq: Alloc Mem Fail.");
        return;
    }

    /* 消息初始化 */
    PS_MEM_SET(pstEccNumInfo, 0, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    pstEccNumInfo->enEvent    = MN_CALL_EVT_XLEMA_CNF;
    pstEccNumInfo->usClientId = pstCallMsg->clientId;

    /* 获取紧急呼列表 */
    MN_CALL_GetEccNumList(pstEccNumInfo);

    usLen = (VOS_UINT16)sizeof(MN_CALL_ECC_NUM_INFO_STRU);

    /* 上报AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (TAF_UINT8 *)pstEccNumInfo, usLen);

    /* 内存释放 */
    PS_MEM_FREE(WUEPS_PID_TAF, pstEccNumInfo);

    return;
}



VOS_VOID  TAF_CALL_RcvStartDtmfReq(struct MsgCB * pstStartDtmf)
{
    MN_CALL_ID_T                        CallId;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq       = VOS_NULL_PTR;
    TAF_CALL_DTMF_PARAM_STRU           *pstDtmfParam    = VOS_NULL_PTR;
    TAF_CALL_DTMF_INFO_STRU             stDtmfInfo;
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo  = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stDtmfInfo, 0, sizeof(stDtmfInfo));

    pstAppReq               = ((MN_CALL_APP_REQ_MSG_STRU *)pstStartDtmf);
    pstDtmfParam            = &pstAppReq->unParm.stDtmf;
    stDtmfInfo.CallId       = pstDtmfParam->CallId;
    stDtmfInfo.cKey         = pstDtmfParam->cKey;
    stDtmfInfo.usOnLength   = pstDtmfParam->usOnLength;
    stDtmfInfo.usClientId   = pstAppReq->clientId;
    stDtmfInfo.opId         = pstAppReq->opId;

    stDtmfInfo.usOffLength  = pstDtmfParam->usOffLength;

    /* DTMF信息合法性判断 */
    if ( (VOS_OK != TAF_SDC_CheckDtmfKey(&stDtmfInfo.cKey))
      || (stDtmfInfo.usOnLength < TAF_CALL_DTMF_MIN_ONLENGTH) )
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             TAF_CS_CAUSE_INVALID_PARAMETER);
        return;
    }

    /* 先判断当前是否允许发起DTMF，再获取所有可以发送DTMF的呼叫ID */
    ulResult    = TAF_CALL_CheckUserDtmfCallId(stDtmfInfo.CallId);
    if (TAF_CS_CAUSE_SUCCESS != ulResult)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             ulResult);
        return;
    }

    /* 判断DTMF状态是否正常 */
    if (TAF_CALL_GetDtmfState() >= TAF_CALL_DTMF_STATE_BUTT)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             TAF_CS_CAUSE_STATE_ERROR);
        return;
    }

    /* DTMF处于非空闲状态，则缓存此DTMF */
    if (TAF_CALL_GetDtmfState() != TAF_CALL_DTMF_IDLE)
    {
        ulResult = TAF_CALL_SaveDtmfInfo(&stDtmfInfo);

        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             ulResult);
        return;
    }

    /* DTMF当前处于空闲态，则发送到CC */
    pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();
    *pstDtmfCurInfo = stDtmfInfo;

    /* 获取发送DTMF的CALL ID */
    CallId   = 0;
    ulResult = TAF_CALL_GetAllowedDtmfCallId(&CallId);
    if (TAF_CS_CAUSE_SUCCESS != ulResult)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             ulResult);
        return;
    }

    if (VOS_OK != MN_CALL_SendCcStartDtmfReq(CallId, pstDtmfCurInfo->cKey))
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* 发送成功，更新DTMF状态 */
    TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_START_CNF);

    TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                         stDtmfInfo.opId,
                         MN_CALL_EVT_START_DTMF_CNF,
                         TAF_CS_CAUSE_SUCCESS);

    return;
}


VOS_VOID  TAF_CALL_RcvStopDtmfReq(struct MsgCB * pstStopDtmf)
{
    MN_CALL_ID_T                        CallId;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq       = VOS_NULL_PTR;
    TAF_CALL_DTMF_PARAM_STRU           *pstDtmfParam    = VOS_NULL_PTR;
    TAF_CALL_DTMF_INFO_STRU             stDtmfInfo;
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo  = VOS_NULL_PTR;
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enDtmfState;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stDtmfInfo, 0, sizeof(stDtmfInfo));

    pstAppReq               = ((MN_CALL_APP_REQ_MSG_STRU *)pstStopDtmf);
    pstDtmfParam            = &pstAppReq->unParm.stDtmf;
    stDtmfInfo.CallId       = pstDtmfParam->CallId;
    stDtmfInfo.cKey         = pstDtmfParam->cKey;
    stDtmfInfo.usOnLength   = pstDtmfParam->usOnLength;
    stDtmfInfo.usClientId   = pstAppReq->clientId;
    stDtmfInfo.opId         = pstAppReq->opId;
    enDtmfState             = TAF_CALL_GetDtmfState();

    stDtmfInfo.usOffLength  = pstDtmfParam->usOffLength;

    /* STOP_DTMF请求时，OnLength值不为0 */
    if (0 != stDtmfInfo.usOnLength)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             TAF_CS_CAUSE_INVALID_PARAMETER);
        return;
    }

    /* 判断DTMF状态是否正常 */
    if ( (TAF_CALL_DTMF_STATE_BUTT <= enDtmfState)
      || (TAF_CALL_DTMF_IDLE == enDtmfState) )
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             TAF_CS_CAUSE_STATE_ERROR);
        return;
    }

    /* 先判断当前是否允许发起DTMF，以及用户输入的呼叫ID是否可以发送DTMF */
    ulResult    = TAF_CALL_CheckUserDtmfCallId(stDtmfInfo.CallId);
    if (TAF_CS_CAUSE_SUCCESS != ulResult)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             ulResult);
        return;
    }

    /* 如果当前没有缓存且处于等待定时器超时状态，则停定时器，发送STOP_DTMF，否则缓存 */
    if ( (0 == TAF_CALL_GetDtmfBufCnt())
      && (TAF_CALL_DTMF_WAIT_ON_LENGTH_TIME_OUT == enDtmfState))
    {
        MN_CALL_StopTimer(TAF_CALL_TID_DTMF_ON_LENGTH);


        pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();
        *pstDtmfCurInfo = stDtmfInfo;

        /* 获取发送DTMF的CALL ID */
        CallId = 0;
        ulResult = TAF_CALL_GetAllowedDtmfCallId(&CallId);
        if (TAF_CS_CAUSE_SUCCESS != ulResult)
        {
            TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                                 stDtmfInfo.opId,
                                 MN_CALL_EVT_STOP_DTMF_CNF,
                                 ulResult);
            return;
        }

        if (VOS_OK != MN_CALL_SendCcStopDtmfReq(CallId))
        {
            TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                                 stDtmfInfo.opId,
                                 MN_CALL_EVT_STOP_DTMF_CNF,
                                 TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        /* 发送成功，更新DTMF状态 */
        TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_STOP_CNF);

        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             TAF_CS_CAUSE_SUCCESS);
        return;
    }

    /* 当前不能发送STOP_DTMF请求，则缓存 */
    ulResult = TAF_CALL_SaveDtmfInfo(&stDtmfInfo);

    TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                         stDtmfInfo.opId,
                         MN_CALL_EVT_STOP_DTMF_CNF,
                         ulResult);
    return;
}


VOS_VOID  TAF_CALL_RcvCcwaiSetReq(MN_CALL_APP_REQ_MSG_STRU *pstAppReq)
{
    TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode;
    TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU   stCcwaCtrlMode;
    VOS_UINT32                          ulRst;

    enCcwaiMode = pstAppReq->unParm.stCcwaiSet.enMode;


    if (TAF_CALL_CCWAI_SRV_CLASS_SET_NW == pstAppReq->unParm.stCcwaiSet.enSrvClass)
    {
        /* 将CCWAI设置写入NV */
        PS_MEM_SET(&stCcwaCtrlMode, 0, sizeof(stCcwaCtrlMode));
        stCcwaCtrlMode.enCcwaCtrlMode = TAF_CALL_CCWA_CTRL_BY_NW;
        stCcwaCtrlMode.enCcwaiMode = enCcwaiMode;

        ulRst = NV_Write(en_NV_Item_Ccwa_Ctrl_Mode,
                         (VOS_VOID *)&stCcwaCtrlMode,
                         sizeof(TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU));

        /* 如果写NV失败，则CCWAI设置失败 */
        if (NV_OK != ulRst)
        {
            MN_ERR_LOG("TAF_CALL_RcvCcwaiSetReq:Write NVIM Error");

            TAF_CALL_SendCcwaiCnf(pstAppReq->clientId,
                                  pstAppReq->opId,
                                  TAF_CALL_EVT_CCWAI_SET_CNF,
                                  VOS_ERR);

            return;
        }

        TAF_CALL_SetCcwaiMode(enCcwaiMode);
        TAF_CALL_SetCcwaCtrlMode(TAF_CALL_CCWA_CTRL_BY_NW);

        TAF_WARNING_LOG2(WUEPS_PID_TAF, "TAF_CALL_RcvCcwaiSetReq ", TAF_CALL_CCWA_CTRL_BY_NW, enCcwaiMode);

        TAF_CALL_SendCcwaiCnf(pstAppReq->clientId,
                              pstAppReq->opId,
                              TAF_CALL_EVT_CCWAI_SET_CNF,
                              VOS_OK);

        return;
    }

    /* 将CCWAI设置写入NV */
    PS_MEM_SET(&stCcwaCtrlMode, 0, sizeof(stCcwaCtrlMode));
    stCcwaCtrlMode.enCcwaCtrlMode = TAF_CALL_CCWA_CTRL_BY_UE;
    stCcwaCtrlMode.enCcwaiMode = enCcwaiMode;

    ulRst = NV_Write(en_NV_Item_Ccwa_Ctrl_Mode,
                     (VOS_VOID*)&stCcwaCtrlMode,
                     sizeof(TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU));

    /* 如果写NV失败，则CCWAI设置失败 */
    if (NV_OK != ulRst)
    {
        MN_ERR_LOG("TAF_CALL_RcvCcwaiSetReq:Write NVIM Error");

        TAF_CALL_SendCcwaiCnf(pstAppReq->clientId,
                              pstAppReq->opId,
                              TAF_CALL_EVT_CCWAI_SET_CNF,
                              VOS_ERR);

        return;
    }

    /* 将CCWAI设置保存到全局变量 */
    TAF_CALL_SetCcwaiMode(enCcwaiMode);
    TAF_CALL_SetCcwaCtrlMode(TAF_CALL_CCWA_CTRL_BY_UE);

    TAF_WARNING_LOG2(WUEPS_PID_TAF, "TAF_CALL_RcvCcwaiSetReq ", TAF_CALL_CCWA_CTRL_BY_UE, enCcwaiMode);

    TAF_CALL_SendCcwaiCnf(pstAppReq->clientId,
                          pstAppReq->opId,
                          TAF_CALL_EVT_CCWAI_SET_CNF,
                          VOS_OK);
    return;
}

#if (FEATURE_ON == FEATURE_ECALL)

VOS_VOID TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(
    VOS_UINT8                           ucCallId
)
{
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;

    pstBufferdMsg  = MN_CALL_GetBufferedMsg();

    if ((VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
     && (ucCallId == pstBufferdMsg->stBufferedSetupMsg.ucCallId))
    {
        MN_CALL_ClearBufferedMsg();

        /* 停止eCall重拨定时器 */
        MN_CALL_StopTimer(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL);
        MN_CALL_StopTimer(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD);
    }
}


VOS_VOID TAF_CALL_RcvQryEcallInfoReq(MN_CALL_QRY_ECALL_INFO_REQ_STRU *pstQryEcallInfoReq)
{
    MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU stQryEcallCnf;
    MN_CALL_MGMT_STRU                  *pstCallEntityAddr = VOS_NULL_PTR;
    VOS_UINT8                           i;

    PS_MEM_SET(&stQryEcallCnf, 0, sizeof(MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU));

    /* 在呼叫实体中获取MO eCall呼叫的相关信息 */
    pstCallEntityAddr = TAF_CALL_GetCallEntityAddr();

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if (VOS_FALSE == pstCallEntityAddr->bUsed)
        {
            pstCallEntityAddr++;

            continue;
        }

        /* 获取eCall呼叫信息 */
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstCallEntityAddr->stCallInfo.callId))
        {
            stQryEcallCnf.stEcallInfo.astEcallInfos[stQryEcallCnf.stEcallInfo.ucNumOfEcall].ucCallId    =
                pstCallEntityAddr->stCallInfo.callId;

            stQryEcallCnf.stEcallInfo.astEcallInfos[stQryEcallCnf.stEcallInfo.ucNumOfEcall].enCallState =
                pstCallEntityAddr->stCallInfo.enCallState;

            stQryEcallCnf.stEcallInfo.astEcallInfos[stQryEcallCnf.stEcallInfo.ucNumOfEcall].enEcallType =
                pstCallEntityAddr->stCallInfo.enCallType;

            PS_MEM_CPY(&(stQryEcallCnf.stEcallInfo.astEcallInfos[stQryEcallCnf.stEcallInfo.ucNumOfEcall].stDialNumber),
                       &(pstCallEntityAddr->stCallInfo.stCalledNumber),
                       sizeof(MN_CALL_CALLED_NUM_STRU));

            stQryEcallCnf.stEcallInfo.ucNumOfEcall++;
        }

        pstCallEntityAddr++;
    }

    stQryEcallCnf.ucOpId     = pstQryEcallInfoReq->ucOpId;
    stQryEcallCnf.usClientId = pstQryEcallInfoReq->usClientId;

    /* 发送消息给请求信息的查询方 */
    TAF_CALL_SendQueryEcallInfoCnf(pstQryEcallInfoReq->usClientId,
                                   pstQryEcallInfoReq->ucOpId,
                                   &stQryEcallCnf);
}


VOS_VOID TAF_CALL_EcallSupsCmdRelReqProc(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    const MN_CALL_SUPS_PARAM_STRU      *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* 挂断所有正在通话的eCall呼叫 */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            if (VOS_FALSE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* ECLSTOP命令仅能挂断eCall呼叫 */
                continue;
            }

            /* 清除"等待mt eCall呼叫标志位" */
            TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

            MN_CALL_GetCallState(aCallIds[i], &enCallState, &enMptyState);
            MN_CALL_UpdateClientId(aCallIds[i], usClientId);

            /* 如果呼叫处于dialing状态并且呼叫重发间隔定时器在运行，cc处于U0状态，无需
               给cc发送disconnect消息，处理缓存的rej ind消息 */
            if ((MN_CALL_TIMER_STATUS_RUNING == TAF_CALL_GetRedialIntervalTimerStatus(aCallIds[i]))
             && (MN_CALL_S_DIALING           == enCallState))
            {
                TAF_CALL_RelRedialingCall(usClientId, ucOpId, pstCallSupsParam);
                return;
            }

            if ((MN_CALL_S_INCOMING            == enCallState)
             || (MN_CALL_S_WAITING             == enCallState)
             || (MN_CALL_S_CCBS_WAITING_RECALL == enCallState))
            {
                TAF_CALL_RelIncomingOrWaitingCall(aCallIds[i], enCallState);
            }
            else
            {
                (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* 记录主动挂断的原因值 */
                MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* 记录呼叫挂断的方向 */
                MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

                /* 如果T9定时器在运行，停止T9定时器 */
                if (MN_CALL_TIMER_STATUS_RUNING == MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
                {
                    /* 停止T9定时器 */
                    MN_CALL_StopTimer(TAF_CALL_TID_T9);
                }

                /* 清除重拨缓存与重拨定时器 */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }

            MN_CALL_DeRegSsKeyEvent(aCallIds[i],MN_CALL_SS_PROG_EVT_SETUP_COMPL);
            MN_CALL_DeRegSsKeyEvent(aCallIds[i],MN_CALL_SS_PROG_EVT_REL);
        }

        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(usClientId, ucOpId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    TAF_CALL_SendSupsCmdCnf(usClientId, ucOpId, pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(usClientId,
                                              ucOpId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_SUCCESS);
}
#endif

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



