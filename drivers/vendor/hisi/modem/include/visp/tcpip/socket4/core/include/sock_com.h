/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_com.h
*
*  Project Code: VISP1.5
*   Module Name: socket4
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: socket common definition
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*  2006-05-11   luyao           为支持ARM CPU字节对齐特性，修改结构。
*  2006-12-11   l57500          增加支持IPV6流发送
*******************************************************************************/
#ifndef  _SOCK_COM_H
#define  _SOCK_COM_H

#ifdef   __cplusplus
extern   "C"{
#endif

#ifndef _UTLDLL_H_
#include "vos/vospubh/utldll.h"
#endif
#include "tcpip/ifnet/include/ifnet_api.h"
#ifndef _IF_IIFNET_INC_H_
#include "tcpip/ifnet/include/iifnet_inc.h"
#endif
#ifndef _IP6_PUB_H_
#include "ipv6/ppmng/core/include/ppmng_pub.h"
#endif

#include "tcpip/tcp4/include/tcp_api.h"
#include "tcpip/udp4/include/udp_api.h"
#include "tcpip/rawip4/include/rawip_api.h"
#include "common/ipos/ipv6/tcp6_public.h"
#include "vos/vospubh/utlsll.h"

struct tagPROTOSW;
struct tagTCB;

#ifndef TYPEDEF_TASK_T
#define TYPEDEF_TASK_T
typedef ULONG    task_t;
#endif

/* socket   state */
#define    SS_NOFDREF           0x001    /* 没有任何文件表参考  no file table ref any more */
#define    SS_ISCONNECTED       0x002    /* 与一个监视相连的socket  socket connected to a peer */
#define    SS_ISCONNECTING      0x004    /* 在与监视相连接的过程中  in process of connecting to peer */
#define    SS_ISDISCONNECTING   0x008    /* 在断开连接的过程中  in process of disconnecting */
#define    SS_CANTSENDMORE      0x010    /* 不能再发送更多的数据  can't send more data to peer */
#define    SS_CANTRCVMORE       0x020    /* 不能在接收更多的数据  can't receive more data from peer */
#define    SS_RCVATMARK         0x040    /* 将OOB数据存在于接收缓存的起始位置 */

#define    SS_PRIV              0x080    /* 广播特权  privileged for broadcast, raw... */
#define    SS_NBIO              0x100    /* 没有阻塞选项  non-blocking ops */
#define    SS_ASYNC             0x200    /* 异步输入/输出通知  async i/o notify */
#define    SS_ISCONFIRMING      0x400    /* 决定接收连接请求  deciding to accept connection req */
#define    SS_CONNECT           0x800

#define    SS_BLOCKING          0x1000    /* there is one task blocking on this socket*/
                                          /* used in global socket*/
#define    SS_RECALL            0x2000    /* set socket to call back */
#define    SS_SENDDATAIF        0X20000
#define    SS_WOULDWAKEUP       0X40000
#define    SS_ASYNWAKEUP        0x80000   /* asynsocket to wake up peerclose message */

#define    SS_BACK              0x4000    /* set socket to backup */ /* added by mayun for socket ha */

#define    SS_CHILDSOCK    0x8000     /* To indicate whether the socket is a child socket */

/*    sockbuf     state */
#define    SB_LOCK              0x01    /* lock on data queue */
#define    SB_WANT              0x02    /* someone is waiting to lock */
#define    SB_WAIT              0x04    /* someone is waiting for data/space */
#define    SB_SEL               0x08    /* someone is selecting */
#define    SB_ASYNC             0x10    /* ASYNC I/O, need signals */
#define    SB_NOTIFY            (SB_WAIT|SB_SEL|SB_ASYNC)
#define    SB_NOINTR            0x40    /* operations not interruptible */
#define    SB_SELOOB            0x80
#define    SB_LOCKWAIT          0x100
#define    SB_BLOCKING          0x1000   /* there has been a task blocking on this sb */

#define    SCM_RIGHTS           0x01

/* Added by fengjing209023 DTS2014032706863 本段调用了CLOSE后不需要再上报ASYN_CLOSE事件 */
/* user close  state */
#define    SS_USERCLOSECALLED     0x01  /* 用户已经调用过CLOSE */
#define    SS_PEERCLOSENOTIFIED   0x02  /* SOCKET已经上报过PEERCLOSE */

/*************************************************************************/
/* 为向信息中心注册而定义相应宏                                          */
/*************************************************************************/
/*定义模块名称*/
#define MODULE_SOCKET       "SOCKET"


/* 告警消息 */
#define SOCK_DEBUG_GEN      1
#define SOCK_LOG_GEN        2
#define SOCK_TRAP_GEN       3

extern ULONG g_ulTcp_Syn_Use_Config_TOS;

typedef struct tagCMSGHDR
{
    SHORT        cmsg_nLen;     /* data byte count, including hdr */
    SHORT        cmsg_sLevel;   /* originating protocol */
    SHORT        cmsg_sType;    /* protocol-specific type */
    CHAR         cmsg_cData[2];
}CMSGHDR_S;
#define        L_CMSGHDR_S        sizeof(CMSGHDR_S)

#define    CMSG_DATA(cmsg)        ((UCHAR *)((cmsg) + 1))

typedef struct tagSELINFO
{
    task_t      si_tTaskId;   /* 保存等待这个Socket的进程ID（仅仅select使用）*/
    SHORT       si_sFlags;    /* 若有多个进程选中该SB，这个标志位将被设为SI_COLL（仅仅select使用）*/
    UCHAR       ucPadding[2];
}SELINFO_S;
#define        L_SELINFO_S        sizeof(SELINFO_S)


typedef struct tagSENDDATAIF
{
    ULONG           ulIfIndex;
    ULONG           ulSrcAddr;
}SENDDATAIF_S;
#define         L_SENDDATAIF_S  sizeof(SENDDATAIF_S)

typedef struct tagKEEPALIVESET
{
    USHORT usKeepintvl;       /* second */
    USHORT usKeepcount;       /* keepintvl's count */
}KEEPALIVESET_S;
#define         L_KEEPALIVE_S   sizeof(KEEPALIVESET_S)
/* end of mayun 2001-07-19 */


typedef struct tagSENDBY_IF_NEXTHOP
{
    ULONG           ulOutIfIndex;
    ULONG           ulNextHopAddr;     /* must be net-order */
}SENDBY_IF_NEXTHOP_S;
#define         L_SENDBY_IF_NEXTHOP_S  sizeof(SENDBY_IF_NEXTHOP_S)
/* end of mayun */

#define         L_SNDBYDSTMAC_S  sizeof(SNDBYDSTMAC_S)
#define         MAXMACLEN        8
typedef struct tagSNDBYDSTMAC
{
    UCHAR           ucDstMac[MAXMACLEN];
    ULONG           ulMacLen;
}SNDBYDSTMAC_S;

typedef struct  tagASYNSOCKET
{
    ULONG           ulQueueID;
    ULONG           ulPointer;
    task_t          ulWakeTaskID;
}ASYNSOCKET_S;
#define L_ASYNSOCKET_S sizeof(struct tagASYNSOCKET)

typedef struct  tagRECALLSOCKET
{
    ULONG (*so_pfCallBack)( CHAR *, VOID *ulValue );
    CHAR  *pszDataBuf;
    ULONG ulBufLen;
    ULONG ulUserData;  /* the data user set and will be return at ulValue */
}RECALLSOCKET_S;

#define L_RECALLSOCKET_S sizeof(RECALLSOCKET_S)

typedef union tagAsyncsock_un
{
    ASYNSOCKET_S    so_unstAsynSocket; /* this is set by the application, to wakeup application */
    RECALLSOCKET_S  so_unstCallBack;
}ASYNSOCKINFO_UN;
#define L_SO_UNASYNSOCK sizeof(ASYNSOCKINFO_UN)


#define HC_SEND_SUCCESS     0              /*发送成功*/
#define HC_NEED_UPDATE      1              /*报文首部需要update*/
#define HC_NOT_SUPPORT      2              /*不支持使用Head Cache发送*/
#define HC_SEND_FAIL        3              /*发送失败*/
/* add by l57500, 06/12/08. 在支持IR流发送时,如果发送时流缓存状态是HC_OK,返回该宏 */
#define HC_IR_SUCCESS       4              /* IR流发送缓存状态OK */

/* 指定socket获取TCP/UDP/RAWIP统计字段定义 */
typedef union unPerSocketStat_U
{
    TCP4PERSTAT_S   stPerTCP4Stat;          /* 基于socket id task id或 四元组统计TCP4 */
    UDP4PERSTAT_S   stPerUDP4Stat;          /* 基于socket id task id或 四元组统计UDP4 */
    RAWIP4PERSTAT_S stPerRAWIP4Stat;        /* 基于socket id task id或 四元组统计RAWIP4 */
    TCP6PERCONNSTAT_S stPerTCP6Stat;        /* 基于socket id task id或 四元组统计TCP6 */
}PERSOCKETSTAT_U;

/*struct tagPROTOSW;*/ /* by zhangyilong 27499 重复声明，去掉 */
typedef struct tagSOCKET
{
    SHORT               so_sType;           /* generic type, see socket.h */
    SHORT               so_sLinger;         /* time to linger while closing */
    ULONG               so_sOptions;        /* from socket call, see socket.h
                                             changed by yuyong&mayun 2002/10/30 for address overlap*/
    ULONG               so_sState;          /* internal state flags SS_*, below */
    VOID                (*so_pfSignal)();
    CHAR                *so_pPcb;           /* protocol control block */
    struct tagPROTOSW   *so_pProto;         /* protocol handle */
    struct tagSOCKET    *so_pHead;          /* back pointer to accept socket */
    struct tagSOCKET    *so_pQ0;            /* queue of partial connections */
    struct tagSOCKET    *so_pQ;             /* queue of incoming connections */
    SHORT               so_sQ0Len;          /* partials on so_q0 */
    SHORT               so_sQLen;           /* number of connections on so_q */
    SHORT               so_sQLimit;         /* max number queued connections */
    SHORT               so_sTimeO;          /* connection timeout */
    SHORT               so_sError;          /* error affecting connection */
    /* Added by fengjing209023 DTS2014032706863 本段调用了CLOSE后不需要再上报ASYN_CLOSE事件 */
    UCHAR               ucUsrCloseFlag;     /* 1、用来标记用户是否调了CLOSE,2、用来标记是否上报过PEERCLOSE */
    /* Addend end */
    UCHAR               ucPadding_1[1];
    task_t              so_tTaskId;         /* pgid for signals */
    ULONG               so_ulOobMark;       /* chars to oob mark */
    
    ULONG               ulKeepIdle;
    /* End of likaikun */
    
    KEEPALIVESET_S      so_stKeepalive;
    /* end of mayun */

    SENDDATAIF_S        so_stSendDataIf;
    
    SENDBY_IF_NEXTHOP_S so_stSendby_If_NextHop;

    SNDBYDSTMAC_S       so_stSndbyDstMac;

    ULONG               ulSrcAddr;      /* 网络字节序 */

    struct tagSOCKBUF
    {
        LONG        sb_ulCC;        /* actual chars in buffer */
        LONG        sb_ulHiWat;     /* max actual CHAR count */

        LONG        sb_ulLoWat;     /* low water mark */
        MBUF_S      *sb_pMb;        /* the mbuf chain */

        MBUF_S      *sb_pLastMbuf;  /*refer to the mbuf node next to never*/
        /*End of addition to improve search efficiency, 2002,04,19*/

        SELINFO_S   sb_stSel;       /* process selecting read/write */
        SHORT       sb_sFlags;      /* flags, see below */
        SHORT       sb_sTimeO;      /* timeout for read/write */
        ULONG       sb_ulIfIndex;   /* contain the ifnet inext of the latest sended or received datagram */
        /* we set read , connect, accept sleep in so_stRcv.sb_tTaskId,
        * and write,close in so_stSnd.sb_tTaskId */
        task_t      sb_tTaskId;     /* the task who sleep to read,write,connect,accept */

        /* Added for SOCKET HA */
        ULONG       sb_ulAddOrSubLen;     /* Save the length to be added or subtract from the socket buffer by ha */
        UCHAR       sb_ucIsInBackupQueue; /* Indicate whether this socket buf is backup queue */
        UCHAR       ucPadding_1[3];
    } so_stRcv, so_stSnd;

    SHORT so_sRefCnt;   /* the number of tasks to share this socket */
    UCHAR ucPadding_2[2];

    /* added for mpls vpn */
    ULONG           ulVrfIndex;
    ULONG           ulVrfIndex_Rcvd;

    /* mayun for zoneid */
    ULONG           ulZoneId;

    ASYNSOCKINFO_UN so_unAsynSock;

    LONG             so_iFd;            /* the file descriptor of this socket */
    struct tagTCB   *so_pTcb;           /* the tcb which this socket socket is in
                                         It is to falloc a fd in SO_IsConnected() for new socket(which is create by SO_NewConn ) */
#define so_stAsynSocket    so_unAsynSock.so_unstAsynSocket
#define so_stCallBack      so_unAsynSock.so_unstCallBack

    /* add for Socketdebug ,only use in UDP or RawIP for full drop .mayun. */
    ULONG so_ulDropPackets;

    /*供IPV4 UDP, RAW IP发送报文时填入目的地址，避免重复创建mbuf操作*/
    VOID *so_pAddr;

    VOID *pstHeadCacheInfo;/*指向Head Cache的信息结构*/
    struct tagSOCKET *pstHeadCacheSocketNext;/*指向下一个使用Head Cache的socket*/

    /* Added for SOCKET HA */
    ULONG so_ulBackupTimeStamp; /* Indicate the time when socket chain's backup msg of this
                                 * socket is put into socket backup queue.
                                 */
    UCHAR so_ucIsInBackupQueue; /* Indicate whether backup msg of socket modification
                                 * or socket chain is in socket backup queue
                                 */
    UCHAR ucPadding;        /* 保留字段,未使用 */
    USHORT usRcvVlanInfo;   /* 保存vlan tag信息,主机序 */

    SENDDATAIF_S so_stTrrtOutIfIndex;    /*trrt发送时指定的出接口*/

    PERSOCKETSTAT_U unSocketStat;        /* 指定socket获取TCP/UDP/RAWIP统计字段 */
}SOCKET_S;
#define L_SOCKET_S        sizeof(SOCKET_S)

typedef struct tagSOCKBUF     SOCKBUF_S;
#define L_SOCKBUF_S       sizeof(SOCKBUF_S)



typedef struct tagFILEOPS
{
    LONG   (*fo_pfRead)();
    LONG   (*fo_pfWrite)();
    LONG   (*fo_pfIoctl)();
    LONG   (*fo_pfSelect)();
    LONG   (*fo_pfClose)();
}FILEOPS_S;
#define        L_FILEOPS_S        sizeof(FILEOPS_S)

typedef struct tagFILE
{
    UCHAR    f_ucState;
    UCHAR    f_ucFlags;
    UCHAR    f_ucType;
    UCHAR    ucPadding;
    FILEOPS_S    *f_pOps;
    SOCKET_S    *f_pData;
}FILE_S;
#define        L_FILE_S    sizeof(FILE_S)

/*task control block*/
typedef struct tagTCB
{
    struct tagTCB   *tcb_pNext;
    task_t           tcb_tTaskId;    /* the task prossess this tcb */
    FILE_S          *tcb_pFile;     /* the files in this tcb */
    LONG            tcb_sMinVldIdx; /* the minimum valid file index */
                                    /* every time, we use the minimum valid
                                     *file index in this tcb, to optimize the
                                     *select function */
    LONG            tcb_sFileNum;   /* the number of files in tcb_pFile */
    LONG            tcp_sBusyFileNum;
    /*Begin BC3D01829 liangjicheng 2009-08-04*/
    LONG            tcb_usMaxSockId;
    /*End BC3D01829 liangjicheng 2009-08-04*/
}TCB_S;
#define L_TCB_S        sizeof(TCB_S)

/* Head Cache结点结构*/
/*moved by y36299 for SWFD10728 2005/06/21*/
/* Modified by X36317, 为保证ARM CPU四字节对齐，需在链路层首部预留一定长度，
   所以添加一个指针，用于指向真正的链路层首部, 2006/5/19 */

typedef struct tag_HeadCache
{
    DLL_NODE_S stHeadCacheNodeLink;   /* Head Cache结点顺序链表*/
    DLL_NODE_S stHeadCacheHashLink;   /* hash冲突结点链表*/
    SOCKET_S   *pSocket;              /* 指回相应的socket结构*/
    ULONG      ulFlag;                /* Head Cache标志，表明Head Cache的状态，具体请见下面的宏定义*/
    ULONG      ulSrcIP;               /* 源地址*/
    ULONG      ulDstIp;               /* 目的地址*/
    IN6ADDR_S  stSrcIP6;              /* IPv6 源地址   */
    IN6ADDR_S  stDstIP6;              /* IPv6 目的地址 */
    ULONG      ulIpPro;               /* 协议号*/
    ULONG      ulIfIndex;             /* 出接口索引*/
    ULONG      ulNextHop;             /* 下一跳的地址*/
    IN6ADDR_S stNextHop6;             /* IPv6 下一跳地址 */
    USHORT     usSrcPort;             /* 本地端口号*/
    USHORT     usDstPort;             /* 远端端口号*/
    UCHAR      *pucBlock;             /* 指向申请的报文首部内存*/
    UCHAR      *pucHead;              /* 报文首部，(UDP首部)+IP首部+链路层首部*/
    ULONG      ulHeadLen;             /* 报文首部长度*/
    ULONG      ulNormalSendTotal;     /* 统计走正常流程报文数 */
    ULONG      ulHCSendTotal;         /* 统计流发送成功报文数（走流发送流程报文数）*/
} HEADCACHE_ENTRY_S;

/* 流缓存头最大长度 */
#define HC_MAX_HDR   64
/*如下定义为避免VISP内部源文件同时包含sock_pub.h和tcpip_sock.h出现冲突而重定义*/
/* 为了解决测试组编译目标机文件时，此结构体冲突而定义一个编译宏:VISP_TEST
   默认情况下不定义此编译宏，对产品不会有影响 */
#ifndef VISP_TEST
typedef struct tagTCPIP_HEADCACHE_ENTRY
{
    ULONG      ulFlag;                /* Head Cache标志，表明Head Cache的状态，具体请见下面的宏定义*/
    ULONG      ulSrcIP;               /* 源地址*/
    ULONG      ulDstIp;               /* 目的地址*/
    IN6ADDR_S  stSrcIP6;              /* IPv6 源地址   */
    IN6ADDR_S  stDstIP6;              /* IPv6 目的地址 */
    ULONG      ulIpPro;               /* 协议号*/
    ULONG      ulIfIndex;             /* 出接口索引*/
    ULONG      ulNextHop;             /* 下一跳的地址*/
    IN6ADDR_S stNextHop6;             /* IPv6 下一跳地址 */
    USHORT     usSrcPort;             /* 本地端口号*/
    USHORT     usDstPort;             /* 远端端口号*/
    UCHAR      aucHead[HC_MAX_HDR];   /* 报文首部，(UDP首部)+IP首部+链路层首部*/
    ULONG      ulHeadLen;             /* 报文首部长度*/
    ULONG      ulNormalSendTotal;     /* 统计走正常流程报文数 */
    ULONG      ulHCSendTotal;         /* 统计流发送成功报文数（走流发送流程报文数）*/
}TCPIP_HEADCACHE_ENTRY_S;
#endif
typedef ULONG (*HEADCACHE_VLANCHECK_HOOK_FUNC)(IFNET_S *pIf);


typedef struct tagIP_SOCK_SH_CALLBACUP_SET_S
{
    VOID (*pfDebugToIC) ( ULONG ulInfoID, CHAR *szString );
    ULONG (*pfVOS_Que_Create)(CHAR *pQueName,ULONG ulQueDepth,ULONG ulFlags,ULONG *pulRetQueID);
    ULONG (*pfVOS_Que_GetName)(ULONG ulQueID, CHAR *pQueName);
    ULONG (*pfVOS_Que_Write)(ULONG ulQueID,UINTPTR *ulMsg,ULONG ulFlag, ULONG ulTimeOutInmillsec);
    ULONG (*pfVOS_Que_Read)(ULONG ulQueID,UINTPTR *ulRetMsg,ULONG ulFlag, ULONG ulTimeOutInmillsec);
    ULONG (*pfSOCK_SH_Que_GetMsgNum)(ULONG ulQueID, ULONG *pulRetMsgNum);
    ULONG (*pfSOCK_SH_Que_GetMaxNum)(ULONG ulQueID, ULONG *pulRetMaxNum);
    ULONG (*pfVOS_Ev_Write)(ULONG ulTaskID,ULONG ulEvents);
    ULONG (*pfVOS_Ev_Read)(ULONG ulEvents, ULONG *pulRetEvents,ULONG ulFlags, ULONG ulTimeOutInmillsec);
    ULONG (*pfGetHostName)(CHAR* pchName, LONG iLen);
}IP_SOCK_SH_CALLBACUP_SET_S;

typedef struct tagSOCK_MOD_INFO_S
{
    ULONG ulModID;
    ULONG ulSubModID;
    ULONG ulSKT_MAX_SOCK_N;
    ULONG ulHC_ENTRY_MAINTYPE;
    ULONG ulSKT_GLOBAL_SOCKET_EN;
    ULONG ulHC_IR_Enable_flag;     /* add by l57500,06/12/08. for support IR hc */
}SOCK_MOD_INFO_S;

typedef struct tagNewFreePort
{
    SLL_NODE_S stNode;      /* 全局链表节点 */
    USHORT     usPort;      /* 模块ID */
    USHORT     usReserve;   /* 保留 */
}NEW_FREE_PORT_S;

VOID SOCK_Init_RecentlyFreePortList();
ULONG SOCK_Add_NewFreePort(USHORT usPort);
ULONG SOCK_Search_FreePort(USHORT usPort, ULONG ulDelFlag);

extern SLL_S g_sllRecentlyFreePortList;
extern ULONG g_ulRandomPortEnhance;
extern USHORT g_usRandomPortStart;
#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
