/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pppmux_type.h
*
*  Project Code: VISPV100R005
*   Module Name: PPPMUX
*  Date Created: 2006-5-11
*        Author: ZhouTong(43740)
*   Description: PPPMUX模块的类型定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-5-11  ZhouTong(43740)   Create
*
*******************************************************************************/

#ifndef _PPPMUX_TYPE_H_
#define _PPPMUX_TYPE_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/ppp/include/pppmux_api.h"



/* PPPMUXCP控制块数据结构 */
typedef struct tagPppMuxcpInfo
{
    PPPINFO_S *pstPppInfo;              /* PPP控制块指针 */
    PPPFSM_S  stFsm;                    /* MUXCP协议状态机 */
    PPP_MUXCP_OPTION_S stGotOptions;    /* 已经协商到的我的选项 */
    PPP_MUXCP_OPTION_S stHisOptions;    /* 已经协商到的对方的选项 */
    PPP_MUXCP_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_MUXCP_OPTION_S stAllowOptions;  /* 允许与对方协商的我的选项 */
    DLL_NODE_S stPppInfoLink;           /* 构造PPP协议控制块的链表指针 */
} PPPMUXCPINFO_S ;

/* PPPMUX复合结构 */
typedef struct tagPPPMUX_MUX_STRUCT
{
    ULONG   ulBeginHigh;        /*复合开始时间,高32位*/
    ULONG   ulBeginLow;         /*复合开始时间,低32位*/
    USHORT  usLastPID;          /*复合协议号*/
    USHORT  usFrameLen;         /*当前复合帧长度*/
    USHORT  usPayLoadLen;       /*当前报文净荷长度*/
    USHORT  usSubFrameCount;    /*当前子帧个数*/
    MBUF_S *pstMuxMBuf;         /*复合报文*/
}PPPMUXSTRUCT_S;

/* PPPMUX复合上下文存储结构 */
typedef struct tagPPPMUX_CONTEXT_STRUCT
{
    PPPMUXSTRUCT_S stMuxStructArray[MC_MAX_LSCLASS];
    PPPMUXSTATS_S  stMuxStat;
}PPPMUXCONTEXT_S;


/*PPPMUX模块信息*/
typedef struct tagMUXCP_ModInfo
{
    ULONG ulMID_PPPMUX;          /*模块ID*/
    ULONG ulQUE_PPPMUX_INPUT;    /*接收队列ID*/
    ULONG ulCPU_TICKS_PER_MS;    /*每毫秒CPU Ticks*/
    ULONG ulNPMode;              /*NP模式标记*/
}PPPMUX_MOD_INFO_S;

/*shell 向core注册的回调函数集合*/
typedef struct tagPPPMUX_SHELL_CALLBACK
{
    ULONG (*pfQOS_GetPacketClass)(ULONG ulIfIndex, MBUF_S* pstMBuf,UCHAR* pulClass);    
    VOID  (*pfPPPMUX_DebugOutput)(CHAR *pInfo);
}PPPMUX_SHELL_CALLBACK_S;

/* 添加协商选项宏 */
#define ADDCIPID(opt, neg, val) \
{\
    if (neg)\
    { \
        PPP_PUTCHAR(opt, pucPacket); \
        PPP_PUTCHAR(MUXCP_CILEN_PID, pucPacket); \
        PPP_PUTSHORT(val, pucPacket); \
    }\
}

/* 分析收到的ACK报文PID选项宏 */
#define ACKCIPID(opt, neg, val) \
{\
    if (neg) \
    { \
        if ((LONG)(ulLen -= MUXCP_CILEN_PID) < 0) \
        {\
            goto bad; \
        }\
        PPP_GETCHAR(ucCiType, pucPacket); \
        PPP_GETCHAR(ucCiLen,  pucPacket); \
        if ( (ucCiLen != MUXCP_CILEN_PID) || (ucCiType != opt) ) \
        {\
            goto bad; \
        }\
        PPP_GETSHORT(usCiShort, pucPacket); \
        if (usCiShort != val) \
        {\
            goto bad; \
        }\
    }\
}

/* 处理受到的NAK报文的PID选项宏 */
#define NAKCIPID(opt, neg, code) \
{\
    if (pstGotOptions->neg && ulLen >= MUXCP_CILEN_PID && \
        MUXCP_CILEN_PID == pucPacket[1] && pucPacket[0] == opt) \
    { \
        ulLen -= MUXCP_CILEN_PID; \
        PPP_INCPTR(MUXCP_CILEN_VOID, pucPacket); \
        PPP_GETSHORT(usCiShort, pucPacket); \
        stNoOption.neg = 1; \
        code \
    }\
}

/* 处理收到的REJ报文PID选项宏 */
#define REJCIPID(opt, neg, val) \
{\
    if (pstGotOptions->neg && ulLen >= MUXCP_CILEN_PID && \
        MUXCP_CILEN_PID == pucPacket[1] && pucPacket[0] == opt) \
    { \
        ulLen -= MUXCP_CILEN_PID; \
        PPP_INCPTR(MUXCP_CILEN_VOID, pucPacket); \
        PPP_GETSHORT(usCiShort, pucPacket); \
        /* Check rejected value. */ \
        if(usCiShort != val) \
        {\
            goto bad; \
        }\
        stTryOption.neg = 0; \
    }\
}

/* 协商结果不可接受,结束协商 */
#define PPP_MUXCP_NegotiationDown(pMuxcpInfo)\
{\
    PPP_MUXCP_ReceiveEventFromCore(pMuxcpInfo, (ULONG)PPP_EVENT_FSM_CLOSE, NULL); \
    PPP_MUXCP_ReceiveEventFromCore(pMuxcpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL); \
}

#ifdef  __cplusplus
}
#endif

#endif /* end of _PPPMUX_TYPE_H_ */
