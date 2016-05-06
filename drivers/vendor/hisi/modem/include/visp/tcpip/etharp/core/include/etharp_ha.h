/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              etharp_ha.h
*
*  Project Code: VISPV100R006
*   Module Name: HA
*  Date Created: 2006-12-04
*        Author: xiehuaguo
*   Description: 以太备份处理头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-04  xiehuaguo        Create
*
*******************************************************************************/

#ifndef _ETHARP_HA_H_
#define _ETHARP_HA_H_

#ifdef  __cplusplus
extern "C"{
#endif


/* 以太备份消息头 */
typedef struct tag_ETH_BAK
{
    ULONG    ulMsgType; /* 消息类型 */
    ULONG    ulArpItems;   /* ARP项备份的个数*/
} ETH_BAK_S ;

typedef struct tag_ARP_BAK_UPGRADE
{
    ULONG     ulIfIndex;        /* 接口索引 */
    ULONG     ulIpAddr;         /* 地址 */
    ULONG     ulRtExpire;       /* 超时时间 */
    UCHAR     szMac[MACADDRLEN];/* physical地址 */
    UCHAR     ucFlags;          /* ARP标记*/
    UCHAR     ucSourceType;      /*动态ARP的来源:自学习、用户配置、配置后给自学习更新*/
    ULONG     ulVrfIndex;       /* 实例索引 */    
    USHORT    usVID;            /* VLAN ID */
    USHORT    usReserved;       /* 保留 */ 
}ARP_BAK_UPGRADE_S;

#define ETHARP_BAK_STATIC_BASE(from, to )\
{\
    (to)->ulIpAddr   =  (from)->ulIpAddr ;\
    (to)->ucFlags    =  (from)->ucFlags ;\
    (to)->ulIfIndex  =  (from)->ulIfIndex;\
    (to)->ulVrfIndex  =  (from)->ulVrfIndex;\
    (to)->usVID      =  (from)->usVID;\
    (VOID)TCPIP_Mem_Copy((to)->szMac,MACADDRLEN,(from)->szMac,MACADDRLEN);\
}

/* 备板接收备份动态ARP恢复宏*/
#define ETHARP_BAK_DYNAMIC_BASE(from, to )\
{ \
    (to)->ulIfIndex   =  (from)->ulIfIndex ;\
    (to)->ulIpAddr    =  (from)->ulIpAddr ;\
    (to)->ucFlags     =  (from)->ucFlags ;\
    (to)->ulRtExpire  =  (from)->ulRtExpire ;\
    (to)->ulVrfIndex  =  (from)->ulVrfIndex;\
    (to)->usVID       =  (from)->usVID;\
    (to)->ucSourceType = (from)->ucSourceType;\
    (VOID)TCPIP_Mem_Copy((to)->szMac,MACADDRLEN,(from)->szMac,MACADDRLEN);\
}

/* End: VISP Support multi-instance project */

/* 以太配置信息备份结构 */
typedef struct tag_ETH_BAK_CFG_S
{
    ULONG     ulIfIndex;        /* 接口索引 */
    USHORT    usIsARPproxy;     /* ARP代理标记 */
    USHORT    usDhcpflag ;      /* 接口是否使能DHCP标记 */  
    UCHAR     ucBakEthMac [MACADDRLEN];/* 接口MAC */  
    UCHAR     ucEnableSpecArpPrxy; /* 特殊ARP代理标记 */
    UCHAR     ucVlanflag;   /* 接口VLAN使能标记 */

}ETH_BAK_CFG_S;


/* 以太备份消息类型 */
enum enumEthBAKMsgType
{
    ETH_BAK_ARP = 1,
    ETH_BAK_CONFIG,
    ETH_BAK_ARP_ADD,
    ETH_BAK_ARP_DELETE,
    ETH_BAK_ARP_UPDATE,
    ETH_BAK_GLOBAL,
    ETH_BAK_TLV,
    ETH_BAK_VLANID,
    ETH_BAK_ARP_ADD_VRF,
    ETH_BAK_ARP_DELETE_VRF,
    ETH_BAK_ARP_UPDATE_VRF,
    /* End: VISP Support multi-instance project */
    ETH_BAK_DARP_USERADD,
    ETH_BAK_SARP_CONFLICT,
    ETH_BAK_ARPTIME, /* BC3D01640 用户可以按ETH接口设置动态ARP表项的老化超时时间 备份处理 */
    ETH_BAK_SUBVLAN,
    ETH_BAK_ISISFLAG,
    ETH_BAK_ARPGUARD,
    ETH_BAK_ARPCAPTURE,
};

enum enumEthBAKSubMsgType
{
    ETH_BAK_FREEARPMAXTIMES,
    ETH_BAK_FREEARPMAXNUM,
    ETH_BAK_ARPSTRICTLEARNSWITCH,
    ETH_BAK_ARPUNICASTCOUNT,
    ETH_BAK_ARPEXPIREOFFSET,
};

/*ETHARP模块HA备份消息头*/
typedef struct tagETHARP_HA_HEAD
{
    USHORT usEthOprType;  /* ETHARP备份消息类型  */
    USHORT usEthOprLen;   /* ETHARP备份消息长度  */
}ETHARP_HA_HEAD_S;

/* 以太备份消息TLV */
typedef struct tag_ETH_BAK_GLOBAL_TLV
{
    USHORT    usTlvType;   /* TLV消息类型 */
    USHORT    usTlvLen;    /* TLV长度*/
} ETH_BAK_GLOBAL_TLV_S ;

typedef struct tag_ETH_BAK_VLANID_S
{
    ULONG     ulMsgType;        /*消息类型*/
    ULONG     ulLen;            /*报文长度*/
    ULONG     ulIfIndex;        /* 接口索引 */
    ULONG     ulVlanID;         /* 接口VLAN ID*/
}ETH_BAK_VLANID_S;
 
/* BC3D01640 用户可以按ETH接口设置动态ARP表项的老化超时时间 备份处理 */
typedef struct tag_ETH_BAK_ARPTIME_S
{
    ULONG     ulMsgType;        /*消息类型*/
    ULONG     ulLen;            /*报文长度*/
    ULONG     ulIfIndex;        /* 接口索引 */
    ULONG     ulArpExpireTime;  /* 接口arp时间 */
}ETH_BAK_ARPTIME_S;

typedef struct tag_ETH_BAK_ISISFLAG_S
{
    ULONG     ulMsgType;        /*消息类型*/
    ULONG     ulLen;            /*报文长度*/
    ULONG     ulIfIndex;        /* 接口索引 */
    ULONG     ulISISFlag;       /* ISIS使能标记 */
}ETH_BAK_ISISFLAG_S;

typedef struct tag_ETH_BAK_DARPUSERADD_S
{
    ULONG      ulMsgType;        /* 消息类型 */
    ULONG      ulLen;            /* 报文长度 */
    ULONG      ulIpAddr;         /* 地址 */
    ULONG      ulIfIndex;        /* 接口索引 */
    UCHAR      ucDArpUserAddflag; /* 动态ARP用户添加标记 */
    UCHAR      ucPadding[3];
}ETH_BAK_DARPUSERADD_S;

typedef struct tag_ETH_BAK_SARPCONFLICT_S
{
    ULONG      ulMsgType;               /* 消息类型 */
    ULONG      ulLen;                   /* 报文长度 */
    ULONG      ulIpAddr;                /* 地址 */
    ULONG      ulVrfId;                 /* 实例号 */
    UCHAR      ucSArpConflictFlag;      /* 静态ARP和动态ARP冲突标记 */
    UCHAR      ucPadding[3];
}ETH_BAK_SARPCONFLICT_S;

typedef struct tag_ETH_SUB_HEAD_BAK
{
    ULONG    ulMsgType; /* 消息类型 */
    ULONG    ulLength;   /* 备份报文的总长度*/
} ETH_SUB_HEAD_BAK_S ;

/* Add for DTS2011080805208 , by zhaoyue00171897, at 2011-08-09. 修改原因: 设置ARP队列长度支持HA */
typedef struct tag_ETH_BAK_ARPCAPTURE_S
{
    ULONG     ulMsgType;        /*消息类型*/
    ULONG     ulLen;            /*报文长度*/
    ULONG     ulIfIndex;        /* 接口索引 */
    ULONG     ulRcvCaptureQueLen;  /* 接收队列长度 */
    ULONG     ulSndCaptureQueLen;  /* 发送队列长度 */
}ETH_BAK_ARPCAPTURE_S;

#define ETH_REALTIME_BAK         0
#define ETH_BATCH_BAK            1

/*每次批备份的ARP个数*/
#define  ETH_BAK_MAX_ITEM        20  

/*以太备份消息首部长度*/
#define  ETH_BAK_HEAD_LEN       (sizeof(ETH_BAK_S) + sizeof(HAMSGHEADER_S))

/*由于下面两个宏只在主板发送的时候调用，所以，在里面添加了备份Vrf信息*/
/* 备份静态ARP*/
#define ETHARP_BAK_STATIC_ARP(from, to )\
{\
    (to)->ulIpAddr   =  (from)->ulRtIpAddr ;\
    (to)->ucFlags    =  (UCHAR)((from)->ulFlags) ;\
    (to)->ulIfIndex  =  (from)->ulRtIfIndex;\
    (to)->ulVrfIndex  =  (from)->ulVrfIndex;\
    (to)->usVID      =  (from)->usVID;\
    (VOID)TCPIP_Mem_Copy((to)->szMac,MACADDRLEN,(from)->ucMacAddr,MACADDRLEN);\
}

/* 备份动态ARP*/
#define ETHARP_BAK_DYNAMIC_ARP(from, to )\
{ \
    (to)->ulIfIndex   =  (from)->ulRtIfIndex ;\
    (to)->ulIpAddr    =  (from)->ulRtIpAddr ;\
    (to)->ucFlags     =  (UCHAR)((from)->ulFlags) ;\
    (to)->ulRtExpire  =  (from)->ulRtExpire ;\
    (to)->ulVrfIndex  =  (from)->ulVrfIndex;\
    (to)->usVID       =  (from)->usVID;\
    (to)->ucSourceType = (from)->ucSourceType;\
    (VOID)TCPIP_Mem_Copy((to)->szMac,MACADDRLEN,(from)->ucMacAddr,MACADDRLEN);\
}
/* End: VISP Support multi-instance project */


/* 备份配置信息 */
#define ETHARP_BAK_SND_CFG_INFO(from, to )\
{ \
    (to)->ulIfIndex     =  ((from)->pMtSoftIf)->if_ulIfIndex ;\
    (to)->usIsARPproxy  = (USHORT)((from)->bIsARPproxy) ;\
    (to)->ucEnableSpecArpPrxy    = (UCHAR)((from)->bEnableSpecArpPrxy) ;\
    (to)->ucVlanflag    =  (UCHAR)((from)->ulVlanFlag) ;\
    (VOID)TCPIP_Mem_Copy((to)->ucBakEthMac,MACADDRLEN,(from)->ucEthernetHeader,MACADDRLEN);\
}

/* 恢复配置信息 */
#define ETHARP_BAK_RCV_CFG_INFO(from, to )\
{ \
    (to)->bIsARPproxy  = (BOOL_T)((from)->usIsARPproxy) ;\
    (to)->bEnableSpecArpPrxy = (BOOL_T)((from)->ucEnableSpecArpPrxy);\
    (to)->ulVlanFlag   = (ULONG)(from)->ucVlanflag;\
    (VOID)TCPIP_Mem_Copy((to)->ucBakEthMac,MACADDRLEN,(from)->ucBakEthMac,MACADDRLEN);\
}

#define  ETH_SUB_BAK_HEAD_LEN       (sizeof(ETH_SUB_HEAD_BAK_S) + sizeof(HAMSGHEADER_S))

/*构造VLAN ID 的备份信息*/
#define ETHARP_BAK_SND_VLANID_INFO(from, to )\
{ \
    (to)->ulIfIndex     =  ((from)->pMtSoftIf)->if_ulIfIndex ;\
    (to)->ulVlanID      =  (from)->ulVlanId ;\
}

enum enumEthHaRetrunCode
{
    ETH_HA_OK,
    ETH_HA_ERR,                          /* 1 失败 */
    ETH_HA_MALLOC_FAIL,                  /* 2 分配内存失败 */
    ETH_HA_NEED_DELAY,                   /* 3 需要延时 */
    ETH_HA_WRITEHAQUE_FAIL,              /* 4 写HA队列失败 */ 
};


extern VOID *ETHARP_GetNextMt(VOID *pCur,VOID **ppNext);
extern ULONG ETHARP_OpenMtEntry (UINTPTR *pulWaitListHandle);
extern ULONG ETHARP_GetMtEntry (UINTPTR ulEntryWaitList, ETHARP_MTSOFTC_S **ppstMtSoftC);
extern ULONG ETHARP_CloseMtObject ( UINTPTR ulWaitListHandle);

extern ULONG ETHARP_HA_BatchBackup ();
extern ULONG ETHARP_HA_Input(UCHAR * pBuf, ULONG ulMsgLen);
extern ULONG ETHARP_HA_Smooth ();
extern ULONG ETHARP_HA_GetEthDbg (ULONG *pulDbg);
extern ULONG TCPIP_HA_SetEthDbg (ULONG ulDbg);
extern VOID ETHARP_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
extern ULONG ETHARP_HA_GetVerboseDbg (ULONG *pulDbg);
extern ULONG ETHARP_HA_SetVerboseDbg (ULONG ulDbg);

extern ULONG ETHARP_SetDhcpflag (ULONG ulIfindex , ULONG ulflag);
extern ULONG ETHARP_HA_SendArpMsg (ULONG ulCmd ,ETHARP_ARPRTENTRY_S *pNode);
extern ULONG ETHARP_HA_SendCfgMsg (ETHARP_MTSOFTC_S    *pstMt);
extern ULONG ETHARP_HA_Clean();
extern VOID ETHARP_HA_NEW_Send_GlobalVar(ULONG ulSubType);
extern VOID ETHARP_HA_NEW_BatchGlobalVar(VOID);
extern ULONG ETHARP_HA_NEW_GlobalVarInput(UCHAR *pBuf, ULONG ulMsgLen);
ULONG  ETHARP_HA_SendVlanIDMsg (ULONG ulIfIndex , ULONG ulVlanTag);
extern ULONG  ETHARP_HA_SendRealTypeMsg (UCHAR * pstNeedBakData, ULONG ulBakLen, ULONG ulType);
extern ULONG ETHARP_HA_BuildOneTLV(UCHAR *pucBuf, UCHAR * pstNeedBakData, ULONG ulType, ULONG *pulLen);
extern ULONG ETHARP_HA_BuildBatchType(UCHAR **pucData, UCHAR *pucNeedbackData,UCHAR **pHaHead, 
                               UCHAR **pHaTail, ULONG ulType, ULONG *pulTlvNum, ULONG *pulTotalNum);

extern ULONG ETHARP_HA_BatchArpTLV();
extern ULONG ETHARP_HA_BatchEthTLV();

extern VOID ETHARP_HA_RestorDArpFlag(ETH_BAK_DARPUSERADD_S * pstBakDArp);
extern VOID ETHARP_HA_RestoreSArpConflict(ETH_BAK_SARPCONFLICT_S *pstBakSArp);
extern ULONG ETHARP_HA_BuildHeaderAndSend(UCHAR *pHaBufHead, UCHAR *pHaData);
extern VOID ETHARP_SArpConflictSmooth(VOID);
extern ULONG ETHARP_HA_SetISISFlag(ULONG ulIfIndex,ULONG ulISISFlag);

#ifdef  __cplusplus
}
#endif
#endif

