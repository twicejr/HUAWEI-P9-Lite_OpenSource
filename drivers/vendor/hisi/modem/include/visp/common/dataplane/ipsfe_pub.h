/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipsfe_pub.h
*
*  Project Code: V1.1.0
*   Module Name: pub
*  Date Created: 2009-8-18
*        Author: z62531
*   Description: pub模块数据面和控制面共用的结构,宏等定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-8-18    z62531           Creat the first version.
*
*******************************************************************************/

#ifndef _IPSFE_PUB_H_
#define _IPSFE_PUB_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 在通道中传输显示数据面ARP信息的结构体 */
typedef struct tagSFE_ARP_SHOW
{
    UINT32 u32VrfIndex;         /* VRF索引 */
    UINT8  uiIpAddr[LEN_16];    /* 地址, 点分十进制字符串 */
}SFE_ARP_SHOW_S;

/* 在通道中传输显示数据面BFD信息的结构体 */
typedef struct tagSFE_BFD_SHOW
{
    UINT32 u32VrfIndex;         /* VRF索引 */
    UINT32 u32SessionID;        /* BFD会话ID */
}SFE_BFD_SHOW_S;

/* 在通道中传输显示数据面ROUTE信息的结构体 */
typedef struct tagSFE_ROUTE_SHOW
{
    UINT32 u32VrfIndex;         /* VRF索引 */
    UINT8  uiIpAddr[LEN_16];    /* 地址, 点分十进制字符串 */
}SFE_ROUTE_SHOW_S;

#ifdef  __cplusplus
}
#endif

#endif

