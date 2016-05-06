/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_ha.h
*
*  Project Code: VISPV1R6
*   Module Name: Trunk  
*  Date Created: 2006-12-6
*        Author: LY(57500)
*   Description: trunk HA头文件，定义相关的数据结构、宏、枚举以及对引用其他模块函数的声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2006-12-6   LY(57500)        Create the first version.
*
*******************************************************************************/
#ifndef _TRUNK_HA_H
#define _TRUNK_HA_H

#ifdef  __cplusplus
extern  "C" {
#endif

/************ HA数据结构和宏 **************/

/* 定义HA报头的操作类型 */
#define TRUNK_HA_BATCH              0x00          
#define TRUNK_HA_REALTIME           0x01

#define TRUNK_INFO_BAK_TYPE         0x0001  /* Trunk信息备份*/
#define TRUNK_PORT_NEGO_BAK_TYPE    0x0002  /* 端口信息备份 */
#define TRUNK_PORT_NONEGO_BAK_TYPE  0x0003  /* 端口信息备份 */
#define TRUNK_GCFG_BAK_TYPE         0x0004  /* 全局配置信息 */

/*#define TRUNK_REALTIME_BAK_TYPE  0x0003*/
/* 实时备份消息类型, 注意需要同步修改g_aulRtPackLen 和 g_aszRtBackDbgInfo */
enum enTrunkRealBackUpType
{
    TRUNK_REALTIME_TRUNK_CREATE = 0x0100,
    TRUNK_REALTIME_PORT_ADD,
    TRUNK_REALTIME_PORT_REMOVE,
    TRUNK_REALTIME_PORT_UP,
    TRUNK_REALTIME_PORT_DOWN,
    TRUNK_REALTIME_SET_PERIOD,
    TRUNK_REALTIME_SET_LACP,
    TRUNK_REALTIME_NEWREFPORT,      /* 参考端口索引变化 */
    TRUNK_REALTIME_HE_CHNGPERIOD,   /* 对端周期模式变化 */
    TRUNK_REALTIME_TRUNK_BFDMODE,   /* 设置trunk或成员端口上配置单跳bfd会话的生效方式 */
    TRUNK_BAK_DYNMAC_INDEX,         /* 增加动态获取trunk mac特性,为支持主备动态获取mac一致,新增备份类型,对于实时备份和批量备份,都使用此备份类型 */
    TRUNK_BAK_NEGOUTTIME,           /* 备份首次协商不通过对外告警通知的时间 */
    TRUNK_BAK_PORTMAC,              /* trunk成员端口mac备份 BC3D02043 ETH/TRUNK MAC主备一致时，实现需要完善 */
    TRUNK_BAK_SYS_PRI,              /* 实时备份系统优先级 */
    TRUNK_BAK_PORT_PRI,             /* 备份端口优先级 */
    TRUNK_BAK_BACKUPMODE,           /* 备份端口备份模式 */
    TRUNK_BAK_MASTERPORT,           /* 备份1:1模式主端口 */
    TRUNK_BAK_RECOVERMODE,          /* 备份端口恢复模式 */
    TRUNK_BAK_ACTIVENUM,            /* 备份M:N模式激活端口 */
    TRUNK_BAK_PASSIVEMODE,          /* 备份主被动状态 */
    TRUNK_BAK_SYS_PRI_BYID = 0x0114, /* 备份Trunk组系统优先级 */
    TRUNK_BAK_PRODUCT_POLICY,       /* 备份Trunk的产品定制策略 */
    /* 【注意】: 如果有增加实时备份类型, 需要同步修改g_aulRtPackLen 和 g_aszRtBackDbgInfo */  
};

/* 备份出错消息输出 */
#define TRUNK_HA_DBG_CLOSE      0
#define TRUNK_HA_DBG_OPEN       1

#define TKHA_DEBUG_INFO_LEN     256

/* 调试信息输出宏 */
extern TRUNK_SHELL_CALLBACK_SET_S g_stTrunkShellApi;
#define TRUNK_HA_DEBUG(stErr) TCPIP_DebugOutput(stErr)

/* add by lijing for V1R6C02维优增强项目 */
/* LACP协商信息表 */
typedef struct tagLacpNegoBak
{
    /* 本端信息 */
    ULONG ulDefaulted;             /* 端口是否为defaulted端口 */
    UCHAR ucActorAdminState;       /* 本端端口管理状态值 */
    UCHAR ucActorOperState;        /* 本端端口运作状态值 */
    USHORT usActorAdminKey;        /* 本端端口管理Key */
    USHORT usActorOperKey;         /* 本端端口运作Key */
    USHORT usActorPortPri;         /* 本端端口优先级 */
    USHORT usActorPortIndex;       /* 本端端口号 */

    /* 对端信息 */
    UCHAR ucPartnerAdminState;     /* 对端端口管理状态值 */
    UCHAR ucPartnerOperState;      /* 对端端口运作状态值 */
    USHORT usPartnerAdminKey;      /* 对端端口管理KEY */
    USHORT usPartnerOperKey;       /* 对端端口运作Key */
    USHORT usPartnerAdminPortPri;  /* 对端端口管理优先级 */
    USHORT usPartnerOperPortPri;   /* 对端端口运作优先级 */
    USHORT usPartnerAdminPortIndex; /* 对端端口管理端口号 */
    USHORT usPartnerOperPortIndex;  /* 对端端口运作端口号 */
    USHORT usPartnerAdminSysPri;   /* 对端系统管理优先级 */
    USHORT usPartnerOperSysPri;    /* 对端系统运作优先级 */
    UCHAR ucPartnerAdminSysMac[TRUNK_MACADDR_LEN]; /* 对端系统管理physical地址 */
    UCHAR ucPartnerOperSysMac[TRUNK_MACADDR_LEN];  /* 对端系统运作physical地址 */
}LACP_NEGO_BAK_S;


/* 端口备份消息 LACP协商信息表 64字节*/
typedef struct tagTrunkPortNegoBak
{
    ULONG ulTrunkId;        /* Trunk ID（0－31）        */
    ULONG ulIfIndex;        /* 成员端口的接口索引       */
    ULONG ulLacpStatus;             /* 端口状态             */
    UCHAR ucOldMacAddress[TRUNK_MACADDR_LEN];       /* 成员端口加入Trunk前的physical地址 */
    UCHAR ucReserved[2];            /* 保留字段                     */
    LACP_NEGO_BAK_S stLacpNegoBak;      /* 备份的协商信息表             */
}TRUNK_PORT_NEGO_BAK_S;

/* 端口备份消息 NOLACP协商信息表 20字节*/
typedef struct tagTrunkPortNoNegoBak
{
    ULONG ulTrunkId;        /* Trunk ID（0－31）    */
    ULONG ulIfIndex;        /* 端口的接口索引       */
    ULONG ulLacpStatus;             /* 端口状态             */
    UCHAR ucOldMacAddress[TRUNK_MACADDR_LEN];       /* 成员端口加入Trunk前的physical地址 */
    UCHAR ucReserved[2];            /* 保留字段                     */
}TRUNK_PORT_NONEGO_BAK_S;

/* Trunk备份消息 24字节 */
typedef struct tagTrunkInfoBak
{
    ULONG ulTrunkId;        /* Trunk ID（0－31）    */
    ULONG ulIfIndex;        /* Trunk接口索引        */
    ULONG ulEnableLacp;     /* 是否使能LACP，默认为使能 */
    ULONG ulRefIfIndex;     /* 参考端口的接口索引   */
    UCHAR ucMacAddress[TRUNK_MACADDR_LEN];  /* Trunk接口physical地址     */
    UCHAR ucBfdTrunkMode;             /* trunk或成员端口上建立单跳bfd会话的生效模式,默认trunk优先 */   
    UCHAR ucPadding[1];
}TRUNK_INFO_BAK_S;

/* 全局配置信息 8字节 */
typedef struct tagTrunkGCfgBak
{
    UCHAR   g_ucSysMacAddress[TRUNK_MACADDR_LEN];   /* Trunk接口physical地址     */
    USHORT  g_usSysPri;             /* 记录Trunk模块的系统优先级，供LACP协商使用 */ 
}TRUNK_GCFG_BAK_S;

/* TRUNK备份消息头 4 字节 */
typedef struct tagTrunk_HEAD_BAK
{
    USHORT usType;          /* 备份消息块类型       */
    USHORT usLen;           /* 备份消息块长度       */
} TRUNK_HEAD_BAK_S;

/* HA 头长度 + Trunk HA 头长度 */
#define TKHA_HDR_LEN (sizeof(HAMSGHEADER_S)+sizeof(TRUNK_HEAD_BAK_S))


typedef struct tagTrunkPortAddBak
{
    ULONG ulIfIndex;
    ULONG ulTrunkId;
    USHORT usPri;
    USHORT usPadding;
}TRUNK_PORTADD_BAK_S;

typedef struct tagTrunkSetLacpBak
{
    ULONG ulIfIndex;
    ULONG ulValue;
}TRUNK_SETLACP_BAK_S;

typedef struct tagTrunkSetPeriodBak
{
    ULONG ulIfIndex;
    ULONG ulPeriod;
}TRUNK_SETPERIOD_BAK_S;

typedef struct tagTrunkNewRefPortBak
{
    ULONG ulTrunkId;
    ULONG ulNewRefIndex;
}TRUNK_NEWREFPORT_BAK_S;

/* 对端改变周期模式实时备份消息结构 */
typedef struct tagTrunkHeChngPeriodBak
{
    ULONG ulIfIndex; /* 端口索引 */
    UCHAR ucPartnerOperState;
    UCHAR ucReserved[3];
}TRUNK_HECHNGPERIOD_BAK_S;

/* 备份trunk上建立单跳bfd会话的生效模式 */
typedef struct tagBfdTrunkModeBak
{
    ULONG ulIfIndex; /* trunk索引 */
    UCHAR ucBfdTrunkMode;
    UCHAR ucReserved[3];
}TRUNK_BFDMODE_BAK_S;

/* 备份trunk动态获取physical地址情况下的接口索引,以保证主备一致 */
typedef struct tagTrunkDynMacIndex
{
    ULONG  ulTrunkId;
    ULONG  ulMacPortIndex;
    UCHAR  ucMacAddress[TRUNK_MACADDR_LEN];  /* Trunk接口physical地址     */
    UCHAR  ucPadding[2];
}TRUNK_DYNMAC_INDEX;

/* trunk 成员端口physical地址备份 */
typedef struct tagTrunkPortMac
{
    ULONG  ulTrunkId;
    ULONG  ulPortIndex;
    UCHAR  ucBakMacAddress[TRUNK_MACADDR_LEN];       /* 主板成员端口的实际physical地址 */
    UCHAR  Padding[2];    
}TRUNK_PORTMAC_S;

/* 备份端口优先级 */
typedef struct tagTrunkPortPri
{
    ULONG  ulPortIndex;
    ULONG  ulPortPri;
}TRUNK_PORT_PRI_S;

typedef struct tagTrunkBackupModeBak
{
    ULONG ulTrunkId;
    ULONG ulMode;
}TRUNK_BACKUPMODE_BAK_S;

typedef struct tagTrunkMasterPortBak
{
    ULONG ulTrunkId;
    ULONG ulMasterIfIndex;
}TRUNK_MASTERPORT_BAK_S;

typedef struct tagTrunkRecoverModeBak
{
    ULONG ulTrunkId;
    ULONG ulMode;
}TRUNK_RECOVERMODE_BAK_S;

typedef struct tagTrunkActiveNumBak
{
    ULONG ulTrunkId;
    ULONG ulActiveNum;
}TRUNK_ACTIVENUM_BAK_S;

typedef struct tagTrunkPassiveBak
{
    ULONG ulTrunkId;
    ULONG ulPassive;
}TRUNK_PASSIVE_BAK_S;

typedef struct tagTrunkSysPriByIdBak
{
    ULONG ulTrunkId;
    USHORT usSysPri;
    USHORT usPadding;
}TRUNK_SYSPRI_BYID_BAK_S;

/* Add by shuxieliu00176784/baiweiqiang00177000, at 2011-06-29. 修改原因: 产品定制策略备份  */
typedef struct tagTrunkProductPolicyBak
{
    ULONG ulTrunkId;
    ULONG ulProductPolicy;
}TRUNK_PRODUCT_POLICY_BAK_S;


/* 定义TRUNK HA 函数定义错误码 */
enum tagTrunkHAErr
{
    PACK_TRUNK_OK =  VOS_OK,
    PACK_TRUNK_ERR = VOS_ERR,
    PACKET_TOO_LONG,
    TRUNK_NEED_PACK,
    TRUNK_NO_NEED_PACK   
};

/* 设置HA报文的头(外部总体) */
#define HA_HEAD_TRUNK_SET(pucData, ucBakOperation, usBakMsgLen)\
{\
    HAMSGHEADER_S* pstHaHdr = NULL;\
    pstHaHdr = (HAMSGHEADER_S *)(pucData);\
    pstHaHdr->usMsgLen = (USHORT)usBakMsgLen;\
    pstHaHdr->ulSeq = 0;\
    pstHaHdr->ucModID = (UCHAR)HA_MID_TRUNK;\
    pstHaHdr->ucOperation = (UCHAR)ucBakOperation;\
}

/* 设置TRUNK HA内部报文的头*/
#define HA_TRUNK_HEAD_BAK_SET(pstTrunkHeadBak, usBakType, usBakLen)\
{\
    (pstTrunkHeadBak)->usType = (USHORT)(usBakType);\
    (pstTrunkHeadBak)->usLen = (USHORT)(usBakLen);\
}

/* add by lijing for V1R6C02维优增强项目 */
/* 设置Trunk Lacp协商信息*/
#define HA_TRUNK_LACP_NEGO_BAK_SET(stLacpNegoTo, stLacpNegoFrom)\
{\
    stLacpNegoTo.ulDefaulted = stLacpNegoFrom.ulDefaulted;\
    stLacpNegoTo.ucActorAdminState = stLacpNegoFrom.ucActorAdminState;\
    stLacpNegoTo.ucActorOperState = stLacpNegoFrom.ucActorOperState;\
    stLacpNegoTo.usActorAdminKey = stLacpNegoFrom.usActorAdminKey;\
    stLacpNegoTo.usActorOperKey = stLacpNegoFrom.usActorOperKey;\
    stLacpNegoTo.usActorPortPri = stLacpNegoFrom.usActorPortPri;\
    stLacpNegoTo.usActorPortIndex = stLacpNegoFrom.usActorPortIndex;\
    stLacpNegoTo.ucPartnerAdminState = stLacpNegoFrom.ucPartnerAdminState;\
    stLacpNegoTo.ucPartnerOperState = stLacpNegoFrom.ucPartnerOperState;\
    stLacpNegoTo.usPartnerAdminKey = stLacpNegoFrom.usPartnerAdminKey;\
    stLacpNegoTo.usPartnerOperKey = stLacpNegoFrom.usPartnerOperKey;\
    stLacpNegoTo.usPartnerAdminPortPri = stLacpNegoFrom.usPartnerAdminPortPri;\
    stLacpNegoTo.usPartnerOperPortPri = stLacpNegoFrom.usPartnerOperPortPri;\
    stLacpNegoTo.usPartnerAdminPortIndex = stLacpNegoFrom.usPartnerAdminPortIndex;\
    stLacpNegoTo.usPartnerOperPortIndex = stLacpNegoFrom.usPartnerOperPortIndex;\
    stLacpNegoTo.usPartnerAdminSysPri = stLacpNegoFrom.usPartnerAdminSysPri;\
    stLacpNegoTo.usPartnerOperSysPri = stLacpNegoFrom.usPartnerOperSysPri;\
    (VOID)TCPIP_Mem_Copy(stLacpNegoTo.ucPartnerAdminSysMac,TRUNK_MACADDR_LEN,stLacpNegoFrom.ucPartnerAdminSysMac, TRUNK_MACADDR_LEN);\
    (VOID)TCPIP_Mem_Copy(stLacpNegoTo.ucPartnerOperSysMac,TRUNK_MACADDR_LEN,stLacpNegoFrom.ucPartnerOperSysMac, TRUNK_MACADDR_LEN);\
}

#ifdef    __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _TRUNK_HA_H */
