/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_security.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2009/1/08
*    Author      :  IPSEC
*    Description :  To include Product specific header files
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-----------------------------------------------------------------------
*
*
************************************************************************/

#ifndef _IPBIR_SECURITY_H_
#define _IPBIR_SECURITY_H_


#if (VRP_YES == TCPIP_IN_VRP)
#include "ipbircommon/ipbirmap/ipos/ipbir_ipos_security_map.h"    /* for IPOS map*/
#else
#include "ipbircommon/ipbirmap/visp/ipbir_visp_security_map.h"    /* for VISP map*/
#endif

#endif  /* end of _IPBIR_SECURITY_H_ */
