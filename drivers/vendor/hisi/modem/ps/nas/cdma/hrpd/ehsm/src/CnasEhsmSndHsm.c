/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmSndHsm.c
 Author          :
 Version         :
 Date            :   14/05/2015
 Description     :   EHSM module Sends messages to HSM process file.
 Function list   :
 History         :
     1) Date :
        Author:
        Modification:
********************************************************************************/

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmSndHsm.h"
#include "CnasEhsmCtx.h"
#include "CnasEhsmMntn.h"
#include "ehsm_hsm_pif.h"
#include "CnasMain.h"

/* To Do: Need to add EHSM to HSM interface file */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_SND_HSM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  3 Function Define
*****************************************************************************/

/* To Do: Need to write deifinitions of all functions to send message is HSM */

VOS_VOID CNAS_EHSM_SndHsmConnEstReq(
    VOS_VOID
)
{
    EHSM_HSM_CONN_EST_REQ_STRU         *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (EHSM_HSM_CONN_EST_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_EHSM,
                                           sizeof(EHSM_HSM_CONN_EST_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 
                  sizeof(EHSM_HSM_CONN_EST_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(EHSM_HSM_CONN_EST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulSenderPid         = UEPS_PID_EHSM;
    pstMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid       = UEPS_PID_HSM;
    pstMsg->ulLength            = sizeof(EHSM_HSM_CONN_EST_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId             = ID_EHSM_HSM_CONN_EST_REQ;

    CNAS_SndInternalMsg(pstMsg);

    return;
}


VOS_VOID CNAS_EHSM_SndHsmEhrpdNotAvailableInd(
    VOS_VOID
)
{
    EHSM_HSM_EHRPD_NOT_AVAILABLE_IND_STRU                  *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (EHSM_HSM_EHRPD_NOT_AVAILABLE_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_EHSM,
                                                      sizeof(EHSM_HSM_EHRPD_NOT_AVAILABLE_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 
                  sizeof(EHSM_HSM_EHRPD_NOT_AVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(EHSM_HSM_EHRPD_NOT_AVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulSenderPid         = UEPS_PID_EHSM;
    pstMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid       = UEPS_PID_HSM;
    pstMsg->ulLength            = sizeof(EHSM_HSM_EHRPD_NOT_AVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId             = ID_EHSM_HSM_EHRPD_NOT_AVAILABLE_IND;

    CNAS_SndInternalMsg(pstMsg);

    return;
}



VOS_VOID CNAS_EHSM_SndHsmLteRegSuccessInd(
    VOS_VOID
)
{
    EHSM_HSM_LTE_REG_SUCCESS_IND_STRU          *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (EHSM_HSM_LTE_REG_SUCCESS_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_EHSM,
                                                  sizeof(EHSM_HSM_LTE_REG_SUCCESS_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 
                  sizeof(EHSM_HSM_LTE_REG_SUCCESS_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(EHSM_HSM_LTE_REG_SUCCESS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulSenderPid         = UEPS_PID_EHSM;
    pstMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid       = UEPS_PID_HSM;
    pstMsg->ulLength            = sizeof(EHSM_HSM_LTE_REG_SUCCESS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId             = ID_EHSM_HSM_LTE_REG_SUCCESS_IND;

    CNAS_SndInternalMsg(pstMsg);

    return;
}


VOS_VOID CNAS_EHSM_SndHsmDiscReq(
    VOS_VOID
)
{
    EHSM_HSM_DISC_REQ_STRU             *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (EHSM_HSM_DISC_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_EHSM,
                                           sizeof(EHSM_HSM_DISC_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(EHSM_HSM_DISC_REQ_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(EHSM_HSM_DISC_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulSenderPid         = UEPS_PID_EHSM;
    pstMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid       = UEPS_PID_HSM;
    pstMsg->ulLength            = sizeof(EHSM_HSM_DISC_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId             = ID_EHSM_HSM_DISC_REQ;

    CNAS_SndInternalMsg(pstMsg);

    return;
}



#endif /* FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



