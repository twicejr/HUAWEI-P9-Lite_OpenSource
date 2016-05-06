/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ping_def.h
*
*  Project Code: 2002-8-20
*   Module Name: ping  
*  Date Created: 2006-4-28
*        Author: fu jibin
*   Description: 本文件定义了Ping模块使用的宏
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-8-20  fu jibin         Creat the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/


/* Defect id BYAD01452 - Modified by Suraj 21st Oct 2003. */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _PING_DEF_H_
#define _PING_DEF_H_

/*  Common definitions and typedefs   */
#define PIN_DEFDATALEN        (64 - 8)         /* default data length    */
#define PIN_MAXIPLEN          60
#define PIN_MAXICMPLEN        76
#define PIN_MAXLEN            8100
#define PIN_DEFPACKETCOUNT    5                /*default packet count */
#define PIN_MINLEN            20
#define PIN_MAXWAIT           10               /* max seconds to wait for response */
#define PIN_NROUTES           9                /* number of record route slots*/
#define PIN_MAXHOSTNAMELEN    IP_HOSTNAME_LEN + 1  /* max host name length */
#define PIN_MAXTIME           0xFFFFFFFF       /* 4294967295 */

#define PIN_MAXTTL_TOS        255               /* 最大的TTL或者TOS值 */ 
#define PIN_ICMP_HEADLEN      8                 /* ICMP报文头长度 */ 
#define PIN_DEFTIMEOUT        2000              /* ping 报文默认超时时间 */
#define PIN_IP_HEADLEN        20                /* IP报文头长度 */



/*  various options   */
#define PIN_F_TIMEOUT       0x002
#define PIN_F_NUMERIC       0x004
#define PIN_F_PINGFILLED    0x008
#define PIN_F_QUIET         0x010
#define PIN_F_RROUTE        0x020
#define PIN_F_SO_DEBUG      0x040
#define PIN_F_SO_DONTROUTE  0x080
#define PIN_F_VERBOSE       0x100

/*  MACRO and CONST  */
#define PIN_A( rcvd_tbl, bit ) rcvd_tbl[( bit )>>3 ]    /* identify byte in array */
#define PIN_B(bit)  ( (UCHAR)(1<<(( bit ) & 0x07 )))  /* identify bit in byte   */
#define PIN_SET( rcvd_tbl, bit )  ( PIN_A( rcvd_tbl, bit ) |= PIN_B( bit ))
#define PIN_CLR( rcvd_tbl, bit )  ( PIN_A( rcvd_tbl, bit ) &=( ~PIN_B( bit )))
#define PIN_TST( rcvd_tbl, bit )  ( PIN_A( rcvd_tbl, bit ) & PIN_B( bit ) )

/*  MAX_DUP_CHK is the number of bits in received table, i.e. the maximum
    number of received sequence numbers we can keep track of.  Change 128
    to 8192 for complete accuracy...*/
#define PIN_MAX_DUP_CHK ( 8 * 128 )

/*  Error Message  */
#define PIN_ILLEGAL_PARAM  -1
#define PIN_NO_MATCH       -2
#define PIN_MALLOC_ERROR   -3
#define PIN_PARAM_NULL     -4


/*  Common definitions and typedefs  */ 
/* default ICMP data length   -56 bytes (64 bytes - 8 bytes ICMP header)*/
#define PING6_DEFDATALEN       56

#define PING6_DEFTIMEOUT       2000         /*default timeout 2000 msecs */
#define PING6_DEFPACKETCOUNT   5            /*default packet count */
#define PING6_MAXLEN           8100
#define PING6_MINLEN           20
#define PING6_TIMELEN          4
#define PING6_ICMP6LEN         8
#define PING6_ICMP6_HEADLEN    8
#define PING6_MAXTIME          0xFFFFFFFF  /* 4294967295 */
#define PING6_MAX_IFINDEX_NUM  20

/*    用于处理重复报文的宏*/
#define PING6_MAX_DUP_CHK   ( 8 * 128 )
#define PING6_A( rcvd_tabel, bit ) rcvd_tabel[( bit )>>3 ]    /* identify byte in array */
#define PING6_B(bit)    ((UCHAR)(1<<(( bit ) & 0x07 )))     /* identify bit in byte   */
#define PING6_SET( rcvd_tabel, bit )  ( PING6_A( rcvd_tabel, bit ) |= PING6_B( bit ))
#define PING6_CLR( rcvd_tabel, bit )  ( PING6_A( rcvd_tabel, bit ) &=( ~PING6_B( bit )))
#define PING6_TST( rcvd_tabel, bit )  ( PING6_A( rcvd_tabel, bit ) & PING6_B( bit ) )


/* PING6_MAX_DUP_NUM 是接收列表的位数,也是就可以记录的最大报文数  */
#define PING6_MAX_DUP_NUM ( 8 * 128 )


/* Macro for memory allocation.*/
#define PING6_Min(a, b) ((a) < (b) ? (a) : (b))
#define PING6_Max(a, b) ((a) > (b) ? (a) : (b))

/* Definitions for the SYSTRACE. */
#define SYSTRC_IPV6_PING6_BASE 00
#define IPV6_PING6_CMD ((SYSTRC_IPV6_PING6_BASE << 8) + 010)
#define IPV6_PING6_PKTPROC ((SYSTRC_IPV6_PING6_BASE << 8) + 011)
 
/* PING使用的SID统一在此定义 */

#define SID_PING4_SENDBUF          1  /* 存放ICMP请求报文 */
#define SID_PING4_RECVBUF          2  /* 存放ICMP应答报文 */
#define SID_PING4_STAT             3  /* ping统计信息结构体TCPIP_PING_STAT_S */

#define SID_PING6_SENDBUF        100  /* 存放ICMP请求报文 */
#define SID_PING6_RECVBUF        101  /* 存放ICMP应答报文 */

/* end of SID */

#endif

#ifdef __cplusplus
}
#endif

/* Defect id BYAD01452 - Modified by Suraj 21st Oct 2003. */


