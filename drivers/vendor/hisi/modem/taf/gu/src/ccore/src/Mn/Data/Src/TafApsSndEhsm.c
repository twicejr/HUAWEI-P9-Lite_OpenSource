/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsSndEhsm.c
  版 本 号   : 初稿
  作    者   : y00314741
  生成日期   : 2015年05月08日
  最近修改   :
  功能描述   : TAF APS模块发送消息给HSM的函数实现文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年05月08日
    作    者   : y00314741
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "TafLog.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "TafApsSndEhsm.h"
#include "TafApsCtx.h"
#include "TafApsComFunc.h"
#include "TafApsDecode.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "ehsm_aps_pif.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_EHSM_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 函 数 名  : TAF_APS_SndEhsmPdnActReq
 功能描述  : 发送ID_APS_EHSM_PDN_ACTIVATE_REQ消息
 输入参数  : VOS_UINT8                    ucPdpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月08日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmPdnActReq(
    VOS_UINT8                           ucPdpId,
    TAF_APS_ORIG_TYPE_ENUM_UINT8        enDailType
)
{
    APS_EHSM_PDN_ACTIVATE_REQ_STRU     *pstActReq      = VOS_NULL_PTR;
    TAF_PS_MSG_STRU                    *pstAppMsg      = VOS_NULL_PTR;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq = VOS_NULL_PTR;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_AUTH_INFO_STRU              stAuthInfo;
    VOS_UINT32                          ulResult;

    /* 获取消息内容 */
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg       = (TAF_PS_MSG_STRU *)(pstEntryMsg->aucEntryMsgBuffer);

    pstActReq       = (APS_EHSM_PDN_ACTIVATE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_EHSM_PDN_ACTIVATE_REQ_STRU));

    if (VOS_NULL_PTR == pstActReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmPdnActReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstActReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_PDN_ACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstActReq->ulReceiverPid            = UEPS_PID_EHSM;
    pstActReq->enMsgId                  = ID_APS_EHSM_PDN_ACTIVATE_REQ;
    pstActReq->usOpId                   = 0;
    pstActReq->ucCid                    = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    if (TAF_APS_ORIG_TYPE_PS_CALL == enDailType)
    {
        pstCallOrigReq                  = (TAF_PS_CALL_ORIG_REQ_STRU *)(pstAppMsg->aucContent);
        pstActReq->enPdnType            = pstCallOrigReq->stDialParaInfo.enPdpType;

        pstActReq->enAuthType           = TAF_APS_MapApsAuthTypeToEhsm(pstCallOrigReq->stDialParaInfo.enAuthType);

        VOS_StrNCpy((VOS_CHAR *)pstActReq->aucUserName,
                    (VOS_CHAR *)pstCallOrigReq->stDialParaInfo.aucUserName,
                     EHSM_APS_MAX_AUTHDATA_USERNAME_LEN);

        VOS_StrNCpy((VOS_CHAR *)pstActReq->aucPassword,
                    (VOS_CHAR *)pstCallOrigReq->stDialParaInfo.aucPassWord,
                     EHSM_APS_MAX_AUTHDATA_PASSWORD_LEN);

        pstActReq->stApn.ulLength = VOS_StrLen((VOS_CHAR *)pstCallOrigReq->stDialParaInfo.aucApn);
        PS_MEM_CPY((VOS_INT8*)pstActReq->stApn.aucApn,
                    (VOS_INT8*)pstCallOrigReq->stDialParaInfo.aucApn,
                     EHSM_APS_APN_MAX_LEN);
    }
    else
    {
        pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU *)(pstAppMsg->aucContent);
        PS_MEM_SET(&stAuthInfo, 0, sizeof(TAF_APS_AUTH_INFO_STRU));

        pstActReq->enPdnType  = TAF_APS_GetPdpEntDialPdpType(ucPdpId, pstActReq->ucCid);

        pstActReq->enAuthType = EHSM_APS_AUTH_TYPE_PAP;

        /* MODEM拨号时，只支持PAP类型的鉴权 */
        if ((VOS_TRUE == pstPppDialOrigReq->stPppDialParaInfo.bitOpPppConfigInfo)
         && (TAF_PDP_AUTH_TYPE_PAP == pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthType))
        {
            ulResult = TAF_APS_DecodePapInfo(&stAuthInfo,
                                             pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthContent.stPapContent.aucPapReqBuf,
                                             pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthContent.stPapContent.usPapReqLen);

            if (VOS_OK == ulResult)
            {
                PS_MEM_CPY(pstActReq->aucUserName,
                           stAuthInfo.unAuthParam.stPapParam.aucUsername,
                           stAuthInfo.unAuthParam.stPapParam.ucUsernameLen);

                PS_MEM_CPY(pstActReq->aucPassword,
                           stAuthInfo.unAuthParam.stPapParam.aucPassword,
                           stAuthInfo.unAuthParam.stPapParam.ucPasswordLen);
            }
        }

        pstActReq->stApn.ulLength = TAF_APS_GetTafCidInfoApnLen(pstActReq->ucCid);
        PS_MEM_CPY((VOS_INT8 *)pstActReq->stApn.aucApn,
                    (VOS_INT8 *)TAF_APS_GetTafCidInfoApnData(pstActReq->ucCid),
                     EHSM_APS_APN_MAX_LEN);

    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstActReq);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndEhsmPdnDeactReq
 功能描述  : 发送ID_APS_EHSM_PDN_DEACTIVATE_REQ消息
 输入参数  : VOS_UINT8                    ucPdpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月13日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmPdnDeactReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU   *pstDeactReq  = VOS_NULL_PTR;

    pstDeactReq = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                        sizeof(APS_EHSM_PDN_DEACTIVATE_REQ_STRU));

    if (VOS_NULL_PTR == pstDeactReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmPdnDeactReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstDeactReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_PDN_DEACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstDeactReq->ulReceiverPid          = UEPS_PID_EHSM;
    pstDeactReq->enMsgId                = ID_APS_EHSM_PDN_DEACTIVATE_REQ;
    pstDeactReq->usOpId                 = 0;
    pstDeactReq->ucCid                  = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    pstDeactReq->ucPdnId                = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);

    PS_SEND_MSG(WUEPS_PID_TAF, pstDeactReq);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndEhsmPsRatTypeNtf
 功能描述  : 发送ID_APS_EHSM_PS_RAT_TYPE_NOTIFY消息
 输入参数  : APS_EHSM_PS_RATTYPE_ENUM_UINT32     enPsRatType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月15日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmPsRatTypeNtf(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode
)
{

    APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU   *pstPsRatTypeNty = VOS_NULL_PTR;
    APS_EHSM_PS_RATTYPE_ENUM_UINT32     enPsRatType;

    switch (enCurrCdataServiceMode)
    {
        case TAF_APS_RAT_TYPE_NULL:
            enPsRatType = APS_EHSM_PS_RATTYPE_NULL;
            break;
        case TAF_APS_RAT_TYPE_1X:
            enPsRatType = APS_EHSM_PS_RATTYPE_1X;
            break;
        case TAF_APS_RAT_TYPE_HRPD:
            enPsRatType = APS_EHSM_PS_RATTYPE_HRPD;
            break;
        case TAF_APS_RAT_TYPE_EHRPD:
            enPsRatType = APS_EHSM_PS_RATTYPE_EHRPD;
            break;
        case TAF_APS_RAT_TYPE_LTE:
            enPsRatType = APS_EHSM_PS_RATTYPE_LTE;
            break;
        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmPsRatTypeNtf: enRatType Error");
            return;
    }

    pstPsRatTypeNty  = (APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                        sizeof(APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstPsRatTypeNty)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmPsRatTypeNtf: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPsRatTypeNty + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstPsRatTypeNty->ulReceiverPid     = UEPS_PID_EHSM;
    pstPsRatTypeNty->enMsgId           = ID_APS_EHSM_PS_RAT_TYPE_NOTIFY;
    pstPsRatTypeNty->usOpId            = 0;
    pstPsRatTypeNty->enPsRatType       = enPsRatType;

    PS_SEND_MSG(WUEPS_PID_TAF, pstPsRatTypeNty);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndEhsmReconnReq
 功能描述  : 发送ID_APS_EHSM_RECONN_REQ消息
 输入参数  : VOS_UINT8                           ucPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月15日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmReconnReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_EHSM_RECONN_REQ_STRU           *pstReconnReq = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnId;

    ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);
    pstReconnReq  = (APS_EHSM_RECONN_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                        sizeof(APS_EHSM_RECONN_REQ_STRU));

    if (VOS_NULL_PTR == pstReconnReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmReconnReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstReconnReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_RECONN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstReconnReq->ulReceiverPid     = UEPS_PID_EHSM;
    pstReconnReq->enMsgId           = ID_APS_EHSM_RECONN_REQ;
    pstReconnReq->usOpId            = 0;
    pstReconnReq->ucPdnId           = ucPdnId;
    pstReconnReq->ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    PS_SEND_MSG(WUEPS_PID_TAF, pstReconnReq);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndEhsmPdnCtxInfoInd
 功能描述  : 发送ID_APS_EHSM_PDN_CONTEXT_INFO_IND消息
 输入参数  : VOS_UINT8                           ucPdnId
             VOS_UINT8                           ucCid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月15日
    作    者   : y00314741
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmPdnCtxInfoNotify(
    VOS_UINT8                           ucPdpId,
    EHSM_APS_PDN_OPTION_ENUM_UINT32     enOption
)
{
    APS_EHSM_PDN_CONTEXT_INFO_NOTIFY_STRU                  *pstPdnCtxInfoNty = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST                              *pstPdpEntity     = VOS_NULL_PTR;

    pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdnCtxInfoNty  = (APS_EHSM_PDN_CONTEXT_INFO_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                        sizeof(APS_EHSM_PDN_CONTEXT_INFO_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstPdnCtxInfoNty)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmPdnCtxInfoInd: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPdnCtxInfoNty + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_PDN_CONTEXT_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstPdnCtxInfoNty->ulReceiverPid     = UEPS_PID_EHSM;
    pstPdnCtxInfoNty->enMsgId           = ID_APS_EHSM_PDN_CONTEXT_INFO_NOTIFY;
    pstPdnCtxInfoNty->usOpId            = 0;
    pstPdnCtxInfoNty->ucPdnId           = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);
    pstPdnCtxInfoNty->ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    pstPdnCtxInfoNty->enOption          = enOption;

    if (VOS_TRUE == pstPdpEntity->PdpDns.OP_PriDns)
    {
        pstPdnCtxInfoNty->stIpv4Dns.bitOpIpv4PrimDNS = VOS_TRUE;
        PS_MEM_CPY(pstPdnCtxInfoNty->stIpv4Dns.aucIpv4PrimDNS,
                   pstPdpEntity->PdpDns.aucPriDns,
                   EHSM_APS_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstPdpEntity->PdpDns.OP_SecDns)
    {
        pstPdnCtxInfoNty->stIpv4Dns.bitOpIpv4SecDNS = VOS_TRUE;
        PS_MEM_CPY(pstPdnCtxInfoNty->stIpv4Dns.aucIpv4SecDNS,
                   pstPdpEntity->PdpDns.aucSecDns,
                   EHSM_APS_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstPdpEntity->stPdpIpV6Dns.bitOpPriDns)
    {
        pstPdnCtxInfoNty->stIpv6Dns.bitOpIpv6PrimDNS = VOS_TRUE;
        PS_MEM_CPY(pstPdnCtxInfoNty->stIpv6Dns.aucIpv6PrimDNS,
                   pstPdpEntity->stPdpIpV6Dns.aucPriDns,
                   EHSM_APS_IPV6_ADDR_LEN);
    }

    if (VOS_TRUE == pstPdpEntity->stPdpIpV6Dns.bitOpSecDns)
    {
        pstPdnCtxInfoNty->stIpv6Dns.bitOpIpv6SecDNS = VOS_TRUE;
        PS_MEM_CPY(pstPdnCtxInfoNty->stIpv6Dns.aucIpv6SecDNS,
                   pstPdpEntity->stPdpIpV6Dns.aucSecDns,
                   EHSM_APS_IPV6_ADDR_LEN);
    }

    if (VOS_TRUE == pstPdpEntity->bitOpIpv6RaInfo)
    {
        pstPdnCtxInfoNty->stIpv6Prefix.bitOpIpv6Prefix = VOS_TRUE;
        PS_MEM_CPY(pstPdnCtxInfoNty->stIpv6Prefix.aucIpv6Prefix,
                   pstPdpEntity->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                   EHSM_APS_IPV6_ADDR_LEN);
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPdnCtxInfoNty);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndEhsmLocDetachInd
 功能描述  : TAF Snd Ehsm Detach Ind
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月30日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmLocDetachNotify(VOS_VOID)
{
    APS_EHSM_LOC_DETACH_NOTIFY_STRU    *pstLocDetachNty = VOS_NULL_PTR;

    pstLocDetachNty  = (APS_EHSM_LOC_DETACH_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                       sizeof(APS_EHSM_LOC_DETACH_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstLocDetachNty)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmLocDetachInd: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstLocDetachNty + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_LOC_DETACH_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstLocDetachNty->ulReceiverPid = UEPS_PID_EHSM;
    pstLocDetachNty->enMsgId       = ID_APS_EHSM_LOC_DETACH_NOTIFY;
    pstLocDetachNty->usOpId        = 0;

    PS_SEND_MSG(WUEPS_PID_TAF, pstLocDetachNty);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndEhsmLocDeactReq
 功能描述  : 发送ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY消息
 输入参数  : VOS_UINT8                    ucPdpId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月11日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmLocDeactNtf(
    VOS_UINT8                           ucPdpId
)
{
    APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU           *pstLocDeacNtf;
    pstLocDeacNtf = (APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                        sizeof(APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstLocDeacNtf)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmLocDeactNotify: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstLocDeacNtf + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstLocDeacNtf->ulReceiverPid        = UEPS_PID_EHSM;
    pstLocDeacNtf->enMsgId              = ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY;
    pstLocDeacNtf->usOpId               = 0;
    pstLocDeacNtf->ucCid                = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    PS_SEND_MSG(WUEPS_PID_TAF, pstLocDeacNtf);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_APS_SndEhsmDiscNtf
 功能描述  : 发送ID_APS_EHSM_DISC_NOTIFY消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月08日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmDiscNtf(VOS_VOID)
{
    APS_EHSM_DISC_NOTIFY_STRU             *pstDiscNtf = VOS_NULL_PTR;

    /* 获取消息内容 */
    pstDiscNtf       = (APS_EHSM_DISC_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_EHSM_DISC_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstDiscNtf)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmDiscNtf: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstDiscNtf + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_DISC_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstDiscNtf->ulReceiverPid           = UEPS_PID_EHSM;
    pstDiscNtf->enMsgId                 = ID_APS_EHSM_DISC_NOTIFY;
    pstDiscNtf->usOpId                  = 0;

    PS_SEND_MSG(WUEPS_PID_TAF, pstDiscNtf);

    return;
}


/*****************************************************************************
 函 数 名  : TAF_APS_SndEhsmPdnAttachReq
 功能描述  : TAF向EHSM发送Pdn Attach请求
 输入参数  : VOS_UINT8                           ucCid
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月23日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmPdnAttachReq(
    VOS_UINT8                           ucPdpId,
    TAF_APS_ORIG_TYPE_ENUM_UINT8        enDailType
)
{
    APS_EHSM_PDN_ATTACH_REQ_STRU       *pstAttachReq   = VOS_NULL_PTR;
    TAF_PS_MSG_STRU                    *pstAppMsg      = VOS_NULL_PTR;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq = VOS_NULL_PTR;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_AUTH_INFO_STRU              stAuthInfo;
    VOS_UINT32                          ulResult;

    /* 获取消息内容 */
    pstEntryMsg  = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg    = (TAF_PS_MSG_STRU *)(pstEntryMsg->aucEntryMsgBuffer);
    pstAttachReq = (APS_EHSM_PDN_ATTACH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                   sizeof(APS_EHSM_PDN_ATTACH_REQ_STRU));

    if (VOS_NULL_PTR == pstAttachReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmPdnAttachReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstAttachReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_PDN_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填写参数 */
    pstAttachReq->ulReceiverPid            = UEPS_PID_EHSM;
    pstAttachReq->enMsgId                  = ID_APS_EHSM_PDN_ATTACH_REQ;
    pstAttachReq->usOpId                   = 0;
    pstAttachReq->ucCid                    = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    if (TAF_APS_ORIG_TYPE_PS_CALL == enDailType)
    {
        pstCallOrigReq                  = (TAF_PS_CALL_ORIG_REQ_STRU *)(pstAppMsg->aucContent);
        pstAttachReq->enPdnType         = pstCallOrigReq->stDialParaInfo.enPdpType;
        pstAttachReq->enAuthType        = TAF_APS_MapApsAuthTypeToEhsm(pstCallOrigReq->stDialParaInfo.enAuthType);

        VOS_StrNCpy((VOS_CHAR *)pstAttachReq->aucUserName,
                    (VOS_CHAR *)pstCallOrigReq->stDialParaInfo.aucUserName,
                     EHSM_APS_MAX_AUTHDATA_USERNAME_LEN);

        VOS_StrNCpy((VOS_CHAR *)pstAttachReq->aucPassword,
                    (VOS_CHAR *)pstCallOrigReq->stDialParaInfo.aucPassWord,
                     EHSM_APS_MAX_AUTHDATA_PASSWORD_LEN);

        pstAttachReq->stApn.ulLength = VOS_StrLen((VOS_CHAR *)pstCallOrigReq->stDialParaInfo.aucApn);
        PS_MEM_CPY((VOS_INT8*)pstAttachReq->stApn.aucApn,
                    (VOS_INT8*)pstCallOrigReq->stDialParaInfo.aucApn,
                     EHSM_APS_APN_MAX_LEN);
    }
    else
    {
        pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU *)(pstAppMsg->aucContent);
        PS_MEM_SET(&stAuthInfo, 0, sizeof(TAF_APS_AUTH_INFO_STRU));

        pstAttachReq->enPdnType = TAF_APS_GetPdpEntDialPdpType(ucPdpId, pstAttachReq->ucCid);

        pstAttachReq->enAuthType = EHSM_APS_AUTH_TYPE_PAP;

        /* MODEM拨号时，只支持PAP类型的鉴权 */
        if ((VOS_TRUE == pstPppDialOrigReq->stPppDialParaInfo.bitOpPppConfigInfo)
         && (TAF_PDP_AUTH_TYPE_PAP == pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthType))
        {
            ulResult = TAF_APS_DecodePapInfo(&stAuthInfo,
                                             pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthContent.stPapContent.aucPapReqBuf,
                                             pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthContent.stPapContent.usPapReqLen);

            if (VOS_OK == ulResult)
            {
                PS_MEM_CPY(pstAttachReq->aucUserName,
                           stAuthInfo.unAuthParam.stPapParam.aucUsername,
                           stAuthInfo.unAuthParam.stPapParam.ucUsernameLen);

                PS_MEM_CPY(pstAttachReq->aucPassword,
                           stAuthInfo.unAuthParam.stPapParam.aucPassword,
                           stAuthInfo.unAuthParam.stPapParam.ucPasswordLen);
            }
        }

        pstAttachReq->stApn.ulLength = TAF_APS_GetTafCidInfoApnLen(pstAttachReq->ucCid);
        PS_MEM_CPY((VOS_INT8 *)pstAttachReq->stApn.aucApn,
                    (VOS_INT8 *)TAF_APS_GetTafCidInfoApnData(pstAttachReq->ucCid),
                     EHSM_APS_APN_MAX_LEN);

    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstAttachReq);

    return;
}

#endif


/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
