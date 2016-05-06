/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallProcVc.c
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2014年04月01日
  最近修改   :
  功能描述   : 处理VC发送给CALL模块的消息
  函数列表   :

  修改历史   :
  1.日    期   : 2014年04月01日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "MnCallProcVc.h"
#include "MnCallApi.h"
#include "MnCallMgmt.h"
#include "MnCallReqProc.h"
#include "MnCallCtx.h"
#include "MnComm.h"
#include "MnCallTimer.h"
#include "MnCallSendCc.h"
#include "TafCsCallCommDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_MN_CALL_PROC_VC_C

/*****************************************************************************
   2 变量定义
*****************************************************************************/
/* call所有呼叫信息 */
LOCAL MN_CALL_INFO_STRU                   f_astCallInfos[MN_CALL_MAX_NUM];

/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : TAF_CALL_RcvVcCallEndCall
 功能描述  : 处理收到VC通知CALL模块呼叫结束指示

 输入参数  : pstEndCall   - 消息地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月04日
    作    者   : y00245242
    修改内容   : 新增函数
  2.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID TAF_CALL_RcvVcCallEndCall(VC_CALL_MSG_STRU *pstEndCall)
{
    TAF_UINT8                           ucNumOfCalls;
    MN_CALL_END_PARAM_STRU              stEndParm;
    VOS_UINT32                          ulRet;

    /* ECALL时收到MED的AlAck上报，认为是正常挂断，报原因值#16 */
    stEndParm.enEndCause    = TAF_CALL_ConvertVcCauseToTafCsCause(pstEndCall->enCause);

    MN_CALL_GetCallInfoList(&ucNumOfCalls,f_astCallInfos);
    if (ucNumOfCalls != 0)
    {
        ulRet = MN_CALL_InternalCallEndReqProc(MN_CLIENT_ALL,
                                               0,
                                               f_astCallInfos[0].callId,
                                               &stEndParm);
        if (TAF_CS_CAUSE_SUCCESS != ulRet)
        {
            MN_WARN_LOG("TAF_CALL_RcvVcCallEndCall: Fail to MN_CALL_InternalCallEndReqProc.");
        }
    }
}

#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 函 数 名  : TAF_CALL_ProcEcallMsdTransSuccess
 功能描述  : 处理MSD传输成功消息

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月30日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
  2.日    期   : 2015年4月2日
    作    者   : w00316404
    修改内容   : clean coverity
*****************************************************************************/
VOS_VOID TAF_CALL_ProcEcallMsdTransSuccess(VOID)
{
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_TIMER_STATUS_ENUM_U8        enTimerStatus;

    enCallState                         = MN_CALL_S_BUTT;


    pstBufferdMsg = MN_CALL_GetBufferedMsg();
    if (VOS_FALSE == pstBufferdMsg->bitOpBufferedSetupMsg)
    {
        /* 无缓存，直接更新MSD状态到初始态 */
        TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
        return;
    }

    enTimerStatus = MN_CALL_GetTimerStatus(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL);

    if ((MN_CALL_TIMER_STATUS_RUNING != MN_CALL_GetTimerStatus(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD))
     && (MN_CALL_TIMER_STATUS_RUNING != enTimerStatus))
    {
        /* 如果定时器都不在运行，应该是在eCall通话中，MSD传输成功，更新状态 */
        TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_MSD_TRANSMITTING_SUCCESS);
        return;
    }

    ucCallId = pstBufferdMsg->stBufferedSetupMsg.ucCallId;

    /* 1. 本场景是处理信令连接先释放完成，而后才收到MSD数据传输成功的状态指示
     *    此时需要停止重拨定时器，释放资源，上报呼叫释放完成
     */
    MN_CALL_GetCallState(ucCallId, &enCallState, &enMptyState);

    /* 在dialing状态且间隔定时器在运行时，请求消息还未发送给CC，因此本地释放呼叫就可以了 */
    if ((MN_CALL_TIMER_STATUS_RUNING == TAF_CALL_GetRedialIntervalTimerStatus(ucCallId))
     && (MN_CALL_S_DIALING           == enCallState))
    {
        /* 上报呼叫释放事件 */
        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_RELEASED);

        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_ALL_RELEASED);

        TAF_CALL_ProcCallStatusFail(ucCallId, enCallState);

        MN_CALL_FreeCallId(ucCallId);
    }
    else
    {
        /*挂断指定的呼叫*/
        (VOS_VOID)MN_CALL_SendCcDiscReq(ucCallId, MN_CALL_NORMAL_CALL_CLEARING);

        /* 记录主动挂断的原因值 */
        MN_CALL_UpdateCcCause(ucCallId, MN_CALL_NORMAL_CALL_CLEARING);

        /* 记录呼叫挂断的方向 */
        MN_CALL_UpdateDiscCallDir(ucCallId, VOS_TRUE);
    }

    /* 清除MO呼叫重拨缓存 */
    MN_CALL_ClearBufferedMsg();

    /* 停止所有eCall重拨时长定时器 */
    TAF_CALL_StopAllRedialTimers(ucCallId);

    /* 呼叫释放，更新MSD状态到初始态 */
    TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
}

/*****************************************************************************
 函 数 名  : TAF_CALL_RcvVcEcallTransStatusNtf
 功能描述  : 处理收到VC通知CALL模块当前MSD传输的状态消息

 输入参数  : pstEcallTransStatusNtf   - 消息地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年04月01日
    作    者   : y00245242
    修改内容   : 为eCall feature增加
*****************************************************************************/
VOS_VOID TAF_CALL_RcvVcEcallTransStatusNtf(VC_CALL_ECALL_TRANS_STATUS_NTF_STRU *pstEcallTransStatusNtf)
{


    switch (pstEcallTransStatusNtf->enEcallTransStatus)
    {
        case VC_CALL_ECALL_MSD_TRANSMITTING_SUCCESS:
            TAF_CALL_ProcEcallMsdTransSuccess();
            break;

        case VC_CALL_ECALL_MSD_TRANSMITTING_FAIL:
        case VC_CALL_ECALL_MSD_TRANSMITTING_START:
        case VC_CALL_ECALL_PSAP_MSD_REQUIRETRANSMITTING:
            /* 更新eCall MSD数据传输状态 */
            TAF_CALL_SetEcallMsdTransStatus(pstEcallTransStatusNtf->enEcallTransStatus);
            break;

        default:
            /* 非法值，更新到butt */
            TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
            break;
    }
}
#endif

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



