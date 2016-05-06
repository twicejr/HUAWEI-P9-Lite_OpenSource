/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasERabmIpFilter.c
  版 本 号   : 初稿
  作    者   : L62099
  生成日期   : 2011年2月26日
  最近修改   :
  功能描述   : 本文件为RABM TFT功能在IP Filter硬件加速上的适配，主要包括将TFT
               参数转换为硬件识别的IP Filter格式，以及Filter排序，Filter
               配置等功能
  函数列表   :
  修改历史   :
  1.日    期   : 2011年2月26日
    作    者   : L62099
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmPublic.h"
#include  "NasERabmIpFilter.h"
/*#include  "TlPsDrv.h"*/
#include  "LUPAppItf.h"
/*#include  "NasERabmPdcpMsgProc.h"*/
#include  "NasERabmIpfOm.h"
#include  "NasIpInterface.h"
#include  "NasERabmAppMsgProc.h"
/*#include  "NasERabmIpMsgProc.h"*/
#include  "NasEsmPublic.h"
#include  "NasERabmMain.h"
/*#include  "DataDispatch.h"*/
#include  "CdsInterface.h"
#include  "stdlib.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMIPFILTER_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMIPFILTER_C
/*lint +e767*/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/* IPF公共参数配置信息 */
/*lint -e528*/
/*STATIC IPF_COMMON_PARA_S g_stNasERabmIpfConfigInfo = {0};*/

/*lint +e528*/
/* RABM IPF的Filter队列, 保存目前使用的所有Filter */
NAS_ERABM_IPF_FILTER_ARRAY g_stNasERabmIpfFilterArray = {0};

NAS_ERABM_UL_NDIS_FILTER_FLAG_ENUM_UINT32 g_enUlNdisFilterValidFlag = NAS_ERABM_UL_NDIS_FILTER_INVALID;

NAS_ERABM_IPF_UL_NDIS_FILTER_INFO g_astNasERabmUlNdisFilter[NAS_ERABM_IPF_MAX_UL_NDIS_FILTER];

/* 上行NDIS Filter ID与Filter对应BID的绑定关系 */
STATIC VOS_UINT32 g_aulNasERabmUlNdisFilterTypeTable[][2] =
{
    {NAS_ERABM_IPF_UL_NDIS_FILTER_DHCP4,    CDS_UL_IPF_BEARER_ID_DHCPV4},
    {NAS_ERABM_IPF_UL_NDIS_FILTER_DHCP6,    CDS_UL_IPF_BEARER_ID_DHCPV6},
    {NAS_ERABM_IPF_UL_NDIS_FILTER_RS,       CDS_UL_IPF_BEARER_ID_ICMPV6},
    {NAS_ERABM_IPF_UL_NDIS_FILTER_RA,       CDS_UL_IPF_BEARER_ID_ICMPV6},
    {NAS_ERABM_IPF_UL_NDIS_FILTER_NS,       CDS_UL_IPF_BEARER_ID_ICMPV6},
    {NAS_ERABM_IPF_UL_NDIS_FILTER_NA,       CDS_UL_IPF_BEARER_ID_ICMPV6},
    {NAS_ERABM_IPF_UL_NDIS_FILTER_REDIRECT, CDS_UL_IPF_BEARER_ID_ICMPV6},
    {NAS_ERABM_IPF_UL_NDIS_FILTER_LOC_PING6,CDS_UL_IPF_BEARER_ID_ICMPV6},
    {NAS_ERABM_IPF_UL_NDIS_FILTER_LOC_FE80, CDS_UL_IPF_BEARER_ID_LL_FE80},
    {NAS_ERABM_IPF_UL_NDIS_FILTER_LOC_FF,   CDS_UL_IPF_BEARER_ID_LL_FF}
};
/*****************************************************************************
  3 Function
*****************************************************************************/

/*lint -e960*/
/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfUlNdisFilterInit
 功能描述  : 定义上行 NDIS模块使用的Filter类型和参数，保存在全局变量中
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月3日
    作    者   : l00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_ERABM_IpfUlNdisFilterInit( VOS_VOID )
{
    NAS_ERABM_IPF_UL_NDIS_FILTER_INFO *pstFilter;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_IpfUlNdisFilterInit is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_IpfUlNdisFilterInit_ENUM, LNAS_ENTRY);

    /* 下行规格支持12个Filter， 目前使用了10个，如有添加超过12个，需要修改
      对应宏定义，注意不要溢出 */

    /* 定义上行NDIS DHCPv4 类型Filter */
    NAS_ERABM_IPF_DEF_UL_NDIS_DHCPV4_FILTER();

    /* 定义上行NDIS DHCPv6类型的下行Filter */
    NAS_ERABM_IPF_DEF_UL_NDIS_DHCPV6_FILTER();

    /* 定义上行NDIS ICMP Router Solicitation Filter */
    NAS_ERABM_IPF_DEF_UL_NDIS_ICMP_RS_FILTER();

    /* 定义上行NDIS ICMP Router Advertisement Filter */
    NAS_ERABM_IPF_DEF_UL_NDIS_ICMP_RA_FILTER();

    /* 定义上行NDIS ICMP Neighbor Solicitation Filter */
    NAS_ERABM_IPF_DEF_UL_NDIS_ICMP_NS_FILTER();

    /* 定义上行NDIS ICMP Neighbor Advertisement Filter */
    NAS_ERABM_IPF_DEF_UL_NDIS_ICMP_NA_FILTER();

    /* 定义上行NDIS ICMP Redirect Filter */
    NAS_ERABM_IPF_DEF_UL_NDIS_ICMP_REDIRECT_FILTER();

    /* 定义上行NDIS ICMP ECHO REQUEST Filter */
    NAS_ERABM_IPF_DEF_UL_NDIS_LOC_PING6_FILTER();

    /* 定义上行NDIS 目的地址FE80打头定义 Filter */
    NAS_ERABM_IPF_DEF_UL_NDIS_LOC_FE80_FILTER();

    /* 定义上行NDIS 目的地址FF打头定义 Filter */
    NAS_ERABM_IPF_DEF_UL_NDIS_LOC_FF_FILTER();
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfGetFreeFilter
 功能描述  : 从IP Filter 队列中查找空闲的IP Filter
 输入参数  : NAS_ERABM_IPF_DIRECTION_UINT32 enDir
 输出参数  : 无
 返 回 值  : IPF_FILTER_CONFIG_S *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
IPF_FILTER_CONFIG_S * NAS_ERABM_IpfGetFreeFilter(NAS_ERABM_IPF_DIRECTION_UINT32 enDir)
{
    /* 获取上行Filter */
    if((NAS_ERABM_IPF_DIRECTION_UL == enDir)&&(!NAS_ERABM_IPF_IS_UL_FILTER_FULL()))
    {
        return NAS_ERABM_IPF_GET_UL_FILTER_PTR(NAS_ERABM_IPF_GET_UL_FILTER_NUM());
    }

    /* 获取下行Filter */
    if((NAS_ERABM_IPF_DIRECTION_DL == enDir)&&(!NAS_ERABM_IPF_IS_DL_FILTER_FULL()))
    {
        return NAS_ERABM_IPF_GET_DL_FILTER_PTR(NAS_ERABM_IPF_GET_DL_FILTER_NUM());
    }

    NAS_ERABM_ERR_LOG("NAS_ERABM_IpfGetFreeFilter, Filter Queue Full.");
    TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfGetFreeFilter_ENUM, LNAS_ERABM_FilterQueueFull);

    /* 增加统计信息 */
    NAS_ERABM_IPF_OM_ADD_FILTER_FULL_CNT();

    return VOS_NULL_PTR;
}
/*lint +e960*/

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfCompare
 功能描述  : IPF中 Filter按优先级排序功能
 输入参数  : const VOS_VOID *arg1
             const VOS_VOID *arg2
 输出参数  : 无
 返 回 值  : VOS_INT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_INT32 NAS_ERABM_IpfCompare(const VOS_VOID *arg1, const VOS_VOID *arg2)
{
    VOS_UINT16              usVar1;
    VOS_UINT16              usVar2;
    IPF_FILTER_CONFIG_S*    pstPara1;
    IPF_FILTER_CONFIG_S*    pstPara2;

    pstPara1 = (IPF_FILTER_CONFIG_S*) arg1;
    pstPara2 = (IPF_FILTER_CONFIG_S*) arg2;

    usVar1 = pstPara1->stMatchInfo.unFltChain.Bits.u16FltPri;
    usVar2 = pstPara2->stMatchInfo.unFltChain.Bits.u16FltPri;

    /* IP Filter的优先级从小到大排序 */
    if(usVar1 > usVar2)
    {
        return 1;
    }
    else if(usVar1 < usVar2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfGenerateBaseIpv4Filter
 功能描述  : 产生IPv4类型的基本参数的Filter
 输入参数  : const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
             VOS_UINT8 ucEpsbId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_IpfGenerateBaseIpv4Filter
(
    const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
    VOS_UINT8 ucEpsbId
)
{
    VOS_UINT32                      i           = 0;
    IPF_FILTER_CONFIG_S            *pstFilter   = VOS_NULL_PTR;

    /* 从Filter队列中找到下一个空闲的Filter */
    pstFilter = NAS_ERABM_IpfGetFreeFilter(NAS_ERABM_IPF_DIRECTION_UL);
    if(VOS_NULL_PTR == pstFilter)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IPF Get Free Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfGenerateBaseIpv4Filter_ENUM, LNAS_EMM_GET_FILTER_FAIL);
        return PS_FAIL;
    }

    NAS_ERABM_MEM_SET_S(pstFilter,sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));

    /* 填写IP Filter参数 */
    pstFilter->stMatchInfo.unFltRuleCtrl.Bits.FltType = NAS_ERABM_IPF_IPTYPE_IPV4;
    pstFilter->stMatchInfo.unFltRuleCtrl.Bits.FltLAddrEn = NAS_ERABM_OP_TRUE;

    for(i = 0; i < APP_MAX_IPV4_ADDR_LEN; i++)
    {
        pstFilter->stMatchInfo.u8SrcAddr[i] = pstPdnAddr->aucIpV4Addr[i];
        /*pstFilter->stMatchInfo.u8SrcMsk[i] = 0xFF;*/
    }
    /*lint -e40*/
    /*lint -e63*/
    pstFilter->stMatchInfo.u32LocalAddressMsk = 0;
    /*lint +e63*/
    /*lint +e40*/

    /* Precedence = 256 */
    pstFilter->stMatchInfo.unFltRuleCtrl.Bits.FltBid = ucEpsbId;
    pstFilter->stMatchInfo.unFltRuleCtrl.Bits.FltEn  = NAS_ERABM_OP_TRUE;
    pstFilter->stMatchInfo.unFltChain.Bits.u16FltPri = NAS_ERABM_IPF_LOWEST_PRI;

    /* Bearer Id */
    pstFilter->u32FilterID = NAS_ERABM_IPF_UL_IPV4_FILTER_ID(ucEpsbId, 0);

    /* 增加上行Filter数目 */
    NAS_ERABM_IPF_ADD_UL_FILTER_NUM();

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfGenerateBaseIpv6Filter
 功能描述  : 产生IPv6格式的基本参数的Filter
 输入参数  : const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
             VOS_UINT8 ucEpsbId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_IpfGenerateBaseIpv6Filter
(
    const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
    VOS_UINT8 ucEpsbId
)
{
    VOS_UINT32                      i           = 0;
    IPF_FILTER_CONFIG_S            *pstFilter   = VOS_NULL_PTR;
    VOS_UINT8                       aucInvalidIpv6Prefix[NAS_ERABM_IPV6_PREFIX_LEN] = {0};

    /* 检查IPv6前缀是否有效，如果无效，则不配置IPF，直接返回 */
    if(0 == NAS_ERABM_MEM_CMP(  pstPdnAddr->aucIpV6Addr,
                                aucInvalidIpv6Prefix,
                                NAS_ERABM_IPV6_PREFIX_LEN))
    {
        NAS_ERABM_NORM_LOG("NAS_ERABM_IpfGenerateBaseIpv6Filter IPv6 prefix invalid.");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_IpfGenerateBaseIpv6Filter_ENUM, LNAS_ERABM_IPv6PrefixInvalid);
        return PS_SUCC;
    }
    /* 从Filter队列中找到下一个空闲的Filter */
    pstFilter = NAS_ERABM_IpfGetFreeFilter(NAS_ERABM_IPF_DIRECTION_UL);
    if(VOS_NULL_PTR == pstFilter)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IpfGenerateBaseIpv6Filter Get Free Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfGenerateBaseIpv6Filter_ENUM, LNAS_EMM_GET_FILTER_FAIL);
        return PS_FAIL;
    }

    NAS_ERABM_MEM_SET_S(pstFilter, sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));

    /* 填写IP Filter参数 */
    pstFilter->stMatchInfo.unFltRuleCtrl.Bits.FltType = NAS_ERABM_IPF_IPTYPE_IPV6;
    pstFilter->stMatchInfo.unFltRuleCtrl.Bits.FltLAddrEn = NAS_ERABM_OP_TRUE;

    /* IPv6只过滤64bit前缀 */
    for(i = 0; i < (APP_MAX_IPV6_ADDR_LEN/2); i++)
    {
        /*lint -e40*/
        /*lint -e63*/
        pstFilter->stMatchInfo.u8SrcAddr[i] = pstPdnAddr->aucIpV6Addr[i];
        /*lint +e63*/
        /*lint +e40*/
      /* pstFilter->stMatchInfo.u8SrcMsk[i] = 0xFF; */
    }
    /*lint -e40*/
    /*lint -e63*/
    pstFilter->stMatchInfo.u32LocalAddressMsk = 64;
    /*lint +e63*/
    /*lint +e40*/

    /* Precedence = 256 */
    pstFilter->stMatchInfo.unFltRuleCtrl.Bits.FltBid = ucEpsbId;
    pstFilter->stMatchInfo.unFltRuleCtrl.Bits.FltEn = NAS_ERABM_OP_TRUE;
    pstFilter->stMatchInfo.unFltChain.Bits.u16FltPri = NAS_ERABM_IPF_LOWEST_PRI;

    /* Bearer Id */
    pstFilter->u32FilterID = NAS_ERABM_IPF_UL_IPV6_FILTER_ID(ucEpsbId,0);

    /* 增加上行Filter数目 */
    NAS_ERABM_IPF_ADD_UL_FILTER_NUM();

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfGenerateFilterWithoutTFT
 功能描述  : 产生不携带TFT参数的承载的FILTER信息
 输入参数  : APP_ESM_IP_ADDR_STRU *pstPdnAddr
              VOS_UINT8 ucEpsbId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_IpfGenerateFilterWithoutTFT
(
    const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
    VOS_UINT8 ucEpsbId
)
{
    /* check ip type: ipv4, ipv4v6 */
    if((APP_ESM_PDN_TYPE_IPV4 == pstPdnAddr->ucIpType)||
       (APP_ESM_PDN_TYPE_IPV4_IPV6 == pstPdnAddr->ucIpType))
    {
        if(PS_FAIL == NAS_ERABM_IpfGenerateBaseIpv4Filter(pstPdnAddr, ucEpsbId))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_IpfGenerateFilterWithoutTFT: Generate Ipv4 Filter Fail.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfGenerateFilterWithoutTFT_ENUM, LNAS_EMM_IPV4_FAIL);
            return PS_FAIL;
        }
    }

    /* check ip type: ipv6, ipv4v6 */
    if((APP_ESM_PDN_TYPE_IPV6 == pstPdnAddr->ucIpType)||
       (APP_ESM_PDN_TYPE_IPV4_IPV6 == pstPdnAddr->ucIpType))
    {
        if(PS_FAIL ==  NAS_ERABM_IpfGenerateBaseIpv6Filter(pstPdnAddr, ucEpsbId))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_IpfGenerateFilterWithoutTFT: Generate Ipv6 Filter Fail.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfGenerateFilterWithoutTFT_ENUM, LNAS_EMM_IPV6_FAIL);
            return PS_FAIL;
        }
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfConvertOtherPartToFilter
 功能描述  : 将 TFT参数中除源地址/目的地址/FlowLabel 等与V4V6相关参数之外的
             数据转换为IP Filter格式
 输入参数  : const ESM_ERABM_TFT_PF_STRU *pstTftPf,
             IPF_MATCH_INFO_S     *pstIpFilter
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_ERABM_IpfConvertOtherPartToFilter
(
    const ESM_ERABM_TFT_PF_STRU *pstTftPf,
    IPF_MATCH_INFO_S     *pstIpFilter
)
{
    /* Protocol id */
    if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpProtocolId)
    {
        pstIpFilter->unNextHeader.u32Protocol = pstTftPf->ucProtocolId;

        pstIpFilter->unFltRuleCtrl.Bits.FltNhEn = NAS_ERABM_OP_TRUE;
    }

    /* local port */
    if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpSingleLocalPort)
    {
        pstIpFilter->unSrcPort.Bits.u16SrcPortLo = pstTftPf->usSingleLcPort;
        pstIpFilter->unSrcPort.Bits.u16SrcPortHi = pstTftPf->usSingleLcPort;

        pstIpFilter->unFltRuleCtrl.Bits.FltLPortEn = NAS_ERABM_OP_TRUE;
    }

    /* local port range, low to high */
    if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpLocalPortRange)
    {
        pstIpFilter->unSrcPort.Bits.u16SrcPortLo = pstTftPf->usLcPortLowLimit;
        pstIpFilter->unSrcPort.Bits.u16SrcPortHi = pstTftPf->usLcPortHighLimit;

        pstIpFilter->unFltRuleCtrl.Bits.FltLPortEn = NAS_ERABM_OP_TRUE;
    }

    /* remote port */
    if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpSingleRemotePort)
    {
        pstIpFilter->unDstPort.Bits.u16DstPortLo = pstTftPf->usSingleRmtPort;
        pstIpFilter->unDstPort.Bits.u16DstPortHi = pstTftPf->usSingleRmtPort;

        pstIpFilter->unFltRuleCtrl.Bits.FltRPortEn = NAS_ERABM_OP_TRUE;
    }

    /* remote port range , low to high */
    if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpRemotePortRange)
    {
        pstIpFilter->unDstPort.Bits.u16DstPortLo = pstTftPf->usRmtPortLowLimit;
        pstIpFilter->unDstPort.Bits.u16DstPortHi = pstTftPf->usRmtPortHighLimit;

        pstIpFilter->unFltRuleCtrl.Bits.FltRPortEn = NAS_ERABM_OP_TRUE;
    }

    /* type of server and mask for ipv4, traffic class and mask for ipv6*/
    if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpTypeOfService)
    {
      /*pstIpFilter->unTrafficClass.u32ServiceType = pstTftPf->ucTypeOfService;
        pstIpFilter->unTrafficClassMsk.u32ServiceTypeMsk = pstTftPf->ucTypeOfServiceMask;*/
        /*lint -e40*/
        /*lint -e10*/
        /*lint -e63*/
        pstIpFilter->unTrafficClass.Bits.u8TrafficClass     = pstTftPf->ucTypeOfService;
        pstIpFilter->unTrafficClass.Bits.u8TrafficClassMask = pstTftPf->ucTypeOfServiceMask;
        /*lint +e63*/
        /*lint +e10*/
        /*lint +e40*/
        pstIpFilter->unFltRuleCtrl.Bits.FltTosEn = NAS_ERABM_OP_TRUE;
    }

    /* spi for esp or ah ? */
    if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpSecuParaIndex)
    {
        pstIpFilter->u32FltSpi = pstTftPf->ulSecuParaIndex;

        pstIpFilter->unFltRuleCtrl.Bits.FltSpiEn = NAS_ERABM_OP_TRUE;
    }

    return;
}
/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfCalcMaskLength
 功能描述  : 计算掩码的长度
 输入参数  : const ESM_ERABM_TFT_PF_STRU *pstTftPf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_ERABM_IpfCalcIpv4MaskLength
(
    const ESM_ERABM_TFT_PF_STRU *pstTftPf,
    IPF_MATCH_INFO_S           *pstFilter
)
{
    VOS_UINT32                           i = 0;
    VOS_UINT32                           j = 0;
    VOS_UINT32                           ucNumOne = 1;
    VOS_UINT32                           ucNumSev = 7;

    NAS_ERABM_NORM_LOG("NAS_ERABM_IpfCalcIpv4MaskLength enter");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_IpfCalcIpv4MaskLength_ENUM, LNAS_ENTRY);


    for(i = 0;i < APP_MAX_IPV4_ADDR_LEN; i++)
    {
        if (0xFF == pstTftPf->aucLocalIpv4Mask[i])
        {
            pstFilter->u32LocalAddressMsk = pstFilter->u32LocalAddressMsk + 8;
        }
        else
        {
            for (j = 0; j < 8; j++)
            {
                if (0 != ((VOS_UINT32)pstTftPf->aucLocalIpv4Mask[i] & (ucNumOne << (ucNumSev - j))))
                {
                    pstFilter->u32LocalAddressMsk ++;
                }
                else
                {
                    break;
                }
            }
            break;
        }
    }

    return;
}
/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfConvertIpv4TftToFilter
 功能描述  : 将IPv4格式TFT转换为IP filter格式
 输入参数  : const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
             const ESM_ERABM_TFT_PF_STRU *pstTftPf,
             VOS_UINT8            ucEpsbId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_IpfConvertIpv4TftToFilter
(
    const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
    const ESM_ERABM_TFT_PF_STRU *pstTftPf,
    VOS_UINT8            ucEpsbId
)
{
    VOS_UINT32                  i               = 0;
    IPF_FILTER_CONFIG_S        *pstIpFilter     = VOS_NULL_PTR;
    IPF_MATCH_INFO_S           *pstFilter       = VOS_NULL_PTR;

    /* 从Filter队列中找到下一个空闲的Filter */
    pstIpFilter = NAS_ERABM_IpfGetFreeFilter(NAS_ERABM_IPF_DIRECTION_UL);

    if(VOS_NULL_PTR == pstIpFilter)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IPF Get Free Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfConvertIpv4TftToFilter_ENUM, LNAS_EMM_GET_FILTER_FAIL);
        return PS_FAIL;
    }

    NAS_ERABM_MEM_SET_S(pstIpFilter,sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));

    pstFilter = &pstIpFilter->stMatchInfo;

    /* source address and mask for ipv4 */
    if ((ERABM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
        && (NAS_ESM_FUN_CTRL_ON == NAS_ESM_GetLocalIpSupFlag()))
    {
        NAS_ERABM_NORM_LOG("NAS_ERABM_IpfConvertIpv4TftToFilter  r11 enter");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_IpfConvertIpv4TftToFilter_ENUM, LNAS_ERABM_R11);
        for(i = 0;i < APP_MAX_IPV4_ADDR_LEN; i++)
        {
            pstFilter->u8SrcAddr[i] = pstTftPf->aucLocalIpv4Addr[i];
            /* pstFilter->u8SrcMsk[i]  = 0xFF; */
        }
        /* 计算掩码的长度 */
        /* 底软的只需要掩码的长度，u32LocalAddressMsk代表低多少位为0 */
        NAS_ERABM_IpfCalcIpv4MaskLength(pstTftPf,pstFilter);
    }
    else
    {
        for(i = 0;i < APP_MAX_IPV4_ADDR_LEN; i++)
        {
            pstFilter->u8SrcAddr[i] = pstPdnAddr->aucIpV4Addr[i];
            /* pstFilter->u8SrcMsk[i]  = 0xFF; */
        }
        /*lint -e40*/
        /*lint -e63*/
        pstFilter->u32LocalAddressMsk = 0;

    }

    /*lint -e40*/
    /*lint -e63*/
    pstFilter->unFltRuleCtrl.Bits.FltLAddrEn = NAS_ERABM_OP_TRUE;
    /*lint +e63*/
    /*lint +e40*/

    /* destination address and mask for ipv4 */
    if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpRmtIpv4AddrAndMask)
    {
        for(i = 0;i < APP_MAX_IPV4_ADDR_LEN; i++)
        {
            pstFilter->u8DstAddr[i] = pstTftPf->aucRmtIpv4Address[i];
            pstFilter->u8DstMsk[i] = pstTftPf->aucRmtIpv4Mask[i];
        }
        pstFilter->unFltRuleCtrl.Bits.FltRAddrEn = NAS_ERABM_OP_TRUE;
    }

    pstFilter->unFltRuleCtrl.Bits.FltType = NAS_ERABM_IPF_IPTYPE_IPV4;

    /* 将TFT参数中的其余部分转换为IP Filter格式 */
    NAS_ERABM_IpfConvertOtherPartToFilter(pstTftPf, &pstIpFilter->stMatchInfo);

    /* Filter ID */
    pstIpFilter->u32FilterID =
        NAS_ERABM_IPF_UL_IPV4_FILTER_ID(ucEpsbId, pstTftPf->ucNwPacketFilterId);
    /* Filter Precedence and Bearer Id */
    pstFilter->unFltChain.Bits.u16FltPri = pstTftPf->ucPrecedence;
    pstFilter->unFltRuleCtrl.Bits.FltBid = ucEpsbId;
    pstFilter->unFltRuleCtrl.Bits.FltEn = NAS_ERABM_OP_TRUE;

    /* 增加上行Filter数目 */
    NAS_ERABM_IPF_ADD_UL_FILTER_NUM();

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfConvertIpv6TftToFilter
 功能描述  : 将IPv6格式TFT转换为IP Filter格式
 输入参数  : const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
             const ESM_ERABM_TFT_PF_STRU *pstTftPf,
             VOS_UINT8            ucEpsbId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_IpfConvertIpv6TftToFilter
(
    const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
    const ESM_ERABM_TFT_PF_STRU *pstTftPf,
    VOS_UINT8            ucEpsbId
)
{
    VOS_UINT32                  i               = 0;
    IPF_FILTER_CONFIG_S        *pstIpFilter     = VOS_NULL_PTR;
    IPF_MATCH_INFO_S           *pstFilter       = VOS_NULL_PTR;

    /* 从Filter队列中找到下一个空闲的Filter */
    pstIpFilter = NAS_ERABM_IpfGetFreeFilter(NAS_ERABM_IPF_DIRECTION_UL);

    if(VOS_NULL_PTR == pstIpFilter)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IPF Get Free Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfConvertIpv6TftToFilter_ENUM, LNAS_EMM_GET_FILTER_FAIL);
        return PS_FAIL;
    }

    NAS_ERABM_MEM_SET_S(pstIpFilter,sizeof(IPF_FILTER_CONFIG_S), 0x0, sizeof(IPF_FILTER_CONFIG_S));

    pstFilter = &pstIpFilter->stMatchInfo;

    /* source address and mask for ipv6 */
    /* IPv6只过滤64bit前缀 */
    if ((ERABM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
        && (NAS_ESM_FUN_CTRL_ON == NAS_ESM_GetLocalIpSupFlag()))
    {
        NAS_ERABM_NORM_LOG("NAS_ERABM_IpfConvertIpv6TftToFilter  r11 enter");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_IpfConvertIpv6TftToFilter_ENUM, LNAS_ERABM_R11);
        for(i = 0;i < (APP_MAX_IPV6_ADDR_LEN/2); i++)
        {
            pstFilter->u8SrcAddr[i] = pstTftPf->aucLocalIpv6Addr[i];
            /* pstFilter->u8SrcMsk[i]  = 0xFF; */
        }
        /* 掩码的长度和IPV6地址前缀的长度相同 */
        pstFilter->u32LocalAddressMsk = pstTftPf->ucLocalIpv6Prefix;
    }
    else
    {
        for(i = 0;i < (APP_MAX_IPV6_ADDR_LEN/2); i++)
        {
            pstFilter->u8SrcAddr[i] = pstPdnAddr->aucIpV6Addr[i];
            /* pstFilter->u8SrcMsk[i]  = 0xFF; */
        }
        /*lint -e40*/
        /*lint -e63*/
        pstFilter->u32LocalAddressMsk = 64;
        /*lint +e63*/
        /*lint +e40*/
    }

    pstFilter->unFltRuleCtrl.Bits.FltLAddrEn = NAS_ERABM_OP_TRUE;

    /* destination address and mask for ipv6 */
    if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpRmtIpv6AddrAndMask)
    {
        for(i = 0;i < APP_MAX_IPV6_ADDR_LEN; i++)
        {
            pstFilter->u8DstAddr[i] = pstTftPf->aucRmtIpv6Address[i];
            pstFilter->u8DstMsk[i] = pstTftPf->aucRmtIpv6Mask[i];
        }
        pstFilter->unFltRuleCtrl.Bits.FltRAddrEn = NAS_ERABM_OP_TRUE;
    }

    /* flowlabel for ipv6 */
    if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpFlowLabelType)
    {
        pstFilter->u32FlowLable = pstTftPf->ulFlowLabelType;
        pstFilter->unFltRuleCtrl.Bits.FltFlEn = NAS_ERABM_OP_TRUE;
    }
    pstFilter->unFltRuleCtrl.Bits.FltType = NAS_ERABM_IPF_IPTYPE_IPV6;

    /* 将TFT参数中的其余部分转换为IP Filter格式 */
    NAS_ERABM_IpfConvertOtherPartToFilter(pstTftPf, &pstIpFilter->stMatchInfo);

    /* Filter ID */
    pstIpFilter->u32FilterID =
        NAS_ERABM_IPF_UL_IPV6_FILTER_ID(ucEpsbId, pstTftPf->ucNwPacketFilterId);
    /* Filter Precedence and Bearer Id */
    pstFilter->unFltChain.Bits.u16FltPri = pstTftPf->ucPrecedence;
    pstFilter->unFltRuleCtrl.Bits.FltBid = ucEpsbId;
    pstFilter->unFltRuleCtrl.Bits.FltEn = NAS_ERABM_OP_TRUE;

    /* 增加上行Filter数目 */
    NAS_ERABM_IPF_ADD_UL_FILTER_NUM();

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfCheckFilterType
 功能描述  : 检查上行TFT的类型, 可以是IPv4,可以是IPv6, 如果无法区分, 则需要
             将TFT分为IPv4和IPv6两个
 输入参数  : ESM_ERABM_TFT_PF_STRU *pstTftPf
             VOS_UINT8 ucIpType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_IpfCheckFilterType
(
    const ESM_ERABM_TFT_PF_STRU *pstTftPf,
    VOS_UINT8 ucIpType
)
{
    if(APP_ESM_PDN_TYPE_IPV4 == ucIpType) /*PDN类型为IPV4*/
    {
        return NAS_ERABM_IPF_IPTYPE_IPV4;
    }
    else if(APP_ESM_PDN_TYPE_IPV6 == ucIpType) /*PDN类型为IPV6*/
    {
        return NAS_ERABM_IPF_IPTYPE_IPV6;
    }
    else if(APP_ESM_PDN_TYPE_IPV4_IPV6 == ucIpType)   /* PDN类型为IPV4V6*/
    {
        /* 如果PDN连接是IPv4v6类型，需要看TFT参数中是否有能够体现IP类型的内
          容，如目的地址类型或IPv6 FlowLabel，如果没有，则需要产生Ipv4和IPv6
          两个Filter */
        if((NAS_ERABM_OP_TRUE == pstTftPf->bitOpRmtIpv6AddrAndMask)
           ||(NAS_ERABM_OP_TRUE == pstTftPf->bitOpFlowLabelType))
        {
            return NAS_ERABM_IPF_IPTYPE_IPV6;
        }
        else if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpRmtIpv4AddrAndMask)
        {
            return NAS_ERABM_IPF_IPTYPE_IPV4;
        }
        else
        {
            return NAS_ERABM_IPF_IPTYPE_IPV4V6;
        }
    }
    else
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IpfCheckFilterType: Wrong IP Type.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfCheckFilterType_ENUM, LNAS_ERABM_WrongIPType);
        return NAS_ERABM_IPF_IPTYPE_INVALID;
    }
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfConvertTftToFilter
 功能描述  : 将指定上行TFT参数转换为IP Filter格式
 输入参数  : const APP_ESM_IP_ADDR_STRU   *pstPdnAddr,
             const ESM_ERABM_TFT_PF_STRU   *pstTftPf,
             VOS_UINT8                     ucEpsbId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_IpfConvertTftToFilter
(
    const APP_ESM_IP_ADDR_STRU   *pstPdnAddr,
    const ESM_ERABM_TFT_PF_STRU   *pstTftPf,
    VOS_UINT8                     ucEpsbId
)
{
    VOS_UINT32                  ulFilterType    = NAS_ERABM_IPF_IPTYPE_IPV4;

    /* 需要首先检查TFT对应的IP类型 */
    ulFilterType = NAS_ERABM_IpfCheckFilterType(pstTftPf, pstPdnAddr->ucIpType);
    if(NAS_ERABM_IPF_IPTYPE_INVALID == ulFilterType)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IpfConvertTftToFilter: IPtype invalid.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfConvertTftToFilter_ENUM, LNAS_ERABM_IPFConvertIptypeInvalid);
    }
    /* 首先根据不同类型生成IP Filter */
    if((NAS_ERABM_IPF_IPTYPE_IPV4 == ulFilterType)||
       (NAS_ERABM_IPF_IPTYPE_IPV4V6 == ulFilterType))
    {
        if(PS_FAIL == NAS_ERABM_IpfConvertIpv4TftToFilter(pstPdnAddr, pstTftPf, ucEpsbId))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_IpfConvertTftToFilter: Convert Ipv4 Filter Fail.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfConvertTftToFilter_ENUM, LNAS_ERABM_ConvertIpv4FilterFail);
            return PS_FAIL;
        }
    }

    if((NAS_ERABM_IPF_IPTYPE_IPV6 == ulFilterType)||
       (NAS_ERABM_IPF_IPTYPE_IPV4V6 == ulFilterType))
    {
        if(PS_FAIL == NAS_ERABM_IpfConvertIpv6TftToFilter(pstPdnAddr, pstTftPf, ucEpsbId))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_IpfConvertTftToFilter: Convert Ipv6 Filter Fail.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfConvertTftToFilter_ENUM, LNAS_ERABM_ConvertIpv6FilterFail);
            return PS_FAIL;
        }
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfGenerateFilterWithTFT
 功能描述  : 遍历承载的所有TFT参数，并转换为IP Filter
 输入参数  : const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
             VOS_UINT8 ucEpsbId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_IpfGenerateFilterWithTFT
(
    const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
    VOS_UINT8 ucEpsbId
)
{
    VOS_UINT32                      ulTftPfCnt      = NAS_ERABM_NULL;
    ESM_ERABM_TFT_PF_STRU           *pstTftInfo      = VOS_NULL_PTR;

    for(ulTftPfCnt = 0; ulTftPfCnt < NAS_ERABM_GetEpsbTftPfNum(ucEpsbId); ulTftPfCnt++)
    {
        pstTftInfo = NAS_ERABM_GetEpsbTftAddr(ucEpsbId, ulTftPfCnt);

        /* 不需要处理下行TFT参数 */
        if (APP_ESM_TRANSFER_DIRECTION_DOWNLINK == pstTftInfo->enDirection)
        {
            continue;
        }

        /* 将TFT参数转换为IP Filter格式 */
        if(PS_FAIL == NAS_ERABM_IpfConvertTftToFilter(pstPdnAddr, pstTftInfo, ucEpsbId))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_IPF Convert TFT to IPF Filter Failed.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfGenerateFilterWithTFT_ENUM, LNAS_EMM_TFT_TO_IPF_FAIL);
            return PS_FAIL;
        }
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfGenerateUlNidsFilters
 功能描述  : 将所有UL NDIS所需数据包的FILTER配置到上行FILTER队列中
 输入参数  : VOS_UINT32 ulFilterId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月05日
    作    者   : L00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_IpfGenerateUlNidsFilters()
{
    VOS_UINT32                  i               = 0;

    /* 将所有UL NDIS所需数据包的FILTER配置到上行FILTER队列中 */
    for (i=0; i<NAS_ERABM_IPF_CUR_UL_NDIS_FILTER_NUM; i++)
    {
        if (PS_FAIL == NAS_ERABM_IpfAddUlNdisFilter(i))
        {
            NAS_ERABM_LOG1("NAS_ERABM_IpfGenerateUlNidsFilters:NAS_ERABM_IpfAddUlNdisFilter Failed.",i);
            TLPS_PRINT2LAYER_INFO1(NAS_ERABM_IpfGenerateUlNidsFilters_ENUM, LNAS_FAIL, i);
            return PS_FAIL;
        }
    }

    return PS_SUCC;
}
/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfGenerateFilters
 功能描述  : 遍历所有承载，生成IP FIlter参数
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_IpfGenerateFilters()
{
    VOS_UINT8                       ucEpsbId        = NAS_ERABM_NULL;
    APP_ESM_IP_ADDR_STRU           *pstPdnAddr      = VOS_NULL_PTR;

    /* 清空当前所有Filter */
    NAS_ERABM_IPF_SET_UL_FILTER_NUM(0);

    /* 当上行NDIS FILTER有效时，将所有UL NDIS所需数据包的FILTER配置到上行
       FILTER队列中 */
    if (NAS_ERABM_UL_NDIS_FILTER_VALID == NAS_ERABM_IPF_GET_UL_NDIS_FILTER_FLAG())
    {
        if (PS_SUCC != NAS_ERABM_IpfGenerateUlNidsFilters())
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_IpfGenerateFilters:NAS_ERABM_IpfGenerateUlNidsFilters Failed.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfGenerateFilters_ENUM, LNAS_FAIL);
            return PS_FAIL;
        }
    }

    for(ucEpsbId = NAS_ERABM_MIN_EPSB_ID; ucEpsbId <= NAS_ERABM_MAX_EPSB_ID; ucEpsbId++)
    {
        if (NAS_ERABM_EPSB_ACTIVE != NAS_ERABM_GetEpsbStateInfo(ucEpsbId))
        {
            /* 承载未激活，返回 */
            continue;
        }

        /* 查找PDN连接地址 */
        pstPdnAddr = NAS_ERABM_GetEpsbPdnAddr(ucEpsbId);

        /* 先处理未配置TFT参数的默认承载 */
        if(PS_FALSE == NAS_ERABM_IsExistUplinkPfinTft(ucEpsbId))
        {
            if(PS_FAIL == NAS_ERABM_IpfGenerateFilterWithoutTFT(pstPdnAddr, ucEpsbId))
            {
                NAS_ERABM_ERR_LOG("NAS_ERABM_IPF Generate Default Bearer Filter Failed.");
                TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfGenerateFilters_ENUM, LNAS_FUNCTION_LABEL1);
                return PS_FAIL;
            }
        }
        else
        {
            /* 其它专有承载或配置了TFT参数的默认承载,需要根据TFT Filter进行转换 */
            if(PS_FAIL == NAS_ERABM_IpfGenerateFilterWithTFT(pstPdnAddr, ucEpsbId))
            {
                NAS_ERABM_ERR_LOG("NAS_ERABM_IPF Generate Dedicate Bearer Filter Failed.");
                TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfGenerateFilters_ENUM, LNAS_FUNCTION_LABEL2);
                return PS_FAIL;
            }
        }
    }

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 支持EHRPD的情况下，生成过滤器要将未恢复的EHRPD承载信息也全部生成配置给IPF */
    for(ucEpsbId = NAS_ERABM_MIN_EPSB_ID; ucEpsbId <= NAS_ERABM_MAX_EPSB_ID; ucEpsbId++)
    {
        if (NAS_ERABM_EPSB_ACTIVE != NAS_ERABM_GetEhrpdBearerStateInfo(ucEpsbId))
        {
            /* 承载未激活，继续 */
            continue;
        }

        NAS_ERABM_LOG1("NAS_ERABM_IPF Generate Default Bearer Filter: EHRPD Bearer active, ID =", ucEpsbId);
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_IpfGenerateFilters_ENUM, LNAS_ERABM_EhrpdBearerId, ucEpsbId);

        /* 查找PDN连接地址 */
        pstPdnAddr = NAS_ERABM_GetEhrpdPdnAddr(ucEpsbId);

        /* 当前的实现，不支持CL的专有承载互操作，因此激活的只能是缺省承载 */
        if(PS_FAIL == NAS_ERABM_IpfGenerateFilterWithoutTFT(pstPdnAddr, ucEpsbId))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_IPF Generate EHRPD Default Bearer Filter Failed.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfGenerateFilters_ENUM, LNAS_FUNCTION_LABEL3);
            return PS_FAIL;
        }
    }

    #endif

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfFilterSort
 功能描述  : IP Filter 优先级比较函数
 输入参数  : IPF_FILTER_CONFIG_S *pstFilter
             VOS_UINT32 ulNum
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_ERABM_IpfFilterSort(IPF_FILTER_CONFIG_S *pstFilter, VOS_UINT32 ulNum)
{
    /* 调用C语言的库函数qsort对pstFilter进行快速排序 */
    /*lint -e586*/
    qsort(pstFilter, ulNum, sizeof(IPF_FILTER_CONFIG_S), (NAS_IPF_COMP_FUNC)NAS_ERABM_IpfCompare);
    /*lint +e586*/
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfConfigUlFilter
 功能描述  : 便利所有上行TFT, 生成IP Filter, 并配置到硬件加速器
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_IpfConfigUlFilter()
{
    VOS_UINT32                      ulIpFilterNum   = 0;
    IPF_FILTER_CONFIG_S            *pstFilterList   = 0;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_IpfConfigFilter is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_IpfConfigUlFilter_ENUM, LNAS_ENTRY);

    /* 遍历所有TFT，生成IP Filter */
    if(PS_FAIL == NAS_ERABM_IpfGenerateFilters())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IpfConfigFilter: Generate All Filters Fail.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfConfigUlFilter_ENUM, LNAS_FUNCTION_LABEL1);

        /* 增加统计信息 */
        NAS_ERABM_IPF_OM_ADD_UL_FILTER_ERR_CNT();
        return PS_FAIL;
    }

    /* 调用qsort对所有Filter进行排序 */
    ulIpFilterNum = NAS_ERABM_IPF_GET_UL_FILTER_NUM();
    pstFilterList = NAS_ERABM_IPF_GET_UL_FILTER_PTR(0);

    NAS_ERABM_IpfFilterSort(pstFilterList, ulIpFilterNum);

    /* 调用驱动接口， 将Filter列表 配置到硬件加速器中 */
    /*lint -e64*/
    if(PS_SUCC != LDRV_IPF_SET_FILTER(IPF_MODEM0_ULFC, (IPF_FILTER_CONFIG_S*)pstFilterList, ulIpFilterNum))
    /*lint +e64*/
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IpfConfigFilter: BSP Config All Filters Fail.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfConfigUlFilter_ENUM, LNAS_FUNCTION_LABEL2);
        return PS_FAIL;
    }
    NAS_ERABM_SndOmLogIpfUlFilterInfo(pstFilterList, ulIpFilterNum);

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_GetSrcIpv4MatchedDeftBearerId
 功能描述  : 遍历所有缺省承载，查找源IPv4地址匹配的承载号
 输入参数  : VOS_UINT8 *pstDataAddr
 输出参数  : VOS_UINT8 *pucBearerId
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月21日
    作    者   : L00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_ERABM_GetSrcIpv4MatchedDeftBearerId
(
    const NAS_ERABM_IPV4_HEADER_STRU   *pstIpv4HeaderInfo,
    VOS_UINT8                          *pucBearerId
)
{
    VOS_UINT32                          ulEpsbId    = NAS_ERABM_NULL;
    APP_ESM_IP_ADDR_STRU               *pstPdnAddr  = VOS_NULL_PTR;

    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId<= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        if (NAS_ERABM_EPSB_ACTIVE != NAS_ERABM_GetEpsbStateInfo(ulEpsbId))
        {
            continue;
        }

        if (ESM_ERABM_BEARER_TYPE_DEDICATED == NAS_ERABM_GetEpsbBearerType(ulEpsbId))
        {
            continue;
        }

        pstPdnAddr = NAS_ERABM_GetEpsbPdnAddr(ulEpsbId);

        if ((NAS_ERABM_PDN_IPV6 == pstPdnAddr->ucIpType))
        {
            continue;
        }

        /* 匹配源IPv4地址 */
        if (0 == NAS_ERABM_MEM_CMP( pstPdnAddr->aucIpV4Addr,
                                    pstIpv4HeaderInfo->aucSrcIpV4Addr,
                                    NAS_ERABM_IPV4_ADDR_LEN))
        {
            *pucBearerId = (VOS_UINT8)ulEpsbId;
            return NAS_ERABM_SUCCESS;
        }
    }

    /* 增加丢弃IPV4分片包统计信息 */
    NAS_ERABM_IPF_OM_ADD_RCV_UL_DISCARD_IPV4_PACK_NUM();

    *pucBearerId = NAS_ERABM_IPF_INVALID_BEARER_ID;
    return NAS_ERABM_FAILURE;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_GetSrcIpv6MatchedDeftBearerId
 功能描述  : 遍历所有缺省承载，查找源IPv6地址前缀匹配的承载号
 输入参数  : VOS_UINT8 *pstIpv6HeaderInfo
 输出参数  : VOS_UINT8 *pucBearerId
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月21日
    作    者   : L00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_ERABM_GetSrcIpv6MatchedDeftBearerId
(
    const NAS_ERABM_IPV6_HEADER_STRU   *pstIpv6HeaderInfo,
    VOS_UINT8                          *pucBearerId
)
{
    VOS_UINT32                          ulEpsbId    = NAS_ERABM_NULL;
    APP_ESM_IP_ADDR_STRU               *pstPdnAddr  = VOS_NULL_PTR;

    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId<= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        if (NAS_ERABM_EPSB_ACTIVE != NAS_ERABM_GetEpsbStateInfo(ulEpsbId))
        {
            continue;
        }

        pstPdnAddr = NAS_ERABM_GetEpsbPdnAddr(ulEpsbId);
        if ((NAS_ERABM_PDN_IPV4 == pstPdnAddr->ucIpType))
        {
            continue;
        }

        if (ESM_ERABM_BEARER_TYPE_DEDICATED == NAS_ERABM_GetEpsbBearerType(ulEpsbId))
        {
            continue;
        }

        /* 匹配源IPv6前缀 */
        if (0 == NAS_ERABM_MEM_CMP( pstPdnAddr->aucIpV6Addr,
                                    pstIpv6HeaderInfo->aucSrcIpV6Addr,
                                    NAS_ERABM_IPV6_PREFIX_LEN))
        {
            *pucBearerId = (VOS_UINT8)ulEpsbId;
            return NAS_ERABM_SUCCESS;
        }
    }

    /* 增加丢弃IPV6分片包的统计信息 */
    NAS_ERABM_IPF_OM_ADD_RCV_UL_DISCARD_IPV6_PACK_NUM();

    *pucBearerId = NAS_ERABM_IPF_INVALID_BEARER_ID;

    return NAS_ERABM_FAILURE;
}


/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfIpv4HeadFragmentProcess
 功能描述  : IPV4头部分片处理功能
 输入参数  : VOS_UINT8 *pstDataAddr
             VOS_UINT32 ulSegType
             VOS_UINT32 ulMatchId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月21日
    作    者   : L00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_ERABM_IpfIpv4HeadFragmentProcess
(
    const NAS_ERABM_IPV4_HEADER_STRU   *pucIpv4Data,
    VOS_UINT8                           ucBearerId,
    VOS_UINT8                           ucUpperLayerFlag
)
{
    VOS_UINT32                          ulRslt          = NAS_ERABM_NULL;
    VOS_UINT8                           ucBearerIdTmp   = NAS_ERABM_NULL;

    /* 判断是否包含上层头 */
    if (NAS_ERABM_NO_UPPERLAYER != ucUpperLayerFlag)
    {
        /* 存储源IP地址、目的IP地址，identifier以及匹配结果中的usBearedId */
        NAS_ERABM_SaveIpv4SegDataInfo(pucIpv4Data, ucBearerId);

        return ucBearerId;
    }

    /* 增加头部分片但匹配信息不完整IP分片包统计信息 */
    NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_HEADER_NO_UPLAYER_PACK_NUM();

    /* 遍历所有缺省承载，查找源IP地址匹配的承载 */
    ulRslt = NAS_ERABM_GetSrcIpv4MatchedDeftBearerId(pucIpv4Data, &ucBearerIdTmp);

    if (NAS_ERABM_SUCCESS == ulRslt)
    {
        return ucBearerIdTmp;
    }

    return NAS_ERABM_IPF_INVALID_BEARER_ID;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_FindBearerIdInIpv4SegBuff
 功能描述  : 根据identifier、源和目的IP地址，在IPV4分片包存储数组中查找承载号
 输入参数  : NAS_ERABM_IPV4_HEADER_STRU         *pstIpv4HeaderInfo
 输出参数  : VOS_UINT8                          *pucBearerIdTmp
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月21日
    作    者   : L00150010
    修改内容   : 新生成函数

*****************************************************************************/
    VOS_UINT8 NAS_ERABM_FindBearerIdInIpv4SegBuff
    (
        const NAS_ERABM_IPV4_HEADER_STRU   *pstIpv4HeaderInfo,
        VOS_UINT8                          *pucBearerIdTmp
    )
    {
        VOS_UINT32                          ulLoop           = NAS_ERABM_NULL;
        NAS_ERABM_IPV4_SEG_BUFF_ITEM_STRU  *pstSegDataInfo   = VOS_NULL_PTR;

        for (ulLoop = NAS_ERABM_NULL; ulLoop < NAS_ERABM_GetIpv4SegBuffItemNum(); ulLoop++)
        {
            pstSegDataInfo = NAS_ERABM_GetIpv4SegBuffItemAddr(ulLoop);

            /* 由同一个大包分片而来的各分片包具有很多相同的属性，比如identifier，
               源和目的IP地址 */
            if ((pstIpv4HeaderInfo->ulIdentifier == pstSegDataInfo->ulIdentifier)
               && (0 == NAS_ERABM_MEM_CMP(  pstIpv4HeaderInfo->aucSrcIpV4Addr,
                                            pstSegDataInfo->aucSrcIpV4Addr,
                                            NAS_ERABM_IPV4_ADDR_LEN))
               && (0 == NAS_ERABM_MEM_CMP(  pstIpv4HeaderInfo->aucDesIpV4Addr,
                                            pstSegDataInfo->aucDesIpV4Addr,
                                            NAS_ERABM_IPV4_ADDR_LEN)))
            {
                *pucBearerIdTmp = pstSegDataInfo->ucBearerId;

                return NAS_ERABM_SUCCESS;
            }
        }

        /* 增加统计量代码 */
        NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_NON_HEADER_FIND_DEFT_FAIL_PACK_NUM();

        *pucBearerIdTmp = NAS_ERABM_IPF_INVALID_BEARER_ID;
        return NAS_ERABM_FAILURE;
    }

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfIpv4NonHeadFragmentProcess
 功能描述  : IPV4非头部分片处理功能
 输入参数  : NAS_ERABM_IPV4_HEADER_STRU         *pucIpv4Data
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月21日
    作    者   : L00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_ERABM_IpfIpv4NonHeadFragmentProcess
(
    const NAS_ERABM_IPV4_HEADER_STRU   *pucIpv4Data
)
{
    VOS_UINT32                          ulRslt          = NAS_ERABM_NULL;
    VOS_UINT8                           ucBearerIdTmp   = NAS_ERABM_NULL;

    /* 根据源IP地址、目的IP地址，identifier在匹配信息结果数组中查找 */
    ulRslt = NAS_ERABM_FindBearerIdInIpv4SegBuff(pucIpv4Data , &ucBearerIdTmp);
    if (NAS_ERABM_SUCCESS == ulRslt)
    {
        return ucBearerIdTmp;
    }

    /* 遍历所有缺省承载，查找源IP地址匹配的承载 */
    ulRslt = NAS_ERABM_GetSrcIpv4MatchedDeftBearerId(pucIpv4Data, &ucBearerIdTmp);
    if (NAS_ERABM_SUCCESS == ulRslt)
    {
        return ucBearerIdTmp;
    }

    return NAS_ERABM_IPF_INVALID_BEARER_ID;
}


/*****************************************************************************
 函 数 名  : NAS_ERABM_Ipv4fIpFragmentProcess
 功能描述  : IPV4分片处理功能
 输入参数  : VOS_UINT8 *pstDataAddr
             VOS_UINT32 ulSegType
             VOS_UINT32 ulMatchId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月21日
    作    者   : L00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_ERABM_IpfIpv4FragmentProcess
(
    VOS_UINT8                          *pstDataAddr,
    VOS_UINT16                          usSegType,
    VOS_UINT8                           ucBearerId,
    VOS_UINT8                           ucUpperLayerFlag
)
{
    VOS_UINT8                          *pucIpv4Data = VOS_NULL_PTR;

    /* 译码IPV4包头，存储源IPV4地址、目的IPV4地址，identifier */
    pucIpv4Data = NAS_ERABM_GET_IP_HEADER_BUFFER();

    NAS_ERABM_DecodeIpV4Data(pstDataAddr, (NAS_ERABM_IPV4_HEADER_STRU *)pucIpv4Data);

    /* 判断是否是头部分片 */
    if (NAS_ERABM_IPF_IPF_FRAGMENT_HEAD == usSegType)
    {
        /* 增加IPV4头部分片统计信息 */
        NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_HEADER_PACK_NUM();

        return NAS_ERABM_IpfIpv4HeadFragmentProcess(    (NAS_ERABM_IPV4_HEADER_STRU *)pucIpv4Data,
                                                        ucBearerId,
                                                        ucUpperLayerFlag);
    }
    else
    {
        /* 增加IPV4非头部分片统计信息 */
        NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_NON_HEADER_PACK_NUM();

        return NAS_ERABM_IpfIpv4NonHeadFragmentProcess((NAS_ERABM_IPV4_HEADER_STRU *)pucIpv4Data);
    }
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_Ipv6fIpFragmentProcess
 功能描述  : IPV6分片处理功能
 输入参数  : VOS_UINT8 *pstDataAddr
             VOS_UINT32 ulSegType
             VOS_UINT32 ulMatchId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年6月21日
    作    者   : L00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_ERABM_IpfIpv6FragmentProcess
(
    VOS_UINT8                          *pstDataAddr,
    VOS_UINT16                          usSegType,
    VOS_UINT8                           ucMatchId,
    VOS_UINT8                           ucUpperLayerFlag
)
{
    VOS_UINT8                          *pucIpv6Data     = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt          = NAS_ERABM_NULL;
    VOS_UINT8                           ucBearerIdTmp   = NAS_ERABM_NULL;

    (VOS_VOID)usSegType;
    (VOS_VOID)ucMatchId;
    (VOS_VOID)ucUpperLayerFlag;

    /* 译码IPV6包头，存储源IPV6地址、目的IPV6地址，identifier */
    pucIpv6Data = NAS_ERABM_GET_IP_HEADER_BUFFER();

    NAS_ERABM_DecodeIpV6Data(pstDataAddr, (NAS_ERABM_IPV6_HEADER_STRU *)pucIpv6Data);

    /* 遍历所有缺省承载，查找源IP地址匹配的承载 */
    ulRslt = NAS_ERABM_GetSrcIpv6MatchedDeftBearerId(   (NAS_ERABM_IPV6_HEADER_STRU *)pucIpv6Data,
                                                        &ucBearerIdTmp);
    if (NAS_ERABM_SUCCESS == ulRslt)
    {
        return ucBearerIdTmp;
    }

    return NAS_ERABM_IPF_INVALID_BEARER_ID;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfIpFragmentProcess
 功能描述  : 上行IP分片处理功能
 输入参数  : VOS_UINT8 *pstDataAddr
             VOS_UINT32 ulIpVer
             VOS_UINT32 ulSegType
             VOS_UINT32 ulMatchId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月2日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_ERABM_IpfIpFragmentProcess
(
    VOS_UINT8                          *pstDataAddr,
    VOS_UINT16                          usIpVer,
    VOS_UINT16                          usSegType,
    VOS_UINT8                           ucBearerId,
    VOS_UINT8                           ucUpperLayerFlag
)
{
    if (NAS_ERABM_IPFILTER_VERSION_4 == usIpVer)
    {
        /* add ul ipv4 frament packet num */
        NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV4_PACK_NUM();

        ucBearerId = NAS_ERABM_IpfIpv4FragmentProcess(pstDataAddr, usSegType, ucBearerId, ucUpperLayerFlag);
    }
    else
    {
        /* add ul ipv6 frament packet num */
        NAS_ERABM_IPF_OM_ADD_RCV_UL_IPV6_PACK_NUM();

        ucBearerId = NAS_ERABM_IpfIpv6FragmentProcess(pstDataAddr, usSegType, ucBearerId, ucUpperLayerFlag);
    }

    return ucBearerId;
}


/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfAddUlNdisFilter
 功能描述  : 用于添加上行NDIS的几种FILTER类型
 输入参数  : VOS_UINT32 ulFilterId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    作    者   : L00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_IpfAddUlNdisFilter(VOS_UINT32 ulFilterId)
{
    NAS_ERABM_IPF_UL_NDIS_FILTER_INFO  *pstUlNdisFilter = VOS_NULL_PTR;
    IPF_FILTER_CONFIG_S                *pstIpFilter     = VOS_NULL_PTR;

    if(ulFilterId >= NAS_ERABM_IPF_UL_NDIS_FILTER_BUTT)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IpfAddUlNdisFilter, Wrong Filter Type");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfAddUlNdisFilter_ENUM, LNAS_ERABM_WrongFilterType);
        return PS_FAIL;
    }

    /* 从Filter队列中找到下一个空闲的Filter */
    pstIpFilter = NAS_ERABM_IpfGetFreeFilter(NAS_ERABM_IPF_DIRECTION_UL);
    if(VOS_NULL_PTR == pstIpFilter)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IpfAddUlNdisFilter Get Free Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IpfAddUlNdisFilter_ENUM, LNAS_EMM_GET_FILTER_FAIL);
        return PS_FAIL;
    }

    NAS_ERABM_MEM_SET_S(pstIpFilter, sizeof(IPF_FILTER_CONFIG_S),0x0, sizeof(IPF_FILTER_CONFIG_S));

    pstUlNdisFilter = NAS_ERABM_IPF_GET_UL_NDIS_USER_FILTER(ulFilterId);

    pstIpFilter->u32FilterID = ulFilterId;

    pstIpFilter->stMatchInfo.unFltCodeType.Bits.u16Code   = pstUlNdisFilter->usIcmpCode;
    pstIpFilter->stMatchInfo.unFltCodeType.Bits.u16Type   = pstUlNdisFilter->usIcmpType;
    pstIpFilter->stMatchInfo.unDstPort.Bits.u16DstPortHi  = pstUlNdisFilter->usPortHi;
    pstIpFilter->stMatchInfo.unDstPort.Bits.u16DstPortLo  = pstUlNdisFilter->usPortLo;
    pstIpFilter->stMatchInfo.unNextHeader.u32Protocol     = pstUlNdisFilter->ucProtocolId;

    if (NAS_ERABM_IPF_IPTYPE_IPV6 == pstUlNdisFilter->ucIpType)
    {
        NAS_ERABM_MEM_CPY_S(  pstIpFilter->stMatchInfo.u8DstAddr,
                            APP_MAX_IPV6_ADDR_LEN,
                            pstUlNdisFilter->aucDstAdrr,
                            APP_MAX_IPV6_ADDR_LEN);

        NAS_ERABM_MEM_CPY_S(  pstIpFilter->stMatchInfo.u8DstMsk,
                            APP_MAX_IPV6_ADDR_LEN,
                            pstUlNdisFilter->aucDstMask,
                            APP_MAX_IPV6_ADDR_LEN);
    }
    else
    {
        NAS_ERABM_MEM_CPY_S(  pstIpFilter->stMatchInfo.u8DstAddr,
                            16,
                            pstUlNdisFilter->aucDstAdrr,
                            APP_MAX_IPV4_ADDR_LEN);

        NAS_ERABM_MEM_CPY_S(  pstIpFilter->stMatchInfo.u8DstMsk,
                            16,
                            pstUlNdisFilter->aucDstMask,
                            APP_MAX_IPV4_ADDR_LEN);
    }

    pstIpFilter->stMatchInfo.unFltRuleCtrl.Bits.FltType   = pstUlNdisFilter->ucIpType;
    pstIpFilter->stMatchInfo.unFltRuleCtrl.Bits.FltCodeEn = pstUlNdisFilter->bitOpCode;
    pstIpFilter->stMatchInfo.unFltRuleCtrl.Bits.FltTypeEn = pstUlNdisFilter->bitOpType;
    pstIpFilter->stMatchInfo.unFltRuleCtrl.Bits.FltNhEn   = pstUlNdisFilter->bitOpProtocolId;
    pstIpFilter->stMatchInfo.unFltRuleCtrl.Bits.FltRPortEn= pstUlNdisFilter->bitOpPort;
    pstIpFilter->stMatchInfo.unFltRuleCtrl.Bits.FltRAddrEn= pstUlNdisFilter->bitOpDstAdrr;
    pstIpFilter->stMatchInfo.unFltRuleCtrl.Bits.FltBid    = NAS_ERABM_IPF_CONV_ULNDISFILTER_TO_BID(ulFilterId);
    pstIpFilter->stMatchInfo.unFltChain.Bits.u16FltPri    = pstUlNdisFilter->usPriority;
    pstIpFilter->stMatchInfo.unFltRuleCtrl.Bits.FltEn     = NAS_ERABM_OP_TRUE;

    /* 增加上行Filter数目 */
    NAS_ERABM_IPF_ADD_UL_FILTER_NUM();

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_IpfRmvUlNdisFilter
 功能描述  : 删除上行NDIS Filter接口
 输入参数  : VOS_UINT32 ulFilterId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月05日
    作    者   : L00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_IpfRmvUlNdisFilter(VOS_UINT32 ulFilterId)
{
    VOS_UINT32                  i               = 0;
    VOS_UINT32                  j               = 0;
    VOS_UINT32                  ulFound         = PS_FALSE;
    VOS_UINT32                  ulUlFilterNum   = 0;
    IPF_FILTER_CONFIG_S        *pstIpFilter     = VOS_NULL_PTR;
    IPF_FILTER_CONFIG_S        *pstNextFilter   = VOS_NULL_PTR;

    /* 在上行Filter队列中找到对应ID的Filter, 将其后面的Filter向前一位拷贝 */
    ulUlFilterNum = NAS_ERABM_IPF_GET_UL_FILTER_NUM();
    for(i = 0; i < ulUlFilterNum; i++)
    {
        pstIpFilter = NAS_ERABM_IPF_GET_UL_FILTER_PTR(i);

        if(ulFilterId == pstIpFilter->u32FilterID)
        {
            for(j = i; j < (ulUlFilterNum - 1); j++)
            {
                pstIpFilter = NAS_ERABM_IPF_GET_UL_FILTER_PTR(j);
                pstNextFilter = NAS_ERABM_IPF_GET_UL_FILTER_PTR(j+1);

                NAS_ERABM_MEM_CPY_S(pstIpFilter,
                                    sizeof(IPF_FILTER_CONFIG_S),
                                    pstNextFilter,
                                    sizeof(IPF_FILTER_CONFIG_S));
            }

            /* 如果找到了Filter，需要更新Filter数目 */
            ulFound = PS_TRUE;
            break;
        }
    }

    if(PS_TRUE == ulFound)
    {
        /* 设置上行Filter数目为 FilterNum-1 */
        NAS_ERABM_IPF_SET_UL_FILTER_NUM(ulUlFilterNum-1);
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_SetUlNdisFilterValidFlag
 功能描述  : 设置全局变量g_enUlNdisFilterValidFlag
 输入参数  : NAS_ERABM_UL_NDIS_FILTER_FLAG_ENUM_UINT32   enUlNdisFilterFlag
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月12日
    作    者   : L00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_ERABM_SetUlNdisFilterValidFlag
(
    NAS_ERABM_UL_NDIS_FILTER_FLAG_ENUM_UINT32   enUlNdisFilterFlag
)
{
    NAS_ERABM_IPF_SET_UL_NDIS_FILTER_FLAG(enUlNdisFilterFlag);
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_CdsCompare
 功能描述  : CDS中 Filter按优先级排序功能
 输入参数  : const VOS_VOID *arg1
             const VOS_VOID *arg2
 输出参数  : 无
 返 回 值  : VOS_INT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月23日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_INT32 NAS_ERABM_CdsCompare(const VOS_VOID *arg1, const VOS_VOID *arg2)
{
    VOS_UINT16              usVar1;
    VOS_UINT16              usVar2;
    CDS_SOFTFILTER_INFO_STRU*   pstPara1;
    CDS_SOFTFILTER_INFO_STRU*   pstPara2;

    pstPara1 = (CDS_SOFTFILTER_INFO_STRU*) arg1;
    pstPara2 = (CDS_SOFTFILTER_INFO_STRU*) arg2;

    usVar1 = pstPara1->usPrecedence;
    usVar2 = pstPara2->usPrecedence;

    /* IP Filter的优先级从小到大排序 */
    if(usVar1 > usVar2)
    {
        return 1;
    }
    else if(usVar1 < usVar2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}


/*****************************************************************************
 函 数 名  : NAS_ERABM_CdsFilterSort
 功能描述  : IP Filter 优先级比较函数
 输入参数  : CDS_SOFTFILTER_INFO_STRU *pstFilter
             VOS_UINT32 ulNum
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : lihong00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_ERABM_CdsFilterSort(CDS_SOFTFILTER_INFO_STRU *pstFilter, VOS_UINT32 ulNum)
{
    /* 调用C语言的库函数qsort对pstFilter进行快速排序 */
    /*lint -e586*/
    qsort(pstFilter, ulNum, sizeof(CDS_SOFTFILTER_INFO_STRU), (NAS_CDS_COMP_FUNC)NAS_ERABM_CdsCompare);
    /*lint +e586*/
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_CdsGenerateBaseIpv4Filter
 功能描述  : 产生IPv4类型的基本参数的Filter
 输入参数  : const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
             VOS_UINT8 ucEpsbId
 输出参数  : NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : L62099
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_CdsGenerateBaseIpv4Filter
(
    NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay,
    const APP_ESM_IP_ADDR_STRU     *pstPdnAddr,
    VOS_UINT8                       ucEpsbId
)
{
    VOS_UINT32                      i           = 0;
    CDS_SOFTFILTER_INFO_STRU       *pstFilter   = VOS_NULL_PTR;

    /* 从Filter队列中找到下一个空闲的Filter */
    if (pstCdsFilterArryay->ulUpLinkUsedNum >= NAS_ERABM_CDS_MAX_UL_FILTER)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IPF Get Free Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsGenerateBaseIpv4Filter_ENUM, LNAS_EMM_GET_FILTER_FAIL);
        return PS_FAIL;
    }
    pstFilter = &pstCdsFilterArryay->astUlFilter[pstCdsFilterArryay->ulUpLinkUsedNum];

    NAS_ERABM_MEM_SET_S(pstFilter,sizeof(CDS_SOFTFILTER_INFO_STRU), 0x0, sizeof(CDS_SOFTFILTER_INFO_STRU));

    /* 填写IP Filter参数 */
    pstFilter->ucRabId      = ucEpsbId;
    pstFilter->enFilterType = CDS_SOFTFILTER_TYPE_IPV4;

    for(i = 0; i < APP_MAX_IPV4_ADDR_LEN; i++)
    {
        pstFilter->unLocalIpv4Addr.aucIPAddr[i] = pstPdnAddr->aucIpV4Addr[i];
        pstFilter->unLocalIpv4Mask.aucIPAddr[i] = 0xFF;
    }

    /* 环回模式下不匹配IP地址 */
    if (NAS_ERABM_MODE_TYPE_NORMAL == NAS_ERABM_GetMode())
    {
        pstFilter->bitOpLcIpv4AddrAndMask   = NAS_ERABM_OP_TRUE;
    }
    else
    {
        pstFilter->bitOpLcIpv4AddrAndMask   = NAS_ERABM_OP_FALSE;
    }

    /* Precedence = 256 */
    pstFilter->usPrecedence = NAS_ERABM_CDS_LOWEST_PRI;

    /* Bearer Id */
    pstFilter->ulPacketFilterId = NAS_ERABM_IPF_UL_IPV4_FILTER_ID(ucEpsbId, 0);

    /* 增加上行Filter数目 */
    pstCdsFilterArryay->ulUpLinkUsedNum++;

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_CdsGenerateBaseIpv6Filter
 功能描述  : 产生IPv6格式的基本参数的Filter
 输入参数  : const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
             VOS_UINT8 ucEpsbId
 输出参数  : NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : lihong00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_CdsGenerateBaseIpv6Filter
(
    NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay,
    const APP_ESM_IP_ADDR_STRU     *pstPdnAddr,
    VOS_UINT8                       ucEpsbId
)
{
    VOS_UINT32                      i           = 0;
    CDS_SOFTFILTER_INFO_STRU       *pstFilter   = VOS_NULL_PTR;
    VOS_UINT8                       aucInvalidIpv6Prefix[NAS_ERABM_IPV6_PREFIX_LEN] = {0};

    /* 检查IPv6前缀是否有效，如果无效，则不配置IPF，直接返回 */
    if(0 == NAS_ERABM_MEM_CMP(  pstPdnAddr->aucIpV6Addr,
                                aucInvalidIpv6Prefix,
                                NAS_ERABM_IPV6_PREFIX_LEN))
    {
        NAS_ERABM_NORM_LOG("NAS_ERABM_CdsGenerateBaseIpv6Filter IPv6 prefix invalid.");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_CdsGenerateBaseIpv6Filter_ENUM, LNAS_ERABM_IPv6PrefixInvalid);
        return PS_SUCC;
    }

    /* 从Filter队列中找到下一个空闲的Filter */
    if (pstCdsFilterArryay->ulUpLinkUsedNum >= NAS_ERABM_CDS_MAX_UL_FILTER)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IPF Get Free Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsGenerateBaseIpv6Filter_ENUM, LNAS_EMM_GET_FILTER_FAIL);
        return PS_FAIL;
    }
    pstFilter = &pstCdsFilterArryay->astUlFilter[pstCdsFilterArryay->ulUpLinkUsedNum];

    NAS_ERABM_MEM_SET_S(pstFilter,sizeof(CDS_SOFTFILTER_INFO_STRU), 0x0, sizeof(CDS_SOFTFILTER_INFO_STRU));

    /* 填写IP Filter参数 */
    pstFilter->ucRabId      = ucEpsbId;
    pstFilter->enFilterType = CDS_SOFTFILTER_TYPE_IPV6;

    /* IPv6只过滤64bit前缀 */
    for(i = 0; i < (APP_MAX_IPV6_ADDR_LEN/2); i++)
    {
        pstFilter->unLocalIpv6Addr.aucIPAddr[i] = pstPdnAddr->aucIpV6Addr[i];
        pstFilter->unLocalIpv6Mask.aucIPAddr[i] = 0xFF;
    }

    /* 环回模式下不匹配IP地址 */
    if (NAS_ERABM_MODE_TYPE_NORMAL == NAS_ERABM_GetMode())
    {
        pstFilter->bitOpLcIpv6AddrAndMask   = NAS_ERABM_OP_TRUE;
    }
    else
    {
        pstFilter->bitOpLcIpv6AddrAndMask   = NAS_ERABM_OP_FALSE;
    }

    /* Precedence = 256 */
    pstFilter->usPrecedence = NAS_ERABM_CDS_LOWEST_PRI;

    /* Bearer Id */
    pstFilter->ulPacketFilterId = NAS_ERABM_IPF_UL_IPV6_FILTER_ID(ucEpsbId,0);

    /* 增加上行Filter数目 */
    pstCdsFilterArryay->ulUpLinkUsedNum++;

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_CdsGenerateFilterWithoutTFT
 功能描述  : 产生不携带TFT参数的承载的FILTER信息
 输入参数  : APP_ESM_IP_ADDR_STRU *pstPdnAddr
             VOS_UINT8 ucEpsbId
 输出参数  : NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : lihong00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_CdsGenerateFilterWithoutTFT
(
    NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay,
    const APP_ESM_IP_ADDR_STRU     *pstPdnAddr,
    VOS_UINT8                       ucEpsbId
)
{
    /* check ip type: ipv4, ipv4v6 */
    if((APP_ESM_PDN_TYPE_IPV4 == pstPdnAddr->ucIpType)||
       (APP_ESM_PDN_TYPE_IPV4_IPV6 == pstPdnAddr->ucIpType))
    {
        if(PS_FAIL == NAS_ERABM_CdsGenerateBaseIpv4Filter(pstCdsFilterArryay, pstPdnAddr, ucEpsbId))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_CdsGenerateFilterWithoutTFT: Generate Ipv4 Filter Fail.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsGenerateFilterWithoutTFT_ENUM, LNAS_EMM_IPV4_FAIL);
            return PS_FAIL;
        }
    }

    /* check ip type: ipv6, ipv4v6 */
    if((APP_ESM_PDN_TYPE_IPV6 == pstPdnAddr->ucIpType)||
       (APP_ESM_PDN_TYPE_IPV4_IPV6 == pstPdnAddr->ucIpType))
    {
        if(PS_FAIL ==  NAS_ERABM_CdsGenerateBaseIpv6Filter(pstCdsFilterArryay, pstPdnAddr, ucEpsbId))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_CdsGenerateFilterWithoutTFT: Generate Ipv6 Filter Fail.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsGenerateFilterWithoutTFT_ENUM, LNAS_EMM_IPV6_FAIL);
            return PS_FAIL;
        }
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_CdsConvertOtherPartToFilter
 功能描述  : 将 TFT参数中除源地址/目的地址/FlowLabel 等与V4V6相关参数之外的
             数据转换为IP Filter格式
 输入参数  : const ESM_ERABM_TFT_PF_STRU *pstTftPf,
             CDS_SOFTFILTER_INFO_STRU               *pstFilter
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : lihong00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_ERABM_CdsConvertOtherPartToFilter
(
    const ESM_ERABM_TFT_PF_STRU        *pstTftPf,
    CDS_SOFTFILTER_INFO_STRU           *pstFilter
)
{
    /* Protocol id */
    pstFilter->bitOpProtocolId          = pstTftPf->bitOpProtocolId;
    pstFilter->ucProtocolId             = pstTftPf->ucProtocolId;

    /* local port */
    pstFilter->bitOpSingleLocalPort     = pstTftPf->bitOpSingleLocalPort;
    pstFilter->usSingleLcPort           = pstTftPf->usSingleLcPort;

    /* local port range, low to high */
    pstFilter->bitOpLocalPortRange      = pstTftPf->bitOpLocalPortRange;
    pstFilter->usLcPortLowLimit         = pstTftPf->usLcPortLowLimit;
    pstFilter->usLcPortHighLimit        = pstTftPf->usLcPortHighLimit;

    /* remote port */
    pstFilter->bitOpSingleRemotePort    = pstTftPf->bitOpSingleRemotePort;
    pstFilter->usSingleRmtPort          = pstTftPf->usSingleRmtPort;

    /* remote port range , low to high */
    pstFilter->bitOpRemotePortRange     = pstTftPf->bitOpRemotePortRange;
    pstFilter->usRmtPortLowLimit        = pstTftPf->usRmtPortLowLimit;
    pstFilter->usRmtPortHighLimit       = pstTftPf->usRmtPortHighLimit;

    /* type of server and mask for ipv4, traffic class and mask for ipv6*/
    pstFilter->bitOpTypeOfService       = pstTftPf->bitOpTypeOfService;
    pstFilter->ucTypeOfService          = pstTftPf->ucTypeOfService;
    pstFilter->ucTypeOfServiceMask      = pstTftPf->ucTypeOfServiceMask;

    /* spi for esp or ah ? */
    pstFilter->bitOpSecuParaIndex       = pstTftPf->bitOpSecuParaIndex;
    pstFilter->ulSecuParaIndex          = pstTftPf->ulSecuParaIndex;

    return;
}


/*****************************************************************************
 函 数 名  : NAS_ERABM_CdsConvertIpv4TftToFilter
 功能描述  : 将IPv4格式TFT转换为IP filter格式
 输入参数  : const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
             const ESM_ERABM_TFT_PF_STRU *pstTftPf,
             VOS_UINT8            ucEpsbId
 输出参数  : NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay,
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : lihong00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_CdsConvertIpv4TftToFilter
(
    NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay,
    const APP_ESM_IP_ADDR_STRU     *pstPdnAddr,
    const ESM_ERABM_TFT_PF_STRU    *pstTftPf,
    VOS_UINT8                       ucEpsbId
)
{
    VOS_UINT32                          i               = 0;
    CDS_SOFTFILTER_INFO_STRU           *pstFilter       = VOS_NULL_PTR;

    /* 从Filter队列中找到下一个空闲的Filter */
    if (pstCdsFilterArryay->ulUpLinkUsedNum >= NAS_ERABM_CDS_MAX_UL_FILTER)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IPF Get Free Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsConvertIpv4TftToFilter_ENUM, LNAS_EMM_GET_FILTER_FAIL);
        return PS_FAIL;
    }
    pstFilter = &pstCdsFilterArryay->astUlFilter[pstCdsFilterArryay->ulUpLinkUsedNum];

    NAS_ERABM_MEM_SET_S(pstFilter,sizeof(CDS_SOFTFILTER_INFO_STRU), 0x0, sizeof(CDS_SOFTFILTER_INFO_STRU));

    /* source address and mask for ipv4 */
    for(i = 0;i < APP_MAX_IPV4_ADDR_LEN; i++)
    {
        pstFilter->unLocalIpv4Addr.aucIPAddr[i] = pstPdnAddr->aucIpV4Addr[i];
        pstFilter->unLocalIpv4Mask.aucIPAddr[i] = 0xFF;
    }

    /* 环回模式下不匹配IP地址 */
    if (NAS_ERABM_MODE_TYPE_NORMAL == NAS_ERABM_GetMode())
    {
        pstFilter->bitOpLcIpv4AddrAndMask   = NAS_ERABM_OP_TRUE;
    }
    else
    {
        pstFilter->bitOpLcIpv4AddrAndMask   = NAS_ERABM_OP_FALSE;
    }

    /* destination address and mask for ipv4 */
    if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpRmtIpv4AddrAndMask)
    {
        for(i = 0;i < APP_MAX_IPV4_ADDR_LEN; i++)
        {
            pstFilter->unRmtIpv4Addr.aucIPAddr[i]   = pstTftPf->aucRmtIpv4Address[i];
            pstFilter->unRmtIpv4Mask.aucIPAddr[i]   = pstTftPf->aucRmtIpv4Mask[i];
        }
        pstFilter->bitOpRmtIpv4AddrAndMask   = NAS_ERABM_OP_TRUE;
    }

    pstFilter->enFilterType = CDS_SOFTFILTER_TYPE_IPV4;

    /* 将TFT参数中的其余部分转换为IP Filter格式 */
    NAS_ERABM_CdsConvertOtherPartToFilter(pstTftPf, pstFilter);

    /* Filter ID */
    pstFilter->ulPacketFilterId = NAS_ERABM_IPF_UL_IPV4_FILTER_ID(  ucEpsbId,
                                                                    pstTftPf->ucNwPacketFilterId);

    /* Filter Precedence and Bearer Id */
    pstFilter->usPrecedence = pstTftPf->ucPrecedence;
    pstFilter->ucRabId      = ucEpsbId;

    /* 增加上行Filter数目 */
    pstCdsFilterArryay->ulUpLinkUsedNum++;

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_CdsConvertIpv6TftToFilter
 功能描述  : 将IPv6格式TFT转换为IP Filter格式
 输入参数  : const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
             const ESM_ERABM_TFT_PF_STRU *pstTftPf,
             VOS_UINT8            ucEpsbId
 输出参数  : NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay,
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : lihong00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_CdsConvertIpv6TftToFilter
(
    NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay,
    const APP_ESM_IP_ADDR_STRU     *pstPdnAddr,
    const ESM_ERABM_TFT_PF_STRU    *pstTftPf,
    VOS_UINT8                       ucEpsbId
)
{
    VOS_UINT32                          i               = 0;
    CDS_SOFTFILTER_INFO_STRU           *pstFilter       = VOS_NULL_PTR;

    /* 从Filter队列中找到下一个空闲的Filter */
    if (pstCdsFilterArryay->ulUpLinkUsedNum >= NAS_ERABM_CDS_MAX_UL_FILTER)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IPF Get Free Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsConvertIpv6TftToFilter_ENUM, LNAS_EMM_GET_FILTER_FAIL);
        return PS_FAIL;
    }
    pstFilter = &pstCdsFilterArryay->astUlFilter[pstCdsFilterArryay->ulUpLinkUsedNum];

    NAS_ERABM_MEM_SET_S(pstFilter,sizeof(CDS_SOFTFILTER_INFO_STRU), 0x0, sizeof(CDS_SOFTFILTER_INFO_STRU));

    /* source address and mask for ipv6 */
    /* IPv6只过滤64bit前缀 */
    for(i = 0;i < (APP_MAX_IPV6_ADDR_LEN/2); i++)
    {
        pstFilter->unLocalIpv6Addr.aucIPAddr[i] = pstPdnAddr->aucIpV6Addr[i];
        pstFilter->unLocalIpv6Mask.aucIPAddr[i] = 0xFF;
    }

    /* 环回模式下不匹配IP地址 */
    if (NAS_ERABM_MODE_TYPE_NORMAL == NAS_ERABM_GetMode())
    {
        pstFilter->bitOpLcIpv6AddrAndMask   = NAS_ERABM_OP_TRUE;
    }
    else
    {
        pstFilter->bitOpLcIpv6AddrAndMask   = NAS_ERABM_OP_FALSE;
    }

    /* destination address and mask for ipv6 */
    if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpRmtIpv6AddrAndMask)
    {
        for(i = 0;i < APP_MAX_IPV6_ADDR_LEN; i++)
        {
            pstFilter->unRmtIpv6Addr.aucIPAddr[i]   = pstTftPf->aucRmtIpv6Address[i];
            pstFilter->unRmtIpv6Mask.aucIPAddr[i]   = pstTftPf->aucRmtIpv6Mask[i];
        }
        pstFilter->bitOpRmtIpv6AddrAndMask      = NAS_ERABM_OP_TRUE;
    }

    /* flowlabel for ipv6 */
    if(NAS_ERABM_OP_TRUE == pstTftPf->bitOpFlowLabelType)
    {
        pstFilter->ulFlowLabelType      = pstTftPf->ulFlowLabelType;
        pstFilter->bitOpFlowLabelType   = NAS_ERABM_OP_TRUE;
    }

    pstFilter->enFilterType = CDS_SOFTFILTER_TYPE_IPV6;

    /* 将TFT参数中的其余部分转换为IP Filter格式 */
    NAS_ERABM_CdsConvertOtherPartToFilter(pstTftPf, pstFilter);

    /* Filter ID */
    pstFilter->ulPacketFilterId = NAS_ERABM_IPF_UL_IPV4_FILTER_ID(  ucEpsbId,
                                                                    pstTftPf->ucNwPacketFilterId);

    /* Filter Precedence and Bearer Id */
    pstFilter->usPrecedence = pstTftPf->ucPrecedence;
    pstFilter->ucRabId      = ucEpsbId;

    /* 增加上行Filter数目 */
    pstCdsFilterArryay->ulUpLinkUsedNum++;

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : NAS_ERABM_CdsConvertTftToFilter
 功能描述  : 将指定上行TFT参数转换为IP Filter格式
 输入参数  : const APP_ESM_IP_ADDR_STRU   *pstPdnAddr,
             const ESM_ERABM_TFT_PF_STRU   *pstTftPf,
             VOS_UINT8                     ucEpsbId
 输出参数  : NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay,
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : lihong00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_CdsConvertTftToFilter
(
    NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay,
    const APP_ESM_IP_ADDR_STRU     *pstPdnAddr,
    const ESM_ERABM_TFT_PF_STRU    *pstTftPf,
    VOS_UINT8                       ucEpsbId
)
{
    VOS_UINT32                  ulFilterType    = NAS_ERABM_IPF_IPTYPE_IPV4;

    /* 需要首先检查TFT对应的IP类型 */
    ulFilterType = NAS_ERABM_IpfCheckFilterType(pstTftPf, pstPdnAddr->ucIpType);

    /* 首先根据不同类型生成IP Filter */
    if((NAS_ERABM_IPF_IPTYPE_IPV4 == ulFilterType)||
       (NAS_ERABM_IPF_IPTYPE_IPV4V6 == ulFilterType))
    {
        if(PS_FAIL == NAS_ERABM_CdsConvertIpv4TftToFilter(  pstCdsFilterArryay,
                                                            pstPdnAddr,
                                                            pstTftPf,
                                                            ucEpsbId))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_CdsConvertTftToFilter: Convert Ipv4 Filter Fail.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsConvertTftToFilter_ENUM, LNAS_ERABM_ConvertIpv4FilterFail);
            return PS_FAIL;
        }
    }

    if((NAS_ERABM_IPF_IPTYPE_IPV6 == ulFilterType)||
       (NAS_ERABM_IPF_IPTYPE_IPV4V6 == ulFilterType))
    {
        if(PS_FAIL == NAS_ERABM_CdsConvertIpv6TftToFilter(  pstCdsFilterArryay,
                                                            pstPdnAddr,
                                                            pstTftPf,
                                                            ucEpsbId))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_CdsConvertTftToFilter: Convert Ipv6 Filter Fail.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsConvertTftToFilter_ENUM, LNAS_ERABM_ConvertIpv6FilterFail);
            return PS_FAIL;
        }
    }

    return PS_SUCC;
}

/*****************************************************************************
 函 数 名  : NAS_ERABM_CdsGenerateFilterWithTFT
 功能描述  : 遍历承载的所有TFT参数，并转换为IP Filter
 输入参数  : const APP_ESM_IP_ADDR_STRU *pstPdnAddr,
             VOS_UINT8 ucEpsbId
 输出参数  : NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay,
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : lihong00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_CdsGenerateFilterWithTFT
(
    NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay,
    const APP_ESM_IP_ADDR_STRU     *pstPdnAddr,
    VOS_UINT8                       ucEpsbId
)
{
    VOS_UINT32                      ulTftPfCnt      = NAS_ERABM_NULL;
    ESM_ERABM_TFT_PF_STRU           *pstTftInfo      = VOS_NULL_PTR;

    for(ulTftPfCnt = 0; ulTftPfCnt < NAS_ERABM_GetEpsbTftPfNum(ucEpsbId); ulTftPfCnt++)
    {
        pstTftInfo = NAS_ERABM_GetEpsbTftAddr(ucEpsbId, ulTftPfCnt);

        /* 不需要处理下行TFT参数 */
        if (APP_ESM_TRANSFER_DIRECTION_DOWNLINK == pstTftInfo->enDirection)
        {
            continue;
        }

        /* 将TFT参数转换为IP Filter格式 */
        if(PS_FAIL == NAS_ERABM_CdsConvertTftToFilter(pstCdsFilterArryay, pstPdnAddr, pstTftInfo, ucEpsbId))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_CdsGenerateFilterWithTFT: Convert TFT to IPF Filter Failed.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsGenerateFilterWithTFT_ENUM, LNAS_EMM_TFT_TO_IPF_FAIL);
            return PS_FAIL;
        }
    }

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : NAS_ERABM_CdsGenerateFilters
 功能描述  : 遍历所有承载，生成IP FIlter参数
 输出参数  : NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : lihong00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_CdsGenerateFilters
(
    NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay
)
{
    VOS_UINT8                       ucEpsbId        = NAS_ERABM_NULL;
    APP_ESM_IP_ADDR_STRU           *pstPdnAddr      = VOS_NULL_PTR;

    /* 清空当前所有Filter */
    pstCdsFilterArryay->ulUpLinkUsedNum = 0;

    for(ucEpsbId = NAS_ERABM_MIN_EPSB_ID; ucEpsbId <= NAS_ERABM_MAX_EPSB_ID; ucEpsbId++)
    {
        if (NAS_ERABM_EPSB_ACTIVE != NAS_ERABM_GetEpsbStateInfo(ucEpsbId))
        {
            /* 承载未激活，返回 */
            continue;
        }

        /* 查找PDN连接地址 */
        pstPdnAddr = NAS_ERABM_GetEpsbPdnAddr(ucEpsbId);

        /* 先处理未配置TFT参数的默认承载 */
        if(PS_FALSE == NAS_ERABM_IsExistUplinkPfinTft(ucEpsbId))
        {
            if(PS_FAIL == NAS_ERABM_CdsGenerateFilterWithoutTFT(pstCdsFilterArryay,
                                                                pstPdnAddr,
                                                                ucEpsbId))
            {
                NAS_ERABM_ERR_LOG("NAS_ERABM_CDS Generate Default Bearer Filter Failed.");
                TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsGenerateFilters_ENUM, LNAS_FUNCTION_LABEL1);
                return PS_FAIL;
            }
        }
        else
        {
            /* 其它专有承载或配置了TFT参数的默认承载,需要根据TFT Filter进行转换 */
            if(PS_FAIL == NAS_ERABM_CdsGenerateFilterWithTFT(pstCdsFilterArryay, pstPdnAddr, ucEpsbId))
            {
                NAS_ERABM_ERR_LOG("NAS_ERABM_CDS Generate Dedicate Bearer Filter Failed.");
                TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsGenerateFilters_ENUM, LNAS_FUNCTION_LABEL2);
                return PS_FAIL;
            }
        }
    }

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* 支持EHRPD的情况下，生成过滤器要将未恢复的EHRPD承载信息也全部生成配置给CDS */
    for(ucEpsbId = NAS_ERABM_MIN_EPSB_ID; ucEpsbId <= NAS_ERABM_MAX_EPSB_ID; ucEpsbId++)
    {
        if (NAS_ERABM_EPSB_ACTIVE != NAS_ERABM_GetEhrpdBearerStateInfo(ucEpsbId))
        {
            /* 承载未激活，继续 */
            continue;
        }

        NAS_ERABM_LOG1("NAS_ERABM_CDS Generate Default Bearer Filter: EHRPD Bearer active, ID =", ucEpsbId);
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_CdsGenerateFilters_ENUM, LNAS_ERABM_EhrpdBearerId, ucEpsbId);

        /* 查找PDN连接地址 */
        pstPdnAddr = NAS_ERABM_GetEhrpdPdnAddr(ucEpsbId);

        /* 当前的实现，不支持CL的专有承载互操作，因此激活的只能是缺省承载 */
        if(PS_FAIL == NAS_ERABM_CdsGenerateFilterWithoutTFT(pstCdsFilterArryay, pstPdnAddr, ucEpsbId))
        {
            NAS_ERABM_ERR_LOG("NAS_ERABM_CDS Generate EHRPD Default Bearer Filter Failed.");
            TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsGenerateFilters_ENUM, LNAS_FUNCTION_LABEL3);
            return PS_FAIL;
        }
    }

    #endif

    return PS_SUCC;
}


/*****************************************************************************
 函 数 名  : NAS_ERABM_CdsConfigUlFilter
 功能描述  : 遍历所有上行TFT, 生成IP Filter, 并配置到CDS
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月12日
    作    者   : lihong00150010
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_ERABM_CdsConfigUlFilter( VOS_VOID )
{
    NAS_ERABM_CDS_FILTER_ARRAY     *pstCdsFilterArryay = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_CdsConfigUlFilter is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_CdsConfigUlFilter_ENUM, LNAS_ENTRY);

    pstCdsFilterArryay = (NAS_ERABM_CDS_FILTER_ARRAY*)NAS_ERABM_MEM_ALLOC(sizeof(NAS_ERABM_CDS_FILTER_ARRAY));
    if (VOS_NULL_PTR == pstCdsFilterArryay)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_CdsConfigUlFilter: mem alloc fail!.");
        return PS_FAIL;
    }

    /* 遍历所有TFT，生成IP Filter */
    if(PS_FAIL == NAS_ERABM_CdsGenerateFilters(pstCdsFilterArryay))
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_CdsConfigUlFilter: Generate All Filters Fail.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsConfigUlFilter_ENUM, LNAS_ERABM_GenerateAllFiltersFail);

        NAS_ERABM_MEM_FREE(pstCdsFilterArryay);
        return PS_FAIL;
    }

    /*Coverity 告警消除 2013-9-26 Begin*/
    NAS_ERABM_CdsFilterSort(    &(pstCdsFilterArryay->astUlFilter[0]),
                                pstCdsFilterArryay->ulUpLinkUsedNum);
    /*Coverity 告警消除 2013-9-26 End*/

    /* 将上行软过滤器配置给CDS */
    if(PS_SUCC != CDS_SetUlSoftFilter(  &(pstCdsFilterArryay->astUlFilter[0]),
                                        pstCdsFilterArryay->ulUpLinkUsedNum))
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_CdsConfigUlFilter: CDS_SetUlFilter Fail.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_CdsConfigUlFilter_ENUM, LNAS_FUNCTION_LABEL1);

        NAS_ERABM_MEM_FREE(pstCdsFilterArryay);
        return PS_FAIL;
    }
    NAS_ERABM_SndOmLogCdsUlFilterInfo(pstCdsFilterArryay->astUlFilter, pstCdsFilterArryay->ulUpLinkUsedNum);
    NAS_ERABM_MEM_FREE(pstCdsFilterArryay);
    return PS_SUCC;
}
/*****************************************************************************
 函 数 名  : NAS_ERABM_SndOmLogIpfUlFilterInfo
 功能描述  : 输出ERABM给IPF配置的FILTER信息，只输出前16个
 输出参数  : 无
 返 回 值  : None
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月18日
    作    者   : leixiantiao 00258641
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_ERABM_SndOmLogIpfUlFilterInfo(IPF_FILTER_CONFIG_S  *pstFilterList, VOS_UINT32  ulIpFilterNum)
{
    NAS_ERABM_OM_LOG_IPF_FILTER_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_ERABM_OM_LOG_IPF_FILTER_INFO_STRU *)NAS_ERABM_MEM_ALLOC(sizeof(NAS_ERABM_OM_LOG_IPF_FILTER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndOmLogUlFilterInfo: mem alloc fail!.");
        return;
    }

    NAS_ERABM_MEM_SET_S(pstMsg,sizeof(NAS_ERABM_OM_LOG_IPF_FILTER_INFO_STRU), 0, sizeof(NAS_ERABM_OM_LOG_IPF_FILTER_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_RABM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_RABM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_ERABM_OM_LOG_IPF_FILTER_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = ID_NAS_ERABM_OM_LOG_IPF_FILTER_INFO;
    pstMsg->ulFilterNum = ulIpFilterNum;
    if(ulIpFilterNum <= NAS_ERABM_OM_LOG_MAX_FILTER)
    {
        NAS_ERABM_MEM_CPY_S(pstMsg->astUlFilter,
                        NAS_ERABM_OM_LOG_MAX_FILTER*sizeof(IPF_FILTER_CONFIG_S),
                        pstFilterList,
                        ulIpFilterNum * sizeof(IPF_FILTER_CONFIG_S));
    }
    else
    {
        NAS_ERABM_MEM_CPY_S(pstMsg->astUlFilter,
                        NAS_ERABM_OM_LOG_MAX_FILTER * sizeof(IPF_FILTER_CONFIG_S),
                        pstFilterList,
                        NAS_ERABM_OM_LOG_MAX_FILTER * sizeof(IPF_FILTER_CONFIG_S));
    }
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ERABM_MEM_FREE(pstMsg);
    return;
}
/*****************************************************************************
 函 数 名  : NAS_ERABM_SndOmLogCdsUlFilterInfo
 功能描述  : 输出ERABM给CDS配置的FILTER信息，只输出前16个
 输出参数  : 无
 返 回 值  : None
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年3月18日
    作    者   : leixiantiao 00258641
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_ERABM_SndOmLogCdsUlFilterInfo(CDS_SOFTFILTER_INFO_STRU  *pstFilterList, VOS_UINT32  ulUpLinkUsedNum)
{
    NAS_ERABM_OM_LOG_CDS_FILTER_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_ERABM_OM_LOG_CDS_FILTER_INFO_STRU *)NAS_ERABM_MEM_ALLOC(sizeof(NAS_ERABM_OM_LOG_CDS_FILTER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndOmLogUlFilterInfo: mem alloc fail!.");
        return;
    }

    NAS_ERABM_MEM_SET_S(pstMsg,sizeof(NAS_ERABM_OM_LOG_CDS_FILTER_INFO_STRU), 0, sizeof(NAS_ERABM_OM_LOG_CDS_FILTER_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_RABM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_RABM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_ERABM_OM_LOG_CDS_FILTER_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = ID_NAS_ERABM_OM_LOG_CDS_FILTER_INFO;
    pstMsg->ulUpLinkUsedNum = ulUpLinkUsedNum;
    if(ulUpLinkUsedNum <= NAS_ERABM_OM_LOG_MAX_FILTER)
    {
        NAS_ERABM_MEM_CPY_S(pstMsg->astUlFilter,
                        NAS_ERABM_OM_LOG_MAX_FILTER * sizeof(CDS_SOFTFILTER_INFO_STRU),
                        pstFilterList,
                        ulUpLinkUsedNum * sizeof(CDS_SOFTFILTER_INFO_STRU));
    }
    else
    {
        NAS_ERABM_MEM_CPY_S(pstMsg->astUlFilter,
                        NAS_ERABM_OM_LOG_MAX_FILTER * sizeof(CDS_SOFTFILTER_INFO_STRU),
                        pstFilterList,
                        NAS_ERABM_OM_LOG_MAX_FILTER * sizeof(CDS_SOFTFILTER_INFO_STRU));
    }
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ERABM_MEM_FREE(pstMsg);
    return;
}


/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


