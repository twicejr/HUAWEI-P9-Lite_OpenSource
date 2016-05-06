/*******************************************************************************
*
*
*                Copyright 2010, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_shell6.h
*
*  Project Code: VISPV1R8C05
*   Module Name:   
*  Date Created: 2010-09-19
*        Author: raofei62469
*   Description: PTP shell模块函数头文件声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2010-09-19   raofei62469&zhangbo146309             Create
*
*******************************************************************************/

#ifndef _PTP6_SHELL_H_
#define _PTP6_SHELL_H_

#include "tcpip/ipv6/socket6/core/include/sock6_callback.h"
#include "tcpip/ipv6/socket6/core/include/sock6_pub.h"
#include "tcpip/ipv6/socket6/include/tcpip_socket6.h"

#ifdef __cplusplus
extern "C" {
#endif

ULONG PTP6_Socket_Init (ULONG ulEventFlag);

ULONG PTP6_Shell_SndGeneralMsg (UCHAR *pucBuffer, ULONG ulPacketLength, ULONG ulPtpMsgType, PTP_ADDRINFO_S *pstAddrInfo);

ULONG PTP6_SetSocketTos (UCHAR ucDscp);

ULONG PTP6_SetSocketSrcAddr (USHORT usPtpPortNumber,PTP_PORT_ADDR_S *pstPortAddr);

LONG PTP6_SetSocketOption(ULONG ifindex,ULONG ulSrcAddr);

ULONG PTP6_PKT_RcvGeneralMsg(UCHAR *pBuffer, ULONG ulPacketLen, PTP_ADDRINFO_S *pstAddrInfo);

extern LONG PTP6_Inet_pton6(const CHAR *szSrcAddr, VOID *pDstAddr);

extern CHAR * PTP6_Inet_ntop6(const CHAR *pSrcAddr,CHAR *pszDstAddr,ULONG ulAddrLen);

ULONG PTP6_Shell_RcvMsg (CHAR *pChar,SO6_CALLBACKINFO_S *pstVal);

ULONG PTP6_Shell_RcvGeneralMsg (CHAR *pChar,SO6_CALLBACKINFO_S *pstVal);

#ifdef __cplusplus 
}
#endif   /* end of __cplusplus          */

#endif   /* end of _PTP6_SHELL_H_    */ 



