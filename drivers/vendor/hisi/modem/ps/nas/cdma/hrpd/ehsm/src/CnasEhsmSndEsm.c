/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmSndEsm.c
 Author          :
 Version         :
 Date            :   14/05/2015
 Description     :   EHSM module Sends messages to ESM process file.
 Function list   :
 History         :
     1) Date :
        Author:
        Modification:
********************************************************************************/

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmSndEsm.h"
#include "CnasEhsmCtx.h"
#include "CnasEhsmMntn.h"
#include "ehsm_esm_pif.h"

/* To Do: Need to add EHSM to ESM interface file */
#include "CnasMntn.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_SND_ESM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  3 Function Define
*****************************************************************************/

/* To Do: Need to write deifinitions of all functions to send message is ESM */
/*****************************************************************************
Function Name   :   CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd
Description     :   Sends message ID_EHSM_ESM_SYNC_PDN_INFO_IND to ESM.
Input parameters:   VOS_VOID
Output parameters:  None
Return Value    :   VOS_VOID

Modify History  :
1)  Date           : 2015-05-14
    Author         : y00322978
    Modify content : Create

2.  日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity
3.  日    期   : 2015年12月24日
    作    者   : w00242748
    修改内容   : DTS2015121805249:副卡支持EHRPD
*****************************************************************************/
VOS_VOID CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd(
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstPdnInfo,
    VOS_UINT32                          ulAttachFlag,
    EHSM_ESM_PDN_OPTION_ENUM_UINT32     enPdnOption
)
{
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pstMsg     = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (EHSM_ESM_SYNC_PDN_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                               sizeof(EHSM_ESM_SYNC_PDN_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(EHSM_ESM_SYNC_PDN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(EHSM_ESM_SYNC_PDN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid               = PS_PID_ESM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_EHSM;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->enMsgId                     = ID_EHSM_ESM_SYNC_PDN_INFO_IND;
    pstMsg->enPdnOption                 = enPdnOption;
    pstMsg->ulAttachFlag                = ulAttachFlag;
    pstMsg->ulBitCid                    = ((VOS_UINT32)0x00000001) << (pstPdnInfo->ucCid);
    pstMsg->ulEpsbId                    = pstPdnInfo->ulEpsbId;

    /*if the enPdnOption is disconnect,no need to cpy other para*/
    if (EHSM_ESM_PDN_OPT_DISCONNECTED != enPdnOption)
    {
        /* set apn info */
        if (pstPdnInfo->stApn.ucApnLen > 0)
        {
            NAS_MEM_CPY_S(&(pstMsg->stApn), sizeof(EHSM_ESM_APN_STRU), &(pstPdnInfo->stApn), sizeof(EHSM_APS_APN_STRU));
            pstMsg->bitOpApn = 1;
        }

        /*  apn ambr info */
        CNAS_EHSM_FillApnAmbrInfoForSyncPndInfoInd(pstMsg, &(pstPdnInfo->stApnAmbr));

        /* fill pdn address info */
        CNAS_EHSM_FillPdnAddrInfoForSyncPndInfoInd(pstMsg, &(pstPdnInfo->stPdnAddr));

        /* pco */
        CNAS_EHSM_FillPcoInfoForSyncPndInfoInd(pstMsg, &(pstPdnInfo->stPcoIpv4Item), &(pstPdnInfo->stPcoIpv6Item));

    }

    /* modem1不支持LTE，不给ESM发送消息 */
    if (MODEM_ID_0 != CNAS_CCB_GetCdmaModeModemId())
    {
        PS_FREE_MSG(UEPS_PID_EHSM, pstMsg);
        return;
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_EHSM, pstMsg);

    return;
}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_SndEsmClearAllNtf
 功能描述  : bear info clear all notify LANS
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : y00322978
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity
  3.日    期   : 2015年12月24日
    作    者   : w00242748
    修改内容   : DTS2015121805249:副卡支持EHRPD
*****************************************************************************/
VOS_VOID CNAS_EHSM_SndEsmClearAllNtf(VOS_VOID)
{
    EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY_STRU        *pstMsg;

    /* Allocating memory for message */
    pstMsg = (EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_EHSM,
                                               sizeof(EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->ulReceiverPid               = PS_PID_ESM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_EHSM;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;

    pstMsg->enMsgId             = ID_EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY;

    /* modem1不支持LTE，不给ESM发送消息 */
    if (MODEM_ID_0 != CNAS_CCB_GetCdmaModeModemId())
    {
        PS_FREE_MSG(UEPS_PID_EHSM, pstMsg);
        return;
    }

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



