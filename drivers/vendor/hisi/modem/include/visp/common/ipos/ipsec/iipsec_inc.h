

#ifndef _IIPSEC_INC_H
#define _IIPSEC_INC_H

#ifdef __cplusplus
extern "C"{
#endif

/*@@TBD to be removed*/
#if (IPSEC_YES == IPSEC_AH_SUPPORT)
VOID IPSEC_AH_ProtoInput(MBUF_S *pMBuf, LONG lIpHLen);
LONG IPSEC_AH_SysCtl(LONG *pName, ULONG ulNameLen, VOID *pOld,
                        size_t *pOldLen, VOID *pNew, size_t nNewLen);
#endif
VOID IPSEC_ESP_ProtoInput(MBUF_S *pMBuf, LONG lIpHLen);
LONG IPSEC_ESP_SysCtl(LONG *pName, ULONG ulNameLen, VOID *pOld,
                        size_t *pOldLen, VOID *pNew, size_t nNewLen);

/*Component ID declaration */
/* Begin:Support multip VISP and IPOS environment by james*/

/*S9300-Added by Nagendra*/
/*For S9300, CID_IPSEC is available from Ipos_idbase.h*/
/* Kranthi: ARChanges */
#if (((S9300_MODULE_SEC_IPSEC != VRP_YES) \
            || (IR_PRODUCT_BUILD_TYPE != PRODUCT_TYPE_S9300_V1V2))\
        || (VRP_YES == VRP_MODULE_IKE_IPSEC_FOR_AR))

#ifndef CID_IPSEC
#define CID_IPSEC                               (CID_SEC_BASE)
#endif
#endif

/*S9300-Added by Nagendra*/
/* Interface IDs declaration */
/*For S9300, IID_IPSEC_BASE is available from Ipos_idbase.h*/
/* Kranthi: ARChanges */
#if (((S9300_MODULE_SEC_IPSEC != VRP_YES) \
            || (IR_PRODUCT_BUILD_TYPE != PRODUCT_TYPE_S9300_V1V2))\
        || (VRP_YES == VRP_MODULE_IKE_IPSEC_FOR_AR))

#ifndef IID_IPSEC_BASE
#define IID_IPSEC_BASE (IID_SEC_BASE)
#endif
#endif

/* B111: Added for removal of warning message */
struct tagSOCKET;

/* End:Support multip VISP and IPOS environment by james*/

/* Interface ID for Configurational interface */
#define IID_IPSEC_INTF_CFG      (IID_IPSEC_BASE + 2)

/* Interface ID for Functional interface */
#define IID_IPSEC_INTF_FUN      (IID_IPSEC_BASE + 3)

/* Moved here because products need to call Hardware callback */
/* Interface ID for adaptability interface */
#define IID_IPSEC_INTF_ADAPT    (IID_IPSEC_BASE + 5)

/*Ipv6: Security Support*/
/* Interface ID for Ipv6 configurational iterface */
#define IID_IPSECV6_INTF_CFG    (IID_IPSEC_BASE + 7)

/* Interface ID for Functional interface */
#define IID_IPSECV6_INTF_FUN    (IID_IPSEC_BASE + 8)

/* Configuration  API`s */
DECLARE_INTERFACE (IIF_IPSEC_ComIntCFG)
{
    IUNKNOWN_METHODS                                                    /*1*/

    METHOD_(ULONG, pfIPSEC_CreateDelPolicy)(IPSEC_POLICY_S *pstPolicy,
                                    ULONG ulPolicyMode, ULONG ulOpMode);/*2*/

#if ((IPSEC_MAIN_BOARD == IPSEC_YES) || (IPSEC_CENTERALIZATION == IPSEC_YES))

    METHOD_(ULONG, pfIPSEC_CreateDelProposal)(CHAR *szTransformName,
                                    ULONG ulOpMode);                    /*3*/

    METHOD_(ULONG, pfIPSEC_SetEncapsulationMode)(CHAR *pucProposalName,
                                    ULONG ulEncapType);                 /*4*/

    METHOD_(ULONG, pfIPSEC_SetTransformProtocol)(CHAR *pucProposalName,
                                    ULONG ulProtocolType);              /*5*/
#if (IPSEC_YES == IPSEC_AH_SUPPORT)
    METHOD_(ULONG, pfIPSEC_SetAHAlgorithm)(CHAR *purProposalName,
                                    ULONG ulAHHash);                    /*6*/
#endif
    METHOD_(ULONG, pfIPSEC_SetESPEncryption)(CHAR *pucProposalName,
                                    ULONG ulEncryptionType);            /*7*/

    METHOD_(ULONG, pfIPSEC_SetESPAlgorithm)(CHAR *pucProposalName,
                                    ULONG ulESPHash);                   /*8*/

    METHOD_(ULONG, pfIPSEC_SetCompressionAlgorithm)(CHAR *szTransformName,
                        ULONG ulCompressionAlgorithm, ULONG ulOpMode);  /*9*/

    METHOD_(ULONG, pfIPSEC_SetDelPolicyProposal)(IPSEC_POLICY_S *pstPolicy,
                                    CHAR *szTransformName,
                                    ULONG ulOpMode);                    /*10*/

    METHOD_(ULONG, pfIPSEC_SetDelSaSPI)(IPSEC_SPI_PARAM_S *pstIpsecSaSpi,
                                    ULONG ulOpMode);                    /*11*/

    METHOD_(ULONG, pfIPSEC_SetDelSaAuthStringKey)(
                                    IPSEC_KEY_PARAM_S *pstStringKey,
                                    ULONG ulOpMode);                    /*12*/

    METHOD_(ULONG, pfIPSEC_SetDelSaAuthHEXKey)(IPSEC_KEY_PARAM_S *pstHexKey,
                                    ULONG ulOpMode);                    /*13*/

    METHOD_(ULONG, pfIPSEC_SetDelSaEncrHEXKey)(IPSEC_KEY_PARAM_S *pstHexKey,
                                    ULONG ulOpMode);                    /*14*/

    METHOD_(ULONG, pfIPSEC_SetDelACL)(IPSEC_POLICY_S *pstPolicy,
                                    ULONG ulACLNumber, ULONG ulOpMode); /*15*/

    METHOD_(ULONG, pfIPSEC_SetDelTunnelLocalAddress)(IPSEC_POLICY_S *pstPolicy,
                                    ULONG ulLocalAddress,
                                    ULONG ulOpMode);                    /*16*/

    METHOD_(ULONG, pfIPSEC_SetDelTunnelPeerAddress)(IPSEC_POLICY_S *pstPolicy,
                                    ULONG ulPeerAddress,
                                    ULONG ulOpMode);                    /*17*/


    METHOD_(ULONG, pfIPSEC_BindSaVPN)(IPSEC_POLICY_S *pstPolicy,
                                    CHAR *pucVPNName, ULONG ulOpMode);  /*18*/

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_SetDelPolicyIKEPeer)(IPSEC_POLICY_S *pstPolicy,
                                    CHAR *pucIKEPeerName,
                                    ULONG ulOpMode);                    /*19*/
#endif
    METHOD_(ULONG, pfIPSEC_PFS)(CHAR *pucPolicyName, ULONG ulPolicySeq,
                                    ULONG ulPFSType);                   /*20*/

    METHOD_(ULONG, pfIPSEC_SetSaLifetime)(
                                    IPSEC_SA_LIFETIME_PARAM_S *pstSALifeTime,
                                    ULONG ulOpMode);                    /*21*/

    METHOD_(ULONG, pfIPSEC_SetSaLifetimeGlobal)(ULONG ulPeriodsType,
                                    ULONG ulPeriods, ULONG ulOpMode);   /*22*/

    METHOD_(ULONG, pfIPSEC_CreateDelPolicyTemplate)(CHAR *pucTemplateName,
                                    ULONG ulSeqNumber, ULONG ulOpMode); /*23*/
#endif  /*#if ((IPSEC_MAIN_BOARD == IPSEC_YES)
                           || (IPSEC_CENTERALIZATION == IPSEC_YES)) */

    METHOD_(ULONG, pfIPSEC_MapInterface)(ULONG ulIfIndex, CHAR *szMapName,
                                ULONG ulOpMode, ULONG *pulErrMapNum);   /*24*/

/* HS: Pruned as balong dont use this API */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_ClearSA)(IPSEC_POLICY_NAME_SEQ_S *pstPolicy,
                                    IPSEC_SA_PARA_S *pstSAParameters,
                                    ULONG ulRemoteIpAddr, ULONG ulMode);/*25*/
#endif
    METHOD_(ULONG, pfIPSEC_GetDelIPSECSAStat)(IPSEC_AHSTAT_S *pstALLAHStat,
                                    IPSEC_ESPSTAT_S *pstALLESPStat,
                                    IPSEC_STAT_S *pstIPSECStat,
                                    ULONG ulOpMode);                    /*26*/
#if ((IPSEC_MAIN_BOARD == IPSEC_YES) || (IPSEC_CENTERALIZATION == IPSEC_YES))
    METHOD_(ULONG, pfIPSEC_GetProposalSum)(ULONG *pulProposalSum);      /*27*/

    METHOD_(ULONG, pfIPSEC_GetProposalName)(
                            CHAR (*pucProposalName)[IPSEC_STRLEN_15 + 1],
                            ULONG ulBeginIndex, ULONG ulNumber,
                            ULONG *pulActualNumber);                    /*28*/

    METHOD_(ULONG, pfIPSEC_GetProposalByName)(CHAR*pucProposalName,
                        IPSEC_PROPOSAL_CONTENT_S *pstProposalContent);  /*29*/

    METHOD_(ULONG, pfIPSEC_GetPolicySum)(ULONG *pulPolicySum);          /*30*/

    METHOD_(ULONG, pfIPSEC_GetPolicyNameAndSeq)(IPSEC_POLICY_NAME_SEQ_S
                                    *pstPolicyNameAndSeq, ULONG ulBeginIndex,
                                    ULONG ulNumber,
                                    ULONG *pulActualNumber);            /*31*/

    METHOD_(ULONG, pfIPSEC_GetPolicyByName)(CHAR *szMapName, ULONG ulSequence,
                            IPSEC_CryptoMap_Info_S *pstPolicyInfo);     /*32*/
#endif
    METHOD_(ULONG, pfIPSEC_GetTemplateSum)(ULONG *pulTemplateSum);      /*33*/


    METHOD_(ULONG, pfIPSEC_GetTemplateNameAndSeq)(
                                IPSEC_POLICY_NAME_SEQ_S *pstTemplateNameAndSeq,
                                ULONG ulBeginIndex, ULONG ulNumber,
                                ULONG *pulActualNumber);                /*34*/

    METHOD_(ULONG, pfIPSEC_GetTemplateByName)(
                            IPSEC_POLICY_NAME_SEQ_S *pstTemplateNameAndSeq,
                            IPSEC_TEMPLATE_CONTENT_S *pstTemplateContent);/*35*/

    METHOD_(ULONG, pfIPSEC_GetInterfacePolicy)(ULONG ulIfIndex,
                                    CHAR *pucPolicyName);               /*36*/

    METHOD_(ULONG, pfIPSEC_GetSeqByPolicyName)(CHAR*pucPolicyName,
                                    ULONG **ppPolicySeq,
                                    ULONG *pulPolicySum);               /*37*/

    METHOD_(ULONG, pfIPSEC_GetSaLifetimeGlobal)(ULONG *pulTime,
                                    ULONG *pulTraffic);                 /*38*/

                                                                        /*39*/
    METHOD_(ULONG, pfIPSEC_OpenObject_Transform)(ULONG *pulWaitListHandle);

                                                                        /*40*/
    METHOD_(ULONG, pfIPSEC_CloseObject_Transform)(ULONG *pulWaitListHandle);

    METHOD_(ULONG, pfIPSEC_GetBulkTransform)(ULONG ulWaitListHandle,
                                    ULONG ulNumOfTransWanted,
                                    ULONG *pulNumOfTransReturn,
                                    IPSEC_CryptoTransform_S *pTransBuf);/*41*/

    METHOD_(ULONG, pfIPSEC_GetSingleTransForDisplay)(CHAR *szTransformName,
                                IPSEC_CryptoTransform_S *pstTransform); /*42*/

    METHOD_(ULONG, pfIPSEC_GetFirst_PolicyGroup)(ULONG *pulWaitListHandle,
        ULONG *pulNumberOfPolicies, IPSEC_MapGroupHead_S *pstMapHead);  /*43*/

    METHOD_(ULONG, pfIPSEC_GetNext_PolicyGroup)(ULONG *pulWaitListHandle,
        ULONG *pulNumberOfPolicies, IPSEC_MapGroupHead_S *pstMapHead);  /*44*/

    METHOD_(ULONG, pfIPSEC_GetFirstPolicyOfPolGroup)(CHAR *szPolicyGroupName,
                                         ULONG *pulWaitListHandle,
                                 IPSEC_CryptoMap_Info_S *pstPolicyInfo);/*45*/

    METHOD_(ULONG, pfIPSEC_GetNextPolicyOfPolGroup)(ULONG ulWaitListHandle,
                                  IPSEC_CryptoMap_Info_S *pstPolicyInfo);/*46*/

    METHOD_(ULONG, pfIPSEC_GetSinglePolicy)(CHAR *szPolicyName,
        ULONG ulSequenceNumber, IPSEC_CryptoMap_Info_S *pstPolicyInfo); /*47*/

    METHOD_(ULONG, pfIPSEC_GetFirst_DynaPolicyGroup)(ULONG *pulWaitListHandle,
                                ULONG *pulNumberOfPolTems,
                                IPSEC_MapGroupHead_S *pstMapHead);      /*48*/

    METHOD_(ULONG, pfIPSEC_GetNext_DynaPolicyGroup)(ULONG *pulWaitListHandle,
                                    ULONG *pulNumberOfPolTems,
                                    IPSEC_MapGroupHead_S *pstMapHead);  /*49*/

#if ((IPSEC_MAIN_BOARD == IPSEC_YES) || (IPSEC_CENTERALIZATION == IPSEC_YES))
    METHOD_(ULONG, pfIPSEC_GetFirst_SAIfHandle)(IPSEC_SHOW_SAINFO_S *pstSAInfo,
                                    IPSEC_SHOWSA_HANDLE_S *pstHandles,
                                    IPSEC_SHOW_INTERFACE_S *pstInterface);/*50*/

    METHOD_(ULONG, pfIPSEC_GetBulkSA)(IPSEC_SHOW_SAINFO_S *pstSAInfo,
                                    IPSEC_SHOWSA_HANDLE_S *pstHandles,
                                    UCHAR *pucShowBuf, ULONG *pulRevLen); /*51*/

    METHOD_(ULONG, pfIPSEC_GetNext_SAIfHandle)(IPSEC_SHOW_SAINFO_S *pstSAInfo,
                                    IPSEC_SHOWSA_HANDLE_S *pstHandles,
                                    IPSEC_SHOW_INTERFACE_S *pstInterface);/*52*/
#endif

    METHOD_(ULONG, pfIPSEC_GetIFDetails)(CHAR *pMsg, CHAR *pRevData,
                                                     ULONG ulRevLen);   /*53*/

    METHOD_(ULONG, pfIPSEC_SetDebug)(ULONG ulSet, ULONG ulDebugType);   /*54*/

    METHOD_(ULONG, pfIPSEC_SetPacketDebugOnMap)(ULONG ulSet, CHAR *szMapName,
                                    ULONG ulSequence);                  /*55*/

                                                                        /*56*/
    METHOD_(ULONG, pfIPSEC_SetPacketDebugOnTernaryOperator)(ULONG ulSet,
                                  ULONG ulAddress, ULONG ulSpi, UCHAR ucProto);

                                                                        /*57*/
    METHOD_(ULONG, pfIPSEC_SetPafValues)(IPSEC_PAF_VALUES_S *pstIPsecPafValue);

#if ((IPSEC_MAIN_BOARD == IPSEC_YES) || (IPSEC_CENTERALIZATION == IPSEC_YES))
    METHOD_(ULONG, pfIPSEC_GetTransParamByName)(CHAR *szTransformName,
                                    USHORT *pusTransform);              /*58*/
#endif
    METHOD_(ULONG, pfIPSEC_GetSAMode)(CHAR *szMapName, ULONG ulSequence,
                                                     UCHAR *pucSaMode); /*59*/

                                                                        /*60*/
    METHOD_(ULONG, pfIPSEC_GetDebug)(ULONG ulDebugType, ULONG *pulDbgStatus);

    METHOD_(ULONG, pfIPSEC_GetTunnelDebugStatus)(ULONG ulIfIndex,
                                                ULONG *pulDbgStatus);   /*61*/

    METHOD_(ULONG, pfIPSEC_GetTdbVtSyncInfo)(ULONG ulSpi,
                                    union sockaddr_union *pPeer, UCHAR ucProto,
                                    IPSEC_VT_SYN_MSG_S *pstSyncMsg);    /*62*/

    METHOD_(ULONG, pfIPSEC_GetFirst_MapifIndex_ByMapName)(
                                    ULONG *pulWaitListHdlr, CHAR *szMapName,
                                    CHAR *szIfnetName);                 /*63*/

    METHOD_(ULONG, pfIPSEC_GetNext_MapifIndex_ByMapName)(ULONG ulWaitListHdlr,
                                    CHAR *szMapName, CHAR *szIfnetName);/*64*/

    METHOD_(ULONG, pfIPSEC_ApplyManualMap)(VOID *pMsg);                 /*65*/
/* HS: Pruned as balong dont use this API */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_ApplyIsakmpMap)( VOID *pMsg, VOID *pstFlow,
                        ULONG ulRuleID, UCHAR ucDscp, ULONG ulAction);  /*66*/
#endif
    METHOD_(ULONG, pfIPSEC_GetBulkSA_IO)(CHAR *pMsg, UCHAR *pucShowBuf,
                                    ULONG *pulRevLen);                  /*67*/

#if ((IPSEC_MAIN_BOARD == IPSEC_YES) || (IPSEC_CENTERALIZATION == IPSEC_YES))
    METHOD_(ULONG, pfIPSEC_SetSATriggerMode)(IPSEC_POLICY_S *pstPolicy,
                                    ULONG ulMode);                      /*68*/
#endif

    METHOD_(ULONG, pfIPSEC_GetDefaultIpsecParameters)(
                    IPSEC_DEFAULT_PARAMETERS_S *pstDefaultValues);      /*69*/

    /* V1R3_DEV_BEGIN: CACHE  */
    METHOD_(ULONG, pfIPSEC_GetMainCacheContents)(
                    IPSEC_SHOWCACHE_HANDLE_S *pucShowBuf,
                    UCHAR ucCacheType, ULONG ulEntryCount);             /*70*/

    METHOD_(ULONG, pfIPSEC_FlushCache)(UCHAR ucCacheType);               /*71*/

    METHOD_(VOID, pfIPSec_DelAgedCacheEntries)(UCHAR ucCacheType);      /*72*/

    METHOD_(ULONG, pfIPSEC_EnableDisableCache)(UCHAR ucOpMode);         /*73*/

    METHOD_(ULONG, pfIPSEC_SetCacheAgeTime)(ULONG ulAgeTime,
                                    UCHAR ucCacheType);                 /*74*/

    METHOD_(ULONG, pfIPSEC_SetCacheSavedEntriesCount)(ULONG ulEntryCount);
                                                                        /*75*/

    METHOD_(ULONG, pfIPSec_GetIoCacheContents)(VOID *pRcvMsg,
                                    IPSEC_SHOWCACHE_HANDLE_S *pucShowBuf,
                                    UCHAR ucCacheType,
                                    ULONG ulEntryCount);                /*76*/

    METHOD_(ULONG, pfIPSEC_GetDeleteCacheStats)(UCHAR ucOpmode,
                                    UCHAR ucCacheType,
                                    IPSEC_CACHE_STAT_S *pucShowBuf);    /*77*/

    METHOD_(ULONG, pfIPSEC_HandleUpdateForCache)(UCHAR ucCacheType,
                       ULONG ucOperationType, IPSEC_POLICY_ACL_S *pstAClInfo,
                       IPSEC_SPDS_S *pstSpdsData);                      /*78*/

    METHOD_(ULONG, pfIPSEC_OpenObject_Cache)(ULONG *pulWaitListHandle,
        UCHAR ucCacheType);                                             /*79*/

    METHOD_(ULONG, pfIPSEC_CloseObject_Cache)(ULONG *pulWaitListHandle);/*80*/

     /* V1R3_DEV_END: CACHE*/
#if ((IPSEC_MAIN_BOARD == IPSEC_YES) || (IPSEC_CENTERALIZATION == IPSEC_YES))
    METHOD_(ULONG, pfIPSEC_CreateModeCfgPolicy)(
                                    IPSEC_POLICY_S *pstPolicy);         /*81*/

    METHOD_(ULONG, pfIPSEC_EnableDisableTrafficSelector)(UCHAR ucOpMode,
                                     IPSEC_POLICY_S *pstPolicy);        /*82*/
#if(IPSEC_YES == IPSEC_CACHE)/*Hisilicon - added while Integration */
    METHOD_(ULONG, pfIPSEC_GetCacheGlobals)(
                                IPSEC_CACHE_GLOBAL_S *pstCacheGlobals); /*83*/
#endif
#endif
    METHOD_(ULONG, pfIPSEC_EnableDisableDscp)(UCHAR ucOpMode);          /*84*/

    /* Sumangala : Added for New API requirement from SGSN */           /*85*/
    METHOD_(ULONG, pfIPSEC_GetInterfacesUsedByPolicy)(
            IPSEC_INTERFACEPOLICY_S  **pstInterfacePolicy, ULONG *pulCount);

    /* Anti replay Configuration Change: Start */
    METHOD_(ULONG, pfIPSEC_EnableDisableAntiReplay)(UCHAR ucOpMode);    /*86*/
    /* Anti replay Configuration Change: End */

    METHOD_(ULONG, pfIPSEC_SetOnDemandHardExpTimeout) (ULONG ulTimeOut,
                                                   ULONG ulOpMode);     /*87*/

    /*B500 - SGSN-CMD Registration*/
    METHOD_(ULONG, pfIPSEC_Config_Proposal)
                        (IPSEC_PROPOSAL_CONFIG_S * pstIpsecProposal);   /*88*/
    METHOD_(ULONG, pfIPSEC_Get_Proposal) (CHAR * pszTransformName,
                        IPSEC_PROPOSAL_CONFIG_S * pstIpsecProposal);    /*89*/
    METHOD_(ULONG, pfIPSEC_Config_Manual_Policy)
                    (IPSEC_POLICY_MANUAL_S * pstIpsecManualPolicy);     /*90*/
    METHOD_(ULONG, pfIPSEC_Get_Manual_Policy) (CHAR * pszMapName,
                        ULONG ulMapSeq,
                        IPSEC_POLICY_MANUAL_S * pstIpsecManualPolicy);  /*91*/
    METHOD_(ULONG, pfIPSEC_Config_IsakmpModecfg_Policy)
                    (IPSEC_POLICY_ISAKMPMODECFG_S * pstIpsecPolicy);    /*92*/
    METHOD_(ULONG, pfIPSEC_Get_IsakmpModecfg_Policy)
                    (CHAR * pszMapName, ULONG ulMapSeq,
                    IPSEC_POLICY_ISAKMPMODECFG_S * pstIpsecPolicy);     /*93*/
    METHOD_(ULONG, pfIPSEC_GetDelSaStat)(IPSEC_SA_STAT_S *pstSaStat,
                                                       ULONG ulOpMode); /*94*/
#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
    METHOD_(ULONG, pfIPSEC_GetDelIPSECGenHwStat)(IPSEC_GEN_HW_STAT_S *
                                        pstGenHwStat, ULONG ulOpMode);  /*95 */
#endif

#if(IPSEC_YES == IPSEC_MODECFG)
    /* AC4D07629: Updated for suggession address */
    METHOD_(ULONG, pfIPSEC_GetModeCFG_SA)(CHAR *szMap, ULONG ulSeq,
                              ULONG ulDirection, ULONG ulIfIndex,
                              ULONG ulModeCfgAddress, TDB_S **ppstTdb); /*96*/
#endif

    METHOD_(ULONG, pfIPSEC_SetModeCFG_SuggestionAddr) (CHAR *szMap, ULONG ulSeq,
                            ULONG ulModeCfgSugAddress, ULONG ulMask);   /*97*/

    /*[Defect:AC4D07930] Auto Trigger Cnofiguration Apis*/
    METHOD_(ULONG, pfIPSEC_EnableDisableWindowSizeOneSupport)
                                                (ULONG ulOpMode);       /*98*/

    METHOD_(ULONG, pfIPSEC_GetAutoTrigParam)(ULONG *pulTime,
                                             ULONG *pulMaxAcquire);     /*99*/
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    /*Iteration2-Story3-IpsecPeerHash*/
    METHOD_(ULONG, pfIPSEC_GetDynaPeersBuffer)(ULONG ulWaitListHandle,
                            ULONG ulRemaining, CHAR *pcBuffer,
                                            ULONG *pulFetchCount);      /*100*/


    METHOD_(ULONG, pfIPSEC_GetPeerBuffer)(CHAR *pcPeerName,
                                            CHAR *pcBuffer);            /*101*/
/* HS: Pruned as balong suports only manual ipsec */

    METHOD_(ULONG, pfIPSEC_DisplayAllPeers)(ULONG ulWaitListHandle,
                            CHAR *pcBuffer, ULONG *pulFetchCount);      /*102*/
    METHOD_(VOID, pfIPSEC_GetPeerCount)();                              /*103*/
    METHOD_(ULONG, pfIPSEC_OpenObject_Peer)(ULONG *pulWaitListHandle);  /*104*/
    METHOD_(ULONG, pfIPSEC_CloseObject_Peer)(ULONG *pulWaitListHandle); /*105*/

    METHOD_(ULONG, pfIPSEC_OpenObject_DynaPeer)
                (ULONG *pulWaitListHandle, CHAR *pcPeerName);           /*106*/
    METHOD_(ULONG, pfIPSEC_CloseObject_DynaPeer)(ULONG * pulWaitListHandle);
                                                                        /*107*/
#endif                                                                        
    METHOD_(ULONG, pfIPSEC_GetPeerStats)(ULONG *pulIpsecPeerCount,
                            ULONG *pulIpsecDynaPeerCount,
                            ULONG *pulIpsecTotalPeerCount,
                            ULONG *pulIpsecDpdTimerCount);              /*108*/

    /*S9300 - Added by Nagendra*/
    METHOD_(ULONG, pfIPSEC_GetDeleteSAExpStats) (IPSEC_SA_EXP_S *pstSAExpStats,
                                                  ULONG ulOpMode);      /*109*/

    /*Added for Warning messages in IPOS. Removed extra * in the function arguemnt*/
    METHOD_(ULONG, pfIPSEC_RegisterWarningAPI)(pfIPSEC_WarningOut pfFunc);
                                                                        /*110*/

    /*Iteration2: Story12: Maintainance*/
    METHOD_(VOID, pfIPSEC_GetPfkeyv2Stats)(IPSEC_PFKEYV2_STATS_S *pstStats);
                                                                        /*111*/
    METHOD_(VOID, pfIPSEC_GetPfkeyv2FailStats)(IPSEC_PFKEYV2_FAIL_STATS_S
                                                    *pstStats);         /*112*/
    METHOD_(VOID, pfIPSEC_ResetPfkeyv2Stats)();                         /*113*/
    METHOD_(ULONG, pfIPSEC_GetPfkeyv2MapStats)(CHAR *szMapName, ULONG ulSequence,
                                ULONG ulIfIndex,
                                IPSEC_PFKEYV2_MAP_STATS_S *pstStats);   /*114*/
    METHOD_(ULONG, pfIPSEC_ResetPfkeyv2MapStats)(CHAR *szMapName,
                                ULONG ulSequence,
                                ULONG ulIfIndex);                       /*115*/
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(VOID, pfIPSEC_GetSaFailedMapCount)(ULONG *pulCount);        /*116*/

    METHOD_(ULONG, pfIPSEC_GetSaFailedMap)(ULONG ulCount, UCHAR *pcBuffer);
                                                                        /*117*/
#endif
    METHOD_(ULONG, pfIPSEC_SetCoreTriggerParams)(ULONG ulIPSecMaxAutoTriggerDef,
                                        ULONG ulIPSecMaxPending);       /*118*/

    /*LTE multiple ACL-SA : Dynamic ACL updation*/
    METHOD_(ULONG, pfIPSEC_HandleACLEvent)(ULONG ulAclNo, ULONG ulRuleNo,
                                                ULONG ulEventType);     /*119*/
    METHOD_(ULONG, pfIPSEC_SetMaxPolicyProposal)(ULONG ulMaxPolicy,
                                                ULONG ulMaxProposal);   /*120*/
#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
    /*B053: Peer reliability (Master/Slave)*/
    METHOD_(ULONG, pfIPSEC_SetDel_MasSlv_Policy)(
            IPSEC_POLICY_RELATION_BIND_S  *pstMsPolInfo, ULONG ulOper); /*121*/
#endif

    /*B057: key deletion from IKE/IPSEC after SA establishment*/
    METHOD_(ULONG, pfIPSEC_EnableKeyDeletion) (ULONG ulOpMode);         /*122*/

    /*B058: Replay Window Size*/
    METHOD_(ULONG, pfIPSEC_SetDelPolicyWindowSize_SeqNo) (IPSEC_POLICY_S *pstIpsecPolicy,
                                ULONG ulWindowSize, ULONG ulOpMode);    /*123*/
#if (IPSEC_YES == IPSEC_PROFILE_SUPPORT)
#if ((IPSEC_MAIN_BOARD == IPSEC_YES) || (IPSEC_CENTERALIZATION == IPSEC_YES))
    METHOD_(ULONG, pfIPSEC_PROF_CreateOrDelete)(UCHAR *pucProfileName,
                                                ULONG ulOpMode);        /*124*/
    METHOD_(ULONG, pfIPSEC_PROF_SetDelIpsecProp)(UCHAR *pucProfileName,
                        UCHAR *pucTransformName, ULONG ulOpMode);       /*125*/

    METHOD_(ULONG, pfIPSEC_PROF_SetSALifetime)(UCHAR *pucProfileName, ULONG ulPeriodsType,
                                    ULONG ulPeriods, ULONG ulOpMode);   /*126*/

    METHOD_(ULONG, pfIPSEC_PROF_OpenObject)(ULONG *pulWaitListHandle);  /*127*/

    METHOD_(ULONG, pfIPSEC_PROF_CloseObject)(ULONG *pulWaitListHandle); /*128*/

    METHOD_(ULONG, pfIPSEC_PROF_GetBulk)(ULONG ulProfileWaitListHandle,
                        ULONG ulNumOfProfilesWanted, ULONG *pulNumOfProfilesReturn,
                        IPSEC_PROFILE_INFO_S *pstProfBuf);              /*129*/

    METHOD_(ULONG, pfIPSEC_PROF_GetTotalCount)();                       /*130*/

    METHOD_(ULONG, pfIPSEC_PROF_SetDelPFS)(UCHAR *pucProfileName,
                                                ULONG ulPFSType);       /*131*/
    METHOD_(ULONG, pfIPSEC_PROF_SetMax)(ULONG ulMaxProfile);            /*132*/
    METHOD_(ULONG, pfIPSEC_PROF_SetDelPeerName)(UCHAR *pucProfileName,
                        UCHAR *pucInputIkePeerName, ULONG ulOpMode);    /*133*/
    METHOD_(ULONG, pfIPSEC_PROF_SetDelOnInterface)(ULONG ulIfIndex,
                        UCHAR *pucProfileName, ULONG ulOpMode);         /*134*/

    METHOD_(ULONG, pfIPSEC_PROF_GetInfoStruct)(UCHAR *ucProfileName,
                        IPSEC_PROFILE_INFO_S *pstProfInfo);             /*135*/

    METHOD_(ULONG, pfIPSEC_PROF_AddSpoke) (ULONG ulIfIndex,
                                            ULONG ulDestIP,
                                            VOID *pvFutureUse);         /*136*/

    METHOD_(ULONG, pfIPSEC_PROF_DeleteSA) (UCHAR *pucProfileName);      /*137*/

    METHOD_(ULONG, pfIPSEC_PROF_DelSpokeByDestAddr) (ULONG ulIfIndex,
                                                ULONG ulDestAddress);   /*138*/

    METHOD_(ULONG, pfIPSEC_PROF_GetIKEVersionByProfileName) (CHAR *pszProfileName,
                                                UCHAR *pucIKEVersion);  /*139*/
#endif
#endif
    /*GGSN-SUPPORT*/
    METHOD_(ULONG, pfIPSEC_GetPeerBuf)(ULONG ulDestAddr,
                                                CHAR *pucMsgBuf);       /*140*/

#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(VOID, pfIPSEC_VerifyDynaPeerHashTable)(CHAR *pcBuf);        /*141*/
#endif
#if (IPSEC_YES == IPSEC_PROFILE_SUPPORT) 
    METHOD_(VOID, pfIPSEC_PROF_UnMapOnInterfaceDel) (ULONG ulIfIndex,
                                                UCHAR *pucProfileName, ULONG ulIsEzVPN); /*142*/
#endif
    METHOD_(ULONG, pfIPSEC_SetResetSupportedAlgorithm) (
                                        IPSEC_PROP_PARAM_S *pstPropParam,
                                                ULONG ulOpMode);        /*143*/
    METHOD_(VOID, pfIPSEC_GetSupportedAlgorithms)(
                                IPSEC_PROP_PARAM_S *pstPropParam);      /*144*/
#if (IPSEC_YES == IPSEC_RRI_SUPPORT) 
    METHOD_(ULONG, pfIPSEC_EnableDisableReverseRoute)(CHAR *szPolName, ULONG ulPolSeqNo,
                                UCHAR ucRouteInjectionMode, ULONG ulPreference,
                                UCHAR ucOpMode);                        /*145*/
#endif
    METHOD_(ULONG, pfIPSEC_PROF_GetTunnelParams)(
                        IPSEC_TUNNEL_PARAMS_S *pstIPsecTunnelParams);   /*146*/
    METHOD_(ULONG, pfIPSEC_SetDelACLVer)(IPSEC_POLICY_S *pstPolicy, ULONG ulACLNumber,
                                UCHAR ucACLVer, ULONG ulOpMode);        /*147*/

    /*LTE Multi-ACL6-SA : Dynamic ACL updation*/
    METHOD_(ULONG, pfIPSEC_HandleACL6Event)(ULONG ulAclNo, ULONG ulRuleNo,
                                                ULONG ulEventType);     /*148*/

#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
    METHOD_(ULONG, pfIPSEC_PROF_GetTunnelStatus) (ULONG ulIfIndex, ULONG ulVrfIndex,
                                                ULONG ulTunnelLocalAddr,
                                                ULONG ulTunnelDestAddr); /*149*/
#endif

    METHOD_(ULONG, pfIPSEC_IntfStateNotification) (ULONG ulIfIndex, ULONG ulIfState);/*150*/
#if (IPSEC_YES == IPSEC_PROFILE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_EasyVPN_CreateOrDelete) (UCHAR *pucEasyVpnName, ULONG ulEasyVpnMode,
                                                            ULONG ulOpMode);/*151*/

    METHOD_(ULONG, pfIPSEC_EasyVPN_SetDelIkePeer) (UCHAR *pucEasyVpnName, ULONG ulIkeVersion,
                                                            ULONG ulOpMode);      /*152*/

    METHOD_(ULONG, pfIPSEC_EasyVPN_SetDelPeerRemoteName) (UCHAR *pucEasyVpnName , UCHAR *pszRemoteName,
                                                            ULONG ulOpMode);      /*153*/

    METHOD_(ULONG, pfIPSEC_EasyVPN_SetDelVrf) (UCHAR *pucEasyVpnName, CHAR *pszVPNName, ULONG ulOpMode);  /*154*/

    METHOD_(ULONG, pfIPSEC_EasyVPN_SetDelPeerLocalAddr) (UCHAR *pucEasyVpnName, ULONG ulLocalAddr,
                                                            ULONG ulOpMode);  /*155*/

    METHOD_(ULONG, pfIPSEC_EasyVPN_SetDelAclNo) (UCHAR *pucEasyVpnName, ULONG ulACLNumber, ULONG ulOpMode);  /*156*/

    METHOD_(ULONG, pfIPSEC_EasyVPN_SetAuthMethod) (UCHAR *pucEasyVpnName, ULONG ulAuthMethod, ULONG ulOpMode); /*157*/

    METHOD_(ULONG, pfIPSEC_EasyVPN_SetDelPreSharedKey) (UCHAR *pucEasyVpnName, CHAR* pucPreSharedKey,
                                                            ULONG ulOpMode);     /*158*/

    METHOD_(ULONG, pfIPSEC_EasyVPN_SetResetPkiObj) (UCHAR *pucEasyVpnName, CHAR* pszObj,
                                                            ULONG ulOpMode);     /*159*/


    METHOD_(ULONG, pfIPSEC_EasyVPN_SetMax)(ULONG ulMaxEasyVPN);            /*160*/

    METHOD_(ULONG, pfIPSEC_EasyVPN_SetDelIkePeerAddr)(UCHAR *pucEasyVpnName, ULONG ulIpAddress,
                                            ULONG ulOpMode);            /*161*/

    METHOD_(ULONG, pfIPSEC_EasyVPN_SetDelIkePeerFqdn)(UCHAR *pucEasyVpnName, UCHAR *pszFqdn,
                                            ULONG ulOpMode);            /*162*/

    METHOD_(ULONG, pfIPSEC_EasyVPN_SetDelOnInterface)(ULONG ulIfIndex, UCHAR *pucEasyVPNName,
                                            ULONG ulOpMode);            /*163*/

    METHOD_(ULONG, pfIPSEC_EasyVPN_GetTotalCount)();            /*164*/

    METHOD_(ULONG, pfIPSEC_EasyVPN_GetBulk)(ULONG ulProfileWaitListHandle,
                            ULONG ulNumOfProfilesWanted,
                            ULONG *pulNumOfProfilesReturn,
                            IPSEC_PROFILE_INFO_S *pstProfInfoBuf);            /*165*/
    METHOD_(ULONG, pfIPSEC_EasyVPN_OpenObject)(ULONG *pulWaitListHandle);        /* 166 */

    METHOD_(ULONG, pfIPSEC_EasyVPN_SetDelLocalIDType)(UCHAR *pucEasyVpnName, ULONG ulLocalIDType); /* 167 */

    METHOD_(ULONG, pfIPSEC_EasyVPN_GetInfoStruct)(UCHAR *ucEasyVPNName,
                                            IPSEC_PROFILE_INFO_S *pstEasyVPNInfo); /* 168 */

    METHOD_(ULONG, pfIPSEC_EasyVPN_SetResetInBandExchange)(UCHAR *pucEasyVpnName,
                                                    ULONG ulType, ULONG ulOpMode); /* 169 */
#endif
    METHOD_(ULONG, pfIPSEC_TemplateKickSaWithSameFlow)(ULONG ulSetOrUndo);         /* 170 */
    METHOD_(ULONG, pfIPSEC_GetTemplateKickSaWithSameFlow)(VOID);                   /* 171 */

    /*HERT 3.4 - DO req*/
    METHOD_(ULONG, pfIPSEC_GetIPSECDoStats)(ULONG ulOperType);   /* 172 */


};

/* Function  API`s */
DECLARE_INTERFACE (IIF_IPSEC_ComIntFUN)
{
    IUNKNOWN_METHODS                                                    /*1*/

#if ((IPSEC_DISTRIBUTED == IPSEC_YES) && (IPSEC_MAIN_BOARD == IPSEC_YES))
    METHOD_(ULONG, pfIPSEC_ClearAllIpsecSA)(VOID);                      /*2*/
#endif
/* HS: Pruned as balong suports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_CheckIkePeerUsed)(CHAR *szIkePeerName, BOOL_T bCheckPROFApplyOnInter);      /*3*/
#endif
                                                                        /*4*/
    METHOD_(ULONG, pfIPSEC_GetRandomBytes)(VOID *pBuf, ULONG ulNumberofBytes);

#if ((IPSEC_MAIN_BOARD == IPSEC_YES) || (IPSEC_CENTERALIZATION == IPSEC_YES))
/* HS: Pruned as balong suports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_UpdateTdbEntryByIkePeer)(
                                        IPSEC_PEER_INFO_S *pstPeerInfo);/*5*/
#endif
#endif
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
                                                                        /*6*/
    METHOD_(ULONG, pfIPSEC_CheckIkePeer)(CHAR *szIkePeerName, ULONG ulIfIndex);
#endif

#if ((IPSEC_DISTRIBUTED == IPSEC_YES) && (IPSEC_MAIN_BOARD == IPSEC_YES))

    METHOD_(VOID, pfIPSEC_HotInsertProc)(ULONG ulDstSlot);              /*7*/

    METHOD_(ULONG, pfIPSEC_RemoveBoardForVirtualIF)(ULONG ulDstSlot);   /*8*/
#endif

    METHOD_(VOID, pfIPSEC_Output)(MBUF_S *pstMBuf, VOID *pIf,
                                    ULONG *pulUseIpsec);                /*9*/

    METHOD_(ULONG, pfIPSEC_Input)(MBUF_S *pstMBuf, VOID *pIf);          /*10*/
#if (IPSEC_YES == IPSEC_AH_SUPPORT)
    METHOD_(VOID, pfIPSEC_AH_ProtoInput)(MBUF_S *pMBuf, LONG lIpHLen);/*11*/
#endif
    METHOD_(VOID, pfIPSEC_ESP_ProtoInput)(MBUF_S *pMBuf, LONG lIpHLen);/*12*/

    METHOD_(ULONG, pfIPSEC_InputPacketMsg_Handler)(ULONG *pulMsgBuf);   /*13*/

    METHOD_(ULONG, pfIPSEC_OutputPacketMsg_Handler)(ULONG *pulMsgBuf);  /*14*/

    METHOD_(VOID, pfIPSEC_Timer_Callback)(VOID *pData, ULONG ulTimerType);/*15*/

    METHOD_(ULONG, pfIPSEC_GetIkePeerByCryptoMap)(CHAR *szMapName,
                                ULONG ulSequence, CHAR *szIKEPeerName); /*16*/

#if ((IPSEC_MAIN_BOARD == IPSEC_YES) || (IPSEC_CENTERALIZATION == IPSEC_YES))
    METHOD_(ULONG, pfIPSEC_FindCryptoMapByPeerAddress)(VOID *pvDstSockAddr, VOID *pvSrcSockAddr,
                                ULONG ulIfIndex, UCHAR ucType, CHAR *szIKEPeerName,
                                ULONG ulVrfIndex); /*17*/
#endif
#if (IPSEC_YES == IPSEC_AH_SUPPORT)
    METHOD_(LONG, pfIPSEC_AH_SysCtl)(LONG *pName, ULONG ulNameLen, VOID *pOld,
                            size_t *pOldLen, VOID *pNew, size_t nNewLen); /*18*/
#endif
    METHOD_(LONG, pfIPSEC_ESP_SysCtl)(LONG *pName, ULONG ulNameLen, VOID *pOld,
                            size_t *pOldLen, VOID *pNew, size_t nNewLen); /*19*/

    METHOD_(const CHAR *, pfIPSEC_GetVersion)();                         /*20*/
    METHOD_(ULONG, pfIPSEC_SA_Exists)(ULONG ulConnId, ULONG ulIntID,
                                    CHAR *szPolicyName, ULONG ulSequence);/*21*/

    METHOD_(VOID, pfIPSEC_SetMemShortageFlag)(ULONG ulMemShortFlag);    /*22*/

#if (IPSEC_MAIN_BOARD == IPSEC_YES) && (IPSEC_DISTRIBUTED == IPSEC_YES)
    METHOD_(VOID, pfIPSEC_pfkeyv2_from_ipc)(VOID *mem, ULONG datalen);  /*23*/
#endif
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
#if (IPSEC_IO_BOARD == IPSEC_NO)
                                                                        /*24*/
    METHOD_(LONG, pfIPSEC_PFkeyv2_sendmessage)(VOID **headers, LONG mode,
                        struct tagSOCKET *pstSocket, UCHAR satype, LONG count);
#endif
#endif
    METHOD_(VOID, pfIPSEC_IfDelete)(ULONG ulIfIndex);                   /*25*/

#if (IPSEC_DISTRIBUTED == IPSEC_YES) && (IPSEC_IO_BOARD == IPSEC_YES)
    METHOD_(LONG, pfIPSEC_Ipc_Key_send)(ULONG flg, ULONG fd, ULONG node,
                            ULONG chid, VOID *data, ULONG len);         /*26*/
#endif

    METHOD_(ULONG, pfIPSEC_SetDebugFlags)(UCHAR ucDebugflag);           /*27*/

    METHOD_(ULONG, pfIPSEC_GetTunnelLocalAddr)(CHAR *szPolName,
                                       ULONG ulSeqNum, VOID *pvAddr);  /*28*/


    METHOD_(ULONG, pfIPSEC_PostHW_InputPktHdlr)(SEC2_NOTIFY_CTX *pNotifyCtx,
                                     UCHAR *pucIV, ULONG ulIVLength,
                                     ULONG ulResult);                   /*29*/

    METHOD_(ULONG, pfIPSEC_PostHW_OutputPktHdlr)(SEC2_NOTIFY_CTX *pNotifyCtx,
                                      UCHAR *pucIV, ULONG ulIVLength,
                                      ULONG ulResult);                  /*30*/

    METHOD_(ULONG, pfIPSEC_RegisterTunnelStatus_Callback) (
                IPSEC_TUNNEL_STATUS_CALLBACK pfFuncPtr, ULONG ulAppId); /*31*/

    METHOD_(ULONG, pfIPSEC_GetTunnelStatus)(ULONG ulIfIndex,
                                ULONG ulSourceAddr, ULONG ulDestAddr,
                                ULONG ulDirection, ULONG *pulSaState);  /*32*/
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(VOID,  pfIPSec_AutoSendAcquire)(VOID);                      /*33*/
#endif

    METHOD_(TDB_S **, pfIPSEC_GetSharedSAInfo)(ULONG ulDirection);      /*34*/

                                                                        /*35*/
    METHOD_(ULONG, pfIPSec_RegisterProductFunc)(ULONG ulFuncID, VOID* pFunc);
    METHOD_(ULONG, pfIPSEC_IsNeedMergeToSECTask)(MBUF_S *pstMbuf,
                                                        ULONG ulDirec); /*36*/
                                                                        /*37*/
#if ((IPSEC_MAIN_BOARD == IPSEC_YES) || (IPSEC_CENTERALIZATION == IPSEC_YES))
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_CreateIkePeer)(IPSEC_PEER_INFO_S *pstPeerContent);
#endif
#endif
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_DeleteIkePeer)(UCHAR *szPeerName);           /*38*/

    METHOD_(VOID,  pfIPSEC_DpdTimerExpire)(
                            IPSEC_DPDCALLBACKDATA_S *pstCallbackData); /*39*/
#endif    
#if (IPSEC_MAIN_BOARD == IPSEC_YES)
    METHOD_(VOID, pfIPSEC_HandleDpdRequest)(VOID *pMsg);                /*40*/
    METHOD_(ULONG, pfIPSEC_HandleStopDpd)(VOID *pMsg, ULONG ulMsgLen);  /*41*/
#endif
#if (IPSEC_YES == IPSEC_IO_BOARD)
    METHOD_(ULONG, pfIPSEC_DeleteModeCfgEntries_in_IO)();               /*42*/
#endif
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    /*S9300.ITR2.STORY.2*/
    METHOD_(VOID, pfIPSEC_SendExpireByPeerName)(UCHAR *szPeerName,
                                        union sockaddr_union *pstAddr,
                                        USHORT usSadbSrcPort,
                                        USHORT usSadbDstPort);

    METHOD_(ULONG, pfIPSEC_Check_VendorID)(UCHAR *szPeerName,
                                            UCHAR ucVendorIdResult);    /*44*/
#endif    
#if (IPSEC_YES == IPSEC_IO_BOARD)
#if ((IPSEC_DPD == IPSEC_YES) || (IPSEC_MODECFG == IPSEC_YES))
    METHOD_(ULONG, pfIPSEC_UpdateIkePeer)(CHAR *pMsg);                  /*45*/
#endif
#endif

    /*TDBPROBLEM-IkeV2*/  /*51*/
    METHOD_(IPSEC_TRAFFIC_SELECTOR_S *, pfIPSEC_GetTSFromTdb)(TDB_S *pstTdb);/*46*/
#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
    METHOD_(ULONG, pfIPSEC_HandleGenHWMsg)(ULONG ulNotifyType,
                                        IPSEC_HW_COMMON_S *pstCommNotifyInfo,
                                        VOID* pstPacketInfo,
                                        IPSEC_TdbIndex_S *pstTdbIndex);  /*47*/
    METHOD_(ULONG, pfIPSEC_HW_NotifyReceive)(ULONG ulNotifyType,
                                        IPSEC_HW_COMMON_S *pstCommNotifyInfo,
                                        VOID* pstPacketInfo,
                                        IPSEC_TdbIndex_S *pstTdbIndex); /*48*/
#endif
    METHOD_(ULONG, pfIPSEC_StartIpsecSaRekey)(CHAR *szMapName,
                                        ULONG ulSeq, ULONG ulIfIdx);    /*49*/
#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
    /*Added by Prateek for AP requirement*/
    METHOD_(ULONG, pfIPSEC_HW_SATrafficExpire)(IPSEC_TdbIndex_S *pstTdbIndex,
                                                UCHAR ucExpirationType); /*50*/
#endif
#if(IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_InboundDpdProcessingBySA)(TDB_S *pstTdb);     /*51*/
    METHOD_(ULONG, pfIPSEC_OnDemandDpdProcessingBySA)(TDB_S *pstTdb);    /*52*/


    /* IPSEC6.STORY.04 - Removal of Pfkey socket */
    METHOD_(UCHAR *, pfIPSEC_Pfkeyv2_send) (VOID *pvSadbMsg, ULONG ulLen); /*53*/
#endif
    /* LOOP_OPT */
    METHOD_(ULONG, pfIPSEC_GetConnIdFromTernaryOperator) (ULONG ulSpi,
                                        VOID *puSockAddr, UCHAR ucProto); /*54*/
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    /*Iteration2: Story12: Maintainance*/
    METHOD_(ULONG, pfIPSEC_NotifyPfkeyv2Msg)(CHAR *szMapName, ULONG ulMapSeq,
                                        ULONG ulIfIndex, ULONG ulFailType,
                                        ULONG ulCauseType);             /*55*/
#endif
    /*SGSN License implementation - B511*/
    METHOD_(VOID, pfIPSEC_EnableDisableLicense)(ULONG ulLicenseFlag);   /*56*/

    METHOD_(ULONG, pfIPSEC_GetIkePeerByCrytoDetails)(CHAR *szMapName,
                                ULONG ulSequence, CHAR *szIKEPeerName); /*57*/
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_GENERIC_HW_SUPPORT == IPSEC_YES)
    /*B050: Traffic based SA_Expiry*/
    METHOD_(VOID, pfIPSEC_TrafficBasedTriggerForHW)();                  /*58*/
#endif
    /*GGSN-SUPPORT*/
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_UpdatePhase1connIDForPeer)(ULONG ulPeerIndx,
                                ULONG ulDestAddr, USHORT usDestPort,
                                ULONG ulConnID, ULONG ulVrfIndex);     /*59*/
#endif
#if (IPSEC_YES == IPSEC_PROFILE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_PROF_GetProfileIDAndVersion) (CHAR *pszProfileName,
                                    ULONG *pulProfileID, UCHAR *pucIKEVersion); /*60*/
#endif
    METHOD_(ULONG, pfIPSEC_GetIPSecSALifetime)(CHAR *pcMapName, ULONG ulSeqNo,
                                 ULONG *pulLifeTimeSec, ULONG *pulLifeTimeBytes); /*61*/
#if (IPSEC_YES == IPSEC_PROFILE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_PROF_DynaUpdateByPeerName)(CHAR *szPeerName, ULONG ulProfPeerUpdateType,
                                        UCHAR ucUpdateTdb);             /*62*/
#endif
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_GetPhase1connIDFromPeer)(ULONG ulPeerIndx, ULONG ulDestAddr,
                                USHORT usDestPort, ULONG ulVrfIndex, ULONG *pulConnID);   /*63*/

    METHOD_(struct tagIPSEC_PEER_S *, pfIPSEC_GetDynaPeer)(ULONG ulDestAddr,
                                        USHORT usDestPort, ULONG ulVrfIndex);         /*64*/
#endif
    METHOD_(ULONG, pfIPSEC_IPv6_FindCryptoMapByPeerAddress) (VOID *pvSockAddr, VOID *pvSrcSockAddr,
                                                            ULONG ulIfIndex, CHAR *szIKEPeerName);    /*65*/
/* HS: Pruned as balong supports only manual ipsec */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_CheckPolicyOnIntForIkePeer)(UCHAR *pszIkePeerName);       /*66*/
#endif

    METHOD_(ULONG, pfIPSEC_HandleIntfStateEvent) (ULONG ulIfIndex, ULONG ulIfState); /*67*/
#if (IPSEC_YES == IPSEC_PROFILE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_CheckEasyVpnAddrConflict)(ULONG ulTunnelDest, UCHAR *pszFQDN,
                                                        UCHAR *pszPeerName, ULONG ulVrfIndex);/*68*/
#endif
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    /* Multi-SeGw Feature */
    METHOD_(ULONG, pfIPSEC_UpdateIpsecPeer)(IPSEC_PEER_INFO_S *pstPeerInfo);              /*69*/
#endif
    METHOD_(ULONG, pfIPSEC_FindTdbEntriesByPeerNameAndUpdatePolicy)(UCHAR *pszIkePeerName, UCHAR ucUsePolicy);    /*70*/
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_Set_TdbUsage)(ULONG ulSpi, ULONG ulDstAddr, IN6ADDR_S *pstipv6Addr, UCHAR ucProto);/*71*/
#endif
};

/* Adapt  API`s */
DECLARE_INTERFACE (IIF_IPSEC_ComIntADAPT)
{
    IUNKNOWN_METHODS                                                    /*1*/

    METHOD_(ULONG, pfIPSEC_Auth_Alg_Init)(IPSEC_AUTH_HASH_S *pstAHNewHash,
                                            ULONG ulCount);             /*2*/

    METHOD_(ULONG, pfIPSEC_ESP_Auth_Alg_Init)(IPSEC_AUTH_HASH_S *pstAHNewHash,
                                            ULONG ulCount);             /*3*/

    METHOD_(ULONG, pfIPSEC_ESP_Enc_Alg_Init)(IPSEC_ENC_XFORM_S *pstESPNewXForm,
                                            ULONG ulCount);             /*4*/

    METHOD_(ULONG, pfIPSEC_RegHardwareCallbackApi)(
                          IPSEC_HARD_CALLBACK_S  *pfHardCallBackSet);   /*5*/

    METHOD_(ULONG, pfIPSEC_SetProductType)(ULONG ulProductType);        /*6*/

    METHOD_(ULONG, pfIPSEC_RegGenHardwareCallbackApi)(
                      IPSEC_GEN_HARD_CALLBACK_S  *pfGenHardCallBackSet); /*7*/

    /*B110-NP*/
    METHOD_ (ULONG, pfIPSEC_RegNPDownloadFailureCallbackAPI)
                    (NPDOWNLOADFAILURENOTIFY * pfNPDownloadFailureNotify); /*8*/

    /*Ipv6: Security Support*/
    METHOD_(ULONG, pfIPSEC_IPv6_RegCallbackAPI)(
                    IPSEC_IPV6_CALLBACKAPI_S *pstIPv6CallbackAPI);      /*9*/

    /* For DMVPN Support */
    METHOD_(ULONG, pfIPSEC_TUNNEL_RegCallbackAPI)(
                    IPSEC_TUNNEL_CALLBACKAPI_S *pstTUNNELCallbackAPI);  /*10*/

    METHOD_(ULONG, pfIPSEC_RegisterTunnelStatusNotify_Callback)
                (IPSEC_NOTIFY_TUNNEL_STATUS_CALLBACK_NEW pfFuncPtr, ULONG ulAppId);
};

/* Ipv6: Security Support */
/* Configuration  API`s */
DECLARE_INTERFACE (IIF_IPSEC_IPv6_ComIntCFG)
{
    IUNKNOWN_METHODS                                                        /*1*/

    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_CreateDelPolicy)(IPSEC_POLICY_S *pstPolicy,
                                    ULONG ulPolicyMode,
                                    ULONG ulOpMode);                        /*2*/

    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_SetDelTunnelPeerAddress)(
                                    IPSEC_POLICY_S *pstPolicy,
                                    IN6ADDR_S *pstPeerAddress,
                                    ULONG ulOpMode);                        /*3*/

    METHOD_(ULONG ,pfIPSEC_IPv6_Wrap_SetDelTunnelLocalAddress)(
                                    IPSEC_POLICY_S *pstPolicy,
                                    IN6ADDR_S *pstLocalAddress,
                                    ULONG ulOpMode);                        /*4*/

    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_MapInterface)(ULONG ulIfIndex,
                                    CHAR *szInMapName,
                                    ULONG ulOpMode,
                                    ULONG *pulErrMapNum);                   /*5*/

    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_GetFirst_SAIfHandle)(
                                    IPSEC_SHOW_SAINFO_S *pstSAInfo,
                                    IPSEC_SHOWSA_HANDLE_S *pstHandles,
                                    IPSEC_SHOW_INTERFACE_S *pstInterface);  /*6*/

    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_GetDelIPSECSAStat)(
                                    IPSEC_IPV6_AHSTAT_S *pstALLAHStat,
                                    IPSEC_IPV6_ESPSTAT_S *pstALLESPStat,
                                    IPSEC_STAT_S *pstIPSECStat,
                                    ULONG ulOpMode);                        /*7*/
/* HS: Pruned as balong dont use this API */
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_ClearSA)(IPSEC_POLICY_NAME_SEQ_S *pstPolicy,
                                    IPSEC6_SA_PARA_S *pstSAParameters,
                                    IN6ADDR_S *pstRemoteIpAddr,
                                    ULONG ulMode);                          /*8*/
#endif
    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_EncryptNAPackets)(ULONG ulOpMode);     /*9*/

    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_CreateDelPolicyTemplate)(
                                    CHAR *szTemplateName,
                                    ULONG ulSeqNumber, ULONG ulOpMode);     /*10*/

    /* Added for IPv6 HW stats r72335 */
    METHOD_(ULONG, pfIPSEC_IPV6_Wrap_GetDeleteHwStats)(IPSEC_GEN_HW_STAT_S *pstGenHwStat,
                                    ULONG ulOpMode);                        /*11*/

    METHOD_(ULONG, pfIPSEC_IPv6_RegisterTunnelStatusNotify_Callback)(
                                    IPSEC6_NOTIFY_TUNNEL_STATUS_CALLBACK_NEW pfFuncPtr,
                                    ULONG ulAppId);                         /*12*/

    /* Added for Peer stats r72335 */
    METHOD_(VOID, pfIPSEC_IPV6_Wrap_IPSEC_IPv6_GetPeerStats)(
                                    ULONG *pulIpsecPeerCount,
                                    ULONG *pulIpsecDynaPeerCount,
                                    ULONG *pulIpsecTotalPeerCount,
                                    ULONG *pulIpsecDpdTimerCount);          /*13*/

    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_SetDelV4CtrlTrafficOnV6)(
                                    UCHAR *szMapName,
                                    ULONG ulOpMode);                        /*14*/

    METHOD_(VOID, pfIPSEC_IPv6_GetPeerCount)();                             /*15*/
#if (IPSEC_YES == IPSEC_IKE_SUPPORT)
    METHOD_(ULONG, pfIPSEC_IPv6_DisplayAllPeers)(
                                    ULONG ulWaitListHandle,
                                    CHAR *pcBuffer,
                                    ULONG *pulFetchCount);                  /*16*/
#endif
};

/*Ipv6: Security Support*/
/* Functional  API`s */
DECLARE_INTERFACE (IIF_IPSEC_IPv6_ComIntFUN)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_Hook_IP_Output)(MBUF_S *pstMBuf); /*1*/

    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_InputPreCheck)(MBUF_S *pstMBuf);  /*2*/

    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_AH_ProtoInput)(MBUF_S **ppMBuf,
                                                ULONG *pulOff,
                                                ULONG ulNextHdr);      /*3*/

    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_ESP_ProtoInput)(MBUF_S **ppMBuf,
                                                ULONG *pulOff,
                                                ULONG ulNextHdr);      /*4*/

    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_InputPacketMsg_Handler)(ULONG *pulMsgBuf); /*5*/

    METHOD_(ULONG, pfIPSEC_IPv6_Wrap_OutputPacketMsg_Handler)(ULONG *pulMsgBuf); /*6*/

    METHOD_(ULONG, pfIPSEC_IPv6_HandleGenHWMsg)(ULONG ulNotifyType,
                                       IPSEC6_HW_COMMON_S *pstCommNotifyInfo,
                                       VOID* pvPacketInfo,
                                       IPSEC6_TdbIndex_S *pstTdbIndex); /*7*/

    METHOD_(ULONG, pfIPSEC_IPV6_Wrap_IPSEC_IPv6_HW_NotifyReceive) (     /*8*/
                        ULONG ulNotifyType, IPSEC6_HW_COMMON_S *pstCommNotifyInfo,
                        VOID* pvPacketInfo, IPSEC6_TdbIndex_S *pstTdbIndex);

};

#ifdef __cplusplus
}
#endif
#endif  /* _IIPSEC_INC_H */
