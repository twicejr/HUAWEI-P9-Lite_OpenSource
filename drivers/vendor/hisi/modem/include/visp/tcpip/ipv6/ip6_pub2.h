

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/


#include "common/ipos/ipv6/ip6_pub.h"

/*Removed by wan for VISP-Integrated, 2007-01-27*/
#ifndef _ICMP_RELATED_DEFINES /* BY KLSRINI */
#define _ICMP_RELATED_DEFINES

/*ICMPv6 header*/
typedef struct tagICMP6
{
    UCHAR  ucIcmp6_type;                     /* type of message, see below */
    UCHAR  ucIcmp6_code;                     /* type sub code */
    USHORT usIcmp6_cksum;                 /* ones complement cksum of struct */
    union
    {
        ULONG  ulIcmp6_un_data32[1];    /* type-specific field */
        USHORT usIcmp6_un_data16[2];   /* type-specific field */
        UCHAR  ucIcmp6_un_data8[4];      /* type-specific field */
    }unIcmp6_data;
} ICMP6_S;

#define ulIcmp6_data32      unIcmp6_data.ulIcmp6_un_data32
#define usIcmp6_data16     unIcmp6_data.usIcmp6_un_data16
#define ucIcmp6_data8       unIcmp6_data.ucIcmp6_un_data8
#define ulIcmp6_pptr          ulIcmp6_data32[0]        /* parameter prob */
#define ulIcmp6_mtu           ulIcmp6_data32[0]        /* packet too big */
#define usIcmp6_id             usIcmp6_data16[0]       /* echo request/reply */
#define usIcmp6_seq          usIcmp6_data16[1]        /* echo request/reply */


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


/* Start: Changes for RFC4443 compliance */
#define ICMP6_RSVD_ERR_TYPE          127    /* Code for Reserved ICMP6 error messages*/
#define ICMP6_RSVD_INFO_TYPE         255    /* Code for Reserved ICMP6 info messages*/
#define ICMP6_PVT_ERR_TYPE1          100    /* Code for Private experimentation */
#define ICMP6_PVT_ERR_TYPE2          101    /* Code for Private experimentation */
#define ICMP6_PVT_INFO_TYPE1         200    /* Code for Private experimentation */
#define ICMP6_PVT_INFO_TYPE2         201    /* Code for Private experimentation */

/* End: Changes for RFC4443 compliance */

#define ICMP6_MAXTYPE                206

/* ICMP6 Message Codes */
#define ICMP6_DST_UNREACH_NOROUTE    0    /* no route to destination */
#define ICMP6_DST_UNREACH_ADMIN      1    /* administratively prohibited */
#define ICMP6_DST_UNREACH_NOTNEIGHBOR  2    /* not a neighbor(obsolete) */
#define ICMP6_DST_UNREACH_BEYONDSCOPE  2    /* beyond scope of source address */
#define ICMP6_DST_UNREACH_ADDR         3    /* address unreachable */
#define ICMP6_DST_UNREACH_NOPORT       4    /* port unreachable */

/* RFC4443 compliance changes */
#define ICMP6_DST_UNREACH_INGRESS_EGRESS_FLTR  5    /* Ingress/egress filter */
#define ICMP6_DST_UNREACH_REJECT_ROUTE         6    /* Reject route */

#define ICMP6_TIME_EXCEED_TRANSIT      0    /* ttl==0 in transit */
#define ICMP6_TIME_EXCEED_REASSEMBLY   1    /* ttl==0 in reass */

#define ICMP6_PARAMPROB_HEADER         0    /* erroneous header field */
#define ICMP6_PARAMPROB_NEXTHEADER     1    /* unrecognized next header */
#define ICMP6_PARAMPROB_OPTION         2    /* unrecognized option */


#define ICMP6_INFOMSG_MASK             0x80    /* all informational messages */

#define ICMP6_FILTER_SETPASSALL(filterp) \
    TCPIP_Mem_Set((CHAR *)filterp, (CHAR)0xff, sizeof(ICMP6_FILTER_S))

#define ICMP6_FILTER_SETBLOCKALL(filterp) \
    TCPIP_Mem_Set((CHAR *)filterp, 0x00, sizeof(ICMP6_FILTER_S))

#define ICMP6_FILTER_SETPASS(type, filterp) \
    (((filterp)->ulIcmp6_filt[(type) >> 5]) |= (1 << ((type) & 31)))

#define ICMP6_FILTER_SETBLOCK(type, filterp) \
    (((filterp)->ulIcmp6_filt[(type) >> 5]) &= ~(1 << ((type) & 31)))

#define ICMP6_FILTER_WILLPASS(type, filterp) \
    ((((filterp)->ulIcmp6_filt[(type) >> 5]) & (1 << ((type) & 31))) != 0)

#define ICMP6_FILTER_WILLBLOCK(type, filterp) \
    ((((filterp)->ulIcmp6_filt[(type) >> 5]) & (1 << ((type) & 31))) == 0)

#ifndef offsetof
#define offsetof(type, member)    ((ULONG)(&((type *)0)->member))
#endif

/* ICMP6 Filter*/
typedef struct tagICMP6_FILTER
{
    ULONG ulIcmp6_filt[8];
}ICMP6_FILTER_S;

/*ICMP6 Status fields*/
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
    ICMP6STAT_BADREDIRECT,  /* Added by Saravanya for ND Host */


    /* IPv6oFR END : Modifier:arvindsaproo,   Date:2004/10/4 */
    /* Reason:- For ARM CPU support*/
    IP6_ENUM_ICMP6 = 0xFFFFFFFF


}ICMP6STATFIELD;

/* KLSRINI : Moving here to keep all ICMP stuff together */
typedef struct tagIP6_CTLPARAM
{
    MBUF_S * pstMbuf;       /* start of mbuf chain */
    ICMP6_S  * pstIp6c_icmp6;   /* icmp6 header of target packet */
    IP6_S *pstIp6c_ip6;         /* ip6 header of target packet */
    ULONG ulIp6c_off;           /* offset of the target proto header */
    SOCKADDR_IN6_S *pstIp6c_src;    /* srcaddr w/ additional info */
    SOCKADDR_IN6_S *pstIp6c_dst;    /* (final) dstaddr w/ additional info */
    IN6ADDR_S * pstIp6c_finaldst;   /* final destination address */
    VOID * vpIp6c_cmdarg;       /* control command dependent data */
    UCHAR ucIp6c_nxt;       /* final next header field */
    UCHAR ucPadding[3];
} IP6_CTLPARAM_S;

#endif /* BY KLSRINI */

