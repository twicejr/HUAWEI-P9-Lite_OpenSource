/*************************************************************************************
*
*                       dhcpv6c_pkt.c
*
*  项目代码：           UGW9811 V900R010C00
*  创建日期：           2012-06-28
*  作者：               y00170683
*  修改历史列表：
*  参考文档：
*  功能：               DHCPV6C模块编解码处理
*  其他：
*
*-----------------------------------------------------------------------------------
*
*  Copyright  Beijing Institute HuaWei Tech, Inc.
*                     ALL RIGHTS RESERVED
*
*************************************************************************************/

#ifdef    __cplusplus
extern "C" {
#endif

/********************************************************************************/
/******************                  头文件引用               *******************/
/********************************************************************************/
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc.h"
#include "dhcpc_table.h"
#include "dhcpv6_def.h"
#include "dhcpv6c_pkt.h"
#include "dhcpv6c_fsm.h"
#include "dhcpc_var.h"
#include "dhcpc_comp.h"
#include "dhcpc_dbg.h"
#include "TtfDrvInterface.h"
#include "TTFMemInterface.h"
#include "cds_trans_data_pif.h"


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV6C_PKT_C
/*lint +e767*/



/********************************************************************************/
/******************                  全局变量                 *******************/
/********************************************************************************/
UCHAR* g_pucDhcpv6cSendBuff = VOS_NULL;        /*发送消息缓存*/

USHORT g_usDhcpv6cMaxSeqNum = DHCPV6C_MAX_SEQUENCE_NUM_DE; /* SequencNum规格,DE512,F1024*/
DHCPV6C_SEQNUM_FREELINK_S g_stDhcpv6cSeqNumLink = {0}; /* SequencNum后向空闲链 */
DHCPV6C_SEQNUM_CONTEXT_S *g_pstDhcpv6cSeqContext = NULL; /*  SequenceNum与DHCP控制块对应关系 */

/********************************************************************************/
/******************                  宏定义                 *******************/
/********************************************************************************/

/********************************************************************************/
/******************                  内部接口                 *******************/
/********************************************************************************/

#define _MESSAGE_CHECK_
/*****************************************************************************
 Prototype    : DHCPV6C_IPv6ValidCheck
 Description  : IPv6地址合法性检测
 Input        : in6_addr* stAddr
 Output       : None
 Return Value :
 Calls        :
 Called By    :

*****************************************************************************/
ULONG DHCPV6C_IPv6ValidCheck(in6_addr* pstAddr)
{
    USHORT ustype = 0;
    ULONG ulGlobalAddr = VOS_HTONL(0x20000000);   /* "可聚集全局单播地址"的二进制前缀为001 */
    ULONG ulSiteLocalAddr = VOS_HTONL(0xFEC00000);/* "网点本地单播地址"的二进制前缀为1111 1110 11 */
    ULONG ulIpAddr = pstAddr->s6_addr32[0];
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter, pstAddr = %08x;%08x;%08x;%08x",
        pstAddr->s6_addr32[0], pstAddr->s6_addr32[1],
        pstAddr->s6_addr32[2], pstAddr->s6_addr32[3]);

    ustype = LAP_IPv6GetAddrType(pstAddr);
    /*暂时只支持SITE- local address，可以考虑以后再扩展*/
    if ((ustype & IPV6_ADDR_UNICAST)&&
         ((ustype & IPV6_ADDR_SITELOCAL)||(ustype & IPV6_ADDR_GLOBAL))) /* 支持 global */
    {
        if (((ulIpAddr & VOS_HTONL(0xE0000000)) != ulGlobalAddr)
            && ((ulIpAddr & VOS_HTONL(0xFFC00000)) != ulSiteLocalAddr))
        {
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "addr not ulGlobalAddr and ulSiteLocalAddr!");
            return VOS_ERR;
        }
        return VOS_OK;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "err-type = %u!", ustype);
    return VOS_ERR;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_CheckCiDuidData
 *  初稿完成:       2012-07-09
 *  作    者:       y00170683
 *  函数功能:       检查CiDuidData
 *  输入参数:       UCHAR *pucData,DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_CheckCiDuidData(UCHAR *pucData,
                                          DHCPC_CTRLBLK *pstDhcpcContext)
{
    LONG lRet = 0;

    /* 优先使用MSISDN，其次使用IMSI，再次使用IMEI */
    if((VOS_NULL_DWORD != pstDhcpcContext->aulMSISDN[0])
        || (VOS_NULL_DWORD != pstDhcpcContext->aulMSISDN[1]))
    {
        lRet = VOS_MemCmp(pstDhcpcContext->aulMSISDN, pucData, DHCP_MAX_MSISDN_LEN);
    }
    else if ((VOS_NULL_DWORD != pstDhcpcContext->aulIMSI[0])
        || (VOS_NULL_DWORD != pstDhcpcContext->aulIMSI[1]))
    {
        lRet = VOS_MemCmp(pstDhcpcContext->aulIMSI, pucData, DHCP_MAX_MSISDN_LEN);
    }
    else if ((VOS_NULL_DWORD != pstDhcpcContext->aulIMEI[0])
        || (VOS_NULL_DWORD != pstDhcpcContext->aulIMEI[1]))
    {
        lRet = VOS_MemCmp(pstDhcpcContext->aulIMEI, pucData, DHCP_MAX_MSISDN_LEN);
    }
    if (0 != lRet)
    {
        return VOS_ERR;
    }
    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_CheckClientIdOption
 *  初稿完成:       2012-07-09
 *  作    者:       y00170683
 *  函数功能:       检查ClientId的合法性
 *  输入参数:       DHCPV6C_TLV_OPTION_S *pstClientIdOption,
                    DHCPV6C_DUID_EN_OPTION_S *pstDuidEn,
                    DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_CheckClientIdOption(DHCPV6C_TLV_OPTION_S *pstClientIdOption,
                                                DHCPV6C_DUID_EN_OPTION_S *pstDuidEn,
                                                DHCPC_CTRLBLK *pstDhcpcContext)
{
    USHORT usDuidLen = 0;
    ULONG ulRet = VOS_OK;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    /* 没有携带ClientId */
    if (VOS_NULL == pstClientIdOption)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_NO_CI);
        return VOS_ERR;
    }

    /* deleted by t00265288 start 参照的码流里面没有带DUID-en，所以把这个check注释掉 */
#if 0
    /* 没有携带DUID-EN类型的DUID */
    if (VOS_NULL == pstDuidEn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CIDUID_TYPE_ERR);
        return VOS_ERR;
    }

    /* EnterpriseNum 不是华为2011 */
    if (DHCPV6_HUAWEI_ENTERPRISENUM != pstDuidEn->ulEnterpriseNum)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CIDUID_ENTERNUM_ERR);
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:ulEnterpriseNum = %u", pstDuidEn->ulEnterpriseNum);
        return VOS_ERR;
    }

    /* 长度必须是8字节 */
    usDuidLen = pstClientIdOption->usLen - sizeof(DHCPV6C_DUID_EN_OPTION_S);
    if (DHCP_MAX_MSISDN_LEN != usDuidLen)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CIDUID_LEN_ERR);
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:usDuidLen = %u", usDuidLen);
        return VOS_ERR;
    }

    /* 与控制块进行一致性检查 */
    ulRet = DHCPV6C_CheckCiDuidData(pstDuidEn->ucData, pstDhcpcContext);
    if (VOS_OK != ulRet)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CIDUID_DATA_ERR);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "[dhcpv6c-err]:DHCPV6C_CheckCiDuidData fail");
        return DHCPC_RET_DROP_MSG;
    }
#endif

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_CheckSiDuidTypeLen
 *  初稿完成:       2012-07-09
 *  作    者:       y00170683
 *  函数功能:       检查CiDuidData
 *  输入参数:       UCHAR *pucData,DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_CheckSiDuidTypeLen(USHORT usType, USHORT usLen)
{
    ULONG ulRet = VOS_OK;

    switch (usType)
    {
        case DHCPV6_MSG_OPTION_DUID_LLT :
            if (usLen <= sizeof(DHCPV6C_DUID_LLT_OPTION_S))
            {
                ulRet = VOS_ERR;
            }
            break;

        case DHCPV6_MSG_OPTION_DUID_EN :
            if (usLen <= sizeof(DHCPV6C_DUID_EN_OPTION_S))
            {
                ulRet = VOS_ERR;
            }
            break;

        case DHCPV6_MSG_OPTION_DUID_LL :
            if (usLen <= sizeof(DHCPV6C_DUID_LL_OPTION_S))
            {
                ulRet = VOS_ERR;
            }
            break;

        default:
            ulRet = VOS_ERR;
            break;
    }
    return ulRet;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_CheckServerIdOption
 *  初稿完成:       2012-07-09
 *  作    者:       y00170683
 *  函数功能:       检查ServerId的合法性
 *  输入参数:       DHCPV6C_TLV_OPTION_S *pstServerIdOption, DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_CheckServerIdOption(DHCPV6C_TLV_OPTION_S *pstServerIdOption,
                                                DHCPC_CTRLBLK *pstDhcpcContext)
{
    LONG lRet = 0;
    USHORT usSiLen = 0;
    UCHAR aucSiDuid[DHCPV6C_MAX_DUID_LEN] = {0};
    DHCPV6C_DUID_EN_OPTION_S *pstDuidEn = VOS_NULL;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    /* 没有携带ServerId */
    if (VOS_NULL == pstServerIdOption)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_NO_SI);
        return VOS_ERR;
    }

    /* 没有携带DUID,大于14字节按照没有携带处理 */
    usSiLen = pstServerIdOption->usLen;
    if ((0 == usSiLen)
        || (DHCPV6C_MAX_DUID_LEN < usSiLen))
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SIDUID_LEN_ERR);
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:usLen = %u", usSiLen);
        return VOS_ERR;
    }

    /* DUID-type,len 不正确 */
    pstDuidEn = (DHCPV6C_DUID_EN_OPTION_S *)pstServerIdOption->ucData;
    if (VOS_OK != DHCPV6C_CheckSiDuidTypeLen(VOS_NTOHS(pstDuidEn->usType), usSiLen))
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SIDUID_TYPE_ERR);
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:usType = %u, usLen = %u",
                           VOS_NTOHS(pstDuidEn->usType), usSiLen);
        return VOS_ERR;
    }

    /* 控制块中没有ServerId,直接返回成功 */
    lRet = VOS_MemCmp(pstDhcpcContext->aucSiDuid, aucSiDuid, DHCPV6C_MAX_DUID_LEN);
    if (0 == lRet)
    {
        return VOS_OK;
    }

    /* 与控制块进行一致性检查 */
    lRet = VOS_MemCmp(pstDhcpcContext->aucSiDuid, pstDuidEn, usSiLen);
    if (0 != lRet)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SIDUID_DATA_ERR);
        return DHCPC_RET_DROP_MSG;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_CheckIaNaOption
 *  初稿完成:       2012-07-09
 *  作    者:       y00170683
 *  函数功能:       检查IaNa的合法性
 *  输入参数:       DHCPV6C_IANA_OPTION_S *pstIaNaOption, DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_CheckIaNaOption(DHCPV6C_IANA_OPTION_S *pstIaNaOption,
                                           DHCPC_CTRLBLK *pstDhcpcContext)
{
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    /* 没有携带IaNa */
    if (VOS_NULL == pstIaNaOption)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_NO_IANA);
        return VOS_ERR;
    }

    /* 长度不正确 */
    if (pstIaNaOption->usLen < sizeof(DHCPV6C_IANA_OPTION_S) - DHCPV6_OPT_HEADER_LEN)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_IANA_LEN_ERR);
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:usLen = %u", pstIaNaOption->usLen);
        return VOS_ERR;
    }

    /* teidc不一致 */
    if (pstIaNaOption->ulId != pstDhcpcContext->ulTEIDC)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_IANA_TEIDC_ERR);
        return VOS_ERR;
    }

    /* T1>T2. T1和T2中如果有为0的,其合法性需要在状态机预处理中再检查 */
    if ((pstIaNaOption->ulT1 > pstIaNaOption->ulT2)
        && (0 != pstIaNaOption->ulT1)
        && (0 != pstIaNaOption->ulT2))
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_IANA_T1T2_ERR);
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:ulT1(%u) > ulT2(%u)",
            pstIaNaOption->ulT1, pstIaNaOption->ulT2);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_CheckIaAddrOption
 *  初稿完成:       2012-07-09
 *  作    者:       y00170683
 *  函数功能:       检查IaAddr的合法性
 *  输入参数:       DHCPV6C_IAADDR_OPTION_S *pstIaAddrOption, DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_CheckIaAddrOption(DHCPV6C_IAADDR_OPTION_S *pstIaAddrOption,
                                              DHCPC_CTRLBLK *pstDhcpcContext)
{
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    /* 没有携带IaAddr */
    if (VOS_NULL == pstIaAddrOption)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_NO_IAADDR);
        return VOS_ERR;
    }

    /* 长度不正确 */
    if (pstIaAddrOption->usLen < sizeof(DHCPV6C_IAADDR_OPTION_S) - DHCPV6_OPT_HEADER_LEN)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_IAADDR_LEN_ERR);
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:usLen = %u", pstIaAddrOption->usLen);
        return VOS_ERR;
    }

    /* 合法性检查 */
    if (VOS_OK != DHCPV6C_IPv6ValidCheck(&(pstIaAddrOption->stIpv6Addr)))
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_IAADDR_DATA_ERR);
        return VOS_ERR;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_CheckDnsOption
 *  初稿完成:       2012-07-28
 *  作    者:       y00170683
 *  函数功能:       检查DNS的合法性
 *  输入参数:       DHCPV6C_TLV_OPTION_S *pstDnsOption
 *  输出参数:       UCHAR *pucMainDnsFlg, UCHAR *pucSecdDnsFlg
 *  返回类型:       VOID
 *  其他说明:       CR20120726042 DNS-option只取最后一个的前两个地址作为主备DNS
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_CheckDnsOption(DHCPV6C_TLV_OPTION_S *pstDnsOption,
                                          UCHAR *pucMainDnsFlg, UCHAR *pucSecdDnsFlg)
{
    LONG lRet = 0;
    in6_addr stMainDnsAddr;
    in6_addr stSecdDnsAddr;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");
    DHCP_MemZero(&stMainDnsAddr, sizeof(in6_addr));
    DHCP_MemZero(&stSecdDnsAddr, sizeof(in6_addr));

    if ((NULL == pucMainDnsFlg) || (NULL == pucSecdDnsFlg))
    {
        return;
    }

    /* 没有携带DNS */
    if (VOS_NULL == pstDnsOption)
    {
        *pucMainDnsFlg = VOS_FALSE;
        *pucSecdDnsFlg = VOS_FALSE;
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_NO_DNS);
        return;
    }

    /* DNS长度不合法 */
    if ((0 == pstDnsOption->usLen)
        || (0 != (pstDnsOption->usLen) % (sizeof(in6_addr))))
    {
        *pucMainDnsFlg = VOS_FALSE;
        *pucSecdDnsFlg = VOS_FALSE;
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_DNS_LEN_ERR);
        return;
    }

    /* 合法性检查 */
    if (VOS_TRUE == *pucMainDnsFlg)
    {
        VOS_MemCpy(&stMainDnsAddr, pstDnsOption->ucData, sizeof(in6_addr));
        if (VOS_OK != DHCPV6C_IPv6ValidCheck(&stMainDnsAddr))
        {
            *pucMainDnsFlg = VOS_FALSE;
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_DNS_MAIN_ERR);
        }

    }
    if (VOS_TRUE == *pucSecdDnsFlg)
    {
        VOS_MemCpy(&stSecdDnsAddr, pstDnsOption->ucData + sizeof(in6_addr), sizeof(in6_addr));
        if (VOS_OK != DHCPV6C_IPv6ValidCheck(&stSecdDnsAddr))
        {
            *pucSecdDnsFlg = VOS_FALSE;
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_DNS_SECD_ERR);
        }
    }

    /* 主备都合法时需要检查一致性,如果一致则认为只携带了主----DTS2012080906701 y00170683 */
    if ((VOS_TRUE == *pucMainDnsFlg) && (VOS_TRUE == *pucSecdDnsFlg))
    {
        lRet = VOS_MemCmp(&stMainDnsAddr, &stSecdDnsAddr, sizeof(in6_addr));
        if (0 == lRet)
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_DNS_SAME);
            *pucSecdDnsFlg = VOS_FALSE;
        }
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_CheckOption
 *  初稿完成:       2012-07-11
 *  作    者:       y00170683
 *  函数功能:       检查DHCPV6C-OPTION
 *  输入参数:       DHCPV6C_OPTION_INFO_S *pstDhcpv6cOptionInfo
                    DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_CheckOption(DHCPV6C_OPTION_INFO_S *pstDhcpv6cOptionInfo,
                                      DHCPC_CTRLBLK *pstDhcpcContext)
{
    ULONG ulRet = VOS_OK;

    /* 检查clientId */
    ulRet = DHCPV6C_CheckClientIdOption(pstDhcpv6cOptionInfo->pstClientIdOption,
                                           pstDhcpv6cOptionInfo->pstCiDuidEn,
                                           pstDhcpcContext);
    if (VOS_OK != ulRet)
    {
        return ulRet;
    }

    /* 检查serverId */
    ulRet = DHCPV6C_CheckServerIdOption(pstDhcpv6cOptionInfo->pstServerIdOption,
                                           pstDhcpcContext);
    if (VOS_OK != ulRet)
    {
        return ulRet;
    }

    /* deleted by t00265288 start 参照的码流里面没有带IaNa，所以把这个check注释掉 */
#if 0
    /* 检查IaNa */
    ulRet = DHCPV6C_CheckIaNaOption(pstDhcpv6cOptionInfo->pstIaNaOption,
                                       pstDhcpcContext);
    if (VOS_OK != ulRet)
    {
        return ulRet;
    }

    /* 检查IaAddr */
    ulRet = DHCPV6C_CheckIaAddrOption(pstDhcpv6cOptionInfo->pstIaAddrOption,
                                         pstDhcpcContext);
    if (VOS_OK != ulRet)
    {
        return ulRet;
    }
#endif

    /* 检查DNS */
    DHCPV6C_CheckDnsOption(pstDhcpv6cOptionInfo->pstDnsOption,
                              &(pstDhcpv6cOptionInfo->ucMainDnsFlg),
                              &(pstDhcpv6cOptionInfo->ucSecdDnsFlg));

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return VOS_OK;
}

#define _MESSAGE_DECODE_
/*****************************************************************************
 *  函数名称:       DHCPV6C_SaveOptionToContext
 *  初稿完成:       2012-07-12
 *  作    者:       y00170683
 *  函数功能:       保存消息内容至控制块
 *  输入参数:       DHCPV6C_OPTION_INFO_S *pstDhcpv6Option
 *  输出参数:       DHCPC_CTRLBLK *pstDhcpcContext
 *  返回类型:       VOID
 *  其他说明:       CR20120726042 DNS-option只取最后一个的前两个地址作为主备DNS
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_SaveDnsOptionToContext(DHCPC_CTRLBLK *pstDhcpcContext,
                                                     DHCPV6C_TLV_OPTION_S *pstDnsOption,
                                                     UCHAR ucMainDnsFlg,
                                                     UCHAR ucSecdDnsFlg)
{
    /* 保存DNS 以reply为准,因此DNS需要实时刷新 --DTS2012072307085 DNS无效值是全F y00170683 */
    /* 没有携带或者都非法时清空控制块内容 */
    if ((VOS_FALSE == ucMainDnsFlg) && (VOS_FALSE == ucSecdDnsFlg))
    {
        DHCPV6C_SET_V6ADDR_NULL(pstDhcpcContext->aulMainDnsAddr);
        DHCPV6C_SET_V6ADDR_NULL(pstDhcpcContext->aulSecdDnsAddr);
    }
    /* 主DNS是空时,将备DNS保存为主 --- 如果主无效,备有效,将备更新为主 */
    else if(VOS_FALSE == ucMainDnsFlg)
    {
        VOS_MemCpy(pstDhcpcContext->aulMainDnsAddr,
            pstDnsOption->ucData + sizeof(in6_addr), sizeof(in6_addr));
        DHCPV6C_SET_V6ADDR_NULL(pstDhcpcContext->aulSecdDnsAddr);
    }
    /* 备DNS是空时*/
    else if(VOS_FALSE == ucSecdDnsFlg)
    {
        VOS_MemCpy(pstDhcpcContext->aulMainDnsAddr,
            pstDnsOption->ucData, sizeof(in6_addr));
        DHCPV6C_SET_V6ADDR_NULL(pstDhcpcContext->aulSecdDnsAddr);
    }
    /* 主备都携带 */
    else
    {
        VOS_MemCpy(pstDhcpcContext->aulMainDnsAddr,
            pstDnsOption->ucData, sizeof(in6_addr));
        VOS_MemCpy(pstDhcpcContext->aulSecdDnsAddr,
            pstDnsOption->ucData + sizeof(in6_addr), sizeof(in6_addr));
    }
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_SaveOptionToContext
 *  初稿完成:       2012-07-12
 *  作    者:       y00170683
 *  函数功能:       保存消息内容至控制块
 *  输入参数:       DHCPV6C_OPTION_INFO_S *pstDhcpv6Option
 *  输出参数:       DHCPC_CTRLBLK *pstDhcpcContext
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_SaveOptionToContext(DHCPC_CTRLBLK *pstDhcpcContext,
                                                 DHCPV6C_OPTION_INFO_S *pstDhcpv6Option)
{
    if (NULL != pstDhcpv6Option->pstServerIdOption)
    {
        /* 保存SI-DUID 消息检查时已经确认长度不应大于DHCPV6C_MAX_DUID_LEN 14 */
        if (pstDhcpv6Option->pstServerIdOption->usLen <= DHCPV6C_MAX_DUID_LEN)
        {
            VOS_MemCpy(pstDhcpcContext->aucSiDuid,
                          pstDhcpv6Option->pstServerIdOption->ucData,
                          pstDhcpv6Option->pstServerIdOption->usLen);
        }
        else
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SIDUID_LEN2_ERR); /* 异常调用计数 */
        }
    }

    if (NULL != pstDhcpv6Option->pstIaNaOption)
    {
        /* 保存IANA */
        pstDhcpcContext->ulT1 = pstDhcpv6Option->pstIaNaOption->ulT1;
        pstDhcpcContext->ulT2 = pstDhcpv6Option->pstIaNaOption->ulT2;
    }

    if (NULL != pstDhcpv6Option->pstIaAddrOption)
    {
        /* 保存IA-ADDR */
        pstDhcpcContext->ulLease = pstDhcpv6Option->pstIaAddrOption->ulValidTime;
        VOS_MemCpy(pstDhcpcContext->aulUserIpAddr,
            &(pstDhcpv6Option->pstIaAddrOption->stIpv6Addr), sizeof(in6_addr));
    }

    /* 保存DNS CR20120726042 DNS-option只取最后一个的前两个地址作为主备DNS */
    DHCPV6C_SaveDnsOptionToContext(pstDhcpcContext, pstDhcpv6Option->pstDnsOption,
                        pstDhcpv6Option->ucMainDnsFlg, pstDhcpv6Option->ucSecdDnsFlg);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_ConvertDnsToHomeOrder
 *  初稿完成:       2012-07-27
 *  作    者:       y00170683
 *  函数功能:       将dns-option中字段转换为本地序
 *  输入参数:       DHCPV6C_TLV_OPTION_S **ppstDnsOption
 *  输出参数:       DHCPV6C_DNS_OPTION_S **ppstDnsOption, UCHAR *pucMainDnsFlg, UCHAR *pucSecdDnsFlg
 *  返回类型:       VOID
 *  其他说明:       CR20120726042 DNS-option只取最后一个的前两个地址作为主备DNS
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_ConvertDnsToHomeOrder(DHCPV6C_TLV_OPTION_S **ppstDnsOption,
                                                    UCHAR *pucMainDnsFlg, UCHAR *pucSecdDnsFlg)
{
    in6_addr stDnsAddr[DHCPV6C_MAX_DNS_NUM];

    (*ppstDnsOption)->usLen = VOS_NTOHS((*ppstDnsOption)->usLen);

    /* 携带多于两个地址 */
    if ((*ppstDnsOption)->usLen >= (DHCPV6C_MAX_DNS_NUM * sizeof(in6_addr)))
    {
        *pucMainDnsFlg = VOS_TRUE;
        *pucSecdDnsFlg = VOS_TRUE;
        VOS_MemCpy(stDnsAddr, (*ppstDnsOption)->ucData, DHCPV6C_MAX_DNS_NUM * sizeof(in6_addr));
//        DHCPV6_NTOHL_IPV6_ADDR(stDnsAddr[0]);
//        DHCPV6_NTOHL_IPV6_ADDR(stDnsAddr[1]);
        VOS_MemCpy((*ppstDnsOption)->ucData, stDnsAddr, DHCPV6C_MAX_DNS_NUM * sizeof(in6_addr));
    }
    /* 只携带一个地址 */
    else if((*ppstDnsOption)->usLen >= sizeof(in6_addr))
    {
        *pucMainDnsFlg = VOS_TRUE;
        *pucSecdDnsFlg = VOS_FALSE;
        VOS_MemCpy(stDnsAddr, (*ppstDnsOption)->ucData,  sizeof(in6_addr));
//        DHCPV6_NTOHL_IPV6_ADDR(stDnsAddr[0]);
        VOS_MemCpy((*ppstDnsOption)->ucData, stDnsAddr,  sizeof(in6_addr));
    }
    /* 其他情况,DNS信元错误 */
    else
    {
        *pucMainDnsFlg = VOS_FALSE;
        *pucSecdDnsFlg = VOS_FALSE;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_ConvertToHomeOrder
 *  初稿完成:       2012-07-09
 *  作    者:       y00170683
 *  函数功能:       将option中字段转换为本地序
 *  输入参数:       DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption
 *  输出参数:       DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_ConvertToHomeOrder(DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption)
{
    /* clientId */
    if (VOS_NULL != pstDhcpv6cOption->pstClientIdOption)
    {
        pstDhcpv6cOption->pstClientIdOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstClientIdOption->usLen);
    }

    /* CiDuId */
    if (VOS_NULL != pstDhcpv6cOption->pstCiDuidEn)
    {
        pstDhcpv6cOption->pstCiDuidEn->ulEnterpriseNum = VOS_NTOHL(pstDhcpv6cOption->pstCiDuidEn->ulEnterpriseNum);
    }

    /* ServerId */
    if (VOS_NULL != pstDhcpv6cOption->pstServerIdOption)
    {
        pstDhcpv6cOption->pstServerIdOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstServerIdOption->usLen);
    }

    /* IaNa */
    if (VOS_NULL != pstDhcpv6cOption->pstIaNaOption)
    {
        pstDhcpv6cOption->pstIaNaOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstIaNaOption->usLen);
        pstDhcpv6cOption->pstIaNaOption->ulId = VOS_NTOHL(pstDhcpv6cOption->pstIaNaOption->ulId);
        pstDhcpv6cOption->pstIaNaOption->ulT1 = VOS_NTOHL(pstDhcpv6cOption->pstIaNaOption->ulT1);
        pstDhcpv6cOption->pstIaNaOption->ulT2 = VOS_NTOHL(pstDhcpv6cOption->pstIaNaOption->ulT2);
    }

    /* IaAddr */
    if (VOS_NULL != pstDhcpv6cOption->pstIaAddrOption)
    {
        pstDhcpv6cOption->pstIaAddrOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstIaAddrOption->usLen);
        //DHCPV6_NTOHL_IPV6_ADDR(pstDhcpv6cOption->pstIaAddrOption->stIpv6Addr);
        pstDhcpv6cOption->pstIaAddrOption->ulPreTime = VOS_NTOHL(pstDhcpv6cOption->pstIaAddrOption->ulPreTime);
        pstDhcpv6cOption->pstIaAddrOption->ulValidTime = VOS_NTOHL(pstDhcpv6cOption->pstIaAddrOption->ulValidTime);
    }

    /* Dns CR20120726042 DNS-option只取最后一个的前两个地址作为主备DNS */

    if (VOS_NULL != pstDhcpv6cOption->pstDnsOption)
    {
        DHCPV6C_ConvertDnsToHomeOrder(&(pstDhcpv6cOption->pstDnsOption),
            &(pstDhcpv6cOption->ucMainDnsFlg), &(pstDhcpv6cOption->ucSecdDnsFlg));
    }

    /* StatusCode */
    if (VOS_NULL != pstDhcpv6cOption->pstMsgStatusCodeOption)
    {
        pstDhcpv6cOption->pstMsgStatusCodeOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstMsgStatusCodeOption->usLen);
        pstDhcpv6cOption->pstMsgStatusCodeOption->usCode = VOS_NTOHS(pstDhcpv6cOption->pstMsgStatusCodeOption->usCode);
    }

    if (VOS_NULL != pstDhcpv6cOption->pstIaNaStatusCodeOption)
    {
        pstDhcpv6cOption->pstIaNaStatusCodeOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstIaNaStatusCodeOption->usLen);
        pstDhcpv6cOption->pstIaNaStatusCodeOption->usCode = VOS_NTOHS(pstDhcpv6cOption->pstIaNaStatusCodeOption->usCode);
    }

    if (VOS_NULL != pstDhcpv6cOption->pstIaAddrStatusCodeOption)
    {
        pstDhcpv6cOption->pstIaAddrStatusCodeOption->usLen = VOS_NTOHS(pstDhcpv6cOption->pstIaAddrStatusCodeOption->usLen);
        pstDhcpv6cOption->pstIaAddrStatusCodeOption->usCode = VOS_NTOHS(pstDhcpv6cOption->pstIaAddrStatusCodeOption->usCode);
    }
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_IaAddrOptionDecode
 *  初稿完成:       2012-07-04
 *  作    者:       y00170683
 *  函数功能:       解析IaAddrOption
 *  输入参数:       UCHAR *pucMsg, ULONG ulMsgLen,
 *  输出参数:       DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_IaAddrOptionDecode(UCHAR *pucMsg,
                                               ULONG ulMsgLen,
                                               DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption)
{
    ULONG ulOffset = 0;
    ULONG ulExtnLen = 0;
    DHCPV6C_TLV_OPTION_S * pstTmpTlvExt = VOS_NULL;

    while(ulOffset < ulMsgLen)
    {
        pstTmpTlvExt = (DHCPV6C_TLV_OPTION_S*)&(pucMsg[ulOffset]);
        ulExtnLen = VOS_NTOHS(pstTmpTlvExt->usLen) + DHCPV6_OPT_HEADER_LEN;

        /* OPTION长度大于消息长度,说明当前信元错误不能解析使用,应该直接退出 */
        if (ulOffset + ulExtnLen > ulMsgLen)
        {
            DHCPC_DebugPrint(PTM_LOG_INFO, "ulOffset = %u, type = %u, len = %u, ulMsgLen = %u",
                               ulOffset, VOS_NTOHS(pstTmpTlvExt->usType),
                               VOS_NTOHS(pstTmpTlvExt->usLen), ulMsgLen);
            break;
        }

        switch (VOS_NTOHS(pstTmpTlvExt->usType))
        {
            case DHCPV6_MSG_OPTION_STATUS_CODE:
            {
                pstDhcpv6cOption->pstIaAddrStatusCodeOption = (DHCPV6C_STATUS_CODE_OPTION_S *)pstTmpTlvExt;
                break;
            }
            default:     /* ignore unknow extension */
            {
                break;
            }
        }
        ulOffset += ulExtnLen;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_IaNaOptionDecode
 *  初稿完成:       2012-07-04
 *  作    者:       y00170683
 *  函数功能:       解析IaNaOption
 *  输入参数:       UCHAR *pucMsg, ULONG ulMsgLen,
 *  输出参数:       DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_IaNaOptionDecode(UCHAR *pucMsg,
                                            ULONG ulMsgLen,
                                            DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption)
{
    ULONG ulOffset = 0;
    ULONG ulExtnLen = 0;
    USHORT usIaAddrLen = 0;
    USHORT usIaAddrDataLen = 0;
    UCHAR *pucIaAddrData = VOS_NULL;
    DHCPV6C_TLV_OPTION_S * pstTmpTlvExt = VOS_NULL;

    while(ulOffset < ulMsgLen)
    {
        pstTmpTlvExt = (DHCPV6C_TLV_OPTION_S*)&(pucMsg[ulOffset]);
        ulExtnLen = VOS_NTOHS(pstTmpTlvExt->usLen) + DHCPV6_OPT_HEADER_LEN;

        /* OPTION长度大于消息长度,说明当前信元错误不能解析使用,应该直接退出 */
        if (ulOffset + ulExtnLen > ulMsgLen)
        {
            DHCPC_DebugPrint(PTM_LOG_INFO, "ulOffset = %u, type = %u, len = %u, ulMsgLen = %u",
                               ulOffset, VOS_NTOHS(pstTmpTlvExt->usType),
                               VOS_NTOHS(pstTmpTlvExt->usLen), ulMsgLen);
            break;
        }

        switch (VOS_NTOHS(pstTmpTlvExt->usType))
        {
            case DHCPV6_MSG_OPTION_IAADDR:
            {
                pstDhcpv6cOption->pstIaAddrOption = (DHCPV6C_IAADDR_OPTION_S *)pstTmpTlvExt;

                /* 解析IANA-data 可能含有staus-code */
                pucIaAddrData = pstDhcpv6cOption->pstIaAddrOption->ucData;
                usIaAddrLen = VOS_NTOHS(pstDhcpv6cOption->pstIaAddrOption->usLen);
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "IaAddrLen = %u ", usIaAddrLen);
                if (usIaAddrLen > (sizeof(DHCPV6C_IAADDR_OPTION_S) - DHCPV6_OPT_HEADER_LEN))
                {
                    usIaAddrDataLen = usIaAddrLen
                                    - (sizeof(DHCPV6C_IAADDR_OPTION_S) - DHCPV6_OPT_HEADER_LEN);
                    DHCPV6C_IaAddrOptionDecode(pucIaAddrData, (ULONG)usIaAddrDataLen, pstDhcpv6cOption);
                }
                break;
            }
            case DHCPV6_MSG_OPTION_STATUS_CODE:
            {
                pstDhcpv6cOption->pstIaNaStatusCodeOption = (DHCPV6C_STATUS_CODE_OPTION_S *)pstTmpTlvExt;
                break;
            }
            default:     /* ignore unknow extension */
            {
                break;
            }
        }
        ulOffset += ulExtnLen;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_OptionDecode
 *  初稿完成:       2012-06-29
 *  作    者:       y00170683
 *  函数功能:       解析Option
 *  输入参数:       UCHAR *pucMsg,  ULONG ulMsgLen
 *  输出参数:       DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_OptionDecode(UCHAR *pucMsg,
                                      ULONG ulMsgLen,
                                      DHCPV6C_OPTION_INFO_S *pstDhcpv6cOption)
{
    ULONG ulOffset = 0;
    ULONG ulExtnLen = 0;
    USHORT usIaNaLen = 0;
    USHORT usIaNaDataLen = 0;
    UCHAR *pucIaNaData = VOS_NULL;
    DHCPV6C_TLV_OPTION_S *pstTmpTlvExt = VOS_NULL;

    while(ulOffset < ulMsgLen)
    {
        pstTmpTlvExt = (DHCPV6C_TLV_OPTION_S*)&(pucMsg[ulOffset]);
        ulExtnLen = VOS_NTOHS(pstTmpTlvExt->usLen) + DHCPV6_OPT_HEADER_LEN;

        /* OPTION长度大于消息长度,说明当前信元错误不能解析使用,应该直接退出 */
        if (ulOffset + ulExtnLen > ulMsgLen)
        {
            DHCPC_DebugPrint(PTM_LOG_INFO, "ulOffset = %u, type = %u, len = %u, ulMsgLen = %u",
                               ulOffset, VOS_NTOHS(pstTmpTlvExt->usType),
                               VOS_NTOHS(pstTmpTlvExt->usLen), ulMsgLen);
            break;
        }

        switch (VOS_NTOHS(pstTmpTlvExt->usType))
        {
            case DHCPV6_MSG_OPTION_CLIENTID:
            {
                pstDhcpv6cOption->pstClientIdOption = pstTmpTlvExt;
                if ((DHCPV6C_MAX_DUID_LEN == VOS_NTOHS(pstTmpTlvExt->usLen))
                    && (DHCPV6_MSG_OPTION_DUID_EN == VOS_NTOHS(*(USHORT*)pstTmpTlvExt->ucData)))
                {
                    pstDhcpv6cOption->pstCiDuidEn = (DHCPV6C_DUID_EN_OPTION_S *)(pstTmpTlvExt->ucData);
                }
                break;
            }
            case DHCPV6_MSG_OPTION_SERVERID:
            {
                pstDhcpv6cOption->pstServerIdOption = pstTmpTlvExt;
                break;
            }
            case DHCPV6_MSG_OPTION_IA_NA:
            {
                pstDhcpv6cOption->pstIaNaOption = (DHCPV6C_IANA_OPTION_S*)pstTmpTlvExt;

                /* 解析IANA-data 可能含有ia-addr, staus-code */
                pucIaNaData = pstDhcpv6cOption->pstIaNaOption->ucData;
                usIaNaLen = VOS_NTOHS(pstDhcpv6cOption->pstIaNaOption->usLen);
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "IaNaLen = %u ", usIaNaLen);
                if (usIaNaLen > (sizeof(DHCPV6C_IANA_OPTION_S) - DHCPV6_OPT_HEADER_LEN))
                {
                    usIaNaDataLen = usIaNaLen
                                    - (sizeof(DHCPV6C_IANA_OPTION_S) - DHCPV6_OPT_HEADER_LEN);
                    DHCPV6C_IaNaOptionDecode(pucIaNaData, (ULONG)usIaNaDataLen, pstDhcpv6cOption);
                }
                break;
            }
            case DHCPV6_MSG_OPTION_DNS_SERVERS:
            {
                /* CR20120726042 DNS-option只取最后一个的前两个地址作为主备DNS */
                pstDhcpv6cOption->pstDnsOption = pstTmpTlvExt;
                break;
            }
            case DHCPV6_MSG_OPTION_STATUS_CODE:
            {
                pstDhcpv6cOption->pstMsgStatusCodeOption = (DHCPV6C_STATUS_CODE_OPTION_S *)pstTmpTlvExt;
                break;
            }
            default:     /* ignore unknow extension */
            {
                break;
            }
        }
        ulOffset += ulExtnLen;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return ;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_GetSeqNumByMsg
 *  初稿完成:       2012-07-07
 *  作    者:       y00170683
 *  函数功能:       根据消息得出sequenceNum
 *  输入参数:       USHORT *pusSeqNum
 *  输出参数:       USHORT *pusSeqNum
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_GetSeqNumByMsg(USHORT *pusSeqNum,
                                            UCHAR *pucMsg)
{
    DHCPV6C_MSG_S stTransId = {0};
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter, TransId=%x", ((DHCPV6C_MSG_S*)pucMsg)->ulTransIdBit24);

    stTransId.ulTransIdBit24 = VOS_NTOHBIT24(((DHCPV6C_MSG_S*)pucMsg)->ulTransIdBit24);

    if ((CRM_BOARD_TYPE_SPUD == g_ulDhcpcBoardType)
        || (CRM_BOARD_TYPE_SPUE == g_ulDhcpcBoardType))
    {
        *pusSeqNum = stTransId.ulTransIdBit24 & (DHCPV6C_MAX_SEQUENCE_ID_DE);
    }
    else if (CRM_BOARD_TYPE_SPUF == g_ulDhcpcBoardType)
    {
        *pusSeqNum = stTransId.ulTransIdBit24 & (DHCPV6C_MAX_SEQUENCE_ID_F);
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit, TransId = %x, usSeqNum = %u",
                       stTransId.ulTransIdBit24, *pusSeqNum);
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_MsgDecode
 *  初稿完成:       2012-07-10
 *  作    者:       y00170683
 *  函数功能:       消息解码
 *  输入参数:       DHCPV6C_MSG_INFO_S *pstMsgInfo
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_MsgDecode(DHCPV6C_MSG_INFO_S *pstMsgInfo)
{
    ULONG ulOffset = sizeof(DHCPV6C_MSG_S);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    /* 消息长度检查 */
    if(pstMsgInfo->ulMsgLen < ulOffset)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_MSGLEN_ERR);
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:ulMsgLen = %u", pstMsgInfo->ulMsgLen);
        return VOS_ERR;
    }

    /* 解析OPTION */
    DHCPV6C_OptionDecode(pstMsgInfo->pucMsg + ulOffset,
                            pstMsgInfo->ulMsgLen - ulOffset,
                            &(pstMsgInfo->stDhcpv6cOptionInfo));

    /* 网络序转化为主机序 */
    DHCPV6C_ConvertToHomeOrder(&(pstMsgInfo->stDhcpv6cOptionInfo));

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return VOS_OK;
}

#define _MESSAGE_ENCODE_
/*****************************************************************************
 *  函数名称:       DHCPV6C_CalcuTransId
 *  初稿完成:       2012-07-07
 *  作    者:       y00170683
 *  函数功能:       计算TransctionId
 *  输入参数:       DHCPV6C_MSG_S *pstDhcpv6cMsg,  ULONG ulTeidc
 *  输出参数:       USHORT usSeqNum
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_CalcuTransId(DHCPV6C_MSG_S *pstDhcpv6cMsg,
                                     ULONG ulTeidc,
                                     USHORT usSeqNum)
{
    ULONG ulToken = DHCPC_GET_TOKEN_BY_TEIDC(ulTeidc);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    if ((CRM_BOARD_TYPE_SPUD == g_ulDhcpcBoardType)
        || (CRM_BOARD_TYPE_SPUE == g_ulDhcpcBoardType))
    {
        pstDhcpv6cMsg->ulTransIdBit24 = ulToken<<DHCPV6C_TOKEN_BIT11
                                        | DHCPC_SELF_CMPIDX_INSG<<DHCPV6C_SCID_BIT9
                                        | usSeqNum;
    }
    else if (CRM_BOARD_TYPE_SPUF == g_ulDhcpcBoardType)
    {
        pstDhcpv6cMsg->ulTransIdBit24  = ulToken<<DHCPV6C_TOKEN_BIT10 | usSeqNum;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit, TransId = %x, ulToken = %u, usSeqNum = %u",
                       pstDhcpv6cMsg->ulTransIdBit24, ulToken, usSeqNum);
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_GetCiDuidData
 *  初稿完成:       2012-07-07
 *  作    者:       y00170683
 *  函数功能:       获取CI-DUID-DATA
 *  输入参数:       DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       UCHAR *pucData
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_GetCiDuidData(UCHAR *pucData,
                                       DHCPC_CTRLBLK *pstDhcpcContext)
{
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    /* 优先使用MSISDN，其次使用IMSI，再次使用IMEI */
    if((VOS_NULL_DWORD != pstDhcpcContext->aulMSISDN[0])
        || (VOS_NULL_DWORD != pstDhcpcContext->aulMSISDN[1]))
    {
        VOS_MemCpy(pucData, (UCHAR *)pstDhcpcContext->aulMSISDN, DHCP_MAX_MSISDN_LEN);
    }
    else if ((VOS_NULL_DWORD != pstDhcpcContext->aulIMSI[0])
        || (VOS_NULL_DWORD != pstDhcpcContext->aulIMSI[1]))
    {
        VOS_MemCpy(pucData, (UCHAR *)pstDhcpcContext->aulIMSI, DHCP_MAX_MSISDN_LEN);
    }
    else if ((VOS_NULL_DWORD != pstDhcpcContext->aulIMEI[0])
        || (VOS_NULL_DWORD != pstDhcpcContext->aulIMEI[1]))
    {
        VOS_MemCpy(pucData, (UCHAR *)pstDhcpcContext->aulIMEI, DHCP_MAX_MSISDN_LEN);
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_FillClientIdOption
 *  初稿完成:       2012-06-29
 *  作    者:       y00170683
 *  函数功能:       填充Client Identifier Option
 *  输入参数:       DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       UCHAR *pucMsgBuff, ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_FillClientIdOption(UCHAR *pucMsgBuff,
                                           ULONG *pulOffset,
                                           DHCPC_CTRLBLK *pstDhcpcContext)
{
    USHORT usOptionLen = 0;
    DHCPV6C_TLV_OPTION_S *pstClientIdOption = (DHCPV6C_TLV_OPTION_S *)pucMsgBuff;
    DHCPV6C_DUID_EN_OPTION_S *pstDuidEn = (DHCPV6C_DUID_EN_OPTION_S *)pstClientIdOption->ucData;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    pstClientIdOption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_CLIENTID);
    pstDuidEn->usType = VOS_HTONS(DHCPV6_MSG_OPTION_DUID_EN);
    pstDuidEn->ulEnterpriseNum = VOS_HTONL(DHCPV6_HUAWEI_ENTERPRISENUM);
    usOptionLen += sizeof(DHCPV6C_DUID_EN_OPTION_S);

    /* 获取CI-DUID-DATA,BCD码-不需要字节序转换 */
    DHCPV6C_GetCiDuidData(pstDuidEn->ucData, pstDhcpcContext);
    usOptionLen += DHCP_MAX_MSISDN_LEN;

    pstClientIdOption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_FillServerIdOption
 *  初稿完成:       2012-06-29
 *  作    者:       y00170683
 *  函数功能:       填充Server Identifier Option
 *  输入参数:       UCHAR aucSiDuid[]
 *  输出参数:       UCHAR *pucMsgBuff,  ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_FillServerIdOption(UCHAR *pucMsgBuff,
                                            ULONG *pulOffset,
                                            UCHAR aucSiDuid[])
{
    DHCPV6C_TLV_OPTION_S *pstServerIdOption = (DHCPV6C_TLV_OPTION_S *)pucMsgBuff;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    pstServerIdOption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_SERVERID);
    VOS_MemCpy(pstServerIdOption->ucData, aucSiDuid, DHCPV6C_MAX_DUID_LEN);
    pstServerIdOption->usLen = VOS_HTONS(DHCPV6C_MAX_DUID_LEN);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + DHCPV6C_MAX_DUID_LEN);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_FillIaAddrOption
 *  初稿完成:       2012-06-29
 *  作    者:       y00170683
 *  函数功能:       填充IA Address Option
 *  输入参数:       DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       UCHAR *pucMsgBuff, ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_FillIaAddrOption(UCHAR *pucMsgBuff,
                                         ULONG *pulOffset,
                                         DHCPC_CTRLBLK *pstDhcpcContext)
{
    USHORT usOptionLen = 0;
    DHCPV6C_IAADDR_OPTION_S *pstIaAddrOption = (DHCPV6C_IAADDR_OPTION_S *)pucMsgBuff;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    pstIaAddrOption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_IAADDR);
    VOS_MemCpy(&(pstIaAddrOption->stIpv6Addr), pstDhcpcContext->aulUserIpAddr, sizeof(in6_addr));
//    DHCPV6_HTONL_IPV6_ADDR(pstIaAddrOption->stIpv6Addr);
    usOptionLen += sizeof(in6_addr);
    pstIaAddrOption->ulPreTime = 0;
    usOptionLen += sizeof(ULONG);
    pstIaAddrOption->ulValidTime = VOS_HTONL(pstDhcpcContext->ulLease);
    usOptionLen += sizeof(ULONG);
    pstIaAddrOption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += sizeof(DHCPV6C_IAADDR_OPTION_S);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_FillIaNaOption
 *  初稿完成:       2012-06-29
 *  作    者:       y00170683
 *  函数功能:       填充Identity Association for Non-temporary Addresses Option
 *  输入参数:       UCHAR ucIsSolictFlg, DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       UCHAR *pucMsgBuff,   ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_FillIaNaOption(UCHAR *pucMsgBuff,
                                       ULONG *pulOffset,
                                       UCHAR ucIsSolictFlg,
                                       DHCPC_CTRLBLK *pstDhcpcContext)
{
    ULONG ulIaAddrLen = 0;
    USHORT usOptionLen = 0;
    DHCPV6C_IANA_OPTION_S *pstIanaOption = (DHCPV6C_IANA_OPTION_S *)pucMsgBuff;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    pstIanaOption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_IA_NA);
    pstIanaOption->ulId = VOS_HTONL(pstDhcpcContext->ulTEIDC);
    usOptionLen += sizeof(pstIanaOption->ulId);
    pstIanaOption->ulT1 = VOS_HTONL(pstDhcpcContext->ulT1);
    usOptionLen += sizeof(pstIanaOption->ulT1);
    pstIanaOption->ulT2 = VOS_HTONL(pstDhcpcContext->ulT2);
    usOptionLen += sizeof(pstIanaOption->ulT2);

    /* 除 solicit 消息外都要添加IaAddrOption */
    if (VOS_FALSE == ucIsSolictFlg)
    {
        DHCPV6C_FillIaAddrOption(pstIanaOption->ucData, &ulIaAddrLen, pstDhcpcContext);
        usOptionLen += (USHORT)ulIaAddrLen;
    }
    pstIanaOption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_FillRapidComOption
 *  初稿完成:       2012-07-27
 *  作    者:       y00170683
 *  函数功能:       填充rapid-commit-option
 *  输入参数:       无
 *  输出参数:       UCHAR *pucMsgBuff, ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:       CR20120726042 rapid-commit-option作为单独的option携带
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_FillRapidComOption(UCHAR *pucMsgBuff, ULONG *pulOffset)
{
    DHCPV6C_TLV_OPTION_S *pstRapidComOption = (DHCPV6C_TLV_OPTION_S *)pucMsgBuff;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    pstRapidComOption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_RAPID_COMMIT);
    pstRapidComOption->usLen = 0;
    *pulOffset += DHCPV6_OPT_HEADER_LEN ;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_FillOROption
 *  初稿完成:       2012-06-29
 *  作    者:       y00170683
 *  函数功能:       填充Option Request Option
 *  输入参数:       无
 *  输出参数:       UCHAR *pucMsgBuff, ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_FillOROption(UCHAR *pucMsgBuff, ULONG *pulOffset)
{
    USHORT usOptionLen = 0;
    DHCPV6C_TLV_OPTION_S *pstOROption = (DHCPV6C_TLV_OPTION_S *)pucMsgBuff;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    pstOROption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_ORO);

    /* 请求快速流程和DNS */
    /* Deleted start by y00170683 at 2012-07-27 UGW10.0-DHCPV6C特性 for CR20120726042 rapid-commit-option作为单独的option携带 */
    /* Deleted end by y00170683 at 2012-07-27 UGW10.0-DHCPV6C特性 for CR20120726042 rapid-commit-option作为单独的option携带 */
    *(USHORT*)(pstOROption->ucData) = VOS_HTONS(DHCPV6_MSG_OPTION_DNS_SERVERS);
    usOptionLen += sizeof(USHORT);
    pstOROption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_FillElapTimeOption
 *  初稿完成:       2012-06-29
 *  作    者:       y00170683
 *  函数功能:       填充Elapsed_Time Option
 *  输入参数:       UCHAR ucResendTime,   UCHAR ucResendTimeout
 *  输出参数:       UCHAR *pucMsgBuff, ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
 *  修改记录:       DTS2012083106081 填自第一条消息已经等待的时间,备sever时继续累加,不是从0开始
*****************************************************************************/
VOID DHCPV6C_FillElapTimeOption(UCHAR *pucMsgBuff,
                                            ULONG *pulOffset,
                                            UCHAR ucResendTime,
                                            UCHAR ucResendTimeout)
{
    USHORT usTryTime = 0;
    USHORT usOptionLen = 0;
    DHCPV6C_TLV_OPTION_S *pstElapTimeOption = (DHCPV6C_TLV_OPTION_S *)pucMsgBuff;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter, ucResendTime = %u, ucResendTimeout = %u",
        ucResendTime, ucResendTimeout);

    usTryTime = ucResendTime * ucResendTimeout;
    pstElapTimeOption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_ELAPSED_TIME);
    *(USHORT*)pstElapTimeOption->ucData = VOS_HTONS((USHORT)(usTryTime * DHCPV6C_HUNDRED));
    usOptionLen += sizeof(USHORT);
    pstElapTimeOption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_FillDnsOption
 *  初稿完成:       2012-06-29
 *  作    者:       y00170683
 *  函数功能:       填充DNS Option
 *  输入参数:       in6_addr *pstDnsAddr
 *  输出参数:       UCHAR *pucMsgBuff, ULONG *pulOffset
 *  返回类型:       VOID
 *  其他说明:       CR20120726042 DNS-option只取最后一个的前两个地址作为主备DNS
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_FillDnsOption(UCHAR *pucMsgBuff,
                                      ULONG *pulOffset,
                                      DHCPC_CTRLBLK *pstDhcpcContext)
{
    in6_addr stIpv6Addr;
    USHORT usOptionLen = 0;
    DHCPV6C_TLV_OPTION_S *pstDnsServerOption = (DHCPV6C_TLV_OPTION_S *)pucMsgBuff;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    pstDnsServerOption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_DNS_SERVERS);
    VOS_MemCpy(&stIpv6Addr, pstDhcpcContext->aulMainDnsAddr, sizeof(in6_addr));
//    DHCPV6_HTONL_IPV6_ADDR(stIpv6Addr);
    VOS_MemCpy(pstDnsServerOption->ucData, &stIpv6Addr, sizeof(in6_addr));
    usOptionLen += sizeof(in6_addr);

    /* 如果备DNS有效,也需要携带 */
    if (VOS_FALSE == DHCPC_CHECK_V6ADDR_IS_NULL(pstDhcpcContext->aulSecdDnsAddr))
    {
        VOS_MemCpy(&stIpv6Addr, pstDhcpcContext->aulSecdDnsAddr, sizeof(in6_addr));
//        DHCPV6_HTONL_IPV6_ADDR(stIpv6Addr);
        VOS_MemCpy(pstDnsServerOption->ucData + sizeof(in6_addr), &stIpv6Addr, sizeof(in6_addr));
        usOptionLen += sizeof(in6_addr);
    }
    pstDnsServerOption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_FillMustOption
 *  初稿完成:       2012-06-29
 *  作    者:       y00170683
 *  函数功能:       填充必选Option
 *  输入参数:       UCHAR ucIsSolictFlg,DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       UCHAR *pucMsgBuff,  ULONG *pulMsgLen,
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_FillMustOption(UCHAR *pucMsgBuff,
                                       ULONG *pulMsgLen,
                                       UCHAR ucIsSolictFlg,
                                       DHCPC_CTRLBLK *pstDhcpcContext)
{
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    /* 填充ClientId Option */
    DHCPV6C_FillClientIdOption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen, pstDhcpcContext);

    /* 填充ServerId Option --solicit消息不需要填充 */
    if (VOS_FALSE == ucIsSolictFlg)
    {
        DHCPV6C_FillServerIdOption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen, pstDhcpcContext->aucSiDuid);
    }

    /* 填充IA_NA Option */
    DHCPV6C_FillIaNaOption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen, ucIsSolictFlg, pstDhcpcContext);

    /* 填充Elapsed_Time Option */
    DHCPV6C_FillElapTimeOption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen,
                pstDhcpcContext->ucWaitRspTimeOutNum, pstDhcpcContext->ucResendTimeout);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_FillMsg
 *  初稿完成:       2012-07-18
 *  作    者:       y00170683
 *  函数功能:       填充消息
 *  输入参数:       ULONG ulDhpcv6MsgType, DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       UCHAR *pucMsgBuff,  ULONG *pulMsgLen
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_FillMsg(UCHAR *pucMsgBuff,
                             ULONG *pulMsgLen,
                             ULONG ulDhpcv6MsgType,
                             DHCPC_CTRLBLK *pstDhcpcContext)
{
    DHCPV6C_MSG_S *pstDhcpv6Msg = NULL;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    /* 填充消息头 */
    pstDhcpv6Msg = (DHCPV6C_MSG_S *)pucMsgBuff;
    pstDhcpv6Msg->ulMsgTypeBit8 = ulDhpcv6MsgType;
    DHCPV6C_CalcuTransId(pstDhcpv6Msg, pstDhcpcContext->ulTEIDC, pstDhcpcContext->usSeqNum);
    pstDhcpv6Msg->ulTransIdBit24 = VOS_HTONBIT24(pstDhcpv6Msg->ulTransIdBit24);
    *pulMsgLen += sizeof(DHCPV6C_MSG_S);

    /* 填充必选Option */
    if (DHCPV6_MSG_TYPE_SOLICIT == ulDhpcv6MsgType)
    {
        DHCPV6C_FillMustOption(pucMsgBuff, pulMsgLen, VOS_TRUE, pstDhcpcContext);

        /* solicit消息 需要填充rapid-commit-option CR20120726042 */
        DHCPV6C_FillRapidComOption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen);

        /* solicit消息 填充option request Option 请求DNS */
        DHCPV6C_FillOROption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen);
    }
    else
    {
        DHCPV6C_FillMustOption(pucMsgBuff, pulMsgLen, VOS_FALSE, pstDhcpcContext);
    }

    /* request消息 填充DnsServer Option */
    if (DHCPV6_MSG_TYPE_REQUEST == ulDhpcv6MsgType)
    {
        /* mod by t00265288 start 我们改为不依赖上下文，request中携带DNS的选项 */
#if 0
        /* 上下文中存在有效的主DNS地址时才进行携带 */
        if (VOS_FALSE == DHCPC_CHECK_V6ADDR_IS_NULL(pstDhcpcContext->aulMainDnsAddr))
        {
            DHCPV6C_FillDnsOption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen, pstDhcpcContext);
        }
#endif
        DHCPV6C_FillDnsOption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen, pstDhcpcContext);
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_CheckSendMsgType
 *  初稿完成:       2012-07-18
 *  作    者:       y00170683
 *  函数功能:       判断消息类型
 *  输入参数:       ulDhpcv6MsgType
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_CheckSendMsgType(ULONG ulDhpcv6MsgType)
{
    ULONG ulRet = VOS_OK;

    switch (ulDhpcv6MsgType)
    {
        case DHCPV6_MSG_TYPE_SOLICIT :
        case DHCPV6_MSG_TYPE_REQUEST :
        case DHCPV6_MSG_TYPE_RENEW :
        case DHCPV6_MSG_TYPE_RELEASE :
        case DHCPV6_MSG_TYPE_DECLINE :
            ulRet = VOS_OK;
            break;

        default:
            ulRet = VOS_ERR;
            break;
    }

    return ulRet;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_UdpOutPut
 *  初稿完成:       2012-07-07
 *  作    者:       y00170683
 *  函数功能:       封装buff,发包
 *  输入参数:       UCHAR *pucMsg, ULONG ulMsgLen, DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_UdpOutPut(UCHAR *pucMsg, ULONG ulMsgLen, DHCPC_CTRLBLK *pstDhcpcContext)
{
    LONG lRet = 0;
    ULONG ulRet = VOS_OK;
    ULONG ulVpnIndex = 0;
    PMBUF_S *pstMbuf = NULL;
    FWD_TO_CTRL_HDR stCtrlEncap = {0};
    UDPS_PACKET_INFO_S stNodeTemp = {0};
    TTF_MEM_ST        *pstData;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter, ulMsgLen = %u", ulMsgLen);

    /* 备板不发送 */
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup((UCHAR)DVM_SELF_SLOTID))
    {
        return VOS_ERR;
    }

    ulRet = DHCPM_GetDhcpSrvVpnByIndex(pstDhcpcContext->usServerGrpIndex, &ulVpnIndex);
    if (VOS_OK != ulRet)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:call DHCPM_GetDhcpSrvVpnByIndex ulRet = %x", ulRet);
        return ulRet;
    }

    /* DHCPv6 UDP信令必须算Checksum */
    UDPS_SET_CHECK_SUM_ENABLE(&stNodeTemp);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "src addr: 0x%x %x %x %x", pstDhcpcContext->aulAgentIpAddr[0],
                    pstDhcpcContext->aulAgentIpAddr[1], pstDhcpcContext->aulAgentIpAddr[2],pstDhcpcContext->aulAgentIpAddr[3]);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "dst addr: 0x%x %x %x %x", pstDhcpcContext->aulSrvIp[0], pstDhcpcContext->aulSrvIp[1],
                        pstDhcpcContext->aulSrvIp[2], pstDhcpcContext->aulSrvIp[3]);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "vpnindex = %u selfpid = %u", ulVpnIndex, DVM_GetSelfLpid());

    /*构造UDP头参数*/
    stNodeTemp.ulFamily = AF_INET6;
    VOS_MemCpy(&(stNodeTemp.uaddrSrc.stAddr6Src.stSin6_addr),
        pstDhcpcContext->aulAgentIpAddr, sizeof(in6_addr));
    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPV6_CLIENT_UDP_PORT;
    VOS_MemCpy(&(stNodeTemp.uaddrDst.stAddr6Dst.stSin6_addr), pstDhcpcContext->aulSrvIp, sizeof(in6_addr));
    stNodeTemp.uaddrDst.stAddrDst.sin_usPort = DHCPV6_SERVER_UDP_PORT;
    stNodeTemp.ulVpnId = ulVpnIndex;
    stNodeTemp.pData = (CHAR*)&stCtrlEncap;
    stNodeTemp.ulDataLen = sizeof(FWD_TO_CTRL_HDR);

    ///TODO: subindex
    /*调用函数发送报文*/
    DHCP_MemZero(&stCtrlEncap,sizeof(FWD_TO_CTRL_HDR));

    fwd_set_ctrlhdr_vcpuid(&stCtrlEncap,DVM_GetSelfLpid());
    fwd_set_ctrlhdr_vrfindex(&stCtrlEncap,ulVpnIndex);
    fwd_set_ctrlhdr_moduleid(&stCtrlEncap,MID_DHCPC);
    fwd_set_ctrlhdr_msgcode(&stCtrlEncap,(ULONG)((DHCPV6C_MSG_S *)pucMsg)->ulMsgTypeBit8);

    /* 申请BUFF */
    pstMbuf = (PMBUF_S *)PMBUF_GetPMbuf(MID_DHCPC, 500);
    if (VOS_NULL == pstMbuf)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_ALLOC_MBUF_ERR);
        return VOS_ERR;
    }

    /* 填充MBUFF内容，不包含IP 和UDP */
    ulRet = PMBUF_CopyDataFromBufferToPMBuf(pstMbuf, 0, ulMsgLen, pucMsg, MID_DHCPC);
    if (VOS_OK != ulRet)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_COPY_MBUF_ERR);
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:call UDPS_DataHandle ulRet = %x", ulRet);
        (VOID)PMBUF_Destroy(pstMbuf);
        return VOS_ERR;
    }

    /* 调用UDP接口发送 */
    stNodeTemp.uaddrDst.stAddr6Dst.ucSin6_family = AF_INET6;
    stNodeTemp.uaddrSrc.stAddr6Src.ucSin6_family = AF_INET6;
    (VOID)UDPS_ConvertToSockAddr((SOCKADDRIN_S * )&(stNodeTemp.uaddrSrc.stAddr6Src), sizeof(SOCKADDR_IN6_S));
    (VOID)UDPS_ConvertToSockAddr((SOCKADDRIN_S * )&(stNodeTemp.uaddrDst.stAddr6Dst), sizeof(SOCKADDR_IN6_S));

    pstData = PPPC_AdapterMBuftoTtfMemory(pstMbuf, TTF_MEM_POOL_ID_UL_DATA, 0, ulMsgLen);

    lRet = PPPC_RcvCdsUlFrame(pstDhcpcContext->ucRabId, pstData); /* TODO rabId hard code */
    lRet = UDPS_DataHandle(&stNodeTemp, pstMbuf);
    if (0 != lRet)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_UDPOUT_ERR);
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:call UDPS_DataHandle lRet = %d", lRet);
        (VOID)PMBUF_Destroy(pstMbuf);
        return VOS_ERR;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return VOS_OK;
}


/*****************************************************************************
 *  函数名称:       DHCPV6C_SendDhcpDlDatatoCds
 *  初稿完成:       2015-04-28
 *  作    者:       t00265288
 *  功能描述:       下行DHCP报文发送到CDS
 *  输入参数:       pstTtfMem    TTF Mem
                    ulMsgLen     长度
                    enModemId
                    ucRabId      承载号
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
*****************************************************************************/
VOS_VOID DHCPV6C_SendDhcpDlDatatoCds(TTF_MEM_ST *pstTtfMem, ULONG ulMsgLen, USHORT enModemId, UCHAR ucRabId)
{
    CDS_CDMA_TRANS_DATA_STRU            stPppSdu;

    VOS_MemSet(&stPppSdu, 0, sizeof(stPppSdu));
    stPppSdu.ucRabId    = ucRabId;
    stPppSdu.ulSduLen   = ulMsgLen;
    stPppSdu.pstSdu     = pstTtfMem;

    CDS_CDMA_DL_DataInd(&stPppSdu, enModemId);
    CDS_CDMA_WakeupCds();

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_SendMsgToServer
 *  初稿完成:       2015-02-28
 *  作    者:       t00265288
 *  函数功能:       发送dhcp报文到dhcp服务器
 *  输入参数:       UCHAR *pucMsg, ULONG ulMsgLen, DHCPC_CTRLBLK *pstDhcpcContext
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_SendMsgToServer(UCHAR *pucMsg, ULONG ulMsgLen, DHCPC_CTRLBLK *pstDhcpcContext)
{
    in6_addr stDstAddr;    /* 目的地址 */
    in6_addr stSrcAddr;    /* 源地址 */
    ULONG ulPktLen = 0;    /* dhcp消息总长度 */
    ULONG ulRet = VOS_OK;
    USHORT usUdpMsgLen = 0;
    USHORT usCheckSumFresh = 0;
    IPV6HDR_S *pstIpv6Hdr = NULL;
    UDPHDR_S *pstUdpv6Hdr = NULL;
    TTF_MEM_ST        *pstTtfMem;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter, ulMsgLen = %u", ulMsgLen);

    /* dhcp消息总长度 = IP头长度 + UDP头长度 + dhcp报文长度 */
    ulPktLen = IPV6_HEADER_LEN + UDPV6_HEADER_LEN + ulMsgLen;

    pstTtfMem = TTF_MemBlkAlloc(MID_DHCPC, TTF_MEM_POOL_ID_UL_DATA, ulPktLen);
    if (VOS_NULL_PTR == pstTtfMem)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:TTF_MEM ALLOC FAIL!");
        return VOS_NULL_PTR;
    }

    VOS_MemSet(pstTtfMem->pData, 0x00, ulPktLen);

    /* 填充消息 预留出ip头和udp头 */
    pstIpv6Hdr = (IPV6HDR_S *)(pstTtfMem->pData);
    pstUdpv6Hdr = (UDPHDR_S *)(pstTtfMem->pData + IPV6_HEADER_LEN);

    /* Copy dhcp报文内容到TTFmemory */
    (VOID)VOS_MemCpy((UCHAR*)(pstTtfMem->pData + IPV6_HEADER_LEN + UDPV6_HEADER_LEN),
                      pucMsg, ulMsgLen);

    /* 填写UDP头内容 UDP头中长度应该是UDP头长度+消息长度 */
    usUdpMsgLen= (USHORT)(ulMsgLen + UDPV6_HEADER_LEN);
    pstUdpv6Hdr->uh_sULen = (SHORT)VOS_HTONS(usUdpMsgLen);
    pstUdpv6Hdr->uh_usDPort = DHCPV6_CLIENT_UDP_PORT;
    pstUdpv6Hdr->uh_usSPort = DHCPV6_SERVER_UDP_PORT;

    VOS_MemSet(&stSrcAddr, 0x00, sizeof(stSrcAddr));
    //VOS_MemCpy(&(stDstAddr), pstDhcpcContext->aulSrvIp, sizeof(in6_addr));
    //(VOID)UDPS_ConvertToSockAddr((SOCKADDRIN_S * )&stDstAddr, sizeof(SOCKADDR_IN6_S));
    //(VOID)UDPS_ConvertToSockAddr((SOCKADDRIN_S * )&stSrcAddr, sizeof(SOCKADDR_IN6_S));

    //if(ipv6_addr_any(&stSrcAddr))
    //{
        ipv6_addr_all_nodes(&stDstAddr);
    //}
    //else
    //{
    //    ipv6_addr_copy(&stDstAddr, &stSrcAddr);
    //}

    if (VOS_OK != ICMPv6_CheckSum((UCHAR *)pstIpv6Hdr, stSrcAddr, stDstAddr, (UCHAR *)pstUdpv6Hdr,
                                    usUdpMsgLen, &usCheckSumFresh, IPV6_UDP_PRO))
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:ICMPv6_CheckSum FAIL!");
        return VOS_ERR;
    }
    pstUdpv6Hdr->uh_usSum = usCheckSumFresh;


    /* 填写IP头内容 */
    *(ULONG*)pstIpv6Hdr = VOS_HTONL(0x60000000); /* version and etc */
    pstIpv6Hdr->payload_len = VOS_HTONS(usUdpMsgLen);
    pstIpv6Hdr->nexthdr = IPV6_UDP_PRO;
    pstIpv6Hdr->hop_limit = 255;
    ipv6_addr_copy(&(pstIpv6Hdr->saddr), &stSrcAddr);    /* todo 源地址暂时取不到 */
    ipv6_addr_copy(&(pstIpv6Hdr->daddr), &stDstAddr);

    /* Send to CDS */
    DHCPV6C_SendDhcpDlDatatoCds(pstTtfMem, ulPktLen,
                            pstDhcpcContext->enModemId, pstDhcpcContext->ucRabId);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return VOS_OK;
}


/*****************************************************************************
 *  函数名称:       DHCPV6C_CalcSuccSendPacketNum
 *  初稿完成:       2012-07-18
 *  作    者:       y00170683
 *  函数功能:       统计发消息成功计数
 *  输入参数:       ulDhpcv6MsgType
 *  输出参数:
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_CalcSuccSendPacketNum(ULONG ulDhpcv6MsgType)
{
    /* 消息计数 */
    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_PACKET_OK);

    switch (ulDhpcv6MsgType)
    {
        case DHCPV6_MSG_TYPE_SOLICIT :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_SOLICIT_OK);
            break;

        case DHCPV6_MSG_TYPE_REQUEST :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_REQUEST_OK);
            break;

        case DHCPV6_MSG_TYPE_RENEW :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_RENEW_OK);
            break;

        case DHCPV6_MSG_TYPE_RELEASE :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_RELEASE_OK);
            break;

        case DHCPV6_MSG_TYPE_DECLINE :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_DECLINE_OK);
            break;

        default:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_SERVER_OTHER_OK);
            break;
    }

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_CalcFailSendPacketNum
 *  初稿完成:       2012-07-18
 *  作    者:       y00170683
 *  函数功能:       统计发消息失败计数
 *  输入参数:       ulDhpcv6MsgType
 *  输出参数:
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_CalcFailSendPacketNum(ULONG ulDhpcv6MsgType)
{
    /* 消息计数 */
    switch (ulDhpcv6MsgType)
    {
        case DHCPV6_MSG_TYPE_SOLICIT :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_SOLICIT_ERR);
            break;

        case DHCPV6_MSG_TYPE_REQUEST :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_REQUEST_ERR);
            break;

        case DHCPV6_MSG_TYPE_RENEW :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_RENEW_ERR);
            break;

        case DHCPV6_MSG_TYPE_RELEASE :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_RELEASE_ERR);
            break;

        case DHCPV6_MSG_TYPE_DECLINE :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_DECLINE_ERR);
            break;

        default:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_SERVER_OTHER_ERR);
            break;
    }

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_SendPacket
 *  初稿完成:       2012-07-07
 *  作    者:       y00170683
 *  函数功能:       封装消息发包
 *  输入参数:       DHCPC_CTRLBLK *pstDhcpcContext, ULONG ulDhpcv6MsgType
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_SendPacket(DHCPC_CTRLBLK *pstDhcpcContext, ULONG ulDhpcv6MsgType)
{
    ULONG ulRet = VOS_OK;
    ULONG ulMsgLen = 0;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_PACKET_ENTER);

    /* 选择向哪个服务器发送消息 */
    ulRet = DHCPC_SelectAndGetServerCfg(pstDhcpcContext, pstDhcpcContext->aulSrvIp);
    if (VOS_OK != ulRet)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_PKT_SELECT_SVR_FAIL);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "[dhcpv6c-err]:call DHCPC_SelectAndSetServer err! ulRet=%u", ulRet);
        return ulRet;
    }

    DHCP_MemZero(g_pucDhcpv6cSendBuff, DHCPV6C_SEND_MSG_MAXLEN);

    /* 检查消息类型 */
    ulRet = DHCPV6C_CheckSendMsgType(ulDhpcv6MsgType);
    if (VOS_OK != ulRet)
    {
        return ulRet;
    }

    /* 填充消息 */
    DHCPV6C_FillMsg(g_pucDhcpv6cSendBuff, &ulMsgLen, ulDhpcv6MsgType, pstDhcpcContext);

    /* 封装buff,调用UDP接口发送 */
    /* ulRet = DHCPV6C_UdpOutPut(g_pucDhcpv6cSendBuff, ulMsgLen, pstDhcpcContext); */
    ulRet = DHCPV6C_SendMsgToServer(g_pucDhcpv6cSendBuff, ulMsgLen, pstDhcpcContext);

    /* 统计发送消息计数 */
    if (VOS_OK == ulRet)
    {
        /* 增加消息发送数 */
        (pstDhcpcContext->ucCurSvrSendCount)++;
        (pstDhcpcContext->ucTotalSendCount)++;

        DHCPV6C_CalcSuccSendPacketNum(ulDhpcv6MsgType);

        /*消息跟踪*/
        DHCPCv6_OmMsgTrc(g_pucDhcpv6cSendBuff,pstDhcpcContext, (UCHAR)ulDhpcv6MsgType,ulMsgLen, DHCPV6_MSG_DIRECTION_SEND);
    }
    else
    {
        DHCPV6C_CalcFailSendPacketNum(ulDhpcv6MsgType);
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit, ulRet = %u", ulRet);
    return ulRet;
}

#define _SEQUENCENUM_MANAGE_
/*****************************************************************************
 *  函数名称:       DHCPV6C_ReleaseNode
 *  初稿完成:       2012-07-09
 *  作    者:       y00170683
 *  函数功能:       释放SequenceNum节点到空闲链
 *  输入参数:       DHCPV6C_SEQNUM_FREELINK_S* pstFreeLink, VOS_UINT16 usIndex
 *  输出参数:       无
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_ReleaseNode(DHCPV6C_SEQNUM_FREELINK_S* pstFreeLink, USHORT usIndex, USHORT usTotalNum)
{
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter, usIndex = %u", usIndex);

    /*参数非法*/
    if(usTotalNum <= usIndex)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:usIndex = %u", usIndex);
        return;
    }

    /* 全部占用时,回收第一个节点至空闲链时把该节点设置为头节点 */
    if (usTotalNum == pstFreeLink->usUsedNum)
    {
        pstFreeLink->usFreeHead = usIndex;
    }
    else
    {
        /*加入链表尾*/
        pstFreeLink->pusNextNode[pstFreeLink->usFreeTail] = usIndex;
    }

    pstFreeLink->usFreeTail = usIndex;

    /* 最后将尾节点的下一个置为无效值 */
    pstFreeLink->pusNextNode[pstFreeLink->usFreeTail] = usTotalNum;

    if (pstFreeLink->usUsedNum > 0)
    {
        pstFreeLink->usUsedNum--;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_InitFreeLink
 *  初稿完成:       2012-07-09
 *  作    者:       y00170683
 *  函数功能:       初始化SequenceNum空闲链
 *  输入参数:       DHCPV6C_SEQNUM_FREELINK_S* pstFreeLink, USHORT usTotalNum
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_InitFreeLink(DHCPV6C_SEQNUM_FREELINK_S* pstFreeLink, USHORT usTotalNum)
{
    USHORT usIndex = 0;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    /* 申请空闲链内存 */
    pstFreeLink->pusNextNode = (USHORT *)DHCP_Malloc(DHCPC_HANDLE, sizeof(USHORT) * usTotalNum);
    if(VOS_NULL == pstFreeLink->pusNextNode)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c_err]:malloc err");
        return VOS_ERR;
    }
    VOS_MemSet(pstFreeLink->pusNextNode, DHCP_INVALID_USHORT, sizeof(USHORT) * usTotalNum);

    pstFreeLink->usUsedNum = usTotalNum;
    pstFreeLink->usFreeHead = usTotalNum;
    pstFreeLink->usFreeTail = usTotalNum;

    /* 初始化空闲链 */
    for(usIndex = 0; usIndex < usTotalNum; usIndex++)
    {
        DHCPV6C_ReleaseNode(pstFreeLink, usIndex, usTotalNum);
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_RebuildFreeLink
 *  初稿完成:       2012-08-01
 *  作    者:       y00170683
 *  函数功能:       重建SequenceNum空闲链
 *  输入参数:       DHCPV6C_SEQNUM_FREELINK_S* pstFreeLink, USHORT usTotalNum
 *  输出参数:       无
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_RebuildFreeLink(DHCPV6C_SEQNUM_FREELINK_S* pstFreeLink, USHORT usTotalNum)
{
    USHORT usIndex = 0;
    DHCPC_DebugPrint(PTM_LOG_INFO, "enter");

    VOS_MemSet(pstFreeLink->pusNextNode, DHCP_INVALID_USHORT, sizeof(USHORT) * usTotalNum);
    pstFreeLink->usUsedNum = usTotalNum;
    pstFreeLink->usFreeHead = usTotalNum;
    pstFreeLink->usFreeTail = usTotalNum;

    /* 重建空闲链 */
    for(usIndex = 0; usIndex < usTotalNum; usIndex++)
    {
        if (VOS_FALSE == g_pstDhcpv6cSeqContext[usIndex].ucbit2UsedFlg)
        {
            DHCPV6C_ReleaseNode(pstFreeLink, usIndex, usTotalNum);
        }
    }

    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_GetFreeNode
 *  初稿完成:       2012-07-09
 *  作    者:       y00170683
 *  函数功能:       获取SequenceNum空闲节点
 *  输入参数:       无
 *  输出参数:       无
 *  返回类型:       USHORT
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
USHORT DHCPV6C_GetFreeNode(DHCPV6C_SEQNUM_FREELINK_S* pstFreeLink)
{
    USHORT usIndex = 0;
    USHORT usTotalNum = DHCPV6C_MAX_SEQUENCE_NUM;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter");

    /* 正在使用数已经满规格 */
    if (pstFreeLink->usUsedNum >= usTotalNum)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TID_EXHAUST);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "usUsedNum = %u", pstFreeLink->usUsedNum);
        return usTotalNum;
    }

    /*链表异常*/
    if(usTotalNum <= pstFreeLink->usFreeHead)
    {
        /* 重建空闲链 */
        DHCPV6C_RebuildFreeLink(pstFreeLink, usTotalNum);

        /* 重建后依然异常,则分配失败 */
        if(usTotalNum <= pstFreeLink->usFreeHead)
        {
            DHCPC_DebugPrint(PTM_LOG_INFO, "usFreeHead = %u", pstFreeLink->usFreeHead);
            return usTotalNum;
        }
    }

    /*空闲链头下移*/
    usIndex = pstFreeLink->usFreeHead;
    pstFreeLink->usFreeHead = pstFreeLink->pusNextNode[usIndex];
    pstFreeLink->usUsedNum++;

    /* 已经分配了最后一个节点 */
    if (usTotalNum == pstFreeLink->usUsedNum)
    {
        pstFreeLink->usFreeHead = usTotalNum;
        pstFreeLink->usFreeTail = usTotalNum;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit, usIndex = %u", usIndex);
    return usIndex;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_AllocSeqNum
 *  初稿完成:       2012-07-09
 *  作    者:       y00170683
 *  函数功能:       分配SEQnum
 *  输入参数:       ULONG ulTeidc, UCHAR ucIpAddrType
 *  输出参数:       USHORT *pusSeqNum
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_AllocSeqNum(USHORT *pusSeqNum, ULONG ulTeidc, UCHAR ucIpAddrType)
{
    USHORT usIndex = DHCPV6C_MAX_SEQUENCE_NUM;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter, ulTeidc=%x, ucIpType=%d", ulTeidc, ucIpAddrType);

    if (NULL == pusSeqNum)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "NULL");
        return VOS_ERR;
    }

    /*获取空闲索引*/
    usIndex = DHCPV6C_GetFreeNode(&g_stDhcpv6cSeqNumLink);
    if(DHCPV6C_MAX_SEQUENCE_NUM <= usIndex)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "[dhcpv6c-err]:usIndex = %u", usIndex);
        return VOS_ERR;
    }

    g_pstDhcpv6cSeqContext[usIndex].ulTeidc = ulTeidc;
    g_pstDhcpv6cSeqContext[usIndex].ucbit2IpAddrType = ucIpAddrType;
    g_pstDhcpv6cSeqContext[usIndex].ucbit2UsedFlg = VOS_TRUE;
    g_pstDhcpv6cSeqContext[usIndex].ucbit4AgeingCnt = 0;

    *pusSeqNum = usIndex;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit, *pusSeqNum=%u, ulTeidc=%x, ucIpType=%d", *pusSeqNum, ulTeidc, ucIpAddrType);
    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_QuryTeidcBySeqNum
 *  初稿完成:       2012-07-09
 *  作    者:       y00170683
 *  函数功能:       根据SequenceNum确定teidc
 *  输入参数:       USHORT usSeqNum
 *  输出参数:       ULONG *pulTeidc, UCHAR *pucIpAddrType
 *  返回类型:       ULONG
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
ULONG DHCPV6C_QuryTeidcBySeqNum(USHORT usSeqNum, ULONG *pulTeidc, UCHAR *pucIpAddrType)
{
    USHORT usTotalNum = DHCPV6C_MAX_SEQUENCE_NUM;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter, usSeqNum = %u", usSeqNum);

    if ((NULL == pulTeidc) || (NULL == pucIpAddrType))
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "NULL");
        return VOS_ERR;
    }

    if(usTotalNum <= usSeqNum)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:usSeqNum = %u", usSeqNum);
        return VOS_ERR;
    }

    if(VOS_FALSE == g_pstDhcpv6cSeqContext[usSeqNum].ucbit2UsedFlg)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:usSeqNum = %u, ulTeidc = 0x%x, UsedFlag = %u, IpType = %u, AgeingCnt = %u",
                        usSeqNum, g_pstDhcpv6cSeqContext[usSeqNum].ulTeidc,
                        g_pstDhcpv6cSeqContext[usSeqNum].ucbit2UsedFlg,
                        g_pstDhcpv6cSeqContext[usSeqNum].ucbit2IpAddrType,
                        g_pstDhcpv6cSeqContext[usSeqNum].ucbit4AgeingCnt);
        return VOS_ERR;
    }


    *pulTeidc = g_pstDhcpv6cSeqContext[usSeqNum].ulTeidc;
    *pucIpAddrType = g_pstDhcpv6cSeqContext[usSeqNum].ucbit2IpAddrType;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit, UsedFlag = %u, ulTeidc = 0x%x, ucIpType = %u, AgeingCnt = %u",
                       g_pstDhcpv6cSeqContext[usSeqNum].ucbit2UsedFlg,
                       *pulTeidc, *pucIpAddrType, g_pstDhcpv6cSeqContext[usSeqNum].ucbit4AgeingCnt);
    return VOS_OK;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_FreeSeqNum
 *  初稿完成:       2012-07-09
 *  作    者:       y00170683
 *  函数功能:       释放SequenceNum节点到空闲链
 *  输入参数:       usSeqNum
 *  输出参数:       无
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_FreeSeqNum(USHORT usSeqNum)
{
    USHORT usTotalNum = DHCPV6C_MAX_SEQUENCE_NUM;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "enter, usSeqNum = %u", usSeqNum);

    if(usTotalNum <= usSeqNum)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:usSeqNum = %u", usSeqNum);
        return;
    }

    if(VOS_FALSE == g_pstDhcpv6cSeqContext[usSeqNum].ucbit2UsedFlg)
    {
        DHCPC_DebugPrint(PTM_LOG_INFO, "usSeqNum = %u, ulTeidc = 0x%x, UsedFlag = %u, IpType = %u, AgeingCnt = %u",
                        usSeqNum, g_pstDhcpv6cSeqContext[usSeqNum].ulTeidc,
                        g_pstDhcpv6cSeqContext[usSeqNum].ucbit2UsedFlg,
                        g_pstDhcpv6cSeqContext[usSeqNum].ucbit2IpAddrType,
                        g_pstDhcpv6cSeqContext[usSeqNum].ucbit4AgeingCnt);
        return;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "ulTeidc = 0x%x, UsedFlag = %u, IpType = %u, AgeingCnt = %u",
                        g_pstDhcpv6cSeqContext[usSeqNum].ulTeidc,
                        g_pstDhcpv6cSeqContext[usSeqNum].ucbit2UsedFlg,
                        g_pstDhcpv6cSeqContext[usSeqNum].ucbit2IpAddrType,
                        g_pstDhcpv6cSeqContext[usSeqNum].ucbit4AgeingCnt);

    DHCP_MemZero(&g_pstDhcpv6cSeqContext[usSeqNum], sizeof(DHCPV6C_SEQNUM_CONTEXT_S));
    DHCPV6C_ReleaseNode(&g_stDhcpv6cSeqNumLink, usSeqNum, usTotalNum);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}

/*****************************************************************************
 *  函数名称:       DHCPV6C_AgeingSeqNum
 *  初稿完成:       2012-09-10
 *  作    者:       y00170683
 *  函数功能:       SequenceNum老化处理
 *  输入参数:       usSeqNum
 *  输出参数:       无
 *  返回类型:       VOID
 *  其他说明:       无
 *  调用函数:
 *  主调函数:
*****************************************************************************/
VOID DHCPV6C_AgeingSeqNum()
{
    ULONG ulSeqNum = 0;

    for (ulSeqNum = 0 ; ulSeqNum < DHCPV6C_MAX_SEQUENCE_NUM; ulSeqNum++)
    {
        if (VOS_TRUE == g_pstDhcpv6cSeqContext[ulSeqNum].ucbit2UsedFlg)
        {
            /* 大于等于DHCPC_AGEING_SEQNUM_MAX_CNT时说明seqnum残留,需要释放 */
            g_pstDhcpv6cSeqContext[ulSeqNum].ucbit4AgeingCnt++;
            if (g_pstDhcpv6cSeqContext[ulSeqNum].ucbit4AgeingCnt >= DHCPC_AGEING_SEQNUM_MAX_CNT)
            {
                DHCPV6C_FreeSeqNum((USHORT)ulSeqNum);
                DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEQNUM_REMAIN);
                DHCPC_DebugPrint(PTM_LOG_ERR, "[dhcpv6c-err]:ulSeqNum = %u", ulSeqNum);
            }
        }
    }

    return;
}

#ifdef    __cplusplus
}
#endif

