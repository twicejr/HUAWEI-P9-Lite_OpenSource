
/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_api.h
*
*  Project Code: VISPV100R007C02
*   Module Name:   
*   Description: 
*   01  定义引用的外部头文件(为了相关模块可以直接引用)
*   02  声明本本模块库全局变量
*   03  声明本本模块库函数

*   11 ULONG 类型 默认主机序号 
*   12 usProcessId = 0 时，查找所有的OSPF进程
*   13 usProcessId不为0时，查找指定的OSPF进程
*   14 如果ucLsaType =0时，查找所有的LSA
*   15 如果ucLsaType 为1-11时，查找指定类型的LSA
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng       Create
*  2009-4-8     liangjicheng       
*******************************************************************************/
#ifndef _OSPF_API_H_
#define _OSPF_API_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "ospf_api_def.h"
#include "ospf_api_stru01.h"
#include "ospf_api_stru02.h"
#include "ospf_api_stru03.h"
#include "ospf_api_01.h"

/*11 原开发配置接口原形*/
extern OSPF_ERROR_E OSPF_CFG_CmdAreaRangeProc(OSPF_CFGAREARANGE_S *pstAreaRangeIn);
extern OSPF_ERROR_E OSPF_CFG_CmdClearOspfproc(OSPF_CFGRESET_S *pstResetIn);
/*Added by guo00178934, Story交付【S.OSPF.MD5.01】备份MD5序号, 2012/5/19   问题单号:S.OSPF.MD5.01 */
extern OSPF_ERROR_E OSPF_CFG_CmdResetAllOspfproc(VOID);
/* End of Added by guo00178934, 2012/5/19   问题单号:S.OSPF.MD5.01 */
extern OSPF_ERROR_E OSPF_CFG_CmdNeighborProc(OSPF_CFGNEIGHBOR_S *pstPeerIn);
extern OSPF_ERROR_E OSPF_CFG_CmdNetworkAreaProc(OSPF_CFGNETWORK_S *pstNetIn);

extern OSPF_ERROR_E OSPF_CFG_CmdOspfProc(OSPF_CFGPROC_S *pstProcIn);
extern OSPF_ERROR_E OSPF_CFG_CmdRouterOspfProc(OSPF_CFGPROC_WITHRID_S *pstProcIn);
extern OSPF_ERROR_E OSPF_CFG_CmdAreaStubProc(OSPF_CFGAREASTUB_S *pstAreaStubIn);
extern OSPF_ERROR_E OSPF_CFG_CmdAreaProc(OSPF_CFGAREA_S *pstAreaIn);
extern VOID OSPF_ShowAreaAuth_Info(ULONG ulOspfInstance,ULONG ulAreaID);
extern OSPF_ERROR_E OSPF_CFG_CmdGrHelper(OSPF_CFGGRHELPER_S * pstGrHelper);
extern OSPF_ERROR_E OSPF_CFG_CmdGrHelperByPro(OSPF_CFGGRHELPER_PRO_S * pstGrHelper);
/*end for BC3D03437 at 2010-07-16*/
/*Added by guo00178934, 问题单修改, 2011/3/2   问题单号:DTS2011022803652 */
extern OSPF_ERROR_E OSPF_CFG_RouterId(USHORT usProcessId,ULONG ulRouterId);
/* End of Added by guo00178934, 2011/3/2   问题单号:DTS2011022803652 */
extern OSPF_ERROR_E OSPF_CFG_ASBRRouter(OSPF_CFG_ASBR_S *pstAsbr);
extern OSPF_ERROR_E OSPF_CFG_CompRfc1583(OSPF_CFGCOMPRFC1583_S *pstComp);

extern OSPF_ERROR_E OSPF_CFG_IfLsaDelay(OSPF_CFGIFLSADELAY_S *pstLsaDelay);
extern OSPF_ERROR_E OSPF_CFG_IfPollItvl(OSPF_CFGIF_POLL_S *pstIfPoll);
extern OSPF_ERROR_E OSPF_CFG_MaxMtu(OSPF_CFG_MAXMTU_S *pstMaxMtu);
extern OSPF_ERROR_E OSPF_CFG_AreaRfshItvl(OSPF_CFGAREA_RFSHITVL_S *pstAreaRfshItvl);
extern OSPF_ERROR_E OSPF_CFG_CmdMd5Offset ( ULONG ulMd5Offset );
extern VOID OSPF_CFG_CmdBackupSmooth (VOID);

/*12 原开发查询接口原形*/
extern OSPF_ERROR_E OSPF_CMM_Md5Offset_Get ( ULONG *pulMd5Offset );
extern OSPF_ERROR_E OSPF_CMM_Entity_Open(ULONG *pulHandle);
extern OSPF_ERROR_E OSPF_CMM_Entity_Close(ULONG ulHandle);
extern OSPF_ERROR_E OSPF_CMM_Entity_GetFirst(ULONG ulHandle,OSPF_ENTITY_SHOW_S *pstShow);
extern OSPF_ERROR_E OSPF_CMM_Entity_GetNext(ULONG ulHandle,OSPF_ENTITY_SHOW_S *pstShow);
extern OSPF_ERROR_E OSPF_CMM_Area_Open(ULONG *pulHandle, OSPF_SHOWAREA_S *pstAreaIn);
extern OSPF_ERROR_E OSPF_CMM_Area_Close(ULONG ulHandle);
extern OSPF_ERROR_E OSPF_CMM_Area_GetFirst(ULONG ulHandle,OSPF_SHOW_AREA_S *pstShow);
extern OSPF_ERROR_E OSPF_CMM_Area_GetNext(ULONG ulHandle,OSPF_SHOW_AREA_S *pstShow);
extern OSPF_ERROR_E OSPF_CMM_AreaAgg_Open(ULONG *pulHandle);
extern OSPF_ERROR_E OSPF_CMM_AreaAgg_Close(ULONG ulHandle);
extern OSPF_ERROR_E OSPF_CMM_AreaAgg_GetFirst(ULONG ulHandle,OSPF_SHOW_AREA_AGG_S *pstShow);
extern OSPF_ERROR_E OSPF_CMM_AreaAgg_GetNext(ULONG ulHandle,OSPF_SHOW_AREA_AGG_S *pstShow);

extern VOID OSPF_ShowEntityInfo(VOID);

extern VOID OSPF_ShowArea_Info(VOID);
extern VOID OSPF_Show_AreaAgg_Info(VOID);

 /*21 新开发配置接口原形*/

/*CFG 201*/
OSPF_ERROR_E OSPF_CFG_CmdRedistributeProc ( OSPF_CFGREDISTRIBUTE_S* pstRedistIn );
/*CFG 202*/
OSPF_ERROR_E OSPF_CFG_CmdDistributeOutProc ( OSPF_CFGDISTRIBUTE_S* pstDistExpIn );
OSPF_ERROR_E OSPF_CFG_CmdDistributeInProc  ( OSPF_CFGDISTRIBUTE_S*  pstDistImpIn );

/*CFG 204*/
OSPF_ERROR_E OSPF_CFG_CmdIpNetworkProc(OSPF_CFGIF_NETTYPE_S* pstIfNetWork);
OSPF_ERROR_E OSPF_CFG_CmdIpHelloItvlProc(OSPF_CFGIF_HELLO_S* pstIfHelloIn);
OSPF_ERROR_E OSPF_CFG_CmdIpDeadItvlProc(OSPF_CFGIF_DEAD_S *pstIfDeadIn);
OSPF_ERROR_E OSPF_CFG_CmdIpRetransItvlProc(OSPF_CFGIF_RETRANSMIT_S *pstIfRetransIn);
OSPF_ERROR_E OSPF_CFG_CmdIpPriorityProc(OSPF_CFGIF_PRIORITY_S *pstIfPriorityIn);
OSPF_ERROR_E OSPF_CFG_CmdIpCostProc(OSPF_CFGIF_COST_S *pstIfCost);
/*CFG 205*/
OSPF_ERROR_E OSPF_CFG_CmdIfAuthKeyProc(OSPF_CFGIFAUTHKEY_S *pstIpAuthKeyIn);
OSPF_ERROR_E OSPF_CFG_CmdAreaAuthProc(OSPF_CFGAUTHENMODE_S *pstAreaAuthIn);
/*CFG 206*/
OSPF_ERROR_E OSPF_CFG_CmdPreferenceProc (OSPF_CFGPREFERENCE_S* pstPrefIn);
/*CFG 207*/
OSPF_ERROR_E OSPF_CFG_CmdAreaNssaProc(OSPF_CFGAREANSSA_S *pstAreaNssaIn);

/*22 新开发查询接口原形*/

OSPF_ERROR_E OSPF_CMM_Session_Close(ULONG ulSessionId);
/*CMM 101*/
OSPF_ERROR_E OSPF_CMM_If_Open( ULONG *pulSessionId, OSPF_SHOWIF_S * pstIfIn );
OSPF_ERROR_E OSPF_CMM_If_GetFirst(ULONG ulSessionId, OSPF_SHOWIF_OUT_S *pstOspf_ShowIf);
OSPF_ERROR_E OSPF_CMM_If_GetNext(ULONG ulSessionId, OSPF_SHOWIF_OUT_S *pstOspf_ShowIf);
VOID OSPF_ShowIf(USHORT usProcessId);

/*CMM 102*/
OSPF_ERROR_E OSPF_CMM_Nbr_Open( ULONG *pulSessionId,OSPF_SHOWNEIGHBOR_S *pstNbrIn);
OSPF_ERROR_E OSPF_CMM_Nbr_GetFirst( ULONG ulSessionId,OSPF_SHOWNBR_OUT_S *pstOspf_ShowNbr );
OSPF_ERROR_E OSPF_CMM_Nbr_GetNext( ULONG ulSessionId, OSPF_SHOWNBR_OUT_S *pstOspf_ShowNbr);
VOID OSPF_ShowNbr(USHORT usProcessId);

/*CMM 103*/
OSPF_ERROR_E OSPF_CMM_Rout_Open( ULONG* pulSessionId, OSPF_SHOWROUTING_S *pstRoutIn );
OSPF_ERROR_E OSPF_CMM_Rout_GetFirst (ULONG ulSessionId,OSPF_SHOWROUTING_OUT_S * pstRoutOut );
OSPF_ERROR_E OSPF_CMM_Rout_GetNext (ULONG ulSessionId,OSPF_SHOWROUTING_OUT_S * pstRoutOut );
VOID OSPF_ShowOspfRout(USHORT usProcessId);

/*CMM 104*/
OSPF_ERROR_E OSPF_CMM_Lsdb_Open(ULONG *pulSessionId,OSPF_SHOWLSDB_S *pstLsdbIn);
OSPF_ERROR_E OSPF_CMM_Lsdb_GetFirst(ULONG ulSessionId,OSPF_SHOWLSDB_OUT_S *pstOspf_Showlsdb);
OSPF_ERROR_E OSPF_CMM_Lsdb_GetNext(ULONG ulSessionId,OSPF_SHOWLSDB_OUT_S *pstOspf_Showlsdb);
VOID OSPF_ShowLsdb(USHORT usProcessId, ULONG ulType);


/*CMM 105*/
OSPF_ERROR_E OSPF_CMM_PeerCfg_Open(ULONG* pulSessionId, OSPF_SHOWPEERCFG_S *pstPeerCfgIn );
OSPF_ERROR_E OSPF_CMM_PeerCfg_GetFirst (ULONG ulSessionId, OSPF_SHOWPEERCFG_OUT_S * pstPeerCfgOut);
OSPF_ERROR_E OSPF_CMM_PeerCfg_GetNext(ULONG ulSessionId,OSPF_SHOWPEERCFG_OUT_S *pstPeerCfgOut );
VOID OSPF_ShowPeer(USHORT usProcessId);

/*CMM 106*/
OSPF_ERROR_E OSPF_CMM_Network_Open ( ULONG* pulSessionId, OSPF_SHOWNETWORK_S * pstNetworkIn );
OSPF_ERROR_E OSPF_CMM_Network_GetFirst ( ULONG ulSessionId,OSPF_SHOWNETWORK_OUT_S * pstNetworkOut);
OSPF_ERROR_E OSPF_CMM_Network_GetNext ( ULONG ulSessionId, OSPF_SHOWNETWORK_OUT_S * pstNetworkOut);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
VOID OSPF_ShowNetwork(USHORT usProcessId,CHAR *pszVrfName,USHORT usIsAllVRF);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*CMM 107*/
OSPF_ERROR_E OSPF_CMM_Brief_Open ( ULONG* pulSessionId, OSPF_SHOWOSPF_BRIEF_S * pstOspfBriefIn );
OSPF_ERROR_E OSPF_CMM_Brief_GetFirst ( ULONG ulSessionId, OSPF_SHOWOSPF_BRIEF_OUT_S * pstOspfBriefOut );
OSPF_ERROR_E OSPF_CMM_Brief_GetNext ( ULONG ulSessionId,OSPF_SHOWOSPF_BRIEF_OUT_S * pstOspfBriefOut );       
VOID OSPF_ShowBrief(USHORT usProcessId);

/*CMM 108*/
VOID OSPF_CMM_Cumul_Clear(USHORT usProcessId);
OSPF_ERROR_E OSPF_CMM_Cumul_Open(ULONG* pulSessionId, OSPF_SHOWCUMLTVE_S *pstCumulIn );
OSPF_ERROR_E OSPF_CMM_Cumul_GetFirst ( ULONG ulSessionId, OSPF_SHOWCUMLTVE_OUT_S *pstCumulOut);
OSPF_ERROR_E OSPF_CMM_Cumul_GetNext ( ULONG ulSessionId, OSPF_SHOWCUMLTVE_OUT_S *pstCumulOut); 
VOID OSPF_ShowCumul(USHORT usProcessId);

/*CMM 109*/
VOID OSPF_CMM_Error_Clear(USHORT usProcessId);
OSPF_ERROR_E OSPF_CMM_Error_Open ( ULONG *pulSessionId, OSPF_SHOWERROR_S * pstErrorIn );
OSPF_ERROR_E OSPF_CMM_Error_GetFirst ( ULONG ulSessionId,OSPF_SHOWERROR_OUT_S * pstErrorOut );
OSPF_ERROR_E OSPF_CMM_Error_GetNext ( ULONG ulSessionId, OSPF_SHOWERROR_OUT_S * pstErrorOut );
VOID OSPF_ShowError(ULONG ulProcessId);

/*CMM 110*/
OSPF_ERROR_E OSPF_CMM_Import_Open ( ULONG* pulSessionId, OSPF_SHOWIMPORT_S * pstImportIn );
OSPF_ERROR_E OSPF_CMM_Import_GetFirst ( ULONG ulSessionId, OSPF_SHOWIMPORT_OUT_S * pstConfigInfo );
OSPF_ERROR_E OSPF_CMM_Import_GetNext ( ULONG ulSessionId, OSPF_SHOWIMPORT_OUT_S * pstConfigInfo );
/*CMM 111*/
OSPF_ERROR_E  OSPF_CMM_PolicyDist_Open ( ULONG* pulSessionId, OSPF_SHOWPLCYDIST_S * pstPolicyDistIn );
OSPF_ERROR_E OSPF_CMM_PolicyDist_GetFirst ( ULONG ulSessionId, OSPF_SHOWPLCYDIST_OUT_S * pstPolicyDistOut );
OSPF_ERROR_E OSPF_CMM_PolicyDist_GetNext ( ULONG ulSessionId, OSPF_SHOWPLCYDIST_OUT_S * pstPolicyDistOut );
VOID OSPF_ShowImportPolicyInfo(USHORT usProcId);
VOID OSPF_ShowFilterPolicyInfo(USHORT usProcId);

/*32 Query查询接口原形*/

ULONG OSPF_Intermediate_Hook_Register(ULONG ulDirection, 
        OSPF_PACKET_HOOK_FUNC pfOspfFwHookFunc);
ULONG OSPF_Intermediate_UnHook_Register(ULONG ulDirection);

OSPF_ERROR_E OSPF_Direct_OpenNbrEntry(ULONG *pulHandle ,USHORT usProcId);
OSPF_ERROR_E OSPF_Direct_CloseNbrEntry(ULONG ulHandle);
OSPF_ERROR_E OSPF_Direct_GetFirstNbrInfo(ULONG ulHandle, OSPF_SHOWINFO_NBR_S *pstOspf_ShowNbr);
OSPF_ERROR_E OSPF_Direct_GetNextNbrInfo(ULONG ulHandle, OSPF_SHOWINFO_NBR_S *pstOspf_ShowNbr);
VOID OSPF_Direct_ShowNbrInfo(USHORT usProcId);

/*邻居状态(是否可达)通知注册接口*/
ULONG OSPF_NBR_State_Hook_Register(OSPF_NBR_STATE_NOTIFY_FUNC pfNbrStateNotifyFunc);
ULONG OSPF_NBR_State_Hook_UnRegister(VOID);

/* Begin BC3D03438 liangjicheng 2010-08-10*/
/*邻居事件通知注册接口*/
ULONG OSPF_NBR_Event_Hook_Register(OSPF_NBR_EVENT_NOTIFY_FUNC pfNbrEventNotifyFunc);
ULONG OSPF_NBR_Event_Hook_UnRegister(VOID);
/* End   BC3D03438 */

/*Modified by lKF35457, 新增接口状态通知注册注销接口, 2010/10/28   问题单号:DTS2010102700956  */
ULONG OSPF_If_Event_Hook_Register(OSPF_IF_EVENT_NOTIFY_FUNC pfIfEventNotifyFunc);
ULONG OSPF_If_Event_Hook_UnRegister(VOID);
/*End of Modified by lKF35457, 2010/10/28   问题单号:DTS2010102700956  */
/*add by lkf35460 问题单号：DTS2011040603509*/
ULONG OSPF_Get_DR_Info(ULONG ulIfIndex, ULONG ulIpAddr, 
        OSPF_DR_INFO_S *pDrInfo);
/*add end lkf35460 问题单号：DTS2011040603509*/

/*Added by guo00178934, 全系统邻居、LSA个数统计, 2011/7/19   问题单号:DTS2011071901386 */
ULONG OSPF_CMM_SysCount(OSPF_SYS_COUNT_S *pstSysCount);
/* End of Added by guo00178934, 2011/7/19   问题单号:DTS2011071901386 */

/*Modified by liangjicheng 00103192, , 2011/10/28   问题单号: REQ-201106295399-OSPF-PER */
/*******************************************************************************
*    Func Name: OSPF_CFG_CmdCalcDelay
* Date Created: 2011-10-27
*       Author: liangjicheng 00103192
*  Description: 
*        Input: OSPF_CFGCALCDELAY_S *pstCalcDelay
*                USHORT usProcessId; 
*                ULONG ulCaclDelay;  millsecond 1~10000
*       Output: 
*       Return: 成功返回 OSPF_OK；失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-27   liangjicheng 00103192   Create
*
*******************************************************************************/
OSPF_ERROR_E OSPF_CFG_CmdCalcDelay(OSPF_CFGCALCDELAY_S *pstCalcDelay);
/*End of Modified by liangjicheng 00103192, 2011/10/28   问题单号: REQ-201106295399-OSPF-PER */

/*******************************************************************************
*    Func Name: OSPF_Warning_Hook_Register
* Date Created: 2013-09-13
*       Author: guojianjun178934
*  Description: OSPF告警注册钩子函数
*        Input: OSPF_WARNING_HOOK_FUNC pfOSPFWarningHookFun:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-09-13   guojianjun178934        Create
*
*******************************************************************************/
ULONG OSPF_Warning_Hook_Register(OSPF_WARNING_HOOK_FUNC pfOSPFWarningHookFun);

/*Added by guojianjun178934, 【DOPRA IP V3R2C10-同步问题单-DTS2014040401470】【SGSN产品：OSPF】linux x86 系统函数times存在bug，需要VISP提供规避方案 , 2014/6/3   问题单号:DTS2014052908271 */
OSPF_ERROR_E OSPF_CFG_TimerSwitch(ULONG ulTimerType);
OSPF_ERROR_E OSPF_Get_TimerSwitch_Info(OSPF_SHOW_TIMER_SWITCH_S *pstTimerSwitchInfo);
VOID OSPF_Show_TimerSwitch_Info(VOID);
/* End of Added by guojianjun178934, 2014/6/3   问题单号:DTS2014052908271 */


/*******************************************************************************
*    Func Name: OSPF_Enable_CalcHotPatch
* Date Created: 2014-09-09
*       Author: guojianjun178934
*  Description: 浙江移动USN单板只学习到单平面路由热补丁开关,默认关闭
*        Input: ULONG ulHotPatchSwitch:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-09   guojianjun178934        Create
*
*******************************************************************************/
VOID OSPF_Enable_CalcHotPatch(ULONG ulHotPatchSwitch);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _OSPF_SGSN_API_H_ */

