/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ptpv2_api.h
*
*  Project Code:
*   Module Name: PTPV2 api
*  Date Created: 2014-03-3
*        Author: luoagwoei & dutianyi
*   Description: 主要提供给产品调用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-3      luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _TCPIP_PTPV2_API_h_
#define _TCPIP_PTPV2_API_h_

#ifdef __cplusplus
extern "C" {
#endif

/*PTP  端口的状态角色*/
#define  TCPIP_PTP_PORT_ROLE_UNDEFINED  0
#define  TCPIP_PTP_PORT_ROLE_MASTER     1
#define  TCPIP_PTP_PORT_ROLE_SLAVE      2
#define  TCPIP_PTP_PORT_ROLE_PASSIVE    3  /*BC中 系统没有选到源时候端口的状态*/

/* announce最小接收超时倍数 */
#define TCPPI_PTP_MIN_ANN_RCV_TIMEOUT        2

/* announce最小发送间隔(指数) */
#define TCPPI_PTP_MIN_ANN_SND_TIMEOUT        -3
/* announce最大发送间隔(指数) */
#define TCPPI_PTP_MAX_ANN_SND_TIMEOUT        3

/* PPI信息中的源参数变化标记 */
#define  TCPIP_PTP_PARA_CHANGE_FIELD_NONE   0     /* 源没有参数发生变化 */
#define  TCPIP_PTP_PARA_CHANGE_FIELD_BMC    0x01  /* 优选源发生变化 */
#define  TCPIP_PTP_PARA_CHANGE_FIELD_UTC    0x02  /* 源的UTC参数发生变化 */

/*定义时钟设备类型枚举*/
typedef enum tagPTPV2_TYPE_E
{
    PTPV2_CLOCK_TYPE_NULL = 0,    /*0  NULL*/
    PTPV2_CLOCK_TYPE_OC,         /*1  OC */
    PTPV2_CLOCK_TYPE_BC,        /*2  BC*/
    PTPV2_CLOCK_TYPE_END
} PTPV2_TYPE_E;

/*PTP错误码定义*/
typedef enum tagTCPIP_PTP_ERR_E
{
    TCPIP_PTP_OK = 0,
    TCPIP_PTP_ERR,
    TCPIP_PTP_ERR_POINTER_NULL,         /* 2.指针为空错误 */
    TCPIP_PTP_ERR_UNINIT,               /* 3.时钟实体未初始化 */
    TCPIP_PTP_ERR_OTHER_PTP_USED,       /* 4.PTPV1已经初始化 */
    TCPIP_PTP_ERR_INVALID_PARA,         /* 5.参数错误 */
    TCPIP_PTP_ERR_HOOK_UNREG,           /* 6.回调函数未注册 */
    TCPIP_PTP_ERR_INVALID_RCVINDEX,     /* 7.一个Master的报文从本端的多个接口物理收到 */
    TCPIP_PTP_ERR_INVALID_MBUF,         /* 8.MBUF非法 */
    TCPIP_PTP_ERR_WRITE_QUE_FAIL,       /* 9.写队列失败 */
    TCPIP_PTP_ERR_PACKET_LEN,           /* 10.报文长度非法 */
    TCPIP_PTP_ERR_INTF_NOT_EXIST,       /* 11.接口不存在 */
    TCPIP_PTP_ERR_MSGTYPE,              /* 12.消息类型错误 */
    TCPIP_PTP_ERR_NOT_SUPPORT_IN_OC,    /* 13.OC下不应存在PPI下发的情况 */
    TCPIP_PTP_ERR_NO_TIME_SOURCE,       /* 14.PTP还没有选到过时钟源 */
    TCPIP_PTP_ERR_MASTER_UP_MAX,        /* 15.ForeignMaster数量已达最大值 */
    TCPIP_PTP_ERR_MALLOC_FAIL,          /* 16.内存分配失败 */
    TCPIP_PTP_ERR_INTF_TYPE,            /* 17.不支持的接口类型 */
    TCPIP_PTP_ERR_PROTNO_FULL,          /* 18.端口号已用尽 */
    TCPIP_PTP_ERR_PROTINFO_NOT_EXIST,   /* 19.端口信息不存在 */
    TCPIP_PTP_ERR_PACKET,               /* 20.报文控制域字段错误*/
    TCPIP_PTP_ERR_PORTID,               /* 21.ForeignMaster的ClockID和端口号发生了变化*/
    TCPIP_PTP_ERR_NON_L2IF,             /* 22.当前使用了非层2接口*/
    TCPIP_PTP_ERR_TIMER_NUM_FULL,       /* 23.逻辑定时器数量已达最大值 */
    TCPIP_PTP_ERR_INVALID_DOMAIN,       /* 24.收到了不在同一个域的报文 */
    TCPIP_PTP_ERR_LOGIC_TIMERID_NULL,   /* 25.逻辑定时器ID为空 */
    TCPIP_PTP_ERR_LOGIC_TIMER_NUM_ZERO, /* 26.当前没有逻辑定时器 */
    TCPIP_PTP_ERR_CAST_MODE,            /* 27.不支持报文的CastMode */
    TCPIP_PTP_ERR_CLOCK_ACCURACY,       /* 28.无效的时钟精度 */
    TCPIP_PTP_ERR_SYSTEM_EXCEPTION,     /* 29.系统异常，全局/端口信息无法获取 */
    TCPIP_PTP_ERR_NO_START,             /* 30.端口未启动 */
    TCPIP_PTP_ERR_CREATE_QUEUE_FAILED,  /* 31.创建队列失败 */
    TCPIP_PTP_ERR_CREATE_TIMER,         /* 32.定时器创建失败 */
    TCPIP_PTP_ERR_PORTNO,               /* 33.无效的端口号 */
    TCPIP_PTP_ERR_VERSION,              /* 34.错误的PTP版本 */
    TCPIP_PTP_ERR_SEQUENCEID,           /* 35.错误的PTP序号 */
    TCPIP_PTP_ERR_UNICASTFLAG,          /* 36.报文的单多播模式非法 */
    TCPIP_PTP_ERR_CREATE_TASK,          /* 37.创建任务失败 */
    TCPIP_PTP_ERR_SMP_TIMEOUT,          /* 38.去初始化等待信号量超时 */
    TCPIP_PTP_ERR_ALREADY_STARTED,      /* 39.当前端口已经启动 */
    TCPIP_PTP_ERR_CLOCKID,              /* 40.错误的时钟ID */
    TCPIP_PTP_ERR_BMC_ERRNO1,           /* 41.ForeMaster与本端的时钟Id一样,AR-IP-PTP.002*/
    TCPIP_PTP_ERR_BMC_ERRNO2,           /* 42.ForeMaster与本端的时钟portnum一样,AR-IP-PTP.002*/
    TCPIP_PTP_ERR_STEPSREMOVED,         /* 43.收到了StepsRemoved大于等于255的Ann报文 */
    TCPIP_PTP_ERR_MAX = 255
} TCPIP_PTP_ERR_E;


/* 时间精度枚举定义 */
typedef enum tagTCPIP_PTP_CLOCK_ACCURACY_E
{
    TCPIP_PTP_CLOCK_ACCURACY_25NS = 0X20, /*The time is accurate to within 25 ns*/
    TCPIP_PTP_CLOCK_ACCURACY_100NS,       /*The time is accurate to within 100 ns*/
    TCPIP_PTP_CLOCK_ACCURACY_250NS,       /*The time is accurate to within 250 ns*/
    TCPIP_PTP_CLOCK_ACCURACY_1US,         /*The time is accurate to within 1 us*/
    TCPIP_PTP_CLOCK_ACCURACY_2P5US,       /*The time is accurate to within 2.5 us*/
    TCPIP_PTP_CLOCK_ACCURACY_10US,        /*The time is accurate to within 10 us*/
    TCPIP_PTP_CLOCK_ACCURACY_25US,        /*The time is accurate to within 25 us*/
    TCPIP_PTP_CLOCK_ACCURACY_100US,       /*The time is accurate to within 100 us*/
    TCPIP_PTP_CLOCK_ACCURACY_250US,       /*The time is accurate to within 250 us*/
    TCPIP_PTP_CLOCK_ACCURACY_1MS,         /*The time is accurate to within 1 ms*/
    TCPIP_PTP_CLOCK_ACCURACY_2P5MS,       /*The time is accurate to within 2.5 ms*/
    TCPIP_PTP_CLOCK_ACCURACY_10MS,        /*The time is accurate to within 10 ms*/
    TCPIP_PTP_CLOCK_ACCURACY_25MS,        /*The time is accurate to within 25 ms*/
    TCPIP_PTP_CLOCK_ACCURACY_100MS,       /*The time is accurate to within 100 ms*/
    TCPIP_PTP_CLOCK_ACCURACY_250MS,       /*The time is accurate to within 250 ms*/
    TCPIP_PTP_CLOCK_ACCURACY_1S,          /*The time is accurate to within 1 s*/
    TCPIP_PTP_CLOCK_ACCURACY_10S,         /*The time is accurate to within 10 s*/
    TCPIP_PTP_CLOCK_ACCURACY_M10S         /*The time is accurate to >10 s*/
} TCPIP_PTP_CLOCK_ACCURACY_E;


/* 报文类型定义 */
typedef enum tagTCPIP_PTP_MSG_TYPE_E
{
    TCPIP_PTP_MSG_SYNC              =       0,     /* Sync */
    TCPIP_PTP_MSG_DELAY_REQ,                       /* Delay_Req */
    TCPIP_PTP_MSG_PDELAY_REQ,                      /* Pdelay_Req */
    TCPIP_PTP_MSG_PDELAY_RESP,                     /* Pdelay_Resp */
    TCPIP_PTP_MSG_LIVE,                            /* keep alive packet */
    /* 5~7预留 */
    TCPIP_PTP_MSG_FOLLOW_UP         =       0x8,   /* Follow_Up */
    TCPIP_PTP_MSG_DELAY_RESP,                      /* Delay_Resp */
    TCPIP_PTP_MSG_PDELAY_RESP_FOLLOW_UP,           /* Pdelay_Resp_Follow_Up */
    TCPIP_PTP_MSG_ANNOUNCE,                        /* Announce */
    TCPIP_PTP_MSG_SIGNALING,                       /* Signaling */
    TCPIP_PTP_MSG_MANAGEMENT,                      /* Management */
    TCPIP_PTP_MSG_MAX
} TCPIP_PTP_MSG_TYPE_E;

/*PPI 命令枚举定义*/
typedef enum tagTCPIP_PTP_PPI_CMD_E
{
        TCPIP_PTP_PPI_ADD = 0,        /* 选中时钟源*/
        TCPIP_PTP_PPI_DEL,            /* 删除时钟源*/
        TCPIP_PTP_PPI_UPDATE,         /* 源的UTC参数、是否优选源发生变化*/
        TCPIP_PTP_PPI_MAX
} TCPIP_PTP_PPI_CMD_E;

/* 端口地址定义 */
typedef struct tagTCPIP_PTP_PORT_ADDR_S
{
    USHORT  usNetworkProtocol;
    USHORT  usAddressLength;
    union
    {
        ULONG   ulIpv4;         /* 主机字节序 */
        UCHAR   ucMacAddr[8];   /*physical地址 8字节为了对齐*/
        ULONG   ulIpv6[4];      /*IPv6地址，主机字节序 */
    } unAddr;
} TCPIP_PTP_PORT_ADDR_S;

#define TCPIP_PTP_CLOCK_ID_LEN      8

#pragma pack(1)
/*PTP clock ID*/
typedef UCHAR TCPIP_PTP_CLOCK_ID_SZ[TCPIP_PTP_CLOCK_ID_LEN];

typedef struct tagTCPIP_PTP_PORT_ID_S   /*PTP port ID*/
{
    TCPIP_PTP_CLOCK_ID_SZ szClockId;
    USHORT          usPortNumber;
}TCPIP_PTP_PORT_ID_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/*端口数据集*/
typedef struct tagTCPIP_PTP_PORT_DS
{
    ULONG ulIfIndex;  /*接口索引，对于OC，返回第一个*/
    USHORT usPortNo;  /*port number*/
    UCHAR ucPortState; /*端口的状态*/
    CHAR   clogAnnounceInterval;      /*Announce发送间隔*/
    UCHAR  ucAnnRcvTimeoutNum;  /*announce接收超时次数*/
    UCHAR  ucCastMode;/*单播、多播模式，目前仅支持L2组播*/
    UCHAR  ucDomain;  /*域*/
    UCHAR  ucPortRole; /*端口角色*/
    UCHAR  ulPading[32]; /*预留字段*/
} TCPIP_PTP_PORT_INFO_S;

typedef struct tagTCPIP_PTP_CLOCK_QA_S
{
    UCHAR   ucClockClass;                   /* 时钟等级 */
    UCHAR   ucClockAccuracy;                /* 时钟精度 */
    USHORT  usOffsetScaledLogVariance;      /* 时钟稳定度 */
} TCPIP_PTP_CLOCK_QA_S;

typedef struct tagPTCPIP_PTP_PKT_STAT
{
    ULONG ulSndAnnPackets;              /*发送Announce报文 */
    ULONG ulRcvAnnPackets;              /*接收announce报文 */
    ULONG ulRcvErrorPackets;
    ULONG ulRcvErrorTotalLenPackets;    /*接收TotalLen非法的报文*/
    ULONG ulRcvErrorDomainNoPackets;    /*接收不相同域的报文*/
    ULONG ulRcvErrorPtpLenPackets;      /*接收PtpLen非法的报文*/
    ULONG ulRcvErrorAddrPackets;        /*接收地址信息非法的报文*/
    ULONG ulRcvErrorClockIdPackets;     /*接收ClockId相同的报文*/
    ULONG ulRcvErrorSeqIdPackets;       /*接收SeqId错误的报文*/
    ULONG ulRcvErrorUnexpectedSeqIdPackets; /*接收非预期SeqId的报文，不是错误*/
    ULONG ulRcvErrorIfPackets;          /*同一个ForeMaster的报文从不同物理口被收到*/
    ULONG ulRcvErrorForeMasterPackets;  /*接收导致ForeMaster创建或查找失败的报文*/

    ULONG ulSndDropPackets;             /*If模块发送失败丢包*/
    ULONG ulSndBuildDropPackets;        /*发送构包失败丢包*/
    ULONG ulSndGetIfDropPackets;        /*发送获取If控制块失败丢包*/
    ULONG ulReserve[25];
} TCPIP_PTP_PKT_STAT_S; /*PTP 报文统计*/

/* IP/UDP信息，主要用来
   1)收到报文之后，将收到报文的IP/UDP信息组织起来，作为参数传给报文接收函数
   2)用户配置IP和UDP端口的时候调用
*/
typedef struct tagTCPIP_PTP_ADDRINFO_S
{
    TCPIP_PTP_PORT_ADDR_S  stDstPortAddr;   /* 目的地址信息，主机序。对接收报文来说，目的地址即为本地地址；对发送报文来说，目的地址为对端地址 */
    TCPIP_PTP_PORT_ADDR_S  stSrcPortAddr;   /* 源地址信息，主机序。对接收报文来说，源地址即为对端地址；对发送报文来说，源地址为本端地址 */
    ULONG            ulDstUdpPort;      /* 目的UDP端口，主机序。 */
    ULONG            ulSrcUdpPort;      /* 源UDP端口号，主机序。 */
    ULONG            ulVrfIndex;        /* 所属VRF index */
    ULONG            ulIfIndex;         /* 仅用于报文接收处理中保存入接口索引，发送流程中不使用*//*qinyun&luogaowei 0地址方案 2011-12-12*/
}TCPIP_PTP_ADDRINFO_S;

typedef ULONG (* TCPIP_PTP_PPI_HOOK_FUNC) (ULONG ulPtpFsmRole, ULONG ulPtpPpiCmd, void* pstPtpPpiInfo);
typedef ULONG (* TCPIP_PTP_CAPTURE_PACKET_FUNC)(ULONG ulInOrOut, UCHAR* pucPacket, ULONG ulPacketLen, TCPIP_PTP_ADDRINFO_S *pstIpUdpInfo, ULONG ulPortNo);

/*告警,维测相关*/
#define TCPIP_PTP_WARNING_BEGIN 1  /*告警上报*/
#define TCPIP_PTP_WARNING_END  0   /*告警取消*/

/*告警ID*/
typedef enum tagTCPIP_PTP_WARN_ID_E
{
    TCPIP_PTP_WARN_BMC_FAIL = 0,    /*30秒内选不到源的告警*/
    TCPIP_PTP_WARN_ID_MAX           /*PTP WARNING ID 最大值 */
}TCPIP_PTP_WARNINGID_E;

typedef struct tagTCPIP_PTP_WARN_PARAM_S
{
    UCHAR ucWarnType;/*告警类型*/
    UCHAR ucWarnState; /*告警动作,1-告警,0-恢复告警*/
    UCHAR ucReserve[2];
}TCPIP_PTP_WARN_PARAM_S;

/* 获取报文方向:1--入方向;0--出方向 */
#define TCPIP_PTP_PKT_IN    1
#define TCPIP_PTP_PKT_OUT   0

/* 告警消息输出函数指针类型定义 */
typedef ULONG (* TCPIP_PTP_WARN_OUTPUT_FUNC) (TCPIP_PTP_WARN_PARAM_S *pstPtpWarnPara);

/* Debug消息输出函数指针类型定义 */
typedef VOID (* TCPIP_PTP_DBG_OUTPUT_FUNC)(CHAR *pszMsg);

/*PTP defualt DS*/
typedef struct tagTCPIP_PTP_DEFAULT_DS
{
    ULONG   ulNumberPorts;
    TCPIP_PTP_CLOCK_QA_S stCfgClockQa;/* 时钟等级 时钟精度 时钟稳定度 */
    BOOL_T  bTwoStepFlag;
    UCHAR   ucPriority1;
    UCHAR   ucPriority2;
    USHORT  usClockFsmMode;
    /*master 使用 UTC 参数*/
    SHORT   sCurrentUtcOffset;
    BOOL_T  bCurrentUtcOffsetValid;
    BOOL_T  bLeap61;
    BOOL_T  bLeap59;

    UCHAR   ucDomainNumber;
    UCHAR   ucPriClassFlag;/*标记是否选择优选源*/
    UCHAR   ucClass0;/*优选源0*/
    UCHAR   ucClass1;/*优选源1*/
    UCHAR   ucClass2;/*优选源2*/
    UCHAR   ucClass3;/*优选源3*/

    CHAR    szReserved[8];
} TCPIP_PTP_DEFAULT_DS_S;

/*最终选中的时钟源*/
typedef struct TagTCPIP_PTP_PARENT_DS
{
    TCPIP_PTP_CLOCK_ID_SZ   szGrandMasterId;
    TCPIP_PTP_PORT_ID_S     stParentPortId;
    TCPIP_PTP_PORT_ADDR_S   stParentAddr;
    TCPIP_PTP_CLOCK_QA_S    stParentClockQA;
    UCHAR   ucGrandmasterPriority1;
    UCHAR   ucGrandmasterPriority2;

    BOOL_T      bCurrentUtcOffsetValid;
    SHORT       sCurrentUtcOffset;      /*当前UTC偏移 */
    BOOL_T      bLeap59;
    BOOL_T      bLeap61;

    BOOL_T      bTimeTraceable;
    BOOL_T      bFrequencyTraceable;    /*是否追踪到主时钟频率*/
    BOOL_T      bTimeScale;
    BOOL_T      bPtpTimescale;          /*从上一级时钟获取时间标尺*/
    UCHAR       ucTimeSource;           /*时钟源 :从上一级时钟获取*/
    CHAR        cLogMAnnInterval;       /*Ann的发送间隔，由Ann报文学到，多播下使用*/
    USHORT      usStepsRemoved;         /*本端为0*/
    UCHAR       ucBestClassFlag;        /*是否带有优选源标记*/
    UCHAR       ucPadding[9];
} TCPIP_PTP_PARENT_DS_S;

/*slave下发PPI*/
typedef struct tagTCPIP_PTP_SLAVE_PPI
{
    ULONG   ulIfIndex;                      /*接口索引*/
    TCPIP_PTP_PORT_ADDR_S stLocalAddr;      /*本地址*/
    USHORT  usLocalPortNo;                  /*PTP端口号*/
    BOOL_T  bTwoStep;                       /*是否是单双步时钟*/
    ULONG   ulChangeField;                  /*源变化的信息: UTC变化，class变化*/    
    UCHAR   Reserved[124];
    TCPIP_PTP_PARENT_DS_S  stParentDS;      /*选中源的信息*/
} TCPIP_PTP_SLAVE_PPI_S;

typedef struct tagTCPIP_PTP_SYSTEM_INFO
{
    TCPIP_PTP_CLOCK_ID_SZ   szClockId;      /*clock id*/
    TCPIP_PTP_DEFAULT_DS_S  stDefaultDS;    /* 本设备配置的时钟信息*/
    TCPIP_PTP_PARENT_DS_S   stParentMasterDS;/*选中的时钟源信息*/
} TCPIP_PTP_SYSTEM_INFO_S;

/*端口状态机流程确认出端口角色,并PPI下发的信息类型,AR-IP-PTP.002*/
typedef struct tagTCPIP_PTP_PASSIVE_PPI
{
    ULONG   ulIfIndex;                      /*接口索引*/
    TCPIP_PTP_PORT_ADDR_S stLocalAddr;      /*本地址*/
    USHORT  usLocalPortNo;                  /*PTP端口号*/
    UCHAR   Reserved[122];
} TCPIP_PTP_PASSIVE_PPI_S;

/* 调试开关 */
typedef enum tagTCPIP_PTP_DEBUG_FLAG_E
{
    TCPIP_PTP_DEBUG_FOREMASTER  = 0x01,   /* PTP ForeMaster调试 */
    TCPIP_PTP_DEBUG_INPUT  = 0X02,        /* 接收的PTP报文调试 */
    TCPIP_PTP_DEBUG_OUTPUT = 0X04,        /* 发送的PTP报文调试 */
    TCPIP_PTP_DEBUG_TIMER  = 0X08,        /* PTP定时器的调试 */
    TCPIP_PTP_DEBUG_WARN   = 0X10,        /* PTP告警的调试 */
    TCPIP_PTP_DEBUG_PPI    = 0x20         /* PPI信息的调试 */
}TCPIP_PTP_DEBUG_FLAG_E;

/*Add by heyijun 00218462 for AR-IP-PTP.001 支持PTSF配置参与选源, 2014-11 */
/*Ptsf类型，目前仅支持TCPIP_PTP_PTSF_SYNC*/
typedef enum tagTCPIP_PTP_PTSF_TYPE_E
{
    TCPIP_PTP_PTSF_SYNC,
    TCPIP_PTP_PTSF_UNUSED
}TCPIP_PTP_PTSF_TYPE_E;

typedef struct TCPIP_PTP_FOREIGN_MASTER
{
    TCPIP_PTP_PORT_ID_S szForeignMasterPortId;  /*ForeginMaster Id*/
    UCHAR               ucPad[2];
    ULONG               ulRcvIfIndex;           /*Master所在的接口索引*/
    ULONG               ulPtsfValue;            /*Ptsf值*/
    ULONG               ulAnnRcvTimeoutNum;     /*接收ann 报文超时次数*/
    UCHAR               ucReserve[120];         /*预留字段*/
}TCPIP_PTP_FOREIGN_MASTER_S;

/*全局配置*/
/*******************************************************************************
*    Func Name: TCPIP_PTP_Init
* Date Created: 2014-03-03
*       Author: luogaowei
*      Purpose: PTPV2初始化
*  Description: PTPV2初始化，创建定时器、报文、控制消息队列，创建PTP任务，分配端口资源
*        Input: ulPtpClockType: PTP时钟类型，OC或者BC
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-03   luogaowei               Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_Init(ULONG ulPtpClockType);

/*******************************************************************************
*    Func Name: TCPIP_PTP_UnInit
* Date Created: 2014-03-03
*       Author: luogaowei
*      Purpose: PTPV2去初始化
*  Description: PTPV2去初始化，写事件给PTP主任务，并等待主任务卸载完成
*        Input: 
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-03   luogaowei               Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_UnInit();

/*******************************************************************************
*    Func Name: TCPIP_PTP_AddPort
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: 创建可用的PTP端口
*  Description: 创建可用的PTP端口
*        Input: ULONG ulIfIndex: 接口索引
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr: 添加的PTP地址，目前不使用，用于将来扩展
*       Output: USHORT* pusPtpPortNo:返回的PTP端口号
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 1.目前仅支持Overmac，基于接口配置不需要指定physical地址
*               2.OC下，返回的端口号只能为1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_AddPort(ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr,
                        USHORT* pusPtpPortNo);

/*******************************************************************************
*    Func Name: TCPIP_PTP_DelPort
* Date Created: 2014-03-21
*       Author: luogaowei & dutianyi
*      Purpose: 删除指定的PTP端口
*  Description: 删除指定的PTP端口
*        Input: USHORT usPtpPortNo:PTP端口号
*               ULONG ulIfIndex:接口索引
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr:PTP地址
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 1. BC只需要指定的端口号即可，后两个参数传任意值即可
*               2. OC由于共享的是端口号1，需要指定接口索引(后续也可能需要指定地址)
*               3. pstPtpAddr仅为未来扩展预留，在OC下，同一个接口不同的地址可以配置PTP应用
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-21   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_DelPort(USHORT usPtpPortNo, ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr);

/*******************************************************************************
*    Func Name: TCPIP_PTP_Start
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: 启动PTP的功能
*  Description: 启动PTP的功能，启动指定端口的发送定时器
*        Input: USHORT usPtpPortNo: 创建的PTP端口号
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr: 地址信息目前不使用，将来扩展
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 1.参数pstPtpAddr暂时不使用，用于将来扩展支持层3单播功能
*               2.OC下仅有一个端口，启动后该端口所有的物理口都会发送报文
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_Start(USHORT usPtpPortNo, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetClockIdentity
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: 配置PTP时钟ID
*  Description: 配置PTP时钟ID
*        Input: TCPIP_PTP_CLOCK_ID_SZ szClockID:PTP时钟ID
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 参数有效性由产品保证
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetClockIdentity(TCPIP_PTP_CLOCK_ID_SZ szClockID);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetClockQuality
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: 设置时钟源质量
*  Description: 设置时钟源质量
*        Input: TCPIP_PTP_CLOCK_QA_S *pstPtpCfgClockQuality:时钟源质量
*                 pstPtpCfgClockQuality->ucClockClass:时钟类别，默认0
*                 pstPtpCfgClockQuality->ucClockAccuracy: 时钟精度，默认0，范围0x20-0x32
*                 pstPtpCfgClockQuality->usOffsetScaledLogVariance:时钟稳定度，默认0
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 时钟等级/时钟稳定度的有效性由产品保证
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetClockQuality(TCPIP_PTP_CLOCK_QA_S *pstPtpCfgClockQuality);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetUtcProperties
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi
*      Purpose: OC matser下设置UTC
*  Description: OC matser下设置UTC
*        Input: SHORT sCurrentUtcOffset:UTC偏移量
*               BOOL_T bLeap61:Leap61
*               BOOL_T bLeap59:Leap59
*               BOOL_T bCurrentUtcOffsetValid:UTC偏移量有效性
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 1.Leap61和Leap59不能同时为真
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetUtcProperties(SHORT sCurrentUtcOffset, BOOL_T bLeap61, BOOL_T bLeap59, 
                                    BOOL_T bCurrentUtcOffsetValid);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetPriClassGroup
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: 设置PTP优选源
*  Description: 设置PTP优选源，选中与优选源一致的源进行PPI下发时会携带优选源标记
*        Input: UCHAR ucClass0
*               UCHAR ucClass1
*               UCHAR ucClass2
*               UCHAR ucClass3
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 参数有效性由产品保证
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetPriClassGroup(UCHAR ucClass0, UCHAR ucClass1, UCHAR ucClass2, UCHAR ucClass3);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetDomain
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: 设置时钟设备的域参数
*  Description: 设置时钟设备的域参数，PTP通信仅在同一个域的时钟间进行
*        Input: UCHAR ucDomainNumber:时钟设备域
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 参数有效性由产品保证
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetDomain(UCHAR ucDomainNumber);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetAnnInterval
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: 设置端口的Ann报文消息间隔(指数形式)
*  Description: 设置端口的Ann报文消息间隔(指数形式)
*        Input: USHORT usPtpPortNo:时钟端口号
*               CHAR cLogAnnInterval:时钟端口LogAnnounceInterval值, 默认1，范围0--4
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: OC下端口号只能为1，时间间隔由产品保证有效性
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetAnnInterval(USHORT usPtpPortNo, CHAR cLogAnnInterval);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetAnnRcvTimeoutNum
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: 设置announce报文接收超时最大次数
*  Description: 设置announce报文接收超时最大次数，超过该次数后会删除端口上对应的ForeignMaster
*        Input: USHORT usPtpPortNo:PTP端口号
*               UCHAR ucReceiptTimeout:接收超时最大次数，接收超时次数的默认值为3，范围2-10
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: OC下端口号只能为1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetAnnRcvTimeoutNum(USHORT usPtpPortNo, UCHAR ucAnnRcvTimeoutNum);

/*******************************************************************************
*    Func Name: TCPIP_PTP_GetSysInfo
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: 获取PTP当前的全局信息
*  Description: 获取PTP当前的全局信息(用户配置信息和选中的上游时钟源信息)
*        Input: 
*       Output: TCPIP_PTP_SYSTEM_INFO_S *pstSysInfo:PTP全局信息
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_GetSysInfo(TCPIP_PTP_SYSTEM_INFO_S *pstSysInfo);

/*******************************************************************************
*    Func Name: TCPIP_PTP_GetPortInfo
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: 获取PTP端口级信息
*  Description: 获取PTP端口级信息
*        Input: USHORT usPtpPortNo:时钟端口号
*       Output: TCPIP_PTP_PORT_INFO_S *pstPortPara:PTP端口级信息
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: OC下端口号只能为1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_GetPortInfo(USHORT usPtpPortNo, TCPIP_PTP_PORT_INFO_S *pstPortPara);

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowSysInfo
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: 打印PTP当前的全局信息
*  Description: 打印PTP当前的全局信息
*        Input: 
*       Output: PTP当前的全局信息
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowSysInfo();

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowPortInfo
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: 打印PTP端口级信息
*  Description: 打印PTP端口级信息
*        Input: USHORT usPtpPortNo:时钟端口号
*       Output: PTP的端口级信息
*       Return: 
*      Caution: OC下端口号只能为1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowPortInfo(USHORT usPortNo);

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowSysPktStatics
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: 打印PTP系统级报文统计信息
*  Description: 打印PTP系统级报文统计信息
*        Input: 
*       Output: PTP的系统级报文统计信息
*       Return: 
*      Caution: OC下端口号只能为1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowSysPktStatics();

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowPortPktStatics
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: 打印PTP端口级报文统计信息
*  Description: 打印PTP端口级报文统计信息
*        Input: 
*       Output: PTP的端口级报文统计信息
*       Return: 
*      Caution: OC下端口号只能为1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowPortPktStatics(USHORT usPortNo);

/*******************************************************************************
*    Func Name: TCPIP_PTP_RegFuncWarningHook
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: 注册告警函数
*  Description: 注册告警函数
*        Input: TCPIP_PTP_WARN_OUTPUT_FUNC pfWarnOutPut:告警处理函数
*       Output: 
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_RegFuncWarningHook(TCPIP_PTP_WARN_OUTPUT_FUNC pfWarnOutPut);

/*******************************************************************************
*    Func Name: TCPIP_PTP_RegFuncPpiHook
* Date Created: 2014-03-15
*       Author: luogaowei
*      Purpose: 注册PPI下发处理函数
*  Description: 注册PPI下发处理函数
*        Input: TCPIP_PTP_PPI_HOOK_FUNC pfPtpPpiHook:PPI下发处理函数
*       Output: 
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_RegFuncPpiHook(TCPIP_PTP_PPI_HOOK_FUNC pfPtpPpiHook);

/*******************************************************************************
*    Func Name: TCPIP_PTP_RegFuncCapturePacketHook
* Date Created: 2014-03-15
*       Author: luogaowei
*      Purpose: 注册报文捕获函数
*  Description: 注册报文捕获函数
*        Input: TCPIP_PTP_WARN_OUTPUT_FUNC pfWarnOutPut:报文捕获函数
*       Output: 
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei               Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_RegFuncCapturePacketHook(TCPIP_PTP_CAPTURE_PACKET_FUNC pfPtpCapturePacket);

/*******************************************************************************
*    Func Name: TCPIP_PTP_GetPktPortStat
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: 获取端口的报文统计信息
*  Description: 获取端口的报文统计信息
*        Input: USHORT usPtpPortNo:时钟端口号
*       Output: TCPIP_PTP_PKT_STAT_S *pStatPackets:基于端口的报文统计信息
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: OC下端口号只能为1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_GetPktPortStat(USHORT usPortNo, TCPIP_PTP_PKT_STAT_S *pStatPackets);

/*******************************************************************************
*    Func Name: TCPIP_PTP_GetPktStat
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: 获取全局的报文统计信息
*  Description: 获取全局的报文统计信息
*        Input: 
*       Output: TCPIP_PTP_PKT_STAT_S *pStatPackets:全局的报文统计信息
*       Return: 成功返回PTP_OK，失败返回错误码
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_GetPktStat(TCPIP_PTP_PKT_STAT_S *pStatPackets);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetDbgSwitch
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: 设置Debug开关
*  Description: 设置Debug开关
*        Input: ULONG ulDbgFlag:
*                   TCPIP_PTP_DEBUG_FOREMASTER  = 0x01,   PTP ForeMaster调试
*                   TCPIP_PTP_DEBUG_INPUT  = 0X02,        接收的PTP报文调试
*                   TCPIP_PTP_DEBUG_OUTPUT = 0X04,        发送的PTP报文调试
*                   TCPIP_PTP_DEBUG_TIMER  = 0X08,        PTP定时器的调试
*                   TCPIP_PTP_DEBUG_WARN   = 0X10         PTP告警的调试
*       Output: 
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetDbgSwitch (ULONG ulDbgFlag);

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowTimerInfo
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: 打印PTP当前所有的定时器信息
*  Description: 打印PTP当前所有的定时器信息
*        Input: 
*       Output: PTP当前所有的定时器信息
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowTimerInfo();

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowForeMasterInfo
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: 打印PTP当前所有的ForeMaster信息
*  Description: 打印PTP当前所有的ForeMaster信息
*        Input: 
*       Output: PTP当前当前所有的ForeMaster信息
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowForeMasterInfo();


ULONG TCPIP_PTP_GetForeignMasterInfo(ULONG ulVrfIndex,
    TCPIP_PTP_PORT_ADDR_S   *pstInForeignMasterPortAddr,
    TCPIP_PTP_FOREIGN_MASTER_S *pstOutForeignMasterInfo);


ULONG TCPIP_PTP_SetPtsf(ULONG ulVrfIndex, TCPIP_PTP_PORT_ADDR_S* pstForeignMasterAddr, ULONG ulPtsfType,ULONG ulPTSFValue);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of _TCPIP_PTPV2_API_h_   */
