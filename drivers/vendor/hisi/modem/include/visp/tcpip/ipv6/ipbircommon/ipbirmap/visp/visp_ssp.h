/*******************************************************************************
*                                                                              *
*        Copyright 2003-2006  Huawei Technologies India Private Limited        *
*                          All Rights Reserved                                 *
*                                                                              *
*------------------------------------------------------------------------------*
*                                                                              *
*                                 visp_ssp.h                                   *
*                                                                              *
*    Project Code:  IPBIRV1R2                                                     *
*     Module Name:  IPBIR used this ssp header file to adapt VISP      *
*     Create Date:  2006/12/05                                                 *
*          Author:  wanlujun                                                  *
*     Description:  This file include all external ssp head files which are         *
*                   used for IR core part.  It copys to replace former ipos_ssp.h    *
*------------------------------------------------------------------------------*
*  Modification History                                                        *
*  DATE        NAME             DESCRIPTION                                    *
*  --------------------------------------------------------------------------  *
*  2006-12-05  wanlujun     Creation                                      *
*                                                                              *
*******************************************************************************/


#ifdef __cplusplus
extern "C"{
#endif

#ifndef _VISP_SSP_H
#define _VISP_SSP_H

#if (TCPIP_IN_VRP == VRP_NO)

#include "vos/vospubh/basetype.h"
#include "vos/vospubh/utldll.h"
#include "vos/vospubh/utlsll.h"
#include "vos/vospubh/vos_mem.h"
/*#include "vos/vospubh/mbuf.h"*/
/* #include "vos/vospubh/vos_arg.h" */
#include "vos/vospubh/vos_lib.h"
#include "vos/vospubh/vos_err.h"
#include "vos/vospubh/vos_id.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_intr.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/vos_time.h"
#include "vos/vospubh/vos_ker.h"
#include "vos/vospubh/rpc_inc.h"
#include "vos/vospubh/ipc_inc.h"
#include "vos/vospubh/wlst_inc.h"
#include "vos/vospubh/vos_util.h"
#include "vos/vospubh/cksum.h"
#include "vos/vosregex/vos_regx.h"    
#include "vos/vospubh/paf.h"
#include "vos/vospubh/rdx6_pub.h"
#include "vos/vospubh/compbase.h"
/* Add     Reason :ADDINVISP  Bharath*/ 
#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/systrace.h"
#include "vos/vosprih/vos_stm.h"
#include "common/visp/tcpip_entry.h"

/*added Sandeep71635 for IPBIRV100R002.IP.E001*/
#include "visp/software/tcpip/public/vrpvos/gads_api.h"
#include "vos/vospubh/wlst_inc.h"
 /* End  */

/* Rohit */
#include "vos/vosutil/des_self.h"
#include "vos/vospubh/radix.h"


extern ULONG TCPIP_Get_PAF_ResValue (SPECS_RES_VALUE_S* pstResValue);
extern ULONG TCPIP_Get_PAF_FunValue (SPECS_FUN_VALUE_S* pstFunValue);


#define IPOS_APP_INIT_INFO_S  APP_INIT_INFO_S
/*Begin: VISPV1R7 need to debug in memory, we need to call TCPIP_Malloc/Free.
   Changed by wan for VISPV1R7 Build2 integration, 2008-05-16*/
#define VOS_Malloc  TCPIP_Malloc
#define VOS_Free  TCPIP_Free
/*End of Change by wan for VISPV1R7 integration*/
#endif



#endif /* End of _VISP_SSP_H */

#ifdef    __cplusplus
}
#endif

