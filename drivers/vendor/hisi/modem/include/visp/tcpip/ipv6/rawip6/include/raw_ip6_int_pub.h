/*-----------------------------------------------------------------------
*                              raw_ip6_com_pub.h
*
*    Project Code:  IPB IR V1R2
*    Module Name :  RAWIP6
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
#ifndef _RAW_IP6_COM_PUB_H
#define _RAW_IP6_COM_PUB_H

#ifdef  __cplusplus
extern "C" {
#endif

/* External module number*/
#define IP6_RAWIP6_EXT_COMIF_CNT      0x3

#define SYSTRC_IPV6_RIP6_BASE         01
#define IP6_RIP6_RAW_IP6            ((SYSTRC_IPV6_RIP6_BASE << 8) + 1)
#define IP6_RIP6_RAW_IP6_INIT       ((SYSTRC_IPV6_RIP6_BASE << 8) + 2)
#define IP6_RIP6_RAW_IP6_FAC        ((SYSTRC_IPV6_RIP6_BASE << 8) + 3)
#define IP6_RIP6_RAW_IP6_INT        ((SYSTRC_IPV6_RIP6_BASE << 8) + 4)
#define IP6_RIP6_RAW_IP6_SH_INIT    ((SYSTRC_IPV6_RIP6_BASE << 8) + 5)


#define    RIPV6SNDQ    8192
#define    RIPV6RCVQ    8192


/*RAWIP6 module information */
typedef struct  tagIP6_RIP6_MOD_INFO
{
    ULONG ulModID; /* Module id */
    ULONG ulRIP6_CFG_SRC_CACHE;
} IP6_RIP6_MOD_INFO_S;

#ifdef  __cplusplus
}
#endif

#endif

