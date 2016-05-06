/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_ssp.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To include IPOS / VISP specific SSP Map file
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for including relevant SSP Map file
*                               based on IPOS or VISP compilation
************************************************************************/

#ifndef _IPBIR_SSP_H_
#define _IPBIR_SSP_H_



#if (VRP_YES == TCPIP_IN_VRP)                    /* for IPOS */
#include "common/ipos/adp/ipos_ssp.h"
#include "common/ipos/adp/ipos_mac.h"

#include "util/vosutil/utldll.h"
#include "util/vosutil/utlsll.h"
#include "util/waitlist/wlst_inc.h"
#include "util/vosutil/cksum.h"
#include "util/radix6/rdx6_pub.h"
#include "util/gads/gads_api.h"

/* Added by Guru; for DHCP6 Integration */
#include "util/radix/radix.h"

#define IPB_IR_VRP_EVENT_TIMERREQ IPOS_EVENT_TIMERREQ
#define IPB_IR_VRP_EVENT_RUNINDICATION IPOS_EVENT_RUNINDICATION


#define IPBIR_PAF_GetResource  PAF_GetResource
#define IPBIR_LCS_GetResource  LCS_GetResource

#else                                                           /* for VISP */
#include "ipbircommon/ipbirmap/visp/visp_ssp.h"
#include "common/visp/tcpip_log.h"

/*Post B102 changes: tcpip_ir_log.h is moved to common\ipos */
#include "common/ipos/tcpip_ir_log.h"

#define IPB_IR_VRP_EVENT_TIMERREQ VRP_EVENT_TIMERREQ
#define IPBIR_PAF_GetResource TCPIP_Get_PAF_ResValue

#endif
/* Semaphore Flags */
#define IPB_IR_VOS_SEMA4_PRIOR              0x00000002
#define IPB_IR_VOS_SEMA4_INVERSION_SAFE     0x08

/* Start : Relocated from ipbir_common.h to here by Arvind for C05 Rearrangement*/
#define IPB_IR_RET_VAL_UNALLIGNED_ERR  1
#define IPB_IR_RET_VAL_NONE 0
#define IPB_IR_GET_LAST_2_BITS 0x03

#if (VRP_YES  == ARM_SUPPORT)
#define IPB_IR_CHECK_MEMORYADDRESS(pstPointer) \
         ( 0 != ((ULONG)pstPointer & IPB_IR_GET_LAST_2_BITS))
#else
#define IPB_IR_CHECK_MEMORYADDRESS(pstPointer) \
         ( 0 )
#endif
/* End : Relocatation from ipbir_common.h to here */

/*Acquire the VISP global semaphore*/
extern ULONG VRPAdapt_GlobalSemaphore_Acquire(VOID);

/*Release the VISP global semaphore*/
extern ULONG VRPAdapt_GlobalSemaphore_Release(VOID);

extern ULONG TCPIP_SmP(ULONG ulMutexID);
extern ULONG TCPIP_SmV(ULONG ulMutexID);

extern ULONG g_ulSemForTightMods;

#ifndef TCPIP_BEGIN_PT
#define TCPIP_BEGIN_PT(ulSem) (VOID)TCPIP_SmP(ulSem)
#endif

#ifndef TCPIP_END_PT
#define TCPIP_END_PT(ulSem) (VOID)TCPIP_SmV(ulSem)
#endif

#endif  /* end of _IPBIR_SSP_H_ */

