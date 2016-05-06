/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_sfe_share_api.h
*
*  Project Code: V1.1.0
*   Module Name: API
*  Date Created: 2009-8-29
*        Author: w60786
*   Description: 控制面和数据面共用的对外ARI结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-8-29    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _TCPIP_SFE_SHARE_API_H_
#define _TCPIP_SFE_SHARE_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

#include "tcpip/public/tcpip_id.h"

/*******************************公共定义**********************************************************************/
#define SFE_ERRCODE_BEGIN      ( MID_COMP_PUBLIC + 0x8000 )

/* 数据面对应的控制面代码返回值全局唯一各模块错误码区段划分,为每个模块预留512个错误码,0x200
   注意数据面对应的控制面错误码取值范围是从控制面PUBLID模块分出来的后面一部分,
   分配错误码时注意不要越界.目前分配的错误码必须在以下区间:
   [(MID_COMP_PUBLIC + 0x8000), (MID_COMP_PUBLIC + 0xFFFF)] */
typedef enum enumTcpipSfeGlobalRetCode
{
    TCPIP_SFE_COM_BEGIN_RET_CODE = SFE_ERRCODE_BEGIN,                  /* MSG消息通讯模块错误码起始值 */
    TCPIP_SFE_TABLE_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0200),     /* POOL TABLE操作模块错误码起始值 */
    TCPIP_SFE_ARP_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0400),       /* ARP模块错误码起始值 */
    TCPIP_SFE_ROUTE_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0600),     /* ROUTE模块错误码起始值 */
    TCPIP_SFE_IF_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0800),        /* IF接口模块错误码起始值 */
    TCPIP_SFE_BFD_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0a00),       /* BFD消息通讯模块错误码起始值 */
    TCPIP_SFE_ICMP_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0c00),      /* ICMP模块错误码起始值 */
    TCPIP_SFE_IP_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0e00),        /* IP模块错误码起始值 */
    TCPIP_SFE_DEBUG_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x1000),     /* DEBUG维测模块错误码起始值*/
    TCPIP_SFE_PUB_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x1200),       /* PUB模块错误码起始值*/
}TCPIP_SFE_GLOBAL_RET_CODE_E;

/*******************************控制面到数据面消息通道相关宏,枚举,结构等定义**********************************/
/* 控制面通信错误码 */
enum enumCtlComCode
{
    TCPIP_SFE_COM_SUCCESS,                      /* 操作成功*/
    TCPIP_SFE_COM_ERR_BEGIN = TCPIP_SFE_COM_BEGIN_RET_CODE,/* 模块错误码起始值,建议内部不要使用该值 */
    TCPIP_SFE_COM_RCVMSG_LEN_ERR,               /* 通道传递报文长度和收到报文长度不一致 */
    TCPIP_SFE_COM_RCVMSG_LEN_SHORT,             /* 报文总长度非法 */
    TCPIP_SFE_COM_REG_MSGTOTSFE_NULL,           /* 注册控制面发往数据面消息钩子函数为空 */
    TCPIP_SFE_COM_REG_MSGFROMSFE_NULL,          /* 注册控制面接收数据面消息钩子函数为空 */
    TCPIP_SFE_COM_REG_ALLOC_NULL,               /* 注册分配内存钩子函数为空 */
    TCPIP_SFE_COM_REG_FREE_NULL,                /* 注册释放内存钩子函数为空 */
    TCPIP_SFE_RECV_MSG_NULL,                    /* 控制面接收消息通道报文为空 */
    TCPIP_SFE_RECV_MOUDLE_ERR,                  /* 控制面接收数据面消息中模块非法 */
    TCPIP_SFE_RECV_ITEM_LEN_ERR,                /* 控制面接收数据面消息中报文长度小于一个TLV */
    TCPIP_SFE_COM_ARPMISS_ITEMLEN_INVALID,      /* ARP MISS消息长度不合法 */

    TCPIP_SFE_MSG_PARA_INVALID,                 /* 参数不合法,接收的数据长度为0和接收缓冲区指针NULL必须配套使用 */
    TCPIP_SFE_MSG_SEND_PARA_INVALID,            /* 参数不合法,发送的数据长度为0和发送缓冲区指针NULL必须配套使用 */
    TCPIP_SFE_MSG_MEMALLOC_FUNC_NULL,           /* 控制面通道内存申请释放函数为NULL,未注册 */
    TCPIP_SFE_MSG_CHANNEL_FUNC_NULL,            /* 控制面与数据面的通道为NULL,未注册 */
    TCPIP_SFE_MSG_MEMALLOC_INPUT_NULL,          /* 申请通道内存时传入的指针都为NULL */
    TCPIP_SFE_MSG_MEMALLOC_SENDBUF_FAIL,        /* 申请发送缓冲区失败 */
    TCPIP_SFE_MSG_MEMALLOC_RCVBUF_FAIL,         /* 申请接收缓冲区失败 */
    TCPIP_SFE_MSG_CHANNEL_SEND_FAIL,            /* 控制面与数据面的通道发送数据到数据面失败 */
    TCPIP_SFE_MSG_CHANNEL_RCV_FAIL,             /* 控制面与数据面的通道从数据面接收数据接收失败 */
    TCPIP_SFE_MSG_RCVMSG_LEN_INVALID,           /* 接收的消息长度非法,小于最小消息长度 */
    TCPIP_SFE_MSG_RCVMSG_LENFIELD_INVALID,      /* 接收的消息中的消息长度字段非法,与接收消息长度不等 */
    TCPIP_SFE_MSG_RCVMSG_SEQ_INVALID,           /* 接收的消息中的消息序号字段非法,与发送消息序号不等 */
    TCPIP_SFE_MSG_RCVMSG_ITEMLEN_INVALID,       /* 子选项中的长度字段不非法,与接收的消息长度不协调 */
    TCPIP_SFE_MSG_RCVMSGLEN_NOTEXPECT,          /* 接收的消息长度非法,不等于期望的接收消息长度 */
    TCPIP_SFE_MSG_RCVMSG_DATALEN_NOTEXPECT,     /* 接收的数据长度不等于期望接收的数据长度 */
    TCPIP_SFE_MSG_RCVMSG_DATALEN_LESSTHAN4,     /* 接收的数据长度不合法,小于错误码4字节 */

    TCPIP_SFE_COM_BFDDETECTDOWN_ITEMLEN_INVALID,/* BFD探测DOWN消息长度不合法 */
    TCPIP_SFE_COM_EVENT_OPER_TYPE_INVALID,      /* 控制面收到的数据面EVNET类型消息中的操作命令字不合法 */

    TCPIP_SFE_COM_CHECKSUM_FAIL,                /* 通道消息校验和错误*/
    TCPIP_SFE_COM_CHECKSUM_EVENT_FAIL,          /* 事件消息的校验和错误*/
};

/*******************************IF接口相关宏,枚举,结构等定义**********************************/
/* 接口模块错误码 */
typedef enum enumCTLIFERRCODE
{
    TCPIP_SFE_IF_SUCCESS,           /* 操作成功 */
    TCPIP_SFE_IF_ERR_BEGIN = TCPIP_SFE_IF_BEGIN_RET_CODE,/* 模块错误码起始值,建议内部不要使用该值 */
    TCPIP_SFE_IF_NULL_POINTER,      /* 输入参数指针为空 */
    TCPIP_SFE_IF_COMREG_NULL,       /* 通道相关接口未注册 */
    TCPIP_SFE_IF_MALLOCFAIL,        /* 申请内存失败 */
    TCPIP_SFE_IF_ERROROPER,         /* 操作码错误 */
    TCPIP_SFE_IF_OVERMAXPORTTYPE,   /* 不存在的接口类型 */
    TCPIP_SFE_IF_ERRPORTTYPE,       /* 不支持此种接口类型 */
    TCPIP_SFE_IF_GETIFNETFAIL,      /* 获取IFNET信息失败 */
    TCPIP_SFE_IF_GETPORTINFOFAILFOR1DIM,/* 获取一维的接口ID失败 */
    TCPIP_SFE_IF_GETPORTINFOFAILFOR3DIM,/* 获取三维的接口ID失败 */
    TCPIP_SFE_IF_PARA_NULL_GET,     /* 指定接口ID获取接口信息时传入的参数为NULL */
    TCPIP_SFE_IF_IFID_POINTER_NULL_SETARPMISSSWITCH,   /* 设置接口ARP MISS功能时,传入的接口ID参数为NULL */
    TCPIP_SFE_IF_IFID_POINTER_NULL_SETREDUCETTLSWITCH, /* 设置接口Reduce TTL功能时,传入的接口ID参数为NULL */
    TCPIP_SFE_IF_ERRPORTTYPE_SFEPORT,       /* 不支持此种接口类型 */
    TCPIP_SFE_IF_ERRPORTTYPE_CONTROLPORT,       /* 不支持此种接口类型 */
}CTLIFERRCODE_E;

/* physical地址长度 */
#ifndef TCPIP_SFE_MAC_LEN
#define TCPIP_SFE_MAC_LEN 6
#endif

/* PPI下发端口类型 */
#define TCPIP_SFE_PORT_PPI     0
/* FABRIC端口 */
#define TCPIP_SFE_PORT_FABRIC  1
/* SPI4端口 */
#define TCPIP_SFE_PORT_SPI4    2

/* 接口物理状态UP */
#define TCPIP_SFE_PHY_STATUS_UP   1
/* 接口物理状态DOWN */
#define TCPIP_SFE_PHY_STATUS_DOWN 2

/* 接口IPV4协议状态UP */
#define TCPIP_SFE_LINE4_STATUS_UP   1
/* 接口IPV4协议状态DOWN */
#define TCPIP_SFE_LINE4_STATUS_DOWN 2

/* 接口IPV6协议状态UP */
#define TCPIP_SFE_LINE6_STATUS_UP   1
/* 接口IPV6协议状态DOWN */
#define TCPIP_SFE_LINE6_STATUS_DOWN 2

/* 接口转发报文时递减TTL值 */
#define SFE_IF_REDUCETTL_ENABLE      1
/* 接口转发报文时不递减TTL值 */
#define SFE_IF_REDUCETTL_DISABLE     0

/* 去使能ARP MISS功能 */
#define SFE_ETH_ARP_MISS_DISABLE          1
/* 不去使能ARP MISS功能 */
#define SFE_ETH_ARP_MISS_NOT_DISABLE      0

/* 接口信息来源于控制面PPI下发 */
#define SFE_IF_SOURCE_PPI     0
/* 接口信息来源于产品配置 */
#define SFE_IF_SOURCE_PRODUCT 1

/* 直接调用控制面接口创建/删除/更新接口的接口类型枚举定义 */
typedef enum enumTCPIP_SFE_IF_TYPE
{
    TCPIP_SFE_IF_NULL = 0,
    TCPIP_SFE_IF_INLOOPBACK,
    TCPIP_SFE_IF_LOOPBACK,
    TCPIP_SFE_IF_ETH,
    TCPIP_SFE_IF_PPP,

    TCPIP_SFE_IF_TYPEMAX = 8
}TCPIP_SFE_IF_TYPE_E;

/* IF数据面操作对应的控制面表项配置操作类型 */
typedef enum enumTcpipSfeIfOperType
{
    TCPIP_SFE_IF_CREATE,      /* 接口创建 */
    TCPIP_SFE_IF_DELETE,      /* 接口删除 */
    TCPIP_SFE_IF_SETMTU,      /* 设置MTU */
    TCPIP_SFE_IF_UP,          /* 接口UP */
    TCPIP_SFE_IF_DOWN,        /* 接口DOWN*/
    TCPIP_SFE_IF_SETMAC,      /* 设置接口physical地址 */
    TCPIP_SFE_IF_VRF_BIND,    /* 接口绑定到VRF */
    TCPIP_SFE_IF_VRF_UNBIND,  /* 接口去绑定VRF */

    TCPIP_SFE_IF_OPER_MAX     /* IF表项配置操作类型无效边界值,以后新增类型请在此前增加 */
}TCPIP_SFE_IF_OPER_TYPE_E;

/* 接口信息ID,保证SFE_IFID和TCPIP_SFE_IFID结构成员及大小定义一致 */
typedef struct tagTCPIP_SFE_IFID
{
    UINT8   u8PortType;        /* 端口类型,参见TCPIP_SFE_IF_TYPE_E */
    UINT8   u8FrameID;         /* 框号,全F表示不使用 */
    UINT16  u16SlotID;         /* 逻辑槽位号,全F表示不使用 */
    UINT16  u16PortNo;         /* 逻辑端口号,一维模式下系统端口编号唯一,三维模式下在同一框同一槽位下唯一,此值可配置 */
    UINT16  u16lSubPortNo;     /* 子端口号,目前未使用,预留 */
}TCPIP_SFE_IFID;

/* 接口信息结构,保证SFE_INTERFACE_INFO_S和TCPIP_SFE_INTF_S结构成员及大小定义一致 */
typedef struct tagTCPIP_SFE_INTF
{
    TCPIP_SFE_IFID stIfID;          /* 接口ID */
    UINT32   u32IfIndex;            /* 接口索引,ACL模块需要,产品如没有接口索引则直接填0 */
    UINT32   u32VrfIndex;           /* VRF索引 */
    UINT32   u32LinkType;           /* 端口的链路层属性,目前预留,清0 */
    UINT32   u32PhyStatus;          /* 端口物理状态,值:TCPIP_SFE_PHY_STATUS_UP,TCPIP_SFE_PHY_STATUS_DOWN */
    UINT32   u32LineStatus;         /* IPV4链路状态,值:TCPIP_SFE_LINE4_STATUS_UP,TCPIP_SFE_LINE4_STATUS_DOWN */
    UINT32   u32Line6Status;        /* IPV6链路状态,值:TCPIP_SFE_LINE6_STATUS_UP,TCPIP_SFE_LINE6_STATUS_DOWN */
    UINT32   u32Baud;               /* 端口的波特率 */
    UINT32   u32MTU;                /* 端口的MTU */
    UINT32   u32ReduceTTL;          /* 接口转发报文TTL是否减1,SFE_NO(0):表示不需要递减TTL,SFE_YES(1):表示需要递减TTL */
    UINT8    u8MacAddr[TCPIP_SFE_MAC_LEN];/* physical地址 */
    UINT8    u8Attribute;           /* 接口属性Fabric/spi4口,值:TCPIP_SFE_PORT_FABRIC,TCPIP_SFE_PORT_SPI4 */
    UINT8    u8Origin;              /* 接口创建来源,产品不需要填写 */
    UINT32   u32IsDisableArpMiss;   /* 接口是否需要去使能ARP MISS功能,只对以太口有效 */
}TCPIP_SFE_INTF_S;

/*******************************ROUTE路由相关宏,枚举,结构等定义**********************************/
/* ROUTE模块错误码 */
enum enumTcpipSfeRouteCode
{
    TCPIP_SFE_RT_SUCCESS = 0,           /* 0 路由操作成功 */
    TCPIP_SFE_RT_ERR_BEGIN = TCPIP_SFE_ROUTE_BEGIN_RET_CODE,/* 模块错误码起始值,建议内部不要使用该值 */
    TCPIP_SFE_RT_NULL_POINTER,          /* 1 输入参数为空 */
    TCPIP_SFE_RT_OPER,                  /* 2 操作类型错误 */
    TCPIP_SFE_RT_REG_FILTER_HOOK_NULL,  /* 注册路由过滤回调为空 */
    TCPIP_SFE_RT_PARA_NULL_GET,         /* 指定VRF和IP获取路由信息时传入的参数为NULL */
};

/* 路由配置命令 */
typedef enum enumTcpipSfeRouteOperType
{
    TCPIP_SFE_FIB4_ADD = 0,      /* 路由增加 */
    TCPIP_SFE_FIB4_DEL,          /* 路由删除 */

    TCPIP_SFE_FIB4_OPER_MAX      /* FIB表项配置操作类型无效边界值,以后新增类型请在此前增加 */
}TCPIP_SFE_ROUTE_OPER_TYPE_E;

/* 路由来源宏 */
#define TCPIP_SFE_ROUTE_PPI_DOWN         0   /* 控制面VISP下发路由 */
#define TCPIP_SFE_ROUTE_PRO_DOWN         1   /* 产品添加下发路由 */

/*路由标记*/
enum ROUTE_FLAG
{
    TCPIP_SFE_ROUTE_UP        = 0x1,    /* 路由可用 */
    TCPIP_SFE_ROUTE_GATEWAY   = 0x2,    /* 间接路由, 无此标记则为直接路由 */
    TCPIP_SFE_ROUTE_HOST      = 0x4,    /* 主机路由，无此标记则为网段路由 */
    TCPIP_SFE_ROUTE_DYNAMIC   = 0x10,   /* 动态路由 */
    TCPIP_SFE_ROUTE_STATIC    = 0x800,  /* 静态路由 */
    TCPIP_SFE_ROUTE_BLACKHOLE = 0x1000, /* 黑洞路由，表示需要丢弃报文 */
};

#define TCPIP_SFE_OPEN_ALL_VRF 0xFFFFFFFF     /* 全F时表示open全部的VRF [TCPIP_SFE_OpenTable] */

/* 用户配置路由表项数据结构 */
typedef struct tagTCPIP_SFE_ROUTE
{
    UINT32    u32VrfIndex;          /* 实例索引,用户必须添加*/
    UINT32    u32DstIp;             /* 目的地址,主机字节序,用户必须添加 */
    UINT32    u32Nexthop;           /* 下一跳,,主机字节序,用户必须添加 */
    TCPIP_SFE_IFID  stOutIf;        /* 出接口信息,用户必须添加 */
    UINT32    u32LocalIp;           /* 本地出接口地址,,主机字节序,不使用填充0 */
    UINT32    u32Flags;             /* 路由标记,用户不必指定 */
    UINT32    u32Origin;            /* 来源,,配置时不使用填充0,获取时,TCPIP_SFE_ROUTE_PRO_DOWN表示产品添加;TCPIP_SFE_ROUTE_PPI_DOWN表示有控制面添加 */
    UINT32    u32ATIndex;           /* 保留，暂不使用*/
    UINT8     u8DstPrefixLength;    /* 目的地址掩码长度，用户必须添加 */
    UINT8     u8LocalPrefixLength;  /* 本地出接口地址掩码长度,不使用填充0 */
    UINT16    u16RTPri;             /* 路由优先级,用户可以指定,不指定填充0 */
}TCPIP_SFE_ROUTE_S;

/*******************************ARP相关宏,枚举,结构等定义**********************************/
/* ARP模块错误码 */
typedef enum enumTcpipSfeArpErrCode
{
    TCPIP_SFE_ARP_OK,                       /* 操作成功 */
    TCPIP_SFE_ARP_ERR_BEGIN = TCPIP_SFE_ARP_BEGIN_RET_CODE,/* 模块错误码起始值,建议内部不要使用该值 */
    TCPIP_SFE_ARP_PARA_NULL,                /* 配置ARP时传入NULL指针 */
    TCPIP_SFE_ARP_OPERTYPE_INVALID,         /* 配置ARP时传入的操作类型不合法 */
    TCPIP_SFE_ARP_MISS_GET_IFINDEX_FAIL,    /* 根据接口信息获取接口索引失败 */
    TCPIP_SFE_ARP_MISS_CALL_NOTIFY_FAIL,    /* 调用控制面ARP MISS通知函数通知失败 */
    TCPIP_SFE_ARP_PARA_NULL_GET,            /* 指定VRF和IP获取BFD会话信息时传入的参数为NULL */
    TCPIP_SFE_ARP_MISS_ETHARP_NOT_INIT,     /* 数据面通知控制面ARP MISS时,控制面ETHARP模块没有注册 */
}TCPIP_SFE_ARP_ERR_CODE_E;

/* ARP数据面操作对应的控制面表项配置操作类型 */
typedef enum enumTcpipSfeArpOperType
{
    TCPIP_SFE_ARP_ADD,      /* 增加ARP表项 */
    TCPIP_SFE_ARP_DEL,      /* 删除ARP表项 */

    TCPIP_SFE_ARP_OPER_MAX  /* ARP表项配置操作类型无效边界值,以后新增类型请在此前增加 */
}TCPIP_SFE_ARP_OPER_TYPE_E;

/* ARP节点来源于控制面PPI下发 */
#define SFE_ARP_SOURCE_PPI 0
/* ARP节点来源于控制面产品配置,因为数据面的某些接口控制面VISP是看不见的,所以需要产品直接配置 */
#define SFE_ARP_SOURCE_PRODUCT 1

/* 静态ARP标志 */
#define SFE_ARP_STATIC_ARPNODE 1
/* 动态ARP标志 */
#define SFE_ARP_DYNAMIC_ARPNODE 0

/* ARP数据面操作对应的控制面配置参数结构 */
typedef struct tagTCPIP_SFE_ARP
{
    TCPIP_SFE_IFID  stIfID;                         /* 该ARP表项所属的接口 */
    UINT32          u32VrfIndex;                    /* IP所属VRF */
    UINT32          u32IpAddr;                      /* 地址，主机字节序 */
    UINT8           u8MacAddr[TCPIP_SFE_MAC_LEN];   /* physical地址 */
    UINT8           u8StaticFlag;                   /* 动静态ARP标志,对配置接口该字段无效,用户可填SFE_ARP_STATIC_ARPNODE
                                                       取值范围:SFE_ARP_STATIC_ARPNODE，SFE_ARP_DYNAMIC_ARPNODE */
    UINT8           u8Source;                       /* ARP表项的来源,对配置接口该字段无效,用户可直接填SFE_ARP_SOURCE_PPI
                                                       取值范围:SFE_ARP_SOURCE_PPI，SFE_ARP_SOURCE_PRODUCT */
}TCPIP_SFE_ARP_S;

/*******************************BFD相关宏,枚举,结构等定义**********************************/
/* BFD模块错误码 */
typedef enum enumTcpipSfeBfdErrCode
{
    TCPIP_SFE_BFD_OK,                       /* 操作成功 */
    TCPIP_SFE_BFD_ERR_BEGIN = TCPIP_SFE_BFD_BEGIN_RET_CODE,/* 模块错误码起始值,建议内部不要使用该值 */
    TCPIP_SFE_BFD_PARA_NULL_PPI,            /* PPI配置BFD时传入的参数为NULL */
    TCPIP_SFE_BFD_PARA_NULL_GET,            /* 指定VRF和会话ID获取BFD会话信息时传入的参数为NULL */
    TCPIP_SFE_BFD_NOTIFY_DOWN_FUNC_NULL,    /* 数据面探测到BFD DOWN调用的控制面通知函数钩子未注册 */
    TCPIP_SFE_BFD_PARA_NULL_GETSTAT,        /* 获取BFD统计信息时,传入参数为空 */
}TCPIP_SFE_BFD_ERR_CODE_E;

/* 不带任何认证的BFD控制报文长度 */
#define SFE_BFD_LEN_AUTH_NONE       24

/* 单跳BFD会话 */
#define SFE_BFD_SINGLE_HOP_SESS     0
/* 多跳BFD会话 */
#define SFE_BFD_MULTI_HOP_SESS      1

/* BFD会话状态DOWN */
#define SFE_BFD_SESS_STATE_DOWN     0
/* BFD会话状态UP */
#define SFE_BFD_SESS_STATE_UP       1

/* IPv4 BFD会话 */
#define SFE_BFD_SESS_IPV4           0
/* IPv6 BFD会话 */
#define SFE_BFD_SESS_IPV6           1

/* BFD的检测模式,目前数据面只支持不带ECHO功能的异步模式SFE_BFD_DETECT_ASYNC_WOECHO */
/* CAUTION: 该枚举定义需要与控制面BFD_DETECT_MODE_E定义保持一致 */
typedef enum enumSFE_BFD_DETECT_MODE
{
    SFE_BFD_DETECT_ASYNC_WECHO = 0,                 /* 带ECHO功能的异步模式 */
    SFE_BFD_DETECT_ASYNC_WOECHO,                    /* 不带ECHO功能的异步模式 */
    SFE_BFD_DETECT_DEMAND_WECHO,                    /* 带ECHO功能的查询模式 */
    SFE_BFD_DETECT_DEMAND_WOECHO,                   /* 不带ECHO功能的查询模式 */
    SFE_BFD_DETECT_MODE_MAX                         /* 检测模式的最大无效值 */
}SFE_BFD_DETECT_MODE_E;

/* 地址信息结构定义 */
typedef union unTCPIP_SFE_IPADDR
{
    UINT32 u32IPv4;       /* IPv4地址 */
    UINT32 u32IPv6[4];    /* IPv6地址 */
}TCPIP_SFE_IPADDR_UN;

/* BFD会话信息 */
typedef struct tagTCPIP_SFE_BFD_SESS_INFO
{
    UINT32 u32VrfIndex;                  /* 会话所在的VRF */
    UINT32 u32SessionId;                 /* BFD会话ID */
    UINT32 u32SessIsUp;                  /* 会话是否UP标志:UP/DOWN */
    UINT32 u32DetectMode;                /* 实际的检测模式 */
    UINT32 u32TxInterval;                /* 本端实际的发送时间间隔,ms */
    UINT32 u32DetectInterval;            /* 本端实际的检测间隔,ms */
    UINT32 u32DetectMult;                /* 本端实际的检测倍数 */
    UINT32 u32MyDiscriminator;           /* 本端标识符 */
    UINT32 u32YourDiscriminator;         /* 对端标识符 */
    UINT32 u32IpVer;                     /* IP版本标识:0--表示是IPv4 BFD;1--表示是IPv6 BFD */
    TCPIP_SFE_IPADDR_UN unDstIPAddr;     /* 对端地址,主机序 */
    TCPIP_SFE_IPADDR_UN unSrcIPAddr;     /* 本端地址,主机序 */
    UINT32 u32TTL;                       /* TTL */
    UINT32 u32DstUdpPort;                /* UDP目的端口号,单跳为3784,多跳为4784,主机序 */
    UINT32 u32SrcUdpPort;                /* UDP源端口号,值为49151+X(X>0),主机序 */
    UINT32 u32Tos;                       /* TOS值 */
    UINT32 u32IsMultiHop;                /* BFD多跳会话标志,要求在控制面根据接口索引转换好 */
    TCPIP_SFE_IFID stSendIfID;           /* 会话的出接口信息,单跳时有效,多跳时无效 */

    CHAR szCtlPkt[SFE_BFD_LEN_AUTH_NONE];/* 会话的BFD控制报文,网络序,值为用户配置值 */
}TCPIP_SFE_BFD_SESS_INFO_S;

/* BFD会话统计信息 ,增加该结构里面字段,需要更改显示接口和清0接口 */
typedef struct tagSFE_SESS_BFD_STATISTIC
{
    UINT32 u32Bfd_ToOwnDetectPkt;                       /* BFD正常终结报文统计 */
    UINT32 u32Bfd_SendTotalPkt;                           /* BFD会话发送报文总计数 */
    UINT32 u32Bfd_SendSuccessPkt;                       /* 本端会话UP,BFD成功发送报文统计 */
    UINT32 u32Bfd_ToCtrlSessNotUp;                      /* 数据面对应会话状态没有UP时,上交控制面统计 */
    UINT32 u32Bfd_ToCtrlPktStateNotUp;                  /* BFD报文中的状态不为BFD_STATE_UP(3)时,上交控制面统计 */
    UINT32 u32Bfd_ToCtrlPktPollFlagSet;                 /* BFD报文中的P标志置位时,上交控制面统计 */
    UINT32 u32Bfd_ToCtrlPktFinalFlagSet;                /* BFD报文中的F标志置位时,上交控制面统计 */

    UINT32 u32Bfd_DropVrfNotMatch;                      /* 本端会话UP,收到报文vrf和本端会话vrf不一致丢弃统计 */
    UINT32 u32Bfd_DropDstIpNotMatch;                    /* 本端会话UP,收到报文目的IP和会话源IP不一致丢弃统计 */
    UINT32 u32Bfd_DropSrcIpNotMatch;                    /* 本端会话UP,收到报文源IP和会话目的IP不一致丢弃统计 */
    UINT32 u32Bfd_DropSingleHopTTL;                     /* 本端会话UP,单跳会话收到报文TTL不是255丢弃统计 */

    UINT32 u32Bfd_DropPortTypeNotMatch;                 /* 本端会话UP,单调会话收到报文接口类型和本端创建会话接口类型不一致丢弃统计 */
    UINT32 u32Bfd_DropFrameIDNotMatch;                  /* 本端会话UP,单调会话收到报文框号和本端创建会话框号类型不一致丢弃统计 */
    UINT32 u32Bfd_DropSlotIDNotMatch;                   /* 本端会话UP,单调会话收到报文槽号和本端创建会话槽号类型不一致丢弃统计 */
    UINT32 u32Bfd_DropPortNumNotMatch;                  /* 本端会话UP,单调会话收到报文端口号和本端创建会话端口号不一致丢弃统计 */

    UINT32 u32Bfd_DetectDownNotifyOk;                   /* 探测定时器超时,上报控制面Down次数 */
    UINT32 u32Bfd_DetectDownNotifyFail;                 /* 探测定时器超时,上报控制面Down失败次数 */

    UINT32 u32Bfd_AbnormalGetSessRecvPkt;               /* 收到BFD报文,从pool中获取BFD会话失败异常统计 */
    UINT32 u32Bfd_AbnormalGetSessAtSendTimer;           /* 发送定时器超时,从pool中获取BFD会话失败异常统计 */
    UINT32 u32Bfd_AbnormalGetSessAtDetectTimer;         /* 探测定时器超时,,从pool中获取BFD会话失败异常统计 */

}SFE_BFD_SESS_STATISTIC_S;


/*******************************ICMP相关宏,枚举,结构等定义**********************************/
/* ICMP模块错误码 */
enum enumTcpipSfeIcmpErrCode
{
    TCPIP_SFE_ICMP_OK,
    TCPIP_SFE_ICMP_ERR_BEGIN = TCPIP_SFE_ICMP_BEGIN_RET_CODE,/* 模块错误码起始值,建议内部不要使用该值 */
    TCPIP_SFE_ICMP_SET_SWITCH_ERR,    /* 1 设置发送ICMP调试开关非法 */
    TCPIP_SFE_ICMP_GET_NULL_POINT,    /* 2 获取发送ICMP调试开关参数为空 */
};

/* 关闭发送ICMP差错报文 */
#define SFE_ICMP_SEND_OFF           0x00000000
/* 主机不可达差错报文打开 */
#define SFE_ICMP_HOST_UNREACH_ON    0x00000001
/* TTL为0差错报文打开 */
#define SFE_ICMP_TTL_ZERO_ON        0x00000002
/* 需分片但设置了DF标志 */
#define SFE_ICMP_NEED_FRAG_ON       0x00000004
/* 打开发送所有ICMP差错报文 */
#define SFE_ICMP_SEND_ALL           (SFE_ICMP_HOST_UNREACH_ON | SFE_ICMP_TTL_ZERO_ON | SFE_ICMP_NEED_FRAG_ON)

/*******************************IP相关宏,枚举,结构等定义**********************************/
/* IP模块错误码 */
enum enumTcpipSfeIPErrCode
{
    TCPIP_SFE_IP_OK,
    TCPIP_SFE_IP_ERR_BEGIN = TCPIP_SFE_IP_BEGIN_RET_CODE,
    TCPIP_SFE_IP_GET_SRCIP_NULL_POINT,  /* 1 获取源IP Addr时，传入参数为空 */
};

/*******************************POOL表项相关宏,枚举等定义**********************************/
/* POOL表项操作错误码 */
enum enumTcpipSfeTblOperCode
{
    TCPIP_SFE_TABLE_SUCCESS = 0,           /* 操作成功 */
    TCPIP_SFE_TABLE_ERR_BEGIN = TCPIP_SFE_TABLE_BEGIN_RET_CODE,/* 模块错误码起始值,建议内部不要使用该值 */

    TCPIP_SFE_TABLE_OPEN_COM_NULL,         /* OPEN操作,通信模块指针没有注册 */
    TCPIP_SFE_TABLE_OPEN_NULL_PTR,         /* OPEN操作,输入指针为空 */
    TCPIP_SFE_TABLE_OPEN_ALLOC,            /* OPEN操作,分配内存空间失败 */
    TCPIP_SFE_TABLE_OPEN_SEND,             /* OPEN操作,发往数据面通道失败 */
    TCPIP_SFE_TABLE_OPEN_RECV,             /* OPEN操作,接收数据面消息失败 */
    TCPIP_SFE_TABLE_OPEN_HEADER_LEN,       /* OPEN操作,接收数据面通道长度和报文长度不一致 */
    TCPIP_SFE_TABLE_OPEN_TOTAL_LEN,        /* OPEN操作,接收数据面长度非法 */
    TCPIP_SFE_TABLE_OPEN_SEQ,              /* OPEN操作,接收数据面序列号和发送时产生的序列号不一致 */
    TCPIP_SFE_TABLE_OPEN_ITEM_LEN,         /* OPEN操作,接收数据面报文子选项长度非法 */

    TCPIP_SFE_TABLE_GET_OVER,              /* GET操作,数据面表项已经获取完成 */
    TCPIP_SFE_TABLE_GET_COM_NULL,          /* GET操作,通信模块指针没有注册 */
    TCPIP_SFE_TABLE_GET_NULL_PTR,          /* GET操作,输入指针为空 */
    TCPIP_SFE_TABLE_GET_ALLOC,             /* GET操作,分配内存空间失败 */
    TCPIP_SFE_TABLE_GET_SEND,              /* GET操作,发往数据面通道失败 */
    TCPIP_SFE_TABLE_GET_RECV,              /* GET操作,接收数据面消息失败 */
    TCPIP_SFE_TABLE_GET_TOTAL_LEN,         /* GET操作,接收数据面长度非法 */
    TCPIP_SFE_TABLE_GET_HEADER_LEN,        /* GET操作,接收数据面通道长度和报文长度不一致 */
    TCPIP_SFE_TABLE_GET_SEQ,               /* GET操作,接收数据面序列号和发送时产生的序列号不一致 */
    TCPIP_SFE_TABLE_GET_ITEM_LEN,          /* GET操作,接收数据面报文子选项长度非法 */
    TCPIP_SFE_TABLE_GET_TABLE_DATA_LEN,    /* GET操作,接收数据面表项内容长度错误 */
    TCPIP_SFE_TABLE_GET_NUM,               /* GET操作,接收数据面表项数目非法 */
    TCPIP_SFE_TABLE_GET_LARGE_LEN,         /* GET操作,接收数据面表项长度大于用户传递的缓冲区 */

    TCPIP_SFE_TABLE_CLOSE_COM_NULL,        /* CLOSE操作,通信模块指针没有注册 */
    TCPIP_SFE_TABLE_CLOSE_ALLOC,           /* CLOSE操作,分配内存空间失败 */
    TCPIP_SFE_TABLE_CLOSE_SEND,            /* CLOSE操作,发往数据面通道失败 */
    TCPIP_SFE_TABLE_CLOSE_RECV,            /* CLOSE操作,接收数据面消息失败 */
    TCPIP_SFE_TABLE_CLOSE_TOTAL_LEN,       /* CLOSE操作,接收数据面长度非法 */
    TCPIP_SFE_TABLE_CLOSE_HEADER_LEN,      /* CLOSE操作,接收数据面通道长度和报文长度不一致 */
    TCPIP_SFE_TABLE_CLOSE_SEQ,             /* CLOSE操作,接收数据面序列号和发送时产生的序列号不一致 */
    TCPIP_SFE_TABLE_CLOSE_ITEM_LEN,        /* CLOSE操作,接收数据面报文子选项长度非法 */
};

/* POOL表项操作类型宏, TCPIP_SFE_OpenTable中u32TableType参数值 */
enum enumTableType
{
    TCPIP_SFE_TABLE_ETH,
    TCPIP_SFE_TABLE_NULL,
    TCPIP_SFE_TABLE_INLOOPBACK,
    TCPIP_SFE_TABLE_LOOPBACK,
    TCPIP_SFE_TABLE_ROUTE,
    TCPIP_SFE_TABLE_BALANCE_ROUTE,
    TCPIP_SFE_TABLE_RESOLVED_ARP,
    TCPIP_SFE_TABLE_RESOLVING_ARP,
    TCPIP_SFE_TABLE_BFD_SESSION,
    TCPIP_SFE_TABLE_MAX,
};

/*******************************PUB相关宏,枚举等定义**********************************/
/* 公共模块错误码 */
typedef enum enumTcpipSfePubErrCode
{
    TCPIP_SFE_PUB_OK,
    TCPIP_SFE_PUB_ERR_BEGIN = TCPIP_SFE_PUB_BEGIN_RET_CODE,
    TCPIP_SFE_GET_ACLFAKEREASS_SWITCH_POINT_NULL,       /* 获取ACL是否需要数据面进行假重组开关时,传入参数为NULL */
}TCPIP_SFE_PUB_ERR_CODE_E;

/*******************************维测模块相关宏,枚举等定义**********************************/
/* 维测调试统计日志模块错误码 */
typedef enum enumTcpipSfeDebugErrCode
{
    TCPIP_SFE_DEBUG_OK,                       /* 操作成功 */
    TCPIP_SFE_DEBUG_ERR_BEGIN = TCPIP_SFE_DEBUG_BEGIN_RET_CODE,/* 模块错误码起始值,建议内部不要使用该值 */
    TCPIP_SFE_GET_DEBUGSWITCH_POINT_NULL,               /* 1  获取调试开关时参数为空指针 */
    TCPIP_SFE_SET_MSGOREVENT_DEBUG_PARA_ERR,            /* 2  设置消息或事件调试开关时,参数错误 */
    TCPIP_SFE_GET_MSGOREVENT_DEBUG_PARA_NULL,           /* 3  获取控制面和数据面的消息或事件调试开关时指针为空 */
    TCPIP_SFE_GET_VERBOSE_DEBUG_NULL_POINT,             /* 4  获取详细调试的报文次数和报文个数 */

    TCPIP_SFE_GET_STAT_MANUALINFO_POINT_NULL,           /* 5  获取全局统计信息时,传入的手动统计指针为NULL */
    TCPIP_SFE_GET_STAT_AUTOINFO_POINT_NULL,             /* 6  获取全局统计信息时,传入的自动统计指针为NULL */
    TCPIP_SFE_GET_STAT_GETMANUALNULL,                   /* 7  获取全局统计信息时,从数据面获取的全局手动统计信息指针为NULL */
    TCPIP_SFE_GET_STAT_GETAUTONULL,                     /* 8  获取全局统计信息时,从数据面获取的全局自动统计信息指针为NULL */
    TCPIP_SFE_GET_MANUSTATBYVCPU_POINT_NULL,            /* 9  获取指定VCPU的全局手动统计信息时,传入的指针为NULL */
    TCPIP_SFE_GET_MANUSTATBYVCPU_VCPU_INVALID,          /* 10 获取指定VCPU的全局手动统计信息时,传入的VCPU ID不合法 */
    TCPIP_SFE_GET_MANUSTATBYVCPU_GETMANUALNULL,         /* 11 获取指定VCPU的全局手动统计信息时,从数据面获取的全局手动统计信息指针为NULL */

    TCPIP_SFE_GET_FLOWSTAT_SWITCH_POINT_NULL,           /* 12 获取流统计开关时,传入空指针 */
    TCPIP_SFE_GET_FLOWSTAT_RULENUM_POINT_NULL,          /* 13 获取流统计规则数时,传入空指针 */

    TCPIP_SFE_GET_FLOWSTATRULE_RULEPOINT_NULL,          /* 14 获取流统计规则时,传入的存放获取规则的数组空间指针为NULL */
    TCPIP_SFE_GET_FLOWSTATRULE_NUMPOINT_NULL,           /* 15 获取流统计规则时,传入的需要获取的规则数目指针为NULL */
    TCPIP_SFE_GET_FLOWSTATRULE_GETRULENULL,             /* 16 获取流统计规则时,从数据面获取的流统计规则指针为NULL */

    TCPIP_SFE_GET_FLOWSTATINFO_RULEPOINT_NULL,          /* 17 获取流统计信息时,传入的流规则指针为NULL */
    TCPIP_SFE_GET_FLOWSTATINFO_MANUALINFOPOINT_NULL,    /* 18 获取流统计信息时,传入的手动流统计信息指针为NULL */
    TCPIP_SFE_GET_FLOWSTATINFO_AUTOINFOPOINT_NULL,      /* 19 获取流统计信息时,传入的自动流统计信息指针为NULL */
    TCPIP_SFE_GET_FLOWSTATINFO_GETRULENULL,             /* 20 获取流统计信息时,从数据面获取的流统计规则指针为NULL */
    TCPIP_SFE_GET_FLOWSTATINFO_GETMANUALNULL,           /* 21 获取流统计信息时,从数据面获取的手动流统计指针为NULL */
    TCPIP_SFE_GET_FLOWSTATINFO_GETAUTONULL,             /* 22 获取流统计信息时,从数据面获取的自动流统计指针为NULL */
    TCPIP_SFE_GET_FLOWSTATINFO_NOT_EXIST,               /* 23 获取流统计信息时,指定的流规则不存在 */


}TCPIP_SFE_DEBUG_ERR_CODE_E;

/*******************************调试相关宏,枚举等定义**********************************/
/* 异常调试信息输出位开关 */
#define SFE_DEBUG_TYPE_ERROR        0x0001
/* 入口出口调试信息输出位开关 */
#define SFE_DEBUG_TYPE_INOUT        0x0002
/* 重要处理流程调试信息输出位开关 */
#define SFE_DEBUG_TYPE_PROC         0x0004
/* 详细调试信息输出位开关*/
#define SFE_DEBUG_TYPE_VERBOSE      0x0008

/* 打开所有调试类型开关 */
#define SFE_DEBUG_TYPE_ALL \
    (SFE_DEBUG_TYPE_ERROR | SFE_DEBUG_TYPE_INOUT | SFE_DEBUG_TYPE_PROC | SFE_DEBUG_TYPE_VERBOSE)

/* 打开IPFWD模块调试开关 */
#define SFE_DEBUG_MODULE_IPFWD     0x00000001
/* 打开ICMP模块调试开关 */
#define SFE_DEBUG_MODULE_ICMP      0x00000002
/* 打开BFD模块调试开关 */
#define SFE_DEBUG_MODULE_BFD       0x00000004
/* 打开当前全部模块的调试开关,Notice:当前只考虑IPFED/ICMP/BFD三个模块,不考虑IR的模块*/
#define SFE_DEBUG_MODULE_ALL       (SFE_DEBUG_MODULE_IPFWD | SFE_DEBUG_MODULE_ICMP | SFE_DEBUG_MODULE_BFD)

/* 详细调试信息输出个数默认值,表示一至打印 */
#define SFE_VERBOSE_DEBUG_DEFAULT_COUNT         0xFFFFFFFF
/* 详细调试报文信息长度默认值,单位:字节 */
#define SFE_VERBOSE_DEBUG_PACKET_DEFAULT_LEN    128

/*******************************统计相关宏,枚举等定义**********************************/
/* 数据面支持的最大VCPU个数 */
#define SFE_VCPU_MAX_NUM  32

/* 显示各VCPU手动统计值之和 */
#define SFE_SHOW_TOTAL_MANUAL_STATISTIC  0xFFFFFFFF

/* 流统计规则配置操作的操作类型 */
typedef enum enumSfeFlowStatisticRuleOperType
{
    SFE_FLOWSTATISTIC_ADD,      /* 添加流统计规则 */
    SFE_FLOWSTATISTIC_DEL,      /* 删除流统计规则 */
    SFE_FLOWSTATISTIC_DELALL,   /* 删除所有流统计规则 */

    SFE_FLOWSTATISTIC_OPER_MAX  /* 流统计规则配置操作类型无效边界值,以后新增类型请在此前增加 */
}SFE_FLOWSTATISTIC_RULE_OPER_TYPE_E;

/* 流统计开关打开 */
#define  SFE_FLOWSTAT_SWITCH_ON     1
/* 流统计开关关闭 */
#define  SFE_FLOWSTAT_SWITCH_OFF    0

/* 流规则中的VRF通配值,当为该值时,表示所有VRF都匹配 */
#define SFE_FLOWSTAT_VRF_ALL        0xFFFFFFFF
/* 流规则中的协议号通配值,当为该值时,表示所有协议号都匹配 */
#define SFE_FLOWSTAT_PROTO_ALL      0xFFFFFFFF
/* 流规则中的地址通配值,当为该值时,表示所有IP都匹配 */
#define SFE_FLOWSTAT_IP_ALL         0
/* 流规则中的端口号通配值,当为该值时,表示所有端口号都匹配 */
#define SFE_FLOWSTAT_PORT_ALL       0

/* 流统计规则结构定义,流统计规则的配置要求用户在删除一条流规则后必须间隔一定时间(一个报文在协议栈可能停留的最大时间,
   例如6s,)之后才重新添加流规则,否则可能存在多核操作引起的问题,统计值可能不准确 */
typedef struct  tagTCPIP_SFE_FlowStatisticRule
{
    UINT32              u32FlowStatId;        /* 流统计ID,添加时作为输出参数,删除时忽略该值,填0即可,获取时表示流统计ID,从0开始编号 */
    UINT32              u32VrfIndex;          /* VRF索引,主机序 */
    TCPIP_SFE_IPADDR_UN unSrcIp;              /* 源IP,主机序 */
    TCPIP_SFE_IPADDR_UN unDstIp;              /* 目的IP,主机序 */
    UINT32              u32ProNo;             /* 协议号,取值范围[0,255] */
    UINT16              u16SrcPort;           /* 源端口号,主机序,只在协议为UDP和TCP时有效,其它协议号时无效用户直接填0即可 */
    UINT16              u16DstPort;           /* 目的端口号,主机序,只在协议为UDP和TCP时有效,其它协议号时无效用户直接填0即可 */
}TCPIP_SFE_FLOWSTATISTIC_RULE_S;

/* 数据面手动统计项统计结构定义 */
typedef struct  tagSFE_IPSFEStatistic
{
    UINT64  dwLink_In;                      /* 接收入口统计 */
    UINT64  dwEth_In;                       /* eth接收入口统计 */
    UINT64  dwNet_In;                       /* net接收入口统计 */
    UINT64  dwIcmp_Out;                     /* 数据面产生的icmp差错报文统计 */

    UINT64  dwArp_Deliver;                  /* ARP上送处理统计 */
    UINT64  dwIpOpt_Deliver;                /* IP选项报文上送统计 */
    UINT64  dwIpBroadcast_Deliver;          /* 广播报文上送统计 */
    UINT64  dwIpMulticast_Deliver;          /* 多播报文上送统计 */
    UINT64  dwNonFrag_Deliver;              /* 本地接收的非分片非OSPF非BFD报文上交FWD分发统计 */
    UINT64  dwFragHaveFakeReassed_Deliver;  /* 本机接收的分片报文已经在其它地方假重组上交FWD分发统计 */
    UINT64  dwOspf_Deliver;                 /* OSPF上送处理统计 */
    UINT64  dwUpToCtrlPlane;                /* 上送控制面统计 */

    UINT64  dwFakeReass_NetSuccess;         /* 在网络层进行假重组成功FWD分发统计 */
    UINT64  dwFakeReass_LinkSuccess;        /* 在链路层进行假重组成功上送统计 */
    UINT64  dwFakeReass_InFragNum;          /* 进行假重组的分片报文数 */
    UINT64  dwFakeReass_OutFragNum;         /* 假重组成功的分片报文个数 */
    UINT64  dwReass_InFragNum;              /* 进行真重组的分片报文个数 */
    UINT64  dwReass_OutReassPktNum;         /* 真重组成功返回的完整报文个数 */

    UINT64  dwNet_Out;                      /* net发送出口统计 */
    UINT64  dwEth_Out;                      /* eth发送出口统计,交给驱动发送 */

    UINT64  dwFrag_InNum;                   /* 分片报文入口总数 */
    UINT64  dwFrag_OutNum;                  /* 分片报文出口总数 */

    UINT64  dwFakeRease_resv;               /* 进行分片重组处理,并返回去保序统计 */
    UINT64  dwArpMiss_Resv;                 /* ARP查找失败,缓存报文并返回去保序统计 */

    UINT64  dwArp_ArpSearchIn;              /* ARP查找入口统计 */
    UINT64  dwArp_HaveNormalArp;            /* ARP查找成功统计(存在正常ARP) */
    UINT64  dwArp_HaveFakeArp;              /* ARP查找存在ARP哑元统计(不存在正常ARP但存在哑元ARP) */
    UINT64  dwArp_NoArp;                    /* ARP查找不存在ARP统计(既不存在正常ARP也不存在哑元ARP) */
    UINT64  dwArp_ReNotifyArpMissSuccess;   /* ARP查找存在ARP哑元时重新上报ARP MISS成功 */
    UINT64  dwArp_SendCachePktSuccess;      /* 更新ARP哑元节点时,发送缓存报文成功 */

    UINT64  dwIcmp_RecvErrIcmpPkt;          /* 收到ICMP差错报文,不产生差错报文的个数 */
    UINT64  dwIcmp_RecvNoFirstFrg;          /* 收到报文不是首片,不产生差错报文的个数 */
    UINT64  dwIcmp_RecvBroadOrMultiPkt;     /* 收到广播或多播包,不产生差错报文的个数 */
    UINT64  dwIcmp_RecvSrcIpErr;            /* 收到的报文源IP错误，不产生差错报文的个数 */
    UINT64  dwIcmp_SendUnreachHostNum;      /* 发送主机不可达报文个数 */
    UINT64  dwIcmp_SendNeedFragNum;         /* 发送需分片但是置不分片差错报文个数 */
    UINT64  dwIcmp_SendTimeExceededNum;     /* 发送生存时间超时差错报文个数 */

    UINT64  dwBfd_In;                       /* BFD接收入口报文统计 */
    UINT64  dwBfd_ToCtrlSessIdZero;         /* BFD报文中的ulYourDisctor为0时,上交控制面统计 */
    UINT64  dwBfd_ToCtrlSessNotUp;          /* 数据面对应会话状态没有UP时,上交控制面统计 */
    UINT64  dwBfd_ToCtrlPktStateNotUp;      /* BFD报文中的状态不为BFD_STATE_UP(3)时,上交控制面统计 */
    UINT64  dwBfd_ToCtrlPktPollFlagSet;     /* BFD报文中的P标志置位时,上交控制面统计 */
    UINT64  dwBfd_ToCtrlPktFinalFlagSet;    /* BFD报文中的F标志置位时,上交控制面统计 */
    UINT64  dwBfd_ToOwnDetectPkt;           /* BFD正常终结报文统计 */
    UINT64  dwBfd_DetectUp;                 /* BFD探测到会话正常的统计 */
    UINT64  dwBfd_DetectDownNotifyOk;       /* BFD探测到会话DOWN并通知控制面成功的统计 */
    UINT64  dwBfd_EncapsualeLinkHeader;     /* BFD封装链路层头部报文统计 */
    UINT64  dwBfd_SendPktOk;                /* BFD报文发送成功统计 */

    UINT64  dwFwd_HaveHandle;               /* 本地接收报文交给FWD钩子,FWD钩子已经处理交VISP直接发送 */
    UINT64  dwFwd_NotHandle;                /* 本地接收报文交给FWD钩子,FWD钩子未处理交VISP控制面处理 */
    UINT64  dwFwd_Drop;                     /* 本地接收报文交给FWD钩子,FWD钩子已经处理交VISP释放报文 */

    UINT64  dwAcl_Forward_NotHandle;        /* 转发报文交给ACL钩子,ACL钩子未处理交VISP继续转发处理 */
    UINT64  dwAcl_Forward_Drop;             /* 转发报文交给ACL钩子,ACL钩子已处理交VISP释放报文 */

    UINT64  dwAcl_UpDeliver_NotHandle;      /* 上交控制面及FWD报文交给ACL钩子,ACL钩子未处理交VISP继续转发处理 */
    UINT64  dwAcl_UpDeliver_Drop;           /* 上交控制面及FWD报文交给ACL钩子,ACL钩子未处理交VISP继续转发处理 */

    UINT64  dwNet_BadVers;                  /* IP版本号错误 */
    UINT64  dwNet_BadHLen;                  /* IP首部长度无效的报文个数 */
    UINT64  dwNet_BadLen;                   /* IP首部和IP数据长度不一致的报文个数 */
    UINT64  dwNet_TooShort;                 /* 具有无效数据长度的报文个数 */
    UINT64  dwNet_BadSum;                   /* 校验和错误的报文数 */
    UINT64  dwNet_NoProto;                  /* 具有不支持的协议的报文个数 */
    UINT64  dwNet_NoRoute;                  /* 没有路由 */
    UINT64  dwNet_TTLExceed;                /* TTL小于1,无法转发的报文个数 */  
    UINT64  dwNet_CantFrag;                 /* 由于DF置位而丢弃的报文数 */

}SFE_IPSFE_STATISTIC_S;

/* 目前只针对接收转发流程进行流统计及打点处理,主动发送的报文,如ICM,BFD报文暂不考虑 */
/* 数据面流统计手动统计项统计结构定义 */
typedef struct  tagSFE_IPSFEFlowStatistic
{
    UINT32  u32Link_FlowStat_TcpUdpNonFrag;         /* Link链路层TCP或UDP非分片报文流统计起始点 */
    UINT32  u32Link_FlowStat_TcpUdpFrag;            /* Link链路层TCP或UDP分片报文流统计起始点 */
    UINT32  u32Link_FlowStat_NonTcpUdp;             /* Link链路层非TCP和UDP报文流统计起始点 */

    UINT32  u32Eth_In;                              /* eth以太接收入口统计 */
    UINT32  u32Net_In;                              /* net网络层接收入口统计 */
    UINT32  u32Acl_ForwardHook_NotHandle;           /* 上交控制面处理中,ACL钩子函数处理返回让数据面继续处理 */
    UINT32  u32Acl_ForwardHook_Drop;                /* 上交控制面处理中,ACL钩子函数处理返回让数据面丢弃报文 */
    UINT32  u32Frag_In;                             /* 分片处理入口报文统计 */
    UINT32  u32Frag_Out;                            /* 分片处理出口报文统计 */
    UINT32  u32Net_Out;                             /* net网络层发送出口统计 */
    UINT32  u32Arp_HaveFakeArp;                     /* ARP查找存在ARP哑元统计(不存在正常ARP但存在哑元ARP) */
    UINT32  u32Arp_NoArp;                           /* ARP查找不存在ARP统计(既不存在正常ARP也不存在哑元ARP) */
    UINT32  u32Arp_FakeArpCachePkt;                 /* 存在哑元ARP时缓存报文统计 */
    UINT32  u32Arp_NoArpCachePkt;                   /* 不存在ARP(既不存在正常ARP也不存在哑元ARP)时缓存报文统计 */
    UINT32  u32Eth_Out;                             /* eth以太发送出口统计 */
    UINT32  u32Arp_SendCachePkt;                    /* 发送ARP哑元缓存报文统计 */

    UINT32  u32UpDeliver_IpOpt;                     /* 带IP选项的报文待上交控制面处理 */
    UINT32  u32UpDeliver_IpBroadcast;               /* IP广播报文待上交控制面处理 */
    UINT32  u32UpDeliver_IpMulticast;               /* IP多播报文待上交控制面处理 */
    UINT32  u32UpDeliver_IpOspf;                    /* IP OSPF报文待上交控制面处理 */
    UINT32  u32UpDeliver_IpLocalInFragHaveFakeReass;/* 本机接收的分片报文已经在其它地方假重组待上交控制面处理 */
    UINT32  u32UpDeliver_IpLocalInFragNetFakeReass; /* 本机接收的分片报文在网络层进行假重组成功待上交控制面处理 */
    UINT32  u32UpDeliver_IpLocalInNotFragOspfBfd;   /* 本机接收的非分片非OSPF非BFD报文待上交控制面处理 */
    UINT32  u32LocalIn_UpDeliverFwdHook_HaveHandle; /* 上交控制面处理中,本地接收报文FWD钩子函数处理返回让数据面将报文交给驱动发送 */
    UINT32  u32LocalIn_UpDeliverFwdHook_NotHandle;  /* 上交控制面处理中,本地接收报文FWD钩子函数处理返回让数据面继续上交控制面处理 */
    UINT32  u32LocalIn_UpDeliverFwdHook_Drop;       /* 上交控制面处理中,本地接收报文FWD钩子函数处理返回让数据面丢弃报文 */
    UINT32  u32Acl_UpDeliverHook_NotHandle;         /* 上交控制面处理中,ACL钩子函数处理返回让数据面继续处理 */
    UINT32  u32Acl_UpDeliverHook_Drop;              /* 上交控制面处理中,ACL钩子函数处理返回让数据面丢弃报文 */
    UINT32  u32UpToCtrlPlane;                       /* 上送控制面统计 */

    UINT32  u32Bfd_In;                              /* BFD接收入口报文统计 */
    UINT32  u32Bfd_ToOwnDetectPkt;                  /* BFD数据面正常终结报文统计 */
    UINT32  u32UpDeliver_BfdSessIdZero;             /* BFD报文中的ulYourDisctor为0,待上交控制面处理统计 */
    UINT32  u32UpDeliver_BfdSessNotUp;              /* 数据面对应会话状态没有UP,待上交控制面处理统计 */
    UINT32  u32UpDeliver_BfdPktStateNotUp;          /* BFD报文中的状态不为BFD_STATE_UP(3),待上交控制面处理统计 */
    UINT32  u32UpDeliver_BfdPktPollFlagSet;         /* BFD报文中的P标志置位,待上交控制面处理统计 */
    UINT32  u32UpDeliver_BfdPktFinalFlagSet;        /* BFD报文中的F标志置位,待上交控制面处理统计 */
}SFE_IPSFE_FLOWSTATISTIC_S;

/*可测试性信息码结构定义*/
/*tml base start*/
#define SFE_STAT_BASE    0x0000
/*tml base end*/

/* 数据面处理自动统计项ID */
enum SFE_STAT_ID_IPFWD_ENUM
{
    /*tml code start*/
    SFE_STAT_IPFWD_0000 = SFE_STAT_BASE,  /*预留,不使用*/
    SFE_STAT_IPFWD_0001,
    SFE_STAT_IPFWD_0002,
    SFE_STAT_IPFWD_0003,
    SFE_STAT_IPFWD_0004,
    SFE_STAT_IPFWD_0005,
    SFE_STAT_IPFWD_0006,
    SFE_STAT_IPFWD_0007,
    SFE_STAT_IPFWD_0008,
    SFE_STAT_IPFWD_0009,
    SFE_STAT_IPFWD_000A,
    SFE_STAT_IPFWD_000B,
    SFE_STAT_IPFWD_000C,
    SFE_STAT_IPFWD_000D,
    SFE_STAT_IPFWD_000E,
    SFE_STAT_IPFWD_000F,
    SFE_STAT_IPFWD_0010,
    SFE_STAT_IPFWD_0011,
    SFE_STAT_IPFWD_0012,
    SFE_STAT_IPFWD_0013,
    SFE_STAT_IPFWD_0014,
    SFE_STAT_IPFWD_0015,
    SFE_STAT_IPFWD_0016,
    SFE_STAT_IPFWD_0017,
    SFE_STAT_IPFWD_0018,
    SFE_STAT_IPFWD_0019,
    SFE_STAT_IPFWD_001A,
    SFE_STAT_IPFWD_001B,
    SFE_STAT_IPFWD_001C,
    SFE_STAT_IPFWD_001D,
    SFE_STAT_IPFWD_001E,
    SFE_STAT_IPFWD_001F,
    SFE_STAT_IPFWD_0020,
    SFE_STAT_IPFWD_0021,
    SFE_STAT_IPFWD_0022,
    SFE_STAT_IPFWD_0023,
    SFE_STAT_IPFWD_0024,
    SFE_STAT_IPFWD_0025,
    SFE_STAT_IPFWD_0026,
    SFE_STAT_IPFWD_0027,
    SFE_STAT_IPFWD_0028,
    SFE_STAT_IPFWD_0029,
    SFE_STAT_IPFWD_002A,
    SFE_STAT_IPFWD_002B,
    SFE_STAT_IPFWD_002C,
    SFE_STAT_IPFWD_002D,
    SFE_STAT_IPFWD_002E,
    SFE_STAT_IPFWD_002F,
    SFE_STAT_IPFWD_0030,
    SFE_STAT_IPFWD_0031,
    SFE_STAT_IPFWD_0032,
    SFE_STAT_IPFWD_0033,
    SFE_STAT_IPFWD_0034,
    SFE_STAT_IPFWD_0035,
    SFE_STAT_IPFWD_0036,
    SFE_STAT_IPFWD_0037,
    SFE_STAT_IPFWD_0038,
    SFE_STAT_IPFWD_0039,
    SFE_STAT_IPFWD_003A,
    SFE_STAT_IPFWD_003B,
    SFE_STAT_IPFWD_003C,
    SFE_STAT_IPFWD_003D,
    SFE_STAT_IPFWD_003E,
    SFE_STAT_IPFWD_003F,
    SFE_STAT_IPFWD_0040,
    SFE_STAT_IPFWD_0041,
    SFE_STAT_IPFWD_0042,
    SFE_STAT_IPFWD_0043,
    SFE_STAT_IPFWD_0044,
    SFE_STAT_IPFWD_0045,
    SFE_STAT_IPFWD_0046,
    SFE_STAT_IPFWD_0047,
    SFE_STAT_IPFWD_0048,
    SFE_STAT_IPFWD_0049,
    SFE_STAT_IPFWD_004A,
    SFE_STAT_IPFWD_004B,
    SFE_STAT_IPFWD_004C,
    SFE_STAT_IPFWD_004D,
    SFE_STAT_IPFWD_004E,
    SFE_STAT_IPFWD_004F,
    SFE_STAT_IPFWD_0050,
    SFE_STAT_IPFWD_0051,
    SFE_STAT_IPFWD_0052,
    SFE_STAT_IPFWD_0053,
    SFE_STAT_IPFWD_0054,
    SFE_STAT_IPFWD_0055,
    SFE_STAT_IPFWD_0056,
    SFE_STAT_IPFWD_0057,
    SFE_STAT_IPFWD_0058,
    SFE_STAT_IPFWD_0059,
    SFE_STAT_IPFWD_005A,
    SFE_STAT_IPFWD_005B,
    SFE_STAT_IPFWD_005C,
    SFE_STAT_IPFWD_005D,
    SFE_STAT_IPFWD_005E,
    SFE_STAT_IPFWD_005F,
    SFE_STAT_IPFWD_0060,
    SFE_STAT_IPFWD_0061,
    SFE_STAT_IPFWD_0062,
    SFE_STAT_IPFWD_0063,
    SFE_STAT_IPFWD_0064,
    SFE_STAT_IPFWD_0065,
    SFE_STAT_IPFWD_0066,
    SFE_STAT_IPFWD_0067,
    SFE_STAT_IPFWD_0068,
    SFE_STAT_IPFWD_0069,
    SFE_STAT_IPFWD_006A,
    SFE_STAT_IPFWD_006B,
    SFE_STAT_IPFWD_006C,
    SFE_STAT_IPFWD_006D,
    SFE_STAT_IPFWD_006E,
    SFE_STAT_IPFWD_006F,
    SFE_STAT_IPFWD_0070,
    SFE_STAT_IPFWD_0071,
    SFE_STAT_IPFWD_0072,
    SFE_STAT_IPFWD_0073,
    SFE_STAT_IPFWD_0074,
    SFE_STAT_IPFWD_0075,
    SFE_STAT_IPFWD_0076,
    SFE_STAT_IPFWD_0077,
    SFE_STAT_IPFWD_0078,
    SFE_STAT_IPFWD_0079,
    SFE_STAT_IPFWD_007A,
    SFE_STAT_IPFWD_007B,
    SFE_STAT_IPFWD_007C,
    SFE_STAT_IPFWD_007D,
    SFE_STAT_IPFWD_007E,
    SFE_STAT_IPFWD_007F,
    SFE_STAT_IPFWD_0080,
    SFE_STAT_IPFWD_0081,
    SFE_STAT_IPFWD_0082,
    SFE_STAT_IPFWD_0083,
    SFE_STAT_IPFWD_0084,
    SFE_STAT_IPFWD_0085,
    SFE_STAT_IPFWD_0086,
    SFE_STAT_IPFWD_0087,
    SFE_STAT_IPFWD_0088,
    SFE_STAT_IPFWD_0089,
    SFE_STAT_IPFWD_008A,
    SFE_STAT_IPFWD_008B,
    SFE_STAT_IPFWD_008C,
    SFE_STAT_IPFWD_008D,
    SFE_STAT_IPFWD_008E,
    SFE_STAT_IPFWD_008F,
    SFE_STAT_IPFWD_0090,
    SFE_STAT_IPFWD_0091,
    SFE_STAT_IPFWD_0092,
    SFE_STAT_IPFWD_0093,
    SFE_STAT_IPFWD_0094,
    SFE_STAT_IPFWD_0095,
    SFE_STAT_IPFWD_0096,
    SFE_STAT_IPFWD_0097,
    SFE_STAT_IPFWD_0098,
    SFE_STAT_IPFWD_0099,
    SFE_STAT_IPFWD_009A,
    SFE_STAT_IPFWD_009B,
    SFE_STAT_IPFWD_009C,
    SFE_STAT_IPFWD_009D,
    SFE_STAT_IPFWD_009E,
    SFE_STAT_IPFWD_009F,
    SFE_STAT_IPFWD_00A0,
    SFE_STAT_IPFWD_00A1,
    SFE_STAT_IPFWD_00A2,
    SFE_STAT_IPFWD_00A3,
    SFE_STAT_IPFWD_00A4,
    SFE_STAT_IPFWD_00A5,
    SFE_STAT_IPFWD_00A6,
    SFE_STAT_IPFWD_00A7,
    SFE_STAT_IPFWD_00A8,
    SFE_STAT_IPFWD_00A9,
    SFE_STAT_IPFWD_00AA,
    SFE_STAT_IPFWD_00AB,
    SFE_STAT_IPFWD_00AC,
    SFE_STAT_IPFWD_00AD,
    SFE_STAT_IPFWD_00AE,
    SFE_STAT_IPFWD_00AF,
    SFE_STAT_IPFWD_00B0,
    SFE_STAT_IPFWD_00B1,
    SFE_STAT_IPFWD_00B2,
    SFE_STAT_IPFWD_00B3,
    SFE_STAT_IPFWD_00B4,
    SFE_STAT_IPFWD_00B5,
    SFE_STAT_IPFWD_00B6,
    SFE_STAT_IPFWD_00B7,
    SFE_STAT_IPFWD_00B8,
    SFE_STAT_IPFWD_00B9,
    SFE_STAT_IPFWD_00BA,
    SFE_STAT_IPFWD_00BB,
    SFE_STAT_IPFWD_00BC,
    SFE_STAT_IPFWD_00BD,
    SFE_STAT_IPFWD_00BE,
    SFE_STAT_IPFWD_00BF,
    SFE_STAT_IPFWD_00C0,
    SFE_STAT_IPFWD_00C1,
    SFE_STAT_IPFWD_00C2,
    SFE_STAT_IPFWD_00C3,
    SFE_STAT_IPFWD_00C4,
    SFE_STAT_IPFWD_00C5,
    SFE_STAT_IPFWD_00C6,
    SFE_STAT_IPFWD_00C7,
    SFE_STAT_IPFWD_00C8,
    SFE_STAT_IPFWD_00C9,
    SFE_STAT_IPFWD_00CA,
    SFE_STAT_IPFWD_00CB,
    SFE_STAT_IPFWD_00CC,
    SFE_STAT_IPFWD_00CD,
    SFE_STAT_IPFWD_00CE,
    SFE_STAT_IPFWD_00CF,
    SFE_STAT_IPFWD_00D0,
    SFE_STAT_IPFWD_00D1,
    SFE_STAT_IPFWD_00D2,
    SFE_STAT_IPFWD_00D3,
    SFE_STAT_IPFWD_00D4,
    SFE_STAT_IPFWD_00D5,
    SFE_STAT_IPFWD_00D6,
    SFE_STAT_IPFWD_00D7,
    SFE_STAT_IPFWD_00D8,
    SFE_STAT_IPFWD_00D9,
    SFE_STAT_IPFWD_00DA,
    SFE_STAT_IPFWD_00DB,
    SFE_STAT_IPFWD_00DC,
    SFE_STAT_IPFWD_00DD,
    SFE_STAT_IPFWD_00DE,
    SFE_STAT_IPFWD_00DF,
    SFE_STAT_IPFWD_00E0,
    SFE_STAT_IPFWD_00E1,
    SFE_STAT_IPFWD_00E2,
    SFE_STAT_IPFWD_00E3,
    SFE_STAT_IPFWD_00E4,
    SFE_STAT_IPFWD_00E5,
    SFE_STAT_IPFWD_00E6,
    SFE_STAT_IPFWD_00E7,
    SFE_STAT_IPFWD_00E8,
    SFE_STAT_IPFWD_00E9,
    SFE_STAT_IPFWD_00EA,
    SFE_STAT_IPFWD_00EB,
    SFE_STAT_IPFWD_00EC,
    SFE_STAT_IPFWD_00ED,
    SFE_STAT_IPFWD_00EE,
    SFE_STAT_IPFWD_00EF,
    SFE_STAT_IPFWD_00F0,
    SFE_STAT_IPFWD_00F1,
    SFE_STAT_IPFWD_00F2,
    SFE_STAT_IPFWD_00F3,
    SFE_STAT_IPFWD_00F4,
    SFE_STAT_IPFWD_00F5,
    SFE_STAT_IPFWD_00F6,
    SFE_STAT_IPFWD_00F7,
    SFE_STAT_IPFWD_00F8,
    SFE_STAT_IPFWD_00F9,
    SFE_STAT_IPFWD_00FA,
    SFE_STAT_IPFWD_00FB,
    SFE_STAT_IPFWD_00FC,
    SFE_STAT_IPFWD_00FD,
    SFE_STAT_IPFWD_00FE,
    SFE_STAT_IPFWD_00FF,
    SFE_STAT_IPFWD_0100,
    SFE_STAT_IPFWD_0101,
    SFE_STAT_IPFWD_0102,
    SFE_STAT_IPFWD_0103,
    SFE_STAT_IPFWD_0104,
    SFE_STAT_IPFWD_0105,
    SFE_STAT_IPFWD_0106,
    SFE_STAT_IPFWD_0107,
    SFE_STAT_IPFWD_0108,
    SFE_STAT_IPFWD_0109,
    SFE_STAT_IPFWD_010A,
    SFE_STAT_IPFWD_010B,
    SFE_STAT_IPFWD_010C,
    SFE_STAT_IPFWD_010D,
    SFE_STAT_IPFWD_010E,
    SFE_STAT_IPFWD_010F,
    SFE_STAT_IPFWD_0110,
    SFE_STAT_IPFWD_0111,
    SFE_STAT_IPFWD_0112,
    SFE_STAT_IPFWD_0113,
    SFE_STAT_IPFWD_0114,
    SFE_STAT_IPFWD_0115,
    SFE_STAT_IPFWD_0116,
    SFE_STAT_IPFWD_0117,
    SFE_STAT_IPFWD_0118,
    SFE_STAT_IPFWD_0119,
    SFE_STAT_IPFWD_011A,
    SFE_STAT_IPFWD_011B,
    SFE_STAT_IPFWD_011C,
    SFE_STAT_IPFWD_011D,
    SFE_STAT_IPFWD_011E,
    SFE_STAT_IPFWD_011F,
    SFE_STAT_IPFWD_0120,
    SFE_STAT_IPFWD_0121,
    SFE_STAT_IPFWD_0122,
    SFE_STAT_IPFWD_0123,
    SFE_STAT_IPFWD_0124,
    SFE_STAT_IPFWD_0125,
    SFE_STAT_IPFWD_0126,
    SFE_STAT_IPFWD_0127,
    SFE_STAT_IPFWD_0128,
    SFE_STAT_IPFWD_0129,
    SFE_STAT_IPFWD_012A,
    SFE_STAT_IPFWD_012B,
    SFE_STAT_IPFWD_012C,
    SFE_STAT_IPFWD_012D,
    SFE_STAT_IPFWD_012E,
    SFE_STAT_IPFWD_012F,
    SFE_STAT_IPFWD_0130,
    SFE_STAT_IPFWD_0131,
    SFE_STAT_IPFWD_0132,
    SFE_STAT_IPFWD_0133,
    SFE_STAT_IPFWD_0134,
    SFE_STAT_IPFWD_0135,
    SFE_STAT_IPFWD_0136,
    SFE_STAT_IPFWD_0137,
    SFE_STAT_IPFWD_0138,
    SFE_STAT_IPFWD_0139,
    SFE_STAT_IPFWD_013A,
    SFE_STAT_IPFWD_013B,
    SFE_STAT_IPFWD_013C,
    SFE_STAT_IPFWD_013D,
    SFE_STAT_IPFWD_013E,
    SFE_STAT_IPFWD_013F,
    SFE_STAT_IPFWD_0140,
    SFE_STAT_IPFWD_0141,
    SFE_STAT_IPFWD_0142,
    SFE_STAT_IPFWD_0143,
    SFE_STAT_IPFWD_0144,
    SFE_STAT_IPFWD_0145,
    SFE_STAT_IPFWD_0146,
    SFE_STAT_IPFWD_0147,
    SFE_STAT_IPFWD_0148,
    SFE_STAT_IPFWD_0149,
    SFE_STAT_IPFWD_014A,
    SFE_STAT_IPFWD_014B,
    SFE_STAT_IPFWD_014C,
    SFE_STAT_IPFWD_014D,
    SFE_STAT_IPFWD_014E,
    SFE_STAT_IPFWD_014F,
    SFE_STAT_IPFWD_0150,
    SFE_STAT_IPFWD_0151,
    SFE_STAT_IPFWD_0152,
    SFE_STAT_IPFWD_0153,
    SFE_STAT_IPFWD_0154,
    SFE_STAT_IPFWD_0155,
    SFE_STAT_IPFWD_0156,
    SFE_STAT_IPFWD_0157,
    SFE_STAT_IPFWD_0158,
    SFE_STAT_IPFWD_0159,
    SFE_STAT_IPFWD_015A,
    SFE_STAT_IPFWD_015B,
    SFE_STAT_IPFWD_015C,
    SFE_STAT_IPFWD_015D,
    SFE_STAT_IPFWD_015E,
    SFE_STAT_IPFWD_015F,
    SFE_STAT_IPFWD_0160,
    SFE_STAT_IPFWD_0161,
    SFE_STAT_IPFWD_0162,
    SFE_STAT_IPFWD_0163,
    SFE_STAT_IPFWD_0164,
    SFE_STAT_IPFWD_0165,
    SFE_STAT_IPFWD_0166,
    SFE_STAT_IPFWD_0167,
    SFE_STAT_IPFWD_0168,
    SFE_STAT_IPFWD_0169,
    SFE_STAT_IPFWD_016A,
    SFE_STAT_IPFWD_016B,
    SFE_STAT_IPFWD_016C,
    SFE_STAT_IPFWD_016D,
    SFE_STAT_IPFWD_016E,
    SFE_STAT_IPFWD_016F,
    SFE_STAT_IPFWD_0170,
    SFE_STAT_IPFWD_0171,
    SFE_STAT_IPFWD_0172,
    SFE_STAT_IPFWD_0173,
    SFE_STAT_IPFWD_0174,
    SFE_STAT_IPFWD_0175,
    SFE_STAT_IPFWD_0176,
    SFE_STAT_IPFWD_0177,
    SFE_STAT_IPFWD_0178,
    SFE_STAT_IPFWD_0179,
    SFE_STAT_IPFWD_017A,
    SFE_STAT_IPFWD_017B,
    SFE_STAT_IPFWD_017C,
    SFE_STAT_IPFWD_017D,
    SFE_STAT_IPFWD_017E,
    SFE_STAT_IPFWD_017F,
    SFE_STAT_IPFWD_0180,
    SFE_STAT_IPFWD_0181,
    SFE_STAT_IPFWD_0182,
    SFE_STAT_IPFWD_0183,
    SFE_STAT_IPFWD_0184,
    SFE_STAT_IPFWD_0185,
    SFE_STAT_IPFWD_0186,
    SFE_STAT_IPFWD_0187,
    SFE_STAT_IPFWD_0188,
    SFE_STAT_IPFWD_0189,
    SFE_STAT_IPFWD_018A,
    SFE_STAT_IPFWD_018B,
    SFE_STAT_IPFWD_018C,
    SFE_STAT_IPFWD_018D,
    SFE_STAT_IPFWD_018E,
    SFE_STAT_IPFWD_018F,
    SFE_STAT_IPFWD_0190,
    SFE_STAT_IPFWD_0191,
    SFE_STAT_IPFWD_0192,
    SFE_STAT_IPFWD_0193,
    SFE_STAT_IPFWD_0194,
    SFE_STAT_IPFWD_0195,
    SFE_STAT_IPFWD_0196,
    SFE_STAT_IPFWD_0197,
    SFE_STAT_IPFWD_0198,
    SFE_STAT_IPFWD_0199,
    SFE_STAT_IPFWD_019A,
    SFE_STAT_IPFWD_019B,
    SFE_STAT_IPFWD_019C,
    SFE_STAT_IPFWD_019D,
    SFE_STAT_IPFWD_019E,
    SFE_STAT_IPFWD_019F,
    SFE_STAT_IPFWD_01A0,
    SFE_STAT_IPFWD_01A1,
    SFE_STAT_IPFWD_01A2,
    SFE_STAT_IPFWD_01A3,
    SFE_STAT_IPFWD_01A4,
    SFE_STAT_IPFWD_01A5,
    SFE_STAT_IPFWD_01A6,
    SFE_STAT_IPFWD_01A7,
    SFE_STAT_IPFWD_01A8,
    SFE_STAT_IPFWD_01A9,
    SFE_STAT_IPFWD_01AA,
    SFE_STAT_IPFWD_01AB,
    SFE_STAT_IPFWD_01AC,
    SFE_STAT_IPFWD_01AD,
    SFE_STAT_IPFWD_01AE,
    SFE_STAT_IPFWD_01AF,
    SFE_STAT_IPFWD_01B0,
    SFE_STAT_IPFWD_01B1,
    SFE_STAT_IPFWD_01B2,
    SFE_STAT_IPFWD_01B3,
    SFE_STAT_IPFWD_01B4,
    SFE_STAT_IPFWD_01B5,
    SFE_STAT_IPFWD_01B6,
    SFE_STAT_IPFWD_01B7,
    SFE_STAT_IPFWD_01B8,
    SFE_STAT_IPFWD_01B9,
    SFE_STAT_IPFWD_01BA,
    SFE_STAT_IPFWD_01BB,
    SFE_STAT_IPFWD_01BC,
    SFE_STAT_IPFWD_01BD,
    SFE_STAT_IPFWD_01BE,
    SFE_STAT_IPFWD_01BF,
    SFE_STAT_IPFWD_01C0,
    SFE_STAT_IPFWD_01C1,
    SFE_STAT_IPFWD_01C2,
    SFE_STAT_IPFWD_01C3,
    SFE_STAT_IPFWD_01C4,
    SFE_STAT_IPFWD_01C5,
    SFE_STAT_IPFWD_01C6,
    SFE_STAT_IPFWD_01C7,
    SFE_STAT_IPFWD_01C8,
    SFE_STAT_IPFWD_01C9,
    SFE_STAT_IPFWD_01CA,
    SFE_STAT_IPFWD_01CB,
    SFE_STAT_IPFWD_01CC,
    SFE_STAT_IPFWD_01CD,
    SFE_STAT_IPFWD_01CE,
    SFE_STAT_IPFWD_01CF,
    SFE_STAT_IPFWD_01D0,
    SFE_STAT_IPFWD_01D1,
    SFE_STAT_IPFWD_01D2,
    SFE_STAT_IPFWD_01D3,
    SFE_STAT_IPFWD_01D4,
    SFE_STAT_IPFWD_01D5,
    SFE_STAT_IPFWD_01D6,
    SFE_STAT_IPFWD_01D7,
    SFE_STAT_IPFWD_01D8,
    SFE_STAT_IPFWD_01D9,
    SFE_STAT_IPFWD_01DA,
    SFE_STAT_IPFWD_01DB,
    SFE_STAT_IPFWD_01DC,
    SFE_STAT_IPFWD_01DD,
    SFE_STAT_IPFWD_01DE,
    SFE_STAT_IPFWD_01DF,
    SFE_STAT_IPFWD_01E0,
    SFE_STAT_IPFWD_01E1,
    SFE_STAT_IPFWD_01E2,
    SFE_STAT_IPFWD_01E3,
    SFE_STAT_IPFWD_01E4,
    SFE_STAT_IPFWD_01E5,
    SFE_STAT_IPFWD_01E6,
    SFE_STAT_IPFWD_01E7,
    SFE_STAT_IPFWD_01E8,
    SFE_STAT_IPFWD_01E9,
    SFE_STAT_IPFWD_01EA,
    SFE_STAT_IPFWD_01EB,
    SFE_STAT_IPFWD_01EC,
    SFE_STAT_IPFWD_01ED,
    SFE_STAT_IPFWD_01EE,
    SFE_STAT_IPFWD_01EF,
    SFE_STAT_IPFWD_01F0,
    SFE_STAT_IPFWD_01F1,
    SFE_STAT_IPFWD_01F2,
    SFE_STAT_IPFWD_01F3,
    SFE_STAT_IPFWD_01F4,
    SFE_STAT_IPFWD_01F5,
    SFE_STAT_IPFWD_01F6,
    SFE_STAT_IPFWD_01F7,
    SFE_STAT_IPFWD_01F8,
    SFE_STAT_IPFWD_01F9,
    SFE_STAT_IPFWD_01FA,
    SFE_STAT_IPFWD_01FB,
    SFE_STAT_IPFWD_01FC,
    SFE_STAT_IPFWD_01FD,
    SFE_STAT_IPFWD_01FE,
    SFE_STAT_IPFWD_01FF,
    SFE_STAT_IPFWD_0200,
    SFE_STAT_IPFWD_0201,
    SFE_STAT_IPFWD_0202,
    SFE_STAT_IPFWD_0203,
    SFE_STAT_IPFWD_0204,
    SFE_STAT_IPFWD_0205,
    SFE_STAT_IPFWD_0206,
    SFE_STAT_IPFWD_0207,
    SFE_STAT_IPFWD_0208,
    SFE_STAT_IPFWD_0209,
    SFE_STAT_IPFWD_020A,
    SFE_STAT_IPFWD_020B,
    SFE_STAT_IPFWD_020C,
    SFE_STAT_IPFWD_020D,
    SFE_STAT_IPFWD_020E,
    SFE_STAT_IPFWD_020F,
    SFE_STAT_IPFWD_0210,
    SFE_STAT_IPFWD_0211,
    SFE_STAT_IPFWD_0212,
    SFE_STAT_IPFWD_0213,
    SFE_STAT_IPFWD_0214,
    SFE_STAT_IPFWD_0215,
    SFE_STAT_IPFWD_0216,
    SFE_STAT_IPFWD_0217,
    SFE_STAT_IPFWD_0218,
    SFE_STAT_IPFWD_0219,
    SFE_STAT_IPFWD_021A,
    SFE_STAT_IPFWD_021B,
    SFE_STAT_IPFWD_021C,
    SFE_STAT_IPFWD_021D,
    SFE_STAT_IPFWD_021E,
    SFE_STAT_IPFWD_021F,
    SFE_STAT_IPFWD_0220,
    SFE_STAT_IPFWD_0221,
    SFE_STAT_IPFWD_0222,
    SFE_STAT_IPFWD_0223,
    SFE_STAT_IPFWD_0224,
    SFE_STAT_IPFWD_0225,
    SFE_STAT_IPFWD_0226,
    SFE_STAT_IPFWD_0227,
    SFE_STAT_IPFWD_0228,
    SFE_STAT_IPFWD_0229,
    SFE_STAT_IPFWD_022A,
    SFE_STAT_IPFWD_022B,
    SFE_STAT_IPFWD_022C,
    SFE_STAT_IPFWD_022D,
    SFE_STAT_IPFWD_022E,
    SFE_STAT_IPFWD_022F,
    SFE_STAT_IPFWD_0230,
    SFE_STAT_IPFWD_0231,
    SFE_STAT_IPFWD_0232,
    SFE_STAT_IPFWD_0233,
    SFE_STAT_IPFWD_0234,
    SFE_STAT_IPFWD_0235,
    SFE_STAT_IPFWD_0236,
    SFE_STAT_IPFWD_0237,
    SFE_STAT_IPFWD_0238,
    SFE_STAT_IPFWD_0239,
    SFE_STAT_IPFWD_023A,
    SFE_STAT_IPFWD_023B,
    SFE_STAT_IPFWD_023C,
    SFE_STAT_IPFWD_023D,
    SFE_STAT_IPFWD_023E,
    SFE_STAT_IPFWD_023F,
    SFE_STAT_IPFWD_0240,
    SFE_STAT_IPFWD_0241,
    SFE_STAT_IPFWD_0242,
    SFE_STAT_IPFWD_0243,
    SFE_STAT_IPFWD_0244,
    SFE_STAT_IPFWD_0245,
    SFE_STAT_IPFWD_0246,
    SFE_STAT_IPFWD_0247,
    SFE_STAT_IPFWD_0248,
    SFE_STAT_IPFWD_0249,
    SFE_STAT_IPFWD_024A,
    SFE_STAT_IPFWD_024B,
    SFE_STAT_IPFWD_024C,
    SFE_STAT_IPFWD_024D,
    SFE_STAT_IPFWD_024E,
    SFE_STAT_IPFWD_024F,
    SFE_STAT_IPFWD_0250,
    SFE_STAT_IPFWD_0251,
    SFE_STAT_IPFWD_0252,
    SFE_STAT_IPFWD_0253,
    SFE_STAT_IPFWD_0254,
    SFE_STAT_IPFWD_0255,
    SFE_STAT_IPFWD_0256,
    SFE_STAT_IPFWD_0257,
    SFE_STAT_IPFWD_0258,
    SFE_STAT_IPFWD_0259,
    SFE_STAT_IPFWD_025A,
    SFE_STAT_IPFWD_025B,
    SFE_STAT_IPFWD_025C,
    SFE_STAT_IPFWD_025D,
    SFE_STAT_IPFWD_025E,
    SFE_STAT_IPFWD_025F,
    SFE_STAT_IPFWD_0260,
    SFE_STAT_IPFWD_0261,
    SFE_STAT_IPFWD_0262,
    SFE_STAT_IPFWD_0263,
    SFE_STAT_IPFWD_0264,
    SFE_STAT_IPFWD_0265,
    SFE_STAT_IPFWD_0266,
    SFE_STAT_IPFWD_0267,
    SFE_STAT_IPFWD_0268,
    SFE_STAT_IPFWD_0269,
    SFE_STAT_IPFWD_026A,
    SFE_STAT_IPFWD_026B,
    SFE_STAT_IPFWD_026C,
    SFE_STAT_IPFWD_026D,
    SFE_STAT_IPFWD_026E,
    SFE_STAT_IPFWD_026F,
    SFE_STAT_IPFWD_0270,
    SFE_STAT_IPFWD_0271,
    SFE_STAT_IPFWD_0272,
    SFE_STAT_IPFWD_0273,
    SFE_STAT_IPFWD_0274,
    SFE_STAT_IPFWD_0275,
    SFE_STAT_IPFWD_0276,
    SFE_STAT_IPFWD_0277,
    SFE_STAT_IPFWD_0278,
    SFE_STAT_IPFWD_0279,
    SFE_STAT_IPFWD_027A,
    SFE_STAT_IPFWD_027B,
    SFE_STAT_IPFWD_027C,
    SFE_STAT_IPFWD_027D,
    SFE_STAT_IPFWD_027E,
    SFE_STAT_IPFWD_027F,
    SFE_STAT_IPFWD_0280,
    SFE_STAT_IPFWD_0281,
    SFE_STAT_IPFWD_0282,
    SFE_STAT_IPFWD_0283,
    SFE_STAT_IPFWD_0284,
    SFE_STAT_IPFWD_0285,
    SFE_STAT_IPFWD_0286,
    SFE_STAT_IPFWD_0287,
    SFE_STAT_IPFWD_0288,
    SFE_STAT_IPFWD_0289,
    SFE_STAT_IPFWD_028A,
    SFE_STAT_IPFWD_028B,
    SFE_STAT_IPFWD_028C,
    SFE_STAT_IPFWD_028D,
    SFE_STAT_IPFWD_028E,
    SFE_STAT_IPFWD_028F,
    SFE_STAT_IPFWD_0290,
    SFE_STAT_IPFWD_0291,
    SFE_STAT_IPFWD_0292,
    SFE_STAT_IPFWD_0293,
    SFE_STAT_IPFWD_0294,
    SFE_STAT_IPFWD_0295,
    SFE_STAT_IPFWD_0296,
    SFE_STAT_IPFWD_0297,
    SFE_STAT_IPFWD_0298,
    SFE_STAT_IPFWD_0299,
    SFE_STAT_IPFWD_029A,
    SFE_STAT_IPFWD_029B,
    SFE_STAT_IPFWD_029C,
    SFE_STAT_IPFWD_029D,
    SFE_STAT_IPFWD_029E,
    SFE_STAT_IPFWD_029F,
    SFE_STAT_IPFWD_0300,
    SFE_STAT_IPFWD_0301,
    SFE_STAT_IPFWD_0302,
    SFE_STAT_IPFWD_0303,
    SFE_STAT_IPFWD_0304,
    SFE_STAT_IPFWD_0305,
    SFE_STAT_IPFWD_0306,
    SFE_STAT_IPFWD_0307,
    SFE_STAT_IPFWD_0308,
    SFE_STAT_IPFWD_0309,
    SFE_STAT_IPFWD_030A,
    SFE_STAT_IPFWD_030B,
    SFE_STAT_IPFWD_030C,
    SFE_STAT_IPFWD_030D,
    SFE_STAT_IPFWD_030E,
    SFE_STAT_IPFWD_030F,
    SFE_STAT_IPFWD_0310,
    SFE_STAT_IPFWD_0311,
    SFE_STAT_IPFWD_0312,
    SFE_STAT_IPFWD_0313,
    SFE_STAT_IPFWD_0314,
    SFE_STAT_IPFWD_0315,
    SFE_STAT_IPFWD_0316,
    SFE_STAT_IPFWD_0317,
    SFE_STAT_IPFWD_0318,
    SFE_STAT_IPFWD_0319,
    SFE_STAT_IPFWD_031A,
    SFE_STAT_IPFWD_031B,
    SFE_STAT_IPFWD_031C,
    SFE_STAT_IPFWD_031D,
    SFE_STAT_IPFWD_031E,
    SFE_STAT_IPFWD_031F,
    SFE_STAT_IPFWD_0320,
    SFE_STAT_IPFWD_0321,
    SFE_STAT_IPFWD_0322,
    SFE_STAT_IPFWD_0323,
    SFE_STAT_IPFWD_0324,
    SFE_STAT_IPFWD_0325,
    SFE_STAT_IPFWD_0326,
    SFE_STAT_IPFWD_0327,
    SFE_STAT_IPFWD_0328,
    SFE_STAT_IPFWD_0329,
    SFE_STAT_IPFWD_032A,
    SFE_STAT_IPFWD_032B,
    SFE_STAT_IPFWD_032C,
    SFE_STAT_IPFWD_032D,
    SFE_STAT_IPFWD_032E,
    SFE_STAT_IPFWD_032F,
    SFE_STAT_IPFWD_0330,
    SFE_STAT_IPFWD_0331,
    SFE_STAT_IPFWD_0332,
    SFE_STAT_IPFWD_0333,
    SFE_STAT_IPFWD_0334,
    SFE_STAT_IPFWD_0335,
    SFE_STAT_IPFWD_0336,
    SFE_STAT_IPFWD_0337,
    SFE_STAT_IPFWD_0338,
    SFE_STAT_IPFWD_0339,
    SFE_STAT_IPFWD_033A,
    SFE_STAT_IPFWD_033B,
    SFE_STAT_IPFWD_033C,
    SFE_STAT_IPFWD_033D,
    SFE_STAT_IPFWD_033E,
    SFE_STAT_IPFWD_033F,
    SFE_STAT_IPFWD_0340,
    SFE_STAT_IPFWD_0341,
    SFE_STAT_IPFWD_0342,
    SFE_STAT_IPFWD_0343,
    SFE_STAT_IPFWD_0344,
    SFE_STAT_IPFWD_0345,
    SFE_STAT_IPFWD_0346,
    SFE_STAT_IPFWD_0347,
    SFE_STAT_IPFWD_0348,
    SFE_STAT_IPFWD_0349,
    SFE_STAT_IPFWD_034A,
    SFE_STAT_IPFWD_034B,
    SFE_STAT_IPFWD_034C,
    SFE_STAT_IPFWD_034D,
    SFE_STAT_IPFWD_034E,
    SFE_STAT_IPFWD_034F,
    SFE_STAT_IPFWD_0350,
    SFE_STAT_IPFWD_0351,
    SFE_STAT_IPFWD_0352,
    SFE_STAT_IPFWD_0353,
    SFE_STAT_IPFWD_0354,
    SFE_STAT_IPFWD_0355,
    SFE_STAT_IPFWD_0356,
    SFE_STAT_IPFWD_0357,
    SFE_STAT_IPFWD_0358,
    SFE_STAT_IPFWD_0359,
    SFE_STAT_IPFWD_035A, 
    SFE_STAT_IPFWD_035B,
    SFE_STAT_IPFWD_035C,
    SFE_STAT_IPFWD_035D,
    SFE_STAT_IPFWD_035E,
    SFE_STAT_IPFWD_035F,
    SFE_STAT_IPFWD_0360,
    SFE_STAT_IPFWD_0361,
    SFE_STAT_IPFWD_0362,
    SFE_STAT_IPFWD_0363,
    SFE_STAT_IPFWD_0364,
    SFE_STAT_IPFWD_0365,
    SFE_STAT_IPFWD_0366,
    SFE_STAT_IPFWD_0367,
    SFE_STAT_IPFWD_0368,
    SFE_STAT_IPFWD_0369,
    SFE_STAT_IPFWD_0370,
    SFE_STAT_IPFWD_0371,
    SFE_STAT_IPFWD_0372,
    SFE_STAT_IPFWD_0373,
    SFE_STAT_IPFWD_0374,
    SFE_STAT_IPFWD_0375,
    SFE_STAT_IPFWD_0376,
    SFE_STAT_IPFWD_0377,
    SFE_STAT_IPFWD_0378,
    SFE_STAT_IPFWD_0379,
    SFE_STAT_IPFWD_0380,
    SFE_STAT_IPFWD_MAX,
    /*tml code end*/
};



#ifdef  __cplusplus
}
#endif
#endif

