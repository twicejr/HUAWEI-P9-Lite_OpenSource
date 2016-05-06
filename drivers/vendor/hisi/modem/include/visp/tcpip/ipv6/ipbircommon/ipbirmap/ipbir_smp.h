/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_smp.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To include IPOS / VISP specific SMP Map file
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for including relevant SMP Map file
*                               based on IPOS or VISP compilation
************************************************************************/

#ifndef _IPBIR_SMP_H_
#define _IPBIR_SMP_H_

/*Modified to re-arrange IPB IR common headfile
   for VISP and IPOS, w39621, 2006-12-02*/

#if (VRP_YES == TCPIP_IN_VRP)   /* for IPOS smp*/
#include "common/ipos/adp/ipos_smp.h"

#define IPB_IR_CFM_BUILDRUN_INS_FUNC CFM_BUILDRUN_INS_FUNC
#define IPB_IR_CFM_IPV6_ND_BRUN  CFM_IPV6_ND_BRUN

#define IPB_IR_CFM_IPV6_ND2_BRUN  CFM_IPV6_ND2_BRUN  /* Added by KLSRINI for AC4D00983 */


#define IPB_IR_CFM_BUILDRUN_INS_FUNC  CFM_BUILDRUN_INS_FUNC
/* #define IPB_IR_CFM_IPV6_ADDR_BRUN     IPOS_CFM_IPV6_ADDR_BRUN */
#define IPB_IR_CFM_IPV6_ADDR_BRUN     CFM_IPV6_ADDR_BRUN

/*Begin: MST Defect Sandeep71635.  2006-10-10
  buildrun callback not called*/
#define IPB_IR_CFM_IPV6_PMTU_BRUN     CFM_IPV6_PMTU_BRUN
/*End: MST Defect Sandeep71635    2006-10-10 */

/* Added by Guru for DHCP6R Integration; TBD  */
#define IPB_IR_CFM_DHCP6R_BRUN        CFM_DHCP6RELAY_BRUN

#else
/*#include "visp_smp.h"*/          /* for VISP: VISP donot use SMP*/
#endif

#endif  /* end of _IPBIR_SMP_H_ */

