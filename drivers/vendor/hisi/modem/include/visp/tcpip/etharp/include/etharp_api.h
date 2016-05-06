/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              etharp_api.h
*
*  Project Code: VISPV100R007
*   Module Name: ETHARP
*  Date Created: 2008年1月25日
*        Author: x00100259
*   Description: ETHARP模块提供的对外数据结构定义和用户API声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008年1月25日  x00100259         Create the first version.
*  2008-08-13     f54882            Modify for BC3D00237
*
*******************************************************************************/

#ifndef _ETHARP_API_H_
#define _ETHARP_API_H_


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/**********************************************************************
*                        对外提供的错误码
***********************************************************************/

enum tagETHARPRetCode
{
    MEM_MALLOCFAIL = VOS_ERR + 1,   /*2,内存分配失败*/
    UNKNOWNED_FRAME,                /*3,报文为空*/
    MEMPREPEND_FAIL,                /*4,调用mbuf prepend失败*/
    UNKNOWNED_PROTO,                /*5,未知协议号*/
    ARP_OVERMAX,                    /*6,ARP表已满*/
    INVALID_IFNET,                  /*7,IFNET不存在*/
    LINKISDOWN,                     /*8,链路状态没有UP*/
    ARPRESOLVE_FAIL,                /*9,解析ARP失败*/
    ARPHEADER_ERROR,                /*10,ARP首部格式错误*/
    ARPSRCMAC_BROADCAST,            /*11,ARP源physical地址为广播地址*/
    ARPSRCMAC_ALLZERO,              /*12,ARP源physical地址为全零地址*/
    ARPONESEFMAC,                   /*13,ARP报文源MAC与本接口MAC相同*/
    ARPONESEFIP,                    /*14,ARP报文源IP与本接口IP相同*/
    ARPDSTIP_NOTSAMENET,            /*15,ARP报文目的地址与本接口地址不在同一网段*/
    ARPSRCIP_BROADCAST,             /*16,ARP源地址IP为广播地址*/
    ARPINERT_FAIL,                  /*17,插入ARP节点失败*/
    NOTARPREQUEST,                  /*18,报文不是ARP REQUEST*/
    NOTMAXIPADDR,                   /*19,接口不存在有效最匹配地址*/
    SENDING_REQUEST,                /*20,发送ARP REQUEST报文*/
    NOTENOUGHMEM,                   /*21,内存不足*/
    GETMTSOFTFAIL,                  /*22,获取以太控制块失败*/
    IPXENCAP_CONFLICT,              /*23,*/
    SPLIMP_FAIL,                    /*24,关中断失败*/
    ARPNOTEXIST,                    /*25,ARP节点不存在*/
    ERR_LINKTYPE,                   /*26,链路类型错误*/
    ARPREQUEST_FAIL,                /*27,发送ARP REQUEST失败*/

    ETHARP_GET_DATA_END,            /*28,无后续节点可获取*/
    ETHARP_INVALID_IPADDR,          /*29,地址不合法*/
    ETHARP_NULL_POINTER,            /*30,输入指针为空*/
    ETHARP_ERROR_SWITCH,            /*31,指定的开关值错误*/
    ETHARP_ERROR_PROXYTYPE,         /*32,指定的ARP代理类型错误*/
    ETHARP_INVALID_WLHANDLE,        /*33,指定的WaitList句柄无效*/
    ETHARP_HA_IS_SMOOTHING ,        /*34,HA正在平滑处理或手动倒换处理*/
    ETHARP_PORT_IS_TRUNKPORT,       /*35,接口是trunk的成员端口，不可操作*/
    ETHRRP_CMD_ERR,                 /*36,命令字不合法 */
    ETHARP_NOT_INIT,                /*37,以太功能被裁减，无该功能*/
    ETHARP_ERROR_SCOPE,             /*38 */
    ETHARP_OAM3AH_LB_LOCAL,         /*39,接口处于3AH环回响应态且测试模式为VISP软件模式     */
    ETHARP_WRONG_TYPE,              /*40,类型出错 */
    ETHARP_NOREG,                   /*41,ETH未注册*/
    ETHARP_VIRTUAL_IF,              /*42,虚接口不支持此功能 */
    ETHARP_LOCAL_IPADDR,            /*43,目的地址是本机IP */
    ETHARP_SUBNET_BROADCAST,        /*44,目的地址是子网广播地址 */
    ETHARP_ENABLE_VLAN_MODE,        /*45配置了VLAN模块的属性*/
    ETHARP_INVALID_VLAN_ID,         /*46 VLAN ID非法*/
    ETHARP_ERR_MAIN_INTF,           /*47 接口不应该为主接口*/
    ETHARP_ERR_L2PORT_TYPE,         /*48 二层端口类型不正确*/

    ETHARP_ERROR_VLANARPPROXY,      /*49,非VLAN IF接口不允许设置VLAN IF代理*/
    ETHARP_ERROR_L2IFNOTREG,        /*50 L2IF模块未注册*/
    ETHARP_ERROR_L2IFCHECK,         /*51 VLAN ID和出端口的有效性模块检查不通过*/
    ETHARP_ERROR_VLANIFNOTEXIST,    /*52 不存在跟VLAN对应的VLANIF*/
    ETHARP_ERROR_NOTSAMENETWITHVLANIF, /*53 地址和VLANIF不在同一网段内*/
    ETHARP_INVALID_IPADDR_IN_IF,    /*54 */
    ETHARP_ERROR_PARAWRONG,         /* 55 输入参数不合法 */
    ETHARP_ERROR_VRRP_VMAC,         /* 56 MAC是VRRP虚MAC */

    ETHARP_WAITLIST_CLOSE_FAIL,     /* 57 关闭waitlist失败 */
    ETHARP_WAITLIST_OPEN_FAIL,      /* 58 打开waitlist失败 */
    ETHARP_WAITLIST_GET_FAIL,       /* 59 获取waitlist失败 */
    /*Add by Q62011 for BC3D01073*/
    ETHARP_ERR_PROXY_IF,            /* 60 设置代理的接口不正确 */
    ETHARP_ERR_VIRTUAL_IP,          /* 61 地址是Backup路由器的虚地址 */
    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
    ETHARP_ERR_GET_VRFINDEX,        /* 62 获取VRF Index失败 */
    /* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */

    ETHARP_ERR_UNARP_DISABLE,       /*63 UNARP功能未使能,兼容V1R8C01*/

    /*Begin BC3D01604 子接口不显示ARP统计信息 l00147446 09-05-31*/
    ETHARP_ERR_SUB_INTF,            /*64 接口不应该为子接口*/
    /*End BC3D01604 子接口不显示ARP统计信息 l00147446 09-05-31*/
    ETHARP_ERR_HOOK_TYPE,            /* 65 注册钩子的类型参数不对 */
    ETHARP_ERR_HOOK_ALREADYREG,      /* 66 钩子已经注册 */
    ETHARP_ERR_HOOK_NOTREG,          /* 67 钩子未曾注册 */

    ARPREQUEST_FAIL_RE,             /*68,多次发送ARP REQUEST失败*/
    ARPREQUEST_FAIL_RES,            /*69,非RESOLVING状态发送ARP REQUEST失败*/

    ETHARP_GUARD_PKT_INBLACKLIST,      /*70 ARP报文结点在黑名单中  */

    ETHARP_GUARD_NULL_POINTER,         /*71 ETHARP Guard空指针 */

    ETHARP_GUARD_SET_BLACKNUMM_ERR,    /*72 ETHARP Guard设置一个IP下黑名单个数非法  */

    ETHARP_GUARD_GET_BLACKNUMM_FINISH, /*73 ETHARP Guard获取黑名单节点完成 */

    ETHARP_GUARD_OPEN_WAITLIST_ERR,    /*74 ETHARP Guard OPEN WaitList失败 */

    ETHARP_GUARD_SET_WAITLIST_ERR,     /*75 ETHARP Guard Set WaitList失败 */

    ETHARP_GUARD_CLOSE_WAITLIST_ERR,   /*76 ETHARP Guard Close WaitList失败 */

    ETHARP_GUARD_REG_WAITLIST_ERR,     /*77 ETHARP Guard Register WaitList失败 */

    ETHARP_GUARD_GET_WAITLIST_ERR,     /*78 ETHARP Guard Get WaitList失败 */

    ETHARP_GUARD_CLOSE_WAITLIST_PARA_ERR,/*79 ETHARP Guard Get WaitList失败 */

    ETHARP_GUARD_SET_SWITCH_ERR,       /*80 设置Guard开关值非法 */

    ETHARP_GUARD_GETMACNODEOK,         /*81 获取MAC结点成功 */

    ETHARP_GUARD_GETMACNODEFAIL,       /*82 获取MAC结点失败 */

    ETHARP_GUARD_MALLOC_BLACKNODE,     /*83 分配BLACK NODE节点失败 */

    ETHARP_GUARD_MALLOC_STATIC_BLACKNODE,     /*84 分配STATIC BLACK NODE节点失败 */

    ETHARP_GUARD_DEL_NOTAT_STATIC_BLACKLIST,  /*85 该MAC不在静态黑名单列表里面 */

    ETHARP_GUARD_NULL_POINT,                  /*86 空指针 */

    ETHARP_GUARD_NOT_ENABLE,                  /*87 ARP Guard开关没有打开 */

    ETHARP_GUARD_MAX_BLACKNUM_ONEIP,          /*88 同一个地址下的黑名单超出规格 */

    ETHARP_GUARD_MAX_STATIC_ARPNODE,          /*89 静态ARP Guard结点超出规格 */

    ETHARP_GUARD_VRF_ERR,                     /*90 VRFID超出范围 */

    EHTARP_VLAN_DISABLE,                      /*91, VLAN功能没有被使能 */

    EHTARP_INVALID_ID,                        /*92, 无效的VLIN ID */

    EHTARP_INVALID_VRF,                       /*93, 无效的VRF 信息 */

    ETHARP_MACMULTICAST,                      /*94, MAC是多播MAC */

    ETHARP_NOT_MAININTF,                      /*95, 接口不是主接口,只有主接口才能设置 */

    ETHARP_GUARD_DYNAMIC_NODE_NOEXSIT,        /*96, 动态ARP Gurad结点不存在 */

    ETHARP_NULL_POINTER_REG1XHOOK,            /*97, 注册处理802.1X钩子为空 */
    ETHARP_ERROR_NULL_IFNET_SNDEAP,           /*98, 发送802.1X等产品自定义报文接口不存在 */
    ETHARP_ERROR_IFNOTUP_SNDEAP,              /*99, 发送802.1X等产品自定义报文接口状态不为UP */
    ETHARP_ERROR_NULL_MBUF_SNDEAP,            /*100, 发送802.1X等产品自定义报文MBUF指针为空 */
    ETHARP_ERROR_NOTETH_SNDEAP,               /*101, 发送802.1X等产品自定义报文接口类型非Eth口 */
    ETHARP_ERROR_NO_FATHERIF,                 /* 102, 不存在父接口 */
    ETHARP_ERROR_REG_ISNATIP_NULL,            /* 103, 注册是否是NAT IP回调函数为空 */
    ETHARP_ERROR_VRF_NAMELONG=104,            /* 104, VRF名字长度大于31 */
    ETHARP_GUARD_NOT_INIT,                     /* 105,ARP Guard 未初始化 */
    ETHARP_INVALID_UNICAST_ARP_COUNT,          /* 106, 设置单播ARP次数非法 */
    ETHARP_INVALID_QUELEN,                     /* 107, ARP报文保存队列非法 */
    ETHARP_ERROR_FORMAT,                       /* 108, 非EthernetII及SNAP格式 */    
    ETHARP_GUARD_INVALID_PARA,                 /* 109, 输入参数非法 */
    ETHARP_GUARD_HA_IS_SMOOTHING,              /* 110, arpguard正在平滑 */ 
    ETHARP_MAX_SYSTEM_ARP,                    /* 配置达到系统最大可配ARP表项 */
    ETHARP_IPCONFLICT_TBL_DISABLE,              /* 112, IP Conflict table capture is disabled */
    ETHARP_EOF_IPCONFLICT_TBL,                /* 113, End of IP Conflict table */
    ETHARP_INVALID_PRECFG,                    /* 114,与配置值不匹配 */
    ETHARP_GUARD_DYNAMIC_EXCEED,              /* 115,动态黑名单个数超过规格 */
    ETHARP_ERROR_ALREADY_FRESHED,             /*116,动态ARP表项已经被动态更新*/
    ETHARP_ERROR_INVALID                       /* 最大值 */
};


/**********************************************************************
*                        对外提供的宏定义
***********************************************************************/
#define NORMAL_ARP_PROXY  0x01

/* 特殊ARP代理标志宏定义 */
#define SPECIAL_ARP_PROXY   0x02
/* 光网络特殊ARP代理标志，现已被SPECIAL_ARP_PROXY代替，暂时保留 */
#define OPTIC_ARP_PROXY   0x02


#define EXPIRETIME       1200    /*动态ARP老化时间20分钟*/
#define LARPTDOWN        20      /*延迟发送ARP请求的时间(秒)*/
#define NARPMAXTRIES     5       /*每一秒钟内允许向同一目的发送的ARP请求数*/
#define MAXPACKETS       1000    /*ARP队列的长度*/
#define MACADDRLEN       6       /*physical地址长度*/
#define PROADDRLEN       4       /*协议地址长度*/
#define MAXPKTSPERTIME   100     /*一次处理的ARP报文的最大包数*/
#define ARP_EXPIRE_DETECT_TIMES 3/* ARP超时探测次数缺省值 add by xiaoshouhe 2003/10/16 */


/*以太网帧格式*/
#define PKTFMT_ETHNT_2   0         /*ETHNT_2*/
#define PKTFMT_EN_SNAP   1         /*SNAP*/
#define PKTFMT_8023_IPX  2         /*8023*/
#define PKTFMT_8022_IPX  3         /*8022*/
#define PKTFMT_ETHNT_UNKNOWN 4      /*以太接口不识别报文*/
#define PKTFMT_EN_PPPOE  5         /*PPPOE帧类型*/


#define ETHERTYPE_BPDU     0xFFFD  /* use for bridge */
#define ETHERTYPE_CDP      0xFFFE  /* use for bridge */
#define ETHERTYPE_OTHER    0xFFFF  /* use for bridge */


#define ETHERiiHDRLEN       14 /*sizeof(struct tagETHERHDR)*/
#define ETHERSNAPHDRLEN     22 /*sizeof(struct tagETSNAPHDR)*/
#define ETHER8023HDRLEN     14 /*sizeof(struct tagET8023HDR)*/
#define ETHER8022HDRLEN     17 /*sizeof(struct tagFMT802HDR)*/


/*协议类型*/
#define ETHERTYPE_PUP       0x0200  /* PUP protocol */
#define ETHERTYPE_IP        0x0800  /* IP protocol */
#define ETHERTYPE_ARP       0x0806  /* Addr. resolution protocol */
#define ETHERTYPE_REVARP    0x8035  /* reverse Addr. resolution protocol */
#define ETHERTYPE_IPX       0x8137  /* Novell's IPX/SPX protocol */
#define ETHERTYPE_SLOW      0x8809  /* slow protocol */

#define ETHERTYPE_PPPOE_DISCOVERY 0x8863    /* PPPoE协商阶段报文协议号 */
#define ETHERTYPE_PPPOE_SESSION 0x8864      /* PPPoE会话阶段报文协议号 */
#define ETHERTYPE_ISIS      0x8000  /*need tested with cisco*/

#define ETHERTYPE_8021X     0x888E    /* 802.1X报文协议号 */

#define VLAN_DISABLE     0
#define VLAN_ENABLE      1
#define VLANTYPE_DOT1Q   0x8100  /* VLAN 802.1q格式*/
#define DOT1Q_TAG_SIZE   4

/*地址族类型,由socket.h提供，暂时*/
#ifndef AF_UNSPEC
#define AF_UNSPEC   0
#endif

#ifndef AF_IPX
#define AF_IPX      23              /* Novell Internet Protocol */
#endif

#ifndef AF_INET
#define AF_INET     2               /* internetwork: UDP, TCP, etc. */
#endif

#ifndef AF_ARPREPLY
#define AF_ARPREPLY 19              /* ARP应答报文*/
#endif


#define AF_PPPOE    13              /* PPPOE */

#define AF_PPPOE_CLIENT 14          /* PPPoE Client包标志*/

#define OSI_ISIS    7


#define ETHVLAN_VID_BROADCAST 4095
#define ETHVLAN_VLANID_MASK 0xfff


/*以下是ARP协议宏*/
#define ARP_PRELINKLEN   22        /*ARP请求报文链路头长度*/
#define MAX_ARPNUMBER    512       /*初始化静态ARP表项数*/
#define MAX_APRNUMBER_DYNAMIC 4096 /*初始化动态ARP表项数目*/

#define ARP_TIMEOUT      1000      /*1000ms,为防止ARP恶意攻击,如果连续收到地址与本机冲突的ARP报文, 每隔1秒处理一次 */


#define ETHARP_GET_DSTMACADDR(pArp) ((pArp)->ucArpDstMacAddr)
#define ETHARP_GET_SRCMACADDR(pArp) ((pArp)->ucArpSrcMacAddr)
#define ETHARP_GET_DSTPROADDR(pArp) ((pArp)->ucArpDstProAddr)
#define ETHARP_GET_SRCPROADDR(pArp) ((pArp)->ucArpSrcProAddr)

/* D12226 防止组播地址加入ARP表 */
#define IP_ETHER_MAC_MULTICAST(enaddr) ( (enaddr)[0] & 0x01 )

/*VLANIF ARP PROXY*/
#define INTER_SUB_VLAN_ARP_PROXY 0x03

/* 如下宏定义ARP结点的状态,供TCPIP_GetArpEntry使用,考虑到
某些产品可能已经使用了这些值,此处不再像ARP下发PPI那样将其
转换为按位的形式*/
#define ETHARP_ARPF_STATIC    0  /*ARP标志:静态*/
#define ETHARP_ARPF_RESOLVED  2  /*ARP结点项的状态,已经解析出来*/
#define ETHARP_ARPF_RESOLVING 3  /*ARP结点项的状态,正在解析*/

#define ETHARP_ARP_EXPIRE_INVALID 0XFFFFFFFF   /*ARP表项时间的无效值*/

#define ARP_GUARD_ENABLE    1
#define ARP_GUARD_DISNABLE  0

/* Modify by z00171897/s00176784, at 2011-06-02. 修改原因: 支持获取保存ARP报文队列 */
#define ETHARP_MAX_ARPQUE_LEN      128    /* 保存ARP报文队列长度最大值 */
/**********************************************************************
*                        对外提供的数据结构定义
***********************************************************************/

#pragma    pack( 1 )

typedef struct  tagETSNAPHDR
{
    UCHAR                   ucHdrDstMacAddr[6];     /*目的physical地址   */
    UCHAR                   ucHdrSrcMacAddr[6];     /*源physical地址     */
    USHORT                  usLen;                  /*以太网幀长度          */
    UCHAR                   ucDSAP;                 /* destination service access point*/
    UCHAR                   ucSSAP;                 /* source service access point */
    UCHAR                   ucCtrl;                 /* control domain */
    UCHAR                   ucORI[3];
    USHORT                  usType;
}ETHARP_ETSNAPHDR_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

#pragma    pack( 1 )

typedef struct tagFMT802HDR
{
    UCHAR                   ucHdrDstMacAddr[6];     /*目的physical地址  */
    UCHAR                   ucHdrSrcMacAddr[6];     /*源physical地址    */
    USHORT                  usLen;                  /*以太网幀长度        */
    UCHAR                   ucDSAP;                 /* destination service access point*/
    UCHAR                   ucSSAP;                 /* source service access point */
    UCHAR                   ucCtrl;                 /* control domain */
}ETHARP_FMT802HDR_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

#pragma    pack( 1 )

typedef struct   tagET8023HDR
{
    UCHAR                   ucHdrDstMacAddr[6];  /*目的physical地址  */
    UCHAR                   ucHdrSrcMacAddr[6];  /*源physical地址    */
    USHORT                  usLen;               /*以太网幀长度 */
}ETHARP_ET8023HDR_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

typedef struct    tagARPHDR
{
     USHORT     usHrdAddrFormat;          /* format of hardware address */
     #define    ARPHRD_ETHER     1          /* ethernet hardware format */
     #define    ARPHRD_IEEE      6          /* ieee snap hardware format */
     #define    ARPHRD_FRELAY    15          /* frame relay hardware format */
     USHORT     usProAddrFormat;          /* format of protocol address */
     UCHAR      ucHrdAddrLen;              /* length of hardware address */
     UCHAR      ucProAddrLen;              /* length of protocol address */
     USHORT     usOpType;                  /* one of operation type: */
     #define    ARPOP_REQUEST    1          /* request to resolve address */
     #define    ARPOP_REPLY      2          /* response to previous request */
     #define    ARPOP_REVREPLY   4          /* response giving protocol address */
     #define    ARPOP_INVREQUEST 8           /* request to identify peer */
     #define    ARPOP_INVREPLY   9          /* response identifying peer */
}ETHARP_ARPHDR_S;

typedef struct  tagETHERARP
{
     struct  tagARPHDR   ea_stHdr;        /* fixed-size header */
     UCHAR   ucArpSrcMacAddr[6];          /* sender hardware address */
     UCHAR   ucArpSrcProAddr[4];          /* sender protocol address */
     UCHAR   ucArpDstMacAddr[6];          /* target hardware address */
     UCHAR   ucArpDstProAddr[4];          /* target protocol address */
     #define  usHdrAddrFmt   ea_stHdr.usHrdAddrFormat
     #define  usProAddrFmt   ea_stHdr.usProAddrFormat
     #define  ucHdrAdrLen    ea_stHdr.ucHrdAddrLen
     #define  ucProAdrLen    ea_stHdr.ucProAddrLen
     #define  usOprType      ea_stHdr.usOpType
}ETHARP_ETHERARP_S;

typedef struct  tagETHERUNARP
{
     struct  tagARPHDR   ea_stHdr;        /* fixed-size header */
     UCHAR   ucUnArpSrcProAddr[4];          /* sender protocol address */
     UCHAR   ucUnArpDstProAddr[4];          /* target protocol address */
     #define  usUnHdrAddrFmt   ea_stHdr.usHrdAddrFormat
     #define  usUnProAddrFmt   ea_stHdr.usProAddrFormat
     #define  ucUnHdrAdrLen    ea_stHdr.ucHrdAddrLen
     #define  ucUnProAdrLen    ea_stHdr.ucProAddrLen
     #define  usUnOprType      ea_stHdr.usOpType
}ETHARP_ETHERUNARP_S;


#pragma    pack( 1 )
typedef struct  tagETHERHDR
{
    UCHAR                   ucHdrDstMacAddr[6];     /*目的physical地址*/
    UCHAR                   ucHdrSrcMacAddr[6];     /*源physical地址  */
    USHORT                  usHdrType;              /*协议类型   */
}ETHARP_ETHERHDR_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

typedef struct tagTCPIP_ETHARP_ARPRTENTRY
{
    ULONG ulRtIpAddr;             /*用来保存地址*/
    UCHAR ucMacAddr[6];           /*用来保存physical地址*/
    UCHAR ucPadding_1[2];
    ULONG ulFlags;                /*该ARP的标志字段 */
    ULONG ulRtIfIndex;            /*用来保存IFNET接口INDEX*/
    ULONG ulRtExpire;             /*用来实现ARP缓存的超时处理 */
    ULONG ulVlinkIndex;           /*NP下发后返回的VLINK索引号*/
    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
    ULONG ulVrfIndex;             /* VRF索引 */
    /* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
    ULONG ulOutPortIfIndex;       /*ARP出端口索引*/
}TCPIP_ETHARP_ARPRTENTRY_S;


typedef struct tagETHSTAT_S
{
    ULONG    ulRcvBytes;          /* 接收的字节数 */
    ULONG    ulSndBytes;          /* 发送的字节数 */
    ULONG    ulRcvPkts;           /* 接收的报文数 */
    ULONG    ulSndPkts;           /* 发送的报文数 */
    ULONG    ulRcvARPRqstPkts;    /* 接收的ARP请求报文数 */
    ULONG    ulRcvARPRplyPkts;    /* 接收的ARP应答报文数 */
    ULONG    ulSndARPRqstPkts;    /* 发送的ARP请求报文数 */
    ULONG    ulSndARPRplyPkts;    /* 发送的ARP应答报文数 */
    ULONG    ulSndDropPkts;       /* 发送时丢弃的报文数 */
    ULONG    ulRcvDropPkts;       /* 接收时丢弃的报文数 */
    /*Add for BC3D00792,DR.134以太的统计信息中增加：FREE ARP的统计*/
    ULONG    ulSndFreeArp;        /* 发送的免费ARP报文数 */
    /*Add for BC3D00792,DR.133以太模块需提供发送ARP 报文的接口*/
    ULONG    ulUserSndArpRas;     /* 用户API发送的ARP请求报文数 */
    ULONG    ulUserSndArpRpl;     /* 用户API发送的ARP响应报文数 */
    ULONG    ulSndUnArpPkts;      /* 发送的UNARP报文数 */
    ULONG    ulRcvUnArpPkts;      /* 接收的UNARP报文数 */
    ULONG    ulArpMissUpCount;    /* ARP Miss上报次数统计 */
    ULONG    ulArpMissNpCount;    /* ARP Miss下发Np次数统计*/
    /*Added by wangtong207740, ETH报文统计增强, 2012/9/3 */
    ULONG    ulRcvBcastPkts;       /*收到的广播报文个数*/
    ULONG    ulSndBcastPkts;       /*发送的广播报文个数*/
    ULONG    ulRcvMcastPkts;       /*收到的多播报文个数*/
    ULONG    ulSndMcastPkts;       /*发送的多播报文个数*/
    ULONG    ulSndPhyFailtPkts;   /*发送驱动失败的报文个数统计。*/
}ETHSTAT_S;

/* Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */
typedef struct tagETHSTAT_LIST_S
{
    ULONG     ulIfIndex;
    ETHSTAT_S stEthStat;
}ETHSTAT_LIST_S;
/* End of Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */

/* 用户发送的ARP请求报文统计信息 */
typedef struct tagUSERARPSTAT_S
{
    ULONG    ulSendUserArpPkts;    /* 用户指定发送ARP请求成功次数 */
    ULONG    ulSendUserArpFails;   /* 用户指定发送ARP请求失败次数 */
}USERARPSTAT_S;

typedef struct tagSPECIAL_ARPPROXY_PARA
{
    ULONG ulSrcIpAddr;
    ULONG ulDestIpAddr;
    ULONG ulSubnetMask;
    ULONG ulInIfIndex;
    ULONG ulOutIfIndex;
    ULONG ulOutIfLinePro;
    ULONG ulDestIpRtMaskLen;
}SPECIAL_ARPPROXY_PARA_S;

typedef struct tagARPINFO_S
{
    ULONG ulIfIndex;     /* 接口索引 */
    ULONG ulIpAddr;      /* 地址，主机字节序 */
    UCHAR ucMacAddr[6];  /* physical地址 */
    USHORT ulFlags;      /* 0 静态 1 动态 */
    ULONG ulVlinkIndex;  /* VLINK索引 */
    ULONG ulVlanId;      /* VLAN ID */
    ULONG ulPortIfIndex; /* 出接口索引 */

    /*arp Mccp support V300R001C00 --  start*/    
    
    ULONG ulRemainExpireTime;         /*Remaining Expiry Time*/
    ULONG ulLastRefTime;              /*absolute Time at which the entry was last ref.*/

    /*arp Mccp support V300R001C00 --  End*/        

} ARPINFO_S;

/* DTS2013082109647【新需求-CIP-ARP】CGP产品联调测试场景需要获取临时ARP表项信息，需要新增API接口获取临时表项 */
typedef struct tagARPINPUT_S
{
    ULONG ulIpAddr;      /* 地址，主机字节序 */
    ULONG ulVrfIndex;    /* vrf index */
} ARPINPUT_S;

/*Added by z00208058, for PTN需求，支持指定VLAN恢复ARP, 2013/1/23 */
typedef struct tagARPWITHVLANINFO_S
{
    ULONG  ulIfIndex;     /* 接口索引 */
    ULONG  ulIpAddr;      /* 地址 */
    UCHAR  ucMacAddr[6];  /* physical地址 */
    USHORT usVlanId;      /* VLAN ID */
} ARPWITHVLANINFO_S;

/*Added by z00208058, 解决主接口和子接口共vlan问题，DTS2014122609381, 2014/12/26 */
typedef struct tagEtharpGetRcvIfInfo_S
{
    ULONG ulMainIfIndex;         /*主接口索引*/
    ULONG ulSubIfIndex;          /*对应VLAN子接口索引*/
    ULONG ulRcvIfIndex;          /*返回的入接口索引*/
}ETHARP_GET_RCVIF_S;

#define ETHARP_NOT_PROCESSED_BY_VLAN              0
#define ETHARP_PROCESSED_ERR_BY_VLAN              1
#define ETHARP_PROCESSED_BY_VLAN              2

/**********************************************************************
*                        对外提供的类型定义
***********************************************************************/

typedef ULONG (*ETHARP_INTERMEDIATE_HOOK_FUNC)(struct tagMBuf *pstMBuf);
typedef VOID (*DealIpConflict_HOOK_FUNC )(ULONG ulIfIndex, ULONG ulIpAddr, UCHAR * pucMac);
typedef ULONG ( * gpfTCPIPSpecialArpProxy) (SPECIAL_ARPPROXY_PARA_S *pstSpecArpPrxyPara);
typedef ULONG ( *gpfTCPIPGetVlanHead)(MBUF_S* pstMbuf,ULONG* pulVlanHead);
typedef ULONG(*gpfTCPIPSpecialArpProxyIP)(ULONG ulIfIndex, ULONG IPAddr);

/* 是否是NAT 地址回调函数数据结构定义,地址为网络序 */
typedef ULONG(*ETHARP_IS_NAT_IPADDR_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulIPAddr);

/*Added by z00208058, 解决主接口和子接口共vlan问题，DTS2014122609381, 2014/12/26 */
typedef ULONG (*ETHARP_GETARPRCVIFINDEX_HOOK_FUNC)(ETHARP_GET_RCVIF_S *pstRcvIfInfo);


#define ETHARP_NOT_PROCESSED_BY_INTERMEDIATE              0
/* intermediate found the packet has Error, Stack will Destroy the Packet */
#define ETHARP_INTER_PROCESS_ERROR                        1
/* Intermediate Processing will continue processing and will own the packet PP do not need to process the packet any more */
#define ETHARP_PROCESSED_BY_INTERMEDIATE                  2

#define ARP_FILTER_IFINDEX      0x00000001
#define ARP_FILTER_VALID        0x00000010
#define ARP_FILTER_IPADDR       0x00000100
#define ARP_FILTER_MAC          0x00001000
#define ARP_FILTER_ARPSTATIC    0x00010000
#define ARP_FILTER_ARPDYNAMIC   0x00100000
#define ARP_FILTER_VRF          0X01000000

#define MAX_ETHARP_EXPIRE_TIME 86400
#define MIN_ETHARP_EXPIRE_TIME 60

#define MAX_ETHARP_EXPIRE_TIME_SGSN 62640
#define MIN_ETHARP_EXPIRE_TIME_SGSN 20


/* Expire Time Mode Macros for different products*/
#define EXPIRE_TIME_MODE_SGSN 0    /* allows changing expire time for main interface and change will reflet inexisting entries*/
#define EXPIRE_TIME_MODE_HERT 1    /*allows changing expire time for main interface and sub interface and change will reflet in existing entries*/
#define EXPIRE_TIME_MODE_MCCP 2   /*allows changing expire time for main interface and sub interface and change will not reflet in existing entries*/

#define MAX_ETHARP_DETECT_TIMES 12
#define MIN_ETHARP_DETECT_TIMES 1

#define ETHARP_STATIC_ARP_TYPE 1
#define ETHARP_DYNAMIC_ARP_TYPE 2

#define ETHARP_ARP_INVALID 0
#define ETHARP_ARP_VALID 1

#define ETHARP_FREEARP_MINTIMES      3
#define ETHARP_FREEARP_DEFAULTTIMES  5
#define ETHARP_FREEARP_MAXTIMES      10

#define ETHARP_FREEARP_MINTOTALNUM      32
#define ETHARP_FREEARP_DEFAULTTOTALNUM  64
#define ETHARP_FREEARP_MAXTOTALNUM      256

#define ETHARP_FAKEUPDATE 2   /*pre-config value for g_ulArpUpdToPPISwitch for Fake node uupdate to PPI feature*/

#define ETHARP_MIN_EXPIREOFFSET 30
#define ETHARP_MAX_EXPIREOFFSET 60

typedef struct tagARPInfo
{
    ULONG     ulValid;
    ULONG     ulIfIndex;
    ULONG     ulIpAddr;
    UCHAR     ucMac[6];
    USHORT    usVID;
    ULONG     ulArpType;
    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
    CHAR  szVrfName[TCPIP_MAX_VRFNAME_LENGTH + 1];
    /* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
    ULONG     ulArpExpireTime;/*ARP结点的老化时间，如果为静态结点，此值为0xFFFFFFFF*/
    /*modefy for BC3D03264 ARP显示需要符合SGSN要求 l00147446 10-06-13*/
    ULONG     ulLeftExpireTime;/*ARP结点老化剩余时间,对于静态ARP结点，此值为0 */
    UCHAR     ucDArpFlag;  /* 动态ARP有效, 1表示由用户添加, 0表示协议栈自动生成 */
    UCHAR     ucpad[3];
} ARP_INFO_S;

typedef struct tagARPFilter
{
    /*f47854:过滤模式
    ARP_FILTER_IFINDEX - 基于ulIfIndex过滤
    ARP_FILTER_VALID - 基于ulValid过滤
    ARP_FILTER_IPADDR - 基于ulIpAddr过滤
    ARP_FILTER_MAC - 基于ucMac过滤
    ARP_FILTER_ARPSTATIC - 基于静态ARP过滤
    ARP_FILTER_ARPDYNAMIC - 基于动态ARP过滤
    ARP_FILTER_VRF - 基于VRF过滤
    */
    ULONG ulFilterMode;
    ULONG  ulIfIndex;
    ULONG  ulValid;
    ULONG  ulIpAddr;
    UCHAR  ucMac[6];
    USHORT usRsv;
    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
    CHAR  szVrfName[TCPIP_MAX_VRFNAME_LENGTH + 1];
    /* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
}ARP_FILTER_S;

#define ETHARP_MAX_MAC_INFO  4

typedef struct tagMacInfo
{
    UCHAR  ucMac[6];     /* physical address */
    UCHAR  ucFlag;       /*ETHARP_STATE_CONFLICT, ETHARP_STATE_WAITFORREPLY */
    UCHAR  ucTimeCount;  /* Timer units */
}ETHARP_MAC_INFO_S;  

typedef struct tagIpConflictInfo
{
    ULONG ulIPConflictType; /* Conflicting address type: ETHIP (1); OMIP (2) */
    ULONG ulIfIndex;        /* Conflict IfIndex */
    ULONG ulIpAddr;         /* Conflicting address */
    ULONG ulMacNum;         /* address conflicts with an address corresponding to the number of conflicts Mac */
    ETHARP_MAC_INFO_S stMacInfo[ETHARP_MAX_MAC_INFO] ;
    ULONG ulVrfIndex;       /* Attached VrfIndex */
} ETHARP_IP_CONFLICT_INFO_S;

/* IPConflictType definitions */
#define ETHARP_STATE_CONFLICT               1  
#define ETHARP_STATE_WAITFORREPLY           2  

/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
#ifndef MACADDRLEN
#define MACADDRLEN 6             /* physical地址长度 */
#endif

typedef struct tagARP_CFG_S
{
    ULONG ulIpAddr ;
    UCHAR ucMacAddr[MACADDRLEN];
    USHORT usVID;    /* Add By q62011 for BC3D01371 */
    CHAR  szVrfName[TCPIP_MAX_VRFNAME_LENGTH + 1];
}ARP_CFG_S;
/* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */

/*发送UNARP入参结构*/
typedef struct tagETHARP_UNARPINFO_S
{
    ULONG ulIfIndex;        /*出接口*/
    ULONG ulIpAddr;         /*源地址(主机序)*/
}ETHARP_UNARPINFO_S;

typedef ULONG (*ETHARP_INPUT_HOOK_FUNC)( MBUF_S* pMbuf );
typedef ULONG (*ETHARP_OUTPUT_HOOK_FUNC)( MBUF_S* pMbuf );

extern ETHARP_INPUT_HOOK_FUNC g_EthARP_Input_HookFunc;
extern ETHARP_OUTPUT_HOOK_FUNC g_EthARP_Output_HookFunc;

/* 接收ARP报文通知处理回调函数，VLAN首部为主机序，ARP报文内容为网络序 */
typedef VOID (*ETHARP_ARPINPUT_NOTIFY_HOOK)(ULONG ulIfIndex,ULONG ulVlanHead, ETHARP_ETHERARP_S *pstArp);

/* EAP模块接收802.1X报文钩子函数原型,报文由钩子函数负责释放 */
typedef ULONG (*EAPOL_RECV_PKT_HOOK)(ULONG ulIfIndex, struct tagMBuf *pstMBuf, ULONG ulPktLen);

/* 以太封装VLAN首部前处理回调函数 */
typedef ULONG (*ETH_BEFORE_ADD_VLANTAG_HOOK)(ULONG ulIfIndex, MBUF_S* pstMBuf);

/**********************************************************************
*                        对外提供的用户API声明
***********************************************************************/

extern ULONG TCPIP_RegFuncARPInputFunc( ETHARP_INPUT_HOOK_FUNC pfHookFunc );
extern ULONG TCPIP_RegFuncEthArpOutputHook( ETHARP_OUTPUT_HOOK_FUNC pfHookFunc );
extern ULONG TCPIP_CloseARPInfoTable( UINTPTR ulARPInfoHandle );
extern ULONG TCPIP_GetNextARPInfo( UINTPTR ulARPInfoHandle, ARP_INFO_S* pstARPInfo );
extern ULONG TCPIP_OpenARPInfoTable(UINTPTR* pulARPInfoHandle, ARP_FILTER_S* pstARPFilter);
extern ULONG TCPIP_SetARPExpireTime( ULONG ulTime, CHAR* szIfName );
extern ULONG TCPIP_SetARPDetectTimes( ULONG ulDetectTimes, CHAR* szIfName );
extern ULONG TCPIP_SetARPDetectTimesByIndex( ULONG ulDetectTimes, ULONG ulIfIndex );
extern ULONG TCPIP_GetARPDetectTimes( ULONG* pulDetectTimes, CHAR* szIfName );
extern ULONG TCPIP_GetARPExpireTime( ULONG* pulTime, CHAR* szIfName );
extern ULONG TCPIP_ShowARPDetectTimes( CHAR* szIfName );
extern ULONG TCPIP_ShowARPExpireTime( CHAR* szIfName );

extern ULONG  TCPIP_AddStaticArpWithVlan(ULONG ulIpAddr, UCHAR *pucMacAddr,USHORT usVID);
/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
/*******************************************************************************
*    Func Name: TCPIP_AddStaticArpByVrf
* Date Created: 2008-03-25
*       Author: x00100259
*  Description: Add static arp entry by Vrf
*        Input: ARP_CFG_S *pstARPIn:静态arp配置控制块
*
*       Output:
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_AddStaticArpByVrf(ARP_CFG_S *pstARPIn);

/*******************************************************************************
*    Func Name: TCPIP_DelArpEntryByVrf
* Date Created: 2009-02-06
*       Author: wangchengyang
*  Description: 删除某个指定VRF的ARP表项
*        Input: ULONG ulIpAddr:地址
*               ULONG ulScope:范围
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-06   wangchengyang           VISP1.7C03 VRF,Create
*******************************************************************************/
extern ULONG  TCPIP_DelArpEntryByVrf(ULONG ulIpAddr,ULONG ulScope,CHAR *pszVrfName);

/* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */

/*******************************************************************************
*    Func Name: TCPIP_AddStaticArp
*  Description: Add static arp entry
*        Input: ULONG ulIpAddr:地址
*               UCHAR pucMacAddr:physical地址
*       Output:
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_AddStaticArp( ULONG ulIpAddr, UCHAR *pucMacAddr );
/*******************************************************************************
*    Func Name: TCPIP_ClearAllARPEntry
*  Description: 清除所有的ARP表
*        Input: 无
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_ClearAllARPEntry(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ClearAllDynARPEntry
*  Description: 清楚所有arp表象
*        Input: 无
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_ClearAllDynARPEntry(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ClearDynARPEntryByIntf
*  Description: 删除某个接口下的动态ARP表项
*        Input: ULONG ulIfIndex:接口索引
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*  2008-08-13   f54882                  Modified for BC3D00242
*
*******************************************************************************/
extern ULONG  TCPIP_ClearDynARPEntryByIntf( ULONG ulIfIndex );
/*******************************************************************************
*    Func Name: TCPIP_ClearStaticARPEntry
*  Description: 清楚所有静态arp表项
*        Input: 无
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_ClearStaticARPEntry(VOID);
/*******************************************************************************
*    Func Name: TCPIP_CloseArpTable
*  Description: 关闭apr表
*        Input: ULONG ulWaitlist:ulWaitlist句柄
*       Output:
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_CloseArpTable( UINTPTR ulWaitlist );
/*******************************************************************************
*    Func Name: TCPIP_ClrEthStat
*  Description: 清除以太接口报文统计信息
*        Input: ULONG ulIfIndex:接口索引
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_ClrEthStat( ULONG ulIfIndex );
/*******************************************************************************
*    Func Name: TCPIP_DelArpEntry
*  Description: 删除某个ARP表项
*        Input: ULONG ulIpAddr:地址
*               ULONG ulScope:范围
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_DelArpEntry( ULONG ulIpAddr,ULONG ulScope );
/*******************************************************************************
*    Func Name: TCPIP_EthArpmiss_SGSN
* Date Created: 2010-04-13
*       Author: x00100259
*  Description: 处理NP的ARP MISS消息,供SGSN使用
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulDstIpAddr:目的地址
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-13   l00147446               Create
*
*******************************************************************************/
ULONG TCPIP_EthArpmiss_SGSN(ULONG ulIfIndex, ULONG ulDstIpAddr);
/*******************************************************************************
*    Func Name: TCPIP_EthArpmiss
*  Description: 处理NP的ARP MISS消息
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulDstIpAddr:目的地址
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG   TCPIP_EthArpmiss( ULONG ulIfIndex, ULONG ulDstIpAddr );
/*******************************************************************************
*    Func Name: TCPIP_GetArpEntry
*  Description: Get arp entry
*        Input: ULONG ulWaitlist:WaitList句柄
*               TCPIP_ETHARP_ARPRTENTRY_S *pstArpEntry:ARP表项结点指针
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetArpEntry( UINTPTR ulWaitlist, TCPIP_ETHARP_ARPRTENTRY_S *pstArpEntry );
/*******************************************************************************
*    Func Name: TCPIP_GetArpEntryByIPAddr
*  Description: 根据地址查询ARP表项
*        Input: ULONG ulIPAddr: 要查询的ARP表项的地址，主机序
*               ARPINFO_S *pstARPInfo: 产品关心的ARP信息，指向的内存由用户负责申请和释放
*       Output: ARPINFO_S *pstARPInfo: 产品关心的ARP信息，指向的内存由用户负责申请和释放
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetArpEntryByIPAddr( ULONG ulIPAddr, ARPINFO_S *pstARPInfo );

/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
/*******************************************************************************
*    Func Name: TCPIP_GetArpEntryByVrfIPAddr
* Date Created: 2009-02-09
*       Author: wangchengyang
*  Description: 根据地址查询ARP表项
*        Input: ULONG ulIPAddr: 要查询的ARP表项的地址，主机序
*               ARPINFO_S *pstARPInfo: 产品关心的ARP信息，指向的内存由用户负责申请和释放
*       Output: ARPINFO_S *pstARPInfo: 产品关心的ARP信息，指向的内存由用户负责申请和释放
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-09   wangchengyang           VISP1.7C03 VRF,Create
*******************************************************************************/
extern ULONG  TCPIP_GetArpEntryByVrfIPAddr(ULONG ulIPAddr, ARPINFO_S *pstARPInfo,ULONG ulVrfIndex);
/* End:VISP1.7C03 VRF wangchengyang , 2009-02-09 */

/*******************************************************************************
*    Func Name: TCPIP_GetArpInfoByInput
* Date Created: 2013-08-20
*       Author: MaFeng59090
*  Description: 为支持用户指定信息查询ARP表项信息新增API接口
*        Input: ARPINPUT_S *pstInputInfo: 用户指定的查询条件
*               ARPINFO_S *pstARPInfo: 查询到的ARP表项信息
*       Output: ARPINFO_S *pstARPInfo: 查询到的ARP表项信息
*       Return: 0 成功/非0 错误码
*      Caution: DOPRA IP V300R001C10版本仅支持指定vrf、地址两个查询条件
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-08-20   MaFeng59090             Create
*
*******************************************************************************/
ULONG TCPIP_GetArpInfoByInput(ARPINPUT_S *pstInputInfo, ARPINFO_S *pstARPInfo);

/*******************************************************************************
*    Func Name: TCPIP_GetArpNum
*  Description: 查询ARP表项总个数
*        Input: ULONG ulType:ULONG ulType: 0 静态  1 动态  其他 静态加动态表项总数
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetArpNum( ULONG ulType );
/*******************************************************************************
*    Func Name: TCPIP_GetArpProxy
*  Description: get arp proxy switch
*        Input: ULONG ulIfIndex:接口索引
*
*       Output:  ULONG * pulFlag:开关
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetArpProxy( ULONG ulIfIndex, ULONG * pulFlag );
/*******************************************************************************
*    Func Name: TCPIP_GetEthArpDebugSwitch
*  Description: 获取DEBUG调试开关
*        Input: ULONG* pulDebugArp:ARP调试开关
*               ULONG* pulDebugEthernet:ETH调试开关
*               ULONG* pulAclGroupNum:ACL规则组序号
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetEthArpDebugSwitch( ULONG* pulDebugArp, ULONG* pulDebugEthernet, ULONG* pulAclGroupNum );
/*******************************************************************************
*    Func Name: TCPIP_GetEthHADbg
*  Description: ETHARP调试信息的获取接口
*        Input: 无
*       Output: ULONG *pulDbg:以太调试开关状态
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetEthHADbg( ULONG *pulDbg );
/*******************************************************************************
*    Func Name: TCPIP_GetEthStat
*  Description: 查询以太接口报文统计信息
*        Input: ULONG ulIfIndex:接口索引
*
*       Output: ETHSTAT_S * pstEthStat:以太接口的统计信息
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetEthStat( ULONG ulIfIndex, ETHSTAT_S * pstEthStat );
/*******************************************************************************
*    Func Name: TCPIP_GetPPIArpByIp
*  Description: 根据PPI接口的需要，利用地址查询对应的ARP节点
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulIpAddr:目的地址
*
*       Output: PPI_ARP_S*pstPpiArp:查询成功后得到的ARP信息
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetPPIArpByIp(ULONG ulIfIndex, ULONG ulIpAddr, PPI_ARP_S*pstPpiArp );
/*******************************************************************************
*    Func Name: TCPIP_OpenArpTable
*  Description: Open object for arp table
*        Input: ULONG *pulWaitlist:WaitList句柄
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_OpenArpTable( UINTPTR *pulWaitlist );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDealIpConflictHook
*  Description: 注册地址冲突适配函数
*        Input: DealIpConflict_HOOK_FUNC pfHookFunc:地址冲突适配函数
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncDealIpConflictHook( DealIpConflict_HOOK_FUNC pfHookFunc );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncEthArpHook
*  Description: 注册钩子函数
*        Input: ULONG  ulType:注册类型
*               ETHARP_INTERMEDIATE_HOOK_FUNC pfFun:ETHARP钩子函数
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncEthArpHook( ULONG  ulType, ETHARP_INTERMEDIATE_HOOK_FUNC pfFun );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetVlanHeadHook
*  Description: 注册获取vlan头适配函数
*        Input: gpfTCPIPGetVlanHead pfHookFuc:获取vlan头适配函数
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncGetVlanHeadHook( gpfTCPIPGetVlanHead pfHookFuc );
/*******************************************************************************
*    Func Name: TCPIP_RegFuncSpecialArpProxyHook
*  Description: 注册特殊arp函数
*        Input: gpfTCPIPSpecialArpProxy pfHookFuc:特殊arp函数
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncSpecialArpProxyHook( gpfTCPIPSpecialArpProxy pfHookFuc );
/*******************************************************************************
*    Func Name: TCPIP_SendGratuitousArp
*  Description: 发送免费ARP报文
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulIpAddr:地址
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-24   x00100259               Create
*  2008-08-13   f54882                  Modified for BC3D00242
*
*******************************************************************************/
extern ULONG  TCPIP_SendGratuitousArp (ULONG ulIfIndex, ULONG ulIpAddr);
/*******************************************************************************
*    Func Name: TCPIP_SetArpProxy
*  Description: set arp proxy switch
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulFlag:接口类型标志
*               ULONG ulSetYes:是否设置
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*  2008-08-13   f54882                  Modified for BC3D00242
*
*******************************************************************************/
extern ULONG  TCPIP_SetArpProxy( ULONG ulIfIndex, ULONG ulFlag, ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_SetEthArpDebugSwitch
*  Description: 获取DEBUG调试开关
*        Input: ULONG ulDebugArp:ARP调试开关
*               ULONG ulDebugEthernet:ETH调试开关
*               ULONG ulAclGroupNum:ACL规则组序号
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_SetEthArpDebugSwitch( ULONG ulDebugArp, ULONG ulDebugEthernet, ULONG ulAclGroupNum );
/*******************************************************************************
*    Func Name: TCPIP_SetEthHADbg
*  Description: ETH调试信息设置接口
*        Input: ULONG ulDbg:调试开关值
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*
*******************************************************************************/
extern ULONG  TCPIP_SetEthHADbg( ULONG ulDbg );
/*******************************************************************************
*    Func Name: TCPIP_SetVlan
*  Description: 使能或去使能接口VLAN功能
*        Input: ulIfIndex:接口的索引号
 *              ulSetYes:使用能标致 1：使能  0:不使能
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   x00100259               Create
*  2008-08-13   f54882                  Modified for BC3D00242
*
*******************************************************************************/
extern ULONG  TCPIP_SetVlan( ULONG ulIfIndex , ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_GetVlan
*  Description: 获取接口VLAN使能状态
*        Input: ULONG ulIfIndex:接口索引
*       Output: ULONG *pulVlanFlag:使能状态
*       Return: VOS_OK 成功
*               错误码 失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-09-04   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetVlan(ULONG ulIfIndex, ULONG * pulVlanFlag);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetOmIpHook
*  Description: 注册特殊ARP代理的逻辑IP（OMIP）地址判断钩子函数
*        Input: gpfTCPIPSpecialArpProxyIP pfHookFunc:逻辑IP（OMIP）地址判断钩子函数
*       Output:
*       Return: VOID
*      Caution: pfHookFunc不为空，表示注册，为空表示注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-14   z00104207               Create
*
*******************************************************************************/
extern VOID   TCPIP_RegFuncGetOmIpHook(gpfTCPIPSpecialArpProxyIP pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_GetEtharpMac
*  Description: 获取以太physical地址
*        Input: ULONG ulIfIndex:接口索引
*       Output: UCHAR *pucMac:返回接口对应的physical地址
*       Return: VOS_OK  操作成功
*               错误码  失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-16   Zheng Sen Huo (00104483)  Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetEtharpMac(ULONG ulIfIndex, UCHAR *pucMac);
/*******************************************************************************
*    Func Name: TCPIP_ShowEtharpStatistic
*  Description: 获取接口以太统计
*        Input: CHAR *pName:接口名称
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-18   x00100259               Create
*
*******************************************************************************/
extern VOID   TCPIP_ShowEtharpStatistic(CHAR *pName);
/*******************************************************************************
*    Func Name: TCPIP_ShowIPConflictTable
*  Description: 显示IP冲突Table
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-04   fuxiaodong(54882)       Create
*
*******************************************************************************/
extern VOID   TCPIP_ShowIPConflictTable(VOID);

/*******************************************************************************
*    Func Name: TCPIP_OpenARPIPConflictInfoTable
* Date Created: 2013-11-18
*       Author: Chandra (00902193)
*  Description: Function to open the IPConflicttable with waitlist.
*        Input: None
*       Output: ULONG *pulConflictInfoHandle: Handle to access the table.
*       Return: VOS_OK / Error
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-18  Chandra (00902193)       Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenARPIPConflictInfoTable(UINTPTR *pulConflictInfoHandle);

/*******************************************************************************
*    Func Name: TCPIP_GetARPIPConflictInfo
* Date Created: 2013-11-18
*       Author: Chandra (00902193)
*  Description: Function to get the IPConflicttable entry.
*        Input: 
*               ULONG ulConflictInfoHandle: Handle to access the table.
*               
*       Output: 
*               ETHARP_IP_CONFLICT_INFO_S *pstIPConflictInfo: IPConflict table entry
*
*       Return: VOS_OK / Error
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-18  Chandra (00902193)       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetARPIPConflictInfo(UINTPTR ulConflictInfoHandle, ETHARP_IP_CONFLICT_INFO_S *pstIPConflictInfo);

/*******************************************************************************
*    Func Name: TCPIP_CloseARPIPConflictInfoTable
* Date Created: 2013-11-18
*       Author: Chandra (00902193)
*  Description: Function to close the IPConflicttable with waitlist.
*        Input: ULONG ulConflictInfoHandle: Handle to close the table.
*       Output: 
*       Return: VOS_OK / Error
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-18  Chandra (00902193)       Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseARPIPConflictInfoTable(UINTPTR  ulConflictInfoHandle);

/*******************************************************************************
*    Func Name: TCPIP_AddStaticArpWithVlanAndPortIfIndex
* Date Created: 2008-11-14
*       Author: wuhailan
*  Description:
*        Input: ULONG ulIpAddr:地址(主机序)
*               UCHAR *pucMacAddr:physical地址
*               USHORT usVID:VLAN ID (1~4094)
*               ULONG ulPortIfIndex:二层端口接口索引
*       Output:
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-14   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_AddStaticArpWithVlanAndPortIfIndex(ULONG ulIpAddr, UCHAR *pucMacAddr,USHORT usVID, ULONG ulPortIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_ShowARPByVrf
* Date Created: 2009-02-28
*       Author: wangchengyang
*  Description: 显示指定VRF的ARP表项
*        Input: CHAR *pszVrfName VRF名称
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-09  wangchengyang    Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowARPByVrf(CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: TCPIP_ShowARPByFilter
* Date Created: 2009-02-28
*       Author: wangchengyang
*  Description: 显示指定VRF的ARP表项
*        Input: CHAR *pszVrfName VRF名称
*               ULONG ulFilterMode
*               ULONG ulIfIndex
*               ULONG vlValid
*               ULONG ulIpAddr
*               UCHAR *ucMac
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-09  wangchengyang    Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowARPByFilter(CHAR *pszVrfName,ULONG ulFilterMode, ULONG ulIfIndex, ULONG ulValid, ULONG ulIpAddr, UCHAR* ucMac);

/*******************************************************************************
*    Func Name: TCPIP_SendUserArp
* Date Created: 2008-10-11
*       Author: z43740
*  Description: 根据用户指定的参数发送ARP请求报文
*        Input: ULONG ulIfIndex : 接口索引
*               ULONG ulDstIP   : 目的IP
*               ULONG ulIsUnicast: 广播/单播标记 0 广播 1 单播
*       Output:
*       Return: VOS_OK            发送成功
*               其它              发送失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-11   z43740                  Create
*
*******************************************************************************/
extern ULONG TCPIP_SendUserArp(ULONG ulIfIndex, ULONG ulDstIP, ULONG ulIsUnicast);

/*******************************************************************************
*    Func Name: TCPIP_GetUserArpStat
* Date Created: 2008-10-19
*       Author: z43740
*  Description: 获取用户发送ARP报文统计信息
*        Input: ULONG ulIfIndex: 接口索引
*       Output: USERARPSTAT_S* pstStat: 统计信息
*       Return: VOS_OK                  成功
*               其它                    失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-19   z43740                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetUserArpStat(ULONG ulIfIndex, USERARPSTAT_S* pstStat);

/*******************************************************************************
*    Func Name: TCPIP_ClearUserArpStat
* Date Created: 2008-10-19
*       Author: z43740
*  Description: 清除用户发送ARP报文统计信息
*        Input: ULONG ulIfIndex: 接口索引
*       Output:
*       Return: VOS_OK                  成功
*               其它                    失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-19   z43740                  Create
*
*******************************************************************************/
extern ULONG TCPIP_ClearUserArpStat(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ShowUserArpStat
* Date Created: 2008-10-19
*       Author: z43740
*  Description: 显示用户发送ARP报文统计信息
*        Input: CHAR* pszIfName: 接口名
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-19   z43740                  Create
*
*******************************************************************************/
extern VOID TCPIP_ShowUserArpStat(CHAR* pszIfName);

/*******************************************************************************
*    Func Name: TCPIP_SendArpPkt
* Date Created:
*       Author:
*  Description: 根据用户指定的参数发送ARP请求报文
*        Input:
*       Output:
*       Return: VOS_OK            发送成功
*               其它              发送失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-29   q62011                  Create
*
*******************************************************************************/
extern ULONG TCPIP_SendArpPkt(ULONG ulIfIndex, ULONG ulSrcIpAddr,ULONG ulDstIpAddr,
                              UCHAR* pucDstMac,USHORT usVid,BOOL_T bIsReply);

/*******************************************************************************
*    Func Name: TCPIP_SetFreeArpSendTimes
* Date Created: 2009-01-15
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: 配置指数退避算法发送免费ARP时同一地址发送的最大次数
*        Input: ULONG ulTimes:最大次数
*       Output:
*       Return: 成功返回VOS_OK，失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-15   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern ULONG TCPIP_SetFreeArpSendTimes(ULONG ulTimes);


/*******************************************************************************
*    Func Name: TCPIP_SetFreeArpSendTotalNum
* Date Created: 2009-01-15
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: 配置指数退避算法发送免费ARP时每秒发送的最大次数
*        Input: ULONG ulNum:发送次数
*       Output:
*       Return: 成功返回VOS_OK，失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-15   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
extern ULONG TCPIP_SetFreeArpSendTotalNum(ULONG ulNum);

/*******************************************************************************
*    Func Name: TCPIP_GetFreeArpSendTimesAndTotalNum
* Date Created: 2009-01-16
*       Author: ZhengSenHuo/GeXianJun(104483/121208)
*  Description: 获取指数退避数法发送免费ARP时同一地址发送的最大次数
*                           和发送免费ARP时每秒发送的最大次数
*        Input:
*       Output: ULONG *pulTimes:   发送免费ARP时同一地址发送的最大次数
*               ULONG *pulTotalNum:发送免费ARP时每秒发送的最大次数
*       Return: 成功返回VOS_OK，失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-16   ZhengSenHuo/GeXianJun(104483/121208)  Create
*
*******************************************************************************/
ULONG TCPIP_GetFreeArpSendTimesAndTotalNum(ULONG *pulTimes,ULONG *pulTotalNum);


extern VOID TCPIP_ETHARP_SendGratuitousArp(MBUF_S *pMBuf, UCHAR* szSrcMacAddr,
                                        UCHAR* szProAddr,USHORT usOpType,
                                        ULONG ulIfIndex);


extern ULONG TCPIP_ETHARP_EtherOutput( MBUF_S *pMbuf );

/*******************************************************************************
*    Func Name: TCPIP_RegFuncArpInputNotifyHook
* Date Created: 2009-01-03
*       Author: z43740
*  Description: 注册ARP报文接收通知回调函数
*        Input: ETHARP_ARPINPUT_NOTIFY_HOOK pfHook: 回调函数指针
*       Output:
*       Return: VOS_OK                  注册成功
*      Caution: pfHook不为空，表示注册，为空表示注销
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-03   z43740                  Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncArpInputNotifyHook(ETHARP_ARPINPUT_NOTIFY_HOOK pfHook);

/*******************************************************************************
*    Func Name: TCPIP_SetArpLogSwitch
* Date Created: 2009-02-17
*       Author: z43740
*  Description: 设置指定端口ARP报文收发日志开关
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulLogSwitch: 开关值，0 关闭，1 打开
*       Output:
*       Return: VOS_OK               成功
*               ETHARP_ERROR_SWITCH  开关值非法
*      Caution: 1.该接口将指定端口上发送的ARP请求和对应应答报文，对收到的ARP请求报文
*                 的相应报文简要信息记录到日志中
*               2.需要注意ARP报文收发的频率，请慎重使用本功能
*               3.本日志开关不支持备份，如果产品需要在主备倒换后，也可以记录日志，则
*                 需要产品在主备倒换的时候打开相应的开关
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-17   z43740                  Create
*
*******************************************************************************/
extern ULONG TCPIP_SetArpLogSwitch(ULONG ulIfIndex, ULONG ulLogSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetArpLogSwitch
* Date Created: 2009-02-17
*       Author: z43740
*  Description: 获取ARP报文日志记录开关
*        Input: ULONG ulIfIndex: 接口索引
*       Output: ULONG* pulLogSwitch: 开关值，0 关闭，1 打开
*       Return: VOS_OK                  成功
*               ETHARP_NULL_POINTER     参数指针为空
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-17   z43740                  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetArpLogSwitch(ULONG ulIfIndex, ULONG* pulLogSwitch);

/*****************************************************************************
 函 数 名  : TCPIP_GetEthHeadLen
 功能描述  : 获取eth头
 输入参数  : MBUF_S* pMBuf  mbuf指针
             ULONG ulIfIndex    接口索引
 输出参数  : ULONG *pulEthHeadLen  eth头长度
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年4月27日
    作    者   : w62223
    修改内容   : 新生成函数

*****************************************************************************/
extern ULONG TCPIP_GetEthHeadLen(MBUF_S* pMBuf,ULONG ulIfIndex,ULONG *pulEthHeadLen);

/*******************************************************************************
*    Func Name: TCPIP_SetUnarpCapability
* Date Created: 2009-05-19
*       Author: qinyun62011
*  Description: 使能/去使能UNARP功能
*        Input: ULONG ulFlag:标志(1-使能；0-去使能)
*       Output:
*       Return: 成功返回VOS_OK
*               失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-05-19   qinyun62011             Create
*
*******************************************************************************/
extern ULONG TCPIP_SetUnarpCapability(ULONG ulFlag);

/*******************************************************************************
*    Func Name: TCPIP_GetUnarpCapability
* Date Created: 2009-05-20
*       Author: qinyun62011
*  Description: 获取使能去使能标志
*        Input:
*       Output: ULONG *pulFlag:使能去使能标志
*       Return: 成功返回VOS_OK
*               失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-05-20   qinyun62011             Create
*
*******************************************************************************/
extern ULONG TCPIP_GetUnarpCapability(ULONG *pulFlag);

/*******************************************************************************
*    Func Name: TCPIP_ShowUnarpCapability
* Date Created: 2009-05-20
*       Author: qinyun62011
*  Description: 显示使能去使能标志
*        Input: VOID
*       Output:
*       Return: 成功返回VOS_OK
*               失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-05-20   qinyun62011             Create
*
*******************************************************************************/
extern VOID TCPIP_ShowUnarpCapability(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SendUnArp
* Date Created: 2009-05-19
*       Author: qinyun62011
*  Description: 发送UNARP报文
*        Input: ETHARP_UNARPINFO_S *pstUnarpInfo:入参结构
*       Output:
*       Return: 成功返回VOS_OK
*               失败返回错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-05-19   qinyun62011             Create
*
*******************************************************************************/
extern ULONG TCPIP_SendUnArp(ETHARP_UNARPINFO_S *pstUnarpInfo);

/****************************************************************************
*    Func Name: TCPIP_SetIPZeroArpSwitch
* Date Created: 2008-08-26
*       Author: wuhailan
*  Description: 设置是否处理地址为0的ARP请求报文开关
*        Input: ULONG ulSwitch:开关,0 关闭, 1 打开, 默认关闭
*       Output: 
*       Return: VOS_OK:成功 其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-26   wuhailan         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIPZeroArpSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetIPZeroArpSwitch
* Date Created: 2009-09-22
*       Author: wuhailan103194
*  Description: 获取是否处理地址为0的ARP请求报文开关
*        Input:
*       Output: ULONG *pulSwitch:返回的开关值
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-22   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIPZeroArpSwitch(ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SetArpStrictLearnSwitch
* Date Created: 2009-09-15
*       Author: wuhailan103194
*  Description: 支持严格学习ARP表项功能开关设置接口
*               使能了严格ARP表项学习后,仅学习自己发送的ARP请求报文的应答报文,
*               其他场景一律不再进行ARP表项学习.并且不做ARP回复及其他处理,将直接丢弃报文以防攻击
*        Input: ULONG ulSwitch:开关,0 关闭, 1 打开, 默认关闭
*       Output: 
*       Return: VOS_OK:成功 其他返回失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-15   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetArpStrictLearnSwitch(ULONG ulSwitch);


/*******************************************************************************
*    Func Name: TCPIP_GetArpStrictLearnSwitch
* Date Created: 2009-09-22
*       Author: wuhailan103194
*  Description: 获取严格学习ARP表项功能开关设置接口
*        Input:
*       Output: ULONG *pulSwitch:返回的开关值
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-22   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetArpStrictLearnSwitch(ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_AddDynamicArp
* Date Created: 2008-10-28
*       Author: zhangchunyu(62474)
*  Description: 添加动态ARP
*        Input: ULONG ulIfIndex: 接口索引
*               UCHAR *pucMacAddr: 相关MAC
*               ULONG ulDstIpAddr: 地址,网络序
*       Output:
*       Return:
*      Caution: PTN需求,应用场景:单主控复位,底层NP把保存的动态ARP还原到VISP,静态ARP
*               用老接口还原。
*               该接口只能在主控复位恢复时调用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-28    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_AddDynamicArp(ULONG ulIfIndex, UCHAR *pucMacAddr, ULONG ulDstIpAddr);

/*******************************************************************************
*    Func Name: TCPIP_AddDynamicArpWithVlan
* Date Created: 2013-01-17
*       Author: z00208058
*  Description: 添加动态ARP，指定VLAN ID
*        Input: pstArpInfo:入参结构
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-01-17   z00208058               Create
*
*******************************************************************************/
ULONG TCPIP_AddDynamicArpWithVlan(ARPWITHVLANINFO_S *pstArpInfo);


/*******************************************************************************
*    Func Name: TCPIP_SendArpRequestForVlan
* Date Created: 2008-10-28
*       Author: zhangchunyu(62474)
*  Description: 指定接口发送相应地址ARP请求,用户接口
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulDstIpAddr: 地址,网络序
*       Output:
*       Return: VOS_OK 成功, 其他 失败
*      Caution: 该函数目的是PTN产品配置静态ARP之后，发送到目的地址的ARP请求
*               判断动静态ARP是否存在冲突
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-28    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_SendArpRequestForVlan(ULONG ulIfIndex, ULONG ulDstIpAddr);

/*******************************************************************************
*    Func Name: TCPIP_CheckSrcMacErr
* Date Created: 2009-7-14
*       Author: l00143205
*  Description: 校验ARP报文源MAC的合法性
*        Input: ULONG* ucSrcMacAddr: 源MAC
*       Output:
*       Return: VOS_OK: MAC合法
*               其他:   MAC非法
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-7-14    L(00143205)      Create the first version.
*
*******************************************************************************/
ULONG TCPIP_CheckSrcMac(UCHAR *ucSrcMacAddr);

/*******************************************************************************
*    Func Name: TCPIP_SetARPExpireTimeByIndex
* Date Created: 2009-6-4
*       Author: LY(57500)
*  Description: 设置ARP超时时间
*        Input: ULONG ulTime: 设置的时间
*               ULONG ulIfIndex: 设置的接口索引
*       Output:
*       Return: VOS_OK: 设置成功
*               其他:   设置失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-6-4    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG TCPIP_SetARPExpireTimeByIndex(ULONG ulTime, ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetARPExpireTimeByIndex
* Date Created: 2009-6-4
*       Author: LY(57500)
*  Description: 获取接口的arp超时时间
*        Input: ULONG* pulTime: 保存输出arp超时时间
*               ULONG ulIfIndex: 接口索引
*       Output:
*       Return: VOS_OK: 获取成功
*               其他:   获取失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-6-4    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG TCPIP_GetARPExpireTimeByIndex(ULONG* pulTime, ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SetVlanTag
* Date Created: 2008-5-8
*       Author: zhangchunyu(62474)
*  Description: 设置报文中VLAN ID，用户接口
*        Input: ULONG ulIfIndex: 接口的索引号
*               ULONG ulVlanTag: vLandId.仅仅只是VLANID,必须是主机序
*       Output:
*       Return:
*      Caution:如果ulVlanTag等于零，并且使能了VLAN 功能，那么报文中VLAN 头部信息由产品适配
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-5-8    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_SetVlanTag(ULONG ulIfIndex , ULONG ulVlanTag);

/*******************************************************************************
*    Func Name: TCPIP_GetVlanTag
* Date Created: 2008-5-8
*       Author: zhangchunyu(62474)
* Description :  获取接口VLAN ID
* Others      :
* Input       : ulIfIndex:接口的索引号
*               pulVlanTag: 输出参数
* Output      : pulVlanTag: 返回vlanID
* Return      : 成功:0  其它表示失败
* Caution     :
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-5-8    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_GetVlanTag(ULONG ulIfIndex, ULONG* pulVlanTag);

/*******************************************************************************
*    Func Name: TCPIP_ShowArpInfoByIf
* Date Created: 2009-11-13
*       Author: zhangchi(00142640)
*  Description: 显示接口ARP信息
*        Input: CHAR *szIfName:接口名
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-13   zhangchi(00142640)      Create
*
*******************************************************************************/
extern VOID TCPIP_ShowArpInfoByIf(CHAR *szIfName);
/*******************************************************************************
*    Func Name: TCPIP_RegFunc1xInputHook
* Date Created: 2009-12-14
*       Author: Gexianjun/h00121208
*  Description: 注册Eth模块处理802.1X协议报文钩子函数
*        Input: EAPOL_RECV_PKT_HOOK  pfEAPoL_RecvPkt_Hook: 处理802.1X报文钩子函数
*       Output: 
*       Return: 成功VOS_OK;失败错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-14   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFunc1xInputHook(EAPOL_RECV_PKT_HOOK  pfEAPoL_RecvPkt_Hook);

/*******************************************************************************
*    Func Name: TCPIP_UnRegFunc1xInputHook
* Date Created: 2009-12-14
*       Author: Gexianjun/h00121208
*  Description: 解注册Eth模块处理802.1X协议报文钩子函数
*        Input: VOID
*       Output: 
*       Return: 成功VOS_OK;失败错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-14   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_UnRegFunc1xInputHook(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SendMacFrameOverEth
* Date Created: 2009-12-14
*       Author: Gexianjun/h00121208
*  Description: 调用底层发送函数发送802.1X报文接口
*        Input: ULONG ulIfIndex:  接口索引
*               MBUF_S * pstMbuf: 发送报文MBUF
*       Output: 
*       Return: 成功VOS_OK;失败错误码
*      Caution: 发送失败由调用者释放MBUF
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-14   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_SendMacFrameOverEth (ULONG ulIfIndex, MBUF_S * pstMbuf);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncEtharpDealHook
* Date Created: 2009-9-8
*       Author: LY(57500)
*  Description: 产品注册etharp报文的钩子函数
*        Input: ULONG ulInOrOut: 发送或接收
*               ULONG ulPriority: 优先级，值域有效，值越大优先级越高
*               ETHARP_INTERMEDIATE_HOOK_FUNC pfHookFunc: 待注册钩子
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-8    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncEtharpDealHook(ULONG ulInOrOut, ULONG ulPriority, ETHARP_INTERMEDIATE_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_UnRegFuncEtharpDealHook
* Date Created: 2009-9-8
*       Author: LY(57500)
*  Description: 产品解注册etharp报文的钩子函数
*        Input: ULONG ulInOrOut: 发送或接收
*               ETHARP_INTERMEDIATE_HOOK_FUNC pfHookFunc: 待解注册钩子
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-8    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG TCPIP_UnRegFuncEtharpDealHook(ULONG ulInOrOut, ETHARP_INTERMEDIATE_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncIsNatIPAddrHook
* Date Created: 2010-05-20
*       Author: zhangchunyu(62474)
*      Purpose: 注册是否是NAT 地址回调函数
*  Description: 如果接口使能NAT功能,支持接口回答外面ARP请求,即收到ARP请求判断是否是该接口NAT使用的地址,
*               如果是则回应本接口的MAC
*        Input: ETHARP_IS_NAT_IPADDR_HOOK_FUNC pfHookFunc: 注册是否是NAT IP回调函数<非空函数指针>
*       Output: 
*       Return: 成功:VOS_OK
*               失败:其他
*      Caution: 
*        Since: V100R008C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-20   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncIsNatIPAddrHook(ETHARP_IS_NAT_IPADDR_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncEthBeforeAddVlanTagHook
* Date Created: 2010-11-03
*       Author: y171195(z171897)
*  Description: 注册封装Vlan首部前处理回调函数
*        Input: ETH_BEFORE_ADD_VLANTAG_HOOK  pfEthBeforeAddVlanTagHook: 回调函数
*       Output: 
*       Return: 成功:VOS_OK
*               失败:其他
*      Caution: 1.该钩子函数支持动态注册和解注册,所以产品必须在协议栈启动之后才能
*                 调用该接口注册和解注册.
*               2.该回调钩子函数中不能使用产品的信号量，否则可能会和VISP的信号量产生死锁。
*               3.为支持DHCP VLAN Scanning功能新增该接口.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-03   y171195(z171897)              Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncEthBeforeAddVlanTagHook(ETH_BEFORE_ADD_VLANTAG_HOOK  pfEthBeforeAddVlanTagHook);

/*******************************************************************************
*    Func Name: TCPIP_SetUnicastARPCount
* Date Created: 2011-06-01
*       Author: zhaoyue00171897/shuxieliu00176784
*  Description: 设定结点老化时发送单播ARP次数
*        Input: ULONG ulCount:结点老化时发送单播ARP次数
*       Output: 
*       Return: VOS_OK 成功
*               其他   失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-01   z00171897/s00176784     Create
*
*******************************************************************************/
ULONG TCPIP_SetUnicastARPCount(ULONG ulCount);

/*******************************************************************************
*    Func Name: TCPIP_GetUnicastARPCount
* Date Created: 2011-06-01
*       Author: zhaoyue00171897/shuxieliu00176784
*  Description: 查询结点老化时发送单播ARP次数
*        Input: 
*       Output: ULONG *pulCount:结点老化时发送单播ARP次数
*       Return: VOS_OK 成功
*               其他   失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-01   z00171897/s00176784     Create
*
*******************************************************************************/
ULONG TCPIP_GetUnicastARPCount(ULONG *pulCount);

/*******************************************************************************
*    Func Name: TCPIP_SetARPCapture
* Date Created: 2011-06-02
*       Author: zhaoyue00171897
*  Description: 设置ARP报文收发队列长度
*        Input: ULONG ulIfIndex: 接口索引，必须是以太类型的主接口
*               ULONG ulRcvCaptureQueLen: 接收队列长度，取值范围[0, 128]
*               ULONG ulSndCaptureQueLen: 发送队列长度，取值范围[0, 128]
*       Return: VOS_OK           成功
*               其他             失败
*      Caution: 
*               不支持VLAN IF
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-02   zhaoyue00171897         Create
*
*******************************************************************************/
ULONG TCPIP_SetARPCapture(ULONG ulIfIndex, ULONG ulRcvCaptureQueLen, ULONG ulSndCaptureQueLen);

/*******************************************************************************
*    Func Name: TCPIP_GetARPCapture
* Date Created: 2011-06-02
*       Author: zhaoyue00171897/shuxieliu00176784
*  Description: 获取ARP报文收发队列长度
*        Input: ULONG ulIfIndex: 接口索引
*       Output: ULONG *pulRcvCaptureQueLen: 接收队列长度
*               ULONG *pulSndCaptureQueLen: 发送队列长度
*       Return: VOS_OK    成功
*               其他      失败
*      Caution: 不支持VLAN IF
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-02   zhaoyue00171897         Create
*
*******************************************************************************/
ULONG TCPIP_GetARPCapture(ULONG ulIfIndex, ULONG *pulRcvCaptureQueLen, ULONG *pulSndCaptureQueLen);

/*******************************************************************************
*    Func Name: TCPIP_GetARPCaptureQue
* Date Created: 2011-06-02
*       Author: zhaoyue00171897/shuxieliu00176784
*  Description: 获取以太/Trunk主接口上保存的ARP报文队列
*        Input: ULONG ulIfIndex: 接口索引
*       Output: ULONG *pulRcvQueMbufNum: 接收报文队列中的报文个数
*               MBUF_S **ppstRcvMbuf: ARP报文接收队列
*               ULONG *pulSndQueMbufNum: 发送报文队列中的报文个数
*               MBUF_S **ppstSndMbuf: ARP报文发送队列
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-02   zhaoyue00171897         Create
*
*******************************************************************************/
ULONG TCPIP_GetARPCaptureQue(ULONG ulIfIndex, ULONG *pulRcvQueMbufNum, MBUF_S **ppstRcvMbuf,
                             ULONG *pulSndQueMbufNum, MBUF_S **ppstSndMbuf);

/*******************************************************************************
*    Func Name: TCPIP_SetArpExpireOffsetTime
* Date Created: 2013-12-04
*       Author: mafeng 59090
*  Description: 设置ARP最大老化偏移时间
*        Input: UCHAR ucTime: 0 不偏移，[30,60] 偏移老化时间取值范围
*       Return: VOS_OK           成功
*               其他             失败
*      Caution: 当配置为0时ARP表项按照配置的老化时间进行老化，当非0时随机取一个
*               0~配置值之间的数字作为老化时间的偏移值。
*               本API仅对配置完成后生成的ARP表项有效，配置之前的ARP老化时间不刷新。

*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-04   mafeng 59090            Create
*
*******************************************************************************/
ULONG TCPIP_SetArpExpireOffsetTime(UCHAR ucTime);

/*******************************************************************************
*    Func Name: TCPIP_GetArpExpireOffsetTime
* Date Created: 2013-12-04
*       Author: mafeng(59090)
*  Description: 获取ARP最大老化偏移时间
*        Input: UCHAR *pucTime:0 不偏移 非0 偏移时间(s)
*       Return: VOS_OK 成功
*               错误码 失败
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-04   mafeng(59090)           Create
*
*******************************************************************************/
ULONG  TCPIP_GetArpExpireOffsetTime(UCHAR *pucTime);

/*******************************************************************************
*    Func Name: TCPIP_SetArpStrictLearnSwitchByIntf
* Date Created: 2014-04-03
*       Author: likaikun213099
*  Description: 支持严格学习ARP表项功能接口开关设置
*               使能了严格ARP表项学习后,仅学习自己发送的ARP请求报文的应答报文,
*               其他场景一律不再进行ARP表项学习.并且不做ARP回复及其他处理,将直接丢弃报文以防攻击
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulSwitch:  开关,0 关闭, 1 打开, 默认关闭
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-03   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_SetArpStrictLearnSwitchByIntf(ULONG ulIfIndex, ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetArpStrictLearnSwitchByIntf
* Date Created: 2014-05-27
*       Author: likaikun213099
*  Description: 
*        Input: ULONG ulIfIndex:
*               ULONG *pulSwitch:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-27   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_GetArpStrictLearnSwitchByIntf(ULONG ulIfIndex, ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_DelArpEntryByVrfIndex
* Date Created: 2014-11-20
*       Author: caiqizheng
*  Description: 删除某个指定VRF的ARP表项
*        Input: ULONG ulIpAddr:地址
*               ULONG ulScope:范围
*               ULONG ulVrfIndex:vrf索引
*       Output: 无
*       Return: 成功或错误码
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-20   caiqizheng           VISP1.7C03 VRF,Create
*******************************************************************************/
extern ULONG TCPIP_DelArpEntryByVrfIndex(ULONG ulIpAddr,ULONG ulScope,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetArpEntryByIntfAndIPAddr
* Date Created: 2014-12-16
*       Author: likaikun213099
*  Description: 指定接口和IP地址获取ARP表项
*        Input: ULONG ulIfIndex:
*               ULONG ulIPAddr:
*       Output: ARPINFO_S *pstARPInfo:
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-16   likaikun213099          Create
*
*******************************************************************************/
ULONG  TCPIP_GetArpEntryByIntfAndIPAddr(ULONG ulIfIndex, ULONG ulIPAddr, ARPINFO_S *pstARPInfo);

/*******************************************************************************
*    Func Name: TCPIP_DelDynamicArpEntryByIntf
* Date Created: 2014-12-16
*       Author: likaikun213099
*  Description: 删除指定接口和IP地址的动态ARP表项（静态ARP配置的时候没有接口信息）
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulIpAddr:IP地址(主机顺序)
*       Output: 无
*       Return: VOS_OK:成功
*               错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-16   likaikun213099          Create
*
*******************************************************************************/
ULONG  TCPIP_DelDynamicArpEntryByIntf(ULONG ulIfIndex, ULONG ulIpAddr);

/*******************************************************************************
*    Func Name: TCPIP_ShowARPTimerListInfo
* Date Created: 2014-12-23
*       Author: likaikun213099
*  Description: ARP老化时间节点信息查询
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-23   likaikun213099          Create
*
*******************************************************************************/
VOID TCPIP_ShowARPTimerListInfo(VOID);


ULONG TCPIP_RegFuncGetARPRcvIfIndexHook(ETHARP_GETARPRCVIFINDEX_HOOK_FUNC pfHookFunc);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ETHARP_API_H_ */

