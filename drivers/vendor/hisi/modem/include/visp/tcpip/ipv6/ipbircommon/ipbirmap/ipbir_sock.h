/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_sock.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To include IPOS / VISP specific SOCKET Map file
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for including relevant SOCKET Map file
*                               based on IPOS or VISP compilation
************************************************************************/

#ifndef _IPBIR_SOCK_H_
#define _IPBIR_SOCK_H_

/*Modified to re-arrange IPB IR common headfile
    for VISP and IPOS, w39621, 2006-12-02*/

#if (VRP_YES == TCPIP_IN_VRP)                          /* for IPOS */
#include "common/ipos/socket/sock_public.h"
#include "common/ipos/socket/sock_type.h"

/* Add : Rajat Phull, IPBIRV1R2C02DHCPv6 */
#include "ipbircommon/ipbirmap/ipos/ipbir_ipos_sock_map.h"    /* for IPOS map*/
#else
#include "common/visp/VISP_IR_SOCKET.h"         /* for VISP */

/* Add : Rajat Phull, IPBIRV1R2C02DHCPv6 */
#include "ipbircommon/ipbirmap/visp/ipbir_visp_sock_map.h"    /* for VISP map*/
#endif

#endif  /* end of _IPBIR_SOCK_H_ */

