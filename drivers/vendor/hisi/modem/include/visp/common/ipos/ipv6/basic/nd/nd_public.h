/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              nd_public.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  IPBIRV100R003.IPv6.E001
*    Module Name :  Nd
*    Create Date :  2006/09/23
*    Author      :  Yinyuanbin
*    Description :  To define ND data structures used by external modules
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-09-23  Yinyuanbin    Created for including all public definitions in
*                             this file, for IPOSV1R1
************************************************************************/

#ifndef _ND_PUBLIC_H
#define _ND_PUBLIC_H

#ifdef  __cplusplus
extern "C"{
#endif  /* #ifdef  __cplusplus */

/*----------------------------------------------*
 *              Macros                          *
 *----------------------------------------------*/
#define IP6_ND_MAX_ENUM_VALUE           0xFFFFFFFF

/* Function return types */
#define ND_OK                           0
#define ND_ERR                          1
#define ND_NOFOUND                      2
#define ND_STOP                         3
#define ND_OWN_LINK_LOCAL               4

#define IP6_ND_TRUE                     0
#define IP6_ND_FALSE                    1

/* Neighbor Entry related macros */
#define IP6_ND_NON_STATIC_ENTRY         0
#define IP6_ND_STATIC_ENTRY             1


#define ND_NEIGHBORTABLE_LEN            1024
#define NB_ENTRY_PRODUCTINFO_SIZE       16

/* Operation code */
#define ND_FALSE                        0
#define ND_TRUE                         1
#define IP6_ND_CONFIG                   0
#define IP6_ND_UNDO_CONFIG              1

/* for NB entry display */
/* Changed as error code in enum */
/* #define IP6_ND_NO_NB_ENTRY              2 */

/* Min, Max, Avail values for Total NB entries */
#define IP6_ND_MAX_NB_TOTAL_NUM         4096
#define IP6_ND_MIN_NB_TOTAL_NUM         1024
#define IP6_ND_DEF_NB_TOTAL_NUM         1024

#define IP6_ND_MAX_NB_TOTAL_NUM_EXACT         1024*66 /*66K*/
#define IP6_ND_MIN_NB_TOTAL_NUM_EXACT         1
#define IP6_ND_DEF_NB_TOTAL_NUM_EXACT         1024

/* Description: Minimum value for total NB entries is added for PAF support of
   number of total NB entries per Interface */

/* Min, Max, Avail values for Interface NB entries */
#define IP6_ND_MAX_INTF_NB_NUM          4096
#define IP6_ND_DEF_INTF_NB_NUM          1024
#define IP6_ND_MIN_INTF_NB_NUM          32

/* Min, Max, Avail values for Interface NB entries */
#define IP6_ND_MAX_INTF_NB_NUM_EXACT          1024*40  /*40K*/
#define IP6_ND_DEF_INTF_NB_NUM_EXACT          1024
#define IP6_ND_MIN_INTF_NB_NUM_EXACT          1


/* Default Percentage Value for Interface NB entries */
#define IP6_ND_DEF_INTF_NB_PERCENT      100

#define IP6_ND_MIN_INTF_NB_PERCENT      4
#define IP6_ND_MAX_INTF_NB_PERCENT      100


/* Min, Max, Avail values for Total Static NB entries */
#define IP6_ND_MAX_TOT_STAT_NB_NUM      2048
#define IP6_ND_DEF_TOT_STAT_NB_NUM      512
#define IP6_ND_MIN_TOT_STAT_NB_NUM      50

#define IP6_ND_MAX_NB_NUM_EXACT_DEFAULT      1
#define IP6_ND_DEF_NB_NUM_EXACT_DEFAULT      1
#define IP6_ND_MIN_NB_NUM_EXACT_DEFAULT      1

/* Min, Max, Avail values for Total Static NB entries */
#define IP6_ND_MAX_TOT_STAT_NB_NUM_EXACT      2*1024  /*2K*/
#define IP6_ND_DEF_TOT_STAT_NB_NUM_EXACT      512
#define IP6_ND_MIN_TOT_STAT_NB_NUM_EXACT      1

/* Default Percentage Value for Total Static NB entries */
#define IP6_ND_DEF_TOT_STAT_NB_PERCENT  50

#define IP6_ND_MIN_TOT_STAT_NB_PERCENT  6
#define IP6_ND_MAX_TOT_STAT_NB_PERCENT  50

/* Begin :Changes for AC4D05067 by Anand on 20-02-2008*/
/* Min, Max, Avail values for Interface Static NB entries */
#define IP6_ND_MAX_NB_INTF_STATIC_NUM      2048
#define IP6_ND_DEF_NB_INTF_STATIC_NUM      256

#define IP6_ND_MIN_NB_INTF_STATIC_NUM      4

#define IP6_ND_MAX_NB_INTF_STATIC_NUM_EXACT      1024*2
#define IP6_ND_DEF_NB_INTF_STATIC_NUM_EXACT      256
#define IP6_ND_MIN_NB_INTF_STATIC_NUM_EXACT      1


/* Default Percentage Value for Interface Static NB entries */
#define IP6_ND_DEF_NB_INTF_STATIC_PERCENT  25

#define IP6_ND_MIN_NB_INTF_STATIC_PERCENT  10
#define IP6_ND_MAX_NB_INTF_STATIC_PERCENT  50

/* End :Changes for AC4D05067 by Anand on 20-02-2008*/

#define IP6_ND_NEXT_HOP_IS_ROUTER       2
#define IP6_ND_NEXT_HOP_IS_HOST         3


#define IP6_ND_ROUTER_INT_MIN_OVER      7

/* Added for SGSN callback notification */
#define ND_ADD     1
#define ND_DEL     2
#define ND_MOD     3

/* macros for filling/validating SPECS_RES_VALUE_S */
#define ND_CONTROLLED_BY_PAF_LCS      1
#define ND_CONTROLLED_BY_PAF          0

#define STALE_TIME            60 * 60 * 24 /*stale状态默认超时时间24小时*/
#define MAX_UNICAST_SOLICIT   3            /*发送单播NS请求最大次数*/

 /*----------------------------------------------*
  *              Enumerated Data Types           *
  *----------------------------------------------*/

/* Error types returned by ND Config API's */
typedef enum IP6_ND_ERR_Config
{
    /* Err types in case of when config of static NB*/
    IP6_ND_ERR_CFG_INVALID_LLCADDR = 5001,
    IP6_ND_ERR_CFG_ADDR_CONFLICT,
    IP6_ND_ERR_CFG_UNSPEC_ADDR,
    IP6_ND_ERR_CFG_MULTI_ADDR,
    IP6_ND_ERR_CFG_LOOP_ADDR,
    IP6_ND_ERR_CFG_INVALID_V4_COMP_ADDR,
    IP6_ND_ERR_CFG_INVALID_V4_MAPPED_ADDR,
    IP6_ND_ERR_CFG_PREF_LIFE_TIM_EXCEED,
    IP6_ND_ERR_CFG_UNSPEC_PREFIX,
    IP6_ND_ERR_CFG_LINK_LOCAL_PREFIX,
    IP6_ND_ERR_CFG_PREFIX_MULTI,
    IP6_ND_ERR_CFG_PREFIX_LOOP,
    IP6_ND_ERR_CFG_INVALID_V4_COMP_PREFIX,
    IP6_ND_ERR_CFG_INVALID_V4_MAPPED_PREFIX,
    IP6_ND_ERR_CFG_INVALID_PREFIX_LEN,
    IP6_ND_ERR_CFG_INVALID_LIFETIME,
    IP6_ND_ERR_INVALID_INPUT_USING_DEFAULT,
    IP6_ND_ERR_DAD_NOT_SUP_ON_INT,
    IP6_ND_ERR_NBMA_NOT_SUPPORTED,
    IP6_ND_ERR_LOOP_NOT_SUPPORTED,
    IP6_ND_SERIAL_NOT_SUPPORTED,
    IP6_ND_MAX_NB_PER_BOARD,
    IP6_ND_DYNAMIC_ENTRY,
    IP6_ND_ERR_CFG_INVALID_PREFIX_LEN_RANGE,

    
    IP6_ND_ERR_INVALID_NBENTRY_CTRL_PARAMS,
    IP6_ND_ERR_DEPENDENT_PAF_CONFLICT_LOAD_DEFAULT,

    /* IAS changes End */

    /* Begin : Changes for AC4D05470 by SurajR (72063) on 04-03-2008 */
    /* Description: Moved error code macros, as elements into enum
     *              IP6_ND_ERR_Config.
     */
    IP6_ND_TRUE_NEXT,
    IP6_ND_CLI_EXCEEDS_LIMIT,
    IP6_ND_PREFIX_DOESNOT_EXISTS,

    /* End : Changes for AC4D05470 by SurajR (72063) on 04-03-2008 */

    IP6_ND_ROUTER_INT_MINGTMAX,
    IP6_ND_ROUTER_INT_MINGTMAX_UNDO,
    IP6_ND_ROUTER_LIFE_TIME_LESS,
    
    IP6_ND_ERR_NA_NOT_SUP_ON_INT,
    
    IP6_ND_ERR_CFG_MAX = IP6_ND_MAX_ENUM_VALUE

}IP6_ND_ERR_CFG_E;

/* Operation code */
typedef enum tagIP6_ND_SETFLAG_E
{
    IP6_ND_FLAG_SET = 0,
    IP6_ND_FLAG_UNDOSET,

    IP6_ENUM_SETFLAG_PAD = IP6_ND_MAX_ENUM_VALUE

}IP6_ND_SETFLAG_E;

/* Error types returned by ND API's */
typedef enum tagIP6_ND_ERRORS_E
{
    IP6_ND_ERR_INPUTISNULL = 2,             /* 2 */
    IP6_ND_ERR_IFNETISNULL,                 /* 3 */
    IP6_ND_ERR_NDINFOISNULL,                /* 4 */
    IP6_ND_ERR_INVALIDVALUE,                /* 5 */
    IP6_ND_ERR_INVALIDFLAG,                 /* 6 */
    IP6_ND_ERR_GETTIME_FAIL,                /* 7 */
    IP6_ND_ERR_PREFIX_NOT_FOUND,            /* 8 */
    IP6_ND_ERR_PREFIX_NOT_PRESENT,          /* 9 */
    IP6_ND_ERR_NBENTRY_NOT_PRESENT,         /* 10 */
    IP6_ND_ERR_NBENTRY_NOT_PRESENT_ON_INTERF,/* 11 */
    IP6_ND_ERR_FAIL_TOGET_NBENTRY_IO,       /* 12 */
    IP6_ND_ERR_WAITLIST_SET_FAIL,           /* 13 */
    IP6_ND_ERR_WAITLIST_GET_FAIL,           /* 14 */
    IP6_ND_ERR_NO_IFNET_PRESENT,            /* 15 */

    IP6_ND_ERR_MALLOC_FAILED,               /* 16 Memory allocation failed */
    IP6_ND_ERR_WRITE_TO_QUEUE_FAILED,       /* 17 Queue write failed */
    IP6_ND_ERR_WRITE_EVENT_FAILED,          /* 18 Event write failed */
    IP6_ND_ERR_DEFRTR_ENTRY_NOTPRESENT,     /* 19 Default Rtr entry not present*/
    IP6_ND_ERR_NO_DEFRTR_ENTRY_PRESENT,     /* 20 Default Router list is empty */
    IP6_ND_ERR_PREFIXLST_ENTRY_NOTPRESENT,  /* 21 Prefix list entry not present */
    IP6_ND_ERR_MAX_PREFIX_ENTRY_REACHED,    /* 22 Maximum No of Prefix list
                                                entry reached */
    IP6_ND_ERR_NO_PREFIXLST_ENTRY_PRESENT,  /* 23 Prefix list is empty */
    IP6_ND_ERR_GBLPREFIX_ENTRY_NOTPRESENT,  /* 24 Global Prefix entry not present*/
    IP6_ND_ERR_NO_GBLPREFIX_ENTRY_PRESENT,  /* 25 Global Prefix entry is empty */
    IP6_ND_ERR_INVALID_PRE_TYPE,            /* 26 Invalid Prefix Address type */
    IP6_ND_ERR_FETCH_CTRL_BLK,              /* 27 Interface Control block does
                                                not exists */
    IP6_ND_ERR_MAX_DEFRTR_REACHED,          /* 28 Maximum No of Default Router
                                            entry reached */
    IP6_ND_ERR_IATYPE_NOT_SUPPORTED,        /* 29 IA type Given for Stateful
                                            address config is not supported*/
    IP6_ND_ERR_INVALID_ADDR_COUNT,          /* 30 Address count for Stateful addr
                                            config is not valid */
    IP6_ND_ERR_INVALID_SFADDR_CFG_TYPE,     /* 31 Stateful Address config operation
                                            type invalid */
    IP6_ND_ERR_NO_ADAPT_CALLBACKS_REG,      /* 32 DHCP6C Adaptor Call back function
                                            is not registered */
    IP6_ND_ERR_INVALID_ADDR_TYPE,           /* 33 Invalid Address type for config*/
    IP6_ND_ERR_INVALID_LIFETIME,            /* 34 Pref LT greater than Valid LT/
                                            Valid LT  0 for Address Add/update*/
    IP6_ND_ERR_DUPLICATE_ADDR_FOUND,        /* 35 Duplicate Address(es) found */
    IP6_ND_ERR_ADAPT_NOT_NOTIFIED,          /* 36 Host has not notified Adaptor */
    IP6_ND_ERR_INVALID_SFOTHER_PARAM_TYPE,  /* 37 Stateful Other Config parameter
                                            type invalid */
    IP6_ND_ERR_INVALID_SFADDR_NOT_USETYPE,  /* 38 Invalid Stateful Address Not
                                            usable reason type */
    IP6_ND_ERR_MBUF_CREATE_FAILED,          /* 39 MBUF Control packet creation
                                            failed */
    IP6_ND_ERR_UNALIGNED_ADDRESS,           /* 40 Un aligned address */
    IP6_ND_ERR_DESTCACHE_EMPTY,             /* 41 Destination Cache is empty */
    IP6_ND_ERR_DESTCACHE_MATCH_FAIL,        /* 42 Destination Cache match failed */
    IP6_ND_ERR_NO_LRUDESTCACHE_ENTRY,       /* 43 No LRU entry present for delete*/
    IP6_ND_ERR_END_OF_LIST,                 /* 44 End of list reached */
    IP6_ND_ERR_NO_NEXTHOP_FOUND,            /* 45 If Next hop determination fail */
    IP6_ND_ERR_WRITE_EVENT_TO_TASK_FAILED,  /* 46 Writing event to ND task failed*/
    IP6_ND_ERR_GET_FIRST_NODE_FAIL,         /* 47 Get First node failed */
    IP6_ND_ERR_WAITLIST_REGISTER_FAIL,      /* 48 Waitlist register failed */
    IP6_ND_ERR_WAITLISTGET_PARAM_FAIL,      /* 49 Get Params from waitlist failed*/
    IP6_ND_ERR_INVALID_WAITLIST_ID,         /* 50 Invalid waitlist ID */
    IP6_ND_ERR_INVALID_PREFIX_LEN_RANGE,    /* 51 Invalid Prefix Length */
    IP6_ND_ERR_PREF_LIFE_TIM_EXCEED,        /* 52 Invalid Lifetime */
    IP6_ND_ERR_SAME_CFG_VALUE,              /* 53 Config value is same as previous
                                            value */
    IP6_ND_ERR_INTERFACE_DOWN,              /* 54 IP6 Protocol is down for the
                                            interface*/
    IP6_ND_ERR_NO_NB_ENTRY,                 /* 55 No Neighbor entry present */

    
    IP6_ND_ERR_MAX_INF_STAT_NBENTRIES_REACHED,  /* 56 */
    IP6_ND_ERR_MAX_INF_NBENTRIES_REACHED,       /* 57 */


    /* Begin :Changes for AC4D05067 by Anand on 20-02-2008*/
    IP6_ND_ERR_MAX_STAT_NB_PER_BOARD_REACHED,   /* 58 */
    IP6_ND_ERR_SEMOP_ACQUIRELOCK_FAIL,          /* 59 */

    /* BEGIN : NDHOST SDV Defect AC4D05549, Anand */
    IP6_ND_ERR_WAITLIST_UNREGISTER_FAIL,    /* 60 Waitlist un-register failed */

    /* Changed by Anand, for adhering to Log check list */
    IP6_ND_ERR_TIMER_CREATE_FAIL,           /* 61 Timer Creation failed */
    IP6_ND_ERR_INVALIDIFPHYTYPE,            /* 62 If phy type is invalid */
    IP6_ND_ERR_GETTMTIMEFAIL,               /* 63*/
    IP6_ENUM_ERRORS_PAD = IP6_ND_MAX_ENUM_VALUE

}IP6_ND_ERRORS_E;

/* IAS operation */
typedef enum tagIP6_ND_IAS_OPERATION
{
    IP6_ND_IAS_NOTIFY_NBENTRY_ADD,     /* IAS NB entry addition operation */
    IP6_ND_IAS_NOTIFY_NBENTRY_DELETE,  /* IAS NB entry deletion operation */
    IP6_ND_IAS_NOTIFY_NBENTRY_MODIFY,  /* IAS NB entry modification operation */
    IP6_ND_IAS_NOTIFY_MAX,
    IP6_ND_IAS_NOTIFY_ULONG = IP6_ADDR_MAX_ENUM_VALUE
}IP6_ND_IAS_OPERATION_E;


/*----------------------------------------------*
 *              Data Structures                 *
 *----------------------------------------------*/

/* Neighbor Solicitation packet Structure */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagND_NS
{
    ULONG       ulIfIndex;        /*接口索引*/
    UCHAR       ucDADFlag;        /*DAD报文标记*/
    UCHAR       ucOptionFlag;     /*是否带选项标记*/
    USHORT      usPad;
    IN6ADDR_S   stDstAddr;        /*目的地址*/
    IN6ADDR_S   stSrcAddr;        /*源地址*/
    IN6ADDR_S   stTgtAddr;        /*目标地址*/
}ND_NS_S;

/* The structure is added for IAS. Structure contains VLAN ID and Port index */
typedef struct tagND_PKT_CTLPARAM
{
    ULONG    ulPortIndex;  /* Receive Port */
    USHORT   usVlanId;     /* Receive VlanId */
    UCHAR    ucReserve[2];
}ND_PKT_CTLPARAM_S;

/*邻居项数据结构*/
/* HCC error: Structure having more than 5 elements - Obvious */
typedef  struct    tagNeighborEntry
{
    ULONG       ulIfnetIndex;    /*接口索引*/
    ULONG       ulVLinkIndex;
    IN6ADDR_S   stIPv6Addr;     /*邻居的IPv6地址*/

    /*when the NS has no SLLA info, we should create the entry and fill the
    entry all the related info especially this field. We can put the NS target
    address to this field. After sending NS and receiving the NA to get the
    SLLA of the source node, we can find this entry according this field,
    then send the NA and delete the target address in the entry. */

    IN6ADDR_S    stNAIPv6Addr;

    UCHAR        ucLLAddr[MACADDRLEN];    /*邻居的链路地址*/
    UCHAR        ucLLAddrFlag;            /*接口有无链路地址的标志*/
    UCHAR        ucIsRouter;              /*邻居的路由器标志*/
    UCHAR        ucState;                 /*邻居状态*/
    UCHAR        ucIsStaticEntry;
    UCHAR        ucPad;
    UCHAR        ucNoPpiDelNDFlag;        /*不下发PPI 删除ND的标记位，产品定制场景*/
    ULONG        ulReachableTimeElapsed;

    /* added for MIB timestamp Net To Media */
    ULONG        ulTimeStamp;

    /* ULONG           ulExpire;                状态变化预期时间*/
    ULONG              ulExpireHigh;   /* High ULONG of millisecond curr time*/
    ULONG              ulExpireLow;    /* Low ULONG of millisecond curr time*/

    ND_NS_S      stNSInfor;       /*要发送的NS内容*/

    struct tagNeighborEntry *pstNext;         /*下一个*/
    struct tagNeighborEntry *pstPrevious;     /*上一个*/

    VOID        *pND_Data;/* To store the MBUF_S and start address resolution*/

    ULONG       aulProductInfo[NB_ENTRY_PRODUCTINFO_SIZE];    /* 产品信息 */
    USHORT      usNeedNS;       /*进行邻居不可达检测需要发送的次数*/

    /* Control parmeters (VLAN ID and Port index) using by IAS product */
    USHORT   usVlanId;     /* Receive VlanId */
    ULONG    ulPortIndex;  /* Receive Port */
    ULONG    ulVrfIndex;


    UCHAR   *pucRdxExtNode;

    ULONG        ulCreatedTimeStamp;             /* 表项创建的时间 */

}ND_NBENTRY_S;

/* RFC 2461: => Prefix Option fields
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |     Type      |    Length     | Prefix Length |L|A| Reserved1 |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                         Valid Lifetime                        |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                       Preferred Lifetime                      |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                           Reserved2                           |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                                                               |
      +                                                               +
      |                                                               |
      +                            Prefix                             +
      |                                                               |
      +                                                               +
      |                                                               |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


*/

/* Moved to External include */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct  tagND_Prefix
{
    ULONG       ulIfnetIndex;       /*接口索引*/
    ULONG       ulLen;              /*前缀选项总长度*/
    ULONG       ulValidTime;        /*前缀有效生命周期*/
    ULONG       ulPreferredTime;    /*前缀首选生命周期*/
    UCHAR       ucLFlag;            /*OnLink标志*/
    UCHAR       ucAFlag;
    USHORT      usPad;              /*Autoconfig标志*/

    /* The count is maintained as there are many addresses with same
    prefix with different interface ids, AddrMgt will notify ND for all, hence
    we maintain one prefix, and when count is 0, delete the prefix. */

    ULONG                   ulCount;
    IN6ADDR_S               stPrefix;       /*前缀*/
    struct tagND_Prefix    *pstPrevious;    /*上一个*/
    struct tagND_Prefix    *pstNext;        /*下一个*/
    ULONG    ulStatus;
}ND_PREFIX_S;

/* Moved to External Include  */

#ifndef _NDTIMER_
#define _NDTIMER_

/*ND模块定时器的数据结构*/
typedef  struct tagND_Timer
{
    ULONG   ulTimerType;
    ULONG   ulTimerID;
    ULONG   ulIfIndex;
    ULONG   ulReserved;

}ND_TIMER_S;
#endif


/*重复地址检测数据结构*/
/* HCC error: Structure having more than 5 elements - Obvious */
typedef  struct    tagDAD
{
    ULONG              ulIfIndex;               /*接口索引*/
    IP6IFADDR_S        *pstIp6IfAddr;           /*待检测单播地址*/
    ULONG              ulDADAttempt;            /*待发送邻居请求的次数*/
    /* Modified by guojianjun178934, IPV6 DAD探测定时器修改方案变更, 2014/2/12   问题单号:S-IP-003-PUBLIC-FUNC-005  */
    ULONG              ulExpireHigh;            /*下一次发送邻居请求的预期时间*/
    ULONG              ulExpireLow;             /*下一次发送邻居请求的预期时间*/
    /*End of Modified by guojianjun178934, 2014/2/12   问题单号:S-IP-003-PUBLIC-FUNC-005  */
    struct    tagDAD    *pstTotalNext;          /*总链表下一个*/
    struct    tagDAD    *pstTotalPrevious;      /*总链表上一个*/
    struct    tagDAD    *pstIfNext;             /*接口链表下一个*/
    struct    tagDAD    *pstIfPrevious;         /*接口链表上一个*/
}DAD_S;


/*路由器宣告消息内容数据结构*/
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct   tagND_RA
{
    ULONG          ulIfnetIndex;          /*接口索引*/
    UCHAR          ucSendRAFlag;        /*发送路由器宣告标志*/
    UCHAR          ucMFlag;              /* M标志位 */
    UCHAR          ucOFlag;              /* O标志位 */
    UCHAR          ucRtLifetimeFlag;      /*路由器生存期为0标记，如果值为1
    表示路由器生命周期为0，如果值为0表示路由器生命期为设定值*/
    ULONG          ulRtlifetime;           /* 路由器生存期 */
    ULONG          ulReachable;          /*可达时间*/
    ULONG          ulRetrans;             /*重传时间*/
    ULONG          ulRAIntervalMax;      /*发送路由器宣告的时间间隔的最大值*/
    ULONG          ulRAIntervalMin;      /*发送路由器宣告的时间间隔的最小值*/
    ULONG          ulTimerID;            /*RA定时器ID*/
    ULONG          ulLastSendTime;       /*上次发送路由器宣告的时间*/
    ULONG          ulTime;               /*下次发送路由器宣告的时间*/

    /*  The address structures are added to support unicast RA send messages
        and the CLI prefix are now being supported */

    IN6ADDR_S      stDstAddr;
    ND_PREFIX_S    *pstCliPrefix;            /*要发送的前缀头指针*/


    ND_PREFIX_S    *pstPrefix;            /*要发送的前缀头指针*/

    ULONG          ulFlag;                /*用来标识RA中是否要进行默认配置*/

    IN6ADDR_S      stIPv6AddrDel;        /*RA source address has been deleted,
                                            but RA has not been sent*/
    IN6ADDR_S      stIPv6AddrAdd;       /*RA source address has been added,
                                            but RA has not been sent*/

    /* All are used only in case of sending unicast RA */
    ULONG          ulSendUnicastRA;
    IN6ADDR_S      stUnicastAddr;
    ULONG          ulNextMulticastRATime;

    BOOL_T         usCliPrxNum;            /*前缀链表中的前缀个数*/
    BOOL_T         usPrxNum;            /*前缀链表中的前缀个数*/

    UCHAR          ucFinalRa;
    UCHAR          ucPad[2];

    /*Reason: This flag has been added to check whether Router-lifetime is
      user-configured or default */
    UCHAR ucIsRtLifeTimeConfigured;

    ULONG          ulMinConfig;
    ULONG          ulInitAdver;    /* Value to keep track of number of initial
                                     advertisements */
}ND_RA_S;


/* ND Info Structure */
/* HCC error: Structure having more than 5 elements - Obvious */
/* IP6_ND_HOSTPARAMS_S pointer will not be used in Router but still the
structure is defined, Otherwise it has to be declared as VOID and in all
ND Host code it has to be typecasted. */
typedef struct tagNDInfo
{
    ULONG          ulIfIndex;              /*接口索引*/
    UCHAR          ucInterfacePhyState;    /*接口物理状态*/
    UCHAR          ucInterfaceState;       /*接口状态*/
    UCHAR          ucLLAddr[MACADDRLEN];   /*接口的链路地址*/
    UCHAR          ucLLAddrFlag;           /*接口有无链路地址的标志*/
    UCHAR          ucNDSpecialProxyFlag;   /*接口使能特殊ND代理标记*/
    UCHAR          ucPad[2];
    ULONG          ulNSInterval;           /*发送邻居请求的时间间隔*/
    ULONG          ulReachableTime;        /*邻居项可达时间*/
    ULONG          ulTimerID;              /*邻居项定时器ID*/
    ULONG          ulNBForceDelTimerID;    /*This timer will be started to
                                            clean the NB cache when it reaches
                                            the critical value*/
    ND_TIMER_S     stNDNBTimerMsg;
    ND_NBENTRY_S   *pstNBEntry;            /*邻居项头指针*/
    DAD_S          *pstDAD;                /*接口DAD链表头指针*/
    ND_RA_S        stRAInfo;               /* RA configuration information */

    ULONG          ulNBNum;                /*此接口中邻居项的个数*/
    ULONG          ulTotalStatic;


    /* Description: Static array is changed to pointer which can be allocated
       dynamically because maximum number of NB entries per Interface is now
       supporting by PAF */


    ULONG          ulDADAttempt;        /*重复地址检测时发送邻居请求的次数*/

    ULONG          ulLastTimeNASentTimeStamp;

    /* Begin : Changes for AC4D05067 by Anand on 20s-02-2008 */
    ULONG          ulNonDeleteNBEntries; /* Non Deletable NB entries */

    /*Added by guojianjun178934,  接口状态变化或MAC地址变化主动发送通告NA报文, 2014/1/26   问题单号:S-IP-005-PUBLIC-FUNC-003 */
    SLL_S           *pstNARoot;
    ND_TIMER_S      stNDNATimerMsg;
    ULONG           ulNATimerID;      /*接口主动通告NA报文定时器ID*/
    ULONG           ulNAInterval;     /*NA报文重传时间间隔*/
    ULONG           ulNAMinDelay;     /*首个NA报文的最小发送时延*/
    ULONG           ulNAMaxDelay;     /*首个NA报文的最大发送时延*/
    ULONG           ulMaxNACount;     /*NA报文最大发送次数*/
    /* End of Added by guojianjun178934, 2014/1/26   问题单号:S-IP-005-PUBLIC-FUNC-003 */

    /*Added by guojianjun178934, 【检视问题单---DAD告警优化】产品定期发送地址冲突检测的NS报文，如果收到了NA我们需要启动DAD探测, 2014/2/21   问题单号:DTS2014021206259  */
    SLL_S           *pstDADExtRoot;
    ND_TIMER_S      stNDDADExtTimerMsg;
    ULONG           ulDADExtTimerID;      /*接口执行DAD扩展定时器ID*/
    /* End of Added by guojianjun178934, 2014/2/21   问题单号:DTS2014021206259  */
    
    VOID           *pvHostParams;  /* ND Host parameters */

    VOID          *pvNDRootNode;  /* Root node for the radix tree */

}NDINFO_S;


/* New structure defined to send info to Shell for Build Run and Sync*/
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagND_GETFROMCORE
{
    ULONG         ulReachable;
    ULONG         ulAdvReachable;
    ULONG         ulNSInterval;
    ULONG         ulRAIntervalMax;
    ULONG         ulRAIntervalMin;
    ULONG         ulRAMinConfig;
    ULONG         ulRtlifetime;
    UCHAR         ucSendRAFlag;
    UCHAR         ucMFlag;
    UCHAR         ucOFlag;
    UCHAR         ucCurHopLimit;
    ND_PREFIX_S   *pstCliPrefix;
    ND_PREFIX_S   *pstPrefix;
    ULONG         ulDADAttempt;
    UCHAR         ucIsRtLifeTimeConfigured;
    UCHAR         ucRes[3];
} ND_GETFROMCORE_S;

/* Prefix Table */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagIP6_ND_PrefixTbl
{
    ULONG          ulIfIndex;
    IN6ADDR_S      stIpv6AddressPrefix;
    ULONG          ulIPv6AddrPrefixLength;
    BOOL_T         ipv6AddrPrefixOnLinkFlag;
    BOOL_T         ipv6AddrPrefixAutonomousFlag;
    ULONG          ulIPv6AddrPrefixAdvPreferredLifetime;
    ULONG          ulIPv6AddrPrefixAdvValidLifetime;
}IP6_ND_PrefixTbl_S;

/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagIP6_ND_Net2MediaTbl
{
    ULONG          ulIfIndex;
    IN6ADDR_S      stipv6NetToMediaNetAdd;
    UCHAR          ucMacAddr[MACADDRLEN];
    BOOL_T         usipv6NetToMediaValid;
    ULONG          ulipv6NetToMediaType;
    ULONG          ulipv6IfNetToMediaState;
    ULONG          ulipv6IfNetToMediaLastUpdated;

}IP6_ND_Net2MediaTbl_S;


/* SGSN Stub call back functions */
typedef struct tagIP6_ND_SGSN_CALLBACK_FUNC
{
    /* SGSN CallBacks */
    ULONG (*pfPPI_IPV6_OpIpv6Route)(VOID * pvRtMsg);
    ULONG (*pfPPI_IPV6_OpIpv6Neighbor)(UCHAR ucOpType, VOID* pstNBEntry,
                                                    ULONG *pulVlinkIndex);
    ULONG (*pfPPI_IPV6_NDNeedToLookUp)(MBUF_S* pstMbuf);

}IP6_ND_SGSN_CALLBACK_FUNC_S;

/* Neighbor Entry */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef  struct    tagNeighborEntryInfo
{
    ULONG       ulIfnetIndex;
    ULONG       ulVLinkIndex;
    IN6ADDR_S   stIPv6Addr;                /*邻居的IPv6地址*/
    UCHAR       ucLLAddr[MACADDRLEN];      /*邻居的链路地址*/
    UCHAR       ucLLAddrFlag;              /*接口有无链路地址的标志*/
    UCHAR       ucIsRouter;                /*邻居的路由器标志*/
    UCHAR       ucState;                   /*邻居状态*/
    UCHAR       ucIsStaticEntry;
    USHORT      usPad;
    ULONG       ulReachableTimeElapsed;
    ULONG       ulTimeStamp;
    ULONG       ulExpireHigh;
    ULONG       ulExpireLow;
    ULONG       ulVrfIndex;

    /* IAS changes Start :
            This field is using by IAS product to display Vlan-ID and Port name.
    */
    ND_PKT_CTLPARAM_S stNDCtrlParam;       /* Control parameters (vlan-id,
                                            port index) */

    /* IAS changes End */

}ND_NBENTRY_INFO_S;

/* Structure using as Static neighbor entry addition API argument */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef  struct    tagStaticNeighborEntry
{
    ULONG       ulIfnetIndex;   /* Interface index */
    IN6ADDR_S   stIn6Addr;      /* IPv6 address */

    /* This field is using by IAS product */
    /* Control parameters (vlan-id, port index) */
    ULONG       ulPortIndex;    /* Receive Port */
    USHORT      usVlanId;       /* Receive VlanId */

    /* LLA size is taken as 6 bytes, based on the change in size padding needs
       to add for 4-byte allignment */
    UCHAR       aucLLAddr[MACADDRLEN];    /* Link layer address - 6 Bytes */
}ND_STATIC_NBENTRY_S;


/* NB update should notify VISP socket for Head cache */
typedef struct tagIP6_ND_SOCK_CALLBACK_SET_S
{
    VOID (*pfHeadCache_Event) (ULONG ulEventType, VOID *pData);
}IP6_ND_SOCK_CALLBACK_SET_S;

typedef struct tagIP6_ND_FLOW_CALLBACK_SET_S
{
    ULONG (*pfIP6_ND_Incoming_Flow_Callback)(ULONG ulIfIndex, VOID *pvMBuf);
}IP6_ND_FLOW_CALLBACK_SET_S;


/****************************************************************************
 *                  Nd_public.h Changes for ND Host Feature support         *
 ****************************************************************************/
/***********/
/* Defines */
/***********/



/* MAX, MIN Params for ND Host */

/* Default Router list entries per interfaces */
#define IP6_ND_MAX_DEFRTR_PER_INTF              4
#define IP6_ND_MIN_DEFRTR_PER_INTF              2
#define IP6_ND_DEF_DEFRTR_PER_INTF              4

/* Prefix list entries per interfaces */

#define IP6_ND_MAX_PREFLIST_PER_INTF            16
#define IP6_ND_MIN_PREFLIST_PER_INTF            1
#define IP6_ND_DEF_PREFLIST_PER_INTF            16

/* Destination Cache entries */
#define IP6_ND_MAX_DESTCACHE_ENTRY              64
#define IP6_ND_MIN_DESTCACHE_ENTRY              1
#define IP6_ND_DEF_DESTCACHE_ENTRY              64

/* Macro for FIB Route notification type */
/* TODO to be moved to FIB public */
#define SIFB6_EVENTNOTIFY_ROUTE_ADD             0x01
#define SIFB6_EVENTNOTIFY_ROUTE_DELETE          0x02

/* Used to return invalid hop limit in Global Hop Limit, bcz in Host
the hop limit is maintained per interface, So the Global GetHopLimit API
 will return this value */
#define IP6_ND_INVALID_HOP_LIMIT                0xFF

/* Neighbor Entry States */
#define ND_STATE_INVALID                0
#define ND_STATE_INCOMPLETE             1
#define ND_STATE_REACHABLE              2
#define ND_STATE_STALE                  3
#define ND_STATE_DELAY                  4
#define ND_STATE_PROBE                  5

/* Macros to indicate the reset type values */
#define IP6_ND_RESET_ALL                1
#define IP6_ND_RESET_STATIC             2
#define IP6_ND_RESET_DYNAMIC            3

#define IP6_ND_SPECIAL_PROXY_DISABLE         0
#define IP6_ND_SPECIAL_PROXY_ENABLE          1

#define IP6_ND_SPECIAL_PROXY_ACTIVE          0x01
#define IP6_ND_SPECIAL_PROXY_INACTIVE        0x02 

/*********/
/* Enums */
/*********/

/* Identity Association Type - Temporary/Non-temporary Addresses */
typedef enum tagIP6_ND_IAType
{
    IP6_ND_IA_TYPE_NA = 0,      /* Non Temporary IA */
    IP6_ND_IA_TYPE_TA,          /* Temporary IA */
    IP6_ND_IA_MAX,
    IP6_ND_IA_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_IATYPE_E;

/* Stateful address configuration operation type */
typedef enum tagIP6_ND_StatefulCfg_OptType
{
    IP6_ND_STFULCFG_ADDITION = 0,
    IP6_ND_STFULCFG_DELETION,
    IP6_ND_STFULCFG_LIFETIMEUPDATION,
    IP6_ND_STFULCFG_MAX,
    IP6_ND_STFULCFG_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_STATEFULCFG_OPTTYPE_E;

/* Notification type about presence of DHCPv6 Server to Client Adaptor */
typedef enum tagIP6_ND_DHCPV6SERVER_AVAIL
{
    /* DHCPv6 Server Available for Address and Other configuration */
    IP6_ND_SA_NOTIFY_MFLAG = 0,

    /* DHCPv6 Server Available only for Other configuration */
    IP6_ND_SA_NOTIFY_OFLAG,

    /* Absence of Router in link */
    IP6_ND_SA_NOTIFY_NO_RA,
    IP6_ND_SA_NOTIFY_MAX,
    IP6_ND_SA_NOTIFY_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_DHCPV6SERVER_AVAIL_E;

/* Notification to Client Adaptor about Non usability of the Stateful Address */
typedef enum tagIP6_ND_Notusable_Reason
{
    /* The Address provide is not unique on the link */
    IP6_ND_NOTUSE_ADDR_DUPLICATE = 0,

    /* Release the Address */
    IP6_ND_NOTUSE_RELEASE,

    /* The statefull address provided is alreay present in the systme (same
    interface or different interface) */
    IP6_ND_NOTUSE_ADDRCONFLICT,

    /* Maximum number of Address configuration has reached */
    IP6_ND_NOTUSE_MAX_ENTRY_REACHED,

    /* Invalid address (Address Type/Life time) */
    IP6_ND_NOTUSE_INVALID_ADDRESS,

    /* Address entry not present */
    IP6_ND_NOTUSE_ADDRESS_NOTPRESENT,

    /* Invalid Interface Index in IA Descriptor */
    IP6_ND_NOTUSE_INTF_NOTPRESENT,

    /* IA type in IA descriptor is not supported  */
    IP6_ND_NOTUSE_IATYPE_NOTSUPPORTED,

    /* SRM Table Space is Full */
    IP6_ND_NOTUSE_SRM_TBL_FULL,

    /* Invalid Address Info */
    IP6_ND_NOTUSE_INVALID_ADDRINFO,

    /* Maximum No of Address entry reached */
    IP6_ND_NOTUSE_MAXADDR_ENTRY_REACHED,

    IP6_ND_NOTUSE_MAX,
    IP6_ND_NOTUSE_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE

}IP6_ND_NOTUSABLE_REASON_E;


/* Other configuration Information type enum */
typedef enum tagIP6_ND_OTHERCONFIGPARAMTYPE
{
    IP6_ND_MTU = 0,         /* IPv6 Link MTU */
    IP6_ND_HOPLIMIT,        /* Hop limit */
    IP6_ND_BASEREACH_TIME,  /* Base Reachable time value */
    IP6_ND_NSRETRANS_TIME,  /* NS Retransmission time value */
    IP6_ND_OTHERCFG_MAX,
    IP6_ND_OTHERCFG_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_OTHERCFGPARAMTYPE_E;


/* Enum to store different type of Source of Route */
typedef enum tagND_ROUTESOURCE
{
    IP6_ND_ROUTSRC_SFIB = 0,            /* Source of Route from FIB */
    IP6_ND_ROUTSRC_PREFIX_LIST,         /* Source of Route from Prefix List */
    IP6_ND_ROUTSRC_DEF_ROUTER_LIST,     /* Source of Route from Def Rtr list*/
    IP6_ND_ROUTSRC_OWN_ADDRESS,         /* Dest. is own address */
    IP6_ND_ROUTSRC_MAX,
    ND_ROUTSRC_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}ND_ROUTESOURCE_E;

/* Default Router entry state enum */
typedef enum tagIP6_ND_DefRtrState
{
    /* The Router's NB cache entry is in a state other than INCOMPLETE*/
    IP6_ND_DR_ST_REACHABLE = 0,

    /* The Router's NB cache entry is in INCOMPLETE
    state or there is no corresponding entry in the NB cache.*/
    IP6_ND_DR_ST_NOT_REACHABLE,
    IP6_ND_DR_ST_MAX,
    IP6_ND_DR_ST_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_DEFRTRSTATE_E;

/* Configuration Operation */
typedef enum tagIP6_ND_CFG_OPT
{
    IP6_ND_CFG_OPT_DISABLE = 0, /* Disable Operation */
    IP6_ND_CFG_OPT_ENABLE,      /* Enable Operation */
    IP6_ND_CFG_MAX,
    IP6_ND_CFG_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_CFG_OPT_E;


/****************************************************************************/
/* Structures */

/* Get all Interface related Parameters */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagIP6_ND_GetHostParams
{
    ULONG         ulBaseReachTime;      /* Base Reachable Time */
    ULONG         ulReachTime;          /* Random Reachable time */
    ULONG         ulNSRetransInterval;  /* NS Retransmission Interval */
    ULONG         ulDADAttempt;         /* Number of DAD NS to be sent */
    ULONG         ulCurHopLimit;        /* Current Hop limit */
    ULONG         ulLinkMTU;            /* Link MTU value */
    UCHAR         ucStoredMandOFlag;    /* Managed and Other Flag bitMap*/
    UCHAR         ucPad[3];             /* Padding*/
}IP6_ND_GETHOSTPARAMS_S;


/* Contain the various attributes of the added/deleted route information */
/* HCC error: Structure having more than 5 elements - Obvious */
/* Note: Prefix length is ULONG, to avoid typecast (Radix tree)- Obvious */
typedef struct tagSFIB6_ROUTEINFO
{
    ULONG   aulDestination[4];      /* Destination Address */
    ULONG   aulNextHop[4];          /* Next Hop Address */
    ULONG   ulOutIfIndex;           /* Outgoing Interface */
    ULONG   ulATIndex;              /* AT Index */
    ULONG   ulFlags;                /* Route Flags */
    ULONG   ulProtocol;             /* Route Protocol */
    ULONG   ulPrefixLen;            /* Prefix Length  */

}SFIB6_ROUTEINFO_S;


/* Default Router List Structure - Used in Display */
typedef struct tagND_DefRouter_Info
{
    IN6ADDR_S stIPv6Addr;           /* Default Router Address */

    /* Time stamp updated when Router entry is newly created or lifetime
    of existing entries are updated */
    ULONG ulLastChangeTime;

    /* Default Router State (PROBABLY_REACHABLE/NOT_REACHABLE)*/
    IP6_ND_DEFRTRSTATE_E enState;
    USHORT usLifetime;            /* Router lifetime */
    UCHAR aucPad[2];              /* Padding */

}IP6_ND_DEFROUTER_INFO_S;


/* Interface Level Prefix List Structure - Used in Display */
typedef struct tagND_IntfPrefix_Info
{


    IN6ADDR_S stPrefix;          /* Prefix */
    ULONG ulValidLifetime;       /* Valid Lifetime of Prefix */

    /* Time stamp when the Prefix entry created/updated its lifetime */
    ULONG ulLastChangeTime;
    UCHAR ucPrefixLen;          /* Prefix Length */
    UCHAR aucPad[3];            /* for padding */
}IP6_ND_INTFPREFIX_INFO_S;


/* Destination Cache Structure - Used in Display */
typedef struct tagND_DestCache_Info
{
    IN6ADDR_S   stDestAddr;         /* Destination Address */
    IN6ADDR_S   stNextHopAddr;      /* Next hop Address */
    ULONG       ulTimeStamp;        /* Time Stamp to Force Delete entries */
    ULONG       ulOGIfnetIndex;     /* Outgoing interface index */
    ND_ROUTESOURCE_E  enSRCRoute;   /* Source of Route */

}IP6_ND_DESTCACHE_INFO_S;


/* IA Descriptor */
typedef struct tagIP6_ND_IADESC_S
{
    ULONG           ulIfindex;  /* IFNET index */
    IP6_ND_IATYPE_E enIAType;    /* IA type */
    ULONG           ulIAID;     /* IAID */
}IP6_ND_IADESC_S;


/* Address with Lifetime values */
typedef struct tagIP6_ND_IN6ADDRWITHTIME
{
    IN6ADDR_S stAddress;           /* Address in IA */
    ULONG ulPreferedLifeTimeValue;  /* Preferred life time of address */
    ULONG ulValidLifeTimeValue;     /* Valid life time of address */
}IP6_ND_IN6ADDRWITHTIME_S;

/* DHCPv6 Client Adaptor Call back functions */
typedef struct tagIP6_ND_DHCP6CAdapt_CallBack
{

    /* Callback to inform the presence of a stateful server on the link for
    Address/Other configuration or to inform the Router Discovery Failure. */
    ULONG (*pfIP6_ND_NotifyServerAvailability)(ULONG ulIfnetIndex,
                                IP6_ND_DHCPV6SERVER_AVAIL_E eNotifyType);

    /* Callback to Notify Client Adaptor about Non usability of the Stateful
       Address */
    ULONG (*pfIP6_ND_DHCP6CAdaptAddrNotUsable)(IP6_ND_IADESC_S *pstIADesc,
            IP6_ND_IN6ADDRWITHTIME_S *pstAddress,
            IP6_ND_NOTUSABLE_REASON_E eType);

}IP6_ND_DHCP6CADAPT_CALLBACK_S;


/* Other configuration Information for Stateful autoconfiguration protocol */
typedef struct tagIP6_ND_OtherConfigParams
{
    ULONG ulIfIndex;            /* Interface index */
    ULONG ulValue;              /* Other Config Value */
    IP6_ND_OTHERCFGPARAMTYPE_E enParamType;
}IP6_ND_OTHERCFGPARAMS_S;

typedef struct tagIP6_ND_NP_MSG
{
    ULONG     ulIfIndex;             /* Interface Index */
    IN6ADDR_S stIP6Addr;             /* IPv6 Address */
    UCHAR     ucLLAddr[MACADDRLEN];  /* MAC Address */
    UCHAR     ucType;                /* Static / Dynamic,
                                        Possible Values :
                                        IP6_ND_NON_STATIC_ENTRY
                                        IP6_ND_STATIC_ENTRY
                                      */
    UCHAR     ucState;               /* NB Entry State :
                                        Possible Values :
                                        ND_STATE_INCOMPLETE
                                        ND_STATE_REACHABLE
                                        ND_STATE_STALE
                                      */
    USHORT   usVlanId;     /* VlanId */
    USHORT   usPad;         /* Padding */
    ULONG    ulVrfIndex;
}IP6_ND_NP_MSG_S;


typedef struct tagIP6_ND_NP_PL_MSG
{
    ULONG     ulIfIndex;             /* Interface Index */
    IN6ADDR_S stIP6Prefix;           /* IPv6 Prefix */
    ULONG     ulPrefixLen;           /* Prefix Length */
}IP6_ND_NP_PL_MSG_S;

typedef struct tagIP6_ND_NP_DRL_MSG
{
    ULONG     ulIfIndex;             /* Interface Index */
    IN6ADDR_S stIP6Addr;             /* IPv6 Prefix */
    ULONG     ulState;               /* Default Router State */
                                     /* Possible Values :
                                        IP6_ND_DR_ST_REACHABLE,
                                        IP6_ND_DR_ST_NOT_REACHABLE
                                     */
}IP6_ND_NP_DRL_MSG_S;


typedef struct tagIP6_ND_NP_DC_MSG
{
    ULONG     ulIfIndex;             /* Interface Index */
    IN6ADDR_S stDestIP6Addr;         /* Destination IPv6 address */
    IN6ADDR_S stNextHopIP6Addr;      /* Next Hop IPv6 address */
}IP6_ND_NP_DC_MSG_S;


typedef enum tagIP6_ND_NBSEARCH_TYPE
{
    IP6_ND_NBSEARCH_BY_L3IF = 0, 
    IP6_ND_NBSEARCH_BY_L2PORT,     
    IP6_ND_NBSEARCH_BY_RDX,
    IP6_ND_NBSEARCH_MAX = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_NBSEARCH_TYPE_E;

typedef struct tagIP6_ND_SPECIAL_PROXY_PARA
{
    ULONG     ulOutIfIndex;      /*ND代理绑定的实际出接口索引*/
    IN6ADDR_S stIP6Addr;         /*被代码的IPv6地址*/
}IP6_ND_SPECIAL_PROXY_PARA_S;

typedef ULONG ( * gpfIP6NDSpecialNDProxy) (IP6_ND_SPECIAL_PROXY_PARA_S *pstSpecNDPrxyPara);
typedef ULONG ( * gpfIP6GetDADProxyIfIndex) (ULONG ulVrfIndex, IN6ADDR_S *pstIP6Addr, ULONG *pulIfIndex);

typedef struct tagTCPIPNDFilter
{
    ULONG ulIfIndex;
}TCPIP_ND_FILTER_S;

typedef  struct   tagTCPIPNeighborEntryInfo
{
    ULONG       ulIfnetIndex;
    IN6ADDR_S   stIPv6Addr;                /* 邻居的IPv6地址        */
    UCHAR       ucLLAddr[MACADDRLEN];      /* 邻居的链路地址        */
    UCHAR       ucLLAddrFlag;              /* 接口有无链路地址的标志*/
    UCHAR       ucIsRouter;                /* 邻居的路由器标志      */
    UCHAR       ucState;                   /* 邻居状态              */
    UCHAR       ucIsStaticEntry;
    USHORT      usVlanId;                  /* Receive VlanId        */
    ULONG       ulCreatedTime;             /* 表项创建到现在的相对时间 */
    ULONG       lLeftExpireTime;           /* 老化剩余时间          */
    ULONG       ulVrfIndex;                /* vrf索引               */
    ULONG       ulReserv[6];
}TCPIP_ND_NBENTRY_INFO_S;

typedef struct tagTCPIPIfNDFilter
{
    ULONG ulIfIndex;      /*按接口过滤*/
}TCPIP_IF_ND_FILTER_S;

typedef struct tagTCPIPIfNDInfo
{
    ULONG ulIfIndex;      /*接口索引*/
    ULONG ulDADAttempt;   /*DAD探测次数*/
    ULONG ulNSInterval;   /*NS 发送间隔*/
    ULONG ulNAInterval;   /*NA发送间隔*/
    ULONG ulNAAttempts;   /*NA 发送次数*/
    ULONG ulReachableTime;/*可达时间*/
    ULONG ulStaticNeigborNums;  /*静态邻居个数*/
    ULONG ulDynamicNeigborNums; /*动态邻居个数*/
    ULONG ulReserv[8];    /*预留字段*/
}TCPIP_IF_NDINFO_S;

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* _ND_PUBLIC_H*/
