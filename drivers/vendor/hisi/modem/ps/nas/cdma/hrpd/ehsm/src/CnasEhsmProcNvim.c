/******************************************************************************

             Copyright 2014, Huawei Technologies Co. Ltd.

******************************************************************************
File Name       :   CnasEhsmProcNvim.c
Author          :
Version         :
Date            :   21/05/2015
Description     :   Contains functions to retrieve ConnEst and PDN activate retry info from Nvim.
Function list   :
History         :
   1) Date :
      Author:
      Modification:
********************************************************************************/


/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasEhsmProcNvim.h"
#include "CnasEhsmCtx.h"
#include "CnasEhsmMntn.h"
#include "CnasMntn.h"
#include "omnvinterface.h"
#include "PsLib.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_EHSM_PROC_NVIM_C

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID CNAS_EHSM_InitConnEstRetryInfoNvim(
    CNAS_EHSM_RETRY_CONN_EST_INFO_STRU                     *pstRetryConnEstInfoInfo
)
{
    CNAS_EHSM_RETRY_CONN_EST_NVIM_INFO_STRU                 stRetryConnEstNvimInfo;
    VOS_UINT32                                              ulLength;

    ulLength = 0;

    NV_GetLength(en_NV_Item_EHRPD_Retry_Conn_Est_Config, &ulLength);
    if (ulLength > sizeof(CNAS_EHSM_RETRY_CONN_EST_NVIM_INFO_STRU))
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_InitConnEstRetryInfoNvim(): en_NV_Item_EHRPD_Retry_Conn_Est_Config length Error");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_EHRPD_Retry_Conn_Est_Config,
                         &stRetryConnEstNvimInfo,
                         ulLength))
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_InitConnEstRetryInfoNvim(): en_NV_Item_EHRPD_Retry_Conn_Est_Config error");
        return;
    }

    /* If bActiveFlag is set to false assign the values with default values */
    if (VOS_TRUE == stRetryConnEstNvimInfo.ulActiveFlag)
    {
        pstRetryConnEstInfoInfo->ulExpireTimerLen    =   stRetryConnEstNvimInfo.ulExpireTimerLen;
        pstRetryConnEstInfoInfo->usMaxNoOfRetry      =   stRetryConnEstNvimInfo.usMaxNoOfRetry;
    }
}


VOS_VOID CNAS_EHSM_InitPdnSetupRetryInfoNvim (
    CNAS_EHSM_RETRY_PDN_SETUP_INFO_STRU                    *pstRetryPdnSetupInfoInfo
)
{
    CNAS_NVIM_EHRPD_PDN_SETUP_RETRY_STRU                    stRetryPdnSetupNvimInfo;
    VOS_UINT32                                              ulLength;

    ulLength = 0;

    NV_GetLength(en_NV_Item_EHRPD_Retry_Pdn_Setup_Config, &ulLength);
    if (ulLength > sizeof(CNAS_NVIM_EHRPD_PDN_SETUP_RETRY_STRU))
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_InitPdnSetupRetryInfoNvim(): en_NV_Item_EHRPD_Retry_Pdn_Setup_Config length Error");
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_EHRPD_Retry_Pdn_Setup_Config,
                         &stRetryPdnSetupNvimInfo,
                         ulLength))
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "CNAS_EHSM_InitPdnSetupRetryInfoNvim(): en_NV_Item_EHRPD_Retry_Pdn_Setup_Config error");
        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_NV_Item_EHRPD_Retry_Pdn_Setup_Config,
                            sizeof(stRetryPdnSetupNvimInfo),
                            UEPS_PID_EHSM,
                           (VOS_UINT8 *)&stRetryPdnSetupNvimInfo);

    /* If bActiveFlag is set to false assign the values with default values */
    if (VOS_TRUE == stRetryPdnSetupNvimInfo.ulActiveFlag)
    {
        pstRetryPdnSetupInfoInfo->ulExpireTimerLen  =   stRetryPdnSetupNvimInfo.ulExpireTimerLen;
        pstRetryPdnSetupInfoInfo->usMaxNoOfRetry    =   stRetryPdnSetupNvimInfo.usMaxNoOfRetry;
    }
}


#endif /* FEATURE_UE_MODE_CDMA */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

