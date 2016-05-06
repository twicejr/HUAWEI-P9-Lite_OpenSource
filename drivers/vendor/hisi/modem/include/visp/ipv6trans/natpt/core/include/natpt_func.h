/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             natpt_func.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-17
 *  Author:             archana   (VRPv5 IPv6 Team) 
 *  Document:
 *  Function Description:
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  2003-11-27  Archana P V      For Defect BYAD04227
 *  
 *  2003-12-2  Usha             For Defect BYAD04881 
 *  2003-12-12 Archana P V      For Defect BYAD05489
 *  2003-12-15 Arvindsaproo     For Defect BYAD06254
 *  2003-01-12 Archana P V      For Defect BYAD06698
 *  2004-01-26 Archana P V      For Defect BYAD07342
 *  2004-01-27 Archana P V      For Defect BYAD07343
 *  2004-02-03 Archana P V      For Defect BYAD06372
 *  2004-02-09 Archana P V      For Defect BYAD08095
 *  2004-02-04 Usha             for Defect BYAD07830
 *  2004-03-15 Archana P V      for Defect BYAD09118
 ************************************************************************/



#ifndef _NATPT_FUNC_H_
#define _NATPT_FUNC_H_

#ifdef  __cplusplus
extern  "C"{
#endif



ULONG NATPT_MM_Init ();
ULONG NATPT_MM_DeInit();
NATPT_HASH_ADDRMAP_S*  NATPT_MM_CreateAddrMap  (ULONG ulV4Address, IN6ADDR_S   stV6Address , UCHAR ucFlag);
ULONG NATPT_MM_FindAddressMap(IN6ADDR_S*  pstV6address,
                                            ULONG*  pulV4address ,
                                            USHORT* pusV6Port , 
                                            USHORT* pusV4Port, 
                                            UCHAR ucPro, 
                                            UCHAR* pucFlag);
NATPT_HASH_DPAT_S*  NATPT_MM_FindDPAT (ULONG ulV4Addr , 
                                                  IN6ADDR_S stV6Address,
                                                  USHORT usV4Port,
                                                  USHORT usV6Port,
                                                  UCHAR ucProtocol,
                                                  UCHAR ucISPortValid);
ULONG NATPT_MM_SearchAndCreateAMap(NATPT_SEARCH_ADDR_S* pstSearchAddr);
BOOL_T NATPT_AM_AAM_CheckByAddrGroup(ULONG ulStartAddr,ULONG ulEndAddr);
ULONG NATPT_MGMT_AM_Download(ULONG ulSlot,USHORT usFlag);
ULONG NATPT_SM_AM_DeleteAllDynamic();
BOOL_T NATPT_MM_DeleteAll();
ULONG NATPT_MM_CreateSession(NATPT_HASH_SESSION_S stHashSession);
ULONG  NATPT_MM_CreateFrag(NATPT_HASH_FRAG_S stHashFrag);
NATPT_HASH_SESSION_S * NATPT_MM_FindSessionMapByV4 (ULONG ulV4SAddress, 
                                                                    ULONG ulV4Daddress, 
                                                                    USHORT usV4SPort, 
                                                                    USHORT usV4DPort ,
                                                                    UCHAR ucPro);
NATPT_HASH_SESSION_S* NATPT_MM_FindSessionMapByV6 (IN6ADDR_S stV6SAddress, 
                                                                   IN6ADDR_S stV6Daddress, 
                                                                   USHORT usV6SPort,
                                                                   USHORT usV6DPort,
                                                                   UCHAR ucPro);
NATPT_HASH_FRAG_S* NATPT_MM_FindFrag(IN6ADDR_S stV6Saddress, 
                                               IN6ADDR_S stV6Daddress, 
                                               ULONG ulPacketID);

VOID NATPT_MM_HashTimer(VOID*);

BOOL_T  NATPT_AAM_SM_DeleteForV4Addr(ULONG ulV4Addr);
BOOL_T  NATPT_UpdateSesisonTTL  (NATPT_HASH_SESSION_S* pstHashSession,UCHAR ucFlag);
BOOL_T  NATPT_UpdateFragTTL  (NATPT_HASH_FRAG_S* pstHashFrag);

ULONG NATPT_AAM_Init();
ULONG NATPT_AAM_GetV4Addr(NATPT_V6SearchParams_S * pstV6SearchParams, 
                          ULONG *pulV4address, USHORT *pusV4Port);
ULONG NATPT_AAM_Get_Prefix(NATPT_V4SearchParams_S *pstV4SearchParams,
                            IN6ADDR_S *pstV6Prefix);

ULONG NATPT_MGMT_AAM_DOWNLOAD(VOID *pRcvMsg, ULONG ulSlot);

ULONG NATPT_AAM_ValidPrefix(IN6ADDR_S stV6DA,  
                             ULONG *pulIfIndex, 
                             ULONG *pulV4NextHop);
ULONG NATPT_MGMT_AAM_DeleteAll();
ULONG NATPT_AM_AAM_IsPATAddress(ULONG ulV4Addr);

ULONG NATPT_AAM_LCS_UpdateHandlerPAT(ULONG ulEvent, 
                                         SPECS_FUN_VALUE_S *pstFunSpec);


/* BYAD06254 - For Queue based PAT port allocation scheme */
ULONG NATPT_SM_AAM_ReleasePatPort(USHORT usPatPort);
ULONG NATPT_SM_AAM_ReleaseAllPatPorts();
/* BYAD06254 end */

ULONG NATPT_ChgResSpecs_ADDRMAP(SPECS_RES_VALUE_S *pstResSpec,ULONG ulEvent);
ULONG NATPT_ChgResSpecs_MAXDPAT(SPECS_RES_VALUE_S *pstResSpec,ULONG ulEvent);
ULONG NATPT_ChgResSpecs_MAXSESSIONS(SPECS_RES_VALUE_S *pstResSpec,ULONG ulEvent);
ULONG NATPT_MM_LCS_UpdateHandlerDPAT(ULONG ulEvent,SPECS_FUN_VALUE_S *pstFunSpec);

ULONG NATPT_TranslateV6ToV4(MBUF_S *pstMBuf,
                            MBUF_S **ppstMBufALG, 
                            NATPT_PKTCHAR_S *pstPktChar);
ULONG NATPT_TranslateV4ToV6 (MBUF_S *pstMBuf,
                             MBUF_S **ppstMBufALG,
                             NATPT_PKTCHAR_S *pstPktChar);
ULONG NATPT_CreateV4Header (UCHAR *pstV4Hdr,
                            NATPT_PKTCHAR_S *pstPktChar);
ULONG NATPT_CreateV6Header (UCHAR *pstV6Hdr,
                            NATPT_PKTCHAR_S *pstPktChar);
VOID NATPT_AdjustChecksum (UCHAR *pucChksum, 
                            UCHAR *pucOldData, 
                            LONG lOldLen,
                            UCHAR * pucNewData,
                            LONG lNewLen);


ULONG  NATPT_ALG_Translate (MBUF_S *pMBufIn, MBUF_S **ppMBufOut,  VOID *pstHash, USHORT usDirection, USHORT usPort,
                            UCHAR ucProtocol, USHORT ulHdrLen);
ULONG NATPT_ALG_Is_ALGProcessPacket (NATPT_ALG_PROCESSCHECK_S stAlgProcessCheck ) ;

ULONG NATPT_PT_Init();
ULONG NATPT_MM_GetBackUpData();
ULONG NAPT_MM_SetBackUpData(UCHAR* pData,ULONG ulLen);
ULONG NATPT_MM_Smooth();


VOID NATPT_SysDebug(CHAR* szLog);
VOID NATPT_SysWarning(CHAR* szLog);
VOID NATPT_SysLogError(CHAR* szLog);
VOID NATPT_SysLogInfo(CHAR* szLog);

ULONG NATPT_MGMT_AAM_BoardPlugout (ULONG ulSlot);

ULONG NATPT_SetResSpecs_ADDRMAP(SPECS_RES_VALUE_S *pstResSpec);
ULONG NATPT_SetResSpecs_MAXSESSIONS(SPECS_RES_VALUE_S *pstResSpec) ;
ULONG NATPT_SetResSpecs_MAXDPAT(SPECS_RES_VALUE_S *pstResSpec) ;
ULONG NATPT_SetFunSpecs_DPATEnable(SPECS_FUN_VALUE_S *pstResSpec) ;
ULONG NATPT_SetFunSpecs_PATEnable(SPECS_FUN_VALUE_S *pstResSpec) ;
ULONG NATPT_MGMT_AAM_IFDelete(ULONG ulIfnetIndex);
extern IFNET_S * IF_GetIfByFullName(CHAR *);
extern ULONG IF_GetSlotByIndex(ULONG);
ULONG NATPT_ALG_Init();
VOID NATPT_HSB_SetHAState(ULONG ulState);
ULONG NATPT_AM_SetObject_AddrMap(IN6ADDR_S stV6Addr,
                                 ULONG ulV4Addr, 
                                 USHORT usFlag,
                                 UCHAR ucAddrInfoFlag);


ULONG NATPT_AM_SetObject_StaticV4DPATMap(IN6ADDR_S stV6Addr,
                                         ULONG ulV4Addr,
                                         USHORT usV6Port , 
                                         USHORT usV4Port ,  
                                         UCHAR ucPro,
                                         USHORT usFlag);
/*Modified for defect BYAD08095*/
ULONG NATPT_MM_SetObject_TimeOut(ULONG ulTimeoutType , ULONG ulTimeOutValue);
ULONG NATPT_MM_SetObject_MaxSession(ULONG ulMaxSessionNo , USHORT usFlag);

ULONG NATPT_MM_SetObject_ClearSessions();

/*Added for Defect BYAD03928*/

ULONG NATPT_MM_SetObject_ClearStatistics();


ULONG  NATPT_MM_OpenObject_Session(ULONG* pulWaitListHandle,ULONG ulIndex);
ULONG  NATPT_MM_OpenObject_FragMap(ULONG* pulWaitListHandle,ULONG ulIndex);

ULONG NATPT_MM_GetObject_Session_Bulk(ULONG ulWaitListHandle,ULONG ulObjInstance,ULONG ulNum,
                                      ULONG ulNumOfEntryWanted,
                                      ULONG *pulNumOfEntryReturn,
                                      UCHAR ucPro,
                                      NATPT_HASH_SESSION_S* ppstSessionBuffer);

ULONG NATPT_MM_GetObject_Frag_Bulk(ULONG ulWaitListHandle,
                                      ULONG ulObjInstance,
                                      ULONG ulNum,  
                                      ULONG ulNumOfEntryWanted,
                                      ULONG *pulNumOfEntryReturn,
                                      NATPT_HASH_FRAG_S* pstFragBuffer);

ULONG NATPT_MM_GetObject_Session_First(ULONG* pulWaitListHandle, 
                                                      ULONG ulObjInstance,
                                                      ULONG ulNum,
                                                      ULONG ulIndex, 
                                                      NATPT_HASH_SESSION_S** ppstSessionMap);
ULONG NATPT_MM_GetObject_Session_Next(ULONG* pulWaitListHandle,
                                                      ULONG ulObjInstance,
                                                      ULONG ulNum,
                                                      NATPT_HASH_SESSION_S*  pstCurSessionMap,
                                                      NATPT_HASH_SESSION_S** ppstNextSessionMap);
ULONG NATPT_MM_GetObject_TimeOut(NATPT_TIMEOUT_S** ppstNatptTimeOut);
ULONG NATPT_MM_GetObject_MaxSession();
ULONG  NATPT_MM_OpenObject_AddrMap(ULONG* pulWaitListHandle);

ULONG NATPT_MM_GetObject_AddrMap_Bulk(ULONG ulWaitListHandle,
                                      ULONG ulObjInstance,
                                      ULONG ulNum,  
                                      ULONG ulNumOfEntryWanted,
                                      ULONG *pulNumOfEntryReturn,
                                      NATPT_HASH_ADDRMAP_S* pstAddrMapBuffer);

ULONG NATPT_MM_OpenObject_DPAT(ULONG* pulWaitListHandle);


ULONG NATPT_MM_GetObject_DPATMap_Bulk(ULONG ulWaitListHandle,
                                      ULONG ulObjInstance,
                                      ULONG ulNum,  
                                      ULONG ulNumOfEntryWanted,
                                      ULONG *pulNumOfEntryReturn,
                                      NATPT_HASH_DPAT_S* pstDPATMapBuffer);



ULONG NATPT_MM_CloseObject(ULONG* pulWaitListHandle);

ULONG  NATPT_MM_GetStatistics(NATPT_SM_STATS_S** ppstStats,
                               USHORT* pusStaticMappings,
                               USHORT* pusDynamicMappings,
                               ULONG* pulDPATMappings,
                               ULONG* pulIfIndexList,
                               ULONG ulSlot);

ULONG NATPT_MM_SetCount(ULONG ulV4Addr,
                                  IN6ADDR_S stV6Addr,
                                  USHORT usCmdSign,
                                  USHORT usFlag,
                                  ULONG ulSlot);

ULONG NATPT_AAM_SetObject_DyanmicV6Mapping(
                                     ULONG ulACLListNo,
                                     CHAR *pcACLName, 
                                     IN6ADDR_S stNATPTPrefix, 
                                     USHORT usAddrGroupNo, 
                                     USHORT usPATFlag, 
                                     ULONG ulIfnetIndex, 
                                     CHAR *pcIfName, 
                                     USHORT usFlag, 
                                     ULONG ulMappingType, 
                                     ULONG ulIfV4Addr);

ULONG NATPT_AAM_SetObject_V4ACLPrefix(ULONG ulACLListNo, 
                                                 CHAR *pcACLName, 
                                                 IN6ADDR_S  stNATPTPrefix, 
                                                 ULONG ulMappingType, 
                                                 USHORT usFlag);
ULONG NATPT_AAM_SetObject_NATPTPrefix(IN6ADDR_S stNATPTPrefix,
                                                 CHAR *pcIfName, 
                                                 ULONG ulIfIndex, 
                                                 ULONG ulNextHopAddr,
                                                 ULONG ulPrefixType,
                                                 USHORT usFlag
                                                 );
ULONG NATPT_AAM_GetObject_AddressGroup_First(
                                       NATPTAddrGroupIndex_S **ppstAddrGrp);

ULONG NATPT_AAM_GetObject_AddressGroup_Next(
                                              NATPTAddrGroupIndex_S *pstLastIndex,
                                              NATPTAddrGroupIndex_S **ppstAddrGrp);

ULONG NATPT_AAM_GetObject_DynamicV6Bound_First(
                                               NATPTv6Access_S **ppstV6Access);



ULONG NATPT_AAM_GetObject_DynamicV6Bound_Next(
                                                  NATPTv6Access_S *pstLastIndex, 
                                                  NATPTv6Access_S  **ppstV6Access);


ULONG NATPT_AAM_GetObject_DynamicV4Bound_First(
                                                    NATPTv4Access_S **ppstV4Access);


ULONG NATPT_AAM_GetObject_DynamicV4Bound_Next(
                                         NATPTv4Access_S  *pstLastIndex, 
                                         NATPTv4Access_S  **ppstV4Access);

ULONG NATPT_AAM_GetObject_Prefix_First(NATPTPrefixInfo_S **ppstPrefixInfo);

ULONG NATPT_AAM_GetObject_Prefix_Next(NATPTPrefixInfo_S *pstLastIndex,
                                                NATPTPrefixInfo_S **ppstPrefixInfo);

ULONG NATPT_AAM_SetObject_AddressGroup(ULONG ulStartAddr, 
                                                   ULONG ulEndAddr, 
                                                   USHORT usPoolNumber, 
/* For defect BYAD04881 */                                                   USHORT usFlag);
ULONG NATPT_PT_SetObject_TrafClass(UCHAR ucTrafFlag,
                                            USHORT usFlag);

BOOL_T NATPT_AM_DeleteAllDynamic();
ULONG NATPT_MGMT_SetObject_Enable (ULONG ,USHORT );
ULONG NATPT_MGMT_GetObject_Debug(UCHAR *pucNatptDebug,ULONG ulIfnetIndex);
ULONG NATPT_MGMT_SetObject_DebugFlag (UCHAR, ULONG ,USHORT );


ULONG NATPT_Core_Init(COM_ID_INFO_S *pstComInfo, ULONG  ulComLen);
ULONG NATPT_SetModuleInfo( NATPT_MOD_INFO_S *pstModInfo);
ULONG NATPT_Activate_Com() ;

ULONG NATPT_Register_NonComInt (NATPT_NonCompINT_S* pstNATPT_NonCompINT);
ULONG NATPT_HA_GetBackUPData(ULONG ulBackupType);
ULONG NATPT_HA_Smooth ();
ULONG NATPT_HASetBackupData (UCHAR* ,ULONG);
ULONG NATPT_IO_Forward (MBUF_S *);

ULONG NATPT_MGMT_IFDelete (ULONG );

ULONG NATPT_EnableInterface (ULONG );
ULONG NATPT_DisableInterface (ULONG );

ULONG NATPT_MGMT_IO_DeleteAll ();

ULONG NATPT_InIPv4 (MBUF_S *);
ULONG NATPT_AAM_ARP_CheckPoolAddr(ULONG ulV4Addr, 
                                              ULONG ulIfIndex );
ULONG NATPT_AAM_AddrChange(ULONG ulIfIndex,
                                    USHORT usEvent,
                                    ULONG ulNewV4Addr);
ULONG NATPT_AAM_Get_Addr_ByAddrGroupNo(USHORT usAddrGroupNo,
                                                     IN6ADDR_S stV6SrcAddr,
                                                     UCHAR ucIsDNS,
                                                     ULONG *pulFreeAddr);
ULONG NATPT_IPv4OutputRegCallback (MBUF_S *);
ULONG NATPT_InIPv6(MBUF_S *pstMBuf);
ULONG NATPT_IPv6OutputRegCallback (MBUF_S *);

ULONG NATPT_AAM_Update_IfIndex(VOID *pRcvMsg);
ULONG NATPT_AAM_Update_IfIndexAndV4addr(VOID *pRcvMsg);
ULONG NATPT_Core_DeInit();

ULONG NATPT_PT_GetTrafClass(UCHAR *pucTrafFlag);
/* end of defect BYAD04881 */
ULONG NATPT_SM_SetSessTTLtoCurTime();
/*Added for Defect BYAD05489*/
BOOL_T NATPT_AM_CheckAMforV6Addr(IN6ADDR_S stV6Addr);

ULONG NATPT_MM_UndoEnable(ULONG ulSlot);
/* For defect BYAD07830 */

ULONG NATPT_MGMT_NoDebugAll();
/* end of defect BYAD07830 */

VOID NATPT_CreateV4PseudoHdr (NATPT_V4PSEUDOHDR_S *pstV4PsdHdr,
                               NATPT_PKTCHAR_S *pstPktChar);
VOID NATPT_CreateV6PseudoHdr (NATPT_V6PSEUDOHDR_S *pstV6PsdHdr,
                               NATPT_PKTCHAR_S *pstPktChar);
VOID NATPT_CalcChecksum (UCHAR *pucData,
                         ULONG  ulLength,
                         UCHAR *pucChecksum);

/* For defect BYAD11433 */
ULONG NATPT_MGMT_SetObject_AllowPrvAddr (USHORT usFlag);
ULONG NATPT_MGMT_GetObject_AllowPrvAddr (UCHAR *pucAddr);
/* End of defect BYAD11433 */

#ifdef  __cplusplus
}
#endif

#endif
