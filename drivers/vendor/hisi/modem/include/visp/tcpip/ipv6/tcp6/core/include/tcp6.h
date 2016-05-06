
/*****************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------
*                              tcp6.h
*
*    Project Code:  VRP5.0
*    Module Name:  IP6 TCP6
*    Version     : Initial Draft
*    Create Date:  2003/06/27
*    Author:       Naina Gupta
*    Description: TCP6 header flags and generic macros defined
*-----------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------
*  2003-06-27  Naina Gupta    Create
*  2006-06-06  Alok       Updated for 14 Fly-Check rules adherence
*                         for IPOSIR-V1R1-IPv6
******************************************************************
*/

#ifndef _TCP6_H
#define _TCP6_H

#ifdef    __cplusplus
extern    "C"{
#endif

/* Constant definition for TCP header options */
#define TCP6OPT_EOL                      0L
#define TCP6OPT_NOP                      1L
#define TCP6OPT_MAXSEG                   2L
#define TCP6OLEN_MAXSEG                  4L
#define TCP6OPT_WINDOW                   3L
#define TCP6OLEN_WINDOW                  3L
#define TCP6OPT_SACK_PERMITTED           4L
#define TCP6OLEN_SACK_PERMITTED          2L
#define TCP6OPT_SACK                     5L
#define TCP6OPT_TIMESTAMP                8L
#define TCP6OLEN_TIMESTAMP               10L
#define TCP6OLEN_TSTAMP_APPA             (TCP6OLEN_TIMESTAMP + 2)
#define TCP6OPT_TSTAMP_HDR \
            ((TCP6OPT_NOP<<24) | (TCP6OPT_NOP<<16) | (TCP6OPT_TIMESTAMP<<8)\
            | TCP6OLEN_TIMESTAMP)

#define TCP6_MSS                         1024
#define TCP6_INITIAL_SEQ                 0

/*Added by likaikun00213099, 修改支持MCCP信令面设置MSS, 2013/12/18 */
/* the max ethernet mtu is 1500,
*  decrease IP6 head(40),TCP6 head(20)
*/
#define TCP6_MAX_ETH_MSS 1440 

/* largest value for (unscaled) window */
#define TCP6_MAXWIN                      65535L

#define TCP6_MAX_WINSHIFT        14              /* maximum window shift */

/* Reason: To handle the scenario when there is no parallel BGP server */
#define SUCCESS_IN6PCB_SEARCHSECOND 1

/* The following definations are added for PSOS version, LQZ. */
#ifndef TCP6_MIN
#define TCP6_MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef TCP6_MAX
#define TCP6_MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef roundup
#define roundup(x, y)   ((((x) + ((y) - 1)) / (y)) * (y))
#endif

#if (ARM_SUPPORT == VRP_YES)
#define TCP6_CHECK_MEMORYADDRESS(pstPointer)   \
{\
    if (0 != (((ULONG)(pstPointer)) % 4 ))\
    {\
        VOS_DBGASSERT(0);\
    }\
}
#else
#define TCP6_CHECK_MEMORYADDRESS(pstPointer)
#endif

/*symbolic constants replace magic numbers*/
#define TCP6_BUF_4          4
#define TCP6_BUF_5          5
#define TCP6_BUF_10         10
#define TCP6_BUF_12         12
#define TCP6_BUF_16         16
#define TCP6_BUF_30         30
#define TCP6_BUF_32         32
#define TCP6_BUF_96         96
#define TCP6_BUF_100        100
#define TCP6_BUF_128        128
#define TCP6_BUF_256        256
#define TCP6_BUF_512        512


/* Default hop limit to be used for tcp6 response packet when
   TCP6CB doesnot exist */
/* #define TCP6_DEF_HOP_LIMIT  255 - Commented by Anand S */

/*Input flag values for TCP6_TransaOutput function*/
#define TCP6_PRINT_SOCK_PAIR_OFF    0L
#define TCP6_PRINT_SOCK_PAIR_ON     1L

#define TCP6_DISP_STR_BOUND         26
#define TCP6_KILOBITS               1024


#define TCP6_SYN_TIMEOUT_MIN 2
#define TCP6_SYN_TIMEOUT_MAX 600
#define TCP6_FIN_TIMEOUT_MIN 76
#define TCP6_FIN_TIMEOUT_MAX 3600
#define TCP6_WINDOW_SIZE_MIN 1
#define TCP6_WINDOW_SIZE_MAX 32


/* For VISP LOG Framework */
#define IP6_NULL_LOGID     0
#define IP6_NULL_PARA      0


/* Added by Anand - V1R7 Workspace Integration */
#define TCP6_MEM_ZERO(m_pBufPtr, m_ulBufLen)\
                        (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), 0, (m_ulBufLen))

/* Added by Anand - V1R7 Workspace Integration */
#define TCP6_MEM_SET(m_pBufPtr, m_cBufVal, m_ulBufLen)\
            (VOID)TCPIP_Mem_Set((CHAR *)(m_pBufPtr), (m_cBufVal), (m_ulBufLen))
            

#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
