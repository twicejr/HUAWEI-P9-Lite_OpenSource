/*******************************************************************************
*                          icmp6_typ.h
*  Project Code    : VRP3.0
*  Author          : Mayun  / Mahaveer Jain
*  Create Date     : 2002-8-20
*  Version         :
*  Description     : 本文件是icmp6.c文件
*  Others          :
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
* 2006-09-14   Alok             Updated for 14 Fly-Check rules adherence
*                               for IPBIRV1R2.IPv6
*-------------------------------------------------------------------------------
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.
*                      ALL RIGHTS RESERVED
*******************************************************************************/
#ifndef _ICMP6_typ_H_
#define _ICMP6_typ_H_

#ifdef  __cplusplus
extern "C"{
#endif

#define SID_ICMP6_ERROR                   1
#define SID_ICMP6_CTLOUTPUT               2
#define SID_ICMP6_RIP6_INPUT              3
#define SID_ICMP6_INPUT_EXTHDR_GET        4
#define SID_ICMP6_INPUT_RAWCOPY           5
#define SID_ICMP6_INPUT_RAWCOPY_RA        6
#define SID_ICMP6_INPUT_RAWCOPY_RS        7
#define SID_ICMP6_INPUT_RAWCOPY_NA        8
#define SID_ICMP6_INPUT_RAWCOPY_NS        9
#define SID_ICMP6_ERROR_EXTHDR_GET        10
#define SID_ICMP6_REFLECT_COPY            11
#define SID_ICMP6_REFLECT_PREPREND        12
#define SID_ICMP6_RIP6_INPUT_EXTHDR_GET   13
#define SID_IP6_ICMP6_REDIRECT            14
#define SID_ICMP6_NOTIFYERROR             15
#define SID_ICMP6_TIMER                   16

#define IP6_ICMP6_ICMP6  ((SYSTRC_IPV6_ICMP6_BASE << 8) + 1)
#define IP6_ICMP6_INIT   ((SYSTRC_IPV6_ICMP6_BASE << 8) + 3)
#define IP6_ICMP6_IICMP  ((SYSTRC_IPV6_ICMP6_BASE << 8) + 4)
#define IP6_ICMP6_FAC    ((SYSTRC_IPV6_ICMP6_BASE << 8) + 5)

/* Debug related macros */
/* Begin : Defect ID: D001104, Modifier:Rajesh,   Date:2004/9/13
   Reason : since No increment of statistics in I/O Board */
#define ICMP6_BADCODE    3
#define ICMP6_BADLEN     4
#define ICMP6_SUPPRESSERR  5
#define ICMP6_BADSRCADDR   6
#define ICMP6_GETEXTHDRFAILED1      7
#define ICMP6_ERRTYPEERREDIRECT     8
#define ICMP6_LONGPKTCUTTAILFAILED  9
#define ICMP6_PREPENDFAILEDERR     10
#define ICMP6_GETIFFAILED          11
#define ICMP6_GETIFADDRWITHBESTPREFIXFAILED1 12
#define ICMP6_CANTFINDSRCADDR  13
#define ICMP6_SERCHFIBFAILED   14
#define ICMP6_RFLMBUFISNULL    15
#define ICMP6_OFFSETERR        16
#define ICMP6_COPYIPHDRFAILED  17
#define ICMP6_MAKEMEMCONTINUE  18
#define ICMP6_UNKNOWNINFOPKT   19
#define ICMP6_ICMP6PKTLENTHERR   20
#define ICMP6_GETPSTFIELDFAILED  21
#define ICMP6_SPECIFYHOSTORRTFAILED  22
#define ICMP6_DSTADDRISMULTICAST   23
#define ICMP6_MALLOCFAILED     24
#define ICMP6_CREATEMBUFFAILED 25
#define ICMP6_GETLLADDRFAILED  26
#define ICMP6_RDTGTADDRERR     27
#define ICMP6_CONCATBUFFER     28
#define ICMP6_ERRMBUFISNULL    29
#define ICMP6_INVALIDPOINTER   30
#define ICMP6_INMBUFNULL       31
#define ICMP6_NTFMBUFNULL      32
#define ICMP6_RDCTOUTMBUFNULL  33
#define ICMP6_DSCDTLFAILED     34
#define ICMP6_OFFSETSHORT      35
#define ICMP6_GETIPHDRFAILED   36
#define ICMP6_SANITYCHECKFAILED  37
#define ICMP6_GETLLIFFAILED    38
#define ICMP6_GETMULTICASRIFFAILED  39
#define ICMP6_PREPENDFAILEDRFL  40
#define ICMP6_GETIFADDRWITHBESTPREFIXFAILED2 41
#define ICMP6_GETIFADDRWITHBESTPREFIXFAILED3 42
#define ICMP6_GETIFADDRWITHBESTPREFIXFAILED4 43
#define ICMP6_GETEXTHDRFAILED2  44
#define ICMP6_GETEXTHDRFAILED3  45
#define ICMP6_GETEXTHDRFAILED4  46
#define ICMP6_GETEXTHDRFAILED5  47
#define ICMP6_GETEXTHDRFAILED6  48
#define ICMP6_GETEXTHDRFAILED7  49
#define ICMP6_GETEXTHDRFAILED8  50

/* Added by Alok 70823 on 16 Nov 2006 for AC4D01159 */
#define ICMP6_DISCARDPACKET     51
#define ICMP6_NOTIFYUPPERLAYER  52

#define ICMP6_NP_GETGLOBALSTATS 53
#define ICMP6_NP_GETINTFSTATS   54
#define ICMP6_NP_GETSTATPERTYPE 55

#define ICMP6_NP_RESETGLOBALSTATS 56
#define ICMP6_NP_RESETINTFSTATS   57
#define ICMP6_NP_RESETSTATPERTYPE 58

#define ICMP6_BADDSTADDR   59
/* Start: RFC4443 compliance changes */
/* Rate Limit (Too Big/Error) related macros */
#define IP6_ICMP6_DEFAULT_ERRORRATE_INTERVAL     10000 /* 10 secound */
/* End: RFC4443 compliance changes */

#define IP6_ICMP6_DEFAULT_TOCKENS                10  /* 10 Tockens*/
#define IP6_ICMP6_TIMER_UNIT                     10
#define IP6_ICMP6_TOOBIG_ERROR_TIMER            1000 /* 1000 Millisecs */
#define IP6_ICMP6_DEFAULT_TOKENS                5   /* For default Tokens */

#define IP6_ICMP6_MAX_HOPLIMIT                 255

#define IP6_ICMP6_INTERFACE_ADDRESS_LENGTH     6

#define IP6_ICMP6_ROUND_LENGTH                 7

#define IP6_ICMP6_INVALID_OFFSET              -1

/* IPV6_MMTU - sizeof(struct ip6_hdr) - sizeof(struct icmp6_hdr) */
#define ICMPV6_PLD_MAXLEN    1232

/* ND option macros */
#define ND_OPT_SOURCE_LINKADDR      1
#define ND_OPT_TARGET_LINKADDR      2
#define ND_OPT_PREFIX_INFORMATION   3
#define ND_OPT_REDIRECTED_HEADER    4
#define ND_OPT_MTU                  5
#define ND_OPT_ADVINTERVAL          7  /* 2292bis-02 */
#define ND_OPT_HOMEAGENT_INFO       8  /* 2292bis-02 */
#define ND_OPT_SOURCE_ADDRLIST      9  /* will be renamed */
#define ND_OPT_TARGET_ADDRLIST      10 /* will be renamed */



/* For VISP log FrameWork */
#define IP6_NULL_PARA   0
#define IP6_NULL_LOGID  0

/* To remove L4 warning regarding unused function arguments */
#ifndef NO_USE
#define NO_USE(macro_var)     (VOID)(macro_var)
#endif

#define BUFF_50 50

/* Copy IP6 Address from the Structure to the ULONG */
#define ICMP6_COPY_IP6ADDR_STRUCT_TO_ARRAY(macro_dst,macro_src)\
{\
    (macro_dst)[0] = (macro_src)->s6_addr32[0];\
    (macro_dst)[1] = (macro_src)->s6_addr32[1];\
    (macro_dst)[2] = (macro_src)->s6_addr32[2];\
    (macro_dst)[3] = (macro_src)->s6_addr32[3];\
}

/* Copy IP6 Address from the ULONG to the Structure */
#define ICMP6_COPY_IP6ADDR_ARRAY_TO_STRUCT(macro_dst,macro_src)\
{\
    (macro_dst)->s6_addr32[0] = (macro_src)[0];\
    (macro_dst)->s6_addr32[1] = (macro_src)[1];\
    (macro_dst)->s6_addr32[2] = (macro_src)[2];\
    (macro_dst)->s6_addr32[3] = (macro_src)[3];\
}

/* Reason : Source address should not be selected as
            link local address */
#define ICMP6_SET_ADDR_UNSPECIFIED(macro_addr)\
{\
    ((macro_addr)->s6_addr32[0] = 0);\
    ((macro_addr)->s6_addr32[1] = 0);\
    ((macro_addr)->s6_addr32[2] = 0);\
    ((macro_addr)->s6_addr32[3] = 0);\
}

/* Error type is from 0 to 127 */
#define IS_ICMP6_TYPE_ERROR(macro_type) \
                        ((macro_type) < ICMP6_ECHO_REQUEST)

/* Invalid type and code for debugging purpose */
#define IP6_INVALID_ICMP_TYPE       0xFFFF
#define IP6_INVALID_ICMP_CODE       0xFFFF

/* Neighbor discovery option header */
typedef struct tagIP6_REDIRECT_OPT_HDR_S
{
    UCHAR   ucNdOptType;
    UCHAR   ucNdOptLen;

    /* followed by option specific data*/
} IP6_REDIRECT_OPT_HDR_S;

/* redirected header */
typedef struct tagND_OPT_RD_HDR
{
    UCHAR   ucNd_opt_rh_type;
    UCHAR   ucNd_opt_rh_len;
    USHORT  usNd_opt_rh_reserved1;
    ULONG   ulNd_opt_rh_reserved2;

    /* followed by IP header and data */
} /*__attribute__((__packed__))*/ ND_OPT_RD_HDR_S;

/* structures required for redirect routines */
typedef struct tagREDIRECT {
    ICMP6_S        stNd_rd_hdr;
    IN6ADDR_S      stNd_rd_target;     /* target address */
    IN6ADDR_S      stNd_rd_dst;        /* destination address */
    /* could be followed by options */
}REDIRECT_S;

#ifndef MACADDRLEN
#define MACADDRLEN 6
#endif

#define ICMP6_SEND_LOG g_stICMP6CallbackFun.pfIP6_ICMP6_SH_LogToIPOSIC
#define ICMP6_SEND_STR_DBG(DbgStr)    \
    g_stICMP6CallbackFun.pfIP6_ICMP6_SH_DbgToIPOSIC(ICMP6_DBGID_STR, DbgStr)


#define ICMP6_MAC_DST_MCAST_OR_BCAST(macro_enaddr) ((macro_enaddr)[0] & 0x01)

/* IP6_ICMP6_MALLOC will be used in ICMP6 module, only when this
 * allocated memory will be used and freed inside ICMP6 module.
 * Similarly, IP6_ICMP6_FREE will be used in ICMP6 module, only
 * when the corresponding memory is allocated by ICMP6 module.
 * If the pointer 'ptr' is NULL, then print an assert for
 * debugging the bad pointer.
 */
#define IP6_ICMP6_MALLOC(macro_ulInfo, macro_ulSize) \
                                    TCPIP_Malloc((macro_ulInfo), (macro_ulSize))
#define IP6_ICMP6_FREE(macro_ptr)\
{\
    if (NULL != (macro_ptr))\
    {\
        (VOID)TCPIP_Free(macro_ptr);\
        (macro_ptr) = NULL;\
    }\
    else\
    {\
        VOS_DBGASSERT(0);\
    }\
}

/* Macro for unused variables */
#define ICMP6_NOUSE(m_vVar)    (VOID)(m_vVar)

/* Start: RFC4443 compliance changes */
/* Macro to check if Destination not reachable error is enabled in that
   interface or not */
/*   Note: Incase of receive ifindex not set, then there may be a case
           in which icmp6 error message is generated for the message
           which is yet to be send. In such scenarios, this check is
           bypassed */
#if (VRP_MODULE_MINI == VRP_YES)
#define IP6_ICMP6_CHK_DEST_UNREACH_ERR_ENBL(m_ulIfIndex, m_ucType, m_bResult)\
{\
    VOID         *m_pstIfNet = NULL;\
    m_bResult = BOOL_FALSE;\
    m_pstIfNet = IPB_IR_IF_GETIFBYINDEX(m_ulIfIndex);\
    if (NULL == m_pstIfNet)\
    {\
        goto m_end;\
    }\
    m_end:\
    ;\
}    
#else
#define IP6_ICMP6_CHK_DEST_UNREACH_ERR_ENBL(m_ulIfIndex, m_ucType, m_bResult)\
{\
    IP6IFNET_S   *m_pstIp6If = NULL;\
    VOID         *m_pstIfNet = NULL;\
    m_bResult = BOOL_FALSE;\
    m_pstIfNet = IPB_IR_IF_GETIFBYINDEX(m_ulIfIndex);\
    if (NULL == m_pstIfNet)\
    {\
        goto m_end;\
    }\
    m_pstIp6If = (IP6IFNET_S *)IPB_IR_IF_GETIPV6CTLBLK(m_pstIfNet);\
    if (NULL == m_pstIp6If)\
    {\
        m_bResult = BOOL_TRUE;\
        goto m_end;\
    }\
    if ((ICMP6_DST_UNREACH == m_ucType)\
        && (BOOL_FALSE== m_pstIp6If->stIcmp6Info.bDestUnReachErrEnbl))\
    {\
        m_bResult = BOOL_TRUE;\
    }\
    m_end:\
    ;\
}
#endif
/* Macro to check memory address */
#define IP6_ICMP6_CHK_MEMORYADDRESS(m_pstOldIp6, m_pstMBuf, bResult)\
{\
    bResult = BOOL_TRUE;\
    if (IPB_IR_CHECK_MEMORYADDRESS (m_pstOldIp6))\
    {\
        VOS_DBGASSERT(0);\
        if (NULL != m_pstMBuf)\
        {\
            IPB_IR_MBUF_DESTROY(m_pstMBuf);\
        }\
        bResult = BOOL_FALSE;\
    }\
}

/* Macro to check if the error code falls into any reserved or private scope*/
#define IP6_ICMP6_CHK_RSVD_PVT_ERR(m_ucType, m_bResult)\
{\
    m_bResult = BOOL_FALSE;\
    if ((ICMP6_RSVD_ERR_TYPE == m_ucType) ||\
       (ICMP6_RSVD_INFO_TYPE == m_ucType) ||\
       (ICMP6_PVT_ERR_TYPE1  == m_ucType) ||\
       (ICMP6_PVT_ERR_TYPE2  == m_ucType) ||\
       (ICMP6_PVT_INFO_TYPE1  == m_ucType) ||\
       (ICMP6_PVT_INFO_TYPE2  == m_ucType))\
    {\
        m_bResult = BOOL_TRUE;\
    }\
}

#define IP6_ICMP6_CALC_CLK_TIME_INVL(m_ulClockTime, m_ulInterval)\
{\
    m_ulClockTime = m_ulInterval/g_ulIcmp6_FillErrorRate;\
}

#define IP6_ICMP6_RELEASE_TOKENS(m_ulTokens, m_ulTotalTokens)\
{\
    m_ulTokens += m_ulTotalTokens/g_ulIcmp6_FillErrorRate;\
}

/* End: RFC4443 compliance changes */
#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _ICMP6_TYP_H_ */



