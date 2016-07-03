

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_CHAP_DBG_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

CHAR *cChap_Debug_Code[] =
{
    "Reserved",      /* 0 */
    "Challenge",    /* 1 */
    "Response",      /* 2 */
    "SUCCESS",      /* 3 */
    "FAILURE"      /* 4 */
};

CHAR *cChap_Server_State[] =
{
    "Initial",
    "SendChallenge",
    "  ",
    "ServerSuccess",
    "ServerFailed",
    "WaittingAAA"
};
CHAR *cChap_Client_State[] =
{
    "Initial",
    "ListenChallenge",
    "SendResponse",
    "ClientSuccess",
    "ClientFailed",
    " "
};

CHAR *cChap_Debug_Event[] =
{
    "Server Lower Up ",     /* 0 */
    "Client Lower Up",  /* 1 */
    "Lower Down ",      /* 2 */
    "Receive Challenge",    /* 3 */
    "Receive Response",     /* 4 */
    "Receive Success",  /* 5 */
    "Receive Failure",  /* 6 */
    "Response TimeOut",     /* 7 */
    "Challenge TimeOut",    /* 8 */
    "Initial",          /* 9 */
    "Challenge Again",  /* 10 */
    "Code Reject",      /* 11 */
    "AAA Result",           /* 12 */
    "AAA Response TimeOut",   /* 13 */
    "Error Event"           /* 14 */
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*lint -e813*/

VOID CHAP_Debug_Packet(PPPINFO_S* pstPppInfo,
                       UCHAR *    pPacket,
                       VOS_UINT32      ulLen,
                       VOS_UINT16     usProtocol,
                       UCHAR      ucIsInPacket)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;

    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;
    VOS_UINT32 ulTotalLen = ulLen + CHAP_HEADERLEN;
    UCHAR ucCode, ucId;
    VOS_UINT16 sFrameLen;
    LONG lLen = (LONG)ulLen;
    UCHAR ucSize;
    UCHAR ucLoopI;
    LONG lBufLen = 0;

    szDebugBuf[0] = '\0';

    /* 根据IMSI输出调试信息 */
    DEBUGBYIMSI();

    if (pstPppInfo->stPppDebugInfo.bDebug_Chap_Packet == VRP_NO)
    {
        /*DEBUG 开关未打开,返回*/
        return;
    }

    /* chap 报文情况 */

    /*
     |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  ff   |  03   |    c223       |  code |  ID   |    frame len  |   ...     |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |------------- lLen / sFrameLen ------------|
                                    pPacket
     |-----------------------------  ulTotalLen    --------------------------------|
     */

    /*VOS_DBGASSERT(pstPppInfo ) ; */
    /*VOS_DBGASSERT(pPacket ) ;  */

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Packet: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s %s(%04x) Pkt, Len %lu ",
                        PPP_Debug_GetInterfaceName(pstPppInfo),
                        (ucIsInPacket == 1) ? "Input " : "Output",
                        PPP_Debug_GetProtocolName(usProtocol),
                        usProtocol,
                        ulTotalLen
            );

    /* 合法性检查 */
    if (lLen < 4)
    {
        pBuf += VOS_sprintf(pBuf, "\r\n Value: %s ",
                            PPP_Debug_GetValueStr(pPacket, (UCHAR)lLen)
                );
        pBuf += VOS_sprintf(pBuf, "\r\n Error: packet too short, discard.");
        lBufLen = pBuf - szDebugBuf;
        PPP_DebugOutString(szDebugBuf, lBufLen, pstPppInfo);

        return;
    }

    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(ucId, pPacket);
    PPP_GETSHORT(sFrameLen, pPacket);

    /* 显示当前状态,Code,id以及长度 */
    if (((ucIsInPacket == 1) && (ucCode == CHAP_PACKET_CODE_RESPONSE))
        || ((ucIsInPacket != 1) && (ucCode == CHAP_PACKET_CODE_CHALLENGE))
        || ((ucIsInPacket != 1) && (ucCode == CHAP_PACKET_CODE_SUCCESS))
        || ((ucIsInPacket != 1) && (ucCode == CHAP_PACKET_CODE_FAILURE)))
    {
        pBuf += VOS_sprintf(pBuf, "\r\n      State %s, code %s(%02x), id %x, len %d ",
                            cChap_Server_State[pstChapInfo->ucServerState],
                            cChap_Debug_Code[ucCode],
                            ucCode,
                            ucId,
                            sFrameLen
                );
    }
    else if (((ucIsInPacket != 1) && (ucCode == CHAP_PACKET_CODE_RESPONSE))
             || ((ucIsInPacket == 1) && (ucCode == CHAP_PACKET_CODE_CHALLENGE))
             || ((ucIsInPacket == 1) && (ucCode == CHAP_PACKET_CODE_SUCCESS))
             || ((ucIsInPacket == 1) && (ucCode == CHAP_PACKET_CODE_FAILURE)))
    {
        pBuf += VOS_sprintf(pBuf, "\r\n      State %s, code %s(%02x), id %x, len %d ",
                            cChap_Client_State[pstChapInfo->ucClientState],
                            cChap_Debug_Code[ucCode],
                            ucCode,
                            ucId,
                            sFrameLen
                );
    }

    /* pBuf += VOS_sprintf(pBuf, "\r\n      State %s, code %s(%02x), id %x, len %d ",
         (pstConfig->bAuthRmtChap)?
         cChap_Server_State[pstChapInfo->ucServerState]:cChap_Client_State[pstChapInfo->ucClientState],
         cChap_Debug_Code[ucCode],
         ucCode,
         ucId,
         sFrameLen
         );*/

    lLen -= 4;

    /* 报文情况 */

    /*
    -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     ...   |  code |  ID   |    frame len  |          ...          |
    -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |-------- lLen ---------|
     |------ sFrameLen ------|
                                           pPacket
     */
    switch (ucCode)
    {
        case CHAP_PACKET_CODE_CHALLENGE:
        case CHAP_PACKET_CODE_RESPONSE:
            PPP_GETCHAR(ucSize, pPacket);

            /*显示Value_Size */
            pBuf += VOS_sprintf(pBuf, "\r\n      Value_Size: %3d ", ucSize);

            /*显示Value */
            pBuf += VOS_sprintf(pBuf, " Value: ");
            for (ucLoopI = 0; ucLoopI < ucSize; ucLoopI++)
            {
                pBuf += VOS_sprintf(pBuf, "%2x ", *pPacket);
                PPP_INCPTR(1, pPacket);
            }

            lLen = lLen - (LONG)ucSize - 1;  /*Name 域长度*/
            /* 显示Name */
            pBuf += VOS_sprintf(pBuf, "\r\n      Name: %s",
                                PPP_Debug_GetString(pPacket, (UCHAR )lLen));
            break;

        case CHAP_PACKET_CODE_SUCCESS:
        case CHAP_PACKET_CODE_FAILURE:

            /* 显示Message */
            pBuf += VOS_sprintf(pBuf, "\r\n      Message: %s ",
                                PPP_Debug_GetString(pPacket, (UCHAR )lLen ));
            break;
        default:
            pBuf += VOS_sprintf(pBuf, "\r\n      UnKnown Code ");
            break;
    }

    lBufLen = pBuf - szDebugBuf;
    PPP_DebugOutString(szDebugBuf, lBufLen, pstPppInfo);

    return;
}


VOID CHAP_Debug_StateChange(PPPINFO_S *pstPppInfo, UCHAR ucNewState, UCHAR ucType)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;
    CHAR cState[20], cNewState[20];
    LONG lBufLen = 0;

    szDebugBuf[0] = '\0';
    cState[0] = 0;
    cNewState[0] = 0;

    /* 根据IMSI输出调试信息 */
    DEBUGBYIMSI();

    if (pstPppInfo->stPppDebugInfo.bDebug_Chap_StateChange == VRP_NO)
    {
        /*DEBUG 开关未打开,返回*/
        return;
    }

    if (ucType == CHAP_CLIENT_STATE)
    {
        /* Client 状态转换 */
        if (pstChapInfo->ucClientState == ucNewState)
        {
            return;
        }
        else
        {
            if (pstChapInfo->ucClientState > CHAP_STATE_WAITING_AAA)
            {
                /* 错误的状态 */
                (VOID)VOS_sprintf(cState, "%s", "Error-State");
            }
            else
            {
                (VOID)VOS_sprintf(cState, "%s", cChap_Client_State[pstChapInfo->ucClientState]);
            }

            if (ucNewState >= CHAP_STATE_WAITING_AAA)
            {
                /* 错误的状态 */
                (VOID)VOS_sprintf(cNewState, "%s", "Error-State");
            }
            else
            {
                (VOID)VOS_sprintf(cNewState, "%s", cChap_Client_State[ucNewState]);
            }

            pBuf += VOS_sprintf(pBuf, "\r\n  PPP State Change: ");
            pBuf += VOS_sprintf(pBuf, "\r\n      %s %s : %s --> %s ",
                                PPP_Debug_GetInterfaceName(pstPppInfo),
                                PPP_Debug_GetProtocolName(PPP_CHAP),
                                cState,
                                cNewState);
        }
    }
    else
    {
        /* Server 状态转换 */
        if (pstChapInfo->ucServerState == ucNewState)
        {
            return;
        }
        else
        {
            if (pstChapInfo->ucServerState > CHAP_STATE_WAITING_AAA)
            {
                /* 错误的状态 */
                (VOID)VOS_sprintf(cState, "%s", "Error-State");
            }
            else
            {
                (VOID)VOS_sprintf(cState, "%s", cChap_Server_State[pstChapInfo->ucServerState]);
            }

            if (ucNewState > CHAP_STATE_WAITING_AAA)
            {
                /* 错误的状态 */
                (VOID)VOS_sprintf(cNewState, "%s", "Error-State");
            }
            else
            {
                (VOID)VOS_sprintf(cNewState, "%s", cChap_Server_State[ucNewState]);
            }

            pBuf += VOS_sprintf(pBuf, "\r\n  PPP State Change: ");
            pBuf += VOS_sprintf(pBuf, "\r\n      %s %s : %s --> %s ",
                                PPP_Debug_GetInterfaceName(pstPppInfo),
                                PPP_Debug_GetProtocolName(PPP_CHAP),
                                cState,
                                cNewState);
        }
    }

    lBufLen = pBuf - szDebugBuf;
    PPP_DebugOutString(szDebugBuf, lBufLen, pstPppInfo);

    return;
}


VOID CHAP_Debug_Event(PPPINFO_S* pstPppInfo, UCHAR ucEvent)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    PPPCONFIGINFO_S *pstConfig = pstPppInfo->pstConfigInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;
    CHAR cClientState[20], cServerState[20], cEvent[100];
    LONG lBufLen = 0;
    szDebugBuf[0]   = 0;
    cClientState[0] = 0;
    cServerState[0] = 0;
    cEvent[0] = 0;

    /* 根据IMSI输出调试信息 */
    DEBUGBYIMSI();

    if (pstPppInfo->stPppDebugInfo.bDebug_Chap_Event == VRP_NO)
    {
        /*DEBUG 开关未打开,返回*/
        return;
    }

    /* 取得 Client 状态 */
    if (pstChapInfo->ucClientState > CHAP_STATE_WAITING_AAA)
    {
        /* 错误的状态 */
        (VOID)VOS_sprintf(cClientState, "%s", "Error-State");
    }
    else
    {
        (VOID)VOS_sprintf(cClientState, "%s", cChap_Client_State[pstChapInfo->ucClientState]);
    }

    /* 取得 Server 状态 */
    if (pstChapInfo->ucServerState > CHAP_STATE_WAITING_AAA)
    {
        /* 错误的状态 */
        (VOID)VOS_sprintf(cServerState, "%s", "Error-State");
    }
    else
    {
        (VOID)VOS_sprintf(cServerState, "%s", cChap_Server_State[pstChapInfo->ucServerState]);
    }

    if (ucEvent >= CHAP_ERROREVENT)
    {
        /* 错误的事件 */
        (VOID)VOS_sprintf(cEvent, "%s", "Error-Event");
    }
    else
    {
        (VOID)VOS_sprintf(cEvent, "%s", cChap_Debug_Event[ucEvent]);
    }

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Event: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s %s Event ",
                        PPP_Debug_GetInterfaceName(pstPppInfo),
                        PPP_Debug_GetProtocolName(PPP_CHAP),
                        cEvent);

    switch (ucEvent)
    {
        case CHAP_INITIALIZATION:
        case CHAP_LOWERDOWN:
        case CHAP_CODEREJECT:
            pBuf += VOS_sprintf(pBuf, "\r\n      state %s ",
                                (pstConfig->bAuthRmtChap) ? cServerState : cClientState);
            break;

        case CHAP_CLIENTLOWERUP:
        case CHAP_AUTHSUCCESS:
        case CHAP_AUTHFAILURE:
        case CHAP_RESPONSETIMEOUT:
        case CHAP_RECEIVECHALLENGE:
            pBuf += VOS_sprintf(pBuf, "\r\n      state %s ", cClientState);
            break;

        case CHAP_CHALLENGETIMEOUT:
        case CHAP_RECHANLLENGE:
        case CHAP_SERVERLOWERUP:
        case CHAP_AAARESULT:
        case CHAP_RECEIVERESPONSE:
            pBuf += VOS_sprintf(pBuf, "\r\n      state %s ", cServerState);
            break;

        default:
            break;
    }


    /*pBuf += VOS_sprintf(pBuf, "\r\n      state %s ",
                        (pstConfig->bAuthRmtChap)?cServerState:cClientState) ;*/

    /* response timeout 事件:显示retransmit计数器值 */
    if (ucEvent == CHAP_RESPONSETIMEOUT)
    {
        pBuf += VOS_sprintf(pBuf, ", Retransmit %lu ", pstChapInfo->ulRespTransmits);
    }

    /* challenge timeout 事件:显示retransmit计数器值 */
    if (ucEvent == CHAP_CHALLENGETIMEOUT)
    {
        pBuf += VOS_sprintf(pBuf, ", Retransmit %lu ", pstChapInfo->ulChalTransmits);
    }

    lBufLen = pBuf - szDebugBuf;
    PPP_DebugOutString(szDebugBuf, lBufLen, pstPppInfo);

    return;
}


VOID CHAP_Debug_Error(PPPINFO_S *pstPppInfo, VOS_UINT16 usLogLevel, CHAR *pString)
{
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;
    LONG lBufLen  = 0;
    szDebugBuf[0] = '\0';

    /* 根据IMSI输出调试信息 */
    DEBUGBYIMSI();

    if (pstPppInfo->stPppDebugInfo.bDebug_Chap_Error == VRP_NO)
    {
        /*DEBUG 开关未打开,返回*/
        return;
    }

    /*VOS_DBGASSERT(pstPppInfo ) ;*/

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Error: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s : %s ",
                        PPP_Debug_GetInterfaceName(pstPppInfo),
                        PPP_Debug_GetProtocolName(PPP_CHAP),
                        pString);
    lBufLen = pBuf - szDebugBuf;
    PPP_DebugOutString(szDebugBuf, lBufLen, pstPppInfo);

    return;
}

/*lint +e813*/
/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

