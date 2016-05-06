/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              etharp_pub_type.h
*
*  Project Code: VISPV100R005
*   Module Name: ETHARP   
*  Date Created: 2004-7-7
*        Author: zhang hong yan(19316)
*   Description: 以太网组件的公共头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE          NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2004-7-7      zhanghongyan(19316)  Create the first version.
*  2006-4-27     wang xin(03278)      根据编程规范，对文件进行规范化整理
*  2006-05-11    luyao                为支持ARM CPU字节对齐特性，修改结构。
*  2006-05-13    l48923               Delete useless code
*  2006-07-12    wuhailan             第二阶段质量整改(A82D03515)
*  2008-08-13    f54882               Modify for BC3D00237,新增IP冲突消除检测相关结构
*  2008-11-29    q62011               Add for BC3D00792
*                                     DR.131获取链路层状态
*                                     DR.133以太模块需提供发送ARP 报文的接口
*******************************************************************************/

#ifndef    _ETHARP_PUB_TYPE_H_
#define    _ETHARP_PUB_TYPE_H_

#ifdef    __cplusplus
extern "C"{
#endif

#include "tcpip/sfib4/include/ifiba_inc.h"
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#include "tcpip/public/arith_cbb/include/avltree.h"
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
#include "tcpip/vlink/include/vlink.h"
#include "tcpip/etharp/include/etharp_api.h"

enum enumArpMsg
{
    Help_Mac_Info = 0
};
/*ETHARP模块SID定义*/
#define SID_COMP_ETHARP_MTSOFTC_S       ( 1 )
#define SID_COMP_ETHARP_MTSOFTCSUB_S    ( 2 )
#define SID_COMP_ETHARP_ARPRTENTRY_S    ( 3 )
#define SID_COMP_ETHARP_ARPCMD_S        ( 4 )

/*链路层头长度*/
/*#define ETHERNETMTU     0x0600 */
/* 当前以太，trunk接口的最大MTU调整为1800，为了能正确区分两种格式的以太报文，
 * 也需要调整ETHERNETMTU,现在调整为1836(0x072c) */
#define ETHERNETMTU     0x072c
/*ARP表项最大数目*/
#define ARP_TABLELEN    4096 
 

/*接口状态*/  /*已经不用，与IFNET统一*/
#define IFNETDOWN 0
#define IFNETUP   1


#define RESOLVED    2            /*ARP结点项的状态,已经解析出来*/
#define RESOLVING   3            /*ARP结点项的状态,正在解析*/
#define MAXSCRIPT   6            /*以太网接口描述字的最大长度*/
#define HEADER_LEN  16           /*以太网幀头的长度*/

#define PKTFMT_EN_LEG_DHCP 0xffff

/* 指数退避算法发送免费ARP时的次数 */
#define ETHARP_SENDFREEARP_3TIMES  3 
#define ETHARP_SENDFREEARP_4TIMES  4

/* 下一次超时时间，单位毫秒 */
#define ETHARP_SENDFREEARP_OUTTIME 2000

/* ARP表项刷新标记 */
#define ETHARP_ARPUPDATE_BYFREEARP 0x01   /* ARP表项MAC因免费ARP而更新 */
#define ETHARP_ARPUPDATE_OUTIF     0x02   /* 静态ARP表项刷新出接口 */

/*进行源MAC的检查，判断报文中的源MAC是否和接口的MAC相同，相同，需要考虑是否丢弃，
 不丢弃是为了可以上报冲突告警
 
0:    ETH报文不检查   ARP要检查
1:    ETH报文检查     ARP也检查
2:    ETH报文不检查   ARP不检查    MCCP 使用

*/
#define ETHARP_ETH_AND_ARP_MACCHECK_POLICY   2  /*支持MCCP 进行源MAC的检查:  ETH报文不检查  ARP报文也不检查*/

/* Modify by z00171897/s00176784, at 2011-06-02. 修改原因: 支持节点老化前发送单播ARP请求 */
/* ARP老化超时处理标志 */
#define ETHARP_ARP_EXPIRE_PROC       1
/* ARP非老化超时处理标志 */
#define ETHARP_NOT_ARP_EXPIRE_PROC   0 

/* 处理上报ARP MISS调试结果命令 */
enum tagArpMissDebugCode
{
    ARPMISS_SUCCESSDOWN = 1,      /* 1 成功下发arp */
    ARPMISS_SUCCESSREQUEST,       /* 2 成功发送arp请求 */
    ARPMISS_NOREGPPI,             /* 3 没有注册arp ppi钩子函数 */
    ARPMISS_WRONGIFINDEX,         /* 4 接口索引不存在 */
    ARPMISS_NOMTSOFT,             /* 5 不存在接口控制块 */
    ARPMISS_WRONGIFTYPE,          /* 6 上报接口类型错误 */
    ARPMISS_NOSOURCEIP,           /* 7 接口没有地址 */
    ARPMISS_SENDFAIL,             /* 8 发送arp请求报文失败 */
    ARPMISS_INSERTNODE,           /* 9 插入ARP节点失败 */
    
    ARPMISS_MAX
};

#ifdef TCPIP_SUPPORT_ARMCPU
#define FAST_COPY_MACADDR(Dest,Source) \
    ((VOID)TCPIP_Mem_Copy((VOID *)(Dest), 6, (VOID *)(Source), 6))
#define FAST_COPY_8BYTE(Dest,Source) \
    ((VOID)TCPIP_Mem_Copy((VOID *)(Dest), 8, (VOID *)(Source), 8))
#else
#define FAST_COPY_MACADDR(Dest,Source) \
    ((ULONG *)(Dest))[0] = ((ULONG *)(Source))[0]; \
    ((USHORT *)(((UCHAR *)(Dest))+4))[0] = ((USHORT *)(((UCHAR *)(Source))+4))[0]
#define FAST_COPY_8BYTE(Dest,Source) \
    ((ULONG *)(Dest))[0] = ((ULONG *)(Source))[0]; \
    ((ULONG *)(((UCHAR *)(Dest))+4))[0] = ((ULONG *)(((UCHAR *)(Source))+4))[0]    
#endif



/*以下是本模块的宏定义*/
#define ETHARP_GET_ETHERHDR_FROM_MTSOFTC(pMtSoft)    ((pMtSoft)->ucEthernetHeader)

#define ETHER_MAP_IP_MULTICAST(ipaddr, enaddr) \
{ \
    (enaddr)[0] = 0x01; \
    (enaddr)[1] = 0x00; \
    (enaddr)[2] = 0x5e; \
    (enaddr)[3] = ((UCHAR *)ipaddr)[1] & 0x7f; \
    (enaddr)[4] = ((UCHAR *)ipaddr)[2]; \
    (enaddr)[5] = ((UCHAR *)ipaddr)[3]; \
}


#define AF_UNICAST_ARP 20           /* 单播ARP */

/*以下由IFNET统一提供，暂时*/
#define IF_LINKSTATE_LINKUP   19
#define IF_LINKSTATE_PHYDOWN  20

#define ETHARP_SNDBUF_MAX_LEN 10  
#define ETHARP_SNDBUF_TOTAL_LEN  512
#define ETHARP_WAIT_FOR_RESOLVE 3  /*解释ARP失败入暂存队列时的返回值?for D25765*/


#define ETHERTYPE_IP6    0x86DD   /*IPv6协议的定义*/
#define INTERFACEIDLEN   8

#define IP6_ETHER_MAC_MULTICAST(enaddr) ( ((UCHAR)0x33 == (enaddr)[0]) && ((UCHAR)0x33 == (enaddr)[1]) ) 

#define ETHARP_INIT_INTERFACE_ID( interface_id ) \
{\
  (interface_id)[0] = ( UCHAR ) 0x00;\
  (interface_id)[1] = ( UCHAR ) 0x00;\
  (interface_id)[2] = ( UCHAR ) 0x00;\
  (interface_id)[3] = ( UCHAR ) 0x00;\
  (interface_id)[4] = ( UCHAR ) 0x00;\
  (interface_id)[5] = ( UCHAR ) 0x00;\
  (interface_id)[6] = ( UCHAR ) 0x00;\
  (interface_id)[7] = ( UCHAR ) 0x00;\
}

#define ETHER_MAP_IP6_MULTICAST(ipaddr, enaddr) \
{ \
    (enaddr)[0] = 0x33; \
    (enaddr)[1] = 0x33; \
    (enaddr)[2] = ((UCHAR *)ipaddr)[12]; \
    (enaddr)[3] = ((UCHAR *)ipaddr)[13]; \
    (enaddr)[4] = ((UCHAR *)ipaddr)[14]; \
    (enaddr)[5] = ((UCHAR *)ipaddr)[15]; \
}

#define ETHER_MAP_MAC_INTERFACEID(enaddr , interfaceid) \
{ \
   (interfaceid)[0] = (enaddr)[0] | (CHAR)0x02; \
   (interfaceid)[1] = (enaddr)[1];  \
   (interfaceid)[2] = (enaddr)[2];  \
   (interfaceid)[3] = (CHAR)  0xff; \
   (interfaceid)[4] = (CHAR)  0xfe; \
   (interfaceid)[5] =(enaddr)[3]; \
   (interfaceid)[6] =(enaddr)[4]; \
   (interfaceid)[7] =(enaddr)[5]; \
}

typedef struct tagARPTOREPLYINFO
{
    ULONG   ulIpAddr;                     /* 待应答的ARP请求中的目的地址 */
    struct tagARPTOREPLYINFO *pstNext;   /* 下一个待应答的ARP请求中的目的地址 */
}ARPTOREPLYINFO_S;

#define  ETHER_GET_LINKSTATUS(pstIf) \
     ((pstIf->if_ulSubIndex)?((IF_GETMTSOFT(pstIf))?(((ETHARP_MTSOFTCSUB_S*)IF_GETMTSOFT(pstIf))->ulLinkStatus):0)\
     :((IF_GETMTSOFT(pstIf))?(((ETHARP_MTSOFTC_S*)IF_GETMTSOFT(pstIf))->ulLinkStatus):0))

/*#pragma VOS_BEGINPACK(1)                            按字节对齐*/
typedef struct tagARPRTENTRY
{
    struct    tagARPRTENTRY*   pRtLeft;              /* 左子树 */
    struct    tagARPRTENTRY*   pRtRight;             /* 右子树 */
    ULONG                    ulRtIpAddr;             /*用来保存地址*/
    UCHAR                    ucMacAddr[6];           /*用来保存physical地址*/
    UCHAR                    ucDArpFlag;             /*记录动态ARP记录是否是用户添加 */
    UCHAR                    ucSArpConflict;         /*静态ARP和动态ARP冲突标记,1冲突 0不冲突 */ 
    ULONG                    ulFlags;                /*该ARP的标志字段 */
    ULONG                    ulRtIfIndex;            /*用来保存IFNET接口INDEX*/
    ULONG                    ulRtExpire;             /*用来实现ARP缓存的超时处理 */
    struct    tagARPRTENTRY*   pLPrev;       /*指向前的ARPENTRY_S项(老化链)*/
    struct    tagARPRTENTRY*   pLNext;       /*指向后的ARPENTRY_S项(老化链)*/
    ULONG                     ulAsked;                /*该ARP项已请求的次数*/ 
    ULONG                    ulVrfIndex;        /*标示地址所在的VPN*/
    /*目前的方案中，协议栈在添加时记录产品的VLINK索引，并在UPDATE和删除时透传，
    为了避免和产品产生耦合，协议栈UPTATE时不根据它来区分是否应该UPDATE还是ADD，
    由产品在适配时根据vlink索引来区分分发消息；*/
    ULONG                   ulVlinkIndex;/*NP下发后返回的VLINK索引号*/
    MBUF_QUEUE_S         stSndPkts ;/*用于暂存ARP没有生成发送的报文*/
    struct     tagMTSOFTC* pMtSoft;           /*以太网控制块zhanghongyan*/
    UCHAR    ucReSendNum;   /*用于ARP超时之后主动发送ARP请求的次数*/
    UCHAR    ucHasDownLoadToNP;  /* 1 该表项已下发NP 0 未下发NP.在下发删除ARP时候,该标记必须为1,
                                    否则说明该ARP表项没有下发到NP,目前在ADD和UPDATE操作已经把该标记置1 */
    /*Modefy by Q62011 for vlan start*/
    USHORT   usVID;         /*该ARP对应的VLANID*/
    /*Modefy by Q62011 for vlan end*/
    struct    tagARPRTENTRY*   pNodePrev;   /*指向前的ARPENTRY_S项(顺序链)*/
    struct    tagARPRTENTRY*   pNodeNext;   /*指向后的ARPENTRY_S项(顺序链)*/

    ULONG     ulOutPortIfIndex;
    ULONG     ulCountToReply;   /* VLANIF便能ARP代理后，待应答的ARP请求个数 */
    ARPTOREPLYINFO_S *pstArpToRelayNode;   /* VLANIF便能ARP代理后，待应答的ARP请求链表 */

    UCHAR        ucArpUpdateFlag;          /* ARP表项有更新 */
    UCHAR        ucSourceType;      /*动态ARP的来源:自学习、用户配置、配置后给自学习更新*/
    UCHAR        ucReserved[2];
    TCPIP_TIME_S stEtharpUpdateTime;       /* ARP表项最近一次更新时间 */
    ULONG ulDownNpTime;   /* ARP表项下发Np时间 */  
    VOID         *pstGuardNode;            /* ARP防欺骗节点 */

    /*arp Mccp support V300R001C00 --  start*/    
    ULONG ulLastRefTime;              /*absolute Time at which the entry was last ref.*/
    struct tagARPTIMER_ENTRY_NODE *pEntryTimerNode;  /*Timer node for the arp entry node*/
    /*arp Mccp support V300R001C00 --  end*/ 
    
}ETHARP_ARPRTENTRY_S;


typedef struct tagARPTIMERLIST
{
    ULONG ulTimeoutValue;     /*Time out Value*/
    struct tagARPTIMERLIST   *pNextTimerNode;    /*next node*/    
    struct tagARPTIMERLIST   *pPrevTimerNode;    /*previous node*/        
    struct tagARPTIMER_ENTRY_NODE *ptimerEntryNodeList; /*Arp Entry node in the list*/            
    
}ETHARP_TIMER_LIST_S;

typedef struct tagARPTIMER_ROOTNODE
{

    ULONG ulTimerId;     /*Time out Value*/
    ETHARP_TIMER_LIST_S *pTimerList;      /*starting  of the timer list */    
    ULONG ulCount;
}ETHARP_TIMER_ROOTNODE_S;


/*timer helper task- linked list structure */
typedef struct tagARPHELPERTASKNODE
{
    ULONG ulListId;     /*List Id Value*/
    struct tagARPHELPERTASKNODE *pNext;
    struct tagARPTIMER_ENTRY_NODE *pArpHelperEntryNodeList;
    
}ETHARP_HELPERTASK_NODE_S;


typedef struct tagARPTIMER_ENTRY_NODE
{
    struct tagARPTIMER_ENTRY_NODE   *pNextTimerEntryNode;    /*next node*/   
    struct tagARPTIMER_ENTRY_NODE   *pPrevTimerEntryNode;    /*previous node*/  
    struct tagARPTIMER_ENTRY_NODE   **pParentTimerlistNode;     /*Parent Timerlist node*/   
    ETHARP_ARPRTENTRY_S *pActualEntryNode;                          /*Arp Entry node list*/  
    
}ETHARP_TIMERENTRY_NODE_S;




typedef struct  tagETHARP_ARPTABLE
{
    ETHARP_ARPRTENTRY_S*     pRtLeft;  /* 左子树 */
    ETHARP_ARPRTENTRY_S*     pRtRight; /* 右子树 */
}ETHARP_ARPTABLE_S;  


/* 修改该数据结构,需要在后面添加,不能添加到中间,并且要评估是否会对子接口控制块造成影响.
   因为需要保证该数据结构和子接口控制块tagMTSOFTCSUB前面的数据结构一致,在应用pppoc等特性,
   存在转换,如果不一致可能导致异常*/
typedef struct  tagMTSOFTC
{
    struct     tagIFNET*   pMtSoftIf;             /*与控制块相联的IFNET*/
    USHORT                 usIPEncapsulation;     /*不同的IP报文封装格式*/
    USHORT                 usIPXEncapsulation;    /*不同的IPX报文封装格式*/
    ULONG                  ulLinkStatus;          /*描述接口的DOWN或UP状态*/
    ULONG                  ulNetProtocolStatus;  /*protocol link status of the interface except IP */

    ULONG           ulIP6LinkStatus;          /*描述接口的IPv6 DOWN或UP状态*/
    UCHAR           ucInterfaceID[8];          /* 接口ID */

    struct     tagIFNET*   pIPXEncapsulation[4];  /*封装不同IPX子网*/
    struct     tagMTSOFTC* pMtSoftNext;           /*以太网控制块*/
    UCHAR       ucEthernetHeader[HEADER_LEN];      /*以太网幀头*/    

    BOOL_T                  bIsARPproxy;/* true or false 该接口的ARP PROXY功能是否生效*/
    UCHAR                   ucArpDetectTimes; /* ARP超时探测次数 */
    UCHAR                   ucArpLog;         /* 是否记录ARP报文日志 */ 

    ULONG                   ulArpExpireTime;  /* ARP超时时间 */
    
    ULONG                   ulPoecDebugFlag;             /*PPPoE Client Debug Flag*/
    VOID *                  pPoeClientCB;                /*PPPoE Client CB Pointer*/
    ETHARP_ARPRTENTRY_S    sArpRoot;              /*ARP链头*/
    ETHARP_ARPTABLE_S      sArpTable[ARP_TABLELEN];             /*ARP 表*/ 
    ULONG                  ulArpNumber;           /*ARP号*/
    ULONG                  ulTimerId;  /* 定时器ID */
    ULONG                  ulVlanFlag ;   /*标识接口是否使能VLAN特 性*/
    UCHAR                  ucBakEthMac [MACADDRLEN]; /* 备份的MAC */
    USHORT                 usDhcpflag ;  /* 接口是否使能DHCP的标记 */

    ETHSTAT_S              stETHStat; /* 以太接口的报文统计信息 */
    ULONG                  ulIsIsFlag;  /*是否使能收发ISIS报文，为1使能，0去使能*/
    USERARPSTAT_S          stUserArpStat; /* 用户指定发送ARP报文统计信息 */   
    UINTPTR  ulVLANPortInfo;  /* The address of the VLAN port info structure */
    BOOL_T                 bIsVlanARPproxy;
    UCHAR                  ucArpUpdate;
    UCHAR                  ucReserved;
    ULONG                  ulVlanId ;      /* vlan ID */
    
    BOOL_T                 bEnableSpecArpPrxy;  /*该接口的特殊ARP代理功能是否生效*/
    BOOL_T                 bEnableIfArpStrict;  /*Added by l00213099,ARP严格学习接口配置开关,2014-04-03 */

    /* Add by z171897/s176784, at 2011-06-02. 修改原因: 支持获取保存的ARP报文队列 */
    MBUF_QUEUE_S           stSndArpPktQue;  
    MBUF_QUEUE_S           stRcvArpPktQue;
}ETHARP_MTSOFTC_S;
/* 注意:主接口控制块和子接口控制块前面的数据结构相同,转换后可以共用,但后面的数据结构与子接口不同,如存在转换,
   需注意pPoeClientCB后面的变量和ucArpLog在两结构体中不同,可能会导致取值随机或异常 */

#define IP_ARP_PROXY_DISABLE BOOL_FALSE
#define IP_ARP_PROXY_ENABLE  BOOL_TRUE

/* 修改该数据结构,需要在后面添加,不能添加到中间,并且要评估是否会对父接口控制块造成影响.
   因为需要保证该数据结构和子接口控制块tagMTSOFTCSUB前面的数据结构一致,在应用pppoc等特性,
   存在转换,如果不一致可能导致异常*/
typedef struct  tagMTSOFTCSUB
{
    struct     tagIFNET*   pMtSoftIf;             /*与控制块相联的IFNET*/
    USHORT                 usIPEncapsulation;     /*不同的IP报文封装格式*/
    USHORT                 usIPXEncapsulation;    /*不同的IPX报文封装格式*/
    ULONG                  ulLinkStatus;          /*描述接口的DOWN或UP状态*/
    ULONG                  ulNetProtocolStatus;  /*protocol link status of the interface except IP */
    ULONG           ulIP6LinkStatus;          /*描述接口的IPv6 DOWN或UP状态*/
    UCHAR           ucInterfaceID[8];          /* 接口ID */

    struct     tagIFNET*   pIPXEncapsulation[4];  /*封装不同IPX子网*/
    struct     tagMTSOFTC* pMtSoftNext;           /*以太网控制块*/
    UCHAR                  ucEthernetHeader[HEADER_LEN]; /*以太网幀头*/

    BOOL_T    bIsARPproxy;/* true or false 该接口的ARP PROXY功能是否生效*/

    UCHAR      ucArpDetectTimes; /* ARP超时探测次数 */
    UCHAR      ucPadding;        /*注意:保留字段要和ETHARP_MTSOFTC_S 中的ucArpLog对齐*/
    
    ULONG      ulArpExpireTime;  /* ARP超时时间  和主接口结构的位置一致*/

    ULONG                   ulPoecDebugFlag;             /*PPPoE Client Debug Flag*/
    VOID *                  pPoeClientCB;                /*PPPoE Client CB Pointer*/
    
    UINTPTR      ulVLANPortInfo;  /* The address of the VLAN port info structure */
    BOOL_T                 bEnableSpecArpPrxy;  /*DTS2012112200999 该接口的特殊ARP代理功能是否生效*/
    BOOL_T                 bEnableIfArpStrict;  /*Added by l00213099,ARP严格学习接口配置开关,2014-04-03 */

    ETHSTAT_S              stETHStat; /* 以太接口的报文统计信息 */
   
}ETHARP_MTSOFTCSUB_S;
/* 注意:子接口控制块和主接口控制块前面的数据结构相同,转换后可以共用,但后面的数据结构与主接口不同,如存在转换,
   需注意pPoeClientCB后面的变量ucPadding在两结构体中不同,可能会导致取值异常 */


typedef struct tagETHARP_MOD_INFO
{
    ULONG    ulEthModID;
    ULONG    ulSID_ETHARP_MTSOFTC_S;
    ULONG    ulSID_ETHARP_MTSOFTCSUB_S; /*Added by f54882, 子接口以太结构SID, 2008/01/17 */
    ULONG    ulSID_ETHARP_ARPRTENTRY_S;
    ULONG    ulSID_ETHARP_ARPCMD_S;    
    ULONG    ulQUE_PPPOE_CLIENT_INPUT;
    ULONG    ulQUE_PPPOE_INPUT;
    ULONG    ulQUE_IP_INPUT;
    ULONG    ulQUE_IPV6_INPUT;
    ULONG    ulQUE_ARP;
    ULONG    ulMBUF_LINK_TYPE_ETHERNET;
    ULONG    ulARP_ENTRY_MAINTYPE;/*waitlist*/
    ULONG    ulETH_ENTRY_MAINTYPE;/*waitlist*/
    ULONG    ulMAX_APRNUMBER_DYNAMIC;
    ULONG    ulMAX_STATIC_ARPNUMBER;
    ULONG    ulETH_IPINPUT_OPTIMIZE; /*Added by x36317, 标识是否使能IP队列调度优化, 2006-04-27*/
    ULONG    ulBakDynamicArp  ; /*标识是否备份动态ARP*/
    ULONG    ulBakMacSet; /*标识physical地址的设置方式*/
    ULONG    ulQUE_ISIS_INPUT;
    ULONG    ulIPConflictMode;        /*IP冲突处理模式:0,由外部模块处理;由VISP自行处理*/
    ULONG    ulStaticArpDownload;     /* 配置(增加删除更新)静态ARP是否下发NP,光网络特殊需求,
                                         默认情况该标记为0,如果预配置设置为1,用户在添加删除静态ARP时,会直接下发NP */
    ULONG    ulArpMissNotNetTimeOut;  /*上报ARP MISS如果地址和接口不是同一网段,哑元的老化时间  */ 
    ULONG    ulChkPktSrcMac;          /*是否检查报文的源地址,1为检查,0为不检查,默认为不检查 */
    ULONG    ulFreeArpReplyUnicast;   /* 是否单播应答地址冲突的免费ARP报文 */
    ULONG    ulArpTimerList;  /* ARP timer list */
    ULONG    ulSysDynicArpMaxNum;        /* 需求201305305465,系统级可配最大动态ARP数目 */
    ULONG    ulArpStrictLearnMode;       /* Added by l00213099，ARP严格学习全局模式和接口模式配置开关,2014-04-03 */
    ULONG    ulArpSwapFalg; /*add by wuling for DTS2014111905832, ARP规格满情况下的原有替换策略,默认为1即保持原有的替换策略,0时关闭替换策略*/
} ETHARP_MOD_INFO_S;

enum enum_Eth_ErrCode 
{    
    Eth_InvalidPacket=0, 
    Eth_NullCB, 
    Eth_NullPPPOECB, 
    Eth_LinkDown,  
    Eth_UnkonwnProType, 
    Eth_UnsupportUpPro,
    Eth_ONESEFMAC,
    Eth_MEMPREPEND_FAIL,
    ETH_UNSUPPORTISIS,
    ETH_OAM3AH_LB_LOCAL,
    Eth_OK
};

typedef struct tagETHARP_SHELL_CALLBACK_SET
{
    VOID (*pfETHARP_CreateTimer) (VOID * timerList, VOID  (*pfTimerFunc)(VOID *), ULONG *pulTimerId);
    ULONG (*pfETHARP_DelTimer)(ULONG ulTimerId);
    ULONG (*pfETHARP_CreateQueue)(ULONG ulQueID,ULONG ulGetCntPerTimes,
            ULONG (* Eth_QueDealPacketFunc)(MBUF_S *),
            ULONG (* Eth_QueIsDropThisPacketFunc)(MBUF_S *,ULONG,CHAR*),
            ULONG ulMaxLen);
    ULONG (*pfETHARP_ActiveQueue)(ULONG ulQueID);
    ULONG (*pfETHARP_EnQueue)(MBUF_S *);
    ULONG (*pfETHARP_DropQueue)(MBUF_S *);
    VOID (*pfETHARP_FreePacketInQueue)(ULONG ulQueID,ULONG ulCmd,CHAR* pData);

    /*调试信息输出(直接输出字符串), 一般产品用这个即可*/
    VOID (*pfETHARP_SimpleDebugInfo)(CHAR *pBuf, ULONG ulLen);

    /*调试信息输出(报文，操作，错误码) ，
    适用于对输出信息有特殊要求的产品*/
    VOID (*pfETHARP_DebugEthPacket)(IFNET_S *pIf, ETHARP_ETSNAPHDR_S * pHead, enum enum_Eth_ErrCode ulErrCode, ULONG ulEvent);
    VOID (*pfETHARP_DebugArpEvent)(ETHARP_ETHERARP_S *pArp, ULONG ulEvent);

    VOID (*pfPPPOE_SetOurMac)( IFNET_S *pstIfnet );
}ETHARP_SHELL_CALLBACK_SET_S;

typedef struct tagETHARP_VLAN_PROC_HOOK
{
    ULONG (*pfETHVLAN_InitPortInfo)( ETHARP_MTSOFTC_S *pBufMtSoftC);
    VOID (*pfETHVLAN_ClearPortInfo)( ETHARP_MTSOFTC_S *pBufMtSoftC);
    /*ULONG (*pfETHVLAN_Output)( IFNET_S *pIf, MBUF_S * pstMBuf,USHORT usVID);*/
    ULONG (*pfETHVLAN_Output)( IFNET_S *pIf, MBUF_S * pstMBuf,USHORT usVID,ULONG *pulSndPkts);
    ULONG (*pfETHVLAN_Input)( MBUF_S * pstMbuf,IFNET_S *pIf);
    ULONG (*pfETHVLAN_VlanCheck)( IFNET_S *pIf);
    BOOL_T (*pfETHVLAN_HaveVid)( ETHARP_MTSOFTCSUB_S *pBufMtSoftC );

    ULONG (*pfETHVLAN_IsForbidIf)(IFNET_S *pstIf);

    /* Add by z62474 for vlan ha */
    ULONG (*pfETHVLAN_HA_BatchBackup)(VOID);
    ULONG (*pfETHVLAN_HA_RealTimeBackup)(ULONG ulBakType, VOID* pData);
    ULONG (*pfETHVLAN_HA_Input)(UCHAR *pucBuf, ULONG ulMsgLen);
    VOID  (*pfETHVLAN_HA_VerboseOutput)(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);
    ULONG (*pfETHVLAN_HA_Smooth)(VOID);
    ULONG (*pfETHVLAN_HA_Clean)(VOID);
    /* End by z62474 for vlan ha */
    VOID  (*pfETHVLAN_VlanConsistencyWarningProc)(MBUF_S *pstMBuf, USHORT usVlanId, ULONG ulMainIfIndex, ULONG ulVlanSubIfIndex);
    
} ETHARP_VLAN_PROC_HOOK_S;

/* 
 * Add this struct for suppotting CBSC and NodeB 
 * or another requirements submitted by special product,
 * using this as adapter function's parameter 
 */





#define ETHARP_GET_STATIC         1
#define ETHARP_GET_DYNAMIC        2
#define ETHARP_GET_NEXT_INTERFACE 1
#define ETHARP_DEFAULT_VRF_INDEX  0


#define ETHARP_SCOPE_STATIC          0x01
#define ETHARP_SCOPE_DYNAMIC         0x02
#define ETHARP_SCOPE_ALL             (ETHARP_SCOPE_STATIC | ETHARP_SCOPE_DYNAMIC)
#define ETHARP_SCOPE_THIS_INTERFACE 0x04
#define ETHARP_SCOPE_PER_INTERFACE  0x08

#define ETHARP_SEND_PACKET 1
#define ETHARP_RECE_PACKET 2
#define ETHARP_DISC_PACKET 3

#define ETHARP_SEND_ARP_PACKET 1
#define ETHARP_RECE_ARP_PACKET 2
#define ETHARP_ADD_ARP_ENTRY   3
#define ETHARP_DEL_ARP_ENTRY   4




/* 产品需要激活特殊ARP代理功能 */
#define SPECIAL_ARP_PROXY_ACTIVE    0x01
/* 产品不需要激活特殊ARP代理功能 */
#define SPECIAL_ARP_PROXY_INACTIVE  0x02

#define DYNA_ARP_ENTRY     0 /*找到动态ARP表项*/
#define STATIC_ARP_ENTRY   1 /*找到静态ARP表项*/
#define NO_ARP_ENTRY       2 /*没有找到ARP表项*/


#define ETH_IF_POSITION_UP     0 /*以太接口位置，充当上层*/
#define ETH_IF_POSITION_LINK   2 /*以太接口位置，充当链路层*/
#define ETH_IF_POSITION_DEV    3 /*以太接口位置，充当设备层*/

#define     ETHARP_DEFAULT_VLINK_INDEX     0/*非法VLINK索引值*/
#define ETHARP_CONFLICT_WARNING(pNode, WFlag, IfIndex) \
{ \
    pNode->ucSArpConflict = WFlag; \
    if (TCPIP_HA_AMB == TCPIP_HA_GetBoardType()) \
    { \
        ETH_SARPCONFLICT_PARAM_S stArpConflict = {0}; \
        stArpConflict.ulIfIndex = IfIndex; \
        stArpConflict.ulVrfID = pNode->ulVrfIndex; \
        stArpConflict.ulIPAddr = pNode->ulRtIpAddr; \
        stArpConflict.ucAlmSt = WFlag; \
        (VOID)TCPIP_Mem_Copy(stArpConflict.szMacAddr, MACADDRLEN, pNode->ucMacAddr, MACADDRLEN); \
        TCPIP_WarningOut(WARNING_ARP_CONFLICT, (VOID *)&stArpConflict); \
    } \
}

/**********************************
以下为新接口管理和地址管理的适配宏
**********************************/
#define ETH_IF_GetIfByIndex g_pstCoreIFNETFunTable->pfIF_GetIfByIndex
#define ETH_IF_GetMainIf g_pstCoreIFNETFunTable->pfIF_GetMainIf
#define ETH_IF_GETMTSOFT IF_GETMTSOFT
#define ETH_IF_GETINDEXBYIF IF_GETINDEXBYIF
#define ETH_IF_GetIfByIndex_XY IF_GetIfByIndex_XY
#define ETH_IP_Eth_IsValidIpAddr g_pstCoreAM4FunTable->pfIP_Eth_IsValidIpAddr
#define ETH_IF_SearchIfFromChain g_pstCoreIFNETFunTable->pfIF_SearchIfFromChain
#define ETH_IF_GETLINKTYPE IF_GETLINKTYPE
#define ETH_IP_IF_HaveIpAddr g_pstCoreAM4FunTable->pfIP_IF_HaveIpAddr
#define ETH_IP_IF_MaxIpAddr g_pstCoreAM4FunTable->pfIP_IF_MaxIpAddr
#define ETH_IP_IF_IsThisIfIpAddr g_pstCoreAM4FunTable->pfIP_IF_IsThisIfIpAddr
#define ETH_IP_ArpProxy_IsValidIpAddr g_pstCoreAM4FunTable->pfIP_ArpProxy_IsValidIpAddr
/* Added by l57500 for 同步VISPV1R5问题单A82D13365,2007-05-09 */
/* 查询指定的地址是否和接口上的地址处于相同网段 */
#define ETH_IP_IF_IsSameNet g_pstCoreAM4FunTable->pfIP_IF_IsSameNet
/* End of addition */

#define ETH_IP_IsLocalIfAddr g_pstCoreAM4FunTable->pfIP_IsLocalIfAddr
#define ETH_IP_IsBroadcast g_pstCoreAM4FunTable->pfIP_IsBroadcast

/* Added by likaikun213099, 地址冲突告警处理, 2014/10/24 */
#define ETH_IP_SetIpConflictFlag   g_pstCoreAM4FunTable->pfIP_SetIpConflictFlag
#define ETH_IP_ClearIpConflictFlag g_pstCoreAM4FunTable->pfIP_ClearIpConflictFlag

extern ULONG IP_Eth_IsValidIpAddr( IFNET_S *pstIfNet, ULONG ulSrcIpAddr, ULONG ulDstIpAddr, USHORT usOpType);
extern IFNET_S * IF_SearchIfFromChain( IFNET_S * pIf , ULONG ulSearch );

#define ETHARP_INPUT 0
#define ETHARP_OUTPUT 1

#define ETHARP_MAX_IP_CONFLICT_ITEM         8  /* 冲突地址最大数*/
#define ETHARP_MAX_IP_MAC_ITEM              4  /* 一个冲突IP对应physical地址最大数*/
#define ETHARP_IP_CONFLICT_DETECT_TIMEOUT   10 /* 冲突检测定时器TimeOut时间 */
#define ETHARP_IP_CONFLICT_UPDATE_TIMEOUT   10 /* 冲突更新定时器TimeOut时间 */
#define ETHARP_STATE_CONFLICT               1  /* 冲突状态 */
#define ETHARP_STATE_WAITFORREPLY           2  /* 等待回复状态 */
#define ETHARP_IP_CONFLICT_NOT_FOUND        0xffff
#define ETHARP_IPCONFLICTITEM_ADD_SUCC      2  /* IP冲突表项添加成功 */
#define ETHARP_IPCONFLICTITEM_REF_SUCC      3  /* IP冲突表项刷新成功 */
#define ETHARP_CONFLICTIP_IS_NOEXIT         0  /* 表项中的冲突IP不存在 */
#define ETHARP_CONFLICTIP_IS_EXIT           1  /* 表项中的冲突IP存在 */

/* 使能VLANIF代理后，对同一个地址的最大待应答的ARP请求个数 */
#define ETHARP_MAX_COUNT_TOREPLY        64

/* 地址冲突表项 */
typedef struct tagMacFlagItem
{
    UCHAR  ucMac[6];        /*与地址冲突对应的physical地址*/
    UCHAR  ucFlag;          /*地址physical地址确定的冲突项的冲突标志 ETHARP_STATE_CONFLICT, ETHARP_STATE_WAITFORREPLY */
    UCHAR  ucTimeCount;     /*计时器 单位s */
}ETHARP_MAC_Flag_Item_S;  
typedef struct tagIpConflictItem
{
    ULONG ulIPConflictType; /*冲突的地址类型:ETHIP(1);OMIP(2)*/
    ULONG ulIfIndex;        /*冲突的IfIndex*/    
    ULONG ulIpAddr;         /*冲突地址*/
    ULONG ulMacNum;         /*同一个冲突地址对应冲突physical地址个数*/
    ETHARP_MAC_Flag_Item_S stMacFlagItem[ETHARP_MAX_IP_MAC_ITEM] ;/*一个地址可以检测4个与其冲突的physical地址*/
    ULONG ulVrfIndex;      /*ulIfIndex 所在的vrf index  DTS2013040700986 */
}ETHARP_IP_CONFLICT_ITEM_S;

typedef struct tagIpSendFreeArpNode
{
    SLL_NODE_S stSllNode;
    ULONG ulIfIndex;
    ULONG ulIpAddr;
    ULONG ulCount;
    ULONG ulOutTimes;
}ETHARP_IPSENDFREEARPNODE_S;

#pragma    pack(1)

typedef  struct  tagDOT1QHDR
{
    UCHAR     aucDestAddr[6];/* Destination physical address */
    UCHAR     aucSrcAddr[6]; /* Source physical address */
    USHORT    usTPID;        /* 802.1q Protype 8100 */
    USHORT    usTCI;         /*user User_priority CFI VLANID */
    USHORT    usLenEtype;    /* Length or the type field */
}ETHARP_VLAN_DOT1QHDR_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* ARP解析信息结构 */
typedef struct tagETHARP_RESOLVE_FAILED
{
    ULONG       ulIfIndex;              /* 接口索引 */
    ULONG       ulIpAddr;               /* 地址 */
    TCPIP_TIME_S stResolveFailedTime;  /* 解析失败时间 */
}ETHARP_RESOLVE_FAILED_S;

/* ARP解析失败记录最大条数 */
#define ETHARP_MAX_RESOVLEFILED    8   

/* ARP解析失败记录结构 */
typedef struct tagETHARP_RESOLVE_RECORD
{
    ETHARP_RESOLVE_FAILED_S g_stArpResloveFailed[ETHARP_MAX_RESOVLEFILED];    /* ARP解析失败信息记录表 */
    ULONG          ulArpRecordCount;                                          /* 解析失败次数 */
}ETHARP_RESOLVE_RECORD_S;

/*记录ARP解析失败信息*/
#define ETHARP_ARP_RESOVLEFAIL_NOTE(ul_ArpIfIndex,ul_ArpIpAddr)\
{\
    ULONG ii = g_stEtharpResolveRecord.ulArpRecordCount;\
    ETHARP_RESOLVE_FAILED_S *pstArpResolveFailed = NULL;\
    ii %= ETHARP_MAX_RESOVLEFILED;\
    pstArpResolveFailed = &g_stEtharpResolveRecord.g_stArpResloveFailed[ii];\
    (VOID)TCPIP_Get_CurrentTime(&pstArpResolveFailed->stResolveFailedTime);\
    pstArpResolveFailed->ulIfIndex = ul_ArpIfIndex;\
    pstArpResolveFailed->ulIpAddr = ul_ArpIpAddr;\
    g_stEtharpResolveRecord.ulArpRecordCount++;\
}

/* ETHARP报文处理勾子(构成链表) */
typedef struct tagEtharpIntermediateDeal
{
    ULONG ulPriority;
    ETHARP_INTERMEDIATE_HOOK_FUNC pfEtharpDealHookFunc;  /* The Registered Function Pointer */
    struct tagEtharpIntermediateDeal *pstNext;
}ETHARP_INTERMEDIATE_DEAL_HOOK_S;

/* MAC信息节点 */
typedef struct tagMACNode
{
    ULONG  ulPktCount;           /* 一定时间内收到该MAC的计数 */
    ULONG  ulTimeCount;          /* 超时计数 */
    UCHAR  ucMac[MACADDRLEN];    /* physical地址 */
    UCHAR  ucPadding[2];         /* 填充位 */ 
}MAC_NODE_S;

/* 动态黑名单节点 */
typedef struct tagArpBlackNode
{
    ULONG                  ulPktCount;           /* 一定时间内收到该MAC的计数 */
    ULONG                  ulBlakNodeTimeOut;    /* 黑名单节点老化时间点 */
    UCHAR                  ucMac[MACADDRLEN];
    UCHAR                  ucPadding[2];
    struct tagArpBlackNode *pstPreNode;
    struct tagArpBlackNode *pstNextNode;
}BLACK_NODE_S;

/* 动态黑名单头节点 */
typedef struct tagArpGuardBlackNodeHead
{
    BLACK_NODE_S            *pstNodeList; 
    BLACK_NODE_S            *pstNodeListTail;   /*增加指向链表尾部的指针 */
    ULONG                   ulNodeNum;
}ARP_GUARD_BLACK_HEAD;

/* ARP潜在攻击者节点 */
typedef struct tagArpGuardAttackNode
{
    struct tagArpGuardAttackNode *pstPreNode;     /* 前一个攻击者 */
    struct tagArpGuardAttackNode *pstNextNode;    /* 后一个攻击者 */
    MAC_NODE_S                    stAttackNode;   /* 当前攻击者信息,只使用ulPktCount和ucMac字段,不使用超时字段ulTimeCount */
}ARP_GUARD_ATTACK_NODE_S;

/* ARP潜在攻击者链表头节点 */
typedef struct tagArpGuardAttackHead
{
    ULONG                   ulNodeNum;             /* 当前的潜在攻击者个数 */
    ARP_GUARD_ATTACK_NODE_S *pstNodeList;          /* 潜在攻击者链表头 */
}ARP_GUARD_ATTACK_HEAD_S;

/* ARP防欺骗节点信息 */
typedef struct tagArpGuardNode
{
    ULONG ulIpAddr;                                 /* 地址 */
    ETHARP_ARPRTENTRY_S     *pstArpEntry;           /* ARP结点 */
    ARP_GUARD_BLACK_HEAD    stBlackListHead;        /* 动态黑名单头节点,动态黑名单节点内存需要动态申请释放 */
    MAC_NODE_S              stCurNode;              /* 当前节点信息,最近一次收到的ARP报文信息,
                                                       只使用ulTimeCount和ucMac字段,不使用ulPktCount字段 */
    struct tagArpGuardNode  *pstPreNode;
    struct tagArpGuardNode  *pstNextNode;
    UCHAR                   ucNodeState;            /* ARP防欺骗节点的状态,信任和非信任状态 */
    UCHAR                   ucWarningFlag;          /* 告警标志,1表示已经上报告警，0表示恢复告警 */
    UCHAR                   ucAttackWarningFlag;    /* ARP攻击告警标志,1表示已经上报告警，0表示当前无告警 */
    UCHAR                   ucPadd;                 /* 保留字段 */
    MAC_NODE_S              stTrustNode;            /* 存放当前的信任MAC信息,只使用ulPktCount,ulTimeCount和ucMac字段.
                                                       信任节点ulTimeCount在存在潜在攻击者时,1秒定时器超时1次就递增,
                                                       表示尝试发送ARP报文的次数.ulPktCount表示收到的信任MAC对应的ARP报文计数. */
    ARP_GUARD_ATTACK_HEAD_S stAttackListHead;       /* 潜在攻击者头节点,潜在攻击者节点内存需要动态申请释放 */   
    ULONG                   ulAttackCount;          /* 攻击次数,试图改变MAC的次数 */
    ULONG                   ulAttackWarningTimeOut; /* 攻击告警的检测周期1分钟, 这里是告警检测的超时处理次数 */
    MAC_NODE_S              stAttackMaxWaningNode;  /* 攻击次数最多的潜在攻击者信息,用于告警上报*/
    ARP_GUARD_ATTACK_HEAD_S stWarningAttackListHead;      /* 60秒告警期间攻击者记录表项*/   

}ARP_GUARD_NODE_S;

/* Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-01. 修改原因: lib小型化,支持ARP防欺骗功能可裁剪 */
typedef struct tagETHARP_GUARD_PROC_HOOK
{
    VOID (*pfARP_Guard_FreeNode)(ARP_GUARD_NODE_S *pstGuardNode);
    VOID (*pfARP_Guard_Update)(ARP_GUARD_NODE_S *pstGuardNode, UCHAR *pszMac);
    ULONG (*pfARP_Guard_SearchDynamicBlackMac)(ARP_GUARD_NODE_S *pstGuardNode, UCHAR *pszMac);
    VOID (*pfARP_Guard_NewNode)(ETHARP_ARPRTENTRY_S *pstArpEntry, ULONG ulIpAddr, UCHAR *pszMac);
    ULONG (*pfARP_Guard_SearchStaticBlackMac)(ULONG ulIpAddr, ULONG ulVrfIndex, UCHAR *pszMac);

/* Add by b00177000/shuxieliu00176784, at 2011-06-01. 修改原因: 支持ARP防欺骗HA功能 */
    ULONG (*pfARPGUARD_HA_BatchBackup)(VOID);
    ULONG (*pfARPGUARD_HA_RealTimePack)(USHORT usType, UCHAR * pucData, USHORT usInBufLen);
    ULONG (*pfARPGUARD_HA_Input)(UCHAR *pucBuf, ULONG ulMsgLen);
    VOID  (*pfARPGUARD_HA_DebugOutPut)(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);
    ULONG (*pfARPGUARD_HA_Smooth)(VOID);
    ULONG (*pfARPGUARD_HA_Clean)(VOID);
    ULONG (*pfARP_Guard_GetSwitch)(ULONG *pulValue);
    ULONG  (*pfARP_Guard_BlackList_Is_Full)(ARP_GUARD_NODE_S *pstGuardNode);
    ULONG  (*pfARP_Guard_Is_Trust)(ARP_GUARD_NODE_S *pstGuardNode);
}ETHARP_GUARD_PROC_HOOK_S;

/* Modify by z00171897/s00176784, at 2011-06-02. 修改原因: 支持获取保存ARP报文队列 */
#pragma    pack( 1 )

/* 带VLAN的SNAP以太头 */
typedef struct tagETHSNAPHDR_WITHVLAN
{
    UCHAR  ucHdrDstMacAddr[6];     /*目的physical地址*/ 
    UCHAR  ucHdrSrcMacAddr[6];     /*源physical地址  */
    USHORT  usVlanEthtype;                   /*0x8100*/
    USHORT  usVlanTag;               /* vlan标签 */
    USHORT usLen;                  /* 协议类型长度字段    */
    UCHAR  ucDSAP;                 /* destination service access point*/
    UCHAR  ucSSAP;                 /* source service access point */
    UCHAR  ucCtrl;                 /* control domain */
    UCHAR  ucORI[3];                              
    USHORT usType;
}ETHSNAPHDR_WITHVLAN_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* Begin Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. 修改原因: 支持VLAN配置不一致的告警 */
/* 报文信息 */
typedef struct tagETHARP_PKT_INFO
{                                
    USHORT usType;  /* 报文类型,IP,ARP等 */
    USHORT usRes;   /* 保留字段 */
    ULONG  ulSrcIp; /* ARP报文中的源IP,网络序.只对ARP报文有效 */
    ULONG  ulDstIp; /* ARP报文中的目的IP,网络序.只对ARP报文有效 */
}ETHARP_PKT_INFO_S;
/* End Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. 修改原因: 支持VLAN配置不一致的告警 */


#define ETHARP_ARP_QUE_MIN_PKTS_ONETIME     40 /*ARP队列一次处理的ARP报文个数最小值*/

/* Support maximum of 8 response to GARP with Conflictiong IP. */
#define ETHARP_MAX_CONFLICT_RESP    8

/* Structure to store details of conflicted incoming GARP. */
typedef struct tagArpConflictTime
{
    ULONG ulSecHigh;        /* Dynamic ARP entries timestamp higher 4 bytes */ 
    ULONG ulSecLow;         /* Dynamic ARP entries timestamp lower 4 bytes */ 
    ULONG ulIpAddr;         /* Conflicting address */
    ULONG ulVrfIndex;       /* Attached Vrf Index */
} ARP_CONFLICT_TIME_S;

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _ETHARP_H_ */

