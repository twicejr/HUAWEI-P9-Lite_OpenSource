/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmSndInternalMsg.c
 Author          :
 Version         :
 Date            :   14/05/2015
 Description     :   EHSM module Sends internal messages.
 Function list   :
 History         :
     1) Date :
        Author:
        Modification:
********************************************************************************/

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmSndInternalMsg.h"
#include "CnasEhsmCtx.h"
#include "CnasEhsmMntn.h"
/* To Do: Need to add required EHSM to internal message file */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_SND_INTERNAL_MSG_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  3 Function Define
*****************************************************************************/
/*lint -save -e958 -e429 -e830 */

VOS_VOID CNAS_EHSM_SndActivatingRslt(
    VOS_UINT32                          ulResult,
    VOS_UINT8                           ucIsPermanentFail
)
{
    CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF_STRU                *pstMsg = VOS_NULL_PTR;

    /* Alloc the memory for Switch On result Message */
    pstMsg  = (CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_EHSM,
                                                            sizeof(CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF_STRU));

    /* Return if malloc fails */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* Construct the internal message */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_EHSM;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_EHSM;
    pstMsg->enMsgId                     = ID_CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF;
    pstMsg->ulLength                    = sizeof(CNAS_EHSM_EHSM_ACTIVATING_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enRslt                      = ulResult;
    pstMsg->ucIsPermanentFail           = ucIsPermanentFail;

    CNAS_EHSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

}



VOS_VOID CNAS_EHSM_SndInternalAttachReq(
    CNAS_EHSM_ATTACH_REASON_ENUM_UINT32                 enAttachReason
)
{
    CNAS_EHSM_EHSM_ATTACH_REQ_STRU                *pstMsg = VOS_NULL_PTR;

    /* Alloc the memory for Handover attach Message */
    pstMsg  = (CNAS_EHSM_EHSM_ATTACH_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_EHSM,
                                                            sizeof(CNAS_EHSM_EHSM_ATTACH_REQ_STRU));

    /* Return if malloc fails */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* Construct the internal message */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_EHSM;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_EHSM;
    pstMsg->enMsgId                     = ID_CNAS_EHSM_EHSM_ATTACH_REQ;
    pstMsg->ulLength                    = sizeof(CNAS_EHSM_EHSM_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enAttachReason              = enAttachReason;

    CNAS_EHSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

}


/*****************************************************************************
 函 数 名  : CNAS_EHSM_SndDeactivatingRslt
 功能描述  : send internal msg about deactivating result
 输入参数  : ulResult
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
Modify History  :
1)  Date           : 2015-05-18
    Author         : y00322978
    Modify content : Create
*****************************************************************************/
VOS_VOID CNAS_EHSM_SndDeactivatingRslt(VOS_VOID)
{
    CNAS_EHSM_EHSM_DEACTIVATING_RSLT_CNF_STRU              *pstMsg = VOS_NULL_PTR;
    /* Alloc the memory for Deactivating result Message */
    pstMsg  = (CNAS_EHSM_EHSM_DEACTIVATING_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_EHSM,
                                                            sizeof(CNAS_EHSM_EHSM_DEACTIVATING_RSLT_CNF_STRU));

    /* Return if malloc fails */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }
    NAS_MEM_SET_S(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                  (VOS_SIZE_T)(sizeof(CNAS_EHSM_EHSM_DEACTIVATING_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH),
                  0x00,
                  (VOS_SIZE_T)(sizeof(CNAS_EHSM_EHSM_DEACTIVATING_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* Construct the internal message */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_EHSM;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_EHSM;
    pstMsg->enMsgId                     = ID_CNAS_EHSM_EHSM_DEACTIVATING_RSLT_CNF;
    pstMsg->ulLength                    = sizeof(CNAS_EHSM_EHSM_DEACTIVATING_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    CNAS_EHSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

}



VOS_VOID CNAS_EHSM_SndPdnSetupReq(
    VOS_UINT32                          ulLtePdnIndex
)
{
    CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ_STRU               *pstMsg = VOS_NULL_PTR;

    /* Alloc the memory for pdn setup req Message */
    pstMsg  = (CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_EHSM,
                                                            sizeof(CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ_STRU));

    /* Return if malloc fails */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* Construct the internal message */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_EHSM;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_EHSM;
    pstMsg->enMsgId                     = ID_CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ;
    pstMsg->ulLength                    = sizeof(CNAS_EHSM_EHSM_PDN_RE_ESTABLISH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulLtePdnIndex               = ulLtePdnIndex;

    CNAS_EHSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

}


VOS_VOID CNAS_EHSM_SndInternalAbortReq(
    VOS_UINT32                          ulEventType
)
{
    CNAS_EHSM_EHSM_ABORT_REQ_STRU  *pstMsg = VOS_NULL_PTR;

    /* Alloc the memory for pdn setup req Message */
    pstMsg  = (CNAS_EHSM_EHSM_ABORT_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_EHSM,
                                                            sizeof(CNAS_EHSM_EHSM_ABORT_REQ_STRU));

    /* Return if malloc fails */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* Construct the internal message */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_EHSM;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_EHSM;
    pstMsg->enMsgId                     = ID_CNAS_EHSM_EHSM_ABORT_REQ;
    pstMsg->ulLength                    = sizeof(CNAS_EHSM_EHSM_ABORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulEventType                 = ulEventType;

    CNAS_EHSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

}


VOS_VOID CNAS_EHSM_SndLocalDetachAllReq(
    EHSM_APS_CAUSE_ENUM_UINT32                  enCause
)
{
    CNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    /* Alloc the memory for pdn setup req Message */
    pstMsg  = (CNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_EHSM,
                                                            sizeof(CNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ_STRU));

    /* Return if malloc fails */
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* Construct the internal message */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_EHSM;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_EHSM;
    pstMsg->enMsgId                     = ID_CNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ;
    pstMsg->ulLength                    = sizeof(CNAS_EHSM_EHSM_LOCAL_DETACH_ALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enCause                     = enCause;

    CNAS_EHSM_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

}



#endif /* FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



