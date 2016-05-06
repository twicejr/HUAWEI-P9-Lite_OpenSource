/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4c_ha.h
*
*  Project Code:    VISP1.6
*   Module Name:  DHCP client Module   
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

#ifndef _DHCP4C_HA_H_
#define _DHCP4C_HA_H_

#ifdef  __cplusplus
extern  "C"{
#endif

#define DHCP4C_BOUND_BAK                   32    /* DHCP会话控制块备份 */
#define DHCP4C_UNBOUND_BAK                 33    /* 去绑定DHCP会话 */
#define DHCP4C_FSM_IFDOWN_BAK              34    /* 非UP的DHCP会话控制块备份 */

#define DHCP4C_ENABLE_DHCP_FLAG_BAK        40    /*  使能DHCP获得地址操作 */
#define DHCP4C_DISABLE_DHCP_FLAG_BAK       41    /*  去使能DHCP获得地址操作 */
#define DHCP4C_ISRENEW_BAK                 42    /*  重新获得接口的DHCP地址 */
#define DHCP4C_ISRELEASEING_BAK            0x08  /*  释放接口的DHCP地址操作 */

#define DHCP4C_CFG_ITEM_BAK                50    /*  DHCP配置块的备份 */
#define DHCP4C_CFG_CIADDR_BAK              51    /*  DHCP的CIADDR参数的备份 */
#define DHCP4C_OPTION_DEL_BAK              52    /*  删除参数 */

#define DHCP4C_OPTION_VSI_BAK              43    /* VIS的备份头部标记 */
#define DHCP4C_OPTION_CLIENTID_BAK         61    /* CID备份的头部标记 */

#define DHCP4C_IFNET_DOWN_BAK              70    /* 接口down事件的备份 */
#define DHCP4C_IFNET_DELETE_BAK            71    /*接口删除的备份*/

#define DHCP4C_CFG_DEFAULTIP_SET_BAK       80    /* 设置DHCP默认地址 */
#define DHCP4C_CFG_DEFAULTIP_DEL_BAK       81    /* 删除DHCP默认地址 */

#define DHCP4C_CONFIG_LIST                 1     /*  配置链表 */
#define DHCP4C_SESSION_LIST                2     /*  会话链表 */

#define DHCP4C_BAK_VIRTUAL                 0x80

#define DHCP4C_BAK_GLOBALCFG               0x81  /* 全局配置信息备份操作,ha公共头操作字段 */

enum enumDHCP4CNEWBAKMsgType  /*新的DHCP HA头消息类型,占两个字节*/
{
    DHCP4C_NEWBAK_VIRTUAL_INFO = 0X0100,/*VISPV1R7新增的备份项类型值从0X0100开始,前面的值预留给VISPV1R6*/
    DHCP4C_DNS_BAK_INFO_CODE = 0X0101,
    DHCP4C_GATEWAYIP_BAK_INFO_CODE = 0x0102,
    DHCP4C_DOMAIN_BAK_INFO_CODE = 0x0103,
    
    DHCP4C_GLOBALCFG_BAK = 0x0200,     /* dhcp4c全局配置信息备份             */
    DHCP4C_GLOBALCFG_BAK_TOS,          /* 子tlv－tos值备份                   */
    DHCP4C_GLOBALCFG_BAK_IGNOREOPTION, /* 子TLV－是否忽略50/55/57选项标记    */
    DHCP4C_GLOBALCFG_BAK_END,          /* 后续要在此前添加全局配置信息tlv    */

    DHCP4C_ENABLERMT_OUTIF_BAK = 0x0300,    /* 指定出接口使能DHCP时备份出接口信息 */
};

#ifndef DHCP4C_HA_CAL_CFG_SIZE
#define DHCP4C_HA_CAL_CFG_SIZE(ulCIDLen, ulVSILen) \
             (ulCIDLen + ulVSILen + ((4 - (ulCIDLen + ulVSILen) % 4))%4)
#endif

/* 使能DHCP时需要备份的信息 */
typedef struct tagDHCP4C_ENABLEPARA
{
    ULONG  ulFlag;         /* DHCP使能标志 */
    ULONG  ulOutIfIndex;   /* DHCP使能时指定的出接口索引 */
}DHCP4C_ENABLEPARA_S;

typedef struct tagDHCP4C_PACKET_HEAD_BAK
{
    USHORT usType;                 /* 备份消息块类型 */
    USHORT usLen;                  /* 备份消息块的总长度 */
    ULONG  ulIfIndex;              /* 配置块所属的接口索引 */
    ULONG  ulExtend;               /*  扩展字段*/
}DHCP4C_PACKET_HEAD_BAK_S;

typedef struct tagDHCP4C_FSM_IFDOWN_BAK
{
    USHORT usType;                         /* 备份消息块类型 */
    USHORT usLen;                          /* 备份消息块的总长度 */
    ULONG  ulIfIndex;                      /* 配置块所属的接口索引 */
    ULONG  ulInterfaceIPAddr;              /* interface address  */
    ULONG  ulLeaseTimeSince1970;           /* lease time in seconde since 1970/1/1 00:00:00*/
    UCHAR  pucChaddr [DHCP4C_CHADDR_LEN];  /* 硬件地址 */
}DHCP4C_FSM_IFDOWN_BAK_S;

typedef struct tagDHCP4C_UP_HEAD_BAK
{
    USHORT  usType;              /* 备份消息块类型 */
    USHORT  usLen;              /* 备份消息块的总长度 */
    ULONG   ulXID;              /* Transaction ID */
    ULONG   ulInterfaceIndexID; /* Interface Index ID */
    ULONG   ulInterfaceIPAddr;  /* interface address  */
    ULONG   ulInterfaceSubnetMask;    /* the interface's subnetmask  */
    ULONG   ulGatewayIPAddr[DHCP4C_ROUTER_NUM];      /* the Gatewey address */
    ULONG   ulDNSIPAddr[DHCP4C_DNSIP_NUM];/* the Domain Nane Server's address */
    CHAR    pcDomainName[DHCP4C_DOMAINNAME_SIZE];   /* the Domain Name */
    ULONG   ulServerIdentifier;                      /* the DHCP server identifier */
    UCHAR   pucChaddr [DHCP4C_CHADDR_LEN];           /* client hardware address */
    ULONG   ulLeaseTime;      /* address lease time */
    ULONG   ulRenewTime;      /* renewal time value  */
    ULONG   ulRebindTime;     /* rebinding time value */
    ULONG   ulFSMState;       /* FSM state */    
}DHCP4C_UP_HEAD_BAK_S;

typedef struct tagDHCP4C_CFG_NODE_BAK
{
    USHORT  usType;              /* 备份消息块类型 */
    USHORT  usLen;              /* 备份消息块的总长度 */
    ULONG    ulIfIndex;           /* 配置块所属的接口索引 */
    ULONG    ulConfigFlag;        /* 配置的标记 */
    ULONG    ulCiaddr;            /* 配置的Ciaddr 值 */
    ULONG    ulCIDLen;            /* 配置的CID值长度 */  
    ULONG    ulVSILen;            /* 配置的VSI值长度 */
    /*added by l61496 增加DHCP默认地址的备份项*/
    ULONG ulDHCPDefaultIP;     /* Default address*/
    ULONG ulDHCPDefaultSubMask; /* Default sub mask */
}DHCP4C_CFG_NODE_BAK_S;


typedef struct tagDHCP4C_HA_HEAD_BAK
{
    USHORT usType;                         
    USHORT usLen;                          
}DHCP4C_HA_HEAD_BAK_S;

typedef struct tagDHCP4C_HA_VIRTUAL_INFO_BAK
{
    ULONG ulIfIndex;                         
    ULONG ulDHCPClientIP;
    ULONG ulDHCPClientIPMask;
    ULONG ulFlag;    
}DHCP4C_HA_VIRTUAL_INFO_S;

typedef struct tagDHCP4C_DNSTLV_BAK
{
    USHORT usType;
    USHORT usLen;
    ULONG aulDNSIP[DHCP4C_DNSIP_NUM];  
}DHCP4C_DNSTLV_BAK_S;

typedef struct tagDHCP4C_GATEWAYIPTLV_BAK
{
    USHORT usType;
    USHORT usLen;
    ULONG aulGatewayIP[DHCP4C_ROUTER_NUM];
}DHCP4C_GATEWAYIPTLV_BAK_S;

typedef struct tagDHCP4C_DOMAINTLV_BAK
{
    USHORT usType;
    USHORT usLen;
    UCHAR ucDomainName[DHCP4C_DOMAINNAME_SIZE];
}DHCP4C_DOMAINTLV_BAK_S;

typedef struct tagDHCP4C_TLV_HEAD_BAK
{
    USHORT usType;
    USHORT usLen;
}DHCP4C_TLV_HEAD_BAK_S;

typedef struct tagDHCP4C_TOSTLV_BAK
{
    DHCP4C_TLV_HEAD_BAK_S stTlvHdr;
    UCHAR  ucTos;
    UCHAR  ucPad[3];
}DHCP4C_TOSTLV_BAK_S;

typedef struct tagDHCP4C_IGNOREOPTION_BAK
{
    DHCP4C_TLV_HEAD_BAK_S stTlvHdr;
    ULONG  ulIgnoreOption;
}DHCP4C_IGNOREOPTION_BAK_S;

/* 设置HA报文的头(外部总体) */
#define HA_DHCP4C_BAK_SESS_SET(pstUpSession, pstSession)\
{\
    pstUpSession->ulXID = pstSession->ulXID;\
    pstUpSession->ulInterfaceIndexID = pstSession->ulInterfaceIndexID;\
    pstUpSession->ulInterfaceIPAddr = pstSession->ulInterfaceIPAddr;\
    pstUpSession->ulInterfaceSubnetMask = pstSession->ulInterfaceSubnetMask;\
    (VOID)TCPIP_Mem_Copy(pstUpSession->ulGatewayIPAddr, DHCP4C_ROUTER_NUM * sizeof(ULONG), pstSession->ulGatewayIPAddr, DHCP4C_ROUTER_NUM * sizeof(ULONG));\
    (VOID)TCPIP_Mem_Copy(pstUpSession->ulDNSIPAddr, DHCP4C_DNSIP_NUM * sizeof(ULONG), pstSession->ulDNSIPAddr, DHCP4C_DNSIP_NUM * sizeof(ULONG));\
    (VOID)TCPIP_Mem_Copy(pstUpSession->pcDomainName, DHCP4C_DOMAINNAME_SIZE, pstSession->pcDomainName, DHCP4C_DOMAINNAME_SIZE);\
    pstUpSession->ulServerIdentifier = pstSession->ulServerIdentifier;\
    (VOID)TCPIP_Mem_Copy(pstUpSession->pucChaddr, DHCP4C_CHADDR_LEN, pstSession->pucChaddr, DHCP4C_CHADDR_LEN);\
    pstUpSession->ulLeaseTime = pstSession->ulLeaseTime;\
    pstUpSession->ulRenewTime = pstSession->ulRenewTime;\
    pstUpSession->ulRebindTime = pstSession->ulRebindTime;\
    pstUpSession->ulFSMState = pstSession->ulFSMState;\
}

ULONG DHCP4C_HA_VirtualCfgInput(UCHAR *pucBuf, USHORT usDataLen);
ULONG DHCP4C_HA_SendVirtualInfo(IFNET_S *pstIf);
ULONG DHCP4C_HA_BuildOnePacket(USHORT usType, ULONG ulIfIndex, UCHAR *pucData, UCHAR *pucInBuf, USHORT usInBufLen);
ULONG DHCP4C_HA_SendPacket(UCHAR * pucData, USHORT usDataLen);
VOID DHCP4C_HA_ReleaseDhcpFlag(ULONG ulIndex, ULONG usFlag);
ULONG DHCP4C_HA_BatchBackup();
ULONG DHCP4C_HA_Input(UCHAR *pucInBuf, USHORT usDataLen);
ULONG DHCP4C_HA_Smooth();
ULONG DHCP4C_HA_BuildSendOnePacket(USHORT usType, ULONG ulIfIndex, UCHAR * pucData, USHORT usInBufLen);
ULONG TCPIP_HA_SetDhcpDbg(ULONG ulDbg);
ULONG DHCP4C_HA_CheckEnableDhcp(ULONG ulIfIndex);
ULONG DHCP4C_HA_GetDhcpDbg(ULONG *pulDbg);
VOID *DHCP4C_GetNext(VOID *pCur,VOID **ppNext);
ULONG DHCP4C_OpenEntry (UINTPTR *pulWaitListHandle, ULONG ulWaitId);
ULONG DHCP4C_GetEntry (UINTPTR ulEntryWaitList, UCHAR *ucData, ULONG ulDataSize, ULONG ulType);
ULONG DHCP4C_CloseObject (UINTPTR ulWaitListHandle);
DHCP4C_SESSION_S *DHCP4C_HA_CreateAtSlave (ULONG ulIfIndex);
/* Modified by caili cKF34546,创建socket不依赖于是否有session, 2011/2/15 问题单号:DTS2011012803825 */
ULONG DHCP4C_HA_CreateSocketAtSlave (VOID);
/*End of Modified by caili cKF34546,2011/2/15 问题单号:DTS2011012803825 */
ULONG DHCP4C_HA_GetDhcp4cVerboseDbg (ULONG *pulDbg);
ULONG DHCP4C_HA_SetDhcp4cVerboseDbg(ULONG ulDbg);
VOID DHCP4C_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
ULONG DHCP4C_HA_Clean(VOID);
ULONG DHCP4C_HA_GlobalCfg_BackUp(ULONG ulBakType);
ULONG DHCP4C_HA_GlobalCfg_Input(UCHAR *pucData, ULONG ulDataLen);

#ifdef  __cplusplus
}
#endif

#endif

