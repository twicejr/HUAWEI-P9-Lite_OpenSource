/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              1ag_typ.h
*
*  Project Code: VISPV100R007
*   Module Name: 1AG  
*  Date Created: 2008-2-29
*        Author: yebo(62007)
*   Description: 定义1AG枚举变量及结构体类型
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-2-29   yebo(62007)      Create the first version.
*
*******************************************************************************/
#ifndef _1AG_TYP_H
#define _1AG_TYP_H

#ifdef  __cplusplus
        extern "C"{
#endif

/*-------------------------------结构体类型定义Begin------------------------------
---------------------------------------------------------------------------------*/
#pragma    pack(1)
/* VLAN标签结构体定义 */
typedef struct  tagOAM1AGVLANTAG
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    USHORT  usVlanId   :12;                           /* VLanID */
    USHORT  usCfi      :1;                            /* 0表示physical地址是经典格式，1表示physical地址不是经典格式，默认是0 */
    USHORT  usPriority :3;                            /* 报文优先级 */
#else
    USHORT  usPriority :3;                            /* 报文优先级 */
    USHORT  usCfi      :1;                            /* 0表示physical地址是经典格式，1表示physical地址不是经典格式，默认是0 */
    USHORT  usVlanId   :12;                           /* VLanID */
#endif
}OAM1AG_VLANTAG_S;

/* Added begin for 支持接收不带VLAN头的1AG报文2009-05-14 */
/*OAM 1AG 不带VLAN的SNAP以太头*/
typedef struct  tagOAM1AGNOVLANSNAPETHDR
{
    UCHAR   ucHdrDstMacAddr[OAM_1AG_MACADDR_LEN];     /*目的physical地址   */
    UCHAR   ucHdrSrcMacAddr[OAM_1AG_MACADDR_LEN];     /*源physical地址     */
    USHORT             usLen;                         /*以太网幀长度  */
    UCHAR              ucDSAP;                        /* destination service access point*/
    UCHAR              ucSSAP;                        /* source service access point */
    UCHAR              ucCtrl;                        /* control domain */
    UCHAR              ucORI[3];                              
    USHORT             usType;
}OAM1AG_NOVLAN_ETSNAPHDR_S;

/*OAM 1AG 不带VLAN的以太头*/
typedef struct tagOAM1AGNOVLANETHERHDR  
{
    UCHAR   ucHdrDstMacAddr[OAM_1AG_MACADDR_LEN];     /*目的physical地址   */
    UCHAR   ucHdrSrcMacAddr[OAM_1AG_MACADDR_LEN];     /*源physical地址     */
    USHORT  usType;                                   /* 以太类型 */
}OAM1AG_NOVLAN_ETHERHDR_S;
/* Added end for 支持接收不带VLAN头的1AG报文2009-05-14 */

/*OAM 1AG 带VLAN的SNAP以太头*/
typedef struct  tagOAM1AGSNAPETHDR
{
    UCHAR   ucHdrDstMacAddr[OAM_1AG_MACADDR_LEN];     /*目的physical地址   */
    UCHAR   ucHdrSrcMacAddr[OAM_1AG_MACADDR_LEN];     /*源physical地址     */
    USHORT  usVlanEthtype;                            /*0x8100*/
    OAM1AG_VLANTAG_S   stVlanTag;                     /* vlan标签 */
    USHORT             usLen;                         /*以太网幀长度  */
    UCHAR              ucDSAP;                        /* destination service access point*/
    UCHAR              ucSSAP;                        /* source service access point */
    UCHAR              ucCtrl;                        /* control domain */
    UCHAR              ucORI[3];                              
    USHORT             usType;
}OAM1AG_ETSNAPHDR_S;

/*OAM 1AG 带VLAN的以太头*/
typedef struct tagOAM1AGETHERHDR
{
    UCHAR   ucHdrDstMacAddr[OAM_1AG_MACADDR_LEN];     /*目的physical地址   */
    UCHAR   ucHdrSrcMacAddr[OAM_1AG_MACADDR_LEN];     /*源physical地址     */
    USHORT  usVlanEthtype;                            /*0x8100*/
    OAM1AG_VLANTAG_S    stVlanTag;                    /* vlan标签 */
    USHORT  usType;                                   /* 以太类型 */
}OAM1AG_ETHERHDR_S;

/*公共1ag头部*/
typedef struct tagOam1agPubHead
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion:5;                                /*MD的级别*/
    UCHAR ucMdLevel:3;                                /*版本号*/
#else
    UCHAR ucMdLevel:3;
    UCHAR ucVersion:5;
#endif
    UCHAR ucOpcode;                                   /*CFM数据帧类型*/
    UCHAR ucFlag;                                     /*标记*/
    UCHAR ucFirstTlvOffset;                           /*第一个TLV的偏移量*/
}OAM_1AG_PUBHEAD_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif


/*MD全局数组结构*/
typedef struct tagOAM_1AG_MDCHAIN
{
    VOID *pstMdInfo;                                  /*指向Md控制块,初始化为空*/
}OAM_1AG_MDCHAIN_S;

/*MA全局数组结构*/
typedef struct tagOAM_1AG_MACHAIN
{
    struct tagOAM_1AG_MACHAIN *pstNext;               /*指向下一个MA*/
    VOID *pstMaInfo;                                  /*指向Ma控制块,初始化为空*/
}OAM_1AG_MACHAIN_S;

/*MEP全局数组结构*/
typedef struct tagOAM_1AG_MEPCHAIN
{
    DLL_NODE_S stDllNode;                             /*用于超时定时器的分组*/
    VOID *pstMepInfo;                                 /*指向Mep控制块,初始化为空*/
}OAM_1AG_MEPCHAIN_S;

/*RMEP全局数组结构*/
typedef struct tagOAM_1AG_RMEPCHAIN
{
    DLL_NODE_S stDllNode;                             /*用于超时定时器的分组*/
    VOID *pstRmepInfo;                                /*指向Rmep控制块,初始化为空*/
}OAM_1AG_RMEPCHAIN_S;

/*AIS MA 数组结构*/
typedef struct tagOAM_Y1731_AISMACHAIN
{
    DLL_NODE_S stDllNode;                             /*用于超时定时器的分组*/
    VOID *pstAISMaInfo;                                /*指向MA 控制块,初始化为空*/
}OAM_Y1731_AISMACHAIN_S;

/*MD数据结构*/
typedef struct tagOAM_1AG_MD
{
    DLL_S stMaDllList;                                /*MD下MA链表*/
    UCHAR ucMdLevel;                                  /*MD级别*/
    UCHAR ucMdNameType;                               /*MD名字类型,目前只支持字符串形式*/
    UCHAR ucRes[2];    
    UCHAR szMDName[OAM_1AG_MAX_MDNAME_LEN + 1];       /*MD名字,最长为43字节*/
    ULONG ulMdIndex;                                  /*保存MD索引*/
    ULONG ulMdNameHash;                               /*MD名的Hash值*/
}OAM_1AG_MD_S;

/*MA数据结构*/
typedef struct tagOAM_1AG_MA
{
    DLL_NODE_S stDllNode;                           /*MD下节点*/
    DLL_S  stMepDllList;                            /*MA下MEP链表*/
    DLL_S  stRmepDllList;                           /*MA下RMEP链表*/
    USHORT usVlanId ;                               /*MA关联的VLAN ID值*/
    UCHAR  ucMaNameType;                            /*ma名字类型,目前只支持形式*/
    UCHAR  ucCcmInterval;                           /*CCM发送间隔*/
    UCHAR  szMaName[OAM_1AG_MAX_MANAME_LEN + 1];    /*ma名字，最大长度为43*/
    UCHAR  ucCompatibleFlag;                        /*兼容标记,0-为标准模式,1-数通模式*/
    UCHAR  ucRdiFlag;                               /*MA 内RDI标记,同时也是RDI告警是否消失的标记*/
    USHORT usRcvRdiCount;                           /*接收到的RDI计数,说明对远端有可能产生了故障 */
    USHORT usSndRdiCount;                           /*本端的RDI计数,当此值为0时说明本端没有MEP产生故障*/
    UCHAR  ucMaVlanPri;                             /*基于MA的VLAN优先级*/
    UCHAR  ucRes;
    ULONG  ulMdIndex;                               /*保存MD索引*/
    ULONG  ulMaIndex;                               /*保存MA索引*/
    ULONG  ulMaHashIndex;                           /*MA索引*/
    UCHAR  ucAisEnable;                            /* AIS使能开关*/
    UCHAR  ucAisWarningFlag;                                /* AIS告警标识*/
    UCHAR  ucAisInterval;                         /*  AIS 传输周期 */
    UCHAR  ucAisRes[1];    
    USHORT usAisOutTimerSet;                        /*AIS告警超时设置值*/
    USHORT usAisOutTimerCount;                      /*AIS告警超时计数值*/
}OAM_1AG_MA_S;

/* MEP数据结构 */
typedef struct tagOAM_1AG_MEP
{
    DLL_NODE_S stDllNode;                           /*MA下双向链表节点*/
    ULONG  ulMaIndex;                               /*所属MA索引*/
    ULONG  ulMepIndex;                              /*保存MEP索引*/
    ULONG  ulIfIndex;                               /*所属接口索引*/
    USHORT usMepId;                                 /*MEP ID*/
    UCHAR  ucCcSendEnable;                          /*是否使能CCM发送功能标记*/    
    UCHAR  ucPad1;                                  /* 填充1字节 */
    USHORT usMepOutTimerSet;                        /*mep超时发送CCM设置值*/
    USHORT usMepOutTimerCount;                      /*mep超时发送CCm计数值*/
    UCHAR  ucLevel;                                 /*MEP级别,同所在MD级别,方便判断*/

    /* Edit by L00105073 at 2009-12-24 for 1agOverTrunkPort
        在ifnet结构上增加一个字段if_ul1agMultiCount，用于是否需要下发多播组的计数，
        增加if_ul1agMultiCount后，下面这个字段废弃不用 */
    UCHAR  ucMultiFlag;                             /* 标志删除所有MEP时是否需要下发退出多播组命令 */
                                                    
    UCHAR  uc1agVersion;                            /* 该MEP使用的1AG版本号,0:Draft7版本;1:标准版本;2:Y1731版本 */
    UCHAR  ucVlanFlag;                              /*该MEP下发送的报文是否带VLAN头标志.
                                                      0:表示不需要带VLAN头,1表示需要带VLAN*/
    OAM_1AG_STAT_S stMepStat;                       /*MEP统计信息*/
    USHORT usLossDetectTimer;                       /*本端MEP的Loss检测时间*/                                                  
    UCHAR  ucPadding[2];                            /*padding*/
    /* Add for V2R3C06, by z00171897/p00193127, at 2011-10-17. 修改原因: 支持Y1731使能/去使性能检测 */
    MEP_PM_INFO_S stPMCheckDLM;
    MEP_PM_INFO_S stPMCheckSLM;
    MEP_PM_INFO_S stPMCheckDDM; 
}OAM_1AG_MEP_S;

/* RMEP性能监视信息 */
typedef struct tagRMEP_PM_INFO
{
    USHORT usMepId;
    USHORT usPMEnableFlag;
}RMEP_PM_INFO_S;

/* RMEP数据结构 */
typedef struct tagOAM_1AG_RMEP
{
    DLL_NODE_S stDllNode; 
    ULONG  ulMaIndex;                               /*所属MA数组索引*/
    ULONG  ulRmepIndex;                             /*RMEP数组索引*/
    ULONG  ulIfIndex;                               /*RMEP出接口索引*/
    ULONG  ulRMepOldTimerSet;                       /*Rmep超时后老化CCM设置值*/
    ULONG  ulRMepOldTimerCount;                     /*rmep老化CCm计数值*/
    USHORT usRmepId;                                /*RMEP ID值*/
    USHORT usRMepOutTimerSet;                       /*Rmep超时发送CCM设置值*/
    USHORT usRMepOutTimerCount;                     /*Rmep超时发送CCm计数值*/
    UCHAR  ucRemoteIfFlag;                          /*远端接口状态标记,同时也是告警标记*/
    UCHAR  ucCcLost;                                /*ccm LOST告警标记*/
    UCHAR  ucRdiFlag;                               /*记录是否已收到过带RDI的CCM,收到后MA内的接收RDI计算要增加*/
    UCHAR  ucMdLevelFlag;                           /*MD 级别,1-大于本级别,0-等于本级别*/ 
    UCHAR  ucRMepStatic;                            /*0表示动态生成的RMEP ，1表示静态创建的RMEP*/
    UCHAR  ucCcmInterval;                           /*对端CCM发送隔间*/
    UCHAR  aucMacAddress[OAM_1AG_MACADDR_LEN];      /*RMEP physical地址*/
    UCHAR  ucDownloadNp;                            /*置1为此RMEP下发过NP*/
    UCHAR  ucVlanFlag;                              /*收到CCM报文是否带有VLAN标记 0-不带VLAN，1-带VLAN */
    UCHAR  ucMdLevel;                               /*保存remp MD级别(对端),静态RMEP在没有收到CCM之前保留为创建时所在的MD级别 */
    UCHAR  ucRmepCheck;                             /*未收到CCM前是否向NP下发RMEP，已使NP可以进行连通性检查*/
    UCHAR  ucPadding[2];                            /*Padding*/
    ULONG  ulSequence;                              /*序列号*/
    /* Add for V2R3C06, by z00171897/p00193127, at 2011-10-17. 修改原因: 支持Y1731使能/去使性能检测 */
    RMEP_PM_INFO_S  stPMCheckDLM;                       /*双端帧丢失检测使能标记*/
    RMEP_PM_INFO_S  stPMCheckSLM;                       /*单端帧丢失检测使能标记*/
    RMEP_PM_INFO_S  stPMCheckDDM;                       /*双向延时检测使能标记*/

    /* Modified by likaikun213099, 支持基于RMEP的CCM统计功能, 2014/10/15   问题单号:DTS2014101504612  */
    OAM_1AG_RMEP_STAT_S stRMepStat;                              /* 收到的ccm报文统计 */
    /*End of Modified by likaikun213099, 2014/10/15   问题单号:DTS2014101504612  */
}OAM_1AG_RMEP_S;
/*---------------------------------------------------------------------------------------
---------------------------------------CCM_Struct_Begin----------------------------------*/
#pragma    pack(1)
/*普通CCM的TLV结构*/
typedef struct tagOAM_1AG_INTERFACETLV
{
    UCHAR  ucType;                                  /*该TLV字段的类型*/
    USHORT usLength;                                /*TLV字段中Value值的长度*/
    UCHAR  ucValue;                                 /*TLV字段中的Value值*/
}OAM_1AG_INTERFACETLV_S;

/*CCM报文的模版*/
typedef struct tagOAM_1AG_CCM_TEMPLET
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion:5;                              /*MD的级别*/
    UCHAR ucMdLevel:3;                              /*版本号*/
#else
    UCHAR ucMdLevel:3;
    UCHAR ucVersion:5;
#endif
    UCHAR ucOpcode;                                 /*CFM数据帧类型*/
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucInterval:3;                             /*CCM发送间隔*/
    UCHAR ucReserve:4;
    UCHAR ucRdi:1;                                  /*RDI位*/
#else
    UCHAR ucRdi:1;
    UCHAR ucReserve:4;
    UCHAR ucInterval:3;
#endif
    UCHAR ucTlvOffset;                              /*报文头到第一个TLV字段的偏移量*/
    ULONG ulSequence;                               /*报文的序列号*/
    USHORT usMepId;                                 /*MEP标识*/
    UCHAR ucMdMaInfo[OAM_1AG_MAX_MDMAINFO_LEN];     /*保存MD、MA的类型、长度和名称*/
}OAM_1AG_CCM_TEMPLET_S;

/*封装了二层头后的CCM报文*/
typedef struct tagOAM_1AG_CCM_Packet
{
    
    OAM1AG_ETHERHDR_S      stEtherHeader;           /*以太头*/
    OAM_1AG_CCM_TEMPLET_S  stCcmTemplet;            /*报文的模版*/
    OAM_1AG_INTERFACETLV_S stInterfaceTlv;          /*CCM报文的第一个TLV*/
}OAM_1AG_CCM_PACKET_S;

typedef struct tagOAM_1AG_CCM_UPDATE_INFO
{
    UCHAR  ucVlanFlag;          /* 对端发送的CCM报文携带VLAN tag */
    UCHAR  ucMdLevel;           /* 对端发送的CCM报文的MD 级别 */
    UCHAR  ucPadding[2];
}OAM_1AG_CCM_UPDATE_INFO_S;

typedef struct tagOAM_Y1731_AIS_Packet
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion:5;                                /*MD的级别*/
    UCHAR ucMdLevel:3;                                /*版本号*/
#else
    UCHAR ucMdLevel:3;
    UCHAR ucVersion:5;
#endif
    UCHAR ucOpcode;                                   /*CFM数据帧类型*/
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucInterval:3;                                     /*AIS 报文周期*/
    UCHAR ucReserve:5;                                
#else
    UCHAR ucReserve:5;                                    
    UCHAR ucInterval:3;                                     /*AIS 报文周期*/
#endif
    UCHAR ucFirstTlvOffset;                           /*第一个TLV的偏移量*/  
    UCHAR  ucEndTlv;                                    /*结尾TLV*/
}OAM_Y1731_AIS_PACKET_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif


/*---------------------------------------CCM_Struct_End-----------------------------------
------------------------------------------------------------------------------------------*/
/*OAM 1AG mode Info*/
typedef struct tagOAM_1AG_MOD_INFO
{
    ULONG ulMID_Oam1ag;
    ULONG ulNpModel;  /*工作的NP模式*/
    ULONG ulDefaultVersion;  /* 1AG默认协议版本*/
}OAM_1AG_MOD_INFO_S;

/*OAM1AG组件Shell向Core注册的回调函数集*/
typedef struct tagOam1agShellCallback
{
    VOID (*pfOAM_1AG_DebugInfo)(CHAR * szStr);
}OAM_1AG_SHELL_CALLBACK_S;

#pragma    pack(1)

/* 1AG-CFM-2007 LTM Egress TLV 格式  */
typedef struct tagOAM_1AG_LTM_EGRESS_TLV
{
    UCHAR  ucType;                               /* 类型 */
    USHORT usLength;                             /* 长度 */
    UCHAR  aucEgressIdentifier[OAM_1AG_EGRESSID_SIZE];   /* 出接口标识符 */
}OAM_1AG_LTM_EGRESS_TLV_S;

/* 1AG-CFM-2007 LTR Egress TLV 格式  */
typedef struct tagOAM_1AG_LTR_EGRESS_TLV
{
    UCHAR  ucType;                                 /* 类型 */
    USHORT usLength;                               /* 长度 */
    UCHAR  aucLastEgressId[OAM_1AG_EGRESSID_SIZE]; /* 上一个出接口标识符 */
    UCHAR  aucNextEgressId[OAM_1AG_EGRESSID_SIZE]; /* 本地出接口标识符 */    
}OAM_1AG_LTR_EGRESS_TLV_S;

/* 包含入端口信息的TLV */
typedef struct tagOAM_1AG_REPLYINGRESSTLV
{
    UCHAR ucType;                                /* 类型 */
    USHORT usLength;                             /* 长度 */
    UCHAR ucIngressAction;                       /* 入接口动作 */ 
    UCHAR aucIngressMac[OAM_1AG_MACADDR_LEN];    /* 入接口physical地址 */
    UCHAR ucIngressPortIDLength;                 /* 入接口端口ID长度 */
    UCHAR ucIngressPortIDSubtype;                /* 入接口端口ID子类型 */
    UCHAR aucIngressPortID[OAM_1AG_PORTID_SIZE]; /* 入接口端口ID */
}OAM_1AG_REPLYINGRESSTLV_S;

/* 包含出端口信息的TLV */
typedef struct tagOAM_1AG_REPLYEGRESSTLV
{
    UCHAR ucType;                                /* 类型 */
    USHORT usLength;                             /* 长度 */
    UCHAR ucEgressAction;                        /* 出接口动作 */
    UCHAR aucEgressMac[OAM_1AG_MACADDR_LEN];     /* 出接口physical地址 */
    UCHAR ucEgressPortIDLength;                  /* 出接口端口ID长度 */
    UCHAR ucEgressPortIDSubtype;                 /* 出接口端口ID子类型 */
    UCHAR aucEgressPortID[OAM_1AG_PORTID_SIZE];  /* 出接口端口ID */
}OAM_1AG_REPLYEGRESSTLV_S;

/* Y1731入端口信息的TLV */
typedef struct tagOAM_1AG_Y1731REPLYINGRESSTLV
{
    UCHAR ucType;                                /* 类型 */
    USHORT usLength;                             /* 长度 */
    UCHAR ucIngressAction;                       /* 入接口动作 */ 
    UCHAR aucIngressMac[OAM_1AG_MACADDR_LEN];    /* 入接口physical地址 */
}OAM_1AG_Y1731REPLYINGRESSTLV_S;

/* Y1731出端口信息的TLV */
typedef struct tagOAM_1AG_Y1731REPLYEGRESSTLV
{
    UCHAR ucType;                                /* 类型 */
    USHORT usLength;                             /* 长度 */
    UCHAR ucEgressAction;                        /* 出接口动作 */
    UCHAR aucEgressMac[OAM_1AG_MACADDR_LEN];     /* 出接口physical地址 */
}OAM_1AG_Y1731REPLYEGRESSTLV_S;


/* 接收到的LTR的信息 */
typedef struct tagOAM_1AG_LTR_RECV
{
    DLL_NODE_S stLtrNode;                           /* LTR节点 */
    ULONG ulLTRSendId;                              /* LTR标识符 */
    UCHAR aucDmac[OAM_1AG_MACADDR_LEN];             /* 目的地址 */
    UCHAR aucSmac[OAM_1AG_MACADDR_LEN];             /* 源地址 */
    UCHAR aucLastEgressId[OAM_1AG_EGRESSID_SIZE];   /* 上一个出接口标识符 */
    UCHAR aucNextEgressId[OAM_1AG_EGRESSID_SIZE];   /* 本地出接口标识符 */
    UCHAR ucReplyTtl;                               /* 回复TTL */
    UCHAR ucReplyAction;                            /* 回复动作 */
    UCHAR ucFwdYes;                                 /* 是否转发 */
    UCHAR ucIsMep;                                  /* 是否MEP */
    OAM_1AG_REPLYINGRESSTLV_S stReplyIngressTlv;    /* 回复入接口TLV*/
    OAM_1AG_REPLYEGRESSTLV_S stReplyEgressTlv;      /* 回复出接口TLV*/
}OAM_1AG_LTR_RECV_S;

/* Draft7协议标准LTR报文 */
typedef struct tagOAM_1AG_LTR_DRAFT7
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion    :5;                         /* 1AG版本 */  
    UCHAR ucLevel      :3;                         /* MD级别 */
#else
    UCHAR ucLevel      :3;                         /* MD级别 */
    UCHAR ucVersion    :5;                         /* 1AG版本 */
#endif 
    UCHAR ucOpCode;                                /* 操作码 */
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucReserve    :6;   
    UCHAR ucIsMep      :1;                         /* 是否MEP */
    UCHAR ucFwdYes     :1;                         /* 是否转发 */
#else
    UCHAR ucFwdYes     :1;                         /* 是否转发 */
    UCHAR ucIsMep      :1;                         /* 是否MEP */
    UCHAR ucReserve    :6;   
#endif
    UCHAR ucFirstTlvOffset;                        /* 第一个TLV偏移量 */
    ULONG ulLTRSendId;                             /* LTR标识符 */
    UCHAR aucLastEgressId[OAM_1AG_EGRESSID_SIZE];  /* 上一个出接口标识符 */
    UCHAR aucNextEgressId[OAM_1AG_EGRESSID_SIZE];  /* 本地出接口标识符 */
    UCHAR ucReplyTtl;                              /* 回复TTL */
    UCHAR ucReplyAction;                           /* 回复动作 */
    UCHAR aucReserve[6];
    OAM_1AG_REPLYINGRESSTLV_S stReplyIngressTlv;   /* 回复入接口TLV*/
    OAM_1AG_REPLYEGRESSTLV_S stReplyEgressTlv;     /* 回复出接口TLV*/
    UCHAR ucEndTlv;                                /* 结束TLV */
}OAM_1AG_LTR_DRAFT7_S;

/* 1AG-CFM-2007协议标准LTR报文 */
typedef struct tagOAM_1AG_LTR_STD
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion    :5;                         /* 1AG版本 */  
    UCHAR ucLevel      :3;                         /* MD级别 */
#else
    UCHAR ucLevel      :3;                         /* MD级别 */
    UCHAR ucVersion    :5;                         /* 1AG版本 */
#endif 
    UCHAR ucOpCode;                                /* 操作码 */
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucReserve    :5;   
    UCHAR ucIsMep      :1;                         /* 是否MEP */
    UCHAR ucFwdYes     :1;                         /* 是否转发 */
    UCHAR ucUseFDBonly :1;
#else
    UCHAR ucUseFDBonly :1;
    UCHAR ucFwdYes     :1;                         /* 是否转发 */
    UCHAR ucIsMep      :1;                         /* 是否MEP */
    UCHAR ucReserve    :5;   
#endif
    UCHAR ucFirstTlvOffset;                        /* 第一个TLV偏移量 */
    ULONG ulLTRSendId;                             /* LTR标识符 */
    UCHAR ucReplyTtl;                              /* 回复TTL */
    UCHAR ucReplyAction;                           /* 回复动作 */
}OAM_1AG_LTR_STD_S;

/* 数通格式LTR报文 */
typedef struct tagOAM_1AG_LTR_VRP
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion    :5;                          /* 1AG版本 */  
    UCHAR ucLevel      :3;                          /* MD级别 */
#else
    UCHAR ucLevel      :3;                          /* MD级别 */
    UCHAR ucVersion    :5;                          /* 1AG版本 */
#endif    
    UCHAR ucOpCode;                                 /* 操作码 */
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucReserve    :6;   
    UCHAR ucIsMep      :1;                          /* 是否MEP */
    UCHAR ucFwdYes     :1;                          /* 是否转发 */
#else
    UCHAR ucFwdYes     :1;                          /* 是否转发 */
    UCHAR ucIsMep      :1;                          /* 是否MEP */
    UCHAR ucReserve    :6;   
#endif     

    UCHAR ucFirstTlvOffset;                         /* 第一个TLV偏移量 */
    ULONG ulLTRSendId;                              /* LTR标识符 */
    UCHAR aucLastEgressId[OAM_1AG_EGRESSID_SIZE];   /* 上一个出接口标识符 */
    UCHAR aucNextEgressId[OAM_1AG_EGRESSID_SIZE];   /* 本地出接口标识符 */
    UCHAR ucReplyTtl;                               /* 回复TTL */
    UCHAR ucReplyAction;                            /* 回复动作 */
    UCHAR aucReserve[6];
    OAM_1AG_REPLYINGRESSTLV_S stReplyIngressTlv;    /* 回复入接口TLV*/
    OAM_1AG_REPLYEGRESSTLV_S stReplyEgressTlv;      /* 回复出接口TLV*/

    ULONG ulLspToken;                               /* 填0 */
    USHORT usVsiIndex;                              /* 填0xFFFF */
    UCHAR ucLtrPwFlag;                              /* 填0 */
    UCHAR ucBroadcastFlag;                          /* 填0 */
    UCHAR ucEndTlv;                                 /* 结束TLV */
    UCHAR aucReserve2[3];
}OAM_1AG_LTR_VRP_S;

/* Draft7协议标准LTM报文 */
typedef struct tagOAM_1AG_LTM_DRAFT7
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion    :5;                              /* 1AG版本 */  
    UCHAR ucLevel      :3;                              /* MD级别 */
#else
    UCHAR ucLevel      :3;                              /* MD级别 */
    UCHAR ucVersion    :5;                              /* 1AG版本 */
#endif
    UCHAR ucOpCode;                                     /* 操作码 */
    UCHAR ucFlag;                                       /* 标志 */
    UCHAR ucFirstTlvOffset;                             /* 第一个TLV偏移量 */
    ULONG ulLTMSendId;                                  /* LTM标识符 */
    UCHAR aucEgressIdentifier[OAM_1AG_EGRESSID_SIZE];   /* 出接口标识符 */
    UCHAR ucTtl;                                        /* TTL,默认64 */
    UCHAR aucOriginalMac[OAM_1AG_MACADDR_LEN];          /* 发起LTM的源地址 */
    UCHAR aucTargetMac[OAM_1AG_MACADDR_LEN];            /* LTM的目的地址 */
    UCHAR aucReserve[3];                                /* 只是为了实现的方便，也不违反协议 */
    UCHAR ucEndTlv;                                     /* 结束TLV */
}OAM_1AG_LTM_DRAFT7_S;

/* 1AG-CFM-2007标准协议LTM报文 */
typedef struct tagOAM_1AG_LTM_STD
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion    :5;                              /* 1AG版本 */  
    UCHAR ucLevel      :3;                              /* MD级别 */
#else
    UCHAR ucLevel      :3;                              /* MD级别 */
    UCHAR ucVersion    :5;                              /* 1AG版本 */
#endif
    UCHAR ucOpCode;                                     /* 操作码 */
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucReserve    :7;   
    UCHAR ucUseFDBonly :1;
#else
    UCHAR ucUseFDBonly :1;
    UCHAR ucReserve    :7;   
#endif

    UCHAR ucFirstTlvOffset;                             /* 第一个TLV偏移量 */
    ULONG ulLTMSendId;                                  /* LTM标识符 */
    UCHAR ucTtl;                                        /* TTL,默认64 */
    UCHAR aucOriginalMac[OAM_1AG_MACADDR_LEN];          /* 发起LTM的源地址 */
    UCHAR aucTargetMac[OAM_1AG_MACADDR_LEN];            /* LTM的目的地址 */
}OAM_1AG_LTM_STD_S;

/* 数通格式LTM报文 */
typedef struct tagOAM_1AG_LTM_VRP
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucVersion    :5;                              /* 1AG版本 */  
    UCHAR ucLevel      :3;                              /* MD级别 */
#else
    UCHAR ucLevel      :3;                              /* MD级别 */
    UCHAR ucVersion    :5;                              /* 1AG版本 */
#endif    

    UCHAR ucOpCode;                                     /* 操作码 */
    UCHAR ucFlag;                                       /* 标志 */
    UCHAR ucFirstTlvOffset;                             /* 第一个TLV偏移量 */
    ULONG ulLTMSendId;                                  /* LTM标识符 */
    UCHAR aucEgressIdentifier[OAM_1AG_EGRESSID_SIZE];   /* 出接口标识符 */
    UCHAR ucTtl;                                        /* TTL,默认64 */
    UCHAR aucOriginalMac[OAM_1AG_MACADDR_LEN];          /* 发起LTM的源地址 */
    UCHAR aucTargetMac[OAM_1AG_MACADDR_LEN];            /* LTM的目的地址 */
    UCHAR aucReserve[3];
    ULONG ulLspToken;                                   /* 填0 */
    USHORT usVsiIndex;                                  /* 填0xFFFF */
    USHORT usLtrPwFlag;                                 /* 填0 */
    UCHAR ucBroadcastFlag;                              /* 填0 */
    UCHAR ucEndTlv;                                     /* 结束TLV */
    UCHAR aucReserve2[13];
}OAM_1AG_LTM_VRP_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif


/* 已发送的LTM的信息 */
typedef struct tagOAM_1AG_LTM_SENDOUTDATA
{
    DLL_S stLtrList;                         /* LTR链表 */ 
    ULONG ulLTMSendId;                       /* LTM发送标识 */
    ULONG ulExecID;                          /* 用户ID */
    ULONG ulSendTime;                        /* 发送时间戳 */
    ULONG ulTimeOut;                         /* 超时时间，单位秒 */
    ULONG ulTtl;                             /* 到达目的MP的最大跳数 */
    ULONG ulReadResult;                      /* 可读取标志，当置为1，表示可以打印之后的LTR链表，否则，应继续等待 */
    UCHAR aucTargetMac[OAM_1AG_MACADDR_LEN]; /* 目的physical地址 */
    UCHAR aucReserve[2];
}OAM_1AG_LTM_SENDOUTDATA_S;
/* 发送LT的任务所需的参数 */
typedef struct tagOAM_1AG_LT_PARA
{
    UCHAR aucTargetMac[OAM_1AG_MACADDR_LEN];    /* 目的MP的physical地址 */
    UCHAR aucSourceMac[OAM_1AG_MACADDR_LEN];    /* 发起MP的physical地址 */
    ULONG ulExecID;                             /* 用户ID */
    ULONG ulIfIndex;                            /* 出接口 */
    ULONG ulMepIndex;                           /* 发送LTM的MEP，统计信息关联于此MEP */
    ULONG ulLTMSendId;                          /* LTM发送标识 */
    ULONG ulTtl;                                /* 到达目的MP的最大跳数 */
    ULONG ulTimeOut;                            /* 超时时间，单位秒 */
    USHORT usVlanId;                            /* VLanID */
    UCHAR ucLevel;                              /* MD级别 */
    UCHAR ucFreeLtmIndex;                       /* 全局LTM数组中空闲节点索引 */
}OAM_1AG_LT_PARA_S;
/* 接收到的LTM信息 */
typedef struct tagOAM_1AG_LTM_RECV
{
    UCHAR aucDmac[OAM_1AG_MACADDR_LEN];                /* 目的地址 */
    UCHAR aucSmac[OAM_1AG_MACADDR_LEN];                /* 源地址 */
    USHORT usVlanId;                                   /* VLanID */
    USHORT usEthType;                                  /* 以太报文类型 */
    UCHAR ucPriority;                                  /* 报文优先级 */
    UCHAR ucVersion;                                   /* 1AG版本 */  
    UCHAR ucLevel;                                     /* MD级别 */
    UCHAR ucOpCode;                                    /* 操作码 */
    UCHAR ucFlag;                                      /* 标志 */
    UCHAR ucTtl;                                       /* TTL,默认64 */
    UCHAR aucRes[2];                                   /* 保留字段 */
    ULONG ulLTMSendId;                                 /* LTM标识符 */
    UCHAR aucEgressIdentifier[OAM_1AG_EGRESSID_SIZE];  /* 出接口标识符 */
    UCHAR aucOriginalMac[OAM_1AG_MACADDR_LEN];         /* 发起LTM的源地址 */
    UCHAR aucTargetMac[OAM_1AG_MACADDR_LEN];           /* LTM的目的地址 */
}OAM_1AG_LTM_RECV_S;

/* 要发送的LTR的信息 */
typedef struct tagOAM_1AG_LTR_SEND
{
    DLL_NODE_S stLtrNode;       /* LTR节点 */
    MBUF_S *pstMbuf;            /* 要发送的MBUF */
    ULONG ulIfIndex;            /* 出接口索引 */
}OAM_1AG_LTR_SEND_S;

/* DCDataTLV Value */
typedef struct tagOAM_1AG_DCDataTLV_Value
{
    ULONG   ulCPTimeHigh;   /*上层软件打的高四字节的时间戳*/
    ULONG   ulCPTimeLow;    /*上层软件打的低四字节的时间戳*/
    ULONG   ulNPTimeHigh;   /*NP软件打的高四字节的时间戳*/
    ULONG   ulNPTimeLow;    /*NP软件打的高四字节的时间戳*/
}OAM_1AG_VRPDATATLV_VALUE_S;
#pragma pack(1)

/*数通Data TLV数据类型定义*/
typedef struct tagOAM_1AG_VRPDataTLV
{
    UCHAR   ucType;                     /*TLV类型成员*/
    USHORT  usLength;                   /*TLV长度成员*/
    UCHAR   reserve;                    /*保留*/
    OAM_1AG_VRPDATATLV_VALUE_S stValue; /*TLV值成员*/
}OAM_1AG_VRPDATATLV_S;

/*标准格式TLV*/
typedef struct tagOAM_1AG_DataTLV
{
    UCHAR   ucType;                     /*TLV类型成员*/
    USHORT  usLength;                   /*TLV长度成员*/
    ULONG   ulValueHigh;                /*TLV值成员*/
    ULONG   ulValueLow;
}OAM_1AG_DATATLV_S;
/*标准LB报文头格式*/
typedef struct tagOAM_1AG_STDLBPACKET
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR   ucVersion    :5;       /* 1AG版本 */  
    UCHAR   ucLevel      :3;       /* MD级别 */
#else
    UCHAR   ucLevel      :3;       /* MD级别 */
    UCHAR   ucVersion    :5;       /* 1AG版本 */
#endif    
    UCHAR   ucOpCode;              /* 操作码 */
    UCHAR   ucFlag;                /*标志地段*/
    UCHAR   ucTLVOffset;           /*第一个TLV在报文中的偏移*/
    ULONG   ulSequence;            /*报文的序列号*/
    OAM_1AG_DATATLV_S  stdatatlv;  /*数据TLV定义*/
}OAM_1AG_STDLBPACKET_S;


/*数通LB报文格式*/
typedef struct tagOAM_1AG_VRPLBPACKET
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR   ucVersion    :5;    /* 1AG版本 */  
    UCHAR   ucLevel      :3;    /* MD级别 */
#else
    UCHAR   ucLevel      :3;    /* MD级别 */
    UCHAR   ucVersion    :5;    /* 1AG版本 */
#endif    
    UCHAR   ucOpCode;           /* 操作码 */
    UCHAR   ucFlag;             /*标志地段*/
    UCHAR   ucTLVOffset;        /*第一个TLV在报文中的偏移*/
    ULONG   ulSequence;         /*报文的序列号*/
    USHORT  usvsiIndex;
    UCHAR   ucFromPwlag;
    UCHAR   ucReserve[3];       /*保留*/
    OAM_1AG_VRPDATATLV_S    stSendLBMTLV;
    OAM_1AG_VRPDATATLV_S    stRecvLBMTLV;
    OAM_1AG_VRPDATATLV_S    stSendLBRTLV;
    OAM_1AG_VRPDATATLV_S    stRecvLBRTLV;
    UCHAR   ucEndTLV;           /*End TLV*/
}OAM_1AG_VRPLBPACKET_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif


/*LBR缓存队列中的节点数据结构定义*/
typedef struct tagLbrQUE_Node
{
    DLL_NODE_S node;         /*链表节点*/    
    ULONG   ulLbrRecvtime;   /*接收LBR报文时间*/
    MBUF_S  *pstLbrpacket;   /*LBR报文*/
    ULONG   ulLbrSequence;   /*LBR报文序号*/
}LBRQUE_NODE_S;

/*LB 发起过程传给LB测试过程的测试参数，如发送报文个数*/
typedef struct tagMacPingParam
{
    UCHAR   ucDestMacAddr[OAM_1AG_MACADDR_LEN];     /*目标地址*/
    UCHAR   ucSrcMacAddr[OAM_1AG_MACADDR_LEN];      /* 源地址 */
    ULONG   ulIfIndex;                              /*出接口*/
    ULONG   ulPackets;                              /*发送次数*/
    ULONG   ulPacketSize;                           /*报文大小，不包括以太头*/
    ULONG   ulTimeout;                              /*超时时间*/
    ULONG   ulPeriod;                               /*发送间隔*/
    ULONG   ulMaIndex;                              /*MA索引*/
    ULONG   ulLocalMepIndex;                        /* 本地维护点索引*/
    USHORT  usRmepId;                               /* RMEP ID */
    UCHAR   ucVlanPri;                              /* 发送1AG Ping报文的VLAN优先级,取值范围[0,7]以及0xFF.
                                                       0xFF表示按照协议栈默认规则填写VLAN优先级,如果该MA设置了VLAN优先级
                                                       则使用该MA的VLAN优先级,否则使用全局VLAN优先级. */
    UCHAR   ucReserve;                              /* pad */
    /*--------------------------------------------------------------------*\
    |*   统计用信息                                                       *|
    \*--------------------------------------------------------------------*/
    ULONG     ulTransmitted;                       /*已发送次数*/
    ULONG     ulReceived;                          /*已接收次数*/
    ULONG     ulTmin;                              /*最小往返时间*/
    ULONG     ulTmax;                              /*最大往返时间*/
    ULONG     ulTsum;                              /*总的往返时间*/
}MACPINGPARAM_S;

/* LB 序号链表 */
typedef struct tagOAM_1AG_LBSEQ_NODE
{
    DLL_NODE_S    node;           /* 链表节点 */
    ULONG       ulSequence;       /* 序号 */
}OAM_1AG_LBSEQ_NODE_S;

/* NP消息 */
typedef struct tagOAM_1AG_NPNOTIFYPARA
{
    ULONG ulIfIndex;                            /*接口索引*/
    UCHAR szMdName[OAM_1AG_MAX_MDNAME_LEN + 1]; /*MD名称*/
    UCHAR szMaName[OAM_1AG_MAX_MANAME_LEN + 1]; /*MA名称*/
    USHORT usRmepId;                             /*MEPID值*/
    UCHAR ucRes[2];
    ULONG ulType;                               /*告警类型*/
}OAM_1AG_NPNOTIFYPARA_S;

/*---------------------------------------------------------------------------------
--------------------------------结构体类型定义End---------------------------------*/
/*-------------------------------枚举类型定义Begin------------------------------
---------------------------------------------------------------------------------*/
enum eOAM1AGTYPE
{
    OAM1AG_CCM = 1,/*ccm报文*/
    OAM1AG_LBR = 2,/*LBR报文*/
    OAM1AG_LBM = 3,/*LBM报文*/
    OAM1AG_LTR = 4,/*LTR报文*/
    OAM1AG_LTM = 5, /*LTM报文*/
    OAM1AG_AIS =  33  /*AIS报文*/
};

/* 目的physical地址的类型 */
enum e1AGMacAddrtype
{
    OAM_1AG_MULTICAST,
    OAM_1AG_UNICAST,
    OAM_1AG_ZERO,
    OAM_1AG_NULLPARA,
    OAM_1AG_BROADCAST
};

/* VISP支持的运行模式 */
enum e1AGNpMode
{
    OAM_1AG_NONP,   /*软件模式*/
    OAM_1AG_HALFNP, /*半NP模式*/
    OAM_1AG_FULLNP, /*全NP模式*/
};

/* MD名字格式 */
enum eMDNAMETYPE
{
    OAM_1AG_MDNAMETYPE_NO_MD_NAME_PRESENT = 1,      /* No Maintenance Domain Name present */
    OAM_1AG_MDNAMETYPE_STRING = 2,                  /* Domain Name based string */
    OAM_1AG_MDNAMETYPE_MACADDR_ADD_2BYTEINT = 3,    /* physical address + 2-octet integer */
    OAM_1AG_MDNAMETYPE_CHARACTER_STRING = 4,        /* Character string ,目前MD名字只支持这种格式*/
    OAM_1AG_MDNAMETYPE_MAX
};

/* MA名字格式 */
enum eMANAMETYPE
{
    OAM_1AG_MANAMETYPE_PRIMARY_VID = 1,         /* Primary VID */
    OAM_1AG_MANAMETYPE_CHARACTER_STRING = 2,    /* Character string,目前MA名字只支持这种格式 */
    OAM_1AG_MANAMETYPE_2OCTET_INTEGER = 3,      /* 2-octet integer */
    OAM_1AG_MANAMETYPE_RFC2685_VPN_ID = 4,      /* RFC 2685 VPN ID */
    OAM_1AG_MANAMETYPE_MAX
};

/* Mep超时发送CCM值 */
enum eMEPOUTTIME
{
    /*OAM_1AG_CCINTERVAL_100ms的通过(ulInterval / 20)计算得到.因为MEP是20ms遍历一次，所以要除以20*/
    /*OAM_1AG_CCINTERVAL_1s的通过(ulInterval / 20) / 10 计算得到.因为MEP是10次才递减，所以要除以10*/
    /*OAM_1AG_CCINTERVAL_10s以上的通过(ulInterval / 20) / 100 计算得到.因为MEP是100次才递减，所以要除以100*/
    OAM_1AG_10SSNDTIMEOUT   = 5, 
    OAM_1AG_1MINSNDTIMEOUT  = 30,
    OAM_1AG_10MINSNDTIMEOUT = 300
};

/*Rmep超时检测值*/
enum eRMEPOUTTIME
{
    /* OAM_1AG_CCINTERVAL_3ms和OAM_1AG_CCINTERVAL_10ms的检测间隔VISP不支持RMEP探测,所以以前没有处理这两种间隔的超时时间
       设置值,并一直为0，但是在NP模式下VISP是会维护这两种探测间隔的RMEP项的，所以就会造成RMEP显示信息不准，这两种间隔的
       RMEP项无论是否超时都显示为超时.在全NP模式下VISP是不会启动RMEP检测定时器的,所以为了全NP模式下也能正确显示,将这两种
       间隔的RMEP的超时设置值设定为一个非0值1.*/
    OAM_1AG_3MS_10MSTIMEOUT = 1,
    /*OAM_1AG_CCINTERVAL_100ms的通过(ulInterval / 50) * 3.5 计算得到*/
    /*OAM_1AG_CCINTERVAL_1s的通过((ulInterval / 50) / 10) * 3.5 计算得到.*/
    /*OAM_1AG_CCINTERVAL_10s以上的通过((ulInterval / 50) / 100) * 3.5 计算得到.*/
    OAM_1AG_10STIMEOUT   = 7,
    OAM_1AG_1MINTIMEOUT  = 42,
    OAM_1AG_10MINTIMEOUT = 420
};

/* Mep超时发送CCM值 */
enum eAISOUTTIME
{
    /* 定时器周期为500ms */
    OAM_Y1731_1STIMEOUT   = 7, 
    OAM_Y1731_1MINTIMEOUT  = 42
};

/* TLV 类型 */
enum e1AGTLVType
{
    OAM_1AG_END_TLV                     = 0,    /* End TLV */
    OAM_1AG_SENDER_ID_TLV               = 1,    /* Sender ID TLV */
    OAM_1AG_PORT_STATUS_TLV             = 2,    /* Port Status TLV */
    OAM_1AG_INTERFACE_STATUS_TLV_DRAFT7 = 3,    /* Interface Status TLV */
    OAM_1AG_DATA_TLV_DRAFT7             = 4,    /* Data TLV */
    OAM_1AG_REPLY_INGRESS_TLV           = 5,    /* Reply Ingress TLV */
    OAM_1AG_REPLY_EGRESS_TLV            = 6,    /* Reply Egress TLV */    
    OAM_1AG_ORGANIZATION_SPECIFIC_TLV   = 31    /* Organization-Specific TLV */
};

/* 标准协议TLV 类型 */
enum e1AGTLVSTDType
{    
    OAM_1AG_DATA_TLV_STD                = 3,    /* Data TLV */
    OAM_1AG_INTERFACE_STATUS_TLV_STD    = 4,    /* Interface Status TLV */
    OAM_1AG_LTM_EGRESS_TLV              = 7,    /* Reply Egress TLV */
    OAM_1AG_LTR_EGRESS_TLV              = 8,    /* Reply Egress TLV */
};


/* Ingress TLV ACTION */
enum eOAM1AG_INGRESS_TLV_ACTION
{
    OAM_1AG_INGRESS_OK = 1,     /* The target data frame would be passed through to the MAC Relay
                                    Entity. */
    OAM_1AG_INGRESS_DOWN = 2,   /* The Bridge Port’s MAC_Operational parameter is false. */
    OAM_1AG_INGRESS_BLOCKED = 3,/* The target data frame would not be forwarded if received on this
                                    Port due to active topology enforcement */
    OAM_1AG_INGRESS_VID = 4,    /* The ingress port is not in the member set of the LTM’s VID, and
                                    ingress filtering is enabled, so the target data frame would be filtered
                                    by ingress filtering */
    OAM_1AG_INGRESS_MAX
};

/* Egress TLV ACTION */
enum eOAM1AG_EGRESS_TLV_ACTION
{
    OAM_1AG_EGRESS_OK = 1,      /* The targeted data frame would be forwarded. */
    OAM_1AG_EGRESS_DOWN = 2,    /* The Egress Port can be identified, but that
                                    Bridge Port’s MAC_Operational parameter is false. */
    OAM_1AG_EGRESS_BLOCKED = 3, /* The Egress Port can be identified, but the data
                                    frame would not pass through the Egress Port
                                    due to active topology management (8.6.1), i.e.
                                    the Bridge Port is not in the Forwarding state. */
    OAM_1AG_EGRESS_VID = 4,     /* The Egress Port can be identified, but the
                                    Bridge Port is not in the LTM’s VID’s member
                                    set, so would be filtered by egress filtering */
    OAM_1AG_EGRESS_MAX
};

/* LTR Reply Action */
enum eOAM1AG_LTR_REPLY_ACTION
{
    OAM_1AG_RLY_HIT = 1,    /* The LTM reached an MP whose physical address matches the target physical address. */
    OAM_1AG_RLY_FDB = 2,    /* The Egress Port was determined by consulting the Filtering Database */
    OAM_1AG_RLY_MPDB = 3,   /* The Egress Port was determined by consulting the MIP CCM Database */
    OAM_1AG_RLY_MAX
};


/*-------------------------------枚举类型定义end------------------------------
---------------------------------------------------------------------------------*/
#ifdef __cplusplus
    }
#endif  /* end of __cplusplus */

#endif

