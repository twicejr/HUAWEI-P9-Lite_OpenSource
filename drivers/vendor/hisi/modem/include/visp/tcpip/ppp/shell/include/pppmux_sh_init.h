/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pppmux_sh_init.h
*
*  Project Code: VISPV100R005
*   Module Name: PPPMUX
*  Date Created: 2006-5-11
*        Author: ZhouTong(43740)
*   Description: PPPMUX组件shell函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-5-11  ZhouTong(43740)   Create
*
*******************************************************************************/

#ifndef _PPPMUX_SH_INIT_H_
#define _PPPMUX_SH_INIT_H_

#ifdef  __cplusplus
extern  "C"{
#endif

ULONG PPPMUX_SH_Init();
ULONG PPPMUX_SH_DeInit();
ULONG PPPMUX_RegApp();

extern struct ComponentInfo m_CompPppMuxInfo;

extern  ULONG TCPIP_QOS_GetPacketClass(ULONG ulIfIndex,MBUF_S* pstMBuf,UCHAR * pucClass);

extern VOS_UINT32 VOS_GetCpuTickBase( VOS_UINT32 *pCpuTickBase);

#ifdef  __cplusplus
}
#endif

#endif/*#ifndef _PPPMUX_SH_INIT_H_*/

