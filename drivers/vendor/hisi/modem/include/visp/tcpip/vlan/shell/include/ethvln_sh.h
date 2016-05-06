/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ethvln_sh.h
*
*  Project Code: VISPV100R007
*   Module Name: VLAN Shell
*  Date Created: 2008-08-04
*        Author: qinyun
*   Description: ethvln_sh.h
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME              DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-08-01      qinyun(62011)     Create the first version.
*
*******************************************************************************/
#ifndef _ETHVLN_SH_H_
#define _ETHVLN_SH_H_

#ifdef  __cplusplus
extern "C"{
#endif
extern IFNET_S *g_pstIfConfigNet;
extern ULONG VOS_strlen(const CHAR *);
extern VOID ETHVLAN_Info_Output(CHAR *pszMsg);
extern VOID ETHVLAN_PacketDebugInfo(IFNET_S * pIf, VOID * pPara,ULONG ulErrCode, ULONG ulDebugEvent);
extern ULONG ETHVLAN_SH_Init();
#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif /* end of  _ETHVLN_SH_H_*/

