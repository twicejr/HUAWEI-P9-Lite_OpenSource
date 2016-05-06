/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

  ******************************************************************************
 File Name       :   CnasEhsmSndHsd.c
 Author          :
 Version         :
 Date            :   14/05/2015
 Description     :   EHSM module Sends messages to HSD process file.
 Function list   :
 History         :
     1) Date :
        Author:
        Modification:
********************************************************************************/

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmSndHsd.h"
#include "CnasEhsmCtx.h"
#include "CnasEhsmMntn.h"
#include "ehsm_hsd_pif.h"
#include "CnasMain.h"
/* To Do: Need to add EHSM to HSD interface file */

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_SND_HSD_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  3 Function Define
*****************************************************************************/

/* To Do: Need to write deifinitions of all functions to send message is HSD */

VOS_VOID CNAS_EHSM_SndHsdStartCnf(
    EHSM_HSD_START_RESULT_ENUM_UINT32   enResult
)
{
    EHSM_HSD_START_CNF_STRU            *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (EHSM_HSD_START_CNF_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_EHSM,
                                        sizeof(EHSM_HSD_START_CNF_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulSenderPid         = UEPS_PID_EHSM;
    pstMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid       = UEPS_PID_HSD;
    pstMsg->ulLength            = sizeof(EHSM_HSD_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId             = ID_EHSM_HSD_START_CNF;
    pstMsg->enRslt              = enResult;

    CNAS_SndInternalMsg(pstMsg);

    return;
}


VOS_VOID CNAS_EHSM_SndHsdPowerOffCnf(
    VOS_VOID
)
{
    EHSM_HSD_POWER_OFF_CNF_STRU        *pstMsg = VOS_NULL_PTR;

    /* Allocating memory for message */
    pstMsg = (EHSM_HSD_POWER_OFF_CNF_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_EHSM,
                                            sizeof(EHSM_HSD_POWER_OFF_CNF_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulSenderPid         = UEPS_PID_EHSM;
    pstMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid       = UEPS_PID_HSD;
    pstMsg->ulLength            = sizeof(EHSM_HSD_POWER_OFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId             = ID_EHSM_HSD_POWER_OFF_CNF;

    CNAS_SndInternalMsg(pstMsg);

    return;
}


#endif /* FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



