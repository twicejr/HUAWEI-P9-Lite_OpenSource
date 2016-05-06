/************************************************************************
*                                                                      *
*                             pppc_eap_aka.c                                    *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2015/11/9                                      *
*  Author:             GENGXIAOLI                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP的EAP-AKA鉴权方法模块                                *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了EAP-AKA/AKA'协议模块的全部接口函数和内部处理函数              *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"
#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "vrpcfg.h"
#include "pppc_sha1.h"
#include "pppc_sha256.h"
#include "pppc_eap_aka.h"
#include "pppc_eap_fun.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifndef __STATIC_
#if defined(DMT) || defined(__UT_CENTER__)
#define __STATIC_
#else
#define __STATIC_ static
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PPPC_EAP_AKA_C
/*lint +e767*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* EAP Method Output */
PPPC_EAP_METHOD_OUTPUT_STRU             g_stEAPAkaMethodOutput;

/* EAP-AKA的实体结构 */
PPPC_EAP_AKA_DATA_INFO_STRU             g_stPppcEapAkaDataInfo;

/* 从EAP Request包里解出来的EAP-AKA属性信息 */
__STATIC_ PPPC_EAP_AKA_ATTRS_STRU                 g_stPppcEapAkaPktAttrInfo;

const PPPC_EAP_AKA_ATTRIBUTE_DATA_STRU g_stAttributeHandleTab[]=
{
    {PPPC_EAP_AKA_AT_RAND,                   {0, 0, 0}, PPPC_EAP_AKA_AttRandParse},
    {PPPC_EAP_AKA_AT_AUTN,                   {0, 0, 0}, PPPC_EAP_AKA_AttAutnParse},
    {PPPC_EAP_AKA_AT_PADDING,                {0, 0, 0}, PPPC_EAP_AKA_AttPaddingParse},
    {PPPC_EAP_AKA_AT_PERMANENT_ID_REQ,       {0, 0, 0}, PPPC_EAP_AKA_AttPermanentParse},
    {PPPC_EAP_AKA_AT_MAC,                    {0, 0, 0}, PPPC_EAP_AKA_AttMacParse},
    {PPPC_EAP_AKA_AT_NOTIFICATION,           {0, 0, 0}, PPPC_EAP_AKA_AttNotificationParse},
    {PPPC_EAP_AKA_AT_ANY_ID_REQ,             {0, 0, 0}, PPPC_EAP_AKA_AttAnyParse},
    {PPPC_EAP_AKA_AT_FULLAUTH_ID_REQ,        {0, 0, 0}, PPPC_EAP_AKA_AttFullauthParse},
    {PPPC_EAP_AKA_AT_COUNTER,                {0, 0, 0}, PPPC_EAP_AKA_AttCounterParse},
    {PPPC_EAP_AKA_AT_NONCE_S,                {0, 0, 0}, PPPC_EAP_AKA_AttNonceSParse},
    {PPPC_EAP_AKA_AT_KDF_INPUT,              {0, 0, 0}, PPPC_EAP_AKA_AttKdfInputParse},
    {PPPC_EAP_AKA_AT_KDF,                    {0, 0, 0}, PPPC_EAP_AKA_AttKdfParse},
    {PPPC_EAP_AKA_AT_IV,                     {0, 0, 0}, PPPC_EAP_AKA_AttIvParse},
    {PPPC_EAP_AKA_AT_ENCR_DATA,              {0, 0, 0}, PPPC_EAP_AKA_AttEncrParse},
    {PPPC_EAP_AKA_AT_NEXT_PSEUDONYM,         {0, 0, 0}, PPPC_EAP_AKA_AttNextPseudonymParse},
    {PPPC_EAP_AKA_AT_NEXT_REAUTH_ID,         {0, 0, 0}, PPPC_EAP_AKA_AttNextReauthParse},
    {PPPC_EAP_AKA_AT_CHECKCODE,              {0, 0, 0}, PPPC_EAP_AKA_AttCheckcodeParse},
    {PPPC_EAP_AKA_AT_RESULT_IND,             {0, 0, 0}, PPPC_EAP_AKA_AttResultParse},
    {PPPC_EAP_AKA_AT_BIDDING,                {0, 0, 0}, PPPC_EAP_AKA_AttBiddingParse}
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_MntnTraceInfo
 功能描述  : EAP-AKA鉴权勾包
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-11-18
    作    者   : h00309869
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_MntnTraceInfo
(
    PPPC_EAP_AKA_AUTH_PARA_STRU        *pstEapAkaAuthPara,
    PPPC_EAP_AKA_KEY_DATA_STRU         *pstEapAkaKey
)
{
    PPPC_EAP_AKA_TRACE_INFO_STRU       *pstTraceInfo = VOS_NULL_PTR;


    pstTraceInfo = (PPPC_EAP_AKA_TRACE_INFO_STRU *)PPP_Malloc(sizeof(PPPC_EAP_AKA_TRACE_INFO_STRU));
    if (VOS_NULL_PTR == pstTraceInfo)
    {
        PPPC_WARNING_LOG("EAP-AKA: malloc trace info fail");

        return;
    }

    PS_MEM_SET(pstTraceInfo, 0, sizeof(PPPC_EAP_AKA_TRACE_INFO_STRU));

    pstTraceInfo->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstTraceInfo->ulSenderPid       = MSPS_PID_PPPC;
    pstTraceInfo->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstTraceInfo->ulReceiverPid     = MSPS_PID_PPPC;
    pstTraceInfo->ulLength          = sizeof(PPPC_EAP_AKA_TRACE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstTraceInfo->enMsgId           = ID_CTTF_PPPC_TRACE_EAP_AKA_INFO;
    pstTraceInfo->usVersion         = CTTF_PPPC_TRACE_DATA_VERSION;

    /* 勾取鉴权的一些参数信息 */
    PS_MEM_CPY(&(pstTraceInfo->stEapAkaAuthPara), pstEapAkaAuthPara, sizeof(PPPC_EAP_AKA_AUTH_PARA_STRU));

    /* 勾取EAP-AKA鉴权过程中的Key信息 */
    PS_MEM_CPY(&(pstTraceInfo->stEapAkaKey), pstEapAkaKey, sizeof(PPPC_EAP_AKA_KEY_DATA_STRU));

    PPP_MNTN_TRACE_MSG(pstTraceInfo);

    PPP_Free(pstTraceInfo);
    pstTraceInfo = VOS_NULL_PTR;

    (VOS_VOID)pstTraceInfo;
    return;
}


/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_PRIME_DeriveKeys
 功能描述  : 计算EAP-AKA‘全鉴权参数
 输入参数  : pucIdentity        网侧携带的AT_IDENTITY
             ucIdentityLen      网侧携带的AT_IDENTITY的长度
             pstEapAkaAuthPara   网侧携带过来的相关参数结构体
             pstEapAkaKey        运算所需KEY的结构体
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_PRIME_DeriveKeys
(
    VOS_UINT8                          *pucIdentity,
    VOS_UINT16                          usIdentityLen,
    PPPC_EAP_AKA_AUTH_PARA_STRU        *pstEapAkaAuthPara,
    PPPC_EAP_AKA_KEY_DATA_STRU         *pstEapAkaKey
)
{
    VOS_UINT8                           ucCur;
    VOS_UINT8                           aucKey[PPPC_EAP_AKA_IK_AND_CK_LEN];
    VOS_UINT8                           aucHash[PPPC_SHA256_MAC_LEN];
    const VOS_UINT8                     aucPortion[] = {'E','A','P','-','A','K','A','\''}; /* PRF参数 */
    VOS_UINT16                          usNetworkNameLen;
    const VOS_UINT8                     aucSqnLen[PPPC_EAP_AKA_S_L_LEN] = {0x00, 0x06};
    VOS_UINT8                           aucMK[PPPC_EAP_AKA_PRIME_MK_LEN];
    VOS_UINT8                           ucFC = 0x20;                            /* 生成IK',CK'的参数，协议规定为0x20 */
    VOS_UINT32                          ulRet;
    PPPC_SHA256_PARA_STRU               stPara;


    /*
       3GPP TS 33.402 V9.7.0 第45页

       CK' || IK' = HMAC-SHA-256(Key, S)
       S = FC || P0 || L0 || P1 || L1 || ... || Pn || Ln
       Key = CK || IK
       FC = 0x20
       P0 = access network identity (3GPP TS 24.302)
       L0 = length of acceess network identity (2 octets, big endian)
       P1 = SQN xor AK (if AK is not used, AK is treaded as 000..0
       L1 = 0x00 0x06
    */

    if ((pstEapAkaAuthPara->usNetworkNameLen >= PPPC_EAP_AKA_NETNAME_MAX_LEN)
        || (usIdentityLen >= PPPC_EAP_AKA_IDENTITY_REC_LEN))
    {
        PPPC_WARNING_LOG2("The length of Network Name or Identity out of range,",
            pstEapAkaAuthPara->usNetworkNameLen, usIdentityLen);
        return VOS_ERR;
    }

    /* 初始化 Key */
    PS_MEM_SET(aucKey, 0x00, sizeof(aucKey));

    /* Key = CK || IK */
    PS_MEM_CPY(aucKey, pstEapAkaKey->aucCK, PPPC_EAP_AKA_CK_LEN);
    PS_MEM_CPY(aucKey + PPPC_EAP_AKA_CK_LEN, pstEapAkaKey->aucIK, PPPC_EAP_AKA_IK_LEN);

    /* 初始化 S,Hash */
    PS_MEM_SET(aucHash, 0x00, sizeof(aucHash));

    /* S = FC || P0 || L0 || P1 || L1 || ... || Pn || Ln */
    stPara.ucNum = 5;

    stPara.apucAdrr[0]  = (VOS_UINT8 *)&ucFC;
    stPara.aulLen[0]    = sizeof(ucFC);

    stPara.apucAdrr[1]  = pstEapAkaAuthPara->aucNetworkName;
    stPara.aulLen[1]    = pstEapAkaAuthPara->usNetworkNameLen;

    usNetworkNameLen = VOS_HTONS(pstEapAkaAuthPara->usNetworkNameLen);
    stPara.apucAdrr[2]  = (VOS_UINT8 *)&usNetworkNameLen;
    stPara.aulLen[2]    = PPPC_EAP_AKA_S_L_LEN;

    stPara.apucAdrr[3]  = pstEapAkaAuthPara->aucAutn;
    stPara.aulLen[3]    = PPPC_EAP_AKA_SQN_LEN;

    stPara.apucAdrr[4]  = (VOS_UINT8 *)aucSqnLen;
    stPara.aulLen[4]    = PPPC_EAP_AKA_S_L_LEN;


    ulRet = PPPC_HMAC_SHA256(aucKey, sizeof(aucKey), &stPara, aucHash);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("DeriveKeys When HAMAC_SHA256 Error!");
        return VOS_ERR;
    }

    PS_MEM_CPY(pstEapAkaKey->aucCKPrime, aucHash, PPPC_EAP_AKA_CK_LEN);
    PS_MEM_CPY(pstEapAkaKey->aucIKPrime, aucHash + PPPC_EAP_AKA_CK_LEN, PPPC_EAP_AKA_IK_LEN);

    /*
       rfc5448 第10页

       MK = PRF'(IK'|CK',"EAP-AKA'"|Identity)
       K_encr = MK[0..127]
       K_aut  = MK[128..383]
       K_re   = MK[384..639]
       MSK    = MK[640..1151]
       EMSK   = MK[1152..1663]
    */

    /* 初始化 MK */
    PS_MEM_SET(aucMK, 0x00, sizeof(aucMK));

    /* 初始化 Key */
    PS_MEM_SET(aucKey, 0x00, sizeof(aucKey));

    /* Key = IK' | CK' */
    PS_MEM_CPY(aucKey, pstEapAkaKey->aucIKPrime, PPPC_EAP_AKA_IK_LEN);
    PS_MEM_CPY(aucKey + PPPC_EAP_AKA_IK_LEN, pstEapAkaKey->aucCKPrime, PPPC_EAP_AKA_CK_LEN);

    stPara.ucNum        = 2;

    stPara.apucAdrr[0]  = (VOS_UINT8 *)aucPortion;
    stPara.aulLen[0]    = PPPC_EAP_AKA_PRF_STR_LEN;

    stPara.apucAdrr[1]  = pucIdentity;
    stPara.aulLen[1]    = usIdentityLen;

    ulRet = PPPC_EAP_PRF_PRIME(aucKey, &stPara, aucMK, PPPC_EAP_AKA_PRIME_MK_LEN);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("DeriveKeys When PRF' Error!");
        return VOS_ERR;
    }

    ucCur = 0;

    PS_MEM_CPY(pstEapAkaKey->aucK_encr, aucMK, PPPC_EAP_AKA_K_ENCR_LEN);
    ucCur += PPPC_EAP_AKA_K_ENCR_LEN;

    PS_MEM_CPY(pstEapAkaKey->aucPrimeK_aut, aucMK + ucCur, PPPC_EAP_AKA_PRIME_K_AUT_LEN);
    ucCur += PPPC_EAP_AKA_PRIME_K_AUT_LEN;

    PS_MEM_CPY(pstEapAkaKey->aucK_re, aucMK + ucCur, PPPC_EAP_AKA_PRIME_K_RE_LEN);
    ucCur += PPPC_EAP_AKA_PRIME_K_RE_LEN;

    PS_MEM_CPY(pstEapAkaKey->aucMSK, aucMK + ucCur, PPPC_EAP_AKA_MSK_LEN);
    ucCur +=PPPC_EAP_AKA_MSK_LEN;

    PS_MEM_CPY(pstEapAkaKey->aucEMSK, aucMK + ucCur, PPPC_EAP_AKA_EMSK_LEN);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_PRIME_DeriveKeys_Reauth
 功能描述  : 计算EAP-AKA‘重鉴权参数
 输入参数  : pucIdentity        网侧携带的AT_IDENTITY
             ucIdentityLen      网侧携带的AT_IDENTITY的长度
             pstEapAkaAuthPara   网侧携带过来的相关参数结构体
             pstEapAkaKey        运算所需KEY的结构体
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_PRIME_DeriveKeys_ReAuth
(
    VOS_UINT8                          *pucIdentity,
    VOS_UINT16                          usIdentityLen,
    PPPC_EAP_AKA_AUTH_PARA_STRU        *pstEapAkaAuthPara,
    PPPC_EAP_AKA_KEY_DATA_STRU         *pstEapAkaKey
)
{
    PPPC_SHA256_PARA_STRU               stPara;
    VOS_UINT8                           aucMK[PPPC_EAP_AKA_REAUTH_MK_LEN];
    const VOS_UINT8                     aucPortion[] ={'E','A','P','-','A','K','A','\'',' ','r','e','a','u','t','h'};
    VOS_UINT16                          usCounter;
    VOS_UINT32                          ulRet;


    /*
       rfc5448 第10页

       MK = PRF'(K_re,"EAP-AKA' re-auth"|Identity|counter|NONCE_S)
       MSK  = MK[0..511]
       EMSK = MK[512..1023]
    */
    if (usIdentityLen >= PPPC_EAP_AKA_IDENTITY_REC_LEN)
    {
        PPPC_WARNING_LOG1("The length of Identity out of range,%d.", usIdentityLen);
        return VOS_ERR;
    }

    PS_MEM_SET(aucMK, 0x00, sizeof(aucMK));

    stPara.ucNum        = 4;

    stPara.apucAdrr[0]  = (VOS_UINT8 *)aucPortion;
    stPara.aulLen[0]    = PPPC_EAP_AKA_REAUTH_PRF_STR_LEN;

    stPara.apucAdrr[1]  = pucIdentity;
    stPara.aulLen[1]    = usIdentityLen;

    usCounter = VOS_HTONS(pstEapAkaAuthPara->usCounter);
    stPara.apucAdrr[2]  = (VOS_UINT8 *)&usCounter;
    stPara.aulLen[2]    = PPPC_EAP_AKA_COUNTER_LEN;

    stPara.apucAdrr[3]  = pstEapAkaAuthPara->aucNonce_s;
    stPara.aulLen[3]    = PPPC_EAP_AKA_NONCE_S_LEN;


    ulRet = PPPC_EAP_PRF_PRIME(pstEapAkaKey->aucK_re, &stPara, aucMK, PPPC_EAP_AKA_REAUTH_MK_LEN);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("DeriveKeys ReAuth When PRF' Error!");
        return VOS_ERR;
    }

    PS_MEM_CPY(pstEapAkaKey->aucMSK, aucMK, PPPC_EAP_AKA_MSK_LEN);

    PS_MEM_CPY(pstEapAkaKey->aucEMSK, aucMK + PPPC_EAP_AKA_MSK_LEN, PPPC_EAP_AKA_EMSK_LEN);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_DeriveKeys
 功能描述  : 计算EAP-AKA全鉴权参数
 输入参数  : pucIdentity        网侧携带的AT_IDENTITY
             ucIdentityLen      网侧携带的AT_IDENTITY的长度
             pstEapAkaAuthPara   网侧携带过来的相关参数结构体
             pstEapAkaKey        运算所需KEY的结构体
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_DeriveKeys
(
    VOS_UINT8                          *pucIdentity,
    VOS_UINT16                          usIdentityLen,
    PPPC_EAP_AKA_AUTH_PARA_STRU        *pstEapAkaAuthPara,
    PPPC_EAP_AKA_KEY_DATA_STRU         *pstEapAkaKey
)
{
    PPPC_SHA1_PARA_STRU                 stPara;
    VOS_UINT8                           aucBuf[PPPC_EAP_AKA_BUF_LEN];
    VOS_UINT8                           ucCur;
    VOS_UINT32                          ulRet;


    /*
       rfc4187 第43页
       MK = SHA1(Identity|IK|CK)
    */

    if (usIdentityLen >= PPPC_EAP_AKA_IDENTITY_REC_LEN)
    {
        PPPC_WARNING_LOG1("The length of Identity out of range,%d.", usIdentityLen);
        return VOS_ERR;
    }

    PS_MEM_SET(pstEapAkaKey->aucMk, 0x00, sizeof(pstEapAkaKey->aucMk));

    stPara.ucNum        = 3;

    stPara.apucAdrr[0]  = pucIdentity;
    stPara.aulLen[0]    = usIdentityLen;

    stPara.apucAdrr[1]  = pstEapAkaKey->aucIK;
    stPara.aulLen[1]    = PPPC_EAP_AKA_IK_LEN;

    stPara.apucAdrr[2]  = pstEapAkaKey->aucCK;
    stPara.aulLen[2]    = PPPC_EAP_AKA_CK_LEN;


    ulRet = PPPC_SHA1(&stPara, pstEapAkaKey->aucMk);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("DeriveKeys When SHA1 Error!");
        return VOS_ERR;
    }

    PS_MEM_SET(aucBuf, 0x00, sizeof(aucBuf));

    ulRet = PPPC_EAP_PRF(pstEapAkaKey->aucMk, PPPC_EAP_AKA_MK_LEN, aucBuf, sizeof(aucBuf));
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("DeriveKeys When PRF Error!");
        return VOS_ERR;
    }

    ucCur = 0;
    PS_MEM_CPY(pstEapAkaKey->aucK_encr, aucBuf, PPPC_EAP_AKA_K_ENCR_LEN);
    ucCur += PPPC_EAP_AKA_K_ENCR_LEN;
    PS_MEM_CPY(pstEapAkaKey->aucK_aut, aucBuf + ucCur, PPPC_EAP_AKA_K_AUT_LEN);
    ucCur += PPPC_EAP_AKA_K_AUT_LEN;
    PS_MEM_CPY(pstEapAkaKey->aucMSK, aucBuf + ucCur, PPPC_EAP_AKA_MSK_LEN);
    ucCur += PPPC_EAP_AKA_MSK_LEN;
    PS_MEM_CPY(pstEapAkaKey->aucEMSK, aucBuf + ucCur, PPPC_EAP_AKA_EMSK_LEN);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_DeriveKeys
 功能描述  : 计算EAP-AKA重鉴权参数
 输入参数  : pucIdentity        网侧携带的AT_IDENTITY
             ucIdentityLen      网侧携带的AT_IDENTITY的长度
             pstEapAkaAuthPara   网侧携带过来的相关参数结构体
             pstEapAkaKey        运算所需KEY的结构体
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月06日
    作    者   : t00359887
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_DeriveKeys_ReAuth
(
    VOS_UINT8                          *pucIdentity,
    VOS_UINT16                          usIdentityLen,
    PPPC_EAP_AKA_AUTH_PARA_STRU        *pstEapAkaAuthPara,
    PPPC_EAP_AKA_KEY_DATA_STRU         *pstEapAkaKey
)
{
    PPPC_SHA1_PARA_STRU                 stPara;
    VOS_UINT8                           aucXkey[PPPC_SHA1_MAC_LEN];
    VOS_UINT8                           aucBuf[PPPC_EAP_AKA_BUF_LEN];
    VOS_UINT16                          usCounter;
    VOS_UINT8                           ucCur;
    VOS_UINT32                          ulRet;


    /*
       rfc4187 第45页
       XKEY' = SHA1(Identity|counter|NONCE_S|MK)
    */

    if (usIdentityLen >= PPPC_EAP_AKA_IDENTITY_REC_LEN)
    {
        PPPC_WARNING_LOG1("The length of Identity out of range,%d.", usIdentityLen);
        return VOS_ERR;
    }

    PS_MEM_SET(aucXkey, 0x00, sizeof(aucXkey));

    stPara.ucNum        = 4;

    stPara.apucAdrr[0]  = pucIdentity;
    stPara.aulLen[0]    = usIdentityLen;

    usCounter = VOS_HTONS(pstEapAkaAuthPara->usCounter);
    stPara.apucAdrr[1]  = (VOS_UINT8 *)&usCounter;
    stPara.aulLen[1]    = PPPC_EAP_AKA_COUNTER_LEN;

    stPara.apucAdrr[2]  = pstEapAkaAuthPara->aucNonce_s;
    stPara.aulLen[2]    = PPPC_EAP_AKA_NONCE_S_LEN;

    stPara.apucAdrr[3]  = pstEapAkaKey->aucMk;
    stPara.aulLen[3]    = PPPC_EAP_AKA_MK_LEN;

    ulRet = PPPC_SHA1(&stPara, aucXkey);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("DeriveKeys ReAuth When SHA1 Error!");
        return VOS_ERR;
    }

    PS_MEM_SET(aucBuf, 0x00, sizeof(aucBuf));

    ulRet = PPPC_EAP_PRF(aucXkey, PPPC_EAP_AKA_MK_LEN, aucBuf, sizeof(aucBuf));
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("DeriveKeys ReAuth When PRF Error!");
        return VOS_ERR;
    }

    ucCur = 0;
    PS_MEM_CPY(pstEapAkaKey->aucMSK, aucBuf, PPPC_EAP_AKA_MSK_LEN);
    ucCur += PPPC_EAP_AKA_MSK_LEN;
    PS_MEM_CPY(pstEapAkaKey->aucEMSK, aucBuf + ucCur, PPPC_EAP_AKA_EMSK_LEN);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ClearKeys
 功能描述  : 清除Key信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_ClearKeys
(
    PS_BOOL_ENUM_UINT8                  enReauth
)
{

    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_KEY_DATA_STRU         *pstEapAkaKey;

    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaKey      = &(pstEapAkaDataInfo->stEapAkaKey);


    if (PS_FALSE == enReauth)
    {
        PS_MEM_SET(&(pstEapAkaKey->aucMk[0]), 0, PPPC_EAP_AKA_MK_LEN);
        PS_MEM_SET(&(pstEapAkaKey->aucK_aut[0]), 0, PPPC_EAP_AKA_K_AUT_LEN);
        PS_MEM_SET(&(pstEapAkaKey->aucPrimeK_aut[0]), 0, PPPC_EAP_AKA_PRIME_K_AUT_LEN);
        PS_MEM_SET(&(pstEapAkaKey->aucK_encr[0]), 0, PPPC_EAP_AKA_K_ENCR_LEN);
        PS_MEM_SET(&(pstEapAkaKey->aucK_re[0]), 0, PPPC_EAP_AKA_PRIME_K_RE_LEN);
    }
    PS_MEM_SET(&(pstEapAkaKey->aucMSK[0]), 0, PPPC_EAP_AKA_MSK_LEN);
    PS_MEM_SET(&(pstEapAkaKey->aucEMSK[0]), 0, PPPC_EAP_AKA_EMSK_LEN);

   return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_InitForReAuth
 功能描述  : 快速重鉴权过程中初始化一些实体信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_InitForReAuth(VOS_VOID)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_AUTH_PARA_STRU        *pstEapAkaAuthPara = VOS_NULL_PTR;
    VOS_UINT16                          usCounter;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaAuthPara = &(pstEapAkaDataInfo->stEapAkaAuthPara);

    /* 清除鉴权参数信息, Counter不能被清除 */
    usCounter = pstEapAkaAuthPara->usCounter;
    PS_MEM_SET(pstEapAkaAuthPara, 0, sizeof(PPPC_EAP_AKA_AUTH_PARA_STRU));
    pstEapAkaAuthPara->usCounter            = usCounter;
    pstEapAkaDataInfo->enEapAkaState        = PPPC_EAP_AKA_STATE_CONTINUE;
    pstEapAkaDataInfo->enReauth             = PS_FALSE;

    /* 清除Key信息 */
    PPPC_EAP_AKA_ClearKeys(PS_TRUE);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_RespMsgInit
 功能描述  : 填写消息头部
 输入参数  : ucEapAkaSubType --EAP-AKA Subtype
 输出参数  : pstEAPMethodOutput
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_RespMsgInit
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    VOS_UINT8                           ucEapAkaSubType
)
{

    VOS_UINT8                          *pucEapAkaRspPayloadInfo;
    VOS_UINT16                          usEapLen;
    const VOS_UINT8                     ucConst3Value = 3; /* Subtype和Reserved总共3字节*/

    /*
       RFC4187 P46
        0               1             2             3
        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        | Code        | Identifier    | Length                         |
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        | Type        | Subtype       | Reserved                       |
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |AttributeType| Length        | Value...
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |AttributeType| Length        | Value...
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        ......
    */
    /* subtype之前的域EAP已填好, AKA只需要从subtype开始填写即可,
        MsgInit里面填充Subtype和Reserved 3字节 */
    usEapLen = *(pstEAPMethodOutput->pusRespLen);

    pucEapAkaRspPayloadInfo = &(pstEAPMethodOutput->pucPktData[usEapLen]);
    *pucEapAkaRspPayloadInfo = ucEapAkaSubType;

    /* Reserved Field */
    pucEapAkaRspPayloadInfo++;
    PS_MEM_SET(pucEapAkaRspPayloadInfo, 0, sizeof(VOS_UINT16));

    /* 调用PPPC接口更新EAP长度 */
    usEapLen += ucConst3Value;

    PPPC_EAP_UpdateLen(pstEAPMethodOutput->pucPktData,
                pstEAPMethodOutput->pusRespLen, usEapLen);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_MsgAddAttr
 功能描述  : 完成属性的填写
 输入参数  : ucAttrId  --EAP-AKA Attribute type
             usValue   --属性的第三四个字节数据值
             pData     --属性Value域的数据
             usDataLen --属性Value域数据长度
 输出参数  : pMsg      --属性要填写的位置
 返 回 值  : usAttrLen --填充的属性长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 PPPC_EAP_AKA_MsgAddAttr
(
    VOS_UINT8                          *pucAddAttrStart,
    PPPC_EAP_AKA_ATTR_INFO_STRU        *pstEapAkaAttrInfo,
    VOS_UINT16                          usCurPayloadLen,
    VOS_UINT16                          usTotalPayloadLen
)
{
    VOS_UINT16                          usPadLen        = 0;
    VOS_UINT16                          usAttrLen       = 0;
    const VOS_UINT8                     ucAttrHeadLen   = 4;
    const VOS_UINT8                     ucBytesPerWord  = 4;
    VOS_UINT16                          usHtonsValue    = 0;


    if (VOS_NULL_PTR == pucAddAttrStart)
    {
        PPPC_WARNING_LOG("pucAddAttrStart is NULL.");
        return usAttrLen;
    }

    /* 整个属性的长度为4BYTES的倍数 */
    usAttrLen = ucAttrHeadLen + pstEapAkaAttrInfo->usDataLen;
    usPadLen  = (ucBytesPerWord - (usAttrLen % ucBytesPerWord)) % ucBytesPerWord;
    usAttrLen = usAttrLen + usPadLen;

    if (usTotalPayloadLen < (usAttrLen + usCurPayloadLen))
    {
        PPPC_WARNING_LOG("EapPayloadLen is lager than MAX LEN.");
        return 0;
    }

    /* Attr Id */
    *pucAddAttrStart     = pstEapAkaAttrInfo->ucAttrId;
    pucAddAttrStart++;

    /* Attr LEN */
    *pucAddAttrStart     = (VOS_UINT8)usAttrLen / ucBytesPerWord;
    pucAddAttrStart++;

    /* Attr Value */
    usHtonsValue = VOS_HTONS(pstEapAkaAttrInfo->usValue);
    PS_MEM_CPY(pucAddAttrStart, &usHtonsValue, sizeof(VOS_UINT16));
    pucAddAttrStart = pucAddAttrStart + sizeof(pstEapAkaAttrInfo->usValue);


    if (VOS_NULL_PTR != pstEapAkaAttrInfo->pData)
    {
        PS_MEM_CPY(pucAddAttrStart, pstEapAkaAttrInfo->pData,
                        pstEapAkaAttrInfo->usDataLen);
        pucAddAttrStart = pucAddAttrStart + pstEapAkaAttrInfo->usDataLen;
    }

    if (0 != usPadLen)
    {
        PS_MEM_SET(pucAddAttrStart, 0, usPadLen);
    }

    return usAttrLen;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_UpdateState
 功能描述  : 更新AKA状态
 输入参数  : ulPppId    --PPPId
             enNewState --新状态
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月13日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_UpdateState
(
    VOS_UINT32                          ulPppId,
    PPPC_EAP_AKA_STATE_ENUM_UINT16      enNewState
)
{
    PPPC_EAP_AKA_STATE_ENUM_UINT16      enOldState;
    PPPC_EAP_METHOD_TYPE_ENUM_UINT16    enEapMethod;
    PPPC_EVENT_USER_DATA                stPppEventData = {0};


    enEapMethod = g_stPppcEapAkaDataInfo.enEapMethod;
    enOldState  = g_stPppcEapAkaDataInfo.enEapAkaState;
    g_stPppcEapAkaDataInfo.enEapAkaState = enNewState;

    /* 可维可测 */
    stPppEventData.ulPppId      = ulPppId;
    stPppEventData.ucPdnId      = 0xFF;
    stPppEventData.enEntityId   = PPPC_ENTITY_ID_EAP_AKA;
    stPppEventData.ulNewState   = enNewState;
    stPppEventData.ulOldState   = enOldState;
    stPppEventData.aucData[0]   = (VOS_UINT8)enEapMethod;
    PPPC_MNTN_SndEvent(MSPS_PID_PPPC, DIAG_MODE_COMM, PPPC_LOG_EVENT_EAP_AKA_STATE_UPDATE,
            &stPppEventData, sizeof(PPPC_EVENT_USER_DATA));

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AddClientError
 功能描述  : 构造PPPC_EAP_AKA_SUBTYPE_CLIENT_ERROR报文
 输入参数  : 无
 输出参数  : pstEAPMethodOutput --Response数据要填写的位置
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月13日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_AddClientError
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput
)
{
    VOS_UINT8                          *pucEapAkaRspPayloadInfo;
    VOS_UINT16                          usAttrLen = 0;
    VOS_UINT16                          usEapLen;
    VOS_UINT8                           ucEapAkaSubType;
    PPPC_EAP_AKA_ATTR_INFO_STRU         stEapAkaAttrInfo;


    /* 1) 填充Subtype和Reserved域 */
    ucEapAkaSubType = PPPC_EAP_AKA_SUBTYPE_CLIENT_ERROR;
    PPPC_EAP_AKA_RespMsgInit(pstEAPMethodOutput, ucEapAkaSubType);

    /* 2) Add AT_CLIENT_ERROR_CODE Attribute */
    usEapLen = *(pstEAPMethodOutput->pusRespLen);
    pucEapAkaRspPayloadInfo = &(pstEAPMethodOutput->pucPktData[usEapLen]);

    /*
       RFC 4187 P66
       0               1               2             3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |AT_CLIENT_ERR..| Length = 1 | Client Error Code                |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    PS_MEM_SET(&stEapAkaAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTR_INFO_STRU));
    stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_CLIENT_ERROR_CODE;
    stEapAkaAttrInfo.usValue    = PPPC_EAP_AKA_UNABLE_TO_PROCESS_PACKET;
    stEapAkaAttrInfo.pData      = VOS_NULL_PTR;
    stEapAkaAttrInfo.usDataLen  = 0;
    usAttrLen = PPPC_EAP_AKA_MsgAddAttr(pucEapAkaRspPayloadInfo, &stEapAkaAttrInfo,
                    usEapLen, PPPC_EAP_MAX_PACKET_LEN);

    /* 调用PPPC接口更新EAP长度 */
    usEapLen += usAttrLen;

    PPPC_EAP_UpdateLen(pstEAPMethodOutput->pucPktData, pstEAPMethodOutput->pusRespLen,
        usEapLen);

    return;
}


/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_SndClientErrorPkt
 功能描述  : EAP-AKA发送ClientError报文
 输入参数  : 无
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月13日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_SndClientErrorPkt
(
    PPPC_EAP_METHOD_OUTPUT_STRU         *pstEAPMethodOutput
)
{
    /* 更新EAP-AKA状态 */
    PPPC_EAP_AKA_UpdateState(pstEAPMethodOutput->ulPppId,
                        PPPC_EAP_AKA_STATE_FAILURE);

    /* 清除实体信息 */
    g_stPppcEapAkaDataInfo.ucNumNotification = 0;
    g_stPppcEapAkaDataInfo.ucNumIdReq = 0;

    /* 填充PPPC_EAP_AKA_SUBTYPE_CLIENT_ERROR报文 */
    PPPC_EAP_AKA_AddClientError(pstEAPMethodOutput);

    /* 给EAP发送Response报文 */
    PPPC_EAP_SendResponse(pstEAPMethodOutput->ulPppId);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_PRIME_KdfSelect
 功能描述  : 选择KDF
 输入参数  : pstEAPMethodInput --EAP递给方法的包
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_PRIME_KdfSelect
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    VOS_UINT8                          *pucEapAkaRspPayloadInfo;
    VOS_UINT16                          usAttrLen = 0;
    VOS_UINT16                          usEapLen;
    VOS_UINT8                           ucEapAkaSubType = 0;
    PPPC_EAP_AKA_ATTR_INFO_STRU         stEapAkaAttrInfo;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;

    /* 设置实体参数信息 */
    pstEapAkaDataInfo->enKdfNegotiation         = PS_TRUE;
    pstEapAkaDataInfo->stEapAkaAuthPara.usKdf   = PPPC_EAP_AKA_PRIME_KDF;

    /* 1) 填充Subtype和Reserved域 */
    ucEapAkaSubType = PPPC_EAP_AKA_SUBTYPE_CHALLENGE;
    PPPC_EAP_AKA_RespMsgInit(pstEAPMethodOutput, ucEapAkaSubType);

    /* 2) Add AT_KDF Attribute */
    /*
       RFC 5448 P8
       0             1               2               3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       | AT_KDF      | Length        | Key Derivation Function       |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    usEapLen = *(pstEAPMethodOutput->pusRespLen);
    pucEapAkaRspPayloadInfo = &(pstEAPMethodOutput->pucPktData[usEapLen]);

    PS_MEM_SET(&stEapAkaAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTR_INFO_STRU));
    stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_KDF;
    stEapAkaAttrInfo.usValue    = PPPC_EAP_AKA_PRIME_KDF;
    stEapAkaAttrInfo.pData      = VOS_NULL_PTR;
    stEapAkaAttrInfo.usDataLen  = 0;

    usAttrLen = PPPC_EAP_AKA_MsgAddAttr(pucEapAkaRspPayloadInfo, &stEapAkaAttrInfo,
                                usEapLen, PPPC_EAP_MAX_PACKET_LEN);

    /* 调用PPPC接口更新EAP长度 */
    usEapLen += usAttrLen;

    PPPC_EAP_UpdateLen(pstEAPMethodOutput->pucPktData,
            pstEAPMethodOutput->pusRespLen, usEapLen);

    /* 给EAP发送Response报文 */
    PPPC_EAP_SendResponse(pstEAPMethodOutput->ulPppId);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AuthenticationReject
 功能描述  : 发送AuthenticationReject消息
 输入参数  : 无
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_AuthenticationReject
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput
)
{
    VOS_UINT8                           ucEapAkaSubType;
    VOS_UINT32                          ulLocalResult;


    /* 更新状态 */
    PPPC_EAP_AKA_UpdateState(pstEAPMethodOutput->ulPppId,
                        PPPC_EAP_AKA_STATE_FAILURE);

    g_stPppcEapAkaDataInfo.ucNumNotification = 0;
    g_stPppcEapAkaDataInfo.ucNumIdReq = 0;

    /*
       RFC4187 P46
       0               1             2             3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       | Code        | Identifier    | Length                         |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       | Type        | Subtype       | Reserved                       |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |AttributeType| Length        | Value...
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |AttributeType| Length        | Value...
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       ......
    */
    ucEapAkaSubType = PPPC_EAP_AKA_SUBTYPE_AUTHENTICATION_REJECT;
    PPPC_EAP_AKA_RespMsgInit(pstEAPMethodOutput, ucEapAkaSubType);

    /* Reject消息没有属性域 */

    /* AKA通知EAP Peer的鉴权结果 */
    ulLocalResult = VOS_ERR;
    PPPC_EAP_PeerProcessEvent(pstEAPMethodOutput->ulPppId,
                PPPC_EAP_PEER_AUTH_IND_EVENT, &ulLocalResult);

    /* 给EAP发送Response报文 */
    PPPC_EAP_SendResponse(pstEAPMethodOutput->ulPppId);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_PRIME_KdfNeg
 功能描述  : 协商KDF
 输入参数  : pstEAPMethodInput --EAP递给方法的包
 输出参数  : pstEAPMethodOutput--Response数据要填写的位置
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_PRIME_KdfNeg
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
)
{
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    VOS_UINT32                          ulLoop1;


    pstEapAkaAttrInfo = &g_stPppcEapAkaPktAttrInfo;


    for (ulLoop1 = 0; ulLoop1 < pstEapAkaAttrInfo->usKdfCount; ulLoop1++)
    {
        if (PPPC_EAP_AKA_PRIME_KDF == pstEapAkaAttrInfo->ausKdf[ulLoop1])
        {
            PPPC_EAP_AKA_PRIME_KdfSelect(pstEAPMethodOutput);
            return;
        }
    }

    /* No matching KDF found - fail authentication as if AUTN had been
        incorrect */
    PPPC_EAP_AKA_AuthenticationReject(pstEAPMethodOutput);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_PRIME_KdfValid
 功能描述  : 检查KDF是不是有效的
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK; VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_PRIME_KdfValid(VOS_VOID)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    VOS_UINT32                          ulLoop1;
    VOS_UINT32                          ulLoop2;
    VOS_UINT32                          ulLoopStart;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo = &g_stPppcEapAkaPktAttrInfo;

    if (0 == pstEapAkaAttrInfo->usKdfCount)
    {
        PPPC_WARNING_LOG("usKdfCount is zero");
        return VOS_ERR;
    }

    /* The only allowed (and required) duplication of a KDF is the addition
       of the selected KDF into the beginning of the list. */
    if (PS_TRUE == pstEapAkaDataInfo->enKdfNegotiation)
    {
        if (pstEapAkaDataInfo->stEapAkaAuthPara.usKdf != pstEapAkaAttrInfo->ausKdf[0])
        {
            PPPC_WARNING_LOG("EAP-AKA': The server did not "
                   "accept the selected KDF");
            return VOS_ERR;
        }

        for (ulLoop1 = 1; ulLoop1 < pstEapAkaAttrInfo->usKdfCount; ulLoop1++)
        {
            if (pstEapAkaDataInfo->stEapAkaAuthPara.usKdf == pstEapAkaAttrInfo->ausKdf[ulLoop1])
            {
                break;
            }
        }
        /*
           the server re-sends the EAP-Response/AKA'-Challenge message, but adds the selected
           alternative to the beginning of the list of AT_KDF attributes and retains the entire
           list following it.  Note that this means that the selected alternative appears twice
           in the set of AT_KDF values.
        */
        if ((ulLoop1 == pstEapAkaAttrInfo->usKdfCount)
            && (pstEapAkaAttrInfo->usKdfCount < PPPC_EAP_AKA_PRIME_KDF_MAX))
        {
            PPPC_WARNING_LOG("EAP-AKA': The server did not "
                   "duplicate the selected KDF");
            return VOS_ERR;
        }
    }

    ulLoopStart = (pstEapAkaDataInfo->stEapAkaAuthPara.usKdf ? 1 : 0);
    for (ulLoop1 = ulLoopStart; ulLoop1 < pstEapAkaAttrInfo->usKdfCount; ulLoop1++)
    {
        for (ulLoop2 = ulLoop1 + 1; ulLoop2 < pstEapAkaAttrInfo->usKdfCount; ulLoop2++)
        {
            if (pstEapAkaAttrInfo->ausKdf[ulLoop1] == pstEapAkaAttrInfo->ausKdf[ulLoop2])
            {
                PPPC_WARNING_LOG("EAP-AKA': The server did not "
                       "included a duplicated KDF");

                return VOS_ERR;
            }
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_SaveIds
 功能描述  : 保存ID信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_SaveIds(VOS_VOID)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    PPPC_EAP_AKA_ID_INFO_STRU          *pstEapAkaIdInfo;
    VOS_UINT8                          *pucRealm;
    VOS_UINT16                          usRealmLen;
    VOS_UINT8                          *pucPermenentId;
    VOS_UINT16                          usPermenentIdLen;
    VOS_UINT32                          ulLoop;


    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo   = &g_stPppcEapAkaPktAttrInfo;
    pstEapAkaIdInfo     = &(pstEapAkaDataInfo->stEapAkaIdInfo);


    /* 保存NextPseudonym */
    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstEapAkaAttrInfo->ulAttrExistCtrlFlag, PPPC_EAP_AKA_NEXT_PSEUDONYM_BIT))
    {
        /* Add userName */
        PS_MEM_CPY(&(pstEapAkaIdInfo->aucPseudonym[0]),
                &(pstEapAkaAttrInfo->aucNextPseudonym[0]),
                pstEapAkaAttrInfo->usNextPseudonymLen);

        /* Add Realm */
        pucPermenentId = &(pstEapAkaIdInfo->aucPermenentId[0]);
        usPermenentIdLen = pstEapAkaIdInfo->usPermenentIdLen;
        for (ulLoop = 0; ulLoop < usPermenentIdLen; ulLoop++)
        {
            if ('@' == pucPermenentId[ulLoop])
            {
                pucRealm    = &(pucPermenentId[ulLoop]);
                usRealmLen  = usPermenentIdLen - (VOS_UINT16)ulLoop;
                PS_MEM_CPY(&(pstEapAkaIdInfo->aucPseudonym[pstEapAkaAttrInfo->usNextPseudonymLen]),
                        pucRealm, usRealmLen);
                pstEapAkaIdInfo->usPseudonymLen = pstEapAkaAttrInfo->usNextPseudonymLen + usRealmLen;
                break;
            }
        }

        if (ulLoop == usPermenentIdLen)
        {
            PPPC_WARNING_LOG("EAP-AKA': Add realm fail");
        }
    }

    /* 保存NextReauthId */
    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstEapAkaAttrInfo->ulAttrExistCtrlFlag,
            PPPC_EAP_AKA_NEXT_REAUTH_BIT))
    {
        PS_MEM_CPY(&(pstEapAkaIdInfo->aucReauthId[0]),
                &(pstEapAkaAttrInfo->aucNextReauthId[0]),
                pstEapAkaAttrInfo->usNextReauthIdLen);
        pstEapAkaIdInfo->usReauthIdLen = pstEapAkaAttrInfo->usNextReauthIdLen;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_CheckAmf
 功能描述  : 检查AMF
 输入参数  : pucAutn        --AUTN
 输出参数  :
 返 回 值  : VOS_ERR; VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_CheckAmf
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    VOS_UINT8                          *pucAutn
)
{
    VOS_UINT16                          usAmf;
    VOS_UINT16                         *pusAmf;
    const VOS_UINT16                    usAmfAddrOffset = 6;
    const VOS_UINT16                    usAmfCheckMask = 0x8000;
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_METHOD_TYPE_ENUM_UINT16    enEapMethod;


    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;

    enEapMethod         = pstEapAkaDataInfo->enEapMethod;
    /*  RFC5448 P10
        When the server creates an AKA challenge and corresponding AUTN, CK,
        CK', IK, and IK' values, it MUST set the Authentication Management
        Field (AMF) separation bit to 1 in the AKA algorithm [3GPP.33.102].
        Similarly, the peer MUST check that the AMF separation bit is set to
        1.  If the bit is not set to 1, the peer behaves as if the AUTN had
        been incorrect and fails the authentication.
    */
    /* Note: AUTN = (SQN ^ AK) || AMF || MAC which gives us the
       needed 6-octet SQN ^ AK for CK',IK' derivation
     */

    if (PPPC_EAP_METHOD_TYPE_AKA_PRIME == enEapMethod)
    {
        pusAmf = (VOS_UINT16 *)(pucAutn + usAmfAddrOffset);
        usAmf = (VOS_UINT16)VOS_HTONS(*pusAmf);
        if (usAmfCheckMask != (usAmf & usAmfCheckMask))
        {
            PPPC_WARNING_LOG("EAP-AKA': AMF separation bit not set");
            PPPC_EAP_AKA_AuthenticationReject(pstEAPMethodOutput);

            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AddCheckCode
 功能描述  : 添加CheckCode
 输入参数  : 无
 输出参数  : pucEapAkaRspPayloadInfo    --Response数据要填写的位置
 返 回 值  : CheckCode 属性长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 PPPC_EAP_AKA_AddCheckCode
(
    VOS_UINT8                          *pucEapAkaRspPayloadInfo,
    VOS_UINT16                          usCurEapPayloadLen
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    VOS_UINT8                          *pucIdMsgAddr;
    VOS_UINT16                          usIdMsgLen;
    VOS_UINT8                           aucHash[PPPC_SHA256_MAC_LEN];
    VOS_UINT16                          usHashLen = 0;
    PPPC_SHA1_PARA_STRU                 stSha1Para;
    PPPC_SHA256_PARA_STRU               stSha256Para;
    VOS_UINT16                          usAttrLen = 0;
    PPPC_EAP_AKA_ATTR_INFO_STRU         stEapAkaAttrInfo;
    VOS_UINT32                          ulRslt;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    PS_MEM_SET(&(aucHash[0]), 0, PPPC_SHA256_MAC_LEN);
    PS_MEM_SET(&stEapAkaAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTR_INFO_STRU));

    /*
       RFC 4187 P61
       0             1               2               3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       | AT_CHECKCODE| Length        | Reserved                      |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                             |
       | Checkcode (0 or 20 bytes)                                   |
       |                                                             |
       |                                                             |
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */

    if (0 == pstEapAkaDataInfo->usIdMsgLen)
    {
        /*
         * No EAP-AKA/Identity packets were exchanged - send empty
         * checkcode.
        */
        stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_CHECKCODE;
        stEapAkaAttrInfo.usValue    = 0;
        stEapAkaAttrInfo.pData      = VOS_NULL_PTR;
        stEapAkaAttrInfo.usDataLen  = 0;

        usAttrLen = PPPC_EAP_AKA_MsgAddAttr(pucEapAkaRspPayloadInfo,
                        &stEapAkaAttrInfo, usCurEapPayloadLen, PPPC_EAP_MAX_PACKET_LEN);
        return usAttrLen;
    }

    pucIdMsgAddr = &(pstEapAkaDataInfo->ucIdMsgs[0]);
    usIdMsgLen   = pstEapAkaDataInfo->usIdMsgLen;

    /* Checkcode is SHA1/SHA256 hash over all EAP-AKA/Identity packets. */
    if (PPPC_EAP_METHOD_TYPE_AKA_PRIME == pstEapAkaDataInfo->enEapMethod)
    {
        stSha256Para.ucNum          = 1;
        stSha256Para.apucAdrr[0]    = pucIdMsgAddr;
        stSha256Para.aulLen[0]      = usIdMsgLen;
        usHashLen = PPPC_EAP_AKA_PRIME_CHECKCODE_LEN;
        ulRslt = PPPC_SHA256(&stSha256Para, &(aucHash[0]));;
    }
    else
    {
        stSha1Para.ucNum = 1;
        stSha1Para.apucAdrr[0] = pucIdMsgAddr;
        stSha1Para.aulLen[0]  = usIdMsgLen;
        usHashLen = PPPC_EAP_AKA_CHECKCODE_LEN;
        ulRslt = PPPC_SHA1(&stSha1Para, &(aucHash[0]));
    }
    if (VOS_OK != ulRslt)
    {
        PPPC_WARNING_LOG("PPPC_SHA256 or PPPC_SHA1 is fail");
        return usAttrLen;
    }

    stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_CHECKCODE;
    stEapAkaAttrInfo.usValue    = 0;
    stEapAkaAttrInfo.pData      = &(aucHash[0]);
    stEapAkaAttrInfo.usDataLen  = usHashLen;

    usAttrLen = PPPC_EAP_AKA_MsgAddAttr(pucEapAkaRspPayloadInfo,
                    &stEapAkaAttrInfo, usCurEapPayloadLen, PPPC_EAP_MAX_PACKET_LEN);

    return usAttrLen;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_VerifyCheckCode
 功能描述  : 检查CheckCode
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK; VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_VerifyCheckCode(VOS_VOID)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    VOS_UINT8                          *pucIdMsgAddr;
    VOS_UINT16                          usIdMsgLen;
    VOS_UINT8                           aucHash[PPPC_SHA256_MAC_LEN];
    VOS_UINT16                          usHashLen = 0;
    PPPC_SHA1_PARA_STRU                 stSha1Para;
    PPPC_SHA256_PARA_STRU               stSha256Para;
    VOS_UINT32                          ulRslt = VOS_ERR;

    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo = &g_stPppcEapAkaPktAttrInfo;
    PS_MEM_SET(&(aucHash[0]), 0, PPPC_SHA256_MAC_LEN);

    /*
       RFC4187 p61
        If the checkcode is not included in AT_CHECKCODE, then
        the attribute indicates that no EAP/-AKA-Identity messages
        were exchanged. This may occur in both full authentication
        and fast re-authentication.
    */
    if (0 == pstEapAkaDataInfo->usIdMsgLen)
    {
        if (0 != pstEapAkaAttrInfo->usCheckCodeLen)
        {
            PPPC_WARNING_LOG("EAP-AKA: Checkcode from server indicates that AKA/Identity messages were used, but they were not");
            return VOS_ERR;
        }
        return VOS_OK;
    }

    /* EAP-AKA checkcode域为20byte, EAP-AKA' checkcode域为32byte*/
    if (PPPC_EAP_METHOD_TYPE_AKA_PRIME == pstEapAkaDataInfo->enEapMethod)
    {
        usHashLen = PPPC_EAP_AKA_PRIME_CHECKCODE_LEN;
    }
    else
    {
        usHashLen = PPPC_EAP_AKA_CHECKCODE_LEN;
    }

    if (usHashLen != pstEapAkaAttrInfo->usCheckCodeLen)
    {
        PPPC_WARNING_LOG("EAP-AKA: Checkcode from server indicates that AKA/Identity messages were used, but they were not");
        return VOS_ERR;
    }

    pucIdMsgAddr = &(pstEapAkaDataInfo->ucIdMsgs[0]);
    usIdMsgLen   = pstEapAkaDataInfo->usIdMsgLen;

    /* Checkcode is SHA1/SHA256 hash over all EAP-AKA/Identity packets. */
    if (PPPC_EAP_METHOD_TYPE_AKA_PRIME == pstEapAkaDataInfo->enEapMethod)
    {
        stSha256Para.ucNum          = 1;
        stSha256Para.apucAdrr[0]    = pucIdMsgAddr;
        stSha256Para.aulLen[0]      = usIdMsgLen;
        ulRslt = PPPC_SHA256(&stSha256Para, &(aucHash[0]));
    }
    else
    {
        stSha1Para.ucNum        = 1;
        stSha1Para.apucAdrr[0]  = pucIdMsgAddr;
        stSha1Para.aulLen[0]    = usIdMsgLen;
        ulRslt = PPPC_SHA1(&stSha1Para, &(aucHash[0]));
    }
    if (VOS_OK != ulRslt)
    {
        PPPC_WARNING_LOG("PPPC_SHA256 or PPPC_SHA1 is fail");
        return VOS_ERR;
    }

    if (0 != PS_MEM_CMP(&(aucHash[0]), &(pstEapAkaAttrInfo->aucCheckCode[0]), usHashLen))
    {
        PPPC_WARNING_LOG("EAP-AKA: Mismatch in AT_CHECKCODE");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_VerifyMac
 功能描述  : 检查AT_MAC属性
 输入参数  : pucMsg --EAP递过来的报文
             usMsgLen --EAP递过来的报文长度
             pucExtra --其他的参数
             usExtraLen --其他参数的长度
 输出参数  :
 返 回 值  : VOS_OK; VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_VerifyMac
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT16                          usMsgLen,
    VOS_UINT8                          *pucExtra,
    VOS_UINT16                          usExtraLen
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    VOS_UINT8                          *pucKey;
    VOS_UINT8                           ucKeyLen;
    VOS_UINT8                           aucMac[PPPC_EAP_AKA_MAC_MAX_LEN];
    PPPC_SHA1_PARA_STRU                 stSha1Para;
    PPPC_SHA256_PARA_STRU               stSha256Para;
    PPPC_EAP_METHOD_TYPE_ENUM_UINT16    enEapMethod;
    VOS_UINT8                           aucNullMac[PPPC_EAP_AKA_MAC_VALUE_LEN];
    VOS_UINT8                          *pucAtMacPos;
    const VOS_UINT8                     uc4Octet = 4;   /* attribute的长度跟length域的值的倍数 */

    /* 从ATTR字段开始查找，所以跳过CODE和TYPE字段 */
    pucAtMacPos = pucMsg + 2*uc4Octet;
    while (PPPC_EAP_AKA_AT_MAC != *pucAtMacPos)
    {
        if ((pucAtMacPos - pucMsg) > (usMsgLen - PPPC_EAP_AKA_MAC_VALUE_LEN))
        {
            PPPC_WARNING_LOG("Not Find AT_MAC");
            return VOS_ERR;
        }
        pucAtMacPos += pucAtMacPos[1]*uc4Octet;
    }

    pucAtMacPos += uc4Octet;

    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo   = &g_stPppcEapAkaPktAttrInfo;
    enEapMethod         = pstEapAkaDataInfo->enEapMethod;

    PS_MEM_SET(&(aucMac[0]), 0, PPPC_EAP_AKA_MAC_MAX_LEN);
    PS_MEM_SET(&(aucNullMac[0]), 0, PPPC_EAP_AKA_MAC_VALUE_LEN);

    if (PPPC_EAP_METHOD_TYPE_AKA_PRIME == enEapMethod)
    {
        pucKey = &(pstEapAkaDataInfo->stEapAkaKey.aucPrimeK_aut[0]);
        ucKeyLen = PPPC_EAP_AKA_PRIME_K_AUT_LEN;
        stSha256Para.ucNum          = 4;
        stSha256Para.apucAdrr[0]    = pucMsg;
        stSha256Para.aulLen[0]      = (VOS_UINT32)(pucAtMacPos - pucMsg);
        stSha256Para.apucAdrr[1]    = &(aucNullMac[0]);
        stSha256Para.aulLen[1]      = PPPC_EAP_AKA_MAC_VALUE_LEN;
        stSha256Para.apucAdrr[2]    = (VOS_UINT8 *)(pucAtMacPos + PPPC_EAP_AKA_MAC_VALUE_LEN);
        stSha256Para.aulLen[2]      = (VOS_UINT32)(pucMsg + usMsgLen - pucAtMacPos - PPPC_EAP_AKA_MAC_VALUE_LEN);
        stSha256Para.apucAdrr[3]    = pucExtra;
        stSha256Para.aulLen[3]      = usExtraLen;
        PPPC_HMAC_SHA256(pucKey, ucKeyLen, &stSha256Para, &(aucMac[0]));
    }
    if (PPPC_EAP_METHOD_TYPE_AKA == pstEapAkaDataInfo->enEapMethod)
    {
        pucKey = &(pstEapAkaDataInfo->stEapAkaKey.aucK_aut[0]);
        ucKeyLen = PPPC_EAP_AKA_K_AUT_LEN;
        stSha1Para.ucNum        = 4;
        stSha1Para.apucAdrr[0]  = pucMsg;
        stSha1Para.aulLen[0]    = (VOS_UINT32)(pucAtMacPos - pucMsg);
        stSha1Para.apucAdrr[1]  = &(aucNullMac[0]);
        stSha1Para.aulLen[1]    = PPPC_EAP_AKA_MAC_VALUE_LEN;
        stSha1Para.apucAdrr[2]  = (VOS_UINT8 *)(pucAtMacPos + PPPC_EAP_AKA_MAC_VALUE_LEN);
        stSha1Para.aulLen[2]    = (VOS_UINT32)(pucMsg + usMsgLen - pucAtMacPos - PPPC_EAP_AKA_MAC_VALUE_LEN);
        stSha1Para.apucAdrr[3]  = pucExtra;
        stSha1Para.aulLen[3]    = usExtraLen;
        PPPC_HMAC_SHA1(pucKey, ucKeyLen, &stSha1Para, &(aucMac[0]));
    }

    if (0 != PS_MEM_CMP(&(aucMac[0]), &(pstEapAkaAttrInfo->aucMac[0]),
                PPPC_EAP_AKA_MAC_VALUE_LEN))
    {
        PPPC_WARNING_LOG("EAP-AKA: Mismatch in AT_MAC");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_MsgAddAtMacAttr
 功能描述  : 添加AT_MAC属性
 输入参数  : pucExtra --其他的参数
             usExtraLen --其他参数的长度
 输出参数  : pstEAPMethodOutput
 返 回 值  : AT_MAC属性长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 PPPC_EAP_AKA_MsgAddAtMacAttr
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    VOS_UINT8                          *pucExtra,
    VOS_UINT16                          usExtraLen
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    VOS_UINT8                          *pucRspAttrData;
    VOS_UINT8                          *pucKey;
    VOS_UINT8                          *pucData;
    VOS_UINT8                           ucKeyLen;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucMac[PPPC_EAP_AKA_MAC_MAX_LEN];
    VOS_UINT8                           aucNullMac[PPPC_EAP_AKA_MAC_TOTAL_LEN];
    const VOS_UINT8                     ucAtMacWordLen = 5; /* AT MAC长度为5words */
    PPPC_SHA1_PARA_STRU                 stSha1Para;
    PPPC_SHA256_PARA_STRU               stSha256Para;
    VOS_UINT16                          usAttrLen = 0;
    PPPC_EAP_AKA_ATTR_INFO_STRU         stEapAkaAttrInfo;
    VOS_UINT8                           aucEapHead[PPPC_EAP_HEADER_LEN];
    VOS_UINT16                          usEapLen;
    VOS_UINT16                          usTransEapLen;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    PS_MEM_SET(&(aucMac[0]), 0, PPPC_EAP_AKA_MAC_MAX_LEN);
    PS_MEM_SET(&(aucNullMac[0]), 0, PPPC_EAP_AKA_MAC_TOTAL_LEN);

    /* 构造MAC属性头部 */
    aucNullMac[0] = PPPC_EAP_AKA_AT_MAC;
    aucNullMac[1] = ucAtMacWordLen;

    /* EAP 头部信息 */
    PS_MEM_CPY(&(aucEapHead[0]), &(pstEAPMethodOutput->pucPktData[0]), PPPC_EAP_HEADER_LEN);
    usEapLen = *(pstEAPMethodOutput->pusRespLen) + PPPC_EAP_AKA_MAC_TOTAL_LEN;
    usTransEapLen = VOS_HTONS(usEapLen);
    PS_MEM_CPY(&(aucEapHead[2]), &usTransEapLen, sizeof(VOS_UINT16));

    /* EAP 头部之后的数据信息 */
    pucData             = &(pstEAPMethodOutput->pucPktData[PPPC_EAP_HEADER_LEN]);
    usDataLen           = *(pstEAPMethodOutput->pusRespLen) - PPPC_EAP_HEADER_LEN;

    /*
       0               1               2             3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       | AT_MAC | Length = 5 | Reserved                                |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                               |
       | MAC                                                           |
       |                                                               |
       |                                                               |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    if (PPPC_EAP_METHOD_TYPE_AKA_PRIME == pstEapAkaDataInfo->enEapMethod)
    {
        pucKey = &(pstEapAkaDataInfo->stEapAkaKey.aucPrimeK_aut[0]);
        ucKeyLen = PPPC_EAP_AKA_PRIME_K_AUT_LEN;
        stSha256Para.ucNum        = 4;
        stSha256Para.apucAdrr[0]  = &(aucEapHead[0]);
        stSha256Para.aulLen[0]    = PPPC_EAP_HEADER_LEN;
        stSha256Para.apucAdrr[1]  = pucData;
        stSha256Para.aulLen[1]    = usDataLen;
        stSha256Para.apucAdrr[2]  = &(aucNullMac[0]);
        stSha256Para.aulLen[2]    = PPPC_EAP_AKA_MAC_TOTAL_LEN;
        stSha256Para.apucAdrr[3]  = pucExtra;
        stSha256Para.aulLen[3]    = usExtraLen;
        PPPC_HMAC_SHA256(pucKey, ucKeyLen, &stSha256Para, &(aucMac[0]));
    }
    if (PPPC_EAP_METHOD_TYPE_AKA == pstEapAkaDataInfo->enEapMethod)
    {
        pucKey = &(pstEapAkaDataInfo->stEapAkaKey.aucK_aut[0]);
        ucKeyLen = PPPC_EAP_AKA_K_AUT_LEN;
        stSha1Para.ucNum        = 4;
        stSha1Para.apucAdrr[0]  = &(aucEapHead[0]);
        stSha1Para.aulLen[0]    = PPPC_EAP_HEADER_LEN;
        stSha1Para.apucAdrr[1]  = pucData;
        stSha1Para.aulLen[1]    = usDataLen;
        stSha1Para.apucAdrr[2]  = &(aucNullMac[0]);
        stSha1Para.aulLen[2]    = PPPC_EAP_AKA_MAC_TOTAL_LEN;
        stSha1Para.apucAdrr[3]  = pucExtra;
        stSha1Para.aulLen[3]    = usExtraLen;
        PPPC_HMAC_SHA1(pucKey, ucKeyLen, &stSha1Para, &(aucMac[0]));
    }

    pucRspAttrData = &(pstEAPMethodOutput->pucPktData[0]) + *(pstEAPMethodOutput->pusRespLen);

    PS_MEM_SET(&stEapAkaAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTR_INFO_STRU));
    stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_MAC;
    stEapAkaAttrInfo.usValue    = 0;
    stEapAkaAttrInfo.pData      = &(aucMac[0]);
    stEapAkaAttrInfo.usDataLen  = PPPC_EAP_AKA_MAC_VALUE_LEN;

    usAttrLen = PPPC_EAP_AKA_MsgAddAttr(pucRspAttrData, &stEapAkaAttrInfo,
                                *(pstEAPMethodOutput->pusRespLen), PPPC_EAP_MAX_PACKET_LEN);

    return usAttrLen;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AddIdMsg
 功能描述  : 保存IdMsg消息
 输入参数  : pucMsg
 输出参数  :
 返 回 值  : VOS_OK; VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AddIdMsg
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT16                          usMsgLen
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucIdMsgs = VOS_NULL_PTR;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;

    if (VOS_NULL_PTR == pucMsg)
    {
        PPPC_WARNING_LOG("pucIdMsg is NULL.");
        return VOS_ERR;
    }

    pucIdMsgs = &(pstEapAkaDataInfo->ucIdMsgs[pstEapAkaDataInfo->usIdMsgLen]);
    PS_MEM_CPY(pucIdMsgs, pucMsg, usMsgLen);
    pstEapAkaDataInfo->usIdMsgLen += usMsgLen;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttRandParse
 功能描述  : 解析AT_RAND属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttRandParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P55
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |   AT_RAND    | Length=5      | Reserved                     |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                             |
       |                                                             |
       |                     RAND                                    |
       |                                                             |
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */

    VOS_UINT32                              ulAttrExistCtrlFlag;


    pstAttWalker->pucAttPos += PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET;
    pstAttWalker->usAttrLen -= PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET;

    if (PPPC_EAP_AKA_RAND_LEN != pstAttWalker->usAttrLen)
    {
        PPPC_WARNING_LOG1("EAP-AKA: Invalid AT_RAND (len )",
            pstAttWalker->usAttrLen);

        return VOS_ERR;
    }

    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_RAND_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_RAND have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_RAND_BIT);
    PS_MEM_CPY(&(pstAttWalker->pstPppcEapAkaPktAttrInfo->aucRand[0]),
        pstAttWalker->pucAttPos, pstAttWalker->usAttrLen);

    return VOS_OK;
}

 /*****************************************************************************
  函 数 名  : PPPPC_EAP_AKA_AttAutnParse
  功能描述  : 解析AT_AUTN属性
  输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
  输出参数  : 无
  返 回 值  : VOS_OK 成功 VOS_ERR 错误
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2015年11月06日
     作    者   : j00353617
     修改内容   : 新生成函数

 *****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttAutnParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
     /*
        RFC 4187 P56
        0                   1                   2                   3
        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |   AT_AUTN    | Length=5      | Reserved                     |
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |                                                             |
        |                                                             |
        |                     AUTN                                    |
        |                                                             |
        |                                                             |
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     */

    VOS_UINT32                              ulAttrExistCtrlFlag;


    pstAttWalker->pucAttPos += PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET;
    pstAttWalker->usAttrLen -= PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET;

    if (PPPC_EAP_AKA_AUTN_LEN != pstAttWalker->usAttrLen)
    {
        PPPC_WARNING_LOG1("EAP-AKA: Invalid AT_AUTN (len)",
            pstAttWalker->usAttrLen);

        return VOS_ERR;
    }

    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_AUTN_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_AUTN have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_AUTN_BIT);
    PS_MEM_CPY(&(pstAttWalker->pstPppcEapAkaPktAttrInfo->aucAutn[0]),
        pstAttWalker->pucAttPos, pstAttWalker->usAttrLen);

    return VOS_OK;
}

 /*****************************************************************************
  函 数 名  : PPPC_EAP_AKA_AttPaddingParse
  功能描述  : 解析AT_PADDING属性
  输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
  输出参数  : 无
  返 回 值  : VOS_OK 成功 VOS_ERR 错误
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2015年11月06日
     作    者   : j00353617
     修改内容   : 新生成函数

 *****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttPaddingParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P60
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |   AT_PADDING | Length        | Padding...                   |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-                              |
       |                                                             |
       |                                                             |
       |                                                             |
       |                                                             |
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */

    VOS_UINT32                          ulLoop;
    const VOS_UINT8                     ucPadingOctet = 0x0;
    VOS_UINT32                          ulAttrExistCtrlFlag;



    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_PADDING_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_PADDING have been included in the EAP request");

        return VOS_ERR;
    }

    if (PS_FALSE == pstAttWalker->enEncr)
    {
        PPPC_WARNING_LOG("EAP-AKA: Unencrypted AT_PADDING");

        return VOS_ERR;
    }

    /*
       RFC4187
       "The recipient of the message MUST verify that the pad bytes are set to
       zero.  If this verification fails on the peer, then it MUST send the
       EAP-Response/AKA-Client-Error packet with the error code "unable to
       process packet" to terminate the authentication exchange."
    */
    for (ulLoop = PPPC_EAP_AKA_ATTRIBUTE_TYPE_VALUE_OFFSET;
         ulLoop < (pstAttWalker->usAttrLen);
         ulLoop++)
    {
        if (ucPadingOctet != pstAttWalker->pucAttPos[ulLoop])
        {
            PPPC_WARNING_LOG("EAP-AKA: AT_PADDING used a non-zero padding byte");
            PPPC_WARNING_LOG2("EAP-AKA:padding bytes",
                (pstAttWalker->pucAttPos + PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET),
                (pstAttWalker->usAttrLen - PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET));

            return VOS_ERR;
        }
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_PADDING_BIT);

    return VOS_OK;
}

/*****************************************************************************
  函 数 名  : PPPC_EAP_AKA_AttPermanentParse
  功能描述  : 解析AT_PERMANENT_ID_REQ属性
  输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
  输出参数  : 无
  返 回 值  : VOS_OK 成功 VOS_ERR 错误
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2015年11月06日
     作    者   : j00353617
     修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttPermanentParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
     /*
        RFC 4187 P54
        0                   1                   2                   3
        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        |AT_PERM..._REQ  | Length=1    | Reserved                     |
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     */

    VOS_UINT32                          ulAttrExistCtrlFlag;


    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_PERMANENT_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_PERMANENT have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_PERMANENT_BIT);
    pstAttWalker->pstPppcEapAkaPktAttrInfo->enEapAkaIdReqType
        = PPPC_EAP_AKA_PERMANENT_ID_REQ;

    return VOS_OK;
}

/*****************************************************************************
函 数 名  : PPPC_EAP_AKA_AttMacParse
功能描述  : 解析AT_MAC属性
输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
输出参数  : 无
返 回 值  : VOS_OK 成功 VOS_ERR 错误
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2015年11月06日
   作    者   : j00353617
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttMacParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P63
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |   AT_MAC     | Length=5      | Reserved                     |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                             |
       |                                                             |
       |                     MAC                                     |
       |                                                             |
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT32                          ulAttrExistCtrlFlag;


    if ((PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET + PPPC_EAP_AKA_MAC_VALUE_LEN)
        != pstAttWalker->usAttrLen)
    {
        PPPC_WARNING_LOG("EAP-AKA: Invalid AT_MAC length");

        return VOS_ERR;
    }

    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_MAC_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_MAC have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_MAC_BIT);

    PS_MEM_CPY(&(pstAttWalker->pstPppcEapAkaPktAttrInfo->aucMac[0]),
               (pstAttWalker->pucAttPos + PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET),
               (pstAttWalker->usAttrLen - PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET));

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttNotificationParse
 功能描述  : 解析AT_NOTIFICATION属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年11月06日
   作    者   : j00353617
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttNotificationParse(
    PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P65
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |AT_NOTIFICATION | Length=1   |S|P|Notification Code          |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT32                          ulAttrExistCtrlFlag;


    if (PPPC_EAP_AKA_AT_NOTIFICATION_VALUE_LEN != pstAttWalker->usAttrLen)
    {
        PPPC_WARNING_LOG1("EAP-AKA: Invalid AT_NOTIFICATION length",
            pstAttWalker->usAttrLen);

        return VOS_ERR;
    }

    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_NOTIFICATION_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_NOTIFICATION have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_NOTIFICATION_BIT);

    pstAttWalker->pstPppcEapAkaPktAttrInfo->usNotification
        = pstAttWalker->pucAttPos[0] * 256 + pstAttWalker->pucAttPos[1];

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttAnyParse
 功能描述  : 解析AT_ANY_ID_REQ属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttAnyParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P54
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |AT_ANY_IQ_REQ | Length=1      |   Reserved                   |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT32                          ulAttrExistCtrlFlag;


    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_ANY_ID_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_ANY_ID have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_ANY_ID_BIT);

    pstAttWalker->pstPppcEapAkaPktAttrInfo->enEapAkaIdReqType
        = PPPC_EAP_AKA_ANY_ID_REQ;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttFullauthParse
 功能描述  : 解析FULLAUTH_ID_REQ属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttFullauthParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P54
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |AT_FULLAUTH   | Length=1      |   Reserved                   |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT32                          ulAttrExistCtrlFlag;


    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_FULLAUTH_ID_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_FULLAUTH_ID_REQ have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_FULLAUTH_ID_BIT);

    pstAttWalker->pstPppcEapAkaPktAttrInfo->enEapAkaIdReqType
        = PPPC_EAP_AKA_FULLAUTH_ID_REQ;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttCounterParse
 功能描述  : 解析AT_COUNTER属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttCounterParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P64
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |AT_COUNTER    | Length=1      |   Counter                    |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT32                          ulAttrExistCtrlFlag;


    if (PS_FALSE == pstAttWalker->enEncr)
    {
        PPPC_WARNING_LOG("EAP-AKA: Unencrypted AT_COUNTER");
        return VOS_ERR;
    }

    if (PPPC_EAP_AKA_AT_COUNTER_VALUE_LEN != pstAttWalker->usAttrLen)
    {
        PPPC_WARNING_LOG1("EAP-AKA: (encr) Invalid AT_COUNTER (ucAttrLen)",
            pstAttWalker->usAttrLen);

        return VOS_ERR;
    }

    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_COUNTER_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_COUNTER have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_COUNTER_BIT);
    pstAttWalker->pstPppcEapAkaPktAttrInfo->usCounter
        = pstAttWalker->pucAttPos[0] * 256 + pstAttWalker->pucAttPos[1];

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttNonceSParse
 功能描述  : 解析AT_NONCE_S属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttNonceSParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P65
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |   AT_NONCE_S | Length=5      | Reserved                     |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                             |
       |                                                             |
       |                     NONCE_S                                 |
       |                                                             |
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT32                          ulAttrExistCtrlFlag;


    if (PS_FALSE == pstAttWalker->enEncr)
    {
        PPPC_WARNING_LOG("EAP-AKA: Unencrypted AT_NONCE_S");

        return VOS_ERR;
    }

    if ((PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET + PPPC_EAP_AKA_NONCE_S_LEN)
        != pstAttWalker->usAttrLen)
    {
        PPPC_WARNING_LOG1("EAP-AKA: (encr) Invalid AT_NONCE_S (ucAttrLen)",
            (pstAttWalker->usAttrLen));

        return VOS_ERR;
    }

    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_NONCE_S_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_NONCE_S have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_NONCE_S_BIT);

    PS_MEM_CPY(&(pstAttWalker->pstPppcEapAkaPktAttrInfo->aucNonce_s[0]),
            (pstAttWalker->pucAttPos + PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET),
            (pstAttWalker->usAttrLen - PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET));

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttKdfInputParse
 功能描述  : 解析AT_KDF_INPUT属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttKdfInputParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 5448 P6
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |  AT_KDF_INPUT| Length        | Actual Network Name Length   |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                             |
       |                                                             |
       |                    Network Name                             |
       |                                                             |
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT32                          ucPlen;


    ucPlen = VOS_HTONS(*((VOS_UINT16 *)pstAttWalker->pucAttPos));
    pstAttWalker->pucAttPos += PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET;
    pstAttWalker->usAttrLen -= PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET;

    if (ucPlen > pstAttWalker->usAttrLen)
    {
        PPPC_WARNING_LOG2(
            "EAP-AKA': Invalid AT_KDF_INPUT (Actual Length, remaining length)",
            ucPlen, (pstAttWalker->usAttrLen));

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_KDF_INPUT_BIT);
    PS_MEM_CPY(&(pstAttWalker->pstPppcEapAkaPktAttrInfo->aucKdfInput[0]),
        pstAttWalker->pucAttPos, pstAttWalker->usAttrLen);
    pstAttWalker->pstPppcEapAkaPktAttrInfo->usKdfInputLen = pstAttWalker->usAttrLen;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttKdfParse
 功能描述  : 解析AT_KDF属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttKdfParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 5448 P9
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |  AT_KDF      | Length        | Key Derivation Function      |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT16  usKdfCount;


    if (PPPC_EAP_AKA_AT_KDF_VALUE_LEN != pstAttWalker->usAttrLen)
    {
        PPPC_WARNING_LOG1("EAP-AKA': Invalid AT_KDF len",
            (pstAttWalker->usAttrLen));

        return VOS_ERR;
    }

    usKdfCount  =   pstAttWalker->pstPppcEapAkaPktAttrInfo->usKdfCount;

    if (PPPC_EAP_AKA_PRIME_KDF_MAX == usKdfCount)
    {
        PPPC_WARNING_LOG("EAP-AKA': Too many AT_KDF attributes - ignore this");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_KDF_BIT);
    pstAttWalker->pstPppcEapAkaPktAttrInfo->ausKdf[usKdfCount]
        = VOS_HTONS(*((VOS_UINT16 *)pstAttWalker->pucAttPos));
    pstAttWalker->pstPppcEapAkaPktAttrInfo->usKdfCount++;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttIvParse
 功能描述  : 解析AT_IV属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttIvParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P59
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |   AT_IV      | Length=5      | Reserved                     |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                             |
       |                                                             |
       |             Initialization Vector                           |
       |                                                             |
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT32                          ulAttrExistCtrlFlag;


    if ((PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET + PPPC_EAP_AKA_IV_LEN)
        != pstAttWalker->usAttrLen)
    {
        PPPC_WARNING_LOG1("EAP-AKA: Invalid AT_IV length", (pstAttWalker->usAttrLen));

        return VOS_ERR;
    }

    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_IV_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_IV have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_IV_BIT);

    PS_MEM_CPY(&(pstAttWalker->pstPppcEapAkaPktAttrInfo->aucIv[0]),
               (pstAttWalker->pucAttPos + PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET),
               (pstAttWalker->usAttrLen - PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET));

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttEncrParse
 功能描述  : 解析AT_ENCR_DATA属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttEncrParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P59
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       | AT_ENCR_DATA | Length        | Reserved                     |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                             |
       |                                                             |
       |             Encrypted Data                                  |
       |                                                             |
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT16                          usEncDataLen;
    VOS_UINT8                           ucRemain;
    VOS_UINT32                          ulAttrExistCtrlFlag;


    usEncDataLen  =   (pstAttWalker->usAttrLen - PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET);
    ucRemain  =   TTF_MOD_GET(usEncDataLen, PPPC_EAP_AKA_16_BYTE);

    /*
       RFC4187
       The encryption algorithm requires the length of the plaintext to be a
       multiple of 16 bytes.  The sender may need to include the AT_PADDING
       attribute as the last attribute within AT_ENCR_DATA.  The AT_PADDING
       attribute is not included if the total length of other nested
       attributes within the AT_ENCR_DATA attribute is a multiple of 16
       bytes.  As usual, the Length of the Padding attribute includes the
       Attribute Type and Attribute Length fields.  The length of the
       Padding attribute is 4, 8, or 12 bytes.  It is chosen so that the
       length of the value field of the AT_ENCR_DATA attribute becomes a
       multiple of 16 bytes.
   */
    if (0 != ucRemain)
    {
        PPPC_WARNING_LOG1("EAP-SIM: Invalid AT_ENCR_DATA length", usEncDataLen);
        return VOS_ERR;
    }

    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_ENCR_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_ENCR_DATA have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_ENCR_BIT);

    PS_MEM_CPY(&(pstAttWalker->pstPppcEapAkaPktAttrInfo->aucEncrData[0]),
        pstAttWalker->pucAttPos + PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET,
        usEncDataLen);
    pstAttWalker->pstPppcEapAkaPktAttrInfo->usEncrDataLen = usEncDataLen;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttNextPseudonymParse
 功能描述  : 解析AT_NEXT_PSEUDONYM属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttNextPseudonymParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P57
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |AT_NEXT_PSEU..| Length        | Actual Pseudonym Length      |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                             |
       |                                                             |
       |             Next Pseudonym                                  |
       |                                                             |
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulAttrExistCtrlFlag;


    if (PS_FALSE == pstAttWalker->enEncr)
    {
        PPPC_WARNING_LOG("EAP-AKA: Unencrypted AT_NEXT_PSEUDONYM");

        return VOS_ERR;
    }

    ulLen = pstAttWalker->pucAttPos[0] * 256 + pstAttWalker->pucAttPos[1];

    if (pstAttWalker->usAttrLen < ulLen + PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET)
    {
        PPPC_WARNING_LOG2("EAP-AKA: (encr) Invalid AT_NEXT_PSEUDONYM (actual len, attr len)",
            ulLen, (pstAttWalker->usAttrLen));

        return VOS_ERR;
    }

    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_NEXT_PSEUDONYM_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_NEXT_PSEUDONYM have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_NEXT_PSEUDONYM_BIT);

    PS_MEM_CPY(&(pstAttWalker->pstPppcEapAkaPktAttrInfo->aucNextPseudonym[0]),
               pstAttWalker->pucAttPos + PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET,
               ulLen);
    pstAttWalker->pstPppcEapAkaPktAttrInfo->usNextPseudonymLen = (VOS_UINT16)ulLen;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttNextReauthParse
 功能描述  : 解析AT_NEXT_REAUTH_ID属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttNextReauthParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P57
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |AT_NEXT_REAU..| Length        |Actual Re-Auth Identity Length|
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                             |
       |                                                             |
       |             Next Fast Re-Authentication Username            |
       |                                                             |
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT32                              ulPlen;
    VOS_UINT32                              ulAttrExistCtrlFlag;


    if (PS_FALSE == pstAttWalker->enEncr)
    {
        PPPC_WARNING_LOG("EAP-AKA: Unencrypted AT_NEXT_REAUTH_ID");

        return VOS_ERR;
    }

    ulPlen = pstAttWalker->pucAttPos[0] * 256 + pstAttWalker->pucAttPos[1];

    if (pstAttWalker->usAttrLen < ulPlen + PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET)
    {
        PPPC_WARNING_LOG2("EAP-AKA: (encr) Invalid AT_NEXT_REAUTH_ID (actual len, attr len)",
            ulPlen, (pstAttWalker->usAttrLen));

        return VOS_ERR;
    }

    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_NEXT_REAUTH_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_NEXT_REAUTH_ID have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_NEXT_REAUTH_BIT);

    PS_MEM_CPY(&(pstAttWalker->pstPppcEapAkaPktAttrInfo->aucNextReauthId[0]),
               pstAttWalker->pucAttPos + PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET,
               ulPlen);
    pstAttWalker->pstPppcEapAkaPktAttrInfo->usNextReauthIdLen = (VOS_UINT16)ulPlen;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttCheckcodeParse
 功能描述  : 解析AT_CHECKCODE属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttCheckcodeParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P61
       0             1               2               3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       | AT_CHECKCODE| Length        | Reserved                      |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                             |
       | Checkcode (0 or 20 bytes)                                   |
       |                                                             |
       |                                                             |
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT32                          ulAttrExistCtrlFlag;


    pstAttWalker->pucAttPos += PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET;
    pstAttWalker->usAttrLen -= PPPC_EAP_AKA_ATTRIBUTE_RESERVED_VALUE_OFFSET;

    if ((0 != pstAttWalker->usAttrLen)
        && (PPPC_EAP_AKA_CHECKCODE_MAX_LEN != pstAttWalker->usAttrLen)
        && (PPPC_EAP_AKA_CHECKCODE_MIN_LEN != pstAttWalker->usAttrLen))
   {
        PPPC_WARNING_LOG1("EAP-AKA: Invalid AT_CHECKCODE len",
            (pstAttWalker->usAttrLen));

        return VOS_ERR;
    }

    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_CHECKCODE_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_CHECKCODE have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_CHECKCODE_BIT);

    PS_MEM_CPY(&(pstAttWalker->pstPppcEapAkaPktAttrInfo->aucCheckCode[0]),
               pstAttWalker->pucAttPos,
               pstAttWalker->usAttrLen);
    pstAttWalker->pstPppcEapAkaPktAttrInfo->usCheckCodeLen = pstAttWalker->usAttrLen;

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttResultParse
 功能描述  : 解析AT_RESULT_IND属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttResultParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 4187 P62
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |AT_RESULT_... | Length=1      |   Reserved                   |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT32                          ulAttrExistCtrlFlag;


    if (PS_TRUE == pstAttWalker->enEncr)
    {
        PPPC_WARNING_LOG("EAP-AKA: Encrypted AT_RESULT_IND");

        return VOS_ERR;
    }

    if (PPPC_EAP_AKA_AT_RESULT_IND_VALUE_LEN != pstAttWalker->usAttrLen)
    {
        PPPC_WARNING_LOG1("EAP-AKA: Invalid "
              "AT_RESULT_IND (ucAttrLen)",
              (unsigned long) pstAttWalker->usAttrLen);

        return VOS_ERR;
    }

    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_RESULT_IND_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_RESULT_IND have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_RESULT_IND_BIT);

    pstAttWalker->pstPppcEapAkaPktAttrInfo->enResultInd = PS_TRUE;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AttBiddingParse
 功能描述  : 解析AT_BIDDING属性
 输入参数  : pstAttWalker        指向解属性需要中间变量的结构体变量
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_AttBiddingParse(PPPC_EAP_AKA_ATT_WALKER_STRU *pstAttWalker)
{
    /*
       RFC 5448 P14
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |AT_BIDDING    | Length=1      |D| Reserved                   |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    VOS_UINT32                          ulAttrExistCtrlFlag;


    if (PPPC_EAP_AKA_AT_BIDDING_VALUE_LEN != pstAttWalker->usAttrLen)
    {
        PPPC_WARNING_LOG1("EAP-AKA: Invalid AT_BIDDING len",
            (pstAttWalker->usAttrLen));

        return VOS_ERR;
    }

    ulAttrExistCtrlFlag = pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_BIDDING_BIT))
    {
        PPPC_WARNING_LOG("EAP-AKA: duplicate AT_BIDDING have been included in the EAP request");

        return VOS_ERR;
    }

    TTF_SET_A_BIT(pstAttWalker->pstPppcEapAkaPktAttrInfo->ulAttrExistCtrlFlag,
        PPPC_EAP_AKA_BIDDING_BIT);

    pstAttWalker->pstPppcEapAkaPktAttrInfo->usBidding
        = pstAttWalker->pucAttPos[0] * 256 + pstAttWalker->pucAttPos[1];

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_FindTypeFun
 功能描述  : 根据TYPE查表返回相应处理函数的地址
 输入参数  : aucAttributeTypex  需要解析的TYPE
 输出参数  : 无
 返 回 值  : ATTRIBUTE_HANDLE_TAB[ulAttLoop].pfuncMatchHead 处理函数地址 VOS_NULL_PTR 空指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数

*****************************************************************************/
PPPC_EAP_AKA_MATCH_FUNC PPPC_EAP_AKA_FindTypeFun(VOS_UINT8 aucAttributeType)
{
    VOS_UINT32                          ulAttLoop;
    VOS_UINT32                          ulAttNum;

    ulAttNum = sizeof(g_stAttributeHandleTab)/sizeof(g_stAttributeHandleTab[0]);

    for (ulAttLoop = 0; ulAttLoop < ulAttNum; ulAttLoop++)
    {
        if (g_stAttributeHandleTab[ulAttLoop].aucAttributeType == aucAttributeType)
        {
            return g_stAttributeHandleTab[ulAttLoop].pfuncMatchHead;
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ParseAttr
 功能描述  : 解析Attribute
 输入参数  : pucAkaAttrStartPos  需要解析的Attribute首地址
             pucAkaAttrEndPos    需要解析的Attribute尾地址
             enEncr              属性需要加密
 输出参数  : 无
 返 回 值  : VOS_OK 成功 VOS_ERR 错误
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月06日
    作    者   : j00353617
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_ParseAttr
(
    VOS_UINT8                          *pucAkaAttrStartPos,
    VOS_UINT8                          *pucAkaAttrEndPos,
    PS_BOOL_ENUM_UINT8                  enEncr
)
{
    PPPC_EAP_AKA_ATT_WALKER_STRU        stAttWalker;
    PPPC_EAP_AKA_MATCH_FUNC             pfuncMatchHead;
    VOS_UINT32                          ulResult;
    VOS_UINT8                          *pucPos;
    VOS_UINT16                          usAttLen;
    VOS_UINT8                           ucAttType;
    const VOS_UINT8                     uc4Octet = 4;   /* attribute的长度跟length域的值的倍数 */
    const VOS_UINT8                     ucMaxNonSkipAttType = 127;


    stAttWalker.pstPppcEapAkaPktAttrInfo = &g_stPppcEapAkaPktAttrInfo;

    stAttWalker.enEncr = enEncr;
    pucPos = pucAkaAttrStartPos;

    while ( pucAkaAttrEndPos > pucPos)
    {
        if (pucAkaAttrEndPos < pucPos + PPPC_EAP_AKA_ATTRIBUTE_TYPE_VALUE_OFFSET)
        {
            PPPC_WARNING_LOG("EAP-AKA: Attribute overflow");

            return VOS_ERR;
        }

        ucAttType   =   pucPos[0];
        usAttLen    =   pucPos[1] * uc4Octet;
        if (pucAkaAttrEndPos < pucPos + usAttLen)
        {
            PPPC_WARNING_LOG3("EAP-AKA: Attribute overflow (pos len end)",
                pucPos, usAttLen, pucAkaAttrEndPos);

            return VOS_ERR;
        }

        if (0 == usAttLen)
        {
            PPPC_WARNING_LOG("EAP-AKA: Attribute underflow");

            return VOS_ERR;
        }

        /*
            0                   1                   2                   3
            0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
           +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
           |Attribute Type |    Length     | Value...
           +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        */
        /* 每个attribute在解析前, 都有此操作, 偏移掉前2个字节 */
        stAttWalker.pucAttPos = pucPos + PPPC_EAP_AKA_ATTRIBUTE_TYPE_VALUE_OFFSET;
        stAttWalker.usAttrLen = usAttLen - PPPC_EAP_AKA_ATTRIBUTE_TYPE_VALUE_OFFSET;

        pfuncMatchHead = PPPC_EAP_AKA_FindTypeFun(ucAttType);

        /*判断指针不为空*/
        if (VOS_NULL_PTR != pfuncMatchHead)
        {
            ulResult = (*pfuncMatchHead)(&stAttWalker);

            if (VOS_ERR == ulResult)
            {
                PPPC_WARNING_LOG("EAP-AKA': Parse failed");

                return VOS_ERR;
            }
        }
        else
        {
            /*
               RFC4187
               Attributes numbered within the range 0 through 127 are called
               non-skippable attributes.
            */
            if (ucAttType <= ucMaxNonSkipAttType)
            {
                /* 6.3.1. Peer Operation */
                PPPC_WARNING_LOG1("EAP-AKA: Unrecognized non-skippable attribute",
                    ucAttType);
                return VOS_ERR;
            }
            else
            {
                PPPC_WARNING_LOG1("EAP-AKA: Unrecognized skippable attribute ignored",
                    ucAttType);
            }
        }

        pucPos += usAttLen;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ClearIdentity
 功能描述  : 清除Identity
 输入参数  : ucId
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_ClearIdentity
(
    VOS_UINT8                           ucId
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo = VOS_NULL_PTR;
    PPPC_EAP_AKA_ID_INFO_STRU          *pstEapAkaIdInfo = VOS_NULL_PTR;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaIdInfo   = &(pstEapAkaDataInfo->stEapAkaIdInfo);


    /* 永远不清除Pseudonym信息??? */
    /* 清除ReauthId信息 */
    if ((0 != (ucId & PPPC_EAP_AKA_CLEAR_REAUTH_ID))
        && (0 != pstEapAkaIdInfo->usReauthIdLen))
    {
        PS_MEM_SET(&(pstEapAkaIdInfo->aucReauthId[0]), 0x0,
            PPPC_EAP_AKA_IDENTITY_MAX_LEN);
        pstEapAkaIdInfo->usReauthIdLen = 0;
    }

    /* 清除EapId信息 */
    if ((0 != (ucId & PPPC_EAP_AKA_CLEAR_EAP_ID))
        && (0 != pstEapAkaIdInfo->usLastEapIdentityLen))
    {
        PS_MEM_SET(&(pstEapAkaIdInfo->aucLastEapIdentity[0]), 0x0,
            PPPC_EAP_AKA_IDENTITY_MAX_LEN);
        pstEapAkaIdInfo->usLastEapIdentityLen = 0;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ParseEncr
 功能描述  : 解析加密的属性
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK; VOS_ERR;
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_ParseEncr(VOS_VOID)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    VOS_UINT8                          *pucEncrData;
    VOS_UINT8                          *pucDecryptedEndPos;
    VOS_UINT8                           aucDecrPayload[PPPC_EAP_AKA_ENRC_DATA_LEN];
    VOS_UINT8                          *pucKey;
    VOS_UINT8                          *pucIv;
    VOS_UINT32                          ulRes;
    VOS_UINT16                          usEncrDataLen;
    PS_BOOL_ENUM_UINT8                  enEncr;


    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo   = &g_stPppcEapAkaPktAttrInfo;

    pucEncrData         = &(pstEapAkaAttrInfo->aucEncrData[0]);
    usEncrDataLen       = pstEapAkaAttrInfo->usEncrDataLen;
    pucKey              = &(pstEapAkaDataInfo->stEapAkaKey.aucK_encr[0]);
    pucIv               = &(pstEapAkaAttrInfo->aucIv[0]);

    PS_MEM_SET(&(aucDecrPayload[0]), 0, PPPC_EAP_AKA_ENRC_DATA_LEN);
    ulRes = PPPC_AES_128_CBC_Decrypt(pucKey, pucIv, pucEncrData, usEncrDataLen, &(aucDecrPayload[0]));
    if (VOS_OK != ulRes)
    {
        PPPC_WARNING_LOG("Decrypt is fail");
        return VOS_ERR;
    }

    enEncr = PS_TRUE;
    pucDecryptedEndPos = &(aucDecrPayload[0]) + pstEapAkaAttrInfo->usEncrDataLen;
    ulRes  = PPPC_EAP_AKA_ParseAttr(&(aucDecrPayload[0]), pucDecryptedEndPos, enEncr);

    return ulRes;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_GetRand
 功能描述  : 获取16BYTES随机数
 输入参数  : 无
 输出参数  : pucRand --存储随机数的地址
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_GetRand
(
    VOS_UINT8                          *pucRand
)
{
    VOS_UINT32                          ulSeed;
    VOS_UINT32                          ulRandVal;
    VOS_UINT32                          ulLoop;
    const VOS_UINT32                    ulMax = 0x100;


    /*
     Please see [RFC4086] for more information about generating
     random numbers for security applications.
    */
    /* 获取时间tick数作为种子 */
    ulSeed = VOS_GetTick();
    VOS_SetSeed(ulSeed);

    for (ulLoop = 0; ulLoop < PPPC_EAP_AKA_IV_LEN; ulLoop++)
    {
        /* 生成随机数, 生成的范围:[0..max-1] */
        ulRandVal = VOS_Rand(ulMax);
        pucRand[ulLoop] = (VOS_UINT8)ulRandVal;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AddAtPadding
 功能描述  : ResponseReauth
 输入参数  : pucEapAkaRspPayloadInfo    --AT_PADDING填写的初始位置
             pucIv                      --IV value
             usEncrLen                  --PAD之前需要加密的数据长度
 输出参数  : pstEAPMethodOutput         --Response数据要填写的位置
 返 回 值  : usAttrLen                  --属性长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月13日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 PPPC_EAP_AKA_AddAtPadding
(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen,
    VOS_UINT16                          usDataMaxBuff
)
{
    VOS_UINT16                          usAttrLen      = 0;
    VOS_UINT16                          usPadLen       = 0;
    const VOS_UINT16                    usConstValue16 = 16;
    const VOS_UINT16                    usConstValue4  = 4;
    const VOS_UINT8                     ucPadHeader    = 2;
    VOS_UINT8                           aucPad[PPPC_EAP_AKA_PADDING_MAX_LEN];
    PPPC_EAP_AKA_ATTR_INFO_STRU         stEapAkaAttrInfo;


    /*
        The encryption algorithm requires the length of the plaintext to be a
        multiple of 16 bytes. The sender may need to include the AT_PADDING
        attribute as the last attribute within AT_ENCR_DATA. The AT_PADDING
        attribute is not included if the total length of other nested
        attributes within the AT_ENCR_DATA attribute is a multiple of 16
        bytes. As usual, the Length of the Padding attribute includes the
        Attribute Type and Attribute Length fields. The length of the
        Padding attribute is 4, 8, or 12 bytes. It is chosen so that the
        length of the value field of the AT_ENCR_DATA attribute becomes a
        multiple of 16 bytes. The actual pad bytes in the value field are
        set to zero (00 hexadecimal) on sending.
    */
    PS_MEM_SET(&(aucPad[0]), 0, PPPC_EAP_AKA_PADDING_MAX_LEN);

    if (0 != TTF_MOD_GET(usDataLen, usConstValue16))
    {
        usPadLen = usConstValue16 - TTF_MOD_GET(usDataLen, usConstValue16);
        if (usConstValue4 > usPadLen)
        {
            PPPC_WARNING_LOG1("invalid pad_len", usPadLen);
            return usAttrLen;
        }

        PS_MEM_SET(&stEapAkaAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTR_INFO_STRU));
        stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_PADDING;
        stEapAkaAttrInfo.usValue    = 0;
        stEapAkaAttrInfo.pData      = &(aucPad[0]);
        stEapAkaAttrInfo.usDataLen  = (VOS_UINT16)(usPadLen - ucPadHeader- sizeof(VOS_UINT16));
        usAttrLen = PPPC_EAP_AKA_MsgAddAttr(pucData,
                        &stEapAkaAttrInfo, usDataLen, usDataMaxBuff);

        return usAttrLen;
    }

    return usAttrLen;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_GetEncrPayload
 功能描述  : ResponseReauth
 输入参数  :
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_GetEncrPayload
(
    PPPC_EAP_METHOD_OUTPUT_STRU         *pstEAPMethodOutput,
    VOS_UINT8                           *pucEncrPayload,
    VOS_UINT16                          *pusEncrLen,
    VOS_UINT8                           *pucRandom,
    PS_BOOL_ENUM_UINT8                   enExistCounterTooSmall
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucKey;
    VOS_UINT8                           aucData[PPPC_EAP_AKA_ENRC_DATA_LEN];
    VOS_UINT16                          usDataLen = 0;
    VOS_UINT16                          usAttrLen = 0;
    VOS_UINT16                          usCounter;
    PPPC_EAP_AKA_ATTR_INFO_STRU         stEapAkaAttrInfo;


    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;

    pucKey              = &(pstEapAkaDataInfo->stEapAkaKey.aucK_encr[0]);
    PS_MEM_SET(&(aucData[0]), 0, PPPC_EAP_AKA_ENRC_DATA_LEN);
    PS_MEM_SET(&stEapAkaAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTR_INFO_STRU));
    if (PS_TRUE == enExistCounterTooSmall)
    {
       /* 添加AT_COUNTER_TOO_SMALL */
       /*
          0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          | AT_COUNTER...| Length = 1   | Reserved                      |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       */
        stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_COUNTER_TOO_SMALL;
        stEapAkaAttrInfo.usValue    = 0;
        stEapAkaAttrInfo.pData      = VOS_NULL_PTR;
        stEapAkaAttrInfo.usDataLen  = 0;
        usAttrLen = PPPC_EAP_AKA_MsgAddAttr(&(aucData[0]), &stEapAkaAttrInfo,
                        usDataLen, PPPC_EAP_AKA_ENRC_DATA_LEN);

        usDataLen  += usAttrLen;
        usCounter   = pstEapAkaDataInfo->usCounterTooSmall;
   }
   else
   {
       usCounter = pstEapAkaDataInfo->stEapAkaAuthPara.usCounter;
   }

   /* 添加AT_COUNTER */
   /*
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       | AT_COUNTER  | Length = 1    | Counter                       |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   */

   stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_COUNTER;
   stEapAkaAttrInfo.usValue    = usCounter;
   stEapAkaAttrInfo.pData      = VOS_NULL_PTR;
   stEapAkaAttrInfo.usDataLen  = 0;
   usAttrLen = PPPC_EAP_AKA_MsgAddAttr(&(aucData[usDataLen]), &stEapAkaAttrInfo,
                   usDataLen, PPPC_EAP_AKA_ENRC_DATA_LEN);

   usDataLen  += usAttrLen;

   /* 添加AT_PADDING */
   usAttrLen = PPPC_EAP_AKA_AddAtPadding(&(aucData[usDataLen]), usDataLen, PPPC_EAP_AKA_ENRC_DATA_LEN);

   usDataLen  += usAttrLen;

   /* 运行加密算法 */
   PPPC_AES_128_CBC_Encrypt(pucKey, pucRandom, &(aucData[0]), usDataLen, pucEncrPayload);

   *pusEncrLen = usDataLen;

   return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ResponseReauth
 功能描述  : ResponseReauth
 输入参数  :
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_ResponseReauth
(
    PPPC_EAP_METHOD_OUTPUT_STRU         *pstEAPMethodOutput,
    PS_BOOL_ENUM_UINT8                   enExistCounterTooSmall
)
{
    VOS_UINT8                          *pucEapAkaRspPayloadInfo = VOS_NULL_PTR;
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo       = VOS_NULL_PTR;
    VOS_UINT16                          usAttrLen               = 0;
    VOS_UINT16                          usEapLen                = 0;
    VOS_UINT8                           ucEapAkaSubType;
    VOS_UINT8                           aucRandom[PPPC_EAP_AKA_IV_LEN];
    VOS_UINT8                           aucEncrPayload[PPPC_EAP_AKA_ENRC_DATA_LEN];
    VOS_UINT16                          usEncrLen = 0;
    PPPC_EAP_AKA_ATTR_INFO_STRU         stEapAkaAttrInfo;
    VOS_UINT32                          ulLocalResult;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    PS_MEM_SET(&(aucRandom[0]), 0, PPPC_EAP_AKA_IV_LEN);
    PS_MEM_SET(&(aucEncrPayload[0]), 0, PPPC_EAP_AKA_ENRC_DATA_LEN);

    /* 1) 填充Subtype和Reserved 3字节 */
    ucEapAkaSubType = PPPC_EAP_AKA_SUBTYPE_REAUTHENTICATION;
    PPPC_EAP_AKA_RespMsgInit(pstEAPMethodOutput, ucEapAkaSubType);

    /* Attribute Field */
    usEapLen = *(pstEAPMethodOutput->pusRespLen);
    pucEapAkaRspPayloadInfo = &(pstEAPMethodOutput->pucPktData[usEapLen]);

    PPPC_EAP_AKA_GetRand(&(aucRandom[0]));

    /* 2) 添加AT_IV */
    /*
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       | AT_IV       | Length = 5    | Reserved                      |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                             |
       | Initialization Vector                                       |
       |                                                             |
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    PS_MEM_SET(&stEapAkaAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTR_INFO_STRU));
    stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_IV;
    stEapAkaAttrInfo.usValue    = 0;
    stEapAkaAttrInfo.pData      = &(aucRandom[0]);
    stEapAkaAttrInfo.usDataLen  = PPPC_EAP_AKA_IV_LEN;
    usAttrLen = PPPC_EAP_AKA_MsgAddAttr(pucEapAkaRspPayloadInfo,
                &stEapAkaAttrInfo, usEapLen, PPPC_EAP_MAX_PACKET_LEN);

    usEapLen  += usAttrLen;

    /* 更新到下一个属性地址 */
    pucEapAkaRspPayloadInfo = &(pstEAPMethodOutput->pucPktData[usEapLen]);

    /* 3) 添加AT_ENCR_DATA 头部信息 */
    /*
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       | AT_ENCR_DATA | Length       | Reserved                      |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                             |
       . Encrypted Data . . .
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */

    PPPC_EAP_AKA_GetEncrPayload(pstEAPMethodOutput, &(aucEncrPayload[0]),
            &usEncrLen, &(aucRandom[0]), enExistCounterTooSmall);

    PS_MEM_SET(&stEapAkaAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTR_INFO_STRU));
    stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_ENCR_DATA;
    stEapAkaAttrInfo.usValue    = 0;
    stEapAkaAttrInfo.pData      = &(aucEncrPayload[0]);
    stEapAkaAttrInfo.usDataLen  = usEncrLen;
    usAttrLen = PPPC_EAP_AKA_MsgAddAttr(pucEapAkaRspPayloadInfo, &stEapAkaAttrInfo,
                                usEapLen, PPPC_EAP_MAX_PACKET_LEN);
    usEapLen  += usAttrLen;

    /* 4) Add AT_CHECKCODE */
    pucEapAkaRspPayloadInfo = &(pstEAPMethodOutput->pucPktData[usEapLen]);
    usAttrLen = PPPC_EAP_AKA_AddCheckCode(pucEapAkaRspPayloadInfo, usEapLen);
    usEapLen  += usAttrLen;

    /* 更新EAP包Len长度 */
    PPPC_EAP_UpdateLen(pstEAPMethodOutput->pucPktData, pstEAPMethodOutput->pusRespLen, usEapLen);

    /* 5) Add AT_MAC */
    usAttrLen = PPPC_EAP_AKA_MsgAddAtMacAttr(pstEAPMethodOutput, &(pstEapAkaDataInfo->stEapAkaAuthPara.aucNonce_s[0]),
                    PPPC_EAP_AKA_NONCE_S_LEN);

    usEapLen  += usAttrLen;

    /* 更新EAP包Len长度 */
    PPPC_EAP_UpdateLen(pstEAPMethodOutput->pucPktData, pstEAPMethodOutput->pusRespLen, usEapLen);

    /* AKA通知EAP Peer的鉴权结果 */
    if (PS_FALSE == enExistCounterTooSmall)
    {
        ulLocalResult = VOS_OK;
        PPPC_EAP_PeerProcessEvent(pstEAPMethodOutput->ulPppId,
                    PPPC_EAP_PEER_AUTH_IND_EVENT, &ulLocalResult);
    }

    /* 给EAP发送Response报文 */
    PPPC_EAP_SendResponse(pstEAPMethodOutput->ulPppId);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ResponseChallenge
 功能描述  : EAP-AKA处理鉴权消息
 输入参数  : pstEAPMethodInput --EAP递给方法的包
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_ResponseChallenge
(
    PPPC_EAP_AUTH_RESULT_STRU           *pstResult
)
{
    VOS_UINT8                          *pucEapAkaRspPayloadInfo;
    VOS_UINT16                          usAttrLen = 0;
    VOS_UINT16                          usEapLen;
    VOS_UINT8                           ucEapAkaSubType;
    VOS_UINT8                           ucResByteLen = 0;
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo = VOS_NULL_PTR;
    PPPC_EAP_AKA_ATTR_INFO_STRU         stEapAkaAttrInfo;
    VOS_UINT32                          ulLocalResult;
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput;


    pstEAPMethodOutput = &g_stEAPAkaMethodOutput;
    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;

    /* 1) 填充Subtype和Reserved 3字节 */
    ucEapAkaSubType = PPPC_EAP_AKA_SUBTYPE_CHALLENGE;
    PPPC_EAP_AKA_RespMsgInit(pstEAPMethodOutput, ucEapAkaSubType);

    /* 2) 添加AT_RES属性 */
    /*
       rfc 4187 p56
       0               1               2               3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       | AT_RES        | Length        | RES Length                    |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-|
       |                                                               |
       | RES                                                           |
       |                                                               |
       |                                                               |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       The value field of this attribute begins with the 2-byte RES Length,
       which identifies the exact length of the RES in bits. The RES length
       is followed by the AKA RES parameter. According to [TS33.105], the
       length of the AKA RES can vary between 32 and 128 bits. Because the
       length of the AT_RES attribute must be a multiple of 4 bytes, the
       sender pads the RES with zero bits where necessary.
    */
    /* 取属性填写的开始位置 */
     usEapLen = *(pstEAPMethodOutput->pusRespLen);

    /* Attribute Field */
    pucEapAkaRspPayloadInfo = &(pstEAPMethodOutput->pucPktData[usEapLen]);
    ucResByteLen = pstResult->ucAuthRseLen;
    PS_MEM_SET(&stEapAkaAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTR_INFO_STRU));
    stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_RES;
    stEapAkaAttrInfo.usValue    = TTF_BYTE2BIT(ucResByteLen);
    stEapAkaAttrInfo.pData      = &(pstResult->aucAuthRes[0]);
    stEapAkaAttrInfo.usDataLen  = ucResByteLen;

    usAttrLen = PPPC_EAP_AKA_MsgAddAttr(pucEapAkaRspPayloadInfo, &stEapAkaAttrInfo,
                    usEapLen, PPPC_EAP_MAX_PACKET_LEN);


    /* 3) 添加AT_CHECKCODE属性 */
    usEapLen = *(pstEAPMethodOutput->pusRespLen) + usAttrLen;
    pucEapAkaRspPayloadInfo = &(pstEAPMethodOutput->pucPktData[usEapLen]);
    usAttrLen = PPPC_EAP_AKA_AddCheckCode(pucEapAkaRspPayloadInfo, usEapLen);

    /* 4) 添加AT_RESULT_IND属性 */
    usEapLen = usEapLen + usAttrLen;
    pucEapAkaRspPayloadInfo = &(pstEAPMethodOutput->pucPktData[usEapLen]);
    if (PS_TRUE == pstEapAkaDataInfo->enResultInd)
    {
        /*
          0               1             2               3
          0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
          | AT_RESULT_...| Length = 1 | Reserved                        |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        */

        PS_MEM_SET(&stEapAkaAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTR_INFO_STRU));
        stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_RESULT_IND;
        stEapAkaAttrInfo.usValue    = 0;
        stEapAkaAttrInfo.pData      = VOS_NULL_PTR;
        stEapAkaAttrInfo.usDataLen  = 0;
        usAttrLen = PPPC_EAP_AKA_MsgAddAttr(pucEapAkaRspPayloadInfo, &stEapAkaAttrInfo,
                           usEapLen, PPPC_EAP_MAX_PACKET_LEN);
        usEapLen = usEapLen + usAttrLen;
    }

    /* 更新EAP包Len长度 */
    PPPC_EAP_UpdateLen(pstEAPMethodOutput->pucPktData, pstEAPMethodOutput->pusRespLen, usEapLen);;

    /* 添加AT_MAC属性 */
    usAttrLen = PPPC_EAP_AKA_MsgAddAtMacAttr(pstEAPMethodOutput, VOS_NULL_PTR, 0);
    usEapLen = usEapLen + usAttrLen;

    /* 更新EAP包Len长度 */
    PPPC_EAP_UpdateLen(pstEAPMethodOutput->pucPktData, pstEAPMethodOutput->pusRespLen, usEapLen);

    /* AKA通知EAP Peer的鉴权结果 */
    ulLocalResult = VOS_OK;
    PPPC_EAP_PeerProcessEvent(pstEAPMethodOutput->ulPppId,
            PPPC_EAP_PEER_AUTH_IND_EVENT, &ulLocalResult);

    /* 给EAP发送Response报文 */
    PPPC_EAP_SendResponse(pstEAPMethodOutput->ulPppId);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_BuildPermanentId
 功能描述  : 使用IMSI构造永久性NAI
 输入参数  : enType - AKA or AKA'
             aucCImsi - IMSI
 输出参数  : pucNai - 获取的NAI
             pusNaiLen - 获取的NAI长度
 返 回 值  :
 调用函数  :
 被调函数  :
 说    明  : 调用者需要保证留有足够的空间来存储NAI

 修改历史      :
  1.日    期   : 2015年11月13日
    作    者   : liukai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_BuildPermanentId(VOS_UINT8 aucNai[],
            VOS_UINT16 *pusNaiLen, PPPC_EAP_METHOD_TYPE_ENUM_UINT16 enType,
            VOS_UINT8 aucCImsi[])
{
    VOS_UINT8                           aucMcc[PPPC_EAP_CIMSI_MCC_MAX_LEN];
    VOS_UINT8                           aucMnc[PPPC_EAP_CIMSI_MNC_MAX_LEN];
    PPPC_EAP_PERMANENT_NAI_REALM_PART_INFO_STRU     *pstPartChar;
    VOS_UINT8                           ucMncDigit;
    VOS_UINT16                          usLen = 0;

    /*
       From RFC 4187, 4.1.1.1 General,
       "Subscribers of mobile networks are identified with the International
       Mobile Subscriber Identity (IMSI) [TS23.003].  The IMSI is a string
       of not more than 15 digits.  It is composed of a Mobile Country Code
       (MCC) of 3 digits, a Mobile Network Code (MNC) of 2 or 3 digits, and
       a Mobile Subscriber Identification Number (MSIN) of not more than 10
       digits.  MCC and MNC uniquely identify the GSM operator and help
       identify the AuC from which the authentication vectors need to be
       retrieved for this subscriber."
   */
    /*
       From 23003-9f0, 2.2 Composition of IMSI
       |-----------------------IMSI(<=15 digit)-----------------------|
       |---MCC(3 digit)---|---MNC(2/3 digit)---|---MSIN(<=10 digit)---|
    */
    const VOS_UINT8                     ucMccStartPos = 0;   /* 在IMSI中MCC从0th开始 */
    const VOS_UINT8                     ucMncStartPos = 3;   /* 在IMSI中MCC从3th开始 */
    const PPPC_EAP_PERMANENT_NAI_REALM_PART_INFO_STRU astRealmPart[PPPC_EAP_PERMANENT_NAI_REALM_MAX_PART] =
    {
        {11, {0, 0, 0}, {'n', 'a', 'i', '.', 'e', 'p', 'c', '.', 'm', 'n', 'c'}},
        {4,  {0, 0, 0}, {'.', 'm', 'c', 'c'}},
        {16, {0, 0, 0}, {'.', '3', 'g', 'p', 'p', 'n', 'e', 't', 'w', 'o', 'r', 'k', '.', 'o', 'r', 'g'}}
    };


    /* 计算MCC */
    PS_MEM_SET(aucMcc, 0, PPPC_EAP_CIMSI_MCC_MAX_LEN);
    PS_MEM_CPY(aucMcc, &aucCImsi[ucMccStartPos], PPPC_EAP_CIMSI_MCC_MAX_LEN);

    /*
       From 23003-9f0, 19.2 Home Network Realm/Domain,
       "NOTE: If it is not possible for a UE to identify whether a 2 or 3 digit
       MNC is used (e.g. USIM is inserted and the length of MNC in the IMSI is
       not available in the "Administrative data" data file), it is implementation
       dependent how the UE determines the length of the MNC (2 or 3 digits)."

       从51011的10.3.18中得出6FAD中存有MNC的长度
    */
    /*
       From 23003-9f0, 19.2 Home Network Realm/Domain,
       "Both the "<MNC>" and "<MCC>" fields are 3 digits long. If the MNC of
       the PLMN is 2 digits, then a zero shall be added at the beginning."
       如果MNC长度为2 第一个digit填'0'
    */
    ucMncDigit = PPPC_UIM_GetImsiMncLen();
    if (PPPC_EAP_CIMSI_MNC_MAX_LEN == ucMncDigit)
    {
        PS_MEM_CPY(&aucMnc[0],
            &aucCImsi[ucMncStartPos], ucMncDigit);
    }
    else
    {
        aucMnc[0] = '0';
        PS_MEM_CPY(&aucMnc[PPPC_EAP_CIMSI_MNC_MAX_LEN-ucMncDigit],
            &aucCImsi[ucMncStartPos], ucMncDigit);
    }

    /*
       From RFC 4187, 4.1.1.1 General,
       "Internet AAA protocols identify users with the Network Access
       Identifier (NAI) [RFC4282].  When used in a roaming environment, the
       NAI is composed of a username and a realm, separated with "@"
       (username@realm).  The username portion identifies the subscriber
       within the realm.

       This section specifies the peer identity format used in EAP-AKA.  In
       this document, the term identity or peer identity refers to the whole
       identity string that is used to identify the peer.  The peer identity
       may include a realm portion.  "Username" refers to the portion of the
       peer identity that identifies the user, i.e., the username does not
       include the realm portion."
    */
    /*
       From 23003-9f0, 19.3.2 Root NAI
       "The Root NAI shall take the form of an NAI, and shall have the form
       username@realm as specified in clause 2.1 of IETF RFC 4282 [53].

       The format of the username part of the Root NAI shall comply with
       IETF RFC 4187 for use with EAP AKA authentication. For EAP-AKA',
       see IETF RFC 5448, the Root NAI shall comply with IETF RFC 4187 except
       that the username part of the Root NAI shall be prepended with the single
       digit "6".

       When the username part includes the IMSI, the Root NAI shall be built
       according to the following steps:
       1.Generate an identity conforming to NAI format from IMSI as defined in
       EAP AKA as appropriate;
       2.Convert the leading digits of the IMSI, i.e. MNC and MCC, into a domain
       name, as described in subclause 19.2.
       3.Prefix domain name with the label of "nai".

       The result will be a root NAI of the form:
       "0<IMSI>@nai.epc.mnc<MNC>.mcc<MCC>.3gppnetwork.org" for EAP AKA authentication
       "6<IMSI>@nai.epc.mnc<MNC>.mcc<MCC>.3gppnetwork.org" for EAP AKA' authentication

       For example, if the IMSI is 234150999999999 (MCC = 234, MNC = 15), the
       root NAI then takes the form as 0234150999999999@nai.epc.mnc015.mcc234.3gppnetwork.org
       for EAP AKA authentication, and takes the form as
       6234150999999999@nai.epc.mnc015.mcc234.3gppnetwork.org for EAP AKA' authentication."
    */
    if (PPPC_EAP_METHOD_TYPE_AKA == enType)
    {
        aucNai[usLen] = '0';
    }

    if (PPPC_EAP_METHOD_TYPE_AKA_PRIME == enType)
    {
        aucNai[usLen] = '6';
    }

    usLen++;

    PS_MEM_CPY(&aucNai[usLen], aucCImsi, PS_CUE_IMSI_MAX_SIZE);
    usLen += PS_CUE_IMSI_MAX_SIZE;

    /* 到此, 完成username的构造 */

    aucNai[usLen] = '@';
    usLen++;

    /*下边构造realm, 形如"nai.epc.mnc<MNC>.mcc<MCC>.3gppnetwork.org"*/
    pstPartChar = (PPPC_EAP_PERMANENT_NAI_REALM_PART_INFO_STRU*)&(astRealmPart[PPPC_EAP_PERMANENT_NAI_REALM_PART_ONE]);
    PS_MEM_CPY(&aucNai[usLen],
               pstPartChar->aucPartChar,
               pstPartChar->ucPartCharNum);
    usLen += pstPartChar->ucPartCharNum;

    /* 注意MNC在前面 */
    PS_MEM_CPY(&aucNai[usLen],
               aucMnc,
               PPPC_EAP_CIMSI_MNC_MAX_LEN);
    usLen += PPPC_EAP_CIMSI_MNC_MAX_LEN;

    pstPartChar = (PPPC_EAP_PERMANENT_NAI_REALM_PART_INFO_STRU*)&(astRealmPart[PPPC_EAP_PERMANENT_NAI_REALM_PART_TWO]);
    PS_MEM_CPY(&aucNai[usLen],
               pstPartChar->aucPartChar,
               pstPartChar->ucPartCharNum);
    usLen += pstPartChar->ucPartCharNum;

    PS_MEM_CPY(&aucNai[usLen],
               aucMcc,
               PPPC_EAP_CIMSI_MCC_MAX_LEN);
    usLen += PPPC_EAP_CIMSI_MCC_MAX_LEN;

    pstPartChar = (PPPC_EAP_PERMANENT_NAI_REALM_PART_INFO_STRU*)&(astRealmPart[PPPC_EAP_PERMANENT_NAI_REALM_PART_THREE]);
    PS_MEM_CPY(&aucNai[usLen],
               pstPartChar->aucPartChar,
               pstPartChar->ucPartCharNum);
    usLen += pstPartChar->ucPartCharNum;

    *pusNaiLen = usLen;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_GetPermanentNAI
 功能描述  : 获取永久性NAI
 输入参数  : enType - AKA or AKA'
 输出参数  : pucNai - 获取的NAI
             pusNaiLen - 获取的NAI长度
 返 回 值  :
 调用函数  :
 被调函数  :
 说    明  : 调用者需要保证留有足够的空间来存储NAI

 修改历史      :
  1.日    期   : 2015年11月13日
    作    者   : liukai
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_GetPermanentNAI(VOS_UINT8 aucNai[],
            VOS_UINT16 *pusNaiLen, PPPC_EAP_METHOD_TYPE_ENUM_UINT16 enType)
{
    VOS_UINT8                           aucCImsi[PS_CUE_IMSI_MAX_SIZE];
    PPPC_EAP_AKA_ID_INFO_STRU          *pstEapAkaIdInfo;
    VOS_UINT32                          ulResult;


    if ((VOS_NULL_PTR == aucNai) || (VOS_NULL_PTR == pusNaiLen))
    {
        PPPC_WARNING_LOG2("invalid input when GetPermanentNAI", aucNai, pusNaiLen);

        return VOS_ERR;
    }

    if (PPPC_EAP_METHOD_TYPE_ENUM_BUTT <= enType)
    {
        PPPC_WARNING_LOG1("invalid type when GetPermanentNAI", enType);

        return VOS_ERR;
    }

    pstEapAkaIdInfo =   &g_stPppcEapAkaDataInfo.stEapAkaIdInfo;

    if (0 == pstEapAkaIdInfo->usPermenentIdLen) /* 未保存 */
    {
        ulResult    =   PPPC_UIM_GetUsimIMSI(aucCImsi);

        if (VOS_OK != ulResult)
        {
            PPPC_WARNING_LOG("fail to get CIMSI");

            return VOS_ERR;
        }

        PPPC_EAP_AKA_BuildPermanentId(aucNai, pusNaiLen, enType, aucCImsi);

        /* 保存PermanentId到AKA实体中 */
        PS_MEM_CPY(pstEapAkaIdInfo->aucPermenentId, aucNai, *pusNaiLen);
        pstEapAkaIdInfo->usPermenentIdLen = *pusNaiLen;
    }
    else
    {
        PS_MEM_CPY(aucNai, pstEapAkaIdInfo->aucPermenentId,
            pstEapAkaIdInfo->usPermenentIdLen);
        *pusNaiLen  =   pstEapAkaIdInfo->usPermenentIdLen;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_GetResponseIdentity
 功能描述  : 获取要发送的NAI
 输入参数  : enEapAkaIdReqType --EAP-AKA Identity的Type
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : VOS_OK; VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_GetResponseIdentity
(
    PPPC_EAP_AKA_ID_REQ_TYPE_ENUM_UINT16    enEapAkaIdReqType,
    VOS_UINT8                             **ppucIdentity,
    VOS_UINT16                             *pusIdentityLen
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo   = VOS_NULL_PTR;
    PPPC_EAP_AKA_ID_INFO_STRU          *pstEapAkaIdInfo     = VOS_NULL_PTR;
    VOS_UINT16                          usPermenentIdLen    = 0;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaIdInfo   = &(pstEapAkaDataInfo->stEapAkaIdInfo);

    /*
       RFC4187 P25
       If the EAP-Request/AKA-Identity includes AT_ANY_ID_REQ, and if the
       peer has maintained fast re-authentication state information and
       wants to use fast re-authentication, then the peer responds with
       EAP-Response/AKA-Identity and includes the fast re-authentication
       identity in AT_IDENTITY. Else, if the peer has a pseudonym identity
       available, then the peer responds with EAP-Response/AKA-Identity and
       includes the pseudonym identity in AT_IDENTITY. Else, the peer
       responds with EAP-Response/AKA-Identity and includes the permanent
       identity in AT_IDENTITY.
    */

    pstEapAkaDataInfo->enReauth = PS_FALSE;
    if ((PPPC_EAP_AKA_ANY_ID_REQ == enEapAkaIdReqType)
        && (0 != pstEapAkaIdInfo->usReauthIdLen))
    {
       *ppucIdentity     = &(pstEapAkaIdInfo->aucReauthId[0]);
       *pusIdentityLen   = pstEapAkaIdInfo->usReauthIdLen;
        pstEapAkaDataInfo->enReauth = PS_TRUE;
    }
    else if (((PPPC_EAP_AKA_ANY_ID_REQ == enEapAkaIdReqType)
                || (PPPC_EAP_AKA_FULLAUTH_ID_REQ == enEapAkaIdReqType))
                && (0 != pstEapAkaIdInfo->usPseudonymLen))
    {
       *ppucIdentity    = &(pstEapAkaIdInfo->aucPseudonym[0]);
       *pusIdentityLen  = pstEapAkaIdInfo->usPseudonymLen;
        PPPC_EAP_AKA_ClearIdentity(PPPC_EAP_AKA_CLEAR_REAUTH_ID);
    }
    else if (PPPC_EAP_AKA_ID_REQ_BUTT > enEapAkaIdReqType)
    {
        if (0 == pstEapAkaIdInfo->usPermenentIdLen)
        {
            (VOS_VOID)PPPC_EAP_AKA_GetPermanentNAI(&(pstEapAkaIdInfo->aucPermenentId[0]),
                    &usPermenentIdLen, pstEapAkaDataInfo->enEapMethod);
            pstEapAkaIdInfo->usPermenentIdLen = usPermenentIdLen;
        }

       *ppucIdentity    = &(pstEapAkaIdInfo->aucPermenentId[0]);
       *pusIdentityLen  = pstEapAkaIdInfo->usPermenentIdLen;
        PPPC_EAP_AKA_ClearIdentity(PPPC_EAP_AKA_CLEAR_REAUTH_ID|PPPC_EAP_AKA_CLEAR_EAP_ID);
    }
    else
    {
       *ppucIdentity   = VOS_NULL_PTR;
       *pusIdentityLen = 0;
        PPPC_WARNING_LOG("enEapAkaIdReqType "
               "is error");
        return VOS_ERR;
    }

    /* 将当前使用的Identity保存到LastIdentity*/
    PS_MEM_SET(&(pstEapAkaIdInfo->aucLastEapIdentity[0]), 0, pstEapAkaIdInfo->usLastEapIdentityLen);
    PS_MEM_CPY(&(pstEapAkaIdInfo->aucLastEapIdentity[0]), *ppucIdentity, *pusIdentityLen);
    pstEapAkaIdInfo->usLastEapIdentityLen = *pusIdentityLen;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ResponseIdentity
 功能描述  : EAP-AKA处理PPPC_EAP_AKA_SUBTYPE_IDENTITY消息
 输入参数  : enEapAkaIdReqType --EAP-AKA Identity的Type
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : VOS_OK; VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_ResponseIdentity
(
    PPPC_EAP_AKA_ID_REQ_TYPE_ENUM_UINT16    enEapAkaIdReqType,
    PPPC_EAP_METHOD_OUTPUT_STRU            *pstEAPMethodOutput
)
{
    VOS_UINT8                          *pucEapAkaRspPayloadInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucIdentity             = VOS_NULL_PTR;
    VOS_UINT8                           ucEapAkaSubType         = 0;
    VOS_UINT16                          usIdentityLen           = 0;
    VOS_UINT16                          usAttrLen               = 0;
    VOS_UINT16                          usEapLen                = 0;
    VOS_UINT32                          ulRes;
    PPPC_EAP_AKA_ATTR_INFO_STRU         stEapAkaAttrInfo;


    /* 获取要发送的NAI */
    ulRes = PPPC_EAP_AKA_GetResponseIdentity(enEapAkaIdReqType, &pucIdentity, &usIdentityLen);
    if (VOS_OK != ulRes)
    {
        PPPC_WARNING_LOG("EAP-AKA: GetResponseIdentity is fail ");
        PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);
        return VOS_ERR;
    }

    /* 填写Response报文 */
    /* 1) 填充Subtype和Reserved 3字节 */
    ucEapAkaSubType = PPPC_EAP_AKA_SUBTYPE_IDENTITY;
    PPPC_EAP_AKA_RespMsgInit(pstEAPMethodOutput, ucEapAkaSubType);

    /* 2) 填充AT_IDENTITY Attribute Field */
    /*
       0               1             2               3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       | AT_IDENTITY   | Length      |  Actual Identity Length       |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                                                             |
       .                        Identity . . .
       |                                                             |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */
    usEapLen                = *(pstEAPMethodOutput->pusRespLen);
    pucEapAkaRspPayloadInfo = &(pstEAPMethodOutput->pucPktData[usEapLen]);

    PS_MEM_SET(&stEapAkaAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTR_INFO_STRU));
    stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_IDENTITY;
    stEapAkaAttrInfo.usValue    = usIdentityLen;
    stEapAkaAttrInfo.pData      = pucIdentity;
    stEapAkaAttrInfo.usDataLen  = usIdentityLen;
    usAttrLen = PPPC_EAP_AKA_MsgAddAttr(pucEapAkaRspPayloadInfo, &stEapAkaAttrInfo,
                            usEapLen, PPPC_EAP_MAX_PACKET_LEN);

    /* 调用PPPC接口更新EAP长度 */
    usEapLen = *(pstEAPMethodOutput->pusRespLen) + usAttrLen;

    PPPC_EAP_UpdateLen(pstEAPMethodOutput->pucPktData, pstEAPMethodOutput->pusRespLen, usEapLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ResponseNotification
 功能描述  : EAP-AKA处理鉴权消息
 输入参数  : 无
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_ResponseNotification
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput
)
{
    VOS_UINT8                          *pucEapAkaRspPayloadInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucK_aut          = VOS_NULL_PTR;
    VOS_UINT16                          usAttrLen         = 0;
    VOS_UINT16                          usEncrLen         = 0;
    VOS_UINT16                          usEapLen;
    VOS_UINT8                           ucEapAkaSubType;
    VOS_UINT8                           aucRandom[PPPC_EAP_AKA_IV_LEN];
    VOS_UINT8                           aucEncrPayload[PPPC_EAP_AKA_ENRC_DATA_LEN];
    PS_BOOL_ENUM_UINT8                  enExistCounterTooSmall;
    PPPC_EAP_AKA_ATTR_INFO_STRU         stEapAkaAttrInfo;


    PS_MEM_SET(&(aucRandom[0]), 0, PPPC_EAP_AKA_IV_LEN);
    PS_MEM_SET(&(aucEncrPayload[0]), 0, PPPC_EAP_AKA_ENRC_DATA_LEN);

    /*
       RFC4187 P52
       The AT_MAC attribute MUST be included in cases when the P bit of the
       notification code in AT_NOTIFICATION of EAP-Request/AKA-Notification
       is set to zero, and MUST NOT be included in cases when the P bit is
       set to one. The P bit is discussed in Section 6.
       If EAP-Request/AKA-Notification is used on a fast re-authentication
       exchange, and if the P bit in AT_NOTIFICATION is set to zero, then
       AT_COUNTER is used for replay protection. In this case, the
       AT_ENCR_DATA and AT_IV attributes MUST be included, and the
       encapsulated plaintext attributes MUST include the AT_COUNTER
       attribute. The counter value included in AT_COUNTER MUST be the same
       as in the EAP-Request/AKA-Reauthentication packet on the same fast
       re-authentication exchange.
    */
    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo = &g_stPppcEapAkaPktAttrInfo;

    /* 填充Subtype和Reserved 3字节 */
    ucEapAkaSubType = PPPC_EAP_AKA_SUBTYPE_NOTIFICATION;
    PPPC_EAP_AKA_RespMsgInit(pstEAPMethodOutput, ucEapAkaSubType);

    if (0 == (pstEapAkaAttrInfo->usNotification & PPPC_EAP_AKA_NOTIFICATION_P_IS_1))
    {
        pucK_aut = &(pstEapAkaDataInfo->stEapAkaKey.aucK_aut[0]);
    }
    else
    {
        pucK_aut = VOS_NULL_PTR;
    }

    usEapLen = *(pstEAPMethodOutput->pusRespLen);

    if ((VOS_NULL_PTR != pucK_aut)
        && (PS_TRUE == pstEapAkaDataInfo->enReauth))
    {
        PPPC_EAP_AKA_GetRand(&(aucRandom[0]));

        /* Attribute Field */
        pucEapAkaRspPayloadInfo = &(pstEAPMethodOutput->pucPktData[usEapLen]);

        /* 添加AT_IV */
        PS_MEM_SET(&stEapAkaAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTR_INFO_STRU));
        stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_IV;
        stEapAkaAttrInfo.usValue    = 0;
        stEapAkaAttrInfo.pData      = &(aucRandom[0]);
        stEapAkaAttrInfo.usDataLen  = PPPC_EAP_AKA_IV_LEN;
        usAttrLen = PPPC_EAP_AKA_MsgAddAttr(pucEapAkaRspPayloadInfo,
                    &stEapAkaAttrInfo, usEapLen, PPPC_EAP_MAX_PACKET_LEN);
        usEapLen += usAttrLen;

        /* 添加AT_ENCR_DATA */
        enExistCounterTooSmall = PS_FALSE;
        PPPC_EAP_AKA_GetEncrPayload(pstEAPMethodOutput, &(aucEncrPayload[0]),
            &usEncrLen, &(aucRandom[0]), enExistCounterTooSmall);
        PS_MEM_SET(&stEapAkaAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTR_INFO_STRU));
        stEapAkaAttrInfo.ucAttrId   = PPPC_EAP_AKA_AT_ENCR_DATA;
        stEapAkaAttrInfo.usValue    = 0;
        stEapAkaAttrInfo.pData      = &(aucEncrPayload[0]);
        stEapAkaAttrInfo.usDataLen  = usEncrLen;
        pucEapAkaRspPayloadInfo = &(pstEAPMethodOutput->pucPktData[usEapLen]);
        usAttrLen = PPPC_EAP_AKA_MsgAddAttr(pucEapAkaRspPayloadInfo,
                    &stEapAkaAttrInfo, usEapLen, PPPC_EAP_MAX_PACKET_LEN);
        usEapLen += usAttrLen;

        /* 调用PPPC接口更新EAP长度 */
        PPPC_EAP_UpdateLen(pstEAPMethodOutput->pucPktData, pstEAPMethodOutput->pusRespLen, usEapLen);
    }

    if (VOS_NULL_PTR != pucK_aut)
    {
        usAttrLen = PPPC_EAP_AKA_MsgAddAtMacAttr(pstEAPMethodOutput, VOS_NULL_PTR, 0);
        usEapLen  += usAttrLen;

        /* 调用PPPC接口更新EAP长度 */
        PPPC_EAP_UpdateLen(pstEAPMethodOutput->pucPktData, pstEAPMethodOutput->pusRespLen, usEapLen);
    }

    /* 给EAP发送Response报文 */
    PPPC_EAP_SendResponse(pstEAPMethodOutput->ulPppId);

    return;
}
/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_CheckIdentity
 功能描述  : EAP-AKA检查IDENTITY消息
 输入参数  :
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : VOS_OK; VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_CheckIdentity
(
    PPPC_EAP_METHOD_OUTPUT_STRU                 *pstEAPMethodOutput
)
{
    VOS_UINT16                              usIdError  = 0;
    VOS_UINT8                               ucNumIdReq = 0;
    PPPC_EAP_AKA_DATA_INFO_STRU            *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU                *pstEapAkaAttrInfo;
    PPPC_EAP_AKA_ID_REQ_TYPE_ENUM_UINT16    enEapAkaIdReqType;


    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo   = &g_stPppcEapAkaPktAttrInfo;
    ucNumIdReq          = pstEapAkaDataInfo->ucNumIdReq;
    enEapAkaIdReqType   = pstEapAkaAttrInfo->enEapAkaIdReqType;
    /*
       RFC4187 P48
       1)If the server has previously issued an EAP-Request/AKA-Identity
       message with the AT_PERMANENT_ID_REQ attribute, and if the server has
       received a response from the peer, then the server MUST NOT issue a
       new EAP-Request/AKA-Identity packet.
       2)If the server has previously issued an EAP-Request/AKA-Identity
       message with the AT_FULLAUTH_ID_REQ attribute, and if the server has
       received a response from the peer, then the server MUST NOT issue a
       new EAP-Request/AKA-Identity packet with the AT_ANY_ID_REQ or
       AT_FULLAUTH_ID_REQ attributes.
       3)If the server has previously issued an EAP-Request/AKA-Identity
       message with the AT_ANY_ID_REQ attribute, and if the server has
       received a response from the peer, then the server MUST NOT issue a
       new EAP-Request/AKA-Identity packet with the AT_ANY_ID_REQ.
    */
    switch (enEapAkaIdReqType)
    {
        case PPPC_EAP_AKA_ANY_ID_REQ:   /* 只应第一个出现 */
        {
            if (ucNumIdReq > 0)
            {
                usIdError++;
            }
            pstEapAkaDataInfo->ucNumIdReq++;

            break;
        }
        case PPPC_EAP_AKA_FULLAUTH_ID_REQ:    /* 在any后, permanent前出现 */
        {
            if (ucNumIdReq > 1)
            {
                usIdError++;
            }
            pstEapAkaDataInfo->ucNumIdReq++;

            break;
        }
        case PPPC_EAP_AKA_PERMANENT_ID_REQ:    /* 最后出现 */
        {
            if (ucNumIdReq > 2)
            {
                usIdError++;
            }
            pstEapAkaDataInfo->ucNumIdReq++;

            break;
        }
        default:
        {
            PPPC_WARNING_LOG("EAP-AKA: Id request type butt");

            PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);

            return VOS_ERR;
        }
    }

    if (0 != usIdError)
    {
        PPPC_WARNING_LOG("EAP-AKA: Too many ID requests used within one authentication");

        PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ProcessIdentity
 功能描述  : EAP-AKA处理PPPC_EAP_AKA_SUBTYPE_IDENTITY消息
 输入参数  : pstEAPMethodInput --EAP递给方法的包
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_ProcessIdentity
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
)
{
    VOS_UINT16                              usMsgLen     = 0;
    VOS_UINT32                              ulRslt       = 0;
    PPPC_EAP_AKA_ID_REQ_TYPE_ENUM_UINT16    enEapAkaIdReqType;
    PPPC_EAP_AKA_DATA_INFO_STRU            *pstEapAkaDataInfo;
    VOS_UINT8                              *pucEapAkaRespInfo;
    PPPC_EAP_AKA_ATTRS_STRU                *pstEapAkaAttrInfo;


    pstEapAkaAttrInfo   = &g_stPppcEapAkaPktAttrInfo;
    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;
    enEapAkaIdReqType   = pstEapAkaAttrInfo->enEapAkaIdReqType;

    ulRslt = PPPC_EAP_AKA_CheckIdentity(pstEAPMethodOutput);
    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* 回复Identity Response (PPPC_EAP_AKA_SUBTYPE_IDENTITY) */
    ulRslt = PPPC_EAP_AKA_ResponseIdentity(enEapAkaIdReqType, pstEAPMethodOutput);
    if (VOS_OK != ulRslt)
    {
        return;
    }

    pucEapAkaRespInfo = &(pstEAPMethodOutput->pucPktData[0]);

    /* 保存Identity Request 和 Identity Response消息 */
    if (pstEapAkaDataInfo->usPrevId != pstEAPMethodInput->ucEAPID)
    {
        /* 保存Identity Request消息 */
        usMsgLen = pstEAPMethodInput->usEAPLen;
        PPPC_EAP_AKA_AddIdMsg(pstEAPMethodInput->pucPktData, usMsgLen);

        /* 保存Identity Response消息 */
        usMsgLen = *(pstEAPMethodOutput->pusRespLen);
        PPPC_EAP_AKA_AddIdMsg(pucEapAkaRespInfo, usMsgLen);
        pstEapAkaDataInfo->usPrevId = (VOS_UINT16)pstEAPMethodInput->ucEAPID;
    }

    /* 给EAP发送Response报文 */
    PPPC_EAP_SendResponse(pstEAPMethodOutput->ulPppId);

    return;
}
/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_CheckCheckcodeAttr
 功能描述  : 检查CheckCode属性
 输入参数  :
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : VOS_OK; VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_CheckCheckcodeAttr
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput
)
{
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    VOS_UINT32                          ulAttrExistCtrlFlag;
    VOS_UINT32                          ulRes;


    pstEapAkaAttrInfo   = &g_stPppcEapAkaPktAttrInfo;
    ulAttrExistCtrlFlag = pstEapAkaAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_CHECKCODE_BIT))
    {
        ulRes = PPPC_EAP_AKA_VerifyCheckCode();
        if (VOS_OK != ulRes)
        {
            PPPC_WARNING_LOG("EAP-AKA: Invalid AT_CHECKCODE in the "
               "message");

            /* 发送ClientError包 */
            PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);

            return VOS_ERR;
        }
    }

    return VOS_OK;
}
/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_CheckKdfInputAttr
 功能描述  : 检查AT_KDF_INPUT属性
 输入参数  :
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : VOS_OK; VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_CheckKdfInputAttr
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    VOS_UINT32                          ulAttrExistCtrlFlag;


    pstEapAkaAttrInfo   = &g_stPppcEapAkaPktAttrInfo;
    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;
    ulAttrExistCtrlFlag = pstEapAkaAttrInfo->ulAttrExistCtrlFlag;

    if ((PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_KDF_INPUT_BIT))
        || (0 == pstEapAkaAttrInfo->usKdfInputLen))
    {
        PPPC_WARNING_LOG("EAP-AKA': Challenge message"
                  "did not include non-empty AT_KDF_INPUT");
        PPPC_EAP_AKA_AuthenticationReject(pstEAPMethodOutput);
        return VOS_ERR;
    }

    /* 保存AT_KDF_INPUT属性 */
    PS_MEM_CPY(&(pstEapAkaDataInfo->stEapAkaAuthPara.aucNetworkName[0]),
                &(pstEapAkaAttrInfo->aucKdfInput[0]), pstEapAkaAttrInfo->usKdfInputLen);
    pstEapAkaDataInfo->stEapAkaAuthPara.usNetworkNameLen =  pstEapAkaAttrInfo->usKdfInputLen;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_CheckKdfandKdfInputAttr
 功能描述  : 检查并处理AT_KDF和AT_KDF_INPUT属性
 输入参数  : pstEAPMethodInput --EAP递给方法的包
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : VOS_OK; VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_CheckKdfandKdfInputAttr
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    VOS_UINT32                          ulRes;
    PPPC_EAP_METHOD_TYPE_ENUM_UINT16    enEapMethod;


    pstEapAkaAttrInfo   = &g_stPppcEapAkaPktAttrInfo;
    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;

    enEapMethod         = pstEapAkaDataInfo->enEapMethod;

    /* 如果为EAP-AKA'的话，必须要检查AT_KDF_INPUT和AT_KDF属性*/
    if (PPPC_EAP_METHOD_TYPE_AKA_PRIME == enEapMethod)
    {
        /* 检查KDF_INPUT属性是否合法 */
        ulRes = PPPC_EAP_AKA_CheckKdfInputAttr(pstEAPMethodOutput);
        if (VOS_OK != ulRes)
        {
            return VOS_ERR;
        }

        /* 检查KDF属性是否合法 */
        ulRes = PPPC_EAP_AKA_PRIME_KdfValid();
        if (VOS_OK != ulRes)
        {
            PPPC_EAP_AKA_AuthenticationReject(pstEAPMethodOutput);
            return VOS_ERR;
        }

        if (PPPC_EAP_AKA_PRIME_KDF != pstEapAkaAttrInfo->ausKdf[0])
        {
            PPPC_EAP_AKA_PRIME_KdfNeg(pstEAPMethodOutput, pstEAPMethodInput);
            return VOS_ERR;
        }

        pstEapAkaDataInfo->stEapAkaAuthPara.usKdf = PPPC_EAP_AKA_PRIME_KDF;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_CheckBiddingAttr
 功能描述  : 检查AT_BIDDING属性
 输入参数  : 无
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : VOS_OK; VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_CheckBiddingAttr
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    PPPC_EAP_METHOD_TYPE_ENUM_UINT16    enEapMethod;
    const VOS_UINT8                     ucDbitPos = 15;
    VOS_UINT16                          usBiddingDbit = 0;


    pstEapAkaAttrInfo   = &g_stPppcEapAkaPktAttrInfo;
    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;

    enEapMethod         = pstEapAkaDataInfo->enEapMethod;

    /* 检查AT_BIDING属性 */
    if ((PPPC_EAP_METHOD_TYPE_AKA == enEapMethod)
        && (pstEapAkaAttrInfo->usBidding))
    {
        usBiddingDbit = TTF_GET_A_BIT(pstEapAkaAttrInfo->usBidding, ucDbitPos);
        if (PPPC_BIT_MASK_ON == usBiddingDbit)
        {
            PPPC_EAP_AKA_AuthenticationReject(pstEAPMethodOutput);
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_InitForFullAuth
 功能描述  : 执行全鉴权流程时初始化实体信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_InitForFullAuth(VOS_VOID)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo = VOS_NULL_PTR;
    PPPC_EAP_AKA_AUTH_PARA_STRU        *pstEapAkaAuthPara = VOS_NULL_PTR;
    VOS_UINT16                          usKdf;

    /* 全鉴权开始不能清除Id_Msg */
    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaAuthPara = &(pstEapAkaDataInfo->stEapAkaAuthPara);

    usKdf = pstEapAkaAuthPara->usKdf;
    PS_MEM_SET(pstEapAkaAuthPara, 0, sizeof(PPPC_EAP_AKA_AUTH_PARA_STRU));
    pstEapAkaDataInfo->enEapAkaState                = PPPC_EAP_AKA_STATE_CONTINUE;
    pstEapAkaDataInfo->enReauth                     = PS_FALSE;
    pstEapAkaDataInfo->enResultInd                  = PS_FALSE;

    pstEapAkaAuthPara->usKdf                        = usKdf;
    PS_MEM_SET(&(pstEapAkaDataInfo->aucPppcInputMsg[0]),
               0x0, PPPC_EAP_MAX_PACKET_LEN);
    pstEapAkaDataInfo->usInputMsgLen                = 0;

    PPPC_EAP_AKA_ClearKeys(PS_FALSE);
    PPPC_EAP_AKA_ClearIdentity(PPPC_EAP_AKA_CLEAR_REAUTH_ID);

    return;
}


/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ProcessChallenge
 功能描述  : EAP-AKA处理鉴权消息
 输入参数  : pstEAPMethodInput --EAP递给方法的包
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_ProcessChallenge
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    VOS_UINT8                          *pucRand;
    VOS_UINT8                          *pucAutn;
    VOS_UINT32                          ulRes;
    VOS_UINT32                          ulAttrExistCtrlFlag;


    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo   = &g_stPppcEapAkaPktAttrInfo;
    ulAttrExistCtrlFlag = pstEapAkaAttrInfo->ulAttrExistCtrlFlag;

    /* 初始化实体信息 */
    PPPC_EAP_AKA_InitForFullAuth();

    /* 检查CHECKCODE属性 */
    ulRes = PPPC_EAP_AKA_CheckCheckcodeAttr(pstEAPMethodOutput);
    if (VOS_OK != ulRes)
    {
        return;
    }

    /* 检查并处理KDF 和KDF_INPUT属性 */
    ulRes = PPPC_EAP_AKA_CheckKdfandKdfInputAttr(pstEAPMethodOutput, pstEAPMethodInput);
    if (VOS_OK != ulRes)
    {
        return;
    }

    /* 检查AT_BIDING属性 */
    ulRes = PPPC_EAP_AKA_CheckBiddingAttr(pstEAPMethodOutput);
    if (VOS_OK != ulRes)
    {
        return;
    }

    /* 检查必带属性 */
    pstEapAkaDataInfo->enReauth = PS_FALSE;
    if ((PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_MAC_BIT))
        || (PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_RAND_BIT))
        || (PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_AUTN_BIT)))
    {
        PPPC_WARNING_LOG("Challenge message"
               "did not include AT_MAC, AT_RAND, AT_AUTN");
        PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);

        return;
    }

    /* 检查AMF */
    ulRes = PPPC_EAP_AKA_CheckAmf(pstEAPMethodOutput, &(pstEapAkaAttrInfo->aucAutn[0]));
    if (VOS_OK != ulRes)
    {
        return;
    }

    /* 保存RAND and AUTN参数 */
    pucRand = &(pstEapAkaDataInfo->stEapAkaAuthPara.aucRand[0]);
    pucAutn = &(pstEapAkaDataInfo->stEapAkaAuthPara.aucAutn[0]);
    PS_MEM_CPY(pucRand, &(pstEapAkaAttrInfo->aucRand[0]),
                    PPPC_EAP_AKA_RAND_LEN);

    PS_MEM_CPY(pucAutn, &(pstEapAkaAttrInfo->aucAutn[0]),
                    PPPC_EAP_AKA_AUTN_LEN);

    /* 保存EAP递交过来的报文信息 */
    PS_MEM_CPY(&(pstEapAkaDataInfo->aucPppcInputMsg[0]),
            pstEAPMethodInput->pucPktData, pstEAPMethodInput->usEAPLen);

    pstEapAkaDataInfo->usInputMsgLen = pstEAPMethodInput->usEAPLen;
    pstEapAkaDataInfo->usPrevId      = pstEAPMethodInput->ucEAPID;

    /* 保存pstPppcEapInfo地址*/
    PS_MEM_CPY(&g_stEAPAkaMethodOutput, pstEAPMethodOutput, sizeof(PPPC_EAP_METHOD_OUTPUT_STRU));

    /* 给卡发送鉴权请求, 等待卡的鉴权结果 */
    PPPC_UIM_SendEapAuthReq(pucRand, pucAutn, pstEAPMethodInput->ucEAPID);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ProcessNotificationReauth
 功能描述  : EAP-AKA处理鉴权消息
 输入参数  : pstEAPMethodInput --EAP递给方法的包
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : VOS_OK; VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_ProcessNotificationReauth
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    VOS_UINT32                          ulRes;
    VOS_UINT32                          ulAttrExistCtrlFlag;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo = &g_stPppcEapAkaPktAttrInfo;
    ulAttrExistCtrlFlag = pstEapAkaAttrInfo->ulAttrExistCtrlFlag;

    if ((PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_ENCR_BIT))
        || (PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_IV_BIT)))
    {
        PPPC_WARNING_LOG("EAP-AKA: Notification message after "
               "reauth did not include encrypted data");
        return VOS_ERR;
    }

    ulRes  = PPPC_EAP_AKA_ParseEncr();
    if (VOS_OK != ulRes)
    {
        PPPC_WARNING_LOG("EAP-AKA: Failed to parse encrypted "
               "data from notification message");
        return VOS_ERR;
    }

    if (pstEapAkaAttrInfo->usCounter != pstEapAkaDataInfo->stEapAkaAuthPara.usCounter)
    {
        PPPC_WARNING_LOG("EAP-AKA: Counter in notification"
               "message does not match with counter in reauth"
               "message");
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ProcessNotificationAuth
 功能描述  : EAP-AKA处理鉴权消息
 输入参数  : pstEAPMethodInput --EAP递给方法的包
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : VOS_OK, VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_ProcessNotificationAuth
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    VOS_UINT32                          ulRes;
    VOS_UINT32                          ulAttrExistCtrlFlag;

    /* The AT_MAC attribute MUST be included if the P bit of the
       AT_NOTIFICATION code is set to zero, and MUST NOT be included if the
       P bit is set to one. */

    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo = &g_stPppcEapAkaPktAttrInfo;
    ulAttrExistCtrlFlag = pstEapAkaAttrInfo->ulAttrExistCtrlFlag;

    if (PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_MAC_BIT))
    {
        PPPC_WARNING_LOG("no AT_MAC in"
               "Notification message");
        return VOS_ERR;
    }

    ulRes = PPPC_EAP_AKA_VerifyMac(pstEAPMethodInput->pucPktData,
                    pstEAPMethodInput->usEAPLen, VOS_NULL_PTR, 0);
    if (VOS_OK != ulRes)
    {
        PPPC_WARNING_LOG("Invalid in"
               "Notification message");
        return VOS_ERR;
    }

    if (PS_TRUE == pstEapAkaDataInfo->enReauth)
    {
        ulRes = PPPC_EAP_AKA_ProcessNotificationReauth(pstEAPMethodOutput);
        if (VOS_OK != ulRes)
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ProcessNotification
 功能描述  : 处理Notification消息
 输入参数  : pstEAPMethodInput --EAP递给方法的包
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_ProcessNotification
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    VOS_UINT32                          ulRes;
    VOS_UINT8                           ucCount = 1;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo = &g_stPppcEapAkaPktAttrInfo;

    if (ucCount < pstEapAkaDataInfo->ucNumNotification)
    {
        PPPC_WARNING_LOG("too many notification");

        /* 发送ClientError包 */
        PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);
    }
    pstEapAkaDataInfo->ucNumNotification++;

    if (PPPC_EAP_AKA_NOTIFICATION_INVALID_VALUE == pstEapAkaAttrInfo->usNotification)
    {
        PPPC_WARNING_LOG("no AT_NOTIFICATION in"
               "Notification message");

        /* 发送ClientError包 */
        PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);
    }

    /*
        The second most significant bit of the notification code is called
    the Phase bit (P bit). It specifies at which phase of the EAP-AKA
    exchange the notification can be used. If the P bit is set to zero,
    the notification can only be used after a successful EAP/AKAChallenge
    round in full authentication or a successful EAP/AKAReauthentication
    round in re-authentication. A re-authentication round is considered
    successful only if the peer has successfully verified AT_MAC and AT_COUNTER
    attributes, and does not include the AT_COUNTER_TOO_SMALL attribute in
    EAP-Response/AKA-Reauthentication.
    If the P bit is set to one, the notification can only by used before
    the EAP/AKA-Challenge round in full authentication or before the
    EAP/AKA-Reauthentication round in reauthentication. These
    notifications can only be used to indicate various failure cases. In
    other words, if the P bit is set to one, then the S bit MUST be set
    to zero.
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |AT_NOTIFICATION| Length = 1  |S|P| Notification Code         |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */

    if (0 == ((pstEapAkaAttrInfo->usNotification) & PPPC_EAP_AKA_NOTIFICATION_P_IS_1))
    {
        ulRes = PPPC_EAP_AKA_ProcessNotificationAuth(pstEAPMethodOutput, pstEAPMethodInput);
        if (VOS_OK != ulRes)
        {
            PPPC_WARNING_LOG("Receive Notification Message After Auths");

            /* 发送ClientError包 */
            PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);
            return;
        }
    }

    /* 更新状态 */
    if (PPPC_EAP_AKA_SUCCESS > pstEapAkaAttrInfo->usNotification)
    {
        PPPC_EAP_AKA_UpdateState(pstEAPMethodOutput->ulPppId,
                        PPPC_EAP_AKA_STATE_FAILURE);
    }
    else if ((PPPC_EAP_AKA_SUCCESS == pstEapAkaAttrInfo->usNotification)
             && (PPPC_EAP_AKA_STATE_RESULT_SUCCESS == pstEapAkaDataInfo->enEapAkaState))
    {
        PPPC_EAP_AKA_UpdateState(pstEAPMethodOutput->ulPppId,
                        PPPC_EAP_AKA_STATE_SUCCESS);
    }
    else
    {
        PPPC_WARNING_LOG("State should not be changed");
    }

    PPPC_EAP_AKA_ResponseNotification(pstEAPMethodOutput);

    return;
}
/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ProcessResultInd
 功能描述  : 收到ResultInd属性的状态处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_ProcessResultInd
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;


    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo   = &g_stPppcEapAkaPktAttrInfo;

    /* 检查是否存在AT_RESULT_IND属性 */
    if (PS_TRUE == pstEapAkaAttrInfo->enResultInd)
    {
        pstEapAkaDataInfo->enResultInd = PS_TRUE;
    }

    /* 更新状态 */
    if (PPPC_EAP_AKA_STATE_FAILURE != pstEapAkaDataInfo->enEapAkaState)
    {
        if (PS_TRUE == pstEapAkaDataInfo->enResultInd)
        {
            PPPC_EAP_AKA_UpdateState(pstEAPMethodOutput->ulPppId,
                        PPPC_EAP_AKA_STATE_RESULT_SUCCESS);
        }
        else
        {
            PPPC_EAP_AKA_UpdateState(pstEAPMethodOutput->ulPppId,
                        PPPC_EAP_AKA_STATE_SUCCESS);
        }
    }

    return;
}
/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ProcessCounterTooSmall
 功能描述  : Counter太小的处理
 输入参数  : 无
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_EAP_AKA_ProcessCounterTooSmall
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    PPPC_EAP_AKA_AUTH_PARA_STRU        *pstEapAkaAuthPara;
    PPPC_EAP_AKA_ID_INFO_STRU          *pstEapAkaIdInfo;
    PS_BOOL_ENUM_UINT8                  enExistCounterTooSmall = PS_FALSE;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo = &g_stPppcEapAkaPktAttrInfo;
    pstEapAkaIdInfo   = &(pstEapAkaDataInfo->stEapAkaIdInfo);
    pstEapAkaAuthPara = &(pstEapAkaDataInfo->stEapAkaAuthPara);


    if (pstEapAkaAttrInfo->usCounter <= pstEapAkaAuthPara->usCounter)
    {
        /* Reply using Re-auth w/ AT_COUNTER_TOO_SMALL. The current
         * reauth_id must not be used to start a new reauthentication.
         * However, since it was used in the last EAP-Response-Identity
         * packet, it has to saved for the following fullauth to be
         * used in MK derivation.
        */
        PS_MEM_CPY(&(pstEapAkaIdInfo->aucLastEapIdentity[0]),
                    &(pstEapAkaIdInfo->aucReauthId[0]),
                     pstEapAkaIdInfo->usReauthIdLen);
        pstEapAkaIdInfo->usLastEapIdentityLen =  pstEapAkaIdInfo->usReauthIdLen;

        PS_MEM_SET(&(pstEapAkaIdInfo->aucReauthId[0]), 0, pstEapAkaIdInfo->usReauthIdLen);
        pstEapAkaIdInfo->usReauthIdLen = 0;
        pstEapAkaDataInfo->usCounterTooSmall = pstEapAkaAttrInfo->usCounter;
        enExistCounterTooSmall = PS_TRUE;
        PPPC_EAP_AKA_ResponseReauth(pstEAPMethodOutput, enExistCounterTooSmall);

        return PS_TRUE;
    }

    return PS_FALSE;
}
/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_CalReAuthKeys
 功能描述  : 计算K
 输入参数  : pstResult --卡计算的结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月14日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_CalReAuthKeys(VOS_VOID)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ID_INFO_STRU          *pstEapAkaIdInfo;
    PPPC_EAP_AKA_AUTH_PARA_STRU        *pstEapAkaAuthPara;
    PPPC_EAP_AKA_KEY_DATA_STRU         *pstEapAkaKey;
    VOS_UINT32                          ulRst;


    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;
    pstEapAkaIdInfo     = &(pstEapAkaDataInfo->stEapAkaIdInfo);
    pstEapAkaAuthPara   = &(pstEapAkaDataInfo->stEapAkaAuthPara);
    pstEapAkaKey        = &(pstEapAkaDataInfo->stEapAkaKey);


    if (PPPC_EAP_METHOD_TYPE_AKA_PRIME == pstEapAkaDataInfo->enEapMethod)
    {
        ulRst = PPPC_EAP_AKA_PRIME_DeriveKeys_ReAuth(&(pstEapAkaIdInfo->aucReauthId[0]),
            pstEapAkaIdInfo->usReauthIdLen, pstEapAkaAuthPara, pstEapAkaKey);
    }
    else
    {
        ulRst = PPPC_EAP_AKA_DeriveKeys_ReAuth(&(pstEapAkaIdInfo->aucReauthId[0]),
            pstEapAkaIdInfo->usReauthIdLen, pstEapAkaAuthPara, pstEapAkaKey);
    }

    if (VOS_OK != ulRst)
    {
        PPPC_WARNING_LOG("DeriveKey is fail");
    }

    /* 勾取可维可测信息 */
    PPPC_EAP_AKA_MntnTraceInfo(pstEapAkaAuthPara, pstEapAkaKey);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ProcessChallenge
 功能描述  : EAP-AKA处理鉴权消息
 输入参数  : pstEAPMethodInput --EAP递给方法的包
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_ProcessReauthentication
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    PPPC_EAP_AKA_AUTH_PARA_STRU        *pstEapAkaAuthPara;
    VOS_UINT32                          ulRes;
    VOS_UINT32                          ulAttrExistCtrlFlag = 0;
    PS_BOOL_ENUM_UINT8                  enExistCounterTooSmall = PS_FALSE;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo = &g_stPppcEapAkaPktAttrInfo;
    pstEapAkaAuthPara = &(pstEapAkaDataInfo->stEapAkaAuthPara);

    /* 初始化实体信息 */
    PPPC_EAP_AKA_InitForReAuth();

    /* 检查CHECKCODE属性 */
    ulRes = PPPC_EAP_AKA_CheckCheckcodeAttr(pstEAPMethodOutput);
    if (VOS_OK != ulRes)
    {
        return;
    }

    /* 检查实体里面是否有ReauthId */
    if (0 == pstEapAkaDataInfo->stEapAkaIdInfo.usReauthIdLen)
    {
        PPPC_WARNING_LOG("EAP-AKA: Server is trying"
               "reauthentication, but no reauth_id available");
        /* 发送ClientError包 */
        PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);

        return;
    }

    /* 设置重鉴权标记 */
    pstEapAkaDataInfo->enReauth = PS_TRUE;

    /* 检查AT_MAC */
    ulRes = PPPC_EAP_AKA_VerifyMac(pstEAPMethodInput->pucPktData,
                    pstEAPMethodInput->usEAPLen, VOS_NULL_PTR, 0);
    if (VOS_OK != ulRes)
    {
        PPPC_WARNING_LOG("used invalid AT_MAC");
        PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);
        return;
    }

    ulAttrExistCtrlFlag = pstEapAkaAttrInfo->ulAttrExistCtrlFlag;

    /* 检查快速鉴权中必带属性AT_ENCR and AT_IV */
    if ((PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_ENCR_BIT))
        || (PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_IV_BIT)))
    {
        PPPC_WARNING_LOG("AT_ENCR and AT_IV");
        PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);
        return;
    }

    /* 解析AT_ENCR属性 */
    ulRes = PPPC_EAP_AKA_ParseEncr();
    if (VOS_OK != ulRes)
    {
        PPPC_WARNING_LOG("decryption is fail");
        PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);
        return;
    }

    /* 检查AT_NONCE_S and AT_COUNTER属性 */
    ulAttrExistCtrlFlag = pstEapAkaAttrInfo->ulAttrExistCtrlFlag;
    if ((PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_NONCE_S_BIT))
        || (PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_COUNTER_BIT)))
    {
        PPPC_WARNING_LOG("enExistNonce_s AND usCounter");
        PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);
        return;
    }

    /* Counter Too Small 处理 */
    enExistCounterTooSmall = PPPC_EAP_AKA_ProcessCounterTooSmall(pstEAPMethodOutput);
    if (PS_TRUE == enExistCounterTooSmall)
    {
        return;
    }

    /* 保存Counter值 */
    pstEapAkaAuthPara->usCounter = pstEapAkaAttrInfo->usCounter;

    PS_MEM_CPY(&(pstEapAkaAuthPara->aucNonce_s[0]),
                &(pstEapAkaAttrInfo->aucNonce_s[0]),
                PPPC_EAP_AKA_NONCE_S_LEN);

    /* 计算快速鉴权Key */
    PPPC_EAP_AKA_CalReAuthKeys();

    PPPC_EAP_AKA_ClearIdentity(PPPC_EAP_AKA_CLEAR_REAUTH_ID | PPPC_EAP_AKA_CLEAR_EAP_ID);
    PPPC_EAP_AKA_SaveIds();

    /* 收到ResultInd属性的状态处理 */
    PPPC_EAP_AKA_ProcessResultInd(pstEAPMethodOutput);

    pstEapAkaDataInfo->ucNumIdReq = 0;
    pstEapAkaDataInfo->ucNumNotification = 0;

    if (pstEapAkaAuthPara->usCounter > PPPC_EAP_AKA_MAX_FAST_REAUTHS)
    {
        PPPC_WARNING_LOG("EAP-AKA: Maximum number of"
               "fast reauths performed - force fullauth");
        PPPC_EAP_AKA_ClearIdentity(PPPC_EAP_AKA_CLEAR_REAUTH_ID | PPPC_EAP_AKA_CLEAR_EAP_ID);
    }

    enExistCounterTooSmall = PS_FALSE;
    PPPC_EAP_AKA_ResponseReauth(pstEAPMethodOutput, enExistCounterTooSmall);

    return;
}
/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_InitAttrInfo
 功能描述  : 初始化之前解出来的属性信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月13日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_InitAttrInfo(VOS_VOID)
{
    PPPC_EAP_AKA_ATTRS_STRU             *pstPppcEapAkaPktAttrInfo;


    pstPppcEapAkaPktAttrInfo = &g_stPppcEapAkaPktAttrInfo;
    PS_MEM_SET(&g_stPppcEapAkaPktAttrInfo, 0, sizeof(PPPC_EAP_AKA_ATTRS_STRU));
    pstPppcEapAkaPktAttrInfo->enEapAkaIdReqType = PPPC_EAP_AKA_ID_REQ_BUTT;
    pstPppcEapAkaPktAttrInfo->enResultInd = PS_FALSE;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_PreProcessPkt
 功能描述  : 预处理EAP报文
 输入参数  : pstEAPMethodInput --EAP递给方法的包
 输出参数  :
 返 回 值  : PS_TRUE --收到的包是鉴权消息
             PS_FALSE --收到的包不是鉴权消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_EAP_AKA_PreProcessPkt
(
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
)
{
     VOS_UINT8                           ucSubType;
     PS_BOOL_ENUM_UINT8                  enResult;
     /* 5Bytes: Code+Identifier+Length+Type */
     const VOS_UINT8                     ucConst5Value = 5;


     ucSubType = *(pstEAPMethodInput->pucPktData + ucConst5Value);

     switch (ucSubType)
     {
         case PPPC_EAP_AKA_SUBTYPE_IDENTITY:
         case PPPC_EAP_AKA_SUBTYPE_NOTIFICATION:
             enResult   = PS_FALSE;
             break;

         case PPPC_EAP_AKA_SUBTYPE_CHALLENGE:
         case PPPC_EAP_AKA_SUBTYPE_REAUTHENTICATION:
             enResult   = PS_TRUE;
             break;

         default:
             enResult   = PS_FALSE;
             PPPC_WARNING_LOG1("Invalid subtype!", ucSubType);
             break;
     }

     return enResult;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ProcessPkt
 功能描述  : 处理EAP报文
 输入参数  : pstEAPMethodInput --EAP递给方法的包
 输出参数  : pstEAPMethodOutput    --Response数据要填写的位置
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_ProcessPkt
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    PPPC_EAP_METHOD_INPUT_STRU         *pstEAPMethodInput
)
{
    VOS_UINT8                          *pucAkaAttrStartPos;
    VOS_UINT8                          *pucAkaAttrEndPos;
    VOS_UINT8                           ucSubType;
    VOS_UINT32                          ulResult;
    PS_BOOL_ENUM_UINT8                  enEncr        = PS_FALSE;
    /* 5Bytes: Code+Identifier+Length+Type */
    const VOS_UINT8                     ucConst5Value = 5;
    /* 8Bytes: Code+Identifier+Length+Type+Subtype+Reserved */
    const VOS_UINT8                     ucConst8Value = 8;

   /*
      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      | Code        |    Identifier | Length                        |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      | Type        | Subtype       | Reserved                      |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   */

    pucAkaAttrStartPos = pstEAPMethodInput->pucPktData + ucConst8Value;
    pucAkaAttrEndPos   = pstEAPMethodInput->pucPktData + pstEAPMethodInput->usEAPLen;

    /* 清除属性的全局变量信息 */
    PPPC_EAP_AKA_InitAttrInfo();

    /* 解EAP-AKA属性 */
    ulResult = PPPC_EAP_AKA_ParseAttr(pucAkaAttrStartPos, pucAkaAttrEndPos, enEncr);

    if (VOS_OK != ulResult)
    {
        PPPC_WARNING_LOG("parse Attr is fail ");
        PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);
        return;
    }

    ucSubType = *(pstEAPMethodInput->pucPktData + ucConst5Value);

    switch (ucSubType)
    {
        case PPPC_EAP_AKA_SUBTYPE_IDENTITY:
            PPPC_EAP_AKA_ProcessIdentity(pstEAPMethodOutput, pstEAPMethodInput);
            break;
        case PPPC_EAP_AKA_SUBTYPE_CHALLENGE:
            PPPC_EAP_AKA_ProcessChallenge(pstEAPMethodOutput, pstEAPMethodInput);
            break;
        case PPPC_EAP_AKA_SUBTYPE_NOTIFICATION:
            PPPC_EAP_AKA_ProcessNotification(pstEAPMethodOutput, pstEAPMethodInput);
            break;
        case PPPC_EAP_AKA_SUBTYPE_REAUTHENTICATION:
            PPPC_EAP_AKA_ProcessReauthentication(pstEAPMethodOutput, pstEAPMethodInput);
            break;
        default:
            PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);
            break;
    }

    return;
}
/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_AddAutsAttr
 功能描述  : 添加AUTN属性
 输入参数  : ucAttrId   --属性Id
 输出参数  : pMsg       --属性填写的地址
             pData      --AT_AUTS的value域
             usDataLen  --Value域长度
 返 回 值  : AT_AUTS属性的长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月14日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 PPPC_EAP_AKA_AddAutsAttr
(
    VOS_UINT8                          *pucAttrStartPos,
    VOS_UINT8                           ucAttrId,
    const VOS_UINT8                    *pData,
    VOS_UINT16                          usDataLen
)
{
    VOS_UINT16                          usAttrLen       = 0;
    const VOS_UINT8                     ucAutsHeaderLen = 2;
    const VOS_UINT8                     ucConstValue    = 4;
    const VOS_UINT8                     usAutsLen       = 16;


    if (VOS_NULL_PTR == pucAttrStartPos)
    {
        PPPC_WARNING_LOG("parameter is NULL.");
        return usAttrLen;
    }

    /* 整个属性的长度为4BYTES的倍数 */
    usAttrLen = ucAutsHeaderLen + usDataLen;
    if (usAutsLen != usAttrLen)
    {
        usAttrLen = 0;
        PPPC_WARNING_LOG("usAttrLen is error.");
        return usAttrLen;
    }

    /* Attr Id */
    *pucAttrStartPos     = ucAttrId;
    pucAttrStartPos++;

    /* Attr LEN */
    *pucAttrStartPos     = usAutsLen/ucConstValue;
    pucAttrStartPos++;

    /* CPY Value域 */
    if (VOS_NULL_PTR != pData)
    {
        PS_MEM_CPY(pucAttrStartPos, pData, usDataLen);
    }

    return usAttrLen;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_SynchronizationFailure
 功能描述  : 同步失败
 输入参数  : pstResult --卡计算的结果
 输出参数  : pstEAPMethodOutput
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月14日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_SynchronizationFailure
(
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput,
    PPPC_EAP_AUTH_RESULT_STRU          *pstResult
)
{

    VOS_UINT8                           *pucEapAkaRspPayloadInfo;
    VOS_UINT16                           usAttrLen = 0;
    VOS_UINT16                           usEapLen;
    VOS_UINT8                            ucEapAkaSubType;

    /*
       RF4187 P50
        The peer sends the EAP-Response/AKA-Synchronization-Failure, when the
        sequence number in the AUTN parameter is incorrect.
        The peer MUST include the AT_AUTS attribute. Future versions of the
        protocol MAY specify other additional attributes for this message.
    */
    /* 填充Subtype和Reserved域 */
    ucEapAkaSubType = PPPC_EAP_AKA_SUBTYPE_SYNCHRONIZATION_FAILURE;
    PPPC_EAP_AKA_RespMsgInit(pstEAPMethodOutput, ucEapAkaSubType);

    /*
       0             1               2                 3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
       | AT_AUTS     | Length = 4    |                                 |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                               |
       |                                                               |
       | AUTS                                                          |
       |                                                               |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       The value field of this attribute contains the AKA AUTS parameter,
       112 bits (14 bytes).
    */
    /* Add AT_AUTS Attribute */
    usEapLen = *(pstEAPMethodOutput->pusRespLen);
    pucEapAkaRspPayloadInfo = &(pstEAPMethodOutput->pucPktData[usEapLen]);

    usAttrLen = PPPC_EAP_AKA_AddAutsAttr(pucEapAkaRspPayloadInfo,
                    PPPC_EAP_AKA_AT_AUTS, &(pstResult->aucAuts[0]),
                    USIMM_AUTH_AUTS_LEN);

    /* 调用PPPC接口更新EAP长度 */
    usEapLen = *(pstEAPMethodOutput->pusRespLen) + usAttrLen;

    PPPC_EAP_UpdateLen(pstEAPMethodOutput->pucPktData, pstEAPMethodOutput->pusRespLen, usEapLen);

    /* 给EAP发送Response报文 */
    PPPC_EAP_SendResponse(pstEAPMethodOutput->ulPppId);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_CheckAuthRes
 功能描述  : 检查卡的鉴权结果
 输入参数  : pstResult --卡计算的结果
 输出参数  :
 返 回 值  : VOS_OK; VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_AKA_CheckAuthRes
(
    PPPC_EAP_AUTH_RESULT_STRU          *pstResult
)
{
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput;
    PPPC_USIMM_AUTH_RESULT_ENUM_UINT8   enResult;


    pstEAPMethodOutput  = &g_stEAPAkaMethodOutput;

    enResult = pstResult->enResult;

    if (PPPC_USIMM_AUTH_SUCCESS == enResult)
    {
        return VOS_OK;
    }
    else if (PPPC_USIMM_AUTH_MAC_FAILURE == enResult)
    {
        PPPC_WARNING_LOG("EAP-AKA: UMTS authentication "
                   "failed (AUTN)");
        PPPC_EAP_AKA_AuthenticationReject(pstEAPMethodOutput);

        return VOS_ERR;
    }
    else if (PPPC_USIMM_AUTH_SYNC_FAILURE == enResult)
    {
        PPPC_WARNING_LOG("EAP-AKA: UMTS authentication "
                   "failed (AUTN seq# -> AUTS)");
        PPPC_EAP_AKA_SynchronizationFailure(pstEAPMethodOutput, pstResult);

        return VOS_ERR;
    }
    else
    {
        PPPC_WARNING_LOG("EAP-AKA: UMTS authentication failed");
        PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);
        return VOS_ERR;
    }
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_CalFullAuthKeys
 功能描述  : 计算K
 输入参数  : pstResult --卡计算的结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月14日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_CalFullAuthKeys(VOS_VOID)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ID_INFO_STRU          *pstEapAkaIdInfo;
    PPPC_EAP_AKA_AUTH_PARA_STRU        *pstEapAkaAuthPara;
    PPPC_EAP_AKA_KEY_DATA_STRU         *pstEapAkaKey;
    VOS_UINT8                           aucIdentity[PPPC_EAP_AKA_NETNAME_MAX_LEN];
    VOS_UINT16                          usIdentityLen;
    VOS_UINT32                          ulRslt;


    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;
    pstEapAkaIdInfo     = &(pstEapAkaDataInfo->stEapAkaIdInfo);
    pstEapAkaAuthPara   = &(pstEapAkaDataInfo->stEapAkaAuthPara);
    pstEapAkaKey        = &(pstEapAkaDataInfo->stEapAkaKey);

    PS_MEM_SET(&(aucIdentity[0]), 0, PPPC_EAP_AKA_NETNAME_MAX_LEN);
    if (0 != pstEapAkaIdInfo->usLastEapIdentityLen)
    {
        PS_MEM_CPY(&(aucIdentity[0]), &(pstEapAkaIdInfo->aucLastEapIdentity[0]),
                    pstEapAkaIdInfo->usLastEapIdentityLen);
        usIdentityLen = pstEapAkaIdInfo->usLastEapIdentityLen;
    }
    else if (0 != pstEapAkaIdInfo->usPseudonymLen)
    {
        PS_MEM_CPY(&(aucIdentity[0]), &(pstEapAkaIdInfo->aucPseudonym[0]),
                    pstEapAkaIdInfo->usPseudonymLen);
        usIdentityLen = pstEapAkaIdInfo->usPseudonymLen;
    }
    else if (0 != pstEapAkaIdInfo->usPermenentIdLen)
    {
        PS_MEM_CPY(&(aucIdentity[0]), &(pstEapAkaIdInfo->aucPermenentId[0]),
            pstEapAkaIdInfo->usPermenentIdLen);
        usIdentityLen = pstEapAkaIdInfo->usPermenentIdLen;
    }
    else
    {
        ulRslt = PPPC_EAP_AKA_GetPermanentNAI(&(aucIdentity[0]),
               &usIdentityLen, pstEapAkaDataInfo->enEapMethod);
        if (VOS_OK != ulRslt)
        {
            PPPC_WARNING_LOG("PPPC_EAP_AKA_GetPermanentNAI is fail");
            return;
        }
    }

    if (PPPC_EAP_METHOD_TYPE_AKA_PRIME == pstEapAkaDataInfo->enEapMethod)
    {
        ulRslt = PPPC_EAP_AKA_PRIME_DeriveKeys(&(aucIdentity[0]), usIdentityLen,
                        pstEapAkaAuthPara, pstEapAkaKey);
    }
    else
    {
        ulRslt = PPPC_EAP_AKA_DeriveKeys(&(aucIdentity[0]), usIdentityLen,
                        pstEapAkaAuthPara, pstEapAkaKey);
    }

    if (VOS_OK != ulRslt)
    {
        PPPC_WARNING_LOG("DeriveKey is fail");
    }

    /* 勾取可维可测信息 */
    PPPC_EAP_AKA_MntnTraceInfo(pstEapAkaAuthPara, pstEapAkaKey);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_ReciveAuthRes
 功能描述  : 收到卡的鉴权结果
 输入参数  : pstResult --卡计算的结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_ReciveAuthRes
(
    PPPC_EAP_AUTH_RESULT_STRU          *pstResult
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    PPPC_EAP_AKA_ATTRS_STRU            *pstEapAkaAttrInfo;
    PPPC_EAP_AKA_KEY_DATA_STRU         *pstEapAkaKey;
    PPPC_EAP_METHOD_OUTPUT_STRU        *pstEAPMethodOutput;
    VOS_UINT32                          ulRes;
    VOS_UINT32                          ulAttrExistCtrlFlag;


    pstEapAkaDataInfo   = &g_stPppcEapAkaDataInfo;
    pstEapAkaAttrInfo   = &g_stPppcEapAkaPktAttrInfo;
    pstEapAkaKey        = &(pstEapAkaDataInfo->stEapAkaKey);
    pstEAPMethodOutput  = &g_stEAPAkaMethodOutput;
    ulAttrExistCtrlFlag = pstEapAkaAttrInfo->ulAttrExistCtrlFlag;

    /* 消息检查 */
    if (pstResult->ucIdentifier != pstEapAkaDataInfo->usPrevId)
    {
        PPPC_WARNING_LOG2("Receive the result is not Current Msg",
            pstResult->ucIdentifier, pstEapAkaDataInfo->usPrevId);

        return;
    }

    /* 检查卡的鉴权结果 */
    ulRes = PPPC_EAP_AKA_CheckAuthRes(pstResult);
    if (VOS_OK != ulRes)
    {
        return;
    }

    /* 保存卡的计算结果 */
    PS_MEM_CPY(&(pstEapAkaKey->aucIK[0]), &(pstResult->aucIK[0]), USIMM_AUTH_IK_LEN);
    PS_MEM_CPY(&(pstEapAkaKey->aucCK[0]), &(pstResult->aucCK[0]), USIMM_AUTH_CK_LEN);

    /* 计算K */
    PPPC_EAP_AKA_CalFullAuthKeys();

    /* 用计算的K验证AT_MAC */
    ulRes = PPPC_EAP_AKA_VerifyMac(&(pstEapAkaDataInfo->aucPppcInputMsg[0]),
                    pstEapAkaDataInfo->usInputMsgLen, VOS_NULL_PTR, 0);
    if (VOS_OK != ulRes)
    {
        PPPC_WARNING_LOG("used invalid AT_MAC");
        PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);
        return;
    }

    /* Old reauthentication identity must not be used anymore. In
     * other words, if no new identities are received, full
     * authentication will be used on next reauthentication (using
     * pseudonym identity or permanent identity).
     */
    PPPC_EAP_AKA_ClearIdentity(PPPC_EAP_AKA_CLEAR_REAUTH_ID | PPPC_EAP_AKA_CLEAR_EAP_ID);

    if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(ulAttrExistCtrlFlag, PPPC_EAP_AKA_ENCR_BIT))
    {
        ulRes = PPPC_EAP_AKA_ParseEncr();
        if (VOS_OK != ulRes)
        {
            PPPC_WARNING_LOG("decryption is fail");
            PPPC_EAP_AKA_SndClientErrorPkt(pstEAPMethodOutput);

            return;
        }
        /* 解密成功，保存ID信息 */
        PPPC_EAP_AKA_SaveIds();
    }

    /* 收到ResultInd属性的状态处理 */
    PPPC_EAP_AKA_ProcessResultInd(pstEAPMethodOutput);


    /* RFC 4187  p32 specifies that counter is initialized to one after
     * fullauth, but initializing it to zero makes it easier to implement
     * reauth verification.
    */
    pstEapAkaDataInfo->stEapAkaAuthPara.usCounter = 0;

    PPPC_EAP_AKA_ResponseChallenge(pstResult);

    return;

}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_DeInitForReAuth
 功能描述  : 快速重鉴权流程结束后初始化实体信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月16日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_DeInitForReAuth(VOS_VOID)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo;
    VOS_UINT16                          usCounter;


    /*
       快速重鉴权结束
       1)不能清除Identity, PrevID
       2)MSK和EMSK清除, 其余key不清除
       3)方法, 状态不清除, 便于维测(再重新选择方法时, 将被清除)
    */
    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;

    pstEapAkaDataInfo->ucNumIdReq        = 0;
    pstEapAkaDataInfo->ucNumNotification = 0;

    PPPC_EAP_AKA_ClearKeys(PS_TRUE);

    PS_MEM_SET(&(pstEapAkaDataInfo->ucIdMsgs[0]),
               0x0, PPPC_EAP_AKA_ID_MSG_MAX_LEN);
    pstEapAkaDataInfo->usIdMsgLen       = 0;

    pstEapAkaDataInfo->enReauth         = PS_FALSE;
    pstEapAkaDataInfo->enKdfNegotiation = PS_FALSE;

    PS_MEM_SET(&(pstEapAkaDataInfo->aucPppcInputMsg[0]),
                    0x0, PPPC_EAP_MAX_PACKET_LEN);
    pstEapAkaDataInfo->usInputMsgLen    = 0;

    pstEapAkaDataInfo->enResultInd      = PS_FALSE;
    pstEapAkaDataInfo->usCounterTooSmall    = 0;

    /* Counter不能清除 */
    usCounter = pstEapAkaDataInfo->stEapAkaAuthPara.usCounter;
    PS_MEM_SET(&(pstEapAkaDataInfo->stEapAkaAuthPara),
               0x0, sizeof(pstEapAkaDataInfo->stEapAkaAuthPara));

    pstEapAkaDataInfo->stEapAkaAuthPara.usCounter = usCounter;
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_DeInitForFullAuth
 功能描述  : 执行全鉴权流程结束后初始化实体信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月12日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_DeInitForFullAuth(VOS_VOID)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo = VOS_NULL_PTR;
    PPPC_EAP_AKA_AUTH_PARA_STRU        *pstEapAkaAuthPara = VOS_NULL_PTR;


    /*
       全鉴权结束
       1)不能清除Keys, PrevID
       2)不能清除Identity, 但是把LastEapIdentity清除掉
       3)方法, 状态不清除, 便于维测(再重新选择方法时, 将被清除)
    */
    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaAuthPara = &(pstEapAkaDataInfo->stEapAkaAuthPara);

    pstEapAkaDataInfo->ucNumIdReq        = 0;
    pstEapAkaDataInfo->ucNumNotification = 0;

    pstEapAkaDataInfo->enReauth         = PS_FALSE;
    pstEapAkaDataInfo->enKdfNegotiation  = PS_FALSE;

    PS_MEM_SET(pstEapAkaAuthPara, 0x0, sizeof(PPPC_EAP_AKA_AUTH_PARA_STRU));

    PS_MEM_SET(&(pstEapAkaDataInfo->ucIdMsgs[0]),
               0x0, PPPC_EAP_AKA_ID_MSG_MAX_LEN);
    pstEapAkaDataInfo->usIdMsgLen = 0;

    PS_MEM_SET(&(pstEapAkaDataInfo->aucPppcInputMsg[0]),
               0x0, PPPC_EAP_MAX_PACKET_LEN);
    pstEapAkaDataInfo->usInputMsgLen = 0;

    pstEapAkaDataInfo->enResultInd      = PS_FALSE;
    pstEapAkaDataInfo->usCounterTooSmall    = 0;

    PPPC_EAP_AKA_ClearIdentity(PPPC_EAP_AKA_CLEAR_EAP_ID);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_FailInit
 功能描述  : 初始化EAP-AKA实体信息
 输入参数  : enMethodType --EAP-AKA or EAP-AKA'
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月13日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_FailInit(VOS_VOID)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo = VOS_NULL_PTR;
    PPPC_EAP_AKA_KEY_DATA_STRU         *pstEapAkaKey      = VOS_NULL_PTR;
    PPPC_EAP_AKA_AUTH_PARA_STRU        *pstEapAkaAuthPara = VOS_NULL_PTR;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaKey      = &(pstEapAkaDataInfo->stEapAkaKey);
    pstEapAkaAuthPara = &(pstEapAkaDataInfo->stEapAkaAuthPara);

    PS_MEM_SET(pstEapAkaKey, 0, sizeof(PPPC_EAP_AKA_KEY_DATA_STRU));
    PS_MEM_SET(pstEapAkaAuthPara, 0, sizeof(PPPC_EAP_AKA_AUTH_PARA_STRU));

    PS_MEM_SET(&(pstEapAkaDataInfo->ucIdMsgs[0]),
                    0, PPPC_EAP_AKA_ID_MSG_MAX_LEN);
    pstEapAkaDataInfo->usIdMsgLen = 0;
    PS_MEM_SET(&(pstEapAkaDataInfo->aucPppcInputMsg[0]),
                    0, PPPC_EAP_MAX_PACKET_LEN);
    pstEapAkaDataInfo->usInputMsgLen    = 0;
    pstEapAkaDataInfo->enEapAkaState    = PPPC_EAP_AKA_STATE_CONTINUE;
    pstEapAkaDataInfo->enReauth         = PS_FALSE;
    pstEapAkaDataInfo->enResultInd      = PS_FALSE;
    pstEapAkaDataInfo->enKdfNegotiation = PS_FALSE;
    pstEapAkaDataInfo->ucNumIdReq        = 0;
    pstEapAkaDataInfo->ucNumNotification = 0;
    pstEapAkaDataInfo->usCounterTooSmall = 0;

    PPPC_EAP_AKA_ClearIdentity((PPPC_EAP_AKA_CLEAR_EAP_ID | PPPC_EAP_AKA_CLEAR_REAUTH_ID));

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_NotifyResult
 功能描述  : EAP通知AKA网侧的鉴权结果
 输入参数  : ulResult --网侧对Peer端的鉴权结果
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月13日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_NotifyResult(VOS_UINT32 ulResult)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulPppId;


    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    ulPppId           = 0xFFFF;

    if (VOS_ERR == ulResult)
    {
        PPPC_EAP_AKA_UpdateState(ulPppId, PPPC_EAP_AKA_STATE_FAILURE);
        PPPC_EAP_AKA_FailInit();
    }
    else
    {
        PPPC_EAP_AKA_UpdateState(ulPppId, PPPC_EAP_AKA_STATE_SUCCESS);
        if (PS_TRUE == pstEapAkaDataInfo->enReauth)
        {
            PPPC_EAP_AKA_DeInitForReAuth();
        }
        else
        {
            PPPC_EAP_AKA_DeInitForFullAuth();
        }
    }

    return;
}


/*****************************************************************************
 函 数 名  : PPPC_EAP_GetIdentity
 功能描述  : EAP来获取Identity
 输入参数  : enType - AKA or AKA'
 输出参数  : pucIdentity - 获取的NAI
             pusIdentityLen - 获取的NAI长度
 返 回 值  : VOS_OK; VOS_ERR;
 调用函数  :
 被调函数  :
 说    明  :

 修改历史      :
  1.日    期   : 2015年11月14日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_EAP_GetIdentity
(
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enMethodType,
    VOS_UINT8                          *pucIdentity,
    VOS_UINT16                         *pusIdentityLen
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo   = VOS_NULL_PTR;
    PPPC_EAP_AKA_ID_INFO_STRU          *pstEapAkaIdInfo     = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    PPPC_EAP_METHOD_TYPE_ENUM_UINT16    enEapAkaType        = PPPC_EAP_METHOD_TYPE_AKA_PRIME;
    VOS_UINT32                          ulResult            = VOS_OK;

    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;
    pstEapAkaIdInfo   = &(pstEapAkaDataInfo->stEapAkaIdInfo);

    if (0 != pstEapAkaIdInfo->usReauthIdLen)
    {
        PS_MEM_CPY(pucIdentity, &(pstEapAkaIdInfo->aucReauthId[0]),
                    pstEapAkaIdInfo->usReauthIdLen);
        *pusIdentityLen  = pstEapAkaIdInfo->usReauthIdLen;

    }
    else if (0 != pstEapAkaIdInfo->usPseudonymLen)
    {
        PS_MEM_CPY(pucIdentity, &(pstEapAkaIdInfo->aucPseudonym[0]),
                    pstEapAkaIdInfo->usPseudonymLen);
        *pusIdentityLen = pstEapAkaIdInfo->usPseudonymLen;

    }
    else if (0 != pstEapAkaIdInfo->usPermenentIdLen)
    {
        PS_MEM_CPY(pucIdentity, &(pstEapAkaIdInfo->aucPermenentId[0]),
            pstEapAkaIdInfo->usPermenentIdLen);
        *pusIdentityLen = pstEapAkaIdInfo->usPermenentIdLen;

    }
    else
    {
        if (PPPC_EAP_AKA_TYPE == enMethodType)
        {
            enEapAkaType = PPPC_EAP_METHOD_TYPE_AKA;
        }
        else
        {
            enEapAkaType = PPPC_EAP_METHOD_TYPE_AKA_PRIME;
        }

        ulRet = PPPC_EAP_AKA_GetPermanentNAI(pucIdentity,
                    pusIdentityLen, enEapAkaType);

        if(VOS_OK != ulRet)
        {
             PPPC_WARNING_LOG("EAP-AKA: There is no Identity Info");

             ulResult = VOS_ERR;
        }
    }

    if (VOS_ERR != ulResult)
    {
        /* 将当前使用的Identity保存到LastIdentity*/
        PS_MEM_SET(&(pstEapAkaIdInfo->aucLastEapIdentity[0]), 0, pstEapAkaIdInfo->usLastEapIdentityLen);
        PS_MEM_CPY(&(pstEapAkaIdInfo->aucLastEapIdentity[0]), pucIdentity, *pusIdentityLen);
        pstEapAkaIdInfo->usLastEapIdentityLen = *pusIdentityLen;
    }

    return ulResult;
}
/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_Init
 功能描述  : 初始化EAP-AKA实体信息
 输入参数  : enMethodType --EAP-AKA or EAP-AKA'
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月13日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_Init
(
    PPPC_EAP_METHODS_TYPE_ENUM_UINT8    enMethodType
)
{
    PPPC_EAP_AKA_DATA_INFO_STRU        *pstEapAkaDataInfo = VOS_NULL_PTR;


    /* EAP在选好方法的时候会先初始化EAP-AKA实体信息 */
    PS_MEM_SET(&g_stPppcEapAkaDataInfo, 0, sizeof(PPPC_EAP_AKA_DATA_INFO_STRU));
    pstEapAkaDataInfo = &g_stPppcEapAkaDataInfo;

    pstEapAkaDataInfo->enEapAkaState    = PPPC_EAP_AKA_STATE_CONTINUE;
    pstEapAkaDataInfo->enReauth         = PS_FALSE;
    pstEapAkaDataInfo->enResultInd      = PS_FALSE;
    pstEapAkaDataInfo->usPrevId         = 0xFFFF;
    pstEapAkaDataInfo->enKdfNegotiation = PS_FALSE;

    if (PPPC_EAP_AKA_TYPE == enMethodType)
    {
        pstEapAkaDataInfo->enEapMethod  = PPPC_EAP_METHOD_TYPE_AKA;
    }
    else if (PPPC_EAP_AKA_PRIME_TYPE == enMethodType)
    {
        pstEapAkaDataInfo->enEapMethod  = PPPC_EAP_METHOD_TYPE_AKA_PRIME;
    }
    else
    {
        PPPC_WARNING_LOG("EAP-AKA: enMethodType is error");
    }

    return;
}


/*****************************************************************************
 函 数 名  : PPPC_EAP_AKA_InitState
 功能描述  : 初始化EAP-AKA状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月13日
    作    者   : g00260269
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_EAP_AKA_InitState(VOS_VOID)
{
    VOS_UINT32                          ulPppId;

    ulPppId = 0xFFFF;
    PPPC_EAP_AKA_UpdateState(ulPppId, PPPC_EAP_AKA_STATE_CONTINUE);

    return;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


