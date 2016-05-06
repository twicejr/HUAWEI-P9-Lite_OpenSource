/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                        IIFNET.H
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/06/25 
 *        Author: luohanjun
 *   Description: IFNET接口描述
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/06/25      luohanjun       Create
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *  2007/11/22      f54882          For SWID00244,删除组件接口pfIF_GetIfIndexbyName
 *
 ************************************************************************/

#ifndef _TCPIP_IIFNET_H
#define _TCPIP_IIFNET_H

#ifdef __cplusplus
extern "C"{
#endif
                 
DECLARE_INTERFACE(IIF_IFNET_ComIntFUN)
{
    IUNKNOWN_METHODS
    /**********************接口创建、删除类方法**************************/
    METHOD_( IFNET_S*, pfIF_CreateByDev) (DEVLINK_S * pstDev,ULONG ulIndex);    /*根据设备创建接口*/
    METHOD_( ULONG, pfIF_Delete)( IFNET_S *pIf );
    METHOD_( ULONG, pfIF_Shutdown)( IFNET_S *pIf );
    METHOD_( ULONG, pfIF_NoShutdown)( IFNET_S *pIf );
    METHOD_( ULONG, pfIF_LinkIoCtl)(ULONG ulIfIndex, ULONG ulCmdIndex, CHAR *pData);
    METHOD_( ULONG, pfIF_LinkReceived)( ULONG ulIfIndex, MBUF_S * pMBuf);
    METHOD_( IFNET_S*, pfIF_DynamicCreateIfNet) (CHAR * szFullName, ULONG ulSubType); /*根据名称、索引创建接口*/

    METHOD_( IFNET_S*, pfIF_DynamicCreateL2IfNet) (CHAR * szFullName, ULONG ulSubType); /*根据名称、索引创建接口*/
    
    METHOD_( IFNET_S*, pfIF_CreateSubIf) (CHAR * szSubName , ULONG ulIndex, ULONG ulSubType, IFNET_S * pMain); 

    METHOD_( IFNET_S*, pfIF_CreateVA) (ULONG ulVTIndex,ULONG ulClassID,ULONG ulIfIndex, ULONG ulChannelId);
    METHOD_( ULONG, pfIF_InitIfByLayer) (IFNET_S *pIf,ULONG ulPos);  /*触发指定层的初始化*/
    METHOD_( ULONG, pfIF_BuildrunByLayer) (IFNET_S *pIf,ULONG ulPos);  /*触发指定层的buildrun操作*/
    METHOD_( ULONG, pfIF_CmdHideByLayer) (IFNET_S *pIf,ULONG ulPos); 
    
    /**********************定位类方法**************************/
    METHOD_( IFNET_S*, pfIF_GetIfByIndex) (ULONG ulIfIndex); /*根据索引获取接口指针*/
    METHOD_( ULONG, pfIF_GetSlotByIndex) (ULONG ulIfIndex); /*根据索引获取接口所在槽号*/
    METHOD_( ULONG, pfIF_GetLineProtoByIndex) (ULONG ulIfIndex);  /*根据索引获取接口链路层协议*/
    METHOD_( ULONG, pfIF_BoardIsUp) (ULONG ulSlot ); /*判断板是否UP*/
    METHOD_( ULONG, pfIF_IsVisible) ( IFNET_S * pIf ); /*判断接口是否可见*/
    METHOD_( ULONG, pfIF_IsConfigure) ( IFNET_S * pIf ); 
    METHOD_( ULONG, pfIF_IsTempIf) ( ULONG ulIndex); 
    METHOD_( ULONG, pfIF_IsTempIfByPtr) ( IFNET_S * pIf );  /*判断接口是否是临时接口  建议使用本函数---luohanjun*/
    METHOD_( LONG, pfIF_IsSameBoard) ( ULONG ulIndex);  /*判断接口是否在本板*/
    METHOD_( LONG, pfIF_JudgeNameOrder) ( CHAR * Sour,CHAR * if_pName);
    METHOD_( ULONG, pfIF_GetNextUpBoardID) (ULONG ulSlot );
    METHOD_( IFNET_S*, pfIF_GetConfigHead) ( );
    METHOD_( IFNET_S*, pfIF_GetIfByFullName) (CHAR * szFull );
    METHOD_( IFNET_S*, pfIF_GetMainIf) ( IFNET_S* pIf);
    METHOD_( ULONG, pfIF_GetFirstIfIndex) ( ULONG * pIndex);
    METHOD_( ULONG, pfIF_GetNextIfIndex) ( ULONG ulIndex, ULONG * pNextIndex);
    METHOD_( IFNET_S*, pfIF_FindFirstSubIfnet) ( IFNET_S* pMain);
    METHOD_( IFNET_S*, pfIF_FindNextSubIfnet) ( IFNET_S* pSub);
    METHOD_( IFNET_S*, pfIF_FindSubIfWithName) (CHAR * if_pName);        /*根据子接口名查找子接口*/
    METHOD_( IFNET_S*, pfIF_FindWithMainName) (CHAR * if_pName); /*根据主接口名查找接口*/
    METHOD_( IFNET_S*, pfIF_FindWithSubIndex) (IFNET_S * pIf, ULONG ulSubIndex ); 
    METHOD_( IFNET_S*, pfIF_SearchIfFromChain) ( IFNET_S* pIf , ULONG ulSearch);
    METHOD_( IFNET_S*, pfIF_SearchIfFromChainFun) ( IFNET_S* pIf , ULONG ulSearch);
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_( ULONG, pfIF_GetVrfByIfIndex) ( ULONG ulIndex, ULONG * pVrfIndex);
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

    /**********************报文处理类函数**************************/
    METHOD_( ULONG, pfIF_Output) ( MBUF_S * pMbuf);
    
    /**********************操作维护类函数**************************/

    /*封装前预处理*/
    METHOD_( ULONG, pfIF_BeforeEncap) ( IFNET_S *pIf , ULONG *ulShutdown, ULONG ulExecID, ULONG ulNewProtocol);
    METHOD_( ULONG, pfIF_AfterEncap) ( IFNET_S *pIf , ULONG ulShutdown ); /*封装后处理*/
    METHOD_( VOID, pfIF_SetLastChangeTime) ( IFNET_S * pIf ); 

    METHOD_( ULONG, pfIF_GetConfigMTU) ( IFNET_S * pIf ); 
    METHOD_( VOID , pfIF_SelectMtu) (IFNET_S * pIf, ULONG * pMin, ULONG * pMax ); 
    METHOD_( ULONG, pfIF_GetMTU)( IFNET_S* pIf );
    METHOD_( ULONG, pfIF_SetMTU)( IFNET_S* pMtuIf, ULONG ulMTU );

    METHOD_(ULONG, pfIF_SetBandWidthValue)(ULONG ulSlot, IFNET_S* pIf, ULONG ulValue);
    METHOD_(ULONG, pfIF_SetDescript)( IFNET_S* pIf, CHAR * pDescript );

    METHOD_( ULONG, pfIF_GetKeepAliveValue)(IFNET_S* pIf, ULONG* pValue);
    METHOD_( ULONG, pfIF_SetKeepAliveValue)(IFNET_S* pIf, ULONG ulValue);

    /**********************HOOK类方法**************************/
    METHOD_( ULONG, pfIF_AnalyseIfName)( IFNAME_S * pstIfName,CHAR * szName );

    METHOD_( ULONG, pfIF_HookForQuery)(ULONG ulFunc, CHAR * szType, CHAR * szInput, ULONG pHelpVec);

    METHOD_( ULONG, pfIF_VLINK_IoCtl)(VOID * pVLinkStatus, VOID * pCB);
    METHOD_( ULONG, pfIF_VLINK6_IoCtl)(VOID * pVLinkStatus, VOID * pCB);
    METHOD_( VOID*, pfIF_VLINK_GetCB)(ULONG ulVlinkIndex);              /* VLINK_GetCB */
    METHOD_( ULONG, pfIF_VLINK_SetCB)(ULONG ulVlinkIndex, VOID * pCB);    /* VLINK_SetCB */

    /**********************通知函数注册类**************************/
    METHOD_( ULONG, pfIF_RegisterNotifyFn)(/*ULONG ulModule,*/ULONG ulType, ULONG ulPriority, void* pfNotifyFn); 
    METHOD_(ULONG, pfIF_UnRegisterNotifyFn)(/*ULONG ulModule,*/ULONG ulType,void* pfNotifyFn);

    METHOD_(ULONG, pfIF_OpenIfConfigEntry)(UINTPTR *pulWaitListHandle);
    METHOD_(ULONG, pfIF_GetIfConfigEntry)(UINTPTR ulEntryWaitList, IFNET_S * pstIfConfig);
    METHOD_(ULONG, pfIF_CloseIfConfigEntry)(UINTPTR ulWaitListHandle);  /*VISP V100R005   x43050 2006-5-9 Interface Check  */

    METHOD_(ULONG, pfIF_IsTrunkPort)(IFNET_S* pIf);
    METHOD_(ULONG, pfIF_VTIsBinded)(IFNET_S *pstIf, ULONG *pulEthIfIndex);
    METHOD_(ULONG, pfIF_HA_BatchBackup)();
    METHOD_(ULONG, pfIF_HA_Input)(UCHAR *pBuf, ULONG ulMsgLen);
    METHOD_(ULONG, pfIF_HA_Smooth)();
    METHOD_(ULONG, pfTCPIP_HA_VerifyInterface)(ULONG ulIfIndex); 
    METHOD_(ULONG, pfIF_GetIfFullNameByIndex)(ULONG ulIfIndex, CHAR *pszIfName);
    METHOD_(ULONG, pfIF_GetIfIndexByFullName)(CHAR *pszIfName, ULONG *pulIfIndex);
    METHOD_(IFNET_S*, pfIF_GetIfByTypeNum)(ULONG ulIfType, ULONG ulFirstDim, ULONG ulSecondDim, ULONG ulThirdDim);
    METHOD_(ULONG, pfIF_HA_Clean)();
    METHOD_(VOID, pfIF_DealIoCtlMsgs)();

    METHOD_(ULONG, pfIF_SetIsisFlag)( ULONG ulIfIndex ,ULONG ulFlag );
    METHOD_(ULONG, pfIF_GetIsisFlag)( ULONG ulIfIndex ,ULONG *pulFlag );

    METHOD_(ULONG, pfIF_RegisterVlanCheckFnc)(IF_VLANCHECKFN pfIfHookFunc);
    
    /* 创建二层端口 */
    METHOD_( IFNET_S *, pfIF_CreateByDevForPort)(DEVLINK_S * pstDev ,ULONG ulIndex, ULONG ulL2Flag);

    METHOD_( VOID, pfIF_Health_BatchCheckup)();
    METHOD_(DEVLINK_S *, pfIF_FindDevByIfIndex)(DEVLINK_S *pstDevLink, ULONG ulIfIndex);
    METHOD_(ULONG, pfIF_SetDevLink)(DEVLINK_S *pstDevLink);
    METHOD_(ULONG, pfIF_GetDevLink)(ULONG ulIfIndex, DEVLINK_S *pstDevLink);

    METHOD_(ULONG, pfIF_SetIfEventDebugSwitch)(ULONG ulValue);
    METHOD_(ULONG, pfIF_GetIfEventDebugSwitch)(ULONG *pulValue);

    METHOD_(ULONG, pfIF_GetISIStatus)(ULONG ulIfIndex, ULONG *pulIfState);    
    METHOD_(ULONG, pfIF_GetAllIfIndex)(ULONG *pulIfNum, ULONG *pulIfIndex);    
    METHOD_(ULONG, pfIF_GetIfNum)(ULONG *pulIfNum);    

    METHOD_(IFNET_S*, pfIF_GetIfByTypeNumSub)(ULONG ulIfType, ULONG ulFirstDim, ULONG ulSecondDim, ULONG ulThirdDim,ULONG ulSubPort);

    /*Added by apurba for VRF6*/
    METHOD_( ULONG, pfIF_GetVrf6ByIfIndex) ( ULONG ulIndex, ULONG * pVrfIndex);
    METHOD_( ULONG, pfIF_Tunn_SetTunnelPara) (ULONG ulIfIndex, TCPIP_TUNNEL_IF_PPI_S *pstTunnelPPI);
    METHOD_( ULONG, pfIF_Tunn_DelTunnelPara) (ULONG ulIfIndex);
    METHOD_( ULONG, pfIF_Tunn_GetIfInfoByIfIndex) (ULONG ulIfIndex, TCPIP_TUNNEL_IF_PPI_S *pstTunnelPPI);
    METHOD_( ULONG, pfIF_Tunn_ShowIfByName) (CHAR *szIfName);
};


/*公共接口声明*/

/*
 * 注意: -----add by luohanjun
 * 由于一个组件可以作为接口的上层、链路层、设备层，按参数ulPosition区分
 * 其中参数ulPosition需要按如下定义进行判断
 * 0: 上层,一般指IPv4，只能执行上层操作；
 * 1: 上层,一般指IPv6，只能执行IPv6操作；
 * 2: 链路层，只能执行链路层的操作；
 * 3: 设备层，只能执行设备层的操作；
 */
DECLARE_INTERFACE(IIF_IFS_IntFun) /*外部组件IFNET公共接口*/
{
    IUNKNOWN_METHODS

    /* 创建各层自有数据，并初始化 */
    METHOD_(ULONG , pfIF_InitIF) (IFNET_S* pIf, ULONG ulPosition, ULONG* pulRet);

    /* 启动各层，触发UP事件，执行各层组件的buildrun，通过控制函数进行事件传递等操作，可以不执行任何操作。*/
    METHOD_(ULONG , pfIF_BuildrunIF) (IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);

    /* 接口命令屏蔽，主要是针对链路层，其他层必须提供空函数。*/
    METHOD_(ULONG , pfIF_HideCommand) (IFNET_S* pIf, ULONG ulPosition, ULONG* pulRet);

    /*释放指定层控制块。*/
    METHOD_(ULONG , pfIF_FreeControlBlock) (IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);

};
/*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
ULONG IF_QueryInterface(IUnknown * This, COMP_IID iid, VOID **ndvObj);


#ifdef __cplusplus
}
#endif

#endif /* _TCPIP_IIFNET_H */

