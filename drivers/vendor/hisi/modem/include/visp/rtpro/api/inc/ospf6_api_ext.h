/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf6_api_ext.h
*
*  Project Code: VISPV100R008C02
*   Module Name:   
*  Date Created: 2009-07-14
*        Author: hanna55555
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-07-14   hanna55555              Create
*
*******************************************************************************/
#ifndef OSPF6_API_EXT_H
#define OSPF6_API_EXT_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*全局头文件*/
#include <nbase.h>
#include <ntlbuf.h>
#include <a0stubs.h>
#include <a0glob.h>
#include <a0cust.h>
#include <a0inst.h>
#include <a0mib.h>
#include <ambips.h>
#include <a0spec.h>
#include <o0mac.h>
#include <a0auth.h>
#include <nbbi.h>
#include <yapiincl.h>
#include <qopmincl.h>

/*组件MIB头文件*/
#include <qo0pmib.h>
#include <qo0pmbv3.h>
#include <qcrtdef.h>

/*VISP相关头文件*/
#include "tcpip/public/tcpip_config.h" 
#include "tcpip/public/tcpip_id.h"

#include "vos/vospubh/basetype.h"
#include "vos/vospubh/compbase.h"
#include "dopra/target/include/v_sm.h"

#include "tcpip/public/tcpip_debug.h"
#include "tcpip/public/entry/tcpip_entry.h" 

#include "tcpip/public/arith_cbb/include/mbuf.h"
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/public/tcpip_log.h"
#include "tcpip/ip4/am4/include/am4_api.h"

#include "tcpip/sfib4/include/ifiba_inc.h"
#include "rtpro/glue/i3agent/i3agent.h"
#include "tcpip/vrf/core/include/vrf_inc.h"

/*Modified by liangjicheng 00103192, G3, 2011/2/9   问题单号:V2R3C03-ROTUE-MERGE */
#include "tcpip/socket4/core/include/sock_com.h"
/*End of Modified by liangjicheng 00103192, 2011/2/9   问题单号:V2R3C03-ROTUE-MERGE */

#include "vos/vospubh/vos_util.h"
#include "tcpip/ipv6/ppmng/core/include/ppmng_pub.h"
#include "common/ipos/ipv6/basic/icmp6/icmp6_public.h"
#include "common/ipos/ipv6/basic/addrmng/iaddr_inc.h"
#include "common/ipos/ipv6/basic/addrmng/addr_public.h"
#include "tcpip/ipv6/socket6/core/include/sock6_callback.h"


/*--------------------
01 外部使用的库函数声明
---------------------*/
extern VOID *TCPIP_Malloc(ULONG ulInfo, ULONG ulSize);
extern ULONG TCPIP_Free(VOID* pBuf);
extern ULONG VOS_strlen(const CHAR *);
extern LONG VOS_strcmp (const CHAR *, const CHAR *);
extern VOID TCPIP_InfoOutput(CHAR *pInfo);

extern ULONG  TCPIP_GetFullNameByIfIndex(ULONG ulIfIndex,CHAR *pszIfName);
extern ULONG TCPIP_GetIfIndexByFullName(CHAR *pszIfName, ULONG *pulIfIndex);
extern ULONG TCPIP_GetMainIpAddr(ULONG ulIfIndex,ULONG *pulMainAddr, ULONG *pulMainMask);
extern ULONG TCPIP_GetLocalIpAddr(ULONG ulIfIndex, IP_AM4_IF_ADDR_S *pstIPIfAddr);
extern NBB_VOID nbs_get_local_data(NBB_CXT_T NBB_CXT);
extern NBB_VOID nbs_release_local_data(NBB_CXT_T NBB_CXT);
extern NBB_BOOL qopm_initialize(NBB_VOID_PARMS);

extern ULONG TCPIP_CreateMutex(CHAR *pMutexName, ULONG *pulMutexID);
extern ULONG TCPIP_SmP(ULONG ulMutexID);
extern ULONG TCPIP_SmV(ULONG ulMutexID);
extern ULONG TCPIP_DeleteMutex(ULONG ulMutexID);

extern USHORT IP_MaskBitLen(ULONG ulMask);
extern ULONG RM_IsPolicyExist(USHORT usDestType, USHORT usDestProcId, ULONG ulDirFlag);
extern VOID VOS_T_Delay( ULONG ulMillisecond );
extern CHAR *inet_ntop4(const CHAR *pcsrc, CHAR *pcdst, ULONG ulsize);
extern CHAR * inet_ntop6(const CHAR *pSrcAddr,CHAR *pszDstAddr, ULONG ulAddrLen);

/*--------------------
02 外部使用的全局变量声明
---------------------*/
extern NBB_PROC_ID yamb_pid[];
extern NBB_ULONG g_mib_stub_ulCount;
extern OSPF6_INIT_HOOK_FUNC g_pstOSPF6_InitFunc; /*OSPF6 DCL 内部初始化钩子函数*/
extern OSPF6_NM_INIT_HOOK_FUNC g_pstOSPF6_NM_InitFunc;

/*PP4不可以剪裁,所以这里使用PP4模块虚表指针*/
extern struct IIF_COMP_FIBAGENT_ComIntFUNVtbl  *g_pstPp4SfibVtbl;
extern struct IIF_VRF_ComIntFUNVtbl * g_pstI3VRFFunTable;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


