/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              udp.h
*
*  Project Code: VISP1.5
*   Module Name: udp4
*  Date Created: 2004-04-28
*        Author: WeiYongDong
*   Description: 定义udp模块的数据结构
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-04-28 WeiYongDong       Create the first version.
*  2006-04-27 luyao             根据编程规范，对文件进行规范化整理
*  2006-05-11 luyao             为支持ARM CPU字节对齐特性，修改结构。
*
*******************************************************************************/

 
#ifndef _UDP_H_
#define _UDP_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "tcpip/udp4/include/udp_api.h"
typedef struct tagUDPIPOVLY
{
    ULONG ih_pNext,ih_pPrev;/* for protocol sequence q's */
    UCHAR   ih_chXl;            /* (unused) */
    UCHAR   ih_chPr;            /* protocol */
    SHORT   ih_sLen;            /* protocol length */
    INADDR_S ih_stSrc;          /* source internet address */
    INADDR_S ih_stDst;          /* destination internet address */
}UDPIPOVLY_S,IPOVLY_S;          /* add by x36530 Trace to D03852 */


/*
 * UDP kernel structures and variables.
 */
typedef struct  tagUDPIPHDR
{
    UDPIPOVLY_S ui_stIp;   /* overlaid ip structure */
    UDPHDR_S    ui_stUdp;  /* udp header */
}UDPIPHDR_S;

#define ui_pNext                ui_stIp.ih_pNext
#define ui_pPrev                ui_stIp.ih_pPrev
#define ui_chXl                 ui_stIp.ih_chXl
#define ui_chPr                 ui_stIp.ih_chPr
#define ui_sLen                 ui_stIp.ih_sLen
#define ui_stSrc                ui_stIp.ih_stSrc
#define ui_stDst                ui_stIp.ih_stDst
#define ui_usSPort              ui_stUdp.uh_usSPort
#define ui_usDPort              ui_stUdp.uh_usDPort
#define ui_sULen                ui_stUdp.uh_sULen
#define ui_usSum                ui_stUdp.uh_usSum

typedef struct tagUDP4_CONNECTION_INFO_S  
{
    INADDR_S   stUdpLocalAddress;
    USHORT     usUdpLocalPort;
    UCHAR      ucPadding[2];
    ULONG      ulUdpIfIndex;
}UDP4_CONNECTION_INFO_S;


typedef struct tagIP4_UDP4_SH_CALLBACUP_SET_S
{
    VOID (*pfIP4_UDP4_DbugPkt)(CHAR *pPreStr, MBUF_S *pMbuf) ;
    VOID (*pfIP4_UDP4_SH_SendInfo2IC)(CHAR *szString );
}IP4_UDP4_SH_CALLBACUP_SET_S;

typedef struct  tagIP4_UDP4_MOD_INFO_S
{
    ULONG ulModID;                /* Module id */

    ULONG ulUDP4_OUTPUT_OPTIMIZE; /*Added by x36317, 标识是否使能UDP4发送流程优化, 2006-04-27*/

}IP4_UDP4_MOD_INFO_S;


/*
 * Names for UDP sysctl objects
 */
#define UDPCTL_CHECKSUM         1       /* checksum UDP packets */
#define UDPCTL_MAXID            2

#ifdef __cplusplus
}
#endif

#endif
