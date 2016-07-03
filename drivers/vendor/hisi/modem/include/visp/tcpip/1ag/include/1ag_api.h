/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              1ag_api.h
*
*  Project Code: VISPV100R007
*   Module Name: 1AG
*  Date Created: 2008-3-3
*        Author: yebo(62007)
*   Description: 1AG模块API
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-3-3  yebo(62007)         Create the first version.
*
*******************************************************************************/
#ifndef _1AG_API_H
#define _1AG_API_H

#ifdef  __cplusplus
    extern "C"{
#endif

/* 1AG 错误码类型 */
enum eOAM1AGERRCODE
{
    OAM1AG_OK,                      /*0功能正常*/
    OAM1AG_ERR,                     /*1功能错误,用于内部函数返回值*/
    OAM1AG_ERR_PARAWRONG,           /*2参数有效性错误*/
    OAM1AG_ERR_PARANULL,            /*3输入参数为空*/
    OAM1AG_ERR_MDNAMELEN,           /*4MD名字长度错误*/
    OAM1AG_ERR_MANAMELEN,           /*5MA名字长度错误*/
    OAM1AG_ERR_MDMANAMELEN,         /*6MDMA名字长度错误*/
    OAM1AG_ERR_IFNULL,              /*7接口不存在*/
    OAM1AG_ERR_IFINVALID,           /*8接口类型错误*/
    OAM1AG_ERR_MDALREADYEXIST,      /*9MD已存在*/
    OAM1AG_ERR_MDNOTEXIST,          /*10MD不存在*/
    OAM1AG_ERR_MAALREADYEXIST,      /*11MA已存在*/
    OAM1AG_ERR_MANOTEXIST,          /*12MA不存在*/
    OAM1AG_ERR_PORTHASMEP,          /*13接口MA下已存在MEP*/
    OAM1AG_ERR_MEPNOTEXIST,         /*14接口MA下不存在MEP*/
    OAM1AG_ERR_REMOTEHASMEP,        /*15远端MA下已配置过该MEPID*/
    OAM1AG_ERR_PORTHASNOMP,         /*16接口上没有维护点*/
    OAM1AG_ERR_EQUALTOPORTMEP,      /*17配置的RMEPID与本接口上MEP相同*/
    OAM1AG_ERR_NOTENOUGHMEMORY,     /*18内存空间不足*/
    OAM1AG_ERR_OVERMDMAXNUM,        /*19MD已满规格*/
    OAM1AG_ERR_OVERMAMAXNUM,        /*20MA已满规格*/
    OAM1AG_ERR_OVERMEPMAXNUM,       /*21MEP已满规格*/
    OAM1AG_ERR_OVERRMEPMAXNUM,      /*22RMEP已满规格*/
    OAM1AG_ERR_HAISSMOOTHING,       /*23正处于平滑或倒换*/
    OAM1AG_ERR_RMEPALREADYEXIST,    /*24RMEP已存在*/
    OAM1AG_ERR_MEPHASSENDCCM,       /*25已经使能了CCM发送*/
    OAM1AG_ERR_VLANIDALREADYEXIST,  /*26VLANID已经存在*/
    OAM1AG_ERR_INTERVALNEEDNP,      /*27发送间隔需NP支持*/
    OAM1AG_ERR_RMEPNOTEXIST,        /*28RMEP 不存在*/
    OAM1AG_ERR_CCMALREADYENABLE,    /*29CCM的发送间隔已配置*/
    OAM1AG_ERR_SENDCCM,             /*30发送CCM报文失败*/
    OAM1AG_ERR_LTSELFMAC,           /*31链路追踪测试的目的physical地址等于本地physical地址 */
    OAM1AG_ERR_SENDLTM,             /*32发送LTM报文失败*/
    OAM1AG_ERR_PACKETSIZE,          /*33LB报文长度错误*/
    OAM1AG_ERR_LBTIMEOUT,           /*34LB超时时间错误*/
    OAM1AG_ERR_LBINTERVAL,          /*35LB发送间隔错误*/
    OAM1AG_ERR_MACADDR,             /*36用户physical地址错误*/
    OAM1AG_ERR_RMEPHAVENOMAC,       /*37RMEP 表项没有physical地址*/
    OAM1AG_ERR_OVERMAXPING,         /*38已经有16个ping任务*/
    OAM1AG_ERR_USERENCAPSULATE,     /*39封装自定义报文失败 */
    OAM1AG_ERR_MAHASMEP,            /*40MA下已有相同的MEP*/
    OAM1AG_ERR_OVERMAXLT,           /*41同时发起的LT超过上限*/
    OAM1AG_ERR_MODULENOTEXIST,      /*42组件未注册*/
    OAM1AG_ERR_NORECV,              /*43未收到一个lbr报文 */
    OAM1AG_ERR_RECVPART,            /*44收到的lbr数小于发送的lbm报文数 */
    OAM1AG_ERR_LBSELFMAC,           /*45环回测试的目的地址等于出接口的physical地址 */
    OAM1AG_ERR_CCMINTERVAL,         /*46CCM发送间隔错误 */
    OAM1AG_ERR_MEPIDWRONG,          /*47MEPID超出范围 */
    OAM1AG_ERR_DISABLECCMFAILED,    /*48去使能CCM发送失败(删除MEP时)*/
    OAM1AG_ERR_DELETEALLMEPFAILED,  /*49删除MA下的所有MEP失败*/
    OAM1AG_ERR_DELETEALLRMEPFAILED, /*50删除MA下的所有RMEP失败(当删除该MA下的最后一个MEP时)*/
    OAM1AG_ERR_GETMACADDR,          /*51获取出接口的physical地址失败 */
    OAM1AG_ERR_CREATEMBUF,          /*52创建mbuf失败 */
    OAM1AG_ERR_USERHOOKNOTREG,      /*53用户自定义处理函数没有注册 */
    OAM1AG_ERR_TRANSMITFAIL,        /*54没有一个lbm报文被发送 */
    OAM1AG_ERR_NOTRECEIVEEXPECTLTR, /*55没有收到从目的MP返回的LTR */
    OAM1AG_ERR_SENDUNCOMPLETE,      /*56因为某种原因中断，发送未完全 */
    OAM1AG_ERR_SETMAVLANPRIORITY,   /*57设置基于MA的VLAN优先级超出范围 */
    OAM1AG_ERR_NOTINFULLNPMODE,     /*58不处于全NP模式 */
    OAM1AG_ERR_VLANPRIINVALID,      /*59指定的VLAN优先级不合法 */
    OAM1AG_ERR_NOTENOUGHMEMORY_DOT1 = 60,/* 60 内存空间不足，错误码唯一性整改*/
    OAM1AG_ERR_MACADDR_NOTUNICAST,  /* 61 非单播physical地址*/
    OAM1AG_ERR_GET_ETHCTLBLOCK,     /* 62 获取不到以太控制块 */
    OAM1AG_ERR_INTER_FAIL,          /* 63 发送报文的钩子函数返回失败 */
    OAM1AG_ERR_MBUF_PREPEND,        /* 64 MBUF扩充头操作失败 */
    OAM1AG_ERR_MBUF_CONTINUE,       /* 65 使得MBUF内存连续的操作失败 */
    OAM1AG_ERR_UNREG_ENCAP,         /* 66 无法识别和支持的以太封装类型 */
    OAM1AG_ERR_SLAVE_BOARD,         /* 67 本板是备板，不作处理 */
    OAM1AG_ERR_TTL_INVALID,         /* 68 TTL值不合法 */
    OAM1AG_ERR_TIMEOUT_INVALID,     /* 69 Time out值不合法 */
    OAM1AG_ERR_NOT_STATICRMEP,      /* 70 非静态RMEP*/  
    OAM1AG_ERR_RMEPISDOWNLOADNP,    /* 71 RMEP已经下发过NP */
    OAM1AG_ERR_TRUNKPORT_TOOMANYMEP,/* 72 在Trunk成员端口上配置MEP，则该MEP所在的MA只支持配置一个MEP */
    OAM1AG_ERR_TRUNKPORT_MDLEVEL,   /* 73 Trunk 口上的 MDLevel 应该比 TrunkPort 高 */
    OAM1AG_ERR_TRUNKPORT_CCMINTERVAL,   /* 74 Trunk 上的 CCM 探测周期应该是 TrunkPort 上的三倍以上 */
    OAM1AG_ERR_MA_BIND_VLAN,        /* 75 在Trunk成员端口上创建MEP，其关联的MA不能绑定VLAN */
    OAM1AG_ERR_MA_NOT_BIND_VLAN,    /* 76 在Trunk或Eth上创建MEP，其关联的MA必须绑定VLAN */
    OAM1AG_ERR_NOT_1731_MODE,       /* 77 非1731版本 */
    OAM1AG_ERR_VLANID_MEGLEVEL_EXIST,  /* 78 VLANID+MegLevel已经存在 */
    OAM1AG_ERR_GET_PMPOLICY,        /* 79 获取监视策略失败 */
    OAM1AG_ERR_NOTSUPPORT_1731_MODE,/* 80 不支持Y1731版本 */
    OAM1AG_ERR_RMEPIDWRONG,         /* 81 RMEPID超出范围 */
    OAM1AG_ERR_PARAOVERFLOW,        /* 82 参数输入超出范围 */
    OAM1AG_ERR_NOTENABLECCMSEND,    /* 83 未使能CCM */
    OAM1AG_ERR_ALREADYENABLE,       /* 84 该MEP/RMEP已使能性能检测,不能修改参数 */
    OAM1AG_ERR_ALREADYENABLEMEP,    /* 85 该MEP已使能该项性能检测 */
    OAM1AG_ERR_ALREADYENABLERMEP,   /* 86 该RMEP已使能该项性能检测 */
    OAM1AG_ERR_NOTSTATICRMEP,       /* 87 非静态RMEP */
    OAM1AG_REPEATSET,               /* 88 重复设置 */
    OAM1AG_ERR_MEPNULL,             /* 89 获取MEP INFO失败 */
    OAM1AG_ERR_RMEPNULL,            /* 90 获取RMEP INFO失败 */
    OAM1AG_ERR_CC_DETECT_MODE,      /* 91 错误的REMP 探测模式*/
    OAM1AG_ERR_NOTINNONPMODE,       /* 92 不处于非NP(软件)模式 */
    OAM1AG_ERR_MAXCODE              /*最大错误码,添加新错误码时,添加到本错误码之前*/
};


#define OAM_1AG_NOTBINDVLAN 0xFFFF

/*physical地址长度*/
#define OAM_1AG_MACADDR_LEN 6

/*1AG MD最大名字长度*/
#ifndef OAM_1AG_MAX_MDNAME_LEN
#define OAM_1AG_MAX_MDNAME_LEN 43
#endif

/*1AG MA最大名字长度*/
#ifndef OAM_1AG_MAX_MANAME_LEN
#define OAM_1AG_MAX_MANAME_LEN 43
#endif

/*Y1731 MA最大名字长度*/
#ifndef OAM_Y1731_MAX_MANAME_LEN
#define OAM_Y1731_MAX_MANAME_LEN 13
#endif

typedef enum enumTcpipOAM1AGWarning
{
    OAM_1AG_NOTIFYCCPERIOD = 0,       /*np通告CC超时*/
    OAM_1AG_NOTIFYCCAGING,            /*NP通告CC老化*/     
    OAM_1AG_NOTIFYCCRECOVER,          /*NP通知告警恢复*/   
    OAM_Y1731_NOTIFYLEVELERROR,       /*NP通知非期望的MEG level*/   
    OAM_Y1731_NOTIFYLEVELRECOVER,     /*NP通知非期望的MEG level告警恢复*/
    OAM_Y1731_NOTIFYMEGIDERROR,       /*NP通知非期望的MEG ID*/
    OAM_Y1731_NOTIFYMEGIDRECOVER,     /*NP通知非期望的MEG ID告警恢复*/
    OAM_Y1731_NOTIFYMEPIDERROR,       /*NP通知非期望的MEP ID*/
    OAM_Y1731_NOTIFYMEPIDRECOVER,     /*NP通知非期望的MEP ID告警恢复*/
    OAM_Y1731_NOTIFYINTERVALERROR,    /*NP通知非期望的传输周期*/
    OAM_Y1731_NOTIFYINTERVALRECOVER,  /*NP通知非期望的传输周期告警恢复*/

    OAM_WARNING_NOTIFY_MAX,
}TCPIP_OAM_1AG_WARNING_E;

/*1AG告警开始、结束*/
#define OAM_1AG_WARNING_BEGIN 1
#define OAM_1AG_WARNING_END 0

/* 去使能CCM发送 */
#define OAM_1AG_CCMSEND_DISABLE   0
/* 使能CCM发送 */
#define OAM_1AG_CCMSEND_ENABLE   1

/* MP的两种类型MEP、RMEP */
#define OAM_1AG_MEPTYPE  0
#define OAM_1AG_RMEPTYPE 1

/*RMEP的状态*/
#define OAM_1AG_DYNAMICRMEP 0    /* 动态RMEP */
#define OAM_1AG_STATICRMEP  1    /* 静态RMEP */

/* 1AG Draft7版本*/
#define OAM_1AG_VERSION_DRAFT7    0
/* 1AG标准版本*/
#define OAM_1AG_VERSION_STD       1
/* 1AG Y.1731版本*/
#define OAM_1AG_VERSION_Y1731     2

/* 主动发送报文时是否需要带VLAN头标志,包括发送CCM,LBM,LTM报文.但是不包括回复的LBR和LTR报文 */
/* 主动发送报文时需要带VLAN头 */
#define OAM_1AG_SEND_WITH_VLAN  1
/* 主动发送报文时不需要带VLAN头 */
#define OAM_1AG_SEND_WITHOUT_VLAN  0

/* RMEP的MD Level相对本端MEP的MD Level的比较情况 */
#define OAM_1AG_EQLEVEL   0      /* RMEP的MD Level跟本端MEP的MD Level相等 */
#define OAM_1AG_GTLEVEL   1      /* RMEP的MD Level大于本端MEP的MD Level */
/* 去使能性能检测(Y1731) */
#define Y1731_PMCHECK_DISABLE   0
/* 使能性能检测(Y1731) */
#define Y1731_PMCHECK_ENABLE   1
/* 去使能AIS 功能*/
#define Y1731_AIS_DISABLE   0
/*使能AIS 功能*/
#define Y1731_AIS_ENABLE   1


/* 1AG Ping(即LB测试)参数结构 */
typedef struct tagTCPIP_1AG_PING
{
    ULONG   ulUserID;       /* 用户ID */
    UCHAR   szMDName[OAM_1AG_MAX_MDNAME_LEN + 1]; /*MD名字,最长为43字节*/
    UCHAR   szMaName[OAM_1AG_MAX_MANAME_LEN + 1]; /*MA名字,最长为43字节*/
    UCHAR  *pucMacAddr;     /* 1AG Mac Ping使用的目的physical地址.指向"XX-XX-XX-XX-XX-XX"形式physical地址的指针,
                               如果为NULL则根据RMEP Ping,否则根据指定的physical地址和接口索引Ping */
    ULONG   ulIfIndex;      /* iAG MAC Ping使用的接口索引 */    
    USHORT  usRmepId;       /* 1AG RMEP Ping使用的RMEP ID */
    USHORT  usTimeOut;      /* 1AG Ping超时时间.如果用户未指定(值为0),则使用默认值2s */
    ULONG   ulInterval;     /* 发送1AG Ping报文的间隔.取值范围[0s,60s] */
    ULONG   ulCount;        /* 发送1AG Ping报文的次数.如果用户未指定(值为0),则使用默认值5次 */
    USHORT  usPacketSize;   /* 发送1AG Ping报文的大小.如果用户未指定(值为0),则使用默认值128字节,取值范围[95,1500] */
    UCHAR   ucVlanPri;      /* 发送1AG Ping报文的VLAN优先级,取值范围[0,7]以及0xFF.
                               0xFF表示按照协议栈默认规则填写VLAN优先级,如果该MA设置了VLAN优先级则
                               使用该MA的VLAN优先级,否则使用全局VLAN优先级. */
    UCHAR   ucReserve;      /* 保留字段未使用 */
}TCPIP_1AG_PING_S;

/* 1AG User Ping(即用户自定义LB测试)参数结构 */
typedef struct tagTCPIP_1AG_USERPING
{
    UCHAR   szMDName[OAM_1AG_MAX_MDNAME_LEN + 1]; /*MD名字,最长为43字节*/
    UCHAR   szMaName[OAM_1AG_MAX_MANAME_LEN + 1]; /*MA名字,最长为43字节*/
    UCHAR  *pucMacAddr;     /* 1AG Mac User Ping使用的目的physical地址.指向"XX-XX-XX-XX-XX-XX"形式physical地址的指针,
                               如果为NULL则根据RMEP Ping,否则根据指定的physical地址和接口索引Ping */
    ULONG   ulIfIndex;      /* iAG MAC User Ping使用的接口索引 */    
    USHORT  usRmepId;       /* 1AG RMEP User Ping使用的RMEP ID */
    UCHAR   ucVlanPri;      /* 发送1AG User Ping报文的VLAN优先级,取值范围[0,7]以及0xFF.
                               0xFF表示按照协议栈默认规则填写VLAN优先级,如果该MA设置了VLAN优先级则
                               使用该MA的VLAN优先级,否则使用全局VLAN优先级. */
    UCHAR   ucReserve;      /* 保留字段未使用 */
    UCHAR  *pBuffer;        /* 填入1AG User Ping报文中DATA TLV的Value字段值,要求数据在[40,1460]字节之内 */
    ULONG   ulLen;          /* pBuffer中数据长度,取值范围[40,1460]字节 */
}TCPIP_1AG_USERPING_S;

/* 收到一个不带VLAN的LB和LT报文时,入接口存在多个不带VLAN的MEP信息时,回调通知信息结构 */
typedef struct tagTCPIP_1AG_NOVLANINFO_S
{
    UCHAR  szMacAddr[OAM_1AG_MACADDR_LEN];       /* 报文中的源physical地址 */
    USHORT usMepId;                              /* MEP ID */
    UCHAR  szMaName[OAM_1AG_MAX_MANAME_LEN + 1]; /* MA名字,最大长度为43 */
    UCHAR  szMdName[OAM_1AG_MAX_MDNAME_LEN + 1]; /* MD名字,最长为43字节 */
    USHORT usVlanId;                             /* MA关联的VLAN ID值 */    
    UCHAR  ucMdLevel;                            /* MD级别 */
    UCHAR  ucReserve;                            /* 保留字段未使用 */
} TCPIP_1AG_NOVLANINFO_S;

/*显示MD信息*/
typedef struct tagDISP_MD_INFO
{
    UCHAR ucLevel;          /* 维护域级别*/
    UCHAR ucMDNameType;     /*维护域名字类型，目前只支持字符串类型*/
    UCHAR ucRes[2];
} DISP_MD_INFO_S;

/*显示MA信息*/
typedef struct tagDISP_MA_INFO
{
    ULONG ulVLanID;     /* VLan ID */
    UCHAR ucMDLevel;    /* 维护域级别 */
    UCHAR ucInterval;   /* CCM发送间隔 */
    UCHAR ucPriority;   /* 1ag 报文优先级 */
    UCHAR ucCompatible; /* 兼容模式 */
    UCHAR ucRdiFlag;    /* MA内RDI标记,同时也是RDI告警是否消失的标记*/
    UCHAR ucAisEnable;   /* AIS使能开关*/ 
    UCHAR ucAisWarningFlag;       /* AIS告警标识*/
    UCHAR ucAisInterval;  /*AIS传输周期*/
} DISP_MA_INFO_S;

typedef struct tagMEP_PMINFO
{
    USHORT usRmepId;                         /* RMEP ID */
    USHORT usEnableFlag;                     /* 使能标记 */
    ULONG  ulInterval;                       /*发送周期*/
    ULONG  ulTimeOut;                        /*超时时间*/
}MEP_PM_INFO_S;

/*显示MEP信息*/
typedef struct tagDISP_MEP_INFO
{
    ULONG  ulOutIfIndex;                    /* 出接口即收到CCM报文的接口 */
    USHORT usMepId;                         /* MEP ID */
    UCHAR  szMacAddr[OAM_1AG_MACADDR_LEN];  /* RMEP physical地址 */
    UCHAR  ucMepType;                       /* 静态或者动态RMEP标记 */
    UCHAR  ucMepLocation;                   /* MEP位置,本端或者远端 */
    UCHAR  ucSendFlag;                      /* CCM发送标志 */
    UCHAR  uc1agVersion;                    /* MEP 使用的1AG版本,0:Draft7版本;1:标准版本;2:Y1731版本 */
    UCHAR  ucVlanFlag;                      /* 该MEP下发送的报文是否带VLAN头标志.
                                               0:表示不需要带VLAN头,1表示需要带VLAN*/
    UCHAR  ucRes[3];
                                               
    MEP_PM_INFO_S stPMCheckDLM;
    MEP_PM_INFO_S stPMCheckSLM;
    MEP_PM_INFO_S stPMCheckDDM;                   
} DISP_MEP_INFO_S;

/*根据ID获取所有ID相同的MEP和RMEP显示信息*/
typedef struct tagDISP_MEP_INFO_LIST
{
    struct tagDISP_MEP_INFO_LIST *pstNext;  /* 下一个显示节点 */
    ULONG  ulOutIfIndex;                    /* 出接口即收到CCM报文的接口 */
    USHORT usMepId;                         /* MEP ID */
    UCHAR  szMacAddr[OAM_1AG_MACADDR_LEN];  /* RMEP physical地址 */
    UCHAR  ucMepType;                       /* 静态或者动态RMEP标记 */
    UCHAR  ucMepLocation;                   /* MEP位置,本端或者远端 */
    UCHAR  ucSendFlag;                      /* CCM发送标志 */
    UCHAR  uc1agVersion;                    /* MEP 使用的1AG版本,0:Draft7版本;1:标准版本;2:Y1731版本 */
    UCHAR  ucVlanFlag;                      /* 该MEP下发送的报文是否带VLAN头标志.
                                               0:表示不需要带VLAN头,1表示需要带VLAN*/
    UCHAR  ucRes[3];

    MEP_PM_INFO_S stPMCheckDLM;
    MEP_PM_INFO_S stPMCheckSLM;
    MEP_PM_INFO_S stPMCheckDDM; 
} DISP_MEP_INFO_LIST_S;

/*OAM 1AG 报文统计结构体 */
typedef struct tagOAM_1AG_STAT
{
    ULONG ulSndPkt;         /*发送总报文数*/
    ULONG ulSndDropPkt;     /*发送丢弃报文数*/
    ULONG ulRcvPkt;         /*接收报文数*/
    ULONG ulRcvDropPkt;     /*接收丢弃报文数*/
    ULONG ulFwdPkt;         /*转发报文数*/
    ULONG ulFwdDropPkt;     /*转发丢弃的报文数*/
    ULONG ulUpPkt;          /*上送的报文数(针对TrunkPort)*/

    /*统计CCM*/
    ULONG ulSndCcmPkt;     /*发送CCM报文数*/
    ULONG ulRcvCcmPkt;     /*接收CCM报文数*/
    ULONG ulFwdCcmPkt;     /*转发CCM报文数*/
    ULONG ulUpCcmPkt;      /*上送CCM报文数(针对TrunkPort)*/

    /*统计LBM*/
    ULONG ulSndLbmPkt;     /*发送LBM报文数*/
    ULONG ulRcvLbmPkt;     /*接收LBM报文数*/
    ULONG ulFwdLbmPkt;     /*转发LBM报文数*/
    ULONG ulUpLbmPkt;      /*上送LBM报文数(针对TrunkPort)*/
    
    /*统计LBR*/
    ULONG ulSndLbrPkt;     /*发送LBR报文数*/
    ULONG ulRcvLbrPkt;     /*接收LBR报文数*/
    ULONG ulFwdLbrPkt;     /*转发LBR报文数*/
    ULONG ulUpLbrPkt;      /*上送LBR报文数(针对TrunkPort)*/

    /*统计LTM*/
    ULONG ulSndLtmPkt;     /*发送LTM报文数*/
    ULONG ulRcvLtmPkt;     /*接收LTM报文数*/
    ULONG ulFwdLtmPkt;     /*转发LTM报文数*/
    ULONG ulUpLtmPkt;      /*上送LTM报文数(针对TrunkPort)*/

    /*统计LTR*/
    ULONG ulSndLtrPkt;     /*发送LTR报文数*/
    ULONG ulRcvLtrPkt;     /*接收LTR报文数*/
    ULONG ulFwdLtrPkt;     /*转发LTR报文数*/
    ULONG ulUpLtrPkt;      /*上送LTR报文数(针对TrunkPort)*/

    /*统计VLAN头标志的切换次数*/
    ULONG ulVlanChangeCount;
    ULONG ulCCMLostPkt;

    ULONG ulRcvMutiLbmPkt; /*接收组播LBM报文数*/ 
    ULONG ulRcvUniLbmPkt;  /*接收单播LBM报文数*/  

    /*统计AIS报文*/
    ULONG ulSndAisPkt;    /*发送AIS报文数*/
    ULONG ulRcvAisPkt;   /*接收AIS报文数*/
    ULONG ulFwdAisPkt; /*转发AIS报文数*/    
    ULONG ulUpAisPkt;   /*上送AIS报文数(针对TrunkPort)*/
    
} OAM_1AG_STAT_S;

/*HA 统计信息 */
typedef struct tagHA1AGSTAT
{
    ULONG ulOutPackets;       /* 主板发送成功备份消息包个数 */
    ULONG ulOutDropPackets;   /* 主板发送失败备份消息包个数 */
    ULONG ulInPackets;        /* 备板接收并处理成功备份消息包个数 */
    ULONG ulInDropPackets;    /* 备板接收、处理失败备份消息包个数 */
} HA1AGSTAT_S;

/* 1AG发送间隔 */
enum eCCMINTERVALVALUE
{
    OAM_1AG_CCSEND_3ms   = 3,
    OAM_1AG_CCSEND_10ms  = 10,
    OAM_1AG_CCSEND_100ms = 100,
    OAM_1AG_CCSEND_1s    = 1000,
    OAM_1AG_CCSEND_10s   = 10 * 1000,
    OAM_1AG_CCSEND_1min  = 60 * 1000,
    OAM_1AG_CCSEND_10min = 600 * 1000
};

/* VISP下发给NP的对RMEP进行CC检测的时间间隔值 */
enum eCCMINTERVAL
{
    OAM_1AG_CCINTERVAL_3ms   = 1,
    OAM_1AG_CCINTERVAL_10ms  = 2,
    OAM_1AG_CCINTERVAL_100ms = 3,
    OAM_1AG_CCINTERVAL_1s    = 4,
    OAM_1AG_CCINTERVAL_10s   = 5,
    OAM_1AG_CCINTERVAL_1min  = 6,
    OAM_1AG_CCINTERVAL_10min = 7
};

/* AIS 报文 */
enum eAISINTERVAL
{
    OAM_Y1731_AISINTERVAL_1s   = 4,
    OAM_Y1731_AISINTERVAL_1min  = 6
};

/* 1AG调试开关类型 */
enum eDEBUGTYPE
{
    OAM1AG_DEBUG_NORMAL = 0,        /* 正常开关 */
    OAM1AG_DEBUG_EXCEPTION = 1,     /* 异常开关 */
    OAM1AG_DEBUG_VERBOSE = 2        /*  VERBOSE开关*/
};

/* Y1731性能检测可设置的类型 */
typedef enum enumTcpipY1731PMType
{
    Y1731_PM_DLM = 0,       /* 双端帧丢失检测 */
    Y1731_PM_SLM,           /* 单端帧丢失检测 */
    Y1731_PM_DDM,           /* 双向时延检测 */
    Y1731_PM_TYPE_MAX       /* 性能检测类型的边界值 */              
}TCPIP_Y1731_PM_TYPE_E;

/* 1AG对外告警状态*/
typedef struct tagOAM_1AG_WARNSTATE                   
{                                                     
    ULONG ulCcLosWarn;           /* Rmep CcLos告警    */
    ULONG ulIntfDownWarn;        /* InterfaceDown告警 */
    ULONG ulRDIWarn;             /* RDI告警           */
}OAM1AG_WARN_STATE_S;                                 

/*注册函数类型*/
/*1AG LT、LB打印信息输出钩子*/
typedef VOID (*OAM_1AG_OUTINFO_HOOK_FUNC)(UCHAR *szBuf, ULONG ulID);

/*注册Ping stop钩子函数*/
typedef ULONG (*OAM_1AG_STOP_HOOK_FUNC)(ULONG ulID);

/*注册自定义Ping报文处理钩子函数*/
typedef ULONG (*OAM_1AG_USERPINGPKTDEAL)(UCHAR *pBuffer, ULONG ulBufLen, ULONG ulPktType);

/*注册1AG性能测试钩子*/
typedef ULONG (*OAM_1AG_CAPTEST)(ULONG ulTestType);

/*注册收到不带VLAN的LB和LT报文时,存在多个不带VLAN的MEP的通知钩子函数原型*/
typedef ULONG (*OAM_1AG_MORENOVLANNOTIFY_HOOK_FUNC)(ULONG ulIfIndex, TCPIP_1AG_NOVLANINFO_S *pstNoVlanInfo,
                                                             ULONG ulNoVlanInfoNum);
typedef struct tagOAM_1AG_RMEP_STAT
{
    ULONG ulRcvCcmPkt;      /*接收CCM报文数*/
    ULONG ulReserv;         /*预留4字节*/
} OAM_1AG_RMEP_STAT_S;

/*API 接口手册 */

extern ULONG  TCPIP_1AG_ClearHaStat(VOID);

extern ULONG  TCPIP_1AG_ClearMepStat(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId);

extern ULONG  TCPIP_1AG_CreateMa(UCHAR * pszMdName, UCHAR * pszMaName, ULONG ulVlanId);

extern ULONG  TCPIP_1AG_CreateMd(UCHAR * pszMdName, UCHAR ucMdLevel);

extern ULONG  TCPIP_1AG_CreateMep(ULONG ulIfIndex, UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId);

extern ULONG  TCPIP_1AG_CreateRmep(ULONG ulIfIndex, UCHAR *pucMacAddr, UCHAR * pszMdName, UCHAR * pszMaName,
                                    USHORT usRmepId);

extern ULONG  TCPIP_1AG_DeleteMa(UCHAR * pszMdName, UCHAR * pszMaName);

extern ULONG  TCPIP_1AG_DeleteMd(UCHAR * pszMdName);

extern ULONG  TCPIP_1AG_DeleteMep(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId);

extern ULONG  TCPIP_1AG_DeleteRmep(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usRmepId);
/****************************************************************************
*    Func Name: TCPIP_1AG_EnableCcmSend()
*  Description: 使能/去使能CCM报文发送接口
*        Input: UCHAR *pszMdName     MD名称
*               UCHAR *pszMaName     MA名称
*               USHORT usMepId      MEP标志
*               ULONG ucSendFlag    使能/去使能标志.1：使能，0去使能
*
*       Output: 无
*       Return: 成功或错误码
*
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-10  Zheng Sen Huo (00104483)         Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_1AG_EnableCcmSend(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, UCHAR ucSendFlag);

extern ULONG  TCPIP_1AG_GetCompatible(UCHAR * pszMdName, UCHAR *pszMaName, ULONG *pulValue);

extern ULONG  TCPIP_1AG_GetDebug(ULONG *pul1AgPktDebug, ULONG *pulError1AgPktDebug, ULONG
                                 *pul1AgVerbosePktDebug, ULONG *pulPacketNum, ULONG *pulPacketOctets);

extern ULONG  TCPIP_1AG_GetHaDebug(ULONG *pulHADebugFlag);

extern ULONG  TCPIP_1AG_GetHaStat(HA1AGSTAT_S *pstHa1agStat);

extern ULONG  TCPIP_1AG_GetMaInfo(UCHAR *pszMdName, UCHAR *pszMaName, DISP_MA_INFO_S *pstDispMaInfo);

extern ULONG  TCPIP_1AG_GetMdInfo(UCHAR *pszMdName, DISP_MD_INFO_S *pstDispMdInfo);

extern ULONG  TCPIP_1AG_GetMepInfo(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId,
                                    DISP_MEP_INFO_S * pstDispMepInfo);
/*******************************************************************************
*    Func Name: TCPIP_1AG_GetAllMepInfoById
* Date Created: 2009-01-11
*       Author: w60786
*  Description: 根据ID获取所有ID相同的MEP和RMEP信息.以链表的形式输出获取的信息.
*        Input: pszMdName:MD名称
                pszMaName:ma名称
                usMepId:mep id
*       Output: DISP_MEP_INFO_LIST_S ** ppstDispMepInfoList:mep信息链表.函数返回成功时输出MEP显示链表.否则一般为NULL.
*       Return: OAM1AG_ERR_PARANULL:参数为空
                OAM1AG_ERR_MDNAMELEN:md名字长度错误
                OAM1AG_ERR_MANAMELEN:ma名字长度错误
                OAM1AG_ERR_MDNAMELEN:md，ma名称长度错误
                OAM1AG_ERR_PARAWRONG:usMepId不合法
                OAM1AG_ERR_MDNOTEXIST:md不存在
                OAM1AG_ERR_MANOTEXIST:ma不存在
                OAM1AG_ERR_MEPNOTEXIST:mep不存在
                OAM1AG_ERR_NOTENOUGHMEMORY:内存分配失败
                OAM1AG_ERR_MODULENOTEXIST:组件未注册
                OAM1AG_OK:成功
*      Caution: 由VISP申请MEP显示链表节点内存,必须由调用者调用VISP接口TCPIP_1AG_FreeMepInfoList释放该链表内存.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-11   w60786                  Create
*
*******************************************************************************/
extern ULONG  TCPIP_1AG_GetAllMepInfoById(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, 
                                   DISP_MEP_INFO_LIST_S ** ppstDispMepInfoList);
/*******************************************************************************
*    Func Name: TCPIP_1AG_FreeMepInfoList
* Date Created: 2009-01-11
*       Author: w60786
*  Description: 释放TCPIP_1AG_GetAllMepInfoById接口返回给用户的MEP显示链表.
*        Input: pstDispMepInfoList:TCPIP_1AG_GetAllMepInfoById接口返回给用户的MEP显示链表指针,
*       Output: 
*       Return: OAM1AG_ERR_PARANULL:参数为空
                OAM1AG_ERR_MODULENOTEXIST:组件未注册
                OAM1AG_OK:成功 
*      Caution: TCPIP_1AG_GetAllMepInfoById接口返回给用户的MEP显示链表节点内存由VISP申请,
                必须由调用者调用VISP接口TCPIP_1AG_FreeMepInfoList释放该链表内存.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-11   w60786                  Create
*
*******************************************************************************/
extern ULONG  TCPIP_1AG_FreeMepInfoList(DISP_MEP_INFO_LIST_S * pstDispMepInfoList);

extern ULONG  TCPIP_1AG_GetMepStat(UCHAR *pszMdName, UCHAR * pszMaName, USHORT usMepId,
                                    OAM_1AG_STAT_S *pstOam1agStat);

extern ULONG  TCPIP_1AG_GetPktType(USHORT *pusEthType, UCHAR *pucPriority);
/*******************************************************************************
*    Func Name: TCPIP_1AG_SetMaVlanPri
*  Description: 设置基于MA的VLAN优先级
*        Input: UCHAR *pucMdName:MD名字
*               UCHAR *pucMaName:MA名字
*               UCHAR ucPriority:优先级,0~7
*       Output: 
*       Return: 成功:OAM1AG_OK ,失败:其它
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-07-07   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG  TCPIP_1AG_SetMaVlanPri(UCHAR *pucMdName,UCHAR *pucMaName,UCHAR ucPriority);

extern ULONG  TCPIP_1AG_GlobalDisable(VOID);

extern ULONG  TCPIP_1AG_NpNotify(ULONG ulIfIndex, UCHAR *pszMdName, UCHAR *pszMaName, USHORT usRmepId, ULONG ulType);

extern ULONG  TCPIP_1AG_Ping(ULONG ulIfIndex, UCHAR *pucMacAddr, UCHAR * pszMdName,
                              UCHAR * pszMaName, USHORT usRmepId, ULONG ulCount,
                              USHORT usPacketSize, USHORT usTimeOut, ULONG ulSendInterval, ULONG ulID);

/*******************************************************************************
*    Func Name: TCPIP_1AG_VlanPriPing
* Date Created: 2009-5-13
*       Author: w60786
*  Description: 指定VLAN优先级进行1AG Ping(即LB测试)
*        Input: TCPIP_1AG_PING_S *pst1agPing:指向1AG Ping参数的指针
*       Output: 
*       Return: OAM1AG_OK:成功; 其它:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-5-13   w60786/z62474    Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_1AG_VlanPriPing(TCPIP_1AG_PING_S *pst1agPing);


extern ULONG  TCPIP_1AG_RegFuncUserPingPktDeal(OAM_1AG_USERPINGPKTDEAL pfEoamPingPktDealFunc);
/****************************************************************************
*    Func Name: TCPIP_1AG_SetCcmInterval()
*  Description: 设置CCM发送间隔接口
*        Input: UCHAR *pszMdName    MD名称
*               UCHAR *pszMaName    MA名称
*               ULONG ulInterval    发送间隔
*
*       Output: 无
*       Return: 
*
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-10  Zheng Sen Huo (00104483)         Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_1AG_SetCcmInterval(UCHAR * pszMdName, UCHAR * pszMaName, ULONG ulInterval);

extern ULONG  TCPIP_1AG_SetCompatible(UCHAR * pszMdName, UCHAR *pszMaName, ULONG ulValue);

extern ULONG  TCPIP_1AG_SetDebug(ULONG ulType, ULONG ulFlag, ULONG ulPacketNum, ULONG ulPacketOctets);

extern ULONG  TCPIP_1AG_SetHaDebug(ULONG ulHADebugFlag);

extern ULONG  TCPIP_1AG_SetPktType(USHORT usPktType, UCHAR ucPriority);

extern VOID   TCPIP_1AG_ShowMaInfo(UCHAR *pszMdName, UCHAR *pszMaName);

extern VOID   OAM_1AG_ShowAllMdInfo(VOID);

extern VOID   TCPIP_1AG_ShowMdInfo(UCHAR *pszMdName);

extern VOID   TCPIP_1AG_ShowMepInfo(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepOrRmepId);

extern VOID   TCPIP_1AG_ShowMepStat(UCHAR *pszMdName, UCHAR * pszMaName, USHORT usMepId);

extern ULONG  TCPIP_1AG_Trace(ULONG ulIfIndex, UCHAR *pcMacAddr, UCHAR * pszMdName, UCHAR * pszMaName,
                               USHORT usRmepId, UCHAR ucTtl, USHORT usTimeOut, ULONG ulID);

extern ULONG  TCPIP_1AG_UserPing(ULONG ulIfIndex, UCHAR *pucMacAddr, UCHAR * pszMdName,
                                  UCHAR * pszMaName, USHORT usRmepId,
                                  UCHAR *pBuffer, ULONG ulLen);

/*******************************************************************************
*    Func Name: TCPIP_1AG_VlanPriUserPing
* Date Created: 2009-5-13
*       Author: w60786
*  Description: 指定VLAN优先级进行1AG User Ping(即用户自定义LB测试)
*        Input: TCPIP_1AG_USERPING_S *pst1agUserPing:指向1AG User Ping参数的指针
*       Output: 
*       Return: OAM1AG_OK:成功; 其它:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-5-13   w60786/z62474    Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_1AG_VlanPriUserPing(TCPIP_1AG_USERPING_S *pst1agUserPing);


extern ULONG  TCPIP_RegFunc1AGOutInfo(OAM_1AG_OUTINFO_HOOK_FUNC pfEOAM_1AG_OutInfo);

extern ULONG  TCPIP_RegFunc1AGUserStop(OAM_1AG_STOP_HOOK_FUNC pfEOAM_1AG_Stop);

/*******************************************************************************
*    Func Name: TCPIP_1AG_SetVersion
* Date Created: 2009-03-26
*       Author: wangmingxia
*  Description: 基于接口设置使用的1AG版本
*        Input: ULONG ulIfIndex:以太接口或者TRUNK接口索引
*               ULONG ulVersion:1AG使用的版本号,取值范围:0~1.
*                               0:表示使用Draft7版本的1AG协议; 1表示使用标准版本的1AG协议.
*                               默认值为0,即Draft7.
*       Output: 无
*       Return: VOS_OK:成功
*               其它:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-26   wangmingxia             Create
*
*******************************************************************************/
extern ULONG TCPIP_1AG_SetVersion(ULONG ulIfIndex, ULONG ulVersion);

/*******************************************************************************
*    Func Name: TCPIP_1AG_GetVersion
* Date Created: 2009-03-26
*       Author: wangmingxia
*  Description: 基于接口获取使用的1AG版本
*        Input: ULONG ulIfIndex:以太接口或者TRUNK接口索引
*       Output: ULONG *pulVersion:1AG使用的版本号,取值范围:0~1.
*                               0:表示使用Draft7版本的1AG协议; 1表示使用标准版本的1AG协议.
*       Return: VOS_OK:成功
*               其它:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-26   wangmingxia             Create
*
*******************************************************************************/
extern ULONG TCPIP_1AG_GetVersion(ULONG ulIfIndex, ULONG *pulVersion);

/*******************************************************************************
*    Func Name: TCPIP_1AG_SetRcvDefaultVlan
* Date Created: 2009-05-15
*       Author: wuhailan103194
*  Description: 设置1AG接收方向的默认处理VLAN,在处理LB/LT报文时,
*               如果报文中不带VLAN,则直接从该接口默认VLAN进行判断处理MD/MA
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulRcvDefaultVlan:接收方向的默认处理VLAN,0表示取消设置的默认VLAN
*       Output: 
*       Return: VOS_OK:成功
*               其它:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-05-15   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_1AG_SetRcvDefaultVlan(ULONG ulIfIndex, ULONG ulDefaultVlan);

/*******************************************************************************
*    Func Name: TCPIP_1AG_GetRcvDefaultVlan
* Date Created: 2009-05-15
*       Author: wuhailan103194
*  Description: 获取1AG接收方向的默认处理VLAN
*        Input: ULONG ulIfIndex:接口索引
*       Output: ULONG *pulDefaultVlan:返回的默认VLAN值.0表示没有设置默认VLAN
*       Return: VOS_OK:成功
*               其它:错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-05-15   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_1AG_GetRcvDefaultVlan(ULONG ulIfIndex, ULONG *pulDefaultVlan);

/*******************************************************************************
*    Func Name: TCPIP_1AG_RegFuncMoreNoVlanNotify
* Date Created: 2009-5-21
*       Author: w60786/z62474
*  Description: 注册收到不带VLAN的LB和LT报文时,存在多个不带VLAN的MEP的通知钩子函数
*        Input: OAM_1AG_MORENOVLANNOTIFY_HOOK_FUNC pfEoam1agMoreNoVlanNotifyFunc:
*               用户提供的钩子函数指针
*       Output: 
*       Return: OAM1AG_OK:成功; 其它:失败
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-5-21  w60786/z62474         Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_1AG_RegFuncMoreNoVlanNotify(OAM_1AG_MORENOVLANNOTIFY_HOOK_FUNC pfEoam1agMoreNoVlanNotifyFunc);


extern ULONG TCPIP_1AG_SetRmepCheck(UCHAR* pszMdName, UCHAR* pszMaName, USHORT usRmepId, ULONG ulSetYes);


extern ULONG TCPIP_1AG_GetRmepCheck(UCHAR* pszMdName, UCHAR* pszMaName, USHORT usRmepId, ULONG *pulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_1AG_SetFullCompatible
* Date Created: 2010-04-13
*       Author: wangbin (62223)
*  Description: 协议标准兼容性开关
*        Input: ULONG ulValue:0 -- 关闭 1-- 打开
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   wangbin (62223)         Create
*
*******************************************************************************/
ULONG TCPIP_1AG_SetFullCompatible(ULONG ulValue);


/*******************************************************************************
*    Func Name: TCPIP_1AG_GetFullCompatible
* Date Created: 2010-04-13
*       Author: wangbin (62223)
*  Description: 获取协议标准兼容性开关
*        Input: ULONG *pulValue:协议标准兼容性开关值
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   wangbin (62223)         Create
*
*******************************************************************************/
ULONG TCPIP_1AG_GetFullCompatible(ULONG *pulValue);


/*******************************************************************************
*    Func Name: TCPIP_1AG_ShowFullCompatible
* Date Created: 2010-04-13
*       Author: wangbin (62223)
*  Description: 显示协议标准兼容性开关
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   wangbin (62223)         Create
*
*******************************************************************************/
VOID TCPIP_1AG_ShowFullCompatible(VOID);


/*******************************************************************************
*    Func Name: TCPIP_1AG_SetLossDetectInterval
* Date Created: 2010-04-13
*       Author: wangbin (62223)
*  Description: 设置本端MEP的CCM Loss检测时间
*        Input: UCHAR *pszMdName:
*               UCHAR *pszMaName:
*               USHORT usMepId:
*               USHORT usInterval:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   wangbin (62223)         Create
*
*******************************************************************************/
ULONG TCPIP_1AG_SetLossDetectInterval(UCHAR *pszMdName, UCHAR *pszMaName, 
                                USHORT usMepId, USHORT usInterval);


/*******************************************************************************
*    Func Name: TCPIP_1AG_GetLossDetectInterval
* Date Created: 2010-04-13
*       Author: wangbin (62223)
*  Description: 获取本端MEP的CCM Loss检测时间
*        Input: UCHAR *pszMdName:MD
*               UCHAR *pszMaName:MA
*               USHORT usMepId:Mep Id
*               
*       Output: USHORT *pusInterval:保存CCm Lost Detect Timer
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   wangbin (62223)         Create
*
*******************************************************************************/
ULONG TCPIP_1AG_GetLossDetectInterval(UCHAR *pszMdName, UCHAR *pszMaName, 
                                    USHORT usMepId, USHORT *pusInterval);



ULONG TCPIP_1AG_GetRmepWarnState(UCHAR * pszMdName, UCHAR * pszMaName,
                    USHORT usRmepId, OAM1AG_WARN_STATE_S * pst1agWarnState);
 

ULONG TCPIP_1AG_SetGlobalVersion(ULONG ulVersion);


ULONG TCPIP_1AG_GetGlobalVersion(ULONG *pulVersion);


VOID TCPIP_1AG_ShowGlobalVersion(VOID);


ULONG TCPIP_Y1731_EnableAIS(UCHAR *pucMdName,UCHAR *pucMaName,UCHAR ucEnable);


ULONG TCPIP_Y1731_EnablePMCheck(UCHAR * pszMdName, UCHAR * pszMaName, USHORT usMepId, 
                        USHORT usRmepId,UCHAR ucPMType,UCHAR ucCheckFlag, ULONG ulSendInterval, ULONG ulTimeOut);



ULONG TCPIP_1AG_EnableRmepCCDetectEx(UCHAR* pszMdName, UCHAR* pszMaName, USHORT usRmepId, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_1AG_GetRMepStat
* Date Created: 2014-10-15
*       Author: likaikun213099
*  Description: 查询RMEP收到的CCM报文总数
*        Input: UCHAR *pszMdName:
*               UCHAR * pszMaName:
*               USHORT usRMepId:
*               OAM_1AG_RMEP_STAT_S  *pstRMepPkt:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-10-15   likaikun213099          Create
*
*******************************************************************************/
ULONG  TCPIP_1AG_GetRMepStat(UCHAR *pszMdName, UCHAR * pszMaName, USHORT usRMepId, 
                                            OAM_1AG_RMEP_STAT_S  *pstRMepPkt);
                                            
/*******************************************************************************
*    Func Name: TCPIP_1AG_ClearRMepStat
* Date Created: 2014-10-15
*       Author: likaikun213099
*  Description: 清除RMEP收到的CCM报文总数
*        Input: UCHAR *pszMdName:
*               UCHAR * pszMaName:
*               USHORT usRMepId:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-10-15   likaikun213099          Create
*
*******************************************************************************/
ULONG  TCPIP_1AG_ClearRMepStat (UCHAR *pszMdName,UCHAR * pszMaName, USHORT usRMepId);

/*******************************************************************************
*    Func Name: TCPIP_1AG_ShowRMepStat
* Date Created: 2014-10-15
*       Author: likaikun213099
*  Description: 显示RMEP收到的CCM报文总数
*        Input: UCHAR *pszMdName:
*               UCHAR * pszMaName:
*               USHORT usRMepId:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-10-15   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_1AG_ShowRMepStat(UCHAR *pszMdName, UCHAR * pszMaName, USHORT usRMepId);

/*******************************************************************************
*    Func Name: TCPIP_1AG_ShowAllMepInfoOnIf
* Date Created: 2014-11-08
*       Author: likaikun213099
*  Description: 显示指定接口上的所有MEP和RMEP
*        Input: CHAR* pszIfName:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-08   likaikun213099          Create
*
*******************************************************************************/
VOID TCPIP_1AG_ShowAllMepInfoOnIf(CHAR* pszIfName);

#ifdef  __cplusplus
}
#endif

#endif

