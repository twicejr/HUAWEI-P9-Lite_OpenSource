
#ifndef _IP6_ND_H
#define _IP6_ND_H

#ifdef    __cplusplus
extern "C"{
#endif

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

#if(TCPIP_IN_VRP == VRP_NO)
extern ULONG    EXEC_OutString(ULONG,CHAR *);
#endif

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

/* Macros used for Trace information */
#define IP6_ND_C         ((SYSTRC_IPV6_ND_BASE << 8) + 01)
#define IP6_ND_NB_C      ((SYSTRC_IPV6_ND_BASE << 8) + 02)
#define IP6_ND_RT_C      ((SYSTRC_IPV6_ND_BASE << 8) + 03)
#define IP6_ND_DAD_C     ((SYSTRC_IPV6_ND_BASE << 8) + 04)
#define IP6_ND_MGT_C     ((SYSTRC_IPV6_ND_BASE << 8) + 05)
#define IP6_ND_NBCACHE_C ((SYSTRC_IPV6_ND_BASE << 8) + 06)

/* Conditional compilation macro to enable Debugs */
#define ND_DEBUG_TEST     0

/* Assigned ND Task Priority */
#define ND_TASK_PRIORITY  128

/* Macros for Interface Status */
#define IFPHY_DOWN        0
#define IFPHY_UP          1
#define INTERFACE_DOWN    0
#define INTERFACE_UP      1

/*****************************************************************************/
                    /* ND - SID's for Malloc */
/*****************************************************************************/
/* SID for ND Memory allocations */
#define SID_NDINFO      0x0001     /* SID for ND Info structure */
#define SID_NDDAD       0x0002
#define SID_NBENTRY     0x0003
#define SID_ND_PREFIX   0x0004
#define SID_NDTIMER     0x0005
#define SID_NSPACKET    0x0006
#define SID_NAPACKET    0x0007
#define SID_RAPACKET    0x0008
#define SID_RSPACKET    0x0009


/*****************************************************************************/
                    /* ND Host - SID's for Malloc */
/*****************************************************************************/
/* RA Host Params Control msg Data */
#define SID_RAHOSTPARAMS                  0x0010

/* Prefix List node constructed for processing PIOs received in RA */
#define SID_PREFIXOPTLIST                 0x0011

/* Timer message structure pointer */
#define SID_HOST_TMRMSG                   0x0012

/* Timer message structure pointer */
#define SID_HOST_TMRMSG_DATA              0x0013

/* Default Router list node */
#define SID_HOST_DEFROUTER_LIST           0x0014

/* Global list node for Interface which has Default Router(s) */
#define SID_HOST_INTFDEFRTRAVAILNODE      0x0015

/* Stateful Address config control message pointer */
#define SID_STATEFULADDRCFGMSG            0x0016

/* Stateful Address config control message Data(Address) pointer */
#define SID_STATEFULADDRCFGMSG_DATA       0x0017

/* Stateful Other config control message pointer */
#define SID_STATEFULOTHERCFGMSG           0x0018

/* Stateful Address Not usable notification control message pointer */
#define SID_STFADDRNOTUSEMSG              0x0019

/* Stateful Address Not usable notification control message Data pointer */
#define SID_STFADDRNOTUSEMSG_DATA         0x0020

/* Interface Prefix list node */
#define SID_HOST_INTFPREFIX_LIST          0x0021

/* Global Prefix list node */
#define SID_HOST_GBLPREFIX_LIST           0x0022

/* Radix tree External node for both Destination Cache and Global Prefix list */
#define SID_HOST_EXT_RADIX_NODE           0x0023

/* Destination cache node */
#define SID_HOST_DEST_CACHE_NODE          0x0024

/* For Redirect Message */
#define SID_REDIRECTPACKET                0x0025

/* ND Host parameter */
#define SID_ND_HOSTPARAMS                 0x0026

/* Helper Data pointer for waitlist */
#define SID_WLHELPER_INFO                 0x0027

/* Host Related changed end here */
/*****************************************************************************/

/* Structure defined to send info to Shell for Build Run and Sync*/
#define SID_ND_GETFROMCORE                0x0028

/* Added for the New nd_l2.c file to handle L3 VLAN and VLANIF changes */
#define SID_ND_L2_PROC                         0x0029

/* Macros for representing MAIN Board or Slave Board */
#define ND_AMB            0
#define ND_SMB            1

/* Macro to mention Timeout value for RPC call */
#define TIMEOUTVALUE_2000 2000

/* RFC 2461
10.  PROTOCOL CONSTANTS
   Router constants:
            MAX_INITIAL_RTR_ADVERT_INTERVAL  16 seconds
            MAX_INITIAL_RTR_ADVERTISEMENTS    3 transmissions
            MAX_FINAL_RTR_ADVERTISEMENTS      3 transmissions
            MIN_DELAY_BETWEEN_RAS             3 seconds
            MAX_RA_DELAY_TIME                .5 seconds
*/

#define MAX_INITIAL_RTR_ADVERT_INTERVAL     16  /* seconds */
#define MAX_INITIAL_RTR_ADVERTISEMENTS       3
#define MAX_FINAL_RTR_ADVERTISEMENTS         3
#define MIN_DELAY_BETWEEN_RAS             3000  /* mSeconds */
#define MAX_RA_DELAY_TIME                  500  /* mSeconds */

/* RFC 2461

   Node constants:

            MAX_MULTICAST_SOLICIT             3 transmissions
            MAX_UNICAST_SOLICIT               3 transmissions
            MAX_ANYCAST_DELAY_TIME            1 second
            MAX_NEIGHBOR_ADVERTISEMENT        3 transmissions
            REACHABLE_TIME               30,000 milliseconds
            RETRANS_TIMER                 1,000 milliseconds
            DELAY_FIRST_PROBE_TIME            5 seconds

*/

#define MAX_MULTICAST_SOLICIT                    3
#define MAX_NEIGHBOR_ADVERTISEMENT               3
#define DELAY_FIRST_PROBE_TIME                5000

#define IP6_ND_PREFIX_VALID_LIFE_TIME      2592000
#define IP6_ND_PREFIX_PREFERRED_LIFE_TIME   604800
#define ND_PACKET_HOPLIMIT                     255


#define IP6_ND_PREFIX_LENGTH_MAX                128

/* V4 Mapped Address Prefix length */
#define IP6_ND_V4_MAPPED_PREFIX                   96

#define DEFAULT_RA_MTU                          1500

/* RFC 2461

      AdvReachableTime
                     The value to be placed in the Reachable Time field
                     in the Router Advertisement messages sent by the
                     router.  The value zero means unspecified (by this
                     router).  MUST be no greater than 3,600,000
                     milliseconds (1 hour).
                     Default: 0

      AdvRetransTimer The value to be placed in the Retrans Timer field
                     in the Router Advertisement messages sent by the
                     router.  The value zero means unspecified (by this
                     router).
                     Default: 0

*/
#define DEFAULT_RA_REACHABLE          0
#define DEFAULT_RA_RETRANS            0

#define RESERVEDHEADSPACE           200

#define ND_SETMINVAL            0
#define ND_REACH_SETMAXVAL      3600000
#define ND_REACH_SETMINVAL      1000
#define ND_RAMAX_SETMINVAL      4
#define ND_RAMAX_SETMAXVALUE    1800
#define ND_RAMAX_SETMAXVALUE_NINE 9
#define ND_RAMIN_SETMINVAL      3
#define ND_RAMIN_SETMAXVALUE    1350
#define ND_RA_SETDEFAULTVALUE   9000
#define ND_SET_MINHOPLIMIT      1
#define ND_SET_MAXHOPLIMIT      255
#define ND_SET_MAXENTRYLIMIT    1025
#define ND_SET_MAXDADATTEMPT    600

/* Modified by guojianjun178934, 【检视发现问题-ND间隔不准】邻居请求的重传间隔不准，有0.5s的误差 , 2014/1/21   问题单号:DTS2014011003946  */
#define ND_NBTIMER_INTERVAL     200
/*End of Modified by guojianjun178934, 2014/1/21   问题单号:DTS2014011003946  */
/* Modified by guojianjun178934, IPV6 DAD探测定时器修改方案变更, 2014/2/12   问题单号:S-IP-003-PUBLIC-FUNC-005  */
#define IP6_ND_DAD_INTERVAL     100
/*End of Modified by guojianjun178934, 2014/2/12   问题单号:S-IP-003-PUBLIC-FUNC-005  */

/* RFC 2461: RETRANS_TIMER  1,000 milliseconds */
#define ND_DADTIMER_INTERVAL            1000

/*modified for DTS2014051400943 2014-05-14 修改免费NA定时器时长为10ms，解决hert倒换丢包问题--start */
#define ND_NATIMER_INTERVAL             10

#define ND_NBFORCEDELTIMER_INTERVAL     100

/*Added by guojianjun178934, 接口状态变化或physical地址变化主动发送通告NA报文 , 2014/1/26   问题单号:S-IP-005-PUBLIC-FUNC-003 */
#define ND_NA_DELAY_MIN     ND_NATIMER_INTERVAL   /*首个NA报文最小发送时延*/

/*modified for DTS2014051400943 2014-05-14 修改首个免费NA延时时间为10ms，解决hert倒换丢包问题--start */
#define ND_NA_DELAY_MAX     100        /*首个NA报文最大发送时延*/

#define ND_SET_MAXNAATTEMPT 10        /*NA报文最大发送次数*/
#define ND_NA_INTERVAL_MIN  1000      /*NA报文发送的最小时间间隔*/
#define ND_NA_INTERVAL_MAX  5000      /*NA报文发送的最大时间间隔*/
/* End of Added by guojianjun178934, 2014/1/26   问题单号:S-IP-005-PUBLIC-FUNC-003 */


#if (VRP_YES == IPB_IR_IPV6_MODULE_IND)
#define ND_INDTIMER_INTERVAL            500   /* Trigger IND TWL timer */
#endif /* (VRP_YES == VRP_MODULE_IPV6_FR)*/

/* Neighbor Discovery Message Type values */
#define ND_RS        133        /* RFC 2461 Section 4.1 */
#define ND_RA        134        /* RFC 2461 Section 4.2 */
#define ND_NS        135        /* RFC 2461 Section 4.3 */
#define ND_NA        136        /* RFC 2461 Section 4.4 */

/* ND Options Type value */
#define ND_OPTION_SLLA          1
#define ND_OPTION_TLLA          2
#define ND_OPTION_PREFIX        3
#define ND_OPTION_REDIRECT      4
#define ND_OPTION_MTU           5

/*Changed by Karthik for Def: AC4D00935 Des:ND.RA Implementation
  violates the RFC */
#define ND_MULT_RA_GET_LIFE          3
#define ND_MAX_ROUT_LIFETIME       9000

/* Unspecified hop limit value */
#define IP6_ND_RA_HOPLIMIT_UNSPEC               0

/* Unspecified MTU value */
#define IP6_ND_RA_MTU_UNSPEC                    0

/* Unspecified Base Reachable Time value */
#define IP6_ND_RA_BASEREACH_TIME_UNSPEC         0

/* Unspecified NS Retransmission Time value */
#define IP6_ND_RA_NSRETRANS_TIME_UNSPEC         0


#define ND_ARE_LLA_EQUAL(m_aucLLA1, m_aucLLA2) \
    ((m_aucLLA1[0] == m_aucLLA2[0]) && (m_aucLLA1[1] == m_aucLLA2[1]) \
    && (m_aucLLA1[2] == m_aucLLA2[2]) && (m_aucLLA1[3] == m_aucLLA2[3]) \
    && (m_aucLLA1[4] == m_aucLLA2[4]) && (m_aucLLA1[5] == m_aucLLA2[5]))\


/* Copy IP6 Address from the ULONG to the Structure - Convert to
Network byte order also */
#define IP6_ND_COPY_IP6ADDR_ARRAY_TO_STRUCT(m_dst, m_src)\
{\
    (m_dst)->s6_addr32[0] = VOS_HTONL(m_src[0]);\
    (m_dst)->s6_addr32[1] = VOS_HTONL(m_src[1]);\
    (m_dst)->s6_addr32[2] = VOS_HTONL(m_src[2]);\
    (m_dst)->s6_addr32[3] = VOS_HTONL(m_src[3]);\
}

/* Copy IP6 Address from the Structure to the Array - Convert to
host byte order also */
#define IP6_ND_COPY_IP6ADDR_STRUCT_TO_ARRAY(m_dest, m_src)\
{\
    (m_dest)->aulAddr[0] = VOS_NTOHL((m_src)->s6_addr32[0]);\
    (m_dest)->aulAddr[1] = VOS_NTOHL((m_src)->s6_addr32[1]);\
    (m_dest)->aulAddr[2] = VOS_NTOHL((m_src)->s6_addr32[2]);\
    (m_dest)->aulAddr[3] = VOS_NTOHL((m_src)->s6_addr32[3]);\
}

/* Macros to access ND_OPT_U */
#define pstNdOptSrcLladdr     stNdOptEach.pstOptSrcLladdr
#define pstNdOptTgtLladdr     stNdOptEach.pstOptTgtLladdr
#define pstNdOptPrxBe         stNdOptEach.pstOptPrxBeg
#define pstNdOptPrxEnd        stNdOptEach.pstOptPrxEnd
#define pstNdOptRh            stNdOptEach.pstOptRh
#define pstNdOptMtu           stNdOptEach.pstOptMtu
#define pstNdOptSearch        stNdOptEach.pstOptSearch
#define pstNdOptLast          stNdOptEach.pstOptLast
#define usNdOptDone           stNdOptEach.bOptDone


/* Macros for LOG information  */
#define M_FLAG                  0
#define O_FLAG                  1
#define CUR_HOP_LIMIT           2
#define REACHABLETIME           3
#define NSINTERVAL              4
#define MTU                     5
#define GET_EXTHEADER           6

/* Macros for Debug Information  */
#define DEBUG_NAMSG             0
#define DEBUG_NSMSG             1
#define DEBUG_RAMSG             2
#define DEBUG_RSMSG             3
#define DEBUG_FINALRAMSG        4
#define DEBUG_REDIRECTMSG       5

#define DEBUG_RCV_EXTHEADER     2
#define DEBUG_RCV_HOPLIMIT      3     /* Packet Hop Limit Exceeds */

/* if the source address is a unspecified address, destination address
   not a solicited-node  multicast address, discard the packet. */
#define DEBUG_RCV_SRCDST        4
#define DEBUG_RCV_TGT           5   /* Target address is a multicast address */
#define DEBUG_RCV_SAME_IP       6   /* target address is same as address */
#define DEBUG_RCV_DUPLICATE     7   /* target address is duplicate */
#define DEBUG_RCV_OPTION        8   /* Options Incorrect */
#define DEBUG_RCV_SRC_SLLA      9   /* Src Addr Unspecified and SLLA present */
#define DEBUG_RCV_TRG_TENTATIVE 10  /* target address is tentative */
#define DEBUG_RCVMSG_TUNNEL     11
#define DEBUG_RCV_DST_FLAG      12
#define DEBUG_RCV_TRG_CACHE     13
#define DEBUG_RCV_SRC_TLLA      14
#define DEBUG_RCV_RA_RTZERO     15
#define DEBUG_RCV_RA_UNICAST    16
#define DEBUG_RCV_RA_TIME       17
#define DEBUG_RCV_RA_CANNOT     18
#define DEBUG_NS_SEND_TGT       19
#define DEBUG_NS_SEND_PROB      20
#define DEBUG_NA_SEND_PROB      21
#define DEBUG_RA_SEND_PROB      22
#define DEBUG_SNDADDRMSG        23
#define DEBUG_RCV_NOTLINKLOCAL  24
#define DEBUG_RCV_INPKTNULL     25
#define DEBUG_RCV_IFISNULL      26
#define DEBUG_RCV_GETIPV6CTLBLKFAILED   27
#define DEBUG_RCV_GETNDINFOFAILED       28
#define DEBUG_RCV_OPTHDRERR     29
#define DEBUG_SND_RACTLBLKNULL  30
#define DEBUG_SND_CRTPKTFLD     31
#define DEBUG_SND_NDINFONULL    32
#define DEBUG_RCV_NDCACHEERR    33
#define DEBUG_ADDNBENTRY        0
#define DEBUG_DELNBENTRY        1
#define DEBUG_CHANGNBENTRY      2
#define DEBUG_STARTADDRRES      3
#define DEBUG_STARTADDRSTOP     4

/* Macro to assign All node link local address to IN6ADDR_S */
#define IP6_IN6ADDR_LINKLOCAL_ALLNODES_INIT \
{\
    {\
        {\
            0xff, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 \
        }\
    }\
}

/* Macro to assign unspecified address to IN6ADDR_S */
#define IP6_IN6ADDR_ANY_INIT \
{\
    {\
        {\
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 \
        }\
    }\
}


/* Macros to tell what operations is being done on neighbor cache */
/* SWFD12690: modified by z45065 */
#define ND_ADD     1
#define ND_DEL     2
#define ND_MOD     3


/* Macro for  Minimum, maximum and default values for MTU */
#define     IP6_ND_MIN_MTU                     1280
#define     IP6_ND_MAX_MTU                     1500
#define     IP6_ND_DEFAULT_MTU                 1500


/* Max Prefix allowed via CLI configuration */
/* AC4D01206 - Modified by Prabhu H (71185) */
#define    IP6_ND_MAX_CLI_PREFIX_ALLOWED    IP6_MAXADDRNUM_ONEIF

/* Max Prefix allowed via notification from Address Management */
#define    IP6_ND_MAX_AUTO_PREFIX_ALLOWED    IP6_MAXADDRNUM_ONEIF


#define    IP6_ND_LINK_DOWN                 00        /* To indicate RA to be
sent out if LL down, to be decided */

#define    IP6_ND_ERROR_MAX_NO              10

#define NSINTERVAL_MIN  1000
#define NSINTERVAL_MAX  3600000

/* Macros to avoid magic numbers */
#define ULONG_BY4       5 /* 4 + 1 */
#define ULONG_STR_SIZE  11 /* 10 + 1 */
#define BUFF_19         19
#define BUFF_30         30
#define BUFF_50         50
#define BUFF_100        100
#define NDSTATELEN      13
#define DISPLAYLLASTATE 15
#define FORDISPLAYSTATE 6
#define AFTERFIRSTBYTE  1
#define AFTERTHIRDBYTE  3
#define STRLEN_24       24
#define STRLEN_25       25
#define STRLEN_27       27 /* Max ipos num length */
#define ND_OPT_LEN_SFT  3

/* For converting time units */
#define CONVERT_BETWEEN_SEC_MIN 60

#define NOT_MII_SUPPORT  0

#define PPI_IP6_NBENTRY_ADD         1
#define PPI_IP6_NBENTRY_DELETE      2

/*  IP6_ND_MOD_INFO_S for getting the MOD ID from shell,
and IP6ND_DADState_S for distribution requirement. */

#define ND_OPT_DONE       1
#define ND_OPT_NOTDONE    0

#define ND_RA_SENDLIFETIME_ZERO     0
#define ND_RA_SENDLIFETIME_NONZERO  1

#define ND_HAVENOTLLA               0
#define ND_HAVELLA                  1

#define IP6_MIB_TRUE                1
#define IP6_MIB_FALSE               2
#define IP6_MIB_ENTRY_NOTPRESENT    3

/*ipv6NetToMediaType */
#define IP6_ND_OTHER    1
#define IP6_ND_DYNAMIC  2
#define IP6_ND_STATIC   3
#define IP6_ND_LOCAL    4

/*ipv6IfNetToMediaState*/
#define IP6_ND_REACHABLE 1
#define IP6_ND_STALE     2
#define IP6_ND_DELAY     3
#define IP6_ND_PROBE     4
#define IP6_ND_INVALID   5
#define IP6_ND_UNKNOWN   6


/* Notification to NP/IAS for VLAN and VLANIF framework*/
#define IP6_ND_NOTIFY_HW                    1
#define IP6_ND_DONOT_NOTIFY_HW       0

/* PAF value for Per board NB entries */
#define ND_PAF_TOTAL_NBENTRIES_MAX      g_stIP6_ND_PAFTotalNBEntries.ulMax_Value
#define ND_PAF_TOTAL_NBENTRIES_MIN      g_stIP6_ND_PAFTotalNBEntries.ulMin_Value
#define ND_PAF_TOTAL_NBENTRIES_AVAIL    g_stIP6_ND_PAFTotalNBEntries.ulAvail_Value

/* HCC Error : 80 chars it is obvious */
#define ND_PAF_TOTAL_STAT_NBENTRIES_AVAIL g_stIP6_ND_PAFTotalStatNBEntries.ulAvail_Value

/* PAF value for Interafce NB entries */
#define ND_PAF_INF_NBENTRIES_MAX     g_stIP6_ND_PAFInfNBEntries.ulMax_Value
#define ND_PAF_INF_NBENTRIES_MIN     g_stIP6_ND_PAFInfNBEntries.ulMin_Value
#define ND_PAF_INF_NBENTRIES_AVAIL   g_stIP6_ND_PAFInfNBEntries.ulAvail_Value

/* PAF value for Interafce NB entries */
#define ND_PAF_INF_STATIC_NBENTRIES_MAX    g_stIP6_ND_PAFInfStatNBEntries.ulMax_Value
#define ND_PAF_INF_STATIC_NBENTRIES_MIN    g_stIP6_ND_PAFInfStatNBEntries.ulMin_Value
#define ND_PAF_INF_STATIC_NBENTRIES_AVAIL  g_stIP6_ND_PAFInfStatNBEntries.ulAvail_Value

/* PAF value for Prefix number */
#define ND_PAF_PREFIX_NUMBER_MAX     g_stIP6_ND_PAFPrefixNum.ulMax_Value
#define ND_PAF_PREFIX_NUMBER_MIN     g_stIP6_ND_PAFPrefixNum.ulMin_Value
#define ND_PAF_PREFIX_NUMBER_AVAIL   g_stIP6_ND_PAFPrefixNum.ulAvail_Value



#define IP6_ND_FILLPREFIXENTRY(m_pstOutPfxTblEntry, m_pstNDPrefix)\
{\
    (m_pstOutPfxTblEntry)->ulIfIndex                           \
                                   = (m_pstNDPrefix)->ulIfnetIndex;\
    VOS_CopyVar((m_pstOutPfxTblEntry)->stIpv6AddressPrefix ,\
                                          (m_pstNDPrefix)->stPrefix);\
    (m_pstOutPfxTblEntry)->ulIPv6AddrPrefixLength   = (m_pstNDPrefix)->ulLen;\
    if (VOS_FALSE != (m_pstNDPrefix)->ucAFlag)\
    {\
        (m_pstOutPfxTblEntry)->ipv6AddrPrefixAutonomousFlag  \
                                            = (BOOL_T)IP6_MIB_TRUE;\
    }\
    else\
    {\
        (m_pstOutPfxTblEntry)->ipv6AddrPrefixAutonomousFlag    \
                                             = (BOOL_T)IP6_MIB_FALSE;\
    }\
    if (VOS_FALSE != (m_pstNDPrefix)->ucLFlag)\
    {\
        (m_pstOutPfxTblEntry)->ipv6AddrPrefixOnLinkFlag      \
                                                = (BOOL_T)IP6_MIB_TRUE;\
    }\
    else\
    {\
        (m_pstOutPfxTblEntry)->ipv6AddrPrefixOnLinkFlag   \
                                                 = (BOOL_T)IP6_MIB_FALSE;\
    }\
    (m_pstOutPfxTblEntry)->ulIPv6AddrPrefixAdvPreferredLifetime   \
                                  = (m_pstNDPrefix)->ulPreferredTime;\
    (m_pstOutPfxTblEntry)->ulIPv6AddrPrefixAdvValidLifetime     \
                                             = (m_pstNDPrefix)->ulValidTime;\
}



#define  IP6_ND_FILLNET2MEDIAENTRY(m_pstOutNet2MediaEntry, m_pstNBEntry)\
{\
    (m_pstOutNet2MediaEntry)->ulIfIndex                     \
                                  = (m_pstNBEntry)->ulIfnetIndex;\
    VOS_CopyVar((m_pstOutNet2MediaEntry)->stipv6NetToMediaNetAdd,\
    (m_pstNBEntry)->stIPv6Addr);\
    (VOID)TCPIP_Mem_Copy((m_pstOutNet2MediaEntry)->ucMacAddr, MACADDRLEN,\
                             (m_pstNBEntry)->ucLLAddr, MACADDRLEN);\
    (m_pstOutNet2MediaEntry)->ulipv6IfNetToMediaLastUpdated  \
                                        = (m_pstNBEntry)->ulTimeStamp;\
    switch ((m_pstNBEntry)->ucState)\
    {\
        case ND_STATE_REACHABLE:\
            (m_pstOutNet2MediaEntry)->ulipv6IfNetToMediaState = \
                                                 IP6_ND_REACHABLE;\
            break;\
        case ND_STATE_STALE:\
            (m_pstOutNet2MediaEntry)->ulipv6IfNetToMediaState = \
                                                     IP6_ND_STALE;\
            break;\
        case ND_STATE_DELAY:\
            (m_pstOutNet2MediaEntry)->ulipv6IfNetToMediaState = \
                                        IP6_ND_DELAY;\
            break;\
        case ND_STATE_PROBE:\
            (m_pstOutNet2MediaEntry)->ulipv6IfNetToMediaState = \
                                                    IP6_ND_PROBE;\
            break;\
        default:\
            (m_pstOutNet2MediaEntry)->ulipv6IfNetToMediaState = \
                                             IP6_ND_UNKNOWN;\
            break;\
    }\
    if ((m_pstNBEntry)->ucIsStaticEntry)\
    {\
        (m_pstOutNet2MediaEntry)->ulipv6NetToMediaType = IP6_ND_STATIC;\
    }\
    else\
    {\
        (m_pstOutNet2MediaEntry)->ulipv6NetToMediaType = IP6_ND_DYNAMIC;\
    }\
    (m_pstOutNet2MediaEntry)->usipv6NetToMediaValid  = IP6_MIB_TRUE;\
}

/*To convert Net2Media Entry from Network to Host*/
#define IP6_ND_NET2MEDIAENTRY_NTOH(m_pstNet2MediaEntry)\
{\
    (m_pstNet2MediaEntry)->ulIfIndex                       \
                  = VOS_NTOHL((m_pstNet2MediaEntry)->ulIfIndex);\
    (m_pstNet2MediaEntry)->ulipv6IfNetToMediaLastUpdated   \
        = VOS_NTOHL((m_pstNet2MediaEntry)->ulipv6IfNetToMediaLastUpdated);\
    (m_pstNet2MediaEntry)->usipv6NetToMediaValid           \
        = (BOOL_T)VOS_NTOHS((m_pstNet2MediaEntry)->usipv6NetToMediaValid);\
    (m_pstNet2MediaEntry)->ulipv6IfNetToMediaState         \
        = VOS_NTOHL((m_pstNet2MediaEntry)->ulipv6IfNetToMediaState);\
    (m_pstNet2MediaEntry)->ulipv6NetToMediaType            \
        = VOS_NTOHL((m_pstNet2MediaEntry)->ulipv6NetToMediaType);\
    IPV6_ADDRESS_NTOH(\
        (m_pstNet2MediaEntry)->stipv6NetToMediaNetAdd.u6_addr.u6_uladdr);\
}

/*To convert Net2Media Entry from Host to Network*/
#define IP6_ND_NET2MEDIAENTRY_HTON(m_pstNet2MediaEntry)\
{\
    (m_pstNet2MediaEntry)->ulIfIndex                      \
        = VOS_HTONL((m_pstNet2MediaEntry)->ulIfIndex);\
    (m_pstNet2MediaEntry)->ulipv6IfNetToMediaLastUpdated   \
        = VOS_HTONL((m_pstNet2MediaEntry)->ulipv6IfNetToMediaLastUpdated);\
    (m_pstNet2MediaEntry)->usipv6NetToMediaValid           \
        = (BOOL_T)VOS_HTONS((m_pstNet2MediaEntry)->usipv6NetToMediaValid);\
    (m_pstNet2MediaEntry)->ulipv6IfNetToMediaState         \
        = VOS_HTONL((m_pstNet2MediaEntry)->ulipv6IfNetToMediaState);\
    (m_pstNet2MediaEntry)->ulipv6NetToMediaType            \
        = VOS_HTONL((m_pstNet2MediaEntry)->ulipv6NetToMediaType);\
    IPV6_ADDRESS_HTON(\
        (m_pstNet2MediaEntry)->stipv6NetToMediaNetAdd.u6_addr.u6_uladdr);\
}

/*
 * Defect Id: BYAD09505
 * Description: IPv6:Address not going to tentative state after shutdown of
interface
 */
/* Get the Physical status of the interface */
/* AC4D01447 - Physical status always set to 0 for IF_STATUS_LOW_DOWN case
 * Modified by Prabhu H (71185) */
/* Santhosh : Modified to get get IPv6 link status
   Changed macro from IPB_IR_SIOCLINKSTATE to IPB_IR_SIOC6LINKSTATE
*/
#define IP6_ND_GETINTERFACEPHYSTATE(m_pstIf, m_ulPhyStatusisUp) \
{\
    ULONG  ulLinkStatus;\
    ULONG  ulSpoofing = 0;\
    if (IPB_IR_IF_ISSPOOFINGSET((m_pstIf)))\
    {\
        ulSpoofing = 1 ;\
    }\
    if (IPB_IR_PORT_TEMPLATE == IPB_IR_IF_GETPORTTYPE((m_pstIf)))\
    {\
        ulLinkStatus = IPB_IR_IF_STATUS_PROT_UP;\
    }\
    else\
    {\
        ulLinkStatus = IPB_IR_IF_PFLINKDOWNIOCtl((m_pstIf), \
                                               (ULONG)IPB_IR_SIOC6LINKSTATE\
                                                    , NULL );\
    }\
    switch (ulLinkStatus)\
    {\
        case IPB_IR_IF_STATUS_LOW_DOWN :   \
            (m_ulPhyStatusisUp) = 0; \
            break;\
        case IPB_IR_IF_STATUS_PROT_DOWN :   \
            if (IPB_IR_IF_ISSHUTDOWN((m_pstIf)))\
            {\
                (m_ulPhyStatusisUp) = 0;\
            }\
            else\
            {\
                (m_ulPhyStatusisUp) = 1;\
            }\
            break;\
        case IPB_IR_IF_STATUS_PROT_UP :  \
            (m_ulPhyStatusisUp) = 1;\
            break;\
        default :\
            if (ulSpoofing)\
            {\
                if (IPB_IR_IF_ISSHUTDOWN((m_pstIf)))\
                {\
                    (m_ulPhyStatusisUp) = 0; \
                }\
                else\
                {\
                    (m_ulPhyStatusisUp) = 1; \
                }\
            }\
            else\
            {\
                (m_ulPhyStatusisUp) = 1;\
            }\
            break ;\
    }\
}

/* This macro will traverse the Prefix list pointed by m_pstPrefixHead (which
 * can be static list or dynamic list) and compares the prefix information
 * with 'pstPfxToCmp'.  If it finds any matching prefix in the list, it stops
 * traversing entries and the macro invocation function will use 'm_pstPrefix'
 * for retrieving information on the matched prefix; else 'm_pstPrefix' will be
 * pointing to NULL */


#define IP6_ND_FIND_PFX_FROM_PFXLIST(m_pstPrefixHead, m_pstPrefix, m_pstPfxToCmp)\
{\
    (m_pstPrefix) = NULL;\
    for ((m_pstPrefix) = (m_pstPrefixHead); (m_pstPrefix) != NULL;\
                                        (m_pstPrefix) = (m_pstPrefix)->pstNext)\
    {\
        if (IN6_ARE_ADDR_EQUAL(&((m_pstPrefix)->stPrefix), (m_pstPfxToCmp)))\
        {\
            break;\
        }\
    }\
}


/* Added for AC4D01448 by Karthik */
#define IP6_ND_IS_INITIAL_RA_SCHEDULED(m_pstNDInfo) \
    ( ( ( 0 < (m_pstNDInfo)->stRAInfo.ulInitAdver ) \
       && ((m_pstNDInfo)->stRAInfo.ulInitAdver <= MAX_INITIAL_RTR_ADVERTISEMENTS))\
                                                                        ? 1 :0 )

#ifndef NO_USE
#define     NO_USE(var)     (VOID)(var)
#endif

/* This macro is used to set the current system + interval to be used for
   DAD & neighbor expiry */
#define IP6_ND_SET_TIME(m_pstVal, m_ulHighMilSec, m_ulLowMilSec, m_ulInterval)\
{\
    ULONG ulTmpHigTim = (m_ulHighMilSec);\
    ULONG ulTmpLowTim = (m_ulLowMilSec) + (m_ulInterval);\
    if (ulTmpLowTim < (m_ulLowMilSec))\
    {\
        ulTmpHigTim = (m_ulHighMilSec) + 1;\
    }\
    (m_pstVal)->ulExpireHigh = ulTmpHigTim;\
    (m_pstVal)->ulExpireLow = ulTmpLowTim;\
}

/* This macro is used to set the reachable time in seconds */
#define IP6_ND_SET_VAL_SEC(m_ulHighMilSec, m_ulLowMilSec, m_ulSecVal)\
{\
    ULONG ulTmp;\
    ulTmp = ((m_ulHighMilSec) << 16) | ((m_ulLowMilSec) >> 16);\
    (m_ulSecVal) = (ulTmp / 1000) << 16;\
    ulTmp = ulTmp % 1000;\
    ulTmp = (ulTmp << 16) | ((m_ulLowMilSec) & 0x0FFFF);\
    (m_ulSecVal) = (m_ulSecVal) + (ulTmp / 1000);\
}

/* IP6_ND_MALLOC will be used in ND module, to allocate inside ND Module.
   Similarly, IP6_ND_FREE will be used in ND module, only when the corresponding
   memory is allocated by ND module. If the pointer 'ptr' is NULL, then print
   an assert for debugging the bad pointer.*/

#define IP6_ND_MALLOC(m_ulInfo, m_ulSize)  TCPIP_Malloc((m_ulInfo), (m_ulSize))
#define IP6_ND_FREE(m_ptr)\
{\
    if (NULL != (m_ptr))\
    {\
        (VOID)TCPIP_Free((VOID *)m_ptr);\
        (m_ptr) = NULL;\
    }\
    else\
    {\
        VOS_DBGASSERT(0);\
    }\
}

/* Macros to fill PIO flags and PIO option length */
#define ND_OPT_PREFIX_LENGTH            4
#define ND_OPT_PI_FLAG_ONLINK           0x80
#define ND_OPT_PI_FLAG_AUTO             0x40


/* Length of MTU option */
#define ND_OPT_MTU_LENGTH        1

/****************************************************************************
 *                  Nd.h Changed for ND Host Feature support                *
 ****************************************************************************/

/* RFC 2461
   Host constants:

            MAX_RTR_SOLICITATION_DELAY          1 second
            RTR_SOLICITATION_INTERVAL           4 seconds
            MAX_RTR_SOLICITATIONS               3 transmissions

   Node constants:
            REACHABLE_TIME                      30,000 milliseconds
            RETRANS_TIMER                       1,000 milliseconds
*/

#define     IP6_ND_MAX_RTR_SOLICITATION_DELAY          1000
#define     IP6_ND_RTR_SOLICITATION_INTERVAL           4000
#define     IP6_ND_MAX_RTR_SOLICITATIONS               3

#define     IP6_ND_MAX_RTR_SOLICITATIONS_MINUS_ONE     2

/* Default Router Reachable time value in milliseconds */
#define     IP6_ND_DEF_REACHABLE_TIME                  30000

/* Default Router life time is zero */
#define IP6_ND_DEF_ROUTER_LIFETIME_ZERO                  0

/* Random Reachable Time Recomputation time - 1hour (3600000 milliseconds) */
#define     IP6_ND_DEF_RECOMP_TIME              3600000

/* Default Router lifetime MAX value (0-9000 Sec)*/
#define IP6_ND_MAX_ROUTER_LIFETIME              9000

/* Minimum Random Reachable Time Recomputation time - 1 min (60000 millisec) */
#define IP6_ND_MIN_RECOMP_TIME                  60000

/* Minimum Prefix length */
#define IP6_ND_PREFIX_LENGTH_MIN                48

/* Convert the randome number from ULONG to USHORT */
#define IP6_ND_GET_RANDOM_USHORT(m_ulRandom)                                \
    ((USHORT)((m_ulRandom) ^ (((m_ulRandom) >> IP6_ND_NO_OF_BITS_PER_USHORT)\
    & IP6_ND_USHORT_MASK)))

/* Bit Masks and BIT Definitions */
#define IP6_ND_NO_OF_BITS_PER_USHORT    (sizeof(USHORT) * 8)


#define IP6_ND_USHORT_MASK                      0xFFFF

#define IP6_ND_MAX_TM_PARA_LEN                  4

/* Invalid Timer-Id for Timer Wheel is 0xFFFFFFFF */
#define IP6_ND_TWL_INVALID_TIMER_ID             0xFFFFFFFF

/* Invalid Timer-Id for VOS Timer is 0 */
#define IP6_ND_VOS_INVALID_TIMER_ID             0

/* Invalid Waitlist ID */
#define IP6_ND_INVALID_WAITLIST_ID              0


/* Reachale time is computed by multiplying Base reachable time with a Radom
value between 0.5 to 1.5. To normalize the generted random number within the
range the following macros are used */
#define IP6_ND_REACHTIME_MAX_RAND_RANGE         100
#define IP6_ND_REACHTIME_MIN_RAND_RANGE         50

/* Max USHORT value */
#define IP6_ND_MAX_USHORT                       0xFFFF


#define IP6_IN6ADDR_LINKLOCAL_ALLROUTER_INIT \
{\
    {\
        {\
            0xff, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 \
        }\
    }\
}

/* Infinite Life time value */
#define IP6_ND_INFINITE_DURATION                0xFFFFFFFF

/* Max Lifetime value
Possible Max value is 0xFFFFFFFF, But when it is converted into millisec,
this will exceed the max ULONG. Hence we have chosen - 49 days (4233600)
i.e 49 days * 24 Hrs * 60 Min * 60 sec = 4233600 Seconds
4233600 Seconds * 1000 = 4233600000 MilliSec = FC579C00 < FFFFFF */
#define IP6_ND_MAX_LIFETIME_VAL                 (49 * 24 * 60 * 60) /* 49 Days*/

/* Maximum Prefix length value for IPv6 address */
#define IP6_ND_MAX_PREFIX_LENGTH                128

/* Minimum time (in seconds) an entry should be present in DEstination cache*/
#define IP6_ND_MIN_DEST_CACHE_LIFE              5
#define IP6_ND_WORD_LENGTH_IN_BITS              32

#define IP6_ND_BYTE_LENGTH_IN_BITS              8

/* void If Index ID */
#define IP6_ND_INDEX_IF_VOID               0x00000000
#define IP6_ND_NULL_CHAR                        '\0'

/* Macro to reset all the flags */
#define IP6_ND_RESET_FLAG                   0

/* Macro to fill LLA option length */
#define ND_OPT_LLA_LENGTH        1

/* Begin :Changes for AC4D05067 by Arvind's Review comment */
#define IP6_ND_TOTAL_NB_PER_BOARD                           0x01
#define IP6_ND_TOTAL_STATIC_NB_PER_BOARD                    0x02
#define IP6_ND_TOTAL_NB_PER_INTERFACE                       0x04

#define IP6_NULL_PARA          0
#define IP6_NULL_LOGID         0


/* Added by Anand - V1R7 Workspace Integration */
#define ND_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
                        (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))

/* Macro for unused variables */
#define ND_NOUSE(m_vVar)    (VOID)(m_vVar)

/* Begin: Changes for VLAN & VLANIF framework by karthik 70713 in Nov 2009 */

#define IP6_ND_L3_IF_VLAN               0


#define IP6_ND_MAX_VLAN_ID            4094
#define IP6_ND_MIN_VLAN_ID            1

/* End: Changes for VLAN & VLANIF framework by karthik 70713 in Nov 2009 */

/***************************************************************************/
/*                       Structures and Unions                             */
/****************************************************************************/

#ifndef _NDTIMER_
#define _NDTIMER_

/* ND timer */
typedef  struct tagND_Timer
{
    ULONG   ulTimerType;
    ULONG   ulTimerID;
    ULONG   ulIfIndex;

    /* to ensure the structure has 4 ulongs for vos que functionality */
    ULONG   ulReserved;
}ND_TIMER_S;
#endif

/* LLA option format */
typedef struct tagND_OPT_LLA
{
    UCHAR    ucType;
    UCHAR    ucLength;
    UCHAR    ucLLAddr[MACADDRLEN];
}ND_OPT_LLA_S;



#if(VRP_COMPILER_GHC_68000 == VRP_YES || VRP_COMPILER_GCC == VRP_YES)
#pragma  pack(1)
#elif(VRP_COMPILER_CC386 == VRP_YES)
#pragma  align(tagNDOptHdr = 1)
#endif

#ifdef TCPIP_SUPPORT_ARMCPU
#pragma    pack(1)
#endif

/* Option Header format */
typedef  struct tagNDOptHdr
{
    UCHAR    ucType;
    UCHAR    ucLength;
}ND_OPT_HDR_S;

#ifdef TCPIP_SUPPORT_ARMCPU
#pragma    pack(0)
#endif

#if(VRP_COMPILER_GHC_68000 == VRP_YES || VRP_COMPILER_GCC == VRP_YES)
#pragma  pack()
#elif(VRP_COMPILER_CC386 == VRP_YES)
#pragma  align
#endif

/* ND Prefix option format */
/* HCC error : No of elements in Structure is more than 5 - Obvious */
typedef struct tagNDOptPrefix
{
    UCHAR        ucType;
    UCHAR        ucLen;
    UCHAR        ucPrefixLen;
    UCHAR        ucFlagsReserved;
    ULONG        ulValidTime;
    ULONG        ulPreferredTime;
    ULONG        ulReserved2;
    IN6ADDR_S    stPrefix;
} ND_OPT_PREFIX_S;


/* ND MTU option format */
typedef struct tagNDOptMTU
{
    UCHAR        ucType;
    UCHAR        ucLen;
    BOOL_T       bReserved;
    ULONG        ulMTU;
} ND_OPT_MTU_S;


/* ND Option structure, parsed from the received messages */
typedef  union  tagNDOpt
{
    ND_OPT_HDR_S    *pstArray[6];    /* max = target address list */
    struct ND_OPT_EACH_S
    {
        ND_OPT_HDR_S      *pstOptZero;
        ND_OPT_HDR_S      *pstOptSrcLladdr;
        ND_OPT_HDR_S      *pstOptTgtLladdr;
        ND_OPT_PREFIX_S   *pstOptPrxBeg;   /* multiple opts, start */
        ND_OPT_HDR_S      *pstOptRh;
        ND_OPT_MTU_S      *pstOptMtu;
        ND_OPT_HDR_S      *pstOptSearch;   /* multiple opts */
        ND_OPT_HDR_S      *pstOptLast;     /* multiple opts */
        BOOL_T            bOptDone;       /* BOOL_T is of length USHORT */
        UCHAR             ucPadding[2];
        ND_OPT_PREFIX_S   *pstOptPrxEnd;   /* multiple opts, end */
    } stNdOptEach;
}ND_OPT_U;

/* Default Router List Structure */
/* HCC error : No of elements in Structure is more than 5 - Obvious */
typedef struct tagND_DefRouter_List
{
    /* DLL pointers */
    struct tagND_DefRouter_List *pNext;
    struct tagND_DefRouter_List *pPrev;

    /* Default Router Address */
    IN6ADDR_S   stIPv6Addr;

    /* Default Router State (PROB_REACHABLE/NOT_REACHABLE)*/
    IP6_ND_DEFRTRSTATE_E       enState;

    /* Timer Id of the associated Invalidation Timer */
    ULONG       ulTimerId;

    /* Time stamp updated when Router entry is newly created or lifetime
    of existing entries are updated */
    ULONG       ulLastChangeTime;

    /* Router lifetime */
    USHORT      usLifetime;

    UCHAR   aucPad[2]; /* Padding */
}IP6_ND_DEFROUTER_LIST_S;


/* Prefix List Addition Input parameters */
/* HCC error : No of elements in Structure is more than 5 - Obvious */
typedef struct tagND_Prefix_Param
{
    IN6ADDR_S stPrefix;     /* Prefix */
    ULONG ulValidLifetime;  /* Valid Lifetime of Prefix */
    ULONG ulPrefLifetime;   /* Preferred lifetime */
    UCHAR ucPrefixLen;      /* Prefix Length */
    UCHAR ucFlagsReserved;  /* L and A flag */
    USHORT usPad;           /* Padding */
}IP6_ND_PREFIX_PARAM_S;

/* Interface Level Prefix List Structure */
/* HCC error : No of elements in Structure is more than 5 - Obvious */
typedef struct tagND_IntfPrefix_List
{
    /* DLL pointers */
    struct tagND_IntfPrefix_List *pNext;
    struct tagND_IntfPrefix_List *pPrev;

    /* Prefix */
    IN6ADDR_S   stPrefix;

    /* Timer Id of the associated Invalidation Timer */
    ULONG ulTimerId;

    /* Valid Lifetime of Prefix */
    ULONG ulValidLifetime;

    /* Time stamp when the Prefix entry created/updated its lifetime */
    ULONG ulLastChangeTime;

    UCHAR ucPrefixLen;                /* Prefix Length */

    UCHAR aucPad[3]; /* for padding */

}IP6_ND_INTFPREFIX_LIST_S;


/* Global Prefix List Structure */
typedef struct tagND_GlobalPrefix_List
{
    /* Prefix */
    IN6ADDR_S   stPrefix;

    /* Interface Index */
    ULONG       ulIfnetIndex;

}IP6_ND_GLOBALPREFIX_LIST_S;


/* Destination Cache Structure */
/* HCC error : No of elements in Structure is more than 5 - Obvious */
typedef struct tagND_DestCache_Entry
{
    /* DLL pointers */
    struct tagND_DestCache_Entry *pNext;
    struct tagND_DestCache_Entry *pPrev;

    /* Destination Address */
    IN6ADDR_S   stDestAddr;

    /* Next hop Address */
    IN6ADDR_S   stNextHop;

    /* Time Stamp to Force Delete cache entries */
    ULONG       ulTimeStamp;

    /* Outgoing interface index */
    ULONG       ulOGIfnetIndex;

    /* Source of Route */
    ND_ROUTESOURCE_E  enSRCRoute;

    /*Back pointer to Radix tree External node  */
    VOS_RDX6_EXTNODE_S *pstExtNode;

   /* The folowing values are valid only if srcOfRoute is ND_ROUTESRC_SFIB */

    /* Zone Id */
    ULONG ulZoneId;

    /* Flags */
    ULONG ulFlags;

    /* AT Index */
    ULONG ulATIndex;

}IP6_ND_DESTCACHE_ENTRY_S;

/* Other configuration Parameters learned from RA message */
/* HCC error : No of elements in Structure is more than 5 - Obvious */
typedef struct tag_IP6_ND_RAOtherParams
{

    ULONG ulRetrans;        /* NS Retransmission time value */
    ULONG ulMTU;            /* IP6 link MTU value */
    ULONG ulBaseReachTime;  /* Base Reachable time */
    BOOL_T bIsMTUPresent;   /* Flag to indicate MTU option is received */
                            /* Bool is USHORT*/
    UCHAR ucHopLimit;       /* Hop limit */
    UCHAR ucPad;            /* Padding */
}IP6_ND_RAOTHERPARAMS_S;

/* RA Parameters Control message structure */
/* HCC error : No of elements in Structure is more than 5 - Obvious */
typedef struct tagIP6_ND_RAHostParams
{
    ULONG   ulIfIndex;                  /* Interface index */
    IP6_ND_RAOTHERPARAMS_S stRAParams;  /* other parameter advertised in RA */
    DLL_S   stPrefixHead;              /* Head node of Prefixes */
    IN6ADDR_S stRASrcAddr;              /* RA Source Address */
    UCHAR   ucMandOFlag;                /* M and O flag from RA */
    UCHAR   ucPad;                      /* Padding */
    USHORT  usRtrLifeTime;              /* Router Life time */
}IP6_ND_RAHOSTPARAMS_S;

/* Destination Cache Root node structure */
typedef struct tagIP6_ND_DestCacheGblParam
{
    /* Root Node of Destination Cache Radix tree */
    VOS_RDX6_INTNODE_S *pstDestCacheRootNode;

    /* DLL List for destination cache entries for LRU */
    DLL_S stDestCacheHead;

    /* Reference to L1 DestCache*/
    IP6_ND_DESTCACHE_ENTRY_S *pstL1DestCache;
}IP6_ND_DESTCACHEGBLPARAM_S;

typedef struct tagIP6_ND_PrefixNode
{
    VOS_RDX6_INTNODE_S *pstNDPfxRootNode;
}IP6_ND_PREFIXNODE_S;

/* Global list contains the interfaces which as Default Router(s) */
typedef struct tagIP6_ND_IntfDefRtrAvailNode
{
    /* DLL pointers */
    struct tagIP6_ND_IntfDefRtrAvailNode *pNext;
    struct tagIP6_ND_IntfDefRtrAvailNode *pPrev;

    ULONG ulHandle;     /* Holds the interface index, which has Def Router(s) */
}IP6_ND_INTFDEFRTRAVAILNODE_S;

/*
 *  Structure for storing Next hop Information retieved by
 *  Destination cache | Prefix list | FIB | Default Router Look UP
 */
/* HCC error : No of elements in Structure is more than 5 - Obvious */
typedef struct tag_NHINFO_S
{
    ULONG ulIfIndex;             /* out going interface */
    IN6ADDR_S stNexthopAddr;     /* Next hop address */
    ND_ROUTESOURCE_E enSRCRoute;  /* Source of route as in
                                    destination cache entry */
    ULONG ulFlags;               /* Flags set for FIB | Default router look UP*/
    ULONG ulZoneId;              /* ZoneId */
    ULONG ulATIndex;             /* AT Index */
    ULONG ulIsDestCacheHit;      /* Will be set to ND_TRUE only if the next hop
                                    determination is due to Destination cache
                                    Hit */
}NHINFO_S;

/* Waitlist helper structure */
typedef struct tagIP6_ND_WLHelper_Info
{
    DLL_S *pstHead;             /* DLL list head node */
    VOID *pstCurNode;           /* current node protected by the WL */
    UINTPTR ulWaitListHandle;     /* waitlist handle */
    ULONG ulIfIndex;            /* Interface index */
}IP6_ND_WLHELPER_INFO_S;

/* Added By Rajat Phull for */
/* Waitlist helper structure */
typedef struct tagIP6_ND_NB_WLHelper_Info
{
    VOID *pstCurNode;            /* current node protected by the WL */
    UINTPTR ulWaitListHandle;      /* waitlist handle */
    VOID *pvNDInfo;              /* Pointer to ND Info Structure */
}IP6_ND_NB_WLHELPER_INFO_S;

/* Control Message Strucutre */
typedef struct tagIP6_ND_CTRLMSG
{
    ULONG   ulCtrlMsgType;      /* Control message type */
    ULONG   ulIfIndex;          /* Interface Index */
    VOID    *pvDataPtr;         /* Message Data Ptr */
    ULONG   ulReserved;         /* Reserved for future use*/
}IP6_ND_CTRLMSG_S;


/* The ADD NB information structure  */
typedef struct tagIP6_ND_ADDNBMSG
{
    UCHAR ucIsRouter;
    UCHAR ucState;
    UCHAR ucIsStatic;
    UCHAR ucPad;
    ND_PKT_CTLPARAM_S stNDCtrlParam;
}IP6_ND_ADDNBMSG_S;

/* End: Changes for VLAN & VLANIF framework by karthik 70713 in Nov 2009 */

/* Holds all ND Host related parameters to be stored for each interface */
/* HCC error: Structure having more than 5 elements - Obvious */
typedef struct tagIP6_ND_HostParams
{
    ULONG           ulCurHopLimit;          /* Hop limit Learned from RA */
    ULONG           ulBaseReachableTime;    /* Base Reachabletime */
    ULONG           ulRSRetransCount;       /* RS Re-transmission count */
    ULONG           ulRecomputeTimerVal;    /* Random Reachable time
                                               Recomputation timer Value */
    ULONG           ulRecomputeTimerID;     /* Random Reachable time
                                               Recomputation timer id */
    ULONG           ulRsRetransTimerID;     /* RS Retransmission timer id */
    DLL_S           stDefRouterList;        /* Default Router list head node */
    DLL_S           stPrefixList;           /* Prefix list head node */
    UCHAR           ucStoredMandOFlag;      /* Stored M and O flag */
    UCHAR           ucNotifyMORAFlag;       /* Notification given to Adaptor
                                               M and O flag or Absence of RA */
    BOOL_T          bIsValidRAReceived;     /* Flag to check Valid RA received*/
}IP6_ND_HOSTPARAMS_S;


/***************************************************************************/
/*                              Enums                                      */
/***************************************************************************/

/* Timer Message Types */
typedef enum tagIP6_ND_Host_TimerMsg_Type
{
    IP6_ND_TMRMSG_RECOMPUATION = 0, /* Reachable time recomputation timer */
    IP6_ND_TMRMSG_RSRETRANS,        /* RS retransmission timer */
    IP6_ND_TMRMSG_DEFROUTER,        /* Default Router invalidation timer */
    IP6_ND_TMRMSG_PREFIXLIST,       /* Prefix list invaildation timer */
    IP6_ND_TMRMSG_MAX,
    IP6_ND_TMRMSG_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE
}IP6_ND_HOST_TIMERMSG_TYPE_E;

/* Control message type enum */
typedef enum tagIP6_ND_Host_CtrlMsg_Type
{
    IP6_ND_CTRLMSG_STFADDR = 0, /* Stateful Address configuration */

    /* Stateful Address Not used notification to Adaptor */
    IP6_ND_CTRLMSG_STFADDRNOTUSED,
    IP6_ND_CTRLMSG_STFOTHERCFG,
    IP6_ND_CTRLMSG_RAPROC,
    IP6_ND_CTRLMSG_MAX,
    IP6_ND_CTRLMSG_MAX_ULONG = IP6_ND_MAX_ENUM_VALUE

}IP6_ND_HOST_CTRLMSG_TYPE_E;


/* Type of Operation */
typedef enum tagIP6_TYPE_OF_OPERATION
{
    IP6_MULTICAST_OPERATION,
    IP6_UNICAST_OPERATION,
    IP6_ENUM_OPERATION_PAD = IP6_ND_MAX_ENUM_VALUE
}IP6_TYPE_OF_OPERATION_E;


/* Enumeration constants for neighbor entry on product */
typedef enum tagPRINTPRODUCTINFO
{
    IP6_PRINT_PRODUCTINFO_IP6NB = 0,
    IP6_PRINT_PRODUCTINFO_IP6ENTRY,
    IP6_ENUM_PRODUCT_PAD = IP6_ND_MAX_ENUM_VALUE
}ND_PRINT_PRODUCT_INFO_S;


/* Added by Suraj_R for NP Support */

#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)

#define IP6_ND_NOTIFY_NP(ulOper, pvInfo, ulIfIndex) \
        ((g_pfIP6_ND_PPIOperation)?IP6_ND_Notify_PPI(ulOper, \
                                pvInfo, ulIfIndex): VOS_OK)

#define IP6_ND_NP_SHOWDEBUG_ADDR_INTF(ulDbgId, ulIfIndex, stIPv6Addr) \
{                                                                 \
    CHAR  szAddr[BUFF_50] = "\0";                                 \
    if (VOS_ERR != g_stNDCallBack.pfIP6_ND_SH_Addr6ToStr(         \
                      &stIPv6Addr, szAddr))                       \
    {                                                             \
        if (VRP_YES == g_ulNDDebugFlag)                            \
        {                                                         \
            (VOID)IP6_ND_CORE_DEBUG(ulDbgId, szAddr,                  \
            IPB_IR_IF_GETIFNAMEBYINDEX(ulIfIndex));    \
        }                                                         \
    }                                                             \
}


#define IP6_ND_NP_SHOWDEBUG_INTF(ulDbgId, ulIfIndex)              \
{                                                                 \
    if (VRP_YES == g_ulNDDebugFlag)                      \
    {                                                             \
        (VOID)IP6_ND_CORE_DEBUG(ulDbgId,                              \
        IPB_IR_IF_GETIFNAMEBYINDEX(ulIfIndex));    \
    }                                                             \
}


#define IP6_ND_NP_SHOWDEBUG_PREF_LEN_INTF(ulDbgId, ulIfIndex, stIPv6Addr, ulPrefixLength) \
{                                                                 \
    CHAR  szAddr[BUFF_50] = "\0";                                 \
    if (VOS_ERR != g_stNDCallBack.pfIP6_ND_SH_Addr6ToStr(         \
                      &stIPv6Addr, szAddr))                       \
    {                                                             \
        if (VRP_YES == g_ulNDDebugFlag)                         \
        {                                                         \
            (VOID)IP6_ND_CORE_DEBUG(ulDbgId, szAddr, ulPrefixLength,  \
             IPB_IR_IF_GETIFNAMEBYINDEX(ulIfIndex));    \
        }                                                         \
    }                                                             \
}

#else

#define IP6_ND_NOTIFY_NP(ulOper, pvInfo, ulIfIndex) VOS_OK
#define IP6_ND_NP_SHOWDEBUG_ADDR_INTF(ulDbgId, ulIfIndex, stIPv6Addr)
#define IP6_ND_NP_SHOWDEBUG_INTF(ulDbgId, ulIfIndex)
#define IP6_ND_NP_SHOWDEBUG_PREF_LEN_INTF(ulDbgId, ulIfIndex, stIPv6Addr, ulPrefixLength)

#endif


#define IP6_ND_FLAG_ISSET(pstIPv6CtlBlk, flag) \
                        ((pstIPv6CtlBlk)->ucFlag & (flag))

#define IP6_ND_FLAG_DO_SET(pstIPv6CtlBlk, flag) \
                        ((pstIPv6CtlBlk)->ucFlag |= (flag))

#define IP6_ND_FLAG_DO_RESET(pstIPv6CtlBlk, flag) \
                        ((pstIPv6CtlBlk)->ucFlag &= (~(flag)))

#define IP6_ND_NOTIFY_INCOMING_FLOW(m_ulIfIndex, m_pstMBuf) \
        ((g_stNDFlowCallback.pfIP6_ND_Incoming_Flow_Callback)? \
        g_stNDFlowCallback.pfIP6_ND_Incoming_Flow_Callback(m_ulIfIndex, m_pstMBuf) \
        : VOS_OK)

#define IP6_ND_UPDATE_MBUF_VPNID(pstMBuf, pstIfNet)  \
{ \
    IP6IFNET_S *pstIp6If = NULL; \
    pstIp6If = (IP6IFNET_S *)IPB_IR_IF_GETIPV6CTLBLK(pstIfNet); \
    if (NULL != pstIp6If) \
    { \
        MBUF_SET_TAG_MPLS_VPNID(pstMBuf, (ULONG)(pstIp6If->usVrfIndex)); \
    } \
}

#ifdef        __cplusplus
}
#endif        /* end of __cplusplus */

#endif        /* end of _ND_H_ */

