/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_pub.h
*
*  Project Code: VISPV100R006C02
*   Module Name:
*  Date Created: 2007-07-28
*        Author: zhanghuihui(55157)
*   Description: VISP 公共模块处理头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-28   zhanghuihui(55157)      Create
*  2007-09-19   y62007                  modify A82D20228
*******************************************************************************/
#ifndef _TCPIP_PUB_H_
#define _TCPIP_PUB_H_

#ifdef  __cplusplus
extern "C"{
#endif

#define LINK_INPUT  1  /*链路层注册钩子输入方向*/
#define LINK_OUTPUT 0  /*链路层注册钩子输出方向*/

#define MAX_LINK_MAXPKT    1024           /*用户设置N_Max值的上限*/
#define DEFAULT_LINKPKT_NUM    1          /*定义协议栈默认N值*/
#define DEFAULT_LINK_MAXPKT   128         /*协议栈默认N_Max值*/

#define DEFAULT_SOCK_SCHEDULE  256        /*SOCK任务默认事件、报文调度次数*/
#define MAX_SOCK_SCHEDULE      1024       /*SOCK任务最大事件、报文调度次数*/
#define DEFAULT_SOCK_DELAY     10         /*SOCK任务默认达到调度次数后延时*/
#define MAX_SOCK_DELAY         40         /*SOCK任务最大达到调度次数后延时*/
#define LINK_UPDOWN_STEP       4          /*链路up/down事件权重*/

#define CHARACTER_BACKSLASH     0x5c   /*表示字符'\'*/

#define MEM_IPv4_MAX_MID    128    /*模块内存统计中IPV4允许的最大模块ID对应的数组索引*/
#define MEM_MAX_MID         256    /*模块内存统计中允许的最大模块ID对应的数组索引*/

/* Add for DTS2011071902704, by zhaoyue00171897, at 2011-07-19. 修改原因:防止CPU占用率过高 */
#define  SOCK_POINT_MAX_RUN_TIME        800  /*SOCK 单次调度最大时间 ms*/
#define  SOCK_POINT_DEFAULT_RUN_TIME    40   /*SOCK 单次调度默认时间 ms*/
#define  SOCK_POINT_MAX_FREE_TIME       100  /*SOCK 单次释放最大时间 ms*/
#define  SOCK_POINT_DEFAULT_FREE_TIME   40   /*SOCK 单次释放默认时间 ms*/

/* 移动内存指针 */
#define MEM_INCPTR(n, cp)   ((cp) += (n))
#define MEM_DECPTR(n, cp)   ((cp) -= (n))

/*从内存中获取4字节值,并向前偏移4字节指针.
要求传入的指针首地址为4整数倍,以保证不存在四字节对齐等问题*/
#define MEM_GETLONG(l, cp) { \
    (l) = *((ULONG *)cp); \
    cp += sizeof(ULONG) ; \
}
/*向内存中设置4字节值,并向前偏移4字节指针.
要求传入的指针首地址为4整数倍,以保证不存在四字节对齐等问题*/
#define MEM_PUTLONG(l, cp) { \
    *((ULONG*)cp) = l; \
    cp += sizeof(ULONG); \
}

#define SOCKRUN_SCHED_NUM_MIN   32
#define SOCKRUN_SCHED_NUM_MAX   512

/*获取TICK的高低位结构*/
typedef struct tagTCPIP_CPUTICK
{
    ULONG  ulLowTick;
    ULONG  ulHighTick;
}TCPIP_CPUTICK_S;

 /*链路层注册钩子的链表结构*/
typedef struct tagLINK_HOOK_NODE
{
    ULONG                     ulPriority;
    TCPIP_LINK_HOOK_FUNC      pfLinkHookFunc;
    struct tagLINK_HOOK_NODE *pstNext;
}LINK_HOOK_NODE_S;

/* 系统时间结构 */
typedef struct tagTCPIP_TIME
{
    USHORT usYear;       /* 1970-... */
    UCHAR  ucMonth;      /* 1-12     */
    UCHAR  ucDate;       /* 1-31     */

    UCHAR  ucHour;       /* 0-23 */
    UCHAR  ucMinute;     /* 0-59 */
    UCHAR  ucSecond;     /* 0-59 */
    UCHAR  ucReseved;
}TCPIP_TIME_S;

/* 资源占用超过阈值并反复抖动时，进行维护时的哈希表数组大小 */
#define RESLIMIT_TIME_MAX       0xFFFFFFFF
#define RESLIMIT_TIME_MINUTE    60

#define RESLIMIT_RESTRAINTIME_MIN 0
#define RESLIMIT_RESTRAINTIME_MAX 60

/* 目前支持16种资源类型 */
#define RESLIMIT_MAXGROUP_SIZE  17

#define VISP_VRRP 1
#define EXTR_VRRP  2

/*Added for PTPV2, PTP 的组件编号*/
#define PTPCOMP_VERSION_NULL  0
#define PTPCOMP_VERSION_OLD  1 
#define PTPCOMP_VERSION_NEW  2

/* Added by qinyun62011, (Distribute socket)分布式socket裁剪, 2014/3/11 */
typedef struct tagTCPIP_DESTINFO
{
    UCHAR ucFamilyType;     /*协议类型:AF_INET/AF_INET6*/
    UCHAR ucRes[3];
    ULONG ulDestAddr[4];    /*目的地址，主机序
                            若目的地址为广播地址或全0地址，则返回本VRF域的一个有效地址和及接口即可*/
    ULONG ulVrfIndex;       /*VRF索引*/
}TCPIP_DESTINFO_S;
typedef struct tagTCPIP_GETSRCADDROUT
{
    ULONG ulSrcAddr[4];     /*源地址，主机序*/
    ULONG ulNexthop[4];     /*下一跳地址，主机序*/
    ULONG ulIfIndex;        /*出接口信息*/
}TCPIP_GETSRCADDROUT_S;
typedef ULONG (*TCPIP_GETSRCADDRHOOK_FUNC)(TCPIP_DESTINFO_S *pInfoIn,TCPIP_GETSRCADDROUT_S *pInfoOut);
typedef ULONG (*TCPIPGETMTU_HOOK_FUNC)( TCPIP_DESTINFO_S* pInfo,LONG *plMTU );

/* 资源占用超过阈值时需要记录日志，如果占用超过阈值的情况反复抖动，
则需要对日志记录情况进行抑制(在规定时间内只输出一条日志)，抑制操作是根据资源类型进行的 */
typedef enum tagResLimit_ResType
{
    RESTYPE_QUE_LINK_LAYER = QUE_LINK_LAYER,                 /* 链路层队列资源 */
    RESTYPE_QUE_ARP = QUE_ARP,                               /* ARP队列资源 */
    RESTYPE_QUE_PPP_NEGO = QUE_PPP_NEGO,                     /* PPP协商队列资源 */
    RESTYPE_QUE_PPP_ASY = QUE_PPP_ASY,                       /* PPP同步队列资源 */
    RESTYPE_QUE_PPP_STAC = QUE_PPP_STAC,                     /* PPP STAC队列资源 */
    RESTYPE_QUE_PPP_MP = QUE_PPP_MP,                         /* MP队列资源 */
    RESTYPE_QUE_IP_INPUT = QUE_IP_INPUT,                     /* IPv4队列资源 */
    RESTYPE_QUE_IPV6_INPUT = QUE_IPV6_INPUT,                 /* IPv6列资源 */
    RESTYPE_QUE_PPPOE_CLIENT_INPUT = QUE_PPPOE_CLIENT_INPUT, /* PPPoE Client队列资源 */
    RESTYPE_QUE_PPPMUX_INPUT = QUE_PPPMUX_INPUT,             /* PPPMUX队列资源 */
    RESTYPE_QUE_LACP = QUE_LACP,                             /* LACP报文队列资源 */
    RESTYPE_QUE_POES = QUE_POES,                             /* PPPoE Server报文队列资源 */
    RESTYPE_QUE_ISIS_INPUT = QUE_ISIS_INPUT,                 /* ISIS报文队列 */
    RESTYPE_QUE_INARP = QUE_INARP,                           /* INARP队列资源 */

    RESTYPE_MP_REORDER_WIN,                                  /* MP重组窗口资源 */

    RESTYPE_MAX                                              /* 资源类型最大值 */
}RESLIMIT_RESTYPE_E;

extern ULONG g_ulPingForbidFlag;

extern ULONG g_ulMemStat[MEM_MAX_MID];
extern ULONG g_ulSockScheduleTime;
extern ULONG g_ulSockScheduleSwitch;
extern ULONG g_ulSockRunTime;
extern ULONG g_ulSockScheduleDelay;

/*Add by q62011 for DTS2013011509185 大规格配置性能优化*/
extern ULONG g_ulCreateEthIfTimeTotal ;
extern ULONG g_ulCreateEthIfCount ;
extern ULONG g_ulCreateEthIfPPITimeTotal ;
extern ULONG g_ulCreateEthIfPhyIoTimeTotal ;
extern ULONG g_ulCreateLoopIfTimeTotal ;
extern ULONG g_ulCreateLoopIfCount ;
extern ULONG g_ulSubIfCreateTimeTotal ;
extern ULONG g_ulSubIfCreateCount ;
extern ULONG g_ulCreateLoopIfPPITimeTotal ;
extern ULONG g_ulSubIfNpTimeTotal ;
extern ULONG g_ulAddrPerfCfgTime ;
extern ULONG g_ulAddrPerfCfgCount ;
extern ULONG g_ulAddrPPIPerfTime;

typedef VOID (*BFD_IF_DEL_HOOK_FUNC)(ULONG);

extern VOID *TCPIP_MemMove(VOID *pVoidDes, const VOID *pVoidSrc, ULONG ulLen);
extern CHAR *TCPIP_GetMidInfo(ULONG ulMid);
extern VOID TCPIP_GetFileName(CHAR *pstFile, CHAR *pstFileName, ULONG ulstrMaxLen);
extern ULONG TCPIP_DealLinkHook(MBUF_S *pstMBuf, ULONG ulInputOrOutput);
extern ULONG TCPIP_GetCpuTickPerMs(ULONG *pulCPU_TICKS_PER_MS);
extern VOID TCPIP_MacToString(CHAR *szMac,CHAR *szString);
extern ULONG TCPIP_Get_CurrentTime(TCPIP_TIME_S *pstTime);
extern ULONG TCPIP_ResLimit_IsOverTime(ULONG ulResType, ULONG ulTimeHigh, ULONG ulTimeLow);
extern VOID TCPIP_ResLimitMaintain(ULONG ulIfIndex, ULONG ulResType, ULONG ulResLimitVal, ULONG ulCurrentVal);
extern VOID TCPIP_RecordMemErrInfo(ULONG ulType,  ULONG ulPara0, ULONG ulPara1, ULONG ulPara2, ULONG ulPara3);
extern ULONG TCPIP_VirtualIpAddrConflict(VOID *pfCompTbl, ULONG ulIfIndex, ULONG ulIpAddr);
extern ULONG TCPIP_CompareVirtualMac(VOID *pfCompTbl, VOID *pstIf, UCHAR *aucMacAddr);
extern ULONG TCPIP_GetVirtualMacByVip(VOID *pfCompTbl, ULONG ulIfIndex, ULONG ulIpAddr, UCHAR *aucMacAddr);
extern ULONG TCPIP_GetVirtualMacByIpAddr(VOID *pfCompTbl, ULONG ulIfIndex, ULONG ulIpAddr, UCHAR *aucMacAddr);
extern ULONG TCPIP_IsVipInVrf(ULONG ulVrfIndex, ULONG ulIpAddr);
extern ULONG TCPIP_ISVirtualMacToFillEthSourcMac(VOID *pfCompTbl, MBUF_S *pstMbuf);

extern ULONG TCPIP_GetMemInfo(ULONG ulInfo);
/*Add by q62011 for DTS2013011509185 大规格配置性能优化*/
extern VOID TCPIP_AddrSpecoOptimizeFlag(VOID);
extern VOID TCPIP_ShowPerfInfo(VOID);
extern VOID TCPIP_ClearPerfInfo(ULONG ulFlag);
/* Begin DTS2011010503133 liangjicheng 2010-08-12 RIP的接口创建OSPF一致 */
/*如下宏用于删除VRF的I3同步*/
#define I3_SYN_WAITING  0xAAAA
#define I3_SYN_FINISHED 0xEEEE
#define I3_SYN_INTERVAL 10
/*Add by q62011 for DTS2013011509185 大规格配置性能优化*/
#define I3_CFG_SEM_MAX_WAIT_TIME 20000
#define I3_SYN_TRY_TIMES 500
extern VOID I3_WaitI3Syn(VOID);

extern gpfTCPIPUserStop         g_pfTCPIPUserStop;      /* 用户操作停止命令钩子 */
extern gpfTCPIPTrrtUserStopEx       g_pfTCPIPTrrtUserStopEx;
extern gpfTCPIPPingUserStopEx       g_pfTCPIPPingUserStopEx;

extern CreateMutex_HOOK_FUNC    g_pfTCPIPCreateMutex;   /* 创建信号量钩子 */
extern CreateSm_HOOK_FUNC       g_pfTCPIPCreateSm;      /* 创建信号量钩子 */
extern SmP_HOOK_FUNC            g_pfTCPIPSmP;           /* 获取信号量钩子 */
extern SmV_HOOK_FUNC            g_pfTCPIPSmV;           /* 释放信号量钩子 */
extern DeleteMutex_HOOK_FUNC    g_pfTCPIPDeleteMutex;   /* 删除信号量钩子 */

extern LINK_HOOK_NODE_S      *g_pstLinkInputHook;    /*链路层注册钩子接收方向链表头结点*/
extern LINK_HOOK_NODE_S      *g_pstLinkOutputHook;   /*链路层注册钩子发送方向链表头结点*/

extern gpfGetSockMaxNum g_pfGetSockMaxNum;
/*Added by yanlei00216869, 使以.so方式提供给bluestar的visp，不依赖产品代码, 2014/11/26   问题单号:DTS2014112500391 */
extern gpfRegAllAppInfo g_pfRegAllAppInfo;
/* End of Added by yanlei00216869, 2014/11/26   问题单号:DTS2014112500391 */
extern BFD_IF_DEL_HOOK_FUNC g_pfBfdIfDeleteNotify;

extern TCPIP_VirtualIpAddrConflict_HOOKFUNC g_pfVirtualIpAddrConflict;
extern TCPIP_CompareVirtualMac_HOOKFUNC     g_pfCompareVirtualMac;
extern TCPIP_IsVipInIf_HOOKFUNC             g_pfIsVipInIf;
extern TCPIP_GetVirtualMacByIpAddr_HOOKFUNC g_pfGetVirtualMacByIpAddr;

/* 获取隧道MTU */
extern gpfTCPIP_GetTunnelMtu_HOOK_FUNC g_pfGetTunnelMtu_HOOK_FUNC;

extern TCPIP_IsNeedWarning_HOOK_FUNC        g_pfIsNeedWarning;


/* Add for DTS2011031702777, by zhukun00166124, at 2011-03-21. 修改原因: VRRP获取用户配置的BFD规格，保证模块独立性 */
extern ULONG (*g_pfVrrpGetBfdMaxSessID)(VOID);

/*LLDP模块Trunk报文收发钩子*/
typedef ULONG     (*gpfTrunkLLDPRcvPkt_HOOK_FUN)(MBUF_S * pMBuf);
extern ULONG  g_ulTaskMonitorMaxtime;
extern TCPIP_TASK_MONITOR_PARA_S g_stTaskMoniterPara;

typedef ULONG  (*pfBfdMonitorHOOK_Func)(VOID); /*定义线程监视BFD 钩子类型*/

typedef ULONG  (*pfTWAMPMonitorHOOK_Func)(VOID); /*TWAMP Monitor Hook function*/

/* Added by qinyun62011, (Distribute socket)分布式socket裁剪, 2014/3/11 */
extern TCPIP_GETSRCADDRHOOK_FUNC g_pfGetSrcAddrHookFunc;
extern TCPIPGETMTU_HOOK_FUNC g_pfGetMtu_HookFunc;
ULONG TCPIP_RegFuncGetSrcAddrHook( TCPIP_GETSRCADDRHOOK_FUNC pfFuncHook );
ULONG TCPIP_RegFuncGetMtuHook( TCPIPGETMTU_HOOK_FUNC pfFuncHook );

extern ULONG g_ulNeedShutIFForVRFChange;
extern ULONG g_ulTcpTimerFlag;
#ifdef  __cplusplus
}
#endif
#endif /* _PUBLIC_PUBLIC_H_ */


