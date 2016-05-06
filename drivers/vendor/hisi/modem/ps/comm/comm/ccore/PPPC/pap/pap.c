/************************************************************************
*                                                                      *
*                             pap.c                                    *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/06/01                                      *
*  Author:             Zhu Fengzhi                                     *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP的PAP协议模块                                *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了PAP协议模块的全部接口函数和内部处理函数                *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"
#include "pppc_ctrl.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_PAP_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：PAP初始化PAP控制块                                            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_Core_AuthenticatePhase                                    *
****************************************************************************/
VOID PPP_PAP_Init(PPPINFO_S *pstPppInfo)
{
    PPPPAPINFO_S *pstPapInfo;
    PPPCONFIGINFO_S *pstConfig;

    if (pstPppInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_279);
        return;
    }

    pstPapInfo = pstPppInfo->pstPapInfo;
    pstConfig = pstPppInfo->pstUsedConfigInfo;
    if ((pstPapInfo == NULL) || (pstConfig == NULL))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_280);
        return;
    }
    pstPapInfo->ucUsed = 1;
    pstPapInfo->pstPppInfo = pstPppInfo;
    pstPapInfo->ucClientState = PAP_STATE_CLIENT_INITIAL;
    pstPapInfo->ucServerState = PAP_STATE_SERVER_INITIAL;
    pstPapInfo->ucId = 0;
    pstPapInfo->ucPeerId = 0;
    pstPapInfo->ulSendReqTimeout = pstConfig->ulNegTimeOut;
    pstPapInfo->ulWaitReqTimeout = PAP_WAITREQUESTTIME;
    pstPapInfo->ulWaitLnsAuthTimeOut = PAP_WAITLNSAUTHTIME;
    pstPapInfo->ulMaxTransmits = PPP_DEFMAXCONFREQS;
    pstPapInfo->ucTransmits = 0;
    pstPapInfo->ulClientTimeoutID = 0;
    pstPapInfo->ulServerTimeoutID = 0;
    pstPapInfo->usAuthClientFailureTimes = 0;
    pstPapInfo->usAuthServerFailureTimes = 0;

    pstPapInfo->ulWaitAuthRspTimeout = PAP_WAITAAARSPTIME;
    pstPapInfo->ulAuthMaxTransmits = PAP_MAXAUTHTRANSMITS;
    pstPapInfo->ucAuthTransmits  = 0;
    pstPapInfo->pstAAAAuthReqMsg = NULL;

    /* 输出事件调试信息 */
    PAP_Debug_Event(pstPppInfo, PAP_INITIALIZATION);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：PAP接收外部事件.事件包括：ClientUp、ServerUp、Down            *                                           Open、Close            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                ulCmd:命令字,可以为如下值:                                 *
*                    PAP_EVENT_CLIENTLOWERUP:本地下层UP                        *
*                    PAP_EVENT_SERVERLOWERUP:对端下层UP                        *
*                    PAP_EVENT_LOWERDOWN:下层DOWN                            *
*                pPara:事件的参数,为NULL                                    *
* OUTPUT       ：                                                           *
* RETURN       ：NULL                                                       *
* CALLED BY    ：PPP_Core_AuthenticatePhase                                    *
****************************************************************************/
VOID PPP_PAP_ReceiveEventFromCore (PPPINFO_S *pstPppInfo, VOS_UINT32 ulCmd, char *pPara)
{
    if (pstPppInfo == 0)
    {
        return;
    }

    switch (ulCmd)
    {
        case PAP_EVENT_CLIENTLOWERUP:
            PPP_PAP_ClientLowerUp(pstPppInfo);
            break;

        case PAP_EVENT_SERVERLOWERUP:
            PPP_PAP_ServerLowerUp(pstPppInfo);
            break;

        case PAP_EVENT_LOWERDOWN:
            PPP_PAP_LowerDown(pstPppInfo);
            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_281);
            PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Error Event!" );
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：PAP本地LowerUp,由对端验证我方                                *
*                 进入PAP_STATE_SEND_AUTHREQ状态,向对端发出验证请求              *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_PAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_PAP_ClientLowerUp(PPPINFO_S *pstPppInfo)
{
    PPPCONFIGINFO_S                    *pstConfig       = pstPppInfo->pstUsedConfigInfo;
    PPPPAPINFO_S                       *pstPapInfo      = pstPppInfo->pstPapInfo;
    VOS_UINT32                          ulRet;


    PPPC_INFO_LOG("\r\nPPP_PAP_ClientLowerUp \r\n");

    if ((pstPapInfo == NULL) || (pstConfig == NULL))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_282);
        return;
    }

    /* 输出事件调试信息 */
    PAP_Debug_Event(pstPppInfo, PAP_CLIENTLOWERUP);

    ulRet = PPP_GetConfigUserName(pstPapInfo->szPapUsrName, pstPppInfo->ulRPIndex);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("Get username fail when pap client up.");
    }

    ulRet = PPP_GetConfigPassWord(pstPapInfo->szPapUsrPwd);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("Get pass word fail when pap client up.");
    }

    pstPapInfo->ucTransmits = 0;
    pstPapInfo->ucId = 0;
    pstPapInfo->ulSendReqTimeout = pstConfig->ulNegTimeOut;
    pstPapInfo->ulMaxTransmits = PPP_DEFMAXCONFREQS;
    pstPapInfo->ucTransmits = 0;
    pstPapInfo->ulClientTimeoutID = 0;
    pstPapInfo->usAuthClientFailureTimes = 0;

    PPP_PAP_SendAuthReq(pstPppInfo);

    /* 输出状态转换调试信息 */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SEND_AUTHREQ, CLIENT_STATE);
    pstPapInfo->ucClientState = PAP_STATE_SEND_AUTHREQ;

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：PAP远端LowerUp,由我端验证对端                                *
*                 进入PAP_STATE_SERVER_LISTEN状态,等待对端送出验证字            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_PAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_PAP_ServerLowerUp(PPPINFO_S *pstPppInfo)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;

    if (pstPapInfo == NULL)
    {
        return;
    }

    pstPapInfo->ucPeerId = 0;
    pstPapInfo->ulWaitReqTimeout  = PAP_WAITREQUESTTIME;
    pstPapInfo->ulServerTimeoutID = 0;
    pstPapInfo->usAuthServerFailureTimes = 0;

    /* 输出事件调试信息 */
    PAP_Debug_Event(pstPppInfo, PAP_SERVERLOWERUP);

    /*申请等待对断送出验证请求超时定时器 */
    (VOS_VOID)VOS_StartRelTimer((HTIMER *)&(pstPapInfo->ulServerTimeoutID),
                                MID_PPPC,
                                pstPapInfo->ulWaitReqTimeout,
                                pstPppInfo->ulRPIndex,
                                PPPC_PAP_WAIT_FOR_REQ_TIMER,
                                VOS_TIMER_LOOP,
                                VOS_TIMER_PRECISION_0);

    /* 输出状态转换调试信息 */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SERVER_LISTEN, SERVER_STATE);
    pstPapInfo->ucServerState = PAP_STATE_SERVER_LISTEN;

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：PAPLowerDown                                                *
*                 进入PAP_STATE_SERVER_INITIAL状态并进入PAP_STATE_CLIENT_INITIAL状态*
*                 同时删除定时器                                                *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_PAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_PAP_LowerDown(PPPINFO_S *pstPppInfo)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;

    if (pstPapInfo == NULL)
    {
        return;
    }

    /* 输出事件调试信息 */
    PAP_Debug_Event(pstPppInfo, PAP_LOWERDOWN);
    PPP_PAP_DeleteTimer(pstPppInfo);    /*删除定时器 */
    /* 输出状态转换调试信息 */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SERVER_INITIAL, SERVER_STATE);
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_CLIENT_INITIAL, CLIENT_STATE);

    pstPapInfo->ucClientState = PAP_STATE_CLIENT_INITIAL;
    pstPapInfo->ucServerState = PAP_STATE_SERVER_INITIAL;

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：PAP收到pap 数据包,分析报文头并作相应处理                    *
*                pHead:存放报文内存的头指针包括协议号,应负责释放这段内存    *
*                pPacket:报文头位置                                         *
*                ulLen:报文长度                                             *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_Core_ReceivePacketFromShell                            *
****************************************************************************/
VOID PPP_PAP_ReceivePacket (PPPINFO_S *pstPppInfo, UCHAR* pHead, UCHAR* pPacket, VOS_UINT32 ulLen)
{
    UCHAR ucCode, ucId;
    VOS_UINT32 ulCiLen;

    if (pstPppInfo == NULL)
    {
        return;
    }

    /*输出报文调试信息*/
    PAP_Debug_Packet(pstPppInfo, pPacket, ulLen, PPP_PAP, 1);

    PPPC_INFO_LOG("\r\n PPP_PAP_ReceivePacket \r\n");

    /*分析报文头(code,id, length)*/
    if (ulLen < FSM_HDRLEN)        /* 如果报文包太短则丢弃 */
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_283);
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        return;
    }

    /* 获得报文中字段值,并移动报文指针 */
    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(ucId, pPacket);
    PPP_GETSHORT(ulCiLen, pPacket);

    if ((ulCiLen > ulLen) || (ulCiLen < PAP_HEADERLEN))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_284);
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Error packet length!");
        return;
    }

    ulCiLen -= PAP_HEADERLEN;

    /* 依照 code 采用相应的动作 */
    switch (ucCode)
    {
        case PAP_AUTHREQ:/* 收到 Authenticate-Request */
            PPP_DBG_OK_CNT(PPP_PHOK_932);
            PPPC_WARNING_LOG3("Peer should not receive Authenticate-Request", pstPppInfo->ulRPIndex, ucId, ulCiLen);
            break;

        case PAP_AUTHACK:/*收到 Authenticate_Ack */
            PPP_PAP_ReceiveAuthAck(pstPppInfo, pPacket, ucId, ulCiLen);
            break;

        case PAP_AUTHNAK:/* 收到 Authenticate-Nak */
            PPP_PAP_ReceiveAuthNak(pstPppInfo, pPacket, ucId, ulCiLen);
            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_285);
            PPP_PAP_ReceiveUnknownCode(pstPppInfo); /* code拒绝 */
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：删除定时器                                                    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：                                                            *
****************************************************************************/
VOID PPP_PAP_DeleteTimer(PPPINFO_S *pstPppInfo)
{
    PPPPAPINFO_S *pstPapInfo;

    if (pstPppInfo == NULL)
    {
        return;
    }

    pstPapInfo = pstPppInfo->pstPapInfo;
    if (pstPapInfo == NULL)
    {
        return;
    }

    if (pstPapInfo->ulClientTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulClientTimeoutID));   /* 删除Client定时器 */
        pstPapInfo->ulClientTimeoutID = 0;
    }

    if (pstPapInfo->ulServerTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));    /* 删除Server 定时器 */
        pstPapInfo->ulServerTimeoutID = 0;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：PAP收到一非法协议,通知底层DOWN                                *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_PAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_PAP_ReceiveUnknownCode(PPPINFO_S *pstPppInfo)
{
    /* 输出事件调试信息 */
    PAP_Debug_Event(pstPppInfo, PAP_CODEREJECT);

    return;
}

/*
   liukai:
   因此目前将其屏蔽, 理由有散:
   (1) 函数中使用g_pstApnByIndex,
   其数组中只有5个成员, 而使用时(g_pstApnByIndex[pstPppInfo->usCDBIndex]或者
   [pstPppInfo->usVirtualDomainIdx]), 这两个index的范围从[0..RM_MAX_APN_NUM-1]
   RM_MAX_APN_NUM被定为3000, 因此被静态检查查出越界了
   此问题经chenxianhua确认为, 移植代码时, 改出来的问题, 原核心网代码是使用
   动态申请的, 所以不应该有问题。这里出现问题, 实际上移植时, 没有弄清除数组大下,
   从而引入的
   (2) 同样VOS_MemCpy((CHAR *)pstMsg->ucPwd, pPacket, (VOS_UINT32 )pstMsg->ucPwdLen)
   也被检查出越界。因为ucPwd[18], 而ucPwdLen是与PPP_MAXUSERPWDLEN(128)比较,
   同样是移植代码时, 改出来的问题
   (3) 在手机端, 在PPP认证阶段, 充当的是peer角色
   peer是不应收到Authenticate-Request的, 即这段代码在手机端是使用不到的
*/
#if 0
/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：PAP收到验证请求包,分析当前状态并进行处理                    *
* MODIFY DATE  ：modified by gxf for GGSN80 20030220                        *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 pPacket:报文头位置                                            *
*                 ucId:报文ID                                                *
*                ulLen:报文数据长度                                            *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_PAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_PAP_ReceiveAuthReq(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, VOS_UINT32 ulLen)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;
    UCHAR ucPeerIdLen, ucPswLen;
    AAA_AUTHREQ_S *pstMsg;
    CHAR msg[256] = {0};

    LONG lLen = (LONG)ulLen;

    if (pstPapInfo == NULL)
    {
        return;
    }

    /* 提前给pap控制块中id赋值，否则重协商是pap response中 id为0 */
    pstPapInfo->ucPeerId = ucId;

    /* 输出事件调试信息 */
    PAP_Debug_Event(pstPppInfo, PAP_RECEIVEREQUEST);

    if ((pstPapInfo->ucServerState == PAP_STATE_SERVER_INITIAL)
        || (pstPapInfo->ucServerState == PAP_STATE_WAIT_AAA))
    {
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        PPP_DBG_ERR_CNT(PPP_PHERR_286);
        return;
    }

    /*当已经验证过再次收到验证请求，则以上次验证结果回复对方。*/
    if (pstPapInfo->ucServerState == PAP_STATE_SERVER_SUCCESS)
    {
         /*Modified by liushuang for DTS2012050403584. L2TP用户建立隧道时收到
           终端的Request消息，直接丢弃*/
        if ( ( 0 == pstPppInfo->bReNego )
                && (0 == pstPppInfo->bPppClient)
                 && (1 == pstPppInfo->bPppMode))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_287);
        }
        else
        {
            /*输出错误调试信息*/
            PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Receive request again!");
            PPP_PAP_SendResponse(pstPppInfo, PAP_AUTHACK, ucId, AuthMsgError, 0); /* return auth-ack */
            PPP_DBG_ERR_CNT(PPP_PHERR_288);
        }
        return;
    }

    if (pstPapInfo->ucServerState == PAP_STATE_SERVER_FAILED)
    {
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Receive request again!");
        PPP_PAP_SendResponse(pstPppInfo, PAP_AUTHNAK, ucId, AuthMsgError, 0); /* return auth-nak */
        PPP_DBG_ERR_CNT(PPP_PHERR_289);
        return;
    }

    if (pstPapInfo->pstAAAAuthReqMsg)
    {
        /* 若已经分配过内存, 直接使用 */
        pstMsg = pstPapInfo->pstAAAAuthReqMsg;
    }
    else
    {
        pstMsg = (AAA_AUTHREQ_S *)PPP_Malloc( sizeof(AAA_AUTHREQ_S));
        if (!pstMsg)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_290);
            PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Malloc error!");
            return;
        }

        pstPapInfo->pstAAAAuthReqMsg = pstMsg;
    }

    PPP_MemSet((void *)pstMsg, 0, sizeof(AAA_AUTHREQ_S));

    /* 分析用户名及密码    */
    PPP_GETCHAR(ucPeerIdLen, pPacket);
    lLen -= (LONG)(sizeof (UCHAR) + ucPeerIdLen + sizeof (UCHAR));
    if (lLen < 0)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_26);
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        PPP_PAP_SendResponse(pstPppInfo, (UCHAR)PAP_AUTHNAK, ucId, AuthMsgError, (VOS_UINT16)VOS_StrLen(AuthMsgError));

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_PAP_AAAAuthFailed(pstPapInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_291);
        return;
    }

    if ((ucPeerIdLen > A11_MAX_NAI_LENGTH) || (ucPeerIdLen == 0))
    {
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too long or NULL PeerId!");
        PPP_PAP_SendResponse(pstPppInfo, (UCHAR)PAP_AUTHNAK, ucId, AuthMsgError, (VOS_UINT16)VOS_StrLen(AuthMsgError));
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_27);

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_PAP_AAAAuthFailed(pstPapInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_292);
        return;
    }

    pstMsg->ucUsernameLen = ucPeerIdLen;

    (VOID)VOS_sprintf((char*)pstMsg->ucUsername, "%*.*s", pstMsg->ucUsernameLen, pstMsg->ucUsernameLen, pPacket);

    /*指针移到Passwd_Length位置*/
    PPP_INCPTR(ucPeerIdLen, pPacket);    /*指针移到Passwd_Length位置*/
    PPP_GETCHAR(ucPswLen, pPacket);
    if (lLen < ucPswLen)
    {
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_28);

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_DBG_ERR_CNT(PPP_PHERR_293);
        return;
    }

    if (ucPswLen > PPP_MAXUSERPWDLEN)
    {
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too long Password!");
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_29);

        /* BEGIN: Added for 问题单号:DTS2010101801457 by z00129699, 2010/10/18 */
        PPP_PAP_SendResponse(pstPppInfo, (UCHAR)PAP_AUTHNAK, ucId, AuthMsgError, (VOS_UINT16)VOS_StrLen(AuthMsgError));

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_PAP_AAAAuthFailed(pstPapInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_294);
        return;
    }

    /*删除等待Request 超时定时器*/
    if (pstPapInfo->ulServerTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));
        pstPapInfo->ulServerTimeoutID = 0;
    }

    if ((0 != pstPppInfo->ucNAI[0]) && 0 != VOS_StrCmp((CHAR*)(pstMsg->ucUsername), (CHAR*)(pstPppInfo->ucNAI)))
    {
        PPP_PAP_AAAAuthFailed(pstPapInfo);

        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_30);
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/

        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "NAI != username");
        PPP_DBG_ERR_CNT(PPP_PHERR_295);
        return;
    }

    PPPC_INFO_LOG2("\r\n PPP_PAP_ReceiveAuthReq:The domain index(%u)(%u)",
                 pstPppInfo->usCDBIndex,
                 pstPppInfo->usVirtualDomainIdx);
    if ((pstPppInfo->usCDBIndex >= RM_MAX_APN_NUM)
        && (pstPppInfo->usVirtualDomainIdx >= RM_MAX_APN_NUM))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_933);
        if (VOS_OK != PPP_GetDomainInfoByName(pstPppInfo, pstMsg->ucUsername))
        {
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
            /*End of liushuang*/
            PPP_PAP_AAAAuthFailed(pstPapInfo);
            PPP_DBG_ERR_CNT(PPP_PHERR_296);
            return;
        }
    }
#if 0
    A11_UpdateDomainIndexAtEntryState(pstPppInfo->ulRPIndex, pstPppInfo->usCDBIndex, VOS_FALSE);
#endif
    (VOID)VOS_sprintf((char*)pstPppInfo->ucNAI, "%s", pstMsg->ucUsername);

    /* 根据LOCK标志判断是否允许激活，如是被LOCK，则不允许它激活，返回协商失败 */
    if ((PPP_DOMAIN_LOCKED == g_pstApnByIndex[pstPppInfo->usCDBIndex].ucLock)
        || (PPP_DOMAIN_LOCKED == g_pstApnByIndex[pstPppInfo->usVirtualDomainIdx].ucLock))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_31);
        PPPC_INFO_LOG2("\r\n PPP_PAP_ReceiveAuthReq:The domain is locked, the domainindex is (%u)(%u)",
                 pstPppInfo->usCDBIndex,
                 pstPppInfo->usVirtualDomainIdx);
        PPP_PAP_AAAAuthFailed(pstPapInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_297);
        return;
    }

    PPP_PerfInc(&g_stPppPerfStatistic.ulPapTotal, PERF_TYPE_PPPC_PAP_AUTHEN_NUM, pstPppInfo->bEhrpdUser);

    if(VOS_TRUE == pstPppInfo->bAuthFlag)
    {
        PPPC_INFO_LOG2(
                            "\r\n [ppp]PPP_PAP_ReceiveAuthReq: pstPppInfo->bAuthFlag is %u PpcFlag %d",
                            pstPppInfo->bAuthFlag,
                            pstPppInfo->bPpcAAAFlag);


        /* 重协商不需要到AAA鉴权 */
        if (0 == pstPppInfo->bPpcAAAFlag)
        {
            (VOID)VOS_sprintf(msg, "Welcome to %s.", pstPppInfo->pstConfigInfo->cChapHostName);
            PPP_PAP_SendResponse(pstPppInfo, PAP_STATE_SERVER_SUCCESS, pstPapInfo->ucPeerId,
                                 msg, (VOS_UINT16 )VOS_StrLen(msg));
            /* 输出状态转换调试信息 */
            PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SERVER_SUCCESS, SERVER_STATE);
            pstPapInfo->ucServerState = PAP_STATE_SERVER_SUCCESS;

            PPP_PerfInc(&g_stPppPerfStatistic.ulPapSuccess, PERF_TYPE_PPPC_PAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);

            if (NULL != pstPapInfo->pstAAAAuthReqMsg)
            {
                PPP_Free( pstPapInfo->pstAAAAuthReqMsg);
                pstPapInfo->pstAAAAuthReqMsg = NULL;
                pstMsg = NULL;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_934);
            pstPppInfo->bAuthServer = VRP_NO;
            PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (VOS_UINT32)PPP_EVENT_PAPSUCCESS, NULL);

            return;
        }
    }


    /* 构造验证信息块stMsg */
    pstMsg->ulMsgType  = PPPC_AAA_CREAT_REQ;
    pstMsg->ulSDBIndex = pstPppInfo->ulRPIndex;
    pstMsg->usCDBIndex = pstPppInfo->usCDBIndex;
    pstMsg->ucPwdLen = ucPswLen;
    (VOID)VOS_MemCpy((CHAR *)pstMsg->ucPwd, pPacket, (VOS_UINT32 )pstMsg->ucPwdLen);
    pstMsg->ucPwd[pstMsg->ucPwdLen] = 0x0;
    /*pstMsg->usVPNID = pstPppInfo->usVPNID;*/
    pstMsg->ucPktID = ucId;
    pstMsg->stIMSI = pstPppInfo->stIMSI;

    /* add by g00127633 for 预付费重协商*/
    pstMsg->ucRenegoFlag = pstPppInfo->bPpcAAAFlag;

    (VOID)VOS_MemCpy((CHAR *)pstPapInfo->szPapUsrPwd, pPacket, (VOS_UINT32 )pstMsg->ucPwdLen);
    pstPapInfo->szPapUsrPwd[pstMsg->ucPwdLen] = 0x0;


    /* 输出状态转换调试信息 */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_WAIT_AAA, SERVER_STATE);
    pstPapInfo->ucServerState = PAP_STATE_WAIT_AAA;

#if (VRP_MODULE_SEC_L2TP == VRP_YES)
    /* 设置PPP 与 L2TP 通信数据 stOption 部分 */
    if (pstPppInfo->pL2tpPara != NULL)
    {
        L2TP_SESSIONPARA_S *pstOptionalPara = (L2TP_SESSIONPARA_S*)pstPppInfo->pL2tpPara;

        /* 设置验证类型 */
        pstOptionalPara->usAuthenType = L2TP_PPP_PAP;

        /* 设置请求验证用户名 */
        VOS_MemCpy(pstOptionalPara->szAuthenName,
                        pstMsg->ucUsername,
                        pstMsg->ucUsernameLen);
        pstOptionalPara->szAuthenName[pstMsg->ucUsernameLen] = 0x0;

        /* 设置用户密码 */
        VOS_MemCpy(pstOptionalPara->szResponse,
                        pstMsg->ucPwd,
                        pstMsg->ucPwdLen);
        pstOptionalPara->szResponse[pstMsg->ucPwdLen] = 0x0;
        pstOptionalPara->ulResponseLen = pstMsg->ucPwdLen;

        /* 设置验证包 ID */
        pstOptionalPara->usAuthenID = ucId;
    }
#endif

    /* 调用发送的函数或者直接在此处发送 */
    PPP_PAP_SendAAAAuthReq(pstPapInfo);
    PPP_DBG_OK_CNT(PPP_PHOK_935);
    return;
}
#endif



/*****************************************************************************
 函 数 名  : PPP_PAP_ReceiveAAAResult
 功能描述  : Pap模块收到AAA的鉴权消息
 输入参数  : AAA_AUTHRSP_S *pMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_PAP_ReceiveAAAResult(AAA_AUTHRSP_S *pMsg)
{
    PPPINFO_S *pstPppInfo;
    PPPPAPINFO_S * pstPapInfo;
    CHAR msg[256]   = {0};          /*魔鬼数字，要宏定义*/
    VOS_UINT16 usMsgLen = 0;

    PPPC_INFO_LOG("\r\n---PPP_PAP_ReceiveAAAResult---\r\n");

    /*判断输入参数的有效性*/
    if (NULL == pMsg)
    {
        PPPC_INFO_LOG("\r\n PPP_PAP_ReceiveAAAResult: Invalid input parameter!");
        return;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, pMsg->ulSDBIndex);
    if (pstPppInfo == NULL)
    {
        PPPC_INFO_LOG1("\r\n PPP_PAP_ReceiveAAAResult: User %d isn't exist!", pMsg->ulSDBIndex);
        return;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_936);
    pstPapInfo = pstPppInfo->pstPapInfo;
    if (pstPapInfo == NULL)
    {
        PPPC_INFO_LOG1("\r\n PPP_PAP_ReceiveAAAResult: User %d  papinfo isn't exist!",
                 pMsg->ulSDBIndex);
        return;
    }

    /* 删除定时器 */
    if (pstPapInfo->ulServerTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));
        pstPapInfo->ulServerTimeoutID = 0;
    }

    /* 释放AAA认证请求消息 */
    if (pstPapInfo->pstAAAAuthReqMsg)
    {
        PPP_Free(pstPapInfo->pstAAAAuthReqMsg);
        pstPapInfo->pstAAAAuthReqMsg = NULL;
    }

    /* 输出事件调试信息 */
    PAP_Debug_Event(pstPppInfo, PAP_AAARESULT);

    if (pstPapInfo->ucServerState != PAP_STATE_WAIT_AAA)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_298);

        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        return;
    }

    if (pMsg->ucResult == 0) /* AAA 验证通过 */
    {
        PPP_PerfInc(&g_stPppPerfStatistic.ulPapSuccess, PERF_TYPE_PPPC_PAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);

        PPP_DBG_OK_CNT(PPP_PHOK_937);
        (VOID)VOS_sprintf(msg, "Welcome to %s.", pstPppInfo->pstConfigInfo->cChapHostName);
        PPP_PAP_SendResponse(pstPppInfo, PAP_STATE_SERVER_SUCCESS, pstPapInfo->ucPeerId,
                             msg, (VOS_UINT16 )VOS_StrLen( msg ));

        /* 输出状态转换调试信息 */
        PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SERVER_SUCCESS, SERVER_STATE);
        pstPapInfo->ucServerState = PAP_STATE_SERVER_SUCCESS;

        /*向内核报Server端 PAP 验证成功 */
        pstPppInfo->bAuthServer = VRP_NO;
        PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (VOS_UINT32)PPP_EVENT_PAPSUCCESS, (CHAR*)pMsg);
    }

    else        /* AAA验证未过 */
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_299);
        if (pMsg->ucReplyMsg[0] == 0)
        {
            PPP_PAP_SendResponse(pstPppInfo, PAP_STATE_SERVER_FAILED, pstPapInfo->ucPeerId,
                                 "Authenticate failed.",
                                 sizeof("Authenticate failed."));
        }
        else
        {
            usMsgLen = (VOS_UINT16)VOS_StrLen((CHAR *)(pMsg->ucReplyMsg));
            PPP_PAP_SendResponse(pstPppInfo, PAP_STATE_SERVER_FAILED, pstPapInfo->ucPeerId,
                                 (CHAR *)(pMsg->ucReplyMsg), usMsgLen);
        }

        /* 输出状态转换调试信息 */
        PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SERVER_FAILED, SERVER_STATE);
        pstPapInfo->ucServerState = PAP_STATE_SERVER_FAILED;

        /*删除定时器 */
        PPP_PAP_DeleteTimer(pstPppInfo);

        /*向内核报Server端PAP验证失败*/
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_NAK);
        PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (VOS_UINT32)PPP_EVENT_PAPFAILED, NULL);
        A11_PPP_TermTag(pstPppInfo->ulRPIndex, Authentication_Fail);
    }
    PPP_DBG_OK_CNT(PPP_PHOK_938);
    PPPC_INFO_LOG("\r\nPPP_PAP_ReceiveAAAResult Done !");
    return;
}



/*****************************************************************************
 函 数 名  : PPP_PAP_SendAAAAuthReq
 功能描述  : 向AAA发送鉴权请求
 输入参数  : AAA_AUTHREQ_S *pstMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年2月21日
    作    者   : gxf
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_PAP_SendAAAAuthReq(PPPPAPINFO_S *pstPapInfo)
{
#if 0
    AAA_AUTHREQ_S *pstMsg;
    VOS_UINT32 ulRet;
    PPPINFO_S *pstPppInfo;
    PPP_DBG_OK_CNT(PPP_PHOK_939);

    PPP_TRACE("\r\n---Into PPP_PAP_SendAAAAuthReq---\r\n");
    if (NULL == pstPapInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_300);
        VOS_DBGASSERT(0);
        PPPC_INFO_LOG(MID_PPPC, PPP_DEBUG_INFO, "PPP_PAP_SendAAAAuthReq: pstPapInfo=NULL");
        return;
    }

    pstMsg = pstPapInfo->pstAAAAuthReqMsg;
    if (NULL == pstMsg)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_301);
        VOS_DBGASSERT(0);
        PPPC_INFO_LOG(MID_PPPC, PPP_DEBUG_INFO, "PPP_PAP_SendAAAAuthReq: pstMsg=NULL");
        return;
    }

    pstPppInfo = pstPapInfo->pstPppInfo;
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_302);
        VOS_DBGASSERT(0);
        PPPC_INFO_LOG(MID_PPPC, PPP_DEBUG_INFO, "PPP_PAP_SendAAAAuthReq: pstPppInfo=NULL");
        return;
    }


    /* 用于控制是否将NAI转换成小写软参 */
    if (1 == M_SPM_USER_NAME_LOWERCASE)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_940);
        VOS_lowercase((CHAR*)(((AAA_AUTHREQ_S*)pstMsg)->ucUsername));
    }

    pstMsg->ulMsgType  = PPPC_AAA_CREAT_REQ;
    pstMsg->ulSDBIndex = pstPppInfo->ulRPIndex;

    ((AAA_AUTHREQ_S*)pstMsg)->ucPPPFlag =1;
    ulRet = PPP_SendRtMsg(PPP_SELF_CSI,
                         g_ullPppAuthCsi,
                         AUTH_MSG_TYPE_PPP,
                         PPP_AUTH_FLAG,
                         (UCHAR *)pstMsg,
                         sizeof( AAA_AUTHREQ_S ));
    if ( VOS_OK != ulRet )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_303);
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_PAP_SendAAAAuthReq: PPP_SendRtMsg Err!!");
        return;
    }


    /* 设置超时定时器 */
    VOS_DBGASSERT(pstPapInfo->ulServerTimeoutID == 0);
    ulRet = PGP_Timer_Create(PPP_SELF_CSI,
                             PPP_MSG_TYPE_TIMER,
                             pstPapInfo->ulWaitAuthRspTimeout,
                             PPP_PAP_AuthRspTimeout,
                             (VOID*)pstPppInfo->ulRPIndex,
                             &(pstPapInfo->ulServerTimeoutID),
                             VOS_TIMER_LOOP);
    if (ulRet != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_304);
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "PGP_Timer_Create error!");
    }

    ++pstPapInfo->ucAuthTransmits;
    PPP_DBG_OK_CNT(PPP_PHOK_941);
#endif
    return ;
}



/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：PAP收到对端ACK,进行处理                                    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 pPacket:报文头位置                                            *
*                 ucId:报文ID                                                *
*                ulLen:报文数据长度                                            *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_PAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_PAP_ReceiveAuthAck(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, VOS_UINT32 ulLen)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;
    CTTF_PPPC_AUTH_INFO_STRU   stPppAuthInfo;

    UCHAR ucMsgLen;

    /*CHAR *stMsg ;*/

    if (pstPapInfo == NULL)
    {
        return;
    }

    /* 输出事件调试信息 */
    PAP_Debug_Event(pstPppInfo, PAP_RECEIVEACK);

    if (pstPapInfo->ucClientState != PAP_STATE_SEND_AUTHREQ) /* 非法事件 */
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_305);
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        return;
    }

    /* 分析 Message */
    if (ulLen < sizeof (UCHAR))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_306);
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        return;
    }

    PPP_GETCHAR(ucMsgLen, pPacket); /*取得 ACK 报文的Message 长度 */
    if (ulLen < ucMsgLen)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_307);
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        return;
    }

    /*删除定时器*/
    if (pstPapInfo->ulClientTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulClientTimeoutID));
        pstPapInfo->ulClientTimeoutID = 0;
    }

    /*stMsg = (CHAR *) pPacket ;*/    /*取得 ACK 报文的Message 内容 */

    /* 输出状态转换调试信息 */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_CLIENT_SUCCESS, CLIENT_STATE);
    pstPapInfo->ucClientState = PAP_STATE_CLIENT_SUCCESS;

    PPPC_GetPppAuthInfo(&stPppAuthInfo);
    PPPC_MntnTraceAuthResult((VOS_UINT8)(pstPppInfo->ulRPIndex),
                PPP_PAP, VOS_OK, &stPppAuthInfo);

    /*向内核报 Client 端PAP 验证成功 */
    pstPppInfo->bAuthClient = VRP_NO;
    PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (VOS_UINT32)PPP_EVENT_PAPSUCCESS, NULL);

    (VOS_VOID)pPacket;
    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：PAP收到对端NAK,进行处理                                    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 pPacket:报文头位置                                            *
*                 ucId:报文ID                                                *
*                ulLen:报文数据长度                                            *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_PAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_PAP_ReceiveAuthNak(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, VOS_UINT32 ulLen)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;
    CTTF_PPPC_AUTH_INFO_STRU   stPppAuthInfo;
    UCHAR ucMsgLen;

    /*CHAR *stMsg ;*/
    CHAR cErrstr[100];

    if (pstPapInfo == NULL)
    {
        return;
    }

    /*上报OM可维可测信息*/
    g_stPppcStatRpt.stPppcStatisticInfo.ulNameOrPwdAuthFailCnt++;
    PPP_MNTN_CMO_SendOmResourceStateInfo();

    /* 输出事件调试信息 */
    PAP_Debug_Event(pstPppInfo, PAP_RECEIVENAK);

    if (pstPapInfo->ucClientState != PAP_STATE_SEND_AUTHREQ) /* 异常事件 */
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_308);
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        return;
    }

    /*分析 Message*/
    if (ulLen < sizeof (UCHAR))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_309);
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        return;
    }

    PPP_GETCHAR(ucMsgLen, pPacket); /*取得 NAK 报文的Message 长度 */
    if (ulLen < ucMsgLen)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_310);
        /*输出错误调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        return;
    }

    /* 删除定时器 */
    if (pstPapInfo->ulClientTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulClientTimeoutID));
        pstPapInfo->ulClientTimeoutID = 0;
    }

    /*stMsg = (CHAR *) pPacket ;*/
    /* 输出状态转换调试信息 */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_CLIENT_FAILED, CLIENT_STATE);
    pstPapInfo->ucClientState = PAP_STATE_CLIENT_FAILED;

    /*Client验证失败次数加一*/
    pstPapInfo->usAuthClientFailureTimes += 1;

    /*输出错误调试信息*/
    (VOID)VOS_sprintf(cErrstr, "Client failed No. %2d !",
                      pstPapInfo->usAuthClientFailureTimes );
    PAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, cErrstr);

    /* 电信规范要求业务协商时PAP鉴权失败需要发送Lcp Terminate Req进行PPP断链 */
    PPP_DBG_ERR_CNT(PPP_PHERR_311);
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_PAPFAILED, NULL);

#if 0
    if (pstPapInfo->usAuthClientFailureTimes >= PPP_MAXAUTHFAILTIMES)
    {
        PPPC_GetPppAuthInfo(&stPppAuthInfo);
        PPPC_MntnTraceAuthResult((VOS_UINT8)(pstPppInfo->ulRPIndex), PPP_PAP,
                    VOS_ERR, &stPppAuthInfo);

        PPP_DBG_ERR_CNT(PPP_PHERR_311);
        /*超过相对端申请验证次数,向内核报PAP 验证失败 */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (VOS_UINT32)PPP_EVENT_PAPFAILED, NULL);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_942);
        /*否则,再次相对端请求验证 */
        PPP_PAP_SendAuthReq(pstPppInfo);
    }
#endif
    (VOS_VOID)pPacket;
    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：PAP向对端发出验证请求                                        *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_PAP_ClientLowerUp,PPP_PAP_SendAuthReqTimeout,            *
*                 PPP_PAP_ReceiveAuthNak                                        *
****************************************************************************/
VOID PPP_PAP_SendAuthReq(PPPINFO_S *pstPppInfo)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;
    UCHAR *pHead, *pPacket;
    VOS_UINT32 ulLen = 0;
    VOS_UINT32 ulOffset;
    UCHAR tmplen;
    VOS_UINT32 ulErrorCode;

    if (pstPapInfo == NULL)
    {
        return;
    }

    /* 预留出打PPP报文头的空间 */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* 申请内存 */
    pHead = g_ucPppSendPacketHead;

    pPacket = pHead + ulOffset;
    ulLen = PAP_HEADERLEN + 2 + VOS_StrLen((CHAR*)pstPapInfo->szPapUsrName)
            + VOS_StrLen((CHAR*)pstPapInfo->szPapUsrPwd);

    PPP_PUTCHAR(PAP_AUTHREQ, pPacket);            /*PAP CODE */
    PPP_PUTCHAR(++pstPapInfo->ucId, pPacket);    /*PAP ID */
    PPP_PUTSHORT((VOS_UINT16)ulLen, pPacket);                /*PAP LENGTH*/

    /* 写Peer_Id Length 和 Peer_Id*/
    tmplen = (UCHAR )VOS_StrLen((CHAR*) pstPapInfo->szPapUsrName);
    PPP_PUTCHAR(tmplen, pPacket );
    (VOID)VOS_MemCpy((CHAR *)pPacket,
                       (pstPapInfo->szPapUsrName),
                       (VOS_UINT32)tmplen );

    PPP_INCPTR(tmplen, pPacket);

    /*写 Passwd_Length 和Password */
    tmplen = (UCHAR )VOS_StrLen((CHAR*) pstPapInfo->szPapUsrPwd);
    PPP_PUTCHAR( tmplen, pPacket );
    (VOID)VOS_MemCpy((CHAR *)pPacket,
                       (pstPapInfo->szPapUsrPwd),
                       (VOS_UINT32)tmplen);
    PPP_INCPTR(tmplen, pPacket);

    pPacket -= ulLen;

    /*输出报文调试信息*/
    PAP_Debug_Packet(pstPppInfo, pPacket, ulLen, PPP_PAP, 0);

    /* 直接调用外壳的发送函数 */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo, pHead, pPacket, ulLen, PPP_PAP);
    if (ulErrorCode != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_313);
        /*输出调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_ERROR, "Send Packet Failed!");
    }

    if (pstPapInfo->ulClientTimeoutID == 0)
    {
        /*设置等待验证超时定时器*/
        (VOS_VOID)VOS_StartRelTimer((HTIMER *)&(pstPapInfo->ulClientTimeoutID),
                                    MID_PPPC,
                                    pstPapInfo->ulSendReqTimeout,
                                    pstPppInfo->ulRPIndex,
                                    PPPC_PAP_SEND_AUTH_REQ_TIMER,
                                    VOS_TIMER_LOOP,
                                    VOS_TIMER_PRECISION_0);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_314);
    }

    ++pstPapInfo->ucTransmits;

    /* 输出状态转换调试信息 */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SEND_AUTHREQ, CLIENT_STATE);
    pstPapInfo->ucClientState = PAP_STATE_SEND_AUTHREQ;

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：PAP向对端发出响应(ACK或NAK)                                *
* MODIFY DATE  ：                                                            *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 ucCode: 验证成功/失败报文code                                *
*                 stMsg: 回传信息                                                *
*                 ucMsgLen: 信息长度                                            *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_PAP_ClientLowerUp,PPP_PAP_SendAuthReqTimeout,            *
*                 PPP_PAP_ReceiveAuthNak                                        *
****************************************************************************/
VOID PPP_PAP_SendResponse(PPPINFO_S * pstPppInfo, UCHAR ucCode, UCHAR ucId, char *stMsg, VOS_UINT16 usMsgLen)
{
    PPPPAPINFO_S *pstPapInfo;
    UCHAR *pHead, *pPacket;
    VOS_UINT32 ulLen = 0;
    VOS_UINT32 ulOffset;
    VOS_UINT32 ulErrorCode;

    PPPC_INFO_LOG("\r\n---Into PPP_PAP_SendResponse---\r\n");

    if (pstPppInfo == NULL)
    {
        return;
    }

    pstPapInfo = pstPppInfo->pstPapInfo;
    if (pstPapInfo == NULL)
    {
        return;
    }

    /* 预留出打PPP报文头的空间 */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* 申请内存 */
    pHead = g_ucPppSendPacketHead;

    pPacket = pHead + ulOffset;
    ulLen = (VOS_UINT16 )(PAP_HEADERLEN + 1 + usMsgLen);

    PPP_PUTCHAR(ucCode, pPacket);            /*PAP CODE */
    PPP_PUTCHAR(ucId, pPacket);            /*PAP ID */
    PPP_PUTSHORT((VOS_UINT16)ulLen, pPacket);            /*PAP LENGTH*/

    /* 写Message Length 和 Message */
    PPP_PUTCHAR(usMsgLen, pPacket);
    (VOID)VOS_MemCpy((CHAR * )pPacket, stMsg, (VOS_UINT32)usMsgLen);
    PPP_INCPTR(usMsgLen, pPacket);

    pPacket -= ulLen;

    /*输出报文调试信息*/
    PAP_Debug_Packet(pstPppInfo, pPacket, ulLen, PPP_PAP, 0);

    /* 直接调用外壳的发送函数 */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo, pHead, pPacket, ulLen, PPP_PAP);
    if (ulErrorCode != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_316);
        /*输出调试信息*/
        PAP_Debug_Error(pstPppInfo, PPP_LOG_ERROR, "Send Packet Failed!");
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：Server端等待对端发送验证请求超时,向内核报PAP验证失败       *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：由ulServerTimeoutID触发                                    *
****************************************************************************/
VOS_VOID PPP_PAP_WaitReqTimeout(VOS_UINT32 ulPppId)
{
    PPPINFO_S *pstPppInfo;
    PPPPAPINFO_S *pstPapInfo;
    PPP_DBG_OK_CNT(PPP_PHOK_943);

    GETPPPINFOPTRBYRP(pstPppInfo, ulPppId);
    if (pstPppInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_317);
        return;
    }

    pstPapInfo = pstPppInfo->pstPapInfo;
    if (pstPapInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_318);
        return;
    }

    /* 输出事件调试信息 */
    PAP_Debug_Event(pstPppInfo, PAP_WAITREQTIMEOUT);

    /* 清除定时器 */
    (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));
    pstPapInfo->ulServerTimeoutID = 0;
    if (pstPapInfo->ucServerState != PAP_STATE_SERVER_LISTEN)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_319);
        return;
    }

    /* 输出状态转换调试信息 */
    PAP_Debug_StateChange(pstPppInfo, PAP_STATE_SERVER_FAILED, SERVER_STATE);
    pstPapInfo->ucServerState = PAP_STATE_SERVER_FAILED;
    SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_MS_NO_RSP);


    PPP_PAP_DeleteTimer(pstPppInfo);    /*删除定时器 */
    PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_PAP_REQTIMEOUT);
    PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (VOS_UINT32)PPP_EVENT_PAPFAILED, NULL);


    A11_ReqNumSubProc(pstPppInfo);
    PPP_DBG_ERR_CNT(PPP_PHERR_320);


    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：PAP Client端等待验证结果超时                                *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：由ulClientTimeoutID定时器触发                                *
****************************************************************************/
VOS_VOID PPP_PAP_SendAuthReqTimeout(VOS_UINT32 ulPppId)
{
    PPPINFO_S *pstPppInfo;
    PPPPAPINFO_S *pstPapInfo;

    PPP_DBG_OK_CNT(PPP_PHOK_944);

    GETPPPINFOPTRBYRP(pstPppInfo, ulPppId);
    if (pstPppInfo == 0L)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_322);
        return;
    }

    pstPapInfo = pstPppInfo->pstPapInfo;
    if (pstPapInfo == 0L)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_323);
        return;
    }

    /* 清除定时器 */
    (VOID)VOS_StopRelTimer(&(pstPapInfo->ulClientTimeoutID));
    pstPapInfo->ulClientTimeoutID = 0;

    /* 输出事件调试信息 */
    PAP_Debug_Event(pstPppInfo, PAP_REQUESTTIMEOUT);

    if (pstPapInfo->ucClientState != PAP_STATE_SEND_AUTHREQ)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_324);
        return;
    }

    if (pstPapInfo->ucTransmits >= pstPapInfo->ulMaxTransmits)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_325);
        /* 输出状态转换调试信息 */
        PAP_Debug_StateChange(pstPppInfo, PAP_STATE_CLIENT_FAILED, CLIENT_STATE);
        pstPapInfo->ucClientState = PAP_STATE_CLIENT_FAILED;

        PPP_PAP_DeleteTimer(pstPppInfo);    /*删除定时器 */
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_PAP_SEND_REQTIMEOUT);
        PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (VOS_UINT32)PPP_EVENT_PAPFAILED, NULL);
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_945);

    PPP_PAP_SendAuthReq(pstPppInfo);        /* Send Authenticate-Request */

    return;
}

/*****************************************************************************
 函 数 名  : PPP_PAP_AuthRspTimeout
 功能描述  : PAP Server端等待AAA验证结果超时
 输入参数  : VOID *pPppInfo
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年2月21日
    作    者   : gxf
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_PAP_AuthRspTimeout(VOID *ulIndex)
{
    PPPINFO_S *pstPppInfo = NULL;
    PPPPAPINFO_S *pstPapInfo = NULL;
    AAA_AUTHREQ_S *pstAuthMsg = NULL;
    VOS_UINT32 ulIdxTmp = (VOS_UINT32)ulIndex;

    PPPC_INFO_LOG("\r\n---Into PPP_PAP_AuthRspTimeout---\r\n");
    PPP_DBG_OK_CNT(PPP_PHOK_946);

    GETPPPINFOPTRBYRP(pstPppInfo, (VOS_UINT32)ulIndex);
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_326);
        PPPC_INFO_LOG1("PPP_PAP_AuthRspTimeout: ulIdxTmp(%d)pstPppInfo=NULL", ulIdxTmp);
        return;
    }

    pstPapInfo = (PPPPAPINFO_S *)pstPppInfo->pstPapInfo;
    if (NULL == pstPapInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_327);
        PPPC_INFO_LOG1("PPP_PAP_AuthRspTimeout: ulIdxTmp(%d)pstPapInfo=NULL", ulIdxTmp);
        return;
    }

    pstAuthMsg = pstPapInfo->pstAAAAuthReqMsg;
    if (NULL == pstAuthMsg)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_328);
        PPPC_INFO_LOG1("PPP_PAP_AuthRspTimeout: ulIdxTmp(%d)pstAuthMsg=NULL", ulIdxTmp);
        return;
    }

    pstPppInfo = pstPapInfo->pstPppInfo;
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_329);
        PPPC_INFO_LOG1("PPP_PAP_AuthRspTimeout: ulIdxTmp(%d)pstPapInfo->pstPppInfo=NULL", ulIdxTmp);
        return;
    }

    if(pstPapInfo->ucServerState != PAP_STATE_WAIT_AAA)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_330);
        PPPC_INFO_LOG2("PPP_PAP_AuthRspTimeout: ulIdxTmp(%d)pstPapInfo->ucServerState(%d)",
                         ulIdxTmp, pstPapInfo->ucServerState);
        return;
    }

    /* 输出事件调试信息 */
    PAP_Debug_Event(pstPppInfo, PAP_WAITAAARSPTIMEOUT);

    /* 清除定时器 */
    (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));
    pstPapInfo->ulServerTimeoutID = 0;

    if (pstPapInfo->ucAuthTransmits >= pstPapInfo->ulAuthMaxTransmits)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_32);
        PPP_DBG_ERR_CNT(PPP_PHERR_331);
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_AAA_NO_RSP);
        /*End of liushuang*/
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_PAP_AAATIMEOUT);
        PPP_PAP_AAAAuthFailed(pstPapInfo);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_947);
        PPP_PAP_SendAAAAuthReq(pstPapInfo);
    }

    (VOS_VOID)ulIdxTmp;
    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
