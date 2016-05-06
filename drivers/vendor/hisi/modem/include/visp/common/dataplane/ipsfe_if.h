/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipsfe_if.h
*
*  Project Code: V1.1.0
*   Module Name: IF
*  Date Created: 2009-8-18
*        Author: z00104483/h00121208
*   Description: IF模块数据面和控制面共用的结构,宏等定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-8-18    z00104483/h00121208           Creat the first version.
*
*******************************************************************************/

#ifndef _IPSFE_IF_H_
#define _IPSFE_IF_H_

#ifdef  __cplusplus
    extern "C"{
#endif

#ifndef SFE_MAC_LEN
#define SFE_MAC_LEN         6        /* physical地址长度 */
#endif

/* IFID的拷贝 */
#define INTF_COPYIFID(pstDestIfID,pstSrcIfID)\
{\
    (pstDestIfID)->u8FrameID     = (pstSrcIfID)->u8FrameID;\
    (pstDestIfID)->u16SlotID     = (pstSrcIfID)->u16SlotID;\
    (pstDestIfID)->u16PortNo     = (pstSrcIfID)->u16PortNo;\
    (pstDestIfID)->u8PortType    = (pstSrcIfID)->u8PortType;\
    (pstDestIfID)->u16lSubPortNo = (pstSrcIfID)->u16lSubPortNo;\
}

#define INTF_COPYMAC(pu8DestMac,pu8SrcMac)\
{\
    pu8DestMac[0] = pu8SrcMac[0];\
    pu8DestMac[1] = pu8SrcMac[1];\
    pu8DestMac[2] = pu8SrcMac[2];\
    pu8DestMac[3] = pu8SrcMac[3];\
    pu8DestMac[4] = pu8SrcMac[4];\
    pu8DestMac[5] = pu8SrcMac[5];\
}

/* 接口信息ID,保证SFE_IFID和TCPIP_SFE_IFID结构成员及大小定义一致 */
typedef struct tagSFE_IFID
{
    UINT8   u8PortType;        /* 端口类型 */
    UINT8   u8FrameID;         /* 框号,全F表示不使用 */
    UINT16  u16SlotID;         /* 逻辑槽位号,全F表示不使用 */
    UINT16  u16PortNo;         /* 逻辑端口号,一维模式下系统端口编号唯一，三维模式下在同一框同一槽位下唯一 */
    UINT16  u16lSubPortNo;     /* 子端口号 */
}SFE_IFID;

/* 接口信息结构,保证SFE_INTERFACE_INFO_S和TCPIP_SFE_INTF_S结构成员及大小定义一致 */ 
typedef struct tagSFE_INTERFACE_INFO
{
    SFE_IFID stIfID;
    UINT32   u32IfIndex;             /* 接口索引,ACL模块需要 */
    UINT32   u32VrfIndex;            /* VRF索引 */
    UINT32   u32LinkType;            /* 端口的链路层属性 */    
    UINT32   u32PhyStatus;           /* 端口物理状态 */
    UINT32   u32LineStatus;          /* IPV4链路状态 */
    UINT32   u32Line6Status;         /* IPV6链路状态 */    
    UINT32   u32Baud;                /* 端口的波特率 */
    UINT32   u32MTU;                 /* 端口的MTU */
    UINT32   u32ReduceTTL;           /* 接口转发报文TTL是否减1 */
    UINT8    u8MacAddr[SFE_MAC_LEN]; /* physical地址 */ 
    UINT8    u8Attribute;            /* 接口属性Fabric/spi4口 */
    UINT8    u8Origin;               /* 接口创建来源 */
    UINT32   u32IsDisableArpMiss;    /* 接口是否需要去使能ARP MISS功能,只对以太口有效 */
}SFE_INTERFACE_INFO_S;

/* 设置接口相关开关的参数信息,ARP MISS开关,TTL是否减1开关 */
typedef struct tagSFE_IF_SET_SWITCH
{
    SFE_IFID stIfID;                 /* 接口ID */
    UINT32   u32Switch;              /* 开关值 */
    UINT32   u32Reserved;            /* 填充4字节保证在64位上8字节对齐 */
}SFE_IF_SET_SWITCH_S;

#ifdef  __cplusplus
}
#endif

#endif

