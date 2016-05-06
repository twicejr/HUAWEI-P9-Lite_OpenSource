/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                             ppp_core_type.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPP
 *  Date Created: 2004-07-01
 *        Author: YiAn
 *   Description: PPP模块的数据结构定义
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004-07-01      YiAn            Create
 *  2006-03-31      ZhuKun          Adjust for D00661
 *  2006-04-21      ZhuKun          Adjust for D00875
 *  2006-05-11      luyao           为支持ARM CPU字节对齐特性，修改结构。
 *  2006-05-13      l48923          Delete useless code
 *
 *************************************************************************/

#ifndef _PPP_CORE_TYPE_H_
#define _PPP_CORE_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ppp/include/ppp_api.h"

/*modify by y36299 for SWFD03884  2004/12/10
  *删除各子协议的debug all开关*/


/* PPP控制块 */
typedef struct tagPppInfo
{
    ULONG bIsAsync: 1,        /* 是否是异步口, 在LCP中判断是否协商ACCMAP */
          bSynAsyConvert: 1,  /* 对于异步口，用于确定是否由PPP进行同/异步报文转换 */
          bLoopBacked: 1,     /* 接口是否发生了自环 */
          bLowerIsUp: 1, 

          bIsDialer:1,       /* 是否拨号口 */
          bIsCallIn:1,       /* 是否是呼入,用于判断是否callback */
          bIsCallBackUser:1, /* 是否是callback用户,验证时从AAA获得 */

          bMpChannelType:2, /* MP通道类型
                                0(PPP_MP_NONE):不是MP
                                1(PPP_MP_SUBCHANNEL):MP子通道
                                2(PPP_MP_FATHER):MP父通道
                                3(PPP_MP_TEMPLATE):MP模版
                             */

          bPppInterleave:1,  /*是否配置LFI*/

          bRunningPoeClient:1, /* 表明该PPP Info结构是否用于PPPoE Client*/

          bLqmStatus:1, /* 表明LQM链路状态 */
          bReserved: 20;     /* 保留,以后使用 */

    ULONG ulRemoteAccm;      /* 对端ACCM控制字 */
    ULONG ulLocalAccm;       /* 本端ACCM控制字 */

    ULONG ulIfIndex;         /* 对应的IFNET索引 */
    ULONG ulVLinkIndex;      /* 保留的VLink索引 */

    ULONG ulGetAddrTmerId;

    ULONG ulRouteIfIndex;    /* 路由可见接口的IFNET索引 */

    /* 构造PPP协议控制块的链表指针 */
    DLL_NODE_S  stPppInfoLink; 

    ULONG usPhase;           /* PPP当前所处协商阶段,可以为如下值:
                                 PPP_PHASE_DEAD
                                 PPP_PHASE_ESTABLISH
                                 PPP_PHASE_AUTHENTICATE
                                 PPP_PHASE_CBCP
                                 PPP_PHASE_NETWORK
                                 PPP_PHASE_TERMINATE
                              */

    ULONG ulResetTimerId;    /* 协商失败后,设置reset定时器,超时后重新协商.
                                 但对于L2TP tunnel、PPPOE等虚接口或DDR的情况,
                                 则通知IFNET，直接断掉
                              */


    ULONG ulPpiFailed;      /* PPI下发失败标志位 */
    ULONG ulFatherIfIndex;  /* 用于PPI(MP)重复下发时找到要下发的父接口 */
    

    /* 配置信息 */
    PPPCONFIGINFO_S *pstConfigInfo;      /* 当前接口上用户输入的配置信息,
                                            只对配置可见接口有效
                                          */
                              
    PPPCONFIGINFO_S *pstUsedConfigInfo;  /* 当前接口用于协商的配置信息,
                                            是从当前接口或其他接口的pstConfigInfo拷贝来的
                                          */

    /* 子协议指针 */
    VOID *pstLcpInfo;        /* LCP  控制块指针 */
    VOID *pstPapInfo;        /* PAP  控制块指针 */
    VOID *pstChapInfo;       /* CHAP 控制块指针 */
    VOID *pstIpcpInfo;       /* IPCP 控制块指针 */
    
    VOID *pstLqmInfo;        /* LQM  控制块指针 */

    VOID *pstIp6cpInfo;       /* IPv6CP 控制块指针 */ 

    ULONG ulIP6LinkStatus;          /* 描述接口的IPv6 DOWN或UP状态 */
    UCHAR ucInterfaceID[8];         /* 接口ID */
    UCHAR ucInterfaceIDAuto[8];     /* 接口ID */
    ULONG ulFirstGetInterfaceID;    /* 第一次获取接口ID的标志 */
    ULONG ulInterfaceIDType; 

    VOID *pstMpInfo;         /* MP控制块指针
                                 对于MP父通道(virtual access)，是MP控制块指针
                                 对于MP子通道，是父通道的IFNET索引
                                 对于MP模板(virtual template或BRI/PRI),是
                                 virtual access链表指针
                              */
    VOID *pstMuxcpInfo;      /* PPPMUXCP 控制块指针 */

    struct tagPppStatistic stStatisticInfo; /* 统计信息，包括计费信息和Mib统计信息 */

    struct tagPppDebugInfo stPppDebugInfo;  /* 接口的debug开关信息 */

    USHORT usMtu;

    /* 记录曾对外输出的PPP告警 */
    USHORT usWarningRecord;

    UCHAR ucAuthServer;        
    UCHAR ucAuthClient;
    UCHAR ucPadding_2[2];
    CHAR  szLoginUsrName[PPP_MAXUSERNAMELEN + 1]; /* 对端向我认证时使用的用户名 */
    CHAR  szCallBackDialString[PPP_MAXCALLBACKDIALERSTRINGLEN + 1];
    CHAR  szCalledNumber[PPP_CALLINGNUM_LEN + 1];
    CHAR  szCallingNumber[PPP_CALLEDNUM_LEN + 1];
    /*end*/
    ULONG ulUserId;

    struct tagIPHC_COMPRESSION_CONTEXT *pCompContext;
    LONG  lCCompany;                        /* 协商结果设置 */

    struct tagSLCompress *pVJContext;

    struct tagPPPMUX_CONTEXT_STRUCT* pstMuxContext; /* PPPMUX上下文指针 */
    /* End of addition */
    ULONG ulIsIsFlag;     /* 是否使能收发ISIS报文，为1使能，0去使能 */
    VOID *pstOsicpInfo;   /* Osicp 控制块指针 */
    UCHAR ucPPPType;
    UCHAR ucBakflag ;    /* PPP init标记 */

    UCHAR ucCurrentMode;  /* 当前PPP接口模式, 0-正常模式,1-保活模式(保活模式下不收发报文) */
    UCHAR ucRestoreFlag;  /* 保活模式下,恢复成功失败标记, 0-恢复成功, 1-恢复失败 */
    UCHAR ucNpHandleLcpEcho; /* NP是否处理PPP LCP Echo, 0-VISP处理, 1-NP处理 */
    UCHAR ucPadding_3[3];
    
    ULONG ulNegTimeCnt;         /* 指定时间内协商不通过计数 */
    ULONG ulNcpResendTimerId;   /* NCP延时补发一个CR报文的定时器ID */
} PPPINFO_S;

/* PPP类型定义 */
typedef enum tagPPPTPYE
{
    PPPTYPE_PPP = 0, /*普通PPP*/
    PPPTYPE_PPPOE,
    PPPTYPE_PPPOEOA,
    PPPTYPE_PPPOA,

    PPPTYPE_MAX
}PPPTYPE_ENUM;

/* Multilink User链表节点 */
typedef struct tagPppMultilinkUser
{
    struct tagPppMultilinkUser *pNext;        /* 链表指针 */
    CHAR cUserName[PPP_MAXUSERNAMELEN + 2];   /* 用户名 */
    CHAR c_IntfName[200 + 2];                 /* virtual template接口名 */
} PPPMULTILINKUSER_S;


/* 状态机模块数据结构定义 */
typedef struct tagPppFsm
{
    CHAR *  pProtocolInfo;         /* 子协议控制块指针 */
    CHAR *  pPppInfo;              /* PPP控制块指针 */
    ULONG   ulTimeOutTime;         /* config request/terminate request报文的超时时间 */
    ULONG   ulTimeOutID;           /* config request报文的定时器 */
    ULONG   ulEchoTimeOutTime;     /* LCP Echo request报文的超时时间 */
    ULONG   ulEchoTimeoutID;       /* LCP Echo request报文的定时器 */

    ULONG   ulResetTimerId;        /* NCP reset定时器 */

    ULONG   ulIPCPResetTimerId;    /* IPCP 状态机reset定时器 add by h00177429 for ipcp sub-opt adapt 2012/2/7 */

    struct tagPppFsmCallbacks *pstCallBacks;  /* 回调函数集 */

    ULONG   ulNeedNego;            /*子协议是否需要协商 add by y36299 for SWFD05286 2005/06/22*/

    USHORT  usProtocol;            /* 子协议的PPP协议号 */
    SHORT   sRetransmits;          /* config request/terminate request报文重传次数 */
    USHORT  usNakloops;            /* Nak对方同一个选项的次数 */
    UCHAR   ucState;               /* 协议状态 */
    UCHAR   ucPktId;               /* 本协议当前报文的ID */
    UCHAR   ucEchoId;              /* LCP Echo request报文的ID */
    UCHAR   ucEchoTimes;           /* PPP echo探测次数 */
    USHORT  usDownReason;          /* 记录控制流(down或close事件)导致的PPP协议down原因 */
} PPPFSM_S;

typedef struct tagPppFsmCallbacks
{
    /* 动作：协商报文处理 */
    VOID  (*resetci)(PPPFSM_S *);   /* 根据配置信息设置协商初始值 */
    USHORT (*cilen)(PPPFSM_S *);    /* 我要发送的request报文长度 */

    VOID  (*addci)(PPPFSM_S *, UCHAR *);          /* 组织协商报文 */

    USHORT (*ackci)(PPPFSM_S *, UCHAR *, ULONG);  /* 处理对方的ack报文 */

    USHORT (*nakci)(PPPFSM_S *, UCHAR *, ULONG);  /* 处理对方的nak报文 */

    USHORT (*rejci)(PPPFSM_S *, UCHAR *, ULONG);  /* 处理对方的reject报文 */

    UCHAR (*reqci)(PPPFSM_S *, UCHAR *, ULONG *); /* 处理对方的request报文 */

    USHORT (*extcode)(PPPFSM_S *, UCHAR, UCHAR, UCHAR *, UCHAR *, ULONG); /* 处理协议特有的报文，如protocol reject等 */
                                  
    /* 事件：协议转入了终止状态 */
    VOID (*up)(PPPFSM_S *);         /* 协议up */

    ULONG (*upcheck)(PPPFSM_S *);   /* 协议up后对协商结果进行正确性检查  */     

    VOID (*down)(PPPFSM_S *);       /* 协议暂时down,马上要重新协商.
                                       与finished的区别是:对于PPPOE、DDR等的情况，
                                       不用通知下层拆除链路 */
    VOID (*finished)(PPPFSM_S *);   /* 协议结束，通知底层:拆除链路.对于LCP,只要不是
                                       PPPOE、DDR等的情况,则会设置reset定时器,
                                       超时后重新启动协商 */
    VOID (*starting)(PPPFSM_S *);   /* tls(This-Layer-Started)动作中，通知下层:我准
                                       备好了重新协商,如可能,请发一个up事件.
                                       协议对这个动作没有具体规定,可以不实现*/

    /* Add for DTS2011042101452, by z00166124, at 2011-04-21. 修改原因: 创建定时器时回调方式获取处理函数 */
    VOID (*timerout)(VOID *);       /* PPP各协议状态机FSM超时处理函数 */

    VOID (*ncpreset)(VOID *);       /* PPP各协议状态机报文重传超时处理函数 */

    /* 子协议信息 */
    CHAR proto_name[8];             /* 子协议名 */
} PPPFSMCALLBACK_S;


typedef struct tagMP_USER_INFO
{
    DLL_NODE_S stDLLNode;                 /* 双链表节点 */
    ULONG ulVirtualTemplateNum;           /* 对应虚模板号 */
    UCHAR ucUserName[MP_USERNAME_LEN + 2];/* 用户名 */
    UCHAR ucPadding[2]; 
    DLL_S *pulIfIndexList;
} MP_USER_INFO_S;/*用户名-虚模板对应表结构*/

typedef struct tagMPGROUP_LIST_INFO
{
    DLL_NODE_S stDLLNode;   /* 双链表节点 */
    UCHAR ucMpGroupName[IF_MAX_INTERFACE_NAME_LEN+1];/* 用户名 */
    DLL_S *pulSubLinkList;
} MPGROUP_LIST_INFO_S;

/**引入的模块id*******/
/* Modified by z43740 for A82D02377:删除PFC/ACFC/MC/PPPMUX预配置参数,2006/06/20 */
typedef struct tagPPP_ModInfo
{
    ULONG ulMID_PPP;
    ULONG ulMID_IFNET;
    ULONG ulMID_STAC;
    ULONG ulMID_STAC_HASH;
    ULONG ulMID_VJCOMP;
    
    ULONG ulSID_PPP_PACKET_S;
    ULONG ulSID_PPP_CB_S;
    ULONG ulSID_PPP_L2TPOPTION_S;
    ULONG ulSID_PPP_L2TPPARA_S;
    ULONG ulSID_PPP_BUILDRUN;
    ULONG ulSID_STAC_BUFFER_S;
    ULONG ulSID_STAC_HASHNODE_S;
    ULONG ulSID_STAC_MINLIST_S;
    ULONG ulSID_STAC_PACKET_S;
    ULONG ulSID_PPP_ASY_S;
    ULONG ulSID_PPP_SYN_S;
    ULONG ulSID_MBUF_S;
    
    ULONG ulQUE_PPP_ASY;
    ULONG ulQUE_IP_INPUT;
    ULONG ulQUE_IPV6_INPUT;
    ULONG ulQUE_MPLS_INPUT;
    ULONG ulQUE_IPX;
    ULONG ulQUE_ISIS_INPUT;
    ULONG ulQUE_PPP_STAC;
    ULONG ulQUE_PPP_MP;
    ULONG ulQUE_PPP_NEGO;
    ULONG ulQUE_PPPMUX_INPUT;

    /*预配置参数*/
    ULONG ulPPP_DEF_NEED_PAP;/* PPP链路是否需要PAP验证 */
    ULONG ulPPP_DEF_NEED_CHAP;/* PPP链路是否需要CHAP验证 */
    ULONG ulPPP_DEF_NEED_LOOPNEGO;/*第一次协商不成功以后，是否等待一定时间后继续循环协商*/
    ULONG ulPPP_DEF_NEGO_TIMEOUT;/* 一次协商超时时间 */
    ULONG ulPPP_DEFAULT_KEEPALIVE;/* 链路层协商和探测链路状态 */
    ULONG ulPPP_DEFMRU;/*协商时缺省MRU*/
    ULONG ulPPP_DEFAULT_ACCM;/*缺省同异步转换字符集，所有控制字都转换(0xffffffff) */
    ULONG ulPPP_DEF_NEED_NCP;/*配置缺省是否需要NCP协商*/
    ULONG ulPPP_DEF_NEED_LCP;/* Liqiang 实现智能光网络产品的需求---配置缺省是否需要LCP协商 2003-12-17 */
    ULONG ulPPP_DEF_NEED_OSICP; /*配置缺省是否需要OSICP协商*/
    ULONG ulPPP_DEF_CONFREQS;/*Config Request的重传次数*/
    ULONG ulPPP_DEF_MAX_CTLNUM;/*最大PPP控制块数目*/
    ULONG ulNeedAsyQue;/*是否需要创建异步报文队列*/
    ULONG ulTcpSpace;       /* TCP格式最大CID值 */
    ULONG ulNonTcpSpace;    /* 非TCP格式最大CID值 */
    ULONG ulRtpCompression; /* 协商(Enhanced) RTP Compression子选项协商设置 */
    ULONG ulCompressType;   /* 报文压缩类型设置*/
    ULONG ulIphcNpSwitch;   /* 是否支持NP的IPHC开关*/
    ULONG ulUnidirction;    /* 是否支持单向处理 */
    /* End of addition for IPHC,2005/09/19*/
    ULONG ulChapCheckUser;  /* Chap Client端是否校验用户名 */
    ULONG ulGlobalTimer;    /* Added by z43740 for for BC3D01909: 支持使用系统定时器,2009-08-16 */
    ULONG ulIphcSubOptAdapt;
}PPP_MOD_INFO_S;

/**************shell 向core注册的回调函数集************************************/
typedef ULONG (* PPP_QueDealPacketFunc)(MBUF_S *);                    /* 处理包的函数 */
typedef ULONG (* PPP_QueIsDropThisPacketFunc)(MBUF_S *,ULONG,CHAR*); /* 是否丢弃 */

typedef struct tagPPP_SHELL_CALLBACK_SET
{
    ULONG (*pfCLI_EnableCommand)( CHAR *  szCmdModeName, CHAR * szCmdKey );
    ULONG (*pfCLI_DisableCommand)( CHAR *  szCmdModeName, CHAR * szCmdKey );
    
    ULONG (*pfQue_AddQueLen)(ULONG ulQueID,ULONG ulLen);
    VOID (*pfQue_FreePacketInQueueForRequest)(ULONG ulQueID,ULONG ulCmd,CHAR* pData);
    ULONG (*pfQue_GetQueLen)(ULONG ulQueID);
    ULONG (*pfQue_SetQueLen)(ULONG ulQueID,ULONG ulMaxLen);

    ULONG (*pfQue_RegisterQue)(ULONG ulQueID, ULONG ulGetCntPerTimes, PPP_QueDealPacketFunc pfDealPkt, PPP_QueIsDropThisPacketFunc pfIsDropThisPkt, ULONG ulMaxLen);
    ULONG (*pfQue_ActiveQue)(ULONG ulQueID);
    ULONG (*pfQue_DeActiveQue)(ULONG ulQueID);
    ULONG (*pfQue_EnQueue)(MBUF_S* pMBuf);
    ULONG (*pfPPP_EnDropQue)(MBUF_S *pMBuf);
        
    ULONG (*pfPPP_NotifyIpcpDown)(ULONG ulIfIndex);
    ULONG (*pfPPP_BuildRun)(CHAR* szSectionName, CHAR** pszBuildRunInfo);
    
    VOID (*pfPPP_Shell_AuthRequest)(ULONG ulIfnetIndex, PPPAUTHMSG_S * pMsg);
    ULONG (*pfPPP_GetPeerIPAddress)(ULONG ulUserID, 
                                                                          ULONG ulIfnetIndex, 
                                                                                 PPP_GetPeerCallBack_PF pfGetPeerCallBack);
    VOID (*pfPPP_FreeAddr)(ULONG ulUserID, ULONG ulIfnetIndex, ULONG ulPeerIPAddress);
    ULONG (*pfPPP_Shel_Chap_GetUserPsw)(PPPAUTHMSG_S *pstMsg);

    VOID (*pfPPP_ShowDebugInfo)( CHAR *szString, ULONG ulLen );

}PPP_SHELL_CALLBACK_SET_S;

/********定时器相关结构定义如下************/
typedef struct tagPppChainNode
{
    LONG lPrev; /*前向索引*/
    LONG lNext; /*后向索引*/
}PPPCHAINNODE_S;

/*定时器回调函数指针*/
typedef void (* PppTimeoutCall)( VOID * );

typedef struct tagPppTimerNode
{
    PPPCHAINNODE_S  stNode;
    ULONG           stEndTimeHigh;
    ULONG           stEndTimeLow;
    ULONG           ulTimerId;
    VOID            *pArg;
    PppTimeoutCall  stCallBack;
}PPPTIMERNODE_S;


/*****************************VLINK相关结构定义***********************************/
typedef struct  tagPppIFConfig
{
    USHORT  usIfDelay;
    USHORT  usIfReliability;
    USHORT  usIfLoad;
    UCHAR   ucPadding[2]; 
    ULONG   ulIfBandwidth;
    ULONG   ulIfBaudrate;
    ULONG   ulIfMtu;
    /*add sunyu for bandwidth,delay command*/
    ULONG   ulConfIfDelay;
    ULONG   ulConfIfBandwidth;

    ULONG   ulData;
} PPPIFCONFIG_S;

typedef struct tagPppIfMsgentry
{
    ULONG  ulIntfIndex;             /*接口唯一索引值*/
    ULONG  ulVlinkIndex;            /*虚链路索引值，接口事件时置为0*/
    USHORT  usSlot;                 /*接口所在槽号， new in 3.0 */
    USHORT  usMsgType;              /*见下面定义*/
    USHORT  usIfState;              /*接口状态*/
    USHORT  usIfFlags;              /* 接口标志*/        
    CHAR    cIfName[IF_MAX_INTERFACE_NAME_LEN + 1];    /*接口名称*/
    USHORT  usIfType;                               /*接口类型*/
    UCHAR ucPadding_1[2]; 
    PPPIFCONFIG_S      stIfData;                    /*接口参数*/
    SOCKADDR_S  stPeerAddr;         /*对端地址，创建虚链路时必须有对端地址*/
    ULONG ulMacAddrLen;
    UCHAR ucMacAddr[IF_MAX_MAC_LEN + 1];
    UCHAR ucPadding_2;
    ULONG ulVrfIndex;

}PPPIFMSGENTRY_S;

typedef struct tagPppIfMsgentry PPP_VLINKSTATUS_S;


typedef ULONG (*PPP_NotifySubMod_FuncPtr)(IFNET_S *pstIf, ULONG ulCmd, CHAR *pPara);

typedef struct tagPPPSUBMODCALLBACK
{
    PPP_NotifySubMod_FuncPtr pfPPP_NotifyMp;
}PPP_SUBMOD_CALLBACK_S;


#ifdef __cplusplus
}
#endif

#endif /* end of _PPP_TYPE_H_ */

