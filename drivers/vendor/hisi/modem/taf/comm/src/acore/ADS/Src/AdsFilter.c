

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AdsCtx.h"
#include "AdsLog.h"
#include "AdsFilter.h"
/* Modified by m00217266 for L-C互操作项目, 2014-2-11, begin */
#include "AdsInterface.h"
/* Modified by m00217266 for L-C互操作项目, 2014-2-11, end */
#include "NVIM_Interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_FILTER_C
/*lint +e767*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* ADS过滤功能上下文 */
ADS_FILTER_CTX_STRU                     g_stAdsFilterCtx;

/* ADS过滤功能统计信息: 数组中各元素所代表的统计量意义如下:
   数组索引        统计量
      0         上行IPv4 TCP
      1         上行IPv4 UDP
      2         上行IPv4 ECHO REQ
      3         上行不支持的IPv4报文
      4         上行IPv6报文
      5         下行IPv4 TCP
      6         下行IPv4 UDP
      7         下行IPv4 ECHO REPLY
      8         下行IPv4 ICMP差错报文
      9         下行IPv4 分片包(首片)
      10        下行IPv4 分片包(非首片)
      11        下行IPv6包 */
VOS_UINT32                              g_aulAdsFilterStats[ADS_FILTER_ORIG_PKT_BUTT]  = {0};

/* ADS解析下行ICMP报文所用的函数指针结构体，当前只支持Echo Reply和ICMP差错报文 */
ADS_FILTER_DECODE_DL_ICMP_FUNC_STRU     g_astAdsFilterDecodeDlIcmpFuncTbl[] =
    {         /*ICMP Type*/                            /* pFunc */                               /* enOrigPktType */
        /*  0:Echo Reply              */   {ADS_FILTER_DecodeDlIPv4EchoReplyPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ECHOREPLY},
        /*  1:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /*  2:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /*  3:Destination Unreachable */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR},
        /*  4:Source Quench           */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR},
        /*  5:Redirect (change route) */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR},
        /*  6:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /*  7:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /*  8:Echo Request            */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /*  9:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 10:Reserve                 */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 11:Time Exceeded           */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR},
        /* 12:Parameter Problem       */   {ADS_FILTER_DecodeDlIPv4IcmpErrorPacket,     ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR},
        /* 13:Timestamp Request       */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 14:Timestamp Reply         */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 15:Information Request     */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 16:Information Reply       */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 17:Address Mask Request    */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             },
        /* 18:Address Mask Reply      */   {VOS_NULL_PTR,                               ADS_FILTER_ORIG_PKT_BUTT             }
    };


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : ADS_FILTER_ResetIPv6Addr
 功能描述  : 重置过滤的IPv6地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_ResetIPv6Addr(VOS_VOID)
{
    PS_MEM_SET(ADS_FILTER_GET_IPV6_ADDR(), 0, sizeof(ADS_IPV6_ADDR_UN));

    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_InitListsHead
 功能描述  : 初始化ADS下行数据过滤表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_InitListsHead(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    HI_LIST_S                          *pstListHead = VOS_NULL_PTR;

    /* 循环初始化每一个过滤表的头节点 */
    for (ulLoop = 0; ulLoop < ADS_FILTER_MAX_LIST_NUM; ulLoop++)
    {
        pstListHead = ADS_FILTER_GET_LIST(ulLoop);

        /*lint -e717*/
        HI_INIT_LIST_HEAD(pstListHead);
        /*lint -e717*/
    }
    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_InitCtx
 功能描述  : 初始化ADS过滤器上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
  2.日    期   : 2013年07月222日
    作    者   : j00177245
    修改内容   : 清理编译warning
*****************************************************************************/
VOS_VOID ADS_FILTER_InitCtx(VOS_VOID)
{
    TAF_NVIM_SHARE_PDP_INFO_STRU        stSharePdp;
    VOS_UINT32                          ulTimeLen;

    PS_MEM_SET(&g_stAdsFilterCtx, 0, sizeof(g_stAdsFilterCtx));

    /* 初始化过滤表头节点 */
    ADS_FILTER_InitListsHead();

    /* 初始化老化周期 */
    /* 读取NV项，获取过滤节点老化时长 */
    PS_MEM_SET(&stSharePdp, 0, sizeof(stSharePdp));
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_SHARE_PDP_INFO,
                           &stSharePdp,
                           sizeof(stSharePdp)))
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_DL, "ADS_FILTER_InitCtx: NV Read Failed!");
        stSharePdp.usAgingTimeLen = ADS_FILTER_DEFAULT_AGING_TIMELEN;
    }

    ulTimeLen   = ADS_FILTER_SECOND_TRANSFER_JIFFIES * stSharePdp.usAgingTimeLen;
    ADS_FILTER_SET_AGING_TIME_LEN(ulTimeLen);

    /* 初始化IPv6过滤地址 */
    ADS_FILTER_ResetIPv6Addr();

    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_HeapAlloc
 功能描述  : ADS过滤器系统内存申请函数
 输入参数  : VOS_UINT32 ulSize  -- 申请内存大小
 输出参数  : 无
 返 回 值  : VOS_VOID*          -- 申请内存地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID* ADS_FILTER_HeapAlloc(VOS_UINT32 ulSize)
{
    VOS_VOID                           *ret = VOS_NULL_PTR;

    if ((ulSize == 0) || (ulSize > 1024))
    {
        return VOS_NULL_PTR;
    }

#if (VOS_LINUX == VOS_OS_VER)
    ret = (VOS_VOID *)kmalloc(ulSize, GFP_KERNEL);
#else
    ret = (VOS_VOID *)malloc(ulSize);
#endif

    return ret;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_HeapFree
 功能描述  : ADS过滤器系统内存释放函数
 输入参数  : VOS_VOID *pAddr    -- 需要释放的内存地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_HeapFree(VOS_VOID *pAddr)
{
    if (pAddr == NULL)
    {
        return;
    }

#if (VOS_LINUX == VOS_OS_VER)
    kfree(pAddr);
#else
    free(pAddr);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_AddFilter
 功能描述  : 增加过滤器到过滤表
 输入参数  : ADS_FILTER_IPV4_INFO_STRU *pstFilter   -- 新增的过滤器
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_AddFilter(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter)
{
    ADS_FILTER_NODE_STRU               *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    /* 申请过滤表节点内存 */
    pstNode = (ADS_FILTER_NODE_STRU *)ADS_FILTER_MALLOC(sizeof(ADS_FILTER_NODE_STRU));
    if (VOS_NULL_PTR == pstNode)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_FILTER_AddFilter: Malloc Failed!");
        return;
    }

    pstNode->stFilter = *pstFilter;

    /* 获取标示信息对应的过滤表索引号 */
    ucIndex = ADS_FILTER_GET_INDEX(pstFilter);

    /* 通过索引号获取对应过滤链表的头结点 */
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);

    /* 将节点增加到过滤表链表中 */
    msp_list_add_tail(&pstNode->stList, pstListHead);

    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_ResetLists
 功能描述  : 重置ADS下行数据过滤表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_ResetLists(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstTmp      = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead = VOS_NULL_PTR;
    ADS_FILTER_NODE_STRU               *pstNode     = VOS_NULL_PTR;

    /* 循环遍历所有过滤表，并释放过滤表的所有节点 */
    for (ulLoop = 0; ulLoop < ADS_FILTER_MAX_LIST_NUM; ulLoop++)
    {
        pstListHead = ADS_FILTER_GET_LIST(ulLoop);
        msp_list_for_each_safe(pstMe, pstTmp, pstListHead)
        {
            pstNode = msp_list_entry(pstMe, ADS_FILTER_NODE_STRU, stList);

            /* 从过滤表中删除节点 */
            msp_list_del(&pstNode->stList);

            /* 释放节点内存 */
            ADS_FILTER_FREE(pstNode);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_Reset
 功能描述  : 重置过滤信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_Reset(VOS_VOID)
{
    /* 重置IPv6过滤地址 */
    ADS_FILTER_ResetIPv6Addr();

    /* 重置过滤表 */
    ADS_FILTER_ResetLists();

    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_Match
 功能描述  : 在过滤表匹配标示信息，若匹配将刷新老化周期
 输入参数  : HI_LIST_S                 *pstListHead     -- 过滤表首节点
             ADS_FILTER_IPV4_INFO_STRU *pstFilter       -- 用于匹配的标示信息
 输出参数  : 无
 返 回 值  : VOS_TRUE   -- 过滤信息匹配
             VOS_FALSE  -- 过滤信息不匹配
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_UINT32 ADS_FILTER_IsInfoMatch(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter1,
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter2)
{
    VOS_UINT32                          ulRet;

    ulRet = VOS_FALSE;

    /* 匹配源地址、目的地址、协议类型 */
    if ( !ADS_FILTER_IS_IPHDR_MATCH(&pstFilter1->stIPHeader, &pstFilter2->stIPHeader) )
    {
        return ulRet;
    }

    /* 按照报文类型进行匹配 */
    switch(pstFilter1->enPktType)
    {
        case ADS_FILTER_PKT_TYPE_TCP:
            /* 按照TCP类型进行匹配 */
            if (ADS_FILTER_IS_TCP_PKT_MATCH(&pstFilter1->unFilter.stTcpFilter,
                                            &pstFilter2->unFilter.stTcpFilter))
            {
                ulRet = VOS_TRUE;
            }
            break;
        case ADS_FILTER_PKT_TYPE_UDP:
            /* 按照UDP类型进行匹配 */
            if (ADS_FILTER_IS_UDP_PKT_MATCH(&pstFilter1->unFilter.stUdpFilter,
                                            &pstFilter2->unFilter.stUdpFilter))
            {
                ulRet = VOS_TRUE;
            }
            break;
        case ADS_FILTER_PKT_TYPE_ICMP:
            /* 按照ICMP类型进行匹配 */
            if (ADS_FILTER_IS_ICMP_PKT_MATCH(&pstFilter1->unFilter.stIcmpFilter,
                                             &pstFilter2->unFilter.stIcmpFilter))
            {
                ulRet = VOS_TRUE;
            }
            break;
        case ADS_FILTER_PKT_TYPE_FRAGMENT:
            /* 按照分片包类型进行匹配 */
            if (ADS_FILTER_IS_FRAGMENT_MATCH(&pstFilter1->unFilter.stFragmentFilter,
                                             &pstFilter2->unFilter.stFragmentFilter))
            {
                ulRet = VOS_TRUE;
            }
            break;
        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_Match
 功能描述  : 在过滤表匹配标示信息，若匹配将刷新老化周期
 输入参数  : ADS_FILTER_IPV4_INFO_STRU *pstFilter       -- 用于匹配的标示信息
 输出参数  : 无
 返 回 值  : VOS_TRUE   -- 过滤信息匹配
             VOS_FALSE  -- 过滤信息不匹配
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_UINT32 ADS_FILTER_Match(
    ADS_FILTER_IPV4_INFO_STRU          *pstFilter)
{
    ADS_FILTER_NODE_STRU               *pstNode     = VOS_NULL_PTR;
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstListTmp  = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucIndex;

    ulRet   = VOS_FALSE;

    /* 获取标示信息对应的过滤表索引号 */
    ucIndex = ADS_FILTER_GET_INDEX(pstFilter);

    /* 通过索引号获取对应过滤链表的头结点 */
    pstListHead = ADS_FILTER_GET_LIST(ucIndex);

    /* 循环遍历链表，查找匹配项 */
    msp_list_for_each_safe(pstMe, pstListTmp, pstListHead)
    {
        pstNode = msp_list_entry(pstMe, ADS_FILTER_NODE_STRU, stList);

        /* 判断节点是否过期 */
        if (ADS_FILTER_IS_AGED(pstNode->stFilter.ulTmrCnt))
        {
            /* 从链表中拆出该节点 */
            msp_list_del(&pstNode->stList);

            /* 释放节点内存 */
            ADS_FILTER_FREE(pstNode);

            continue;
        }

        /* 判断报文类型是否匹配 */
        if ( (pstFilter->enPktType != pstNode->stFilter.enPktType)
          || (VOS_TRUE == ulRet) )
        {
            /* 若类型不匹配或已经找到匹配项则继续处理下一个节点 */
            continue;
        }

        /* 报文过滤信息匹配 */
        ulRet = ADS_FILTER_IsInfoMatch(pstFilter, &pstNode->stFilter);

        /* 过滤信息匹配，刷新老化时间 */
        if (VOS_TRUE == ulRet)
        {
            pstNode->stFilter.ulTmrCnt = ADS_GET_CURR_KERNEL_TIME();
        }
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_SaveIPAddrInfo
 功能描述  : 保存IP过滤地址信息
 输入参数  : ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr    -- IP地址信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_SaveIPAddrInfo(
    ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr)
{
    /* IPv6类型，则需要将IPv6地址保存到全局过滤信息中 */
    if (VOS_TRUE == pstFilterIpAddr->bitOpIpv6Addr)
    {
        PS_MEM_CPY(ADS_FILTER_GET_IPV6_ADDR()->aucIpAddr,
                   pstFilterIpAddr->aucIpv6Addr,
                   ADS_IPV6_ADDR_LEN);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_DecodeUlPacket
 功能描述  : ADS过滤器上行数据包解码，只支持TCP\UDP\ICMP
 输入参数  : IMM_ZC_STRU                *pstData       -- 上行数据包
 输出参数  : ADS_FILTER_IPV4_INFO_STRU  *pstIPv4Filter -- 过滤标志结构体指针
 返 回 值  : VOS_OK     -- 上行数据包解码成功
             VOS_ERR    -- 上行数据包解码失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeUlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr      = VOS_NULL_PTR;
    ADS_UDP_HDR_STRU                   *pstUdpHdr       = VOS_NULL_PTR;
    ADS_TCP_HDR_STRU                   *pstTcpHdr       = VOS_NULL_PTR;
    ADS_ICMP_HDR_STRU                  *pstIcmpHdr      = VOS_NULL_PTR;

    /* 解析IP首部 */
    pstIPv4Hdr  = (ADS_IPV4_HDR_STRU *)IMM_ZcGetDataPtr(pstData);

    /* 分片包的非首片，则直接发送，不需要进行过滤信息提取。各类型判别条件如下(分片包非首片判断方法: Offset为非0):
                         MF      Offset
        非分片包         0         0
        分片包首片       1         0
        分片包中间片     1         非0
        分片包尾片       0         非0 */
    if (0 != (pstIPv4Hdr->usFlags_fo & VOS_HTONS(ADS_IP_OFFSET)))
    {
        /* 可维可测统计 */
        ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_FIRST_FRAGMENT, 1);
        return VOS_ERR;
    }


    /* 获取当前系统时间 */
    pstIPv4Filter->ulTmrCnt                 = ADS_GET_CURR_KERNEL_TIME();

    pstIPv4Filter->stIPHeader.ulSrcAddr     = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr     = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol    = pstIPv4Hdr->ucProtocol;

    /* 判断报文类型是否为TCP\UDP\ICMP。注意:分片包首片为TCP或UDP，统一按照TCP/UDP包类型进行处理 */
    switch (pstIPv4Hdr->ucProtocol)
    {
        case ADS_IPPROTO_ICMP:
            pstIcmpHdr = (ADS_ICMP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

            /* 目前上行只支持PING ECHO REQ类型ICMP报文，若收到其他类型ICMP报文，不做过滤处理，直接发送 */
            if (ADS_ICMP_ECHOREQUEST != pstIcmpHdr->ucType)
            {
                /* 其他类型ICMP报文，不处理，可维可测统计 */
                ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT, 1);
                return VOS_ERR;
            }

            pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_ICMP;
            pstIPv4Filter->unFilter.stIcmpFilter.usIdentifier = pstIcmpHdr->unIcmp.stIcmpEcho.usIdentifier;
            pstIPv4Filter->unFilter.stIcmpFilter.usSeqNum     = pstIcmpHdr->unIcmp.stIcmpEcho.usSeqNum;

            /* 可维可测统计 */
            ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_ECHOREQ, 1);
            return VOS_OK;

        case ADS_IPPROTO_TCP:
            pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_TCP;
            pstTcpHdr = (ADS_TCP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);
            pstIPv4Filter->unFilter.stTcpFilter.usSrcPort = pstTcpHdr->usSrcPort;
            pstIPv4Filter->unFilter.stTcpFilter.usDstPort = pstTcpHdr->usDstPort;

            /* 可维可测统计 */
            ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_TCP, 1);
            return VOS_OK;

        case ADS_IPPROTO_UDP:
            pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_UDP;
            pstUdpHdr = (ADS_UDP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);
            pstIPv4Filter->unFilter.stUdpFilter.usSrcPort = pstUdpHdr->usSrcPort;
            pstIPv4Filter->unFilter.stUdpFilter.usDstPort = pstUdpHdr->usDstPort;

            /* 可维可测统计 */
            ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_UDP, 1);
            return VOS_OK;

        default:
            /* 不支持的IPv4包，不处理 */
            /* 可维可测统计 */
            ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT, 1);
            break;
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_ProcUlPacket
 功能描述  : ADS过滤器上行数据包处理
 输入参数  : IMM_ZC_STRU               *pstData     -- 上行数据包
             ADS_PKT_TYPE_ENUM_UINT8    enIpType    -- 上行数据包IP类型
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_ProcUlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType)
{
    ADS_FILTER_IPV4_INFO_STRU           stIPv4Filter;
    VOS_UINT32                          ulDecodeRet;
    VOS_UINT32                          ulRet;

    /* 初始化 */
    PS_MEM_SET(&stIPv4Filter, 0 ,sizeof(stIPv4Filter));

    /* 仅处理IPv4类型数据包，IPv6包则直接发送 */
    if (ADS_PKT_TYPE_IPV4 != enIpType)
    {
        ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_UL_IPV6_PKT, 1);
        return;
    }

    /* 解码上行数据包，并提取对应报文类型中的过滤标示信息 */
    ulDecodeRet = ADS_FILTER_DecodeUlPacket(pstData, &stIPv4Filter);
    if (VOS_OK != ulDecodeRet)
    {
        /* 解析失败或不支持的报文类型不处理 */
        return;
    }

    /* 在过滤表中匹配标示信息 */
    ulRet       = ADS_FILTER_Match(&stIPv4Filter);
    if (VOS_TRUE != ulRet)
    {
        /* 没匹配到节点，则将IP标示信息添加到过滤表 */
        ADS_FILTER_AddFilter(&stIPv4Filter);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_DecodeDlIPv4NotFirstFragPacket
 功能描述  : 下行分片报文(非首片)的过滤信息提取
 输入参数  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- 下行数据包
 输出参数  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 过滤标志结构体指针
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月14日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_DecodeDlIPv4NotFirstFragPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    PS_MEM_SET(pstIPv4Filter, 0, sizeof(ADS_FILTER_IPV4_INFO_STRU));

    /* 提取分片包过滤信息 */
    pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_FRAGMENT;
    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIPv4Hdr->ucProtocol;
    pstIPv4Filter->unFilter.stFragmentFilter.usIdentification = pstIPv4Hdr->usIdentification;

    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_DecodeDlIPv4EchoReplyPacket
 功能描述  : 下行ECHO REPLY报文的过滤信息提取
 输入参数  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- 下行数据包
 输出参数  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 过滤标志结构体指针
 返 回 值  : VOS_OK     -- 下行数据包解码成功
             VOS_ERR    -- 下行数据包解码失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月14日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeDlIPv4EchoReplyPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_ICMP_HDR_STRU                  *pstIcmpHdr      = VOS_NULL_PTR;

    /* 获取ICMP报文首部 */
    pstIcmpHdr = (ADS_ICMP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

    pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_ICMP;
    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIPv4Hdr->ucProtocol;
    pstIPv4Filter->unFilter.stIcmpFilter.usIdentifier = pstIcmpHdr->unIcmp.stIcmpEcho.usIdentifier;
    pstIPv4Filter->unFilter.stIcmpFilter.usSeqNum = pstIcmpHdr->unIcmp.stIcmpEcho.usSeqNum;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_DecodeDlIPv4IcmpErrorPacket
 功能描述  : 下行ICMP差错报文的过滤信息提取
 输入参数  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- 下行数据包
 输出参数  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 过滤标志结构体指针
 返 回 值  : VOS_OK     -- 下行数据包解码成功
             VOS_ERR    -- 下行数据包解码失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月14日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeDlIPv4IcmpErrorPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_IPV4_HDR_STRU                  *pstIcmpIPv4Hdr  = VOS_NULL_PTR;
    ADS_TCP_HDR_STRU                   *pstTcpHdr       = VOS_NULL_PTR;
    ADS_UDP_HDR_STRU                   *pstUdpHdr       = VOS_NULL_PTR;

    /* 获取ICMP报文中所带的原始数据包的IP首部指针 */
    pstIcmpIPv4Hdr = (ADS_IPV4_HDR_STRU *)(((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN + ADS_FILTER_ICMP_HDR_LEN));

    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIcmpIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIcmpIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIcmpIPv4Hdr->ucProtocol;

    if (ADS_IPPROTO_TCP == pstIcmpIPv4Hdr->ucProtocol)
    {
        pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_TCP;
        pstTcpHdr = (ADS_TCP_HDR_STRU *)((VOS_UINT8 *)pstIcmpIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);
        pstIPv4Filter->unFilter.stTcpFilter.usSrcPort = pstTcpHdr->usSrcPort;
        pstIPv4Filter->unFilter.stTcpFilter.usDstPort = pstTcpHdr->usDstPort;
    }
    else if (ADS_IPPROTO_UDP == pstIcmpIPv4Hdr->ucProtocol)
    {
        pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_UDP;
        pstUdpHdr = (ADS_UDP_HDR_STRU *)((VOS_UINT8 *)pstIcmpIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);
        pstIPv4Filter->unFilter.stUdpFilter.usSrcPort = pstUdpHdr->usSrcPort;
        pstIPv4Filter->unFilter.stUdpFilter.usDstPort = pstUdpHdr->usDstPort;
    }
    else
    {
        /* 非TCP/UDP包则退出，直接交由HOST处理 */
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_DecodeDlIPv4TcpPacket
 功能描述  : 下行TCP报文的过滤信息提取
 输入参数  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- 下行数据包
 输出参数  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 过滤标志结构体指针
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月14日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_DecodeDlIPv4TcpPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_TCP_HDR_STRU                   *pstTcpHdr       = VOS_NULL_PTR;

    /* 获取TCP报文首部 */
    pstTcpHdr = (ADS_TCP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

    pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_TCP;
    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIPv4Hdr->ucProtocol;
    pstIPv4Filter->unFilter.stTcpFilter.usSrcPort = pstTcpHdr->usDstPort;
    pstIPv4Filter->unFilter.stTcpFilter.usDstPort = pstTcpHdr->usSrcPort;

    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_DecodeDlIPv4UdpPacket
 功能描述  : 下行UDP报文的过滤信息提取
 输入参数  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- 下行数据包
 输出参数  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 过滤标志结构体指针
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月14日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_DecodeDlIPv4UdpPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter)
{
    ADS_UDP_HDR_STRU                   *pstUdpHdr       = VOS_NULL_PTR;

    /* 获取UDP报文首部 */
    pstUdpHdr = (ADS_UDP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

    pstIPv4Filter->enPktType = ADS_FILTER_PKT_TYPE_UDP;
    pstIPv4Filter->ulTmrCnt  = ADS_GET_CURR_KERNEL_TIME();
    pstIPv4Filter->stIPHeader.ulSrcAddr  = pstIPv4Hdr->unDstAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ulDstAddr  = pstIPv4Hdr->unSrcAddr.ulIpAddr;
    pstIPv4Filter->stIPHeader.ucProtocol = pstIPv4Hdr->ucProtocol;
    pstIPv4Filter->unFilter.stUdpFilter.usSrcPort = pstUdpHdr->usDstPort;
    pstIPv4Filter->unFilter.stUdpFilter.usDstPort = pstUdpHdr->usSrcPort;

    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_DecodeDlIPv4FragPacket
 功能描述  : 下行分片报文的过滤信息提取
 输入参数  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr     -- 下行数据包
 输出参数  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 过滤标志结构体指针
             ADS_FILTER_ORIG_PKT_ENUM_UINT32          *penOrigPktType -- 下行数据包原始类型
 返 回 值  : VOS_OK     -- 下行数据包解码成功
             VOS_ERR    -- 下行数据包解码失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月18日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeDlIPv4FragPacket(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter,
    ADS_FILTER_ORIG_PKT_ENUM_UINT32    *penOrigPktType)
{
    VOS_UINT32                          ulRet;

    /* 判断分片包是否为首片(首片与非首片的区别在于Offset是否为0).
        各类型判别条件如下:
                         MF      Offset
        分片包首片       1         0
        分片包中间片     1         非0
        分片包尾片       0         非0 */
    if (0 == (pstIPv4Hdr->usFlags_fo & VOS_HTONS(ADS_IP_OFFSET)))
    {
        /* 首片的处理(当前只支持TCP和UDP两种协议类型) */
        switch (pstIPv4Hdr->ucProtocol)
        {
            case ADS_IPPROTO_TCP:
                /* 记录报文原始类型 */
                *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT;

                /* 提取TCP报文过滤信息 */
                ADS_FILTER_DecodeDlIPv4TcpPacket(pstIPv4Hdr, pstIPv4Filter);

                ulRet = VOS_OK;
                break;

            case ADS_IPPROTO_UDP:
                /* 记录报文原始类型 */
                *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT;

                /* 提取UDP报文过滤信息 */
                ADS_FILTER_DecodeDlIPv4UdpPacket(pstIPv4Hdr, pstIPv4Filter);

                ulRet = VOS_OK;
                break;

            default:
                /* 其他类型报文，不处理，直接交由HOST处理 */
                ulRet = VOS_ERR;
                break;
        }
    }
    else
    {
        /* 报文为"非首片",记录报文原始类型 */
        *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_NOT_FIRST_FRAGMENT;

        /* 提取非首片的过滤信息 */
        ADS_FILTER_DecodeDlIPv4NotFirstFragPacket(pstIPv4Hdr, pstIPv4Filter);

        ulRet = VOS_OK;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_DecodeDlIPv4Packet
 功能描述  : 判断报文类型是否为TCP\UDP\ICMP(ECHO REPLY或ICMP差错报文)\分片包非首片，
             并提取对应报文类型中的过滤标示信息
             注意: 源和目的是倒换的，因为过滤表信息是按上行方向来填写的
 输入参数  : ADS_IPV4_HDR_STRU                        *pstIPv4Hdr,    -- 下行数据包
 输出参数  : ADS_FILTER_IPV4_INFO_STRU                *pstIPv4Filter  -- 过滤标志结构体指针
             ADS_FILTER_ORIG_PKT_ENUM_UINT32          *penOrigPktType -- 下行数据包原始类型
 返 回 值  : VOS_OK     -- 下行数据包解码成功
             VOS_ERR    -- 下行数据包解码失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月13日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_UINT32 ADS_FILTER_DecodeDlIPv4Packet(
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr,
    ADS_FILTER_IPV4_INFO_STRU          *pstIPv4Filter,
    ADS_FILTER_ORIG_PKT_ENUM_UINT32    *penOrigPktType)
{
    ADS_ICMP_HDR_STRU                                      *pstIcmpHdr           = VOS_NULL_PTR;
    ADS_FILTER_DECODE_DL_ICMP_FUNC                          pDecodeDlIcmpFunc    = VOS_NULL_PTR;
    ADS_FILTER_DECODE_DL_ICMP_FUNC_STRU                    *pDecodeDlIcmpFuncTbl = VOS_NULL_PTR;
    VOS_UINT32                                              ulRet                = VOS_ERR;

    /* 处理"分片包".各类型判别条件如下:
                         MF      Offset
        非分片包         0         0
        分片包首片       1         0
        分片包中间片     1         非0
        分片包尾片       0         非0 */
    if (0 != (pstIPv4Hdr->usFlags_fo & VOS_HTONS(ADS_IP_MF | ADS_IP_OFFSET)))
    {
        return ADS_FILTER_DecodeDlIPv4FragPacket(pstIPv4Hdr, pstIPv4Filter, penOrigPktType);
    }

    /* 处理TCP\UDP\ICMP(ECHO REPLY或ICMP差错报文) */
    switch (pstIPv4Hdr->ucProtocol)
    {
        case ADS_IPPROTO_ICMP:
            pstIcmpHdr = (ADS_ICMP_HDR_STRU *)((VOS_UINT8 *)pstIPv4Hdr + ADS_FILTER_IPV4_HDR_LEN);

            if (pstIcmpHdr->ucType < ADS_FILTER_GET_DL_ICMP_FUNC_TBL_SIZE())
            {
                pDecodeDlIcmpFuncTbl = ADS_FILTER_GET_DL_ICMP_FUNC_TBL_ADDR(pstIcmpHdr->ucType);
                pDecodeDlIcmpFunc = pDecodeDlIcmpFuncTbl->pFunc;
                if (VOS_NULL_PTR != pDecodeDlIcmpFunc)
                {
                    /* 记录报文原始类型 */
                    *penOrigPktType = pDecodeDlIcmpFuncTbl->enOrigPktType;

                    /* 提取ICMP报文过滤信息 */
                    ulRet = pDecodeDlIcmpFunc(pstIPv4Hdr, pstIPv4Filter);
                }
            }
            break;

        case ADS_IPPROTO_TCP:
            /* 记录报文原始类型 */
            *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_TCP;

            /* 提取TCP报文过滤信息 */
            ADS_FILTER_DecodeDlIPv4TcpPacket(pstIPv4Hdr, pstIPv4Filter);

            ulRet = VOS_OK;
            break;

        case ADS_IPPROTO_UDP:
            /* 记录报文原始类型 */
            *penOrigPktType = ADS_FILTER_ORIG_PKT_DL_IPV4_UDP;

            /* 提取UDP报文过滤信息 */
            ADS_FILTER_DecodeDlIPv4UdpPacket(pstIPv4Hdr, pstIPv4Filter);

            ulRet = VOS_OK;
            break;

        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_ProcDlIPv4Packet
 功能描述  : ADS过滤处理IPv4类型下行数据包处理
 输入参数  : IMM_ZC_STRU               *pstData     -- 下行数据包
 输出参数  : 无
 返 回 值  : VOS_OK   -- 数据包处理完毕
             VOS_ERR  -- 数据包未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_UINT32 ADS_FILTER_ProcDlIPv4Packet(
    IMM_ZC_STRU                        *pstData)
{
    ADS_IPV4_HDR_STRU                  *pstIPv4Hdr      = VOS_NULL_PTR;
    ADS_FILTER_IPV4_INFO_STRU           stIPv4Filter;
    VOS_UINT32                          ulDecodeRet;
    VOS_UINT32                          ulRet;
    ADS_FILTER_ORIG_PKT_ENUM_UINT32     enOrigPktType;

    /* 获取IPV4报文首部地址 */
    pstIPv4Hdr  = (ADS_IPV4_HDR_STRU *)IMM_ZcGetDataPtr(pstData);

    /* 判断报文类型并提取过滤标示信息 */
    PS_MEM_SET(&stIPv4Filter, 0, sizeof(ADS_FILTER_IPV4_INFO_STRU));
    ulDecodeRet = ADS_FILTER_DecodeDlIPv4Packet(pstIPv4Hdr, &stIPv4Filter, &enOrigPktType);
    if (VOS_OK != ulDecodeRet)
    {
        /* 解析失败或不支持的报文类型不处理，交给HOST处理 */
        return VOS_ERR;
    }

    /* 在过滤表中匹配标示信息 */
    ulRet       = ADS_FILTER_Match(&stIPv4Filter);
    if (VOS_TRUE == ulRet)
    {
        /* 找到了匹配节点，如果是分片包首片，则需要将首片中的相关信息提取出来并添加到过滤表中，
            作为后续非首片分片包的过滤条件 */
        if (ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT == enOrigPktType)
        {
            ADS_FILTER_DecodeDlIPv4NotFirstFragPacket(pstIPv4Hdr, &stIPv4Filter);

            /* 将分片包过滤信息添加到过滤表中 */
            ADS_FILTER_AddFilter(&stIPv4Filter);
        }

        ADS_FILTER_DBG_STATISTIC(enOrigPktType, 1);

        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_ProcDlIPv6Packet
 功能描述  : ADS过滤处理IPv6类型下行数据包处理
 输入参数  : IMM_ZC_STRU               *pstData     -- 下行数据包
 输出参数  : 无
 返 回 值  : VOS_OK   -- 数据包处理完毕
             VOS_ERR  -- 数据包未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月14日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_UINT32 ADS_FILTER_ProcDlIPv6Packet(
    IMM_ZC_STRU                        *pstData)
{
    ADS_IPV6_HDR_STRU                  *pstIPv6Hdr      = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* 获取IPV6首部指针 */
    pstIPv6Hdr = (ADS_IPV6_HDR_STRU *)IMM_ZcGetDataPtr(pstData);

    /* 判断下行包中的目的地址是否与DEVICE端地址相同 */
    if (ADS_FILTER_IS_IPV6_ADDR_IDENTICAL(ADS_FILTER_GET_IPV6_ADDR(), &(pstIPv6Hdr->unDstAddr)))
    {
        ADS_FILTER_DBG_STATISTIC(ADS_FILTER_ORIG_PKT_DL_IPV6_PKT, 1);

        ulRet = VOS_OK;
    }
    else
    {
        ulRet = VOS_ERR;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_ProcDlPacket
 功能描述  : ADS过滤器下行数据包处理
 输入参数  : IMM_ZC_STRU               *pstData     -- 下行数据包
             ADS_PKT_TYPE_ENUM_UINT8    enIpType    -- 下行数据包IP类型
 输出参数  : 无
 返 回 值  : VOS_OK     -- 数据包处理完毕
             VOS_ERR    -- 数据包未处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_UINT32 ADS_FILTER_ProcDlPacket(
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType)
{
    VOS_UINT32                          ulRet;

    /* 初始化 */
    ulRet   = VOS_ERR;

    /* 根据IP类型选择过滤处理方式 */
    switch (enIpType)
    {
        case ADS_PKT_TYPE_IPV4:
            /* IPv4类型需要匹配过滤表 */
            ulRet = ADS_FILTER_ProcDlIPv4Packet(pstData);
            break;

        case ADS_PKT_TYPE_IPV6:
            /* IPv6类型需要匹配IP地址是否相同 */
            ulRet = ADS_FILTER_ProcDlIPv6Packet(pstData);
            break;

        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : ADS_Ipv4AddrItoa
 功能描述  : 把IPV4地址由数字格式转换成字符串格式
 输入参数  : pucNumber [in] 数字格式的IP地址,char pucNumber[4]={192,168,0,1}
 输出参数  : pcString [out] 字符串格式的IP地址,char * pcString="192.168.0.1"
 返 回 值  : VOS_OK     -- 转换成功
             VOS_ERR    -- 转换失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_UINT32 ADS_Ipv4AddrItoa(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber)
{
    VOS_UINT32                          ret = VOS_OK;
    VOS_CHAR                            astringTmp[8] = {0};

    if ( (VOS_NULL_PTR == pcString) || (VOS_NULL_PTR == pucNumber) )
    {
        ret = VOS_ERR;
    }
    else
    {
        PS_MEM_SET(pcString, 0, ADS_MAX_IPV4_ADDR_LEN);
        sprintf(astringTmp, "%d", pucNumber[0]);
        strcat(pcString, astringTmp);

        sprintf(astringTmp, ".%d", pucNumber[1]);
        strcat(pcString, astringTmp);

        sprintf(astringTmp, ".%d", pucNumber[2]);
        strcat(pcString, astringTmp);

        sprintf(astringTmp, ".%d", pucNumber[3]);
        strcat(pcString, astringTmp);
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_ShowStatisticInfo
 功能描述  : 可维可测打印函数，打印上下行报文统计个数
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月14日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_ShowStatisticInfo(VOS_VOID)
{
    PS_PRINTF("\n********************ADS FILTER 上行统计信息************************\n");
    PS_PRINTF("上行IPv4类型TCP报文个数统计              %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_TCP));
    PS_PRINTF("上行IPv4类型UDP报文个数统计              %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_UDP));
    PS_PRINTF("上行IPv4类型Echo Req报文个数统计         %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_ECHOREQ));
    PS_PRINTF("上行IPv4类型分片报文(非首片)个数统计     %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_FIRST_FRAGMENT));
    PS_PRINTF("上行IPv4类型不支持过滤的报文个数统计     %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV4_NOT_SUPPORT));
    PS_PRINTF("上行IPv6类型报文个数统计                 %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_UL_IPV6_PKT));

    PS_PRINTF("********************ADS FILTER 下行统计信息************************\n");
    PS_PRINTF("下行IPv4类型TCP匹配报文个数统计          %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_TCP));
    PS_PRINTF("下行IPv4类型UDP匹配报文个数统计          %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_UDP));
    PS_PRINTF("下行IPv4类型Echo Reply匹配报文个数统计   %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_ECHOREPLY));
    PS_PRINTF("下行IPv4类型ICMP差错报文匹配报文个数统计 %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_ICMPERROR));
    PS_PRINTF("下行IPv4类型首片分片匹配报文个数统计     %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_FIRST_FRAGMENT));
    PS_PRINTF("下行IPv4类型非首片分片匹配报文个数统计   %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV4_NOT_FIRST_FRAGMENT));
    PS_PRINTF("下行IPv6类型匹配报文个数统计             %d\n", ADS_FILTER_DBG_GET_STATS_BY_INDEX(ADS_FILTER_ORIG_PKT_DL_IPV6_PKT));

    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_ResetStatisticInfo
 功能描述  : 清除可维可测信息
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月14日
    作    者   : L47619
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_ResetStatisticInfo(VOS_VOID)
{
    PS_MEM_SET(ADS_FILTER_DBG_GET_STATS_ARRAY_ADDR(), 0, (VOS_SIZE_T)(sizeof(VOS_UINT32) * ADS_FILTER_ORIG_PKT_BUTT));
    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_ShowFilterLists
 功能描述  : 可维可测打印函数，打印出所有的过滤器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_ShowFilterLists(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    ADS_FILTER_NODE_STRU               *pstNode     = VOS_NULL_PTR;
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstListTmp  = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead  = VOS_NULL_PTR;
    VOS_CHAR                            acIPv4Addr[ADS_MAX_IPV4_ADDR_LEN + 1];

    PS_PRINTF("*************************** ADS FILTER 过滤器列表 ******************************\n");
    PS_PRINTF("  索引  报文类型    老化周期       源地址       目的地址        标示1   标示2\n");
    PS_PRINTF("********************************************************************************\n");

    for (ulIndex = 0; ulIndex < ADS_FILTER_MAX_LIST_NUM; ulIndex++)
    {
        pstListHead = ADS_FILTER_GET_LIST(ulIndex);

        /* 循环遍历链表，查找匹配项 */
        msp_list_for_each_safe(pstMe, pstListTmp, pstListHead)
        {
            pstNode = msp_list_entry(pstMe, ADS_FILTER_NODE_STRU, stList);

            /* 打印索引 */
            PS_PRINTF(" [%3d] ", ulIndex);

            /* 打印报文类型 */
            switch (pstNode->stFilter.enPktType)
            {
                case ADS_FILTER_PKT_TYPE_TCP:
                    PS_PRINTF("   TCP   ");
                    break;
                case ADS_FILTER_PKT_TYPE_UDP:
                    PS_PRINTF("   UDP   ");
                    break;
                case ADS_FILTER_PKT_TYPE_ICMP:
                    PS_PRINTF("   ICMP  ");
                    break;
                case ADS_FILTER_PKT_TYPE_FRAGMENT:
                    PS_PRINTF("   FRAG  ");
                    break;
                default:
                    PS_PRINTF("  OTHER  ");
                    break;
            }

            /* 打印老化周期 */
            PS_PRINTF("%11d  ", pstNode->stFilter.ulTmrCnt);

            /* 打印源地址 */
            ADS_Ipv4AddrItoa(acIPv4Addr, (VOS_UINT8*)&pstNode->stFilter.stIPHeader.ulSrcAddr);
            PS_PRINTF("%-16s", acIPv4Addr);

            /* 打目的地址 */
            ADS_Ipv4AddrItoa(acIPv4Addr, (VOS_UINT8*)&pstNode->stFilter.stIPHeader.ulDstAddr);
            PS_PRINTF("%-16s", acIPv4Addr);

            /* 打印标示1 */
            PS_PRINTF("%8d", VOS_NTOHS(pstNode->stFilter.unFilter.stTcpFilter.usSrcPort));

            /* 打印标示2 */
            PS_PRINTF("%8d\n", VOS_NTOHS(pstNode->stFilter.unFilter.stTcpFilter.usDstPort));
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_FILTER_ShowIPv6Addr
 功能描述  : 可维可测打印函数，打印IPv6地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年06月04日
    作    者   : l00198894
    修改内容   : V3R3 Share-PDP项目新增函数
*****************************************************************************/
VOS_VOID ADS_FILTER_ShowIPv6Addr(VOS_VOID)
{
    VOS_UINT8                          *pucIPv6Addr = VOS_NULL_PTR;
    VOS_UINT8                           ucLoop;

    pucIPv6Addr = ADS_FILTER_GET_IPV6_ADDR()->aucIpAddr;

    for (ucLoop = 0; ucLoop < ADS_IPV6_ADDR_LEN; ucLoop++)
    {
        if ( (0 != ucLoop) && (0 == ucLoop % 2) )
        {
            PS_PRINTF(":");
        }
        PS_PRINTF("%02x", pucIPv6Addr[ucLoop]);
    }

    PS_PRINTF("\n");

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
