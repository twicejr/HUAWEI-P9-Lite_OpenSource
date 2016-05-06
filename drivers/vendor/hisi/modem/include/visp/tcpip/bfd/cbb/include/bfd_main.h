/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              bfd_main.h
*
*  Project Code: VISPV100R006
*   Module Name: BFD主任务管理模块
*  Date Created: 2006-12-21
*        Author: wujie(61195)
*   Description: BFD主任务管理模块头文件，主要是函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-21  wujie(61195)         Creat the first version.
*
*******************************************************************************/

#ifndef _BFD_MAIN_H_
#define _BFD_MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

VOID BFD_TaskMain(UINTPTR ulArg1, UINTPTR ulArg2, UINTPTR ulArg3, UINTPTR ulArg4);
VOID BFD_ProcIPEvent (ULONG ulEvType, ULONG ulIPAddr, ULONG ulIfIndex);
VOID BFD6_ProcIPEvent(ULONG ulEvType, UINTPTR ulIP6AddrHandle, ULONG ulIfIndex);
VOID BFD_ProcTrunkPortEvent(ULONG ulEvType, ULONG ulPortIfIndex);
VOID BFD_TrunkPortEventCoreProc(ULONG ulWarnType, ULONG ulPortIfIndex, ULONG ulVrfIndex, ULONG ulIpVer);
/* Bein:VISP1.7C03 VRF wangchengyang,2009-01-20 */
VOID BFD_ProcGloableDisable(ULONG ulCurVrfIndex,ULONG ulCurSessionID,ULONG ulIpVersion);
ULONG BFD6_ProcGloableDisableOneVrf(ULONG ulCurVrfIndex,ULONG *pulCurSessionID);
/*Added by qinyun62011, 优化BFD会话ID扩展到9215的性能问题, 2013/9/27 */
ULONG BFD_ProcGloableDisableOneVrf(ULONG ulCurVrfIndex,ULONG *pulCurSessionID);
VOID BFD_ProcSessionDelete(BFD_SESS_ENTRY_S *pstBFDSessEntry);
/* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */
/* Modified by qinyun62011, DTS2013101804899 删除队列判断，依赖Dopra函数的返回即可, 2013/10/18 */
ULONG BFD_GetCPUType(CHAR *pCPUType);
VOID BFD_License_ProcAdminUp(ULONG ulVrfIndex, ULONG ulSessionID);
VOID BFD_Proc_LicenseMsg(ULONG ulCurVrfIndex, ULONG ulCurSessionId, ULONG ulBfdLicenseIsOn);
VOID BFD_ProcResetAll(ULONG ulIpVerison);
VOID BFD_ProcShutDown(BFD_SESS_ENTRY_S *pstBFDSessEntry);
VOID BFD_ProcNoShutDown(ULONG ulSessionID,BFD_SESS_ENTRY_S *pstBFDSessEntry);
VOID BFD_ProcDownAll(ULONG ulIpVersion);
#ifdef __cplusplus
}
#endif

#endif

