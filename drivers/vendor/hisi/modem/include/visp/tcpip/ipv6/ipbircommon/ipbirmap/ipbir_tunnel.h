/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_tunnel.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To include IPOS / VISP specific Tunnel Map file
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for including relevant Tunnel Map file
*                               based on IPOS or VISP compilation
************************************************************************/

#ifndef _IPBIR_TUNNEL_H_
#define _IPBIR_TUNNEL_H_

/*Modified to re-arrange IPB IR common headfile
    for VISP and IPOS, w39621, 2006-12-02*/

#if (VRP_YES == TCPIP_IN_VRP)
#include "ipbircommon/ipbirmap/ipos/ipbir_ipos_tunnel_map.h"          /*For IPOS map*/
#else
/*#include "ipv6/ipbirmap/visp/ipbir_visp_tunnel_map.h"*/   /*For VISP map:VISP donot use*/
#endif

#endif  /* end of _IPBIR_TUNNEL_H_ */

