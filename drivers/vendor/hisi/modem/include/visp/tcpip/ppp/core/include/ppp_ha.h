/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ppp_ha.h
*
*  Project Code: VISPV100R006
*   Module Name: HA
*  Date Created: 2006-12-15
*        Author: xiehuaguo
*   Description: PPP备份处理头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-12-15  xiehuaguo        Create
*  2007-06-28  f54882           增加PPP模块全局变量备份(同步问题单A82D11804)
*  2008-08-25  f54882           Modify for BC3D00263
*******************************************************************************/

#ifndef _PPP_HA_H_
#define _PPP_HA_H_

#ifdef  __cplusplus
extern "C"{
#endif

#define  PPP_BAK_PRFIX_GOTOPT       0X00000001
#define  PPP_BAK_PRFIX_HISOPT       0X00000002
#define  PPP_BAK_PRFIX_WANTOPT      0X00000004
#define  PPP_BAK_PRFIX_ALLOWOPT     0X00000008

#define  PPP_BAK_PRFIX_CONFIG       0X00000001
#define  PPP_BAK_PRFIX_USEDCONFIG   0X00000002

#define  PPP_BAK_NO_SMOOTH                      0X00000001

/* PPP 控制块备份信息结构 */
typedef struct tagPppInfoBak
{
    ULONG   bIsAsync:1,         /* 是否是异步口, 在LCP中判断是否协商ACCMAP */
            bSynAsyConvert:1,   /* 对于异步口，用于确定是否由PPP进行同/异步报文转换 */
            bLoopBacked:1,      /* 接口是否发生了自环 */ 
            bLowerIsUp:1,       /* 底层是否UP */ 
            bMpChannelType:2 ,  /* MP通道类型 */
            bPppInterleave:1,   /* 是否配置LFI */
            bRunningPoeClient:1, /* 表明该PPP Info结构是否用于PPPoE Client*/ 
            bLqmStatus:1,
            bReserved: 23  ;     /* */
    ULONG   ulRemoteAccm ;       /* 对端ACCM控制字*/
    ULONG   ulMpgroupIfIndex ;   /* 如果是子通道存保存父通道的索引*/
    ULONG   ulLocalAccm ;        /* 本端ACCM控制字*/
    ULONG   ulRouteIfIndex ;     /* 路由可见接口的IFNET索引*/
    ULONG   ulPhase ;            /* PPP当前所处协商阶段*/
    USHORT  usMtu;               /* MTU值*/
    UCHAR   ucAuthServer ;       /* 本端作为认证端**/
    UCHAR   ucAuthClient ;       /* 本端作为被认证端*/
} PPPINFO_BAK_S ;


typedef struct tagMCPrefixEBak
{ 
    UCHAR aucPrefixE[MC_PREFIXE_MAX_STR];   /* 具体前缀省略字段，最大长度为8字节*/
    UCHAR ucIsUsedFlag;                     /* 是否配置该等级前缀省略标志 */
    UCHAR ucClass;                          /* 具体Class等级 */
    UCHAR ucPrefixELen;                     /* 前缀字段长度 */      
    UCHAR ucReserve;                        /* 保留 */
} MC_PREFIXE_BAK_S;

/* 基础数据区,不能修改其任何成员 */
typedef struct tagPppConfigInfoForBak 
{
    ULONG bCallbackReq    : 1,
          bCallbackAcc    : 1,
          bCallInAuth     : 1,
          bAuthRmtChap    : 1,
          bAuthRmtPap     : 1,
          bEnableVJComp   : 1,
          bEnablePComp    : 1,
          bEnableACComp   : 1,
          bSetAsMp        : 1,
          bPapPwdEncrypt  : 1,
          bChapPwdEncrypt : 1,
          bAuthRmtList    : 1,

          bAcceptPeerDNS0      :1,
          bRejectPeerDNS0      :1,
          bAcceptPeerDNS1      :1,
          bRejectPeerDNS1      :1,
  
          bEnableIPHComp  : 1,
          bNegoSubOptions : 1,  /* 是否协商RFC3544规定的子选项*/ 
          bStacCompress   : 1,   
          
          bPppInterleave  : 1,  /* 是否使能MP的分片交叉功能 */

          bPppReorderWindow  : 1, 
          bMpDiscriminator:1,   /* discriminator negotiation */
          bNegoLCPEnable:  1,   
          bNegoNCPEnable:  1,
          bMc         :1,
          bMcPrefixE  :1,
          bSsnhf      :1,
          bPPPMux     :1,  /* 是否协商PPP MUX */
          bNegoDNSEnable   :1, /* 用于POEC协商DNS */
          bLqmNegEnable    :1, /* 是否协商LQM */
          bNegoOSICPEnable :1, /* 是否协商OSI */
          bReserved   :1;  /* 保留,以后使用 */
    ULONG ulNegTimeOut;

    USHORT usMaxMpBindNum;/*最大绑定链路数*/
    USHORT usMinFragLen; /*MP开始分段的最小包长*/
    ULONG  ulBindType;
    ULONG  ulBindVTNum;
    ULONG  ulEndpointDiscriminator; /*MP终端描述符值*/
    
    USHORT usMaxDelayLFI; 
    USHORT usLqmPeriod;   /* LQM 发送周期值 */
    USHORT usUpSublinkLowLimit; /* mp接口成员端口UP数达到该值时才进行网络层协商 */
    UCHAR  ucPadding[2];
    
    ULONG  ulClosePercentage;   /* 设定的关闭链路的门限 */
    ULONG  ulResumePercentage;  /* 设定的重新启用链路的门限 */
    ULONG  ulPrimDNSIPAddr;     /* 设定的Primary DNS Server地址 */
    ULONG  ulSndDNSIPAddr;      /* 设定的Secondary DNS Server地址 */

    UCHAR cChapHostName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cChapPassword[PPP_MAXUSERPWDLEN + 1];
    UCHAR cPapUserName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cPapPwd[PPP_MAXUSERPWDLEN + 1];


    USHORT  iphc_tcp_space;
    USHORT  iphc_non_tcp_space;
    USHORT usFMaxPeriod;    /* 连续发送非TCP压缩报文最大个数 */
    USHORT usFMaxTime;      /* 发送完整首部报文最大间隔时间 */
    USHORT usMaxHeader;     /* 可压缩首部最大长度 */
    UCHAR  ucRtpCompression;/* 协商(Enhanced) RTP Compression子选项设置 */
    UCHAR  ucCompressType;  /* 报文压缩类型 */
    LONG   lCCOMPANY_FORMAT;
    LONG   lDELETE_UDP_CHKSUM;

    USHORT usDefaultPid;     /* Default PID */
    USHORT usSubFrameLen;    /* 最大子帧长度 */
    USHORT usFrameLen;       /* 最大复合帧长度 */
    USHORT usSubFrameCount;  /* 最大子帧数 */
    USHORT usMuxDelay;       /* 最大报文复合时延 */
    
    UCHAR  ucMhfCode;        /* MHF选项的code值 2:长序列头格式；6:短序列头格式 */ 
    UCHAR  ucMhfClass;       /* MHF选项的class值:对应头格式所支持的等级数 */
    ULONG  ulMcPrefixESum;   /* 存在的前缀省略映射对数目 */
}PPPCONFIGINFO_FOR_BAK_S;
/* 基础数据区,不能修改其任何成员 */

typedef struct tagPppConfigInfoForBakOld
{
    ULONG bCallbackReq    : 1,
          bCallbackAcc    : 1,
          bCallInAuth     : 1,
          bAuthRmtChap    : 1,
          bAuthRmtPap     : 1,
          bEnableVJComp   : 1,
          bEnablePComp    : 1,
          bEnableACComp   : 1,
          bSetAsMp        : 1,
          bPapPwdEncrypt  : 1,
          bChapPwdEncrypt : 1,
          bAuthRmtList    : 1,

          bAcceptPeerDNS0      :1,
          bRejectPeerDNS0      :1,
          bAcceptPeerDNS1      :1,
          bRejectPeerDNS1      :1,
  
          bEnableIPHComp  : 1,
          bNegoSubOptions : 1,  /* 是否协商RFC3544规定的子选项*/ 
          bStacCompress   : 1,   
          
          bPppInterleave  : 1,  /* 是否使能MP的分片交叉功能 */

          bPppReorderWindow  : 1, 
          bMpDiscriminator:1,   /* discriminator negotiation */
          bNegoLCPEnable:  1,   
          bNegoNCPEnable:  1,
          bMc         :1,
          bMcPrefixE  :1,
          bSsnhf      :1,
          bPPPMux     :1,  /* 是否协商PPP MUX */
          bNegoDNSEnable   :1, /* 用于POEC协商DNS */
          bLqmNegEnable    :1, /* 是否协商LQM */
          bNegoOSICPEnable :1, /* 是否协商OSI */
          bReserved   :1;  /* 保留,以后使用 */
    ULONG ulNegTimeOut;

    USHORT usMaxMpBindNum;/*最大绑定链路数*/
    USHORT usMinFragLen; /*MP开始分段的最小包长*/
    ULONG  ulBindType;
    ULONG  ulBindVTNum;
    ULONG  ulEndpointDiscriminator; /*MP终端描述符值*/
    
    USHORT usMaxDelayLFI; 
    USHORT usLqmPeriod;   /* LQM 发送周期值 */
    USHORT usUpSublinkLowLimit; /* mp接口成员端口UP数达到该值时才进行网络层协商 */
    UCHAR  ucPadding[2];
    
    ULONG  ulClosePercentage;   /* 设定的关闭链路的门限 */
    ULONG  ulResumePercentage;  /* 设定的重新启用链路的门限 */
    ULONG  ulPrimDNSIPAddr;     /* 设定的Primary DNS Server地址 */
    ULONG  ulSndDNSIPAddr;      /* 设定的Secondary DNS Server地址 */

    UCHAR cChapHostName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cChapPassword[PPP_MAXUSERPWDLENOLD+ 1];
    UCHAR cPapUserName[PPP_MAXUSERNAMELEN + 1];
    UCHAR cPapPwd[PPP_MAXUSERPWDLENOLD + 1];


    USHORT  iphc_tcp_space;
    USHORT  iphc_non_tcp_space;
    USHORT usFMaxPeriod;    /* 连续发送非TCP压缩报文最大个数 */
    USHORT usFMaxTime;      /* 发送完整首部报文最大间隔时间 */
    USHORT usMaxHeader;     /* 可压缩首部最大长度 */
    UCHAR  ucRtpCompression;/* 协商(Enhanced) RTP Compression子选项设置 */
    UCHAR  ucCompressType;  /* 报文压缩类型 */
    LONG   lCCOMPANY_FORMAT;
    LONG   lDELETE_UDP_CHKSUM;

    USHORT usDefaultPid;     /* Default PID */
    USHORT usSubFrameLen;    /* 最大子帧长度 */
    USHORT usFrameLen;       /* 最大复合帧长度 */
    USHORT usSubFrameCount;  /* 最大子帧数 */
    USHORT usMuxDelay;       /* 最大报文复合时延 */
    
    UCHAR  ucMhfCode;        /* MHF选项的code值 2:长序列头格式；6:短序列头格式 */ 
    UCHAR  ucMhfClass;       /* MHF选项的class值:对应头格式所支持的等级数 */
    ULONG  ulMcPrefixESum;   /* 存在的前缀省略映射对数目 */
}PPPCONFIGINFO_FOR_BAK_OLD_S;

typedef struct tagPppLcpOptionBak
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
         neg_mrru : 1,
         neg_ssnhf : 1,
         neg_discr : 1,
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
    /*用宏代替数字做数组的长度*/
    UCHAR   discr_addr[PPP_MP_DISCR_MAX_LENGTH];
    UCHAR   callbackinfo[PPP_MAX_CALLBACK_INFO_LEN];
    UCHAR   callbacklen;

    UCHAR ucPrefixELen;       /* Req报文中前缀省略选项的长度 */
    UCHAR ucMhfCode;          /* MHF选项中code值 */
    UCHAR ucMhfClass;         /* MHF选项中class值 */
    UCHAR ucReserve; 
} PPP_LCP_OPTION_BAK_S;

typedef struct tagPppIpcpOptionBak
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

} PPP_IPCP_OPTION_BAK_S;

typedef struct tagPppMuxcpOptionBak
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
} PPP_MUXCP_OPTION_BAK_S; 

/* Begin of HA UPGRADE modification, 2010 December to 2011 January */
/* 定义这个结构，是为了解决VR6C02和VR6C05版本上，PPP_MUXCP_OPTION_BAK_S对于大端字节序宏使用不正确的问题 */
typedef struct tagPppMuxcpPid_LD
{
    /* 是否协商 */
    ULONG bReserve       : 31,   /* 为了以后扩展预留协商位 */
          neg_defaultpid : 1;    /* Negotiate Default Pid */
}PPP_MUXCP_PID_LD_S;

/* End of HA UPGRADE modification, 2010 December to 2011 January */

typedef struct tagPppOsicpOptionBak
{
    /* 是否协商 */
    UCHAR neg_Align_NPDU ;
    /* 协商参数值 */
    UCHAR ucAlign_NPDU;
	
	UCHAR ucRes[2];
} PPP_OSICP_OPTION_BAK_S; 

#define PPP_COPY_IPCP_OPTION(to, from) \
{ \
    (to).neg_addr = (from).neg_addr; \
    (to).old_addrs = (from).old_addrs; \
    (to).req_addr = (from).req_addr; \
    (to).neg_vj = (from).neg_vj; \
    (to).neg_dnsaddr0 = (from).neg_dnsaddr0; \
    (to).req_dnsaddr0 = (from).req_dnsaddr0; \
    (to).neg_nbnsaddr0 = (from).neg_nbnsaddr0; \
    (to).req_nbnsaddr0 = (from).req_nbnsaddr0; \
    (to).neg_dnsaddr1 = (from).neg_dnsaddr1; \
    (to).req_dnsaddr1 = (from).req_dnsaddr1; \
    (to).neg_nbnsaddr1 = (from).neg_nbnsaddr1; \
    (to).req_nbnsaddr1 = (from).req_nbnsaddr1; \
    (to).accept_dnsaddr0 = (from).accept_dnsaddr0; \
    (to).accept_dnsaddr1 = (from).accept_dnsaddr1; \
    (to).accept_nbnsaddr0 = (from).accept_nbnsaddr0; \
    (to).neg_iphc = (from).neg_iphc; \
    (to).accept_nbnsaddr1 = (from).accept_nbnsaddr1; \
    (to).breserved = (from).breserved; \
    (to).vj_protocol = (from).vj_protocol; \
    (to).maxslotindex = (from).maxslotindex; \
    (to).cflag = (from).cflag; \
    (to).ouraddr = (from).ouraddr; \
    (to).hisaddr = (from).hisaddr; \
    (to).dnsaddr0 = (from).dnsaddr0; \
    (to).nbnsaddr0 = (from).nbnsaddr0; \
    (to).dnsaddr1 = (from).dnsaddr1; \
    (to).nbnsaddr1 = (from).nbnsaddr1; \
    (to).iphc_protocol = (from).iphc_protocol; \
    (to).us_tcp_space = (from).us_tcp_space; \
    (to).us_non_tcp_space = (from).us_non_tcp_space; \
    (to).us_f_max_period = (from).us_f_max_period; \
    (to).us_f_max_time = (from).us_f_max_time; \
    (to).us_max_header = (from).us_max_header; \
    (to).ucRtpCompression = (from).ucRtpCompression; \
    (to).ucCompressType = (from).ucCompressType; \
}

#define PPP_COPY_PPPMUX_OPTION(to, from) \
{ \
    (to).neg_defaultpid = (from).neg_defaultpid; \
    (to).bReserve = (from).bReserve; \
    (to).usDefaultPid = (from).usDefaultPid; \
    (to).usReserved = (from).usReserved; \
}

#define PPP_COPY_OSICP_OPTION(to, from) \
{ \
    (to).neg_Align_NPDU = (from).neg_Align_NPDU; \
    (to).ucAlign_NPDU = (from).ucAlign_NPDU; \
}


#define PPP_COPY_LCPOPTION_EXCEPT_PREFIX(to, from) \
{ \
    (to)->neg_mru = (from)->neg_mru; \
    (to)->neg_asyncmap = (from)->neg_asyncmap; \
    (to)->neg_upap = (from)->neg_upap; \
    (to)->neg_chap = (from)->neg_chap; \
    (to)->neg_magicnumber = (from)->neg_magicnumber; \
    (to)->neg_pcompression = (from)->neg_pcompression; \
    (to)->neg_accompression =  (from)->neg_accompression; \
    (to)->neg_lqr = (from)->neg_lqr; \
    (to)->neg_mrru = (from)->neg_mrru; \
    (to)->neg_ssnhf = (from)->neg_ssnhf; \
    (to)->neg_discr = (from)->neg_discr; \
    (to)->neg_callback = (from)->neg_callback; \
    (to)->neg_mhf = (from)->neg_mhf; \
    (to)->neg_prefixE = (from)->neg_prefixE; \
    (to)->bReserve = (from)->bReserve; \
    (to)->mru = (from)->mru; \
    (to)->mrru = (from)->mrru; \
    (to)->asyncmap = (from)->asyncmap; \
    (to)->magicnumber = (from)->magicnumber; \
    (to)->numloops = (from)->numloops; \
    (to)->chap_mdtype = (from)->chap_mdtype; \
    (VOID)TCPIP_Mem_Copy((to)->ucPadding, sizeof((to)->ucPadding), (from)->ucPadding, 3); \
    (to)->lqr_period = (from)->lqr_period; \
    (to)->discr_len = (from)->discr_len;  \
    (to)->discr_class = (from)->discr_class; \
    (to)->callbackopr = (from)->callbackopr; \
    (VOID)TCPIP_Mem_Copy((to)->discr_addr, sizeof((to)->discr_addr), (from)->discr_addr, PPP_MP_DISCR_MAX_LENGTH); \
    (VOID)TCPIP_Mem_Copy((to)->callbackinfo, sizeof((to)->callbackinfo), (from)->callbackinfo, PPP_MAX_CALLBACK_INFO_LEN); \
    (to)->callbacklen = (from)->callbacklen; \
    (to)->ucPrefixELen = (from)->ucPrefixELen; \
    (to)->ucMhfCode = (from)->ucMhfCode; \
    (to)->ucMhfClass = (from)->ucMhfClass; \
    (to)->ucReserve = (from)->ucReserve; \
}

#define PPP_COPY_PREFIX(to, from) \
{ \
    ULONG ulCopyTime; \
    for ( ulCopyTime = 0; ulCopyTime < MC_PREFIXE_MAX_NUM; ulCopyTime++ ) \
    { \
        (VOID)TCPIP_Mem_Copy(to[ulCopyTime].aucPrefixE, sizeof(to[ulCopyTime].aucPrefixE), from[ulCopyTime].aucPrefixE, MC_PREFIXE_MAX_STR); \
        to[ulCopyTime].ucIsUsedFlag = from[ulCopyTime].ucIsUsedFlag; \
        to[ulCopyTime].ucClass = from[ulCopyTime].ucClass; \
        to[ulCopyTime].ucPrefixELen = from[ulCopyTime].ucPrefixELen; \
        to[ulCopyTime].ucReserve = from[ulCopyTime].ucReserve; \
    } \
}
 

/*为了处理简单，重新定义一个结构*/
typedef struct tagPppConfigInfoBak
{
    PPPCONFIGINFO_FOR_BAK_S stPppConfigInfo;
    MC_PREFIXE_BAK_S stPrefixE[MC_PREFIXE_MAX_NUM];/* 前缀省略映射表 */    
}PPPCONFIGINFO_BAK_S;

typedef struct tagPppConfigInfoBakOld
{
    PPPCONFIGINFO_FOR_BAK_OLD_S stPppConfigInfo;
    MC_PREFIXE_BAK_S stPrefixE[MC_PREFIXE_MAX_NUM];/* 前缀省略映射表 */    
}PPPCONFIGINFO_BAK_OLD_S;

/*为了处理简单，重新定义一个结构*/
typedef struct tagPppLcpBAkOption
{
    PPP_LCP_OPTION_BAK_S stPppLcpOption;
    MC_PREFIXE_BAK_S stPrefixE[MC_PREFIXE_MAX_NUM]; /* 前缀省略映射表，该表是一个16个MC_PREFIXE_S元素的数组，存储前缀省略规则 */
} PPP_LCPBAK_OPTION_S;

/* 状态机模块备份数据结构 */
typedef struct tagPppFsmBak
{
    ULONG   ulTimeOutTime;       /* config request报文的超时时间 */
    ULONG   ulEchoTimeOutTime;   /* LCP Echo request报文的超时时间 */
    USHORT  usProtocol;          /* 子协议的PPP协议号  */
    UCHAR   ucState ;            /* 协议状态 */
    UCHAR   ucNeedNego;          /* 是否协商子协议 */
} PPPFSM_BAK_S ;


/* LCP控制块备份数据结构 */
typedef struct tagPppLcpInfoBak
{
    PPPFSM_BAK_S     stFsmBak;        /* LCP协议状态机需要备份的数据 */
    ULONG            ulBakPrefix ;    /* 是否备份前缀表,是按位判断的 */
    PPP_LCPBAK_OPTION_S stGotOptions;    /* 已经协商到的我的选项 */
    PPP_LCPBAK_OPTION_S stHisOptions;    /* 已经协商到的对方的选项 */
    PPP_LCPBAK_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_LCPBAK_OPTION_S stAllowOptions;  /* 允许与对方协商的我的选项 */
} PPPLCPINFO_BAK_S ;


/* IPCP控制块备份数据结构 */
typedef struct tagPppIpcpInfoBak
{
    PPPFSM_BAK_S      stFsmBak;       /* IPCP协议状态机要备份的数据 */   
    PPP_IPCP_OPTION_BAK_S stGotOptions;   /* 已经协商到的我的选项 */   
    PPP_IPCP_OPTION_BAK_S stHisOptions;   /* 已经协商到的对方的选项 */   
    PPP_IPCP_OPTION_BAK_S stWantOptions;  /* 我希望与对方协商的我的选项 */   
    PPP_IPCP_OPTION_BAK_S stAllowOptions; /* 允许与对方协商的我的选项 */   
} PPPIPCPINFO_BAK_S ;


/* MUXCP控制块备份数据结构 */
typedef struct tagPppMUXCPInfoBak
{
    PPPFSM_BAK_S      stFsmBak;         /* MUXVP协议状态机要备份的数据 */  
    PPP_MUXCP_OPTION_BAK_S  stGotOptions;   /* 已经协商到的我的选项 */   
    PPP_MUXCP_OPTION_BAK_S stHisOptions;    /* 已经协商到的对方的选项 */  
    PPP_MUXCP_OPTION_BAK_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_MUXCP_OPTION_BAK_S stAllowOptions;  /* 允许与对方协商的我的选项 */
} PPPMUXCPINFO_BAK_S;

/* OSICP控制块备份数据结构 */
typedef struct tagPppOSICPInfoBak
{
    PPPFSM_BAK_S      stFsmBak;         /* OSICP协议状态机要备份的数据 */  
    PPP_OSICP_OPTION_BAK_S stGotOptions;    /* 已经协商到的我的选项 */   
    PPP_OSICP_OPTION_BAK_S stHisOptions;    /* 已经协商到的对方的选项 */  
    PPP_OSICP_OPTION_BAK_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_OSICP_OPTION_BAK_S stAllowOptions;  /* 允许与对方协商的我的选项 */
} PPPOSICPINFO_BAK_S;

/* OSICP控制块批量备份数据结构 */
typedef struct tagPppOSICPBatchBak
{
    ULONG ulIfIndex;                       /* 接口索引 */
    PPPOSICPINFO_BAK_S  stInfoBak;         /* OSICP协议备份的数据 */  
} PPPOSICPBATCH_BAK_S;

/* PAP控制块备份数据结构 */
typedef struct tagPppPapInfoBak
{
    UCHAR ucServerState;               /* Server 状态 */ 
    UCHAR ucClientState;               /* Client 状态 */ 
    UCHAR ucAuthServer ;               /* 本端作为认证端* */ 
    UCHAR ucAuthClient ;               /* 本端作为被认证端 */ 
    UCHAR szPapUsrName[PPP_MAXUSERNAMELEN + 2];  /* 用户名  */ 
    UCHAR szPapUsrPwd[PPP_MAXUSERPWDLEN + 2];    /* 用户pwd */ 
}PPPPAPINFO_BAK_S;

/* CHAP控制块备份数据结构 */
typedef struct tagPppChapInfoBak 
{
    UCHAR ucServerState;         /* Server 状态 */ 
    UCHAR ucClientState;         /* Client 状态 */ 
    UCHAR ucAuthServer ;         /* 本端作为认证端* */
    UCHAR ucAuthClient ;         /* 本端作为被认证端 */
    UCHAR szHostName[PPP_MAXUSERNAMELEN + 2]; /* 主机名 */
    UCHAR szHostPwd[PPP_MAXUSERPWDLEN + 2];   /* pwd */
} PPPCHAPINFO_BAK_S ;

/* PAP控制块备份数据结构 */
typedef struct tagPppPapInfoBakOld
{
    UCHAR ucServerState;               /* Server 状态 */ 
    UCHAR ucClientState;               /* Client 状态 */ 
    UCHAR ucAuthServer ;               /* 本端作为认证端* */ 
    UCHAR ucAuthClient ;               /* 本端作为被认证端 */ 
    UCHAR szPapUsrName[PPP_MAXUSERNAMELEN + 2];  /* 用户名  */ 
    UCHAR szPapUsrPwd[PPP_MAXUSERPWDLENOLD + 2];    /* 用户pwd */ 
}PPPPAPINFO_BAK_OLD_S;

/* CHAP控制块备份数据结构 */
typedef struct tagPppChapInfoBakOld 
{
    UCHAR ucServerState;         /* Server 状态 */ 
    UCHAR ucClientState;         /* Client 状态 */ 
    UCHAR ucAuthServer ;         /* 本端作为认证端* */
    UCHAR ucAuthClient ;         /* 本端作为被认证端 */
    UCHAR szHostName[PPP_MAXUSERNAMELEN + 2]; /* 主机名 */
    UCHAR szHostPwd[PPP_MAXUSERPWDLENOLD + 2];   /* pwd */
} PPPCHAPINFO_BAK_OLD_S ;

/* PPP接口信息备份数据结构，在批量备份时以接口为单位收集备份信息 */
typedef struct tag_PPPINTF_BAK_S
{
    ULONG   bBakPppCb: 1,    /* 用于判断是否备份PPP CB 信息 */
            bBakLcp: 1,      /* 用于判断是否备份LCP 信息*/
            bBakIpcp: 1,     /* 用于判断是否备份IPCP 信息*/
            bBakMuxcp: 1,    /* 用于判断是否备份Muxcp 信息*/
            bBakPap: 1,      /* 用于判断是否备份PAP 信息*/
            bBakChap: 1,     /* 用于判断是否备份CHAP 信息*/
            bBakConfig:1,    /* 用于判断是否备份config配置信息信息*/
            bBakConfigPrefixE:1,    /* config中是否存在前缀表*/
            bBakUsedConfig:1,    /* 用于判断是否备份usedconfig配置信息信息*/
            bBakUsedConfigPrefixE:1,    /* usedconfig中是否存在前缀表*/
            bReserved :22;   /* */
    
    PPPCONFIGINFO_BAK_S   stPppConfig;
    PPPCONFIGINFO_BAK_S   stPppUsedConfig;
    PPPINFO_BAK_S        stPppCBInfo; /* PPP控制块信息 */
    PPPLCPINFO_BAK_S     stLcpInfo;   /* LCP控制块信息 */
    PPPIPCPINFO_BAK_S    stIpcpInfo;  /* IPCP控制块信息 */
    PPPMUXCPINFO_BAK_S   stMuxcpInfo; /* Muxcp控制块信息 */
    PPPPAPINFO_BAK_S     stPapInfo;   /* PAP控制块信息 */ 
    PPPCHAPINFO_BAK_S    stChapInfo;  /* CHAP控制块信息 */
}PPPINTF_BAK_S;

typedef struct tag_PPPINTF_BAK_OLD_S
{
    ULONG   bBakPppCb: 1,    /* 用于判断是否备份PPP CB 信息 */
            bBakLcp: 1,      /* 用于判断是否备份LCP 信息*/
            bBakIpcp: 1,     /* 用于判断是否备份IPCP 信息*/
            bBakMuxcp: 1,    /* 用于判断是否备份Muxcp 信息*/
            bBakPap: 1,      /* 用于判断是否备份PAP 信息*/
            bBakChap: 1,     /* 用于判断是否备份CHAP 信息*/
            bBakConfig:1,    /* 用于判断是否备份config配置信息信息*/
            bBakConfigPrefixE:1,    /* config中是否存在前缀表*/
            bBakUsedConfig:1,    /* 用于判断是否备份usedconfig配置信息信息*/
            bBakUsedConfigPrefixE:1,    /* usedconfig中是否存在前缀表*/
            bReserved :22;   /* */
    
    PPPCONFIGINFO_BAK_OLD_S   stPppConfig;
    PPPCONFIGINFO_BAK_OLD_S   stPppUsedConfig;
    PPPINFO_BAK_S        stPppCBInfo; /* PPP控制块信息 */
    PPPLCPINFO_BAK_S     stLcpInfo;   /* LCP控制块信息 */
    PPPIPCPINFO_BAK_S    stIpcpInfo;  /* IPCP控制块信息 */
    PPPMUXCPINFO_BAK_S   stMuxcpInfo; /* Muxcp控制块信息 */
    PPPPAPINFO_BAK_OLD_S     stPapInfo;   /* PAP控制块信息 */ 
    PPPCHAPINFO_BAK_OLD_S    stChapInfo;  /* CHAP控制块信息 */
}PPPINTF_BAK_OLD_S;


/*子协议备份缓冲区长度,以批量备份时单接口满配置所需的备份长度为备份缓冲区长度*/
#define  PPP_MAX_PROTOCOL_INFO_LEN       sizeof(PPPINTF_BAK_S)   

/* PPP子协议备份数据结构 */
typedef struct tag_PPP_PROTOCOL_BAK_S
{
    ULONG ulIfIndex;    /* 子协议控制块所对应的接口索引 */
    ULONG ulProtocol;   /* 子协议的PPP协议号 */
    CHAR szProtocolInfo[PPP_MAX_PROTOCOL_INFO_LEN] ;/* 子协议控制块信息存储区 */
}PPP_PROTOCOL_BAK_S;


/* PPP快照备份数据结构 */
typedef struct tag_PPP_BAK_S
{
    ULONG ulProMsgType ;   /* 备份消息类型 */
    PPP_PROTOCOL_BAK_S   stPPPBak  ;  /* 需要备份的信息 */
}PPP_BAK_S;

/* MP绑定信息备份结构 */
typedef struct tag_PPPMP_BAK_S 
{
    UCHAR ucMpGroupName[IF_MAX_INTERFACE_NAME_LEN+1];  /* 接口名*/
    ULONG ulIfindexArrary[MP_SUPPORT_MAX_BIND];    /* 接口索引表 */
}PPPMP_BAK_S;

/* MP绑定信息备份结构 */
typedef struct tag_MPCFG_BAK_S
{
    ULONG  ulflag;        /* 标记备份的命令类型 */
    ULONG  ulSubIfIndex;  /* 子通道索引 */
    CHAR   szMpGroupName [ IF_MAX_INTERFACE_NAME_LEN+1];   /* 父接口名*/
}MPCFG_BAK_S;

/* PPP模块全局变量备份结构 */
typedef struct tag_PPPGLOBALVAR_BAK_S
{
    ULONG   ulDiscrSpecial;  /* HDLC自动侦听功能开关备份变量 */
    ULONG   ulPPPResetTime;  /* 定时器超时时间单位为毫秒 */
    ULONG   ulMpReorderWinTimes;/*MP重组窗口调整信息*/
    ULONG   ulMpEDConsistent; /* MP终端描述符号一致性开关 */
}PPPGLOBALVAR_BAK_S;

#define PPP_HA_TLLENGTH 4

typedef struct tagPPPTYPELENGTH
{
    USHORT usType;             /*type*/
    USHORT usLength;           /*length*/
}PPPTYPELENGTH_S;

/*T*/
typedef enum tagPPPBAKTYPE
{
    PPP_HA_SET_NEGTIME = 0x1000
}PPPBAKTYPE_E;

/*V*/
typedef struct tagPPP_NEGTIME_BAK
{
    ULONG  ulNegTime;
}PPP_NEGTIME_BAK_S;

/*定义PPP模块HA的标准备份消息头等数据结构,add by wuhailan,2008-04-11.*/
/*PPP模块HA备份消息头*/
typedef struct tagPPP_HA_HEAD
{
    USHORT usPppOprType;  /* PPP备份消息类型  */
    USHORT usPppOprLen;   /* PPP备份消息长度  */
}PPP_HA_HEAD_S;

/*配置子消息类型TLV结构*/
typedef struct tagPPP_CFG_UNIDIRECTION_HA_TLV
{
    USHORT usMsgType;
    USHORT usMsgLen;
    UCHAR  ucEnableUniDirection;  /*是否支持IPHC单通处理*/
    UCHAR  ucPadding[3];
}PPP_CFG_UNIDIRECTION_HA_TLV_S;

/*PPP模块新增信息HA备份标准消息头*/
typedef struct tagPPP_NEW_CFG_BAK  
{
    /*基础数据区*/
    ULONG ulIfIndex;    /*接口索引*/
    PPP_CFG_UNIDIRECTION_HA_TLV_S stConfigUniDirection;/*单通处理配置子消息类型*/
}PPP_NEW_CFG_BAK_S;

/*PPP模块新增信息HA备份标准消息头*/
typedef struct tagPPP_NEW_GLOBARVAR_BAK  
{
    USHORT usMsgType;
    USHORT usMsgLen;
    PPPVERIFYSWITCH_S stVerifySwitch; /*核查开关*/
}PPP_NEW_GLOBARVAR_VERIFYSWITCH_BAK_S;

/* 定义TLV中的TL字段 */
typedef struct tagPPP_HA_TLV
{
    USHORT usSubMsgType; /* 备份子消息类型 */
    USHORT usSubMsgLen;  /* 备份子消息长度 */
}PPP_HA_TLV_S;

typedef struct tagPPP_CFG_NEGO_MAGICNUM_BAK
{
    ULONG ulIfIndex;         /* 接口索引 */
    ULONG ulNegoMagicNum;    /* 是否协商Magic Number选项标记 */
}PPP_CFG_NEGO_MAGICNUM_BAK_S;

typedef struct tagPPP_CFG_SELFLOOP_BAK
{
    ULONG ulIfIndex;         /* 接口索引 */
    ULONG ulSelfLoop;        /* 是否设置为自环模式标记 */
}PPP_CFG_SELFLOOP_BAK_S;

typedef struct tagPPP_CFG_DR_BAK
{
    ULONG ulIfIndex;       /*接口索引*/
    ULONG ulDiscardReq;    /*是否处理Discard Request报文开关*/
}PPP_CFG_DR_BAK_S;

/* 备份NCP延时补发一个NCP CR报文的TLV结构 */
typedef struct tagPPP_CFG_NRT_BAK
{
    ULONG ulIfIndex;        /* 接口索引 */
    ULONG ulNcpResendTime;  /* NCP延时补发一个NCP CR报文的时间值 */
}PPP_CFG_NRT_BAK_S;

/*备份PPP检测自环次数*/
typedef struct tagPPP_LOOPBACKTIME_BAK  
{
    USHORT usMsgType;
    USHORT usMsgLen;
    ULONG ulPPPLoopbackTime; /*自环检测次数*/
}PPP_LOOPBACKTIME_BAK_S;

typedef struct tagPPP_HA_VIRTUAL_INFO_BAK
{
    ULONG ulIfIndex;
    ULONG ulLocalIp;
    ULONG ulRemoteIp;
    ULONG ulMtu;
    ULONG ulFlag;
    ULONG ulVlinkIndex;
}PPP_HA_VIRTUAL_INFO_BAK_S;

typedef struct tagPPP_DNSTLV_BAK
{
    USHORT usType;
    USHORT usLen;
    ULONG aulDNSIP[DHCP4C_DNSIP_NUM];  
}PPP_DNSTLV_BAK_S;

typedef struct tagPPP_CFG_DEALACFCPFC_BAK
{
    ULONG ulIfIndex;        /* 接口索引 */
    ULONG ulDealAcfcPfc;    /* 是否接受和处理ACFC/PFC协商选项标记 */
}PPP_CFG_DEALACFCPFC_BAK_S;

typedef struct tagPPP_ISISFLAG_BAK
{
    ULONG ulIfIndex;        /* 接口索引 */
    ULONG ulIsIsFlag;       /* 是否使能ISIS报文发送 */
}PPP_ISISFLAG_BAK_S;


enum enumPPPBAKMsgType  /*操作类型*/
{
    PPP_BAK_BATCH_MPINFO = 1,   /*批备份MP绑定信息*/
    PPP_BAK_BATCH_PPPINFO,     /*批备份PPP信息*/
    PPP_BAK_REALTIME_PPPINFO,  /*PPP实时备份*/
    PPP_BAK_REALTIME_CONFIGINFO, /*配置信息备份*/
    PPP_BAK_MPCONFIG_INFO,     /*Mp配置信息备份*/
    PPP_BAK_EVENT_OPENED,      /*PPP 子协议OPEN命今字*/
    PPP_BAK_EVENT_INIT,        /*PPP 子协议DOWN命今字*/
    PPP_BAK_EVENT_SHUTDOWN,    /*接口被shutdown导致PPP 子协议DOWN命今字*/
    PPP_BAK_LCP_OPENED,        /*LCP 协议OPEN*/
    PPP_BAK_IPCP_OPENED,       /* IPCP协议OPEN*/
    PPP_BAK_MUXCP_OPENED,      /* MUXCP协议OPEN*/
    PPP_BAK_PAP_OPENED,        /* PAP协议OPEN*/
    PPP_BAK_CHAP_OPENED,       /* CHAP协议OPEN*/
    PPP_BAK_MPSUBLINK_OPENED,  /*MP子通道绑定成功*/
    PPP_BAK_CONFIG_INFO,       /*备份CONFIG配置信息*/
    PPP_BAK_USEDCONFIG_INFO,   /*备份USEDCONFIG配置信息*/
    PPP_BAK_NO_PPPMULTILINK,   /*MP配置信息*/
    PPP_BAK_BINDTO_MPGROUP,    /*MP绑定信息*/
    PPP_BAK_GLOBALVAR,         /*全局变量备份*/
    
    /*VISPV1R7新增的备份项操作类型值从0X80开始,前面的值预留给VISPV1R6*/
    PPP_BAK_BATCH_NEW_PPPINFO = 0X80,
    PPP_BAK_VIRTUAL,
    PPP_BAK_NEW_GLOBALVAR,
    PPP_NEWBAK_TLV_MSG,        /* 备份的所有子消息都是按TLV格式组包的 */
    PPP_BAK_OSICP_OPENED,      /* OSICP协议OPEN*/
};

/*新的PPP HA头消息类型, 支持无损升级, 类型定义不能重复, 后续修改禁止删除*/
enum enumPPPNEWBAKMsgType  
{
    /*VISPV1R7新增的备份项类型值从0X0100开始,前面的值预留给VISPV1R6*/
    PPP_NEWBAK_CONFIG_INFO = 0X0100, /*新配置信息类型,子类型由下方枚举类型enumPPPNEWCFGBAKSubMsgType定义*/
    
    PPP_VIRTUAL_CONFIG_INFO = 0X0200,/*三维虚拟PPP接口上状态信息的实时备份消息类型*/    
    PPP_DNS_BAK_INFO_CODE = 0X0201,
    
    PPP_NEWBAK_GLOBAL_INFO = 0X0300,  /*新全局变量类型*/
    PPP_NEWBAK_GLOBAL_INFO_VERIFYSWITCH = 0X0301, /*全局变量g_stPppVerifySwitch备份类型*/
    PPP_NEWBAK_GLOBAL_INFO_LOOPBACKTIME = 0x0302, /*全局变量g_ulPPPLoopBackTime备份类型*/
};

enum enumPPPNEWCFGBAKSubMsgType  /*PPP_NEWBAK_CONFIG_INFO消息类型下的子消息类型,占两个字节*/
{
    PPP_NEWBAK_CONFIG_INFO_CODE = 0X0100,   /*VISPV1R7新增的备份项类型值从0X0100开始,前面的值预留给VISPV1R6*/
};

enum PPP_NEWBAK_TLV_MSG_TYPE  /*PPP_NEWBAK_TLV_MSG消息类型下的子消息类型,占两个字节*/
{
    /*Mod By t00110672 for BC3D01741,2009-8-25,修改REQ为CFG*/
    PPP_NEWBAK_TLV_DISCARDREQ_CFG = 1, /* 备份配置的Discard Request开关的子消息类型，V1R7C01的类型  */
    /*Mod End*/
    PPP_NEWBAK_TLV_DISCARDREQ_USE,      /* 备份生效的Discard Request开关的子消息类型，V1R7C01的类型 */
    PPP_NEWBAK_TLV_DEAL_ACFCPFC_CFG,    /* 备份配置的"是否接受和处理ACFC/PFC协商选项的标记"子消息类型，VR6C05类型 */
    PPP_NEWBAK_TLV_DEAL_ACFCPFC_USE,    /* 备份生效的"是否接受和处理ACFC/PFC协商选项的标记"子消息类型，VR6C05类型 */
    PPP_NEWBAK_TLV_IPHCUNIDIRT_USE,     /* 备份生效的IPHC单通使能标记，z00104207 for BC3D01706，V1R7C01的类型 */
    PPP_NEWBAK_TLV_NEGO_MAGICNUM_USE,   /* 备份生效的"是否协商Magic Number选项的标记"子消息类型，VR6C02类型 */
    PPP_NEWBAK_TLV_NEGO_MAGICNUM_CFG,   /* 备份配置的"是否协商Magic Number选项的标记"子消息类型，VR6C02类型 */
    PPP_NEWBAK_TLV_SELFLOOP_USE,        /* 备份生效的"是否设置自环模式标记"子消息类型，VR6C02类型 */
    PPP_NEWBAK_TLV_SELFLOOP_CFG,        /* 备份配置的"是否设置自环模式标记"子消息类型，VR6C02类型 */
    PPP_NEWBAK_TLV_NCPRESENDTIME_USE,   /* 备份生效的"延时补发一个NCP CR报文的时间"子消息类型 */
    PPP_NEWBAK_TLV_NCPRESENDTIME_CFG,   /* 备份配置的"延时补发一个NCP CR报文的时间"子消息类型 */
    PPP_NEWBAK_TLV_OSICP_INFO,          /* 备份OSICP协议信息 */
    PPP_NEWBAK_TLV_ISISFLAG_INFO,       /* 备份ISIS标记信息 */
};

#define PPP_TLV_HEAD_LENGTH     4  /*TLV格式固定首部长度*/

#define PPP_HA_ENCAPTLV(pBuf, usMsgType, usMsgLen, pPara)\
{\
    USHORT *pusBuf = (USHORT *)(pBuf);\
    *pusBuf = (usMsgType);\
    *(pusBuf+1) = (usMsgLen);\
    (pBuf) += PPP_TLV_HEAD_LENGTH;\
    (VOID)TCPIP_Mem_Copy((pBuf), (usMsgLen) - PPP_TLV_HEAD_LENGTH, (pPara), (usMsgLen) - PPP_TLV_HEAD_LENGTH);\
    (pBuf) += (usMsgLen) - PPP_TLV_HEAD_LENGTH;\
}

#define PPP_BAKUP_FSM_INFO(from, to) \
{ \
    (to).ulTimeOutTime     = (from).ulTimeOutTime; \
    (to).ulEchoTimeOutTime = (from).ulEchoTimeOutTime; \
    (to).usProtocol        = (from).usProtocol; \
    (to).ucState           = (from).ucState; \
}



/* 备份IPCP信息 */
/*
from: PPPIPCPINFO_S*
to:   PPPIPCPINFO_BAK_S*
*/

#define PPP_BAKUP_IPCP_INFO_SND(from, to) \
{ \
    PPP_BAKUP_FSM_INFO((from)->stFsm, (to)->stFsmBak); \
    PPP_COPY_IPCP_OPTION((to)->stGotOptions, (from)->stGotOptions); \
    PPP_COPY_IPCP_OPTION((to)->stHisOptions, (from)->stHisOptions); \
    PPP_COPY_IPCP_OPTION((to)->stWantOptions, (from)->stWantOptions); \
    PPP_COPY_IPCP_OPTION((to)->stAllowOptions, (from)->stAllowOptions); \
}

#define PPP_BAKUP_IPCP_INFO_RCV(from, to) \
{ \
    PPP_BAKUP_FSM_INFO((from)->stFsmBak, (to)->stFsm); \
    PPP_COPY_IPCP_OPTION((to)->stGotOptions, (from)->stGotOptions); \
    PPP_COPY_IPCP_OPTION((to)->stHisOptions, (from)->stHisOptions); \
    PPP_COPY_IPCP_OPTION((to)->stWantOptions, (from)->stWantOptions); \
    PPP_COPY_IPCP_OPTION((to)->stAllowOptions, (from)->stAllowOptions); \
}

/* 备份MUXCP信息 */
/*
from: PPPMUXCPINFO_S*
to:   PPPMUXCPINFO_BAK_S*
*/

#define PPP_BAKUP_MUXCP_INFO_SND(from, to) \
{ \
    PPP_BAKUP_FSM_INFO((from)->stFsm, (to)->stFsmBak); \
    PPP_COPY_PPPMUX_OPTION((to)->stGotOptions, (from)->stGotOptions);\
    PPP_COPY_PPPMUX_OPTION((to)->stHisOptions, (from)->stHisOptions);\
    PPP_COPY_PPPMUX_OPTION((to)->stWantOptions, (from)->stWantOptions);\
    PPP_COPY_PPPMUX_OPTION((to)->stAllowOptions, (from)->stAllowOptions);\
}

#define PPP_BAKUP_MUXCP_INFO_RCV(from, to) \
{ \
    PPP_BAKUP_FSM_INFO((from)->stFsmBak, (to)->stFsm); \
    PPP_COPY_PPPMUX_OPTION((to)->stGotOptions, (from)->stGotOptions);\
    PPP_COPY_PPPMUX_OPTION((to)->stHisOptions, (from)->stHisOptions);\
    PPP_COPY_PPPMUX_OPTION((to)->stWantOptions, (from)->stWantOptions);\
    PPP_COPY_PPPMUX_OPTION((to)->stAllowOptions, (from)->stAllowOptions);\
}

/* pwd最大长度为20位 */
/* 备份PAP信息 */
#define PPP_BAKUP_PAP_INFO_PROC(from, to) \
{ \
    (to)->ucServerState = (from)->ucServerState; \
    (to)->ucClientState = (from)->ucClientState; \
    (VOID)TCPIP_Mem_Copy((to)->szPapUsrName, sizeof((to)->szPapUsrName), (from)->szPapUsrName, PPP_MAXUSERNAMELEN + 2); \
    (VOID)TCPIP_Mem_Copy((to)->szPapUsrPwd, sizeof((to)->szPapUsrPwd), (from)->szPapUsrPwd, PPP_MAXUSERPWDLEN + 2); \
}
/* 备份CHAP信息 */
#define PPP_BAKUP_CHAP_INFO_PROC(from, to) \
{ \
    (to)->ucClientState = (from)->ucClientState; \
    (to)->ucServerState = (from)->ucServerState; \
    (VOID)TCPIP_Mem_Copy((to)->szHostName, sizeof((to)->szHostName), (from)->szHostName, PPP_MAXUSERNAMELEN + 2);\
    (VOID)TCPIP_Mem_Copy((to)->szHostPwd, sizeof((to)->szHostPwd), (from)->szHostPwd, PPP_MAXUSERPWDLEN + 2);\
}

/* pwd最大长度为16位 */
/* 备份PAP信息 */
#define PPP_BAKUP_PAP_INFO_PROC_OLD(from, to) \
{ \
    (to)->ucServerState = (from)->ucServerState; \
    (to)->ucClientState = (from)->ucClientState; \
    (VOID)TCPIP_Mem_Copy((to)->szPapUsrName, sizeof((to)->szPapUsrName), (from)->szPapUsrName, PPP_MAXUSERNAMELEN + 2); \
    (VOID)TCPIP_Mem_Copy((to)->szPapUsrPwd, sizeof((to)->szPapUsrPwd), (from)->szPapUsrPwd, PPP_MAXUSERPWDLENOLD + 2); \
}
/* 备份CHAP信息 */
#define PPP_BAKUP_CHAP_INFO_PROC_OLD(from, to) \
{ \
    (to)->ucClientState = (from)->ucClientState; \
    (to)->ucServerState = (from)->ucServerState; \
    (VOID)TCPIP_Mem_Copy((to)->szHostName, sizeof((to)->szHostName), (from)->szHostName, PPP_MAXUSERNAMELEN + 2);\
    (VOID)TCPIP_Mem_Copy((to)->szHostPwd, sizeof((to)->szHostPwd), (from)->szHostPwd, PPP_MAXUSERPWDLENOLD + 2);\
}

/* 备份OSICP信息 */
/*
from: PPPOSICPINFO_S*
to:   PPPOSICPINFO_BAK_S*
*/

#define PPP_BAKUP_OSICP_INFO_SND(from, to) \
{ \
    PPP_BAKUP_FSM_INFO((from)->stFsm, (to)->stFsmBak); \
    PPP_COPY_OSICP_OPTION((to)->stGotOptions, (from)->stGotOptions);\
    PPP_COPY_OSICP_OPTION((to)->stHisOptions, (from)->stHisOptions);\
    PPP_COPY_OSICP_OPTION((to)->stWantOptions, (from)->stWantOptions);\
    PPP_COPY_OSICP_OPTION((to)->stAllowOptions, (from)->stAllowOptions);\
}

#define PPP_BAKUP_OSICP_INFO_RCV(from, to) \
{ \
    PPP_BAKUP_FSM_INFO((from)->stFsmBak, (to)->stFsm); \
    PPP_COPY_OSICP_OPTION((to)->stGotOptions, (from)->stGotOptions);\
    PPP_COPY_OSICP_OPTION((to)->stHisOptions, (from)->stHisOptions);\
    PPP_COPY_OSICP_OPTION((to)->stWantOptions, (from)->stWantOptions);\
    PPP_COPY_OSICP_OPTION((to)->stAllowOptions, (from)->stAllowOptions);\
}

extern ULONG PPP_HA_VirtualCfgInput(UCHAR *pBuf, ULONG ulMsgLen);
extern VOID PPP_HA_SendVirtualInfo(IFNET_S *pstIf);
extern ULONG PPP_HA_ProcessVlinkDel(IFNET_S *pstIf,PPP_IPCP_OPTION_S *pstGotOptions,PPPINFO_S *pstPppInfo);
extern ULONG PPP_HA_ProcessMuxCpDown(IFNET_S *pstIf, PPPINFO_S *pstPppInfo);
extern ULONG PPP_HA_ProcessIpcpDown(IFNET_S *pstIf,PPPINFO_S *pstPppInfo);
extern ULONG PPP_HA_ProcessLcpDown (PPPINFO_S *pstPppInfo);
extern ULONG PPP_HA_ProcessNcpDown (PPPINFO_S *pstPppInfo);

extern ULONG PPP_HA_BatchBackup ();
extern ULONG PPP_HA_RealSnd_PppInfo (PPPINFO_S *pstPppInfo, ULONG  ulMsgType,ULONG ulOper);
extern VOID  PPP_HA_RealSnd_CfgInfo (ULONG ulIfIndex, ULONG  ulMsgType);
extern ULONG PPP_HA_RealSnd_MPCfgInfo (ULONG  ulMsgType,ULONG ulSubIfindex,UCHAR *pszMpGroupName);
extern ULONG PPP_HA_Input(UCHAR * pBuf, ULONG ulMsgLen);
extern ULONG  PPP_HA_Smooth();
extern ULONG PPP_HA_GetPppDbg (ULONG *pulDbg);
extern ULONG TCPIP_HA_SetPppDbg (ULONG ulDbg);
extern VOID PPP_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
extern ULONG PPP_HA_SetVerboseDbg (ULONG ulDbg);
extern ULONG PPP_HA_GetVerboseDbg (ULONG *pulDbg);
extern ULONG PPP_HA_SearchMpGroupList(ULONG ulFartherIndex ,ULONG ulSonIndex);
extern VOID PPP_HA_GlobalVar();
extern ULONG PPP_HA_Clean();
extern VOID PPP_HA_IPCPDownProcess(PPPINFO_S *pstPppInfo);

extern VOID PPP_HA_NEW_RealSnd_CfgInfo(ULONG ulIfIndex, ULONG ulSubMsgType);
extern ULONG PPP_HA_NEW_SendMsg(UCHAR *pucHABuf, ULONG ulDataLen);
extern ULONG PPP_HA_NEW_BatchCfgInfo(UCHAR *pucHABuf, ULONG ulBakTotalLen, ULONG ulOffsetLen,
                                     ULONG ulType, VOID *pucNode, ULONG *pulBakNodeLen);
extern ULONG PPP_HA_NEW_BatchPppInfo(VOID);
extern ULONG PPP_HA_NEW_BatchCfgInput(UCHAR *pBuf, ULONG ulMsgLen);
extern ULONG PPP_HA_NEW_BatchPppInput(UCHAR *pBuf, ULONG ulMsgLen);
extern VOID PPP_HA_NEW_RealSnd_GlobalVar(USHORT usMsgType);
extern VOID PPP_HA_NEW_BatchGlobalVar();
extern ULONG PPP_HA_NEW_GlobalVarInput(UCHAR *pBuf, ULONG ulMsgLen);
extern ULONG PPP_HA_TLV_BuildOnePkt(ULONG ulIfIndex, UCHAR *pucBuf, USHORT usOffset, USHORT usSubMsgType, USHORT *pusBakLen);
extern ULONG PPP_HA_TLV_RealTimeBak(ULONG ulIfIndex, USHORT usSubMsgType);
extern ULONG PPP_HA_TLV_BatchBak(VOID);
extern ULONG PPP_HA_TLV_Input(UCHAR *pucBuf, ULONG ulMsgLen);
extern ULONG PPP_HA_TLV_Restore(ULONG ulIfIndex, UCHAR *pucBuf, USHORT usMsgType);
extern ULONG PPP_HA_TLV_OutputMsg(UCHAR *pucBuf, UCHAR ucOperation, USHORT usMsgLen);
extern ULONG PPP_HA_TLV_CalcMsgLen(USHORT usSubMsgType, USHORT *pusMsgLen);
extern ULONG PPP_HA_ProcessOsiCpDown(IFNET_S *pstIf, PPPINFO_S *pstPppInfo);
extern ULONG PPP_HA_TLV_PPPStateBatchBak(VOID);

#ifdef  __cplusplus
}
#endif
#endif


