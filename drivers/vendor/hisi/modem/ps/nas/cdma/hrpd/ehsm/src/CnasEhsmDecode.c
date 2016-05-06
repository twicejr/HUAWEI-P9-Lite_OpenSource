/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmDecode.c
 Author          :
 Version         :
 Date            :   14/05/2015
 Description     :EHSM module to deccode.
 Function list   :
 History         :
     1) Date :
        Author:
        Modification:
********************************************************************************/

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmSndPpp.h"
#include "CnasEhsmCtx.h"
#include "CnasEhsmMntn.h"
#include "cnas_cttf_ehrpd_ehsm_ppp_pif.h"
#include "CnasEhsmDecode.h"
#include "CnasEhsmComFunc.h"
#include "CnasEhsmEncode.h"
#include "CnasEhsmDecode.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif
#if 1
#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_DECODE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  3 Function Define
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv4Item
 Description     : 译码PCO信元中的IP项，如P-CSCF IPV4 ADDRESS，P-CSCF IPV6
                   ADDRESS，DNS SERVER IPV4 ADDRESS,DNS SERVER IPV6 ADDRESS
                   等
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv4Item
(
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_IPV4_ADDR_STRU           *pstIpAddr
)
{
    VOS_UINT8                           ucItemLen;
    VOS_UINT32                          ulSum;

    ucItemLen = 0;
    ulSum     = 0;

    /* 记录并跳过IP项长度 */
    ucItemLen = pucMsg[ulSum++];

    if (ucItemLen == CNAS_EHSM_IPV4_ADDR_LEN)
    {
        NAS_MEM_CPY_S(pstIpAddr->aucIpV4Addr,
                      CNAS_EHSM_IPV4_ADDR_LEN,
                      &pucMsg[ulSum],
                      CNAS_EHSM_IPV4_ADDR_LEN);
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodePcoIpv4Item:IP address length is illegal");
        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv6Item
 Description     : 译码PCO信元中的IP项，如P-CSCF IPV6 ADDRESS，DNS SERVER IPV6 ADDRESS
                   等
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv6Item
(
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_IPV6_ADDR_STRU           *pstIpAddr
)
{
    VOS_UINT8                           ucItemLen;
    VOS_UINT32                          ulSum;

    ucItemLen = 0;
    ulSum     = 0;

    /* 记录并跳过IP项长度 */
    ucItemLen = pucMsg[ulSum++];

    if (ucItemLen == CNAS_EHSM_IPV6_ADDR_LEN)
    {
        NAS_MEM_CPY_S(pstIpAddr->aucIpV6Addr,
                      CNAS_EHSM_IPV6_ADDR_LEN,
                      &pucMsg[ulSum],
                      CNAS_EHSM_IPV6_ADDR_LEN);
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodePcoIpv6Item:IP address length is illegal");
        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv6Dns
 Description     : 译码PCO信元中的IPV6 DNS SERVER
                   等
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv6Dns
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_IPV6_ADDR_STRU           *pstEmptyIpv6Addr
)
{
    VOS_UINT32                          ulSum;
    CNAS_EHSM_CAUSE_ENUM_UINT8          enEhsmCause;

    ulSum               = 0;
    enEhsmCause          = CNAS_EHSM_CAUSE_SUCCESS;

    /* DNS SERVER存储已满，则跳过此项 */
    if (pstPco->ucIpv6DnsSerNum >= CNAS_EHSM_MAX_DNS_SERVER_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
        *pulSum = *pulSum + ulSum;
        return CNAS_EHSM_CAUSE_SUCCESS;
    }

    enEhsmCause = CNAS_EHSM_DecodePcoIpv6Item( &pucTmpMsg[ulSum],
                                            &pstPco->astIpv6DnsServer[pstPco->ucIpv6DnsSerNum]);
    if (CNAS_EHSM_CAUSE_SUCCESS == enEhsmCause)
    {
        /* 如果获取的IPv6 DNS内容为全零，代表网侧无此DNS，则不增加DNS数量 */
        if (PS_MEM_CMP(&pstPco->astIpv6DnsServer[pstPco->ucIpv6DnsSerNum],
                            pstEmptyIpv6Addr,
                            sizeof(CNAS_EHSM_IPV6_ADDR_STRU)))
        {
            pstPco->ucIpv6DnsSerNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);

    *pulSum = *pulSum + ulSum;

    return CNAS_EHSM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv4Dns
 Description     : 译码PCO信元中的IPV4 DNS SERVER
                   等
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv4Dns
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_IPV4_ADDR_STRU           *pstEmptyIpv4Addr
)
{
    VOS_UINT32                          ulSum;
    CNAS_EHSM_CAUSE_ENUM_UINT8          enEhsmCause;

    ulSum               = 0;
    enEhsmCause          = CNAS_EHSM_CAUSE_SUCCESS;

    /* DNS SERVER存储已满，则跳过此项 */
    if (pstPco->ucIpv4DnsSerNum >= CNAS_EHSM_MAX_DNS_SERVER_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
        *pulSum += ulSum;
        return CNAS_EHSM_CAUSE_SUCCESS;
    }

    enEhsmCause = CNAS_EHSM_DecodePcoIpv4Item(&pucTmpMsg[ulSum], &pstPco->astIpv4DnsServer[pstPco->ucIpv4DnsSerNum]);
    if (CNAS_EHSM_CAUSE_SUCCESS == enEhsmCause)
    {
        /* 如果获取的IPv4 DNS内容为全零，代表网侧无此DNS，则不增加DNS数量 */
        if (PS_MEM_CMP(&pstPco->astIpv4DnsServer[pstPco->ucIpv4DnsSerNum],
                            pstEmptyIpv4Addr,
                            sizeof(CNAS_EHSM_IPV4_ADDR_STRU)))
        {
            pstPco->ucIpv4DnsSerNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
    *pulSum += ulSum;
    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv4Pcscf
 Description     : 译码PCO信元中的IPV4 P-CSCF
                   等
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv4Pcscf
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_IPV4_ADDR_STRU           *pstEmptyIpv4Addr
)
{
    VOS_UINT32                          ulSum;
    CNAS_EHSM_CAUSE_ENUM_UINT8          enEhsmCause;

    ulSum               = 0;
    enEhsmCause          = CNAS_EHSM_CAUSE_SUCCESS;

    /* P-CSCF存储已满，则跳过此项 */
    if (pstPco->ucIpv4PcscfNum >= CNAS_EHSM_MAX_PCSCF_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
        *pulSum += ulSum;
        return CNAS_EHSM_CAUSE_SUCCESS;
    }

    enEhsmCause = CNAS_EHSM_DecodePcoIpv4Item(&pucTmpMsg[ulSum], &pstPco->astIpv4Pcscf[pstPco->ucIpv4PcscfNum]);
    if (CNAS_EHSM_CAUSE_SUCCESS == enEhsmCause)
    {
        /* 如果获取的IPv4 P-CSCF内容为全零，代表网侧无此P-CSCF，则不增加P-CSCF数量 */
        if (PS_MEM_CMP(&pstPco->astIpv4Pcscf[pstPco->ucIpv4PcscfNum],
                            pstEmptyIpv4Addr,
                            sizeof(CNAS_EHSM_IPV4_ADDR_STRU)))
        {
            pstPco->ucIpv4PcscfNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
    *pulSum += ulSum;
    return CNAS_EHSM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv6Pcscf
 Description     : 译码PCO信元中的IPV6 P-CSCF
                   等
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoIpv6Pcscf
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_IPV6_ADDR_STRU           *pstEmptyIpv6Addr
)
{
    VOS_UINT32                          ulSum;
    CNAS_EHSM_CAUSE_ENUM_UINT8          enEhsmCause;

    ulSum               = 0;
    enEhsmCause          = CNAS_EHSM_CAUSE_SUCCESS;

    /* P-CSCF存储已满，则跳过此项 */
    if (pstPco->ucIpv6PcscfNum >= CNAS_EHSM_MAX_PCSCF_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
        *pulSum += ulSum;
        return CNAS_EHSM_CAUSE_SUCCESS;
    }

    enEhsmCause = CNAS_EHSM_DecodePcoIpv6Item(&pucTmpMsg[ulSum], &pstPco->astIpv6Pcscf[pstPco->ucIpv6PcscfNum]);
    if (CNAS_EHSM_CAUSE_SUCCESS == enEhsmCause)
    {
        /* 如果获取的IPv4 P-CSCF内容为全零，代表网侧无此P-CSCF，则不增加P-CSCF数量 */
        if (PS_MEM_CMP(&pstPco->astIpv6Pcscf[pstPco->ucIpv6PcscfNum],
                            pstEmptyIpv6Addr,
                            sizeof(CNAS_EHSM_IPV6_ADDR_STRU)))
        {
            pstPco->ucIpv6PcscfNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
    *pulSum += ulSum;
    return CNAS_EHSM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoIpv6Pcscf
 Description     : 译码PCO信元中的IPV6 P-CSCF
                   等
 Input           : None
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodeLocalAddress
(
    VOS_UINT8                          *pucTmpMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco,
    VOS_UINT32                         *pulSum
)
{
    VOS_UINT32                          ulSum;

    ulSum               = 0;

    /* 跳过此项内容 */
    ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);

    *pulSum += ulSum;

    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoBcm
 Description     : 译码PCO信元中的BCM
 Input           : pucMsg
 Output          : pstPco
 Return          : VOS_VOID

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
VOS_VOID  CNAS_EHSM_DecodePcoBcm
(
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco
)
{
    VOS_UINT8                           ucItemLen;
    VOS_UINT32                          ulSum;

    ucItemLen = 0;
    ulSum     = 0;

    /* 记录并跳过IP项长度 */
    ucItemLen = pucMsg[ulSum++];

    /* 协议规定BCM的内容长度为1，若不为1，则忽略此项 */
    if (1 != ucItemLen)
    {
        CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodePcoBcm:BCM len illegal!");
        return ;
    }

    /* 协议规定BCM的合法值为SM_ESM_BCM_MS_ONLY和SM_ESM_BCM_MS_NW */

    pstPco->enBcm       = pucMsg[ulSum];
    pstPco->bitOpBcm    = CNAS_EHSM_OP_TRUE;
}


/*****************************************************************************
 Function Name   : CNAS_EHSM_ValidatePcoLen
 Description     : 判断IPCP信元长度的合法性
 Input           : pucMsg       -- 空口消息码流
                   ucIpcpLength -- IPCP结构长度
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数
*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_ValidateIpcpLen
(
     VOS_UINT8                         *pucMsg
)
{
    VOS_UINT8                           ucTmpLength;
    VOS_UINT8                          *pucTmpMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucSum;

    pucTmpMsg           = pucMsg;
    ucTmpLength = 0;
    ucSum     = 0;

    /* 获取总长度 */
    ucTmpLength |= (VOS_UINT8)((pucTmpMsg[2] << 8));
    ucTmpLength |= pucTmpMsg[3];

    /* 判断是否可以读取长度 */
    if (ucTmpLength < (ucSum + CNAS_EHSM_IPCP_PACKET_HEAD_LEN))
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_ValidateIpcpLen:IPCP length is illegal!");

        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    /* 跳过IPCP的头长度 */
    ucSum += CNAS_EHSM_IPCP_PACKET_HEAD_LEN;

    /* 统计所有的长度 */
    while (ucTmpLength > ucSum)
    {
#if 0
        /* 判断是否可以读取长度 */
        if (ucTmpLength < ((ucSum + CNAS_EHSM_IPCP_OPTION_HEAD_LEN) - 1))
        {
            CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_ValidateIpcpLen:IPCP Opt length is illegal!");

            return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
        }
#endif
        /* 判断长度不能为0，避免死循环 */
        if (0 == pucTmpMsg[(ucSum + CNAS_EHSM_IPCP_OPTION_HEAD_LEN) - 1])
        {
            CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_ValidateIpcpLen:IPCP Opt length is 0!");

            return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
        }
        ucSum += pucTmpMsg[(ucSum + CNAS_EHSM_IPCP_OPTION_HEAD_LEN) -1];
    }

    /* 判断总长度是否相等 */
    if (ucTmpLength != ucSum)
    {
        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_CheckIpAddrIsEmpty
 Description     : 检查IP地址是否为空
 Input           :
 Output          : None
 Return          : BOOL

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/

VOS_UINT8 CNAS_EHSM_CheckIpv4AddrIsEmpty( CNAS_EHSM_IPV4_ADDR_STRU *pstIpAddr)
{
    if ( (0 == pstIpAddr->aucIpV4Addr[0])
        && (0 == pstIpAddr->aucIpV4Addr[1])
        && (0 == pstIpAddr->aucIpV4Addr[2])
        && (0 == pstIpAddr->aucIpV4Addr[3]))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}
/*****************************************************************************
 Function Name   : CNAS_EHSM_OptimizeDnsServer
 Description     : 重新组合DNS
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_OptimizeDnsServer
(
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco
)
{
    VOS_UINT8                           ucPriDnsNoExist;
    VOS_UINT8                           ucSecDnsNoExist;

    ucPriDnsNoExist = VOS_TRUE;
    ucSecDnsNoExist = VOS_TRUE;

    ucPriDnsNoExist = CNAS_EHSM_CheckIpv4AddrIsEmpty(&(pstPco->astIpv4DnsServer[0]));
    ucSecDnsNoExist = CNAS_EHSM_CheckIpv4AddrIsEmpty(&(pstPco->astIpv4DnsServer[1]));

    if ((VOS_TRUE == ucPriDnsNoExist) && (VOS_FALSE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 1;
        NAS_MEM_CPY_S((VOS_VOID*)&(pstPco->astIpv4DnsServer[0]),
                      sizeof(CNAS_EHSM_IPV4_ADDR_STRU),
                      (VOS_VOID*)&(pstPco->astIpv4DnsServer[1]),
                      sizeof(CNAS_EHSM_IPV4_ADDR_STRU));
        return;
    }

    if ((VOS_FALSE == ucPriDnsNoExist) && (VOS_TRUE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 1;
        return;
    }

    if ((VOS_TRUE == ucPriDnsNoExist) && (VOS_TRUE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 0;
        return;
    }

    if ((VOS_FALSE == ucPriDnsNoExist) && (VOS_FALSE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 2;
        return;
    }

}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodeIpcpOptionContent
 Description     : 解码IPCP Option内容
 Input           :
 Output          : None
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
      1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8 CNAS_EHSM_DecodeIpcpOptionContent
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                         *pulSum,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco
)
{
     VOS_UINT8                         *pucTmpMsg = VOS_NULL_PTR;
    CNAS_EHSM_CAUSE_ENUM_UINT8          enRslt;
    VOS_UINT32                          ulOptionLen;
    VOS_UINT32                          ulTempSum;

    ulTempSum = *pulSum;
    ulOptionLen = 0;
    pucTmpMsg           = pucMsg;

    CNAS_INFO_LOG1(UEPS_PID_EHSM, "CNAS_EHSM_DecodeIpcpContent:configure-type:", pucMsg[*pulSum]);

    /* 检查当前的可选项总长度正确 */
    enRslt = CNAS_EHSM_ValidateIpcpLen(pucMsg + ulTempSum);
    if (CNAS_EHSM_CAUSE_SUCCESS != enRslt)
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodeIpcpOptionContent:Lenth is illegal!");

        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }


    /*计算该IPCP option长度 */
    ulOptionLen |= (VOS_UINT8)((pucTmpMsg[ulTempSum + 2] << 8));
    ulOptionLen |= pucTmpMsg[ulTempSum + 3];


    /* 跳过头部结构 */
    ulTempSum += CNAS_EHSM_IPCP_PACKET_HEAD_LEN;

    while (ulTempSum < (*pulSum + ulOptionLen))
    {
        switch (pucTmpMsg[ulTempSum])
        {
            /* 译码主DNS Server信息 */
            case CNAS_EHSM_IPCP_OPTIONS_PRI_DNS_ADDR:

                /*跳过type字节*/
                ulTempSum++;

                /* 判断长度是否合法 */
                if (CNAS_EHSM_IPCP_OPTION_DNS_LEN != pucTmpMsg[ulTempSum])
                {
                    CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodeIpcpContent:DNS Lenth is illegal!");
                    *pulSum = ulTempSum;
                    return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
                }

                /*跳过length字节*/
                ulTempSum++;

                NAS_MEM_CPY_S((VOS_VOID*)pstPco->astIpv4DnsServer[0].aucIpV4Addr,
                              CNAS_EHSM_IPV4_ADDR_LEN,
                              (VOS_VOID*)&pucTmpMsg[ulTempSum],
                              CNAS_EHSM_IPV4_ADDR_LEN);


                /* 跳过IP地址 */
                ulTempSum += CNAS_EHSM_IPV4_ADDR_LEN;

                break;


            case CNAS_EHSM_IPCP_OPTIONS_SEC_DNS_ADDR:

                /*跳过type字节*/
                ulTempSum++;

                /* 判断长度是否合法 */
                if (CNAS_EHSM_IPCP_OPTION_DNS_LEN != pucTmpMsg[ulTempSum])
                {
                    CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodeIpcpContent:DNS Lenth is illegal!");
                    *pulSum = ulTempSum;
                    return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
                }

                /*跳过length字节*/
                ulTempSum++;

                NAS_MEM_CPY_S((VOS_VOID*)pstPco->astIpv4DnsServer[1].aucIpV4Addr,
                              CNAS_EHSM_IPV4_ADDR_LEN,
                              (VOS_VOID*)&pucTmpMsg[ulTempSum],
                              CNAS_EHSM_IPV4_ADDR_LEN);


                /* 跳过IP地址 */
                ulTempSum += CNAS_EHSM_IPV4_ADDR_LEN;

                break;

            default:
                /* 判断长度不能为0，避免死循环 */
                if (0 == pucTmpMsg[ulTempSum + 1])
                {
                    *pulSum = ulTempSum;
                    return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
                }

                /* 跳过信元长度 */
                ulTempSum += pucTmpMsg[ulTempSum + 1];

                break;
        }
    }
    *pulSum = ulTempSum;
    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodeIpcpContent
 Description     : 译码IPCP的码流
IPCP
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|     Code      |  Identifier   |            Length             |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Options ...
+-+-+-+-+

IP:
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |     Type      |    Length     |           IP-Address
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         IP-Address (cont)       |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

DNS Server Address
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |     Type      |    Length     |      Primary-NBNS-Address
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    Primary-NBNS-Address (cont)  |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

NBNS Server Address
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |     Type      |    Length     |      Secondary-NBNS-Address
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   Secondary-NBNS-Address (cont) |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodeIpcpContent
(
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco
)
{
    CNAS_EHSM_CAUSE_ENUM_UINT8          enRslt;
    VOS_UINT8                           ucTmpLength;
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pucTmpMsg = VOS_NULL_PTR;

    enRslt              = CNAS_EHSM_CAUSE_ERROR;
    ucTmpLength         = 0;
    ulSum               = 0;
    pucTmpMsg           = pucMsg;

    /* 获取length项 */
    ucTmpLength = pucTmpMsg[ulSum++];

#if 0
    /* 判断类型是否为CONFIGURE_NAK,为增强网络兼容性,可解码NAK/ACK/REJ/REQ*/
    if(pucTmpMsg[ulSum] != CNAS_EHSM_IPCP_MSG_TYPE_CONFIGURE_NAK)
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodeIpcpContent:code is illegal!");
    }
#endif

    /* 判断总长度是否合法 */
    if (ucTmpLength < CNAS_EHSM_IPCP_PACKET_HEAD_LEN)
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodeIpcpContent:IPCP length is illegal!");

        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    while (ucTmpLength > (ulSum -1))
    {
        enRslt = CNAS_EHSM_DecodeIpcpOptionContent(pucTmpMsg, &ulSum, pstPco);
        if (CNAS_EHSM_CAUSE_SUCCESS != enRslt)
        {
            return enRslt;
        }
    }

    return CNAS_EHSM_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : CNAS_EHSM_ValidatePcoLen
 Description     : 判断PCO信元长度的合法性
 Input           : pucMsg      -- 空口消息码流
                   ucPcoLength -- PCO结构长度
 Output          : usDecodeLen -- 要解码的长度
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_ValidatePcoLen
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT8                           ucPcoLength,
    VOS_UINT16                         *pusDecodeLen
)
{
    VOS_UINT8                           ucAllPcoLength;
    VOS_UINT8                           ucPrePcoLength;
    VOS_UINT8                          *pTmp = VOS_NULL_PTR;
    VOS_UINT8                          *pucTemp = VOS_NULL_PTR;

    ucAllPcoLength  = 0;
    ucPrePcoLength  = 0;
    pTmp            = pucMsg;
    pucTemp         = VOS_NULL_PTR;
    /* 如果PCO长度为0，则返回失败 */
    if (0 == ucPcoLength)
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_ValidatePcoLen:Pco length is 0!");
        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    /* 如果PCO信元只包含配置协议项，则返回成功 */
    if (CNAS_EHSM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL == ucPcoLength)
    {
        *pusDecodeLen = CNAS_EHSM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL;
        return CNAS_EHSM_CAUSE_SUCCESS;
    }

    /* 判断长度是否合法 */
    if(ucPcoLength < (CNAS_EHSM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL + CNAS_EHSM_SUM_LEN_OF_ID_LEN))
    {
         CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_ValidatePcoLen:Pco length is between (1,4)!");
         return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    pucTemp = &(pTmp[CNAS_EHSM_PCO_ITEM_LEN_OFFSET]);

    /* 获取所有packet filter所占总字节数 */
    ucPrePcoLength = pTmp[CNAS_EHSM_PCO_ITEM_LEN_OFFSET];
    ucAllPcoLength = ucPrePcoLength + (CNAS_EHSM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL
                                                    + CNAS_EHSM_SUM_LEN_OF_ID_LEN);
    /*到此处可认为可解析的长度为1，即仅包含CONFIGURATION PROTOCOL*/
    *pusDecodeLen = CNAS_EHSM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL;

    while (ucPcoLength >= ucAllPcoLength)
    {
         *pusDecodeLen = ucAllPcoLength;
         /* 判断长度是否合法 */
         if ((ucAllPcoLength + CNAS_EHSM_SUM_LEN_OF_ID_LEN) > ucPcoLength)
         {
             break;
         }

         /* 累加下一项的长度 */
         ucAllPcoLength =   ucAllPcoLength +
                            pucTemp[ucPrePcoLength + CNAS_EHSM_SUM_LEN_OF_ID_LEN]
                            + CNAS_EHSM_SUM_LEN_OF_ID_LEN;

         /* 将指针指到下一项的长度信元的位置 */
         pucTemp = &(pucTemp[ucPrePcoLength + CNAS_EHSM_SUM_LEN_OF_ID_LEN]);

         /* 保存下一项的长度信元的值 */
         ucPrePcoLength = *pucTemp;
    }

    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodePcoContent
 Description     : 译码PCO内容
 Input           : pucMsg---------------------空口消息码流
                   pstMsgIE-------------------译码后的空口消息
 Output          : pulIndex-------------------此函数译码的消息长度指针
 Return          : CNAS_EHSM_CAUSE_ENUM_UINT8

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePcoContent
(
    VOS_UINT16                          usMsgLen,
     VOS_UINT8                         *pucMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstMsgIE
)
{
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pucTmpMsg = VOS_NULL_PTR;
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstPco = VOS_NULL_PTR;
    VOS_UINT16                          usPcoItemId;
    CNAS_EHSM_IPV6_ADDR_STRU            stEmptyIpv6Addr;
    CNAS_EHSM_IPV4_ADDR_STRU            stEmptyIpv4Addr;

    ulSum               = 0;
    pucTmpMsg           = pucMsg;
    pstPco              = pstMsgIE;
    usPcoItemId         = 0;

    NAS_MEM_SET_S(&stEmptyIpv6Addr, sizeof(CNAS_EHSM_IPV6_ADDR_STRU), 0, sizeof(CNAS_EHSM_IPV6_ADDR_STRU));
    NAS_MEM_SET_S(&stEmptyIpv4Addr, sizeof(CNAS_EHSM_IPV4_ADDR_STRU), 0, sizeof(CNAS_EHSM_IPV4_ADDR_STRU));
    /* 如果PCO功能已关闭，则直接跳过PCO内容并返回成功 */
#if 0
    if (CNAS_EHSM_PCO_OFF  == CNAS_EHSM_GetPcoFlag())
    {
        CNAS_EHSM_NORM_LOG("CNAS_EHSM_DecodePcoContent:PCO fuction is closed!");

        return CNAS_EHSM_SUCCESS;
    }
#endif
    /* 判断PCO携带的协议是否正确 */
    if (CNAS_EHSM_PCO_CONFIG_PROTOCOL != (pucTmpMsg[ulSum++] & CNAS_EHSM_HIGH_5_BIT_MASK))
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodePcoContent:Pco Configaration Proctocol error!");
        return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    /* 逐一译码PCO所携带的各项内容 */
    while (usMsgLen > ulSum)
    {
        usPcoItemId = ((VOS_UINT16)pucTmpMsg[ulSum++] << CNAS_EHSM_MOVEMENT_8_BITS);
        usPcoItemId = usPcoItemId | (pucTmpMsg[ulSum++]);

        switch (usPcoItemId)
        {
            case CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV6:
                CNAS_EHSM_DecodePcoIpv6Dns(&pucTmpMsg[ulSum],
                                                    pstPco,
                                                    &ulSum,
                                                    &stEmptyIpv6Addr);
                break;
            case CNAS_EHSM_PCO_ITEM_TYPE_PCSCF_IPV4:

                CNAS_EHSM_DecodePcoIpv4Pcscf(&pucTmpMsg[ulSum],
                                                        pstPco,
                                                        &ulSum,
                                                        &stEmptyIpv4Addr);
                break;
            case CNAS_EHSM_PCO_ITEM_TYPE_BCM:
                CNAS_EHSM_DecodePcoBcm(&pucTmpMsg[ulSum], pstPco);
                ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
                break;

            case CNAS_EHSM_PCO_ITEM_TYPE_DNS_SERVER_IPV4:

                CNAS_EHSM_DecodePcoIpv4Dns(&pucTmpMsg[ulSum],
                                                        pstPco,
                                                        &ulSum,
                                                        &stEmptyIpv4Addr);
                break;

            case CNAS_EHSM_PCO_ITEM_TYPE_IPCP:
                /*LV格式译码*/
                (VOS_VOID)CNAS_EHSM_DecodeIpcpContent(&pucTmpMsg[ulSum],pstPco);
                ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
                break;

            case CNAS_EHSM_PCO_ITEM_TYPE_PCSCF_IPV6:

                CNAS_EHSM_DecodePcoIpv6Pcscf(&pucTmpMsg[ulSum],
                                                        pstPco,
                                                        &ulSum,
                                                        &stEmptyIpv6Addr);
                break;

            case CNAS_EHSM_PCO_ITEM_TYPE_IM_CN_SIGNAL_FLAG:
                pstPco->bitOpImsCnSignalFlag = CNAS_EHSM_OP_TRUE;
                ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
                break;

            case CNAS_EHSM_PCO_ITEM_TYPE_LOCAL_ADDRESS:
                (VOS_VOID)CNAS_EHSM_DecodeLocalAddress(&pucTmpMsg[ulSum],
                                                    pstPco,
                                                    &ulSum);
                break;

            default:
                /* 跳过此项内容 */
                ulSum += (pucTmpMsg[ulSum] + CNAS_EHSM_LEN_IE_OCTETS);
                break;
        }
    }
    /*重新调整DNS */
    CNAS_EHSM_OptimizeDnsServer(pstPco);

    return CNAS_EHSM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name  : CNAS_EHSM_DecodePco()
 Description    : SM模块解析PCO信息
 Input          :

 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
/*lint -e415 -e416 -e661 -e662*/
CNAS_EHSM_CAUSE_ENUM_UINT8  CNAS_EHSM_DecodePco
(
    VOS_UINT16                          usMsgLen,
     VOS_UINT8                         *pucMsg,
    CNAS_EHSM_CONTEXT_PCO_STRU         *pstMsgIE
)
{
    CNAS_EHSM_CAUSE_ENUM_UINT8          enEhsmCause;
    VOS_UINT16                          usDecodeLen;

    enEhsmCause          = CNAS_EHSM_CAUSE_SUCCESS;
    /*打印进入该函数*/
    CNAS_INFO_LOG(UEPS_PID_EHSM,   "CNAS_EHSM_DecodePco is entered");

    enEhsmCause = CNAS_EHSM_ValidatePcoLen(pucMsg,(VOS_UINT8)usMsgLen,&usDecodeLen);
    if (CNAS_EHSM_CAUSE_SUCCESS != enEhsmCause)
    {
        /*返回消息检测失败*/
        CNAS_INFO_LOG(UEPS_PID_EHSM,  "CNAS_EHSM_DecodeNwPco:CNAS_EHSM_ValidatePcoLen failed!");
        return enEhsmCause;
    }

    enEhsmCause = CNAS_EHSM_DecodePcoContent(usDecodeLen, pucMsg, pstMsgIE);
    if (CNAS_EHSM_CAUSE_SUCCESS != enEhsmCause)
    {
        return enEhsmCause;
    }


    return CNAS_EHSM_CAUSE_SUCCESS;
}/*lint +e415 +e416 +e661 +e662*/

/*****************************************************************************
 Function Name   : CNAS_EHSM_DecodeNwPDNValue
 Description     : PDN地址解码
 Input           :VOS_UINT16             usMsgLen
                VOS_UINT8             *pucMsg
                CNAS_EHSM_NW_MSG_STRU   *pstMsgIE
 Output          : None
 Return          : VOS_UINT32

 History         :
  1.日    期    : 2015年6月8日
    作    者    : f00279542
    修改内容    : 新生成函数

*****************************************************************************/
CNAS_EHSM_CAUSE_ENUM_UINT8 CNAS_EHSM_DecodeNwPDNValue
(
    VOS_UINT16                          usMsgLen,
    VOS_UINT8                          *pucMsg,
    CNAS_EHSM_PDN_ADDR_STRU            *pstMsgIE
)
{
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pucTmpMsg;
    CNAS_EHSM_PDN_ADDR_STRU            *pstPDNInfo;

    ulSum            = 0;
    pucTmpMsg        = pucMsg;
    pstPDNInfo       = pstMsgIE;

    /*判断PDN ADDRESS内容长度是否符合协议规范，目前只考虑IPV4的地址*/

    /*内存空间初始化*/
    NAS_MEM_SET_S((VOS_VOID*)pstPDNInfo, sizeof(CNAS_EHSM_PDN_ADDR_STRU), 0, sizeof(CNAS_EHSM_PDN_ADDR_STRU));

    /*保存PDN地址内型*/
    pstPDNInfo->enPdnType = pucTmpMsg[ulSum++];

    /* jump three pad */
    ulSum += 3;

    switch(pstPDNInfo->enPdnType)
    {
        /*如果是IPV4内型地址，则保存，IPV4地址有4个字节*/
        case CNAS_EHSM_PDN_TYPE_IPV4:
            NAS_MEM_CPY_S(pstPDNInfo->aucIpv4Addr, CNAS_EHSM_IPV4_ADDR_LEN, &pucTmpMsg[ulSum], CNAS_EHSM_IPV4_ADDR_LEN);
            break;

        /*如果是IPV6内型地址，则保存，IPV4地址有16个字节,保留*/
        case CNAS_EHSM_PDN_TYPE_IPV6:
            /*存放IPV6格式的地址*/
            NAS_MEM_CPY_S((pstPDNInfo->aucIpv6Addr + CNAS_EHSM_IPV6_IF_OFFSET),  
                          (CNAS_EHSM_IPV6_ADDR_LEN - CNAS_EHSM_IPV6_IF_OFFSET),
                          &pucTmpMsg[ulSum], 
                          CNAS_EHSM_IPV6_IF_LEN);
            break;

        /*如果支持IPV4和IPV6地址，按位保存，保留*/
        case CNAS_EHSM_PDN_TYPE_IPV4V6:
            /*依次存放IPV4和IPV6地址*/
            NAS_MEM_CPY_S((pstPDNInfo->aucIpv6Addr + CNAS_EHSM_IPV6_IF_OFFSET),
                          (CNAS_EHSM_IPV6_ADDR_LEN - CNAS_EHSM_IPV6_IF_OFFSET),
                          &pucTmpMsg[ulSum], 
                          CNAS_EHSM_IPV6_IF_LEN);
            NAS_MEM_CPY_S(pstPDNInfo->aucIpv4Addr, CNAS_EHSM_IPV4_ADDR_LEN, &pucTmpMsg[ulSum+CNAS_EHSM_IPV6_IF_LEN], CNAS_EHSM_IPV4_ADDR_LEN);

            break;
        default:
            CNAS_WARNING_LOG(UEPS_PID_EHSM, "CNAS_EHSM_DecodeEsmPDN:WARNING:NW->SM Invalid mandatory information1!");
            NAS_MEM_SET_S((VOS_VOID*)pstPDNInfo, sizeof(CNAS_EHSM_PDN_ADDR_STRU), 0, sizeof(CNAS_EHSM_PDN_ADDR_STRU));
            return CNAS_EHSM_CAUSE_PROTOCOL_ERROR;
    }

    return CNAS_EHSM_CAUSE_SUCCESS;
}
/*lint -restore*/

#endif /* FEATURE_UE_MODE_CDMA */
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



