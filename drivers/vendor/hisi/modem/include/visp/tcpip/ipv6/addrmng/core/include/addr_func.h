

#ifndef _ADDR_FUNC_H_
#define _ADDR_FUNC_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "ipv6/addrmng/core/include/addr_type.h"
#include "ipv6/addrmng/core/include/addr_def.h"

ULONG IP6_ProcIp6AddrMsg(VOID *pMsgRcv, VOID **ppMsgSnd);

ULONG IP6_ProcIp6EnableMsg(VOID *pMsgRcv, VOID **ppMsgSnd);

ULONG IP6_Addr_Add_GlobalUniAddr(ULONG ulIfNetIndex,
                                   IN6ADDR_S  stIn6Addr,
                                   ULONG      ulPrefixLen);

ULONG IP6_Addr_Add_LinkLocalAddr(ULONG ulIfNetIndex, IN6ADDR_S  stIn6Addr);

ULONG IP6_Addr_Add_EuiAddr(ULONG ulIfNetIndex, IN6ADDR_S  stIn6Addr,
                                            ULONG  ulPrefixLen);

ULONG IP6_Addr_AutoCfg_LinkLocalAddr(VOID *pstIfNet, IP6IFNET_S *pstIp6If);

ULONG IP6_Addr_Del_GlobalUniAddr(ULONG ulIfNetIndex, IN6ADDR_S  stIn6Addr,
                                                      ULONG ulPrefixLen);

ULONG IP6_Addr_Del_GlobalUniAddrProc(VOID *pstIfNet, IN6ADDR_S *pstIn6Addr,
                                                      ULONG ulPrefixLen);

ULONG IP6_Addr_Del_LinkLocalAddr(ULONG ulIfNetIndex, IN6ADDR_S  stIn6Addr);

ULONG IP6_Addr_Del_EuiAddr(ULONG ulIfNetIndex,
                                           IN6ADDR_S  stIn6Addr,
                                           ULONG      ulPrefixLen);

ULONG IP6_Addr_Del_AllAddr(ULONG ulIfNetIndex);

/* New config API added to delete all EUI-64 addresses */
ULONG IP6_Addr_Del_All_EuiAddr(ULONG ulIfNetIndex);

ULONG IP6_Addr_Modify_OldAddr(VOID *pstIfNet,
                               const IP6IFNET_S *pstIp6If,
                               IP6IFADDR_S *pstIp6IfAddr,
                               IN6ADDR_S *pstIn6Addr,
                               IN6ADDR_S *pstPrefixMask,
                               ULONG ulPrefixLen);

ULONG IP6_Addr_Modify_EuiAddr(VOID *pstIfNet,
                                IP6IFADDR_S  *pstIp6IfAddrToModify,
                                IN6ADDR_S    *pstNewIn6Addr,
                                ULONG ulOldDADState);



ULONG IP6_Addr_Add_NewAddr(VOID *pstIfNet,
                           IN6ADDR_S *pstIn6Addr,
                           IN6ADDR_S *pstPrefixMask,
                           ULONG ulPrefixLen,
                           IN6ADDR_S *pstDstAddr,
                           ULONG ulAddrFlag,
                           ULONG ulOldDADState);



ULONG IP6_Addr_Del_Addr(VOID *pstIfNet,
                       IP6IFADDR_S *pstIp6IfAddr);

ULONG IP6_Addr_Del_AllOfIfIp6Addr(IP6IFNET_S *pstIp6If);

ULONG IP6_Addr_Del_AllOfIfIp6MultiAddr(IP6IFNET_S *pstIp6If);

ULONG IP6_Addr_AutoCfg(ULONG ulIfIndex);

ULONG IP6_Addr_UndoAutoCfg(ULONG ulIfIndex);

ULONG IP6_Addr_Validation(IN6ADDR_S *pstIn6Addr, VOID *pstIf, ULONG ulNoFlag,
                                        ULONG ulEuiFlag, ULONG ulDelAllFlag,
                                        ULONG ulPrefixLength);

/* Trunk interface AT defect VISP */
ULONG IP6_Addr_Interface_Validation(VOID* pstIfNet);

VOID IP6_Addr_DADCompleteNotify(IP6IFADDR_S *pstIp6IfAddr);
IP6MULTI_S *IP6_Addr_FindMultiOnIpIf(IN6ADDR_S *pstAddr,
                                      IP6IFNET_S *pstIp6IfNet);

ULONG IP6_Addr_SyncRefCountMulti (IN6ADDR_S *pstMultiAddr,
                                   IP6IFNET_S *pstIp6If, ULONG ulRefCount);
ULONG IP6_Addr_SendMultiRefCountMsg (IN6ADDR_S *pstMultiAddr, VOID *pstIf,
                                                  ULONG ulReferenceCount);

/********************************************************************
 *          functions in file addr_proc.c                           *
 ********************************************************************/
ULONG IP6_Addr_Init(VOID);

ULONG IP6_Addr_DeleteIp6IfAddr(IP6IFADDR_S *pstIp6IfAddr);

IP6IFNET_S * IP6_Addr_IF_NewIp6IfNet(VOID *pstIf);

ULONG IP6_Addr_IF_DelIp6IfNet(IP6IFNET_S *pstIp6If);

ULONG IP6_Addr_IF_Attach(VOID *pstIf);

ULONG IP6_Addr_MTU_Notify(VOID *pstIf);

ULONG IP6_Addr_IF_Detach(VOID *pstIf);

ULONG IP6_Addr_PlugOut(VOID *pstIf);


ULONG IP6_Add_LoopBackAddr(VOID *pstIfNet,
                                    IP6IFNET_S *pstIp6If);

ULONG IP6_Addr_LLC_Notify(VOID *pstIf,
                                ULONG ulCmd,
                                CHAR *pcData);

ULONG IP6_Addr_PhyUpDownNotify(VOID *pstIf,
                                     ULONG ulCmd,
                                     CHAR *pcData);

ULONG IP6_Addr_GetAddrScopeType(const IN6ADDR_S *pstIn6Addr);

IP6IFADDR_S * IP6_Addr_GetLinkLocalAddrOnIf(VOID *pstIfNet);

ULONG IP6_Addr_GetUnicastAddrNumOnIf(IP6IFNET_S *pstIp6If);

VOID IP6_Addr_PrefixLen2Mask(IN6ADDR_S *pstMask, ULONG ulPrefixLen);

ULONG IP6_Addr_IsInvalidIP4Address(ULONG ulAddr);

ULONG IP6_Addr_IsInvalidIP6Address(VOID *pstIfNet, IN6ADDR_S  stIn6Addr);

ULONG IP6_Addr_IsSameNeighborExists(ULONG ulIfNetIndex, IN6ADDR_S *pstIn6Addr);

IP6IFADDR_S *IP6_Addr_IF_FindSameIpAddr(IN6ADDR_S stIn6Addr,
                                         IP6IFNET_S *pstIp6IfNet);

IP6IFADDR_S * IP6_Addr_IF_FindAddrWithPrefix(IN6ADDR_S *pstIn6Addr,
                                             IN6ADDR_S *pstPrefixMask,
                                             IP6IFNET_S *pstIp6If);

ULONG IP6_Addr_IF_HaveIp6Addr(VOID *pstIf);

ULONG IP6_Addr_IF_HaveLinkLocalAddr(VOID *pstIf);

ULONG IP6_Addr_IF_IsAddrOnIpIf(VOID *pstIfNet, IN6ADDR_S stIn6Addr, BOOL_T bCheckIFStatus);

ULONG IP6_Addr_IsLocalAddr(IN6ADDR_S  *pstAddr, USHORT usVrfIndex);
ULONG IP6_Addr_IsLocalIfAddr(IN6ADDR_S  *pstAddr, ULONG ulIfIndex);

ULONG IP6_Addr_ConflictIp6Address(IN6ADDR_S *pstIn6Addr,
                                 IN6ADDR_S *pstPrefixMask,
                                 ULONG     ulIfIndex,
                                 ULONG     ulCheckFlag);

ULONG IP6_Addr_DoConflictCheckOnAddrList(IN6ADDR_S *pstIn6Addr,
                                            IN6ADDR_S *pstPrefixMask,
                                            ULONG ulIfIndex,
                                            ULONG ulCheckFlag,
                                            const IP6IFADDR_S *pstAddrList,
                                            ULONG ulAddrListType);

ULONG IP6_Addr_GetInterfaceId(VOID *pstIf, IP6_INTERFACEID_S *pstInterfaceId);

VOID IP6_Addr_NotifyLinkLayer(VOID *pstIf, ULONG ulCmd);


IP6MULTI_S *IP6_Addr_IF_AddMulti (IN6ADDR_S *pstMultiAddr, VOID *pstIf);

ULONG IP6_Addr_IF_DelMulti(IN6ADDR_S *pstIn6Addr,  VOID *pstIf);


ULONG IP6_Addr_IFA_IfWithBestPrefix(SOCKADDR_IN6_S *pstSockIn6Addr,
                                      VOID *pstIfnet, IN6ADDR_S **ppstAddrOut);

IP6IFADDR_S *IP6_Addr_IFA_IfWithBestPrefixTL(
                                          const SOCKADDR_IN6_S *pstSockIn6Addr,
                                          const IP6IFNET_S *pstIp6If);

IN6ADDR_S IP6_Addr_Get_MainIp6Addr (IP6IFNET_S *pstIp6If);

VOID * IP6_Addr_UnicastAddr_GetNext (VOID *pCur, VOID **ppNext);

VOID * IP6_Addr_MulticastAddr_GetNext (VOID *pCur, VOID **ppNext);

ULONG IP6_Addr_GetLinkMtu (VOID *pstIfnet, ULONG *pulMtu);

ULONG IP6_Addr_GetMultiAddrNumOnIf (IP6IFNET_S *pstIp6If);

ULONG IP6_Addr_InterfaceIdChange (VOID *pstIf, CHAR *pcData);

ULONG IP6_Addr_QueryInterface(IUnknown *  This, COMP_IID iid,
                                                          VOID **ADDRvObj);

ULONG IP6_Addr_Init_Com_New(const IPB_IR_ADDR_COM_ID_INFO_S *pstComInfo,
                            ULONG ulComLen);

ULONG IP6_Addr_Activate_Com(VOID);

/* Begin : Defect ID: D01006,     Modifier:Rajesh,   Date:2004/9/13
        Reason   : Initial, Max Mtu change for Pos,GE interfaces*/

ULONG IP6_Addr_SetResSpecs (SPECS_RES_VALUE_S  *);

ULONG IP6_Addr_SetFunSpecs (SPECS_FUN_VALUE_S  *pstFunSpecs);

ULONG IP6_Addr_SetModuleInfo(IP6_ADDR_MOD_INFO_S *pstMInfo);

IP6IFADDR_S *IP6_Addr_Get_First_Addr (ULONG ulScopeType, IP6IFNET_S *pstIp6If);
IP6IFADDR_S *IP6_Addr_Get_Head (ULONG ulScopeType, IP6IFNET_S *pstIp6If);

IP6IFADDR_S *IP6_Addr_Get_Next_Addr (IP6IFADDR_S *pstIp6IfAddr);

ULONG IP6_Addr_OpenTable(ULONG ulMainType, UINTPTR *pulWaitListHandle,
                                                        UCHAR ucWaitlistType);
ULONG IP6_Addr_CloseTable(UINTPTR ulWaitListHandle);
ULONG IP6_Addr_GetFirstExt(UINTPTR ulWaitListHandle, VOID *pstAddrNode,
                                VOID **ppstCurrentNode);
ULONG IP6_Addr_GetFirstAddrByIfIndex(ULONG ulIfIndex,
                                                ULONG ulMainType,
                                                ULONG ulIP6ScopeOrder,
                                                UINTPTR ulWaitListHandle, 
                                                IN6ADDR_S *pstIn6Addr);
ULONG IP6_Addr_GetNextExt(UINTPTR ulWaitListHandle, ULONG ulMainType,
                                                  VOID **ppCurrentObject);

IP6IFADDR_S  *IP6_Addr_IfWithDstAddr (SOCKADDR_IN6_S *pstSockAddr,
                                                           USHORT usVrfIndex);

ULONG IP6_Addr_GetNumofScopeMulti (IP6IFNET_S *pstIp6If, ULONG ulScopeType);

/* Added third parameter so that I/O board can signify whether DADCompleteNotify
   need to invoked when DAD message is handled in Main Board */
VOID IP6_Addr_SendDADStateMsg (VOID *pstIf, IP6IFADDR_S *pstIp6IfAddr,
                                                    BOOL_T bDADCompleteNotify);



/* Begin : Defect ID: BYAD12114,     Modifier:Rajesh,   Date:2004/10/21
Reason   : IPC RPC synch call must not be called from sock run context*/
VOID IP6_Addr_HandleDADMsg(IP6_ADDR_DADSTATE_S *pstRecData);


VOID IP6_Addr_HandleRPCMsg (IP6RPC_REQUEST_S*pstRecvInfo,
         IP6_GETINTERFACEID_REPLY_S **pstOutReplyMsg, ULONG *pulSendDataLen);

VOID IP6_Addr_SetDebug(ULONG ulSwitch, ULONG ulLevel);

VOID IP6_Addr_DisplayIntAddDebug(IP6IFADDR_S *pIp6IfAddr);

ULONG IP6_Addr_GetIfnetIndex(IN6ADDR_S stAddr, USHORT usVrfIndex);

IP6IFADDR_S  *IP6_Addr_Get_ValidIPAddr (VOID);

ULONG IP6_Addr_IfWithAddr (SOCKADDR_IN6_S *pstSockIn6Addr,
                             USHORT usVrfIndex);

/*FOR MIB*/
ULONG IP6_Addr_GetFirstAddrTbl(IP6_ADDR_ADDRTBL_S *pstInOutMIBAddrTbl);
ULONG IP6_Addr_GetNextAddrTbl(ULONG ulIfIndex,
                               IP6_ADDR_ADDRTBL_S *pstInOutMIBAddrTbl);
ULONG IP6_Addr_GetAddrTbl(ULONG ulIfIndex,
                               IP6_ADDR_ADDRTBL_S *pstInOutMIBAddrTbl);


VOID IP6_Addr_NotifyRMIntStatus(VOID *pstIfNet, UCHAR  ucType);

ULONG IP6_Addr_CheckDADType(VOID *pstIf);
ULONG IP6_Addr_IsAnycastAddress (IN6ADDR_S  stIn6Addr, ULONG ulPrefixLen);

VOID IP6_Addr_Enable(VOID);
VOID IP6_Addr_Disable(VOID);

/* Modified by Rajesh for defect id BYAD11067*/
VOID IP6_Addr_UnLoopBack(VOID *pstLoopIf);


VOID IP6_Addr_Set_RPCSendToIO(VOID); /*Added by SandeepMN for SWFD13741*/

/* Change for defect SWFD16749 BY:karthik ON:29/9/2005
 * To implement get next for SMP
 */
IP6IFADDR_S* IP6_Addr_GetNextAddrOnIf(VOID *pstIfNet, IN6ADDR_S *pstAddr);
IN6ADDR_S* IP6_Addr_GetNextAddrOnBoard(IN6ADDR_S *pstAddr);

ULONG IP6_Addr_GetFirstIfTbl (ULONG *pulIpv6IfIndex);
ULONG IP6_Addr_GetNextIfTbl (ULONG *pulIpv6IfIndex);
ULONG IP6_Addr_IfTblGetValueByIndex(ULONG ulIpv6IfIndex,
                                        IP6_ADDR_IFENTRY_S *pstIfnetEntry);
ULONG IP6_Addr_IfTblIndexExist(ULONG ulIfIndex);

ULONG IP6_SendGetMacAddrMsg(VOID *pstIf, CHAR *pcMacAddr);

VOID IP6_Addr_SetLastChangeTime(IP6IFNET_S    *pstNewIp6If);

ULONG IP6_Addr_SendGetIfStatusMsg(IP6_ADDR_IFSTATUS_S *pstUpDownInfo);

ULONG IP6_Addr_GetIfState(IP6_ADDR_IFSTATUS_S *pstUpDownInfo);
ULONG IP6_Addr_SendIfState(IP6RPC_REQUEST_S *psRcvMsg, VOID **ppSendData,
                                                    ULONG *pulSendDataLen);
ULONG IP6_Addr_SH_RegCallbackFunc(IP6_ADDR_SH_CALLBACK_FUNC_S *pstCallbackFunc);

ULONG IP6_Addr_SGSN_RegCallbackFunc (IP6_ADDR_SGSN_CALLBACK_FUNC_S
                                                              *pstCallbackFunc);
ULONG IP6_Addr_IFA_IfWithNextBestPrefix(VOID *pstIf, IN6ADDR_S stAddrIn,
                                      IN6ADDR_S **ppstAddrOut,
                                      USHORT usVrfIndex);
ULONG IP6_Addr_GetAddrStatus(VOID *pIf);
ULONG IP6_Addr_GetUpDownInfo(IP6_ADDR_IFSTATUS_S *pstUpDownInfo);

/* HA_AM */
VOID IP6_Addr_HA_DataSmoothEvent(VOID);
VOID IP6_Addr_HA_StateChange(ULONG ulHAState);

ULONG IP6_Addr_HA_RegCallbackFunc(IP6_ADDR_HA_CALLBACK_FUNC_S
                                                    *pstHACallBackSet);

ULONG IP6_Addr_HA_RealtimeBackup(VOID *pstIfNet, IP6IFADDR_S *pstIp6IfAddr,
                                                             ULONG ulType);
ULONG IP6_Addr_HA_SetBackupData (UCHAR *pucData, ULONG ulEventType);
ULONG IP6_Addr_HA_SendBackupData (VOID);
VOID IP6_Addr_SyncRefCount(VOID);

ULONG IP6_Addr_SyncDADState();

/* Begin : Defect ID: D01006,     Modifier:Rajesh,   Date:2004/9/13
     Reason   : Get negotiated Mtu from I/O Board*/
ULONG  IP6_Addr_SyncNegMtu();
ULONG IP6_Addr_Sync_DADState_FromIO(IP6IFNET_S   *pstIp6If, ULONG ulDadType);
ULONG IP6_Addr_Get_DADState(ULONG ulIfIndex, IP6IFADDR_S  *pstIp6IfAddr);

ULONG IP6_Addr_Get_MainIp6AddrByType(IP6IFNET_S *pstIp6If, ULONG ulType,
                                                      IN6ADDR_S *pstAddr);
ULONG IP6_Addr_GetNumValidUcastAddrOnIF(VOID *pstIfnet);

VOID IP6_Addr_GetDebug(ULONG *pulSwitch, ULONG *pulLevel);
ULONG IP6_Addr_GetNumValidUcastAddrOnIF(VOID *pstIfnet);
IN6ADDR_S * IP6_Addr_GetValidUnicastAddrOnIf(VOID *pstIfNet);
IP6IFADDR_S * IP6_Addr_GetInterfaceFirstAddr(VOID *pstIfNet);
ULONG IP6_Addr_GetInterfaceNextAddr(IP6IFADDR_S  *pstIfAddr,
                                    IP6IFADDR_S  **pstOutAddrNext);
ULONG IP6_Addr_SerialLinkChange(VOID *pstIfNet, ULONG ulCmd); /* BYAD13106 */

/********************************************************************
 *          End-new functions in file addr_proc.c                   *
 ********************************************************************/

ULONG IP6_Addr_Srm_RegCallbackFunc(
                                IP6_ADDR_SRM_CALLBACK_FUNC_S *pstCallbackFunc);
ULONG IP6_Addr_SetMaxMtu(ULONG ulMaxMtu);
ULONG IP6_Addr_GetMaxMtu (ULONG *pulMaxMtu);


/* New API's added for SGSN CR by karthik */

ULONG  IP6_Addr_Disp_Open (UINTPTR *pulSessionId,
                            IP6_ADDR_DISP_FILTER_S *pstDispAddrFilter);


ULONG IP6_Addr_Display_GetFirst(UINTPTR ulSessionId,
                                IP6_ADDR_GET_INFO_S *pstRetAddr);

ULONG IP6_Addr_Display_GetNext(UINTPTR ulSessionId,
                               IP6_ADDR_GET_INFO_S *pstRetAddr);


ULONG IP6_Addr_Disp_Close (UINTPTR ulSessionId);

VOID IP6_Addr_Display_CopyAddrInfo (VOID *pstIfNet,
                                     IP6IFADDR_S *pIp6IfLinkLocAddr,
                                     IP6IFNET_S *pstIp6IfCB,
                                     IP6_ADDR_GET_INFO_S *pstAddrinfo);

ULONG IP6_Addr6_Open(UINTPTR *pulSessionId, IPADDR6_FILTER_S *pstFilter);
ULONG IP6_Addr6_GetNext (UINTPTR ulSessionId, IP6_ADDR_GET_INFO_S *pstRetAddr);
ULONG IP6_Addr6_Close (UINTPTR ulSessionId);
ULONG IP6_GetAddr6ByIfIndex(ULONG ulIfIndex, IP6_ADDR_GET_INFO_S *pstRetAddr);

ULONG IP6_Addr_RestartDAD(ULONG ulIfIndex);

#if (VRP_YES == IP6_NDHOST)

ULONG IP6_Addr_GetSrcAddrForGlobalDestOnIntf(VOID *pvIfnet,
                                            const IN6ADDR_S *pstIp6DestAddr,
                                            IN6ADDR_S *pstIp6SrcAddr);
#endif



ULONG IP6_Addr_SetIpv6FuncOnIntf(ULONG ulIntfIndex, BOOL_T bIpv6FuncStatus);

ULONG IP6_Addr_GetIpv6FuncStatusOnIntf(ULONG ulIfIndex,
                                                    BOOL_T *pbIpv6FuncStatus);
ULONG IP6_Addr_Del_AllManualAddr(ULONG ulIfIndex);

ULONG IP6_Addr_Del_AllStatelessAddr(ULONG ulIfIndex);

ULONG IP6_Addr_Register_IntfIPV6StatusNotify(const
                IP6_ADDR_APPLICATION_CALLBACK_FUNC_S *pstApplicationCallBack);

ULONG IP6_Addr_UnRegister_IntfIPV6Notify(ULONG ulModuleId);

ULONG  IP6_Addr_UniAddr_GetFirst(UINTPTR ulSessionId, ULONG ulAddrScope,
                        ULONG ulIfIndex, IP6_ADDR_INFO_S *pstDispUniAddr);

ULONG  IP6_Addr_UniAddr_GetNext(UINTPTR ulSessionId, ULONG ulAddrScope,
                        ULONG ulIfIndex, IP6_ADDR_INFO_S *pstDispUniAddr);

ULONG  IP6_Addr_MultiAddr_GetFirst(UINTPTR ulSessionId, ULONG ulAddrScope,
            ULONG ulIfIndex, IP6_NDHOST_MULTIADDR_INFO_S *pstDispMultiAddr);

ULONG  IP6_Addr_MultiAddr_GetNext(UINTPTR ulSessionId,
                            IP6_NDHOST_MULTIADDR_INFO_S *pstDispMultiAddr);

ULONG IP6_Addr_Util_TriggerStartTimer_Stateless(VOID *pvAddrTimerMsg,
                                        ULONG ulAddrState, ULONG ulTimeOutSec,
                                        ULONG *pulTimerId);

ULONG IP6_Addr_Add_GlobalUniAddrProc (VOID *pstIfNet,
                                      IN6ADDR_S  *pstIn6Addr,
                                      ULONG ulPrefixLen,
                                      ULONG ulAddrFlag);

ULONG IP6_Addr_Modify_ToManualAddr(IN6ADDR_S *pstIn6Addr,
                                                IP6IFNET_S *pstIp6If);

ULONG IP6_Addr_MakeSpaceForManualCfg(VOID *pvIfNet, IP6IFNET_S *pstIp6If);

ULONG IP6_Addr_Stop_Timer(ULONG ulTimerID);

IP6IFADDR_S* IP6_Addr_NewIp6IfAddr(IP6IFNET_S *pstIp6If,
                                   ULONG ulAddrType,
                                   ULONG ulAddrFlag);

ULONG IP6_Addr_Util_StartInitDelayTimer(IP6IFNET_S *pstIp6If, ULONG ulIfIndex);

ULONG IP6_Addr_Util_GetPhysicalStateForSubIf(VOID *pstIfNet,
                                                        ULONG *pulPhyStatus);
ULONG IP6_Addr_Util_GetAddrRemainLifeTimeandState(IP6IFADDR_S *pstIfAddr,
                            IP6_ADDR_LIFETIMEANDSTATE_S *pstAddrLifeandState);


ULONG IP6_Addr_DelStateful_Addr(VOID *pstIfNet, IP6IFADDR_S *pstIp6IfAddr,
                    IP6_ND_NOTUSABLE_REASON_E eNotUseType);


ULONG IP6_Addr_SetMTU(ULONG ulIfnetIndex, ULONG ulIsNoCmd, ULONG ulMtu);

ULONG IP6_Addr_GetMTU(ULONG ulIfnetIndex, ULONG ulIsCmd, ULONG *pulMtu);


ULONG IP6_Addr_SelectIntfwithValidAddr(ULONG ulIfIndex, ULONG * pulAddrState);

ULONG IP6_Addr_EnableIpv6OnIntf(VOID *pvIfnet);

ULONG IP6_Addr_DisableIpv6OnIntf(VOID *pvIfnet);

ULONG IP6_Addr_Util_GetNumOfMatchingBits(const IN6ADDR_S *pstIP6Addr1,
                                         const IN6ADDR_S *pstIP6Addr2,
                                         ULONG *pulMatchBitsNum);

VOID IP6_Addr_HandleEvent_SIOCNDDAD(ULONG ulDadType, IP6IFNET_S *pstIp6If);

VOID IP6_ADDR_Handle_ISLDOWN(VOID *pstIf, IP6IFNET_S *pstIp6If,
                                                            ULONG ulDadType);

ULONG IP6_Addr_Config_StatelessAddress(ULONG ulIfIndex,
                                IP6_ND_STATELESSADDRCFGMSG_S *pstStatelessAddr);

ULONG IP6_Addr_Handle_StatefulAddressMsg(ULONG ulIfIndex,
                            IP6_ND_STATEFULADDRCFGMSG_S *pstStatefulAddrMsg);

ULONG IP6_Addr_InitialDelay_TimeOut(ULONG ulIntfIndex);

ULONG IP6_Addr_Handle_StatelessLifetimeExpiry(
                        IP6_ADDR_STATELESS_TIMER_S *pstAddrStatelessTimerMsg);

ULONG IP6_Addr_Handle_StatefulLifetimeExpiry(
                            IP6_ADDR_STATEFUL_TIMER_S *pstAddrStatefulTimerMsg);

ULONG IP6_Addr_Start_Timer(VOID *pvTimerMsg, ULONG ulTimeMilliSec,
                    IP6_ADDR_TIMERTYPE_E enTimerType, ULONG *pulTimerId);

ULONG IP6_Addr_Util_ValidatePrefix(IN6ADDR_S *pstIp6AddrPrefix);

ULONG IP6_Addr_Util_FindStateLessAddress(IP6IFNET_S *pstIp6If,
                                         IN6ADDR_S  *pstPrefixMask,
                                         IN6ADDR_S  *pstIn6AddrPrefix,
                                         IP6IFADDR_S **pstIp6IfAddrOut);


ULONG IP6_Addr_Util_GetUnsetBitsInByte(UCHAR ucAddressByte,
                                                    ULONG *pulLeftUnsetBits);

ULONG IP6_Addr_Util_TriggerStartLifetimeTimer(VOID *pvAddrTimerMsg,
        ULONG ulTimeOutSec, IP6_ADDR_TIMERTYPE_E enTimerType, ULONG *pulTimerId);

ULONG IP6_Addr_StartStatelessAddressTimer(ULONG ulTimerType,
                                          ULONG ulTimeOutSec,
                                          VOID *pvAddressTimerInfo,
                                          VOID *pvAutoCfgInfo);

ULONG IP6_Addr_Add_StatefulAddresses(VOID *pvIfnet, IP6IFNET_S  *pstIp6If,
                            IP6_ND_STATEFULADDRCFGMSG_S *pstStatefulAddrMsg);

ULONG IP6_Addr_StartStatefulAddressTimer(ULONG ulTimerType,
                                         ULONG ulTimeOutSec,
                                         VOID *pvAddressTimerInfo,
                                         VOID *pvAutoCfgInfo);


ULONG IP6_Addr_Util_Formulate_StateAndTimer(IP6IFADDR_S *pstIp6IfAddr,
                            ULONG ulPreferredTime, ULONG ulValidTime,
                            VOID *pvAddressTimerInfo,
                            ULONG (*pfIP6_Addr_StartAddressTimer)
                                             (ULONG, ULONG, VOID *, VOID *));

ULONG IP6_Addr_Util_Update_StateAndTimer(ULONG ulTimerType,
                            VOID *pvIfNet, IP6IFADDR_S *pstIp6IfAddr,
                            VOID *pvAddressTimerInfo,
                            ULONG (*pfIP6_Addr_StartAddressTimer)
                                             (ULONG, ULONG, VOID *, VOID *));

ULONG IP6_Addr_Del_StatefulAddresses(VOID *pvIfnet, IP6IFNET_S  *pstIp6If,
                            IP6_ND_STATEFULADDRCFGMSG_S *pstStatefulAddrMsg);

ULONG IP6_Addr_Update_StatefulAddresses(VOID *pvIfnet, IP6IFNET_S  *pstIp6If,
                            IP6_ND_STATEFULADDRCFGMSG_S *pstStatefulAddrMsg);

ULONG IP6_Addr_Update_StateLessAddrLifetime(VOID *pvIfNet,
                        IP6IFADDR_S *pstIp6IfAddr,
                        ULONG ulNewPreferredTime,
                        ULONG ulNewValidTime,
                        IP6_ADDR_STATELESSADDRESSINFO_S *pstAddressInfo);

ULONG IP6_Addr_AddStateLessAddress(VOID *pvIfNet, IP6IFNET_S  *pstIp6IfNet,
                            ULONG ulPreferredTime,
                            ULONG ulValidTime,
                            IP6_ADDR_STATELESSADDRESSINFO_S *pstAddressInfo);

VOID IP6_Addr_Util_Notify_RegApplication(ULONG ulIfindex,
                                                        BOOL_T bIpv6FuncStatus);

ULONG IP6_Addr_Util_Address_Validation(const IN6ADDR_S *pstIp6Addr);

ULONG IP6_Addr_FindSrcAddrOnSameIntf(IP6IFNET_S  *pstIp6If,
                                     const IN6ADDR_S *pstIp6DestAddr,
                                     IN6ADDR_S *pstIp6SrcAddr);

ULONG IP6_Addr_FindSrcAddrOnSystem(IN6ADDR_S *pstIp6SrcAddr);

ULONG IP6_Addr_HandleTimeOutEvents(IP6_ADDR_TIMER_CTRL_MSG *pstTimerCtrlMsg);

ULONG IP6_Addr_Timer_RegCallbackFunc(IP6_ADDR_TIMER_CALLBACK_FUNC_S
                                                            *pstCallbackFunc);
ULONG IP6_Addr_HandleHostEvents(IP6_ADDR_HOSTEVENT_S *pstNDHostEvent);

ULONG IP6_Addr_CreateIpv6CtrlBlk(VOID *pstIf);

ULONG IP6_Addr_SelectSourceAddr(const IN6ADDR_S *pstIp6DestAddr,
                                IN6ADDR_S *pstSrcAddr, ULONG ulIfIndex, ULONG ulVrfIndex);

/* Prototypes of addr_test.c */

CHAR * IP6_Addr_ConvertIp6AddressToString(const IN6ADDR_S *pstIP6Addr,
                                                                CHAR *szAddr);
ULONG IP6_Addr_GetSrcAddr_ForMultiAndLLADest(VOID *pvIfnet,
                                            const IN6ADDR_S *pstIp6DestAddr,
                                            IN6ADDR_S *pstIp6SrcAddr);

ULONG IP6_Addr_FindGlobalAddr_ForMultiDest(IP6IFNET_S *pstIp6If,
                                                IN6ADDR_S *pstIp6SrcAddr);


VOID IP6_ADDR_VOID_DUMMY();
VOID* IP6_ADDR_POINTER_DUMMY();
ULONG IP6_ADDR_ULONG_DUMMY();

VOID IP6_Addr_Util_StoreAddressLifetime(IP6IFADDR_S *pstIp6IfAddr,
                                    ULONG ulPrefLifeTime,
                                    ULONG ulValidLifeTime,
                                    ULONG ulLastChangePrefTime,
                                    ULONG ulLastChangeValidTime);


ULONG IP6_Addr_IsIntfPhyStateUp(VOID *pstIfNet);

#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
ULONG IP6_Addr_Notify_PPI(ULONG ulOper, VOID *pvAddrInfo);
#endif

ULONG IP6_Addr_RegNPCallback(IPV6_PPI_HOOK_S *pstCallbackFunc);
ULONG IP6_Addr_Reg_Platform_Hook(IP6_ADDR_DADRESULT_NOTIFY_FUNC_S *pstCallbackFunc);
ULONG IP6_Addr_Notify_StateInfo(ULONG ulOper, IP6IFADDR_S  *pstIFAddr);


ULONG IP6_Addr_EnableDisableIntfAutoconfig(ULONG ulIfIndex,
                                                        ULONG ulOperation);
ULONG IP6_Addr_L3VPN6_Notify (ULONG ulEvent, VOID *pData);
ULONG IP6_Addr_IfAddVRF(USHORT usVpnid ,ULONG ulIfIndex);
ULONG IP6_Addr_IfDeleteVRF(USHORT usVpnid ,ULONG ulIfIndex);
IP6_Addr_IfVpn * IP6_Addr_IfFindVRF (USHORT usVpnid ,ULONG ulIfIndex);
ULONG IP6_Addr_Del_RadixNode(VOS_RDX6_INTNODE_S **ppstVpnRootNode,
                                         VOS_RDX6_EXTNODE_S **ppstRdxExtNode);
 ULONG IP6_Addr_Add_RadixNode(IP6IFADDR_S *pstIp6IfAddr,
                                         ULONG        ulAddrType,
                                         IN6ADDR_S    stIn6Addr,
                                         ULONG        ulPrefixLen);
 ULONG IP6_Addr_Add_NewAddrToRadixTree(IP6IFADDR_S *pstIp6IfAddr,
                                                      ULONG       ulAddrType,
                                                      IN6ADDR_S   stIn6Addr,
                                                      ULONG       ulPrefixLen);
 ULONG IP6_Addr_SearchExactNoPrefix(USHORT usVrfIndex,
                                   IN6ADDR_S *pstAddr,
                                   VOS_RDX6_EXTNODE_S **ppstRetExtNode);

ULONG IP6_Addr_GetIfIndexByAddr(ULONG ulVrfIndex, IN6ADDR_S *pstIn6Addr, ULONG *pulIfIndex);
ULONG IP6_Addr_GetDADState(ULONG ulIfIndex, IN6ADDR_S *pstIn6Addr, ULONG *pulDadState);

ULONG IP6_Addr_IsValidSpecialProxyAddr( ULONG ulIfIndex, 
                                                   IN6ADDR_S *pstIP6Addr);
IP6IFADDR_S *IP6_Addr_GetExactAddrNoPrefix(ULONG ulVrfIndex, 
                                                        IN6ADDR_S *pstIn6Addr);
ULONG IP6_Addr_RestartDADForAddr(ULONG ulVrfIndex, IN6ADDR_S *pstIP6Addr);

IP6IFNET_S *IP6_Addr_GetLinkLocalIf(ULONG ulVrfIndex, IN6ADDR_S *pstIP6Addr);
ULONG IP6_Addr_GetLoopBackIfIndexByAddr(ULONG ulVrfIndex, ULONG *pulIfIndex);
ULONG IP6_Addr_GetLinkLocalIfIndexByAddr(ULONG ulVrfIndex, IN6ADDR_S *pstIn6Addr, 
                                                        ULONG *pulIfIndex);

/* Modified by guojianjun178934, 【检视问题单---DAD告警优化】产品定期发送地址冲突检测的NS报文，如果收到了NA我们需要启动DAD探测, 2014/2/21   问题单号:DTS2014021206259  */
VOID IP6_Addr_DADExtCompleteNotify(IP6IFADDR_S *pstIp6IfAddr);
/*End of Modified by guojianjun178934, 2014/2/21   问题单号:DTS2014021206259  */

IP6IFADDR_S *IP6_Addr_IF_FindNetAddrWithPrefix(IN6ADDR_S *pstIn6Addr,
                                             IN6ADDR_S *pstPrefixMask,
                                             IP6IFNET_S *pstIp6If);
IP6IFADDR_S *IP6_Addr_FindSamePrefixAddrByIndex(IN6ADDR_S *pstIn6Addr, IP6IFNET_S *pstIp6IfNet);
ULONG IP6_Addr_NotifyRmForIpcIf(ULONG ulVrfIndex, VOID *pvIf);
VOID IP6_Addr_AddrListDeadLoopDebug(IP6IFADDR_S *pstAddrListHead);

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif/* end of _ADDR_FUNC_H_ */

