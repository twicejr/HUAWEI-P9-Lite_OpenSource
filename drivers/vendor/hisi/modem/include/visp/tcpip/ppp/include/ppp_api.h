/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ppp_api.h
*
*  Project Code: VISPV100R006C02
*   Module Name: PPP  
*  Date Created: 2008-03-17
*        Author: chenfutian69112
*   Description: PPP模块提供的对外数据结构定义和API声明
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*  2008-08-25   f54882                  Modify for BC3D00263
*
*******************************************************************************/
#ifndef _PPP_API_H_
#define _PPP_API_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "ppp/include/mp_api.h"

/**********************************************************************
*                        对外提供的错误码
***********************************************************************/

/*注意:
如果修改错误码，请同步修改ppp_info.c 文件中的
CHAR* g_apszPPPErrorInfo_En[] 描述 
added by l61496 2007-9-10
*/
typedef enum enPppProErrorInfo
{
    PPP_NOENCAP_ERROR = VOS_ERR + 1,    /* 2 */ 
    PPP_WRONGPARA_ERROR,                /* 3 */
    PPP_NOTHISINTERF_ERROR,             /* 4 */
    PPP_DNSIPADDRESS_SAME,              /* 5 */
    PPP_DNSIPADDRESS_INVALID,           /* 6 */
    PPP_DNSIPADDRESS_PRI_IS_INVALID,    /* 7 主DNS无效 */
    PPP_DNSIPADDRESS_SEC_IS_INVALID,    /* 8 从DNS无效 */
    PPP_DNSIPADDRESS_NOEXIST,           /* 9 */
    PPP_CIPHERPASSWORD_WRONG,           /* 10 */
    PPP_IFNETCB_NOEXIST,                /* 11 */
    PPP_PPPCB_NOEXIST,                  /* 12 */
    PPP_CONFIGINFO_NOEXIST,             /* 13 */
    PPP_CONFIGINFO_NOEXIST_2,           /* 14 */
    PPP_LCPCB_NOEXIST,                  /* 15 */
    PPP_IPCPCB_NOEXIST,                 /* 16 */

    PPP_IPHC_DISABLE,                   /* 17 */
    PPP_IPHC_DISABLE_2,                 /* 18 */
    PPP_IPHC_CONTEXT_NOTEXIST,          /* 19 */
    PPP_IPHC_CONTEXT_NOTEXIST_2,        /* 20 */
     
    PPP_NEGOPHASE_ERR,                  /* 21 negotiate phase error*/
    PPP_NEGOTYPE_ERR,                   /* 22 negotiate protocol error */
    PPP_FSMSTATE_ERR,                   /* 23 protocol fsm state error */
    
    PPP_MUXCPCB_NOEXIST,                /* 24 */
    PPP_MUX_DISABLE,                    /* 25 */
    PPP_MUX_CONTEXT_NOTEXIST,           /* 26 */
    
    PPP_IP6CPCB_NOEXIST,                /* 27 */
    PPP_EXCEED_MAX_CBNUM,               /* 28 */

    PPP_CONFIG_CONFLICT,                /* 29 PPP相关配置冲突，如，VJ-IPHC、PAP-CHAP */
    PPP_PARA_NULLPOINTER,               /* 30 输入参数为空指针 */
    PPP_PROTOCOL_INVALID,               /* 31 无效的协议类型 */
    PPP_HOSTNAME_INVALID,               /* 32 无效的用户名(过短或超长) */
    PPP_HA_IS_SMOOTHING,                /* 33 HA正在平滑处理或手动倒换处理，用户操作接口则返回此错误码 */

    PPP_CONFIG_IFCONFLICT,              /* 34 */
    PPP_IP6CB_NOEXIST,                  /* 35 获取IPv6的控制块失败 */
    PPP_WRONGSETPARA_ERROR,             /* 36 是否设置开关参数错误 */
    PPP_GETCB_FAIL,                     /* 37 获取PPP控制块失败 */
    PPP_PHYTYPE_ERR,                    /* 38 物理类型错误 */
    PPP_GETCONFIGINFO_FAIL,             /* 39 获取配置信息失败 */
    PPP_CIPHERPASSWORD_WRONGLONG,       /* 40 pwd过长 */
    PPP_SETONEOPT_FAIL,                 /* 41 设置单个开关状态失败 */
    PPP_SETGLOBEONEOPT_FAIL,            /* 42 设置单个全局开关失败 */
    PPP_SETNODEONEOPT_FAIL,             /* 43 设置单个全局节点开关失败 */
    PPP_UPDATECONFIGINFO,               /* 44 更新配置信息 */

    PPP_CANOT_SET_OSICP,                /* 45 该接口不能设置是否协商OSICP*/
    PPP_OSICPCB_NOEXIST,                /* 46 OSICP 控制块不存在*/

    PPP_COM_NULL,                       /* 47 组件虚表为空 */
    PPP_VA_NOEXIST,                     /* 48 Dialer或者VT接口下的VA接口不存在 */
    PPP_NOT_3D_MODE,                    /* 49 接口配置非三维模式 */
    PPP_PARA_IP_WRONG,                  /* 50 */
    PPP_ERR_PORT_IS_VIRTUAL,            /* 51 非本板接口 */
    PPP_FUNCHOOK_NULL,                  /* 52 函数钩子为空 */
    PPP_IS_SHUTDOWN,                    /* 53 PPP接口已经被shutdown了 */
    PPP_IPCTL_NOTEXIST,                 /* 54 IP控制块为空 */
    PPP_CFG_MTU_FAIL,                   /* 55 MTU参数越界 */
    PPP_CONFIGERR_MEMORY,               /* 56 内存分配失败 */
    PPPMUX_COM_NULL,                    /* 57 PPPMUX组件为空 */
    PPP_TASKRAP_NULL_IFNET,             /* 58 任务抢占导致接口被删58 */

    PPP_ERR_NEG_TIME_REACHMAX,          /* 59 用户指定的协商时间超出范围 */
    PPP_ERR_CREATE_TIMER_FAIL,          /* 60 创建定时器失败 */

    PPP_ERR_NOT_PPP_ITF = 61,           /* 61 接口不是PPP接口 */

    PPP_LCPFSM_NOTOPEN,                 /* 62 NP逻辑获取VISP内部PPP Lcp Echo相关信息时, LCP状态机状态不为OPEN状态 */
    PPP_TIMER_CREATION_FAIL,
    PPP_INVALID_INPUT,

    PPP_ERRCODE_END         /* 错误码上限值，仅作错误码边界判断，以后增加错误码时必须定义在此值之前 */
}PPP_PRO_ERROR_INFO_E;
/*注意:
如果修改错误码，请同步修改ppp_info.c 文件中的
CHAR* g_apszPPPErrorInfo_En[] 描述 
added by l61496 2007-9-10
*/


/**********************************************************************
*                        对外提供的宏定义
***********************************************************************/

/* Modified by z43740: 支持RFC2486, 2006/05/29 */
#define PPP_MAXUSERNAMELEN     72
/* Modify by b00177000 2011-08-30,for DTS2011083000610, 修改原因:无线基站维优小需求:用户pwd可以最大支持20个字符 */
#define PPP_MAXUSERPWDLEN      20
#define PPP_MAXUSERPWDLENOLD   16

#define PPP_MAXCALLBACKDIALERSTRINGLEN  64
#define PPP_CALLINGNUM_LEN              64
#define PPP_CALLEDNUM_LEN               64

#define PPP_MP_DISCR_MAX_LENGTH         20  /* 终端描述符的最大长度 */
#define PPP_MAX_CALLBACK_INFO_LEN       20
#define MC_PREFIXE_MAX_NUM              16  /* 前缀省略支持的最大等级数 */

/*作为TCPIP_GetPPPInfo的入参ulType传递*/
#define PPP_SELF            0
#define PPP_USEDCONFIG      1
#define PPP_CONFIG          2   
#define PPP_LCP             0xc021          /* Link Control Protocol */
#define PPP_IPCP            0x8021          /* IP Control Protocol */
#define PPP_PPPMUXCP        0x8059          /* PPP Multiplexing Control Protocol */
#define PPP_OSICP           0x8023          /* OSI Control Protocol */
#define PPP_IP6CP           0x8057          /* IPv6 Control Protocol */

/*作为TCPIP_SetPppAuthType的入参ulType传递*/
#define TCPIP_AUTH_NONE 0
#define TCPIP_AUTH_PAP  1
#define TCPIP_AUTH_CHAP 2
#define TCPIP_AUTH_ALL  3

#define PPP_NP_NOT_HANDLE_LCP_ECHO 0
#define PPP_NP_HANDLE_LCP_ECHO 1



#ifndef DHCP4C_DNSIP_NUM
#define DHCP4C_DNSIP_NUM       6 /* dns server 地址个数 */
#endif

/*用于用户名和pwd验证(CHAP/PAP)*/
#define PPPMAXTUNNELSERVERNUM  5
#define PPP_MAXPERUSERCFGLEN   10

#define INTERFACE_ID_LEN       8


#define PPP_INTERFACEID_INDEX   8

#define PPP_IP6_INTERID_ISZERO(InterfaceID) \
( (InterfaceID)[0]== 0x00 && \
   (InterfaceID)[1]== 0x00 && \
   (InterfaceID)[2]== 0x00 && \
   (InterfaceID)[3]== 0x00 && \
   (InterfaceID)[4]== 0x00 && \
   (InterfaceID)[5]== 0x00 && \
   (InterfaceID)[6]== 0x00 && \
   (InterfaceID)[7]== 0x00 )

#define  PPP_IP6_CHECK_LINKLOCAL_ADDR(pstIpv6Addr)  \
   (PPP_IP6_INTERID_ISZERO((UCHAR *)((UCHAR *)pstIpv6Addr + PPP_INTERFACEID_INDEX))) ? VOS_ERR : VOS_OK 

/********************** PPP告警相关的宏定义 **********************/
#define PPP_IPHC_PARA_DIFF              0x0001  /* 对应告警ID为WARNING_PPP_IPHC_PARA_DIFF */
#define PPP_IPCONFLICT                  0x0002  /* PPP的地址协商冲突告警 */
#define PPP_LOOPBACK                    0x0004  /* PPP的链路环回告警 */
#define PPP_MP_ED_DIFF                  0x0008  /* PPP的MP终端描述符不一致告警*/
#define PPP_LCP_AUTH_NEGOTIATE_FAILURE  0x0010  /* LCP认证协议协商不满足导致协商失败的告警 */
#define PPP_LCP_MP_NOBIND               0x0020  /* LCP协商时探测到一段绑定到MP组下一端没有绑定到MP组告警 */
#define PPP_MP_SUBLINKLOWLIMIT          0x0040  /* 设定MP下限阀值导致链路断链告警 */
#define PPP_MP_CFG_DIFF                 0x0080  /* 本端或对端子通道PFC/ACFC/MHF/SSNHF/MRU/MRRU/PREFIX不一致导致LCP down */
#define PPP_PAP_AUTH_FAILURE            0x0100  /* PAP认证失败，对应WARNING_PPP_AUTH_FAILURE */
#define PPP_CHAP_AUTH_FAILURE           0x0200  /* CHAP认证失败，对应WARNING_PPP_AUTH_FAILURE */
#define PPP_NPINFO_NOCONSISTENT         0x0400  /* VISP下发给NP的信息与NP生效的信息不一致，对应WARNING_PPP_NPINFO_NOCONSISTENT */
#define PPP_DOWN_PPI_FAIL               0x0800  /* 下发NP失败，对应WARNING_PPI_DOWN_PPP_FAIL */
#define PPP_NEG_NOT_PASS                0x1000  /* 规定时间内协商不通过时对外告警，对外对应WARNING_PPP_NEG_NOT_PASS */

/**********************************************************************
*                        对外提供的数据结构定义
***********************************************************************/

/*供TCPIP_ReceiveAuthResult接口中的ulResult字段填写验证结果,以返回给VISP
  用户只要填写PPP_PRIM_ACCEPT或PPP_PRIM_REJECT即可*/
typedef enum enPppAuthPrimID
{
    PPP_PRIM_JOIN = 1,
    PPP_PRIM_CHAP,
    PPP_PRIM_ACCT,

    
    PPP_PRIM_LEAVING,
    PPP_PRIM_ACCEPT,
    PPP_PRIM_REJECT,
    PPP_PRIM_BYE,
    PPP_PRIM_CUT,
    
    
    PPP_PRIM_EXECUSERNULL,
    PPP_PRIM_LEAVING_OK
}PPP_AUTH_PRIMID_E;


/*PPP Debug Flag Info*/
typedef struct tagPppDebugInfo
{
    ULONG ulDebug_Verbose_SetNum;/* 设置Verbose信息打印次数 */
    ULONG ulDebug_Verbose_Octets;/* 设置的Verbose信息打印前N字节数 */
    ULONG ulDebug_Verbose_CountNum; /* Verbose 信息打印次数计数 */
    
    UCHAR ucDebug_Lcp_Packet;
    UCHAR ucDebug_Lcp_Event;
    UCHAR ucDebug_Lcp_Error;
    UCHAR ucDebug_Lcp_StateChange;
    UCHAR ucDebug_Lcp_Action;
    UCHAR ucDebug_Lcp_Verbose;

    UCHAR ucDebug_Lcpecho_Packet;
    UCHAR ucDebug_Lcpecho_Event;
    UCHAR ucDebug_Lcpecho_Action;
    
    UCHAR ucDebug_Ipcp_Packet;
    UCHAR ucDebug_Ipcp_Event;
    UCHAR ucDebug_Ipcp_Error;
    UCHAR ucDebug_Ipcp_StateChange;
    UCHAR ucDebug_Ipcp_Action;
    UCHAR ucDebug_Ipcp_Verbose;

    UCHAR ucDebug_Ip6cp_Packet;
    UCHAR ucDebug_Ip6cp_Event;
    UCHAR ucDebug_Ip6cp_Error;
    UCHAR ucDebug_Ip6cp_StateChange;
    UCHAR ucDebug_Ip6cp_Action;
    UCHAR ucDebug_Ip6cp_Verbose;

    UCHAR ucDebug_Pap_Packet;
    UCHAR ucDebug_Pap_Event;
    UCHAR ucDebug_Pap_Error;
    UCHAR ucDebug_Pap_StateChange;
    UCHAR ucDebug_Pap_Verbose;

    UCHAR ucDebug_Chap_Packet;
    UCHAR ucDebug_Chap_Event;
    UCHAR ucDebug_Chap_Error;
    UCHAR ucDebug_Chap_StateChange;
    UCHAR ucDebug_Chap_Verbose;

    UCHAR ucDebug_Osicp_Packet ;
    UCHAR ucDebug_Osicp_Event ;
    UCHAR ucDebug_Osicp_Error ;
    UCHAR ucDebug_Osicp_StateChange ;
    UCHAR ucDebug_Osicp_Action;
    UCHAR ucDebug_Osicp_Verbose;
    UCHAR ucDebug_Osi_Packet ;
    UCHAR ucDebug_Osi_Verbose ;

    UCHAR ucDebug_Ip_Packet;
    UCHAR ucDebug_Ip_Verbose;
    
    UCHAR ucDebug_Ip6_Packet; /*显示所有的IPv6报文*/
    UCHAR ucDebug_Ip6_Verbose;
    
    UCHAR ucDebug_MP_Event;
    UCHAR ucDebug_MP_Packet;
    UCHAR ucDebug_MP_Error;
    UCHAR ucDebug_MP_Verbose;

    UCHAR ucDebug_VJComp_Packet;
    UCHAR ucDebug_VJComp_Verbose;

    UCHAR ucDebug_Lqm_Packet;
    UCHAR ucDebug_Lqm_Verbose;

    UCHAR ucDebug_Muxcp_Packet ;
    UCHAR ucDebug_Muxcp_Event ;
    UCHAR ucDebug_Muxcp_Error ;
    UCHAR ucDebug_Muxcp_StateChange;
    UCHAR ucDebug_Muxcp_Action;
    UCHAR ucDebug_Muxcp_Verbose;

    UCHAR ucDebug_Pppmux_Packet;
    UCHAR ucDebug_Pppmux_Error;
    UCHAR ucDebug_Pppmux_Verbose;
    UCHAR ucDebug_IPHC_Verbose;/* 用于打印IPHC原始报文信息 */

    UCHAR ucDebug_Core_Event;
    UCHAR ucDebug_Packet_Verbose;/*独立开关，不受all的控制*/
    UCHAR ucDebug_Link_PhaseChange;
}PPPDEBUGINFO_S;


/*PPP Control Block Info*/
typedef struct tagTCPIP_PppInfo
{
    ULONG bIsAsync: 1,        /* 是否是异步口, 在LCP中判断是否协商ACCMAP */
          bSynAsyConvert: 1,  /* 对于异步口，用于确定是否由PPP进行同/异步报文转换 */
          bLoopBacked: 1,     /* 接口是否发生了自环 */
          bLowerIsUp: 1, 
          bIsDialer:1,       /* 是否拨号口 */
          bIsCallIn:1,       /* 是否是呼入,用于判断是否callback */
          bIsCallBackUser:1, /* 是否是callback用户,验证时从AAA获得 */
          bMpChannelType:2,  /* MP通道类型
                                0(PPP_MP_NONE):不是MP
                                1(PPP_MP_SUBCHANNEL):MP子通道
                                2(PPP_MP_FATHER):MP父通道
                                3(PPP_MP_TEMPLATE):MP模版
                             */
          bPppInterleave:1,    /*是否配置LFI*/
          bRunningPoeClient:1, /* 表明该PPP Info结构是否用于PPPoE Client*/
          bLqmStatus:1,      /* 表明LQM链路状态 */
          bReserved: 20;     /* 保留,以后使用 */

    ULONG ulRemoteAccm;      /* 对端ACCM控制字 */
    ULONG ulLocalAccm;       /* 本端ACCM控制字 */

    ULONG ulIfIndex;         /* 对应的IFNET索引 */
    ULONG ulVLinkIndex;      /* 保留的VLink索引 */
    ULONG ulRouteIfIndex;    /* 路由可见接口的IFNET索引 */

    ULONG usPhase;           /* PPP当前所处协商阶段,可以为如下值:
                                 PPP_PHASE_DEAD
                                 PPP_PHASE_ESTABLISH
                                 PPP_PHASE_AUTHENTICATE
                                 PPP_PHASE_CBCP
                                 PPP_PHASE_NETWORK
                                 PPP_PHASE_TERMINATE
                              */

    struct tagPppDebugInfo stPppDebugInfo;  /* 接口的debug开关信息 */

    USHORT usMtu;
    UCHAR  ucPadding_1[2];

    UCHAR ucAuthServer;        
    UCHAR ucAuthClient;
    UCHAR ucPadding_2[2];
    CHAR  szLoginUsrName[PPP_MAXUSERNAMELEN + 1]; /* 对端向我认证时使用的用户名 */
    CHAR  szCallBackDialString[PPP_MAXCALLBACKDIALERSTRINGLEN + 1];
    /*aaa authencation*/
    CHAR  szCalledNumber[PPP_CALLINGNUM_LEN + 1];
    CHAR  szCallingNumber[PPP_CALLEDNUM_LEN + 1];

    ULONG ulUserId;
    ULONG ulIsIsFlag;     /* 是否使能收发ISIS报文，为1使能，0去使能 */
} TCPIP_PPPINFO_S;

/*PPP AUTH MSG*/
typedef struct tagPppAuthMsg
{
    USHORT usType;      /*PAP or CHAP Auth packet*/
    UCHAR ucPktID;      /*报文序号*/
    CHAR szUsrName[PPP_MAXUSERNAMELEN + 2];
    UCHAR ucUsrNameLen;
    CHAR szPwd[LEN_256];/*chap验证时为challege*/
    UCHAR ucPwdLen;
    CHAR szResponse[LEN_256];/*根据用户名取pwd时为pwd，chap验证结果时为生成的response*/
    UCHAR ucResponseLen;
}PPPAUTHMSG_S; 

/*PPP LCP Option*/
typedef struct tagPppLcpOption
{
    /* 是否协商 */
    ULONG neg_mru: 1,
         neg_asyncmap : 1,
         neg_upap : 1,
         neg_chap : 1,
         neg_magicnumber : 1,
         neg_pcompression : 1,
         neg_accompression : 1,
         neg_lqr : 1,
         neg_mrru : 1,      /* mp协商选项，必须协商 */
         neg_ssnhf : 1,     /* mp协商选项，可选项，visp默认不协商，使用长序号 */
         neg_discr : 1,     /* mp协商选项，可选项，visp默认协商，class为1，随机6字节地址 */
         neg_callback : 1,
         neg_mhf : 1,
         neg_prefixE : 1,
         bReserve : 18;

    /* 协商参数值 */
    USHORT  mru;
    USHORT  mrru;
    ULONG   asyncmap;
    ULONG   magicnumber;
    ULONG   numloops;
    UCHAR   chap_mdtype;
    UCHAR   ucPadding[3]; 
    ULONG   lqr_period; /* Reporting period for LQR 1/100ths second */
    UCHAR   discr_len;
    UCHAR   discr_class;
    UCHAR   callbackopr;
    UCHAR   discr_addr[PPP_MP_DISCR_MAX_LENGTH];
    UCHAR   callbackinfo[PPP_MAX_CALLBACK_INFO_LEN];
    UCHAR   callbacklen;

    UCHAR ucPrefixELen;       /* Req报文中前缀省略选项的长度 */
    UCHAR ucMhfCode;          /* MHF选项中code值 */
    UCHAR ucMhfClass;         /* MHF选项中class值 */
    UCHAR ucReserve; 
    
    /* 为了方便前缀省略表的拷贝，将其定义将其定义放在结构的最后，
       后续增加的参数请放在该参数前面，否则处理会有问题 */
    MC_PREFIXE_S *pstPrefixE; /* 前缀省略映射表，该表是一个16个MC_PREFIXE_S元素的数组，存储前缀省略规则 */
} PPP_LCP_OPTION_S;

/*PPP LCP Info*/
typedef struct tagTCPIP_PppLcpInfo
{
    PPP_LCP_OPTION_S stGotOptions;    /* 已经与对方协商成功的我的选项 */
    PPP_LCP_OPTION_S stHisOptions;    /* 已经与我协商成功的对方的选项 */
    PPP_LCP_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_LCP_OPTION_S stAllowOptions;  /* 允许对方与我协商的我的选项 */
} TCPIP_PPPLCPINFO_S;

/*PPP IPCP Option*/
typedef struct tagPppIpcpOption
{
    /* 是否协商 */
    ULONG neg_addr :         1,   /* Negotiate Address? */
          old_addrs:         1,   /* Use old (IP-Addresses) option? */
          req_addr :         1,   /* Ask peer to send address? */
          neg_vj :           1,   /* Van Jacobson Compression? */
          neg_dnsaddr0 :     1,   /* negotiate Primary DNS server address? */
          req_dnsaddr0 :     1,   /* Ask peer to send DNS server address? */
          neg_nbnsaddr0 :    1,   /* negotiate Primary NBNS server address? */
          req_nbnsaddr0 :    1,   /* Ask peer to send NBNS server address? */
          neg_dnsaddr1 :     1,   /* negotiate Secondary DNS server address? */
          req_dnsaddr1 :     1,   /* Ask peer to send DNS server address? */
          neg_nbnsaddr1 :    1,   /* negotiate Secondary NBNS server address? */
          req_nbnsaddr1 :    1,   /* Ask peer to send NBNS server address? */
          accept_dnsaddr0 :  1,   /* accept peer's value is changed */
          accept_dnsaddr1 :  1,   /* accept peer's value is changed */
          accept_nbnsaddr0 : 1,   /* accept peer's value is changed */
          neg_iphc : 1,           /* IPHC Compression? */
          accept_nbnsaddr1 : 1,   /* accept peer's value is changed */

          breserved: 15;

    USHORT vj_protocol;           /* protocol value to use in VJ option */
    UCHAR maxslotindex, cflag;    /* values for RFC1332 VJ compression neg. */
    ULONG ouraddr, hisaddr;       /* Addresses in HOST BYTE ORDER */
    ULONG dnsaddr0, nbnsaddr0;    /* Primary DNS address and Primary NDNS address (in HOST BYTE ORDER) */
    ULONG dnsaddr1, nbnsaddr1;    /* Secondary DNS and NBNS address (in HOST BYTE ORDER) */  
    
    USHORT iphc_protocol;
    USHORT us_tcp_space;
    USHORT us_non_tcp_space;
    USHORT us_f_max_period;
    USHORT us_f_max_time;
    USHORT us_max_header;

    UCHAR ucRtpCompression;    /* 协商(Enhance) RTP Compression子选项设置 */
    UCHAR ucCompressType;      /* 报文压缩类型 */

    UCHAR ucPadding[2]; 
} PPP_IPCP_OPTION_S ;

/*PPP IP6CP Option*/
typedef struct tagPppIp6cpOption
{
    /* 是否协商 */
#if (VRP_BIG_ENDIAN == VRP_YES)
    ULONG   neg_interfaceid :  1,   /* Negotiate Address? */
            neg_compprotocol:  1,
            nak_isok        :  1,   /* Use old (IP-Addresses) option? */
            bReserve        :  29;  /* 为了以后扩展预留协商位 */
#else
    ULONG   bReserve        :  29,  /* 为了以后扩展预留协商位 */
            nak_isok        :  1,   /* Use old (IP-Addresses) option? */
            neg_compprotocol:  1, 
            neg_interfaceid :  1;   /* Negotiate Address? */
#endif

    UCHAR   my_interface_id[8],his_interface_id[8];
    USHORT  comp_protocol;   /* protocol value to use in compress protocol option */
    UCHAR   ucPadding[2]; 
} PPP_IP6CP_OPTION_S;

/*PPP IPCP Info*/
typedef struct tagTCPIP_PppIpcpInfo
{
    PPP_IPCP_OPTION_S stGotOptions;    /* 已经协商到的我的选项 */
    PPP_IPCP_OPTION_S stHisOptions;    /* 已经协商到的对方的选项 */
    PPP_IPCP_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_IPCP_OPTION_S stAllowOptions;  /* 允许与对方协商的我的选项 */
} TCPIP_PPPIPCPINFO_S ;

/*PPP IP6CP Info*/
typedef struct tagTCPIP_PppIp6cpInfo
{
    PPP_IP6CP_OPTION_S stGotOptions;    /* 已经协商到的我的选项 */
    PPP_IP6CP_OPTION_S stHisOptions;    /* 已经协商到的对方的选项 */
    PPP_IP6CP_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_IP6CP_OPTION_S stAllowOptions;  /* 允许与对方协商的我的选项 */
} TCPIP_PPPIP6CPINFO_S ;

/*PPP PPPMUXCP Option*/
typedef struct tagPppMuxcpOption
{
    /* 是否协商 */
    #if (VRP_BIG_ENDIAN == VRP_YES)
    ULONG neg_defaultpid : 1,    /* Negotiate Default Pid */
          bReserve       : 31;   /* 为了以后扩展预留协商位 */
    #else
    ULONG bReserve       : 31,   /* 为了以后扩展预留协商位 */
          neg_defaultpid : 1;    /* Negotiate Default Pid */
    #endif
    
    /* 协商参数 */
    USHORT usDefaultPid;        /* 默认协议号，若用户不配置则为0x0021 */
    USHORT usReserved;          /* 预留 */
} PPP_MUXCP_OPTION_S; 

/*PPP PPPMUXCP Info*/
typedef struct tagTCPIP_PppMuxcpInfo
{
    PPP_MUXCP_OPTION_S stGotOptions;    /* 已经协商到的我的选项 */
    PPP_MUXCP_OPTION_S stHisOptions;    /* 已经协商到的对方的选项 */
    PPP_MUXCP_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_MUXCP_OPTION_S stAllowOptions;  /* 允许与对方协商的我的选项 */
} TCPIP_PPPMUXCPINFO_S ;

/*PPP OSICP Option*/
typedef struct tagPppOsicpOption
{
    /* 是否协商 */
    UCHAR neg_Align_NPDU ;

    /* 协商参数值 */
    UCHAR ucAlign_NPDU;
} PPP_OSICP_OPTION_S ;

/*PPP OSICP Info*/
typedef struct tagTCPIP_PppOsicpInfo
{
    PPP_OSICP_OPTION_S stGotOptions;    /* 已经协商到的我的选项 */
    PPP_OSICP_OPTION_S stHisOptions;    /* 已经协商到的对方的选项 */
    PPP_OSICP_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_OSICP_OPTION_S stAllowOptions;  /* 允许与对方协商的我的选项 */
} TCPIP_PPPOSICPINFO_S ;

/* PPP协商结果数据结构 */
typedef struct tagPPPNEGORESULT
{
    /* 是否使能 */
    ULONG  neg_upap          : 1,   /* 标志协商PAP验证 */
           neg_chap          : 1,   /* 标志协商CHAP验证 */
           neg_pcompression  : 1,   /* 标志协商PFC */
           neg_accompression : 1,   /* 标志协商ACFC */
           neg_ssnhf         : 1,   /* 标志协商SSNHF */
           neg_mhf           : 1,   /* 标志协商MHF */
           neg_prefixE       : 1,   /* 标志协商Prefix-Elision */
           neg_iphc          : 1,   /* 标志协商IPHC */
           neg_vj            : 1,   /* 标志协商Vjy压缩 */
           neg_mrru          : 1,   /* 标志协商mrru */
           neg_discr          :1,   /*标志协商discr*/
           neg_defaultpid    : 1,   /* 标志协商PPPMux */
           is_lcp_up         : 1,   /* 是否LCP协商成功 */
           is_ipcp_up        : 1,   /* 是否IPCP协商成功*/
           is_pppmux_up      : 1,   /* 是否PPPMUX协商成功*/
           is_osicp_up       : 1,   /*是否osicp协商成功*/
           is_ip6cp_up       : 1,   /* 是否IP6CP协商成功*/
           breserved         : 15;  /* 保留 */

    /* LCP */
    USHORT mru;                  /* 协商的mru */
    USHORT mrru;                 /* 协商的mrru */
    UCHAR ucMhfCode;             /* MHF选项支持长序列头格式还是短序列头格式 */
    UCHAR ucMhfClass;            /* MHF选项支持的等级数 */
    UCHAR discr_len;             /*终端描述符长度*/
    UCHAR discr_class;           /*终端描述符类型*/
    
    /*终端描述符*/
    UCHAR discr_addr[PPP_MP_DISCR_MAX_LENGTH];

    MC_PREFIXE_S astPrefixE[MC_PREFIXE_MAX_NUM]; /* 前缀省略映射表 */

    /* IPCP */
    ULONG  ouraddr;              /* 本端地址 */
    ULONG  hisaddr;              /* 对端地址 */
    ULONG  iphc_protocol;
    USHORT us_tcp_space;
    USHORT us_non_tcp_space;
    USHORT us_f_max_period;
    USHORT us_f_max_time;
    USHORT us_max_header;
    UCHAR  ucRtpCompression;     /* 协商(Enhance) RTP Compression子选项设置 */
    UCHAR  ucCompressType;       /* 报文压缩类型 */

    /* MUXCP */
    ULONG ulDefaultPid;         /* 协商的PID */

    /* OSICP */
    UCHAR our_neg_Align_NPDU;        /*本端是否协商NPDU*/
    UCHAR our_ucAlign_NPDU;          /*协商的值*/
    UCHAR his_neg_Align_NPDU;        /*对端是否协商NPDU*/
    UCHAR his_ucAlign_NPDU;          /*协商的值*/
    
    /* IP6CP */
    UCHAR  my_interface_id[8];   /* 本端接口ID */
    UCHAR  his_interface_id[8];  /* 对端接口ID */
} PPPNEGORESULT_S;

/*PPP子协议，仅用于TCPIP_ShowPPPCfgInfo的ulProtocol参数传递*/
typedef enum enPppSubProtocol
{
    PPP_SUB_MUXCP,
    PPP_SUB_IPHC,
    PPP_SUB_MC,
    PPP_SUB_PREFIX,
    PPP_SUB_OSICP
}PPP_SUB_PROTOCOL_E;

/* LQM从驱动获取的字段信息 */
typedef struct tagTCPIP_LQR_STAT
{
    ULONG ulSaveInPackets; /*接收的报文数*/
    ULONG ulSaveInDiscards;/*接收后丢弃的报文数*/
    ULONG ulSaveInErrors;  /*接收到的错误报文数*/
    ULONG ulSaveInOctets;  /*接收到的字节数*/
    ULONG ulOutPackets;    /*发送的报文数*/
    ULONG ulOutOctets;     /*发送的字节数*/
} TCPIP_LQR_STAT_S;

/* 统计信息 */
typedef struct tagPppStatistic
{
    /* 计费信息 */
    ULONG ulInOctets;
    ULONG ulInGigaWords;
    ULONG ulOutOctets;
    ULONG ulOutGigaWords;
    ULONG ulInPackets;
    ULONG ulOutPackets;
    ULONG ulOutBadPkts;       /* 发送丢弃报文数 */
    ULONG ulOutBadOctets;     /* 发送丢弃字节数 */
    ULONG ulBadFcsPackets;
    ULONG ulBadAddressPackets;
    ULONG ulBadControlPackets;
    ULONG ulSendDiscReqPackets; /* 接口上发送的discard request报文数 */
    ULONG ulRecvDiscReqPackets; /* 接口上接收的discard request报文数 */
    ULONG ulDownDiscReqPackets; /* 成功down掉其它接口的discard request报文数 */
} PPPSTATISTIC_S;

typedef enum enPppFsmState
{
    PPP_FSM_INITIAL_STATE = 1,  /* 1   Down, hasn't been opened */
    PPP_FSM_STARTING_STATE,     /* 2   Down, been opened */
    PPP_FSM_CLOSED_STATE,       /* 3   Up, hasn't been opened */
    PPP_FSM_STOPPED_STATE,      /* 4   Open, waiting for down event */
    PPP_FSM_CLOSING_STATE,      /* 5   Terminating the connection, not open */
    PPP_FSM_STOPPING_STATE,     /* 6   Terminating, but open */
    PPP_FSM_REQSENT_STATE,      /* 7   We've sent a Config Request */
    PPP_FSM_ACKRCVD_STATE,      /* 8   We've received a Config Ack */
    PPP_FSM_ACKSENT_STATE,      /* 9   We've sent a Config Ack */
    PPP_FSM_OPENED_STATE        /* 10   Connection available */
}PPP_FSM_STATE_E;

/* 配置信息 */
typedef struct tagPppConfigInfo 
{
    ULONG bCallbackReq    : 1,
          bCallbackAcc    : 1,
          bCallInAuth     : 1,
          bAuthRmtChap    : 1,
          bAuthRmtPap     : 1,
          bEnableVJComp   : 1,
          /*bEnableComp     : 1,*/
          bEnablePComp    : 1,
          bEnableACComp   : 1,
          /* End of addition */
          bSetAsMp        : 1,
          bPapPwdEncrypt  : 1,
          bChapPwdEncrypt : 1,
          bAuthRmtList    : 1,

          bAcceptPeerDNS0      :1,
          bRejectPeerDNS0      :1,
          bAcceptPeerDNS1      :1,
          bRejectPeerDNS1      :1,
  
          bEnableIPHComp  : 1,
          bNegoSubOptions : 1,  /* 是否协商RFC3544规定的子选项，added by z43740,2005/09/19 */ 
          bStacCompress   : 1,   
          
          bPppInterleave  : 1,  /* 是否使能MP的分片交叉功能 */

          bPppReorderWindow  : 1,
          bMpDiscriminator:1,   /* SWFD10247 2005.06.11  discriminator negotiation,默认使能,class:1(本地随机分配6字节), */

          bNegoLCPEnable:  1,   
          bNegoNCPEnable:  1,
          /*End for IPOS D00042*/

          bMc         :1,
          bMcPrefixE  :1,
          bSsnhf      :1,
          bPPPMux     :1,  /* 是否协商PPP MUX */
          bNegoDNSEnable   :1, /* 用于POEC协商DNS */
          bLqmNegEnable    :1, /* 是否协商LQM */
          bNegoOSICPEnable :1, /* 是否协商OSI */
          bReserved   :1;

    ULONG ulNegTimeOut;

    USHORT usMaxMpBindNum;/*最大绑定链路数*/
    USHORT usMinFragLen; /*MP开始分段的最小包长, added by pengjimei 2001/09/17*/
    ULONG  ulBindType;
    ULONG  ulBindVTNum;
    ULONG  ulEndpointDiscriminator; /*MP终端描述符值*/
    
    USHORT usMaxDelayLFI;
    USHORT usLqmPeriod;   /* LQM 发送周期值 */
    USHORT usUpSublinkLowLimit; /* mp接口成员端口UP数达到该值时才进行网络层协商 */
    UCHAR  ucNegoMagicNum;      /* 是否协商魔术字标记 */
    UCHAR  ucSelfLoop;          /* 是否设置自环模式标记 */
    UCHAR  ucMpDiscardRequest;  /* MP接口是否处理discard request报文 */
    UCHAR  ucDealAcfcPfc;       /* 是否接受和处理ACFC和PFC协商选项，默认是接受的 */
    UCHAR  ucPadding[2];
    ULONG  ulClosePercentage;   /* 设定的关闭链路的门限 */
    ULONG  ulResumePercentage;  /* 设定的重新启用链路的门限 */
    ULONG  ulPrimDNSIPAddr;     /* 设定的Primary DNS Server地址 */
    ULONG  ulSndDNSIPAddr;      /* 设定的Secondary DNS Server地址 */

    UCHAR cChapHostName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cChapPassword[PPP_MAXUSERPWDLEN + 1];
    UCHAR cPapUserName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cPapPwd[PPP_MAXUSERPWDLEN + 1];
    /* BAPCONFIGINFO_S stBapConfigInfo; */   /* BAP/BACP配置信息 */

    USHORT  iphc_tcp_space;
    USHORT  iphc_non_tcp_space;
    USHORT usFMaxPeriod;    /* 连续发送非TCP压缩报文最大个数 */
    USHORT usFMaxTime;      /* 发送完整首部报文最大间隔时间 */
    USHORT usMaxHeader;     /* 可压缩首部最大长度 */
    UCHAR  ucRtpCompression;/* 协商(Enhanced) RTP Compression子选项设置 */
    UCHAR  ucCompressType;  /* 报文压缩类型 */
    /* End of addition for IPHC,2005/09/19*/
    LONG   lCCOMPANY_FORMAT;
    LONG   lDELETE_UDP_CHKSUM;
    
    UCHAR  ucEnableUniDirection;/*是否支持IPHC单通处理,add by wuhailan,2008-04-11.*/
    UCHAR  ucPadding_2[3];

    USHORT usDefaultPid;        /* Default PID */
    USHORT usSubFrameLen;       /* 最大子帧长度 */
    USHORT usFrameLen;          /* 最大复合帧长度 */
    USHORT usSubFrameCount;     /* 最大子帧数 */
    USHORT usMuxDelay;          /* 最大报文复合时延 */
    
    UCHAR  ucMhfCode;           /* MHF选项的code值 2:长序列头格式；6:短序列头格式 */ 
    UCHAR  ucMhfClass;          /* MHF选项的class值:对应头格式所支持的等级数 */
    ULONG  ulMcPrefixESum;      /* 存在的前缀省略映射对数目 */
    ULONG  ulNcpResendTime;     /* LCP报OPEN时，NCP发送一个CR报文后，再延时补发一个NCP CR报文的时间，范围是0~6000毫秒 */
    MC_PREFIXE_S *pstPrefixE;/* 前缀省略映射表 */  /* 重要:目前代码现状要求此字段必须在最后; 否则会导致逻辑异常 */
}PPPCONFIGINFO_S;


typedef struct tagPppAuthResult
{
    ULONG ulResult;                                  
    ULONG ulUserID;    
    ULONG ulIfnetIndex;                               
    ULONG ulUserType;     
    USHORT usChap;
    CHAR szCallBackDialString[PPP_CALLINGNUM_LEN + 1];
    UCHAR ucPadding_1; 
    ULONG ulIsCallBackUser;                          
    ULONG ulPerUserCfgNum;
    CHAR* pszPerUserCfg[PPP_MAXPERUSERCFGLEN];
    ULONG ulTunnelType; 
    ULONG ulTunnelServerIPNum;                          
    ULONG pulTunnelServerIP[PPPMAXTUNNELSERVERNUM];   
    SHORT   sVpdnGroupNumber;
    UCHAR ucPadding_2[2]; 
}PPPAUTHRESULT_S; 

/*核查开关状态结构*/
typedef struct tagPppVerifySwitch
{
    ULONG ulSwitch; /*核查开关:1-使能;0-去使能*/ 
    ULONG ulPeriod; /*核查周期,[1,0xffffffff),单位s*/   
    ULONG ulIfNum;  /*每次核查接口数,[1,0xffffffff)*/
}PPPVERIFYSWITCH_S;

/* IPHC统计住处数据结构 */
typedef struct tagTCPIP_IPHC_STATISTICS
{
    ULONG ulRcvTotal;           /* 接收报文总数 */
    ULONG ulRcvTcpCompressed;   /* 成功解压缩的TCP报文数 */
    ULONG ulRcvNoTcpCompressed; /* 成功解压缩的非TCP报文数 */
    ULONG ulRcvError;           /* 接收失败的报文数 */
    
    ULONG ulSndTotal;           /* 发送报文总数 */
    ULONG ulSndTcpCompressed;   /* 成功压缩的TCP报文数 */
    ULONG ulSndNoTcpCompressed; /* 成功压缩的非TCP报文数 */
    ULONG ulSndTcpFullHead;     /* 发送完整首部的TCP报文数 */
    ULONG ulSndNoTcpFullHead;   /* 发送完整首部的非TCP报文数 */
}TCPIP_IPHC_STATISTICS_S;

/* PPP协商Down相关的信息 */
typedef struct tagPPPDOWNINFO
{
    ULONG ulDownReason;     /* Down Reason */
    ULONG ulWarningRecord;  /* PPP协商过程中对外通告的协商失败告警记录 */
}PPPDOWNINFO_S;

/**********************************************************************
*                        对外提供的类型定义和用户API声明
***********************************************************************/

/************************ 错误提示信息 ************************/
typedef VOID  (* PPP_GetPeerCallBack_PF)(ULONG ulUserID, ULONG ulIfnetIndex, ULONG ulPeerIPAddress);
typedef ULONG ( * NotifyIpcpDown_HOOK_FUNC)(ULONG ulIfIndex);
typedef ULONG ( * PPPShellAuthRequest)(ULONG ulIfnetIndex, PPPAUTHMSG_S *pMsg);
typedef ULONG ( * PPPShellChapGetUserPsw)(PPPAUTHMSG_S *pstMsg);
typedef ULONG ( * PPPAllocPeerIpAddr)(ULONG ulUserID, ULONG ulIfnetIndex,  PPP_GetPeerCallBack_PF pfGetPeerCallBack);
typedef ULONG ( * PPPFreeAddr)(ULONG ulUserID, ULONG ulIfnetIndex, ULONG ulPeerIPAddress);
typedef ULONG ( * GetLQRStat_HOOK_FUNC)(ULONG ulIfIndex,TCPIP_LQR_STAT_S *pstLQRStat);
typedef ULONG ( * NotifyPppDns_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulSetYes,ULONG ulPriDns, ULONG ulSecDns);
 /* 注册获取PPP信息钩子函数 */
typedef ULONG ( * GET_PPP_NEGO_IP_HOOK_FUN) (ULONG ulIfIndex, ULONG ulLocalIP, ULONG aulDNSIP[],
                                             ULONG ulRemoteIP, ULONG ulMTU, ULONG ulFlag );

/*******************************************************************************
*    Func Name: TCPIP_ShowPPPEffectiveCfgByIfName
*  Description: 显示PPP链路当前生效配置参数
*        Input: CHAR *pszIfName:接口名指针
*               ULONG ulProtocol:子协议号
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/

extern VOID TCPIP_ShowPPPEffectiveCfgByIfName(CHAR *pszIfName,ULONG ulProtocol);
/*******************************************************************************
*    Func Name: TCPIP_ShowIfIPHCConfig
*  Description: 显示PPP接口的IPHC相关配置信息
*        Input: CHAR *pszIfName:接口名指针
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowIfIPHCConfig(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowIPHCContextByIfName
*  Description: 显示PPP接口的上下文详细信息
*        Input: CHAR *pszIfName:接口名指针
*               ULONG ulPacketType:报文格式标记（是否为TCP格式）
*               ULONG ulFlag:压缩/解压缩标记
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowIPHCContextByIfName(CHAR *pszIfName, ULONG ulPacketType, ULONG ulFlag);
/*******************************************************************************
*    Func Name: TCPIP_ShowIfIPHCStat
*  Description: 显示PPP接口的IPHC报文统计信息
*        Input: CHAR *pszIfName:指向接口名称的指针
*               ULONG ulPacketType:TCP/non-TCP格式标记
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowIfIPHCStat(CHAR *pszIfName, ULONG ulPacketType);
/*******************************************************************************
*    Func Name: TCPIP_ShowPPPStateByIfName
*  Description: 显示指定接口的协议状态信息
*        Input: CHAR *pszIfName:指向接口名称的指针
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPPPStateByIfName(CHAR *pszIfName);
/*******************************************************************************
*    Func Name: TCPIP_GetPPPInfo
*  Description: 获取PPP及子协议控制块
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulType:要获取的协议控制块类型
*               VOID *pstPppInfo:要返回的控制块结构
*       Output: pstPppInfo:要返回的控制块结构
*       Return: VOS_OK                    成功
*               PPP_PARA_NULLPOINTER      指针参数值为空
*               PPP_NOTHISINTERF_ERROR    接口索引值为0
*               PPP_IFNETCB_NOEXIST       指定接口不存在
*               PPP_NOENCAP_ERROR         指定接口非PPP链路类型
*               PPP_PPPCB_NOEXIST         指定接口的PPP控制块不存在
*               PPP_PROTOCOL_INVALID      指定的协议类型无效
*               PPP_IPCPCB_NOEXIST        IPCP控制块不存在
*               PPP_MUXCPCB_NOEXIST       PPPMUX控制块不存在
*               PPP_CONFIGINFO_NOEXIST    PPP配置信息控制块不存在
*               VOS_ERR                   PPP模块内部错误。
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPPPInfo(ULONG ulIfIndex, ULONG ulType,VOID *pstPppInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetFsmState
*  Description: 获取各子协议状态机状态
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulProtocol:协议号
*               ULONG *pulState:状态机状态
*       Output: 
*       Return: VOS_OK                    成功
*               PPP_WRONGPARA_ERROR       参数错误（指针参数为空）
*               PPP_NOTHISINTERF_ERROR    指定的接口索引为0
*               PPP_IFNETCB_NOEXIST       指定接口不存在
*               PPP_NOENCAP_ERROR         指定接口非PPP链路类型
*               PPP_PPPCB_NOEXIST         指定接口的PPP控制块不存在
*               VOS_ERR                   指定的协议号错误
*               PPP_FSMSTATE_ERR          协议状态机错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetFsmState(ULONG ulIfIndex, ULONG ulProtocol, ULONG *pulState);
/*******************************************************************************
*    Func Name: TCPIP_GetNegoResult
*  Description: 获取协商结果
*        Input: ULONG ulIfIndex:接口索引
*               PPPNEGORESULT_S *pstGotResult:本端协商接口输出结构指针
*               PPPNEGORESULT_S *pstHisResult:对端协商结果输出结构指针
*       Output: PPPNEGORESULT_S *pstGotResult:本端协商接口输出结构指针
*               PPPNEGORESULT_S *pstHisResult:对端协商结果输出结构指针
*       Return: VOS_OK                    成功  
*               PPP_PARA_NULLPOINTER      指针参数值为空
*               PPP_IFNETCB_NOEXIST       指定接口不存在
*               PPP_NOENCAP_ERROR         指定接口非PPP链路类型
*               PPP_PPPCB_NOEXIST         指定接口的PPP控制块不存在
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetNegoResult ( ULONG ulIfIndex,  PPPNEGORESULT_S *pstGotResult, PPPNEGORESULT_S *pstHisResult );
/*******************************************************************************
*    Func Name: TCPIP_GetPPPDebugInfo
*  Description: 获取PPP Debug信息
*        Input: ULONG ulIfIndex:接口索引，为0时表示取全局debug信息表
*               PPPDEBUGINFO_S *pstPppDebugInfo:获取的debug信息缓冲区指针
*       Output: PPPDEBUGINFO_S *pstPppDebugInfo:获取的debug信息缓冲区指针
*       Return: VOS_OK                           成功
*               PPP_PARA_NULLPOINTER             指针参数值为空
*               PPP_NOTHISINTERF_ERROR           接口索引值为0
*               PPP_IFNETCB_NOEXIST              指定接口不存在
*               PPP_NOENCAP_ERROR                指定接口非PPP链路类型
*               PPP_PPPCB_NOEXIST                指定接口的PPP控制块不存在
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPPPDebugInfo(ULONG ulIfIndex, PPPDEBUGINFO_S *pstPppDebugInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetPppPhase
*  Description: 获取PPP协商所处的阶段
*        Input: ULONG ulIfIndex:接口索引
*               ULONG *pulPhase:PPP协商所处的阶段
*       Output: pulPhase:PPP协商所处的阶段
*       Return: VOS_OK                        成功
*               PPP_NOTHISINTERF_ERROR        接口索引为0
*               PPP_IFNETCB_NOEXIST           指定接口不存在
*               PPP_NOENCAP_ERROR             指定接口非PPP链路类型
*               PPP_PPPCB_NOEXIST             指定接口的PPP控制块不存在
*               PPP_WRONGPARA_ERROR           参数错误（指针参数为空）
*               PPP_NEGOPHASE_ERR             协商阶段错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPppPhase(ULONG ulIfIndex, ULONG *pulPhase);
/*******************************************************************************
*    Func Name: TCPIP_SetInterfaceNego
*  Description: 设置某个接口是否进行LCP/NCP协商
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulNegoLCP:是否协商LCP：0 不协商，1 协商
*               ULONG ulNegoNCP:是否协商NCP：0 不协商，1 协商
*       Output: 
*       Return: VOS_OK                             成功
*               PPP_HA_IS_SMOOTHINGHA              正在平滑处理或手动倒换处理
*               PPP_WRONGPARA_ERROR                参数错误（是非变量须为0或1）
*               PPP_NOTHISINTERF_ERROR             接口索引值为0
*               PPP_IFNETCB_NOEXIST                指定接口不存在
*               PPP_NOENCAP_ERROR                  指定接口非PPP链路类型
*               PPP_PPPCB_NOEXIST                  指定接口的PPP控制块不存在
*               VOS_ERR                            VT接口必须作LCP
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetInterfaceNego(ULONG ulIfIndex,ULONG ulNegoLCP,ULONG ulNegoNCP);
/*******************************************************************************
*    Func Name: TCPIP_GetInterfaceNego
*  Description: 获取某个接口是否要进行LCP/NCP协商
*        Input: ULONG ulIfIndex:接口索引
*               ULONG *pulNegoLCP:是否协商LCP：0 不协商，1 协商
*               ULONG *pulNegoNCP:是否协商NCP：0 不协商，1 协商
*       Output: ULONG *pulNegoLCP:是否协商LCP：0 不协商，1 协商
*               ULONG *pulNegoNCP:是否协商NCP：0 不协商，1 协商
*       Return: VOS_OK                          成功
*               PPP_WRONGPARA_ERROR             参数错误（是非变量须为0或1）
*               PPP_PPPCB_NOEXIST               指定接口的PPP控制块不存在
*               PPP_CONFIGINFO_NOEXISTR         指定接口配置信息控制块不存在
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetInterfaceNego (ULONG ulIfIndex, ULONG *pulNegoLCP, ULONG *pulNegoNCP);
/*******************************************************************************
*    Func Name: TCPIP_GetPppStatics
*  Description: 获取接口下的IP报文统计信息
*        Input: ULONG ulIfIndex:接口索引
*               PPPSTATISTIC_S * pstStat:输出的报文统计信息
*       Output: PPPSTATISTIC_S * pstStat:输出的报文统计信息
*       Return: VOS_OK                  成功
*               PPP_PARA_NULLPOINTER    指针参数值为空
*               PPP_IFNETCB_NOEXIST     指定接口不存在
*               PPP_NOENCAP_ERROR       指定接口非PPP链路类型
*               VOS_ERR                 PPP模块内部错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPppStatics(ULONG ulIfIndex, PPPSTATISTIC_S * pstStat);
/*******************************************************************************
*    Func Name: TCPIP_ClrPppStatics
*  Description: 清除接口下的PPP报文统计信息
*        Input: ULONG ulIfIndex:接口索引
*       Output: 
*       Return: VOS_OK                                 成功
*               PPP_IFNETCB_NOEXIST                    指定接口不存在
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrPppStatics(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_SetInterfaceNegoOsicp
*  Description: 设置PPP接口是否进行OSICP协商
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulNegoOSICP:使能开关
*       Output: 
*       Return: VOS_OK                        成功
*               PPP_WRONGPARA_ERROR           参数错误      
*               PPP_IFNETCB_NOEXIST           接口控制块不存在
*               PPP_NOENCAP_ERROR             指定接口非PPP链路类型
*               PPP_CANOT_SET_OSICP           该接口不能设置是否协商OSICP
*               PPP_PPPCB_NOEXIST             指定接口的PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST        指定接口的配置信息不存在
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetInterfaceNegoOsicp(ULONG ulIfIndex, ULONG ulNegoOSICP);
/*******************************************************************************
*    Func Name: TCPIP_GetInterfaceNegoOsicp
*  Description: 查询PPP接口OSICP协商设置
*        Input: ULONG ulIfIndex:接口索引
*               ULONG *pulNegoOSICP:用来存放接口OSICP协商的设置
*       Output: ULONG *pulNegoOSICP:用来存放接口OSICP协商的设置
*       Return: VOS_OK                              成功
*               PPP_WRONGPARA_ERROR                 参数错误
*               PPP_IFNETCB_NOEXIST                 接口控制块不存在
*               PPP_NOENCAP_ERROR                   指定接口非PPP链路类型
*               PPP_CANOT_SET_OSICP                 该接口不支持操作OSICP选项
*               PPP_PPPCB_NOEXIST                   指定接口的PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST              指定接口的配置信息不存在
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetInterfaceNegoOsicp(ULONG ulIfIndex, ULONG *pulNegoOSICP);
/*******************************************************************************
*    Func Name: TCPIP_EnableACFC
*  Description: 使能/去使能协商ACFC
*        Input: ULONG ulIfIndex:PPP链路的接口索引
*               ULONG ulSetYes:设置开关 1：使能； 0：去使能；其他：非法
*       Output: 
*       Return: VOS_OK                          成功
*               PPP_HA_IS_SMOOTHING             HA正在平滑处理或手动倒换处理
*               PPP_NOTHISINTERF_ERROR          接口索引值为0
*               PPP_IFNETCB_NOEXIST             指定接口不存在
*               PPP_NOENCAP_ERROR               指定接口非PPP链路类型
*               PPP_PPPCB_NOEXIST               指定接口的PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST          指定接口的配置信息不存在
*               PPP_WRONGPARA_ERROR             参数不合法（开关变量须为0或1）
*               PPP_CONFIG_CONFLICT             PPP相关配置冲突（PPPoE链路不支持ACFC）
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableACFC ( ULONG ulIfIndex, ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_SetPppAuthType
*  Description: 设置PPP验证的类型
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulType:验证类型：0，不设置验证；1，设置pap验证；2，设置chap验证,3---ALL
*       Output: 
*       Return: VOS_OK                             成功
*               VOS_ERR                            失败
*               PPP_HA_IS_SMOOTHING                HA正在平滑处理或手动倒换处理
*               PPP_WRONGPARA_ERROR                参数不合法（开关/是非变量须为0或1）
*               PPP_NOTHISINTERF_ERROR             接口索引值为0
*               PPP_IFNETCB_NOEXIST                指定接口不存在
*               PPP_NOENCAP_ERROR                  指定接口非PPP链路类型
*               PPP_PPPCB_NOEXIST                  指定接口的PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST             指定接口的配置信息不存在
*               PPP_CONFIG_CONFLICT                PPP配置冲突（PAP与CHAP不可同时使能）
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPppAuthType(ULONG ulIfIndex, ULONG ulType);

/*******************************************************************************
*    Func Name: TCPIP_GetPppAuthType
* Date Created: 2010-01-19
*       Author: z00104207
*  Description: 获取PPP认证方式
*        Input: ULONG ulIfIndex:      接口索引
*       Output: ULONG *pulType:       PPP认证方式，传入指针不能为空。
*               ULONG *pulCallInAuth: CallInAuth字段，暂无使用，保留将来使用。如
*                                     不获取该字段的值，可以传入空指针。
*       Return: 成功则返回VOS_OK，否则返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-19   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPppAuthType(ULONG ulIfIndex, ULONG *pulType, ULONG *pulCallInAuth);

/*******************************************************************************
*    Func Name: TCPIP_SetChapNamePwd
*  Description: 设置chap验证时的用户名和认证pwd
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulSetYes:是否设置：0为否；1为是
*               ULONG usEncrypt:pwd是否enc ，1为设置enc ，0为取消
*               UCHAR *pcP***W***:待设置的pwd指针
*               UCHAR *pcUsername:待设置的用户名指针
*       Output: 
*       Return: VOS_OK                     成功
*               PPP_HA_IS_SMOOTHING        HA正在平滑处理或手动倒换处理
*               PPP_WRONGPARA_ERROR        参数不合法（是非值须为0或1）
*               PPP_NOTHISINTERF_ERROR     接口索引值为0
*               PPP_IFNETCB_NOEXIST        指定接口不存在
*               PPP_NOENCAP_ERROR          指定接口非PPP链路类型
*               PPP_PPPCB_NOEXIST          指定接口的PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST     指定接口的配置信息不存在
*               PPP_PARA_NULLPOINTER       指针参数值为空
*               PPP_HOSTNAME_INVALID       无效的用户名（长度为0或超过72）
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetChapNamePwd(ULONG ulIfIndex,ULONG ulSetYes,  ULONG usEncrypt, UCHAR *pcPassword, UCHAR *pcUsername);
/*******************************************************************************
*    Func Name: TCPIP_ClrIfIPHCContext
*  Description: 清除接口的上下文信息
*        Input: ULONG ulIfIndex:接口索引
*       Output: 
*       Return: VOS_OK                           成功
*               PPP_CONFIGINFO_NOTEXIST          配置信息不存在
*               PPP_IPHC_DISABLE                 IPHC功能未使能
*               PPP_IPHC_CONTEXT_NOTEXIST        context存储结构不存在
*               PPP_IFNETCB_NOEXIST              接口不存在
*               PPP_NOENCAP_ERROR                接口类型不是PPP
*               PPP_PPPCB_NOEXIST                PPP控制块不存在
*               VOS_ERR                          其它错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrIfIPHCContext (ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPCompress
*  Description: 设置ppp是否进行头部压缩
*        Input: ULONG ulIfIndex:接口索引
*       Output: 
*       Return: VOS_OK                          成功
*               PPP_GETCONFIGINFO_FAIL          获取配置信息失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPCompress(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPCompressType
*  Description: 设置接口的IPHC压缩类型
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulCompressType:报文压缩类型
*               ULONG ulReset:重置默认值标识：0不重置，非0重置
*       Output: 
*       Return: VOS_OK                    成功
*               PPP_HA_IS_SMOOTHING       HA正在平滑处理或手动倒换处理
*               PPP_IPHC_DISABLE          接口上未使能IPHC功能
*               PPP_WRONGPARA_ERROR       参数不合法
*               PPP_IFNETCB_NOEXIST       接口不存在
*               PPP_NOENCAP_ERROR         接口类型不是PPP
*               PPP_PPPCB_NOEXIST         PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST    接口配置信息不存在
*               VOS_ERR                   其它错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPCompressType(ULONG ulIfIndex,ULONG ulCompressType,ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPDebug
*  Description: 设置debug选项
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulDebugAll:是否全部接口设置，1为设置所有选项，0为设置单个选项
*               ULONG ulSetYes:是否设置的标志，1为使用，0为取消，其他非法
*               ULONG ulType:选项类型
*               USHORT usProtocol:选项协议类型，为PPP_LCP、PPP_IPCP等
*               ULONGulPacketNum:打印Verbose信息的次数
*               ULONG ulPacketOctets:打印Verbose信息的前N个字节数
*       Output: 
*       Return: VOS_OK                           成功
*               PPP_WRONGPARA_ERROR              参数不合法
*               PPP_NOENCAP_ERROR                接口类型不是PPP
*               PPP_PPPCB_NOEXIST                PPP控制块不存在
*               VOS_ERR                          其它错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPDebug(ULONG ulIfIndex, ULONG ulDebugAll, ULONG ulSetYes, ULONG ulType,USHORT usProtocol,ULONG ulPacketNum, ULONG ulPacketOctets);
/*******************************************************************************
*    Func Name: TCPIP_DelPPPUdpChkSum
*  Description: 设置是否删除UDP校验和（即是否将UDP校验和置0）
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulDeleteUdpChkSum:是否删除UDP校验和标记：1 删除，0不删除，其它 非法
*       Output: 
*       Return: VOS_OK                      成功
*               PPP_IPHC_DISABLE            IPHC功能不可用
*               PPP_WRONGPARA_ERROR         参数不合法
*               PPP_IFNETCB_NOEXIST         接口不存在
*               PPP_NOENCAP_ERROR           接口类型不是PPP
*               PPP_PPPCB_NOEXIST           PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST      接口配置信息不存在
*               PPP_HA_IS_SMOOTHING         HA正在平滑处理或手动倒换处理
*               VOS_ERR                     其它错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_DelPPPUdpChkSum (ULONG ulIfIndex, ULONG ulDeleteUdpChkSum);
/*******************************************************************************
*    Func Name: TCPIP_SetFMaxPeriod
*  Description: 设置接口的最大连续发送非TCP首部压缩报文数
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulFMaxPeriod:最大连续发送非TCP首部压缩报文数
*               ULONG ulReset:重置默认值标识：0 不重置，非0 重置
*       Output: 
*       Return: VOS_OK                        成功
*               PPP_IPHC_DISABLE              IPHC功能不可用
*               PPP_WRONGPARA_ERROR           参数不合法
*               PPP_IFNETCB_NOEXIST           接口不存在
*               PPP_NOENCAP_ERROR             接口类型不是PPP
*               PPP_PPPCB_NOEXIST             PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST        接口配置信息不存在
*               PPP_HA_IS_SMOOTHING           HA正在平滑处理或手动倒换处理
*               VOS_ERR                       其它错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetFMaxPeriod(ULONG ulIfIndex, ULONG ulFMaxPeriod, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetFMaxTime
*  Description: 设置接口的发送完整首部最大间隔时间
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulFMaxTime:发送完整首部最大间隔时间
*               ULONG ulReset:重置默认值标识：0 不重置，非0 重置
*       Output: 
*       Return: VOS_OK                                成功
*               PPP_IPHC_DISABLE                      IPHC功能不可用
*               PPP_WRONGPARA_ERROR                   参数不合法
*               PPP_IFNETCB_NOEXIST                   接口不存在
*               PPP_NOENCAP_ERROR                     接口类型不是PPP
*               PPP_PPPCB_NOEXIST                     PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST                接口配置信息不存在
*               PPP_HA_IS_SMOOTHING                   HA正在平滑处理或手动倒换处理
*               VOS_ERR                               其它错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetFMaxTime(ULONG ulIfIndex, ULONG ulFMaxTime, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_EnableIPHC
*  Description: 使能/去使能接口的IPHC功能
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulEnable:使能/去使能标记：0  去使能，非0  使能
*               ULONG ulCCompany:对端是否C公司：0  不是，非0 是
*       Output: 
*       Return: VOS_OK                            成功
*               PPP_HA_IS_SMOOTHING               HA正在平滑处理或手动倒换处理
*               PPP_NOTHISINTERF_ERROR            接口索引值为0
*               PPP_IFNETCB_NOEXIST               指定接口不存在
*               PPP_NOENCAP_ERROR                 指定接口非PPP链路类型
*               PPP_PPPCB_NOEXIST                 指定接口的PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST            指定接口的配置信息不存在
*               PPP_CONFIG_CONFLICT               配置冲突
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableIPHC(ULONG ulIfIndex, ULONG ulEnable, ULONG ulCCompany);
/*******************************************************************************
*    Func Name: TCPIP_SetMaxHeader
*  Description: 设置接口的最大可压缩首部长度
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulMaxHeader:最大可压缩首部长度
*               ULONG ulReset:重置默认值标识：0 不重置，非0 重置
*       Output: 
*       Return: VOS_OK                  成功
*               PPP_IPHC_DISABLE        IPHC功能不可用
*               PPP_WRONGPARA_ERROR     参数不合法
*               PPP_IFNETCB_NOEXIST     接口不存在
*               PPP_NOENCAP_ERROR       接口类型不是PPP
*               PPP_PPPCB_NOEXIST       PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST  接口配置信息不存在
*               PPP_HA_IS_SMOOTHING     HA正在平滑处理或手动倒换处理
*               VOS_ERR                 其它错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMaxHeader(ULONG ulIfIndex, ULONG ulMaxHeader, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetNegoSubOptions
*  Description: 设置接口是否协商子选项
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulSetYes:协商标识标识：0不协商，非0协商，其他非法
*       Output: 
*       Return: VOS_OK                           成功
*               PPP_IPHC_DISABLE                 IPHC功能不可用
*               PPP_IFNETCB_NOEXIST              接口不存在
*               PPP_NOENCAP_ERROR                接口类型不是PPP
*               PPP_PPPCB_NOEXIST                PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST           接口配置信息不存在
*               PPP_HA_IS_SMOOTHING              HA正在平滑处理或手动倒换处理
*               VOS_ERR                          其它错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetNegoSubOptions ( ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPNegTime
*  Description: 设置PPP协商超时的时间
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulSetYes:是否设置的标志：1为使用，0为取消，其他非法
*               ULONG ulTimeoutTime:协商超时时间
*       Output: 
*       Return: VOS_OK                      成功
*               VOS_ERR                     失败
*               PPP_HA_IS_SMOOTHING         HA正在平滑处理或手动倒换处理
*               PPP_CONFIGINFO_NOEXIST      用户输入的配置信息不存在
*               PPP_WRONGPARA_ERROR         参数不合法
*               PPP_NOTHISINTERF_ERROR      接口索引为空，不存在
*               PPP_IFNETCB_NOEXIST         接口不存在
*               PPP_NOENCAP_ERROR           接口类型不是PPP
*               PPP_PPPCB_NOEXIST           PPP控制块不存在
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPNegTime(ULONG ulIfIndex, ULONG ulSetYes, ULONG ulTimeoutTime);
/*******************************************************************************
*    Func Name: TCPIP_SetNonTcpSpace
*  Description: 设置接口的非TCP报文格式最大CID
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulNonTcpSpace:non-TCP格式最大CID值
*               ULONG ulReset:重置默认值标识：0 不重置，非0 重置
*       Output: 
*       Return: VOS_OK                       成功
*               PPP_IPHC_DISABLE             IPHC功能不可用
*               PPP_WRONGPARA_ERROR          参数不合法
*               PPP_IFNETCB_NOEXIST          接口不存在
*               PPP_NOENCAP_ERROR            接口类型不是PPP
*               PPP_PPPCB_NOEXIST            PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST       接口配置信息不存在
*               PPP_HA_IS_SMOOTHING          HA正在平滑处理或手动倒换处理
*               VOS_ERR                      其它错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetNonTcpSpace(ULONG ulIfIndex, ULONG ulNonTcpSpace, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetPapNameP**
*  Description: 设置PAP验证的用户名和pwd
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulSetYes:是否设置的标志：1为使用，0为取消，其他非法；如果设置取消则后面三个参数不用
*               ULONG usEncrypt:pwd是否enc ，1为设置enc ，0为取消
*               UCHAR *pcP***W***:pwd内容（有效长度非enc pwd1～16，或enc pwd24）
*               UCHAR *pcUsername:用户名（有效长度1～72）
*       Output: 
*       Return: VOS_OK                        成功
*               PPP_HA_IS_SMOOTHING           HA正在平滑处理或手动倒换处理
*               PPP_WRONGPARA_ERROR           参数不合法（是非值须为0或1）
*               PPP_NOTHISINTERF_ERROR        接口索引值为0
*               PPP_IFNETCB_NOEXIST           指定接口不存在
*               PPP_NOENCAP_ERROR             指定接口非PPP链路类型
*               PPP_PPPCB_NOEXIST             指定接口的PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST        指定接口的配置信息控制块不存在
*               PPP_PARA_NULLPOINTER          指针参数值为空
*               PPP_CIPHERP***W***_WRONG      enc pwd设置错误
*               PPP_HOSTNAME_INVALID          无效的用户名（长度为0或超过72）
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPapNamePwd(ULONG ulIfIndex,ULONG ulSetYes,  ULONG usEncrypt, UCHAR *pcPassword, UCHAR *pcUsername);
/*******************************************************************************
*    Func Name: TCPIP_EnablePFC
*  Description: 使能/去使能协商PFC
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulSetYes:设置开关： 1  使能， 0  去使能，其他非法
*       Output: 
*       Return: VOS_OK                           成功
*               PPP_HA_IS_SMOOTHING              HA正在平滑处理或手动倒换处理
*               PPP_NOTHISINTERF_ERROR           接口索引值为0
*               PPP_IFNETCB_NOEXIST              指定接口不存在
*               PPP_NOENCAP_ERROR                指定接口非PPP链路类型
*               PPP_PPPCB_NOEXIST                指定接口的PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST           指定接口的配置信息不存在
*               PPP_WRONGPARA_ERROR              参数不合法（开关变量须为0或1）
*               PPP_CONFIG_CONFLICT              PPP相关配置冲突（PPPoE链路不支持PFC）
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_EnablePFC ( ULONG ulIfIndex, ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_SetRtpCompression
*  Description: 设置接口是否协商RTP Compression子选项或者Enhanced RTP Compression 子选项
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulRtpCompression:是否协商(Enhanced)RTP Compression子选项
*               ULONG ulReset:重置默认值标识：0 不重置，非0 重置
*       Output: 
*       Return: VOS_OK                          成功
*               PPP_IPHC_DISABLE                IPHC功能不可用
*               PPP_WRONGPARA_ERROR             参数不合法
*               PPP_IFNETCB_NOEXIST             接口不存在
*               PPP_NOENCAP_ERROR               接口类型不是PPP
*               PPP_PPPCB_NOEXIST               PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST          接口配置信息不存在
*               PPP_HA_IS_SMOOTHING             HA正在平滑处理或手动倒换处理
*               VOS_ERR                         其它错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetRtpCompression(ULONG ulIfIndex, ULONG ulRtpCompression, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetTcpSpace
*  Description: 设置接口的TCP报文格式最大CID
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulTcpSpace:TCP格式最大CID值
*               ULONG ulReset:重置默认值标识：0 不重置，非0 重置
*       Output: 
*       Return: VOS_OK                      成功
*               PPP_IPHC_DISABLE            IPHC功能不可用
*               PPP_WRONGPARA_ERROR         参数不合法
*               PPP_IFNETCB_NOEXIST         接口不存在
*               PPP_NOENCAP_ERROR           接口类型不是PPP
*               PPP_PPPCB_NOEXIST           PPP控制块不存在
*               PPP_CONFIGINFO_NOEXIST      接口配置信息不存在
*               PPP_HA_IS_SMOOTHING         HA正在平滑处理或手动倒换处理
*               VOS_ERR                     其它错误
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetTcpSpace (ULONG ulIfIndex, ULONG ulTcpSpace, ULONG ulReset);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPDebugSwitch
*  Description: 设置全局debug开关
*        Input: ULONG ulPppDebugFlag:debug开关：0  关闭，1  打开，其他非法
*       Output: 
*       Return: VOS_OK                         成功
*               VOS_ERR                        失败
*               PPP_WRONGPARA_ERROR            参数不合法
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPDebugSwitch(ULONG ulPppDebugFlag);
/*******************************************************************************
*    Func Name: TCPIP_EnableVjComp
*  Description: 设置是否使能VJ压缩
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulSetYes:使能标志：0  关闭，1  使能，其他非法
*       Output: 
*       Return: VOS_OK                    成功
*               VOS_ERR                   失败
*               PPP_WRONGPARA_ERROR       参数不合法
*               PPP_HA_IS_SMOOTHING       HA正在平滑处理或手动倒换处理
*               PPP_NOTHISINTERF_ERROR    接口索引为空，不存在
*               PPP_IFNETCB_NOEXIST       接口不存在
*               PPP_NOENCAP_ERROR         接口类型非PPP类型
*               PPP_PPPCB_NOEXIST         PPP控制块不存在
*               PPP_CONFIG_CONFLICT       PPP相关配置冲突（该接口上已使能IPHC）
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_EnableVjComp(ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetDiscrSpecial
*  Description: 设置MP支持CBTS产品的非标自动侦听方式对接
*        Input: ULONG ulSetYes:设置开关：1-支持  0-不支持
*       Output: 
*       Return: VOS_OK                   成功
*               VOS_ERR                  失败  
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDiscrSpecial ( ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPResetTime
*  Description: 设置PPP复位定时器
*        Input: ULONG ulTime:设置的事件间隔
*       Output: 
*       Return: VOS_OK                  成功
*               VOS_ERR                 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPResetTime(ULONG ulTime);
/*******************************************************************************
*    Func Name: TCPIP_SetLQMNeg
*  Description: 设置是否使能LQM功能
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulSetYes:使能标志：0  去使能，1  使能，其他非法（默认为0）
*       Output: 
*       Return: VOS_OK                        成功
*               PPP_HA_IS_SMOOTHING           正在手动倒换或者平滑处理
*               PPP_WRONGPARA_ERROR           参数错误
*               PPP_IFNETCB_NOEXIST           接口不存在
*               PPP_PHYTYPE_ERR               接口类型错误
*               PPP_CONFIGINFO_NOEXIST        不存在PPP配置控制块
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLQMNeg( ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetLQMPeriod
*  Description: 设置LQM周期值
*        Input: ULONG ulIfIndex:接口索引
*               USHORT usLqrPeriod:设置的周期值(范围10～100，默认为50)
*       Output: 
*       Return: VOS_OK                  成功
*               PPP_HA_IS_SMOOTHING     正在手动倒换或者平滑处理
*               PPP_WRONGPARA_ERROR     参数错误
*               PPP_IFNETCB_NOEXIST     接口不存在
*               PPP_PHYTYPE_ERR         接口类型错误
*               PPP_CONFIGINFO_NOEXIST  不存在PPP配置控制块
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLQMPeriod( ULONG ulIfIndex, USHORT usLqrPeriod);
/*******************************************************************************
*    Func Name: TCPIP_SetLQMLimit
*  Description: 设置LQM关闭、恢复阀值
*        Input: ULONGulIfIndex:接口索引
*               ULONG ulCloseValue:关闭阀值(范围0～100，默认为80)
*               ULONG ulResumeValue:恢复阀值(范围0～100，默认为80)
*       Output: 
*       Return: VOS_OK                   成功
*               PPP_HA_IS_SMOOTHING      正在手动倒换或平滑处理
*               PPP_WRONGPARA_ERROR      参数错误
*               PPP_IFNETCB_NOEXIST      接口不存在
*               PPP_PHYTYPE_ERR          接口类型错误
*               PPP_CONFIGINFO_NOEXIST   不存在PPP配置控制块
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLQMLimit(ULONG ulIfIndex,ULONG ulCloseValue,ULONG ulResumeValue);
/*******************************************************************************
*    Func Name: TCPIP_SetIpcpNegoDns
*  Description: 使能/去使能在IPCP阶段是否协商DNS选项
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulSetYes:使能标志，1 使能，0 去使能
*       Output: 
*       Return: VOS_OK                   成功
*               PPP_WRONGPARA_ERROR      参数错误
*               PPP_HA_IS_SMOOTHING      HA正在平滑处理或手动倒换处理
*               PPP_GETCONFIGINFO_FAIL   获取PPP配置信息失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIpcpNegoDns (ULONG ulIfIndex, ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_SetIPCPDNSAddr
*  Description: 设置/删除IPCP协商的DNS服务器地址，提供给对端
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulSetYes:设置标志，1配置，0 删除
*               ULONG ulNum_Pri:主DNS服务器地址
*               ULONG ulNum_Sec:从DNS服务器地址
*       Output: 
*       Return: VOS_OK                      成功
*               PPP_CONFIG_IFCONFLICT       接口失败
*               PPP_WRONGPARA_ERROR         输入的参数错误
*               PPP_HA_IS_SMOOTHING         HA正在平滑处理或手动倒换处理
*               PPP_DNSIPADDRESS_INVALID    配置的主从DNS服务器地址无效
*               PPP_DNSIPADDRESS_PRI_IS_INVALID 配置的主DNS服务器地址无效
*               PPP_DNSIPADDRESS_SEC_IS_INVALID 配置的从DNS服务器地址无效
*               Other                       获取PPP信息块的错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIPCPDNSAddr(ULONG ulIfIndex, ULONG ulSetYes, ULONG ulNum_Pri, ULONG ulNum_Sec);
/*******************************************************************************
*    Func Name: TCPIP_SetPppHADbg
*  Description: 设置PPP模块HA功能调试开关状态
*        Input: ULONG ulDbg:设置PPP的HA调试开关值
*       Output: 
*       Return: VOS_OK                         成功
*               VOS_ERR                        失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPppHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetPppHADbg
*  Description: 获取PPP模块HA功能调试开关状态
*        Input: ULONG *pulDbg:调试信息输出开关指针
*       Output: ULONG *pulDbg:调试信息输出开关指针
*       Return: VOS_OK                     成功
*               VOS_ERR                    失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPppHADbg (ULONG *pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_SetMpEDConsistent
*  Description: 设置MP终端描述符一致性检测开关
*        Input: ULONG ulSetYes:设置MP终端描述符一致性检测开关
*       Output: 
*       Return: VOS_OK                   成功
*               VOS_ERR                  失败
*               PPP_HA_IS_SMOOTHING      正在平滑或者手动倒换处理
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMpEDConsistent (ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_GetMpEDConsistent
*  Description: 获取MP终端描述符一致性检测开关
*        Input: VOID
*       Output: 
*       Return: MP终端描述符一致性检测开关
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetMpEDConsistent(VOID);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncNotifyIpcpDownHook
*  Description: 通知IPCP down
*        Input: NotifyIpcpDown_HOOK_FUNC pfHookFunc:函数钩子
*       Output: 
*       Return: VOS_OK                 成功
*               VOS_ERR                失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncNotifyIpcpDownHook(NotifyIpcpDown_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncShellAuthRequestHook
*  Description: 向验证模块发送验证请求
*        Input: PPPShellAuthRequest pfHookFunc:函数钩子
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-10   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncShellAuthRequestHook(PPPShellAuthRequest pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncShellChapGetUserPswHook
*  Description: CHAP验证时根据用户名获取用户的pwd
*        Input: PPPShellChapGetUserPsw pfHookFunc:函数钩子
*       Output: 
*       Return: VOS_OK                成功
*               VOS_ERR               失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncShellChapGetUserPswHook(PPPShellChapGetUserPsw pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncAllocPPPHook
*  Description: 获取分配给对端的地址
*        Input: PPPAllocPeerIpAddr pfHookFunc:函数钩子
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncAllocPPPHook(PPPAllocPeerIpAddr pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncFreeAddrHook
*  Description: 释放分配给对端的地址
*        Input: PPPFreeAddr pfHookFunc:函数钩子
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncFreeAddrHook(PPPFreeAddr pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetLQRStatHook
*  Description: 获取LQR所需的统计信息,测试时需要注销Adapter里面相同的文件
*        Input: GetLQRStat_HOOK_FUNC pfHookFunc:函数钩子
*       Output: 
*       Return: VOS_OK                     成功
*               VOS_ERR                    失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetLQRStatHook(GetLQRStat_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncNotifyPppDnsHook
*  Description: PPP协商时获取DNS的地址
*        Input: NotifyPppDns_HOOK_FUNC pfHookFunc:函数钩子
*       Output: 
*       Return: VOS_OK           成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncNotifyPppDnsHook(NotifyPppDns_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_ADP_NotifyPppDns
*  Description: PPP协商时获取DNS的地址
*        Input: ULONG ulIfIndex:接口索引值
*               ULONG ulSetYes:1表示删除, 0表示增加
*               ULONG ulPriDns:主DNS服务器地址(主机字节序)
*               ULONG ulSecDns:次DNS服务器地址(主机字节序)
*       Output: 
*       Return: VOS_OK:处理成功
*              其它  :处理失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-28   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_ADP_NotifyPppDns(ULONG ulIfIndex, ULONG ulSetYes,ULONG ulPriDns, ULONG ulSecDns);
/*******************************************************************************
*    Func Name: TCPIP_ShowPppGlobalInfo
*  Description: PPP模块产品定制需求使能开关及部分全局信息显示接口
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPppGlobalInfo (VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowPppStatistic
*  Description: PPP模块统计类信息显示接口
*        Input: CHAR *pName:接口名称
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPppStatistic(CHAR *pName);
/*******************************************************************************
*    Func Name: TCPIP_ShowPPPCfgInfo
*  Description: 显示PPP扩展一些配置信息
*        Input: CHAR *pszIfName:接口名称
*               ULONG ulProtocol:扩展协议号
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPPPCfgInfo(CHAR *pszIfName,ULONG ulProtocol);
/*******************************************************************************
*    Func Name: TCPIP_ResetIPCP
*  Description: 重启IPCP协议
*        Input: ULONG ulIfIndex:            接口索引
*       Output: 
*       Return: VOS_OK                      成功
*               PPP_HA_IS_SMOOTHING         正在手动倒换或平滑处理
*               PPP_IFNETCB_NOEXIST         接口指针为空
*               PPP_PPPCB_NOEXIST           PPP控制块不存在
*               PPP_NOENCAP_ERROR           非PPP协议
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_ResetIPCP (ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ResetIP6CP
* Date Created: 2009-03-20
*       Author: hanna55555
*  Description: 重启IP6CP协议
*        Input: ULONG ulIfIndex:            接口索引
*       Output: 
*       Return: VOS_OK                      成功
*               PPP_HA_IS_SMOOTHING         正在手动倒换或平滑处理
*               PPP_IFNETCB_NOEXIST         接口指针为空
*               PPP_ERR_PORT_IS_VIRTUAL   非本板接口 
*               PPP_PPPCB_NOEXIST           PPP控制块不存在
*               PPP_IP6CPCB_NOEXIST          IP6CP控制块不存在
*               PPP_NOENCAP_ERROR           非PPP协议
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-20   hanna55555         Create in VISPV1R8C01 for ppp-link support ipv6
*
*******************************************************************************/
extern ULONG TCPIP_ResetIP6CP (ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_ResetOSICP
*  Description: 重启OSICP协议
*        Input: ULONG ulIfIndex:            接口索引
*       Output: 
*       Return: VOS_OK                      成功
*               PPP_HA_IS_SMOOTHING         正在手动倒换或平滑处理
*               PPP_IFNETCB_NOEXIST         接口指针为空
*               PPP_PPPCB_NOEXIST           PPP控制块不存在
*               PPP_NOENCAP_ERROR           非PPP协议
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-17   chenfutian69112         Create
*
*******************************************************************************/
extern ULONG TCPIP_ResetOSICP (ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetPPPNegoIP
*  Description: 注册PPP协商协商上报钩子处理函数
*        Input: GET_PPP_NEGO_IP_HOOK_FUN pfGetPPPNegoIP
*               
*       Output: 
*       Return: VOS_ERR
                VOS_OK
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/
    
extern ULONG TCPIP_RegFuncGetPPPNegoIP (GET_PPP_NEGO_IP_HOOK_FUN pfGetPPPNegoIP);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPNegoIP
*  Description: 配置下发PPP协商获取信息接口
*        Input: ULONG ulIfIndex:    接口索引
                ULONG ulLocalIP:    本地地址(主机序)
*               ULONG aulDNSIP[]:   DNS地址(主机序)
                ULONG ulRemoteIP:   对端地址(主机序)
                ULONG ulMTU:        MTU
                ULONG ulFlag:       添加删除标志:0添加,1删除
*       Output: 
*       Return: PPP_HA_IS_SMOOTHING:系统处于平滑或手动倒换阶段
                PPP_NOT_3D_MODE:    非三维模式
                PPP_COM_NULL:       组件为空
                PPP_WRONGPARA_ERROR:参数错误
                VRP_IFNET_ENOSUCHIF:接口指针为空
                VOS_OK:             处理成功
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/

extern ULONG TCPIP_SetPPPNegoIP(ULONG ulIfIndex,ULONG ulLocalIP, ULONG aulDNSIP[DHCP4C_DNSIP_NUM],
                                ULONG ulRemoteIP,ULONG ulMTU, ULONG ulFlag);
/*******************************************************************************
*    Func Name: TCPIP_SetIPHCUniDirection
*  Description: 使能/去使能接口的IPHC单通处理功能
*        Input: ULONG ulIfIndex:接口索引
*               ULONG ulEnable:使能标记,0去使能,其他使能
*       Output: 无
*       Return: VOS_OK成功,其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIPHCUniDirection(ULONG ulIfIndex, ULONG ulEnable);

/*******************************************************************************
*    Func Name: TCPIP_ReceiveAuthResult
*  Description: 用户在进行验证校对后将通过此接口来将验证结果返回给VISP
*        Input: PPPAUTHRESULT_S *pstAuthResult:返回的验证情况
*       Output: 无
*       Return: 成功VOS_OK,其他返回失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-07-01   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_ReceiveAuthResult(PPPAUTHRESULT_S *pstAuthResult);
/*******************************************************************************
*    Func Name: TCPIP_SetPPPVerifySwitch
*  Description: 使能/去使能PPP/MP数据核查功能(核查VISP下发NP的相关信息)
*        Input: ULONG ulSwitch:开关(1:使能；0:去使能)
*               ULONG ulPeriod:核查周期（取值范围: [1，0xffffffff），单位s）
*               ULONG ulIfNum: 每次核查的接口数（取值范围：[1，128]）
*       Output: 
*       Return: VOS_OK：使能/去使能成功
*               VOS_ERR：使能/去使能失败
*               PPP_WRONGPARA_ERROR:参数不合法
*               PPP_HA_IS_SMOOTHING:HA正在平滑处理或手动倒换处理
*               PPP_FUNCHOOK_NULL:函数钩子为空
*               PPP_COM_NULL:组件虚表为空
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-20   fuxiaodong(54882)       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPPPVerifySwitch(ULONG ulSwitch, ULONG ulPeriod, ULONG ulIfNum);
/*******************************************************************************
*    Func Name: TCPIP_GetPPPVerifySwitch
*  Description: 获取PPP NP下发信息核查开关状态
*        Input: 
*       Output: PPPVERIFYSWITCH_S *pstPppVerifySwitch:返回开关状态
*       Return: VOS_OK：获取成功
*               其他：获取失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-20   fuxiaodong(54882)       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPPPVerifySwitch(PPPVERIFYSWITCH_S *pstPppVerifySwitch);
/*******************************************************************************
*    Func Name: TCPIP_ClearIfIPHCStat
*  Description: 清除指定接口的IPHC上下文统计信息
*        Input: ULONG ulIfIndex: 接口索引
*       Output: 
*       Return：VOS_OK          成功
*               其它            失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-9-19  zhangchunyu(62474)   Create
*
*******************************************************************************/
extern ULONG TCPIP_ClearIfIPHCStat(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetIfIPHCStatistics
* Date Created: 2009-02-25
*       Author: ZhengSenHuo/Zhongweihua(104483/104207)
*  Description: 获取IPHC的统计信息
*        Input: ULONG ulIfIndex: 接口索引
*       Output: TCPIP_IPHC_STATISTICS_S *pstIPHCStatistics: IPHC统计信息结构
*       Return: 成功IPHC_OK，失败返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-25   ZhengSenHuo/Zhongweihua(104483/104207)  Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIfIPHCStatistics(ULONG ulIfIndex,TCPIP_IPHC_STATISTICS_S *pstIPHCStatistics);

/*******************************************************************************
*    Func Name: TCPIP_PPP_Set_NegTimeoutWaring
* Date Created: 2009-02-26
*       Author: zengshaoyang62531/hexianjun00121208
*  Description: 设置/取消首次协商不过对外告警功能
*        Input: ULONG ulTime:为0时表示取消协商不过对外告警功能
*                            非0表示设置协商不过对外告警功能，
*                            ulTime数值表示用户指定的协商时间
*       Output: 
*       Return: 成功:VOS_OK;失败:返回错误码
*      Caution: ulTime必须为5的倍数,否则返回错误,最大为600s
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                     DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-26   zengshaoyang62531/hexianjun00121208       Create
*
*******************************************************************************/
extern ULONG TCPIP_PPP_Set_NegTimeoutWaring(ULONG ulTime);
/*******************************************************************************
*    Func Name: TCPIP_PPP_Get_NegTime
* Date Created: 2009-02-26
*       Author: zengshaoyang62531/hexianjun00121208
*  Description: 获取用户设置的首次协商不过对外告警时间
*        Input: ULONG ulTime: 首次协商不过对外告警时间
*       Output: 
*       Return: 成功:VOS_OK;失败:返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-26   zengshaoyang62531/hexianjun00121208       Create
*
*******************************************************************************/
extern ULONG TCPIP_PPP_Get_NegTime(ULONG *pulTime);

/*******************************************************************************
*    Func Name: TCPIP_SetNegoMagicNum
* Date Created: 2009-07-14
*       Author: z00104207
*  Description: 设置接口是否协商Magic Number
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulSetYes:  协商Magic Number标记，1-协商，0-不协商
*       Output: 
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 只能对PPP/VT/Dialer接口调用该API接口。要使得配置操作生效，需要重启接口。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-14   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetNegoMagicNum(ULONG ulIfIndex, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_GetNegoMagicNum
* Date Created: 2009-07-14
*       Author: z00104207
*  Description: 获取接口是否协商Magic Number的标记
*        Input: ULONG ulIfIndex:  接口索引
*       Output: ULONG *pulSetYes: 获取到的标记值，1-协商，0-不协商
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 只能对PPP/VT/Dialer接口调用该API接口。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-14   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetNegoMagicNum(ULONG ulIfIndex, ULONG *pulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_SetPppSelfLoop
* Date Created: 2009-07-17
*       Author: z00104207
*  Description: 设置接口自环模式标记
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulSetYes:  设置是否自环模式，1-是，0-否
*       Output: 
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 设置自环模式，是指本接口与本接口自身建立连接，进行PPP协商。
*               自环模式下，将不协商Magic Number，不检查对端地址的合法性。对于
*               MP组接口，除了要对MP组设置自环模式外，还需对每条子链路设置自环模
*               式，MP组的自环才能生效。只能对PPP接口和MP组接口调用该API接口。要
*               使得配置操作生效，需要重启接口。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-17   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPppSelfLoop(ULONG ulIfIndex, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_GetPppSelfLoop
* Date Created: 2009-07-17
*       Author: z00104207
*  Description: 获取接口自环模式标记
*        Input: ULONG ulIfIndex:  接口索引
*       Output: ULONG *pulSetYes: 获取到的标记值
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 只能对PPP接口和MP组接口调用该API接口。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-17   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPppSelfLoop(ULONG ulIfIndex, ULONG *pulSetYes);

/*******************************************************************************
*    Func Name: TCPIP_SetNcpResendTime
* Date Created: 2009-09-04
*       Author: z00104207
*  Description: 设置LCP报OPEN时，各个NCP协议发送一个协商请求报文后，再分别对各个
*               NCP协议延时补发一个NCP协商请求报文的时间
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulTime:    延时补发的时间，范围是0~6000毫秒，其中取0时表示
*                                不补发NCP协商请求报文
*       Output: 
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 接口的链路封装类型必须为PPP，即支持PPP/MP/Dialer接口，默认情况下
*               是不会对各个NCP协议再补发一个NCP协商请求报文的。NCP协商请求报文
*               包括IPCP协商请求报文、OSICP协商请求报文和MUXCP协商请求报文
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-04   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetNcpResendTime(ULONG ulIfIndex, ULONG ulTime);

/*******************************************************************************
*    Func Name: TCPIP_GetNcpResendTime
* Date Created: 2009-09-04
*       Author: z00104207
*  Description: 获取LCP报OPEN时，各个NCP协议发送一个NCP协商请求报文后，再分别对各个
*               NCP协议延时补发一个NCP协商请求报文的时间
*        Input: ULONG ulIfIndex: ULONG ulIfIndex: 接口索引
*       Output: ULONG *pulTime:  获取到的延时补发的时间，范围是0~6000毫秒，其中
*                                取0时表示不补发NCP协商请求报文
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 接口的链路封装类型必须为PPP，即支持PPP/MP/Dialer接口，默认情况下
*               是不会对各个NCP协议再补发一个NCP协商请求报文的，因此默认情况下获
*               取到的值为0
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-04   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetNcpResendTime(ULONG ulIfIndex, ULONG *pulTime);

/*******************************************************************************
*    Func Name: TCPIP_ShowConfigInfo
* Date Created: 2009-10-10
*       Author: zhangchi(00142640)
*  Description: 显示PPP Config信息 
*        Input: CHAR *szName:接口名
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-10   zhangchi(00142640)      Create
*
*******************************************************************************/
extern VOID TCPIP_ShowConfigInfo(CHAR *szName);

/*******************************************************************************
*    Func Name: TCPIP_ShowUsedConfigInfo
* Date Created: 2009-10-10
*       Author: zhangchi(00142640)
*  Description: 显示PPP UsedConfig信息 
*        Input: CHAR *szName:接口名
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-10   zhangchi(00142640)      Create
*
*******************************************************************************/
extern VOID TCPIP_ShowUsedConfigInfo(CHAR *szName);

/*******************************************************************************
*    Func Name: TCPIP_GetLcpEchoInfo
* Date Created: 2008-11-9
*       Author: zhangchunyu(62474)
*  Description: NP逻辑获取VISP内部PPP Lcp Echo相关信息
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulCmd: 命令字
*               VOID  *pData: 命令字下相应的数据结构,输出参数
*       Output: pData
*       Return: VOS_OK 成功  其他 失败
*      Caution: 只有底层想处理Echo报文的时候,才可以调用获取PPP Lcp保活信息。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-11-9    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetLcpEchoInfo(ULONG ulIfIndex, ULONG ulCmd, VOID  *pData);


/*******************************************************************************
*    Func Name: TCPIP_SetDealAcfcPfcFlag
* Date Created: 2009-06-23
*       Author: z00104207
*  Description: 针对接口设置是否接受和处理ACFC、PFC协商选项
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG ulFlag:    是否接受和处理标记，是则填写为1，否则填写为0
*       Output: 
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 操作的接口只能是PPP接口
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_SetDealAcfcPfcFlag(ULONG ulIfIndex, ULONG ulFlag);

/*******************************************************************************
*    Func Name: TCPIP_GetDealAcfcPfcFlag
* Date Created: 2009-06-23
*       Author: z00104207
*  Description: 获取接口上"是否接受和处理ACFC、PFC协商选项"标记的值
*        Input: ULONG ulIfIndex: 接口索引
*               ULONG *pulFlag:  标记值输出参数
*       Output: 
*       Return: 
*      Caution: 成功则返回VOS_OK，失败则返回其他错误码
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-23   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDealAcfcPfcFlag(ULONG ulIfIndex, ULONG *pulFlag);


/*******************************************************************************
*    Func Name: TCPIP_GR_PPPRestore
* Date Created: 2008-8-16
*       Author: zhangchunyu(62474)
*  Description: PPP保活恢复接口, 用户接口
*        Input: VOID
*       Output: 
*       Return: GR_SUCCESS: 成功, 其他: 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-8-16    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GR_PPPRestore(VOID);

/*******************************************************************************
*    Func Name: TCPIP_GR_PPPSmooth
* Date Created: 2008-8-16
*       Author: zhangchunyu(62474)
*  Description: PPP模块保活平滑操作, 用户接口
*        Input: VOID
*       Output: 
*       Return: GR_SUCCESS: 成功, 其他: 失败
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-8-16    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GR_PPPSmooth(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SetMaxLoopbackDetectTime
* Date Created: 2009-11-28
*       Author: zhangchi(00142640)
*  Description: 设置PPP自环检测次数 
*        Input: ULONG ulTime:检测次数
*       Output: 
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-28   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMaxLoopbackDetectTime(ULONG ulTime);

/*******************************************************************************
*    Func Name: TCPIP_GetMaxLoopbackDetectTime
* Date Created: 2009-11-28
*       Author: zhangchi(00142640)
*  Description: 获取PPP自环检测次数 
*        Input: ULONG *pulTime:检测次数 
*       Output: 
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-28   zhangchi(00142640)      Create
*
*******************************************************************************/
extern ULONG TCPIP_GetMaxLoopbackDetectTime(ULONG *pulTime);

/*******************************************************************************
*    Func Name: TCPIP_ShowPPPNegoInfoByIf
* Date Created: 2009-11-13
*       Author: zhangchi(00142640)
*  Description: 根据接口名显示协商信息
*        Input: CHAR *szName:接口名
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-13   zhangchi(00142640)      Create
*
*******************************************************************************/
extern VOID TCPIP_ShowPPPNegoInfoByIf(CHAR *szName);

/*******************************************************************************
*    Func Name: TCPIP_GetPPPFSMState
* Date Created: 2009-12-15
*       Author: Gexianjun/h00121208
*  Description: 获取PPP状态机状态
*        Input: ULONG ulIfIndex: 接口索引
*       Output: ULONG *pulPppPhase:PPP所处的阶段,取值：参见enum ePppPhase
*               ULONG *pulPppNegoType:PPP协商类型,取值：参见enum ePppNegoType
*               ULONG *pulPppFsmState:PPP协商状态值,取值：参见enum ePppFsmState
*       Return: 成功则返回VOS_OK，失败则返回其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-15   Gexianjun/h00121208     Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPPPFSMState(ULONG ulIfIndex, ULONG *pulPppPhase,ULONG *pulPppNegoType, ULONG *pulPppFsmState );

/*******************************************************************************
*    Func Name: TCPIP_GetPapUserName
* Date Created: 2010-01-19
*       Author: z00104207
*  Description: 获取PAP认证时的用户名。
*        Input: ULONG ulIfIndex:    接口索引
*       Output: UCHAR *pucUserName: 用户名，用户应保证传入内存的长度最少为
*                                   (PPP_MAXUSERNAMELEN + 1)字节
*       Return: 成功则返回VOS_OK，否则返回错误码。
*      Caution: 获取用户名时，不限制认证方式必须为PAP认证。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-19   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPapUserName(ULONG ulIfIndex, UCHAR *pucUserName);

/*******************************************************************************
*    Func Name: TCPIP_GetChapUserName
* Date Created: 2010-01-19
*       Author: z00104207
*  Description: 获取CHAP认证时的用户名。
*        Input: ULONG ulIfIndex:    接口索引
*       Output: UCHAR *pucUserName: 用户名，用户应保证传入内存的长度最少为
*                                   (PPP_MAXUSERNAMELEN + 1)字节
*       Return: 成功则返回VOS_OK，否则返回错误码。
*      Caution: 获取用户名时，不限制认证方式必须为CHAP认证。
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-01-19   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetChapUserName(ULONG ulIfIndex, UCHAR *pucUserName);

/*******************************************************************************
*    Func Name: TCPIP_GetPppDownInfo
* Date Created: 2010-03-10
*       Author: z00104207
*  Description: 获取PPP协商Down相关的信息
*        Input: ULONG ulIfIndex:               接口索引
*               ULONG ulProtocolType:          PPP子协议
*       Output: PPPDOWNINFO_S *pstPppDownInfo: PPP协商Down相关的信息
*       Return: 成功则返回VOS_OK，否则返回其他错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-10   z00104207               Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPppDownInfo(ULONG ulIfIndex, ULONG ulProtocolType, PPPDOWNINFO_S *pstPppDownInfo);


/*******************************************************************************
* Func Name: TCPIP_SyncPPPKeepaliveProbe 
* Date Created: 25-04-2013
*       Author: s72256	
*  Description: Function to sync PPP keep aliave probe while switchig from one board to another.
*        Input: ULONG ulIfIndex:   Interface Index
*               ULONG ulProbeSup:          Flag to indicate that NP supports ppp keep alive.
*       Output: 
*       Return: VOS_OK in case of success
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  25-04-2013   s72256               Create
*
*******************************************************************************/
extern ULONG TCPIP_SyncPPPKeepaliveProbe (ULONG ulIfIndex, ULONG ulProbeSup);


#ifdef __cplusplus
}
#endif


#endif

