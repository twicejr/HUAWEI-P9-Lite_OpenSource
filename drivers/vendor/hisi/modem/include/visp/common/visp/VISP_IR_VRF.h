/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              VISP_IR_VRF.h
*
*  Project Code: VISPV1R6C02
*   Module Name:   
*  Date Created: 2009-03-13
*        Author: qinyun
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-03-13   qinyun                  Create
*
*******************************************************************************/

#ifndef _VISP_IR_VRF_H_
#define _VISP_IR_VRF_H_

#ifdef  __cplusplus
extern "C"{
#endif

/*same with vrf_api.h VRF_CALLBACK_CREATE,VRF_CALLBACK_DELETE,VRF_CALLBACK_CHANGE*/
#define VRFADAPT_CALLBACK_CREATE 0x1
#define VRFADAPT_CALLBACK_DELETE 0x02
#define VRFADAPT_CALLBACK_CHANGE 0x03

typedef  ULONG  (*L3VPNF_VRFCALLBACK_FUNC)( ULONG ulEvents , VOID *pData);

extern ULONG VRPAdapt_L3VPN_VRFMGM_VrfIdQueryByName (
        CHAR *pszVrfName, 
        ULONG *pulVrfId);
extern ULONG VRPAdapt_L3VPN_VRFMGM_VrfNameQueryById (
    CHAR *pszVrfName, 
    ULONG ulVrfId);
extern ULONG VRPAdapt_L3VPN_VRFMGM_RegisterCb (
    ULONG ulModId, 
    ULONG ulEventsToReceive, 
    L3VPNF_VRFCALLBACK_FUNC pfVrfNotify);
extern ULONG VRPAdapt_L3VPN_VRFMGM_VrfDelSuccessNotify (
    ULONG ulModId, 
    ULONG ulVrfId);

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif    /* end of _VISP_IR_ACL_H_ */
