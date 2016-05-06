/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_inf.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2007/12/05
*    Author      :  IPv6 Team
*    Description :  To include Interface specific header files
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*-----------------------------------------------------------------------
*
*
************************************************************************/

#ifndef _IPBIR_INF_H_
#define _IPBIR_INF_H_

/* -------------------------------------------------------------------------- */
/* Include Product Header files - Based on the selected Product */
#if (VRP_YES == TCPIP_IN_VRP)

#include "ipbircommon/ipbirmap/ipos/ipbir_ipos_inf_map.h" /* for IPOS map*/

#else

#include "ipbircommon/ipbirmap/visp/ipbir_visp_inf_map.h" /* for VISP map*/

#endif

#endif  /* end of _IPBIR_INF_H_ */
