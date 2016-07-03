/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmSndPpp.c
 Author          :
 Version         :
 Date            :   14/05/2015
 Description     :   EHSM module Sends messages to PPP process file.
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
#include "CnasEhsmEncode.h"
#include "CnasMntn.h"
/* To Do: Need to add EHSM to PPP interface file */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_SND_PPP_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  3 Function Define
*****************************************************************************/
/*lint -save -e958*/

/* To Do: Need to write deifinitions of all functions to send message is PPP */

VOS_VOID CNAS_EHSM_SndCttfEhrpdPdnConnReq(
    VOS_UINT8                           ucPdnId
)
{
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU  *pstMsg              = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstLocalPdnBearInfo = VOS_NULL_PTR;
    CNAS_EHSM_LTE_PDN_BEAR_INFO_STRU   *pstLtePdnInfo       = VOS_NULL_PTR;
    CNAS_EHSM_PDN_ADDR_STRU            *pstPdnAddr          = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* Allocating memory for message */
    pstMsg = (CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                                  sizeof(CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstLocalPdnBearInfo = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[ucPdnId]);
    pstLtePdnInfo       = &(CNAS_EHSM_GetEhsmCtxAddr()->astLtePdnBearInfo[ucPdnId]);

    pstMsg->ulReceiverPid       = MSPS_PID_PPPC;
    pstMsg->enMsgId             = ID_CNAS_CTTF_EHRPD_PDN_CONN_REQ;
    pstMsg->ucPdnId             = ucPdnId;

    /* aucIpv4DefaultRouterAddress  */
    NAS_MEM_SET_S(&(pstMsg->aucIpv4DefaultRouterAddress[0]), CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN, 0, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    /* 对应ID_APS_EHSM_PDN_ACTIVATE_REQ 的场景 */
    if (VOS_FALSE == pstLtePdnInfo->ucInUsed)
    {
        NAS_MEM_SET_S(&(pstMsg->stPdnAddress.aucAddress[0]),
                      CNAS_CTTF_EHRPD_PDN_ADDRESS_LEN,
                      0x00,
                      CNAS_CTTF_EHRPD_PDN_ADDRESS_LEN);

        /*
            For default APN connection setup, if the default APN is not known to the UE, then the UE shall set the APN using
            a zero length APN Network Identifier as the APN name (see TS 23.003 [19]). When the HSGW receives a VSNCP Configure-Request
            message indicating a zero length APN, then the HSGW shall set the APN in the PBU message to the default APN value that
            is contained in the subscription data for the user, unless the HSGW also receives the Emergency Indicator configuration
            option with the value set to 1. If the HSGW receives a VSNCP Configure-Request message with the Emergency Indicator
            configuration option with the value set to 1, then the HSGW shall set the APN in the PBU message to the emergency APN value
            contained in the HSGW Emergency Configuration Data, and the APN supplied in the VSNCP Configure-Request is ignored by the HSGW.
         */

        /* apn */
        pstMsg->stApn.ucApnLen = pstLocalPdnBearInfo->stApn.ucApnLen;
        NAS_MEM_CPY_S(pstMsg->stApn.aucApn, CNAS_CTTF_EHRPD_MAX_APN_LEN, pstLocalPdnBearInfo->stApn.aucApn, pstMsg->stApn.ucApnLen);

        /* ucAttachType  */
        pstMsg->enAttachType = CNAS_CTTF_EHRPD_ATTACH_TYPE_INITIAL;

        /* enPdnType  */
        pstMsg->stPdnAddress.enPdnType = CNAS_CTTF_EHRPD_PDN_TYPE_INVALID;
        pstMsg->enPdnType = pstLocalPdnBearInfo->enPdnType;

        pstPdnAddr = &(pstLocalPdnBearInfo->stPdnAddr);
    }
    else
    {
        /* 对应ID_CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ 的场景 */

        /* aucIpv4DefaultRouterAddress todo */

        /* ucAttachType  */
        pstMsg->enAttachType = CNAS_CTTF_EHRPD_ATTACH_TYPE_HANDOVER;

        /* apn */
        pstMsg->stApn.ucApnLen = pstLtePdnInfo->stApn.ucApnLen;
        NAS_MEM_CPY_S(pstMsg->stApn.aucApn, CNAS_CTTF_EHRPD_MAX_APN_LEN, pstLtePdnInfo->stApn.aucApn, pstMsg->stApn.ucApnLen);

        /* pco 需要对 stPcoIpv4Item 和 stPcoIpv6Item进行编码 */

        pstMsg->stPdnAddress.enPdnType = CNAS_EHSM_MapEhsmPdnTypeToCttf(pstLtePdnInfo->stPdnAddr.enPdnType);
        pstMsg->enPdnType = CNAS_EHSM_MapEhsmPdnTypeToCttf(pstLtePdnInfo->enPdnType);

        pstPdnAddr = &(pstLtePdnInfo->stPdnAddr);
    }

    /* ucAddressAllocCause  */
    pstMsg->ucAddressAllocCause = CNAS_CTTF_EHRPD_AddRESS_ALLOC_CAUSE_REQ;

    /* pco encode */
    ulLength = 0;
    if(CNAS_EHSM_FAILURE == CNAS_EHSM_EncodePco(pstMsg->enPdnType, ucPdnId,
                                                pstMsg->stPco.aucPco, &ulLength))
    {
         /*打印异常信息*/
        pstMsg->stPco.ucPcoLen = (VOS_UINT8)ulLength;
        PS_FREE_MSG(UEPS_PID_EHSM, pstMsg);
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodePco:fail ");
        return;
    }
    pstMsg->stPco.ucPcoLen = (VOS_UINT8)ulLength;

    /* pdn address encode  if the attah type is "handoff",IP address(es) assigned for the PDN shall be set in the
        the value field  refer to 9.1.4.2 of X.S0057
    */
    if(CNAS_EHSM_SUCCESS != CNAS_EHSM_EncodeNwPDNValue(pstPdnAddr, &(pstMsg->stPdnAddress)))
    {
         /*打印异常信息*/
        PS_FREE_MSG(UEPS_PID_EHSM, pstMsg);
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodeNwPDNValue:fail ");
        return;
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;
}


VOS_VOID CNAS_EHSM_SndCttfEhrpdAttachReq(
    VOS_UINT8                                       ucPdnId,
    CNAS_EHSM_ATTACH_REASON_ENUM_UINT32             enAttachReason
)
{
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstMsg              = VOS_NULL_PTR;
    CNAS_EHSM_LTE_PDN_BEAR_INFO_STRU   *pstLtePdnInfo       = VOS_NULL_PTR;
    CNAS_EHSM_PDN_ADDR_STRU            *pstPdnAddr          = VOS_NULL_PTR;
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstLocalPdnBearInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength            = 0;
    pstLocalPdnBearInfo = &(CNAS_EHSM_GetEhsmCtxAddr()->astLocalPdnBearInfo[ucPdnId]);

    /* Allocating memory for message */
    pstMsg = (CNAS_CTTF_EHRPD_ATTACH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                                  sizeof(CNAS_CTTF_EHRPD_ATTACH_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = MSPS_PID_PPPC;
    pstMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid         = UEPS_PID_EHSM;
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->enMsgId             = ID_CNAS_CTTF_EHRPD_ATTACH_REQ;
    pstMsg->ucPdnId             = ucPdnId;
    pstMsg->ucAddressAllocCause = CNAS_CTTF_EHRPD_AddRESS_ALLOC_CAUSE_REQ;
    pstMsg->enModemId           = CNAS_CCB_GetCdmaModeModemId();

    switch (enAttachReason)
    {
        case CNAS_EHSM_ATTACH_REASON_INITIAL_ATTACH:
        {
            pstMsg->enAttachType = CNAS_CTTF_EHRPD_ATTACH_TYPE_INITIAL;

            /* the PDN Address configuration option shall have a value 0,if the Attach Type is "Initial Attach"
                 refer to 9.1.4.2 of X.S0057
             */
            NAS_MEM_SET_S(&(pstMsg->stPdnAddress),
                          (sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU)),
                          0x00,
                          (sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU)));

            pstMsg->stPdnAddress.enPdnType = CNAS_CTTF_EHRPD_PDN_TYPE_INVALID;

            pstMsg->enPdnType = CNAS_EHSM_MapEhsmPdnTypeToCttf(pstLocalPdnBearInfo->enPdnType);

            /*
                For default APN connection setup, if the default APN is not known to the UE, then the UE shall set the APN using
                a zero length APN Network Identifier as the APN name (see TS 23.003 [19]). When the HSGW receives a VSNCP Configure-Request
                message indicating a zero length APN, then the HSGW shall set the APN in the PBU message to the default APN value that
                is contained in the subscription data for the user, unless the HSGW also receives the Emergency Indicator configuration
                option with the value set to 1. If the HSGW receives a VSNCP Configure-Request message with the Emergency Indicator
                configuration option with the value set to 1, then the HSGW shall set the APN in the PBU message to the emergency APN value
                contained in the HSGW Emergency Configuration Data, and the APN supplied in the VSNCP Configure-Request is ignored by the HSGW.
             */

            /* apn */
            pstMsg->stApn.ucApnLen = pstLocalPdnBearInfo->stApn.ucApnLen;
            NAS_MEM_CPY_S(pstMsg->stApn.aucApn, CNAS_CTTF_EHRPD_MAX_APN_LEN, pstLocalPdnBearInfo->stApn.aucApn, pstMsg->stApn.ucApnLen);

            NAS_MEM_SET_S(&(pstMsg->aucIpv4DefaultRouterAddress[0]), CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN, 0, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);
        }
        break;

        case CNAS_EHSM_ATTACH_REASON_HANDOVER_ATTACH:
        {
            pstLtePdnInfo  = &(CNAS_EHSM_GetEhsmCtxAddr()->astLtePdnBearInfo[ucPdnId]);

            pstMsg->enAttachType = CNAS_CTTF_EHRPD_ATTACH_TYPE_HANDOVER;
            pstMsg->enPdnType    = pstLtePdnInfo->enPdnType;
            pstMsg->stPdnAddress.enPdnType = CNAS_CTTF_EHRPD_PDN_TYPE_INVALID;

            /* APN */
            pstMsg->stApn.ucApnLen = pstLtePdnInfo->stApn.ucApnLen;
            NAS_MEM_CPY_S(pstMsg->stApn.aucApn, CNAS_CTTF_EHRPD_MAX_APN_LEN, pstLtePdnInfo->stApn.aucApn, pstMsg->stApn.ucApnLen);

            /* ROUTER ADDRESS */
            NAS_MEM_SET_S(&(pstMsg->aucIpv4DefaultRouterAddress[0]), CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN, 0, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

            pstPdnAddr = &(pstLtePdnInfo->stPdnAddr);

            /* pdn address encode  if the attah type is "handoff",IP address(es) assigned for the PDN shall be set in the
               the value field  refer to 9.1.4.2 of X.S0057
             */
            if(CNAS_EHSM_SUCCESS != CNAS_EHSM_EncodeNwPDNValue(pstPdnAddr, &(pstMsg->stPdnAddress)))
            {
                 /*打印异常信息*/
                PS_FREE_MSG(UEPS_PID_EHSM, pstMsg);
                CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodeNwPDNValue:fail ");
                return;
            }

            pstMsg->enPdnType = CNAS_EHSM_MapEhsmPdnTypeToCttf(pstLtePdnInfo->enPdnType);
        }
        break;

        default:
            PS_FREE_MSG(UEPS_PID_EHSM, pstMsg);
            CNAS_WARNING_LOG1(UEPS_PID_EHSM, "CNAS_EHSM_SndCttfEhrpdAttachReq:Wrong Reason: ", enAttachReason);
            return;
    }

    /* pco encode */
    if(CNAS_EHSM_FAILURE == CNAS_EHSM_EncodePco(pstMsg->enPdnType, ucPdnId,
                                                pstMsg->stPco.aucPco, &ulLength))
    {
         /*打印异常信息*/
        pstMsg->stPco.ucPcoLen = (VOS_UINT8)ulLength;
        PS_FREE_MSG(UEPS_PID_EHSM, pstMsg);
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_EncodePco:fail ");
        return;
    }
    pstMsg->stPco.ucPcoLen = (VOS_UINT8)ulLength;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;
}



VOS_VOID CNAS_EHSM_SndCttfEhrpdPdnDiscReq(
    VOS_UINT8                           ucPdnId
)
{
    CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU  *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                                  sizeof(CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = MSPS_PID_PPPC;
    pstMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid         = UEPS_PID_EHSM;
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->enMsgId             = ID_CNAS_CTTF_EHRPD_PDN_DISC_REQ;
    pstMsg->ucPdnId             = ucPdnId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;
}


VOS_VOID CNAS_EHSM_SndCttfEhrpdDetachReq(
    VOS_VOID
)
{
    CNAS_CTTF_EHRPD_DETACH_REQ_STRU    *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (CNAS_CTTF_EHRPD_DETACH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                                sizeof(CNAS_CTTF_EHRPD_DETACH_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = MSPS_PID_PPPC;
    pstMsg->enMsgId             = ID_CNAS_CTTF_EHRPD_DETACH_REQ;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;
}

VOS_VOID CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(
    VOS_UINT8                ucPdnId
)
{
    CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU        *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                                sizeof(CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = MSPS_PID_PPPC;
    pstMsg->enMsgId             = ID_CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND;
    pstMsg->ucPdnId             = ucPdnId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;
}


VOS_VOID CNAS_EHSM_SndCttfEhrpdDetachInd(
    VOS_VOID
)
{
    CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU     *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                                sizeof(CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = MSPS_PID_PPPC;
    pstMsg->enMsgId             = ID_CNAS_CTTF_EHRPD_LOC_DETACH_IND;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return ;
}


VOS_VOID CNAS_EHSM_SndCttfEhrpdLinkStatusNotify(
    CNAS_CTTF_EHRPD_LINK_STATUS_ENUM_UINT8                  enLinkStatus
)
{
    CNAS_CTTF_EHRPD_LINK_STATUS_NTF_STRU                   *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (CNAS_CTTF_EHRPD_LINK_STATUS_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                                     sizeof(CNAS_CTTF_EHRPD_LINK_STATUS_NTF_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_LINK_STATUS_NTF_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(CNAS_CTTF_EHRPD_LINK_STATUS_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid       = MSPS_PID_PPPC;
    pstMsg->enMsgId             = ID_CNAS_CTTF_EHRPD_LINK_STATUS_NTF;

    pstMsg->enLinkStatus        = enLinkStatus;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return ;
}


CNAS_CTTF_EHRPD_LINK_STATUS_ENUM_UINT8 CNAS_EHSM_GetPdnLinkStatus(VOS_VOID)
{
    if (VOS_TRUE == CNAS_EHSM_GetAirLinkExistFlag())
    {
        return CNAS_CTTF_EHRPD_LINK_CONNECTED;
    }
    else
    {
        return CNAS_CTTF_EHRPD_LINK_NOT_EXISTED;
    }
}

/*lint -restore*/

#endif /* FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



