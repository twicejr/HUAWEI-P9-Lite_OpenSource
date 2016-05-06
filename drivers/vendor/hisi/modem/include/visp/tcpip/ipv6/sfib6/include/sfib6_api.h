
/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfib6_api.h
*
*  Project Code: VISPV1R7
*   Module Name:   
*  Date Created: 2008-3-9
*        Author: wangbin(62223)
*   Description: SFIB6模块对外提供的头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-3-8 wangbin(62223)     Create the first version.
*
*******************************************************************************/
#ifndef _SFIB6_API_H_
#define _SFIB6_API_H_

#ifdef __cplusplus
extern "C"{
#endif

#define FIB6_OK                 VOS_OK
#define FIB6_ERR                VOS_ERR
#define SFIB6_GENERAL_ERR       VOS_ERR + 1
#define SFIB6_NOT_FIND_ROUTE    VOS_ERR + 2
#define SFIB6_ERR_SCAN_FAIL     VOS_ERR + 3
#define FIB6_NOT_REGISTER       VOS_ERR + 4
#define FIB6_MALLOC_FAIL        VOS_ERR + 5
#define FIB6_GET_RTENTRY_ERR    VOS_ERR + 6
#define FIB6_IS_L2PORT          VOS_ERR + 7 /*输入的目标接口是二层端口*/
#define FIB6_ERR_RM_TYPE        VOS_ERR + 8 /*RTM模式下*/
#define FIB6_ERR_DEST_ADDR      VOS_ERR + 9 /*目的地址非法*/
#define FIB6_ERR_IF_NULL        VOS_ERR + 10/*接口为空*/
#define FIB6_ERR_IF_TYPE        VOS_ERR + 11/*接口类型错误*/
#define FIB6_ERR_NULL_PARAM     VOS_ERR + 12/*入参指针为空*/
#define FIB6_ERR_NETRT_PREFIX   VOS_ERR + 13/*网段路由前缀无效*/
#define FIB6_ERR_NETRT_NEXTHOP_INVALID    VOS_ERR + 14/*下一跳必须为指定接口Global地址*/
#define FIB6_ERR_NETRT_DESTADDR_INVALID   VOS_ERR + 15/*目的地址与下一跳和前缀相与结果不等*/
#define FIB6_ERR_NETRT_EXIST              VOS_ERR + 16/*网段路由已经存在*/
#define FIB6_ERR_NETRT_NOT_EXIST          VOS_ERR + 17/*网段路由不存在*/
#define FIB6_ERR_NETRT_GET_IF_INFO        VOS_ERR + 18/*获取网段路由出接口信息出错*/
#define FIB6_ERR_NETRT_IF_TYPE_INVALID    VOS_ERR + 19/*网段路由出接口类型无效*/
#define FIB6_ERR_GET_IPV6VTABLE           VOS_ERR + 20/*获取IPv6虚表出错*/
#define FIB6_ERR_RIB_FULL                 VOS_ERR + 21/*RIB6表已满*/
#define FIB6_ERR_DESTADDR_NOT_GLOBAL      VOS_ERR + 22/*目的地址不是Global地址出错*/
#define FIB6_ERR_PREFIXLEN_INVALID        VOS_ERR + 23/*地址前缀长度非法*/
#define FIB6_ERR_PRIORITY_INVALID         VOS_ERR + 24/*优先级非法*/
#define FIB6_ERR_NEXTHOP_OR_INTF_INVALID  VOS_ERR + 25/*下一跳或出接口无效*/
#define FIB6_ERR_NEXTHOP_IS_OWN_GLOBAL    VOS_ERR + 26/*下一跳是本机Global地址*/
#define FIB6_ERR_BEST_SEARCH_FAIL         VOS_ERR + 27/*查询指定目的地址的路由失败*/
#define FIB6_ERR_INVALID_FLAG             VOS_ERR + 28/*错误的标志*/
#define FIB6_ERR_INVALID_WLHANDLE         VOS_ERR + 29/* 无效的Waitlist句柄 */
#define RIB6_ERR_NO_USE_ENTRY             VOS_ERR + 30/* 没有可用的下一个路由节点*/
#define FIB6_ERR_NULL_POINTER    VOS_ERR + 31
#define FIB6_GET_FAIL_CLOSE      VOS_ERR + 32
#define FIB6_SEARCH_NO_FILTER    VOS_ERR + 33
#define FIB6_ERR_GET_VRFINDEX    VOS_ERR + 34
#define FIB6_GET_FAIL_OPEN          VOS_ERR + 35
#define FIB6_GET_RT_FAIL_CLOSE   VOS_ERR + 36
#define FIB6_GET_FAIL                      VOS_ERR + 37
#define FIB6_GET_END                       VOS_ERR + 38
#define FIB6_GET_ERR_CLOSE_VRF   VOS_ERR + 39
#define FIB6_GET_FAIL_CLOSE_VRF  VOS_ERR + 40
#define FIB6_GET_FAIL_BY_VRF       VOS_ERR + 41
#define FIB6_GET_FAIL_CLOSE_NETIP  VOS_ERR + 42
#define FIB6_GET_FAIL_OPEN_NETIP   VOS_ERR + 43
#define FIB6_GET_VRF_NET_FAIL_CLOSE  VOS_ERR + 44
#define FIB6_GET_FAIL_VRF_NET_CLOSE   VOS_ERR + 45
#define FIB6_ERR_WAITLIST_GET VOS_ERR + 46
/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
#define FIB6_ERR_VRF_NOT_INIT VOS_ERR + 47
#define FIB6_ERR_INVALID_INTERFACE VOS_ERR + 48
#define FIB6_ERR_IF_NOT_IN_VRF VOS_ERR + 49
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */

#define FIB6_RTMSG_ADD             1
#define FIB6_RTMSG_DEL             2
#define FIB6_RTMSG_CLEAR           3
#define FIB6_RTMSG_REFRESH         4    /* added for defect 7034; Guru, 1-03-04 */
#define FIB6_RTMSG_STACK_ADD       5

#define FIB6_OLDRTMSG6             6    /* added for defect 7034; Guru, 1-03-04 */
#define FIB6_NEWRTMSG6             7    /* added for defect 7034; Guru, 1-03-04 */



#define FIB6_STATICRT_MIN_PRIORITY      1
#define FIB6_STATICRT_MAX_PRIORITY      255

#define FIB6_NETRT_MIN_PREFIX      1
#define FIB6_NETRT_MAX_PREFIX      127

/*added by limin00188004, 2011/8/12   问题单号:C06新需求 */
#define  TCPIP_RIB6_MAX_VRFNAME_LENGTH   31      /*和TCPIP_MAX_VRFNAME_LENGTH保持一致*/

#define FIB6_SEARCH_ALL                0x00    /*查询所有VRF全部路由 */

#define FIB6_SEARCH_BY_VRF6             0x01    /*指定VRF查询[查询指定VRF中的全部路由]*/

#define FIB6_SEARCH_BY_NETIP           0x02    /*指定网段查询[查询全部VRF中的指定路由]*/

#define FIB6_SEARCH_BY_VRF_AND_NETIP   (FIB6_SEARCH_BY_VRF6 | FIB6_SEARCH_BY_NETIP)    /*指定VRF+网段查询[查询指定VRF中的指定路由]*/

typedef struct tagTCPIP_RIB_RT6_ENTRY
{
    ULONG  ulRtDestAddr[4];                             /* 目的地址 */
    ULONG  ulRtDestPrefLen;                             /* 掩码长度 */
    ULONG  ulRtNextHopAddr[4];                          /* 下一跳 */
    ULONG  ulRtIfIndex;                                 /* 出接口索引 */
    ULONG  ulRtFlags;                                   /* 路由标记 */
    ULONG  ulRtPri;                                     /* 路由优先级 */
    ULONG  ulRtProto;                                   /* 路由协议类型 */
    ULONG  ulRtUse;                                     /* 是否有效 */
    CHAR   szVrfName[TCPIP_RIB6_MAX_VRFNAME_LENGTH + 1];     /* VRF名称 */
} TCPIP_RIB_RT6_ENTRY_S;
/*End of Modified by limin00188004, 2011/8/12   问题单号:C06新需求 */


/*支持通过预配置的方式配置路由选路策略*/
typedef enum tagRoute6Strategy
{
    RS6_ONE_BY_ONE = 0,    /* 0 负荷分担，轮循方式 */
    RS6_NEWEST_FIRST,      /* 1 最新路由有效 */
    RS6_OLDEST_FIRST,      /* 2 最老路由有效 */
    RS6_PRI_BASED,         /* 3 接口优先级最高有效 */
    RS6_BFCR,              /* 4 五元组报文流保序 */
    RS6_RTPRI,             /* 5 路由优先级 */
    RS6_END
}ROUTE6_STRATEGY_E;

/*支持通过预配置的方式配置路由下发NP的模式*/
typedef enum tagFib6NpMode
{
    FIB6_NP_DOWNALL = 0, /*下发全部路由至NP*/
    FIB6_NP_DOWNBEST,    /*下发最优路由至NP*/
    FIB6_NP_END
}FIB6NPMODE_E;

/*支持通过预配置的方式配置NP路由更新模式*/
typedef enum tagUpdateFib6NpMode
{
    UPDATE_FIB6_ADDTHENDEL,   /*先下发增加，后下发删除*/
    UPDATE_FIB6_DELTHENADD    /*先下发删除，后下发增加*/
}UPDATEFIB6NPMODE_E;

/* 从IPv6报文中提取的信息 */
typedef struct tagPacket6Info 
{
    ULONG ulSrcAddr[4];            /* 源IPv6地址 */            
    ULONG ulDstAddr[4];            /* 目的IPv6地址 */ 
    USHORT usSrcPort;            /* 源端口号 or ICMPv6 Type*/            
    USHORT usDstPort;            /* 目的端口号 or ICMPv6 Code*/            
    UCHAR ucProto;               /* 协议号范围最大值 */
    UCHAR ucReserve[3];         /*保留字段*/
} PACKET6INFO_S;

/*  One of the data stores maintained by FIB6Agent for providing search interface
    to external modules */
/* 该数据结构是为了MCCP产品特殊FIB使用, 其他产品不能应用该数据结构 */
typedef struct tagROUTE6
{
    USHORT usZoneID;            /* vrf id */
    UCHAR  ucPadding_1[2];
    ULONG  aulDestination[4];
    ULONG  aulNexthop[4];
    ULONG  aulLocalAddress[4];        
    ULONG  ulIfIndex;           /* index of outgoing interface */
    ULONG  ulATIndex;           /* virtual link index */
    ULONG  ulSlot;
    ULONG  ulFlags;             /* RTF_GATEWAY, RTF_HOST, ...*/
    UCHAR  ucDestPrefixLength;
    UCHAR  ucLocalPrefixLength;
    UCHAR  ucPadding_2[2];
    ULONG  ulLabel;             /* Inner label */ 
    /* >=1 - > indicates MPLS tunnel, 0 - indicates normal forwarding  
       V6 stack will decide MPLS forwarding/normal forwarding based on this */
    ULONG  ulToken;  
/* Guru: End of addition for 6PE implementation 26th Mar'04 */
    ULONG ulRtPri;            /* route priority */
    PACKET6INFO_S *pstPacket6Info;
} ROUTE6_S;

typedef struct tagTCPIP_RTMSG6
{
    USHORT  usType;
    USHORT  usZoneID;
    ULONG   aulDestination[4];
    ULONG   aulNexthop[4];
    ULONG   aulLocalAddress[4];        
    ULONG   ulIfIndex;          /* index of outgoing interface */
    ULONG   ulATIndex;          /* virtual link index */
    ULONG   ulSlot;
    ULONG   ulFlags; 
    ULONG   ulRTPri;            /* route priority */
    UCHAR   ucDestPrefixLength;
    UCHAR   ucLocalPrefixLength;
    USHORT  ucReserved1;
} TCPIP_RTMSG6_S;

typedef struct tagTCPIP_RT6_ENTRY
{
    ULONG  aulRt_Dest[4];  
    ULONG  ulRt_Dest_PrefLen;
    ULONG  aulRt_Nexthop[4];
    ULONG  ulRt_Flags;        
    ULONG  ulRt_IfIndex;       /* index of outgoing interface */
    ULONG  ulRt_ATIndex;       /* index of virtual link between rt_stLclAddr */
    ULONG  ulRt_Slot;          /* slot num of outgoing interface */
    ULONG  ulRTPri;            /* route priority */
    ULONG  ulRt_Proto;
} TCPIP_RT6_ENTRY_S;

typedef struct tagTCPIP_ROUTE6
{
    ULONG  aulDestination[4];
    ULONG  aulNexthop[4];
    ULONG  aulLocalAddress[4];        
    ULONG  ulIfIndex;           /* index of outgoing interface */
    ULONG  ulATIndex;           /* virtual link index */
    ULONG  ulSlot;
    ULONG  ulFlags;             /* RTF_GATEWAY, RTF_HOST, ...*/
    ULONG  ulRTPri;            /* route priority */
    UCHAR  ucDestPrefixLength;
    UCHAR  ucLocalPrefixLength;
    USHORT usZoneID;            /* zone ID */
    ULONG ulSrcAddr[4];            /* 源IPv6地址 */            
    ULONG ulDstAddr[4];            /* 目的IPv6地址 */ 
    USHORT usSrcPort;            /* 源端口号 or ICMPv6 Type*/            
    USHORT usDstPort;            /* 目的端口号 or ICMPv6 Code*/            
    UCHAR ucProto;               /* 协议号范围最大值 */
    UCHAR ucReserve[3];         /*保留字段*/
} TCPIP_ROUTE6_S;

#ifndef _VRP_IN6ADDR_S
#define _VRP_IN6ADDR_S
typedef   struct    tagVRPIN6Addr
{
    union
    {
        UCHAR   u6_ucaddr[16];
        USHORT  u6_usaddr[8];
        ULONG   u6_uladdr[4];
    } vrp_u6_addr;    /* 128-bit IP6 address */
}VRP_IN6ADDR_S;
#endif

typedef struct tagTCPIP_RT6
{
    VRP_IN6ADDR_S stIn6Addr;          /*目的地址*/
    ULONG ulPreLen;                   /*掩码长度,0~128*/
    VRP_IN6ADDR_S stGateway;          /*网关地址*/
    ULONG ulIfIndex;                  /*出接口索引*/
    ULONG ulRTPri;                    /*路由优先级,1~255*/
}TCPIP_RT6_S;

typedef struct tagTCPIP_CFG_RT_BYNH
{
    ULONG ulIfIndex;                  /*出接口索引*/
    VRP_IN6ADDR_S stGateway;          /*网关地址*/
}TCPIP_CFG_RT_BYNH_S;

typedef struct tagTCPIP_CFG_RT_EXACT
{
    VRP_IN6ADDR_S stIn6Addr;          /*目的地址*/
    ULONG ulMaskLen;                  /*掩码长度,0~128*/
    VRP_IN6ADDR_S stGateway;          /*网关地址*/
    ULONG ulIfIndex;                  /*出接口索引*/
}TCPIP_CFG_RT_EXACT_S;

typedef struct tagTCPIP_NET_RT6
{
    VRP_IN6ADDR_S stIn6Addr;             /*目的地址*/
    ULONG ulPreLen;                      /*掩码长度,1~127*/
    VRP_IN6ADDR_S stGateway;             /*网关地址*/
    ULONG ulIfIndex;                     /*出接口索引*/
}TCPIP_NET_RT6_S;



typedef struct tagSFIB_AM6_MSG
{
    ULONG ulIfnetIndex;     /*接口索引*/
    ULONG ulMsgType;        /*地址添加删除消息 0-新增,1-删除*/
    ULONG ulLogAddr[LEN_4]; /*地址*/
    ULONG ulSubMaskLen;     /*地址前缀*/
    /* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
    ULONG  ulInstanceID;
    /* End: VISP V3R2C10 VRF chandra , 2014-03-18 */    
}SFIB_AM6_MSG_S;

/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
#define FIB6_STATIC_ADDR_ADD       1
#define FIB6_STATIC_ADDR_DEL       0

#define SFIB6_VRF_MAX_VRFNAME_LENGTH    31

typedef struct tagTCPIP_RM6_CFGSTATIC_S
{
    ULONG Oper; /* 1 is Add, 0 is delete */
    VRP_IN6ADDR_S stIn6Addr;  
    ULONG ulPreLen; 
    VRP_IN6ADDR_S stGateway;   
    UCHAR szIfName[MAX_IF_NAME_LENGTH + 1];   
    ULONG ulRTPri; 
    UCHAR szVrfName[SFIB6_VRF_MAX_VRFNAME_LENGTH + 1];    
}TCPIP_RM6_CFGSTATIC_S;

typedef struct tagTCPIP_NET_RT6_WITH_VRF
{
    ULONG ulOper; /* 1- Add and 0 - Delete */
    VRP_IN6ADDR_S stIn6Addr;             /*目的地址*/
    ULONG ulPreLen;                      /*掩码长度,1~127*/
    VRP_IN6ADDR_S stGateway;             /*网关地址*/
    ULONG ulIfIndex;                     /*出接口索引*/
    UCHAR szVrfName[SFIB6_VRF_MAX_VRFNAME_LENGTH + 1];     
}TCPIP_NET_RT6_WITH_VRF_S;
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */

/*added by Abhishek Mishraa for VRF6 related APIs*/
typedef struct tagFIB6_FILTER_COND_API
{
    CHAR  szVrfName[TCPIP_RIB6_MAX_VRFNAME_LENGTH + 1]; /*VPN 名字*/
    ULONG ulRtDestAddr[4];                                     /*目的地址*/
    ULONG ulDstMask;                                   /*掩码长度,请用户填写掩码长度，比如128*/
    ULONG ulFilterType;                               /*FIB6_SEARCH_ALL--无过滤条件查询
                                                                   FIB6_SEARCH_BY_VRF6--指定VRF6查询
                                                                   FIB6_SEARCH_BY_NETIP--指定网段查询
                                                                   FIB6_SEARCH_BY_VRF6_AND_NETIP--指定VRF6+网段查询*/

}FIB6_FILTER_COND_API_S;


typedef struct tagTCPIP_RT6_ENTRY_BY_VRF
{
     ULONG  ulRt_Dest[4];
     ULONG  ulRt_Dest_PrefLen;
     ULONG  ulRt_Nexthop[4];
     ULONG  ulRt_Flags;         /* route flags -RTF_GATEWAY, RTF_HOST */
     ULONG  ulRt_IfIndex;       /* index of outgoing interface */
     ULONG  ulRt_ATIndex;       /* index of virtual link between rt_stLclAddr */
     ULONG  ulRt_Slot;          /* slot num of outgoing interface */
     ULONG  ulRt_Use;           /* metrics to consider */
     ULONG  ulRt_State;
     ULONG  ulRt_Proto;
     ULONG  ulRt_TimeStamp;
     ULONG  ulCacheEntryIndex;  /* used to access corr. cache entry */
     ULONG  ulRTPri;            /* route priority */
     ULONG  ulVrfIndex;         /* VRF Index*/
} TCPIP_RT6_ENTRY_BY_VRF_S;

/*End of addion for VRF6 related APIs  by Abhishek Mishraa */

typedef ULONG ( *IPV6_SHELL_RM_CALLBACK_FUNC_PTR)(SFIB_AM6_MSG_S *pstIn6Addr);

typedef ULONG (*TCPIP_SEARCH_VPN_FIB6_FUN)(ROUTE6_S* pstRoute6);

/*******************************************************************************
*    Func Name: TCPIP_SetSFIB6Debug
*  Description: Set debug switch
*        Input: ULONG ulDbg: 0 - OFF; Other value - ON. 
*       Output: VOID
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetSFIB6Debug(ULONG ulDbg);

/*******************************************************************************
*    Func Name: TCPIP_GetSFIB6Debug
*  Description: get sfib6 debug switch
*        Input: ULONG *pulDbg: 
*       Output: VOID
*       Return: FIB6_ERR
*               FIB6_OK
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetSFIB6Debug(ULONG *pulDbg);

/*******************************************************************************
*    Func Name: TCPIP_RequestFIB6
*  Description: Adds, Updates, Deletes or Clears the FIB table depending 
*               on the input message type
*        Input: TCPIP_RTMSG6_S * pstRtMsg: 路由消息指针
*       Output: 
*       Return: FIB6_OK,FIB6_ERR,FIB6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RequestFIB6(TCPIP_RTMSG6_S * pstRtMsg);

/*******************************************************************************
*    Func Name: TCPIP_OpenFib6Table
*  Description: register waillist object for doubly linked list of route
*        Input: ULONG *pulWaitListHandle: waitlist handle
*               USHORT usZoneID: zone id
*       Output: 
*       Return: FIB6_OK,FIB6_ERR,FIB6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_OpenFib6Table (UINTPTR *pulWaitListHandle);

/*******************************************************************************
*    Func Name: TCPIP_CloseFib6Table
*  Description: unregister waillist object for doubly linked list of route
*        Input: ULONG ulWaitlist: waitlist handle
*       Output: VOID
*       Return: FIB6_OK
*               FIB6_ERR
*               FIB6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_CloseFib6Table(UINTPTR ulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_GetFib6Entry
*  Description: Fetches bulk of FIB entries, protected  using waitlist
*        Input: 
*               ULONG ulWaitlist    : waitlist handle
*               ULONG ulRtNumWanted  : number of wanted entrys
*       Output: TCPIP_RT6_ENTRY_S *pstRtEntry : point to route entry table
                ULONG *pulRtNumReturn: number of get entrys
*               
*       Return: FIB6_ERR
*               FIB6_OK
*               FIB6_RT_END
*               FIB6_ERR_SCAN
*               FIB6_MALLOC_FAIL
*               FIB6_GET_RTENTRY_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetFib6Entry(UINTPTR ulWaitlist,ULONG ulRtNumWanted,
                                                            TCPIP_RT6_ENTRY_S *pstRtEntry,ULONG *pulRtNumReturn);

/*******************************************************************************
*    Func Name: TCPIP_GetRoute6Count
*  Description: Returns total number of routes in corresponding FIB table
*        Input: 
*       Output: ULONG *pulNum :number of routes
*       Return: FIB6_OK
*               FIB6_ERR
*               FIB6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/

extern ULONG TCPIP_GetRoute6Count (ULONG *pulNum);

/*******************************************************************************
*    Func Name: TCPIP_LookupFIB6
*  Description: Searches for the given destination address in the FIB table 
*               and fills with the route information if found
*        Input: TCPIP_ROUTE6_S* pstRoute6  : Pointer to route entry memory, containing
*                                      the destination address, and zoneid
*               BOOL_T bEnableRouteBal: A flag indicate whether to use route balancing or not
*       Output: 
*       Return: FIB6_OK,FIB6_ERR,FIB6_NOT_REGISTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-9  wanggbin(62223)        Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_LookupFIB6(TCPIP_ROUTE6_S *pstRoute4, BOOL_T bEnableRouteBal);

/*******************************************************************************
*    Func Name: TCPIP_ShowFIB6
* Date Created: 2009-08-20
*       Author: mafeng(59090)
*  Description: 显示IPv6 FIB路由表项信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-20   mafeng(59090)           Create
*
*******************************************************************************/
extern VOID TCPIP_ShowFIB6(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowRIB6
* Date Created: 2009-08-20
*       Author: mafeng(59090)
*  Description: 显示IPv6 RIB路由表项信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-20   mafeng(59090)           Create
*
*******************************************************************************/
extern VOID TCPIP_ShowRIB6(VOID);

/*******************************************************************************
*    Func Name: TCPIP_Route6Add
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: 配置IPv6静态路由.
*        Input: TCPIP_RT6_S *pstStaticRouter:静态路由配置信息
*       Output: 
*       Return: 成功返回FIB6_OK
*               失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_Route6Add(TCPIP_RT6_S *pstStaticRouter);

/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */

ULONG TCPIP_SetRoute6ByVrf(TCPIP_RM6_CFGSTATIC_S *pstStaticRoute);
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */

/*******************************************************************************
*    Func Name: TCPIP_Route6Del
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: 删除IPv6静态路由.
*        Input: TCPIP_RT6_S *pstStaticRouter:静态路由删除信息
*       Output: 
*       Return: 成功返回FIB6_OK
*               失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_Route6Del(TCPIP_RT6_S *pstStaticRouter);

/*******************************************************************************
*    Func Name: TCPIP_DisableRt6ByIfNextHop
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: 根据指定的出接口、下一跳去使能路由.
*        Input: TCPIP_CFG_RT_BYNH_S  *pstRtMsg:路由信息
*       Output: 
*       Return: 成功返回FIB6_OK
*               失败返回错误码
*      Caution: 只能在SRM方式下正常使用.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_DisableRt6ByIfNextHop (TCPIP_CFG_RT_BYNH_S  *pstRtMsg);

/*******************************************************************************
*    Func Name: TCPIP_EnableRt6ByIfNextHop
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: 根据指定的出接口、下一跳使能路由.
*        Input: TCPIP_CFG_RT_BYNH_S  *pstRtMsg:路由信息
*       Output: 
*       Return: 成功返回FIB6_OK
*               失败返回错误码
*      Caution: 只能在SRM方式下正常使用.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_EnableRt6ByIfNextHop (TCPIP_CFG_RT_BYNH_S  *pstRtMsg);

/*******************************************************************************
*    Func Name: TCPIP_ExactDisableRt6
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: 根据指定的目的地址、掩码长度、出接口、下一跳去使能路由.
*        Input: TCPIP_CFG_RT_EXACT_S  *pstRtMsg:路由信息
*       Output: 
*       Return: 成功返回FIB6_OK
*               失败返回错误码
*      Caution: 只能在SRM方式下正常使用.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_ExactDisableRt6 (TCPIP_CFG_RT_EXACT_S  *pstRtMsg);

/*******************************************************************************
*    Func Name: TCPIP_ExactEnableRt6
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: 根据指定的目的地址、掩码长度、出接口、下一跳使能路由.
*        Input: TCPIP_CFG_RT_EXACT_S  *pstRtMsg:路由信息
*       Output: 
*       Return: 成功返回FIB6_OK
*               失败返回错误码
*      Caution: 只能在SRM方式下正常使用.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_ExactEnableRt6 (TCPIP_CFG_RT_EXACT_S  *pstRtMsg);

/*******************************************************************************
*    Func Name: TCPIP_SetHost6RouteReserved
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: 设置接口DWON时,是否保留IPv6主机路由的标记.
*        Input: ULONG ulIfIndex:接口索引;
*               ULONG ulFlag:保留主机路由的标记,1:保留,0:不保留;
*       Output: 
*       Return: 成功返回FIB6_OK
*               失败返回错误码
*      Caution: 只能是ETH或Trunk对应的接口.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_SetHost6RouteReserved(ULONG ulIfIndex, ULONG ulFlag);

/*******************************************************************************
*    Func Name: TCPIP_GetHost6RouteReserved
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: 获取是否保留IPv6主机路由的标记.
*        Input: ULONG ulIfIndex:接口索引;
*               ULONG *pulFlag:主机路由保留标记;
*       Output: 
*       Return: 成功返回FIB6_OK
*               失败返回错误码
*      Caution: 只能是ETH或Trunk对应的接口.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_GetHost6RouteReserved(ULONG ulIfIndex, ULONG *pulFlag);

/*******************************************************************************
*    Func Name: TCPIP_ShowHost6RouteReserved
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: 显示是否保留IPv6主机路由的标记.
*        Input: CHAR *pIfName:接口名;
*       Output: 
*       Return: 
*      Caution: 只能是ETH或Trunk对应的接口.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
VOID TCPIP_ShowHost6RouteReserved(CHAR *pIfName);

/*******************************************************************************
*    Func Name: TCPIP_NetRoute6Add
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: 在主机模式下,配置IPv6网段路由.
*        Input: TCPIP_NET_RT6_S *pstNetRouter:网段路由信息;
*       Output: 
*       Return: 成功返回FIB6_OK
*               失败返回错误码
*      Caution: 仅在主机模式下使用,由产品自行保证.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_NetRoute6Add(TCPIP_NET_RT6_S *pstNetRouter);

/*******************************************************************************
*    Func Name: TCPIP_NetRoute6Del
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: 在主机模式下,删除IPv6网段路由.
*        Input: TCPIP_NET_RT6_S *pstNetRouter:网段路由信息;
*       Output: 
*       Return: 成功返回FIB6_OK
*               失败返回错误码
*      Caution: 仅在主机模式下使用,由产品自行保证.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create
*
*******************************************************************************/
ULONG TCPIP_NetRoute6Del(TCPIP_NET_RT6_S *pstNetRouter);


ULONG TCPIP_SetNetRoute6ByVrf(TCPIP_NET_RT6_WITH_VRF_S *pstNetRouter);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncUpdateIntfAddr6Hook
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: 注册IPv6接口地址变化通知路由管理模块的钩子.
*        Input: IPV6_SHELL_RM_CALLBACK_FUNC_PTR pfHookFunc:地址变化通知处理钩子
*       Output: 
*       Return: 成功返回FIB6_OK
*               失败返回错误码
*      Caution: 只能在光网络定制RM方式下正常使用.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create for VISPV1R8C03
*
*******************************************************************************/
ULONG TCPIP_RegFuncUpdateIntfAddr6Hook(IPV6_SHELL_RM_CALLBACK_FUNC_PTR pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_OpenRib6Table
* Date Created: 2011-08-12
*       Author: limin00188004
*  Description:  通过传入的VRF名称，获取查询句柄。
*        Input:  CHAR * pszVrfName  : 传入VRF的名称
*       Output: ULONG *pulWaitlist : 传出句柄
*       Return: RIB6_OK,RIB6_ERR_NULL_POINTER,RIB6_ERR_MALLOC_FAIL
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   limin00188004                 Create
*
*******************************************************************************/
ULONG TCPIP_OpenRib6Table(UINTPTR *pulWaitlist, CHAR *pszVrfName);

/******************************************************************************
*
*    Func Name: TCPIP_GetRib6Entry
* Date Created: 2011-08-12
*       Author: limin00188004
*  Description:  通过查询句柄，获取下一个节点。
*       Input:  ULONG ulWaitlist  : 查询句柄
*       Output:  TCPIP_RIB_RT6_ENTRY_S *pstRtEntry : 查询出来的下一个节点
*       Return: RIB6_OK,RIB6_ERR_NULL_INPUT,RIB6_ERR_NO_USE_ENTRY
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   limin00188004                 Create
*
*******************************************************************************/
ULONG TCPIP_GetRib6Entry(UINTPTR ulWaitlist, TCPIP_RIB_RT6_ENTRY_S *pstRtEntry);

/*******************************************************************************
*    Func Name: TCPIP_CloseRib6Table
* Date Created: 2011-08-12
*       Author: limin00188004
*  Description:  关闭 查询句柄。
*        Input:  ULONG ulWaitlist: 查询句柄
*       Output: 
*       Return: RIB6_OK,RIB6_ERR_HANDLE
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   limin00188004                 Create
*
*******************************************************************************/
ULONG TCPIP_CloseRib6Table(UINTPTR ulWaitlist);

/*******************************************************************************
*    Func Name: TCPIP_ShowRib6ByVrfName
* Date Created: 2011-08-12
*       Author: limin00188004
*  Description: 显示IPv6 RIB路由表项信息。
*        Input: CHAR *pszVrfName: VRF的名称
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-08-12   limin00188004                 Create
*
*******************************************************************************/
VOID TCPIP_ShowRib6ByVrfName(CHAR *pszVrfName);


ULONG TCPIP_OpenFib6TableByFilter(UINTPTR *pulHandle, FIB6_FILTER_COND_API_S *pstFilter);

/*******************************************************************************
*    Func Name: TCPIP_GetNextFib6Entry
* Date Created: 2013-10-10
*       Author: a00900872
*  Description:According to user-specified criteria, to return to the user a routing table entry
*        Input: ULONG ulHandle: Handle
*       Output: TCPIP_RT4_ENTRY_BY_VRF_S *pstRtEntry:Return routing table entry
*       Return: VOS_OK,Error Code；FIB4_GET_END, routing table entry end of the query; other error codes
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-10-10  a00900872       Create
*
*******************************************************************************/
ULONG TCPIP_GetNextFib6Entry(UINTPTR ulHandle, TCPIP_RT6_ENTRY_BY_VRF_S* pstRtEntry);


ULONG TCPIP_CloseFib6TableByFilter(UINTPTR ulHandle);

/*******************************************************************************
*    Func Name: TCPIP_ShowFIB6ByVrf
*  Description: 显示指定VRF6的FIB表项
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-10-25  wangjiaqi        Create the first version.
*
*******************************************************************************/
VOID TCPIP_ShowFIB6ByVrf(CHAR *pszVrfName);
/*******************************************************************************
*    Func Name: TCPIP_Reg_VpnFib6
* Date Created: 2013-12-05
*       Author: likaikun213099
*  Description: 注册产品查询FIB6接口
*        Input: TCPIP_SEARCH_VPN_FIB6_FUN pfSearchFib6:钩子函数
*       Output: 
*       Return: 成功：VOS_OK
*               失败：VOS_ERR
*      Caution: 需要在协议栈初始化之前注册
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-05   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_Reg_VpnFib6(TCPIP_SEARCH_VPN_FIB6_FUN pfSearchFib6);

#ifdef __cplusplus
}
#endif      /* end of _cplusplus        */

#endif      /* end of _SFIB6_API_H_    */


