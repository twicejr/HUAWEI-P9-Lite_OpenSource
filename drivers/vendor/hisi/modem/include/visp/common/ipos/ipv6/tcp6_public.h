/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              tcp6_public.h
*
*    Project Code:  VRP5.0
*    Module Name: IP6 TCP6
*    Create Date:   2006/04/11
*    Author:        SandeepMN
*    Description:   To define all TCP6 public data structures and definitions
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-04-11    SandeepMN    Created for including all public definitions in-
*                                               this file, for IPOSV1R1
************************************************************************/

#ifndef _TCP6_PUBLIC_H
#define _TCP6_PUBLIC_H

#ifdef  __cplusplus
extern "C"{
#endif

/*MAX_INT to arm allign the enums*/
#define IP6_TCP6_MAX_ENUM_VALUE            0xFFFFFFFF

/*TCP6 statistics type definition*/
#define ACTIVE_OPEN 0
#define PASSIVE_OPEN 1
#define ATTEMPT_FAILS 2
#define EST_RESET 3
#define IN_SEG     4
#define OUT_SEG 5
#define RETRANS_SEG 6
#define IN_ERR    7
#define OUT_RSTS 8
#define TCP6_SEND_SPACE 9
#define TCP6_SYN_WAIT 10
#define TCP6_FIN_WAIT   11

#define HC_IN_SEG 12
#define HC_OUT_SEG 13

/*Return value definition in TCP6_ProDbugFilter */
#define TCP6_MAXFILTNUM 5
#define TCP6_FILTOK        0
#define TCP6_FILTINUSE     1
#define TCP6_FILTTOOMUCH   2
#define TCP6_FILTNOTFOUND  3
#define TCP6_FILTNONE      4
#define TCP6_FILTADD       5


#define TCP6_SOCK_ERROR 6
#define TCP6_ERRORPACKET      99

/* Added by Saravanya for handling semaphore lock failure condition */
#define TCP6_ERR_SEMOP_ACQUIRELOCK_FAIL 7

#define TCP6_DEBUG_PACKET    0x01
#define TCP6_DEBUG_TRANSA    0x10

/*Return value definition of TCP6_Get_Object_NextTCP6Conn*/
#define TCP6_LAST_CB 5

/* TCP connection state definations. */

#define    TCP6S_CLOSED          0    /* closed */
#define    TCP6S_LISTEN          1    /* listening for connection */
#define    TCP6S_SYN_SENT        2    /* active, have sent syn */
#define    TCP6S_SYN_RECEIVED    3    /* have send and received syn */

#define    TCP6S_ESTABLISHED     4    /* established */
#define    TCP6S_CLOSE_WAIT      5    /* rcvd fin, waiting for close */

#define    TCP6S_FIN_WAIT_1      6    /* have closed, sent fin */
#define    TCP6S_CLOSING         7    /* closed xchd FIN; await FIN ACK */
#define    TCP6S_LAST_ACK        8    /* had fin and close; await FIN ACK */
#define    TCP6S_FIN_WAIT_2      9    /* have closed, fin is acked */
#define    TCP6S_TIME_WAIT      10    /* in 2*msl quiet wait after close */

#define    TCP6_NSTATES          11
#define    TCP6_DELTCB           11   /* for SNMP */

/* Constant defination for TCP-IP header flags */
#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PUSH 0x08
#define TH_ACK  0x10
#define TH_URG  0x20

#define TCP6_SNDRCVSPACE  8 * 1024

/*
 * Definitions of the TCP timers.  These timers are counted
 * down PR_SLOWHZ times a second.
 */
#define    TCP6T_NTIMERS    4

#define    TCP6T_REXMT        0    /* retransmit                 */
#define    TCP6T_PERSIST      1    /* retransmit persistance     */
#define    TCP6T_KEEP         2    /* keep alive                 */
#define    TCP6T_2MSL         3    /* 2*msl quiet time timer     */

/* Time constants */
#define    TCP6TV_MSL        (30*PR_SLOWHZ)         /****** 段的最长时间maximum segment lifetime   ******/
#define    TCP6TV_SRTTBASE    0                     /****** 基础聚拢时间base roundtrip time        ******/
#define    TCP6TV_SRTTDFLT   (2*PR_SLOWHZ)          /****** 默认聚拢时间ssumed roundtrip time      *****/ 

#define    TCP6TV_PERSMIN    (5*PR_SLOWHZ)          /****** 转发持久性retransmit persistance       *****/
#define    TCP6TV_PERSMAX    (60*PR_SLOWHZ)         /****** 最大持续间隔maximum persist interval   *****/

#define    TCP6TV_KEEP_INIT    (75*PR_SLOWHZ)  		/****** 目礽initial connect keep alive         *****/ 
#define    TCP6TV_KEEP_IDLE    (120*60*PR_SLOWHZ)   /****** 目礵default time before probing         ****/
#define    TCP6TV_KEEPINTVL    (75*PR_SLOWHZ)       /****** 目礵default probe interval             *****/
#define    TCP6TV_KEEPCNT      8                    /****** 目祄max probes before drop             *****/ 

#define    TCP6TV_MIN         (1*PR_SLOWHZ)    		/****** 目祄minimum allowable value           ******/ 
#define    TCP6TV_REXMTMAX    (64*PR_SLOWHZ)   		/****** 目祄max allowable REXMT value         ******/

#define    TCP6_LINGERTIME    120        			/****** 目祃linger at most 2 minutes          ******/ 

#define    TCP6_MAXRXTSHIFT    12        			/****** 目祄maximum retransmits               ******/

#ifdef    TCPTIMERS
CHAR *psTCPTimers[] =
    { "REXMT", "PERSIST", "KEEP", "2MSL" };

#endif


typedef ULONG   TCP6_SEQ;

#ifdef COMPILING_IR_IPV6_CORE
#pragma pack(1)
#endif

/*TCP6 Header*/
typedef struct tagTCP6HDR
{
    USHORT usSrcPort;
    USHORT usDstPort;
    TCP6_SEQ seqSeqNumber;
    TCP6_SEQ seqAckNumber;
#if (VRP_LITTLE_ENDIAN == VRP_YES)
    UCHAR ucX2:4,
    ucOffset:4;
#else
    UCHAR ucOffset:4, /* warning:nonstandard extn used :
                         bit field types other than LONG. */
    ucX2:4;             /* warning:nonstandard extn used : bit
                         field types other than LONG. */
#endif
    UCHAR ucFlags;
    USHORT usWnd;
    USHORT usCheckSum;
    USHORT usUrgentPoint;
} TCP6HDR_S;

/*TCP6 Pseudo header*/
/*It comprises of the TCP6 header and the IPV6 base header.
  It is used by TCP6 solely for the purpose of Checksum computation*/
typedef struct tagTCP6IP6HDR
{
    IP6_S        stIp6Hdr;
    TCP6HDR_S    stTcp6Hdr;
} TCP6IP6HDR_S;

/* Abbreviation macro for TCP6-IP6 header */
#define ucIH6Ver             stIp6Hdr.ip6_ucVer
#define ulIH6Flow            stIp6Hdr.ip6_ulFlow
#define ucIH6HLim            stIp6Hdr.ip6_ucHLim
#define ucIH6Protocol        stIp6Hdr.ip6_ucNxtHdr
#define sIH6Len              stIp6Hdr.ip6_usPLen
#define adrIH6Src            stIp6Hdr.ip6_stSrc
#define adrIH6Dst            stIp6Hdr.ip6_stDst

#define usTHSrc6Port         stTcp6Hdr.usSrcPort
#define usTHDst6Port         stTcp6Hdr.usDstPort
#define seqTH6Seq            stTcp6Hdr.seqSeqNumber
#define seqTH6Ack            stTcp6Hdr.seqAckNumber
#define ucTH6X2              stTcp6Hdr.ucX2
#define ucTH6Offset          stTcp6Hdr.ucOffset
#define ucTH6Flags           stTcp6Hdr.ucFlags
#define usTH6Wnd             stTcp6Hdr.usWnd
#define usTH6CheckSum        stTcp6Hdr.usCheckSum
#define usTH6UrgentPoint     stTcp6Hdr.usUrgentPoint



/*TCP6 statistics*/
typedef struct tagTCP6STAT
{
    DULONG   dulHCInSegs;
    DULONG   dulHCOutSegs;
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
    ULONG    ulSndRST;
    ULONG    ulSndUrgent;
    ULONG    ulSndWndUpdate;
    ULONG    ulTimeOutDrop;
    ULONG    ulKeepAliveTimeOut;  /*路由器保活定时器超时次数*/
    ULONG    ulKeepAliveDrops;    /*保活探测失败丢弃连接次数*/

    ULONG   ulExtPreProc;

    /* Added by fengjing209023 cookie维测 */
    ULONG    ulCookie6RcvdSyn;      /* cookie6打开时收到的SYN报文数 */
    ULONG    ulCookie6RspdSynAck;   /* cookie6打开时回的SYNACK报文数 */
    ULONG    ulCookie6RcvdAck;      /* cookie6打开时收到的ACK报文数 */
    ULONG    ulCookie6PassedAck;    /* cookie6打开时校验成功的ACK报文数 */
    ULONG    ulCookie6TimoAck;      /* cookie6打开时校验失败的ACK报文数(超时) */
    ULONG    ulCookie6BadMssAck;    /* cookie6打开时校验失败的ACK报文数(MSS索引不对) */
    ULONG    ulCookie6OtherPkt;     /* cookie6打开时监听socket收到的其他报文 */
    ULONG    ulUsrCookie6OnWhenTIMO;/* cookie6打开时收到的ACK报文超时。但是产品COOKIE打开了 */
    ULONG    ulPad;
} TCP6STAT_S;



/*Structure used by TCP6 in reassembly of the out of sequence packets*/
typedef struct tagIP6tcp6reass_S
{
    CHAR*    i6tr_next;
    CHAR*   i6tr_prev;
    TCP6HDR_S  *i6tr_t;
    #ifdef _MBUF_H_
    MBUF_S *i6tr_m;
    #else
    VOID *i6tr_m;
    #endif
    UCHAR    i6tr_x1;
    UCHAR    i6tr_pr;
    SHORT    i6tr_len;
    ULONG    i6tr_x2;
    IN6ADDR_S i6tr_dst;
}IP6TCP6REASS_S;
/*timer statistics*/
typedef struct tagTCP6TimerStat
{
    ULONG   ulStarts;     /*启动次数*/
    ULONG   ulWakeups;    /*超时次数*/
}TCP6TimerStat_S;

/*TCP6 Connection statistics */
typedef struct tagTCP6CONNSTAT
{
    ULONG    ulAccepts;             /* Number of Accepted connections */
    ULONG    ulConnects;           /* Number of established connections */
    ULONG    ulDelayedAck;       /* Number of delayed ACKs sent */

    ULONG    ulKeepProbe;        /* Number of keep alive probes sent */
    ULONG    ulKeepTimeOut;    /* Number of times keep alive timer has expired */
    ULONG    ulPAWSDrop;        /* Number of packets dropped due to PAWS */

    ULONG    ulPersistTimeOut; /* Number of persist probes sent, due to persist time out */
    ULONG    ulPredictionAck;   /* Number of header prediction ACks*/
    ULONG    ulPredictionData; /* Number of header prediction packets received */
    ULONG    ulRcvAckByte;      /* Number of bytes ACKED*/
    ULONG    ulRcvAckPacket;  /* Number of packets ACKED*/
    ULONG    ulRcvAckTooMuch; /* Number of ACKs received for which data sent */
    ULONG    ulRcvDupAck;        /* Number of duplicate ACK packets received */

    ULONG    ulRcvByte;            /* The total size of received bytes */
    ULONG    ulRcvDupByte;     /* The total size of received duplicate bytes */
    ULONG    ulRcvDupPacket; /* Number of duplicate packets received */
    ULONG    ulRcvPacketAfterWnd; /* Number of out of window packets received */
    ULONG    ulRcvByteAfterWnd;    /* The total size of out of window bytes received */
    ULONG    ulRcvPartDupByte;      /* The total size of partially duplicate bytes received */
    ULONG    ulRcvPartDupPacket;  /* Number of partially duplicate packets received*/
    ULONG    ulRcvOutOrderPacket; /* Number of out-of-order packets received */
    ULONG    ulRcvOutOrderByte;   /* The total size of out-of-order bytes received */

    ULONG    ulRcvTotal; /* Total number of received packets */
    ULONG    ulRcvPacket; /* Number of received packets in sequence */
    ULONG    ulRcvWndProbe; /* Number of window probe packets received */
    ULONG    ulRcvWndUpdate;/* Number of window update packets received */
    ULONG    ulRexmtTimeOut; /* Number of re-transmit time-outs */
    ULONG    ulRTTUpdated; /* Number of times RTT is updated */
    ULONG    ulSegsTimed; /*Number of segments queued for re-transmit */
    ULONG    ulSndByte;     /* Total size of data bytes sent */
    ULONG    ulSndControl; /* Number of control packets sent */
    ULONG    ulSndPacket; /* Number of data packets sent */
    ULONG    ulSndProbe;  /* Number of probe packets sent due to persist timer expiry */
    ULONG    ulSndRexmtByte; /* The size of the data bytes re-transmitted */
    ULONG    ulSndAcks;          /* The total number of ACK packets sent */
    ULONG    ulSndRexmtPacket; /* Number of data packets re-transmitted */
    ULONG    ulSndTotal;         /* Number of total sent packets */
    ULONG    ulSndRST;           /* Number of send RST packets */
    ULONG    ulSndUrgent;      /* Number of urgent packets sent */
    ULONG    ulSndWndUpdate; /* Number of send window update packets */
    ULONG    ulTimeOutDrop;   /* Number of connections dropped due to re-transmit time out*/
    ULONG    ulKeepAliveTimeOut; /* Number of times keep alive timer has expired */
    ULONG    ulKeepAliveDrops; /* Number of connections dropped due to keep alive time out*/

    ULONG    ulClosed;
    ULONG    ulDrops;
    ULONG    ulKeepDrops;
    ULONG    ulPersistDrops;
    ULONG    ulRcvAfterClose;
    ULONG    ulConnDrops;
    ULONG    ulConnAttempt;     /* Number of Initiated connections */ /* Per conn will be 1*/
}TCP6CONNSTAT_S;

/* TCP6 Connection Info */
typedef struct tagTCP6CONNINFO_S
{
    ULONG     ulVrfIndex;    /* VRF index */
    IN6ADDR_S stLAddr;    /* Local IPv6 address */
    IN6ADDR_S stFAddr;    /* Remote IPv6 address */
    ULONG     ulLPort;       /* Local Port */
    ULONG     ulFPort;       /* Remote Port */
    ULONG     ulSocketID;    /* Socket Id */
    ULONG     ulTaskID;      /* Task ID */
}TCP6CONNINFO_S;

/* TCP6 Per Connection Statistics */
typedef struct tagTCP6PERCONNSTAT
{
   TCP6CONNINFO_S stTcp6Conn;
   TCP6CONNSTAT_S stTcp6ConnStat;
}TCP6PERCONNSTAT_S;


/*TCP6 Control Block*/
typedef struct tagTCP6CB
{
    IP6TCP6REASS_S       *seg_next;
    IP6TCP6REASS_S       *seg_prev;
    TCP6IP6HDR_S         *pTemplate;
    struct tagTCP6CB     *pNextFastTimer;
    struct tagTCP6CB     *pPrevFastTimer;
    TCP6CONNSTAT_S       *pstTCP6ConnStats;/* Added for per Connection statistics*/
    UINTPTR              ulIn6PCB;
    SHORT                sState;
    SHORT                sTimer[TCP6T_NTIMERS];
    SHORT                sRexmtShift;
    SHORT                sRexmtCur;
    SHORT                sDupAcks;
    USHORT               usMaxSeg;
    USHORT               usRTTMin;

#define    TF_ACKNOW        0x0001    /* ack peer immediately */
#define    TF_DELACK        0x0002    /* ack, but try to delay it */
#define    TF_NODELAY       0x0004    /* don't delay packets to coalesce */
#define    TF_NOOPT         0x0008    /* don't use tcp options */
#define    TF_SENTFIN       0x0010    /* have sent FIN */
#define    TF_REQ_SCALE     0x0020    /* have/will request window scaling */
#define    TF_RCVD_SCALE    0x0040    /* other side has requested scaling */
#define    TF_REQ_TSTMP     0x0080    /* have/will request timestamps */
#define    TF_RCVD_TSTMP    0x0100    /* a timestamp was received in SYN */
#define    TF_SACK_PERMIT   0x0200    /* other side said I could SACK */
#define    TF_STDURG        0x0400    /*URG ptr is last byte of urg data */
#define    TF_WASIDLE       0x0800    /* tcp6_output() was idle on last call */

    TCP6_SEQ            seqSndUnack;
    TCP6_SEQ            seqSndNxt;
    TCP6_SEQ            seqSndUrgentPoint;
    TCP6_SEQ            seqLastRcvSeqToUpdWnd;/* Records the last sequence
                                                   number received used to
                                                   update the send window
                                                   (ulSndWnd).
                                                */
    TCP6_SEQ            seqLastRcvAckToUpdWnd;/* Records the last ack number
                                                   received used to update the
                                                   send window.
                                                */
    TCP6_SEQ            seqISS;
    ULONG               ulSndWnd;
    ULONG               ulRcvWnd;
    TCP6_SEQ            seqRcvNxt;
    TCP6_SEQ            seqRcvUrgentPoint;
    TCP6_SEQ            seqInitRcvSeq;
    TCP6_SEQ            seqRcvAdvertise;
    TCP6_SEQ            seqSndMax;
    ULONG               ulSndCongestionWnd;
    ULONG               ulSndSSThresh;
    SHORT               sIdle;
    SHORT               sRTT;
    TCP6_SEQ            seqRTSeq;
    SHORT               sSRTT;
    SHORT               sRTTVar;

    ULONG               ulMaxSndWnd;
    CHAR                cOOBFlags;
    CHAR                cIOBC;
#define    TCP6OOB_HAVEDATA    0x01
#define    TCP6OOB_HADDATA     0x02
    SHORT                sSoftError;
    UCHAR                ucSndScale;
    UCHAR                ucRcvScale;
    UCHAR                ucRequestRScale;
    UCHAR                ucRequestedSScale;
    ULONG                ulTSRecent;
    ULONG                ulTSRecentAge;
    TCP6_SEQ            seqLastAckSent;

    TCP6TimerStat_S       stConEstab;   /*连接建立定时器计数*/
    TCP6TimerStat_S       stRetrans;    /*重传定时器计数*/
    TCP6TimerStat_S       stAckHold;    /*延迟ACK定时器计数*/
    TCP6TimerStat_S       stPersist;    /*持续定时器计数*/
    TCP6TimerStat_S       stKeepAlive;  /*保活定时器计数*/
    TCP6TimerStat_S       stFinWait2;   /*FIN_WAIT_2定时器计数*/
    TCP6TimerStat_S       stTimeWait;   /*TIME_WAIT定时器计数*/

    ULONG                 ulRcvMSS;             /*收到对端通告的MSS选项值*/
    ULONG                 ulSndMSS;             /*向对端通告的MSS选项值*/
    ULONG                 ulRcvTotal;           /*这条连接接收报文的总个数*/
    ULONG                 ulRcvOutOrderPacket;  /*乱序报文个数*/
    ULONG                 ulRcvDataPacket;      /*数据报文个数*/
    ULONG                 ulRcvDataByte;        /*接收的有效的数据字节数*/
    ULONG                 ulRcvMaxDataByte;     /*最大数据报文段所携带的字节数*/
    ULONG                 ulRcvMinDataByte;     /*最小数据报文段所携带的字节数*/
    ULONG                 ulSndTotal;           /*包括发送报文的总个数*/
    ULONG                 ulSndRetran;          /*重传报文个数*/
    ULONG                 ulSndDataPacket;      /*发送有效数据报文个数*/
    ULONG                 ulSndDataByte;        /*共发送有效数据字节数*/
    ULONG                 ulPMTUVal;
    IN6ADDR_S             stIP6NextHop;         /*sending next-hop address*/
    ULONG                 ulOutIfIndex;         /*sending output interface*/
    ULONG                 ulRtFlags;            /*FIB6 Route flags*/
    USHORT                usFlags;
    CHAR                  cForce;
    /*Added by likaikun213099, MCCP-MSS可配置, 2013/12/18 */
    UCHAR                 ucIsUserSetMSS;

    ULONG                 ulSendTick;      /* The time last pkt is sent, 10ms. Added for Qos Info*/
    ULONG                 ulAvgRTT;        /* Average RTT, 10ms. Added for Qos Info */
    ULONG                 ulLastRTT;       /* Last RTT, 10ms. Added for Qos Info */
    ULONG                 ulAvgRTTWarp;    /* Average warping RTT, 10ms. Added for Qos Info */
} TCP6CB_S;

/* A data structure is being provided to fetch
           the desired parameters from the TCP6 control block*/
typedef struct tagTCP6CBParam
{
    SHORT           sState;
    SHORT           sRTTVar;
    TCP6_SEQ        seqISS;
    TCP6_SEQ        seqSndUnack;
    TCP6_SEQ        seqSndNxt;
    ULONG           ulSndWnd;
    TCP6_SEQ        seqSndMax;
    TCP6_SEQ        seqInitRcvSeq;
    TCP6_SEQ        seqRcvNxt;
    ULONG           ulRcvWnd;
    ULONG             ulConEstabStarts;
    ULONG             ulConEstabWakeups;
    ULONG             ulRetransStarts;
    ULONG             ulRetransWakeups;
    ULONG             ulAckHoldStarts;
    ULONG             ulAckHoldWakeups;
    ULONG             ulPersistStarts;
    ULONG             ulPersistWakeups;
    ULONG             ulKeepAliveStarts;
    ULONG             ulKeepAliveWakeups;
    ULONG             ulFinWait2Starts;
    ULONG             ulFinWait2Wakeups;
    ULONG             ulTimeWaitStarts;
    ULONG             ulTimeWaitWakeups;
    ULONG           ulRcvMSS;
    ULONG           ulSndMSS;
    USHORT          usMaxSeg;
    SHORT           sSRTT;
    SHORT           sRexmtCur;
    USHORT          usRTTMin;
    ULONG           ulRcvTotal;
    ULONG           ulRcvDataByte;
    ULONG           ulRcvDataPacket;
    ULONG           ulRcvOutOrderPacket;
    ULONG           ulRcvMaxDataByte;
    ULONG           ulRcvMinDataByte;
    ULONG           ulSndTotal;
    ULONG           ulSndRetran;
    ULONG           ulSndDataPacket;
    ULONG           ulSndDataByte;
    ULONG               ulSndCongestionWnd;
    UCHAR               ucRequestedSScale;
    UCHAR               ucReserved[3];
    ULONG               ulTSRecent;
    ULONG               ulTSRecentAge;
} TCP6CBPARAM_S;

/*MIB Structure for TCP6CB parameters*/
typedef struct tagTCP6CONNPARAM
{
    UINTPTR             ulTCP6CB;
    IN6ADDR_S           stLAddr;
    IN6ADDR_S           stFAddr;
    ULONG               ulVrfIndex;
    ULONG               ulTaskId;
    LONG                 lFD;
    USHORT              usLPort;
    USHORT              usFPort;
    SHORT               sState;
    SHORT               sReserved;    
} TCP6CONNPARAM_S;



/*MIB connection parameter*/
typedef struct tagTCP6MIBCONN
{
    IN6ADDR_S            stLAddr;
    IN6ADDR_S            stFAddr;
    USHORT              usLPort;
    USHORT              usFPort;
    ULONG               ulConnIfIndex;
    SHORT               sState;
    SHORT               sReserved;
} TCP6MIBCONN_S;

/* TCP6 MIB RFC 4022 implementation  */
/* connection table avail node */
typedef struct tagTCP6_CON_TABLE_AVL_NODE
{
    TCP6CB_S*   pstTcpCB;  /* To get TCP current 'state' information */
    IN6ADDR_S   stTcpConTabLocAddr;
    IN6ADDR_S   stTcpConTabRemAddr;
    USHORT      usTcpConTabLocPort;
    USHORT      usTcpConTabRemPort;
    ULONG       ulTcpConTabProcess;
} TCP6_CON_TABLE_AVL_NODE_S;

/* listener table Avail node*/
typedef struct tagTCP6_LIS_TABLE_AVL_NODE
{
    TCP6CB_S*   pstTcpCB;  /* Have a back-pointer to TCPCB */
    IN6ADDR_S   stTcpLisTabLocAddr;
    ULONG       ulTcpLisTabProcess;
    USHORT      usTcpLisTabLocPort;
    UCHAR       ucPadding[2]; /* For byte-alignment */
} TCP6_LIS_TABLE_AVL_NODE_S;

/*MIB return values*/
typedef struct tagTCP6_MIB_RETURN
{
    ULONG       ulTcpMibLocAddrType;
    IN6ADDR_S   stTcpMibLocAddr;
    ULONG       ulTcpMibLocPort;
    ULONG       ulTcpMibRemAddrType;
    IN6ADDR_S   stTcpMibRemAddr;
    ULONG       ulTcpMibRemPort;
    LONG        lTcpMibState;
    ULONG       ulTcpMibProcess;
} TCP6_MIB_RETURN_S;

#define TCP6_MIB_LOCAL_ADDR_TYPE    2
#define TCP6_MIB_REMOTE_ADDR_TYPE   2

/*Debug filter */
typedef struct tagTCP6DBUGFILT
{
    ULONG   ulTaskId;        /* 存放用户设置的过滤条件中的任务ID   */
    ULONG   ulSockId;        /* 存放用户设置的过滤条件中的套接口号 */
}TCP6DBUGFILT_S;

/*Debug filter*/
typedef struct tagTCP6DBUGFILTRD
{
    TCP6DBUGFILT_S stSockDbugFilt[TCP6_MAXFILTNUM];
    ULONG          ulFiltCnt;       /* 当前过滤条件的个数 */
}TCP6DBUGFILTRD_S;

/* Begin - IPv4-IPv6 Mib Coupling interface */
typedef struct tagTCP6_MibScalarStc
{
    DULONG dulTcp6HCInSegs;
    DULONG dulTcp6HCOutSegs;
    ULONG ulTcp6RtoAlgorithm;
    ULONG ulTcp6RtoMin;
    ULONG ulTcp6RtoMax;
    ULONG ulTcp6MaxConn;
    ULONG ulTcp6ActiveOpens;
    ULONG ulTcp6PassiveOpens;
    ULONG ulTcp6AttemptFails;
    ULONG ulTcp6EstabResets;
    ULONG ulTcp6CurrEstab;
    ULONG ulTcp6InSegs;
    ULONG ulTcp6OutSegs;
    ULONG ulTcp6RetransSegs;
    ULONG ulTcp6InErrs;
    ULONG ulTcp6OutRsts;    
} TCP6_MibScalarStc;

#define TCP6_VJ_ALGORITHM        4
/*#define TCP6_UNKNOWN_VALUE       0 */
#define TCP6_UNKNOWN_VALUE       0xFFFFFFFF

#define TCP6_MIB_IPV4_ADDR_TYPE    1

/* End - IPv4-IPv6 Mib Coupling interface */

#define IPV6TCPCONNTABLE_TBL   5

#define CFGMIB_IPV6TCPCONNLOCALADDRESS  \
                            CFG_CMO_DEF(MID_TCP6, IPV6TCPCONNTABLE_TBL, 1)
#define CFGMIB_IPV6TCPCONNLOCALPORT     \
                            CFG_CMO_DEF(MID_TCP6, IPV6TCPCONNTABLE_TBL, 2)
#define CFGMIB_IPV6TCPCONNREMADDRESS    \
                            CFG_CMO_DEF(MID_TCP6, IPV6TCPCONNTABLE_TBL, 3)
#define CFGMIB_IPV6TCPCONNREMPORT       \
                            CFG_CMO_DEF(MID_TCP6, IPV6TCPCONNTABLE_TBL, 4)
#define CFGMIB_IPV6TCPCONNIFINDEX       \
                            CFG_CMO_DEF(MID_TCP6, IPV6TCPCONNTABLE_TBL, 5)
#define CFGMIB_IPV6TCPCONNSTATE         \
                            CFG_CMO_DEF(MID_TCP6, IPV6TCPCONNTABLE_TBL, 6)

#ifdef COMPILING_IR_IPV6_CORE
#pragma pack()
#endif

#ifdef  __cplusplus
}
#endif

#endif  /* _TCP6_PUBLIC_H */

