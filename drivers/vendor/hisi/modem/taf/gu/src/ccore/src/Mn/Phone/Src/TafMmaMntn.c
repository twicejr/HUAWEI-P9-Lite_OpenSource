

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafLog.h"
#include "TafMmaMntn.h"
#include "Taf_Status.h"

#include "TafMmaCtx.h"
#include "TafSdcCtx.h"
#include "TafMmaComFunc.h"
#include "TafMmaSndInternalMsg.h"
#include "NasUtranCtrlInterface.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_MNTN_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
extern STATUS_CONTEXT_STRU                      g_StatusContext;

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_VOID  TAF_MMA_LogFsmInfo(VOS_VOID)
{
    TAF_MMA_LOG_FSM_INFO_STRU          *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_MMA_LOG_FSM_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_LOG_FSM_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_MMA_LogFsmInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_MMA_LOG_FSM_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = TAF_MMA_LOG_FSM_INFO_IND;

    pstMsg->ulState                     = TAF_MMA_FSM_GetFsmTopState();
    pstMsg->enFsmId                     = TAF_MMA_GetCurrFsmId();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

    return;
}



VOS_VOID  TAF_MMA_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
)
{
    TAF_MMA_LOG_BUffER_MSG_INFO_STRU    *pstBufferMsg = VOS_NULL_PTR;
    TAF_MMA_MSG_QUEUE_STRU              *pstMsgQueue  = VOS_NULL_PTR;

    pstBufferMsg = (TAF_MMA_LOG_BUffER_MSG_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                             sizeof(TAF_MMA_LOG_BUffER_MSG_INFO_STRU));
    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LogBufferQueueMsg:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsgQueue                               = TAF_MMA_GetCachMsgBufferAddr();
    pstBufferMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBufferMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstBufferMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstBufferMsg->ulLength        = sizeof(TAF_MMA_LOG_BUffER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBufferMsg->enMsgId         = TAF_MMA_LOG_BUFFER_MSG_INFO_IND;
    pstBufferMsg->ulFullFlg       = ulFullFlg;
    PS_MEM_CPY(&(pstBufferMsg->stMsgQueue), pstMsgQueue, sizeof(pstBufferMsg->stMsgQueue));

    DIAG_TraceReport(pstBufferMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstBufferMsg);

    return;
}



VOS_VOID TAF_MMA_LogOperCtxInfo(VOS_VOID)
{
    TAF_MMA_LOG_OPER_CTX_INFO_STRU     *pstBufferMsg    = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;

    pstBufferMsg = (TAF_MMA_LOG_OPER_CTX_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                             sizeof(TAF_MMA_LOG_OPER_CTX_INFO_STRU));
    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LogOperCtxInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMmaOperCtx                             = TAF_MMA_GetOperCtxAddr();
    pstBufferMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBufferMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstBufferMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstBufferMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstBufferMsg->ulLength        = sizeof(TAF_MMA_LOG_OPER_CTX_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBufferMsg->enMsgId         = TAF_MMA_LOG_OPER_CTX_INFO_IND;
    PS_MEM_CPY(pstBufferMsg->astMmaOperCtx, pstMmaOperCtx, sizeof(pstBufferMsg->astMmaOperCtx));

    DIAG_TraceReport(pstBufferMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstBufferMsg);

    return;
}





VOS_VOID  TAF_MMA_SndOmInternalMsgQueueInfo(
    VOS_UINT8                          ucFullFlg,
    VOS_UINT8                          ucMsgLenValidFlg
)
{
    TAF_MMA_LOG_INTER_MSG_INFO_STRU     *pstInterMsg = VOS_NULL_PTR;

    pstInterMsg = (TAF_MMA_LOG_INTER_MSG_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                             sizeof(TAF_MMA_LOG_INTER_MSG_INFO_STRU));

    if ( VOS_NULL_PTR == pstInterMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndOmInternalMsgQueueInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstInterMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInterMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstInterMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstInterMsg->ulLength        = sizeof(TAF_MMA_LOG_INTER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInterMsg->enMsgId         = TAF_MMA_LOG_INTER_MSG_INFO_IND;
    pstInterMsg->ucFullFlg                   = ucFullFlg;
    pstInterMsg->ucMsgLenValidFlg            = ucMsgLenValidFlg;

    DIAG_TraceReport(pstInterMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstInterMsg);

    return;
}



VOS_VOID  TAF_MMA_LogDrvApiPwrCtrlSleepVoteUnlock(
    VOS_UINT32                          ulRslt,
    PWC_CLIENT_ID_E                     enClientId
)
{
    TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                              sizeof(TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LogDrvApiPwrCtrlSleepVoteUnlock:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                sizeof(TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->ulLength        = sizeof(TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_UNLOCK;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enClientId                  = enClientId;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

    return;
}




VOS_VOID  TAF_MMA_LogDrvApiPwrCtrlSleepVoteLock(
    VOS_UINT32                          ulRslt,
    PWC_CLIENT_ID_E                     enClientId
)
{
    TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                              sizeof(TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LogDrvApiPwrCtrlSleepVoteLock:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                sizeof(TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->ulLength        = sizeof(TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enClientId                  = enClientId;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

    return;
}


VOS_VOID TAF_MMA_ShowPhoneModeCtrlInfo(VOS_VOID)
{
    (VOS_VOID)vos_printf("\n");
    (VOS_VOID)vos_printf("*****************************\n");
    (VOS_VOID)vos_printf("*Auto Init Ps Flag:      %d\n", TAF_MMA_GetAutoInitPsFlg());
    (VOS_VOID)vos_printf("*Auto Switch On Flag:    %d\n", TAF_MMA_GetAutoSwitchOnFlg());
    (VOS_VOID)vos_printf("*Cur  Phone Mode:        %d\n", TAF_SDC_GetCurPhoneMode());
    (VOS_VOID)vos_printf("*Cur  Fsm State:         %d\n", g_StatusContext.ulFsmState);
    (VOS_VOID)vos_printf("*Phone Mode Error Code:  %d\n", TAF_MMA_GetCurPhoneErrorCode_PhoneMode());
    (VOS_VOID)vos_printf("*****************************\n");
}


VOS_VOID TAF_MMA_ShowCLConfigInfo(VOS_VOID)
{
    (VOS_VOID)vos_printf("\n");
    (VOS_VOID)vos_printf("*****************************\n");
    (VOS_VOID)vos_printf("*CL CONFIG Enable Flag: %d\n",          TAF_SDC_GetLCEnableFlg());
    (VOS_VOID)vos_printf("*CL CONFIG RatCombined Flag: %d\n",     TAF_SDC_GetLCRatCombined());
    (VOS_VOID)vos_printf("*CL CONFIG LCWORK Flag: %d\n",          TAF_SDC_GetLCWorkCfg());
    (VOS_VOID)vos_printf("*****************************\n");
}



VOS_VOID TAF_MMA_LogCopsRltInfo(
        TAF_PH_NETWORKNAME_STRU                   *pstOperatorName,
        TAF_SDC_LOG_OPER_NAME_TYPE_ENUM_UINT8      enType
)
{
    TAF_MMA_LOG_COPS_RLT_INFO_STRU               *pstBufferMsg            = VOS_NULL_PTR;
    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU     *pstEnhancedOperNameInfo = VOS_NULL_PTR;

    pstBufferMsg = (TAF_MMA_LOG_COPS_RLT_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                             sizeof(TAF_MMA_LOG_COPS_RLT_INFO_STRU));
    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LogCopsRltInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstEnhancedOperNameInfo = TAF_SDC_GetEnhancedOperatorNameInfo();
    PS_MEM_SET(pstBufferMsg, 0x0, sizeof(TAF_MMA_LOG_COPS_RLT_INFO_STRU));

    pstBufferMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBufferMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstBufferMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstBufferMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstBufferMsg->ulLength        = sizeof(TAF_MMA_LOG_COPS_RLT_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBufferMsg->enMsgId         = TAF_MMA_LOG_COPS_RLT_INFO_IND;

    pstBufferMsg->enType                      = enType;
    pstBufferMsg->stNameFormat                = pstOperatorName->NameFormat;
    pstBufferMsg->ucRaMode                    = pstOperatorName->RaMode;
    pstBufferMsg->ucPlmnSelMode               = pstOperatorName->PlmnSelMode;
    PS_MEM_CPY(&pstBufferMsg->stName, &pstOperatorName->Name, sizeof(TAF_PH_OPERATOR_NAME_STRU));

    /* log中只打印MMINFO和SPN FILE */
    pstBufferMsg->stEonsInfo.cWildCard        = pstEnhancedOperNameInfo->cWildCard;
    pstBufferMsg->stEonsInfo.enCopsFormatType = pstEnhancedOperNameInfo->enCopsFormatType;
    PS_MEM_CPY(&pstBufferMsg->stEonsInfo.stOperNameTypePrio, &pstEnhancedOperNameInfo->stOperNameTypePrio, sizeof(TAF_SDC_OPER_NAME_TYPE_PRIO_STRU));

    /* SPN USIM FILE */
    PS_MEM_CPY(&pstBufferMsg->stEonsInfo.stUsimSpnFileInfo,
                &pstEnhancedOperNameInfo->stUsimSpnFileInfo,
                sizeof(TAF_SDC_SPN_FILE_INFO_STRU));

    /* SPN SIM FILE */
    PS_MEM_CPY(&pstBufferMsg->stEonsInfo.stSimSpnFileInfo,
                &pstEnhancedOperNameInfo->stSimSpnFileInfo,
                sizeof(TAF_SDC_SPN_FILE_INFO_STRU));

    /* MMINFO */
    PS_MEM_CPY(&pstBufferMsg->stEonsInfo.stMmInfo,
                &pstEnhancedOperNameInfo->stMmInfo,
                sizeof(TAF_SDC_MM_INFO_STRU));

    DIAG_TraceReport(pstBufferMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstBufferMsg);

    return;
}



VOS_VOID TAF_MMA_ModelPihSndUsimStatusInd(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardTypeOne,
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardServiceOne,
    USIMM_CARD_TYPE_ENUM_UINT32         enCardTypeTwo,
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardServiceTwo
)
{
    USIMM_CARDSTATUS_IND_STRU          *pstUsimMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstUsimMsg = (USIMM_CARDSTATUS_IND_STRU *)TAF_MMA_ALLOC_MSG_WITH_HDR(sizeof(USIMM_CARDSTATUS_IND_STRU));
    if (VOS_NULL_PTR == pstUsimMsg)
    {
        return;
    }

    /* 清空消息内容 */
    TAF_MMA_CLR_MSG_ENTITY(pstUsimMsg);

    pstUsimMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstUsimMsg->ulReceiverPid    = WUEPS_PID_MMA;
    pstUsimMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstUsimMsg->ulSenderPid      = MAPS_PIH_PID;
    pstUsimMsg->ulMsgName        = USIMM_CARDSTATUS_IND;
    pstUsimMsg->enPhyCardType    = USIMM_PHYCARD_TYPE_UICC;

    switch(enCardTypeOne)
    {
        case USIMM_CARD_USIM:
        case USIMM_CARD_SIM:
            {
                pstUsimMsg->stUsimSimInfo.enCardType    = enCardTypeOne;
                pstUsimMsg->stUsimSimInfo.enCardService = enCardServiceOne;
            }
            break;

        case USIMM_CARD_UIM:
        case USIMM_CARD_CSIM:
            {
                pstUsimMsg->stCsimUimInfo.enCardService = enCardServiceOne;
                pstUsimMsg->stCsimUimInfo.enCardType    = enCardTypeOne;
            }
            break;

        default:
            break;
    }

    switch(enCardTypeTwo)
    {
        case USIMM_CARD_USIM:
        case USIMM_CARD_SIM:
            {
                pstUsimMsg->stUsimSimInfo.enCardType    = enCardTypeTwo;
                pstUsimMsg->stUsimSimInfo.enCardService = enCardServiceTwo;
            }
            break;

        case USIMM_CARD_UIM:
        case USIMM_CARD_CSIM:
            {
                pstUsimMsg->stCsimUimInfo.enCardService = enCardServiceTwo;
                pstUsimMsg->stCsimUimInfo.enCardType    = enCardTypeTwo;
            }
            break;

        default:
            break;
    }


    /* 调用VOS发送原语 */
    TAF_MMA_SEND_MSG(pstUsimMsg);

    return;

}


VOS_VOID TAF_MMA_ModelUphySndInitStatusInd(
    MMA_UPHY_INIT_STATUS_ENUM_UINT16               enInitStatus
)
{
    UPHY_MMA_INIT_STATUS_IND_STRU      *pstRcvMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstRcvMsg = (UPHY_MMA_INIT_STATUS_IND_STRU *)TAF_MMA_ALLOC_MSG_WITH_HDR(sizeof(UPHY_MMA_INIT_STATUS_IND_STRU));
    if (VOS_NULL_PTR == pstRcvMsg)
    {
        return;
    }

    /* 清空消息内容 */
    TAF_MMA_CLR_MSG_ENTITY(pstRcvMsg);

    pstRcvMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstRcvMsg->ulReceiverPid    = WUEPS_PID_MMA;
    pstRcvMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstRcvMsg->ulSenderPid      = DSP_PID_STARTUP;
    pstRcvMsg->usMsgID          = ID_UPHY_MMA_INIT_STATUS_IND;
    pstRcvMsg->enInitStatus     = enInitStatus;

    /* 调用VOS发送原语 */
    TAF_MMA_SEND_MSG(pstRcvMsg);

    return;

}


VOS_VOID TAF_MMA_ModelUsimStatusIndTimeOut(VOS_VOID)
{
    REL_TIMER_MSG                      *pstTimerMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstTimerMsg = (REL_TIMER_MSG *)TAF_MMA_ALLOC_MSG_WITH_HDR(sizeof(REL_TIMER_MSG));
    if (VOS_NULL_PTR == pstTimerMsg)
    {
        return;
    }

    /* 清空消息内容 */
    TAF_MMA_CLR_MSG_ENTITY(pstTimerMsg);

    pstTimerMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstTimerMsg->ulReceiverPid    = WUEPS_PID_MMA;
    pstTimerMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstTimerMsg->ulSenderPid      = VOS_PID_TIMER;
    pstTimerMsg->ulName           = TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT;

    /* 调用VOS发送原语 */
    TAF_MMA_SEND_MSG(pstTimerMsg);

    return;

}



VOS_VOID TAF_MMA_SndTestInterPowerInitReq(VOS_VOID)
{
    TAF_MMA_INTER_POWER_INIT_REQ_STRU  *pstPowerInitMsg = VOS_NULL_PTR;
    TAF_SDC_CTX_STRU                   *pstSdcCtx = VOS_NULL_PTR;

    pstSdcCtx = TAF_SDC_GetSdcCtx();

    pstPowerInitMsg  = (TAF_MMA_INTER_POWER_INIT_REQ_STRU*)TAF_MMA_ALLOC_MSG_WITH_HDR(sizeof(TAF_MMA_INTER_POWER_INIT_REQ_STRU));
    if (VOS_NULL_PTR == pstPowerInitMsg)
    {
        return;
    }

    /* 清空消息内容 */
    TAF_MMA_CLR_MSG_ENTITY(pstPowerInitMsg);

    TAF_MMA_CFG_INTRA_MSG_HDR(pstPowerInitMsg, MMA_MMA_INTER_POWER_INIT);

    TAF_MMA_SetPhyInitStatus(MMA_UPHY_INIT_STATUS_BUTT);
    TAF_SDC_InitSimInfo(&pstSdcCtx->stSimInfo.stUsimInfo);

    /* 需要发送外部消息,因为上电时无外部消息触发内部消息 */
    TAF_MMA_SEND_MSG(pstPowerInitMsg);

    return;
}


VOS_VOID TAF_MMA_TestSetGeoInfo(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc
)
{
    TAF_MMA_GET_GEO_CTX_STRU            *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx        = TAF_MMA_GetGeoCtxAddr();

    pstGetGeoCtx->stGeoPlmnId.ulMcc = ulMcc;
    pstGetGeoCtx->stGeoPlmnId.ulMnc = ulMnc;
    pstGetGeoCtx->ulGetGeoTickTime  = VOS_GetTick() / PRE_SECOND_TO_TICK;

    return;
}



VOS_VOID  TAF_MMA_LogNetworkInfoAndAppNetworkInfo(VOS_VOID)
{
    TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU                            *pstMsg = VOS_NULL_PTR;
    TAF_SDC_NETWORK_INFO_STRU           *pstNetworkInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO             *pstAppNetworkInfo= VOS_NULL_PTR;

    pstMsg = (TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                         sizeof(TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU));

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_SDC_LogNetworkInfoAndAppNetworkInfo:ERROR:Alloc Mem Fail.");
        return;
    }
    PS_MEM_SET(pstMsg, 0x00, sizeof(TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU));


    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = TAF_MMA_LOG_NETWORK_APPNETWORK_CTX_INFO_IND;

    pstNetworkInfo          = TAF_SDC_GetCurrNetworkInfo();
    pstAppNetworkInfo       = TAF_SDC_GetAppNetworkInfo();

    PS_MEM_CPY(&(pstMsg->stNetworkInfo), pstNetworkInfo, sizeof(TAF_SDC_NETWORK_INFO_STRU));
    PS_MEM_CPY(&(pstMsg->stAppNetworkInfo), pstAppNetworkInfo, sizeof(TAF_SDC_APPNETWORK_INFO));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

    return;
}



VOS_VOID TAF_MMA_LogReadNVInfo(
    VOS_UINT16                          enNvItem,
    VOS_UINT16                          usNvDataLength,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData
)
{
    TAF_MMA_LOG_READ_NV_INFO_IND_STRU  *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_MMA_LOG_READ_NV_INFO_IND_STRU*)PS_MEM_ALLOC(ulPid,
                             sizeof(TAF_MMA_LOG_READ_NV_INFO_IND_STRU) + usNvDataLength - 4);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulPid;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulPid;
    pstMsg->ulLength        = sizeof(TAF_MMA_LOG_READ_NV_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH + usNvDataLength - 4;
    pstMsg->enMsgId         = TAF_MMA_LOG_READ_NV_INFO_IND;
    pstMsg->enNvItem        = enNvItem;
    pstMsg->usNvDataLength  = usNvDataLength;
    PS_MEM_CPY(pstMsg->aucNvInfo, pucData, usNvDataLength);

    DIAG_TraceReport((VOS_VOID *)pstMsg);

    PS_MEM_FREE(ulPid, pstMsg);
    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_MMA_LogDelayReportInfo(
    TAF_MMA_LOG_DELAY_REPORT_TYPE_ENUM_UINT8    enDelayRptType
)
{
    TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LogDelayReportInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->ulLength        = sizeof(TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_IND;

    pstMsg->enDelayRptType  = enDelayRptType;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

    return;
}
#endif
/*lint -restore */



VOS_VOID TAF_MMA_LogCLDelayRptSrvStatusCtx(
    TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENUM_UINT8         enMmaLogDelayRptCtxType
)
{
    TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU    *pstMsg              = VOS_NULL_PTR;
    TAF_SDC_NETWORK_INFO_STRU                              *pstNetWorkInfo      = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO                                *pstAppNetWorkInfo   = VOS_NULL_PTR;

    pstMsg = (TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LogCLDelayRptSrvStatusCtx:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->ulLength        = sizeof(TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_STRU) - VOS_MSG_HEAD_LENGTH;

    if (TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER == enMmaLogDelayRptCtxType)
    {
        pstMsg->enMsgId         = TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_ENTER_IND;
    }
    else
    {
        pstMsg->enMsgId         = TAF_MMA_LOG_CL_DELAY_REPORT_SERVICE_STATUS_CTX_EXIT_IND;
    }

    pstNetWorkInfo      = TAF_SDC_GetNetWorkInfoAddr();
    pstAppNetWorkInfo   = TAF_SDC_GetAppNetWorkInfoAddr();

    /* 勾取NetWorkInfo中的系统信息，实时信息 */
    /* 实时1x系统信息 */
    pstMsg->stNetWorkInfo.st1xSysInfo.usBandClass    = pstNetWorkInfo->stSysInfo.st1xSysInfo.usBandClass;
    pstMsg->stNetWorkInfo.st1xSysInfo.usFreq         = pstNetWorkInfo->stSysInfo.st1xSysInfo.usFreq;
    pstMsg->stNetWorkInfo.st1xSysInfo.lSid           = pstNetWorkInfo->stSysInfo.st1xSysInfo.lSid;
    pstMsg->stNetWorkInfo.st1xSysInfo.lNid           = pstNetWorkInfo->stSysInfo.st1xSysInfo.lNid;
    pstMsg->stNetWorkInfo.st1xSysInfo.uc1xRfAvailFlg = pstNetWorkInfo->stSysInfo.st1xSysInfo.uc1xRfAvailFlg;
    pstMsg->stNetWorkInfo.st1xSysInfo.ucRoamingInd   = pstNetWorkInfo->stSysInfo.st1xSysInfo.ucRoamingInd;
    pstMsg->stNetWorkInfo.st1xSysInfo.usImsi11_12    = pstNetWorkInfo->stSysInfo.st1xSysInfo.stServiceInfo.usImsi11_12;
    pstMsg->stNetWorkInfo.st1xSysInfo.ulMcc          = pstNetWorkInfo->stSysInfo.st1xSysInfo.stServiceInfo.ulMcc;
    pstMsg->stNetWorkInfo.st1xSysInfo.usMnc          = pstNetWorkInfo->stSysInfo.st1xSysInfo.stServiceInfo.usMnc;

    /* 实时CS域和PS域相关信息 */
    PS_MEM_CPY(&(pstMsg->stNetWorkInfo.stCsDomainInfo), &(pstNetWorkInfo->stCsDomainInfo), sizeof(TAF_SDC_CS_DOMAIN_INFO_STRU));
    PS_MEM_CPY(&(pstMsg->stNetWorkInfo.stPsDomainInfo), &(pstNetWorkInfo->stPsDomainInfo), sizeof(TAF_SDC_PS_DOMAIN_INFO_STRU));

    /* 实时lte系统信息 */
    PS_MEM_CPY(&(pstMsg->stNetWorkInfo.st3GppServPlmnInfo.stServicePlmnId),
               &(pstNetWorkInfo->stSysInfo.st3gppSysInfo.stPlmnId),
               sizeof(TAF_SDC_PLMN_ID_STRU));
    pstMsg->stNetWorkInfo.st3GppServPlmnInfo.enServiceSysMode     = pstNetWorkInfo->stSysInfo.enSysMode;
    pstMsg->stNetWorkInfo.st3GppServPlmnInfo.ucServiceUtranMode   = NAS_UTRANCTRL_GetCurrUtranMode();
    pstMsg->stNetWorkInfo.st3GppServPlmnInfo.enServiceSysSubMode  = pstNetWorkInfo->stSysInfo.enSysSubMode;
    pstMsg->stNetWorkInfo.st3GppServPlmnInfo.usServiceLac         = pstNetWorkInfo->stSysInfo.st3gppSysInfo.usLac;
    pstMsg->stNetWorkInfo.st3GppServPlmnInfo.ucServiceRac         = pstNetWorkInfo->stSysInfo.st3gppSysInfo.ucRac;
    pstMsg->stNetWorkInfo.st3GppServPlmnInfo.ulServiceCellId      = pstNetWorkInfo->stSysInfo.st3gppSysInfo.ulCellId;
    pstMsg->stNetWorkInfo.st3GppServPlmnInfo.ucServiceRoamFlg     = pstNetWorkInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

    pstMsg->stNetWorkInfo.enSysMode                               = pstNetWorkInfo->stSysInfo.enSysMode;
    pstMsg->stNetWorkInfo.enSysSubMode                            = pstNetWorkInfo->stSysInfo.enSysSubMode;
    pstMsg->stNetWorkInfo.enReportSrvsta                          = pstNetWorkInfo->enReportSrvsta;
    pstMsg->stNetWorkInfo.enServiceDomain                         = pstNetWorkInfo->enServiceDomain;

    /* 勾取AppNetWorkInfo中的系统信息，延时信息 */
    /* 延时1x系统信息 */
    pstMsg->stAppNetWorkInfo.st1xSysInfo.usBandClass    = pstAppNetWorkInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo.usBandClass;
    pstMsg->stAppNetWorkInfo.st1xSysInfo.usFreq         = pstAppNetWorkInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo.usFreq;
    pstMsg->stAppNetWorkInfo.st1xSysInfo.lSid           = pstAppNetWorkInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo.lSid;
    pstMsg->stAppNetWorkInfo.st1xSysInfo.lNid           = pstAppNetWorkInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo.lNid;
    pstMsg->stAppNetWorkInfo.st1xSysInfo.uc1xRfAvailFlg = pstAppNetWorkInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo.uc1xRfAvailFlg;
    pstMsg->stAppNetWorkInfo.st1xSysInfo.ucRoamingInd   = pstAppNetWorkInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo.ucRoamingInd;
    pstMsg->stAppNetWorkInfo.st1xSysInfo.usImsi11_12    = pstAppNetWorkInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo.stServiceInfo.usImsi11_12;
    pstMsg->stAppNetWorkInfo.st1xSysInfo.ulMcc          = pstAppNetWorkInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo.stServiceInfo.ulMcc;
    pstMsg->stAppNetWorkInfo.st1xSysInfo.usMnc          = pstAppNetWorkInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo.stServiceInfo.usMnc;
    /* 延时lte系统信息 */
    PS_MEM_CPY(&(pstMsg->stAppNetWorkInfo.st3GppServPlmnInfo),
               &(pstAppNetWorkInfo->stAppSysInfo.stServPlmnInfo),
               sizeof(TAF_SDC_SERVICED_PLMN_INFO_STRU));
    /* 延时CS域和PS域相关信息 */
    PS_MEM_CPY(&(pstMsg->stAppNetWorkInfo.stCsDomainInfo), &(pstAppNetWorkInfo->stCsDomainInfo), sizeof(TAF_SDC_CS_DOMAIN_INFO_STRU));
    PS_MEM_CPY(&(pstMsg->stAppNetWorkInfo.stPsDomainInfo), &(pstAppNetWorkInfo->stPsDomainInfo), sizeof(TAF_SDC_PS_DOMAIN_INFO_STRU));

    pstMsg->stAppNetWorkInfo.enSysMode       = pstAppNetWorkInfo->stAppSysInfo.enSysMode;
    pstMsg->stAppNetWorkInfo.enSysSubMode    = pstAppNetWorkInfo->stAppSysInfo.enSysSubMode;
    pstMsg->stAppNetWorkInfo.enReportSrvsta  = pstAppNetWorkInfo->enReportSrvsta;
    pstMsg->stAppNetWorkInfo.enServiceDomain = pstAppNetWorkInfo->enServiceDomain;

    /* 延时上报定时器状态 */
    pstMsg->enCsDelayReportTimerStatus      = TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
    pstMsg->enPsDelayReportTimerStatus      = TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
    pstMsg->enDelayRptApsClNoSrvTimerStatue = TAF_MMA_GetTimerStatus(TI_TAF_MMA_DELAY_RPT_APS_CL_NO_SERVICE);
    pstMsg->enDelayRptApsDoNoSrvTimerStatue = TAF_MMA_GetTimerStatus(TI_TAF_MMA_DELAY_RPT_APS_DO_NO_SERVICE);

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


