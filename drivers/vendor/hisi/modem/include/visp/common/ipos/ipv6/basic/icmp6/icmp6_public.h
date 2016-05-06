/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              icmp6_public.h
*
*    Project Code:  IPBIRV1R2
*    Module Name :  ICMP6
*    Create Date :  2006/09/23
*    Author      :  Yinyuanbin
*    Description :  To define ICMP6 data structures used by external modules
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-09-23  Yinyuanbin    Created for including all public definitions in
*                             this file, for IPOSV1R1
************************************************************************/
#ifndef _ICMP6_PUBLIC_H
#define _ICMP6_PUBLIC_H

#ifdef  __cplusplus
extern "C"{
#endif

/***********************************************************************/
/*                             Macro Defination                        */
/***********************************************************************/
#ifndef IPPROTO_ICMPV6
#define IPPROTO_ICMPV6     58        /* UDP protocol */
#endif

#ifndef ICMP6_FILTER
#define ICMP6_FILTER        9 /* icmp6_filter; icmp6 filter */
#endif


#ifndef offsetof
#define offsetof(type, member)    ((ULONG)(&((type *)0)->member))
#endif

/*MAX_INT to arm allign the enums*/
#define IP6_ICMP6_MAX_ENUM_VALUE            0xFFFFFFFF


/*The values for member ulOpsFlag of struct ICMP6_ERRRATE_MSG_S
  passed as argument through pfIP6_ICMP6_ErrorRateLimitUpdate*/
#define SET_ICMP6_ERRRATE_UNDO      0x0
#define SET_ICMP6_BUCKET            0x1
#define SET_ICMP6_INTERVAL          0x2
#define SET_ICMP6_BOTH             (SET_ICMP6_BUCKET | SET_ICMP6_INTERVAL)


/*Argument for pfIP6_ICMP6_SetTooBigErrorRateLimit*/
#define  IP6_ICMP6_TOO_BIG_ERRORRATE_DISABLE   0
#define  IP6_ICMP6_TOO_BIG_ERRORRATE_ENABLE    1


#ifndef _ICMP_RELATED_DEFINES

/* ICMP6 Message Types */
#define ICMP6_DST_UNREACH            1      /********************** 目的不可达 ************************************/
#define ICMP6_PACKET_TOO_BIG         2      /********************** 报文过大 **************************************/
#define ICMP6_TIME_EXCEEDED          3      /********************** 超时 ****************************************/
#define ICMP6_PARAM_PROB             4      /********************** IP头损坏 *************************************/

#define ICMP6_ECHO_REQUEST           128    /********************** 回显服务 echo service *******************************/
#define ICMP6_ECHO_REPLY             129    /********************** 回显应答 echo reply *****************************/
#define ICMP6_MEMBERSHIP_QUERY       130    /********************** 组成员询问 group membership query **********************/
#define ICMP6_MEMBERSHIP_REPORT      131    /********************** 组成员报告 group membership report **********************/
#define MLD6_LISTENER_REPORT         131    /********************** 多播成员回复 multicast listener report **********************/
#define ICMP6_MEMBERSHIP_REDUCTION   132    /********************** 组成员减少 group membership termination **********************/
#define MLD6_LISTENER_DONE           132    /********************** 多播监听完成  multicast listener done **********************/

#define MLD6_V1LISTENER_REPORT       131
#define MLD6_V2LISTENER_REPORT       143

#define ND_ROUTER_SOLICIT            133    /********************** 路由器请求  router solicitation **********************/
#define ND_ROUTER_ADVERT             134    /********************** 路由器通告  router advertisment **********************/
#define ND_NEIGHBOR_SOLICIT          135    /********************** 相邻请求  neighbor solicitation **********************/
#define ND_NEIGHBOR_ADVERT           136    /********************** 相邻通告  neighbor advertisment **********************/
#define ND_REDIRECT                  137    /********************** 重定向  redirect **********************/

#define ICMP6_ROUTER_RENUMBERING     138    /********************** 路由重计数  router renumbering **********************/
#define ICMP6_WRUREQUEST             139    /********************** 请求者  who are you request **********************/
#define ICMP6_WRUREPLY               140    /********************** 应答者  who are you reply **********************/
#define ICMP6_FQDN_QUERY             139    /********************** 域名询问  FQDN query **********************/
#define ICMP6_FQDN_REPLY             140    /********************** 域名应答  FQDN reply **********************/
#define ICMP6_NI_QUERY               139    /********************** 节点信息请求  node information request **********************/
#define ICMP6_NI_REPLY               140    /********************** 节点信息应答  node information reply **********************/

#define IND_SOLICIT                  141
#define IND_ADVERT                   142

/* Start: RFC4443 compliance changes */
#define ICMP6_RSVD_ERR_TYPE          127    /* Reserved ICMP6 error messages*/
#define ICMP6_RSVD_INFO_TYPE         255    /* Reserved ICMP6 info messages*/
#define ICMP6_PVT_ERR_TYPE1          100    /* Private experimentation */
#define ICMP6_PVT_ERR_TYPE2          101    /* Private experimentation */
#define ICMP6_PVT_INFO_TYPE1         200    /* Private experimentation */
#define ICMP6_PVT_INFO_TYPE2         201    /* Private experimentation */

/* End: RFC4443 compliance changes */

#define ICMP6_MAXTYPE                206

/* ICMP6 Message Codes */
#define ICMP6_DST_UNREACH_NOROUTE       0    /* no route to destination */
#define ICMP6_DST_UNREACH_ADMIN         1    /* administratively prohibited */
#define ICMP6_DST_UNREACH_NOTNEIGHBOR   2    /* not a neighbor(obsolete) */
#define ICMP6_DST_UNREACH_BEYONDSCOPE   2    /* beyond scope of source address*/
#define ICMP6_DST_UNREACH_ADDR          3    /* address unreachable */
#define ICMP6_DST_UNREACH_NOPORT        4    /* port unreachable */

/* Start: RFC4443 compliance changes */
#define ICMP6_DST_UNREACH_INGRESS_EGRESS_FLTR 5 /* ingress/egress policy */
#define ICMP6_DST_UNREACH_REJECT_ROUTE        6 /* Reject route to dest */

#define ICMP6_ENABLE_DEST_UNREACH_ERR     0
#define ICMP6_DISABLE_DEST_UNREACH_ERR    1

/* End: RFC4443 compliance changes */

#define ICMP6_TIME_EXCEED_TRANSIT       0    /* ttl==0 in transit */
#define ICMP6_TIME_EXCEED_REASSEMBLY    1    /* ttl==0 in reass */

#define ICMP6_PARAMPROB_HEADER          0    /* erroneous header field */
#define ICMP6_PARAMPROB_NEXTHEADER      1    /* unrecognized next header */
#define ICMP6_PARAMPROB_OPTION          2    /* unrecognized option */

/* Filters using by Upper Layers */
#define ICMP6_FILTER_SETPASSALL(filterp) \
    VOS_Mem_Set((CHAR *)filterp, (CHAR)0xff, sizeof(ICMP6_FILTER_S))

#define ICMP6_FILTER_SETBLOCKALL(filterp) \
    VOS_Mem_Set((CHAR *)filterp, 0x00, sizeof(ICMP6_FILTER_S))

#define ICMP6_FILTER_SETPASS(type, filterp) \
    (((filterp)->ulIcmp6_filt[(type) >> 5]) |= (1 << ((type) & 31)))

#define ICMP6_FILTER_SETBLOCK(type, filterp) \
    (((filterp)->ulIcmp6_filt[(type) >> 5]) &= ~(1 << ((type) & 31)))

#define ICMP6_FILTER_WILLPASS(type, filterp) \
    ((((filterp)->ulIcmp6_filt[(type) >> 5]) & (1 << ((type) & 31))) != 0)

#define ICMP6_FILTER_WILLBLOCK(type, filterp) \
    ((((filterp)->ulIcmp6_filt[(type) >> 5]) & (1 << ((type) & 31))) == 0)
#endif /* _ICMP_RELATED_DEFINES */

/* ICMP Debug Print - String Offsets */
#define ICMP6_IN              0
#define ICMP6_OUT             1
#define ICMP6_CHKSUM          2


#define ICMP6_MIN_ERR_RATELIMIT_BUCKETSIZE 10
#define ICMP6_MAX_ERR_RATELIMIT_BUCKETSIZE 200

#define ICMP6_MIN_ERR_RATELIMIT_INTERVAL 10
#define ICMP6_MAX_ERR_RATELIMIT_INTERVAL 2147483647


/***********************************************************************/
/*                              Enum Defenation                        */
/***********************************************************************/

/* Return values of core functions */
typedef enum tagICMP6_ERRORS
{
    IP6_ICMP6_ERR_CREATE_TIMER_FAILED = 1,
    IP6_ICMP6_INVALID_INPUT_PARAMETER,
    IP6_ICMP6_INVALID_TOKEN_VALUE,
    IP6_ICMP6_ERR_FETCH_CTRL_BLK,
    IP6_ICMP6_ERR_INVALID_INTF_INDEX,
    IP6_ICMP6_ERR_NULL_INPUT,
    IP6_ICMP6_ERR_SEMOP_ACQUIRELOCK_FAIL,
    IP6_ENUM_ICMP6PAD = IP6_ICMP6_MAX_ENUM_VALUE
}ICMP6_ERRORS_E;

/*----------------------------------------------------------------------------*/
/* Not Used By Any One - TBD */
#ifndef _IP6_ICMP6_STATISTICS
#define _IP6_ICMP6_STATISTICS

/* Use to modify statistics */
typedef enum tagIP6_ICMP6_STATISTICS
{
    ICMP6_STAT_INCREMENT,
    ICMP6_STAT_DECREMENT,
    ICMP6_STAT_END = IP6_ICMP6_MAX_ENUM_VALUE
}IP6_ICMP6_STATISTICS;
#endif
/*----------------------------------------------------------------------------*/

#ifndef _ICMP_RELATED_DEFINES

/* ICMP6 statistics field */
typedef enum tagICMP6STATFIELD
{
    ICMP6STAT_PACKET_TOO_SHORT = 0x1,
    ICMP6STAT_TOTAL_OUTPUT,
    ICMP6STAT_OUT_HISTORY,
    ICMP6STAT_BAD_OPTION_PACKET,
    ICMP6STAT_BAD_ROUTER_PACKET,
    ICMP6STAT_ND_NS_OUT,
    ICMP6STAT_ND_NA_OUT,
    ICMP6STAT_ND_RA_OUT,
    ICMP6STAT_ND_RS_OUT,
    ICMP6STAT_TOO_FREQ,
    ICMP6STAT_ERROR,
    ICMP6STAT_CANTERROR,
    ICMP6STAT_TOO_SHORT,
    ICMP6STAT_OUTHIST,
    ICMP6STAT_BADCODE,
    ICMP6STAT_CHECKSUM,
    ICMP6STAT_BADLEN,
    ICMP6STAT_REFLECT,
    ICMP6STAT_INHIST,
    ICMP6STAT_ND_TOOMANYOPTS,
    ICMP6STAT_PMTU_CHG,
    ICMP6STAT_ND_BADOPT,
    ICMP6STAT_BADNS,
    ICMP6STAT_BADNA,
    ICMP6STAT_BADRS,
    ICMP6STAT_BADRA,
    ICMP6STAT_TOTAL_INPUT,
    ICMP6STAT_UNKNOWN_INFO,
    ICMP6STAT_UNKNOWN_ERROR,
    ICMP6STAT_HOP_EXPIRED,
    ICMP6STAT_RES_EXPIRED,
    ICMP6STAT_REDIRECT,
    ICMP6STAT_IN_HISTORY,
    ICMP6STAT_IND_SOLICIT_OUT,
    ICMP6STAT_IND_ADV_OUT,
    ICMP6STAT_BADREDIRECT,  /* Added by Saravanya for ND Host */
    ICMPSTAT_BADDSTADDR,
    IP6_ENUM_PAD = IP6_ICMP6_MAX_ENUM_VALUE

}ICMP6STATFIELD;
#endif /* _ICMP_RELATED_DEFINES */

/***********************************************************************/
/*                           Structure Defenation                      */
/***********************************************************************/

/* Modified by Saravanya : Defect ID AC4D05073, Comment changed */
/* Error Rate Limit structure */
typedef struct tagICMP6_ERRRATE_MSG
{
    ULONG ulInterval; /* Time Interval */
    ULONG ulBucket;   /* Bucket Size */
    ULONG ulOpsFlag;  /* SET_BUCKET = 1, SET_INTERVAL = 2, SET_BOTH = 3,
                                                              SET_UNDO = 0 */
} ICMP6_ERRRATE_MSG_S;

/* Routing related data using by ICMP6 */
typedef struct tagICMP6_ROUTE
{
    ULONG   ulIfIndex;
    ULONG   ulFlags;
    ULONG   aulNexthop[4];
}ICMP6_ROUTE_S;

#ifndef _ICMP6_ERRSTAT_S
#define _ICMP6_ERRSTAT_S

/* generate ICMP6 error packet statistics */
typedef struct tagICMP6_ERRSTAT
{
    ULONG ulIcp6errs_dst_unreach_noroute;
    ULONG ulIcp6errs_dst_unreach_admin;
    ULONG ulIcp6errs_dst_unreach_beyondscope;
    ULONG ulIcp6errs_dst_unreach_addr;
    ULONG ulIcp6errs_dst_unreach_noport;
    ULONG ulIcp6errs_dst_unreach_ingress_egress_plcy;
    ULONG ulIcp6errs_dst_unreach_reject_route;
    ULONG ulIcp6errs_packet_too_big;
    ULONG ulIcp6errs_time_exceed_transit;
    ULONG ulIcp6errs_time_exceed_reassembly;
    ULONG ulIcp6errs_paramprob_header;
    ULONG ulIcp6errs_paramprob_nextheader;
    ULONG ulIcp6errs_paramprob_option;
    ULONG ulIcp6errs_redirect; /* we regard redirect as an error here */
    ULONG ulIcp6errs_unknown;
}ICMP6_ERRSTAT_S;
#endif

#ifndef _ICMP6STAT_S
#define _ICMP6STAT_S

/* ICMP6 packet statistics */
typedef struct tagICMP6STAT
{
    /* statistics related to icmp6 packets generated */
    ULONG ulIcp6s_error;            /* no of calls to icmp6_error */
    ULONG ulIcp6s_canterror;        /* no error 'cuz old was icmp */
    ULONG ulIcp6s_toofreq;          /* no error 'cuz rate limitation */
    ULONG ulIcp6s_intoofreq;        /* no error 'cuz rate limitation */
    ULONG ulIcp6s_outhist[256];

    /* statistics related to input message processed */
    ULONG ulIcp6s_badcode;          /* icmp6_code out of range */
    ULONG ulIcp6s_tooshort;         /* packet < sizeof(struct icmp6_hdr) */
    ULONG ulIcp6s_checksum;         /* bad checksum */
    ULONG ulIcp6s_badlen;           /* calculated bound mismatch */

    ULONG ulIcp6s_reflect;
    ULONG ulIcp6s_inhist[256];
    ULONG ulIcp6s_nd_toomanyopt;    /* too many ND options */

    ICMP6_ERRSTAT_S stIcp6s_outerrhist;
    ICMP6_ERRSTAT_S stIcp6s_inerrhist;

    ULONG ulIcp6s_pmtuchg;           /* path MTU changes */
    ULONG ulIcp6s_nd_badopt;         /* bad ND options */
    ULONG ulIcp6s_badns;             /* bad neighbor solicitation */
    ULONG ulIcp6s_badna;             /* bad neighbor advertisement */
    ULONG ulIcp6s_badrs;             /* bad router advertisement */
    ULONG ulIcp6s_badra;             /* bad router advertisement */

    /* Added by Saravanya for ND Host */
    ULONG ulIcp6s_badredirect;       /* bad Redirect received */

    ULONG ulIcp6s_badDstAddr;        /* Invalid destination address */
    ULONG  ulIcps_totaloutput;       /* Sent total */
    ULONG  ulIcps_totalinput;        /* Recvd total */
    ULONG  ulIcps_inunknowninfo;     /* Recvd unknown info type */
    ULONG  ulIcps_inunknownerror;    /* Recvd unknown error type */
    ULONG  ulIcp6s_inhopexpired;     /* Recvd hop expired */
    ULONG  ulIcp6s_reassexpired;     /* Recvd reassemble expired */
}ICMP6STAT_S;
#endif

/* Start: RFC4443 compliance changes */
#ifndef _ICMP6INFO_S
#define _ICMP6INFO_S

/* Structure to hold ICMP6 info in the Ifnet */
typedef struct tagICMP6Info 
{
    BOOL_T bDestUnReachErrEnbl;
    UCHAR  ucPad[2];
}ICMP6INFO_S;
#endif

/* End: RFC4443 compliance changes */

#ifndef _ICMP_RELATED_DEFINES
#define _ICMP_RELATED_DEFINES

/* ICMP6 header structure */

typedef struct tagICMP6
{
    UCHAR  ucIcmp6_type;                  /* type of message, see below */
    UCHAR  ucIcmp6_code;                  /* type sub code */
    USHORT usIcmp6_cksum;                 /* ones complement cksum of struct */
    union
    {
        ULONG  ulIcmp6_un_data32[1];      /* type-specific field */
        USHORT usIcmp6_un_data16[2];      /* type-specific field */
        UCHAR  ucIcmp6_un_data8[4];       /* type-specific field */
    }unIcmp6_data;
} ICMP6_S;

/* Macros using to access ICMP6_S variables */
#define ulIcmp6_data32    unIcmp6_data.ulIcmp6_un_data32
#define usIcmp6_data16    unIcmp6_data.usIcmp6_un_data16
#define ucIcmp6_data8     unIcmp6_data.ucIcmp6_un_data8
#define ulIcmp6_pptr      ulIcmp6_data32[0]        /* parameter prob */
#define ulIcmp6_mtu       ulIcmp6_data32[0]        /* packet too big */
#define usIcmp6_id        usIcmp6_data16[0]        /* echo request/reply */
#define usIcmp6_seq       usIcmp6_data16[1]        /* echo request/reply */

/* IP6 control parameters */
typedef struct tagIP6_CTLPARAM
{
    MBUF_S         *pstMbuf;         /* start of mbuf chain */
    ICMP6_S        *pstIp6c_icmp6;   /* icmp6 header of target packet */
    IP6_S          *pstIp6c_ip6;     /* ip6 header of target packet */
    ULONG          ulIp6c_off;       /* offset of the target proto header */
    SOCKADDR_IN6_S *pstIp6c_src;     /* srcaddr w/ additional info */
    SOCKADDR_IN6_S *pstIp6c_dst;     /* (final) dstaddr w/ additional info */
    IN6ADDR_S      *pstIp6c_finaldst;/* final destination address */
    VOID           *vpIp6c_cmdarg;   /* control command dependent data */
    UCHAR          ucIp6c_nxt;       /* final next header field */
    UCHAR          ucPadding[3];
} IP6_CTLPARAM_S;


/* ICMP6 filter option */
typedef struct tagICMP6_FILTER
{
    ULONG ulIcmp6_filt[8];
}ICMP6_FILTER_S;

#endif /* _ICMP_RELATED_DEFINES */


/* Shell callback using by other modules (Eg:PING6) */
typedef struct tagIP6_ICMP6_SH_CALLBACUP_SET_S
{
    VOID (*pfIP6_ICMP6_SH_OutDebugInfoToIC)(const ICMP6_S *pstIcmp6,
                   const IN6ADDR_S *pstSrcaddr, const IN6ADDR_S *pstDstaddr, ULONG ulFlag);

}IP6_ICMP6_SH_CALLBACUP_SET_S;

/* Structure has more that 5 elements, obvious */
typedef struct tagICMP6_NP_ERRSTAT
{
    ULONG ulIcp6errs_dst_unreach_noroute; /* No Route to Destination */
    ULONG ulIcp6errs_dst_unreach_admin;   /* Route to dest Admin Prohibited */
    ULONG ulIcp6errs_dst_unreach_beyondscope;   /* Beyond scope of Src Address */
    ULONG ulIcp6errs_dst_unreach_addr;          /* Address Unreachable */
    ULONG ulIcp6errs_dst_unreach_reject_route;  /* Reject Route */
    ULONG ulIcp6errs_packet_too_big;            /* Packet too big */
    ULONG ulIcp6errs_time_exceed_transit;       /* Time exceeded */
    ULONG ulIcp6errs_time_exceed_reassembly;    /* Reassembly Timeout */
    ULONG ulIcp6errs_paramprob_header;   
    ULONG ulIcp6errs_paramprob_nextheader;
    ULONG ulIcp6errs_paramprob_option;
    ULONG ulIcp6errs_redirect;                  /* Redirect */
    ULONG ulIcp6errs_unknown;                   /* Unknown Error */
}ICMP6_NP_ERRSTAT_S;

/* ICMPv6 NP Statistics */
typedef struct tagICMP6STAT_NP
{
    ULONG ulIcps_totaloutput;   /* Total number of ICMPv6 packets sent out */
    ULONG ulIcp6s_error; /* Total number of ICMPv6 ERROR packets sent out */
    ULONG ulIcp6s_canterror; /* Total number of times ICMPv6 ERROR is supressed */
    ULONG ulIcp6s_outhist[256]; /* Sent Packet History */
    ICMP6_NP_ERRSTAT_S stIcp6s_outerrhist; /* ICMPv6 pkts sent out with particular type */
} ICMP6STAT_NP_S;

typedef struct tagICMP6STATBYTYPE
{
    ULONG ulStatValue_Return;   /* Return Value of Statistics */
    ULONG ulICMPv6StatField;    /* ICMPv6 Statistics Field */
    UCHAR ucICMP6Type;          /* ICMPv6 Statistics Type */
    UCHAR ucPad[3];
}ICMP6STATBYTYPE_S;

 /* Get ICMPv6 statistics by Ifnet Index */
typedef struct tagICMP6STATPERINTF
{
    ULONG ulIfIndex;
    ICMP6STAT_NP_S stStatOut;   /* Return Value of Statistics */
}ICMP6STATPERINTF_S;

typedef struct ICMP6_EXT_CALLBACK
{
    /* For ICMPv6 Too-Big Notification */
    ULONG (*pfICMP6_TooBigNotify)(MBUF_S *pstMBuf, ULONG ulIfIndex);
}ICMP6_EXT_CALLBACK_S;


#ifdef  __cplusplus
}
#endif

#endif  /* _ICMP6_PUBLIC_H */

