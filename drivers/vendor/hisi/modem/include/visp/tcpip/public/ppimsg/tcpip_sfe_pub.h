/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_sfe_pub.h
*
*  Project Code: V1.1.0
*   Module Name: PUB
*  Date Created: 2009-8-21
*        Author: w60786
*   Description: 公共处理头文件
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-8-21    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _TCPIP_SFE_PUB_H_
#define _TCPIP_SFE_PUB_H_

#ifdef  __cplusplus
    extern "C"{
#endif

#ifndef SFE_OK
#define SFE_OK      0
#endif

#ifndef LEN_64
#define LEN_64   64
#endif

/* 数据面地址信息结构定义 */
typedef union unSFE_IPADDR
{
    UINT32 u32IPv4;       /* IPv4地址 */
    UINT32 u32IPv6[4];    /* IPv6地址 */
}SFE_IPADDR_UN;

/* 拷贝流规则信息,从控制面对外结构中拷贝到数据面配置结构中 */
#define TCPIP_SFE_FLOWSTAT_COPY_RULE_CTRLTOSFE(pstSfeFlowStatCfgRule, pstCtrlFlowStatCfgRule) \
{\
        (pstSfeFlowStatCfgRule)->u32FlowStatId = (pstCtrlFlowStatCfgRule)->u32FlowStatId;\
        (pstSfeFlowStatCfgRule)->u32VrfIndex = (pstCtrlFlowStatCfgRule)->u32VrfIndex;\
        (pstSfeFlowStatCfgRule)->unSrcIp.u32IPv4 = VOS_HTONL((pstCtrlFlowStatCfgRule)->unSrcIp.u32IPv4);\
        (pstSfeFlowStatCfgRule)->unDstIp.u32IPv4 = VOS_HTONL((pstCtrlFlowStatCfgRule)->unDstIp.u32IPv4);\
        (pstSfeFlowStatCfgRule)->u32ProNo = (pstCtrlFlowStatCfgRule)->u32ProNo;\
        (pstSfeFlowStatCfgRule)->u16SrcPort = VOS_HTONS((pstCtrlFlowStatCfgRule)->u16SrcPort);\
        (pstSfeFlowStatCfgRule)->u16DstPort = VOS_HTONS((pstCtrlFlowStatCfgRule)->u16DstPort);\
}

#ifdef  __cplusplus
}
#endif

#endif

