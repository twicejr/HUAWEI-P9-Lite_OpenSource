/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 *
 *-----------------------------------------------------------------------*
 *
 *                             ppp_core_def.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPP
 *  Date Created: 2004-07-01
 *        Author: YiAn
 *   Description: PPP组件使用的宏定义声明
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004-07-01      YiAn            Create
 *  2004-12-05      YiAn            Modify
 *  2006-03-31      ZhuKun          Adjust for D00661
 *  2006-04-21      ZhuKun          Adjust for D00875
 *  2006-05-13      l48923          Delete useless code
 *  2006-06-20      ZhouTong        A82D02377:删除PFC/ACFC/MC/PPPMUX预配置参数
 *  2006-09-12      fuxiaodong      A82D06326:修改宏PPP_GETSHORT，PPP_GETLONG
 *  2008-08-25      f54882          Modified for BC3D00262
 *
************************************************************************/

#ifndef _PPP_CORE_DEF_H_
#define _PPP_CORE_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ppp/include/ppp_api.h"

/*地址族类型,由socket.h提供，暂时*/
#ifndef AF_INET
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#endif

#ifndef AF_INET6
#define AF_INET6        29
#endif
#ifndef AF_IPX
#define AF_IPX          23              /* Novell网络协议 Novell Internet Protocol */
#endif


#ifndef MIN
#define MIN(a, b)       ((a)>(b) ? (b):(a)) 
#endif

/* 零散宏定义 *******************************************************************/
#define TCPIP_PPP_FAC 0

#define PPP_DEBUGSWITCH_ERROR 0xFF

#define PPP_DEF_MAX_CTLNUM 64
#define RTM_CREATE      0x01    /* 接口、虚链路创建*/
#define RTM_DEL         0x02    /* 接口、虚链路删除*/
#define MIB_MAC_LEN 6
#define IFTABLE 1

#define PPP_MAX_NEG_TIME 600            /*用户指定的最大的协商时间*/
#define PPP_TIMEINIT     (ULONG)~0x0    /* 0xFFFFFFFF,ppp控制块上计时初始值(无效) */
#define PPP_TIMEDONE     (ULONG)~0x1    /* 0xFFFFFFFE,ppp控制块上计时为PPP_TIMEDONE,表示已经对外告警过了 */
#define PPP_INVALID_STATE 0xFFFFFFFF  /* ppp控制块协商无效状态 */
#define PPP_MUXCP_DISABLE   0xFF       /* pppMux未使能协商状态值*/
/*******************************************************************************/


/************************* 与规格有关的宏 (Begin)*****************************/

#define PPP_MAXAUTHFAILTIMES        3

#define PPP_MAXTRANSFAILEDTIMES     5
#define PPP_DEF_MP_FRAGS            4
#define PPP_DEF_MP_BINDS            4

#define PPP_GETCOUNTPERTIME 200   /* 一次调度最多处理的报文数 */

#define PPP_QUE_REGLEN      1024    /*  队列的缺省注册长度  shiyong 2000/10/10  */
#define PPP_MAXQUELEN       1024

#define PPP_ECHOTIMEOUT     10000    /* 10000毫秒   ten seconds in milliseconds */
#define PPP_ECHOSENDTIME    PPP_ECHOTIMEOUT  /* same as echo timeout */

#define PPP_MAXMRU          2000    /* maximum MRU */

#define PPP_DEFMRU          1500    /*缺省MRU default MRU */

#define PPP_MINMRU          46      /* minimum MRU */

#define PPP_DEFTIMEOUTTIME  3000L   /* Timeout time in milliseconds */
#define PPP_MAXTIMEOUTTIME  10000L  /* Timeout time in milliseconds */

#define PPP_DEFMAXCONFREQS  5       /* 最大的CR报文重传次数    Maximum Configure-Request transmissions */

#define PPP_MAXTERMREQS     5       /* 最大的TR报文重传次数   Maximum Terminate-Request transmissions */
#define PPP_MAXNAKLOOPS     10      /* NAK环的最大次数  Maximum number of nak loops */
#define PPP_MAXLOOPSBACK    10      /* 最大环回检测次数 Maximum number of loopsback */


#define PPP_MINLOOPSBACK    3       /* 最小环回检测次数 */


#define PPP_AUTH_MAXTRANSMITS  10   /* PAP&&CHAP 验证最大重传次数 */

#define PPP_DEF_RESETTIME   30000L

#define PPP_DEFMRRU  1500
#define PPP_MINMRRU  128            /* 最小允许的MRRU值  No MRUs below this is allowed */


/*最大用户数*/
#define MP_MAX_USER_NUM        200
#define MAX_HOT_SLOT_USER_NUM  20   /* 热插拔的最大下发用户数目 */
/*用户名长度*/
#define MP_USERNAME_LEN        PPP_MAXUSERNAMELEN

#define NOAUTH_NODISCR         1    /* 直接绑定 */
#define DISCR_NOAUTH           2    /* 终端描述符绑定 */
#define NODISCR_AUTH           3    /* 用户名绑定 */
#define DISCR_AUTH             4    /* 终端描述符、用户名绑定 */

#define MPGROUP_BIND            0
#define NOBIND_MP               5
/*不存在指定的子通道*/
#define NOSUCHSUBCHANNEL        0

#define PPP_DEFAULT_ACCM  0xffffffff  /* 缺省同异步转换字符集，所有控制字都转换 */

#define MP_SSNHF_ENABLE              1  /* 使能协商SSNHF选项 */
#define MP_SSNHF_DISNABLE            0  /* 去使能协商SSNHF选项 */
#define MC_MHF_ENABLE                1  /* 使能协商MHF选项 */
#define MC_MHF_DISNABLE              0  /* 去使能协商MHF选项 */
#define MC_PREFIX_ELISION_ENABLE     1  /* 使能协商Prefix-Elision选项 */
#define MC_PREFIX_ELISION_DISNABLE   0  /* 去使能协商Prefix-Elision选项 */
#define PREFIX_E_IS_USED             1  /* 该等级存在前缀省略映射关系 */
#define PREFIX_E_NO_USED             0  /* 该等级不存在前缀省略映射关系 */

#define MC_MAX_LSCLASS              16  /* 长序列头格式支持的最大等级数 */
#define MC_DEF_LSCLASS               8  /* 长序列头格式默认支持的等级数 */
#define MC_MAX_SSCLASS               4  /* 短序列头格式支持的最大等级数 */
#define MC_LSN_CODE                  2  /* 长序列格式的code值 */
#define MC_SSN_CODE                  6  /* 短序列头格式的code值 */
#define MC_PREFIXE_MAX_STR           8  /* 前缀省略字段的最大长度 */

/*Begin BC3D01936 同步BC3D01705 liangjicheng 2009-08-24*/
/* 资源核查时，一次检查的最多接口数，用户配置时不能超过这个数 */
#define PPP_MAX_VERIFY_IFNUM    128
/*End BC3D01936*/

/************************* 与规格有关的宏 (End)*****************************/


/************************* 可配置规格的配置默认值 (Begin)*************************/

#define PPP_DEF_NEED_PAP      0x0   /* 缺省: 不需要PAP验证 */

#define PPP_DEF_NEED_CHAP     0x0   /* 缺省: 不需要CHAP验证 */

#define PPP_DEF_NEED_LOOPNEGO  0x1   /* 缺省: 继续协商*/

/* Liqiang17164  实现CDMA BSC产品需求 2003-10-25 */
#define PPP_DEF_NEED_NCP       0x1   /* 缺省: 启用NCP协商*/

/* Liqiang 实现智能光网产品需求 2003-12-17 */
#define PPP_DEF_NEED_LCP       0x1   /* 缺省: 启用LCP协商*/
#define PPP_DEF_NEED_OSICP     0x1   /* 是否协商OSICP直接上报UP，默认为1，协商 */
/* 注意: 如果LCP协商不通过, 且不断出现PPP_STATE_REQSENT, 则增大Timeout时间 *
 *       希望以后可以实现在协商过程中如果出现超时, 则下次自动调节超时时间  */
#define PPP_DEF_NEGO_TIMEOUT  6000L  /* 缺省: 缺省Timeout时间(6秒) */
/*x36317 Trace item No：D00519根据CDMA WLL的需求,将Timeout 时间的最大值调高到30秒,2004-6-8*/
#define PPP_MAX_NEGO_TIMEOUT  30000L /* 最大Timeout时间(30秒) */

#define PPP_DEF_ECHO_TIMEOUT  10000L /* 缺省: 缺省Echo超时时间(10秒) */
#define PPP_DEF_ECHO_SENDTIME PPP_DEF_ECHO_TIMEOUT /* 与Echo超时时间相同 */
#define PPP_DEFAULT_KEEPALIVE PPP_DEF_ECHO_TIMEOUT /* 链路层协商用和链路层探测链路状态用 */

#define PPP_DEF_CONFREQS      5     /* 缺省: 5次  */
#define PPP_MAX_CONFREQS      10    /* 最大: 10次 */

#define PPP_DEF_NAKLOOPS      10
#define PPP_MAX_NAKLOOPS      10
#define PPP_MAX_LOOPSBACK     10    /* Maximum number of nak loops */

/*是否创建PPP异步报文队列，缺省为不创建*/
#define PPP_NEED_ASYQUE    1
#define PPP_NO_ASYQUE      0

/* 是否协商网络层协议，默认都协商 */
#define PPP_NEGO_NPROTO_ALL   0xFFFFFFFF
#define PPP_NEGO_NPROTO_IPCP  0x1
#define PPP_NEGO_NPROTO_OSICP 0x2

/************************* 可配置规格的配置默认值 (End)*************************/


/************************* 事件枚举变量 (Begin)*****************************/

/* 外壳向内核报事件 */
enum enumPPP_EVENT_ShellToCore
{
    PPPISLUP = 0,
    PPPISLDOWN,
    PPPCHGIPADDR,
    PPPADDIPADDR,
    PPPDELIPADDR,
    PPPADDIP6LINKLOCALADDR,  /*增加LINKLOCAL地址*/
    PPPDELIP6LINKLOCALADDR,  /*删除LINKLOCAL地址*/
    PPPCHGIPXADDR,
    PPPADDIPXADDR,
    PPPDELIPXADDR,
    PPPADDIPISIS,
    PPPDELIPISIS,

    PPPISDOWNALL,
    PPPENABLEPPPMUX,  /*使能PPP MUX*/
    PPPDISABLEPPPMUX, /*去使能PPP MUX*/
    /* End of addition */

    /* add by L00105073 for BC3D01546，协商来的地址与本机其他接口地址有冲突时删除 */
    PPPDELIPADDFORINVALID,

    PPPMAX_END
};

/* 状态机事件 */
enum enumPPP_EVENT_FSM
{
    /* 外部事件 */
    PPP_EVENT_FSM_UP = 0,
    PPP_EVENT_FSM_DOWN,
    PPP_EVENT_FSM_OPEN,
    PPP_EVENT_FSM_CLOSE,
    /* 定时器事件 */
    PPP_EVENT_FSM_TO_PLUS,
    PPP_EVENT_FSM_TO_SUB,
    /* 报文事件 */
    PPP_EVENT_FSM_RCR_PLUS,
    PPP_EVENT_FSM_RCR_SUB,
    PPP_EVENT_FSM_RCA,
    PPP_EVENT_FSM_RCN,
    PPP_EVENT_FSM_RTR,
    PPP_EVENT_FSM_RTA,
    PPP_EVENT_FSM_RUC,
    PPP_EVENT_FSM_RXJ_PLUS,
    PPP_EVENT_FSM_RXJ_SUB,
    PPP_EVENT_FSM_RXR
};

enum emumPPP_ACTION_FSM
{
    PPP_ACTION_FSM_TLU = 1,
    PPP_ACTION_FSM_TLD,
    PPP_ACTION_FSM_TLS,
    PPP_ACTION_FSM_TLF,
    PPP_ACTION_FSM_IRC,
    PPP_ACTION_FSM_ZRC,
    PPP_ACTION_FSM_SCR,
    PPP_ACTION_FSM_SCA_SCN,
    PPP_ACTION_FSM_STR,
    PPP_ACTION_FSM_STA,
    PPP_ACTION_FSM_SCJ,
    PPP_ACTION_FSM_SER,
    PPP_ACTION_FSM_SDR,
    PPP_ACTION_FSM_MAX,
};

/* 协议向内核报的事件 */
enum enumPPP_EVENT_ProtocolToCore
{
    PPP_EVENT_LCPUP = 0,
    PPP_EVENT_LCPDOWN,
    PPP_EVENT_LCPFINISHED,
    PPP_EVENT_LCPSTARTING,
    PPP_EVENT_IPCPUP,
    PPP_EVENT_IPCPDOWN,
    PPP_EVENT_IPCPFINISHED,
    PPP_EVENT_IPCPSTARTING,

    PPP_EVENT_IPXCPUP,
    PPP_EVENT_IPXCPDOWN,
    PPP_EVENT_IPXCPFINISHED,
    PPP_EVENT_IPXCPSTARTING,

    PPP_EVENT_CCPUP,
    PPP_EVENT_CCPDOWN ,
    PPP_EVENT_CCPFINISHED,
    PPP_EVENT_CCPSTARTING,
    PPP_EVENT_PAPSUCCESS,
    PPP_EVENT_PAPFAILED,
    PPP_EVENT_CHAPSUCCESS,
    PPP_EVENT_CHAPFAILED,
    PPP_EVENT_RECHALLENGE,
    PPP_EVENT_OSICPUP,
    PPP_EVENT_OSICPDOWN,
    PPP_EVENT_OSICPFINISHED,
    PPP_EVENT_OSICPSTARTING,
    PPP_EVENT_MPLSCPUP,
    PPP_EVENT_MPLSCPDOWN,
    PPP_EVENT_MPLSCPFINISHED,
    PPP_EVENT_MPLSCPSTARTING,

    PPP_EVENT_IP6CPUP,
    PPP_EVENT_IP6CPDOWN,
    PPP_EVENT_IP6CPFINISHED,
    PPP_EVENT_IP6CPSTARTING,
    PPP_EVENT_IP6CP_SET_INTERFACE_ID,

    PPP_EVENT_MUXCPUP ,
    PPP_EVENT_MUXCPDOWN ,
    PPP_EVENT_MUXCPFINISHED ,
    PPP_EVENT_MUXCPSTARTING ,
    /* End of addition */

    PPP_EVENT_MAXEVENT
};

/* 内核向外壳报的事件 */
enum enumPPP_EVENT_CoreToShell
{
    /* 支持np xiehuaguo add for support np 2006-05-08 */
    PPP_LCP_UP = 0,
    PPP_LCP_DOWN ,
    PPP_IPCP_UP,
    PPP_IPCP_DOWN,

    PPP_IP6CP_UP,
    PPP_IP6CP_DOWN,
    PPP_IP6CP_GET_LINKLOCAL_ADDR,
    PPP_IP6CP_SET_INTERFACEID,

    PPP_GET_IPADDR,
    PPP_GET_PEERIPADDR,
    PPP_FREE_PEERIPADDR,
    PPP_IPXCP_UP,
    PPP_IPXCP_DOWN,
    PPP_GET_IPXADDR,
    PPP_SET_ACCM,
    PPP_OSICP_UP,
    PPP_OSICP_DOWN,
    PPP_OSICP_ENABLE

    ,PPP_MUXCP_UP,
    PPP_MUXCP_DOWN
    /* End of addition */
};

/* PPP RPC 通信消息 */
enum enumPPP_IPC_MSG
{
   PPP_HOT_INSERT_SLOT ,
   PPP_HOT_INSERT_POINTER
};

/************************* 事件枚举变量 (End)*****************************/


/* 调试信息级别宏,以后应替换掉 */
#define PPP_LOG_INFO    0
#define PPP_LOG_WARNING 1
#define PPP_LOG_NOTICE  2
#define PPP_LOG_ERROR   3


/**************************** PPP阶段 *********************************/
enum enumPppPhase
{
    PPP_PHASE_DEAD = 0,       /* 0  链路不可用阶段   Dead Phase */
    PPP_PHASE_ESTABLISH,      /* 1  链路建立阶段     Establish Phase */
    PPP_PHASE_AUTHENTICATE,   /* 2  验证阶段         Authenticate Phase */
    PPP_PHASE_CBCP,           /* 3                   Cbcp Phase */
    PPP_PHASE_NETWORK,        /* 4  网络层协议阶段   Network Phase */
    PPP_PHASE_TERMINATE       /* 5  链路终止阶段     Terminate Phase */
};

/**************************** PPP阶段 *********************************/
enum ePppPhase
{
    PPP_DEAD_PHASE = 1,       /* 1  链路不可用阶段    Dead Phase */
    PPP_ESTABLISH_PHASE,      /* 2  链路建立阶段      Establish Phase */
    PPP_AUTHENTICATE_PHASE,   /* 3  验证阶段          Authenticate Phase */
    PPP_CBCP_PHASE,           /* 4                    Cbcp Phase */
    PPP_NETWORK_PHASE,        /* 5  网络层协议阶段    Network Phase */
    PPP_TERMINATE_PHASE       /* 6  链路终止阶段      Terminate Phase */
};

/* PPP协商类型  PPP Nego Type */
enum ePppNegoType
{
    PPP_NEGO_LCP = 1,    /* 1  PPP链路控制协商   PPP LCP Negotiation */
    PPP_NEGO_NCP         /* 2  PPP网络控制协商   PPP IPCP Negotiation */
};


/********************** PPP报文各部分长度 *****************************/
#define FSM_HDRLEN  4     /* 协议字节数 octets for every protocol, code+ID+length*/
#define PPP_HDRLEN  4     /* 标准ppp头字节数 octets for standard ppp header ff+03+protocol*/
#define PPP_FCSLEN  2     /* FCS字节数 octets for FCS */

/* PPP首部压缩  Added by z43740 for PPP HeaderCompression, 2006/05/12*/
#define PPP_HDRLEN_MIN 1  /* 最小PPP首部长度 */
/*
|--------- PPP_HDRLEN ----------|--------- FSM_HDRLEN ----------|
0       1       2       3       4       5       6       7       8
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|   ff  |   03  |    protocol   |  code |   ID  |     length    |  data...
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

/* 各协议通用的协商选项长度 */
#define PPP_CILEN_VOID      2   /* PPP ci type + ci length */
#define PPP_CILEN_SHORT     4   /* PPP_CILEN_VOID + sizeof(short) */
#define PPP_CILEN_LONG      6   /* PPP_CILEN_VOID + sizeof(long) */

/* 各协议通用的获取协商选项长度(cilen)宏 */
#define PPP_LENCIVOID(neg)      (neg ? PPP_CILEN_VOID : 0)
#define PPP_LENCISHORT(neg)     (neg ? PPP_CILEN_SHORT : 0)
#define PPP_LENCILONG(neg)      (neg ? PPP_CILEN_LONG : 0)
/********************** PPP报文各部分长度 *****************************/


/************************ IPCP模块 *****************************/
/* 各协商选项长度 */
#define PPP_CILEN_COMPRESS  4   /* 压缩协商选项最小长度  min length for compression protocol opt. */
#define PPP_CILEN_VJ        6   /* RFC1332压缩算法选项长度  length for RFC1332 Van-Jacobson opt. */
#define PPP_CILEN_ADDR      6   /* 新型单地址选项  new-style single address option */
#define PPP_CILEN_ADDRS     10  /* 老式偶地址选项  old-style dual address option */
/************************ IPCP模块 *****************************/


/************************ IPXCP模块 *****************************/
/* 各协商选项长度 */
#define PPP_CILEN_NODE      8   /* IPX节点数目选项长度  length for IPX Node Number opt. */
#define PPP_CILEN_ROUTING   4   /* 路由协商选项最小长度  min length for routing protocol opt. */
#define PPP_CILEN_ROUTER    3   /* 压缩协商选项最小长度  min length for compression protocol opt. */
/************************ IPXCP模块 *****************************/


/************************* 报文类型 **********************************/
#define PPP_MP             0x003d
#define PPP_IP             0x0021
#define PPP_OSI            0x0023
#define PPP_IPX            0x002b

#define PPP_IP6                 0x0057
#define PPP_INTERFACELEN        8
#define PPP_MACADDRLEN          6
#define PPP_INTERFACENUMLEN     2
#define PPP_RANDOMLEN           4

#define PPP_IPHC                0x0061      /* IP首部压缩 IP header compress */

#define PPP_VJ_COMP             0x002d
#define PPP_VJ_UNCOMP           0x002f
#define PPP_VJ_COMP_OLD         0x0037
#define PPP_COMP                0x00fd          /* 压缩包 compressed packet */

#define PPP_PPPMUX              0x0059          /* PPP多路复用 PPP Multiplexing  */

#define PPP_IPXCP               0x802b          /* IPX控制选项 IPX Control Protocol */
#define TELEBIT_COMPRESS        0x0002          /* Telebit压缩  Telebit Compressed IPX */
#define SHIVA_COMPRESS          0x0235          /* Shiva压缩  Shiva Compressed NCP/IPX */
#define PPP_CCP                 0x80fd          /* 压缩控制协议  Compression Control Protocol */
#define PPP_PAP                 0xc023          /* 密钥认证协议  P***W*** Authentication Protocol */
#define PPP_LQR                 0xc025          /* 链路质量报告协议  Link Quality Report protocol */
#define PPP_CHAP                0xc223          /* 挑战握手报文认证协议  Cryptographic Handshake Auth. Protocol */
#define PPP_BCP                 0x8031          /* ppp网桥控制协议  ppp bridge control protocol */
#define PPP_BP                  0x0031          /* ppp网桥协议  PPP bridge protocol */
#define PPP_SCCP                0x80fd          /* 单链路ppp压缩控制协议 ppp compress control protocol on single link */
#define PPP_SCP                 0x00fd          /* 单链路ppp压缩协议 ppp compress protocol on single link */
#define PPP_MCCP                0x80fb          /* 多链路ppp压缩控制协议 ppp compress control protocol on multilink  */
#define PPP_MCP                 0x00fb          /* 多链路ppp压缩协议 PPP compress protocol on multilink */
#define PPP_SECP                0x8053          /* 单链路pppenc 控制协议 ppp enc control protocol on single link */
#define PPP_SEP                 0x0053          /* 单链路pppenc 协议 PPP enc protocol on single link */
#define PPP_MECP                0x8055          /* 多链路pppenc 控制协议 PPP enc control protocol on multilink */
#define PPP_MEP                 0x0055          /* 多链路pppenc 协议 PPP enc protocol on multilink */
#define PPP_BACP                0xc02b          /* 带宽配置控制协议 Bandwidth Allocation Control Protocol */
#define PPP_BAP                 0xc02d          /* 带宽控制协议 Bandwidth Control Protocol */
#define PPP_CBCP                0xc029          /* 回叫控制协议 Callback Control Protocol */
#define PPP_OSI_NPDU            0x0023          /* 开放系统互连网络协议数据单元协议 OSI NPDU(Network Protocol Data Unit) Protocol */
#define PPP_MPLSCP              0x8281          /* 多协议标记交换控制协议 MPLS Control Protocol */
#define PPP_MPLS_UNICAST        0x0281          /* 单点传输报文 MPLS unicast packet */
#define PPP_MPLS_MULTICAST      0x0283          /* 多点传输报文 MPLS multicast packet */

/*add by wht06310 for debugsort*/
#define PPP_LCP_ECHO            0xc022

/************************* 报文类型 **********************************/

/* 
 * Significant octet values.
 */
#define PPP_ALLSTATIONS 0xff        /* 广播地址 All-Stations broadcast address */
#define PPP_UI          0x03        /* 未编号信息 Unnumbered Information */
#define PPP_FLAG        0x7e        /* 标记序列 Flag Sequence */
#define PPP_ESCAPE      0x7d        /* escape异步控制 Asynchronous Contro Escape */
#define PPP_TRANS       0x20        /* 异步透明修正 Asynchronous transparency modifier */


/* 预留的报文头大小 */
#define PPP_RESERVED_PACKET_HEADER  40
/* 由于增加前缀省略，导致LCP协商报文的长度可能超过200字节，现增加到256字节 */
#define PPP_DEFAULT_NEGO_PACKET_LEN 256

/* MP通道类型 */
#define PPP_MP_NONE          0          /* 不是MP */
#define PPP_MP_SUBCHANNEL    1          /* MP子通道 */
#define PPP_MP_FATHER        2          /* MP父通道 */
#define PPP_MP_TEMPLATE      3          /* MP模版 */

#define PPP_MP_DISCR_LOCASSIGN_LEN  6   /* 本地分配的终端描述符号长度 */

/* 验证消息类型 */
#define PPP_AUTH_ACCEPT      0
#define PPP_AUTH_FAILED      1

/* NP获取PPP LCP Echo相关信息 */
#define PPPISHANDLELCPECHO  0        /* VISP是否发送和处理保活报文 */
#define PPPGETLCPECHOINFO  1         /* 获取LCP OPEN状态下Echo相关信息 */

/* 定义无效的定时器ID宏 */
#define PPP_INVALID_TIMERID  0

/* 定义NCP延时补发一个CR报文定时器最小和最大值 */
#define PPP_NCP_NEGO_DELAY_MIN 1
#define PPP_NCP_NEGO_DELAY_MAX 6000

/*************************** 报文读、写宏 (Begin)****************************/
/* 移动指针报文 */
#define PPP_INCPTR(n, cp)   ((cp) += (n))
#define PPP_DECPTR(n, cp)   ((cp) -= (n))

/*
* Inline versions of get/put char/short/long.
* Pointer is advanced; we assume that both arguments
* are lvalues and will already be in registers.
* 假设两元素均为左计算，并且已经存在缓存器中
* cp MUST be UCHAR *. cp的类型必须为UCHAR型
*/

#define PPP_GETCHAR(c, cp) { \
    (c) = *(cp); \
    (cp) ++ ; \
}
#define PPP_PUTCHAR(c, cp) { \
    *(cp) = (UCHAR) (c); \
    (cp) ++ ; \
}

#ifdef TCPIP_SUPPORT_ARMCPU
#define PPP_GETSHORT(s, cp) { \
    /*modify by w62223 for coverity warning-type:UNINIT*/ \
    USHORT usPosShift = 0;\
    (VOID)TCPIP_Mem_Copy((VOID *)&(usPosShift), sizeof(USHORT), (VOID *)&(*(USHORT*)cp), sizeof(USHORT));\
    (s) = VOS_NTOHS(usPosShift);\
    (cp) += sizeof(USHORT) ; \
}
#define PPP_PUTSHORT(s, cp) { \
    USHORT usPosShift = 0;\
    usPosShift = s;\
    (usPosShift) = (USHORT)VOS_HTONS(usPosShift);\
    (VOID)TCPIP_Mem_Copy((VOID *)&(*((USHORT*)cp)), sizeof(USHORT), (VOID *)&(usPosShift), sizeof(USHORT));\
    (cp) += sizeof(USHORT) ; \
}
#define PPP_GETLONG(l, cp) { \
    ULONG ulPosShift = 0;\
    (VOID)TCPIP_Mem_Copy((VOID *)&(ulPosShift), sizeof(ULONG), (VOID *)&(*((ULONG *)cp)), sizeof(ULONG));\
    (l) = VOS_NTOHL(ulPosShift);\
    cp += sizeof(ULONG) ; \
}
#define PPP_PUTLONG(l, cp) { \
    ULONG ulPosShift = 0;\
    ulPosShift = l;\
    (ulPosShift) = (ULONG)VOS_HTONL(ulPosShift);\
    (VOID)TCPIP_Mem_Copy((VOID *)&(*((ULONG*)cp)), sizeof(ULONG), (VOID *)&(ulPosShift), sizeof(ULONG));\
    cp += sizeof(ULONG) ; \
}
#else
#define PPP_GETSHORT(s, cp) { \
    (s) = (USHORT)VOS_NTOHS((*(USHORT*)cp)); \
    (cp) += sizeof(USHORT) ; \
}
#define PPP_PUTSHORT(s, cp) { \
    *((USHORT*)cp) = (USHORT)VOS_HTONS(s); \
    (cp) +=sizeof(USHORT) ; \
}

/* Zhukun Modified,D00816: 添加字节序转换 */
#define PPP_GETLONG(l, cp) { \
    (l) = VOS_NTOHL(*((ULONG *)cp)); \
    cp += sizeof(ULONG) ; \
}
#define PPP_PUTLONG(l, cp) { \
    *((ULONG*)cp) = VOS_HTONL(l) ; \
    cp += sizeof(ULONG) ; \
}
#endif
/* PPP首部压缩  Added by z43740 for PPP HeaderCompression,2006/05/12 */
#define PPP_HDRLEN_PF(bNegPfc,usProtocol) \
    (bNegPfc ? ((usProtocol & 0xff00) ? 2:1) : 2)

#define PPP_HDRLEN_ACF(bNegAcfc) (bNegAcfc ? 0:2)

#define PPP_MAKEPF(bPfc, p, t) \
{ \
    if (PPP_LCP == t) \
    { \
        PPP_PUTSHORT(t, p); \
    } \
    else if (bPfc && !(t & 0xff00) ) \
    { \
        PPP_PUTCHAR((UCHAR)t,p); \
    } \
    else \
    { \
        PPP_PUTSHORT(t, p); \
    } \
}
/* End of addition */

/*
 * 为报文增加首部
 * PPP_MAKEHEADER - Add Header fields to a packet.
 */
/* PPP首部压缩  Modified by z43740 for PPP HeaderCompression,2006/05/12*/
#define PPP_MAKEHEADER(bPfc,bAcfc,p, t) \
{ \
    if ((PPP_LCP == t) || (!bAcfc)) \
    { \
        PPP_PUTCHAR(PPP_ALLSTATIONS, p); \
        PPP_PUTCHAR(PPP_UI, p); \
    } \
    PPP_MAKEPF(bPfc,p,t); \
}

/* 分配前缀省略映射表并进行内容拷贝 */
#define PPP_COPYPREFIXE(pstPppInfo, pstDestInfo, pstSrcInfo)\
{\
    if ( NULL == pstDestInfo->pstPrefixE )\
    {\
        pstDestInfo->pstPrefixE = (MC_PREFIXE_S *)TCPIP_Malloc(g_stPPPModInfo.ulMID_PPP | g_stPPPModInfo.ulSID_PPP_CB_S, \
                                                             sizeof(MC_PREFIXE_S)*MC_PREFIXE_MAX_NUM);\
        if ( NULL == pstDestInfo->pstPrefixE )\
        {\
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Malloc Prefix-Elision CB error!!");\
        }\
    }\
    if ( pstDestInfo->pstPrefixE )\
    {\
        if ( pstSrcInfo->pstPrefixE )\
        {\
            (VOID)TCPIP_Mem_Copy(pstDestInfo->pstPrefixE, sizeof(MC_PREFIXE_S)*MC_PREFIXE_MAX_NUM, pstSrcInfo->pstPrefixE, sizeof(MC_PREFIXE_S)*MC_PREFIXE_MAX_NUM);\
        }\
        else\
        {\
            (VOID)TCPIP_Mem_Set((CHAR *)pstDestInfo->pstPrefixE, 0, sizeof(MC_PREFIXE_S)*MC_PREFIXE_MAX_NUM);\
        }\
    }\
}


/* 由于在PPP_LCP_OPTION_S和PPPCONFIGINFO_S结构中增加了前缀省略映射表指针，
   所以在进行内容拷贝时不能简单的结构赋值，要对前缀省略映射表指针作特殊处理 */
#define PPP_COPYINFOBYPREFIXE(pstPppInfo, opt, pstDestInfo, pstSrcInfo)\
{\
    if ( opt )\
    {\
        /* 将SrcLcpOption中内容拷贝到DestLcpOption中，除前缀省略映射表指针所占4个字节外 */\
        (VOID)TCPIP_Mem_Copy(pstDestInfo, sizeof(*pstDestInfo), pstSrcInfo, sizeof(*pstDestInfo)-LEN_4);\
        PPP_COPYPREFIXE(pstPppInfo, pstDestInfo, pstSrcInfo);\
    }\
    else\
    {\
        if ( pstDestInfo->pstPrefixE )\
        {\
            (VOID)TCPIP_Free(pstDestInfo->pstPrefixE);\
            pstDestInfo->pstPrefixE = NULL;\
        }\
        /* 如果不存在前缀省略映射表，则可直接拷贝内容 */\
        (VOID)TCPIP_Mem_Copy(pstDestInfo, sizeof(*pstDestInfo), pstSrcInfo, sizeof(*pstDestInfo));\
    }\
}


/*************************** 报文读、写宏 (End)****************************/


#define PPP_NEED_NEGO      1
#define PPP_NOT_NEED_NEGO  0


/**********************/
/* 状态机模块的宏定义 */
/**********************/

/***************************** code值 ********************************/
/*
 *  CP (LCP, IPCP, etc.) codes.
 */
#define CONFREQ   1   /* 配置请求 Configuration Request */
#define CONFACK   2   /* Ack配置 Configuration Ack */
#define CONFNAK   3   /* Nak配置 Configuration Nak */
#define CONFREJ   4   /* 拒绝配置 Configuration Reject */
#define TERMREQ   5   /* 终止请求 Termination Request */
#define TERMACK   6   /* ACK终止 Termination Ack */
#define CODEREJ   7   /* 代码拒绝 Code Reject */
#define PROTREJ   8   /* 协议拒绝 Protocol-Reject */
/***************************** code值 ********************************/


/****************************** 状态 *********************************/
/* FSM states */
enum ePppState
{
    PPP_STATE_INITIAL = 0,  /* 0   down，没有打开 Down, hasn't been opened */
    PPP_STATE_STARTING,     /* 1   down，已经打开 Down, been opened */
    PPP_STATE_CLOSED,       /* 2   up，没有打开 Up, hasn't been opened */
    PPP_STATE_STOPPED,      /* 3   open，等待down事件 Open, waiting for down event */
    PPP_STATE_CLOSING,      /* 4   终止连接，没有打开 Terminating the connection, not open */
    PPP_STATE_STOPPING,     /* 5   终止，打开 Terminating, but open */
    PPP_STATE_REQSENT,      /* 6   发送一个拒绝配置 We've sent a Config Request */
    PPP_STATE_ACKRCVD,      /* 7   接受一个ACK配置 We've received a Config Ack */
    PPP_STATE_ACKSENT,      /* 8   发送一个ACK配置 We've sent a Config Ack */
    PPP_STATE_OPENED        /* 9   可以连接 Connection available */
};

#define PPP_TUNNEL_TYPE_L2TP  3

/*这三种用户类型属于PPP*/
#define PPP_USERTYPE_PPP               0x0010
#define PPP_USERTYPE_L2TP              0x0050


/************************ PPP 状态机状态转换图 (Begin)***********************/
/*
           | State状态
           |  0           1        2          3         4         5           6         7         8           9
Events 事件| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
             状态       状态     状态       状态      状态      状态      状态        状态     状态        状态
-----------+------------------------------------------------------------------------------------------------------
 Up   事件|    2     irc,scr/6     -         -         -         -          -         -         -           -
 Down 事件|    -         -       0       tls/1       0         1          1         1         1         tld/1
 Open 事件|  tls/1       1     irc,scr/6     3r        5r        5r         6         7         8           9r
 Close事件|    0       tlf/0       2         2         4         4      irc,str/4  irc,str/4   irc,str/4    tld,irc,str/4
          |
  TO+ 事件|    -         -         -         -      str/4     str/5     scr/6    scr/6     scr/8         -
  TO- 事件|    -         -         -         -       tlf/2     tlf/3      tlf/3p    tlf/3p    tlf/3p        -
          |
 RCR+ 事件|    -         -    sta/2   irc,scr,sca/8     4         5        sca/8   sca,tlu/9   sca/8    tld,scr,sca/8
 RCR- 事件|    -         -    sta/2   irc,scr,scn/6     4         5        scn/6     scn/7     scn/6   tld,scr,scn/6
 RCA  事件|    -         -    sta/2     sta/3         4         5        irc/7     scr/6x  irc,tlu/9    tld,scr/6x
 RCN  事件|    -         -    sta/2     sta/3         4         5      irc,scr/6   scr/6x  irc,scr/8    tld,scr/6x
          |
 RTR  事件|    -         -    sta/2     sta/3        sta/4     sta/5      sta/6     sta/6     sta/6    tld,zrc,sta/5
 RTA  事件|    -         -      2         3         tlf/2     tlf/3        6         6         8      tld,scr/6
          |
 RUC  事件|    -         -    scj/2     scj/3        scj/4     scj/5      scj/6     scj/7     scj/8       scj/9
 RXJ+ 事件|    -         -      2         3          4         5          6         6         8           9
 RXJ- 事件|    -         -     tlf/2     tlf/3         tlf/2     tlf/3       tlf/3     tlf/3     tlf/3       tld,irc,str/5
          |
 RXR  事件|    -         -      2         3          4         5          6         7         8      ser/9
*/

/* 事件(Events)和动作(Actions)说明:
   Events                                   Actions

   Up   = lower layer is Up                 tlu = This-Layer-Up
          下层up                                  本层up
   Down = lower layer is Down               tld = This-Layer-Down
          下层down                                本层down
   Open = administrative Open               tls = This-Layer-Started
          管理打开                                本层开始
   Close= administrative Close              tlf = This-Layer-Finished
          管理关闭                                本层结束

   TO+  = Timeout with counter > 0          irc = Initialize-Restart-Count
          count大于零超时                         初始化重新开始
   TO-  = Timeout with counter expired      zrc = Zero-Restart-Count
          count过期超时

   RCR+ = Receive-Configure-Request (Good)  scr = Send-Configure-Request
          接收CR报文                              发送CR报文
   RCR- = Receive-Configure-Request (Bad)
   RCA  = Receive-Configure-Ack             sca = Send-Configure-Ack
          接收配置ACK                             发送配置ACK
   RCN  = Receive-Configure-Nak/Rej         scn = Send-Configure-Nak/Rej
          接收配置NAK/Rej                         发送配置NAK/Rej
   RTR  = Receive-Terminate-Request         str = Send-Terminate-Request
          接收请求                                发送终止请求
   RTA  = Receive-Terminate-Ack             sta = Send-Terminate-Ack
          接收终止ACK                             发送终止ACK

   RUC  = Receive-Unknown-Code              scj = Send-Code-Reject
          接收未知编码                            发送编码拒绝
   RXJ+ = Receive-Code-Reject (permitted)
          接收编码拒绝（允许）
       or Receive-Protocol-Reject
       或 接收协议拒绝
   RXJ- = Receive-Code-Reject (catastrophic)
       or Receive-Protocol-Reject
   RXR  = Receive-Echo-Request              ser = Send-Echo-Reply
          接收重复请求                            发送重复应答
       or Receive-Echo-Reply
       或 接收重复应答
       or Receive-Discard-Request
       或 接收丢弃请求
*/

/* 事件(Events)和动作(Actions)的处理
   对于事件：
   每个事件一个函数,+和-的事件(如RCR+和RCR-)合并为一个函数,
   因为要在函数中判断究竟是+还是-事件.

   对于动作:
   每个动作一个宏.
*/
/************************ PPP 状态机状态转换图 (End)***********************/


/************************ 状态机动作的宏定义 (Begin)*************************/

/* tlu(本层up This-Layer-Up)动作:调用回调函数up */
#define PPP_FSM_tlu(pstFsm) \
{\
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_TLU); \
    if((pstFsm->pstCallBacks != NULL) && (pstFsm->pstCallBacks->up)) \
    { \
        (*pstFsm->pstCallBacks->up)(pstFsm); \
    } \
}

/* tld(本层down This-Layer-Down)动作:调用回调函数down */
#define PPP_FSM_tld(pstFsm) \
{\
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_TLD); \
    if((pstFsm->pstCallBacks != NULL)&&(pstFsm->pstCallBacks->down)) \
    { \
        /* 报down */ \
        (*pstFsm->pstCallBacks->down)(pstFsm); \
    } \
}

/* tls(本层开始 This-Layer-Started)动作: */
#define PPP_FSM_tls(pstFsm) \
{\
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_TLS); \
    if((pstFsm->pstCallBacks != NULL) && (pstFsm->pstCallBacks->starting)) \
    { \
        (*pstFsm->pstCallBacks->starting)(pstFsm); \
    } \
}

/* tlf(本层结束 This-Layer-Finished)动作: */
#define PPP_FSM_tlf(pstFsm) \
{\
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_TLF); \
    if((pstFsm->pstCallBacks != NULL) && (pstFsm->pstCallBacks->finished)) \
    { \
        (*pstFsm->pstCallBacks->finished)(pstFsm); \
    } \
}

/* irc(初始化－重启－计数 Initialize-Restart-Count)动作: */
#define PPP_FSM_irc(pstFsm) \
{ \
    /* 转播初始化 Retransmits */ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_IRC); \
    pstFsm->sRetransmits = (SHORT)g_stPPPModInfo.ulPPP_DEF_CONFREQS;/*最大Retransmit值*/\
    /* TimeOutTime回到初始值 */ \
    /*pstFsm->ulTimeOutTime = PPP_DEFTIMEOUTTIME; 初始值 */ \
    /*pstFsm->usNakloops = 0; 不能在此处清零，否则不该清的时候也清了，*/\
    /*导致协商陷入不必要的循环。pengjimei2003/07/27*/\
}

/* zrc(置零－重启－计数 Zero-Restart-Count)动作: */
#define PPP_FSM_zrc(pstFsm) \
{ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_ZRC); \
    pstFsm->sRetransmits = 0; \
}


/* scr(发送－配置－请求 Send-Configure-Request)动作:发送报文 */
#define PPP_FSM_scr(pstFsm) \
{ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_SCR); \
    PPP_FSM_SendConfigReq(pstFsm); \
    pstFsm->ucPktId ++; \
    /* 启动定时器 */ \
    PPP_FSM_SetRetransmitTimer(pstFsm); \
}

/* sca(Send-Configure-Ack)或scn(Send-Configure-Nak/Rej)动作: */
/* ulCode代表了具体是什么报文 */
#define PPP_FSM_sca_scn(pstFsm, ucCode, ucId, pHead, pPacket, ulLen) \
{ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_SCA_SCN); \
    PPP_FSM_SendPacket(pstFsm, ucCode, ucId, pHead, pPacket, ulLen); \
}

/* str(发送－终止－请求 Send-Terminate-Request)动作 */
#define PPP_FSM_str(pstFsm) \
{ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_STR); \
    PPP_FSM_SendPacketByCode(pstFsm, TERMREQ, pstFsm->ucPktId); \
    pstFsm->ucPktId ++; \
    /* 启动定时器 */ \
    PPP_FSM_SetRetransmitTimer(pstFsm); \
}

/* sta(发送－终止－Ack Send-Terminate-Ack)动作 */
#define PPP_FSM_sta(pstFsm, ucId) \
{ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_STA); \
    PPP_FSM_SendPacketByCode(pstFsm, TERMACK, ucId); \
}

/* scj(发送－编码－拒绝 Send-Code-Reject)动作 */
#define PPP_FSM_scj(pstFsm, pHead, pPacket, ulLen) \
{ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_SCJ); \
    PPP_FSM_SendPacket(pstFsm, CODEREJ, pstFsm->ucPktId, pHead, pPacket, ulLen); \
}

/* ser(发送－返回－应答 Send-Echo-Reply)动作,只有LCP会调用这个函数 */
#define PPP_FSM_ser(pstFsm, ucId, pHead, pPacket, ulLen, ulMagicNumber) \
{ \
    UCHAR *pTemp = pPacket; \
    /* 报文情况                                                       \
    |--------FSM Head(bytes) -------|                                 \
        0       1      2       3        4       5       6       7     \
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
    |       |       |       |       |       |       |       |       | \
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
                                    |                                 \
                                    pPacket                           \
                                    pTemp                             \
    */ \
    PPP_Debug_FsmAction(pstFsm, (ULONG)PPP_ACTION_FSM_SER); \
    PPP_PUTLONG(ulMagicNumber, pTemp); \
    pstFsm->sRetransmits = (SHORT)g_stPPPModInfo.ulPPP_DEF_CONFREQS;\
    /* 报文情况                                                       \
    |--------FSM Head(bytes) -------|                                 \
        0       1      2       3        4       5       6       7     \
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
    |       |       |       |       |       Magic  Number           | \
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \
                                    |                               | \
                                    pPacket                         | \
                                                                 pTemp\
    */                                                                \
   PPP_FSM_SendPacket(pstFsm, ECHOREP, ucId, pHead, pPacket, ulLen); \
}

/************************ 状态机动作的宏定义 (End)*************************/


/************************ 与状态机有关的其他宏定义 (Begin)*************************/

/* 改变状态,对于不需要定时器的状态,删除定时器 */
/* TO事件的状态转换图 */
/*
      | State
      |    0         1         2         3         4         5           6         7         8           9
Events| Initial   Starting  Closed    Stopped   Closing   Stopping   Req-Sent  Ack-Rcvd  Ack-Sent    Opened
------+------------------------------------------------------------------------------------------------------
  TO+ |    -         -         -         -       str/4     str/5      scr/6     scr/6     scr/8         -
  TO- |    -         -         -         -       tlf/2     tlf/3      tlf/3p    tlf/3p    tlf/3p        -
*/
/* 因此,Initial、Starting、Closed、Stopped和Opened状态不用定时器,需要删除定时器,
   其他状态则保留原来的定时器 */
/* 如果在ACKRCVD状态发生TO-事件，那么是双方的链路超时时间设置太短所引起的，应该设置negotiate time时间 */
/*子协议从OPEN状态转出，需要通知备板*/
/*子协议转入OPEN状态，且非Mp子通道，对于MP子通道在绑定成功时备份*/

/* 删除重传定时器 */
#define PPP_FSM_DelRetransmitTimer(pstFsm) \
{ \
    if(pstFsm->ulTimeOutID) \
    { \
        (VOID)PPP_Timer_Delete(pstFsm->ulTimeOutID); \
        pstFsm->ulTimeOutID = 0; \
    } \
}

/* Add for DTS2011042101452, by z00166124, at 2011-04-21. 修改原因: 创建定时器的入参通过回调方式获取处理函数 */
/* 设置重传定时器 */
/* 使用循环定时器，避免因消息丢失导致状态机无法继续运行 */
#define PPP_FSM_SetRetransmitTimer(pstFsm) \
{ \
    ULONG ulRetValue; \
    PPPINFO_S *pstTempPppInfo = NULL;\
    /* 如果定时器已经创建，则不用创建 */ \
    if (0 == pstFsm->ulTimeOutID) \
    { \
        if ((NULL != (PPPINFO_S *)pstFsm->pPppInfo) && (NULL != pstFsm->pstCallBacks) && (NULL != pstFsm->pstCallBacks->timerout))\
        {\
            pstTempPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;\
            ulRetValue = PPP_Timer_Create(\
                             pstFsm->ulTimeOutTime, \
                             pstFsm->pstCallBacks->timerout, \
                             (VOID*)(UINTPTR)pstTempPppInfo->ulIfIndex, \
                             &(pstFsm->ulTimeOutID) \
                            ); \
            VOS_DBGASSERT(0 == ulRetValue); \
        }\
    } \
}

/* Add for DTS2011042101452, by z00166124, at 2011-04-21. 修改原因: 创建定时器的入参通过回调方式获取处理函数 */
/* Added by z43740 for BC3D01909,2009-08-16
   设置重传定时器,减少额外100毫秒
   避免本端重传时间和对端相同时，本端定时器先创建晚超时的情况
 */
#define PPP_FSM_SetRetransmitTimerWithLessDelay(pstFsm) \
{ \
    ULONG ulRetValue; \
    PPPINFO_S *pstPppInfo = NULL;\
    /* 如果定时器已经创建，则不用创建 */ \
    if (0 == pstFsm->ulTimeOutID) \
    { \
        if ((NULL != (PPPINFO_S *)pstFsm->pPppInfo) && (NULL != pstFsm->pstCallBacks) && (NULL != pstFsm->pstCallBacks->timerout))\
        {\
            pstPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;\
            ulRetValue = PPP_Timer_Create(\
                             pstFsm->ulTimeOutTime - g_ulPPPRestanmitDelay, \
                             pstFsm->pstCallBacks->timerout, \
                             (VOID*)(UINTPTR)pstPppInfo->ulIfIndex, \
                             &(pstFsm->ulTimeOutID) \
                            ); \
            VOS_DBGASSERT(0 == ulRetValue); \
        }\
    } \
}
/* End of addition */

/*分析config-request报文*/
#define PPP_FSM_reqci(pstFsm, pPacket, ulLen, ucCode) \
{ \
\
    if(PPP_NOT_NEED_NEGO == pstFsm->ulNeedNego)\
    {\
        ucCode = CONFACK;\
    }\
    else\
    {\
        if(pstFsm->pstCallBacks->reqci) \
        { \
            ULONG ulPacketLen = ulLen; \
            UCHAR szPacketBuf[PPP_DEFAULT_NEGO_PACKET_LEN]; /* 有足够的缓冲器临时存储数据报 enough buffer to store the nego pakcet temporarily */ \
            if(PPP_MAXNAKLOOPS <= pstFsm->usNakloops) \
            {\
                /* 无应答的循环数达到最大，如需要则备份该数据报 reaching the max nak loops, backup the packet to build REJ packet if need. */ \
                (VOID)TCPIP_Mem_Copy(szPacketBuf, PPP_DEFAULT_NEGO_PACKET_LEN, pPacket, ulLen); \
            }\
            ucCode = (*pstFsm->pstCallBacks->reqci)(pstFsm, pPacket, &ulLen); /* 解析ci请求 parse his request ci */ \
            if(CONFNAK == ucCode) \
            { \
                pstFsm->usNakloops ++; \
                if(pstFsm->usNakloops > PPP_MAXNAKLOOPS) \
                { \
                    /* NCC协商失败原因采集 */ \
                    if (NCC_PPP_ISENABLE) \
                    { \
                        PPPINFO_S *pst_PppInfo = (PPPINFO_S*)(pstFsm->pPppInfo); \
                        if (pst_PppInfo) \
                        { \
                            if (PPP_LCP == pstFsm->usProtocol) \
                            { \
                                NCC_RecordPppLcpDot(LCP_FSM_REQCI_MAXNAKTOREJ, pst_PppInfo->ulIfIndex); \
                            } \
                            else if (PPP_IPCP == pstFsm->usProtocol) \
                            { \
                                NCC_RecordPppIpcpDot(IPCP_FSM_REQCI_MAXNAKTOREJ, pst_PppInfo->ulIfIndex); \
                            } \
                        } \
                    } \
\
                    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_0E88, TCPIP_LOG_LEVEL_ERROR, LOG_TYPE_RUN, \
                          "TCPIP PPP LOG:Rej neg pkt!/nakloops:%d\n", pstFsm->usNakloops, 0, 0, 0);\
\
                    PPP_FSM_RejLOG(pstFsm, pPacket, szPacketBuf, ulLen, ulPacketLen);\
                    PPP_Debug_CoreEvent((PPPINFO_S*)pstFsm->pPppInfo, PPP_LOG_NOTICE, "reach the max nak times,reject it.\r\n");\
                    ucCode = CONFREJ; /* 无应答数目太大，则拒绝 Nak too much,then Rej */ \
                    ulLen = PPP_FSM_RebuildRejPacket(pPacket, (LONG)ulLen, szPacketBuf, (LONG)ulPacketLen); \
                } \
                else\
                {\
\
                    CHAR szBuf[LEN_192];\
                    (VOID)TCPIP_SNPRINTF0(szBuf, LEN_192, P1("the times of nak is %d\r\n", pstFsm->usNakloops));\
                    PPP_Debug_CoreEvent((PPPINFO_S*)pstFsm->pPppInfo, PPP_LOG_NOTICE, szBuf);\
                }\
            } \
            else \
            { \
                pstFsm->usNakloops = 0; \
            } \
        } \
        else \
        { \
            if(ulLen) \
            { \
                ucCode = CONFREJ; /* 拒绝所有参数 */ \
            } \
            else \
            { \
                ucCode = CONFACK; \
            } \
        } \
    }\
}

/************************ 与状态机有关的其他宏定义 (End)*************************/


/************************ 与debug有关的宏定义 (Begin)*************************/

/* 输入/输出报文标志宏 */
#define PPP_DEBUG_PACKET_IN       0
#define PPP_DEBUG_PACKET_OUT      1
#define PPP_DEBUG_PACKET_UNCOMPED 2
#define PPP_DEBUG_PACKET_FORCOMP  3
#define PPP_DEBUG_PACKET_VERBOSE_LENTH  64

/* debug命令中的类型值 */
#define PPP_DEBUG_ERROR       0
#define PPP_DEBUG_EVENT       1
#define PPP_DEBUG_PACKET      2
#define PPP_DEBUG_STATE       3
#define PPP_DEBUG_ALL         4
#define PPP_DEBUG_ACTION      5

#define PPP_DEBUG_VERBOSE     6

/* 目标机上的调试宏 */
#define PPP_DebugOutString(cDebugBuf, ulLen, pstPppInfo) \
{ \
    g_stPPPShellFun.pfPPP_ShowDebugInfo(cDebugBuf, (ULONG)(ulLen)); \
}

/************************ 与debug有关的宏定义 (End)*************************/





/**********************protocol name index*********************/
enum enPppProNameIndex
{
    PPP_PRONAMEINDEX_IP,         /* 0 */
    PPP_PRONAMEINDEX_LCP,        /* 1 */
    PPP_PRONAMEINDEX_PAP,        /* 2 */
    PPP_PRONAMEINDEX_CHAP,       /* 3 */
    PPP_PRONAMEINDEX_IPCP,       /* 4 */
    PPP_PRONAMEINDEX_IPXCP,      /* 5 */
    PPP_PRONAMEINDEX_MP,         /* 6 */
    PPP_PRONAMEINDEX_BCP,        /* 7 */
    PPP_PRONAMEINDEX_BRIDGE,     /* 8 */
    PPP_PRONAMEINDEX_VJComp,     /* 9 */
    PPP_PRONAMEINDEX_VJUnComp,   /* 10 */
    PPP_PRONAMEINDEX_IPX,        /* 11 */
    PPP_PRONAMEINDEX_CCP,        /* 12 */
    PPP_PRONAMEINDEX_MCCP,       /* 13 */
    PPP_PRONAMEINDEX_SCP,        /* 14 */
    PPP_PRONAMEINDEX_MCP,        /* 15 */
    PPP_PRONAMEINDEX_MPLSCP,     /* 16 */
    PPP_PRONAMEINDEX_MPLS_UNICAST,     /* 17 */
    PPP_PRONAMEINDEX_MPLS_MULTICAST,   /* 18 */
    PPP_PRONAMEINDEX_OSICP,      /* 19 */
    PPP_PRONAMEINDEX_OSI_NPDU,   /* 20 */
    PPP_PRONAMEINDEX_CBCP,       /* 21 */
    PPP_PRONAMEINDEX_LQM         /* 22 */
    ,PPP_PRONAMEINDEX_IP6CP,     /* 23 */
    PPP_PRONAMEINDEX_IP6         /* 24 */
    ,PPP_PRONAMEINDEX_PPPMUXCP,  /* 25 */
    PPP_PRONAMEINDEX_PPPMUX      /* 26 */
    /* End of addition */

    /* Added by z43740 for IPHC debug，2006/06/07*/
    ,PPP_PRONAMEINDEX_FULL_HEADER,          /* 27 */
    PPP_PRONAMEINDEX_Compressed_TCP,        /* 28 */
    PPP_PRONAMEINDEX_Compressed_TCP_NODELTA,/* 29 */
    PPP_PRONAMEINDEX_Compressed_NON_TCP,    /* 30 */
    PPP_PRONAMEINDEX_Compressed_UDP_8,      /* 31 */
    PPP_PRONAMEINDEX_Compressed_UDP_16,     /* 32 */
    PPP_PRONAMEINDEX_Compressed_RTP_8,      /* 33 */
    PPP_PRONAMEINDEX_Compressed_RTP_16,     /* 34 */
    PPP_PRONAMEINDEX_CONTEXT_STATE          /* 35 */
    /* End of addition */
};
/********************协议名索引  protocol name index*******************/


/************************ 同异步转换宏 *************************/
#define PPP_ConvertByteToAsy(ucOctet, pAsyData, ulAsyLen, ulAsynAccm) \
{                                                  \
    if((ucOctet == '\x7e') || (ucOctet == '\x7d')) \
    {                                              \
        /* 增加escape控制段 add the Escape Control Character */     \
        *pAsyData = '\x7d';                        \
        pAsyData ++;                               \
        ulAsyLen ++;                               \
        ucOctet ^= 0x20;                           \
    }                                              \
    if(ucOctet < 0x20)                             \
    {                                              \
        if ((ulAsynAccm >> (unsigned int)ucOctet) & ((unsigned int)0x1)) \
        {                                          \
            /* 如果需要启动escape控制段 if this character need be mapped, add the Escape Control Character */ \
            *pAsyData = '\x7d';                    \
            pAsyData ++;                           \
            ulAsyLen ++;                           \
            ucOctet ^= 0x20;                       \
        }                                          \
    }                                              \
    /* 增加escape控制段 add the Escape Control Character */         \
    * pAsyData = ucOctet;                          \
    pAsyData ++;                                   \
    ulAsyLen ++; /* 适合帧长度 adjust frame's length */       \
}
/************************ 同异步转换宏 *************************/


/* 将下行流量记录到PPP控制块 Add by xiaoshouhe31170 2003/10/16 */
#define PPP_FLOW_STAT_OUT(pstPppInfo, ulLen) \
{\
    (pstPppInfo)->stStatisticInfo.ulOutOctets += (ulLen);\
    if((pstPppInfo)->stStatisticInfo.ulOutOctets < (ulLen))\
    {\
        (pstPppInfo)->stStatisticInfo.ulOutGigaWords++;\
    }\
    (pstPppInfo)->stStatisticInfo.ulOutPackets++;\
}

/* 将上行流量记录到PPP控制块 Add by xiaoshouhe31170 2003/10/16 */
#define PPP_FLOW_STAT_IN(pstPppInfo, ulLen) \
{\
    (pstPppInfo)->stStatisticInfo.ulInOctets += (ulLen);\
    if((pstPppInfo)->stStatisticInfo.ulInOctets < (ulLen))\
    {\
        (pstPppInfo)->stStatisticInfo.ulInGigaWords++;\
    }\
    (pstPppInfo)->stStatisticInfo.ulInPackets++;\
}


/********************* 定时器相关的宏定义 (Begin)**********************/

#define PPP_CHAIN_TAIL       -1    /* 用数组下标串起来的各种链表的表尾 */

#define PPP_DEF_GLOBALTIME 1000

#define PppChainDelNode(astBufHead,pstQueueHead,pstNode) \
{\
    if (PPP_CHAIN_TAIL == ((pstNode)->stNode.lPrev))\
    {\
        (pstQueueHead)->lNext =  (pstNode)->stNode.lNext;\
    }\
    else \
    { \
        astBufHead[((pstNode)->stNode.lPrev)].stNode.lNext = (pstNode)->stNode.lNext;\
    } \
    if (PPP_CHAIN_TAIL == ((pstNode)->stNode.lNext))\
    { \
        (pstQueueHead)->lPrev =  (pstNode)->stNode.lPrev;\
    } \
    else \
    { \
        astBufHead[((pstNode)->stNode.lNext)].stNode.lPrev = (pstNode)->stNode.lPrev;\
    } \
    (pstNode)->stNode.lPrev = PPP_CHAIN_TAIL;\
    (pstNode)->stNode.lNext = PPP_CHAIN_TAIL;\
}

#define PppChainAddNode(astBufHead,pstQueueHead,pstNode)\
{\
    (pstNode)->stNode.lPrev = (pstQueueHead)->lPrev;\
    (pstNode)->stNode.lNext = PPP_CHAIN_TAIL;\
    if (PPP_CHAIN_TAIL == ((pstNode)->stNode.lPrev))\
    {\
        (pstQueueHead)->lNext = (pstNode) - (astBufHead);\
    }\
    else\
    {\
        astBufHead[((pstNode)->stNode.lPrev)].stNode.lNext = (pstNode) - (astBufHead);\
    }\
    (pstQueueHead)->lPrev = (pstNode) - (astBufHead);\
}

#define PppChainInsNode(astBufHead,pstQueueHead,pstNode,pstNewNode)\
{\
    (pstNewNode)->stNode.lNext = (pstNode) - (astBufHead);\
    if (PPP_CHAIN_TAIL == ((pstNode)->stNode.lPrev))\
    {\
        (pstNewNode)->stNode.lPrev = PPP_CHAIN_TAIL;\
        (pstQueueHead)->lNext = (pstNewNode) - (astBufHead);\
    }\
    else\
    {\
        (pstNewNode)->stNode.lPrev =  (pstNode)->stNode.lPrev;\
        astBufHead[((pstNode)->stNode.lPrev)].stNode.lNext = (pstNewNode) - (astBufHead);\
    }\
    (pstNode)->stNode.lPrev = (pstNewNode) - (astBufHead);\
}

#define PppChainPrevNode(astBufHead,pstNode,pstPrevNode)\
{\
    if (PPP_CHAIN_TAIL == ((pstNode)->stNode.lPrev))\
    {\
        pstPrevNode = NULL;\
    }\
    else\
    {\
        pstPrevNode = &(astBufHead[((pstNode)->stNode.lPrev)]);\
    }\
}

#define PppChainNextNode(astBufHead,pstNode,pstNextNode)\
{\
    if (PPP_CHAIN_TAIL == ((pstNode)->stNode.lNext))\
    {\
        pstNextNode = NULL;\
    }\
    else\
    {\
        pstNextNode = &(astBufHead[((pstNode)->stNode.lNext)]);\
    }\
}

#define PppChainFirstNode(astBufHead,pstQueueHead,pstFirstNode)\
{\
    if (PPP_CHAIN_TAIL == (pstQueueHead)->lNext)\
    {\
        pstFirstNode = NULL;\
    }\
    else\
    {\
        pstFirstNode = &(astBufHead[((pstQueueHead)->lNext)]);\
    }\
}

#define PppChainEndNode(astBufHead,pstQueueHead,pstEndNode)\
{\
    if (PPP_CHAIN_TAIL == (pstQueueHead)->lPrev)\
    {\
        pstEndNode = NULL;\
    }\
    else\
    {\
        pstEndNode = &(astBufHead[((pstQueueHead)->lPrev)]);\
    }\
}

/********************* 定时器相关的宏定义 (End)**********************/

/* 如果本端配置的参数和本端协商获得的参数不一致, 或两端协商获得的参数不一致, 则记录告警 */
#define PPP_PARA_CMP_RECORD(parameter, stParaRecorder, usWarningRecord)\
if ((pstWantOptions->parameter != pstGotOptions->parameter)\
   || (pstGotOptions->parameter != pstHisOptions->parameter))\
{\
    stParaRecorder.ul_is_different = 1;\
    stParaRecorder.ul_want_value = pstWantOptions->parameter;\
    stParaRecorder.ul_got_value = pstGotOptions->parameter;\
    stParaRecorder.ul_his_value = pstHisOptions->parameter;\
    usWarningRecord |= PPP_IPHC_PARA_DIFF;\
}\

/********************** PPP告警相关的宏定义(End) **********************/

#define PPP_COPY_LCPOPTION_TO_PPI(stPpiInfo, pstLcpOption)\
{\
    ULONG i;\
    VOS_DBGASSERT(PPI_MC_PREFIX_MAX_NUM >= MC_PREFIXE_MAX_NUM);\
    VOS_DBGASSERT(PPI_MC_PREFIX_MAX_LEN >= MC_PREFIXE_MAX_STR);\
    (stPpiInfo).neg_discr = (pstLcpOption)->neg_discr;\
    (stPpiInfo).neg_magicnumber = (pstLcpOption)->neg_magicnumber;\
    (stPpiInfo).neg_accompression = (pstLcpOption)->neg_accompression;\
    (stPpiInfo).neg_asyncmap = (pstLcpOption)->neg_asyncmap;\
    (stPpiInfo).neg_mhf = (pstLcpOption)->neg_mhf;\
    (stPpiInfo).neg_mrru = (pstLcpOption)->neg_mrru;\
    (stPpiInfo).neg_mru = (pstLcpOption)->neg_mru;\
    (stPpiInfo).neg_pcompression = (pstLcpOption)->neg_pcompression;\
    (stPpiInfo).neg_prefix = (pstLcpOption)->neg_prefixE;\
    (stPpiInfo).neg_ssnhf = (pstLcpOption)->neg_ssnhf;\
    (stPpiInfo).ulAsyncmap = (pstLcpOption)->asyncmap;\
    (stPpiInfo).usMrru = (pstLcpOption)->mrru;\
    (stPpiInfo).usMru = (pstLcpOption)->mru;\
    (stPpiInfo).ucCode = (pstLcpOption)->ucMhfCode;\
    (stPpiInfo).ucClass = (pstLcpOption)->ucMhfClass;\
    if(((pstLcpOption)->neg_prefixE) && ((pstLcpOption)->pstPrefixE))\
    {\
        for(i = 0; i < (ULONG)MC_PREFIXE_MAX_NUM; i++)\
        {\
            (stPpiInfo).astPrefix[i].ucPrefixValid = (pstLcpOption)->pstPrefixE[i].ucIsUsedFlag;\
            (stPpiInfo).astPrefix[i].ucClass = (pstLcpOption)->pstPrefixE[i].ucClass;\
            (stPpiInfo).astPrefix[i].usPrefixLength = (pstLcpOption)->pstPrefixE[i].ucPrefixELen;\
            (VOID)TCPIP_Mem_Copy((stPpiInfo).astPrefix[i].aucPrefix, PPI_MC_PREFIX_MAX_LEN, \
            (pstLcpOption)->pstPrefixE[i].aucPrefixE, MC_PREFIXE_MAX_STR);\
        }\
    }\
    if((pstLcpOption)->neg_mrru)\
    {\
        (stPpiInfo).ucDiscr_len = (pstLcpOption)->discr_len;\
        (stPpiInfo).ucDiscr_class = (pstLcpOption)->discr_class;\
        (VOID)TCPIP_Mem_Copy((stPpiInfo).discr_addr, PPI_MP_MP_DISCR_MAX_LENGTH,\
                (pstLcpOption)->discr_addr, PPP_MP_DISCR_MAX_LENGTH);\
    }\
    (stPpiInfo).ulMagicnumber = (pstLcpOption)->magicnumber;\
}

#define PPP_EnDropQueue  g_stPPPShellFun.pfPPP_EnDropQue
#define PPP_GetIfByIndex(ulIfIndex) g_pstCoreIFNETFUNTable->pfIF_GetIfByIndex(ulIfIndex)
#define PPP_GetConfigMTU(pIf)    g_pstCoreIFNETFUNTable->pfIF_GetConfigMTU(pIf)
#define PPP_GetIfByFullName(szFull)\
            g_pstCoreIFNETFUNTable->pfIF_GetIfByFullName(szFull)

#define PPP_MP_ISLInput(ulIfIndex, pstMbuf, usProtocol, ulOffset)\
            g_pstPppMpFunTable->pfMP_SonISLInput((ulIfIndex),\
                                                 (pstMbuf), \
                                                 (usProtocol), \
                                                 (ulOffset))

#define PPP_MP_FatherOutput(pstIfnet, pstMbuf, usProtocol)\
            g_pstPppMpFunTable->pfMP_FatherOutput((pstIfnet),\
                                                  (pstMbuf), \
                                                  (usProtocol))

#define PPP_MP_NoPppMultilink(ulIfIndex)\
            g_pstPppMpFunTable->pfMP_NoPppMultilink(ulIfIndex)

/*(同步问题单A82D11804)Modified by f54882, 2007-02-01, HDLC自动侦听非标需求开发*/
#define PPP_MP_GetDiscr(ulIfIndex, pucDiscr_addr, pucClass, pucLength)  \
            g_pstPppMpFunTable->pfMP_GetDiscr(ulIfIndex, pucDiscr_addr, pucClass, pucLength)

#define PPP_MP_IsCfgDiscriminator(ulIfIndex)\
            g_pstPppMpFunTable->pfMP_IsCfgDiscriminator(ulIfIndex)

/* Added by z43740 for TR报文发送增强,2009-04-09 */
#define PPP_MP_IsCfgDiscardReq(ulIfIndex) \
            g_pstPppMpFunTable->pfMP_IsCfgDiscardReq(ulIfIndex)

#define PPP_MP_GetGoodSonChannel(ulIfIndex,pulSonIfIndex) \
            g_pstPppMpFunTable->pfMP_GetGoodSonChannel(ulIfIndex,pulSonIfIndex)

#define PPP_MP_GetNeedDownSonChannel(ulIfIndex,ulOurMagicNum,ulHisMagicNum,pulSonIfIndex) \
            g_pstPppMpFunTable->pfMP_GetNeedDownSonChannel(ulIfIndex,ulOurMagicNum,ulHisMagicNum,pulSonIfIndex)
/* End of addition */


#define PPP_MID_PPP     g_stPPPModInfo.ulMID_PPP
#define PPP_SID_ASY_S   g_stPPPModInfo.ulSID_PPP_ASY_S
#define PPP_QUE_MP      (ULONG)g_stPPPModInfo.ulQUE_PPP_MP

#define PPP_QUE_PPPMUX  g_stPPPModInfo.ulQUE_PPPMUX_INPUT

#define PPP_FreePacketInQueForRequest(ulQueID, ulCmd, pData)\
            g_stPPPShellFun.pfQue_FreePacketInQueueForRequest((ulQueID), \
                                                              (ulCmd), \
                                                              (pData))

/********************* PPP模块相关SID相关宏(BEGIN)**********************/
#define SID_COMP_PPP_PACKET_S           ( 1 )
#define SID_COMP_PPP_CB_S               ( 2 )
#define SID_COMP_PPP_L2TPOPTION_S       ( 3 )
#define SID_COMP_PPP_L2TPPARA_S         ( 4 )
#define SID_COMP_PPP_BUILDRUN           ( 5 )
#define SID_COMP_PPP_STAC_BUFFER_S      ( 6 )
#define SID_COMP_PPP_STAC_HASHNODE_S    ( 7 )
#define SID_COMP_PPP_STAC_MINLIST_S     ( 8 )
#define SID_COMP_PPP_STAC_PACKET_S      ( 9 )
#define SID_COMP_PPP_ASY_S              ( 10)
#define SID_COMP_PPP_SYN_S              ( 11)
#define SID_COMP_PPP_MBUF_S             ( 12)
/********************* PPP模块相关SID相关宏(END)**********************/


#define PPI_LCP (PPI_LCPGOTOPTION|PPI_LCPHISOPTION)
#define PPI_IPCP (PPI_IPCPGOTOPTION|PPI_IPCPHISOPTION)
#define PPI_MCP (PPI_MUXCPGOTOPTION|PPI_MUXCPHISOPTION)
#define PPI_MP (PPI_ADD_MLPPP|PPI_DEL_MLPPP)
#define PPI_IP6CP (PPI_IP6CPGOTOPTION|PPI_IP6CPHISOPTION)

#define PPP_LCPECHO_TONP(pstNpLcpEcho, pstFsm) \
{ \
    PPP_LCP_OPTION_S *pstGotOptions; \
    PPP_LCP_OPTION_S *pstHisOptions; \
    UCHAR             *pcTemp; \
    USHORT            usTemp; \
    ULONG             ulMagic; \
    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions); \
    pstHisOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stHisOptions); \
    ulMagic = pstGotOptions->magicnumber; \
    pstNpLcpEcho->ulGotMagicNum = VOS_HTONL(ulMagic); \
    ulMagic = pstHisOptions->magicnumber; \
    pstNpLcpEcho->ulHisMagicNum = VOS_HTONL(ulMagic); \
    pstNpLcpEcho->ulKeepAlive  = VOS_HTONL(pstFsm->ulEchoTimeOutTime / 1000); \
    usTemp = PPP_MAXLOOPSBACK; \
    pstNpLcpEcho->usLoopBackNum = VOS_HTONS(usTemp); \
    pstNpLcpEcho->ucPacketID = pstFsm->ucEchoId; \
    pstNpLcpEcho->ucPppDownNum = (UCHAR)g_stPPPModInfo.ulPPP_DEF_CONFREQS; \
    pstNpLcpEcho->szEchoReq[0] = 0xff; \
    pstNpLcpEcho->szEchoReq[1] = 0x03; \
    pcTemp = (UCHAR *)&pstNpLcpEcho->szEchoReq[2]; \
    usTemp = PPP_LCP; \
    PPP_PUTSHORT(usTemp, pcTemp) \
    pstNpLcpEcho->szEchoReq[4] = ECHOREQ; \
    pstNpLcpEcho->szEchoReq[5] = pstFsm->ucEchoId; \
    pcTemp = (UCHAR *)&pstNpLcpEcho->szEchoReq[6]; \
    usTemp = (LCP_MAGICNUM_LEN + FSM_HDRLEN); \
    PPP_PUTSHORT(usTemp, pcTemp) \
    pcTemp = (UCHAR *)&pstNpLcpEcho->szEchoReq[8]; \
    PPP_PUTLONG(pstGotOptions->magicnumber, pcTemp) \
}

/* 修改增加该枚举定义时,注意需要对CHAR *g_stNccPppDownReason[]做相应的修改 */
enum emumPPP_DOWN_DOT
{
    PPP_DOWN_RCR = 1,
    PPP_DOWN_RCA,
    PPP_DOWN_RCN,
    PPP_DOWN_RXJ_SUB_CR,  /* 收到拒绝编码code reject */
    PPP_DOWN_RXJ_SUB_PR,  /* 收到拒绝协议protocal reject */
    PPP_DOWN_RTR,
    PPP_DOWN_RTA,
    PPP_DOWN_DOT_8,
    PPP_DOWN_DOT_9,
    PPP_DOWN_DOT_10,
    PPP_DOWN_DOT_11,
    PPP_DOWN_DOT_12,
    PPP_DOWN_DOT_13,
    PPP_DOWN_DOT_14,
    PPP_DOWN_DOT_15,
    PPP_DOWN_DOT_16,
    PPP_DOWN_DOT_17,
    PPP_DOWN_DOT_18,
    PPP_DOWN_DOT_19,
    PPP_DOWN_DOT_20,
    PPP_DOWN_DOT_21,
    PPP_DOWN_DOT_22,
    PPP_DOWN_DOT_23,
    PPP_DOWN_DOT_24,
    PPP_DOWN_DOT_25,
    PPP_DOWN_DOT_26,
    PPP_DOWN_DOT_27,
    PPP_DOWN_DOT_28,
    PPP_DOWN_DOT_29,
    PPP_DOWN_DOT_30,
    PPP_DOWN_DOT_31,
    PPP_DOWN_DOT_32,
    PPP_DOWN_DOT_33,
    PPP_DOWN_DOT_34,
    PPP_DOWN_DOT_35,
    PPP_DOWN_DOT_36,
    PPP_DOWN_DOT_37,
    PPP_DOWN_DOT_38,
    PPP_DOWN_DOT_39,
    PPP_DOWN_DOT_40,
    PPP_DOWN_DOT_41,
    PPP_DOWN_DOT_42,
    PPP_DOWN_DOT_43,
    PPP_DOWN_DOT_44,
    PPP_DOWN_DOT_45,
    PPP_DOWN_DOT_46,
    PPP_DOWN_DOT_47,
    PPP_DOWN_DOT_48,
    PPP_DOWN_DOT_49,
    PPP_DOWN_DOT_50,
    PPP_DOWN_DOT_51,
    PPP_DOWN_DOT_52,
    PPP_DOWN_DOT_53,
    PPP_DOWN_DOT_54,
    PPP_DOWN_DOT_55,
    PPP_DOWN_DOT_56,
    PPP_DOWN_DOT_57,
    PPP_DOWN_DOT_58,
    PPP_DOWN_DOT_59,
    PPP_DOWN_DOT_60,
    PPP_DOWN_DOT_61,
    PPP_DOWN_DOT_62,
    PPP_DOWN_DOT_63,
    PPP_DOWN_DOT_64,
    PPP_DOWN_DOT_65,
    PPP_DOWN_DOT_66,
    PPP_DOWN_DOT_67,
    PPP_DOWN_DOT_68,
    PPP_DOWN_DOT_69,
    PPP_DOWN_DOT_70,
    PPP_DOWN_DOT_71,
    PPP_DOWN_DOT_END,
};
/* 修改增加该枚举定义时,注意需要对CHAR *g_stNccPppDownReason[]做相应的修改 */

#ifdef __cplusplus
}
#endif

#endif
