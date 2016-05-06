/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                               tcpip_dcc.h
*
*  Project Code: VR8C01
*   Module Name: PUBLIC
*  Date Created: 2009-03-25
*        Author: zhangchunyu(62474)
*   Description: 数据连通性检查处理头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-03-25   zhangchunyu(62474)      Create
*******************************************************************************/
#ifndef _TCPIP_DCC_H_
#define _TCPIP_DCC_H_

#ifdef  __cplusplus
extern "C"{
#endif


#include "tcpip/public/debug/tcpip_dcc_api.h"

/*******************************宏*********************************************/
/* DCC写消息队列宏定义*/ 
#define DCC_WriteQueue(ulQueueId,ulMsg,ul_Ret) \
{ \
    ul_Ret = VOS_Que_Write (ulQueueId, ulMsg, VOS_NO_WAIT | VOS_NORMAL, 0);\
}

/* DCC写任务事件宏定义 */
#define DCC_SchedTask(ulEvent) \
{ \
    (VOID)VOS_Ev_Write( g_ulDCCTaskId, ulEvent ); \
}

/* 是本板的ETH或TRUNK接口 */
#define DCC_ISEHTORTRUNK(pstIfNet) \
    ((NULL != pstIfNet) && ((IF_ETHERNET_TYPE == pstIfNet->if_ulType) \
    || (IF_ETH_TRUNK_TYPE == pstIfNet->if_ulType)) && (IF_IS_ThisBoard(pstIfNet)))

#define DCC_EVENT                       0x00000001       /* DCC事件 */

#define DCC_EVENT_START                 0x00000002       /* DCC事件开始 */          
#define DCC_EVENT_TIMER                 (1 << 15)        /* 开始DCC连通检查定时器事件 */

#define DCC_QMODE                       VOS_Q_FIFO     /* 队列标志 */
#define DCC_QUEDEPTH                    (512)       /* DCC队列长度 */

#define DCC_ARP_DETECT_MAX_COUNT        3    /* ARP Ping的最大次数 */
#define DCC_MAX_STEAM                   4    /* 最大统计流个数 */

#define DCC_ENABLE                      1
#define DCC_DISNABLE                    0

#define DCC_MAX_PRI                     255      /* CC任务最大优先级 */
#define DCC_MAX_DATATIME                600  /* 数据统计的最大时间 */


#define DCC_TCPCOMP_ISEXIST             (g_pstDCCTcp4CfgVtbl != NULL)
#define DCC_UDPCOMP_ISEXIST             (g_pstDCCUdp4CfgVtbl != NULL)
#define DCC_RAWIPCOMP_ISEXIST           (g_pstDCCRawip4CfgVtbl != NULL)

#define DCC_PKTFLOW_SEND                0
#define DCC_PKTFLOW_RCV                 1
#define DCC_PKTFLOW_FORWARD             2

#define DCC_IS_ENABLE                   (DCC_ENABLE == g_ulDccPktFlowEnable) /*是否使能DCC功能*/
#define DCC_NOTFOUND                    0
#define DCC_FOUND                       1  

#define DCC_ETHII_HEADER_LEN            14 /*以太头中未带VLAN TAG标签长度*/
#define DCC_IP_HEADER_LEN               20 /*IP头中长度*/
#define DCC_ETHII_ETHTYPE_POSITION_LEN  12 /*以太头中两字节以太类型或长度字段的偏移位置*/
#define DCC_ETHII_VLANTAG_LEN           4  /*以太头中VLAN TAG占用的字节长度*/

#define DCC_ENABLE_PING                 1  /* 在ping操作 */
#define DCC_DISNABLE_PING               0  /* 不在ping做错 */


#define DCC_RECV_DROPSTAT(pMBuf) \
{ \
    if ((DCC_IS_ENABLE) && (NULL != pMBuf) && (MBUF_GET_DCCFLAG(pMBuf) & MBUF_FLAG_DCCSTREAM_RCV)) \
    { \
        ULONG ulLine = __LINE__; \
        UCHAR ucDccFlowId; \
        CHAR  szCurrentFileName[FILENAME_LEN]; \
        TCPIP_GetFileName(__FILE__, szCurrentFileName, FILENAME_LEN); \
        ucDccFlowId = MBUF_GET_DCC_FLOWID(pMBuf); \
        (VOID)TCPIP_strncpy(g_stDccStat.stDccStat[ucDccFlowId].stRcvStat.cFileName, FILENAME_LEN, szCurrentFileName, FILENAME_LEN - 1); \
        g_stDccStat.stDccStat[ucDccFlowId].stRcvStat.ulFileLine = ulLine; \
        MBUF_SET_DCCFLAG(pMBuf, MBUF_FLAG_DCCSTREAM_DESTROY); \
    } \
}

#define DCC_SEND_DROPSTAT(pMBuf) \
{ \
    if ((DCC_IS_ENABLE) && (NULL != pMBuf) && (MBUF_GET_DCCFLAG(pMBuf) & MBUF_FLAG_DCCSTREAM_SND)) \
    { \
        ULONG ulLine = __LINE__; \
        UCHAR ucDccFlowId; \
        CHAR  szCurrentFileName[FILENAME_LEN]; \
        TCPIP_GetFileName(__FILE__, szCurrentFileName, FILENAME_LEN); \
        ucDccFlowId = MBUF_GET_DCC_FLOWID(pMBuf); \
        (VOID)TCPIP_strncpy(g_stDccStat.stDccStat[ucDccFlowId].stSndStat.cFileName, FILENAME_LEN, szCurrentFileName, FILENAME_LEN - 1); \
        g_stDccStat.stDccStat[ucDccFlowId].stSndStat.ulFileLine = ulLine; \
        MBUF_SET_DCCFLAG(pMBuf, MBUF_FLAG_DCCSTREAM_DESTROY); \
    } \
}


/*******************************枚举变量***************************************/

/* 增加enumDccInfo类型, 一定要增加g_stDccInfoString相关字符串 */
enum enumDccInfo
{
    DCC_INFO_START = 0,              /* 开始,打印诊断标题 */
    DCC_INFO_INTFPHYUP,              /* 接口底层UP */   
    DCC_INFO_INTFPHYDOWN,            /* 接口底层Down */ 
    DCC_INFO_LINEDOWN,               /* ETH或TRUNK接口协议状态不是UP*/
    DCC_INFO_LINEUP,                 /* 接口协议状态是UP*/
    DCC_INFO_LCPDOWN,
    DCC_INFO_LCPOPEN,
    DCC_INFO_PPPIPCPOPEN,
    DCC_INFO_PPPIPCPDOWN,
    DCC_INFO_MPIPCPOPEN,
    DCC_INFO_MPIPCPDOWN,
    DCC_INFO_NOFIB,
    DCC_INFO_EXISTFIB,
    DCC_INFO_EXISTARP,
    DCC_INFO_ARPDETECTOK,
    DCC_INFO_NOARP,   
    DCC_INFO_PINGOK,
    DCC_INFO_PINGFAIL,
    
    DCC_INFO_NOINPCB,
    DCC_INFO_INPCB,
    DCC_INFO_NOTCPCB,
    DCC_INFO_TCPCB,
    DCC_INFO_NOSOCKETCB,
    DCC_INFO_SOCKETCB,
    DCC_INFO_NOINPCB_EISTSOCKETCB,
    DCC_INFO_NOSOCKETID,
    DCC_INFO_EXISTSOCKETID,
    DCC_INFO_NOTSAME_SOCKETTYPE,
    DCC_INFO_NOTSAMESOCKET,
    
    DCC_INFO_TCP_ISNOTBEGINCONNECT,
    DCC_INFO_TCP_ISCONNECTING,
    DCC_INFO_TCP_ISCONNECTTED,
    DCC_INFO_TCP_ISDISCONNECTING,
    DCC_INFO_TCP_TCPS_FATHERLISTEN,
    DCC_INFO_TCP_TCPS_SONLISTEN,    
    DCC_INFO_TCP_TCPS_SYN_SENT,
    DCC_INFO_TCP_TCPS_SYN_RECEIVED,
    DCC_INFO_TCP_LOCALCLOSE,
    DCC_INFO_TCP_REMOTECLOSE,
    DCC_INFO_TCP_LRCLOSE,
    DCC_INFO_TCP_TCPS_FIN_WAIT_1,
    DCC_INFO_TCP_TCPS_FIN_WAIT_2,
    DCC_INFO_TCP_TCPS_TIME_WAIT,
    DCC_INFO_TCP_TCPS_CLOSE_WAIT,
    DCC_INFO_TCP_TCPS_LAST_ACK,
    
    DCC_INFO_TCP_NOACCEPT,
    DCC_INFO_TCP_ACCEPT,
    DCC_INFO_TCP_USERCLOSE,
    DCC_INFO_TCP_TCPCLOSE,
    DCC_INFO_TCP_SHUTDOWNWRITE,
    DCC_INFO_TCP_SHUTDWONREAD,
    DCC_INFO_TCP_RECVFIN,
    DCC_INFO_TCP_SHUTDOWNRW,
    DCC_INFO_TCP_SOCKETCLOSE,
    DCC_INFO_TCP_SOCKETRWOK,

    DCC_INFO_FLOWSTAT_RCV,
    DCC_INFO_FLOWSTAT_SND,
    DCC_INFO_FLOWNOSTREAM,
    DCC_INFO_ICMPERROR_RCV,
    DCC_INFO_CREATE_DCCTIME_ERR,
    DCC_INFO_INNER_ABEND,
    DCC_INFO_DELETINTF_BYDCC,
    DCC_INFO_USERSTOP,

    DCC_INFO_END,                   /* 诊断完毕 */
};


typedef enum enumDccFlowStatResult
{
    DCC_FLOW_NO_DISCARD,
    DCC_FLOW_LINK_DISCARD,
    DCC_FLOW_NETWORK_DISCARD,
    DCC_FLOW_TRAN_DISCARD,
}DccFlowStatResult_E;


/* DCC 诊断结果 */
enum enumDccDiagResult
{
    DCC_DIAG_SUCCESS = VOS_OK,          /* 0 没有问题 */
    DCC_DIAG_FAILED,               /* 1 存在问题 */
};

/*******************************数据结构***************************************/
typedef struct tagSTREAMINFO_S
{
    ULONG   ulProType;                               /* 协议类型 */
    ULONG   ulSipAddr;                               /* 源地址,主机序 */
    ULONG   ulDipAddr;                               /* 目的地址,主机序 */
    USHORT  usSport;                                 /* 源端口号 */
    USHORT  usDport;                                 /* 目的端口号,主机序 */
}STREAMINFO;


typedef struct tagDCC_STREAMSTAT_RCV
{
    ULONG ulRcvIfIndex;/*链路类型是以太还是PPP*/
    
    /* LINK层统计信息 */
    ULONG ulRcvLinkBegin;
    ULONG ulRcvLinkVlan;
    ULONG ulRcvLinkEnd;    

    /* IP层统计信息 */   
    ULONG ulRcvIPBegin;    
    ULONG ulRcvInputAllPktIntermediateHook;  
    ULONG ulRcvInputLocalPktIntermediateHook;
    ULONG ulRcvWrongIPCheckSum;
    ULONG ulRcvIPNoFrag;    
    ULONG ulRcvIPtoIPFrag;    
    ULONG ulRcvIPFragFail;  
    ULONG ulRcvIPFragOK;  

    ULONG ulRcvIcmpBegin;
    ULONG ulRcvIcmpErrNum;
    ULONG ulRcvIcmpErrType;
    ULONG ulRcvIcmpErrCode;
    ULONG ulRcvIcmpBadCode;
    ULONG ulRcvIcmpEnd;
    ULONG ulRcvIPEnd;    

    /* TRAN层统计信息 */ 
    ULONG ulRcvTranBegin;
    
    ULONG ulRcvTcpHook;
    ULONG ulRcvUdpInterMediate;
    ULONG ulRcvUdpHook;
    ULONG ulRcvUdpBfd;
    ULONG ulRcvRawHook;

    ULONG ulRcvTcpZeroPacket;
    ULONG ulRcvDropTcpDupPacket;
    ULONG ulRcvDropTcpQueDupPacket;
    ULONG ulRcvDropTcpAfterWinPacket;
    
    ULONG ulRcvTcpReassQuePacket;
    
    ULONG ulRcvDropTcpNotRcvMore;
    ULONG ulRcvDropTcpClose;
    
    ULONG ulRcvTranEnd;
    
    ULONG ulMbufDestroy;
    
    CHAR  cFileName[FILENAME_LEN]; /*记录当前调用函数的文件名*/
    ULONG ulFileLine;              /*记录当前调用函数的行号*/
}DCC_STREAMSTAT_RCV_S;


typedef struct tagDCC_STREAMSTAT_SND
{
    ULONG ulSndIfIndex; /*链路类型是以太还是PPP*/
        
    /* LINK层统计信息 */
    ULONG ulSndLinkBegin;
    ULONG ulSndETHOutHookFunc;
    ULONG ulSndMpFragNum;
    ULONG ulSndPppMuxNum;
    ULONG ulSnd3DVirtualNum;
    ULONG ulSndLinkEnd;


    
    /* IP层统计信息 */   
    ULONG ulSndIPBegin;
    ULONG ulSndAllPktIntermediateHook;
    ULONG ulSndLocalPktIntermediateHook;
    ULONG ulSndIpOutputPPI;
    ULONG ulSndIpWholePktHook;
    ULONG ulSndIpMplsHook;
    ULONG ulSndIPNoFrag;
    ULONG ulSndIPFragOK;
    ULONG ulSndIPtoIPFrag;
    ULONG ulSndIPFragFail;
    ULONG ulSndIPEnd;

    /* TRAN层统计信息 */ 
    ULONG ulSndTranBegin;    
    ULONG ulSndTranEnd;  

    ULONG ulMbufDestroy;

    CHAR  cFileName[FILENAME_LEN]; /*记录当前调用函数的文件名*/
    ULONG ulFileLine;              /*记录当前调用函数的行号*/
}DCC_STREAMSTAT_SND_S;


typedef struct tagDCC_STREAMSTAT
{
    ULONG                ulStreamNum;              /* 数据流号码 */
    STREAMINFO           stStreamInfo;

    DCC_STREAMSTAT_RCV_S stRcvStat;
    DCC_STREAMSTAT_SND_S stSndStat;
    
}DCC_STREAMSTAT_S;

/* 全局DCC检查报告统计信息 */
typedef struct tagDccStat
{
    ULONG ulExecID;                              /* 用户输出ID */
    ULONG ulDataStatTime;                        /* 统计时间,单位秒 */
    TCPIP_DCC_S stUserDcc;                       /* 用户输入DCC参数 */
    ULONG ulOutIfIndexforDip;                    /* 根据目的地址获取的出接口索引 */
    ULONG ulOutIfIndexforSip;                    /* 根据源地址获取的出接口索引 */
    ULONG ulNextHopforDip;                       /* 根据目的地址获取的下一跳IP*/
    ULONG ulNextHopforSip;                       /* 根据源地址获取的下一跳IP*/
    ULONG ulHaveSteam;                           /* 当前存在多少个流 */
    DCC_STREAMSTAT_S stDccStat[DCC_MAX_STEAM];   /* 数据统计流 */ 
}DCC_STAT_S;

typedef struct tagDccOutput
{
   ULONG  ulKindID;
   ULONG  ulIfIndex;
   ULONG  ulFatherIfIndex;
   ULONG  ulDiagnoseID;
   ULONG  ulIpAddr;
   ULONG  ulFlowSndResult;
   ULONG  ulFlowRcvResult;
   ULONG  ulFlowID;
   CHAR   szInfoBuf[1024];
 }DCC_OUTPUT_S;

/*******************************全局变量声明***************************************/
extern ULONG g_ulDCCTimerQueId;
extern ULONG g_ulDccPktFlowEnable; /*是否使能DCC功能开关*/
extern DCC_STAT_S g_stDccStat;
extern ULONG g_ulDCCTaskId;
extern ULONG g_ulDccOperNum; 


/*******************************其他模块需要调用的函数声明***************************************/
extern ULONG DCC_FlowClassifyInMBuf(MBUF_S *pMBuf, ULONG ulRouteFlag, ULONG ulProType);
extern VOID DCC_FlowClassifyRcvMbuf(IFNET_S *pstIfnet, MBUF_S *pstMbuf);
extern VOID DCC_FlowClassifyMbufAtIpLayer(MBUF_S *pstMbuf, ULONG ulDirect, ULONG ulSendFlag, ULONG ulVrfIndex);
extern VOID DCC_IcmpErrorFlowCheck(MBUF_S *pstMBuf, LONG lHLen);

#ifdef  __cplusplus 
}
#endif
#endif /* _TCPIP_DCC_H_ */

