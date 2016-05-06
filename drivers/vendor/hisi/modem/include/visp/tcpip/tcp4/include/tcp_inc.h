/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp_inc.h
*
*  Project Code: VISP1.5
*   Module Name: IP TCP4  
*  Date Created: 2003-05-23
*        Author: w25705
*   Description: To define tcp component interfaces
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-05-23  w25705           Create the first version.
*
*******************************************************************************/
#ifndef _IP_TCP_H
#define _IP_TCP_H

#ifdef  __cplusplus
extern "C"{
#endif


#include "tcpip/tcp4/core/include/tcp.h"
#include "tcpip/tcp4/core/include/tcp_fsm.h"
#include "tcpip/tcp4/core/include/tcp_time.h"
#include "tcpip/tcp4/core/include/tcp_cmd.h"
#include "tcpip/tcp4/core/include/tcp_var.h"
#include "tcpip/tcp4/core/include/tcp_seq.h"
#include "tcpip/tcp4/core/include/tcp_ha.h"
#include "tcpip/tcp4/core/include/itcp.h"
#include "tcpip/tcp4/core/include/tcp_fun.h"

/*x36317 在数通，用的原来的FIB，在非数通用的是SFIB 2004-7-16*/
/* Modified by Sunil to update the review comments -- BYAD05764 */
#define IP4_TCP_EXT_COMIF_CNT            0x6

extern UINT8 g_u8Tcp4CookieSwitch;
extern ULONG g_ulTcpReassMaxSeg;

#ifdef  __cplusplus
}
#endif

#endif  /* _IP_TCP_H */
