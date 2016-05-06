/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfib_sh_ha.h
*
*  Project Code:    VISPV1R6
*   Module Name:  SFIB Module   
*  Date Created:   2006-12-06
*        Author:        j51916
*   Description:      SFIB high availability function implement
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE                  NAME                     DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-06      j51916                  Creat the first version.
*
*
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _SFIB_SH_HA_H
#define _SFIB_SH_HA_H

#define SFIB_ADD_STATIC_BAK                1    /* 增加静态路由的 */
#define SFIB_BATCH_ITEM_BAK                2    /* 批量备份路由项 */
#define SFIB_DEL_STATIC_BAK                3    /* 删除静态路由消息 */
#define SFIB_DISABLE_BY_NEXTHOP_BAK        4    /* 根据下一跳去使能接口路由 */
#define SFIB_ENABLE_BY_NEXTHOP_BAK         5    /* 根据下一跳使能接口路由 */
#define SFIB_DISABEL_RT_BAK                6    /* 禁止RIB表项 */
#define SFIB_ENABLE_RT_BAK                 7    /* 使能RIB表项 */
#define SFIB_ROUTE_POLICY_BAK              8    /* 路由策略的备份 */

/* 全局调试开关 */
extern ULONG g_ulFibBakDbg;

/* 实时路由备份消息 */
typedef struct tagSFIB_REAL_HEAD_BAK
{
    USHORT usType;              /* 备份消息块类型 */
    USHORT usLen;               /* 备份消息块的总长度 */
    ULONG ulIpAddress;          /* 配置的地址 */
    ULONG ulMaskLen;            /* 掩码长度 */
    ULONG ulGateway;            /* 网关地址 */
    ULONG ulIfIndex;            /* 出接口索引 */
    ULONG ulRt_Flags;           /* 路由有效标记 */
    ULONG ulRTPri;              /* 路由优先级 */
    ULONG ulPmtu;
} SFIB_REAL_HEAD_BAK_S;

/* 实时信息备份消息 */
typedef struct tagSFIB_HEAD_BAK
{
    USHORT usType;              /* 备份消息块类型 */
    USHORT usLen;               /* 备份消息块的总长度 */
    ULONG ulExtend;             /* 扩展字段，现在路由策略用这个字段 */
} SFIB_HEAD_BAK_S;

ULONG SFIB4_HA_BatchBackup();
ULONG SFIB4_HA_BuildOnePacket(USHORT usType, UCHAR * pucData, UCHAR *pucInBuf, USHORT usInBufLen);
ULONG SFIB4_HA_BatchBackupSendPacket(UCHAR * pucData, USHORT usDataLen, ULONG ulCount);
ULONG SFIB4_HA_Input(UCHAR * pucBuf, ULONG ulMsgLen);
ULONG SFIB4_HA_BuildSendOnePacket(USHORT usType, UCHAR * pucData, USHORT usInBufLen);
USHORT SFIB4_HA_SendPacket(UCHAR * pucData, USHORT usDataLen);
ULONG SFIB4_HA_Smooth();
ULONG TCPIP_HA_SetSfibDbg(ULONG ulDbg);
ULONG SFIB4_HA_GetSfibDbg (ULONG *pulDbg);
VOID SFIB4_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
ULONG SFIB4_HA_SetSfib4VerboseDbg(ULONG ulDbg);
ULONG SFIB4_HA_GetSfib4VerboseDbg (ULONG *pulDbg);
extern void *VOS_Mem_Cpy( void *Dest, const void *Src, ULONG Count );
ULONG SFIB4_HA_Clean(VOID);

#ifdef  __cplusplus
}
#endif

#endif
