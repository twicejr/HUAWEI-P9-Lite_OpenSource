/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_sfe_if.h
*
*  Project Code: copy 1.1
*   Module Name: IF
*  Date Created: 2009-08-21
*        Author: ZhengSenHuo/GeXianJun(104483/121208)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-08-21   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
#ifndef _TCPIP_SFE_IF_H_
#define _TCPIP_SFE_IF_H_

#ifdef  __cplusplus
extern "C"{
#endif

extern UINT32 TCPIP_SFE_IF_ProductGetPortType(UINT8 u8PortType,UINT8 *pu8SfePortType);
extern UINT32 TCPIP_SFE_IF_PPIGetSfePortType(UINT32 u32PortType,UINT8 *pu8SfePortType);
extern UINT32 TCPIP_SFE_IF_PPIGetControlPortType(UINT32 u32SfePortType,UINT32 *pu32ControlPortType);
extern UINT32 TCPIP_SFE_IF_GetSfeIfIDByIfIndex(UINT32 u32IfIndex,SFE_IFID *pstIfID);
extern UINT32 TCPIP_SFE_IF_GetIfIndexBySfeIfID(UINT32 *pu32IfIndex,SFE_IFID *pstIfID);

#ifdef  __cplusplus
}
#endif
#endif

