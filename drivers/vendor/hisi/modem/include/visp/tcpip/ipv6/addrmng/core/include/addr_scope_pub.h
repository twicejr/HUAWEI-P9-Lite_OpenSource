/*************************************************************************
*                                                                        *
*                         Addr_scope_pub.h                               *
*                                                                        *
*  Project Code:       VRP3.1 IPv6 project                               *
*  Version     :       IPBIRV100R003.IPv6.E001                           *
*  Module Code:       IPv6 Address management                            *
*  Create Date:        2002-8-21                                         *
*  Author:             luoli                                             *
*  Modify Date:                                                          *
*  Description:        Contains Data Structures and extern declaration   *
*                      of functions                                      *
*  Function:                                                             *
*  Others:                                                               *
*------------------------------------------------------------------------*
*                                                                        *
*  Copyright 2000-2002 VRP3.1 Team Beijing Institute HuaWei Tech, Inc.   *
*                      ALL RIGHTS RESERVED                               *
*                                                                        *
*************************************************************************/

#ifndef _SCOPE_PUB_H_
#define _SCOPE_PUB_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "ipbircommon/ipbirmap/ipbir_ssp.h"

/* Data Structure to implement linked list for Link local and
   site local scoped addresses */
typedef  struct   tagScopeNode
{
    ULONG    ulScopeZoneId;    /* scope zone id */
    DLL_S     stInterfaceDll;
    struct  tagScopeNode    *pstNext;
}SCOPE_NODE_S;


/* Data Structure to hold information of Link local address list
   and site local address list for each interface */
typedef  struct   tagScopeInterface
{
    DLL_NODE_S    stDllNode;
    ULONG         ulIfIndex;
    struct   tagIP6IFADDR  *pstRelevantAddrList;
}SCOPE_INTERFACE_S;

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _SCOPE_PUB_H_ */

