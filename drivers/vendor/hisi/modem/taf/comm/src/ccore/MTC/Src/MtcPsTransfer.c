
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MtcDebug.h"
#include "MtcComm.h"
#include "MtcPsTransfer.h"

#include "MtcGmmInterface.h"

#include "UsimPsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_MTC_PS_TRANSFER_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_VOID MTC_SndModem0MtaPsTransferInd(
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enPsTransferCause
)
{
    VOS_UINT16                          ulLenth;
    MTC_MTA_PS_TRANSFER_IND_STRU       *pstPsTransferInd = VOS_NULL_PTR;

    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx = VOS_NULL_PTR;

    pstPsTransferCtx                    = MTC_GetPsTransferCtxAddr();
    pstPsTransferCtx->enReportCause     = enPsTransferCause;

    ulLenth = sizeof(MTC_MTA_PS_TRANSFER_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 分配消息空间 */
    pstPsTransferInd = (MTC_MTA_PS_TRANSFER_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstPsTransferInd)
    {
        MTC_ERROR_LOG("MTC_SndModem0MtaPsTransferInd: Alloc msg fail!");
        return;
    }

    /* 清消息空间 */
    PS_MEM_SET((VOS_UINT8*)pstPsTransferInd + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* 填充消息 */
    pstPsTransferInd->stMsgHeader.ulReceiverPid = I0_UEPS_PID_MTA;
    pstPsTransferInd->stMsgHeader.ulMsgName     = ID_MTC_MTA_PS_TRANSFER_IND;
    pstPsTransferInd->ucCause                   = enPsTransferCause;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstPsTransferInd))
    {
        MTC_ERROR1_LOG("MTC_SndModem0MtaPsTransferInd: Snd Msg err. Rec Pid ", I0_UEPS_PID_MTA);
        return;
    }

    /* 可维可测: 记录上报PS域迁移指示次数 */
    MTC_DEBUG_SndPsTransferInd(enPsTransferCause);

    return;
}


VOS_VOID MTC_SndModem0GmmRrcAreaLostInd(VOS_VOID)
{
    VOS_UINT16                          ulLenth;
    MTC_GMM_RRC_AREA_LOST_IND_STRU     *pstAreaLostInd = VOS_NULL_PTR;

    ulLenth = sizeof(MTC_GMM_RRC_AREA_LOST_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 分配消息空间 */
    pstAreaLostInd = (MTC_GMM_RRC_AREA_LOST_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstAreaLostInd)
    {
        MTC_ERROR_LOG("MTC_SndModem0GmmRrcAreaLostInd: Alloc msg fail!");
        return;
    }

    /* 清消息空间 */
    PS_MEM_SET((VOS_UINT8*)pstAreaLostInd + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* 填充消息 */
    pstAreaLostInd->stMsgHeader.ulReceiverPid   = I0_WUEPS_PID_GMM;
    pstAreaLostInd->stMsgHeader.ulMsgName       = ID_MTC_GMM_RRC_AREA_LOST_IND;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstAreaLostInd))
    {
        MTC_ERROR1_LOG("MTC_SndModem0GmmRrcAreaLostInd: Snd Msg err. Rec Pid ", I0_UEPS_PID_MTA);
        return;
    }

    return;
}


VOS_VOID MTC_SndModem0MmaPsTransferInd(
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enPsTransferCause
)
{
    VOS_UINT16                          ulLenth;
    MTC_MMA_PS_TRANSFER_IND_STRU       *pstPsTransferInd = VOS_NULL_PTR;

    ulLenth = sizeof(MTC_MMA_PS_TRANSFER_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 分配消息空间 */
    pstPsTransferInd = (MTC_MMA_PS_TRANSFER_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstPsTransferInd)
    {
        MTC_ERROR_LOG("MTC_SndMmaPsTransferInd: Alloc msg fail!");
        return;
    }

    /* 清消息空间 */
    PS_MEM_SET((VOS_UINT8*)pstPsTransferInd + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* 填充消息 */
    pstPsTransferInd->stMsgHeader.ulReceiverPid     = I0_WUEPS_PID_MMA;
    pstPsTransferInd->stMsgHeader.ulMsgName         = ID_MTC_MMA_PS_TRANSFER_IND;
    pstPsTransferInd->enSolutionCfg                 = MTC_GetPsTransferCfg();
    pstPsTransferInd->ucCause                       = enPsTransferCause;

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstPsTransferInd))
    {
        MTC_ERROR1_LOG("MTC_SndMmaPsTransferInd: Snd Msg err. Rec Pid ", I0_WUEPS_PID_MMA);
        return;
    }

    return;
}


VOS_VOID MTC_RcvRrcAreaLostInd(VOS_VOID * pMsg)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    RRC_MTC_AREA_LOST_IND_STRU         *pstAreaLostInd = VOS_NULL_PTR;
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enModem1PowerState;
    MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8   enOperatorCustSolution;
    VOS_BOOL                            enTestCardFlg;

    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx    = VOS_NULL_PTR;
    pstPsTransferCtx                    = MTC_GetPsTransferCtxAddr();

    /* GCF测试时不需要启动PSTRANSFER流程，否则导致GCF测试部不通过 */
    enTestCardFlg = USIMM_IsTestCard();
    if (VOS_TRUE == enTestCardFlg)
    {
        return;
    }

    pstAreaLostInd      = (RRC_MTC_AREA_LOST_IND_STRU*)pMsg;
    enModemId           = VOS_GetModemIDFromPid(pstAreaLostInd->stMsgHeader.ulSenderPid);

    /* 仅处理Modem0发送的丢网指示 */
    if (enModemId != MODEM_ID_0)
    {
        MTC_ERROR1_LOG("MTC_RcvRrcAreaLostInd: Err ModemId ", enModemId);
        return;
    }

    /* 未开启PS域迁移策略，只记录次数 */
    if (MTC_PS_TRANSFER_NONE == MTC_GetPsTransferCfg())
    {
        /* 可维可测: 记录接收到丢网指示的次数 */
        MTC_DEBUG_RcvRrcAreaLostInd(pstAreaLostInd->stMsgHeader.ulSenderPid);
        return;
    }

    /* 运营商定制方案SVLTE或C+L时需要上报AT丢网指示 */
    enOperatorCustSolution  = MTC_GetOperatorCustSolution();
    enModem1PowerState      = MTC_GetModemPowerState(MODEM_ID_1);

    /* 当接入层在业务态或idle态丢网且Modem1开机且卡有效时，上报PS域迁移指示 */
    if ((VOS_TRUE == MTC_GetModemUsimValidFlag(enModemId))
     && (((MTC_OPERATOR_CUST_CMCC_SVLTE == enOperatorCustSolution)
       && (MTC_MODEM_POWER_ON == enModem1PowerState))
      || (MTC_OPERATOR_CUST_CT_LC == enOperatorCustSolution) ))
    {
        if (MTC_PS_TRANSFER_CAUSE_AREA_LOST != pstPsTransferCtx->enReportCause)
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_LOST);

            /* 通知modem0 gmm丢网，gmm记录全局变量后续detach只做一次减少detach时间 */
            MTC_SndModem0GmmRrcAreaLostInd();
        }
    }

    pstPsTransferCtx->enRrcCause = MTC_PS_TRANSFER_CAUSE_AREA_LOST;

    /* 可维可测: 记录接收到丢网指示的次数 */
    MTC_DEBUG_RcvRrcAreaLostInd(pstAreaLostInd->stMsgHeader.ulSenderPid);

    return;
}


VOS_VOID MTC_RcvRrcAreaAvaliableInd(VOS_VOID * pMsg)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    RRC_MTC_AREA_AVALIABLE_IND_STRU    *pstAreaAvaliableInd = VOS_NULL_PTR;
    MTC_MODEM_NETWORK_INFO_STRU        *pstNetworkInfo      = VOS_NULL_PTR;

    VOS_UINT8                           ucUsimValidFlag;
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx    = VOS_NULL_PTR;

    pstPsTransferCtx    = MTC_GetPsTransferCtxAddr();
    ucUsimValidFlag     = MTC_GetModemUsimValidFlag(MODEM_ID_0);

    pstAreaAvaliableInd = (RRC_MTC_AREA_AVALIABLE_IND_STRU*)pMsg;
    enModemId           = VOS_GetModemIDFromPid(pstAreaAvaliableInd->stMsgHeader.ulSenderPid);

    /* 仅处理Modem0发送的网络恢复指示 */
    if (enModemId != MODEM_ID_0)
    {
        MTC_ERROR1_LOG("MTC_RcvRrcAreaAvaliableInd: Err ModemId ", enModemId);
        return;
    }

    /* PS域离网重选策略开启时 */
    if (MTC_PS_TRANSFER_OFF_AREA == MTC_GetPsTransferCfg())
    {
        pstNetworkInfo = MTC_GetModemNetworkInfoAddr(enModemId);

        /* 当前驻留网络非禁止PLMN、非禁止GPRS接入、卡状态有效、不重复上报 */
        if ( (VOS_FALSE == pstNetworkInfo->ucIsForbiddenPlmnFlag)
          && (VOS_TRUE == pstNetworkInfo->stPsDomainInfo.ucPsSupportFlg)
          && (VOS_TRUE == ucUsimValidFlag)
          && (MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE != pstPsTransferCtx->enReportCause))
        {
            /* 上报PS域迁移网络恢复指示AT命令 */
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }

        pstPsTransferCtx->enRrcCause = MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE;

        MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
 
    }

    /* 可维可测: 记录接收到丢网指示的次数 */
    MTC_DEBUG_RcvRrcAreaAvaliableInd();

    return;
}


VOS_VOID MTC_ProcCurrCampPlmnInfoForSvlte(VOS_VOID)
{
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enModem1PowerState;
    MTC_MODEM_NETWORK_INFO_STRU        *pstModem0NetworkInfo = VOS_NULL_PTR;
    MTC_PS_TRANSFER_ENUM_UINT8          enPsTransferSolution;
    MTC_RATMODE_ENUM_UINT8              enModem0RateMode;

    VOS_UINT8                           ucUsimValidFlag;

    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx    = VOS_NULL_PTR;
    pstPsTransferCtx                    = MTC_GetPsTransferCtxAddr();

    enModem1PowerState      = MTC_GetModemPowerState(MODEM_ID_1);
    pstModem0NetworkInfo    = MTC_GetModemNetworkInfoAddr(MODEM_ID_0);
    enPsTransferSolution    = MTC_GetPsTransferCfg();
    enModem0RateMode        = MTC_GetModemRatMode(MODEM_ID_0);



    /* Modem1关机，国外模式无需PS域迁移 */
    if (MTC_MODEM_POWER_OFF == enModem1PowerState)
    {
        return;
    }

    ucUsimValidFlag = MTC_GetModemUsimValidFlag(MODEM_ID_0);

    /* 1、modem1处于开机状态
       2、当前驻留网络接入技术为T/L(OscarTL通过主卡的G重选回T/L)
       3、当前驻留网络非禁止plmn
       4、单待模式modem0的ps是detach状态，上报PS域迁移指示 */
    if ( ( (MTC_RATMODE_LTE == enModem0RateMode)
        || (MTC_RATMODE_TDS == enModem0RateMode) )
      && (VOS_FALSE == pstModem0NetworkInfo->ucIsForbiddenPlmnFlag)
      && (VOS_TRUE == ucUsimValidFlag)
      && (VOS_FALSE == pstModem0NetworkInfo->stPsDomainInfo.ucPsAttachAllowFlg)
      && (VOS_TRUE == pstModem0NetworkInfo->stPsDomainInfo.ucPsSupportFlg) )
    {
        /* PS域迁移策略脱网重选，上报网络恢复指示AT命令 */
        if (MTC_PS_TRANSFER_LOST_AREA == enPsTransferSolution)
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
            MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }

        /* PS域迁移策略离网重选，上报网络恢复指示AT命令 */
        if ((MTC_PS_TRANSFER_OFF_AREA == enPsTransferSolution)
         && (MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE == pstPsTransferCtx->enRrcCause))
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
            MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }
        //MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);

    }

    return;
}


VOS_VOID MTC_ProcCurrCampPlmnInfoForLC(VOS_VOID)
{
    MTC_MODEM_NETWORK_INFO_STRU        *pstModem0NetworkInfo = VOS_NULL_PTR;
    MTC_PS_TRANSFER_ENUM_UINT8          enPsTransferSolution;
    MTC_RATMODE_ENUM_UINT8              enModem0RateMode;

    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx    = VOS_NULL_PTR;
    pstPsTransferCtx                    = MTC_GetPsTransferCtxAddr();


    pstModem0NetworkInfo    = MTC_GetModemNetworkInfoAddr(MODEM_ID_0);
    enPsTransferSolution    = MTC_GetPsTransferCfg();
    enModem0RateMode        = MTC_GetModemRatMode(MODEM_ID_0);

    /* 1、当前驻留网络非禁止plmn
        2、单待模式modem0的ps是detach状态，上报PS域迁移指示 */
    if ( (MTC_RATMODE_LTE == enModem0RateMode)
      && (VOS_FALSE == pstModem0NetworkInfo->ucIsForbiddenPlmnFlag)
      && (VOS_FALSE == pstModem0NetworkInfo->stPsDomainInfo.ucPsAttachAllowFlg))
    {
        /* PS域迁移策略脱网重选，上报网络恢复指示AT命令 */
        if (MTC_PS_TRANSFER_LOST_AREA == enPsTransferSolution)
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }

        /* PS域迁移策略离网重选，上报网络恢复指示AT命令 */
        if ((MTC_PS_TRANSFER_OFF_AREA == enPsTransferSolution)
         && (MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE == pstPsTransferCtx->enRrcCause))
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }

        MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
    }

    return;
}


VOS_VOID MTC_RcvGsmCellInfoInd(VOS_VOID *pMsg)
{
    RRC_MTC_GSM_CELL_INFO_IND_STRU     *pstGsmInfoInd  = VOS_NULL_PTR;
    MTC_RRC_GSM_CELL_INFO_IND_STRU     *pstGsmCellInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;

    /* 如果当前已经关机，则停止发送信息 */
    if (MTC_MODEM_POWER_OFF == MTC_GetModemPowerState(MODEM_ID_0))
    {
        return;
    }

    /* 判断当前主模状态, 为TDS/LTE时发送 */
    if (MTC_RATMODE_TDS == MTC_GetModemRatMode(MODEM_ID_0))
    {
        ulReceiverPid = TPS_PID_RRC;
    }
    else if (MTC_RATMODE_LTE== MTC_GetModemRatMode(MODEM_ID_0))
    {
        ulReceiverPid = PS_PID_ERRC;
    }
    else
    {
        return;
    }

    /* 分配消息空间 */
    pstGsmCellInfo  = (MTC_RRC_GSM_CELL_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                UEPS_PID_MTC,
                                                                sizeof(MTC_RRC_GSM_CELL_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstGsmCellInfo)
    {
        MTC_ERROR_LOG("MTC_RcvGsmCellInfoInd: Alloc Msg Fail!");
        return;
    }

    pstGsmCellInfo->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstGsmCellInfo->stMsgHeader.ulMsgName     = ID_MTC_RRC_GSM_CELL_INFO_IND;

    pstGsmInfoInd                             = (RRC_MTC_GSM_CELL_INFO_IND_STRU *)pMsg;
    PS_MEM_CPY(&pstGsmCellInfo->stGsmCellInfo,
               &pstGsmInfoInd->stGsmCellInfo,
               sizeof(RRC_MTC_GSM_CELL_INFO_STRU));

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstGsmCellInfo))
    {
        MTC_ERROR_LOG("MTC_RcvGsmCellInfoInd: Snd Msg Err!");
    }

    return;

}

/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of MtcPsTransfer.c */


