/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ITrrt.h
*
*  Project Code: VISP1.5
*   Module Name: Traceroute Module 
*  Date Created: 2003-07-14
*        Author: suraj( )
*   Description: Declare All Interface IDs for ping Component
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-07-14  suraj( )         Creat the first version.
*
*******************************************************************************/

#ifndef _TRRT_H_
#define _TRRT_H_

#ifdef  __cplusplus
extern "C"{
#endif
    
typedef struct tagINT_TRRT_OBJ_S
{
    IIF_TRRT_ComIntFUN       * pComIntTrrtFun;  
    IIF_TRRT_ComIntCFG       * pComIntTrrtCFG;
    
}TRRT_INT_OBJ_S;

/*Component Factory for TRRT component */
extern IComponentFactory m_ITrrtFactory;
ULONG TRRT_QueryInterface(IUnknown *This, COMP_IID iid, LPVOID *ppvObj);
extern ULONG TRRT_DoTrace(ULONG ulUserID,struct tagTrrtDetectMtuParam *pstTrrtParam);
ULONG TRRT_ActiveCom();
ULONG TRRT_InitCom(COM_ID_INFO_S *pstComInfo, ULONG  ulComLen);
ULONG TRRT_SetModuleInfo(TRRT_MOD_INFO_S *pstMInfo);
ULONG TRRT_RegShellApi(TRRT_SH_CALLBACK_S *pstTrrtCallBack);
ULONG TRRT_SetPortRange(USHORT usTrrtMinPort, USHORT usTrrtMaxPort, USHORT usTrrtDefaultPort);
ULONG TRRT_GetPortRange(USHORT *pusTrrtMinPort, USHORT *pusTrrtMaxPort, USHORT *pusTrrtDefaultPort);
#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TRACERT_H_ */

