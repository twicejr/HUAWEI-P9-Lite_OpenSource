
#ifndef      _ND_FUNC_H_
#define      _ND_FUNC_H_

#ifdef      __cplusplus
extern "C"{
#endif

#include "tcpip/public/vrpvos/rdx6_pub.h"

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/
#define IP6_ND_CORE_LOG     g_stNDCallBack.pfIP6ND_SH_LogToIPOSIC

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/* nd_src.c */
ULONG IP6_ND_QueryInterface(IUnknown * This, COMP_IID iid,
                                    VOID **ndvObj);

VOID IP6_ND_VOID_DUMMY();
VOID* IP6_ND_POINTER_DUMMY();
ULONG IP6_ND_ULONG_DUMMY();

/****************************************************************************/

/* nd.c */
ULONG IP6_ND_Init_Com_New(IPB_IR_ND_COM_ID_INFO_S *pstComInfo, ULONG ulComLen);
ULONG IP6_ND_Activate_Com(VOID);
ULONG IP6_ND_SetResSpecs(SPECS_RES_VALUE_S  *pstResSpecs);
ULONG IP6_ND_SetModuleInfo(IP6_ND_MOD_INFO_S *pstMInfo);

ULONG IP6_ND_SH_RegCallbackFunc (IP6_ND_SH_CALLBACK_FUNC_S
                                             *pstNDShellCallback);

/*nd.c*/
VOID IP6_ND_NDInfoInit(IP6IFNET_S *pstIP6Ifnet);

VOID IP6_ND_NDInfoFree(const IP6IFNET_S *pstIP6Ifnet);

VOID IP6_ND_AddPrefix(ULONG ulIfnetIndex, IN6ADDR_S  stPrefixInfo,
                                            ULONG ulPrefixLength);

VOID IP6_ND_DeletePrefix(ULONG ulIfnetIndex, IN6ADDR_S  stPrefixInfo);

/* AC4D01348 - Added by Prabhu H (71185) */
VOID IP6_ND_UpdatePrefixStatus(const IP6IFNET_S *pstIp6Ifnet,
                               const IN6ADDR_S  *pstPrefixInfo,
                               ULONG ulStatus);

VOID IP6_ND_AddAddr(const IP6IFADDR_S *pstAddr);

VOID IP6_ND_DelAddr(const IP6IFADDR_S *pstAddr);

VOID IP6_ND_UpDownNotify(VOID *pvIf,ULONG ulCmd,CHAR *pcData);

VOID IP6_ND_ShutDownNotify(VOID *pvIf);

VOID IP6_ND_PhyUpDownNotify(VOID *pvIf,ULONG ulCmd,CHAR *pcData);

VOID IP6_ND_LLAddrNotify(VOID *pvIf, CHAR *pcData);

VOID IP6_ND_Create_NA_Timer(ND_NA_S *pstNAInfo);

VOID IP6_ND_NA_Timeout(ND_TIMER_S  *pstTimerMsg);

/* Deletion BCQ-NDHOST Begin: By Srinivas D S on 21-2-2008
   Desc: Function defnition is not there */

/* Deletion BCQ-NDHOST End: By Srinivas D S on 21-2-2008 */

ULONG IP6_ND_Event_To_NDTask(IP6_ND_CTRLMSG_S *pstCtrMsg);

ULONG IP6_ND_HostTimeoutHandler(IP6_ND_HOST_TMRMSG_S *pstTmrMsg);

ULONG IP6_ND_CtrlMsgNotify(UINTPTR *pulCtrMsg);

VOID IP6_ND_DeleteTimers(ULONG ulTimerID);

VOID IP6_ND_NDHostInfoFree (NDINFO_S *pstNDInfo);

ULONG IP6_ND_PAF_Validate (const SPECS_RES_VALUE_S *pstResSpecs,
                ULONG ulDefMinValue, ULONG ulDefMaxValue);
VOID IP6_ND_PAF_LoadValues (SPECS_RES_VALUE_S *pstResSpecsDS,
                const SPECS_RES_VALUE_S *pstNewResSpecs);
VOID IP6_ND_PAF_ReloadPercentValues (SPECS_RES_VALUE_S *pstResSpecsDS,
                                     SPECS_RES_VALUE_S *pstNewResSpecs,
                                    ULONG ulPercentage);
VOID IP6_ND_PAF_CompareAndLoadValues (SPECS_RES_VALUE_S *pstResSpecsDS,
                                         SPECS_RES_VALUE_S *pstNewResSpecs);
ULONG IP6_ND_Verify_Inf_Stat_NBEntries(VOID);
VOID IP6_ND_PAF_SetDefaults_MaxDefRtrInIntf(VOID);
VOID IP6_ND_PAF_SetDefaults_MaxPrefListInf(VOID);
VOID IP6_ND_PAF_SetDefaults_MaxDestCache(VOID);
VOID IP6_ND_PAF_LoadDefaultValues(SPECS_RES_VALUE_S *pstResSpecsDS,
                ULONG ulMinVal, ULONG ulMaxVal, ULONG ulAvailVal);
VOID IP6_ND_PAF_LoadAllNBDefaultValues(VOID);
VOID IP6_ND_PAF_ComputeValues (SPECS_RES_VALUE_S *pstBaseResSpecs,
                SPECS_RES_VALUE_S *pstNewResSpecs);

/****************************************************************************/
/*nd_nb.c*/

VOID IP6_ND_Second_Since1970(ULONG ulDate, ULONG ulTime, ULONG *pulRetTime);

ULONG IP6_ND_VOS_time(ULONG *pulTimeRet);

VOID IP6_ND_NS_Input(MBUF_S *pstMbuf, LONG lOff, LONG lIcmp6Len);

VOID IP6_ND_NA_Input(MBUF_S *pstMbuf, LONG lOff, LONG lIcmp6Len);

VOID IP6_ND_NS_Output(const ND_NS_S *pstNSInfo);

VOID IP6_ND_NA_Output(const ND_NA_S *pstNAInfo);

VOID IP6_ND_NB_Timeout(ND_TIMER_S  *pstNDTimer);

ULONG IP6_ND_SetNSRetransTimer(NDINFO_S *pstNDInfo, ULONG ulValue);

/****************************************************************************/
/*nd_mgt.c*/

ULONG IP6_ND_GetStaticEntryCount(ULONG ulIfNetIndex, ULONG *pulStaticNBCount);

NDINFO_S    *IP6_ND_GetNDInfoByIndex(ULONG ulIfnetIndex);

NDINFO_S *IP6_ND_GetNDInfoByIfnet(const VOID *pvIfnet);

VOID  IP6_ND_Option_Init(VOID *pvOpt, LONG lIcmpLen, ND_OPT_U *punNDOpt);

ND_OPT_HDR_S *IP6_ND_Option(ND_OPT_U *punNDOpt);

ULONG  IP6_ND_Options(ND_OPT_U *punNDOpt);

ULONG IP6_ND_GetLinkLocalAddr (ULONG ulIfIndex,
                                        const IN6ADDR_S *pstInAddr,
                                        IN6ADDR_S **pstOutAddr);

ULONG IP6_ND_GetLinkLayerAddr (ULONG ulIfIndex,
                                         const IN6ADDR_S *pstAddr,
                                         UCHAR **ppucllAddr);

ULONG IP6_ND_IsNextHopRouterHost (ULONG ulIfIndex,
                                             const IN6ADDR_S st_Addr);

ULONG IP6_ND_EnableRouterFlag (VOID);

ULONG IP6_ND_DisableRouterFlag (VOID);

ND_GETFROMCORE_S    *IP6_ND_GetNDInfoFromCore(VOID *pvIfnet);

VOID IP6_ND_SetLastChangeTime(ND_NBENTRY_S  *pstNBEntry);

ULONG IP6_ND_Lookup (MBUF_S *pMbuf);

ULONG IP6_ND_Start_Timer(VOID *pvTimerMsg, ULONG ulTimeMilliSec,
          ULONG *pulTimerId);

ULONG IP6_ND_Stop_Timer(ULONG ulTimerID);

ULONG IP6_ND_FindNHAndOGIntf(MBUF_S * pstMBuf, const IP6_PKTOPTS_S * pstOpt,
           ULONG ulZoneId, LONG lFlags);

VOID IP6_ND_NotifyRouteChange(SFIB6_ROUTEINFO_S * pstRtInfo, ULONG ulEvent);

ULONG IP6_ND_FindNHAndOGIntf_ForDestAddr (IP6_ND_NHINPUTPARAM_S *pstNHInput,
           IP6_ND_NHOUTPUTPARAM_S *pstNHOut);
ULONG IP6_ND_GetNHInfo(IN6ADDR_S *pstDestAddr, NHINFO_S *pstNHInfo);
BOOL_T IP6_ND_IsNodeHost(VOID);



/****************************************************************************/
/* nd_cfg.c */

ULONG IP6_ND_SetManageFlag (ULONG ulIfnetIndex,
                                      IP6_ND_SETFLAG_E enFlag);

ULONG IP6_ND_SetOtherFlag (ULONG ulIfnetIndex, IP6_ND_SETFLAG_E enFlag);

ULONG IP6_ND_SetReachableTime (ULONG ulIfnetIndex, ULONG ulValue,
                                    IP6_ND_SETFLAG_E enFlag);

ULONG IP6_ND_SetRAInterval (ULONG ulIfnetIndex, ULONG ulValue,
                                    IP6_ND_SETFLAG_E enFlag);

/* Begin : Defect ID: BYAD12218,     Modifier:Rajesh,   Date:2004/9/13
        Reason   : To config Minimum RA interval.*/

ULONG IP6_ND_SetRAMinInterval (ULONG ulIfnetIndex, ULONG ulValue,
                                                IP6_ND_SETFLAG_E     enFlag);
ULONG IP6_ND_SetDefaultTime (ULONG ulIfnetIndex, ULONG ulValue,
                                                IP6_ND_SETFLAG_E enFlag);

ULONG IP6_ND_SetHopLimit (UCHAR ucValue, IP6_ND_SETFLAG_E enFlag);

ULONG IP6_ND_SetDeleteEntryLimit(ULONG ulEntryToDelete);



VOID IP6_ND_SetVlink(ULONG ulFlag);
VOID IP6_ND_SetGlobalValue(ULONG ulValue);

/* Begin : Defect ID: BYAD011817,     Modifier:Rajesh,   Date:2004/9/15
Reason   : Component issues*/
VOID IP6_ND_Reboot(VOID);

UCHAR IP6_ND_GetHopLimit (VOID);

ULONG IP6_ND_SetSuppressRAFlag(ULONG ulIfnetIndex,
                                          IP6_ND_SETFLAG_E enFlag);

ULONG IP6_ND_SetNSInterval (ULONG ulIfnetIndex, ULONG ulValue,
                                                IP6_ND_SETFLAG_E enFlag);

ULONG IP6_ND_SetDADAttempt (ULONG ulIfnetIndex, ULONG ulValue,
                                                IP6_ND_SETFLAG_E enFlag);


/* Clear NB entries Cmd */
ULONG IP6_ND_AddStaticNBEntry(ND_STATIC_NBENTRY_S *pstStaticNBEntry);


ULONG IP6_ND_DelStaticNBEntry(ULONG ulIfNetIndex,
                                        IN6ADDR_S  stIn6Addr);

ULONG IP6_ND_ResetStaticNBEntries(VOID);

ULONG IP6_ND_ResetDynamicNBEntries(VOID);

ULONG IP6_ND_ResetIfAllNBEntries(VOID *pvIfNet);

ULONG IP6_ND_ResetAllNBEntries(VOID);

ULONG  IP6_ND_GetManageFlag (ULONG ulIfnetIndex, UCHAR *pucRetVal);
ULONG  IP6_ND_GetOtherFlag (ULONG ulIfnetIndex, UCHAR *pucRetVal);
ULONG  IP6_ND_GetReachableTime (ULONG ulIfnetIndex,
                                           ULONG *pulRetVal);
ULONG  IP6_ND_GetRAInterval (ULONG ulIfnetIndex, ULONG *pulRetVal);
ULONG  IP6_ND_GetRAMinInterval (ULONG ulIfnetIndex, ULONG *pulRetVal);
ULONG  IP6_ND_GetDefaultTime(ULONG ulIfnetIndex, ULONG *pulRetVal);
UCHAR  IP6_ND_GetHopLimit (VOID);

ULONG  IP6_ND_GetRAFlag (ULONG ulIfnetIndex, UCHAR *pucRetVal);

ULONG  IP6_ND_GetNSInterval (ULONG ulIfnetIndex, ULONG *pulRetVal);

ULONG  IP6_ND_GetDADAttempt (ULONG ulIfnetIndex, ULONG *pulRetVal);
ULONG  IP6_ND_GetDeleteEntryLimit(ULONG *pulRetVal);
ULONG  IP6_ND_GetDebug (ULONG *pulRetVal);
ULONG IP6_ND_SGSN_RegCallbackFunc(
            IP6_ND_SGSN_CALLBACK_FUNC_S *pstNDSgsnCallback);

ULONG IP6_ND_SOCK_RegCallbackFunc(
            IP6_ND_SOCK_CALLBACK_SET_S *pstNDSocketCallback);

ULONG IP6_ND_Flow_RegCallbackFunc(IP6_ND_FLOW_CALLBACK_SET_S *pstFlowCallback);

/* Set prefix info related */
ULONG IP6_ND_ProcPrefixInfo (ULONG ulIfIndex, ULONG ulNo,
            ULONG ulValidTime, UCHAR ucAutoConfFlag,
            ULONG ulPreferredTime, ULONG ulPrefixLength,
            IN6ADDR_S stAddrPrefix, UCHAR ucOnLinkFlag);

ULONG IP6_ND_GetIntfHopLimit(ULONG ulIfIndex, ULONG *pulHopLimit);
ULONG IP6_ND_GetNDHostParams(ULONG ulIfIndex,
            IP6_ND_GETHOSTPARAMS_S *pstHostParams);
ULONG IP6_ND_SetDebug(IP6_ND_CFG_OPT_E enFlag);
ULONG IP6_ND_GetDebug (ULONG *pulRetVal);
ULONG IP6_ND_ResetIfAllNBEntriesPerVLAN(ULONG ulIfIndex, ULONG ulVlanId, UCHAR ucType);

/****************************************************************************/
/* nd_display.c */
ULONG IP6_ND_GetFirstExt(VOID *pvIfNet,
                                ND_NBENTRY_INFO_S *pstNBEntryOut,
                                UINTPTR ulNBWaitListHandle);

ULONG IP6_ND_OpenTable(UINTPTR *pulWaitListHandle);

VOID IP6_ND_CloseTable(UINTPTR ulNBWaitListHandle);

ULONG IP6_ND_GetNextExt(UINTPTR ulNBWaitListHandle,
                                ND_NBENTRY_INFO_S*pstNextNBInfo);
ND_NBENTRY_S *IP6_ND_GetNextNode(ND_NBENTRY_S *pstCurrentNode);

ULONG IP6_ND_IsNBEntryStatic(VOID *pvCurrentNode);

VOID *IP6_ND_WaitListSet(UINTPTR ulNBWaitListHandle, ULONG *pstNBNode,
                                                        ULONG *pstCurrentNode);

ND_NBENTRY_S *IP6_ND_NeighborEntry_NodeGetNext (VOID *pCur, VOID **ppNext);
ULONG IP6_ND_OpenIOTable(UINTPTR *pulWaitListHandle, VOID *pvIfNet);

ND_NBENTRY_S *IP6_ND_UpdateCache(VOID *pvIfNet,  IN6ADDR_S *pstFromAddr,
                                  UCHAR *pucLLAddr, BOOL_T  usMsgType,
                                  ND_PKT_CTLPARAM_S *pstNDCtrlParam);

/* Changes for VLAN & VLANIF framework by karthik 70713 in Nov 2009 */
ND_NBENTRY_S *IP6_ND_UpdateCacheNoSLLA(VOID *pvIfNet,
                                                IN6ADDR_S *pstFromAddr,
                                                const IN6ADDR_S *pstTargetddr,
                                                ND_PKT_CTLPARAM_S *pstNDCtrlParam);

ND_NBENTRY_S *IP6_ND_NBEntryLookup(ULONG ulIndex, IN6ADDR_S stIPv6Addr);

ULONG IP6_ND_FetchNBEntry(ULONG ulIfnetIndex, IN6ADDR_S *pstIPv6Addr,
                                                ND_NBENTRY_INFO_S *pstNBInfo);

/* Changes for VLAN & VLANIF framework by karthik 70713 in Nov 2009 */
ND_NBENTRY_S *IP6_ND_NBEntryAdd(ULONG ulIfnetIndex,
                            IN6ADDR_S stIPv6Addr, UCHAR *pucLLAddr,
                            IP6_ND_ADDNBMSG_S *pstAddNBInfo);

ULONG IP6_ND_NBEntryDel(ND_NBENTRY_S *pstNBEntry);

void IP6_ND_NBEntryDelLeastUsed(ULONG ulIfnetIndex);

VOID IP6_ND_DeleteNeighbour(IN6ADDR_S stIn6Addr, ULONG ulIfIndex);

ULONG IP6_ND_HostDispOpenTable(ULONG ulWaitListIndex, UINTPTR *pulHandle,
            WAITLIST_GETNEXTFUNC  pfWaitlistCallBackToRegister);
ULONG IP6_ND_HostCloseTable(UINTPTR ulWaitListHandle, ULONG ulWaitListIndex);
ULONG IP6_ND_DefRouterOpenTable(ULONG ulIfIndex, UINTPTR *pulHandle);
ULONG IP6_ND_DefRouterCloseTable(UINTPTR ulWaitListHandle);
ULONG IP6_ND_PrefixListOpenTable(ULONG ulIfIndex, UINTPTR *pulHandle);
ULONG IP6_ND_PrefixListCloseTable(UINTPTR ulWaitListHandle);
ULONG IP6_ND_DestinationCacheOpenTable(UINTPTR *pulHandle);
ULONG IP6_ND_GblPrefixListOpenTable(UINTPTR *pulHandle);
ULONG IP6_ND_DestinationCacheCloseTable(UINTPTR ulWaitListHandle);
ULONG IP6_ND_GblPrefixListCloseTable(UINTPTR ulWaitListHandle);
VOID *IP6_ND_NBEntry_GetNextNode(VOID *pvInHelperParam,
                                                    VOID **ppvOutHelperParam);

/****************************************************************************/
/* nd_rt.c */

ULONG  IP6_ND_NewCliPrefix(ULONG ulIfnetIndex, ND_PREFIX_S **pstPrefix);

ND_PREFIX_S  *IP6_ND_NewPrefix(ULONG ulIfnetIndex);

ULONG IP6_ND_DelCliPrefix(ND_PREFIX_S *pstPrefix);

ULONG IP6_ND_DelPrefix(ND_PREFIX_S *pstPrefix);

 /* Modified by Rajesh for defect id : SWFD07118 */
ND_PREFIX_S  * IP6_ND_FindCliPrefix(ULONG ulIfnetIndex,
                                            IN6ADDR_S stPrefix,
                                            ULONG ulPrefixLength);

ULONG IP6_ND_FindExactMatchCliPrefix(ULONG ulIfnetIndex,
                                              IN6ADDR_S *pstPrefix,
                                              ULONG ulPrefixLength,
                                              ND_PREFIX_S **ppstOutPrefix);


ND_PREFIX_S  * IP6_ND_FindPrefix(ULONG ulIfnetIndex, IN6ADDR_S stPrefix);

VOID IP6_ND_RA_Output (ND_RA_S *pstRAInfo,
                               IP6_TYPE_OF_OPERATION_E enOpType);

VOID IP6_ND_RA_Timer_Create(ND_RA_S *pstRAInfo);

VOID IP6_ND_RA_TimeOut(ND_TIMER_S  *pstTimerMsg);

VOID IP6_ND_Unicast_RA_Timer_Create(ND_RA_S *pstRAInfo);

VOID  IP6_ND_RA_Timer_Update(ULONG ulIfnetIndex,ULONG ulTimeValue);

VOID IP6_ND_RA_Input(MBUF_S *pMbuf,LONG lOff, LONG lIcmp6Len);

VOID IP6_ND_RS_Input(MBUF_S *pMbuf,LONG lOff, LONG lIcmp6Len);

ULONG IP6_ND_RS_Output(NDINFO_S *pstNDInfo);
MBUF_S *IP6_ND_Make_Packet(ND_RA_S *pstRAInfo,
                                    IP6_TYPE_OF_OPERATION_E enOpType);
ULONG IP6_ND_ProcessRAParams(IP6_ND_RAHOSTPARAMS_S *pstRAHostParams,
                                            NDINFO_S *pstNDInfo);
ULONG IP6_ND_ParameterDiscovery(NDINFO_S *pstNDInfo, IN6ADDR_S *pstRouterAddr,
                                            IP6_ND_RAOTHERPARAMS_S *pstRAParam);
ULONG IP6_ND_ProcessBaseReachTime(NDINFO_S  *pstNDInfo, ULONG ulBaseReachTime);
ULONG IP6_ND_RandReachTime(ULONG ulBaseReachTime);
ULONG IP6_ND_ProcessPrefixOptions(NDINFO_S *pstNDInfo, DLL_S *pstPrefixHead);
ULONG IP6_ND_ProcessMandOFlag(NDINFO_S *pstNDInfo,
            IP6_ND_RAHOSTPARAMS_S *pstRAHostParams);
ULONG IP6_ND_GenerateRandReachTime(ULONG ulBaseReachTime);
ULONG IP6_ND_UpdateRandReachTime(NDINFO_S *pstNDInfo);
ULONG IP6_ND_RS_ReTransTimerCreate(NDINFO_S *pstNDInfo);
ULONG IP6_ND_RS_Retrans_Timeout (IP6_ND_HOST_TMRMSG_S *pstTmrMsg,
            NDINFO_S *pstNDInfo);
ULONG IP6_ND_ReachTimeRecompute_Timeout(NDINFO_S *pstNDInfo);

ULONG IP6_ND_Random(VOID);

/****************************************************************************/
/* nd_dad.c */

VOID IP6_ND_DAD_Delete(DAD_S *pstDAD);

VOID IP6_ND_DAD_Timeout(VOID);
VOID  IP6_ND_NBCacheCleanup_Timeout(ND_TIMER_S *pstTimerMsg);

DAD_S *IP6_ND_DAD_Lookup(const NDINFO_S *pstNDInfo,
                         const IP6IFADDR_S    *pstIPv6Addr);

VOID IP6_ND_DADStart(IP6IFADDR_S *pstIpIfAddr);

VOID IP6_ND_DADStop(const IP6IFADDR_S *pstIp6IfAddr);

VOID IP6_ND_DADStopAll(VOID *pvIf);

VOID IP6_ND_DAD_NS_Input(IP6IFADDR_S *pstTAddr);

VOID IP6_ND_DAD_NA_Input(IP6IFADDR_S *pstTAddr);

VOID IP6_ND_DAD_Duplicate(DAD_S *pstDAD,IP6IFADDR_S *pstIp6IfAddr);

VOID IP6_ND_DAD_NS_Output(const DAD_S *pstDAD);

ULONG IP6_ND_DAD_Duplicate_On_InitDelay(IP6IFADDR_S *pstTAddr,
            NDINFO_S *pstNDInfo, IP6IFNET_S *pstIp6If);

/****************************************************************************/

ULONG Random();

/*For MIB*/
ULONG IP6_ND_AddrPrefixTbl_GetNextEntry(ULONG ulIfIndex,
                           IP6_ND_PrefixTbl_S  *pstOutPfxTblEntry);
ULONG IP6_ND_AddrPrefixTbl_GetEntry(ULONG ulIfIndex,
                        IP6_ND_PrefixTbl_S  *pstOutPfxTblEntry);
ULONG IP6_ND_AddrPrefixTbl_GetFirst(IP6_ND_PrefixTbl_S
                                                *pstOutPfxTblEntry);

/* Change for def: AC4D00949 & AC4D00947
  Reason: Have to perform basic validation for the physical address*/
ULONG IP6_ND_IfValidMacAddr(const UCHAR szMac[]);

/*End of change for AC4D00949 & AC4D00947*/

ULONG IP6_ND_HA_RegisterCallBack
                        (IP6_ND_SH_HA_CALLBACK_FUNC_S *pfCallBackSet);



ULONG IP6_ND_GetVlinkStatus(VOID);
VOID IP6_ND_NBForceDelTimer_Create(ULONG ulIfnetIndex,
                                                NDINFO_S *pstNDInfo);


ULONG IP6_ND_GetTimerQueueID(ULONG *pulTimerQueID);
ULONG IP6_ND_GetTaskID (ULONG *pulTaskID);
VOID IP6_ND_SetTimerQueueID(ULONG ulTimerQueueID);
ULONG IP6_ND_ClearRATimerId(ULONG ulIfindex);


/* VOID IP6_ND_AsynEnQue(ND_TIMER_S    *pstRcvMsg); */

VOID IP6_ND_AsynEnQue(IP6_ND_EVENTMSG_S *pstRcvMsg);



VOID IP6_ND_ResetDadAttempts (ULONG ulIfnetIndex);



/*Change for def: AC4D01214 by karthik70713 desc: Neighbor cache is
 getting updated with the address present  in the local interface*/

ULONG IP6_ND_NBValidate_Address(IN6ADDR_S  stIn6Addr,
                                UCHAR *pucLLAddr,
                                UCHAR ucFlag, ULONG ulIfIndex);

ULONG IP6_ND_GetNode(UINTPTR ulNBWaitListHandle,
                             ND_NBENTRY_INFO_S *pstNBInfo);

ULONG IP6_ND_NBEntryDelOneLeastUsed(NDINFO_S *pstNDInfo);
ULONG IP6_ND_SearchAllIntfToDelNBEntry(NDINFO_S *pstNDInfo);

/****************************************************************************/
/* nd_hst_util.c */

VOID IP6_ND_Util_NodeFree(VOID *pvMsg);
ULONG IP6_ND_Util_GetNodeCount(const DLL_S *pstHead, ULONG *pulCount);
ULONG IP6_ND_Util_GetFirstNode(const DLL_S *pstHead, VOID **ppstNode);
ULONG IP6_ND_Util_GetNextNode(const DLL_S *pstHead,
            const VOID *pvCurNode, VOID **ppvNextNode);
ULONG IP6_ND_Util_FreeList(DLL_S *pstHead);
ULONG IP6_ND_Util_GetDefRouterNode(IN6ADDR_S *pstIPv6Addr, DLL_S *pstHead,
            IP6_ND_DEFROUTER_LIST_S **ppstDefRouterNode);
ULONG IP6_ND_Util_AddDefRouterNode(IN6ADDR_S *pstIPv6Addr,
            IP6_ND_DEFRTRSTATE_E enState, NDINFO_S *pstNDInfo,
            IP6_ND_DEFROUTER_LIST_S **pstDefRouterNode);
ULONG IP6_ND_Util_AddNodeToGlobalDefRtrList(ULONG ulIfIndex);
ULONG IP6_ND_Util_GetIntrfaceDfltRtr(ULONG ulVrfIndex, ULONG *pulIfIndex,
                                                IN6ADDR_S *pstDefRouteAddr);
ULONG IP6_ND_Util_SelectDefaultRouter(NDINFO_S *pstNDInfo,
            IN6ADDR_S *pstDefaultRtr);
ULONG IP6_ND_Util_UpdateDefRouterNodeState(NDINFO_S *pstNDInfo,
            IP6_ND_DEFRTRSTATE_E enState, IN6ADDR_S *pstIPv6Addr);
ULONG IP6_ND_Util_DeleteDefRouterNode(NDINFO_S *pstNDInfo,
            IP6_ND_DEFROUTER_LIST_S *pstDeleteNode);
ULONG IP6_ND_Util_GetIntfPrefixListNode(IN6ADDR_S *pstIPv6Addr,
            ULONG ulPrefixLen, DLL_S *pstHead,
            IP6_ND_INTFPREFIX_LIST_S **pstIntfPrefixListNode);
ULONG IP6_ND_Util_AddIntfPrefixListNode(
            IP6_ND_PREFIXOPTLIST_S *pstPrefixOption,
            DLL_S *pstHead, IP6_ND_INTFPREFIX_LIST_S **pstNode);
ULONG IP6_ND_Util_DelIntfPrefixListNode(DLL_S *pstHead,
            IP6_ND_INTFPREFIX_LIST_S *pstDeleteNode);
ULONG IP6_ND_Util_AddOnlinkAutonomusPrefix
            (IP6_ND_PREFIX_PARAM_S *pstPrefixInput, DLL_S *pstHead);
ULONG IP6_ND_Util_DelNodeFromGlobalDefRtrList(ULONG ulIfIndex);
ULONG IP6_ND_Util_ValidateAddrWithTime(
            const IP6_ND_IN6ADDRWITHTIME_S  *pstAddrWithTime, ULONG ulAddrCnt,
            IP6_ND_STATEFULCFG_OPTTYPE_E enAddUpdateFlag);
ULONG IP6_ND_Util_ValidateOtherConfigParams(
            IP6_ND_OTHERCFGPARAMS_S *pstOtherCfgParam);
ULONG IP6_ND_Util_ValidateOnlinkPrefixes(IP6_ND_PREFIX_PARAM_S *pstPrefixInput,
            ULONG ulIfnetIndex);

/****************************************************************************/
/* nd_plmgmt.c */

/* Interface Prefix List function */
ULONG IP6_ND_PrefixDiscovery(NDINFO_S *pstNDInfo,
            IP6_ND_PREFIXOPTLIST_S *pstPrefixOption);
ULONG IP6_ND_AddNodeToIntfPrefixList(NDINFO_S *pstNDInfo,
            IP6_ND_PREFIXOPTLIST_S *pstPrefixOption,
            IP6_ND_INTFPREFIX_LIST_S **ppstPrefixListNode);
ULONG IP6_ND_DeleteIntfPrefixListEntry(NDINFO_S *pstNDInfo,
            IP6_ND_INTFPREFIX_LIST_S *pstPrefixListNode);
ULONG IP6_ND_GetPrefixListEntryCount(ULONG ulIfIndex,
            ULONG *pulPrefixListEntryCnt);
ULONG IP6_ND_StartPrefixEntryTimer(ULONG ulIfIndex,
            IP6_ND_INTFPREFIX_LIST_S *pstPrefixListNode);
ULONG IP6_ND_PrefixListGetFirst(UINTPTR ulWaitListHandle,
            IP6_ND_INTFPREFIX_INFO_S *pstPrefixEntryOut);
ULONG IP6_ND_PrefixListGetNext(UINTPTR ulWaitListHandle,
            IP6_ND_INTFPREFIX_INFO_S *pstPrefixEntryOut);
VOID * IP6_ND_PrefixList_NodeGetNext (VOID *pInHelperParam,
            VOID **ppOutHelperParam);
VOID * IP6_ND_PrefixList_NodeGetNext (VOID *pInHelperParam,
            VOID **ppOutHelperParam);
ULONG IP6_ND_FlushIntfPrefixList (NDINFO_S *pstNDInfo);
ULONG IP6_ND_DeleteAllIntfPrefixEntries(ULONG ulIfIndex);

/* Global Prefix List function */
ULONG IP6_ND_AddToGlobalPrefixList(IN6ADDR_S *pstPrefix, ULONG ulIfnetIndex,
                                    ULONG ulPrefixLen, ULONG ulVrfIndex);
ULONG IP6_ND_DeleteGlobalPrefixNode(VOS_RDX6_EXTNODE_S *pstDelExtNode, ULONG ulVrfIndex);
ULONG IP6_ND_DeleteIntfGlobalPrefixList (ULONG ulIfnetIndex);
ULONG IP6_ND_GetGlobalPrefixMatch(ULONG ulVrfIndex, IN6ADDR_S *pstAddrPrefix,
                                    IP6_ND_GLOBALPREFIX_LIST_S **ppstPrefix);
ULONG IP6_ND_SrchAndDelFrmGlobalPrefixList(IN6ADDR_S *pstPrefix,
                                                ULONG ulPrefixLen, ULONG ulVrfIndex);
ULONG IP6_ND_GetFirstGblPrefixEntry (UINTPTR ulWtLstHandle, ULONG ulVrfIndex,
                                IP6_ND_GLOBALPREFIX_INFO_S *pstGblPfxEntryOut);
ULONG IP6_ND_GetNextGblPrefixEntry (UINTPTR ulWtLstHandle,
            IP6_ND_GLOBALPREFIX_INFO_S *pstGblPfxEntryOut);
VOID * IP6_ND_GblPrefix_WaitListGetNext (VOID *pvCurNode, VOID **ppvNxtNode);
ULONG IP6_ND_PrefixList_Timeout (IP6_ND_HOST_TMRMSG_S *pstTmrMsg,
            NDINFO_S *pstNDInfo);
ULONG IP6_ND_GetGlobalPrefixExactMatch(IN6ADDR_S *pstPrefix,UCHAR ucPrefixLen,
                                    ULONG ulVrfIndex, IP6_ND_GLOBALPREFIX_LIST_S **ppstPrefix);

/****************************************************************************/
/* nd_drmgmt.c */

ULONG IP6_ND_RouterDiscovery(NDINFO_S *pstNDInfo, IN6ADDR_S  *pstRouterAddr,
            USHORT usRouterLifeTime);
ULONG IP6_ND_DeleteDefaultRouterEntry(IP6_ND_DEFROUTER_LIST_S *pstDefRtrNode,
            NDINFO_S *pstNDInfo);
ULONG IP6_ND_GetDefRouterEntryCount(ULONG ulIfIndex, ULONG *pulDefRouterCnt);
ULONG IP6_ND_DefRouterList_Timeout(IP6_ND_HOST_TMRMSG_S *pstTmrMsg,
            NDINFO_S *pstNDInfo);
ULONG IP6_ND_DefRouterGetFirst(UINTPTR ulWaitListHandle,
            IP6_ND_DEFROUTER_INFO_S *pstDefRouterEntryOut);

/* BEGIN : NDHOST SDV Defect AC4D05550, Anand */
ULONG IP6_ND_DefRouterGetNext(UINTPTR ulWaitListHandle,
            IP6_ND_DEFROUTER_INFO_S *pstDefRouterEntryOut);
VOID * IP6_ND_DefRouterList_NodeGetNext (VOID * pInHelperParam,
            VOID **ppOutHelperParam);
ULONG IP6_ND_DeleteAllDefRouterEntries(ULONG ulIfIndex);
ULONG IP6_ND_FlushDefRouterList (NDINFO_S *pstNDInfo);
ULONG IP6_ND_StartDefaultRouterEntryTimer(ULONG ulIfIndex,
            IP6_ND_DEFROUTER_LIST_S *pstDefRouterNode);

/****************************************************************************/
/* nd_dcmgmt.c */

ULONG IP6_ND_GetDestCacheEntryCount (ULONG ulVrfIndex, ULONG *pulDestCacheEntryCnt);
ULONG IP6_ND_DeleteDestinationCacheNode(ULONG ulVrfIndex, VOS_RDX6_EXTNODE_S *pstDelExtNode);
ULONG IP6_ND_ForceDeleteDestCache (ULONG ulVrfIndex);
ULONG IP6_ND_AddToDestCache (ULONG ulVrfIndex, IN6ADDR_S *pstDestAddr,
            IP6_ND_DESTCACHE_ENTRY_S **ppstDestCacheEntry);
ULONG IP6_ND_GetDestCacheEntry (ULONG ulVrfIndex, IN6ADDR_S *pstDestAddr,
            IP6_ND_DESTCACHE_ENTRY_S **pstDestCacheEntry);
ULONG IP6_ND_SrchandDelDestAddrInDestCache(ULONG ulVrfIndex, IN6ADDR_S *pstDestAddr);
ULONG IP6_ND_FlushDestinationCache(VOID);
ULONG IP6_ND_DestCacheGetFirst (UINTPTR ulWtLstHandle, ULONG ulVrfIndex,
                                IP6_ND_DESTCACHE_INFO_S  *pstDestEntryOut);

ULONG IP6_ND_DestCacheGetNext(UINTPTR ulWtLstHandle,
            IP6_ND_DESTCACHE_INFO_S *pstDestEntry);
VOID* IP6_ND_DestCache_WaitListGetNext (VOID *pvCurNode, VOID **ppvNxtNode);
ULONG IP6_ND_SrchAndDelFIBInDestCache (IN6ADDR_S *pstDestAddr,
            ULONG ulPrefixLen, BOOL_T bIsFIBAddition, BOOL_T bIsOwnAddress, ULONG ulVrfIndex);
ULONG IP6_ND_SrchAndDelOGIntfInDestCache (ULONG ulOGIfnetIndex, ULONG ulVrfIndex);
ULONG IP6_ND_SrchAndDelDefRouteInDestCache (IN6ADDR_S *pstDefRouteAddr,
                                                         ULONG ulIfnetIndex, ULONG ulVrfIndex);
ULONG IP6_ND_DeleteAllDestCacheEntries(ULONG ulVrfIndex);
ULONG IP6_ND_SrchAndDelPrefixInDestCache(IN6ADDR_S *pstPrefix,
                                    ULONG ulPrefixLen, BOOL_T bIsAddition, ULONG ulVrfIndex);
ULONG IP6_ND_IsDestCacheEntryPresent (IN6ADDR_S *pstDestAddr, ULONG ulVrfIndex,
                       IP6_ND_DESTCACHE_ENTRY_S **ppstDestCacheEntry);
ULONG IP6_ND_DelFIBExtNode(VOS_RDX6_EXTNODE_S *pstRetExtNode,
                            BOOL_T bFIBAddition, ULONG ulVrfIndex);
ULONG IP6_ND_DoesPrefixMatch(IN6ADDR_S * pstAddr, IN6ADDR_S *pstPrefix,
                        ULONG ulPrefixLen);

/****************************************************************************/
/* nd_hst_stateful.c */

ULONG IP6_ND_ConfigureStatefulAddress (const IP6_ND_IADESC_S *pstIADesc,
            const IP6_ND_IN6ADDRWITHTIME_S  *pstAddrWithTime, ULONG ulAddrCnt,
            IP6_ND_STATEFULCFG_OPTTYPE_E enAddUpdateFlag);
ULONG IP6_ND_DHCPv6CAdaptCallback(IP6_ND_DHCP6CADAPT_CALLBACK_S
            *pstDHCPV6AdaptCallback);
ULONG IP6_ND_NotifyDHCP6CAdaptAddrNotUse(IP6_ND_IADESC_S *pstIADesc,
            IP6_ND_IN6ADDRWITHTIME_S *pstAddress,
            IP6_ND_NOTUSABLE_REASON_E enNotifyType);
ULONG IP6_ND_SetOtherConfigParam(IP6_ND_OTHERCFGPARAMS_S *pstOtherCfgParam);
ULONG IP6_ND_CfgStatefulOtherParam(IP6_ND_OTHERCFGPARAMS_S *pstOtherStfCfgParam,
                                    NDINFO_S *pstNDInfo);

/****************************************************************************/
/* nd_init.c */
VOID IP6_ND_ResetNDParams(NDINFO_S *pstNDInfo);
ULONG IP6_ND_TWL_RegCallbackFunc(IP6_ND_SH_TWLCALLBACK_FUNC_S
            *pstTWLCallBackFunc);
ULONG IP6_ND_DHCPC6_Adapt_RegCallbackFunc(IP6_ND_DHCP6CADAPT_CALLBACK_S
            *pstDHCP6AdaptCallBackFunc);
ULONG IP6_ND_RegNPCallback(IPV6_PPI_HOOK_S *pstCallbackFunc);

/****************************************************************************/

/****************************************************************************/
/* nd_hst_redirect.c */
VOID IP6_ND_Redirect_Input(MBUF_S * pstMbuf, LONG lOff, LONG lIcmp6Len);

/****************************************************************************/

#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
ULONG IP6_ND_Notify_PPI(ULONG ulOper, VOID *pvAddrInfo, ULONG ulInfo);
#endif

ULONG IP6_ND_Start_NUD(ULONG ulIfIndex, IN6ADDR_S *pstIP6Addr);

ULONG IP6_ND_Start_AddressResolution(ULONG ulIfIndex, IN6ADDR_S *pstIP6Addr,
                                                    IN6ADDR_S *pstSrcIP6Addr, ULONG ulIsAutoSrc);

ULONG IP6_ND_Find_NH_OG_Interface (IN6ADDR_S *pstDestAddress, 
                                                    ULONG *pulIfIndex,
                                                    IN6ADDR_S *pstNexthopAddr);

ULONG IP6_ND_SendAdvertiseNA(CHAR *szIfName, IN6ADDR_S *pstDstAddr, UCHAR *pucMac);

ULONG IP6_ND_SendAdvertiseNAByIf(ULONG ulIfIndex, IN6ADDR_S *pstDstAddr, UCHAR *pucMac);
/****************************************************************************/

/* Begin: Changes for VLAN & VLANIF framework by karthik 70713 in Nov 2009 */

ULONG IP6_ND_Is_SubIntf(ULONG ulIfIndex);

ULONG IP6_ND_Is_VlanIntf(ULONG ulIfIndex);

ULONG IP6_ND_Get_VlanInfo (ULONG ulIfIndex, MBUF_S *pstMbuf,
                                                        ND_PKT_CTLPARAM_S   *pstNDCtrlParam);


ULONG IP6_ND_Get_Mbuf_vlan_OriginIf(ULONG ulIfIndex,
                                                                            USHORT *pusVlanId,
                                                                            ULONG *pulOriginIfIndex,
                                                                            MBUF_S *pstMbuf);


ULONG IP6_ND_UpdateNB_InRSRAInput(MBUF_S *pstMbuf, ND_OPT_U  *punNDOpt,
                                                                            ND_PKT_CTLPARAM_S *pstNDCtrlParam,
                                                                            BOOL_T  usMsgType);


VOID IP6_ND_SetVlanIDPortIndex(MBUF_S *pstMbuf, ND_NBENTRY_S *pstNBEntry);


VOID IP6_ND_UpdateVlanIDPortInNB (ND_NBENTRY_S *pstNBEntry,
                                                                        ND_PKT_CTLPARAM_S *pstNDCtrlParam,
                                                                        ULONG ulOperation, UCHAR ucNotifyNP);
/* End: Changes for VLAN & VLANIF framework by karthik 70713 in Nov 2009 */

VOS_RDX6_EXTNODE_S * IP6_ND_Add_RadixNode2Root(ND_NBENTRY_S *pstNBEntry, VOID **ppNDRootNode);
ULONG IP6_ND_Add_RadixNode(ND_NBENTRY_S *pstNBEntry, NDINFO_S *pstNDInfo);
ULONG IP6_ND_Add_RadixNode(ND_NBENTRY_S *pstNBEntry, NDINFO_S *pstNDInfo);
ULONG IP6_ND_Del_RadixNode(VOS_RDX6_INTNODE_S **ppstVpnRootNode,
                                 VOS_RDX6_EXTNODE_S **ppstRdxExtNode);
ULONG IP6_ND_SearchExactNoPrefix(NDINFO_S *pstNDInfo,
                                   IN6ADDR_S *pstAddr,
                                   ND_NBENTRY_S **ppstNBEntry);

VOID IP6_ND_NBChangeState(ND_NBENTRY_S *pstNBEntry, UCHAR ucNewState);
ULONG IP6_ND_NBEntry_DelbyPrefix(ULONG ulIfIndex,
                                    IN6ADDR_S stIn6Addr,
                                    IN6ADDR_S stPrefixMask);
ULONG IP6_ND_NBEntryDelFromLink(NDINFO_S *pstNDInfo, ND_NBENTRY_S *pstNBEntry);
NDINFO_S *IP6_ND_GetNDInfoByIndex(ULONG ulIfnetIndex);
ULONG IP6_ND_NBEntryOpenTable(UINTPTR *pulWaitListHandle, ULONG ulSearchType);
ULONG IP6_ND_NBEntryGetNext(UINTPTR ulNBWaitListHandle, VOID **ppCurrentObject, ULONG ulSearchType);
VOID IP6_ND_NBEntryCloseTable(UINTPTR ulNBWaitListHandle);
ULONG IP6_ND_NBEntry_do_Func_By_If(ULONG ulIfNetIndex, ND_FOR_DO_SOMETHING_S* p_Do_Para);
ULONG IP6_ND_NBEntry_DelByL3(ULONG ulIfIndex, ULONG ulDelType);
ULONG IP6_ND_NBEntry_DownByIf(ULONG ulIfIndex);
ULONG IP6_ND_NBEntry_UpByIf(ULONG ulIfIndex);
ULONG IP6_ND_NBEntry_ResetByL3(ULONG ulIfIndex, ULONG ulDelType);

ULONG IP6_ND_DelDynamicNBEntriesByAddr(ULONG ulIfIndex, IN6ADDR_S *pstIn6Addr);
ULONG IP6_ND_NS_Output_Ext(ULONG ulIfIndex,
                                    ULONG  ucOptionFlag,
                                    IN6ADDR_S *pstDstAddr,
                                    IN6ADDR_S *pstSrcAddr,
                                    IN6ADDR_S *pstTgtAddr);
ULONG IP6_ND_SetNDSpecialProxyFlag(ULONG ulIfIndex, UCHAR ucFalg);
ULONG IP6_ND_GetSpecialProxy(IP6_ND_SPECIAL_PROXY_PARA_S *pstSpecProxyPara);
ULONG IP6_ND_GetProxyIfByAddr(ULONG ulVrfIndex, IN6ADDR_S *pstIP6Addr);

/*Added by guojianjun178934, 接口状态变化或physical地址变化主动发送通告NA报文, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */
LONG IP6_ND_NATimerNodeCmp(VOID *pVal, SLL_NODE_S *pNode);
ND_NA_TIMER_NODE *IP6_ND_NATimer_Lookup(const NDINFO_S *pstNDInfo, const IP6IFADDR_S *pstIPv6Addr);
ULONG IP6_ND_NAStart(IP6IFADDR_S *pstIpIfAddr);
VOID IP6_ND_NADelete(ND_NA_TIMER_NODE *pstRATimerNode);
VOID IP6_ND_NAStop(const IP6IFADDR_S *pstIp6IfAddr);
VOID IP6_ND_NAStopAll(VOID *pvIf);
VOID IP6_ND_NA_Timeout(ND_TIMER_S  *pstNATimer);
ULONG IP6_ND_SetNAAttempt(ULONG ulIfnetIndex, ULONG ulValue,
                                       IP6_ND_SETFLAG_E enFlag);
ULONG IP6_ND_GetNAAttempt(ULONG ulIfnetIndex , ULONG *pulRetVal);
ULONG IP6_ND_SetNAInterval(ULONG ulIfnetIndex, ULONG ulValue,
                                      IP6_ND_SETFLAG_E enFlag);
ULONG IP6_ND_GetNAInterval(ULONG ulIfnetIndex , ULONG *pulRetVal);

/* End of Added by guojianjun178934, 2014/1/27   问题单号:S-IP-005-PUBLIC-FUNC-003 */

ULONG IP6_ND_GetResSpecs(SPECS_RES_VALUE_S  *pstResSpecs);

/*Added by guojianjun178934, 【检视问题单---DAD告警优化】产品定期发送地址冲突检测的NS报文，如果收到了NA我们需要启动DAD探测。, 2014/2/22   问题单号:DTS2014021206259  */
LONG IP6_ND_DADExt_TimerNodeCmp(VOID *pVal, SLL_NODE_S *pNode);
ULONG IP6_ND_DADExtStart(IP6IFADDR_S *pstIpIfAddr);
VOID IP6_ND_DADExtStop(const IP6IFADDR_S *pstIp6IfAddr);
VOID IP6_ND_DADExtStopAll(VOID *pvIf);
VOID IP6_ND_DADExt_Update(const IP6IFADDR_S *pstIp6IfAddr);
VOID IP6_ND_DADExt_Timeout(ND_TIMER_S *pstTimerMsg);
VOID IP6_ND_DADExt_Duplicate(IP6IFADDR_S *pstIp6IfAddr, UCHAR *pucDuplicateLLA);
/* End of Added by guojianjun178934, 2014/2/22   问题单号:DTS2014021206259  */

/*******************************************************************************
*    Func Name: IP6_ND_GetNextNBInfoByFilter
* Date Created: 2014-03-10
*       Author: likaikun213099
*  Description: 根据过滤器获取下一个表项
*        Input: VOID* pFilter:
*               VOID* pCurEntry:
*       Output: 下一个表项
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-10   likaikun213099          Create
*
*******************************************************************************/
VOID *IP6_ND_GetNextNBInfoByFilter(VOID* pFilter, VOID* pCurEntry);

/*******************************************************************************
*    Func Name: IP6_ND_OpenNBTableInfo
* Date Created: 2014-03-10
*       Author: likaikun213099
*  Description: 注册ComWaitList Handle
*        Input: TCPIP_ND_FILTER_S* pstNDFilter: 过滤器
*       Output: UINTPTR* pulNBInfoHandle: 返回的handle句柄
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-10   likaikun213099          Create
*
*******************************************************************************/
ULONG IP6_ND_OpenNBTableInfo(UINTPTR* pulNBInfoHandle, TCPIP_ND_FILTER_S* pstNDFilter);

/*******************************************************************************
*    Func Name: IP6_ND_GetNextNBEntryInfo
* Date Created: 2014-03-10
*       Author: likaikun213099
*  Description: Get the next object for the Display command
*        Input: UINTPTR ulNBInfoHandle:
*       Output: TCPIP_ND_NBENTRY_INFO_S *pstNBEntryInfo:
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-10   likaikun213099          Create
*
*******************************************************************************/
ULONG IP6_ND_GetNextNBEntryInfo(UINTPTR ulNBInfoHandle, TCPIP_ND_NBENTRY_INFO_S *pstNBEntryInfo);

/*******************************************************************************
*    Func Name: IP6_ND_CloseNBTableInfo
* Date Created: 2014-03-10
*       Author: likaikun213099
*  Description: Un registers the wait list handle
*        Input: UINTPTR ulNBWaitListHandle:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-10   likaikun213099          Create
*
*******************************************************************************/
ULONG IP6_ND_CloseNBTableInfo(UINTPTR ulNBWaitListHandle);

VOID IP6_IFND_SH_DisplayInfo(TCPIP_IF_NDINFO_S *pstIfNDInfo);
ULONG IP6_GetNDInfoByIfIndex(ULONG ulIfIndex, TCPIP_IF_NDINFO_S *pstIfNDInfo);
ULONG IP6_IfND_Open(UINTPTR *pulIfNDInfoHandle, TCPIP_IF_ND_FILTER_S *pstFilter);
ULONG IP6_IfND_GetNext(UINTPTR ulNDInfoHandle, TCPIP_IF_NDINFO_S *psIfNdInfo);
ULONG IP6_IfND_Close(UINTPTR ulNDInfoHandle);
#if (VRP_NO == IP6_NDHOST)
VOID IP6_ND_SendFinalRA(ULONG ulIfIndex);
#endif
ULONG IP6_ND_NBEntry_UpdateVrfByIf(ULONG ulVrfIndex, ULONG ulIfIndex);
VOID IP6_ND_DADListDeadLoopDebug(DAD_S *pstDAD);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _ND_FUNC_H_ */

