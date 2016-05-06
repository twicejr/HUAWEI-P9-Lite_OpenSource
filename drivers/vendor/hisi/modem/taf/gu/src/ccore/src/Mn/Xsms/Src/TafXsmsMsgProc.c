/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsMsgProc.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年10月31日
  功能描述   : 1X SMS(Short Message Service)任务消息函数处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXsmsMsgProc.h"
#include "TafXsmsMoFsmMain.h"
#include "TafXsmsMtFsmMain.h"
#include "siapppih.h"
#include "TafAppXsmsInterface.h"
#include "TafXsmsUimProc.h"
#include "TafXsmsSndAt.h"
#include "TafXsmsEncode.h"
#include "NVIM_Interface.h"
#include "TafXsmsTimer.h"
#include "TafXsmsSndCas.h"
#include "csn1clib.h"
#include "TafXsmsSndXcc.h"
#include "TafXsmsStkInterface.h"
#include "taf_xcall_xsms_pif.h"
#include "TafXpdsXsmsInterface.h"
#include "TafXsmsSndXcall.h"


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "UserDefinedDataTypes_cs0005.h"
#include "ed_c_cs0005.h"
#endif


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_MSG_PROC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_XSMS_MsgHook
 功能描述  : XSMS内部可维可测钩包处理函数
 输入参数  : enMsgName:内部可维可测消息名
             pucMsg:可维可测消息
             ulMsgLen:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月2日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32 enMsgName, VOS_UINT8 *pucMsg, VOS_UINT32 ulMsgLen)
{
    TAF_XSMS_MSG_HOOK_STRU             *pstMsg;

    pstMsg = (TAF_XSMS_MSG_HOOK_STRU *)VOS_AllocMsg(UEPS_PID_XSMS, sizeof(TAF_XSMS_MSG_HOOK_STRU) - VOS_MSG_HEAD_LENGTH + ulMsgLen - 4);

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_MsgHook:WARNING:alloc msg failed.\n");

        return;
    }

    pstMsg->ulReceiverPid   = UEPS_PID_XSMS;
    pstMsg->enMsgId         = enMsgName;

    PS_MEM_CPY(pstMsg->aucMsg, pucMsg, ulMsgLen);


    DIAG_TraceReport(pstMsg);

    VOS_FreeMsg(UEPS_PID_XSMS, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_AtDeleteMsgProc
 功能描述  : XSMS处理AT发来的删除短信消息处理函数
 输入参数  : pstMsg:AT发过来的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月2日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_AtDeleteMsgProc(TAF_XSMS_DELETE_MSG_REQ_STRU *pstMsg)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    TAF_XSMS_CTRL_INFO_STRU            *pstCtrlInfoAddr;
    VOS_UINT8                           ucIndex;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();
    pstCtrlInfoAddr     = TAF_XSMS_GetReqCtrlInfoAddr();

    /* 当前有初始化未完成 */
    if (TAF_XSMS_INIT_STATUS_FINISH != pstInitCtrlInfoAddr->enSmsInitState)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtDeleteMsgProc:XSMS Init not finish");

        TAF_XSMS_MsgDeleteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR);

        return;
    }

    /* 当前有AT命令在处理 */
    if (TAF_XSMS_UIM_LOCK_LOCKED == pstCtrlInfoAddr->enUimLock)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtDeleteMsgProc:XSMS At cmd Locked");

        TAF_XSMS_MsgDeleteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR);

        return;
    }

    /* AT输入的索引值从0开始，UIM卡中的索引值从1开发，需要加1后再处理 */
    ucIndex = pstMsg->ucIndex + 1;

    if (ucIndex > pstInitCtrlInfoAddr->ucMaxRecord)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtDeleteMsgProc:Index invalid");

        TAF_XSMS_MsgDeleteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR);

        return;
    }

    /* 填充控制信息 */
    pstCtrlInfoAddr->usClient     = pstMsg->usClientId;
    pstCtrlInfoAddr->ucOpID       = pstMsg->ucOpId;
    pstCtrlInfoAddr->enAppMsgType = pstMsg->ulMsgName;
    pstCtrlInfoAddr->enUimLock    = TAF_XSMS_UIM_LOCK_LOCKED;

    /* 删除空记录，返回操作成功 */
    if (TAF_XSMS_EFSMS_STATUS_FREE == TAF_XSMS_GetBitFromBuf(pstInitCtrlInfoAddr->aucFreeIndex, ucIndex))
    {
        TAF_XSMS_MsgDeleteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_OK);
    }
    else
    {
        TAF_XSMS_AtSmsDeleteReq(ucIndex);
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_AtWriteMsgProc
 功能描述  : XSMS处理AT发来的写短信消息处理函数
 输入参数  : pstMsg:AT发过来的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月2日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_AtWriteMsgProc(TAF_XSMS_WRITE_MSG_REQ_STRU *pstMsg)
{
    TAF_XSMS_CTRL_INFO_STRU            *pstCtrlInfoAddr;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    VOS_UINT8                           aucData[TAF_XSMS_RECORD_LEN_MAX];
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucIndex;

    pstCtrlInfoAddr     = TAF_XSMS_GetReqCtrlInfoAddr();
    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* 当前初始化未完成 */
    if (TAF_XSMS_INIT_STATUS_FINISH != pstInitCtrlInfoAddr->enSmsInitState)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtWriteMsgProc:XSMS Init not finish");

        TAF_XSMS_MsgWriteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR, 0);

        return;
    }

    /* 当前没有AT命令在处理 */
    if (TAF_XSMS_UIM_LOCK_LOCKED == pstCtrlInfoAddr->enUimLock)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtWriteMsgProc:XSMS At cmd Locked");

        TAF_XSMS_MsgWriteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR, 0);

        return;
    }

    /* 如果当前不存在空闲的记录，返回错误并通过AT命令上报存储器满 */
    if (VOS_OK != TAF_XSMS_FindFreeIndex(&ucIndex))
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtWriteMsgProc:Not find free index");

        TAF_XSMS_MsgWriteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR, 0);

        TAF_XSMS_MsgUimFullInd();

        return;
    }

    /* 调用MO的编码函数生成TransportLayer数据，预留前两个字节填充状态信息和长度，Reply Seq的值默认都填0 */
    if (VOS_OK != TAF_XSMS_EncodeBearDataStruToSimRaw(&pstMsg->st1XSms,
                                                        aucData + 2,
                                                        VOS_NULL,
                                                        &ucLen,
                                                        pstMsg->enSmsStatus,
                                                        VOS_TRUE))
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_AtWriteMsgProc:TAF_XSMS_EncodeBearDataStruToSimRaw return fail");

        TAF_XSMS_MsgWriteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR, 0);

        return;
    }

    switch (pstMsg->enSmsStatus)
    {
        case TAF_XSMS_STATUS_REC_UNREAD:
            aucData[0] = TAF_XSMS_UIM_MSG_STATUS_UNREAD;
            break;

        case TAF_XSMS_STATUS_REC_READ:
            aucData[0] = TAF_XSMS_UIM_MSG_STATUS_READ;
            break;

        case TAF_XSMS_STATUS_STO_UNSEND:
            aucData[0] = TAF_XSMS_UIM_MSG_STATUS_UNSEND;
            break;

        case TAF_XSMS_STATUS_STO_SEND:
            aucData[0] = TAF_XSMS_UIM_MSG_STATUS_SEND;
            break;

        default:
            TAF_XSMS_WARNING_LOG("TAF_XSMS_AtWriteMsgProc:Invalid SMS status");

            TAF_XSMS_MsgWriteCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR, 0);
            return;
    }

    /* 填充控制信息 */
    pstCtrlInfoAddr->usClient     = pstMsg->usClientId;
    pstCtrlInfoAddr->ucOpID       = pstMsg->ucOpId;
    pstCtrlInfoAddr->enAppMsgType = pstMsg->ulMsgName;
    pstCtrlInfoAddr->enUimLock    = TAF_XSMS_UIM_LOCK_LOCKED;

    aucData[1] = ucLen;

    TAF_XSMS_AtSmsWriteReq(ucLen + 2, aucData, ucIndex);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_AtMsgProc
 功能描述  : XSMS处理AT发来的消息处理函数
 输入参数  : pstMsg:AT发过来的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月2日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_AtMsgProc(MsgBlock* pstMsg)
{
    VOS_UINT32                          ulRet;
    TAF_XSMS_SEND_MSG_REQ_STRU         *pstSendReqMsg;

    pstSendReqMsg   = (TAF_XSMS_SEND_MSG_REQ_STRU *)pstMsg;

    /* 因为A核PID超过16位，在状态机表中使用XSMS自己的PID */
    pstSendReqMsg->ulSenderPid = UEPS_PID_XSMS;

    switch (pstSendReqMsg->ulMsgName)
    {
        /* AT命令发来的短信发送请求 */
        case TAF_XSMS_APP_MSG_TYPE_SEND_REQ:

            if (TAF_XSMS_MO_IDLE_STATE != TAF_XSMS_MoGetCurrFsmId())
            {
                /* 判断是否可以将XCALL的请求放在发送池里面 */
                if (VOS_TRUE == TAF_XSMS_IsRecCanInsertToPool(TAF_XSMS_SMS_ORIGPID_AT))
                {
                    if (VOS_OK != TAF_XSMS_InsertRecToMoSendPool(TAF_XSMS_SMS_ORIGPID_AT,
                                                                 VOS_TRUE,
                                                                 0,
                                                                 &pstSendReqMsg->st1XSms))
                    {
                        TAF_XSMS_ERROR_LOG("TAF_XSMS_AtMsgProc:TAF_XSMS_IsRecCanInsertToPool fail");
                        TAF_XSMS_MsgSubmitCnf(pstSendReqMsg->usClientId, pstSendReqMsg->ucOpId, VOS_ERR);
                    }
                    else
                    {
                        TAF_XSMS_MsgSubmitCnf(pstSendReqMsg->usClientId, pstSendReqMsg->ucOpId, VOS_OK);
                    }

                }
                else
                {
                    TAF_XSMS_ERROR_LOG("TAF_XSMS_AtMsgProc:can not insert to send pool");
                    TAF_XSMS_MsgSubmitCnf(pstSendReqMsg->usClientId, pstSendReqMsg->ucOpId, VOS_ERR);
                }

                return;
            }

            ulRet = TAF_XSMS_MoFsmMainProc(pstMsg);
            TAF_XSMS_MsgSubmitCnf(pstSendReqMsg->usClientId, pstSendReqMsg->ucOpId, ulRet);

            break;

        /* AT命令发来的短信写入请求 */
        case TAF_XSMS_APP_MSG_TYPE_WRITE_REQ:

            TAF_XSMS_AtWriteMsgProc((TAF_XSMS_WRITE_MSG_REQ_STRU *)pstMsg);

            break;

        /* AT命令发来的短信删除请求 */
        case TAF_XSMS_APP_MSG_TYPE_DELETE_REQ:

            TAF_XSMS_AtDeleteMsgProc((TAF_XSMS_DELETE_MSG_REQ_STRU *)pstMsg);

            break;

        /* AT命令发来的短信满请求 */
        case TAF_XSMS_APP_MSG_TYPE_UIM_MEM_SET_REQ:

            TAF_XSMS_AtApMemFullMsgProc((TAF_XSMS_APP_MSG_SET_AP_MEM_FULL_REQ_STRU *)pstMsg);

            break;


        default:

            TAF_XSMS_WARNING_LOG("TAF_XSMS_AtMsgProc:Invalid request");

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_StkProc
 功能描述  : STK的消息处理
 输入参数  : pstMsg  短信内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月30日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_StkProc(MsgBlock *pstMsg)
{
    STK_XSMS_SEND_SMS_REQ_STRU         *pstSendReq;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usIsTlAckNeed  = VOS_TRUE;

    pstSendReq = (STK_XSMS_SEND_SMS_REQ_STRU*)pstMsg;

    if (VOS_TRUE == pstSendReq->ulIsUserAck)
    {
        usIsTlAckNeed  = VOS_FALSE;
    }

    switch (pstSendReq->enMsgId)
    {
        case ID_STK_XSMS_SEND_SMS_REQ:

            if (TAF_XSMS_MO_IDLE_STATE != TAF_XSMS_MoGetCurrFsmId())
            {
                /* 判断是否可以将XCALL的请求放在发送池里面 */
                if (VOS_TRUE == TAF_XSMS_IsRecCanInsertToPool(TAF_XSMS_SMS_ORIGPID_STK))
                {
                    if (VOS_OK != TAF_XSMS_InsertRecToMoSendPool(TAF_XSMS_SMS_ORIGPID_STK,
                                                             usIsTlAckNeed,
                                                             0,
                                                             &pstSendReq->st1XSms))
                    {
                        TAF_XSMS_ERROR_LOG("TAF_XSMS_StkProc : TAF_XSMS_InsertRecToMoSendPool ERR");
                        TAF_XSMS_StkMsgSubmitCnf(VOS_ERR);
                    }
                }
                else
                {
                    TAF_XSMS_ERROR_LOG("TAF_XSMS_StkProc : can not insert to pool");
                    TAF_XSMS_StkMsgSubmitCnf(VOS_ERR);
                }

                return;
            }

            ulRet = TAF_XSMS_MoFsmMainProc(pstMsg);

            if (VOS_FALSE == pstSendReq->ulIsUserAck)
            {
                TAF_XSMS_StkMsgSubmitCnf(ulRet);
            }

            break;

        default:
            break;
    }

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_TimeOutMsgProc
 功能描述  : XSMS PID定时器超时处理函数
 输入参数  : pstRelTimerMsg:定时器超时消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月2日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_TimeOutMsgProc(REL_TIMER_MSG *pstRelTimerMsg)
{
    TAF_XSMS_WARNING_LOG1("TAF_XSMS_TimeOutMsgProc: timer name is",pstRelTimerMsg->ulName);

    if (TI_TAF_XSMS_TIMER_INIT_PROTECT == pstRelTimerMsg->ulName)
    {
        TAF_XSMS_InitTimeOutMsgProc();
    }
    else if (TI_TAF_XSMS_TIMER_MO_POOL_REFRESH == pstRelTimerMsg->ulName)
    {
        TAF_XSMS_RefreshRecsInMoSendPool();
    }
    else
    {
        if (TI_TAF_XSMS_TIMER_MT_END_LINK_PROTECT == pstRelTimerMsg->ulName)
        {
            TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MT,
                                      TAF_XCC_END_REASON_NORMAL_RELEASE);
        }

        /* MO或MT的状态机处理 */
        if (TI_TAF_XSMS_TIMER_INIT_PROTECT > pstRelTimerMsg->ulName)
        {
            TAF_XSMS_MtFsmMainProc((MsgBlock*)pstRelTimerMsg);
        }
        else
        {
            TAF_XSMS_MoFsmMainProc((MsgBlock*)pstRelTimerMsg);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_XccEndCallCnfChooseStateMachine
 功能描述  : 判断END_CALL_CNF消息进什么状态机(MO还是MT)
 输入参数  : pstMsg:收到的XCC消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月5日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_XccEndCallCnfChooseStateMachine(MsgBlock *pstMsg)
{
    XCC_CSMS_END_SMS_CALL_CNF_STRU     *pstEndCallMsg;

    pstEndCallMsg = (XCC_CSMS_END_SMS_CALL_CNF_STRU*)pstMsg;

    if (TAF_XSMS_SEND_XCC_CALL_ID_MO == pstEndCallMsg->ucCallId)
    {
        TAF_XSMS_MoFsmMainProc(pstMsg);
    }
    else if (TAF_XSMS_SEND_XCC_CALL_ID_MT == pstEndCallMsg->ucCallId)
    {
        TAF_XSMS_MtFsmMainProc(pstMsg);
    }
    else
    {
        /* 错误的CALL ID */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_XccEndCallCnfChooseStateMachine: Wrong Call Id");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_XccSoIndChooseStateMachine
 功能描述  : 判断SO_IND消息进什么状态机(MO还是MT)
 输入参数  : pstMsg:收到XCC的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月5日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/

VOS_VOID TAF_XSMS_XccSoIndChooseStateMachine(MsgBlock *pstMsg)
{
    XCC_CSMS_SERVICE_CONNECT_IND_STRU *pstSoIndMsg;

    pstSoIndMsg = (XCC_CSMS_SERVICE_CONNECT_IND_STRU*)pstMsg;

    if (TAF_XSMS_SEND_XCC_CALL_ID_MO == pstSoIndMsg->ucCallId)
    {
        TAF_XSMS_MoFsmMainProc(pstMsg);
    }
    else if (TAF_XSMS_SEND_XCC_CALL_ID_MT == pstSoIndMsg->ucCallId)
    {
        TAF_XSMS_MtFsmMainProc(pstMsg);
    }
    else
    {
        /* 错误的CALLID */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_XccSoIndChooseStateMachine: Wrong Call Id");
    }

    return;

}
/*****************************************************************************
 函 数 名  : TAF_XSMS_XccMsgProc
 功能描述  : XCC消息分发处理函数
 输入参数  : pstMsg:收到的XCC消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月5日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_XccMsgProc(MsgBlock *pstMsg)
{
    VOS_UINT16                          usMsgName;

    PS_MEM_CPY(&usMsgName, pstMsg->aucValue, 2);

    switch (usMsgName)
    {
        case ID_XCC_CSMS_ORIG_SMS_CALL_CNF:

            TAF_XSMS_MoFsmMainProc(pstMsg);

            break;

        case ID_XCC_CSMS_END_SMS_CALL_CNF:

            /* 根据call ID区分谁发起拆链的 */
            TAF_XSMS_XccEndCallCnfChooseStateMachine(pstMsg);

            break;

        case ID_XCC_CSMS_INCOMING_CALL_IND:

            TAF_XSMS_MtFsmMainProc(pstMsg);

            break;

        case ID_XCC_CSMS_CALL_CONN_IND:

            TAF_XSMS_MtFsmMainProc(pstMsg);

            break;

        case ID_XCC_CSMS_ANSWER_CALL_CNF:

            TAF_XSMS_MtFsmMainProc(pstMsg);

            break;

        case ID_XCC_CSMS_SERVICE_CONNECT_IND:

            /* 根据call ID区分谁建立的 */
            TAF_XSMS_XccSoIndChooseStateMachine(pstMsg);

            break;

        case ID_XCC_CSMS_MSG_WATING_IND:

            /* voice mail notification */
            TAF_XSMS_DealXccVoiceMailInd(pstMsg);
            break;


        default:

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_1xCasMsgProc
 功能描述  : 接入层发过来的消息处理函数
 输入参数  : pstMsg:接入层发过来的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月2日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_1xCasMsgProc(MsgBlock* pstMsg)
{
    VOS_UINT16                          usMsgName;

    PS_MEM_CPY(&usMsgName, pstMsg->aucValue, 2);

    /* 判断msg name */
    switch (usMsgName)
    {
        case ID_CAS_CNAS_1X_DSCH_DATA_CNF:

            TAF_XSMS_CasDschCnfProc(pstMsg);

            break;

        case ID_CAS_CNAS_1X_DSCH_DATA_IND:

            TAF_XSMS_CasDschDataIndProc(pstMsg);

            break;

        case ID_CAS_CNAS_1X_CSCH_DATA_CNF:

            TAF_XSMS_SndCasEndSessionNotify(CNAS_CAS_1X_SESSION_TYPE_SMS);

            TAF_XSMS_CasCschCnfProc(pstMsg);

            break;

        case ID_CAS_CNAS_1X_CSCH_DATA_IND:

            TAF_XSMS_CasCschDataIndProc(pstMsg);

            break;

        case ID_CAS_CNAS_1X_SMS_ABORT_IND:

            TAF_XSMS_CasAbortProc(pstMsg);

            break;

        default:
            break;

    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_TransCSCHDataToDbm
 功能描述  : CAS发送的cSCH数据转换成DBM
 输入参数  : pstCschData:收到的CSCH_DATA_IND
 输出参数  : pstDbm:DATA BURST MSG
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TransCSCHDataToDbm
(
    CAS_CNAS_1X_CSCH_DATA_IND_STRU     *pstCschData,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm
)
{

    TAF_XSMS_INFO_LOG1("TAF_XSMS_TransCSCHDataToDbm: Msglen is ", pstCschData->usMsgDataLen);

    if (pstCschData->usMsgDataLen < (4 * TAF_XSMS_BIT_NUMBER_OF_BYTE))
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_TransCSCHDataToDbm: bit length error !");

        return VOS_ERR;
    }

    TAF_XSMS_TransAucDataToDbm(pstCschData->aucMsgData,pstDbm);

    TAF_XSMS_INFO_LOG1("TAF_XSMS_TransCSCHDataToDbm: DBM NUMFIELDS is ", pstDbm->ucNumFields);

    if ((pstCschData->usMsgDataLen > ((pstDbm->ucNumFields + 4) * TAF_XSMS_BIT_NUMBER_OF_BYTE))
        || (pstCschData->usMsgDataLen < ((pstDbm->ucNumFields + 3) * TAF_XSMS_BIT_NUMBER_OF_BYTE)))
    {
        TAF_XSMS_ERROR_LOG1("TAF_XSMS_TransCSCHDataToDbms: num fields bit length not matched !" ,pstDbm->ucNumFields);
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_TransDbmToCSCHData
 功能描述  : DBM数据转换成CAS发送的CSCH_DATA_REQ
 输入参数  : pstDbm:DATA BURST MSG
 输出参数  : pstCschData:要发送的CSCH_DATA_IND
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TransDbmToCSCHData
(
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm,
    CNAS_CAS_1X_CSCH_DATA_REQ_STRU     *pstCschData
)
{
    VOS_UINT16                          usBitNum;

    usBitNum = (VOS_UINT16)TAF_XSMS_TransDbmToAucData(pstDbm, pstCschData->aucMsgData);

    TAF_XSMS_INFO_LOG1("TAF_XSMS_TransDbmToCSCHData:data req bit num is ", usBitNum);

    /* 如果BIT 数小于32， 或者大于DBM的总长度 返回错误 */
    if ((usBitNum < (4 * TAF_XSMS_BIT_NUMBER_OF_BYTE))
        ||(usBitNum > (pstDbm->ucNumFields + 4) * TAF_XSMS_BIT_NUMBER_OF_BYTE)
        ||(usBitNum < ((pstDbm->ucNumFields + 3) * TAF_XSMS_BIT_NUMBER_OF_BYTE)))
    {
        TAF_XSMS_ERROR_LOG1(" Bit Num error! dbm length is", pstDbm->ucNumFields);
        return VOS_ERR;
    }

    pstCschData->usMsgDataLen   = usBitNum;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_TransDSCHDataToDbm
 功能描述  : CAS发送的DSCH数据转换成DBM
 输入参数  : pstDschData:接入层发过来的DATA_IND
 输出参数  : pstDbm:DATA BURST MSG
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TransDSCHDataToDbm
(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschData,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm
)
{

    TAF_XSMS_INFO_LOG1("TAF_XSMS_TransDSCHDataToDbm: Msglen is ", pstDschData->usMsgDataLen);

    if (pstDschData->usMsgDataLen < (4 * TAF_XSMS_BIT_NUMBER_OF_BYTE))
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_TransDSCHDataToDbm: bit length error !");

        return VOS_ERR;
    }

    TAF_XSMS_TransAucDataToDbm(pstDschData->aucMsgData,pstDbm);

    TAF_XSMS_INFO_LOG1("TAF_XSMS_TransDSCHDataToDbm: DBM NUMFIELDS is ", pstDbm->ucNumFields);

    if ((pstDschData->usMsgDataLen > ((pstDbm->ucNumFields + 4) * TAF_XSMS_BIT_NUMBER_OF_BYTE))
        || (pstDschData->usMsgDataLen < ((pstDbm->ucNumFields + 3) * TAF_XSMS_BIT_NUMBER_OF_BYTE)))
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_TransDSCHDataToDbm: num fields bit length not matched !");
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_TransAucDataToDbm
 功能描述  : DATA_Ind的 DATA段 转换成DBM
 输入参数  : paucData :DATA_Ind的 DATA段
 输出参数  : pstDbm::Data Burst MSGS
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月25日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_TransAucDataToDbm
(
    VOS_UINT8                          *paucData ,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm
)
{
    VOS_UINT8                           i                   =  0;
    VOS_UINT16                          usBitpos            =  0;


    /* 解码MSG NUMS */
    pstDbm->ucMsgNum        =   paucData[0];
    usBitpos               +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;

    /* 解码BURST TYPE */
    TAF_XSMS_TL_UnpackByteToBit(paucData, &(pstDbm->ucBurstType), usBitpos, 6);
    usBitpos               +=   6;

    /* 解码NUM MSGS */
    TAF_XSMS_TL_UnpackByteToBit(paucData, &(pstDbm->ucNumMsgs), usBitpos, TAF_XSMS_BIT_NUMBER_OF_BYTE);
    usBitpos               +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;

    /* 解码NUM FIELDS */
    TAF_XSMS_TL_UnpackByteToBit(paucData, &(pstDbm->ucNumFields), usBitpos, TAF_XSMS_BIT_NUMBER_OF_BYTE);
    usBitpos               +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;


    /* 解码DBM DATA */
    for (i = 0; i < pstDbm->ucNumFields; i++)
    {
        TAF_XSMS_TL_UnpackByteToBit(paucData, &(pstDbm->aucData[i]), usBitpos, TAF_XSMS_BIT_NUMBER_OF_BYTE);
        usBitpos          +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_TransDbmToDSCHData
 功能描述  : DBM数据转换成CAS发送的DSCH_DATA_REQ
 输入参数  : pstDbm :Data Burst MSG
 输出参数  : pstDschData:要发送出去的DSCH_DATA_REQ
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TransDbmToDSCHData
(
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm,
    CNAS_CAS_1X_DSCH_DATA_REQ_STRU     *pstDschData
)
{
    VOS_UINT16                          usBitNum;

    usBitNum = (VOS_UINT16)TAF_XSMS_TransDbmToAucData(pstDbm, pstDschData->aucMsgData);

    TAF_XSMS_INFO_LOG1("TAF_XSMS_TransDbmToDSCHData: data req bit num is ", usBitNum);

    /* 如果BIT 数小于32， 或者大于DBM的总长度 返回错误 */
    if ((usBitNum < (4 * TAF_XSMS_BIT_NUMBER_OF_BYTE))
        ||(usBitNum > (pstDbm->ucNumFields + 4) * TAF_XSMS_BIT_NUMBER_OF_BYTE)
        ||(usBitNum < ((pstDbm->ucNumFields + 3) * TAF_XSMS_BIT_NUMBER_OF_BYTE)))
    {
        TAF_XSMS_ERROR_LOG1(" Bit Num error! dbm length is", pstDbm->ucNumFields);
        return VOS_ERR;
    }

    pstDschData->usMsgDataLen   = usBitNum;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_TransDbmToAucData
 功能描述  : DBM数据转换成CAS发送DATA_REQ的 DATA段
 输入参数  : pstDbm :Data Burst MSG
 输出参数  : paucData:要发送出去的DATA_REQ的DATA段
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月24日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TransDbmToAucData
(
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm,
    VOS_UINT8                          *paucData
)
{

    VOS_UINT32                          i           = 0;
    VOS_UINT16                          usBitPos    = 0;

    /* 编码MSG NUM  */
    paucData[0]     =   pstDbm->ucMsgNum;
    usBitPos       +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;

    /* 编码BURST TYPE */
    TAF_XSMS_PackBitToByte(paucData, pstDbm->ucBurstType, 6, usBitPos);
    usBitPos       +=   6;

    /* 编码NUM MSGS */
    TAF_XSMS_PackBitToByte(paucData, pstDbm->ucNumMsgs, TAF_XSMS_BIT_NUMBER_OF_BYTE, usBitPos);
    usBitPos       +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;

    /* 编码NUM FIELDS */
    TAF_XSMS_PackBitToByte(paucData, pstDbm->ucNumFields, TAF_XSMS_BIT_NUMBER_OF_BYTE, usBitPos);
    usBitPos       +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;

    /* 编码DATA */
    for (i = 0; i < pstDbm->ucNumFields; i++)
    {
        TAF_XSMS_PackBitToByte(paucData, pstDbm->aucData[i], TAF_XSMS_BIT_NUMBER_OF_BYTE, usBitPos);
        usBitPos   +=   TAF_XSMS_BIT_NUMBER_OF_BYTE;
    }

    return usBitPos;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_CasDschCnfProc
 功能描述  : 根据MSG_SEQ_NUM 区分是进MO 还是MT的状态机
 输入参数  : pstMsg:CAS发过来的消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_CasDschCnfProc(MsgBlock *pstMsg)
{
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pstCnfMsg;

    pstCnfMsg = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU*)pstMsg;

    if (TAF_XSMS_CAS_DATA_REQ_TYPE_MO == pstCnfMsg->ucMsgSeqNum)
    {
        TAF_XSMS_MoFsmMainProc(pstMsg);
    }
    else if (TAF_XSMS_CAS_DATA_REQ_TYPE_MT == pstCnfMsg->ucMsgSeqNum)
    {
        TAF_XSMS_MtFsmMainProc(pstMsg);
    }
    else
    {
        /* DATA_CNF 里面SEQ NUM错误 */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasDschCnfProc: Wrong seq num");
    }

    return;
}
/*****************************************************************************
 函 数 名  : TAF_XSMS_CasDschDataIndProc
 功能描述  : 将DATA_IND转换成内部的消息类型,
             并根据DBM里面的MSGTYPE判断是进MO还是MT的状态机
 输入参数  : pstMsg:接入层发过来的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_CasDschDataIndProc(MsgBlock *pstMsg)
{

    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstCnfMsg;
    TAF_XSMS_DATA_BURST_MSG_STRU        stDbm;
    TAF_XSMS_CAS_DATA_IND_MSG_STRU      stDataInd;

    pstCnfMsg = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;
    PS_MEM_SET(&stDbm, 0, sizeof(TAF_XSMS_DATA_BURST_MSG_STRU));
    PS_MEM_SET(&stDataInd, 0, sizeof(TAF_XSMS_CAS_DATA_IND_MSG_STRU));

    if (VOS_OK != TAF_XSMS_TransDSCHDataToDbm(pstCnfMsg, &stDbm))
    {
        /* 解码失败 */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasDschDataIndProc:TAF_XSMS_TransDSCHDataToDbm return fail");

        return;
    }

    if (VOS_TRUE != TAF_XSMS_CheckIsSmsDbm(&stDbm))
    {
        /* DBM里面信息不是SMS */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasDschDataIndProc:TAF_XSMS_CheckIsSmsDbm return false");

        return;
    }

    /* 构建内部消息结构体 */
    PS_MEM_CPY(&stDataInd, pstCnfMsg, VOS_MSG_HEAD_LENGTH + sizeof(pstCnfMsg->enMsgId) + sizeof(pstCnfMsg->usOpId));
    stDataInd.ucLen = stDbm.ucNumFields;
    PS_MEM_CPY(stDataInd.aucMsg, stDbm.aucData, stDataInd.ucLen);

    if (TAF_XSMS_TL_P2P_MSG == stDbm.aucData[0]) /* 协议 C.S0015 章节 3.4.1*/
    {
        TAF_XSMS_MtFsmMainProc((MsgBlock*)&stDataInd);
    }
    else if (TAF_XSMS_TL_ACK_MSG == stDbm.aucData[0])
    {
        TAF_XSMS_MoFsmMainProc((MsgBlock*)&stDataInd);
    }
    else
    {
        /* 错误的MSG TYPE */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasDschDataIndProc:Wrong Msg type");
    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_CasCschCnfProc
 功能描述  : 分发CAS的CSCH DATA CNF 进MO还是MT的状态机处理
 输入参数  : pstMsg:收到的接入层在公共信道发送过来的CNF消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_CasCschCnfProc(MsgBlock *pstMsg)
{
    CAS_CNAS_1X_CSCH_DATA_CNF_STRU     *pstCnfMsg;

    pstCnfMsg = (CAS_CNAS_1X_CSCH_DATA_CNF_STRU*)pstMsg;

    if (TAF_XSMS_CAS_DATA_REQ_TYPE_MO == pstCnfMsg->ucMsgSeqNum)
    {
        TAF_XSMS_MoFsmMainProc(pstMsg);
    }
    else if (TAF_XSMS_CAS_DATA_REQ_TYPE_MT == pstCnfMsg->ucMsgSeqNum)
    {
        TAF_XSMS_MtFsmMainProc(pstMsg);
    }
    else
    {
        /* error */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasCschCnfProc: Wrong seq num");;
    }

    return;
}
/*****************************************************************************
 函 数 名  : TAF_XSMS_CasDschDataIndProc
 功能描述  : 将DATA_IND转换成内部的消息类型,
             并根据DBM里面的MSGTYPE判断是进MO还是MT的状态机
 输入参数  : pstMsg:收到的CSCH_DATA_IND
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_CasCschDataIndProc(MsgBlock *pstMsg)
{
    CAS_CNAS_1X_CSCH_DATA_IND_STRU     *pstDataIndMsg;
    TAF_XSMS_DATA_BURST_MSG_STRU        stDbm;
    TAF_XSMS_CAS_DATA_IND_MSG_STRU      stDataInd;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec      = TAF_XSMS_MtGetRecAddr();
    pstDataIndMsg = (CAS_CNAS_1X_CSCH_DATA_IND_STRU*)pstMsg;
    PS_MEM_SET(&stDbm, 0, sizeof(TAF_XSMS_DATA_BURST_MSG_STRU));
    PS_MEM_SET(&stDataInd, 0, sizeof(TAF_XSMS_CAS_DATA_IND_MSG_STRU));


    if (VOS_OK != TAF_XSMS_TransCSCHDataToDbm(pstDataIndMsg,&stDbm))
    {
        /* 解码失败 */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasCschDataIndProc:TAF_XSMS_TransCSCHDataToDbm return fail");

        return;
    }

    if (VOS_TRUE != TAF_XSMS_CheckIsSmsDbm(&stDbm))
    {
        /* DBM里面信息不是SMS */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasCschDataIndProc:TAF_XSMS_CheckIsSmsDbm return false");

        return;
    }

    PS_MEM_CPY(&stDataInd, pstDataIndMsg, VOS_MSG_HEAD_LENGTH + sizeof(pstDataIndMsg->enMsgId) + sizeof(pstDataIndMsg->usOpId));
    stDataInd.ucLen  = stDbm.ucNumFields;
    PS_MEM_CPY(stDataInd.aucMsg, stDbm.aucData, stDataInd.ucLen);

    if (TAF_XSMS_TL_ACK_MSG == stDbm.aucData[0])
    {
        if (VOS_TRUE == pstDataIndMsg->enAckReqFlag)
        {
            TAF_XSMS_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_SMS);
            TAF_XSMS_SndCasCschOrderMsg(0, pstDataIndMsg->enAckReqFlag, pstDataIndMsg->aucAckPara);
        }

        TAF_XSMS_MoFsmMainProc((MsgBlock*)&stDataInd);
    }
    else if (TAF_XSMS_TL_P2P_MSG == stDbm.aucData[0])
    {
        pstMtRec->enIsCasAckFlag    = pstDataIndMsg->enAckReqFlag;
        PS_MEM_CPY(pstMtRec->aucCasAckData, pstDataIndMsg->aucAckPara, 2);

        TAF_XSMS_MtFsmMainProc((MsgBlock*)&stDataInd);
    }
    else
    {
        /* 错误的MSG TYPE */
        TAF_XSMS_WARNING_LOG("TAF_XSMS_CasCschDataIndProc:Wrong Msg type");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_CasAbortProc
 功能描述  : 收到XCC的ABORT消息的分发处理
 输入参数  : pstMsg: XSMS收到的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_CasAbortProc(MsgBlock *pstMsg)
{
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_END_LINK_PROTECT);
    TAF_XSMS_MtFsmMainProc(pstMsg);
    TAF_XSMS_MoFsmMainProc(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_CheckIsSmsDbm()
 功能描述  : 判断收到DATA BURST MSG 是不是协议规定的SMS短信
             (协议C.S0015 2.4.1.1.1.1章节)
 输入参数  : pstDbm:DATA BURST MSG
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月03日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_CheckIsSmsDbm(TAF_XSMS_DATA_BURST_MSG_STRU *pstDbm)
{
    /* 协议 C.S0015 2.4.1.1.1.1章节 */

    if ((TAF_XSMS_DBM_SMS_TYPE == pstDbm->ucBurstType)
     && (1 == pstDbm->ucMsgNum)
     && (1 == pstDbm->ucNumMsgs)
     && (VOS_NULL != pstDbm->ucNumFields))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_PidMsgProc
 功能描述  : TAF XSMS PID的消息处理函数
 输入参数  : pstMsg:其它PID发过来的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月2日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_PidMsgProc(MsgBlock* pstMsg)
{

    /* 消息的分发处理 */
    switch (pstMsg->ulSenderPid)
    {
        case MAPS_PIH_PID:

            TAF_XSMS_PihMsgProc((TAF_XSMS_UIM_MSG_STRU *)pstMsg);

            break;

        case VOS_PID_TIMER:

            TAF_XSMS_TimeOutMsgProc((REL_TIMER_MSG*)pstMsg);

            break;

        case WUEPS_PID_AT:

            TAF_XSMS_AtMsgProc(pstMsg);

            break;

        case WUEPS_PID_USIM:

            TAF_XSMS_UsimmMsgProc((TAF_XSMS_UIM_MSG_STRU *)pstMsg);

            break;

        case UEPS_PID_XCC:

            TAF_XSMS_XccMsgProc(pstMsg);

            break;

        case UEPS_PID_1XCASM:

            TAF_XSMS_1xCasMsgProc(pstMsg);

            break;
        case WUEPS_PID_MMA:

            TAF_XSMS_MoFsmMainProc(pstMsg);

            break;

        case MAPS_STK_PID:
            TAF_XSMS_StkProc(pstMsg);
            break;

        case UEPS_PID_XPDS:
            TAF_XSMS_XpdsProc(pstMsg);
            break;

        case WUEPS_PID_TAF:
            TAF_XSMS_XcallProc(pstMsg);
            break;

        default:
            TAF_XSMS_ERROR_LOG("TAF_XSMS_PidMsgProc : can not find pid");
            break;

    }

    return;
}


/*****************************************************************************
 函 数 名  : TAF_XSMS_PidInit
 功能描述  : XSMS PID初始化处理函数
 输入参数  : ip:初始化阶段
 输出参数  : 无
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年11月2日
    作    者   : h00300778
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_PidInit(enum VOS_INIT_PHASE_DEFINE  ip)
{
    TAF_NVIM_1X_XSMS_CFG_STRU          stXsmsNv;

    switch (ip)
    {
        case VOS_IP_INITIAL:
            TAF_XSMS_ReqCtrlInfoClear();
            TAF_XSMS_InitCtrlInfoClear();

            if (VOS_OK != NV_Read(en_NV_Item_1X_SMS_CFG, &stXsmsNv, sizeof(TAF_NVIM_1X_XSMS_CFG_STRU)))
            {
                /* 中国电信要求在专用信道上发短信 */
                stXsmsNv.enXsmsChannelOption = TAF_XSMS_DATA_REQ_SEND_CHAN_TRAFFIC_CHAN;
                stXsmsNv.ucResendMax         = TAF_XSMS_RESEND_TIMES_MAX;
                stXsmsNv.ucResendInterval    = TAF_XSMS_RESEND_INTERVAL_MAX;
                stXsmsNv.ucReconnectInterval = TAF_XSMS_RECONNECT_INTERVAL_MAX;
            }

            PS_MEM_CPY(&(TAF_XSMS_MoGetRecAddr()->stNvResend), &stXsmsNv, sizeof(stXsmsNv));
            PS_MEM_CPY(&(TAF_XSMS_MtGetRecAddr()->stResend), &stXsmsNv, sizeof(stXsmsNv));

            TAF_XSMS_MoGetRecAddr()->ucReplySeq   = VOS_NULL;

            TAF_XSMS_MoInitSendPool();

            TAF_XSMS_MoIdleInit();
            TAF_XSMS_MtIdleInit();
            TAF_XSMS_RegMoFsm();
            TAF_XSMS_RegMtFsm();
            break;

        case   VOS_IP_RESTART:

            /* 注册到PIH，准备接收卡状态消息 */
            PIH_RegUsimCardStatusIndMsg(UEPS_PID_XSMS);

            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Taf_Xsms_EncodeCschOrderMsg
 功能描述  : 对CSCH 的order msg 进行编码
 输入参数  : 无
 输出参数  : pstCschDataReq
 返 回 值  : VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年12月5日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_XSMS_EncodeCschOrderMsg
(
    CNAS_CAS_1X_CSCH_DATA_REQ_STRU     *pstCschDataReq
)
{
    c_r_csch_ORDM                                          *pstORDM;
    VOS_INT32                                               lEncodeRslt;
    CS0005E_Details                                         stCS0005Detail;
    c_r_csch_mini6                                          stEncodeData;
    TAF_XSMS_3RD_PARTY_ERR_TYPE_ENUM_UINT32                 enErrType;

    /* 初始化内存 */
    PS_MEM_SET(&stEncodeData, 0, sizeof(stEncodeData));

    /* 分配ORDM结构 */
    SETPRESENT_c_r_csch_mini6_ORDM(&stEncodeData);

    pstORDM = stEncodeData.u.ORDM;

    if (VOS_NULL_PTR == pstORDM)
    {
        /* 防止外面空指针再次做释放 */
        stEncodeData.Present        = U_c_r_csch_mini6_NONE;

        return VOS_ERR;
    }

    /* 申请内存 */
    SETPRESENT_c_R_Orders_parameters_p_R_Generic_Order(&stEncodeData.u.ORDM->order.parameters);

    if (VOS_NULL_PTR == stEncodeData.u.ORDM->order.parameters.u.p_R_Generic_Order)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeCschOrderMsg: allocate memory fail");

        stEncodeData.u.ORDM->order.parameters.Present = U_c_R_Orders_parameters_NONE;

        FREE_c_r_csch_mini6(&stEncodeData);

        return VOS_ERR;
    }

    /* 先赋值 order code 和orderq */
    pstORDM->order.ORDER                    = 0x10; /* CAS_1X_REV_ORDER_CODE_MS_ACKNOWLEDGMENT */
    pstORDM->order.parameters.u.p_R_Generic_Order->ORDQ = 0;

    TAF_XSMS_SetCS0005EDetailPara(&stCS0005Detail, 0x0002, 6, 0); /* 0x0002和 6 的值需要CAS确认 */

    /* 编码 */
    lEncodeRslt = ENCODE_c_r_csch_mini6((char *)(pstCschDataReq->aucMsgData),
                                        0,
                                        &stEncodeData,
                                        &stCS0005Detail);

    if (lEncodeRslt < 0)
    {
        TAF_XSMS_ERROR_LOG("Taf_Xsms_EncodeCschOrderMsg: ENCODE_c_r_csch_mini6 fail");

        enErrType = TAF_XSMS_3RD_PARTY_ERR_DECODE_ENCODE_c_r_csch_mini6;

        TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_3RD_PARTY, (VOS_UINT8*)&enErrType, sizeof(TAF_XSMS_3RD_PARTY_ERR_TYPE_ENUM_UINT32));

        FREE_c_r_csch_mini6(&stEncodeData);
        /* 打印编码错误 */
        return VOS_ERR;
    }

    pstCschDataReq->usMsgDataLen = (VOS_UINT16)lEncodeRslt;

    FREE_c_r_csch_mini6(&stEncodeData);

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : TAF_XSMS_DealXccVoiceMailInd
 功能描述  : 对收到的XCC waiting ind 进行处理
 输入参数  : pstMsg-- XCC waiting ind
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月26日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_DealXccVoiceMailInd(MsgBlock* pstMsg)
{

    TAF_XSMS_MESSAGE_STRU               stDeliveryMsg;
    XCC_CSMS_MSG_WATING_IND_STRU       *pstMsgWaitInd;

    PS_MEM_SET(&stDeliveryMsg, 0, sizeof(TAF_XSMS_MESSAGE_STRU));

    pstMsgWaitInd                       = (XCC_CSMS_MSG_WATING_IND_STRU*)pstMsg;

    stDeliveryMsg.ulTeleserviceID       = TAF_XSMS_VOICE_NOTIFICATION;
    stDeliveryMsg.bIsServicePresent     = VOS_FALSE;

    /* 固定码流长度12字节 */
    stDeliveryMsg.ulBearerDataLen       = 12;

    /* 根据协议C.S0015 4.5.1 MSG_ID */
    stDeliveryMsg.aucBearerData[0]      = 0x00;
    stDeliveryMsg.aucBearerData[1]      = 0x03;
    stDeliveryMsg.aucBearerData[2]      = 0x10;
    stDeliveryMsg.aucBearerData[3]      = 0x00;
    stDeliveryMsg.aucBearerData[4]      = 0x00;

    /* 根据协议C.S0015 4.5.2 USER DATA */
    stDeliveryMsg.aucBearerData[5]      = 0x01;
    stDeliveryMsg.aucBearerData[6]      = 0x02;
    stDeliveryMsg.aucBearerData[7]      = 0x10;
    stDeliveryMsg.aucBearerData[8]      = 0x00;

    /* 根据协议C.S0015 4.5.12 MSG_COUNT */
    stDeliveryMsg.aucBearerData[9]      = 0x0b;
    stDeliveryMsg.aucBearerData[10]     = 0x01;

    /* 根据协议C.S0015 4.5.12 MSG_COUNT 小于等于99 */
    if (pstMsgWaitInd->ucMsgCnt > 99)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_DealXccVoiceMailInd:ucMsgCnt > 99!");
        return;
    }
    else
    {
        /* MSG_COUNT 数值 */
        stDeliveryMsg.aucBearerData[11]   =  pstMsgWaitInd->ucMsgCnt;
    }

    TAF_XSMS_MsgDeliveryInd(&stDeliveryMsg);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_AtApMemFullMsgProc
 功能描述  : 对收到的XCC waiting ind 进行处理
 输入参数  : pstMsg-- XCC waiting ind
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月26日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_AtApMemFullMsgProc(TAF_XSMS_APP_MSG_SET_AP_MEM_FULL_REQ_STRU *pstApMemFullMsg)
{
    /* 更新全局变量 */
    TAF_XSMS_SetApMemFullFlag(pstApMemFullMsg->enApMemFullFlag);

    /* 給AT回复OK */
    (VOS_VOID)TAF_XSMS_SetAPFullCnf(pstApMemFullMsg->usClientId, pstApMemFullMsg->ucOpId, VOS_OK);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_HookSmsTlAck
 功能描述  :
 输入参数  : pstMsg  短信内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月30日
    作    者   : c00299064
    修改内容   : 新生成函数
******************************************************************************/
VOS_VOID TAF_XSMS_HookSmsTlAck(
    TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32  enMsgName,
    TAF_XSMS_CAUSE_CODE_STRU           *pstCauseCode
)
{
    TAF_XSMS_INT_TL_ACK_STRU            stTlAck;

    PS_MEM_SET(&stTlAck, 0, sizeof(TAF_XSMS_INT_TL_ACK_STRU));

    PS_MEM_CPY(&stTlAck.stCauseCode, pstCauseCode, sizeof(TAF_XSMS_CAUSE_CODE_STRU));


    TAF_XSMS_MsgHook(enMsgName, (VOS_UINT8*)(&stTlAck), sizeof(stTlAck));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_HookSmsContect
 功能描述  : 勾去当前的短信内容
 输入参数  : pstMsg  短信内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月30日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_HookSmsContect(
    TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32  enMsgName,
    VOS_UINT32                          ulReqSeq,
    TAF_XSMS_MESSAGE_STRU              *pstXsmsMsg
)
{
    TAF_XSMS_INT_SMS_CONTENT_STRU       stXsmsContent;
    VOS_UINT16                          usUserDataStartByte = 0;
    VOS_UINT16                          usUserDataLen       = 0;

    PS_MEM_SET(&stXsmsContent, 0, sizeof(TAF_XSMS_INT_SMS_CONTENT_STRU));

    stXsmsContent.ulTeleserviceID       =  pstXsmsMsg->ulTeleserviceID;
    stXsmsContent.ulServiceCategory     =  pstXsmsMsg->ulServiceCategory;
    stXsmsContent.ulReplySeq            =  ulReqSeq;

    PS_MEM_CPY(&stXsmsContent.stAddr, &pstXsmsMsg->stAddr, sizeof(TAF_XSMS_ADDR_STRU));

    if ((TAF_XSMS_BEARER_DATA_MAX + 1) < pstXsmsMsg->ulBearerDataLen)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_HookSmsContect : pstXsmsMsg->ulBearerDataLen to large");
        return;
    }

    stXsmsContent.ulBearerDataLen       = pstXsmsMsg->ulBearerDataLen;

    PS_MEM_CPY(stXsmsContent.aucBearerData,
               pstXsmsMsg->aucBearerData,
               pstXsmsMsg->ulBearerDataLen);

    /* decode msg_Id and user data */
    TAF_XSMS_DecodeUserDataInBearerData(pstXsmsMsg->ulBearerDataLen,
                                        pstXsmsMsg->aucBearerData,
                                        &usUserDataStartByte,
                                        &usUserDataLen,
                                        &stXsmsContent.stUserData);

    TAF_XSMS_DecodeMsgId(pstXsmsMsg->ulBearerDataLen,
                         pstXsmsMsg->aucBearerData,
                         &stXsmsContent.stMsgId);

    TAF_XSMS_MsgHook(enMsgName, (VOS_UINT8*)(&stXsmsContent), sizeof(stXsmsContent));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_XcallProc
 功能描述  : XCALL的消息处理
 输入参数  : pstMsg  短信内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月30日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_XcallProc(MsgBlock *pstMsg)
{
    XCALL_XSMS_KMC_MSG_SEND_REQ_STRU   *pstSendReq;
    VOS_UINT32                          ulRet;
    TAF_XSMS_MESSAGE_STRU               stXsmsMsg;

    PS_MEM_SET(&stXsmsMsg, 0, sizeof(TAF_XSMS_MESSAGE_STRU));

    pstSendReq = (XCALL_XSMS_KMC_MSG_SEND_REQ_STRU*)pstMsg;

    switch (pstSendReq->enMsgId)
    {
        case ID_XCALL_XSMS_KMC_MSG_SEND_REQ:

            if (TAF_XSMS_MO_IDLE_STATE != TAF_XSMS_MoGetCurrFsmId())
            {
                /* 判断是否可以将XCALL的请求放在发送池里面 */
                if (VOS_TRUE == TAF_XSMS_IsRecCanInsertToPool(TAF_XSMS_SMS_ORIGPID_XCALL))
                {
                    if (VOS_ERR == TAF_XSMS_EncodeXcallMsgBearDataByContext(pstSendReq->aucData,
                                                             pstSendReq->usDataLen,
                                                             &stXsmsMsg))
                    {
                        TAF_XSMS_ERROR_LOG("TAF_XSMS_XcallProc: encode user data fail");
                        TAF_XSMS_SndXcallMsgSendCnf(XSMS_XCALL_SEND_RESULT_ENCODE_ERR, pstSendReq->usOpId);
                        return;
                    }

                    TAF_XSMS_GetKmcDefaultAddress(&stXsmsMsg.stAddr);

                    stXsmsMsg.ulTeleserviceID = TAF_XSMS_TELESERVICE_CDMACMT;

                    if (VOS_ERR == TAF_XSMS_InsertRecToMoSendPool(TAF_XSMS_SMS_ORIGPID_XCALL,
                                                   VOS_TRUE,
                                                   pstSendReq->usOpId,
                                                   &stXsmsMsg))
                    {
                        TAF_XSMS_ERROR_LOG("TAF_XSMS_XcallProc: TAF_XSMS_InsertRecToMoSendPool fail");
                        TAF_XSMS_SndXcallMsgSendCnf(XSMS_XCALL_SEND_RESULT_POOL_FULL, pstSendReq->usOpId);
                        return;
                    }
                }
                else
                {
                    TAF_XSMS_ERROR_LOG("TAF_XSMS_XcallProc: xcall req already in rec");
                    TAF_XSMS_SndXcallMsgSendCnf(XSMS_XCALL_SEND_RESULT_POOL_FULL, pstSendReq->usOpId);
                }

                return;
            }

            ulRet = TAF_XSMS_MoFsmMainProc(pstMsg);

            if (VOS_ERR == ulRet)
            {
                TAF_XSMS_ERROR_LOG("TAF_XSMS_XcallProc: handle err");
            }

            break;

        default:
            TAF_XSMS_ERROR_LOG("TAF_XSMS_XcallProc: xcall msg id err");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_XpdsProc
 功能描述  : Xpds的消息处理
 输入参数  : pstMsg  短信内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月14日
    作    者   : c00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_XpdsProc(MsgBlock *pstMsg)
{
    TAF_XPDS_XSMS_SEND_REQ_STRU        *pstSendReq;
    VOS_UINT32                          ulRet;
    TAF_XSMS_MESSAGE_STRU               stXsmsMsg;

    PS_MEM_SET(&stXsmsMsg, 0, sizeof(TAF_XSMS_MESSAGE_STRU));

    pstSendReq = (TAF_XPDS_XSMS_SEND_REQ_STRU*)pstMsg;

    switch (pstSendReq->enMsgName)
    {
        case ID_XPDS_XSMS_SEND_REQ:

            if (TAF_XSMS_MO_IDLE_STATE != TAF_XSMS_MoGetCurrFsmId())
            {
                /* 判断是否可以将Xpds的请求放在发送池里面 */
                if (VOS_TRUE == TAF_XSMS_IsRecCanInsertToPool(TAF_XSMS_SMS_ORIGPID_XPDS))
                {
                    (VOS_VOID)TAF_XSMS_EncodeXsmsMsgBearDataByContext(pstSendReq->aucData,
                                                                      pstSendReq->usDataLen,
                                                                      &stXsmsMsg);
                    PS_MEM_CPY(&stXsmsMsg.stAddr,
                               &pstSendReq->stXsmsAddr,
                               sizeof(TAF_XSMS_ADDR_STRU));

                    stXsmsMsg.ulTeleserviceID = TAF_XSMS_TELESERVICE_AGPS_NI_SMS;

                    (VOS_VOID)TAF_XSMS_InsertRecToMoSendPool(TAF_XSMS_SMS_ORIGPID_XPDS,
                                                             VOS_TRUE,
                                                             pstSendReq->usOpId,
                                                             &stXsmsMsg);
                }
                else
                {
                    TAF_XSMS_ERROR_LOG("TAF_XSMS_XpdsProc: XPDS ALREAD  EXIST IN REC");
                }

                return;
            }

            ulRet = TAF_XSMS_MoFsmMainProc(pstMsg);

            if (VOS_ERR == ulRet)
            {
                TAF_XSMS_ERROR_LOG("TAF_XSMS_XpdsProc: handle err");
            }

            break;

        default:
            TAF_XSMS_ERROR_LOG("TAF_XSMS_XpdsProc: xcall msg id err");
            break;
    }

    return;
}



#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



