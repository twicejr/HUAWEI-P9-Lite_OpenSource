


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"
#include "MnCallApi.h"
#include "MnComm.h"
#include "MnCallImsaProc.h"
#include "MnCallSendCc.h"
#include "MnCallFacilityEncode.h"
#include "MnCall.h"
#include "MnCallMgmt.h"
#include "TafSdcCtx.h"
#include "MnCallReqProc.h"
#include "NasCcIe.h"
#include "MnCallProcNvim.h"
#include "MnCallBcProc.h"
#include "MnCallReqProc.h"
#include "SpmImsaInterface.h"
#include "NasStkInterface.h"

#include "MnCallMnccProc.h"

#include "MnCallSendApp.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_MN_CALL_IMSA_PROC_C

/*****************************************************************************
  2 全局变量定义
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


/*****************************************************************************
  6 函数定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_CALL_ProcImsaMsg(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pstImsaMsg = VOS_NULL_PTR;

    pstImsaMsg = (MSG_HEADER_STRU *)pMsg;

    switch (pstImsaMsg->ulMsgName)
    {
        case ID_IMSA_CALL_SRVCC_CALL_INFO_NOTIFY:
            TAF_CALL_ProcImsaSrvccCallInfoNtf((CALL_IMSA_SRVCC_CALL_INFO_NOTIFY_STRU *)pstImsaMsg);
            break;

        case ID_IMSA_CALL_MSG_SYNC_IND:
            TAF_CALL_ProcImsaMsgSyncInd((IMSA_CALL_MSG_SYNC_IND_STRU *)pstImsaMsg);
            break;



        default:
            MN_WARN_LOG("TAF_CALL_ProcImsaMsg:Error MsgName");
            break;
    }

    return;
}




VOS_VOID TAF_CALL_ProcImsaSrvccCallInfoNtf(
    CALL_IMSA_SRVCC_CALL_INFO_NOTIFY_STRU                  *pstCallInfoNtf
)
{
    VOS_UINT8                           ucRealCallNum;
    MNCC_ENTITY_STATUS_STRU             astEntitySta[MNCC_MAX_ENTITY_NUM];

    /* 映射呼叫实体 */
    TAF_CALL_CreateCallEntitiesWithImsCallInfo(pstCallInfoNtf->ucCallNum, &(pstCallInfoNtf->astCallInfo[0]), pstCallInfoNtf->ucStartedHifiFlag);

    /* 初始化DTMF缓存队列 */
    TAF_CALL_InitDtmfCtx();

    /* 处理DTMF请求信息 */
    TAF_CALL_ProcSrvccDtmfBuffInfo(&(pstCallInfoNtf->stDtmfBuffInfo));

    /* 将CALL模块的呼叫信息映射成CC模块的呼叫信息 */
    PS_MEM_SET(&astEntitySta[0], 0, sizeof(MNCC_ENTITY_STATUS_STRU)*MNCC_MAX_ENTITY_NUM);

    TAF_CALL_MapCallInfoToCcInfo(&astEntitySta[0], &ucRealCallNum);

    /* 通知CC模块呼叫信息MNCC_SRVCC_CALL_INFO_NOTIFY */
    TAF_CALL_SendCcSrvccCallInfoNtf(ucRealCallNum, astEntitySta);

    return;
}



VOS_VOID TAF_CALL_SendImsaSrvccStatusNtf(
    CALL_IMSA_SRVCC_STATUS_ENUM_UINT32  enSrvccSta
)
{
    CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* 申请消息内存  */
    pstSndMsg = (CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_CALL_SendImsaSrvccStatusNtf: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* fill in message header */
    pstSndMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSndMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSndMsg->ulLength                    = sizeof(CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->enSrvccStatus               = enSrvccSta;

    /* fill in message name */
    pstSndMsg->ulMsgId                     = ID_CALL_IMSA_SRVCC_STATUS_NOTIFY;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstSndMsg);

    if (VOS_OK != ulRet)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_SendImsaSrvccStatusNtf: send msg fail!");
        return;
    }

    return;
}


VOS_VOID TAF_CALL_ConvertOrigReqMsg(
    SPM_IMSA_CALL_ORIG_REQ_STRU        *pstSrcMsg,
    MN_CALL_APP_REQ_MSG_STRU           *pstDstMsg
)
{
    /* 消息头这儿就不用填写了 */

    pstDstMsg->clientId = pstSrcMsg->usClientId;
    pstDstMsg->opId     = pstSrcMsg->ucOpId;
    pstDstMsg->enReq    = MN_CALL_APP_ORIG_REQ;

    /* 复制呼叫发起信息参数 */
    PS_MEM_CPY(&(pstDstMsg->unParm.stOrig), &(pstSrcMsg->stOrig), sizeof(MN_CALL_ORIG_PARAM_STRU));
}


VOS_VOID TAF_CALL_ConvertSupsCmdReqMsg(
    SPM_IMSA_CALL_SUPS_CMD_REQ_STRU    *pstSrcMsg,
    MN_APP_CALL_SUPS_REQ_STRU          *pstDstMsg
)
{
    /* 消息头这儿就不用填写了 */

    pstDstMsg->opID       = pstSrcMsg->ucOpId;
    pstDstMsg->usClientId = pstSrcMsg->usClientId;
    pstDstMsg->ulMsgId    = MN_CALL_APP_SUPS_CMD_REQ;

    PS_MEM_CPY(&(pstDstMsg->stSupsPara), &(pstSrcMsg->stCallMgmtCmd), sizeof(MN_CALL_SUPS_PARAM_STRU));
}


VOS_VOID TAF_CALL_ConvertStartDtmfReqMsg(
    SPM_IMSA_CALL_START_DTMF_REQ_STRU  *pstSrcMsg,
    MN_CALL_APP_REQ_MSG_STRU           *pstDstMsg
)
{
    /* 消息头这儿就不用填写了 */

    pstDstMsg->callId   = pstSrcMsg->stDtmf.CallId;
    pstDstMsg->clientId = pstSrcMsg->usClientId;
    pstDstMsg->opId     = pstSrcMsg->ucOpId;
    pstDstMsg->enReq    = MN_CALL_APP_START_DTMF_REQ;

    PS_MEM_CPY(&(pstDstMsg->unParm.stDtmf), &(pstSrcMsg->stDtmf), sizeof(TAF_CALL_DTMF_PARAM_STRU));
}


VOS_VOID TAF_CALL_ConvertStopDtmfReqMsg(
    SPM_IMSA_CALL_STOP_DTMF_REQ_STRU   *pstSrcMsg,
    MN_CALL_APP_REQ_MSG_STRU           *pstDstMsg
)
{
    pstDstMsg->callId = pstSrcMsg->stDtmf.CallId;
    pstDstMsg->clientId = pstSrcMsg->usClientId;
    pstDstMsg->opId     = pstSrcMsg->ucOpId;
    pstDstMsg->enReq    = MN_CALL_APP_STOP_DTMF_REQ;

    PS_MEM_CPY(&(pstDstMsg->unParm.stDtmf), &(pstSrcMsg->stDtmf), sizeof(TAF_CALL_DTMF_PARAM_STRU));
}


VOS_VOID TAF_CALL_ProcOrigReq(SPM_IMSA_CALL_ORIG_REQ_STRU *pstOrigReq)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstDstMsg = VOS_NULL_PTR;
    /* 申请消息内存  */
    pstDstMsg = (MN_CALL_APP_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(MN_CALL_APP_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstDstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_ProcOrigReq: ERROR:Memory Alloc is fail!");

        return;
    }

    PS_MEM_SET(pstDstMsg, 0, sizeof(MN_CALL_APP_REQ_MSG_STRU));

    /* 首先转换消息类型到call可处理的内部消息 */
    TAF_CALL_ConvertOrigReqMsg(pstOrigReq, pstDstMsg);

    /* 调用call模块Orig Req消息处理函数 */
    MN_CALL_CallOrigReqProc(pstDstMsg->clientId,
                            pstDstMsg->opId,
                            pstDstMsg->callId,
                            (MN_CALL_ORIG_PARAM_STRU*)&(pstDstMsg->unParm));

    /* 释放分配的内存空间 */
    PS_FREE_MSG(WUEPS_PID_TAF, pstDstMsg);
}


VOS_VOID TAF_CALL_ProcSupsCmdReq(SPM_IMSA_CALL_SUPS_CMD_REQ_STRU *pstSupsCmdReq)
{
    MN_APP_CALL_SUPS_REQ_STRU          *pstDstMsg = VOS_NULL_PTR;
    /* 申请消息内存  */
    pstDstMsg = (MN_APP_CALL_SUPS_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(MN_APP_CALL_SUPS_REQ_STRU));
    if (VOS_NULL_PTR == pstDstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_ProcSupsCmdReq: ERROR:Memory Alloc is fail!");

        return;
    }

    PS_MEM_SET(pstDstMsg, 0, sizeof(MN_APP_CALL_SUPS_REQ_STRU));

    /* 首先转换消息类型到call可处理的内部消息 */
    TAF_CALL_ConvertSupsCmdReqMsg(pstSupsCmdReq, pstDstMsg);

    /* 调用call模块SupsCmdReq消息处理函数 */
    MN_CALL_CallSupsCmdReqProc((struct MsgCB *)pstDstMsg);

    /* 释放分配的内存空间 */
    PS_FREE_MSG(WUEPS_PID_TAF, pstDstMsg);
}


VOS_VOID TAF_CALL_ProcStartDtmfReq(SPM_IMSA_CALL_START_DTMF_REQ_STRU *pstStartDtmfReq)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstDstMsg = VOS_NULL_PTR;
    TAF_CALL_DTMF_INFO_STRU             stDtmfInfo;
    TAF_CS_CAUSE_ENUM_UINT32            ulResult;

    /* 申请消息内存  */
    pstDstMsg = (MN_CALL_APP_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(MN_CALL_APP_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstDstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_ProcSupsCmdReq: ERROR:Memory Alloc is fail!");

        return;
    }

    PS_MEM_SET(pstDstMsg, 0, sizeof(MN_CALL_APP_REQ_MSG_STRU));

    /* 首先转换消息类型到call可处理的内部消息 */
    TAF_CALL_ConvertStartDtmfReqMsg(pstStartDtmfReq, pstDstMsg);

    /* 如果TCH还没有分配，直接就缓存 */
    if (VOS_FALSE == MN_CALL_GetTchStatus())
    {
        PS_MEM_SET(&stDtmfInfo, 0, sizeof(TAF_CALL_DTMF_INFO_STRU));

        stDtmfInfo.opId        = pstDstMsg->opId;
        stDtmfInfo.usClientId  = pstDstMsg->clientId;
        stDtmfInfo.CallId      = pstDstMsg->unParm.stDtmf.CallId;
        stDtmfInfo.cKey        = pstDstMsg->unParm.stDtmf.cKey;
        stDtmfInfo.usOffLength = pstDstMsg->unParm.stDtmf.usOffLength;
        stDtmfInfo.usOnLength  = pstDstMsg->unParm.stDtmf.usOnLength;

        ulResult = TAF_CALL_SaveDtmfInfo(&stDtmfInfo);

        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             ulResult);
    }
    else
    {
        /* 调用call模块StartDtmfReq消息处理函数 */
        TAF_CALL_RcvStartDtmfReq((struct MsgCB *)pstDstMsg);
    }


    /* 释放分配的内存空间 */
    PS_FREE_MSG(WUEPS_PID_TAF, pstDstMsg);
}


VOS_VOID TAF_CALL_ProcStopDtmfReq(SPM_IMSA_CALL_STOP_DTMF_REQ_STRU *pstStopDtmfReq)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstDstMsg = VOS_NULL_PTR;
    TAF_CALL_DTMF_INFO_STRU             stDtmfInfo;
    TAF_CS_CAUSE_ENUM_UINT32            ulResult;

    /* 申请消息内存  */
    pstDstMsg = (MN_CALL_APP_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(MN_CALL_APP_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstDstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_ProcSupsCmdReq: ERROR:Memory Alloc is fail!");

        return;
    }

    PS_MEM_SET(pstDstMsg, 0, sizeof(MN_CALL_APP_REQ_MSG_STRU));

    /* 首先转换消息类型到call可处理的内部消息 */
    TAF_CALL_ConvertStopDtmfReqMsg(pstStopDtmfReq, pstDstMsg);

        /* 如果TCH还没有分配，直接就缓存 */
    if (VOS_FALSE == MN_CALL_GetTchStatus())
    {
        PS_MEM_SET(&stDtmfInfo, 0, sizeof(TAF_CALL_DTMF_INFO_STRU));

        stDtmfInfo.opId        = pstDstMsg->opId;
        stDtmfInfo.usClientId  = pstDstMsg->clientId;
        stDtmfInfo.CallId      = pstDstMsg->unParm.stDtmf.CallId;
        stDtmfInfo.cKey        = pstDstMsg->unParm.stDtmf.cKey;
        stDtmfInfo.usOffLength = pstDstMsg->unParm.stDtmf.usOffLength;
        stDtmfInfo.usOnLength  = pstDstMsg->unParm.stDtmf.usOnLength;

        ulResult = TAF_CALL_SaveDtmfInfo(&stDtmfInfo);

        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             ulResult);
    }
    else
    {
        /* 调用call模块pstStopDtmfReq消息 */
        TAF_CALL_RcvStopDtmfReq((struct MsgCB *)pstDstMsg);
    }

    /* 释放分配的内存空间 */
    PS_FREE_MSG(WUEPS_PID_TAF, pstDstMsg);
}


VOS_VOID TAF_CALL_ProcSyncServiceMsgReq(MSG_HEADER_STRU *pstMsg)
{
    switch (pstMsg->ulMsgName)
    {
        case ID_SPM_IMSA_CALL_ORIG_REQ:
            TAF_CALL_ProcOrigReq((SPM_IMSA_CALL_ORIG_REQ_STRU *)pstMsg);
            break;

        case ID_SPM_IMSA_CALL_SUPS_CMD_REQ:
            TAF_CALL_ProcSupsCmdReq((SPM_IMSA_CALL_SUPS_CMD_REQ_STRU *)pstMsg);
            break;

        case ID_SPM_IMSA_CALL_START_DTMF_REQ:
            TAF_CALL_ProcStartDtmfReq((SPM_IMSA_CALL_START_DTMF_REQ_STRU *)pstMsg);
            break;

        case ID_SPM_IMSA_CALL_STOP_DTMF_REQ:
            TAF_CALL_ProcStopDtmfReq((SPM_IMSA_CALL_STOP_DTMF_REQ_STRU *)pstMsg);
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_ProcSyncMsgReq: This is an illegal message!");
            break;

    }
}



VOS_VOID TAF_CALL_ProcImsaMsgSyncInd(IMSA_CALL_MSG_SYNC_IND_STRU *pstMsgSyncInd)
{
    VOS_UINT8                           i;

    /* 检查消息数目是否合法 */
    if ((0 == pstMsgSyncInd->ucMsgNum)
     || (IMSA_CALL_MSG_SYNC_MAX_NUM < pstMsgSyncInd->ucMsgNum))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_ProcImsaMsgSyncInd: message number is invalid!");

        return;
    }

    for (i = 0; i < pstMsgSyncInd->ucMsgNum; i++)
    {
        TAF_CALL_ProcSyncServiceMsgReq((MSG_HEADER_STRU *)&(pstMsgSyncInd->astMsgArray[i]));
    }
}





#endif










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




