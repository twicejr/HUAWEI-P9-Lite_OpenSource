/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_ann.h
*
*  Project Code:
*   Module Name: PTPV2 func
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _PTPV2_ANN_H_
#define _PTPV2_ANN_H_

#ifdef __cplusplus
extern "C" {
#endif

ULONG PTPV2_Ann_RcvMsg (UCHAR* pucBuffer, ULONG ulPacketLen, 
                                  TCPIP_PTP_ADDRINFO_S* pstAddrInfo, PTPV2_PORT_S *pstPortInfo);

ULONG PTPV2_BC_MasterBuildAnnPkt(VOID* pThis, VOID** pData);

ULONG PTPV2_OC_MasterBuildAnnPkt(VOID* pThis, VOID** pData);

VOID PTPV2_ANN_PrintAnn(PTPV2_ANNOUNCE_MSG_S *pstAnnMsg, TCPIP_PTP_ADDRINFO_S *pstAddrInfo, ULONG ulFlag);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of _PTPV2_ANN_h_   */

