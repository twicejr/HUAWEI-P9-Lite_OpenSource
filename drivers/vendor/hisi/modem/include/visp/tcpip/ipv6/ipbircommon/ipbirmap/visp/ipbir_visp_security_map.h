/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_visp_security_map.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To define VISP specific IC macros
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for defining VISP related IC macros
************************************************************************/

#ifndef _IPBIR_VISP_SECURITY_MAP_H_
#define _IPBIR_VISP_SECURITY_MAP_H_

/*B110-NP*/
#define IPB_IR_IPSEC_NP_DOWNLOADFAILURE_NOTIFY(m_pfHookFunc)\
    (VOID)TCPIP_RegFuncNPDownloadFailedProcFunc(m_pfHookFunc)

/* Anoop_VPN VISP macro */

/* VISP Macro need to add here like L3VPN_ENABLE    */

#define IPB_IR_VRFDELSUCCESSNOTIFY(ulModId, ulVrfId, ulRet)    \
                ulRet = TCPIP_VrfDelSuccessNotify (ulModId, ulVrfId);

/* This API has to be changed */
#define IPB_IR_VRFIDQUERYBYNAME(szVpnName, pulVrfId, ulRet)   \
                ulRet = TCPIP_GetVrfIndexByName (szVpnName, pulVrfId);

#define IPB_IR_VRFNAMEQUERYBYID(ulVrfIndex, szVpnName, ulRet)  \
ulRet = TCPIP_GetVrfNameByIndex((CHAR *)szVpnName,IKE_CONFIG_STRING_LENGTH, ulVrfIndex);

#define IPB_IR_SH_VRFNAMEQUERYBYID(ulVrfIndex, szVpnName, ulRet)    \
ulRet = TCPIP_GetVrfNameByIndex((CHAR *)szVpnName,IKE_CONFIG_STRING_LENGTH, ulVrfIndex);

#define IPB_IR_SH_REGFUNCVRFEVENTCALLBACK(ulModId, ulEventsToReceive,\
                                          pfVrfNotify) \
TCPIP_RegFuncVrfEventCallBack (ulModId, ulEventsToReceive, pfVrfNotify);


/* End  */
#endif  /* end of _IPBIR_VISP_SECURITY_MAP_H_ */

