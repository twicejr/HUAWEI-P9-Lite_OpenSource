/******************************************************************************

                    版权所有 (C), 2001-2011, 华为技术有限公司

*******************************************************************************

  文    件  名     : ppp_shel.c
  版    本  号     : VRP3.0
  作             者     : Deng Yi Ou
  生成日期     : 2000-04-04
  最近修改     :
  功能描述     : PPP的外壳(shell)模块
  函数列表     :

*
*       1.                GGSN_PathProcess
*       2.                GTPC_ASNSwitchChange
*       3.                GTPC_BatchDeletePdpContextByPath
*       4.                GTPC_BatchDelTaskByPath
*       5.                GTPC_CalculateHashValue
*       6.                GTPC_CMNotifyVolumetoAM
*       7.                GTPC_CompareSgsnRecovery
*       8.                GTPC_CreatDeletePdpTaskByPath
*       9.                GTPC_CreateNode
*       10.                GTPC_CreatePath
*       11.                GTPC_DeactiveConSgsnRestart
*

  修改历史     :
  1.日    期   : 2010-05-13
    作    者   : c00127007
    修改内容   : 删除多余代码、代码美化、增加函数注释、增加打印打点等。
******************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"
#include "pppc_ctrl.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_SHEL_C

/* PPPC的数据队列统计信息结构体 */
extern PPP_DATA_Q_STAT_STRU             g_stPppcDataQueueStats;

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : PPP_USMStartVsncp
 功能描述  : USM通知PPP开始VSNCP请求处理
 输入参数  : PPP_A11MSG_S *pstA11Msg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : wangyong 00138171
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_USMStartVsncp(UCHAR *pucVsncpMsg, VOS_UINT32 ulRpIndex)
{
    VOS_UINT32 ulLen = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_774);
        PPPC_INFO_LOG1(
                     "\r\n PPP_USMStartVsncp: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    ulLen = *((VOS_UINT32 *)pucVsncpMsg);
    pHead = pucVsncpMsg + sizeof(VOS_UINT32);
    pPacket = pucVsncpMsg + sizeof(VOS_UINT32) + PPP_RESERVED_PACKET_HEADER;

    PPP_VSNCP_PactketProc(pstPppInfo, pHead, pPacket, ulLen, CONFREQ);
    PPP_DBG_OK_CNT(PPP_PHOK_1472);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_USMNotifyRelease
 功能描述  : USM通知PPP删除资源，不需要发送LCP
 输入参数  : PPP_A11MSG_S *pstA11Msg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : wangyong 00138171
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_USMNotifyRelease(PPP_A11MSG_S *pstA11Msg)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, pstA11Msg->ulRPIndex);

    PPP_DBG_OK_CNT(PPP_PHOK_1292);
    if (VOS_NULL_PTR != pstPppInfo)
    {
        pstPppInfo->bFailFlag = PPPA11DOWNNOLCPTER;
    }

    (VOID)PPP_Shell_ISLIoCtl(pstA11Msg->ulRPIndex, PPP_ISLDOWN, (CHAR *)&pstA11Msg->ulL2tpType);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPP_IpcpTimeOutProcForPdn
 功能描述  : pdn ipcp定时器超时，调用该函数
 输入参数  : VOS_UINT32 ulRpIndex
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_IpcpTimeOutProcForPdn(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_567);
        return;
    }

    A11_ReqNumSubProc(pstPppInfo);

    SNMP_SetFailReason(pstPppInfo, FSM_ALARM_IPCP_MS_NO_RSP);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_UpdatePcfInfo
 功能描述  : ppp刷新pcfip和pcfindex，提供给a11调用
 输入参数  : VOS_UINT32 ulRpIndex
             VOS_UINT32 ulPcfIp
             VOS_UINT16 usPcfIndex
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月18日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_UpdatePcfInfo(VOS_UINT32 ulRpIndex, VOS_UINT32 ulPcfIp, VOS_UINT16 usPcfIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_568);
        PPPC_INFO_LOG1("\r\n PPP_UpdatePcfInfo: User %d isn't exist!", ulRpIndex);
        return;
    }

    pstPppInfo->ulPcfIP = ulPcfIp;
    pstPppInfo->usPcfIndex = usPcfIndex;
    PPP_DBG_OK_CNT(PPP_PHOK_1293);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_StartIPV4CP
 功能描述  :
             如果没有PPP控制块，返回失败
             如果有PPP控制块，没有IPCP控制块，就要判断是否在重协商，是则保存地址，否则返回失败
             如果有IPCP控制块，则保存地址，进行IPCP协商
             取出控制块中缓存消息，发送IPCP Request 消息，然后再收到缓存中的IPCP Request 消息

 输入参数  : VOS_UINT32 ulRpIdx
             VOS_UINT32 ulIpAddr
             VOS_UINT32 ulPriDns
             VOS_UINT32 ulSecDns
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_StartIPV4CP(VOS_UINT32 ulRpIdx, VOS_UINT32 ulIpAddr, VOS_UINT32 ulPriDns, VOS_UINT32 ulSecDns)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    VOS_UINT32 ulMsgLen = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIdx);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_569);
        PPPC_INFO_LOG1("\r\n PPP_StartIPV4CP: User %d isn't exist!", ulRpIdx);
        return VOS_ERR;
    }

    if (0 != pstPppInfo->ulPeerIPAddr)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_570);
        PPPC_INFO_LOG("\r\n PPP_StartIPV4CP: User IP is exist!");
        return VOS_ERR;
    }

    /* 保存地址*/
    pstPppInfo->ulPeerIPAddr = ulIpAddr;
    pstPppInfo->ulDNSAddr1 = ulPriDns;
    pstPppInfo->ulDNSAddr2 = ulSecDns;
    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV4;

    /* 重协商，直接保存地址 此处重协商标记控制不住 使用协商阶段控制 */
    if ((VOS_UINT16)PPP_PHASE_NETWORK != pstPppInfo->usPhase)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1294);
        PPPC_WARNING_LOG("\r\n PPP_StartIPV4CP: Renego!");
        return VOS_OK;
    }

    /* 没控制块 */
    if (VOS_NULL_PTR == pstPppInfo->pstIpcpInfo)
    {
        /* 否则创建控制块，主动协商 */
        PPP_GETIPCPADDR(pstPppInfo->pstIpcpInfo, pstPppInfo->ulRPIndex);
        if (VOS_NULL_PTR == pstPppInfo->pstIpcpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_571);
            PPPC_WARNING_LOG(" \r\n PPP_StartIPV4CP: malloc ipcp CB fail!");
            return VOS_ERR;
        }
        PPP_MemSet(pstPppInfo->pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

        PPPC_INFO_LOG("\r\n PPP_StartIPV4CP: active ipcp negoation !");
    }

    /* 有控制块 */
    pstIpcpInfo = (PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo;

    /* 判断是否需要协商VJ压缩 */
    /*lint -e746*/
    if(VOS_OK == PPP_CheckVjLimit())
    /*lint +e746*/
    {
        pstPppInfo->pstConfigInfo->bEnableVJComp = 1;
    }
    else
    {
        pstPppInfo->pstConfigInfo->bEnableVJComp = 0;
    }

    /* 初始化IPCP控制块 取出IPCP控制块中内容，先发Request消息 */
    PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);
    /* 向IPCP发送消息,触发IPCP开始协商 */
    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, VOS_NULL_PTR );
    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, VOS_NULL_PTR );

    /* 处理缓存消息*/
    if (VOS_NULL_PTR != pstIpcpInfo->pucIpv4cpMsg)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1295);
        pHead    = pstIpcpInfo->pucIpv4cpMsg;
        pPacket  = pstIpcpInfo->pucIpv4cpMsg + PPP_RESERVED_PACKET_HEADER;
        ulMsgLen = pstIpcpInfo->ulIpv4cpLen;

        /* 收到终端发来的鉴权请求 */
        PPP_IPCP_ReceivePacket(pstPppInfo->pstIpcpInfo, pHead, pPacket, ulMsgLen);
        (VOID)PPP_Free(pstIpcpInfo->pucIpv4cpMsg);
        pstIpcpInfo->pucIpv4cpMsg = VOS_NULL_PTR;
        pstIpcpInfo->ulIpv4cpLen = 0;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1296);
    PPPC_INFO_LOG("\r\n PPP_StartIPV4CP: Done!");
    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : PPP_StartIPV6CP
 功能描述  :
          如果没有PPP控制块，返回失败
          如果有PPP控制块，没有IPCP控制块，就要判断是否在重协商，是则保存地址，否则返回失败
          如果有IPCP控制块，则保存地址，进行IPCP协商
          取出控制块中缓存消息，发送IPCP Request 消息，然后再收到缓存中的IPCP Request 消息

 输入参数  : VOS_UINT32 ulRpIdx
             UCHAR* szIpV6Addr
             UCHAR* szPriDns
             UCHAR* szSecDns
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_StartIPV6CP(VOS_UINT32 ulRpIdx, UCHAR* szIpV6Addr, UCHAR* szPriDns, UCHAR* szSecDns)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S *pstIpV6CpInfo = VOS_NULL_PTR;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    VOS_UINT32 ulMsgLen = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIdx);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_572);
        PPPC_INFO_LOG1("\r\n PPP_StartIPV6CP: User %d isn't exist!", ulRpIdx);
        return VOS_ERR;
    }

    if (VOS_OK == PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_573);
        PPPC_INFO_LOG("\r\n PPP_StartIPV6CP: User IP is exist!");
        return VOS_ERR;
    }

    /* 保存地址 */
    VOS_MemCpy(pstPppInfo->usPeerIPv6Addr, szIpV6Addr, PDN_IPV6ADDR_LEN);
    pstPppInfo->ucIpCapability |= PDSN_PPP_IPTYE_IPV6;

    /* 重协商，直接保存地址 此处重协商标记控制不住 使用协商阶段控制 */
    if ((VOS_UINT16)PPP_PHASE_NETWORK != pstPppInfo->usPhase)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1297);
        PPPC_WARNING_LOG("\r\n PPP_StartIPV6CP: Renego!");
        return VOS_OK;
    }

    /* 没有控制块 */
    if (VOS_NULL_PTR == pstPppInfo->pstIpV6cpInfo)
    {
        /* 否则创建控制块，主动协商 */
        PPP_GETIPV6CPADDR(pstPppInfo->pstIpV6cpInfo, pstPppInfo->ulRPIndex);
        if (VOS_NULL_PTR == pstPppInfo->pstIpV6cpInfo)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1298);
            PPPC_WARNING_LOG(" \r\n PPP_StartIPV6CP: malloc ipcp CB fail!");
            return VOS_ERR;
        }
        PPP_MemSet(pstPppInfo->pstIpV6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));

        PPPC_INFO_LOG("\r\n PPP_StartIPV6CP: IPV6CP CB is VOS_NULL_PTR!");
    }

    pstIpV6CpInfo = (PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo;

    /* 初始化IPV6CP控制块 取出IPV6CP控制块中内容，先发Request消息，然后收到 */
    PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);

    /* 向IPCP发送消息,触发IPCP开始协商 */
    PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (VOS_UINT32)PPP_EVENT_FSM_OPEN, VOS_NULL_PTR );
    PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (VOS_UINT32)PPP_EVENT_FSM_UP, VOS_NULL_PTR );

    /* 处理缓存消息*/
    if (pstIpV6CpInfo->pucIpv6cpMsg)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1299);
        pHead    = pstIpV6CpInfo->pucIpv6cpMsg;
        pPacket  = pstIpV6CpInfo->pucIpv6cpMsg + PPP_RESERVED_PACKET_HEADER;
        ulMsgLen = pstIpV6CpInfo->ulIpv6cpLen;

        /* 收到终端发来的鉴权请求 */
        PPP_IPV6CP_Pactket_Proc(pstPppInfo, pHead, pPacket, ulMsgLen);

        (VOID)PPP_Free(pstIpV6CpInfo->pucIpv6cpMsg);
        pstIpV6CpInfo->pucIpv6cpMsg = VOS_NULL_PTR;
        pstIpV6CpInfo->ulIpv6cpLen = 0;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1300);

    PPPC_INFO_LOG("\r\n PPP_StartIPV6CP: Done!");
    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : PPP_StopIPV4CP
 功能描述  : PDN通知PPP单栈删除IPV4
 输入参数  : VOS_UINT32 ulRpIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_StopIPV4CP(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR ;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    VOS_UINT32 ulMsgLen = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_574);
        PPPC_INFO_LOG1("\r\n PPP_StopIPV4CP: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }
    pstPppInfo->bIpcpNoToPDN= VOS_TRUE;   /* 1时不通知PDN */
    pstIpcpInfo = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV4;

    /* 发送ipcp term消息拆除ipv4链路 */
    if (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlg)
    {
        PPP_IPCP_NegotiationDown(pstPppInfo->pstIpcpInfo);
        PPP_DBG_OK_CNT(PPP_PHOK_1301);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1302);
        if ((VOS_NULL_PTR != pstIpcpInfo)
            && (PPP_STATE_INITIAL == pstIpcpInfo->stFsm.ucState)
            && (VOS_NULL_PTR != pstIpcpInfo->pucIpv4cpMsg))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1303);
            /* 如果是INIT状态，说明是在等待PDN申请地址，如果失败则需要发LCP Protol Reject */
            pHead    = pstIpcpInfo->pucIpv4cpMsg;
            pPacket  = pstIpcpInfo->pucIpv4cpMsg + PPP_RESERVED_PACKET_HEADER;
            ulMsgLen = pstIpcpInfo->ulIpv4cpLen;

            PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulMsgLen, PPP_IPCP, CONFREQ);

            (VOID)PPP_Free(pstIpcpInfo->pucIpv4cpMsg);
            pstIpcpInfo->pucIpv4cpMsg = VOS_NULL_PTR;
            pstIpcpInfo->ulIpv4cpLen = 0;
        }
        PPP_Core_IpcpV4FinProc(pstPppInfo);
    }

    PPPC_INFO_LOG("\r\n PPP_StopIPV4CP Done!");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_ReleaseIPV4CP
 功能描述  : PDN通知PPP单栈删除IPV4控制块
 输入参数  : VOS_UINT32 ulRpIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月28日
    作    者   : y00170683
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_ReleaseIPV4CP(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_575);
        PPPC_INFO_LOG1("\r\n PPP_StopIPV4CP: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }
    pstPppInfo->bIpcpNoToPDN= VOS_TRUE;   /* 1时不通知PDN */
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV4;

    PPP_Core_IpcpV4FinProc(pstPppInfo);
    PPP_DBG_OK_CNT(PPP_PHOK_1304);

    PPPC_INFO_LOG("\r\n PPP_StopIPV4CP Done!");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_StopIPV6CP
 功能描述  : PDN通知PPP单栈删除IPV6
 输入参数  : VOS_UINT32 ulRpIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_StopIPV6CP(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S *pstIpv6cpInfo = VOS_NULL_PTR ;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    VOS_UINT32 ulMsgLen = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_576);
        PPPC_INFO_LOG1("\r\n PPP_StopIPV6CP: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    pstPppInfo->bIpv6cpNoToPDN= VOS_TRUE;   /* 1时不通知PDN */
    pstIpv6cpInfo = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV6;

    /*发送只有ipv6处于open 状态才ipv6cp term消息拆除ipv6链路， 否则直接删除ipv6cp资源。*/
    if (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlgV6)
    {
        PPP_IPV6CP_NegotiationDown(pstPppInfo->pstIpV6cpInfo);
        PPP_DBG_OK_CNT(PPP_PHOK_1305);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1306);
        if ((VOS_NULL_PTR != pstIpv6cpInfo)
            && (PPP_STATE_INITIAL == pstIpv6cpInfo->stFsm.ucState)
            && (VOS_NULL_PTR != pstIpv6cpInfo->pucIpv6cpMsg))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1307);
            /* 如果是INIT状态，说明是在等待PDN申请地址，如果失败则需要发LCP Protol Reject */
            pHead    = pstIpv6cpInfo->pucIpv6cpMsg;
            pPacket  = pstIpv6cpInfo->pucIpv6cpMsg + PPP_RESERVED_PACKET_HEADER;
            ulMsgLen = pstIpv6cpInfo->ulIpv6cpLen;

            PPP_Core_ReceiveUnknownProtocol(pstPppInfo, pHead, pPacket, ulMsgLen, PPP_IPV6CP, CONFREQ);

            (VOID)PPP_Free(pstIpv6cpInfo->pucIpv6cpMsg);
            pstIpv6cpInfo->pucIpv6cpMsg = VOS_NULL_PTR;
            pstIpv6cpInfo->ulIpv6cpLen = 0;
        }

        PPP_Core_IpcpV6FinProc(pstPppInfo);
    }

    PPPC_INFO_LOG("\r\n PPP_StopIPV6CP Done!");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_ReleaseIPV6CP
 功能描述  : PDN通知PPP单栈删除IPV6控制块
 输入参数  : VOS_UINT32 ulRpIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月28日
    作    者   : y00170683
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_ReleaseIPV6CP(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_577);
        PPPC_INFO_LOG1("\r\n PPP_StopIPV6CP: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    pstPppInfo->bIpv6cpNoToPDN= VOS_TRUE;   /* 1时不通知PDN */
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV6;

    PPP_Core_IpcpV6FinProc(pstPppInfo);
    PPP_DBG_OK_CNT(PPP_PHOK_1308);

    PPPC_INFO_LOG("\r\n PPP_StopIPV6CP Done!");
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_NotifyIpv6SendRA
 功能描述  : ppp通知ipv6发送ra消息
 输入参数  : VOS_UINT32 ulRpIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年04月13日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_NotifyIpv6SendRA(VOS_UINT32 ulRpIndex, UCHAR ucPDNId)
{
    VOS_UINT32 ulResult = 0;
    VOS_UINT32 ulPdnIndex = 0;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL_PTR;

    /*获取rp上下文*/
    ulResult = (VOS_UINT32)SDB_GetRpContextByIndex(ulRpIndex, (VOID**)&pstRpContext);
    if ((SDB_SUCCESS != ulResult) || (VOS_NULL_PTR == pstRpContext))
    {
        PPPC_WARNING_LOG1(
                     "\r\n PPP_NotifyIpv6SendRA: User %u isn't exist!", ulRpIndex);
        PPP_DBG_ERR_CNT(PPP_PHERR_578);
        return VOS_ERR;
    }

    PPPC_INFO_LOG1(
                 "\r\n PPP_NotifyIpv6SendRA: ucPDNId[%u]!", ucPDNId);
    if (VOS_NULL_BYTE == ucPDNId)
    {
        ucPDNId = 0;
    }
    PPPC_INFO_LOG1(
                 "\r\n PPP_NotifyIpv6SendRA1: ucPDNId[%u]!", ucPDNId);
    if (ucPDNId >= A11_MAX_PDN_NUM)
    {
        PPPC_WARNING_LOG1(
                     "\r\n PPP_NotifyIpv6SendRA: ucPDNId %u isn't valid!", ucPDNId);
        PPP_DBG_ERR_CNT(PPP_PHERR_579);
        return VOS_ERR;
    }

    ulPdnIndex = (VOS_UINT32)pstRpContext->ausPdnIndexArray[ucPDNId];

    /*获取PDN上下文*/
    ulResult = (VOS_UINT32)SDB_GetPdnContextByIndex(ulPdnIndex, (VOID**)&pstPdnContext);
    if ((SDB_SUCCESS != ulResult) || (VOS_NULL_PTR == pstPdnContext))
    {
        PPPC_WARNING_LOG1(
                     "\r\n PPP_NotifyIpv6SendRA: PDN %u isn't exist!", ulPdnIndex);
        PPP_DBG_ERR_CNT(PPP_PHERR_580);
        return VOS_ERR;
    }

    PPPC_INFO_LOG3(
                 "\r\n PPP_NotifyIpv6SendRA: ulPdnIndex[%u]bIpV6Used[%u]ulIpv6Timer[%u]!",
                 ulPdnIndex,pstPdnContext->bIpV6Used,pstPdnContext->ulIpv6Timer);

    if (pstPdnContext->bIpV6Used)
    {
        if (0 != pstPdnContext->ulIpv6Timer)
        {
            /* 停止IPv6定时器，不再发生RA消息 */
            ulResult = IPV6_StopTimer(pstPdnContext->ulIpv6Timer);
            if (VOS_OK != ulResult)
            {
                /* 增加调试信息，但不退出 */
                PPP_DBG_ERR_CNT(PPP_PHERR_581);
            }
        }

        pstPdnContext->ucIpv6RouteMsgNum = 0;

        /* 通知IPv6发送RA消息 */
        ulResult = Ipv6_A11NotifySendRa(pstPdnContext->ulPdnIndex);
        if (VOS_OK != ulResult)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_582);
            PPPC_WARNING_LOG2(
                         "\r\n PPP_NotifyIpv6SendRA: Ipv6_A11NotifySendRa fail pdnindex[%u]!",
                         ulResult,pstPdnContext->ulPdnIndex);
            return VOS_ERR;
        }
        PPP_DBG_OK_CNT(PPP_PHOK_1309);
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPP_SendFakeIPV4CPReqMsg
 功能描述  : PDN超时，PPP提供给PDN调用发送Config Req消息
 输入参数  : VOS_UINT32 ulRpIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月13日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_SendFakeIPV4CPReqMsg(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR;
    PPPFSM_S *pstFsm = VOS_NULL_PTR;

    /* 获取PPP控制块 */
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_583);
        PPPC_INFO_LOG1("\r\n PPP_SendFakeIPV4CPReqMsg: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    if (PPP_PHASE_NETWORK != pstPppInfo->usPhase)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_584);
        PPPC_INFO_LOG1("\r\n PPP_SendFakeIPV4CPReqMsg: Wrong phase! usPhase = %u", pstPppInfo->usPhase);
        return VOS_ERR;
    }

    /* 获取IPCP控制块 */
    pstIpcpInfo = pstPppInfo->pstIpcpInfo;
    if (VOS_NULL_PTR == pstIpcpInfo)
    {
        PPP_GETIPCPADDR(pstIpcpInfo, pstPppInfo->ulRPIndex);
        if (VOS_NULL_PTR == pstIpcpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_585);
            /* Malloc Error */
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_SendFakeIPV4CPReqMsg Malloc IPCP CB Err!!");
            return VOS_ERR;
        }
        pstPppInfo->pstIpcpInfo = pstIpcpInfo;
    }

    PPP_MemSet((void *)pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

    /* 判断是否需要协商VJ压缩 */
    /*lint -e746*/
    if(VOS_OK == PPP_CheckVjLimit())
    /*lint +e746*/
    {
        pstPppInfo->pstConfigInfo->bEnableVJComp = 1;
    }
    else
    {
        pstPppInfo->pstConfigInfo->bEnableVJComp = 0;
    }

    PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);

    pstFsm = (PPPFSM_S*)&(pstIpcpInfo->stFsm);
    (*pstFsm->pstCallBacks->resetci)(pstFsm);

    /* 构造并发送报文 */
    PPP_FSM_SendConfigReq(pstFsm);

    /* 清除IPCP控制块 */
    PPP_ClearCB_IPCP(pstIpcpInfo);
    pstPppInfo->pstIpcpInfo = VOS_NULL_PTR;


    PPP_DBG_OK_CNT(PPP_PHOK_1310);
    PPPC_INFO_LOG("\r\n PPP_SendFakeIPV4CPReqMsg Done !");
    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : PPP_SendFakeIPV6CPReqMsg
 功能描述  : PDN超时，PPP提供给PDN调用发送Config Req消息
 输入参数  : VOS_UINT32 ulRpIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月13日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_SendFakeIPV6CPReqMsg(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S *pstIpV6cpInfo = VOS_NULL_PTR;
    PPPFSM_S *pstFsm = VOS_NULL_PTR;

    /* 获取PPP控制块 */
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (pstPppInfo == VOS_NULL_PTR)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_585);
        PPPC_INFO_LOG1("\r\n PPP_SendFakeIPV6CPReqMsg: User %d isn't exist!", ulRpIndex);
        return VOS_ERR;
    }

    if (PPP_PHASE_NETWORK != pstPppInfo->usPhase)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_586);
        PPPC_INFO_LOG1("\r\n PPP_SendFakeIPV6CPReqMsg: Wrong phase! usPhase = %u", pstPppInfo->usPhase);
        return VOS_ERR;
    }

    /* 获取IPV6CP控制块 */
    pstIpV6cpInfo = pstPppInfo->pstIpV6cpInfo;
    if (VOS_NULL_PTR == pstIpV6cpInfo)
    {
        PPP_GETIPV6CPADDR(pstIpV6cpInfo, pstPppInfo->ulRPIndex);
        if (VOS_NULL_PTR == pstIpV6cpInfo)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1311);
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "\r\nPPP_SendFakeIPV6CPReqMsg Malloc IPv6CP CB Err!!");
            return VOS_ERR;
        }
        pstPppInfo->pstIpV6cpInfo = pstIpV6cpInfo;
    }
    PPP_MemSet((void *)pstIpV6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));

    PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);

    pstFsm = (PPPFSM_S*)&(pstIpV6cpInfo->stFsm);
    (*pstFsm->pstCallBacks->resetci)(pstFsm);

    /* 构造并发送报文 */
    PPP_FSM_SendConfigReq(pstFsm);

    /* 清除IPV6CP控制块 */
    PPP_ClearCB_IPV6CP(pstIpV6cpInfo);
    pstPppInfo->pstIpV6cpInfo = VOS_NULL_PTR;

    PPP_DBG_OK_CNT(PPP_PHOK_1312);
    PPPC_INFO_LOG("\r\n PPP_SendFakeIPV6CPReqMsg Done!");
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPP_Shell_ReceiveLcpUpFromCore
 功能描述  : PPP外壳收到LCP_UP事件
 输入参数  : PPPINFO_S *pstPppInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_Shell_ReceiveLcpUpFromCore(PPPINFO_S *pstPppInfo)
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;

    if ( VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_INFO_LOG("\r\n PPP_Shell_ReceiveLcpUpFromCore Input para null! ");
        return VOS_ERR;
    }

    pstLcpInfo = (PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo);

    if ( VOS_NULL_PTR == pstLcpInfo)
    {
        PPPC_INFO_LOG("\r\nPPP_Shell_ReceiveLcpUpFromCore para null");
        return VOS_ERR;
    }

    if (VOS_OK != PPP_SendUserInfo(pstPppInfo, LCP_INFOR))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_587);
        return VOS_ERR;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1313);

    /* 性能统计:LCP协商成功次数 */
    PPP_PerfInc(&g_stPppPerfStatistic.ulLcpSuccess, PERF_TYPE_PPPC_LCP_NEGO_SUCC_NUM, pstPppInfo->bEhrpdUser);
    PPPC_INFO_LOG1(
                  "\r\n [ppp]PPP_Shell_ReceiveLcpUpFromCore: LcpSuccess: %d",
                  g_stPppPerfStatistic.ulLcpSuccess);
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPP_Shell_ReceiveLcpDownFromCore
 功能描述  : PPP外壳收到LCP_DOWN事件
 输入参数  : PPPINFO_S *pstPppInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_Shell_ReceiveLcpDownFromCore(PPPINFO_S *pstPppInfo)
{
    PPPC_INFO_LOG1(
                  "\r\n [ppp]PPP_Shell_ReceiveLcpDownFromCore: Enter pstPppInfo->bFailFlag=%d", pstPppInfo->bFailFlag);

    if (PPPLOWEDOWN != pstPppInfo->bFailFlag)
    {

        PPP_DBG_OK_CNT(PPP_PHOK_1314);

        if (LAPRECYCLE == pstPppInfo->bFailFlag)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1315);
            PPPC_INFO_LOG(
                          "\r\n [ppp]PPP_Shell_ReceiveLcpDownFromCore: LAPRECYCLE");
            A11_PPP_TermTag(pstPppInfo->ulRPIndex, LAPRECYCLE);
        }
        else if (PPPFADOWN == pstPppInfo->bFailFlag)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1316);
            PPPC_INFO_LOG(
                          "\r\n [ppp]PPP_Shell_ReceiveLcpDownFromCore: PPPFADOWN");
            A11_PPP_TermTag(pstPppInfo->ulRPIndex, PPPFADOWN);
        }
        else
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1317);
            A11_PPP_TermTag(pstPppInfo->ulRPIndex, PPP_Negotiation_Fail);
        }

        PPPC_INFO_LOG1("\r\n [ppp]PPP_Shell_ReceiveLcpDownFromCore: Notify lower release user %u", pstPppInfo->ulRPIndex);
    }

    /* 退网最后一步 */
    PPPC_WARNING_LOG1("Into Delete CB", g_astPppPool[pstPppInfo->ulRPIndex].usState);
    if (PPP_CB_STATE_USED == g_astPppPool[pstPppInfo->ulRPIndex].usState)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1318);
        (VOID)PPP_DeleteCB(pstPppInfo, PS_TRUE);

        PPPC_DeletePppId((VOS_UINT8)pstPppInfo->ulRPIndex);
    }

    PPPC_INFO_LOG("\r\n PPP_Shell_ReceiveLcpDownFromCore Done!");
    return;
}


/*****************************************************************************
 函 数 名  : PPP_Shell_IpcpUpNoIp
 功能描述  : IPCP协商完成后用户没协商ip
 输入参数  : PPPINFO_S *pstPppInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月22日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_Shell_IpcpUpNoIp(PPPINFO_S *pstPppInfo)
{
    if(VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_INFO_LOG("\r\n PPP_Shell_IpcpUpNoIp Input is null!");
        return VOS_ERR;
    }

    PPPC_INFO_LOG2("\r\n [ppp]PPP_Shell_IpcpUpNoIp: Enter pstPppInfo->bIPTech %u pstPppInfo->ulPeerIPAddr %u",
                  pstPppInfo->bIPTech, pstPppInfo->ulPeerIPAddr);

    /* 非CMip用户，删除单栈 */

    /*清除ipv4地址及IPV4版本能力*/
    PPP_DBG_OK_CNT(PPP_PHOK_1319);
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV4;
    PPP_IPCP_NegotiationDown(pstPppInfo->pstIpcpInfo);

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : PPP_Shell_IpcpUpNegotiateIp
 功能描述  :  PPP的处理IpcpUpNegotiateIp事件的函数
 输入参数  : PPPINFO_S *pstPppInfo
             PPPLCPINFO_S *pstLcpInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_Shell_IpcpUpNegotiateIp(PPPINFO_S *pstPppInfo, PPPLCPINFO_S *pstLcpInfo)
{

    PPPC_INFO_LOG2("\r\n [ppp]PPP_Shell_IpcpUpNegotiateIp: Enter pstPppInfo->bIPTech %u pstPppInfo->ulPeerIPAddr %u",
                  pstPppInfo->bIPTech, pstPppInfo->ulPeerIPAddr);

    /* 配置了鉴权但没有鉴权 */
    if (PPP_USERTYPE_NOCMIP_NOAAA(pstLcpInfo,pstPppInfo))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_10);
        PPPC_INFO_LOG1(
                      "\r\n [ppp]PPP_Shell_IpcpUpNegotiateIp: is sip no auth: %u",
                      pstPppInfo->ulRPIndex);
        /*免认证算作PPP协商成功*/
        PPP_SNMP_PERF_SET_SUCCESS(pstPppInfo);

        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);

        /* 在IPCP成功之间免认证用户PDSN会去活该用户 分组会话激活请求数减1 */
        A11_ReqNumSubProc(pstPppInfo);
        PPP_PerfInc(&g_stPppPerfStatistic.ulIpcpSuccess, PERF_TYPE_PPPC_IPCP_NEGO_SUCC_NUM, pstPppInfo->bEhrpdUser);


        PPP_DBG_ERR_CNT(PPP_PHERR_588);

        return VOS_ERR;
    }
    PPPC_INFO_LOG("\r\n PPP_Shell_IpcpUpNegotiateIp Done!");
    return VOS_OK;
}


/*****************************************************************************
函 数 名  : PPP_Shell_IpcpSuccessProc
功能描述  : PPP的处理IpcpUp成功后的处理函数
输入参数  : PPPINFO_S *pstPppInfo
输出参数  : 无
返 回 值  : VOS_OK;VOS_ERR
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2009-03-19
  作    者   : c00127007
  修改内容   : 新生成函数 for reduce CC

*****************************************************************************/
VOS_UINT32 PPP_Shell_IpcpSuccessProc(PPPINFO_S *pstPppInfo)
{
    ULONG64 ulNegoTime = 0;
    VOS_UINT32 ulRet;


    PPPC_INFO_LOG("\r\n [ppp]PPP_Shell_IpcpSuccessProc: Enter");
#if 0
    /* 检查是否允许激活cmip用户DTS2014012102440  */
    if (VOS_OK != PDN_CheckIsCmipCanRun(pstPppInfo->ulRPIndex, 0))
    {
         PPPC_INFO_LOG(MID_PPPC, PDSN_DBGLVL_INFO,
                   "\r\n [ppp]PPP_Shell_IpcpSuccessProc: dea cmip user for bit1493 is openl !");
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_DEA_CMIP_FOR_BIT1493);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        return VOS_ERR;
    }
#endif

    /* 删除协商定时器 */
    (VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);


    if (pstPppInfo->bReNego)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1320);
        pstPppInfo->bReNego = 0;
        if (pstPppInfo->pstPppRenegoInfo)
        {
            (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
            pstPppInfo->pstPppRenegoInfo = 0;
        }
    }


    PPP_SNMP_PERF_SET_SUCCESS(pstPppInfo);

    /* 性能统计:IPCP协商成功次数 */
    PPP_PerfInc(&g_stPppPerfStatistic.ulIpcpSuccess, PERF_TYPE_PPPC_IPCP_NEGO_SUCC_NUM, pstPppInfo->bEhrpdUser);
    PPP_DBG_OK_CNT(PPP_PHOK_1321);

    /* 稳态连接标记置成功 */
    pstPppInfo->bPppStateFlg = PPP_STATE_SUCCESS;

    /* PPP链路建立成功 */
    pstPppInfo->bPppSuccess = 1;

    /* 重协商不做统计( 问题单号:DTS2012051201030 ) */
    if(0 == pstPppInfo->ulNegoEndTime)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1322);
        pstPppInfo->ulNegoEndTime = VOS_GetTick();
        ulNegoTime = pstPppInfo->ulNegoEndTime - pstPppInfo->ulNegoStartTime;
        (VOID)PerfSetFamPerfCounterByAddress(&(g_stPppPerfStatistic.ulPppNegoTotalTime), PPP_PERF_ADD, (VOS_UINT32)ulNegoTime);
        PPP_PerfInc(&g_stPppPerfStatistic.ulPppNegoNum, PERF_TYPE_PPPC_PPP_NEGO_NUM, pstPppInfo->bEhrpdUser);
    }

    /* 定时备份,记录改变的连接 */

    if (pstPppInfo->bReNego)
    {
        pstPppInfo->bReNego = 0;
        if (pstPppInfo->pstPppRenegoInfo)
        {
            (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
            pstPppInfo->pstPppRenegoInfo = 0;
        }
    }

    if (VOS_NULL_PTR != pstPppInfo->pstLcpInfo)
    {
        ((PPPLCPINFO_S*)pstPppInfo->pstLcpInfo)->bReqSendAck = VOS_FALSE;
    }

    /* 释放L2TP控制块 */
    if (pstPppInfo->pL2tpPara != VOS_NULL_PTR)
    {
        (VOID)PPP_Free(pstPppInfo->pL2tpPara);
        pstPppInfo->pL2tpPara = VOS_NULL_PTR;
    }

    if (VOS_OK != PPP_SendUserInfo(pstPppInfo, IPCP_INFOR))
    {
        PPPC_INFO_LOG(
                   "\r\n [ppp]PPP_Shell_IpcpSuccessProc: PPP_SendUserInfo fail !");
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_590);
        return VOS_ERR;
    }

    ulRet = PPP_StopNegoTimer((VOS_UINT8)pstPppInfo->ulRPIndex);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("stop nego timer fail!\r\n", ulRet);
    }

    /* IPCP成功时发送 */
    PPPC_IsReadyToRespActCmd(pstPppInfo);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_Shell_ReceiveIpcpUpFromCore
 功能描述  : PPP的处理IpcpUp事件的函数
 输入参数  : PPPINFO_S *pstPppInfo
 输出参数  : 无
 返 回 值  : VOS_OK;VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-03-19
    作    者   : c00127007
    修改内容   : 新生成函数 for reduce CC

*****************************************************************************/
VOS_UINT32 PPP_Shell_ReceiveIpcpUpFromCore(PPPINFO_S *pstPppInfo)
{
    VOS_UINT32 ulRet = VOS_OK;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR;
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    UCHAR ucDmpuId = 0;
    UCHAR ucDpeId = 0;


    PPPC_INFO_LOG("\r\n [ppp]PPP_Shell_ReceiveIpcpUpFromCore: Enter");

    pstIpcpInfo = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
    pstLcpInfo = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;


    if(pstIpcpInfo->stGotOptions.neg_vj)
    {
        /* 选择子卡及子卡的DPEID */
        if (MAX_DMPU_ID <= pstPppInfo->ucDmpuId)
        {
            ulRet = (VOS_UINT32)PPP_CompSelectDmpuDpe(&ucDmpuId, &ucDpeId);
            if (VOS_OK != ulRet)
            {
                HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_11);
                /* 子卡不在位，或用户数也已经达到上限，则退网 */
                PPP_DBG_ERR_CNT(PPP_PHERR_591);
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
                PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*释放链路*/
                return VOS_ERR;
            }

            ulRet = (VOS_UINT32)PPP_CompCheckVjUserNum(&ucDmpuId);
            if(VOS_OK != ulRet)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_592);
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
                PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*释放链路*/
                return VOS_ERR;
            }

            pstPppInfo->ucDmpuId = ucDmpuId;
            pstPppInfo->ucDpeId  = ucDpeId;
        }

        if((VOS_FALSE == pstPppInfo->bVjFlag) && (VOS_TRUE == pstPppInfo->bMppcFlag))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1323);
        }
        /* END of liushuang*/
        PPP_CompUserNumAdd(pstPppInfo, PPP_USERSTAT_VJ);
    }


    /*协商了IP地址*/
    ulRet = PPP_Shell_IpcpUpNegotiateIp(pstPppInfo, pstLcpInfo);
    if (VOS_ERR == ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_593);
        return VOS_ERR;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1324);
    return PPP_Shell_IpcpSuccessProc(pstPppInfo);
}


/*****************************************************************************
 函 数 名  : PPP_Shell_IpV6cpUpNoIp
 功能描述  : IPV6CP协商完成后用户没有协商IP
 输入参数  : PPPINFO_S *pstPppInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月22日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_Shell_IpV6cpUpNoIp( PPPINFO_S *pstPppInfo )
{

    if(VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_INFO_LOG("\r\n PPP_Shell_IpcpUpNoIp Input is null!");
        return VOS_ERR;
    }

    /* IPV6CP协商没有协商用户IP，直接通知PDN删除单栈，不支持CMIPV6 */

    /*清除ipv6地址及IPV6版本能力*/
    PPP_DBG_OK_CNT(PPP_PHOK_1325);
    pstPppInfo->ucIpCapability &= ~PDSN_PPP_IPTYE_IPV6;
    PPP_IPV6CP_NegotiationDown(pstPppInfo->pstIpV6cpInfo);

    return VOS_OK;
}



/*****************************************************************************
 函 数 名  : PPP_Shell_IpV6cpUpNegotiateIp
 功能描述  : ipv6cp阶段协商了ip的sip场景up处理函数
 输入参数  : PPPINFO_S *pstPppInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月12日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_Shell_IpV6cpUpNegotiateIp( PPPINFO_S *pstPppInfo )
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;

    PPPC_INFO_LOG4(
                 "\r\n PPP_Shell_Ipv6cpUpNegotiateIp: ipcp up (negotiate ip) addr:%02x:%02x:%02x:%02x",
                 pstPppInfo->usPeerIPv6Addr[0],pstPppInfo->usPeerIPv6Addr[1],pstPppInfo->usPeerIPv6Addr[2],pstPppInfo->usPeerIPv6Addr[3]);

    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if ( VOS_NULL_PTR == pstLcpInfo )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_594);
        PPPC_INFO_LOG("\r\n PPP_Shell_IpV6cpUpNegotiateIp: lcp cb is null");
        return VOS_ERR;
    }

    /* 配置了鉴权但没有鉴权 */
    if (PPP_USERTYPE_NOCMIP_NOAAA(pstLcpInfo,pstPppInfo))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_12);
        PPP_DBG_ERR_CNT(PPP_PHERR_595);
        PPPC_INFO_LOG1(
                     "\r\n PPP_Shell_Ipv6cpUpNegotiateIp 2: is sip no auth: %u",
                     pstPppInfo->ulRPIndex);

        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPV6CP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        /* 性能统计:IPv6CP协商成功次数 DTS2012060402399 */
        A11_OM_PerfStatisticPCFUnit((VOS_UINT32)PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_SUCC_NUM, pstPppInfo->ulPcfIP);
        return VOS_ERR;
    }
    PPPC_INFO_LOG("\r\n PPP_Shell_IpV6cpUpNegotiateIp Done!");
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPP_Shell_IpV6cpSuccessProc
 功能描述  : shell层处理ipv6cp成功的处理函数
 输入参数  : PPPINFO_S *pstPppInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月12日
    作    者   : T62595
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_Shell_IpV6cpSuccessProc( PPPINFO_S *pstPppInfo )
{
    PDN_PPP_NCP_UP_S                    stNcpUpInfo = { 0 };
    ULONG64                             ulNegoTime = 0;
    VOS_UINT32                          ulRet;

    /* 性能统计 */

    /* IPV6CP成功，PPP通知PDN */
    VOS_MemCpy(stNcpUpInfo.aucIpV6Addr, pstPppInfo->usPeerIPv6Addr,PDN_IPV6ADDR_LEN);

    /* Added start by y00202564 at 2012-03-08 for ipv6性能统计 */
    /* 性能统计:IPv6CP协商成功次数 */
    PPP_DBG_OK_CNT(PPP_PHOK_1326);
    PPPC_INFO_LOG(  "\r\n PPP_Shell_IpV6cpSuccessProc: IPV6_PerfStatistic Success:Enter !");

    A11_OM_PerfStatisticPCFUnit((VOS_UINT32)PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_SUCC_NUM, pstPppInfo->ulPcfIP);

    M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_SUCCESS);

    /* PPP链路建立成功 */
    pstPppInfo->bPppSuccess = 1;

    /* 删除协商定时器 */
    (VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);

    if(0 == pstPppInfo->ulNegoEndTime)
    {
        pstPppInfo->ulNegoEndTime = VOS_GetTick();
        ulNegoTime = pstPppInfo->ulNegoEndTime - pstPppInfo->ulNegoStartTime;
        (VOID)PerfSetFamPerfCounterByAddress(&(g_stPppPerfStatistic.ulPppNegoTotalTime), PPP_PERF_ADD, (VOS_UINT32)ulNegoTime);
        PPP_PerfInc(&g_stPppPerfStatistic.ulPppNegoNum, PERF_TYPE_PPPC_PPP_NEGO_NUM, pstPppInfo->bEhrpdUser);
        PPP_DBG_OK_CNT(PPP_PHOK_1327);
    }

    /* 稳态连接标记置成功 */
    pstPppInfo->bPppStateFlgV6 = PPP_STATE_SUCCESS;

    /* 定时备份 */

    if (pstPppInfo->bReNegoV6)
    {
        pstPppInfo->bReNegoV6 = 0;

        /*ipcp控制块为空或者v4重协商标记无效则释放控制块*/
        if (((pstPppInfo->pstPppRenegoInfo)&&(VOS_NULL_PTR == pstPppInfo->pstIpcpInfo))
            || ((pstPppInfo->pstPppRenegoInfo)&&(!pstPppInfo->bReNego)))
        {
            (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
            pstPppInfo->pstPppRenegoInfo = 0;
        }
    }

    if (pstPppInfo->pL2tpPara != VOS_NULL_PTR)
    {
        (VOID)PPP_Free(pstPppInfo->pL2tpPara);
        pstPppInfo->pL2tpPara = VOS_NULL_PTR;
    }

    (VOID)PPP_NotifyIpv6SendRA(pstPppInfo->ulRPIndex, VOS_NULL_BYTE);

    (VOID)PPP_SendUserInfo(pstPppInfo, IPCPV6_INFOR);

    ulRet = PPP_StopNegoTimer((VOS_UINT8)pstPppInfo->ulRPIndex);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("stop nego timer fail!\r\n", ulRet);
    }

    /* IPV6CP成功时发送 */
    PPPC_IsReadyToRespActCmd(pstPppInfo);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_Shell_ReceiveIpV6cpUpFromCore
 功能描述  : shell层收到核心层IPV6CP-UP事件的处理函数
 输入参数  : PPPINFO_S *pstPppInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月12日
    作    者   : T62595
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_Shell_ReceiveIpV6cpUpFromCore(  PPPINFO_S *pstPppInfo )
{
    PPPIPV6CPINFO_S* pstIpV6cpInfo = VOS_NULL_PTR;
    VOS_UINT32 ulRet = VOS_ERR;

    pstIpV6cpInfo = pstPppInfo->pstIpV6cpInfo;
    if ( VOS_NULL_PTR == pstIpV6cpInfo )
    {
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPV6CP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*释放链路*/
        PPP_DBG_ERR_CNT(PPP_PHERR_597);
        return VOS_ERR;
    }

    /* 未协商ip为CMIP场景 */
    if (0 == pstIpV6cpInfo->stHisOptions.neg_addr)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_598);
        (VOID)PPP_Shell_IpV6cpUpNoIp(pstPppInfo);
        return VOS_ERR;
    }

    /*协商了IP地址*/
    ulRet = PPP_Shell_IpV6cpUpNegotiateIp(pstPppInfo);
    if (VOS_ERR == ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_599);
        return VOS_ERR;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1328);
    return PPP_Shell_IpV6cpSuccessProc(pstPppInfo);
}



/*****************************************************************************
 函 数 名  : PPP_Shell_ReceiveCcpUpFromCore
 功能描述  : 从Core收到CCP UP事件处理
 输入参数  :
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月7日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_Shell_ReceiveCcpUpFromCore(PPPINFO_S *pstPppInfo)
{
    VOS_UINT32 ulResult = 0;
    PPP_CCP_INFO_S* pstCcpInfo = VOS_NULL_PTR;
    UCHAR ucDmpuId = 0;
    UCHAR ucDpeId = 0;


    pstCcpInfo = (PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo;
    if (VOS_NULL_PTR == pstCcpInfo)
    {
         return VOS_ERR;
    }

    switch(pstCcpInfo->ucPppCompType)
    {
        case PPPCOMP_MPPC:
        {
            /* 选择子卡及子卡的DPEID */
            if (MAX_DMPU_ID <= pstPppInfo->ucDmpuId)
            {
                ulResult = (VOS_UINT32)PPP_CompSelectDmpuDpe(&ucDmpuId, &ucDpeId);
                if (VOS_OK != ulResult)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_600);
                    return VOS_ERR;
                }

                ulResult = (VOS_UINT32)PPP_CompCheckMppcUserNum(&ucDmpuId);
                if(VOS_OK != ulResult)
                {
                     /* 子卡不在位，或用户数也已经达到上限，则终止CCP */
                     PPP_DBG_ERR_CNT(PPP_PHERR_601);
                     return VOS_ERR;
                }

                pstPppInfo->ucDmpuId = ucDmpuId;
                pstPppInfo->ucDpeId  = ucDpeId;
            }

            if((VOS_FALSE == pstPppInfo->bMppcFlag) && (VOS_TRUE == pstPppInfo->bVjFlag))
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1329);
            }
            /* END of liushuang */

            PPP_DBG_OK_CNT(PPP_PHOK_1330);
            PPP_CompUserNumAdd(pstPppInfo, PPP_USERSTAT_MPPC);
            break;
        }
        case PPPCOMP_LZS0:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1331);
            PPP_CompUserNumAdd(pstPppInfo, PPP_USERSTAT_ZLS0);
            break;
        }
        case PPPCOMP_LZS1:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1332);
            PPP_CompUserNumAdd(pstPppInfo, PPP_USERSTAT_ZLS1);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_602);
            PPPC_INFO_LOG1(
                      "\r\n [ppp]PPP_Shell_ReceiveCcpUpFromCore: Unknow compress type %d",
                      pstCcpInfo->ucPppCompType);
            return VOS_ERR;
        }
    }

    if (VOS_OK != PPP_SendUserInfo(pstPppInfo, SCP_INFOR))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_603);
        return VOS_ERR;
    }

    /* 性能统计 */
    PPP_PerfInc(&g_stPppPerfStatistic.ulCcpSuccess, PERF_TYPE_PPPC_CCP_NEGO_SUCC, pstPppInfo->bEhrpdUser);


    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_Shell_ReceiveCcpDownFromCore
 功能描述  : 从Core收到CCP Down事件处理
 输入参数  :
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月7日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_Shell_ReceiveCcpDownFromCore(PPPINFO_S *pstPppInfo)
{

    if (pstPppInfo->bMppcFlag)
    {
        PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_MPPC);
        PPP_DBG_OK_CNT(PPP_PHOK_1333);
    }
    if (pstPppInfo->bLzs0Flag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1334);
        PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_ZLS0);
    }
    if (pstPppInfo->bLzs1Flag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1335);
        PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_ZLS1);
    }


    /* BEGIN: Added for PN:备份代码检视 by wangyong 00138171, 2013/11/22 */
    if (PPPA11DOWNNOLCPTER == pstPppInfo->bFailFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1336);
    }
    /* END:   Added for PN:备份代码检视 by wangyong 00138171, 2013/11/22 */
#if 0
    /* 通知A11更新上下文及A10表 */
    (VOID)A11_PPPC_SendUsrInfor(pstPppInfo->ulRPIndex,
                        &stUsrinfo,
                        SCP_INFOR);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : PPP_Shell_ReceiveFreePeerIpFromCore
 功能描述  : 从内核接收事件的接口函数
 输入参数  : pstPppInfo:PPP控制块
             ulCmd:命令字
             pPara:事件的参数
 输出参数  : 无
 返 回 值  : VOS_OK;VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2000-04-04
    作    者   : Deng Yi Ou
    修改内容   :

*****************************************************************************/
VOS_UINT32 PPP_Shell_ReceiveEventFromCore(PPPINFO_S *pstPppInfo,
                                     VOS_UINT32      ulCmd,
                                     CHAR *     pPara)
{
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL_PTR;
    VOS_UINT32 ulResult = VOS_OK;
    VOS_UINT32 ulPdnIndex = 0;

    PPPC_INFO_LOG1(
        "\r\n [ppp]PPP_Shell_ReceiveEventFromCore: Enter ulCmd: %d", ulCmd);

    if (!pstPppInfo || (ulCmd >= PPP_EVENT_CTSEND))
    {
        return VOS_ERR;
    }

    switch (ulCmd)
    {
        case PPP_LCP_UP:
        {
            /* 下发LCP用户信息*/
            ulResult = PPP_Shell_ReceiveLcpUpFromCore(pstPppInfo);
            break;
        }

        case PPP_LCP_DOWN:
        {
            PPP_Shell_ReceiveLcpDownFromCore(pstPppInfo);
            break;
        }

        case PPP_IPCP_UP:
        {
            ulResult = PPP_Shell_ReceiveIpcpUpFromCore(pstPppInfo);
            break;
        }

        case PPP_IPCP_DOWN:
        {
            /* 稳态连接标记置失败 */
            pstPppInfo->bPppStateFlg = PPP_STATE_FAIL;

            break;
        }

        case PPP_IPV6CP_UP:
        {
            ulResult = PPP_Shell_ReceiveIpV6cpUpFromCore(pstPppInfo);
            break;
        }

        case PPP_IPV6CP_DOWN:
        {
            /* 稳态连接标记置失败 */
            pstPppInfo->bPppStateFlgV6 = PPP_STATE_FAIL;


            /*获取rp上下文*/
            ulResult = (VOS_UINT32)SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (VOID**)&pstRpContext);
            if ((SDB_SUCCESS != ulResult) || (VOS_NULL_PTR == pstRpContext))
            {
                break;
            }

            ulPdnIndex = (VOS_UINT32)pstRpContext->ausPdnIndexArray[0];

            /*获取PDN上下文*/
            ulResult = (VOS_UINT32)SDB_GetPdnContextByIndex(ulPdnIndex, (VOID**)&pstPdnContext);
            if ((SDB_SUCCESS != ulResult) || (VOS_NULL_PTR == pstPdnContext))
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_604);
                break;
            }

            /* 停止IPv6定时器，不再发生RA消息 */
            ulResult = IPV6_StopTimer(pstPdnContext->ulIpv6Timer);
            if (VOS_OK != ulResult)
            {
               /* 增加调试信息，但不退出 */
               PPP_DBG_ERR_CNT(PPP_PHERR_605);
            }
            pstPdnContext->ulIpv6Timer = 0;

            break;
        }
        /* BEGIN: Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */
        case PPP_VSNCP_UP:
        {
            ulResult = PPP_Shell_ReceiveVSNCPUpFromCore(pstPppInfo);
            break;
        }
        case PPP_VSNCP_DOWN:
        {
            /* 稳态连接标记置失败 */
            break;
        }
        /* END:   Added for PN:PDSN融合 by wangyong 00138171, 2013/1/19 */
        case PPP_CCP_UP:
        {
            ulResult = PPP_Shell_ReceiveCcpUpFromCore(pstPppInfo);
            break;
        }
        case PPP_CCP_DOWN:
        {
            PPP_Shell_ReceiveCcpDownFromCore(pstPppInfo);
            break;
        }
        default:
            break;
    }

    return ulResult;
}
/*****************************************************************************
 函 数 名  : PPP_Shell_GetPacketFromCore
 功能描述  : 内核发送报文函数
 输入参数  : pstPppInfo:PPP控制块
             pPacket:字符数组形式存在的报文
             ulLen:报文长度
             usProtocol:PPP协议号
 输出参数  : 无
 返 回 值  : VOS_OK;VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2000-04-04
    作    者   : Deng Yi Ou
    修改内容   :

*****************************************************************************/
VOS_UINT32 PPP_Shell_GetPacketFromCore(CHAR * pstPppInfo,
                                  UCHAR* pHead,
                                  UCHAR* pPacket,
                                  VOS_UINT32  ulLen,
                                  VOS_UINT16 usProtocol)
{
    PMBUF_S *pMbuf = VOS_NULL_PTR;
    VOS_UINT32 ulRetCode = 0;

    PPPC_INFO_LOG(  "\r\n [ppp]PPP_Shell_GetPacketFromCore: Enter");

    if (VOS_NULL_PTR == pstPppInfo)
    {
        return VOS_ERR;
    }

    ShowCode(pPacket, (VOS_UINT16)ulLen);

    /* 报文情况 */
    /*
     |------------- PPP_RESERVED_PACKET_HEADER ----------|
     |                   |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |       ...         |       |       |       |       |  Data ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |                                                   |
    pHead                                               pPacket
     */

    /* 消息跟踪 */
    PPP_OmMsgTrc(((PPPINFO_S*)pstPppInfo)->ulRPIndex, usProtocol, pPacket, ulLen, PPP_TRACE_OUT,
                 0, &(((PPPINFO_S*)pstPppInfo)->stIMSI), ((PPPINFO_S*)pstPppInfo)->bEhrpdUser);

    /* 创建MBUF */
    pMbuf = (PMBUF_S *)PMBUF_GetPMbuf(MID_PPPC, ulLen);
    if (VOS_NULL_PTR == pMbuf)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_606);
        PPPC_INFO_LOG(
                     "\r\n [ppp]PPP_Shell_GetPacketFromCore: PMBUF_GetMbuf is NULL!");
        return VOS_ERR;
    }

    ulRetCode = PMBUF_CopyDataFromBufferToPMBuf(pMbuf,
                                              0,
                                              ulLen,
                                              (UCHAR *)pPacket,
                                              MID_PPPC);
    if (VOS_OK != ulRetCode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_607);
        (VOS_VOID)PMBUF_Destroy(pMbuf);
        PPPC_INFO_LOG(
                     "\r\n [ppp]PPP_Shell_GetPacketFromCore: MBUF_CopyDataFromBufferToMBuf fail!");
        return VOS_ERR;
    }

    /* 性能统计:发送协商报文总数 */
    PPP_PerfInc(&g_stPppPerfStatistic.ulSendNego, PERF_TYPE_PPPC_SEND_NEGO_PKT_NUM, ((PPPINFO_S*)pstPppInfo)->bEhrpdUser);

    /* PPPC发送及回复协商报文时，不使用HDLC硬件封装 */
#if 0 /*(FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)*/
    return PPPC_HDLC_HARD_ProcProtocolPacket(((PPPINFO_S *)pstPppInfo)->ulRPIndex, pMbuf, 0, usProtocol);
#else
    return PPP_Shell_SendPacketToISL((PPPINFO_S *)pstPppInfo, pMbuf, usProtocol);
#endif
}


/*****************************************************************************
 函 数 名  : PPP_Shell_ReceiveNegoPacket
 功能描述  : 接收协商报文函数,
 输入参数  : pMbuf:报文
 输出参数  : 无
 返 回 值  : VOS_OK;VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2000-04-04
    作    者   : Deng Yi Ou
    修改内容   :

*****************************************************************************/
VOS_UINT32 PPP_Shell_ReceiveNegoPacket(PMBUF_S *pMbuf, VOS_UINT8 ucPppId)
{
    VOS_UINT32 ulLen = 0;
    VOS_UINT32 ulOffset = 0;
    UCHAR *pHead = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    UCHAR ucLcpTerminateFlg = VOS_FALSE;
    CTTF_PPPC_TRACE_DATA_STRU *pstMntnInfo  = VOS_NULL_PTR;


    PPPC_INFO_LOG(  "\r\n [ppp]PPP_Shell_ReceiveNegoPacket: Enter");

    PPPC_INFO_LOG1(
                  "\r\n [ppp]PPP_Shell_ReceiveNegoPacket: ReceiveNego: %d", g_stPppPerfStatistic.ulReceiveNego);

    if (VOS_NULL_PTR == pMbuf)
    {
        /* 性能统计:无效协商报文数*/

        PPPC_INFO_LOG1(
                      "\r\n [ppp]PPP_Shell_ReceiveNegoPacket: ReceiveNegoErr: %d", g_stPppPerfStatistic.ulReceiveNegoErr);

        PPP_DBG_ERR_CNT(PPP_PHERR_608);
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ucPppId);

    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_INFO_LOG2(
                      "\r\n [ppp]PPP_Shell_ReceiveNegoPacket: ReceiveNegoErr: %d, User %d isn't exist!",
                      g_stPppPerfStatistic.ulReceiveNegoErr, ucPppId);

        PPP_DBG_ERR_CNT(PPP_PHERR_611);
        return VOS_ERR;
    }

    pstPppInfo->bIsAsync = pstPppInfo->bSynAsyConvert;
    if (pstPppInfo->bSynAsyConvert && pstPppInfo->pstLcpInfo)
    {
        ((PPPLCPINFO_S *)pstPppInfo->pstLcpInfo)->stWantOptions.neg_asyncmap  = 1;
        ((PPPLCPINFO_S *)pstPppInfo->pstLcpInfo)->stAllowOptions.neg_asyncmap = 1;
    }

    ulLen = PMBUF_GET_TOTAL_DATA_LENGTH(pMbuf);

    /* 可维可测 */
    pstMntnInfo = (CTTF_PPPC_TRACE_DATA_STRU *)PPP_Malloc(
                   PPPC_OM_TRANS_DATA_OFFSET_LEN + ulLen);
    if (VOS_NULL_PTR != pstMntnInfo)
    {
        PS_MEM_SET(pstMntnInfo, 0, PPPC_OM_TRANS_DATA_OFFSET_LEN + ulLen);
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = MSPS_PID_PPPC;
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;

        if (PPPC_RAT_MODE_1X == PPPC_GetRatMode())
        {
            pstMntnInfo->ulSenderPid     = MSPS_PID_1X_FRLP;
            pstMntnInfo->enMsgId         = ID_CTTF_1X_PPPC_TRACE_DATA_NEGO_DL;
            pstMntnInfo->enRatMode       = PPPC_RAT_MODE_1X;
            /* 收到的PPP协商报文数加一 */
            PPPC_1X_IncreaseNegoRcvCnt();
        }
        else
        {
            pstMntnInfo->ulSenderPid     = CTTF_PID_HRPD_FPA;
            pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_NEGO_DL;
            pstMntnInfo->enRatMode       = PPPC_GetRatMode();
            pstMntnInfo->ucStreamNum     = PPPC_HRPD_GetStreamNumber(ucPppId);
            /* 收到的PPP协商报文数加一 */
            PPPC_HRPD_IncreaseNegoRcvCnt();
        }

        pstMntnInfo->ulLength        = ulLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PMBUF_CopyDataFromPMBufToBuffer(pMbuf, 0, ulLen, pstMntnInfo->aucValue);

        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        PPP_Free(pstMntnInfo);

        (VOS_VOID)pstMntnInfo;

        pstMntnInfo = VOS_NULL_PTR;
    }

    if (ulLen > PPP_DEFAULT_NEGO_PACKET_LEN)
    {
        PPPC_WARNING_LOG2(
                  "[ppp]: ReceiveNegoErr: %d, ulLength %d is too long!",
                  g_stPppPerfStatistic.ulReceiveNegoErr, ulLen);

        return VOS_OK;
    }

    /* 预留出打PPP报文头的空间 */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /*mode by z0012969 for c05 性能优化*/
    pHead = g_ucPppRcvPacketHead;
    PPP_MemSet((void *)g_ucPppRcvPacketHead, 0,  PPP_DEFAULT_NEGO_PACKET_LEN+PPP_RESERVED_PACKET_HEADER);

    (VOID)PMBUF_CopyDataFromPMBufToBuffer(pMbuf, 0, ulLen, pHead + ulOffset);

    /* BEGIN: Added for PN:DTS2013111600091 备板不处理数据面承载信令的去活，主板平滑时按照OM去活释放 by y00170683, 2013/11/19 */
    PPP_CheckIsLcpTerminateMsg(pstPppInfo, pHead + ulOffset, ulLen, &ucLcpTerminateFlg);
    /* END:   Added for PN:DTS2013111600091 备板不处理数据面承载信令的去活，主板平滑时按照OM去活释放 by y00170683, 2013/11/19 */

    /* 交给内核处理 */
    PPP_Core_ReceivePacketFromShell(pstPppInfo, pHead, pHead + ulOffset, ulLen);
    (VOS_VOID)pstMntnInfo;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : PPP_Shell_ISLIoCtl
功能描述  : 从底层接收事件的接口函数
输入参数  : USM_LAP2_MSG_S* pstMsg
输出参数  : pstPppInfo:PPPC控制块指针
            ulCmd:命令字,可以为如下值:
                  ISLUP:底层UP
                  ISLDOWN:底层DOWN                                                          ISPCFSWITCH:BS/PCF切换
                  ISLRENEGO:底层重协商
                  PPPC_L2TPUP:L2TP发送给PPP的UP事件
                  PPPC_L2TPDOWN:L2TP发送给PPP的DOWN事件
            pPara:事件的参数,一般情况下为NULL
                  L2TP的LNS端报ISLUP时，则是预协商结果
返 回 值  : VOS_OK;VOS_ERR
调用函数  :

被调函数  :

修改历史     :
1.日    期   : 2000年04月04日
  作    者   : Deng Yi Ou
  修改内容   : 新生成函数
2.日    期   : 2012年10月22日
  作    者   : luofang
  修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_Shell_ISLIoCtl(VOS_UINT32 ulRPIndex, VOS_UINT32 ulCmd, char *pPara)
{
    VOS_UINT32 ulA10Index  = 0;
    VOS_UINT32 ulReRpIndex = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S* pstIpcpInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S* pstIpv6cpInfo = VOS_NULL_PTR;
    PPP_CCP_INFO_S* pstCcpInfo = VOS_NULL_PTR;
    PPPRENOGOINFO stPppRenegoInfo = {0};


    PPPC_INFO_LOG2(  "\r\n [ppp]PPP_Shell_ISLIoCtl: Enter ulRPIndex %u, ulCmd %d", ulRPIndex, ulCmd);

    if (!(ulRPIndex <= PPP_MAX_USER_NUM)
        || (ulCmd >= ISLTUEND))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_615);
        return VOS_ERR;
    }

    switch (ulCmd)
    {
        case PPP_ISLDOWN:
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1337);

            GETPPPINFOPTRBYRP(pstPppInfo, ulRPIndex);

            if (VOS_NULL_PTR != pstPppInfo)
            {
                /* SNMP新需求: 设置性能统计原因值: pcf主动去活 */
                PPP_SNMP_PERF_SET_FAILREASON_PCF_RELEASE(pstPppInfo, pstPppInfo->pulCurrFsm);

                /* PPP协商过程中，收到PCF的释放请求 将“分组会话激活请求数”减1 */
                A11_ReqNumSubProc(pstPppInfo);
                PPP_DBG_OK_CNT(PPP_PHOK_1338);

                PPP_Core_ReceiveEventFromShell(pstPppInfo, (VOS_UINT32)PPPISLDOWN, VOS_NULL_PTR);
                (VOID)PPP_DeleteCB(pstPppInfo, PS_TRUE);

                PPPC_DeletePppId((VOS_UINT8)pstPppInfo->ulRPIndex);
                PPP_DBG_OK_CNT(PPP_PHOK_1339);
            }
            else
            {
                PPPC_INFO_LOG1(
                        "\r\n [ppp]PPP_Shell_ISLIoCtl: PPPINFO index %d IS NULL!", ulRPIndex);

                return VOS_ERR;
            }
            break;
        }

        case ISPCFSWITCH:
        {
            if (VOS_NULL_PTR == pPara)
            {
                return VOS_ERR;
            }

            GETPPPINFOPTRBYRP(pstPppInfo, ulRPIndex);
            if (VOS_NULL_PTR != pstPppInfo)
            {
                /* 更新RP INDEX */
                VOS_MemCpy(&g_astPppPool[*(VOS_UINT32*)pPara], pstPppInfo, sizeof(PPPINFO_S));

                g_astPppPool[*(VOS_UINT32*)pPara].ulRPIndex = *(VOS_UINT32*)pPara;
                g_astPppPool[ulRPIndex].usState = PPP_CB_STATE_FREE;
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_617);
                PPPC_INFO_LOG(
                            "\r\n [ppp]PPP_Shell_ISLIoCtl: ISPCFSWITCH: PPPINFO IS NULL!");
                return VOS_ERR;
            }
            break;
        }
        case ISLRENEGO:
        {
            /*底层上报的PPP协商报文中是A10Index，需要转换成RpIndex，为了保持接口统一，
            这里还是使用ulRPIndex做为入参，其中保存的值为底层带上来的A10Index*/
            ulA10Index = ulRPIndex;
#if 0
            enReturn = (VOS_UINT32)SDB_GetRpContextByA10Index(ulA10Index,
                                                         (VOS_UINT32*)&ulReRpIndex,
                                                         (UCHAR**)&pstRpContext);
            if ((enReturn != SDB_SUCCESS) || (VOS_NULL_PTR == pstRpContext))
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_618);
                PPP_ERROR_COUNTER(PPP_ERROR_COUNTER008);
                return VOS_ERR;
            }
#endif
            PPP_DBG_OK_CNT(PPP_PHOK_1340);

            PPPC_INFO_LOG1(
                         "\r\n [ppp]PPP_Shell_ISLIoCtl: NP notify user %u RENEGO", ulReRpIndex);
            /*lint -e774*/
            GETPPPINFOPTRBYRP(pstPppInfo, ulReRpIndex);
            /*lint +e774*/
            if (VOS_NULL_PTR != pstPppInfo)
            {
                pstIpcpInfo = (PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo;
                pstIpv6cpInfo = (PPPIPV6CPINFO_S*)pstPppInfo->pstIpV6cpInfo;
                pstCcpInfo = (PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo;

                PPP_DBG_OK_CNT(PPP_PHOK_1341);

                PPP_MemSet((VOID*)&stPppRenegoInfo, 0, sizeof(stPppRenegoInfo));

                if ( (pstIpcpInfo&&(PPP_STATE_OPENED == pstIpcpInfo->stFsm.ucState))
                    || ((pstIpv6cpInfo) && (PPP_STATE_OPENED == pstIpv6cpInfo->stFsm.ucState)))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_1342);

                    if (pstIpcpInfo)
                    {
                        pstPppInfo->bReNego = 1;
                        stPppRenegoInfo.ucIpcpFlag = 1;
                        (VOID)VOS_MemCpy((VOID*)&stPppRenegoInfo.stIpcpOptions, (VOID*)&pstIpcpInfo->stGotOptions,
                        sizeof(PPP_IPCP_OPTION_S));
                    }
                    if (pstIpv6cpInfo)
                    {
                        pstPppInfo->bReNegoV6 = 1;
                        stPppRenegoInfo.ucIpV6cpFlag = 1;
                        (VOID)VOS_MemCpy((VOID*)&stPppRenegoInfo.stIpcpV6Options, (VOID*)&pstIpv6cpInfo->stGotOptions,
                        sizeof(PPP_IPV6CP_OPTION_S));
                    }

                    /* 通用处理无论是否双栈用户 */
                    if (pstCcpInfo && (PPP_STATE_OPENED == pstCcpInfo->stFsm.ucState))
                    {
                        stPppRenegoInfo.ucCcpFlag = 1;
                        (VOID)VOS_MemCpy((VOID*)&stPppRenegoInfo.stCcpOptions, (VOID*)&pstCcpInfo->stGotOptions,
                        sizeof(PPP_CCP_options_S));
                    }

                    M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_LCP);
                    //(VOID)PPP_NodeDelete(ulReRpIndex);
                    (VOID)PPP_NodeAdd(ulReRpIndex, 0, PPP_NEGO_LIST_NODE_LCP_START);

                    if (VOS_NULL_PTR == pstPppInfo->pstPppRenegoInfo)
                    {
                        pstPppInfo->pstPppRenegoInfo = (PPPRENOGOINFO *)PPP_Malloc(sizeof(PPPRENOGOINFO));
                        if(VOS_NULL_PTR == pstPppInfo->pstPppRenegoInfo )
                        {
                            PPP_DBG_ERR_CNT(PPP_PHERR_619);
                            (VOID)vos_printf("\r\n PPP_Shell_ISLIoCtl PPP_Malloc Failed!~!!");
                            return VOS_ERR;
                        }
                        PPP_MemSet((void*)pstPppInfo->pstPppRenegoInfo, 0, sizeof(PPPRENOGOINFO));
                    }

                    if (VOS_NULL_PTR != pstPppInfo->pstPppRenegoInfo)
                    {
                        (VOID)VOS_MemCpy(pstPppInfo->pstPppRenegoInfo, (VOID*)&stPppRenegoInfo,
                        sizeof(PPPRENOGOINFO));
                    }

                    PPP_DBG_OK_CNT(PPP_PHOK_1343);
                    pstPppInfo->bPpcAAAFlag = 0;

                    PPP_Core_ReceiveEventFromShell(pstPppInfo, PPPISLRENEGO, VOS_NULL_PTR);
                }
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_620);
                PPPC_INFO_LOG(
                             "\r\n [ppp]PPP_Shell_ISLIoCtl: ISLRENEGO: PPPINFO IS VOS_NULL_PTR!");
                return VOS_ERR;
            }
            break;
        }
        default:
            break;
    }
    (VOS_VOID)ulA10Index;
    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：向底层发送报文,调用本函数前最好在Mbuf中预留出PPP报文头空间 *
* MODIFY DATE  ：modified by gxf for GGSN80 20030218                        *
* INPUT        ：pstPppInfo:PPP控制块                                       *
*                pMbuf:MBUF形式存在的报文                                   *
*                usProtocol:PPP协议号                                       *
* OUTPUT       ：                                                           *
* RETURN       ：VOS_OK:成功;VOS_ERR:失败                                   *
* CALLED BY    ：PPP_Shell_GetPacketFromCore、PPP_Shell_NiOutput、          *
*                MP_Transmit                                                *
****************************************************************************/
VOS_UINT32 PPP_Shell_SendPacketToISL(PPPINFO_S *pstPppInfo,
                               PMBUF_S *   pMbuf,
                               VOS_UINT16     usProtocol)
{
    /* 报文情况 */

    /*
    |--------PPP Head(bytes) -------|
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |       |       |       |       |  Data ...
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |
                                  pMbuf->pData
    */
    UCHAR* pBuf = VOS_NULL_PTR;
    VOS_UINT32 ulResult;
    VOS_UINT32 ulHeadLen;
    PPPLCPINFO_S* pstLcpInfo = VOS_NULL_PTR;

    PPPC_INFO_LOG3(
                "\r\n PPP_Shell_SendPacketToISL: enter pstPppInfo=0x%x, pMbuf = 0x%x, usProtocol = 0x%x",
                pstPppInfo, pMbuf, usProtocol);

    if (VOS_NULL_PTR == pMbuf)
    {
        return VOS_ERR;
    }

    if ((VOS_NULL_PTR == pstPppInfo) || (VOS_NULL_PTR == pstPppInfo->pstLcpInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_621);
        /* Added start by gaofeng 00127633 at 2008-07-08 PDSN V9R7C01B025 for 检视 */
        (VOS_VOID)PMBUF_Destroy(pMbuf);
        /* Added end by gaofeng 00127633 at 2008-07-08 PDSN V9R7C01B025 for 检视 */
        return VOS_ERR;
    }

    /* 获得报文指针 */
    pBuf = (UCHAR*)PMBUF_MTOD(pMbuf, CHAR *);

    pstLcpInfo = (PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo);

   /* 增加报文长度 */
   if ((pstPppInfo->bIsAsync)
       && ((usProtocol == PPP_LCP) || !(pstLcpInfo->stHisOptions.neg_accompression)))
   {
       ulHeadLen = PPP_HDRLEN;
   }
   else
   {
       ulHeadLen = PPP_HDRLEN - 2; /* 去掉ff03 */
   }

   /*Begin WGGSN_B03_L2TP_PPPC_COMP*/
   /* 对协议域压缩的处理 */
   if (((usProtocol == PPP_IP)
        || (usProtocol == PPP_SCP)) && (pstLcpInfo->stHisOptions.neg_pcompression))
   {
       ulHeadLen -= 1;
   }

   /*End WGGSN_B03_L2TP_PPPC_COMP*/

   PMBUF_PREPEND_MEMORY_SPACE(pMbuf, ulHeadLen, MID_PPPC, ulResult);

   if (ulResult == 0)
   {
       /* ok */
       if (pMbuf == VOS_NULL_PTR)
       {
           PPP_DBG_ERR_CNT(PPP_PHERR_622);
           PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_Shell_SendPacketToISL: Mbuf is NULL!");
           return VOS_ERR;
       }
   }
   else
   {
       PPP_DBG_ERR_CNT(PPP_PHERR_623);
       /* failed */
       PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "MBUF_PREPEND_MEMORY_SPACE Err!!");
       (VOS_VOID)PMBUF_Destroy(pMbuf);
       return VOS_ERR;
   }

   /* 获得报文指针 */
   pBuf = (UCHAR*)PMBUF_MTOD(pMbuf, CHAR *);

   /* 报文情况 */

   /*
    |--------PPP Head(bytes) -------|
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |       |       |       |       |  Data ...
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |
   pMbuf->pData
   pBuf
    */

   /* 打PPP报文头 */
   /*PPP_MAKEHEADER(pBuf, usProtocol) ;*/
   if (pstPppInfo->bIsAsync
       && ((usProtocol == PPP_LCP) || !(pstLcpInfo->stHisOptions.neg_accompression)))
   {
       PPP_PUTCHAR(PPP_ALLSTATIONS, pBuf);
       PPP_PUTCHAR(PPP_UI, pBuf);
   }

   /*Begin WGGSN_B03_L2TP_PPPC_COMP*/
   /* 对协议域压缩的处理 */
   if (((usProtocol == PPP_IP)
        || (usProtocol == PPP_SCP)) && (pstLcpInfo->stHisOptions.neg_pcompression))
   {
       PPP_PUTCHAR(usProtocol, pBuf);
   }
   else
   {
       PPP_PUTSHORT(usProtocol, pBuf);
   }

   /*End WGGSN_B03_L2TP_PPPC_COMP*/


   /* 报文情况 */

   /*
    |--------PPP Head(bytes) -------|
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |  ff   |   03  |    protocol   |  Data ...
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                               |
   pMbuf->pData                    |
                                   pBuf
    */

   /* 同/异步转换 */
   if (pstPppInfo->bSynAsyConvert)
   {
        /* 早期PPP协议RFC1661中LCP配置选项无ACCM选项，所有LCP报文不做异步映射 */
       pMbuf = PPP_SynToAsy(pMbuf,
                (usProtocol == PPP_LCP ? 0x00000000 : pstPppInfo->ulRemoteAccm));
       if (pMbuf == VOS_NULL_PTR)
       {
           PPP_DBG_ERR_CNT(PPP_PHERR_624);
           PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Syn To Asy Error!!");
           return VOS_ERR;
       }
   }

   if (1 == pstPppInfo->bPppClient)
   {
       /* 发送报文 */
       ulResult = PPPC_ULSendNegoFrame(pMbuf, pstPppInfo->ulRPIndex);

#ifdef PPPC_ST
       ulResult =VOS_OK;
#endif

        if (VOS_ERR == ulResult)
        {
           PPP_DBG_ERR_CNT(PPP_PHERR_625);
           PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Send Packet Fail!!");
           return VOS_ERR;
        }
    }
    else
    {
       /* 释放pMbuf */
        PMBUF_Destroy(pMbuf);
        PPP_DBG_ERR_CNT(PPP_PHERR_867);
        PPPC_WARNING_LOG1(
                    "\r\n PPP_Shell_SendPacketToISL: PPP mode err not client %d", pstPppInfo->bPppClient);
    }
    (VOS_VOID)pMbuf;
    (VOS_VOID)pBuf;
    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPP_Shell_ReceiveAAAResult
 功能描述  : PPP收到AAA回复的鉴权消息
 输入参数  : AAA_AUTHRSP_S *pstMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_Shell_ReceiveAAAResult(AAA_AUTHRSP_S *pstMsg)
{
#if 0
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    UCHAR ucValid = 0;
    VOS_UINT32 ulIndex = 0;
    VOS_UINT32 ulResult = 0;
    USM_PPP_LINKUP_RESULT_S stMsg ={0};  /* PPP Link up 通知USM的消息结构体 */
    /*入参检查*/
    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_INFO_LOG( "\r\nPPP_Shell_ReceiveAAAResult Input para null!");
        return ;
    }

    ulIndex = pstMsg->ulSDBIndex;
    GETPPPINFOPTRBYRP(pstPppInfo, ulIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_626);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER023);
        PPPC_INFO_LOG(  "\r\n PPP_Shell_ReceiveAAAResult: User %d isn't exist!", ulIndex);
        return;
    }

    if (pstMsg->ulMsgType != AAA_PPPC_CREAT_RSP)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_627);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER022);
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP ReceiveAAAResult: Msg Type Error!!");
        return;
    }

    ucValid = ((VOS_NULL_PTR == pstPppInfo->pstPapInfo)
          || ((PPPPAPINFO_S*)pstPppInfo->pstPapInfo)->ucServerState != PAP_STATE_WAIT_AAA)
          && ((VOS_NULL_PTR == pstPppInfo->pstChapInfo)
          || ((PPPCHAPINFO_S*)pstPppInfo->pstChapInfo)->ucServerState != CHAP_STATE_WAITING_AAA);
    if (ucValid)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_628);
        PPPC_INFO_LOG(  "\r\n PPP_Shell_ReceiveAAAResult: User %d state is wrong.", ulIndex);
        return;
    }

    /*认证成功*/
    if (VOS_OK == pstMsg->ucResult)
    {
        /* 如果AAA下发隧道类型非 L2TP,软参开启则去活用户 */
        ucValid = ((TUNNEL_L2TP != pstMsg->usTunnelType[0]) && (0 != pstMsg->usTunnelType[0]))
                &&(VOS_TRUE == SOFTPARA_BIT1478);
        if(ucValid)
        {
            /* 去活用户 */
            PPP_DBG_ERR_CNT(PPP_PHERR_629);
            PPP_CHAP_DeleteTimer(pstPppInfo);
            PPP_PAP_DeleteTimer(pstPppInfo);
            PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_L2TPTUNLPARA_ERR);
            PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
            return;
        }

        /*调用 PDN_CheckL2tpUser()函数判断*/
        ulResult = PDN_CheckL2tpUser(pstPppInfo->usCDBIndex,pstMsg);
        /*如果是L2TP用户，直接通知USM*/
        if(VOS_OK == ulResult)
        {
            /* 填充发给USM的消息结构体 */
            stMsg.pucMsg = (UCHAR *)pstMsg;
            stMsg.ulRpIndex = pstPppInfo->ulRPIndex;
            stMsg.usDomainIndex = pstPppInfo->usCDBIndex;
            stMsg.usVirtualDomainIndex = pstPppInfo->usVirtualDomainIdx;
            VOS_MemCpy(stMsg.aucNAI, pstPppInfo->ucNAI, NAI_NAME_LEN + 1);

            (VOID)USM_NotifyPhaseResultFunc(pstPppInfo->ulRPIndex,
                                          E_USM_MSGTYPE_PPP2USM_SETUP,
                                          (UCHAR *)&stMsg);
            PPP_CHAP_DeleteTimer(pstPppInfo);
            PPP_PAP_DeleteTimer(pstPppInfo);
            return;
        }

    }
    else
    {
        /* AUTH模块返回失败时，将“分组会话激活请求数”减1*/
        switch(pstMsg->ucResult)
        {
            case AAA_AUTH_FAIL:
            {
                SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);

                A11_ReqNumSubProc(pstPppInfo);
                PPP_DBG_ERR_CNT(PPP_PHERR_630_AUTH_FAIL);

                break;
            }
            case AAA_AUTH_SRV_ERR:
            {
                SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_AAA_NO_RSP);

                A11_ReqNumSubProc(pstPppInfo);

                PPP_DBG_ERR_CNT(PPP_PHERR_631);
                break;
            }
            default:
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_632);
                break;
            }
        }
    }

    /*否则，回复鉴权消息.然后在PPP_Core_NetworkPhase函数中
    区分免认证、重协商和正常流程，再通知USM*/
    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_633);
        PPPC_INFO_LOG(
                   "\r\n PPP_Shell_ReceiveAAAResult:pstLcpInfo null");
        return;
    }

    /* 到chap\pap模块处理 */
    if (pstLcpInfo->stGotOptions.neg_chap)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1344);
        PPP_CHAP_ReceiveAAAResult(pstMsg);
    }
    if (pstLcpInfo->stGotOptions.neg_upap)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1345);
        PPP_PAP_ReceiveAAAResult(pstMsg);
    }

    PPPC_INFO_LOG( "\r\n PPP_Shell_ReceiveAAAResult success !");
#endif
    return;
}


/****************************************************************************
* CREATE DATE  ：2009-03-20                                                 *
* CREATED BY   ：c00127007                                                  *
* FUNCTION     :                                                            *
* MODIFY DATE  ：                                                           *
* INPUT        ：PPPINFO_S* pstPppInfo                                      *
*                VOS_UINT32 ulType                                               *
* OUTPUT       ：                                                           *
* RETURN       ：VOID                                                       *
* CALLED BY    ：PPP_SendUserInfo                                           *
****************************************************************************/
VOID PPP_SendLcpPreProc(PPPINFO_S* pstPppInfo, A11_PPPC_USR_INFOR_S *pstUsrinfo)
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    pstLcpInfo = (PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo);

    /* 下发协商结果给A11 */
    pstUsrinfo->usMtu  = pstPppInfo->usMtu;
    pstUsrinfo->ulAccm = (pstPppInfo->ulLocalAccm | pstPppInfo->ulRemoteAccm);
    pstUsrinfo->ulMagicNum = pstLcpInfo->stGotOptions.magicnumber;
    pstUsrinfo->ulRpIndex = pstPppInfo->ulRPIndex;

    /* 同步异步标志 */
    pstUsrinfo->ucPPPMode |= (pstPppInfo->bSynAsyConvert ? A11_PPP_FLAG_SYNASY : 0);

    /* 终结续传标志 */
    pstUsrinfo->ucPPPMode |= (pstPppInfo->bPppMode ? A11_PPP_FLAG_MODE : 0);

    pstUsrinfo->ucPPPMode |= (pstLcpInfo->stHisOptions.neg_pcompression ? A11_PPP_FLAG_PFC : 0);
    pstUsrinfo->ucPPPMode |= (pstLcpInfo->stHisOptions.neg_accompression ? A11_PPP_FLAG_ACFC : 0);

    return;
}

/****************************************************************************
* CREATE DATE  ：2009-03-20                                                 *
* CREATED BY   ：c00127007                                                  *
* FUNCTION     :                                                            *
* MODIFY DATE  ：                                                           *
* INPUT        ：PPPINFO_S* pstPppInfo                                      *
*                VOS_UINT32 ulType                                               *
* OUTPUT       ：                                                           *
* RETURN       ：VOID                                                       *
* CALLED BY    ：PPP_SendUserInfo                                           *
****************************************************************************/
VOID PPP_SendIpcpPreProc(PPPINFO_S* pstPppInfo, A11_PPPC_USR_INFOR_S *pstUsrinfo)
{
     PPPIPCPINFO_S*  pstIpcpInfo = (PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo);
     PPP_CCP_INFO_S* pstCcpInfo  = (PPP_CCP_INFO_S*)(pstPppInfo->pstCcpInfo);

     /*保存PPP消息到用户信息*/
     if ((VOS_NULL_PTR != pstIpcpInfo)
        && (PPP_STATE_OPENED == pstIpcpInfo->stFsm.ucState))
     {
          pstUsrinfo->ulPppFlag |= pstIpcpInfo->stGotOptions.neg_vj ? A11_PPP_FLAG_VJ : 0;
          pstUsrinfo->ucmaxslotindex = pstIpcpInfo->stGotOptions.maxslotindex;
     }

     if ((VOS_NULL_PTR != pstCcpInfo)
        && (PPP_STATE_OPENED == pstCcpInfo->stFsm.ucState))
     {
         switch (pstCcpInfo->ucPppCompType)
         {
             case PPPCOMP_MPPC:
                 pstUsrinfo->ulPppFlag |= A11_PPP_FLAG_MPPC;
                 break;
             case PPPCOMP_LZS0:
                 pstUsrinfo->ulPppFlag |= A11_PPP_FLAG_LZS0;
                 break;
             case PPPCOMP_LZS1:
                 pstUsrinfo->ulPppFlag |= A11_PPP_FLAG_LZS1;
                 break;
             default:
                 break;
         }
     }

     pstUsrinfo->ucPPPConFlag = (UCHAR)((pstUsrinfo->ulPppFlag) & (0xFFFFFFFC));

     if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
     {
         if (MAX_DMPU_NUM > pstPppInfo->ucDmpuId)
         {
             pstUsrinfo->ucDmpuId    = pstPppInfo->ucDmpuId + PPP_CPU_2_ON_SPU;  /* 子卡ID从逻辑ID要转换为实际CPUID */
             pstUsrinfo->ucDmpuDpeId = pstPppInfo->ucDpeId;
         }
     }
     else
     {
        pstUsrinfo->ucDmpuId    = pstPppInfo->ucDmpuId;
        pstUsrinfo->ucDmpuDpeId = pstPppInfo->ucDpeId;
     }
     return;
}

/****************************************************************************
* CREATE DATE  ：2004/01/31                                                 *
* CREATED BY   ：heyajun                                                    *
* FUNCTION     :                                                            *
* MODIFY DATE  ：                                                           *
* INPUT        ：                                                           *
*                                                                           *
*                                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：成功返回VOS_OK，失败返回VOS_ERR                            *
* CALLED BY    ：                                                           *
****************************************************************************/
VOS_UINT32 PPP_SendUserInfo(PPPINFO_S* pstPppInfo, VOS_UINT32 ulType)
{
    A11_PPPC_USR_INFOR_S stUsrinfo = {0};

    if(LCP_INFOR == ulType)
    {
        PPP_SendLcpPreProc(pstPppInfo, &stUsrinfo);
    }
    else if ((IPCP_INFOR == ulType) || (SCP_INFOR == ulType))
    {
        PPP_SendIpcpPreProc(pstPppInfo, &stUsrinfo);
    }

    /* TODO:c00184031保存PPP消息到用户信息,参考核心网代码g_stPppCallBacks.pfUpIoCtl */

    return VOS_OK;

}

/*End WGGSN_B03_L2TP_PPPC_COMP*/
/* Added start by liutao 38563 at 2004-09-22 V800R002 for PPP压缩移植 */

  /*=======================================================================
   *  函数名称:  GTPC_EncapUpdatePdpContextReqV1
   *  初稿完成:  2004/01/28
   *  作    者:
   *  函数功能:  GTPC提供给PPPC模块的PPP报文封装接口
   *  输入参数:  pMbuf        封装有PPP协商消息的MBUF结构指针
   *  输出参数:  无
   *  返回类型:  GTPC_SUCCESS            －成功
   *             GTPC_FAILURE            －失败
   *  全局变量:  无
   *  其他说明:  B03 新增函数
   *  调用函数:  *
   *  主调函数:
   *=======================================================================*/
  VOS_VOID ShowCode(VOS_UINT8 *pucMsg, VOS_UINT16 usLen)
  {
      UCHAR ucMaxPerLine = 16;
      UCHAR ucCodeCount = 0, ucLine = 1;

      if ((VOS_NULL_PTR == pucMsg) || (usLen == 0))
      {
          return;
      }

      if (VRP_NO == g_ulPppDebugSwitch)
      {
          return;
      }

      (VOID)VOS_OutPrintf("\r\n #######Begin Decode Message#######\r\n");
      (VOID)VOS_OutPrintf("[%u]  ", ucLine++);

      while (usLen > 0)
      {
          (VOID)VOS_OutPrintf("%.2x ", *pucMsg );

          if (0 == (++ucCodeCount % ucMaxPerLine))
          {
              (VOID)VOS_OutPrintf("\r\n");
              if (ucLine < 10)
              {
                  (VOID)VOS_OutPrintf("[%u]  ", ucLine++);
              }
              else
              {
                  (VOID)VOS_OutPrintf("[%u] ", ucLine++);
              }
          }

          usLen--;
          pucMsg++;
      }

      (VOID)VOS_OutPrintf("\r\n#######End Decode Message#######\r\n");

      return;
  }

/* BEGIN: Added for PN:切平台 by wangyong 00138171, 2012/10/9 */
/*****************************************************************************
函 数 名  : PPP_Shell_OutPut
功能描述  : ppp对外提供的发送函数
输入参数  : VOS_UINT32 ulRpindex
           PMBUF_S *pstPMBuffNew
输出参数  : 无
返 回 值  : VOS_UINT32
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2012年9月26日
  作    者   : wangyong 00138171
  修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_Shell_OutPut(VOS_UINT32 ulRpindex, PMBUF_S *pstPMBuffNew, VOS_UINT16 usProtocol)
{
  PPPINFO_S *pstPppInfo = VOS_NULL_PTR;  /*PDSN中指向PPP控制块的指针*/
  VOS_UINT32 ulResult = 0;

  /* 获取PPPC控制块指针*/
  GETPPPINFOPTRBYRP(pstPppInfo, ulRpindex);

  if (VOS_NULL_PTR == pstPppInfo)
  {
      PPP_DBG_ERR_CNT(PPP_PHERR_635);
      (VOID)PMBUF_Destroy((PMBUF_S*)pstPMBuffNew);
      return VOS_ERR;
  }

  /* 调用PPP外壳的发送函数 */
  ulResult = PPP_Shell_SendPacketToISL((PPPINFO_S *)pstPppInfo, pstPMBuffNew, (VOS_UINT16)usProtocol);
  if (VOS_OK != ulResult)
  {
      PPP_DBG_ERR_CNT(PPP_PHERR_636);
      return VOS_ERR;
  }
  return VOS_OK;
}

/*****************************************************************************
函 数 名  : PPP_CM_GetAuthFlag
功能描述  : ppp对提供给CM获取是否是认证用户的标示
输入参数  : VOS_UINT32 ulPdnIndex
            UCHAR * pucAuthFlag
输出参数  : 无
返 回 值  : VOS_UINT32
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2012年12月14日
作    者   : zhaichao 00129699
修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_CM_GetAuthFlag(VOS_UINT32 ulPdnIndex,UCHAR * pucAuthFlag)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL_PTR;

    if (pucAuthFlag == VOS_NULL_PTR)
    {
        PPPC_INFO_LOG(  "\r\nPPP PPP_CM_GetAuthFlag : input pointer is null");
        return VOS_ERR;
    }

    (VOID)SDB_GetPdnContextByIndex(ulPdnIndex, (VOS_VOID **)&pstPdnContext);
    if (VOS_NULL_PTR == pstPdnContext)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_637);
        PPPC_INFO_LOG1(
                "\r\nPPP PPP_CM_GetAuthFlag : get pdn context error %d",ulPdnIndex);
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, pstPdnContext->ulRpIndex);
    if ((!pstPppInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_638);
        PPPC_WARNING_LOG1(
                 "\r\n PPP_CM_GetAuthFlag: Find RpIndex is wrong, ulRpIndex:%u", ulPdnIndex);
        return VOS_ERR;
    }

    *pucAuthFlag = 0;
    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_639);
        PPPC_INFO_LOG(  "\r\nPPP PPP_CM_GetAuthFlag pstLcpInfo is null no auth !");
        return VOS_ERR;
    }

    if (E_PDNTYPE_CMIP == pstPdnContext->ucPdnType)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1346);
        *pucAuthFlag = 1;
        PPPC_INFO_LOG(  "\r\nPPP PPP_CM_GetAuthFlag : cmip user");
        return VOS_OK;
    }

    if ((1 == pstLcpInfo->stGotOptions.neg_chap) || (1 == pstLcpInfo->stGotOptions.neg_upap))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1347);
        *pucAuthFlag = 1;
        PPPC_INFO_LOG(  "\r\nPPP PPP_CM_GetAuthFlag : used chap/pap auth");
    }

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : PPP_SetSendSTRFlag
功能描述  : 提供给DIAM AUTH调用，设置发送STR标记
输入参数  : VOS_UINT32 ulRpIndex, VOS_UINT32 ulAuthSessionState
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2013年03月06日
   作    者   : wangyong 00138171
   修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_SetSendSTRFlag(VOS_UINT32 ulRpIndex, VOS_UINT32 ulAuthSessionState)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    VOS_UINT32 ulRet = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_640);
        PPPC_INFO_LOG(  "\r\n [ppp]PPP_SetSendSTRFlag: pstPppInfo is null!");
        return;
    }

    PPPC_INFO_LOG3(
                 "\r\n [ppp]PPP_SetSendSTRFlag: ulAuthSessionState[%u] usPeerId[%u]ucAAAType[%u]!",
                 ulAuthSessionState, pstPppInfo->usPeerId, pstPppInfo->ucAAAType);

    if (VOS_TRUE == ulAuthSessionState)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1348);
        if (M_DIAMAUTH_DYNAAA_AAA == pstPppInfo->ucAAAType)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1349);
            /* 删除老的hash */
            ulRet = Diam_AUTHHostRemoveByAAACBIndex(pstPppInfo->usPeerId, pstPppInfo->ulRPIndex);
            if (ulRet != VOS_OK)
            {
                PPPC_WARNING_LOG3("[ppp]PPP_SetSendSTRFlag: Diam_AUTHHostRemoveByAAACBIndex fail[%u] usPeerId[%u]ucAAAType[%u]!",
                             ulAuthSessionState, pstPppInfo->usPeerId, pstPppInfo->ucAAAType);
                PPP_DBG_ERR_CNT(PPP_PHERR_641);
            }

        }
        pstPppInfo->usPeerId = VOS_NULL_WORD;
        pstPppInfo->ucAAAType = VOS_NULL_BYTE;

    }

    return;
}


/*****************************************************************************
函 数 名  : PPP_GetIPCPNakHandlingFlag
功能描述  : 提供给PDN调用，获取IPCP NAK HANDLING
输入参数  : VOS_UINT32 ulRpIndex
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2013年12月06日
   作    者   : wangyong 00138171
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_GetIPCPNakHandlingFlag(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_642);
        PPPC_WARNING_LOG(
                     "\r\n [ppp]PPP_GetIPCPNakHandlingFlag: pstPppInfo is null!");
        return VOS_FALSE;
    }

    PPPC_INFO_LOG1(
                 "\r\n [ppp]PPP_GetIPCPNakHandlingFlag: bIPCPNakHandFlag[%u]!",
                 pstPppInfo->bIPCPNakHandFlag);

    return pstPppInfo->bIPCPNakHandFlag;
}


/*****************************************************************************
函 数 名  : PPP_GetPeerID
功能描述  : 提供给DIAM AUTH调用，获取服务器ID
输入参数  : VOS_UINT32 ulRpIndex
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2013年03月06日
   作    者   : wangyong 00138171
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_GetPeerID(VOS_UINT32 ulRpIndex, VOS_UINT16 *pusPeerId)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_643);
        PPPC_WARNING_LOG(
                     "\r\n [ppp]PPP_GetPeerID: pstPppInfo is null!");
        return VOS_ERR;
    }

    PPPC_INFO_LOG1(
                 "\r\n [ppp]PPP_GetPeerID: usPeerId[%u]!",
                 pstPppInfo->usPeerId);

    *pusPeerId = pstPppInfo->usPeerId;

    return VOS_OK;
}



/*****************************************************************************
函 数 名  : PPP_GetAAAType
功能描述  : 提供给DIAM AUTH调用，获取服务器类型
输入参数  : VOS_UINT32 ulRpIndex
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2013年03月06日
   作    者   : wangyong 00138171
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_GetAAAType(VOS_UINT32 ulRpIndex, UCHAR *pucAAAType)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_644);
        PPPC_WARNING_LOG(
                     "\r\n [ppp]PPP_GetAAAType: pstPppInfo is null!");
        return VOS_ERR;
    }

    PPPC_INFO_LOG1(
                 "\r\n [ppp]PPP_GetAAAType: ucAAAType[%u]!",
                 pstPppInfo->ucAAAType);
    *pucAAAType = pstPppInfo->ucAAAType;
    return VOS_OK;
}

/*****************************************************************************
函 数 名  : PPP_UpdatePeerID
功能描述  : 提供给DIAM AUTH调用，更新服务器ID
输入参数  : VOS_UINT32 ulRpIndex
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2013年10月20日
   作    者   : wangyong 00138171
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_UpdatePeerID(VOS_UINT32 ulRpIndex, VOS_UINT16 usPeerId, UCHAR ucAAAType)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    VOS_UINT32 ulRet = 0;
    VOS_UINT16 usOldPeerId = 0;
    UCHAR ucOldAAAType = 0;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_645);
        PPPC_WARNING_LOG("\r\n [ppp]PPP_UpdatePeerID: pstPppInfo is null!");
        return VOS_ERR;
    }

    ulRet = (VOS_UINT32)SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (VOS_VOID **)&pstRpContext);
    if ((VOS_NULL_PTR == pstRpContext) || (ulRet != VOS_OK))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_646);
        PPPC_WARNING_LOG2(
                     "\r\n [ppp]PPP_UpdatePeerID: SDB_GetRpContextByIndex fail[%u] index[%u]!",
                     ulRet, pstPppInfo->ulRPIndex);
        return VOS_ERR;
    }

    PPPC_INFO_LOG3(
                 "\r\n [ppp]PPP_UpdatePeerID: usPeerId[%u][%u] aaatype[%u]!",
                 pstPppInfo->usPeerId, usPeerId, ucAAAType);

    PPP_DBG_OK_CNT(PPP_PHOK_1350);
    usOldPeerId = pstPppInfo->usPeerId;
    ucOldAAAType = pstPppInfo->ucAAAType;
    pstPppInfo->usPeerId = usPeerId;
    pstPppInfo->ucAAAType = ucAAAType;

    /* 备份 */
    if ((USM_STATE_ACTIVE == pstRpContext->ucUsmState)
        && ((pstPppInfo->usPeerId != usOldPeerId)
        || (pstPppInfo->ucAAAType != ucOldAAAType)))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1351);
    }

    return VOS_OK;
}


/*****************************************************************************
函 数 名  : PPP_JudgeIsDynAAAResource
功能描述  : 提供给DIAM AUTH调用，核查动态aaa资源
输入参数  : VOS_UINT32 ulRpIndex
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2013年11月05日
   作    者   : wangyong 00138171
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_JudgeIsDynAAAResource(VOS_UINT32 ulRpIndex, VOS_UINT16 *pusDynAAAIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;


    if (VOS_NULL_PTR == pusDynAAAIndex)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_647);
        PPPC_WARNING_LOG("\r\n [ppp]PPP_CheckDynAAAResource: pusDynAAAIndex is null!");
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_648);
        PPPC_INFO_LOG(
                     "\r\n [ppp]PPP_CheckDynAAAResource: pstPppInfo is null!");
        return VOS_ERR;
    }


    if (M_DIAMAUTH_DYNAAA_AAA == pstPppInfo->ucAAAType)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1352);
        *pusDynAAAIndex = pstPppInfo->usPeerId;
        PPPC_INFO_LOG2(
                     "\r\n [ppp]PPP_CheckDynAAAResource: usPeerId[%u]aaatype[%u]!",
                     pstPppInfo->usPeerId, pstPppInfo->ucAAAType);
        return VOS_OK;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1353);

    return VOS_ERR;
}


/*****************************************************************************
函 数 名  : PPP_GetNowUTCInSec
功能描述  : 提供给USM调用，获取时间错
输入参数  : VOS_UINT32 ulRpIndex
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2013年03月06日
   作    者   : wangyong 00138171
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_GetNowUTCInSec(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_649);
        PPPC_WARNING_LOG1(
                     "\r\n [ppp]PPP_GetNowUTCInSec: pstPppInfo is null!ulRpIndex=%u", ulRpIndex);
        return VOS_NULL_DWORD;
    }

    PPPC_INFO_LOG1(
                 "\r\n [ppp]PPP_GetNowUTCInSec: ulNowUTCInSec[%u]!",
                 pstPppInfo->ulNowUTCInSec);

    return pstPppInfo->ulNowUTCInSec;
}

/*****************************************************************************
 函 数 名  : PPP_GetLocalL2tpCsi
 功能描述  : 获取本板l2tp组件的csi
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT64
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月2日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT64 PPP_GetLocalL2tpCsi(VOID)
{
    return g_ullPppLocalL2tpCsi;
}

/*****************************************************************************
 *  函数名称:       PPP_CheckIsLcpTerminateMsg
 *  初稿完成:       2013-11-19
 *  作    者:       y00170683
 *  函数功能:       检查是否是LCP-terminate消息
 *  输入参数:       PPPINFO_S *pstPppInfo, UCHAR *pucPacket, VOS_UINT32 ulLen
 *  输出参数:       UCHAR *pucLcpTerminateFlg
 *  返回类型:       VOID
 *  其他说明:       DTS2013111600091
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID PPP_CheckIsLcpTerminateMsg(PPPINFO_S *pstPppInfo, UCHAR *pucPacket, VOS_UINT32 ulLen, UCHAR *pucLcpTerminateFlg)
{
    UCHAR ucCode = 0;
    VOS_UINT32 ulOffset = 0;
    VOS_UINT16 usProtocol = 0;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPppInfo))
    {
        return;
    }
#if 0
    if (E_CRM_ACTIVE == CRM_GetSlotPrimaryInfoOfSelfGroup((UCHAR)DVM_SELF_SLOTID))
    {
        return;
    }
#endif

    /* 获得协议号,并返回PPP头长度 */
    ulOffset = PPP_Core_GetProtocol(pstPppInfo, pucPacket, &usProtocol);
    if ((ulOffset == 0) || (ulLen < ulOffset))
    {
        return;
    }

    /* 移动指针 */
    pucPacket += ulOffset;
    ulLen -= ulOffset;

    PPP_GETCHAR(ucCode, pucPacket);
    (VOS_VOID)pucPacket;

    if (PPP_LCP == usProtocol)
    {
        if ((ulLen > PPP_LCP_NEGO_PACKET_MAX_LEN) || (ulLen < FSM_HDRLEN)
            || ((VOS_NULL_PTR == pstPppInfo->pstLcpInfo)))
        {
            return;
        }
        if (TERMREQ == ucCode)
        {
            *pucLcpTerminateFlg = VOS_TRUE;
        }
    }

    return;
}

/*****************************************************************************
 *  函数名称:       PPP_SlaveBoardDiscardMsMsg
 *  初稿完成:       2013-11-19
 *  作    者:       y00170683
 *  函数功能:       备板不处理MS上送的消息
 *  输入参数:       PDN_CONTEXT_S *pstPdnContext, UCHAR ucSlaveReleaseFlg
 *  输出参数:
 *  返回类型:       VOS_UINT32, 只有主板时才返回ERR
 *  其他说明:       DTS2013111600091
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOS_UINT32 PPP_SlaveBoardDiscardMsMsg(SDB_PDSN_RP_CONTEXT_S *pstRpContext, UCHAR ucSlaveReleaseFlg)
{
#if 0
    if (E_CRM_ACTIVE == CRM_GetSlotPrimaryInfoOfSelfGroup((UCHAR)DVM_SELF_SLOTID))
    {
        return VOS_ERR;
    }
#endif

    if (VOS_NULL_PTR == pstRpContext)
    {
        return VOS_OK;
    }

    /* 备板不需要处理的释放消息 */
    if (VOS_FALSE == ucSlaveReleaseFlg)
    {
        return VOS_OK;
    }

    pstRpContext->bSlaveReleaseFlg = VOS_TRUE;
    PPP_DBG_ERR_CNT(PPP_PHERR_650_MS_SLAVE_REL);

    return VOS_OK;
}


#define __PPP_L2TP_PROC__

/*****************************************************************************
函 数 名  : PPP_L2tpMsgProc
功能描述  : PPP模块收到L2TP消息的处理函数
输入参数  : PPPC_L2TP_NOTIFY_INFO *pstMsg
           VOS_UINT32 ulMsgCode
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2012年12月13日
  作    者   :ZHAICHAO
  修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_L2tpMsgProc(VOID *pstMsg, VOS_UINT32 ulMsgCode)
{
#if 0
    VOS_UINT32 ulRet = VOS_OK;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPdnContext = VOS_NULL_PTR;
    VOS_UINT32 ulPdnIndex = 0;

    if ( VOS_NULL_PTR == pstMsg )
    {
         PPPC_INFO_LOG(  "\r\n [ppp]PPP_L2tpMsgProc: input para is null!");
         return ;
    }

    /* 入参已经被调用者判断 */
    switch (ulMsgCode)
    {
         case PPP_MSG_CODE_L2TP_UP:
         {
             L2TP_NOTIFY_PPPC_UP_INFO* pstL2tpUpMsg = pstMsg;
             PPP_INNER_COUNTER(PPP_INNER_COUTNER_008);

             PPP_DBG_OK_CNT(PPP_PHOK_1356);

             ulPdnIndex = PDN_PDNGlobalIndexToPDNScIndex(pstL2tpUpMsg->ulPdpindex);

             ulRet = SDB_GetPdnContextByIndex(ulPdnIndex, (UCHAR**)&pstPdnContext);
             if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPdnContext))
             {
                 PPP_DBG_ERR_CNT(PPP_PHERR_652);
                 return;
             }

             (VOID)PPP_NodeDelete(pstPdnContext->ulRpIndex);

             GETPPPINFOPTRBYRP(pstPppInfo, pstPdnContext->ulRpIndex);
             if (VOS_NULL_PTR != pstPppInfo)
             {
                 (VOID)PPP_ClearCB(pstPppInfo);
             }

             /* 是否删除ppp控制块 */
             (VOID)PDN_L2tpUp(ulPdnIndex, pstMsg);
             break ;
         }
         case PPP_MSG_CODE_L2TP_DOWN:
         {
             L2TP_NOTIFY_PPPC_DOWN_INFO* pstL2tpDownMsg = pstMsg;
             PPP_INNER_COUNTER(PPP_INNER_COUTNER_009);

             PPP_DBG_OK_CNT(PPP_PHOK_1357);

             ulPdnIndex = PDN_PDNGlobalIndexToPDNScIndex(pstL2tpDownMsg->ulPdpindex);

             ulRet = SDB_GetPdnContextByIndex(ulPdnIndex, (UCHAR**)&pstPdnContext);
             if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPdnContext))
             {
                 PPP_DBG_ERR_CNT(PPP_PHERR_653);
                 return ;
             }

             GETPPPINFOPTRBYRP(pstPppInfo, pstPdnContext->ulRpIndex);
             if (VOS_NULL_PTR != pstPppInfo)
             {
                 (VOID)PPP_NodeDelete(pstPdnContext->ulRpIndex);
             }
             else
             {
                 pstL2tpDownMsg->usFailReason = L2TP_DEA_CALL_BY_LNS;
             }

             (VOID)PDN_L2tpDown(ulPdnIndex, pstMsg);
             break ;
         }
         default:
         {
             PPP_DBG_ERR_CNT(PPP_PHERR_654);
             VOS_DBGASSERT(0);
             PPPC_INFO_LOG(
                                  "\r\n PPP_L2tpMsgProc: Proc l2tp msg faild! MsgCode[%d].",
                                  ulMsgCode);
             break;
         }
    }
#endif
    return;
}

 /*****************************************************************************
   函 数 名  : PPP_Shell_NotifyL2tpUp
   功能描述  : PPP通知L2TP建立L2tp隧道
   输入参数  : VOS_UINT32 ulIndex
               L2TP_PPPPARA_S *pstPPPPara
   输出参数  : 无
   返 回 值  : VOS_UINT32
   调用函数  :
   被调函数  :

   修改历史      :
    1.日    期   : 2012年10月17日
      作    者   : luofang
      修改内容   : 新生成函数

  *****************************************************************************/
VOS_UINT32 PPP_Shell_NotifyL2tpUp(VOS_UINT32 ulIndex, L2TP_PPPPARA_S *pstPPPPara )
{
#if 0
    VOS_UINT32         ulResult = 0;
    SDB_RETURNCODE_E   enSdbReturn = SDB_SUCCESS;
    SDB_PDSN_RP_CONTEXT_S *pstContext = VOS_NULL_PTR;

    PPP_DBG_OK_CNT(PPP_PHOK_1358);
    PPPC_INFO_LOG( ( VOS_UINT32 )  "\r\n PPP_NotifyL2tpUp: Call %lu up in.", ulIndex );

    if (VOS_NULL_PTR == pstPPPPara)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_655);
        PPPC_INFO_LOG( ( VOS_UINT32 )MID_PPPC, PPP_DEBUG_LOG, "\r\n PPP_NotifyL2tpUp: pstPPPPara is null" );
        return VOS_ERR;
    }

    enSdbReturn = (SDB_RETURNCODE_E)SDB_GetRpContextByIndex(ulIndex, ( UCHAR** )&pstContext );
    if ( ( SDB_SUCCESS != enSdbReturn   )  || ( VOS_NULL_PTR == pstContext  ) )
    {
        /* 该上下文不存在 */
        PPPC_INFO_LOG( ( VOS_UINT32 )MID_PPPC, PPP_DEBUG_LOG, "\r\n PPP_NotifyL2tpUp The PDP Context dose not exist %lu", enSdbReturn);
        PPP_DBG_ERR_CNT(PPP_PHERR_656);
        return VOS_ERR;
    }

    PPP_L2tpUpPreProc(pstPPPPara, pstContext,ulIndex);

    ulResult = PPP_SendMsgToL2tp(L2TP_MSGCODE_UP,
                                    (UCHAR *)pstPPPPara,
                                    sizeof(L2TP_PPPPARA_S));

    PPPC_INFO_LOG( ( VOS_UINT32 )  "\r\n PPP_NotifyL2tpUp  exit %lu spu type %lu", ulResult, g_enPppBoardType);

    if (VOS_OK != ulResult)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_657);
        return VOS_ERR ;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1359);
#endif
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_Shell_NotifyL2tpDown
 功能描述  : PPP模块通知L2TP模块Down
 输入参数  : VOS_UINT32 ulRPIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月8日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_Shell_NotifyL2tpDown(PDN_CONTEXT_S *pstPdnContext, UCHAR ucMsgCode)
{
#if 0
    VOS_UINT32 ulResult = VOS_OK;
    L2TP_DOWNPARA_S stL2tpDown = {0};

    stL2tpDown.ulPdpindex   = PDN_PDNScIndexToPDNGlobalIndex(pstPdnContext->ulPdnIndex);
    stL2tpDown.ulTeidc      = pstPdnContext->ulTeidc;
    stL2tpDown.ulGiifIndex  = pstPdnContext->stL2tp.ulIfIndex;
    stL2tpDown.usLocalTID   = pstPdnContext->stL2tp.usLocalTid;
    stL2tpDown.usLocalSID   = pstPdnContext->stL2tp.usLocalSid;
    stL2tpDown.ucScid       = (UCHAR)PPP_SELF_CMPIDXINSG;

    ulResult = PPP_SendMsgToL2tp(ucMsgCode,
                                    (UCHAR *)&stL2tpDown,
                                    sizeof(L2TP_DOWNPARA_S));

    if ( VOS_OK != ulResult )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_658);
        PPPC_INFO_LOG(
                    "\r\n [ppp]PPP_Shell_NotifyL2tpDown: PPP_SendMsgToL2tp error %u,%u",
                    ulResult, ucMsgCode);
        return VOS_ERR;
    }
#endif
    return VOS_OK;
}

/*****************************************************************************
函 数 名  : PPP_L2tpUpPreProc
功能描述  :  根据软参配置设置L2TP参数
输入参数  : L2TP_PPPPARA_S * pstPPPPara
           SDB_GSPU_CONTEXT_S *pstContext
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2012年10月17日
  作    者   : luofang
  修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_L2tpUpPreProc(L2TP_PPPPARA_S * pstPPPPara, SDB_PDSN_RP_CONTEXT_S *psRpContext,VOS_UINT32 ulIndex)
{
#if 0
    UCHAR szTempImsi[M_IMSI_LEN] = {0}; /*Imsi to string*/
    VOS_UINT32 imsiLen = 0;
    VOS_UINT32 i = 0;  /*IMSI Lenth*/
    CHAR szCallFromId[CALL_FROMID_LENTH] = {0};
    UCHAR aucMsisdn[A11_MSISDN_LEN] = {0};
    S_CFG_DOMAINNODE *pstDomain = VOS_NULL_PTR;
    UCHAR ucMDNFlag = 0;
    VOS_UINT32 ulRet = 0;

    if ((VOS_NULL_PTR == pstPPPPara) || (VOS_NULL_PTR == psRpContext))
    {
        PPPC_INFO_LOG(  "\r\nPPP_L2tpUpPreProc input para is null");
        return;
    }


    ImsiToString(psRpContext->stImsi, szTempImsi);     /*Convert IMSI to string for variable IMSI*/

    ulRet = A11_GetDomainByIndex(psRpContext->usDomainIndex, &pstDomain);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_659);
        PPPC_INFO_LOG(MID_PPPC, PPP_DEBUG_LOG, "\r\nPPP_L2tpUpPreProc Get Domain configure fail!");
        return;
    }

    ucMDNFlag = pstDomain->ucL2tpAttribute;

    if((HSGW_DOMAIN_L2TP_ATTRIBUTE_MDN == ucMDNFlag) && (VOS_TRUE == psRpContext->ucMsisdnFlag)) /* 判断AAA是否下发了该字段 */
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1360);
        A11_BCDToString(psRpContext->szMsisdn, aucMsisdn, 15);
        PTM_StrNCpy(pstPPPPara->stSessionInfo.szDialingNumber, aucMsisdn, L2TP_DIALINGNUM_LEN-1);
    }
    else
    {
        /*取IMSI作为用户号码，18号软参控制*/
        if (g_ulSoftPara534 & 0x01)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1361);
            VOS_MemCpy(pstPPPPara->stSessionInfo.szDialingNumber, szTempImsi,
            VOS_StrLen((CHAR *)szTempImsi));
        }
        else
        {
            imsiLen = VOS_StrLen((CHAR *)szTempImsi);
            if ((imsiLen >= 10) && (imsiLen <= 15))
            {
                for (i = 0; i < 10; i++)
                {
                    szCallFromId[i] = (CHAR)szTempImsi[i + imsiLen - 10];
                }

                szCallFromId[10] = '\0';
                VOS_StrCpy(pstPPPPara->stSessionInfo.szDialingNumber, szCallFromId);
            }
            else
            {
                PPPC_INFO_LOG(  "\r\n PPP_L2tpUpPreProc IMSI Length Error: %d \r\n", imsiLen);
            }
        }
    }

    VOS_StrCpy(pstPPPPara->stSessionInfo.szDialedNumber, "8888");

    pstPPPPara->stSessionInfo.bBearTypeUsed = VOS_TRUE;
    pstPPPPara->stSessionInfo.ulBearType = BEARER_TYPE_BOTH;
    pstPPPPara->stSessionInfo.ulFramType = FRAMING_TYPE_BOTH;
    pstPPPPara->stSessionInfo.bPrivateGroupIdUsed = VOS_TRUE;
#endif
    return;
}

/*****************************************************************************
 函 数 名  : PPP_Shell_L2tpProc
 功能描述  : L2TP用户处理
 输入参数  :
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月6日
    作    者   : h50774
    修改内容   : 新生成函数

2.日    期   : 2012年12月13日
  作    者   : zhaichao 00129699
  修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_Shell_L2tpProc(VOS_UINT32 ulRpIdx, L2TP_PPPPARA_S *pstL2tpPara)
{
    PPPLCPINFO_S *pstLcpInfo = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;  /*PDSN中指向PPP控制块的指针*/

    if (VOS_NULL_PTR == pstL2tpPara)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_660);
        return VOS_ERR;
    }

    /* 获取PPPC控制块指针*/
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIdx);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_661);
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == pstPppInfo->pL2tpPara)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_662);
        return VOS_ERR;
    }

    VOS_MemCpy(&(pstL2tpPara->stSessionInfo),
                pstPppInfo->pL2tpPara,
                sizeof(L2TP_SESSIONPARA_S));

    pstL2tpPara->stSessionInfo.bLcpOptionUsed   = VOS_TRUE;
    pstL2tpPara->stSessionInfo.bProxyAuthenUsed = VOS_TRUE;

    /*是l2tp用户,通知l2tp up*/
    /* 通知L2TP建立隧道 */

    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    if (VOS_NULL_PTR == pstLcpInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_663);
        return VOS_ERR;
    }

    if (pstLcpInfo->stGotOptions.neg_chap)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1362);
        PPP_PerfInc(&g_stPppPerfStatistic.ulChapSuccess, PERF_TYPE_PPPC_CHAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);
    }
    else if (pstLcpInfo->stGotOptions.neg_upap)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1363);
        PPP_PerfInc(&g_stPppPerfStatistic.ulPapSuccess, PERF_TYPE_PPPC_PAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1364);
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_Shell_L2tpProc: Receive unexpected message!!");
    }


    PPP_SNMP_PERF_SET_SUCCESS(pstPppInfo);

    if (VOS_ERR == PPP_Shell_NotifyL2tpUp(pstPppInfo->ulRPIndex, pstL2tpPara))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_664);
        PPPC_INFO_LOG(  "\r\n PPP_Shell_ReceiveAAAResult: PPP_Shell_NotifyL2tpUp failed");
        pstPppInfo->bFailFlag = PPPL2TPDOWN;
        /* BEGIN: D by h50774 for PS10.1整改，向PDN状态机返回失败即可, 2013/1/3 */
        /* PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo); */
        /* END  : D by h50774 for PS10.1整改，向PDN状态机返回失败即可, 2013/1/3 */
        return VOS_ERR;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1365);
    pstPppInfo->bAuthFlag = VOS_TRUE;
    pstPppInfo->bPppSuccess = 1;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_SendMsgToL2tp
 功能描述  : 发送消息给LAC线程
 输入参数  : UCHAR ucMsgCode
             UCHAR* pucMsg
             VOS_UINT32 ulMsgLen
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月19日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_SendMsgToL2tp(UCHAR ucMsgCode, UCHAR* pucMsg, VOS_UINT32 ulMsgLen )
{
#if 0
    VOS_UINT32 ulRet = VOS_OK;

    if (VOS_NULL_PTR == pucMsg)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_665);
        PPPC_INFO_LOG(  "\r\n [ppp]PPP_SendMsgToL2tp : Input ptr is null");
        return VOS_ERR;
    }

    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)    /*SPUD板*/
    {
        ulRet = PPP_SendRtMsg(PPP_SELF_CSI, g_ullPppLocalL2tpCsi, L2TP_MSG_TYPE_PPPC, ucMsgCode, pucMsg, ulMsgLen);
        if ( VOS_OK != ulRet )
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_666);
            PPPC_INFO_LOG(MID_PPPC, PPP_DEBUG_LOG ,
                        "\r\n %s:  PPP_SendMsgToL2tp error, the ret = 0x%lx, msgcode %d. ",
                        (CHAR *)(__FUNCTION__), ulRet, ucMsgCode );
            return VOS_ERR;
        }
    }
    else
    {
        ulRet = PPP_SendURTMsg(g_ullPppLocalL2tpCsi, L2TP_MSG_TYPE_FCM, ucMsgCode, pucMsg, ulMsgLen);
        if (VOS_OK != ulRet)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_667);
            PPPC_INFO_LOG( MID_PPPC, PPP_DEBUG_LOG,
                        "\r\n PPP_SendMsgToL2tp: Call PPP_SendURTMsg ret %lu msgcode %d.", ulRet, ucMsgCode);
            return VOS_ERR;
        }
    }

    PPPC_INFO_LOG(
                "\r\n PPP_SendMsgToL2tp:  send message to lac succ. ");
#endif
    return VOS_OK ;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
