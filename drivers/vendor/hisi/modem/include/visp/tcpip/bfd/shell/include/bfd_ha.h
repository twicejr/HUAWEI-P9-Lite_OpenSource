/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_ha.h
*
*  Project Code:  VISP1.6
*   Module Name:  bfd Module   
*  Date Created:  2006-12-06
*        Author:  j51916
*   Description:  bfd_ha high availability function implement
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE                  NAME                     DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-06            j51916                  Creat the first version.
*  2007-08-13            w61195                  质量提升整改
*
*
*******************************************************************************/

#ifndef _BFD_HA_H_
#define _BFD_HA_H_

#ifdef  __cplusplus
extern  "C"{
#endif

/* BFD HA备份消息类型 */
/* 注意: 如果更改了备份类型，则需要同步修改 pszBfdBakTypeStr字符串  */
typedef enum tagBFD_HA_MSG_TYPE
{
    BFD_MSGTYPE_UNKNOW,            /* 0  错误的备份消息类型 */
    BFD_SESSION_UP_BAK,            /* 1  会话UP备份块 */
    BFD_SESSION_CREATE_BAK,        /* 2  用户创建会话控制块*/
    BFD_SESSION_DEL_BAK,           /* 3  用户配置删除会话控制块*/
    BFD_SESSION_CFG_UPDATE_BAK,    /* 4  用户配置更新会话参数 */
    BFD_SESSION_BATCH_BAK,         /* 5  批量备份会话块 */

    BFD_SESSION_DIG_DOWN_BAK,      /* 6  用户控制会话down */
    BFD_SET_FUNC_ENABLE_BAK,       /* 7  设置使能BFD配置 */
    BFD_SESSION_SET_WTR_TIME_BAK,  /* 8  设置会话down以后重发报文时间*/
    BFD_SESSION_SET_APPS_FLAG,     /* 9  设置应用组*/

    BFD_SESSION_SET_SING_APPS_BAK, /* 10 设置单个应用组*/
    BFD_SESSION_DEL_SING_APPS_BAK, /* 11 删除单个应用组*/
    BFD_REC_ASY_PACKET_BAK,        /* 12 更改了(异步模式)会话参数的报文 */
    BFD_REC_DEMAND_BAK,            /* 13 更改了(查询模式)会话参数的报文 */
    BFD_UNDO_SHUTDOWN_BAK,         /* 14 用户控制会话undo shutdown */

    BFD_ADAPT_MULTIHOP_PORT,       /* 15 全局开关备份: 是否允许多跳会话自动调整UDP目的端口号 */
    BFD_NEW_MULTIHOP_PORT,         /* 16 备份多跳会话改变后的目的端口号 */
    
    BFD_SESSION_BAK_TOS,           /* 17 备份bfd会话tos值 */
    BFD_CREATE_VRF_SESSION_BAK,    /* 18 多实例下用户创建BFD会话 */
    BFD_DELETE_VRF_SESSION_BAK,    /* 19 多实例下用户删除BFD会话 */
    BFD_UPDATE_VRF_SESSION_CFG_BAK,/* 20 用户配置更新会话参数 */
    BFD_DIG_DOWN_VRF_SESSION_BAK,  /* 21 用户控制会话down */
    BFD_SETAPPS_VRF_SESSION_FLAG,  /* 22 设置应用组 */
    BFD_SETSINGAPPS_VRF_SESSION_BAK, /* 23 设置单个应用组 */
    BFD_DELSINGAPPS_VRF_SESSION_BAK, /* 24 删除单个应用组 */
    BFD_VRF_REC_ASY_PACKET_BAK,      /* 25 更改了(异步模式)会话参数的报文 */
    BFD_VRF_REC_DEMAND_BAK,          /* 26 更改了(查询模式)会话参数的报文 */
    BFD_VRF_UNDO_SHUTDOWN_BAK,       /* 27 用户控制会话undo shutdown */
    BFD_VRF_NEW_MULTIHOP_PORT_BAK,   /* 28 备份多跳会话改变后的目的端口号 */
    BFD_SESSION_NAME_BAK,            /* 29 备份BFD名字 */
    BFD_SESSION_DESC_BAK,            /* 30 备份BFD描述 */
    /* Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 会话创建协议类型备份 */   
    BFD_SESSION_BFDPROTOCOL_BAK,     /* 31 备份创建BFD会话的协议类型 */
    BFD_SESSION_REMOTEMRI_BAK,       /* 32 备份对端RequiredMinRxInterval值 */  
    BFD_SESSION_REMOTE_DEMANDMODE_BAK,       /* 32 备份对端DemandMode值 */  

    BFD_MSGTYPE_MAX,               /*  操作类型上限 [注意]: 如果更改了备份类型，则需要同步修改 pszBfdBakTypeStr字符串 */
} BFD_HA_MSG_TYPE;

/* Begin of HA UPGRADE modification, 2010 December to 2011 January */
/* 该消息由VISPV1R6C02和VISPV1R6C05版本发出, 需要做兼容性特殊处理 */
#define BFD_CREATE_VPN_SESSION_BAK  17

typedef struct tagBFD_CREATE_VPN_SESSION_BAK
{
    USHORT  usType;                /* 备份消息块类型 */
    USHORT  usLen;                 /* 备份消息块的总长度 */
    ULONG   ulSessId;              /* 会话ID */
    ULONG   ulDstIP;               /* 目的地址(网络序) */
    ULONG   ulSrcIP;               /* 源地址(网络序) */
    ULONG   ulOutIfIndex;          /* 出接口 */
    ULONG   ulVrfIndex;            /* 会话所属得VPN*/
}BFD_CREATE_VPN_SESSION_BAK_S;
/* End of HA UPGRADE modification, 2010 December to 2011 January */

typedef struct tagBFD_PACKET_HEAD_BAK
{
    USHORT usType;           /* 备份消息块类型 */
    USHORT usLen;            /* 备份消息块的总长度 */
    ULONG ulSessionID;       /* 配置块所属的会话索引 */
    ULONG ulExtend;          /* 扩展字段 */
} BFD_PACKET_HEAD_BAK_S;

/* BFD报文强制部分数据结构 */
typedef struct tagBFD_PACKET_BAK
{
#if ( VRP_BIG_ENDIAN == VRP_YES )
    UCHAR   bVers                   : 3 ;       /* BFD的版本信息 */
    UCHAR   bDiagnostic             : 5 ;       /* BFD的诊断信息 */
#else
    UCHAR   bDiagnostic             : 5 ;       /* BFD的诊断信息 */
    UCHAR   bVers                   : 3 ;       /* BFD的版本信息 */
#endif
#if ( VRP_BIG_ENDIAN == VRP_YES )
    UCHAR   bState                  : 2 ;       /* BFD的状态信息 */
    UCHAR   bPollFlag               : 1 ;       /* BFD的轮询标志 */
    UCHAR   bFinalFlag              : 1 ;       /* BFD的轮询回应标志 */
    UCHAR   bControlPlanFlag        : 1 ;       /* BFD和控制平面共存的标志 */
    UCHAR   bAuthenticationFlag     : 1 ;       /* BFD的认证标志 */
    UCHAR   bDemandModeFlag         : 1 ;       /* BFD的查询方式标志 */
    UCHAR   bReserved               : 1 ;       /* BFD的保留位 */ 
#else
    UCHAR   bReserved               : 1 ;       /* BFD的保留位 */ 
    UCHAR   bDemandModeFlag         : 1 ;       /* BFD的查询方式标志 */
    UCHAR   bAuthenticationFlag     : 1 ;       /* BFD的认证标志 */
    UCHAR   bControlPlanFlag        : 1 ;       /* BFD和控制平面共存的标志 */
    UCHAR   bFinalFlag              : 1 ;       /* BFD的轮询回应标志 */
    UCHAR   bPollFlag               : 1 ;       /* BFD的轮询标志 */
    UCHAR   bState                  : 2 ;       /* BFD的状态信息 */
#endif
    UCHAR   ucDetectMult                ;       /* BFD的检测倍数 */ 
    UCHAR   ucPacketLength              ;       /* BFD的报文长度 */ 
    ULONG   ulLocalDiscriminitor        ;       /* BFD的本地标识符 */
    ULONG   ulRemoteDiscriminitor       ;       /* BFD的对端标识符 */
    ULONG   ulDesiredMinTxInterval      ;       /* BFD期望的发送间隔 */ 
    ULONG   ulRequiredMinRxInterval     ;       /* BFD的本地接收能力 */ 
    ULONG   ulRequiredMinEchoRxInterval ;       /* BFD回声功能的发送间隔 */ 
} BFD_PACKET_BAK_S;


typedef struct tagBFD_REC_PACKET_BAK
{
    USHORT usType;           /* 备份消息块类型 */
    USHORT usLen;            /* 备份消息块的总长度 */
    ULONG ulSessionID;       /* 配置块所属的接口索引 */
    BFD_PACKET_BAK_S stPacket;   /* 收到的报文字段 */
} BFD_REC_PACKET_BAK_S;

typedef struct tagBFD_VRF_REC_PACKET_BAK
{
    USHORT usType;           /* 备份消息块类型 */
    USHORT usLen;            /* 备份消息块的总长度 */
    ULONG  ulSessionID;       /* 配置块所属的接口索引 */
    ULONG  ulVrfIndex;
    BFD_PACKET_BAK_S stPacket;   /* 收到的报文字段 */
} BFD_VRF_REC_PACKET_BAK_S;

/* 会话更新参数数据结构 */
typedef struct tagBFD_SESSION_PARA_BAK
{
    ULONG ulDetectMode;      /* 会话检测模式:1查询模式;2异步模式 */
    ULONG ulMinTxInterval;   /* ms,最小发送时间间隔：10~1000ms */
    ULONG ulMinRxInterval;   /* ms,最小接收时间间隔：10~1000ms */
    ULONG ulDetectMult;      /* 检测倍数：3~50 */
}BFD_SESSION_PARA_BAK_S;

typedef struct tagBFD_CFG_PACKET_HEAD_BAK
{
    USHORT usType;                    /* 备份消息块类型 */
    USHORT usLen;                     /* 备份消息块的总长度 */
    ULONG ulSessionID;                /* 配置块所属的接口索引 */
    BFD_SESSION_PARA_BAK_S stSessionPara; /* 会话参数 */
} BFD_CFG_PACKET_HEAD_BAK_S;

typedef struct tagBFD_VRF_CFG_PACKET_HEAD_BAK
{
    USHORT usType;                    /* 备份消息块类型 */
    USHORT usLen;                     /* 备份消息块的总长度 */
    ULONG  ulSessionID;               /* 配置块所属的接口索引 */
    ULONG  ulVrfIndex;                /* VRF索引 */
    BFD_SESSION_PARA_BAK_S stSessionPara; /* 会话参数 */
} BFD_VRF_CFG_PACKET_HEAD_BAK_S;


/* 备份bfd会话的tos */
typedef struct tagBFD_SESSION_TOS_BAK
{
    USHORT usType;                    /* 备份消息块类型 */
    USHORT usLen;                     /* 备份消息块的总长度 */
    ULONG  ulSessionID;               /* 配置块所属的BFD会话ID */
    UCHAR  ucTos;                     /* bfd会话tos */
    UCHAR  Padding[3];
    ULONG  ulVrfIndex;             
}BFD_SESSION_TOS_BAK_S;

/* Begin:Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 创建会话的协议类型备份包 */   
/* 备份bfd会话的协议类型，1:RFC协议 0:草案04*/
typedef struct tagBFD_SESSION_BFDPROTOCOL_BAK
{
    USHORT usType;                    /* 备份消息块类型 */
    USHORT usLen;                     /* 备份消息块的总长度 */
    ULONG  ulSessionID;               /* 配置块所属的BFD会话ID */
    ULONG  ulVrfIndex;                /* VRF索引 */
    ULONG  ulBfdProtocol;             /* bfd会话协议类型 */
}BFD_SESSION_BFDPROTOCOL_BAK_S;
/* End:Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 创建会话的协议类型备份包 */   

/* Begin:Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 会话的对端RequiredMinRxInterval备份包 */   
/* 备份bfd会话的协议类型，1:RFC协议 0:草案04*/
typedef struct tagBFD_SESSION_REMOTEMRI_BAK
{
    USHORT usType;                    /* 备份消息块类型 */
    USHORT usLen;                     /* 备份消息块的总长度 */
    ULONG  ulSessionID;               /* 配置块所属的BFD会话ID */
    ULONG  ulVrfIndex;                /* VRF索引 */
    ULONG  ulRemoteMinRxInterval;     /* 对端的RequiredMinRxInterval值 */
}BFD_SESSION_REMOTEMRI_BAK_S;
/* End:Add for V2R3C05, by b0177000/y00176567, at 2011-06-03. 修改原因: V2R3C05 创建会话的协议类型备份包 */  

/* Begin:Add for V2R3C05, by b0177000/y00176567, at 2011-06-05. 修改原因: V2R3C05 会话的对端RequiredMinRxInterval备份包 */   
/* 备份bfd会话对端的DemandMode值*/
typedef struct tagBFD_SESSION_REMOTE_DEMANDMODE_BAK
{
    USHORT usType;                    /* 备份消息块类型 */
    USHORT usLen;                     /* 备份消息块的总长度 */
    ULONG  ulSessionID;               /* 配置块所属的BFD会话ID */
    ULONG  ulVrfIndex;                /* VRF索引 */
    USHORT usRemoteDemandMode;        /* 对端的DemandMode值 */
    USHORT usReserved;                /* 四字节对齐，保留不用 */
}BFD_SESSION_REMOTE_DEMANDMODE_BAK_S;
/* End:Add for V2R3C05, by b0177000/y00176567, at 2011-06-05. 修改原因: V2R3C05 创建会话的协议类型备份包 */ 

typedef struct tagBFD_CREATE_SESSION_BAK
{
    USHORT  usType;                /* 备份消息块类型 */
    USHORT  usLen;                 /* 备份消息块的总长度 */
    ULONG   ulSessId;              /* 会话ID */
    ULONG   ulDstIP;               /* 目的地址(网络序) */
    ULONG   ulSrcIP;               /* 源地址(网络序) */
    ULONG   ulOutIfIndex;          /* 出接口 */
}BFD_CREATE_SESSION_BAK_S;

typedef struct tagBFD_CREATE_VRF_SESSION_BAK
{
    USHORT  usType;                /* 备份消息块类型 */
    USHORT  usLen;                 /* 备份消息块的总长度 */
    ULONG   ulSessId;              /* 会话ID */
    ULONG   pulDstIP[4];               /* 目的地址(网络序) */
    ULONG   pulSrcIP[4];               /* 源地址(网络序) */
    ULONG   ulOutIfIndex;          /* 出接口 */
    ULONG   ulIpVer;
    ULONG   ulVrfIndex;            /* 会话所属得VPN*/
}BFD_CREATE_VRF_SESSION_BAK_S;

typedef struct tagBFD_DELETE_VRF_SESSION_BAK
{
    USHORT  usType;                /* 备份消息块类型 */
    USHORT  usLen;                 /* 备份消息块的总长度 */
    ULONG   ulSessId;              /* 会话ID */
    ULONG   ulVrfIndex;            /* 会话所属得VPN*/
}BFD_DELETE_VRF_SESSION_BAK_S;

typedef struct tagBFD_SESSION_CFG_HA_BAK
{
    ULONG   ulBfdType                             ;              /* BFD绑定的类型 */
    ULONG   ulPeerAddrType                        ;              /* BFD绑定的地址类型 */
    ULONG   ulSrcAddr[4]                          ;              /* IPv4、IPv6地址,网络序 */
    ULONG   ulPeerAddr[4]                         ;              /* IPv4、IPv6地址,网络序 */
    ULONG   ulIfIndex                             ;              /* BFD指定的出接口索引 */
    ULONG   ulVrfIndex                            ;              /* BFD's Vpn index*/
    ULONG   ulVlanId                              ;              /* BFD指定的VlanId（在是以太网接口时用户可选） */
    BOOL_T  bDemand                               ;
    BOOL_T  bEcho                                 ;
    ULONG   ulDemandTimerInterval                 ;              /* BFD查询模式下定时查询的间隔 */ 
    ULONG   ulDetectMult                          ;              /* BFD的本地检测倍数 */ 
    ULONG   ulMinTxInterval                       ;              /* BFD期望的发送间隔 */ 
    ULONG   ulMinRxInterval                       ;              /* BFD的本地接收能力 */ 
    ULONG   ulMinEchoTxInterval                   ;              /* BFD会话本地回声功能的接收能力(不支持Echo,此值必须为0) */ 
    ULONG   ulMinEchoRxInterval                   ;              /* BFD回声功能的发送间隔(不支持Echo,此值必须为0)*/ 
    ULONG   ulWtrTimeInterval                     ;              /* Time for wtr. millisecond */
    USHORT  usAuthMode                            ;              /* BFD的认证方式 */ 
    UCHAR   ucAuthKeyId                           ;              /* BFD配置的认证KeyId */ 
    UCHAR   ucAuthPwd[BFD_LEN_MAX_SIMPLE_PWD + 1] ;              /* BFD配置的认证pwd */
}BFD_SESSION_CFG_HA_BAK_S;

/* 会话实际的运行信息 size 13*4字节*/
typedef struct tagBFD_SESS_RUN_ENTRY_BAK
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
    ULONG   ulActEchoTxInterval       ;              /* BFD会话本地回声功能的实际发送能力 */ 
    ULONG   ulActEchoRxInterval       ;              /* BFD回声功能的实际接收间隔 */ 
    ULONG   ulRcvAuthSeq              ;              /* 接收到序列号 */
    ULONG   ulXmitAuthSeq             ;              /* 发送的序列号对于MD5和SHA1 */
    BOOL_T  bAuthSeqKnown             ;              /* 接收的序列号是否可知 */
    BOOL_T  bPollFlag                 ;              /* 是否发送轮询报文 */
    USHORT  usLocalDiag               ;              /* 本地诊断字段 */
    USHORT  usSessState               ;              /* 会话的当前状态 */
} BFD_SESS_RUN_ENTRY_BAK_S;

typedef struct tagBFD_SESSION_BAK
{
    USHORT  usType;                               /* 备份消息块类型 */
    USHORT  usLen;                                /* 备份消息块的总长度 */
    ULONG   ulSessId;                             /* 会话ID */
    ULONG   ulAppId;                              /* 应用关联标记 */
    BFD_SESSION_CFG_HA_BAK_S  stSessCfgEntry;     /* 会话配置块 */
    BFD_SESS_RUN_ENTRY_BAK_S  stSessRunEntry;    /* BFD实际的信息 */
}BFD_SESSION_BAK_S;

/* SESSION Down信息的备份 */
typedef struct tagBFD_DIG_DOWN_BAK
{
    USHORT usType;           /* 备份消息块类型 */
    USHORT usLen;            /* 备份消息块的总长度 */
    ULONG  ulSessionID;      /* 配置块所属的会话索引 */
    ULONG  ulVrfIndex;       /* VRF索引 */
    ULONG  ulDigDown;        /* Session down的类型 */
}BFD_DIG_DOWN_BAK_S;

/* SESSION 应用组信息的备份 */
typedef struct tagBFD_APPGROUP_BAK
{
    USHORT usType;           /* 备份消息块类型 */
    USHORT usLen;            /* 备份消息块的总长度 */
    ULONG  ulSessionID;      /* 配置块所属的会话索引 */
    ULONG  ulVrfIndex;       /* VRF索引 */
    ULONG  ulAppGroup;       /* Session 应用组信息 */
}BFD_APPGROUP_BAK_S;

typedef struct tagBFD_SETSINGAPPS_BAK
{
    USHORT usType;           /* 备份消息块类型 */
    USHORT usLen;            /* 备份消息块的总长度 */
    ULONG  ulSessionID;      /* 配置块所属的会话索引 */
    ULONG  ulVrfIndex;       /* VRF索引 */
    ULONG  ulAppID;
} BFD_SETSINGAPPS_BAK_S;

typedef struct tagBFD_MULTIHOP_PORT_BAK
{
    USHORT usType;           /* 备份消息块类型 */
    USHORT usLen;            /* 备份消息块的总长度 */
    ULONG  ulSessionID;      /* 配置块所属的会话索引 */
    ULONG  ulVrfIndex;       /* VRF索引 */
    ULONG  ulPort;           /* 多跳UDP端口号 */
} BFD_MULTIHOP_PORT_BAK_S;

typedef struct tagBFD_SESSION_NAME_BAK
{
    USHORT usType;           /* 备份消息块类型 */
    USHORT usLen;            /* 备份消息块的总长度 */
    ULONG  ulSessionID;      /* 配置块所属的会话索引 */
    ULONG  ulVrfIndex;       /* VRF索引 */
    UCHAR  szCfgName[BFD_MAX_SESS_NAME_LEN + 1];
} BFD_SESSION_NAME_S;

typedef struct tagBFD_SESSION_DESC_BAK
{
    USHORT usType;           /* 备份消息块类型 */
    USHORT usLen;            /* 备份消息块的总长度 */
    ULONG  ulSessionID;      /* 配置块所属的会话索引 */
    ULONG  ulVrfIndex;       /* VRF索引 */
    UCHAR  szSessionDes[BFD_MAX_DESC_NAME_LEN + 1];
} BFD_SESSION_DESC_S;

#define BFD_HA_PACKET_COPY(PACKET_TO, PACKET_FROM)\
{\
    PACKET_TO.bVers = PACKET_FROM.bVers;\
    PACKET_TO.bDiagnostic = PACKET_FROM.bDiagnostic;\
    PACKET_TO.bState = PACKET_FROM.bState;\
    PACKET_TO.bPollFlag = PACKET_FROM.bPollFlag;\
    PACKET_TO.bFinalFlag = PACKET_FROM.bFinalFlag;\
    PACKET_TO.bControlPlanFlag = PACKET_FROM.bControlPlanFlag;\
    PACKET_TO.bAuthenticationFlag = PACKET_FROM.bAuthenticationFlag;\
    PACKET_TO.bDemandModeFlag = PACKET_FROM.bDemandModeFlag;\
    PACKET_TO.bReserved = PACKET_FROM.bReserved;\
    PACKET_TO.ucDetectMult = PACKET_FROM.ucDetectMult;\
    PACKET_TO.ucPacketLength = PACKET_FROM.ucPacketLength;\
    PACKET_TO.ulLocalDiscriminitor = PACKET_FROM.ulLocalDiscriminitor;\
    PACKET_TO.ulRemoteDiscriminitor = PACKET_FROM.ulRemoteDiscriminitor;\
    PACKET_TO.ulDesiredMinTxInterval = PACKET_FROM.ulDesiredMinTxInterval;\
    PACKET_TO.ulRequiredMinRxInterval = PACKET_FROM.ulRequiredMinRxInterval;\
    PACKET_TO.ulRequiredMinEchoRxInterval = PACKET_FROM.ulRequiredMinEchoRxInterval;\
}

#define BFD_HA_SESSION_PARA_COPY(SESSION_TO, SESSION_FROM)\
{\
    SESSION_TO.ulDetectMode = SESSION_FROM.ulDetectMode;\
    SESSION_TO.ulMinTxInterval = SESSION_FROM.ulMinTxInterval;\
    SESSION_TO.ulMinRxInterval = SESSION_FROM.ulMinRxInterval;\
    SESSION_TO.ulDetectMult = SESSION_FROM.ulDetectMult;\
}

#define BFD_HA_SESS_RUN_ENTRY_COPY(ENTRY_TO, ENTRY_FROM)\
{\
    ENTRY_TO.ulLocalDiscr = ENTRY_FROM.ulLocalDiscr;\
    ENTRY_TO.ulRemoteDiscr = ENTRY_FROM.ulRemoteDiscr;\
    ENTRY_TO.usUdpSrcPort = ENTRY_FROM.usUdpSrcPort;\
    ENTRY_TO.usUdpDstPort = ENTRY_FROM.usUdpDstPort;\
    ENTRY_TO.usDetectMode = ENTRY_FROM.usDetectMode;\
    ENTRY_TO.usIsMultiHop = ENTRY_FROM.usIsMultiHop;\
    ENTRY_TO.ulActTxInterval = ENTRY_FROM.ulActTxInterval;\
    ENTRY_TO.ulActRxInterval = ENTRY_FROM.ulActRxInterval;\
    ENTRY_TO.ulDetectTime = ENTRY_FROM.ulDetectTime;\
    ENTRY_TO.ulActEchoTxInterval = ENTRY_FROM.ulActEchoTxInterval;\
    ENTRY_TO.ulActEchoRxInterval = ENTRY_FROM.ulActEchoRxInterval;\
    ENTRY_TO.ulRcvAuthSeq = ENTRY_FROM.ulRcvAuthSeq;\
    ENTRY_TO.ulXmitAuthSeq = ENTRY_FROM.ulXmitAuthSeq;\
    ENTRY_TO.bAuthSeqKnown = ENTRY_FROM.bAuthSeqKnown;\
    ENTRY_TO.bPollFlag = ENTRY_FROM.bPollFlag;\
    ENTRY_TO.usLocalDiag = ENTRY_FROM.usLocalDiag;\
    ENTRY_TO.usSessState = ENTRY_FROM.usSessState;\
}


/* 赋值BFD会话消息 */
#define HA_SESSION_CFG_HA_PACK(stSESSION_CFG_TO, stSESSION_CFG_FROM) \
{\
    stSESSION_CFG_TO.ulBfdType = stSESSION_CFG_FROM.ulBfdType;\
    stSESSION_CFG_TO.ulPeerAddrType = stSESSION_CFG_FROM.ulPeerAddrType;\
    (VOID)TCPIP_Mem_Copy(stSESSION_CFG_TO.ulSrcAddr, sizeof(ULONG) * 4, stSESSION_CFG_FROM.ulSrcAddr, sizeof(ULONG) * 4);\
    (VOID)TCPIP_Mem_Copy(stSESSION_CFG_TO.ulPeerAddr, sizeof(ULONG) * 4, stSESSION_CFG_FROM.ulPeerAddr, sizeof(ULONG) * 4);\
    stSESSION_CFG_TO.ulIfIndex = stSESSION_CFG_FROM.ulIfIndex;\
    stSESSION_CFG_TO.ulVrfIndex = stSESSION_CFG_FROM.ulVrfIndex;\
    stSESSION_CFG_TO.ulVlanId = stSESSION_CFG_FROM.ulVlanId;\
    stSESSION_CFG_TO.bDemand = stSESSION_CFG_FROM.bDemand;\
    stSESSION_CFG_TO.bEcho = stSESSION_CFG_FROM.bEcho;\
    stSESSION_CFG_TO.ulDemandTimerInterval = stSESSION_CFG_FROM.ulDemandTimerInterval;\
    stSESSION_CFG_TO.ulDetectMult = stSESSION_CFG_FROM.ulDetectMult;\
    stSESSION_CFG_TO.ulMinTxInterval = stSESSION_CFG_FROM.ulMinTxInterval;\
    stSESSION_CFG_TO.ulMinRxInterval = stSESSION_CFG_FROM.ulMinRxInterval;\
    stSESSION_CFG_TO.ulMinEchoTxInterval = stSESSION_CFG_FROM.ulMinEchoTxInterval;\
    stSESSION_CFG_TO.ulMinEchoRxInterval = stSESSION_CFG_FROM.ulMinEchoRxInterval;\
    stSESSION_CFG_TO.ulWtrTimeInterval = stSESSION_CFG_FROM.ulWtrTimeInterval;\
    stSESSION_CFG_TO.usAuthMode = stSESSION_CFG_FROM.usAuthMode;\
    stSESSION_CFG_TO.ucAuthKeyId = stSESSION_CFG_FROM.ucAuthKeyId;\
    (VOID)TCPIP_Mem_Copy(stSESSION_CFG_TO.ucAuthPwd, BFD_LEN_MAX_SIMPLE_PWD + 1, stSESSION_CFG_FROM.ucAuthPwd, BFD_LEN_MAX_SIMPLE_PWD + 1);\
}

ULONG BFD_HA_BatchBackup(VOID);
ULONG BFD_HA_BuildOnePacket(USHORT usType, ULONG ulSessionId, VOID * pucData, VOID *pucInBuf, USHORT usInBufLen);
ULONG BFD_HA_BuildSendOnePacket(USHORT usType, ULONG ulSessionId, VOID * pucData, USHORT usInBufLen);
ULONG BFD_HA_BatchBackupSendPacket (UCHAR * pucData, USHORT usDataLen, ULONG ulCount);
ULONG BFD_HA_SendPacket(UCHAR * pucData, USHORT usDataLen);
ULONG BFD_HA_Input(UCHAR * pucBuf, ULONG ulMsgLen);
ULONG BFD_HA_CopyTOSession(BFD_SESSION_BAK_S *pstBfdSessionBak);
ULONG BFD_HA_Smooth(VOID);
ULONG BFD_HA_SmoothOneSession(BFD_SESS_ENTRY_S *pstSession);
ULONG BFD_HA_CanSendPacket(VOID);
ULONG BFD_HA_CannotCfg(VOID);
ULONG BFD_HA_GetDbgSwitch(VOID);
VOID BFD_HA_Register();
VOID BFD_HA_DebugOutPut(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);
ULONG BFD_HA_SetBfdVerboseDbg(ULONG ulDbg);
ULONG BFD_HA_GetBfdVerboseDbg(ULONG *pulDbg);
ULONG BFD_HA_Clean(VOID);

#ifdef  __cplusplus
}
#endif

#endif

