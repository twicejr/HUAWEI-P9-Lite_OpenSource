/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipsfe_msg.h
*
*  Project Code: VISPV100R008C02
*   Module Name: ipsfe_msg 
*  Date Created: 2009-8-21
*        Author: zhangchunyu(62474)
*   Description: 数据面和控制面公用头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                      DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-7-28  zhangchunyu(62474)         Create the first version.
*
*******************************************************************************/
#ifndef _IPSFE_MSG_H_
#define _IPSFE_MSG_H_

#ifdef __cplusplus
    extern "C"{
#endif

/* 控制面发往数据面消息类型,对应MSG_HEADER中u16MsgType字段,修改该定义时,
   请注意修改g_ai8TCPIPSFE_MsgTypeInfo和g_ai8SFE_MsgTypeInfo字符数组信息 */
enum enMsgType
{
    MSG_TYPE_NPCFG,     /* NP PPI下发类型 */
    MSG_TYPE_NP_TABLE,  /* 获取POOL资源池信息 */
    MSG_TYPE_NP_NPPI,   /* 非PPI类消息类型 */
    
    MSG_TYPE_NP_MAX,    /* MAX */
};

/* 控制面发往数据面模块类型,对应MSG_ITEM_HEADER_S中u8MoudleID字段,
   修改增删模块ID时,需要修改增删对应的g_SfeDispatchMsg和g_SfeNPpiDispatchMsg分发处理数组
   修改g_ai8TCPIPSFE_ModuleTypeInfo和g_ai8SFE_ModuleTypeInfo对应字符数组信息*/
enum enMoudleType
{
    MOUDLE_TYPE_IFNET,
    MOUDLE_TYPE_ROUTE,
    MOUDLE_TYPE_ARP,
    MOUDLE_TYPE_BFD,
    MOUDLE_TYPE_ICMP,
    MOUDLE_TYPE_ACL,
    MOUDLE_TYPE_IP,
    MOUDLE_TYPE_DEBUG,
    MOUDLE_TYPE_PUB,
    MOUDLE_TYPE_MAX,
};

/* 控制面到数据面表操作类型 */
enum enSfeTableOpType
{  
    SFE_TABLE_OPEN,
    SFE_TABLE_GET_DATA,
    SFE_TABLE_CLOSE,
    SFE_TABLE_OP_MAX,    
};

/* 数据面发往控制面消息类型,对应MSG_HEADER中u16MsgType字段 */
enum enSfeToCtlMsgType
{
    SFE_MSG_EVENT,
    SFE_MSG_NP_ACK,
};

/* 数据面发往控制面模块类型,对应MSG_ITEM_HEADER_S中u8MoudleID字段 */
enum enSfeToCtlMoudleType
{
    SFE_ARP_MOUDLE,
    SFE_BFD_MOUDLE,
    SFE_MAX_MOUDLE,
};

/* 数据面到控制面操作类型,修改该定义时,
   请注意修改g_ai8TCPIPSFE_EventTypeInfo和g_ai8SFE_EventTypeInfo字符数组信息 */
enum enOpTypeCtl
{  
    SFE_ARP_MISS_EVENT,             /* ARP MISS通知 */
    SFE_BFD_DETECT_DOWN_EVENT,      /* BFD探测到会话DOWN通知 */
    
    SFE_MAX_EVENT,                  /* 数据面上报事件消息类型边界无效值 */
};

/* NPPI(非PPI)消息类型下的操作命令字 */
enum enSfeNPpiType
{
    /* ARP处理命令字 */
    SFE_NPPI_ARP_GET,                       /* 指定ID获取ARP信息 */
    SFE_NPPI_ARP_SHOWALLARPINFO,            /* 显示所有ARP表项 */
    SFE_NPPI_ARP_SHOWARPINFOBYVRF,          /* 根据VRF显示ARP */
    SFE_NPPI_ARP_SHOW_ONEARPINFO,           /* 根据VRF和IP显示ARP */

    /* 接口处理命令字 */
    SFE_NPPI_IF_GET,                        /* 指定ID获取接口信息 */
    SFE_NPPI_IF_SET_ETH_ARPMISSSWITCH,      /* 设置以太接口的ARP MISS开关 */
    SFE_NPPI_IF_SET_REDUCETTLSWITCH,        /* 设置接口TTL是否减一开关 */
    SFE_NPPI_IF_SHOWALLIFINFO,              /* 显示所有接口信息 */
    SFE_NPPI_IF_SHOWBYID,                   /* 根据接口ID显示接口信息 */

    /* ROUTE处理命令字 */
    SFE_NPPI_ROUTE_GET,                     /* 指定获取路由信息 */
    SFE_NPPI_ROUTE_SHOWALLINFO,             /* 显示所有路由信息 */
    SFE_NPPI_ROUTE_SHOWBYIP,                /* 显示指定IP路由信息 */

    /* BFD处理命令字 */
    SFE_NPPI_BFD_GET,                       /* 指定ID获取BFD会话信息 */
    SFE_NPPI_BFD_SET_DEBUG_SWITCH,          /* 设置基于BFD的调试开关 */
    SFE_NPPI_BFD_GET_DEBUG_SWITCH,          /* 获取基于BFD的调试开关 */
    SFE_NPPI_BFD_SHOWALLBFDINFO,            /* 显示所有BFD信息*/
    SFE_NPPI_BFD_SHOWBFDINFO_BYVRF,         /* 显示指定VRF下的所有BFD会话信息 */
    SFE_NPPI_BFD_SHOWBFDINFO_BYID,          /* 显示指定VRF会话ID的BFD会话信息 */
    SFE_NPPI_BFD_CLEAR_STATISTIC,           /* 清0指定BFD会话的统计信息 */
    SFE_NPPI_BFD_GET_STATISTIC,             /* 获取指定BFD会话的统计信息 */
    SFE_NPPI_BFD_SHOW_STATISTIC,            /* 显示指定BFD会话的统计信息 */
    
    
    /* ICMP处理命令字 */
    SFE_NPPI_ICMP_SETSWITCH,                /* 设置ICMP差错报文调试开关 */
    SFE_NPPI_ICMP_GETSWITCH,                /* 获取ICMP差错报文调试开关 */
    
    /* IP处理命令字 */
    SFE_NPPI_IP_SETRTID,                    /* 设置Router ID */
    SFE_NPPI_IP_GETRTID,                    /* 获取Router ID */

    /* 统计处理命令字 */
    SFE_NPPI_STAT_GET_ALLINFO,              /* 获取全局统计所有相关信息,包括存储统计相关信息的地址 */    
    SFE_NPPI_STAT_SHOW_ALLSTAT,             /* 显示所有总的全局统计信息 */
    SFE_NPPI_STAT_SHOW_AUTOSTAT,            /* 显示全局自动统计信息 */
    SFE_NPPI_STAT_SHOW_MANUALSTAT,          /* 显示全局各VCPU手动统计信息之和,即总的手动统计信息 */
    SFE_NPPI_STAT_SHOW_MANUALSTATBYVCPU,    /* 显示指定VCPU的全局手动统计信息 */
    SFE_NPPI_STAT_CLEAR_ALLSTAT,            /* 清除所有全局统计信息 */

    /* 流统计处理命令字 */
    SFE_NPPI_FLOWSTAT_SET_SWITCH,           /* 设置流统计开关 */
    SFE_NPPI_FLOWSTAT_GET_SWITCH,           /* 获取流统计开关 */
    SFE_NPPI_FLOWSTAT_SHOW_SWITCH,          /* 显示流统计开关 */
    SFE_NPPI_FLOWSTAT_CFG_FLOWRULE,         /* 配置流统计规则 */
    SFE_NPPI_FLOWSTAT_GET_RULENUM,          /* 获取流规则总数 */
    SFE_NPPI_FLOWSTAT_GET_ALLINFO,          /* 获取流统计所有相关信息,包括存储流统计相关信息的地址 */

    SFE_NPPI_FLOWSTAT_SHOW_ALLRULE,         /* 显示所有流统计规则 */    
    SFE_NPPI_FLOWSTAT_SHOW_RULE_BYFLOWID,   /* 显示指定流ID的流统计规则 */
    
    SFE_NPPI_FLOWSTAT_SHOW_ALLSTAT,         /* 显示所有流统计信息 */    
    SFE_NPPI_FLOWSTAT_SHOW_STAT_BYRULE,     /* 显示指定规则的流统计信息 */
    SFE_NPPI_FLOWSTAT_SHOW_STAT_BYFLOWID,   /* 显示指定流ID的流统计信息 */

    SFE_NPPI_FLOWSTAT_CLEAR_ALLSTAT,        /* 清除所有流统计信息 */
    

    /* 调试处理命令字 */
    SFE_NPPI_DEBUG_SET_DEBUGTYPE,           /* 设置Debug类型开关 */
    SFE_NPPI_DEBUG_SET_DEBUGVCPU,           /* 设置vcpu Debug类型开关 */
    SFE_NPPI_DEBUG_SET_DEBUGMODU,           /* 设置模块Debug开关 */
    SFE_NPPI_DEBUG_GET_DEBUGSWITCH,         /* 获取Debug开关 */
    SFE_NPPI_DEBUG_SETMSGOREVT_DEBUGSWITCH, /* 设置消息或事件调试开关 */
    SFE_NPPI_DEBUG_GETMSGOREVT_DEBUGSWITCH, /* 获取消息或事件调试开关 */
    SFE_NPPI_DEBUG_SETVERBOSE_DEBUG,        /* 设置详细调试的报文次数及报文长度 */
    SFE_NPPI_DEBUG_GETVERBOSE_DEBUG,        /* 获取详细调试的报文次数及报文长度 */
    SFE_NPPI_DEBUG_SHOW_DEBUGSWITCH,        /* 显示调试开关信息 */

    /* 日志处理 */
    SFE_NPPI_LOG_SET_LOGLEVEL,              /* 设置日志级别 */
    SFE_NPPI_LOG_SET_LOGTYPE,               /* 设置日志类型 */
    SFE_NPPI_LOG_SHOW_LOGSWITCH,            /* 显示日志开关 */

    /* 其它公共处理 */
    SFE_NPPI_PUB_SHOW_VERSION,              /* 显示数据面版本号 */
    SFE_NPPI_PUB_SHOW_PRECONFIG,            /* 显示数据面预配置信息 */
    SFE_NPPI_PUB_SHOW_SHAREMEMID,           /* 显示数据面共享内存ID信息 */
    SFE_NPPI_PUB_SHOW_STUBMODULE,           /* 显示数据面模块裁减情况 */
    SFE_NPPI_PUB_SET_ACLFAKEREASS,          /* 设置ACL处理是否需要数据面进行假重组开关 */
    SFE_NPPI_PUB_GET_ACLFAKEREASS,          /* 获取ACL处理是否需要数据面进行假重组开关 */
    SFE_NPPI_PUB_SHOW_ACLFAKEREASS,         /* 显示ACL处理是否需要数据面进行假重组开关 */
    SFE_NPPI_PUB_SHOW_MSGSEQ,               /* 显示数据面消息序号 */
    SFE_NPPI_PUB_SET_OUTPUT_TOCOM,          /* 设置数据面输出到com口的开关 */
    
};

/* 消息包公共头大小 */
#define TCPIP_SFE_MSG_HEADER_LEN   (sizeof(MSG_HEADER) + sizeof(MSG_ITEM_HEADER_S))

/* 打包消息头 */
#define SET_MSG_HEAD(pstMsgHdr,u16MsgTypeH,u16MsgLenH,u32SeqH,u8OriginH)\
{\
    (pstMsgHdr)->u16MsgType = (u16MsgTypeH);\
    (pstMsgHdr)->u16MsgLen  = (u16MsgLenH);\
    (pstMsgHdr)->u32Ver     = 0;\
    (pstMsgHdr)->u32Seq     = (u32SeqH);\
    (pstMsgHdr)->u8Pri      = 0;\
    (pstMsgHdr)->u8Origin   = (u8OriginH);\
    (pstMsgHdr)->u16Chksum  = 0;\
}

/* 打包子消息头 */
#define SET_MSG_ITEMHDR(pstItem,u8MoudleIDH,u8OperTypeH,u16ItemLenH)\
{\
    (pstItem)->u8MoudleID = (u8MoudleIDH);\
    (pstItem)->u8OperType = (u8OperTypeH);\
    (pstItem)->u16ItemLen = (u16ItemLenH);\
}

/* 数据面和控制面通信消息公共头 */
typedef struct tagMsgHead
{
    UINT16   u16MsgType;             /* 消息类型 */
    UINT16   u16MsgLen;              /* 消息总长度 */
    UINT32   u32Ver;                 /* SFE版本号 */
    UINT32   u32Seq;                 /* SFE备份消息编号 */
    UINT8    u8Pri;                  /* 优先级 */
    UINT8    u8Origin;               /* 数据来源 */
    UINT16   u16Chksum;              /* 校验和, 缺省为0 */
}MSG_HEADER;

/* 数据面和控制面TL, 后面接着数据是V */
typedef struct tagItem
{
    UINT8   u8MoudleID;              /* 模块ID */
    UINT8   u8OperType ;             /* 操作类型 */
    UINT16  u16ItemLen;              /* 消息长度 */
}MSG_ITEM_HEADER_S;

/* 控制面发往数据面OPEN TABLE组包数据结构 */
typedef struct tagSfeOpen
{
    UINT32 u32TableType;
    UINT32 u32VrfIndex;
}TCPIP_SFE_OPEN_S;

/* 控制面回复OPEN TABLE组包数据结构 */
typedef struct tagSfeOpenRet
{
    UINT32 u32Ret;
    UINT32 u32Handle;
}SFE_OPEN_RET_S;

/* 控制面发往数据面GET TABLE DATA组包数据结构 */
typedef struct tagSfeGet
{
    UINT32 u32Handle;        
    UINT32 u32GetNum;
    UINT32 u32BufLen;
}TCPIP_SFE_GET_S;

/* 控制面回复GET TABLE DATA组包数据结构 */
typedef struct tagSfeGetRet
{
    UINT32 u32Ret;
    UINT32 u32Len;
    UINT32 u32Num;
}SFE_GET_RET_S;

/* 数据面对应的控制面PPI类型消息分发函数类型定义*/
typedef UINT32 (*MsgDispatchFuncPtr)(VOID *pstMsg);

/* 数据面对应的控制面非PPI类型消息分发函数类型定义*/
typedef UINT32 (*MsgNPpiDispatchFuncPtr)(VOID *pstMsg, UINT32 u32DataBufLen, CHAR *pDataBuf, UINT32 *pu32ActualDataLen);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

