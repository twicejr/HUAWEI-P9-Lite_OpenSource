/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_type.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD
*  Date Created: 2006-12-01
*        Author: Wangchengyang
*   Description: BFD需要用到的数据结构类型定义头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-01      Wangchengyang       Create
*
*******************************************************************************/
#ifndef _BFD_TYPE_H_
#define _BFD_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*Add for BC3D02737 BFD静态配置会话索引修改 l00147446 10-03-04*/
#define BFD_DEFAULT_GATE_VALUE 501
/*End for BC3D02737*/
#define BFD_ACTION_SND          1
#define BFD_ACTION_RCV          2
#define BFD_ACTION_SND_ERR      3
#define BFD_ACTION_RCV_ERR      4

/* BFD的检测模式 */
/* CAUTION: if modify mode define,pls update g_aszDetectMode */
typedef enum tagBFD_DETECT_MODE_E
{
    BFD_DETECT_ASYNC_WECHO      = 0     ,       /* 带ECHO功能的异步模式 */
    BFD_DETECT_ASYNC_WOECHO             ,       /* 不带ECHO功能的异步模式 */
    BFD_DETECT_DEMAND_WECHO             ,       /* 带ECHO功能的查询模式 */
    BFD_DETECT_DEMAND_WOECHO            ,       /* 不带ECHO功能的查询模式 */
    BFD_DETECT_MODE_MAX                         /* 检测模式的最大无效值 */
} BFD_DETECT_MODE_E ;

/* BFD 认证方式 */
typedef enum tagBFD_AUTH_TYPE_E
{
    BFD_AUTH_NONE      = 0            ,       /* 无认证 */
    BFD_AUTH_SIMPLE                   ,       /* 简单pwd认证 */
    BFD_AUTH_MD5                      ,       /* MD5认证 */
    BFD_AUTH_MMD5                     ,       /* Meticulous MD5认证 */
    BFD_AUTH_SHA1                     ,       /* SHA1认证 */
    BFD_AUTH_MSHA1                    ,       /* Meticulous SHA1认证 */
    BFD_AUTH_MAX                              /* 最大无效值 */
} BFD_AUTH_TYPE_E;

/*Begin BC3D02903 liangjicheng 2010-04-19 */
#define BFD_SESSION_STATE_NORMAL    0
#define BFD_SESSION_STATE_DELETE    1
/*End   BC3D02903 liangjicheng 2010-04-19 */  
typedef struct tagBFD_SESS_PKT_STATIC_S
{
    /* 协商统计信息  接收*/
    ULONG ulBfdRcvDown;      /*接收的DOWN报文*/
    ULONG ulBfdRcvInit;      /*接收的Init报文*/
    ULONG ulBfdRcvUp;        /*接收的Up报文*/
    ULONG ulBfdRcvAdminDown; /*接收的AdminDown报文*/
    ULONG ulBfdRcvErr;       /*接收的错误报文*/
    ULONG ulBfdRcvP;         /*接收的P报文*/
    ULONG ulBfdRcvF;         /*接收的F报文*/

    /* 协商统计信息  发送*/
    ULONG ulBfdSndDown;      /*发送的DOWN报文*/
    ULONG ulBfdSndInit;      /*发送的Init报文*/
    ULONG ulBfdSndUp;        /*发送的Up报文*/
    ULONG ulBfdSndAdminDown; /*发送的AdminDown报文*/
    ULONG ulBfdSndErr;       /*发送的错误报文*/    
    ULONG ulBfdSndP;         /*发送的P报文*/
    ULONG ulBfdSndF;         /*发送的F报文*/
}BFD_SESS_PKT_STATIC_S ;
/* BFD会话的配置表项 */
typedef struct tagBFD_SESS_CFG_ENTRY_S
{
    ULONG   ulBfdType                             ;      /* BFD绑定的类型 */
    ULONG   ulPeerAddrType                        ;      /* BFD绑定的地址类型 */
    ULONG   ulSrcAddr[4]                          ;      /* IPv4、IPv6地址,网络序 */
    ULONG   ulPeerAddr[4]                         ;      /* IPv4、IPv6地址,网络序 */
    ULONG   ulIfIndex                             ;      /* BFD指定的出接口索引 */
    ULONG   ulVrfIndex                            ;      /* BFD's Vpn index*/
    ULONG   ulVlanId                              ;      /* BFD指定的VlanId（在是以太网接口时用户可选） */
    BOOL_T  bDemand                               ;    
    BOOL_T  bEcho                                 ;    
    ULONG   ulDemandTimerInterval                 ;      /* BFD查询模式下定时查询的间隔，暂未使用 */ 
    ULONG   ulDetectMult                          ;      /* BFD的本地检测倍数 */ 
    ULONG   ulMinTxInterval                       ;      /* BFD期望的发送间隔 */ 
    ULONG   ulMinRxInterval                       ;      /* BFD的本地接收能力 */ 
    ULONG   ulMinEchoTxInterval                   ;      /* BFD会话本地回声功能的接收能力(不支持Echo,此值必须为0) */ 
    ULONG   ulMinEchoRxInterval                   ;      /* BFD回声功能的发送间隔(不支持Echo,此值必须为0)*/ 
    ULONG   ulWtrTimeInterval                     ;      /* Time for wtr. millisecond */
    USHORT  usAuthMode                            ;      /* BFD的认证方式 */ 
    UCHAR   ucAuthKeyId                           ;      /* BFD配置的认证KeyId */ 
    UCHAR   ucAuthPwd[BFD_LEN_MAX_SIMPLE_PWD + 1] ;      /* BFD配置的认证pwd */
    ULONG   ulSentPakcets                         ;      /* 发送报文个数 */
    ULONG   ulRcvPackets                          ;      /* 接收报文个数 */
    ULONG   ulLastSentTime                        ;      /* 最后发送报文时间 */
    ULONG   ulUpToDown                            ;      /* 会话状态Up变为Down的次数 */

    /* 对端已经确认了的收发间隔, Added by wujie 61195 for A82D25354, 2008/05/12 */
    ULONG   ulAckedCfgTX                          ;
    ULONG   ulAckedCfgRX                          ;
    UCHAR   szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
    UCHAR   szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
    UCHAR   ucTos                                 ;      /* bfd 会话tos */
    UCHAR   Padding[3]                            ;
    ULONG   ulRemoteDiscr;
}BFD_SESS_CFG_ENTRY_S ;

/* 会话实际的运行信息 size 13*4字节*/
typedef struct tagBFD_SESS_RUN_ENTRY_S
{
    ULONG   ulLocalDiscr              ;              /* BFD的本地标识符 */
    ULONG   ulRemoteDiscr             ;              /* BFD的对端标识符 */
    USHORT  usUdpSrcPort              ;              /* UDP的源端口号 */
    USHORT  usUdpDstPort              ;              /* UDP的目的端口号 */
    USHORT  usDetectMode              ;              /* BFD的检测模式 */
    USHORT  usIsMultiHop              ;              /* BFD会话是否是mulit-hop */ 
    ULONG   ulActTxInterval           ;              /* BFD实际的发送间隔 */ 
    ULONG   ulActRxInterval           ;              /* BFD的实际接收能力 */ 
    ULONG   ulDetectTime              ;              /* BFD的实际检测时间 */
    /*Add for BC3D00792,DR.177 保存对端实际检测倍数 */
    ULONG   ulActDetectMult           ;              /* BFD的对端检测倍数 */
    ULONG   ulActEchoTxInterval       ;              /* BFD会话本地回声功能的实际发送能力 */ 
    ULONG   ulActEchoRxInterval       ;              /* BFD回声功能的实际接收间隔 */ 
    ULONG   ulRcvAuthSeq              ;              /* 接收到序列号 */
    ULONG   ulXmitAuthSeq             ;              /* 发送的序列号对于MD5和SHA1 */
    BOOL_T  bAuthSeqKnown             ;              /* 接收的序列号是否可知 */
    BOOL_T  bPollFlag                 ;              /* 是否发送轮询报文 */
    USHORT  usLocalDiag               ;              /* 本地诊断字段 */
    USHORT  usSessState               ;              /* 会话的当前状态 */
    USHORT  usRemoteDemandMode        ;              /* 对端BFD会话是否设置为查询模式，BFD_TRUE:对端设置; BFD_FALSE:对端未设置 */
    USHORT  usReserved                ;              /* 四字节对齐，该字段保留不用 */
    /* Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 增加记录最近一次收到BFD报文中的RequiredMinRxInterval值 */   
    ULONG   ulRemoteMinRxInterval     ;              /*bfd对端期望的接收时间间隔值*/
    ULONG   ulRemoteMinTxInterval     ;              /*bfd对端期望的发送时间间隔值 added by luogaowei 2012-10-27*/
} BFD_SESS_RUN_ENTRY_S;

typedef struct tagBFD_SESS_COUNT_ENTRY_S
{
    ULONG   ulPktRcvDrop                        ;      /* 丢弃报文的个数 */
    ULONG   ulPktSendErr                        ;      /* 发送报文失败的个数*/
    ULONG   ulSessionStateTime                        ;      /* 会话开始的时间 */
    ULONG   ulLastDownTime                        ;      /* 最后一次Down的时间 */
} BFD_SESS_COUNT_ENTRY_S;

/* 会话信息，使用数组结构存放，最大为255个 */
typedef struct tagBFD_SESS_ENTRY_S
{
    ULONG   ulSessId                          ;      /* 会话ID */
    ULONG   ulDbgFlag                         ;      /* 会话debug开关，按位设置BFD_DEBUG_STATE/BFD_DEBUG_INPUT等 */
    ULONG   ulChangeFlag                      ;      /* 会话缓存的控制报文参数是否更改标志位。1 表示更改，0 表示未更改 */
    ULONG   ulAppId                           ;      /* 会话应用号,一个比特位标识一个应用 */
    ULONG   ulWtrTimerId                      ;      /* WTR定时器ID */
    ULONG   ulTxTimerId                       ;      /* 发送报文定时器ID */
    ULONG   ulDetectOrInitTimerId             ;      /* 会话Up之前为Init超时定时器，会话Up之后为探测定时器 */    
    CHAR*   pchPacket                         ;      /* 报文缓存Buffer，BFD4和BFD6结构不同;若参数未更改则直接拷贝发送，不用再构造报文 */
    ULONG   ulHAFlag                          ;      /* HA标记，取值BFD_HA_BEFORESMOOTH、BFD_HA_SMOOTHING、BFD_HA_SMOOTHED */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    ULONG   ulVrfIndex                        ;      /* VRF索引,主要用来通过具体的会话控制块反查其所在的VRF */
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
    
    ULONG   ulIpVer                           ;      /* IP版本标识:0--表示是IPv4 BFD;1--表示是IPv6 BFD */

    ULONG   ulSentNegoPakcets; /*用于统计发送报文个数，不会被清除，除非会话被删除*/

    BFD_SESS_CFG_ENTRY_S   stSessCfgEntry     ;      /* 会话的配置信息的表项索引 */
    BFD_SESS_RUN_ENTRY_S   stSessRunEntry     ;      /* BFD实际的信息 */ 
    BFD_SESS_COUNT_ENTRY_S stSessCountEntry;
    ULONG   ulCurrentGRState                  ;      /* 该BFD会话当前的GR状态, 取值见enumBFD_GR_STATE */
    ULONG   ulNotifyTimerId                   ;       /*指定时间内对外通知一次性定时器*/

    /*Begin BC3D02903 liangjicheng 2010-04-19 */
    ULONG   ulStateFlag                       ;       /*表项状态信息，用于刷新操作*/
    /*End   BC3D02903 liangjicheng 2010-04-19 */
    ULONG   ulNoPPIDown                       ;       /*用来标识删除会话时是否下发BFD_PPI_SESSION_DELETE*/
    
    /*Begin BC3D03565 chenlong 2010-10-08 */
    ULONG   ulNoSendDDFlag                    ;       /*取值为1表示删除会话时不发送Admin Down报文,取值为0表示删除会话时发送Admin Down报文*/
    /*End   BC3D03565 chenlong 2010-10-08 */
    /* Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 增加BFD创建会话的协议类型字段 */   
    ULONG   ulBfdProtocol;                            /*BFD创建会话的协议类型 BFD_PROTO_DRAFT4:草案4; BFD_PROTO_STD:标准RFC*/
    UCHAR   ucPFState;                                /*P标记状态: P_NULL, P_OPEN , F_ACK, P_EXPIRE*/
    UCHAR   ucPSndCount;                              /*P报文发送次数， 最大默认5次*/
    USHORT  usSessionPosNo;                           /*BFD会话的编号，先创建的先后顺序*/
#if (TCPIP_NSR == VRP_YES) 
    USHORT  usStateResultInSmooth;                    /* 平滑后会话状态*/
    UCHAR   ucNSRRcvAdmindown;                        /* nsr过程中收到admin down报文*/
    UCHAR   ucNSRCfgAdmindown;                        /* nsr过程中配置admin down*/
    UCHAR   ucNSRPPIFlag;                             /* NSR过程中PPI下发标志*/
    UCHAR   ucPad[3];
#endif
    BFD_SESS_PKT_STATIC_S stBfdSessPktStatic;
    
    /* Added by fengjing209023 for S-BFD-MultiSession.CFG.001 置为BFD_ON会生效，其他默认不生效 */
    ULONG ulMultiHopFlag;       /* 如果置上该标记，则在多跳下也是用3784，否则默认4784 */
    AVL3_NODE_S stBfdSessionNode;             /* AVL Node */
} BFD_SESS_ENTRY_S ;

/* BFD的控制报文格式 */
typedef struct tagBFD_CONTROL_PACKET_S
{
     BFD_PACKET_S   stMandPkt                      ;      /* 控制报文的强制部分 */
     UCHAR   ucAuthType                            ;      /* 认证类型 */
     UCHAR   ucAuthLen                             ;      /* 认证报文的长度 */
     UCHAR   ucAuthKeyID                           ;      /* 认证的KeyID */
     UCHAR   ucAuthPwd[BFD_LEN_MAX_SIMPLE_PWD + 1] ;      /* 认证的pwd */
     ULONG   ulSeqNum                              ;      /* 认证的序列号 */
} BFD_CONTROL_PACKET_S;

/* BFD使能开关状态 */
typedef enum tagBFD_CAPABILITY_E
{
    BFD_CAPABILITY_DISABLED      = 0         ,       /* BFD已去使能，默认为此 */
    BFD_CAPABILITY_ENABLED                   ,       /* BFD已经使能 */
    BFD_CAPABILITY_DISABLE_PROCESSING        ,       /* BFD正处于去使能中 */
    BFD_CAPABILITY_MAX                       ,       /* BFD使能标记最大无效值 */
}BFD_GLOBAL_CAPABILITY_E;

/* BFD License状态 */
typedef enum tagBFD_LICENSE_E
{
    BFD_LICENSE_DISABLED      = 0         ,       /* BFD License已去使能 */
    BFD_LICENSE_ENABLED                   ,       /* BFD License已经使能 */
    /* Modify for DTS2011021002203, by chenyaoKF34558, at 2011-02-28. 修改原因: 重新设计license功能 */
    BFD_LICENSE_DISABLING                 ,       /* BFD License去使能中*/
    BFD_LICENSE_ENABLING                  ,       /* BFD License使能中*/
}BFD_GLOBAL_LICENSE_E;

/* BFD消息类型 */
typedef enum tagBFD_MSG_TYPE_E
{
    BFD_ADD_IPADDR,           /* 增加地址 */
    BFD_DEL_IPADDR,           /* 删除地址 */
    BFD_START_POLL,           /* 用户发起POLL */
    BFD_SESSION_CREATE,       /* 用户创建会话 */
    BFD_SESSION_UPDATE,       /* 会话参数更新 */
    BFD_SESSION_SHUTDOWN,     /* 用户shutdown*/
    BFD_SESSION_UNDOSHUTDOWN, /* 用户undo shutdown */
    BFD_SESSION_DELETE,       /* 删除会话 */
    BFD_TRUNKPORT_ADD,        /* 接口加入trunk */
    BFD_TRUNKPORT_REMOVE,     /* 接口移除trunk */
    BFD_GLOBAL_DISABLE,       /* 全局去使能 */
    /*Added by qinyun62011, 优化BFD会话ID扩展到9215的性能问题, 2013/9/27 */
    BFD_VRF_DELETE,           /* 删除VRF */
    BFD_LICENSE_SHUTDOWN,     /* BFD License功能关闭 */
    BFD_LICENSE_UNDOSHUTDOWN, /* BFD License功能打开 */
    BFD_GLOBAL_RESETALL,       /* 全局复位会话*/

    /*Begin BC3D02903 liangjicheng 2010-04-19 */
    BFD_EXT_OSPF_RULE_ADD,     /* 这里定义三种处理，目前的处理不区分更新类型做整理更新*/
    BFD_EXT_OSPF_RULE_UPDATE,
    BFD_EXT_OSPF_RULE_DELETE,
    /*End   BC3D02903 liangjicheng 2010-04-19 */
    BFD6_GLOBAL_DISABLE,        /* bfd6全局去使能 */
    BFD6_VRF_DELETE,           /* 删除VRF */
    BFD6_GLOBAL_RESETALL,       /* bfd6全局复位会话*/
    BFD6_LICENSE_SHUTDOWN,       /* BFD6 License功能关闭 */
    BFD6_LICENSE_UNDOSHUTDOWN,   /* BFD6 License功能打开 */
    BFD6_ADD_IPADDR,           /* 增加IPv6地址 */
    BFD6_DEL_IPADDR,           /* 删除IPv6地址 */    
    BFD_EXT_REFERSH_ALL_RULE,    /*BFD EXT刷新所有规则*/
    BFD_MSG_MAX
}BFD_MSG_TYPE_E;

/* BFD消息数据结构 */
typedef struct tagBFD_MSG_S
{
   ULONG   ulMsgType       ;   /* 消息类型 */
   ULONG   ulSessionID     ;   /* 会话ID，用于用户发起POLL */
   ULONG   ulIfIndex       ;   /* 接口索引，用于地址增删 */
   /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01,因为BFD会话需要会话ID和Vrf Index共同标识
   * 而写消息的时候消息队列的参数是四个元素的ULONG的数组,鉴于地址和VRFIndex不同时出现，因此改为联合体 */
   union
   {
       ULONG   ulIPAddr    ;   /* 地址,网络序，用于地址增删 */
       UINTPTR ulIP6AddrHandle;
       ULONG   ulVrfIndex  ;   /* VRF索引 */
       UINTPTR ulLinkLink  ;   /* 用于传递数据的指针 */
   }unPrivate;
   /* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */
} BFD_MSG_S;

/*Begin BC3D02903 liangjicheng 2010-04-19 */
typedef struct tagBFD_EXT_OSPF_RULE_MSG
{
   ULONG    ulIPVertion;        /*IP版本号*/
   ULONG    ulMsgType;          /* 消息类型 */
   ULONG    ulProcIndex;
   ULONG    ulIfIndex;        /*接口索引*/
   ULONG    ulInstanceID;     /*接口实例ID(适用于OSPFV3场景)*/
   ULONG    ulMinTxInterval;
   ULONG    ulMinRxInterval;
   ULONG    ulDetectMult;
} BFD_EXT_OSPF_RULE_MSG;
/*End   BC3D02903 liangjicheng 2010-04-19 */

/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-01 */
/* BFD 会话查询标记*/
typedef struct tagBFD_KEY_S
{
    ULONG ulVrfIndex    ;     /* vrf 索引 */
    ULONG ulSessionId   ;     /* 会话标识 */
    ULONG ulIsAllVrf    ;     /* 是否查询所有VRF下的会话:1-是,0-不是 */
    ULONG ulIpVer       ;     /* IP版本标识 */
}BFD_KEY_S;
/* End:VISP1.7C03 VRF wangchengyang,2009-02-01 */

/* BFD6报文接收信息 */
typedef struct tagBFD_PKTINFO_S
{
    ULONG  ulDstIP[4];     /* 报文目的IP,网络序 */
    ULONG  ulSrcIP[4];     /* 报文源IP,网络序 */
    ULONG  ulVrfIndex;     /* 报文接收对应的VRF */
    ULONG  ulIfIndex;      /* 入接口索引 */
    USHORT usDstPort;      /* 目的端口号,网络序 */
    USHORT usTTL;          /* 报文携带的TTL */
    ULONG  ulIpVer;        /* IP版本标识:0--IPv4;1--IPv6 */
    ULONG  ulIsMutiHop;    /* 报文是否多跳*/
}BFD_PKTINFO_S;

typedef struct tagBFD_SESSION_PUB_INFO_S
{
    ULONG ulSessionId; /* 会话ID */
    ULONG ulIpVer;        /* IP版本标识:0--IPv4;1--IPv6 */
    ULONG ulOutIndex; /* 会话出接口*/
    ULONG ulAppId;       /* 会话应用号,一个比特位标识一个应用 */
    USHORT usSessState;/* 会话状态*/
    USHORT usLocalDiag;/* 本地诊断字段 */
}BFD_SESSION_PUB_INFO_S;

/* BFD模块是否能够发送备份报文 函数原型 */
typedef ULONG(*BFD_HA_CAN_SEND_PACKET)(VOID);

/* BFD模块发送备份报文 函数原型 */
typedef ULONG(*BFD_HA_SEND_LIVE_PACKET)(USHORT usType, ULONG ulSessionId, VOID * pucData, USHORT usInBufLen);

/* BFD模块获取HA调试开关状态 函数原型 */
typedef ULONG(*BFD_HA_GET_DBG_SWITCH)(VOID);

/* BFD模块查询当前是否禁止配置 函数原型 */
typedef ULONG(*BFD_HA_CANNOT_CFG)(VOID);

/* BFD HA调试函数输出 函数原型 */
typedef VOID(*BFD_HA_DBG_OUTPUT)(CHAR *pDebugInfo);

/* BFD状态通知VRRP模块的钩子 */
typedef VOID(*BFD_STATE_NOTIFYVRRP)(ULONG ulNotifyType, ULONG ulSessionID, ULONG ulVrfIndex, 
                    ULONG ulState, ULONG ulDstIP, ULONG ulSrcIP, ULONG ulInIfIndex, ULONG ulAppGroup);

/*Modified by qinyun62011, DTS2010092600602 BFD去使能时，没有删除对应的静态路由关联表项。 for VISP1.8C01, 2010/9/29 */
/* BFD状态通知BFD EXT模块的钩子 */
typedef VOID(*BFD_STATE_NOTIFYEXT)(ULONG ulNotifyType, ULONG ulSessionID, ULONG ulVrfIndex, 
                    ULONG ulDstIP, ULONG ulSrcIP, ULONG ulInIfIndex, ULONG ulNewSessionID);

typedef ULONG (*BFD_TaskonitorTimeInit)(VOID);

#ifdef __cplusplus
}
#endif

#endif

