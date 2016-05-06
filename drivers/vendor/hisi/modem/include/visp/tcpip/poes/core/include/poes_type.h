/*******************************************************************************
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poes_type.h
*
* Project Code: VISPV100R006C02
*  Module Name: POES
* Date Created: 2007-07-18
*       Author: lijing(52889)
*  Description: POES模块的数据结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-18   lijing(52889)           Create
*
*******************************************************************************/

#ifndef  _POES_TYPE_H_
#define  _POES_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* PPPoE报文首部，包括以太首部 */
typedef struct tagPoesEtherPppoe
{
    UCHAR  szDestMacAddr[POES_MAC_LEN]; /* 目的mac */
    UCHAR  szSourMacAddr[POES_MAC_LEN]; /* 源mac */
    USHORT usProType;   /* 协议号 */
    UCHAR  ucVerType;   /* PPPoE报文的ver和type */
    UCHAR  ucCode;      /* PPPoE报文的code */
    USHORT usSesId;     /* PPPoE报文的session id */
    USHORT usLength;    /* PPPoE报文的报文负载部分长度 */
} POES_ETHPOE_S;

/* 对端MAC控制块 */
typedef struct tagPoesHisMac
{
    DLL_NODE_S stDLLNode;   /* 双链表节点 */
    UCHAR      aucHisMacAddr[POES_MAC_LEN]; /* 对端physical地址 */
    USHORT     usSessionNum;/* 与对端physical地址建立Session的数目 */
} POES_HIS_MAC_S;

/* Session控制块 */
typedef struct tagPoesSb
{
    struct tagPoesCb *pstPoesCb;    /* PPPoE控制块指针 */
    POES_HIS_MAC_S *pstHisMac;      /* 对端physical地址控制块指针 */
    IFNET_S *pstEthIf;      /* 对应以太网接口IFNET指针 */
    IFNET_S *pstVAIf;       /* 对应VA子通道的IFNET指针 */
    USHORT usSessionId;     /* 本Session的ID */
    UCHAR  ucSesState;      /* 本Session协商状态 */
    UCHAR  ucTimeCounter;   /* PADI状态Session清除定时计数器 */
    ULONG  ulInPackets;     /* 收到的包数 */
    ULONG  ulInOctets;      /* 收到的字节数 */
    ULONG  ulInDiscards;    /* 接收时丢弃的包数 */
    ULONG  ulOutPackets;    /* 发送的包数 */
    ULONG  ulOutOctets;     /* 发送的字节数 */
    ULONG  ulOutDiscards;   /* 发送时丢弃的包数 */
}POES_SB_S;

/* Session节点 */
typedef struct tagPoesSessionNode
{
    POES_SB_S *pstSession;/* 对应Session控制块指针 */
    USHORT     usPrev;/* 前一个Session节点 */
    USHORT     usNext;/* 后一个Session节点 */
} POES_SESSION_NODE_S;

/* POES控制块 */
typedef struct tagPoesCb
{
    DLL_NODE_S           stDLLNode; /* 控制块链表节点 */
    ULONG                ulEthIfIndex; /* 对应的以太接口接口索引 */
    ULONG                ulVTIfIndex; /* 本以太接口对应的VT接口索引 */
    UCHAR                aucOurMacAddr[POES_MAC_LEN]; /* 本接口的physical地址 */
    UCHAR                ucPadding[2]; /* 填充字段 */
    UCHAR                szServiceName[POES_SERVICENAME_MAX_LEN]; /* Service Name */
    ULONG                ulNewSessionCount; /* 用于统计Session建立速率 */
    ULONG                ulCurrentEstablishRate; /* 最新Session建立速率 */
    ULONG                ulBurstEstablishRate; /* 最高Session建立速率 */
    ULONG                ulPadiFaliedCount; /* PADI状态超时次数 */
    POES_SESSION_NODE_S *pstSesNodeArray;   /* session节点数组指针 */
    USHORT               usSesNodeArrayLen; /* 当前Session节点数组长度 */
    USHORT               usSessionNum; /* 本接口上建立Session数目*/
    USHORT               usSessFreeIndex; /* 空闲Session节点数组索引 */
    USHORT               usFirstPadiSessIndex; /* PADI状态session链表头节点数组索引 */
    POES_DEBUG_INFO_S    stDebugInfo; /* debug开关 */
} POES_CB_S;

/* POES模块信息 */
typedef struct tagPoesModInfo
{
    ULONG ulMID_POES;
    ULONG ulQUE_POES;
    ULONG ulPoesCb_WaitListID;
} POES_MOD_INFO_S;

/* POES组件Shell向Core注册的回调函数集 */
typedef struct tagPoesShellCallbackSet
{
    VOID (*pfPOES_DebugOutString)(CHAR * szStr);

    ULONG (*pfPOES_CreateQueue)(ULONG ulQueID, ULONG ulGetCntPerTimes,
                                ULONG (*pfPOES_QueDealPacketFunc)(MBUF_S *),
                                ULONG (*pfPOES_QueIsDropThisPacketFunc)(MBUF_S *, ULONG, CHAR *),
                                ULONG ulMaxLen);

    ULONG (*pfPOES_DeleteQue)(ULONG ulQueID);

    ULONG (*pfPOES_ActiveQueue)(ULONG ulQueID);

    ULONG (*pfPOES_DeActiveQueue)(ULONG ulQueID);

    ULONG (*pfPOES_EnQueue)(MBUF_S *);

    ULONG (*pfPOES_DropQueue)(MBUF_S *);

    VOID (*pfPOES_FreePacketInQueue)(ULONG ulQueID, ULONG ulCmd, CHAR * pData);
} POES_SHELL_CALLBACK_SET_S;

#ifdef __cplusplus
}
#endif

#endif

