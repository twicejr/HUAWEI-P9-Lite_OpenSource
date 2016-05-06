/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_cfg.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-06-18
*        Author: chenshuanglong(28510)
*   Description: PP4_cfg.C头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2002-06-18   chenshuanglong(28510)   Create
*  2006-11-01   zhoutong(43740)         规范性整改
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _PP4_CFG_H_
#define _PP4_CFG_H_


/***************************************************************
 *        定义调试信息开关                                     *
 ***************************************************************/
#define IP_DEBUG_ON                 0x0001
#define IP_DEBUG_OFF                0x0000


#define IP_NO_ACL                   0

/* IP统计信息显示类别 */
#define IP_SHOW_TRAFFIC_ALL         0
#define IP_SHOW_TRAFFIC_MAIN        1
#define IP_SHOW_TRAFFIC_IO          2

/* 清除统计信息类别 */
#define IP_CLEAR_COUNTERS_ALL       0
#define IP_CLEAR_COUNTERS_MAIN      1
#define IP_CLEAR_COUNTERS_IO        2
#define IP_CLEAR_COUNTERS_INTERFACE 3    /* 同步D21代码  x36530  2004-9-16  */

extern ULONG ulDebugIpPacketFlag;   /* IP报文开关 */
extern ULONG ulDebugIpPacketErrFlag;/* IP报文错误信息开关 */
extern ULONG ulDebugIpDebugInfo;    /* IP报文调试信息开关 */

extern ULONG g_ulDubugIpAcl;       /* 标准ACL规则组号，用于过滤调试信息 */
extern ULONG g_ulDubugIpIfAcl;     /* 基于接口的ACL规则组号，用于过滤调试信息 */
extern ULONG g_ulDebugIpIfOpt;     /* 基于接口的ACL规则过滤方向，暂不实现in|out interface, 留待以后扩展 */

extern UCHAR g_ucbIpSendRedirects; /* 发送重定向报文开关 */
extern UCHAR g_ucbIpForwarding;    /* IP报文转发开关 */
extern LONG  nIpDefTTL ;           /* 默认TTL */

extern ULONG g_ulIpDebugFilter[IP_DEBUG_FILTER_MAX];

extern ULONG IP_PP4_GetStatics(IPSTAT_S* pstIpStat);
extern VOID IP_PP4_ClearIpCounters( ULONG  ulSlotNumber );

extern ULONG IP_PP4_GetDebugFlag(ULONG *pulDebugFlag,
                                 ULONG *pulDebugIpAcl,
                                 ULONG *pulDebugIpIfAcl,
                                 ULONG *pulDebugIpIfOpt,
                                 ULONG *pulDebugIpErr,
                                 ULONG *ulDebugPacketVerbose);
/* syn D038 by x36530 20050715*/
extern ULONG IP_PP4_SetDebugFlag(ULONG ulIpDebugNo, 
                                 ULONG ulDebugAcl,
                                 ULONG ulDebugIfAcl,
                                 ULONG ulDebugIfOpt, 
                                 ULONG ulDebugIpErr, 
                                 ULONG ulDebugPacketVerbose);

ULONG IP_PP4_SetForwardFlag(ULONG ulFlag);
ULONG IP_PP4_GetForwardFlag();
ULONG IP_PP4_SetDefaultTTL(ULONG ulTtl);
ULONG IP_PP4_GetDefaultTTL();
ULONG IP_PP4_GetInterfaceStatics(ULONG ulIfIndex, IPIFSTAT_S * pIpif_stData);
ULONG IP_PP4_ClearInterfaceStatics(ULONG ulIfIndex);

VOID IP_PP4_ClearIpInterface( IPIFNET_S *  pstIpIf);
ULONG IP_ICMP_RedirectsFunc(IFNET_S * pIf, ULONG ulFlag);
ULONG IP_ICMP_HostUnreachFunc(IFNET_S * pIf, ULONG ulFlag);
/*路由变化清空缓存接口*/
extern ULONG IP_ClearRouteCache(VOID);
extern ULONG IP_SetIpDebugFilter(ULONG ulSetYes, ULONG ulIfIndex, CHAR *szSrcIp, CHAR *szDstIp,
    ULONG ulProtocol, ULONG ulSrcPort, ULONG ulDstPort);
extern ULONG IP_GetIpDebugFilter(ULONG *pulDebugFlag, ULONG *pulDebugFilter);
/* Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */
extern ULONG IP_PP4_GetInterfaceStaticsByIfNum(IPIFSTAT_LIST_S *pIpif_stData, ULONG ulIfNum);
/* End of Add by heyijun 00218462 for DTS2012092803600 维测需求开发, 2012-9 */

#endif  /* _PP4_CFG_H_  */

#ifdef  __cplusplus
}
#endif


