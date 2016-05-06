/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock.h
*
*  Project Code: VISP1.5
*   Module Name:   
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: socket function
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*  2006-05-11   luyao           为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/
#ifndef  _SOCK_H
#define  _SOCK_H

#ifdef  __cplusplus
extern  "C"{
#endif

typedef struct tagLINGER {
    LONG        l_iOnOff;        /* option on/off */
    LONG        l_iLinger;       /* linger time */
}LINGER_S;
#define        L_LINGER_S        sizeof(LINGER_S)

typedef struct tagMSGHDR
{
    CHAR    *msg_pName;         /* optional address */
    SHORT   msg_nNameLen;       /* size of address */
    UCHAR   ucPadding_1[2];
    IOVEC_S *msg_pIov;          /* scatter/gather array */
    SHORT   msg_nIovLen;        /* # elements in msg_iov */
    UCHAR   ucPadding_2[2];
    CHAR    *msg_pControl;      /* access rights sent/received */
    SHORT   msg_nControlLen;
    SHORT   msg_sFlags;
}MSGHDR_S;
#define L_MSGHDR_S        sizeof(MSGHDR_S)


LONG SO_Create(ULONG ,LONG ,SOCKET_S **,LONG ,LONG);
LONG SO_Bind(SOCKET_S *, SOCKADDRIN_S *);
LONG SO_UnBind(SOCKET_S *, SOCKADDRIN_S *);

LONG SO_Listen(SOCKET_S *,LONG );
LONG SO_Accept(SOCKET_S *,MBUF_S *);
LONG SO_Connect(SOCKET_S *, SOCKADDRIN_S *);

LONG SO_Connect2(SOCKET_S *, SOCKET_S *);
LONG SO_Abort(SOCKET_S *);
LONG SO_Shutdown(SOCKET_S *,LONG );
LONG SO_Close(SOCKET_S *);
LONG SendIt(LONG,MSGHDR_S *,SHORT ,LONG *);
LONG SO_Send(SOCKET_S *,MBUF_S *, UIO_S *, MBUF_S *, MBUF_S *,SHORT );
LONG RecvIt(LONG , MSGHDR_S *,LONG *,LONG *);
LONG SO_Receive(SOCKET_S *, MBUF_S **, UIO_S *,MBUF_S **,MBUF_S **,SHORT *);
LONG SO_SetOpt(SOCKET_S *, LONG ,LONG ,MBUF_S  *);
LONG SO_GetOpt(SOCKET_S *, LONG , LONG , MBUF_S **);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
