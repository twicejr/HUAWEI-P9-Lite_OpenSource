/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_pub.h
*
* Project Code: VISPV100R005
*  Module Name: AM4  
* Date Created: 2006-01-04
*       Author: Li LiXiang
*  Description: AM4模块对外提供的宏定义、结构、函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                根据编程规范，对文件进行规范化整理
*  2006-05-11   luyao(60000758)         为支持ARM CPU字节对齐特性，修改结构。
*  2006-11-07   zhoutong(43740)         规范性整改
*  2007-12-06   wangmingxia(60786)      Modify by A82D21748 删除无用的函数声明
*
*******************************************************************************/
 
#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _AM4_PUB_H_
#define _AM4_PUB_H_

#include "tcpip/public/tcpip_config.h"
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/ip4/am4/include/am4_api.h"
#include "tcpip/ip4/pp4/include/pp4_api.h"
#include "tcpip/igmp4/include/igmpv3_api.h"
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#include "tcpip/ip4/am4/core/include/am4_l3vpn.h"
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 */


#define VRP_IN_CLASSA(i)        (0 == ((long)(i) & 0x80000000L))
#define VRP_IN_CLASSA_NET       0xff000000L
#define IN_CLASSA_NSHIFT    24
#define VRP_IN_CLASSA_HOST      0x00ffffffL
#define VRP_IN_CLASSA_MAX       128L

#define VRP_IN_CLASSB(i)        (0x80000000L == ((long)(i) & 0xc0000000L))
#define VRP_IN_CLASSB_NET       0xffff0000L
#define IN_CLASSB_NSHIFT    16
#define VRP_IN_CLASSB_HOST      0x0000ffffL
#define VRP_IN_CLASSB_MAX       65536L

#define VRP_IN_CLASSC(i)        (0xc0000000L == ((long)(i) & 0xe0000000L))
#define VRP_IN_CLASSC_NET       0xffffff00L
#define IN_CLASSC_NSHIFT    8
#define VRP_IN_CLASSC_HOST      0x000000ffL

#define VRP_IN_CLASSD(i)        (0xe0000000L == ((long)(i) & 0xf0000000L))
#define VRP_IN_CLASSD_NET       0xf0000000L /* These ones aren't really */
#define IN_CLASSD_NSHIFT    28          /* net and host fields, but */
#define VRP_IN_CLASSD_HOST      0x0fffffffL /* routing needn't know.    */
#define IN_MULTICAST(i)     VRP_IN_CLASSD(i)

#define IN_EXPERIMENTAL(i)  (0xf0000000L == ((long)(i) & 0xf0000000L))
#define IN_BADCLASS(i)      (0xf0000000L == ((long)(i) & 0xf0000000L))

/* add by multicast policy routing project */
#define IN_MULTICAST_PROTO(i)   (0xe0000000L == ((long)(i) & 0xffffff00L))

#ifndef INADDR_ANY
#define INADDR_ANY          (ULONG)0x00000000L
#endif
#ifndef INADDR_BROADCAST
#define INADDR_BROADCAST    (ULONG)0xffffffffL  /* must be masked */
#endif

#ifndef INADDR_NONE
#define INADDR_NONE         0xffffffffUL        /* -1 return */
#endif


#define INADDR_UNSPEC_GROUP     (ULONG)0xe0000000L  /* 224.0.0.0 */
#define INADDR_ALLHOSTS_GROUP   (ULONG)0xe0000001L  /* 224.0.0.1 */
#define INADDR_MAX_LOCAL_GROUP  (ULONG)0xe00000ffL  /* 224.0.0.255 */

#define IN_LOOPBACKNET      127         /* official! */

/* syn D038 by x36530 20050715*/
/*ULONG      ipif_ulControlFlag;*/      /* 控制标志，可以供各种对IP的控制命令使用 */

#define IP_CTRLFLAG_IPBIND           0x00000001  /* 接口正在执行ip binding或undo ip binding的标志 */

#define ICMP_MAXTYPE         19         /* added by 8011 maye BYDD06214 */

#define AM4_ON  1
#define AM4_OFF 0

/* Socket address, internet style */
typedef struct tagSOCKADDRIN
{
    UCHAR   sin_chLen;
    UCHAR   sin_chFamily;
    USHORT  sin_usPort;
    struct  tagINADDR sin_stAddr;
    char    sin_chZero_a[8];
}SOCKADDRIN_S;

/*Added by pengjimei for 8070 IP特性移植项目*/
#define IP_RPC_FUNC_ID_HOT_IFNET_INSERT 1
/*End*/


struct tagIPIFNET;
struct _IP_radix_node;
typedef struct tagIPIFADDR
{
    struct tagIPIFNET   *ia_pIpIf;
    
    struct tagINADDR    ia_stAddr;  

    /* net info */
    struct tagINADDR    ia_stNet;
    struct tagINADDR    ia_stNetMask;
    struct tagINADDR    ia_stNetBroadcast;
    /* subnet info */
    struct tagINADDR    ia_stSubnet;
    struct tagINADDR    ia_stSubnetMask;
    struct tagINADDR    ia_stSubnetBroadcast;
    /* dst info */
    struct tagINADDR    ia_stDstAddr;
    /* form double linklist of ipifnet I belong */
    struct tagIPIFADDR  *ia_v_pPrev;    
    struct tagIPIFADDR  *ia_v_pNext;   
    /* form double linklist of all ipifnet addresses */
    struct tagIPIFADDR  *ia_h_pPrev;
    struct tagIPIFADDR  *ia_h_pNext;

    struct _IP_radix_node  *ia_r_pNode; /* 回指内部节点 */
    /*f47854 add begin:地址描述信息*/
    CHAR ia_description[48];
    /*f47854 add end:地址描述信息*/

    /*Added by likaikun213099, 地址冲突标志, 2014/10/23 */
    ULONG   ia_ulConflictFlag;
} IPIFADDR_S, *PIPIFADDR_S;

typedef struct tagIPMULTI_SOURCELIST
{
    ULONG   ulSourceAddr;
    ULONG   ulReference;    /*references by sockets*/
    ULONG   ulReportTag;    /*tag which source to be reported*/
    struct  tagIPMULTI_SOURCELIST *pstNextSourceAddr;
}IPMULTI_SOURCELIST_S;
/*
 * Internet multicast address structure.  There is one of these for each IP
 * multicast group to which this host belongs on a given network interface.
 * They are kept in a linked list, rooted in the interface's in_ifaddr
 * structure.
 */
typedef struct tagIPMULTI
{
    ULONG   ipm_ulIndexIf;
    struct  tagINADDR   ipm_stAddr;     /* IP multicast address */
    USHORT  ipm_usRefCnt;               /* no. membership claims by sockets */ 
    UCHAR   ucPadding[2]; 
    ULONG   ulSrcNumsOfResultList;      /* the source numbers on the result list*/
    ULONG   ulExcludeSock;              /* the number of sockets in exclude mode*/
    ULONG   ulReTrans;                  /* the retransported times*/
    UCHAR   ucLastMemberFlag;           /* only used for IGMPv2*/
    UCHAR   ucFilterMode;               /* group filter mode*/
    UCHAR   ucGroupStateChangeFlag;     /* group state change flag*/
    UCHAR   ucSourceListChangeFlag;     /* source list change flag*/
    ULONG   ulTimer_StateChange;        /* send state change report when this timer expired*/
    ULONG   ulTimer_GroupSpecific;      /* response to the group specefic query when this timer expired*/
    ULONG   ulTimer_GrpSrcSpecific;     /* response to the group and source specific query when this timer expired*/
    struct tagIPMULTI_SOURCELIST *pstResultList;        /*source list to be reported*/
    struct tagIPMULTI_SOURCELIST *pstExcludeList;       /*Exclude list*/
    struct tagIPMULTI_SOURCELIST *pstIncludeList;       /*Include list*/
    struct tagIPMULTI_SOURCELIST *pstRecordList;        /*source list from received Group Specefic Query*/    
    struct  tagIPMULTI  *ipm_pNext;     /* ptr to next multicast address */
}IPMULTI_S, *PIPMULTI_S;

typedef struct tagIPMULTI_LIST
{
    /*ULONG   ulVersion;*/              /* the IGMP version run on the interface*/
    ULONG   ulTimer_GeneralQuery;       /* only for responsing the IGMPv3 General Query*/
    ULONG   ulTimer_Version_IGMPv1;
    ULONG   ulTimer_Version_IGMPv2;
    ULONG   ulGroupCount;
    ULONG   ulQryRobVar;
    struct tagIGMPSTAT stIGMPState;    /* IGMP statistic*/
    struct tagIPMULTI * pstMultiAddr;
}IPMULTI_LIST_S;

/* IP ifnet */
typedef struct tagIPIFNET
{
    ULONG   ipif_ulIndexIf;     /* 接口索引 */
    ULONG   ipif_ulFlags;       /* 接口标志位：广播属性、NBMA属性IFF_BROADCAST、IFF_NBMA*/

    ULONG   ipif_ulNegSlot;     /* 用于协商时记录槽号  */ 
    ULONG   ipif_ulAddrFlag;    /* 接口地址的特性：地址协商、借用地址、有自己的地址 
                                   IFF_NEGOTIATE,*/
    ULONG   ipif_ulBorrowIfIndex; /* 借用地址接口索引 */

    CHAR     ipif_szIfName[IF_MAX_INTERFACE_NAME_LEN+1];   /* 接口名 */
    IPIFSTAT_S  ipif_stData;    /* 接口的统计信息 */
    
    IPIFADDR_S  ipif_stIpIfAddrList;    /* 接口的单播地址链：双向链表 */
    IPMULTI_LIST_S   *ipif_pMultiAddrList;   /* 接口的多播地址链 */

    ULONG ipif_ulMBoundary;     /*表示组播边界的配置由哪个ACL进行匹配*/
    ULONG ipif_ulMTTL;          /*表示TTL必须具有更大的TTL值才允许顺利通过此接口*/
    

    ULONG      ipif_ulIcmpInPktNum;         /* 接口收到的ICMP报文数目 */
    ULONG      ipif_ulICMP_UNKNOW ;         /* 接口收到的ICMP类型非法的报文数目 */
    ULONG      ipif_ulIcmpInType_A[ICMP_MAXTYPE + 1]; /* 接口收到的各个类型ICMP报文的数目 */
    ULONG      ipif_ulTtlInvalidInPktNum;   /* 接口收到的TTL非法的报文的数目(路由协议报文除外)*/
    ULONG      ipif_ulArpReqInPktNum;       /* 接口收到的ARP请求报文数目 */
    ULONG      ipif_ulArpReplyInPktNum;     /* 接口收到的ARP应答报文数目 */
    ULONG      ipif_ulArpUnknowInPktNum;    /* 接口收到的ARP非法报文数目 */
    ULONG      ipif_ulIcmpHostUnreach;      /* 接口收到的主机不可达报文数目 */
    ULONG      ipif_ulIcmpRedirect;         /* 接口收到的重定向报文数目 */
    ULONG      ipif_ulControlFlag;      /* 控制标志，可以供各种对IP的控制命令使用 */
    ULONG      ipif_ulNODHCPFlag;       /* 接口地址优先级高于DHCP获得地址的优先级的标志位，即如果接口上有
                                           地址则DHCP学习的地址不会配置到接口上，2006-06-03 */

/* End:同步D21代码  x36530  2004-9-8  */

#define ipif_ulMetric     ipif_stData.ifi_ulMetric
#define ipif_ulLoad       ipif_stData.ifi_ulLoad
#define ipif_ulIPackets   ipif_stData.ifi_ulIPackets
#define ipif_ulOPackets   ipif_stData.ifi_ulOPackets
#define ipif_ulIBytes     ipif_stData.ifi_ulIBytes
#define ipif_ulOBytes     ipif_stData.ifi_ulOBytes
#define ipif_ulIMcasts    ipif_stData.ifi_ulIMcasts
#define ipif_ulOMcasts    ipif_stData.ifi_ulOMcasts
    ULONG ulIgmpVer;      /*z62531,IGMP兼容变量*/
    ULONG ulHostRtReserved;  /*保留主机路由标记*/
} IPIFNET_S,*PIPIFNET_S;

/* Begin:同步D21代码  x36530  2004-9-8  */
/*Added by pengjimei for 8070 IP特性移植项目 2004/04/15*/
/* IP statics for display information */
typedef struct tagIPSHOWSTAT
{
    IPIFSTAT_S  ipif_stData;    /* 接口的统计信息 */
} IPSHOWSTAT_S;

/* End:同步D21代码  x36530  2004-9-8  */

typedef struct _IP_radix_node 
{
    struct _IP_radix_node  *rnode_left;     /* child when bit clear */
    struct _IP_radix_node  *rnode_right;    /* child when bit set */
    struct _IP_radix_node  *rnode_parent;   /* parent */
    USHORT     rnode_bit;                   /* bit number for node/mask 掩码长度*/
    UCHAR      rnode_tbyte;                 /* UCHAR to test in address 0~3，掩码长度值所在字节，*/
    UCHAR      rnode_tbit;                  /* bit to test in UCHAR */
    struct tagIPIFADDR *rnode_beginaddr;    /* our external info */
    struct tagIPIFADDR *rnode_endaddr;      /* our external info */
    ULONG      rnode_flag;                  /* 标志自己的子孙所包含的网段*/
    VOID      *rnode_pstVrf;
} IP_radix_node; 


typedef struct tagIPAddrTable
{
    struct _IP_radix_node *pstRootNode; /* 根节点 */
    ULONG  ulNodeNum;                   /* radix节点数 */
    ULONG  ulAddrNum;                   /* 地址数 */
}IPAddrTable;  

typedef struct tagIP_L3VPN_VRF
{
    ULONG                    ulVrfIndex;        /* VRF Index */
    IPAddrTable            * pVRFIPAddrTable;   /* Radix Tree */
    IPIFADDR_S             * pVRFIPIfAddr;      /* Address List */   
    struct tagIP_L3VPN_VRF * pstPrev;
    struct tagIP_L3VPN_VRF * pstNext;
}IP_L3VPN_VRF_S,*PIP_L3VPN_VRF_S;

/*结构IFADDRMSG_S已经挪到am4_api.h*/

struct tagIFNET;
/**********************************************************************/
/* public interface provided by core. can be called through component */
/* way, also here provide prototypes, other module can call these     */
/* interface directly                                                 */
/**********************************************************************/
/* judge if a packet is multicast */
extern ULONG IP_IsMultiCast(struct tagMBuf *pstMBuf) ;
/* judge if a packet is netbroadcast */
extern ULONG IP_IsNetBroadcast(struct tagMBuf *pstMBuf) ;
/* judge if a packet is subnetbroadcast */
extern ULONG IP_IsSubNetBroadcast(struct tagMBuf *pstMBuf) ;

/* is the net mask valid?(continuous) */
extern ULONG IP_NetmaskIsContinue( ULONG ulMask );

/* judge if an address is broadcast address, including all 1, all 0, broadcast on if. */
extern ULONG IP_IsBroadcast(struct tagIFNET *pstIfNet, ULONG ulIpAddr );
/* judge if an address is broadcast address on if */
extern ULONG IP_IF_IsBroadcast( ULONG ulIpAddr, struct tagIFNET *pstIfNet );

/* is the address and mask invalid on the interface? */
extern ULONG IP_IsInvalidIPAddress( struct tagIFNET *pstIfNet, ULONG ulAddr, ULONG ulMask );

/* does the address and mask conflict with other configured address? */
extern ULONG IP_ConflictIpAddress( IPIFNET_S *pstIpIf, ULONG ulAddr, ULONG ulMask, ULONG ulFlag); /* mayun & yuyong */

/* get the current configured addres number of the interface */
extern ULONG IP_GetAddrNumOnIf( IPIFNET_S *pstIpIf );

/* get the multicast group number joined on the interface */
extern ULONG IP_GetMultiAddrNumOnIf( IPIFNET_S *pstIpIf );

/* does the interface has address? */
extern ULONG IP_IF_HaveIpAddr( struct tagIFNET *pstIfNet );

/* get the main address and mask of the interface */
/* the address maybe OWN or BORROW */
extern ULONG IP_Get_Main_IpAddr( IPIFNET_S *pstIpIf, ULONG *pulMainAddr, ULONG *pulMainMask );
/* get the main address of the interface */
/* the address maybe OWN or BORROW */
/* (same functionality with previous, ifindex used as incoming parameter) */
extern ULONG IP_GetIfIpAddrByIndex ( ULONG ulIndex, ULONG *pulIpAddr );
/* get the main address of the interface, only OWN address */
extern ULONG IP_Get_MainIpAddr( IPIFNET_S *pIpIf );
/* get the main address of the interface, only OWN address */
/* (same functionality with previous, use ifnet as parameter) */
extern ULONG IP_Get_IF_MainIpAddr( struct tagIFNET *pstIf );

/* get the mask for the address on interface. when failed, return 0 */
extern ULONG IP_GetMask( struct tagIFNET *pstIfNet, ULONG ulIpAddr );

/* search the longest match address of the interface */
extern ULONG IP_IF_MaxIpAddr( struct tagIFNET *pstIfNet, ULONG ulIpAddr );
/* search the longest match address on interface */
/* (same functionality with previous, parameter diff) */
extern IPIFADDR_S *IP_IF_IFA_IfWithBestNet( SOCKADDRIN_S *pSockInAddr, IPIFNET_S *pIpIf );

/* search the multicast address on interface */
extern IPMULTI_S *IP_FindMultiOnIpIf( INADDR_S *pAddr, IPIFNET_S *pIpIfNet );

/* is the address one of the interface? */
extern ULONG IP_IF_IsThisIfIpAddr ( struct tagIFNET *pstIfNet, ULONG ulIpAddr );

/* is this address a VRF's local address? (address of one of VRF's interface) */
extern ULONG IP_IsLocalIfAddr(ULONG ulIpAddr, ULONG ulVrfIndex); /* mayun & yuyong */
extern ULONG IP_IsLocalUpIfAddr(ULONG ulIpAddr, ULONG ulVrfIndex); /* add by z62531 for A82D15058 */

/* 根据地址获取地址所在接口索引(跳过借用地址的接口) */
extern ULONG IP_DHCP4R_FindIfByIp( ULONG ulGiaddr, ULONG ulVrfIndex);

/* Added by l57500 for 同步VISPV1R5问题单A82D13365,2007-05-09 */
/* 查询指定的地址是否和接口上的地址处于相同网段 */
extern ULONG IP_IF_IsSameNet(struct tagIFNET *pstIfNet, ULONG ulIpAddr);
/* End of addition */

/* search all VRF's address, find the interface which has the specified address. */
/* (almost same with the previous one. a little more is: returns the ifindex) */
extern ULONG IP_GetIfindexbyIpAddr(ULONG ulIpAddr,ULONG *pulIfIndex, ULONG ulVrfIndex);
/* find the address whose neighbor is the given one, in the VRF */
extern IPIFADDR_S *IP_IFA_IfWithDstAddr( SOCKADDRIN_S *pSockInAddr ,ULONG ulVrfIndex); /* mayun & yuyong */
/* find the local address, which is in the same net with given one, in the VRF */
extern IPIFADDR_S *IP_IFA_IfWithNet(SOCKADDRIN_S *pSockInAddr, ULONG ulVrfIndex); /* mayun & yuyong */
/* find if the address is a local address or a broadcast address of the VRF */
extern IPIFADDR_S *IP_IFA_IfWithAddr( SOCKADDR_S *pstSockAddr, ULONG ulVrfIndex);  /* mayun & yuyong */

/* get any valid address from all of the VRF's */
extern IPIFADDR_S *IP_Get_ValidIpAddr( ULONG ulVrfIndex );
/* get any valid address from all of the VRF's. */
/* (same functionality with previous, only parameter diff) */
extern BOOL_T IP_GetValidAddress( ULONG *pulValidIpAddr, ULONG ulVrfIndex);

/* ARP to query if the address is valid input */
extern ULONG IP_Eth_IsValidIpAddr( struct tagIFNET *pstIfNet, ULONG ulSrcIpAddr, ULONG ulDstIpAddr, USHORT usOpType);

/* get the interface state. */
/* not a good idea use this interface. */
/* maybe can use pstIfnet->if_pfLinkDownIOCtl with SIOCLINKSTATE cmd instead. */
extern ULONG IP_GetIfUpDownStateFromIndex(ULONG ulIfIndex, ULONG *pUpDown);



/* these defines are  kept for compatibility. */
#define RM_vrf_GetVRFByIndex          IP_L3VPN_LocateVRFByIndex
#define RM_vrf_locate(name, bCreate)  IP_L3VPN_LocateVRFByName(name)
#define RM_vrf_S IP_L3VPN_VRF_S

/* VRP creation, deletion, interface changing */
extern ULONG IP_L3VPN_VRF_CallBack(ULONG ulEvent, VOID * pData);
/* find VRF with specified name */
extern IP_L3VPN_VRF_S * IP_L3VPN_LocateVRFByIndex(ULONG ulVRFIndex);
/* find VRF with specified VRFindex */
extern IP_L3VPN_VRF_S * IP_L3VPN_LocateVRFByName(CHAR *szName);
/* is the vrf index valid? */
extern BOOL_T IP_L3VPN_IsValidVRFIndex(ULONG ulVRFIndex);

/* link layer and ifnet UP IOCtl function. */
extern ULONG IP_Addr_LLC_Notify( struct tagIFNET *pstIfNet, ULONG ulCmd, CHAR *pcData);
/* Attach IP to an interface */
extern ULONG IP_IF_Attach( struct tagIFNET *pstIfNet );
/* Detach IP to an interface */
extern ULONG IP_IF_Detach( struct tagIFNET *pstIfNet, ULONG ulCmd);


#endif  /* _AM4_PUB_H_  */

#ifdef  __cplusplus
}
#endif
