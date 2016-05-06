/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_ha.h
*
*  Project Code:    VISP1.6
*   Module Name:  am4 Module   
*  Date Created:   2006-12-06
*        Author:        j51916
*   Description:      dhcp4c high availability function implement
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

#ifndef _AM4_HA_H_
#define _AM4_HA_H_

#ifdef  __cplusplus
extern  "C"{
#endif

#define IP4_CFG_ADD_MAIN_ADDR_BAK          1    /*增加配置主地址 */
#define IP4_CFG_ADD_SEC_ADDR_BAK           2    /*增加配置从地址 */
#define IP4_CFG_DEL_MAIN_ADDR_BAK          3    /*删除接口的主地址 */
#define IP4_CFG_DEL_SEC_ADDR_BAK           4    /*删除配置的从地址 */
#define IP4_UNNUMBER_ADDR_BAK              5    /* 借用接口地址标志 */

#define IP4_UNNUMBER_DEL_ADDR_BAK          10   /* 删除借用接口地址标志 */
#define IP4_NEGO_ADDR_BAK                  11   /* 协商地址备份标记 */
#define IP4_NEGO_DEL_ADDR_BAK              12   /* 删除协商地址备份标记 */
#define IP_DEL_BAK                         13   /* 清空接口上的地址 */

#define IP4_TTL_BAK                        21   /* TTL值的备份 */
#define IP4_ICMP_REDIRECTS                 22   /* ICMP值的重定向 */
#define IP4_ICMP_HOSTUNREACH               23   /* 主机不可达的配置 */
#define IP4_FORWARDFLAG_BAK                24   /* 报文转发开关备份 */
#define IP4_HOSTRTRESERVED_BAK             25   /* 接口DOWN时，保留主机路由标记 */

/* Begin of HA UPGRADE modification, 2010 December to 2011 January */
#define IP4_HA_MSGID_VRF                   25   /* VRF */
#define IP4_HA_MSGID_VRF_CREATE            26   /* Create VRF */
#define IP4_HA_MSGID_VRF_DELETE            27   /* delete VRF  */
#define IP4_HA_MSGID_INT_BIND_VRF          28   /*  VRF is bind to interface */
#define IP4_HA_MSGID_INT_UNBIND_VRF        29   /* VRF is unbind to interface  */

typedef struct tagIP4_VRF_BAK
{
    USHORT  usType;            /* 备份消息块类型 */
    USHORT  usLen;             /* 备份消息块的总长度 */
    ULONG   ulIfIndex;         /* Interface Index */
    ULONG   ulVrfIndex;        /* VRF Index */
} IP4_VRF_BAK_S;
/* End of HA UPGRADE modification, 2010 December to 2011 January */
        
typedef struct tagIP4_PACKET_HEAD_BAK
{
    USHORT usType;              /* 备份消息块类型 */
    USHORT usLen;              /* 备份消息块的总长度 */
    ULONG  ulIfIndex;          /* 配置块所属的接口索引 */
    ULONG  ulExtend;           /* 扩展字段 */
} IP4_PACKET_HEAD_BAK_S;

typedef struct tagIP4_CFG_PACKET_HEAD_BAK
{
    USHORT  usType;              /* 备份消息块类型 */
    USHORT  usLen;              /* 备份消息块的总长度 */
    ULONG    ulIfIndex;          /* 配置块所属的接口索引 */
    ULONG    ulIpAddr;           /* 配置的地址*/
    ULONG    ulIpMask;           /* 配置的地址掩码*/
} IP4_CFG_PACKET_HEAD_BAK_S;

typedef struct tagIP4_HA_PACKET_TLV
{
    USHORT  usHaMsgType;         /* 备份消息的类型 */
    USHORT  usHaMsgLength;       /* 备份消息的长度 */
}IP4_HA_PACKET_TLV_S;

typedef struct tagIP4_HA_HOSTRTRESERVED
{
    ULONG ulIfIndex;             /* 要在接口协议栈DWON时保留主机路由的接口索引 */
    ULONG ulHostRtReservedFlag;  /* 保留主机路由标记 */
}IP4_HA_HOSTRTRESERVED_S;

typedef struct tagIP4_UNNUMBER_PACKET_HEAD_BAK
{
    USHORT usType;                /* 备份消息块类型 */
    USHORT  usLen;                /* 备份消息块的总长度 */
    ULONG  ulMyIfIndex;           /* 配置块所属的接口索引 */
    ULONG  ulOtherIfIndex;        /* 借用地址的接口索引 */
} IP4_UNNUMBER_PACKET_HEAD_BAK_S;

typedef enum tagIP4_HA_OPTTYPE
{
    IP4_HA_OPTTYPE_BASE = 0,             /* 基础数据的备份 */
    IP4_HA_OPTTYPE_TLV,                  /* 按TLV方式组包备份 */
    IP4_HA_OPTTYPE_END
}IP4_HA_OPTTYPE_E;

#ifndef AM4_MAX_ONE_BAK_SIZE
#define AM4_MAX_ONE_BAK_SIZE \
             (sizeof(IP4_UNNUMBER_PACKET_HEAD_BAK_S))
#endif


ULONG IP_HA_BatchBackup();
ULONG IP_HA_PP4Batchup(ULONG ulCount);
ULONG IP_HA_BuildOnePacket(USHORT usType, ULONG ulIfIndex, UCHAR * pucData, UCHAR *pucInBuf, USHORT usInBufLen);
ULONG IP_HA_BatchBackupSendPacket(UCHAR * pucData, USHORT usDataLen, ULONG ulCount, UCHAR ucOperation);
ULONG IP_HA_Input(UCHAR * pucBuf, ULONG ulMsgLen);
ULONG IP_HA_BuildSendOnePacket(USHORT usType, ULONG ulIfIndex, UCHAR * pucData,
    USHORT usInBufLen, UCHAR ucOperation);
ULONG IP_HA_SendPacket(UCHAR * pucData, USHORT usDataLen);
ULONG TCPIP_HA_SetIpDbg(ULONG ulDbg);
ULONG IP_HA_GetIpDbg(ULONG *pulDbg);
ULONG IP_HA_Smooth();
VOID IP_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
ULONG IP_HA_SetIpVerboseDbg(ULONG ulDbg);
ULONG IP_HA_GetIpVerboseDbg (ULONG *pulDbg);
ULONG IP_HA_BatchBackup_TLV(ULONG ulCount);

#ifdef  __cplusplus
}
#endif

#endif

