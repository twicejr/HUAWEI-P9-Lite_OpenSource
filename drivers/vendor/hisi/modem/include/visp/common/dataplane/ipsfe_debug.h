/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipsfe_debug.h
*
*  Project Code: V1.1.0
*   Module Name: 维测
*  Date Created: 2009-9-2
*        Author: w60786
*   Description: 维测模块数据面和控制面共用的结构,宏等定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-9-2     w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _IPSFE_DEBUG_H_
#define _IPSFE_DEBUG_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* 数据面自动统计项所需空间大小 */
#define SFE_STATISTIC_AUTOSTAT_SIZE     (SFE_STAT_IPFWD_MAX * sizeof(UINT32))

/* 对应的流统计项未被使用,表示该项无流统计规则 */
#define  SFE_FLOWSTAT_IS_NOTUSED    0
/* 对应的流统计项已被使用,表示该项有流统计规则 */
#define  SFE_FLOWSTAT_IS_USED       1

/* TCP协议号 */
#define SFE_FLOWSTAT_IPPROTO_TCP    6 
/* UDP协议号 */
#define SFE_FLOWSTAT_IPPROTO_UDP    17 

/* 配置流统计规则时传入参数为NULL */
#define SFE_FLOWSTAT_CFGRULE_IS_NULL  1
/* 配置流统计规则时传入参数不为NULL */
#define SFE_FLOWSTAT_CFGRULE_IS_NOT_NULL  0

/* 判断是否是五元组加VRF规则 */
#define SFE_FLOWSTAT_IS_6KEY_FLOW(u32ProtocalNo) \
    ((SFE_FLOWSTAT_IPPROTO_UDP ==  (u32ProtocalNo)) || (SFE_FLOWSTAT_IPPROTO_TCP == (u32ProtocalNo)))

/* 累加各VCPU的手动统计信息 */
#define SFE_STAT_SUM_VCPU_MANUALSTAT(pstSumSfeManualStat, pstTempSfeVcpuManualStat) \
{\
    (pstSumSfeManualStat)->dwLink_In += (pstTempSfeVcpuManualStat)->dwLink_In;\
    (pstSumSfeManualStat)->dwEth_In += (pstTempSfeVcpuManualStat)->dwEth_In;\
    (pstSumSfeManualStat)->dwNet_In += (pstTempSfeVcpuManualStat)->dwNet_In;\
    (pstSumSfeManualStat)->dwIcmp_Out += (pstTempSfeVcpuManualStat)->dwIcmp_Out;\
    \
    (pstSumSfeManualStat)->dwArp_Deliver += (pstTempSfeVcpuManualStat)->dwArp_Deliver;\
    (pstSumSfeManualStat)->dwIpOpt_Deliver += (pstTempSfeVcpuManualStat)->dwIpOpt_Deliver;\
    (pstSumSfeManualStat)->dwIpBroadcast_Deliver += (pstTempSfeVcpuManualStat)->dwIpBroadcast_Deliver;\
    (pstSumSfeManualStat)->dwIpMulticast_Deliver += (pstTempSfeVcpuManualStat)->dwIpMulticast_Deliver;\
    (pstSumSfeManualStat)->dwNonFrag_Deliver += (pstTempSfeVcpuManualStat)->dwNonFrag_Deliver;\
    (pstSumSfeManualStat)->dwFragHaveFakeReassed_Deliver += (pstTempSfeVcpuManualStat)->dwFragHaveFakeReassed_Deliver;\
    (pstSumSfeManualStat)->dwOspf_Deliver += (pstTempSfeVcpuManualStat)->dwOspf_Deliver;\
    (pstSumSfeManualStat)->dwUpToCtrlPlane += (pstTempSfeVcpuManualStat)->dwUpToCtrlPlane;\
    \
    (pstSumSfeManualStat)->dwFakeReass_NetSuccess += (pstTempSfeVcpuManualStat)->dwFakeReass_NetSuccess;\
    (pstSumSfeManualStat)->dwFakeReass_LinkSuccess += (pstTempSfeVcpuManualStat)->dwFakeReass_LinkSuccess;\
    \
    (pstSumSfeManualStat)->dwFakeReass_InFragNum += (pstTempSfeVcpuManualStat)->dwFakeReass_InFragNum;\
    (pstSumSfeManualStat)->dwFakeReass_OutFragNum += (pstTempSfeVcpuManualStat)->dwFakeReass_OutFragNum;\
    (pstSumSfeManualStat)->dwReass_InFragNum += (pstTempSfeVcpuManualStat)->dwReass_InFragNum;\
    (pstSumSfeManualStat)->dwReass_OutReassPktNum += (pstTempSfeVcpuManualStat)->dwReass_OutReassPktNum;\
    \
    (pstSumSfeManualStat)->dwNet_Out += (pstTempSfeVcpuManualStat)->dwNet_Out;\
    (pstSumSfeManualStat)->dwEth_Out += (pstTempSfeVcpuManualStat)->dwEth_Out;\
    \
    (pstSumSfeManualStat)->dwFrag_InNum += (pstTempSfeVcpuManualStat)->dwFrag_InNum;\
    (pstSumSfeManualStat)->dwFrag_OutNum += (pstTempSfeVcpuManualStat)->dwFrag_OutNum;\
    \
    (pstSumSfeManualStat)->dwFakeRease_resv += (pstTempSfeVcpuManualStat)->dwFakeRease_resv;\
    (pstSumSfeManualStat)->dwArpMiss_Resv += (pstTempSfeVcpuManualStat)->dwArpMiss_Resv;\
    \
    (pstSumSfeManualStat)->dwArp_ArpSearchIn += (pstTempSfeVcpuManualStat)->dwArp_ArpSearchIn;\
    (pstSumSfeManualStat)->dwArp_HaveNormalArp += (pstTempSfeVcpuManualStat)->dwArp_HaveNormalArp;\
    (pstSumSfeManualStat)->dwArp_HaveFakeArp += (pstTempSfeVcpuManualStat)->dwArp_HaveFakeArp;\
    (pstSumSfeManualStat)->dwArp_NoArp += (pstTempSfeVcpuManualStat)->dwArp_NoArp;\
    (pstSumSfeManualStat)->dwArp_ReNotifyArpMissSuccess += (pstTempSfeVcpuManualStat)->dwArp_ReNotifyArpMissSuccess;\
    (pstSumSfeManualStat)->dwArp_SendCachePktSuccess += (pstTempSfeVcpuManualStat)->dwArp_SendCachePktSuccess;\
    \
    (pstSumSfeManualStat)->dwIcmp_RecvErrIcmpPkt += (pstTempSfeVcpuManualStat)->dwIcmp_RecvErrIcmpPkt;\
    (pstSumSfeManualStat)->dwIcmp_RecvNoFirstFrg += (pstTempSfeVcpuManualStat)->dwIcmp_RecvNoFirstFrg;\
    (pstSumSfeManualStat)->dwIcmp_RecvBroadOrMultiPkt += (pstTempSfeVcpuManualStat)->dwIcmp_RecvBroadOrMultiPkt;\
    (pstSumSfeManualStat)->dwIcmp_RecvSrcIpErr += (pstTempSfeVcpuManualStat)->dwIcmp_RecvSrcIpErr;\
    (pstSumSfeManualStat)->dwIcmp_SendUnreachHostNum += (pstTempSfeVcpuManualStat)->dwIcmp_SendUnreachHostNum;\
    (pstSumSfeManualStat)->dwIcmp_SendNeedFragNum += (pstTempSfeVcpuManualStat)->dwIcmp_SendNeedFragNum;\
    (pstSumSfeManualStat)->dwIcmp_SendTimeExceededNum += (pstTempSfeVcpuManualStat)->dwIcmp_SendTimeExceededNum;\
    \
    (pstSumSfeManualStat)->dwBfd_In += (pstTempSfeVcpuManualStat)->dwBfd_In;\
    (pstSumSfeManualStat)->dwBfd_ToCtrlSessIdZero += (pstTempSfeVcpuManualStat)->dwBfd_ToCtrlSessIdZero;\
    (pstSumSfeManualStat)->dwBfd_ToCtrlSessNotUp += (pstTempSfeVcpuManualStat)->dwBfd_ToCtrlSessNotUp;\
    (pstSumSfeManualStat)->dwBfd_ToCtrlPktStateNotUp += (pstTempSfeVcpuManualStat)->dwBfd_ToCtrlPktStateNotUp;\
    (pstSumSfeManualStat)->dwBfd_ToCtrlPktPollFlagSet += (pstTempSfeVcpuManualStat)->dwBfd_ToCtrlPktPollFlagSet;\
    (pstSumSfeManualStat)->dwBfd_ToCtrlPktFinalFlagSet += (pstTempSfeVcpuManualStat)->dwBfd_ToCtrlPktFinalFlagSet;\
    (pstSumSfeManualStat)->dwBfd_ToOwnDetectPkt += (pstTempSfeVcpuManualStat)->dwBfd_ToOwnDetectPkt;\
    (pstSumSfeManualStat)->dwBfd_DetectUp += (pstTempSfeVcpuManualStat)->dwBfd_DetectUp;\
    (pstSumSfeManualStat)->dwBfd_DetectDownNotifyOk += (pstTempSfeVcpuManualStat)->dwBfd_DetectDownNotifyOk;\
    (pstSumSfeManualStat)->dwBfd_EncapsualeLinkHeader += (pstTempSfeVcpuManualStat)->dwBfd_EncapsualeLinkHeader;\
    (pstSumSfeManualStat)->dwBfd_SendPktOk += (pstTempSfeVcpuManualStat)->dwBfd_SendPktOk;\
    \
    (pstSumSfeManualStat)->dwFwd_HaveHandle += (pstTempSfeVcpuManualStat)->dwFwd_HaveHandle;\
    (pstSumSfeManualStat)->dwFwd_NotHandle += (pstTempSfeVcpuManualStat)->dwFwd_NotHandle;\
    (pstSumSfeManualStat)->dwFwd_Drop += (pstTempSfeVcpuManualStat)->dwFwd_Drop;\
    \
    (pstSumSfeManualStat)->dwAcl_Forward_NotHandle += (pstTempSfeVcpuManualStat)->dwAcl_Forward_NotHandle;\
    (pstSumSfeManualStat)->dwAcl_Forward_Drop += (pstTempSfeVcpuManualStat)->dwAcl_Forward_Drop;\
    \
    (pstSumSfeManualStat)->dwAcl_UpDeliver_NotHandle +=(pstTempSfeVcpuManualStat)->dwAcl_UpDeliver_NotHandle;\
    (pstSumSfeManualStat)->dwAcl_UpDeliver_Drop += (pstTempSfeVcpuManualStat)->dwAcl_UpDeliver_Drop;\
}
    

/* 流统计规则结构定义,流统计规则的配置要求用户在删除一条流规则后必须间隔一定时间(一个报文在协议栈可能停留的最大时间,
   例如6s,)之后才重新添加流规则,否则可能存在多核操作引起的问题,统计值可能不准确 */
typedef struct  tagSFE_FlowStatisticRule
{
    UINT32         u32FlowStatId;        /* 流统计ID,添加时作为输出参数,删除时忽略该值,填0即可,获取时表示流统计ID,从0开始编号 */
    UINT32         u32VrfIndex;          /* VRF索引,主机序 */
    SFE_IPADDR_UN  unSrcIp;              /* 源IP,网络序 */
    SFE_IPADDR_UN  unDstIp;              /* 目的IP,网络序 */
    UINT32         u32ProNo;             /* 协议号,取值范围[0,255] */
    UINT16         u16SrcPort;           /* 源端口号,网络序,只在协议为UDP和TCP时有效,其它协议号时无效用户直接填0即可 */
    UINT16         u16DstPort;           /* 目的端口号,网络序,只在协议为UDP和TCP时有效,其它协议号时无效用户直接填0即可 */
}SFE_FLOWSTATISTIC_RULE_S;

/* 流统计规则配置信息结构 */
typedef struct tagSFE_FlowStatisticRuleCfgInfo
{
    UINT32   u32OperType;                           /* 流统计规则配置操作类型 */
    UINT32   u32IsFlowRulePointerNull;              /* 流统计规则参数指针是否为NULL */
    SFE_FLOWSTATISTIC_RULE_S stFlowStatisticRule;   /* 流统计规则参数 */
}SFE_FLOWSTATISTIC_RULE_CFG_INFO_S;

/* 流统计信息结构定义,定义为结构体是为了便于以后扩展其它字段 */
typedef struct tagSFE_FlowStatisticInfo
{
    UINT32  u32FlowStatNum;               /* 当前流统计个数 */
    UINT32  u32FlowStatSwitch;            /* 流统计开关 */
}SFE_FLOW_STATISTIC_INFO_S;

/* 流统计规则结构定义,流统计规则的配置要求用户在删除一条流规则后必须间隔一定时间(一个报文在协议栈可能停留的最大时间,
   例如6s,)之后才重新添加流规则,否则可能存在多核操作引起的问题,统计值可能不准确 */
typedef struct  tagSFE_FlowStatisticRuleInfo
{
    UINT32         u32IsUsed;            /* 该流统计项是否存在,是否被使用 */
    UINT32         u32FlowStatId;        /* 流统计ID,主机序,配置时忽略该值,填0即可,获取时表示流统计ID,从0开始编号 */
    UINT32         u32VrfIndex;          /* VRF索引,主机序 */
    UINT32         u32Reserved;          /* 填充4字节保证在64位上8字节对齐 */
    SFE_IPADDR_UN  unSrcIp;              /* 源IP,网路序 */
    SFE_IPADDR_UN  unDstIp;              /* 目的IP,网路序 */
    UINT32         u32ProNo;             /* 协议号 */
    UINT16         u16SrcPort;           /* 源端口号,网路序 */
    UINT16         u16DstPort;           /* 目的端口号,网路序 */
}SFE_FLOW_STATISTIC_RULE_INFO_S;

/* 流统计所有相关信息结构 */
typedef struct tagSFE_FLOWSTATISTIC_ALLINFO
{
    UINT32                           u32SfeFlowStatMaxNum;      /* 流统计最大流规格个数 */
    UINT32                           u32Reserved;               /* 填充4字节保证在64位上8字节对齐 */
    SFE_FLOW_STATISTIC_INFO_S       *pstSfeFlowStatInfo;        /* 流统计公共信息指针 */
    SFE_FLOW_STATISTIC_RULE_INFO_S  *pstSfeFlowStatRule;        /* 流统计规则信息指针 */
    SFE_IPSFE_FLOWSTATISTIC_S       *pstSfeFlowStatManualInfo;  /* 流统计手动统计信息指针 */
    UINT32                          *pu32SfeFlowStatAutolInfo;  /* 流统计自动统计信息指针 */
}SFE_FLOWSTATISTIC_ALLINFO_S;

/* 统计所有相关信息结构 */
typedef struct tagSFE_STATISTIC_ALLINFO
{
    SFE_IPSFE_STATISTIC_S           *pstSfeStatManualInfo;      /* 全局统计手动统计信息指针 */
    UINT32                          *pu32SfeStatAutolInfo;      /* 全局统计自动统计信息指针 */
}SFE_STATISTIC_ALLINFO_S;

/* 设置日志类型开关对应的数据结构 */
typedef struct tagSFE_LOG_TYPESWITCH
{
    UINT32    ul32WarningLogEnable;     /* 告警日志记录开关 */
    UINT32    u32CfgLogEnable;          /* 配置日志记录开关 */
    UINT32    u32RunLogEnable;          /* 运行日志记录开关 */
    UINT32    u32Reserved;              /* 填充4字节保证在64位上8字节对齐 */
}SFE_LOG_TYPESWITCH_S;

/* 获取调试开关对应的数据结构 */
typedef struct tagSFE_DEBUGSWITCH
{
    UINT32    u32DebugTypeSwitch;       /* 调试类型开关 */
    UINT32    u32DebugVcpuSwitch;       /* VCPU调试开关 */
    UINT32    u32DebugModuleSwitch;     /* 模块调试开关 */
    UINT32    u32Reserved;              /* 填充4字节保证在64位上8字节对齐 */
}SFE_DEBUGSWITCH_S;

/* 详细调试时，指定报文次数及报文长度 */
typedef struct tagSFE_VERBOSEDEBUG
{
    UINT32 u32PktNum;                   /* 报文次数 */
    UINT32 u32Length;                   /* 报文长度 */
}SFE_VERBOSEDEBUG_S;

/* 消息调试 */
#define TCPIP_SFE_MSG_DEBUG     0      
/* 事件调试 */
#define TCPIP_SFE_EVENT_DEBUG   1        

/* 接收方向 */
#define TCPIP_SFE_INPUT     0  
/* 发送方向 */
#define TCPIP_SFE_OUTPUT    1            

#ifdef  __cplusplus
}
#endif

#endif

