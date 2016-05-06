/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ip_pub.h
*
* Project Code: VISPV100R005
*  Module Name: IP4
* Date Created: 2000-01-25
*       Author: Lirui
*  Description: IP模块对外提供的宏定义、结构、函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2000-01-25   Lirui                   Create
*  2006-05-11   luyao                   为支持ARM CPU字节对齐特性，修改结构
*  2006-11-07   zhoutong(43740)         规范性整改
*
*******************************************************************************/

/****************************************************************************/
/*                          Start of Standard header                        */
/****************************************************************************/

#ifdef    __cplusplus
extern "C"{
#endif

#ifndef _TCPIP_OLD_IP_PUB_H_
#define _TCPIP_OLD_IP_PUB_H_

/****************************************************************************/
/*                           End of Standard header                         */
/****************************************************************************/


/****************************************************************************/
/*                              Include Files                               */
/****************************************************************************/
#define RT_VRF_NAMELEN               31
/* VPN和策略模块定义 */
typedef struct tagVrfRd
{
    UCHAR   ec_style;
    UCHAR   ec_type;
    USHORT  s_value;
    ULONG   l_value;
}  VRFRD;

/* VPN最大实例数 */
extern ULONG    g_ulFibMaxVpnInstanceNum;

/****************************************************************************/
/*                              Macro Defination                            */
/****************************************************************************/
#define V_LIST_FIRST(ptr)    ((ptr)->ia_v_pNext)
#define V_LIST_NEXT(ptr)    ((ptr)->ia_v_pNext)


#define TYPE_OPER        0

#define MAX_NUMBER_INSTANCE RT_VRF_INDEX_MAX

#define RT_VRF_DELETE       2
#define RT_VRFINTF_CHANGE   4

#define FIB_LSPM_CREATESCAN 0x01
#define FIB_LSPM_CHANGESCAN 0x02
#define FIB_LSPM_DELSCAN    0x03


#define FIB_GET_ROUTE       200
#define MAX_NODES_DELETED   500

#ifndef BIT_TEST
#define BIT_TEST(f, b)  ((f) & (b))
#endif
#ifndef BIT_SET
#define BIT_SET(f, b)   ((f) |= (b))
#endif
#ifndef BIT_RESET
#define BIT_RESET(f, b) ((f) &= ~(b))
#endif


/* 路由及FTN消息类型 */
#define LSPM_FTN_MSG    1
#define LSPM_RT_MSG     0

/* FTN 消息类型 */
#define FTNMSG_ADD      1
#define FTNMSG_DEL      2

#define LSPM_LSPSTATUS_READY                4
#define LSPM_LSPSTATUS_SPECIAL4BGP_READY    6

/* 策略模块定义 */
#define LSPM_GETLSP_TYPE(x)                 ( ((x)>>19) & 0x7 )
#define LSPM_GETLSP_STATUS(x)               ( ((x)>>16) & 0x7 )
#define LSPM_GETLSP_SIGNALNO(x)             ( (x) & 0xF )
#define LSPM_GETLSP_ROUTEPROTOTYPE(x)       ( ((x)>>22) & 0x7 )
#define LSPM_SETLSP_TYPE(x, y)              ( x = ( ( x & 0xffc7ffff ) | ((y)<<19) ) )
#define LSPM_SETLSP_STATUS(x, y)            ( x = ( ( x & 0xfff8ffff ) | ((y)<<16) ) )
#define LSPM_SETLSP_SIGNALNO(x, y)          ( x = ( ( x & 0xffffff00 ) | y ) )
#define LSPM_SETLSP_ROUTEPROTOTYPE(x, y)    ( x = ( ( x & 0xfe3fffff ) | ((y)<<22) ) )

/* error code */
#define RT_ALLOCATE_MEM_ERR     15
#define RT_INVALID_MSG          8
#define RT_FIBITEM_NOT_EXIST    30
#define RT_LSP_NOT_EXIST        29


#define RT_VRF_POOL_SIZE        4096

#define RT_VRF_INDEX_PUBLIC     0
#define RT_VRF_INDEX_MIN        1
#define RT_VRF_INDEX_MAX        (g_ulFibMaxVpnInstanceNum-1)

#define RT_IsRDValid(x) \
    ( ( ( RT_VRF_INDEX_MIN <= (x)) && ( RT_VRF_INDEX_MAX >= (x))) ? 1 : 0 )

#define RT_NO_USE(var)          ((VOID)(var))


/* Start of 以太网的公共函数返回值 */
#define IP_ARP_IPIFNET_ERR          1
#define IP_ARP_ONESEFIP             14
#define IP_ARP_DSTIP_NOTSAMENET     15
#define IP_ARP_SRCIP_BROADCAST      16
#define IP_ARP_INVALIDADDR          17
#define IP_ARP_DSTIPISNET           18
#define IP_ARP_SRCIP_NOTSAMENET     19
#define IP_ARP_DSTADD_NOTMY         20
#define IP_ERR_SHUTDOWN_FIRST       21

/*add by zhangtongjie 2005  6/1*/
typedef struct tagPHY_CHECK_PARA
{
    ULONG   ulIfIndex; /*当前接口*/
    USHORT  usVPI ;        
    USHORT  usVCI ;    
    USHORT  usLowVid;
    USHORT  usHighVid;
    CHAR    szLocalCeMac[6];
    UCHAR   ucPadding_1[2];
    ULONG   ulIpAddr;
    USHORT  usPeerCeFlag;
    UCHAR   ucPadding_2[2];
    ULONG   uloperation;
}PHY_CHECK_PARA_S ;

enum enumoperation
{
    PHY_CHECK_PARA_CREATE,
    PHY_CHECK_PARA_DELETE,
    PHY_CHECK_PARA_MODIFY,
    PHY_CHECK_PARA_END
};
 /*add over zhangtongjie */


/**********************************************************************
* from ip_addr.h
**********************************************************************/
/*
 * Internet address (a structure for historical reasons) .mayun.
 */

#define RTMSG_ADD       1

#define RTF_UP          0x1         /* 可用路由 route usable */
#define RTF_GATEWAY     0x2         /* 目的地址是一个路由器 destination is a gateway */
#define RTF_HOST        0x4         /* 进入主机澹(否则进入网络) host entry (net otherwise) */
#define RTF_REJECT      0x8         /* 主机或网络不可达 host or net unreachable */
#define RTF_DYNAMIC     0x10        /* 动态创建澹(通过重定向) created dynamically (by redirect) */
#define RTF_MODIFIED    0x20        /* 动态修改(通过重定向) modified dynamically (by redirect) */
#define RTF_DONE        0x40        /* 确认信息 message confirmed */
#define RTF_MASK        0x80        /* 子网掩码 subnet mask present */
#define RTF_CLONING     0x100       /* 生成新路由 generate new routes on use */
#define RTF_XRESOLVE    0x200       /* 外部程序解决 external daemon resolves name */
#define RTF_LLINFO      0x400       /* 由ARP或ESIS生成 generated by ARP or ESIS */
#define RTF_STATIC      0x800       /* 手动增加 manually added */
#define RTF_BLACKHOLE   0x1000      /* 丢弃报文 just discard pkts (during updates) */
#define RTF_REF         0x2000
#define RTF_PROTO2      0x4000      /* 特殊路由协议标志 protocol specific routing flag */
#define RTF_REJECT2     0x8000      /* 特殊路由协议标志 protocol specific routing flag */

/* addded by vijay on 29/12/2004 to define NOLSPM flag, to fix defect 7478 */
/* Moved by vijay on 12/2/2004 */
/* added by dengqiulin for system graceful */
#define RTF_STALE       0x40000
/* end of addition*/

/* addded by vijay on 12/2/2004 to define NOLSPM flag */
#define RTF_NOLSPM      0x80000     /* for no lspm  flag */
/* End of Modification */

/*
 * copy from 8011v100r001 2003/06/03
 */


/**********************************************************************
* from route.h
**********************************************************************/
#define RTV_MTU         0x1     /* init or lock _mtu */
#define RTV_HOPCOUNT    0x2     /* init or lock _hopcount */
#define RTV_EXPIRE      0x4     /* init or lock _hopcount */
#define RTV_RPIPE       0x8     /* init or lock _recvpipe */
#define RTV_SPIPE       0x10    /* init or lock _sendpipe */
#define RTV_SSTHRESH    0x20    /* init or lock _ssthresh */
#define RTV_RTT         0x40    /* init or lock _rtt */
#define RTV_RTTVAR      0x80    /* init or lock _rttvar */


typedef struct tagROUTE
{
    struct  tagRTENTRY  *ro_pRt;
    struct  tagSOCKADDR ro_stDst;
}ROUTE_S;

typedef struct tagRT_NEXTHOP
{    
    ULONG ulNextHopAddr;    /* the address of next hop */
    ULONG ulOutIfIndex;     /* the index of out interface */
    
}RT_NEXTHOP_S;

/*
* These numbers are used by reliable protocols for determining
* retransmission behavior and are included in the routing structure.
*/
typedef struct tagRTMETRICS
{
    ULONG rmx_ulLocks;      /* Kernel must leave these values alone */
    ULONG rmx_ulMTU;        /* MTU for this path */
    ULONG rmx_ulHopCount;   /* max hops expected */
    ULONG rmx_ulExpire;     /* lifetime for route, e.g. redirect */
    ULONG rmx_ulRecvPipe;   /* inbound delay-bandwith product */
    ULONG rmx_ulSendPipe;   /* outbound delay-bandwith product */
    ULONG rmx_ulSsthresh;   /* outbound gateway buffer limit */
    ULONG rmx_ulRtt;        /* estimated round trip time */
    ULONG rmx_ulRttvar;     /* estimated rtt variance */
    ULONG rmx_ulPkSent;     /* packets sent using this route */
}RTMETRICS_S;


/*
* rmx_rtt and rmx_rttvar are stored as microseconds;
* RTTTOPRHZ(rtt) converts to a value suitable for use
* by a protocol slowtimo counter.
*/
/*TCP use*/
#define    RTM_RTTUNIT    1000000    /* units for rtt, rttvar, as units per sec */
#define    RTTTOPRHZ(r)    ((r) / (RTM_RTTUNIT / PR_SLOWHZ))

/*
* We distinguish between routes to hosts and routes to networks,
* preferring the former if available.  For each route we infer
* the interface to use from the gateway address supplied when
* the route was entered.  Routes that forward packets through
* gateways are marked so that the output routines know to address the
* gateway rather than the ultimate destination.
*/
typedef struct tagRTENTRY
{
    INADDR_S rt_stDst;      /* Destination address */
    INADDR_S rt_stDstMask;  /* Destination mask */
    INADDR_S rt_stGateway;  /* Next hop */

    #define RT_KEY(r)       ((r)->rt_stDst)
    #define RT_MASK(r)      ((r)->rt_stDstMask)
    #define RT_GATEWAY(r)   ((r)->rt_stGateway)

    INADDR_S rt_stLclAddr;  /* local address */
    INADDR_S rt_stLclMask;  /* local address mask */

    ULONG    rt_ulFlags;    /* route flags,RTF_GATEWAY, RTF_HOST, RTF_INTERFACE, RTF_STATE*/

    ULONG    rt_ulIfIndex;  /* index of outgoing interface */
    ULONG    rt_ulATIndex;  /* index of virtual link between rt_stLclAddr/rt_stLclMask and gateway */
    ULONG    rt_ulSlot;     /* slot num of outgoing interface */
    ULONG    rt_ulUse;
    ULONG    rt_ulTimeStamp;


    /*x36530 Syn VRPV5R1B12D030 20050314*/
    /* added by kelvin dengqiulin to support two rm entry mapping to one fib entry 04.11.23*/
    SHORT    rt_sEntryCount;


    /* added by kelvin dengqiulin to support two rm entry mapping to one fib entry 04.11.23*/
    USHORT   rt_usEntryCount;
    

    /* Robin, 2003/09/20, for VRP_VERSION_5, V3 used wrong macro */
    USHORT   usIsLspForwardFlag;
    UCHAR    ucPadding[2];
    ULONG    ulLspToken;
    ULONG    ulInLabel;     /* vpn-lsp的内层标签 add by james for D19207 03/01/15 */
/*x36530 同步25代码20041130*/
    USHORT   rt_usOriginAs;
    USHORT   rt_usPeerAs;
    ULONG    rt_ulBGPNexthop;
    /* end of addition 09.11*/



    ULONG  rt_ulLogicIfIndex;       /* 存放rt_ulIfIndex对应的逻辑接口，当rt_ulIfIndex为二层接口时，
                                       rt_ulLogicIfIndex与rt_ulIfIndex的值不同 */

    struct tagRTENTRY *rt_pNext;    /*To Form Double Link*/
    struct tagRTENTRY *rt_pPrev;    /*To Form Double Link*/
}RTENTRY_S;


#define RT_FIELD_DST_ADDR(pRt)  ((pRt)->rt_stDst.s_ulAddr)
#define RT_FIELD_FLAGS(pRt)     ((pRt)->rt_ulFlags)
#define RT_FIELD_GATEWAY(pRt)   ((pRt)->rt_stGateway.s_ulAddr)
#define RT_FIELD_IF(pRt)        ((pRt)->rt_ulIfIndex)
/* MVLAN 09/02/2004 */
#define RT_FIELD_IF_LOGIC(pRt)  ((pRt)->rt_ulLogicIfIndex)
/* END MVLAN */ 

#define RT_FIELD_SLOT(pRt)      ((pRt)->rt_ulSlot)
#define RT_FIELD_AT(pRt)        ((pRt)->rt_ulATIndex)
#define RT_FIELD_IFA_ADDR(pRt)  ((pRt)->rt_stLclAddr.s_ulAddr)
#define RT_FIELD_IFA_MASK(pRt)  ((pRt)->rt_stLclMask.s_ulAddr)
#define RT_INVALID_LABEL        0xFFFFFFFF

/* 如果是网关路由,返回非0 */
#define RT_IS_GATEWAY( pRt )    (((pRt)->rt_ulFlags) & RTF_GATEWAY) 


/**********************************************************************
* from ip_icmp.h
**********************************************************************/



/**********************************************************************
* from ip_input.h
**********************************************************************/

/*
 * Options for use with [gs]etsockopt at the IP level.
 * First word of comment is data type; bool is stored in int.
 */
#ifndef IP_OPTIONS
#define IP_OPTIONS           1   /* buf/ip_opts; set/get IP options */
#endif
#define IP_HDRINCL           2   /* int; header is included with data */
#define IP_TOS               3   /* int; IP type of service and preced. */
#define IP_TTL               4   /* int; IP time to live */
#define IP_RECVOPTS          5   /* bool; receive all IP opts w/dgram */
#define IP_RECVRETOPTS       6   /* bool; receive IP opts for response */
#define IP_RECVDSTADDR       7   /* bool; receive IP dst addr w/dgram */
#define IP_RETOPTS           8   /* ip_opts; set/get IP options */

#define IP_DEBUG_FIB         3   
#define FIB_DEBUG_AGE        4
#define FIB_DEBUG_ROUTE      5

/*added by huzhiyong 2002/07/03定义show fib的命令类型*/
#define Show_Fib_AclList                11
#define Show_Fib_PreFix                 12
#define Show_Fib_StringSearch           13
#define Show_Fib_IpAddr1                14
#define Show_Fib_IpAddr1Mask1           15
#define Show_Fib_IpAddr1LongMatch       16
#define Show_Fib_IpAddr1Mask1Addr2Mask2 17
#define Show_Fib_Summary                18
#define Show_Fib                        19
/*endofadd*/
#define Prefix_SynData                  20
/*add by evan */
#define Show_MplsIlm                    21
#define Show_MplsNhlfe                  22

#define Del_Prefix      1
#define Add_Prefix      2

#ifndef MAXLIST_NAME 
#define MAXLIST_NAME    30
#endif

typedef struct tagPREFIXSYNDATA
{
    ULONG ulMsgType;
    ULONG ulCmd;
    ULONG seq_num;
    ULONG ulMode;
    ULONG ulNetwork;
    ULONG ulMaskLen;
    ULONG ulGeNum;
    ULONG ulLeNum;
    ULONG ulIsSeqDef;
    CHAR list_name[MAXLIST_NAME];
    UCHAR ucPadding[4-((MAXLIST_NAME)%4)];
}PREFIXSYNDATA_S;



#define FIB_STATE_NO                        0
#define FIB_STATE_DOWNLOADTIMEOUT           1
#define FIB_STATE_REFRESHTIMEOUT            2
#define FIB_STATE_AGETIMEOUT                3
#define FIB_STATE_BEGINTOREFRESHWALKING     4
#define FIB_STATE_MIDDLEREFRESHWALKING      5
#define FIB_STATE_ENDREFRESHWALKING         6
#define FIB_STATE_BEGINTOAGEWALKING         7
#define FIB_STATE_MIDDLEAGEWALKING          8
#define FIB_STATE_ENDAGEWALKING             9
#define FIB_STATE_REFRESHFINISH             10
#define FIB_STATE_AGEFINISH                 11
#define FIB_STATE_RouteNotFound             12    


/*****************************************************************
* ip_mrout.h
*****************************************************************/
/*
 * Multicast Routing set/getsockopt commands.
 */
#define MRT_INIT        100    /* initialize forwarder */
#define MRT_DONE        101    /* shut down forwarder */
#define MRT_ADD_VIF     102    /* create virtual interface */
#define MRT_DEL_VIF     103    /* delete virtual interface */
#define MRT_ADD_MFC     104    /* insert forwarding cache entry */
#define MRT_DEL_MFC     105    /* delete forwarding cache entry */
#define MRT_VERSION     106
#define MRT_ASSERT      107

#define MIN_INDEX_ENCAPIF   0x8000



/****************************************************************************/
/*                              Static Variable                             */
/****************************************************************************/


/****************************************************************************/
/*                              External Variable                           */
/****************************************************************************/


/****************************************************************************/
/*                              Declaration Of Structure                    */
/****************************************************************************/

typedef struct tagRTMSG
{
    ULONG   ulVrfIndex;
    USHORT  rtmsg_usType;        /* msg type, RTMSG_DEL: delete operation; RTMSG_ADD: add opration; RTMSG_REFRESH: refresh opration; */
    UCHAR   ucPadding_1[2];
    union
    {
        UCHAR   rtmsg_szVrfName_ex[RT_VRF_NAMELEN + 1];
        struct tagRtInfo
        {
            USHORT      rtmsg_usIsLspForwardFlag_ex;
            UCHAR       ucPadding_2[2];
            ULONG       rtmsg_ulInLabel_ex; 
            ULONG       rtmsg_ulToken_ex;
            INADDR_S    rtmsg_stDst_ex;        /* route destination */
            INADDR_S    rtmsg_stDstMask_ex;    /* route destination mask */
            INADDR_S    rtmsg_stGateway_ex;    /* next hop */
            INADDR_S    rtmsg_stLclAddr_ex;    /* local address */
            INADDR_S    rtmsg_stLclMask_ex;    /* local address mask */
            ULONG       rtmsg_ulFlags_ex;      /* route flags,RTF_GATEWAY, RTF_HOST, RTF_INTERFACE, RTF_STATE*/
            ULONG       rtmsg_ulIfIndex_ex;    /* index of outgoing interface */
            ULONG       rtmsg_ulATIndex_ex;    /* index of virtual link between rtmsg_stLclAddr/rtmsg_stLclMask and gateway */
            ULONG       rtmsg_ulSlot_ex;

            /*Added by vijay on 02/04/2004 to fix the defect BYAD07036*/
            
            ULONG       rtmsg_ulOldInLabel_ex;  /* old inner label */
            ULONG       rtmsg_ulOldToken_ex;    /* old token */
            INADDR_S    rtmsg_stOldGateway_ex;  /* old next hop */
            ULONG       rtmsg_ulOldIfIndex_ex;  /* old index of outgoing interface */
            ULONG       rtmsg_ulOldATIndex_ex;  /* old index of virtual link between rtmsg_stLclAddr/rtmsg_stLclMask and gateway */
            /*End of Modification BYAD07036*/
            /* #ifdef (RM_NETSTREAM) */
/*x36530 同步25代码20041130*/
            USHORT      rtmsg_usFirstAs_ex;
            USHORT      rtmsg_usLastAs_ex;
            ULONG       rtmsg_ulOriginNexthop_ex;
            /*end of addition 09.11*/
                    /* #endif */

            /* wuxiaoqian */
            SHORT      rtmsg_sRefCount_ex;            
            /* wuxiaoqian */
            UCHAR      ucPadding_3[2];
        }RtInfo_S;
    }Msg_un;
    #define rtmsg_szVrfName         Msg_un.rtmsg_szVrfName_ex
    #define rtmsg_usIsLspForwardFlag Msg_un.RtInfo_S.rtmsg_usIsLspForwardFlag_ex
    #define rtmsg_ulInLabel         Msg_un.RtInfo_S.rtmsg_ulInLabel_ex
    #define rtmsg_ulToken           Msg_un.RtInfo_S.rtmsg_ulToken_ex
    #define rtmsg_stDst             Msg_un.RtInfo_S.rtmsg_stDst_ex    
    #define rtmsg_stDstMask         Msg_un.RtInfo_S.rtmsg_stDstMask_ex    
    #define rtmsg_stGateway         Msg_un.RtInfo_S.rtmsg_stGateway_ex    
    #define rtmsg_stLclAddr         Msg_un.RtInfo_S.rtmsg_stLclAddr_ex    
    #define rtmsg_stLclMask         Msg_un.RtInfo_S.rtmsg_stLclMask_ex    
    #define rtmsg_ulFlags           Msg_un.RtInfo_S.rtmsg_ulFlags_ex    
    #define rtmsg_ulIfIndex         Msg_un.RtInfo_S.rtmsg_ulIfIndex_ex        
    #define rtmsg_ulATIndex         Msg_un.RtInfo_S.rtmsg_ulATIndex_ex        
    #define rtmsg_ulSlot            Msg_un.RtInfo_S.rtmsg_ulSlot_ex     
    #define rtMsg_bNAT              Msg_un.RtInfo_S.bNAT_ext

    /*Added by vijay on 02/04/2004 to fix the defect BYAD07036*/
    #define rtmsg_ulOldInLabel      Msg_un.RtInfo_S.rtmsg_ulOldInLabel_ex
    #define rtmsg_ulOldToken        Msg_un.RtInfo_S.rtmsg_ulOldToken_ex
    #define rtmsg_stOldGateway      Msg_un.RtInfo_S.rtmsg_stOldGateway_ex
    #define rtmsg_ulOldIfIndex      Msg_un.RtInfo_S.rtmsg_ulOldIfIndex_ex
    #define rtmsg_ulOldATIndex      Msg_un.RtInfo_S.rtmsg_ulOldATIndex_ex
    /* #ifdef (RM_NETSTREAM) *//*x36530 同步25代码20041130*/
    #define rtmsg_usFirstAs         Msg_un.RtInfo_S.rtmsg_usFirstAs_ex
    #define rtmsg_usLastAs          Msg_un.RtInfo_S.rtmsg_usLastAs_ex
    #define rtmsg_ulOriginNexthop   Msg_un.RtInfo_S.rtmsg_ulOriginNexthop_ex
    /* end of addition 09.11 */
    /* #endif */

    /*End of Modification BYAD07036*/

    /* wuxiaoqian */
    #define rtmsg_sRefCount         Msg_un.RtInfo_S.rtmsg_sRefCount_ex
    /* wuxiaoqian */  


/*=======Guo yuedong2004==========begin======================================*/

}RTMSG_S;


typedef struct tagRmRouteEntry
{
    ULONG ulNextHop;
    ULONG ulIfIndex;
}RM_ROUTE_ENTRY_S;

/*注意: 此宏必须大于等于RT_N_MULTIPATH*/
#define RT_ENTRY_MAX  3

typedef struct tagRmRoute
{
    RM_ROUTE_ENTRY_S aRTEntry[RT_ENTRY_MAX];
    USHORT           ar_usRtCount;
    UCHAR            ucPadding[2];
}RM_ROUTE_S;


 
/****************************************************************************/
/*                              Declaration Of Function                     */
/****************************************************************************/
/* this function is in rtsyn.c. not really a VOS interface. */
extern ULONG VOS_time(ULONG *pulTimeRet);

/****************************************************************************/
/*                           Start of Standard Tail                         */
/****************************************************************************/

#endif  /*  _TCPIP_OLD_IP_PUB_H_   */

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

/****************************************************************************/
/*                           End of Standard Tail                           */
/****************************************************************************/

