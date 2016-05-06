/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_visp_fib6_map.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To define VISP specific FIB6 macros
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for defining VISP related FIB6 macros
************************************************************************/

#ifndef _IPB_IR_VISP_FIB_MAPP_H_
#define _IPB_IR_VISP_FIB_MAPP_H_



#include "common/visp/VISP_IR_SFIB.h"

/* Commented by Prabhu H - B100 ACT RND2 Smoke findings */

ULONG VRPAdapt_FIB6_Get_RT6_VlanId(ULONG ulSin6ScopeId, VOID *pstIn6Addr, ULONG *pulVlanId);
ULONG VRPAdapt_FIB6_Get_RT6_Flags(ULONG ulSin6ScopeId, VOID *pstIn6Addr, ULONG *pulFlags);
ULONG VRPAdapt_FIB6_Get_RT6_Nexthop(ULONG ulSin6ScopeId, VOID *pstIn6Addr, ULONG *aulNexthop);
ULONG VRPAdapt_FIB6_Get_NHInfo(ULONG ulZoneID, VOID *pstIn6DstAddr,
                               ULONG *pulIfIndex, ULONG *paulNexthop,
                               ULONG *pulFlags,ULONG *pulVlanId,
                               ULONG *pulATIndex);


#define IPB_IR_FIB6_LOADBALANCE_ENABLE FIB6_LOADBALANCE_ENABLE
#define IPB_IR_FIB6_LOADBALANCE_DISABLE FIB6_LOADBALANCE_DISABLE

/* Commented by Prabhu H - B100 ACT RND2 Smoke findings */

#define IPB_IR_FIB6_GET_RT6_NHINFO(ulSin6ScopeId, pstIn6Addr, pulIfIndex, paulNexthop, pulFlags, pulVlanId, pulATIndex) \
    VRPAdapt_FIB6_Get_NHInfo(ulSin6ScopeId, (VOID*)pstIn6Addr, pulIfIndex, \
                       (ULONG *)paulNexthop, pulFlags, pulVlanId, pulATIndex)



#endif  /* end of _IPB_IR_VISP_FIB_MAPP_H_ */
