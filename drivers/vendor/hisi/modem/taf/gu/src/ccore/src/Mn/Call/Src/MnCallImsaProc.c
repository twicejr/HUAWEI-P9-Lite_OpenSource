
/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCallImsaProc.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年09月24日
  最近修改   :
  功能描述   : call模块与Imsa模块的消息交互文件
  函数列表   :

  修改历史   :
  1.日    期   : 2013年9月24日
    作    者   : W00176964
    修改内容   : 创建文件

******************************************************************************/

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

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */
#include "MnCallMnccProc.h"
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-5-20, begin */
#include "MnCallSendApp.h"
/* Added by y00245242 for V3R3C60_eCall项目, 2014-5-20, end */
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
/*****************************************************************************
 函 数 名  : TAF_CALL_ProcImsaMsg
 功能描述  : 处理来自IMSA的消息
 输入参数  : pstMsg  消息指针

 输出参数  : 无

 返回值    : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年12月14日
    作    者   : y00245242
    修改内容   : 增加SRVCC过程中缓存处理功能
*****************************************************************************/
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

        case ID_IMSA_CALL_CCWA_CAP_NOTIFY:
            TAF_CALL_ProcImsaCcwaCapNtf((IMSA_CALL_CCWA_CAP_NOTIFY_STRU *)pstImsaMsg);
            break;

        default:
            MN_WARN_LOG("TAF_CALL_ProcImsaMsg:Error MsgName");
            break;
    }

    return;
}

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-16, end */

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcImsaSrvccCallInfoNtf
 功能描述  : 处理来自IMSA的呼叫信息同步消息
 输入参数  : pstCallInfoNtf  IMSA通知的同步呼叫信息

 输出参数  : 无

 返回值    : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月24日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年12月23日
    作    者   : y00245242
    修改内容   : 增加SRVCC缓存处理
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_CALL_SendImsaSrvccStatusNtf
 功能描述  : 发送ID_CALL_IMSA_SRVCC_STATUS_NOTIFY消息给IMSA
 输入参数  : enSrvccSta--srvcc 状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月11日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CALL_ConvertSupsCmdReqMsg
 功能描述  : 转换呼叫请求消息

 输入参数  : pstSrcMsg －－ 源消息地址
             pstDstMsg －－ 目的消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CALL_ConvertSupsCmdReqMsg
 功能描述  : 转换与呼叫相关的补充业务请求

 输入参数  : pstSrcMsg －－ 源消息地址
             pstDstMsg －－ 目的消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CALL_ConvertStartDtmfReqMsg
 功能描述  : 转换启动DTMF请求

 输入参数  : pstSrcMsg －－ 源消息地址
             pstDstMsg －－ 目的消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CALL_ConvertStopDtmfReqMsg
 功能描述  : 转换停止DTMF请求

 输入参数  : pstSrcMsg －－ 源消息地址
             pstDstMsg －－ 目的消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcOrigReq
 功能描述  : 处理同步过来的呼叫请求消息

 输入参数  : pstOrigReq －－ 消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcSupsCmdReq
 功能描述  : 处理同步过来的与呼叫相关的补充业务请求

 输入参数  : pstSupsCmdReq －－ 消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcStartDtmfReq
 功能描述  : 处理同步过来的启动DTMF请求

 输入参数  : pstStartDtmfReq －－ 消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcStopDtmfReq
 功能描述  : 处理同步过来的启动DTMF请求

 输入参数  : pstStopDtmfReq －－ 消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
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

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcSyncServiceMsgReq
 功能描述  : 根据同步过来的消息类型，进行相应处理

 输入参数  : pstMsg －－ 同步过来的消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_CALL_ProcImsaMsgSyncInd
 功能描述  : 处理在SRVCC成功后，由IMSA模块同步过来的未发送呼叫相关的请求消息

 输入参数  : pstMsgSyncInd －－ 消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月14日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
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


/*****************************************************************************
 函 数 名  : TAF_CALL_ProcImsaCcwaCapNtf
 功能描述  : 处理IMSA上报的CCWA能力通知信息
 输入参数  : IMSA_CALL_CCWA_CAP_NOTIFY_STRU *pstCcwaCapNtf
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月24日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_CALL_ProcImsaCcwaCapNtf(
    IMSA_CALL_CCWA_CAP_NOTIFY_STRU     *pstCcwaCapNtf
)
{
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode;

    enCcwaCtrlMode = TAF_CALL_GetCcwaCtrlMode();

    /* 如果NV2340配置CCWA控制模式不是UE控制，则不处理ID_IMSA_CALL_CCWA_CAP_NOTIFY */
    if (TAF_CALL_CCWA_CTRL_BY_IMS != enCcwaCtrlMode)
    {
        return;
    }

    /* 将IMS域的CCWA能力保存到全局变量 */
    TAF_CALL_SetCcwaiFlg(pstCcwaCapNtf->ucCcwaCap);

    return;
}


#endif










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




