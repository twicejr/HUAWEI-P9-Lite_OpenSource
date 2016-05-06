/*******************************************************************************
*
*
*                Copyright 2014, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_cookie.h
*
*  Project Code: v3r01c01B601
*   Module Name:   
*  Date Created: 2014-01-03
*        Author: zhoushisong202096
*   Description: TCP Cookie Calc or Check
*                Include TCP4/TCP6 
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-01-03   zhoushisong202096       Create
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _TCPIP_COOKIE_H_
#define _TCPIP_COOKIE_H_

#define TCP_COOKIEBITS 24   /* Upper bits store count */
#define TCP_COOKIEMASK (((UINT32)1 << TCP_COOKIEBITS) - 1)
#define TCP_DIGEST_WORDS 5
#define TCP_WORKSPACE_WORDS 80
#define TCP_COOKIETIMEOUT 4 /*240S = 4min * 60 --> 后面改成分钟了 */

#define K1  0x5A827999L    /* Rounds  0-19: sqrt(2) * 2^30 */
#define K2  0x6ED9EBA1L    /* Rounds 20-39: sqrt(3) * 2^30 */
#define K3  0x8F1BBCDCL    /* Rounds 40-59: sqrt(5) * 2^30 */
#define K4  0xCA62C1D6L    /* Rounds 60-79: sqrt(10) * 2^30 */

#define f1(x,y,z)   (z ^ (x & (y ^ z)))   /* x ? y : z */
#define f2(x,y,z)   (x ^ y ^ z)               /* XOR */
#define f3(x,y,z)   ((x & y) + (z & (x ^ y)))  /* majority */
#define SWAP32(x) ((UINT32)(\
    (((UINT32)(x) & (UINT32)0x000000ffUL) << 24) | \
    (((UINT32)(x) & (UINT32)0x0000ff00UL) <<  8) | \
    (((UINT32)(x) & (UINT32)0x00ff0000UL) >>  8) | \
    (((UINT32)(x) & (UINT32)0xff000000UL) >> 24)))

#define TCP_MAX_MSSIDINDEX  8

#define TCPIP_COOKIE_ON      1
#define TCPIP_COOKIE_OFF     0
#define TCPIP_USR_COOKIE_ON  1
#define TCPIP_USR_COOKIE_OFF 0

#define IP4BASICHEAD_LEN             20
#define IP6BASICHEAD_LEN             40
#define LEN_136                      136

extern VOID TCPCOOKIE_ShaTransform(UINT32 *digest, CHAR *in, UINT32 *W);
extern UINT32 g_u32SynCookieSecret[2][16 - 4 + TCP_DIGEST_WORDS];
extern UINT16 g_au16MssTable[TCP_MAX_MSSIDINDEX];

#endif

#ifdef  __cplusplus
}
#endif

