/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              prod.h
*
*  Project Code: VISP1.5
*   Module Name: socket4 
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: the declaration of socket functions used in protocol( such as tcp, udp ). 
*                these functions are used to modified state of socket 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef        _PROD_H
#define        _PROD_H

#ifdef    __cplusplus
extern    "C"{
#endif

#define    SBSPACE(sb) \
    ((LONG) ((sb)->sb_ulHiWat - (sb)->sb_ulCC))
     

#define    SBALLOC(sb, lLen) \
{ \
    (sb)->sb_ulCC += lLen; \
}

#define    SBFREE(sb, lLen) \
{ \
    (sb)->sb_ulCC -= lLen; \
}
     
#define    SOWWAKEUP(so)    SoWakeUp((so), 1)
#define    SORWAKEUP(so)    SoWakeUp((so), 2)

VOID        SO_CantSendMore(SOCKET_S *);
VOID        SO_CantRcvMore(SOCKET_S *pSocket);
VOID        SO_IsConnecting(SOCKET_S *);
VOID        SO_IsConnected(SOCKET_S *);
VOID        SO_IsDisconnecting(SOCKET_S *);
VOID        SO_IsDisconnected(SOCKET_S *);
SOCKET_S    *SO_NewConn(SOCKET_S *, LONG );
VOID        SO_HasOutOfBand(SOCKET_S *);
VOID        SO_QInsQue(SOCKET_S *pHead, SOCKET_S *pSocket, SHORT sQ);
LONG        SO_QRemQue(SOCKET_S *pSocket, SHORT sQ);
VOID        SO_Free(SOCKET_S *pSocket);
VOID        SO_RFlush(SOCKET_S *pSocket);
LONG        SO_Reserve(SOCKET_S *, ULONG, ULONG);

VOID        SBAppend(SOCKBUF_S *pSb, MBUF_S *pstMTail);
VOID        SB_Append(SOCKET_S *pSocket, LONG iKind, MBUF_S *pstMTail);
LONG        SB_AppendAddr(SOCKET_S *pSocket,SOCKADDR_S *pAsa,MBUF_S *pM0,\
                 MBUF_S *pControl);
VOID        SB_AppendRecord(SOCKBUF_S *pSb, MBUF_S *pM0);
LONG        SB_AppendControl(SOCKBUF_S *pSb, MBUF_S *pM0, MBUF_S *pControl);
VOID        SB_InsertOob(SOCKBUF_S *pSb, MBUF_S *pM0);
VOID        SBFlush(SOCKBUF_S *pSb);
VOID        SB_Flush(SOCKET_S *pSocket, LONG iKind);
VOID        SB_Drop(SOCKBUF_S *, LONG );
LONG        SB_Reserve(SOCKBUF_S *, ULONG );
VOID        SB_Compress(SOCKBUF_S *pSb, MBUF_S *pM, MBUF_S *pN);
VOID        SB_DropRecord(SOCKBUF_S *pSb);
VOID        SB_Release(SOCKET_S *pSocket, LONG iKind);
LONG        SB_Reserve(SOCKBUF_S *pSb, ULONG ulCc);
VOID        SBDropLastRecord( SOCKBUF_S *pSb );
VOID        SB_DropLastRecord(SOCKET_S *pSocket, LONG iKind) ;
UINT32      SO_CheckCookieStart(SOCKET_S *pHead);

VOID             SO6_CantSendMore(UINTPTR);
VOID             SO6_CantRcvMore(UINTPTR);
VOID             SO6_IsConnecting(UINTPTR);
VOID             SO6_IsConnected(UINTPTR);
VOID             SO6_IsDisconnecting(UINTPTR);
VOID             SO6_IsDisconnected(UINTPTR);
UINTPTR          SO6_NewConn(UINTPTR, LONG);
VOID             SO6_HasOutOfBand(UINTPTR);
LONG             SO6_Reserve(UINTPTR ,  ULONG, ULONG);
VOID             SB6_Append(UINTPTR , MBUF_S *);
LONG             SB6_AppendAddr(UINTPTR ,SOCKADDR_S *,MBUF_S *, MBUF_S *);
VOID             SB6_Flush(UINTPTR);
VOID             SB6_Drop(UINTPTR, LONG);
UINT32           SO6_CheckCookieStart(UINTPTR);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
