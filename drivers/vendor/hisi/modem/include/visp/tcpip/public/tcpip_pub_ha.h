/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_pub_ha.h
*
*  Project Code: VISPV100R007
*   Module Name: PUBLIC HA  
*  Date Created: 2008-04-09
*        Author: zhoutong(43740)
*   Description: 公共模块HA宏定义与函数声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-09   zhoutong(43740)         Create
*
*******************************************************************************/
#ifndef _TCPIP_PUB_HA_H_
#define _TCPIP_PUB_HA_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/* 公共模块HA备份中操作码的定义 */
typedef enum tagPUBLIC_HAHEAD_TYPE
{
    PUBLIC_INFORMATION_BAK = 1,           /* 公共模块基础数据的实时备份 */
    PUBLIC_SOCKSCHEDULE_BAK,              /* 设置Sock事件、报文调度次数 */
    PUBLIC_PINGALLOWLIST_BAK = 0x81,      /* ping allow list的实时备份，需要预留一些值给VISPV1R6使用，故从0x81开始 */
    PUBLIC_OPTIM_BAK,                     /* 性能优化的实时备份 */

    PUBLIC_BATCH_BAK = 0xff   /* 公共模块所有数据批量备份，公共模块新增备份内容时，在此字段之前添加类型字 */
}PUBLIC_HAHEAD_TYPE_E;

/* 公共模块HA备份中TLV类型的定义 */
typedef enum tagPUBLIC_HATLV_TYPE
{
    PUBLIC_HA_PINGALLOWLIST_ADD       = 0x0001, /* 增加地址到ping allow list */
    PUBLIC_HA_PINGALLOWLIST_DELSINGLE = 0x0002, /* 从ping allow list中删除一个地址 */
    PUBLIC_HA_PINGALLOWLIST_DELALL    = 0x0003, /* 删除ping allow list中的所有地址 */
    PUBLIC_HA_OPTIM_TYPE              = 0x0004, /* 性能优化子模块备份类型 */
    PUBLIC_HA_SOCKSCHEDULE            = 0x0005, /* 设置Sock事件、报文调度次数 */
}PUBLIC_HATLV_TYPE_E;

/* 公共部分备份消息 */
typedef struct tagPUBLIC_HEAD_BAK
{
    ULONG  ulLinkMaxPkt;         
    ULONG  ulPingForbidFlag;
}PUBLIC_HEAD_BAK_S;

/*add by z00104207 for VR7，用于禁ping增强的地址备份*/
typedef struct tagHA_PINGALLOWLIST_ADDR
{
    ULONG ulIPAddr;             /*地址*/
    ULONG ulSubnetMask;         /*子网掩码*/
}HA_PINGALLOWLIST_ADDR_S;

/* 公共部分中性能优化部分备份消息(TLV) */
typedef struct tagPUBLIC_OPTIM_BAK
{
    ULONG  ulOptimEnable;
    ULONG  ulOptimEntrySum;
}PUBLIC_OPTIM_BAK_S;

/* 公共部分中Sock Schedule部分备份消息(TLV) */
typedef struct tagPUBLIC_SOCKSCHEDULE_BAK
{
    ULONG  ulSwitch;
    ULONG  ulTimes;
    ULONG  ulDelayTime;
}PUBLIC_SOCKSCHEDULE_BAK_S;


/* PUBLIC HA设置HA公共报头 */
#define SET_PUBLIC_HA_HEAD(pucData, ucHAMid, ucBakOperation, usBakMsgLen)\
{\
    HAMSGHEADER_S* pstHaHdr = (HAMSGHEADER_S *)(pucData);\
    pstHaHdr->ucModID = (UCHAR)(ucHAMid);\
    pstHaHdr->ucOperation = (UCHAR)(ucBakOperation);\
    pstHaHdr->usMsgLen = (USHORT)(usBakMsgLen);\
}

extern ULONG g_ulPUBLICBakDbg; 
extern ULONG g_ulPUBVerboseDebug;

extern ULONG PUBLIC_HA_PingAllosList_Input(UCHAR *pucBuf);
extern ULONG PUBLIC_HA_PingAllowList_Backup(ULONG ulOperation, ULONG ulIPAddr, ULONG ulSubnetMask);
extern ULONG PUBLIC_HA_OptimInput(UCHAR *pucBuf);
extern ULONG PUBLIC_HA_BatchBackup(VOID);
extern ULONG PUBLIC_HA_Backup(UCHAR ucOperation);
extern ULONG PUBLIC_HA_Input(UCHAR *pucInBuf, USHORT usDataLen);
extern ULONG PUBLIC_HA_Smooth(VOID);
extern ULONG PUBLIC_HA_Clean(VOID);
extern VOID  PUBLIC_HA_DebugOutPut(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _TCPIP_PUB_HA_H_ */

