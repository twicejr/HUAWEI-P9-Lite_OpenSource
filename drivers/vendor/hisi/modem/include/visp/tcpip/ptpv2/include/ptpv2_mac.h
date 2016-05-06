/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_mac.h
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

#ifndef _PTPV2_MAC_H_
#define _PTPV2_MAC_H_

#ifdef __cplusplus
extern "C" {
#endif

ULONG PTPV2_OverMacRcvPktHookEntry (MBUF_S* pstMBuf);

ULONG PTPV2_OverMacPktRcvProc(MBUF_S* pstMBuf);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of _PTPV2_MAC_h_   */
