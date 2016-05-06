/************************************************************************
*                                                                      *
*                             pap_dbg.c                                *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/06/14                                      *
*  Author:             Zhu Feng Zhi                                    *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PAP模块的debug信息处理                          *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件包括了PAP模块debug信息处理的全部代码                       *
*                                                                      *
************************************************************************/



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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_PAP_DBG_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

CHAR *cPap_Debug_Code[] =
{
    "Reserved",      /* 0 */
    "Request",       /* 1 */
    "Ack",           /* 2 */
    "Nak"            /* 3 */
};

CHAR *cPap_Client_State[] =
{
    "Initial",
    "SendRequest",
    "ClientSuccess",
    "ClientFailed",
    " "
};

CHAR *cPap_Server_State[] =
{
    "Initial",
    "ServerListen",
    "ServerSuccess",
    "ServerFailed",
    "WaitAAA"
};

CHAR *cPap_Debug_Event[] =
{
    "Initial ",             /* 0 */
    "Server Lower Up",  /* 1 */
    "Client Lower Up",  /* 2 */
    "Lower Down",           /* 3 */
    "Receive Request",  /* 4 */
    "AAA Result",           /* 5 */
    "Receive Ack",      /* 6 */
    "Receive Nak",      /* 7 */
    "Request TimeOut",  /* 8 */
    "Code Reject",      /* 9 */
    "Wait Request TimeOut",  /* 10 */
    "AAA Response TimeOut",   /* 11 */
    "Error Event"           /* 12 */
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*lint -e813*/
/****************************************************************************
* CREATE DATE  ：2000/06/14                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：输出关于报文的调试信息,只针对符合PPP状态机的控制协议       *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块                                       *
*                pPacket:报文头位置                                         *
*                ulLen:报文长度                                             *
*                ucIsInPacket:是否是输入报文                                *
*                usProtocol:报文协议号                                      *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_LCP_ReceivePacket等                                    *
****************************************************************************/
VOID PAP_Debug_Packet(PPPINFO_S* pstPppInfo, UCHAR *pPacket, VOS_UINT32 ulLen, VOS_UINT16 usProtocol, UCHAR ucIsInPacket)
{
    PPPPAPINFO_S *pstPapInfo   = pstPppInfo->pstPapInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;
    VOS_UINT32 ulTotalLen = ulLen + PAP_HEADERLEN;
    UCHAR ucCode, ucId;
    VOS_UINT16 sFrameLen;
    LONG lLen = (LONG)ulLen;
    UCHAR ucLen;

    szDebugBuf[0] = '\0';

    /* 根据IMSI输出调试信息 */
    DEBUGBYIMSI();

    if (pstPppInfo->stPppDebugInfo.bDebug_Pap_Packet == VRP_NO)
    {
        /*DEBUG 开关未打开,返回*/
        return;
    }

    /* pap 报文情况 */

    /*
     |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  ff   |  03   |    c223       |  code |  ID   |    frame len  |   ...     |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |------------- lLen / sFrameLen ------------|
                                    pPacket
     |-----------------------------  ulTotalLen    --------------------------------|
     */

    /* VOS_DBGASSERT(pstPppInfo) ;
     VOS_DBGASSERT(pPacket) ;
     */
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
        PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);
        return;
    }

    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(ucId, pPacket);
    PPP_GETSHORT(sFrameLen, pPacket);

    /* 显示当前状态,Code,id以及长度 */
    /*区分是server状态还是client状态 added by guoning 20021022 D7169*/
    if (((ucIsInPacket == 1) && (ucCode == PAP_AUTHREQ))
       || ((ucIsInPacket != 1) && (ucCode == PAP_AUTHACK))
       || ((ucIsInPacket != 1) && (ucCode == PAP_AUTHNAK)))
    {
        pBuf += VOS_sprintf(pBuf, "\r\n      State %s, code %s(%02x), id %x, len %d ",
                            cPap_Server_State[pstPapInfo->ucServerState],
                            cPap_Debug_Code[ucCode],
                            ucCode,
                            ucId,
                            sFrameLen
                );
    }
    else if (((ucIsInPacket != 1) && (ucCode == PAP_AUTHREQ))
       || ((ucIsInPacket == 1) && (ucCode == PAP_AUTHACK))
       || ((ucIsInPacket == 1) && (ucCode == PAP_AUTHNAK)))
    {
        pBuf += VOS_sprintf(pBuf, "\r\n      State %s, code %s(%02x), id %x, len %d ",
                            cPap_Server_State[pstPapInfo->ucClientState],
                            cPap_Debug_Code[ucCode],
                            ucCode,
                            ucId,
                            sFrameLen
                );
    }

    /*pBuf += VOS_sprintf(pBuf, "\r\n      State %s, code %s(%02x), id %x, len %d ",
        (pstConfig->bAuthRmtPap)?
        cPap_Server_State[pstPapInfo->ucServerState]:cPap_Client_State[pstPapInfo->ucClientState],
        cPap_Debug_Code[ucCode],
        ucCode,
        ucId,
        sFrameLen
        );*/


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
        case PAP_AUTHREQ:

            /*显示Id_Len 及 Id*/
            PPP_GETCHAR(ucLen, pPacket);

            pBuf += VOS_sprintf(pBuf, "\r\n      Host Len:%3d  Name:%s ", ucLen,
                                PPP_Debug_GetString(pPacket, ucLen));
            PPP_INCPTR(ucLen, pPacket);

            /* 显示Password Length 及 Pwd*/
            PPP_GETCHAR(ucLen, pPacket);
            pBuf += VOS_sprintf(pBuf, "\r\n      Pwd Len:%3d  Pwd:%s", ucLen,
                                PPP_Debug_GetString(pPacket, ucLen));
            break;
        case PAP_AUTHACK:
        case PAP_AUTHNAK:

            /*显示Message_Len 及 Msg*/
            PPP_GETCHAR(ucLen, pPacket);
            pBuf += VOS_sprintf(pBuf, "\r\n      Msg Len:%3d  Msg:%s", ucLen,
                                PPP_Debug_GetString(pPacket, ucLen));
            break;
        default:
            pBuf += VOS_sprintf(pBuf, "\r\n       UnKnown Code ");
            break;
    }

    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/14                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：输出子协议状态转换的调试信息                               *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPapInfo:PAP控制块指针                                 *
*                ucNewState:状态机新状态                                    *
*                 ucType: Client状态或Server状态                                *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：                                                            *
****************************************************************************/
VOID PAP_Debug_StateChange(PPPINFO_S *pstPppInfo, UCHAR ucNewState, UCHAR ucType)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;
    CHAR cState[20], cNewState[20];

    szDebugBuf[0] = 0;
    cState[0] = 0;
    cNewState[0] = 0;

    /* 根据IMSI输出调试信息 */
    DEBUGBYIMSI();

    if (pstPppInfo->stPppDebugInfo.bDebug_Pap_StateChange == VRP_NO)
    {
        /*DEBUG 开关未打开,返回*/
        return;
    }

    if (ucType == CLIENT_STATE)
    {
        /* Client 状态转换 */
        if (pstPapInfo->ucClientState == ucNewState)
        {
            return;
        }
        else
        {
            if (pstPapInfo->ucClientState > PAP_STATE_CLIENT_FAILED)
            {
                /* 错误的状态 */
                (VOID)VOS_sprintf(cState, "%s", "Error-State");
            }
            else
            {
                (VOID)VOS_sprintf(cState, "%s", cPap_Client_State[pstPapInfo->ucClientState]);
            }

            if (ucNewState >= PAP_STATE_WAIT_AAA)
            {
                /* 错误的状态 */
                (VOID)VOS_sprintf(cNewState, "%s", "Error-State");
            }
            else
            {
                (VOID)VOS_sprintf(cNewState, "%s", cPap_Client_State[ucNewState]);
            }

            pBuf += VOS_sprintf(pBuf, "\r\n  PPP State Change: ");
            pBuf += VOS_sprintf(pBuf, "\r\n      %s %s : %s --> %s ",
                                PPP_Debug_GetInterfaceName(pstPppInfo),
                                PPP_Debug_GetProtocolName(PPP_PAP),
                                cState,
                                cNewState);
        }
    }
    else
    {
        /* Server 状态转换 */
        if (pstPapInfo->ucServerState == ucNewState)
        {
            return;
        }
        else
        {
            if (pstPapInfo->ucServerState > PAP_STATE_WAIT_AAA)
            {
                /* 错误的状态 */
                (VOID)VOS_sprintf(cState, "%s", "Error-State");
            }
            else
            {
                (VOID)VOS_sprintf(cState, "%s", cPap_Server_State[pstPapInfo->ucServerState]);
            }

            if (ucNewState > PAP_STATE_WAIT_AAA)
            {
                /* 错误的状态 */
                (VOID)VOS_sprintf(cNewState, "%s", "Error-State");
            }
            else
            {
                (VOID)VOS_sprintf(cNewState, "%s", cPap_Server_State[ucNewState]);
            }

            pBuf += VOS_sprintf(pBuf, "\r\n  PPP State Change: ");
            pBuf += VOS_sprintf(pBuf, "\r\n      %s %s : %s --> %s ",
                                PPP_Debug_GetInterfaceName(pstPppInfo),
                                PPP_Debug_GetProtocolName(PPP_PAP),
                                cState,
                                cNewState);
        }
    }

    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/14                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：输出PAP子协议发生外部事件的调试信息                       *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPapInfo: PAP控制块指针                                *
*                ulEvent:状态机事件                                         *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：                                                            *
****************************************************************************/
VOID PAP_Debug_Event(PPPINFO_S* pstPppInfo, UCHAR ucEvent)
{
    PPPPAPINFO_S *pstPapInfo   = pstPppInfo->pstPapInfo;
    PPPCONFIGINFO_S *pstConfig = pstPppInfo->pstConfigInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;

    CHAR cClientState[20], cServerState[20], cEvent[100];

    szDebugBuf[0]   = 0;
    cClientState[0] = 0;
    cServerState[0] = 0;
    cEvent[0] = 0;

    /* 根据IMSI输出调试信息 */
    DEBUGBYIMSI();

    if (pstPppInfo->stPppDebugInfo.bDebug_Pap_Event == VRP_NO)
    {
        /*DEBUG 开关未打开,返回*/
        return;
    }

    /* 取得 Client 状态 */
    if (pstPapInfo->ucClientState > PAP_STATE_WAIT_AAA)
    {
        /* 错误的状态 */
        (VOID)VOS_sprintf(cClientState, "%s", "Error-State");
    }
    else
    {
        (VOID)VOS_sprintf(cClientState, "%s", cPap_Client_State[pstPapInfo->ucClientState]);
    }

    /* 取得 Server 状态 */
    if (pstPapInfo->ucServerState > PAP_STATE_WAIT_AAA)
    {
        /* 错误的状态 */
        (VOID)VOS_sprintf(cServerState, "%s", "Error-State");
    }
    else
    {
        (VOID)VOS_sprintf(cServerState, "%s", cPap_Server_State[pstPapInfo->ucServerState]);
    }

    if (ucEvent >= PAP_ERROREVENT)
    {
        /* 错误的事件 */
        (VOID)VOS_sprintf(cEvent, "%s", "Error-Event");
    }
    else
    {
        (VOID)VOS_sprintf(cEvent, "%s", cPap_Debug_Event[ucEvent]);
    }

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Event: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s %s Event ",
                        PPP_Debug_GetInterfaceName(pstPppInfo),
                        PPP_Debug_GetProtocolName(PPP_PAP),
                        cEvent);

    switch (ucEvent)
    {
        case PAP_INITIALIZATION:
        case PAP_LOWERDOWN:
        case PAP_CODEREJECT:
            pBuf += VOS_sprintf(pBuf, "\r\n      state %s ",
                                (pstConfig->bAuthRmtPap) ? cServerState : cClientState);
            break;

        case PAP_CLIENTLOWERUP:
        case PAP_RECEIVEACK:
        case PAP_RECEIVENAK:
        case PAP_REQUESTTIMEOUT:
            pBuf += VOS_sprintf(pBuf, "\r\n      state %s ", cClientState);
            break;

        case PAP_SERVERLOWERUP:
        case PAP_RECEIVEREQUEST:
        case PAP_AAARESULT:
        case PAP_WAITREQTIMEOUT:
            pBuf += VOS_sprintf(pBuf, "\r\n      state %s ", cServerState);
            break;

        default:
            break;
    }


    /*pBuf += VOS_sprintf(pBuf, "\r\n      state %s ",
                (pstConfig->bAuthRmtPap)?cServerState:cClientState) ;*/

    /* request timeout 事件:显示retransmit计数器值 */
    if (ucEvent == PAP_REQUESTTIMEOUT)
    {
        pBuf += VOS_sprintf(pBuf, ", Retransmit %d ", pstPapInfo->ucTransmits);
    }

    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/14                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：输出子协议PAP的错误信息                                    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                usLogLevel:LOG级别                                         *
*                pString   :要输出的字串                                    *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PAP 各处理函数                                            *
****************************************************************************/
VOID PAP_Debug_Error(PPPINFO_S *pstPppInfo, VOS_UINT16 usLogLevel, CHAR *pString)
{
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;

    szDebugBuf[0] = 0;

    /* 根据IMSI输出调试信息 */
    DEBUGBYIMSI();

    if (pstPppInfo->stPppDebugInfo.bDebug_Pap_Error == VRP_NO)
    {
        /*DEBUG 开关未打开,返回*/
        return;
    }

    /* VOS_DBGASSERT(pstPppInfo) ;*/

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Error: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s : %s ",
                        PPP_Debug_GetInterfaceName(pstPppInfo),
                        PPP_Debug_GetProtocolName(PPP_PAP),
                        pString);
    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);

    return;
}

/*lint +e813*/
/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
