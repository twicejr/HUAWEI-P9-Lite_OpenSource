/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_type.h
*
*  Project Code:
*   Module Name: PTPV2 type
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description: 主要提供给产品以及CBB自己调用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _PTPV2_TYPE_h_
#define _PTPV2_TYPE_h_

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)
/* PTP消息头部 */
/*
   Bits                                  Octets  Offset
   7     6     5     4   3   2   1   0
   |transportSpecific|  messageType  |     1       0
   |    reserved     |  versionPTP   |     1       1
   |           messageLength         |     2       2
   |           domainNumber          |     1       4
   |           reserved              |     1       5
   |           flagField             |     2       6
   |           correctionField       |     8       8
   |           reserved              |     4       16
   |           sourcePortIdentity    |     10      20
   |           sequenceId            |     2       30
   |           controlField          |     1       32
   |           logMessageInterval    |     1       33

*/
typedef struct tagPTPV2_MSGHEADER_S
{
    #if (VRP_LITTLE_ENDIAN == VRP_YES)
    UCHAR            ucmessageType              : 4 ;   /* 消息类型，详细定义见消息类型定义 */
    UCHAR            uctransportSpecific        : 4 ;
    #else
    UCHAR            uctransportSpecific        : 4 ;
    UCHAR            ucmessageType              : 4 ;   /* 消息类型，详细定义见消息类型定义 */
    #endif

    #if (VRP_LITTLE_ENDIAN == VRP_YES)
    UCHAR            ucversionPTP               : 4 ;   /* PTP版本号，本次实现1588v2，因此版本号为2 */
    UCHAR            ucreserved4                : 4 ;   /* 预留 */
    #else
    UCHAR            ucreserved4                : 4 ;   /* 预留 */
    UCHAR            ucversionPTP               : 4 ;   /* PTP版本号，本次实现1588v2，因此版本号为2 */
    #endif

    USHORT           usmessageLength                ;   /* 消息长度，包括消息头 */
    UCHAR            ucdomainNumber                 ;   /* 域号 */
    UCHAR            ucreserved2                    ;   /* 预留 */
    UCHAR            ucflagField[2]                 ;   /* 标志域 */
    UULONG           uulcorrectionField             ;   /* 修正域，Announce/Signaling/Management消息该字段填0 */
    UCHAR            ucreserved[4]                  ;   /* 预留 */
    TCPIP_PTP_PORT_ID_S stSourcePortIdentity           ;   /* 时钟ID */
    USHORT           usSequenceId                   ;   /* 序列号 */
    UCHAR            ucControlField                 ;   /* 控制域 */
    CHAR             cLogMessageInterval            ;   /* 消息间隔，由消息类型决定 */
}PTPV2_MSGHEADER_S;

/* 时间戳定义 */ 
typedef struct tagPTPV2_TIMESTAMP_S
{
    USHORT  usSecondsHigh;
    ULONG   ulSecondsLow;
    ULONG   ulNanoseconds;
}PTPV2_TIMESTAMP_S;
 
/* Announce消息格式 */
/*
  Bits                                Octets      Offset
  |7   6   5   4   3   2   1   0
  |    header (see 13.3)       |          34      0
  |    originTimestamp         |          10      34
  |    currentUtcOffset        |          2       44
  |    reserved                |          1       46
  |    grandmasterPriority1    |          1       47
  |    grandmasterClockQuality |          4       48
  |    grandmasterPriority2    |          1       52
  |    grandmasterIdentity     |          8       53
  |    stepsRemoved            |          2       61
  |    timeSource              |          1       63
*/
typedef struct tagPTPV2_ANNOUNCE_MSG_S
{
    PTPV2_MSGHEADER_S       stMsgHeader                    ;   /* 消息头 */
    PTPV2_TIMESTAMP_S       stOriginTimestamp              ;   /* 源时间戳 */
    SHORT                   sCurrentUtcOffset              ;   /* 当前UTC偏移 */
    UCHAR                   ucreserved                     ;   /* 预留 */
    UCHAR                   ucGrandmasterPriority1         ;   /* 优先级1 */
    TCPIP_PTP_CLOCK_QA_S    stGrandmasterClockQuality      ;   /* 时钟质量 */
    UCHAR                   ucGrandmasterPriority2         ;   /* 优先级2 */
    TCPIP_PTP_CLOCK_ID_SZ   stGrandmasterIdentity          ;   /* master时钟id */
    USHORT                  usStepsRemoved                 ;   /*  */
    UCHAR                   ucTimeSource                   ;   /* 时钟源 */ 
}PTPV2_ANNOUNCE_MSG_S;

/* Sync 和 Delay_Req消息格式 */
/*
  Bits                             Octets  Offset
  7   6   5   4   3   2   1   0
  |    header (see 13.3)      |    34      0
  |    originTimestamp        |    10      34
*/
typedef struct tagPTPV2_SYNC_MSG_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    PTPV2_TIMESTAMP_S   stOriginTimestamp              ;   /* 源时间戳 */
}PTPV2_SYNC_MSG_S;

typedef struct tagPTPV2_DELAY_REQ_MSG_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    PTPV2_TIMESTAMP_S   stOriginTimestamp              ;   /* 源时间戳 */
}PTPV2_DELAY_REQ_MSG_S;

/* Delay_Resp消息格式 */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    receiveTimestamp        |   10      34
    |    requestingPortIdentity  |   10      44
*/
typedef struct tagPTPV2_DELAY_RESP_MSG_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    PTPV2_TIMESTAMP_S   stReceiveTimestamp             ;   /* 接收时间戳 */
    TCPIP_PTP_PORT_ID_S stRequestingPortIdentity       ;   /* 请求端口 */
}PTPV2_DELAY_RESP_MSG_S;

/* Pdelay_Req消息格式 */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    originTimestamp         |   10      34
    |    reserved                |   10      44
*/
typedef struct tagPTPV2_PDELAY_REQ_MSG_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    PTPV2_TIMESTAMP_S   stOriginTimestamp              ;   /* 源时间戳 */
    UCHAR             ucReserved[10]                 ;   /* 预留 */
}PTPV2_PDELAY_REQ_MSG_S;

/* Pdelay_Resp消息格式 */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    requestReceiptTimestamp |   10      34
    |    requestingPortIdentity  |   10      44
*/
typedef struct tagPTPV2_PDELAY_RESP_MSG_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    PTPV2_TIMESTAMP_S   stRequestReceiptTimestamp      ;   /* 请求接收时间戳 */
    TCPIP_PTP_PORT_ID_S     stRequestingPortIdentity       ;   /* 请求端口 */
}PTPV2_PDELAY_RESP_MSG_S;

/* Pdelay_Resp_Follow_Up消息格式 */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    responseOriginTimestamp |   10      34
    |    requestingPortIdentity  |   10      44
*/
typedef struct tagPTPV2_PDELAY_RESP_FOLLOW_UP_MSG_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    PTPV2_TIMESTAMP_S   stResponseOriginTimestamp      ;   /* 相应源时间戳 */
    TCPIP_PTP_PORT_ID_S stRequestingPortIdentity       ;   /* 请求端口 */
}PTPV2_PDELAY_RESP_FOLLOW_UP_MSG_S;

/* Signaling消息格式 */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    targetPortIdentity      |   10      34
    |    One or more TLVs        |   M       44
*/
typedef struct tagPTPV2_SIGNALING_HEARDER_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    TCPIP_PTP_PORT_ID_S     stTargetPortIdentity           ;   /* 目标时钟端口 */
}PTPV2_SIGNALING_HEARDER_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

#pragma pack(1)
typedef struct  tagTCPIP_PTPv2_VLANTAG/* VLAN标签结构体定义 */
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    USHORT  usVlanId   :12;                           /* VLanID */
    USHORT  usCfi      :1;                            /* 0表示physical地址是经典格式，1表示physical地址不是经典格式，默认是0 */
    USHORT  usPriority :3;                            /* 报文优先级 */
#else
    USHORT  usPriority :3;                            /* 报文优先级 */
    USHORT  usCfi      :1;                            /* 0表示physical地址是经典格式，1表示physical地址不是经典格式，默认是0 */
    USHORT  usVlanId   :12;                           /* VLanID */
#endif
}TCPIP_PTPV2_VLANTAG_S;

typedef  struct  tagTCPIP_PTPV2IEEE8023VlanHead
{
    UCHAR   ucDstMacAddr[6];     /* 协议多播MAC: 01-1B-19-00-00-00 */
    UCHAR   ucSrcMacAddr[6];     /* 源MAC                          */
    USHORT  usTPID;                                 /* 802.1q Protype 8100            */
    TCPIP_PTPV2_VLANTAG_S stVlanTag;                        /* Vlan标签                       */
    USHORT  usPTPType;                              /* PTP协议类型0x88F7              */
}TCPIP_PTPV2_IEEE8023VLAN_HEAD_S;

/* 不带VLAN的PTP Heard */
typedef struct tagTCPIP_PTPV2IEEE8023Head
{
    UCHAR   ucDstMacAddr[PTPV2_MACADDRLEN];     /* 协议多播MAC: 01-1B-19-00-00-00 */
    UCHAR   ucSrcMacAddr[PTPV2_MACADDRLEN];     /* 源MAC                            */
    USHORT   usPTPType;                             /* PTP协议类型0x88F7               */
}TCPIP_PTPV2_IEEE8023_HEAD_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

typedef struct tagPTPV2_PORT_ANN_INFO
{
    USHORT usSndAnnSequenceId;
    CHAR   clogAnnounceInterval;        /*Announce发送间隔*/
    UCHAR  ucAnnRcvTimeoutNum;
}PTPV2_PORT_ANN_INFO_S;

/*Local端口信息*/
typedef struct tagPTPV2_PORT_SUB_INFO
{
    PTPV2_PORT_ANN_INFO_S  stPortAnnInfo;    
    ULONG  ulAnnSndTimerId;                 /*发送定时器,每个端口的发送周期可配置，不一定相同*/
    UCHAR  ucWorkState;                     /*由启动和停止*/
    UCHAR  ucPtpPortRole;                   /*端口角色, PTPV2_MASTER 、PTPV2_SLAVE, PTPV2_PASSIVE*/
    USHORT usPortNo;                        /*port 端口号*/
    UCHAR  ucDelayMechanism;                /*E2E P2P  none*/
    UCHAR  ucCastMode;                      /*单播、多播模式，目前仅支持L2组播*/
    UCHAR  ucPtpPortFsmState;               /*端口状态, AR-IP-PTP.002*/
    UCHAR  ucPpiRoleFlag;                   /*下发端口角色*/
    UCHAR  ucPading[8];                    /*预留 */
}PTPV2_PORT_SUB_INFO_S;

typedef struct tagPTPV2_PORT_S
{
    ULONG ulIfIndex;                        /*接口索引*/
    ULONG ulPtpPortAllocIndex;              /*PTP 端口分配索引，对应g_pstPortManageInfo->ulPortInfoHandle*/
    TCPIP_PTP_PORT_ADDR_S stPtpPortAddr;    /*地址*/
    DLL_S  dllForeignMasterHead;            /*备用master 链表*/
    TCPIP_PTP_PKT_STAT_S stPacketStat;      /* 报文统计信息 */
    AVL3_TREE_S stSlavetreeRoot;            /*slave 树，暂时预留*/
    PTPV2_PORT_SUB_INFO_S *pstSubPortInfo;  /*OC 下共享同一个结构，BC 每个端口一个*/
    ULONG (*pfPtpStartFunc)(VOID *pThis, VOID *pData); /*启动PTP 功能*/
    ULONG (*pfPtpStopFunc)(VOID *pThis, VOID *pData);  /*关闭PTP 功能*/ 
    ULONG (*pfPtpBuildAnnPktFunc)(VOID *pThis, VOID **ppData);
    ULONG (*pfPtpSndAnnPktFunc)(VOID *pThis, VOID *pData, VOID *pAddr);
    AVL3_NODE_S stPtpPortNode;             /* AVL Node */
} PTPV2_PORT_S;

/*  PTP 全局信息的获取命令字类型*/
#define   PTPV2_CMD_BMC_POLICY          0x0000001
#define   PTPV2_CMD_MASTER_NUM_LIMIT    0x0000002
#define   PTPV2_CMD_CURRENT_MASTER_NUMS 0x0000004
#define   PTPV2_CMD_PORT_FSM_MODE       0x0000005

typedef struct tagPTPV2_FOREIGN_MASTER_S
{
    DLL_NODE_S      stPortDllNode;                      /* 用于端口结点的存储*/
    DLL_NODE_S      stGlobalDllNode;                    /* 用于全局结点的存储*/
    PTPV2_PORT_S   *pstPortInfo;
    TCPIP_PTP_PORT_ID_S szForeignMasterPortId;
    UCHAR           ucGrandmasterPriority1;             /*时钟优先级1*/
    UCHAR           ucGrandmasterPriority2;             /*时钟优先级2*/
    UCHAR           ucFlagField[2];                     /* flagfield域,选源出来之后更新时间属性数据集需要 */
    UCHAR           ucTimeSource;                       /* 时钟源,更新时间属性数据集的时候需要 */
    CHAR            cLogMAnnInterval;                   /* Ann的发送间隔，由Ann报文学到，多播下使用，
                                                       单播下是通过单播协商获取，放在单播Master列表中*/
    SHORT           sCurrentUtcOffset;                  /* 当前UTC偏移 */
    TCPIP_PTP_PORT_ADDR_S   stForeignMasterPortAddr;     /*PTP_PORT_ADDR_S时钟源地址*/
    ULONG           ulVrfIndex;

    /*以下是该ForeignMaster的GrandMaster的属性，例如时钟质量、优先级等，这些属性
      本质就是grand的，foreign是没有的，故选源时也应该参考它*/
    TCPIP_PTP_CLOCK_ID_SZ   szGrandMasterId;            /*该字段对于目前的一级场景，就是Fore的Clock ID*/
    TCPIP_PTP_CLOCK_QA_S    stGrandmasterClockQuality;  /*时钟质量，包括时钟精度、时钟稳定度*/
    ULONG           ulRcvIfIndex;                       /*Master所在的接口索引 ，如果和端口的索引不一致，则丢弃*/
    ULONG           ulAnnRcvTimerId;                    /*接收定时器*/
    ULONG           ulAnnRcvTimerCount;                 /*接收ann 报文定时器的统计*/
    USHORT          usRcvAnnSequenceId;                 /*master announce 序列号 主机顺序*/
    USHORT          usStepsRemoved;                     /*网络序*/

    /*Add by heyijun 00218462 for AR-IP-PTP.001 支持PTSF配置参与选源, 2014-11 */
    ULONG            ulPtsfSync;                        /*Sync PTSF*/
    ULONG            ulPtsfUnused;                      /*当前未使用*/
    ULONG            ulRecvAnnCount;                    /*接收到的ann报文统计,少于2个则不能参与选源*/
}PTPV2_FOREIGN_MASTER_S;

typedef struct tagPTPV2_PORT_MANAGE
{
    ULONG ulCrtPortCount;   /*当前的ptp号总数*/
    ULONG ulPortInfoHandle[PTPV2_MAX_PORTNO + 1];
}PTPV2_PORT_MANAGE_S;

typedef struct tagPTPv2_Global_INFO
{
    TCPIP_PTP_CLOCK_ID_SZ   szClockId;
    TCPIP_PTP_DEFAULT_DS_S  stCfgDefaultDs;     /*用户配置值*/
    TCPIP_PTP_PARENT_DS_S   stParentDs;         /*最近一次选中的源的信息*/

    ULONG       ulMaxMasterNum;             /*最大master 个数，8个*/
    UCHAR       ucBMCPolicy;                /*选源策略，目前仅支持1588选源*/
    UCHAR       ucReserved[3];

    /*master使用*/
    USHORT      usSndPortMaxNum;            /*OC master的端口发送个数*/
    BOOL_T      bPtpTimescale;
    BOOL_T      bTimeTraceable;
    BOOL_T      bFrequencyTraceable;
    USHORT      usStepsRemoved;             /*本端为0*/
    USHORT      usWarningRecord;            /*告警记录*/
    UCHAR       ucTimeSource;

    UCHAR       ucPad[31];
}PTPV2_GLOBAL_INFO_S;


/*PTP任务的消息类型*/
typedef enum tagPTPV2_TMSG_TYPE_E
{
    PTPV2_TMSG_ANN_REQ,                /*  0 发起ANN协商请求消息类型 */
    PTPV2_TMSG_SYNC_REQ,               /*  1 发起SYNC协商请求消息类型 */
    PTPV2_TMSG_ANN_CANCEL,             /*  2 发起ANN协商取消消息类型 */
    PTPV2_TMSG_ANN_CANCELED,           /*  3 ANN单播协商已取消 */
    PTPV2_TMSG_DELAY_RESP_SYNC_CANCEL, /*  4 发起delay resp/pdelay resp 和sync协商取消报文消息类型 */
    PTPV2_TMSG_DELAY_RESP_REQ,         /*  5 多播收到ann的时候启动这个请求 */
    PTPV2_TMSG_ACCEPT_MASTER_DEL,      /*  6 删除可接受master表中的节点 */
    PTPV2_TMSG_FSM_INIT,               /*  7 初始化PTP状态机消息类型 */
    PTPV2_TMSG_FSM_DISABLE,            /*  8 去使能PTP状态机消息类型 */
    PTPV2_TMSG_FSM_ENABLE,             /*  9 使能PTP状态机消息类型 */
    PTPV2_TMSG_FSM_LOCKED,             /* 10 给PTP状态机输送LOCKED事件消息类型 */
    PTPV2_TMSG_FSM_STATE_DECISION,     /* 11 改变手动选源自动选源的时候可能触发此事件 */
    PTPV2_TMSG_ACCEPT_MASTER_ENABLE,   /* 12 使能可接受Master列表 */
    PTPV2_TMSG_ACCEPT_MASTER_DISABLE,  /* 13 去使能可接受Master列表 */
}PTPV2_TMSG_TYPE_E;

typedef enum tagPTPV2_CONTROLFIELD_E
{
    PTPV2_CONTROLFIELD_SYNC      = 0x00,
    PTPV2_CONTROLFIELD_DELAY_REQ,
    PTPV2_CONTROLFIELD_FOLLOW_UP,
    PTPV2_CONTROLFIELD_DELAY_RESP,
    PTPV2_CONTROLFIELD_MANAGEMENT,
    PTPV2_CONTROLFIELD_ALL_OTHER,
    PTPV2_CONTROLFIELD_RESERVED
}PTPV2_CONTROLFIELD_E;

/*端口状态机状态定义, AR-IP-PTP.002*/
typedef enum tagTCPIP_PTP_FSM_STATE_E
{
    PTPV2_PORT_FSM_INITIALIZING=1,  /*1  INITIALIZING状态       */
    PTPV2_PORT_FSM_FAULTY,          /*2  FAULTY状态,未实现      */
    PTPV2_PORT_FSM_DISABLED,        /*3  DISABLED状态,未实现    */
    PTPV2_PORT_FSM_LISTENING,       /*4  LISTENING状态          */
    PTPV2_PORT_FSM_PRE_MASTER,      /*5  PRE_MASTER状态,未实现  */
    PTPV2_PORT_FSM_MASTER,          /*6  MASTER状态             */
    PTPV2_PORT_FSM_PASSIVE,         /*7  PASSIVE状态            */
    PTPV2_PORT_FSM_UNCALIBRATED,    /*8  UNCALIBRATED状态,未实现*/
    PTPV2_PORT_FSM_SLAVE,           /*9  SLAVE状态              */
    PTPV2_PORT_FSM_END              /*   枚举结束               */
}TCPIP_PTP_FSM_STATE_E;

#define PTPV2_PPI_SLAVE_FLAG     0x1   /*PPI下发 SLAVE角色标志  */
#define PTPV2_PPI_PASSIVE_FLAG   0x2   /*PPI下发 PASSIVE角色标志*/

#ifdef __cplusplus
}
#endif   /* end of __cplusplus */

#endif   /* end of _PTPV2_TYPE_h_ */


