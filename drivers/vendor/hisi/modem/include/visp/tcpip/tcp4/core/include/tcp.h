/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp.h
*
*  Project Code: VISP1.5
*   Module Name: IP TCP4  
*  Date Created: 1996-12-26
*        Author: 刘庆智
*   Description: TCP自有数据结构
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  1996-12-26  刘庆智           Create the first version.
*
*******************************************************************************/

#ifndef _TCP_STRUCT_H
#define _TCP_STRUCT_H

#ifdef  __cplusplus
extern  "C"{
#endif

#include "tcpip/tcp4/include/tcp_api.h"

#define  SYSTRC_IPV4_TCP4_BASE       01
#define IP4_TCP4_TCP4_USR  ((SYSTRC_IPV4_TCP4_BASE << 8) + 1) 
#define IP4_TCP4_TCP4_SH_CFG  ((SYSTRC_IPV4_TCP4_BASE << 8) + 2) 
#define IP4_TCP4_TCP4_IN  ((SYSTRC_IPV4_TCP4_BASE << 8) + 3) 
#define IP4_TCP4_TCP4_OUT  ((SYSTRC_IPV4_TCP4_BASE << 8) + 4)
#define IP4_TCP4_TCP4_SH_INIT ((SYSTRC_IPV4_TCP4_BASE << 8) + 5)
#define IP4_TCP4_TCP4_SH_IC ((SYSTRC_IPV4_TCP4_BASE << 8) + 6)
#define IP4_TCP4_TCP4_INIT  ((SYSTRC_IPV4_TCP4_BASE << 8) + 7)
#define IP4_TCP4_TCP4_FUN  ((SYSTRC_IPV4_TCP4_BASE << 8) + 8) 
#define IP4_TCP4_TCP4_TIMER  ((SYSTRC_IPV4_TCP4_BASE << 8) + 9)
#define IP4_TCP4_TCP4_FAC  ((SYSTRC_IPV4_TCP4_BASE << 8) + 10)
#define IP4_TCP4_TCP4_INT  ((SYSTRC_IPV4_TCP4_BASE << 8) + 11)



/* Constant defination for TCP-IP header flags */
#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PUSH 0x08
#define TH_ACK  0x10
#define TH_URG  0x20

/* Constant defination for TCP header options */
#define TCPOPT_EOL                              0L
#define TCPOPT_NOP                              1L
#define TCPOPT_MAXSEG                   2L
#define TCPOLEN_MAXSEG                  4L
#define TCPOPT_WINDOW                   3L
#define TCPOLEN_WINDOW                  3L
#define TCPOPT_SACK_PERMITTED   4L
#define TCPOLEN_SACK_PERMITTED  2L
#define TCPOPT_SACK                             5L
#define TCPOPT_TIMESTAMP                8L

/* TCP with MD5 authentication, zhangfeng, 2002,07,20 */
/* Option code of TCP MD5 option = 19 */
/* Total length of TCP MD5 option = 1 code + 1 length + 16 digest */
#define TCPOPT_MD5PASS                  19
#define TCPLEN_MD5PASS                  20
/* TCP with MD5 authentication, zhangfeng, 2002,07,20 */


#define TCPOLEN_TIMESTAMP               10L
#define TCPOLEN_TSTAMP_APPA             (TCPOLEN_TIMESTAMP + 2)
#define TCPOPT_TSTAMP_HDR \
            ((TCPOPT_NOP<<24) | (TCPOPT_NOP<<16) | (TCPOPT_TIMESTAMP<<8) | TCPOLEN_TIMESTAMP)

#define TCP_MSS                         512

#define TCP_MAXWIN                      65535L  /* largest value for (unscaled) window */

/*Added by zhoushisong202096, 修改支持MCCP信令面设置MSS, 2013/11/30 */
/* the max ethernet mtu is 1500,
*  decrease IP head(20),TCP head(20)
*/
#define TCP_MAX_ETH_MSS 1460 

/* TCP with MD5 authentication, zhangfeng, 2002,07,20 */
#define MAXPASSLEN             255     /* Maximum length of MD5 P***W*** */
/* TCP with MD5 authentication, zhangfeng, 2002,07,20 */

#define TCP_MAX_WINSHIFT        14              /* maximum window shift */

/* User-settable options (used with setsockopt). 
#define TCP_NODELAY     0x01     don't delay send to coalesce packets 
#define TCP_MAXSEG      0x02     set maximum segment size */


#define TCP_DEFAULT_REASSMAXSEG   0xFFFFFFFF

typedef struct tagTCPIPOVLY
{
    ULONG   ih_pNext,ih_pPrev; /* for protocol sequence q's */
    UCHAR   ih_chXl;            /* (unused) */
    UCHAR   ih_chPr;            /* protocol */
    SHORT   ih_sLen;            /* protocol length */
    INADDR_S ih_stSrc; /* source internet address */
    INADDR_S ih_stDst; /* destination internet address */
}TCPIPOVLY_S;


/* TCP/IP混合头 */
typedef struct tagTCPIPHDR
{
    TCPIPOVLY_S ihOverlaidIP;
    TCPHDR_S    thTCPHeader;
} TCPIPHDR_S;


/* 用于存放MD5验证所需的各种字段的数据结构，其中包括ip头中的一些字段和
 * 某些字段以特殊值填充的TCP头部,2002,08,16, zhangfeng
 */
typedef struct tagMD5IP
{
    INADDR_S stSrc; /* source internet address */
    INADDR_S stDst; /* destination internet address */
    USHORT   usPr;            /* protocol */
    USHORT   usLen;            /* protocol length */
} MD5IP_S;

typedef struct tagMD5HDR
{
    MD5IP_S      stIP;
    TCPHDR_S    stTCP;
} MD5HDR_S;


/* Abbreviation macro for TCP-IP header */
#define pIHNext         ihOverlaidIP.ih_pNext
#define pIHPrev         ihOverlaidIP.ih_pPrev
#define ucIHX1          ihOverlaidIP.ih_chXl
#define ucIHProtocol    ihOverlaidIP.ih_chPr
#define sIHLen          ihOverlaidIP.ih_sLen
#define adrIHSrc        ihOverlaidIP.ih_stSrc
#define adrIHDst        ihOverlaidIP.ih_stDst
#define usTHSrcPort     thTCPHeader.usSrcPort
#define usTHDstPort     thTCPHeader.usDstPort
#define seqTHSeq        thTCPHeader.seqSeqNumber
#define seqTHAck        thTCPHeader.seqAckNumber
#define ucTHX2          thTCPHeader.ucX2
#define ucTHOffset      thTCPHeader.ucOffset
#define ucTHFlags       thTCPHeader.ucFlags
#define usTHWnd         thTCPHeader.usWnd
#define usTHCheckSum    thTCPHeader.usCheckSum
#define usTHUrgentPoint thTCPHeader.usUrgentPoint


/* The following definations are added for PSOS version, LQZ. */
#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef roundup
#define roundup(x, y)   ((((x)+((y)-1))/(y))*(y))
#endif


#ifdef  __cplusplus
}
#endif

#endif


