/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              addr_public.h
*
*    Project Code:  IPBIRV1R2
*    Module Name :  Addr
*    Create Date :  2006/09/23
*    Version     :  Initial Draft
*    Author      :  Yinyuanbin
*    Description :  To define Addr data structures used by external modules
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-09-23  yinyuanbin    Created for including all public definitions in
*                             this file, for IPBIRV1R2
************************************************************************/
#ifndef _ADDR_PUBLIC_H
#define _ADDR_PUBLIC_H


#ifdef  __cplusplus
extern "C"{
#endif  /* #ifdef  __cplusplus */

/*----------------------------------------------*
 *              Macros                          *
 *----------------------------------------------*/

#define IP6_NP_ADDR_NODELETE           (1<<0)
#define IP6_NP_ND_RESETALLNB           (1<<1)
#define IP6_NP_NDRESETDYNAMICNB        (1<<2)
#define IP6_NP_ND_RESETSTATICNB        (1<<3)
#define IP6_NP_ADDR_AUTOCONFIGSWICH    (1<<4)

/* Added for NDHost */

/*MAX_INT to arm allign the enums*/
#define IP6_ADDR_MAX_ENUM_VALUE            0xFFFFFFFF


#define IP6_ADDR_MIN_MTU     1280
#define IP6_ADDR_MAX_MTU     1800  /*Modified by Rakesh to 1800 as per product requirement */
#define IP6_ADDR_DEFAULT_MTU 1500
#define IP6_ADDR_NO_MTU 0


#define IP6_ADDR_MTU_CONFIG                   0
#define IP6_ADDR_MTU_UNDO_CONFIG              1
#define IP6_ADDR_MTU_CLI_CONFIG               2

#define IP6_ADDR_MTU_ACTUAL_CONFIG            0
#define IP6_ADDR_MTU_RA_CONFIG  1

/* In IPOS the maximum Number of Address is 16 + 1 - link local address */
#define IP6_DISPMAXADDRNUM_PERIF 17

/* Prefix length for Link local addess and Site local address */
#define IP6_ADDR_PRELEN_LLA    10
#define IP6_ADDR_PRELEN_SLA    10
#define IP6_ADDR_PRELEN_MAX    128


#define  IP6_DAD_RESET          0     /* Reset the DAD state flag  */
#define  IP6_DAD_OK             1     /* DAD is OK and Address is valid*/
#define  IP6_DAD_TENTATIVE      2     /* tentative address */
#define  IP6_DAD_DUPLICATED     4     /* DAD detected duplicate */
#define  IP6_DAD_NODAD          8     /* Don't perform DAD on this address */

/*Added by guojianjun178934, DAD扩展状态, 2014/2/20   问题单号:DTS2014021206259  */
#define IP6_DAD_EXT_NULL          0
#define IP6_DAD_EXT_OK            1
#define IP6_DAD_EXT_DUPLICATED   2
/* End of Added by guojianjun178934, 2014/2/20   问题单号:DTS2014021206259  */

#define IP6_DAD_INVALID         0xFFFFFFFF 

#define  IP6_ENABLE              32
#define  IP6_MANUAL_LINKLOCAL    64

#define IP6_ADDR_EUI64           1


#define INVALID_IFINDEX          0xFFFFFFFF


/*waitlist macros*/
#define IP6_ADDR_MULTICAST_WAITLIST       1
#define IP6_ADDR_UNICAST_WAITLIST         2
#define IP6_ADDR_IFNET_WAITLIST           3

#define IPv6_ANYCAST_TRUE                 1
#define IPv6_ANYCAST_FALSE                2

#define IPv6_ADDR_STATELESS               1
#define IPv6_ADDR_STATEFUL                2
#define IPv6_ADDR_STATEUNKNOWN            3

/*macro to show Administrative status of a link */
#define IPv6_ADDR_ADMIN_STATUSUP          1
#define IPv6_ADDR_ADMIN_STATUSDOWN        2

#define IP6_ADDR_BUFF_ADDRSIZE           50

#define MACADDRLEN 6
#define MACADDRLENPAD 2

#define  IP6_LINK_P2P_NO        0x1
#define  IP6_LINK_P2P_YES       0x2

/*link type macros ppp or fr*/
#define  IP6_LINK_P2P           0x4
#define  IP6_LINK_FR            0x8

/* Used by Internal Functions only - can be moved to internal header */
#define  IPV6_ADDR_SCOPE_RESERVED       0x00
#define  IPV6_ADDR_SCOPE_NODELOCAL      0x01
#define  IPV6_ADDR_SCOPE_INTFACELOCAL   0x01
#define  IPV6_ADDR_SCOPE_LINKLOCAL      0x02
#define  IPV6_ADDR_SCOPE_SITELOCAL      0x05
#define  IPV6_ADDR_SCOPE_ORGLOCAL       0x08
#define  IPV6_ADDR_SCOPE_GLOBAL         0x0e

/*address types*/
#define  IP6_TYPE_LINKLOCAL   0
#define  IP6_TYPE_GLOBAL      1
#define  IP6_TYPE_ANY         2



#define  IP6_ADDR_TRUE    1
#define  IP6_ADDR_FALSE   0


#define  IP6_ADD    16
#define  IP6_DEL    32
#define  IP6_CHA    64
#define  IP6_OTH    128 /* Return value of a config API */

#define ADD_ADDRESS   0
#define DEL_ADDRESS   1
#define DEL_ALL_UNSET 1
#define DEL_ALL_SET   0
#define FLAG_SET      1
#define FLAG_UNSET    0

#define IP6_ADDR_AUTOCONFIG_ENABLE  1
#define IP6_ADDR_AUTOCONFIG_DISABLE 0

#define     IP6_ADDR_DISP_FIL_ALL          1
#ifndef TCPIP_DOUBLEOS
/***************************************************************************************/
#define IN6ADDR_ANY_INIT \
    {{{ 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00 }}}
/***************************************************************************************/

#define IN6ADDR_LOOPBACK_INIT \
    {{{ 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x01 }}}
/***************************************************************************************/
#else
/***************************************************************************************/
#define VRP_IN6ADDR_ANY_INIT \
    {{{ 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00 }}}
/***************************************************************************************/

#define VRP_IN6ADDR_LOOPBACK_INIT \
    {{{ 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x01 }}}
/***************************************************************************************/
#endif
#define IN6ADDR_NODELOCAL_ALLNODES_INIT \
    {{{ 0xff, 0x01, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x01 }}}
/***************************************************************************************/

#define IN6ADDR_INTFACELOCAL_ALLNODES_INIT \
    {{{ 0xff, 0x01, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x01 }}}
/***************************************************************************************/

#define IN6ADDR_LINKLOCAL_ALLNODES_INIT \
    {{{ 0xff, 0x02, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x01 }}}
/***************************************************************************************/

#define IN6ADDR_LINKLOCAL_ALLROUTERS_INIT \
    {{{ 0xff, 0x02, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x02 }}}
/***************************************************************************************/

#define  IP6_SCOPE_ORDER_INTERFACELOCAL 0x01
#define  IP6_SCOPE_ORDER_NODELOCAL      0x01
#define  IP6_SCOPE_ORDER_LINKLOCAL      0x02
#define  IP6_SCOPE_ORDER_ORGLOCAL       0x03
#define  IP6_SCOPE_ORDER_GLOBAL         0x04
#define  IPV6_ADDR_SCOPE_SUPPORT_NUM    0x04


#define  ip6if_stNodeLocalUniAddr    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_NODELOCAL - 1].stUnicastAddrlist
#define  ip6if_stNodeLocalMultiAddr    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_NODELOCAL - 1].stMulticastAddrlist
#define  ip6if_ulNodeLocalScopeType    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_NODELOCAL - 1].ulScopeType
#define  ip6if_ulNodeLocalScopeZoneId    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_NODELOCAL - 1].ulScopeZoneId


#define  ip6if_stInterfaceLocalUniAddr    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_INTERFACELOCAL - 1].stUnicastAddrlist
#define  ip6if_stInterfaceLocalMultiAddr    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_INTERFACELOCAL - 1].stMulticastAddrlist
#define  ip6if_ulInterfaceLocalScopeType    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_INTERFACELOCAL - 1].ulScopeType
#define  ip6if_ulInterfaceLocalScopeZoneId    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_INTERFACELOCAL - 1].ulScopeZoneId


#define  ip6if_stLinkLocalUniAddr    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_LINKLOCAL - 1].stUnicastAddrlist
#define  ip6if_stLinkLocalMultiAddr    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_LINKLOCAL - 1].stMulticastAddrlist
#define  ip6if_ulLinkLocalScopeType    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_LINKLOCAL - 1].ulScopeType
#define  ip6if_ulLinkLocalScopeZoneId    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_LINKLOCAL - 1].ulScopeZoneId

#define  ip6if_stOrgLocalUniAddr    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_ORGLOCAL - 1].stUnicastAddrlist
#define  ip6if_stOrgLocalMultiAddr    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_ORGLOCAL - 1].stMulticastAddrlist
#define  ip6if_ulOrgLocalScopeType   \
    ip6if_stAddrList[IP6_SCOPE_ORDER_ORGLOCAL - 1].ulScopeType
#define  ip6if_ulOrgLocalScopeZoneId   \
    ip6if_stAddrList[IP6_SCOPE_ORDER_ORGLOCAL - 1].ulScopeZoneId


#define  ip6if_stGlobalUniAddr    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_GLOBAL - 1].stUnicastAddrlist
#define  ip6if_stGlobalMultiAddr    \
    ip6if_stAddrList[IP6_SCOPE_ORDER_GLOBAL - 1].stMulticastAddrlist
#define  ip6if_ulGlobalScopeType   \
    ip6if_stAddrList[IP6_SCOPE_ORDER_GLOBAL - 1].ulScopeType
#define  ip6if_ulGlobalScopeZoneId   \
    ip6if_stAddrList[IP6_SCOPE_ORDER_GLOBAL - 1].ulScopeZoneId

#define V6_LIST_FIRST(ptr)  ((ptr)->ia6_v_pNext)
#define V6_LIST_NEXT(ptr)   ((ptr)->ia6_v_pNext)

 /*----------------------------------------------*
  *              Enumerated Data Types           *
  *----------------------------------------------*/

/* log level */
enum LOG_LEVEL
{

    IP6_LEVEL_DEBUGGING,        /* Inside some place displaying some error
                                                                information*/
    IP6_LEVEL_INFORMATIONAL,    /* It will cover normal functionaliy */
    IP6_LEVEL_INTERFACES,       /* This will display messages of AM sent or
                                   received though any other module interface */
    IP6_LEVEL_ALL,              /* This will display all the information,
                                   above 3 included*/
    IP6_LEVEL_BUT,

    IP6_LEVEL_PADDING = IP6_ADDR_MAX_ENUM_VALUE
};

/*enum used to define the error numbers during CLI processing */
typedef enum tagCLIErrorNum
{
    IP6_ADDR_ERR_INVALID_GLOBAL_UNICAST = 2,     /* 2 */
    IP6_ADDR_ERR_ADDR_CONFLICT,                  /* 3 */
    IP6_ADDR_ERR_NUM_EXCEED_MAX_LIMIT,           /* 4 */
    IP6_ADDR_ERR_INVALID_LLA,                    /* 5 */
    IP6_ADDR_ERR_EUI_PREFIX_LEN,                 /* 6 */
    IP6_ADDR_ERR_INVALID_INTERFACEID,            /* 7 */
    IP6_ADDR_INVALID_ADDRESS,                    /* 8 */
    IP6_ADDR_ERR_INVALID_DEL_GLOBAL_UNICAST,     /* 9 */
    IP6_ADDR_ERR_ADDR_NOT_EXIST,                 /* 10 */
    IP6_ADDR_MALLOC_FAIL,                        /* 11 */
    IP6_ADDR_ERR_DEL_AUTOCFG,                    /* 12 */
    IP6_ADDR_ERR_AUTOADDRNOT_EXIST,              /* 13 */
    IP6_ADDR_ERR_INVALID_LOOPBACK,               /* 14 */
    IP6_ADDR_ERR_INVALID_MULTICAST,              /* 15 */
    IP6_ADDR_ERR_INVALID_UNSPECIFIED,            /* 16 */
    IP6_ADDR_ERR_INVALID_DEL_UNSPECIFIED,        /* 17 */
    IP6_ADDR_ERR_INVALID_DEL_LOOPBACK,           /* 18 */
    IP6_ADDR_ERR_INVALID_DEL_MULTICAST,          /* 19 */
    IP6_ADDR_INVALID_ANYCAST,                    /* 20 */
    IP6_ADDR_ERR_INVALID_V4ADDR,                 /* 21 */
    IP6_ADDR_ERR_V4MAPPED_ADDR,                  /* 22 */
    IP6_ADDR_ERR_PREFIX_LEN,                     /* 23 */
    IP6_ADDR_ERR_INVALIDPPP_ADDR,                /* 24 */
    IP6_ADDR_INVALIDNB_ADDR,                     /* 25 */
    IP6_ADDR_ERR_IO_BOARD,                       /* 26 */
    IP6_ADDR_MTU_SHUT_UNSHUT,                    /* 27 */
    IP6_NOFREE_ITEM,                             /* 28 */
    IP6_ADDR_ERR_OPERATION_NOT_SUPPORTED,

    /* Return values for Config APIs*/
    IP6_ADDR_ERR_NULL_INPUT,                    /* 30 */
    IP6_ADDR_ERR_FETCH_CTRL_BLK,                /* 31 */
    IP6_ADDR_ERR_OLDADDR_MODIFY,                /* 32 */
    IP6_ADDR_ERR_AUTOCFG_LINKLOCAL,             /* 33 */
    IP6_ADDR_ERR_ADD_ADDR,                      /* 34 */
    IP6_ADDR_ERR_FINDADDRESS,                   /* 35 */
    IP6_ADDR_ERR_ADDR_DEL_FAIL,                 /* 36 */
    IP6_ADDR_ERR_NOADDR_CFGD,                   /* 37 */
    IP6_ADDR_ERR_INVALID_MTU,                   /* 38 */
    IP6_ADDR_ERR_INVALID_INTERFACE_POINTER,     /* 39 */
    IP6_ADDR_ERR_INVALID_WAITLIST_TYPE,         /* 40 */
    IP6_ADDR_ERR_WAITLIST_REGISTER,             /* 41 */
    IP6_ADDR_ERR_WAITLIST_UNREGISTER,           /* 42 */
    IP6_ADDR_ERR_WAITLISTSET,                   /* 43 */
    IP6_ADDR_ERR_WAITLISTGET,                   /* 44 */
    IP6_ADDR_ERR_GET_FIRST_ADDRTBL,             /* 45 */
    IP6_ADDR_ERR_GET_NEXT_ADDRTBL,              /* 46 */
    IP6_ADDR_ERR_INVALID_SCOPE,                 /* 47 */
    IP6_ADDR_ERR_GET_ADDRTBL,                   /* 48 */
    IP6_ADDR_ERR_GET_FIRST_IFTBL,               /* 49 */
    IP6_ADDR_ERR_GET_NEXT_IFTBL,                /* 50 */
    IP6_ADDR_ERR_SAME_NB_EXIST,                 /* 51 */
    IP6_ADDR_ERR_NEED_SENDTO_IO,                /* 52 */
    IP6_ADDR_ERR_NO_IPV6_ADDR_EXIST_ON_INTF,           /* 53 */

    /* Added by karthik as per SGSN CR*/
    IP6_ADDR_ERR_INVALID_WAITLIST_ID,           /* 54 */
    IP6_ADDR_ERR_WAITLISTGET_PARAM,             /* 55 */
    IP6_ADDR_ERR_INVALID_FIL_INPUT,             /* 56 */

    /**************************************************************************
    Added for IPV6 ND-HOST
    **************************************************************************/
    IP6_ADDR_ERR_IPV6_NOT_ENABLED,
    IP6_ADDR_ERR_INTF_NOT_SUPPORTED,                    /* 58 */
    IP6_ADDR_ERR_IPV6_ENABLE_FAILED,                    /* 59 */
    IP6_ADDR_ERR_IPV6_DISABLE_FAILED,                   /* 60 */
    IP6_ADDR_ERR_INVALID_PREFIXLEN_STATELESS_ADDRESS,   /* 61 */
    IP6_ADDR_ERR_INVALID_LIFETIME_AUTOCFG_ADDRESS,      /* 62 */
    IP6_ADDR_ERR_INVALID_ADDRESSPREFIX,                 /* 63 */
    IP6_ADDR_ERR_INVALID_INPUT,                         /* 64 */
    IP6_ADDR_ERR_MAX_APPLICATION_LIMIT,                 /* 65 */
    IP6_ADDR_ERR_APP_ALREADY_REGISTERED,                /* 66 */
    IP6_ADDR_ERR_APP_NOT_REGISTERED,                    /* 67 */
    IP6_ADDR_ERR_LLA_NOT_EXISTS,                        /* 68 */
    IP6_ADDR_ERR_ADDR_NOT_MANUALLYCFGED,                /* 69 */
    IP6_ADDR_ERR_INIT_DELAY_NOT_SUPPORTED,              /* 70 */
    IP6_ADDR_ERR_INVALID_DEST_ADDR,                     /* 71 */
    IP6_ADDR_ERR_IDENTIFY_OUT_INTF,                     /* 72 */
    IP6_ADDR_ERR_IATYPE_NOT_SUPPORTED,                  /* 73 */
    IP6_ADDR_ERR_INVALID_ADDR_COUNT,                    /* 74 */
    IP6_ADDR_ERR_CONFLICT_ADDRONOTHER,                  /* 75 */
    IP6_ADDR_ERR_CONFLICT_ADDRONSELF,                   /* 76 */
    IP6_ADDR_ERR_PROTOCOL_DOWN,                         /* 77 */
    IP6_ADDR_ERR_NO_SUCH_ADDRESS_EXISTS,                /* 78 */
    IP6_ADDR_ERR_MULTI_SCOPE_NOT_SUPPORTED,             /* 79 */

    /* Waitlist Related Error values */
    IP6_ADDR_ERR_GETFIRST_NO_UNIADDR,                   /* 80 */
    IP6_ADDR_END_OF_ADDR_LIST,                          /* 81 */
    IP6_ADDR_ERR_GETFIRST_NO_MULTIADDR,                 /* 82 */
    IP6_ADDR_ERR_INVALID_INTF_INDEX,                    /* 83 */
    IP6_ADDR_ERR_SRC_NOT_AVAILABLE,                     /* 84 */
    IP6_ADDR_ERR_DISPLAY_GETFIRST,                      /* 85 */
    IP6_ADDR_ERR_DISPLAY_GETNEXT,                       /* 86 */
    IP6_ADDR_ERR_CONFLICT_PREFIXONSELF,                 /* 87 */
    IP6_ADDR_ERR_CONFLICT_PREFIXONOTHER,                /* 88 */
    IP6_ADDR_ERR_INVALID_WAITLIST_HANDLE,               /* 89 */

    /* Description: New error code is added for deletion of all EUI-64
       addresses */
    IP6_ADDR_ERR_NO_EUI_ADDR_AVAIL,                     /* 90 */


    IP6_ADDR_ERR_SEMOP_ACQUIRELOCK_FAIL,                /* 91 */

    IP6_ADDR6_ERR_NULL_INPUT,                           /* 92 */
    IP6_ADDR6_MALLOC_FAIL,                              /* 93 */
    IP6_ADDR6_ERR_WAITLIST_REGISTER,                    /* 94 */
    IP6_ADDR6_ERR_WAITLISTSET,                          /* 95 */
    IP6_ADDR6_ERR_INVALID_WAITLIST_HANDLE,              /* 96 */
    IP6_ADDR6_ERR_WAITLISTGET,                          /* 97 */
    IP6_ADDR6_ERR_INVALID_IFINDEX,                      /* 98 */
    IP6_ADDR6_ERR_NULL_IP6IFNET,                        /* 99 */
    IP6_ADDR6_ERR_NONE_LINKLOCAL_ADDR,                  /* 100 */
    IP6_ADDR6_ERR_WAITLISTGET_PARAM,                    /* 101 */
    IP6_ADDR6_ERR_GET_IP6ADDR_END,                      /* 102 */
    IP6_ADDR6_ERR_CREATNEWADDRFAILED,                   /* 103 */
    IP6_ADDR6_ERR_ADDALLNODESFAILED,                    /* 104 */
    IP6_ADDR6_ERR_ADDALLROUTERSFAILED,                  /* 105 */
    IP6_ADDR6_ERR_ADDSOLICITEDMULTIFAILED,              /* 106 */
    IP6_ADDR6_ERR_DEL_CTRL_BLK_FAILED,                  /* 107 */
    IP6_ADDR6_ERR_DEL_MULTI_ADDR_FAILED,                /* 108 */

    IP6_ADDR_MAX,

    IP6_ADDR_ERR_PADDING = IP6_ADDR_MAX_ENUM_VALUE
}IP6_ADDR_CLI_ERR_NUM_E;

/* IAS operation */
typedef enum tagIP6_ADDR_IAS_OPERATION
{
    IP6_ADDR_IAS_NOTIFY_ADD,       /* IAS address addition operation */
    IP6_ADDR_IAS_NOTIFY_DELETE,    /* IAS address deletion operation */
    IP6_ADDR_IAS_NOTIFY_MAX,
    IP6_ADDR_IAS_NOTIFY_ULONG = IP6_ADDR_MAX_ENUM_VALUE
}IP6_ADDR_IAS_OPERATION_E;


/*----------------------------------------------*
 *              Data Structures                 *
 *----------------------------------------------*/

/* IPV6 Address Information */
typedef  struct   tagIP6IFADDR
{
    struct  tagIP6IFNET *ia6_pIp6If;
    IN6ADDR_S      ia6_stAddr;
    ULONG  ia6_ulAddrDADState;
    ULONG  ia6_ulAddrFlag;

    /* prefix  info*/
    IN6ADDR_S     ia6_stPrefixMask;
    ULONG  ia6_ulPrefixLength;

    /* destination info */
    IN6ADDR_S      ia6_stDstAddr;

    struct  tagIP6IFADDR    *ia6_v_pPrev;
    struct  tagIP6IFADDR    *ia6_v_pNext;
    struct  tagIP6IFADDR    *ia6_h_pPrev;
    struct  tagIP6IFADDR    *ia6_h_pNext;
    struct  tagIP6IFADDR    *ia6_ss_pPrev;
    struct  tagIP6IFADDR    *ia6_ss_pNext;
    UCHAR   ucNotifyRM;                   /* If set - added address has been
                                           * notified to RM, else it is not */

    UCHAR   ucHaveSendPrefix;             /* If this flag is SET then it means
                                           * for that particular prefix
                                           * notification to ND corresponding
                                           * to that address has already
                                           * been sent*/
    UCHAR   aucDuplicateTimes;
    UCHAR   ucDADExtState;

    /* Pointer to Information related to Stateful/Stateless addresses */
    VOID    *pvAddrInfo;
    UCHAR   *pucRdxExtNode; /*Radix extern node*/
    UCHAR   ucDuplicateLLAddr[MACADDRLEN]; /* 引起地址冲突的接口的mac地址 */
    UCHAR   bMACChange;                     /* MAC地址是否发生变化 */
    UCHAR   ucpad[1];
    /* Modified by guojianjun178934, DAD扩展处理, 2014/2/21   问题单号:DTS2014021206259  */
    ULONG  ulDADExtDuplicateTimes;
    ULONG  ulPPINotifyTags;
    ULONG  ulNPNotifyTags;
    /*End of Modified by guojianjun178934, 2014/2/21   问题单号:DTS2014021206259  */
} IP6IFADDR_S;

/* IPv6 Multicast Address information */
typedef struct    tagIP6MULTI
{
    ULONG ip6m_ulIfIndex;
    IN6ADDR_S ip6m_stAddr;
    USHORT ip6m_usRefCnt;

    UCHAR aucPadding[2];
    struct  tagIP6MULTI *ip6m_pNext;
}IP6MULTI_S;

/* Address Scope list structure */
typedef struct    tagScopedAddrList
{
    ULONG ulScopeType;
    ULONG ulScopeZoneId;
    IP6IFADDR_S stUnicastAddrlist;
    IP6MULTI_S stMulticastAddrlist;
}SCOPED_ADDR_LIST_S;

/* Interface ID structure */
typedef  struct  tagIp6InterfaceId
{
    union
    {
        UCHAR    u6_InterfaceId8[8];
        USHORT   u6_InterfaceId16[4];
        ULONG    u6_InterfaceId32[2];
    } u6_InterfaceId;
}IP6_INTERFACEID_S;

#define  ip6_ifid8    u6_InterfaceId.u6_InterfaceId8
#define  ip6_ifid16   u6_InterfaceId.u6_InterfaceId16
#define  ip6_ifid32   u6_InterfaceId.u6_InterfaceId32

/* structure for DAD related information*/
typedef  struct  tag_IP6_ADDR_DADSTATE
{
    ULONG  ulIfIndex;         /* Interface Index corresponding to
                                 the self I/O board */
    ULONG  ulAddrDADState;    /* Address state OK/TENTATIVRE/DUPLICATED */
    IN6ADDR_S stIp6Addr;      /* Address whose DAD state changed */

    BOOL_T    bDADCompleteNotify;  /* Flag to check whether Invocation of
                                      DAD_Complete_Notify is required in
                                      Main Board */
    UCHAR     ucPad[2];            /* Padding for Structure Allignment */

}IP6_ADDR_DADSTATE_S;

/*structure for IFNET status */
typedef struct tagIP6_ADDR_IFSTATUS
{
    ULONG          ulIfIndex;
    ULONG          ulPhyStatus;
    ULONG          ulLineStatus;

}IP6_ADDR_IFSTATUS_S;

/*address table structure*/
typedef struct tagIP6_ADDR_ADDRTBL
{
    ULONG          ulIfIndex;
    IN6ADDR_S      stIPv6Addr;
    ULONG          ulAddrPfxLength;
    ULONG          ulAddrType;
    ULONG          ulAnyCastFlag;
    ULONG          ulAddrStatus;
}IP6_ADDR_ADDRTBL_S;

/*addr IFNET entry*/
typedef struct tagIP6_ADDR_IFENTRY
{
    ULONG            ipv6IfIndex;
    UCHAR            ipv6IfDescr[255];
    UCHAR            ucPadding_1;
    ULONG            ulipv6IfDescrLength;
    UCHAR            ipv6IfLowerLayer;
    UCHAR            aucPadding_2[3];
    ULONG            ipv6IfEffectiveMtu;
    ULONG            ipv6IfReasmMaxSize;
    UCHAR            ipv6IfIdentifier[255];
    UCHAR            ucPadding_3;
    LONG             ipv6IfIdentifierLength;
    UCHAR            ipv6IfPhysicalAddress[MACADDRLEN];
    UCHAR            aucPadding[MACADDRLENPAD];
    LONG             ipv6IfAdminStatus;
    LONG             ipv6IfOperStatus;
    ULONG            ipv6IfLastChange;
}IP6_ADDR_IFENTRY_S;


/* structure for MIB object */
typedef struct tagIP6_ADDR_MIB_OBJ
{
    LONG lipv6Forwarding;
    LONG lDefaultHopLimit;
    ULONG ulIpv6Interfaces;
    ULONG ipv6IfTableLastChange;

}IP6_ADDR_MIB_OBJ_S;


/*structure for address notify message*/
typedef struct tagIP6_ADDR_NOTIFY_MSG
{
    ULONG  ulIfnetIndex;      /* IFNET index of bound physical interface */
    ULONG  ulMsgType;         /* IP address added or deleted */
    ULONG  ulLogAddr[4];      /* IP address */
    ULONG  ulSubMaskLen;      /* Address mask length*/
    /* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
    ULONG  ulInstanceID;
    /* End: VISP V3R2C10 VRF chandra , 2014-03-18 */    

}IP6_ADDR_NOTIFY_MSG_S;


/*addr SGSN callback functions*/
typedef struct tagIP6_ADDR_SGSN_CALLBACK_FUNC_S
{

    /* Function Registered by product*/
    ULONG (*pfIP6_Notify_DuplicateAddr) (IP6_ADDR_DADSTATE_S *);

}IP6_ADDR_SGSN_CALLBACK_FUNC_S;

/* IPv6 Control Block */
typedef  struct   tagIP6IFNET
{
    ULONG    ip6if_ulIndexIf;
    ULONG    ip6if_ulMtu;

    ULONG    ip6if_ulNGMtu;
    ULONG    ip6if_ulAddrFlag;

    ULONG    ip6if_osicpFlag;
    ULONG    ip6if_ulLastChange; /*Added for MIB*/
    /* VPNV6_DEV_BEGIN */
    USHORT usVrfIndex;
    USHORT usFill;
    /* VPNV6_DEV_END */
    struct  tagScopedAddrList    ip6if_stAddrList[IPV6_ADDR_SCOPE_SUPPORT_NUM];
    struct tagNDInfo    * ip6if_pstNDInfo;
    IP6STAT_S  stIP6Stat;
    ICMP6STAT_S stICMP6Stat;
    ULONG   ulInitDelayTimerId;
    
    /* Start: RFC4443 compliance changes */
    ICMP6INFO_S stIcmp6Info;
    
    /* End: RFC4443 compliance changes */

    USHORT  usHostEvents;

    UCHAR ucFlag;


    UCHAR  ucPad;

    ULONG ip6if_ulMtuRA; /* To store the mtu from RA */
    ULONG ip6if_ulMtuManual; /* To store the mtu from Manual config*/
} IP6IFNET_S;


/*addr SRM callback functions*/
typedef struct tagIP6_ADDR_SRM_CALLBACK_FUNC_S
{
    ULONG (*pfIP6_Addr_Shell_Srm_Callback)(USHORT usInstanceID,
                                           IP6_ADDR_NOTIFY_MSG_S* pstIpMsg);
    /* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
    /* ULONG (*pfIP6_Addr_Shell_Srm_JudgeFunction)(VOID); */
    ULONG (*pfIP6_Addr_Shell_Srm_JudgeFunction)(USHORT usZoneId);
    /* End:VISP V3R2C10 VRF chandra , 2014-03-18 */
} IP6_ADDR_SRM_CALLBACK_FUNC_S;

/* Added by karthik for SGSN CR */
typedef struct tagIP6_ADDR_INFO_S
{
    ULONG  ia6_ulPrefixLength;    /* The value of the prefix length*/
    ULONG  ia6_ulAddrDADState;    /* The value of address state */

    /* Flag to indicate the address is configured through
       manual/stateless/stateful configuration or a link local address */
    ULONG  ia6_ulAddrFlag;        /* Flag to indicate eui/non eui address*/
    ULONG  ulIfIndex;             /* The interface index information*/
    IN6ADDR_S stIp6Addr;          /* The ipv6 address*/

    /* In ND Host - for Stateful and Stateless address */
    ULONG  ulAddrLifetimeState;   /* Address State Deprecate/preferred */
    ULONG  ulRemainValidTime;     /* Remaining Valid Lifetime */
    ULONG  ulRemainPrefTime;      /* Remaining Preferred Lifetime */
    ULONG  ulCfgValidTime;        /* Configured Valid Time */
    ULONG  ulCfgPrefTime;         /* Configured Preferred Time */
}IP6_ADDR_INFO_S;

/* Address information */
typedef struct tagIP6_ADDR_GET_INFO_S
{
    ULONG ulAddrCount;        /* The number of addresses updated in the array*/
    IP6_ADDR_INFO_S astIp6AddrInfo[IP6_DISPMAXADDRNUM_PERIF];
} IP6_ADDR_GET_INFO_S;

/* Filter Information Structure */
typedef struct tagIP6_ADDR_DISP_FILTER
{
    ULONG ulFlag;             /* The flag indicate the filter information*/
} IP6_ADDR_DISP_FILTER_S;



/******************************************************************************
ADDED By RAJAT PHULL for ND-Host
******************************************************************************/


/* Used to register socket-application's Callback. The registered Callbacks
   are invoked to notify interface ipv6 Enable/Disable functionality status */
typedef struct tagIP6_ADDR_APPLICATION_CALLBACK_FUNC
{

    /* Module Id */
    ULONG ulModuleId;

    /* Callback to Notify Interface Level Ipv6 Enable/Disable Status */
    ULONG (*pfIP6_ADDR_NotifyApplication)(ULONG ulIfnetIndex,
                                                    BOOL_T bIpv6FuncStatus);
}IP6_ADDR_APPLICATION_CALLBACK_FUNC_S;

/* Though the name of the structure has HOST in it, this 
 * structure is common for both host and router */
/* Multicast Address Info for display */
typedef struct tagIP6_NDHOST_MULTIADDR_INFO_S
{
    IN6ADDR_S stIp6Addr;   /* ipv6 multicast address */
    USHORT usRefCount;     /* Reference count */
    UCHAR  aucPad[2];      /* ARM CPU Support */
}IP6_NDHOST_MULTIADDR_INFO_S;

/* Address Types */
#define IP6_NDHOST_ADDR_PARA_NOTUSED    0
#define IP6_ADDR_EUI64                  1
#define IP6_NDHOST_ADDR_STATELESS       2
#define IP6_NDHOST_ADDR_STATEFUL        4
#define IP6_NDHOST_ADDR_MANUAL          8
#define IP6_NDHOST_ADDR_LINKLOCAL      16

/* Address States */
#define IP6_ADDR_LIFETIME_INVALID        0
#define IP6_ADDR_LIFETIME_PREFERRED      1
#define IP6_ADDR_LIFETIME_DEPRECATED     2

typedef enum tagIP6_ADDR_RESULT_NOTIFY
{
    NP_IP6ADDR_NOTIFY_DAD_OK,              /* Address DAD state is OK */
    NP_IP6ADDR_NOTIFY_DAD_DUPLICATE,       /* Address DAD state is DUPLICATE */
    NP_IP6ADDR_NOTIFY_LIFETIME_PREFERRED,  /* Address lifetime is PREFERRED */
    NP_IP6ADDR_NOTIFY_LIFETIME_DEPRICATED, /* Address lifetime is DEPRICATED */
    NP_IP6ADDR_NOTIFY_DAD_DUPICATE_RESUME, /* Address from duplicate to none duplicate*/
    NP_IP6ADDR_NOTIFY_DADEXT_DUPLICATE,     /*NA报文探测地址冲突*/
    NP_IP6ADDR_NOTIFY_DADEXT_DUPICATE_RESUME, /*NA报文探测地址冲突告警恢复*/
    NP_IP6ADDR_NOTIFY_PADDING = IP6_ADDR_MAX_ENUM_VALUE
}IP6_ADDR_RESULT_NOTIFY_E;

/*Added by guojianjun178934, 【检视问题单---DAD告警优化】产品定期发送地址冲突检测的NS报文，如果收到了NA我们需要启动DAD探测, 2014/2/21   问题单号:DTS2014021206259  */
#define NP_IP6ADDR_PPI_DAD_DUPLICATE        1       /*是否下发DAD冲突告警*/
#define NP_IP6ADDR_PPI_DADEXT_DUPLICATE    2        /*是否下发DADExt冲突告警*/
/* End of Added by guojianjun178934, 2014/2/21   问题单号:DTS2014021206259  */

/*addr callback functions*/
typedef struct tagIP6_ADDR_DADRESULT_NOTIFY_FUNC
{
    ULONG (*pfIP6_ADDR_Platform_Operation)(ULONG ulOperType, VOID *pvData);
} IP6_ADDR_DADRESULT_NOTIFY_FUNC_S;

typedef struct tagIP6_ADDR_NP_MSG
{
    ULONG     ulIfIndex;           /* Interface Index */
    IN6ADDR_S stIP6Addr;           /* IPv6 Address */
    ULONG     ulAddrLifetimeState; /* Preferred / Depricated State
                                      Possible Values :
                                      IP6_ADDR_LIFETIME_PREFERRED
                                      IP6_ADDR_LIFETIME_DEPRECATED
                                    */
    UCHAR   ucDADState;
    UCHAR   ucDADExtState;
    UCHAR   pad[2];
}IP6_ADDR_NP_MSG_S;

typedef struct tagIP6_ADDR_NP_MTUMSG
{
    ULONG     ulIfIndex;         /* Interface Index */
    ULONG     ulIPv6MTU;         /* IPv6 MTU */
}IP6_ADDR_NP_MTUMSG_S;

typedef struct tagIP6_ADDR_NOTIFICATION_MSG
{
    ULONG     ulIfIndex;                     /* Interface Index */
    IN6ADDR_S stIP6Addr;                     /* IPv6 Address */
    UCHAR     ucDuplicateLLAddr[MACADDRLEN]; /* 引起地址冲突的接口的mac地址 */
    BOOL_T    bMACChange;                     /* mac地址是否发生变化 */

    /* Modified by likaikun213099, 地址冲突告警需要指定vrf, 2014/10/16 */
    ULONG     ulVrfIndex;                    /* 接口所在VRF索引 */
}IP6_ADDR_NOTIFICATION_MSG_S;


typedef enum tagL3VPN6_EVENT
{
    L3VPN6_VRF_CREATE       = 1,           
    L3VPN6_VRF_DELETE       = 2,           
    L3VPN6_VRFINTF_CHANGE   = 3,

}L3VPN6_EVENT;

typedef struct   tagIP6AddrVrf_Msg
{
    USHORT usOldVrfIndex;
    USHORT usNewVrfIndex;
    ULONG  ulIfindex;
} IP6_Addr_Vrf_Msg;

typedef struct tagIpAddr6Filter
{
    ULONG ulIfIndex;
}IPADDR6_FILTER_S;

#ifdef  __cplusplus
}
#endif

#endif  /* _ADDR_PUBLIC_H */

