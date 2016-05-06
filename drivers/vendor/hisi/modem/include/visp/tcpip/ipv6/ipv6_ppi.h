/******************************************************************************
*
*        Copyright 2003-2011  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Version        : IPBIRV100R003.IPv6.E001
*    Module Name    : IP6 ND
*    File Name      : ipv6_ppi.h
*    Create Date    : 2009/09/09
*    Author         : Suraj_R
*    Description    : NP hardware Interface description
*------------------------------------------------------------------------------
*  Modification History
*
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-09   Suraj_R         Create
*******************************************************************************/

#ifndef _IPV6_PPI_H
#define _IPV6_PPI_H

#ifdef __cplusplus
extern "C"{
#endif


typedef struct tagIPV6_PPI_HOOK
{
    ULONG (*pfIP6_ADDR_PPIOperation)(ULONG ulOperType, VOID * pvData);
    ULONG (*pfIP6_ND_PPIOperation)(ULONG ulOperType, VOID * pData);
    ULONG (*pfIP6_ICMP6_PPIOperation)(ULONG ulOperType, VOID * pData);
    ULONG (*pfIP6_PMTU_PPIOperation)(ULONG ulOperType, VOID * pData);
}IPV6_PPI_HOOK_S;

typedef enum tagIP6_PPI_NOTIFY
{
    IP6_NP_ADDR_ADDUNI_ADDRESS = 1,       /* 01 Add Unicast IPv6 Address */
    IP6_NP_ADDR_DELUNI_ADDRESS,           /* 02 Delete Unicast IPv6 Address */
    IP6_NP_ADDR_SHOWADDRESS,              /* 03 Show IPv6 addresses */
    IP6_NP_ADDR_RESET_UNIADDRESS,         /* 04 Reset Unicast Addresses */
    IP6_NP_ADDR_ADDMULTI_ADDRESS,         /* 05 Add Multicast Address */
    IP6_NP_ADDR_DELMULTI_ADDRESS,         /* 06 Delete Multicast Address */
    IP6_NP_ADDR_RESET_MULTIADDRESS,       /* 07 Reset Mulitcast Addresses */
    IP6_NP_ADDR_NOTIFYMTU,                /* 08 Notify MTU */
    IP6_NP_ND_NP_NB_ADD,                  /* 09 Add IPv6 NB Entry */
    IP6_NP_ND_NP_NB_DEL,                  /* 10 Delete IPv6 NB Entry */
    IP6_NP_ND_NB_RESET_STATIC,            /* 11 Reset Static NB Entries */
    IP6_NP_ND_NB_RESET_DYNAMIC,           /* 12 Reset Dynamic NB Entries */
    IP6_NP_ND_NB_SHOWALL,                 /* 13 Show all NB Entries */
    IP6_NP_ND_PL_ADD,                     /* 14 Add Prefix List Entry */
    IP6_NP_ND_PL_DEL,                     /* 15 Delete Prefix List Entry */
    IP6_NP_ND_PL_RESET,                   /* 16 Reset Prefix List Entry */
    IP6_NP_ND_PL_SHOWALL,                 /* 17 Display all Prefix List Entries */
    IP6_NP_ND_DRL_ADD,                    /* 18 Add Default Router List Entry */
    IP6_NP_ND_DRL_DEL,                    /* 19 Delete Default Router List Entry */
    IP6_NP_ND_DRL_RESET,                  /* 20 Reset Default Router List Entry */
    IP6_NP_ND_DRL_SHOWALL,                /* 21 Show all default router list entries */
    IP6_NP_ICMP6_NPGETGLOBALSTAT_ALL,     /* 22 Get all Global ICMPv6 statistics */
    IP6_NP_ICMP6_NPGETGLOBALSTAT_BYTYPE,  /* 23 Get Global ICMPv6 Statistics by Type */
    IP6_NP_ICMP6_NPGETINTFSTAT_ALL,       /* 24 Get Interface level ICMPv6 statistics */
    IP6_NP_ICMP6_NPRESETGLOBALSTAT_ALL,   /* 25 Reset all ICMPv6 global statistics */
    IP6_NP_ICMP6_NPRESETGLOBALSTAT_BYTYPE,/* 26 Reset Global ICMPv6 statistics by type */
    IP6_NP_ICMP6_NPRESETINTFSTAT_ALL,     /* 27 Reset all interface-level ICMPv6 statistics */
    IP6_NP_PMTU_SHOWALL,                  /* 28 Display all PMTU Entries */
    IP6_NP_PMTU_ADDENTRY,                 /* 29 Add PathMTU Entry */
    IP6_NP_PMTU_DELENTRY,                 /* 30 Delete PMTU Entry */
    IP6_NP_PMTU_RESETSTATIC,              /* 31 Reset Static PMTU Entry */
    IP6_NP_PMTU_RESETDYNAMIC,             /* 32 Reset Dymamic PMTU Entry */
    IP6_NP_PMTU_RESETALL,                 /* 33 Reset all PMTU Entries */
    IP6_NP_ND_DC_ADD,                     /* 34 Update Destination Cache Entry */
    IP6_NP_ADDR_UPDATEUNI_ADDRESS,      /* 35 Update Unicast IPv6 Address */
    IP6_NP_MAX = 0xFFFFFFFF
}IP6_PPI_NOTIFY_E;

extern ULONG IP6_PPI_GetValue(IPV6_PPI_HOOK_S **ppstPPIHook);
extern ULONG IP6_PPI_RegisterNPHook(IPV6_PPI_HOOK_S *pstPPIHook);

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */


#endif /* _IV6_PPI_H */

