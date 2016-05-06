/******************************************************************************

                  版权所有 (C), 2006, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsIpFragmentProc.c
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2011年12月12日
  最近修改   :
  功能描述   : CDS软调信息
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月12日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767*/
#define  THIS_FILE_ID        PS_FILE_ID_CDS_IP_FRAGMENT_PROC_C
/*lint +e767*/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CDS.h"
#include "CdsIpFragmentProc.h"
#include "CdsSoftFilter.h"

CDS_IP_FRAGMENT_BUFF_STRU       g_stCdsIpFragBuff;


/*****************************************************************************
  2 外部函数声明
*****************************************************************************/


/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
******************************************************************************/


/******************************************************************************
   5 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : CDS_DecodeIpv4Pkt
 功能描述  : 获取IPV4分片信息
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_DecodeIpv4Pkt( const TTF_MEM_ST  *pstIpPkt,
                                   CDS_IPV4_FRAGMENT_INFO_STRU *pstIpv4FragInfo)
{
    IPV4_HDR_STRU           *pstIpHdr;

    CDS_ASSERT(VOS_NULL_PTR != pstIpPkt);
    CDS_ASSERT(VOS_NULL_PTR != pstIpv4FragInfo);

    pstIpHdr = (IPV4_HDR_STRU *)((VOS_UINT32)(pstIpPkt->pData));
    pstIpv4FragInfo->unDstAddr.ulIpAddr = pstIpHdr->unDestAddr.ulIpAddr;
    pstIpv4FragInfo->unSrcAddr.ulIpAddr = pstIpHdr->unSrcAddr.ulIpAddr;
    pstIpv4FragInfo->usIpIdentity       = pstIpHdr->usIdentification;

    return;
}


/*****************************************************************************
 函 数 名  : CDS_Ipv4FragmentInfoEqual
 功能描述  : 比较两个IPV4分片信息是否相同
 输入参数  :
 输出参数  :
 返 回 值  : 相同返回PS_TRUE；不同返回PS_FALSE.

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_Ipv4FragmentInfoEqual(const CDS_IPV4_FRAGMENT_INFO_STRU *pstSrc,
                                             const CDS_IPV4_FRAGMENT_INFO_STRU *pstTarget)
{
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstSrc, PS_FALSE);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstTarget, PS_FALSE);

    if (pstSrc->usIpIdentity != pstTarget->usIpIdentity)
    {
        return PS_FALSE;
    }

    if (pstSrc->unDstAddr.ulIpAddr != pstTarget->unDstAddr.ulIpAddr)
    {
        return PS_FALSE;
    }

    if (pstSrc->unSrcAddr.ulIpAddr != pstTarget->unSrcAddr.ulIpAddr)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


/*****************************************************************************
 函 数 名  : CDS_SaveIpv4FragmentInfo
 功能描述  : 保存IPV4分片信息
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_SaveIpv4FragmentInfo(const CDS_IPV4_FRAGMENT_INFO_STRU *pstSrcInfo)
{
    CDS_IPV4_FRAGMENT_BUFF_STRU     *pstIpv4FragBuff;
    CDS_IPV4_FRAGMENT_INFO_STRU     *pstDstInfo;

    CDS_ASSERT(VOS_NULL_PTR != pstSrcInfo);

    pstIpv4FragBuff = CDS_GET_IPV4_FRAGMENT_BUFF();
    pstDstInfo = &(pstIpv4FragBuff->astSegBuff[pstIpv4FragBuff->ulIndex]);
    pstIpv4FragBuff->ulIndex = TTF_MOD_ADD(pstIpv4FragBuff->ulIndex,1,CDS_IPV4_FRAGMENT_BUFF_SIZE);
    PS_MEM_CPY(pstDstInfo,pstSrcInfo,sizeof(CDS_IPV4_FRAGMENT_INFO_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : CDS_GetEpsbIDByIpv4FragInfo
 功能描述  : 根据IPV4分片信息从分片缓存中查找对应的EPSBID。
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_GetEpsbIDByIpv4FragInfo(VOS_UINT8 *pucEpsbID,
                                                 const CDS_IPV4_FRAGMENT_INFO_STRU *pstSrcInfo)
{
    CDS_IPV4_FRAGMENT_BUFF_STRU     *pstIpv4FragBuff;
    CDS_IPV4_FRAGMENT_INFO_STRU     *pstFragItem;
    VOS_UINT32                       ulCnt;

    CDS_ASSERT_RTN(VOS_NULL_PTR != pstSrcInfo, PS_FAIL);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pucEpsbID,  PS_FAIL);

    pstIpv4FragBuff = CDS_GET_IPV4_FRAGMENT_BUFF();
    for (ulCnt = 0; ulCnt < CDS_IPV4_FRAGMENT_BUFF_SIZE; ulCnt ++)
    {
        pstFragItem = &(pstIpv4FragBuff->astSegBuff[ulCnt]);
        if (PS_TRUE == CDS_Ipv4FragmentInfoEqual(pstFragItem,pstSrcInfo))
        {
            *pucEpsbID = pstFragItem->ucEpsbID;
            return PS_SUCC;
        }
    }

    return PS_FAIL;

}

/*****************************************************************************
 函 数 名  : CDS_IpV4FragmentProc
 功能描述  : 处理IPV4分片信息
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_Ipv4FragmentProc(VOS_UINT8 *pucEpsbID,
                                       const TTF_MEM_ST  *pstIpPkt,
                                       const IPF_RESULT_STRU *pstIpfRslt )

{
    CDS_IPV4_FRAGMENT_INFO_STRU       stIpv4Frag = {0};

    CDS_ASSERT_RTN(VOS_NULL_PTR != pucEpsbID,  PS_FAIL);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstIpPkt,   PS_FAIL);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstIpfRslt, PS_FAIL);

    CDS_DecodeIpv4Pkt(pstIpPkt,&stIpv4Frag);

    /*search buffer*/


    /*save new info to buffer*/
    if ((CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_HEAD == pstIpfRslt->usIpSegInfo)
        &&(CDS_UL_IPF_BEARER_ID_INVALID != pstIpfRslt->usBearedId))
    {
        *pucEpsbID = (VOS_UINT8)pstIpfRslt->usBearedId;
        stIpv4Frag.ucEpsbID = (VOS_UINT8)pstIpfRslt->usBearedId;
        CDS_IPFRAG_RX_IPV4_IPF_SUCC(1);
        CDS_SaveIpv4FragmentInfo(&stIpv4Frag);
        return PS_SUCC;
    }

    CDS_IPFRAG_RX_IPV4_IPF_FAIL(1);
    if (PS_SUCC == CDS_GetEpsbIDByIpv4FragInfo(pucEpsbID,&stIpv4Frag))
    {
        return PS_SUCC;
    }
    return PS_FAIL;

}



/*****************************************************************************
 函 数 名  : CDS_DecodeIpv6Pkt
 功能描述  : 解析IPV6信息，获得IPV6分片信息。
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_DecodeIpv6Pkt(const TTF_MEM_ST  *pstIpPkt, CDS_IPV6_FRAGMENT_INFO_STRU *pstIpv6FragInfo)
{
    IPV6_HDR_STRU         *pstIpv6Hdr;
    VOS_UINT8              ucNextHdr;
    VOS_UINT8             *pstExtHdr;
    IPV6_FRAGMENT_HDR     *pstFragHdr;
    IPV6_OPTION_HDR       *pstOptHdr;
    VOS_UINT32             ulOptLen;


    CDS_ASSERT(VOS_NULL_PTR != pstIpPkt);
    CDS_ASSERT(VOS_NULL_PTR != pstIpv6FragInfo);

    pstIpv6Hdr = (IPV6_HDR_STRU *)((VOS_UINT32)(pstIpPkt->pData));
    PS_MEM_CPY(&(pstIpv6FragInfo->unSrcAddr),&(pstIpv6Hdr->unSrcAddr),IPV6_ADDR_LEN);
    PS_MEM_CPY(&(pstIpv6FragInfo->unDstAddr),&(pstIpv6Hdr->unDstAddr),IPV6_ADDR_LEN);

    ucNextHdr = pstIpv6Hdr->ucNextHdr;
    pstExtHdr = pstIpPkt->pData + sizeof(IPV6_HDR_STRU);

    while (CDS_Ipv6ExtHdr(ucNextHdr))
    {
        pstOptHdr = (IPV6_OPTION_HDR*)((VOS_UINT32)pstExtHdr);
        if ((IPV6_NEXTHDR_NONE == ucNextHdr) || (IPV6_NEXTHDR_ESP == ucNextHdr))
        {
            return;
        }

        if (IPV6_NEXTHDR_FRAGMENT == ucNextHdr)
        {
            pstFragHdr = (IPV6_FRAGMENT_HDR *)((VOS_UINT32)pstExtHdr);
            pstIpv6FragInfo->ulIdentity = pstFragHdr->ulIdentification;
            return;
        }

        if (IPV6_NEXTHDR_AUTH == ucNextHdr)
        {
            ulOptLen = (pstOptHdr->ucHdrLen + 2) << 2;
        }
        else
        {
            ulOptLen = IPV6_OPTION_LEN(pstOptHdr);
        }

        ucNextHdr = pstOptHdr->ucNextHdr;
        pstExtHdr = pstExtHdr + ulOptLen;
    }

    return;
}


/*****************************************************************************
 函 数 名  : CDS_Ipv6FragmentInfoEqual
 功能描述  : 比较IPV6分片信息，判断是否是同一个IPV6分片
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_Ipv6FragmentInfoEqual(const CDS_IPV6_FRAGMENT_INFO_STRU *pstSrc,
                                            const CDS_IPV6_FRAGMENT_INFO_STRU *pstTarget)
{
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstSrc, PS_FALSE);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstTarget, PS_FALSE);

    if (pstSrc->ulIdentity != pstTarget->ulIdentity)
    {
        return PS_FALSE;
    }

    if (PS_FALSE == CDS_Ipv6AddrEqual(&(pstSrc->unDstAddr),&(pstTarget->unDstAddr)))
    {
        return PS_FALSE;
    }

    if (PS_FALSE == CDS_Ipv6AddrEqual(&(pstSrc->unSrcAddr),&(pstTarget->unSrcAddr)))
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


/*****************************************************************************
 函 数 名  : CDS_SaveIpV6FragmentInfo
 功能描述  : 保存IPV6分片信息
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_SaveIpv6FragmentInfo(const CDS_IPV6_FRAGMENT_INFO_STRU *pstSrcInfo)
{
    CDS_IPV6_FRAGMENT_BUFF_STRU     *pstIpv6FragBuff;
    CDS_IPV6_FRAGMENT_INFO_STRU     *pstDstInfo;

    CDS_ASSERT(VOS_NULL_PTR != pstSrcInfo);
    pstIpv6FragBuff = CDS_GET_IPV6_FRAGMENT_BUFF();
    pstDstInfo = &(pstIpv6FragBuff->astSegBuff[pstIpv6FragBuff->ulIndex]);
    pstIpv6FragBuff->ulIndex = TTF_MOD_ADD(pstIpv6FragBuff->ulIndex,1,CDS_IPV6_FRAGMENT_BUFF_SIZE);
    PS_MEM_CPY(pstDstInfo,pstSrcInfo,sizeof(CDS_IPV6_FRAGMENT_INFO_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : CDS_GetEpsbIDByIpv6FragInfo
 功能描述  : 根据IPV6分片信息查找IPV6分片对应的承载信息。
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_GetEpsbIDByIpv6FragInfo(VOS_UINT8 *pucEpsbID,
                                                const CDS_IPV6_FRAGMENT_INFO_STRU *pstSrcInfo)
{
    CDS_IPV6_FRAGMENT_BUFF_STRU     *pstIpv6FragBuff;
    CDS_IPV6_FRAGMENT_INFO_STRU     *pstFragItem;
    VOS_UINT32                       ulCnt;

    CDS_ASSERT_RTN(VOS_NULL_PTR != pstSrcInfo, PS_FAIL);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pucEpsbID,  PS_FAIL);

    pstIpv6FragBuff = CDS_GET_IPV6_FRAGMENT_BUFF();
    for (ulCnt = 0; ulCnt < CDS_IPV6_FRAGMENT_BUFF_SIZE; ulCnt ++)
    {
        pstFragItem = &(pstIpv6FragBuff->astSegBuff[ulCnt]);
        if (PS_TRUE == CDS_Ipv6FragmentInfoEqual(pstFragItem,pstSrcInfo))
        {
            *pucEpsbID = pstFragItem->ucEpsbID;
            return PS_SUCC;
        }
    }

    return PS_FAIL;

}

/*****************************************************************************
 函 数 名  : CDS_Ipv6FragmentProc
 功能描述  : 处理IP分片信息
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_Ipv6FragmentProc( VOS_UINT8 *pucEpsbID,
                                        const TTF_MEM_ST      *pstIpPkt,
                                        const IPF_RESULT_STRU *pstIpfRslt )
{
    CDS_IPV6_FRAGMENT_INFO_STRU       stIpv6Frag = {0};

    CDS_ASSERT_RTN(VOS_NULL_PTR != pucEpsbID,  PS_FAIL);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstIpPkt,   PS_FAIL);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstIpfRslt, PS_FAIL);

    CDS_DecodeIpv6Pkt(pstIpPkt,&stIpv6Frag);

    if ((CDS_UL_IPF_IPSEG_TYPE_FRAGMENT_HEAD == pstIpfRslt->usIpSegInfo)


        &&(CDS_UL_IPF_BEARER_ID_INVALID != pstIpfRslt->usBearedId))
    {
        *pucEpsbID = (VOS_UINT8)pstIpfRslt->usBearedId;
        stIpv6Frag.ucEpsbID = (VOS_UINT8)pstIpfRslt->usBearedId;
        CDS_IPFRAG_RX_IPV6_IPF_SUCC(1);
        CDS_SaveIpv6FragmentInfo(&stIpv6Frag);
        return PS_SUCC;
    }

    CDS_IPFRAG_RX_IPV6_IPF_FAIL(1);
    if (PS_SUCC == CDS_GetEpsbIDByIpv6FragInfo(pucEpsbID,&stIpv6Frag))
    {
        return PS_SUCC;
    }
    return PS_FAIL;

}

/*****************************************************************************
 函 数 名  : CDS_IpFragmentProc
 功能描述  : 处理IP分片信息
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CDS_IpFragmentProc( VOS_UINT8       *pucEpsbID,
                                      TTF_MEM_ST      *pstIpPkt,
                                      const IPF_RESULT_STRU *pstIpfRslt,
                                      const CDS_ENTITY_STRU  *pstCdsEntity)
{
    VOS_UINT32          ulRslt;

    CDS_ASSERT_RTN(VOS_NULL_PTR != pucEpsbID, PS_FAIL);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstIpPkt, PS_FAIL);
    CDS_ASSERT_RTN(VOS_NULL_PTR != pstIpfRslt, PS_FAIL);

    if (IPF_IPTYPE_V4 == pstIpfRslt->usIpType)
    {
        CDS_IPFRAG_RX_IPV4_PKT(1);
        ulRslt = CDS_Ipv4FragmentProc(pucEpsbID, pstIpPkt, pstIpfRslt);
    }
    else
    {
        CDS_IPFRAG_RX_IPV6_PKT(1);
        ulRslt = CDS_Ipv6FragmentProc(pucEpsbID, pstIpPkt, pstIpfRslt);
    }

    if (PS_SUCC == ulRslt)
    {
        CDS_IPFRAG_LOCAL_PROC_SUCC(1);
        return PS_SUCC;
    }

    CDS_IPFRAG_LOCAL_PROC_FAIL(1);

#if (CDS_FEATURE_LTE == CDS_FEATURE_ON)
    if (MMC_CDS_MODE_LTE == pstCdsEntity->enRanMode)
    {
        /*get default epsbid by src ip address*/
        return CDS_ERABM_GetIpFragEpsbId(pucEpsbID, pstIpPkt,pstIpPkt->usUsed);
    }
#endif

    return PS_FAIL;
}


/*****************************************************************************
 函 数 名  : CDS_PrintPktData
 功能描述  : 打印数据包内存
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_PrintPktData(const VOS_UINT8 *pucPkt, VOS_UINT32 ulLen)
{
    VOS_UINT32   ulCnt;

    CDS_ASSERT(VOS_NULL_PTR != pucPkt);

    for (ulCnt = 1; ulCnt <= ulLen; ulCnt ++)
    {
        PS_PRINTF("%.2x ",pucPkt[ulCnt - 1]);
        if (0 == (ulCnt % 16))
        {
            PS_PRINTF("\n");
        }
    }

    PS_PRINTF("\n");

    return;
}


/*****************************************************************************
 函 数 名  : CDS_ClearIpFragBuff
 功能描述  : 清空本地IP分片缓存信息
 输入参数  :
 输出参数  :
 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史  :
    1.日    期   : 2012年05月08日
      作    者   : y00151394
      修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CDS_ClearIpFragBuff(VOS_VOID)
{
    PS_MEM_SET(&g_stCdsIpFragBuff,0, sizeof(CDS_IP_FRAGMENT_BUFF_STRU));
    return;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

