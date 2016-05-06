/****************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_api_ext.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description: 
*   01  定义引用的外部头文件
*   02  声明外部引用的库函数
*   03  声明外部引用的全局变量
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create
*******************************************************************************/
#ifndef OSPF_API_EXT_H
#define OSPF_API_EXT_H

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

/*VISP相关头文件*/
#include "tcpip/public/tcpip_config.h" 
#include "tcpip/public/tcpip_id.h"

#include "vos/vospubh/basetype.h"
#include "vos/vospubh/compbase.h"
/*Added by guojianjun178934, 添加Dopra相关内存操作头文件, 2014/1/8   问题单号:20140108_1 */
#include "vos/vospubh/vos_mem.h"
#include "vos/vospubh/vos_lib.h"
/* End of Added by guojianjun178934, 2014/1/8   问题单号:20140108_1 */
#include "dopra/target/include/v_sm.h"

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#include "tcpip/public/tcpip_debug.h"
#include "tcpip/public/entry/tcpip_entry.h" 
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#include "tcpip/public/arith_cbb/include/mbuf.h"
#include "tcpip/ifnet/include/ifnet_api.h"
#include "tcpip/ifnet/include/iifnet_inc.h"
#include "tcpip/public/tcpip_log.h"
#include "tcpip/ip4/am4/include/am4_api.h"

#include "tcpip/sfib4/include/ifiba_inc.h"
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#include "rtpro/glue/i3agent/i3agent.h"
#include "tcpip/vrf/core/include/vrf_inc.h"
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*VC 编译需要 luogaowei*/
#include "vos/vospubh/vos_util.h"

#include "rpm_type.h"
#include "rm_api.h"
#include "rm_type.h"

/* add for BC3D02908  */
#include "tcpip/acl4/include/acl_api.h"
/* end BC3D02908  */

#include "nsr_ospf_backup_fsm.h"
/*end lihaiming, 2013-02-05*/

#include "tcpip/public/tcpip_basefun.h"
/*End of adding for unsafe function by dutianyi, 2014-05-30*/

/*--------------------
01 外部使用的库函数声明
---------------------*/
extern VOID *TCPIP_Malloc(ULONG ulInfo, ULONG ulSize);
extern ULONG TCPIP_Free(VOID* pBuf);

/*Added by guojianjun178934, 添加Dopra相关内存操作头文件, 2014/1/8   问题单号:20140108_1 */
/* End of Added by guojianjun178934, 2014/1/8   问题单号:20140108_1 */

extern VOID TCPIP_InfoOutput(CHAR *pInfo);

extern ULONG  TCPIP_GetFullNameByIfIndex(ULONG ulIfIndex,CHAR *pszIfName);
extern ULONG TCPIP_GetIfIndexByFullName(CHAR *pszIfName, ULONG *pulIfIndex);
extern ULONG TCPIP_GetMainIpAddr(ULONG ulIfIndex,ULONG *pulMainAddr, ULONG *pulMainMask);
extern ULONG TCPIP_GetLocalIpAddr(ULONG ulIfIndex, IP_AM4_IF_ADDR_S *pstIPIfAddr);
extern NBB_VOID nbs_get_local_data(NBB_CXT_T NBB_CXT);
extern NBB_VOID nbs_release_local_data(NBB_CXT_T NBB_CXT);
extern NBB_BOOL qopm_initialize(NBB_VOID_PARMS);
extern NBB_BOOL qonm_initialize(NBB_CXT_T NBB_CXT);

extern ULONG TCPIP_CreateMutex(CHAR *pMutexName, ULONG *pulMutexID);
extern ULONG TCPIP_SmP(ULONG ulMutexID);
extern ULONG TCPIP_SmV(ULONG ulMutexID);
extern ULONG TCPIP_DeleteMutex(ULONG ulMutexID);

extern USHORT IP_MaskBitLen(ULONG ulMask);

extern ULONG RM_IsPolicyExist(USHORT usDestType, USHORT usDestProcId , ULONG ulAddrFamily,ULONG ulDirFlag);

extern VOID VOS_T_Delay( ULONG ulMillisecond );



/*--------------------
02 外部使用的全局变量声明
---------------------*/
extern NBB_PROC_ID yamb_pid[];
extern NBB_ULONG g_mib_stub_ulCount;
extern OSPF_INIT_HOOK_FUNC g_pstOSPF_InitFunc; /*OSPF DCL 内部初始化钩子函数*/
extern OSPF_NM_INIT_HOOK_FUNC g_pstOSPF_NM_InitFunc; /*OSPF NM DCL 内部初始化钩子函数*/

/*Begin B015 DEL liangjicheng 2008-12-08*/
/*extern OSPF_IF_UPDATE_HOOK_FUNC  g_pstOspfIfAddHookFunc;
extern OSPF_IF_UPDATE_HOOK_FUNC  g_pstOspfIfDelHookFunc;*/
/*End B015 DEL liangjicheng 2008-12-08*/

/*PP4不可以剪裁,所以这里使用PP4模块虚表指针*/
extern struct IIF_COMP_FIBAGENT_ComIntFUNVtbl  *g_pstPp4SfibVtbl;
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
extern struct IIF_VRF_ComIntFUNVtbl * g_pstI3VRFFunTable;
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


