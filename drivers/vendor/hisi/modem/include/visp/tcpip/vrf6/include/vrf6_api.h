/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              vrf6_api.h
*
* Project Code: VISPV100R007
*  Module Name: VRF
* Date Created: 2013-10-19
*       Author: Apurba/Abhishek
*  Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-10-19
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _VRF6_API_H_
#define _VRF6_API_H_

#define VRF6_DEFAULT_ID        0
#define VRF6_DEFAULT_NAME      ""

/*******************************************************************************
*    Func Name: TCPIP_CfgVrf6Instance
* Date Created: 2013-09-28
*       Author: apurba
*  Description
*        Input:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-09-28   apurba                  Create
*
*******************************************************************************/
extern ULONG TCPIP_CfgVrf6Instance(VRF_CFGINSTANCE_S *pstVrfIn);

/*******************************************************************************
*    Func Name: TCPIP_CfgIntfBindVrf6
* Date Created: 2013-09-28
*       Author: apurba
*  Description
*        Input: VRF_CFGINTFBIND_S * pstVrfIn
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-09-28   apurba                  Create
*
*******************************************************************************/
ULONG TCPIP_CfgIntfBindVrf6(VRF_CFGINTFBIND_S * pstVrfIn);

/*******************************************************************************
*    Func Name: TCPIP_GetVrf6IndexByName
* Date Created: 2013-10-10
*       Author: Apurba
*  Description:
*        Input: CHAR *pszVrfName
*
*
*       Output: ULONG *pulVrfIndex
*       Return: VRF_OK,
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-10   Apurba                  Create
*******************************************************************************/
extern ULONG TCPIP_GetVrf6IndexByName (CHAR *pszVrfName, ULONG *pulVrfIndex);


/*******************************************************************************
*    Func Name: TCPIP_GetVrf6NameByIndex
* Date Created: 2013-10-10
*       Author: Apurba
*  Description:
*        Input:
*               ULONG ulVrfIndex:
*
*       Output: CHAR *pszVrfName
*       Return: VRF_OK,
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-10   Apurba                  Create
*******************************************************************************/
extern ULONG TCPIP_GetVrf6NameByIndex(CHAR *pszVrfName,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncVrf6EventCallBack
* Date Created: 2013-10-10
*       Author: Apurba
*  Description:
*        Input:
*               ULONG ulModId:
*               ULONG ulEventsToReceive:
*               VRF_CALLBACK_FUNC pfVrfNotify
*
*       Output: 
*       Return: VRF_OK,
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-10   Apurba                  Create
*******************************************************************************/
extern ULONG TCPIP_RegFuncVrf6EventCallBack (ULONG ulModId, ULONG ulEventsToReceive,
                                                VRF_CALLBACK_FUNC pfVrfNotify);


/*******************************************************************************
*    Func Name: TCPIP_Vrf6DelSuccessNotify
* Date Created: 2013-10-10
*       Author: Apurba
*  Description:
*        Input:
*               ULONG ulModId:
*               ULONG ulVrfIndex:
*
*       Output: 
*       Return: VRF_OK,
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-10   Apurba                  Create
*******************************************************************************/
extern ULONG TCPIP_Vrf6DelSuccessNotify(ULONG ulModId, ULONG ulVrfIndex);



ULONG TCPIP_OpenVrf6BindInfo (UINTPTR *pulSessionId, VRF_BIND_FILTER_S * pstFilter);



ULONG TCPIP_GetFirstVrf6BindInfo(UINTPTR ulSessionId, VRF_BIND_INFO_S *pstConfigInfo);


ULONG TCPIP_GetNextVrf6BindInfo(UINTPTR ulSessionId, VRF_BIND_INFO_S *pstConfigInfo);



ULONG TCPIP_CloseVrf6BindInfo (UINTPTR ulSessionId);



VOID TCPIP_ShowVrf6BindInfo (CHAR *pszVrfName, CHAR *pszIfName, ULONG ulIsAllVrf);



ULONG TCPIP_OpenVrf6CfgInfo (UINTPTR *pulSessionId, VRF_INFO_FILTER_S *pstFilter);


ULONG  TCPIP_GetFirstVrf6CfgInfo(UINTPTR ulSessionId, VRF_CFG_INFO_S *pstConfigInfo);



ULONG TCPIP_GetNextVrf6CfgInfo(UINTPTR ulSessionId, VRF_CFG_INFO_S *pstConfigInfo);



ULONG  TCPIP_CloseVrf6CfgInfo (UINTPTR ulSessionId);


VOID TCPIP_ShowVrf6CfgInfo(CHAR *pszVrfName, ULONG ulIsAllVrf);


ULONG TCPIP_GetVrf6IndexByRmPro(ULONG ulRtType,ULONG ulInstance,ULONG *pulVrfIndex);


#endif  /* _VRF_API_H_  */

#ifdef  __cplusplus
}
#endif
