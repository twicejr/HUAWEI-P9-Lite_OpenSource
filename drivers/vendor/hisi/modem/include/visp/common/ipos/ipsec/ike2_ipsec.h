/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ike2_ipsec.h
  Version       : Initial Draft
  Author        : Mahendra
  Created       : 2012/04/10
  Last Modified :
  Description   : Defines IKE functions called by IPSec
  Function List :
  History       :
  1.Date        : 2012/04/10
    Author      : Mahendra
    Modification: Created file
B047: Red Line Requirement
******************************************************************************/


#ifndef _IKE2_IPSEC_H
#define _IKE2_IPSEC_H


ULONG IKE_Udp6Init (VOID);

ULONG IKE_EnableDisableUdpSocket(ULONG ulFlag);

VOID IKE_Udp6DeInit();

ULONG IKE_OpenCloseSocket(ULONG ulFlag);

VOID IKE_CmnWarnIkeSA (ULONG ulWarnId, ULONG ulSubWarnID,
                        ULONG ulSAConnId,ULONG ulPeerAddr,
                        CHAR *pucPeerName);

VOID IKE_GetIKEPeerByNameAndUpdate(UCHAR *pucIKEPeerName, UCHAR ucFlag);

#endif /*_IKE2_IPSEC_H*/
