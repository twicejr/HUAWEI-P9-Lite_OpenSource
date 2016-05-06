/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_INIT.H 
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/03/28  
 *        Author: luohanjun
 *   Description: Ifnet初始化头文件
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/03/28      luohanjun       Create
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *
 ************************************************************************/


#ifndef _TCPIP_IF_INIT_H_
#define _TCPIP_IF_INIT_H_

#ifdef  __cplusplus
extern "C"{
#endif


/*  define in if_init.c  ************************************************/
extern IFNET_S * IF_CreateByDev( DEVLINK_S *pstDev,ULONG ulIndex );
IFNET_S * IF_DynamicCreateIfNet_PT( CHAR * szFullName, ULONG ulSubType );
extern IFNET_S * IF_DynamicCreateIfNet( CHAR *szFullName, ULONG ulSubType );
extern IFNET_S* IF_CreateLogicIFCommon(IF_CLASS_S* pstIfClass,IFNAME_S * pstIfName,ULONG ulIndex, ULONG ulL2Flag, ULONG ulVrfIndex);
extern IFNET_S * IF_DynamicCreateL2IfNet( CHAR * szFullName, ULONG ulSubType);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
extern IFNET_S * IF_DynamicCreateIfNetByVrf( CHAR * szFullName, ULONG ulSubType ,ULONG ulVrfIndex);
/*extern IFNET_S* IF_CreateLogicIF(IF_CLASS_S *pstIfClass,IFNAME_S *pstIfName,ULONG ulIndex);*/
extern IFNET_S* IF_CreateLogicIF(IF_CLASS_S *pstIfClass,IFNAME_S *pstIfName,ULONG ulIndex,ULONG ulVrfIndex);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
extern IFNET_S * IF_CreateSubIf( CHAR *szSubName, ULONG ulIndex, ULONG ulSubType, IFNET_S *pMain );
extern IFNET_S* IF_CreateVA(ULONG ulVTIndex, ULONG ulClassID, ULONG ulIfIndex, ULONG ulChannelId);
extern VOID IF_InitialIf(IFNET_S *pIf);
extern VOID IF_ChangeEncap( IFNET_S *pIf );
extern ULONG IF_TopoIF(IFNET_S *pIf,IFNAME_S *pstIfName, ULONG ulIndex);
extern ULONG IF_InitIFByClass(IFNET_S *pIf, IF_CLASS_S *pstIfClass);
extern ULONG IF_InitIfByLayer(IFNET_S *pIf, ULONG ulPos);
extern ULONG IF_BuildrunByLayer(IFNET_S *pIf, ULONG ulPos);      
extern ULONG IF_CmdHideByLayer(IFNET_S *pIf, ULONG ulPos);       
extern ULONG IF_FreeBlockByClass(IFNET_S *pIf, IF_CLASS_S *pstIfClass);
extern ULONG IF_ChangeL2PortEncap(IFNET_S *pIf);
extern ULONG IF_ChangeL2TrunkPortEncap(IFNET_S *pIf);


/*  define in if_class.c  ***********************************************/
extern ULONG IF_Init_ClassParam(ULONG ulCount,ULONG ulMaxTypeEnum);
extern ULONG IF_Register_IFClass(IF_CLASS_S *pstIfClass);
extern IF_CLASS_S* IF_FindClassByType(ULONG ulType);
extern IF_CLASS_S* IF_FindClassByName(const CHAR *szName);
extern IF_CLASS_S* IF_FindClassByIfName(CHAR *szIfName);

extern ULONG (*g_pfIntfStateChangeNotifyPolicyRt)(ULONG, ULONG, VOID*) ;

ULONG IF_RegisterProductParam(VRP_INTERFACE_S* pstProduct);
ULONG IF_Init_Com();

ULONG IF_RegisterNotifyFn(ULONG ulType,ULONG ulPriority,void* pfNotifyFn);
ULONG IF_UnRegisterNotifyFn(ULONG ulType,void* pfNotifyFn);

VOID IF_CreateIfNet();
ULONG IF_RegisterAll(IF_SH_CALL_S* pstShellCall);
ULONG IF_SetModuleInfo(IF_MOD_INFO_S *pstMInfo);


#ifdef  __cplusplus
}
#endif

#endif

