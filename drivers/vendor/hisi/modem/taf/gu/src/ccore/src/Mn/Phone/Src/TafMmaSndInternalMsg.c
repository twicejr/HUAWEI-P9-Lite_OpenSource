/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaSndInternalMsg.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年7月23日
  最近修改   :
  功能描述   : mma发给mma的消息的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月23日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafLog.h"
#include "TafMmaCtx.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_SND_INTERNAL_MSG_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  4 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_MMA_GetNextInternalMsg
 功能描述  : 获取内部消息队列中的下一条可用的内部消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 内部消息队列的指针
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月19日
   作    者   : W00176964
   修改内容   : 新生成函数
*****************************************************************************/
TAF_MMA_INTERNAL_MSG_BUF_STRU* TAF_MMA_GetNextInternalMsg( VOS_VOID )
{
    TAF_MMA_INTERNAL_MSG_BUF_STRU      *pstNextMsg = VOS_NULL_PTR;
    TAF_MMA_CONTEXT_STRU               *pstMmaCtx  =  VOS_NULL_PTR;
    VOS_UINT8                           ucNextIndex;

    pstMmaCtx   = TAF_MMA_GetMmaCtxAddr();

    if (pstMmaCtx->stInternalMsgQueue.ucHeader != pstMmaCtx->stInternalMsgQueue.ucTail)
    {
        ucNextIndex     = pstMmaCtx->stInternalMsgQueue.ucHeader;
        pstNextMsg      = (TAF_MMA_INTERNAL_MSG_BUF_STRU *)&(pstMmaCtx->stInternalMsgQueue.astMmaMsgQueue[ucNextIndex]);

        /* 取完一条消息,头指针向后偏移 */
        (pstMmaCtx->stInternalMsgQueue.ucHeader)++;
        (pstMmaCtx->stInternalMsgQueue.ucHeader) %= TAF_MMA_MAX_MSG_QUEUE_SIZE;

        return pstNextMsg;
    }

    TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_GetNextInternalMsg:Empty Internal Msg");

    return VOS_NULL_PTR;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetIntMsgSendBuf
 功能描述  : 从 内部消息缓存队列中获取内部消息发送缓冲区, 该缓冲区仅用于构建
             MMA的内部消息。
 输入参数  : VOS_UINT32 ulBufLen:缓存区大小
 输出参数  : 无
 返 回 值  : MsgBlock *
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月19日
   作    者   : W00176964
   修改内容   : 新增获取内部消息缓存队列的指针
*****************************************************************************/
TAF_MMA_INTERNAL_MSG_BUF_STRU *TAF_MMA_GetIntMsgSendBuf(
    VOS_UINT32                          ulLen
)
{
    TAF_MMA_INTERNAL_MSG_BUF_STRU      *pstTafMmaMsg        = VOS_NULL_PTR;
    TAF_MMA_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;

    pstInternalMsgQueue         = &(TAF_MMA_GetMmaCtxAddr()->stInternalMsgQueue);

    /* 从上下文中获取消息缓冲区指针 */
    pstTafMmaMsg = ( TAF_MMA_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->stSendMsgBuf);

    if (ulLen > TAF_MMA_MAX_MSG_BUFFER_LEN )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_GetIntMsgSendBuf: Buffer full" );

        TAF_MMA_SndOmInternalMsgQueueInfo(VOS_FALSE, VOS_FALSE);

        return VOS_NULL_PTR;
    }

    /* 清空这个消息缓冲单元 */
    PS_MEM_SET(pstTafMmaMsg, 0x00, sizeof(TAF_MMA_INTERNAL_MSG_BUF_STRU));

    /* 返回缓冲区指针 */
    return pstTafMmaMsg;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndInternalMsg
 功能描述  : 发送内部消息
 输入参数  : usMsgID:发送消息ID
             usMsgLen:发送消息长度
             pSndMsg:待发送的消息内容
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月19日
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_MMA_SndInternalMsg(
    VOS_VOID                           *pSndMsg
)
{
    VOS_UINT8                           ucMsgPnt;
    TAF_MMA_INTERNAL_MSG_BUF_STRU      *pstMmaMsg           = VOS_NULL_PTR;
    TAF_MMA_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;
    TAF_MMA_INTERNAL_MSG_BUF_STRU      *pstSndMsg           = VOS_NULL_PTR;

    pstInternalMsgQueue                 = &(TAF_MMA_GetMmaCtxAddr()->stInternalMsgQueue);
    pstSndMsg                           = (TAF_MMA_INTERNAL_MSG_BUF_STRU*)pSndMsg;

    /* 1. 判断内部消息缓冲区是否已满 */
    ucMsgPnt = pstInternalMsgQueue->ucTail;
    if ( ((ucMsgPnt + 1) % TAF_MMA_MAX_MSG_QUEUE_SIZE) == pstInternalMsgQueue->ucHeader )
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_SndInternalMsg:Warning: The Queue is full.");
        TAF_MMA_SndOmInternalMsgQueueInfo(VOS_TRUE, VOS_FALSE);
        return;
    }

    /* 2. 取得一个消息缓冲单元 */
    pstMmaMsg = (TAF_MMA_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->astMmaMsgQueue[ucMsgPnt]);

    /* 3. 判断消息长度是否非法 */
    if ( pstSndMsg->ulLength > TAF_MMA_MAX_MSG_BUFFER_LEN)
    {
        TAF_WARNING_LOG(UEPS_PID_MSCC, "TAF_MMA_SndInternalMsg:Warning: ulBufLen is too long.");
        return;
    }

    TAF_NORMAL_LOG1(WUEPS_PID_MMA, "TAF_MMA_SndInternalMsg: usMsgID is ", pstMmaMsg->usMsgID);

    /* 4. 将内部消息发送到内部消息队列中 */
    PS_MEM_CPY(pstMmaMsg, pstSndMsg, sizeof(TAF_MMA_INTERNAL_MSG_BUF_STRU));

    /* 更新内部消息缓冲区 */
    pstInternalMsgQueue->ucTail++;
    pstInternalMsgQueue->ucTail         %= TAF_MMA_MAX_MSG_QUEUE_SIZE;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndInterPowerInitReq
 功能描述  : 发送内部的上电请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月19日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_MMA_SndInterPowerInitReq(VOS_VOID)
{
    TAF_MMA_INTER_POWER_INIT_REQ_STRU  *pstPowerInitMsg = VOS_NULL_PTR;

    pstPowerInitMsg  = (TAF_MMA_INTER_POWER_INIT_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                       sizeof(TAF_MMA_INTER_POWER_INIT_REQ_STRU));

    if (VOS_NULL_PTR == pstPowerInitMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,
                      "TAF_MMA_SndMmaPowerInitReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPowerInitMsg + VOS_MSG_HEAD_LENGTH, 0,
              sizeof(TAF_MMA_INTER_POWER_INIT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPowerInitMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstPowerInitMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstPowerInitMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstPowerInitMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstPowerInitMsg->enMsgId         = MMA_MMA_INTER_POWER_INIT;
    pstPowerInitMsg->ulLength        = sizeof(TAF_MMA_INTER_POWER_INIT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 需要发送外部消息,因为上电时无外部消息触发内部消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstPowerInitMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,
                      "TAF_MMA_SndMmaPowerInitReq: Send message failed.");
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_SndInterUsimChangeInd
 功能描述  : 发送内部的卡状态改变指示消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndInterUsimChangeInd(VOS_VOID)
{
    TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU              *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU);

    pstInternalMsg  = (TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              sizeof(TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->enMsgId         = MMA_MMA_INTER_USIM_STATUS_CHANGE_IND;
    pstInternalMsg->ulLength        = sizeof(TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndSimlocakStatusChangeInd
 功能描述  : 发送锁网锁网卡状态变化指示
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月12日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndSimlocakStatusChangeInd(VOS_VOID)
{
    TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU                *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU);

    pstInternalMsg  = (TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              sizeof(TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->enMsgId         = MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND;
    pstInternalMsg->ulLength        = sizeof(TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}



/*****************************************************************************
 函 数 名  : TAF_MMA_SndPhoneModeRsltInd
 功能描述  : 发送phone mode状态机退出结果指示消息
 输入参数  : enRslt:状态机退出结果消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月19日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndPhoneModeRsltInd(
    TAF_MMA_PHONE_MODE_RESULT_ENUM_UINT8                    enRslt
)
{
    TAF_MMA_PHONE_MODE_RSLT_IND_STRU   *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(TAF_MMA_PHONE_MODE_RSLT_IND_STRU);

    pstInternalMsg  = (TAF_MMA_PHONE_MODE_RSLT_IND_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              ulLen - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->enMsgId         = MMA_MMA_PHONE_MODE_RSLT_IND;
    pstInternalMsg->ulLength        = ulLen - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->enRslt                    = enRslt;

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : TAF_MMA_SndImsSwitchRsltInd
 功能描述  : 发送ims switch状态机退出结果指示消息
 输入参数  : enRslt:状态机退出结果消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-02-04
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndImsSwitchRsltInd(
    TAF_MMA_IMS_SWITCH_RESULT_ENUM_UINT8                    enRslt
)
{
    TAF_MMA_IMS_SWITCH_RSLT_IND_STRU   *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(TAF_MMA_IMS_SWITCH_RSLT_IND_STRU);

    pstInternalMsg  = (TAF_MMA_IMS_SWITCH_RSLT_IND_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              ulLen - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->enMsgId         = MMA_MMA_IMS_SWITCH_RSLT_IND;
    pstInternalMsg->ulLength        = ulLen - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->enRslt                    = enRslt;

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_SndSysCfgRsltInd
 功能描述  : 发送System Config状态机退出结果指示消息
 输入参数  : enRslt:状态机退出结果消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月5日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndSysCfgRsltInd(
    TAF_MMA_SYS_CFG_RSLT_ENUM_UINT8                         enRslt,
    VOS_UINT8                                               ucIsNeedChkLock
)
{
    TAF_MMA_SYS_CFG_RSLT_STRU          *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(TAF_MMA_SYS_CFG_RSLT_STRU);

    pstInternalMsg  = (TAF_MMA_SYS_CFG_RSLT_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              ulLen - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->enMsgId         = MMA_MMA_SYS_CFG_RSLT_IND;
    pstInternalMsg->ulLength        = ulLen - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->ucIsNeedChkLock           = ucIsNeedChkLock;
    pstInternalMsg->enRslt                    = enRslt;

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndInterSysCfgSetReq
 功能描述  : 发送内部消息MMA_MMA_INTER_SYS_CFG_SET_REQ
 输入参数  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月9日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndInterSysCfgSetReq(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg
)
{
    TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU);

    pstInternalMsg  = (TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              ulLen - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->enMsgId         = MMA_MMA_INTER_SYS_CFG_SET_REQ;
    pstInternalMsg->ulLength        = ulLen - VOS_MSG_HEAD_LENGTH;
    PS_MEM_CPY(&(pstInternalMsg->stSysCfgPara), pstSysCfg, sizeof(TAF_MMA_SYS_CFG_PARA_STRU));

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_MMA_SndInterMmaAbortInd
 功能描述  : 发送内部中止指示消息给MMA, 终止当前状态机操作
 输入参数  : VOS_UINT16                          usSid
             VOS_UINT16                          usNid
             VOS_UINT8                           ucPzid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月09日
    作    者   : y00245242
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SndInterMmaAbortInd(VOS_VOID)
{
    TAF_MMA_INTER_ABORT_IND_STRU        *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_INTER_ABORT_IND_STRU*)TAF_MMA_GetIntMsgSendBuf(sizeof(TAF_MMA_INTER_ABORT_IND_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }

    PS_MEM_SET(pstSndMsg, 0, sizeof(TAF_MMA_INTER_ABORT_IND_STRU));

    pstSndMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid     = WUEPS_PID_MMA;
    pstSndMsg->ulLength          = sizeof(TAF_MMA_INTER_ABORT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->enMsgId           = MMA_MMA_INTER_ABORT_IND;

    TAF_MMA_SndInternalMsg(pstSndMsg);

    return;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



