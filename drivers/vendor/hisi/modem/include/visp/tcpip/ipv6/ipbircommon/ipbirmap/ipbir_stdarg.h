/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_stdarg.h
*
*    Project Code:  IPOS IR V1R3
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2008/06/17
*    Author      :  IPv6 Team
*    Description :  To include IPOS / VISP specific Stdarg Map file
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for including relevant Stdarg Map file
*                               based on IPOS or VISP compilation
************************************************************************/

#ifndef _IPBIR_STDARG_H_
#define _IPBIR_STDARG_H_


#if (VRP_YES == TCPIP_IN_VRP)
#include "ipbircommon/ipbirmap/ipos/ipbir_ipos_stdarg_map.h"  /* for IPOS map*/
#else
#include "ipbircommon/ipbirmap/visp/ipbir_visp_stdarg_map.h"  /* for VISP map*/
#endif

#endif  /* end of _IPBIR_STDARG_H_ */

