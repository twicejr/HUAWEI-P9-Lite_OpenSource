/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              udp_sh_ic.h
*
*  Project Code: VISP1.5
*   Module Name: UDP4
*  Date Created: 2004-04-29
*        Author: WeiYongDong
*   Description: Shell IC implement header file for UDP4 Component
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2003-06-10  WeiYongDong      Create the first version.
*  2006-04-27  luyao            根据编程规范，对文件进行规范化整理
*
*******************************************************************************/

#ifndef _UDP_SH_IC_H
#define _UDP_SH_IC_H

#ifdef __cplusplus
extern "C"{
#endif

/*Modified by dengxiong for D00173*/
VOID IP4_UDP4_SH_DbugPkt(CHAR *pPreStr, MBUF_S *pstMbuf) ;
LONG IP4_UDP4_SH_ShowDebugging(CHAR *szStatusStr,
                                ULONG ulMaxLen,
                                ULONG ulDebugIndx,
                                ULONG *pulWaitlistHandle,
                                ULONG ulInterface );
ULONG IP4_UDP4_SH_Reg2IC();
VOID  IP4_UDP4_SH_DebugToIC ( CHAR *szString );

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif
