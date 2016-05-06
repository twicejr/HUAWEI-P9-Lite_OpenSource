/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp_var.h
*
*  Project Code: VISP1.5
*   Module Name: IP TCP4
*  Date Created: 1996-12-26
*        Author: 刘庆智
*   Description: TCP自有数据结构
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  1996-12-26  刘庆智           Create the first version.
*  2006-05-11  luyao            为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/
#ifndef _TCP_VAR_H
#define _TCP_VAR_H

#ifdef __cplusplus
extern "C"{
#endif


#include "tcpip/tcp4/include/tcp_api.h"
/*
 * the smoothed往返时间和估计的偏差保存成定点数与标量的乘积
 * The smoothed round-trip time and estimated variance
 * are stored as fixed point numbers scaled by the values below.
 * For convenience, these scales are also used in smoothing the average
 * 这些标量也同样用在求平均值中，如(smoothed = (1/scale)sample + ((scale-1)/scale)smoothed).
 * (smoothed = (1/scale)sample + ((scale-1)/scale)smoothed).
 * 有了这些标量，srrt占从右边界起的3位，因此"ALPHA"值为0.875，rttvar占从右边界起的2位，"ALPHA"值为0.875
 * With these scales, srtt has 3 bits to the right of the binary point,
 * and thus an "ALPHA" of 0.875.  rttvar has 2 bits to the right of the
 * binary point, and is smoothed with an ALPHA of 0.75.
 */
#define    TCP_RTT_SCALE       8    /* SRTT的乘数  3比特   multiplier for srtt; 3 bits frac. */
#define    TCP_RTT_SHIFT       3    /* SRTT的移位  3比特   shift for srtt; 3 bits frac. */
#define    TCP_RTTVAR_SCALE    4    /* rttvar的乘数 2比特  multiplier for rttvar; 2 bits */
#define    TCP_RTTVAR_SHIFT    2    /* rttvar的移位  2比特   multiplier for rttvar; 2 bits */

#define    TCP_REXMTVAL(tp) \
    (((tp)->sSRTT >> TCP_RTT_SHIFT) + (tp)->sRTTVar)

#define REASS_MBUF(pTCPIPHeader) (*(struct tagMBuf **)&((pTCPIPHeader)->thTCPHeader))

/* insert tcpcb into fast timer serial */
/* 将tcpcb插入到快定时器序列，如果tcpcb已在序列中，则不再插入
 * if this tcpcb is already in the fast timeout train,
 * we do not insert it once more.
 */
#define TCPT_INSFASTTIMER(pTCPCB)   \
{   \
    if( ((pTCPCB)->pNextFastTimer == NULL) \
        && ((pTCPCB)->pPrevFastTimer == NULL) \
        && (g_pstTcpFastHead != (pTCPCB)) \
      ) \
    { \
        (pTCPCB)->pNextFastTimer = g_pstTcpFastHead; \
        if( g_pstTcpFastHead ) \
        { \
            g_pstTcpFastHead->pPrevFastTimer = (pTCPCB); \
        } \
        g_pstTcpFastHead = (pTCPCB); \
    } \
}

/* 将tcpcb从快定时器序列中删除。即使pNextFastTimer,pPrevFastTimer都为空
   它仍可能还在序列中，因为g_pstTcpFastHead == pTcpcb */
/* del tcpcb from fast timer serial */
/* although if pNextFastTimer,pPrevFastTimer all are null,
 * it may be in the serial, because g_pstTcpFastHead == pTcpcb */
#define TCPT_DELFASTTIMER(pTCPCB)   \
{  \
    if( (pTCPCB)->pNextFastTimer )  \
    { \
        (pTCPCB)->pNextFastTimer->pPrevFastTimer = (pTCPCB)->pPrevFastTimer; \
    } \
    if( (pTCPCB)->pPrevFastTimer ) \
    { \
        (pTCPCB)->pPrevFastTimer->pNextFastTimer = (pTCPCB)->pNextFastTimer; \
    } \
    else if( g_pstTcpFastHead == (pTCPCB) ) \
    { \
        g_pstTcpFastHead = (pTCPCB)->pNextFastTimer; \
    } \
    (pTCPCB)->pNextFastTimer = NULL; \
    (pTCPCB)->pPrevFastTimer = NULL; \
}

typedef struct tagTCPTimerStat
{
    ULONG   ulStarts;     /*启动次数*/
    ULONG   ulWakeups;  /*超时次数*/
}TCPTimerStat_S;

/* 用户配置MD5pwd时用到的数据结构 md5P***W***中非pwd成员长度和 */
#define PREFIXMD5LEN sizeof(ULONG)  /*address and mask*/
#define PREFIXMD5LEN_EX sizeof(ULONG) + sizeof(ULONG)  /*address and mask*/


/* md5 hash length */
#define TCPMD5HASHLEN 64
#define TCPMD5PWDMAXLEN 256
#define TCPMD5PWDMAXSUM 512
#define TCPMD5PWDVALUE_ONE 1
#define TCPMD5MAXMASK 32
#define TCPMD5INVALIDMASK 0
#define TCPMD5WILDCARDADDR 0x00000000
#define TCPMD5WILDCARDMASK 0
#define TCPMD5MAXBITMASK 0x80000000
#define TCPMD5NEWCHILDSOCKET 1


/* 设置MD5pwd对应的数据结构 */
typedef struct md5password
{
    ULONG sin_addr;            /* socket的32位地址长度     32-bit address of the socket */
    CHAR  szMd5Password[TCPMD5PWDMAXLEN];  /* MD5pwd(长度< 256位) MD5 P***W***(len < 256 bit) */
}SOCKMD5Pwd_S;

/* 设置MD5pwd对应的数据结构 *//* C00-整改-l00103192 17  2014-1-26 */
typedef struct md5password_ex
{
    ULONG sin_addr;            /* socket的32位地址长度     32-bit address of the socket */
    ULONG ulMask;               /*Mask value to set and get the TCP P***W*** based on masked Peer IP.*/
    CHAR  szMd5Password[TCPMD5PWDMAXLEN];  /* MD5pwd(长度< 256位) MD5 P***W***(len < 256 bit) */
}SOCKMD5Pwd_EX_S;


/* 通过地址HASH数组索引(数组长度为64) */
#define TCP_MD5HASHIP(ulSrcIp, ulHashIndex)\
{\
    (ulHashIndex) = ((ulSrcIp) >> 24) & ((ulSrcIp) >> 16) & ((ulSrcIp) >> 8) & (ulSrcIp);\
    (ulHashIndex) = ((ulHashIndex) >> 2) & 0x3f;\
}

typedef struct tagTCPMd5Pwd
{
    struct tagTCPMd5Pwd * pNext;

    ULONG sin_addr;     /* socket的32位地址长度   32-bit address of the socket */
    ULONG ulmask;     /* Mask value passed during the creation only used in get sock opt*/
    CHAR  *pszMd5Pwd;   /* MD5pwd(长度< 256位)    MD5 P***W***(len < 256 bit) */
}TCPMd5Pwd_S;

/* TCPCB控制块pstTcpMd5PwdHead字段的类型 */
typedef struct tagTCPMd5PwdHead
{
    ULONG ulPwdCnt;
    ULONG ulMaskbitMap;   /*ulong value will be storing 32 bit mapping for the mask set by the user during setting of the option for MD5 p**s***d*/
    CHAR  *pszMd5UsedPwd; /*this will contain the used p***W**d  usually in case of child socket*/
    CHAR  *pszMd5WildcardPwd;
    TCPMd5Pwd_S* apstMd5Pwd[TCPMD5HASHLEN];
}TCPMd5PwdHead_S;

/* TCP协议控制块 */
typedef struct tagTCPCB
{
    /*Added by zhoushisong202096, 更改TCP重组队列, 2013/11/5 */
    MBUF_S       *pReassPkt;             /* TCP重组队列,如果无TCP重组报文则为NULL */
    SHORT        sState;
    SHORT        sTimer[TCPT_NTIMERS];
    SHORT        sRexmtShift;
    SHORT        sRexmtCur;
    SHORT        sDupAcks;
    USHORT       usMaxSeg;
    CHAR         cForce;
    /*Added by likaikun213099, MCCP-MSS可配置, 2013/12/18 */
    UCHAR        ucIsUserSetMSS;
    USHORT       usFlags;
#define    TF_ACKNOW        0x0001        /* ACK, 立即处理      ack peer immediately */
#define    TF_DELACK        0x0002        /* ACK, 但延迟     ack, but try to delay it */
#define    TF_NODELAY       0x0004        /* 不延迟分组合并   don't delay packets to coalesce */
#define    TF_NOOPT         0x0008        /* 不使用TCP选项   don't use tcp options */
#define    TF_SENTFIN       0x0010        /* 已发送FIN       have sent FIN */
#define    TF_REQ_SCALE     0x0020        /* 请求scaling      have/will request window scaling */
#define    TF_RCVD_SCALE    0x0040        /* 对方请求scaling   other side has requested scaling */
#define    TF_REQ_TSTMP     0x0080        /* 请求时间戳    have/will request timestamps */
#define    TF_RCVD_TSTMP    0x0100        /* 接受到SYN中的时间戳  a timestamp was received in SYN */
#define    TF_SACK_PERMIT   0x0200        /* 对方回答能SACK other side said I could SACK */
    UCHAR        ucPadding_2[2];
    TCPIPHDR_S   *pTemplate;
    VOID         *pInPCB;
    TCP_SEQ      seqSndUnack;
    TCP_SEQ      seqSndNxt;
    TCP_SEQ      seqSndUrgentPoint;
    TCP_SEQ      seqLastRcvSeqToUpdWnd;    /* 记录更新发送窗口的最新的序列号  Records the last sequence
                                                   number received used to
                                                   update the send window
                                                   (ulSndWnd).
                                           */
    TCP_SEQ      seqLastRcvAckToUpdWnd;    /* 记录更新发送窗口的最新的ACK号 Records the last ack number
                                                   received used to update the
                                                   send window.
                                           */
    TCP_SEQ      seqISS;
    ULONG        ulSndWnd;
    ULONG        ulRcvWnd;
    TCP_SEQ      seqRcvNxt;
    TCP_SEQ      seqRcvUrgentPoint;
    TCP_SEQ      seqInitRcvSeq;
    TCP_SEQ      seqRcvAdvertise;
    TCP_SEQ      seqSndMax;
    ULONG        ulSndCongestionWnd;
    ULONG        ulSndSSThresh;
    SHORT        sIdle;
    SHORT        sRTT;
    TCP_SEQ      seqRTSeq;
    SHORT        sSRTT;
    SHORT        sRTTVar;
    USHORT       usRTTMin;
    UCHAR        ucPadding_3[2];
    ULONG        ulMaxSndWnd;
    CHAR         cOOBFlags;
    CHAR         cIOBC;
#define    TCPOOB_HAVEDATA    0x01
#define    TCPOOB_HADDATA     0x02
    SHORT        sSoftError;
    UCHAR        ucSndScale;
    UCHAR        ucRcvScale;
    UCHAR        ucRequestRScale;
    UCHAR        ucRequestedSScale;
    ULONG        ulTSRecent;
    ULONG        ulTSRecentAge;
    TCP_SEQ      seqLastAckSent;

    struct tagTCPCB     *pNextFastTimer;
    struct tagTCPCB     *pPrevFastTimer;

/*  struct tagTCPCB    *pNextSlowTimer[TCPT_NTIMERS];
    struct tagTCPCB     *pPrevSlowTimer[TCPT_NTIMERS];
*/
    TCPTimerStat_S   stConEstab;    /*连接建立定时器计数*/
    TCPTimerStat_S   stRetrans;     /*重传定时器计数*/
    TCPTimerStat_S   stAckHold;     /*延迟ACK定时器计数*/
    TCPTimerStat_S   stPersist;     /*持续定时器计数*/
    TCPTimerStat_S   stKeepAlive;   /*保活定时器计数*/
    TCPTimerStat_S   stFinWait2;    /*FIN_WAIT_2定时器计数*/
    TCPTimerStat_S   stTimeWait;    /*TIME_WAIT定时器计数*/

    ULONG     ulRcvMSS;             /*收到对端通告的MSS选项值*/
    ULONG     ulSndMSS;             /*向对端通告的MSS选项值*/

    TCPMd5PwdHead_S* pstTcpMd5PwdHead; /* 用于支持多peer MD5enc 功能 */

    ULONG     ulRcvTotal;           /*这条连接接收报文的总个数*/
    ULONG     ulRcvOutOrderPacket;  /*乱序报文个数*/
    ULONG     ulRcvDataPacket;      /*数据报文个数*/
    ULONG     ulRcvDataByte;        /*接收的有效的数据字节数*/
    ULONG     ulRcvMaxDataByte;     /*最大数据报文段所携带的字节数*/
    ULONG     ulRcvMinDataByte;     /*最小数据报文段所携带的字节数*/
    ULONG     ulSndTotal;           /*包括发送报文的总个数*/
    ULONG     ulSndErr;             /*发送失败报文数 Added for dist_sock by likaikun00213099*/
    ULONG     ulSndRetran;          /*重传报文个数*/
    ULONG     ulSndDataPacket;      /*发送有效数据报文个数*/
    ULONG     ulSndDataByte;        /*共发送有效数据字节数*/

    ULONG     ulIfIndex;            /* TCPCB外发接口的索引   index of outgoing interface For TCPCB*/
    ULONG     ulFlags;              /* RTF_GATEWAY, RTF_HOST, ...*/
    ULONG     ulNexthop;

    /* Added for tcp ha */
    TCP_SEQ   seqRcvNxtLastBackup; /* 最近一次备份的seqRcvNxt    seqRcvNxt that is backuped last time */
    TCP_SEQ   seqRcvLastBackup;    /* 已经备份的seqRcvNxt   The rcv seq where tcp rcv buf have been backuped */
    USHORT    usRoutineBackupTime; /* tcp socket 缓存备份的间隔 Routine backup interval of tcp socket buf */
    USHORT    usRoutineTimeout;    /* 超时时间（200ms） Time(*200ms) when to time out*/
    struct tagTCPCB *pNextRoutine; /* 备份中的下一个TCPCB  Next TCPCB in the chain of routine backup */
    struct tagTCPCB *pPrevRoutine; /* 备份中的上一个TCPCB  Previous TCPCB in the chain of routine backup */
    ULONG     ulSndBufCutLen;      /* 在备板上要去掉的tcp socket 缓存的长度  Length of tcp socket snd buf on slave board to be cut */
    ULONG     ulSeqRcvNxtRevised;  /* 修正seqRcvNxt的时间  Times that seqRcvNxt has been revised */

    /* Modified for A82D12723 by l48923 2007-03-16.
     * After switching, we may rcv seq that is out of rcv wnd.
     * 变换后，rcv seq可能脱离rcv wnd
     * This case is just same as the case in TCP_Reass. We record the
     * smallest rcved seq that is out of order. Once we receive it
     * again(duplicated packet), we can revise our seqRcvNxt.
     * 这种情况和TCP_Reass的情况一致。记录最小的一个rcved seq。一旦再次接收到之后，
     * 就可以校正seqRcvNxt
     */
    TCP_SEQ   seqRcvedOutOfWnd;       /* 最近一次收到的脱离rcv wnd的seq  Last received seq that is out of the rcv wnd */
    CHAR      cSeqRcvedOutOfWndValid; /* 指明这个seq是否有效  Indicate whether the seq that is out rcv wnd is valid.
                                       * 当接收到一个有效的seq时，将其置零  Once a valid seq is recieved, we set it as 0(invalid).
                                       */
    UCHAR     ucPadding_4[3];

    ULONG    ulSendTick;      /* The time last pkt is sent, 10ms. Added for Qos Info*/
    ULONG    ulAvgRTT;        /* Average RTT, 10ms. Added for Qos Info */
    ULONG    ulLastRTT;       /* Last RTT, 10ms. Added for Qos Info */
    ULONG    ulAvgRTTWarp;    /* Average warping RTT, 10ms. Added for Qos Info */

} TCPCB_S;

#define    INTOTCPCB(pInPCB)    ((struct tagTCPCB *)((pInPCB)->inp_pPPcb))
#define    SOTOTCPCB(pSocket)    (INTOTCPCB(SOTOINPCB(pSocket)))

#define TCP_STAT_INC_VALUE    1

/* 通过TCPCB获取TCP统计信息 */
#define    TCPCB_TO_PERTCPSO_STAT(pTcpCB, tcpStatM, ulValue) \
{ \
    if((pTcpCB)->pInPCB) \
    { \
        if (((struct tagINPCB *)((pTcpCB)->pInPCB))->inp_pSocket) \
        { \
            (((struct tagINPCB *)((pTcpCB)->pInPCB))->inp_pSocket)->unSocketStat.stPerTCP4Stat.tcpStatM += ulValue; \
        } \
    } \
}



/* #ifdef KERNEL */
struct tagSOCKET;
struct tagIP;

/*Modified by dengxiong for D00173*/

LONG TCPAttach(VOID *pSocket);
VOID TCPCancelTimers(struct tagTCPCB *);
struct tagTCPCB *TCPClose(struct tagTCPCB *);
VOID TCPCtlInput(LONG, struct tagSOCKADDR *, struct tagIP *);

/*Modified by dengxiong for D00173*/
LONG TCPCtlOutput(  LONG             iOperation,
                    struct tagSOCKET*pSocket,
                    LONG             iLevel,
                    LONG             iOptName,
                    MBUF_S          **pBuf
                 );

LONG TCPSetMd5Pass(LONG iOptName, MBUF_S   *p, TCPCB_S *pNwTCPCB);
LONG TCPGetMd5Pass(LONG iOptName, MBUF_S   *p, TCPCB_S *pNwTCPCB);


struct tagTCPCB        *TCPDisconnect(struct tagTCPCB *);
struct tagTCPCB        *TCPDrop(struct tagTCPCB *, LONG);

/*  与VRPV5B02D21同步  modified by x36317 for synchronizing with VRPV5B02D21  2004-09-10*/
/* TCP MD5 authentication, 2002,07,21, zhangfeng */
ULONG TCPDoOptions(TCPCB_S         *pTCPCB,
                        USHORT          usLenOfIPPack,
                        UCHAR           *pFirstOption,
                        LONG            iTotalLen,
                        TCPIPHDR_S      *pRcvHeader,
                        LONG            *pTSPresent,
                        ULONG           *pTSVal,
                        ULONG           *pTSEchoReply,
                        ULONG           ulVrfindex
                        );
ULONG TCPInsertOptions(ULONG ulOptType, TCPCB_S *pTCPCB, MBUF_S *pstMBufHead,
                            ULONG ulTotalOptLen, ULONG ulSndDataLen, TCPIPHDR_S *pHeader,VOID *OptData);
/* TCP MD5 authentication, 2002,07,21, zhangfeng */

VOID TCPDrain(VOID);
VOID TCPFastTimeOut(VOID);
VOID TCPInit(VOID);
VOID TCPInput(struct tagMBuf *, LONG);
LONG TCPMSS(struct tagTCPCB *, ULONG, TCPIPHDR_S *);
struct tagINPCB;

/*Modified by dengxiong for D00173*/
TCPCB_S *TCPNewTCPCB(VOID *pInPCB);
VOID TCPNotify(VOID *pInPCB, LONG iError);


LONG TCPOutput(TCPCB_S *pTCPCB);
VOID TCPPullOutOfBand(    struct tagSOCKET *,
                                struct tagTCPIPHDR *,
                                struct tagMBuf *
                                    );

/*Modified by dengxiong for D00173*/
VOID TCPQuench(VOID *pInPCB, LONG iError);
/* Modified by Lirui */
/*LONG                    TCPReass(    struct tagTCPCB *,
                                struct tagTCPIPHDR *,
                                struct tagMBbuf *
                            );
*/
LONG TCPReass(TCPCB_S *pTCPCB, TCPIPHDR_S *pRcvHeader, MBUF_S *pRcvSeg);

VOID TCPRespond(    struct tagTCPCB *,
                                struct tagTCPIPHDR *,
                                struct tagMBuf *,
                                ULONG,
                                ULONG,
                                LONG
                                );
VOID TCPSetPersist(struct tagTCPCB *);
VOID TCPSlowTimeOut(VOID);
struct tagTCPIPHDR* TCPTemplate(struct tagTCPCB *);
struct tagTCPCB* TCPTimers(struct tagTCPCB *, LONG);
struct tagTCPCB* TCPUsrClosed(struct tagTCPCB *);

/*Modified by dengxiong for D00173*/
LONG TCPUserRequest(struct tagSOCKET*pSocket,
                    LONG             iRequest,
                    MBUF_S          *pData,
                    MBUF_S          *pName,
                    MBUF_S          *pControl
                  );
VOID TCPXmitTimer(struct tagTCPCB *, SHORT);

extern VOID TCP_PrintState(SHORT state,CHAR *pBuf, ULONG ulLen);

VOID TCPISNTick( VOID );
ULONG TCPNewISN( TCPCB_S* );
VOID TCPRespondEX(TCPCB_S         *pTCPCB,
                    TCPIPHDR_S      *pHeader,
                    MBUF_S          *pRcvSeg,
                    TCP_SEQ         seqAck,
                    TCP_SEQ         seqSeq,
                    LONG            iFlags,
                    UINT16          u16MSS,
                    UINT32          u32TimeStamp
               );

typedef struct tagTCP4MODINFO
{
    ULONG    ulModID;
    ULONG    ulSubModID;
    ULONG    ulTCP4_CFG_NEED_CACHE;
    ULONG    ulTCP4_OUTPUT_OPTIMIZE;
} TCP4_MOD_INFO_S;


extern TCP4_MOD_INFO_S   g_stTCP4ModInfo;

extern struct IP4_TCP4_SH_CALLBACK_SET_S    *g_pstTCP4Callback;

/*move from socktemp.h*/
#define mid_TCP_TCPTEMPLATE (g_stTCP4ModInfo.ulModID | 30) /* TCP模版 0x0392001e, TCPTemplate() */
#define mid_TCP_TCPRESPOND (g_stTCP4ModInfo.ulModID | 31) /* TCP响应 0x0392001f, TCPRespond() */
#define mid_TCP_TCPNEWTCPCB (g_stTCP4ModInfo.ulModID | 32) /*  0x03920020, TCPNewTCPCB() */
#define mid_TCP_TCPINIT (g_stTCP4ModInfo.ulModID | 33) /* TCP初始化 0x03920021, TCPInit() */
#define mid_TCP_TCPOUTPUT (g_stTCP4ModInfo.ulModID | 34) /* TCP输出 0x03920022, TCPOutput() */
#define mid_TCP_TCPUSERREQUEST (g_stTCP4ModInfo.ulModID | 35) /* TCP应用请求 0x03920023,TCPUserRequest() */
#define mid_TCP_TCPCTLOUTPUT (g_stTCP4ModInfo.ulModID | 36) /*  0x03920024, TCPCtlOutput() */


/*move from sock_pub.h*/
/*---------------------------------------------------------------------*/
/* Options for use with [gs]etsockopt at the TCP level.                */
/*---------------------------------------------------------------------*/
#define TCP_NODELAY         1       /* 设置/收到TCP无延迟选项  set/get tcp nodelay option */
#define TCP_MAXSEG          2       /* 设置/收到TCP段的最大值  set/get tcp max segment size */
#define TCP_KEEPALIVE_IDLE  3       /* 设置/收到TCP记时值  set/get TCP Keepalive timer value */
#define TCP_KEEPALIVE_CNT   4       /* 设置/收到TCP持续探测数目  set/get TCP Keepalive probe count */
#define TCP_KEEPALIVE_INTVL 5       /* 设置/收到TCP持续探测间隙  set/get TCP Keepalive probing interval*/
#define TCP_MSL             6       /* 设置/收到最大TCP段生存时间  set/get TCP Maximum Segment Lifetime */
#define TCP_BINDFOREIGNADDR 7

/* TCP with MD5 authentication, zhangfeng, 2002,07,20 */
#define TCP_SETPASSWORD     8       /* 设置/收到TCP md5的验证pwd  set/get tcp md5 authentication P***W*** */
/* TCP with MD5 authentication, zhangfeng, 2002,07,20 */

#define TCP_ROUTINEBACKUP  9        /* 设置/收到tcp socket缓存器的备份间隔  set/get routine backup interval of tcp socket buffer */

extern LONG iTCPMSSDefault;
extern LONG iTCPRTTDefault;
extern LONG iTCPDoRFC1323;
extern LONG iTCPRexmtThresh;
/* extern LONG iTCPDebugFlags;      for configuration */

extern VOID         *pTCPLastInPCB;

extern TCPCB_S      *g_pstTcpFastHead;

extern UCHAR    ucTCPOutFlags[TCP_NSTATES];
extern SHORT    sTCPBackOff[TCP_MAXRXTSHIFT + 1];

extern LONG     iTCPTotalBackOff;    /* sum of sTCPBackOff */

extern LONG     iTCPKeepIdle;
extern LONG     iTCPKeepIntvl;
extern LONG     iTCPKeepCnt;          /* 最大探测空闲  max idle probes */
extern LONG     iTCPMaxPersistIdle;   /* 持续的最大空闲时间  max idle time in persist */
extern LONG     iTCPMaxIdle;
extern ULONG    ulTCPNow;             /* 时间表  for RFC 1323 timestamps */

extern TCP_SEQ      seqTCPISS;        /* tcp初始发送序列  tcp initial send seq # */
extern VOID         *g_ppcbTCPConnections; /* head of queue of active tcpcb's */
/*pcbTCPConnections在SOCKET中申明*/

extern VOID  *g_pstTcpHash;  /* tcp hash table structure */

extern TCPSTAT_S  tstTCPStat;             /* tcp统计量  tcp statistics */
extern ULONG   ulTCPSndSpace;
extern ULONG   ulTCPRcvSpace;

/*move sock_def.h*/
/*****************************************************
* the macro fro tcp,udp, they are define in .c
*****************************************************/
/* used in TCPInput(), it is the second of 24 days */
#define TCP_PAWS_IDLE   (24 * 24 * 60 * 60 * PR_SLOWHZ)
/* 时间表对比  Comparisons of timestamps */
#define TSTMP_LT(a,b)   ((LONG)((a)-(b)) < 0)
#define TSTMP_GEQ(a,b)  ((LONG)((a)-(b)) >= 0)

/* 由于tcp中增加了新的选项,选项的总长度可能达到40字节,因此定义的字符串
 * 长度由32修改为41, TCP MD5 authentication, zhangfeng, 2002,07,20
 */
#define MAX_TCPOPTLEN     /* 32 */ 41 /* 选项中的最大比特数  max # bytes that go in options */


extern SOCKADDRIN_S g_stTcpInAddr;

extern TCPDBUGFILTRD_S  g_stDbugTcpPktFilter;
extern TCPDBUGFILTRD_S  g_stDbugTcpTscFilter;
extern TCPDBUGFILTRD_S  g_stDbugTcpMD5Filter;

extern ULONG g_ulTcpDbugFlag;
extern ULONG g_ulRespondQuench; /* ICMP Quench报文响应开关 */

extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl    *g_pstTCPAddr4Vtbl ;
extern struct IIF_IPV4_IP_PP4_ComIntFUNVtbl         *g_pstTCPPP4Vtbl ;
/* Deleted by qinyun62011, (Distribute socket)分布式socket裁剪，删除无用代码, 2014/3/12 */
//extern struct IIF_IPV4_IP_ICMP_ComIntFUNVtbl     *g_pstTCPICMP4Vtbl ;
/*x36317 在数通，用的原来的FIB，在非数通用的是SFIB 2004-7-16*/
extern struct IIF_COMP_FIBAGENT_ComIntFUNVtbl        *g_pstTCPFIB4Vtbl ;

extern struct IIF_DIST_IP_ComIntFUNVtbl    *g_pstTCPDISTIPVtbl;

extern struct IIF_IP4_SOCK_ComIntFunVtbl    *g_pstTCPSOCK4Vtbl ;

extern struct IIF_COMP_ATK_ComIntFUNVtbl    *g_pstTCPATKVtbl;

extern TCP4_MOD_INFO_S g_stTCP4ModInfo;

extern IP4_TCP4_SH_CALLBACUP_SET_S g_stTCPCallBack;


/* 回调函数  shell call back functions  */
#define     TCP_SHELL_SENDINFO2IC       (g_stTCPCallBack.pfIP4_TCP4_SH_SendInfo2IC)
#define     TCP_SHELL_DEBUGPACKET       (g_stTCPCallBack.pfIP4_TCP4_DbugPkt)
#define     TCP_SHELL_DEBUGMD5          (g_stTCPCallBack.pfIP4_TCP_MD5Debug)
#define     TCP_SHELL_MD5AUTHFAILTRAP   (g_stTCPCallBack.pfTCP_MD5AuthenFailTrap)

/* 宏：获取/设置sock成员变量  get/set sock member variables  */
#define     TCP_SOCKET_GET_PARAM        (g_pstTCPSOCK4Vtbl->pfSOCK_GetParameter)
#define     TCP_SOCKET_SET_PARAM        (g_pstTCPSOCK4Vtbl->pfSOCK_SetParameter)

/* 宏：获取/设置inpcb变量  macro: get/set inpcb variables  */
#define     TCP_INPCB_GET_PARAM         (g_pstTCPSOCK4Vtbl->pfINPCB_GetParameter)
#define     TCP_INPCB_SET_PARAM         (g_pstTCPSOCK4Vtbl->pfINPCB_SetParameter)

/*macro: socket syscall for tcp*/
#define TCP_SOCKET_ISDISCONNECTED       g_pstTCPSOCK4Vtbl->pfSO_IsDisconnected
#define TCP_SOCKET_ISCONNECTED          g_pstTCPSOCK4Vtbl->pfSO_IsConnected
#define TCP_SOCKET_ISCONNECTING         g_pstTCPSOCK4Vtbl->pfSO_IsConnecting
#define TCP_SOCKET_ISDISCONNECTING      g_pstTCPSOCK4Vtbl->pfSO_IsDisconnecting
#define TCP_SOCKET_NEWCONN              g_pstTCPSOCK4Vtbl->pfSO_NewConn
#define TCP_SOCKET_SB_DROP              g_pstTCPSOCK4Vtbl->pfSB_Drop
#define TCP_SOCKET_ABORT                g_pstTCPSOCK4Vtbl->pfSO_Abort
#define TCP_SOCKET_SB_APPEND            g_pstTCPSOCK4Vtbl->pfSB_Append
#define TCP_SOCKET_WAKEUP               g_pstTCPSOCK4Vtbl->pfWakeUp
#define TCP_SOCKET_SORWAKEUP(so)        g_pstTCPSOCK4Vtbl->pfSoWakeUp((so), 2)
#define TCP_SOCKET_SOWWAKEUP(so)        g_pstTCPSOCK4Vtbl->pfSoWakeUp((so), 1)
#define TCP_SOCKET_ASYNWAKEUP           g_pstTCPSOCK4Vtbl->pfSO_AsynWakeUp
#define TCP_SOCKET_ASYNRECALL           g_pstTCPSOCK4Vtbl->pfSO_AsynReCall
#define TCP_SOCKET_CANTRECVMORE         g_pstTCPSOCK4Vtbl->pfSO_CantRcvMore
#define TCP_SOCKET_CANTSENDMORE         g_pstTCPSOCK4Vtbl->pfSO_CantSendMore
#define TCP_SOCKET_RESERVE              g_pstTCPSOCK4Vtbl->pfSO_Reserve
#define TCP_SOCKET_HASOUTOFBAND         g_pstTCPSOCK4Vtbl->pfSO_HasOutOfBand
#define TCP_SOCKET_HA_EVENTNOTIFY       (g_pstTCPSOCK4Vtbl->pfSock_Ha_EventNotify)
#define TCP_SOCKET_SB_FLUSH             (g_pstTCPSOCK4Vtbl->pfSB_Flush)

#define TCP_INPCB_NOTIFY                g_pstTCPSOCK4Vtbl->pfINPCB_Notify
#define TCP_INPCB_BIND                  g_pstTCPSOCK4Vtbl->pfINPCB_Bind
#define TCP_INPCB_INIT_CONNECTIONS_HEAD g_pstTCPSOCK4Vtbl->pfINPCB_Init
#define TCP_INPCB_INIT_HASH_HEAD        g_pstTCPSOCK4Vtbl->pfINPCB_HashInit
#define TCP_INPCB_ALLOC                 g_pstTCPSOCK4Vtbl->pfINPCB_Alloc
#define TCP_INPCB_DETACH                g_pstTCPSOCK4Vtbl->pfINPCB_Detach
#define TCP_INPCB_DISCONNECT            g_pstTCPSOCK4Vtbl->pfINPCB_Disconnect
#define TCP_INPCB_CONNECT               g_pstTCPSOCK4Vtbl->pfINPCB_Connect
#define TCP_INPCB_HASHSEARCH            g_pstTCPSOCK4Vtbl->pfINPCB_HashSearch
#define TCP_INPCB_SETPEERADDR           g_pstTCPSOCK4Vtbl->pfINCB_SetPeerAddr
#define TCP_INPCB_SETSOCKADDR           g_pstTCPSOCK4Vtbl->pfINPCB_SetSockAddr
#define TCP_INPCB_HASHLOOKPORT          g_pstTCPSOCK4Vtbl->pfINPCB_HashLookPort
#define TCP_INPCB_RECORDPCB             g_pstTCPSOCK4Vtbl->pfreorderpcbltob

#define TCP_IP_OUTPUT                   g_pstTCPPP4Vtbl->pfIP_Output_ForInternal
#define TCP_PP_SRCROUTE                 (g_pstTCPPP4Vtbl->pfIP_SrcRoute)
#define TCP_PP_STRIPOPTIONS             (g_pstTCPPP4Vtbl->pfIP_StrIpOptions)

/*x36317 在数通，用的原来的FIB，在非数通用的是SFIB 2004-7-16*/
#define TCP_FIB_RTALLOC                  (g_pstTCPFIB4Vtbl->pfIP4_FIB_AllocValid)

#define TCP_SOCKET_HA_NEEDBACKUP         g_pstTCPSOCK4Vtbl->pfSOCK_HA_NeedBackup
#define TCP_SOCKET_HA_BACKUPNOTIFY       g_pstTCPSOCK4Vtbl->pfSOCK_HA_BackupNotify

#define TCP_SOCKET_CHECKCOOKIESTART      g_pstTCPSOCK4Vtbl->pfSO_CheckCookieStart

typedef ULONG (*TCP_NEED_CLOSE_HOOK)(VOID *pSocket);
extern TCP_NEED_CLOSE_HOOK g_pfTcpNeedClose;

VOID TCP_DecrReassSegNum();

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

