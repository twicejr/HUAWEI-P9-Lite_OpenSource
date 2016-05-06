/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              poec_type.h 
 *
 *  Project Code: VISP1.5
 *   Module Name: PPPoE Client
 *  Date Created: 2003-01-11
 *        Author: liuhui
 *   Description: PPPoE Client模块的Core部分数据结构定义
 *               
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE             NAME               DESCRIPTION
 *  2003-01-11       liuhui             Create file
 *  2005-09-15       t45114             Modify
 *  2006-03-30       liai               Adjust for D00660
 *  2006/04/21       liai               Adjust for D00865
 *   
 ************************************************************************/

#ifndef  _POEC_TYPE_H_
#define  _POEC_TYPE_H_

#ifdef __cplusplus
extern "C"{
#endif



/* PPPoE Client控制块结构，每个封装了PPPoE的以太网接口对应一个PPPoE Client控制块 */
typedef struct tagPppoeClientCb
{
    DLL_NODE_S  stPoeClientDllNode;             /* 控制块链表节点 */
    ULONG       ulEthIfIndex;                   /* 对应的以太网IFNET索引 */
    DLL_S       stPPPoEClientPendingSession;    /* 该以太网接口上处于Discovery阶段的Session链表 */
    DLL_S       stPPPoEClientConnectedSession;  /* 该以太网接口上处于Session阶段的Session链表 */
} PPPOE_CLIENT_CB_S;


/* PPPoE Client Session控制块数据结构*/
typedef struct tagPPPoE_C_Session
{
    DLL_NODE_S        stSessionNode;/*PPPoE Client Session节点*/
    
    UCHAR             szOurMacAddr[PPPOE_MAC_LEN];/*Client physical地址 */
    UCHAR             szHisMacAddr[PPPOE_MAC_LEN];/*Server physical地址 */
    

    PPPINFO_S         *pstLinkHandle;       /*PPPoE Client Session所对应的PPP 控制块指针*/
    PPPOE_CLIENT_CB_S *pstPoeClientCB;      /*PPPoE Client Session所对应的PPPOE Client控制块指针*/
        
    ULONG             ulDisTickCounter;     /*discovery阶段tick计数，用于padi,padr报文超时处理 */
    ULONG             ulDisTimerMaxLength;  /*discovery阶段定时器长度，不同的阶段，值会不同*/

    ULONG             ulIdleTickCounter;    /*IDLE Timeout定时器tick计数 */
    ULONG             ulIdleToutMaxLength;  /*IDLE Timeout定时器时长，通过命令行配置，缺省为0*/

    MBUF_QUEUE_S      stHoldQueue;          /*存放interesting 报文的hold queue*/

    IFNET_S           *pstEthIf;            /* 对应以太网接口IFNET指针 */
    IFNET_S           *pstVAIf;             /* 对应virtual access接口IFNET指针 */
    IFNET_S           *pstDialerIf;         /*对应的dialer 口指针*/
    
    USHORT            usBundleNumber;       /*对应的dialer口bundle number,命令行配置*/
    USHORT            usSessionId;          /* 本Session的ID */
    
    UCHAR             ucSessionTrigger;     /*PPPoE Session是否为报文触发方式*/    
    UCHAR             ucHostUniq;           /*PADI是否携带host unique，命令行配置，默认携带*/
    USHORT            usHostUniqValue;      /*discovery阶段报文所携带的host-unique*/

    MBUF_S            *pstPadrMbuf;         /*上一次发送的padr报文备份*/
    
    ULONG             ulInPacket;           /* 收到的包数 */
    ULONG             ulInOctets;           /* 收到的字节数 */
    ULONG             ulInDiscards;         /* 接收时丢弃的包数 */
    ULONG             ulOutPacket;          /* 发送的包数 */
    ULONG             ulOutOctets;          /* 发送的字节数 */
    ULONG             ulOutDiscards;        /* 发送时丢弃的包数 */
    ULONG             ulInGRDiscards;       /* 处于GR保活状态时接收方向的丢包计数 */
    ULONG             ulOutGRDiscards;      /* 处于GR保活状态时发送方向的丢包计数 */

    UCHAR             ucSessionState;       /* PPPoE Client Session所处的阶段 */
    UCHAR             ucSessionGRState;     /* PPPOE会话的保活状态，取值见enumPPPOE_GR_STATE */
    UCHAR             ucNotifyNpFlag;       /* 通知NP创建/删除会话的标记 */
    UCHAR             ucReserve;            /*保留*/
} PPPOE_C_SESSION_S;

/*以太网帧头数据结构*/
typedef struct tagPPPoEEtherAddr
{
    UCHAR szDestMacAddr[PPPOE_MAC_LEN]; /* 目的地址 */
    UCHAR szSourMacAddr[PPPOE_MAC_LEN]; /* 源地址 */
} PPPOE_ETHER_ADDR_S;

/* module info structure of PPPoE Client */
typedef struct tagPPPOE_CLIENT_MOD_INFO_S
{
    ULONG ulModID;              /* Module id*/
    ULONG ulEthMaxSessionNum;   /*以太口最大可以承载的PPPoE Client会话*/
    ULONG ulQueID;
    
} PPPOE_CLIENT_MOD_INFO_S;

/* shell api structure of SAPRO */
typedef struct tagPPPOEClientShellCallback
{
    VOID (*pfPPPOE_Client_DbgOut) ( CHAR *strDbgOut );
    VOID (*pfPPPOE_Client_CFG_ExecOutStr) ( ULONG ulExecID, ULONG ulInfoID );
    VOID (*pfPPPOE_Client_CreateDisTimer) ( VOID );
    VOID (*pfPPPOE_Client_CreateIdleTimer) ( VOID );
    VOID (*pfPPPOE_Client_DeleteDisTimer) ( VOID );
    VOID (*pfPPPOE_Client_DeleteIdleTimer) ( VOID );
    VOID (*pfPPPOE_Client_PauseDisTimer) ( VOID );
    VOID (*pfPPPOE_Client_ResumeDisTimer) ( VOID );
    
}PPPOE_CLIENT_SHELL_CALLBACK_S;

/*PPPoE Session统计信息*/
typedef struct tagPPPOECSTAT_S
{ 
    IFNET_S          *pstDialerIf;      /* 对应的dialer 口指针 */
    IFNET_S          *pstEthIf;         /* 对应以太网接口IFNET指针 */
    
    USHORT            usSessionId;      /* 本Session的ID */
    USHORT            usBundleNumber;   /* 对应的dialer口bundle number,命令行配置 */

    UCHAR             szOurMacAddr[PPPOE_MAC_LEN]; /* Client physical地址 */
    UCHAR             szHisMacAddr[PPPOE_MAC_LEN]; /* Server physical地址 */
    
    ULONG             ulInPacket;       /* 收到的包数 */
    ULONG             ulInOctets;       /* 收到的字节数 */
    ULONG             ulInDiscards;     /* 接收时丢弃的包数 */
    ULONG             ulOutPacket;      /* 发送的包数 */
    ULONG             ulOutOctets;      /* 发送的字节数 */
    ULONG             ulOutDiscards;    /* 发送时丢弃的包数 */
    ULONG             ulInGRDiscards;   /* 处于GR保活状态时接收方向的丢包计数 */
    ULONG             ulOutGRDiscards;  /* 处于GR保活状态时发送方向的丢包计数 */

    UCHAR             ucSessionState;   /* PPPoE Client Session所处的阶段 */
    UCHAR             ucReserve[3];     /* 保留 */
 
}PPPOECSTAT_S;

/*VA接口下统计信息*/
typedef struct tagVASTAT_S
{
    ULONG             ulLinkStatus;     /* 链路层状态 */

    ULONG             ulInOctets;       /* 收到的字节数 */
    ULONG             ulOutOctets;      /* 发送的字节数 */
    ULONG             ulInPackets;      /* 收到的包数 */
    ULONG             ulOutPackets;     /* 发送的包数 */
    ULONG             ulBadFcsPackets;
    ULONG             ulBadAddressPackets;
    ULONG             ulBadControlPackets;
}VASTAT_S;


#ifdef __cplusplus
}
#endif

#endif 


