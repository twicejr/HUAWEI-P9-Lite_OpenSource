/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_ic.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To include IPOS / VISP specific IC Map file
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for including relevant IC Map file
*                               based on IPOS or VISP compilation
************************************************************************/

#ifndef _IPBIR_IC_H_
#define _IPBIR_IC_H_

#if (VRP_YES == TCPIP_IN_VRP)
#include "ipbircommon/ipbirmap/ipos/ipbir_ipos_ic_map.h"    /* for IPOS map*/
#else
#include "ipbircommon/ipbirmap/visp/ipbir_visp_ic_map.h"    /* for VISP map*/
#endif

#endif  /* end of _IPBIR_IC_H_ */
