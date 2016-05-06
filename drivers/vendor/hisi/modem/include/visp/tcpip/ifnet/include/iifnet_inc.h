
#include  "if_def.h"
#include "tcpip/ifnet/include/ifnet_api.h"

#ifndef _IF_IIFNET_INC_H_
#define _IF_IIFNET_INC_H_

#ifdef  __cplusplus
extern "C"{
#endif


/************************************************************************
 *                             锁定开始(Begin)                          *
 * ......           以下为锁定部分，产品不得修改  luohanjun       ......*
 * ......              (注意: 只能从锁定结束部分之后修改)         ......*
 * ......                                                         ......*
 ************************************************************************/

#define MAX_IFCMD_NAME_LEN                     47
#define MAX_INTERFACE_SIMPLENAME_LEN           20       /* 最大的简单接口名长度 */

#define IF_MAX_INDEX                           100000   /* 最大的接口数目 */


/***********************************************************************/
/*usIfState value: 必须设置正确*/
#define  IF_UP                 0x01
#define  IF_DOWN               0x02
#define  IF_SETMAC             0x04
#define  IF_UNBIND             0x08
#define  IF_STATES             IF_UP | IF_DOWN
#define  OSI_UP                0x10    /*当OSICP协商成功，通知产品接口状态变成UP (光网络路由模块使用)*/
#define  OSI_DOWN              0x20    /*当OSICP协商失败，通知产品接口状态变成DOWN (光网络路由模块使用)*/

/* #endif */ /* VRP_MODULE_RTPRO_RM */

#ifndef FORWARDIFENTRY
#define FORWARDIFENTRY
#endif

#ifndef EXTENDIFENTRY
#define EXTENDIFENTRY
#endif

typedef ULONG (* ENQUEUE_PF)(MBUF_S *);
typedef ULONG (*IF_PRETREATFUN)(ULONG ulIfindex);
typedef VOID  (*pfReceiverNotifyFun)(MBUF_S *,ULONG );

/*
typedef struct tagIFNET;
typedef struct VLINKSTATUS_S;
*/

/*公共接口声明
DECLARE_INTERFACE (IIF_IFS_IntFun) //外部组件IFNET公共接口
{
    IUNKNOWN_METHODS
    //创建各层自有数据，并初始化
    METHOD_(ULONG , pfIF_InitIF) (IFNET_S* pIf, ULONG ulPosition, ULONG* pulRet);
    //启动各层，触发UP事件，执行各层组件的buildrun，通过控制函数进行事件传递等操作，可以不执行任何操作。
    METHOD_(ULONG , pfIF_BuildrunIF) (IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);
    //接口命令屏蔽，主要是针对链路层，其他层必须提供空函数。
    METHOD_(ULONG , pfIF_HideCommand) (IFNET_S* pIf, ULONG ulPosition, ULONG* pulRet);
    //释放指定层控制块。
    METHOD_(ULONG , pfIF_FreeControlBlock) (IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);

};
*/

#ifndef DNS_DOMAIN_LIST_NAME_LENGTH
#define DNS_DOMAIN_LIST_NAME_LENGTH 20
#endif

#ifndef DHCP4C_DOMAINNAME_SIZE
#define DHCP4C_DOMAINNAME_SIZE DNS_DOMAIN_LIST_NAME_LENGTH
#endif

#ifndef DHCP4C_DNSIP_NUM
#define DHCP4C_DNSIP_NUM 6
#endif

#ifndef DHCP4C_ROUTER_NUM
#define DHCP4C_ROUTER_NUM 8
#endif

typedef struct tagPPP_VLINK_INFO
{
    ULONG ulIfIndex;
    ULONG ulLocalIp;
    ULONG ulRemoteIp;
    ULONG aulDNSIP[DHCP4C_DNSIP_NUM];
    ULONG ulFlag;
    ULONG ulVlinkIndex;
    ULONG ulMtu;
}PPP_VLINK_INFO_S;

typedef struct tagDHCP4C_VIRTUAL_INFO
{
    ULONG ulIfIndex;
    ULONG ulDHCPClientIP;
    ULONG ulDHCPClientIPMask;
    ULONG aulDNSIP[DHCP4C_DNSIP_NUM];
    ULONG aulGatewayIP[DHCP4C_ROUTER_NUM];
    ULONG ulFlag;
    UCHAR ucDomainName[DHCP4C_DOMAINNAME_SIZE];
}DHCP4C_VIRTUAL_INFO_S;

/**********************************************************
为兼容其它模块 ，
请不要改动，并在结构的最后添加字段
***********************************************************/
typedef struct tagIFNET
{

    /* 以下为描述接口的基本结构 */
    /* 接口名、接口索引、槽号在创建IFNET时设置 */
    CHAR  if_szIfName[ IF_MAX_INTERFACE_NAME_LEN+1];
    CHAR  if_szDescript[ MAX_INTERFACE_DESCRIPTION_LEN+1 ]; /* 接口描述字符串 */
    UCHAR ucPadding_1[3];

    /* if_ulIfIndex字段各部分的含义
     *         6bit                19bit                  4bit               3bit
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-
     * +    槽号(Slot)    |      偏移(IndexOff)     |  同步号(SynFlag) | 类型(Type) +
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-
     *                                                接口每被删除一次，  接口类型
     *                                                    其值加1
     */
    ULONG if_ulIfIndex;             /* VISP私有索引结构 */
    ULONG if_ulProductIfIndex;      /* 与产品相关的接口索引 */

    ULONG if_ulSlotNum;         /* 高16位为卡号，低16位为槽号 */
    ULONG if_ulTopIfIndex;      /* 该接口的配置父亲的索引 */
    ULONG if_ulNetIfIndex;      /* 该接口的网络层策略父亲的索引 */

    /* 网络层控制块 */
    UINTPTR if_ulIpIf;              /* IP控制块 */
    UINTPTR if_ulIpv6If;            /* IPv6 Control Block */
    ULONG if_ulIsisFlag ;     /* 接口下ISIS使能标志 */

    /* 端口属性 */
    ULONG if_ulSpoofing;       /* Spoofing 标识，1表示具有 spoofing 特性, 0表示不具有这个特性 */
    /*
     * &IF_MOVING      表示该端口可被删除
     * &IF_TEMPIF      临时接口标志
     * &IF_NOCONFIG    接口不可配置
     * &IF_INVISIBLE   接口不可显示( 不可显示接口信息 )
     * 缺省状态是 不可删除、非临时接口、可见、可配置
     */
    ULONG if_ulMoving;
    ULONG if_ulShutdown;            /* shutdown标识,&IF_SHUTDOWN非空表示执行了shutdown操作，否则没有执行 */
    ULONG if_ulSubIndex;            /*  0 表示非子接口；非0 表示子接口(子接口编号) */
    ULONG if_ulSubIfNum;            /*  该接口下配置的子接口数 */
    ULONG if_ulLineProtocol;        /* 端口封装的链路层协议 */
    ULONG if_ulLineEncapsulation;   /* 端口封装的链路层封装DTE还是DCE,以及支持的协议*/
    /* ULONG Basic_if_ulProtocolType;   封装的链路层协议明细 */
    ULONG if_ulLineStatus;          /* 端口协议状态, 1 为UP, 2为DOWN*/

    /* 端口物理状态，对于子接口来说，看主接口状态 */
    /* 使能了OAM-3ah功能后，接口的物理状态取决于底层状态与OAM状态的叠加
        如果底层DOWN，则接口物理状态为DOWN；
        如果底层UP，且3ah处于EFMNORMAL或EFMUP则接口物理状态为UP；否则为DOWN；
    */
    ULONG if_ulPhyStatus;

    ULONG if_ulLine6Status; /* 端口协议状态, 1 为UP, 0为DOWN*/
    ULONG if_ulPhyType;             /* 端口的物理属性 */
    ULONG if_ulPortType;            /* 端口的类型 */
    /* 与网络层和路由模块相关的信息 */
    ULONG if_ulBaud;        /* 端口的波特率 */
    ULONG if_ulMTU;         /* 端口的MTU */
    ULONG if_ulCfgMTU;      /* 协商生成的MTU */
    ULONG if_ulFlags;       /* P-P，NBMA，Broadcast ,  表示接口的路由属性 */
    ULONG if_ulSubType;     /* P-P，MP ,  表示子接口的类型 */
    ULONG if_ulKeepAlive;   /* 链路层协商用和链路层探测链路状态用 */
    USHORT if_usLinkUpDownTrapEnable; /* 接口UP/DOWN时发送trap报文的开关 */
    
    /* Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. 修改原因: 支持VLAN配置不一致的告警 */
    USHORT usVlanWarningFlag;         /* Vlan 一致性告警开关,计数值,0表示没有使能该功能,非0表示主接口下使能该功能的子接口数 */

    ULONG if_ulPassive ;              /* 接口的PASSIVE属性,以防止路由泄漏 */
    ULONG if_ulLastChange ;           /* 接口上一次操作状态改变的时间 */
    /*
     * 链路层控制块，增加新的链路层协议时，增加新的协议控制块
     * 使用宏定义实现链路层协议的可裁剪性
     * 实际只有一个链路层控制块
     */
    UINTPTR if_ulLinkLink;    /*  链路层控制块指针,在CE1中保存时隙占用表示数组*/
    UINTPTR if_ulLogicLink;

    /* IFNET的拓扑结构，对外不可见 */
    struct tagIFNET* if_pFather;            /* 子通道指向父通道的指针*/
    struct tagIFNET* if_pSon;               /* 父通道指向第一个子通道的指针 */
    struct tagIFNET* if_pBrother;           /* 子通道指向下一个兄弟的指针*/
    struct tagIFNET* if_pMain;              /* 从接口指向主接口的指针*/
    struct tagIFNET* if_pSub;               /* 主接口指向第一个从接口的指针 */
    struct tagIFNET* if_pConfig;            /* 指向下一个可配置的接口的指针 */
    /* 注册函数指针 */
    /*
     * 上层模块（IPIF_Output()函数和IPXIF_Output()函数）发送报文使用的函数
     * 参数为指向待发送的报文的指针
     */
    ULONG (*if_pfOutput)(MBUF_S *);

    /*
     * 链路层协议在IFNET上注册的将数据传送给链路层的发送函数
     * 参数为指向待发送的报文的指针
     */
    ULONG (*if_pfLLCOutput)(MBUF_S *);

    /*
     * 链路层在IFNET上注册的供上层使用的下行控制函数
     * 第一个参数为指向IFNET的指针
     * 第二个参数为上层传递给链路层的控制命令字
     * 第三个参数为控制数据，由链路层根据控制命令字进行解释
     */
    ULONG (*if_pfLinkDownIOCtl)(struct tagIFNET *,ULONG,CHAR *);

    /*
     * 上层提供给链路层的向上传递控制信息的函数
     * 第一个参数为上层协议标识
     * 第二个参数为指向IFNET的指针
     * 第三个参数为链路层传递给上层的控制命令字
     * 第四个参数为控制数据，由上层根据命令控制字进行解释
     */
    ULONG (*if_pfUpIOCtl)(ULONG,struct tagIFNET *,ULONG,CHAR *);

    /*
     * IFNET提供的基本的链路层向上传递控制信息的函数
     * 第一个参数为上层协议标识
     * 第二个参数为指向IFNET的指针
     * 第三个参数为链路层传递给上层的控制命令字
     * 第四个参数为控制数据，由上层根据命令控制字进行解释
     */
    ULONG (*if_pfLinkUpIOCtl)(ULONG,struct tagIFNET *,ULONG,CHAR *);

    /*
    * IFNET通知路由管理模块接口UP/DOWN的函数
    * 一般情况下，该函数由路由管理模块负责注册
    * BackUp模块注册自己的函数，实现主备切换特性的接口UP/DOWN抑制功能
    * 第一个参数为指向IFNET的指针
    * 第二个参数为接口UP/DOWN的消息命令字
    * 第三个参数为带外数据
    */
    ULONG (*if_pfNotifyRouter)(struct tagIFNET *, ULONG, UINTPTR);

    /*
     * IFNET注册的处理shutdown命令的函数
     * 第一个参数为指向shutdown命令作用的IFNET的指针
     */
    ULONG (*if_pfShutdown)(struct tagIFNET *);

    /*
     * IFNET注册的处理no shutdown命令的函数
     * 第一个参数为指向no shutdown命令作用的IFNET的指针
     */
    ULONG (*if_pfNoShutdown)(struct tagIFNET *);

    /*
     * IFNET注册的删除接口数据结构的函数
    ** 第一个参数为指向删除操作作用的IFNET的指针
    */
    ULONG (*if_pfDelete)(struct tagIFNET *);

/* 以下为转发特性 */
#ifdef FORWARDIFENTRY

    VOID * if_pstNatpt;

    ULONG if_ulMaxFrag;                     /* 底层允许发送的最大报文分片数 */
    MBUF_QUEUE_S if_stFIFOQueue;            /* 如果平台不支持QOS拥塞控制，则用FIFO队列结构取代它 */

    UINTPTR if_ulCryptMapOut;                 /* enc 出策略控制块 */

    void    * if_pToken;


    /* 特性处理函数，对应上面列举的特性 */
    /* 这部分数据结构是可选的*/
    /* 是使用注册在IFNET上的特性处理函数，还是直接使用具体的函数 */
    /* 由具体的特性模块和使用特性的模块协商决定 */
    /* 接口管理模块不作统一规定 */
    /* 。。。。。。*/

#endif /*FORWARDIFENTRY*/

/* 以下为扩展特性 */
#ifdef EXTENDIFENTRY
    /*
    ISDN拨号属性
    必须CC、Q921、Q931同时存在
    */
    /*VRPV3R001M07_IFNET_XHZ_BEG for R.FUNC.IFNET.010 创建pri-group时隙捆绑接口*/
    /*#if ( VRP_MODULE_LINK_ISDN == VRP_YES || VRP_IFNET_ISDN_PRI == VRP_YES )*/
    UINTPTR if_ulUserInfo;            /*接口保存的自有信息块*/
    /*#endif  VRP_MODULE_LINK_ISDN */
    /*VRPV3R001M07_IFNET_XHZ_END for R.FUNC.IFNET.010 创建pri-group时隙捆绑接口 #endif VRP_MODULE_LINK_ISDN */

    /* 物理层控制块，对于没有底层控制块的端口可以充分利用这个指针 */
    UINTPTR if_ulPhyLink;             /* 底层控制块指针 */

    ULONG if_ulLoopBack;    /* 为支持IPv6而从D21同步 */

    /* PPPoE Server控制块 */
    UINTPTR if_ulPPPOE ;
    /* 注册函数指针 */

    /* 底层使用该函数向上层传递报文 */
    /* 第一个参数为指向IFNET的指针 */
    /* 第二个参数为指向接收的报文的指针 */
    ENQUEUE_PF (* if_pfReceived)(struct tagIFNET *,MBUF_S *);

    /* 链路层协议在IFNET上注册的接收函数（从底层） */
    /* 第一个参数为指向IFNET的指针 */
    /* 第二个参数为指向接收的报文的指针 */
    ENQUEUE_PF (* if_pfLinkReceived)(struct tagIFNET *,MBUF_S *);

    /* Qos在IFNET上注册的供底层调用的TransmitDone函数 */
    /* 只有LAPB等特殊的链路层协议需要专门处理 */
    /* 其它的链路层协议将它置为空 */
    /* 第一个参数为指向IFNET的指针 */
    /* 第二个参数为指向底层控制块的指针  */
    /* 第三个参数为指向待发送的报文的指针 */
    ULONG (*if_pfQosTransmitDone)(struct tagIFNET*,UINTPTR, MBUF_S *);

    /* Qos在IFNET上注册的供链路层使用的发送函数，考虑了拥塞控制 */
    /* 第一个参数为指向IFNET的指针 */
    /* 第二个参数为指向底层控制块的指针  */
    /* 第三个参数为指向待发送的报文的指针 */
    ULONG (*if_pfQosTransmit)(struct tagIFNET*, UINTPTR, MBUF_S *);

    /* 底层在IFNET上注册的供链路层使用的发送函数，考虑了拥塞控制 */
    /* 第一个参数为指向底层控制块的指针 */
    /* 第二个参数为指向待发送的报文的指针 */
    ULONG (*if_pfPhyTransmit)(UINTPTR,MBUF_S *);

    /* 底层在IFNET上注册的供上层使用的流程控制函数 */
    /* 第一个参数为指向物理层控制块的指针 */
    /* 第二个参数为传递给底层的控制命令字 */
    /* 第三个参数为控制数据，由底层根据控制命令字进行解释 */
    ULONG (*if_pfPhyIOCtl)(UINTPTR, ULONG, CHAR *);

    /* IFNET提供的供底层使用的链路层流程控制函数 */
    /* IFNET可以使用该函数冒充底层向链路层发送控制信息 */
    /* 第一个参数为指向IFNET的指针 */
    /* 第二个参数为底层传递给链路层的控制命令字 */
    /* 第三个参数为控制数据，由链路层根据控制命令字进行解释 */
    ULONG (*if_pfLinkIOCtl)(struct tagIFNET *,ULONG,CHAR *);

    /* 链路层在IFNET上注册的供底层使用的流程控制函数 */
    /* IFNET可以使用该函数冒充底层向链路层发送控制信息 */
    /* 第一个参数为指向IFNET的指针 */
    /* 第二个参数为底层传递给链路层的控制命令字 */
    /* 第三个参数为控制数据，由链路层根据控制命令字进行解释 */
    ULONG (*if_pfLLCIOCtl)(struct tagIFNET *,ULONG,CHAR *);

    /* 提供给LINE模块的判断给定的IFNET是否能切换成指定封装的函数 */
    /* 加入了Dialer Group的异步com口不允许切换成SLIP协议 */
    /* 第一个参数为指向IFNET结构的指针 */
    /* 第二个参数为指定的封装 */
    ULONG (*if_pfIsIfSupportEncap)(struct tagIFNET *,ULONG);

/* 以太网与PPPOE之间传递控制流程的函数指针 */
    ULONG (*if_pfPPPOEIOCtl)(UINTPTR, ULONG, CHAR *);

    ULONG if_ulVAInfo;           /* 纪录VT接口当前活动VA的类型(最高8位)和所在的槽位(低24位)*/

    ULONG if_ulBandWidth;       /* 纪录接口缺省的bandwidth, 等于接口初始化时的波特率 */
    ULONG if_ulCfgBandWidth;    /* 纪录接口配置的bandwidth, 若不曾配置, 该值为0 */

    UINTPTR if_pMultilinkInterface;  /* MP子通道上记录的父通道Mp-Group接口名指针 */

    ULONG if_ulSAstatus; /*标志同异步com口的同步/异步状态*/

#endif /*EXTENDIFENTRY*/


    /* 为了与其它模块兼容，请在以下添加字段。 */

    ULONG if_ulType;          /* 接口类型 for VISP add by luohanjun 2004/03/24 */

    /* IFNET通知路由管理模块接口UP/DOWN的函数 */
    ULONG (*if_pfNotifyRouter6)(struct tagIFNET *, ULONG, UINTPTR);

    /* ULONG (*if_pfVLINKIOCtl)(struct VLINKSTATUS_S * , VOID *);*/ /*add by luohanjun for VLINK*/

    ULONG if_ulBaudHigh  ; /*x36530 syn d030 20050317*/

    VOID* Forward_if_pstSec ;

    UINTPTR pQueueInfo;    /*指向QoS控制块，NULL表示没有使用QoS.*/
    ULONG ulHAflag ; /*HA标记，取值可以是这两者的组合
                     # define  IFNET_BAK_NO_RECOVER   0x01  接口未内部平滑
                     # define  IFNET_BAK_CHECK_OVER  0x02 接口已外部平滑
                     */
    ULONG if_ulIfNum;           /*  接口号 */

    PPP_VLINK_INFO_S *pstPppVlink;
    DHCP4C_VIRTUAL_INFO_S *pstDhcpcInfo;

    /* Qos在IFNET上注册的供底层调用的TransmitDone函数 */
    /* 只有LAPB等特殊的链路层协议需要专门处理 */
    /* 其它的链路层协议将它置为空 */
    /* 第一个参数为IFNET接口索引 */
    /* 第二个参数为指向底层控制块的指针  */
    /* 第三个参数为指向待发送的报文的指针 */
    ULONG (*if_pfQosTransmitDoneByIndex)(ULONG,UINTPTR, MBUF_S *);

    /* Qos在IFNET上注册的供链路层使用的发送函数，考虑了拥塞控制 */
    /* 第一个参数为IFNET接口索引 */
    /* 第二个参数为指向底层控制块的指针  */
    /* 第三个参数为指向待发送的报文的指针 */
    ULONG (*if_pfQosTransmitByIndex)(ULONG, UINTPTR, MBUF_S *);

    /* L2IF扩展 */
    ULONG  if_ulL2OrL3;      /* 接口的二三层属性标记: SWITCHPORT_L3IF/SWITCHPORT_L2IF_PORT/SWITCHPORT_L2IF_TRUNKPORT */
    ULONG  if_ulL2ifPortIndex;  /* SWITCHPORT_L2IF_PORT二层接口保存的PORT信息数组索引 */
    ULONG  if_ulDuplexStatus;   /* 接口全双工/单双工工作状态,由底层上报,只对ETH有效.取值PHY_DUPLEX_EN */

    /* vrrp扩展 */
    UINTPTR  if_ulStandbyPointer; /* 指向该接口下的第一个vrrp备份组 */

    /* OAM协议扩展支持主备信息增加字段 */
    ULONG if_ulRawPhyStatus;    /* 保存底层上报的原始物理状态 */
    ULONG if_ulPhyDetectStatus; /* 保存OAM状态，接口OAM状态有以下三种：0 EFMNORMAL，1 EFMUP，2 EFMDOWN */

    /* 记录接口物理、协议UP/Down变化次数 */
    ULONG if_ulPhyUpCount;      /* 接口变化到物理UP次数 */
    ULONG if_ulPhyDownCount;    /* 接口变化到物理Down次数 */
    ULONG if_ulLineUpCount;     /* 接口变化到协议UP次数 */
    ULONG if_ulLineDownCount;   /* 接口变化到协议Down次数 */

    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG if_ulVrfIndex;
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    VOID  *if_ulVrfIfListNode;
    /*Begin: adding VRF6 index for VRF6 support*/
    ULONG if_ulVrf6Index;
    /*End: adding VRF6 index for VRF6 support*/
    VOID  *if_ulVrf6IfListNode;

    /* VISP1.8.1 支持1AG标准协议开发*/
    UCHAR if_uc1agVersion; /* 0:Draft7版本;1:标准版本 */
    UCHAR if_uc1agNpVersion; /* 0:Draft7版本;1:标准版本 */
    /* Added for 支持接收不带VLAN头的1AG报文2009-05-14 */
    USHORT if_us1agRcvDefaultVlan;

    /* Edit by L00105073 at 2009-12-24 for 1agOverTrunkPort 下发组播地址计数 */
    ULONG if_ul1agMultiCount;
    ULONG ulHost6RtReserved;  /*IPV6保留主机路由标记 ，IPV4已经在IP
                             控制块中，但IPV6控制块由IR管理*/
    ULONG ulMacChangeFlag;   /* physical地址改变标记*/     

    VOID *pst1agMepListOnIf;
#if (TCPIP_MODULE_MINI == VRP_YES)
    IN6ADDR_S ia6_stAddr;
    ULONG ia6_ulPrefixLength;
    ULONG ip6if_ulMtu;
    UCHAR ucIpv6EnableFlag;
    UCHAR ucReserved[3];
#endif        
}IFNET_S, *PIFNET_S;


typedef struct  tagIFMsgHdr
{
    USHORT  usMsgID;                /* 消息ID */
    USHORT  usMsgType;              /* 消息类型 */
    USHORT  usSerialNum;
    USHORT  usMsgMode;              /* 消息模式 */
    USHORT  usSlot;                 /* 槽号 */
    USHORT  usData;                 /* 数据 */
    ULONG   ulIfIndex;              /* 接口索引 */
    /*VRPV3R001M07_IFNET_XHZ_BEG base on 8060V100R001M01B01D003_021209*/
    /* ULONG   ulBriSonIfIndex[2]; */
    /*VRPV3R001M07_IFNET_XHZ_END */
    ULONG   ulProductIndex;
    ULONG   ulData;                 /* 数据 */
    ULONG   ulLen;                  /* 消息长度 */
    ULONG   ulSubType;              /* 子接口类型 */

    struct tagIFMsgHdr*     pNext;
}IFMSGHDR_S;            /* message header 32 bytes */


/* #define IF_DEFAULT_IF                           (&gstDefaultIf) */
extern IFNET_S *IF_GetIfByIndex(ULONG ulIfIndex);
extern ULONG IF_IsTrunkPort(IFNET_S* pIf);

#define IF_NULL(m_pstIf)                (NULL == (m_pstIf))
#define IF_GETSLOT(ulIf)                (IF_GetSlotByIndex(ulIf))

/* 下列宏存在问题 */
/*
#define IF_GETNAME(ulIf)                (IF_GetIfByIndex(ulIf)->if_szIfName)
#define IF_GETLINKTYPE(ulIf)            (IF_GetIfByIndex(ulIf)->if_ulPortType)
#define IF_GETLINKPTR(ulIf)             (IF_GetIfByIndex(ulIf)->if_ulLinkLink)
#define IF_GETLINKPTRBYINDEX(ulIf)      (IF_GetIfByIndex(ulIf)->if_ulLinkLink) */

#define IF_GETNAME(ulIf)            (IF_GetIfByIndex(ulIf) ? IF_GetIfByIndex(ulIf)->if_szIfName : "\0")
#define IF_GETLINKTYPE(ulIf)        (IF_GetIfByIndex(ulIf) ? IF_GetIfByIndex(ulIf)->if_ulPortType : PORT_MAX)
#define IF_GETLINKPTR(ulIf)         (IF_GetIfByIndex(ulIf) ? IF_GetIfByIndex(ulIf)->if_ulLinkLink : NULL)
#define IF_GETLINKPTRBYINDEX(ulIf)  (IF_GetIfByIndex(ulIf) ? IF_GetIfByIndex(ulIf)->if_ulLinkLink : NULL)

/* 下列宏无地方调用,删除 */
/* #define IF_GETLINKPROTO(ulIf)           (IF_GetIfByIndex(ulIf)->if_ulLineProtocol)
#define IF_GETPHYTYPE(ulIf)             (IF_GetIfByIndex(ulIf)->if_ulPhyType)
#define IF_GETSHUTDOWN(ulIf)            (IF_GetIfByIndex(ulIf)->if_ulShutdown)*/


#define IF_GETLINKPTRBYIF(pIf)          ((pIf)->if_ulLinkLink)


/*------------------------------------------------------
   接口名解析结构，用于分析接口名字符串的构成
-------------------------------------------------------*/
typedef struct tagIFNAME
{
    CHAR    if_pName[MAX_IF_NAME_LENGTH+1];   /* save the real ifnet name */
    VOID*   if_pClass;                        /* IFNET内部字段 (对应的接口类指针，但VA时为对应的主接口类) */
    CHAR    if_pMainName[MAX_IF_NAME_LENGTH+1];/* 主接口名称 */
    ULONG   if_pOp[IFNET_MAX_IFNAME_INDEX];   /* the part of the name, max is 6 */
    ULONG   if_ulIndex;                       /* the number of the part */
    ULONG   if_ulColon;                       /* 子通道标志 */
    ULONG   if_ulSub;                         /* 子接口标志 */
}IFNAME_S, *PIFNAME_S;

/*------------------------------------------------------
   接口索引结构
-------------------------------------------------------*/
typedef struct tagIFIndex
{
    USHORT usSynFlag;       /* 该索引结构对应的同步号 */
    UCHAR  ucPadding[2];
    IFNET_S *if_pIf;        /* 指向该接口索引对应的接口数据结构的指针 */
}IFINDEX_S;

typedef struct tag_IF_INFO_S
{
    ULONG   ulIndex ;       /* 接口指针索引 */
    ULONG   ulLanguage ;    /* 当前语言模式 */
    CHAR    *pInfo ;         /* 信息缓冲区 */
    ULONG   ulSize ;         /* 缓冲区大小 */
}IF_INFO_S ;

typedef struct tagIF_WAITLIST_PARAM
{
    UINTPTR   ulWaitListHandle;       /* WAITLIST句柄 */
    ULONG   ulSearchType ;          /* 搜索类型 */
    VOID    *pSearch ;                      /* 入口指针 */
}IF_WAITLIST_PARAM ;

typedef struct tagIFCreate              /* create a single ifnet */
{
    IFMSGHDR_S      stMsgHdr;
    CHAR    if_pName[VRP_INTERFACE_NAME_LENGTH];
    ULONG   if_ulShutDown;
    ULONG   if_ulLineProto;
}IF_CREATE_S;

typedef struct  tagIFMIB
{
    USHORT  usTableType;    /* 表类型 */
    UCHAR   ucPadding[2];
    ULONG   ulTableAddr;   /* 表结构地址,分别存放各个表结构的首地址 */
}IFMIB_S;

typedef struct tagIFHotInsert           /* create a single ifnet */
{
    IFMSGHDR_S      stMsgHdr;
    ULONG    ulCfgMTU;
    ULONG    ulIsisFlag;
    ULONG    ulProtoLimit;
    ULONG    ulCfgBandWidth;   /*bandwidth-threshold*/
    CHAR     if_pName[VRP_INTERFACE_NAME_LENGTH];
}IF_HOT_INSERT_S;

#define COMMON_MSG \
    IFNET_S *  pIf;    \
    ULONG ulHandle;    \
                       \
    DULONG   dulInPkts;  \
    DULONG   dulOutPkts; \
    DULONG   dulInBytes; \
    DULONG   dulOutBytes;\
    DULONG   dulInDrops; \
    DULONG   dulOutDrops;\
                       \
    ULONG   ulLastInBytes;\
    ULONG   ulLastInPkts;\
    ULONG   ulLastOutBytes;\
    ULONG   ulLastOutPkts;\
                          \
    ULONG   ulInByteRate; \
    ULONG   ulOutByteRate;\
    ULONG   ulInPacketRate;\
    ULONG   ulOutPacketRate;\
                            \
    ULONG   ulPhyType

typedef struct tagCommonIfPhyMsg
{
    COMMON_MSG;

} COMMON_PHY_MSG;


/*
设备链结构
*/
/*-------------------------
用于进行接口分析的向量结构
----------------------------*/
typedef struct tagAnalVector
{
    ULONG   if_ulMaxEntry;                  /* 最大可分配的数目 */
    ULONG   if_ulAlloced[2];                /* 现在不同的形式分配的数目 */
    ULONG   if_ulLower;                     /* 这项的最低数目 */
    ULONG   if_ulUpper;                     /* 这项的最高数目 */
    ULONG   if_ulHelpIndex;                 /* 接口索引的帮助信息 */
    ULONG   * if_pSymbol[2];                /* 下一项的符号表 */
    ULONG   if_ulProperty;                  /* 接口的标志位 */

    /* 第一个用于slot/card/interface这种形式,第二个用于slot/card/interface:timeslot这种形式
     子接口slot/card/interface.subport复用第二个，因目前支持子通道的Dialer\VT口不支持子接口*/
    struct tagAnalVector    **if_pIndex[2];
}IF_ANAL_VECTOR_S,*PIF_ANAL_VECTOR_S;


/***************************************************************************************/
/********注意下面的宏是为了兼容老的模块，新模块不要使用! *****/
/***************************************************************************************/
extern ULONG gulIfnetLineProtocol[8];
/* 接口管理提供给IP模块 */
#define IF_IS_InLOOPBACK(pIf)            ((pIf != NULL) && (pIf->if_ulPhyType == PHY_LOOP))

/* 输入是IFNET索引，返回值非0表明是LoopBack接口或者是InLoopBack接口 */
#define IF_IS_LOOPBACK(m_ulIndex)        ((gulIfnetLineProtocol[(m_ulIndex) & 0x00000007]) == PORT_LOOP)
#define IF_GETIPCTLBLK(m_pIf)            ((m_pIf)->if_ulIpIf)    /* 输入是IFNET指针，返回值是接口的IP控制块指针 */
#define IF_GETIPv6CTLBLK(m_pIf)          ((m_pIf)->if_ulIpv6If)  /* 输入是IFNET指针，返回值是接口的IPv6控制块指针 */
#define IF_IS_InNull(pIf)                ((pIf != NULL) && (pIf->if_ulPhyType == PHY_NULL))

#define IF_IS_InVI(pIf)                  ((pIf != NULL) && (pIf->if_ulPhyType == PHY_VI))

#define IF_IS_InUI(pIf)                  ((pIf != NULL) && (pIf->if_ulPhyType == PHY_UI))

 /* 代码同步, 增加 新类型. z36377, 2004/09/18 */
#define IF_IS_MTUNNEL(pIf)       ((pIf != NULL) && (pIf->if_ulPortType == PORT_MTUNNEL))

#define IF_IS_VLANIF(pIf)                ((pIf != NULL) && (pIf->if_ulPortType == PORT_VLAN))
#define IF_IS_ETHTRUNKIF(pIf)            ((pIf != NULL) && (pIf->if_ulPortType == PORT_ETH_TRUNK))
#define IF_IS_IPTRUNKIF(pIf)             ((pIf != NULL) && (pIf->if_ulPortType == PORT_IP_TRUNK))

/* 输入pstIfNet是接口指针，pstIpCtlBlk是IP控制块指针，将IP控制块指针设置到接口上 */
#define IF_SETIPCTLBLK(m_pIf,pstIpCtlBlk)    (((m_pIf)->if_ulIpIf) = (UINTPTR)pstIpCtlBlk)

/* 输入pstIfNet是接口指针，pstIpv6CtlBlk是IPv6控制块指针，将IPv6控制块指针设置到接口上 */
#define IF_SETIPv6CTLBLK(m_pIf,pstIpv6CtlBlk)    (((m_pIf)->if_ulIpv6If) = (UINTPTR)pstIpv6CtlBlk)

/* 用户保证接口指针的准确性。输入：接口指针，返回值是接口索引 */
#define IF_GETINDEXBYIF(pIf)                 ((pIf)->if_ulIfIndex)
#define IF_GETTOPIF(pIf)                     (IF_GetIfByIndex((pIf)->if_ulTopIfIndex))
#define IF_GETMTU(pIf)                       ((pIf)->if_ulMTU)

#define IF_SETMTU(pIf,ulMTU) \
{\
    if ((pIf)->if_ulMTU >= (ulMTU))\
    {\
        (pIf)->if_ulMTU = (ulMTU);\
    }\
}

#define IF_GETCFGMTU(pIf)                    ((pIf)->if_ulCfgMTU)
#define IF_SETCFGMTU(pIf,ulMTU)              ((pIf)->if_ulCfgMTU = ulMTU)
#define IF_SETMTSOFT(pIf, pMTSoft)          (((pIf)->if_ulLinkLink) = (UINTPTR)pMTSoft)
#define IF_GETMTSOFT(pIf)                    ((pIf)->if_ulLinkLink)
#define IF_ISBROADCAST(pIf)                  ((pIf)->if_ulFlags & IF_RTATTR_BROADCAST)

/*增加集中式热插拔和卡热插拔项目   pengjimei for DEV_HOTCTL 2002/12/13
#define IF_GETSLOTBYPTR(pIf)     ((pIf)->if_ulSlotNum & 0xffff)*/

/*
#if (VRP_CENTERALIZATION == VRP_YES)
#define IF_GETSLOTBYPTR(pIf)                           (getSelfBoardId())
#else
*/
#define IF_GETSLOTBYPTR(pIf)                  ((pIf)->if_ulSlotNum & 0xffff)
/*
#endif
*/
/*end*/

#define IF_GETIFTYPE(pIf)                     ((pIf)->if_ulType)

#define IF_SLOT2IPCNODE(m_ulSlot)            (m_ulSlot)
#define IF_IPCNODE2SLOT(m_ulNode)            (m_ulNode)     /* m_ulNode MUST NOT BE ZERO */
#define IF_GETLOOPBACKNAME()                 "InLoopBack0"
#define IF_GETIFNAMEBYIF(pIf)                (pIf->if_szIfName)

#define IF_ISVALIDINDEX(m_ulIndex) \
{\
    if((m_ulIndex) != IF_GetIfByIndex(m_ulIndex)->if_ulIfIndex) \
    {\
        VOS_DBGASSERT(0);\
    }\
}

#define IF_ISVALIDIF(m_pIf)\
{\
    if((m_pIf) != IF_GetIfByIndex((m_pIf)->if_ulIfIndex))\
    {\
        VOS_DBGASSERT(0);\
    }\
}

#define IF_IS_SHUTDOWN(pIf)  ((pIf)->if_ulShutdown & IF_SHUTDOWN)
#define IF_IS_NOPHY_SHUTDOWN(pIf) ((pIf)->if_ulShutdown & IF_NO_PHY_SHUTDOWN)
#define IF_IS_SUBIF(pIf)     ((pIf)->if_ulSubIndex)

/* #define MACADDRLEN       6 */      /*physical地址长度*/

/* Added bu zk36377. */
#define IF_GetIfByIndex_XY( pstIfNet, ulIfIndex )  ((pstIfNet)= IF_GetIfByIndex(ulIfIndex))

extern ULONG g_ulFirstDimension;
extern ULONG g_ulSecondDimension;
extern ULONG g_ulIfnetPre3D;

#define IF_GET_FIRST_DIM(pIf) (pIf->if_ulSlotNum) & 0x0000ffff
#define IF_GET_SECOND_DIM(pIf) (pIf->if_ulSlotNum >> 16) & 0x0000ffff
#define IF_GET_THIRD_DIM(pIf) (pIf->if_ulIfNum)

extern ULONG IF_Is_3Dim();
extern ULONG IF_Is_Distribute_3Dim();
extern ULONG IF_Is_Central_3Dim();

/* 判断是否本板接口 */
#define IF_IS_ThisBoard(pIf)  ((pIf != NULL)\
                              &&((!IF_Is_3Dim())\
                                ||( IF_Is_Central_3Dim())\
                                ||((IF_Is_Distribute_3Dim())\
                                    &&(((pIf->if_ulSlotNum)&0x0000ffff) == g_ulFirstDimension )\
                                    &&(((pIf->if_ulSlotNum >>16)&0x0000ffff) == g_ulSecondDimension)\
                                   )\
                                 )\
                               )

/* 下发底层NP LCP ECHO数据结构 */
typedef struct tagPPPNPLCPECHO
{
    ULONG  ulGotMagicNum;             /* 本端MAGIC NUMBER */
    ULONG  ulHisMagicNum;             /* 对端MAGIC NUMBER */
    ULONG  ulKeepAlive;               /* 发送保活报文频率,单位秒 */
    USHORT usLoopBackNum;             /* 判断自环次数 */
    UCHAR  ucPacketID;                /* 初始化报文ID */
    UCHAR  ucPppDownNum;              /* 本端没有收到对端回应PPP请求报文次数,Down掉本端链路 */
    UCHAR  szEchoReq[12];             /*PPP LCP Echo请求报文*/
}PPPNPLCPECHO_S;


#ifdef  __cplusplus
}
#endif

#endif  /* end of _IF_PUB_H_ */


