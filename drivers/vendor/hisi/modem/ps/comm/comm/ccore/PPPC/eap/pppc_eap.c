/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pppc_eap.c
  版 本 号   : 初稿
  作    者   : q00359829
  生成日期   : 2015年11月12日
  最近修改   :
  功能描述   : EAP 消息解析
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月12日
    作    者   : q00359829
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"
#include "pppc_md5.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PPPC_EAP_C
/*lint +e767*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : PPPC_EAP_ReceiveRequest
 功能描述  : EAP收到Request消息, 分析报文头并作相应处理
 输入参数  : pstPppInfo     PPP控制块指针
                            pPacket         报文指针
                            ucId               eap报文Id
                            ulLen           eap报文长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :PPPC_EAP_ReceivePacket

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : q00359829
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_ReceiveRequest
(
    PPPINFO_S *pstPppInfo, VOS_UINT8 *pPacket, VOS_UINT8 ucId, VOS_UINT32 ulLen
)
{
    VOS_UINT8                           ucPayloadType;
    PPPC_EAP_INFO_STRU                 *pstEapInfo;


    /* Payload长度不合法 */
    if ((EAP_PAYLOAD_MAX_LEN < ulLen) || (PPPC_EAP_HEADERLEN > ulLen))
    {
        /*输出错误调试信息*/
        PPPC_WARNING_LOG1("EAP Payload err", ulLen);
        return;
    }

    /* 获取EAP报文中的Payload type */
    PPP_GET_EAP_TYPE(ucPayloadType, pPacket);

    /*更新发送报文ID和TYPE*/
    pstEapInfo                          = pstPppInfo->pstEapInfo;
    pstEapInfo->ucRequestID             = ucId;
    pstEapInfo->enRequestType           = ucPayloadType;

    /* ID 与上一次相等 */
    if (ucId == pstEapInfo->usEAPLastReqID)
    {
        PPPC_EAP_SendResponse(pstPppInfo->ulRPIndex);
        return;
    }

    /*根据TYPE不同触发相应事件*/
    switch (ucPayloadType)
    {
        case PPPC_EAP_IDENTITY_TYPE:
            PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_IDENTITY_REQ_EVENT, pPacket);
            break;

        case PPPC_EAP_NOTIFY_TYPE:
            PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_NOTIFY_REQ_EVENT, pPacket);
            break;

        case PPPC_EAP_MD5_TYPE:
            PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_AUTH_REQ_EVENT, pPacket);
            break;

        case PPPC_EAP_AKA_TYPE:
            PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_AUTH_REQ_EVENT, pPacket);
            break;

        case PPPC_EAP_AKA_PRIME_TYPE:
            PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_AUTH_REQ_EVENT, pPacket);
            break;

        default:
            /*未知方法，报NAK*/
            PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_NAK_EVENT, pPacket);
            break;
    }
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_ReceiveSuccess
 功能描述  : EAP收到Success消息的处理
 输入参数  : pstPppInfo     PPP控制块指针
                            pPacket         报文指针
                            ucId               eap报文Id
                            ulLen           eap报文长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :PPPC_EAP_ReceivePacket

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : q00359829
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_ReceiveSuccess
(
    PPPINFO_S *pstPppInfo, VOS_UINT8 *pPacket, VOS_UINT8 ucId, VOS_UINT32 ulLen
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    /*更新发送报文ID*/
    pstEapInfo                          = pstPppInfo->pstEapInfo;
    pstEapInfo->ucRequestID             = ucId;


    PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_SUCCESS_EVENT, pPacket);
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_ReceiveFailure
 功能描述  : EAP收到Failure消息的处理
 输入参数  : pstPppInfo     PPP控制块指针
                            pPacket         报文指针
                            ucId               eap报文Id
                            ulLen           eap报文长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :PPPC_EAP_ReceivePacket

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : q00359829
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_ReceiveFailure
(
    PPPINFO_S *pstPppInfo, VOS_UINT8 *pPacket, VOS_UINT8 ucId, VOS_UINT32 ulLen
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    /*更新发送报文ID*/
    pstEapInfo                          = pstPppInfo->pstEapInfo;
    pstEapInfo->ucRequestID             = ucId;

    /*上报OM可维可测信息*/
    g_stPppcStatRpt.stPppcStatisticInfo.ulNameOrPwdAuthFailCnt++;
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    PPPC_EAP_PeerProcessEvent(pstPppInfo->ulRPIndex, PPPC_EAP_PEER_FAILURE_EVENT, pPacket);
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_ReceivePacket
 功能描述  : EAP收到消息的处理
 输入参数  : pstPppInfo     PPP控制块指针
                            pPacket         报文指针
                            ucId               eap报文Id
                            ulLen           eap报文长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :PPPC_EAP_ReceivePacket

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : q00359829
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_ReceivePacket
(
    PPPINFO_S                          *pstPppInfo,
    VOS_UINT8                          *pHead,
    VOS_UINT8                          *pPacket,
    VOS_UINT32                          ulLen
)
{
    PPPC_EAP_INFO_STRU                 *pstEapInfo;
    VOS_UINT8                           ucCode;
    VOS_UINT8                           ucId;
    VOS_UINT16                          usCiLen;
    VOS_UINT32                          ulRet;


    if ((VOS_NULL_PTR == pPacket) || (VOS_NULL_PTR == pstPppInfo))
    {
        PPPC_WARNING_LOG("Input param invalid!");
        return;
    }

    pstEapInfo = pstPppInfo->pstEapInfo;
    if (VOS_NULL_PTR == pstEapInfo)
    {
        PPPC_WARNING_LOG("pstEapInfo=NULL");
        return;
    }

    /* 如果报文包太短则丢弃 */
    if (ulLen < FSM_HDRLEN)
    {
        PPPC_WARNING_LOG1("Too short packet", ulLen);
        return;
    }

    /* 获得报文中字段值, 并移动报文指针*/
    PPP_GET_EAP_CODE(ucCode, pPacket);
    PPP_GET_EAP_ID(ucId, pPacket);
    PPP_GET_EAP_LEN(usCiLen, pPacket);

    if ((PPPC_EAP_HEADERLEN > usCiLen) || (EAP_PAYLOAD_MAX_LEN <= usCiLen))
    {
        PPPC_WARNING_LOG1("Invalue EAP packet length", usCiLen);
        return;
    }

    /*重启定时器*/
    if (VOS_NULL_PTR != pstEapInfo->hReqTimeoutID)
    {
        (VOS_VOID)VOS_StopRelTimer((HTIMER *)&(pstEapInfo->hReqTimeoutID));
    }

    ulRet   = VOS_StartRelTimer((HTIMER *)&(pstEapInfo->hReqTimeoutID), MSPS_PID_PPPC,
           PPPC_EAP_TIMEOUT_LENTH, pstPppInfo->ulRPIndex, PPPC_EAP_RCV_EAP_REQ_TIMER,
           VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);
    if (VOS_OK != ulRet)
    {
       PPPC_WARNING_LOG("EAP VOS_Timer_Create TIMER error!");
    }

    /*分析三种code，调用不同函数*/
    switch (ucCode)
    {
        case PPPC_EAP_REQUEST_TYPE:
            PPPC_EAP_ReceiveRequest(pstPppInfo, pPacket, ucId, ulLen);
            break;

        case PPPC_EAP_SUCCESS_TYPE:
            PPPC_EAP_ReceiveSuccess(pstPppInfo, pPacket, ucId, ulLen);
            break;

        case PPPC_EAP_FAILURE_TYPE:
            PPPC_EAP_ReceiveFailure(pstPppInfo, pPacket, ucId, ulLen);
            break;

        default:
            {
                /*输出错误调试信息*/
                PPPC_WARNING_LOG1("Illegal Packet Code", ucCode);
            }
            break;
    }
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_RcvReqTimeout
 功能描述  : 超时处理
 输入参数  : ulPppId     PPP序号
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EAP_RcvReqTimeout(VOS_UINT32 ulPppId)
{
    PPPC_EAP_PeerProcessEvent(ulPppId, PPPC_EAP_PEER_TIMEOUT_EVENT, VOS_NULL_PTR);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_MD5_CheckParam
 功能描述  : 入参检查
 输入参数  : pstEAPInput         输入
 输出参数  : pstMethodOutput
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_MD5_CheckParam
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPInput
)
{
    if ((VOS_NULL_PTR == pstMethodOutput) || (VOS_NULL_PTR == pstEAPInput))
    {
        PPPC_WARNING_LOG("Input param is null!");
        return VOS_ERR;
    }

    if ((VOS_NULL_PTR == pstMethodOutput->pucPktData)
        || (VOS_NULL_PTR == pstMethodOutput->pusRespLen)
        || (VOS_NULL_PTR == pstEAPInput->pucPktData))
    {
        PPPC_WARNING_LOG("Input sub param is null");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_MD5_ProcessPkt
 功能描述  : EAP Md5方法计算鉴权结果
 输入参数  : pstEAPInfo     EAP实体信息
             ucPpstEAPInput 输入
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-9
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EAP_MD5_ProcessPkt
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPInput
)
{
    PPPC_AUTH_MSG_STRU                  stMsg;
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucData;
    VOS_UINT16                          usPayloadLen;
    VOS_UINT16                          usRespLen;
    VOS_UINT16                          usNameLen;
    VOS_UINT8                           aucHostName[PPP_MAXUSERNAMELEN + 2]; /* 主机名 */


    ulRet   = PPPC_EAP_MD5_CheckParam(pstMethodOutput, pstEAPInput);
    if (VOS_OK != ulRet)
    {
        return;
    }

    PS_MEM_SET(&stMsg, 0, sizeof(stMsg));
    PS_MEM_SET(aucHostName, 0, sizeof(aucHostName));

    if (pstEAPInput->usEAPLen <= (PPPC_EAP_HEADERLEN + PPPC_EAP_TYPE_FIELD_LEN))
    {
        PPPC_WARNING_LOG1("Invalid md5 len!", pstEAPInput->usEAPLen);
        return;
    }

    /* 获取报文ID */
    stMsg.ucPktID   = pstEAPInput->ucEAPID;

    /* 获取报文指针 */
    pucData         = pstEAPInput->pucPktData;

    /* 获取payload长度 */
    usPayloadLen    = pstEAPInput->usEAPLen
                    - PPPC_EAP_HEADERLEN - PPPC_EAP_TYPE_FIELD_LEN;

    /* 偏移到TYPE-DATA域 */
    PPP_INCPTR(PPPC_EAP_HEADERLEN + PPPC_EAP_TYPE_FIELD_LEN, pucData);

    PPP_GETCHAR(stMsg.ucPwdLen, pucData);

    usPayloadLen--;

    if (usPayloadLen < stMsg.ucPwdLen)
    {
        PPPC_WARNING_LOG2("Invalid pwd len!", usPayloadLen, stMsg.ucPwdLen);
        return;
    }

    /* 获取密码 */
    PS_MEM_CPY(stMsg.szPwd, pucData, stMsg.ucPwdLen);

    /* 移动指针 */
    PPP_INCPTR(stMsg.ucPwdLen, pucData);

    usPayloadLen       -= stMsg.ucPwdLen;
    stMsg.ucUsrNameLen  = (VOS_UINT8)usPayloadLen;

    if (stMsg.ucUsrNameLen >= PPP_MAXUSERNAMELEN)
    {
        PPPC_WARNING_LOG1("Invalid username len", stMsg.ucUsrNameLen);
        stMsg.ucUsrNameLen  = PPP_MAXUSERNAMELEN;
    }

    /* 获取用户名 */
    PS_MEM_CPY(stMsg.szUsrName, pucData, stMsg.ucUsrNameLen);

    /*取本地的password,作为产生Response的备用secret */
    ulRet = PPP_GetConfigPassWord((VOS_UINT8 *)stMsg.szResponse);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG2("Get pass word fail when when receive challenge.",
            ulRet, pstMethodOutput->ulPppId);
    }

    stMsg.ucResponseLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)(stMsg.szResponse));

    /* 调用MD5算法产生Response */
    PPPC_MD5_GenResponse(&stMsg);

    /* 将Response刷新到EAP实体中 */
    pucData     = pstMethodOutput->pucPktData
                + PPPC_EAP_HEADERLEN + PPPC_EAP_TYPE_FIELD_LEN;
    PPP_PUTCHAR(stMsg.ucResponseLen, pucData);
    PS_MEM_CPY(pucData, stMsg.szResponse, stMsg.ucResponseLen);
    pucData     += stMsg.ucResponseLen;

    /* 刷新Response长度 */
    usRespLen   = PPPC_EAP_HEADERLEN + PPPC_EAP_TYPE_FIELD_LEN
                + sizeof(stMsg.ucResponseLen) + stMsg.ucResponseLen;

    ulRet = PPP_GetConfigUserName(aucHostName, pstMethodOutput->ulPppId);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG2("Get user name fail when when receive challenge.",
            ulRet, pstMethodOutput->ulPppId);
    }

    usNameLen = (VOS_UINT16) VOS_StrLen((CHAR *)aucHostName);
    if (PPPC_EAP_MAX_RESPONSE_LEN <= (usNameLen + usRespLen)
        || (PPP_MAXUSERNAMELEN < usNameLen))
    {
        PPPC_WARNING_LOG3("Invalid name len",
            usNameLen, usRespLen, pstMethodOutput->ulPppId);
        usNameLen   = PPP_MAXUSERNAMELEN;
    }

    PS_MEM_CPY(pucData, aucHostName, usNameLen);

    usRespLen   += usNameLen;

    PPPC_EAP_UpdateLen(pstMethodOutput->pucPktData, pstMethodOutput->pusRespLen, usRespLen);

    PPPC_EAP_SendResponse(pstMethodOutput->ulPppId);

    PPPC_EAP_PeerProcessEvent(pstMethodOutput->ulPppId,
            PPPC_EAP_PEER_AUTH_IND_EVENT, VOS_NULL_PTR);

    return;
}

#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

