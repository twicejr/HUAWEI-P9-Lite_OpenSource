/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmSndAps.c
 Author          :
 Version         :
 Date            :   14/05/2015
 Description     :   EHSM module Sends messages to APS process file.
 Function list   :
 History         :
     1) Date :
        Author:
        Modification:
********************************************************************************/

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmSndAps.h"
#include "CnasEhsmCtx.h"
#include "CnasEhsmMntn.h"
#include "ehsm_aps_pif.h"
/* To Do: Need to add EHSM to APS interface file */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_SND_APS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  3 Function Define
*****************************************************************************/

/* To Do: Need to write deifinitions of all functions to send message is APS */

VOS_VOID CNAS_EHSM_SndApsPdnActivateInd(
    VOS_UINT8                           ucPdnId
)
{
    EHSM_APS_PDN_ACTIVATE_IND_STRU     *pstMsg     = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstPdnInfo = VOS_NULL_PTR;
    CNAS_EHSM_CTX_STRU                 *pstCtxAdrr = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (EHSM_APS_PDN_ACTIVATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                               sizeof(EHSM_APS_PDN_ACTIVATE_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(EHSM_APS_PDN_ACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(EHSM_APS_PDN_ACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->enMsgId             = ID_EHSM_APS_PDN_ACTIVATE_IND;

    pstCtxAdrr = CNAS_EHSM_GetEhsmCtxAddr();
    pstPdnInfo = &(pstCtxAdrr->astLocalPdnBearInfo[ucPdnId]);
    pstMsg->ucCid    = pstPdnInfo->ucCid;
    pstMsg->ucPdnId  = pstPdnInfo->ucPdnId;
    pstMsg->ucRabId  = (VOS_UINT8)pstPdnInfo->ulEpsbId;
    pstMsg->usMtu    = pstPdnInfo->usMtu;

    switch(pstPdnInfo->stPdnAddr.enPdnType)
    {
        case CNAS_EHSM_PDN_TYPE_IPV4:
        {
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv4Addr[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv4Addr[0]), CNAS_EHSM_IPV4_ADDR_LEN);
            pstMsg->stPdnAddr.enPdnType = EHSM_APS_PDN_TYPE_IPV4;

            if (1 == pstPdnInfo->stPcoIpv4Item.bitOpPriDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv4Dns.aucIpv4PrimDNS[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPcoIpv4Item.aucPriDns[0]), CNAS_EHSM_IPV4_ADDR_LEN);
                pstMsg->stIpv4Dns.bitOpIpv4PrimDNS = 1;
            }

            if (1 == pstPdnInfo->stPcoIpv4Item.bitOpSecDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv4Dns.aucIpv4SecDNS[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPcoIpv4Item.aucSecDns[0]), CNAS_EHSM_IPV4_ADDR_LEN);
                pstMsg->stIpv4Dns.bitOpIpv4SecDNS = 1;
            }

            break;
        }
        case CNAS_EHSM_PDN_TYPE_IPV6:
        {
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv6Addr[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv6Addr[0]), CNAS_EHSM_IPV6_ADDR_LEN);
            pstMsg->stPdnAddr.enPdnType = EHSM_APS_PDN_TYPE_IPV6;

            if (1 == pstPdnInfo->stPcoIpv6Item.bitOpPriDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv6Dns.aucIpv6PrimDNS[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPcoIpv6Item.aucPriDns[0]), CNAS_EHSM_IPV6_ADDR_LEN);
                pstMsg->stIpv6Dns.bitOpIpv6PrimDNS = 1;
            }

            if (1 == pstPdnInfo->stPcoIpv6Item.bitOpSecDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv6Dns.aucIpv6SecDNS[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPcoIpv6Item.aucSecDns[0]), CNAS_EHSM_IPV6_ADDR_LEN);
                pstMsg->stIpv6Dns.bitOpIpv6SecDNS = 1;
            }

            break;
        }
        case CNAS_EHSM_PDN_TYPE_IPV4V6:
        {
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv6Addr[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv6Addr[0]), CNAS_EHSM_IPV6_ADDR_LEN);
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv4Addr[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv4Addr[0]), CNAS_EHSM_IPV4_ADDR_LEN);
            pstMsg->stPdnAddr.enPdnType = EHSM_APS_PDN_TYPE_IPV4V6;
            if (1 == pstPdnInfo->stPcoIpv4Item.bitOpPriDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv4Dns.aucIpv4PrimDNS[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPcoIpv4Item.aucPriDns[0]), CNAS_EHSM_IPV4_ADDR_LEN);
                pstMsg->stIpv4Dns.bitOpIpv4PrimDNS = 1;
            }

            if (1 == pstPdnInfo->stPcoIpv4Item.bitOpSecDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv4Dns.aucIpv4SecDNS[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPcoIpv4Item.aucSecDns[0]), CNAS_EHSM_IPV4_ADDR_LEN);
                pstMsg->stIpv4Dns.bitOpIpv4SecDNS = 1;
            }

            if (1 == pstPdnInfo->stPcoIpv6Item.bitOpPriDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv6Dns.aucIpv6PrimDNS[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPcoIpv6Item.aucPriDns[0]), CNAS_EHSM_IPV6_ADDR_LEN);
                pstMsg->stIpv6Dns.bitOpIpv6PrimDNS = 1;
            }

            if (1 == pstPdnInfo->stPcoIpv6Item.bitOpSecDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv6Dns.aucIpv6SecDNS[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPcoIpv6Item.aucSecDns[0]), CNAS_EHSM_IPV6_ADDR_LEN);
                pstMsg->stIpv6Dns.bitOpIpv6SecDNS = 1;
            }

            break;
        }
        default:
        {
            break;
        }
    }

    if (0 != pstPdnInfo->stApn.ucApnLen)
    {
        NAS_MEM_CPY_S(&(pstMsg->stApn.aucApn[0]), EHSM_APS_APN_MAX_LEN, &(pstPdnInfo->stApn.aucApn[0]), pstPdnInfo->stApn.ucApnLen);
        pstMsg->stApn.ulLength = pstPdnInfo->stApn.ucApnLen;
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SndApsPdnAttachCnf
 功能描述  : EHSM发送Pdn Attach Cnf至APS
 输入参数  : VOS_UINT8                           ucPdnId
             EHSM_APS_CAUSE_ENUM_UINT32          enCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月25日
    作    者   : g00261581
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SndApsPdnAttachCnf(
    VOS_UINT8                           ucPdnId,
    EHSM_APS_CAUSE_ENUM_UINT32          enCause
)
{
    EHSM_APS_PDN_ATTACH_CNF_STRU       *pstMsg     = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstPdnInfo = VOS_NULL_PTR;

    pstPdnInfo = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[ucPdnId]);

    /* Allocating memory for message */
    pstMsg = (EHSM_APS_PDN_ATTACH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                               sizeof(EHSM_APS_PDN_ATTACH_CNF_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH), 
                  (VOS_SIZE_T)(sizeof(EHSM_APS_PDN_ATTACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(EHSM_APS_PDN_ATTACH_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->enMsgId       = ID_EHSM_APS_PDN_ATTACH_CNF;

    pstMsg->enCause       = enCause;
    pstMsg->ucCid         = pstPdnInfo->ucCid;
    pstMsg->ucPdnId       = pstPdnInfo->ucPdnId;
    pstMsg->ucRabId       = (VOS_UINT8)pstPdnInfo->ulEpsbId;
    pstMsg->usMtu         = pstPdnInfo->usMtu;

    switch(pstPdnInfo->stPdnAddr.enPdnType)
    {
        case CNAS_EHSM_PDN_TYPE_IPV4:
        {
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv4Addr[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv4Addr[0]), CNAS_EHSM_IPV4_ADDR_LEN);
            pstMsg->stPdnAddr.enPdnType = EHSM_APS_PDN_TYPE_IPV4;

            if (1 == pstPdnInfo->stPcoIpv4Item.bitOpPriDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv4Dns.aucIpv4PrimDNS[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPcoIpv4Item.aucPriDns[0]), CNAS_EHSM_IPV4_ADDR_LEN);
                pstMsg->stIpv4Dns.bitOpIpv4PrimDNS = 1;
            }

            if (1 == pstPdnInfo->stPcoIpv4Item.bitOpSecDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv4Dns.aucIpv4SecDNS[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPcoIpv4Item.aucSecDns[0]), CNAS_EHSM_IPV4_ADDR_LEN);
                pstMsg->stIpv4Dns.bitOpIpv4SecDNS = 1;
            }

            break;
        }
        case CNAS_EHSM_PDN_TYPE_IPV6:
        {
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv6Addr[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv6Addr[0]), CNAS_EHSM_IPV6_ADDR_LEN);
            pstMsg->stPdnAddr.enPdnType = EHSM_APS_PDN_TYPE_IPV6;

            if (1 == pstPdnInfo->stPcoIpv6Item.bitOpPriDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv6Dns.aucIpv6PrimDNS[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPcoIpv6Item.aucPriDns[0]), CNAS_EHSM_IPV6_ADDR_LEN);
                pstMsg->stIpv6Dns.bitOpIpv6PrimDNS = 1;
            }

            if (1 == pstPdnInfo->stPcoIpv6Item.bitOpSecDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv6Dns.aucIpv6SecDNS[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPcoIpv6Item.aucSecDns[0]), CNAS_EHSM_IPV6_ADDR_LEN);
                pstMsg->stIpv6Dns.bitOpIpv6SecDNS = 1;
            }

            break;
        }
        case CNAS_EHSM_PDN_TYPE_IPV4V6:
        {
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv6Addr[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv6Addr[0]), CNAS_EHSM_IPV6_ADDR_LEN);
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv4Addr[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv4Addr[0]), CNAS_EHSM_IPV4_ADDR_LEN);
            pstMsg->stPdnAddr.enPdnType = EHSM_APS_PDN_TYPE_IPV4V6;

            if (1 == pstPdnInfo->stPcoIpv4Item.bitOpPriDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv4Dns.aucIpv4PrimDNS[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPcoIpv4Item.aucPriDns[0]), CNAS_EHSM_IPV4_ADDR_LEN);
                pstMsg->stIpv4Dns.bitOpIpv4PrimDNS = 1;
            }

            if (1 == pstPdnInfo->stPcoIpv4Item.bitOpSecDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv4Dns.aucIpv4SecDNS[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPcoIpv4Item.aucSecDns[0]), CNAS_EHSM_IPV4_ADDR_LEN);
                pstMsg->stIpv4Dns.bitOpIpv4SecDNS = 1;
            }

            if (1 == pstPdnInfo->stPcoIpv6Item.bitOpPriDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv6Dns.aucIpv6PrimDNS[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPcoIpv6Item.aucPriDns[0]), CNAS_EHSM_IPV6_ADDR_LEN);
                pstMsg->stIpv6Dns.bitOpIpv6PrimDNS = 1;
            }

            if (1 == pstPdnInfo->stPcoIpv6Item.bitOpSecDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv6Dns.aucIpv6SecDNS[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPcoIpv6Item.aucSecDns[0]), CNAS_EHSM_IPV6_ADDR_LEN);
                pstMsg->stIpv6Dns.bitOpIpv6SecDNS = 1;
            }

            break;
        }
        default:
        {
            break;
        }
    }

    if (0 != pstPdnInfo->stApn.ucApnLen)
    {
        NAS_MEM_CPY_S(&(pstMsg->stApn.aucApn[0]), EHSM_APS_APN_MAX_LEN, &(pstPdnInfo->stApn.aucApn[0]), pstPdnInfo->stApn.ucApnLen);
        pstMsg->stApn.ulLength = pstPdnInfo->stApn.ucApnLen;
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;
}


VOS_VOID CNAS_EHSM_SndApsLteHandOverToEhrpdInd(
    VOS_UINT8                           ucPdnId,
    EHSM_APS_PDN_OPTION_ENUM_UINT32     enPdnOption
)
{
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU       *pstMsg = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU            *pstPdnInfo = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                               sizeof(EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH), 
                  (VOS_SIZE_T)(sizeof(EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->enMsgId             = ID_EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND;
    pstPdnInfo = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[ucPdnId]);

    pstMsg->ucCid   = pstPdnInfo->ucCid;
    pstMsg->ucPdnId = pstPdnInfo->ucPdnId;
    pstMsg->ucRabId = (VOS_UINT8)pstPdnInfo->ulEpsbId;
    pstMsg->usMtu   = pstPdnInfo->usMtu;
    pstMsg->enPdnOption = enPdnOption;

    switch(pstPdnInfo->stPdnAddr.enPdnType)
    {
        case CNAS_EHSM_PDN_TYPE_IPV4:
        {
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv4Addr[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv4Addr[0]), CNAS_EHSM_IPV4_ADDR_LEN);
            pstMsg->stPdnAddr.enPdnType = EHSM_APS_PDN_TYPE_IPV4;
            break;
        }
        case CNAS_EHSM_PDN_TYPE_IPV6:
        {
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv6Addr[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv6Addr[0]), CNAS_EHSM_IPV6_ADDR_LEN);
            pstMsg->stPdnAddr.enPdnType = EHSM_APS_PDN_TYPE_IPV6;
            break;
        }
        case CNAS_EHSM_PDN_TYPE_IPV4V6:
        {
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv6Addr[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv6Addr[0]), CNAS_EHSM_IPV6_ADDR_LEN);
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv4Addr[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv4Addr[0]), CNAS_EHSM_IPV4_ADDR_LEN);
            pstMsg->stPdnAddr.enPdnType = EHSM_APS_PDN_TYPE_IPV4V6;
            break;
        }
        default:
        {
            break;
        }
    }
    if (0 != pstPdnInfo->stApn.ucApnLen)
    {
        NAS_MEM_CPY_S(&(pstMsg->stApn.aucApn[0]), EHSM_APS_APN_MAX_LEN, &(pstPdnInfo->stApn.aucApn[0]), pstPdnInfo->stApn.ucApnLen);
        pstMsg->stApn.ulLength = pstPdnInfo->stApn.ucApnLen;
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;

}


VOS_VOID CNAS_EHSM_SndApsPdnActivateCnf(
    VOS_UINT8                           ucCid,
    EHSM_APS_CAUSE_ENUM_UINT32          enCause
)
{
    EHSM_APS_PDN_ACTIVATE_CNF_STRU     *pstMsg = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstPdnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulIsPdnIdValid;
    VOS_UINT8                           ucPdnId;

    /* Allocating memory for message */
    pstMsg = (EHSM_APS_PDN_ACTIVATE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                               sizeof(EHSM_APS_PDN_ACTIVATE_CNF_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH), 
                  (VOS_SIZE_T)(sizeof(EHSM_APS_PDN_ACTIVATE_CNF_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(EHSM_APS_PDN_ACTIVATE_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->enMsgId             = ID_EHSM_APS_PDN_ACTIVATE_CNF;

    ucPdnId = CNAS_EHSM_GetPdnIdByCid(ucCid);

    if (0 != ucPdnId)
    {
        CNAS_INFO_LOG(UEPS_PID_EHSM, "CNAS_EHSM_SndApsPdnActivateCnf: PDN ID != 0");
    }

    pstMsg->ucCid               = ucCid;
    pstMsg->enCause             = enCause;

    ulIsPdnIdValid = CNAS_EHSM_IsPdnActived(ucPdnId);

    if ((EHSM_APS_CAUSE_SUCCESS == enCause)
        && (VOS_TRUE == ulIsPdnIdValid))
    {
        pstPdnInfo = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[ucPdnId]);
        pstMsg->ucPdnId             = ucPdnId;
        pstMsg->ucRabId             = (VOS_UINT8)pstPdnInfo->ulEpsbId;

        /* pdn address */
        if ((EHSM_ESM_PDN_TYPE_IPV4 == pstPdnInfo->stPdnAddr.enPdnType)
         || (EHSM_ESM_PDN_TYPE_IPV4V6 == pstPdnInfo->stPdnAddr.enPdnType))
        {
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv4Addr[0]), EHSM_APS_IPV4_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv4Addr[0]), CNAS_EHSM_IPV4_ADDR_LEN);
            pstMsg->stPdnAddr.enPdnType = CNAS_EHSM_MapEhsmPdnTypeToAps(pstPdnInfo->stPdnAddr.enPdnType);

            if (1 == pstPdnInfo->stPcoIpv4Item.bitOpPriDns)
            {
                NAS_MEM_CPY_S(pstMsg->stIpv4Dns.aucIpv4PrimDNS, EHSM_APS_IPV4_ADDR_LEN, pstPdnInfo->stPcoIpv4Item.aucPriDns, CNAS_EHSM_IPV4_ADDR_LEN);
                pstMsg->stIpv4Dns.bitOpIpv4PrimDNS = 1;
            }

            if (1 == pstPdnInfo->stPcoIpv4Item.bitOpSecDns)
            {
                NAS_MEM_CPY_S(pstMsg->stIpv4Dns.aucIpv4SecDNS, EHSM_APS_IPV4_ADDR_LEN, pstPdnInfo->stPcoIpv4Item.aucSecDns, CNAS_EHSM_IPV4_ADDR_LEN);
                pstMsg->stIpv4Dns.bitOpIpv4SecDNS = 1;
            }
        }

        if ((EHSM_ESM_PDN_TYPE_IPV6 == pstPdnInfo->stPdnAddr.enPdnType)
         || (EHSM_ESM_PDN_TYPE_IPV4V6 == pstPdnInfo->stPdnAddr.enPdnType))
        {
            NAS_MEM_CPY_S(&(pstMsg->stPdnAddr.aucIpv6Addr[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPdnAddr.aucIpv6Addr[0]), CNAS_EHSM_IPV6_ADDR_LEN);
            pstMsg->stPdnAddr.enPdnType = CNAS_EHSM_MapEhsmPdnTypeToAps(pstPdnInfo->stPdnAddr.enPdnType);

            if (1 == pstPdnInfo->stPcoIpv6Item.bitOpPriDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv6Dns.aucIpv6PrimDNS[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPcoIpv6Item.aucPriDns[0]), CNAS_EHSM_IPV6_ADDR_LEN);
                pstMsg->stIpv6Dns.bitOpIpv6PrimDNS = 1;
            }

            if (1 == pstPdnInfo->stPcoIpv6Item.bitOpSecDns)
            {
                NAS_MEM_CPY_S(&(pstMsg->stIpv6Dns.aucIpv6SecDNS[0]), EHSM_APS_IPV6_ADDR_LEN, &(pstPdnInfo->stPcoIpv6Item.aucSecDns[0]), CNAS_EHSM_IPV6_ADDR_LEN);
                pstMsg->stIpv6Dns.bitOpIpv6SecDNS = 1;
            }
        }

        /* apn info */
        if (0 != pstPdnInfo->stApn.ucApnLen)
        {
            NAS_MEM_CPY_S(&(pstMsg->stApn.aucApn[0]), EHSM_APS_APN_MAX_LEN, &(pstPdnInfo->stApn.aucApn[0]), pstPdnInfo->stApn.ucApnLen);
            pstMsg->stApn.ulLength = pstPdnInfo->stApn.ucApnLen;
        }
    }
    else
    {
        pstMsg->ucPdnId = 0xFF;
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;
}


VOS_VOID CNAS_EHSM_SndApsPdnDeactivateCnf(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucCid,
    VOS_UINT32                          enCause
)
{
    EHSM_APS_PDN_DEACTIVATE_CNF_STRU                       *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (EHSM_APS_PDN_DEACTIVATE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                               sizeof(EHSM_APS_PDN_DEACTIVATE_CNF_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(EHSM_APS_PDN_DEACTIVATE_CNF_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(EHSM_APS_PDN_DEACTIVATE_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->enMsgId             = ID_EHSM_APS_PDN_DEACTIVATE_CNF;
    pstMsg->enCause             = enCause;
    pstMsg->ucCid               = ucCid;
    pstMsg->ucPdnId             = ucPdnId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : CNAS_EHSM_SndApsPdnDeactivateInd
 功能描述  : pdn deactivate msg indecate to aps
 输入参数  : ulPdnId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月21日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SndApsPdnDeactivateInd(
    VOS_UINT8                   ucPdnId,
    VOS_UINT8                   ucCid,
    VOS_UINT32                  enCause
)
{
    EHSM_APS_PDN_DEACTIVATE_IND_STRU                       *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (EHSM_APS_PDN_DEACTIVATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                               sizeof(EHSM_APS_PDN_DEACTIVATE_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(EHSM_APS_PDN_DEACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(EHSM_APS_PDN_DEACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->enMsgId             = ID_EHSM_APS_PDN_DEACTIVATE_IND;
    pstMsg->enCause             = enCause;
    pstMsg->ucCid               = ucCid;
    pstMsg->ucPdnId             = ucPdnId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;

}




VOS_VOID CNAS_EHSM_SndApsReconnCnf(
    EHSM_APS_CAUSE_ENUM_UINT32          enCause,
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucCid
)
{
    EHSM_APS_RECONN_CNF_STRU           *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (EHSM_APS_RECONN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                               sizeof(EHSM_APS_RECONN_CNF_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(EHSM_APS_RECONN_CNF_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(EHSM_APS_RECONN_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->enMsgId             = ID_EHSM_APS_RECONN_CNF;
    pstMsg->enCause             = enCause;
    pstMsg->ucPdnId             = ucPdnId;
    pstMsg->ucCid               = ucCid;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_GetCdataServiceStatus
 功能描述  : tell aps the Cdate service status according the pdnid
 输入参数  : ucPdnId
 输出参数  : 无
 返 回 值  : EHSM_APS_PDN_STATUS_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月30日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
EHSM_APS_PDN_STATUS_ENUM_UINT32 CNAS_EHSM_GetCdataServiceStatus(
    VOS_UINT8                           ucPdnId
)
{
    CNAS_EHSM_EHRPD_STA_ENUM_UINT32     enState;

    enState = CNAS_EHSM_GetEhrpdState();
    switch (enState)
    {
        case CNAS_EHSM_EHRPD_INACTIVE_STA:
            return EHSM_APS_PDN_STATUS_INACTIVE;

        case CNAS_EHSM_EHRPD_ACTIVE_STA:

            if (VOS_FALSE == CNAS_EHSM_IsPdnActived(ucPdnId))
            {
                return EHSM_APS_PDN_STATUS_SUSPEND;
            }
            else
            {
                return EHSM_APS_PDN_STATUS_ACTIVE;
            }
        case CNAS_EHSM_EHRPD_DORMANT_STA:
            return EHSM_APS_PDN_STATUS_DORMANT;

        case CNAS_EHSM_EHRPD_SUSPEND_STA:
            return EHSM_APS_PDN_STATUS_SUSPEND;

        default:
            return EHSM_APS_PDN_STATUS_INACTIVE;
    }
}
/*****************************************************************************
 函 数 名  : CNAS_EHSM_SndApsPdnChgInd
 功能描述  : pdn 信息发生变更上报给aps
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月7日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_EHSM_SndApsPdnChgInd(
    EHSM_APS_PDN_CHANGE_INFO_STRU      *pstPdnChgInfo,
    VOS_UINT8                           ucPdnId
)
{
    EHSM_APS_PDN_INFO_CHANGE_IND_STRU  *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (EHSM_APS_PDN_INFO_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                               sizeof(EHSM_APS_PDN_INFO_CHANGE_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(EHSM_APS_PDN_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(EHSM_APS_PDN_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_TAF);
    pstMsg->enMsgId             = ID_EHSM_APS_PDN_INFO_CHANGE_IND;
    pstMsg->usOpId              = 0;
    pstMsg->ucCid               = CNAS_EHSM_GetCidByPdnId(ucPdnId);
    NAS_MEM_CPY_S(&pstMsg->stPdnChgInfo, sizeof(EHSM_APS_PDN_CHANGE_INFO_STRU), pstPdnChgInfo, sizeof(EHSM_APS_PDN_CHANGE_INFO_STRU));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;
}

#endif /* FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


