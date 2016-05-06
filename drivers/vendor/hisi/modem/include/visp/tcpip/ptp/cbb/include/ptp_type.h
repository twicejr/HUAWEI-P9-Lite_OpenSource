/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_type.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP PKT
*  Date Created: 2008-06-02
*        Author: lishenchuan
*   Description: PTP PKT模块函数头文件声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-06-02      Lishenchuan       Create
*
*******************************************************************************/
#ifndef __ptp__type__h__
#define __ptp__type__h__

#ifdef __cplusplus
extern "C" {
#endif

/* controlField 枚举值 */
typedef enum tagPTP_CONTROLFIELD_E
{
    PTP_CONTROLFIELD_SYNC      = 0x00,
    PTP_CONTROLFIELD_DELAY_REQ,
    PTP_CONTROLFIELD_FOLLOW_UP,
    PTP_CONTROLFIELD_DELAY_RESP,
    PTP_CONTROLFIELD_MANAGEMENT,
    PTP_CONTROLFIELD_ALL_OTHER,
    PTP_CONTROLFIELD_RESERVED
}PTP_CONTROLFIELD_E;

/* 错误日志等级枚举定义 */
typedef enum tagPTP_FAULT_LOG_E
{
    PTP_FAULT_EMERGENCY = 0X00,     /* 紧急级错误日志 */
    PTP_FAULT_ALERT,                /* alert级错误日志 */
    PTP_FAULT_CRITICAL,             /* critical级错误日志 */
    PTP_FAULT_ERROR,                /* error级错误日志 */
    PTP_FAULT_WARNING,              /* warning级错误日志 */
    PTP_FAULT_NOTICE,               /* notice级错误日志 */
    PTP_FAULT_INFORMATION,          /* information级错误日志 */
    PTP_FAULT_DEBUG                 /* debug级错误日志 */
}PTP_FAULT_LOG_E;

/*状态机状态定义*/
typedef enum tagPTP_FSM_STATE_E
{
    PTP_FSM_STATE_INITIALIZING=1,  /*1  INITIALIZING状态*/
    PTP_FSM_STATE_FAULTY,          /*2  FAULTY状态*/
    PTP_FSM_STATE_DISABLED,        /*3  DISABLED状态*/
    PTP_FSM_STATE_LISTENING,       /*4  LISTENING状态*/
    PTP_FSM_STATE_PRE_MASTER,      /*5  PRE_MASTER状态*/
    PTP_FSM_STATE_MASTER,          /*6  MASTER状态*/
    PTP_FSM_STATE_PASSIVE,         /*7  PASSIVE状态*/
    PTP_FSM_STATE_UNCALIBRATED,    /*8  UNCALIBRATED状态*/
    PTP_FSM_STATE_SLAVE,           /*9  SLAVE状态*/
    PTP_FSM_STATE_END              /*   枚举结束*/
}PTP_FSM_STATE_E;

/*状态机事件定义*/
typedef enum tagPTP_FSM_EVENT_E
{
    PTP_FSM_EVENT_POWERUP = 1,                              /*1,POWERUP事件*/
    PTP_FSM_EVENT_INITIALIZE,                               /*2,INITIALIZE事件*/
    PTP_FSM_EVENT_DESIGNATED_ENABLED,                       /*3,DESIGNATED_ENABLED事件*/
    PTP_FSM_EVENT_DESIGNATED_DISABLED,                      /*4,DESIGNATED_DISABLED事件*/
    PTP_FSM_EVENT_FAULT_CLEARED,                            /*5,FAULT_CLEARED事件*/
    PTP_FSM_EVENT_FAULT_DETECTED,                           /*6,FAULT_DETECTED事件*/
    PTP_FSM_EVENT_STATE_DECISION,                           /*7,STATE_DECISION事件*/
    PTP_FSM_EVENT_RECOMD_STATE_BMC_PASSIVE,                 /*8,Recommended State == BMC_PASSIVE事件*/
    PTP_FSM_EVENT_RECOMD_STATE_BMC_SLAVE,                   /*9,Recommended State == BMC_SLAVE事件*/
    PTP_FSM_EVENT_RECOMD_STATE_BMC_MASTER,                  /*10,Recommended State == BMC_MASTER事件*/
    PTP_FSM_EVENT_RECOMD_STATE_BMC_MASTER_STATE_NOT_MASTER, /*11,Recommended State==BMC_MASTER AND state!=MASTER事件*/
    PTP_FSM_EVENT_RECOMD_STATE_BMC_SLAVE_NEW_NOT_OLD,       /*12,Recommended State==BMC_SLAVE && new_master != old_master事件*/
    PTP_FSM_EVENT_RECOMD_STATE_BMC_SLAVE_NEW_IS_OLD,        /*13,Recommended State==BMC_SLAVE && new_master == old_master事件*/
    PTP_FSM_EVENT_QUALIFICATION_TIMEOUT_EXPIRES,            /*14,QUALIFICATION_TIMEOUT_EXPIRES事件*/
    PTP_FSM_EVENT_ANNOUNCE_RECEIPT_TIMEOUT_EXPIRES,         /*15,ANNOUNCE_RECEIPT_TIMEOUT_EXPIRES事件*/
    PTP_FSM_EVENT_SYNCHRONIZATION_FAULT,                    /*16,SYNCHRONIZATION_FAULT事件*/
    PTP_FSM_EVENT_MASTER_CLOCK_SELECTED,                    /*17,MASTER_CLOCK_SELECTED事件*/
    PTP_FSM_EVENT_LOCKED,                                   /*18 无线定制的Master-only状态机LOCKED事件*/
    PTP_FSM_EVENT_END                                       /*   枚举结束*/
}PTP_FSM_EVENT_E;

/*状态机选源后推荐状态宏定义,供选源算法返回使用*/
typedef enum tagPTP_RECOMD_STATE_E
{
    PTP_RECOMD_STATE_BMC_SLAVE = 1,
    PTP_RECOMD_STATE_BMC_MASTER,
    PTP_RECOMD_STATE_BMC_PASSIVE
}PTP_RECOMD_STATE_E;

/* TLV类型 */
typedef enum tagPTP_TLV_TYPE_E
{
    PTP_TLV_NULL         =    0,   /* 暂时不用 */

    /* Standard TLVs */
    PTP_MANAGEMENT,
    PTP_MANAGEMENT_ERROR_STATUS,
    PTP_ORGANIZATION_EXTENSION,

    /* Optional unicast message negotiation TLVs */
    PTP_REQUEST_UNICAST_TRANSMISSION,
    PTP_GRANT_UNICAST_TRANSMISSION,
    PTP_CANCEL_UNICAST_TRANSMISSION,
    PTP_ACKNOWLEDGE_CANCEL_UNICAST_TRANSMISSION,

    /* Optional path trace mechanism TLV */
    PTP_PATH_TRACE,

    /* Optional alternate timescale TLV */
    PTP_ALTERNATE_TIME_OFFSET_INDICATOR,

    /* 000A - 1FFF,Reserved for standard TLVs */

    /* Security TLVs ,Annex K */
    PTP_AUTHENTICATION      =    0x2000,
    PTP_AUTHENTICATION_CHALLENGE,
    PTP_SECURITY_ASSOCIATION_UPDATE,

    /* Cumulative frequency scale_factor offset */
    PTP_CUM_FREQ_SCALE_FACTOR_OFFSET,

    /*
      2004 - 3FFF,Reserved for Experimental TLVs
      4000 - FFFF,Reserved
    */
    PTP_TLV_MAX

}PTP_TLV_TYPE_E;

/* 日志ID建议从0xc000开始*/
/* 定义扩展TLV 枚举值 organizationSubType,根据<1588v2系统slave-master网元接口说明书.doc>定义 */
typedef enum tagPTP_ORG_SUB_TYPE_E
{
    PTP_ORG_SUB_TYPE_NULL,
    PTP_ORG_SUB_TYPE_REQ,
    PTP_ORG_SUB_TYPE_GRANT,
    PTP_ORG_SUB_TYPE_MAX
}PTP_ORG_SUB_TYPE_E;

/* 网元类型,根据<1588v2系统slave-master网元接口说明书.doc>定义 */
typedef enum tagPTP_ORG_ELEMENT_TYPE_E
{
    PTP_ORG_ELEMENT_CLKSERVER,
    PTP_ORG_ELEMENT_AP,
    PTP_ORG_ELEMENT_NodeB,
    PTP_ORG_ELEMENT_TYPE_MAX
}PTP_ORG_ELEMENT_TYPE_E;

/* 时间戳定义 */
#pragma pack(1)
typedef struct tagPTP_TIMESTAMP_S
{
    USHORT  usSecondsHigh;
    ULONG   ulSecondsLow;
    ULONG   ulNanoseconds;
}PTP_TIMESTAMP_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

typedef struct tagPTP_TLV_S
{
    USHORT  usTlvType;
    SHORT   sLengthField;
}PTP_TLV_S;

typedef struct tagPTP_PTP_TXT_S
{
    UCHAR   ucLengthField;
    CHAR    szReserved[3];
    CHAR    szTextField[PTP_TXT_SUPPORT_LEN];
}PTP_PTP_TXT_S;

typedef struct tagPTP_FAULTRECORD_S
{
    USHORT          usFaultRecordLength;
    UCHAR           ucSeverityCode;
    CHAR            szReserved[3];
    PTP_TIMESTAMP_S stFaultTime;
    PTP_PTP_TXT_S   stFaultName;
    PTP_PTP_TXT_S   stFaultValue;
    PTP_PTP_TXT_S   stFaultDescription;
}PTP_FAULTRECORD_S;

typedef struct tagPTP_FOREIGN_MASTER_S
{
    BOOL_T          bValid;                     /*表示该项是否为有效项*/
    PTP_PORT_ID_S   stForeignMasterPortId;
    USHORT          usForeignMasterAnnMsgs;     /*指定时间间隔内从foreign
                                                master接收到的annouce消息的数量*/
    UCHAR           ucGrandmasterPriority1;     /*时钟优先级1*/
    UCHAR           ucGrandmasterPriority2;     /*时钟优先级2*/
    UCHAR           ucFlagField[2];             /* flagfield域,选源出来之后更新时间属性数据集需要 */
    UCHAR           ucTimeSource;               /* 时钟源,更新时间属性数据集的时候需要 */
    CHAR            cLogMAnnInterval;            /* Ann的发送间隔，由Ann报文学到，多播下使用，
                                                   单播下是通过单播协商获取，放在单播Master列表中*/
    /*Add By t00110672 For BC3D02987,IEEE1588V2 支持UTC时间实现方案*/
    SHORT sCurrentUtcOffset; /* 当前UTC偏移 */
    /*Add by dutianyi 2014-7-24 支持G8275.1标准选源*/
    USHORT usStepsRemoved;   
    /*End of adding by dutianyi*/

    /*该字段是我们实现时添加，因为现在实现多是采用PORT ADDR进行标识*/
    PTP_PORT_ADDR_S  stForeignMasterPortAddr;   /*PTP_PORT_ADDR_S时钟源地址*/

    ULONG           ulVrfIndex; 
    
    /*以下是该ForeignMaster的GrandMaster的属性，例如时钟质量、优先级等，这些属性
      本质就是grand的，foreign是没有的，故选源时也应该参考它*/

    PTP_CLOCK_ID_SZ szGrandMasterId;            /*该字段对于目前的一级场景，就是Fore的Clock ID*/
    PTP_CLOCK_QA_S  stGrandmasterClockQuality;  /*时钟质量，包括时钟精度、时钟稳定度*/
    ULONG           ulIfIndex;                    /*Master所在的接口索引*//*qinyun&luogaowei 0地址方案 2011-12-12*/
    /*Added by zhangliangzhi00187023, PTP 5路选源模式，协商成功后，duration到期重协商成功后，没有发生源切换的情况下，无ppi下发 , 2012/1/13   问题单号:DTS2012010902147 */
    /*存放老的ppi参数*/
    PTP_PPI_S stPtpPpi;
    /* End of Added by zhangliangzhi00187023, 2012/1/13   问题单号:DTS2012010902147 */

    ULONG ulMulRcvAnnPackets;                      /* OverMac,多播统计 */
    ULONG ulMulAnnSequenceError;                   /* OverMac,多播统计 */

    /*Added by heyijun 00218462 for AR-IP-PTP.001 支持PTSF配置参与选源 */
    ULONG  ulPtsfLossSync;      /* 组播链路Sync PTSF */
    
}PTP_FOREIGN_MASTER_S;

typedef struct tagPTP_FOREIGN_MASTER_TAB_S
{
    USHORT                usActualTabSize; /*表项实际有效元素大小*/
    USHORT                usReserved;
    ULONG                 ulSelectMasterMode; /*选源模式*/

    PTP_PORT_ADDR_S       stManualMasterAddr; /*手动选源模式下的Master的PORT ADDR*/
    ULONG                 ulManualVrfIndex;   /* 手动选源VRF index */

    PTP_FOREIGN_MASTER_S *pstBmcParent;   /*当前BMC选出的Parent，是Fore Master表中的元素*/
    PTP_FOREIGN_MASTER_S  stForeignMaster[PTP_UNICAST_MASTR_LEN];
}PTP_FOREIGN_MASTER_TAB_S;


/*单播SLAVE及其列表，无线规格支持10000个，双十字链表，会后咨询梁继成*/
typedef struct tagPTP_UNI_SLAVE_NODE_S
{
    struct tagPTP_UNI_SLAVE_NODE_S *pstPrev;
    struct tagPTP_UNI_SLAVE_NODE_S *pstNext;


    /* 协商状态标记 */
    UCHAR           ucAnnFlag;
    UCHAR           ucSyncFlag;
    UCHAR           ucDelayFlag;       /* pdelay 和 delay 公用 */
    UCHAR           ucReserved;

    /*消息的sequence id*/
    USHORT            usSndAnnSequenceId;    /* Announce消息的sequence id */
    USHORT            usSndSigSequenceId;    /* signaling消息的sequence id */
    USHORT            usRcvSigSequenceId;    /* 接收到的signaling消息sequence id */
    USHORT            usReserved1;

    ULONG ulReserved1[3];/*删除了原来的3个字段，用于保留*/

    CHAR cLogAnnInterval;/*Ann报文发送间隔*/
    CHAR cLogSyncInterval;/*Sync报文发送间隔*/
    CHAR cDelayReqInterval;/*DelayReq报文发送间隔*/
    UCHAR ucReserved2;

    ULONG ulAnnDurationField;/*Ann报文发送时长*/
    ULONG ulSyncDurationField;/*SYNC报文发送时长*/
    ULONG ulDelayReqDurationField;/*Delay Req报文发送时长*/
    /*End*/

    /*对应keep alive 报文接收定时器*/
    ULONG ulLiveRcvTimerId;
    ULONG ulLiveCounter;

    /* 对应Quality timer out 定时器Id */
    ULONG ulQualityTimerId;
    ULONG ulDelayDurationTimerId; /*LGW_QY delay duration定时器*/

    /* 对应Annouce Request Cancel timer out 定时器Id */
    ULONG ulAnnCancelQueryTimerId;
    ULONG ulAnnCancelCounter;

    /* 对应Sync Request Cancel timer out 定时器Id */
    ULONG ulSyncCancelQueryTimerId;
    ULONG ulSyncCancelCounter;

    /* 对应Delay Request Cancel timer out 定时器Id */
    ULONG ulDelayCancelQueryTimerId;
    ULONG ulDelayCancelCounter;

    /* 协商状态标记 */
    PTP_PORT_ADDR_S stSlaveAddr;       /*Slave的地址*/
    PTP_PORT_ADDR_S stExtSlaveAddr;

    PTP_PORT_ID_S   stSlaveId;         /* slave Id */

    /*Begin 【同步VISPV1R7C03问题单BC3D01665】
        BC3D01734【PTP】实现AP产品提出的1588穿透NAT对VISP的需求 l00147446 09-07-13*/
    USHORT usExtUdpPort;
    /*End*/

    /* 统计信息 */
    PTP_PACKET_STAT_S stPacketStat;
    struct tagPTP_PORT_S          *pstPtpPort;
    struct tagPTP_UNI_SLAVE_TBL_S *pstPtpUniSlaveTbl;

    ULONG ulNextAnnLow;
    ULONG ulNextAnnHigh;
    ULONG ulDurationLow;
    ULONG ulDurationHigh;

    /*Added by limin00188004, Master为新模式，向slave发起reqcancel ann时，漏发delay cancel报文, 2012/2/1   问题单号:DTS2012012000431 */
    /* slave侧用stPtpPort.ucDelayMechanism; master侧应使用PTP_UNI_SLAVE_NODE_S.ucDelayMechanism */
    UCHAR ucDelayMechanism;  /* slave节点的DELAY_MECHANISM */
    UCHAR ucReserved3[3];    /* 预留 */ 
    /* End of Added by limin00188004, 2012/2/1   问题单号:DTS2012012000431 */
}PTP_UNI_SLAVE_NODE_S;

typedef struct tagPTP_UNI_SLAVE_TBL_S
{
    struct tagPTP_UNI_SLAVE_TBL_S *pstNextUniSlaveTbl;     /* 下一个UniSlaveTbl节点,NULL表示无下一个UniSlaveTbl节点 */
    PTP_PORT_ADDR_S stMasterIPAddr; /* master端地址 */
    USHORT  usActualTabSize;
    USHORT  usReserved;
    PTP_UNI_SLAVE_NODE_S *pstUnitcastSlave;
}PTP_UNI_SLAVE_TBL_S;


/*TC 端口数据集定义*/
typedef struct tagPTP_TC_PORT_DS
{
    BOOL_T              bValid;
    BOOL_T              bFaultyFlag;
    CHAR                cLogMinPdelayReqInterval;
    CHAR                cReserved;
    PTP_PORT_ID_S       stPortId;
    PTP_TIME_INTERVAL_S stPeerMeanPathDelay;/*初始值为0*/
    ULONG               ulPhyPortNo  ;           /* 杨洋添加 */
}PTP_TC_PORT_DS_S;

/*TC时钟数据结构定义*/
typedef struct tagPTP_TCLOCK_S
{
    /*默认数据集*/
    PTP_CLOCK_ID_SZ szClockId;
    USHORT          usNumberPorts;
    UCHAR           ucDelayMechanism;
    UCHAR           ucPrimaryDomain;
    PTP_TC_PORT_DS_S stTcPortDS[PTP_SUPPORT_PORT_NUMBER];
}PTP_TCLOCK_S;


/*定义时钟端口的描述信息的数据结构*/
/*
Array index (hex)Description
0 he node implements an ordinary clock
1 he node implements a boundary clock
2 he node implements a peer-to-peer transparent clock
3 he node implements an end-to-end transparent clock
4 he node implements a management node
5 - F  Reserved
*/

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
typedef struct tagPTP_MSGHEADER_S
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
    PTP_PORT_ID_S    stSourcePortIdentity           ;   /* 时钟ID */
    USHORT           usSequenceId                   ;   /* 序列号 */
    UCHAR            ucControlField                 ;   /* 控制域 */
    CHAR             cLogMessageInterval            ;   /* 消息间隔，由消息类型决定 */
}PTP_MSGHEADER_S;

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
typedef struct tagPTP_ANNOUNCE_MSG_S
{
    PTP_MSGHEADER_S   stMsgHeader                    ;   /* 消息头 */
    PTP_TIMESTAMP_S   stOriginTimestamp              ;   /* 源时间戳 */
    SHORT             sCurrentUtcOffset              ;   /* 当前UTC偏移 */
    UCHAR             ucreserved                     ;   /* 预留 */
    UCHAR             ucGrandmasterPriority1         ;   /* 优先级1 */
    PTP_CLOCK_QA_S    stGrandmasterClockQuality      ;   /* 时钟质量 */
    UCHAR             ucGrandmasterPriority2         ;   /* 优先级2 */
    PTP_CLOCK_ID_SZ   stGrandmasterIdentity          ;   /* master时钟id */
    USHORT            usStepsRemoved                 ;   /*  */
    UCHAR             ucTimeSource                   ;   /* 时钟源 */
}PTP_ANNOUNCE_MSG_S;

/* Sync 和 Delay_Req消息格式 */
/*
  Bits                             Octets  Offset
  7   6   5   4   3   2   1   0
  |    header (see 13.3)      |    34      0
  |    originTimestamp        |    10      34
*/
typedef struct tagPTP_SYNC_MSG_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    PTP_TIMESTAMP_S   stOriginTimestamp              ;   /* 源时间戳 */
}PTP_SYNC_MSG_S;

typedef struct tagPTP_DELAY_REQ_MSG_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    PTP_TIMESTAMP_S   stOriginTimestamp              ;   /* 源时间戳 */
}PTP_DELAY_REQ_MSG_S;

/* Delay_Resp消息格式 */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    receiveTimestamp        |   10      34
    |    requestingPortIdentity  |   10      44
*/
typedef struct tagPTP_DELAY_RESP_MSG_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    PTP_TIMESTAMP_S   stReceiveTimestamp             ;   /* 接收时间戳 */
    PTP_PORT_ID_S     stRequestingPortIdentity       ;   /* 请求端口 */
}PTP_DELAY_RESP_MSG_S;

/* Pdelay_Req消息格式 */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    originTimestamp         |   10      34
    |    reserved                |   10      44
*/
typedef struct tagPTP_PDELAY_REQ_MSG_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    PTP_TIMESTAMP_S   stOriginTimestamp              ;   /* 源时间戳 */
    UCHAR             ucReserved[10]                 ;   /* 预留 */
}PTP_PDELAY_REQ_MSG_S;


/* Pdelay_Resp消息格式 */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    requestReceiptTimestamp |   10      34
    |    requestingPortIdentity  |   10      44
*/
typedef struct tagPTP_PDELAY_RESP_MSG_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    PTP_TIMESTAMP_S   stRequestReceiptTimestamp      ;   /* 请求接收时间戳 */
    PTP_PORT_ID_S     stRequestingPortIdentity       ;   /* 请求端口 */
}PTP_PDELAY_RESP_MSG_S;


/* Pdelay_Resp_Follow_Up消息格式 */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    responseOriginTimestamp |   10      34
    |    requestingPortIdentity  |   10      44
*/
typedef struct tagPTP_PDELAY_RESP_FOLLOW_UP_MSG_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    PTP_TIMESTAMP_S   stResponseOriginTimestamp      ;   /* 相应源时间戳 */
    PTP_PORT_ID_S     stRequestingPortIdentity       ;   /* 请求端口 */
}PTP_PDELAY_RESP_FOLLOW_UP_MSG_S;


/* Signaling消息格式 */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    targetPortIdentity      |   10      34
    |    One or more TLVs        |   M       44
*/
typedef struct tagPTP_SIGNALING_HEARDER_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* 消息头 */
    PTP_PORT_ID_S     stTargetPortIdentity           ;   /* 目标时钟端口 */

}PTP_SIGNALING_HEARDER_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* REQUEST_UNICAST_TRANSMISSION TLV 格式 */
/*
  Bits                                 Octets    TLV offset
  |  7   6   5   4   3   2   1   0 |
  |          tlvType               |     2        0
  |          lengthField           |     2        2
  | messageType   | Reserved       |     1        4
  |   logInterMessagePeriod        |     1        5
  |        durationField           |     4        6
*/

#pragma pack(1)
/* TLV Header */
typedef struct tagPTP_TLVHEADER_S
{
    USHORT        usType;                 /* 类型 */
    USHORT        usLength;               /* 长度 */
}PTP_TLVHEADER_S;

/*单播请求TLV结构定义*/
typedef struct tagPTP_REQUEST_UNICAST_TLV_S
{
    USHORT usTlvType;
    USHORT usLengthField;
#if (VRP_BIG_ENDIAN == VRP_YES)
    UCHAR  ucMessageType:4;
    UCHAR  ucReserved:4;
#else
    UCHAR  ucReserved:4;
    UCHAR  ucMessageType:4;
#endif
    CHAR   cLogInterMessagePeriod;
    ULONG  ulDurationField;
}PTP_REQUEST_UNICAST_TLV_S;

/* GRANT_UNICAST_TRANSMISSION */
/*
  Bits                                Octets    TLV offset
  |  7   6   5   4   3   2   1   0 |
  |          tlvType               |     2        0
  |          lengthField           |     2        2
  | messageType   | Reserved       |     1        4
  |   logInterMessagePeriod        |     1        5
  |        durationField           |     4        6
  |          reserved              |     1        10
  |  0   0   0   0   0   0   0   R |     1        11
  
*/
/*定义GRANT的消息数据结构*/
typedef struct tagPTP_GRANT_TLV_S
{
    USHORT    usType ;
    USHORT    usLength;
    #if (VRP_BIG_ENDIAN == VRP_YES)
    UCHAR     ucMsgType   :  4;
    UCHAR     ucReserved1 :  4;
    #else
    UCHAR     ucReserved1 :  4;
    UCHAR     ucMsgType   :  4;
    #endif

    CHAR      cLogInterMsgPeriod;
    ULONG     ulDuration;
    CHAR      cReserved2;
     #if (VRP_BIG_ENDIAN == VRP_YES)
    UCHAR     ucReserved3 :  7;
    UCHAR     ucR         :  1;
    #else
    UCHAR     ucR         :  1;
    UCHAR     ucReserved3 :  7;
    #endif
}PTP_GRANT_TLV_S;

/* ACKNOWLEDGE_CANCEL_UNICAST_TRANSMISSION */
/*
  Bits                                Octets    TLV offset
  |  7   6   5   4   3   2   1   0 |
  |          tlvType               |     2        0
  |          lengthField           |     2        2
  |    messageType |  reserved     |     1        4
  |          reserved              |     1        5
  
*/
/*定义ACK_CANCEL的消息数据结构 -- 李神传*/
typedef struct tagPTP_ACK_CANCEL_TLV_S
{
    USHORT    usType ;
    USHORT    usLength;
    #if (VRP_BIG_ENDIAN == VRP_YES)
    UCHAR     ucMsgType   :  4;
    UCHAR     ucReserved1 :  4;
    #else
    UCHAR     ucReserved1 :  4;
    UCHAR     ucMsgType   :  4;
    #endif

    CHAR      cReserved2;
}PTP_ACK_CANCEL_TLV_S;

/* CANCEL_UNICAST_TRANSMISSION */
/*
  Bits                                Octets    TLV offset
  |  7   6   5   4   3   2   1   0 |
  |          tlvType               |     2        0
  |          lengthField           |     2        2
  |    messageType |  reserved     |     1        4
  |          reserved              |     1        5
  
*/
/*定义CANCEL的消息数据结构 -- 杨洋*/
typedef struct tagPTP_CANCEL_TLV_S
{
    USHORT    usType ;
    USHORT    usLength;
    #if (VRP_BIG_ENDIAN == VRP_YES)
    UCHAR     ucMsgType   :  4;
    UCHAR     ucReserved1 :  4;
    #else
    UCHAR     ucReserved1 :  4;
    UCHAR     ucMsgType   :  4;
    #endif
    CHAR      cReserved2;
}PTP_CANCEL_TLV_S;

/* PTP握手消息 */
/* 自定义握手消息
                Bits                               Octets  Offset
    7      6      5     4    3     2     1     0
    | transportSpecific |    messageType(0xE)  |   1       0
    |      reserved     |     versionPTP       |   1       1
    |               Random(随机数)             |   2       2
*/
typedef struct tagPTP_HANDSHAKE_REQ_S
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
    UCHAR            ucreserved                 : 4 ;   /* 预留 */
    #else
    UCHAR            ucreserved                 : 4 ;   /* 预留 */
    UCHAR            ucversionPTP               : 4 ;   /* PTP版本号，本次实现1588v2，因此版本号为2 */
    #endif
    USHORT           usRandom                       ;   /* 随机数 */
}PTP_HANDSHAKE_REQ_S;

/* PTP握手响应消息 */
/*
                Bits                           Octets  Offset
    7     6     5     4    3    2    1    0
    |transportSpecific|   messageType(0xF)|    1       0
    |     Reserved    |      versionPTP   |    1       1
    |    Random(Handshake_Req中的随机数)  |    2       2
    |     SIP(收到的Handshake_Req的源IP)  |    4       4
    |  SPort(收到的Handshake_Req的源端口) |    2       8
    |              reserved               |    2       10
*/
typedef struct tagPTP_HANDSHAKE_RESP_S
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
    UCHAR            ucreserved                 : 4 ;   /* 预留 */
    #else
    UCHAR            ucreserved                 : 4 ;   /* 预留 */
    UCHAR            ucversionPTP               : 4 ;   /* PTP版本号，本次实现1588v2，因此版本号为2 */
    #endif

    USHORT           usRandom                       ;   /* 随机数 */
    ULONG            ulSrcIP                        ;   /* 源IP */
    USHORT           usSrcPort                      ;   /* 源端口号 */
    USHORT           usReserved                     ;   /* 预留 */
}PTP_HANDSHAKE_RESP_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/*  扩展tlv是自定义的tlv，因此如果需要互通，
    需要其他设备也支持该扩展tlv，
    目前我司就无线针对该tlv互通
    Bits                            Octets  TLVOffset
    7   6   5   4   3   2   1   0
    |tlvType(0x0003)            |   2       0
    |lengthField                |   2       2
    |organizationId(由IEEE分配) |   3       4
    |organizationSubType(见后)  |   3       7
    |dataField(见后)            |   N       10

    organizationSubType取值
    类型           值
    无效           0
    ReqUnicast     1
    GrantUnicast   2
    Reserve        保留

    dataField(ReqUnicast)/GrantUnicast无dataField
    Bits                            Octets  TLVOffset
    7   6   5   4   3   2   1   0
    |    ElementType            |   1       0
    |    Reserved               |   1       1
    |    SPort(本端的端口)      |   2       2
    |    SIP(本端的地址)        |   4       4

    网元类型
    ElementType   值
    Clk Server    0
    AP            1
    NodeB         2
    Reserve       保留  ExtensionTlv
*/

#pragma pack(1)
typedef struct tagPTP_EXTENSIONTLV_ADDR_S
{

    USHORT    usType ;
    USHORT    usLength;
    UCHAR     szOrganizationId[3];          /* 组织ID,使用的时候为三个一字节的数组 */
    UCHAR     szOrganizationSubType[3];     /* 组织子类型,使用的时候为三个一字节的数组 */
    UCHAR     ucElementType;                /* 网元类型 */
    UCHAR     ucReserved;                   /* 预留 */
    USHORT    usSrcPort;                    /* 源端口 */
    ULONG     ulSrcAddr;                    /* 源地址 */
}PTP_EXTENSIONTLV_ADDR_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* Add for BC3D03003*/
typedef struct tagPTPMIPINFO
{
  ULONG ulPortIP;                                  /* 上次加入多播组的IP信息 */
  ULONG ulPortIfIndex;                             /* 上次加入多播组的接口信息 */
  ULONG ulDownLoadFlag;                            /* 下发标记 */  
}PTP_MIPINFO_S;


typedef struct tagPTP_UNI_MASTER_NODE_S
{
    /* 公共表 */
    BOOL_T              bLink;   /*链路通断标记*/
    BOOL_T              bValid;  /*节点是否有效 */

    PTP_PORT_ADDR_S     stPortAddr;
    PTP_PORT_ADDR_S     stExtPortAddr;

    BOOL_T              bNegoEnable; /* 启动单播协商标记 */

    /* 配置表 */
    BOOL_T              bCfgValid;

    /* 实际运行表 */
    BOOL_T              bRunValid;
    
    /* 协商状态标记 */
    UCHAR           ucAnnFlag;
    UCHAR           ucSyncFlag;
    UCHAR           ucDelayFlag;   /* pdelay 和 delay 公用 */

    /* 运行时的消息发送间隔, 对2取对数 */
    CHAR            cRunLogAnnInterval;
    CHAR            cRunLogSynInterval;
    CHAR            cRunLogDelayInterval;

    USHORT           usRcvAnnSequenceId;     /* 接收到的annouce sequence id */
    USHORT           usRcvSigSequenceId;     /* 接收到的signaling sequence id */
    USHORT           usSndSigSequenceId;      /* 发送的signaling sequence id(slave不会发announce,因此不用定义announce相关id) */

    USHORT           usReserved;

    ULONG           ulRunAnnDuration;
    ULONG           ulRunSynDuration;
    ULONG           ulRunDelayDuration; /* delay pdelay共用 */

    /* timer identify 定义 */
    ULONG           ulLiveSndTimerId;      /*Keep alive 报文发送定时器*/
    ULONG           ulAnnRecvTimerId;
    ULONG           ulAnnReqQueryTimerId;
    ULONG           ulAnnDurationTimerId;
    ULONG           ulSyncReqQueryTimerId;
    ULONG           ulSyncDurationTimerId;
    ULONG           ulDelayReqQueryTimerId; /* delay pdelay共用 */
    ULONG           ulDelayDurationTimerId;
    ULONG           ulAnnCancelQueryTimerId;
    ULONG           ulSyncCancelQueryTimerId;
    ULONG           ulDelayCancelQueryTimerId;/* delay pdelay共用 */

    /* 单播协商请求和取消个消息的计数器 */
    ULONG            ulAnnReqCounter;
    ULONG            ulSyncReqCounter;
    ULONG            ulDelayReqCounter;
    ULONG            ulAnnCancelCounter;
    ULONG            ulSyncCancelCounter;
    ULONG            ulDelayCancelCounter;

    /*Annouce 接收定时器的计数器*/
    ULONG            ulAnnRecvCounter;

    PTP_PACKET_STAT_S   stPacketStat; /*链路报文统计信息 */
    PTP_SLAVE_STAT_S stSlaveStat; /*Slave端关于Master的报文统计信息*/

    ULONG           ulAnnDurationOutFlag;  /* whether the duration is time out */
    /* PTSF(Packet Timing Signal Fail) of lossSync & lossResp
     * the annouce time-out mechanism can insure the lossAnnouce
     */
    ULONG            ulPtsfLossSync;
    ULONG            ulPtsfLossAnnouce;
    ULONG            ulPtsfLossUnusable;

    /* In new profile,there is a priority for local master,
     * in order to differ from the priority of 1588v2,
     * we use weight here */
    ULONG            ulWeight;          /* the lesser value has high priority,no range,default value is 0 */
    
    /* Master port Identity,set it all 1's when add the unicast master,and 
     * update the value after receiving the announce grant from the master*/
    PTP_PORT_ID_S   stMasterPortIdentity;
    UCHAR          ucSyncDurationOutFlag;     /*Sync是否处于重协商状态(收到授权时清零)*/
    UCHAR          ucHasNpAddFlag;/*已经下发Add*/
    ULONG          ulVrfIndex;

    /*Added by limin00188004/zhangliangzhi00187023/jijianhua00169178, PTP slave侧支持5路SYNC协商, 2011/12/29   问题单号:S.PTP.5SYNC.01 */
    ULONG ulUdpPort;  /* Master的UDP端口，主机序。 */
    /* End of Added by limin00188004/zhangliangzhi00187023/jijianhua00169178, 2011/12/29   问题单号:S.PTP.5SYNC.01 */

    /*Added by guo00178934, 统一调用链路Down告警, 2012/1/13   问题单号:20120112_1 */
    ULONG ulSyncWarning;    /*Sync Warning 类型(Up, Down)*/
    ULONG ulDelayWarning;   /*Delay Warning 类型(Up, Down)*/
    /* End of Added by guo00178934, 2012/1/13   问题单号:20120112_1 */

    /*Added by wuxiaowu00217009, 2012/8/9 Master中保存DSCP值，用于在Slave侧指定Master设置DSCP*/
    UCHAR ucPriority;
    UCHAR ucPad[3];
}PTP_UNI_MASTER_NODE_S;

/*协议可选的数据类型*/
typedef struct tagPTP_UNI_MASTER_TBL_S
{
    USHORT  usPtpPortNumber;
    USHORT  usCfgTableSize;       /* 当前配置的单播master列表的大小,最多支持2个 */
    USHORT  usRunTableSize;       /* 当前运行状态里单播master列表的大小,在删除单播master列表发起单播取消之后，还没收到响应情况下比配置大小大 */
    USHORT  usTotalTableSize;     /* 当前节点大小 */
    PTP_UNI_MASTER_NODE_S stUniMasterNode[PTP_UNICAST_MASTR_LEN];
}PTP_UNI_MASTER_TBL_S;      /*该结构用于unicastMasterTable*/

/******************************************************************************/
/*  Slave 侧 带VRF属性的地址(暂只保存vrf与IfIndex的关系)                      */
/******************************************************************************/
typedef struct tagPTP_PORT_ADDR_VRF_NODE_S
{
    struct tagPTP_PORT_ADDR_VRF_NODE_S *pstPrev;
    struct tagPTP_PORT_ADDR_VRF_NODE_S *pstNext;
    PTP_PORT_ADDR_S      stPtpPortAddr;
    ULONG ulVrfIndex;
    ULONG ulIfIndex;
}PTP_PORT_ADDR_VRF_NODE_S;

typedef struct tagPTP_PORT_ADDR_VRF_TBL_S
{
    ULONG ulCurNum;
    ULONG ulMaxNum;
    PTP_PORT_ADDR_VRF_NODE_S stPtpPortAddrVrfHead;
}PTP_PORT_ADDR_VRF_TBL_S;

typedef struct tagPTP_ALL_PORT_ADDR_VRF_NODE_S
{
    ULONG ulNum;
    struct tagPTP_PORT_ADDR_VRF_NODE_S szPortAddrVrf[PTP_MAX_VRF_NUM];
}PTP_ALL_PORT_ADDR_VRF_NODE_S;

typedef struct tagPTP_UNI_SLAVE_TBL_HASH
{
    PTP_UNI_SLAVE_TBL_S *pstUniSlaveTbl;   /* 指向Hash冲突链头节点的指针 */
    ULONG        ulUniSlaveNum;            /* UniSlaveTbl的Hash冲突链节点个数 */
}PTP_UNI_SLAVE_TBL_HASH_S;

/*定义OC/BC时钟端口数据结构*/
typedef struct tagPTP_PORT_S
{
    /*协议定义的时钟端口数据集合*/
    BOOL_T    bValid;                     /*该时钟端口是否有效，即用户是否创建*/
    /*静态成员*/
    PTP_PORT_ID_S stPortId;

    /*动态成员*/
    PTP_TIME_INTERVAL_S stPeerMeanPathDelay;
    UCHAR   ucPortState;
    CHAR    cLogAnnInterval;             /* 单播协商中,请求对方发送ann消息的间隔 */
    CHAR    cLogSyncInterval;            /* 同上 */
    CHAR    cLogMinDelayReqInterval;     /*Delay 和 Pdelay 共用*/
    UCHAR   ucAnnReceiptTimeout;          /* ann消息接收超时 */
    UCHAR   ucDelayMechanism;
    CHAR    versionNumber;
    /* CHAR    cReserved; */
    CHAR    cLogAnnSndTime;              /* announce报文发送时间,Master侧用到 */

    /*其他协议属性或无线定制属性*/
    ULONG   ulPhyPortNo;                /*该时钟端口对应的物理接口编号*/
    /* 各种情况 address 存储位置
        ipv4                ipv6                overmac
slave   stLocalPortAddr     stLocalPortAddr6    stLocalPortAddr
master  pstUniSlaveTbl      stUniSlaveTbl6      stLocalPortAddr
    */
    PTP_PORT_ADDR_S stLocalPortAddr[2]; /*本地端口的地址，0为标准的，1为AP IPSEC的场景 */
    PTP_PORT_ADDR_S stLocalPortAddr6[2]; /*本地端口的地址，0为标准的*/

    USHORT  usLocalUdpPort[2];          /* 本地端口的udp端口号，0为标准，暂时可以不用,因为是常规端口号(320/319)
                                           1为安全方案场景,由用户配置 */
                                            
    PTP_PORT_ADDR_VRF_TBL_S  stPtpPortAddrVrfTbl;
    /*Slave相关*/
    /*foreign Master列表*/
    PTP_FOREIGN_MASTER_TAB_S stForeignMasterTab;

    /*消息的sequence id,多播时候用，单播时候用单播master/slave列表里面的,多播不关注signaling的 sequence id */
    USHORT            usSndAnnSequenceId;    /* 发送的signaling消息的sequence id，针对master */

    /*单播相关*/
    BOOL_T bUnicastNego;                  /*单播协商标记，整体使能，不做按消息配置*/


    /*Slave相关*/
    ULONG ulAnnDuration;                /*Annouce单播发送时长，单位秒*/
    ULONG ulSyncDuration;               /*Sync单播发送时长，单位秒*/
    ULONG ulDelayRespDuration;          /*Delay_Resp单播发送时长，单位秒*/

    ULONG ulAnnSndTimerId;              /*Ann发送定时器Id*/

    /* 多播Ann接收定时器 */
    ULONG ulAnnMRecvTimerId;            /* Ann多播接收定时器Id */
    ULONG ulAnnMRecvCounter;            /* Ann多播接收定时器计数器*/

    ULONG ulAcceptMasterDetecTimerId;   /* 可接受Master检测定时器 */
    BOOL_T    bAccepMasterTabEnable;      /*可接受Master列表使能标志*/

    /* 多播下delay/pdelay resp 单播协商相关的变量 */
    CHAR  cMRunLogDelayInterval;        /* 多播运行的Delay/pdelay间隔，由协商得到 */
    UCHAR ucMDelayFlag;                 /* 多播的delay resp单播协商的FALG*/
    ULONG ulMDelayReqQueryTimerId;      /* 多播delay/pdelay resp 查询定时器 */
    ULONG ulMRunDelayDuration;          /* 多播运行的delay/pdelay duration，有协商得到 */
    /* ST专项检视:wangchengyang,2008-7-23,counter单词拼写错误 */
    ULONG ulMDelayReqCounter;           /* 多播的Delay Req 计数器 */
    ULONG ulMDelayCancelQueryTimerId;   /* 多播delay/pdelay cancel 查询定时器*/
    ULONG ulMDelayCancelCounter;        /* 多播的Delay cancel 计数器 */

    /*Master相关*/
    PTP_UNI_SLAVE_TBL_S stUniSlaveTbl6;
    PTP_PORT_ADDR_S stMultiSlaveMasterIPAddr;          /* 多播Master 地址 */
    PTP_UNI_SLAVE_TBL_HASH_S stUniSlaveTblHash[PTP_UNI_SLAVE_TBL_HASH_SIZE];

    PTP_PACKET_STAT_S stPacketStat;     /* 报文统计信息 */

    USHORT usVlanId;                    /*VLAN Id*/
    USHORT usIPv4AddrNum;
    /* ST问题:删除流发送缓存报文结构，在实现中也增加相关处理代码,wangchengyang 2008-7-18 */
    /* Add for BC3D03003*/
    PTP_MIPINFO_S stMIpInfo;            /* 下发的多播地址信息 */

    /*Added by guo00178934, Duration超时重协商时相对Duration百分比, 2012/1/7   问题单号:20120107_1 */
    ULONG ulAnnDurationPercent;                /*Annouce单播重协商超时百分比*/
    ULONG ulSyncDurationPercent;               /*Sync单播重协商超时百分比*/
    ULONG ulDelayRespDurationPercent;         /*Delay_Resp重协商超时百分比*/
    /* End of Added by guo00178934, 2012/1/7   问题单号:20120107_1 */
}PTP_PORT_S;


/******************************************************************************/
/*  VRF Node, 用于管理socket(外部输入VRF, 内部管理带VRF的socket)              */
/******************************************************************************/
typedef struct tagPTP_VRF_NODE_S
{
    struct tagPTP_VRF_NODE_S *pstPrev;
    struct tagPTP_VRF_NODE_S *pstNext;
    ULONG ulVrfIndex;
    ULONG ulCreatTaskId; /* 创建该socket的Task id */
    LONG  lSocketFd;
}PTP_VRF_NODE_S;

typedef struct tagPTP_VRF_TBL_S
{
    ULONG ulCurNum;
    ULONG ulMaxNum;
    PTP_VRF_NODE_S stVrfNodeHead;
}PTP_VRF_TBL_S;

typedef struct tagPTP_ALL_VRF_NODE_S
{
    ULONG ulNum;
    struct tagPTP_VRF_NODE_S szVrfNode[PTP_MAX_VRF_NUM];
}PTP_ALL_VRF_NODE_S;

/*时钟等级结构体，只能用于Master侧，用于存储新、老模式的时钟等级*/
typedef struct tagPTP_CLOCK_CLASS_S
{
    UCHAR   uc1588Class;            /*老模式的时钟等级*/
    UCHAR   ucG8265Class;           /*新模式的时钟等级*/
    UCHAR   ucG8275Class;           /*G8275标准的时钟等级*/
    UCHAR   szReserved;             /*填充字段*/
}PTP_CLOCK_CLASS_S;



/*定义OC/BC时钟设备数据结构*/
typedef struct tagPTP_CLOCK_S
{
    /*默认数据集*/
    /*静态成员*/
    BOOL_T            bTwoStep;   /* 默认FALSE, 没有Follow消息 */
    USHORT            usReserved;
    PTP_CLOCK_ID_SZ szClockId ;
    USHORT          usNumberPorts;
    UCHAR ucAnnReceiptTimeout;          /* ann消息接收超时 */
    /*可配置成员*/
    UCHAR       ucPriority1;            /* 范围0--255, 默认0 */
    UCHAR       ucPriority2;            /* 范围0--255, 默认0 */
    UCHAR       ucDomainNumber;         /* 范围0--255, 默认0 */
    UCHAR       ucClockFsmMode;         /* 范围 0--2 */
    UCHAR       ucSyncMode;
    UCHAR       ucCastMode;   /*系统支持网络承载模式(单播/多播/OVER MAC)*/

    /* 单播请求/取消间隔 */
    CHAR   cLogQueryInterval;   /*放这个位置是为了四字节对齐, 协议未规定取值范围,默认值为2*/

    /*当前数据集，全部是动态成员*/
    USHORT      usStepsRemoved;

    PTP_TIME_INTERVAL_S stOffsetFromMaster;
    PTP_TIME_INTERVAL_S stMeanPathDelay;

    /*动态成员*/
    PTP_CLOCK_QA_S stClockQuality;

    /*Added by wuxiaowu217009, 动态成员，只能用于Master侧，支持同时配置新、老模式ClockClass, 2012/9/18   
     *问题单号:S.PTP.02.01 */
    PTP_CLOCK_CLASS_S stMasterCfgClockClass;
    ULONG       ulMasterCfgClockClassFlag;    /*判断是否使能同时配置新、老模式ClockClass，1:使能、0:未使能*/
    /* End of Added by wuxiaowu217009, 2012/9/18   问题单号:S.PTP.02.01 */


    /*父亲数据集，全部是动态成员*/
    PTP_PORT_ID_S   stParentPortId;
    BOOL_T            bParentStats;
    UCHAR           ucGrandmasterPriority1;
    UCHAR           ucGrandmasterPriority2;
    USHORT          usObservedParentOffsetScaledLogVar;
    LONG            lObservedParentClockChangeRate;
    PTP_CLOCK_ID_SZ szGrandMasterId;
    PTP_CLOCK_QA_S  stGrandmasterClockQuality;/*协议前后不一致*/

    PTP_PORT_ADDR_S stParentPortAddr; /*保存PARENT的地址，便于反向索引到单播Master列表*/
    PTP_PORT_ADDR_S stParentPortExtAddr;/* parent的扩展地址 */
    ULONG           ulParentVrfIndex;

    /* VRF table, 管理带vrf socket */
    PTP_VRF_TBL_S   stPtpVrfTbl;

    /*时间属性数据集，全部是动态成员*/
    SHORT   sCurrentUtcOffset;
    BOOL_T    bCurrentUtcOffsetValid;
    BOOL_T    bLeap59;
    BOOL_T    bLeap61;
    BOOL_T    bTimeTraceable;
    BOOL_T    bFrequencyTraceable;
    BOOL_T    bPtpTimescale;
    /*Mod By t00110672 For BC3D02767,【TD产品需求】【PTP】实现1588无线选源方案优化*/
    BOOL_T    bClassIdentify;/*提供ClockClass识别功能的开关*/
    UCHAR      ucClass0;/*提供一组可优选的Class值，默认为6>13>7>14*/
    UCHAR      ucClass1;
    UCHAR      ucClass2;
    UCHAR      ucClass3;
    UCHAR    ucTimeSource;
    CHAR     cReserved8[3];
        /*Mod End*/

    /*其他关联属性或协议属性或无线属性*/
    PTP_PORT_S                  stPtpPort[PTP_SUPPORT_PORT_NUMBER];  /*定义时钟设备时钟端口*/
    PTP_ACCEPT_MASTER_TAB_S     stAcceptMasterTab;                   /*定义时钟可接受的Master列表*/
    PTP_UNI_MASTER_TBL_S        stUniMasterTbl;                  /*单播Master列表*/
    PTP_FAULTRECORD_S           stFaultRecord;                         /*错误记录*/

    ULONG ulRcvErrEventPkt;                                          /* 收到的错误event报文数 */
    ULONG ulRcvCrrctEventPkt;                                        /* 收到的正确的event报文数*/
    ULONG ulSndEventPkt;                                             /* 发送的event报文数 */
    /* the end of wangchengyang's addition */

    ULONG ulSlaveNum;

    /*单播协商的最大查询次数*/
    ULONG ulUniNegoQueryMaxTimes;

    /* keep alive报文超时次数 */
    ULONG ulLiveReceiptTimeout;
    /* the end of wangchengyang's addition */
    ULONG ulMaxMasterNumber;
    
    ULONG ulCancelQueryMaxTimes;

    ULONG ulTimerDelayCount;
}PTP_CLOCK_S;

/* 带VLAN头的PTP报文 */
#pragma pack(1)
/* VLAN标签结构体定义 */
typedef struct  tagPTPVLANTAG
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
}PTP_VLANTAG_S;

typedef  struct  tagPTPIEEE8023VlanHead
{
    UCHAR   ucDstMacAddr[PTP_ADDRLEN_IEEE8023];     /* 协议多播MAC: 01-1B-19-00-00-00 */
    UCHAR   ucSrcMacAddr[PTP_ADDRLEN_IEEE8023];     /* 源MAC                          */
    USHORT  usTPID;                                 /* 802.1q Protype 8100            */
    PTP_VLANTAG_S stVlanTag;                        /* Vlan标签                       */
    USHORT  usPTPType;                              /* PTP协议类型0x88F7              */
}PTP_IEEE8023VLAN_HEAD_S;

/* 不带VLAN的PTP Heard */
typedef struct tagPTPIEEE8023Head
{
    UCHAR   ucDstMacAddr[PTP_ADDRLEN_IEEE8023];     /* 协议多播MAC: 01-1B-19-00-00-00 */
    UCHAR   ucSrcMacAddr[PTP_ADDRLEN_IEEE8023];     /* 源MAC                            */

    USHORT   usPTPType;                             /* PTP协议类型0x88F7               */
}PTP_IEEE8023_HEAD_S;



typedef struct tagPTP_VLANCHAIN_S
{
    DLL_NODE_S stDllNode;                             /* 用于结点的存储*/
    ULONG  ulPhyPortNo;                               /* 物理端口号*/
    USHORT usVlanId;                                  /* VLAN ID*/
    USHORT usVlanPri;                                 /* VLAN优先级 */
}PTP_VLANCHAIN_S;


#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif
