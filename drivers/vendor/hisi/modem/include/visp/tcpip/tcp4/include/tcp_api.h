/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp_api.h
*
*  Project Code: VISPV1R7
*   Module Name: TCP_API  
*  Date Created: 2008-03-07
*        Author: zhengsenhuo(00104483)
*   Description:  
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*   2008-03-07  Zheng SenHuo           Creat the first version.
*   
*******************************************************************************/


#ifndef        _TCP_API_H
#define        _TCP_API_H

#ifdef    __cplusplus
extern    "C"{
#endif

/*[Debug Flag]*/
#define TCP_DEBUG_PACKET    0x01
#define TCP_DEBUG_TRANSA    0x10 
/* Extend debug function for MD5 option, 2002,09,25, zhangfeng */
#define TCP_DEBUG_MD5       0x0100

#define TCP_DEBUG_OFF   0
#define TCP_DEBUG_ON    1

/*TCP模块错误码*/
enum tagTCP_ErrCode
{
    TCP_FILTOK = VOS_OK,
    TCP_FAILURE,

    TCP_FILTNOTFOUND,      /* 2 没找到要删除的规则       */
    TCP_FILTNONE,          /* 3 规则表已经被清空了       */
    TCP_FILTTOOMUCH,       /* 4 规则表满                 */
    TCP_FILTINUSE,         /* 5 指定的规则已经被配置过了 */
    TCP_FILTADD,           /* 6 添加了一条规则           */
    TCP_COMP_NULL,         /* 7 TCP组件未注册            */
    TCP_PARA_ERR,          /* 8 输入参数范围非法         */
    TCP_PARATYPE_ERR,      /* 9 输入的类型非法           */
    TCP_INPUT_NULL_POINT,  /* 10 输入空指针 */
    TCP_ERR_NULL_INPCB,    /* 11 INPCB指针为空 */
    TCP_ERR_NULL_SOCKET,   /* 12 获取SOCKET控制块指针为空 */
    TCP_ERR_NULL_TCPCB,    /* 13 获取TCPCP结构指针为空 */
    TCP_ERR_GETSTAT_INPCB,     /* 14 根据四元组获取INPCB失败 */
    TCP_ERR_GETSTAT_SOCKETCB,  /* 15 根据四元组获取SOCKETCB失败 */
    TCP_ERR_GETSTAT_TCPCB,     /* 16 根据四元组获取TCPCB失败 */

    TCP_NETINFO_FINISH,        /* 17 TCPNetInfo 查询结束 */
    TCP_GETINPCB_WRONG,        /* 18 获取得到的INPCB为空 */

    /*Added by wangtong207740, 基于socket id 获取对应的tcp报文统计, 2012/9/5 */
    TCP_NOT_GLOBAL_SOCKET,      /* 19 不支持非全局SOCKET场景 */

    TCP_ERR_MAX,
};

/* Added by y00171195/p00193127 for TCPNetInfo TCP状态码 */
enum tagTCP_StateCode
{
    TCPSTATE_CLOSED        = 0,   /* closed */
    TCPSTATE_LISTEN        = 1,   /* listening for connection */
    TCPSTATE_SYN_SENT      = 2,   /* active, have sent syn */
    TCPSTATE_SYN_RECEIVED  = 3,   /* have send and received syn */
    TCPSTATE_ESTABLISHED   = 4,   /* established */
    TCPSTATE_CLOSE_WAIT    = 5,   /* rcvd fin, waiting for close */
    TCPSTATE_FIN_WAIT_1    = 6,   /* have closed, sent fin */
    TCPSTATE_CLOSING       = 7,   /* closed xchd FIN; await FIN ACK */
    TCPSTATE_LAST_ACK      = 8,   /* had fin and close; await FIN ACK */
    TCPSTATE_FIN_WAIT_2    = 9,   /* have closed, fin is acked */
    TCPSTATE_TIME_WAIT     = 10,  /* in 2*msl quiet wait after close */
};

/*set/get SYN/FIN/WIN*/
#define TCP_FUNSPEC_CHGKEEPVAL          0
#define TCP_FUNSPEC_CHGKEEPFINTIME      1
#define TCP_FUNSPEC_WINSIZE             2
#define TCP_FUNSPEC_ESTABLISHED         3


/* TCP统计结构 */
typedef struct tagTCPSTAT
{
    ULONG    ulAccepts;
    ULONG    ulClosed;
    ULONG    ulConnAttempt;
    ULONG    ulConnDrops;
    ULONG    ulConnects;
    ULONG    ulDelayedAck;
    ULONG    ulDrops;
    ULONG    ulKeepDrops;
    ULONG    ulKeepProbe;
    ULONG    ulKeepTimeOut;
    ULONG    ulPAWSDrop;
    ULONG    ulPCBCacheMiss;

    /* Added by LQZ, Mar-26 97. */
    ULONG    ulPersistDrops;

    ULONG    ulPersistTimeOut;
    ULONG    ulPredictionAck;
    ULONG    ulPredictionData;
    ULONG    ulRcvAckByte;
    ULONG    ulRcvAckPacket;
    ULONG    ulRcvAckTooMuch;
    ULONG    ulRcvDupAck;
    ULONG    ulRcvAfterClose;
    ULONG    ulRcvBadOff;
    ULONG    ulRcvBadSum;
    ULONG    ulRcvByte;
    ULONG    ulRcvDupByte;
    ULONG    ulRcvDupPacket;
    ULONG    ulRcvPacketAfterWnd;
    ULONG    ulRcvByteAfterWnd;
    ULONG    ulRcvPartDupByte;
    ULONG    ulRcvPartDupPacket;
    ULONG    ulRcvOutOrderPacket;
    ULONG    ulRcvOutOrderByte;
    ULONG    ulRcvShort;
    ULONG    ulRcvTotal;
    ULONG    ulRcvPacket;
    ULONG    ulRcvWndProbe;
    ULONG    ulRcvWndUpdate;
    ULONG    ulRexmtTimeOut;
    ULONG    ulRTTUpdated;
    ULONG    ulSegsTimed;
    ULONG    ulSndByte;
    ULONG    ulSndControl;
    ULONG    ulSndPacket;
    ULONG    ulSndProbe;
    ULONG    ulSndRexmtByte;
    ULONG    ulSndAcks;
    ULONG    ulSndRexmtPacket;
    ULONG    ulSndTotal;
    ULONG    ulSndErr;

    ULONG    ulSndRST;   /* Added for MIB-II */

    ULONG    ulSndUrgent;
    ULONG    ulSndWndUpdate;
    ULONG    ulTimeOutDrop;

    /* added by mayun to distinguish con_estab timer and keepalive timer */
    ULONG    ulKeepAliveTimeOut;  /*路由器保活定时器超时次数*/
    ULONG    ulKeepAliveDrops;    /*保活探测失败丢弃连接次数*/

    /* TCP with MD5 authentication, zhangfeng, 2002,07,20 */
    ULONG    ulMd5Permit;
    ULONG    ulMd5Deny;
    ULONG    ulMd5Output;
    /* TCP with MD5 authentication, zhangfeng, 2002,07,20 */

    /* Added for tcp ha */
    ULONG ulSeqRcvNxtRevised; /* Times that seqRcvNxt has been revised */

    /* Added for notification failure */
    ULONG    ulNotifyReadFailed;
    ULONG    ulNotifyWriteFailed;
    ULONG    ulNotifyPeerCloseFailed;
    ULONG    ulNotifyKeepLiveDownFailed;
    ULONG    ulNotifyConnectFailed;

    /* Added by fengjing209023 cookie维测 */
    ULONG    ulCookieRcvdSyn;       /* cookie打开时收到的SYN报文数 */
    ULONG    ulCookieRspdSynAck;    /* cookie打开时回的SYNACK报文数 */
    ULONG    ulCookieRcvdAck;       /* cookie打开时收到的ACK报文数 */
    ULONG    ulCookiePassedAck;     /* cookie打开时校验成功的ACK报文数 */
    ULONG    ulCookieTimoAck;       /* cookie打开时校验失败的ACK报文数(超时) */
    ULONG    ulCookieBadMssAck;     /* cookie打开时校验失败的ACK报文数(MSS索引不对) */
    ULONG    ulCookieOtherPkt;      /* cookie打开时监听socket收到的其他报文 */
    ULONG    ulUsrCookieOnWhenTIMO; /* cookie打开时收到的ACK报文超时。但是产品COOKIE打开了 */
    
    ULONG    ulRecvMemDrop;        /* 内存不足丢弃的报文数 */
} TCPSTAT_S;

/* 基于socket id,task id和四元组获取统计信息输入参数数据结构 */
typedef struct tagTCP4CONN_S
{
    ULONG    ulVrfIndex;    /* VRF索引*/
    ULONG    ulLAddr;       /* 本端地址(主机序) */
    ULONG    ulFAddr;       /* 对端地址(主机序) */
    ULONG    ulLPort;       /* 本端端口号 */
    ULONG    ulFPort;       /* 对端端口号 */
    ULONG    ulSocketID ; /*在socket id指定时，以socket查找统计信息；*/
    /* 否则用四元组，但因为TCPDORP后INPCB将会删除，因此在该情况必然要用socketid获取 */
    ULONG    ulTaskID;      /* 任务ID */
}TCP4CONN_S;

/* 基于socket id task id 或四元组的TCP统计结构 */
typedef struct tagTCP4PERSTAT
{
    TCP4CONN_S stTcp4Conn; /* 实际获取的socket id task id 和四元组*/    
    
    ULONG    ulAccepts;
    ULONG    ulConnAttempt;
    ULONG    ulConnDrops;
    ULONG    ulConnects;
    ULONG    ulDelayedAck;
    ULONG    ulDrops;
    ULONG    ulKeepDrops;
    ULONG    ulKeepProbe;
    ULONG    ulKeepTimeOut;
    ULONG    ulPAWSDrop;

    ULONG    ulPersistDrops;
    ULONG    ulPersistTimeOut;
    ULONG    ulPredictionAck;
    ULONG    ulPredictionData;
    ULONG    ulRcvAckByte;
    ULONG    ulRcvAckPacket;
    ULONG    ulRcvAckTooMuch;
    ULONG    ulRcvDupAck;
    ULONG    ulRcvAfterClose;
    ULONG    ulRcvByte;
    ULONG    ulRcvDupByte;
    ULONG    ulRcvDupPacket;
    ULONG    ulRcvPacketAfterWnd;
    ULONG    ulRcvByteAfterWnd;
    ULONG    ulRcvPartDupByte;
    ULONG    ulRcvPartDupPacket;
    ULONG    ulRcvOutOrderPacket;
    ULONG    ulRcvOutOrderByte;
    ULONG    ulRcvTotal;
    ULONG    ulRcvPacket;
    ULONG    ulRcvWndProbe;
    ULONG    ulRcvWndUpdate;
    ULONG    ulRexmtTimeOut;
    ULONG    ulRTTUpdated;
    ULONG    ulSegsTimed;
    ULONG    ulSndByte;
    ULONG    ulSndControl;
    ULONG    ulSndPacket;
    ULONG    ulSndProbe;
    ULONG    ulSndRexmtByte;
    ULONG    ulSndAcks;
    ULONG    ulSndRexmtPacket;
    ULONG    ulSndTotal;
    ULONG    ulSndErr;

    ULONG    ulSndRST;   /* Added for MIB-II */
    ULONG    ulSndSYN;   /* Added for Qos Info */
    ULONG    ulSndFIN;   /* Added for Qos Info */

    ULONG    ulSndUrgent;
    ULONG    ulSndWndUpdate;
    ULONG    ulTimeOutDrop;

    ULONG    ulKeepAliveTimeOut;  /*路由器保活定时器超时次数*/
    ULONG    ulKeepAliveDrops;    /*保活探测失败丢弃连接次数*/

    ULONG    ulMd5Permit;
    ULONG    ulMd5Deny;
    ULONG    ulMd5Output;

    /*socket 缓冲区信息*/
    ULONG    ulSndHiWat ; /*发送缓冲区高水位*/
    ULONG    ulRcvHiWat ; /*接收缓冲区高水位*/
    ULONG    ulSndCC ; /*发送缓冲区中实际数据 */
    ULONG    ulRcbCC ; /*接收缓冲区中实际数据 */

    ULONG    ulSubSOTimeODrops;      /* number of subsocket droped because of timeout */
    ULONG    ulSubSoBacklogDrops;    /* number of subsocket droped because of exceeding backlog */  
} TCP4PERSTAT_S;

typedef struct tagTcpSockInfo
{
    ULONG    ulLocalAddr;          /*本端地址 主机顺序*/
    ULONG    ulPeerAddr;           /*对端地址 主机顺序*/
    USHORT   usLocalPort;          /*本端端口号 主机顺序*/
    USHORT   ulPeerPort;           /*对端端口号 主机顺序*/

    ULONG    so_sOptions;            /*socket选项*/
    ULONG    so_sState;              /*tcp 状态*/

    SHORT    so_sLinger;             /*Linger 值 */
    SHORT    so_sQ0Len;         /* 未处理的链接个数*/
    SHORT    so_sQLen;          /* 已经连接个数 */
    SHORT    so_sQLimit;        /* tcp 最大连接个数 */

    ULONG    ulDelayedAck;        /*延迟发送的ACK报文数。*/
    ULONG    ulRcvAckByte;        /*接收的字节数*/
    ULONG    ulRcvAckPacket;      /*收到的ACK报文数。*/
    ULONG    ulRcvAfterClose;     /*关闭后接收的报文个数*/    
    ULONG    ulRcvPacketAfterWnd; /*报文落在接收窗口外数*/
    ULONG    ulRcvPartDupPacket;  /*部分重复报文数。*/
    ULONG    ulRcvOutOrderPacket; /*接收乱序报文数*/
    ULONG    ulRcvTotal;          /*总计收到报文数*/
    ULONG    ulRcvPacket;         /*按顺序到达报文数。*/
    ULONG    ulRexmtTimeOut;      /*重传定时器超时次数*/
    ULONG    ulSndByte;           /*发送的报文字节数*/
    ULONG    ulSndPacket;         /*发送的数据报文*/
    ULONG    ulSndAcks;           /*发送ACK报文数*/
    ULONG    ulSndRexmtPacket;    /*报文重发数。*/
} TCP_SOCK_INFO_S;



#define TCP_MAXFILTNUM      5

typedef struct tagTCPFILT
{
    ULONG   ulTaskId;        /* 存放用户设置的过滤条件中的任务ID   */
    ULONG   ulSockId;        /* 存放用户设置的过滤条件中的套接口号 */
}TCPFILT_S;

typedef struct tagTCPDBUGFILTRD
{       
    TCPFILT_S stTCPDbugFilt[TCP_MAXFILTNUM];
    ULONG          ulFiltCnt;       /* 当前过滤条件的个数 */
}TCPDBUGFILTRD_S;


typedef ULONG   TCP_SEQ;

/* TCP头数据结构 */
typedef struct tagTCPHDR
{
    USHORT  usSrcPort;
    USHORT  usDstPort;
    TCP_SEQ                 seqSeqNumber;
    TCP_SEQ                 seqAckNumber;
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR   ucX2:4,
                    ucOffset:4;
#else
    UCHAR   ucOffset:4, /* warning:nonstandard extension used : bit field types other than LONG. */
                    ucX2:4;     /* warning:nonstandard extension used : bit field types other than LONG. */
#endif
    UCHAR   ucFlags;
    USHORT      usWnd;
    USHORT      usCheckSum;
    USHORT      usUrgentPoint;
} TCPHDR_S;

typedef struct tagTCPIP_TCPNETINFO_S
{
    ULONG   ulTaskId;       /* 任务ID     */
    ULONG   ulSrcIp;        /* 主机字节序 */
    ULONG   ulDstIp;        /* 主机字节序 */
    USHORT  usSrcPort;
    USHORT  usDestPort;
    USHORT  usState;
    USHORT  usRes;
    /*Added by limin00188004, 获取网络状态时输出socket所绑定的VRF索引, 2012/9/28   问题单号:S.VRF.02.01 */
    ULONG   ulVrfIndex;
    /* End of Added by limin00188004, 2012/9/28   问题单号:S.VRF.02.01 */
}TCPIP_TCPNETINFO_S;

/* COOKIE密钥, 136个字节长度 */  
typedef ULONG ( *gpfTCPIPGetCookieSecret)(ULONG* pulCookieValue, ULONG ulBytesNum); 

/* 获取产品COOKIE开关钩子，返回1表示产品打开，0表示产品关闭*/
typedef ULONG ( *gpfTCPIPGetUsrCookieSwitch)(ULONG* pulCookieSwitch);

/* Structure used as input parameter for hook function to notify TCP MD5
   configuration. */
typedef struct tagTCP4MD5CFGNOTIFY 
{
    ULONG ulTaskId;         /* vos task id */ 
    ULONG ulVrfIndex;       /* vrf index */ 
    ULONG ulSocketId;       /* socket id */ 
    ULONG ulLocalAddr;      /* The end of the address: host order */ 
    ULONG ulRemoteAddr;     /* Peer address: host order */ 
    USHORT usLocalPort;     /* local port: host order */ 
    USHORT usRemotePort;    /* peer port: host order */ 
    ULONG ulOper;           /* Add: 1 or Del: 0 */ 
} TCP4MD5CFGNOTIFY_S;
/* Structure used as input parameter for hook function to notify TCP MD5
   authentication result. */
typedef struct tagTCPMD5AUTHRESULT 
{
    ULONG ulTaskId;         /* vos task id */ 
    ULONG ulVrfIndex;       /* vrf index */ 
    ULONG ulSocketId;       /* socket id */ 
    ULONG ulLocalAddr;      /* The end of the address: host order */ 
    ULONG ulRemoteAddr;     /* Peer address: host order */ 
    USHORT usLocalPort;     /* local port: host order */ 
    USHORT usRemotePort;    /* peer port: host order */ 
    ULONG ulResult;         /* permit: 1 or deny: 0 */ 
} TCP4MD5AUTHRESULTNOTIFY_S; 
/* Function pointer to hold the pointer to hook function for notifying TCP MD5
   configuration. */
typedef ULONG ( *gpfTCPIPMd5CfgNotifyHook)(TCP4MD5CFGNOTIFY_S* pstCfgPara);
/* Function pointer to hold the pointer to hook function for notifying TCP MD5
   authentication result. */
typedef ULONG ( *gpfTCPIPMd5AuthNotifyHook)(TCP4MD5AUTHRESULTNOTIFY_S* pstAuthResult);

/*******************************************************************************
*    Func Name: TCPIP_ShowTcpStatistic
*  Description: 显示TCP4统计信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID TCPIP_ShowTcpStatistic(VOID);
/****************************************************************************
*    Func Name: TCPIP_ShowTCPCB()
*  Description: 显示TCP4控制块信息
*        Input: VOID *pAddress: TCP控制块所在的地址
*       Output: 无
*       Return: 无
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-9  Zheng Sen Huo (00104483)         Creat the first version.
*
*******************************************************************************/
VOID TCPIP_ShowTCPCB(VOID *pAddress);
/*******************************************************************************
*    Func Name: TCPIP_ShowTCP
*  Description: 显示TCP4的连接信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID TCPIP_ShowTCP(VOID);
/*******************************************************************************
*    Func Name: TCPIP_GetTCPStat
*  Description: 获得TCP4组件的统计信息
*        Input: 
*       Output: TCPSTAT_S *pstTCPStat:指向结构体TCPSTAT_S的指针。其所指向的内存由用户负责申请和释放
*       Return: VOS_OK  成功
*               VOS_ERR 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_GetTCPStat(TCPSTAT_S *pstTCPStat);
/*******************************************************************************
*    Func Name: TCPIP_ClrTCPStat
*  Description: 清空TCP4组件的统计信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID TCPIP_ClrTCPStat(VOID);
/*******************************************************************************
*    Func Name: TCPIP_NoDebugTCPAll
*  Description: 清除TCP4 DEBUG标记并将过滤值清零
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID TCPIP_NoDebugTCPAll(VOID);
/*******************************************************************************
*    Func Name: TCPIP_DebugTCPAll
*  Description: 打开所有TCP4 DEBUG开关
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID TCPIP_DebugTCPAll(VOID);
/****************************************************************************
*    Func Name: TCPIP_SetTCPDbgFilter()
*  Description: 打开/关闭指定socket id和task id的TCP4 debug开关
*        Input: ULONG ulFlag        命令字
*               ULONG ulDbgFilterId 过滤类型
*               ULONG ulTaskId      socket所在的任务ID
*               ULONG ulSockId      套接字ID
*       Output: 无
*       Return: TCP_FILTOK          操作成功
*               TCP_FILTNOTFOUND    没找到要删除的规则
*               TCP_FILTNONE        规则表已经被清空了
*               TCP_FILTTOOMUCH     规则表满
*               TCP_FILTINUSE       指定的规则已经被配置过了
*               TCP_FILTADD         添加了一条规则
*               VOS_ERR             操作失败
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-9  Zheng Sen Huo (00104483)         Creat the first version.
*
*******************************************************************************/
LONG TCPIP_SetTCPDbgFilter(ULONG ulFlag, ULONG ulDbgFilterId, ULONG ulTaskId, ULONG ulSockId);
/*******************************************************************************
*    Func Name: TCPIP_SetTCPRespondQuench
*  Description: 设置是否响应TCP源抑制报文
*        Input: ULONG ulSetYes:0  不响应   非0  响应
*       Output: 无
*       Return: VOS_OK  成功
*               VOS_ERR 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
ULONG TCPIP_SetTCPRespondQuench(ULONG ulSetYes);
/****************************************************************************
*    Func Name: TCPIP_GetTCPParam()
*  Description: 获取TCP4相关全局变量值
*        Input: ULONG ulType     全局变量类型
*               
*       Output: ULONG * pulValue 返回当前全局变量的值
*       Return: 无
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-9  Zheng Sen Huo (00104483)         Creat the first version.
*
*******************************************************************************/
VOID TCPIP_GetTCPParam(ULONG ulType, ULONG * pulValue);
/****************************************************************************
*    Func Name: TCPIP_SetTCPParam()
*  Description: 设置TCP4相关全局变量值
*        Input: ULONG ulType     全局变量类型
*               ULONG * pulValue 要设置的值
*       Output: 无
*       Return: VOS_OK          操作成功
*               VOS_ERR         正在倒换或平滑
*               TCP_PARAMERROR  参数错误
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-9  Zheng Sen Huo (00104483)         Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_SetTCPParam(ULONG ulType, ULONG ulValue);
/*******************************************************************************
*    Func Name: TCPIP_GetTCPDbgFilter
*  Description: 获取TCP4 DEBUG标识和过滤相关值,不包括MD5过滤信息
*        Input: ULONG *pulDebugFlag:返回TCP Debug标识
*               TCPDBUGFILTRD_S *pstPacketFilter:返回的TCP报文过滤值
*               TCPDBUGFILTRD_S *pstEventFilter:返回的TCP状态过滤值
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
VOID TCPIP_GetTCPDbgFilter(ULONG *pulDebugFlag, TCPDBUGFILTRD_S *pstPacketFilter, TCPDBUGFILTRD_S *pstEventFilter);

/*******************************************************************************
*    Func Name: TCPIP_GetTCPDbgFilterWithMd5
* Date Created: 2009-12-2
*       Author: zhangchunyu(62474)
*  Description: 获取TCP4 DEBUG标识和过滤相关值,包括MD5过滤信息
*        Input: ULONG *pulDebugFlag:返回TCP Debug标识
*               TCPDBUGFILTRD_S *pstPacketFilter:返回的TCP报文过滤值
*               TCPDBUGFILTRD_S *pstEventFilter:返回的TCP状态过滤值
*               TCPDBUGFILTRD_S *pstMD5Filter:返回设置了的MD5
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-2    zhangchunyu(62474)     Create the first version.
*
*******************************************************************************/
VOID TCPIP_GetTCPDbgFilterWithMd5(ULONG *pulDebugFlag, 
                                  TCPDBUGFILTRD_S *pstPacketFilter,
                                  TCPDBUGFILTRD_S *pstEventFilter,
                                  TCPDBUGFILTRD_S *pstMD5Filter);

typedef ULONG (*TCPINPUT_HOOK_FUNC)( MBUF_S* pMbuf );
ULONG TCPIP_RegFuncTCPInputHook( TCPINPUT_HOOK_FUNC pfFuncHook );
extern TCPINPUT_HOOK_FUNC g_TCP_Input_HookFunc;

#define TCP_NOT_PROCESSED_BY_INTERMEDIATE              0 
/* intermediate found the packet has Error, Stack will Destroy the Packet */
#define TCP_INTER_PROCESS_ERROR                        1
/* Intermediate Processing will continue processing and will own the packet
 * PP do not need to process the packet any more */
#define TCP_PROCESSED_BY_INTERMEDIATE                  2

/*******************************************************************************
*    Func Name: TCPIP_GetPerTcp4ConnStats
* Date Created: 2009-12-25
*       Author: Gexianjun/h00121208
*  Description: 指定socket id, task id或指定四元组，VRF获取指定的TCP统计信息
*        Input: TCP4CONN_S *pstConnInfo:    获取指定TCP Socket输入参数
*       Output: TCP4PERSTAT_S *pstRetStats: 获取指定的TCP统计信息
*       Return: 成功:VOS_OK;失败:错误码
*      Caution: 如果socket的模式是全局socket,根据socket id获取tcp统计信息,则不需要指定task id;
*               否则需要同时指定socket id和task id。本接口获取TCP统计信息输入参数必须配对才能正确
*               获取:输入参数可以为socket id + task id去获取;或输入参数为四元组+vrf去获取；
*               也可以同时指定这两种组合。获取方法是先根据socket id +task id去获取,
*               如果获取失败,再根据四元组+vrf去获取。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-25   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPerTcp4ConnStats(TCP4CONN_S *pstConnInfo, TCP4PERSTAT_S *pstRetStats);

/*******************************************************************************
*    Func Name: TCPIP_ResetPerTcp4ConnStats
* Date Created: 2009-12-25
*       Author: Gexianjun/h00121208
*  Description: 指定socket id, task id或指定四元组，VRF清除指定的TCP统计信息
*        Input: TCP4CONN_S *pstConnInfo: 清除指定TCP Socket输入参数
*       Output: 
*       Return: 成功:VOS_OK;失败:错误码
*      Caution: 如果socket的模式是全局socket,根据socket id清除tcp统计信息,则不需要指定task id;
*               否则需要同时指定socket id和task id。本接口清除TCP统计信息输入参数必须配对才能正确
*               清除:输入参数可以为socket id + task id去清除;或输入参数为四元组+vrf去清除；
*               也可以同时指定这两种组合。清除方法是先根据socket id +task id去查找tcp socket, 如果
*               查找成功,则清除指定的该tcp socket的统计信息,如果查找失败,再根据四元组+vrf去查找tcp socket,
*               如果查找成功,则清除指定的该tcp socket的统计信息。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-25   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_ResetPerTcp4ConnStats(TCP4CONN_S *pstConnInfo);

/*******************************************************************************
*    Func Name: TCPIP_OpenTcpNetInfo
* Date Created: 2011-11-3
*       Author: y00171195/p00193127
*  Description: 打开查询句柄
*        Input: 
*       Output: pulWaitlist:Waitlist句柄
*       Return: 成功:VOS_OK;失败:错误码
*      Caution: 只有查询句柄打开成功才能进行下一步TCP网络连接信息查询操作。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-3   y00171195/p00193127     Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenTcpNetInfo(UINTPTR *pulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_GetTcpNetInfo
* Date Created: 2011-11-3
*       Author: y00171195/p00193127
*  Description: 获取TCP网络连接信息
*        Input: pulWaitlist:Waitlist句柄
*       Output: TCPIP_TCPNETINFO_S*pstNetInfo网络连接信息
*       Return: 成功:VOS_OK;失败:错误码
*      Caution: 只有查询句柄打开成功才能进行下一步TCP网络连接信息查询操作,每次查询获取一个连接信息,该函数
*               在打开查询句柄后可以进行多次查询以返回所有的TCP网络连接信息。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-3   y00171195/p00193127     Create
*
*******************************************************************************/
extern ULONG TCPIP_GetTcpNetInfo(UINTPTR ulWaitlist, TCPIP_TCPNETINFO_S *pstNetInfo);

/*******************************************************************************
*    Func Name: TCPIP_CloseTcpNetInfo
* Date Created: 2011-11-3
*       Author: y00171195/p00193127
*  Description: 关闭查询句柄
*        Input: ulWaitlist:Waitlist句柄
*       Output: 
*       Return: 成功:VOS_OK;失败:错误码
*      Caution: 在查询结束后或者获取TCP网络连接信息失败时需要关闭查询句柄。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-3   y00171195/p00193127     Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseTcpNetInfo(UINTPTR ulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_GetTcpInfo
* Date Created: 2012-09-05
*       Author: wangtong207740
*  Description: 
*        Input: ULONG ulSocketId:
*               TCP_SOCK_INFO_S *pstTcpInfo:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-05   wangtong207740          Create
*
*******************************************************************************/
ULONG TCPIP_GetTcpInfo(ULONG ulSocketId, TCP_SOCK_INFO_S *pstTcpInfo);

/*******************************************************************************
*    Func Name: TCPIP_RegTcpCookieSecret
* Date Created: 2014-5-13
*       Author: f00209023
*  Description: 注册获取TCP COOKIE的密钥钩子
*        Input: gpfTCPIPGetCookieSecret  pfGetCookieHook
*       Return: VOS_OK:
*      Caution: 入参为空则注册失败，否则成功，在VISP初始化之前注册
*         约束: 产品若要使用cookie特性，则必须注册该钩子。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-5-13   f00209023                Create
*
*******************************************************************************/
ULONG TCPIP_RegTcpCookieSecret(gpfTCPIPGetCookieSecret  pfGetCookieHook);
/*******************************************************************************
*    Func Name: TCPIP_RegGetUsrCookieSwitch
* Date Created: 2014-5-13
*       Author: f00209023
*  Description: 注册获取产品COOKIE开关的钩子
*        Input: gpfTCPIPGetUsrCookieSwitch pfGetUserCookieSwitch
*       Return: VOS_OK:
*      Caution: 入参为空则注册失败，否则成功，在VISP初始化之前注册
*         约束: 产品若要使用cookie特性，则必须注册该钩子。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-5-13   f00209023                Create
*
*******************************************************************************/
ULONG  TCPIP_RegGetUsrCookieSwitch(gpfTCPIPGetUsrCookieSwitch pfGetUserCookieSwitch);

ULONG TCPIP_RegTcp4Md5CfgNotifyHook(gpfTCPIPMd5CfgNotifyHook pfCfgNotify);

ULONG  TCPIP_RegTcp4Md5AuthNotifyHook(gpfTCPIPMd5AuthNotifyHook pfAuthNotify);
#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

