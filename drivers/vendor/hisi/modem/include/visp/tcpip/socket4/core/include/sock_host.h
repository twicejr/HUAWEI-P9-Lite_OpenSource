/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_host.h
*
*  Project Code: VISPV100R007
*   Module Name: socket
*  Date Created: 2008-04-11
*        Author: zhoutong(43740)
*   Description: 上述定义从sock_pub.h中复制了一份，仅用于sock_api.c和sock6_api.h引用
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-11   zhoutong(43740)         Create
*
*******************************************************************************/

#ifndef _SOCK_HOST_H_
#define _SOCK_HOST_H_

#ifdef __cplusplus
extern "C"{
#endif

#define IP_HOSTNAME_LEN    254
#define HostNameLen        (IP_HOSTNAME_LEN+1)    /* modify by x36530 trace to D08067 */

typedef struct tagSOCKHOST
{
    CHAR  HostName[HostNameLen];
    UCHAR ucPadding_1[4-((HostNameLen)%4)];
    CHAR  HostIP[MAXHOSTADDRNO][IPADDRMAXLEN];
    UCHAR ucPadding_2[4-(((MAXHOSTADDRNO)*(IPADDRMAXLEN))%4)];
    LONG  AddrNo;
    ULONG ulAge;
    CHAR  Flags;
    CHAR  type;
    UCHAR ucPadding_3[2];
}SOCKHOST_S;

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

