/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_sfe_bfd.h
*
*  Project Code: V1.1.0
*   Module Name: BFD
*  Date Created: 2009-9-12
*        Author: w60786/h00121208
*   Description: BFD控制面与数据面交互处理头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                     DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-9-12    w60786/h00121208         Creat the first version.
*
*******************************************************************************/
#ifndef _TCPIP_SFE_BFD_H_
#define _TCPIP_SFE_BFD_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 数据面探测到BFD DOWN调用的控制面通知函数 */
extern ULONG (*g_pfSfeBfdDetectDownNotify)(ULONG ulSessionID, ULONG ulVrfIndex);

extern UINT32 TCPIP_SFE_BFD_DetectDownNotify(UINT32 u32VrfIndex, UINT32 u32SessionId);

#ifdef  __cplusplus
}
#endif

#endif

