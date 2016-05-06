

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmPreProcAct.h"
#include "CnasEhsmCtx.h"
#include "CnasEhsmMntn.h"
#include "CnasEhsmSndHsd.h"
#include "CnasEhsmSndAps.h"
#include "CnasEhsmSndEsm.h"
#include "ehsm_hsd_pif.h"
#include "CnasHsmCtx.h"
/* To Do: Need to add EHSM depending interfaces */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_PRE_PROC_ACT_C

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  3 Function Define
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


VOS_UINT32 CNAS_EHSM_RcvApsPdnContextInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_EHSM_PDN_CONTEXT_INFO_NOTIFY_STRU                  *pstApsPdnCtx = VOS_NULL_PTR;
    CNAS_EHSM_CTX_STRU                                     *pstEhsmCtx   = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU                     *pstPdnInfo   = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT8                                               aucIpv6Prefix[CNAS_EHSM_IPV6_ADDR_LEN-CNAS_EHSM_IPV6_IFID_LEN];


    pstApsPdnCtx    = (APS_EHSM_PDN_CONTEXT_INFO_NOTIFY_STRU *)pstMsg;
    pstEhsmCtx      = CNAS_EHSM_GetEhsmCtxAddr();

    for (i = 0; i < CNAS_EHSM_MAX_PDN_NUM; i++)
    {
        if ((pstEhsmCtx->astLocalPdnBearInfo[i].ucPdnId == pstApsPdnCtx->ucPdnId)
         && (VOS_TRUE == pstEhsmCtx->astLocalPdnBearInfo[i].ucInUsed))

        {
            pstEhsmCtx->astLocalPdnBearInfo[i].ucCid = pstApsPdnCtx->ucCid;

            pstPdnInfo = &(pstEhsmCtx->astLocalPdnBearInfo[pstApsPdnCtx->ucPdnId]);

            if (1 == pstApsPdnCtx->stIpv4Dns.bitOpIpv4PrimDNS)
            {
                pstPdnInfo->stPcoIpv4Item.bitOpPriDns = 1;
                NAS_MEM_CPY_S(&(pstPdnInfo->stPcoIpv4Item.aucPriDns[0]), 
                              CNAS_EHSM_IPV4_ADDR_LEN, 
                              &(pstApsPdnCtx->stIpv4Dns.aucIpv4PrimDNS[0]), 
                              EHSM_APS_IPV4_ADDR_LEN);
            }

            if (1 == pstApsPdnCtx->stIpv4Dns.bitOpIpv4SecDNS)
            {
                pstPdnInfo->stPcoIpv4Item.bitOpSecDns = 1;
                NAS_MEM_CPY_S(&(pstPdnInfo->stPcoIpv4Item.aucSecDns[0]), 
                              CNAS_EHSM_IPV4_ADDR_LEN,
                              &(pstApsPdnCtx->stIpv4Dns.aucIpv4SecDNS[0]), 
                              EHSM_APS_IPV4_ADDR_LEN);
            }

            if (1 == pstApsPdnCtx->stIpv6Dns.bitOpIpv6PrimDNS)
            {
                pstPdnInfo->stPcoIpv6Item.bitOpPriDns = 1;
                NAS_MEM_CPY_S(&(pstPdnInfo->stPcoIpv6Item.aucPriDns[0]), 
                              CNAS_EHSM_IPV6_DNS_LEN,
                              &(pstApsPdnCtx->stIpv6Dns.aucIpv6PrimDNS[0]), 
                              EHSM_APS_IPV6_ADDR_LEN);
            }

            if (1 == pstApsPdnCtx->stIpv6Dns.bitOpIpv6SecDNS)
            {
                pstPdnInfo->stPcoIpv6Item.bitOpSecDns = 1;
                NAS_MEM_CPY_S(&(pstPdnInfo->stPcoIpv6Item.aucSecDns[0]), 
                              CNAS_EHSM_IPV6_DNS_LEN,
                              &(pstApsPdnCtx->stIpv6Dns.aucIpv6SecDNS[0]), 
                              EHSM_APS_IPV6_ADDR_LEN);
            }

            if (1 == pstApsPdnCtx->stIpv6Prefix.bitOpIpv6Prefix)
            {
                PS_MEM_CPY(&(pstPdnInfo->stPdnAddr.aucIpv6Addr[0]), &(pstApsPdnCtx->stIpv6Prefix.aucIpv6Prefix[0]), (EHSM_APS_IPV6_ADDR_LEN-EHSM_APS_IPV6_IFID_LEN));
            }

            /*Send PDN sync ind to LNAS */
            if (EHSM_APS_PDN_OPTION_MODIFIED == pstApsPdnCtx->enOption)
            {
                if ((CNAS_EHSM_PDN_TYPE_IPV4V6 == pstPdnInfo->enPdnType)
                 || (CNAS_EHSM_PDN_TYPE_IPV6   == pstPdnInfo->enPdnType))
                {
                    PS_MEM_SET(aucIpv6Prefix, 0, (EHSM_APS_IPV6_ADDR_LEN-EHSM_APS_IPV6_IFID_LEN));

                    if ((0 != PS_MEM_CMP(&(pstPdnInfo->stPdnAddr.aucIpv6Addr[0]), aucIpv6Prefix, (EHSM_APS_IPV6_ADDR_LEN-EHSM_APS_IPV6_IFID_LEN)))
                     && (0 == pstPdnInfo->stPdnAddr.ucSyncToEsmIpv6Addr))
                    {
                        pstPdnInfo->stPdnAddr.ucSyncToEsmIpv6Addr = 1;
                        CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd(pstPdnInfo, VOS_FALSE, EHSM_ESM_PDN_OPT_MODIFIED);
                    }
                }
                else
                {
                    CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd(pstPdnInfo, VOS_FALSE, EHSM_ESM_PDN_OPT_MODIFIED);
                }
            }

            break;
        }
    }


    return VOS_TRUE;
}


VOS_UINT32 CNAS_EHSM_RcvHsmConnectInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_SetAirLinkExistFlag(VOS_TRUE);

    if (CNAS_EHSM_EHRPD_DORMANT_STA == CNAS_EHSM_GetEhrpdState())
    {
        CNAS_EHSM_SetEhrpdState(CNAS_EHSM_EHRPD_ACTIVE_STA);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvHsmDiscInd_PreProc
 功能描述  : 收到HSM Disc Ind消息时，需要刷新空口链路状态
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月4日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvHsmDiscInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_SetAirLinkExistFlag(VOS_FALSE);

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvPppModifyInd_PreProc
 功能描述  : 收到PPP发送的ip地址变更消息处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月6日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvPppModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_EHRPD_MODIFY_IND_STRU    *pstPppModifyInd = VOS_NULL_PTR;

    pstPppModifyInd = (CTTF_CNAS_EHRPD_MODIFY_IND_STRU *)pstMsg;

    if (VOS_TRUE == CNAS_EHSM_IsPdnActived(pstPppModifyInd->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* 否则不进状态机处理 */
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_RcvEsmClearAllBearer_PreProc
 功能描述  : 预处理里处理ID_ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月14日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_RcvEsmClearAllBearer_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_EHSM_ClearAllLteLocalPdnInfo();

    return VOS_TRUE;
}


#endif /* FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



