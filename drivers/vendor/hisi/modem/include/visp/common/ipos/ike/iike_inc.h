

#ifndef _IKE_IIKEINC_H
#define _IKE_IIKEINC_H

#ifdef __cplusplus
extern "C"{
#endif


/* Begin:Support multip VISP and IPOS environment by james*/
/*Component ID declaration */
/*S9300 - Added by Nagendra*/
/*For S9300, CID_IKE is available from Ipos_idbase.h*/
/* Kranthi: ARChanges */
#if (((S9300_MODULE_SEC_IPSEC != VRP_YES)\
     || (IR_PRODUCT_BUILD_TYPE != PRODUCT_TYPE_S9300_V1V2))\
     || (VRP_YES == VRP_MODULE_IKE_IPSEC_FOR_AR))

#ifndef CID_IKE
#define CID_IKE                 (CID_SEC_BASE + 1)
#endif
#endif

/*S9300 - Added by Nagendra*/
#ifndef CID_IKEV2
#define CID_IKEV2               (CID_IKE + 1)
#endif

/* Interface IDs declaration */
/*S9300 - Added by Nagendra*/
/*For S9300, IID_IKE_BASE is available from Ipos_idbase.h*/
/* Kranthi: ARChanges */
#if (((S9300_MODULE_SEC_IPSEC != VRP_YES) \
            || (IR_PRODUCT_BUILD_TYPE != PRODUCT_TYPE_S9300_V1V2))\
        || (VRP_YES == VRP_MODULE_IKE_IPSEC_FOR_AR))
#ifndef IID_IKE_BASE
#define IID_IKE_BASE            (IID_SEC_BASE + 10)
#endif
#endif

/*S9300 - Added by Nagendra*/
#ifndef IID_IKEV2_BASE
#define IID_IKEV2_BASE          (IID_IKE_BASE + 10)
#endif

/* End:Support multip VISP and IPOS environment by james*/


#define IID_IKE_INTF_CFG        (IID_IKE_BASE + 5)
#define IID_IKE_INTF_FUN        (IID_IKE_BASE + 6)

#define IID_IKEV2_INTF_CFG      (IID_IKEV2_BASE + 4)
#define IID_IKEV2_INTF_FUN      (IID_IKEV2_BASE + 5)

#define IID_IKEV1V2_INTF_CFG    (IID_IKEV2_BASE + 6)

#define IID_IKEV2_INTF_HSB      (IID_IKEV2_BASE + 7)

#define IID_IKEV1V2_INTF_HSB    (IID_IKEV2_BASE + 8)


DECLARE_INTERFACE (IIF_IKE_ComIntCFG)
{
    IUNKNOWN_METHODS

/*------------------------------------------------------------------------
    Component configuration functions
------------------------------------------------------------------------*/
    METHOD_(ULONG, pfIKE_SetDelProposalLevel)(ULONG ulProposalNum,
                                              ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetProposalAuthMethod)(ULONG ulProposalNum,
                                                ULONG ulAuthMethodType);
    METHOD_(ULONG, pfIKE_SetProposalEncrAlgorithm)(ULONG ulProposalNum,
                                                   ULONG ulEncryptionType);
    METHOD_(ULONG, pfIKE_SetProposalAuthAlgorithm)(ULONG ulProposalNum,
                                                   ULONG ulAuthAlgorithmType);
    METHOD_(ULONG, pfIKE_SetProposalDHGroup)(ULONG ulProposalNum,
                                             ULONG ulDHGroupType);
    METHOD_(ULONG, pfIKE_SetISAKMPSALife)(ULONG ulProposalNum,
                                          ULONG ulLifeTime, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelLocalID)(CHAR* pucLocalId,
                                        ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelIkePeer)(CHAR* pucIkePeerName,
                                        ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetPeerNATTraversal)(CHAR* pucIkePeerName,
                                              ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetPeerExchangeMode)(CHAR * pucIkePeerName,
                                              ULONG ulExchangeMode);
    METHOD_(ULONG, pfIKE_SetPeerIDType)(CHAR * pucIkePeerName, ULONG ulIdType);
    METHOD_(ULONG, pfIKE_SetPeerProposalNum)(CHAR * pucIkePeerName,
                                             ULONG ulProposalNum,
                                             ULONG ulOpMode);

    /* Defect AC4D03031: Added new API */
    METHOD_(ULONG, pfIKE_SetCurSAValue) (ULONG ulCurValue);
    METHOD_(ULONG, pfIKE_GetAllProposalName) (ULONG **ppulIKEProposalNum,
                                              ULONG *pulProposalSum);
    METHOD_(ULONG, pfIKE_GetAllProposalStructure) (
                                IKE_PROPOSAL_CONTENT_S **ppstProposalContent,
                                ULONG *pulProposalSum);
    METHOD_(ULONG, pfIKE_GetProposalByNumber) (ULONG ulIKEProposalNum,
                                IKE_PROPOSAL_CONTENT_S *pstIKEProposalContent);
    METHOD_(ULONG, pfIKE_SetDelPreSharedKey) (CHAR *pucIkePeerName,
                                              CHAR *pucKeyName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelRemoteName)(CHAR *pucIkePeerName,
                                           CHAR *pucRemoteName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelPeerAddress) (CHAR *pucIKEPeerName,
                                        ULONG ulIpAddress, ULONG ulEndIpAddress,
                                        CHAR *pucVPNName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_BindSaVPN)(CHAR * pucIkePeerName, CHAR* pucVPNName,
                                    ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_GetPeerInfoByName)(CHAR* pucIkePeerName,
                                            IKE_PEER_CONTENT_S* pstPeerContent);
    METHOD_(ULONG, pfIKE_GetTotalNumberOfPeers) (ULONG *pulPeerSum);
    METHOD_(ULONG, pfIKE_GetPeerName) (
                CHAR (*pucPeerName)[IKE_PEER_NAME_MAX_LEN], ULONG ulBeginIndex,
                ULONG ulNumber, ULONG * pulActualNumber);
    METHOD_(ULONG, pfIKE_GetSAByConnID)(ULONG ulConID,
                                        IKE_SA_CONTENT_S *pstSAContent);
    METHOD_(ULONG, pfIKE_SetDelKeepaliveInterval)(ULONG ulInterval,
                                                  ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelKeepaliveTimeout)(ULONG ulTimeout,
                                                 ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelNatKeepaliveInterval)(ULONG ulInterval,
                                                     ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_ClearSA)(ULONG ulConnectionID, CHAR *szIfname);
    METHOD_(ULONG, pfIKE_ClearAllSA)(VOID);


    METHOD_(ULONG, pfIKE_GetIKESABrief) (ULONG ulWaitListHandle,
                                         IKE_SA_CONTENT_S **ppstIKESAContent,
                                         ULONG *pulIKESASum);

    METHOD_(ULONG, pfIKE_GetLocalID)(CHAR *pucLocalID);
    METHOD_(ULONG, pfIKE_GetKeepaliveInterval)(ULONG* pulInterval);
    METHOD_(ULONG, pfIKE_GetKeepaliveTimeout)(ULONG* pulTimeout);
    METHOD_(ULONG, pfIKE_GetNatKeepaliveInterval)(ULONG* pulNatInterval);
    METHOD_(ULONG, pfIKE_SetReset_Debug) (ULONG ulNoFlag, ULONG ulType);
    METHOD_(ULONG, pfIKE_OpenObject_Proposal) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_Proposal) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkProposal)(ULONG ulWaitListHandle,
                    ULONG ulNumOfProposalWanted, ULONG *pulNumOfPropReturn,
                    IKE_PROPOSAL_CONTENT_S  *pProposalBuf);
    METHOD_(ULONG, pfIKE_OpenObject_Peer) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_Peer) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkPeer)(ULONG ulWaitListHandle,
                    ULONG ulNumOfPeerWanted, ULONG *pulNumOfPropReturn,
                    IKE_PEER_CONTENT_S *pPeerBuf);


    METHOD_(ULONG, pfIKE_OpenObject_SA) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_SA) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkSA)(ULONG ulWaitListHandle,
                    ULONG ulNumOfSAWanted, ULONG *pulNumOfPropReturn,
                    IKE_SA_CONTENT_S *pSABuf, UCHAR ucPhase);

    METHOD_(ULONG, pfIKE_OpenObject_Exchange)(ULONG * pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_Exchange)(ULONG * pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkExchange)(ULONG ulWaitListHandle,
                    ULONG ulNumOfExchangeWanted, ULONG * pulNumOfExchangeReturn,
                    IKE_EXCHANGE_CONTENT_S * pstExchangeBuf);
    METHOD_(ULONG, pfIKE_OpenObject_Event)(ULONG * pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_Event)(ULONG * pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkEvent)(ULONG ulWaitListHandle,
                    ULONG ulNumOfEventWanted, ULONG * pulNumOfEventReturn,
                    IKE_EVENT_CONTENT_S * pstEventBuf);
    METHOD_(ULONG, pfIKE_OpenObject_Transport)(ULONG * pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_Transport)(ULONG * pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkTransport)(ULONG ulWaitListHandle,
                                    ULONG ulNumOfTransportWanted,
                                    ULONG *pulNumOfTransportReturn,
                                    IKE_TRANSPORT_CONTENT_S * pstTransportBuf);
    METHOD_(ULONG, pfIKE_GetGlobalInfo) (
                                    IKE_GLOBAL_CONTENT_S *pstIKEGlobalContent);
    METHOD_(ULONG, pfIKE_GetStats) (
                                    IKE_STATS_CONTENT_S *pstIKEStatsContent);
    METHOD_(ULONG, pfIKE_SetHeartbeatSPIList) (ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_GetVersion) (CHAR *szVer);

    /* AC4D02681,Removed from macro pruining */
    METHOD_(ULONG, pfIKE_SetMaxDeleteSa) (ULONG ulRead);
    METHOD_(ULONG, pfIKE_SetMinHrtbtInt) (ULONG ulRead);
    METHOD_(ULONG, pfIKE_SetPfkeyReadInt) (ULONG ulRead);

    /* @@Gopa */
    METHOD_(ULONG, pfIKE_ShowDebuggingAPI)(ULONG *pulDbgFlg);
    METHOD_(ULONG, pfIKE_SetHeartbeatSeqNum) (UCHAR ucSeqNumType);

    METHOD_(VOID, pfIKE_HeartbeatTimeoutNegotiation) ();
    METHOD_(ULONG, pfIKE_GetProductDefault) (IKE_PRODUCT_VAL_S *pstIKEProd);

    METHOD_(ULONG, pfIKE_ClearAllPhase1Phase2SA)(VOID);

    METHOD_(ULONG, pfIKE_ResetStatistics)(VOID);
    METHOD_(ULONG, pfIKE_SetResetDpd)(CHAR *szPeerName,
                                      IKE_DPD_CFG_S *pstDpdCfg);
    METHOD_(ULONG, pfIKE_EnableDisableDpd)(CHAR *szPeerName,
                                           IKE_DPD_EN_CFG_S *pstDpdCfg);

    METHOD_(ULONG, pfIKE_SetPeerXauth)(CHAR *szIkePeerName,UCHAR ucXauthMode,
                                       ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetResetXauthType)(CHAR *szIkePeerName,
                                            UCHAR ucXauthType,
                                            ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetPeerXauthAttributes)(CHAR *szIkePeerName,
                                                IKE_XAUTH_ATTR_S *pstXauthAttr,
                                                ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetPeerXauthPasscode)(CHAR *szIkePeerName,
                                               UCHAR *szPasscode,
                                               ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetRChapHashSeq)(CHAR *szIkePeerName,UCHAR ulHashSeq);
    METHOD_(ULONG, pfIKE_SetOtpPswdMode)(CHAR *szIkePeerName,
                                         UCHAR ulOTPPswdMode);
    METHOD_(ULONG, pfIKE_SetPeerIDKeyID)(CHAR *szPeerName, UCHAR *szGrpName);
    METHOD_(ULONG, pfIKE_SetDelModeCfg) (CHAR *szIkePeerName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_DisplayModeCfgAddresses)(UCHAR * pucPeerName,
                                                  IKE_ADDR_CONTENT_S *pstData);
    METHOD_(ULONG, pfIKE_SetModeCfgVID)(CHAR *szIkePeerName, UCHAR ucSetVID,
                                        UCHAR *pucVid);
    METHOD_(ULONG, pfIKE_SetDpdHashCalcSequence)(CHAR *szIkePeerName,
                                                UCHAR ucHashSeq);
    METHOD_(ULONG, pfIKE_OpenCloseSocket)(ULONG ulFlag);
    METHOD_(ULONG, pfIKE_SetSockPriority)(UCHAR ucOpmode,
                                            ULONG ulPriorityLevel);
    METHOD_(ULONG, pfIKE_GetSockPriority)();

    /* Sumangala : Added for New API requirement from SGSN */
    METHOD_(ULONG, pfIKE_ClearPh1Ph2ByPeerAddress)(ULONG ulPeerIpAddress,
                                                   ULONG ulNotify);

    /*B500 - SGSN-CMD Registration*/
    METHOD_(ULONG, pfIKE_Config_Peer) (IKE_PEER_CONFIG_S *pstIkePeerConfig);
    METHOD_(ULONG, pfIKE_Get_Peer) (CHAR * szIkePeerName,
                                            IKE_PEER_CONFIG_S * pstIkePeer);
    METHOD_(ULONG, pfIKE_Config_Peer_Dpd) (IKE_DPD_CONFIG_S * pstIkeDpdConfig);
    METHOD_(ULONG, pfIKE_Get_Peer_Dpd) (CHAR * szIkePeerName,
                                        IKE_DPD_CONFIG_S * pstIkeDpdConfig);
    METHOD_(ULONG, pfIKE_Config_Peer_Xauth) (
                                        IKE_XAUTH_CONFIG_S * pstIkeXauthConfig);
    METHOD_(ULONG, pfIKE_Get_Peer_Xauth) (CHAR * szIkePeerName,
                                    IKE_XAUTH_CONFIG_S * pstIkeXauthConfig);
    METHOD_(ULONG, pfIKE_Config_Proposal) (
                            IKE_PROPOSAL_CONFIG_S * pstIkeProposal);
    METHOD_(ULONG, pfIKE_Get_Proposal) (ULONG ulProposalNum,
                                    IKE_PROPOSAL_CONFIG_S * pstIkeProposal);

    /*Sunil: IKE packet trace*/
    METHOD_(ULONG, pfIKE_EnableDisablePacketTrace)(ULONG ulSetReset);

    /*Defect AC4D07275 IKE stats*/
    METHOD_(ULONG, pfIKE_GetMsgStats)(IKE_MSG_STAT_S *pstMsgStat);
    METHOD_(ULONG, pfIKE_DeleteMsgStats)();

    /*Sunil: Source address for peer*/
    METHOD_(ULONG, pfIKE_CmnSetPeerLocalAddr) (CHAR *szInputIkePeerName,
                        ULONG ulLocalAddr, ULONG ulOpMode);

    /* AC4D07706 : New requirement to delete IKEv1 ready/non-ready state SA's */
    METHOD_(ULONG, pfIKEv1_ClearAllSASync) (UCHAR ucIPVersion);

    METHOD_(ULONG, pfIKE_PKI_SetResetPkiObj) (CHAR *szInputIkePeerName, CHAR *pszObj,
                                        ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_PKI_SetResetIdentityValidation) (CHAR *szInputIkePeerName,
                                                        ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_PKI_SetResetUseDefaultCert) (CHAR *szInputIkePeerName,
                                                    ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_PKI_CheckObjectIsInUse) (CHAR *pszObjectName);
    METHOD_(ULONG, pfIKE_PKI_GetPkiStatistics) (IKE_PKI_STAT_S *pstPkiStat);
    METHOD_(ULONG, pfIKE_PKI_ResetPkiStatistics) ();
    /* Added new APIs */
    METHOD_(ULONG, pfIKE_GetObjectNameByPeer)  (CHAR *pszPeerName, CHAR *pszObjName);
    METHOD_(ULONG, pfIKEv1_GetDefaultValues) (IKEV1_DEFAULT_S *pstIKEv1Default);
    /* IPSEC6_Changes Story 10 */
    METHOD_(ULONG, pfIKE_ResetPeerDpdStat)(CHAR *pszPeerName);

    /*Iteration2: Story12: Maintainance*/
    METHOD_(VOID, pfIKE_GetPfkeyv2Stats)(IKE_PFKEYV2_STATS_S *pstStats);
    METHOD_(VOID, pfIKE_GetPfkeyv2FailStats)(
                        IKE_PFKEYV2_FAIL_STATS_S *pstFailStats);
    METHOD_(VOID, pfIKE_ResetPfkeyv2Stats)();

    METHOD_(ULONG, pfIKE_PKI_SetResetInBandExchange) (CHAR *szInputIkePeerName,
                                        ULONG ulType, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_ClearSAByPeerName) (CHAR *pszIkePeerName, ULONG ulNotifyFlag);
    /*SGSN License implementation - B511*/
    METHOD_(ULONG, pfIKE_EnableDisableLicense) (ULONG ulLicenseFlag);
    METHOD_(ULONG, pfIKE_GetLicenseStatus) (VOID);
    METHOD_(ULONG, pfIKE_CmnEnableDisableDhHwApis) (ULONG ulEnable,
                                IKE_DH_HW_REG_FUNC *pstDHHwRegFuncs);
    METHOD_(VOID, pfIKE_CMN_DH1PoolInit)(ULONG ulEnable,  ULONG ulPoolSize);
    METHOD_(VOID, pfIKE_CMN_DH2PoolInit)(ULONG ulEnable,  ULONG ulPoolSize);
    /*Kuldeep : B513 Changes*/

    /*SGSN CR:201002270076 Delete SA's by IP address and VRF Name*/
    METHOD_(ULONG, pfIKE_ClearSAByPeerAddrAndVRFName) (ULONG ulIpAddr, CHAR *pszVRFName,
                                    ULONG ulPhase, ULONG ulNotify);

    /*Kuldeep : B514 Changes*/
    METHOD_(ULONG, pfIKE_RegisterGetLocalIDForPeerFunc_Callback) (
                           IKE_RegFuncGetPeerID_HOOK_FUNC pfFunc);

    /*B515 LTE Peer ID type control, support */
    METHOD_(ULONG, pfIKE_SetIDType) (CHAR *szInputIkePeerName, ULONG ulIdType);

    METHOD_(ULONG, pfIKEv1_StartPh1SaRekey)(UCHAR *pucPeerName, ULONG ulHardTimeout);

    METHOD_(ULONG, pfIKEv1_SetResetSupportedAlgorithm)
                    (IKEV1_SA_PARAM_S *pstSaParam, ULONG ulOpMode);
    METHOD_(ULONG, pfIKEv1_GetSupportedAlgorithm)
                    (IKEV1_SA_PARAM_S *pstSaParam);

    METHOD_(ULONG, pfIKE_SetDelPeerUseAllSupportedAlgs)
                        (CHAR* szInputIkePeerName, ULONG ulOpMode);

    METHOD_(ULONG, pfIKE_SetDelPeerLifeTime)(CHAR* szInputIkePeerName,
                                                ULONG ulTime, ULONG ulOpMode);

    /*PKI alarm for CERT expiration*/
    METHOD_(ULONG, pfIKE_GetPeerIpByConnID)
                                        (ULONG ulConnId, ULONG *pulPeerIpAddr);
    METHOD_(ULONG, pfIKE_SetMaxPeerProposalNum)(ULONG ulMaxPeerNum,
                                    ULONG ulMaxPropNum, ULONG ulMaxSaNum);

    /* B045 : Added API to get ready state SA conn-id for IKEv1/IKEv2 phase-1 SA */
    METHOD_(ULONG, pfIKE_GetSAConnIDByPeerName) (UCHAR *pucPeerName, ULONG *pulConnID);

    /*B057: key deletion from IKE/IPSEC after SA establishment*/
    METHOD_(ULONG, pfIKE_EnableKeyDeletion) (ULONG ulOpMode);
    /*B058: stats improvement for IKEv2 message exchange*/
    METHOD_(ULONG, pfIKE_GetIKEV1ExchStats) (IKE_V1EXCHANGE_STATS_S *pstIkev1ExchStat);
    METHOD_(ULONG, pfIKE_DeleteIKEv1ExchStats) ();

    /* Iteration-3 Ipv6 compatability modification*/
    METHOD_(ULONG, pfIKE_ClearAllSAByAddrType)(UCHAR ucIPVersion);

    METHOD_(ULONG, pfIKE_GetBulkPeerByVersion)(ULONG ulWaitListHandle,
                   ULONG ulNumOfPeerWanted, ULONG *pulNumOfPeerReturn,
                   IKE_PEER_CONTENT_S *pstPeerBuf,  UCHAR ucIPVersion);

    METHOD_(ULONG, pfIKE6_ClearPh1Ph2ByPeerAddress)(
                                    IN6ADDR_S *pstIPv6Address, ULONG ulNotify);

    /*Ipv6: Security Support*/
    METHOD_(ULONG, pfIKE6_SetDelIkePeer)(CHAR *szIkePeerName,
                        ULONG ulOpMode, ULONG ulVersion);
    METHOD_(ULONG, pfIKE6_CmnSetPeerLocalAddr) (CHAR *szInputIkePeerName,
                            IN6ADDR_S *pstLocalV6Address, ULONG ulOpMode);

    METHOD_(ULONG, pfIKE6_SetDelPeerAddress) (CHAR *szIkePeerName,
                            IN6ADDR_S *pstIPv6InputAddr, ULONG ulOpMode);

    METHOD_(ULONG, pfIKE_Ipv6RegisterAndInit) (ULONG (*pfRegisterIpv6ForIke)(
                                                            ULONG), ULONG);

    /*GGSN*/
    METHOD_(ULONG, pfIKE_CmnPacketInput)(IKE_PACKET_INFO_S *pstPktInfo,
                                        UCHAR *pucMsgBuf, ULONG  ulMsgBufLen);
    METHOD_(ULONG, pfIKE_IPSEC_CmnRegisterGgsnCbk)
                                    (CMN_GGSN_API_CALLBACK_S *g_pstGgsnCbk);
    METHOD_ (ULONG, pfIKE_DelSaAfterTimeout) (ULONG ulConnectionID,
            UCHAR *pucIKEInitSpi, UCHAR *pucIKERespSpi,
            UCHAR ucInitAndRespSpiLen, ULONG ulTimeout);

    METHOD_(ULONG, pfIKE_GetBulkSAByType)(ULONG ulWaitListHandle,
                ULONG ulNumOfSAWanted, ULONG *pulNumOfPropReturn,
                IKE_SA_CONTENT_S *pSABuf, UCHAR ucPhase,
                IKE_DISPLAY_TYPE_S *pstDispType, UCHAR ucIPVer);

    METHOD_(ULONG, pfIKE_CmnSetResetGlobalAuthMethod) (UCHAR ucAuthMethod,
                                                        UCHAR ucOpMode);

    METHOD_(ULONG, pfIKE_ClearPh1Ph2ByPeerAddressSync) (ULONG ulPeerIpAddress, ULONG ulVrfIndex);

    METHOD_(ULONG, pfIKE_CmnSetResetPeerAuthDomain) (CHAR *pszPeerName,
                                            CHAR *pszAuthDomain, UCHAR ucOpMode);

    METHOD_(ULONG, pfIKE_PROF_GetBulkSAByProfile) (ULONG ulWaitListHandle, ULONG ulNumOfSAWanted,
                                               ULONG *pulNumOfSAReturn, IKE_SA_CONTENT_S *pstSABuf,
                                               UCHAR ucPhase, CHAR *pszProfileName);

    METHOD_(ULONG, pfIKE_PROF_GetBulkSpokePeer)(ULONG ulWaitListHandle,
                     ULONG ulNumOfPeerWanted, ULONG *pulNumOfPeerReturn,
                       IKE_SPOKE_PEER_CONTENT_S *pstPeerBuf, UCHAR* pucProfileName, UCHAR ucIPVersion);
    METHOD_(ULONG, pfIKE_DNSReturnResolvedIP)(CHAR *pszFQDN, ULONG *pulIpAddr, ULONG ulNumOfAddress, VOID *pvHandle);
    METHOD_(ULONG, pfIKE_SetDelPeerFQDN)(UCHAR *pucIkePeerName, UCHAR *pucRemoteName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_IPSEC_RegisterSPLFeatureCbk) (IKE_IPSEC_SPLFEATURECBK *pstCbk);
    METHOD_(ULONG, pfIKE_GetSplStats)(IKE_IPSEC_SPLFEATURESTAT *pstSplStats);
    METHOD_(VOID *, pfIKE_GetSAByPkiObj)(VOID *pstObj);
    METHOD_(ULONG, pfIKE_SetDelOCSPServerTimeout)(ULONG ulTimeOut, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelModeCfgServerTimeout)(USHORT usTimeOut, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE6_GetBulkSA)(ULONG ulWaitListHandle, ULONG ulNumOfSAWanted, ULONG *pulNumOfPropReturn,
                                IKE_SA_CONTENT_S *pSABuf, UCHAR ucPhase);

    METHOD_(ULONG, pfIKE6_ClearPh1Ph2ByPeerAddressSync)(IN6ADDR_S *pstIPv6Address);
    /* Added for EasyVPN */
    METHOD_(ULONG, pfIKEv1_SetDelDefaultEzVpnIkePeer) (CHAR *szIkePeerName, ULONG ulOpMode);

    METHOD_(ULONG, pfIKE6_SetSockPriority)(UCHAR ucOpmode, ULONG ulPriorityLevel);
    METHOD_(ULONG, pfIKE6_GetSockPriority)();
    METHOD_(ULONG, pfIKE_GetPeerNameByConnID)(ULONG ulConnId, UCHAR *szPeerName);
    METHOD_(ULONG, pfIKE6_GetPeerIpByConnID)(ULONG ulConnId, IN6ADDR_S *pstPeerIpAddr);

    /*B054: crypt sign*/
    METHOD_(ULONG, pfIKE_RegisterPkiCryptSignFunc_Callback)
                (IKE_SHELL_CALLBACK_PKI_CRYPT_SIGN_S *pstIkeCallbackPKICryptSign);

    /* Multi-SeGw Feature */
    METHOD_(ULONG, pfIKE_SetResetLocalBackupPeer)(UCHAR *pucPeerName, UCHAR ucIsLocalPeer,
                                                UCHAR *pucMasterPeerName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_StartNegotiation)(UCHAR *pucPeerName, UCHAR ucPeerType);
    METHOD_(ULONG, pfIKE_StopNegotiation)(UCHAR *pucPeerName, UCHAR ucPeerType);
    METHOD_(ULONG, pfIKE_SetSwitchBack)(UCHAR *pucPeerName, UCHAR ucFlag);
    
	/* HERT3.3 : DH Support in HW */
    METHOD_(ULONG, pfIKE_CmnRegisterHWAPIs)(IKE_DH_HW_CBK_S *pstHwRegAPIs);
};


DECLARE_INTERFACE (IIF_IKE_ComIntFun)
{
    IUNKNOWN_METHODS
    METHOD_(ULONG, pfIKE_SALookupByConnid)(ULONG conn_id,
                                           IKE_SA_PORT_S  *pstIkeSA);
    METHOD_(ULONG, pfIKE_SearchIKEPeer) (UCHAR *pPeerName,
                                         IKE_PEER_CONTENT_S  *pstIkePeer,
                                         ULONG ulTaskLock);
    METHOD_(ULONG, pfIKE_XauthSetDynamicAttr)(IKE_XAUTH_DYNAMIC_USER_ATTR_S
                                                *pstAttrFromUser);
    METHOD_(ULONG, pfIKE_GET_CFG_Attributes)(IKE_GET_ATTR_S *pstGetAttr,
                                             IKE_PRODUCT_NOTIFY_S *pstAttrData);

    METHOD_(ULONG, pfIKE_UnReg_CFG_Attr_Notify_Func) (ULONG ulHandle);

    METHOD_(ULONG, pfIKEv1_RegPacketHook)(IKE_GetAppControlPacket_HOOK_FUNC pfHookFunc);

    METHOD_(ULONG, pfIKE_PKI_CRLDownloadComplete) (ULONG ulReqIdentifier,
                                                    ULONG ulFlag);
    /* AC4D07928 [B116] : Support Tunnel UP/DOWN notification */
    METHOD_(ULONG, pfIKE_RegisterTunnelStatus_Callback) (
                                        IKE_TUNNEL_STATUS_CALLBACK pfFuncPtr);

    /* IPSEC6.STORY.04 - Removal of Pfkey socket */
    METHOD_(ULONG, pfIKE_ExtWritePfkeyEventToIKETask) (ULONG ulMsgType,
                                                 ULONG ulData, ULONG ulEvType);

    /*Added for Warning messages in IPOS.*/
    METHOD_(ULONG, pfIKE_cmn_RegisterWarningAPI)(pfIKE_WarningOut pfFunc);

    /*SGSN License implementation - B511*/
    METHOD_(ULONG, pfIKE_GetLicenseStatus_Callback) (
                       IPSECIKE_GET_LICENSE_STATE_CALLBACK_FUNC pfFunc);

    /*AP : Allowing duplicate remote name in different peers*/
    METHOD_(ULONG, pfIKE_RegisterDuplicateRemoteNameCallback) (
                       IKE_DUPLICATE_REMOTE_NAME pfFunc);

    METHOD_(ULONG, pfIKE_PKI_CertStatusDownloadComplete) (VOID *pstPKIObject,ULONG ulErrorFlag, ULONG ulAppData);

    METHOD_(ULONG, pfIKE_PROF_CreateDelIKEPeer)(UCHAR *pszProfileName, UCHAR *pucProfPeerName,
                                                ULONG ulProfileID, ULONG ulLocalAddr,
                                                ULONG ulPeerAddress, ULONG ulVrfIndex,
                                                UCHAR *pucNewPeerName, ULONG ulOpMode);

    /*Added for ipsec-profile deletespoke support*/
    METHOD_(ULONG, pfIKE_ClearPh1Ph2ByPeerAddress)(ULONG ulPeerIpAddress, ULONG ulNotify);


    /*get IfIndex by peer IP address*/
    METHOD_(ULONG, pfIKE_PROF_GetProfileIdByIPAddr)(ULONG ulDestAddress, ULONG *pulProfileID);

    METHOD_(ULONG, pfIKE_CmSearchSAByPeerAddressAndVrf) (ULONG ulPeerAddress, ULONG ulVrfIndex);

    METHOD_(ULONG, pfIKE_ClearPh1Ph2ByVrfPeerAddressSync) (ULONG ulPeerIpAddress, ULONG ulVrfIndex);

    METHOD_(ULONG, pfIKE_CmnSetResetSupportedIPSecAlg)(VOID *pvPropParam, ULONG ulOpMode);

    METHOD_(VOID, pfIKE_CmnGetSupportedIPSecAlgorithms)(VOID *pvPropParam);

    METHOD_(ULONG, pfIKE_PROF_DynamicUpdateByProfID) (UCHAR *szPeerName, ULONG ulProfileID, ULONG ulProfPeerUpdateType, UCHAR ucUpdateTdb);

    METHOD_(ULONG, pfIKE_CmnResolveFQDN)(UCHAR *pucPeerName);

    METHOD_(ULONG, pfIKE_SetModeCFGAttributes)(IKE_AAA_ID_INFO_S *pstIDInfo,
                        IKE_AAA_MODECFG_ATTR_S *pstProductModeCfgAttr);
    /* Added for EasyVPN */

    METHOD_(ULONG, pfIKE_EasyVPN_GetDefaultPeerName) (UCHAR *pucPeerName, ULONG ulIkeVersion);

    METHOD_(ULONG, pfcheck_ike_peer_addr_conflict) (VOID *pvIkepeer,
                                                    VOID *pvRemoteAddr1, VOID *pvRemoteAddr2,
                                                    ULONG ulVrfIndex);

    METHOD_(ULONG, pfIKE_CheckFqdnConflict) (UCHAR *pucRemoteName);
    METHOD_(VOID*, pfIKE_SearchPeerByRemoteAddrAndVrfIndx)(VOID *pvDestAddr, ULONG ulVrfIndx);
};


/* IKEv2 Component Config interface */
DECLARE_INTERFACE (IIF_IKEv2_ComIntCFG)
{
    IUNKNOWN_METHODS

/*------------------------------------------------------------------------
    Component configuration functions
------------------------------------------------------------------------*/
    METHOD_(ULONG, pfIKEv2_GetVersion) (CHAR *szVer);
    METHOD_(ULONG, pfIKEv2_SetDelIkePeer) (CHAR *szIkePeerName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKEv2_SetPeerNATTraversal) (CHAR* szIkePeerName,
                            ULONG ulOpMode);
    METHOD_(ULONG, pfIKEv2_SetPeerIDType) (CHAR *szIkePeerName, ULONG ulIdType);
    METHOD_(ULONG, pfIKEv2_GetProductDefault) (
                            IKE_PRODUCT_VAL_S *pstIKEProdDefault);
    METHOD_(ULONG, pfIKEv2_SetAsInitiator) (ULONG ulOpMode);
    METHOD_(ULONG, pfIKEv2_SetDelReauthInterval) (ULONG ulProposalNum,
                            ULONG ulInterval, ULONG ulOpMode);
    METHOD_(ULONG, pfIKEv2_ClearAllIkev2SA) (VOID);
    METHOD_(ULONG, pfIKEv2_GetIKESABrief) (ULONG ulWaitListHandle,
                            IKE_SA_CONTENT_S **ppstIKESAContent,
                            ULONG *pulIKEv2SASum);
    METHOD_(ULONG, pfIKEv2_SetPrfNum) (ULONG ulProposalNum, ULONG ulPrfType);
    METHOD_(ULONG, pfIKEv2_OpenObjectSa) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKEv2_GetBulkSa) (ULONG ulWaitListHandle,
                            ULONG ulNumOfSAWanted, ULONG *pulNumOfSAReturn,
                            IKE_SA_CONTENT_S *pstSABuf, UCHAR ucPhase);
    METHOD_(ULONG, pfIKEv2_GetSAByConnID) (ULONG ulConID,
                            IKE_SA_CONTENT_S *pstSAContent);
    METHOD_(ULONG, pfIKE_SetDelProposalLevel) (ULONG ulProposalNum,
                            ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetProposalAuthMethod) (ULONG ulProposalNum,
                            ULONG ulAuthMethodType);
    METHOD_(ULONG, pfIKE_SetProposalEncrAlgorithm) (ULONG ulProposalNum,
                            ULONG ulEncryptionType);
    METHOD_(ULONG, pfIKE_SetProposalAuthAlgorithm) (ULONG ulProposalNum,
                                                   ULONG ulAuthAlgorithmType);
    METHOD_(ULONG, pfIKE_SetProposalDHGroup) (ULONG ulProposalNum,
                            ULONG ulDHGroupType);
    METHOD_(ULONG, pfIKE_SetISAKMPSALife) (ULONG ulProposalNum,
                            ULONG ulLifeTime, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelLocalID) (CHAR *szLocalId, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetPeerProposalNum) (CHAR *szIkePeerName,
                                        ULONG ulProposalNum, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetCurSAValue) (ULONG ulCurValue);
    METHOD_(ULONG, pfIKE_GetAllProposalName) (ULONG **ppulIKEProposalNum,
                            ULONG *pulProposalSum);
    METHOD_(ULONG, pfIKE_GetAllProposalStructure) (
                            IKE_PROPOSAL_CONTENT_S **ppstProposalContent,
                            ULONG *pulProposalSum);
    METHOD_(ULONG, pfIKE_GetProposalByNumber) (ULONG ulIKEProposalNum,
                            IKE_PROPOSAL_CONTENT_S *pstIKEProposalContent);
    METHOD_(ULONG, pfIKE_SetDelPreSharedKey) (CHAR *szIkePeerName,
                            CHAR *szKeyName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelRemoteName) (CHAR *szIkePeerName,
                            CHAR *szRemoteName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelPeerAddress) (CHAR *szIKEPeerName,
                            ULONG ulIpAddress, ULONG ulEndIpAddress,
                            CHAR *szVPNName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_GetPeerInfoByName) (CHAR *szPeerName,
                                          IKE_PEER_CONTENT_S *pstPeerContent);
    METHOD_(ULONG, pfIKE_GetTotalNumberOfPeers) (ULONG *pulPeerSum);
    METHOD_(ULONG, pfIKE_GetPeerName) (CHAR (*pucPeerName)[IKE_PEER_NAME_MAX_LEN],
                                  ULONG ulBeginIndex, ULONG ulNumber,
                                  ULONG *pulActualNumber);
    METHOD_(ULONG, pfIKE_ClearSA) (ULONG ulConnectionID, CHAR *szIfname);
    METHOD_(ULONG, pfIKE_ClearAllSA) (VOID);

    METHOD_(ULONG, pfIKE_GetLocalID) (CHAR *pucLocalID);
    METHOD_(ULONG, pfIKE_SetReset_Debug) (ULONG ulNoFlag, ULONG ulType);
    METHOD_(ULONG, pfIKE_OpenObject_Proposal) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_Proposal) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkProposal) (ULONG ulWaitListHandle,
                                      ULONG ulNumOfProposalWanted,
                                      ULONG *pulNumOfPropReturn,
                                      IKE_PROPOSAL_CONTENT_S *pstProposalBuf);
    METHOD_(ULONG, pfIKE_OpenObject_Peer) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_Peer) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkPeer) (ULONG ulWaitListHandle,
                            ULONG ulNumOfPeerWanted,
                            ULONG *pulNumOfPeerReturn,
                            IKE_PEER_CONTENT_S *pstPeerBuf);

    METHOD_(ULONG, pfIKE_GetGlobalInfo) (
                            IKE_GLOBAL_CONTENT_S *pstIKEGlobalContent);
    METHOD_(ULONG, pfIKE_GetStats) (IKE_STATS_CONTENT_S *pstIKEStatsContent);
    METHOD_(ULONG, pfIKE_ShowDebuggingAPI) (ULONG *pulDbgFlg);
    METHOD_(ULONG, pfIKE_GetProductDefault) (
                            IKE_PRODUCT_VAL_S *pstIKEProdDefault);
    METHOD_(ULONG, pfIKE_ClearAllPhase1Phase2SA) (VOID);

    METHOD_(ULONG, pfIKE_SetResetDpd) (CHAR *szIkePeerName,
                            IKE_DPD_CFG_S *pstDpdCfg);
    METHOD_(ULONG, pfIKE_EnableDisableDpd) (CHAR *szIkePeerName,
                            IKE_DPD_EN_CFG_S *pstDpdCfg);
    METHOD_(ULONG, pfIKE_SetPeerIDKeyID) (CHAR *szIkePeerName,UCHAR *szGrpName);
    METHOD_(ULONG, pfIKE_SetDelModeCfg) (CHAR *szIkePeerName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_DisplayModeCfgAddresses) (UCHAR *pucPeerName,
                            IKE_ADDR_CONTENT_S *pstData);
    METHOD_(ULONG, pfIKE_CloseObject_SA) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKEv2_SetIDType) (CHAR *szIkePeerName, ULONG ulIdType);
    METHOD_(ULONG, pfIKEv2_SetReset_Debug)(ULONG ulNoFlag, ULONG ulType);
    METHOD_(ULONG, pfIKEv2_SetGlobal)(ULONG ulFlag, ULONG ulValue);
    METHOD_(ULONG, pfIKE_SetDelNatKeepaliveInterval)(ULONG ulInterval,
                                                     ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetSockPriority)(UCHAR ucOpmode, ULONG ulPriorityLevel);
    METHOD_(ULONG, pfIKE_GetSockPriority)();

    /* Sumangala : Added for New API requirement from SGSN */
    METHOD_(ULONG, pfIKE_ClearPh1Ph2ByPeerAddress)(ULONG ulPeerIpAddress,
                                                   ULONG ulNotify);

    METHOD_(ULONG, pfIKEv2_ClearPh1Ph2ByPeerAddressSync)(ULONG ulPeerIpAddress);

    METHOD_(ULONG, pfIKE_Config_Peer) (IKE_PEER_CONFIG_S *pstIkePeerConfig);
    METHOD_(ULONG, pfIKE_Get_Peer) (CHAR * szIkePeerName,
                                            IKE_PEER_CONFIG_S * pstIkePeer);
    METHOD_(ULONG, pfIKE_Config_Peer_Dpd) (IKE_DPD_CONFIG_S * pstIkeDpdConfig);
    METHOD_(ULONG, pfIKE_Get_Peer_Dpd) (CHAR * szIkePeerName,
                                        IKE_DPD_CONFIG_S * pstIkeDpdConfig);
    METHOD_(ULONG, pfIKE_Config_Peer_Xauth) (
                                        IKE_XAUTH_CONFIG_S * pstIkeXauthConfig);
    METHOD_(ULONG, pfIKE_Get_Peer_Xauth) (CHAR * szIkePeerName,
                                    IKE_XAUTH_CONFIG_S * pstIkeXauthConfig);
    METHOD_(ULONG, pfIKE_Config_Proposal) (
                            IKE_PROPOSAL_CONFIG_S * pstIkeProposal);
    METHOD_(ULONG, pfIKE_Get_Proposal) (ULONG ulProposalNum,
                                    IKE_PROPOSAL_CONFIG_S * pstIkeProposal);
    /* Anoop_VPN    */
    METHOD_(ULONG, pfIKE_BindSaVPN) (CHAR *szIkePeerName, CHAR *szVPNName,
                                        ULONG ulOpMode);
    /*Sunil: IKE packet trace*/
    METHOD_(ULONG, pfIKE_EnableDisablePacketTrace)(ULONG ulSetReset);

    /*Defect AC4D07275 IKE stats*/
    METHOD_(ULONG, pfIKE_GetMsgStats)(IKE_MSG_STAT_S *pstMsgStat);
    METHOD_(ULONG, pfIKE_DeleteMsgStats)();

    METHOD_(ULONG, pfIKE_CmnSetPeerLocalAddr) (CHAR *szInputIkePeerName,
                                ULONG ulLocalAddr, ULONG ulOpMode);

    METHOD_(ULONG, pfIKE_PKI_SetResetPkiObj) (CHAR *szInputIkePeerName, CHAR *pszObj,
                                        ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_PKI_SetResetIdentityValidation) (CHAR *szInputIkePeerName,
                                                        ULONG ulOpMode);
    METHOD_(ULONG, pfIKEv2_SetResetUrlSupport) (CHAR *szInputIkePeerName,
                                                ULONG ulOpMode, ULONG ulUrlOnly);
    METHOD_(ULONG, pfIKE_PKI_SetResetUseDefaultCert) (CHAR *szInputIkePeerName,
                                                    ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_PKI_CheckObjectIsInUse) (CHAR *pszObjectName);

    METHOD_(ULONG, pfIKEv2_GetSendNotifyStatistics) (CHAR *pszPeerName,
                                    IKEV2_NOTIFY_STAT_S *pstNotifyStat);

    METHOD_(ULONG, pfIKEv2_GetRecvNotifyStatistics) (CHAR *pszPeerName,
                                    IKEV2_NOTIFY_STAT_S *pstNotifyStat);
    METHOD_(ULONG, pfIKE_PKI_GetPkiStatistics) (IKE_PKI_STAT_S *pstPkiStat);
    METHOD_(ULONG, pfIKE_PKI_ResetPkiStatistics) ();
    /* Added new APIs  */
    METHOD_(ULONG, pfIKE_GetObjectNameByPeer)  (CHAR *pszPeerName, CHAR *pszObjName);
    METHOD_(ULONG, pfIKEv2_GetDefaultValues) (IKEV2_DEFAULT_S *pstIKEv2Default);

    /* IPSEC6_Changes Story 10 */
    METHOD_(ULONG, pfIKE_ResetPeerDpdStat)(CHAR *pszPeerName);

    /*Iteration2: Story12: Maintainance*/
    METHOD_(VOID, pfIKE_GetPfkeyv2Stats)(IKE_PFKEYV2_STATS_S *pstStats);
    METHOD_(VOID, pfIKE_GetPfkeyv2FailStats)(
                        IKE_PFKEYV2_FAIL_STATS_S *pstFailStats);
    METHOD_(VOID, pfIKE_ResetPfkeyv2Stats)();

    METHOD_(ULONG, pfIKE_PKI_SetResetInBandExchange) (CHAR *szInputIkePeerName,
                                        ULONG ulType, ULONG ulOpMode);
    /* AP-REQ: Validate Peer auth method */
    METHOD_(ULONG, pfIKE_SetDelRemoteAuthMethod) (CHAR *szInputIkePeerName,
                                   ULONG ulRemoteAuthMethod, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_ClearSAByPeerName) (CHAR *pszIkePeerName, ULONG ulNotifyFlag);
    /*SGSN License implementation - B511*/
    METHOD_(ULONG, pfIKE_EnableDisableLicense) (ULONG ulLicenseFlag);
    METHOD_(ULONG, pfIKE_GetLicenseStatus) (VOID);
    METHOD_(ULONG, pfIKE_GetPeerNameByConnID)(ULONG ulConnId, UCHAR *szPeerName);
    METHOD_(ULONG, pfIKE_CmnEnableDisableDhHwApis) (ULONG ulEnable,
                                IKE_DH_HW_REG_FUNC *pstDHHwRegFuncs);
    METHOD_(VOID, pfIKE_CMN_DH1PoolInit) (ULONG ulEnable,  ULONG ulPoolSize);
    METHOD_(VOID, pfIKE_CMN_DH2PoolInit) (ULONG ulEnable,  ULONG ulPoolSize);

    /*Kuldeep : B513 Changes*/

    /*SGSN CR:201002270076 Delete SA's by IP address and VRF Name*/
    METHOD_(ULONG, pfIKE_ClearSAByPeerAddrAndVRFName) (ULONG ulIpAddr, CHAR *pszVRFName,
                                    ULONG ulPhase, ULONG ulNotify);

    /*Kuldeep : B514 Changes*/
    METHOD_(ULONG, pfIKE_RegisterGetLocalIDForPeerFunc_Callback) (
                       IKE_RegFuncGetPeerID_HOOK_FUNC pfFunc);

    /*B515 LTE Peer ID type control, support */
    METHOD_(ULONG, pfIKE_SetIDType) (CHAR *szInputIkePeerName, ULONG ulIdType);
    METHOD_(ULONG, pfIKEv2_StartReauth) (UCHAR *pucPeerName,
                                                        ULONG ulHardTimeOut);

    METHOD_(ULONG, pfIKEv2_SetResetSupportedAlgorithm)(
                                IKEV2_SA_PARAM_S *pstSaParam, ULONG ulOpMode);

    METHOD_(ULONG, pfIKEv2_GetSupportedAlgorithm)(
                                                IKEV2_SA_PARAM_S *pstSaParam);

    METHOD_(ULONG, pfIKE_SetDelPeerUseAllSupportedAlgs)(
                                    CHAR* szInputIkePeerName, ULONG ulOpMode);

    METHOD_(ULONG, pfIKE_SetDelPeerLifeTime)(CHAR* szInputIkePeerName,
                                                ULONG ulTime, ULONG ulOpMode);

    METHOD_(ULONG, pfIKEv2_SetDelPeerReauthLifeTime) (CHAR* szInputIkePeerName,
                                                ULONG ulTime, ULONG ulOpMode);

    METHOD_(ULONG, pfIKE_SetDelPeerPriorityAuthMethod)
                (CHAR *szInputIkePeerName, ULONG ulAuthMethod);

     /*PKI alarm for CERT expiration*/
    METHOD_(ULONG, pfIKE_GetPeerIpByConnID)
                                        (ULONG ulConnId, ULONG *pulPeerIpAddr);
    METHOD_(ULONG, pfIKE_SetMaxPeerProposalNum) (ULONG ulMaxPeerNum,
                    ULONG ulMaxPropNum, ULONG ulMaxSaNum);

    /* B045 : Added API to get ready state SA conn-id for IKEv1/IKEv2 phase-1 SA */
    METHOD_(ULONG, pfIKE_GetSAConnIDByPeerName) (UCHAR *pucPeerName, ULONG *pulConnID);

    /*B057: key deletion from IKE/IPSEC after SA establishment*/
    METHOD_(ULONG, pfIKE_EnableKeyDeletion) (ULONG ulOpMode);
    /*B058: stats improvement for IKEv2 message exchange*/
    METHOD_(ULONG, pfIKE_GetIKEV2ExchStats) (IKE_V2EXCHANGE_STATS_S *pstIkev2ExchStat);
    METHOD_(ULONG, pfIKE_DeleteIKEv2ExchStats) ();

    /* Iteration-3 Ipv6 compatability modification*/
    METHOD_(ULONG, pfIKE_ClearAllSAByAddrType)(UCHAR ucIPVersion);

    METHOD_(ULONG, pfIKE_GetBulkPeerByVersion)(ULONG ulWaitListHandle,
                    ULONG ulNumOfPeerWanted, ULONG *pulNumOfPeerReturn,
                    IKE_PEER_CONTENT_S *pstPeerBuf,  UCHAR ucIPVersion);

    /*Ipv6: Security Support*/
    METHOD_(ULONG, pfIKE6_ClearPh1Ph2ByPeerAddress)(
                                       IN6ADDR_S *pstIPv6Address, ULONG ulNotify);

    METHOD_(ULONG, pfIKE6_SetDelIkePeer)(CHAR *szIkePeerName,
                        ULONG ulOpMode, ULONG ulVersion);
    METHOD_(ULONG, pfIKE6_CmnSetPeerLocalAddr) (CHAR *szInputIkePeerName,
                            IN6ADDR_S *pstLocalV6Address, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE6_SetDelPeerAddress) (CHAR *szIkePeerName,
                            IN6ADDR_S *pstIPv6InputAddr, ULONG ulOpMode);

    METHOD_(ULONG, pfIKE_Ipv6RegisterAndInit) (ULONG (*pfRegisterIpv6ForIke)(
                                                            ULONG), ULONG);

    /*GGSN*/
    METHOD_(ULONG, pfIKE_CmnPacketInput) (IKE_PACKET_INFO_S *pstPktInfo,
                                        UCHAR *pucMsgBuf, ULONG  ulMsgBufLen);
    METHOD_(ULONG, pfIKE_IPSEC_CmnRegisterGgsnCbk)
                                    (CMN_GGSN_API_CALLBACK_S *g_pstGgsnCbk);
    METHOD_ (ULONG, pfIKE_DelSaAfterTimeout) (ULONG ulConnectionID,
                UCHAR *pucIKEInitSpi, UCHAR *pucIKERespSpi,
                UCHAR ucInitAndRespSpiLen, ULONG ulTimeout);

    METHOD_(ULONG, pfIKEv2_GetBulkSaByType)(ULONG ulWaitListHandle,
                        ULONG ulNumOfSAWanted, ULONG *pulNumOfSAReturn,
                        IKE_SA_CONTENT_S *pstSABuf, UCHAR ucPhase, IKE_DISPLAY_TYPE_S *pstDispType, UCHAR ucIPVer);

    METHOD_(ULONG, pfIKE_CmnSetResetGlobalAuthMethod) (UCHAR ucAuthMethod,
                                                        UCHAR ucOpMode);

    METHOD_(ULONG, pfIKEv2_SetEAPServerTimeout) (USHORT usTimeout);

    METHOD_(ULONG, pfIKE_CmnSetResetPeerAuthDomain) (CHAR *pszPeerName,
                                            CHAR *pszAuthDomain, UCHAR ucOpMode);

    METHOD_(ULONG, pfIKE_PROF_GetBulkSAByProfile) (ULONG ulWaitListHandle, ULONG ulNumOfSAWanted,
                                               ULONG *pulNumOfSAReturn, IKE_SA_CONTENT_S *pstSABuf,
                                               UCHAR ucPhase, CHAR *pszProfileName);

    METHOD_(ULONG, pfIKE_PROF_GetBulkSpokePeer)(ULONG ulWaitListHandle,
                       ULONG ulNumOfPeerWanted, ULONG *pulNumOfPeerReturn,
                       IKE_SPOKE_PEER_CONTENT_S *pstPeerBuf, UCHAR* pucProfileName, UCHAR ucIPVersion);
    METHOD_(ULONG, pfIKE_DNSReturnResolvedIP)(CHAR *pszFQDN, ULONG *pulIpAddr, ULONG ulNumOfAddress, VOID *pvHandle);
    METHOD_(ULONG, pfIKE_SetDelPeerFQDN)(UCHAR *pucIkePeerName, UCHAR *pucRemoteName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_IPSEC_RegisterSPLFeatureCbk) (IKE_IPSEC_SPLFEATURECBK *pstCbk);
    METHOD_(ULONG, pfIKE_GetSplStats)(IKE_IPSEC_SPLFEATURESTAT *pstSplStats);
    METHOD_(VOID *, pfIKEv2_GetSAByPkiObj)(VOID *pstObj);
    METHOD_(ULONG, pfIKE_SetDelOCSPServerTimeout)(ULONG ulTimeOut, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelModeCfgServerTimeout)(USHORT usTimeOut, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE6v2_GetBulkSa) (ULONG ulWaitListHandle,
                            ULONG ulNumOfSAWanted, ULONG *pulNumOfSAReturn,
                            IKE_SA_CONTENT_S *pstSABuf, UCHAR ucPhase);
    METHOD_(ULONG, pfIKE6v2_ClearPh1Ph2ByPeerAddressSync)(IN6ADDR_S *pstIPv6Address);
    /* Added for EasyVPN */
    METHOD_(ULONG, pfIKEv2_SetDelDefaultEzVpnIkePeer) (CHAR *szIkePeerName, ULONG ulOpMode);

    METHOD_(ULONG, pfIKE6_SetSockPriority)(UCHAR ucOpmode, ULONG ulPriorityLevel);
    METHOD_(ULONG, pfIKE6_GetSockPriority)();
    METHOD_(ULONG, pfIKE6_GetPeerIpByConnID)(ULONG ulConnId, IN6ADDR_S *pstPeerIpAddr);

    /*B054: Crypt sign*/
    METHOD_(ULONG, pfIKE_RegisterPkiCryptSignFunc_Callback)
                (IKE_SHELL_CALLBACK_PKI_CRYPT_SIGN_S *pstIkeCallbackPKICryptSign);

    /* Juniper-PnP interop. API for setting priority of the IKE Proposal in IKEv2 */
    METHOD_(ULONG, pfIKEv2_SetPropPriority) (IKE_PROP_PRIO_S *pstIkePropPri, ULONG ulNumIkeProp, ULONG ulOpMode);
    METHOD_(ULONG, pfIKEv2_ShowPropPriority) (ULONG ulNumOfPropWanted, ULONG *pulNumOfPropReturn,
                                                IKE_PROP_PRIO_S *pstPropBuf);

    /* Multi-SeGw Feature */
    METHOD_(ULONG, pfIKE_SetResetLocalBackupPeer)(UCHAR *pucPeerName, UCHAR ucIsLocalPeer,
                                                UCHAR *pucMasterPeerName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_StartNegotiation)(UCHAR *pucPeerName, UCHAR ucPeerType);
    METHOD_(ULONG, pfIKE_StopNegotiation)(UCHAR *pucPeerName, UCHAR ucPeerType);
    METHOD_(ULONG, pfIKE_SetSwitchBack)(UCHAR *pucPeerName, UCHAR ucFlag);
    
	/* HERT3.3 : DH Support in HW */
    METHOD_(ULONG, pfIKE_CmnRegisterHWAPIs)(IKE_DH_HW_CBK_S *pstHwRegAPIs);
};


/* IKEv2 Component Functional interface */
DECLARE_INTERFACE (IIF_IKEv2_ComIntFun)
{
    IUNKNOWN_METHODS

    /* LOOP_OPT */
    METHOD_(ULONG, pfIKEv2_SALookupByConnid) (ULONG conn_id,
                                            IKE_SA_PORT_S *pstIkeSA);
    METHOD_(ULONG, pfIKE_SearchIKEPeer) (UCHAR *pPeerName,
                                         IKE_PEER_CONTENT_S  *pstIkePeer,
                                         ULONG ulTaskLock);

    METHOD_(ULONG, pfIKE_GET_CFG_Attributes) (IKE_GET_ATTR_S *pstGetAttr,
                                           IKE_PRODUCT_NOTIFY_S *pstAttrData);

    METHOD_(ULONG, pfIKE_UnReg_CFG_Attr_Notify_Func) (ULONG ulHandle);
    METHOD_(ULONG, pfIKEv2_NotifyFromEAP) (UCHAR *pucEAPMsg,
                                         ULONG ulMsgLength,
                                         ULONG ulConnId,
                                         ULONG ulTimeOut);
    METHOD_(ULONG, pfIKEv2_EapComplete) (ULONG ulConn_id,
                                        ULONG ulEAPresult);

    METHOD_(ULONG, pfIKEv2_RegPacketHook)(IKE_GetAppControlPacket_HOOK_FUNC pfHookFunc);

    METHOD_(ULONG, pfIKE_PKI_CertDownloadComplete) (ULONG ulReqIdentifer,
                                                    ULONG ulFlag,
                                                    UCHAR *pucCertBuf,
                                                    ULONG ulCertLen);

    METHOD_(ULONG, pfIKE_PKI_CRLDownloadComplete) (ULONG ulReqIdentifier,
                                                    ULONG ulFlag);

    /* AC4D07928 [B116] : Support Tunnel UP/DOWN notification */
    METHOD_(ULONG, pfIKE_RegisterTunnelStatus_Callback) (
                                        IKE_TUNNEL_STATUS_CALLBACK pfFuncPtr);

    /* IPSEC6.STORY.04 - Removal of Pfkey socket */
    METHOD_(ULONG, pfIKE_ExtWritePfkeyEventToIKETask) (ULONG ulMsgType,
                                                 ULONG ulData, ULONG ulEvType);

    /*Added for Warning messages in IPOS.*/
    METHOD_(ULONG, pfIKE_cmn_RegisterWarningAPI)(pfIKE_WarningOut pfFunc);


    /*SGSN License implementation - B511*/
    METHOD_(ULONG, pfIKE_GetLicenseStatus_Callback) (
                         IPSECIKE_GET_LICENSE_STATE_CALLBACK_FUNC pfFunc);

    /*AP : Allowing duplicate remote name in different peers*/
    METHOD_(ULONG, pfIKE_RegisterDuplicateRemoteNameCallback) (
                       IKE_DUPLICATE_REMOTE_NAME pfFunc);

    METHOD_(ULONG, pfIKE_PKI_CertStatusDownloadComplete) (VOID *pstPKIObject, ULONG ulErrorFlag,
                                                    ULONG ulAppData);


    METHOD_(ULONG, pfIKEv2_GenericEapComplete) (IKE_AAA_ID_INFO_S *pstIDInfo,
                                ULONG ulEAPResult, ULONG ulMskLength,
                                UCHAR *pucMSK, ULONG ulMskLifeTime);

    METHOD_(ULONG, pfIKEv2_GenericNotifyFromEAP) (IKE_AAA_ID_INFO_S *pstIDInfo,
                                    ULONG ulMsgLength, UCHAR *pucEAPMsg,
                                    ULONG ulTimeOut);

    METHOD_(ULONG, pfIKE_SetModeCFGAttributes) (IKE_AAA_ID_INFO_S *pstIDInfo,
                                            IKE_AAA_MODECFG_ATTR_S *pstModeCfgAttr);

    /*GGSN:DPD-DEFECTFIXES*/
    METHOD_(ULONG, pfIKEv2_DelSaAfterTimeout) (ULONG ulConnectionID,
                UCHAR *pucIKEInitSpi, UCHAR *pucIKERespSpi, UCHAR ucSpiLen,
                ULONG ulTimeout);

    /*Added for ipsec-profile support*/
    METHOD_(ULONG, pfIKE_PROF_CreateDelIKEPeer)(UCHAR *pszProfileName, UCHAR *pucProfPeerName,
                                                ULONG ulProfileID, ULONG ulLocalAddr,
                                                ULONG ulPeerAddress, ULONG ulVrfIndex,
                                                UCHAR *pucNewPeerName, ULONG ulOpMode);

    /*Added for ipsec-profile deletespoke support*/
    METHOD_(ULONG, pfIKE_ClearPh1Ph2ByPeerAddress)(ULONG ulPeerIpAddress, ULONG ulNotify);


    /*get IfIndex by peer IP address*/
    METHOD_(ULONG, pfIKE_PROF_GetProfileIdByIPAddr)(ULONG ulDestAddress, ULONG *pulProfileID);

    METHOD_(ULONG, pfIKE_CmSearchSAByPeerAddressAndVrf) (ULONG ulPeerAddress, ULONG ulVrfIndex);

    METHOD_(ULONG, pfIKEv2_ClearPh1Ph2ByVrfPeerAddressSync) (ULONG ulPeerIpAddress, ULONG ulVrfIndex);
    METHOD_(ULONG, pfIKE_CmnSetResetSupportedIPSecAlg)(VOID *pvPropParam,
                                                    ULONG ulOpMode);
    METHOD_(VOID, pfIKE_CmnGetSupportedIPSecAlgorithms)(VOID *pvPropParam);
    METHOD_(ULONG, pfIKE_PROF_DynamicUpdateByProfID) (UCHAR *szPeerName, ULONG ulProfileID, ULONG ulProfPeerUpdateType, UCHAR ucUpdateTdb);
    METHOD_(ULONG, pfIKE_CmnResolveFQDN)(UCHAR *pucPeerName);

    /* Added for EasyVPN */
    METHOD_(ULONG, pfIKE_EasyVPN_GetDefaultPeerName) (UCHAR *pucPeerName, ULONG ulIkeVersion);
    METHOD_(ULONG, pfcheck_ike_peer_addr_conflict) (VOID *pvIkepeer,
                                                    VOID *pvRemoteAddr1, VOID *pvRemoteAddr2,
                                                    ULONG ulVrfIndex);

    METHOD_(ULONG, pfIKE_CheckFqdnConflict) (UCHAR *pucRemoteName);
};


DECLARE_INTERFACE (IIF_IKEv1v2_ComIntCFG)
{
    IUNKNOWN_METHODS

/*------------------------------------------------------------------------
    IKEv1 Component configuration functions
------------------------------------------------------------------------*/
    METHOD_(ULONG, pfIKE_SetDelProposalLevel)(ULONG ulProposalNum,
                                              ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetProposalAuthMethod)(ULONG ulProposalNum,
                                                ULONG ulAuthMethodType);
    METHOD_(ULONG, pfIKE_SetProposalEncrAlgorithm)(ULONG ulProposalNum,
                                                   ULONG ulEncryptionType);
    METHOD_(ULONG, pfIKE_SetProposalAuthAlgorithm)(ULONG ulProposalNum,
                                                   ULONG ulAuthAlgorithmType);
    METHOD_(ULONG, pfIKE_SetProposalDHGroup)(ULONG ulProposalNum,
                                             ULONG ulDHGroupType);
    METHOD_(ULONG, pfIKE_SetISAKMPSALife)(ULONG ulProposalNum,
                                          ULONG ulLifeTime, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelLocalID)(CHAR* pucLocalId,
                                        ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelIkePeer_Wrapper)(CHAR* pucIkePeerName,
                                        ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetPeerNATTraversal_Wrapper)(CHAR* pucIkePeerName,
                                              ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetPeerExchangeMode_Wrapper)(CHAR * pucIkePeerName,
                                              ULONG ulExchangeMode);
    METHOD_(ULONG, pfIKE_SetPeerIDType_Wrapper)(CHAR * pucIkePeerName,
                                                ULONG ulIdType);
    METHOD_(ULONG, pfIKE_SetPeerProposalNum)(CHAR * pucIkePeerName,
                                             ULONG ulProposalNum,
                                             ULONG ulOpMode);
    /* Defect AC4D03031: Added new API */
    METHOD_(ULONG, pfIKE_SetCurSAValue) (ULONG ulCurValue);
    METHOD_(ULONG, pfIKE_GetAllProposalName) (ULONG **ppulIKEProposalNum,
                                              ULONG *pulProposalSum);
    METHOD_(ULONG, pfIKE_GetAllProposalStructure) (
                                IKE_PROPOSAL_CONTENT_S **ppstProposalContent,
                                ULONG *pulProposalSum);
    METHOD_(ULONG, pfIKE_GetProposalByNumber) (ULONG ulIKEProposalNum,
                                IKE_PROPOSAL_CONTENT_S *pstIKEProposalContent);
    METHOD_(ULONG, pfIKE_SetDelPreSharedKey) (CHAR *pucIkePeerName,
                                              CHAR *pucKeyName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelRemoteName)(CHAR *pucIkePeerName,
                                           CHAR *pucRemoteName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelPeerAddress) (CHAR *pucIKEPeerName,
                                        ULONG ulIpAddress, ULONG ulEndIpAddress,
                                        CHAR *pucVPNName, ULONG ulOpMode);
    /* Anoop_VPN    */
    METHOD_(ULONG, pfIKE_BindSaVPN) (CHAR *szIkePeerName, CHAR *szVPNName,
                                        ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_GetPeerInfoByName)(CHAR* pucIkePeerName,
                                            IKE_PEER_CONTENT_S* pstPeerContent);
    METHOD_(ULONG, pfIKE_GetTotalNumberOfPeers) (ULONG *pulPeerSum);
    METHOD_(ULONG, pfIKE_GetPeerName) (
                CHAR (*pucPeerName)[IKE_PEER_NAME_MAX_LEN], ULONG ulBeginIndex,
                ULONG ulNumber, ULONG * pulActualNumber);
    METHOD_(ULONG, pfIKE_GetSAByConnID_Wrapper)(ULONG ulConID,
                                        IKE_SA_CONTENT_S *pstSAContent);
    METHOD_(ULONG, pfIKE_SetDelKeepaliveInterval_Wrapper)(ULONG ulInterval,
                                                  ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelKeepaliveTimeout_Wrapper)(ULONG ulTimeout,
                                                 ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelNatKeepaliveInterval)(ULONG ulInterval,
                                                     ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_ClearSA)(ULONG ulConnectionID, CHAR *szIfname);
    METHOD_(ULONG, pfIKE_ClearAllSA)(VOID);

    METHOD_(ULONG, pfIKE_GetIKESABrief_Wrapper) (ULONG ulWaitListHandle,
                                         IKE_SA_CONTENT_S **ppstIKESAContent,
                                         ULONG *pulIKESASum);

    METHOD_(ULONG, pfIKE_GetLocalID)(CHAR *pucLocalID);
    METHOD_(ULONG, pfIKE_GetKeepaliveInterval_Wrapper)(ULONG* pulInterval);
    METHOD_(ULONG, pfIKE_GetKeepaliveTimeout_Wrapper)(ULONG* pulTimeout);
    METHOD_(ULONG, pfIKE_GetNatKeepaliveInterval_Wrapper)(ULONG* pulNatInterval);
    METHOD_(ULONG, pfIKE_SetReset_Debug) (ULONG ulNoFlag, ULONG ulType);
    METHOD_(ULONG, pfIKE_OpenObject_Proposal) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_Proposal) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkProposal)(ULONG ulWaitListHandle,
                    ULONG ulNumOfProposalWanted, ULONG *pulNumOfPropReturn,
                    IKE_PROPOSAL_CONTENT_S  *pProposalBuf);
    METHOD_(ULONG, pfIKE_OpenObject_Peer) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_Peer) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkPeer)(ULONG ulWaitListHandle,
                    ULONG ulNumOfPeerWanted, ULONG *pulNumOfPropReturn,
                    IKE_PEER_CONTENT_S *pPeerBuf);

    METHOD_(ULONG, pfIKE_OpenObject_SA_Wrapper) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_SA) (ULONG *pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkSA_Wrapper)(ULONG ulWaitListHandle,
                    ULONG ulNumOfSAWanted, ULONG *pulNumOfPropReturn,
                    IKE_SA_CONTENT_S *pSABuf, UCHAR ucPhase);

    METHOD_(ULONG, pfIKE_OpenObject_Exchange_Wrapper)(ULONG * pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_Exchange_Wrapper)(ULONG * pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkExchange_Wrapper)(ULONG ulWaitListHandle,
                    ULONG ulNumOfExchangeWanted, ULONG * pulNumOfExchangeReturn,
                    IKE_EXCHANGE_CONTENT_S * pstExchangeBuf);
    METHOD_(ULONG, pfIKE_OpenObject_Event)(ULONG * pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_Event)(ULONG * pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkEvent)(ULONG ulWaitListHandle,
                    ULONG ulNumOfEventWanted, ULONG * pulNumOfEventReturn,
                    IKE_EVENT_CONTENT_S * pstEventBuf);
    METHOD_(ULONG, pfIKE_OpenObject_Transport)(ULONG * pulWaitListHandle);
    METHOD_(ULONG, pfIKE_CloseObject_Transport)(ULONG * pulWaitListHandle);
    METHOD_(ULONG, pfIKE_GetBulkTransport)(ULONG ulWaitListHandle,
                                    ULONG ulNumOfTransportWanted,
                                    ULONG *pulNumOfTransportReturn,
                                    IKE_TRANSPORT_CONTENT_S * pstTransportBuf);
    METHOD_(ULONG, pfIKE_GetGlobalInfo) (
                                    IKE_GLOBAL_CONTENT_S *pstIKEGlobalContent);
    METHOD_(ULONG, pfIKE_GetStats) (
                                    IKE_STATS_CONTENT_S *pstIKEStatsContent);
    METHOD_(ULONG, pfIKE_SetHeartbeatSPIList_Wrapper) (ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_GetVersion_Wrapper) (CHAR *szVer);

    /* AC4D02681,Removed from macro pruining */
    METHOD_(ULONG, pfIKE_SetMaxDeleteSa) (ULONG ulRead);
    METHOD_(ULONG, pfIKE_SetMinHrtbtInt_Wrapper) (ULONG ulRead);
    METHOD_(ULONG, pfIKE_SetPfkeyReadInt) (ULONG ulRead);

    /* @@Gopa */
    METHOD_(ULONG, pfIKE_ShowDebuggingAPI)(ULONG *pulDbgFlg);
    METHOD_(ULONG, pfIKE_SetHeartbeatSeqNum_Wrapper) (UCHAR ucSeqNumType);

    METHOD_(VOID, pfIKE_HeartbeatTimeoutNegotiation_Wrapper) ();
    METHOD_(ULONG, pfIKE_GetProductDefault) (IKE_PRODUCT_VAL_S *pstIKEProd);
    METHOD_(ULONG, pfIKE_ClearAllPhase1Phase2SA)(VOID);

    METHOD_(ULONG, pfIKE_ResetStatistics)(VOID);
    METHOD_(ULONG, pfIKE_SetResetDpd)(CHAR *szPeerName,
                                      IKE_DPD_CFG_S *pstDpdCfg);
    METHOD_(ULONG, pfIKE_EnableDisableDpd)(CHAR *szPeerName,
                                           IKE_DPD_EN_CFG_S *pstDpdCfg);

    METHOD_(ULONG, pfIKE_SetPeerXauth_Wrapper)(CHAR *szIkePeerName,
                                UCHAR ucXauthMode, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetResetXauthType_Wrapper)(CHAR *szIkePeerName,
                                            UCHAR ucXauthType,
                                            ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetPeerXauthAttributes_Wrapper)(CHAR *szIkePeerName,
                                                IKE_XAUTH_ATTR_S *pstXauthAttr,
                                                ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetPeerXauthPasscode_Wrapper)(CHAR *szIkePeerName,
                                               UCHAR *szPasscode,
                                               ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetRChapHashSeq_Wrapper)(CHAR *szIkePeerName,
                                                    UCHAR ulHashSeq);
    METHOD_(ULONG, pfIKE_SetOtpPswdMode_Wrapper)(CHAR *szIkePeerName,
                                         UCHAR ulOTPPswdMode);
    METHOD_(ULONG, pfIKE_SetPeerIDKeyID)(CHAR *szPeerName, UCHAR *szGrpName);
    METHOD_(ULONG, pfIKE_SetDelModeCfg) (CHAR *szIkePeerName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_DisplayModeCfgAddresses)(UCHAR * pucPeerName,
                                                  IKE_ADDR_CONTENT_S *pstData);
    METHOD_(ULONG, pfIKE_SetModeCfgVID_Wrapper)(CHAR *szIkePeerName,
                                            UCHAR ucSetVID, UCHAR *pucVid);
    METHOD_(ULONG, pfIKE_SetDpdHashCalcSequence)(CHAR *szIkePeerName,
                                                UCHAR ucHashSeq);

    /* Juniper-PnP interop. API for setting priority of the IKE Proposal in IKEv2 */
    METHOD_(ULONG, pfIKEv1_SetPropPriority) (IKEV1_PROP_PRIO_S *pstIkePropPri, ULONG ulNumIkeProp, ULONG ulOpMode);

    METHOD_(ULONG, pfIKEv1_ShowPropPriority) (ULONG ulNumOfPropWanted, ULONG *pulNumOfPropReturn,
                                                IKEV1_PROP_PRIO_S *pstPropBuf);

    /* Sumangala : Added for New API requirement from SGSN */
    METHOD_(ULONG, pfIKE_ClearPh1Ph2ByPeerAddress)(ULONG ulPeerIpAddress,
                                                   ULONG ulNotify);

/*------------------------------------------------------------------------
    IKEv2 Component configuration functions
------------------------------------------------------------------------*/
    METHOD_(ULONG, pfIKEv2_ClearPh1Ph2ByPeerAddressSync)(ULONG ulPeerIpAddress);

    METHOD_(ULONG, pfIKEv2_SetDelIkePeer_v1v2) (CHAR *szIkePeerName,
                        ULONG ulOpMode, ULONG ulVersion);
    METHOD_(ULONG, pfIKEv2_SetAsInitiator) (ULONG ulOpMode);
    METHOD_(ULONG, pfIKEv2_SetDelReauthInterval) (ULONG ulProposalNum,
                        ULONG ulInterval, ULONG ulOpMode);
    METHOD_(ULONG, pfIKEv2_SetPrfNum) (ULONG ulProposalNum, ULONG ulPrfNum);
    METHOD_(ULONG, pfIKEv2_SetIDType) (CHAR *szIkePeerName, ULONG ulIdType);
    METHOD_(ULONG, pfIKE_SetSockPriority)(UCHAR ucOpmode, ULONG ulPriorityLevel);
    METHOD_(ULONG, pfIKE_GetSockPriority)();

    /*B500 - SGSN-CMD Registration*/
    METHOD_(ULONG, pfIKE_Config_Peer) (IKE_PEER_CONFIG_S *pstIkePeerConfig);
    METHOD_(ULONG, pfIKE_Get_Peer) (CHAR * szIkePeerName,
                                            IKE_PEER_CONFIG_S * pstIkePeer);
    METHOD_(ULONG, pfIKE_Config_Peer_Dpd) (IKE_DPD_CONFIG_S * pstIkeDpdConfig);
    METHOD_(ULONG, pfIKE_Get_Peer_Dpd) (CHAR * szIkePeerName,
                                        IKE_DPD_CONFIG_S * pstIkeDpdConfig);
    METHOD_(ULONG, pfIKE_Config_Peer_Xauth) (
                                        IKE_XAUTH_CONFIG_S * pstIkeXauthConfig);
    METHOD_(ULONG, pfIKE_Get_Peer_Xauth) (CHAR * szIkePeerName,
                                    IKE_XAUTH_CONFIG_S * pstIkeXauthConfig);
    METHOD_(ULONG, pfIKE_Config_Proposal) (
                            IKE_PROPOSAL_CONFIG_S * pstIkeProposal);
    METHOD_(ULONG, pfIKE_Get_Proposal) (ULONG ulProposalNum,
                                    IKE_PROPOSAL_CONFIG_S * pstIkeProposal);
    /*Sunil: IKE packet trace*/
    METHOD_(ULONG, pfIKE_EnableDisablePacketTrace)(ULONG ulSetReset);

    /*Defect AC4D07275 IKE stats*/
    METHOD_(ULONG, pfIKE_GetMsgStats)(IKE_MSG_STAT_S *pstMsgStat);
    METHOD_(ULONG, pfIKE_DeleteMsgStats)();

    /*Sunil: Source address for peer*/
    METHOD_(ULONG, pfIKE_CmnSetPeerLocalAddr)(CHAR *szInputIkePeerName,
                                ULONG ulLocalAddr, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_PKI_SetResetPkiObj) (CHAR *szInputIkePeerName, CHAR *pszObj,
                                        ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_PKI_SetResetIdentityValidation) (CHAR *szInputIkePeerName,
                                                        ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_PKI_SetResetUseDefaultCert) (CHAR *szInputIkePeerName,
                                                    ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_PKI_CheckObjectIsInUse) (CHAR *pszObjectName);
    METHOD_(ULONG, pfIKE_PKI_GetPkiStatistics) (IKE_PKI_STAT_S *pstPkiStat);
    METHOD_(ULONG, pfIKE_PKI_ResetPkiStatistics) ();
     /* Added new APIs  */
    METHOD_(ULONG, pfIKE_GetObjectNameByPeer)  (CHAR *pszPeerName, CHAR *pszObjName);
    METHOD_(ULONG, pfIKEv2_GetDefaultValues) (IKEV2_DEFAULT_S *pstIKEv2Default);
    METHOD_(ULONG, pfIKEv1_GetDefaultValues_Wrapper) (IKEV1_DEFAULT_S *pstIKEv1Default);

    /* IPSEC6_Changes Story 10 */
    METHOD_(ULONG, pfIKE_ResetPeerDpdStat)(CHAR *pszPeerName);

    /*Iteration2: Story12: Maintainance*/
    METHOD_(VOID, pfIKE_GetPfkeyv2Stats)(IKE_PFKEYV2_STATS_S *pstStats);
    METHOD_(VOID, pfIKE_GetPfkeyv2FailStats)(
                        IKE_PFKEYV2_FAIL_STATS_S *pstFailStats);
    METHOD_(VOID, pfIKE_ResetPfkeyv2Stats)();

    METHOD_(ULONG, pfIKE_PKI_SetResetInBandExchange) (CHAR *szInputIkePeerName,
                                        ULONG ulType, ULONG ulOpMode);
    /* AP-REQ: Validate Peer auth method */
    METHOD_(ULONG, pfIKE_SetDelRemoteAuthMethod) (CHAR *szInputIkePeerName,
                                   ULONG ulRemoteAuthMethod, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_ClearSAByPeerName) (CHAR *pszIkePeerName, ULONG ulNotifyFlag);
    /*SGSN License implementation - B511*/
    METHOD_(ULONG, pfIKE_EnableDisableLicense) (ULONG ulLicenseFlag);
    METHOD_(ULONG, pfIKE_GetLicenseStatus) (VOID);
    METHOD_(ULONG, pfIKE_CmnEnableDisableDhHwApis) (ULONG ulEnable,
                                IKE_DH_HW_REG_FUNC *pstDHHwRegFuncs);
    METHOD_(VOID, pfIKE_CMN_DH1PoolInit)(ULONG ulEnable,  ULONG ulPoolSize);
    METHOD_(VOID, pfIKE_CMN_DH2PoolInit)(ULONG ulEnable,  ULONG ulPoolSize);

    /*Kuldeep : B513 Changes*/

    /*SGSN CR:201002270076 Delete SA's by IP address and VRF Name*/
    METHOD_(ULONG, pfIKE_ClearSAByPeerAddrAndVRFName) (ULONG ulIpAddr, CHAR *pszVRFName,
                                        ULONG ulPhase, ULONG ulNotify);

    /*Kuldeep : B514 Changes*/
     METHOD_(ULONG, pfIKE_RegisterGetLocalIDForPeerFunc_Callback) (
                        IKE_RegFuncGetPeerID_HOOK_FUNC pfFunc);

    /*B515 LTE Peer ID type control, support */
     METHOD_(ULONG, pfIKE_SetIDType) (CHAR *szInputIkePeerName, ULONG ulIdType);

    METHOD_(ULONG, pfIKEv1_SetResetSupportedAlgorithm)
                (IKEV1_SA_PARAM_S *pstSaParam, ULONG ulOpMode);

    METHOD_(ULONG, pfIKEv1_GetSupportedAlgorithm)(IKEV1_SA_PARAM_S *pstSaParam);

    METHOD_(ULONG, pfIKEv2_SetResetSupportedAlgorithm)
                (IKEV2_SA_PARAM_S *pstSaParam, ULONG ulOpMode);

    METHOD_(ULONG, pfIKEv2_GetSupportedAlgorithm)(IKEV2_SA_PARAM_S *pstSaParam);

    METHOD_(ULONG, pfIKE_SetDelPeerUseAllSupportedAlgs)
                                    (CHAR* szInputIkePeerName, ULONG ulOpMode);

    METHOD_(ULONG, pfIKE_SetDelPeerLifeTime)(CHAR* szInputIkePeerName,
                                                ULONG ulTime, ULONG ulOpMode);

    METHOD_(ULONG, pfIKEv2_SetDelPeerReauthLifeTime) (CHAR* szInputIkePeerName,
                                                ULONG ulTime, ULONG ulOpMode);

    METHOD_(ULONG, pfIKE_SetDelPeerPriorityAuthMethod)
                (CHAR *szInputIkePeerName, ULONG ulAuthMethod);

     /*PKI alarm for CERT expiration*/
    METHOD_(ULONG, pfIKE_GetPeerIpByConnID)
                                        (ULONG ulConnId, ULONG *pulPeerIpAddr);
    METHOD_(ULONG, pfIKE_SetMaxPeerProposalNum) (ULONG ulMaxPeerNum,
                        ULONG ulMaxPropNum, ULONG ulMaxSaNum);

    /* B045 : Added API to get ready state SA conn-id for IKEv1/IKEv2 phase-1 SA */
    METHOD_(ULONG, pfIKE_GetSAConnIDByPeerName) (UCHAR *pucPeerName, ULONG *pulConnID);

    /*B057: key deletion from IKE/IPSEC after SA establishment*/
    METHOD_(ULONG, pfIKE_EnableKeyDeletion) (ULONG ulOpMode);
    /*B058: stats improvement for IKEv2 message exchange*/
    METHOD_(ULONG, pfIKE_GetIKEV2ExchStats) (IKE_V2EXCHANGE_STATS_S *pstIkev2ExchStat);
    METHOD_(ULONG, pfIKE_GetIKEV1ExchStats) (IKE_V1EXCHANGE_STATS_S *pstIkev1ExchStat);
    METHOD_(ULONG, pfIKE_DeleteIKEv2ExchStats) ();
    METHOD_(ULONG, pfIKE_DeleteIKEv1ExchStats) ();

    /* Iteration-3 Ipv6 compatability modification*/
    METHOD_(ULONG, pfIKE_ClearAllSAByAddrType)(UCHAR ucIPVersion);

    /*Ipv6: Security Support*/
    METHOD_(ULONG, pfIKE_GetBulkPeerByVersion)(ULONG ulWaitListHandle,
                   ULONG ulNumOfPeerWanted, ULONG *pulNumOfPeerReturn,
                   IKE_PEER_CONTENT_S *pstPeerBuf, UCHAR ucIPVersion);


    /*Ipv6: Security Support*/
    METHOD_(ULONG, pfIKE6_ClearPh1Ph2ByPeerAddress)(
                                    IN6ADDR_S *pstIPv6Address, ULONG ulNotify);

    METHOD_(ULONG, pfIKE6_SetDelIkePeer)(CHAR *szIkePeerName,
                        ULONG ulOpMode, ULONG ulVersion);
    METHOD_(ULONG, pfIKE6_CmnSetPeerLocalAddr) (CHAR *szInputIkePeerName,
                            IN6ADDR_S *pstLocalV6Address, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE6_SetDelPeerAddress) (CHAR *szIkePeerName,
                    IN6ADDR_S *pstIPv6InputAddr, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_Ipv6RegisterAndInit) (ULONG (*pfRegisterIpv6ForIke)(
                                                            ULONG), ULONG);

    /*GGSN*/
    METHOD_(ULONG, pfIKE_CmnPacketInput) (IKE_PACKET_INFO_S *pstPktInfo,
                                        UCHAR *pucMsgBuf, ULONG  ulMsgBufLen);
    METHOD_(ULONG, pfIKE_IPSEC_CmnRegisterGgsnCbk)
                                    (CMN_GGSN_API_CALLBACK_S *g_pstGgsnCbk);
    METHOD_ (ULONG, pfIKE_DelSaAfterTimeout) (ULONG ulConnectionID,
                UCHAR *pucIKEInitSpi, UCHAR *pucIKERespSpi,
                UCHAR ucInitAndRespSpiLen, ULONG ulTimeout);
    METHOD_(ULONG, pfIKE_CmnSetResetGlobalAuthMethod) (UCHAR ucAuthMethod,
                                                        UCHAR ucOpMode);
    METHOD_(ULONG, pfIKEv2_SetEAPServerTimeout) (USHORT usTimeout);

    METHOD_(ULONG, pfIKE_CmnSetResetPeerAuthDomain) (CHAR *pszPeerName,
                                            CHAR *pszAuthDomain, UCHAR ucOpMode);

    METHOD_(ULONG, pfIKE_PROF_GetBulkSAByProfile) (ULONG ulWaitListHandle, ULONG ulNumOfSAWanted,
                                               ULONG *pulNumOfSAReturn, IKE_SA_CONTENT_S *pstSABuf,
                                               UCHAR ucPhase, CHAR *pszProfileName);

    METHOD_(ULONG, pfIKE_PROF_GetBulkSpokePeer)(ULONG ulWaitListHandle,
                     ULONG ulNumOfPeerWanted, ULONG *pulNumOfPeerReturn,
                       IKE_SPOKE_PEER_CONTENT_S *pstPeerBuf, UCHAR* pucProfileName, UCHAR ucIPVersion);
    METHOD_(ULONG, pfIKE_DNSReturnResolvedIP)(CHAR *pszFQDN, ULONG *pulIpAddr, ULONG ulNumOfAddress, VOID *pvHandle);
    METHOD_(ULONG, pfIKE_SetDelPeerFQDN)(UCHAR *pucIkePeerName, UCHAR *pucRemoteName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_IPSEC_RegisterSPLFeatureCbk) (IKE_IPSEC_SPLFEATURECBK *pstCbk);
    METHOD_(ULONG, pfIKE_GetSplStats)(IKE_IPSEC_SPLFEATURESTAT *pstSplStats);
    METHOD_(ULONG, pfIKE_CheckContextusedbyPeer) (CHAR *szCtxName);
    METHOD_(ULONG, pfIKE_SetDelOCSPServerTimeout)(ULONG ulTimeOut, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_SetDelModeCfgServerTimeout)(USHORT usTimeOut, ULONG ulOpMode);

    METHOD_(ULONG, pfIKE6v2_ClearPh1Ph2ByPeerAddressSync)(IN6ADDR_S *pstIPv6Address);
    METHOD_(ULONG, pfIKE6_ClearPh1Ph2ByPeerAddressSync)(IN6ADDR_S *pstIPv6Address);

    METHOD_(ULONG, pfIKE6_SetSockPriority)(UCHAR ucOpmode, ULONG ulPriorityLevel);
    METHOD_(ULONG, pfIKE6_GetSockPriority)();
    METHOD_(ULONG, pfIKE_GetPeerNameByConnID)(ULONG ulConnId, UCHAR *szPeerName);
    METHOD_(ULONG, pfIKE6_GetPeerIpByConnID)(ULONG ulConnId, IN6ADDR_S *pstPeerIpAddr);
    METHOD_(ULONG, pfIKE_QuickModeDrop)(ULONG ulOpMode);
    /*B054: Crypt sign*/
    METHOD_(ULONG, pfIKE_RegisterPkiCryptSignFunc_Callback)
                (IKE_SHELL_CALLBACK_PKI_CRYPT_SIGN_S *pstIkeCallbackPKICryptSign);

    /* Multi-SeGw Feature */
    METHOD_(ULONG, pfIKE_SetResetLocalBackupPeer)(UCHAR *pucPeerName, UCHAR ucIsLocalPeer,
                                                UCHAR *pucMasterPeerName, ULONG ulOpMode);
    METHOD_(ULONG, pfIKE_StartNegotiation)(UCHAR *pucPeerName, UCHAR ucPeerType);
    METHOD_(ULONG, pfIKE_StopNegotiation)(UCHAR *pucPeerName, UCHAR ucPeerType);
    METHOD_(ULONG, pfIKE_SetSwitchBack)(UCHAR *pucPeerName, UCHAR ucFlag);
   
    /* HERT3.3 : DH Support in HW */
    METHOD_(ULONG, pfIKE_CmnRegisterHWAPIs)(IKE_DH_HW_CBK_S *pstHwRegAPIs);
};

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif  /* _IIKE_INC_H_ */


