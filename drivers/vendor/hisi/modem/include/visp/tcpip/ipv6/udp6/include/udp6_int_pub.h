/*-----------------------------------------------------------------------
*                              udp6_com_pub.h
*
*    Project Code:  IPB IR V1R2
*    Module Name :  UDP6
*    Create Date :  2007/06/29
*    Author      :  karthik
*    Description :  To define the structures and macro's used by core
*                    and shell of component
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2007-06-29  karthik      Created for including all component
*                           public definitions in this file,
*                           for IPB IR V1R2 - COMMOM re-arrange
************************************************************************/

#ifndef _UDP6_COM_PUB_H
#define _UDP6_COM_PUB_H

#ifdef  __cplusplus
extern "C"{
#endif  /* #ifdef  __cplusplus */

#include "common/ipos/ipv6/udp6_public.h"
#include "tcpip/public/tcpip_basefun.h"

#define IP6_UDP6_EXT_COMIF_CNT  0x3

#define  SYSTRC_IPV6_UDP6_BASE       01

#define IP6_UDP6_UDP6_USR           ((SYSTRC_IPV6_UDP6_BASE << 8) + 1)
#define IP6_UDP6_UDP6_SH_CFG        ((SYSTRC_IPV6_UDP6_BASE << 8) + 2)
#define IP6_UDP6_UDP6_SH_IC         ((SYSTRC_IPV6_UDP6_BASE << 8) + 3)
#define IP6_UDP6_UDP6_SH_INIT       ((SYSTRC_IPV6_UDP6_BASE << 8) + 4)
#define IP6_UDP6_UDP6_INT           ((SYSTRC_IPV6_UDP6_BASE << 8) + 5)
#define IP6_UDP6_UDP6_FAC           ((SYSTRC_IPV6_UDP6_BASE << 8) + 6)
#define IP6_UDP6_UDP6_INIT          ((SYSTRC_IPV6_UDP6_BASE << 8) + 7)

#define UDP6_FILENUM         FILENUM
#define UDP6_SOCKID_ANY      (UDP6_FILENUM + 1)
#define UDP6_TASKID_ANY      0xFFFFFFFF

/*UDP6 module information*/
typedef struct  tagIP6_UDP6_MOD_INFO
{
    ULONG ulModID; /* Module id */
    ULONG ulUDP6_CFG_SRC_CACHE;

}IP6_UDP6_MOD_INFO_S;

#define UDP6_MAX_STATSTICS_BUFSIZE          1024
#define UDP6_MAX_STATSTICS_TEMP_BUFSIZE     256

/*udp6 shell callback*/
typedef struct tagIP6_UDP6_SH_CALLBACUP_SET
{
#ifdef _MBUF_H_
    VOID (*pfIP6_UDP6_SH_DbugPkt)(CHAR *pPreStr, MBUF_S *pstMbuf, int ioff);
#else
    VOID (*pfIP6_UDP6_SH_DbugPkt)(CHAR *pPreStr, VOID *pstMbuf, int ioff);
#endif
    VOID (*pfIP6_UDP6_SH_DebugToIC)(CHAR *szString);
    ULONG (*pfIP6_UDP6_SH_DebugPktEnable)(VOID);
    ULONG (*pfIP6_UDP6_SH_EndpointTableMib) (VOID* pMsgRcv, VOID** ppMsgSnd);

}IP6_UDP6_SH_CALLBACUP_SET_S;

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* #ifndef _IUDP6_INC_H */

