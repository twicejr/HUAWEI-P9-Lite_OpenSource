/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_mbuf.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To include IPOS / VISP specific MBUF Map file
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for including relevant MBUF Map file
*                               based on IPOS or VISP compilation
************************************************************************/

#ifndef _IPBIR_MBUF_H_
#define _IPBIR_MBUF_H_

#ifdef  __cplusplus
extern "C"{
#endif

/*
MBUF head file included method
*/
#if (VRP_NO == TCPIP_IN_VRP)
#include "common/visp/mbuf.h"    /*If release to VISP, Directly use VISP mbuf*/
#include "ipbircommon/ipbirmap/visp/ipbir_visp_mbuf_map.h"   /*For VISP map*/

#else

#if (VRP_YES == IPOS_NON_VRP)
#include "common/mbuf/ipos_mbuf.h" /*If release to Non-DC(SGSN), use IPOS mbuf*/
#else
#include "vos/vospubh/mbuf.h"    /*Else release to VRP, Directly use VRP mbuf*/
#endif

#include "ipbircommon/ipbirmap/ipos/ipbir_ipos_mbuf_map.h"  /*For IPOS map*/
#endif

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _IPBIR_MBUF_H_ */

