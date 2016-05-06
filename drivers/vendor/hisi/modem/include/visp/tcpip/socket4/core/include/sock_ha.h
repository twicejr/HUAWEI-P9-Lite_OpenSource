/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_ha.h
*
*  Project Code: VISP V100R006
*   Module Name: SOCKET4
*  Date Created: 2006-12-6
*        Author: l48923(48923)
*   Description: Header of Socket HA
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-6   l48923(48923)    Create the first version.
*
*******************************************************************************/
#ifndef        _SOCK_HA_H
#define        _SOCK_HA_H

#ifdef    __cplusplus
extern    "C"{
#endif

/* Definition of backup operation of SOCKET module */
/* if you add or delete bak type,please upate g_aszSocketBackDbgInfo & function SOCK_HA_DebugBackupMsg */
/*如果后续要新增操作类型, 请在BK_SOCKET_HOSTADD之前添加, 而不是在最后添加, 2008-11-26*/
enum enumSOCKHAOP
{
    BK_SOCKET_SKTCHAIN = 1,    /* Backup socket chain */
    BK_SOCKET_SKTMMBRADD,      /* Join multicast group, only used by batch backup */
    BK_SOCKET_SKTMMBRDEL,      /* Leave multicast group */
    BK_SOCKET_SKTMODIFY,       /* Modify socket */
    BK_SOCKET_SKTCLOSE,        /* Close socket */
    BK_SOCKET_SKTACCEPT,       /* Update FD of son socket */
    BK_SOCKET_SKTSONCREATE ,   /* Connection is create and goes into the q queue */
    BK_SOCKET_SKTSONMODIFY ,   /* Son socket changed */
    BK_SOCKET_SKTSONDELETE,    /* Delete son socket */
    BK_SOCKET_SKTSNDBUFADD,    /* Add data to socket send buffer */
    BK_SOCKET_SKTRCVBUFADD,    /* Add data to socket receive buffer */
    BK_SOCKET_SKTRCVBUFEDEL,   /* Delete data from socket receive buffer */
    
    BK_SOCKET_SKTMMBRADDRT,    /* Join multicast group, only used by realtime backup*/
    BK_SOCKET_SKTMMBRBLK,      /* block source from sourcelist*/
    BK_SOCKET_SKTMMBRUNBLK,    /* unblock source from sourcelist*/
    BK_SOCKET_SKTMMBRADDSRC,   /* add source to sourcelist or join multi_group with source*/
    BK_SOCKET_SKTMMBRDRPSRC,   /* drop source from sourcelist or leave group with deleting the last source*/
    BK_SOCKET_SKTMMBSOURCE,    /* only backup source address*/

    BK_SOCKET_HOSTADD,         /* Add host */
    BK_SOCKET_HOSTDEL,         /* Delete host */
    
    BK_SOCKET_BATCHOVER,       /* Batch backup over */    
};

/* Max num of backup socket */
#define MAX_BACKUP_SOCKET 1024

/* Max num of debugged socket */
#define SOCK_HA_MAX_DEBUG 5

/* Flags whether backup msg of socket buf and socket 
 * chain is in socket backup queue
 */
#define SOCK_HA_SNDBUF_BKMSG_INQUE    1
#define SOCK_HA_SNDBUF_BKMSG_NOTINQUE 0
#define SOCK_HA_RCVBUF_BKMSG_INQUE    0X01
#define SOCK_HA_RCVBUF_RMMSG_INQUE    0X02

/* Flags that indicate whether the backup msg of 
 * socket modification/chain is in socket backup queue 
 */
#define SOCK_HA_SOCKET_MODMSG_INQUE   0X01
#define SOCK_HA_SOCKET_CHNMSG_INQUE   0X02

/* Error code for processing socket backup msg:
 * SOCK_HA_RealTimeBackup 
 * SOCK_HA_BackupMsgDeal
 * TCP_HA_RealTimeBackup
 * TCP_HA_BackupMsgDeal
 */
#define SOCK_HA_ERR_BACKUPBUFNOTENOUGH 2 /* Backup buf is not enough */
#define SOCK_HA_ERR_BACKUPMSGPACKED    3 /* Backup msg is already packed */

#define MULTI_MEMBER_DEFAULT    8

#ifndef  MCAST_IFINDEX_REGISTER_IFAP
#define MCAST_IFINDEX_REGISTER_IFAP  IFINDEX_MCAST_RESERVED_BEGIN
#endif

/* Backup socket header */
typedef struct tagBkSocketHeader
{
    LONG lFd;
}BKSOCKETHEADER_S;

/* Backup socket */
typedef struct tagBKSocket
{
    SHORT               so_sType;          /* generic type, see socket.h */
    SHORT               so_sLinger;        /* time to linger while closing */
    ULONG               so_ulOptions;      /* from socket call, see socket.h */
    ULONG               so_ulState;        /* internal state flags SS_*, below */
    ULONG               so_ulOobMark;      /* chars to oob mark */
    ULONG               ulKeepIdle;
    /* End of likaikun */
    KEEPALIVESET_S      so_stKeepalive; 
    SENDDATAIF_S        so_stSendDataIf;
    SENDBY_IF_NEXTHOP_S so_stSendby_If_NextHop; 
    SNDBYDSTMAC_S       so_stSndbyDstMac;
    ULONG               ulSrcAddr;
    ULONG               ulZoneId;
    SHORT               so_sQLimit;        /* max number queued connections */
    SHORT               so_sRefCnt;        /* reference count */
    ULONG               so_ulHeadCacheNum; /* Num of headcache */
    struct tagBKSOCKBUF
    {
        LONG     sb_lHiWat;     /* max actual CHAR count */    
        LONG     sb_lLoWat;     /* low water mark */
        SHORT    sb_sTimeO;      /* timeout for read/write */
        UCHAR    ucPadding_1[2]; /* padding */
    } so_stRcv, so_stSnd;
}BKSOCKET_S;

/* Backup inpcb header */
typedef struct tagBKINPCBHeader
{
    USHORT usTotalLen;  /* Total length of backup inpcb info */
    USHORT usIPOptLen;  /* Length of ip option, 0 indicates that there is no ip option */
    USHORT usMOptLen;   /* Length of multicast options, 0 indicates that there is no multicast option */
    USHORT usPPcbLen;   /* Protocol cb length, used by tcp socket */
}BKINPCBHEADER_S;

/* Backup inpcb */
typedef struct tagBKINPCB
{
    INADDR_S inp_stFAddr;    /* foreign address */
    INADDR_S inp_stLAddr;    /* local address */
    USHORT   inp_usFPort;    /* foreign port */
    USHORT   inp_usLPort;    /* local port */
    LONG     inp_nFlags;     /* generic IP/Datagram flags */
    IP_S     inp_stIp;       /* IP header */
}BKINPCB_S;

/* Backup multicast option */
typedef struct tagBKIPMOPTIONS
{
    ULONG   imo_ulIndexIf;  /* if for outgoing multicasts */
    UCHAR   imo_bTTL;       /* TTL for outgoing multicasts */
    UCHAR   imo_bLoop;      /* 1 indicates that hear sends if a member */
    USHORT  imo_usVIF;      /* outgoing vif no */
}BKIPMOPTIONS_S;

/* Info that describes the socket to be created on slave board or the 
 * socket that has been closed and no fd refers to. These info can 
 * identify this socket.
 */
typedef struct tagBkSocketInfo
{
    LONG      lFamily;
    SHORT     sProtoType;
    SHORT     sProto;
    INADDR_S  stFAddr;
    INADDR_S  stLAddr;
    USHORT    usFPort;
    USHORT    usLPort;
}BKSOCKETINFO_S;

/* Backup son socket header */
typedef struct tagBkSonSocketHeader
{
    INADDR_S  stFAddr;
    INADDR_S  stLAddr;
    USHORT    usFPort;
    USHORT    usLPort;
}BKSONSOCKETHEADER_S;

/* Info for accepting on backup socket */
typedef struct tagBkSocketAcceptInfo
{
    LONG                lSonFd;
    BKSONSOCKETHEADER_S stBkSonSocketHeader;
}BKSOCKETACCEPTINFO_S;

/* Backup host */
typedef struct tagBKSOCKHOST
{
    CHAR  szHostName[HostNameLen];
    CHAR  szHostIP[IPADDRMAXLEN];
    UCHAR ucPadding_1[4 - ((HostNameLen + IPADDRMAXLEN) % 4)];
}BKSOCKHOST_S;

/* Backup msg */
typedef struct tagBKSOCKMSG
{
    UCHAR *pucBkMsg;
    ULONG  ulBkMsgLen;
}BKSOCKMSG_S;

/* Macro that get the length to backup inpcb */
/* Info of multicast group is not considered here */
#define SOCK_HA_GETINPCBBACKUPLEN(pInpcb, ulBackupLen) \
{ \
    ULONG ulTmpTCPCBBackupLenTmp = 0; \
    SOCKET_S *pTmpSocketTmp = NULL; \
    ulBackupLen = sizeof(BKINPCBHEADER_S)+sizeof(BKINPCB_S); \
    if (NULL != (pInpcb)->inp_pOptions) \
    { \
        ulBackupLen += MBUF_GET_TOTAL_DATA_LENGTH((pInpcb)->inp_pOptions) + sizeof(ULONG); \
        ulBackupLen = (((ulBackupLen) + 3) >> 2) << 2; \
    } \
    if (NULL != (pInpcb)->inp_pMOptions) \
    { \
        ulBackupLen += sizeof(BKIPMOPTIONS_S); \
    } \
    pTmpSocketTmp = (pInpcb)->inp_pSocket; \
    if ((NULL != (pInpcb)->inp_pPPcb) \
        && (NULL != pTmpSocketTmp->so_pProto) \
        && (IPPROTO_TCP == pTmpSocketTmp->so_pProto->pr_sProtocol)) \
    { \
        TCP_HA_GETTCPCBBACKUPLEN((TCPCB_S *)((pInpcb)->inp_pPPcb), ulTmpTCPCBBackupLenTmp); \
        ulBackupLen += ulTmpTCPCBBackupLenTmp; \
    } \
}

/* Macro that get the max length to backup inpcb */
#define SOCK_HA_GETMAXINPCBBACKUPLEN(ulBackupLen) \
{ \
    ULONG ulTmpMaxTCPCBBackupLenTmp = 0; \
    ulBackupLen = sizeof(BKINPCBHEADER_S)+sizeof(BKINPCB_S); \
    ulBackupLen += MAX_IPOPTLEN + sizeof(ULONG); \
    ulBackupLen += sizeof(BKIPMOPTIONS_S); \
    TCP_HA_GETMAXTCPCBBACKUPLEN(ulTmpMaxTCPCBBackupLenTmp); \
    ulBackupLen += ulTmpMaxTCPCBBackupLenTmp; \
}

/* Get socket info that can identify it */
/* Modified by y00176567, at 2011-05-26. 修改原因: 消除VC三级告警 */
/* (pstSocketInfo)->sProtoType = (SHORT)((pSocket)->so_pProto->pr_sType); 增加(SHORT)以保证两端类型一致*/
#define SOCK_HA_GETSOCKETINFO(pSocket, pstSocketInfo) \
do \
{ \
    if ((NULL != (pSocket)->so_pProto) && (NULL != (pSocket)->so_pPcb))\
    {\
        (pstSocketInfo)->lFamily = (pSocket)->so_pProto->pr_pDomain->dom_nFamily; \
        (pstSocketInfo)->sProtoType = (SHORT)((pSocket)->so_pProto->pr_sType); \
        if (0 == (pSocket)->so_pProto->pr_sProtocol) \
        { \
            /* Protocolid is zero means that this is a rawip socket, so we should fetch the protocolid from the inpcb.*/ \
            (pstSocketInfo)->sProto = ((INPCB_S *)((pSocket)->so_pPcb))->inp_stIp.ip_chPr; \
        } \
        else \
        { \
            (pstSocketInfo)->sProto = (pSocket)->so_pProto->pr_sProtocol; \
        } \
    }\
    if (NULL != (pSocket)->so_pPcb)\
    {\
        /* Get inpcb info from socket */ \
        (pstSocketInfo)->stFAddr.s_ulAddr = ((INPCB_S *)((pSocket)->so_pPcb))->inp_stFAddr.s_ulAddr; \
        (pstSocketInfo)->stLAddr.s_ulAddr = ((INPCB_S *)((pSocket)->so_pPcb))->inp_stLAddr.s_ulAddr; \
        (pstSocketInfo)->usFPort = ((INPCB_S *)((pSocket)->so_pPcb))->inp_usFPort; \
        (pstSocketInfo)->usLPort = ((INPCB_S *)((pSocket)->so_pPcb))->inp_usLPort; \
    }\
} while(0)

/* Search socket according to socket info. Now only used to search closed tcp socket. */
#define SOCK_HA_SEARCHSOCKET(pSocket, pstSocketInfo) \
do \
{ \
    INPCB_S *pTmpInpcb = NULL; \
    pSocket = NULL; \
    if ((AF_INET == (pstSocketInfo)->lFamily) \
        && (IPPROTO_TCP == (pstSocketInfo)->sProto)) \
    { \
        /* This is just valid for tcp socket. */ \
        pTmpInpcb = INPCB_HashSearch(&g_stTcpHash, \
                                     (pstSocketInfo)->stFAddr, \
                                     (pstSocketInfo)->usFPort, \
                                     (pstSocketInfo)->stLAddr, \
                                     (pstSocketInfo)->usLPort, \
                                     0, \
                                     0); \
        if (NULL != pTmpInpcb) \
        { \
            pSocket = pTmpInpcb->inp_pSocket; \
        } \
    } \
} while(0)

extern ULONG g_ulCurBackupSocketNum;

LONG  SOCK_HA_NeedBackup(SOCKET_S *pSocket);
ULONG TCPIP_HA_SetSockDbg(ULONG ulDbg, LONG lSocketID);
ULONG TCPIP_HA_GetSockDbg(ULONG *pulSockHaDbg);
LONG  SOCK_HA_BackupNotify(LONG lFd, UCHAR ucOperation, CHAR *pszInfo);
LONG  SOCK_HA_BatchBackup();
LONG  SOCK_HA_SwitchNotify();
LONG  SOCK_HA_RealTimeBackup(LONG lFd, UCHAR ucOperation, CHAR *pszInfo, CHAR *pszBuf, ULONG *pulBufLen);
LONG  SOCK_HA_BackupQueueDeal(LONG lIsSwitching);
LONG  SOCK_HA_BackupInput(CHAR * pszBackupBuf, ULONG ulBackupBufLen);
LONG  SOCK_HA_Smooth();
ULONG TCPIP_HA_VerifySocket (LONG lSocketID);
ULONG SOCK_HA_Clean();
ULONG SOCK_HA_GetTcpState(INPCB_S *pstInPCB);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
