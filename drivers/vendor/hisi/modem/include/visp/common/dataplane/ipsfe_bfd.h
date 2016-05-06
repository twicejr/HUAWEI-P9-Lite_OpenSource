/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipsfe_bfd.h
*
*  Project Code: V1.1.0
*   Module Name: BFD
*  Date Created: 2009-9-2
*        Author: w60786
*   Description: BFD模块数据面和控制面共用的结构,宏等定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-9-2     w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _IPSFE_BFD_H_
#define _IPSFE_BFD_H_

#ifdef  __cplusplus
    extern "C"{
#endif


/* BFD会话配置参数 */
typedef struct tagSFE_BFD_PARA
{
    UINT32 u32VrfIndex;                  /* 会话所在的VRF */
    UINT32 u32SessionId;                 /* BFD会话ID */
    UINT32 u32DetectMode;                /* 实际的检测模式 */
    UINT32 u32TxInterval;                /* 本端实际的发送时间间隔,ms */
    UINT32 u32DetectInterval;            /* 本端实际的检测间隔,ms */
    UINT32 u32DetectMult;                /* 本端实际的检测倍数 */
    UINT32 u32MyDiscriminator;           /* 本端标识符 */
    UINT32 u32YourDiscriminator;         /* 对端标识符 */
    UINT32 u32IpVer;                     /* IP版本标识:0--表示是IPv4 BFD;1--表示是IPv6 BFD */
    SFE_IPADDR_UN unDstIPAddr;           /* 对端地址,网络序 */
    SFE_IPADDR_UN unSrcIPAddr;           /* 本端地址,网络序 */
    UINT32 u32TTL;                       /* TTL */
    UINT32 u32DstUdpPort;                /* UDP目的端口号,单跳为3784,多跳为4784,主机序 */
    UINT32 u32SrcUdpPort;                /* UDP源端口号,值为49151+X(X>0),主机序 */
    UINT32 u32Tos;                       /* TOS值 */
    UINT32 u32IsMultiHop;                /* BFD多跳会话标志,要求在控制面根据接口索引转换好 */
    SFE_IFID stSendIfID;                 /* 会话的出接口信息,单跳时有效,多跳时无效 */

    CHAR szCtlPkt[SFE_BFD_LEN_AUTH_NONE];/* 会话的BFD控制报文,网络序,值为用户配置值 */
}SFE_BFD_PARA_S;

/* BFD探测DOWN时数据面通知控制面的消息结构 */
typedef struct tagSFE_BFD_DETECTDOWN_PARA
{
    UINT32   u32VrfIndex;               /* BFD会话所属VRF */
    UINT32   u32SessionId;              /* BFD会话ID */
}SFE_BFD_DETECTDOWN_PARA_S;

/* 单个BFD会话信息获取关键字 */
typedef struct tagSFE_BFD_KEY
{
    UINT32   u32VrfIndex;               /* BFD会话所属VRF */
    UINT32   u32SessionId;              /* BFD会话ID */
}SFE_BFD_KEY_S;

/* 基于BFD会话的调试开关 */
typedef struct tagSFE_BFD_DEBUGSWITCH
{
    UINT32 u32VrfIndex;                 /* BFD会话所属VRF */
    UINT32 u32SessionId;                /* BFD会话ID */
    UINT32 u32IsDebug;                  /* 调试开关,1为打开,0为关闭 */
    UINT32 u32Reserved;                 /* 填充4字节保证在64位上8字节对齐 */
}SFE_BFD_DEBUGSWITCH_S;

#ifdef  __cplusplus
}
#endif

#endif

