/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              if_ha.h
*
*  Project Code: VISPV100R006
*   Module Name: HA
*  Date Created: 2006-12-04
*        Author: xiehuaguo
*   Description: 接口备份处理头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-12  xiehuaguo        Create
*  2008-08-13  f54882           for BC3D00221,同步问题单BC3D00185
*
*******************************************************************************/

#ifndef _IF_HA_H_
#define _IF_HA_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* 配置IFNET接口全局备份消息头*/
typedef struct tagIF_BAK_MSGHEAD
{
    USHORT  usMsgType;
    USHORT  usMsgLen;
} IF_BAK_MSGHEAD_S ;


typedef struct tagIF_BAK_DIMENSION_BASEDATA
{
    ULONG   ulIfFirstDim;
    ULONG   ulIfSecondDim;
} IF_BAK_DIMENSION_BASEDATA_S ;


/* IFNET配置备份结构 */
typedef struct tagIF_BAK_CONFIG
{
    ULONG    ulIfindex ;
    ULONG    ulMtu;
    ULONG    ulCfgMTU;
    ULONG    ulKeepAlive;
    ULONG    ulShutdown;
    ULONG    ulPhyStatus;
    ULONG    ulBaud;
} IF_BAK_CONFIG_S ;

/*IFNET备份消息首部*/
typedef struct tagIF_BAK
{
    ULONG   ulMsgType;    /*备份消息类型*/
    ULONG   ulBakItems;   /*备份数据个数*/
}IF_BAK_S ;

/* 设备节点备份结构  */
typedef struct tagIF_BAK_DEV
{
#define DEVICE_NAME_LEN 50
    CHAR      dev_pDeviceName[DEVICE_NAME_LEN];
    USHORT    dev_usSlot;
    USHORT    dev_usAdaptor;
    USHORT    dev_usUnit;
    USHORT    dev_usSubChan;
    USHORT    dev_usMaxChannel;
    USHORT    dev_usAuxFlag;
    USHORT    dev_usIntPri;
    ULONG     dev_ulFlag;
    ULONG     dev_ulTimeSlotBitMap;
    ULONG     dev_ulBandWidth;
}IF_BAK_DEV_S;

/* IFNET接口备份数据结构 */
typedef struct tag_IF_BAK_SNAP
{
    UCHAR   szIfName[IF_MAX_INTERFACE_NAME_LEN+1] ;
    ULONG   ulIfIndex ;
    ULONG   ulTopIfIndex ;
    ULONG   ulNetIfIndex ;
    ULONG   ulPhyStatus;       
    ULONG   ulShutdown;       
    ULONG   ulMTU;        
    ULONG   ulCfgMTU;  
    ULONG   ulKeepAlive;
    ULONG   ulBaud  ;      
}IF_BAK_SNAP_S ;


typedef struct tag_IF_BAK_STATE
{
    ULONG ulIfIndex;
    ULONG ulIfState;
}IF_BAK_STATE_S;

/*PPP模块新增信息HA备份标准消息头*/
typedef struct tagIF_1AGVERSION_TLV  
{
    USHORT usSubMsgType;
    USHORT usSubMsgLen;
    ULONG  ulIfIndex;
    UCHAR  uc1agVersion;
    UCHAR  ucReserve[3];
}IF_1AGVERSION_TLV_S;

typedef struct tagIF_1AGRCVDEFAULTVLAN_TLV  
{
    USHORT usSubMsgType;
    USHORT usSubMsgLen;
    ULONG  ulIfIndex;
    USHORT us1agRcvDefaultVlan;
    UCHAR  ucReserve[2];
}IF_1AGRCVDEFAULTVLAN_TLV_S;

typedef struct tagIF_LINESTATE_TLV  
{
    USHORT usSubMsgType;
    USHORT usSubMsgLen;
    ULONG  ulIfIndex;
    ULONG  ulIfLineState;
}IF_LINESTATE_TLV_S;

/* Add for DTS2011080805208, by zhaoyue00171897, at 2011-08-09. 修改原因: VLAN一致性告警门限支持HA */
typedef struct tagIF_VLANMAXWARNINGNUM_TLV
{
    USHORT usSubMsgType;
    USHORT usSubMsgLen;
    ULONG  ulIfIndex;
    ULONG  ulMaxWarningNum;
    USHORT usVlanWarningFlag;
    UCHAR  ucReserve[2];
}IF_VLANMAXWARNINGNUM_TLV_S;

/* IFNET备份消息类型 */
enum enumIfBAKMsgType
{
    IF_BAK_DEVICE =1,
    IF_BAK_IFNET,
    IF_BAK_CONFIG,
    IF_BAK_DEVICE_ADD,
    IF_BAK_CREATE,
    IF_BAK_DELETE,
    IF_BAK_GLOBAL,
    IF_BAK_VIRTUAL,
    IF_BAK_STATE,
    IF_BAK_CONFIGTLV,
    IF_BAK_TLV,
    IF_TUNNEL_BAK
};

/*VISPV1R7新增的备份项类型值从0X0100开始,前面的值预留给VISPV1R6*/

enum enumIFNETNEWBAKMsgType  /*新的IFNET HA头消息类型,占两个字节*/
{
    IF_GLOBAL_DIM_CONFIG_INFO = 0x0100, /* 三维模式下IFNET全局信息备份消息类型 */
    IF_VIRTUAL_CONFIG_INFO    = 0x0300, /* 三维虚拟接口状态配置信息备份消息类型 */ 
    IF_CONFIG_1AGVERSION,
    IF_CONFIG_1AGRCVDEFAULTVLAN,
    IF_CONFIG_IFLINESTATE,
    /* Add for DTS2011080805208, by zhaoyue00171897, at 2011-08-09. 修改原因: VLAN一致性告警门限支持HA */
    IF_VLAN_MAXWARNING_NUM,
};

enum IF_NEWBAK_TLV_MSG_TYPE
{
    IF_BAK_TLV_SET_DEV,         /* 设置接口物理参数 */
};

typedef struct tagIF_HA_TLV
{
    USHORT usTlvType;
    USHORT usTlvLen;
} IF_HA_TLV_S;

typedef struct tagIF_BAK_DEV_TLV
{
#define DEVICE_NAME_LEN 50
    CHAR   dev_pDeviceName[DEVICE_NAME_LEN];
    USHORT dev_usSlot;
    USHORT dev_usAdaptor;
    USHORT dev_usUnit;
    USHORT dev_usSubChan;
    USHORT dev_usMaxChannel;
    USHORT dev_usAuxFlag;
    USHORT dev_usIntPri;
    ULONG  dev_ulFlag;
    ULONG  dev_ulIf;
    ULONG  dev_ulTimeSlotBitMap;
    ULONG  dev_ulBandWidth;
}IF_BAK_DEV_TLV_S;

/*每次批备份的IFNET个数*/
#define  IFNET_BAK_MAXIF_ITEM      20    
/*每次批备份的设备节点个数*/
#define  IFNET_BAK_MAXDEV_ITEM     20
/*IFNET备份首部长度*/
#define  IFNET_BAK_HEAD_LEN        (sizeof(IF_BAK_S) + sizeof (HAMSGHEADER_S))
/*接口未内部平滑*/
#define  IFNET_BAK_NO_RECOVER      0x01
/*接口已外部平滑*/
#define  IFNET_BAK_CHECK_OVER      0x02
/*Added by z00208058, PTN需求，主备倒换过程中网管接口不删除，问题单DTS2012120607609, 2012/12/6 */
#define  IFNET_NOT_CLEAN          0x04

#define  IF_EXIST       2
#define  IF_INEXIST     3
#define  IF_ERR_OPENIFCONFIG 4
#define  IF_ERR_GETTRUNKID   5
#define  IF_ERR_GETTRUNKINFO 6

#define IF_BAK_SND_IF_STATE_COPY(from,to) \
{\
    (to)->ulIfIndex     = (from)->if_ulIfIndex; \
    (to)->ulIfState     = (from)->if_ulLineStatus; \
}

#define IF_BAK_SND_IF_PPPINFO_COPY(from,to) \
{\
    (to)->ulLocalIp  = (from)->pstPppVlink->ulLocalIp; \
    (to)->ulRemoteIp = (from)->pstPppVlink->ulRemoteIp; \
    (to)->ulFlag     = (from)->pstPppVlink->ulFlag; \
    (to)->ulVlinkIndex     = (from)->pstPppVlink->ulVlinkIndex; \
    (to)->ulIfIndex        = (from)->pstPppVlink->ulIfIndex; \
    (to)->ulMtu            = (from)->pstPppVlink->ulMtu; \
}

#define IF_BAK_SND_PPP_DNSTLV_COPY(from,to) \
{\
    (VOID)TCPIP_Mem_Copy((to)->aulDNSIP,sizeof(ULONG)*DHCP4C_DNSIP_NUM,(from)->pstPppVlink->aulDNSIP,sizeof(ULONG)*DHCP4C_DNSIP_NUM); \
}


#define IF_BAK_SND_IF_DHCPCINFO_COPY(from,to) \
{\
    (to)->ulDHCPClientIP  = (from)->pstDhcpcInfo->ulDHCPClientIP; \
    (to)->ulDHCPClientIPMask = (from)->pstDhcpcInfo->ulDHCPClientIPMask; \
    (to)->ulFlag  = (from)->pstDhcpcInfo->ulFlag; \
    (to)->ulIfIndex  = (from)->pstDhcpcInfo->ulIfIndex; \
}

#define IF_BAK_SND_DHCPC_DNSTLV_INFO_COPY(from,to) \
{\
    (VOID)TCPIP_Mem_Copy((to)->aulDNSIP,sizeof(ULONG)*DHCP4C_DNSIP_NUM,(from)->pstDhcpcInfo->aulDNSIP,sizeof(ULONG)*DHCP4C_DNSIP_NUM); \
}

#define IF_BAK_SND_DHCPC_GATEWAYTLV_INFO_COPY(from,to) \
{\
    (VOID)TCPIP_Mem_Copy((to)->aulGatewayIP,sizeof(ULONG)*DHCP4C_ROUTER_NUM,(from)->pstDhcpcInfo->aulGatewayIP,sizeof(ULONG)*DHCP4C_ROUTER_NUM); \
}

#define IF_BAK_SND_DHCPC_DOMAINTLV_INFO_COPY(from,to) \
{\
    (VOID)TCPIP_Mem_Copy((to)->ucDomainName,DHCP4C_DOMAINNAME_SIZE,(from)->pstDhcpcInfo->ucDomainName,DHCP4C_DOMAINNAME_SIZE); \
}


/*备份IFNET接口信息*/ 
#define IF_BAK_SND_IF_INFO_COPY(from,to) \
{\
    (to)->ulIfIndex     = (from)->if_ulIfIndex; \
    (to)->ulTopIfIndex  = (from)->if_ulTopIfIndex; \
    (to)->ulNetIfIndex  = (from)->if_ulNetIfIndex; \
    /* edit by L00105073 for 主备倒换后PPP重协商 */\
    /* (to)->ulPhyStatus  = (from)->ulPhyStatus; */\
    (to)->ulPhyStatus   = (from)->if_ulRawPhyStatus; \
    (to)->ulShutdown    = (from)->if_ulShutdown; \
    (to)->ulMTU         = (from)->if_ulMTU; \
    (to)->ulCfgMTU      = (from)->if_ulCfgMTU; \
    (to)->ulKeepAlive   = (from)->if_ulKeepAlive; \
    (to)->ulBaud        = (from)->if_ulBaud; \
    (VOID)TCPIP_Mem_Copy((to)->szIfName,IF_MAX_INTERFACE_NAME_LEN+1,(from)->if_szIfName,IF_MAX_INTERFACE_NAME_LEN+1);\
}

/*恢复IFNET接口信息*/ 
#define IF_BAK_RCV_IF_INFO_COPY(from,to)\
{\
    (to)->if_ulTopIfIndex  =  (from)->ulTopIfIndex;\
    (to)->if_ulNetIfIndex  =  (from)->ulNetIfIndex;\
    /* edit by L00105073 for 主备倒换后PPP重协商 */\
    /* (to)->if_ulPhyStatus   =  (from)->ulPhyStatus; */\
    IF_SET_RAWPHYSTATUS((to), (from)->ulPhyStatus);\
    (to)->if_ulShutdown    =  (from)->ulShutdown;\
    (to)->if_ulShutdown   &=  (~IF_DELETE) ;\
    (to)->if_ulMTU         =  (from)->ulMTU;\
    (to)->if_ulCfgMTU      =  (from)->ulCfgMTU;\
    (to)->if_ulKeepAlive   =  (from)->ulKeepAlive;\
    if((PORT_ETH_TRUNK != (to)->if_ulPortType) && (PORT_MP_GROUP != (to)->if_ulPortType))\
    {\
    (to)->if_ulBaud        =  (from)->ulBaud;\
    }\
}

/*备份IFNET备配信息*/ 
#define IF_BAK_SND_CFG_INFO_COPY(from, to) \
{ \
    (to)->ulIfindex    = (from)->if_ulIfIndex; \
    (to)->ulMtu        = (from)->if_ulMTU; \
    (to)->ulCfgMTU     = (from)->if_ulCfgMTU; \
    (to)->ulKeepAlive  = (from)->if_ulKeepAlive; \
    (to)->ulShutdown   = (from)->if_ulShutdown; \
    /* edit by L00105073 for 主备倒换后PPP重协商 */\
    /* (to)->ulPhyStatus  = (from)->ulPhyStatus; */\
    (to)->ulPhyStatus  = (from)->if_ulRawPhyStatus; \
    (to)->ulBaud       = (from)->if_ulBaud; \
}


/*恢复IFNET备配信息*/ 
#define IF_BAK_RCV_CFG_INFO_COPY(from, to) \
{ \
    (to)->if_ulIfIndex    =   (from)->ulIfindex;\
    (to)->if_ulMTU        =   (from)->ulMtu;\
    (to)->if_ulCfgMTU     =   (from)->ulCfgMTU; \
    (to)->if_ulKeepAlive  =   (from)->ulKeepAlive;\
    (to)->if_ulShutdown   =   (from)->ulShutdown;\
    (to)->if_ulShutdown   &=  (~IF_DELETE) ;\
    /* edit by L00105073 for 主备倒换后PPP重协商 */\
    /* (to)->if_ulPhyStatus  =   (from)->ulPhyStatus;\ */\
    IF_SET_RAWPHYSTATUS((to), (from)->ulPhyStatus);\
    if((PORT_ETH_TRUNK != (to)->if_ulPortType) && (PORT_MP_GROUP != (to)->if_ulPortType))\
    {\
    (to)->if_ulBaud        =  (from)->ulBaud;\
    }\
}

/*备份设备节点信息*/ 
#define IF_BAK_SND_DEV_INFO_COPY(from, to) \
{\
    (to)->dev_usSlot        = (from)->dev_usSlot;\
    (to)->dev_usAdaptor     = (from)->dev_usAdaptor;\
    (to)->dev_usUnit        = (from)->dev_usUnit;\
    (to)->dev_usSubChan     = (from)->dev_usSubChan;\
    (to)->dev_usAuxFlag     = (from)->dev_usAuxFlag;\
    (to)->dev_usMaxChannel  = (from)->dev_usMaxChannel;\
    (to)->dev_usIntPri      = (from)->dev_usIntPri;\
    (to)->dev_ulFlag        = (from)->dev_ulFlag;\
    (to)->dev_ulBandWidth   = (from)->dev_ulBandWidth;\
    (to)->dev_ulTimeSlotBitMap  = (from)->dev_ulTimeSlotBitMap;\
    (VOID)TCPIP_Mem_Copy((to)->dev_pDeviceName,DEVICE_NAME_LEN,(from)->dev_pDeviceName,DEVICE_NAME_LEN);\
}

/*恢复设备节点信息*/ 
#define IF_BAK_RCV_DEV_INFO_COPY(from, to) \
{\
   (to)->dev_usSlot        =   (from)->dev_usSlot;\
   (to)->dev_usAdaptor     =   (from)->dev_usAdaptor;\
   (to)->dev_usUnit        =   (from)->dev_usUnit; \
   (to)->dev_usSubChan     =   (from)->dev_usSubChan;\
   (to)->dev_usAuxFlag     =   (from)->dev_usAuxFlag;\
   (to)->dev_usMaxChannel  =   (from)->dev_usMaxChannel;\
   (to)->dev_usIntPri      =   (from)->dev_usIntPri;\
   (to)->dev_ulFlag        =   (from)->dev_ulFlag;\
   (to)->dev_ulBandWidth   =   (from)->dev_ulBandWidth;\
   (to)->dev_ulTimeSlotBitMap  =  (from)->dev_ulTimeSlotBitMap;\
   (VOID)TCPIP_Mem_Copy((to)->dev_pDeviceName,DEVICE_NAME_LEN,(from)->dev_pDeviceName,DEVICE_NAME_LEN);\
}

#define IF_BAK_COPY_DEVLINK(from, to) \
{\
    (to)->dev_usSlot        = (from)->dev_usSlot;\
    (to)->dev_usAdaptor     = (from)->dev_usAdaptor;\
    (to)->dev_usUnit        = (from)->dev_usUnit;\
    (to)->dev_usSubChan     = (from)->dev_usSubChan;\
    (to)->dev_usAuxFlag     = (from)->dev_usAuxFlag;\
    (to)->dev_usMaxChannel  = (from)->dev_usMaxChannel;\
    (to)->dev_usIntPri      = (from)->dev_usIntPri;\
    (to)->dev_ulFlag        = (from)->dev_ulFlag;\
    (to)->dev_ulIf          = (from)->dev_ulIf;\
    (to)->dev_ulBandWidth   = (from)->dev_ulBandWidth;\
    (to)->dev_ulTimeSlotBitMap  = (from)->dev_ulTimeSlotBitMap;\
    (VOID)TCPIP_Mem_Copy((to)->dev_pDeviceName,DEVICE_NAME_LEN,(from)->dev_pDeviceName,DEVICE_NAME_LEN);\
}

extern ULONG IF_HA_StateInput (UCHAR * pBuf, ULONG ulMsgLen);
extern ULONG IF_HA_VirtualInput(UCHAR * pBuf, ULONG ulMsgLen);
extern VOID IF_HA_SendVirtualInfo(IF_BAK_STATE_S *pstIfIpStatInfo);
extern ULONG TCPIP_HA_GetPhyInitByType(ULONG ulType, UCHAR * szIfName, UINTPTR *pfPhyInitial);
extern ULONG TCPIP_HA_GetIfPhyState(ULONG ulIfIndex);
extern ULONG IF_AddDevNode (DEVLINK_S *pstDev,ULONG ulFirstDim);
extern ULONG IF_DelDevNode (CHAR  * szIntName,ULONG ulFirstDim);
extern ULONG IF_HA_BatchBackup();
extern ULONG IF_HA_Input(UCHAR *pBuf,ULONG ulMsgLen);
extern ULONG IF_HA_SendIfMsg(ULONG  ulCmd,IFNET_S *pstIf);
extern ULONG IF_HA_SendCfgMsg(IFNET_S *pstIf);
extern ULONG IF_HA_Smooth ();
extern ULONG IF_HA_GetIfnetDbg (ULONG *pulDbg);
extern ULONG TCPIP_HA_SetIfnetDbg (ULONG ulDbg);
extern ULONG IF_HA_SetVerboseDbg (ULONG ulDbg);
extern ULONG IF_HA_GetVerboseDbg (ULONG *pulDbg);
extern VOID IF_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
extern ULONG IF_HA_Clean(VOID);


extern ULONG TCPIP_HA_VerifyInterface(ULONG ulIfIndex);

extern ULONG IF_CloseIfEntryByDepth(UINTPTR ulWaitListHandle);
extern ULONG IF_OpenIfEntryByDepth(UINTPTR *pulWaitListHandle);
extern ULONG IF_GetIfEntryByDepth(UINTPTR ulEntryWaitList, IFNET_S ** ppstIfConfig);
/*f47854 modify : 函数参数或者返回值类型与函数指针定义不匹配*/
extern VOID * IF_GetNextIfByDepth(VOID *pParam,VOID **pNewParam);
extern ULONG IF_OpenDeviceNodeTable (UINTPTR *pulWaitListHandle,ULONG ulFirstDim);
extern ULONG IF_GetDeviceNode (UINTPTR ulEntryWaitList, DEVLINK_S  *pstDevNode);
extern ULONG IF_CloseDeviceNodeTable( UINTPTR ulWaitListHandle );
extern ULONG  IF_HA_SendGlobalVar();

/* VISP1.8.1支持1ag标准协议格式新增 */
extern ULONG IF_HA_SendCfgMsgTLV(IFNET_S *pstIf, ULONG ulSubMsgType);
extern ULONG IF_HA_CfgInputTLV(UCHAR *pBuf, ULONG ulMsgLen);
extern ULONG IF_HA_BatchCfgMsgTLV(ULONG ulSubMsgType);

extern ULONG IF_HA_TLV_BuildOnePkt(ULONG ulIfIndex, UCHAR *pucBuf, USHORT usOffset, USHORT usTlvType, USHORT *pusBakLen);
extern ULONG IF_HA_TLV_RealTimeBak(ULONG ulIfIndex, USHORT usTlvType);
extern ULONG IF_HA_TLV_BatchBak(VOID);
extern ULONG IF_HA_TLV_Input(UCHAR *pucBuf, ULONG ulMsgLen);
extern ULONG IF_HA_TLV_Restore(ULONG ulIfIndex, UCHAR *pucBuf, USHORT usTlvType);
extern ULONG IF_HA_TLV_OutputMsg(UCHAR *pucBuf, UCHAR ucOperation, USHORT usMsgLen);
extern ULONG IF_HA_TLV_CalcMsgLen(USHORT usTlvType, USHORT *pusTlvLen);

/*Added by z00208058, PTN需求，主备倒换过程中网管接口不删除，问题单DTS2012120607609, 2012/12/6 */
extern ULONG TCPIP_HA_SetIfnetNotClean(ULONG ulIfIndex);

#ifdef  __cplusplus
}
#endif
#endif

