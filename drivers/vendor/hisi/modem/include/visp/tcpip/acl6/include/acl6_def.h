/*************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              acl6_def.h
 *
 *  Project Code: VISP1.8
 *   Module Name: ACL6
 *  Date Created: 
 *        Author: 
 *   Description: 宏定义
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *
 ************************************************************************/
#ifndef _ACL6_DEF_H_
#define _ACL6_DEF_H_

#ifdef  __cplusplus
extern "C" 
{
#endif

#include "acl6/include/acl6_cbb_api.h"


/**********************************************************
*   规格类型相关宏定义
***********************************************************/
/* 规则类型ID取值范围 */
#define ACL6_MIN_TYPEID  1
#define ACL6_MAX_TYPEID  3

/**********************************************************
*   规格组相关宏定义
***********************************************************/
/* 最大规则组序号总和 */
#define ACL6_MAX_GROUPNUM_SUM  9999

/* 缺省规则类型的规则组序号缺省值 */
#define ACL6_BAS_DEFAULT_MIN     2000
#define ACL6_BAS_DEFAULT_MAX     2999

#define ACL6_ADV_DEFAULT_MIN     3000
#define ACL6_ADV_DEFAULT_MAX     3999

#define ACL6_IF_DEFAULT_MIN      1000
#define ACL6_IF_DEFAULT_MAX      1999

/* 规则组步长范围 */
#define ACL6_MIN_STEP    1
#define ACL6_MAX_STEP    20

/* 产品需要使用默认步长,所以在API中定义一份,注意该宏定义必须与acl6_cbb_api.h中的ACL6_DEFAULT_STEP定义保持一致 */
/* 规则组默认步长 */
#ifndef ACL6_DEFAULT_STEP
#define ACL6_DEFAULT_STEP 5
#endif

/**********************************************************
*   规格相关宏定义
***********************************************************/
/* 全局最大规则数 */
#define ACL6_MAX_ALLRULE_SUM   10000

/* 一个规则组下最大规则数 */
#define ACL6_MAX_GROUPRULE_SUM   256

/* 端口号取值范围 */
#define ACL6_MIN_PORTNUM 0
#define ACL6_MAX_PORTNUM 65535

/* 协议号取值范围 */
#define ACL6_MIN_PROID    0
#define ACL6_MAX_PROID    255

/* Addr Mask Len取值范围 */
#define ACL6_MIN_MASK_LEN 0
#define ACL6_MAX_MASK_LEN 128

/* Hop Limit取值范围 */
#define ACL6_MIN_HOPLM 0
#define ACL6_MAX_HOPLM 255

/* Traffic Class取值范围 */
#define ACL6_MIN_CLASS 0
#define ACL6_MAX_CLASS 255

/* 规则组是否存在 */
#define ACL6_GROUP_IS_EXIST(pstGroup) ((pstGroup) != NULL)

/* IP6首部Next Header 字段的宏定义 */
#define ACL6_HD_HOP_BY_HOP  0
#define ACL6_HD_DST_HD      60
#define ACL6_HD_ROUTE_HD    43
#define ACL6_HD_FRAGMENT    44    /* IPv6 Fragmentation header */
#define ACL6_HD_AH          51
#define ACL6_HD_ESP         50
#define ACL6_HD_NONE        59    /* IPv6 No next header */
#define ACL6_HD_TCP6        6
#define ACL6_HD_UDP6        17
#define ACL6_HD_ICMP6       58
#define ACL6_HD_SCTP        132

/* ICMP6 Code号取值范围 ，有效范围值为:0,1,2,3,4*/
#define ACL6_MIN_ICMP6CODE  0
#define ACL6_MAX_ICMP6CODE  4

/* ICMP6 Type号取值范围 */
#define ACL6_MIN_ICMP6TYPE  0
#define ACL6_MAX_ICMP6TYPE  255

/* 源与目的通用的内部错误码 */
#define ACL6_PORT_TYPE_ERR    1   /* 端口匹配类型非法 */
#define ACL6_PORT_RANGE_ERR   2   /* 端口号配置非法 */


/* x must be a array that have 4 ULONG element */
#define ACL6_ADDRESS_HTON(x) \
{\
    (x)[0] = VOS_HTONL((x)[0]);\
    (x)[1] = VOS_HTONL((x)[1]);\
    (x)[2] = VOS_HTONL((x)[2]);\
    (x)[3] = VOS_HTONL((x)[3]);\
}

/* x must be a array that have 4 ULONG element */
#define ACL6_ADDRESS_NTOH(x) \
{\
    (x)[0] = VOS_NTOHL((x)[0]);\
    (x)[1] = VOS_NTOHL((x)[1]);\
    (x)[2] = VOS_NTOHL((x)[2]);\
    (x)[3] = VOS_NTOHL((x)[3]);\
}


/**********************************************************
*   忽略位相关宏定义，在报文匹配时可对指定字段不予比较
***********************************************************/
/* 获取忽略位标志 */
#define ACL6_ING_SIP(ulByte)         (ACL6_SIPByte & (ulByte))
#define ACL6_ING_DIP(ulByte)         (ACL6_DIPByte & (ulByte))
#define ACL6_ING_PRO(ulByte)         (ACL6_PROByte & (ulByte))
#define ACL6_ING_HLM(ulByte)         (ACL6_HLMByte & (ulByte))
#define ACL6_ING_CLS(ulByte)         (ACL6_CLSByte & (ulByte))
#define ACL6_ING_SPORT(ulByte)       (ACL6_SPORTByte & (ulByte))
#define ACL6_ING_DPORT(ulByte)       (ACL6_DPORTByte & (ulByte))
#define ACL6_ING_VRF(ulByte)         (ACL6_VRFByte & (ulByte))


#define ACL6_IS_IPADDRANY(pAddr,lRetResult)\
{\
    CHAR szAddrZero[ACL6_IPV6_ADDR_LEN];\
    (VOID)TCPIP_Mem_Set(szAddrZero,0,ACL6_IPV6_ADDR_LEN);\
    (VOID)VOS_Mem_Cmp((CHAR *)pAddr,szAddrZero,ACL6_IPV6_ADDR_LEN,&lRetResult);\
}

#define ACL6_FILL_GROUP_OUT_INFO(pstGroup,pstGroupInfo)\
{\
    pstGroupInfo->ulTypeID = pstGroup->ulTypeID;\
    pstGroupInfo->ulGroupIndex = pstGroup->ulGroupIndex;\
    pstGroupInfo->ulMatchOrder = pstGroup->ulMatchOrder;\
    pstGroupInfo->ulStep = pstGroup->ulIndexStep;\
    if (NULL != pstGroup->pACL6Description)\
    {\
        (VOID)TCPIP_strncpy(pstGroupInfo->szDescription, ACL6_DESCRIPTIONSTR_LEN + 1, pstGroup->pACL6Description, ACL6_DESCRIPTIONSTR_LEN);\
        pstGroupInfo->szDescription[ACL6_DESCRIPTIONSTR_LEN] = 0;\
    }\
    else\
    {\
        (VOID)TCPIP_Mem_Set(pstGroupInfo->szDescription, 0, (ACL6_DESCRIPTIONSTR_LEN + 1));\
    }\
    pstGroupInfo->ulRuleNum = pstGroup->ulRuleNum;\
}

/* Modify for DTS2011111806790, by zhaoyue00171897, at 2011-11-18. 修改原因: 掩码长度为128时会导致内存越界 */
#define ACL6_SUBADDR_BUILD(pAddr,ulMaskLen,pSubAddr)\
{\
    CHAR szMask[ACL6_IPV6_ADDR_LEN];\
    UCHAR k,ucLastByte = 0xFF;\
    CHAR *pDst,*pSrc;\
    ULONG ulTemp = ACL6_IPV6_ADDR_LEN/2;\
    (VOID)TCPIP_Mem_Set((CHAR*)pSubAddr, 0,ACL6_IPV6_ADDR_LEN);\
    (VOID)TCPIP_Mem_Set(szMask, 0,ACL6_IPV6_ADDR_LEN);\
    (VOID)TCPIP_Mem_Set(szMask, ucLastByte, (ulMaskLen / ulTemp));\
    if ((ulMaskLen) % ulTemp)\
    {\
        ucLastByte = (CHAR)(ucLastByte << (ulTemp - ((ulMaskLen) % ulTemp)));\
        szMask[(ulMaskLen / ulTemp)] = ucLastByte;\
    }\
    for (k = 0; k < ACL6_IPV6_ADDR_LEN; k++)\
    {\
        pSrc = ((CHAR*)(pAddr)+k);\
        pDst = ((CHAR*)(pSubAddr)+k);\
        *pDst = (CHAR)(*pSrc & szMask[k]);\
    }\
}

#define ACL6_GET_TRAFFICCLASS(ulTclassFlow) ((VOS_NTOHL(ulTclassFlow) & 0x0ff00000)>> 20)
#define ACL6_GET_FRAGMENTOFF(usOffFlag) (VOS_NTOHS(usOffFlag) & 0xfff8)

#ifdef  __cplusplus
}
#endif
   
#endif
