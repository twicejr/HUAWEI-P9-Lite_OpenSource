/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipoa_fun.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2008-07-24
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-07-24   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _IPOA_FUN_H_
#define _IPOA_FUN_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


typedef enum tagATM_SHOW_TYPE
{
    ATM_SHOW_MAP_OF_PVC = 1,    /* 显示本PVC的MAP信息 */
    ATM_SHOW_MAP_OF_INTF,       /* 显示本接口的MAP信息 */
    ATM_SHOW_MAP_OF_CB,         /* 显示本CB的MAP信息 */
    ATM_SHOW_MAP_OF_BOARD       /* 显示本板的MAP信息 */

}ATM_SHOW_TYPE_EN;


/* ipoa_intf */
extern ULONG IPOA_InitVtable( VOID **ppVtable);
extern VOID IPoA_Init( VOID );
extern ULONG IPOA_InitIPoAIf ( IFNET_S *pIf, ULONG ulPosition, ULONG *pulRet );
extern ULONG IPOA_StartIpoaIf (IFNET_S *pIf, ULONG ulPosition, ULONG *pulRet );
extern ULONG IPOA_LinkHideCmd (IFNET_S *pIf, ULONG ulPosition, ULONG *pulRet );
extern ULONG IPOA_IPoAFree ( IFNET_S *pIf, ULONG ulPosition, ULONG *pulRet );
extern ULONG IPOA_DelCtlBlk ( IFNET_S * pstIf );
extern IPOA_PVC_S * IPOA_HashGetPVC (IPOA_CB_S *pstIpoaCB, USHORT usVPI, USHORT usVCI);
extern ULONG IPOA_MapHashIndex (USHORT usVPI, USHORT usVCI);
extern VOID IPOA_PVCHashAdd (IPOA_CB_S *pstIpoaCB, IPOA_PVC_S *pstPVC);
extern VOID IPOA_PVCHashDelete (IPOA_CB_S *pstIpoaCB, IPOA_PVC_S  *pstPVC);
extern ULONG IPOA_InitCB (IFNET_S * pstIf);
extern ULONG IPOA_AddIntf (IPOA_CB_S * pstIpoaCB, IFNET_S *pstIf);
extern ULONG IPOA_DeleteIntf (IFNET_S *pstIf);
extern VOID IPOA_ShutDown (IFNET_S *pstIf, BOOL_T bShutDown);
extern VOID IPOA_VC_IntfStateChange (IPOA_INTERFACE_S *pstIpoaIntf);
extern VOID IPOA_IpAddress(IFNET_S *pstIf, ULONG ulCmd);
extern ULONG IPOA_NetIOCtrl (IFNET_S *pstIf, ULONG ulCmd, CHAR *pcData);
extern VOID IPOA_PhyStateChange (IPOA_CB_S *pstIpoaCB, UCHAR ucState);
extern ULONG IPOA_LlcIOCtrl (IFNET_S *pstIf, ULONG ulCmd, CHAR *pcData);
/* Modify for DTS2011021504820, by zhaoyue 00171897/xiaoqingping xkf34549, at 2011-02-22. 修改原因: 设置IPOA路由状态 */
extern VOID IPOA_MapStateChange(IPOA_MAP_IP_S   *pstIPMap);


/*ipoa_fun*/

extern ULONG IPOA_CreatePvc(IPOA_CFG_PVC_S *pstPvcTable, IPOA_INTERFACE_S *pstIpoaIntf);
extern ULONG IPOA_FillValueToPvc(IPOA_CFG_PVC_S *pstPvcTable, IFNET_S *pstIf);
extern ULONG IPOA_CfgPVCEncapType(IPOA_INTERFACE_S * pstIpoaIntf, USHORT usVPI, USHORT usVCI,UCHAR ucEncType);
extern VOID IPOA_DeletePVC(IPOA_PVC_S *pstPVC);
extern ULONG IPOA_CFG_CreateMap(IPOA_CFG_MAP_S *pstMapTable, IFNET_S *pstIf);
extern ULONG IPOA_AssembleBuffer(ULONG ulPvcFlag, VOID *pstCB, ULONG ulDebugFlag1,
                                        CHAR *pcBuffer,ULONG *pulMaxLen);
extern ULONG IPOA_BufferOutPut (CHAR *pcTemple, CHAR *pcBuffer, ULONG *pulMaxLen);
extern VOID * IPOA_CFG_GetFirst (UCHAR ucGetFirstType, ULONG ulIfIndex,USHORT usVPI, USHORT usVCI);
extern VOID * IPOA_CFG_GetNext (UCHAR ucGetNextType, VOID *pCurNode);
extern VOID *IPOA_GetMapOfPVC (IPOA_PVC_S * pstPVC);                


/*ipoa_pvc*/
extern IPOA_PVC_S *IPOA_SearchPVCToInsert (DLL_S *pstDllList, IPOA_PVC_S * pstInsPVC);
extern IPOA_PVC_S * IPOA_SearchPVCByVpiVci(DLL_S *pstDllList,USHORT usVPI, USHORT usVCI);
extern IPOA_PVC_S * IPOA_VC_CreatePVC (IPOA_INTERFACE_S *pstIpoaIntf, USHORT usVPI, USHORT usVCI,ULONG ulType);
extern VOID IPOA_VC_StateChange (IPOA_PVC_S *pstPVC);
extern VOID IPOA_ChangePVCState (IPOA_PVC_S *pstPVC);
/*ipoa_map*/
extern IPOA_MAP_IP_S *IPOA_GetMap (IPOA_PVC_S * pstPVC, UCHAR ucType, ULONG ulIPAddr);
extern IPOA_MAP_IP_S * IPOA_CreateMap (IPOA_PVC_S * pstPVC, UCHAR ucType, ULONG ulIPAddr, 
                                        ULONG ulMask,USHORT usInArpMinute, BOOL_T bBroadcast);

extern ULONG IPOA_DeleteMap (IPOA_PVC_S * pstPVC, UCHAR ucType, ULONG ulIPAddr);
extern IPOA_MAP_IP_S *IPOA_SearchMapByIP (IPOA_INTERFACE_S * pstIpoaIntf, IPOA_PVC_S * pstPVC, ULONG ulIPAddr, UCHAR ucType);
extern ULONG IPOA_PPI_GetMapByIp(ULONG ulIfIndex, ULONG ulIpAddr, IPOA_MAP_IP_S *pstIpoaMap);


/*ipoa_pkt*/
extern ENQUEUE_PF IPOA_Receive (IFNET_S *pstIf,  MBUF_S *pstMBuf);
extern ULONG  IPOA_NetSend (MBUF_S * pstMBuf);
extern ULONG IPOA_PhyTransmit (IPOA_PVC_S *pstPVC, MBUF_S *pstMBuf, UCHAR ucPacType);
extern ULONG IPOA_VC_QueProc (MBUF_S *pstMBuf);
extern ULONG IPOA_VC_QueDropProc (MBUF_S *pstMBuf, ULONG ulCmd, CHAR *pcData);
extern ENQUEUE_PF IPOA_VC_Receive (IPOA_PVC_S *pstPVC, MBUF_S *pstMBuf);
extern ULONG IPOA_EncapPkt (IPOA_PVC_S * pstPVC,
                      MBUF_S *pstMBuf, 
                      UCHAR ucPacType, 
                      ULONG ulDebug,
                      IPOA_DBG_PKT_INFO_S * pstDbgPktInfo
                      ); 
extern ULONG IPOA_DeEncapPkt (IPOA_PVC_S * pstPVC, MBUF_S *pstMBuf, UCHAR * pucPacType,
                        ULONG ulDebug, IPOA_DBG_PKT_INFO_S * pstDbgPktInfo); 
extern ULONG IPOA_InterpretType (MBUF_S *pstMBuf, UCHAR ucEncType,ULONG *pulPktHeadLen, UCHAR *pucPacType);



/*ipoa_vlink*/
extern ULONG IPOA_VLinkCtrl (IPOA_MAP_IP_S  * pstIPMap, UCHAR ucCmd);

/* Modify for DTS2011021504820, by zhaoyue 00171897/xiaoqingping xkf34549, at 2011-02-22. 修改原因: 设置IPOA路由状态 */
extern ULONG IPOA_Ppi_CtrlUpdate (IPOA_MAP_IP_S  * pstIPMap, UCHAR ucCmd);
extern VOID IPOA_UpdateDstIPAddr(IPOA_PVC_S * pstPVC,ULONG ulIPAddr);
extern VOID IPOA_ResetInARP (IPOA_MAP_IP_S  * pstIPMap, USHORT usMinute);
extern ULONG IPOA_PVCCtrlVlinkRoute (IPOA_MAP_IP_S  * pstIPMap, UCHAR ucCmd);

/*ipoa arp*/
extern ULONG IPOA_INARP_CtrlInARP (IPOA_PVC_S *pstPVC, UCHAR ucCmd);
extern VOID IPOA_INARP_TimeOutProc (VOID * pulIfIndex);
extern ULONG IPOA_INARP_Send (IPOA_PVC_S * pstPVC, UCHAR ucType, ULONG ulDstIPAddr);
extern ULONG  IPOA_INARP_Receive (IPOA_PVC_S *pstPVC, MBUF_S * pstMBuf);
extern ULONG IPOA_SynthesizePacket (UCHAR *pucData, ULONG ulSourceIPAddr,
                                      ULONG ulDstIPAddr, UCHAR ucType,
                                      BOOL_T bDebug,
                                      IPOA_DBG_PKT_INFO_S *pstDbgPktInfo);

extern ULONG IPOA_InterpretPacket (MBUF_S * pstMBuf, ULONG *pulDstIPAddr,
                                 UCHAR *pucType, BOOL_T bDebug,
                                 IPOA_DBG_PKT_INFO_S *pstDbgPktInfo);


/*ipoa dbg*/
extern VOID IPOA_CFG_DbgPacket (IPOA_PVC_S *pstPVC, IPOA_DBG_PKT_INFO_S *pstDbgPktInfo);
extern ULONG IPOA_CFG_DbgError (IPOA_INTERFACE_S *pstIpoaIntf, IPOA_PVC_S *pstPVC, ULONG ulErrCode, ULONG ulData);
extern VOID IPOA_FormIPAddrStr (ULONG ulIPAddr, CHAR * pcIPAddr);
extern ULONG IPOA_CFG_DbgEvent (IPOA_INTERFACE_S *pstIpoaIntf, IPOA_PVC_S *pstPVC, CHAR *pcEventStr);



/*ipoa waitlist*/

extern ULONG CFGAPI_COMM_Display_Init();
extern ULONG CFGAPI_COMM_AllocDisplayNode(ULONG *pulSessionID);
extern ULONG CFGAPI_COMM_FreeDisplayNode(ULONG ulSessionID);
extern ULONG CFGAPI_COMM_DisplayUserData_Set(ULONG ulSessionID, VOID *pstShowNode);
extern ULONG CFGAPI_COMM_DisplayUserData_Get(ULONG ulSessionID, VOID **ppNodeInfoDest);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IPOA_FUN_H_ */


