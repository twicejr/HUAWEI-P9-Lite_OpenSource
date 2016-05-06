/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnApsMultiMode.h
  版 本 号   : 初稿
  作    者   : anhuiqing / 00165503
  生成日期   : 2011年03月30日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2011年03月30日
    作    者   : anhuiqing / 00165503
    修改内容   : 创建文件

******************************************************************************/
#ifndef _MN_APS_MULTI_MODE_H_
#define _MN_APS_MULTI_MODE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的TI
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/

/* 更新 TI，由于SM实现的特殊性，L模下的承载激活，对应到GU的SM与APS的接口来说
   TI的取值范围应该是8~14，所以回复TI值时，做了转换，Tiflag的值取反
*/
#define MN_APS_FillEsmPdpInfoTransId(pstEsmPdpInfoInd, pstPdpEntity)           \
{                                                                              \
    pstEsmPdpInfoInd->stTransId.ucTiFlag  = pstPdpEntity->stTransId.ucTiFlag;  \
    pstEsmPdpInfoInd->stTransId.ucTiValue = pstPdpEntity->stTransId.ucTiValue; \
}

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的NSAPI
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoNsapi(pstEsmPdpInfoInd, pstPdpEntity)  \
{                                                                   \
    pstEsmPdpInfoInd->ulNsapi  = pstPdpEntity->ucNsapi;             \
}

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的CID
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoCid(pstEsmPdpInfoInd, pstPdpEntity)    \
{                                                                   \
    pstEsmPdpInfoInd->ulBitCid                                      \
        = (VOS_UINT32)0x00000001 << (pstPdpEntity->stClientInfo.ucCid);      \
}

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的LINKED NSAPI
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoLinkedNsapi(pstEsmPdpInfoInd, pstPdpEntity)    \
{                                                                           \
    if (APS_PDP_ACT_SEC == pstPdpEntity->ActType)                           \
    {                                                                       \
        pstEsmPdpInfoInd->bitOpLinkedNsapi = VOS_TRUE;                      \
        pstEsmPdpInfoInd->ulLinkedNsapi    = pstPdpEntity->ucLinkedNsapi;   \
    }                                                                       \
}

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PDP ADDRESS
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#if (FEATURE_ON == FEATURE_IPV6)
#define MN_APS_FillEsmPdpInfoPdpAddr(pstEsmPdpInfoInd, pstPdpEntity)    \
{                                                                       \
    if (APS_ADDR_STATIC_IPV4 == pstPdpEntity->PdpAddr.ucPdpTypeNum)     \
    {                                                                   \
        pstEsmPdpInfoInd->stPdpAddr.enPdpType  = SM_ESM_PDP_IPV4;       \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPdpAddr.aucIpV4Addr,             \
                   pstPdpEntity->PdpAddr.aucIpAddr,                     \
                   SM_ESM_IPV4_ADDR_LEN);                               \
    }                                                                   \
    else if (MN_APS_ADDR_IPV6 == pstPdpEntity->PdpAddr.ucPdpTypeNum)    \
    {                                                                   \
        pstEsmPdpInfoInd->stPdpAddr.enPdpType  = SM_ESM_PDP_IPV6;       \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPdpAddr.aucIpV6Addr,             \
                   pstPdpEntity->PdpAddr.aucIpV6Addr,                   \
                   SM_ESM_IPV6_ADDR_LEN);                               \
    }                                                                   \
    else                                                                \
    {                                                                   \
        pstEsmPdpInfoInd->stPdpAddr.enPdpType  = SM_ESM_PDP_IPV4V6;     \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPdpAddr.aucIpV4Addr,             \
                   pstPdpEntity->PdpAddr.aucIpAddr,                     \
                   SM_ESM_IPV4_ADDR_LEN);                               \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPdpAddr.aucIpV6Addr,             \
                   pstPdpEntity->PdpAddr.aucIpV6Addr,                   \
                   SM_ESM_IPV6_ADDR_LEN);                               \
    }                                                                   \
}
#else
#define MN_APS_FillEsmPdpInfoPdpAddr(pstEsmPdpInfoInd, pstPdpEntity)    \
{                                                                       \
    if (APS_ADDR_STATIC_IPV4 == pstPdpEntity->PdpAddr.ucPdpTypeNum)     \
    {                                                                   \
        pstEsmPdpInfoInd->stPdpAddr.enPdpType  = SM_ESM_PDP_IPV4;       \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPdpAddr.aucIpV4Addr,             \
                   pstPdpEntity->PdpAddr.aucIpAddr,                     \
                   SM_ESM_IPV4_ADDR_LEN);                               \
    }                                                                   \
}
#endif

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PDP QOS
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPdpQos(pstEsmPdpInfoInd, pstPdpEntity) \
{                                                                   \
    if (VOS_TRUE == pstPdpEntity->PdpQosFlag)                       \
    {                                                               \
        pstEsmPdpInfoInd->bitOpPdpQos      = VOS_TRUE;              \
        PS_MEM_CPY((VOS_CHAR*)&pstEsmPdpInfoInd->stPdpQos,          \
                   (VOS_CHAR*)&pstPdpEntity->PdpQos,                \
                   sizeof(APS_PDP_QOS_STRU));                       \
    }                                                               \
}

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的APN
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoApn(pstEsmPdpInfoInd, pstPdpEntity)            \
{                                                                           \
    if (VOS_TRUE == pstPdpEntity->PdpApnFlag)                               \
    {                                                                       \
        pstEsmPdpInfoInd->bitOpApn  = VOS_TRUE;                             \
        pstEsmPdpInfoInd->stApn.ucLength  = pstPdpEntity->PdpApn.ucLength;  \
        PS_MEM_CPY(pstEsmPdpInfoInd->stApn.aucValue,                        \
                   pstPdpEntity->PdpApn.aucValue,                           \
                   pstPdpEntity->PdpApn.ucLength);                          \
    }                                                                       \
}

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PACKET FILTER
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPf(pstEsmPdpInfoInd, pstPdpEntity)     \
{                                                                   \
    if (VOS_TRUE == pstPdpEntity->bitOpPf)                          \
    {                                                               \
        pstEsmPdpInfoInd->bitOpTft = VOS_TRUE;                      \
        pstEsmPdpInfoInd->stTft    = pstPdpEntity->stTft;           \
    }                                                               \
}

/*-------------------------------------------------------------------
  开始填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PCO IPV4
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4Begin(pstEsmPdpInfoInd, pstPdpEntity)   \
{                                                                           \
    pstEsmPdpInfoInd->bitOpPcoIpv4Item     = VOS_TRUE;                      \
}

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PCO IPV4: DNS
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4Dns(pstEsmPdpInfoInd, pstPdpEntity) \
{                                                                       \
    if (VOS_TRUE == pstPdpEntity->PdpDnsFlag)                           \
    {                                                                   \
        if (VOS_TRUE == pstPdpEntity->PdpDns.OP_PriDns)                 \
        {                                                               \
            pstEsmPdpInfoInd->stPcoIpv4Item.bitOpPriDns = VOS_TRUE;     \
            PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucPriDns,       \
                       pstPdpEntity->PdpDns.aucPriDns,                  \
                       SM_ESM_IPV4_ADDR_LEN);                           \
        }                                                               \
        if (VOS_TRUE == pstPdpEntity->PdpDns.OP_SecDns)                 \
        {                                                               \
            pstEsmPdpInfoInd->stPcoIpv4Item.bitOpSecDns = VOS_TRUE;     \
            PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucSecDns,       \
                       pstPdpEntity->PdpDns.aucSecDns,                  \
                       SM_ESM_IPV4_ADDR_LEN);                           \
        }                                                               \
    }                                                                   \
}

/*-----------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PCO IPV4: GATE WAY (PEER IP)
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
------------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4GateWay(pstEsmPdpInfoInd, pstPdpEntity) \
{                                                                           \
    if (VOS_TRUE == pstPdpEntity->bitOpPdpGateWay)                          \
    {                                                                       \
        if (VOS_TRUE == pstPdpEntity->stPdpGateWay.bitOpGateWay)            \
        {                                                                   \
            pstEsmPdpInfoInd->stPcoIpv4Item.bitOpGateWay = VOS_TRUE;        \
            PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucGateWay,          \
                       pstPdpEntity->stPdpGateWay.aucGateWay,               \
                       SM_ESM_IPV4_ADDR_LEN);                               \
        }                                                                   \
    }                                                                       \
}

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PCO IPV4: NBNS (WINS)
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4Nbns(pstEsmPdpInfoInd, pstPdpEntity)    \
{                                                                           \
    if (VOS_TRUE == pstPdpEntity->bitOpPdpNbns)                             \
    {                                                                       \
        if (VOS_TRUE == pstPdpEntity->stPdpNbns.OP_PriNbns)                 \
        {                                                                   \
            pstEsmPdpInfoInd->stPcoIpv4Item.bitOpPriNbns = VOS_TRUE;        \
            PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucPriNbns,          \
                       pstPdpEntity->stPdpNbns.aucPriNbns,                  \
                       SM_ESM_IPV4_ADDR_LEN);                               \
        }                                                                   \
        if (VOS_TRUE == pstPdpEntity->stPdpNbns.OP_SecNbns)                 \
        {                                                                   \
            pstEsmPdpInfoInd->stPcoIpv4Item.bitOpSecNbns = VOS_TRUE;        \
            PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucSecNbns,          \
                       pstPdpEntity->stPdpNbns.aucSecNbns,                  \
                       SM_ESM_IPV4_ADDR_LEN);                               \
        }                                                                   \
    }                                                                       \
}

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PCO IPV4: P-CSCF
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4Pcscf(pstEsmPdpInfoInd, pstPdpEntity)   \
{                                                                           \
    if (VOS_TRUE == pstPdpEntity->stPdpPcscf.bitOpPrimPcscfAddr)            \
    {                                                                       \
        pstEsmPdpInfoInd->stPcoIpv4Item.bitOpPriPcscf = VOS_TRUE;           \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucPriPcscf,             \
                   pstPdpEntity->stPdpPcscf.aucPrimPcscfAddr,               \
                   SM_ESM_IPV4_ADDR_LEN);                                   \
    }                                                                       \
    if (VOS_TRUE == pstPdpEntity->stPdpPcscf.bitOpSecPcscfAddr)             \
    {                                                                       \
        pstEsmPdpInfoInd->stPcoIpv4Item.bitOpSecPcscf = VOS_TRUE;           \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucSecPcscf,             \
                   pstPdpEntity->stPdpPcscf.aucSecPcscfAddr,                \
                   SM_ESM_IPV4_ADDR_LEN);                                   \
    }                                                                       \
}

/*-------------------------------------------------------------------
  结束填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PCO IPV4
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4End(pstEsmPdpInfoInd, pstPdpEntity)

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PCO IPV4
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4(pstEsmPdpInfoInd, pstPdpEntity)        \
    MN_APS_FillEsmPdpInfoPcoIpv4Begin(pstEsmPdpInfoInd, pstPdpEntity);      \
    MN_APS_FillEsmPdpInfoPcoIpv4Dns(pstEsmPdpInfoInd, pstPdpEntity);        \
    MN_APS_FillEsmPdpInfoPcoIpv4GateWay(pstEsmPdpInfoInd, pstPdpEntity);    \
    MN_APS_FillEsmPdpInfoPcoIpv4Nbns(pstEsmPdpInfoInd, pstPdpEntity);       \
    MN_APS_FillEsmPdpInfoPcoIpv4Pcscf(pstEsmPdpInfoInd, pstPdpEntity);      \
    MN_APS_FillEsmPdpInfoPcoIpv4End(pstEsmPdpInfoInd, pstPdpEntity);

#if (FEATURE_ON == FEATURE_IPV6)
/*-------------------------------------------------------------------
  开始填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PCO IPV6
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv6Begin(pstEsmPdpInfoInd, pstPdpEntity)   \
{                                                                           \
    pstEsmPdpInfoInd->bitOpPcoIpv6Item     = VOS_TRUE;                      \
}

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PCO IPV6: DNS
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv6Dns(pstEsmPdpInfoInd, pstPdpEntity) \
{                                                                       \
    if (VOS_TRUE == pstPdpEntity->stPdpIpV6Dns.bitOpPriDns)             \
    {                                                                   \
        pstEsmPdpInfoInd->stPcoIpv6Item.bitOpPriDns = VOS_TRUE;         \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv6Item.aucPriDns,           \
                   pstPdpEntity->stPdpIpV6Dns.aucPriDns,                \
                   SM_ESM_IPV6_ADDR_LEN);                               \
    }                                                                   \
    if (VOS_TRUE == pstPdpEntity->stPdpIpV6Dns.bitOpSecDns)             \
    {                                                                   \
        pstEsmPdpInfoInd->stPcoIpv6Item.bitOpSecDns = VOS_TRUE;         \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv6Item.aucSecDns,           \
                   pstPdpEntity->stPdpIpV6Dns.aucSecDns,                \
                   SM_ESM_IPV6_ADDR_LEN);                               \
    }                                                                   \
}

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PCO IPV6: P-CSCF
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv6Pcscf(pstEsmPdpInfoInd, pstPdpEntity)   \
{                                                                           \
    if (VOS_TRUE == pstPdpEntity->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)        \
    {                                                                       \
        pstEsmPdpInfoInd->stPcoIpv6Item.bitOpPriPcscf = VOS_TRUE;           \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv6Item.aucPriPcscf,             \
                   pstPdpEntity->stPdpIpv6Pcscf.aucPrimPcscfAddr,           \
                   SM_ESM_IPV6_ADDR_LEN);                                   \
    }                                                                       \
    if (VOS_TRUE == pstPdpEntity->stPdpIpv6Pcscf.bitOpSecPcscfAddr)         \
    {                                                                       \
        pstEsmPdpInfoInd->stPcoIpv6Item.bitOpSecPcscf = VOS_TRUE;           \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv6Item.aucSecPcscf,             \
                   pstPdpEntity->stPdpIpv6Pcscf.aucSecPcscfAddr,            \
                   SM_ESM_IPV6_ADDR_LEN);                                   \
    }                                                                       \
}

/*-------------------------------------------------------------------
  结束填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PCO IPV6
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv6End(pstEsmPdpInfoInd, pstPdpEntity)

/*-------------------------------------------------------------------
  填写ID_SM_ESM_EPS_BEARER_INFO_IND消息中的PCO IPV6
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv6(pstEsmPdpInfoInd, pstPdpEntity)    \
    MN_APS_FillEsmPdpInfoPcoIpv6Begin(pstEsmPdpInfoInd, pstPdpEntity);  \
    MN_APS_FillEsmPdpInfoPcoIpv6Dns(pstEsmPdpInfoInd, pstPdpEntity);    \
    MN_APS_FillEsmPdpInfoPcoIpv6Pcscf(pstEsmPdpInfoInd, pstPdpEntity);  \
    MN_APS_FillEsmPdpInfoPcoIpv6End(pstEsmPdpInfoInd, pstPdpEntity);
#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : MN_APS_FillEsmPdpInfoIndOptActivatePara
 功能描述  : 填写ID_SM_ESM_PDP_CONTEXT_INFO_IND消息参数
             PDP OPTION 为 SM_ESM_PDP_OPT_ACTIVATE
 输入参数  : pstPdpEntity       - PDP实体信息
 输出参数  : pstEsmPdpInfoInd   - ID_SM_ESM_PDP_CONTEXT_INFO_IND消息内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_FillEsmPdpInfoIndOptActivatePara(
    SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 函 数 名  : MN_APS_FillEsmPdpInfoIndOptModifyPara
 功能描述  : 填写ID_SM_ESM_PDP_CONTEXT_INFO_IND消息参数
             PDP OPTION 为 SM_ESM_PDP_OPT_MODIFY
 输入参数  : pstPdpEntity       - PDP实体信息
 输出参数  : pstEsmPdpInfoInd   - ID_SM_ESM_PDP_CONTEXT_INFO_IND消息内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_FillEsmPdpInfoIndOptModifyPara(
    SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 函 数 名  : MN_APS_FillEsmPdpInfoIndOptDeactivatePara
 功能描述  : 填写ID_SM_ESM_PDP_CONTEXT_INFO_IND消息参数
             PDP OPTION 为 SM_ESM_PDP_OPT_DEACTIVATE
 输入参数  : pstPdpEntity       - PDP实体信息
 输出参数  : pstEsmPdpInfoInd   - ID_SM_ESM_PDP_CONTEXT_INFO_IND消息内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_FillEsmPdpInfoIndOptDeactivatePara(
    SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 函 数 名  : MN_APS_FillEsmPdpInfoIndPara
 功能描述  : 填写ID_SM_ESM_PDP_CONTEXT_INFO_IND消息内容
 输入参数  : pstPdpEntity       - PDP实体信息
             enPdpOption        - PDP实体更新操作(激活, 修改, 和去激活)
 输出参数  : pstEsmPdpInfoInd   - ID_SM_ESM_PDP_CONTEXT_INFO_IND消息内容
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT32 MN_APS_FillEsmPdpInfoIndPara(
    SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_PDP_OPTION_ENUM_UINT32       enPdpOption
);


/*****************************************************************************
 函 数 名  : MN_APS_FillSmBearerActivateIndPara
 功能描述  : 填写ID_MN_SM_BEARER_ACTIVATE_IND消息内容
 输入参数  : pstPdpEntity           - PDP实体信息
 输出参数  : pstSmBearerActivateInd - ID_MN_SM_BEARER_ACTIVATE_IND消息内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_FillSmBearerActivateIndPara(
    SMREG_BEARER_ACTIVATE_IND_STRU     *pstSmBearerActivateInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 函 数 名  : MN_APS_FillSmBearerModifyIndPara
 功能描述  : 填写ID_MN_SM_BEARER_MODIFY_IND消息内容
 输入参数  : pstPdpEntity           - PDP实体信息
 输出参数  : pstSmBearerModifyInd   - ID_MN_SM_BEARER_MODIFY_IND消息内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_FillSmBearerModifyIndPara(
    SMREG_BEARER_MODIFY_IND_STRU       *pstSmBearerModifyInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 函 数 名  : MN_APS_FillSmBearerDeactivateIndPara
 功能描述  : 填写ID_MN_SM_BEARER_DEACTIVATE_IND消息内容
 输入参数  : pstPdpEntity               - PDP实体信息
 输出参数  : pstSmBearerDeactivateInd   - ID_MN_SM_BEARER_DEACTIVATE_IND消息内容
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_FillSmBearerDeactivateIndPara(
    SMREG_BEARER_DEACTIVATE_IND_STRU   *pstSmBearerDeactivateInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 函 数 名  : MN_APS_SndEsmPdpInfoInd
 功能描述  : 发送ID_SM_ESM_PDP_CONTEXT_INFO_IND消息至ESM
 输入参数  : pstPdpEntity   - PDP实体信息
             enPdpOption    - PDP更新状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_SndEsmPdpInfoInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_PDP_OPTION_ENUM_UINT32       enPdpOption
);


/*****************************************************************************
 函 数 名  : MN_APS_SndSmBearerActivateInd
 功能描述  : 发送ID_MN_SM_BEARER_ACTIVATE_IND消息至SM
 输入参数  : pstPdpEntity   - PDP实体信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_SndSmBearerActivateInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);

/*****************************************************************************
 函 数 名  : MN_APS_SndSmSecActivateInd
 功能描述  : 通知SM所有挂接在该缺省承载上的PDP的状态
 输入参数  : pstPdpEntity   - PDP实体信息
 输出参数  : 无
 返 回 值  : VOS_OK         - 成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年06月5日
    作    者   : f00179208
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_APS_SndSmAllSecPdpActivateInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);

/*****************************************************************************
 函 数 名  : MN_APS_SndSmBearerModifyInd
 功能描述  : 发送ID_MN_SM_BEARER_MODIFY_IND消息至SM
 输入参数  : pstPdpEntity   - PDP实体信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_SndSmBearerModifyInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 函 数 名  : MN_APS_SndSmBearerDeactivateInd
 功能描述  : 发送ID_MN_SM_BEARER_DEACTIVATE_IND消息至SM
 输入参数  : pstPdpEntity   - PDP实体信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_SndSmBearerDeactivateInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 函 数 名  : MN_APS_ProcEsmBearerInfoIndOptActivate
 功能描述  :
 输入参数  : SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_ProcEsmBearerInfoIndOptActivate(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 函 数 名  : MN_APS_ProcEsmBearerInfoIndOptModify
 功能描述  :
 输入参数  : SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_ProcEsmBearerInfoIndOptModify(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 函 数 名  : MN_APS_ProcEsmBearerInfoIndOptDeactivate
 功能描述  :
 输入参数  : SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_ProcEsmBearerInfoIndOptDeactivate(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);



/*****************************************************************************
 函 数 名  : MN_APS_UpdatePdpActTypeFromEpsBearer
 功能描述  : 更新PDP ACT TYPE (激活类型)
 输入参数  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpActTypeFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 函 数 名  : MN_APS_UpdatePdpAddrFromEpsBearer
 功能描述  : 更新PDP ADDRESS
 输入参数  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpAddrFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 函 数 名  : MN_APS_UpdatePdpApnFromEpsBearer
 功能描述  : 更新APN
 输入参数  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpApnFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 函 数 名  : MN_APS_UpdatePdpPcoIpv4ItemFromEpsBearer
 功能描述  : 更新PDP PCO IPV4相关参数, 包含DNS, NBNS, PEER IP等
 输入参数  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpPcoIpv4ItemFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 函 数 名  : MN_APS_UpdatePdpPcoIpv6ItemFromEpsBearer
 功能描述  : 更新PDP PCO IPV6相关参数, 包含DNS, PCSCF等
 输入参数  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpPcoIpv6ItemFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);
#endif

/*****************************************************************************
 函 数 名  : MN_APS_UpdatePdpQosFromEpsBearer
 功能描述  : 更新QOS
 输入参数  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpQosFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);

/*****************************************************************************
 函 数 名  : MN_APS_UpdateEpsQosFromEpsBearer
 功能描述  : 更新EPS QOS
 输入参数  : pstPdpEntity           - PDP实体
             pstEpsBearerInfoInd    - EPS Bearer信息
 输出参数  : 无
 返 回 值  : VOS_VOID

*****************************************************************************/
VOS_VOID MN_APS_UpdateEpsQosFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);

/*****************************************************************************
 函 数 名  : MN_APS_UpdatePdpPfFromEpsBearer
 功能描述  : 更新PACKET FILTER
 输入参数  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpPfFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 函 数 名  : MN_APS_UpdatePdpGprsParaFromEpsBearer
 功能描述  : 更新GPRS相关参数
 输入参数  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpGprsParaFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 函 数 名  : MN_APS_FindPdpEntByCid
 功能描述  : 根据CID查找PDP索引
 输入参数  : VOS_UINT32                          ucCid
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :
*****************************************************************************/
VOS_UINT8 MN_APS_FindPdpEntByCid(
    VOS_UINT32                          ucCid
);

#endif

/*****************************************************************************
 函 数 名  : TAF_APS_MatchCallWithAttachBearer
 功能描述  : 检查注册承载是否匹配用户拨号参数的承载
 输入参数  : pstCtrl      --- 控制信息
             pstDialParam --- 拨号参数
 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
*****************************************************************************/
VOS_UINT32 TAF_APS_MatchCallWithAttachBearer(
    CONST TAF_CTRL_STRU                *pstCtrl,
    CONST TAF_APS_MATCH_PARAM_STRU     *pstMatchParam
);

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 TAF_APS_IsApnSameWithDefaultBearer(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId
);

VOS_UINT32 TAF_APS_IsStaticIpAddrSameWithDefaultBearer(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucStaticIpAddr,
    VOS_UINT32                         *pulErrCode
);
VOS_UINT32 TAF_APS_FindSutiablePdpForPppDial_LteMode(
    TAF_PPP_DIAL_PARA_STRU             *pstPppDialParaInfo,
    VOS_UINT32                         *pulErrCode
);

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_APS_ProcImsDedicateBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);

VOS_VOID TAF_APS_SndImsaSrvccCancelNotify(
    TAF_SRVCC_CANCEL_NOTIFY_ENUM_UINT32   enNotificationIndicator
);
#endif

#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
