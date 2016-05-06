/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ppp_lqm.h
*
*  Project Code: VISPV100R006C02
*   Module Name: lqm  
*  Date Created: 2007-7-26
*        Author: yebo(62004)
*   Description: 链路质量检测
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2007-7-26  yebo(62004)         Create the first version.
*
*******************************************************************************/

#ifndef _LQM_DEF_H_
#define _LQM_DEF_H_


#ifdef __cplusplus
extern "C"{
#endif 

#define LQM_ADD_LEN       3    /* 发送LQR报文时需增加的长度 */
#define LQR_PACKET_FIELDLEN 48   /* LQR报文域长度 */
#define LQM_MAXFAILTIME   3    /* 质量差最大探测次数 */
#define LQM_MAXUSABLETIME 3    /* 质量好最大探测次数 */
#define LQM_INSPECTPERIOD 10   /* 质量差时更新报文的间隔*/
#define MAXLOOPSBACK      10   /* 环回最大检测次数 */
#define LQM_MAX_PERIODVALUE 100/* 周期最大值 */
#define LQM_MIN_PERIODVALUE 10/* 周期最小值 */
#define LQRPACKETLEN 52        /* LQR报文长度*/
#define LQM_MAX_GATE 100      /* 阀值最大值 */
#define LQM_DEFAULT_PERIOD 50 /* 默认周期*/
#define LQM_DEFAULT_GATE 80   /*默认门限值*/
#define LQR_MAX_SENDTIME 10   /*链路探测最大次数*/
#define LQR_PERIOD_MINUNIT 10  /* LQR报文发送最小间隔值 */
#define LQR_10MS_TIMERVALUE 10  /* LQR报文发送最小间隔值 */


extern DLL_S g_stLqmDllList;       /* LQM 双向链表 */
extern ULONG g_ulLqmTimerId;       /* LQM周期发送定时器*/

/* 此结构体保存了LQR报文中的统计值字段，包含逻辑字段 */
typedef struct tagPppLqrInfo
{          
    ULONG   ulLastOutLQRs;   /*发出的LQR报文数*/
    ULONG   ulLastOutPackets;/*发出的报文数*/
    ULONG   ulLastOutoctets; /*发出的字节数*/
    ULONG   ulPeerInLQRs;    /*对端接收的LQR报文数*/
    ULONG   ulPeerInPackets; /*对端接收的字节数*/
    ULONG   ulPeerInDiscards;/*对端丢弃的报文数*/
    ULONG   ulPeerInErrors;  /*对端接口到的错误报文数*/
    ULONG   ulPeerInOctets;  /*对端接口的字节数*/
    ULONG   ulPeerOutLQRs;   /*对端发送的LQR报文数*/
    ULONG   ulPeerOutPackets;/*对端发送的报文数*/
    ULONG   ulPeerOutOctets; /*对端发送的字节数*/
    ULONG   ulSaveInLQRs;    /*本端接收LQR报文数*/
    ULONG   ulSaveInPackets; /*本端接收报文数*/
    ULONG   ulSaveInDiscards;/*本端丢弃报文数*/
    ULONG   ulSaveInErrors;  /*本端接收错误报文数*/
    ULONG   ulSaveInOctets;  /*本端接收字节数*/
}PPPLQRINFO_S;

/*链路监测的基本信息*/
typedef struct tagPppLqmInfo
{
    DLL_NODE_S stLqmDllNode;         /* Lqr DLL链表 */
    ULONG  ulInLQRs;                 /*端口接收到的LQR报文计数器 */
    ULONG  ulOutLQRs;                /*端口发送出去LQR报文的计数器 */
    ULONG  ulNumFailure_Up;          /*连续低于关闭链路门限的次数*/
    ULONG  ulNumUsable_Down;         /*连续高于或等于重新启用链路门限的次数*/
    ULONG  ulNumInLQR_Down;          /*连续接收到的LQR报文计数,在链路DOWN掉以后使用*/
    ULONG  ulNumLQRNoEcho;           /*未收到LQR报文时连续发送的LQR报文数*/
    ULONG  ulAllowSendTimeoutID;     /*允许发送LQR报文的最小定时器ID*/
    ULONG  ulLqmTimerSet;            /*Lqr报文发送周期设置值 */
    ULONG  ulLqmTimerCount;          /*Lqr报文发送周期计数值(减计数)*/
    
    PPPINFO_S *pstPppInfo;
    struct tagPppLqrInfo  stFirstLQR;         /* 上次保存的LQR信息 */
    struct tagPppLqrInfo  stSecondLQR;        /* 最新收到的LQR信息 */
    struct tagPppLqrInfo  *pstLastSavedLQR;   /* 上次保存的LQR信息结构体指针 */
    struct tagPppLqrInfo  *pstCurrentLQR;     /* 最新收到的LQR信息结构体指针 */
    ULONG bIsForbidden:1,                     /* 当前链路被禁用标志 */
          bIsAllowSendLQR:1,                  /* 是否允许发送LQR报文*/
          bIsFirstInLqr:1,                    /* 是否是第一个LQR报文*/
          bReserved   : 29;                   /*reserved for later use*/
}PPPLQMINFO_S;



extern ULONG TCPIP_ADP_GetLQRStat(ULONG ulIfIndex,TCPIP_LQR_STAT_S *pstLQRStat);
extern ULONG  PPP_LQM_Delta_ulong(ULONG ulFirstNum, ULONG ulSecondNum);
extern VOID PPP_LQM_Init(PPPINFO_S  *pPppInfo);
extern VOID PPP_LQM_InputLQR(PPPINFO_S  *pPppInfo, UCHAR* pPacket, ULONG ulLen);
extern ULONG PPP_LQM_isLinkUsable(PPPINFO_S  *pPppInfo);
extern VOID PPP_LQM_LinkResume( PPPINFO_S *pPppInfo );
extern VOID PPP_LQM_SendLQR(VOID  *pPppInfo);
extern VOID PPP_LqmTimerOut(VOID *pTemp);
#ifdef __cplusplus
}
#endif 

#endif 

