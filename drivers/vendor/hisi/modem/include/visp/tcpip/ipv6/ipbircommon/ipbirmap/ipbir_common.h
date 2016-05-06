/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_common.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2007/12/05
*    Author      :  IPv6 Team
*    Description :  To include Common component specific header files
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-----------------------------------------------------------------------
*
*
************************************************************************/

#ifndef _IPBIR_COMMON_H_
#define _IPBIR_COMMON_H_

#if (VRP_YES == TCPIP_IN_VRP)

#include "ipbircommon/ipbirmap/ipos/ipbir_ipos_common_map.h" /* for IPOS map*/

#else

#include "ipbircommon/ipbirmap/visp/ipbir_visp_common_map.h" /* for VISP map*/

#endif

#endif  /* end of _IPBIR_COMMON_H_ */
