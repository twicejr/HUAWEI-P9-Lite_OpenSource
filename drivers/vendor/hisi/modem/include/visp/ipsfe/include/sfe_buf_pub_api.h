/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfe_buf_pub_api.h
*
*  Project Code: V1.1.0
*   Module Name:
*  Date Created: 2009-8-31
*        Author: w60786
*   Description: 数据面和控制面公用MBUF相关对外API结构定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-8-31    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _SFE_BUF_PUB_API_H_
#define _SFE_BUF_PUB_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 报文前面预留一定字节用于结构扩充,该预留字节必须与MBUF_S结构大小同步 */
#define SFE_MBUF_RESERVE 2
/* MBUF结构大小,结构字段新增删除修改变化时,必须递增版本号,用于防止内核态(产品)和用户态使用的MBUF头文件不一致.
   sizeof(SFE_MBUF_S)改变后版本号自增:
   Version 1: sizeof(SFE_MBUF_S) == 160;
   Version 2: SCG产品TCP Proxy需求引起的MBUF结构变化;
*/
#define SFE_MBUF_VERSION 2
/* 目前版本MBUF结构大小必须为160 */
#define SFE_MBUF_STRUCT_SIZE 160
/* 当MBUF预配置为扩展模式(MBUF结构大小无限制,即非RPU MBUF应用方式)时,MBUF结构前预留128字节供MCUP添加MBUF控制信息使用 */
#define SFE_MBUF_MCUP_LEN   128

/* DB的长度,因为产品特殊的内存管理机制不能提供太大的DB数据块,所以这里与产品约定DB数据长度为1600 */
#define SFE_MBUF_DATA_BLOCK1600_SIZE  1600
/* 根据预配置扩展MBUF中DB长度 */
#define SFE_MBUF_DATA_BLOCK2048_SIZE  2048
/* MBUF中DB尾部预留长度,用于Linux协议栈shareinfo使用 */
#define SFE_MBUF_DB_TAIL_RESERVE_SIZE  512
/* 系统预留的不使用的MBUF资源个数:10K个,用于临时规避MBUF资源使用完后OS驱动不接收报文问题 */
#define SFE_MBUF_RESERVE_MBUF_NUM    10240

/* 一段式MBUF申请时,MBUF头和MBUF扩展信息,DBD,DB是否使用的标记 */
#define SFE_MBUF_IS_USED    0x01  /* MBUF头和扩展头是否使用标记*/
#define SFE_DBD_IS_USED     0x02  /* DBD是否使用标记*/
#define SFE_DB_IS_USED      0x04  /* DB是否使用标记*/

/* 接口信息ID */
typedef struct tagSFE_MBUF_IFID
{
    UINT8   u8PortType;        /* 端口类型 */
    UINT8   u8FrameID;         /* 框号,全F表示不使用 */
    UINT16  u16SlotID;         /* 逻辑槽位号,全F表示不使用 */
    UINT16  u16PortNo;         /* 逻辑端口号,一维模式下系统端口编号唯一，三维模式下在同一框同一槽位下唯一 */
    UINT16  u16lSubPortNo;     /* 子端口号 */
}SFE_MBUF_IFID_S;

/* 不带IP选项的IP头长度 */
#define SFE_IP_HEADER_NO_OPT_LEN    20

/* IP头定义 */
typedef struct tagSFE_IP
{
#if SFE_LITTLE_ENDIAN == SFE_YES
    UINT8   ip_chHLen:4;        /* header length */
    UINT8   ip_chVer: 4;        /* version */
#else
    UINT8  ip_chVer:  4;        /* version */
    UINT8  ip_chHLen: 4;        /* header length */
#endif
    UINT8   ip_chTOS;           /* type of service */
    UINT16  ip_usLen;           /* total length */
#define ip_sLen ip_usLen
    UINT16  ip_usId;            /* identification */
    UINT16  ip_usOff;           /* fragment offset field */
#define ip_sOff ip_usOff
#define IP_DF 0x4000            /* dont fragment flag */
#define IP_MF 0x2000            /* more fragments flag */
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
    UINT8   ip_chTTL;           /* time to live */
    UINT8   ip_chPr;            /* protocol */
    UINT16  ip_usSum;           /* checksum */
    UINT32  ip_stSrc;           /* source address */
    UINT32  ip_stDst;           /* destination address */
}SFE_IP_S;

/* UDP头结构定义 */
typedef struct tagSFE_UDP
{
    UINT16    u16SrcPort;        /* 源端口号 */
    UINT16    u16DstPort;        /* 目的端口号 */
    INT16     i16Len;            /* UDP长度 */
    UINT16    u16ChkSum;         /* UDP校验和 */
}SFE_UDP_S;

/* 数据面时间信息结构定义 */
typedef struct tagSFE_TimeVal
{
    UINT32 u32HighTick;       /* 高位 */
    UINT32 u32LowTick;        /* 低位 */
}SFE_TIMEVAL_S;

/* 数据面IP报文信息结构定义 */
typedef struct tagSFE_PKTINFO_NET
{
    UINT16 u16PktSrcPortOrIcmpType; /* 报文的源端口号或者ICMP报文的Type,网络字节序 */
    UINT16 u16PktDstPortOrIcmpCode; /* 报文的目的端口号或者ICMP报文的code,网络字节序 */
    UINT32 u32ServiceType;          /* IPv4、IPv6共用 */
}SFE_PKTINFO_NET_S;

/* 流统计一个报文最大支持同时匹配的规则数 */
#define SFE_FLOWSTAT_MATCH_MAX 7

/* 数据面报文流统计信息结构定义 */
typedef struct tagSFE_FLOWSTATISTIC
{
    UINT16  u16FlowStatNum;  /* 报文满足的统计流个数 */
    UINT16  u16FlowStat[SFE_FLOWSTAT_MATCH_MAX]; /* 报文满足的流统计ID */
} SFE_FLOWSTATISTIC_S;

/* 数据面报文公共属性结构定义 */
typedef struct tagSFE_PKTINFO_COMMON
{
    SFE_TIMEVAL_S Time;          /* 用于计算报文发送耗时 */
    UINT32 u32LoopTimes;         /* 报文在组件间回环次数 */
    UINT32 u32VrfIndex;          /* VRF索引 */
    UINT32 u32PktType;           /* 报文类型,本机发送,转发,广播,多播 */
    UINT32 u32IsFragMent:1;      /* 该报文是否是TCP,UDP分片报文,在进行假重组后该标志才有效 */
    UINT32 u32IsFakeReassed:1;   /* 该分片报文是否已经假重组 */
    UINT32 u32IsFlowStatistic:1; /* 该报文是否需要进行流统计 */
    UINT32 u32IsFlowDebug:1;     /* 该报文是否需要进行流调试 */
    UINT32 u32ReserveFlag:28;    /* 保留的标记字段 */
    SFE_FLOWSTATISTIC_S stFlowStat; /* 流统计信息 */
    UINT32 u32DeliverType;       /* 上送分发处理AGENT模块的各报文类型,如ARP.广播类.多播类.分发FWD类等 */
    UINT32 u32DeliverOfflen;     /* 上送处理偏移的头长度 */
} SFE_PKTINFO_COMMON_S;

/* DB的来源 */
#define SFE_MBUF_DATA_NORMAL 0  /* 正常DB,使用SFE提供的创建释放正常DB MBUF的函数操作 */
#define SFE_MBUF_DATA_ETHDRV 1  /* 特殊DB,对该DB的操作需要进行额外的处理,额外操作函数由产品提供(包括释放,拷贝等),
                                   如某些驱动上送SFE的DB是其它操作系统的DB内存,SFE不能直接操作它,解决方法有两个,一个是将
                                   其它操作系统的DB数据拷贝到SFE的DB中,但是产品为了提高性能,希望实现零拷贝,所以提供了
                                   另一种方法,SFE提供一个根据产品提供的系统DB创建MBUF的函数,该函数会记录产品提供的一些
                                   关于系统DB的一些信息,用于产品操作自己的DB,然后SFE在进行MBUF相关操作时作为参数传给产品
                                   提供的操作函数. */
#define SFE_MBUF_DATA_PPPDRV 2  /* 特殊DB,对该DB的操作需要进行额外的处理,额外操作函数由产品提供,同上 */



/* Mbuf中产品自有信息最大长度 */
#define SFE_MBUF_PRIVATE_DATA_LEN 64


/* 产品自有信息结构 */
typedef struct tagSFE_PKTINFO_USERPRIVATE
{
    UINT8  u8UserFlag;          /* 产品私有标志 */
    UINT8  u8Reserve[3];        /* 保留字段 */
    UINT32 u32UsrPrivateLen;                            /* 产品自有数据长度 */
    UINT8  au8PktUsrPrivate[SFE_MBUF_PRIVATE_DATA_LEN]; /* 产品自有数据缓存区 */
    UINT8 *pu8UserPointer1;     /* 产品自有信息指针1,该指针指向的内存由产品负责申请和释放. */
    UINT8 *pu8UserPointer2;     /* 产品自有信息指针2,该指针指向的内存由产品负责申请和释放. */
}SFE_PKTINFO_USERPRIVATE_S;

/* 报文流无上下行属性 */
#define SFE_PKT_NO_DIRECTION_FLOW   0
/* 上行报文流 */
#define SFE_PKT_UP_DIRECTION_FLOW   1
/* 下行报文流 */
#define SFE_PKT_DOWN_DIRECTION_FLOW   2
/* 硬件IO聚合支持的MBUF最大DB数据 */
#define SFE_SGO_DB_MAX_NUM      4

/* 记录MBUF扩展信息,包括产品自有信息和MBUF新增字段信息,后续MBUF新增字段统一在该结构中增加 */
typedef struct tagSFE_MBUF_EXPAND
{
    UINT32 u32IpPktRcvPolicy;   /* IP报文接收处理策略 */
    UINT32 u32PktDispatchKey;   /* 报文分发到某一个固定核的KEY值 */
    UINT32 u32ConnectionId;     /* 记录产品连接ID，便于后续扩展 */
    UINT32 u32FlowDirection;    /* 报文上下行属性 */
    UINT32 u32IpPktLen;         /* IP报文长度 */
    UINT32 u32PktDataLen;       /* 报文中的纯数据长度(不含IP和传输层头的长度) */
    UINT32 u32HdrDataOffset;    /* 报文中头部重复数据不上送,且不能丢弃.
                                   此时记录头部重复数据长度,在上送时偏移到数据区和应用完成处理发送时偏回报文首部时用到 */
    UINT32 u32TailDataOffset;   /* 报文中尾部重复数据不上送,且不能丢弃.
                                   此时记录尾部重复数据长度,在上送(减少)和发送(增加)时报文总长度和纯数据长度偏移会用到 */
    UINT32 u32PktSrcIp;         /* 报文的源IP,网络字节序 */
    UINT32 u32PktDstIp;         /* 报文的目的IP,网络字节序 */
    UINT8  u8IpHdrLen;          /* IP头长度 */
    UINT8  u8TransHdrLen;       /* 传输层头的长度 */
    UINT8  u8StatDirection;     /* 问题单:DTS2010110502669,添加了业务统计方向标志 */
    UINT8  u8Reserve;           /* 预留字段 */    
    UINT32 u32DupPktLen;        /* TCP代理发送时标识重传数据长度 */
    SFE_PKTINFO_USERPRIVATE_S    stUsrPrivateData;  /* 产品自有信息 */
    UINT64 au64SgoAddr[SFE_SGO_DB_MAX_NUM];     /* 存放用于硬件IO聚合的各DB数据起始地址 */
    UINT32 au32SgoDataLen[SFE_SGO_DB_MAX_NUM];/* 存放用于硬件IO聚合的各DB数据长度 */
    UINT32 u32PktTimeStamp;     /* 报文L7处理时延采样时记录的时间戳,包括:接收或释放报文时的时间点 */
    UINT32 u32PktGenNum;        /* 报文L7处理时延采样时报文所处的采样组号 */
}SFE_MBUF_EXPAND_S;

/* 数据面数据块描述符DBD结构定义,
   为了兼容原有RPU产品的特殊MBUF应用(要求DBD的大小固定为32字节),该结构不能显示8字节对齐. */
typedef struct tagSFE_MBUF_DataBlockDescriptor
{
    UINT8 *pu8Data;                                      /* 当前数据块中数据的起始地址，NULL表示无效，其他表示有效 */
    UINT8 *pu8DataBlock;                                 /* 当前数据块的起始地址，NULL表示无效，其他表示有效 */
    struct tagSFE_MBUF_DataBlockDescriptor *pstPrevDBD;  /* 前一个数据块描述符，NULL表示没有 */
    struct tagSFE_MBUF_DataBlockDescriptor *pstNextDBD;  /* 下一个数据块描述符，NULL表示没有 */
    VOID  *pstSysDBCtrl;                                 /* 系统DB对应的控制块, 可选 */
    UINT32 u32DataBlockSource;                           /* DB的来源，详细解释见上宏定义 */
    UINT32 u32DataLength;                                /* 当前数据块中数据的总长度 */
    UINT32 u32DataBlockLength;                           /* 当前数据块的总长度 */
} SFE_MBUF_DATABLOCKDESCRIPTOR_S;

/* 数据面MBUF结构定义 */
typedef struct tagSFE_MBuf
{
    /* 为了支持零拷贝功能MBUF的前后指针必须按照以下顺序放在MBUF结构的最前面 */
    struct tagSFE_MBuf              *pstNextMbuf;                       /* 下一个MBuf */
    struct tagSFE_MBuf              *pstPrevMbuf;                       /* 前一个MBuf */
    UINT32                           u32MBufVersion;                    /* 必须填写为SFE_MBUF_VERSION */
    UINT32                           u32TotalDataLength;                /* mbuf中报文数据的总长度 */
    SFE_MBUF_IFID_S                  stPhyRecvIfInfo;                   /* 报文物理接收接口信息 */
    VOID                            *pPhyRecvLink;                      /* 报文物理接收接口链路头信息指针 */
    VOID                            *pPhyRecvBase;                      /* 报文物理接收接口基本信息指针 */

    UINT8                           *pu8LinkLayerHead;                  /* 指向报文的链路层首部 */
    UINT8                           *pu8NetLayerHeader;                 /* 指向报文的网络层首部 */
    UINT8                           *pu8TranLayerHeader;                /* 指向报文的传输层首部 */
    SFE_MBUF_IFID_S                  stPhySendIfInfo;                   /* 报文物理发送接口信息 */
    VOID                            *pPhySendLink;                      /* 报文物理发送接口链路头信息指针 */
    VOID                            *pPhySendBase;                      /* 报文物理发送接口基本信息指针 */
    SFE_MBUF_DATABLOCKDESCRIPTOR_S  *pstDBD;                            /* 第一个数据块描述符地址，即数据块描述符链表的第一个结点 */

    SFE_PKTINFO_NET_S                stPktNetInfo;                      /* 存放报文网络层及网络层之上的相关信息 */
    SFE_PKTINFO_COMMON_S             stPktCommonInfo;                   /* 存放报文的通用信息 */

    SFE_IPADDR_UN                    unNextHopIp;                       /* 下一跳地址 */
    UINT32                           u32ModuleID;                       /* 创建该MBUF的模块ID */
    UINT32                           u32DataBlockNumber;                /* mbuf中数据块的个数 */

    SFE_MBUF_EXPAND_S               *pstExpandInfo;                     /* 记录MBUF扩展信息,包括产品自有信息和MBUF新增字段信息 */

    UINT32                           u32VcpuId;                         /* 当前核号 */
    UINT32                           u32IfIndex;                        /* Linux下的设备接口索引 */
    UINT8                            u8IsUsed;                          /* MBUF采用一段式申请,MBUF头,DBD,DB,和MBUF扩展信息是否在使用的标记,*/
                                                                        /* 按位表示, 1:表示该段内存在使用, 0:表示该段内存未使用 */
    UINT8                            u8UserStatFlag;
    UINT8                            au8IsReorderSend;                    /*判断是否乱序转发过*/ 
    UINT8                            au8PktReserved;  /* 预留 */
} SFE_MBUF_S;


/* 乱序转发标记,没有转发 */
#define SFE_PKT_NO_REORDER_SEND   0
/* 乱序转发标记,已转发 */
#define SFE_PKT_REORDER_SENDED   1

/* 获取乱序转发标记*/
#define SFE_MBUF_GET_IS_REORDER_SEND(pstMbuf) ((pstMbuf)->au8IsReorderSend)
/* 获取前一个MBUF */
#define SFE_MBUF_GET_PREV(pstMbuf) ((pstMbuf)->pstPrevMbuf)
/* 设置前一个MBUF */
#define SFE_MBUF_SET_PREV(pstMbuf, pstPreMbufM) ((pstMbuf)->pstPrevMbuf = (pstPreMbufM))
/* 获取后一个MBUF */
#define SFE_MBUF_GET_NEXT(pstMbuf) ((pstMbuf)->pstNextMbuf)
/* 设置后一个MBUF */
#define SFE_MBUF_SET_NEXT(pstMbuf, pstNextMbufM) ((pstMbuf)->pstNextMbuf = (pstNextMbufM))

/* 设置MBUF的版本号 */
#define SFE_MBUF_SET_VERSION(pstMbuf, u32Version)(((pstMbuf)->u32MBufVersion) = (u32Version))
/* 获取MBUF版本号 */
#define SFE_MBUF_GET_VERSION(pstMbuf) ((pstMbuf)->u32MBufVersion)

/* 获取MBUF中数据总长度 */
#define SFE_MBUF_GET_TOTAL_DATA_LENGTH(pstMbuf) ((pstMbuf)->u32TotalDataLength)

/* 获取MBUF中DBD的个数(即DB的个数, DBD和DB是一一对应的) */
#define SFE_MBUF_GET_DBD_NUMBER(pstMbuf) ((pstMbuf)->u32DataBlockNumber)
/* 获取MBUF首个DBD地址 */
#define SFE_MBUF_GET_FIRST_DBD_ADDR(pstMbuf) ((pstMbuf)->pstDBD)

/* 获取前一个DBD地址 */
#define SFE_DBD_GET_PREV(pstDBD) ((pstDBD)->pstPrevDBD)
/* 获取后一个DBD地址 */
#define SFE_DBD_GET_NEXT(pstDBD) ((pstDBD)->pstNextDBD)

/* 获取DBD对应的DB地址 */
#define SFE_DBD_GET_DB_ADDR(pstDBD) ((pstDBD)->pu8DataBlock)
/* 获取DBD对应的DB长度 */
#define SFE_DBD_GET_DB_LENGTH(pstDBD) ((pstDBD)->u32DataBlockLength)

/* 获取DBD对应的数据起始地址 */
#define SFE_DBD_GET_DATA_ADDR(pstDBD) ((pstDBD)->pu8Data)
/* 获取DBD对应的数据长度 */
#define SFE_DBD_GET_DATA_LENGTH(pstDBD) ((pstDBD)->u32DataLength)

/* 获取DBD中存放的系统DB控制块地址 */
#define SFE_DBD_GET_SYSDB_CTRL(pstDBD) ((pstDBD)->pstSysDBCtrl)


/*
  针对RPU, 函数入参的含义如下:

 *ppstMbuf   *ppstDBDAddr                      pu8DBAddr         pu8DataAddr
     |            |                                |                  |
     V____________V________________________________V__________________V_________________________
     |            |                                |                  |                  |      |
     | SFE_MBUF_S | SFE_MBUF_DATABLOCKDESCRIPTOR_S |        64        |    链路层报文    | 可选 |
     |____________|________________________________|__________________|__________________|______|
     |                                             |                  |                  |      |
     |                                             |                  |<-- u32DataLen -->|      |
     |                                             |                                            |
     |                                             |<---------------- u32DBLen ---------------->|
     |                                                                                          |
     |<--------------------------------------- 连续内存 --------------------------------------->|

*/

/* 用于填充不使用的字段 */
#define SFE_NOT_USE_NUM 0xFFFFFFFF

/* 框号无效值 */
#define SFE_FRAME_NOT_USE 0xFF
/* 槽号无效值 */
#define SFE_SLOT_NOT_USE 0xFFFF
/* 子端口号无效值 */
#define SFE_SUBPORT_NOT_USE 0xFFFF

/* Modify by huangqingxin177429, at 2012-05-04. 修改原因: pclint告警消除 */
/* 一维接口模式下, 设置报文入接口的信息 */
#define SFE_MBUF_SET_RX_IFINFO(pstMbuf, u8RcvPortType, u16RcvPortID) \
{ \
    ((pstMbuf)->stPhyRecvIfInfo.u8PortType) = (u8RcvPortType); \
    ((pstMbuf)->stPhyRecvIfInfo.u16PortNo) = (u16RcvPortID); \
    ((pstMbuf)->stPhyRecvIfInfo.u8FrameID) = SFE_FRAME_NOT_USE; \
    ((pstMbuf)->stPhyRecvIfInfo.u16SlotID) = SFE_SLOT_NOT_USE; \
    ((pstMbuf)->stPhyRecvIfInfo.u16lSubPortNo) = SFE_SUBPORT_NOT_USE; \
}


/* 一维接口模式下, 设置报文出接口的信息 */
#define SFE_MBUF_SET_TX_IFINFO(pstMbuf, u8SndPortType, u16SndPortID) \
{ \
    ((pstMbuf)->stPhySendIfInfo.u8PortType) = (u8SndPortType); \
    ((pstMbuf)->stPhySendIfInfo.u16PortNo) = (u16SndPortID); \
    ((pstMbuf)->stPhySendIfInfo.u8FrameID) = SFE_FRAME_NOT_USE; \
    ((pstMbuf)->stPhySendIfInfo.u16SlotID) = SFE_SLOT_NOT_USE; \
    ((pstMbuf)->stPhySendIfInfo.u16lSubPortNo) = SFE_SUBPORT_NOT_USE; \
}


/* 获取MBUF中发送接口类型 */
#define SFE_MBUF_GET_SNDIF_TYPE(pstMbuf) ((pstMbuf)->stPhySendIfInfo.u8PortType)
/* 获取MBUF中发送接口框号 */
#define SFE_MBUF_GET_SNDIF_FRAMEID(pstMbuf) ((pstMbuf)->stPhySendIfInfo.u8FrameID)
/* 获取MBUF中发送接口槽号 */
#define SFE_MBUF_GET_SNDIF_SLOTID(pstMbuf) ((pstMbuf)->stPhySendIfInfo.u16SlotID)
/* 获取MBUF中发送接口端口号 */
#define SFE_MBUF_GET_SNDIF_PORTNO(pstMbuf) ((pstMbuf)->stPhySendIfInfo.u16PortNo)
/* 获取MBUF中发送接口子端口号 */
#define SFE_MBUF_GET_SNDIF_SUBPORTNO(pstMbuf) ((pstMbuf)->stPhySendIfInfo.u16lSubPortNo)


/* 获取MBUF中接收接口类型 */
#define SFE_MBUF_GET_RCVIF_TYPE(pstMbuf) ((pstMbuf)->stPhyRecvIfInfo.u8PortType)
/* 获取MBUF中接收接口框号 */
#define SFE_MBUF_GET_RCVIF_FRAMEID(pstMbuf) ((pstMbuf)->stPhyRecvIfInfo.u8FrameID)
/* 获取MBUF中接收接口槽号 */
#define SFE_MBUF_GET_RCVIF_SLOTID(pstMbuf) ((pstMbuf)->stPhyRecvIfInfo.u16SlotID)
/* 获取MBUF中接收接口端口号 */
#define SFE_MBUF_GET_RCVIF_PORTNO(pstMbuf) ((pstMbuf)->stPhyRecvIfInfo.u16PortNo)
/* 获取MBUF中接收接口子端口号 */
#define SFE_MBUF_GET_RCVIF_SUBPORTNO(pstMbuf) ((pstMbuf)->stPhyRecvIfInfo.u16lSubPortNo)


/* 指向报文的链路层首部 */
#define SFE_MBUF_GET_LINK_LAYER_HEAD(pstMbuf) (((pstMbuf)->pu8LinkLayerHead))
/* 指向报文的网络层首部 */
#define SFE_MBUF_GET_NET_LAYER_HEAD(pstMbuf) (((pstMbuf)->pu8NetLayerHeader))
/* 指向报文的传输层首部 */
#define SFE_MBUF_GET_TRAN_LAYER_HEAD(pstMbuf) (((pstMbuf)->pu8TranLayerHeader))

/* 获取IP头中的源地址 */
#define SFE_MBUF_GET_PKT_SRC_IP(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
                                      ((SFE_IP_S *)(VOID *)((pstMbuf)->pu8NetLayerHeader))->ip_stSrc : 0)
/* 获取IP头中的目的地址 */
#define SFE_MBUF_GET_PKT_DST_IP(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
                                      ((SFE_IP_S *)(VOID *)((pstMbuf)->pu8NetLayerHeader))->ip_stDst : 0)
/* 获取IP头中的协议号 */
#define SFE_MBUF_GET_PKT_PRO(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
                                      ((SFE_IP_S *)(VOID *)((pstMbuf)->pu8NetLayerHeader))->ip_chPr : 0)
/* 获取报文TOS */
#define SFE_MBUF_GET_PKT_TOS(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
                                      ((SFE_IP_S *)(VOID *)((pstMbuf)->pu8NetLayerHeader))->ip_chTOS : 0)

/* 获取报文源端口，分片报文从MBUF中取, 非分片报文从报文中取,
   TCP和UDP的端口号位置一样,所以这里直接使用UDP结构取端口号字段 */
#define SFE_MBUF_GET_PKT_SRC_PORT(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
            (((pstMbuf)->stPktCommonInfo.u32IsFragMent)? \
               ((pstMbuf)->stPktNetInfo.u16PktSrcPortOrIcmpType)\
                : (((SFE_UDP_S *)((pstMbuf)->pu8NetLayerHeader \
                     + ((((SFE_IP_S *)((pstMbuf)->pu8NetLayerHeader))->ip_chHLen) << 2 )))->u16SrcPort))\
             : 0)

/* 获取报文目的端口，分片报文从MBUF中取, 非分片报文从报文中取,
   TCP和UDP的端口号位置一样,所以这里直接使用UDP结构取端口号字段 */
#define SFE_MBUF_GET_PKT_DST_PORT(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
            (((pstMbuf)->stPktCommonInfo.u32IsFragMent)? \
               ((pstMbuf)->stPktNetInfo.u16PktDstPortOrIcmpCode)\
                : (((SFE_UDP_S *)((pstMbuf)->pu8NetLayerHeader \
                     + ((((SFE_IP_S *)((pstMbuf)->pu8NetLayerHeader))->ip_chHLen) << 2 )))->u16DstPort))\
             : 0)

/* 获取报文ICMP类型,不支持ICMP分片报文信息的获取,直接从报文中获取,获取值为0xFF时表示事无效值 */
#define SFE_MBUF_GET_PKT_ICMP_TYPE(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
            (*((UINT8 *)((pstMbuf)->pu8NetLayerHeader \
               + ((((SFE_IP_S *)((pstMbuf)->pu8NetLayerHeader))->ip_chHLen) << 2 )))) : 0xFF)

/* 获取报文ICMP code,不支持ICMP分片报文信息的获取,直接从报文中获取,获取值为0xFF时表示事无效值 */
#define SFE_MBUF_GET_PKT_ICMP_CODE(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
            (*((UINT8 *)((pstMbuf)->pu8NetLayerHeader \
               + ((((SFE_IP_S *)((pstMbuf)->pu8NetLayerHeader))->ip_chHLen) << 2 ) + 1))) : 0xFF)

/* 获取报文VRF索引 */
#define SFE_MBUF_GET_PKT_VRFINDEX(pstMbuf) (((pstMbuf)->stPktCommonInfo.u32VrfIndex))

/* 设置MBUF中的报文VRF索引 */
#define SFE_MBUF_SET_PKT_VRFINDEX(pstMbuf,u32VrfIndexM) (((pstMbuf)->stPktCommonInfo.u32VrfIndex) = u32VrfIndexM)

/* 类型强制转换, 调用时必须保证MBUF非NULL，并且调用该处理之后必须判断返回值是否为NULL */
#define SFE_MBUF_MTOD(pstMBufM, DataTypeM) (((pstMBufM)->pstDBD) ? ((DataTypeM)((pstMBufM)->pstDBD->pu8Data)) : NULL)


/*******************************************************************************
*    Func Name: SFE_MBUF_BACKWARD_MOVE
* Date Created: 2009-07-28
*       Author: wangmingxia/luowentong
*  Description: 在首部增加MBUF中的数据长度
*        Input: pstMbuf: MBUF指针
*               u32Length: 增加的首部长度
*       Output: u32Result: 返回结果
*       Return: 成功: SFE_MBUF_OK
*               失败: 返回错误码
*      Caution: 必须保证第一个DB首部有足够的空闲空间，必须要保证MBUF不空
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-28   wangmingxia/luowentong    Create
*
*******************************************************************************/
#define SFE_MBUF_BACKWARD_MOVE(pstMbuf, u32Length, u32Result) \
{\
    if ((NULL != ((pstMbuf)->pstDBD)) && (NULL != ((pstMbuf)->pstDBD->pu8Data)))\
    {\
        /*lint -e946*/\
        if ((u32Length) <= ((pstMbuf)->pstDBD->pu8Data) - ((pstMbuf)->pstDBD->pu8DataBlock))\
        /*lint +e946*/\
        {\
            (pstMbuf)->pstDBD->pu8Data -= (u32Length);\
            (pstMbuf)->pstDBD->u32DataLength += (u32Length);\
            (pstMbuf)->u32TotalDataLength += (u32Length);\
            (u32Result) = SFE_MBUF_OK;\
        }\
        else\
        {\
            (u32Result) = SFE_MBUF_DB_LENGTH_NOTENOUGH_BACKWARD;\
        }\
    }\
    else\
    {\
        (u32Result) = SFE_MBUF_NULL_POINTER_BACKWARD;\
    }\
}

/*******************************************************************************
*    Func Name: SFE_MBUF_FORWARD_MOVE
* Date Created: 2009-07-28
*       Author: wangmingxia/luowentong
*  Description: 在首部减少MBUF中的数据长度
*        Input: pstMbuf: MBUF指针
*               u32Length: 减少的首部长度
*       Output: u32Result: 返回结果
*       Return: 成功: SFE_MBUF_OK
*               失败: 返回错误码
*      Caution: 必须保证第一个DB的数据长度大于等于u32Length,必须要保证MBUF不空
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-28   wangmingxia/luowentong    Create
*
*******************************************************************************/
#define SFE_MBUF_FORWARD_MOVE(pstMbuf, u32Length, u32Result) \
{\
    if ((NULL != ((pstMbuf)->pstDBD)) && (NULL != ((pstMbuf)->pstDBD->pu8Data)))\
    {\
        if ((u32Length) <= ((pstMbuf)->pstDBD->u32DataLength))\
        {\
            (pstMbuf)->pstDBD->pu8Data += (u32Length);\
            (pstMbuf)->pstDBD->u32DataLength -= (u32Length);\
            (pstMbuf)->u32TotalDataLength -= (u32Length);\
            (u32Result) = SFE_MBUF_OK;\
        }\
        else\
        {\
            (u32Result) = SFE_MBUF_DB_LENGTH_NOTENOUGH_FORWARD;\
        }\
    }\
    else\
    {\
        (u32Result) = SFE_MBUF_NULL_POINTER_FORWARD;\
    }\
}

/* 获取MBUF中记录的扩展信息中的连接ID */
#define SFE_MBUF_GET_CONNTION_ID(pstMbufM)  ((pstMbufM)->pstExpandInfo->u32ConnectionId)
/* 获取MBUF中记录的扩展信息中的流方向 */
#define SFE_MBUF_GET_DIRECTION(pstMbufM)    ((pstMbufM)->pstExpandInfo->u32FlowDirection)
/* 获取MBUF中记录的扩展信息中的报文分发KEY值 */
#define SFE_MBUF_GET_PKTDISPATCHKEY(pstMbufM)    ((pstMbufM)->pstExpandInfo->u32PktDispatchKey)
/* 设置MBUF中记录的扩展信息中的连接ID */
#define SFE_MBUF_SET_CONNTION_ID(pstMbufM, u32ConnectionIdM) (((pstMbufM)->pstExpandInfo->u32ConnectionId)= (u32ConnectionIdM))
/* 设置MBUF中记录的扩展信息中的流方向 */
#define SFE_MBUF_SET_DIRECTION(pstMbufM, u32DirectionM) (((pstMbufM)->pstExpandInfo->u32FlowDirection)= (u32DirectionM))
/* 设置MBUF中记录的扩展信息中的报文分发KEY值 */
#define SFE_MBUF_SET_PKTDISPATCHKEY(pstMbufM, u32DispatchKeyM) (((pstMbufM)->pstExpandInfo->u32PktDispatchKey)= (u32DispatchKeyM))

/* 获取MBUF中记录的产品私有标志 */
#define SFE_MBUF_GET_USERFLAG(pstMbufM)  ((pstMbufM)->pstExpandInfo->stUsrPrivateData.u8UserFlag)
/* 获取MBUF中记录的产品自有信息指针1 */
#define SFE_MBUF_GET_USERPOINTER_1(pstMbufM)  ((pstMbufM)->pstExpandInfo->stUsrPrivateData.pu8UserPointer1)
/* 获取MBUF中记录的产品自有信息指针2 */
#define SFE_MBUF_GET_USERPOINTER_2(pstMbufM)  ((pstMbufM)->pstExpandInfo->stUsrPrivateData.pu8UserPointer2)
/* 设置MBUF中记录的产品私有标志 */
#define SFE_MBUF_SET_USERFLAG(pstMbufM, u8UserFlagM)  (((pstMbufM)->pstExpandInfo->stUsrPrivateData.u8UserFlag) = (u8UserFlagM))
/* 设置MBUF中记录的产品自有信息指针1 */
#define SFE_MBUF_SET_USERPOINTER_1(pstMbufM, pu8UserPointer1M)  (((pstMbufM)->pstExpandInfo->stUsrPrivateData.pu8UserPointer1) = (pu8UserPointer1M))
/* 设置MBUF中记录的产品自有信息指针2 */
#define SFE_MBUF_SET_USERPOINTER_2(pstMbufM, pu8UserPointer2M)  (((pstMbufM)->pstExpandInfo->stUsrPrivateData.pu8UserPointer2) = (pu8UserPointer2M))

/* 获取MBUF中记录的IP报文长度,即包括IP头,传输层头,纯数据的总长度 */
#define SFE_MBUF_GET_IP_PKT_LEN(pstMbufM)    ((pstMbufM)->pstExpandInfo->u32IpPktLen)


#ifdef  __cplusplus
}
#endif

#endif


