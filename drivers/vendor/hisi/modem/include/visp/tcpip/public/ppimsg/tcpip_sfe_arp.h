/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_sfe_arp.h
*
*  Project Code: V1.1.0
*   Module Name: ARP
*  Date Created: 2009-8-21
*        Author: w60786
*   Description: ARP控制面与数据面交互处理头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-8-21    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _TCPIP_SFE_ARP_H_
#define _TCPIP_SFE_ARP_H_

#ifdef  __cplusplus
    extern "C"{
#endif

extern UINT32 TCPIP_SFE_ARPMissNotify(UINT32 u32VrfIndex, UINT32 u32IpAddr, SFE_IFID *pstIfID);

#ifdef  __cplusplus
}
#endif

#endif

