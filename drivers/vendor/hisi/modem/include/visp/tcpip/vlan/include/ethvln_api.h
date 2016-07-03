
#ifndef _ETHVLN_CFGAPI_EXT_H
#define _ETHVLN_CFGAPI_EXT_H

#ifdef  __cplusplus
extern "C"{
#endif

#define  ETHVLAN_IFNAME_MAXLEN       (47)/*接口名长度*/
#define  ETHVLN_BUFFER_MIN_LEN       (1024)

/* Add by Q62011 for BC3D0059108-10-31 */
/* Modified by s72256 for Req_201303115271  for 64 to 256*/ 
#define MAX_SUBIF_VIDNUM 256
/* Added macro for default value */
#define MAX_SUBIF_DEFAULT_VIDNUM 64

#define  ETHVLAN_OP_ADD             (1)     /*增加操作*/
#define  ETHVLAN_OP_DEL             (0)     /*删除操作*/

#define  ETHVLAN_DBG_SET            (1)     /*设置debug开关*/
#define  ETHVLAN_DBG_DEL            (0)     /*取消debug开关*/

#define  ETHVLAN_BUFFER_MIN_SIZE    (1024)  /*显示vlan debug信息的最小buffer大小*/

#define ETHVLAN_NOT_PROCESSED_BY_INTERMEDIATE 0  
#define ETHVLAN_PROCESSED_BY_INTERMEDIATE     1  

/* sup** vlan接口最小需要支持的VLAN数量,即一个接口至少需要配置的该数量及其以上的vlan才是su**r vlan接口 */
#define ETHVLAN_MIN_SUPERVLAN 2

enum TagFormat
{
    ETHVLAN_NONE = 0, 
    ETHVLAN_ISL = 1,            /*未支持*/
    ETHVLAN_DOT1Q = 2,          /*802.1q VLAN*/
    ETHVLAN_ALLTAG = 3          /*未支持*/
};

typedef enum SubIfErrorCode
{
    ETHVLN_OK,
    ETHVLN_ERR = MID_COMP_VLAN + 1,     /*1 获取不到VLAN控制块*/               
    ETHVLN_ERR_INVALID_POINTER,         /*2 无效指针 */
    ETHVLN_ERR_INVALID_PARAM_VALUE,     /*3 无效参数值 */
    ETHVLN_ERR_VID,                     /*4 VLAN ID不在有效范围内*/
    ETHVLN_ERR_VID_RANGE,               /*5 配置或删除的VLAN区间过大*/
    ETHVLN_ERR_MAXNUM_VID,              /*6 VLAN ID配置满规格*/
    ETHVLN_ERR_VIDNOEXIST,              /*7 该VLAN ID在系统中不存在*/
    ETHVLN_ERR_IF,                      /*8 根据索引获取不到接口或根据接口名获取接口索引失败*/
    ETHVLN_ERR_GET_MAINIF,              /*9 获取主接口失败*/
    ETHVLN_ERR_SUBIF,                   /*10 子接口不存在或子接口状态为Down*/
    ETHVLN_ERR_ALREADY_PRESENT,         /*11 子接口或主接口已经存在该VLAN ID*/
    ETHVLN_ERR_SUBIF_NOVID,             /*12 接口不存在该VLAN ID*/
    ETHVLN_ERR_IF_NOCFG_VID,            /*13 接口未配置任何VLAN ID*/
    ETHVLN_ERR_NOT_ETH_TYPE,            /*14 接口非eth类型*/
    ETHVLN_ERR_IS_TRUNKPORT,            /*15 接口是TRUNK成员端口*/
    ETHVLN_ERR_ENCAPTYPEERROR,          /*16 封装类型与配置不一致，当前仅支持802.1Q*/
    ETHVLN_ERR_WAITLIST,                /*17 WAITLIST注册失败*/
    ETHVLN_ERR_MEM,                     /*18 分配内存失败*/
    ETHVLN_ERR_MBUF,                    /*19 MBUF操作失败*/
    ETHVLN_ERR_ENABLE_OTH_VLAN_FUNC,    /*20 已使能其他的VLAN特性*/              
    ETHVLN_END_OF_TABLE,                /*21 查询到表尾*/
    ETHVLN_ERR_DISABLE,                 /*22 模块未初始化*/
    ETHVLN_ERR_GETWAITLISTPARA,         /*23 获取waitlist过滤指针失败 */
    ETHVLN_ERR_BUF_NOT_ENOUGH,          /*24 Buf空间不够 */
    ETHVLN_ERR_HA_WAITLIST_OPEN,        /*25 打开ETH VLAN HA waitlist 失败 */
    ETHVLN_ERR_HA_ABNORMAL,             /*26 HA备份内部异常 */
    ETHVLN_ERR_HA_TYPE,                 /*27 HA备份不识别类型 */
    ETHVLN_ERR_HA_SMOOTH,               /*28 正在进行手动倒换或平滑操作 */
    ETHVLN_ERR_HA_MEM_SMALL,            /*29 HA备份内存太小 */
    ETHVLN_ERR_HA_WRITE_QUE,            /*30 写HA队列失败 */
    ETHVLN_ERR_HA_WAITLIST_NULL,        /*31 从waitlist里面获取表项为空 */
    ETHVLN_ERR_INVLAD_WARNING_NUM,      /* 32 设定VLAN不一致告警个数非法 */
    ETHVLN_ERR_VIRTUAL_IF,              /* 33 非本板接口 */
    ETHVLN_NO_SPECIFY_VLAN_WARNING,     /* 34 指定的VLAN一致性告警不存在 */
        
    ETHVLN_ERR_MAX
}VLAN_ERR_E;

#pragma pack(1)
typedef  struct  tagDot1qHdr
{
    UCHAR       aucDestAddr[6];       /* Destination physical address */
    UCHAR       aucSrcAddr[6];        /* Source physical address */
    USHORT      usTPID ;              /* 802.1q Protype 8100 */
    USHORT      usTCI ;               /*user User_priority CFI VLANID */
    USHORT      usLenEtype;           /* Length or the type field */
}ETHVLAN_DOT1QHDR_S;

typedef struct stDot1qHdr
{
    USHORT      usEType;            /* To identify the physical layer */	
    USHORT      usVID;              /* The priority level,CFI and VID */
}VLAN_DOT1QHDR_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif



/*增加删除vlan API*/
typedef struct tagEthVlanOp
{    
    ULONG     ulOperType;                           /*1：增加，0：删除*/
    UCHAR     szIfName[ETHVLAN_IFNAME_MAXLEN + 1];  /*子接口名*/
    USHORT    usLowVid;                             /*vlan id*/
    USHORT    usHighVid;                            /*0：表示增加对应的vlan是usLowVid，
                                                      非0：表示增加对应的vlan是usLowVid～usHighVid*/
    ULONG     ulTagType;                            /*0:缺省值，802.1q ，  2：802.1q */ 
} ETHVLAN_OP_S;

/*查询vlan过滤条件*/
typedef struct tagEthVlanShowFilter
{    
    ULONG  ulIfIndex;                               /*对应子接口索引*/
    USHORT usVlanID;                               /* Vlan ID */
    USHORT usPadding;
} ETHVLAN_FILTER_S;                             

/*查询vlan信息的内容*/
typedef struct tagEthVlanIntf
{    
    ULONG     ulIfIndex;                            /*对应子接口的接口索引*/
    ULONG     ulTotalVlnNum;                        /*此子接口下查询到的vlan总数*/
    USHORT    usVid[MAX_SUBIF_VIDNUM];              /*存放对应各个vlan id的值*/
} ETHVLAN_INTF_S;

/*存储查询vlan统计的结果*/
typedef struct tagEthVlanStat
{    
    ULONG  ulReceivePacketCount;                    /*收到的报文数量*/
    ULONG  ulTransmitPacketCount;                   /*发送的报文数量*/
    ULONG  ulReceiveByteCount;                      /*收到的报文字节数*/
    ULONG  ulTransmitByteCount;                     /*发送的报文字节数*/
    
    ULONG  ulRecvMainMbufErr;                       /*主接口接收报文MBUF处理失败*/
    ULONG  ulRecvMainInvalidVid;                    /*主接口接收不正确的VLAN ID报文个数*/
    ULONG  ulRecvSubInvalidStat;                    /*子接口状态异常时接收报文个数*/
    ULONG  ulRecvSubInvalidEncapType;               /*接收与子接口VLAN类型不符的个数*/
    ULONG  ulSendSubMbufErr;                        /*子接口发送报文MBUF处理失败个数*/
    ULONG  ulSendSubInvalidVid;                     /*发送报文指定的VLAN ID与子接口配置不同的个数*/
    ULONG  ulSendSubPhyErr;                         /*子接口发送报文物理层返回失败个数*/
} ETHVLAN_STAT_S;

/* VLAN一致性告警最大值 */
#define ETHVLAN_MAX_WARNING_NUM  128
/* VLAN一致性告警产生 */
#define ETHVLAN_CONSISTENCY_WARNING_BEGIN  1
/* VLAN一致性告警消除 */
#define ETHVLAN_CONSISTENCY_WARNING_END  0

/* VLAN不一致告警消除原因 */
typedef enum enVlanConsitencyWarningRecoverReason
{
    VLAN_WARNING_REMOTE_MODIFY_VLAN = 1,    /* 对端修改VLAN配置和本端一致 */
    VLAN_WARNING_LOCAL_MODIFY_VLAN,         /* 本端修改VLAN配置和本端一致 */
    VLAN_WARNING_SUBIF_IS_DELETED,          /* 子接口被删除 */
    VLAN_WARNING_IP_IS_DELETED,             /* 子接口删除了IP */
    VLAN_WARNING_NUM_DECREASE,              /* 告警节点规格调小,包括去使能VLAN一致性监视告警功能,即将告警次数设置为0 */
    VLAN_WARNING_USER_DELETED,              /* 用户删除告警 */
    VLAN_WARNING_MAX,                       /* 告警消除字段无效值 */
}VLAN_CONSISTENCY_WARNING_RECOVER_REASON_E;

/* VLAN不一致告警信息 */
typedef struct tagVlanConsistencyWarning
{
    ULONG   ulSubIfIndex;                   /* 子接口索引 */
    ULONG   ulTotalVlanNum;                 /* 子接口加入的VLAN总数 */
    USHORT  usVid[MAX_SUBIF_VIDNUM];        /* 存放子接口当前加入的各个VLAN ID */
    ULONG   ulLocalIPAddr;                  /* 本端IP, 主机序 */
    ULONG   ulNeighbourIPAddr;              /* 邻居IP, 主机序 */
    USHORT  usNeighbourVlanID;              /* 告警时表示邻居所在VLAN */
    UCHAR   ucEventType;                    /* 告警产生:ETHVLAN_CONSISTENCY_WARNING_BEGIN; 告警消除:ETHVLAN_CONSISTENCY_WARNING_END; */
    UCHAR   ucRecoverReason;                /* 告警消除的原因,参见VLAN_CONSISTENCY_WARNING_RECOVER_REASON_E枚举定义 */
}VLAN_CONSISTENCY_WARNING_S;

typedef struct tagETHVLAN_BCPKT_PARA
{
    MBUF_S *pstMBuf;
}ETHVLAN_BCPKT_PARA_S;
typedef ULONG (*ETHVLAN_BCPKT_HOOK_FUNC)(ETHVLAN_BCPKT_PARA_S *pstPara);

typedef ULONG(*ETHVLAN_TOS_TO_VLAN_PRIORITY)(MBUF_S *pMbuf,ULONG *pPriority);

extern ULONG ETHVLAN_CreateDelVlan( ETHVLAN_OP_S* pstVLAN );
extern ULONG ETHVLAN_GetVlanStat( UCHAR* pcIfName, USHORT usVID,ETHVLAN_STAT_S* pstVlnStat );
extern ULONG ETHVLAN_ResetVlanStat( UCHAR* pcIfName, USHORT usVID );
extern VOID ETHVLAN_ShowVlanStat( UCHAR *pcIfName, USHORT usVid);
extern ULONG ETHVLAN_SetVlanDebug( ULONG ulDebugSet, UCHAR *pcIfName, USHORT usVid );
extern ULONG ETHVLAN_GetVlanDebug(CHAR *pcBuffer, ULONG ulMaxLen, ETHVLAN_FILTER_S *pstFilter);
extern VOID ETHVLAN_SetVlanErrDebug( BOOL_T bErrDbg );
extern VOID ETHVLAN_ShowVlanDebug( UCHAR *pcIfName, USHORT usVid );
extern VOID ETHVLAN_RegTos2VlanPriorityHook(ETHVLAN_TOS_TO_VLAN_PRIORITY pfFunHook);
extern VOID ETHVLAN_ShowVlanCfg( UCHAR *pName );
extern ULONG ETHVLAN_TableOpen( UINTPTR* pulWaitListHandle, ETHVLAN_FILTER_S* pstVlan );
extern ULONG ETHVLAN_TableClose( UINTPTR pulWaitListHandle );
extern ULONG ETHVLAN_GetNext( UINTPTR ulEntryWaitList, ETHVLAN_INTF_S* pstVlanIntf );

extern ULONG TCPIP_ETHVLAN_dot1qInput(MBUF_S * pstMbuf,ULONG ulIfIndex);


ULONG TCPIP_SetVlanConsistencyMonitor(ULONG ulSubIfIndex, ULONG ulMaxWarningNum);


ULONG TCPIP_GetVlanConsistencyMonitor(ULONG ulSubIfIndex, ULONG *pulMaxWarningNum);


ULONG TCPIP_DeleteVlanConsistencyWarning(ULONG ulSubIfIndex, ULONG ulLocalIPAddr, ULONG ulNeighbourIPAddr);


VOID TCPIP_ShowVlanConsistencyWarningInfo(ULONG ulSubIfIndex);


ULONG TCPIP_RegFuncBroadcastVlanPktHook(ETHVLAN_BCPKT_HOOK_FUNC  pfEthvln_BCPkt_Hook);

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif 

