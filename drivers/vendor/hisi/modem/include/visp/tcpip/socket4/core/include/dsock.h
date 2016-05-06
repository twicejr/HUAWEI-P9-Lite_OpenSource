/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dsock.h
*
*  Project Code: VISP1.5
*   Module Name: socket4  
*  Date Created: 2006-4-28
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
#ifndef  _DSOCK_H
#define  _DSOCK_H

#ifdef  __cplusplus
extern  "C"{
#endif

/* 
 * max_hdr include UDP or TCP head and IP head(also IP option) 
 * and ETHERnet head is 20 + 20 + 20 + 14
 */
#define    MAX_HDR            80

#define    SOSENDALLATONCE(so)    ((so)->so_pProto->pr_sFlags & PR_ATOMIC)

typedef struct tagSSDATA 
{
    LONG    lResid;
    LONG    lSpace;
    LONG    nClen;
    SHORT   sFlags;
    SHORT   sAtomic;
    SHORT   sDontRoute;
    UCHAR   ucPadding[2];
}SSDATA;

typedef struct tagSSMBUF 
{
    MBUF_S    *pTop;
    MBUF_S    *pAddr;
    MBUF_S    *pControl;
}SSMBUF;

typedef struct tagSRDATA 
{
    LONG    orig_nResid;
    SHORT   sFlags;
    SHORT   sType;
}SRDATA;

typedef struct tagSRMBUF 
{
    MBUF_S    *pM;
    MBUF_S    **ppM;
    MBUF_S    **ppAddr;
    MBUF_S    **ppControl;
    MBUF_DATABLOCKDESCRIPTOR_S *pstCurDesc;
    
}SRMBUF;

LONG    Falloc(ULONG ,TCB_S ** ,LONG *);
VOID    Ffree(TCB_S *, LONG );
LONG    GetSock(ULONG, LONG, SOCKET_S **);
LONG    SockArgs(MBUF_S **, CHAR *, LONG, LONG );

LONG    SO_DisConnect(SOCKET_S * );

VOID    SS_Error(MBUF_S *, MBUF_S *);
LONG    SS_WaitSpace(SOCKET_S *, UIO_S *, SSDATA *, SSMBUF *);
LONG    SS_FillMbuf(UIO_S *, SSDATA *, SSMBUF *);
LONG    SS_PassPro(SOCKET_S *, SSDATA *, SSMBUF *);

LONG    SR_MsgOob(SOCKET_S *, UIO_S *, SRDATA *, SRMBUF *);
LONG    SR_WaitSpace(SOCKET_S *, UIO_S *,SRDATA *, SRMBUF *);
LONG    SR_ProcAddrCon(SOCKET_S *, SRDATA *, SRMBUF *);
LONG    SR_ProcData(SOCKET_S *, UIO_S *, SRDATA *, SRMBUF *);
LONG    SR_CleanUp(SOCKET_S *, UIO_S *, SRDATA *, SRMBUF *);

LONG    TcbFileExpand( TCB_S * );

ULONG TCPKeepAliveCloseJudge(VOID *pSock);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

