/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfib4_api.h
*
*  Project Code: VISPV100R007
*   Module Name:
*  Date Created: 2008-04-08
*        Author: zengshaoyang62531
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _SFIB4_API_H_
#define _SFIB4_API_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define FIB4_OK                     VOS_OK
#define FIB4_ERR                    VOS_ERR
#define FIB4_ERR_NOT_ENOUGH_MEM    (VOS_ERR + 1)
#define FIB4_ERR_Q_WRITE           (VOS_ERR + 2)
#define FIB4_ERR_EV_WRITE          (VOS_ERR + 3)
#define FIB4_ERR_RTMSG_INVALID     (VOS_ERR + 4)
#define FIB_ERR_NEXTHOP_OUTIF      (VOS_ERR + 5)      /* 添加路由时，须指定下一跳或者出接口 */
#define FIB_ERR_NEXTHOP_INVALID    (VOS_ERR + 6)      /* 无效的下一跳地址 */
#define FIB_ERR_DESTADDR_INVALID   (VOS_ERR + 7)      /* 无效的目的地址 */
#define FIB_ERR_OUTIF_WANTED       (VOS_ERR + 8)      /* 须指定出接口 (当指定的下一跳地址是本级地址时) */
#define FIB_ERR_POLICY_CANNTSET    (VOS_ERR + 9)      /* 当前路由策略不支持改变 */
#define FIB_ERR_POLICY_INVALID     (VOS_ERR + 10)     /* 指定的路由策略不支持 */
#define FIB_ERR_NULL_POINTER       (VOS_ERR + 11)     /* 输入指针为空 */
#define FIB_ERR_PRIORITY_INVALID   (VOS_ERR + 12)     /* 路由优先级非法 */
#define FIB_ERR_MASKLEN_INVALID    (VOS_ERR + 13)     /* 掩码长度非法 */
#define FIB_ERR_INVALID_WLHANDLE   (VOS_ERR + 14)     /* 无效的Waitlist句柄 */
#define FIB_NOT_FIND_ROUTE         (VOS_ERR + 15)     /* Added by jiangtao for deleting route item but not find */
#define FIB_HA_IS_SMOOTHING        (VOS_ERR + 16)     /* z55157，HA正在平滑处理或手动倒换处理时，不可对接口进行配置 */
#define FIB_ERR_NEXTHOP_WANTED     (VOS_ERR + 17)     /* z62531, 必须指定next-hop */
#define FIB_ERR_NEXTHOP_OWN        (VOS_ERR + 18)     /* z62531, next-hop为本机地址 */
#define FIB_ERR_DESTADDR_INVALID_2 (VOS_ERR + 19)     /* 无效的目的地址 */
#define FIB_ERR_DESTADDR_INVALID_3 (VOS_ERR + 20)     /* 无效的目的地址 */
#define FIB_ERR_NEXTHOP_INVALID_2  (VOS_ERR + 21)     /* 无效的下一跳地址 */
#define FIB_ERR_NEXTHOP_INVALID_3  (VOS_ERR + 22)     /* 无效的下一跳地址 */
#define FIB_ERR_ROUTEITEM_EXCEED   (VOS_ERR + 23)     /* RIB表空间超出 */
#define FIB_ERR_MSGSEND_FAIL       (VOS_ERR + 24)     /* 消息发送失败 */
#define FIB_ERR_RTMSG_NULL         (VOS_ERR + 25)     /* rtmsg is null */
#define FIB_ERR_RT_NULL            (VOS_ERR + 26)     /* router entry is null */
#define FIB_ERR_DELETE_RT          (VOS_ERR + 27)     /* fail to delete router entry */
#define FIB_ERR_CLEAR_ZONE         (VOS_ERR + 28)     /* fail to clear zone */
#define FIB_ERR_MSG_TYPE           (VOS_ERR + 29)     /* the message type is wrong */
#define FIB_ERR_WAITLIST_GET       (VOS_ERR + 30)     /* fail to get waitlist */
#define FIB_ERR_INVALID_INTERFACE  (VOS_ERR + 31)     /*无效的出接口，如inlookback接口 */
#define FIB_ERR_COMP_NULL          (VOS_ERR + 32)     /* fib4组件为空 */
#define FIB_ERR_MALLOC_FAIL        (VOS_ERR + 33)     /* malloc fail*/
#define FIB_ERR_SCAN_FAIL          (VOS_ERR + 34)     /* 遍历SFIB4失败*/
#define FIB_ERR_INVALID_FLAG       (VOS_ERR + 35)     /* 标记值无效 */
#define FIB_ERR_INVALID_IPCTL      (VOS_ERR + 36)     /* IP控制块无效 */
#define FIB_ERR_INVALID_IFTYPE     (VOS_ERR + 37)     /* 无效的接口类型 */
#define FIB_ERR_INVALID_INSTANCE   (VOS_ERR + 38)     /* 无效的实例号*/
#define FIB_ERR_INVALID_RTNUM      (VOS_ERR + 39)     /* 无效的路由数量*/
#define FIB_ERR_IS_L2PORT          (VOS_ERR + 40)     /* 输入的目标接口是二层端口 */
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define FIB_ERR_GET_VRFINDEX       (VOS_ERR + 41)     /* 获取VRF实例号失败*/
#define FIB_ERR_IF_NOT_IN_VRF      (VOS_ERR + 42)     /* 出接口不在指定的VRF中*/
#define FIB_ERR_VRF_NOT_INIT       (VOS_ERR + 43)     /* VRF未初始化*/
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#define FIB_ERR_OPERA              (VOS_ERR + 44)
#define FIB_ERR_ROUTE_TYPE         (VOS_ERR + 45)

#define FIB_ERR_RM_TYPE            (VOS_ERR + 46)     /*用户预配置路由模式不为SRM，调用了操作VISP RIB的接口*/
                                                      /*直接返回错误(因为当前不为SRM时，是没有初始化RIB资源的)*/

#define RIB4_ERR_VRFID_OUT_BOUND   (VOS_ERR + 47)     /* 获取的VRF实例号超过RIB表的最大路由维数*/
#define RIB4_ERR_NO_USE_ENTRY      (VOS_ERR + 48)     /* 没有可用的下一个路由节点*/
/* 新增错误码请加到FIB_ERROR_CODE_E中 */

/*added by zhangliangzhi 00187023, SRM-RIB6查询, 2011/8/12   问题单号:C06新需求 */
#define  TCPIP_RIB4_MAX_VRFNAME_LENGTH   31      /*和TCPIP_MAX_VRFNAME_LENGTH保持一致*/

typedef struct tagTCPIP_RIB_RT4_ENTRY
{
    ULONG  ulRtDestAddr;         /* 目的地址（主机序） */
    ULONG  ulRtDestPrefLen;      /* 掩码长度 */
    ULONG  ulRtNextHopAddr;      /* 下一跳（主机序） */
    ULONG  ulRtIfIndex;          /* 出接口索引 */
    ULONG  ulRtFlags;            /* 路由标记 */
    ULONG  ulRtPri;              /* 路由优先级 */
    ULONG  ulRtProto;            /* 路由协议类型 */
    ULONG  ulRtUse;              /* 是否有效 */
    ULONG  ulPmtu;
    CHAR   szVrfName[TCPIP_RIB4_MAX_VRFNAME_LENGTH + 1];        /* VRF名称 */
} TCPIP_RIB_RT4_ENTRY_S;
/*End of added by zhangliangzhi 00187023, 2011/8/12   问题单号:C06新需求 */


/* ZENGSHAOYANG:路由模块的错误码都用宏定义来表示，且比较分散，不方便后续添加及维护
新增一个枚举，错误码从101开始编号 */
typedef enum tagFIB_ERROR_CODE
{
    FIB4_GET_END = VOS_ERR + 100  ,    /* 表项到末尾了 */
    FIB4_GET_FAIL                 ,    /* 获取表项失败 */
    FIB4_GET_FAIL_BY_VRF          ,    /* 通过VRF获取表项失败 */
    FIB4_GET_FAIL_CLOSE           ,    /* 关闭waitlist失败 */
    FIB4_GET_FAIL_OPEN            ,    /* 打开waitlist失败*/
    FIB4_GET_RT_FAIL_CLOSE        ,    /* 获取表项失败，直接关闭waitlist*/
    FIB4_GET_ERR_CLOSE_VRF        ,    /* 指定VRF查询时，关闭waitlist失败 */
    FIB4_GET_FAIL_CLOSE_VRF       ,    /* 指定VRF查询时，GET表项失败，且关闭waitlist失败 */
    FIB4_GET_VRF_NET_FAIL_CLOSE   ,    /* 指定VRF+网段查询,关闭waitlist失败 */
    FIB4_GET_FAIL_VRF_NET_CLOSE   ,    /* 指定VRF+网段查询,获取表项失败且关闭waitlist失败 */
    FIB4_GET_FAIL_CLOSE_NETIP     ,    /* 指定网段查询时关闭waitlist失败 */
    FIB4_GET_FAIL_OPEN_NETIP      ,    /* 指定网段查询时打开waitlist失败 */
    FIB_ERR_VRF_NAMELONG               /* VRF名字长度大于31*/
}FIB_ERROR_CODE_E;

#define FIB4_STATIC_ADDR_ADD       1
#define FIB4_STATIC_ADDR_DEL       0



#define FIB4_RTMSG_ADD             1    /* 添加路由 */
#define FIB4_RTMSG_DEL             2    /* 删除路由 */
#define FIB4_RTMSG_CLEAR           3    /* 清空路由 */
#define FIB4_RTMSG_REFRESH         4    /* 刷新路由 */
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define FIB4_RTMSG_CLEARSPEC       5    /* 清空指定路由 */
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*Add by h55555 for VISPV1R7C02 小需求开发*/

#define FIB_RTNUM_LOW_LEVEL       1000
#define FIB_RTNUM_HIGH_LEVEL      100000

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define FIB_IPV4RM_INSTANCE       1
#define FIB_IPV6RM_INSTANCE       2

#define FIB_RM_TYPE_IPV4          1
#define FIB_RM_TYPE_IPV6          2
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#define FIB_RTWARN_INIT           0
#define FIB_RTWARN_OUTPUT         1
#define FIB_RTWARN_CANCEL         2

typedef enum tagRouteStrategy
{
    RS_ONE_BY_ONE = 0,    /* 0 负荷分担，轮循方式 */
    RS_NEWEST_FIRST,      /* 1 最新路由有效 */
    RS_OLDEST_FIRST,      /* 2 最老路由有效 */
    RS_PRI_BASED,         /* 3 接口优先级最高有效 */
    RS_BFCR,              /* 4 五元组报文流保序 */
    RS_RTPRI,             /* 5 路由优先级 */
    /*Added by likaikun00213099, DTS2014052908384 新增平衡路由算法, 2014/6/6 */
    RS_BFCR_DSCP,         /* 6 三元组和DSCP 报文流保序 */
    RS_END
}ROUTE_STRATEGY_E;

typedef enum tagFibNpMode
{
    FIB_NP_DOWNALL = 0, /*下发全部路由至NP*/
    FIB_NP_DOWNBEST,    /*下发最优路由至NP*/
    FIB_NP_END
}FIBNPMODE_E;

typedef enum tagUpdateFibNpMode
{
    UPDATE_FIB_ADDTHENDEL,   /*先下发增加，后下发删除*/
    UPDATE_FIB_DELTHENADD    /*先下发删除，后下发增加*/
}UPDATEFIBNPMODE_E;

#ifndef MAX_IF_NAME_LENGTH
#define MAX_IF_NAME_LENGTH  47   /* 接口名长度 */
#endif

/* One of the data stores maintained by FIB6Agent subsystem. Acts as an unit of external data
interface to be used by FIB6Agent to receive FIB entries from RM. This is defined by RM */
typedef struct tagRTMSG4
{
    USHORT  usType;             /* RTMSG_DEL, RTMSG_ADD, RTMSG_DELETE_ZONE */
    USHORT  usZoneID;           /* zone ID */
    ULONG   ulDestination;
    ULONG   ulNexthop;
    ULONG   ulLocalAddress;
    ULONG   ulIfIndex;          /* index of outgoing interface */
    ULONG   ulATIndex;          /* virtual link index */
    ULONG   ulSlot;
    ULONG   ulFlags;            /* RTF_GATEWAY, RTF_HOST, ...*/
    UCHAR   ucDestPrefixLength;
    UCHAR   ucLocalPrefixLength;
    USHORT  usRTPri;            /* route priority */
    ULONG   ulProto;

    /*Add by h55555 for defect BC3D00951 interface name*/
    UCHAR   ucIfName[MAX_IF_NAME_LENGTH + 1];

    ULONG  ulPmtu;
    /*Add by q62011 for 大规格地址查询速度慢*/
    ULONG   ulLocalIfIndex;
} RTMSG4_S;

/*  One of the data stores maintained by FIB4Container subsystem. It contains route entry
    with various fields as specified below. This structure is used to store external information in
    FIB Table. This can be used in radix node or any other data store based on
    implementation specifics. (to support multi algorithm). */
typedef struct tagTCPIP_RT4_ENTRY
{
     ULONG  ulRt_Dest;
     ULONG  ulRt_Dest_PrefLen;
     ULONG  ulRt_Nexthop;
     ULONG  ulRt_Flags;         /* route flags -RTF_GATEWAY, RTF_HOST */
     ULONG  ulRt_IfIndex;       /* index of outgoing interface */
     ULONG  ulRt_ATIndex;       /* index of virtual link between rt_stLclAddr */
     ULONG  ulRt_Slot;          /* slot num of outgoing interface */
     ULONG  ulRt_Use;           /* metrics to consider */
     ULONG  ulRt_State;
     ULONG  ulRt_Proto;
     ULONG  ulRt_TimeStamp;
     ULONG  ulCacheEntryIndex;  /* used to access corr. cache entry */
     ULONG  ulRt_Loc;           /* local address */
     ULONG  ulRt_Loc_PrefLen;   /* local address mask lenth */
     ULONG  ulRTPri;            /* route priority */
     ULONG  ulPmtu;
} TCPIP_RT4_ENTRY_S;
/* ---------------------------------------SGSN路由维测需求--------------------------------------------- */
/*Added by by pengbinquan pKF34550, 增加查询所有功能, 2011/02/18 问题单号:DTS2011022100676 */
#define SFIB4_VRF_MAX_VRFNAME_LENGTH    31

#define FIB4_SEARCH_ALL                0x00    /*查询所有VRF全部路由 */

#define FIB4_SEARCH_BY_VRF             0x01    /*指定VRF查询[查询指定VRF中的全部路由]*/

#define FIB4_SEARCH_BY_NETIP           0x02    /*指定网段查询[查询全部VRF中的指定路由]*/

#define FIB4_SEARCH_BY_VRF_AND_NETIP   (FIB4_SEARCH_BY_VRF | FIB4_SEARCH_BY_NETIP)    /*指定VRF+网段查询[查询指定VRF中的指定路由]*/


typedef struct tagTCPIP_RIB_FILTER_API
{
    ULONG  ulRtDestAddr;         /* 目的地址（主机序） */
    ULONG  ulRtDestPrefLen;      /* 掩码长度 */
    ULONG  ulRtNextHopAddr;      /* 下一跳（主机序） */
    ULONG  ulRtIfIndex;          /* 出接口索引 */
    CHAR   szVrfName[TCPIP_RIB4_MAX_VRFNAME_LENGTH + 1]; /* VRF名称 */
}TCPIP_RIB_FILTER_API_S;

/* 过滤条件:
1.当过滤条件为空时，查询全部VRF下的全部路由；
如下情况过滤条件都不为空
2.指定VRF查询[查询指定VRF中的全部路由],ulFilterType=FIB4_SEARCH_BY_VRF
3.指定网段查询[查询全部VRF中的指定路由],ulFilterType=FIB4_SEARCH_BY_NETIP
4.指定VRF+网段查询[查询指定VRF中的指定路由],ulFilterType=FIB4_SEARCH_BY_VRF_AND_NETIP
*/
typedef struct tagFIB4_FILTER_COND_API
{
    CHAR  szVrfName[SFIB4_VRF_MAX_VRFNAME_LENGTH + 1]; /*VPN 名字*/
    ULONG ulDstIp;                                     /*目的地址*/
    ULONG ulDstMask;                                   /*掩码长度,请用户填写掩码长度，比如24*/
    ULONG ulFilterType;                                /*过滤条件，见结构体头部的说明*/
}FIB4_FILTER_COND_API_S;

typedef struct tagTCPIP_RT4_ENTRY_BY_VRF
{
     ULONG  ulRt_Dest;
     ULONG  ulRt_Dest_PrefLen;
     ULONG  ulRt_Nexthop;
     ULONG  ulRt_Flags;         /* route flags -RTF_GATEWAY, RTF_HOST */
     ULONG  ulRt_IfIndex;       /* index of outgoing interface */
     ULONG  ulRt_ATIndex;       /* index of virtual link between rt_stLclAddr */
     ULONG  ulRt_Slot;          /* slot num of outgoing interface */
     ULONG  ulRt_Use;           /* metrics to consider */
     ULONG  ulRt_State;
     ULONG  ulRt_Proto;
     ULONG  ulRt_TimeStamp;
     ULONG  ulCacheEntryIndex;  /* used to access corr. cache entry */
     ULONG  ulRt_Loc;           /* local address */
     ULONG  ulRt_Loc_PrefLen;   /* local address mask lenth */
     ULONG  ulRTPri;            /* route priority */
     ULONG  ulVrfIndex;         /* VRF Index*/
     ULONG  ulPmtu;
} TCPIP_RT4_ENTRY_BY_VRF_S;
/* End of Added by pengbinquan pKF34550, 2011/02/18   问题单号:DTS2011022100676 */

/*  One of the data stores maintained by FIB6Agent for providing search interface
    to external modules */
typedef struct tagTCPIP_ROUTE4
{
     USHORT        usZoneID;       /* zone ID */
     /* Modified by likaikun00213099, DTS2014052908384新增平衡路由策略，查询时可以将DSCP作为关键字, 2014/6/6 */
     UCHAR         ucTos;          /* 8bit IP首部TOS字段，如果是DSCP值则需要转换为TOS格式，只有在平衡路由策略为RS_BFCR_DSCP才有意义，其他平衡路由策略下TOS值不起作用*/
     UCHAR         ucPadding_1[1];
     ULONG         ulDestination;
     ULONG         ulNexthop;
     ULONG         ulLocalAddress;
     ULONG         ulIfIndex;  /* index of outgoing interface */
     ULONG         ulATIndex;  /* virtual link index */
     ULONG         ulSlot;
     ULONG         ulFlags;    /* RTF_GATEWAY, RTF_HOST, ...*/
     UCHAR         ucDestPrefixLength;
     UCHAR         ucLocalPrefixLength;
     USHORT        usRTPri;    /* route priority */
     ULONG         ulSrcIPAddr;
     ULONG         ulDstIPAddr;
     ULONG         ulProtocol;
     USHORT        usSrcPort;
     USHORT        usDstPort;

     /* 配置光网OSP平台增加如下两个字段 */
     ULONG         ulVrfIndex;    /*Vrf index*/
     ULONG         ulL3VPNXcIndex;/*查询产品FIB,如果是隧道报文，把该参数传给产品，产品根据该信息获取到Tunnel ID*/
} TCPIP_ROUTE4_S;

/* w60006501添加，五元组路由查询使用的结构体，记录报文的五元组信息 */
/* 该数据结构是为了PTN产品特殊FIB使用, 其他产品不能应用该数据结构 */
typedef struct tagPacketInfo
{
    ULONG  ulSrcIPAddr;     /* FIB查询入参时 网络序 */
    ULONG  ulDstIPAddr;     /* FIB查询入参时 网络序 */
    ULONG  ulProtocol;      /* FIB查询入参时 主机序 */
    USHORT usSrcPort;       /* FIB查询入参时 网络序 */
    USHORT usDstPort;       /* FIB查询入参时 网络序 */
    /* Added by likaikun00213099, DTS2014052908384新增平衡路由策略，查询时可以将DSCP作为关键字, 2014/6/6 */
    UCHAR  ucTos;          /* 8bit IP首部TOS字段，如果是DSCP值则需要转换为TOS格式，只有在平衡路由策略为RS_BFCR_DSCP才有意义，其他平衡路由策略下TOS值不起作用*/
    UCHAR  ucPadding_1[3];
}PACKETINFO_S;

/*  One of the data stores maintained by FIB6Agent for providing search interface
    to external modules */
/* 该数据结构是为了PTN产品特殊FIB使用, 其他产品不能应用该数据结构 */
typedef struct tagROUTE4
{
     USHORT        usZoneID;       /* zone ID */
     UCHAR         ucPadding_1[2];
     ULONG         ulDestination;
     ULONG         ulNexthop;
     ULONG         ulLocalAddress;
     ULONG         ulIfIndex;  /* index of outgoing interface */
     ULONG         ulATIndex;  /* virtual link index */
     ULONG         ulSlot;
     ULONG         ulFlags;    /* RTF_GATEWAY, RTF_HOST, ...*/
     UCHAR         ucDestPrefixLength;
     UCHAR         ucLocalPrefixLength;
     USHORT        usRTPri;    /* route priority */

     ULONG          ulVrfIndex;   /* Vrf index,在该版本,它和usZoneID字段一致,由于R6C05版本产品会用到该字断 */
     ULONG         ulL3VPNXcIndex;/* 查询产品FIB,如果是隧道报文，把该参数传给产品，产品根据该信息获取到Tunnel ID */
     /* End: VISP Support multi-instance project */

     ULONG ulPmtu;

     PACKETINFO_S *pstPacketInfo;
} ROUTE4_S;

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef struct tagTCPIP_RM_CFGSTATIC_S
{
    ULONG Oper;              /*1增加  0:删除*/
    ULONG ulIpAddress;
    ULONG ulMaskLen;
    ULONG ulGateway;
    UCHAR szIfName[MAX_IF_NAME_LENGTH + 1];
    ULONG ulRTPri;
    UCHAR szVrfName[SFIB4_VRF_MAX_VRFNAME_LENGTH + 1];
    ULONG ulPmtu;
}TCPIP_RM_CFGSTATIC_S;
typedef struct tagFIB4_IFNEXTHOP_S
{
    ULONG ulIfIndex;
    ULONG ulNextHop;
    CHAR szVrfName[SFIB4_VRF_MAX_VRFNAME_LENGTH + 1]; /*vrf名*/
}FIB4_IFNEXTHOP_S;

typedef struct tagFIB4_EXACT_ROUTE_S
{
    ULONG ulDstIpAddr;
    ULONG ulMaskLen;
    ULONG ulIfIndex;
    ULONG ulNextHop;
    CHAR szVrfName[SFIB4_VRF_MAX_VRFNAME_LENGTH + 1]; /*vrf名*/
}FIB4_EXACT_ROUTE_S;

/*过滤条件*/
typedef struct tagFIB4_FILTER_S
{
  CHAR szVrfName[SFIB4_VRF_MAX_VRFNAME_LENGTH + 1]; /*VPN 名字*/
} FIB4_FILTER_S;

/*typedef VOID (*NotifyVlinkProcess_HOOK)(ULONG ulIfIndex,ULONG ulPeerAddr,ULONG ulCmd);*/
typedef VOID (*NotifyVlinkProcess_HOOK)(ULONG ulVrfIndex,ULONG ulIfIndex,ULONG ulPeerAddr,ULONG ulCmd);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef ULONG (*GetPriByIfindex_HOOK)(ULONG ulIfindex, ULONG* pulPri);

/* 该数据结构只能PTN特殊场景使用 */
typedef ULONG (*TCPIP_SEARCH_VPN_FIB_FUN)(ROUTE4_S* pstRoute);


/*******************************************************************************
*    Func Name: TCPIP_CloseFibTable
*  Description: unregister waillist object for doubly linked list of route
*        Input: ULONG ulWaitlist:waitlist handle
*       Output:
*       Return: 成功返回VOS_OK,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseFibTable(UINTPTR ulWaitlist);
/*******************************************************************************
*    Func Name: TCPIP_DisableRtByIfNextHop
*  Description: 通过出接口索引和next-hop去使能路由
*        Input: ULONG ulIfIndex:出接口索引
*               ULONG ulNextHop:next-hop地址
*       Output:
*       Return: 成功返回VOS_OK,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_DisableRtByIfNextHop (ULONG ulIfIndex, ULONG ulNextHop);
/*******************************************************************************
*    Func Name: TCPIP_EnableRtByIfNextHop
*  Description: 通过出接口索引和next-hop使能路由
*        Input: ULONG ulIfIndex:出接口索引
*               ULONG ulNextHop:next-hop地址
*       Output:
*       Return: 成功返回VOS_OK,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableRtByIfNextHop (ULONG ulIfIndex, ULONG ulNextHop);
/*******************************************************************************
*    Func Name: TCPIP_ExactDisableRt
*  Description: 精确地去使能路由
*        Input: ULONG ulDstIpAddr:目的地址
*               ULONG ulMaskLen:掩码长度
*               ULONG ulNextHop:next-hop地址
*               ULONG ulIfIndex:出接口索引
*       Output:
*       Return: VOS_OK:成功，失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_ExactDisableRt (ULONG ulDstIpAddr, ULONG ulMaskLen, ULONG ulNextHop, ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_ExactEnableRt
*  Description: 精确地使能路由
*        Input: ULONG ulDstIpAddr:目的地址
*               ULONG ulMaskLen:掩码长度
*               ULONG ulNextHop:next-hop地址
*               ULONG ulIfIndex:出接口索引
*       Output:
*       Return: VOS_OK:成功，失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_ExactEnableRt (ULONG ulDstIpAddr, ULONG ulMaskLen, ULONG ulNextHop, ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetFibEntry
*  Description: Fetches bulk of FIB entries, protected using waitlist
*        Input: ULONG ulWaitlist:waitlist handle
*               ULONG ulRtNumWanted:number of wanted entrys
*               TCPIP_RT4_ENTRY_S *pstRtEntry:point to route entry table
*               ULONG *pulRtNumReturn:number of get entrys
*       Output:
*       Return: 成功返回FIB4_OK,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetFibEntry(UINTPTR ulWaitlist,ULONG ulRtNumWanted,
    TCPIP_RT4_ENTRY_S *pstRtEntry,ULONG *pulRtNumReturn);

/*******************************************************************************
*    Func Name: TCPIP_GetOutIfindexByDstIP
*  Description: 根据目的地址查找出接口索引
*        Input: ULONG ulDIP:  32位网络字节序的地址值
*               ULONG *pulOutIfIndex:出接口指针
*       Output:
*       Return: 成功返回FIB4_OK,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetOutIfindexByDstIP(ULONG ulDIP, ULONG *pulOutIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetRouteCount
*  Description: 获取路由数目
*        Input:
*       Output: ULONG *pulNum:获取的路由数目
*       Return: FIB4_ERR
*               FIB4_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetRouteCount (ULONG *pulNum);
/*******************************************************************************
*    Func Name: TCPIP_GetSFIBDebug
*  Description: Get fib debug switch
*        Input:
*       Output: ULONG *pulDbg: sfib debug switch value
*       Return: FIB4_OK
*               FIB4_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetSFIBDebug(ULONG *pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetSfibHADbg
*  Description: HA调试开关获取函数
*        Input:
*       Output: ULONG *pulDbg:获取的调试开关值
*       Return: VOS_OK:成功
*               VOS_ERR:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetSfibHADbg(ULONG *pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_LookupFIB
*  Description: Searches for the given destination address in the FIB table
*               and fills with the route information if found
*        Input: TCPIP_ROUTE4_S *pstRoute4:Pointer to route entry memory, containing
*                   the destination address, and zoneid
*       Output:  if success,contain search result
*       Return: 成功返回FIB4_OK,失败返回错误码(见sfib4_api.h)
*      Caution: 请注意入参字节序
*               ULONG ulDestination:    目的地址    主机序
*               ULONG ulNexthop:        下一条地址  主机序
*               ULONG ulSrcIPAddr:      源IP        网络序
*               ULONG ulDstIPAddr:      目的IP      网络序
*               ULONG ulProtocol:       协议号      主机序
*               ULONG usSrcPort:        源端口      网络序
*               ULONG usDstPort:        目的端口    网络序
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_LookupFIB(TCPIP_ROUTE4_S *pstRoute4);
/*******************************************************************************
*    Func Name: TCPIP_OpenFibTable
*  Description: register waillist object for doubly linked list of route
*        Input:
*       Output: ULONG *pulWaitlist:waitlist handle
*       Return: 成功返回VOS_OK,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenFibTable(UINTPTR *pulWaitlist);
/*******************************************************************************
*    Func Name: TCPIP_PPI_DownloadStaticRtByNextHop
*  Description: 搜索静态路由或DHCP路由，把符合要求的下发至NP
*        Input: ULONG ulIfIndex:出接口索引
*               ULONG ulNextHop:路由下一跳地址，网络序
*               ULONG ulVlinkIndex:要刷新路由的vlink索引
*       Output:
*       Return: VOS_OK:成功，失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_PPI_DownloadStaticRtByNextHop(ULONG ulIfIndex, ULONG ulNextHop, ULONG ulVlinkIndex);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetPriByIfindexHook
*  Description: 注册通过接口获取接口优先级的钩子函数
*        Input: GetPriByIfindex_HOOK_FUNC pfHookFunc:待注册的通过接口获取接口优先级的钩子函数
*       Output:
*       Return: FIB4_OK:成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetPriByIfindexHook(GetPriByIfindex_HOOK pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncNotifyVlinkProcessHook
*  Description: 注册通知vlink处理的钩子函数
*        Input: NotifyVlinkProcess_HOOK_FUNC pfHookFunc:待注册的通知vlink处理的钩子函数
*       Output:
*       Return: FIB4_OK:成功
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncNotifyVlinkProcessHook(NotifyVlinkProcess_HOOK pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RequestFIB
*  Description: This method is used by FIBAgent for adding/deleteing routes
*        Input: RTMSG4_S* pstMsg:路由项数据结构，提供给用户使用
*       Output:
*       Return: VOS_OK:成功，其他：错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_RequestFIB (RTMSG4_S* pstMsg);
/*******************************************************************************
*    Func Name: TCPIP_RouteAdd
*  Description: 添加静态路由
*        Input: ULONG ulIpAddress:目的地址(主机序)
*               ULONG ulMaskLen:地址掩码
*               ULONG ulGateway:网关地址(主机序,0表示未指定)
*               ULONG ulIfIndex:出接口索引
*               ULONG ulRTPri:路由优先级
*       Output:
*       Return: VOS_OK：成功,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_RouteAdd(ULONG ulIpAddress, ULONG ulMaskLen, ULONG ulGateway,ULONG ulIfIndex,ULONG ulRTPri);
/*******************************************************************************
*    Func Name: TCPIP_RouteDel
*  Description: 删除静态路由
*        Input: ULONG ulIpAddress:目的地址
*               ULONG ulMaskLen:掩码长度
*               ULONG ulGateway:next-hop地址
*               ULONG ulIfIndex:出接口索引
*       Output:
*       Return: VOS_OK:成功，失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_RouteDel(ULONG ulIpAddress, ULONG ulMaskLen,ULONG ulGateway, ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_SetRoutePolicy
*  Description: 在预配置选路策略为基于五元组或基于接口优先级的情况下，在协议栈启
*               动之后，指定选路策略在这两者之间切换，并且实时生效。
*               如果配置为下发最优路由则不能动态切换
*        Input: ULONG ulPolicy:使能选路策略的命令字，0为使能按出接口优先级选路，
*               1为使能五元组路由负荷分担选路。
*       Output:
*       Return: 成功返回VOS_OK,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetRoutePolicy(ULONG ulPolicy);
/*******************************************************************************
*    Func Name: TCPIP_SetSFIBDebug
*  Description: set sfib debug switch.
*        Input: ULONG ulDbg:0 --- off,1 --- on
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern VOID TCPIP_SetSFIBDebug(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_SetSfibHADbg
*  Description: HA调试开关设置函数
*        Input: ULONG ulDbg:设置的调试开关值
*       Output:
*       Return: VOS_OK:成功
*               VOS_ERR:失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetSfibHADbg(ULONG ulDbg);

/*Add by h55555 for defect BC3D00774*/
/*******************************************************************************
*    Func Name: TCPIP_SetWarningRouteNum
* Date Created: 2008-10-28
*       Author: hanna55555
*  Description: 为SGSN用户提供设置告警路由数量值，取值范围为[1000,100000]
*        Input: ULONG ulInstance:实例号，1-IPv4；2-IPv6；
*                  ULONG ulRouteNum:告警路由数量；
*       Output: 
*       Return: FIB4_OK:成功
*                   FIB_ERR_INVALID_INSTANCE:无效的实例号
*                   FIB_ERR_INVALID_RTNUM: 无效的路由数量
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-28    hanna55555       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetWarningRouteNum(ULONG ulInstance, ULONG ulRouteNum);

/*******************************************************************************
*    Func Name: TCPIP_GetWarningRouteNum
* Date Created: 2008-10-28
*       Author: hanna55555
*  Description: 获取设置的告警路由数量值，范围为[1000,100000]
*        Input: ULONG ulInstance:实例号，1-IPv4；2-IPv6；
*       Output: ULONG *pulRouteNum :存储路由告警数量的指针；
*       Return: FIB4_OK:成功
*                   FIB_ERR_INVALID_INSTANCE:无效的实例号
*                   FIB4_ERR: 存储路由数量的入参数量为空
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-28    hanna55555       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetWarningRouteNum(ULONG ulInstance, ULONG *pulRouteNum);

/*******************************************************************************
*    Func Name: TCPIP_ShowWarningRouteNum
* Date Created: 2008-12-27
*       Author: hanna55555
*  Description: 显示设置的告警路由数量值，范围为[1000,100000]
*        Input: ULONG ulInstance:实例号，1-IPv4；2-IPv6；
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-27    hanna55555       Create
*
*******************************************************************************/
extern VOID TCPIP_ShowWarningRouteNum(ULONG ulInstance);
/*******************************************************************************
*    Func Name: TCPIP_DisableRtByIfNextHopByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: 通过出接口索引和next-hop去使能路由
*        Input: ULONG ulIfIndex:出接口索引
*               ULONG ulNextHop:next-hop地址
*       Output:
*       Return: 成功返回VOS_OK,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_DisableRtByIfNextHopByVrf (FIB4_IFNEXTHOP_S *pstInfo);
/*******************************************************************************
*    Func Name: TCPIP_ExactDisableRtByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: 精确地去使能路由
*        Input: ULONG ulDstIpAddr:目的地址
*               ULONG ulMaskLen:掩码长度
*               ULONG ulNextHop:next-hop地址
*               ULONG ulIfIndex:出接口索引
*       Output:
*       Return: VOS_OK:成功，失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_ExactDisableRtByVrf  (FIB4_EXACT_ROUTE_S *pstInfo);
/*******************************************************************************
*    Func Name: TCPIP_ExactEnableRtByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: 精确地使能路由
*        Input: ULONG ulDstIpAddr:目的地址
*               ULONG ulMaskLen:掩码长度
*               ULONG ulNextHop:next-hop地址
*               ULONG ulIfIndex:出接口索引
*       Output:
*       Return: VOS_OK:成功，失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_ExactEnableRtByVrf (FIB4_EXACT_ROUTE_S *pstInfo);
/*******************************************************************************
*    Func Name: TCPIP_OpenFibTableByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: register waillist object for doubly linked list of route
*        Input:
*       Output: ULONG *pulWaitlist:waitlist handle
*       Return: 成功返回VOS_OK,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
ULONG TCPIP_OpenFibTableByVrf(UINTPTR *pulWaitlist, FIB4_FILTER_S *pstFileter) ;
/*******************************************************************************
*    Func Name: TCPIP_GetRouteCount
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: 获取路由数目
*        Input:
*       Output: ULONG *pulNum:获取的路由数目
*       Return: FIB4_ERR
*               FIB4_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
ULONG TCPIP_GetRouteCountByVrf (ULONG *pulNum,CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: TCPIP_EnableRtByIfNextHopByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: 通过出接口索引和next-hop使能路由
*        Input: ULONG ulIfIndex:出接口索引
*               ULONG ulNextHop:next-hop地址
*       Output:
*       Return: 成功返回VOS_OK,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableRtByIfNextHopByVrf (FIB4_IFNEXTHOP_S *pstInfo);

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*******************************************************************************
*    Func Name: TCPIP_SetRouteByVrf
*  Description: 添加静态路由
*        Input: TCPIP_RM_CFGSTATIC_S *pstRmIn:路由信息结构体
*       Output:
*       Return: VOS_OK：成功,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_SetRouteByVrf(TCPIP_RM_CFGSTATIC_S *pstRmIn);
/*******************************************************************************
*    Func Name: TCPIP_GetFibEntryByVrf
*  Description: Fetches bulk of FIB entries, protected using waitlist
*        Input: ULONG ulWaitlist:waitlist handle
*               CHAR *pszVrfName:VRF Name
*               ULONG ulRtNumWanted:number of wanted entrys
*               TCPIP_RT4_ENTRY_S *pstRtEntry:point to route entry table
*               ULONG *pulRtNumReturn:number of get entrys
*       Output:
*       Return: 成功返回FIB4_OK,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetFibEntryByVrf(UINTPTR ulWaitlist,CHAR *pszVrfName,
                ULONG ulRtNumWanted, TCPIP_RT4_ENTRY_S *pstRtEntry,ULONG *pulRtNumReturn);
/*******************************************************************************
*    Func Name: TCPIP_SetRoutePolicyByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: 在预配置选路策略为基于五元组或基于接口优先级的情况下，在协议栈启
*               动之后，指定选路策略在这两者之间切换，并且实时生效。
*               如果配置为下发最优路由则不能动态切换
*        Input: ULONG ulPolicy:使能选路策略的命令字，0为使能按出接口优先级选路，
*               1为使能五元组路由负荷分担选路。
*       Output:
*       Return: 成功返回VOS_OK,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_SetRoutePolicyByVrf(CHAR *pszVrfName,ULONG ulPolicy);
/*******************************************************************************
*    Func Name: TCPIP_GetOutIfindexByDstIPByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: 根据目的地址查找出接口索引
*        Input: ULONG ulDIP:  32位网络字节序的地址值
*               CHAR *szVrfName:VRF实例名
*       Output: ULONG *pulOutIfIndex:出接口指针
*       Return: 成功返回FIB4_OK,失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetOutIfindexByDstIPByVrf(ULONG ulDIP, CHAR *szVrfName, ULONG *pulOutIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_PPI_DownloadStaticRtByNextHop
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: 搜索静态路由或DHCP路由，把符合要求的下发至NP
*        Input: ULONG ulIfIndex:出接口索引
*               ULONG ulNextHop:路由下一跳地址，网络序
*               ULONG ulVlinkIndex:要刷新路由的vlink索引
*       Output:
*       Return: VOS_OK:成功，失败返回错误码(见sfib4_api.h)
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_PPI_DownloadStaticRtByNextHopByVrf(ULONG ulVrfIndex, ULONG ulIfIndex,
                                                                    ULONG ulNextHop, ULONG ulVlinkIndex);
/*******************************************************************************
*    Func Name: TCPIP_SetWarningRouteNumByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: 为SGSN用户提供设置告警路由数量值，取值范围为[1000,100000]
*        Input: ULONG ulInstance:实例号，1-IPv4；2-IPv6；
*               ULONG ulRouteNum:告警路由数量；
*               CHAR *szVrfName:VRF实例号；
*       Output: 
*       Return: FIB4_OK:成功
*                   FIB_ERR_INVALID_INSTANCE:无效的实例号
*                   FIB_ERR_INVALID_RTNUM: 无效的路由数量
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_SetWarningRouteNumByVrf(ULONG ulType,ULONG ulRouteNum,CHAR *szVrfName);
/*******************************************************************************
*    Func Name: TCPIP_GetWarningRouteNumByVrf
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: 获取设置的告警路由数量值，范围为[1000,100000]
*        Input: ULONG ulInstance:实例号，1-IPv4；2-IPv6；
*       Output: ULONG *pulRouteNum :存储路由告警数量的指针；
*       Return: FIB4_OK:成功
*                   FIB_ERR_INVALID_INSTANCE:无效的实例号
*                   FIB4_ERR: 存储路由数量的入参数量为空
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetWarningRouteNumByVrf(ULONG ulType,ULONG *pulRouteNum,CHAR *szVrfName);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*******************************************************************************
*    Func Name: TCPIP_GetRoutePolicyByVrf
* Date Created: 2009-04-08
*       Author: zengshaoyang62531
*  Description: 根据VRF获取平衡路由的选路策略
*        Input: CHAR *pszVrfName:VRF名字
*       Output: ULONG *pulPolicy:平衡路由选路策略
*       Return:
*      Caution: 需补充资料
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetRoutePolicyByVrf(CHAR *pszVrfName,ULONG *pulPolicy);

/*******************************************************************************
*    Func Name: TCPIP_GetRoutePolicy
* Date Created: 2009-04-08
*       Author: zengshaoyang62531
*  Description: 获取平衡路由的选路策略
*        Input:
*       Output: ULONG *pulPolicy:平衡路由的选路策略
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetRoutePolicy(ULONG *pulPolicy);

/*******************************************************************************
*    Func Name: TCPIP_OpenFibTableByFilter
* Date Created: 2010-11-02
*       Author: zengshaoyang62531
*  Description: 根据过滤条件打开路由表的句柄
*        Input: FIB4_FILTER_COND_API_S *pstFilter:过滤条件,参考FIB4_FILTER_COND_API_S结构体说明
*       Output: ULONG *pulHandle:返回的句柄
*       Return:
*      Caution: 当过滤条件为空时，查询全部VRF下的全部路由
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-02   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenFibTableByFilter(UINTPTR *pulHandle, FIB4_FILTER_COND_API_S *pstFilter);

/*******************************************************************************
*    Func Name: TCPIP_GetNextFibEntry
* Date Created: 2010-11-02
*       Author: zengshaoyang62531
*  Description: 根据用户指定的条件，返回给用户一条路由表项
*        Input: ULONG ulHandle:路由句柄　
*       Output: TCPIP_RT4_ENTRY_BY_VRF_S *pstRtEntry:返回的路由表项
*       Return: VOS_OK成功；FIB4_GET_END,路由表项查询结束;其他错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-02   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetNextFibEntry(UINTPTR ulHandle, TCPIP_RT4_ENTRY_BY_VRF_S* pstRtEntry);

/*******************************************************************************
*    Func Name: TCPIP_CloseFibTableByFilter
* Date Created: 2010-11-02
*       Author: zengshaoyang62531
*  Description: 关闭路由句柄，释放相关资源
*        Input: ULONG ulHandle:路由句柄
*       Output: 
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-02   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseFibTableByFilter(UINTPTR ulHandle);

/*******************************************************************************
*    Func Name: TCPIP_Reg_VpnFib
* Date Created: 2008-4-28
*       Author: zhangchunyu(62474)
*  Description: 注册产品查询FIB接口
*        Input: TCPIP_SEARCH_VPN_FIB_FUN pfSearchFib: 产品查询FIB函数
*       Output:
*       Return: FIB4_OK/FIB4_ERR    成功/失败
*      Caution: 该接口只能PTN产品特殊场景调用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-4-28    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_Reg_VpnFib(TCPIP_SEARCH_VPN_FIB_FUN pfSearchFib);

/*******************************************************************************
*    Func Name: TCPIP_Search_VispFIB
* Date Created: 2008-5-6
*       Author: zhangchunyu(62474)
*  Description: 此函数提供给OSP使用，为了支持三层VPN,FIB分为VISP FIB 和产品FIB,
*               OSP使用VISP FIB,产品使用自己的FIB.VISP内部查询FIB通过函数
*               IP_FIB_AllocValid查询，在该函数里判断是否注册产品FIB如果注册产品FIB,
*               则OSP判断是否是OSP的接口，如果是OSP的接口则查询VISP FIB,否则查询产品FIB
*        Input: ROUTE4_S* pstRoute:
*       Output:
*       Return: 0/非0  成功/失败
*      Caution: 该接口只能PTN产品特殊场景调用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-5-6    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_Search_VispFIB (ROUTE4_S* pstRoute);

/*******************************************************************************
*    Func Name: TCPIP_OpenRib4Table
* Date Created: 2011-08-12
*       Author: zhangliangzhi00187023
*  Description:  通过传入的VRF名称，获取查询句柄。
*        Input:  CHAR * pszVrfName  : 传入VRF的名称
*       Output: ULONG *pulWaitlist : 传出句柄
*       Return: RIB4_OK,RIB4_ERR_GET_VRFINDEX,RIB4_ERR_NULL_POINTER,
*                     RIB4_ERR_VRFID_OUT_BOUND,RIB4_ERR_MALLOC_FAIL
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   zhangliangzhi00187023                 Create
*
*******************************************************************************/
ULONG TCPIP_OpenRib4Table(UINTPTR *pulWaitlist, CHAR *pszVrfName);

/******************************************************************************
*
*    Func Name: TCPIP_GetRib4Entry
* Date Created: 2011-08-12
*       Author: zhangliangzhi00187023
*  Description:  通过查询句柄，获取下一个节点。
*       Input:  ULONG ulWaitlist  : 查询句柄
*       Output:  TCPIP_RIB_RT4_ENTRY_S *pstRtEntry : 查询出来的下一个节点
*       Return: RIB4_OK,RIB4_ERR_NULL_INPUT,RIB4_ERR_GET_VRFINDEX,RIB4_ERR_NO_USE_ENTRY
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   zhangliangzhi00187023                 Create
*
*******************************************************************************/
ULONG TCPIP_GetRib4Entry(UINTPTR ulWaitlist, TCPIP_RIB_RT4_ENTRY_S *pstRtEntry);

/*******************************************************************************
*    Func Name: TCPIP_CloseRib4Table
* Date Created: 2011-08-12
*       Author: zhangliangzhi00187023
*  Description:  关闭 查询句柄。
*        Input:  ULONG ulWaitlist: 查询句柄
*       Output: 
*       Return: RIB4_OK,RIB4_ERR_HANDLE
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   zhangliangzhi00187023                 Create
*
*******************************************************************************/
ULONG TCPIP_CloseRib4Table(UINTPTR ulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_ShowRib4ByVrfName
* Date Created: 2011-08-12
*       Author: zhangliangzhi00187023
*  Description: 显示IPv4 RIB路由表项信息。
*        Input: CHAR *pszVrfName: VRF的名称
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   zhangliangzhi00187023                 Create
*
*******************************************************************************/
VOID TCPIP_ShowRib4ByVrfName(CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: TCPIP_OpenRibTableByFilter
* Date Created: 2012-09-18
*       Author: zhongyu206043
*  Description: 打开查询Rib路由的句柄，支持过滤查询
*        Input: TCPIP_RIB_FILTER_API_S *pstFilter:过滤条件，当前仅支持目的地址、
*               掩码长度、下一跳、出接口索引、VPN名字。其中目的地址、掩码作、
*               VPN名字为必须的匹配条件；
*               下一跳和出接口索引支持为0，为0时不匹配，非0则进行匹配；
*       Output: ULONG *pulHandle: 查询句柄
*       Return: FIB4_OK          成功
*               其他             失败
*      Caution: 如果目的VRF名称、地址或者掩码长度为0，则按照0来进行匹配，不支持这3
*               个字段的模糊查询
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-18   zhongyu206043           Create
*               zhangliangzhi(187023)
*******************************************************************************/
ULONG TCPIP_OpenRibTableByFilter(UINTPTR *pulHandle,TCPIP_RIB_FILTER_API_S *pstFilter);

/*******************************************************************************
*    Func Name: TCPIP_GetRib4EntryByFilter
* Date Created: 2012-09-18
*       Author: zhongyu206043
*  Description: 获取Rib路由信息
*        Input: ULONG ulHandle:查询句柄
*       Output: TCPIP_RIB_RT4_ENTRY_S *pstRtEntry:Rib路由信息
*       Return: FIB4_OK          成功
*               其他             失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-18   zhongyu206043           Create
*               zhangliangzhi(187023)
*******************************************************************************/
ULONG TCPIP_GetRib4EntryByFilter(UINTPTR ulHandle, TCPIP_RIB_RT4_ENTRY_S *pstRtEntry);

/*******************************************************************************
*    Func Name: TCPIP_CloseRibTableByFilter
* Date Created: 2012-09-18
*       Author: zhongyu206043
*  Description: 关闭查询句柄
*        Input: ULONG ulHandle:查询句柄
*       Output: 
*       Return: FIB4_OK          成功
*               其他             失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-18   zhongyu206043           Create
*               zhangliangzhi(187023)
*******************************************************************************/
ULONG TCPIP_CloseRibTableByFilter(UINTPTR ulHandle);


ULONG TCPIP_NotifyIfPriChange(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetBalTable
* Date Created: 2013-09-12
*       Author: qinyun62011
*  Description: 指定精确目的地址和掩码查询平衡路由信息
*        Input: pstFilter:过滤条件，当前仅支持VRF索引、目的地址、掩码长度、
*               下一跳、出接口索引、路由FLAG字段。其中VRF索引、目的地址、
*               掩码长度为必须的匹配条件；
*                 pulNumofTable: 数组pstEntryTable的个数
*       Output: pstEntryTable: 平衡路由信息(RTMSG4_S结构的数组)
*                 pulNumofTable: 获取到的路由个数
*       Return: FIB4_OK          成功
*               其他             失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-09-12   qinyun62011           Create
*******************************************************************************/
ULONG TCPIP_GetBalTable(RTMSG4_S *pstFilter,RTMSG4_S *pstEntryTable, ULONG *pulNumofTable);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SFIB4_API_H_ */

