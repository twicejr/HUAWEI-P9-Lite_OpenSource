/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              lldp_api.h
*
*  Project Code: V2R3C06
*   Module Name: API
*  Date Created: 2011-09-27
*        Author: liangjicheng 00103192
*   Description: 用户API头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2011-09-27   liangjicheng 00103192   Create
*
*******************************************************************************/
#ifndef _LLDP_API_H_
#define _LLDP_API_H_

#ifdef  __cplusplus
extern "C"{
#endif

/*****全局配置信息*****/
typedef struct tagLLDP_GLOBAL_CFG_S
{
    ULONG  ulTxInterval;            /* LLDP报文发送间隔 */
    ULONG  ulTxHoldMultiplier;      /* TTL乘数  */
    ULONG  ulReinitDelay;           /* 初始化延时 */
    ULONG  ulFastTxPktNum;          /* FAST模式传输报文个数*/
    /*Begin of added by w00217009, Hert新需求,支持配置快速发送时间间隔msgFastTx, DTS2013011606002*/
    ULONG  ulMsgFastTx;             /* FAST模式报文发送时间间隔*/
} LLDP_GLOBAL_CFG_S; 

/******* Class ID TLV  *******/
#define LLDP_MAC_ADDR_LEN      6    /*physical地址的长度*/
#define LLDP_STR_LEN_256       256  /*256个字符个数*/
typedef struct tagLLDP_CHASSISID_INFO_S
{
    UCHAR  ucChassisIdSubtype; /* ChassisId类型，取值范围（1~7）
                                        chassisComponent(1),   
                                        interfaceAlias(2),     
                                        portComponent(3),      
                                        macAddress(4),         
                                        networkAddress(5),     
                                        interfaceName(6),      
                                        local(7)  */
    UCHAR  ucChassisIdLen;                  /* Chassis Id有效长度  */
    UCHAR  ucRes[2];                         /*填充字段，保证结构体4个字节对齐*/               
    CHAR   szChassisId[LLDP_STR_LEN_256];   /* ChassisId，取值范围（字符串1~255）  */
}LLDP_CHASSISID_INFO_S; 

/******* Management Address TLV  *******/
#define LLDP_STR_LEN_32  32     /*32个字符个数*/
typedef struct tagLLDP_MANAGEMENT_INFO_S
{
    ULONG  ulManAddrSubtype;    /*管理地址类型，取值：IPv4（1） */
    CHAR   szManAddr[LLDP_STR_LEN_32];       /* Management Address TLV中的管理地址*/
    ULONG  ulManAddrIfSubtype;  /*管理地址所在接口类型，默认unknown(1)
                                            unknown(1)
                                            ifIndex(2)
                                            systemPortNumber(3) */
    ULONG  ulManAddrIfId;       /*管理地址所在接口ID，默认0 */
}LLDP_MANAGEMENT_INFO_S;

/******* system name TLV  *******/
typedef struct tagLLDP_SYS_NAME_INFO_S
{
    CHAR   szSysName[LLDP_STR_LEN_256];       /*system name TLV , 本端系统名称，默认值"System" */
}LLDP_SYS_NAME_INFO_S; 

/******* system description TLV *******/
typedef struct tagLLDP_SYS_DESC_INFO_S
{
    CHAR   szSysDesc[LLDP_STR_LEN_256];       /* system description TLV,本端系统描述，默认值"System" */
}LLDP_SYS_DESC_INFO_S;

#define LLDP_SYS_CAP_BIT_LEN 16              /*本端系统支持的功能位，两字节的比特位*/
/* system Capabilities TLV */
typedef struct tagLLDP_SYS_CAPABILITY_INFO_S
{

    USHORT usSysCapSupported;     /* 本端系统支持的功能（BITS）*/
    USHORT usSysCapEnabled;       /* 本端系统开启的功能，同上 */    
}LLDP_SYS_CAPABILITY_INFO_S;

/*Management VID TLV*/
typedef struct tagLLDP_MANAGEMENT_VID_INFO_S
{
    USHORT usManagementVid;       /*本端Management VID信息*/
    UCHAR ucRes[2];                /*填充字段，保证结构体4个字节对齐*/  
} LLDP_MANAGEMENT_VID_INFO_S;


/*用于外部配置的本端系统信息，包括系统名称，系统描述*/
typedef struct tagLLDP_CFG_SYS_NAME_DESC_S
{
    LLDP_SYS_NAME_INFO_S stSysName;        /* 本端系统名称，默认值"System" */
    LLDP_SYS_DESC_INFO_S stSysDesc;        /* 本端系统描述，默认值"System" */
}LLDP_CFG_SYS_NAME_DESC_S;

/*用于外部查询，包括ChassisId，系统名称，系统描述，管理地址信息，本端系统能力*/
typedef struct tagLLDP_SYS_INFO_S
{
    LLDP_SYS_NAME_INFO_S stSysName;        /* 本端系统名称，默认值"System" */
    LLDP_SYS_DESC_INFO_S stSysDesc;        /* 本端系统描述，默认值"System" */
    LLDP_MANAGEMENT_INFO_S stManagement;  /*管理地址TLV信息*/
    LLDP_SYS_CAPABILITY_INFO_S stSysCapability;  /*system Capabilities TLV信息*/
    LLDP_MANAGEMENT_VID_INFO_S stManagementVid;  /*Management VID TLV*/
}LLDP_SYS_INFO_S;


/******* Port Description TLV  *******/
typedef struct tagLLDP_PORT_DESC_INFO_S
{
    CHAR   szPortDesc[LLDP_STR_LEN_256];     /* Port Description内容 */
}LLDP_PORT_DESC_INFO_S;

/* Port And Protocol VLAN ID TLV */
typedef struct tagLLDP_PPVID_INFO_S
{
    USHORT usPpvid;     /* PPVID内容 */
    UCHAR ucFlags;      /*标示字段*/
    UCHAR ucResv[1];    /*填充字段，保证结构体4个字节对齐*/  
}LLDP_PPVID_INFO_S;

/*Port ID TLV*/
typedef struct tagLLDP_PORTID_INFO_S
{
    UCHAR  ucPortIdSubtype;     /* PortId类型，当前仅支持
                                    LLDP_PORTID_MAC_ADDRESS(3)
                                    LLDP_PORTID_INTERFACE_NAME(5)
                                  */
    UCHAR ucResv[3];    /*填充字段，保证结构体4个字节对齐*/  
    CHAR   szPortId[LLDP_STR_LEN_256];   /* PortId，固定physical地址  */
}LLDP_PORTID_INFO_S;


/*Link Aggregation TLV*/
typedef struct tagLLDP_LINK_AGG_INFO_S
{
    UCHAR ucLinkAggCapStatus;      /* 链路聚合能力和状态
                                                （0bit位表示能力，1bit位表示状态） */
    UCHAR ucResv[3];                /*填充字段，保证结构体4个字节对齐*/  
    ULONG ulLinkAggPortID;         /* 链路聚合ID */
}LLDP_LINK_AGG_INFO_S; 

/***Power Via MDI TLV***/
typedef struct tagLLDP_POWER_VIA_MDI_INFO_S
{
    UCHAR ucMdiPowerSupport;         /* MDI Power Support */
    UCHAR ucPsePowerPair;            /* PSE Power Pair*/
    UCHAR ucPowerClass;              /* Power Class       */
    UCHAR ucResv[1];                 /*填充字段，保证结构体4个字节对齐*/  
}LLDP_POWER_VIA_MDI_INFO_S;

/*Port VLAN ID TLV*/
typedef struct tagLLDP_PVID_INFO_S
{
    USHORT usPvid;     /* PVID内容 */
    UCHAR ucResv[2];   /*填充字段，保证结构体4个字节对齐*/  
}LLDP_PVID_INFO_S; 


/***** MAC/PHY Configuration/Status TLV *****/
typedef struct tagLLDP_MAC_PHY_CFG_INFO_S
{
    UCHAR ucLinkAutoNegoCapStatus; /* 链路自协商能力和管理状态
                                    （0bit位表示能力，1bit位表示管理状态） */
    UCHAR ucResv[3];                 /*填充字段，保证结构体4个字节对齐*/  
    USHORT usLinkPmdAutoNegoCap;   /* 链路PMD自协商能力 */
    USHORT usLinkOperMauType;      /* 链路MAU操作类型 */
}LLDP_MAC_PHY_CFG_INFO_S; 


/* Maximum Frame Size TLV */
typedef struct tagLLDP_MAX_FRAME_SIZE_INFO_S
{
    USHORT usMaxFrameSize;        /* Maximum Frame Size TLV支持的Maximum Frame Size信息 */
    CHAR ucResv[2];                /*填充字段，保证结构体4个字节对齐*/  
}LLDP_MAX_FRAME_SIZE_INFO_S;

#define LLDP_MAX_VLAN_NAME_TLV_NUM 32  /*每个接口最多有32个VLAN NAME TLV*/
/*Vlan Name TLV信息*/
typedef struct tagLLDP_VLAN_NAME_INFO_S
{
    USHORT usVlanId;               /*Vlan ID*/
    UCHAR ucNameLen;               /*Vlan Name长度*/
    UCHAR ucRes;                   /*填充字段，保证结构体4个字节对齐*/
    UCHAR ucVlanName[32];          /*Vlan Name*/
} LLDP_VLAN_NAME_INFO_S;

typedef struct tagLLDP_CFG_PORT_INFO_S
{
    LLDP_PORTID_INFO_S  stPortId;      /* Port ID TLV */
    LLDP_PORT_DESC_INFO_S stPortDesc;  /* Port Description TLV */
}LLDP_CFG_PORT_INFO_S;

/*邻居节点查询的过滤条件*/
typedef struct tagLLDP_REM_FILTER_S
{
    ULONG  ulPortIfIndex;         /* Remote所在端口的编号*/
    ULONG  ulDestAddrGroup;       /* Remote所在组播组的编号， 
                                                    DestMac：Nearest bridge （1）
                                                    DestMac：Nearest non-TPMR bridge（2）
                                                    DestMac：Nearest Customer Bridge（3）
                                                    该过滤条件需要和下面的Remote编号一起使用*/
    ULONG  ulRemIndex;            /* Remote编号，取值范围（1~7FFFFFFF）*/
}LLDP_REM_FILTER_S;

/**邻居查询时，通过LLDP_RemTableGet()函数获取到邻居节点，在邻居表中的索引**/
typedef struct tagLLDP_REM_INDEX_S
{
    ULONG  ulPortPos;   /*游标当前所在接口数组中的索引*/
    ULONG  ulMacPos;    /*游标当前所在的组播地址(Agent)*/
    ULONG  ulRemPos;    /*游标当前所在Agent中邻居表的索引*/
}LLDP_REM_INDEX_S;

/***  邻居节点信息***/
#define LLDP_MAX_PPVID_TLV_NUM  16  /*每个接口最多有16个Port And Protocol VLAN ID TLV*/

/*外部邻居查询用的邻居节点*/
typedef struct tagLLDP_REM_INFO_S
{    
    ULONG  ulDestAddrIndex;       /* Remote所在组播组的编号，取值范围（1~3）
                                            DestMac：01:80:c2:00:00:0e（1）
                                            DestMac：01:80:c2:00:00:03（2）
                                            DestMac：01:80:c2:00:00:00（3）*/
    ULONG  ulRemIndex;            /* Remote编号，取值范围（1~7FFFFFFF）*/
    ULONG  ulRemTimeMark;         /* Remote上次变更到现在的时间（单位：秒） */
    ULONG  ulRemExpireTime;       /* Remote超时时间，取自TTL TLV（单位：秒） */
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
                                      10- Port and Protocol Vlan ID TLV
                                      11- Vlan Name TLV
                                      12- Management VID TLV*/    
    ULONG  ulPpvidNum;            /* Port and Protocol Vlan ID TLV 个数*/
    UCHAR ucVlanNameNum;/* Vlan Name TLV 个数*/
    UCHAR ucRes[3];
    LLDP_CHASSISID_INFO_S stRemChassisId; /* Remote ChassisId TLV*/     
    LLDP_PORTID_INFO_S  stRemPortId; /* Remote PortId TLV */ 
    LLDP_MANAGEMENT_INFO_S stRemManagement; /*管理地址TLV*/ 
    LLDP_SYS_NAME_INFO_S stRemSysName;        /* 本端系统名称，默认值"System" */
    LLDP_SYS_DESC_INFO_S stRemSysDesc;        /* 本端系统描述，默认值"System" */
    LLDP_SYS_CAPABILITY_INFO_S stRemSysCapability;  /*系统能力TLV*/
    LLDP_PORT_DESC_INFO_S stRemPortDesc;      /* Port Description TLV */
    LLDP_MAC_PHY_CFG_INFO_S stRemPhyCfgStatus;/* MAC/PHY Configuration/Status TLV */
    LLDP_PVID_INFO_S stRemPortVlanId;   /*Port Vlan Id TLV*/
    LLDP_MANAGEMENT_VID_INFO_S stRemManagementVid; /* Management VID TLV */
    LLDP_MAX_FRAME_SIZE_INFO_S stRemMaxFrameSize;   /*Max Frame Size TLV */
    LLDP_LINK_AGG_INFO_S stLinkAgg; /* Link Aggregation TLV */
    LLDP_VLAN_NAME_INFO_S stRemVlanName[LLDP_MAX_VLAN_NAME_TLV_NUM]; /* Vlan Name TLV */
    LLDP_PPVID_INFO_S stPpvid[LLDP_MAX_PPVID_TLV_NUM]; /* Port And Protocol VLAN ID TLV */

}LLDP_REM_INFO_S; 

/*系统统计信息*/
typedef struct tagLLDP_SYS_STAT_S
{
    ULONG  ulRemTablesLastChangeTime; /* Remote表最后一次修改时间 */
    ULONG  ulRemTablesInserts;        /* Remote表新增表项插入次数 */
    ULONG  ulRemTablesDeletes;        /* Remote表删除次数 */
    ULONG  ulRemTablesDrops;          /* Remote表丢弃节点个数 */
    ULONG  ulRemTablesAgeouts;        /* Remote表超时个数 */
    ULONG  ulRemTablesUpdates;        /* Remote表更新个数 */
}LLDP_SYS_STAT_S; 

/*接口每个Agent(对应于一个组播地址)上的统计信息*/
typedef struct tagLLDP_PORT_STAT_S
{
    ULONG  ulRxFramesTotal;             /* 收到的LLDP 帧总数 */
    ULONG  ulRxDiscardedTotal;          /* 丢弃的LLDP 帧总数 */
    ULONG  ulRxErrorsTotal;             /* 收到的错误LLDP 帧总数 */
    ULONG  ulRxTLVsDiscardedTotal;      /* 丢弃的LLDP TLV 帧总数 */
    ULONG  ulRxTLVsUnrecognizedTotal;   /* 不可识别的LLDP TLV 帧总数 */
    ULONG  ulTxFramesTotal;             /* 发送的LLDP 帧总数 */
    ULONG  ulRxAgeoutsTotal;            /* 老化的LLDP 邻居信息总数 */
}LLDP_PORT_STAT_S; 


/*邻居节点查询的过滤条件*/
/*Remote 所在组播组的编号，共3种组播地址，默认为Nearest bridg(1)*/
#define LLDP_NEAREST_BRIDGE             1
#define LLDP_NEAREST_NON_TPMR_BRIDGE    2
#define LLDP_NEAREST_CUSTOMER_BRIDGE    3

/*邻居查询过滤条件Remote编号，取值范围（1~7FFFFFFF）*/
#define LLDP_REMINDEX_MIN    1
#define LLDP_REMINDEX_MAX    0x7FFFFFFF


/*LLDP CBB错误码*/
#define LLDP_OK                              VOS_OK
#define LLDP_ERR                             VOS_ERR
#define LLDP_ERR_NO_SUCH_FUNC                2       /*无该函数调用*/
#define LLDP_ERR_INVALID_PARA                3       /*API参数无效或非法*/
#define LLDP_ERR_PORT_NUM_ZERO               4       /*本地接口数量为0*/
#define LLDP_ERR_PORT_NOT_EXIST              5       /*PORT不存在，或该PORT未使能LLDP*/
#define LLDP_ERR_INVALID_IF_INDEX            6       /*接口索引无效*/
#define LLDP_ERR_MALLOC_FAIL                 7       /*内存申请失败*/
#define LLDP_ERR_TABLE_END                   8       /*表项为空*/
#define LLDP_ERR_NOSPACEFORTLV               9       /*封装TLV的空间不够*/
#define LLDP_ERR_PORT_MODE_REPEATED          10      /*重复设置接口模式*/
#define LLDP_ERR_CHASSISID_SUBTYPE_INVALID   11      /*配置ChassisIdSubType无效*/
#define LLDP_ERR_CHASSISID_INVALID           12      /*配置ChassisId无效(长度/值)*/
#define LLDP_ERR_MAN_ADDR_SUBTYPE_INVALID    13      /*配置ManAddrSubtype无效*/
#define LLDP_ERR_MAN_ADDR_INVALID            14      /*配置ManAddr无效*/
#define LLDP_ERR_MAN_ADDR_IF_SUBTYPE_INVALID 15      /*配置ManAddrIfSubtype无效*/
#define LLDP_ERR_MAN_ADDR_IF_ID_INVALID      16      /*配置ManAddrIfId无效*/
#define LLDP_ERR_LOCAL_SYS_NAME_INVALID      17      /*配置LocSysName无效*/
#define LLDP_ERR_LOCAL_SYS_DESC_INVALID      18      /*配置LocSysDesc无效*/
#define LLDP_ERR_LLDP_NOT_INIT               19      /*LLDP未初始化*/
#define LLDP_ERR_IF_NOT_SUPPORT              20      /*非以太接口,LLDP不支持*/
#define LLDP_ERR_PPI_NOT_CONFIG              21      /*LLDP PPI未注册*/
#define LLDP_ERR_PPI_UPDATE_FUN_NOT_CFG      22      /*接口模式更新PPI未注册*/
#define LLDP_ERR_INVALID_PARA_VALUE          23      /*API参数值无效*/
#define LLDP_ERR_PPVID_IS_FULL               24      /*PPVID达到最大个数*/
#define LLDP_ERR_PPVID_NOT_EXIST             25      /*PPVID不存在*/
#define LLDP_ERR_PORT_DESC_INVALID           26      /*配置Port Desc参数无效*/
#define LLDP_ERR_VLAN_NAME_NUM_LARGE         27      /*配置VLAN NAME TLV个数太大*/
#define LLDP_ERR_VLAN_NAME_EXIST             28      /*VLAN NAME TLV已存在*/
#define LLDP_ERR_VLAN_NAME_NOEXIST           29      /*VLAN NAME TLV不存在*/
#define LLDP_ERR_VLAN_NAME_LENGTH            30      /*VLAN NAME 长度错误*/
#define LLDP_ERR_MANAGE_VID_TPYE             31      /*Management Vid 类型错误*/
#define LLDP_ERR_SYSCAP_INVALID              32      /*SysCap错误*/
#define LLDP_ERR_PORTID_INVALID              33      /*PortID错误*/
#define LLDP_ERR_PORTDESC_LEN                34      /*Port Desc长度错误*/
#define LLDP_ERR_PORTID_LEN                  35      /*Port ID长度错误*/
#define LLDP_ERR_MACPHY_INVALID              36      /*MacPhy tlv错误*/
#define LLDP_ERR_LINKAGG_INVALID             37      /*LinkAgg tlv错误*/
#define LLDP_ERR_VLAN_NAME_DUPLATE           38      /*VLAN NAME TLV重复存在*/
#define LLDP_ERR_OPERATE_INVALID             39      /*传入操作命令字取值不合法*/
#define LLDP_ERR_PVID_INVALID                40      /*删除的PortVlanId值不存在*/
#define LLDP_ERR_DELETE_PVID_IS_ZERO         41      /*删除的PortVlanId值不能为0*/
#define LLDP_ERR_MANAGEVID_NOEXIST           42      /*删除MANAGEVID不存在 */
#define LLDP_ERR_LINKAGG_NOEXIST             43      /*删除LinkAgg tlv不存在*/
#define LLDP_ERR_MANAGEMENT_NOEXIST          44      /*删除MANAGEMENT不存在 */
#define LLDP_ERR_GETEXTTLV_FUN_NOT_CFG       45      /*获取产品自定义TLV钩子函数未注册*/
#define LLDP_ERR_INPUTHOOK_FUN_NOT_CFG       45      /*上送LLDP报文钩子函数未注册*/


/*判断接口索引是否为0，以判断查询出的接口是否存在*/
#define LLDP_VALID_IF_INDEX(ulIfIndex)  \
  (ulIfIndex) != (0)

/*上报LLDP告警信息子类型*/
#define LLDP_WARNING_INSERT    1    /*邻居节点插入*/
#define LLDP_WARNING_UPDATE    2    /*邻居节点更新*/
#define LLDP_WARNING_DELETE    3    /*邻居节点删除*/
#define LLDP_WARNING_DROP      4    /*邻居表达到规格最大值，丢弃收到的新邻居的报文*/
#define LLDP_WARNING_AGEOUT    5    /*邻居节点老化删除*/

/*接口上报命令字*/
#define LLDP_IF_CMD_CREATE        1    /*接口创建*/
#define LLDP_IF_CMD_DEL           2    /*接口删除*/
#define LLDP_IF_CMD_UP            3    /*接口启动*/ 
#define LLDP_IF_CMD_DOWN          4    /*接口关闭*/ 
#define LLDP_IF_CMD_MTU           5    /*上报MTU变化*/
#define LLDP_IF_CMD_MAC           6    /*上报physical地址更新*/


/*接口Agent工作模式*/
#define LLDP_PORT_MODE_DISABLE     0    /*既不能发送LLDP报文，也不能接收报文*/
#define LLDP_PORT_MODE_TX          1    /*只发送送报文*/
#define LLDP_PORT_MODE_RX          2    /*只能接收报文*/
#define LLDP_PORT_MODE_TXRX        3    /*既能发送LLDP报文，又能接收报文*/

/*配置/删除LLDP接口Port Desc TLV信息操作字，1--添加；0--删除*/
#define LLDP_CREATE            1
#define LLDP_DELETE            0

/*端口物理状态UP/Down,对应于IF_STATUS_UP/IF_STATUS_DOWN,DTS2013060608306*/
#define LLDP_PORT_STATUS_UP    1
#define LLDP_PORT_STATUS_DOWN  2

/*LLDP上报的告警信息*/
typedef struct tagLLDP_REMOTE_TABLE_WARNING_S
{
    ULONG  ulWarningType;         /* 告警子类型：
                                      LLDP_WARNING_INSERT    1
                                      LLDP_WARNING_UPDATE    2
                                      LLDP_WARNING_DELETE    3
                                      LLDP_WARNING_DROP      4
                                      LLDP_WARNING_AGEOUT    5*/
    ULONG  ulPortIfIndex;         /* Remote所在端口的编号*/
    ULONG  ulDestAddrIndex;       /* Remote所在组播组的编号
                                      DestMac：01:80:c2:00:00:0e（1）
                                      DestMac：01:80:c2:00:00:03（2）
                                      DestMac：01:80:c2:00:00:00（3）*/
    ULONG  ulRemIndex;            /* Remote编号，取值范围（1~7FFFFFFF）*/
    LLDP_REM_INFO_S *pstRemoteInfo; /* 扩充 邻居的完整信息  由各个产品自行获取需要的信息   
                                    这个结构比较大，有2608字节，采用指针，如果为NULL，表示内存分配已经失败*/
}LLDP_REMOTE_TABLE_WARNING_S; 

/* 目前支持三个多播地址 */
#define LLDP_MAX_MACTYPE_SIZE  3

/*外部查询和获取LLDP接口信息*/
typedef struct tagLLDP_PORT_INFO_S
{
    /*Added by guo00178934, 获取3个Agent的接口模式, 2011/11/4   问题单号:DTS2011102004029 */
    ULONG  ulPortMode[LLDP_MAX_MACTYPE_SIZE];   /* LLDP接口模式， Tx、Rx、TxRx、Disable */
    /* End of Added by guo00178934, 2011/11/4   问题单号:DTS2011102004029 */

    USHORT usPktVLanId; /*报文头中Vlan Tag的ID, 不是Port Vlan ID TLV信息.*/
    USHORT usPktVLanPri; /*报文头中Vlan Tag的优先级, 不是Port Vlan ID TLV信息.*/
        
    LLDP_PORTID_INFO_S  stPortId;   /*Port ID TLV*/
    LLDP_PORT_DESC_INFO_S stPortDesc;   /* Port Description内容 */
    LLDP_PVID_INFO_S stPortVlanId;  /*Port VLAN ID*/
    LLDP_MAC_PHY_CFG_INFO_S stMacPhyCfg;    /*链路自协商能力*/
    LLDP_MAX_FRAME_SIZE_INFO_S stMaxFrameSize;  /*MTU*/
    LLDP_LINK_AGG_INFO_S stLinkAgg;     /*Link Aggregation */
    LLDP_VLAN_NAME_INFO_S stVlanName[LLDP_MAX_VLAN_NAME_TLV_NUM];  /*LLDP Vlan Name信息*/
    LLDP_CHASSISID_INFO_S stChassisId;
}LLDP_PORT_INFO_S;

/* LLDP Debug调试开关标志*/
#define LLDP_DEBUG_TX_PKT  0x01 /* 调试bit开关－报文发送*/
#define LLDP_DEBUG_RX_PKT  0x02 /* 调试bit开关－报文接收*/
#define LLDP_DEBUG_TX_FSM  0x04 /* 调试bit开关－发送状态机*/
#define LLDP_DEBUG_RX_FSM  0x08 /* 调试bit开关－接收状态机*/
#define LLDP_DEBUG_TR_FSM  0x10 /* 调试bit开关－发送timer状态机*/
#define LLDP_DEBUG_ADD_REM 0x20 /* 调试bit开关－邻居增加*/
#define LLDP_DEBUG_UPD_REM 0x40 /* 调试bit开关－邻居更新*/
#define LLDP_DEBUG_DEL_REM 0x80 /* 调试bit开关－邻居删除*/
#define LLDP_DEBUG_RX_ALL_PKT  0x100 /* 调试bit开关－报文接收打印所有报文包括非lldp报文*/
#define LLDP_DEBUG_ALL     0xffff /* 调试bit开关－全部打开*/

/*LLDP  PPI消息内容结构体*/
typedef struct tagLLDP_PPI_UPDATE_S
{
    ULONG ulIfIndex;         /* 接口索引 */
    ULONG ulDestAddrGroup;  /*目的组播组的编号
                                Nearest bridge              1
                                Nearest non-TPMR bridge     2
                                Nearest Customer Bridge     3*/
}LLDP_PPI_UPDATE_S;

/*PPI注册函数，由TRAN注册，VISP在适当的时候调用该函数将配置信息通知TRAN*/
typedef struct tabLLDP_PPI_HOOK
{
    /*LLDP模式更新*/
    ULONG (*pfLLDP_PPI_Mode_Update)(ULONG ulOperType, LLDP_PPI_UPDATE_S *pstLldpUpdateMsg);
}LLDP_PPI_HOOK_S;

/* 产品回调，获取自定义TLV */
typedef struct tagLLDP_GETEXTTLV
{
	ULONG  ulIfIndex;      /*接口索引*/
	ULONG  ulDestAddrGroup;/*[1,3]
                           Nearest bridge 1
                           Nearest non-TPMR bridge 2
                           Nearest Customer Bridge 3
                           
                           默认为：1 Nearest Bridge
                           */
	ULONG  ulRemTlvLen;    /*扩展TLV可以封装的最大长度*/
	ULONG  ulExtTlvLen;    /*输出，返回的扩展TLV的长度，如果为0则不封装自定义TLV*/
	CHAR * pExtTlv;        /*输出，返回的扩展TLV*/
}LLDP_GETEXTTLV_S;

/* 产品注册函数，获取自定义TLV */
typedef ULONG (*LLDP_GETEXTTLV_HOOK_FUNC)(LLDP_GETEXTTLV_S *pstData);

/* 将收到的LLDP报文上送给产品 */
typedef struct tagLLDP_INPUT
{
	ULONG  ulIfIndex;      /*接口索引*/
	ULONG  ulDestAddrGroup;/*[1,3]
                           Nearest bridge 1
                           Nearest non-TPMR bridge 2
                           Nearest Customer Bridge 3
                           
                           默认为：1 Nearest Bridge
                           */
    ULONG  ulPktLen;       /* 收到的LLDP报文长度 */
	CHAR * pRcvPacket;     /*收到的报文*/
}LLDP_INPUT_S;

/* LLDP收包钩子原型 */
typedef ULONG (*LLDP_INPUT_HOOK_FUNC)(LLDP_INPUT_S *pstData);

/*******************************************************************************
*    Func Name: LLDP_CfgTxInterval
* Date Created: 2011-09-27
*       Author: limin00188004
*  Description:  配置LLDP报文发送间隔接口
*        Input: ULONG ulTxInterval: LLDP报文发送间隔
*       Output: 
*       Return: LLDP_OK, LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-27   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_CfgTxInterval(ULONG ulTxInterval);

/*******************************************************************************
*    Func Name: LLDP_CfgMsgFastTx
* Date Created: 2013-01-15
*       Author: wuxiaowu00217009
*  Description:  配置LLDP在FAST模式下报文发送时间间隔 ,DTS2013011606002
*        Input: ULONG ulMsgFastTx: LLDP在FAST模式下报文发送间隔
*       Output: 
*       Return: LLDP_OK, LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-01-15   wuxiaowu00217009           Create
*
*******************************************************************************/
ULONG LLDP_CfgMsgFastTx(ULONG ulMsgFastTx);

/*******************************************************************************
*    Func Name: LLDP_CfgTxHoldMultiplier
* Date Created: 2011-09-27
*       Author: limin00188004
*  Description:  配置TTL乘数
*        Input: ULONG ulTxHoldMultiplier: TTL乘数，用来计算TTL.
*                        TTL(Time to live TLV) = min(65535, (LLDP报文发送间隔 * TTL乘数))
*       Output:  
*       Return:  LLDP_OK, LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-27   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_CfgTxHoldMultiplier(ULONG ulTxHoldMultiplier);

/*******************************************************************************
*    Func Name: LLDP_CfgReinitDelay
* Date Created: 2011-09-27
*       Author: limin00188004
*  Description:  配置重初始化延时接口
*        Input: ULONG ulReinitDelay: 重始化延时时间
*       Output: 
*       Return: LLDP_OK, LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-27   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_CfgReinitDelay(ULONG ulReinitDelay);

/*******************************************************************************
*    Func Name: LLDP_CfgFastTxPacketNum
* Date Created: 2011-09-27
*       Author: limin00188004
*  Description: 配置FAST模式传输报文个数
*        Input: ULONG ulPacketNum: FAST模式传输报文个数
*       Output: 
*       Return: LLDP_OK, LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-27   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_CfgFastTxPacketNum(ULONG ulPacketNum);

/*******************************************************************************
*    Func Name: LLDP_CfgPortMode
* Date Created: 2011-09-28
*       Author: limin00188004
*  Description:  配置LLDP接口模式，支持Tx、Rx、TxRx、Disable
*        Input: ULONG ulIfIndex: 使能LLDP的接口索引
*               ULONG ulPortMode:接口模式（取值范围：1~4）
*                                               LLDP_ADMIN_STATUS_TX               1
*                                               LLDP_ADMIN_STATUS_RX               2
*                                               LLDP_ADMIN_STATUS_TXRX           3
*                                               LLDP_ADMIN_STATUS_DISABLE      4
*               ULONG ulDestAddrGroup: 目的组播组的编号，默认为Nearest bridg(1)
*                                               Nearest bridge                           1
*                                               Nearest non-TPMR bridge          2
*                                               Nearest Customer Bridge           3
*       Output: 
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_IF_NOT_SUPPORT,LLDP_ERR_INVALID_PARA,
*               LLDP_ERR_PORT_NOT_EXIST,LLDP_ERR_PORT_MODE_REPEATED
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-28   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_CfgPortMode(ULONG ulIfIndex, ULONG ulPortMode, ULONG ulDestAddrGroup);

/*******************************************************************************
*    Func Name: LLDP_CfgIfVlan
* Date Created: 2011-10-20
*       Author: zhangliangzhi00187023
*  Description: 配置LLDP接口Vlan ID.
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulVlanId: Vlan ID（取值范围：0～4094，默认值：0）
*       Output: 
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_IF_NOT_SUPPORT,LLDP_ERR_INVALID_PARA,
*           LLDP_ERR_PORT_NOT_EXIST
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-20   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgIfVlan(ULONG ulIfIndex, USHORT usVlanId, USHORT usPri);

/*******************************************************************************
*    Func Name: LLDP_DisableAllPort
* Date Created: 2011-10-21
*       Author: zhangliangzhi00187023
*  Description: 将系统中所有开启LLDP接口的模式改为DISABLE
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-21   zhangliangzhi00187023   Create
*
*******************************************************************************/
VOID LLDP_DisableAllPort(VOID);

/*******************************************************************************
*    Func Name: LLDP_CfgSysNameAndDescInfo
* Date Created: 2012-10-17
*       Author: zhangliangzhi00187023
*  Description: 配置系统名称和系统描述
*        Input: LLDP_CFG_SYS_NAME_DESC_S *pstSysNameDesc:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-10-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgSysNameAndDescInfo(LLDP_CFG_SYS_NAME_DESC_S *pstSysNameDesc);


/*******************************************************************************
*    Func Name: LLDP_GetGlobalConfig
* Date Created: 2011-09-30
*       Author: limin00188004
*  Description: 获取LLDP全局配置信息。
*        Input: 
*       Output: LLDP_GLOBAL_CFG_S *pstGlobalConfig: LLDP全局配置信息
*               包括LLDP报文发送间隔，TTL乘数，初始化延时，FAST模式传输报文个数。
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-30   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_GetGlobalConfig(LLDP_GLOBAL_CFG_S *pstGlobalConfig);

/*******************************************************************************
*    Func Name: LLDP_ShowGlobalConfig
* Date Created: 2011-10-09
*       Author: guo00178934
*  Description: 显示LLDP全局配置信息。
*               包括LLDP报文发送间隔，TTL乘数，初始化延时，FAST模式传输报文个数。
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-09   guo00178934             Create
*
*******************************************************************************/
VOID LLDP_ShowGlobalConfig(VOID);

/*******************************************************************************
*    Func Name: LLDP_GetLocalInfo
* Date Created: 2011-10-08
*       Author: guo00178934
*  Description: 获取LLDP本端信息。
*        Input: 
*       Output: LLDP_SYS_INFO_S *pstLocal: LLDP本端信息。
*               包括ChassisId，系统名称，系统描述，管理地址信息，本端系统能力。
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-08   guo00178934             Create
*
*******************************************************************************/
ULONG LLDP_GetLocalInfo(LLDP_SYS_INFO_S *pstLocal);

/*******************************************************************************
*    Func Name: LLDP_ShowLocalInfo
* Date Created: 2011-10-08
*       Author: guo00178934
*  Description: 显示本端信息。包括ChassisId，系统名称，系统描述，管理信息，系统能力。
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-08   guo00178934             Create
*
*******************************************************************************/
VOID LLDP_ShowLocalInfo(VOID);

/*******************************************************************************
*    Func Name: LLDP_GetPortInfo
* Date Created: 2011-09-30
*       Author: guo00178934
*  Description: 获取LLDP接口信息
*        Input: ULONG ulIfIndex: LLDP的接口索引
*       Output: LLDP_PORT_INFO_S *pstPortInfo: LLDP接口信息
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA,
*               LLDP_ERR_IF_NOT_SUPPORT,LLDP_ERR_PORT_NOT_EXIST
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-30   guo00178934             Create
*
*******************************************************************************/
ULONG LLDP_GetPortInfo(ULONG ulIfIndex, LLDP_PORT_INFO_S *pstPortInfo);

/*******************************************************************************
*    Func Name: LLDP_ShowPortInfo
* Date Created: 2011-10-31
*       Author: limin00188004
*  Description: 显示所有开启LLDP的接口信息。
*               包括接口编号，接口模式，接口ID，Port Desc TLV，PPVID TLV等。
*        Input: CHAR *pIfName: 指定的接口名称，输入为""则代表显示所有开启LLDP的接口信息
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-31   limin00188004           Create
*
*******************************************************************************/
VOID LLDP_ShowPortInfo(CHAR *pIfName);

/*******************************************************************************
*    Func Name: LLDP_RemTableOpen
* Date Created: 2011-09-29
*       Author: limin00188004
*  Description:  查询LLDP邻居信息的Open函数
*        Input:   LLDP_REM_FILTER_S *pstFilter:  过滤条件（当前端口编号必须指定）。
*               LLDP_REM_FILTER_S中的ulDestAddrGroup和ulRemIndex字段取值如下:
*               ULONG ulDestAddrGroup: Remote所在组播组的编号；为0，则该字段查询时无效。
*                                  DestMac：Nearest bridge （1）
*                                  DestMac：Nearest non-TPMR bridge（2）
*                                  DestMac：Nearest Customer Bridge（3）
*               ULONG ulRemIndex:Remote编号，取值范围（1~7FFFFFFF）；为0，则该字段查询时无效。
*       Output:  ULONG *pHandle: 查询句柄
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA,LLDP_ERR_PORT_NUM_ZERO,
*               LLDP_ERR_MALLOC_FAIL
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-29   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_RemTableOpen(UINTPTR *pulHandle, LLDP_REM_FILTER_S *pstFilter);

/*******************************************************************************
*    Func Name: LLDP_RemTableGet
* Date Created: 2011-09-29
*       Author: limin00188004
*  Description: 查询LLDP邻居信息的Get函数
*        Input: ULONG ulHandle:  查询句柄
*       Output: LLDP_REM_INFO_S * pstRemInfo: 查询到的LLDP邻居节点信息
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-29   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_RemTableGet(UINTPTR ulHandle, LLDP_REM_INFO_S * pstRemInfo);

/*******************************************************************************
*    Func Name: LLDP_RemTableClose
* Date Created: 2011-09-30
*       Author: limin00188004
*  Description: 查询LLDP邻居信息的Close函数
*        Input: ULONG ulHandle: 查询句柄
*       Output: 
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-30   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_RemTableClose(UINTPTR ulHandle);

/*******************************************************************************
*    Func Name: LLDP_ShowRemInfo
* Date Created: 2011-10-21
*       Author: liangjicheng 00103192
*  Description: 
*        Input: CHAR *pIfName: 指定的接口名称
*               ULONG ulDestAddrGroup: Remote所在组播组的编号;为0，则该字段查询时无效。
*                                  DestMac：Nearest bridge （1）
*                                  DestMac：Nearest non-TPMR bridge（2）
*                                  DestMac：Nearest Customer Bridge（3）
*               ULONG ulRemIndex:Remote编号，取值范围（1~7FFFFFFF）；为0，则该字段查询时无效。
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-21   liangjicheng 00103192   Create
*
*******************************************************************************/
VOID LLDP_ShowRemInfo(CHAR *pIfName, ULONG ulDestAddrGroup, ULONG ulRemIndex);

/*******************************************************************************
*    Func Name: LLDP_GetSysStat
* Date Created: 2011-10-24
*       Author: limin00188004
*  Description: 获取LLDP系统统计信息
*        Input: 
*       Output: LLDP_SYS_STAT_S *pstSysStat: 全系统统计信息
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-24   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_GetSysStat(LLDP_SYS_STAT_S *pstSysStat);

/*******************************************************************************
*    Func Name: LLDP_ClearSysStat
* Date Created: 2011-10-24
*       Author: limin00188004
*  Description: 清除LLDP系统统计信息
*        Input: VOID
*       Output: 
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-24   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_ClearSysStat(VOID);

/*******************************************************************************
*    Func Name: LLDP_ShowSysStat
* Date Created: 2011-10-24
*       Author: limin00188004
*  Description: 显示LLDP系统统计信息
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-24   limin00188004           Create
*
*******************************************************************************/
VOID LLDP_ShowSysStat(VOID);

/*******************************************************************************
*    Func Name: LLDP_GetPortStat
* Date Created: 2011-10-19
*       Author: guo00178934
*  Description: 获取LLDP接口统计信息（必须指定接口编号和组播组号）.
*        Input: ULONG ulIfIndex: LLDP的接口索引
*               ULONG ulDestAddrGroup: 目的组播组的编号.
*                    Nearest bridge              1
*                    Nearest non-TPMR bridge     2
*                    Nearest Customer Bridge     3
*       Output: LLDP_PORT_STAT_S *pstPortStat: 接口统计信息
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA,LLDP_ERR_IF_NOT_SUPPORT,
*               LLDP_ERR_PORT_NOT_EXIST
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-19   limin00188004             Create
*
*******************************************************************************/
ULONG LLDP_GetPortStat(ULONG ulIfIndex, ULONG ulDestAddrGroup, LLDP_PORT_STAT_S *pstPortStat);

/*******************************************************************************
*    Func Name: LLDP_ClearPortStat
* Date Created: 2011-10-19
*       Author: guo00178934
*  Description: 清除指定接口指定组播组的LLDP统计信息。
*        Input: ULONG ulIfIndex:使能LLDP的接口索引（为0则清除所有使能LLDP的接口的统计信息）
*               ULONG ulDestAddrGroup: 目的组播组的编号。为0，则清除该接口上的所有Agent上的统计信息。
*                    Nearest bridge              1
*                    Nearest non-TPMR bridge     2
*                    Nearest Customer Bridge     3
*       Output: 
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA_VALUE,
*               LLDP_ERR_PORT_NOT_EXIST,LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-10   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_ClearPortStat(ULONG ulIfIndex, ULONG ulDestAddrGroup);

/*******************************************************************************
*    Func Name: LLDP_ShowPortStat
* Date Created: 2011-10-19
*       Author: guo00178934
*  Description: 显示指定接口所有组播组的LLDP统计信息
*        Input: CHAR *pIfName: 指定的接口名称
*               ULONG ulDestAddrGroup:目的组播组的编号。为0，则显示该接口上所有Agent的统计信息。
*                    Nearest bridge              1
*                    Nearest non-TPMR bridge     2
*                    Nearest Customer Bridge     3
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-10   limin00188004           Create
*
*******************************************************************************/
VOID LLDP_ShowPortStat(CHAR *pIfName, ULONG ulDestAddrGroup);

/*******************************************************************************
*    Func Name: LLDP_SetDebugSwitch
* Date Created: 2011-10-30
*       Author: guo00178934
*  Description: 设置Debug开关和过滤条件
*        Input: ULONG ulDebug: LLDP Debug开关值。
*               ULONG ulIfIndex: 指定接口索引，0代表所有的接口，非零指定某个接口。
*               ULONG ulDestAddrGroup: 指定组播类型，0代表三类组播地址，非0代表指定某类组播地址。
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-30   guo00178934             Create
*
*******************************************************************************/
ULONG LLDP_SetDebugSwitch (ULONG ulDebug, ULONG ulIfIndex, ULONG ulDestAddrGroup);

/*******************************************************************************
*    Func Name: LLDP_GetDebugSwitch
* Date Created: 2011-10-30
*       Author: guo00178934
*  Description: 获取Debug开关和过滤条件
*        Input: ULONG *pulDebug: 获取的LLDP Debug开关值。
*               ULONG *pulIfIndex: 获取当前打开debug开关的接口索引值。
*               ULONG *pulDestAddrGroup: 获取当前打开debug开关的多播类型。
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-30   guo00178934             Create
*
*******************************************************************************/
ULONG LLDP_GetDebugSwitch (ULONG *pulDebug, ULONG *pulIfIndex, ULONG *pulDestAddrGroup);

/*******************************************************************************
*    Func Name: LLDP_ShowDebugSwitch
* Date Created: 2011-10-30
*       Author: guo00178934
*  Description: 显示全局LLDP Debug开关。
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-27   guo00178934             Create
*
*******************************************************************************/
VOID LLDP_ShowDebugSwitch ();

/*******************************************************************************
*    Func Name: LLDP_PPI_HookRegister
* Date Created: 2011-09-28
*       Author: guo00178934
*  Description: PPI注册函数，由TRAN注册，VISP在适当的时候调用该函数将配置信息通知TRAN.
*        Input: LLDP_PPI_HOOK_S *pstHookFun:
*                typedef struct tabLLDP_PPI_HOOK
*                {
*                    ULONG (*pfLLDP_PPI_Mode_Update)(ULONG ulOperType, LLDP_PPI_UPDATE_S *pstLldpUpdateMsg);
*                }LLDP_PPI_HOOK_S;
*
*                   ulOperType    操作类型：
*                   PPI_LLDP_PORT_MODE_DISABLE     0
*                   PPI_LLDP_PORT_MODE_TX          1
*                   PPI_LLDP_PORT_MODE_RX          2
*                   PPI_LLDP_PORT_MODE_TXRX        3
*
*                typedef struct tagLldpPpiUpdate
*                {
*                    ULONG ulIfIndex;      
*                    ULONG ulDestAddrGroup 
*                }LLDP_PPI_UPDATE_S;
*                    ulIfIndex: 接口索引
*                    ulDestAddrGroup:目的组播组的编号
*                    Nearest bridge              1
*                    Nearest non-TPMR bridge     2
*                    Nearest Customer Bridge     3
*       Output: 
*       Return: LLDP_OK,LLDP_ERR_PPI_UPDATE_FUN_NOT_CFG
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-28   guo00178934             Create
*
*******************************************************************************/
ULONG LLDP_PPI_HookRegister(LLDP_PPI_HOOK_S *pstHookFun);

/*LLDP  PPI消息下发钩子函数的宏定义*/
#define g_pfLLDP_PPI_Mode_Update g_stLldpHookRegister.pfLLDP_PPI_Mode_Update


ULONG LLDP_CfgPortMFS(ULONG ulIfIndex, USHORT usMaxFrameSize);


ULONG LLDP_CfgSysCapTlv(LLDP_SYS_CAPABILITY_INFO_S *pstSysCap);


ULONG LLDP_CfgManageVidTlv(ULONG ulOperate, LLDP_MANAGEMENT_VID_INFO_S *pstMngVid);


ULONG LLDP_CfgPortInfo(ULONG ulIfIndex, LLDP_CFG_PORT_INFO_S *pstPortInfo);


ULONG LLDP_CfgPortVlanIdTlv(ULONG ulOperate,ULONG ulIfIndex, LLDP_PVID_INFO_S 
*pstPortVlanId);


ULONG LLDP_CfgMacPhyCfgTlv(ULONG ulIfIndex,LLDP_MAC_PHY_CFG_INFO_S 
*pstMacPhyCfg);



ULONG LLDP_CfgLinkAggregationTlv( ULONG ulOperate,ULONG ulIfIndex, LLDP_LINK_AGG_INFO_S 
*pstLinkAgg);


ULONG LLDP_CfgVlanNameTlv(ULONG ulOperate,ULONG ulIfIndex, ULONG ulNumber, LLDP_VLAN_NAME_INFO_S 
stVlanName[]);


/*******************************************************************************
*    Func Name: LLDP_CfgChassisIDTlv
* Date Created: 2012-10-17
*       Author: zhangliangzhi00187023
*  Description: 配置chassis id 
*        Input: ULONG ulIfIndex:
*               LLDP_CHASSISID_INFO_S *pstChassisId:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-10-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgChassisIDTlv(ULONG ulIfIndex,LLDP_CHASSISID_INFO_S *pstChassisId);


/*******************************************************************************
*    Func Name: LLDP_CfgManagementTlv
* Date Created: 2012-10-17
*       Author: zhangliangzhi00187023
*  Description: 配置管理地址
*        Input: ULONG ulOperate:
*               LLDP_MANAGEMENT_INFO_S *pstManagement:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-10-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgManagementTlv(ULONG ulOperate, LLDP_MANAGEMENT_INFO_S 
*pstManagement);

/*******************************************************************************
*    Func Name: LLDP_AddPortDynamic
* Date Created: 2013-06-07
*       Author: wuxiaowu00217009
*  Description: 
*        Input: ULONG ulIfIndex
*       Output: 
*       Return: ULONG ulRet
*      Caution: 只有预配置为由产品添加LLDP端口时才执行端口添加,DTS2013060608306
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-07   wuxiaowu00217009   Create
*
*******************************************************************************/
ULONG LLDP_AddPortDynamic(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: LLDP_DelPortDynamic
* Date Created: 2013-06-07
*       Author: wuxiaowu00217009
*  Description: 
*        Input: ULONG ulIfIndex
*       Output: 
*       Return: ULONG ulRet
*      Caution: 只有预配置为由产品添加LLDP端口时才执行端口删除,DTS2013060608306
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-06-07   wuxiaowu00217009   Create
*
*******************************************************************************/
ULONG LLDP_DelPortDynamic(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: LLDP_RegFuncGetExtendTlvHook
*      Purpose: 注册获取产品自定义TLV的钩子，每次发送LLDP PDU的时候调用
*  Description: 注册获取产品自定义TLV的钩子，每次发送LLDP PDU的时候调用
*        Input: LLDP_GETEXTTLV_HOOK_FUNC pfFuncHook: 产品注册的钩子函数
*       InOut: 
*       Output: 
*       Return: 
*      Caution: pExtTlvBuff内存由产品管理，VISP通过钩子获取到之后copy到报文中。
*               如果ulExtTlvLen超过可以封装的最大长度，则自定义TLV将被丢弃
*               不封装到LLDP PDU中。
*
*       Since: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-06   l00213099               Create
*
*******************************************************************************/
ULONG LLDP_RegFuncGetExtendTlvHook(LLDP_GETEXTTLV_HOOK_FUNC pfFuncHook);

/*******************************************************************************
*    Func Name: LLDP_CfgLocalChange
*      Purpose: 触发Local Change消息，LLDP进入快速模式
*  Description: 触发Local Change消息，LLDP进入快速模式
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulDestAddrGroup: 目的组播组的编号默认为Nearest bridg(1)
*                                               Nearest bridge              1
*                                               Nearest non-TPMR bridge     2
*                                               Nearest Customer Bridge     3
*       InOut: 
*       Output: 
*       Return: 
*      Caution: 产品RB保存的自定义TLV有变化的时候触发
*       Since: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-06   l00213099               Create
*
*******************************************************************************/
ULONG LLDP_CfgLocalChange(ULONG ulIfIndex, ULONG ulDestAddrGroup);

/*******************************************************************************
*    Func Name: LLDP_RegFuncInputHook
*      Purpose: 注册LLDP收包钩子函数
*  Description: 注册LLDP收包钩子函数
*        Input: LLDP_INPUT_HOOK_FUNC pfFuncHook:
*       InOut: 
*       Output: 
*       Return: 0   成功
*               非0 失败
*
*      Caution: 收到LLDP PDU时回调，此调用在协议栈处理之前。如果收到的是一个
*               新邻居的报文则回调时，LLDP尚未生成邻居节点
*       Since: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-06   l00213099               Create
*
*******************************************************************************/
ULONG LLDP_RegFuncInputHook(LLDP_INPUT_HOOK_FUNC pfFuncHook);

#ifdef  __cplusplus
}
#endif

#endif

