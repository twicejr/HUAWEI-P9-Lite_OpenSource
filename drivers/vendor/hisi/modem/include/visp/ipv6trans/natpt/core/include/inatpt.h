/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             Inatpt.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-07-03
 *  Author:             Desh   (VRPv5 IPv6 Team) 
 *  Document:           NATPT include file for public
 *  Function Description:This file contains all the function,macro and structure definition. 
 *                        
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  2003-7-3    Desh(70216)      Creation 
 *  2003-11-24  Archana P V      For Defect BYAD04227
 *  2003-12-2  Usha             For Defect BYAD04881 
 *  2003-12-16 Archana P V      For Defect BYAD05088
 *  2004-01-27 Archana P V      for Defect BYAD07343
 *  2004-01-27 Archana P V      for Defect BYAD07342
 *  2004-02-09 Archana P V      for Defect BYAD08095
 *  2004-02-04 Usha             for Defect BYAD07830
 *  2004-03-15 Archana P V      for Defect BYAD09118 
 ************************************************************************/




#ifndef _INATPT_H
#define _INATPT_H


#ifdef  __cplusplus
extern  "C"{
#endif

/*----------------------------------------------*
 * Header Files                
 *----------------------------------------------*/
/*Define the component ID  */
#define CID_IPV6_NATPT  (CID_VISP_IPV6_BASE + 8)


/* Define all the Interface identifiers*/
#define IID_IPV6_NATPT_ComINTF_V6STK  (IID_VISP_IPV6_BASE + 80)
#define IID_IPV6_NATPT_ComINTF_V4STK  (IID_VISP_IPV6_BASE + 81)
#define IID_IPV6_NATPT_ComINTF_HSB    (IID_VISP_IPV6_BASE + 82)
#define IID_IPV6_NATPT_ComINTF_SSA    (IID_VISP_IPV6_BASE + 83)
#define IID_IPV6_NATPT_ComINTF_CFG    (IID_VISP_IPV6_BASE + 84)


  

/*----------------------------------------------*
 * External Variables            
 *----------------------------------------------*/

/*----------------------------------------------*
 * Global Variables    
 *----------------------------------------------*/

  /* define the Init com interface*/

/* define the Init com interface*/

DECLARE_INTERFACE (IIF_IPV6_NATPT_ComINTF_HA) 
{
    IUNKNOWN_METHODS
};

DECLARE_INTERFACE (IIF_IPV6_NATPT_ComINTF_SSA) 
{
    IUNKNOWN_METHODS
    METHOD_(BOOL_T, pfNATPT_AM_DeleteAllDynamic)();
    METHOD_(ULONG, pfNATPT_MGMT_IFDelete)(ULONG ulIfnetIndex); 
};

DECLARE_INTERFACE (IIF_IPV6_NATPT_ComINTF_V4STK) 
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfNATPT_InIPv4) (MBUF_S *pMBuf) ;
    METHOD_(ULONG, pfNATPT_AAM_ARP_CheckPoolAddr)(ULONG ulV4Addr, ULONG ulIfIndex);
    METHOD_(ULONG ,pfNATPT_AAM_AddrChange)(ULONG ulIfIndex,USHORT usEvent,ULONG ulNewV4Addr);
    METHOD_(ULONG, pfNATPT_IPv4OutputRegCallback)(MBUF_S *pstMBuf);
};


DECLARE_INTERFACE(IIF_IPV6_NATPT_ComINTF_V6STK) 
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfNATPT_InIPv6) (MBUF_S *pMBuf);
    METHOD_(ULONG, pfNATPT_IPv6OutputRegCallback)(MBUF_S *pstMBuf);
};

DECLARE_INTERFACE(IIF_IPV6_NATPT_ComINTF_CFG) 
{
    IUNKNOWN_METHODS
    METHOD_( ULONG, pfNATPT_AM_SetObject_AddrMap )
            (IN6ADDR_S  stV6Addr, ULONG  ulV4Addr, USHORT usFlag ,UCHAR ucAddrInfoFlag);
    METHOD_( ULONG ,pfNATPT_AM_SetObject_StaticV4DPATMap)
            (IN6ADDR_S stV6Addr, ULONG  ulV4Addr,USHORT ulV6Port , USHORT ulV4Port ,
             UCHAR ucPro, USHORT usFlag);
    METHOD_( ULONG ,pfNATPT_MM_SetObject_TimeOut) 
          ( ULONG ulTimeoutType , ULONG  ulTimeOutValue);
    METHOD_(  ULONG ,pfNATPT_MM_SetObject_MaxSession)
           (ULONG ulMaxSessionNo , USHORT  usFlag);
    METHOD_( ULONG, pfNATPT_MM_SetObject_ClearSessions)();


    /*Add for defect BYAD03928*/
    METHOD_(ULONG, pfNATPT_MM_SetObject_ClearStatistics)();
    METHOD_( ULONG,pfNATPT_MM_OpenObject_Session)
            ( ULONG *pulWaitListHandle,ULONG ulIndex );
    METHOD_( ULONG,pfNATPT_MM_OpenObject_FragMap)
            ( ULONG *pulWaitListHandle,ULONG ulIndex );
    METHOD_( ULONG ,pfNATPT_MM_GetObject_Session_Bulk)
              (ULONG ulWaitListHandle,ULONG ulObjInstance,ULONG ulNum,
                                  ULONG ulNumOfEntryWanted,
                                  ULONG *pulNumOfEntryReturn,
                                  UCHAR ucPro,
                                  NATPT_HASH_SESSION_S* ppstSessionBuffer);
    METHOD_( ULONG ,pfNATPT_MM_GetObject_Frag_Bulk)
              (ULONG ulWaitListHandle,ULONG ulObjInstance,ULONG ulNum,
                                  ULONG ulNumOfEntryWanted,
                                  ULONG *pulNumOfEntryReturn,
                                  NATPT_HASH_FRAG_S* ppstSessionBuffer);

    METHOD_( ULONG ,pfNATPT_MM_GetObject_TimeOut)
          (NATPT_TIMEOUT_S** ppstNatptTimeOut);

    METHOD_( ULONG ,pfNATPT_MM_GetObject_MaxSession)
          ();
    METHOD_( ULONG,pfNATPT_MM_OpenObject_AddrMap)
            ( ULONG *pulWaitListHandle );

    METHOD_(ULONG, pfNATPT_MM_GetObject_AddrMap_Bulk)
            (ULONG ulWaitListHandle, ULONG ulObjInstance, ULONG ulNum,  
             ULONG ulNumOfEntryWanted, ULONG *pulNumOfEntryReturn, NATPT_HASH_ADDRMAP_S* pstAddrMapBuffer);

    METHOD_( ULONG,pfNATPT_MM_OpenObject_DPAT)
                ( ULONG *pulWaitListHandle );

    METHOD_(ULONG, pfNATPT_MM_GetObject_DPATMap_Bulk)
            (ULONG ulWaitListHandle, ULONG ulObjInstance, ULONG ulNum,  
             ULONG ulNumOfEntryWanted, ULONG *pulNumOfEntryReturn, NATPT_HASH_DPAT_S* pstDPATMapBuffer);
    

    METHOD_( ULONG,pfNATPT_MM_CloseObject)
            (ULONG* pulWaitListHandle);
    METHOD_( ULONG,pfNATPT_MM_GetStatistics )
           (NATPT_SM_STATS_S** ppstStats,
                           USHORT* pusStaticMappings,
                           USHORT* pusDynamicMappings,
                           ULONG* pulDPATMappings,
                           ULONG* pulIfIndexList,
                           ULONG ulSlot) ;

    METHOD_(  ULONG ,pfNATPT_AAM_SetObject_DyanmicV6Mapping )
          ( ULONG ulACLListNo,CHAR *pcACLName, IN6ADDR_S stNATPTPrefix, 
            USHORT usAddrGroupNo,  USHORT usPATFlag, ULONG ulIfnetIndex, 
            CHAR *pcIfName, USHORT usFlag, ULONG ulMappingType, ULONG ulIfV4Addr);

    METHOD_( ULONG ,pfNATPT_AAM_SetObject_V4ACLPrefix)
          (ULONG ulACLListNo, CHAR  *pcACLName, IN6ADDR_S  stNATPTPrefix, ULONG ulMappingType, USHORT usFlag);
    METHOD_( ULONG ,pfNATPT_AAM_SetObject_NATPTPrefix)
            (IN6ADDR_S stNATPTPrefix, CHAR *pcIfName, 
            ULONG ulIfIndex, ULONG ulNextHopAddr,
            ULONG ulPrefixType, USHORT usFlag);
    METHOD_(  ULONG,pfNATPT_AAM_GetObject_AddressGroup_First ) 
           (NATPTAddrGroupIndex_S  **ppstAddrGrp);
    METHOD_( ULONG ,pfNATPT_AAM_GetObject_AddressGroup_Next) 
          (NATPTAddrGroupIndex_S *pstLastIndex,NATPTAddrGroupIndex_S **ppstAddrGrp);
    METHOD_(  ULONG, pfNATPT_AAM_GetObject_DynamicV6Bound_First ) 
          (NATPTv6Access_S    **ppstAccess);
    METHOD_( ULONG ,pfNATPT_AAM_GetObject_DynamicV6Bound_Next)
          (NATPTv6Access_S *pstLastIndex, NATPTv6Access_S  **ppstV6Access);  
    METHOD_(  ULONG ,pfNATPT_AAM_GetObject_DynamicV4Bound_First )
           (NATPTv4Access_S   **ppstAclToPrefix);
    METHOD_(  ULONG, pfNATPT_AAM_GetObject_DynamicV4Bound_Next)
          (NATPTv4Access_S  *pstLastIndex,NATPTv4Access_S  **ppstV4Access);
    METHOD_(  ULONG ,pfNATPT_AAM_GetObject_Prefix_First )
           (NATPTPrefixInfo_S **ppstPrefixInfo);
    METHOD_(  ULONG, pfNATPT_AAM_GetObject_Prefix_Next)
          (NATPTPrefixInfo_S *pstLastIndex,NATPTPrefixInfo_S **ppstPrefixInfo);
    METHOD_(ULONG, pfNATPT_AAM_SetObject_AddressGroup)
            (ULONG ulStartAddr,ULONG ulEndAddr, 
             USHORT usPoolNumber, USHORT usFlag) ;
    METHOD_(ULONG, pfNATPT_MGMT_SetObject_Enable) 
          (ULONG ulIfnetIndex,  USHORT usFlag);
    METHOD_(ULONG, pfNATPT_MGMT_SetObject_DebugFlag)
          (UCHAR ucDebugSign , ULONG ulSlotNo, USHORT usFlag);

    METHOD_(ULONG,pfNATPT_SetResSpecs_ADDRMAP) (SPECS_RES_VALUE_S *pstResSpec) ;
    METHOD_(ULONG, pfNATPT_SetResSpecs_MAXSESSIONS) (SPECS_RES_VALUE_S *pstResSpec) ;
    METHOD_(ULONG,pfNATPT_SetResSpecs_MAXDPAT)  (SPECS_RES_VALUE_S *pstResSpec);
    METHOD_(ULONG,pfNATPT_SetFunSpecs_DPATEnable)  (SPECS_FUN_VALUE_S *pstResSpec) ;
    METHOD_(ULONG,pfNATPT_SetFunSpecs_PATEnable) (SPECS_FUN_VALUE_S *pstResSpec) ;

    METHOD_(ULONG,pfNATPT_ChgResSpecs_ADDRMAP) (SPECS_RES_VALUE_S *pstResSpec,ULONG ulEvent);
    METHOD_(ULONG,pfNATPT_ChgResSpecs_MAXDPAT) (SPECS_RES_VALUE_S *pstResSpec,ULONG ulEvent);
    METHOD_(ULONG,pfNATPT_ChgResSpecs_MAXSESSION) (SPECS_RES_VALUE_S *pstResSpec,ULONG ulEvent);
    /*For Defect BYAD05088*/
    METHOD_(ULONG,pfNATPT_AAM_LCS_UpdateHandlerPAT) (ULONG ulEvent,SPECS_FUN_VALUE_S *pstFunSpec);  
    METHOD_(ULONG,pfNATPT_MM_LCS_UpdateHandlerDPAT) (ULONG ulEvent,SPECS_FUN_VALUE_S *pstFunSpec);

    METHOD_(ULONG, pfNATPT_Core_Init) (COM_ID_INFO_S *pstComInfo,ULONG  ulComLen);
    METHOD_(ULONG, pfNATPT_Core_DeInit) ();   
    METHOD_(ULONG, pfNATPT_Register_NonComInt) (NATPT_NonCompINT_S* pstNATPT_NonCompINT );
    METHOD_(ULONG, pfNATPT_SetModuleInfo)( NATPT_MOD_INFO_S *pstMInfo);
    METHOD_(ULONG, pfNATPT_Activate_Com)();
    /* for defect BYAD04881 */
    METHOD_(ULONG, pfNATPT_MGMT_GetObject_Debug) 
    (UCHAR *pucNatptDebug,ULONG ulIfnetIndex);

    METHOD_(ULONG, pfNATPT_PT_SetObject_TrafClass)
    (UCHAR ucTrafFlag, USHORT usFlag);
    METHOD_(ULONG, pfNATPT_PT_GetTrafClass)
        (UCHAR *pucTrafFlag);
    /* end of defect BYAD04881 */
    /* For defect BYAD07830 */
    METHOD_(ULONG, pfNATPT_MGMT_NoDebugAll)(); 
    /* End of defect BYAD07830 */ 

    /* Added for defect BYAD11433 */
    METHOD_(ULONG, pfNATPT_MGMT_SetObject_AllowPrvAddr)
    (USHORT usFlag);

    METHOD_(ULONG, pfNATPT_MGMT_GetObject_AllowPrvAddr)
        (UCHAR *pucAllowAddr);
    /* End of defect BYAD11433 */
};

typedef struct tag_NATPTINT_OBJ_S
{
    IIF_IPV6_NATPT_ComINTF_CFG  *pComINTF_CFG;
    IIF_IPV6_NATPT_ComINTF_HA   *pComINTF_HA;
    IIF_IPV6_NATPT_ComINTF_SSA  *pComINTF_SSA;
    IIF_IPV6_NATPT_ComINTF_V4STK    *pComINTF_V4STK;
    IIF_IPV6_NATPT_ComINTF_V6STK    *pComINTF_V6STK;

} NATPT_INT_OBJ_S;

#ifdef  __cplusplus
}
#endif 
#endif

