/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipsfe_arp.h
*
*  Project Code: V1.1.0
*   Module Name: ARP
*  Date Created: 2009-8-18
*        Author: w60786
*   Description: ARP模块数据面和控制面共用的结构,宏等定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-8-18    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _IPSFE_ARP_H_
#define _IPSFE_ARP_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 有效ARP节点标志 */
#define SFE_ARP_NORMAL_ARPNODE 0
/* ARP伪节点标志 */
#define SFE_ARP_FAKE_ARPNODE 1

/* ARP数据面配置参数结构 */
typedef struct tagSFE_ARP_PARA
{
    SFE_IFID stIfID;
    UINT32   u32VrfIndex;       /* 接口所属VRF */
    UINT32   u32IpAddr;         /* 地址，网络字节序 */
    UINT32   u32VlanId;         /* 暂不使用 */
    UINT32   u32IsFake:1;       /* 是否是哑元标志，1表示是哑元表项 0表示非哑元表项 */
    UINT32   u32IsStatic:1;     /* 动静态标志，1表示是静态表项 0表示动态表项 */
    UINT32   u32FlagReserve:30;     /* 动静态标志，1表示是静态表项 0表示动态表项 */
    UINT8    u8MacAddr[SFE_MAC_LEN]; /* physical地址 */
    UINT8    u8Source;         /* 来源 */
    UINT8    u8Reserve;
}SFE_ARP_PARA_S;

/* ARP MISS数据面通知控制面的消息结构 */
typedef struct tagSFE_ARP_MISS_PARA
{
    SFE_IFID stIfID;            /* 接口信息 */
    UINT32   u32VrfIndex;       /* 接口所属VRF */
    UINT32   u32IpAddr;         /* 地址，网络字节序 */
}SFE_ARP_MISS_PARA_S;

/* 单个ARP表项信息获取关键字 */
typedef struct tagSFE_ARP_KEY
{
    UINT32 u32VrfIndex;  /* VRF索引 */
    UINT32 u32IpAddr;    /* 地址，网络字节序 */
}SFE_ARP_KEY_S;

#ifdef  __cplusplus
}
#endif

#endif

