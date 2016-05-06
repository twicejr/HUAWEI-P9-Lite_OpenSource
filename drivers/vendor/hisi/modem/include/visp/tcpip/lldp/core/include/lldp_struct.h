/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              lldp_struct.h
*
*  Project Code: V2R3C06
*   Module Name:   
*  Date Created: 2011-09-27
*        Author: liangjicheng 00103192
*   Description: 内部结构体定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2011-09-27   liangjicheng 00103192   Create
*
*******************************************************************************/
#ifndef _LLDP_STRUCT_H_
#define _LLDP_STRUCT_H_

#ifdef  __cplusplus
extern "C"{
#endif
#ifndef PCK

typedef struct tagLLDP_RAW_PACKET_S
{
    ULONG  ulLength;
    UCHAR* pucBuf;
}LLDP_RAW_PACKET_S; 

/************************************************************************************/
typedef struct tagLLDP_BASIC_TLV_HEADER_S
{
    USHORT usTLVType : 7;                /*类型*/
    USHORT usTLVInfoLength : 9;          /*后面信息的长度*/
}LLDP_BASIC_TLV_HEADER_S;

typedef struct tagLLDP_VAR_STRING_S
{
    LLDP_BASIC_TLV_HEADER_S stLldpTLVheader;
    UCHAR ucString[2];                  /*TLV Value*/
    
}LLDP_VAR_STRING_S;

typedef struct tagLLDP_ETH_HEADER_S
{
    UCHAR     ucEthDMA[LLDP_MAC_ADDR_LEN];
    UCHAR     ucEthSMA[LLDP_MAC_ADDR_LEN];
    USHORT    usProtocolVer;           /* 协议版本号 ＝ 0x80CC */
}LLDP_ETH_HEADER_S;


/* LLDP协议报文格式 */
typedef struct tagLLDP_PACKET_S
{
    LLDP_ETH_HEADER_S stEthHeader;   /*以太网头*/
    
    LLDP_VAR_STRING_S stTLV[1];      /* 可变长度字符串 */
} LLDP_PACKET_S;

#endif

#ifndef TLV

/*Time To Live TLV*/
typedef struct tagLLDP_TTL_INFO_S
{
    USHORT usTTL;
    UCHAR ucResv[2]; 
}LLDP_TTL_INFO_S;

#endif

#ifndef GLOBAL


/* 用于内部 */
typedef struct tagLLDP_LOCAL_SYS_INFO_S
{
    /**系统全局共享的TLV**/
    LLDP_SYS_NAME_INFO_S stLocSysName;      /*system name TLV , 本端系统名称，默认值"System" */
    LLDP_SYS_DESC_INFO_S stLocSysDesc;      /* system description TLV,本端系统描述，默认值"System" */
    LLDP_SYS_CAPABILITY_INFO_S stSysCapability; /* system Capabilities TLV */ 
    LLDP_MANAGEMENT_VID_INFO_S stManagementVid;  /*Management VID TLV*/
    LLDP_MANAGEMENT_INFO_S stManagement; /** Management Address TLV  **/  

    LLDP_ADMIN_STATUS_E eAdminStatus;              /*本地设备使能LLDP标志*/
    ULONG ulTrapEnabled;                           /*告警使能标志*/  
    
    LLDP_GLOBAL_CFG_S stConfigutation;          /*LLDP全局配置信息*/
    LLDP_SYS_STAT_S         stStatsInfo;               /*LLDP全局统计信息*/   
    ULONG ulTickTimerID;                    /**/    
    /* Modified by zhangliangzhi00187023, 【检视发现问题】支持managevid tlv配置可删除, 2012/8/28   问题单号:DTS2012082808698  */
    ULONG ulManagementVidFlag;  /*Management VID TLV 是否有效*/
    /*End of Modified by zhangliangzhi00187023, 2012/8/28   问题单号:DTS2012082808698  */
    ULONG ulManagementAddressFlag;  /*Management TLV 是否有效*/
}LLDP_LOCAL_SYS_INFO_S;

#endif

#ifndef PORT

/***  邻居节点信息，用于内部系统存储***/
typedef struct tagLLDP_LOCAL_REM_INFO_S
{
    ULONG  ulPortIfIndex;         /* Remote所在端口的编号*/
    ULONG  ulDestAddrIndex;       /* Remote所在组播组的编号，取值范围（0~2）,切换到外部结构体时需加1
                                            DestMac：01:80:c2:00:00:0e（0）
                                            DestMac：01:80:c2:00:00:03（1）
                                            DestMac：01:80:c2:00:00:00（2）*/
    ULONG  ulRemIndex;            /* Remote编号，取值范围（1~7FFFFFFF）*/
    ULONG  ulRemLastMarkTime;         /* Remote上次变更的时间（单位：秒） */
    
    ULONG  ulTlvValidFlag;        /* Remote 携带的可选TLV有效标志（bit标识）
                                    ChassisId, PortId, Management必须携带，不占用标识位
                                      0-  System Name TLV
                                      1-  System Description TLV 
                                      2-  System Capability TLV
                                      3-  Port Description TLV
                                      4-  Management Address TLV
                                      5-  MAC/PHY Configuration/Status TLV
                                      6-  Port Vlan Id TLV
                                      7-  Max Frame Size TLV
                                      8-  Link Aggregation TLV
                                      9-  Power Via Mdi TLV
                                      10- Port and Protocol Vlan ID TLV*/
    USHORT usTTL;                 /* 邻居节点的老化时间, 取自报文中的TTL TLV.*/
    USHORT usRemTTL;              /* 邻居的TTL TLV中的信息*/
    LLDP_CHASSISID_INFO_S stRemChassisId;       /* Remote ChassisId TLV*/     
    LLDP_PORTID_INFO_S  stRemPortId;            /* Remote PortId TLV */ 
    LLDP_MANAGEMENT_INFO_S stRemManagement;
    LLDP_SYS_NAME_INFO_S stRemSysName;          /* 本端系统名称，默认值"System" */
    LLDP_SYS_DESC_INFO_S stRemSysDesc;          /* 本端系统描述，默认值"System" */
    LLDP_SYS_CAPABILITY_INFO_S stRemSysCapability;   
    LLDP_PORT_DESC_INFO_S stRemPortDesc;        /* Port Description TLV */
    LLDP_MAC_PHY_CFG_INFO_S stRemPhyCfgStatus;/* MAC/PHY Configuration/Status TLV */
    LLDP_PVID_INFO_S stRemPortVlanId;
    LLDP_MAX_FRAME_SIZE_INFO_S stRemMaxFrameSize;
    LLDP_LINK_AGG_INFO_S stLinkAgg;             /* Link Aggregation TLV */
    LLDP_POWER_VIA_MDI_INFO_S stPowerViaMdi;
    ULONG  ulPpvidNum;                          /* Port and Protocol Vlan ID TLV 个数*/
    LLDP_PPVID_INFO_S stPpvid[LLDP_MAX_PPVID_TLV_NUM]; /* PPVID TLV */
    LLDP_MANAGEMENT_VID_INFO_S stRemManagementVid; /* Management VID TLV */     
    UCHAR ucVlanNameNum;/* Vlan Name TLV 个数*/
    UCHAR ucRes[2];    
    LLDP_VLAN_NAME_INFO_S stRemVlanName[LLDP_MAX_VLAN_NAME_TLV_NUM]; /*Vlan Name TLV */    

}LLDP_LOCAL_REM_INFO_S; 

/*Added by guo00178934, 结构体名字变更, 2011/11/8   问题单号:DTS2011110800968 */
/*本端接口统计信息*/
typedef struct tagLLDP_LOCAL_PORT_STAT_S
{
    ULONG  ulRxFramesTotal;             /* 收到的LLDP 帧总数 */
    ULONG  ulRxDiscardedTotal;          /* 丢弃的LLDP 帧总数 */
    ULONG  ulRxErrorsTotal;             /* 收到的错误LLDP 帧总数 */
    ULONG  ulRxTLVsDiscardedTotal;      /* 丢弃的LLDP TLV 帧总数 */
    ULONG  ulRxTLVsUnrecognizedTotal;   /* 不可识别的LLDP TLV 帧总数 */
    ULONG  ulTxFramesTotal;             /* 发送的LLDP 帧总数 */
    ULONG  ulRxAgeoutsTotal;            /* 老化的LLDP 邻居信息总数 */
    /*Added by guo00178934, TLV详细查询, 2011/11/8   问题单号:DTS2011110800426 */
    ULONG  ulRxErrTLVSysName;
    ULONG  ulRxErrTLVSysDesc;
    ULONG  ulRxErrTLVSysCapability;
    ULONG  ulRxErrTLVPortDesc;
    ULONG  ulRxErrTLVManAddr;
    ULONG  ulRxErrTLVMacPhyCfg;
    ULONG  ulRxErrTLVPortVlanId;
    ULONG  ulRxErrTLVMaxFrameSize;
    ULONG  ulRxErrTLVLinkAgg;
    ULONG  ulRxErrTLVPowerViaMdi;
    ULONG  ulRxErrTLVPpvid;
    ULONG  ulRxErrTLVChassisId;
    ULONG  ulRxErrTLVPortId;   
    ULONG  ulRxErrTLVTTL;
    ULONG  ulRxErrTLVEndTLV;
    /* End of Added by guo00178934, 2011/11/8   问题单号:DTS2011110800426 */
}LLDP_LOCAL_PORT_STAT_S; 
/* End of Added by guo00178934, 2011/11/10   问题单号:DTS2011110800968 */

typedef struct tagLLDP_LOCAL_AGENT
{
    /*指向本agent直连邻居的信息LLDP_REM_INFO_S类型*/
    LLDP_LOCAL_REM_INFO_S *stRemNeighborDataArray[LLDP_AGENT_MAX_REMOTE_TABLE];
    LLDP_LOCAL_PORT_STAT_S  stStatsPort;             /*本地端口统计信息*/      
    ULONG ulPortMode;                                 /*接口模式 Tx、Rx、TxRx、Disable*/   
    ULONG ulRemNeighborNum;                 /*该agent有效邻居节点数量*/
    ULONG ulTransmitFsmState;               /*发送状态机状态*/
    ULONG ulTransmitTimerFsmState;          /*发送定时器状态机状态*/
    ULONG ulReceiveFsmState;                /*接收状态机状态*/
    ULONG ulTransmitTimerID;                /**/
    ULONG ulShutdownTimerID;                /**/
    ULONG ulRXInfoAgeTimerID;               /**/
    ULONG ulRxInfoAge;                        /**/
    ULONG ulRcvFrame;
    ULONG ulRxChanges;
    ULONG ulBadFrame;
    ULONG ulTxTTL;
    ULONG ulRxTTL;
    ULONG ulTxTick;
    ULONG ulTxNow;
    ULONG ulLocalChange;
    ULONG ulTxTTR;                          /*单位:ms*/
    ULONG ulTxFast;
    ULONG ulTxShutdownWhile;
    ULONG ulNewNeighbor;
    ULONG ulTxCredit;
    ULONG szMsg[4];
}LLDP_LOCAL_AGENT_S;



/*本地端口信息表项*/
typedef struct tagLLDP_LOCAL_PORT
{
    ULONG  ulIfIndex;                                 /* LLDP接口编号 */
    ULONG  ulPortEnabled;                             /*记录端口的状态,用于端口shut/undo shut操作*/    
    ULONG  ulPpvidNum;                               /* Port and Protocol Vlan ID TLV 个数*/
    CHAR  szIfName[LLDP_IF_NAME_LEN];              
    UCHAR szEthMAC[LLDP_MAC_ADDR_LEN];

    /*Added by luogaowei 2013-2-17  DTS2013021802156 是否是默认maximum frame size  VRP_YES 或者VRP_NO*/
    UCHAR ucDefaultMaxSizeTlv;       
    UCHAR ucResv; 
    USHORT usPktVLanId; /*报文头中Vlan Tag的ID, 不是Port Vlan ID TLV信息.*/
    USHORT usPktVLanPri; /*报文头中Vlan Tag的优先级, 不是Port Vlan ID TLV信息.*/
    ULONG ulLinkAggIfCfg; /*Link Aggregation TLV信息通过API配置进来(值为1),或通过LLDP_GetTrunkId获取的(0)*/
    
    LLDP_PORTID_INFO_S stPortID;                      /*Port ID TLV*/
    LLDP_TTL_INFO_S stTTL;                            /*Time To Live TLV*/    
    LLDP_SYS_CAPABILITY_INFO_S stSysCapability;      /* system Capabilities TLV */
    LLDP_PVID_INFO_S stPortVlanID;                 /* PortVlan ID TLV支持的VLAN ID，Port VLAN ID TLV信息 */
    LLDP_PORT_DESC_INFO_S stPortDesc;                 /* Port Description TLV */ 
    LLDP_PPVID_INFO_S stPpvid[LLDP_MAX_PPVID_TLV_NUM];/*Port VLAN ID TLV 支持多个vlanID目前不支持*/
    LLDP_LINK_AGG_INFO_S stLinkAgg;                   /* Link Aggregation TLV */
    LLDP_MAC_PHY_CFG_INFO_S stMacPhyCfg;            /*MAC/PHY Configuration/Status TLV*/ 
    LLDP_MAX_FRAME_SIZE_INFO_S stMaxFrameSize;        /*MaxFrameSize TLV*/
    LLDP_POWER_VIA_MDI_INFO_S stMdi;
    LLDP_VLAN_NAME_INFO_S stVlanName[LLDP_MAX_VLAN_NAME_TLV_NUM];
    LLDP_CHASSISID_INFO_S stChassisId;
    LLDP_LOCAL_AGENT_S  stPortAgent[LLDP_MAX_MACTYPE_SIZE];/*3个多播地址*/              
}LLDP_LOCAL_PORT_S;

#endif

/*Added by guo00178934, 添加系统统计Local存储结构体, 2011/11/8   问题单号:DTS2011110800968 */
/*系统统计信息*/
typedef struct tagLLDP_LOCAL_SYS_STAT_S
{
    ULONG  ulRemTablesLastChangeTime; /* Remote表最后一次修改时间 */
    ULONG  ulRemTablesInserts;        /* Remote表新增表项插入次数 */
    ULONG  ulRemTablesDeletes;        /* Remote表删除次数 */
    ULONG  ulRemTablesDrops;          /* Remote表丢弃节点个数 */
    ULONG  ulRemTablesAgeouts;        /* Remote表超时个数 */
    ULONG  ulRemTablesUpdates;        /* Remote表更新个数 */
}LLDP_LOCAL_SYS_STAT_S; 
/* End of Added by guo00178934, 2011/11/8   问题单号:DTS2011110800968 */


#ifdef  __cplusplus
}
#endif

#endif
