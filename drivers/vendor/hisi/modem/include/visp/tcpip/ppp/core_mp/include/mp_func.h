/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                               mp_func.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2005-09-15
 *        Author: YaoChengliang
 *   Description: MP模块的函数声明
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2005-09-15      YaoChengliang   Create
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *  2006-07-12      ZhuKun          Adjust for A82D03485
 *  2007-02-01      f54882          HDLC自动侦听非标需求开发(同步问题单A82D11804) 
 *  2008-08-13      f54882          for BC3D00221,同步问题单BC3D00185
 *
 *************************************************************************/

#ifndef _MP_FUNC_H_
#define _MP_FUNC_H_

#ifdef  __cplusplus
extern "C"{
#endif


/* mp_init.c */
/*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
ULONG MP_Init_Com(COM_ID_INFO_S *pstComInfo, ULONG ulComLen);
ULONG MP_Active_Com(VOID);
ULONG MP_SetModuleInfo(MP_MOD_INFO_S *pstMInfo);
ULONG MP_RegShellApi(MP_SHELL_CALLBACK_S *pstShellApi);
ULONG MP_InitData();


/* mp_bind.c */
VOID MP_PPI_UPDATE(IFNET_S* pstSonIf, ULONG ulppiOpr, IFNET_S* pstFatherIf);
VOID  MP_AppendChannel( PPPINFO_S *pstPppInfo );
ULONG MP_FindTemplate(PPPINFO_S* pstPppInfo) ;
ULONG MP_FindFather(ULONG ulTemplateIndex,  MP_DISCR_INFO_S *pstDiscrInfo) ;
ULONG MP_BindToFather(PPPINFO_S *pstSonPppInfo, 
                      ULONG ulFatherIndex, 
                      ULONG ulTemplateIndex) ;
ULONG MP_AddFatherInfoToTemplate(ULONG ulFatherIndex, 
                                 ULONG ulTemplateIndex, 
                                 MP_DISCR_INFO_S *pstDiscrInfo) ;
ULONG MP_CreateFather(PPPINFO_S *pstSonPppInfo, ULONG ulTemplateIndex) ;
ULONG MP_InitFather(PPPINFO_S *pstSonPppInfo, 
                    ULONG ulFatherIndex, 
                    ULONG ulTemplateIndex) ;
ULONG MP_AddSonInfoToFather(ULONG ulFatherIndex, ULONG ulSonIndex) ;
VOID  MP_DeleteChannel( PPPINFO_S *pstPppInfo ) ;
VOID  MP_DeleteSonInfoFromFather(ULONG ulSonIndex, ULONG ulFatherIndex) ;
VOID  MP_DeleteFatherInfoFromTemplate( ULONG ulFatherIndex, ULONG ulTemplateIndex ) ;
LONG  MP_FatherIndexValCmp( VOID *pVal, DLL_NODE_S *pstNode ) ;
LONG  MP_FatherIndexValCmp_IFIndex( VOID *pVal, DLL_NODE_S *pstNode ) ;
VOID  MP_DeleteFatherChannel( IFNET_S *pstFatherIf ) ;
VOID  MPChannelChange_QosChange( IFNET_S *pstFatherIf);
VOID  MP_AppendSonChannel(ULONG ulIfIndex);
VOID  MP_DeleteSonChannel(ULONG ulIfIndex);
ULONG MP_AddSonInfoToFather_Check(ULONG ulFatherIndex, ULONG ulSonIndex);

VOID  MP_GroupFatherChannelDown( IFNET_S *pstIf );
VOID  MP_GroupAppendChannel( IFNET_S *pIfnet );
VOID  MP_GroupPhyInit(IFNET_S *pIf);
ULONG MP_GroupPhyIOCtl(UINTPTR ulPhyLink, ULONG ulCmdIndex, char *pData);
ULONG MP_GroupExistSon( IFNET_S *pIf );
ULONG MP_GroupEncapsulate(IFNET_S * pIf);

VOID MP_NotifyNcpUpSublinkLowLimit(PPPINFO_S* pstPppInfo);

/* mp_rcv.c */
ULONG MP_Input( MBUF_S *pstMbuf );
ULONG MP_GetMpHdrInfo( UCHAR ucWeRcvShortHdr,
                       UCHAR *pucFlag,
                       UCHAR *pucClass,
                       ULONG *pulSeqNumber, 
                       UCHAR *pucData );
ULONG MP_SearchBegin( MP_FRAGMENT_S *pstFrag, 
                      ULONG ulCurPos,
                      ULONG ulFragBufLen, 
                      UCHAR ucWeRcvShortHdr );
ULONG MP_SearchEnd( MP_FRAGMENT_S *pstFrag, 
                    ULONG ulCurPos,
                    ULONG ulFragBufLen, 
                    UCHAR ucWeRcvShortHdr );
MBUF_S *MP_AssembleBuf( ULONG ulBeginPos, 
                        ULONG ulEndPos,
                        MP_FRAGMENT_S *pstFrag, 
                        ULONG ulFragBufLen );
ENQUEUE_PF MP_ISLInput( PPPINFO_S *pstPppInfo, 
                        MBUF_S *pstMbuf,
                        USHORT usProtocol, 
                        ULONG ulOffset );
ENQUEUE_PF MP_FastMpInput( MBUF_S *pstMbuf, ULONG ulFatherChannelIfIndex, ULONG *pulRetVal);
ENQUEUE_PF MP_SonISLInput(ULONG ulIfIndex, MBUF_S *pstMbuf,\
            USHORT usProtocol, ULONG ulOffset );
ULONG MP_Reorder( IFNET_S *pstFatherIf, ULONG ulSeqNumber, UCHAR ucClass);
VOID MP_ReconstructBuf( PPPINFO_S *pstPppInfo, ULONG ulBeginPos, ULONG ulEndPos, 
                        ULONG ulFragBufLen, UCHAR ucClass );
LONG CircularSpaceCompare(ULONG a, ULONG b, ULONG ulHalfSpace);

ULONG MP_RestorePrefix(PPPINFO_S* pstPppInfo,MBUF_S* pstMbuf,UCHAR ucClass);

/* mp_snd.c */
ULONG MP_Output( PPPINFO_S *pstPppInfo, MBUF_S *pstMbuf,  USHORT usProtocol );
ULONG MP_GetFragmentNum( ULONG ulPacketLen, USHORT usMpBindNum, USHORT usMinFragLen );
ULONG MP_Transmit( PPPINFO_S *pstPppInfo, MBUF_S *pstMbuf, USHORT usProtocol );
ULONG MP_MPQOS_SonTransmit(IFNET_S *pstIf, ULONG ulPointerToDcb, MBUF_S *pstMBuf);
ULONG MP_Fragment(IFNET_S *pstIfnet, MBUF_S *pstMBuf, USHORT usProtocol, UCHAR ucClass);
ULONG MP_EncapPPP(IFNET_S *pstIfnet, MBUF_S *pstMbuf, USHORT usProtocol);
ULONG MP_LFI_GetFragmentNum( ULONG ulPacketLen, USHORT usMaxFragLFI );
ULONG MP_FatherOutput(IFNET_S *pstIfnet, MBUF_S *pstMbuf,  USHORT usProtocol );

ULONG MP_RemovePrefix(PPPINFO_S* pstPppInfo,MBUF_S* pstMbuf,UCHAR ucClass, 
    USHORT usProtocol,ULONG* pulPrefixE);

/* mp_cfg.c */
ULONG MP_PppMultilinkInterleave( ULONG ulIfIndex, ULONG ulSetYes );
ULONG MP_PppMultilinkFragmentDelay( ULONG ulIfIndex ,ULONG ulDelay, ULONG ulReset);
ULONG MP_AddUser( UCHAR *pucUserName, ULONG ulVirtualTemplateNum );
ULONG MP_DelUser( UCHAR *pucUserName );
ULONG MP_AddNode(ULONG ulIfIndex,ULONG ulVirtualTemplateNum );
VOID  MP_DelNode(ULONG ulIfIndex);
ULONG MP_BindToVT (ULONG ulIfIndex,ULONG ulVTNum );


LONG  MP_UserNameValCmp( VOID *pVal, DLL_NODE_S *pstNode );
LONG  MP_IfIndexValCmp( VOID *pVal, DLL_NODE_S *pstNode );
ULONG MP_PppMultilink( ULONG ulIfIndex );
ULONG MP_NoPppMultilink( ULONG ulIfIndex);
ULONG MP_MultilinkMaxBind(ULONG ulIfIndex, ULONG ulMaxBindNum, ULONG ulReset );
ULONG MP_MultilinkFragment(ULONG ulIfIndex, ULONG usMinFragLen, ULONG ulReset );
ULONG MP_PppMultilinkReorderWindow(ULONG ulIfIndex, ULONG ulSetYes);
ULONG MP_IsCfgDiscriminator(ULONG ulIfIndex);
ULONG MP_PppMultilinkDiscriminator( ULONG ulIfIndex, ULONG ulSetYes );
ULONG MP_SendCfgMsgToMpFather( IFNET_S *pstIf, ULONG  ulOID, ULONG ulPara );
ULONG MP_MultilinkBindMode ( ULONG ulIfIndex, ULONG ulBindMode);
ULONG MP_NoMultilinkBindMode ( ULONG ulIfIndex);

VOID  MP_DbgDisplayEvents( CHAR *szOutString );
VOID  MP_DbgDisplayPackets( ULONG ulFatherIfIndex, 
                            ULONG ulPacketLen,
                            CHAR cPrintNum, 
                            ULONG ulSeqNumber, 
                            UCHAR bWeRcvShortHdr,
                            UCHAR ucFlag, 
                            UCHAR ucClass );
VOID MP_DbgOutputPackets( ULONG ulIfIndex,
                            ULONG ulPacketLen,
                            UCHAR * pucData,
                            UCHAR bSheRcvShortHdr );
INT32  MP_PrintSysTime( CHAR *pcBuf );
ULONG MP_IFDelete(ULONG ulIfIndex);

ULONG MP_AddNode_MPGROUP(ULONG ulIfIndex,CHAR  * ucMpGroupName );
ULONG MP_DelNode_MPGROUP(ULONG ulIfIndex,CHAR  * ucMpGroupName );
ULONG MP_BindToMpGroup (ULONG ulIfIndex, CHAR* szMpGroupName);

ULONG MP_Str2PrefixE ( UCHAR *pszPreEInfo, UCHAR aucClsPrefix[], ULONG ulStrLen );
ULONG MP_PppMultilinkMc ( ULONG ulIfIndex, ULONG ulSetYes );
ULONG MP_SetMcMhf ( ULONG ulIfIndex, UCHAR ucCode, UCHAR ucClass, ULONG ulReset );
ULONG MP_PppMultilinkPrefixE ( ULONG ulIfIndex, ULONG ulSetYes );
ULONG MP_AddMcPrefixE ( ULONG ulIfIndex, UCHAR ucClass, UCHAR *pszPreInfo );
ULONG MP_DelMcPrefixE ( ULONG ulIfIndex, UCHAR ucClass );
ULONG MP_PppMultilinkMc_PT ( ULONG ulIfIndex, ULONG ulSetYes );
ULONG MP_SetMcMhf_PT ( ULONG ulIfIndex, UCHAR ucCode, UCHAR ucClass, ULONG ulReset );
ULONG MP_PppMultilinkPrefixE_PT ( ULONG ulIfIndex, ULONG ulSetYes );
ULONG MP_AddMcPrefixE_PT ( ULONG ulIfIndex, UCHAR ucClass, UCHAR *pszPreEInfo );
ULONG MP_DelMcPrefixE_PT ( ULONG ulIfIndex, UCHAR ucClass );

ULONG MP_PppMultilinkSsnhf ( ULONG ulIfIndex, ULONG ulSetYes );
ULONG MP_PppMultilinkSsnhf_PT ( ULONG ulIfIndex, ULONG ulSetYes );
/* End of addition */
ULONG MP_SetEndpointDiscriminator(ULONG ulIfIndex, ULONG ulDiscriminator, ULONG ulReset);

/* mp_disp.c */
UCHAR MP_ConvertIfStatusToMpSubLinkStatus (UCHAR ucIfStatus);
ULONG MP_Group_GetMpInfo (ULONG ulMpGroupIfIndex,MP_DISP_INFO_S *pstMpDispInfo);
ULONG MP_Group_GetSubIndex(CHAR *pszMpGroupName, MP_SUB_INDEX_S *pSubIndexInfo);
ULONG  MP_GetFirstVAMpInfo (ULONG ulVTIfIndex, \
                                   MP_DISP_INFO_S *pstMpDispInfo, ULONG * pulFirstVAIfIndex);
ULONG  MP_GetNextVAMpInfo (ULONG ulVTIfIndex,ULONG ulCurrentVAIfIndex, \
                                   MP_DISP_INFO_S *pstMpDispInfo, ULONG *pulNextVAIfIndex);

ULONG MP_GetPrefixEInfo ( ULONG ulIfIndex, MC_PREFIXE_S *pstPrefixEInfo );
ULONG MP_GetMcConfig(ULONG ulIfIndex, MC_CONFIG_S *pstMcCfg);
ULONG MP_GetPrefixEInfo_PT( ULONG ulIfIndex, MC_PREFIXE_S *pstPrefixEInfo );
ULONG MP_GetMcConfig_PT(ULONG ulIfIndex, MC_CONFIG_S *pstMcCfg);
/* End of addition */

/* mp_fun.c */
ULONG  MP_IF_GetSlot(ULONG ulIfnetidx);  
VOID MP_SetDiscr(IFNET_S *pstIf, UCHAR *pucdiscr_addr);
ULONG  MP_GetFatherIfIndex(IFNET_S* pstIfnet);
VOID   MP_IncrInterleaveNum(IFNET_S *pstIfnet);
ULONG  MP_IsEnableLFI(IFNET_S* pstIfnet);
VOID   MP_IncrInterleaveNum(IFNET_S *pstIfnet);
PPPINFO_S *MP_GetPppInfoByIndex(ULONG ulIfIndex);
ULONG MP_GetDiscr(ULONG ulIfIndex, UCHAR *pucDiscr_addr, UCHAR *pucClass, UCHAR *pucLength);
ULONG  MP_RcvEventFromPPP(IFNET_S*pstIf, ULONG ulEvent, CHAR *pPara);
ULONG  MP_OpenUserInfoObject(UINTPTR *pulWaitListHandle);
ULONG  MP_GetUserInfo(UINTPTR ulHandle, 
                        CHAR szUserName[MP_USERNAME_LEN + 2], ULONG *pulVTNo);
ULONG  MP_CloseObject(UINTPTR ulWaitListHandle);
USHORT MP_GetUserNameNum();
ULONG  MP_GetStatistic(ULONG ulMpIndex, MPSTATISTIC_S *pstStatistic);
ULONG  MP_ResetStatistic(ULONG ulMpIndex);
ULONG  MP_JudgeIfType(ULONG ulIfIndex);/*Add by Q62011 for BC3D01354*/

/* v1r6添加的优先级保护接口 */
ULONG MP_NoPppMultilink_PT(ULONG ulIfIndex);
ULONG MP_BindToMpGroup_PT(ULONG ulIfIndex, CHAR *szMpGroupName);
ULONG MP_MultilinkMaxBind_PT(ULONG ulIfIndex, ULONG ulMaxBindNum, ULONG ulReset);
ULONG MP_MultilinkFragment_PT(ULONG ulIfIndex, ULONG usMinFragLen, ULONG ulReset);
ULONG MP_PppMultilinkReorderWindow_PT(ULONG ulIfIndex, ULONG ulSetYes);
ULONG MP_PppMultilinkDiscriminator_PT(ULONG ulIfIndex, ULONG ulSetYes);
ULONG MP_PppMultilinkInterleave_PT(ULONG ulIfIndex, ULONG ulSetYes);
ULONG MP_PppMultilinkFragmentDelay_PT(ULONG ulIfIndex, ULONG ulDelay, ULONG ulReset);

ULONG MP_SetUpSublinkLowLimit_PT(ULONG ulIfIndex, ULONG ulValue );
ULONG MP_GetUpSublinkLowLimit_PT(ULONG ulIfIndex, ULONG *pulValue );

ULONG MP_OpenMpGroupList(UINTPTR *pulWaitlistHandle);
ULONG MP_GetMpGroup(UINTPTR ulWaitlistHandle, MPGROUP_LIST_INFO_S**ppstMpGroupListInfo);
ULONG MP_CloseMpGroupList(UINTPTR ulWaitlistHandle);

/* PPP funcitons, MP can call them directly */
extern VOID PPP_DebugPacket_Verbose_Char(UCHAR *pPacket ,ULONG ulMBufLen,\
                    USHORT usProtocol ,ULONG ulIsCut);

extern VOID PPP_RegSubModuleCallBack(ULONG ulSubMod, PPP_NotifySubMod_FuncPtr pfFun);


/* Some extern function declaration */
extern ULONG getMainboardId();
extern ULONG getSelfBoardId();
extern ULONG VOS_T_GetSelfID( ULONG * pulTaskID);
extern ULONG VOS_T_GetName(ULONG ulTaskID, CHAR cTaskName[4]);
extern LONG IF_JudgeNameOrder(CHAR * Sour,CHAR * if_pName);
extern IFNET_S* IF_CreateMpVirtualAccess( ULONG ulVTIndex, CHAR *pcData, ULONG ulDataLen );
extern ULONG IF_GetSlotByIndex(ULONG ulIfIndex);
extern IFNET_S *IF_GetIfByIndex(ULONG ulIfIndex);
extern IFNET_S * IF_GetIfByFullName(CHAR * szFull);
extern ULONG IF_AnalyseIfName(IFNAME_S * pstIfName, CHAR * szName);

/* add by ybo for MP LQM*/
ULONG MP_GetLqmCfgInfo(ULONG ulIfIndex,ULONG *pulLqmEnable,USHORT *pusLqmPeriod);

/* Added by z43740 for A82D20089:MP重组窗口扩大,2007-09-13 */
extern ULONG MP_SetReorderWindowTimes(ULONG ulTimes);
extern VOID  MP_IN_SetReorderWindowTimes(ULONG ulTimes);
extern ULONG MP_GetReorderWindowTimes(VOID);
/* End of addition */

/*add by yebo*/
extern ULONG TCPIP_CloneTemplateQue(ULONG ulFatherIndex, ULONG ulTemplateIfIndex,UCHAR ucMC,UCHAR ucClassNum);
extern VOID TCPIP_DelFatherFromQos(ULONG ulFatherIndex);
extern BOOL_T TCPIP_IfCanSendPkt(ULONG ulIfIndex);
extern ULONG TCPIP_MpGroupQueInit(ULONG ulIfIndex, BOOL_T bLfiConfigFlag,UCHAR ucMC, UCHAR ucClassNum);
extern ULONG TCPIP_MPQOS_TransmitDone(ULONG ulIfIndex, UINTPTR ulPointerToDcb, MBUF_S * pstMBuf);
extern ULONG TCPIP_QM_Transmit(ULONG ulIfIndex, MBUF_S *pstMBuf, USHORT usProtocol );
extern VOID TCPIP_QosChange( ULONG ulFatherIndex, ULONG *pulLfiConfigFlag);
extern ULONG TCPIP_QOS_TransmitDone(ULONG ulIfIndex, ULONG ulPointerToDcb, MBUF_S * pstMBuf);

/* Added by z43740 for TR报文发送增强,2009-04-09 */
extern ULONG MP_SetDiscReq(ULONG ulIfIndex, ULONG ulSetYes);
extern ULONG MP_GetDiscReq(ULONG ulIfIndex, ULONG *pulSetYes);
extern ULONG MP_SetDiscReq_PT(ULONG ulIfIndex, ULONG ulSetYes);
extern ULONG MP_GetDiscReq_PT(ULONG ulIfIndex, ULONG *pulSetYes);

extern ULONG MP_IsCfgDiscardReq(ULONG ulIfIndex);
extern ULONG MP_GetGoodSonChannel(ULONG ulIfIndex, ULONG *pulSonIfIndex);
extern ULONG MP_GetNeedDownSonChannel(ULONG ulIfIndex, ULONG ulOurMagicNumber, ULONG ulHisMagicNumber, ULONG *pulSonIfIndex);
/* End of addition */

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _MP_FUNC_H_ */
