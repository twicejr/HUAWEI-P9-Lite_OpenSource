/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                                 imp.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2005-09-15
 *        Author: YaoChengliang
 *   Description: Defines All Interfaces of the MP Component
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2005-09-15      YaoChengliang   Create
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *  2007-02-01      f54882          HDLC自动侦听非标需求开发(同步问题单A82D11804) 
 *  2008-08-13      f54882          for BC3D00221,同步问题单BC3D00185
 *
 *************************************************************************/
 
#ifndef _IMP_H_
#define _IMP_H_

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_INTERFACE (IIF_MP_ComIntFUN)
{
    IUNKNOWN_METHODS
        
    METHOD_(VOID, pfMP_AppendSonChannel)(ULONG ulIfIndex);
    METHOD_(VOID, pfMP_DeleteSonChannel)(ULONG ulIfIndex);
    
    METHOD_(ULONG, pfMP_FatherOutput)(IFNET_S *pstIfnet, 
                                        MBUF_S * pstMbuf, USHORT usProtocol);
    METHOD_(ULONG, pfMP_MPQOS_SonTransmit)(IFNET_S * pstIf, 
                                     ULONG ulPointerToDcb, MBUF_S * pstMBuf);
    METHOD_(ENQUEUE_PF, pfMP_SonISLInput)(ULONG ulIfIndex, MBUF_S * pstMbuf,\
                                            USHORT usProtocol, ULONG ulOffset);
    METHOD_(ULONG, pfMP_Input)(MBUF_S * pstMbuf);
        
    METHOD_(ULONG, pfMP_GroupExistSon)(IFNET_S * pIf);
    METHOD_(VOID, pfMP_GroupPhyInit)(IFNET_S * pIf);
    METHOD_(ULONG, pfMP_IFDelete)(ULONG ulIfIndex);

    METHOD_(ULONG, pfMP_EncapPPP)(IFNET_S *pstIfnet, MBUF_S *pstMbuf, USHORT usProtocol);
    /* End of modification */
    METHOD_(ULONG, pfMP_Fragment)(IFNET_S *pstIfnet,
                                    MBUF_S *pstMBuf, USHORT usProtocol, UCHAR ucClass);
    METHOD_(ULONG, pfMP_GetFatherIfIndex)(IFNET_S * pstIfnet);
    METHOD_(ULONG, pfMP_IsEnableLFI)(IFNET_S * pstIfnet);
    METHOD_(VOID, pfMP_IncrInterleaveNum)(IFNET_S * pstIfnet);
    
    METHOD_(ULONG, pfMP_Group_GetMpInfo)(ULONG ulMpGroupIfIndex, 
                                              MP_DISP_INFO_S * pstMpDispInfo);    
    METHOD_(ULONG, pfMP_GetFirstVAMpInfo)(ULONG ulVTIfIndex, 
        MP_DISP_INFO_S * pstMpDispInfo, ULONG * pulFirstVAIfIndex);
    METHOD_(ULONG, pfMP_GetNextVAMpInfo)(ULONG ulVTIfIndex, 
                                        ULONG ulCurrentVAIfIndex,
                                        MP_DISP_INFO_S * pstMpDispInfo, 
                                        ULONG * pulNextVAIfIndex);

    METHOD_(ULONG, pfMP_OpenUserInfoObject)(UINTPTR *pulWaitListHandle);
    METHOD_(ULONG, pfMP_CloseObject)(UINTPTR ulWaitListHandle);
    METHOD_(ULONG, pfMP_GetUserInfo)(UINTPTR ulHandle,\
        CHAR szUserName[MP_USERNAME_LEN + 2], ULONG *pulVTNo);
    METHOD_(USHORT, pfMP_GetUserNameNum)();
    
    METHOD_(ULONG, pfMP_GetDiscr)(ULONG ulIfIndex, UCHAR *pucDiscr_addr, \
                                       UCHAR *pucClass, UCHAR *pucLength);
    METHOD_(ULONG, pfMP_IsCfgDiscriminator)(ULONG ulIfIndex);

    METHOD_(ULONG, pfMP_GetStatistic)(ULONG ulMpIndex, 
                                      MPSTATISTIC_S *pstStatistic);
    METHOD_(ULONG, pfMP_ResetStatistic)(ULONG ulMpIndex);
    
    METHOD_(ULONG, pfMP_NoPppMultilink)(ULONG ulIfIndex);
    
    METHOD_(ULONG, pfMP_GetPrefixEInfo) (ULONG ulIfIndex, MC_PREFIXE_S *pstPrefixEInfo);
    METHOD_(ULONG, pfMP_GetMcConfig) (ULONG ulIfIndex, MC_CONFIG_S *pstMcCfg);
    METHOD_(ULONG, pfMP_DelNode_MPGROUP)(ULONG ulIfIndex, CHAR *ucMpGroupName);
    METHOD_(ULONG, pfMP_AddSonInfoToFather)(ULONG ulFatherIndex, ULONG ulSonIndex);
    METHOD_(ULONG, pfMP_GroupEncapsulate)(IFNET_S * pIf);
    METHOD_(DLL_S *,pfMP_GetMpgroupList)();
    /* End of addition */
    /*add by ybo for mp Lqm*/
    METHOD_(ULONG, pfMP_GetLqmCfgInfo)(ULONG ulIfIndex,ULONG *pulLqmEnable,USHORT *pusLqmPeriod);
    
    METHOD_(ULONG, pfMP_OpenMpGroupList)( UINTPTR *pulWaitlistHandle);
    METHOD_(ULONG, pfMP_GetMpGroup)( UINTPTR ulWaitlistHandle, MPGROUP_LIST_INFO_S**ppstMpGroupListInfo);
    METHOD_(ULONG, pfMP_CloseMpGroupList)( UINTPTR ulWaitlistHandle);
    METHOD_(ULONG, pfMP_Group_GetSubIndex)(CHAR *pszMpGroupName, MP_SUB_INDEX_S *pSubIndexInfo);  

    METHOD_(VOID, pfMP_PPI_UPDATE)(IFNET_S* pstSonIf, ULONG ulppiOpr, IFNET_S* pstFatherIf);
    
    METHOD_(VOID, pfMP_Health_BatchCheckup)();
    METHOD_(ULONG, pfMP_LastWord_BatchCheckup)(CHAR *pstBuf, ULONG *pulLastWordLen);
    METHOD_(ULONG, pfMP_LastWord_StatisticCheckup)(CHAR *pstBuf, ULONG *pulLastWordLen);
    METHOD_(ULONG, pfMP_JudgeIfType)(ULONG ulIfIndex);/*Add by Q62011 for BC3D01354*/
    /* Added by z43740 for TR报文发送增强, 2009-04-09 */
    METHOD_(ULONG, pfMP_IsCfgDiscardReq)(ULONG ulIfIndex);
    METHOD_(ULONG, pfMP_GetGoodSonChannel)(ULONG ulIfIndex, ULONG *pulSonIfIndex);
    METHOD_(ULONG, pfMP_GetNeedDownSonChannel)(ULONG ulIfIndex,ULONG ulOurMagicNumber, \
        ULONG ulHisMagicNumber, ULONG *pulSonIfIndex);
    /* End of addition */
};

DECLARE_INTERFACE (IIF_MP_ComIntCFG)
{
    IUNKNOWN_METHODS

    METHOD_(ULONG, pfMP_Init_Com)(COM_ID_INFO_S * pstComInfo, ULONG ulComLen);
    METHOD_(ULONG, pfMP_Active_Com)(VOID);
    METHOD_(ULONG, pfMP_SetModuleInfo)(MP_MOD_INFO_S * pstMInfo);
    METHOD_(ULONG, pfMP_RegShellApi)(MP_SHELL_CALLBACK_S * pstShellApi);

    METHOD_(ULONG, pfMP_PppMultilink)(ULONG ulIfIndex);
    METHOD_(ULONG, pfMP_NoPppMultilink)(ULONG ulIfIndex);
    METHOD_(ULONG, pfMP_BindToVT)(ULONG ulIfIndex, ULONG ulVTNum);
    METHOD_(ULONG, pfMP_BindToMpGroup)(ULONG ulIfIndex, CHAR* szMpGroupName);
    METHOD_(ULONG, pfMP_AddUser)(UCHAR * pucUserName, 
                                         ULONG ulVirtualTemplateNum);
    METHOD_(ULONG, pfMP_DelUser)(UCHAR * pucUserName);
    METHOD_(ULONG, pfMP_MultilinkBindMode)(ULONG ulIfIndex, ULONG ulBindMode);
    METHOD_(ULONG, pfMP_NoMultilinkBindMode)(ULONG ulIfIndex);

    METHOD_(ULONG, pfMP_MultilinkMaxBind)(ULONG ulIfIndex, ULONG ulMaxBindNum, ULONG ulReset);    
    METHOD_(ULONG, pfMP_MultilinkFragment)(ULONG ulIfIndex, ULONG ulMinFragLen, ULONG ulReset);
    METHOD_(ULONG, pfMP_PppMultilinkReorderWindow)(ULONG ulIfIndex, ULONG ulSetYes);
    METHOD_(ULONG, pfMP_PppMultilinkDiscriminator)(ULONG ulIfIndex, ULONG ulSetYes);
    METHOD_(ULONG, pfMP_PppMultilinkInterleave)(ULONG ulIfIndex, ULONG ulSetYes);
    METHOD_(ULONG, pfMP_PppMultilinkFragmentDelay)(ULONG ulIfIndex, ULONG ulDelay, ULONG ulReset);
    
    METHOD_( ULONG, pfMP_PppMultilinkMc) (ULONG ulIfIndex, ULONG ulSetYes);
    METHOD_( ULONG, pfMP_SetMcMhf) (ULONG ulIfIndex, UCHAR ucCode, UCHAR ucClass, ULONG ulReset);  
    METHOD_( ULONG, pfMP_PppMultilinkPrefixE) (ULONG ulIfIndex, ULONG ulSetYes);
    METHOD_( ULONG, pfMP_AddMcPrefixE) (ULONG ulIfIndex, UCHAR ucClass, UCHAR *pszPrefixInfo);
    METHOD_( ULONG, pfMP_DelMcPrefixE) (ULONG ulIfIndex, UCHAR ucClass);
    METHOD_( ULONG, pfMP_PppMultilinkSsnhf) (ULONG ulIfIndex, ULONG ulSetYes);
    /* End of addition */
    /* Added by z43740 for A82D20089: 重组窗口扩大,2007-09-13 */
    METHOD_(ULONG, pfMP_SetReorderWindowTimes)(ULONG ulTimes);
    METHOD_(VOID,  pfMP_IN_SetReorderWindowTimes)(ULONG ulTimes);
    METHOD_(ULONG, pfMP_GetReorderWindowTimes)(VOID);
    /*End of addition */
    METHOD_(ULONG, pfMP_SetEndpointDiscriminator)(ULONG ulIfIndex, ULONG ulDiscriminator, ULONG ulReset);
    /* End of addition */
    METHOD_( ULONG, pfMP_SetUpSublinkLowLimit) (ULONG ulIfIndex, ULONG ulValue );
    METHOD_( ULONG, pfMP_GetUpSublinkLowLimit) (ULONG ulIfIndex, ULONG *pulValue );
    /* Added by z43740 for TR报文发送增强, 2009-04-09 */
    METHOD_( ULONG, pfMP_SetDiscReq)(ULONG ulIfIndex, ULONG ulSetYes);
    METHOD_( ULONG, pfMP_GetDiscReq)(ULONG ulIfIndex, ULONG *pulSetYes);
    /* End of addition */
};
 

DECLARE_INTERFACE (IIF_MP_ComIntSSA)
{
    IUNKNOWN_METHODS
};

typedef struct tagMP_IntObj
{
    struct IIF_MP_ComIntFUN    *pCompIntFUN;
    struct IIF_MP_ComIntCFG    *pCompIntCFG;
    struct IIF_MP_ComIntSSA    *pCompIntSSA;
}MP_INT_OBJ_S;


#ifdef __cplusplus
}
#endif

#endif 
